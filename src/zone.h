#ifndef ZONE
#define ZONE

#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <chrono>
#include <thread>
#include <string>
#include <sstream>

#include "entity.h"
#include "combatEntity.h"
#include "resourceEntity.h"
#include "logger.h"
#include "websocketInterface.h"
#include "json.hpp"
#include "dropTable.h"
#include "entityFactory.h"

using json = nlohmann::json;

using namespace std;

class Player;
class Entity;

class Zone
{   
    public:
    WebsocketInterface * clientInterface;
    string name;

    //unique id, count
    map<string, int> entities;
    dropTable entitySpawnTable;
    map<string, Player*> players;
    static long long lastServerUpdate;
    void respawnEntites();
    void playerActions();
    Player * getPlayer(string targetName);

    void createNewPlayer(string name);

    void explore();

    virtual json to_json()
    {
        Logger::TRACE(" virtual string Zone::packetify() %p", this);

        json j;
        j["name"] = name;
        json entityArray = json::array();
        for (auto e : entities)
        {
            json entEntry;
            entEntry["id"]=e.first;
            entEntry["count"]=e.second;
            entityArray.push_back(entEntry);
        }
        j["entities"] = entityArray;

        return j;
       
    }
    

};



class Zone1 : public Zone{
    public:


    thread t;
    Zone1()
    {
        printf("zone created\n");
        name = "Tutorial Island";
        entitySpawnTable.addEntry(COMBAT_GOBLIN_NORMAL_1, .5, 1);
    }


};

#endif