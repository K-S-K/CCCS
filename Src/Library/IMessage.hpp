#pragma once

#include <string>

#ifndef CCCS_MSG
#define CCCS_MSG

#define CCCS_LABEL 205

enum CCCS_TYPES
{
    CCCS_TYPE_Measures = 1,
    CCCS_TYPE_Conn_Term = 2
};

class IMessage
{
private:
    unsigned char type_sign = 0;

public:
    unsigned char TypeSign() { return type_sign; }
    virtual std::string To2String()
    {
        char *str = (char *)calloc(80, 1);
        snprintf(str, 80, "Message type: %d\n", type_sign);

        return std::string(str);
    }
    
    virtual void ToBinary(unsigned char *&p, size_t &sz) = 0;

    IMessage(unsigned char t) { type_sign = t; }
    ~IMessage() { ; }
};

/// @brief Function type definition for the message transfer
typedef void (*MsgTransferFn)(IMessage *);

#endif // CCCS_MSG
