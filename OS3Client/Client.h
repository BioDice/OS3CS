#pragma once

#include <string>
#include "../Shared/Socket.h"
using namespace std;

namespace OS3CS
{
    class Client
    {
    public:
        Client(void);
        ~Client(void);

        void handle(Socket *socket);
        void connect(const char* adress, int port);
        void Client::listenToSocket(Socket* socket);
    };
}
