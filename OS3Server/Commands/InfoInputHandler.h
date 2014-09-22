#pragma once

#include "../../Shared/InputHandler.h"
#include "../../Shared/Socket.h"
#include "../../Shared/Globals.h"
#include <string>
using namespace std;

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