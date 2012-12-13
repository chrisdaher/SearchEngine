#ifndef _CkSFtp_W_H
#define _CkSFtp_W_H
#include "Chilkat_C.h"

HCkSFtpW CkSFtpW_Create(void);
void CkSFtpW_Dispose(HCkSFtpW handle);
void CkSFtpW_getAccumulateBuffer(HCkSFtpW cHandle, HCkByteDataW retval);
void CkSFtpW_getClientIdentifier(HCkSFtpW cHandle, HCkStringW retval);
void CkSFtpW_putClientIdentifier(HCkSFtpW cHandle, const wchar_t *newVal);
void CkSFtpW_getClientIpAddress(HCkSFtpW cHandle, HCkStringW retval);
void CkSFtpW_putClientIpAddress(HCkSFtpW cHandle, const wchar_t *newVal);
int CkSFtpW_getConnectTimeoutMs(HCkSFtpW cHandle);
void CkSFtpW_putConnectTimeoutMs(HCkSFtpW cHandle, int newVal);
void CkSFtpW_getDebugLogFilePath(HCkSFtpW cHandle, HCkStringW retval);
void CkSFtpW_putDebugLogFilePath(HCkSFtpW cHandle, const wchar_t *newVal);
int CkSFtpW_getDisconnectCode(HCkSFtpW cHandle);
void CkSFtpW_getDisconnectReason(HCkSFtpW cHandle, HCkStringW retval);
BOOL CkSFtpW_getEnableCache(HCkSFtpW cHandle);
void CkSFtpW_putEnableCache(HCkSFtpW cHandle, BOOL newVal);
HCkSFtpProgressW CkSFtpW_getEventCallbackObject(HCkSFtpW cHandle);
void CkSFtpW_putEventCallbackObject(HCkSFtpW cHandle, HCkSFtpProgressW newVal);
void CkSFtpW_getFilenameCharset(HCkSFtpW cHandle, HCkStringW retval);
void CkSFtpW_putFilenameCharset(HCkSFtpW cHandle, const wchar_t *newVal);
void CkSFtpW_getForceCipher(HCkSFtpW cHandle, HCkStringW retval);
void CkSFtpW_putForceCipher(HCkSFtpW cHandle, const wchar_t *newVal);
BOOL CkSFtpW_getForceV3(HCkSFtpW cHandle);
void CkSFtpW_putForceV3(HCkSFtpW cHandle, BOOL newVal);
int CkSFtpW_getHeartbeatMs(HCkSFtpW cHandle);
void CkSFtpW_putHeartbeatMs(HCkSFtpW cHandle, int newVal);
void CkSFtpW_getHostKeyFingerprint(HCkSFtpW cHandle, HCkStringW retval);
void CkSFtpW_getHttpProxyAuthMethod(HCkSFtpW cHandle, HCkStringW retval);
void CkSFtpW_putHttpProxyAuthMethod(HCkSFtpW cHandle, const wchar_t *newVal);
void CkSFtpW_getHttpProxyDomain(HCkSFtpW cHandle, HCkStringW retval);
void CkSFtpW_putHttpProxyDomain(HCkSFtpW cHandle, const wchar_t *newVal);
void CkSFtpW_getHttpProxyHostname(HCkSFtpW cHandle, HCkStringW retval);
void CkSFtpW_putHttpProxyHostname(HCkSFtpW cHandle, const wchar_t *newVal);
void CkSFtpW_getHttpProxyPassword(HCkSFtpW cHandle, HCkStringW retval);
void CkSFtpW_putHttpProxyPassword(HCkSFtpW cHandle, const wchar_t *newVal);
int CkSFtpW_getHttpProxyPort(HCkSFtpW cHandle);
void CkSFtpW_putHttpProxyPort(HCkSFtpW cHandle, int newVal);
void CkSFtpW_getHttpProxyUsername(HCkSFtpW cHandle, HCkStringW retval);
void CkSFtpW_putHttpProxyUsername(HCkSFtpW cHandle, const wchar_t *newVal);
int CkSFtpW_getIdleTimeoutMs(HCkSFtpW cHandle);
void CkSFtpW_putIdleTimeoutMs(HCkSFtpW cHandle, int newVal);
BOOL CkSFtpW_getIncludeDotDirs(HCkSFtpW cHandle);
void CkSFtpW_putIncludeDotDirs(HCkSFtpW cHandle, BOOL newVal);
int CkSFtpW_getInitializeFailCode(HCkSFtpW cHandle);
void CkSFtpW_getInitializeFailReason(HCkSFtpW cHandle, HCkStringW retval);
BOOL CkSFtpW_getIsConnected(HCkSFtpW cHandle);
BOOL CkSFtpW_getKeepSessionLog(HCkSFtpW cHandle);
void CkSFtpW_putKeepSessionLog(HCkSFtpW cHandle, BOOL newVal);
void CkSFtpW_getLastErrorHtml(HCkSFtpW cHandle, HCkStringW retval);
void CkSFtpW_getLastErrorText(HCkSFtpW cHandle, HCkStringW retval);
void CkSFtpW_getLastErrorXml(HCkSFtpW cHandle, HCkStringW retval);
int CkSFtpW_getMaxPacketSize(HCkSFtpW cHandle);
void CkSFtpW_putMaxPacketSize(HCkSFtpW cHandle, int newVal);
BOOL CkSFtpW_getPasswordChangeRequested(HCkSFtpW cHandle);
BOOL CkSFtpW_getPreserveDate(HCkSFtpW cHandle);
void CkSFtpW_putPreserveDate(HCkSFtpW cHandle, BOOL newVal);
int CkSFtpW_getProtocolVersion(HCkSFtpW cHandle);
void CkSFtpW_getSessionLog(HCkSFtpW cHandle, HCkStringW retval);
void CkSFtpW_getSocksHostname(HCkSFtpW cHandle, HCkStringW retval);
void CkSFtpW_putSocksHostname(HCkSFtpW cHandle, const wchar_t *newVal);
void CkSFtpW_getSocksPassword(HCkSFtpW cHandle, HCkStringW retval);
void CkSFtpW_putSocksPassword(HCkSFtpW cHandle, const wchar_t *newVal);
int CkSFtpW_getSocksPort(HCkSFtpW cHandle);
void CkSFtpW_putSocksPort(HCkSFtpW cHandle, int newVal);
void CkSFtpW_getSocksUsername(HCkSFtpW cHandle, HCkStringW retval);
void CkSFtpW_putSocksUsername(HCkSFtpW cHandle, const wchar_t *newVal);
int CkSFtpW_getSocksVersion(HCkSFtpW cHandle);
void CkSFtpW_putSocksVersion(HCkSFtpW cHandle, int newVal);
BOOL CkSFtpW_getTcpNoDelay(HCkSFtpW cHandle);
void CkSFtpW_putTcpNoDelay(HCkSFtpW cHandle, BOOL newVal);
int CkSFtpW_getUploadChunkSize(HCkSFtpW cHandle);
void CkSFtpW_putUploadChunkSize(HCkSFtpW cHandle, int newVal);
BOOL CkSFtpW_getUtcMode(HCkSFtpW cHandle);
void CkSFtpW_putUtcMode(HCkSFtpW cHandle, BOOL newVal);
BOOL CkSFtpW_getVerboseLogging(HCkSFtpW cHandle);
void CkSFtpW_putVerboseLogging(HCkSFtpW cHandle, BOOL newVal);
void CkSFtpW_getVersion(HCkSFtpW cHandle, HCkStringW retval);
int CkSFtpW_AccumulateBytes(HCkSFtpW cHandle, const wchar_t *sftpHandle, int maxBytes);
BOOL CkSFtpW_Add64(HCkSFtpW cHandle, const wchar_t *n1, const wchar_t *n2, HCkStringW outStr);
BOOL CkSFtpW_AuthenticatePk(HCkSFtpW cHandle, const wchar_t *username, HCkSshKeyW privateKey);
BOOL CkSFtpW_AuthenticatePw(HCkSFtpW cHandle, const wchar_t *login, const wchar_t *password);
BOOL CkSFtpW_AuthenticatePwPk(HCkSFtpW cHandle, const wchar_t *username, const wchar_t *password, HCkSshKeyW privateKey);
void CkSFtpW_ClearAccumulateBuffer(HCkSFtpW cHandle);
void CkSFtpW_ClearCache(HCkSFtpW cHandle);
void CkSFtpW_ClearSessionLog(HCkSFtpW cHandle);
BOOL CkSFtpW_CloseHandle(HCkSFtpW cHandle, const wchar_t *sftpHandle);
BOOL CkSFtpW_Connect(HCkSFtpW cHandle, const wchar_t *hostname, int port);
BOOL CkSFtpW_CopyFileAttr(HCkSFtpW cHandle, const wchar_t *localFilePath, const wchar_t *remoteFilenameOrHandle, BOOL bIsHandle);
BOOL CkSFtpW_CreateDir(HCkSFtpW cHandle, const wchar_t *path);
void CkSFtpW_Disconnect(HCkSFtpW cHandle);
BOOL CkSFtpW_DownloadFile(HCkSFtpW cHandle, const wchar_t *sftpHandle, const wchar_t *toFilePath);
BOOL CkSFtpW_DownloadFileByName(HCkSFtpW cHandle, const wchar_t *remoteFilePath, const wchar_t *localFilePath);
BOOL CkSFtpW_Eof(HCkSFtpW cHandle, const wchar_t *sftpHandle);
HCkDateTimeW CkSFtpW_GetFileCreateDt(HCkSFtpW cHandle, const wchar_t *filePathOrHandle, BOOL bFollowLinks, BOOL bIsHandle);
BOOL CkSFtpW_GetFileCreateTime(HCkSFtpW cHandle, const wchar_t *filePathOrHandle, BOOL bFollowLinks, BOOL bIsHandle, SYSTEMTIME *outSysTime);
BOOL CkSFtpW_GetFileGroup(HCkSFtpW cHandle, const wchar_t *filePathOrHandle, BOOL bFollowLinks, BOOL bIsHandle, HCkStringW outStr);
BOOL CkSFtpW_GetFileLastAccess(HCkSFtpW cHandle, const wchar_t *filePathOrHandle, BOOL bFollowLinks, BOOL bIsHandle, SYSTEMTIME *outSysTime);
HCkDateTimeW CkSFtpW_GetFileLastAccessDt(HCkSFtpW cHandle, const wchar_t *filePathOrHandle, BOOL bFollowLinks, BOOL bIsHandle);
BOOL CkSFtpW_GetFileLastModified(HCkSFtpW cHandle, const wchar_t *filePathOrHandle, BOOL bFollowLinks, BOOL bIsHandle, SYSTEMTIME *outSysTime);
HCkDateTimeW CkSFtpW_GetFileLastModifiedDt(HCkSFtpW cHandle, const wchar_t *filePathOrHandle, BOOL bFollowLinks, BOOL bIsHandle);
BOOL CkSFtpW_GetFileOwner(HCkSFtpW cHandle, const wchar_t *filePathOrHandle, BOOL bFollowLinks, BOOL bIsHandle, HCkStringW outStr);
int CkSFtpW_GetFilePermissions(HCkSFtpW cHandle, const wchar_t *filePathOrHandle, BOOL bFollowLinks, BOOL bIsHandle);
unsigned long CkSFtpW_GetFileSize32(HCkSFtpW cHandle, const wchar_t *filePathOrHandle, BOOL bFollowLinks, BOOL bIsHandle);
BOOL CkSFtpW_GetFileSizeStr(HCkSFtpW cHandle, const wchar_t *filePathOrHandle, BOOL bFollowLinks, BOOL bIsHandle, HCkStringW outStr);
BOOL CkSFtpW_InitializeSftp(HCkSFtpW cHandle);
BOOL CkSFtpW_LastReadFailed(HCkSFtpW cHandle, const wchar_t *sftpHandle);
int CkSFtpW_LastReadNumBytes(HCkSFtpW cHandle, const wchar_t *sftpHandle);
BOOL CkSFtpW_OpenDir(HCkSFtpW cHandle, const wchar_t *path, HCkStringW outStr);
BOOL CkSFtpW_OpenFile(HCkSFtpW cHandle, const wchar_t *filePath, const wchar_t *access, const wchar_t *createDisp, HCkStringW outStr);
HCkSFtpDirW CkSFtpW_ReadDir(HCkSFtpW cHandle, const wchar_t *sftpHandle);
BOOL CkSFtpW_ReadFileBytes(HCkSFtpW cHandle, const wchar_t *sftpHandle, int numBytes, HCkByteDataW outBytes);
BOOL CkSFtpW_ReadFileBytes32(HCkSFtpW cHandle, const wchar_t *sftpHandle, int offset, int numBytes, HCkByteDataW outBytes);
BOOL CkSFtpW_ReadFileBytes64(HCkSFtpW cHandle, const wchar_t *sftpHandle, __int64 offset64, int numBytes, HCkByteDataW outBytes);
BOOL CkSFtpW_ReadFileBytes64s(HCkSFtpW cHandle, const wchar_t *sftpHandle, const wchar_t *offset64, int numBytes, HCkByteDataW outBytes);
BOOL CkSFtpW_ReadFileText(HCkSFtpW cHandle, const wchar_t *sftpHandle, int numBytes, const wchar_t *charset, HCkStringW outStr);
BOOL CkSFtpW_ReadFileText32(HCkSFtpW cHandle, const wchar_t *sftpHandle, int offset32, int numBytes, const wchar_t *charset, HCkStringW outStr);
BOOL CkSFtpW_ReadFileText64(HCkSFtpW cHandle, const wchar_t *sftpHandle, __int64 offset64, int numBytes, const wchar_t *charset, HCkStringW outStr);
BOOL CkSFtpW_ReadFileText64s(HCkSFtpW cHandle, const wchar_t *sftpHandle, const wchar_t *offset64, int numBytes, const wchar_t *charset, HCkStringW outStr);
BOOL CkSFtpW_RealPath(HCkSFtpW cHandle, const wchar_t *originalPath, const wchar_t *composePath, HCkStringW outStr);
BOOL CkSFtpW_RemoveDir(HCkSFtpW cHandle, const wchar_t *path);
BOOL CkSFtpW_RemoveFile(HCkSFtpW cHandle, const wchar_t *filePath);
BOOL CkSFtpW_RenameFileOrDir(HCkSFtpW cHandle, const wchar_t *oldPath, const wchar_t *newPath);
BOOL CkSFtpW_ResumeDownloadFileByName(HCkSFtpW cHandle, const wchar_t *remoteFilePath, const wchar_t *localFilePath);
BOOL CkSFtpW_ResumeUploadFileByName(HCkSFtpW cHandle, const wchar_t *remoteFilePath, const wchar_t *localFilePath);
BOOL CkSFtpW_SaveLastError(HCkSFtpW cHandle, const wchar_t *filename);
BOOL CkSFtpW_SetCreateDt(HCkSFtpW cHandle, const wchar_t *pathOrHandle, BOOL bIsHandle, HCkDateTimeW createTime);
BOOL CkSFtpW_SetCreateTime(HCkSFtpW cHandle, const wchar_t *pathOrHandle, BOOL bIsHandle, SYSTEMTIME *createTime);
BOOL CkSFtpW_SetLastAccessDt(HCkSFtpW cHandle, const wchar_t *pathOrHandle, BOOL bIsHandle, HCkDateTimeW createTime);
BOOL CkSFtpW_SetLastAccessTime(HCkSFtpW cHandle, const wchar_t *pathOrHandle, BOOL bIsHandle, SYSTEMTIME *lastAccessTime);
BOOL CkSFtpW_SetLastModifiedDt(HCkSFtpW cHandle, const wchar_t *pathOrHandle, BOOL bIsHandle, HCkDateTimeW createTime);
BOOL CkSFtpW_SetLastModifiedTime(HCkSFtpW cHandle, const wchar_t *pathOrHandle, BOOL bIsHandle, SYSTEMTIME *lastModTime);
BOOL CkSFtpW_SetOwnerAndGroup(HCkSFtpW cHandle, const wchar_t *pathOrHandle, BOOL bIsHandle, const wchar_t *owner, const wchar_t *group);
BOOL CkSFtpW_SetPermissions(HCkSFtpW cHandle, const wchar_t *pathOrHandle, BOOL bIsHandle, int perm);
BOOL CkSFtpW_UnlockComponent(HCkSFtpW cHandle, const wchar_t *unlockCode);
BOOL CkSFtpW_UploadFile(HCkSFtpW cHandle, const wchar_t *sftpHandle, const wchar_t *fromFilePath);
BOOL CkSFtpW_UploadFileByName(HCkSFtpW cHandle, const wchar_t *remoteFilePath, const wchar_t *localFilePath);
BOOL CkSFtpW_WriteFileBytes(HCkSFtpW cHandle, const wchar_t *sftpHandle, HCkByteDataW data);
BOOL CkSFtpW_WriteFileBytes32(HCkSFtpW cHandle, const wchar_t *sftpHandle, int offset, HCkByteDataW data);
BOOL CkSFtpW_WriteFileBytes64(HCkSFtpW cHandle, const wchar_t *sftpHandle, __int64 offset64, HCkByteDataW data);
BOOL CkSFtpW_WriteFileBytes64s(HCkSFtpW cHandle, const wchar_t *sftpHandle, const wchar_t *offset64, HCkByteDataW data);
BOOL CkSFtpW_WriteFileText(HCkSFtpW cHandle, const wchar_t *sftpHandle, const wchar_t *charset, const wchar_t *textData);
BOOL CkSFtpW_WriteFileText32(HCkSFtpW cHandle, const wchar_t *sftpHandle, int offset32, const wchar_t *charset, const wchar_t *textData);
BOOL CkSFtpW_WriteFileText64(HCkSFtpW cHandle, const wchar_t *sftpHandle, __int64 offset64, const wchar_t *charset, const wchar_t *textData);
BOOL CkSFtpW_WriteFileText64s(HCkSFtpW cHandle, const wchar_t *sftpHandle, const wchar_t *offset64, const wchar_t *charset, const wchar_t *textData);
const wchar_t *CkSFtpW__add64(HCkSFtpW cHandle, const wchar_t *n1, const wchar_t *n2);
const wchar_t *CkSFtpW__clientIdentifier(HCkSFtpW cHandle);
const wchar_t *CkSFtpW__clientIpAddress(HCkSFtpW cHandle);
const wchar_t *CkSFtpW__debugLogFilePath(HCkSFtpW cHandle);
const wchar_t *CkSFtpW__disconnectReason(HCkSFtpW cHandle);
const wchar_t *CkSFtpW__filenameCharset(HCkSFtpW cHandle);
const wchar_t *CkSFtpW__forceCipher(HCkSFtpW cHandle);
const wchar_t *CkSFtpW__getFileGroup(HCkSFtpW cHandle, const wchar_t *filePathOrHandle, BOOL bFollowLinks, BOOL bIsHandle);
const wchar_t *CkSFtpW__getFileOwner(HCkSFtpW cHandle, const wchar_t *filePathOrHandle, BOOL bFollowLinks, BOOL bIsHandle);
const wchar_t *CkSFtpW__getFileSizeStr(HCkSFtpW cHandle, const wchar_t *filePathOrHandle, BOOL bFollowLinks, BOOL bIsHandle);
const wchar_t *CkSFtpW__hostKeyFingerprint(HCkSFtpW cHandle);
const wchar_t *CkSFtpW__httpProxyAuthMethod(HCkSFtpW cHandle);
const wchar_t *CkSFtpW__httpProxyDomain(HCkSFtpW cHandle);
const wchar_t *CkSFtpW__httpProxyHostname(HCkSFtpW cHandle);
const wchar_t *CkSFtpW__httpProxyPassword(HCkSFtpW cHandle);
const wchar_t *CkSFtpW__httpProxyUsername(HCkSFtpW cHandle);
const wchar_t *CkSFtpW__initializeFailReason(HCkSFtpW cHandle);
const wchar_t *CkSFtpW__lastErrorHtml(HCkSFtpW cHandle);
const wchar_t *CkSFtpW__lastErrorText(HCkSFtpW cHandle);
const wchar_t *CkSFtpW__lastErrorXml(HCkSFtpW cHandle);
const wchar_t *CkSFtpW__openDir(HCkSFtpW cHandle, const wchar_t *path);
const wchar_t *CkSFtpW__openFile(HCkSFtpW cHandle, const wchar_t *filePath, const wchar_t *access, const wchar_t *createDisp);
const wchar_t *CkSFtpW__readFileText(HCkSFtpW cHandle, const wchar_t *sftpHandle, int numBytes, const wchar_t *charset);
const wchar_t *CkSFtpW__readFileText32(HCkSFtpW cHandle, const wchar_t *sftpHandle, int offset32, int numBytes, const wchar_t *charset);
const wchar_t *CkSFtpW__readFileText64(HCkSFtpW cHandle, const wchar_t *sftpHandle, __int64 offset64, int numBytes, const wchar_t *charset);
const wchar_t *CkSFtpW__readFileText64s(HCkSFtpW cHandle, const wchar_t *sftpHandle, const wchar_t *offset64, int numBytes, const wchar_t *charset);
const wchar_t *CkSFtpW__realPath(HCkSFtpW cHandle, const wchar_t *originalPath, const wchar_t *composePath);
const wchar_t *CkSFtpW__sessionLog(HCkSFtpW cHandle);
const wchar_t *CkSFtpW__socksHostname(HCkSFtpW cHandle);
const wchar_t *CkSFtpW__socksPassword(HCkSFtpW cHandle);
const wchar_t *CkSFtpW__socksUsername(HCkSFtpW cHandle);
const wchar_t *CkSFtpW__version(HCkSFtpW cHandle);
#endif
