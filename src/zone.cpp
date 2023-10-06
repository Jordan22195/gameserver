#include "zone.h"
#include "player.h"

using namespace std;


void Zone::explore()
{
    Logger::TRACE("Zone::explore()");
    //roll for entityID
    auto ids = entitySpawnTable.roll();
    for ( rollResult rr : ids)
    {
        if(entities.count(rr.id) == 0)
        {
            entities[rr.id] = rr.count;
        }
        else
        {
            entities[rr.id] += rr.count;
        }
    }
    // add id to spawns list
}

void Zone::playerActions()
{
    for (auto const& p : players)
    {
        p.second->update(); // string's value 
    }
}