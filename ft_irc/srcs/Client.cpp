#include "Client.hpp"

/*
	Constructors, destructor
*/
Client::Client()
{
	throw std::runtime_error("No fd specified for client.");
}

Client::Client(int fd, const std::string &ipAddress): _ipAddress(ipAddress),
		_hasReceivedWelcome(false), _correctPassword(false),
		_awaitingPong(false)
{
	_pollFd.fd = fd;
	_pollFd.events = POLLIN;
	_pollFd.revents = 0;
	_lastActivity = std::chrono::steady_clock::now();
	_lastPingTime = std::chrono::steady_clock::now();
}

Client::~Client()
{
	if (_pollFd.fd != -1)
		close(_pollFd.fd);
}

Client::Client(Client &&other) noexcept:
	_pollFd(other._pollFd), _lastActivity(other._lastActivity),
	_lastPingTime(other._lastPingTime), _nickname(std::move(other._nickname)), _awaitingPong(other._awaitingPong)
{
	other._pollFd.fd = -1;
}

Client&	Client::operator=(Client &&other) noexcept
{
	if (this != &other)
	{
		if (_pollFd.fd != -1)
			close(_pollFd.fd);
		_pollFd = other._pollFd;
		_lastActivity = other._lastActivity;
		_lastPingTime = other._lastPingTime;
		_nickname = std::move(other._nickname);
		_awaitingPong = other._awaitingPong;
		other._pollFd.fd = -1;
	}
	return (*this);
}

/*
	Getters
*/
int		Client::getFd() const { return _pollFd.fd; }
pollfd& Client::getPollFd() { return _pollFd; }

int		Client::getPongWaitTime() const
{
	if (!_awaitingPong)
		return 0;
	std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
	return std::chrono::duration_cast<std::chrono::seconds>(now - _lastPingTime).count();
}

int		Client::getIdleSeconds() const
{
	std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
	return std::chrono::duration_cast<std::chrono::seconds>(now - _lastActivity).count();
}
const std::string&	Client::getInputBuffer() const { return _inputBuffer; }
std::string&	Client::getOutputBuffer() { return _outputBuffer; }
const std::string&	Client::getNickname() const { return _nickname; }
const std::string&	Client::getUsername() const { return _username; }
const std::string&	Client::getRealname() const { return _realname; }
const std::string&	Client::getIpAddress() const { return _ipAddress; }
const std::string	Client::getHostMask() const { return _nickname + "!" + _username + "@" + _ipAddress; }
bool			Client::isAwaitingPong() const { return _awaitingPong; }
bool			Client::isRegistered() const { return !_nickname.empty() && !_username.empty(); }
bool			Client::hasReceivedWelcome() const { return _hasReceivedWelcome; }
bool			Client::hasEnteredPassword() const { return _correctPassword; }
bool			Client::getDisconnect() const { return _quitMsg.empty() == false; }
const std::string&	Client::getQuitMsg() const { return _quitMsg; }
std::chrono::steady_clock::time_point Client::getDisconnectTime() const { return _quitTime; }

/*
	Setters
*/
void	Client::setWelcomeReceived() { _hasReceivedWelcome = true; }

void	Client::setPingState(bool awaiting)
{
	_awaitingPong = awaiting;
	if (awaiting)
		_lastPingTime = std::chrono::steady_clock::now();
}
void	Client::setNickname(const std::string &nick) { _nickname = nick; }

void	Client::setUserInfo(const std::string &username, const std::string &realname)
{
	_username = username;
	_realname = realname;
}

void	Client::updateActivity() { _lastActivity = std::chrono::steady_clock::now(); }
void	Client::setCorrectPassword() { _correctPassword = true; }

/*
	Sets the client for disconnection, stops listening for incoming messages
	and sets POLLOUT if there is still data to be written to the client
	Stores the time when client was set for disconnection, which is
	a protection against an edge case where client's buffer cannot be emptied
*/
void	Client::setDisconnect(const std::string &quitMsg)
{
	_quitMsg = quitMsg.empty() ? "Client Quit" : quitMsg;
	_quitTime = std::chrono::steady_clock::now();
	_pollFd.events &= ~POLLIN;
	if (!_outputBuffer.empty())
		_pollFd.events |= POLLOUT;
}

void	Client::clearInputBuffer() { _inputBuffer.clear(); }
void	Client::clearOutputBuffer() { _outputBuffer.clear(); }

/*
	Message handling
*/
void			Client::addToInputBuffer(std::string toAppend) { _inputBuffer += toAppend; }
void			Client::addToOutputBuffer(std::string toAppend)
{
	_outputBuffer += toAppend + "\r\n";
	if (!(_pollFd.events & POLLOUT))
		_pollFd.events |= POLLOUT;
}

bool			Client::hasCompleteMessage() const
{
	return ((_inputBuffer.find("\r\n") != std::string::npos)
			|| (_inputBuffer.find('\n') != std::string::npos)
			|| (_inputBuffer.find('\r') != std::string::npos));
}

bool			Client::findLineTerminator(std::string term, std::string &message)
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

std::string		Client::extractMessage()
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

