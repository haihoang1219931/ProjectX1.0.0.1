#pragma once

#ifndef STRING_H
#define STRING_H

#include <Windows.h>
#include <stdio.h>

namespace StringConverter{
	wchar_t* chartowchar_t(char*data);
	char* wchar_ttochar(wchar_t* data);
};
#endif