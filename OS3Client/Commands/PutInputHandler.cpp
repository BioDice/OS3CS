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

		char buffer[MAXBUFFERSIZE];
		int bytesToRead, bytesRead, fileSize;
		ifstream myfile (segments[2].c_str(), ios::out | ios::app | ios::binary);

		fileSize = stoi(buffer);
		bytesToRead = fileSize;

	}

	InputHandler* PutInputHandler::Clone()
	{
		return new PutInputHandler();
	}
}