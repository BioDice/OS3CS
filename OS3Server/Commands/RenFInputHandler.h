#pragma once

#include "../../Shared/InputHandler.h"
#include "../../Shared/Socket.h"
#include "../../Shared/Globals.h"
#include <string>
#include "../../Shared/DirectoryWriter.h"
using namespace std;

namespace OS3CS
{
	class RenFInputHandler : public InputHandler
	{
	public:
		RenFInputHandler(void);
		~RenFInputHandler(void);

		virtual void Process(Socket*, string);
		virtual InputHandler* Clone();
	};
}