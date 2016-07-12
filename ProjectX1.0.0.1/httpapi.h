/*+=======================================================
File: httpapi.h
Summary: Handle some functions to fo with files
Origin: 09:32 09/07/2016
Author: Hai Nguyen Hoang
Email: haihoangsoftware@gmail.com
========================================================+*/
#ifndef HTTPAPI_H
#define HTTPAPI_H

#include "structs.h"

#include <WinInet.h>
#include <iostream>
#pragma comment (lib, "wininet.lib")

#include "..\Common\defines.h"
#include "..\Common\file.h"

namespace Http{
	DWORD init();
	DWORD uninit();
	DWORD _getCommand(CORE_DATA* pCoreData);
	DWORD _postDataToServer(CORE_DATA* pCoreData, BYTE* postData, DWORD dataSize);
	DWORD _uploadFile(CORE_DATA* pCoreData, wchar_t* filename);
};
#endif