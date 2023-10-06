#include "zone.h"
#include "player.h"

using namespace std;


void Zone::explore()
{
    //roll for entityID
    auto ids = entitySpawnTable.roll();
    // add id to spawns list
}

void Zone::playerActions()
{
    for (auto const& p : players)
    {
        p.second->update(); // string's value 
    }
}