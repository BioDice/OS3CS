#include "InputFactory.h"

namespace OS3CS 
{
	InputFactory::InputFactory()
	{

	}

	InputFactory::~InputFactory()
	{
		for (std::map<string, InputHandler*>::iterator MapItor = commands.begin(); MapItor != commands.end(); ++MapItor)
		{
			InputHandler* Value = (*MapItor).second;
			delete Value;
		}
		/*for (std::map<std::string, InputHandler*>::iterator itr = commands.begin(); itr != commands.end(); itr++)
		{
			delete itr->second;
		}*/
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
