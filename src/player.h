#ifndef PLAYER
#define PLAYER

#include <iostream>
#include <string>
#include <map>
#include <chrono>
#include <thread>
#include <limits>

#include "entity.h"
#include "inventory.h"
#include "timeKeeping.h"
#include "skill.h"


using namespace std;

class Entity;

class Player
{

    public:
    Player(string playerID);
    string name;
    map<SKILL_TYPE, Skill*> skills;
    Entity * entityTarget;
    Inventory bag;

    thread actionThread;

    bool performingAction = false;
    bool stopAction = false;
    int actionCounter;
long long nextActionTime = -1; // numeric_limits<long long>::max();;


    Player();
    void setEntityTarget(Entity * entityRef);
    Skill * getActiveSkill();
    void stopEntityAction();
    void startEntityAction();
    double calcHitChance();
    int calcMinHit();
    int calcMaxHit();
    Inventory * getPlayerInventory();
    void update();
    void doEntityAction();
    void getStatus();
   

};

#endif