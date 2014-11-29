#pragma once
#include "../Shared/InputFactory.h"
#include "Commands/DelInputHandler.h"
#include "Commands/DirInputHandler.h"
#include "Commands/GetInputHandler.h"
#include "Commands/InfoInputHandler.h"
#include "Commands/PutInputHandler.h"
#include "Commands/QuitInputHandler.h"
#include "Commands/RenFInputHandler.h"
#include "Commands/SyncInputHandler.h"

namespace OS3CS
{
	class ServerFactory : public InputFactory
	{
	public:
		ServerFactory();
		virtual ~ServerFactory();

		virtual void Initialize();
	};
}