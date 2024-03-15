#pragma once

#ifndef CCCS_SRV
#define CCCS_SRV

#include <string>
#include <cstring>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

class Server
{
private:
    struct sockaddr_in address;

public:
    int Port;
    int SocketId;
    int BuffSize;

    Server(int port, int buffSize = 2048);
    ~Server();

    bool Start(void);
    bool Stop();
    bool CloseSocket(int socketId);
    int AcceptIncomingConnection();

    bool ReadBinaryContent(int socketId, unsigned char *data, size_t size_to_read);
    bool Read(int socketId, unsigned short &value);
    bool Read(int socketId, unsigned char &value);
};

#endif // CCCS_SRV
