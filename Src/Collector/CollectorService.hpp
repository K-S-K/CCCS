#pragma once

#ifndef CCCS_COL
#define CCCS_COL

#include "../Library/IMessage.hpp"
#include "../Library/Server.hpp"

class CollectorService
{
private:
    MsgTransferFn pfnMessageAccepted = nullptr;

    void NotifySubscribers(IMessage *msg);
    bool ReadIncomingMessage(int socketId, bool &stop_signal);

public:
    Server *server;

    bool Start();

    void Listen();

    void SubscribeToAcceptedMessages(MsgTransferFn pfn);

    CollectorService(int port);
    ~CollectorService();
};

#endif // CCCS_COL
