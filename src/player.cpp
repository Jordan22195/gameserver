#include "player.h"
#include "logger.h"
#include "combatEntity.h"


#include <cstring>
#include <fstream>
#include <iostream>


Player::Player(string playerId)
{
    Logger::TRACE("Player::Player(string playerId) %p", this);
    name = playerId;
    skills[WOODCUTTING] = new WoodCuttingSkill(playerId);
    skills[ATTACK] = new AttackSkill(playerId);
 
}


void Player::setEntityTarget(string id)
{
    //create ent with factory from id
    Logger::TRACE("Player::setEntityTarget(Entity * entityRef) %p", this);
    stopEntityAction();
    //entityTarget = entityRef;
}

Skill * Player::getActiveSkill()
{
    Logger::TRACE("Skill * Player::getActiveSkill() %p", this);
    if(entityTarget)
    {
        if(entityTarget->skillCategory == COMBAT)
        {
            return  skills[ATTACK];
        }
        return skills[entityTarget->skillType];
    }
    return nullptr;
}

void Player::stopEntityAction()
{
    Logger::TRACE("void Player::stopEntityAction() %p", this);
    stopAction = true;
    if (actionThread.joinable()) {
        actionThread.join();
    }
}
bool Player::startEntityAction()
{
     Logger::TRACE("void Player::startEntityAction() %p", this);
    performingAction = true;
    if (entityTarget == nullptr) return false;
    actionCounter = 0;

    nextActionTime = TimeKeeping::lastServerTime + getActiveSkill()->actionInterval;
    return true;
}

double Player::calcHitChance()
{
    Logger::TRACE("double Player::calcHitChance() %p", this);
    auto skill = getActiveSkill();
    if (skill != nullptr)
    {
        return (double)skill->level / (double)entityTarget->difficulty;
    }
    return 0.0;
}
int Player::calcMinHit()
{
    Logger::TRACE("int Player::calcMinHit() %p", this);
    int maxHit = calcMaxHit();
    int minHit = (int)((calcHitChance()-1.0) * (double)maxHit) + 1;
    if (minHit < maxHit) return minHit;
    else return maxHit;
}
int Player::calcMaxHit()
{
    Logger::TRACE("int Player::calcMaxHit() %p", this);
    auto skill = getActiveSkill();
    if (skill != nullptr)
    {
        if (skill->type != ATTACK)
        {
            return 1;
        }
        else
        {
            return skills[ATTACK]->level;
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
    //TODO 
    //update entity count in zone from count in current entity target
}
void  Player::doEntityAction()
{
    Logger::TRACE("void  Player::doEntityAction()) %p", this);
    auto skill = getActiveSkill();
    //cout << "time till action " << nextActionTime- TimeKeeping::lastServerTime << endl;
    if (performingAction && (TimeKeeping::lastServerTime >= nextActionTime))
    {

        if (skill->level >= entityTarget->levelRequirement)
        {   
        
            actionCounter ++;
            ActionResult res = entityTarget->action(calcHitChance(), calcMinHit(), calcMaxHit(), ATTACK);
            reportActionResults(res);
            for (auto xp : res.xp)
            {
                skills[xp.skillType]->addXp(xp.xpAmount);
            }
            //bag.addItems(res.items);
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
    json j;
    ClientMessage entMessage;

    if (entityTarget) 
    {
        entMessage.playerName = name;
        entMessage.packetType = "ENTITY";
        entMessage.data = entityTarget->to_json();
        clientInterface->clientMessage(entMessage);

    }

    ClientMessage resMessage;
    resMessage.playerName = name;
    resMessage.packetType = "ACTION_RESULT";
    resMessage.data = res.to_json();


    ClientMessage pMessage;
    pMessage.playerName = name;
    pMessage.packetType = "PLAYER";
    pMessage.data = to_json();
    clientInterface->clientMessage(pMessage);



    clientInterface->clientMessage(resMessage);

}