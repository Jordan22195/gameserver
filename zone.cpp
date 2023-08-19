#include "zone.h"
#include "player.h"


void Zone::respawnEntites()
{
    while(true)
    {
        auto now = chrono::duration_cast< chrono::milliseconds >(chrono::system_clock::now().time_since_epoch()).count();
        long long soonestRespawnTime = numeric_limits<long long>::max();
        for ( Entity *e : entities)
        {
            while(e->getNextRespawnTime() <= now  && e->getNextRespawnTime() > 0)
            {
                e->respawn();
            }
            auto t = e->getNextRespawnTime();
            if(t > now && t < soonestRespawnTime )
            {
                soonestRespawnTime = t;
            }
        }
        auto waitTime = soonestRespawnTime - now;
        if (waitTime > 1000) 
        {
            std::this_thread::sleep_for(std::chrono::milliseconds((1000)));
        }
        else if ( waitTime > 100)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds((100)));
        }
        else if (waitTime > 10)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds((10)));
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::milliseconds((1)));
        }
    }
}

void Zone::playerActions()
{
    
}