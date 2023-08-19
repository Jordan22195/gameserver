#include "entity.h"

class craftingEntity : public Entity
{
    public:
    vector<Item> craftingInput;
    double actionInterval_ms;
    bool requiredItemsAvailable();
    ActionResult action();
};

class arrowShaftCraftingEntity : public craftingEntity
{
    public:
    arrowShaftCraftingEntity()
    {
        craftingInput.push_back(RegularLogsItem(1));
        loot.addEntry(ArrowShaftsItem(), 1.0, 5);

        skillType = SKILL_TYPE::FLETCHING;
        xpValue = 5;
        levelRequirement = 1;
        actionInterval_ms = 1000;
        difficulty = 1;
    }

};
