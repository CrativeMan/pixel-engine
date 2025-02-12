#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <cstdarg>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <sstream>

#define LOG_TRACE(fmt, ...)                                                    \
  Logger::getInstance().log(__FILE_NAME__, __LINE__, LogLevel::TRACE, fmt,     \
                            ##__VA_ARGS__)
#define LOG_DEBUG(fmt, ...)                                                    \
  Logger::getInstance().log(__FILE_NAME__, __LINE__, LogLevel::DEBUG_LEVEL,    \
                            fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...)                                                     \
  Logger::getInstance().log(__FILE_NAME__, __LINE__, LogLevel::INFO, fmt,      \
                            ##__VA_ARGS__)
#define LOG_WARN(fmt, ...)                                                     \
  Logger::getInstance().log(__FILE_NAME__, __LINE__, LogLevel::WARN, fmt,      \
                            ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...)                                                    \
  Logger::getInstance().log(__FILE_NAME__, __LINE__, LogLevel::ERROR, fmt,     \
                            ##__VA_ARGS__)
#define LOG_CRITICAL(fmt, ...)                                                 \
  Logger::getInstance().log(__FILE_NAME__, __LINE__, LogLevel::CRITICAL, fmt,  \
                            ##__VA_ARGS__)

enum class LogLevel { TRACE, DEBUG_LEVEL, INFO, WARN, ERROR, CRITICAL };

class Logger {
public:
  static Logger &getInstance() {
    static Logger instance;
    return instance;
  }

  void setLogLevel(LogLevel level) { logLevel = level; }

  void log(const char *file, int line, LogLevel level, const char *format,
           ...) {
    if (level < logLevel)
      return;

    std::lock_guard<std::mutex> lock(logMutex);

    va_list args;
    va_start(args, format);
    std::string message = formatString(format, args);
    va_end(args);

    std::string formattedMessage = formatLogMessage(level, message, file, line);

    std::cout << getColor(level) << formattedMessage << "\033[0m" << std::endl;
    if (fileStream.is_open()) {
      fileStream << formattedMessage << std::endl;
    }
  }

  void setLogFile(const std::string &filename) {
    std::lock_guard<std::mutex> lock(logMutex);
    fileStream.open(filename, std::ios::app);
  }

  static void setLoggerLevel(int argc, char **argv) {
    if (argc > 1) {
      if (!strcmp(argv[1], "debug")) {
        Logger::getInstance().setLogLevel(LogLevel::DEBUG_LEVEL);
      } else if (!strcmp(argv[1], "trace")) {
        Logger::getInstance().setLogLevel(LogLevel::TRACE);
      }
    } else {
      Logger::getInstance().setLogLevel(LogLevel::INFO);
    }
  }

  static void testLogger() {
    LOG_TRACE("Testing testing");
    LOG_DEBUG("Testing testing");
    LOG_INFO("Testing testing");
    LOG_WARN("Testing testing");
    LOG_ERROR("Testing testing");
    LOG_CRITICAL("Testing testing");
  }

private:
  LogLevel logLevel = LogLevel::INFO;
  std::ofstream fileStream;
  std::mutex logMutex;

  Logger() {} // Private constructor
  ~Logger() {
    if (fileStream.is_open()) {
      fileStream.close();
    }
  }

  std::string formatString(const char *format, va_list args) {
    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), format, args);
    return std::string(buffer);
  }

  std::string formatLogMessage(LogLevel level, const std::string &message,
                               const char *file, int line) {
    std::ostringstream oss;
    oss << "[" << currentDateTime() << "] [" << logLevelToString(level) << "] ";
#ifdef DEBUG
    oss << "[" << file << "|" << line << "] ";
#else
    (void)file;
    (void)line;
#endif // DEBUG
    oss << message;
    return oss.str();
  }

  std::string currentDateTime() {
    std::time_t now = std::time(nullptr);
    std::tm *localTime = std::localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(localTime, "%Y-%m-%d %H:%M:%S");
    return oss.str();
  }

  std::string logLevelToString(LogLevel level) {
    switch (level) {
    case LogLevel::TRACE:
      return "TRACE";
    case LogLevel::DEBUG_LEVEL:
      return "DEBUG";
    case LogLevel::INFO:
      return "INFO";
    case LogLevel::WARN:
      return "WARN";
    case LogLevel::ERROR:
      return "ERROR";
    case LogLevel::CRITICAL:
      return "CRITICAL";
    default:
      return "UNKNOWN";
    }
  }

  std::string getColor(LogLevel level) {
    switch (level) {
    case LogLevel::TRACE:
      return "\033[36m"; // Cyan
    case LogLevel::DEBUG_LEVEL:
      return "\033[90m"; // Gray
    case LogLevel::INFO:
      return "";
    case LogLevel::WARN:
      return "\033[33m"; // Yellow
    case LogLevel::ERROR:
      return "\033[31m"; // Red
    case LogLevel::CRITICAL:
      return "\033[35m"; // Magenta
    default:
      return "\033[0m";
    }
  }
};

#endif // LOGGER_HPP
