#include <windows.h>
#include <stdio.h>
//we need a function pointer,that has the same signature as the dll function(mandatory)
typedef int(*function)();

void main(){
	HMODULE lib = LoadLibraryA("ProjectX1.0.0.1.dll");
	if (lib){
		//lets find the function myFunction in our dll
		function myFunction = (function)GetProcAddress(lib, "mainFunc");
		if (myFunction){
			printf("Function found!Lets call it!\n");
			myFunction();
		}
		else
			printf("Function is not present in the loaded dll!\n");
	}
	else
		printf("Dll file not found!\n");
	//unload the dll
	FreeLibrary(lib);
	//Sleep(5000);
}