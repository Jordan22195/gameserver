#ifndef SKILL
#define SKILL

#include <string>
#include <chrono>
#include <thread>

#include "actionResult.h"
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

struct craftingAction
{
    craftingAction(Item input, Item output, int xpVal, int levelReq, int executionTime_ms, double difficulty)
    {
        inputItem = input;
        outputItem = output;
        xp = xpVal;
        levelRequirement = levelReq;
        actionExecutionTime_ms = executionTime_ms;
        this->difficulty = difficulty;
    }
    Item inputItem;
    Item outputItem;
    int xp;
    int levelRequirement;
    int actionExecutionTime_ms;
    double difficulty;
    bool stopAction = false;

    bool performingAction = false;



    void doAction(Inventory * playerBag)
    {
        ActionResult r;
        performingAction = true;
        stopAction = false;
        while (performingAction)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds((int)(actionExecutionTime_ms)));
            if(stopAction)
            {
                performingAction = false;
                return;
            }
            ActionResult res;
        }
    }

};

class FletchingSkill : public Skill
{
    vector<craftingAction> craftingActions;

    FletchingSkill()
    {
        name = "Fletching";
        xp = 0;
        level = 1;
        type = FLETCHING;
        craftingActions.push_back(craftingAction(RegularLogsItem(1), ArrowShaftsItem(5), 10, 1, 2000, 1.0));
    }

    void doCraftingAction()
    {

    }



};

#endif