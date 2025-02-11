#include "player.h"
#include "logger.h"
#include "combatEntity.h"
#include "entityFactory.h"


#include <cstring>
#include <fstream>
#include <iostream>


Player::Player()
{

}

Player::Player(string playerId)
{
    Logger::TRACE("Player::Player(string playerId) %p", this);
    name = playerId;
    skills[EXPLORATION] = new ExplorationSkill(playerId);
    skills[WOODCUTTING] = new WoodCuttingSkill(playerId);
    skills[ATTACK] = new AttackSkill(playerId);
    skills[HITPOINTS] = new WoodCuttingSkill(playerId);
    skills[DEFENSE] = new DefenseSkill(playerId);
    skills[HITPOINTS] = new HitPointsSkill(playerId);
    skills[FLETCHING] = new FletchingSkill(playerId);
    currentHealth = 1000;

    currentZone = new Zone1();
 
}


void Player::setEntityTarget(int id)
{
    //create ent with factory from id
    Logger::TRACE("Player::setEntityTarget(Entity * entityRef) %p", this);
    stopEntityAction();
    entityTarget = EntityFactory::createEntity((entityIdEnum)id);
    entityTarget->count = currentZone->entities[id];
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

void Player::startExploreZone()
{

    Logger::TRACE("startExploreZone");

    exploring = true;
    stopEntityAction();
    actionCounter = 0;

    nextActionTime = TimeKeeping::getServerTime();
}

void Player::reportZoneStatusToClient()
{
        ClientMessage zoneUpdate;
        zoneUpdate.playerName = name;
        zoneUpdate.packetType = "ZONE";
        zoneUpdate.data = currentZone->to_json();
        clientInterface->clientMessage(zoneUpdate);
}

void Player::doExploreZone()
{
    Logger::TRACE("doExploreZone");
    if (exploring &&  (TimeKeeping::getServerTime() >= nextActionTime))
    {

        auto exploreSkill = skills[EXPLORATION];

        int nextActionInterval = exploreSkill->baseActionInterval - (actionCounter * exploreSkill->actionIntervalAcceleration);
        if (nextActionInterval < exploreSkill->maxActionInterval)
        {
            nextActionInterval =  exploreSkill->maxActionInterval;
        }

        nextActionTime = TimeKeeping::getServerTime() + nextActionInterval;

        currentZone->explore();
        reportZoneStatusToClient();
    }
}

void Player::stopExplore()
{
    exploring = false;
}

void Player::stopEntityAction()
{
    Logger::TRACE("void Player::stopEntityAction() %p", this);
    stopAction = true;
    performingAction = false;
}

bool Player::startEntityAction()
{
     Logger::TRACE("void Player::startEntityAction() %p", this);
    performingAction = true;
    exploring = false;
    if (entityTarget == nullptr) return false;
    actionCounter = 0;

    nextActionTime = TimeKeeping::getServerTime() + getActiveSkill()->baseActionInterval;
    return true;
}

void Player::takeCombatDamage(int damage)
{
    currentHealth -= damage;

    ClientMessage resMessage;
    resMessage.playerName = name;
    resMessage.packetType = "PLAYER";
    resMessage.data = this->to_json();
    clientInterface->clientMessage(resMessage);

}

//player level as a percentage of target difficulty
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

// revisit this - I think just does 0 or max hit at the moment
int Player::calcMinHit()
{
    Logger::TRACE("int Player::calcMinHit() %p", this);
    int maxHit = calcMaxHit();
    int minHit = (int)((calcHitChance()-1.0) * (double)maxHit) + 1;
    if (minHit < maxHit) return minHit;
    else return maxHit;
}

//equal to level
int Player::calcMaxHit()
{
    Logger::TRACE("int Player::calcMaxHit() %p", this);
    auto skill = getActiveSkill();
    if (skill != nullptr)
    {
        return skills[skill->type]->level;
       
    }
    return 0;
}

Inventory * Player::getPlayerInventory()
{
    return &bag;
}


void  Player::update()
{
   // Logger::TRACE("update");
    if(performingAction)
    {
        if(!entityTarget)
        {
            stopEntityAction();
            return;
        }
        if(entityTarget->count == 0)
        {
            stopEntityAction();
            return;
        }
        doEntityAction();
    }
    if(exploring)
    {
        doExploreZone();
    }
   
    //TODO 
    //update entity count in zone from count in current entity target
}

void  Player::doEntityAction()
{
    Logger::TRACE("void  Player::doEntityAction()) %p", this);
    auto skill = getActiveSkill();
    Logger::TRACE( "time till action %d",  nextActionTime- TimeKeeping::getServerTime());
    if (performingAction && (TimeKeeping::getServerTime() >= nextActionTime))
    {
        Logger::TRACE("perfoming action");
        if (skill->level >= entityTarget->levelRequirement)
        {   
            
            Logger::TRACE("level requirement met");
            actionCounter ++;
            ActionResult res = entityTarget->action(calcHitChance(), calcMinHit(), calcMaxHit());
            Logger::TRACE("action exectuted");
            reportActionResults(res);
            for (auto xp : res.xp)
            {
                skills[xp.skillType]->addXp(xp.xpAmount);
            }
            bag.addItems(res.items);

            int nextActionInterval = skill->baseActionInterval - (actionCounter * skill->actionIntervalAcceleration);
            if (nextActionInterval < skill->maxActionInterval)
            {
                nextActionInterval =  skill->maxActionInterval;
            }

            nextActionTime = TimeKeeping::getServerTime() + nextActionInterval;
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
    Logger::TRACE("Player::reportActionResults()");
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
    clientInterface->clientMessage(resMessage);


    ClientMessage pMessage;
    pMessage.playerName = name;
    pMessage.packetType = "PLAYER";
    pMessage.data = to_json();
    clientInterface->clientMessage(pMessage);




}