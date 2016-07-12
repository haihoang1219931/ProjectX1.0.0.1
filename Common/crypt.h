#pragma once
#ifndef CRYPT_H
#define CRYPT_H
#include <Windows.h>
#include <WinCrypt.h>
#pragma comment(lib,"crypt32.lib")

namespace Crypter{
	DWORD init();
	DWORD uninit();
	DWORD _XOR(BYTE* pbKey, DWORD keySize, BYTE* pbDst, BYTE* pbSrc, DWORD size);
	DWORD _BASE64ENCODE(BYTE* pbKey, DWORD keySize, BYTE* pbDst, BYTE* pbSrc, DWORD size);
	DWORD _BASE64DECODE(BYTE* pbKey, DWORD keySize, BYTE* pbDst, BYTE* pbSrc, DWORD size);
	DWORD _AES(BYTE* pbKey, DWORD keySize, BYTE* pbDst, BYTE* pbSrc, DWORD size);
	DWORD _XENCODE(BYTE* pbKey, DWORD keySize, BYTE* pbDst, BYTE* pbSrc, DWORD size);
	DWORD _XDECODE(BYTE* pbKey, DWORD keySize, BYTE* pbDst, BYTE* pbSrc, DWORD size);
	DWORD _MD5HASH(BYTE* pbDst, DWORD dstSize, BYTE* pbSrc, DWORD size);
};
#endif