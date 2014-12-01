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
	static int Counter = 0;
	static const string PATHSEPERATOR =
	#if defined(__APPLE__) || defined(__linux__)
			"/";
	#else
			"\\";
	#endif

	static const char PATHQUOTES =
	#if defined(__APPLE__) || defined(__linux__)
		'\'';
	#else
		'\"';
	#endif

	//static const char PATHESCAPE = 
	//#if defined(__APPLE__) || defined(__linux__)
	//		';
	//#else
	//		";
	//#endif

		static const char* OSRUNNING =
	#if defined(__APPLE__) || defined(__linux__)
			"GNU/Linux";
	#else
			"Win32";
	#endif

	static const int BUFFERSIZE = 20480;

	static const char DELIMITER = '|';
	string Currentpath();
	void StrSplit(string str, vector<string> &tokens, char delim);
	void StrSplit(string str, vector<string> &tokens);
	void StripWhiteSpaces(vector<string> &tokens);
	string GetFileName(string path);
	string ConvertPath(string path);
	bool FormatCommandPath(string commandLine, vector<string> &tokens, int outputNumber);
	bool FormatConnectionString(string commandLine, vector<string> &tokens, int outputNumber);
	string FindAndReplace(string &s, string toReplace, string replaceWith);
}