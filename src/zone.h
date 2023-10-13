#ifndef ZONE
#define ZONE

#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <chrono>
#include <thread>
#include <string>
#include <sstream>

#include "entity.h"
#include "combatEntity.h"
#include "resourceEntity.h"
#include "logger.h"
#include "websocketInterface.h"
#include "json.hpp"
#include "dropTable.h"


using json = nlohmann::json;

using namespace std;

class Player;

class Zone
{   
    public:
    WebsocketInterface * clientInterface;
    string name;

    //unique id, count
    map<int, int> entities;
    dropTable entitySpawnTable;
   // map<string, Player*> players;
    static long long lastServerUpdate;
    void respawnEntites();
    void playerActions();
    Player * getPlayer(string targetName);

    void createNewPlayer(string name);

    void explore();
    virtual json to_json();

    

};



class Zone1 : public Zone{
    public:
    Zone1();

};

#endif