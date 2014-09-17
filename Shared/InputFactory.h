#pragma once

#include <map>
#include <string>
#include "InputHandler.h"
#include "DelInputHandler.h"
#include "DirInputHandler.h"
#include "GetInputHandler.h"
#include "InfoInputHandler.h"
#include "PutInputHandler.h"
#include "QuitInputHandler.h"
#include "RenInputHandler.h"
#include "SyncInputHandler.h"
#include "RespInputHandler.h"

using namespace std;

namespace OS3CS 
{
	class InputFactory
	{
	private:
		typedef map<string, InputHandler*> ShizzleMap;
		static ShizzleMap commands;
		

	public:
		InputFactory();
		~InputFactory();

		void InitializeClient();
		void InitializeServer();
		static InputHandler* CreateHandler(string input);
		
	};
}