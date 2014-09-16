#pragma once

#include "Socket.h"

namespace OS3CS 
{
	class InputHandler
	{
	public:
		InputHandler();
		~InputHandler();

		virtual void Process(Socket*) = 0;
		virtual InputHandler* Clone() = 0;
	};
}