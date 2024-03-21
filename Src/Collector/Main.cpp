#include "CollectorService.hpp"

void MessageAccepted(IMessage *msg)
{
    if (msg == nullptr)
    {
        std::cout << "Empty message accepted" << std::endl;
        return;
    }

    std::cout << "New message: " << msg->To2String() << std::endl;
}

int main()
{
    CollectorService collector = *(new CollectorService(8080));

    collector.SubscribeToAcceptedMessages(MessageAccepted);

    sleep(1);

    if (!collector.Start())
    {
        return 1;
    }

    return 0;
}
