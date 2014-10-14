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
		string temp = response;
		temp = temp.erase(0, 4);
		vector<string> segments = vector<string>();
		vector<string> resp = vector<string>();
		StrSplit(temp, resp, '"');
		if (resp.size() == 1)
		{
			StrSplit(resp[0], segments, ' ');
		}
		else if (resp.size() == 2)
		{
			StripWhiteSpaces(resp);
			segments = resp;
		}
		else if (resp.size() == 3)
		{
			StripWhiteSpaces(resp);
			segments = resp;
		}
		else if (resp.size() == 4)
		{
			StripWhiteSpaces(resp);
			segments.push_back(resp[0]);
			segments.push_back(resp[1]);
		}
		else
		{
			cout << "Syntax error: use put [remote file] [local dir]" << endl;
			return;
		}
		try
		{
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