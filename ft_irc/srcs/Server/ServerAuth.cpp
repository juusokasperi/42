#include "Server.hpp"

/*
	Errors handled;
		462 ERR_ALREADYREGISTERED
		461 ERR_NEEDMOREPARAMS
		464 ERR_PASSWDMISMATCH
*/
void	Server::handlePass(Client& client, const std::vector<std::string>& params)
{
	if (client.isRegistered())
		client.addToOutputBuffer(formatNumReply(ERR_ALREADYREGISTERED, client.getNickname()));
	else if (client.hasEnteredPassword())
		return;
	else if (params.empty())
	{
		client.addToOutputBuffer(formatNumReply(ERR_NEEDMOREPARAMS, client.getNickname(), "PASS"));
		client.addToOutputBuffer("ERROR :Closing Link: " + client.getIpAddress() + " (incorrect password)");
		client.setDisconnect("");
	}
	else if (params[0] == _password)
		client.setCorrectPassword();
	else
	{
		client.addToOutputBuffer(formatNumReply(ERR_PASSWDMISMATCH, client.getNickname()));
		client.addToOutputBuffer("ERROR :Closing Link: " + client.getIpAddress() + " (incorrect password)");
		client.setDisconnect("");
	}
}

void	Server::handleCap(Client& client, const std::vector<std::string>& params)
{
	if (params.empty())
	return;

	const std::string hostname = HOSTNAME;
	if (params[0] == "LS")
		client.addToOutputBuffer(":" + hostname + " CAP * LS :");
	else if (params[0] == "REQ" && params.size() > 1)
		client.addToOutputBuffer(":" + hostname + " CAP * NAK :" + params[1]);
}

/*
	If a user tries to send NICK or USER before PASS (if password is set),
	client is set for disconnection. Before PASS only CAP is handled,
	everything else sends the client error 451 ERR_NOTREGISTERED
*/
bool	Server::validAuthentication(const std::string &cmd, Client& client)
{
	if (client.hasEnteredPassword() && client.isRegistered())
		return true;
	if (cmd == "CAP" || cmd == "PASS")
		return true;
	if (!client.hasEnteredPassword())
	{
		if (cmd == "NICK" || cmd == "USER")
		{
			client.addToOutputBuffer(formatNumReply(ERR_PASSWDMISMATCH, "*"));
			client.addToOutputBuffer("ERROR :Closing Link: " + client.getIpAddress() + " (incorrect password)");
			client.setDisconnect("");
			return false;
		}
		client.addToOutputBuffer(formatNumReply(ERR_NOTREGISTERED, "*", cmd));
		return false;
	}
	if (cmd == "NICK" || cmd == "USER")
		return true;
	client.addToOutputBuffer(formatNumReply(ERR_NOTREGISTERED, "*", cmd));
	return false;
}
