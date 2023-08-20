#include <iostream>
#include <curl/curl.h> // You might need to install a library to handle HTTP requests, like libcurl.
#include <string>
#include <chrono>
#include <thread>
#include <vector>

#include "item.h"
#include "inventory.h"
#include "dropTable.h"
#include "entity.h"
#include "resourceEntity.h"
#include "combatEntity.h"
#include "timeKeeping.h"
#include "craftingEntity.h"
#include "zone.h"
#include "player.h"
#include "databaseInterface.h"


using namespace std;

int main() 
{

    Inventory inv;


    Zone1 zone;

    Player * playerptr;
    playerptr = new Player();
    playerptr->name = "cobek";
    playerptr->setEntityTarget(zone.entities[0]);
    zone.players.push_back(playerptr);
    playerptr->startEntityAction();

    DBInterface::login();

    while(true)
    {
        //system("clear");
        //zone.getZoneView();
        std::this_thread::sleep_for(std::chrono::milliseconds((500)));

    }


}
