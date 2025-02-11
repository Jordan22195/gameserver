#ifndef SKILL
#define SKILL

#include <string>
#include <chrono>
#include <thread>
#include <string>
#include <vector>

#include "inventory.h"
#include "databaseInterface.h"
#include "logger.h"
#include "skillUpgrade.h"
#include "json.hpp"

using json = nlohmann::json;

using namespace std;

enum SKILL_TYPE
{
    EXPLORATION,
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
    vector<SkillUpgrade> upgrades;

    // in game ticks
    double baseActionInterval = 10;
    // fastest 
    double maxActionInterval = 5;

    // number of game ticks to speed up per game tick
    double actionIntervalAcceleration = 1;

    SKILL_TYPE type;
   // vector<SkillUpgrade> upgrades;
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

    int effectiveLevel()
    {
        float linear = 1.0;
        float exp = 1;

       // for (auto &upgrade : upgrades)
       // {
      //      linear += upgrade.additiveSkillAdjustnmentPerLevel;
      //      exp *= upgrade.multiplicitiveSkillAdjustnmentPerLevel;
      //  }
        return level * linear * exp;
    }


    json to_json()
    {
        json j;
        j["name"] = name;
        j["level"] = level;
        j["effectiveLevel"] = effectiveLevel();
        j["xp"] = xp;
        j["baseActionInterval"] = baseActionInterval;
        j["maxActionInterval"] = maxActionInterval;
        j["actionIntervalAcceleration"] = actionIntervalAcceleration;
        json upgradesArray = json::array();
        for (auto &s : upgrades)
        {
            upgradesArray.push_back(s.to_json());
        } 
        j["upgrades"] = upgradesArray;

        return j;
    }
};

class ExplorationSkill : public Skill
{
    public:
    ExplorationSkill(string playerId) : Skill(playerId)
    {
        name = "Exploration";
        xp = 0;
        level = 1;
        type = EXPLORATION;
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

        //                          name                type     lvlreq,     maxLvl, costBase,   cLin,   cExp,   mBase,  mLin,   mExp
        SkillUpgrade testUpgrades( "A little Stronger", POWER,     1,          5,      1,          10,     0,      0,      1,      0);
        upgrades.push_back(testUpgrades);


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