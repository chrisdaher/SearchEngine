#ifndef _CkMailboxes_W_H
#define _CkMailboxes_W_H
#include "Chilkat_C.h"

HCkMailboxesW CkMailboxesW_Create(void);
void CkMailboxesW_Dispose(HCkMailboxesW handle);
long CkMailboxesW_getCount(HCkMailboxesW cHandle);
void CkMailboxesW_getDebugLogFilePath(HCkMailboxesW cHandle, HCkStringW retval);
void CkMailboxesW_putDebugLogFilePath(HCkMailboxesW cHandle, const wchar_t *newVal);
void CkMailboxesW_getLastErrorHtml(HCkMailboxesW cHandle, HCkStringW retval);
void CkMailboxesW_getLastErrorText(HCkMailboxesW cHandle, HCkStringW retval);
void CkMailboxesW_getLastErrorXml(HCkMailboxesW cHandle, HCkStringW retval);
BOOL CkMailboxesW_getVerboseLogging(HCkMailboxesW cHandle);
void CkMailboxesW_putVerboseLogging(HCkMailboxesW cHandle, BOOL newVal);
BOOL CkMailboxesW_GetName(HCkMailboxesW cHandle, long index, HCkStringW outStrName);
BOOL CkMailboxesW_HasInferiors(HCkMailboxesW cHandle, long index);
BOOL CkMailboxesW_IsMarked(HCkMailboxesW cHandle, long index);
BOOL CkMailboxesW_IsSelectable(HCkMailboxesW cHandle, long index);
BOOL CkMailboxesW_SaveLastError(HCkMailboxesW cHandle, const wchar_t *filename);
const wchar_t *CkMailboxesW__debugLogFilePath(HCkMailboxesW cHandle);
const wchar_t *CkMailboxesW__getName(HCkMailboxesW cHandle, long index);
const wchar_t *CkMailboxesW__lastErrorHtml(HCkMailboxesW cHandle);
const wchar_t *CkMailboxesW__lastErrorText(HCkMailboxesW cHandle);
const wchar_t *CkMailboxesW__lastErrorXml(HCkMailboxesW cHandle);
#endif
