#include "DirectoryReader.h"

using namespace std;

namespace OS3CS
{
	void DirectoryReader::del(string)
	{

	}

	DIR* DirectoryReader::open(string szPath)
	{
		DIR* pDir = NULL;

		pDir = opendir(szPath.c_str());

		if (pDir == NULL)
		{
			delete pDir;
			throw("Directory cannot be opened");
		}

		return pDir;
	}

	bool DirectoryReader::isDir(string szPath)
	{
		struct stat s;

		if (stat(szPath.c_str(), &s) == 0)
			return ((s.st_mode & S_IFDIR) == S_IFDIR);
		else
			throw("Can't stat dir");
	}

	void DirectoryReader::createSubDirectories(string szPath, bool bIgnoreLastPart)
	{
		vector<string> vsSubDirectories = vector<string>();
		StrSplit(szPath, vsSubDirectories);

		if (vsSubDirectories.size() < 2)
			throw("Incorrect path syntax");

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
					throw("Could not make subdirectory.");
			}
		}
	}

	bool DirectoryReader::isFile(string szPath)
	{
		struct stat s;

		if (stat(szPath.c_str(), &s) == 0)
			return ((s.st_mode & S_IFDIR) != S_IFDIR);
		else
			throw("Can't stat file");
	}

	time_t DirectoryReader::getLastModifiedTime(string szPath)
	{
		struct stat s;

		if (stat(szPath.c_str(), &s) == 0)
			return s.st_mtime;
		else
			throw("Can't stat file");
	}

	void DirectoryReader::setLastModifiedTime(string szPath, time_t lModTime)
	{
		struct stat s;
		struct utimbuf new_times;

		if (stat(szPath.c_str(), &s) < 0)
		{
			throw("Can't stat file");
		}

		new_times.actime = s.st_atime;
		new_times.modtime = lModTime;

		if (utime(szPath.c_str(), &new_times) < 0)
		{
			throw("Can't utime file");
		}

	}
}
