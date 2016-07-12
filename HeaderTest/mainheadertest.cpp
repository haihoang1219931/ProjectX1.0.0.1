#include "..\Common\os.h"
#include "..\Common\user.h"
#include <stdio.h>
#include <memory.h>
#include <iostream>

using namespace std;
int main(){
	printf("Hello World\r\n");
	
	char os[MAX_OS_NAME];
	char username[MAX_USER_NAME];
	OS::_getOS(os);
	User::_getUserName(username);
	/**/
	char cpostData[1024];
	//CWA(kernel32, ZeroMemory)(cpostData, sizeof(cpostData));
	sprintf_s(cpostData, sizeof(cpostData), "os=%s&username=%s&id=%s", os, username, "12345677889");
	printf("cpostData: %s\r\n", cpostData);
	BYTE cpostDataEncrypted[1024];
	//CWA(kernel32, ZeroMemory)(cpostDataEncrypted, sizeof(cpostDataEncrypted));
	
	return 0;
}