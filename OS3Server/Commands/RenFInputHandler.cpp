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
		result= rename(segments[0].c_str(), segments[1].c_str());
		DirectoryWriter* writer = new DirectoryWriter();
		writer->UpdateNode(GetFileName(segments[0]), GetFileName(segments[1]));
		delete writer;
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