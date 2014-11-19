#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

namespace OS3CS
{
	const int MAXBUFFERSIZE = 1024;
	const int MAXPATH = 256;
	string Currentpath();
	void StrSplit(string str, vector<string> &tokens, char delim);
	void StrSplit(string str, vector<string> &tokens, char delim, int iLimit);
	void StripWhiteSpaces(vector<string> &tokens);
	string GetFileName(string path);
	string ConvertPath(string path);
	bool FormatCommandPath(string commandLine, vector<string> &tokens, int outputNumber);
	string FindAndReplace(string &s, string toReplace, string replaceWith);
}