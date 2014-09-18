#include "stdafx.h"
#include "ClientFactory.h"

namespace OS3CS
{
	ClientFactory::ClientFactory()
	{
	}


	ClientFactory::~ClientFactory()
	{
	}

	void ClientFactory::Initialize()
	{
		DirInputHandler *dir = new DirInputHandler();
		GetInputHandler *get = new GetInputHandler();
		PutInputHandler *put = new PutInputHandler();
		RenFInputHandler *ren = new RenFInputHandler();
		SyncInputHandler *sync = new SyncInputHandler();
		RespInputHandler *resp = new RespInputHandler();
		commands["dir"] = dir;
		commands["get"] = get;
		commands["put"] = put;
		commands["ren"] = ren;
		commands["sync"] = sync;
		commands["resp"] = resp;
	}
}