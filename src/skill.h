#ifndef SKILL
#define SKILL

#include <string>
#include <chrono>
#include <thread>
#include <string>

#include "inventory.h"
#include "databaseInterface.h"
#include "logger.h"
#include "json.hpp"

using json = nlohmann::json;

using namespace std;

enum SKILL_TYPE
{
    WOODCUTTING,
    ATTACK,
    HITPOINTS,
    DEFENSE,
    RANGED,
    FLETCHING
};

class Skill
{

    public:

    string playerUniqueID;
    Skill(string playerId)
    {
        Logger::TRACE("Skill(string playerId)  %p", this);
        playerUniqueID =playerId;
    }
    int xpLevelThreasholds [99] = {
        0, 
        100,
        300,
        500,
        900,
        1500,
        2200,
        3000,
        4000,
        5500,
        7000,
        9000,
        12000,
        15000,
        20000
    };
    string name;
    int xp;
    int level = 1;
    // in game ticks
    double actionInterval = 5;
    SKILL_TYPE type;

    void addXp(int newXp)
    {
        this->xp += newXp;
        //DBInterface::updatePlayerItem("Players-Table", "PlayerID", playerUniqueID, this->name, to_string(this->xp));
        while (xp >= xpLevelThreasholds[level])
        {
            levelUp();
        } 
    }

    void levelUp()
    {
        level++;
        cout << name << " level up! New Level is " << level << endl;
    }

    json to_json()
    {
        json j;
        j["name"] = name;
        j["level"] = level;
        j["xp"] = xp;
        j["actionInterval"] = actionInterval;

        return j;
    }
};

class WoodCuttingSkill : public Skill
{
    public:
    WoodCuttingSkill(string playerId) : Skill(playerId)
    {
        name = "Woodcutting";
        xp = 0;
        level = 1;
        actionInterval = 5;
        type = WOODCUTTING;
    }
};

class AttackSkill : public Skill
{
    public:
    AttackSkill(string playerId) : Skill(playerId)
    {
        name = "Attack";
        xp = 0;
        level = 1;
        type = ATTACK;
    }
};

class DefenseSkill : public Skill
{
    public:
    DefenseSkill(string playerId) : Skill(playerId)
    {
        name = "Defense";
        xp = 0;
        level = 1;
        type = DEFENSE;
    }
};

class HitPointsSkill : public Skill
{
    public:
    HitPointsSkill(string playerId) : Skill(playerId)
    {
        name = "Hit Points";
        xp = 0;
        level = 1;
        type = HITPOINTS;
    }
};


class FletchingSkill : public Skill
{
    public:
    FletchingSkill(string playerId) : Skill(playerId)
    {
        name = "Fletching";
        xp = 0;
        level = 1;
        type = FLETCHING;
    }

    void doCraftingAction()
    {

    }



};

#endif