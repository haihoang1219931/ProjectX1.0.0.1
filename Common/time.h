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
	Инициализация.
	*/
	void init(void);

	/*
	Деинициализация.
	*/
	void uninit(void);

	/*
	Получение текущего времени.

	Return - текущее время.
	*/
	void getTime(char *time);

	/*
	Получение текущего времени GMT.

	Return - текущее время.
	*/
	char * getTime();

	/*
	Получение текущего GMT.

	Return - текущее GMT в секундах.
	*/
	int _getLocalGmt(void);
};
#endif
