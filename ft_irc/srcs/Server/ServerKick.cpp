#include "Server.hpp"

void	Server::handleKick(Client &client, const std::vector<std::string>& params)
{
	if (params.size() < 2)
		return client.addToOutputBuffer(formatNumReply(ERR_NEEDMOREPARAMS, client.getNickname(), "KICK"));

	const std::string& channelName = params[0];
	Channel *channel = getChannelByName(channelName);
	if (!channel)
		return client.addToOutputBuffer(formatNumReply(ERR_NOSUCHCHANNEL, client.getNickname(), channelName));
	if (!channel->isOperator(&client))
		return client.addToOutputBuffer(formatNumReply(ERR_CHANOPRIVSNEEDED, client.getNickname(), channelName));

	std::vector<std::string> targets = separateBy(params[1], ',');
	if (targets.size() > MAX_TARGETS)
		return client.addToOutputBuffer(formatNumReply(ERR_TOOMANYTARGETS, client.getNickname(),
			targets[MAX_TARGETS], ":" + std::to_string(targets.size()) + " targets."));

	std::string reason = (params.size() > 2) ? params[2] : "No reason given";
	if (reason.length() > KICK_LENGTH)
		reason = reason.substr(0, KICK_LENGTH);

	for (size_t i = 0; i < targets.size(); ++i)
	{
		const std::string& nick = targets[i];
		Client* target = getClientByNickname(nick);

		if (!target)
		{
			client.addToOutputBuffer(formatNumReply(ERR_NOSUCHNICK, client.getNickname(), nick));
			continue;
		}
		else if (!channel->hasClient(target))
		{
			client.addToOutputBuffer(formatNumReply(ERR_USERNOTINCHANNEL, client.getNickname(), channel->getName()));
			continue;
		}
		channel->kick(&client, target, reason);
		if (channel->isEmpty())
			return removeChannel(channel->getName()); // If channel becomes empty, early return.
	}
}


