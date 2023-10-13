#ifndef TIMEKEEPING
#define TIMEKEEPING

#include <chrono>
#include <mutex>

using namespace std;
class TimeKeeping
{
    public:

    static unsigned long long getServerTime()
    {   
        TimeKeeping::mtx.lock();
        return tickCounter;
    }
    
    private:
    inline static mutex mtx;
    inline static const int TIME_PER_TICK_ms = 100;
    inline static unsigned long long tickCounter;
    inline static thread updateThread;

    static void update()
    {
        while(true)
        {
            TimeKeeping::updateServerTime();
            std::this_thread::sleep_for(std::chrono::milliseconds((TIME_PER_TICK_ms)));

        }
    }

    static void startUpdateThread()
    {
        updateThread = thread();

    }
    inline static long long lastServerTime;

    static void updateServerTime()
    {
        TimeKeeping::mtx.lock();
        // Get the current time point
        auto currentTime = std::chrono::system_clock::now();

        // Convert the time point to milliseconds
        auto currentTimeMs = std::chrono::time_point_cast<std::chrono::milliseconds>(currentTime);

        // Extract the time in milliseconds
        long long ms = currentTimeMs.time_since_epoch().count();

        TimeKeeping::lastServerTime = ms;
        tickCounter++;

    
    }
};

#endif