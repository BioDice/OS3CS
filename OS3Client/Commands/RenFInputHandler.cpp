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
		StrSplit(response, segments, ' ');
		if (segments.size() != 3)
		{
			cout << "Syntaxt error: ren [oldfile] [newfile]" << endl;
			return;
		}

		socket->writeline(response);

		char line[257];
		while (socket->readline(line, 256) > 0)
		{
			cout << line << endl;
		}
	}

	InputHandler* RenFInputHandler::Clone()
	{
		return new RenFInputHandler();
	}
}