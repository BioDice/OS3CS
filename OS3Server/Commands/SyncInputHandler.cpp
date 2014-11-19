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
		DirectoryWriter *writer = new DirectoryWriter();
		writer->InitList();
		int version = writer->isLeading();
		socket->writeline(std::to_string(version));
		socket->writeline("");
		char line[256 + 1];
		while (socket->readline(line, 256) > 0)
		{
			//wachten
		}

	}

	InputHandler* SyncInputHandler::Clone()
	{
		return new SyncInputHandler();
	}
}