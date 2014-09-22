#pragma once

#include "../../Shared/InputHandler.h"
#include "../../Shared/Socket.h"
#include "../../Shared/Globals.h"
#include <string>
using namespace std;

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