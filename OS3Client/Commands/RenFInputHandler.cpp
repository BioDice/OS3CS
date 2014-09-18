#include "RenFInputHandler.h"

namespace OS3CS
{
	RenFInputHandler::RenFInputHandler(void)
	{
	}


	RenFInputHandler::~RenFInputHandler(void)
	{
	}

	void RenFInputHandler::Process(Socket* socket, string response)
	{
	}

	InputHandler* RenFInputHandler::Clone()
	{
		return new RenFInputHandler();
	}
}