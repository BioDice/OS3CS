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
			cout << "Syntaxt error: use put [remote file] [local dir]" << endl;
			return;
		}
		socket->writeline(response);
		char buffer[MAXBUFFERSIZE + 1];
		int bytesToRead, bytesRead, fileSize;
		ofstream myfile(segments[2].c_str(), ofstream::binary | ofstream::trunc);

		socket->readline(buffer, MAXBUFFERSIZE);
		fileSize = stoi(buffer);
		bytesToRead = fileSize;

		// tell the server the client is ready to receive
		socket->writeline("READY");

		while (bytesToRead > 0)
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

	InputHandler* GetInputHandler::Clone()
	{
		return new GetInputHandler();
	}
}