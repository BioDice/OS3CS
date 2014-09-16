#pragma once

#include <map>
#include <string>
#include "InputHandler.h"
#include "InfoInputHandler.h"

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

		void Initialize();
		static InputHandler* CreateHandler(string input);
		
	};
}