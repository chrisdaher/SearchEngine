#ifndef _CkZipEntryW_H
#define _CkZipEntryW_H
#pragma once

#include "CkWideCharBase.h"
#include "CkString.h"
#include "CkZipEntry.h"

class CkDateTimeW;



#ifndef __sun__
#pragma pack (push, 8) 
#endif


class CkZipEntryW : public CkWideCharBase
{
    private:
	CkZipEntry *m_impl;

        // Disallow assignment or copying this object.
	CkZipEntryW(const CkZipEntryW &) { }
	CkZipEntryW &operator=(const CkZipEntryW &) { return *this; }


    public:
	CkZipEntryW()
	    {
	    m_impl = new CkZipEntry;
	    m_impl->put_Utf8(true);
	    }
	CkZipEntryW(CkZipEntry *p) : m_impl(p)
	    {
	    if (!m_impl) m_impl = new CkZipEntry;
	    m_impl->put_Utf8(true);
	    }
	CkZipEntry *getMbPtr(void) { return m_impl; }
	CkZipEntry &getMbRef(void) { return *m_impl; }
	const CkZipEntry *getMbConstPtr(void) const { return m_impl; }
	const CkZipEntry &getMbConstRef(void) const { return *m_impl; }
	void dispose(void) { m_impl->dispose();  }
	virtual ~CkZipEntryW() { delete m_impl; m_impl = 0; }

void get_Comment(CkString &propVal);
void put_Comment(const wchar_t *w1);
unsigned long get_CompressedLength(void);
__int64 get_CompressedLength64(void);
long get_CompressionLevel(void);
void put_CompressionLevel(long propVal);
long get_CompressionMethod(void);
void put_CompressionMethod(long propVal);
int get_Crc(void);
long get_EntryID(void);
long get_EntryType(void);
void get_FileDateTime(SYSTEMTIME &propVal);
void put_FileDateTime(SYSTEMTIME & propVal);
void get_FileName(CkString &propVal);
void put_FileName(const wchar_t *w1);
bool get_IsDirectory(void);
void LastErrorHtml(CkString &propVal);
void LastErrorText(CkString &propVal);
void LastErrorXml(CkString &propVal);
unsigned long get_UncompressedLength(void);
__int64 get_UncompressedLength64(void);
bool AppendData(const CkByteData &bdata);
bool AppendStringAnsi(const CkString &sdata);
bool Copy(CkByteData &outData);
bool CopyToBase64(CkString &outStr);
bool CopyToHex(CkString &outStr);
bool Extract(const wchar_t *w1);
bool ExtractInto(const wchar_t *w1);
CkDateTimeW *GetDt(void);
bool Inflate(CkByteData &outData);
#if defined(WIN32) | defined(WINCE)
bool InflateToHandle(HANDLE handle);
#endif
bool InflateToString(bool addCR,CkString &outStr);
bool InflateToString2(CkString &outStr);
CkZipEntryW *NextEntry(void);
bool ReplaceData(const CkByteData &bdata);
bool ReplaceStringAnsi(const CkString &sdata);
bool SaveLastError(const wchar_t *w1);
void SetDt(CkDateTimeW &dt);
const wchar_t *comment(void);
const wchar_t *copyToBase64(void);
const wchar_t *copyToHex(void);
const wchar_t *fileName(void);
const wchar_t *inflateToString(bool addCR);
const wchar_t *inflateToString2(void);
const wchar_t *lastErrorHtml(void);
const wchar_t *lastErrorText(void);
const wchar_t *lastErrorXml(void);

};
#endif
