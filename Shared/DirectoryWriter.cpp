#include "DirectoryWriter.h"
#include <iostream>
namespace OS3CS
{
	DirectoryWriter::DirectoryWriter(void)
	{

	}

	DirectoryWriter::~DirectoryWriter(void)
	{
	}
	int DirectoryWriter::isLeading()
	{
		TiXmlDocument doc("config.xml");
		bool loadOkay = doc.LoadFile();

		if (!loadOkay)
		{
			printf("Could not load test file 'config.xml'. Error='%s'. Exiting.\n", doc.ErrorDesc());
			exit(1);
		}

		TiXmlNode *versionNode = 0;
		versionNode = doc.FirstChild("Version");
		TiXmlElement *versionelement = versionNode->ToElement();
		std::string version = versionelement->Attribute("Number");
		return atoi(version.c_str());
	}

	void DirectoryWriter::Sync(Socket *socket)
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
		for (TiXmlElement* server = serverNode->FirstChildElement("File"); server != NULL; server = server->NextSiblingElement("File"))
		{
			found = false;
			const char *serverAttribute = server->Attribute("Originalname");
			for (TiXmlElement* client = clientNode->FirstChildElement("File"); client != NULL; client = client->NextSiblingElement("File"))
			{
				found = true;
			}
			if (!found)
			{
				//delete server node
			}
		}

		for (TiXmlElement* client = clientNode->FirstChildElement("File"); client != NULL; client = client->NextSiblingElement("File"))
		{
			const char *serverAttribute = client->Attribute("Originalname");
			for (TiXmlElement* server = serverNode->FirstChildElement("File"); server != NULL; server = server->NextSiblingElement("File"))
			{
				const char *clientAttribute = server->Attribute("Originalname");
				if (strcmp(clientAttribute, serverAttribute) != 0)
				{
					const char *clientDirectory = client->Attribute("directory");
					const char *serverDirectory = server->Attribute("directory");
					//vector<string> segments = vector<string>();
					//socket->writeline(response);
					//string response = "put "+
					//TransferManager* manager = new TransferManager();
					////manager->SendFile(socket, segments[1]);
					//socket->writeline(r);
					manager->SendFile(socket, clientDirectory);
				}
			}
		}

		delete manager;
		delete clientNode;
	}

	void DirectoryWriter::InitList()
	{
		TiXmlDocument doc;
		TiXmlDeclaration *declaration = new TiXmlDeclaration("1.0", "", "");
		TiXmlElement *version = new TiXmlElement("Version");
		version->SetAttribute("Number", 1);
		doc.LinkEndChild(declaration);
		doc.LinkEndChild(version);

		TiXmlElement *filesystem = new TiXmlElement("Filesystem");
		doc.LinkEndChild(filesystem);
		doc.SaveFile("Config.xml");
		DirectoryReader * reader = new DirectoryReader();
		DIR* pDir = reader->open(Currentpath() + PATHSEPERATOR + "mapje");

		struct dirent* pEnt = NULL;

		int count = 0;
		while (pEnt = readdir(pDir))
		{
			if (strcmp(pEnt->d_name, ".") == 0 || strcmp(pEnt->d_name, "..") == 0)
				continue;

			string szCurrent(Currentpath()+PATHSEPERATOR+"mapje");
			szCurrent.append(PATHSEPERATOR);
			szCurrent.append(pEnt->d_name);

			//if (reader->isDir(szCurrent))
			//{
			//	vListing.push_back(szCurrent);
			//}

			if (reader->isFile(szCurrent))
			{
				//time_t iLastModified = reader->getLastModifiedTime(szCurrent);
				//szCurrent.append("|");
				//szCurrent.append(to_string(iLastModified));
				WriteNode(pEnt->d_name, szCurrent);
			}

			count++;
		}

		delete pEnt;
		delete pDir;
		//TODO:Loop directory
	}

	void DirectoryWriter::UpdateNode(char*nodeName, char*renamename)
	{
		TiXmlDocument doc("config.xml");
		bool loadOkay = doc.LoadFile();

		if (!loadOkay)
		{
			printf("Could not load test file 'config.xml'. Error='%s'. Exiting.\n", doc.ErrorDesc());
			exit(1);
		}

		TiXmlNode *versionNode = 0;
		versionNode = doc.FirstChild("Version");
		TiXmlElement *versionelement = versionNode->ToElement();
		std::string version = versionelement->Attribute("Number");
		int value = atoi(version.c_str());
		value += 1;
		versionelement->SetAttribute("Number", value);

		TiXmlNode *node = 0;
		node = doc.FirstChild("Filesystem");
		TiXmlElement *searchNode = 0;

		for (TiXmlElement* e = node->FirstChildElement("File"); e != NULL; e = e->NextSiblingElement("File"))
		{
			const char *attribute = e->Attribute("Originalname");
			if (strcmp(attribute, nodeName) == 0)
			{
				e->SetAttribute("filename", renamename);
			}
		}

		doc.SaveFile();
	}

	void DirectoryWriter::WriteNode(string nodeName, string directory)
	{
		TiXmlDocument doc("config.xml");
		bool loadOkay = doc.LoadFile();

		if (!loadOkay)
		{
			printf("Could not load test file 'config.xml'. Error='%s'. Exiting.\n", doc.ErrorDesc());
			exit(1);
		}

		TiXmlElement newFile("File");
		newFile.SetAttribute("filename", nodeName.c_str());
		newFile.SetAttribute("Originalname", nodeName.c_str());
		newFile.SetAttribute("directory", directory.c_str());

		TiXmlNode *versionNode = 0;
		versionNode = doc.FirstChild("Version");
		TiXmlElement *versionelement = versionNode->ToElement();
		std::string version = versionelement->Attribute("Number");
		int value = atoi(version.c_str());
		value += 1;
		versionelement->SetAttribute("Number", value);

		TiXmlNode *node = 0;
		node = doc.FirstChild("Filesystem");
		TiXmlElement *rootElement = 0;
		rootElement = node->ToElement();
		rootElement->InsertEndChild(newFile);

		doc.SaveFile();
	}

	void DirectoryWriter::DeleteNode(char *nodeName)
	{
		TiXmlDocument doc("config.xml");
		bool loadOkay = doc.LoadFile();

		if (!loadOkay)
		{
			printf("Could not load test file 'config.xml'. Error='%s'. Exiting.\n", doc.ErrorDesc());
			exit(1);
		}

		TiXmlNode *versionNode = 0;
		versionNode = doc.FirstChild("Version");
		TiXmlElement *versionelement = versionNode->ToElement();
		std::string version = versionelement->Attribute("Number");
		int value = atoi(version.c_str());
		value += 1;
		versionelement->SetAttribute("Number", value);

		TiXmlNode *node = 0;
		node = doc.FirstChild("Filesystem");
		TiXmlElement *searchNode = 0;

		for (TiXmlElement* e = node->FirstChildElement("File"); e != NULL; e = e->NextSiblingElement("File"))
		{
			const char *attribute = e->Attribute("filename");
			if (strcmp(attribute, nodeName) == 0)
			{
				node->RemoveChild(e);
				break;
			}
		}
		doc.SaveFile();
	}
}