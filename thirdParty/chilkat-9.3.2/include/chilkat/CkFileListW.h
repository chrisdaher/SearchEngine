#ifndef _CkFileListW_H
#define _CkFileListW_H
#pragma once

#include "CkWideCharBase.h"
#include "CkString.h"
#include "CkFileList.h"


#ifndef __sun__
#pragma pack (push, 8) 
#endif


class CkFileListW : public CkWideCharBase
{
    private:
	CkFileList m_impl;

        // Disallow assignment or copying this object.
	CkFileListW(const CkFileListW &) { }
	CkFileListW &operator=(const CkFileListW &) { }


    public:
	CkFileListW()
	    {
	    m_impl.put_Utf8(true);
	    }
	virtual ~CkFileListW() { }

// -------------------
// (property get)
// entry name = AppendFromDir
// return type = CkString &
// -------------------
	void get_AppendFromDir(CkString &propVal)
	    {
	    
	    m_impl.get_AppendFromDir(propVal);
	    }
// -------------------
// (property get)
// entry name = AppendFromDir
// return type = CkString &
// -------------------
	const wchar_t *appendFromDir(void)
	    {
	    unsigned int idxW = nextIdxW();
	    if (!m_pResultStringW[idxW]) return 0;
	    m_pResultStringW[idxW]->clear();
	    m_impl.get_AppendFromDir(*(m_pResultStringW[idxW]));
	    return m_pResultStringW[idxW]->getUnicode();
	    }
// -------------------
// (property put)
// entry name = AppendFromDir
// return type = CkString &
// -------------------
	void put_AppendFromDir(CkString & propVal)
	    {
	    
	    m_impl.put_AppendFromDir(propVal);
	    }
// -------------------
// (property get)
// entry name = Count
// return type = int
// -------------------
	int get_Count(void)
	    {
	    
	    return m_impl.get_Count();
	    }
// -------------------
// (property get)
// entry name = LastErrorHtml
// return type = CkString &
// -------------------
	void LastErrorHtml(CkString &propVal)
	    {
	    
	    m_impl.LastErrorHtml(propVal);
	    }
// -------------------
// (property get)
// entry name = LastErrorHtml
// return type = CkString &
// -------------------
	const wchar_t *lastErrorHtml(void)
	    {
	    unsigned int idxW = nextIdxW();
	    if (!m_pResultStringW[idxW]) return 0;
	    m_pResultStringW[idxW]->clear();
	    m_impl.LastErrorHtml(*(m_pResultStringW[idxW]));
	    return m_pResultStringW[idxW]->getUnicode();
	    }
// -------------------
// (property get)
// entry name = LastErrorText
// return type = CkString &
// -------------------
	void LastErrorText(CkString &propVal)
	    {
	    
	    m_impl.LastErrorText(propVal);
	    }
// -------------------
// (property get)
// entry name = LastErrorText
// return type = CkString &
// -------------------
	const wchar_t *lastErrorText(void)
	    {
	    unsigned int idxW = nextIdxW();
	    if (!m_pResultStringW[idxW]) return 0;
	    m_pResultStringW[idxW]->clear();
	    m_impl.LastErrorText(*(m_pResultStringW[idxW]));
	    return m_pResultStringW[idxW]->getUnicode();
	    }
// -------------------
// (property get)
// entry name = LastErrorXml
// return type = CkString &
// -------------------
	void LastErrorXml(CkString &propVal)
	    {
	    
	    m_impl.LastErrorXml(propVal);
	    }
// -------------------
// (property get)
// entry name = LastErrorXml
// return type = CkString &
// -------------------
	const wchar_t *lastErrorXml(void)
	    {
	    unsigned int idxW = nextIdxW();
	    if (!m_pResultStringW[idxW]) return 0;
	    m_pResultStringW[idxW]->clear();
	    m_impl.LastErrorXml(*(m_pResultStringW[idxW]));
	    return m_pResultStringW[idxW]->getUnicode();
	    }
// -------------------
// (method)
// entry name = AppendDirEntry
// return type = bool
//    arg 0: dirPath: const char *
// -------------------
	bool AppendDirEntry(const wchar_t *w1)
	    {
	    CkString sTemp1; sTemp1.appendU(w1);
	    return m_impl.AppendDirEntry(sTemp1.getUtf8());
	    }
// -------------------
// (method)
// entry name = AppendFile
// return type = bool
//    arg 0: filePath: const char *
// -------------------
	bool AppendFile(const wchar_t *w1)
	    {
	    CkString sTemp1; sTemp1.appendU(w1);
	    return m_impl.AppendFile(sTemp1.getUtf8());
	    }
// -------------------
// (method)
// entry name = AppendFiles
// return type = int
//    arg 0: filenamePattern: const char *
//    arg 1: recurse: bool
// -------------------
	int AppendFiles(const wchar_t *w1,bool recurse)
	    {
	    CkString sTemp1; sTemp1.appendU(w1);
	    return m_impl.AppendFiles(sTemp1.getUtf8(),recurse);
	    }
// -------------------
// (method)
// entry name = GetArchivePath
// return type = bool
//    arg 0: idx: int
//    arg 1: outStr: CkString &
// -------------------
	bool GetArchivePath(int idx,CkString &outStr)
	    {
	    
	    return m_impl.GetArchivePath(idx,outStr);
	    }
// -------------------
// (method)
// entry name = GetArchivePath
// return type = bool
//    arg 0: idx: int
//    arg 1: outStr: CkString &
// -------------------
	    const wchar_t *getArchivePath(int idx)
		{
		
		unsigned int idxW = nextIdxW();
		if (!m_pResultStringW[idxW]) return 0;
		m_pResultStringW[idxW]->clear();
		bool success = m_impl.GetArchivePath(idx,*(m_pResultStringW[idxW]));
		if (!success) return 0;
		return m_pResultStringW[idxW]->getUnicode();
		}
// -------------------
// (method)
// entry name = GetData
// return type = bool
//    arg 0: idx: int
//    arg 1: byteData: CkByteData &
// -------------------
	bool GetData(int idx,CkByteData &byteData)
	    {
	    
	    return m_impl.GetData(idx,byteData);
	    }
// -------------------
// (method)
// entry name = GetDiskPath
// return type = bool
//    arg 0: idx: int
//    arg 1: outStr: CkString &
// -------------------
	bool GetDiskPath(int idx,CkString &outStr)
	    {
	    
	    return m_impl.GetDiskPath(idx,outStr);
	    }
// -------------------
// (method)
// entry name = GetDiskPath
// return type = bool
//    arg 0: idx: int
//    arg 1: outStr: CkString &
// -------------------
	    const wchar_t *getDiskPath(int idx)
		{
		
		unsigned int idxW = nextIdxW();
		if (!m_pResultStringW[idxW]) return 0;
		m_pResultStringW[idxW]->clear();
		bool success = m_impl.GetDiskPath(idx,*(m_pResultStringW[idxW]));
		if (!success) return 0;
		return m_pResultStringW[idxW]->getUnicode();
		}
// -------------------
// (method)
// entry name = IsDirectory
// return type = bool
//    arg 0: idx: int
// -------------------
	bool IsDirectory(int idx)
	    {
	    
	    return m_impl.IsDirectory(idx);
	    }
// -------------------
// (method)
// entry name = IsOnDisk
// return type = bool
//    arg 0: idx: int
// -------------------
	bool IsOnDisk(int idx)
	    {
	    
	    return m_impl.IsOnDisk(idx);
	    }
// -------------------
// (method)
// entry name = SaveLastError
// return type = bool
//    arg 0: filename: const char *
// -------------------
	bool SaveLastError(const wchar_t *w1)
	    {
	    CkString sTemp1; sTemp1.appendU(w1);
	    return m_impl.SaveLastError(sTemp1.getUtf8());
	    }
// -------------------
// (method)
// entry name = SetArchivePath
// return type = bool
//    arg 0: idx: int
//    arg 1: filePath: const char *
// -------------------
	bool SetArchivePath(int idx,const wchar_t *w1)
	    {
	    CkString sTemp1; sTemp1.appendU(w1);
	    return m_impl.SetArchivePath(idx,sTemp1.getUtf8());
	    }
// -------------------
// (method)
// entry name = StringReplace
// return type = void
//    arg 0: findStr: const char *
//    arg 1: replaceStr: const char *
// -------------------
	void StringReplace(const wchar_t *w1,const wchar_t *w2)
	    {
	    CkString sTemp1; sTemp1.appendU(w1);
		CkString sTemp2; sTemp2.appendU(w2);
	    m_impl.StringReplace(sTemp1.getUtf8(),sTemp2.getUtf8());
	    }

};
#endif
