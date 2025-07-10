#include "Logger.hpp"

// Initializes a logger instance with a filename and logging enabled/disabled flag

Logger::Logger(const std::string& filename, bool logEnabled) : _logEnabled(logEnabled)
{
	if (_logEnabled)
	{
		_logFile.open(filename, std::ios::app);  // Open log file in append mode
		if (!_logFile.is_open())
			throw std::runtime_error("Failed to open log file: " + filename);
	}
}

Logger::~Logger()
{
	if (_logFile.is_open())
		_logFile.close();
}

// Enables or disables logging at runtime

void	Logger::enableLog(bool value)
{
	_logEnabled = value;
}

bool	Logger::isLogEnabled() const
{
	return _logEnabled;
}

// Logs a received message with the timestamp

void	Logger::logReceived(const std::string& message)
{
	if (!_logEnabled || !_logFile.is_open())
		return;
	_logFile << getTimestamp() << " << " << message << std::endl;
}

// Logs a sent message with the timestamp

void	Logger::logSent(const std::string& message)
{
	if (!_logEnabled || !_logFile.is_open())
		return;
	_logFile << getTimestamp() << " >> " << message << std::endl;
}

// Generates a formatted timestamp string (precision up to milliseconds)

std::string	Logger::getTimestamp() const
{
	auto now = std::chrono::system_clock::now();
	auto timeT = std::chrono::system_clock::to_time_t(now);
	std::tm tm = *std::localtime(&timeT);

	int millis = static_cast<int>(
		std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count() % 1000
	);

	// Format timestamp: YYYY-MM-DD HH:MM:SS.mmm
	std::ostringstream oss;
	oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S")
		<< "." << std::setw(3) << std::setfill('0') << millis;
	return oss.str();
}
