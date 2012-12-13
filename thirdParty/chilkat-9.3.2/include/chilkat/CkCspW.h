#ifndef _CkCSPW_H
#define _CkCSPW_H
#pragma once

#include "CkWideCharBase.h"
#include "CkString.h"
#include "CkCSP.h"

class CkStringArrayW;



#ifndef __sun__
#pragma pack (push, 8) 
#endif


class CkCSPW : public CkWideCharBase
{
    private:
	CkCSP *m_impl;

        // Disallow assignment or copying this object.
	CkCSPW(const CkCSPW &) { }
	CkCSPW &operator=(const CkCSPW &) { return *this; }


    public:
	CkCSPW()
	    {
	    m_impl = new CkCSP;
	    m_impl->put_Utf8(true);
	    }
	CkCSPW(CkCSP *p) : m_impl(p)
	    {
	    if (!m_impl) m_impl = new CkCSP;
	    m_impl->put_Utf8(true);
	    }
	CkCSP *getMbPtr(void) { return m_impl; }
	CkCSP &getMbRef(void) { return *m_impl; }
	const CkCSP *getMbConstPtr(void) const { return m_impl; }
	const CkCSP &getMbConstRef(void) const { return *m_impl; }
	void dispose(void) { m_impl->dispose();  }
	virtual ~CkCSPW() { delete m_impl; m_impl = 0; }

void get_DebugLogFilePath(CkString &propVal);
void put_DebugLogFilePath(const wchar_t *w1);
void get_EncryptAlgorithm(CkString &propVal);
long get_EncryptAlgorithmID(void);
long get_EncryptNumBits(void);
void get_HashAlgorithm(CkString &propVal);
long get_HashAlgorithmID(void);
long get_HashNumBits(void);
void get_KeyContainer(CkString &propVal);
void put_KeyContainer(const wchar_t *w1);
void LastErrorHtml(CkString &propVal);
void LastErrorText(CkString &propVal);
void LastErrorXml(CkString &propVal);
bool get_MachineKeyset(void);
void put_MachineKeyset(bool propVal);
long get_NumEncryptAlgorithms(void);
long get_NumHashAlgorithms(void);
long get_NumKeyContainers(void);
long get_NumKeyExchangeAlgorithms(void);
long get_NumSignatureAlgorithms(void);
void get_ProviderName(CkString &propVal);
void put_ProviderName(const wchar_t *w1);
long get_ProviderType(void);
bool get_VerboseLogging(void);
void put_VerboseLogging(bool propVal);
CkStringArrayW *GetKeyContainerNames(void);
bool HasEncryptAlgorithm(const wchar_t *w1,long numBits);
bool HasHashAlgorithm(const wchar_t *w1,long numBits);
bool NthEncryptionAlgorithm(long index,CkString &outName);
long NthEncryptionNumBits(long index);
bool NthHashAlgorithmName(long index,CkString &outName);
long NthHashNumBits(long index);
bool NthKeyContainerName(long index,CkString &outName);
bool NthKeyExchangeAlgorithm(long index,CkString &outName);
long NthKeyExchangeNumBits(long index);
bool NthSignatureAlgorithm(long index,CkString &outName);
long NthSignatureNumBits(long index);
bool SaveLastError(const wchar_t *w1);
long SetEncryptAlgorithm(const wchar_t *w1);
long SetHashAlgorithm(const wchar_t *w1);
bool SetProviderMicrosoftBase(void);
bool SetProviderMicrosoftEnhanced(void);
bool SetProviderMicrosoftRsaAes(void);
bool SetProviderMicrosoftStrong(void);
const wchar_t *debugLogFilePath(void);
const wchar_t *encryptAlgorithm(void);
const wchar_t *hashAlgorithm(void);
const wchar_t *keyContainer(void);
const wchar_t *lastErrorHtml(void);
const wchar_t *lastErrorText(void);
const wchar_t *lastErrorXml(void);
const wchar_t *nthEncryptionAlgorithm(long index);
const wchar_t *nthHashAlgorithmName(long index);
const wchar_t *nthKeyContainerName(long index);
const wchar_t *nthKeyExchangeAlgorithm(long index);
const wchar_t *nthSignatureAlgorithm(long index);
const wchar_t *providerName(void);

};
#endif
