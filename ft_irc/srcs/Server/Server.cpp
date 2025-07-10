#include "Server.hpp"

static std::string		getTimeNow();
volatile sig_atomic_t	Server::_shouldStop = 0;

Server::Server()
{
	throw std::runtime_error("No port specified for Server.");
}

void	Server::setLogger(Logger* logger)
{
	_logger = logger;
}

int Server::getServerPort() const
{
	sockaddr_in6 addr;
	socklen_t addrLen = sizeof(addr);
	if (getsockname(_serverFd, (sockaddr*)&addr, &addrLen) == -1)
		return -1;
	return ntohs(addr.sin6_port);
}

Server::Server(int port, std::string &password):
	_password(password), _lastPingCheck(std::chrono::steady_clock::now())
{
	if (port < 0 || port > 65535)
		throw std::runtime_error("Invalid port (0-65535).");
	if (!validKeyFormat(password) || password == "-")
		throw std::runtime_error("Invalid format for password.");

	signal(SIGINT, signalHandler);
	signal(SIGTERM, signalHandler);

	initializeCommandHandlers();
	_clients.reserve(MAX_CLIENTS + 10);
	_channels.reserve(RESERVE_CHANNELS);
	_nicknameMap.reserve(MAX_CLIENTS);
	_channelMap.reserve(RESERVE_CHANNELS);

	setupServerSocket(port);
	_serverCreated = getTimeNow();
	port = getServerPort();
	if (port == -1)
		throw std::runtime_error("Failed to get server port after socket setup.");
	std::cout << "Server " << HOSTNAME << " listening on port " << port << std::endl;
}

Server::~Server()
{
	_clients.clear();
	_channels.clear();
	close(_serverFd);
}

void Server::run()
{
	while (!_shouldStop)
	{
		std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
		std::chrono::seconds elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - _lastPingCheck);
		if (elapsed.count() >= 5)
		{
			if (checkClientTimeouts())
				handleDisconnections();
			_lastPingCheck = now;
		}

		std::vector<pollfd> pollFds;
		pollFds.push_back(_serverPoll);
		for (std::unique_ptr<Client> &client: _clients)
			pollFds.push_back(client->getPollFd());

		int pollCount = poll(pollFds.data(), pollFds.size(), POLL_INTERVAL);
		if (pollCount == -1)
		{
			if (errno == EINTR)
				continue;
			std::cerr << "Poll error: " << strerror(errno) << std::endl;
			break;
		}
		else if (pollCount > 0)
		{
			if (pollFds[0].revents & POLLIN) // New client calling connect() on the server socket
			{
				acceptConnection();
				continue;
			}
			for (size_t i = 1; i < pollFds.size(); ++i) // Otherwise, check for the client fds
			{
				size_t clientIndex = i - 1;
				if (clientIndex >= _clients.size())
					break;
				std::unique_ptr<Client> &client = _clients[clientIndex];
				if (pollFds[i].revents & (POLLHUP | POLLERR)) // Client has disconnected or an error has occurred
				{
					client->setDisconnect("");
					client->clearOutputBuffer();
					break;
				}
				else if (pollFds[i].revents & POLLIN) // Client has data available to read
				{
					handleClientData(*client);
					break;
				}
				else if (pollFds[i].revents & POLLOUT) // Client socket ready to write data
				{
					handleClientOutput(*client);
					break;
				}
			}
			handleDisconnections(); // Check for disconnection after poll events
		}
	}
	std::cout << "Server " TRED << "shutting down." << TRESET << std::endl;
}

/*
	Remove all the clients that have been marked for disconnection.
	After a client has been marked for disconnection, server allows
	DISCONNECT_TIME seconds to send their outputbuffer, if it takes
	longer than that, client just gets disconnected.
*/
void	Server::handleDisconnections()
{
	std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
	for (int32_t i = static_cast<int32_t>(_clients.size() - 1); i >= 0; --i)
	{
		std::unique_ptr<Client> &client = _clients[i];
		if (client->getDisconnect())
		{
			bool bufferEmpty = client->getOutputBuffer().empty();
			bool timedOut = std::chrono::duration_cast<std::chrono::seconds>(
				now - client->getDisconnectTime()).count() >= DISCONNECT_TIMEOUT;
			if (bufferEmpty || timedOut)
			{
				std::string announce = ":" + client->getHostMask() + " QUIT :" + client->getQuitMsg();
				sendToAllChannelsWithClient(*client, announce, false, true);
				std::cout << TRED << "Disconnecting client fd " << client->getFd() << TRESET << "\n";
				if (!client->getNickname().empty())
					_nicknameMap.erase(strToLower(client->getNickname()));
				_clients.erase(_clients.begin() + i);
			}
		}
	}
}

static void findLongestSequence(const uint16_t *addr16, int &longestStart, int &longestLen)
{
	int currentStart = -1;
	int currentLen = 0;
	for (int i = 0; i < 8; ++i)
	{
		if (ntohs(addr16[i]) == 0)
		{
			if (currentStart == -1)
				currentStart = i;
			currentLen++;
		}
		else
		{
			if (currentLen >= 2 && currentLen > longestLen)
			{
				longestStart = currentStart;
				longestLen = currentLen;
			}
			currentStart = -1;
			currentLen = 0;
		}
	}
	if (currentLen >= 2 && currentLen > longestLen)
	{
		longestStart = currentStart;
		longestLen = currentLen;
	}
}

static bool formatIpAddress(std::string &ipAddress, sockaddr_in6 clientAddr)
{
	if (IN6_IS_ADDR_V4MAPPED(&clientAddr.sin6_addr))
	{
		struct in_addr ipv4_addr;
		ipv4_addr = *reinterpret_cast<struct in_addr*>(&clientAddr.sin6_addr.s6_addr[12]);
		const char *ipStr = inet_ntoa(ipv4_addr);
		if (ipStr == nullptr)
			return false;
		ipAddress = ipStr;
	}
	else
	{
		const uint16_t *addr16 = reinterpret_cast<const uint16_t *>(clientAddr.sin6_addr.s6_addr);
		int longestSequenceStart = -1;
		int longestSequenceLen = 0;
		findLongestSequence(addr16, longestSequenceStart, longestSequenceLen);

		for (int i = 0; i < 8; ++i)
		{
			if (i == longestSequenceStart && longestSequenceLen >= 2)
			{
				ipAddress += "::";
				i += longestSequenceLen - 1;
			}
			else
			{
				if (!ipAddress.empty() && ipAddress.back() != ':')
					ipAddress += ":";
				std::ostringstream buffer;
				buffer << std::hex << ntohs(addr16[i]);
				ipAddress += buffer.str();
			}
		}
	}
	return true;
}

/*
	Attempt to accept an incoming connection.
*/
void	Server::acceptConnection()
{
	sockaddr_in6 clientAddr = {};
	socklen_t clientLen = sizeof(clientAddr);
	int clientFd = accept(_serverFd, (sockaddr*)&clientAddr, &clientLen);
	if (clientFd == -1)
	{
		if (errno == EAGAIN || errno == EWOULDBLOCK)
			return ;
		std::cerr << "Failed to accept connection: " << strerror(errno) << "\n";
		return ;
	}
	if (fcntl(clientFd, F_SETFL, O_NONBLOCK) == -1)
	{
		close(clientFd);
		return;
	}
	std::string ipAddress;
	if (!formatIpAddress(ipAddress, clientAddr))
	{
		close(clientFd);
		return;
	}
	std::unique_ptr<Client> client = std::make_unique<Client>(clientFd, ipAddress);
	if (_clients.size() >= MAX_CLIENTS)
	{
		client->setDisconnect("Server full");
		client->addToOutputBuffer("ERROR :Closing Link: " + client->getIpAddress() + " (" + client->getQuitMsg() + ")");
		_clients.push_back(std::move(client));
		return;
	}
	if (_password.empty())
		client->setCorrectPassword();
	_clients.push_back(std::move(client));
	std::cout << TGREEN << "New client connected (fd: " << clientFd << ")\n" << TRESET;
}

/*
	Receive data from the client
*/
void	Server::handleClientData(Client& client)
{
	int clientFd = client.getFd();
	char buffer[1024];
	memset(buffer, 0, sizeof(buffer));

	ssize_t bytesReceived = recv(clientFd, buffer, sizeof(buffer), 0);
	if (bytesReceived == -1)
	{
		if (errno == EAGAIN || errno == EWOULDBLOCK)
			return ;
		client.setDisconnect("");
		client.clearOutputBuffer();
		return;
	}
	else if (bytesReceived == 0)
	{
		client.setDisconnect("");
		client.clearOutputBuffer();
		return;
	}

	// NULL is not allowed in IRC messages
	if (memchr(buffer, '\0', bytesReceived) != nullptr)
		return;

	client.updateActivity();
	if (_logger && _logger->isLogEnabled())
		_logger->logReceived(std::string(buffer, bytesReceived));

	// If input is over length and has no line terminator, just clear it and send
	// error to client.
	client.addToInputBuffer(std::string(buffer, bytesReceived));
	if (client.getInputBuffer().length() > MAX_IRC_MESSAGE_LENGTH && !client.hasCompleteMessage())
	{
		client.clearInputBuffer();
		client.addToOutputBuffer(formatNumReply(ERR_INPUTTOOLONG, client.getNickname()));
		return;
	}
	while (client.hasCompleteMessage())
	{
		std::string message = client.extractMessage();
		if (!message.empty() && !client.getDisconnect())
			parseAndExecute(client, message);
	}
}

/*
	If we have set POLLOUT for the client and their outputBuffer is not empty,
	send the buffer to that client and empty the buffer from the beginning until to
	variable sent (how many bytes were sent).
*/
void	Server::handleClientOutput(Client& client)
{
	int clientFd = client.getFd();
	std::string& outputBuffer = client.getOutputBuffer();
	if (outputBuffer.empty())
	{
		client.getPollFd().events = POLLIN;
		return;
	}
	ssize_t sent = send(clientFd, outputBuffer.c_str(), outputBuffer.length(), 0);
	if (sent == -1)
	{
		if (errno == EAGAIN || errno == EWOULDBLOCK)
			return;
		client.setDisconnect("");
		client.clearOutputBuffer();
	}
	else if (sent > 0)
	{
		if (_logger && _logger->isLogEnabled())
			_logger->logSent(outputBuffer.substr(0, sent));
		outputBuffer.erase(0, sent);
		if (outputBuffer.empty())
			client.getPollFd().events = POLLIN;
	}
}


/*
	IF	 a client is set for disconnection, set boolean to true
	ELIF a client is idle for too long, try to PING it
	ELIF a client has been pinged but hasn't responded in the given time,
		 mark for disconnection, clear outputbuffer and set boolean to true.
*/
bool	Server::checkClientTimeouts()
{
	bool	clientsSetToDisconnect = false;
	for (int32_t i = static_cast<int32_t>(_clients.size() - 1); i >= 0; --i)
	{
		std::unique_ptr<Client> &client = _clients[i];
		if (client->getDisconnect())
		{
			clientsSetToDisconnect = true;
			continue;
		}
		int idleTime = client->getIdleSeconds();
		if (idleTime >= PING_INTERVAL && !client->isAwaitingPong())
			sendPing(*client);
		else if (client->isAwaitingPong() && client->getPongWaitTime() >= PONG_TIMEOUT)
		{
			client->setDisconnect("Timed out");
			client->clearOutputBuffer();
			clientsSetToDisconnect = true;
		}
	}
	return (clientsSetToDisconnect);
}

void	Server::signalHandler(int sig)
{
	if (sig == SIGINT || sig == SIGTERM)
		_shouldStop = 1;
}

static std::string	getTimeNow()
{
	time_t		rawtime;
	struct tm	*timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	return asctime(timeinfo);
}

void Server::setupServerSocket(int port)
{
	_serverFd = socket(AF_INET6, SOCK_STREAM, 0);
	if (_serverFd == -1)
		throw std::runtime_error("Failed to create socket.");
	if (fcntl(_serverFd, F_SETFL, O_NONBLOCK) == -1)
	{
		close(_serverFd);
		throw std::runtime_error("Failed to set non-blocking mode.");
	}
	int opt = 1;
	if (setsockopt(_serverFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
	{
		close(_serverFd);
		throw std::runtime_error("Failed to set SO_REUSEADDR.");
	}
	int ipv6only = 0;
	if (setsockopt(_serverFd, IPPROTO_IPV6, IPV6_V6ONLY, &ipv6only, sizeof(ipv6only)) == -1)
	{
		close(_serverFd);
		throw std::runtime_error("Failed to set IPV6_V6ONLY.");
	}
	sockaddr_in6 addr = {};
	addr.sin6_family = AF_INET6;
	addr.sin6_addr = in6addr_any;
	addr.sin6_port = htons(port);
	if (bind(_serverFd, (sockaddr*)&addr, sizeof(addr)) == -1)
	{
		close(_serverFd);
		throw std::runtime_error("Failed to bind socket.");
	}
	if (listen(_serverFd, SOMAXCONN) == -1)
	{
		close(_serverFd);
		throw std::runtime_error("Failed to listen on socket.");
	}
	_serverPoll = {_serverFd, POLLIN, 0};
}
