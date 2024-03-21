#include <cstring>
#include <iostream>
#include <unistd.h>

#include "../Library/ELog/easylogging++.h"

#include "../Library/BinaryWrapper.hpp"
#include "../Library/CommTerm.hpp"
#include "../Library/Measure.hpp"
#include "../Library/Client.hpp"

INITIALIZE_EASYLOGGINGPP

void ConfigureLog()
{
    el::Configurations defaultConf;
    defaultConf.setToDefault();

    defaultConf.set(el::Level::Info, el::ConfigurationType::ToFile, "true");
    defaultConf.set(el::Level::Info, el::ConfigurationType::Format, "%msg");
    defaultConf.set(el::Level::Info, el::ConfigurationType::ToStandardOutput, "false");
    defaultConf.set(el::Level::Info, el::ConfigurationType::Filename, "emitter.log.info");

    defaultConf.set(el::Level::Debug, el::ConfigurationType::ToFile, "true");
    defaultConf.set(el::Level::Debug, el::ConfigurationType::ToStandardOutput, "false");
    defaultConf.set(el::Level::Debug, el::ConfigurationType::Filename, "emitter.log.debug");
    defaultConf.set(el::Level::Debug, el::ConfigurationType::Format, "%datetime [%func] [%loc] %msg");

    el::Loggers::reconfigureLogger("default", defaultConf);
}

int main()
{
    ConfigureLog();

    LOG(DEBUG) << "Emitter started";
    LOG(INFO) << "Emitter started";

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
        Measure *msg = new Measure(20040501, 23.1, "First measure");
        unsigned char *p = nullptr;
        int sz = 0;

        BinaryWrapper::WrapMessage(msg, p, sz);

        client.Send(p, sz);
        std::cout << "Sent: " << msg->To2String() << std::endl;
    }

    sleep(1);

    // Send another measure
    {
        Measure *msg = new Measure(20040501, 23.7, "Second measure");
        unsigned char *p = nullptr;
        int sz = 0;

        BinaryWrapper::WrapMessage(msg, p, sz);

        client.Send(p, sz);
        std::cout << "Sent: " << msg->To2String() << std::endl;
    }

    sleep(1);

    // Send communication closing signal
    {
        CommTerm *msg = new CommTerm();
        unsigned char *p = nullptr;
        int sz = 0;

        BinaryWrapper::WrapMessage(msg, p, sz);

        client.Send(p, sz);
        std::cout << "Sent: " << msg->To2String() << std::endl;
    }

    if (client.Stop())
    {
        std::cout << "Emitter is completed its job." << std::endl;
    }

    sleep(1);

    return 0;
}
