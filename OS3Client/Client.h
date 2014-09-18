#pragma once

#include <string>
#include "../Shared/Socket.h"
#include "../Shared/Globals.h"
#include "../Shared/SocketException.h"
#include "../Shared/InputHandler.h"
#include "../Shared/InputFactory.h"
#include "ClientFactory.h"
using namespace std;

namespace OS3CS
{
    class Client
    {
	private:
		InputFactory *inputFactory;

    public:
        Client(void);
        ~Client(void);

        void handle(Socket *socket);
        void connect(const char* adress, int port);
        void Client::listenToSocket(Socket* socket);
    };
}
