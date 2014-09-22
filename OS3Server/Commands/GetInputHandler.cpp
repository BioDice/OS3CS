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
		vector<string> segments = vector<string>();
		StrSplit(response, segments, ' ');
		if (segments.size() != 3)
		{
			cout << "Syntaxt error: use put [remote dir] [local file]\n";
			return;
		}

		char buffer[MAXBUFFERSIZE];
		int bytesToRead, bytesRead, fileSize;
		ifstream myfile (segments[1].c_str(), ios::out | ios::app | ios::binary);
		
		// goes to end of file to determine the size then sets the iterator back
		myfile.seekg(0, myfile.end);
		fileSize = myfile.tellg();
		myfile.seekg(0, myfile.beg);

		bytesToRead = fileSize;

		while (bytesToRead > 0)
		{
			bytesRead = bytesToRead > MAXBUFFERSIZE ? MAXBUFFERSIZE : bytesToRead;

			myfile.read(buffer, bytesRead);
			
			socket->write(buffer, myfile.gcount());
			cout << bytesRead << " bytes sent\n";
		}
		cout << "File is sent\n";
	}

	InputHandler* GetInputHandler::Clone()
	{
		return new GetInputHandler();
	}
}