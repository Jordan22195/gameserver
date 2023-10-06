#include "websocketInterface.h"


WebsocketInterface::WebsocketInterface()
{
    Logger::TRACE("websocketInterface::websocketInterface() %p", this);

    string ip = "0.0.0.0";
    uint16_t port = 50005;
    txSocket = new udpSocket(ip, port);
    Logger::TRACE("txSocket = new udpSocket(ip, port); %p", this);
    rxSocket = new udpSocket(ip, 50004, true);
    Logger::TRACE("rxSocket = new udpSocket(ip, 50004, true); %s", this);

    string testName = "aaaa";
    string testData = "bbbbb";

    sendServerMessage(testName, "TEST", testData);

}


void WebsocketInterface::sendServerMessage(string playerName, string type, json data)
{
    Logger::TRACE("websocketInterface::sendServerMessage(json playerName, json data) %p", this);
    lock_guard<std::mutex> lock(TxMtx);
    json j;
    j["clientName"] = playerName;
    j["type"] = type;
    j["data"] = data;
    string packet = j.dump();
    Logger::INFO("Sent Packet: %s", packet.c_str());
    txSocket->stringSend(packet);
}

string WebsocketInterface::recieveServerMessage()
{
    Logger::TRACE("websocketInterface::recieveServerMessage() %p", this);

    lock_guard<std::mutex> lock(RxMtx);
    string s = rxSocket->rxClientMessage();

    return s;


}

void WebsocketInterface::clientMessage(ClientMessage message)
{
    sendServerMessage(message.playerName, message.packetType, message.data);
}

void WebsocketInterface::clientActionResponse(commandResponse resp)
{
    Logger::TRACE(" WebsocketInterface::clientActionResponse(commandResponse resp) %p", this);

    string type = "COMMAND_RESPONSE";
    sendServerMessage(resp.name, type, resp.data);
}

