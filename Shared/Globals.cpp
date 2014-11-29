#include "Globals.h"
#include <stdio.h>

#ifdef WIN32
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

namespace OS3CS
{

	string Currentpath()
	{
		char cCurrentPath[FILENAME_MAX];

		if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
		{
			
		}

		cCurrentPath[sizeof(cCurrentPath) - 1] = '/0'; /* not really required */
		return ConvertPath(cCurrentPath);
	}

	void StrSplit(string str, vector<string> &tokens, char delim)
	{
		string buf;
		stringstream ss(str); // Insert the string into a stream

		while (getline(ss, buf, delim))
		{
			if (buf != " ")
				tokens.push_back(buf);
		}
	}

	void StrSplit(string str, vector<string> &tokens)
	{
		string buf;
		stringstream ss(str); // Insert the string into a stream
		char item = '/';
		while (getline(ss, buf, item))
		{
			if (buf != " ")
				tokens.push_back(buf);
		}
	}

	void StripWhiteSpaces(vector<string> &tokens)
	{
		for (int i = 0; i < tokens.size(); i++)
		{
			string str = tokens[i];
			if (str.size() > 0 && str[0] == ' ')
				str.erase(0, 1);
			if (str.size() > 0 && str[str.length()-1] == ' ')
				str.erase(str.length()-1);
			if (str.size() == 0)
			{
				tokens.erase(tokens.begin()+i);
				i--;
			}
			else
				tokens[i] = str;
		}
	}

	bool FormatCommandPath(string commandLine, vector<string> &tokens, int outputNumber)
	{
		commandLine = commandLine.erase(0, 4);
		StrSplit(commandLine, tokens, PATHQUOTES);
		if (tokens.size() == 1)
		{
			tokens.clear();
			StrSplit(commandLine, tokens, ' ');
		}

		StripWhiteSpaces(tokens);
		if (tokens.size() == outputNumber)
			return true;
		else
			return false;
	}

	bool FormatConnectionString(string commandLine, vector<string> &tokens, int outputNumber)
	{
		StrSplit(commandLine, tokens, PATHQUOTES);
		if (tokens.size() == 1)
		{
			tokens.clear();
			StrSplit(commandLine, tokens, ' ');
		}

		StripWhiteSpaces(tokens);
		if (tokens.size() == outputNumber)
			return true;
		else
			return false;
	}

	string GetFileName(string path)
	{
		vector<string> segments = vector<string>();
		StrSplit(ConvertPath(path), segments);
		return segments[segments.size()-1];
	}

	string ConvertPath(string path)
	{
		string temp = path;
		std::replace(temp.begin(), temp.end(), '\\', '/');
		
		return temp;
	}

	string FindAndReplace(string &s, string toReplace, string replaceWith)
	{
		return(s.replace(s.find(toReplace), toReplace.length(), replaceWith));
	}
}