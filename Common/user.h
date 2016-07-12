/*+=======================================================
File: user.h
Summary: Handle some functions to fo with files
Origin: 09:32 09/07/2016
Author: Hai Nguyen Hoang
Email: haihoangsoftware@gmail.com
========================================================+*/
#pragma once

#ifndef USER_H
#define USER_H

#include <Windows.h>
#include "defines.h"

namespace User{
	DWORD init();
	DWORD uninit();
	void _getUserName(char *username);
	char * _getUserName();
};
#endif