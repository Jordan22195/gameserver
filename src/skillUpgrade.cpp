#include "skillUpgrade.h"
#include "json.hpp"


nlohmann::json SkillUpgrade::to_json()
{
    nlohmann::json j;
    j["name"] = name;
    j["level"] = level;
    j["cost"] = cost;
    j["additiveSkillAdjustment"] = additiveSkillAdjustnmentPerLevel;
    j["multiplicitiveSkillAdjustment"] = multiplicitiveSkillAdjustnmentPerLevel;

    return j;
}