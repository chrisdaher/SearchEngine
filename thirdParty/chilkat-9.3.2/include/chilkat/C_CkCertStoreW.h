#ifndef _CkCertStore_W_H
#define _CkCertStore_W_H
#include "Chilkat_C.h"

HCkCertStoreW CkCertStoreW_Create(void);
void CkCertStoreW_Dispose(HCkCertStoreW handle);
BOOL CkCertStoreW_getAvoidWindowsPkAccess(HCkCertStoreW cHandle);
void CkCertStoreW_putAvoidWindowsPkAccess(HCkCertStoreW cHandle, BOOL newVal);
void CkCertStoreW_getDebugLogFilePath(HCkCertStoreW cHandle, HCkStringW retval);
void CkCertStoreW_putDebugLogFilePath(HCkCertStoreW cHandle, const wchar_t *newVal);
void CkCertStoreW_getLastErrorHtml(HCkCertStoreW cHandle, HCkStringW retval);
void CkCertStoreW_getLastErrorText(HCkCertStoreW cHandle, HCkStringW retval);
void CkCertStoreW_getLastErrorXml(HCkCertStoreW cHandle, HCkStringW retval);
long CkCertStoreW_getNumCertificates(HCkCertStoreW cHandle);
BOOL CkCertStoreW_getVerboseLogging(HCkCertStoreW cHandle);
void CkCertStoreW_putVerboseLogging(HCkCertStoreW cHandle, BOOL newVal);
void CkCertStoreW_getVersion(HCkCertStoreW cHandle, HCkStringW retval);
HCkCertW CkCertStoreW_FindCertByRfc822Name(HCkCertStoreW cHandle, const wchar_t *name);
HCkCertW CkCertStoreW_FindCertBySerial(HCkCertStoreW cHandle, const wchar_t *serialNumber);
HCkCertW CkCertStoreW_FindCertBySha1Thumbprint(HCkCertStoreW cHandle, const wchar_t *str);
HCkCertW CkCertStoreW_FindCertBySubject(HCkCertStoreW cHandle, const wchar_t *subject);
HCkCertW CkCertStoreW_FindCertBySubjectCN(HCkCertStoreW cHandle, const wchar_t *commonName);
HCkCertW CkCertStoreW_FindCertBySubjectE(HCkCertStoreW cHandle, const wchar_t *emailAddress);
HCkCertW CkCertStoreW_FindCertBySubjectO(HCkCertStoreW cHandle, const wchar_t *organization);
HCkCertW CkCertStoreW_GetCertificate(HCkCertStoreW cHandle, long index);
BOOL CkCertStoreW_LoadPfxData(HCkCertStoreW cHandle, HCkByteDataW pfxData, const wchar_t *password);
BOOL CkCertStoreW_LoadPfxData2(HCkCertStoreW cHandle, const unsigned char *buf, unsigned long bufLen, const wchar_t *password);
BOOL CkCertStoreW_LoadPfxFile(HCkCertStoreW cHandle, const wchar_t *filename, const wchar_t *password);
BOOL CkCertStoreW_SaveLastError(HCkCertStoreW cHandle, const wchar_t *filename);
const wchar_t *CkCertStoreW__debugLogFilePath(HCkCertStoreW cHandle);
const wchar_t *CkCertStoreW__lastErrorHtml(HCkCertStoreW cHandle);
const wchar_t *CkCertStoreW__lastErrorText(HCkCertStoreW cHandle);
const wchar_t *CkCertStoreW__lastErrorXml(HCkCertStoreW cHandle);
const wchar_t *CkCertStoreW__version(HCkCertStoreW cHandle);
#endif
