#ifndef Included_Measure
#define Included_Measure

#include <ctime>
#include <string>

#include "IMessage.hpp"

class Measure : public IMessage
{
private:
    int device_id;
    std::time_t time;
    double temperature;
    std::string circumstances;
    char *str_circ = nullptr;

    void set_circ(const char *pstr);

    Measure();

public:
    Measure(int id, double t, std::string cirq);
    ~Measure();

    const std::string &Circumstances() const { return circumstances; }
    std::string To2String();

    void ToBinary(unsigned char *&p, size_t &sz);
    static Measure *FromBinary(unsigned char *data);
};

#endif
