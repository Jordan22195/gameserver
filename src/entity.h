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

#include "item.h"
#include "skill.h"
#include "dropTable.h"

using namespace std;

struct ActionResult
{
    vector<Item> items;
    int xp = 0;
};


class Entity
{
    public:
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

    queue<long long> respawnTimes;

    virtual void getStatus();

    long long getNextRespawnTime();
    void respawn();
    void id();
    int calcDamage(double hitChance, int minHit, int maxHit);
    int takeDamage(int amount);

    virtual ActionResult action(double hitChance, int minHit, int maxHit);

    protected:
    mutex mtx;

};






#endif