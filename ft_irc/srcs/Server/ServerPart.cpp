#include "Server.hpp"

void	Server::handlePart(Client &client, const std::vector<std::string>& params)
{
	if (params.empty() || params[0].empty())
		return client.addToOutputBuffer(formatNumReply(ERR_NEEDMOREPARAMS, client.getNickname(), "PART"));

	std::vector<std::string> channelsToPart = separateBy(params[0], ',');
	std::vector<std::string> channelsToRemove;
	const std::string &partMsg = (params.size() > 1) ? " :" + params[1] : "";
	for (size_t i = 0; i < channelsToPart.size(); ++i)
	{
		const std::string& channelName = channelsToPart[i];
		Channel* channel = getChannelByName(channelName);
		if (channel == nullptr)
		{
			client.addToOutputBuffer(formatNumReply(ERR_NOSUCHCHANNEL, client.getNickname(), channelName));
			continue;
		}
		if (!channel->hasClient(&client))
		{
			client.addToOutputBuffer(formatNumReply(ERR_NOTONCHANNEL, client.getNickname(), channelName));
			continue;
		}
		std::string announce = ":" + client.getHostMask() + " PART " + channel->getName() + partMsg;
		channel->broadcast(client, announce, true);
		channel->removeClient(&client);
		if (channel->isEmpty())
			channelsToRemove.push_back(channel->getName());
	}

	for (const std::string& channelName : channelsToRemove)
		removeChannel(channelName);
}

void	Server::partFromAllChannels(Client &client)
{
	std::vector<std::string> channelsToRemove;

	for (std::unique_ptr<Channel>& channel : _channels)
	{
		if (channel->hasClient(&client))
		{
			std::string announce = ":" + client.getHostMask() + " PART " + channel->getName();
			channel->broadcast(client, announce, true);
			channel->removeClient(&client);
			if (channel->isEmpty())
				channelsToRemove.push_back(channel->getName());
		}
	}
	for (const std::string& channelName : channelsToRemove)
		removeChannel(channelName);
}

void	Server::removeChannel(const std::string& channelName)
{
	_channelMap.erase(strToLower(channelName));
	for (size_t i = 0; i < _channels.size(); ++i)
	{
		if (_channels[i]->getName() == channelName)
		{
			_channels.erase(_channels.begin() + i);
			return;
		}
	}
}
