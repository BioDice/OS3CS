#pragma once

#include "../../Shared/InputHandler.h"
#include "../../Shared/Socket.h"
#include "../../Shared/DirectoryWriter.h"
#include <fstream>
#include "../../Shared/Globals.h"

namespace OS3CS
{
	class SyncInputHandler : public InputHandler
	{
	public:
		SyncInputHandler(void);
		~SyncInputHandler(void);
		void SetXML(Socket*socket);
		void GetXML(Socket*socket);
		void Delete(Socket *socket, string name);
		void Put(Socket *socket, string local, string remote);
		void Sync(Socket *socket);
		virtual void Process(Socket*,string response);
		virtual InputHandler* Clone();
	};
}