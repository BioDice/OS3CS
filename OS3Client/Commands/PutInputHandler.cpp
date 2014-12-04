#include "PutInputHandler.h"

namespace OS3CS
{
	PutInputHandler::PutInputHandler(void)
	{
	}


	PutInputHandler::~PutInputHandler(void)
	{
	}

	void PutInputHandler::Process(Socket* socket, string response)
	{
		try
		{
			vector<string> segments = vector<string>();
			if (!FormatCommandPath(response, segments, 2))
			{
				cout << "Syntax error: use put [remote dir] [local file]" << endl;
				return;
			}
			socket->writeline(response);
			TransferManager* manager = new TransferManager();
			manager->SendFile(socket, segments[1]);
			delete manager;
			char line[MAXPATH];
			while (socket->readline(line, MAXPATH) > 0)
			{
				cout << line << endl;
			}
		}
		catch (exception ex)
		{
			cout << "Something went wrong..." << endl;
		}
	}

	InputHandler* PutInputHandler::Clone()
	{
		return new PutInputHandler();
	}
}