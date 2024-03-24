#include "../Library/ELog/easylogging++.h"

#include "CollectorService.hpp"

INITIALIZE_EASYLOGGINGPP

void ConfigureLog()
{
    el::Configurations defaultConf;
    defaultConf.setToDefault();

    defaultConf.set(el::Level::Info, el::ConfigurationType::ToFile, "true");
    defaultConf.set(el::Level::Info, el::ConfigurationType::Format, "%msg");
    defaultConf.set(el::Level::Info, el::ConfigurationType::ToStandardOutput, "true");
    defaultConf.set(el::Level::Info, el::ConfigurationType::Filename, "collector.log.info");

    defaultConf.set(el::Level::Debug, el::ConfigurationType::ToFile, "true");
    defaultConf.set(el::Level::Debug, el::ConfigurationType::ToStandardOutput, "false");
    defaultConf.set(el::Level::Debug, el::ConfigurationType::Filename, "collector.log.debug");
    defaultConf.set(el::Level::Debug, el::ConfigurationType::Format, "%datetime [%func] [%loc] %msg");

    el::Loggers::reconfigureLogger("default", defaultConf);
}

void MessageAccepted(IMessage *msg)
{
    if (msg == nullptr)
    {
        LOG(INFO) << "Empty message accepted";

        return;
    }

    LOG(DEBUG) << "New message: " << msg->To2String();
    LOG(INFO) << "New message: " << msg->To2String();
}

int main()
{
    ConfigureLog();

    LOG(DEBUG) << "Collector started";
    LOG(INFO) << "Collector started";

    CollectorService collector = *(new CollectorService(8080));

    collector.SubscribeToAcceptedMessages(MessageAccepted);

    sleep(1);

    if (!collector.Start())
    {
        return 1;
    }

    return 0;
}
