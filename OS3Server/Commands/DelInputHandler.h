#pragma once

#include "../../Shared/InputHandler.h"
#include "../../Shared/Socket.h"

namespace OS3CS
{
	class DelInputHandler : public InputHandler
	{
	public:
		DelInputHandler(void);
		~DelInputHandler(void);

		virtual void Process(Socket*, string);
		virtual InputHandler* Clone();
	};
}