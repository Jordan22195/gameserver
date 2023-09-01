#include "zone.h"
#include "player.h"
#include "logger.h"

using namespace std;

Player * Zone::getPlayer(string targetName)
{
    Logger::TRACE("Player * Zone::getPlayer(string targetName) %p", this);
    if (players.count(targetName)!=0)
        return players[targetName];
    else
        return nullptr;
}


string Zone::getZoneView()
{
    cout << "ENTITIES" << endl;
    for (int i = 0; i < entities.size(); i++)
    {
        cout << i << " ";
        entities[i]->getStatus();
        cout << endl;
    }
    
    cout << endl;


    cout << "PLAYERS" << endl;

    for (auto const& p : players)
    {
        p.second->getStatus(); // string's value 
        cout << endl;
    }


}

void Zone::respawnEntites()
{
    while(true)
    {
        auto now = chrono::duration_cast< chrono::milliseconds >(chrono::system_clock::now().time_since_epoch()).count();
        TimeKeeping::lastServerTime = now;
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

        playerActions();
        std::this_thread::sleep_for(std::chrono::milliseconds((200)));
    }
}

void Zone::playerActions()
{
    for (auto const& p : players)
    {
        p.second->update(); // string's value 
    }
}