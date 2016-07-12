#include "user.h"
DWORD init(){ return 0; }
DWORD uninit(){ return 0; }
char * User::_getUserName(){
	char *username = (char*)malloc(MAX_USER_NAME);
	DWORD username_len = MAX_USER_NAME;
	CWA(kernel32,GetUserNameA)(username, &username_len);
	return username;
}
void User::_getUserName(char *username){
	DWORD username_len = MAX_USER_NAME;
	CWA(kernel32,GetUserNameA)(username, &username_len);
	return;
}