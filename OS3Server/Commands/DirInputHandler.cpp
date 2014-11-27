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
		ostringstream resp;
		struct stat info;
		vector<string> segments = vector<string>();
		if (!FormatCommandPath(response, segments, 1))
		{
			cout << "SyntaxError - use: dir [remote dir]";
			socket->writeline("SyntaxError - use: dir [remote dir]");
			socket->writeline("");
			return;
			
		}
		else
		{
			const char *pathname = segments[0].c_str();
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