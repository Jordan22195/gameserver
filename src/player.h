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
#include "websocketInterface.h"

using namespace std;

class Entity;

class Player
{

    public:
    WebsocketInterface * clientInterface;
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
    bool startEntityAction();
    double calcHitChance();
    int calcMinHit();
    int calcMaxHit();
    Inventory * getPlayerInventory();
    void update();
    void doEntityAction();
    void getStatus();
    void reportActionResults(ActionResult res);

    virtual string packetify()
    {
        Logger::TRACE("virtual string Player:packetify()  %p", this);
        stringstream ss;
        ss << "PLAYER" << endl;
        ss << name << endl;
        ss << "SKILLS" << endl;
        ss << skills.size() << endl;
        for (auto &s : skills)
        {
            ss << "SKILL" << endl << s.second->name << endl << s.second->xp << endl;
        }
        ss << bag.packetify();
        return ss.str();
    }

};

#endif