#pragma once

#include <fstream>
#include "../../Shared/InputHandler.h"
#include "../../Shared/Socket.h"
#include "../../Shared/Globals.h"
#include "../../Shared/TransferManager.h"
#include <string>
#include "../../Shared/DirectoryWriter.h"
using namespace std;

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