#ifndef _CkCertStoreW_H
#define _CkCertStoreW_H
#pragma once

#include "CkWideCharBase.h"
#include "CkString.h"
#include "CkCertStore.h"

class CkCertW;



#ifndef __sun__
#pragma pack (push, 8) 
#endif


class CkCertStoreW : public CkWideCharBase
{
    private:
	CkCertStore *m_impl;

        // Disallow assignment or copying this object.
	CkCertStoreW(const CkCertStoreW &) { }
	CkCertStoreW &operator=(const CkCertStoreW &) { return *this; }


    public:
	CkCertStoreW()
	    {
	    m_impl = new CkCertStore;
	    m_impl->put_Utf8(true);
	    }
	CkCertStoreW(CkCertStore *p) : m_impl(p)
	    {
	    if (!m_impl) m_impl = new CkCertStore;
	    m_impl->put_Utf8(true);
	    }
	CkCertStore *getMbPtr(void) { return m_impl; }
	CkCertStore &getMbRef(void) { return *m_impl; }
	const CkCertStore *getMbConstPtr(void) const { return m_impl; }
	const CkCertStore &getMbConstRef(void) const { return *m_impl; }
	void dispose(void) { m_impl->dispose();  }
	virtual ~CkCertStoreW() { delete m_impl; m_impl = 0; }

bool get_AvoidWindowsPkAccess(void);
void put_AvoidWindowsPkAccess(bool propVal);
void get_DebugLogFilePath(CkString &propVal);
void put_DebugLogFilePath(const wchar_t *w1);
void LastErrorHtml(CkString &propVal);
void LastErrorText(CkString &propVal);
void LastErrorXml(CkString &propVal);
long get_NumCertificates(void);
bool get_VerboseLogging(void);
void put_VerboseLogging(bool propVal);
void get_Version(CkString &propVal);
CkCertW *FindCertByRfc822Name(const wchar_t *w1);
CkCertW *FindCertBySerial(const wchar_t *w1);
CkCertW *FindCertBySha1Thumbprint(const wchar_t *w1);
CkCertW *FindCertBySubject(const wchar_t *w1);
CkCertW *FindCertBySubjectCN(const wchar_t *w1);
CkCertW *FindCertBySubjectE(const wchar_t *w1);
CkCertW *FindCertBySubjectO(const wchar_t *w1);
CkCertW *GetCertificate(long index);
bool LoadPfxData(CkByteData &pfxData,const wchar_t *w1);
bool LoadPfxData2(const unsigned char *buf,unsigned long bufLen,const wchar_t *w1);
bool LoadPfxFile(const wchar_t *w1,const wchar_t *w2);
bool SaveLastError(const wchar_t *w1);
const wchar_t *debugLogFilePath(void);
const wchar_t *lastErrorHtml(void);
const wchar_t *lastErrorText(void);
const wchar_t *lastErrorXml(void);
const wchar_t *version(void);

};
#endif
