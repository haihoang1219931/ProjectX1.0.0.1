/*+=======================================================
File	: regedit.h
Summary	: Handle some functions invole with regedit
Origin	: 11:14 09/07/2016
Author	: Hai Nguyen Hoang
Email	: haihoangsoftware@gmail.com
========================================================+*/
#pragma once

#ifndef REGEDIT_H
#define REGEDIT_H

#include <Windows.h>
#include <stdio.h>
#include <malloc.h>
#include "defines.h"
namespace Registry{
	/*
		Initialization
	*/
	VOID init();
	
	/* 
		Unintialization
	*/
	VOID uninit();
	
	/*
		Read data from Registry to variable
		OUT pDst: where contain data read
		IN maxSize: max length of data
		IN hKey: key type
		IN wpPath: path to key 

		Return - Error when read file
	*/
	DWORD _readFromRegA(void* pDst, int maxSize, HKEY hKey, char* pcKeyPath, char* pcKeyName);
	DWORD _readFromRegW(void* pDst, int maxSize, HKEY hKey, wchar_t* pcKeyPath, wchar_t* pwKeyName);

	/*
		Write data into Registry
		IN pData: data need to write
		IN size: size of data
		IN hKey: key type
		IN wpPath: path to write

		Return - Error when write to Registry
	*/
	DWORD _writeDataToRegA(void* pData, int size, HKEY hKey, char* pcKeyPath, char* pcKeyName);
	DWORD _writeDataToRegW(void* pData, int size, HKEY hKey, wchar_t* pwKeyPath, wchar_t* pwKeyName);

	/*
		Create key in registry that make program start
		IN lpFile: where is file's location
		IN hKey: key type
		IN wpPath: path to write

		Return - Error when write to Registry
	*/
	DWORD _writeAutoStartA(char* lpFile, HKEY hKey, char* pcKeyPath, char* pcKeyName);
	DWORD _writeAutoStartW(wchar_t* lpFile, HKEY hKey, wchar_t* pwKeyPath, wchar_t* pcKeyName);
};
#endif