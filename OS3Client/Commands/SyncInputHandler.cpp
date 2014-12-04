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
		string deletepath = ConvertPath(path);
		deletepath = PATHQUOTES + deletepath + PATHQUOTES;
		socket->write("DEL ");
		socket->writeline(deletepath);

		char line[MAXPATH + 1];

		while (socket->readline(line, MAXPATH) > 0)
		{
			cout << line << endl;
		}
	}
	void SyncInputHandler::Put(Socket *socket, string local,string remote)
	{
		string remotepath = ConvertPath(remote);
		remotepath = PATHQUOTES + remotepath;
		string localpath = ConvertPath(local);
		localpath = PATHQUOTES + localpath + PATHQUOTES;
		socket->write("put " + remotepath);
		socket->writeline(localpath);
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

		manager->SendFile(socket,localpath);

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
		TiXmlDocument clientDoc("Config.xml");
		TiXmlDocument serverDoc("serverxml/Config.xml");

		bool loadOkay = clientDoc.LoadFile();
		if (!loadOkay)
		{
			printf("Could not load test file 'Config.xml'. Error='%s'. Exiting.\n", clientDoc.ErrorDesc());
			return;
		}
		loadOkay = serverDoc.LoadFile();
		if (!loadOkay)
		{
			printf("Could not load test file 'Config.xml'. Error='%s'. Exiting.\n", serverDoc.ErrorDesc());
			return;
		}

		TiXmlNode *clientNode = 0;
		clientNode = clientDoc.FirstChild("Filesystem");
		TransferManager *manager = new TransferManager();

		TiXmlNode *serverNode = 0;
		serverNode = serverDoc.FirstChild("Filesystem");
		bool found = false;

		char line[MAXPATH + 1];
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
					int serverDate = atoi(server->Attribute("Editdate"));
					int clientDate = atoi(client->Attribute("Editdate"));
					if (clientDate > serverDate)
					{
						found = false;
					}
					else
					{
						found = true;
					}
				}
			}
			if (!found)
			{
				const char *local = client->Attribute("directory");
				TiXmlNode *versionNode = 0;
				versionNode = serverDoc.FirstChild("rootPath");
				TiXmlElement *versionelement = versionNode->ToElement();

				string remotepath = ConvertPath(versionelement->Attribute("path") + string("/") + local);
				vector<string> segments = vector<string>();

				std::string path = "";
				StrSplit(remotepath, segments);
				segments.pop_back();
				for (size_t i = 0; i < segments.size(); i++)
				{
					path.append(segments[i]);
					if (i != segments.size() - 1)
					{
						path.append("/");
					}
				}
				Put(socket, Currentpath().c_str() + string("/") + string(local), path);
			}
		}

		delete manager;
		cout << "Syncing completed!" << endl;
		//socket->writeline("");
	}

	void SyncInputHandler::SetXML(Socket *socket)
	{
		try
		{
			char buffer[MAXBUFFERSIZE + 1];
			int bytesToRead, bytesRead, fileSize;

			ofstream myfile(Currentpath()+"/serverxml/Config.xml", ofstream::binary | ofstream::trunc);

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
