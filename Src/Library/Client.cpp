#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

#include "Client.hpp"

Client::Client(int port, std::string host, int buffSize)
{
    Host = host;
    Port = port;

    BuffSize = buffSize;
}

Client::~Client()
{
}

bool Client::Start()
{
    // Create socket
    SocketId = socket(AF_INET,     // versus AF_LOCAL
                      SOCK_STREAM, // reliable, bidirectional
                      0);          // system picks protocol (TCP)
    if (SocketId < 0)
    {
        std::cerr << "Socket creation error" << std::endl;
        return false;
    }

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(Port);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, Host.c_str(), &serv_addr.sin_addr) <= 0)
    {
        std::cerr << "Invalid address / Address not supported" << std::endl;
        return false;
    }

    // Connect to server
    if (connect(SocketId, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cerr << "Connection Failed" << std::endl;
        return false;
    }

    return true;
}

/// @brief Close the connection
bool Client::Stop()
{
    // https://www.gnu.org/software/libc/manual/html_node/Closing-a-Socket.html

    int result = close(SocketId);

    switch (result)
    {
    case 0:
        return true;
        break;

    case EBADF:
        std::cerr << "socket " << SocketId << " is not a valid file descriptor" << std::endl;
        break;

    case ENOTSOCK:
        std::cerr << "socket " << SocketId << " is not a socket." << std::endl;
        break;

    case ENOTCONN:
        std::cerr << "socket " << SocketId << " is not connected." << std::endl;
        break;

    default:
        std::cerr << "Connection Failed" << std::endl;
        break;
    }

    return false;
}

bool Client::Send(const unsigned char *data, size_t size_to_send, std::string comment)
{
    if (data == nullptr || size_to_send == 0)
    {
        return false;
    }

    ssize_t sent_size = SendBinaryContent(SocketId, data, size_to_send, 0);

    if (sent_size == size_to_send)
    {
        std::cout << "Sent " << sent_size << " bytes: " << comment << std::endl;
    }
    else
    {
        std::cerr << "Sent " << sent_size << " bytes instead of " << size_to_send << std::endl;
        return false;
    }

    return true;
}

ssize_t Client::SendBinaryContent(int SocketId, const unsigned char *data, size_t size_to_send, int flags)
{
    size_t size_sent_total = 0;
    ssize_t size_sent_last;

    while (size_sent_total < size_to_send)
    {
        size_t size_to_send_now = size_to_send - size_sent_total;
        /*
        if (size_to_send_now > 3)
        {
            size_to_send_now = 3;
        }
        //*/
        size_sent_last = send(SocketId, data + size_sent_total, size_to_send_now, flags);
        if (size_sent_last == -1)
        {
            break;
        }
        size_sent_total += size_sent_last;
    }

    return (size_sent_last == -1 ? -1 : size_sent_total);
}

bool Client::Send(const char *buffer, bool echo)
{
    size_t size_to_send = strlen(buffer);
    ssize_t sent_size = send(SocketId, buffer, size_to_send, 0);

    if (sent_size == size_to_send)
    {
        std::cout << "Sent " << sent_size << " bytes: " << buffer << std::endl;
    }
    else
    {
        std::cerr << "Sent " << sent_size << " bytes instead of " << size_to_send << std::endl;
        return false;
    }

    if (echo)
    {
        /* get confirmation echoed from server and print */
        char buffer[BuffSize + 1];
        memset(buffer, '\0', sizeof(buffer));
        ssize_t recv_size = recv(SocketId, buffer, sizeof(buffer), 0);
        if (recv_size > 0)
        {
            std::cout << "Recv " << recv_size << " bytes: " << buffer << std::endl;
        }
    }

    return true;
}