#pragma once
#include "Server.hpp"

class Client;

class Channel
{
	private:
		const std::string	_channelName;
		std::string			_topicName;
		std::string			_channelKey;
		size_t				_userLimit;
		bool				_inviteOnly;
		bool				_topicRestricted;
		bool				_noExternalMessages;

		std::vector<Client*>	_clientMembers;
		std::vector<Client*>	_operators;
		std::vector<Client*>	_invited;
	public:
		Channel(const std::string &name);
		Channel(const Channel &other) = delete;
		~Channel();

		void addClient(Client* client);
		bool removeClient(Client* client);
		bool hasClient(Client* client) const;

		void addOperator(Client* client);
		void removeOperator(Client* client);
		bool isOperator(Client* client) const;

		void setTopic(const std::string& topic);
		const std::string& getTopic() const;

		void invite(Client* client);
		void removeInvited(Client* client);
		bool isInvited(Client* client) const;

		void kick(Client* operatorClient, Client* target, const std::string& reason);
		void broadcast(Client& sender, const std::string& message, bool includeSender);

		//	Mode handlers
		bool setMode(char mode, bool enabled, const std::string& param = "");
		bool handleInvite(bool enabled);
		bool handleTopic(bool enabled);
		bool handleKey(const std::string &channelKey, bool enabled);
		bool handleOp(const std::string &nickname, bool enabled);
		bool handleLimit(const std::string &limit, bool enabled);
		bool handleExternal(bool enabled);

		//getters methods
		std::string getClientsOnChannel() const;
		std::string getModes() const;
		std::string getModeParams() const;
		const std::string& getName() const;
		size_t getUserCount() const;
		Client  *getMemberByName(const std::string &name);
		bool isInviteOnly() const;
		bool isTopicRestricted() const;
		bool isLimited() const;
		bool noExternalMessages() const;
		size_t getUserLimit() const;
		const std::string& getPassword() const;
		bool isEmpty() const;
		bool hasOperators() const;
};

std::ostream& operator<<(std::ostream& os, Channel &channel);
