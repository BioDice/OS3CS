#include "Client.h"

namespace OS3CS
{
    Client::Client(void)
    {
		inputFactory = new ClientFactory();
		inputFactory->Initialize();
    }


    Client::~Client(void)
    {
		delete inputFactory;
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
				if (response.size() == 0)
				continue;

				vector<string> segments = vector<string>();
				StrSplit(response, segments, ' ');

				if (segments.size() > 0)
				{
					// Converts the characters to lower case
					for (int i = 0; i < segments[0].length(); i++)
						segments[0][i] = tolower(segments[0][i]);

					InputHandler *inputHandler = inputFactory->CreateHandler(segments[0]);
					if (inputHandler != NULL)
					{
						try
						{
							inputHandler->Process(s, response);
						}
						catch (const char* ex)
						{
							cout << ex << endl;
						}
					 }
					
					else
						inputFactory->CreateHandler("resp")->Process(s, response);
					delete inputHandler;
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
		char line[MAXPATH + 1];

        while (socket->readline(line, MAXPATH) > 0)
        {
            cout << line << endl;
        }
    }
}
