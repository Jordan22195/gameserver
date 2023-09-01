#include "udpsend.h"
#include <unistd.h>
#include <poll.h>
#include <vector>

#include "logger.h"
using namespace std;
udpSocket::udpSocket(std::string ip, uint16_t port, bool rx)
{
    Logger::TRACE("udpSocket::udpSocket(std::string ip, uint16_t port, bool rx) %p", this);
    sock = ::socket(AF_INET, SOCK_DGRAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip.c_str());
    if (addr.sin_addr.s_addr == -1)
    {
        std::cout<< "invalid hostname : " << ip.c_str() << std::endl;
    }

    if(rx)
        if (bind(sock, (struct sockaddr *) &addr, sizeof(addr)) != 0)
            cout << "SOCKET BIND FAILURE" << endl;

}

udpSocket::~udpSocket()
{
    Logger::TRACE("udpSocket::~udpSocket() %p", this);
    close();
}

int udpSocket::stringSend( string s)
{
    Logger::TRACE("udpSocket::stringSend( string s) %s", this);

    cout << "sending to client" << endl;
    const char * data = s.c_str();
    int len = s.length();
    cout << "packet size " << len << endl;
    char buffer[len+4];
    memcpy(&buffer, &len, 4);
    memcpy(&buffer[4], data, len);
    cout << "memcpy" << endl;

    int ret = send(&buffer[0], len);

    cout << "sent" <<endl;
    return ret;

}
int udpSocket::send( void * data, int lengthInBytes)
{
    Logger::TRACE("udpSocket::send( void * data, int lengthInBytes) %p", this);
    int n_bytes = ::sendto(sock, data, lengthInBytes, 0, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));

    return n_bytes;

}

string udpSocket::rxClientMessage()
{
    Logger::TRACE("udpSocket::rxClientMessage()  %p", this);
    int messageSize  = getHeaderSize();
    if (messageSize <= 0) return "";
    else
    {
        messageSize += 4;
    }
    cout << "client message size: " << messageSize << endl;

    char buffer[messageSize];
    recieve(&buffer[0], messageSize);
    string out (&buffer[4]);
    return out;
}

//return > 0 if data is recieved
int udpSocket::getHeaderSize()
{


    Logger::TRACE("udpSocket::getHeaderSize()  %p", this);

    struct pollfd fd;
    int ret;
    socklen_t len = sizeof(addr);
    uint32_t size = 0;
    int c = 0;

    fd.fd = sock; // your socket handler 
    fd.events = POLLIN;
    ret = 1;//poll(&fd, 1, 1); // 1ms for timeout
    switch (ret) 
    {
        case -1:
            // Error
            break;
        case 0:
            // Timeout 
            break;
        default:
           c =  recvfrom(sock, &size, 4,  
                MSG_PEEK, (struct sockaddr *) &addr, 
                &len);
            break;
    }
    cout << "found from peek: " << size << endl;
    return size;
}

//return > 0 if data is recieved
int udpSocket::recieve(void * buffer, int bufferSize)
{

   Logger::TRACE("udpSocket::recieve(void * buffer, int bufferSize)  %p", this);

    struct pollfd fd;
    int ret;
    socklen_t len = sizeof(addr);

    int c = 0;

    fd.fd = sock; // your socket handler 
    fd.events = POLLIN;
    ret = 1;//poll(&fd, 1, 1); // 1ms for timeout
    switch (ret) 
    {
        case -1:
            // Error
            break;
        case 0:
            // Timeout 
            break;
        default:
           c =  recvfrom(sock, (char *)buffer, bufferSize,  
                MSG_WAITALL, (struct sockaddr *) &addr, 
                &len);
            break;
    }
    return ret;
}


void udpSocket::close()
{
    Logger::TRACE("udpSocket::close())  %p", this);
    ::close(sock);

}