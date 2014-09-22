#include "DirInputHandler.h"

namespace OS3CS
{
	DirInputHandler::DirInputHandler(void)
	{
	}


	DirInputHandler::~DirInputHandler(void)
	{
	}

	void DirInputHandler::Process(Socket* socket, string response)
	{
		vector<string> segments = vector<string>();
		StrSplit(response, segments, ' ');

		ostringstream resp;
		struct stat info;
		if (segments.size() != 2)
		{
			cout << "SyntaxError - use: dir [remote dir]";
			socket->writeline("SyntaxError - use: dir [remote dir]");
			socket->writeline("");
		}
		else
		{
			const char *pathname = segments[1].c_str();
			if (stat(pathname, &info) != 0)
			{
				resp << "Cannot access <" << pathname << ">";
				cout << resp.str();
				socket->writeline(resp.str());
				socket->writeline("");
			}
			// directory exists
			else if (info.st_mode & S_IFDIR)  // S_ISDIR() doesn't exist on my windows 
			{
				//directory listing
				DIR*     dir;
				dirent*  pdir;

				dir = opendir(pathname); // open current directory

				while (pdir = readdir(dir)) {
					
					if (pdir->d_type == DT_DIR)
					{
						resp << "DIR: " << pdir->d_name;
					}
					else if (pdir->d_type == DT_REG)
					{
						resp << "FILE: " << pdir->d_name;
					}
					socket->writeline(resp.str());
					resp.str("");
				}
				socket->writeline("");
				closedir(dir);
				delete pdir;
			}
			else
			{
				resp << "<" << pathname << "> is no directory";
				cout << resp.str();
				socket->writeline(resp.str());
				socket->writeline("");
			}
		}
	}

	InputHandler* DirInputHandler::Clone()
	{
		return new DirInputHandler();
	}
}