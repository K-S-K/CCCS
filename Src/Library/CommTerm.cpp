#include "CommTerm.hpp"
#include <string.h>

std::string CommTerm::To2String()
{
    tm *t = std::localtime(&time);
    char *str = (char *)calloc(80, 1);
    snprintf(str, 80, "Disconnect %d:%d:%d\n",
             t->tm_hour, t->tm_min, t->tm_sec);

    return std::string(str);
}


void CommTerm::ToBinary(unsigned char *&p, size_t &sz)
{
    // The binary data structure is:
    //
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // No   Sz Type   Comment
    // ~~~~|~~|~~~~~~|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //  0   01 Label  CCCS_LABEL - Check if it is our message
    //  1   01 TypeID Id of the data type, from enum CCCS_TYPES
    //  2   02 Size   The size of the serialized data.
    //  3   XX Data   The transferring data
    // ~~~~|~~|~~~~~~|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //  3.2    Time   The Measure Time
    //  N 01 0      Terminator
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //
    // So, the whole message size is data size + 5 bytes

    int data_size = 0;
    data_size += sizeof(time);

    int total_size = data_size;

    unsigned char *data = (unsigned char *)calloc(total_size, sizeof(unsigned char));

    int i = 0;

    memcpy(data + i, &time, sizeof(time));
    i += sizeof(time);

    p = data;
    sz = total_size;
}

CommTerm *CommTerm::FromBinary(unsigned char *data)
{
    CommTerm *m = new CommTerm();

    int i = 0;

    memcpy(&(m->time), data + i, sizeof(time));
    i += sizeof(time);

    return m;
}

CommTerm::CommTerm() : IMessage(CCCS_TYPE_Conn_Term)
{
    time = std::time(nullptr);
}

CommTerm::~CommTerm()
{
}