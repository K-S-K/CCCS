class Client
{
private:
    int Port;
    int SocketId;
    std::string Host;

    int BuffSize;

    ssize_t SendBinaryContent(int SocketId,const unsigned char *data, size_t size_to_send, int flags = 0);

public:
    Client(int port, std::string host = "127.0.0.1", int buffSize = 2048);
    ~Client();

    bool Start();
    bool Stop();
    bool Send(const char *message, bool echo = true);
    bool Send(const unsigned char *data, size_t size_to_send, std::string comment = "");
};