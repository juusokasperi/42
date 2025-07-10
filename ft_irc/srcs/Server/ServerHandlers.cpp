#include "Server.hpp"

/*
	Sends;
		001 RPL_WELCOME
		002 RPL_YOURHOST
		003 RPL_CREATED
		004 RPL_MYINFO
		005 RPL_ISUPPORT
*/
void	Server::handleWelcome(Client& client)
{
	const std::string hostname = HOSTNAME;
	const std::string networkName = "42 FT_IRC";
	const std::string supportReply =
		"CHANTYPES=# CHANMODES=,k,l,nti CHANLIMIT=#:" + std::to_string(USER_MAX_CHANNELS)
		+ " CASEMAPPING=rfc1459-strict PREFIX=(o)@"
		+ " NICKLEN=" + std::to_string(NICK_LENGTH)
		+ " CHANNELLEN=" + std::to_string(CHANNEL_LENGTH)
		+ " TOPICLEN=" + std::to_string(TOPIC_LENGTH)
		+ " USERLEN=" + std::to_string(USERNAME_LENGTH)
		+ " KICKLEN=" + std::to_string(KICK_LENGTH)
		+ " TARGMAX=PRIVMSG:" + std::to_string(MAX_TARGETS) + ",KICK:" + std::to_string(MAX_TARGETS)
		+ ",NAMES:" + std::to_string(MAX_TARGETS)
		+ " :are supported by this server";
	client.addToOutputBuffer(formatManualReply(RPL_WELCOME, client.getNickname(), ":Welcome to the", networkName, client.getHostMask()));
	client.addToOutputBuffer(formatManualReply(RPL_YOURHOST, client.getNickname(), ":Your host is", hostname + ", running version 1.0"));
	client.addToOutputBuffer(formatManualReply(RPL_CREATED, client.getNickname(), ":This server was created", _serverCreated));
	client.addToOutputBuffer(formatManualReply(RPL_MYINFO, client.getNickname(), hostname, "ft_irc 1.0 '' itkol"));
	client.addToOutputBuffer(formatManualReply(RPL_ISUPPORT, client.getNickname(), supportReply));
	client.setWelcomeReceived();
	handleMotd(client);
}

void	Server::handleQuit(Client &client, const std::vector<std::string> &params)
{
	if (params.empty() || params[0].empty())
		client.setDisconnect("");
	else
		client.setDisconnect(params[0]);
	client.addToOutputBuffer(":" + client.getHostMask() + " QUIT :" + client.getQuitMsg());
	client.addToOutputBuffer("ERROR :Closing Link: " + client.getIpAddress() + " (" + client.getQuitMsg() + ")");
}

void		Server::handleInvite(Client &client, const std::vector<std::string>& params)
{
	if (params.size() < 2)
		return client.addToOutputBuffer(formatNumReply(ERR_NEEDMOREPARAMS, client.getNickname(), "INVITE"));

	const std::string& channelName = params[1];
	const std::string& targetNick = params[0];
	Channel* channel = getChannelByName(channelName);

	if (!channel)
		return client.addToOutputBuffer(formatNumReply(ERR_NOSUCHCHANNEL, client.getNickname(), channelName));
	if (!channel->isOperator(&client))
		return client.addToOutputBuffer(formatNumReply(ERR_CHANOPRIVSNEEDED, client.getNickname(), channelName));

	Client *target = getClientByNickname(targetNick);
	if (!target)
		return client.addToOutputBuffer(formatNumReply(ERR_NOSUCHNICK, client.getNickname(), targetNick, channelName));
	if (channel->hasClient(target))
		return client.addToOutputBuffer(formatNumReply(ERR_USERONCHANNEL, client.getNickname(), targetNick, channelName));

	channel->invite(target);
	client.addToOutputBuffer(formatManualReply(RPL_INVITING, client.getNickname(), targetNick, channelName));
	target->addToOutputBuffer(":" + client.getNickname() + " INVITE " + targetNick + " :" + channelName);
}

void		Server::handleTopic(Client &client, const std::vector<std::string>& params)
{
	if (params.size() < 1)
		return client.addToOutputBuffer(formatNumReply(ERR_NEEDMOREPARAMS, client.getNickname(), "TOPIC"));

	const std::string& channelName = params[0];
	Channel* channel = getChannelByName(channelName);
	if (!channel)
		return client.addToOutputBuffer(formatNumReply(ERR_NOSUCHCHANNEL, client.getNickname(), channelName));
	if (params.size() < 2)
		return handleTopicQuery(client, channel);

	std::string topicName = params[1];
	if (topicName.length() > TOPIC_LENGTH)
		topicName = topicName.substr(0, TOPIC_LENGTH);

	if (!channel->hasClient(&client))
		return client.addToOutputBuffer(formatNumReply(ERR_NOTONCHANNEL, client.getNickname(), channelName));
	if (channel->isTopicRestricted() && !channel->isOperator(&client))
		return client.addToOutputBuffer(formatNumReply(ERR_CHANOPRIVSNEEDED, client.getNickname(), channelName));

	channel->setTopic(topicName);
	channel->broadcast(client,":" + client.getHostMask() + " TOPIC " + channelName + " :" + topicName, true);
}

void	Server::handleTopicQuery(Client &client, Channel *channel)
{
	const std::string& topicName = channel->getTopic();
	if (topicName.empty())
		return client.addToOutputBuffer(formatManualReply(RPL_NOTOPIC, client.getNickname(), channel->getName(), ":No topic is set"));
	else
		return client.addToOutputBuffer(formatManualReply(RPL_TOPIC, client.getNickname(), channel->getName(), ":" + topicName));
}

void	Server::handleSummon(Client& client)
{
	client.addToOutputBuffer(formatNumReply(ERR_SUMMONDISABLED, client.getNickname(), "SUMMON"));
}

void	Server::handleUsers(Client& client)
{
	client.addToOutputBuffer(formatNumReply(ERR_USERSDISABLED, client.getNickname(), "USERS"));
}

void	Server::handleMotd(Client& client)
{
	if (MOTD.empty())
		return client.addToOutputBuffer(formatNumReply(ERR_NOMOTD, client.getNickname()));

	client.addToOutputBuffer(formatManualReply(RPL_MOTDSTART, client.getNickname(), ":-", HOSTNAME, "Message of The Day -"));
	for (const char* line : MOTD)
		client.addToOutputBuffer(formatManualReply(RPL_MOTD, client.getNickname(), ":-", line));
	client.addToOutputBuffer(formatManualReply(RPL_ENDOFMOTD, client.getNickname(), ":End of /MOTD command."));
}

void	Server::handleNames(Client &client, const std::vector<std::string>& params)
{
	if (params.empty())
	{
		for (size_t i = 0; i < _channels.size(); ++i)
		{
			const std::string& channelName = _channels[i]->getName();
			const std::string clientsOnChannel = _channels[i]->getClientsOnChannel();
			client.addToOutputBuffer(formatManualReply(RPL_NAMREPLY, client.getNickname(), "=", channelName, ":" + clientsOnChannel));
		}
		client.addToOutputBuffer(formatManualReply(RPL_ENDOFNAMES, client.getNickname(), "* :End of /NAMES list"));
		return;
	}

	std::vector<std::string> channelsList = separateBy(params[0], ',');
	if (channelsList.size() > MAX_TARGETS)
		return client.addToOutputBuffer(formatNumReply(ERR_TOOMANYTARGETS, client.getNickname(),
			channelsList[MAX_TARGETS], ":" + std::to_string(channelsList.size()) + " recipients."));
	for (size_t i = 0; i < channelsList.size(); ++i)
	{
		const std::string &channelName = channelsList[i];
		Channel *channel = getChannelByName(channelName);
		if (channel == nullptr)
			client.addToOutputBuffer(formatManualReply(RPL_ENDOFNAMES, client.getNickname(), channelName, ":End of /NAMES list"));
		else
		{
			client.addToOutputBuffer(formatManualReply(RPL_NAMREPLY, client.getNickname(), "=", channel->getName(), ":" + channel->getClientsOnChannel()));
			client.addToOutputBuffer(formatManualReply(RPL_ENDOFNAMES, client.getNickname(), channel->getName(), ":End of /NAMES list"));
		}
	}
}

void	Server::handleWho(Client &client, const std::vector<std::string>& params)
{
	if (params.empty())
		return client.addToOutputBuffer(formatNumReply(ERR_NEEDMOREPARAMS, client.getNickname(), "WHO"));

	const std::string &mask = params[0];
	if (mask[0] == '#' && params.size() == 1)
	{
		Channel *channel = getChannelByName(mask);
		if (channel != nullptr)
		{
			std::vector<std::string> clientsList = separateBy(channel->getClientsOnChannel(), ' ');
			for (size_t i = 0; i < clientsList.size(); ++i)
			{
				std::string nickname = clientsList[i];
				std::string status = "H";
				if (nickname[0] == '@')
				{
					status += "@";
					nickname.erase(0, 1);
				}

				Client* channelMember = getClientByNickname(nickname);
				if (channelMember == nullptr)
					continue;
				const std::string memberInfo = "~" + channelMember->getUsername() + " "
					+ channelMember->getIpAddress() + " " + std::string(HOSTNAME) + " "
					+ channelMember->getNickname() + " " + status
					+ " :0 " + channelMember->getRealname();
				client.addToOutputBuffer(formatManualReply(RPL_WHOREPLY, client.getNickname(), mask, memberInfo));
			}
		}
	}
	client.addToOutputBuffer(formatManualReply(RPL_ENDOFWHO, client.getNickname(), mask, ":End of WHO list."));
}
