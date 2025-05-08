#include "bopch.h"
#include "Logger.h"

namespace Pinelog {

	void setConsoleColor(LogLevel level)
	{
	#ifdef _WIN32
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			switch (level) {
			case LogLevel::DEBUG: SetConsoleTextAttribute(hConsole, 11); break; // Cyan
			case LogLevel::INFO: SetConsoleTextAttribute(hConsole, 10); break; // Green
			case LogLevel::WARN: SetConsoleTextAttribute(hConsole, 14); break; // Yellow
			case LogLevel::ERR: SetConsoleTextAttribute(hConsole, 12); break; // Red
			default: SetConsoleTextAttribute(hConsole, 15); // White (default)
			}
	#endif
	}

	// Constructor
	Logger::Logger(LogLevel level, const std::string& loggerName, const std::string& filename)
		: currentLevel(level), m_LoggerName(loggerName)
	{
		if (!filename.empty())
			logToFile(filename);
	}

	// Destructor
	Logger::~Logger()
	{
		if (logFile.is_open())
			logFile.close();
	}

	// Set log level dynamically
	void Logger::setLogLevel(LogLevel level)
	{
		std::lock_guard<std::mutex> lock(logMutex);
		currentLevel = level;
	}

	// Set wether to display log level in console (ex. WARNING, DEBUG etc.)
	void Logger::setDisplayLevel(bool isLevelDisplayed)
	{
		levelDisplayed = isLevelDisplayed;
	}

	// Log messages
	void Logger::log(LogLevel level, const std::string& message)
	{
		std::lock_guard<std::mutex> lock(logMutex);
		if (level < currentLevel) return;

		std::string logLevel = " ";
		if (levelDisplayed)
			logLevel = "[" + levelToString(level) + "] ";

		std::string logMessage = "[" + m_LoggerName + "][" + getTimestamp() + "]" + logLevel + message;

		#ifdef _WIN32
				setConsoleColor(level); // Apply color before printing
				std::cout << logMessage << std::endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // Reset to white
		#else
				std::cout << logMessage << std::endl; // Print to console
		#endif

		if (logFile.is_open())
			logFile << logMessage << std::endl; // Write to file
	}

	// Enable file logging
	void Logger::logToFile(const std::string& filename)
	{
		std::lock_guard<std::mutex> lock(logMutex);

		if (logFile.is_open()) logFile.close();

		logFile.open(filename, std::ios::app);
	}

	// Formatted logging (like printf)
	template<typename... Args>
	void Logger::logf(LogLevel level, const std::string& format, Args... args)
	{
		int size = std::snprintf(nullptr, 0, format.c_str(), args...) + 1;

		if (size <= 0) return;

		char buffer[size];
		std::snprintf(buffer, size, format.c_str(), args...);

		log(level, std::string(buffer));
	}

	// Convert log level to string
	std::string Logger::levelToString(LogLevel level)
	{
	#ifdef _WIN32
			switch (level) {
				case LogLevel::DEBUG: return "DEBUG";
				case LogLevel::INFO: return "INFO";
				case LogLevel::WARN: return "WARNING";
				case LogLevel::ERR: return "ERROR";
				default: return "UNKNOWN";
			}
	#else
			switch (level) {
				case LogLevel::DEBUG: "\033[36mDEBUG\033[0m"return;
				case LogLevel::INFO: "\033[32mINFO\033[0m"return;
				case LogLevel::WARN: "\033[33mWARNING\033[0m"return;
				case LogLevel::ERR: "\033[31mERROR\033[0m"return;
				default: return "UNKNOWN";
			}
	#endif
	}

	// Get timestamp
	std::string Logger::getTimestamp()
	{
		std::time_t now = std::time(nullptr);
		std::tm timeStruct;
		localtime_s(&timeStruct, &now);
		std::ostringstream oss;
		oss << std::put_time(&timeStruct, "%Y-%elements-%d %H:%M:%S");
		return oss.str();
	}
}