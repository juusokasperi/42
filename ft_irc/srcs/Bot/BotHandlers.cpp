#include "Bot/Bot.hpp"

static bool isDefaultChannel(const std::string &channelName);
static std::vector<std::string> separateBy(std::string toSeparate, char separator);

static std::vector<std::string>	getHelpMessage()
{
	return {
		"============= Bot42 =============",
		"General Commands:",
		"  !time - Display current date and time",
		"  !roll - Generate random number (0-100)",
		"  !help - Show this help message",
		"Hangman Game:",
		"  !hangman - Start a new game",
		"  !hangman guess <letter> - Guess a single letter (a-z)",
		"  !hangman status - View game status",
		"  !hangman restart - Start over with a new word",
		"  !hangman end - End current game",
		"=================================",
	};
}

void Bot::handlePing(const std::vector<std::string> &params)
{
	if (params.empty())
		addToOutputBuffer("PONG");
	else
		addToOutputBuffer("PONG :" + params[0]);
}

/*
	Join default channels, and update the nickname to make sure it matches
	the server assigned one.
*/
void Bot::handleWelcome(const std::vector<std::string> &params)
{
	if (!params.empty())
		_nickname = params[0];
	joinDefaultChannels();
}

void Bot::joinDefaultChannels()
{
	if (DEFAULT_CHANNELS.empty())
		return;
	for (const char* chan : DEFAULT_CHANNELS)
		addToOutputBuffer("JOIN " + std::string(chan));
}

bool Bot::isBotNickname(const std::string &prefix)
{
	std::string nickname = prefix;
	size_t exclamationPos = nickname.find('!');
	if (exclamationPos != std::string::npos)
		nickname = nickname.substr(0, exclamationPos);
	return nickname == _nickname;
}

const std::string Bot::extractNickname(const std::string &prefix)
{
	std::string nickname = prefix;
	size_t exclamationPos = nickname.find('!');
	if (exclamationPos != std::string::npos)
		nickname = nickname.substr(0, exclamationPos);
	return nickname;
}

/*
	If target of KICK was the bot, remove the channel from channel list
	Otherwise, request a new NAMES from the server to check if channel empty
*/
void Bot::handleKick(const std::vector<std::string> &params)
{
	if (params.size() < 2)
		return;
	const std::string &channel = params[0];
	const std::string &kickedClient = params[1];
	if (isBotNickname(kickedClient))
		return removeFromChannelList(channel);
	addToOutputBuffer("NAMES " + channel);
}

void Bot::addToChannelList(const std::string &channelJoined) { _channelsJoined.insert(strToLower(channelJoined)); }
void Bot::removeFromChannelList(const std::string &channelParted) { _channelsJoined.erase(strToLower(channelParted)); }

/*
	If joiner was not the bot, return.
	Otherwise, add the channel to the joined channel list
*/
void Bot::handleJoin(const std::vector<std::string> &params, const std::string &prefix)
{
	if (params.empty() || !isBotNickname(prefix))
		return;
	const std::string &channelJoined = params[0];
	addToChannelList(channelJoined);
	for (const auto& line : getHelpMessage())
		addToOutputBuffer("PRIVMSG " + params[0] + " :" + line);
}

/*
	If leaver was the bot, remove the channel from bot channel list
	Otherwise, request a new NAMES to check if channel became empty.
*/
void Bot::handlePart(const std::vector<std::string> &params, const std::string &prefix)
{
	if (params.empty())
		return;

	const std::string &channel = params[0];
	if (isBotNickname(prefix))
		return removeFromChannelList(channel);

	addToOutputBuffer("NAMES " + channel);
}

/*
	Since QUIT messages don't have a channel, request a new
	NAMES of all the channels where the bot is on.
*/
void Bot::handleQuit()
{
	for (const std::string& channel : _channelsJoined)
		addToOutputBuffer("NAMES " + channel);
}

/*
	Count the number of clients on a channel.

	If the channel is empty (bot being the only client there) AND it is not
	one of the default channels defined in bot config, vacate the channel.
*/
void Bot::handleNamesReply(const std::vector<std::string> &params)
{
	if (params.size() < 4)
		return;

	const std::string &channelName = params[2];
	std::vector<std::string> usersList = separateBy(params[3], ' ');
	size_t usersOnChannel = 0;
	for (size_t i = 0; i < usersList.size(); ++i)
		usersOnChannel++;
	if (usersOnChannel <= 1 && !isDefaultChannel(channelName))
		addToOutputBuffer("PART " + channelName + " :Parting an empty channel..");
}

static bool isDefaultChannel(const std::string &channelName)
{
	if (DEFAULT_CHANNELS.empty())
		return false;
	for (const char* chan : DEFAULT_CHANNELS)
	{
		if (channelName == chan)
			return true;
	}
	return false;
}

bool	Bot::botOnChannel(const std::string &channel) { return _channelsJoined.find(strToLower(channel)) != _channelsJoined.end(); }

/*
	If bot not on channel already, send a JOIN to server.
*/
void Bot::handleInvite(const std::vector<std::string> &params, const std::string &prefix)
{
	if (params.size() < 2)
		return;
	const std::string &channelToJoin = params[1];
	const std::string &inviter = extractNickname(prefix);
	if (!botOnChannel(channelToJoin))
	{
		if (_channelsJoined.size() > MAX_CHANNELS)
			addToOutputBuffer("PRIVMSG " + inviter + " :Bot has already joined max channels (" + std::to_string(MAX_CHANNELS) + ")");
		else
			addToOutputBuffer("JOIN " + params[1]);
	}
}

static std::vector<std::string> separateBy(std::string toSeparate, char separator)
{
	std::vector<std::string> result;
	std::stringstream ss(toSeparate);
	std::string token;
	while (std::getline(ss, token, separator))
		if (!token.empty())
			result.push_back(token);
	return (result);
}

const std::string Bot::strToLower(const std::string &s)
{
	std::string	result = s;
	for (size_t i = 0; i < result.size(); ++i)
	{
		if (result[i] == '[')
			result[i] = '{';
		else if (result[i] == ']')
			result[i] = '}';
		else if (result[i] == '\\')
			result[i] = '|';
		else
			result[i] = std::tolower(result[i]);
	}
	return result;
}

/*	Handles incoming PRIVMSG commands from IRC users or channels.
	Automatically deduces reply target (channel or private message).
	Parses bot commands (that start with !) and executes the relevant actions:
	- !time: returns current timestamp
	- !roll: Rolls a random number between 0 and 100
	- !hangman: Manages hangman game
*/
void	Bot::handlePrivmsg(const std::vector<std::string> params, const std::string& prefix)
{
	if (params.size() < 2)
		return ;

	const std::string trailing = params[1];
	if (trailing.size() <= 1 || trailing[0] != '!')
		return;

	std::string target = params[0];
	bool isChannel = !target.empty() && target[0] == '#';

	std::string replyTarget = (!isChannel && target == _nickname) ? prefix : target;

	auto tokens = separateBy(trailing, ' ');
	if (tokens.empty())
		return;

	const std::string& botCommand = tokens[0];
	const std::set<std::string> allowedCommands = {
		"!help", "!time", "!roll", "!hangman"
	};
	if (allowedCommands.find(botCommand) == allowedCommands.end())
	{
		addToOutputBuffer("PRIVMSG " + replyTarget + " :Unknown bot command. Use !help to list commands.");
		return;
	}
	if (botCommand == "!help")
	{
		for (const auto& line : getHelpMessage())
			addToOutputBuffer("PRIVMSG " + replyTarget + " :" + line);
		return;
	}
	if (botCommand == "!time")
	{
		time_t now = time(0);
		char buf[80];
		strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
		std::string timeMsg = "Current time is " + std::string(buf);
		addToOutputBuffer("PRIVMSG " + replyTarget + " :" + timeMsg );
		return;
	}
	if (botCommand == "!roll")
	{
		int roll = std::rand() % 101;
		std::string rollMsg = "You rolled: " + std::to_string(roll);
		addToOutputBuffer("PRIVMSG " + replyTarget + " :" + rollMsg);
		return;
	}
	if (botCommand == "!hangman")
	{
		handleHangmanCommand(tokens, target, prefix, isChannel);
		return;
	}
}

void	Bot::handleHangmanCommand(const std::vector<std::string>& tokens, const std::string& target,
							const std::string& prefix, bool isChannel)
{
	std::string gameId = isChannel ? target : prefix;

	if (tokens.size() == 1)
	{
		startGame(gameId, isChannel);
		return;
	}
	const std::set<std::string> allowedGameCommands = {
		"guess", "status", "restart", "end"
	};

	const std::string& gameCommand = tokens[1];
	if (allowedGameCommands.find(gameCommand) == allowedGameCommands.end())
		{
		std::string commandMsg = "Unknown !hangman game command. Use !help to list commands.";
		addToOutputBuffer("PRIVMSG " + gameId + " :" + commandMsg);
		return;
	}
	if (gameCommand == "guess")
	{
		if (tokens.size() >= 3 && tokens[2].size() == 1 && std::isalpha(tokens[2][0]))
		{
			char letter = std::tolower(tokens[2][0]);
			handleGuess(gameId, letter, isChannel);
		}
		else
		{
			std::string usageMsg = ": Usage: !hangman guess <one letter>";
			addToOutputBuffer("PRIVMSG " + gameId + " :" + usageMsg);
		}
		return;
	}
	if (gameCommand == "status")
	{
		handleStatus(gameId, isChannel);
		return;
	}
	if (gameCommand == "restart")
	{
		restartGame(gameId, isChannel);
		return;
	}
	if (gameCommand == "end")
	{
		if (isChannel)
			channelGames.erase(gameId);
		else
			userGames.erase(gameId);

		addToOutputBuffer("PRIVMSG " + gameId + " :" + "Game ended.");
		return;
	}
}

//	If a game instance exists, retrieves it based on the gameId,
//	otherwise creates a new game instance.

BotGame& Bot::getGame(const std::string& gameId, bool isChannel)
{
	auto& games = isChannel ? channelGames : userGames;
	auto [it, _] = games.try_emplace(gameId, getRandomWord());
	return it->second;
}

void	Bot::startGame(const std::string& gameId, bool isChannel)
{
	auto& games = isChannel ? channelGames : userGames;
	auto it = games.find(gameId);
	if (it != games.end() && !it->second.getIsGameOver())
		games.erase(gameId);

	BotGame& game = getGame(gameId, isChannel);
	game.setLastGameActivity();
	addToOutputBuffer("PRIVMSG " + gameId + " :" + game.getStartMessage());
}

// Processes a letter sent as a guess for the hangman game
// Creates a new game automatically if none exists
// Handles the guess and cleans up finished games

void	Bot::handleGuess(const std::string& gameId, char letter, bool isChannel)
{
	auto& games = isChannel ? channelGames : userGames;
	bool isNewGame = games.find(gameId) == games.end();

	BotGame& game = getGame(gameId, isChannel);
	if (isNewGame)
		addToOutputBuffer("PRIVMSG " + gameId + " :" + game.getStartMessage());

	auto messages = game.guess(letter);
	for (const auto& message : messages)
		addToOutputBuffer("PRIVMSG " + gameId + " :" + message);

	if (game.getIsGameOver())
		games.erase(gameId);
}

void	Bot::handleStatus(const std::string& gameId, bool isChannel)
{
	BotGame& game = getGame(gameId, isChannel);
	std::string status = game.getGameStatus();
	addToOutputBuffer("PRIVMSG " + gameId + " :" + status);
}

void	Bot::restartGame(const std::string& gameId, bool isChannel)
{
	BotGame& game = getGame(gameId, isChannel);
	game.reset(getRandomWord());
	addToOutputBuffer("PRIVMSG " + gameId + " :Game restarted! " + game.getStartMessage());
}

