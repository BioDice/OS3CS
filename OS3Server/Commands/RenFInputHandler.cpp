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
		StrSplit(response, segments, ' ');
		if (segments.size() != 3)
		{
			cout << "Syntax error..." << endl;
			socket->writeline("");
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