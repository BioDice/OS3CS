#include "PutInputHandler.h"

namespace OS3CS
{
	PutInputHandler::PutInputHandler(void)
	{
	}


	PutInputHandler::~PutInputHandler(void)
	{
	}

	void PutInputHandler::Process(Socket* socket, string response)
	{
		try
		{
			vector<string> segments = vector<string>();
			if (!FormatCommandPath(response, segments, 2))
			{
				cout << "Syntax error: use put [remote file] [local dir]" << endl;
				return;
			}

			char buffer[MAXBUFFERSIZE + 1];
			int bytesToRead, bytesRead, fileSize;
			// merge path with filename
			string path = ConvertPath(segments[0]) + "/" + GetFileName(segments[1]);
			if (strcmp(segments[0].c_str(), "null") == 0)
			{
				path = ConvertPath(Currentpath()+"/mapje") + "/" + GetFileName(segments[1]);
			}
			TransferManager *manager = new TransferManager();
			socket->writeline("READY");
			manager->ReceiveFile(socket,path);

			delete manager;

			socket->writeline("");

			DirectoryWriter *writer = new DirectoryWriter();
			std::string str = GetFileName(segments[1]);
			char*filename = &str[0];

			DirectoryReader * reader = new DirectoryReader();
			DIR* pDir = reader->open(Currentpath() + PATHSEPERATOR + "mapje");
			time_t iLastModified = reader->getLastModifiedTime(path);
			writer->WriteNode(filename, path, to_string(iLastModified));
		}
		catch (exception ex)
		{
			cout << "Something went wrong..." << endl;
		}
	}

	InputHandler* PutInputHandler::Clone()
	{
		return new PutInputHandler();
	}
}