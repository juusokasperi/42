#pragma once

#include "Config.hpp"
#include <poll.h>
#include <unistd.h>
#include <chrono>
#include <iostream>
#include "Channel.hpp"

class Channel;

class Client {
	private:
		pollfd									_pollFd;
		std::string								_ipAddress;
		bool									_hasReceivedWelcome;
		std::chrono::steady_clock::time_point	_lastActivity;
		std::chrono::steady_clock::time_point	_lastPingTime;

		bool									_correctPassword;
		std::string								_nickname;
		std::string								_username;
		std::string								_realname;
		bool									_awaitingPong;
		std::string								_inputBuffer;
		std::string								_outputBuffer;
		std::string								_quitMsg;
		std::chrono::steady_clock::time_point	_quitTime;

	public:
		Client(int fd, const std::string &ipAddress);
		Client();
		~Client();
		Client(Client &&other) noexcept;
		Client& operator=(Client &&other) noexcept;
		Client(Client &src) = delete;
		Client& operator=(Client &rhs) = delete;

		// Getters:
		int					getFd() const;
		pollfd&				getPollFd();
		int					getPongWaitTime() const;
		int					getIdleSeconds() const;
		const std::string&	getInputBuffer() const;
		std::string&		getOutputBuffer();
		const std::string&	getUsername() const;
		const std::string&	getRealname() const;
		const std::string&	getNickname() const;
		const std::string	getHostMask() const;
		const std::string&	getIpAddress() const;
		const std::string&	getQuitMsg() const;
		bool				isAwaitingPong() const;
		bool				isRegistered() const;
		bool				hasReceivedWelcome() const;
		bool				hasEnteredPassword() const;
		bool				getDisconnect() const;
		std::chrono::steady_clock::time_point	getDisconnectTime() const;

		// Setters:
		void			setWelcomeReceived();
		void			setPingState(bool awaiting);
		void			setNickname(const std::string &nick);
		void			setUserInfo(const std::string &username, const std::string &realname);
		void			updateActivity();
		void			setCorrectPassword();
		void			setDisconnect(const std::string &quitMsg);
		void			clearInputBuffer();
		void			clearOutputBuffer();

		// Message handling:
		void			addToInputBuffer(std::string toAppend);
		void			addToOutputBuffer(std::string toAppend);
		bool			hasCompleteMessage() const;
		std::string		extractMessage();
		bool			findLineTerminator(std::string term, std::string &message);
};
