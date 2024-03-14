class Server
{
private:
    struct sockaddr_in address;

public:
    int Port;
    int SocketId;
    int BuffSize;

    Server(int port, int buffSize = 2048);
    ~Server();

    bool Start(void);
    bool Stop();
    bool CloseSocket(int socketId);
    int AcceptIncomingConnection();

    bool ReadBinaryContent(int socketId, unsigned char *data, size_t size_to_read);
    bool Read(int socketId, unsigned short &value);
    bool Read(int socketId, unsigned char &value);
};
