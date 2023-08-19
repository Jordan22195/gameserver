
#include "craftingEntity.h"

    bool craftingEntity::requiredItemsAvailable(Inventory * bag)
    {
        for (auto &i : craftingInput)
        {
            auto playerItem = bag->get(i);
            if(playerItem == nullptr)
            {
                return false;
            }
            else if (playerItem->quantity < i.quantity)
            {
                return false;
            }
        }
        return true;
    }

    ActionResult craftingEntity::action(Inventory * bag)
    {
        if(!requiredItemsAvailable(bag))
        {
            return ActionResult();
        }
        
        for (auto & i : craftingInput)
        {
           bag->removeItem(i);
        }
        ActionResult r;
        r.xp = xpValue;
        r.items = loot.roll();
        
    }

    