#pragma once
#include "Socket.h"
#include "Globals.h"
#if defined(__APPLE__) || defined(__linux__)
#include <stdio.h>
#include <string.h>
#else
#include <string>
#endif
#include <fstream>

using namespace std;

namespace OS3CS {
	class TransferManager
	{
	public:
		TransferManager();
		~TransferManager();
		void ReceiveFile(Socket*socket,string response);
		void SendFile(Socket*socket,string response);
	};
}
