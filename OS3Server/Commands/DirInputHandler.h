#pragma once

#include "../../Shared/InputHandler.h"
#include "../../Shared/Socket.h"

namespace OS3CS
{
	class DirInputHandler : public InputHandler
	{
	public:
		DirInputHandler(void);
		~DirInputHandler(void);

		virtual void Process(Socket*, string);
		virtual InputHandler* Clone();
	};
}