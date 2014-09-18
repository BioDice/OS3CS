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

		char line[257];
		while (socket->readline(line, 256) > 0)
		{
			cout << line << endl;
		}
	}

	InputHandler* RespInputHandler::Clone()
	{
		return new RespInputHandler();
	}
}