#include <string.h>

#include "Measure.hpp"

#include <memory>
#include <string>
#include <stdexcept>
// https://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf
template <typename... Args>
std::string string_format(const std::string &format, Args... args)
{
    int size_s = std::snprintf(nullptr, 0, format.c_str(), args...) + 1; // Extra space for '\0'
    if (size_s <= 0)
    {
        throw std::runtime_error("Error during formatting.");
    }
    auto size = static_cast<size_t>(size_s);
    std::unique_ptr<char[]> buf(new char[size]);
    std::snprintf(buf.get(), size, format.c_str(), args...);
    return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}

std::string Measure::To2String()
{
    tm *t = std::localtime(&time);
    char *str = (char *)calloc(80, 1);
    snprintf(str, 80, "[%d] %d:%d:%d %f %s\n", device_id,
             t->tm_hour, t->tm_min, t->tm_sec,
             temperature, circumstances.c_str());

    return std::string(str);
}

void Measure::ToBinary(unsigned char *&p, size_t &sz)
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
    //  3.1 04 DevId  The Device ID
    //  3.2    Time   The Measure Time
    //  3.3    Tmpr   The Measure Temperature
    //  3.4    StrLen The circumstances string len
    //  N 01 0      Terminator
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //
    // So, the whole message size is data size + 5 bytes

    int data_size = 0;
    data_size += sizeof(device_id);
    data_size += sizeof(time);
    data_size += sizeof(temperature);
    data_size += sizeof(int);
    data_size += circumstances.length() + 1;

    int total_size = data_size;
    // total_size += 5;

    unsigned char *data = (unsigned char *)calloc(total_size, sizeof(unsigned char));

    int i = 0;
    int circumstances_str_len = circumstances.length() + 1;

    memcpy(data + i, &device_id, sizeof(device_id));
    i += sizeof(device_id);

    memcpy(data + i, &time, sizeof(time));
    i += sizeof(time);

    memcpy(data + i, &temperature, sizeof(temperature));
    i += sizeof(temperature);

    memcpy(data + i, &circumstances_str_len, sizeof(circumstances_str_len));
    i += sizeof(circumstances_str_len);

    memcpy(data + i, circumstances.c_str(), circumstances.length());

    p = data;
    sz = total_size;
}

Measure *Measure::FromBinary(unsigned char *data)
{
    Measure *m = new Measure();

    int i = 0;

    memcpy(&(m->device_id), data + i, sizeof(device_id));
    i += sizeof(device_id);

    memcpy(&(m->time), data + i, sizeof(time));
    i += sizeof(time);

    memcpy(&(m->temperature), data + i, sizeof(temperature));
    i += sizeof(temperature);

    int circumstances_str_len = 0;
    memcpy(&circumstances_str_len, data + i, sizeof(circumstances_str_len));
    i += sizeof(circumstances_str_len);

    char circumstances_buf[circumstances_str_len];
    memset(circumstances_buf, '\0', sizeof(circumstances_buf));
    memcpy(circumstances_buf, data + i, circumstances_str_len);

    m->circumstances = std::string(circumstances_buf);

    return m;
}

Measure::Measure(int id, double t, std::string cirq = "") : IMessage(CCCS_TYPE_Measures)
{
    temperature = t;
    device_id = id;
    circumstances = cirq.c_str();

    time = std::time(nullptr); // https://en.cppreference.com/w/cpp/chrono/c/time

    /*
    // const auto now = std::chrono::system_clock::now();  // https://en.cppreference.com/w/cpp/chrono/system_clock/now
    std::time_t result = std::time(nullptr);
    tm* local_time= std::localtime(&result);

    std::cout << std::asctime(local_time)
              << result << " seconds since the Epoch\n";

    //*/
}

Measure::Measure() : IMessage(CCCS_TYPE_Measures)
{
    circumstances = "";
    temperature = 0.0;
    time = {};
}

Measure::~Measure()
{
}
