#pragma once
#if defined(__APPLE__) || defined(__linux__)

#include <utime.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#else
//windows
#include "../Shared/dirent.h"
#include <sys/utime.h>
#include <direct.h>

#endif

#include <string>
#include <vector>
#include <time.h>
#include "../Shared/Globals.h"

using namespace std;
namespace OS3CS
{
	class DirectoryReader
	{
	public:
		static void del(string);
		static bool isDir(string);
		static bool isFile(string);

		static bool createSubDirectories(string, bool);

		static time_t getLastModifiedTime(string szPath);
		static void setLastModifiedTime(string, time_t);
		static DIR* open(string, DIR* dir);
	private:
		
	};
}
