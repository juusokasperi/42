#include "Bot/Bot.hpp"

/*
	Initializes an unordered map where the command is the key and the corresponding
	handler function wrapped in lambda is the value.
*/
void Bot::initializeCommandHandlers()
{
	commandHandlers =
	{
		{ "001", [this](const std::vector<std::string>& p, const std::string /* &prefix */) { handleWelcome(p); }},
		{ "353", [this](const std::vector<std::string>& p, const std::string /* &prefix */) { handleNamesReply(p); } },
		{ "PING", [this](const std::vector<std::string>& p, const std::string /* &prefix */) { handlePing(p); } },
		{ "PRIVMSG", [this](const std::vector<std::string>& p, const std::string &prefix) { handlePrivmsg(p, prefix); } },
		{ "JOIN", [this](const std::vector<std::string>& p, const std::string &prefix) { handleJoin(p, prefix); } },
		{ "PART", [this](const std::vector<std::string>& p, const std::string &prefix) { handlePart(p, prefix); } },
		{ "KICK", [this](const std::vector<std::string>& p, const std::string /* &prefix */) { handleKick(p); } },
		{ "INVITE", [this](const std::vector<std::string>& p, const std::string &prefix) { handleInvite(p, prefix); } },
		{ "QUIT", [this](const std::vector<std::string>& /* p */, const std::string /* &prefix */) { handleQuit(); } },
	};
}
