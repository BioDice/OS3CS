#include "SyncInputHandler.h"

namespace OS3CS
{
	SyncInputHandler::SyncInputHandler(void)
	{
	}


	SyncInputHandler::~SyncInputHandler(void)
	{
	}

	void SyncInputHandler::Process(Socket* socket, string response)
	{
	}

	InputHandler* SyncInputHandler::Clone()
	{
		return new SyncInputHandler();
	}
}