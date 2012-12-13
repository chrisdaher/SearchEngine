#ifndef _CkZipEntry_W_H
#define _CkZipEntry_W_H
#include "Chilkat_C.h"

HCkZipEntryW CkZipEntryW_Create(void);
void CkZipEntryW_Dispose(HCkZipEntryW handle);
void CkZipEntryW_getComment(HCkZipEntryW cHandle, HCkStringW retval);
void CkZipEntryW_putComment(HCkZipEntryW cHandle, const wchar_t *newVal);
unsigned long CkZipEntryW_getCompressedLength(HCkZipEntryW cHandle);
long CkZipEntryW_getCompressionLevel(HCkZipEntryW cHandle);
void CkZipEntryW_putCompressionLevel(HCkZipEntryW cHandle, long newVal);
long CkZipEntryW_getCompressionMethod(HCkZipEntryW cHandle);
void CkZipEntryW_putCompressionMethod(HCkZipEntryW cHandle, long newVal);
int CkZipEntryW_getCrc(HCkZipEntryW cHandle);
long CkZipEntryW_getEntryID(HCkZipEntryW cHandle);
long CkZipEntryW_getEntryType(HCkZipEntryW cHandle);
void CkZipEntryW_getFileDateTime(HCkZipEntryW cHandle, SYSTEMTIME *retval);
void CkZipEntryW_putFileDateTime(HCkZipEntryW cHandle, SYSTEMTIME *newVal);
void CkZipEntryW_getFileName(HCkZipEntryW cHandle, HCkStringW retval);
void CkZipEntryW_putFileName(HCkZipEntryW cHandle, const wchar_t *newVal);
BOOL CkZipEntryW_getIsDirectory(HCkZipEntryW cHandle);
void CkZipEntryW_getLastErrorHtml(HCkZipEntryW cHandle, HCkStringW retval);
void CkZipEntryW_getLastErrorText(HCkZipEntryW cHandle, HCkStringW retval);
void CkZipEntryW_getLastErrorXml(HCkZipEntryW cHandle, HCkStringW retval);
unsigned long CkZipEntryW_getUncompressedLength(HCkZipEntryW cHandle);
BOOL CkZipEntryW_AppendData(HCkZipEntryW cHandle, HCkByteDataW bdata);
BOOL CkZipEntryW_AppendStringAnsi(HCkZipEntryW cHandle, HCkStringW sdata);
BOOL CkZipEntryW_Copy(HCkZipEntryW cHandle, HCkByteDataW outData);
BOOL CkZipEntryW_CopyToBase64(HCkZipEntryW cHandle, HCkStringW outStr);
BOOL CkZipEntryW_CopyToHex(HCkZipEntryW cHandle, HCkStringW outStr);
BOOL CkZipEntryW_Extract(HCkZipEntryW cHandle, const wchar_t *dirPath);
BOOL CkZipEntryW_ExtractInto(HCkZipEntryW cHandle, const wchar_t *dirPath);
HCkDateTimeW CkZipEntryW_GetDt(HCkZipEntryW cHandle);
BOOL CkZipEntryW_Inflate(HCkZipEntryW cHandle, HCkByteDataW outData);
BOOL CkZipEntryW_InflateToString(HCkZipEntryW cHandle, BOOL addCR, HCkStringW outStr);
BOOL CkZipEntryW_InflateToString2(HCkZipEntryW cHandle, HCkStringW outStr);
HCkZipEntryW CkZipEntryW_NextEntry(HCkZipEntryW cHandle);
BOOL CkZipEntryW_ReplaceData(HCkZipEntryW cHandle, HCkByteDataW bdata);
BOOL CkZipEntryW_ReplaceStringAnsi(HCkZipEntryW cHandle, HCkStringW sdata);
BOOL CkZipEntryW_SaveLastError(HCkZipEntryW cHandle, const wchar_t *filename);
void CkZipEntryW_SetDt(HCkZipEntryW cHandle, HCkDateTimeW dt);
const wchar_t *CkZipEntryW__comment(HCkZipEntryW cHandle);
const wchar_t *CkZipEntryW__copyToBase64(HCkZipEntryW cHandle);
const wchar_t *CkZipEntryW__copyToHex(HCkZipEntryW cHandle);
const wchar_t *CkZipEntryW__fileName(HCkZipEntryW cHandle);
const wchar_t *CkZipEntryW__inflateToString(HCkZipEntryW cHandle, BOOL addCR);
const wchar_t *CkZipEntryW__inflateToString2(HCkZipEntryW cHandle);
const wchar_t *CkZipEntryW__lastErrorHtml(HCkZipEntryW cHandle);
const wchar_t *CkZipEntryW__lastErrorText(HCkZipEntryW cHandle);
const wchar_t *CkZipEntryW__lastErrorXml(HCkZipEntryW cHandle);
#endif
