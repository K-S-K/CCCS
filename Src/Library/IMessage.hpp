#pragma once
#include <string>

#define KSK_LABEL 205

enum KSK_TYPES
{
    KSK_TYPE_Measures = 1
};

class IMessage
{
private:
    unsigned char type_sign = 0;

public:
    unsigned char TypeSign() { return type_sign; }
    virtual std::string To2String() { return "Unoverriden"; }

    IMessage(unsigned char t) { type_sign = t; }
    ~IMessage() { ; }
};
