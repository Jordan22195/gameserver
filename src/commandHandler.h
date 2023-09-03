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
            cmdResponse.data = zone->packetify() + zone->players[name]->packetify();
            clientInterface->clientActionResponse(cmdResponse);

        }


        if (zone->players.count(name) == 0)
        {
            cmdResponse.name = name;
            cmdResponse.data = "UNKNOWN_PLAYER";
            clientInterface->clientActionResponse(cmdResponse);
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
                    zone->players[name]->setEntityTarget(zone->entities[entTarget]);
                    cmdResponse.data = "SET_ENTITY_TARGET\n" + entTarget + "\nSUCCESS";
                    clientInterface->clientActionResponse(cmdResponse);
                }
            } 
            if(action == "PERFORM_ENTITY_ACTION")
            {
                if(zone->players[name]->startEntityAction())
                {
                    cmdResponse.data = "PERFORM_ENTITY_ACTION\nSUCCESS";
                }
                else{
                    cmdResponse.data = "PERFORM_ENTITY_ACTION\nFAILURE";
                }
                clientInterface->clientActionResponse(cmdResponse);
            }



            input >> action;

        }



    }
};

#endif