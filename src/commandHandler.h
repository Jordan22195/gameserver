#ifndef COMMANDHANDLER
#define COMMANDHANDLER


#include "zone.h"
#include "player.h"
#include "websocketInterface.h"
#include <string>
#include <iostream>

using namespace std;



class CommandHander 
{
    public:
    WebsocketInterface * clientInterface;
    Zone * zone;
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
            if (zone->players.count(name) == 0)
            {
                zone->players[name] = new Player(name);
                zone->players[name]->clientInterface = this->clientInterface;
            }
            cmdResponse.name = name;
            json j;
            j["action"] = "LOGIN";
            j["response"] = "SUCCESS";
            j["zone"] = zone->to_json();
            Logger::TRACE("zone added to cmd response");
            j["player"] =  zone->players[name]->to_json();
            Logger::TRACE("player added to cmd response");
            cmdResponse.data = j;
            clientInterface->clientActionResponse(cmdResponse);

        }


        if (zone->players.count(name) == 0)
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
                string entTarget;
                input >> entTarget;
                if(zone->entities.count(entTarget) != 0)
                {
                    json j;
                    j["action"] = action;
                    j["result"] = "SUCCESS";
                    j["entity"] = zone->entities[entTarget]->to_json();
                    zone->players[name]->setEntityTarget(zone->entities[entTarget]);
                    cmdResponse.data = j;
                    clientInterface->clientActionResponse(cmdResponse);
                }
            } 
            if(action == "PERFORM_ENTITY_ACTION")
            {
                json j;
                if(zone->players[name]->startEntityAction())
                {
                    j["PERFORM_ENTITY_ACTION"] = "SUCCESS";
                }
                else{
                    j["PERFORM_ENTITY_ACTION"] = "FAILURE";
                }
                cmdResponse.data = j;
                clientInterface->clientActionResponse(cmdResponse);
            }



            input >> action;

        }



    }
};

#endif