#pragma once
#include "tinyxml/tinyxml/tinyxml.h"
#include <stdlib.h>
#include "Socket.h"
#include "TransferManager.h"
#include "DirectoryReader.h"
#include "Globals.h"
namespace OS3CS{
	class DirectoryWriter
	{
	public:
		DirectoryWriter(void);
		~DirectoryWriter(void);

		void Sync(Socket *socket);
		void InitList();
		void DeleteNode(char *nodeName);
		void WriteNode(string name, string directory);
		void UpdateNode(char*nodeName, char*renamename);
		int isLeading();
	};
}