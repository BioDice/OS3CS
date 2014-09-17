#pragma once

#include "InputHandler.h"
#include "Socket.h"

namespace OS3CS
{
	class SyncInputHandler : public InputHandler
	{
	public:
		SyncInputHandler(void);
		~SyncInputHandler(void);

		virtual void Process(Socket*);
		virtual InputHandler* Clone();
	};
}