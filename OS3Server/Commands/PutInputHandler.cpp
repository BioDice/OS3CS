#include "PutInputHandler.h"

namespace OS3CS
{
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
		ofstream myfile (segments[2].c_str(), ios::out | ios::app | ios::binary);

		fileSize = stoi(buffer);
		bytesToRead = fileSize;
		
		while(bytesToRead > 0)
		{
			try
			{
				bytesRead = socket->read(buffer, bytesToRead > MAXBUFFERSIZE ? MAXBUFFERSIZE : bytesToRead);
			}
			catch (exception ex) 
			{
				cout << "Error occured while reading file..." << endl;
				throw ex;
			}

			myfile.write(buffer, bytesRead);

			bytesToRead -= bytesRead;
			cout << "Bytes Read: " << bytesRead << ". Bytes left: " << bytesToRead << endl;
		}

		myfile.close();
		cout << "File transfer complete!" << endl;
	}

	InputHandler* PutInputHandler::Clone()
	{
		return new PutInputHandler();
	}
}