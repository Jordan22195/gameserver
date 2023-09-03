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

    virtual string packetify()
    {
        Logger::TRACE(" virtual string Zone::packetify() %p", this);
        stringstream ss;

        ss << "ZONE" << endl << this->name << endl;
        ss << "ENTITIES" << endl;
        ss << entities.size() << endl;
        for (auto e : entities)
        {
            ss << e.second->packetify();
        }

        cout << "zone packet" << endl << ss.str() << endl;
        return ss.str();
       
    }
    

};



class Zone1 : public Zone{
    public:


    thread t;
    Zone1()
    {
        printf("zone created\n");
        name = "Tutorial Island";
        auto * tr = new Tree(5);
        auto * g = new Goblin(5);
        entities[tr->name] = tr;
        entities[g->name] = g;
        t = thread(&Zone1::respawnEntites, this);
    }


};

#endif