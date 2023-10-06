#ifndef WEBSOCKET_INTERFACE
#define WEBSOCKET_INTERFACE

#include "udpsend.h"
#include <string>
#include "logger.h"
#include "json.hpp"

using json = nlohmann::json;

using namespace std;

struct ClientMessage{
    string playerName;
    string packetType;
    json data;

};

struct commandResponse
{
    string name;
    json data;
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
    void clientMessage(ClientMessage message);
    void sendServerMessage(string playerName,string type, json data);
    string recieveServerMessage();

    private:
    mutex TxMtx;
    mutex RxMtx;
};

#endif