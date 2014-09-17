#pragma once

#include "InputHandler.h"
#include "Socket.h"

namespace OS3CS
{
	class RenInputHandler : public InputHandler
	{
	public:
		RenInputHandler(void);
		~RenInputHandler(void);

		virtual void Process(Socket*);
		virtual InputHandler* Clone();
	};
}