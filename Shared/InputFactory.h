#pragma once

#include <map>
#include <string>
#include "InputHandler.h"


using namespace std;

namespace OS3CS 
{
	class InputFactory
	{
	protected:
		typedef map<string, InputHandler*> ShizzleMap;
		ShizzleMap commands;

	public:
		InputFactory();
		virtual ~InputFactory();

		virtual void Initialize() = 0;
		InputHandler* CreateHandler(string input);
		
	};
}