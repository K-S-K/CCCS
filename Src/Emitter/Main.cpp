#include <cstring>
#include <iostream>
#include <unistd.h>

#include "../Library/BinaryWrapper.hpp"
#include "../Library/CommTerm.hpp"
#include "../Library/Measure.hpp"
#include "../Library/Client.hpp"

int main()
{
    int message_count = 5;

    sleep(2);

    Client client = *(new Client(8080));
    if (client.Start())
    {
        std::cout << "Emitter is started." << std::endl;
    }
    else
    {
        return 1;
    }

    // Send one measure
    {
        Measure msg = *(new Measure(20040501, 23.1, "First measure"));
        unsigned char *p = nullptr;
        int sz = 0;

        BinaryWrapper::WrapMessage(msg, p, sz);

        client.Send(p, sz);
        std::cout << "Sent: " << msg.To2String() << std::endl;
    }

    sleep(1);

    // Send another measure
    {
        Measure msg = *(new Measure(20040501, 23.7, "Second measure"));
        unsigned char *p = nullptr;
        int sz = 0;

        BinaryWrapper::WrapMessage(msg, p, sz);

        client.Send(p, sz);
        std::cout << "Sent: " << msg.To2String() << std::endl;
    }

    sleep(1);

    // Send communication closing signal
    {
        CommTerm msg = *(new CommTerm());
        unsigned char *p = nullptr;
        int sz = 0;

        BinaryWrapper::WrapMessage(msg, p, sz);

        client.Send(p, sz);
        std::cout << "Sent: " << msg.To2String() << std::endl;
    }

    if (client.Stop())
    {
        std::cout << "Emitter is completed its job." << std::endl;
    }

    sleep(1);

    return 0;
}
