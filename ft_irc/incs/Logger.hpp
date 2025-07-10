#pragma once

#include <fstream>
#include <string>
#include <chrono>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <ctime>

class Logger
{
	private:
		std::ofstream	_logFile;
		bool			_logEnabled;

	public:

		Logger(const std::string& filename, bool logEnabled);
		~Logger();
		
		void		enableLog(bool value);
		void		logReceived(const std::string& message);
		void		logSent(const std::string& message);
		bool		isLogEnabled() const;
		std::string	getTimestamp() const;
};