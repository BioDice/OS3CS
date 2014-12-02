#pragma once

#include <string>
#include "../Shared/Socket.h"
#include "../Shared/Globals.h"
#include "../Shared/SocketException.h"
#include "../Shared/InputHandler.h"
#include "../Shared/InputFactory.h"
#include "ServerFactory.h"
using namespace std;

namespace OS3CS
{
	class Server
	{
	private:
		InputFactory *inputFactory;

	public:
		Server(void);
		~Server(void);

		void handle(Socket *socket);
		void listen(int port);

		bool IsRunning = true;
	};
}