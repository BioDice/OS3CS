#include "DelInputHandler.h"

namespace OS3CS
{
	DelInputHandler::DelInputHandler(void)
	{
	}


	DelInputHandler::~DelInputHandler(void)
	{
	}

	void DelInputHandler::Process(Socket* socket, string response)
	{
	}

	InputHandler* DelInputHandler::Clone()
	{
		return new DelInputHandler();
	}
}