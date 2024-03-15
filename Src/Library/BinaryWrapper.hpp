#include "Measure.hpp"

#ifndef BINARY_WR
#define BINARY_WR

/// @brief The stateless wrapper for binary classes serialization
class BinaryWrapper
{
private:
public:
    BinaryWrapper();
    ~BinaryWrapper();

    static void WrapMeasure(Measure input, unsigned char *&p, int &sz);
    static Measure *FromBinary(unsigned char *data);
};

#endif
