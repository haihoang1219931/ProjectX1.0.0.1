/*+=======================================================
File: time.h
Summary: Handle some functions to fo with files
Origin: 09:32 09/07/2016
Author: Hai Nguyen Hoang
Email: haihoangsoftware@gmail.com
========================================================+*/
#pragma once

#ifndef TIME_H
#define TIME_H

#include <Windows.h>
#include <stdio.h>
#include "defines.h"

namespace Time
{
	/*
	�������������.
	*/
	void init(void);

	/*
	���������������.
	*/
	void uninit(void);

	/*
	��������� �������� �������.

	Return - ������� �����.
	*/
	void getTime(char *time);

	/*
	��������� �������� ������� GMT.

	Return - ������� �����.
	*/
	char * getTime();

	/*
	��������� �������� GMT.

	Return - ������� GMT � ��������.
	*/
	int _getLocalGmt(void);
};
#endif
