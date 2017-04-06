#ifndef _WCU_H
#define _WCU_H

/** @def LIBSPEC
 *     동적 링크 라이브러리를 만들 경우 심볼들의 특성을 정의해 준다. 
 *     */
#ifdef LIBSPEC
#undef LIBSPEC
#endif

#if defined(EXPORT_WCU)
#define LIBSPEC __declspec(dllexport)
#elif defined(IMPORT_WCU)
#define LIBSPEC __declspec(dllimport)
#else
#define LIBSPEC
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* common errors */
typedef enum {
	BG_WCU_INVALID_KEYTYPE = -3000,
	BG_WCU_NO_KEY_SELECTED,
	BG_WCU_MORE_DATA,
	BG_WCU_FILE_CANNOT_WRITE,
	BG_WCU_FILE_CANNOT_CREATE,
	BG_WCU_MORE_MEMORY
}	ER_WCU_ERRORS;

#ifndef SUCCESS
#define SUCCESS 0
#endif

#ifndef FAIL
#define FAIL -1
#endif

#define HARD			0x01
#define FLOPPY		0x02
#define SMARTCARD 0x04
#define USB				0x08
#define USBKEY		0x10 //addstorage34
#define NETBIOS		0x20
#define CPHONE		0x40

#define BG_WCU_DELIMETER "|"
#define BG_WCU_FT_USER_SKEY        0x01
#define BG_WCU_FT_USER_PRIKEY      0x02
#define BG_WCU_FT_SMARTCARD        0x04
#define BG_WCU_FT_USER_CERT        0x02
#define BG_WCU_FT_ROOT_CA_CERT     0x08
#define BG_WCU_FT_CA_CERT          0x10
#define BG_WCU_FT_OTHER_CERT       0x20

// 전체 Folder Type 들
// 개인 키와 비공개키를 위한 Type

// 출력하고자 하는 Key Usage를 선택하기 위한 Flag
#define SELKEY_KU_DigitalSignature 0x8000
#define SELKEY_KU_NonRepudiation   0x4000
#define SELKEY_KU_KeyEncipherment  0x2000
#define SELKEY_KU_DataEncipherment 0x1000
#define SELKEY_KU_KeyAgreement     0x0800
#define SELKEY_KU_KeyCertSign      0x0400
#define SELKEY_KU_CRLSign          0x0200
#define SELKEY_KU_EncipherOnly     0x0100
#define SELKEY_KU_DecipherOnly     0x0080

// 서명용, 암호화용 용도...(KeyAgreement는 제외되어 있음.)
#define SELKEY_KU_Signature        (SELKEY_KU_DigitalSignature | SELKEY_KU_NonRepudiation \
                                    | SELKEY_KU_KeyCertSign | SELKEY_KU_CRLSign)
#define SELKEY_KU_Encipher         (SELKEY_KU_KeyEncipherment | SELKEY_KU_DataEncipherment \
                                    | SELKEY_KU_EncipherOnly | SELKEY_KU_DecipherOnly)
#define SELKEY_KU_ALL              0xffff
//김대형
//LIBSPEC 
LIBSPEC int
BG_WCU_SelectKey(
				char	**ppszKeyName,	// out  : 복수개일 경우 BG_WCU_DELIMETER로 구분됨
				int		*pCount,		// out
				int		nKeyType,		// in
				int		nKeyFolderType,	// in
				int		nFlag,			// in
        int   nTrayMenu); //  in


LIBSPEC
int BG_WCU_SelectCert_FromDirectory(
				char	*pszFileName,	//out
				int		nBufLen,		//in
		const	char	*pszBaseDn,		//in
		const	char	*pszObjectClass,//in
		const	char	*pszLdapIP,		//in
				int		nLdapPort,		//in
				int		nTarget	);		//in

LIBSPEC
int BG_WCU_ImportCert(
        char  *szKeyName,   //out
        int   nBufLen);     //in

LIBSPEC
int BG_WCU_ImportCnK(
        char  *szKeyName,     //out
        int   nBufLen,        //in
        char  *pszPIN,        //out
        int   nBufLen2);      //int

#ifdef __cplusplus
}
#endif


#endif //_WCU_H