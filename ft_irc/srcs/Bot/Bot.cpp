#include "Bot/Bot.hpp"

volatile sig_atomic_t	Bot::_signalReceived = 0;
static std::string		getTimeNow();

void	Bot::setLogger(Logger* logger)
{
	_logger = logger;
}

Bot::Bot()
{
	throw std::runtime_error("Bot called with no IP address and PORT.");
}

Bot::Bot(const std::string &ipAddress, int serverPort, const std::string &password): _state(RUNNING), _password(password), _nickname(NICKNAME)
{
	if (serverPort <= 0 || serverPort > 65535)
		throw std::runtime_error("Invalid port (1-65535).");

	signal(SIGINT, signalHandler);
	signal(SIGTERM, signalHandler);

	getTimeNow();
	initializeCommandHandlers();
	_channelsJoined.reserve(MAX_CHANNELS);
	setupSocket(ipAddress, serverPort);
	std::cout << "Bot " << NICKNAME << " connected to " << ipAddress << ":" << serverPort << "\n";
}

Bot::~Bot()
{
	if (_fd != -1)
		close(_fd);
}

void	Bot::setDisconnect()
{
	_inputBuffer.clear();
	_quitTime = std::chrono::steady_clock::now();
	addToOutputBuffer("QUIT :Bot shutting down");
	_pollFd.events = POLLOUT;
	_state = SET_FOR_DISCONNECT;
}

void Bot::setAuthentication()
{
	if (!_password.empty())
		addToOutputBuffer("PASS " + _password);
	addToOutputBuffer("NICK " + _nickname);
	addToOutputBuffer("USER " + std::string(USERNAME) + " 0 * :" + std::string(REALNAME));
}

void Bot::run()
{
	setAuthentication();
	auto lastCleanup = std::chrono::steady_clock::now();
	while (_state != QUIT)
	{
		if (_signalReceived == 1 && _state == RUNNING)
			setDisconnect();
		if (checkForTimeout())
			break;

		int pollCount = poll(&_pollFd, 1, POLL_INTERVAL * 1000);
		if (pollCount == -1)
		{
			if (errno == EINTR)
				continue;
			std::cerr << "Poll error: " << strerror(errno) << "\n";
			break;
		}
		else if (pollCount > 0)
		{
			if (_pollFd.revents & POLLIN)
				handleIncomingData();
			else if (_pollFd.revents & POLLOUT)
				handleOutgoingData();
			else if (_pollFd.revents & (POLLHUP | POLLERR))
				break;
		}
		auto now = std::chrono::steady_clock::now();
		if (now - lastCleanup >= GAME_CLEANUP_INTERVAL)
		{
			cleanInactiveGames();
			lastCleanup = now;
		}
	}
}

bool Bot::checkForTimeout()
{
	std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
	int elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - _quitTime).count();
	bool shouldQuit = (_state == SET_FOR_DISCONNECT && elapsed >= DISCONNECT_TIMEOUT);
	if (shouldQuit)
		_state = QUIT;
	return shouldQuit;
}

void Bot::addToInputBuffer(const std::string &toAppend) { _inputBuffer += toAppend; }
void Bot::addToOutputBuffer(const std::string &toAppend)
{
	_outputBuffer += toAppend + "\r\n";
	if (!(_pollFd.events & POLLOUT))
		_pollFd.events |= POLLOUT;
}

void Bot::handleIncomingData()
{
	char buffer[1024];
	memset(buffer, 0, sizeof(buffer));

	ssize_t bytesReceived = recv(_fd, buffer, sizeof(buffer), 0);
	if (bytesReceived == -1)
	{
		if (errno == EAGAIN || errno == EWOULDBLOCK)
			return;
		_state = QUIT;
		return;
	}
	else if (bytesReceived  == 0)
	{
		_state = QUIT;
		return;
	}
	if (memchr(buffer, '\0', bytesReceived) != nullptr)
		return;

	if (_logger && _logger->isLogEnabled())
		_logger->logReceived(std::string(buffer, bytesReceived));

	addToInputBuffer(std::string(buffer, bytesReceived));
	if (_inputBuffer.length() > MAX_IRC_MESSAGE_LENGTH && !hasCompleteMessage())
	{
		clearInputBuffer();
		std::cout << "Received a too long message, clearing buffer.\n";
		return;
	}
	while (hasCompleteMessage() && _state == RUNNING)
	{
		const std::string message = extractMessage();
		if (!message.empty())
			parseAndExecute(message);
	}
}

void Bot::parseAndExecute(const std::string &message)
{
	CommandParser parser(message);
	ParsedCommand parsed = parser.parseMessage(message);

	if (parsed.command.empty())
		return;

	auto it = commandHandlers.find(parsed.command);
	if (it != commandHandlers.end())
		it->second(parsed.params, parsed.prefix);
}

void Bot::clearInputBuffer() { _inputBuffer.clear(); }

bool Bot::hasCompleteMessage() const
{
	return ((_inputBuffer.find("\r\n") != std::string::npos)
			|| (_inputBuffer.find('\n') != std::string::npos)
			|| (_inputBuffer.find('\r') != std::string::npos));
}

void Bot::handleOutgoingData()
{
	if (_outputBuffer.empty())
	{
		_pollFd.events = POLLIN;
		return;
	}
	ssize_t sent = send(_fd, _outputBuffer.c_str(), _outputBuffer.length(), 0);
	if (sent == -1)
	{
		if (errno == EAGAIN || errno == EWOULDBLOCK)
			return;
		_state = QUIT;
		return;
	}
	else if (sent > 0)
	{
		if (_logger && _logger->isLogEnabled())
			_logger->logSent(_outputBuffer.substr(0, sent));
		_outputBuffer.erase(0, sent);
		if (_outputBuffer.empty())
			_pollFd.events = POLLIN;
	}
	if (_state == SET_FOR_DISCONNECT && _outputBuffer.empty())
		_pollFd.events = POLLIN;
}

void Bot::cleanInactiveGames()
{
	const auto now = std::chrono::steady_clock::now();
	const auto timeout = std::chrono::minutes(60);

	for (auto it = channelGames.begin(); it != channelGames.end(); )
	{
		if (now - it->second.getLastGameActivity() > timeout)
			it = channelGames.erase(it);
		else
			++it;
	}
	for (auto it = userGames.begin(); it != userGames.end(); )
	{
		if (now - it->second.getLastGameActivity() > timeout)
			it = userGames.erase(it);
		else
			++it;
	}
}

void Bot::setupSocket(const std::string &ipAddress, int serverPort)
{
	_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (_fd == -1)
		throw std::runtime_error("Failed to create socket.");
	sockaddr_in serverAddr = {};
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(serverPort);
	struct hostent *host = gethostbyname(ipAddress.c_str());
	if (host == nullptr || host->h_addrtype != AF_INET || host->h_length != sizeof(struct in_addr))
	{
		close(_fd);
		throw std::runtime_error("Invalid IP address.");
	}
	serverAddr.sin_addr = *reinterpret_cast<struct in_addr*>(host->h_addr_list[0]);
	if (connect(_fd, (sockaddr*)&serverAddr, sizeof(serverAddr)) == -1)
	{
		close(_fd);
		throw std::runtime_error("Failed to connect to server.");
	}
	if (fcntl(_fd, F_SETFL, O_NONBLOCK) == -1)
	{
		close(_fd);
		throw std::runtime_error("Failed to set non-blocking mode.");
	}
	_pollFd = {_fd, POLLIN, 0};
}

void	Bot::signalHandler(int sig)
{
	if (sig == SIGINT || sig == SIGTERM)
		_signalReceived = 1;
}

static std::string	getTimeNow()
{
	time_t		rawtime;
	struct tm	*timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	return asctime(timeinfo);
}

const std::string		Bot::extractMessage()
{
	std::string message;
	if (findLineTerminator("\r\n", message))
		return message;
	else if (findLineTerminator("\n", message))
		return message;
	else if (findLineTerminator("\r", message))
		return message;
	return "";
}

bool	Bot::findLineTerminator(std::string term, std::string &message)
{
	size_t pos = _inputBuffer.find(term);
	if (pos != std::string::npos)
	{
		if (pos + term.length() > MAX_IRC_MESSAGE_LENGTH)
		{
			message = _inputBuffer.substr(0, MAX_IRC_MESSAGE_LENGTH - 2);
			_inputBuffer.erase(0, pos + term.length());
			return true;
		}
		message = _inputBuffer.substr(0, pos);
		_inputBuffer.erase(0, pos + term.length());
		return true;
	}
	return false;
}
