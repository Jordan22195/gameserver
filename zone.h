#ifndef ZONE
#define ZONE

#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <chrono>
#include <thread>

#include "entity.h"
#include "combatEntity.h"
#include "resourceEntity.h"

using namespace std;

class Player;
class Entity;

class Zone
{   
    public:
    vector<Entity*> entities;
    vector<Player*> players;
    static long long lastServerUpdate;
    void respawnEntites();
    void playerActions();

};



class Zone1 : public Zone{
    public:


    thread t;
    Zone1()
    {
        printf("zone created\n");
        entities.push_back(new Tree(5));
        entities.push_back(new Goblin(5));
        t = thread(&Zone1::respawnEntites, this);
    }


};

#endif