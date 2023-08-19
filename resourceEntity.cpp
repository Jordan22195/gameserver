#include "resourceEntity.h"

    ActionResult ResourceEntity::action()
    {
        lock_guard<std::mutex> lock(mtx);
        double hitChance;
         int minHit;
          int maxHit;
        ActionResult r;
        int d = takeDamage(calcDamage(hitChance, minHit, maxHit));
        if ( d > 0)
        {
            r.xp = xpValue;
            r.items = loot.roll();
        }
        return r;
    }