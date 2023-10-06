#ifndef TIMEKEEPING
#define TIMEKEEPING

#include <chrono>

using namespace std;
class TimeKeeping
{
    
    public:
    inline static long long lastServerTime;

    static void updateServerTime()
    {
        // Get the current time point
    auto currentTime = std::chrono::system_clock::now();

    // Convert the time point to milliseconds
    auto currentTimeMs = std::chrono::time_point_cast<std::chrono::milliseconds>(currentTime);

    // Extract the time in milliseconds
    long long ms = currentTimeMs.time_since_epoch().count();

    TimeKeeping::lastServerTime = ms;

    
    }
};

#endif