#include "GetInputHandler.h"

namespace OS3CS
{
	GetInputHandler::GetInputHandler(void)
	{
	}


	GetInputHandler::~GetInputHandler(void)
	{
	}

	void GetInputHandler::Process(Socket* socket, string response)
	{
		try
		{
			vector<string> segments = vector<string>();
			if (!FormatCommandPath(response, segments, 2))
			{
				cout << "Syntax error: use put [remote file] [local dir]" << endl;
				return;
			}
			char buffer[MAXBUFFERSIZE+1];
			int bytesToRead, bytesRead, fileSize;
			
			TransferManager *manager = new TransferManager();
			manager->SendFile(socket,segments[0]);
			delete manager;
		}
		catch (exception ex)
		{
			cout << "Something went wrong..." << endl;
		}
	}

	InputHandler* GetInputHandler::Clone()
	{
		return new GetInputHandler();
	}
}