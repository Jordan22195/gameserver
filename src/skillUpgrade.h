#ifndef SKILL_UPGRADE
#define SKILL_UPGRADE

#include <string>
#include "logger.h"
#include "json.hpp"
#include "scalableNumber.h"


using namespace std;

enum SKILL_MODIFIER
{
    POWER,
    SPEED,
    ACCELERATION
};

class SkillUpgrade
{
    public:
    int levelRequirement;
    string name;
    int level;
    int maxLevel;

    SkillUpgrade();
    SkillUpgrade(
        string upgradeName, 
        SKILL_MODIFIER type,
        int levelReq,
        int upgradeMaxLevel,
        int costBase,
        int costLinCeof,
        int costExpCeof,
        int modifierBase,
        int modifierLinCeof,
        int modifierExpCeo);

    ScalableNumber cost;
    ScalableNumber skillModifier;
    SKILL_MODIFIER skillModifierType = POWER;




    nlohmann::json to_json();



    private:

};

#endif