#ifndef _CkUnixCompress_W_H
#define _CkUnixCompress_W_H
#include "Chilkat_C.h"

HCkUnixCompressW CkUnixCompressW_Create(void);
void CkUnixCompressW_Dispose(HCkUnixCompressW handle);
void CkUnixCompressW_getDebugLogFilePath(HCkUnixCompressW cHandle, HCkStringW retval);
void CkUnixCompressW_putDebugLogFilePath(HCkUnixCompressW cHandle, const wchar_t *newVal);
void CkUnixCompressW_getLastErrorHtml(HCkUnixCompressW cHandle, HCkStringW retval);
void CkUnixCompressW_getLastErrorText(HCkUnixCompressW cHandle, HCkStringW retval);
void CkUnixCompressW_getLastErrorXml(HCkUnixCompressW cHandle, HCkStringW retval);
BOOL CkUnixCompressW_getVerboseLogging(HCkUnixCompressW cHandle);
void CkUnixCompressW_putVerboseLogging(HCkUnixCompressW cHandle, BOOL newVal);
BOOL CkUnixCompressW_CompressFile(HCkUnixCompressW cHandle, const wchar_t *inFilename, const wchar_t *outFilename);
BOOL CkUnixCompressW_CompressFileToMem(HCkUnixCompressW cHandle, const wchar_t *inFilename, HCkByteDataW outData);
BOOL CkUnixCompressW_CompressMemToFile(HCkUnixCompressW cHandle, HCkByteDataW db, const wchar_t *outFilename);
BOOL CkUnixCompressW_CompressMemory(HCkUnixCompressW cHandle, HCkByteDataW dbIn, HCkByteDataW outData);
BOOL CkUnixCompressW_CompressString(HCkUnixCompressW cHandle, const wchar_t *inStr, const wchar_t *outCharset, HCkByteDataW outBytes);
BOOL CkUnixCompressW_CompressStringToFile(HCkUnixCompressW cHandle, const wchar_t *inStr, const wchar_t *outCharset, const wchar_t *outFilename);
BOOL CkUnixCompressW_IsUnlocked(HCkUnixCompressW cHandle);
BOOL CkUnixCompressW_SaveLastError(HCkUnixCompressW cHandle, const wchar_t *filename);
BOOL CkUnixCompressW_UnTarZ(HCkUnixCompressW cHandle, const wchar_t *zFilename, const wchar_t *destDir, BOOL bNoAbsolute);
BOOL CkUnixCompressW_UncompressFile(HCkUnixCompressW cHandle, const wchar_t *inFilename, const wchar_t *outFilename);
BOOL CkUnixCompressW_UncompressFileToMem(HCkUnixCompressW cHandle, const wchar_t *inFilename, HCkByteDataW outData);
BOOL CkUnixCompressW_UncompressFileToString(HCkUnixCompressW cHandle, const wchar_t *inFilename, const wchar_t *inCharset, HCkStringW outStr);
BOOL CkUnixCompressW_UncompressMemToFile(HCkUnixCompressW cHandle, HCkByteDataW db, const wchar_t *outFilename);
BOOL CkUnixCompressW_UncompressMemory(HCkUnixCompressW cHandle, HCkByteDataW dbIn, HCkByteDataW outData);
BOOL CkUnixCompressW_UncompressString(HCkUnixCompressW cHandle, HCkByteDataW inData, const wchar_t *inCharset, HCkStringW outStr);
BOOL CkUnixCompressW_UnlockComponent(HCkUnixCompressW cHandle, const wchar_t *unlockCode);
const wchar_t *CkUnixCompressW__debugLogFilePath(HCkUnixCompressW cHandle);
const wchar_t *CkUnixCompressW__lastErrorHtml(HCkUnixCompressW cHandle);
const wchar_t *CkUnixCompressW__lastErrorText(HCkUnixCompressW cHandle);
const wchar_t *CkUnixCompressW__lastErrorXml(HCkUnixCompressW cHandle);
const wchar_t *CkUnixCompressW__uncompressFileToString(HCkUnixCompressW cHandle, const wchar_t *inFilename, const wchar_t *inCharset);
const wchar_t *CkUnixCompressW__uncompressString(HCkUnixCompressW cHandle, HCkByteDataW inData, const wchar_t *inCharset);
#endif
