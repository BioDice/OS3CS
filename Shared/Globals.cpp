#include "Globals.h"

namespace OS3CS
{
	void StrSplit(string str, vector<string> &tokens, char delim)
	{
		string buf;
		stringstream ss(str); // Insert the string into a stream

		while (getline(ss, buf, delim))
			tokens.push_back(buf);
	}


	void StrSplit(string str, vector<string> &tokens, char delim, int iLimit)
	{
		string buf;
		stringstream ss(str); // Insert the string into a stream
		
		int iCount = 0;
		
		while (getline(ss, buf, delim))
		{
			tokens.push_back(buf);
			iCount++;

			if (iCount == iLimit - 1)
			{
				getline(ss, buf, '\0');
				tokens.push_back(buf);
				break;
			}
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

	string GetFileName(string path)
	{
		vector<string> segments = vector<string>();
		StrSplit(ConvertPath(path), segments, '/');
		return segments[segments.size()-1];
	}

	string ConvertPath(string path)
	{
		string temp = path;
		std::replace(temp.begin(), temp.end(), '\\', '/');
		return temp;
	}
}