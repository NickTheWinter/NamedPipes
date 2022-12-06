#include "HeaderServer.h"
int main()
{
	system("chcp 1251>nul");
	HANDLE hNamedPipe;
	LPSTR LPipeName = L"\\\\.\\pipe\\MyPipe";
	DWORD sizeBuffer = SIZE_BUFFER;
	LPWSTR text = (char*)calloc(sizeBuffer, sizeof(char));
	char message[SIZE_BUFFER];
	BOOL SuccessRead;
	DWORD readen;
	BOOL Connected;
	
	int userNumber;

	while(1)
	{
		hNamedPipe = CreateNamedPipe(LPipeName,
			PIPE_ACCESS_DUPLEX,
			PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
			PIPE_UNLIMITED_INSTANCES,
			SIZE_BUFFER,
			SIZE_BUFFER,
			INFINITE,
			NULL);
		Connected = ConnectNamedPipe(hNamedPipe, NULL);
		if (Connected)
		{
			SuccessRead = ReadFile(hNamedPipe, text, sizeBuffer, &readen, NULL);
			if (SuccessRead)
			{
				printf("\nClient: %s\n",text);
				if (isParsable(text))
				{
					userNumber = atof(text);
					userNumber = pow(userNumber,2);
					snprintf(message, sizeof message, "%d", userNumber);
				}
				else
				{
					printf("Enter message for client\n");
					gets(message);
				}
				text = &message;
				WriteFile(hNamedPipe, text, sizeBuffer, &readen, NULL);
			}
		}
		else
		{
			printf("Client disconnected");
		}
		CloseHandle(hNamedPipe);
	}
}
int isParsable(char* text)
{
	for (size_t i = 0; i < SIZE_BUFFER; i++)
	{
		if (text[i] >= '0' && text[i] <= '9')
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}