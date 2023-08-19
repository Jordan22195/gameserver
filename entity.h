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

    long long getNextRespawnTime();
    void respawn();
    void id();
    int calcDamage(double hitChance, int minHit, int maxHit);
    int takeDamage(int amount);
    virtual ActionResult action();// (Player * playerRef);

    protected:
    mutex mtx;

};






#endif