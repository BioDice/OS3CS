#pragma once

#include "InputHandler.h"
#include "Socket.h"

namespace OS3CS
{
	class DelInputHandler : public InputHandler
	{
	public:
		DelInputHandler(void);
		~DelInputHandler(void);

		virtual void Process(Socket*);
		virtual InputHandler* Clone();
	};
}