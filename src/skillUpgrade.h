#ifndef SKILL_UPGRADE
#define SKILL_UPGRADE

#include <string>
#include "logger.h"
#include "json.hpp"


using namespace std;

class SkillUpgrade
{
    public:
    string name;
    int level;
    int cost;
    float additiveSkillAdjustnmentPerLevel;
    float multiplicitiveSkillAdjustnmentPerLevel;

    nlohmann::json to_json();



    private:

};

#endif