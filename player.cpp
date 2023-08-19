#include "player.h"

Player::Player()
{
    skills[WOODCUTTING] = WoodCuttingSkill();
    skills[ATTACK] = AttackSkill();
    skills[STRENGTH] = StrengthSkill();
}

void Player::setEntityTarget(Entity * entityRef)
{
    stopEntityAction();
    entityTarget = entityRef;
}

Skill * Player::getActiveSkill()
{
    if(entityTarget != nullptr)
    {
        if(entityTarget->skillType == MELEE_COMBAT)
        {
            return  &skills[ATTACK];
        }
        return &skills[entityTarget->skillType];
    }
    return nullptr;
}

void Player::stopEntityAction()
{
    stopAction = true;
    if (actionThread.joinable()) {
        actionThread.join();
    }
}
void Player::startEntityAction()
{
    if(entityTarget == nullptr) return;
    actionThread = thread(&Player::doEntityAction, this);
}

double Player::calcHitChance()
{
    auto skill = getActiveSkill();
    if (skill != nullptr)
    {
        return (double)skill->level / (double)entityTarget->difficulty;
    }
    return 0.0;
}
int Player::calcMinHit()
{
    int maxHit = calcMaxHit();
    int minHit = (int)((calcHitChance()-1.0) * (double)maxHit) + 1;
    if (minHit < maxHit) return minHit;
    else return maxHit;
}
int Player::calcMaxHit()
{
    auto skill = getActiveSkill();
    if (skill != nullptr)
    {
        if (skill->type != ATTACK)
        {
            return 1;
        }
        else
        {
            return skills[STRENGTH].level;
        }
    }
    return 0;
}

Inventory * Player::getPlayerInventory()
{
    return &bag;
}

long long nextActionTime = -1; // numeric_limits<long long>::max();;

void  Player::update()
{
    doEntityAction();
}

void  Player::doEntityAction()
{
    auto skill = getActiveSkill();
    if (performingAction && (TimeKeeping::lastServerTime >= nextActionTime))
    {
        if (skill->level >= entityTarget->levelRequirement)
        {
            ActionResult res = entityTarget->action(calcHitChance(), calcMinHit(), calcMaxHit());
            skill->addXp(res.xp);
            bag.addItems(res.items);
            nextActionTime = TimeKeeping::lastServerTime + skill->actionInterval;
        }
    
    }
}

void Player::getStatus()
{
    cout << name << " ";
    if (entityTarget!= nullptr) entityTarget->getStatus();
    else cout << "idle";

}
