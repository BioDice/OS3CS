#pragma once

#include "../../Shared/InputHandler.h"
#include "../../Shared/Socket.h"

namespace OS3CS
{
	class InfoInputHandler : public InputHandler
	{
	public:
		InfoInputHandler();
		~InfoInputHandler();
	
		virtual void Process(Socket*, string);
		virtual InputHandler* Clone();
	};
}