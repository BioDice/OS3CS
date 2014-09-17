#pragma once

#include "InputHandler.h"
#include "Socket.h"

namespace OS3CS
{
	class DirInputHandler : public InputHandler
	{
	public:
		DirInputHandler(void);
		~DirInputHandler(void);

		virtual void Process(Socket*);
		virtual InputHandler* Clone();
	};
}