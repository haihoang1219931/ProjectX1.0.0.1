
#include "file.h"
void File::init(){}
void File::unit(){}
BOOL File::_fileExist(LPWSTR lpFileName){
	WIN32_FIND_DATA wfData;
	HANDLE hFile = FindFirstFile(lpFileName, &wfData); // find file
	if (hFile != INVALID_HANDLE_VALUE){
		FindClose(hFile);
		return TRUE;
	}
	return FALSE;
}

BOOL File::_removeFile(LPWSTR lpFileName){
	return DeleteFile(lpFileName) ? TRUE : FALSE;
}

BOOL File::_saveToFile(LPWSTR lpFileName, void *data, DWORD dwDataSize){
	BOOL bResult = TRUE;
	HANDLE hFile = CreateFile(lpFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL); // Create file  
	DWORD dwNumberOfByteWritten;
	if (hFile != INVALID_HANDLE_VALUE){
		if (data == NULL || dwDataSize == 0 || WriteFile(hFile, data, dwDataSize, &dwNumberOfByteWritten, NULL) != FALSE) bResult = TRUE;
		CloseHandle(hFile); // if write file success, close file handle
		if (bResult == FALSE){ File::_removeFile(lpFileName); } // if write file failed, remote file created
	}
	return bResult;
}

BOOL File::_appendToFile(LPWSTR lpFileName, void *data, DWORD dwDataSize){
	BOOL bResult = TRUE;
	HANDLE hFile = CreateFileW(lpFileName, FILE_APPEND_DATA, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		DWORD dwPtr = SetFilePointer(hFile, 0, NULL, FILE_END);
		if (dwPtr == INVALID_SET_FILE_POINTER){
			//printf("GetLastError(): %d\r\n",GetLastError());
			bResult = FALSE;
		}
		//printf("dwPtr=%d\r\n",dwPtr);
		DWORD size;
		if (data == NULL || dwDataSize == 0 || WriteFile(hFile, data, dwDataSize, &size, NULL) != FALSE)bResult = TRUE;
		CloseHandle(hFile);
		if (bResult != TRUE) File::_removeFile(lpFileName);
	}
	return bResult;
}

DWORD File::_readFileToBuffer(LPWSTR lpFileName, void *buffer, DWORD dwBufferSize){
	DWORD retVal = (DWORD)-1;
	HANDLE hFile = CWA(kernel32,CreateFile)(lpFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE){
		if (CWA(kernel32, ReadFile)(hFile, buffer, dwBufferSize, &dwBufferSize, NULL) != FALSE)retVal = dwBufferSize;
		CWA(kernel32, CloseHandle)(hFile);
	}
	return retVal;
}
BOOL File::_readLineFromFile(LPWSTR lpFileName, DWORD lineIndex, void *buffer, DWORD *dwBufferSize){ return TRUE; }
BOOL File::_readFirstLine(LPWSTR lpFileName, void *buffer, DWORD *dwBufferSize){ return TRUE; }
BOOL File::_readLastLine(LPWSTR lpFileName, void *buffer, DWORD *dwBufferSize){ return TRUE; }
BOOL File::_getFileTime(BOOL bIsDir, LPWSTR lpFileName, FILETIME *creationTime, FILETIME *lastAccessTime, FILETIME *lastWriteTime){ return TRUE; }
BOOL File::_copyFileTime(BOOL bSourceIsDir, LPWSTR lpSourceFile, BOOL bDestIsDir, LPWSTR lpDestFile){ return TRUE; }
BOOL File::_setFileTime(BOOL bIsDir, LPWSTR lpFileName, FILETIME *creationTime, FILETIME *lastAccessTime, FILETIME *lastWriteTime){ return TRUE; }
BOOL File::_setRandomFileTime(DWORD dwStartTime, DWORD dwReservedSeconds, LPWSTR lpFileName, DWORD dwUpLevel);