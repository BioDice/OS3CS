#include "InputFactory.h"

namespace OS3CS 
{
	InputFactory::InputFactory()
	{

	}

	InputFactory::~InputFactory()
	{

	}

	/*InputFactory::ShizzleMap InputFactory::commands;*/

	InputHandler* InputFactory::CreateHandler(string input)
	{
		ShizzleMap::const_iterator it = commands.find(input);
		if (it == commands.end())
			return NULL;
		else
			return it->second->Clone();
	}
}
