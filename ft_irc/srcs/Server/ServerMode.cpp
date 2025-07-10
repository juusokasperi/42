#include "Server.hpp"

static bool	signChange(std::string &appliedModes, bool enable);
static void formatAppliedModes(std::string &appliedModes, std::string &appliedParams,
			const std::string &modeParam, char mode, bool enable);
static void	broadcastModeChanges(Client &client, Channel *channel,
			const std::string &appliedModes, const std::string &appliedParams);

void	Server::handleMode(Client &client, const std::vector<std::string>& params)
{
	if (params.empty())
		return client.addToOutputBuffer(formatNumReply(ERR_NEEDMOREPARAMS, client.getNickname(), "MODE"));

	const std::string& target = params[0];
	if (std::string("#+!&").find(target[0]) == std::string::npos)
		return handleUserMode(client, params);
	Channel* channel = getChannelByName(target);
	if (!channel)
		return client.addToOutputBuffer(formatNumReply(ERR_NOSUCHCHANNEL, client.getNickname(), target));
	if (params.size() == 1)
		return handleModeQuery(client, channel);
	if (!channel->isOperator(&client))
		return client.addToOutputBuffer(formatNumReply(ERR_CHANOPRIVSNEEDED, client.getNickname(), target));

	const std::string& modeString = params[1];
	if (!validateModes(client, modeString))
		return;

	bool enable = true;
	size_t j = 2;
	std::string appliedModes;
	std::string appliedParams;

	for (size_t i = 0; i < modeString.size(); ++i)
	{
		char mode = modeString[i];
		if (mode == '+')
			enable = true;
		else if (mode == '-')
			enable = false;
		else
		{
			std::string modeParam;
			if (mode == 'k' && !handleModeKey(enable, client, channel, j, params, modeParam))
				continue;
			else if (mode == 'o' && !handleModeOp(client, channel, j, params, modeParam))
				continue;
			else if (mode == 'l' && !handleModeLimit(enable, client, j, params, modeParam))
				continue;
			if (channel->setMode(mode, enable, modeParam))
				formatAppliedModes(appliedModes, appliedParams, modeParam, mode, enable);
		}
	}
	if (!appliedModes.empty())
		broadcastModeChanges(client, channel, appliedModes, appliedParams);
}

bool	Server::validateModes(Client &client, const std::string& modeString)
{
	const std::string validModes = "itklon+-";
	for (size_t i = 0; i < modeString.size(); ++i)
	{
		char mode = modeString[i];
		if (validModes.find(mode) == std::string::npos)
		{
			client.addToOutputBuffer(formatNumReply(ERR_UNKNOWNMODE, client.getNickname(), std::string(1, mode)));
			return false;
		}
	}
	return true;
}

void	Server::handleModeQuery(Client &client, Channel *channel)
{
	const std::string &channelName = channel->getName();

	if (channel->hasClient(&client))
		return client.addToOutputBuffer(formatManualReply(RPL_CHANNELMODEIS, client.getNickname(), channelName, channel->getModes(), channel->getModeParams()));
	else
		return client.addToOutputBuffer(formatManualReply(RPL_CHANNELMODEIS, client.getNickname(), channelName, channel->getModes()));
}

bool	Server::handleModeKey(bool enable, Client &client, Channel *channel,
		size_t &j, const std::vector<std::string> &params, std::string &modeParam)
{
	if (enable && j >= params.size())
	{
		client.addToOutputBuffer(formatNumReply(ERR_NEEDMOREPARAMS, client.getNickname(), "MODE"));
		return false;
	}
	if (enable)
	{
		modeParam = params[j++];
		if (!validKeyFormat(modeParam) || modeParam.empty())
		{
			client.addToOutputBuffer(formatNumReply(ERR_INVALIDKEY, client.getNickname(), channel->getName(), "MODE"));
			return false;
		}
	}
	return true;
}

bool	Server::handleModeOp(Client &client, Channel *channel, size_t &j, const std::vector<std::string> &params, std::string &modeParam)
{
	if (j >= params.size())
	{
		client.addToOutputBuffer(formatNumReply(ERR_NEEDMOREPARAMS, client.getNickname(), "MODE"));
		return false;
	}
	modeParam = params[j++];
	Client*	target = getClientByNickname(modeParam);
	if (!target)
	{
		client.addToOutputBuffer(formatNumReply(ERR_NOSUCHNICK, client.getNickname(), modeParam));
		return false;
	}
	else if (!channel->hasClient(target))
	{
		client.addToOutputBuffer(formatNumReply(ERR_USERNOTINCHANNEL, client.getNickname(), modeParam));
		return false;
	}
	return true;
}

bool	Server::handleModeLimit(bool enable, Client &client, size_t &j,
		const std::vector<std::string> &params, std::string &modeParam)
{
	if (enable)
	{
		if (j >= params.size())
		{
			client.addToOutputBuffer(formatNumReply(ERR_NEEDMOREPARAMS, client.getNickname(), "MODE"));
			return false;
		}
		modeParam = params[j++];
		for (size_t i = 0; i < modeParam.size(); ++i)
		{
			if (!std::isdigit(modeParam[i]))
				return false;
		}
	}
	return true;
}

static bool	signChange(std::string &appliedModes, bool enable)
{
	if (appliedModes.empty())
		return true;

	bool lastSign = true;
	for (size_t i = 0; i < appliedModes.size(); ++i)
	{
		if (appliedModes[i] == '+')
			lastSign = true;
		else if (appliedModes[i] == '-')
			lastSign = false;
	}
	return lastSign != enable;
}

static void formatAppliedModes(std::string &appliedModes, std::string &appliedParams,
			const std::string &modeParam, char mode, bool enable)
{
	if (signChange(appliedModes, enable))
		appliedModes += (enable ? '+' : '-');
	appliedModes += mode;
	if (!modeParam.empty())
	{
		if (!appliedParams.empty())
			appliedParams += " ";
		appliedParams += modeParam;
	}
}

static void	broadcastModeChanges(Client &client, Channel *channel,
			const std::string &appliedModes, const std::string &appliedParams)
{
		std::string msg =	":" + client.getHostMask() + " MODE "
							+ channel->getName() + " " + appliedModes;
		if (!appliedParams.empty())
			msg += " " + appliedParams;
		channel->broadcast(client, msg, true);
}

void	Server::handleUserMode(Client &client, const std::vector<std::string>&params)
{
	const std::string &target = params[0];
	Client* targetUser = getClientByNickname(target);
	if (!targetUser)
		client.addToOutputBuffer(formatNumReply(ERR_NOSUCHCHANNEL, client.getNickname(), target));
	else if (target == client.getNickname())
	{
		if (params.size() == 1)
			client.addToOutputBuffer(formatManualReply(RPL_UMODEIS, client.getNickname(), "+"));
		else
			client.addToOutputBuffer(formatManualReply(ERR_UMODEUNKNOWNFLAG, client.getNickname(), ":Unknown MODE flag"));
	}
	else
		client.addToOutputBuffer(formatManualReply(ERR_USERSDONTMATCH, client.getNickname(), ":Can't change mode for other users"));
}
