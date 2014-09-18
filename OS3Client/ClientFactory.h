#pragma once
#include "../Shared/InputFactory.h"
#include "Commands/RespInputHandler.h"
#include "Commands/DirInputHandler.h"
#include "Commands/GetInputHandler.h"
#include "Commands/PutInputHandler.h"
#include "Commands/RenFInputHandler.h"
#include "Commands/SyncInputHandler.h"

namespace OS3CS
{
	class ClientFactory : public InputFactory
	{
	public:
		ClientFactory();
		~ClientFactory();

		virtual void Initialize();
	};
}