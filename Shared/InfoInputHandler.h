#pragma once

#include "InputHandler.h"
#include "Socket.h"

namespace OS3CS
{
	class InfoInputHandler : public InputHandler
	{
	public:
		InfoInputHandler();
		~InfoInputHandler();
	
		virtual void Process(Socket*);
		virtual InputHandler* Clone();
	};
}