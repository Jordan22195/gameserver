    #include "combatEntity.h"
    

    //return xp on successful action
    //return item on death
    ActionResult combatEntity::action(double hitChance, int minHit, int maxHit)
    {
        Logger::TRACE("combatEntity::action()");
        ActionResult r;
        int d = takeDamage(calcDamage(hitChance, minHit, maxHit));
        if ( d > 0)
        {
            skillXP xp;
            xp.skillType = this->skillType;
            xp.xpAmount = xpValue * d;
            
            r.xp.push_back(xp);

            if (health == maxHealth || health == 0)
            {
                r.items = loot.roll();
                Logger::INFO("got %d items", r.items.size());
            }
        }
        return r;
    }


     void combatEntity::update()
    {

        //if enough time has elapsed
        if (nextAttackTime >= TimeKeeping::getServerTime()+attackInterval)
        {
            playerTarget->takeCombatDamage(attackLevel);
            nextAttackTime = TimeKeeping::getServerTime()+attackInterval;
        }
        
    }