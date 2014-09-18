#pragma once

#include "../../Shared/InputHandler.h"
#include "../../Shared/Socket.h"

namespace OS3CS
{
	class QuitInputHandler : public InputHandler
	{
	public:
		QuitInputHandler(void);
		~QuitInputHandler(void);

		virtual void Process(Socket*, string);
		virtual InputHandler* Clone();
	};
}