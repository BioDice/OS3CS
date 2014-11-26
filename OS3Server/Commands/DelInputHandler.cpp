#include "DelInputHandler.h"

namespace OS3CS
{
	DelInputHandler::DelInputHandler(void)
	{
	}


	DelInputHandler::~DelInputHandler(void)
	{

	}

	void DelInputHandler::Process(Socket* socket, string response)
	{
		char buffer[MAXBUFFERSIZE + 1];

		vector<string> segments = vector<string>();
		StrSplit(response, segments, ' ');
		if (segments.size() != 2)
		{
			cout << "Syntax error..." << endl;
			socket->writeline("");
			return;
		}
		
		if( remove( segments[1].c_str() ) != 0 )
			perror( "Error deleting file" );
		else
		{
			puts( "File successfully deleted" );
			//cout << "File succesfully deleted" ;
			socket->writeline("");
		}
	}

	InputHandler* DelInputHandler::Clone()
	{
		return new DelInputHandler();
	}
}