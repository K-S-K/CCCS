#include "Measure.hpp"
#include "CommTerm.hpp"
#include "IMessage.hpp"

#ifndef BINARY_WR
#define BINARY_WR

/// @brief The stateless wrapper for binary classes serialization
class BinaryWrapper
{
private:
public:
    BinaryWrapper();
    ~BinaryWrapper();

    static void WrapMessage(IMessage *input, unsigned char *&p, int &sz);
};

#endif
