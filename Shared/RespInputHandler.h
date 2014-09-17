#pragma once

#include "InputHandler.h"
#include "Socket.h"

namespace OS3CS
{
	class RespInputHandler : public InputHandler
	{
	public:
		RespInputHandler(void);
		~RespInputHandler(void);

		virtual void Process(Socket*);
		virtual InputHandler* Clone();
	};
}