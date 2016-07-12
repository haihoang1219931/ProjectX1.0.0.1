#include "crypt.h"

DWORD Crypter::init(){ return 0; }
DWORD Crypter::uninit(){ return 0; }
DWORD Crypter::_XOR(BYTE* pbKey, DWORD keySize, BYTE* pbDst, BYTE* pbSrc, DWORD srcSize){
	DWORD i = 0;
	while (i < srcSize){
		for (DWORD j = 0; j < keySize; j++){
			pbDst[i] = pbSrc[i] ^ pbKey[j];
			i++;
			if (i >= srcSize) break;
		}
	}
	return GetLastError();
}
DWORD Crypter::_BASE64ENCODE(BYTE* pbKey, DWORD keySize, BYTE* pbDst, BYTE* pbSrc, DWORD srcSize);
DWORD Crypter::_BASE64DECODE(BYTE* pbKey, DWORD keySize, BYTE* pbDst, BYTE* pbSrc, DWORD srcSize);
DWORD Crypter::_AES(BYTE* pbKey, DWORD keySize, BYTE* pbDst, BYTE* pbSrc, DWORD srcSize);
DWORD Crypter::_XENCODE(BYTE* pbKey, DWORD keySize, BYTE* pbDst, BYTE* pbSrc, DWORD srcSize);
DWORD Crypter::_XDECODE(BYTE* pbKey, DWORD keySize, BYTE* pbDst, BYTE* pbSrc, DWORD srcSize);
DWORD Crypter::_MD5HASH(BYTE* pbDst, DWORD dstSize, BYTE* pbSrc, DWORD srcSize){
	DWORD dwStatus = 0;
	BOOL bResult = FALSE;
	HCRYPTPROV hProv = 0;
	HCRYPTHASH hHash = 0;
	BYTE *rgbHash = new BYTE[dstSize+1];
	DWORD cbHash = 0;
	CHAR rgbDigits[] = "0123456789abcdef";
	if (!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
	{
		dwStatus = GetLastError();
		return dwStatus;
	}
	if (!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash))
	{
		dwStatus = GetLastError();
		CryptReleaseContext(hProv, 0);
		return dwStatus;
	}
	if (!CryptHashData(hHash, pbSrc, srcSize, 0))
	{

		dwStatus = GetLastError();
		CryptReleaseContext(hProv, 0);
		CryptDestroyHash(hHash);
		return dwStatus;
	}
	cbHash = dstSize;
	if (CryptGetHashParam(hHash, HP_HASHVAL, rgbHash, &cbHash, 0))
	{
		for (DWORD i = 0; i < cbHash; i++)
		{
			pbDst[i * 2] = rgbDigits[rgbHash[i] >> 4];
			pbDst[i * 2 + 1] = rgbDigits[rgbHash[i] & 0xf];
		}
		if (strlen((char*)pbDst)>dstSize) pbDst[dstSize] = 0;
	}
	else{
		dwStatus = GetLastError();
	}
	CryptDestroyHash(hHash);
	CryptReleaseContext(hProv, 0);
	return dwStatus;
}