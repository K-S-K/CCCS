#include "CollectorService.hpp"

#include "../Library/BinaryWrapper.hpp"
#include "../Library/CommTerm.hpp"
#include "../Library/Measure.hpp"
#include "../Library/Server.hpp"

bool CollectorService::Start()
{
    if (!server->Start())
    {
        return false;
    }

    std::cout << "Collector is started." << std::endl;
    std::cout << "Listening on port " << server->Port << std::endl;
    std::cout << "Obtained SocketId " << server->SocketId << std::endl;

    Listen();

    return true;
}

void CollectorService::Listen()
{
    const char *stop_word = "stop";
    const char *stop_confirm = "stopped";
    bool stop_signal = false;

    // Listen until the stop signal
    while (!stop_signal)
    {
        int socketId = server->AcceptIncomingConnection();

        std::cout << "Accepted incoming connection, socketId " << socketId << std::endl;

        while (!stop_signal)
        {
            unsigned char project_sign = 0;

            if (!server->Read(socketId, project_sign))
            {
                std::cout << "Can't read from socketId " << socketId << ". Close it." << std::endl;
                break;
            }

            if (project_sign != CCCS_LABEL)
            {
                std::cout << "The message prefix not recognized.  Close it." << std::endl;
                break;
            }

            if (!ReadIncomingMessage(socketId, stop_signal))
            {
                break;
            }
        }

        send(socketId, stop_confirm, sizeof(stop_confirm), 0); // echo as confirmation

        std::cout << "Close incoming connection, socketId " << socketId << std::endl;
        server->CloseSocket(socketId); // break connection
    }

    if (server->Stop())
    {
        std::cout << "Collector is completed its job." << std::endl;
    }
}

void CollectorService::NotifySubscribers(IMessage *msg)
{
    MsgTransferFn pfn = pfnMessageAccepted;

    if (pfn != nullptr)
    {
        pfn(msg);
    }
}

bool CollectorService::ReadIncomingMessage(int socketId, bool &stop_signal)
{
    int count = 0;
    size_t sz = 0;
    IMessage *msg = nullptr;

    unsigned char type_sign = 0;
    unsigned short data_size = 0;

    // read the type sign
    if (!server->Read(socketId, type_sign))
    {
        std::cout << "Can't read a type sign from socketId " << socketId << ". Close it." << std::endl;
        {
            return false;
        };
    }

    // Read the content size
    if (!server->Read(socketId, data_size))
    {
        std::cout << "Can't read the content size from socketId " << socketId << ". Close it." << std::endl;
        return false;
    }

    // Read the content itself

    switch (type_sign)
    {
    case CCCS_TYPE_Measures:
    {
        sz = data_size + 1;
        unsigned char buffer[sz];
        memset(buffer, '\0', sz);
        server->ReadBinaryContent(socketId, buffer, sz);

        Measure meaIn = *(Measure::FromBinary(buffer));

        std::cout << "Readen from socketId " << socketId << ": " << meaIn.To2String() << std::endl;

        NotifySubscribers(&meaIn);
    }
    break;

    case CCCS_TYPE_Conn_Term:
    {
        sz = data_size + 1;
        unsigned char buffer[sz];
        memset(buffer, '\0', sz);
        server->ReadBinaryContent(socketId, buffer, sz);

        CommTerm meaIn = *(CommTerm::FromBinary(buffer));

        std::cout << "Readen from socketId " << socketId << ": " << meaIn.To2String() << std::endl;

        NotifySubscribers(&meaIn);

        stop_signal = true;
    }
    break;

    default:
        std::cout << "Unknuwn command: " << (int)type_sign << std::endl;
        break;
    }

    // std::cout << "Converted " << socketId << ": " << msg->To2String() << std::endl;

    return true;
}

void CollectorService::SubscribeToAcceptedMessages(MsgTransferFn pfn)
{
    pfnMessageAccepted = pfn;
}

CollectorService::CollectorService(int port)
{
    server = new Server(port);
}

CollectorService::~CollectorService()
{
}
