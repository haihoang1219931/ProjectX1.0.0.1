/*+=======================================================
File: os.h
Summary: Handle some functions to fo with files
Origin: 09:32 09/07/2016
Author: Hai Nguyen Hoang
Email: haihoangsoftware@gmail.com
========================================================+*/
#pragma once
#ifndef OS_H
#define OS_H

#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include "defines.h"

using namespace std;

namespace OS{
	DWORD init();
	DWORD uninit();
	/*
	Get operating system information and convert to string 
		- MajorVersion 
		- MinorVersion 
		- BuildNumber 
		- PlatformId
	OUT os: where to save data

	RETURN

	*/
	void _getOS(char * os);
	
	/*
	Get operating system information and convert to string
	- MajorVersion
	- MinorVersion
	- BuildNumber
	- PlatformId
	
	RETURN	string contain operating system information

	*/
	char * _getOS();

	bool _isWindowsXPAndBellow();
};
#endif