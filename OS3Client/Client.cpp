#include "Client.h"

using namespace std;

namespace OS3CS
{
    Client::Client(void)
    {
    }


    Client::~Client(void)
    {
    }

	void Client::listenToSocket(Socket* socket)
    {
        char line[256 + 1];

        while (socket->readline(line, 256) > 0 )
        {
            cout << line << endl;
        }
    }

    void Client::connect(const char* adress, int port)
    {
        Socket * socket = NULL;

        try
        {
            socket = new ClientSocket(adress,port);
        }
        catch (runtime_error& ex)
        {
            delete socket;
            throw(ex);
        }

        listenToSocket(socket);

		string socketLine;

		while(getline(cin,socketLine))
		{
			if(socketLine.size()==0)
				continue;
			
			socket->writeline(socketLine);
			
			//cout << socketLine << endl;
		}
        cout << "Created ClientSocket";
		socket->close();
        delete socket;
    }
}
