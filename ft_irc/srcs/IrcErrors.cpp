#include "IrcErrors.hpp"

std::string getErrorMessage(int code)
{
	static const std::unordered_map<int, std::string> errorMessages =
	{
		{401, ":No such nick/channel"},
		{402, ":No such server"},
		{403, ":No such channel"},
		{404, ":Cannot send to channel"},
		{405, ":You have joined too many channels"},
		{407, "Too many targets"},
		{411, ":No recipient given (PRIVMSG)"},
		{412, ":No text to send"},
		{417, ":Input line was too long"},
		{421, ":Unknown command"},
		{422, ":MOTD File is missing"},
		{431, ":No nickname given"},
		{432, ":Erroneous nickname"},
		{433, ":Nickname is already in use"},
		{441, ":They aren't on that channel"},
		{442, ":You're not on that channel"},
		{443, ":is already on channel"},
		{445, ":SUMMON has been disabled"},
		{446, ":USERS has been disabled"},
		{451, ":You have not registered"},
		{461, ":Not enough parameters"},
		{462, ":You may not reregister"},
		{464, ":Password incorrect"},
		{471, ":Cannot join channel (+l)"},
		{472, ":is unknown mode char to me"},
		{473, ":Cannot join channel (+i)"},
		{475, ":Cannot join channel (+k)"},
		{476, ":Bad Channel Mask"},
		{482, ":You're not a channel operator"},
		{525, ":Key is not well-formed"}
	};

	auto it = errorMessages.find(static_cast<int>(code));
	if (it != errorMessages.end())
		return it->second;
	else
		return "Unknown error code";
}
