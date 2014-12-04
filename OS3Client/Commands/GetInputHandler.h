#pragma once

#include <fstream>
#include "../../Shared/InputHandler.h"
#include "../../Shared/Socket.h"
#include "../../Shared/Globals.h"
#include "../../Shared/TransferManager.h"
#include "../../Shared/DirectoryWriter.h"
namespace OS3CS
{
	class GetInputHandler : public InputHandler
	{
	public:
		GetInputHandler(void);
		~GetInputHandler(void);

		virtual void Process(Socket*, string);
		virtual InputHandler* Clone();
	};
}