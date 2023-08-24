#include <iostream>
#include <fstream>
#include <curl/curl.h> // You might need to install a library to handle HTTP requests, like libcurl.
#include <string>
#include <chrono>
#include <thread>
#include <vector>
#include <cstring>
#include <cstdlib>

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

int IPCTest() {

    auto pipe = fstream("../pipe1");
    pipe << "from game server" << endl;

    return 0;

}






int main() 
{

    cout << "main" << endl;

    IPCTest();

    return 0;

    Inventory inv;


    Zone1 zone;
    DBInterface::go();
    cout << "db go" << endl;
    Player * playerptr;
    playerptr = new Player("cobek");
    cout << "new player" << endl;
    playerptr->setEntityTarget(zone.entities[0]);
    zone.players.push_back(playerptr);
    cout << "add to zone"<< endl;
    playerptr->startEntityAction();
    cout << "start action" << endl;

   // DBInterface::putPlayerItem("Players", "1", "cobek", clientconfig);

        const Aws::String tableName("game-table");
        const Aws::String partitionKey("players");
        const Aws::String partitionValue("0");
        const Aws::String attributeKey("WoodcuttingXp");
        const Aws::String attributeValue("1");




   // DBInterface::updatePlayerItem(tableName, partitionKey, partitionValue,
   //                                  attributeKey,
   //                                  attributeValue, clientconfig);

    while(true)
    {
        //system("clear");
        //zone.getZoneView();
        std::this_thread::sleep_for(std::chrono::milliseconds((500)));

    }


}
