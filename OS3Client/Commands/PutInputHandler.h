#pragma once

#include <fstream>
#include "../../Shared/InputHandler.h"
#include "../../Shared/Socket.h"
#include "../../Shared/Globals.h"
#include "../../Shared/TransferManager.h"
namespace OS3CS
{
	class PutInputHandler : public InputHandler
	{
	private:
		

	public:
		PutInputHandler(void);
		~PutInputHandler(void);

		virtual void Process(Socket*, string);
		virtual InputHandler* Clone();
	};
}