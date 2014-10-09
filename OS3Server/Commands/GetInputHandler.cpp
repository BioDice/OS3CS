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
		try
		{
			char buffer[MAXBUFFERSIZE+1];
			int bytesToRead, bytesRead, fileSize;
			ifstream myfile(segments[1].c_str(), ifstream::binary);

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
			cout << "Sending file size: " << fileSize << endl;
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