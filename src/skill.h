#ifndef SKILL
#define SKILL

#include <string>
#include <chrono>
#include <thread>
#include <string>

#include "inventory.h"
#include "databaseInterface.h"

using namespace std;

enum SKILL_TYPE
{
    WOODCUTTING,
    STRENGTH,
    ATTACK,
    FLETCHING,
    MELEE_COMBAT
};

class Skill
{

    public:

    string playerUniqueID;
    Skill(string playerId)
    {
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
    int level;
    double actionInterval = 1000;
    SKILL_TYPE type;

    void addXp(int newXp)
    {
        this->xp += newXp;
        DBInterface::updatePlayerItem("Players-Table", "PlayerID", playerUniqueID, this->name, to_string(this->xp));
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
};


class WoodCuttingSkill : public Skill
{
    public:
    WoodCuttingSkill(string playerId) : Skill(playerId)
    {
        name = "Woodcutting";
        xp = 0;
        level = 1;
        actionInterval = 400;
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
        type = MELEE_COMBAT;
    }
};

class StrengthSkill : public Skill
{
    public:
    StrengthSkill(string playerId) : Skill(playerId)
    {
        name = "Strength";
        xp = 0;
        level = 1;
        type = MELEE_COMBAT;
    }
};

class FletchingSkill : public Skill
{

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