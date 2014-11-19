#pragma once
#include "../../OS3CS/Shared/tinyxml/tinyxml/tinyxml.h"
#include <stdlib.h>
class DirectoryWriter
{
public:
	DirectoryWriter(void);
	~DirectoryWriter(void);

	void InitList();
	void DeleteNode(char *nodeName);
	void WriteNode(char *nodeName,char*directory);
	void UpdateNode(char*nodeName,char*renamename);
	int isLeading();
};

