
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
    public:
    static Entity * createEntity(entityIdEnum id)
    {
        switch(id)
        {
            case COMBAT_GOBLIN_NORMAL_1:
                return new Goblin((int)id);

        }
    }

    static string getEntityNameFromId(entityIdEnum id )
    {
        auto e = createEntity(id);
        
        if (e)
        {
            return e->name;
        }
        //what happen to the object e is pointing at when this function returns?
        // todo destruct entity object
        return "";
    }
};

#endif
