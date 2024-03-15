#ifndef CCCS_DISCONNECT
#define CCCS_DISCONNECT

#include <ctime>

#include "IMessage.hpp"

class CommTerm : public IMessage
{
private:
    std::time_t time;

public:
    CommTerm(/* args */);
    ~CommTerm();

    std::string To2String();

    void ToBinary(unsigned char *&p, size_t &sz);
    static CommTerm *FromBinary(unsigned char *data);
};

#endif // CCCS_DISCONNECT
