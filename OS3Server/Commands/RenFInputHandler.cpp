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
		char buffer[MAXBUFFERSIZE + 1];

		vector<string> segments = vector<string>();
		if (!FormatCommandPath(response, segments, 2))
		{
			cout << "Syntax error: use ren [remote file] [local file]" << endl;
			return;
		}
		
		int result;
		result= rename(segments[1].c_str(), segments[2].c_str());
		if ( result == 0 )
		{
			puts ( "File successfully renamed" );
			socket->writeline("File successfully renamed");
			socket->writeline("");
		}
		else
		{
			perror( "Error renaming file" );
			socket->writeline("Error renaming file");
			socket->writeline("");
		}
	}

	InputHandler* RenFInputHandler::Clone()
	{
		return new RenFInputHandler();
	}
}