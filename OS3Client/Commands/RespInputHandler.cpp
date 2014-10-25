#include "RespInputHandler.h"

namespace OS3CS
{
	RespInputHandler::RespInputHandler(void)
	{
	}


	RespInputHandler::~RespInputHandler(void)
	{
	}

	void RespInputHandler::Process(Socket* socket, string response)
	{
		socket->writeline(response);

		char line[MAXPATH+1];
		while (socket->readline(line, MAXPATH) > 0)
		{
			cout << line << endl;
		}
	}

	InputHandler* RespInputHandler::Clone()
	{
		return new RespInputHandler();
	}
}