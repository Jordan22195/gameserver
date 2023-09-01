#ifndef WEBSOCKET_INTERFACE
#define WEBSOCKET_INTERFACE

#include "udpsend.h"
#include <string>
#include "logger.h"

using namespace std;



class WebsocketInterface
{

    public:

    int a =1;
    WebsocketInterface();
    udpSocket *txSocket = nullptr; 
    udpSocket *rxSocket = nullptr;
    void clientActionRequestHandler(string message);
    void sendServerMessage(string playerName, string data);
    string recieveServerMessage();
};

#endif