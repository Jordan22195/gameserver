#ifndef WEBSOCKET_INTERFACE
#define WEBSOCKET_INTERFACE

#include "udpsend.h"
#include <string>
#include "logger.h"

using namespace std;

struct commandResponse
{
    string name;
    string data;
};

class WebsocketInterface
{

    public:

    int a =1;
    WebsocketInterface();
    udpSocket *txSocket = nullptr; 
    udpSocket *rxSocket = nullptr;
    void clientActionRequestHandler(string message);
    void clientActionResponse(commandResponse resp);
    void sendServerMessage(string playerName, string data);
    string recieveServerMessage();

    private:
    mutex TxMtx;
    mutex RxMtx;
};

#endif