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
			socket->writeline(response);
			char buffer[MAXBUFFERSIZE+1];
			int bytesToRead, bytesRead, fileSize;
			ifstream myfile (segments[1].c_str(), ifstream::binary);
		
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
			socket->writeline(to_string(fileSize));
			cout << "Sending file size: " << fileSize << endl;
			char line[MAXPATH];

			// asking (waiting) if server is ready
			socket->readline(line, MAXPATH);
			if (strcmp(line, "READY") != 0)
			{
				throw("Server is not ready...");
				return;
			}
			cout << "Server is ready. Start sending content..." << endl;
			// send bytes to socket
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

	InputHandler* PutInputHandler::Clone()
	{
		return new PutInputHandler();
	}
}