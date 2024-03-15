#pragma once

#ifndef CCCS_COL
#define CCCS_COL

#include "../Library/Server.hpp"

class CollectorService
{
private:
    bool ReadIncomingMessage(int socketId, bool &stop_signal);

public:
    Server *server;

    bool Start();

    void Listen();

    CollectorService(int port);
    ~CollectorService();
};

#endif // CCCS_COL
