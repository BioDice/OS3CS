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
		TiXmlDocument doc("Config.xml");
		bool loadOkay = doc.LoadFile();

		if (!loadOkay)
		{
			printf("Could not load test file 'Config.xml'. Error='%s'. Exiting.\n", doc.ErrorDesc());
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
		
	}

	void DirectoryWriter::RecursiveList(string szPath, map<string, string> &directoryMap, bool bRecursive)
	{
		DirectoryReader * reader = new DirectoryReader();
		DIR* pDir = reader->open(szPath);

		struct dirent* pEnt = NULL;

		int count = 0;
		while (pEnt = readdir(pDir))
		{
			if (strcmp(pEnt->d_name, ".") == 0 || strcmp(pEnt->d_name, "..") == 0)
				continue;

			string szCurrent(szPath);
			szCurrent.append(PATHSEPERATOR);
			szCurrent.append(pEnt->d_name);
			
			if (reader->isDir(szCurrent))
			{
				if (bRecursive)
					RecursiveList(szCurrent, directoryMap, true);
			}
			if (reader->isFile(szCurrent))
			{
				vector<string> segments = vector<string>();
				string currentPath = ConvertPath(szCurrent);
				StrSplit(currentPath, segments);

				string path = "";
				vector<string>temp = segments;
				for (size_t i = 0; i < temp.size(); i++)
				//for each (string var in temp)
				{
					if (strcmp(temp[i].c_str(),"mapje")==0)
					{
						break;
					}
					else
					{
						segments.erase(segments.begin());
					}
				}

				for (size_t i = 0; i < segments.size(); i++)
				{
					path.append(segments[i]);
					if (i!=segments.size()-1)
					{
						path.append(PATHSEPERATOR);
					}
				}

				time_t iLastModified = reader->getLastModifiedTime(szCurrent);
				directoryMap[pEnt->d_name] = szCurrent;
				WriteNode(pEnt->d_name, path, to_string(iLastModified));
			}

			count++;
		}

		delete pEnt;
		delete pDir;
	}

	void DirectoryWriter::InitList()
	{
		TiXmlDocument doc;
		TiXmlDeclaration *declaration = new TiXmlDeclaration("1.0", "", "");
		TiXmlElement *version = new TiXmlElement("Version");
		version->SetAttribute("Number", 1);

		TiXmlElement *rootpath = new TiXmlElement("rootPath");
		string path = Currentpath().c_str();
		rootpath->SetAttribute("path", path.c_str());
		doc.LinkEndChild(declaration);
		doc.LinkEndChild(version);
		doc.LinkEndChild(rootpath);

		TiXmlElement *filesystem = new TiXmlElement("Filesystem");
		doc.LinkEndChild(filesystem);
		doc.SaveFile("Config.xml");

		map<string, string> directoryMap = map<string,string>();
		RecursiveList(path+PATHSEPERATOR+"mapje", directoryMap,true);
		
		//TODO:Loop directory
	}

	void DirectoryWriter::RenameNode(string nodeName, string renamename)
	{
		TiXmlDocument doc("Config.xml");
		bool loadOkay = doc.LoadFile();

		if (!loadOkay)
		{
			printf("Could not load test file 'Config.xml'. Error='%s'. Exiting.\n", doc.ErrorDesc());
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
			if (strcmp(attribute, nodeName.c_str()) == 0)
			{
				e->SetAttribute("filename", renamename.c_str());

				vector<string> segments = vector<string>();
				StrSplit(e->Attribute("directory"), segments);

				segments.pop_back();
				segments.push_back(renamename);
				string directory = "";
				for (size_t i = 0; i < segments.size(); i++)
				{
					directory.append(segments[i]);
					if (i != segments.size() - 1)
					{
						directory.append(PATHSEPERATOR);
					}
				}

				e->SetAttribute("directory", directory.c_str());
			}
		}

		doc.SaveFile();
	}

	void DirectoryWriter::UpdateNode(string nodeName, string directory, string editDate)
	{
		TiXmlDocument doc("Config.xml");
		bool loadOkay = doc.LoadFile();

		if (!loadOkay)
		{
			printf("Could not load test file 'Config.xml'. Error='%s'. Exiting.\n", doc.ErrorDesc());
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
			if (strcmp(attribute, nodeName.c_str()) == 0)
			{
				vector<string> segments = vector<string>();
				StrSplit(e->Attribute("directory"), segments);

				segments.pop_back();
				segments.push_back(nodeName);
				string directory = "";
				for (size_t i = 0; i < segments.size(); i++)
				{
					directory.append(segments[i]);
					if (i != segments.size() - 1)
					{
						directory.append(PATHSEPERATOR);
					}
				}
				e->SetAttribute("filename", nodeName.c_str());
				e->SetAttribute("Editdate", editDate.c_str());
				e->SetAttribute("directory", directory.c_str());
				break;
			}
		}

		doc.SaveFile();
	}

	void DirectoryWriter::WriteNode(string nodeName, string directory,string editDate)
	{
		TiXmlDocument doc("Config.xml");
		bool loadOkay = doc.LoadFile();

		if (!loadOkay)
		{
			printf("Could not load test file 'Config.xml'. Error='%s'. Exiting.\n", doc.ErrorDesc());
			exit(1);
		}

		TiXmlNode *versionNode = 0;
		versionNode = doc.FirstChild("Version");
		TiXmlElement *versionelement = versionNode->ToElement();
		std::string version = versionelement->Attribute("Number");
		int value = atoi(version.c_str());
		value += 1;
		versionelement->SetAttribute("Number", value);

		/////
		TiXmlNode *node = 0;
		node = doc.FirstChild("Filesystem");

		TiXmlElement *element = node->FirstChildElement("File");
		if (element == NULL)
		{
			TiXmlElement newFile("File");
			newFile.SetAttribute("filename", nodeName.c_str());
			newFile.SetAttribute("Originalname", nodeName.c_str());
			newFile.SetAttribute("directory", directory.c_str());
			newFile.SetAttribute("Editdate", editDate.c_str());

			TiXmlNode *node = 0;
			node = doc.FirstChild("Filesystem");
			TiXmlElement *rootElement = 0;
			rootElement = node->ToElement();
			rootElement->InsertEndChild(newFile);
		}
		else
		{
			TiXmlElement *searchNode = 0;
			bool found = false;
			for (TiXmlElement* e = node->FirstChildElement("File"); e != NULL; e = e->NextSiblingElement("File"))
			{
				found = false;
				const char *attribute = e->Attribute("Originalname");
				if (strcmp(attribute, nodeName.c_str()) == 0)
				{
					UpdateNode(nodeName,directory,editDate);
					found = true;
				}

				if (!found)
				{
					TiXmlElement newFile("File");
					newFile.SetAttribute("filename", nodeName.c_str());
					newFile.SetAttribute("Originalname", nodeName.c_str());
					newFile.SetAttribute("directory", directory.c_str());
					newFile.SetAttribute("Editdate", editDate.c_str());

					TiXmlNode *node = 0;
					node = doc.FirstChild("Filesystem");
					TiXmlElement *rootElement = 0;
					rootElement = node->ToElement();
					rootElement->InsertEndChild(newFile);
					break;
				}
			}
		}
		doc.SaveFile();
	}

	void DirectoryWriter::DeleteNode(char *nodeName)
	{
		TiXmlDocument doc("Config.xml");
		bool loadOkay = doc.LoadFile();

		if (!loadOkay)
		{
			printf("Could not load test file 'Config.xml'. Error='%s'. Exiting.\n", doc.ErrorDesc());
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
