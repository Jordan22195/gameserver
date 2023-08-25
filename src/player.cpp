#include "player.h"
#include <cstring>
#include <fstream>
#include <iostream>

Player::Player(string playerId)
{
    name = playerId;
    skills[WOODCUTTING] = new WoodCuttingSkill(playerId);
    skills[ATTACK] = new AttackSkill(playerId);
    skills[STRENGTH] = new StrengthSkill(playerId);
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
            return  skills[ATTACK];
        }
        return skills[entityTarget->skillType];
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
    performingAction = true;
    if (entityTarget == nullptr) return;
    actionCounter = 0;

    nextActionTime = TimeKeeping::lastServerTime + getActiveSkill()->actionInterval;
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
            return skills[STRENGTH]->level;
        }
    }
    return 0;
}

Inventory * Player::getPlayerInventory()
{
    return &bag;
}


void  Player::update()
{
    doEntityAction();
}
void  Player::doEntityAction()
{
    auto skill = getActiveSkill();
    //cout << "time till action " << nextActionTime- TimeKeeping::lastServerTime << endl;
    if (performingAction && (TimeKeeping::lastServerTime >= nextActionTime))
    {

        if (skill->level >= entityTarget->levelRequirement)
        {
            actionCounter ++;
            ActionResult res = entityTarget->action(calcHitChance(), calcMinHit(), calcMaxHit());
            reportActionResults(res);
            skill->addXp(res.xp);
            bag.addItems(res.items);
            nextActionTime = TimeKeeping::lastServerTime + skill->actionInterval;
        }
    
    }
}

void Player::getStatus()
{
    cout << name << " Skill: ";
    if(getActiveSkill()!= nullptr)
    {
        cout << getActiveSkill()->name << " xp " << getActiveSkill()->xp << " level: " << getActiveSkill()->level;
    } 
    if (entityTarget!= nullptr) { cout << "Target: ";
     entityTarget->getStatus();
     cout << " Actions: " << actionCounter << endl;}
    else cout << "idle";

}

void Player::reportActionResults(ActionResult res)
{
    string s = name + "\n";
     std::ofstream fs("../pipe1");
    fs << name << endl;
    fs << "Action Result " << res.xp; 
    for (Item &i : res.items)
    {
        fs << " " << i.name << " " << i.quantity;
    }
    fs << entityTarget->getStatus();
    fs << endl;
}