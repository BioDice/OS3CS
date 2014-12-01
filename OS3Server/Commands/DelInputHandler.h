#pragma once

#include "../../Shared/InputHandler.h"
#include "../../Shared/Socket.h"
#include "../../Shared/Globals.h"
#include <string>
#include "../../Shared/DirectoryWriter.h"
using namespace std;

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