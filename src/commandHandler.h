#ifndef COMMANDHANDLER
#define COMMANDHANDLER


#include "zone.h"
#include "player.h"

#include <string>
#include <iostream>

using namespace std;

struct commandResponse
{
    string name;
    string data;
};

class CommandHander 
{
    public:
    Zone * zone;
    commandResponse clientActionRequestHandler(string message)
    {
        Logger::TRACE("commandResponse clientActionRequestHandler(string message) %p", this);
        commandResponse ret;
        stringstream input(message);
        string name;
        string action;
        int numParams;
        input >> name;
        input >> action;
        input >> numParams;

        vector<string> params;

        cout << "Got Client Action Request" << endl;
        cout << "Raw Request : " << endl << message << endl;

        cout << "name " << name << endl;
        cout << "action " << action << endl;
        cout << "numParams " << numParams << endl;


        if (action == "LOGIN")
        {
            cout << "performing login" << endl;
            //if new player, create player
            // return zone info and player stats
            if (zone->players.count(name) == 0)
            {
                zone->players[name] = new Player(name);
            }
            ret.name = name;
            ret.data = zone->players[name]->packetify();

        }
        else
        {

        }

        return ret;

    }
};

#endif