// CkCache.h: interface for the CkCache class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _CKCACHE_H
#define _CKCACHE_H



#include "CkString.h"
class CkByteData;

#if !defined(WIN32) && !defined(WINCE)
#include "SystemTime.h"
#endif

/*
    IMPORTANT: Objects returned by methods as non-const pointers must be deleted
    by the calling application. 

  */

#include "CkMultiByteBase.h"

#ifndef __sun__
#pragma pack (push, 8)
#endif
 
class CkDateTime;

// CLASS: CkCache
class CkCache  : public CkMultiByteBase
{
    private:

	// Don't allow assignment or copying these objects.
	CkCache(const CkCache &) { } 
	CkCache &operator=(const CkCache &) { return *this; }
	CkCache(void *impl);

    public:

	CkCache();
	virtual ~CkCache();

	// May be called when finished with the object to free/dispose of any
	// internal resources held by the object. 
	void dispose(void);

	// BEGIN PUBLIC INTERFACE

	bool SaveTextDt(const char *key, CkDateTime &expire, const char *eTag, const char *strData);
	bool UpdateExpirationDt(const char *key, CkDateTime &dt);
	bool SaveToCacheDt(const char *key, CkDateTime &expire, const char *eTag, CkByteData &data);
	CkDateTime *GetExpirationDt(const char *key);
	

	int DeleteOlderDt(CkDateTime &dt);

	void get_LastEtagFetched(CkString &str);
	const char *lastEtagFetched(void);

	void get_LastExpirationFetched(SYSTEMTIME &outSysTime);

	bool get_LastHitExpired(void);

	void get_LastKeyFetched(CkString &str);
	const char *lastKeyFetched(void);

	int get_Level(void);
	void put_Level(int newVal);

	int get_NumRoots(void);

	void AddRoot(const char *path);

	int DeleteAll(void);

	int DeleteAllExpired(void);

	bool DeleteFromCache(const char *key);

	int DeleteOlder(SYSTEMTIME &dt);

	bool FetchFromCache(const char *key, CkByteData &outBytes);

	bool GetEtag(const char *key, CkString &outStr);
	const char *getEtag(const char *key);

	bool GetExpiration(const char *key, SYSTEMTIME &outSysTime);

	bool GetFilename(const char *key, CkString &outStr);
	const char *getFilename(const char *key);

	bool GetRoot(int index, CkString &outStr);
	const char *getRoot(int index);

	bool IsCached(const char *key);

	bool SaveToCache(const char *key, SYSTEMTIME &expire, const char *eTag, CkByteData &data);

	bool SaveToCacheNoExpire(const char *key, const char *eTag, CkByteData &data);

	bool UpdateExpiration(const char *key, SYSTEMTIME &dt);

	bool FetchText(const char *key, CkString &outStr);
	const char *fetchText(const char *key);

	bool SaveText(const char *key, SYSTEMTIME &expire, 
	    const char *eTag, const char *strData);

	bool SaveTextNoExpire(const char *key, const char *eTag, const char *strData);


	// CACHE_INSERT_POINT

	// END PUBLIC INTERFACE

	


};
#ifndef __sun__
#pragma pack (pop)
#endif



#endif


