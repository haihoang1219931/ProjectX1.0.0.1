#include "string.h"

wchar_t* StringConverter::chartowchar_t(char*data){
	size_t size = strlen(data) + 1;
	wchar_t* data_wchar_t = new wchar_t[size];
	size_t outSize;
	mbstowcs_s(&outSize, data_wchar_t, size, data, size - 1);
	return data_wchar_t;
}
char* StringConverter::wchar_ttochar(wchar_t* data){
	size_t size = wcslen(data) + 1;
	char* data_char = new char[size];
	size_t outSize;
	wcstombs_s(&outSize, data_char, size, data, size - 1);
	return data_char;
}