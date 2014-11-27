#pragma once
#include "tinyxml/tinyxml/tinyxml.h"
#include <stdlib.h>
#include "Socket.h"
#include "TransferManager.h"
#include "DirectoryReader.h"
#include "Globals.h"
#include <map>

namespace OS3CS{
	class DirectoryWriter
	{
	public:
		DirectoryWriter(void);
		~DirectoryWriter(void);
		typedef map<string, string> directoryMap;
		void Sync(Socket *socket);
		void InitList();
		void RecursiveList(string szPath, map<string, string> &value_type, bool bRecursive);
		void DeleteNode(char *nodeName);
		void WriteNode(string name, string directory,string editDate);
		void UpdateNode(string nodeName, string renamename);
		int isLeading();
	};
}
