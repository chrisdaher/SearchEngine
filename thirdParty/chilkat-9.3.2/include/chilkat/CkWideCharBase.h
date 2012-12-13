#ifndef _CkWideCharBase_H
#define _CkWideCharBase_H
#pragma once

#ifndef __sun__
#pragma pack (push, 8)
#endif

#include "CkString.h"

class CkWideCharBase
{
	private:
		
    // Disallow assignment or copying this object.
	CkWideCharBase(const CkWideCharBase &) { }
	CkWideCharBase &operator=(const CkWideCharBase &) { return *this; }

	protected:
		
	unsigned int m_resultIdxW;
	CkString *m_pResultStringW[10];

	unsigned int nextIdxW(void)
	    {
	    m_resultIdxW++;
	    if (m_resultIdxW >= 10)
			{
			m_resultIdxW = 0;
			}
	    if (!m_pResultStringW[m_resultIdxW])
			{
			try
			    {
			    m_pResultStringW[m_resultIdxW] = new CkString;
			    }
			catch (...)
			    {
			    m_pResultStringW[m_resultIdxW] = 0;
			    }
			}
	    return m_resultIdxW;
	    }
	
	const wchar_t *rtnWideString(const char *strUtf8)
	{
	    if (!strUtf8) return 0;
	    unsigned int idxW = nextIdxW();
	    if (!m_pResultStringW[idxW]) return 0;
	    m_pResultStringW[idxW]->setStringUtf8(strUtf8);
	    return m_pResultStringW[idxW]->getUnicode();
	}
	
	public:
		
	CkWideCharBase() : m_resultIdxW(0)
	    {
	    for (int i=0; i<10; i++) m_pResultStringW[i] = 0;
	    }
	virtual ~CkWideCharBase()
	    {
	    for (int i=0; i<10; i++)
			{
			delete m_pResultStringW[i];
			m_pResultStringW[i] = 0;
			}
	    }
	
	
};


#endif
	
