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
			cout << "Created ClientSocket\r\n";
		
			listenToSocket(s);
        
			string szLine;
			char response[256];
			while (getline(cin, szLine))
			{
				s->writeline(szLine);
				while (s->readline(response, 256) > 0)
				{
					cout << response << endl;
				}
			}

			delete s;
		}
		catch (runtime_error& ex)
		{
			delete s;
			throw(ex);
		}
    }

    void Client::listenToSocket(Socket* socket)
    {
        char line[256 + 1];

        while (socket->readline(line, 257) > 0)
        {
            cout << line << endl;
        }
    }
}
