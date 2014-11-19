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

		for (TiXmlElement* client = clientNode->FirstChildElement("File"); client != NULL; client = client->NextSiblingElement("File"))
		{
			const char *clientAttribute = client->Attribute("Originalname");
			for (TiXmlElement* server = serverNode->FirstChildElement("File"); server != NULL; server = server->NextSiblingElement("File"))
			{
				const char *serverAttribute = server->Attribute("Originalname");
				if (strcmp(clientAttribute, serverAttribute) != 0)
				{
					const char *clientDirectory = client->Attribute("directory");
					manager->SendFile(socket,clientDirectory);
				}
			}
		}
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

		//TODO:Loop directory

		doc.SaveFile("config.xml");
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

	void DirectoryWriter::WriteNode(char *nodeName, char*directory)
	{
		TiXmlDocument doc("config.xml");
		bool loadOkay = doc.LoadFile();

		if (!loadOkay)
		{
			printf("Could not load test file 'config.xml'. Error='%s'. Exiting.\n", doc.ErrorDesc());
			exit(1);
		}

		TiXmlElement newFile("File");
		newFile.SetAttribute("filename", nodeName);
		newFile.SetAttribute("Originalname", nodeName);
		newFile.SetAttribute("directory", directory);

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