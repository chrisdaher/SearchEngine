// CkCert.h: interface for the CkCert class.
//
//////////////////////////////////////////////////////////////////////
#ifndef _CKCERT_H
#define _CKCERT_H



class CkString;

#include "CkMultiByteBase.h"
#include "CkString.h"
#include "CkByteData.h"

#if !defined(WIN32) && !defined(WINCE)
#include "SystemTime.h"
#endif

class CkPublicKey;
class CkPrivateKey;
class CkDateTime;

#ifndef __sun__
#pragma pack (push, 8)
#endif
 

// CLASS: CkCert
class CkCert : public CkMultiByteBase 
{
    private:
	// Don't allow assignment or copying these objects.
	CkCert(const CkCert &) { } 
	CkCert &operator=(const CkCert &) { return *this; }

    public:
	CkCert(void *impl);
	CkCert();
	virtual ~CkCert();

	// May be called when finished with the object to free/dispose of any
	// internal resources held by the object. 
	void dispose(void);

	bool LoadFromBinary(const char *buf, unsigned long bufLen);


	// BEGIN PUBLIC INTERFACE
	// GETVALIDFROMDT_BEGIN
	CkDateTime *GetValidFromDt(void);
	// GETVALIDFROMDT_END

	// GETVALIDTODT_BEGIN
	CkDateTime *GetValidToDt(void);
	// GETVALIDTODT_END

#if defined(WIN32) && !defined(__MINGW32__)
	bool ExportToPfxFile(const char *pfxFilename, const char *password, bool bIncludeChain);
	bool LinkPrivateKey(const char *keyContainerName, bool bMachineKeyset, bool bForSigning);
#endif

	bool LoadPfxFile(const char *filename, const char *password);
	bool LoadPfxData(CkByteData &pfxData, const char *password);
	bool LoadPfxData2(const unsigned char *buf, unsigned long bufLen, const char *password);

	bool LoadFromFile(const char *filename);
	bool LoadFromBase64(const char *encodedCert);
	bool LoadFromBinary(const unsigned char *buf, unsigned long bufLen);
	bool SetFromEncoded(const char *encodedCert);
	bool GetEncoded(CkString &outStr);
	bool get_IsRoot(void);
	void get_IssuerE(CkString &str);
	void get_IssuerC(CkString &str);
	void get_IssuerS(CkString &str);
	void get_IssuerL(CkString &str);
	void get_IssuerO(CkString &str);
	void get_IssuerOU(CkString &str);
	void get_IssuerCN(CkString &str);
	void get_IssuerDN(CkString &str);
	void get_SubjectE(CkString &str);
	void get_SubjectC(CkString &str);
	void get_SubjectS(CkString &str);
	void get_SubjectL(CkString &str);
	void get_SubjectO(CkString &str);
	void get_SubjectOU(CkString &str);
	void get_SubjectCN(CkString &str);
	void get_SubjectDN(CkString &str);
	void get_Sha1Thumbprint(CkString &str);

	//bitwise-OR:
	//#define CERT_DIGITAL_SIGNATURE_KEY_USAGE     0x80
	//#define CERT_NON_REPUDIATION_KEY_USAGE       0x40
	//#define CERT_KEY_ENCIPHERMENT_KEY_USAGE      0x20
	//#define CERT_DATA_ENCIPHERMENT_KEY_USAGE     0x10
	//#define CERT_KEY_AGREEMENT_KEY_USAGE         0x08
	//#define CERT_KEY_CERT_SIGN_KEY_USAGE         0x04
	//#define CERT_OFFLINE_CRL_SIGN_KEY_USAGE      0x02
	//#define CERT_CRL_SIGN_KEY_USAGE              0x02
	//#define CERT_ENCIPHER_ONLY_KEY_USAGE         0x01
	unsigned long get_IntendedKeyUsage(void);

	bool get_SignatureVerified(void);
	bool get_TrustedRoot(void);
	bool get_Revoked(void);
	bool get_Expired(void);

	bool HasPrivateKey(void);

	bool SaveToFile(const char *filename);

	// Subject Alternative Name (RFC822) -- Not present in all certificates.
	void get_Rfc822Name(CkString &str);
	
	// SYSTEMTIME is defined in <windows.h>
	// For more information, Google "SYSTEMTIME"
	void get_ValidTo(SYSTEMTIME &outSysTime);
	void get_ValidFrom(SYSTEMTIME &outSysTime);
	void get_SerialNumber(CkString &str);
	bool get_ForTimeStamping(void);
	bool get_ForCodeSigning(void);
	bool get_ForClientAuthentication(void);
	bool get_ForServerAuthentication(void);
	bool get_ForSecureEmail(void);
	void get_Version(CkString &str);


	const char *getEncoded(void);
	const char *issuerE(void);
	const char *issuerC(void);
	const char *issuerS(void);
	const char *issuerL(void);
	const char *issuerO(void);
	const char *issuerOU(void);
	const char *issuerCN(void);
	const char *issuerDN(void);
	const char *subjectE(void);
	const char *subjectC(void);
	const char *subjectS(void);
	const char *subjectL(void);
	const char *subjectO(void);
	const char *subjectOU(void);
	const char *subjectCN(void);
	const char *subjectDN(void);
	const char *sha1Thumbprint(void);
	const char *rfc822Name(void);
	const char *serialNumber(void);
	const char *version(void);


	bool get_HasKeyContainer(void);
	// If HasKeyContainer is false, then the certificate is not associated
	// with a key container.
	void get_KeyContainerName(CkString &str);
	const char *keyContainerName(void);
	void get_CspName(CkString &str);
	const char *cspName(void);
	bool get_MachineKeyset(void);
	bool get_Silent(void);

	bool LoadByEmailAddress(const char *emailAddress);
	bool LoadByCommonName(const char *cn);


	bool ExportCertPem(CkString &outStr);
	bool ExportCertPemFile(const char *filename);
	bool ExportCertDer(CkByteData &outData);
	bool ExportCertDerFile(const char *filename);

	bool PemFileToDerFile(const char *inFilename, const char *outFilename);

	CkPublicKey *ExportPublicKey(void);
	CkPrivateKey *ExportPrivateKey(void);

	const char *exportCertPem(void);

	int CheckRevoked(void);
	// EXPORTCERTXML_BEGIN
	bool ExportCertXml(CkString &outStr);
	const char *exportCertXml(void);
	// EXPORTCERTXML_END
	// VERBOSELOGGING_BEGIN
	bool get_VerboseLogging(void);
	void put_VerboseLogging(bool newVal);
	// VERBOSELOGGING_END
	// CERTVERSION_BEGIN
	int get_CertVersion(void);
	// CERTVERSION_END
	// SETPRIVATEKEY_BEGIN
	bool SetPrivateKey(CkPrivateKey &privKey);
	// SETPRIVATEKEY_END
	// OCSPURL_BEGIN
	void get_OcspUrl(CkString &str);
	const char *ocspUrl(void);
	// OCSPURL_END
	// FINDISSUER_BEGIN
	CkCert *FindIssuer(void);
	// FINDISSUER_END
	// LOADBYISSUERANDSERIALNUMBER_BEGIN
	bool LoadByIssuerAndSerialNumber(const char *issuerCN, const char *serialNum);
	// LOADBYISSUERANDSERIALNUMBER_END
	// SELFSIGNED_BEGIN
	bool get_SelfSigned(void);
	// SELFSIGNED_END
	// SETPRIVATEKEYPEM_BEGIN
	bool SetPrivateKeyPem(const char *privKeyPem);
	// SETPRIVATEKEYPEM_END
	// GETPRIVATEKEYPEM_BEGIN
	bool GetPrivateKeyPem(CkString &outStr);
	const char *getPrivateKeyPem(void);
	// GETPRIVATEKEYPEM_END
	// PRIVATEKEYEXPORTABLE_BEGIN
	bool get_PrivateKeyExportable(void);
	// PRIVATEKEYEXPORTABLE_END
	// AVOIDWINDOWSPKACCESS_BEGIN
	bool get_AvoidWindowsPkAccess(void);
	void put_AvoidWindowsPkAccess(bool newVal);
	// AVOIDWINDOWSPKACCESS_END

	// CERT_INSERT_POINT

	// END PUBLIC INTERFACE
	

	// The following methods should not be called by an application.
	// They for internal use only.
	void inject(void *impl);


};
#ifndef __sun__
#pragma pack (pop)
#endif


#endif

