#include "stdafx.h"
#include "Globals.h"

namespace OS3CS
{
	void StrSplit(string value, string del, vector<string> &arr)
	{
		string delimiter = del;

		size_t pos = 0;
		string token;
		while ((pos = value.find(delimiter)) != string::npos) {
			token = value.substr(0, pos);
			cout << token << endl;
			value.erase(0, pos + delimiter.length());
			arr.push_back(token);
		}
		cout << value << endl;
	}
}