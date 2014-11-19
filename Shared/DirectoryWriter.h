#pragma once
#include "tinyxml/tinyxml/tinyxml.h"
#include <stdlib.h>
#include "Socket.h"
#include "TransferManager.h"

namespace OS3CS{
	class DirectoryWriter
	{
	public:
		DirectoryWriter(void);
		~DirectoryWriter(void);

		void Sync(Socket *socket);
		void InitList();
		void DeleteNode(char *nodeName);
		void WriteNode(char *nodeName, char*directory);
		void UpdateNode(char*nodeName, char*renamename);
		int isLeading();
	};
}