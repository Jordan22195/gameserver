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
#include "commandHandler.h"
#include "logger.h"

using namespace std;




int main() 
{

    Logger::setLogLevel(Logger::LogLevel::TRACE);
  
    

    WebsocketInterface clientInterface;


    CommandHander commandHandler;
    commandHandler.clientInterface = &clientInterface;


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

   commandHandler.startPlayerUpdateThread();

    while(true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds((50)));

        string clientRequest =  clientInterface.recieveServerMessage();
        if(clientRequest != "")
        {
            commandHandler.clientActionRequestHandler(clientRequest);
        }

        
        

        Logger::TRACE("step");

    }
    return 0;


}
