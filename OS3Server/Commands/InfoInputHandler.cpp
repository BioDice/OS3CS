#include "InfoInputHandler.h"

namespace OS3CS
{
	InfoInputHandler::InfoInputHandler()
	{
	}


	InfoInputHandler::~InfoInputHandler()
	{
	}

	void InfoInputHandler::Process(Socket* socket, string response)
	{
		socket->writeline("Craptastic Server\nVersion: -0.1");
		socket->writeline("");
	}

	InputHandler* InfoInputHandler::Clone()
	{
		return new InfoInputHandler();
	}
}