

#include "logger.h"

using namespace std;
std::mutex Logger::mutex;
Logger::LogLevel Logger::logLevel;



void Logger::setLogLevel(LogLevel level)
{
    Logger::logLevel = level;
}

void Logger::Error(const char* format, ...) {
                va_list varg;
        va_start(varg, format);
        Logger::log(LogLevel::ERROR, format, varg);
        va_end(varg);
}

void Logger::WARNING(const char* format, ...) {
               va_list varg;
        va_start(varg, format);
        Logger::log(LogLevel::WARNING, format, varg);
        va_end(varg);
}

void Logger::INFO(const char* format, ...) {
               va_list varg;
        va_start(varg, format);
        Logger::log(LogLevel::INFO, format, varg);
        va_end(varg);
}

void Logger::TRACE(const char* format, ...) {
        va_list varg;
        va_start(varg, format);

        Logger::log(LogLevel::TRACE, format, varg);
        va_end(varg);
}

void Logger::log(LogLevel level, const char* format, va_list varg) {
    std::lock_guard<std::mutex> lock(mutex);



    switch (level) {
        case LogLevel::ERROR:
            std::cout << "[ERROR] ";
            break;
        case LogLevel::WARNING:
            std::cout << "[WARNING] ";
            break;
        case LogLevel::INFO:
            std::cout << "[INFO] ";
            break;
        case LogLevel::TRACE:
            std::cout << "[TRACE] ";
            break;
    }

        vprintf(format, varg);
    std::cout << std::endl;

}