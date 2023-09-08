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
#include "json.hpp"

using json = nlohmann::json;

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
    json toJson();

    virtual json to_json()
    {

        Logger::TRACE("virtual string Player:packetify()  %p", this);

        json j;
        j["name"] = name;
        json skillsArray = json::array();
         for (auto &s : skills)
        {
            skillsArray.push_back(s.second->to_json());
        }
        Logger::TRACE("end of skills");
        j["skills"] = skillsArray;
        Logger::TRACE("put skills in ret");
        j["bag"] = bag.to_json();
        Logger::TRACE("put bag in ret");

        return j;
    }

};

#endif