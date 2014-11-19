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
		try
		{
			vector<string> segments = vector<string>();
			if (!FormatCommandPath(response, segments, 2))
			{
				cout << "Syntax error: use put [remote file] [local dir]" << endl;
				return;
			}
			socket->writeline(response);
			char buffer[MAXBUFFERSIZE + 1];
			int bytesToRead, bytesRead, fileSize;
			string path = ConvertPath(segments[1]) + "/" + GetFileName(segments[0]);
			ofstream myfile(path, ofstream::binary | ofstream::trunc);

			socket->readline(buffer, MAXBUFFERSIZE);
			fileSize = stoi(buffer);
			bytesToRead = fileSize;

			// tell the server the client is ready to receive
			cout << "Ready to receive content" << endl;
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
			while (socket->readline(buffer, MAXPATH) > 0)
			{
				cout << buffer << endl;
			}
		}
		catch (exception ex)
		{
			cout << "Something went wrong..." << endl;
		}
	}

	InputHandler* GetInputHandler::Clone()
	{
		return new GetInputHandler();
	}
}