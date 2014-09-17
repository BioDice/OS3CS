#include "RespInputHandler.h"

namespace OS3CS
{
	RespInputHandler::RespInputHandler(void)
	{
	}


	RespInputHandler::~RespInputHandler(void)
	{
	}

	void RespInputHandler::Process(Socket* socket)
	{
	}

	InputHandler* RespInputHandler::Clone()
	{
		return new RespInputHandler();
	}
}