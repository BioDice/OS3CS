#include "SyncInputHandler.h"

namespace OS3CS
{
	SyncInputHandler::SyncInputHandler(void)
	{
	}


	SyncInputHandler::~SyncInputHandler(void)
	{
	}

	void SyncInputHandler::Process(Socket* socket, string response)
	{
		DirectoryWriter *writer = new DirectoryWriter();
		int version = writer->isLeading();
		socket->writeline(response);
		int serverversion = 0;
		char line[256 + 1];
		while (socket->readline(line, 256) > 0)
		{
			serverversion = atoi(line);
		}

		if (version > serverversion)
		{
			cout << "Sync started";

		}
		else if (version==serverversion)
		{
			cout << "Up to date!";
		}
		
		socket->writeline("");
		delete writer;
	}

	void SyncInputHandler::SetXML(Socket *socket)
	{
		//string temp = ;
		//temp = temp.erase(0, 4);
		//vector<string> segments = vector<string>();
		//vector<string> resp = vector<string>();
		//StrSplit(temp, resp, '"');
		//if (resp.size() == 1)
		//{
		//	StrSplit(resp[0], segments, ' ');
		//}
		//else if (resp.size() == 2)
		//{
		//	StripWhiteSpaces(resp);
		//	segments = resp;
		//}
		//else if (resp.size() == 3)
		//{
		//	StripWhiteSpaces(resp);
		//	segments = resp;
		//}
		//else if (resp.size() == 4)
		//{
		//	StripWhiteSpaces(resp);
		//	segments.push_back(resp[0]);
		//	segments.push_back(resp[1]);
		//}
		//else
		//{
		//	cout << "Syntax error: use put [remote file] [local dir]" << endl;
		//	return;
		//}
		//socket->writeline(response);
		//char buffer[MAXBUFFERSIZE + 1];
		//int bytesToRead, bytesRead, fileSize;
		//string path = ConvertPath(segments[1]) + "/" + GetFileName(segments[0]);
		//ofstream myfile(path, ofstream::binary | ofstream::trunc);

		//socket->readline(buffer, MAXBUFFERSIZE);
		//fileSize = stoi(buffer);
		//bytesToRead = fileSize;

		//// tell the server the client is ready to receive
		//cout << "Ready to receive content" << endl;
		//socket->writeline("READY");

		//while (bytesToRead > 0)
		//{
		//	try
		//	{
		//		bytesRead = socket->read(buffer, bytesToRead > MAXBUFFERSIZE ? MAXBUFFERSIZE : bytesToRead);
		//	}
		//	catch (exception ex)
		//	{
		//		cout << "Error occured while reading file..." << endl;
		//		throw ex;
		//	}

		//	myfile.write(buffer, bytesRead);

		//	bytesToRead -= bytesRead;
		//	cout << "Bytes Read: " << bytesRead << ". Bytes left: " << bytesToRead << endl;
		//}

		//myfile.close();
		//cout << "File transfer complete!" << endl;
		//while (socket->readline(buffer, MAXPATH) > 0)
		//{
		//	cout << buffer << endl;
		//}
	}

	InputHandler* SyncInputHandler::Clone()
	{
		return new SyncInputHandler();
	}
}