
#include "os.h"

#pragma warning(disable: 4996)
DWORD OS::init(){ return 0; }
DWORD OS::uninit(){ return 0; }
void OS::_getOS(char *os){
	OSVERSIONINFO osvi;
	CWA(kernel32,ZeroMemory)(&osvi, sizeof(OSVERSIONINFO));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	BOOL result = CWA(kernel32,GetVersionEx)(&osvi);
	if (!result){
		return;
	}
	sprintf_s(os, MAX_OS_NAME, "Windows %d.%d build %d %d", osvi.dwMajorVersion, osvi.dwMinorVersion, osvi.dwBuildNumber, osvi.dwPlatformId);
	return;
}

char * OS::_getOS(){
	char *os = (char *)malloc(MAX_OS_NAME);
	OSVERSIONINFO osvi;
	CWA(kernel32,ZeroMemory)(&osvi, sizeof(OSVERSIONINFO));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	BOOL result = CWA(kernel32,GetVersionEx)(&osvi);
	if (!result){
		return "";
	}
	sprintf_s(os, MAX_OS_NAME, "Windows %d.%d build %d %d", osvi.dwMajorVersion, osvi.dwMinorVersion, osvi.dwBuildNumber, osvi.dwPlatformId);
	return os;
}
bool OS::_isWindowsXPAndBellow(){
	OSVERSIONINFO osvi;
	CWA(kernel32, ZeroMemory)(&osvi, sizeof(OSVERSIONINFO));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	bool bResult = true;
	BOOL result = GetVersionEx(&osvi);
	
	if (osvi.dwMajorVersion >5){
		bResult = false;
	}
	return bResult;
}