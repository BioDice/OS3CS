#pragma once

#include "InputHandler.h"
#include "Socket.h"

namespace OS3CS
{
	class GetInputHandler : public InputHandler
	{
	public:
		GetInputHandler(void);
		~GetInputHandler(void);

		virtual void Process(Socket*);
		virtual InputHandler* Clone();
	};
}