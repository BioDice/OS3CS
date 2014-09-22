#pragma once

#include "../../Shared/InputHandler.h"
#include "../../Shared/Socket.h"
#include "../../Shared/Globals.h"
#include "../../Shared/dirent.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <string>
using namespace std;

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