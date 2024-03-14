#include "Measure.hpp"

#ifndef BINARY_WR
#define BINARY_WR

// #define KSK_LABEL 205

// enum KSK_TYPES
// {
//     KSK_TYPE_Measures = 1
// };



/// @brief The stateless wrapper for binary classes serialization
class BinaryWrapper
{
private:
    /* data */
public:
    BinaryWrapper(/* args */);
    ~BinaryWrapper();

    static void WrapMeasure(Measure input, unsigned char *&p, int &sz);
    static Measure *FromBinary(unsigned char *data);
};

#endif