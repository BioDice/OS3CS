#pragma once

#include <string>
#include <vector>
#include <sstream>

using namespace std;

namespace OS3CS
{
	void StrSplit(string str, vector<string> &tokens, char delim);
	void StrSplit(string str, vector<string> &tokens, char delim, int iLimit);
}