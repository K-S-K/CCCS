#include "Measure.hpp"
#include "CommTerm.hpp"

#ifndef BINARY_WR
#define BINARY_WR

/// @brief The stateless wrapper for binary classes serialization
class BinaryWrapper
{
private:
public:
    BinaryWrapper();
    ~BinaryWrapper();

    static void WrapMessage(Measure input, unsigned char *&p, int &sz);
    static void WrapMessage(CommTerm input, unsigned char *&p, int &sz);
};

#endif
