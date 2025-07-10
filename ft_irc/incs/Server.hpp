#pragma once

#include "Config.hpp"
#include <time.h>
#include <signal.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>
#include <memory>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <poll.h>
#include <fcntl.h>
#include <chrono>
#include <sstream>
#include <arpa/inet.h>
#include "terminal_colors.h"
#include "Client.hpp"
#include "CommandParser.hpp"
#include "Channel.hpp"
#include "IrcErrors.hpp"
#include "Logger.hpp"

class Channel;
class Client;


class	Server {
	private:
		static volatile sig_atomic_t			_shouldStop;
		std::string								_password;
		std::string								_serverCreated;
		int										_serverFd;
		pollfd									_serverPoll;

		std::unordered_map<std::string, Client*>	_nicknameMap;
		std::unordered_map<std::string, Channel*>	_channelMap;
		std::vector<std::unique_ptr<Client>>		_clients;
		std::vector<std::unique_ptr<Channel>>		_channels;

		std::chrono::steady_clock::time_point	_lastPingCheck;
		std::unordered_map<std::string, std::function<void(Client&, const std::vector<std::string>&)>> commandHandlers;
		Logger*									_logger = nullptr;

		void		setupServerSocket(int port);
		int			getServerPort() const;
		static void	signalHandler(int sig);
		void		acceptConnection();
		void		handleClientData(Client& client);
		void		handleClientOutput(Client& client);
		void		handleDisconnections();
		bool		checkClientTimeouts();

		// Authentication and nick handling
		int		validateNickname(const std::string& nick);
		void	handleWelcome(Client& client);
		void	sendPing(Client& client);
		void	handlePass(Client& client, const std::vector<std::string>& params);
		void	handleCap(Client& client, const std::vector<std::string>& params);
		void	handleNick(Client& client, const std::vector<std::string>& params);
		void	handleUser(Client& client, const std::vector<std::string>& params);
		void	handleWho(Client& client, const std::vector<std::string>& params);

		// Reply formats
		std::string formatNumReply(int code,
									std::string_view arg1 = {},
									std::string_view arg2 = {},
									std::string_view arg3 = {});
		std::string formatManualReply(int code,
									std::string_view arg1 = {},
									std::string_view arg2 = {},
									std::string_view arg3 = {},
									std::string_view arg4 = {});

		//	Utilities
		bool		validKeyFormat(const std::string& password);
		bool		validAuthentication(const std::string &cmd, Client& client);
		Channel		*getChannelByName(const std::string &channelName);
		Client		*getClientByNickname(const std::string &clientName);
		void		removeChannel(const std::string& channel);
		Channel		*getOrCreateChannel(const std::string &channelName, Client &client);
		Channel		*createChannel(const std::string &chanName, Client &client);
		void		partFromAllChannels(Client &client);
		void		sendToAllChannelsWithClient(Client &client, const std::string &message,
						bool includeSender, bool removeClient);
		std::vector<std::string>	separateBy(std::string toSeparate, char separator);
		const std::string strToLower(const std::string &s);

		//	Private message
		void		handlePrivmsg(Client& client, const std::vector<std::string>& params);
		bool		findAndBroadcastToChannel(Client &client, const std::string &recipient, const std::string &message);
		bool		findAndSendToClient(Client &client, const std::string &recipient, const std::string &message);
		bool		validatePrivmsg(Client &client, const std::vector<std::string>& params);
		bool		checkForHostname(Client &client, std::string &recipient);

		//	Join
		void		handleJoin(Client &client, const std::vector<std::string>& params);
		bool		channelJoinAllowed(Client &client, Channel* chan, const std::string &password);
		void		sendJoinMessages(Client &client, Channel *channel);
		size_t		countChannelsJoined(Client &client) const;
		bool		validateChannelName(Client &client, const std::string& channelName);

		//	Mode
		void	handleMode(Client &client, const std::vector<std::string>& params);
		void	handleModeQuery(Client &client, Channel *channel);
		bool	handleModeKey(bool enable, Client &client, Channel *channel, size_t &j,
					const std::vector<std::string> &params, std::string &modeParam);
		bool	handleModeOp(Client &client, Channel *channel, size_t &j,
					const std::vector<std::string> &params, std::string &modeParam);
		bool	handleModeLimit(bool enable, Client &client, size_t &j,
					const std::vector<std::string> &params, std::string &modeParam);
		bool	validateModes(Client &client, const std::string& modeString);
		void	handleUserMode(Client &client, const std::vector<std::string>&params);

		//	Topic
		void	handleTopic(Client &client, const std::vector<std::string>& params);
		void	handleTopicQuery(Client &client, Channel *channel);

		//	Other handlers
		void	handleInvite(Client &client, const std::vector<std::string>& params);
		void	handlePart(Client &client, const std::vector<std::string>& params);
		void	handleKick(Client &client, const std::vector<std::string>& params);
		void	handleQuit(Client &client, const std::vector<std::string>& params);
		void	handlePing(Client& client, const std::vector<std::string>& params);
		void	handlePong(Client& client, const std::vector<std::string>& params);
		void	handleSummon(Client& client);
		void	handleUsers(Client& client);
		void	handleMotd(Client& client);
		void	handleNames(Client &client, const std::vector<std::string>& params);

		//	Parsing, initializing
		void	initializeCommandHandlers();
		void	parseAndExecute(Client &client, std::string &message);
		void	handleParsedCommand(Client& client, const ParsedCommand& cmd);
	public:
		Server();
		Server(int port, std::string &password);
		~Server();
		Server(const Server &src) = delete;
		Server&	operator=(const Server &rhs) = delete;

		void	setLogger(Logger* logger);
		void	run();

		enum NumCode {
			RPL_WELCOME = 001,
			RPL_YOURHOST = 002,
			RPL_CREATED = 003,
			RPL_MYINFO = 004,
			RPL_ISUPPORT = 005,
			RPL_UMODEIS = 221,
			RPL_ENDOFWHO = 315,
			RPL_CHANNELMODEIS = 324,
			RPL_NOTOPIC = 331,
			RPL_TOPIC = 332,
			RPL_INVITING = 341,
			RPL_WHOREPLY = 352,
			RPL_NAMREPLY = 353,
			RPL_ENDOFNAMES = 366,
			RPL_MOTDSTART = 375,
			RPL_MOTD = 372,
			RPL_ENDOFMOTD = 376,
			ERR_NOSUCHNICK = 401,
			ERR_NOSUCHSERVER = 402,
			ERR_NOSUCHCHANNEL = 403,
			ERR_CANNOTSENDTOCHAN = 404,
			ERR_TOOMANYCHANNELS = 405,
			ERR_TOOMANYTARGETS = 407,
			ERR_NORECIPIENT = 411,
			ERR_NOTEXTTOSEND = 412,
			ERR_INPUTTOOLONG = 417,
			ERR_UNKNOWNCOMMAND = 421,
			ERR_NOMOTD = 422,
			ERR_NONICKNAMEGIVEN = 431,
			ERR_ERRONEOUSNICKNAME = 432,
			ERR_NICKNAMEINUSE = 433,
			ERR_USERNOTINCHANNEL = 441,
			ERR_NOTONCHANNEL = 442,
			ERR_USERONCHANNEL = 443,
			ERR_SUMMONDISABLED = 445,
			ERR_USERSDISABLED = 446,
			ERR_NOTREGISTERED = 451,
			ERR_NEEDMOREPARAMS = 461,
			ERR_ALREADYREGISTERED = 462,
			ERR_PASSWDMISMATCH = 464,
			ERR_CHANNELISFULL = 471,
			ERR_UNKNOWNMODE = 472,
			ERR_INVITEONLYCHAN = 473,
			ERR_BADCHANNELKEY = 475,
			ERR_BADCHANMASK = 476,
			ERR_CHANOPRIVSNEEDED = 482,
			ERR_UMODEUNKNOWNFLAG = 501,
			ERR_USERSDONTMATCH = 502,
			ERR_INVALIDKEY = 525
		};
};
