#ifndef TCP_SOCKET_SERVER_H
#define TCP_SOCKET_SERVER_H


#include "Const.h"
#include <sys/socket.h>

class SocketServer {
public:
    int listenfd, acceptfd;
    bool isCreated;
    sockaddr_un addr_server;
    char socket_name[108]; // 108 sun_path length max

    SocketServer();

    bool Create();
    bool Accept();
    bool Bind();
    bool Listen();
    void Close();

    int sendData(void *inData, size_t size);
    bool send(void* inData, size_t size);

    int recvData(void *outData, size_t size);
    size_t receive(void* outData);
};


#endif
