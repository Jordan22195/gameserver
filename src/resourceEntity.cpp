#include "resourceEntity.h"

    //return xp and item on successful action
    ActionResult ResourceEntity::action(double hitChance, int minHit, int maxHit)
    {
        lock_guard<std::mutex> lock(mtx);
        ActionResult r;
        int d = takeDamage(calcDamage(hitChance, minHit, maxHit));
        if ( d > 0)
        {
            skillXP xpres;
            xpres.skillType = this->skillType;
            xpres.xpAmount = xpValue;
            r.xp.push_back(xpres);
            auto rollResults = loot.roll();
            for (auto i : rollResults)
            {
                r.items.push_back( ItemFactory::createItem(i.id,i.count));
            }
        }
        return r;
    }