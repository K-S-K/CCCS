#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

#include "ELog/easylogging++.h"

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
        LOG(DEBUG) << "Socket creation error";
        return false;
    }

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(Port);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, Host.c_str(), &serv_addr.sin_addr) <= 0)
    {
        LOG(DEBUG) << "Invalid address / Address not supported";
        return false;
    }

    // Connect to server
    if (connect(SocketId, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        LOG(DEBUG) << "Connection Failed";
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
        LOG(DEBUG) << "socket " << SocketId << " is not a valid file descriptor";
        break;

    case ENOTSOCK:
        LOG(DEBUG) << "socket " << SocketId << " is not a socket.";
        break;

    case ENOTCONN:
        LOG(DEBUG) << "socket " << SocketId << " is not connected.";
        break;

    default:
        LOG(DEBUG) << "Connection Failed";
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
        // std::cout << "Sent " << sent_size << " bytes: " << comment << std::endl;
    }
    else
    {
        LOG(DEBUG) << "Sent " << sent_size << " bytes instead of " << size_to_send;
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
        LOG(DEBUG) << "Sent " << sent_size << " bytes: " << buffer;
    }
    else
    {
        LOG(DEBUG) << "Sent " << sent_size << " bytes instead of " << size_to_send;
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
            LOG(DEBUG) << "Recv " << recv_size << " bytes: " << std::string(buffer);
        }
    }

    return true;
}