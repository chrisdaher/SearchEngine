#ifndef _CkGzipW_H
#define _CkGzipW_H
#pragma once

#include "CkWideCharBase.h"
#include "CkString.h"
#include "CkGzip.h"

class CkDateTimeW;



#ifndef __sun__
#pragma pack (push, 8) 
#endif


class CkGzipW : public CkWideCharBase
{
    private:
	CkGzip *m_impl;

        // Disallow assignment or copying this object.
	CkGzipW(const CkGzipW &) { }
	CkGzipW &operator=(const CkGzipW &) { return *this; }


    public:
	CkGzipW()
	    {
	    m_impl = new CkGzip;
	    m_impl->put_Utf8(true);
	    }
	CkGzipW(CkGzip *p) : m_impl(p)
	    {
	    if (!m_impl) m_impl = new CkGzip;
	    m_impl->put_Utf8(true);
	    }
	CkGzip *getMbPtr(void) { return m_impl; }
	CkGzip &getMbRef(void) { return *m_impl; }
	const CkGzip *getMbConstPtr(void) const { return m_impl; }
	const CkGzip &getMbConstRef(void) const { return *m_impl; }
	void dispose(void) { m_impl->dispose();  }
	virtual ~CkGzipW() { delete m_impl; m_impl = 0; }

void get_Comment(CkString &propVal);
void put_Comment(const wchar_t *w1);
void get_DebugLogFilePath(CkString &propVal);
void put_DebugLogFilePath(const wchar_t *w1);
void get_ExtraData(CkByteData &propVal);
void put_ExtraData(CkByteData & propVal);
void get_Filename(CkString &propVal);
void put_Filename(const wchar_t *w1);
void LastErrorHtml(CkString &propVal);
void LastErrorText(CkString &propVal);
void LastErrorXml(CkString &propVal);
void get_LastMod(SYSTEMTIME &propVal);
void put_LastMod(SYSTEMTIME & propVal);
bool get_UseCurrentDate(void);
void put_UseCurrentDate(bool propVal);
bool get_VerboseLogging(void);
void put_VerboseLogging(bool propVal);
void get_Version(CkString &propVal);
bool CompressFile(const wchar_t *w1,const wchar_t *w2);
bool CompressFile2(const wchar_t *w1,const wchar_t *w2,const wchar_t *w3);
bool CompressFileToMem(const wchar_t *w1,CkByteData &outData);
bool CompressMemToFile(const CkByteData &db,const wchar_t *w1);
bool CompressMemory(const CkByteData &dbIn,CkByteData &outData);
bool CompressString(const wchar_t *w1,const wchar_t *w2,CkByteData &outBytes);
bool CompressStringToFile(const wchar_t *w1,const wchar_t *w2,const wchar_t *w3);
bool Decode(const wchar_t *w1,const wchar_t *w2,CkByteData &outBytes);
bool DeflateStringENC(const wchar_t *w1,const wchar_t *w2,const wchar_t *w3,CkString &outStr);
bool Encode(CkByteData &byteData,const wchar_t *w1,CkString &outStr);
bool ExamineFile(const wchar_t *w1);
bool ExamineMemory(CkByteData &inGzData);
CkDateTimeW *GetDt(void);
bool InflateStringENC(const wchar_t *w1,const wchar_t *w2,const wchar_t *w3,CkString &outStr);
bool IsUnlocked(void);
bool ReadFile(const wchar_t *w1,CkByteData &outBytes);
bool SaveLastError(const wchar_t *w1);
bool SetDt(CkDateTimeW &dt);
bool UnTarGz(const wchar_t *w1,const wchar_t *w2,bool bNoAbsolute);
bool UncompressFile(const wchar_t *w1,const wchar_t *w2);
bool UncompressFileToMem(const wchar_t *w1,CkByteData &outData);
bool UncompressFileToString(const wchar_t *w1,const wchar_t *w2,CkString &outStr);
bool UncompressMemToFile(const CkByteData &db,const wchar_t *w1);
bool UncompressMemory(const CkByteData &dbIn,CkByteData &outData);
bool UncompressString(CkByteData &inData,const wchar_t *w1,CkString &outStr);
bool UnlockComponent(const wchar_t *w1);
bool WriteFile(const wchar_t *w1,CkByteData &binaryData);
bool XfdlToXml(const wchar_t *w1,CkString &outStr);
const wchar_t *comment(void);
const wchar_t *debugLogFilePath(void);
const wchar_t *deflateStringENC(const wchar_t *w1,const wchar_t *w2,const wchar_t *w3);
const wchar_t *encode(CkByteData &byteData,const wchar_t *w1);
const wchar_t *filename(void);
const wchar_t *inflateStringENC(const wchar_t *w1,const wchar_t *w2,const wchar_t *w3);
const wchar_t *lastErrorHtml(void);
const wchar_t *lastErrorText(void);
const wchar_t *lastErrorXml(void);
const wchar_t *uncompressFileToString(const wchar_t *w1,const wchar_t *w2);
const wchar_t *uncompressString(CkByteData &inData,const wchar_t *w1);
const wchar_t *version(void);
const wchar_t *xfdlToXml(const wchar_t *w1);

};
#endif
