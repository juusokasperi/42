#include "Server.hpp"
#include "Client.hpp"
#include "CommandParser.hpp"
#include "Logger.hpp"

static int validatePort(std::string portStr)
{
	try {
		if (portStr.empty())
			throw std::runtime_error("");
		for (size_t i = 0; i < portStr.length(); ++i)
			if (!std::isdigit(portStr[i]))
				throw std::runtime_error("");
		int port = std::stoi(portStr);
		if (port < 0 || port > 65535)
			throw std::runtime_error("");
		return port;
	} catch (const std::exception &e) {
		throw std::runtime_error("Invalid port (0-65535).");
	}
}

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cerr << "Usage: " << argv[0] << " <port> <password>\n";
		return (1);
	}
	try {
		int port = validatePort(argv[1]);
		std::string password = argv[2];
		Logger logger("server_log", true);
		Server server(port, password);
		server.setLogger(&logger);
		server.run();
	} catch (const std::exception &e) {
		std::cerr << "Error: " << e.what() << "\n";
		return (1);
	}
	return (0);
}
