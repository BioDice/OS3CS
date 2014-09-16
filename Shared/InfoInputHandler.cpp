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
		socket->writeline("Craptastic Server\r\nVersion: -0.1\r\n");
		socket->writeline("");
	}

	InputHandler* InfoInputHandler::Clone()
	{
		return new InfoInputHandler();
	}
}