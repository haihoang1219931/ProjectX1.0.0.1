#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include <Windows.h>
#include <GdiPlus.h>
#include <stdio.h>
#pragma comment( lib,"gdiplus")

#include "structs.h"

namespace CaptureScreen{
	void gdiscreen(const char *fileName);
	int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
};
#endif