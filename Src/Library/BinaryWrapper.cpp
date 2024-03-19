
#include <string.h>

#include "BinaryWrapper.hpp"

BinaryWrapper::BinaryWrapper()
{
}

BinaryWrapper::~BinaryWrapper()
{
}

void BinaryWrapper::WrapMessage(IMessage *input, unsigned char *&p, int &sz)
{
    unsigned short inner_data_size_label;
    size_t inner_data_size = 0;
    unsigned char *inner_data_content;
    input->ToBinary(inner_data_content, inner_data_size);

    inner_data_size_label = inner_data_size;

    // The binary data structure is:
    //
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // No   Sz Type   Comment
    // ~~~~|~~|~~~~~~|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //  0   01 Label  CCCS_LABEL - Check if it is our message
    //  1   01 TypeID Id of the data type, from enum CCCS_TYPES
    //  2   02 Size   The size of the serialized data.
    //  3   XX Data   The transferring data
    //  N   01 1      Terminator

    int outer_data_size = inner_data_size + 5;
    unsigned char *outer_data_content = (unsigned char *)
        calloc(outer_data_size, sizeof(unsigned char));

    int i = 0;

    outer_data_content[i] = CCCS_LABEL;
    i += 1;

    outer_data_content[i] = input->TypeSign();
    i += 1;

    memcpy(outer_data_content + i, &inner_data_size_label, sizeof(inner_data_size_label));
    i += sizeof(inner_data_size_label);

    memcpy(outer_data_content + i, inner_data_content, inner_data_size);
    i += inner_data_size;

    outer_data_content[i] = 1;

    p = outer_data_content;
    sz = outer_data_size;
}
