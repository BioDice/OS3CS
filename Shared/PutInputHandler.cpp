#include "PutInputHandler.h"

namespace OS3CS
{
	PutInputHandler::PutInputHandler(void)
	{
	}


	PutInputHandler::~PutInputHandler(void)
	{
	}

	void PutInputHandler::Process(Socket* socket)
	{
	}

	InputHandler* PutInputHandler::Clone()
	{
		return new PutInputHandler();
	}
}