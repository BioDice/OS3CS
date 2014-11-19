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
			TransferManager *manager = new TransferManager();

			manager->ReceiveFile(socket,path);
			DirectoryWriter *writer = new DirectoryWriter();
			std::string str = GetFileName(segments[1]);
			char*filename = &str[0];

			std::string directory = FindAndReplace(Currentpath(), path, "");
			char*directoryname = &directory[0];

			writer->WriteNode(filename,directoryname);
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