#include <cstring>
#include <iostream>
#include <unistd.h>

#include "../Library/BinaryWrapper.hpp"
#include "../Library/Measure.hpp"
#include "../Library/Client.hpp"

int main()
{
    int message_count = 5;
    const char *stop_word = "stop";

    sleep(1);


    Client client = *(new Client(8080));
    if (client.Start())
    {
        std::cout << "Emitter is started." << std::endl;
    }
    else
    {
        return 1;
    }

    Measure meaOut = *(new Measure(20040501, 23.1, "Evening temperature"));
    unsigned char *p = nullptr;
    int sz = 0;

    BinaryWrapper::WrapMeasure(meaOut, p, sz);

    
    client.Send(p, sz);
    std::string content = meaOut.To2String();
    std::cout << "Sent: " << content << std::endl;

    client.Send(stop_word);

    if (client.Stop())
    {
        std::cout << "Emitter is completed its job." << std::endl;
    }

    return 0;
}
