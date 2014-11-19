#pragma once

#include "../../Shared/InputHandler.h"
#include "../../Shared/Socket.h"
#include "../../Shared/Globals.h"
#include "../../Shared/DirectoryWriter.h"
#include <string>
using namespace std;

namespace OS3CS
{
	class SyncInputHandler : public InputHandler
	{
	public:
		SyncInputHandler(void);
		~SyncInputHandler(void);

		virtual void Process(Socket*, string);
		virtual InputHandler* Clone();
	};
}