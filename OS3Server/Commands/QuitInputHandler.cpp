#include "QuitInputHandler.h"

namespace OS3CS
{
	QuitInputHandler::QuitInputHandler(void)
	{
	}


	QuitInputHandler::~QuitInputHandler(void)
	{
	}

	void QuitInputHandler::Process(Socket* socket, string response)
	{
		socket->writeline("Thank you for using Craptastic Server\r\nWe hope we never see you again. BYE!");
		_CrtDumpMemoryLeaks();
		socket->close();
	}

	InputHandler* QuitInputHandler::Clone()
	{
		return new QuitInputHandler();
	}
}