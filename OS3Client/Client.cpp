#include "stdafx.h"
#include "Client.h"
#include "../shared/Socket.h"

namespace OS3CS
{
    Client::Client(void)
    {

    }


    Client::~Client(void)
    {
    }

    void Client::connect(const char* adress, int port)
    {
        Socket * s = NULL;

        try
        {
            s = new ClientSocket(adress,port);
        }
        catch (runtime_error& ex)
        {
            delete s;
            throw(ex);
        }
        listenToSocket(s);
        cout << "Created ClientSocket";
        delete s;
    }

    void Client::listenToSocket(Socket* socket)
    {
        char line[256 + 1];

        while (socket->readline(line, 256) > 0)
        {
            cout << line << endl;
        }
    }
}
