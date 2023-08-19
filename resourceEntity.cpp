#include "resourceEntity.h"

    ActionResult ResourceEntity::action(double hitChance, int minHit, int maxHit)
    {
        lock_guard<std::mutex> lock(mtx);
        ActionResult r;
        int d = takeDamage(calcDamage(hitChance, minHit, maxHit));
        if ( d > 0)
        {
            r.xp = xpValue;
            r.items = loot.roll();
        }
        return r;
    }