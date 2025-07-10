#pragma once

#include "CommandParser.hpp"
#include "Bot/BotConfig.hpp"
#include "Logger.hpp"
#include "Bot/BotGame.hpp"
#include "Bot/BotWordList.hpp"
#include "terminal_colors.h"
#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <signal.h>
#include <chrono>
#include <iostream>
#include <vector>
#include <map>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <poll.h>
#include <netdb.h>
#include <fcntl.h>

enum BotState {
	RUNNING = 0,
	SET_FOR_DISCONNECT = 1,
	QUIT = 2
};

class Bot {
	private:
		static volatile sig_atomic_t	_signalReceived;

		BotState					_state;
		const std::string			_password;
		pollfd						_pollFd;
		int							_fd;
		std::unordered_set<std::string>	_channelsJoined;
		std::string					_outputBuffer;
		std::string					_inputBuffer;
		std::string					_nickname;

		std::unordered_map<std::string, std::function<void(const std::vector<std::string>&, const std::string&)>> commandHandlers;
		std::chrono::steady_clock::time_point	_quitTime;
		Logger*									_logger = nullptr;

		std::unordered_map<std::string, BotGame> channelGames;
		std::unordered_map<std::string, BotGame> userGames;

		static void	signalHandler(int sig);
		void		setupSocket(const std::string &ipAddress, int serverPort);
		void		handleIncomingData();
		void		handleOutgoingData();
		void		cleanInactiveGames();
		bool		isBotNickname(const std::string &prefix);

		bool		checkForTimeout();
		void		setDisconnect();
		void		setAuthentication();
		void		addToInputBuffer(const std::string &toAppend);
		void		addToOutputBuffer(const std::string &toAppend);
		bool		hasCompleteMessage() const;

		void	clearInputBuffer();
		bool	findLineTerminator(std::string term, std::string &message);
		const	std::string	extractMessage();
		void	initializeCommandHandlers();
		void	parseAndExecute(const std::string &message);

		// Command handlers
		void	handleKick(const std::vector<std::string> &params);
		void	handlePing(const std::vector<std::string> &params);
		void	handleNamesReply(const std::vector<std::string> &params);
		void	handleInvite(const std::vector<std::string> &params, const std::string &prefix);
		void	handlePart(const std::vector<std::string> &params, const std::string &prefix);
		void	handleQuit();
		void	handleJoin(const std::vector<std::string> &params, const std::string &prefix);
		void	handleWelcome(const std::vector<std::string> &params);
		void	handlePrivmsg(const std::vector<std::string> params, const std::string& prefix);
		void	handleHangmanCommand(const std::vector<std::string>& tokens, const std::string& target,
							const std::string& prefix, bool isChannel);
		void	joinDefaultChannels();

		const std::string extractNickname(const std::string &prefix);
		bool	botOnChannel(const std::string &channel);
		void	addToChannelList(const std::string &channelJoined);
		void	removeFromChannelList(const std::string &channelParted);
		const std::string strToLower(const std::string &s);

		BotGame&	getGame(const std::string& gameId, bool isChannel);
		void		startGame(const std::string& gameId, bool isChannel);
		void		handleGuess(const std::string& gameId, char letter, bool isChannel);
		void		handleStatus(const std::string& gameId, bool isChannel);
		void		restartGame(const std::string& gameId, bool isChannel);
	public:
		Bot();
		Bot(const std::string &ipAddress, int serverPort, const std::string &password);
		~Bot();
		Bot(const Bot &src) = delete;
		Bot& operator=(const Bot &src) = delete;
		void		setLogger(Logger* logger);
		void		run();
};
