#include "Server.hpp"

/*
	Handled;
		JOIN 0
			- special case, leaves all joined channels
		461	ERR_NEEDMOREPARAMS
		403 ERR_NOSUCHCHANNEL
			- channel name invalid
		476 ERR_BADCHANMASK
			- channel name invalid
		475 ERR_BADCHANNELKEY
			- (+k) invalid password
		473 ERR_INVITEONLYCHAN
		471 ERR_CHANNELISFULL
			- (+l) channel full
		331 RPL_NOTOPIC
		332 RPL_TOPIC
		405 ERR_TOOMANYCHANNELS
		407 ERR_TOOMANYTARGETS
	Not handled;
		474 ERR_BANNEDFROMCHAN
			- we don't support +b
		473 ERR_UNAVAILRESOURCE
			- we don't have a channel delay mechanism
*/
void	Server::handleJoin(Client &client, const std::vector<std::string>& params)
{
	if (params.empty() || params[0].empty())
		return client.addToOutputBuffer(formatNumReply(ERR_NEEDMOREPARAMS, client.getNickname(), "JOIN"));

	std::vector<std::string> channelsToJoin = separateBy(params[0], ',');
	std::vector<std::string> passwordsList;
	if (params.size() > 1)
		passwordsList = separateBy(params[1], ',');

	size_t channelsJoined = countChannelsJoined(client);
	for (size_t i = 0; i < channelsToJoin.size(); ++i)
	{
		const std::string& channelName = channelsToJoin[i];
		const std::string& password = (i < passwordsList.size()) ? passwordsList[i] : "";

		if (channelName == "0")
		{
			partFromAllChannels(client);
			channelsJoined = 0;
			continue;
		}
		if (!validateChannelName(client, channelName))
			continue;
		if (channelsJoined >= USER_MAX_CHANNELS)
		{
			client.addToOutputBuffer(formatNumReply(ERR_TOOMANYCHANNELS, client.getNickname(), channelName));
			continue;
		}
		Channel *channel = getOrCreateChannel(channelName, client);
		if (channel == nullptr || !channelJoinAllowed(client, channel, password))
			continue;
		channel->addClient(&client);
		sendJoinMessages(client, channel);
		channelsJoined++;
	}
}

void	Server::sendJoinMessages(Client &client, Channel *channel)
{
		std::string announce = ":" + client.getHostMask() + " JOIN " + channel->getName();
		channel->broadcast(client, announce, true);
		const std::string& channelTopic = channel->getTopic();
		if (channelTopic.empty())
			client.addToOutputBuffer(formatManualReply(RPL_NOTOPIC, client.getNickname(), channel->getName(), ":No topic is set"));
		else
			client.addToOutputBuffer(formatManualReply(RPL_TOPIC, client.getNickname(), channel->getName(), ":" + channelTopic));
		client.addToOutputBuffer(formatManualReply(RPL_NAMREPLY, client.getNickname(), "=", channel->getName(), ":" + channel->getClientsOnChannel()));
		client.addToOutputBuffer(formatManualReply(RPL_ENDOFNAMES, client.getNickname(), channel->getName(), ":End of /NAMES list"));
}

bool	Server::validateChannelName(Client &client, const std::string& channelName)
{
	if (channelName.empty())
	{
		client.addToOutputBuffer(formatNumReply(ERR_BADCHANMASK, client.getNickname(), channelName));
		return false;
	}
	if (channelName.length() > CHANNEL_LENGTH
		|| channelName[0] == '+' || channelName[0] == '!' || channelName[0] == '&')
	{
		client.addToOutputBuffer(formatNumReply(ERR_NOSUCHCHANNEL, client.getNickname(), channelName));
		return false;
	}
	if (channelName[0] != '#' || channelName.length() == 1)
	{
		client.addToOutputBuffer(formatNumReply(ERR_BADCHANMASK, client.getNickname(), channelName));
		return false;
	}
	for (size_t i = 1; i < channelName.length(); ++i)
	{
		char c = channelName[i];
		if (c == '\0' || c == '\7' || c == '\r' || c == '\n'
			|| c == ' ' || c == ',' || c == ':')
		{
			client.addToOutputBuffer(formatNumReply(ERR_BADCHANMASK, client.getNickname(), channelName));
			return false;
		}
	}
	return true;
}

bool	Server::channelJoinAllowed(Client &client, Channel* chan, const std::string &password)
{
	const std::string& channelName = chan->getName();
	const std::string& channelKey = chan->getPassword();
	if (!channelKey.empty() && channelKey != password)
	{
		client.addToOutputBuffer(formatNumReply(
			ERR_BADCHANNELKEY, client.getNickname(), channelName));
		return false;
	}
	size_t userLimit = chan->getUserLimit();
	if (userLimit > 0 && chan->getUserCount() >= userLimit)
	{
		client.addToOutputBuffer(formatNumReply(
			ERR_CHANNELISFULL, client.getNickname(), channelName));
		return false;
	}
	if (chan->isInviteOnly() && !chan->isInvited(&client))
	{
		client.addToOutputBuffer(formatNumReply(
			ERR_INVITEONLYCHAN, client.getNickname(), channelName));
		return false;
	}
	return true;
}

Channel* Server::getOrCreateChannel(const std::string &channelName, Client& client)
{
	Channel* channel = getChannelByName(channelName);
	if (channel == nullptr) // Channel doesn't exist, create a new one
		return createChannel(channelName, client);
	if (channel->hasClient(&client)) // If client already on channel, ignore the command
		return nullptr;
	return channel;
}
