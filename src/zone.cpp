#include "zone.h"
#include "player.h"
#include "entityFactory.h"

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
json Zone::to_json()
    {
        Logger::TRACE(" virtual string Zone::packetify() %p", this);

        json j;
        j["name"] = name;
        json entityArray = json::array();
        for (auto e : entities)
        {
            json entEntry;
            entEntry["id"]=e.first;
            entEntry["name"]=EntityFactory::getEntityNameFromId((entityIdEnum)e.first);
            entEntry["count"]=e.second;
            entityArray.push_back(entEntry);
        }
        j["entities"] = entityArray;

        return j;
       
    }


    Zone1::Zone1()
    {
        printf("zone created\n");
        name = "Tutorial Island";
        entitySpawnTable.addEntry((int)entityIdEnum::COMBAT_GOBLIN_NORMAL_1, .5, 1);
        entitySpawnTable.addEntry((int)entityIdEnum::WOODCUTTING_OAK, .5, 1);
    }