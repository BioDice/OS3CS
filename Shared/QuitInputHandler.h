#pragma once

#include "InputHandler.h"
#include "Socket.h"

namespace OS3CS
{
	class QuitInputHandler : public InputHandler
	{
	public:
		QuitInputHandler(void);
		~QuitInputHandler(void);

		virtual void Process(Socket*);
		virtual InputHandler* Clone();
	};
}