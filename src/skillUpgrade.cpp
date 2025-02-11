#include "skillUpgrade.h"
#include "json.hpp"


SkillUpgrade::SkillUpgrade()
{
    return;
}

SkillUpgrade::SkillUpgrade(
    string upgradeName, 
    SKILL_MODIFIER type,
    int levelReq,
    int upgradeMaxLevel,
    int costBase,
    int costLinCeof,
    int costExpCeof,
    int modifierBase,
    int modifierLinCeof,
    int modifierExpCeo)
{
    name = upgradeName;
    skillModifierType = type;
    levelRequirement = levelReq;
    maxLevel = upgradeMaxLevel;
    cost = ScalableNumber(costBase, costLinCeof, costExpCeof);
    skillModifier = ScalableNumber(modifierBase, modifierLinCeof, modifierExpCeo);
}

nlohmann::json SkillUpgrade::to_json()
{
    nlohmann::json j;
    j["name"] = name;
    j["levelRequirement"] = levelRequirement;
    j["level"] = level;
    j["maxLevel"] = maxLevel;
    j["cost"] = cost.to_json();
    j["skillModifier"] = skillModifier.to_json();
    j["skillModifierType"] = skillModifierType;

    return j;
}