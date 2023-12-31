#include "entity.h"
#include "timeKeeping.h"
#include <sstream>

long long Entity::getNextRespawnTime()
{
    lock_guard<std::mutex> lock(mtx);
    if (respawnTimes.size() > 0)
    {
        return respawnTimes.front();
    }
    else
    {
        return -1;
    }
}

void Entity::update()
{};

void Entity::respawn()
{
    lock_guard<std::mutex> lock(mtx);
    if (respawnTimes.size() > 0)
    {
        respawnTimes.pop();
        count++;
    }
}

string Entity::id(){
    return name;
}

int Entity::calcDamage(double hitChance, int minHit, int maxHit)
{
    if (loot.getRandomDouble(0.0, 1.0) <= hitChance)
    {
        return loot.getRandomInt(minHit, maxHit);
    }
    else
    {
        return 0;
    }
}



int Entity::takeDamage(int amount)
{
    if (health > 0)
    {

        if (amount > health)
        {
            amount = health;
        }
        health -= amount;
        if (health == 0 && count > 0)
        {
            health = maxHealth;
            count --;
        }
        //cout << name << " hp " << health << "/" << maxHealth << " | count " << count << "/" << maxCount << endl;
        return amount;
    }
    else
    {
        return 0;
    }
}

 ActionResult Entity::action(double hitChance, int minHit, int maxHit)
 {
    return ActionResult();
 }

  ActionResult Entity::action(double hitChance, int minHit, int maxHit, SKILL_TYPE skillType)
 {
    return ActionResult();
 }

 string Entity::getStatus()
 {
    stringstream ss;
    ss << " Entity " << name << " hp " << health << "/" << maxHealth << " | count " << count << "/" << maxCount;
    return ss.str();
 }

