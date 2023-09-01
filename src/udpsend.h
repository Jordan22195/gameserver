#ifndef UDP_SEND_
#define UDP_SEND_

#include <iostream>
#include <string>
#include <string.h>

#include <arpa/inet.h> // htons, inet_addr
#include <netinet/in.h> // sockaddr_in
#include <sys/types.h> // uint16_t
#include <sys/socket.h> // socket, sendto
using namespace std;
class udpSocket
{
    public:
    udpSocket(std::string ip, uint16_t port, bool bind = false);
    ~udpSocket();
    int send( void * data, int lengthInBytes);
    int stringSend( string s);
    int recieve(void * buffer, int bufferSize);
    void close();
    string rxClientMessage();
    int getHeaderSize();
    private:
    sockaddr_in addr;
    int sock;

};

#endif