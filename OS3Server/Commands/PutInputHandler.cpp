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
		char buffer[MAXBUFFERSIZE + 1];
		int bytesToRead, bytesRead, fileSize;
		// merge path with filename
		string path = ConvertPath(segments[0]) + "/" + GetFileName(segments[1]);
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
		while (socket->readline(buffer, MAXPATH) > 0)
		{
			cout << buffer << endl;
		}
	}

	InputHandler* PutInputHandler::Clone()
	{
		return new PutInputHandler();
	}
}