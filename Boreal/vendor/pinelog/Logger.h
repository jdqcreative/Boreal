#pragma once

#include <iostream>
#include <fstream>
#include <mutex>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <stdio.h>
#include <format>

namespace Pinelog {

	enum class LogLevel { DEBUG, INFO, WARN, ERR };

	class Logger {
	public:
		Logger(LogLevel level = LogLevel::INFO, const std::string& loggerName = "LOG", const std::string & filename = "");

		~Logger();

		void setLogLevel(LogLevel level);
		void setDisplayLevel(bool isLevelDisplayed);
		inline void setLoggerName(const std::string& name) { m_LoggerName = name; }
		void log(LogLevel level, const std::string& message);
		void logToFile(const std::string& filename);

		template <typename... Args>
		void logf(LogLevel level, const std::string& format, Args... args);

		//void debug(const std::string& message) { log(LogLevel::DEBUG, message); }
		//void info(const std::string& message) { log(LogLevel::INFO, message); }
		//void warn(const std::string& message) { log(LogLevel::WARN, message); }
		//void error(const std::string& message) { log(LogLevel::ERR, message); }

		// Template functions for formatting logs with values
		template<typename... Args>
		void debug(std::format_string<Args...> fmt, Args&&... args)
		{
			log(LogLevel::DEBUG, std::format(fmt, std::forward<Args>(args)...));
		}

		template<typename... Args>
		void info(std::format_string<Args...> fmt, Args&&... args)
		{
			log(LogLevel::INFO, std::format(fmt, std::forward<Args>(args)...));
		}

		template<typename... Args>
		void warn(std::format_string<Args...> fmt, Args&&... args)
		{
			log(LogLevel::WARN, std::format(fmt, std::forward<Args>(args)...));
		}

		template<typename... Args>
		void error(std::format_string<Args...> fmt, Args&&... args)
		{
			log(LogLevel::ERR, std::format(fmt, std::forward<Args>(args)...));
		}

	private:
		std::string m_LoggerName;
		LogLevel currentLevel = LogLevel::DEBUG;
		std::ofstream logFile;
		std::mutex logMutex;
		bool levelDisplayed = false;

		std::string getTimestamp();
		std::string levelToString(LogLevel level);
	};

}