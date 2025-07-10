#include "Bot/Bot.hpp"
#include "Logger.hpp"
#include <cstdlib>
#include <ctime>

static int validatePort(std::string portStr)
{
	try {
		if (portStr.empty())
			throw std::runtime_error("");
		for (size_t i = 0; i < portStr.length(); ++i)
			if (!std::isdigit(portStr[i]))
				throw std::runtime_error("");
		int port = std::stoi(portStr);
		if (port < 1 || port > 65535)
			throw std::runtime_error("");
		return port;
	} catch (const std::exception &e) {
		throw std::runtime_error("Invalid port (1-65535).");
	}
}

int main(int argc, char **argv)
{
	if (argc < 3 || argc > 4)
	{
		std::cerr << "Usage: " << argv[0] << " <ip> <port> <password>\n";
		return (1);
	}
	try {
		int port = validatePort(argv[2]);
		std::string password = (argc == 4) ? argv[3] : "";
		Logger logger("bot_log", true);
		Bot bot(argv[1], port, password);
		bot.setLogger(&logger);
		std::srand(static_cast<unsigned int>(std::time(nullptr)));
		bot.run();
	} catch (const std::exception &e) {
		std::cerr << "Error: " << e.what() << "\n";
		return (1);
	}
	return (0);
}
