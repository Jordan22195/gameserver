
#include "craftingEntity.h"
bool craftingEntity::requiredItemsAvailable(){return true;}
ActionResult craftingEntity::action(){return ActionResult();}
/*
    bool craftingEntity::requiredItemsAvailable()
    {
        for (auto &i : craftingInput)
        {
            auto playerItem = playerBag->get(i);
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

    ActionResult craftingEntity::action()
    {
        if(!requiredItemsAvailable(playerRef->getPlayerInventory()))
        {
            return ActionResult();
        }
        
        for (auto & i : craftingInput)
        {
            playerRef->getPlayerInventory()->removeItem(i);
        }
        ActionResult r;
        r.xp = xpValue;
        r.items = loot.roll();
        
    }

    */