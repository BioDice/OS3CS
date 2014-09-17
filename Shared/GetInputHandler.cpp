#include "GetInputHandler.h"

namespace OS3CS
{
	GetInputHandler::GetInputHandler(void)
	{
	}


	GetInputHandler::~GetInputHandler(void)
	{
	}

	void GetInputHandler::Process(Socket* socket)
	{
	}

	InputHandler* GetInputHandler::Clone()
	{
		return new GetInputHandler();
	}
}