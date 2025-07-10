#include "Channel.hpp"

Channel::Channel(const std::string &name) : _channelName(name), _userLimit(0),
	_inviteOnly(false), _topicRestricted(false), _noExternalMessages(true)
{
}


Channel::~Channel()
{
}

/* If channel is +i, remove client from the invited list upon joining. */
void Channel::addClient(Client* client)
{
	if (isInviteOnly() && isInvited(client))
		removeInvited(client);
	if (!hasClient(client))
		_clientMembers.push_back(client);
}

/*
	If client was an operator, remove them.
	If channel ends up with no operators, promote the oldest client.
*/
bool Channel::removeClient(Client* client)
{
	std::vector<Client*>::iterator it = std::find(_clientMembers.begin(), _clientMembers.end(), client);
	if (it != _clientMembers.end())
	{
		if (isOperator(*it))
			removeOperator(*it);
		_clientMembers.erase(it);
		if (!_clientMembers.empty() && !hasOperators())
		{
			const std::string msg = ":" + std::string(HOSTNAME) + " MODE " + _channelName + " +o " + _clientMembers[0]->getNickname();
			addOperator(_clientMembers[0]);
			broadcast(*client, msg, false);
		}
		return _clientMembers.empty();
	}
	return false;
}

bool Channel::hasClient(Client* client) const
{
	return std::find(_clientMembers.begin(), _clientMembers.end(), client) != _clientMembers.end();
}

void Channel::addOperator(Client* client)
{
	if (!isOperator(client))
		_operators.push_back(client);
}

bool Channel::isOperator(Client* client) const
{
	return std::find(_operators.begin(), _operators.end(), client) != _operators.end();
}

void Channel::removeOperator(Client *client)
{
	std::vector<Client*>::iterator it = std::find(_operators.begin(), _operators.end(), client);
	if (it != _operators.end())
		_operators.erase(it);
}

void Channel::setTopic(const std::string &topic) { _topicName = topic; }
const std::string& Channel::getTopic() const { return _topicName; }

void Channel::invite(Client* client)
{
	if (!isInvited(client))
		_invited.push_back(client);
}

void Channel::removeInvited(Client *client)
{
	std::vector<Client*>::iterator it = std::find(_invited.begin(), _invited.end(), client);
	if (it != _invited.end())
		_invited.erase(it);
}

bool Channel::isInvited(Client* client) const
{
	return std::find(_invited.begin(), _invited.end(), client) != _invited.end();
}

void Channel::kick(Client* operatorClient, Client* target, const std::string& reason)
{
	std::string msg = ":" + operatorClient->getHostMask() + " KICK "
				+ _channelName + " " + target->getNickname() + " :" + reason;
	broadcast(*operatorClient, msg, true);
	removeClient(target);
}

void Channel::broadcast(Client &sender, const std::string& message, bool includeSender)
{
	for (size_t i = 0; i < _clientMembers.size(); i++)
	{
		if (includeSender == false && _clientMembers[i] == &sender)
			continue;
		_clientMembers[i]->addToOutputBuffer(message);
	}
}

/*
	Returns true if mode got changed.
*/
bool Channel::setMode(char mode, bool enabled, const std::string& param)
{
	bool	modeChanged = false;

	switch (mode)
	{
		case 'i':
			modeChanged = handleInvite(enabled);
			break;
		case 't':
			modeChanged = handleTopic(enabled);
			break;
		case 'k':
			modeChanged = handleKey(param, enabled);
			break;
		case 'o':
			modeChanged = handleOp(param, enabled);
			break;
		case 'l':
			modeChanged = handleLimit(param, enabled);
			break;
		case 'n':
			modeChanged = handleExternal(enabled);
			break;
		default:
			break;
	}
	return modeChanged;
}

size_t Channel::getUserCount() const { return _clientMembers.size(); }
bool Channel::isInviteOnly() const { return _inviteOnly; }
bool Channel::isTopicRestricted() const { return _topicRestricted; }
bool Channel::isLimited() const { return _userLimit > 0; }
const std::string& Channel::getName() const { return _channelName; }

Client*	Channel::getMemberByName(const std::string& name)
{
	for (size_t i = 0; i < getUserCount(); i++)
		if (name == _clientMembers[i]->getNickname())
			return	_clientMembers[i];
	return nullptr;
}

std::string	Channel::getClientsOnChannel() const
{
	std::string clients;
	for (auto clientPtr = _clientMembers.begin(); clientPtr != _clientMembers.end(); ++clientPtr)
	{
		if (!clients.empty())
			clients += " ";
		if (isOperator(*clientPtr))
			clients += "@" + (*clientPtr)->getNickname();
		else
			clients += (*clientPtr)->getNickname();
	}
	return clients;
}

std::string Channel::getModes() const
{
	std::string modes = "+";

	if (_inviteOnly)
		modes += 'i';
	if (_topicRestricted)
		modes += 't';
	if (!_channelKey.empty())
		modes += 'k';
	if (_userLimit > 0)
		modes += 'l';
	if (_noExternalMessages)
		modes += 'n';

	return modes;
}

size_t Channel::getUserLimit() const { return _userLimit; }
const std::string& Channel::getPassword() const { return _channelKey; }
bool Channel::isEmpty() const { return _clientMembers.empty(); }
bool Channel::hasOperators() const { return _operators.empty() == false; }
bool Channel::noExternalMessages() const { return _noExternalMessages; }

std::string Channel::getModeParams() const
{
	std::string params;

	if (!_channelKey.empty())
		params += _channelKey;
	if (_userLimit > 0)
	{
		if (!params.empty())
			params += " ";
		params += std::to_string(_userLimit);
	}

	return params;
}

bool Channel::handleInvite(bool enabled)
{
	if (_inviteOnly != enabled)
	{
		_inviteOnly = enabled;
		return true;
	}
	return false;
}

bool Channel::handleTopic(bool enabled)
{
	if (_topicRestricted != enabled)
	{
		_topicRestricted = enabled;
		return true;
	}
	return false;
}

bool Channel::handleKey(const std::string &channelKey, bool enabled)
{
	if (enabled)
	{
		if (_channelKey == channelKey)
			return false;
		_channelKey = channelKey;
		return true;
	}
	else if (!_channelKey.empty())
	{
		_channelKey.clear();
		return true;
	}
	return false;
}

bool Channel::handleOp(const std::string &nickname, bool enabled)
{
	Client* target = getMemberByName(nickname);
	if (target)
	{
		if (enabled && !isOperator(target))
		{
			addOperator(target);
			return true;
		}
		else if (!enabled && isOperator(target))
		{
			removeOperator(target);
			return true;
		}
	}
	return false;
}

bool Channel::handleLimit(const std::string &limit, bool enabled)
{
	if (enabled)
	{
		std::istringstream iss(limit);
		size_t limit;
		if (!(iss >> limit) || limit == 0 || _userLimit == limit)
			return false;
		_userLimit = limit;
		return true;
	}
	else if (_userLimit > 0)
	{
		_userLimit = 0;
		return true;
	}
	return false;
}

bool Channel::handleExternal(bool enabled)
{
	if (_noExternalMessages != enabled)
	{
		_noExternalMessages = enabled;
		return true;
	}
	return false;
}
