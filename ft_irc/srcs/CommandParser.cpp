#include "CommandParser.hpp"

CommandParser::CommandParser(const std::string& rawMessage) : _rawMessage(rawMessage) {}

CommandParser::~CommandParser() {}

// Removes trailing newline or '\r'

std::string_view CommandParser::removeNewlines(std::string_view input)
{
	while (!input.empty() && (input.back() == '\n' || input.back() == '\r'))
	{
		input.remove_suffix(1);
	}
	return input;
}

// Extracts the prefix before the first space and then modifies input to exclude it
std::string CommandParser::extractPrefix(std::string_view& input)
{
	if (input.empty() || input.front() != ':')
		return "";
	input.remove_prefix(1);

	size_t space_pos = input.find(' ');
	if (space_pos == std::string_view::npos)
	{
		std::string prefix = std::string(input);
		input = std::string_view();
		return prefix;
	}
	std::string prefix = std::string(input.substr(0, space_pos));
	input.remove_prefix(space_pos + 1);
	return prefix;
}

// Extracts the command before the first space,
// converts the command to uppercase
// and then modifies input to exclude it
std::string CommandParser::extractCommand(std::string_view& input)
{
	size_t space_pos = input.find(' ');
	std::string cmd;

	if (space_pos == std::string_view::npos)
	{
		cmd = std::string(input);
		input = std::string_view(); 
	}
	else
	{
		cmd = std::string(input.substr(0, space_pos));
		input.remove_prefix(space_pos + 1);
	}
	for (char& c : cmd)
		c = std::toupper(static_cast<unsigned char>(c));
	return cmd;
}

void CommandParser::skipLeadingSpaces(std::string_view& input)
{
	while (!input.empty() && input.front() == ' ')
	{
		input.remove_prefix(1);
	}
}

// Extracts parameters.
// Splits by space, unless there is a colon in front of the last parameter

std::vector<std::string> CommandParser::extractParams(std::string_view input)
{
	std::vector<std::string> params;

	skipLeadingSpaces(input);
	while (!input.empty())
	{
		if (input.front() == ':')
		{
			input.remove_prefix(1);
			params.push_back(std::string(input));
			break;
		}
		size_t space_pos = input.find(' ');
		if (space_pos == std::string_view::npos)
		{
			params.push_back(std::string(input));
			break;
		}
		params.push_back(std::string(input.substr(0, space_pos)));
		input.remove_prefix(space_pos + 1);
		skipLeadingSpaces(input);
	}
	return params;
}

// Parses the raw message into a ParsedCommand struct

ParsedCommand CommandParser::parseMessage(const std::string& rawMessage)
{
	ParsedCommand result;

	std::string_view view = removeNewlines(rawMessage);
	if (view.empty())
		return result;
	result.prefix = extractPrefix(view);
	result.command = extractCommand(view);
	result.params = extractParams(view);
	return result;
}

