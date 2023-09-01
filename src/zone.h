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


using namespace std;

class Player;
class Entity;

class Zone
{   
    public:
    string name;
    vector<Entity*> entities;
    map<string, Player*> players;
    static long long lastServerUpdate;
    void respawnEntites();
    void playerActions();
    Player * getPlayer(string targetName);

    virtual string getZoneView();

    virtual string packetify()
    {
        Logger::TRACE(" virtual string Zone::packetify() %p", this);
        stringstream ss;

        ss << name;
        ss << entities.size() << endl;
        for (auto e : entities)
        {
            ss << e->packetify();
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
        entities.push_back(new Tree(5));
        entities.push_back(new Goblin(5));
        t = thread(&Zone1::respawnEntites, this);
    }


};

#endif