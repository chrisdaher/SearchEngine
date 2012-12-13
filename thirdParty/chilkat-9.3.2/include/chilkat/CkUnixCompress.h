// CkUnixCompress.h: interface for the CkUnixCompress class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CKUNIXCOMPRESS_H__6362F307_B140_4CA5_9EA7_5090F4F1EC2A__INCLUDED_)
#define AFX_CKUNIXCOMPRESS_H__6362F307_B140_4CA5_9EA7_5090F4F1EC2A__INCLUDED_


#include "CkMultiByteBase.h"

#include "CkString.h"
class CkByteData;

#ifndef __sun__
#pragma pack (push, 8)
#endif
 

// CLASS: CkUnixCompress
class CkUnixCompress  : public CkMultiByteBase 
{
public:
    private:
	// Don't allow assignment or copying these objects.
	CkUnixCompress(const CkUnixCompress &) { } 
	CkUnixCompress &operator=(const CkUnixCompress &) { return *this; }
	CkUnixCompress(void *impl);

    public:
	CkUnixCompress();
	virtual ~CkUnixCompress();

	// May be called when finished with the object to free/dispose of any
	// internal resources held by the object. 
	void dispose(void);

	// BEGIN PUBLIC INTERFACE

	bool UnlockComponent(const char *unlockCode);
	bool IsUnlocked(void) const;

	// File-to-file
	bool CompressFile(const char *inFilename, const char *outFilename);
	bool UncompressFile(const char *inFilename, const char *outFilename);

	// File-to-memory
	bool CompressFileToMem(const char *inFilename, CkByteData &outData);
	bool UncompressFileToMem(const char *inFilename, CkByteData &outData);

	// Memory-to-file
	bool CompressMemToFile(const CkByteData &db, const char *outFilename);
	bool UncompressMemToFile(const CkByteData &db, const char *outFilename);
	
	// Memory-to-memory
	bool CompressMemory(const CkByteData &dbIn, CkByteData &outData);
	bool UncompressMemory(const CkByteData &dbIn, CkByteData &outData);

	bool UnTarZ(const char *zFilename, const char *destDir, bool bNoAbsolute);

	// UNCOMPRESSSTRING_BEGIN
	bool UncompressString(CkByteData &inData, const char *inCharset, CkString &outStr);
	const char *uncompressString(CkByteData &inData, const char *inCharset);
	// UNCOMPRESSSTRING_END
	// UNCOMPRESSFILETOSTRING_BEGIN
	bool UncompressFileToString(const char *inFilename, const char *inCharset, CkString &outStr);
	const char *uncompressFileToString(const char *inFilename, const char *inCharset);
	// UNCOMPRESSFILETOSTRING_END
	// COMPRESSSTRINGTOFILE_BEGIN
	bool CompressStringToFile(const char *inStr, const char *outCharset, const char *outFilename);
	// COMPRESSSTRINGTOFILE_END
	// COMPRESSSTRING_BEGIN
	bool CompressString(const char *inStr, const char *outCharset, CkByteData &outBytes);
	// COMPRESSSTRING_END

	// UNIXCOMPRESS_INSERT_POINT

	// END PUBLIC INTERFACE


};
#ifndef __sun__
#pragma pack (pop)
#endif


#endif // !defined(AFX_CKUNIXCOMPRESS_H__6362F307_B140_4CA5_9EA7_5090F4F1EC2A__INCLUDED_)
