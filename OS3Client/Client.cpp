#include "Client.h"
#include "../shared/Socket.h"

namespace OS3CS
{
    Client::Client(void)
    {
		inputFactory = new ClientFactory();
		inputFactory->Initialize();
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
			cout << "Created ClientSocket" << endl;
		
			listenToSocket(s);
        
			string response;
			while (getline(cin, response))
			{
				vector<string> segments = vector<string>();
				StrSplit(response, segments, ' ');

				// Converts the characters to lower case
				for (int i = 0; i < segments[0].length(); i++)
					segments[0][i] = tolower(segments[0][i]);

				InputHandler *inputHandler = inputFactory->CreateHandler(segments[0]);
				if (inputHandler != NULL)
					inputHandler->Process(s, response);
				else
					inputFactory->CreateHandler("resp")->Process(s, response);
				delete inputHandler;
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
