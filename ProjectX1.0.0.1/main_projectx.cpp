#include <Windows.h>
#include "core.h"

BOOL APIENTRY DllMain(HANDLE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved)
{
	// Perform actions based on the reason for calling.
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		// Initialize once for each new process.
		// Return FALSE to fail DLL load.            
		break;

	case DLL_THREAD_ATTACH:
		// Do thread-specific initialization.
		break;

	case DLL_THREAD_DETACH:
		// Do thread-specific cleanup.            
		break;

	case DLL_PROCESS_DETACH:
		// Perform any necessary cleanup.
		break;
	}
	return TRUE;
}
extern "C" void __declspec(dllexport) mainFunc(){
	//CWA(user32,MessageBox)(NULL, L"HELLO MAIN WORLD", NULL, NULL);
	//printf("HelloWorld\r\n");
	Core::_action();
}
