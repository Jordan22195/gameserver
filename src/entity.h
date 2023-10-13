#ifndef ENTITY
#define ENTITY

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <random>
#include <mutex>
#include <queue>
#include <memory>
#include <sstream>

#include "item.h"
#include "skill.h"
#include "dropTable.h"
#include "json.hpp"


using json = nlohmann::json;


using namespace std;



enum SKILL_CATEGORY
{
    GATHER,
    COMBAT,
    CRAFT
};

struct skillXP
{
    SKILL_TYPE skillType;
    int xpAmount;
    

    json to_json()
    {
        json j;
        j["skill"] = skillType;
        j["xp"] = xpAmount;

        return j;
    }
};

struct ActionResult
{
    vector<skillXP> xp;
    vector<rollResult> items;

    json to_json()
    {
        json j;
        json itemArray = json::array();
        json xpArray = json::array();
        for (auto i : items)
        {
            itemArray.push_back(i.to_json());
        }
        for (auto x : xp)
        {
            xpArray.push_back(x.to_json());
        }
        j["items"] = itemArray;
        j["xpPoints"] = xpArray;
        Logger::TRACE("action result to_json() \n %s", j.dump());
        return j;
    }
};


class Entity
{
    public:
    int entId;
    string name;
    int health;
    int maxHealth;
    dropTable loot;
    int respawnTime;
    int xpValue;
    int count;
    int maxCount;
    SKILL_TYPE skillType;
    int levelRequirement;
    int difficulty;
    SKILL_CATEGORY skillCategory;

    queue<long long> respawnTimes;

    virtual string getStatus();

    virtual void update();

    long long getNextRespawnTime();
    void respawn();
    virtual string id();
    int calcDamage(double hitChance, int minHit, int maxHit);
    int takeDamage(int amount);

    virtual ActionResult action(double hitChance, int minHit, int maxHit);
    virtual ActionResult action(double hitChance, int minHit, int maxHit, SKILL_TYPE skill);

    virtual json to_json()
    {
        json j;
        j["id"] = entId;
        j["name"] = name;
        j["skillType"] = skillType;
        j["health"] = health;
        j["maxHealth"] = maxHealth;
        j["count"] = count;
        j["maxCount"] = maxCount;
        return j;
    }

    protected:
    mutex mtx;

};






#endif