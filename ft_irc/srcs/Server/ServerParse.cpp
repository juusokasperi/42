#include "Server.hpp"

void Server::parseAndExecute(Client &client, std::string &message)
{
	CommandParser parser(message);
	ParsedCommand parsed = parser.parseMessage(message);
	if (parsed.command.empty())
		return;
	handleParsedCommand(client, parsed);
}

/*
	Searches the unordered map for the handler function that matches the command

	If a user tries to send NICK or USER before PASS (if password is set),
		client is set for disconnection. Before PASS only CAP is handled,
		everything else sends the client error 451 ERR_NOTREGISTERED
	If command is not found, return a 421 UNKNOWNCOMMAND to the client
*/
void	Server::handleParsedCommand(Client& client, const ParsedCommand& cmd)
{
	auto it = commandHandlers.find(cmd.command);
	if (!validAuthentication(cmd.command, client))
		return;
	if (it != commandHandlers.end())
		it->second(client, cmd.params);
	else
		client.addToOutputBuffer(formatNumReply(ERR_UNKNOWNCOMMAND, client.getNickname(), cmd.command));
}

/*
	Initializes an unordered map where the command is the key and the corresponding
	handler function wrapped in lambda is the value.
*/
void Server::initializeCommandHandlers()
{
	commandHandlers =
	{
		{ "PASS", [this](Client& c, const std::vector<std::string>& p) { handlePass(c, p); } },
		{ "CAP", [this](Client& c, const std::vector<std::string>& p) { handleCap(c, p); } },
		{ "NICK", [this](Client& c, const std::vector<std::string>& p) { handleNick(c, p); } },
		{ "USER", [this](Client& c, const std::vector<std::string>& p) { handleUser(c, p); } },
		{ "PONG", [this](Client& c, const std::vector<std::string>& p) { handlePong(c, p); } },
		{ "PING", [this](Client& c, const std::vector<std::string>& p) { handlePing(c, p); } },
		{ "PRIVMSG", [this](Client& c, const std::vector<std::string>& p) { handlePrivmsg(c, p); } },
		{ "JOIN", [this](Client& c, const std::vector<std::string>& p) { handleJoin(c, p); } },
		{ "PART", [this](Client& c, const std::vector<std::string>& p) { handlePart(c, p); } },
		{ "KICK", [this](Client& c, const std::vector<std::string>& p) { handleKick(c, p); } },
		{ "MODE", [this](Client& c, const std::vector<std::string>& p) { handleMode(c, p); } },
		{ "INVITE", [this](Client& c, const std::vector<std::string>& p) { handleInvite(c, p); } },
		{ "TOPIC", [this](Client& c, const std::vector<std::string>& p) { handleTopic(c, p); } },
		{ "QUIT", [this](Client& c, const std::vector<std::string>& p) { handleQuit(c, p); } },
		{ "SUMMON", [this](Client& c, const std::vector<std::string>& /* p */) { handleSummon(c); } },
		{ "USERS", [this](Client& c, const std::vector<std::string>& /* p */) { handleUsers(c); } },
		{ "MOTD", [this](Client& c, const std::vector<std::string>& /* p */) { handleMotd(c); } },
		{ "NAMES", [this](Client& c, const std::vector<std::string>& p) { handleNames(c, p); } },
		{ "WHO", [this](Client& c, const std::vector<std::string>& p) { handleWho(c, p); } },
	};
}
