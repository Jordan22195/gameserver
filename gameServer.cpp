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


using namespace std;

int main() 
{

    Inventory inv;

    string menu = "\n\n\n a:Add Player #:select player";

    Zone1 zone;

    Player * playerptr;

    while(true)
    {
        system("clear");
        zone.getZoneView();
        cout << menu;
        std::this_thread::sleep_for(std::chrono::milliseconds((500)));

        string input;
        cin >> input;
        if (input == "a")
        {
            cout << "enter new player name" << endl;
            string name;
            cin >> name;
            playerptr = new Player();
            playerptr->name = name;
            zone.players.push_back(playerptr);

        }

    }


}
