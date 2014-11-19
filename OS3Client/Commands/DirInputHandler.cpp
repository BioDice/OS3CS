#include "DirInputHandler.h"

namespace OS3CS
{
	DirInputHandler::DirInputHandler(void)
	{
	}


	DirInputHandler::~DirInputHandler(void)
	{
	}

	void DirInputHandler::Process(Socket* socket, string response)
	{
		// not used anymore
	}

	InputHandler* DirInputHandler::Clone()
	{
		return new DirInputHandler();
	}
}