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

using json = nlohmann::json;

using namespace std;

class Player;
class Entity;

class Zone
{   
    public:
    WebsocketInterface * clientInterface;
    string name;
    map<string, Entity*> entities;
    map<string, Player*> players;
    static long long lastServerUpdate;
    void respawnEntites();
    void playerActions();
    Player * getPlayer(string targetName);

    void createNewPlayer(string name);

    virtual string getZoneView();

    virtual json to_json()
    {
        Logger::TRACE(" virtual string Zone::packetify() %p", this);

        json j;
        j["name"] = name;
        json entityArray = json::array();
        for (auto e : entities)
        {
            entityArray.push_back(e.second->to_json());
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
        auto * tr = new Tree("tree1");
        auto * g = new Goblin("goblin1");
        entities[tr->name] = tr;
        entities[g->name] = g;
        t = thread(&Zone1::respawnEntites, this);
    }


};

#endif