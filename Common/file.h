/*+=======================================================
File: file.h
Summary: Handle some functions to fo with files
Origin: 09:32 09/07/2016
Author: Hai Nguyen Hoang
Email: haihoangsoftware@gmail.com
========================================================+*/
#pragma once
#ifndef FILE_H
#define FILE_H

#include <Windows.h>
#include <iostream>
#include "defines.h"
#include "time.h"

namespace File{
	/*
	Initialization
	*/
	void init();

	/*
	Uninstall
	*/
	void unit();

	/*
	Check file's existance

	IN lpFileName - name of file need to check;

	Return - TRUE: if file is exist
	FALSE: if file is not exist
	*/
	BOOL _fileExist(LPWSTR lpFileName);

	/*
	Delete file

	IN lpFileName: name of file need to delete

	Return - TRUE: if delete success
	FALSE: if delete failed
	*/
	BOOL _removeFile(LPWSTR lpFileName);

	/*
	Save data to file

	IN lpFileName: name of file need to save
	IN data: pointer to data will be saved to file
	IN dwDataSize: size of data

	Return - TRUE: if save success
	FALSE: if save failed
	*/
	BOOL _saveToFile(LPWSTR lpFileName, void *data, DWORD dwDataSize);

	/*
	Append data to file

	IN lpFileName: name of file need to append
	IN data: pointer to data will be appended to file
	IN dwDataSize: size of data

	Return - TRUE: if append success
	FALSE: if append failed
	*/
	BOOL _appendToFile(LPWSTR fileName, void *data, DWORD dwDataSize);

	/*
	Read data in file to buffer and return bufferSize

	IN lpFileName: name of file for reading
	OUT buffer: pointer to save data to
	OUT lpBufferSize: pointer to save size of data read

	Return - TRUE: if read success
	FALSE: if read failed
	*/
	DWORD _readFileToBuffer(LPWSTR lpFileName, void *buffer, DWORD lpBufferSize);

	/*
	Read line with index given from file

	IN lpFileName: name of file for reading
	IN dwLineIndex: index of line
	OUT buffer: pointer to save data to
	OUT lpBufferSize: pointer to save size of data read

	Return - TRUE: if read success
	FALSE: if read failed
	*/
	BOOL _readLineFromFile(LPWSTR lpFileName, DWORD dwLineIndex, void *buffer, LPDWORD lpBufferSize);

	/*
	Read first line with index given from file

	IN lpFileName: name of file for reading
	OUT buffer: pointer to save data to
	OUT lpBufferSize: pointer to save size of data read

	Return - TRUE: if read success
	FALSE: if read failed
	*/
	BOOL _readFirstLine(LPWSTR lpFileName, void *buffer, LPDWORD lpBufferSize);

	/*
	Read last line with index given from file

	IN lpFileName: name of file for reading
	OUT buffer: pointer to save data to
	OUT lpBufferSize: pointer to save size of data read

	Return - TRUE: if read success
	FALSE: if read failed
	*/
	BOOL _readLastLine(LPWSTR lpFileName, void *buffer, LPDWORD lpBufferSize);

	/*
	Get three times: creation, last access and last modified

	IN bIsDir: check if file is a directory or not
	IN lpFileName: name of file
	OUT creationTime: pointer to save file's creation time
	OUT lastAccessTime: pointer to save file's last access time
	OUT lastWriteTime: pointer to save file's last modified time

	Return - TRUE: if get succeess
	FALSE: if get failed
	*/
	BOOL _getFileTime(BOOL bIsDir, LPWSTR lpFileName, FILETIME *creationTime, FILETIME *lastAccessTime, FILETIME *lastWriteTime);

	/*
	Copy file's three times to another file

	IN bSourceIsDir: check if source file is a directory or not
	IN lpSourceFile: name of source file
	OUT bDestIsDir: check if destination file is a directory or not
	OUT lpDestFile: name of destination file

	Return - TRUE: if copy success
	FALSE: if copy failed
	*/
	BOOL _copyFileTime(BOOL bSourceIsDir, LPWSTR lpSourceFile, BOOL bDestIsDir, LPWSTR lpDestFile);

	/*
	Set file's three time

	IN bIsDir: check if file is a directory or not
	IN lpFileName: name of file
	IN creationTime: pointer to save file's creation time
	IN lastAccessTime: pointer to save file's last access time
	IN lastWriteTime: pointer to save file's last modified time

	Return - TRUE: if set succeess
	FALSE: if set failed
	*/
	BOOL _setFileTime(BOOL bIsDir, LPWSTR lpFileName, FILETIME *creationTime, FILETIME *lastAccessTime, FILETIME *lastWriteTime);

	/*
	Set file's three time to random

	IN dwStartTime
	IN dwReservedSeconds
	IN lpFileName
	IN dwUpLevel

	Return - TRUE: if set success
	FALSE: if set failed
	*/
	BOOL _setRandomFileTime(DWORD dwStartTime, DWORD dwReservedSeconds, LPWSTR lpFileName, DWORD dwUpLevel);
	
	/*
	
	*/

};
#endif