#include "SyncInputHandler.h"

namespace OS3CS
{
	SyncInputHandler::SyncInputHandler(void)
	{
	}


	SyncInputHandler::~SyncInputHandler(void)
	{
	}

	void SyncInputHandler::Process(Socket* socket,string response)
	{
		//DirectoryWriter *writer = new DirectoryWriter();
		//int version = writer->isLeading();
		//socket->writeline(std::to_string(version));
		//socket->writeline("");
		GetXML(socket);
		//socket->writeline("READY");
		socket->writeline("READY");
	}
	void SyncInputHandler::GetXML(Socket *socket)
	{
		char buffer[MAXBUFFERSIZE + 1];
		int bytesToRead, bytesRead, fileSize;

		ifstream myfile(Currentpath()+PATHSEPERATOR+"Config.xml", ifstream::binary);
		if (!myfile.is_open())
		{
			myfile.close();
			cout << "Cannot open file" << endl;
			return;
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
			cout << "Client is not read..." << endl;
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

	InputHandler* SyncInputHandler::Clone()
	{
		return new SyncInputHandler();
	}
}