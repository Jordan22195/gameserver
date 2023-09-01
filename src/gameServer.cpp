#include <iostream>
#include <fstream>
#include <curl/curl.h> // You might need to install a library to handle HTTP requests, like libcurl.
#include <string>
#include <chrono>
#include <thread>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <cstddef>

#include "websocketInterface.h"
#include "zone.h"
#include "commandHandler.h"
#include "logger.h"

using namespace std;




int main() 
{

    Logger::setLogLevel(Logger::LogLevel::TRACE);
    Zone1 zone;

    WebsocketInterface clientInterface;

    CommandHander commandHandler;
    commandHandler.zone = &zone;


  //  DBInterface::go();
   // DBInterface::putPlayerItem("Players", "1", "cobek", clientconfig);

//    const Aws::String tableName("game-table");
//    const Aws::String partitionKey("players");
//    const Aws::String partitionValue("0");
//    const Aws::String attributeKey("WoodcuttingXp");
//    const Aws::String attributeValue("1");



   // DBInterface::updatePlayerItem(tableName, partitionKey, partitionValue,
   //                                  attributeKey,
   //                                  attributeValue, clientconfig);

    while(true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds((50)));

       string clientRequest =  clientInterface.recieveServerMessage();
        if(clientRequest == "") continue;

       commandResponse response = commandHandler.clientActionRequestHandler(clientRequest);
        if(response.name != "")
        {
            clientInterface.sendServerMessage(response.name, response.data);
        }



    }
    return 0;


}
