#ifndef COMMANDHANDLER
#define COMMANDHANDLER



#include "player.h"
#include "websocketInterface.h"
#include <string>
#include <iostream>
#include <thread>

using namespace std;



class CommandHander 
{
    public:
    WebsocketInterface * clientInterface;
    map<string, Player> playerTracker;

    thread playerUpdateThread;

    void playerUpdate()
    {
        while(true)
        {

        
            for (auto it = playerTracker.begin() ;
            it!=playerTracker.end(); ++it)
            {
                it->second.update();
            }
        }
    }

    void startPlayerUpdateThread()
    {
        playerUpdateThread = thread(&CommandHander::playerUpdate,
        this);

    }

    void clientActionRequestHandler(string message)
    {
        Logger::TRACE("commandResponse clientActionRequestHandler(string message) %p", this);
        commandResponse cmdResponse;
        stringstream input(message);
        string name;
        string action;
        int numParams;
        input >> name;
        input >> action;


        vector<string> params;

        cout << "Got Client Action Request" << endl;
        cout << "Raw Request : " << endl << message << endl;

        cout << "name " << name << endl;
        cout << "action " << action << endl;


        if (action == "LOGIN")
        {
            cout << "performing login" << endl;
            //if new player, create player
            // return zone info and player stats
            if (playerTracker.count(name) == 0)
            {
                playerTracker[name] = Player(name);
                playerTracker[name].clientInterface = this->clientInterface;
            }
            cmdResponse.name = name;
            json j;
            j["action"] = "LOGIN";
            j["response"] = "SUCCESS";
            j["zone"] = playerTracker[name].currentZone->to_json();
            Logger::TRACE("zone added to cmd response");
            j["player"] =  playerTracker[name].to_json();
            Logger::TRACE("player added to cmd response");
            cmdResponse.data = j;
            clientInterface->clientActionResponse(cmdResponse);

        }


        if (playerTracker.count(name) == 0)
        {
            cmdResponse.name = name;
            //cmdResponse.data = "UNKNOWN_PLAYER";
            //clientInterface->clientActionResponse(cmdResponse);
            return;
        }

        cmdResponse.name = name;
        while(input)
        {
            if(action == "SET_ENTITY_TARGET")
            {
                int entTarget;
                input >> entTarget;
                if(playerTracker[name].currentZone->entities.count(entTarget) != 0)
                {
                    json j;
                    j["action"] = action;
                    j["result"] = "SUCCESS";
                    
                    // TODO //zone->entities[entTarget]->to_json();
                    //zone->players[name]->setEntityTarget(zone->entities[entTarget]);
                    playerTracker[name].setEntityTarget(entTarget);
                    j["entity"] = playerTracker[name].entityTarget->to_json();
                    cmdResponse.data = j;
                    clientInterface->clientActionResponse(cmdResponse);
                }
            } 
            if(action == "PERFORM_ENTITY_ACTION")
            {
                json j;
                if(playerTracker[name].startEntityAction())
                {
                    j["PERFORM_ENTITY_ACTION"] = "SUCCESS";
                }
                else{
                    j["PERFORM_ENTITY_ACTION"] = "FAILURE";
                }
                cmdResponse.data = j;
                clientInterface->clientActionResponse(cmdResponse);
            }
            if(action == "EXPLORE_ZONE")
            {
                playerTracker[name].startExploreZone();
            }



            input >> action;

        }



    }
};

#endif