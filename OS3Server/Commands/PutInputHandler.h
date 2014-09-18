#pragma once

#include "../../Shared/InputHandler.h"
#include "../../Shared/Socket.h"

namespace OS3CS
{
	class PutInputHandler : public InputHandler
	{
	public:
		PutInputHandler(void);
		~PutInputHandler(void);

		virtual void Process(Socket*, string);
		virtual InputHandler* Clone();
	};
}