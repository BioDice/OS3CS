#include "DirectoryReader.h"

using namespace std;

namespace OS3CS
{
	void DirectoryReader::del(string)
	{

	}

	DIR* DirectoryReader::open(string szPath, DIR* dir)
	{
		dir = opendir(szPath.c_str());

		if (dir == NULL)
		{
			delete dir;
			throw("Directory cannot be opened");
		}
		return dir;
	}

	bool DirectoryReader::isDir(string szPath)
	{
		struct stat s;

		if (stat(szPath.c_str(), &s) == 0)
			return ((s.st_mode & S_IFDIR) == S_IFDIR);
		else
			throw("Can't stat dir");
	}

	bool DirectoryReader::createSubDirectories(string szPath, bool bIgnoreLastPart)
	{
		vector<string> vsSubDirectories = vector<string>();
		StrSplit(szPath, vsSubDirectories);

		if (vsSubDirectories.size() < 2)
		{
			return false;
		}

		bool bDirectoryExists = false;
		string sCurrentDirectory(vsSubDirectories[0]);

		// Except first slot (drive letter, windows)
		for (int i = 1; i < (bIgnoreLastPart ? vsSubDirectories.size() - 1 : vsSubDirectories.size()); i++)
		{
			sCurrentDirectory.append(PATHSEPERATOR);
			sCurrentDirectory.append(vsSubDirectories[i]);

			try
			{
				bDirectoryExists = DirectoryReader::isDir(sCurrentDirectory);
			}
			catch (const char* ex) { bDirectoryExists = false; }

			if (bDirectoryExists == false)
			{
#if defined(__APPLE__) || defined(__linux__)
				if (mkdir(sCurrentDirectory.c_str(), 0777) != 0)
#else
				if (_mkdir(sCurrentDirectory.c_str()) != 0)
#endif
					return false;
			}
		}
		return true;
	}

	bool DirectoryReader::isFile(string szPath)
	{
		struct stat s;

		if (stat(szPath.c_str(), &s) == 0)
			return ((s.st_mode & S_IFDIR) != S_IFDIR);
		else
			return false;
	}

	time_t DirectoryReader::getLastModifiedTime(string szPath)
	{
		struct stat s;

		if (stat(szPath.c_str(), &s) == 0)
			return s.st_mtime;
		else
			return false;
	}

	void DirectoryReader::setLastModifiedTime(string szPath, time_t lModTime)
	{
		struct stat s;
		struct utimbuf new_times;

		if (stat(szPath.c_str(), &s) < 0)
		{
			return;
		}

		new_times.actime = s.st_atime;
		new_times.modtime = lModTime;

		if (utime(szPath.c_str(), &new_times) < 0)
		{
			return;
		}

	}
}
