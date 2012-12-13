#ifndef _CkCache_W_H
#define _CkCache_W_H
#include "Chilkat_C.h"

HCkCacheW CkCacheW_Create(void);
void CkCacheW_Dispose(HCkCacheW handle);
void CkCacheW_getDebugLogFilePath(HCkCacheW cHandle, HCkStringW retval);
void CkCacheW_putDebugLogFilePath(HCkCacheW cHandle, const wchar_t *newVal);
void CkCacheW_getLastErrorHtml(HCkCacheW cHandle, HCkStringW retval);
void CkCacheW_getLastErrorText(HCkCacheW cHandle, HCkStringW retval);
void CkCacheW_getLastErrorXml(HCkCacheW cHandle, HCkStringW retval);
void CkCacheW_getLastEtagFetched(HCkCacheW cHandle, HCkStringW retval);
void CkCacheW_getLastExpirationFetched(HCkCacheW cHandle, SYSTEMTIME *retval);
BOOL CkCacheW_getLastHitExpired(HCkCacheW cHandle);
void CkCacheW_getLastKeyFetched(HCkCacheW cHandle, HCkStringW retval);
int CkCacheW_getLevel(HCkCacheW cHandle);
void CkCacheW_putLevel(HCkCacheW cHandle, int newVal);
int CkCacheW_getNumRoots(HCkCacheW cHandle);
BOOL CkCacheW_getVerboseLogging(HCkCacheW cHandle);
void CkCacheW_putVerboseLogging(HCkCacheW cHandle, BOOL newVal);
void CkCacheW_AddRoot(HCkCacheW cHandle, const wchar_t *path);
int CkCacheW_DeleteAll(HCkCacheW cHandle);
int CkCacheW_DeleteAllExpired(HCkCacheW cHandle);
BOOL CkCacheW_DeleteFromCache(HCkCacheW cHandle, const wchar_t *key);
int CkCacheW_DeleteOlder(HCkCacheW cHandle, SYSTEMTIME *dt);
int CkCacheW_DeleteOlderDt(HCkCacheW cHandle, HCkDateTimeW dt);
BOOL CkCacheW_FetchFromCache(HCkCacheW cHandle, const wchar_t *key, HCkByteDataW outBytes);
BOOL CkCacheW_FetchText(HCkCacheW cHandle, const wchar_t *key, HCkStringW outStr);
BOOL CkCacheW_GetEtag(HCkCacheW cHandle, const wchar_t *key, HCkStringW outStr);
BOOL CkCacheW_GetExpiration(HCkCacheW cHandle, const wchar_t *key, SYSTEMTIME *outSysTime);
HCkDateTimeW CkCacheW_GetExpirationDt(HCkCacheW cHandle, const wchar_t *key);
BOOL CkCacheW_GetFilename(HCkCacheW cHandle, const wchar_t *key, HCkStringW outStr);
BOOL CkCacheW_GetRoot(HCkCacheW cHandle, int index, HCkStringW outStr);
BOOL CkCacheW_IsCached(HCkCacheW cHandle, const wchar_t *key);
BOOL CkCacheW_SaveLastError(HCkCacheW cHandle, const wchar_t *filename);
BOOL CkCacheW_SaveTextDt(HCkCacheW cHandle, const wchar_t *key, HCkDateTimeW expire, const wchar_t *eTag, const wchar_t *strData);
BOOL CkCacheW_SaveTextNoExpire(HCkCacheW cHandle, const wchar_t *key, const wchar_t *eTag, const wchar_t *strData);
BOOL CkCacheW_SaveToCache(HCkCacheW cHandle, const wchar_t *key, SYSTEMTIME *expire, const wchar_t *eTag, HCkByteDataW data);
BOOL CkCacheW_SaveToCacheDt(HCkCacheW cHandle, const wchar_t *key, HCkDateTimeW expire, const wchar_t *eTag, HCkByteDataW data);
BOOL CkCacheW_SaveToCacheNoExpire(HCkCacheW cHandle, const wchar_t *key, const wchar_t *eTag, HCkByteDataW data);
BOOL CkCacheW_UpdateExpiration(HCkCacheW cHandle, const wchar_t *key, SYSTEMTIME *dt);
BOOL CkCacheW_UpdateExpirationDt(HCkCacheW cHandle, const wchar_t *key, HCkDateTimeW dt);
const wchar_t *CkCacheW__debugLogFilePath(HCkCacheW cHandle);
const wchar_t *CkCacheW__fetchText(HCkCacheW cHandle, const wchar_t *key);
const wchar_t *CkCacheW__getEtag(HCkCacheW cHandle, const wchar_t *key);
const wchar_t *CkCacheW__getFilename(HCkCacheW cHandle, const wchar_t *key);
const wchar_t *CkCacheW__getRoot(HCkCacheW cHandle, int index);
const wchar_t *CkCacheW__lastErrorHtml(HCkCacheW cHandle);
const wchar_t *CkCacheW__lastErrorText(HCkCacheW cHandle);
const wchar_t *CkCacheW__lastErrorXml(HCkCacheW cHandle);
const wchar_t *CkCacheW__lastEtagFetched(HCkCacheW cHandle);
const wchar_t *CkCacheW__lastKeyFetched(HCkCacheW cHandle);
#endif
