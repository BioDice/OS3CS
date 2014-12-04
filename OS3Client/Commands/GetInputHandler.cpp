#include "GetInputHandler.h"

namespace OS3CS
{
	GetInputHandler::GetInputHandler(void)
	{
	}


	GetInputHandler::~GetInputHandler(void)
	{
	}

	void GetInputHandler::Process(Socket* socket, string response)
	{
		try
		{
			vector<string> segments = vector<string>();
			if (!FormatCommandPath(response, segments, 2))
			{
				cout << "Syntax error: use put [remote file] [local dir]" << endl;
				return;
			}
			socket->writeline(response);
			string path = ConvertPath(segments[1]) + "/" + GetFileName(segments[0]);
			TransferManager *manager = new TransferManager();
			manager->ReceiveFile(socket,path);
			delete manager;

			DirectoryWriter *writer = new DirectoryWriter();
			std::string str = GetFileName(segments[0]);
			char*filename = &str[0];

			vector<string> pathsegments = vector<string>();
			StrSplit(path, pathsegments);

			string directory = "";
			vector<string>temp = pathsegments;
			for (size_t i = 0; i < temp.size(); i++)
			{
				if (strcmp(temp[i].c_str(), "mapje") == 0)
				{
					break;
				}
				else
				{
					pathsegments.erase(pathsegments.begin());
				}
			}

			for (size_t i = 0; i < pathsegments.size(); i++)
			{
				directory.append(pathsegments[i]);
				if (i != pathsegments.size() - 1)
				{
					directory.append("/");
				}
			}

			DirectoryReader* reader = new DirectoryReader();
			DIR* pDir = NULL;
			pDir = reader->open(Currentpath() + PATHSEPERATOR + "mapje", pDir);
			time_t iLastModified = reader->getLastModifiedTime(path);
			writer->WriteNode(filename, directory, to_string(iLastModified));
			delete writer;
			// wordt niet gebruikt?
			closedir(pDir);
			delete reader;

		}
		catch (exception ex)
		{
			cout << "Something went wrong..." << endl;
			return;
		}
	}

	InputHandler* GetInputHandler::Clone()
	{
		return new GetInputHandler();
	}
}