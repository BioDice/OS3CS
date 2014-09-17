#include "InputFactory.h"

namespace OS3CS 
{
	InputFactory::InputFactory()
	{

	}

	InputFactory::~InputFactory()
	{

	}

	InputFactory::ShizzleMap InputFactory::commands;

	void InputFactory::InitializeClient()
	{
		DirInputHandler *dir = new DirInputHandler();
		GetInputHandler *get = new GetInputHandler();
		PutInputHandler *put = new PutInputHandler();
		QuitInputHandler *quit = new QuitInputHandler();
		RenInputHandler *ren = new RenInputHandler();
		SyncInputHandler *sync = new SyncInputHandler();
		RespInputHandler *resp = new RespInputHandler();
		commands["dir"] = dir;
		commands["get"] = get;
		commands["put"] = put;
		commands["ren"] = ren;
		commands["sync"] = sync;
		commands["resp"] = resp;
	}

	void InputFactory::InitializeServer()
	{
		DelInputHandler *del = new DelInputHandler();
		DirInputHandler *dir = new DirInputHandler();
		GetInputHandler *get = new GetInputHandler();
		InfoInputHandler *info = new InfoInputHandler();
		PutInputHandler *put = new PutInputHandler();
		QuitInputHandler *quit = new QuitInputHandler();
		RenInputHandler *ren = new RenInputHandler();
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

	InputHandler* InputFactory::CreateHandler(string input)
	{
		ShizzleMap::const_iterator it = commands.find(input);
		if (it == commands.end())
			return NULL;
		else
			return it->second->Clone();
	}
}
