#include "TransferManager.h"
namespace OS3CS {
	TransferManager::TransferManager()
	{
	}


	TransferManager::~TransferManager()
	{
	}

	void TransferManager::ReceiveFile(Socket*socket,string response)
	{
		char buffer[MAXBUFFERSIZE + 1];
		int bytesToRead, bytesRead, fileSize;

		ofstream myfile(response, ofstream::binary | ofstream::trunc);

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
		//while (socket->readline(buffer, MAXPATH) > 0)
		//{
		//	cout << buffer << endl;
		//}
	}
	void TransferManager::SendFile(Socket*socket,string response)
	{
		try
		{
			char buffer[MAXBUFFERSIZE + 1];
			int bytesToRead, bytesRead, fileSize;

			ifstream myfile(response, ifstream::binary);

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
			cout << "Sending file size: " << fileSize << " bytes" << endl;
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
		}
		catch (exception ex)
		{
			cout << "Something went wrong..." << endl;
		}
	}

}
