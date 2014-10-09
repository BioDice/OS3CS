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
		if (segments.size() != 3)
		{
			cout << "Syntaxt error: use put [remote dir] [local file]" << endl;
			return;
		}
		char buffer[MAXBUFFERSIZE + 1];
		int bytesToRead, bytesRead, fileSize;
		// merge path with filename
		string path = ConvertPath(segments[1]) + "/" + GetFileName(segments[2]);
		ofstream myfile(path, ofstream::binary | ofstream::trunc);

		socket->readline(buffer, MAXBUFFERSIZE);
		fileSize = stoi(buffer);
		bytesToRead = fileSize;
		
		// tell the client the server is ready to receive
		socket->writeline("READY");

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