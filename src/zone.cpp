#include "zone.h"
#include "player.h"

using namespace std;

void Zone::createNewPlayer(string name)
{
    Logger::TRACE("void Zone::createNewPlayer(string name) %p", this);
    players[name] = new Player(name);
    players[name]->clientInterface = this->clientInterface;
}

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
        for ( auto e : entities)
        {
            while(e.second->getNextRespawnTime() <= now  && e.second->getNextRespawnTime() > 0)
            {
                e.second->respawn();
            }
            auto t = e.second->getNextRespawnTime();
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