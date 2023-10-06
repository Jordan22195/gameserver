
#ifndef ENTITY_FACTORY
#define ENTITY_FACTORY

#include "entity.h"
#include "combatEntity.h"

enum entityIdEnum
{
    COMBAT_GOBLIN_NORMAL_1
};

class EntityFactory
{
    Entity * createEntity(entityIdEnum id)
    {
        switch(id)
        {
            case COMBAT_GOBLIN_NORMAL_1:
                return new Goblin((int)id);

        }
    }
};

#endif
