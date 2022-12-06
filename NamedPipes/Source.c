#include "..\NamedPipesServer\HeaderServer.h"
int main()
{
	system("chcp 1251>nul");
	LPSTR lPipeName = L"\\\\.\\pipe\\MyPipe";
	BOOL answerFlag = TRUE;
	char message[SIZE_BUFFER];
	DWORD sizeBuffer = SIZE_BUFFER;
	DWORD written;
	LPWSTR text = (char*)calloc(sizeBuffer, sizeof(char));
	DWORD readen;
	BOOL SuccessRead;
	HANDLE hNamedPipe;
	while (1)
	{
		hNamedPipe = CreateFile(lPipeName,
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			OPEN_EXISTING,
			0,
			NULL);
		DWORD dwMode = PIPE_READMODE_MESSAGE;
		BOOL isSuccess = SetNamedPipeHandleState(hNamedPipe, &dwMode, NULL, NULL);
		if (isSuccess)
		{
			if (answerFlag)
			{
				printf("Enter message to the server: \n");
				gets(message);
				text = &message;
				WriteFile(hNamedPipe, text, sizeBuffer, &written, NULL);
				answerFlag = FALSE;
			}
			SuccessRead = ReadFile(hNamedPipe, text, SIZE_BUFFER, &readen, NULL);
			if (SuccessRead)
			{
				printf("Server: %s\n", text);
				answerFlag = TRUE;
				if (text == NULL)
				{
					printf("Ответа нет :(\n");
				}
			}
		}
		else
		{
			printf("Server is not responding...\n");
			answerFlag = TRUE;
		}
		Sleep(250);
		CloseHandle(hNamedPipe);
	}
}