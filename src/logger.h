#ifndef LOGGER 
#define LOGGER 

#include <iostream>
#include <mutex>
#include <cstdarg>
class Logger {
public:
    
    enum class LogLevel { ERROR, WARNING, INFO, TRACE };

    static Logger::LogLevel logLevel;

    static void setLogLevel(LogLevel level);
    static void Error(const char* format, ...);
    static void WARNING(const char* format, ...);
    static void INFO(const char* format, ...);
    static void TRACE(const char* format, ...) ;
    static void log(LogLevel level, const char* format, va_list vargs);


private:
    static std::mutex mutex;
};


#endif