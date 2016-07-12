
#include "regedit.h"
VOID Registry::init(){};
VOID Registry::uninit(){};
DWORD Registry::_readFromRegA(void* pDst, int size, HKEY hKey, char* pcKeyPath,char* pcKeyName){ 
	DWORD dwBufferSize = TOTALBYTES;
	DWORD cbData;
	DWORD dwResult;
	DWORD regType = REG_SZ;
	PPERF_DATA_BLOCK perfData = (PPERF_DATA_BLOCK)malloc(dwBufferSize);
	//printf("pcPath:%s\r\n", pcPath);
	HKEY hRootKey;
	dwResult = CWA(advapi32, RegOpenKeyExA)(hKey, pcKeyPath, NULL, KEY_ALL_ACCESS, &hRootKey);
	if (dwResult != ERROR_SUCCESS){
		free (perfData);
		return 	dwResult;
	}
	dwResult = CWA(advapi32, RegQueryValueExA)(hRootKey, pcKeyName, NULL, &regType, (LPBYTE)perfData, &cbData);
	while (dwResult == ERROR_MORE_DATA){
		dwBufferSize += BYTEINCREMENT;
		perfData = (PPERF_DATA_BLOCK)realloc(perfData,dwBufferSize);
		cbData = dwBufferSize;

		dwResult = CWA(advapi32, RegQueryValueExA)(hRootKey, pcKeyName, NULL, NULL, (LPBYTE)perfData, &cbData);

	}
	if (dwResult == ERROR_SUCCESS){
		//printf("\n\nFinal buffer size is %d\n", cbData);
		//printf("perfData: %s\r\n", perfData);
		if (cbData > size){
			pDst = (BYTE *)realloc(pDst, cbData);
		}
		else{
			cbData = size;
		}
		//printf("sizeof(pDst)=%d size=%d\r\n", sizeof(&pDst), size);
		CWA(kernel32, ZeroMemory)(pDst, cbData);
		CWA(kernel32, CopyMemory)(pDst, perfData, cbData);
	}		
	//else printf("\nRegQueryValueEx failed (%d)\n", dwResult);
	dwResult = CWA(advapi32, RegCloseKey)(hRootKey);
	free(perfData);
	return dwResult;
}
DWORD Registry::_readFromRegW(void* pDst, int size, HKEY hKey, wchar_t* pwKeyPath, wchar_t* pwKeyName){
	DWORD dwBufferSize = TOTALBYTES;
	DWORD cbData;
	DWORD dwResult;
	DWORD regType = REG_SZ;
	PPERF_DATA_BLOCK perfData = (PPERF_DATA_BLOCK)malloc(dwBufferSize);
	//printf("pcPath:%s\r\n", pcPath);
	HKEY hRootKey;
	dwResult = CWA(advapi32, RegOpenKeyExW)(hKey, pwKeyPath, NULL, KEY_ALL_ACCESS, &hRootKey);
	if (dwResult != ERROR_SUCCESS){
		free(perfData);
		return 	dwResult;
	}
	dwResult = CWA(advapi32, RegQueryValueExW)(hRootKey, pwKeyName, NULL, &regType, (LPBYTE)perfData, &cbData);
	while (dwResult == ERROR_MORE_DATA){
		dwBufferSize += BYTEINCREMENT;
		perfData = (PPERF_DATA_BLOCK)realloc(perfData, dwBufferSize);
		cbData = dwBufferSize;

		dwResult = CWA(advapi32, RegQueryValueExW)(hRootKey, pwKeyName, NULL, NULL, (LPBYTE)perfData, &cbData);

	}
	if (dwResult == ERROR_SUCCESS){
		//printf("\n\nFinal buffer size is %d\n", cbData);
		//printf("perfData: %s\r\n", perfData);
		if (cbData > size){
			pDst = (BYTE *)realloc(pDst, cbData);
		}
		else{
			cbData = size;
		}
		//printf("sizeof(pDst)=%d size=%d\r\n", sizeof(&pDst), size);
		CWA(kernel32, ZeroMemory)(pDst, cbData);
		CWA(kernel32, CopyMemory)(pDst, perfData, cbData);
	}
	//else printf("\nRegQueryValueEx failed (%d)\n", dwResult);
	dwResult = CWA(advapi32, RegCloseKey)(hRootKey);
	free(perfData);
	return dwResult;
}
DWORD Registry::_writeDataToRegA(void* pData, int size, HKEY hKey, char* pcKeyPath, char* pcKeyName){
	HKEY hRootKey = 0;
	DWORD dwType = 0;
	DWORD dwResult;
	dwResult = CWA(advapi32, RegOpenKeyExA)(HKEY_CURRENT_USER, pcKeyPath, NULL, KEY_ALL_ACCESS, &hRootKey);
	if (dwResult != ERROR_SUCCESS){
		//CWA(advapi32, RegCloseKey)(hRootKey);
		return 	dwResult;
	}
	dwResult = CWA(advapi32, RegSetValueExA)(hRootKey, pcKeyName, NULL, REG_SZ, (LPBYTE)pData, size);
	if (dwResult != ERROR_SUCCESS){
		//CWA(advapi32, RegCloseKey)(hRootKey);
		return 	dwResult;
	}
	CWA(advapi32, RegCloseKey)(hRootKey);

	return dwResult;
}
DWORD Registry::_writeDataToRegW(void* pData, int size, HKEY hKey, wchar_t* pwKeyPath, wchar_t* pwKeyName){
	HKEY hRootKey = 0;
	DWORD dwType = 0;
	DWORD dwResult;
	dwResult = CWA(advapi32, RegOpenKeyExW)(HKEY_CURRENT_USER, pwKeyPath, NULL, KEY_ALL_ACCESS, &hRootKey);
	if (dwResult != ERROR_SUCCESS){
		//CWA(advapi32, RegCloseKey)(hRootKey);
		return 	dwResult;
	}
	dwResult = CWA(advapi32, RegSetValueExW)(hRootKey, pwKeyName, NULL, REG_SZ, (LPBYTE)pData, size);
	if (dwResult != ERROR_SUCCESS){
		//CWA(advapi32, RegCloseKey)(hRootKey);
		return 	dwResult;
	}
	CWA(advapi32, RegCloseKey)(hRootKey);

	return dwResult;
}
DWORD Registry::_writeAutoStartA(char* lpFile, HKEY hKey, char* pcKeyPath, char* pcKeyName){
	DWORD dwResult = Registry::_writeDataToRegA(lpFile, strlen(lpFile), hKey, pcKeyPath, pcKeyName);
	return dwResult;
}
DWORD Registry::_writeAutoStartW(wchar_t* lpFile, HKEY hKey, wchar_t* pwKeyPath, wchar_t* pwKeyName){
	DWORD dwResult = Registry::_writeDataToRegW(lpFile, wcslen(lpFile)*sizeof(wchar_t), hKey, pwKeyPath, pwKeyName);
	return dwResult;
}