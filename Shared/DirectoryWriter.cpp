#include "../Shared/DirectoryWriter.h"
#include <iostream>    

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

	for(TiXmlElement* e = node->FirstChildElement("File"); e != NULL; e = e->NextSiblingElement("File"))
	{
		const char *attribute = e->Attribute("Originalname");
		if (strcmp(attribute,nodeName)==0)
		{
			e->SetAttribute("filename", renamename);
		}
	}

	doc.SaveFile();
}

void DirectoryWriter::WriteNode(char *nodeName,char*directory)
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


