
#ifndef ENTITY_FACTORY
#define ENTITY_FACTORY


#include <thread>

#include "combatEntity.h"
#include "entity.h"


enum class entityIdEnum
{
    COMBAT_GOBLIN_NORMAL_1,
    WOODCUTTING_OAK
};



class EntityFactory
{
    public:

    inline static vector<Entity*> entities;

    inline static thread updateThread;

    static void startEntityUpdateThread()
    {
        updateThread = thread(updateEntities);

    }

    static void registerEntity(Entity * e)
    {
        entities.push_back(e);
    }

    // call update function for all registered entities
    static void updateEntities()
    {
        while(true)
        {
            for (int i = entities.size()-1; i >= 0; i--)
            {
                entities[i]->update();
                if(entities[i]->count == 0 && entities[i]->health == 0)
                {
                    entities.erase(entities.begin()+i);
                }
            }

            std::this_thread::sleep_for(std::chrono::milliseconds((10)));
        }
 
    }

    static Entity * createEntity(entityIdEnum id)
    {
        Entity * ret;
        switch(id)
        {
            case entityIdEnum::COMBAT_GOBLIN_NORMAL_1:
                ret = new Goblin((int) id);
                break;
            case entityIdEnum::WOODCUTTING_OAK:
                ret = new OakTree((int)id);
                break;

        }
        if(ret)
            registerEntity(ret);
        return ret;
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
