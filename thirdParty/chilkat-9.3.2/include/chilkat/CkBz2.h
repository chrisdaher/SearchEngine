// CkBz2.h: interface for the CkBz2 class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _CkBz2_H
#define _CkBz2_H



#include "CkString.h"
class CkByteData;

/*
    IMPORTANT: Objects returned by methods as non-const pointers must be deleted
    by the calling application. 

  */

#include "CkMultiByteBase.h"

class CkBz2Progress;

#ifndef __sun__
#pragma pack (push, 8)
#endif
 

// CLASS: CkBz2
class CkBz2  : public CkMultiByteBase
{
    private:
	CkBz2Progress *m_callback;

	// Don't allow assignment or copying these objects.
	CkBz2(const CkBz2 &) { } 
	CkBz2 &operator=(const CkBz2 &) { return *this; }
	CkBz2(void *impl);

    public:

	CkBz2();
	virtual ~CkBz2();

	// May be called when finished with the object to free/dispose of any
	// internal resources held by the object. 
	void dispose(void);


	// BEGIN PUBLIC INTERFACE
	
	CkBz2Progress *get_EventCallbackObject(void) const;
	void put_EventCallbackObject(CkBz2Progress *progress);

	// UNCOMPRESSFILE_BEGIN
	bool UncompressFile(const char *inFilename, const char *outFilename);
	// UNCOMPRESSFILE_END
	// COMPRESSFILE_BEGIN
	bool CompressFile(const char *inFilename, const char *outFilename);
	// COMPRESSFILE_END
	// UNCOMPRESSFILETOMEM_BEGIN
	bool UncompressFileToMem(const char *inFilename, CkByteData &outBytes);
	// UNCOMPRESSFILETOMEM_END
	// COMPRESSFILETOMEM_BEGIN
	bool CompressFileToMem(const char *inFilename, CkByteData &outBytes);
	// COMPRESSFILETOMEM_END
	// COMPRESSMEMTOFILE_BEGIN
	bool CompressMemToFile(CkByteData &inData, const char *outFilename);
	// COMPRESSMEMTOFILE_END
	// UNCOMPRESSMEMTOFILE_BEGIN
	bool UncompressMemToFile(CkByteData &inData, const char *outFilename);
	// UNCOMPRESSMEMTOFILE_END
	// COMPRESSMEMORY_BEGIN
	bool CompressMemory(CkByteData &inData, CkByteData &outBytes);
	// COMPRESSMEMORY_END
	// UNCOMPRESSMEMORY_BEGIN
	bool UncompressMemory(CkByteData &inData, CkByteData &outBytes);
	// UNCOMPRESSMEMORY_END
	// UNLOCKCOMPONENT_BEGIN
	bool UnlockComponent(const char *regCode);
	// UNLOCKCOMPONENT_END

	// BZ2_INSERT_POINT

	// END PUBLIC INTERFACE

	


};
#ifndef __sun__
#pragma pack (pop)
#endif



#endif


