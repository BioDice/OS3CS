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
		if (!FormatCommandPath(response, segments, 1))
		{
			cout << "Syntax error... - use: del [remote file]" << endl;
			socket->writeline("");
			return;
		}
		
		if( remove( segments[0].c_str() ) != 0 )
			perror( "Error deleting file" );
		else
		{
			puts( "File successfully deleted" );
			std::string str = GetFileName(segments[0]);
			char*filename = &str[0];
			DirectoryWriter *writer = new DirectoryWriter();
			writer->DeleteNode(filename);
			//cout << "File succesfully deleted" ;
			socket->writeline("");
		}
	}

	InputHandler* DelInputHandler::Clone()
	{
		return new DelInputHandler();
	}
}
