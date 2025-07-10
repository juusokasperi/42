#include "Server.hpp"

void	Server::sendPing(Client& client)
{
	client.addToOutputBuffer("PING :" + std::string(HOSTNAME));
	client.setPingState(true);
}

/*
	Errors handled:
		461 NOTENOUGHPARAMETERS
		402 NOSUCHSERVER
	Errors not handled:
		409 NOORIGIN (older IRC style required PING to include <client> also,
			but this is not implemented in modern servers)
*/
void Server::handlePing(Client& client, const std::vector<std::string>& params)
{
	const std::string hostname = HOSTNAME;

	if (params.size() == 0)
		client.addToOutputBuffer(formatNumReply(ERR_NEEDMOREPARAMS, client.getNickname(), "PING"));
	else if (params.size() == 1)
		client.addToOutputBuffer(":" + hostname + " PONG " + hostname + " :" + params[0]);
	else
	{
		const std::string& serverPinged = params[1];
		if (serverPinged != hostname)
			client.addToOutputBuffer(formatNumReply(ERR_NOSUCHSERVER, client.getNickname(), serverPinged));
		else
			client.addToOutputBuffer(":" + hostname + " PONG " + hostname + " :" + params[0]);
	}
}

void Server::handlePong(Client& client, const std::vector<std::string>& params)
{
	(void)params;
	if (client.isAwaitingPong())
		client.setPingState(false);
}
