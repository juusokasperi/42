#include "Server.hpp"

static void sanitizeUsername(std::string& username);
static void sanitizeRealname(std::string& realname);

void	Server::handleNick(Client& client, const std::vector<std::string>& params)
{
	if (params.empty())
		return client.addToOutputBuffer(formatNumReply(ERR_NONICKNAMEGIVEN, client.getNickname()));

	const std::string& nickname = params[0];
	if (!client.getNickname().empty() && nickname == client.getNickname())
		return;
	int errorCode = validateNickname(nickname);
	if (errorCode != 0)
		return client.addToOutputBuffer(formatNumReply(errorCode, client.getNickname(), nickname));

	if (!client.getNickname().empty())
		_nicknameMap.erase(strToLower(client.getNickname()));

	std::string	announce = ":" + client.getHostMask() + " NICK :" + nickname;
	client.setNickname(nickname);
	_nicknameMap[strToLower(nickname)] = &client;
	if (client.isRegistered() && !client.hasReceivedWelcome())
		handleWelcome(client);
	else if (client.hasReceivedWelcome())
		client.addToOutputBuffer(announce);
	sendToAllChannelsWithClient(client, announce, false, false);
}

void	Server::handleUser(Client& client, const std::vector<std::string>& params)
{
	if (client.isRegistered())  // is this check needed?
	{
		client.addToOutputBuffer(formatNumReply(ERR_ALREADYREGISTERED, client.getNickname(), "USER"));
		return;
	}
	if (params.size() != 4 || params[3].empty())
		return client.addToOutputBuffer(formatNumReply(ERR_NEEDMOREPARAMS, client.getNickname(), "USER"));

	std::string username = params[0];
	std::string hostname = params[1];  // usually ignored
	std::string servername = params[2];  // usually ignored
	std::string realname = params[3];

	sanitizeUsername(username);
	sanitizeRealname(realname);

	client.setUserInfo(username, realname);
	if (client.isRegistered() && !client.hasReceivedWelcome())
		handleWelcome(client);
}

int	Server::validateNickname(const std::string& nick)
{
	if (nick.length() > NICK_LENGTH)
		return ERR_ERRONEOUSNICKNAME;

	char first = nick[0];
	if (!isalpha(first))
		return ERR_ERRONEOUSNICKNAME;

	for (char c : nick)
	{
		if (!isalnum(c) && c != '-' && c != '[' && c != ']' && c != '\\'
			&& c != '`' && c != '^' && c != '{' && c != '}')
			return ERR_ERRONEOUSNICKNAME;
	}
	if (getClientByNickname(nick) != nullptr)
			return ERR_NICKNAMEINUSE;
	return 0;
}

static void sanitizeUsername(std::string& username)
{
	if (username.length() > USERNAME_LENGTH)
		username = username.substr(0, USERNAME_LENGTH);
	for (size_t i = 0; i < username.length(); ++i)
	{
		if (username[i] == '\0' || username[i] == '\r' || username[i] == '\n'
			|| username[i] == ' ' || username[i] == '@')
			username[i] = '_';
	}
}

static void sanitizeRealname(std::string& realname)
{
	if (realname.length() > REALNAME_LENGTH)
		realname = realname.substr(0, REALNAME_LENGTH);
	for (size_t i = 0; i < realname.length(); ++i)
	{
		if (realname[i] == '\0' || realname[i] == '\r' || realname[i] == '\n')
			realname[i] = '_';
	}
}
