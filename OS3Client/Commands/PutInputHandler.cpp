#include "PutInputHandler.h"

namespace OS3CS
{
	const int BUFFERSIZE = 1024;

	PutInputHandler::PutInputHandler(void)
	{
	}


	PutInputHandler::~PutInputHandler(void)
	{
	}

	void PutInputHandler::Process(Socket* socket, string response)
	{
		vector<string> segments = vector<string>();
		StrSplit(response, segments, ' ');
		if (segments.size() != 3)
		{
			cout << "Syntaxt error: use put [remote dir] [local file]\n";
			return;
		}
		socket->writeline(response);
		char buffer[MAXBUFFERSIZE];
		int bytesToRead, bytesRead, fileSize;
		ifstream myfile (segments[2].c_str(), ios::out | ios::app | ios::binary);
		
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

			bytesToRead -= myfile.gcount();

			cout << bytesRead << " bytes sent\n";
		}
		cout << "File is sent\n";

	}

	InputHandler* PutInputHandler::Clone()
	{
		return new PutInputHandler();
	}
}