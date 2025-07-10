#include "Server.hpp"

void	Server::sendToAllChannelsWithClient(Client &client,
		const std::string &message, bool includeSender, bool removeClient)
{
	std::vector<std::string> channelsToRemove;

	for (size_t i = 0; i < _channels.size(); ++i)
	{
		if (_channels[i]->hasClient(&client))
		{
			_channels[i]->broadcast(client, message, includeSender);
			if (removeClient == true)
			{
				_channels[i]->removeClient(&client);
				if (_channels[i]->isEmpty())
					channelsToRemove.push_back(_channels[i]->getName());
			}
		}
	}
	for (const std::string& channelName : channelsToRemove)
		removeChannel(channelName);
}

Channel* Server::getChannelByName(const std::string &channelName)
{
	auto it = _channelMap.find(strToLower(channelName));
	return (it != _channelMap.end()) ? it->second : nullptr;
}

Client*	Server::getClientByNickname(const std::string &clientName)
{
	auto it = _nicknameMap.find(strToLower(clientName));
	return (it != _nicknameMap.end()) ? it->second : nullptr;
}

Channel* Server::createChannel(const std::string &chanName, Client &client)
{
	auto newChannel = std::make_unique<Channel>(chanName);
	Channel* chan = newChannel.get();
	chan->addClient(&client);
	chan->addOperator(&client);
	_channels.push_back(std::move(newChannel));
	_channelMap[strToLower(chanName)] = chan;

	return chan;
}

size_t Server::countChannelsJoined(Client &client) const
{
	size_t count = 0;
	for (size_t i = 0; i < _channels.size(); ++i)
	{
		if (_channels[i]->hasClient(&client))
			count++;
	}
	return count;
}

/*
	Replies with the approppriate error message
*/
std::string Server::formatNumReply(int code,
									std::string_view arg1,
									std::string_view arg2,
									std::string_view arg3)
{
	std::ostringstream oss;
	oss << ":" << HOSTNAME << " " << std::to_string(code);

	oss << " " << (arg1.empty() ? "*" : arg1);
	if (!arg2.empty())
		oss << " " << arg2;
	if (!arg3.empty())
		oss << " " << arg3;

	oss << " " << getErrorMessage(code);
	return oss.str();
}

/*
	Formats a reply with manually set parameters
*/
std::string Server::formatManualReply(int code,
										std::string_view arg1,
										std::string_view arg2,
										std::string_view arg3,
										std::string_view arg4)
{
	if (arg1.empty())
	 return ("");
	std::ostringstream oss;
	std::string codeStr = std::to_string(code);
	while (codeStr.length() < 3)
		codeStr.insert(0, 1, '0');
	oss << ":" << HOSTNAME << " " << codeStr;
	oss << " " << arg1;
	if (!arg2.empty())
		oss << " " << arg2;
	if (!arg3.empty())
		oss << " " << arg3;
	if (!arg4.empty())
		oss << " " << arg4;
	return oss.str();
}

bool	Server::validKeyFormat(const std::string& password)
{
	if (password.empty())
		return true;
	if (password.length() > 23)
		return false;
	for (size_t i = 0; i < password.length(); ++i)
	{
		unsigned char c = password[i];
		if (c == 0x00 || c == 0x06 || (c >= 0x09 && c <= 0x0B)
			|| c == 0x0D || c == 0x20 || c > 0x7F)
			return false;
	}
	return true;
}

std::vector<std::string>	Server::separateBy(std::string toSeparate, char separator)
{
	std::vector<std::string> result;
	std::stringstream ss(toSeparate);
	std::string token;
	while (std::getline(ss, token, separator))
		if (!token.empty())
			result.push_back(token);
	return (result);
}

/*
	Channel names and nicknames are treated case-insensitive.
	IRC protocol also treats chars []\ as {}|.
*/
const std::string Server::strToLower(const std::string &s)
{
	std::string	result = s;
	for (size_t i = 0; i < result.size(); ++i)
	{
		if (result[i] == '[')
			result[i] = '{';
		else if (result[i] == ']')
			result[i] = '}';
		else if (result[i] == '\\')
			result[i] = '|';
		else
			result[i] = std::tolower(result[i]);
	}
	return result;
}
