#pragma once

#include "../../Shared/InputHandler.h"
#include "../../Shared/Socket.h"
#include "../../Shared/DirectoryWriter.h"
namespace OS3CS
{
	class SyncInputHandler : public InputHandler
	{
	public:
		SyncInputHandler(void);
		~SyncInputHandler(void);
		void SetXML(Socket*socket);
		virtual void Process(Socket*, string);
		virtual InputHandler* Clone();
	};
}