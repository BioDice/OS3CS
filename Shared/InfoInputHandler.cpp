#include "InfoInputHandler.h"

namespace OS3CS
{
	InfoInputHandler::InfoInputHandler()
	{
	}


	InfoInputHandler::~InfoInputHandler()
	{
	}

	void InfoInputHandler::Process(Socket* socket)
	{
		socket->write("Test");
		socket->writeline("");
	}

	InputHandler* InfoInputHandler::Clone()
	{
		return new InfoInputHandler();
	}
}