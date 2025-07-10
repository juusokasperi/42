#include "Server.hpp"

/*
	If mode +a (away) is implemented, when sending a PRIVMSG to an away
	client, send also a reply 301 to the sender

	Errors handled;
		401 NOSUCHNICK
		402 NOSUCHSERVER
		407 TOOMANYTARGETS
		411 NORECIPIENT
		412 NOTEXTTOSEND
		404 CANNOTSENDTOCHAN
	Errors not handled;
		413 NOTOPLEVEL
		414 WILDTOPLEVEL
		301 AWAY (reply)
*/
void	Server::handlePrivmsg(Client& client, const std::vector<std::string>& params)
{
	if (!validatePrivmsg(client, params))
		return;
	std::vector<std::string> recipientList = separateBy(params[0], ',');
	std::string message = params[1];
	if (recipientList.size() > MAX_TARGETS)
		return client.addToOutputBuffer(formatNumReply(ERR_TOOMANYTARGETS, client.getNickname(),
			recipientList[MAX_TARGETS], ":" + std::to_string(recipientList.size()) + " recipients."));
	for (std::string& recipient : recipientList)
	{
		if (!checkForHostname(client, recipient))
			continue;
		bool found = false;
		if (recipient[0] == '#')
			found = findAndBroadcastToChannel(client, recipient, message);
		else
			found = findAndSendToClient(client, recipient, message);

		if (!found)
			client.addToOutputBuffer(formatNumReply(ERR_NOSUCHNICK, client.getNickname(), recipient));
	}
}

bool	Server::findAndBroadcastToChannel(Client &client, const std::string &recipient, const std::string &message)
{
	Channel* channel = getChannelByName(recipient);
	if (channel == nullptr)
		return false;
	if (channel->noExternalMessages() && !channel->hasClient(&client))
		client.addToOutputBuffer(formatNumReply(ERR_CANNOTSENDTOCHAN, client.getNickname(), channel->getName()));
	else
	{
		std::string fullMsg =	":" + client.getNickname() + " PRIVMSG "
					+ recipient + " :" + message;
		channel->broadcast(client, fullMsg, false);
	}
	return true;
}

bool	Server::findAndSendToClient(Client &client, const std::string &recipient, const std::string &message)
{
	Client* receivingClient = getClientByNickname(recipient);
	if (receivingClient == nullptr)
		return false;
	const std::string fullMsg = ":" + client.getNickname() + " PRIVMSG " + recipient + " :" + message;
	receivingClient->addToOutputBuffer(fullMsg);
	return true;
}

bool	Server::validatePrivmsg(Client &client, const std::vector<std::string>& params)
{
	if (params.size() == 0)
	{
		client.addToOutputBuffer(formatNumReply(ERR_NORECIPIENT, client.getNickname()));
		return false;
	}
	if (params.size() == 1)
	{
		client.addToOutputBuffer(formatNumReply(ERR_NOTEXTTOSEND, client.getNickname()));
		return false;
	}
	return true;
}

/*
	Checks for `user@hostname` format,
	and that the hostname part matches the hostname of the server
*/
bool Server::checkForHostname(Client &client, std::string &recipient)
{
	size_t atPos = recipient.find('@');
	if (atPos != std::string::npos)
	{
		std::string serverName = recipient.substr(atPos + 1);
		if (serverName != HOSTNAME)
		{
			client.addToOutputBuffer(
				formatNumReply(ERR_NOSUCHSERVER, client.getNickname(), serverName));
			return false;
		}
		recipient = recipient.substr(0, atPos);
	}
	return true;
}
