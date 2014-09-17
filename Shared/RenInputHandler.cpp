#include "RenInputHandler.h"

namespace OS3CS
{
	RenInputHandler::RenInputHandler(void)
	{
	}


	RenInputHandler::~RenInputHandler(void)
	{
	}

	void RenInputHandler::Process(Socket* socket)
	{
	}

	InputHandler* RenInputHandler::Clone()
	{
		return new RenInputHandler();
	}
}