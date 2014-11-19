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
			char buffer[MAXBUFFERSIZE+1];
			int bytesToRead, bytesRead, fileSize;
			ifstream myfile(segments[0].c_str(), ifstream::binary);

			if (!myfile.is_open())
			{
				myfile.close();
				throw("Cannot open file");
			}

			// goes to end of file to determine the size then sets the iterator back
			myfile.seekg(0, myfile.end);
			fileSize = myfile.tellg();
			myfile.seekg(0);

			bytesToRead = fileSize;
			// send filesize to server
			cout << "Sending file size: " << fileSize << " bytes" << endl;
			socket->writeline(to_string(fileSize));
			
			char line[MAXPATH];

			// asking (waiting) if client is ready
			socket->readline(line, MAXPATH);
			if (strcmp(line, "READY") != 0)
			{
				throw("Client is not ready...");
				return;
			}
			cout << "Client is ready. Start sending content..." << endl;

			while (bytesToRead > 0)
			{
				bytesRead = bytesToRead > MAXBUFFERSIZE ? MAXBUFFERSIZE : bytesToRead;

				myfile.read(buffer, bytesRead);

				socket->write(buffer, myfile.gcount());

				bytesToRead -= myfile.gcount();

				cout << bytesRead << " bytes sent" << endl;
			}
			myfile.close();
			cout << "File is sent" << endl;
			socket->writeline("");
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