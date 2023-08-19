#ifndef SKILL
#define SKILL

#include <string>
#include <chrono>
#include <thread>

#include "inventory.h"

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
        cout << this->xp << endl;
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
    WoodCuttingSkill()
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
    AttackSkill()
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
    StrengthSkill()
    {
        name = "Strength";
        xp = 0;
        level = 1;
        type = MELEE_COMBAT;
    }
};

class FletchingSkill : public Skill
{

    FletchingSkill()
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