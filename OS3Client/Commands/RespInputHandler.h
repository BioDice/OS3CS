#pragma once

#include "../../Shared/InputHandler.h"
#include "../../Shared/Socket.h"

namespace OS3CS
{
	class RespInputHandler : public InputHandler
	{
	public:
		RespInputHandler(void);
		~RespInputHandler(void);

		virtual void Process(Socket*, string);
		virtual InputHandler* Clone();
	};
}