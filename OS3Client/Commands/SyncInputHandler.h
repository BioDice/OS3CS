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
		virtual void Process(Socket*,string response);
		virtual InputHandler* Clone();
	};
}