#pragma once

#include "InputHandler.h"
#include "Socket.h"

namespace OS3CS
{
	class PutInputHandler : public InputHandler
	{
	public:
		PutInputHandler(void);
		~PutInputHandler(void);

		virtual void Process(Socket*);
		virtual InputHandler* Clone();
	};
}