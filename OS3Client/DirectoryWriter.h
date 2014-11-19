#pragma once
#include "tinyxml\tinyxml\tinyxml.h"
#include "stdafx.h"
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
	
};

