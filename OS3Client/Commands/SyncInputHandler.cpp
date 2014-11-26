#include "SyncInputHandler.h"

namespace OS3CS
{
	SyncInputHandler::SyncInputHandler(void)
	{
	}


	SyncInputHandler::~SyncInputHandler(void)
	{
	}

	void SyncInputHandler::Delete(Socket *socket, string path)
	{
		socket->write("DEL ");
		socket->writeline(path);

		char line[MAXPATH + 1];

		while (socket->readline(line, MAXPATH) > 0)
		{
			cout << line << endl;
		}
	}
	void SyncInputHandler::Put(Socket *socket, string local,string remote)
	{
		socket->write("put null ");
		socket->writeline(remote);
		char line[MAXPATH + 1];

		socket->readline(line, MAXPATH);

		if (strcmp(line, "READY") != 0)
		{
			while (socket->readline(line, MAXPATH) > 0)
			{
				cout << line << endl;
			}
			throw("Aborted");
		}

		TransferManager *manager = new TransferManager();

		manager->SendFile(socket,local);

		delete manager;

		while (socket->readline(line, MAXPATH) > 0)
		{
			cout << line << endl;
		}
	}

	void SyncInputHandler::Process(Socket* socket, string response)
	{
		socket->writeline(response);
		cout << "Sync started";
		SetXML(socket);
		Sync(socket);
	}

	void SyncInputHandler::Sync(Socket *socket)
	{
		TiXmlDocument clientDoc("config.xml");
		TiXmlDocument serverDoc("serverxml/config.xml");
		bool loadOkay = clientDoc.LoadFile();
		if (!loadOkay)
		{
			printf("Could not load test file 'config.xml'. Error='%s'. Exiting.\n", clientDoc.ErrorDesc());
			return;
		}
		loadOkay = serverDoc.LoadFile();
		if (!loadOkay)
		{
			printf("Could not load test file 'config.xml'. Error='%s'. Exiting.\n", serverDoc.ErrorDesc());
			return;
		}

		TiXmlNode *clientNode = 0;
		clientNode = clientDoc.FirstChild("Filesystem");
		TransferManager *manager = new TransferManager();

		TiXmlNode *serverNode = 0;
		serverNode = serverDoc.FirstChild("Filesystem");
		bool found = false;

		char line[MAX_PATH + 1];
		socket->readline(line, MAXPATH);
		if (strcmp(line, "READY") != 0)
		{
			throw("Server is not ready...");
			return;
		}

		for (TiXmlElement* server = serverNode->FirstChildElement("File"); server != NULL; server = server->NextSiblingElement("File"))
		{
			found = false;
			const char *serverAttribute = server->Attribute("Originalname");
			for (TiXmlElement* client = clientNode->FirstChildElement("File"); client != NULL; client = client->NextSiblingElement("File"))
			{
				const char *clientAttribute = client->Attribute("Originalname");
				if (strcmp(clientAttribute, serverAttribute) == 0)
				{
					found = true;
				}
				
			}
			if (!found)
			{
				const char *dir = server->Attribute("directory");
				Delete(socket, dir);
			}
		}
		for (TiXmlElement* client = clientNode->FirstChildElement("File"); client != NULL; client = client->NextSiblingElement("File"))
		{
			found = false;
			const char *clientAttribute = client->Attribute("Originalname");
			
			for (TiXmlElement* server = serverNode->FirstChildElement("File"); server != NULL; server = server->NextSiblingElement("File"))
			{
				const char *serverAttribute = server->Attribute("Originalname");
				if (strcmp(clientAttribute, serverAttribute) == 0)
				{
					found = true;
				}
			}
			if (!found)
			{
				const char *local = client->Attribute("directory");
				string filename = clientAttribute;
				Put(socket, local,"C:\\Users\\dev\\Documents\\GitHub\\OS3CS\\OS3Server\\mapje"+PATHSEPERATOR+filename);
			}
		}

		delete manager;
		cout << "Syncing completed!" << endl;
	}

	void SyncInputHandler::SetXML(Socket *socket)
	{
		try
		{
			char buffer[MAXBUFFERSIZE + 1];
			int bytesToRead, bytesRead, fileSize;

			ofstream myfile(Currentpath()+"/serverxml/config.xml", ofstream::binary | ofstream::trunc);

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

	InputHandler* SyncInputHandler::Clone()
	{
		return new SyncInputHandler();
	}
}