#pragma once

#include <iostream>
#include <vector>
#include <string_view>

struct ParsedCommand {
	std::string prefix;
	std::string command;
	std::vector<std::string> params;
};

class CommandParser {
	private:
		std::string _rawMessage;

	public:
		CommandParser() = delete;
		CommandParser(const std::string& rawMessage);
		~CommandParser();
		CommandParser(CommandParser& src) = delete;
		CommandParser& operator=(CommandParser &rhs) = delete;

		ParsedCommand parseMessage(const std::string& rawMessage);
		std::string_view removeNewlines(std::string_view input);
		void skipLeadingSpaces(std::string_view& input);
		std::string extractPrefix(std::string_view& input);
		std::string extractCommand(std::string_view& input);
		std::vector<std::string> extractParams(std::string_view input);
};
