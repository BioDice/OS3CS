#pragma once

#include "../../Shared/InputHandler.h"
#include "../../Shared/Socket.h"

namespace OS3CS
{
	class GetInputHandler : public InputHandler
	{
	public:
		GetInputHandler(void);
		~GetInputHandler(void);

		virtual void Process(Socket*, string);
		virtual InputHandler* Clone();
	};
}