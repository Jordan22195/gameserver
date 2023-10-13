    #include "combatEntity.h"
    
    ActionResult combatEntity::action(double hitChance, int minHit, int maxHit, SKILL_TYPE skill)
    {

        ActionResult r;
        int d = takeDamage(calcDamage(hitChance, minHit, maxHit));
        if ( d > 0)
        {
            skillXP xp;
            xp.skillType = skill;
            xp.xpAmount = xpValue * d;
            
            if (health == maxHealth || health == 0)
            {
                r.items = loot.roll();
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