#include "ServerFactory.h"

namespace OS3CS
{
	ServerFactory::ServerFactory()
	{
	}


	ServerFactory::~ServerFactory()
	{
	}

	void ServerFactory::Initialize()
	{
		DelInputHandler *del = new DelInputHandler();
		DirInputHandler *dir = new DirInputHandler();
		GetInputHandler *get = new GetInputHandler();
		InfoInputHandler *info = new InfoInputHandler();
		PutInputHandler *put = new PutInputHandler();
		QuitInputHandler *quit = new QuitInputHandler();
		RenFInputHandler *ren = new RenFInputHandler();
		SyncInputHandler *sync = new SyncInputHandler();
		commands["del"] = del;
		commands["dir"] = dir;
		commands["get"] = get;
		commands["info"] = info;
		commands["put"] = put;
		commands["quit"] = quit;
		commands["ren"] = ren;
		commands["sync"] = sync;
	}
}