#include "RenFInputHandler.h"

namespace OS3CS
{
	RenFInputHandler::RenFInputHandler(void)
	{
	}


	RenFInputHandler::~RenFInputHandler(void)
	{
	}

	void RenFInputHandler::Process(Socket* socket, string response)
	{
		vector<string> segments = vector<string>();
		if (!FormatCommandPath(response, segments, 2))
		{
			cout << "Syntax error: use ren [remote file] [local file]" << endl;
			return;
		}
		socket->writeline(response);

		char line[MAXPATH+1];
		while (socket->readline(line, MAXPATH) > 0)
		{
			cout << line << endl;
		}
	}

	InputHandler* RenFInputHandler::Clone()
	{
		return new RenFInputHandler();
	}
}