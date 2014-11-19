#pragma once
#include "Socket.h"
#include "Globals.h"
#include <string>
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
