

#pragma once
#include "IF_SDK.h"


#include "BioAPI.h"
#include "DssFpError.h"


#ifdef __cplusplus
extern "C" {
#endif 		

#ifdef DSS_EXPORTS
#define DSS __declspec(dllexport)
#else
#define DSS __declspec(dllimport)
#endif

#ifndef FAIL
#define FAIL -1
#endif

#ifndef SUCCESS
#define SUCCESS 0
#endif

#define MAX_IP_LEN 32
#define CERT_SERIAL_SIZE   32
#define DSS_SDK_VERSION    "1.0"

#ifndef XATMI_SERVICE_NAME_LENGTH 
#define XATMI_SERVICE_NAME_LENGTH 16	/* where x must be > 15 */
#ifndef MAXTIDENT
#define MAXTIDENT	XATMI_SERVICE_NAME_LENGTH /* max len of identifier */
#endif
#endif
  
#ifndef MAX_PASSWD_LENGTH
#define MAX_PASSWD_LENGTH  16
#endif

#ifndef TPNOFLAGS
#define TPNOFLAGS          0x00000000
#endif

#ifndef IDN_ERR_CODE_221
#define  IDN_ERR_CODE_221  221
#endif
  
#ifndef IDN_ERR_CODE_203
#define  IDN_ERR_CODE_203  203
#endif

//************************************************************//
/*
  typedef struct tagIFDNLIST
  {
    TCHAR		szDn[MAX_PATH];
    long    time;      //釭醞縑 檜高擎 localtime()蒂 ��轎п憮 displayй熱氈棻.
  }IFDNLIST, FAR *LPIFDNLIST;
  
  
  typedef struct tagIFFILELIST
  {
    INT			nSucc;
    TCHAR		szSrcName[MAX_PATH]; // ≠≠≠ 瞪濠 憮貲衛 奩萄衛 fullpath煎 剩橫諦撿 и棻.
    TCHAR		szTgtName[MAX_PATH];
    TCHAR		szMoreInfo[MAX_PATH];
  }IFFILELIST, FAR *LPIFFILELIST;
  
  const int IFFILELISTSIZE = sizeof(IFFILELIST);
  
  typedef struct tagIFERROR
  {
    int		nErrorCode;
    int		nGroup;
  } IFERROR, FAR *LPIFERROR;
*/
//************************************************************//
  
DSS BOOL DSS_EncryptFiles (IFFILELIST *pFileList, 
													 INT	 	 	  *pFileCnt);

DSS BOOL DSS_EncryptFilesTo (IFFILELIST *pFileList, 
														 INT				 *pFileCnt);

DSS BOOL DSS_EncryptAdd (LPTSTR lpszEncryptedFileName);

DSS BOOL DSS_DecryptFiles (IFFILELIST *pFileList, 
													 INT			  *pFileCnt);

DSS BOOL DSS_ESignFiles(LPIFFILELIST  pFileList, 
       									INT				   *pFileCnt);

DSS INT  DSS_MyESignAddToESignFile(LPTSTR  lpszFile);

//DSS INT	 DSS_ESignAdd(LPTSTR  lpszFile); 
                    //	INT     nSignAlgo, 
									  //  SSACnK *myCnK);

DSS INT  DSS_SearchMyESign(LPTSTR lpszFile);

DSS BOOL DSS_ESignVerify(LPTSTR szSignedFileName, LPTSTR szDn);

DSS BOOL DSS_GetDnFromESignFile(char *lpszFileName, 
																LPIFDNLIST  pDnList, 
																int        *pDnCount);

//DSS BOOL DSS_ImportCert(LPTSTR szSignedFileName, 
	//												        LPTSTR szDn);

DSS BOOL DSS_ExportCnKToPfx (LPTSTR  lpszFileName, LPTSTR  lpszPin);
DSS INT  DSS_VerifyCardPin(char *pin);

DSS INT  DSS_GetLastError();
DSS INT DSS_SetLastError(INT nErrorCode);

DSS INT DSS_OriginFile(LPTSTR lpszSource, 
												         LPTSTR lpszTarget);

DSS BOOL DSS_OriginFiles(LPIFFILELIST pFileList, 
												 INT					*pFileCnt);

DSS BOOL DSS_GetUserName(char *szUserName);

DSS INT DSS_ChangeCardPin(LPTSTR szOldPin, LPTSTR szNewPin);
DSS INT DSS_GetUserInfoFromSC(BYTE *lpUserInfo, int cSize);
DSS INT DSS_GetSubjectCnFromSC(LPTSTR sdn, int *snLen);



/** DSS_SigVal 式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
    @ingroup SSA_SG
    @brief 瞪濠 憮貲 儅撩 л熱(No Message Format)
    
    message蒂 殮溘戲煎 嫡嬴 cnk縑 んл腎橫 氈朝 綠奢偃酈煎 瞪濠憮貲擊 儅撩п 
    唸婁蒂 sigVal縑 轎溘и棻. 

    轎溘高縑 詭衛雖 ん裝檜 んл腎雖 彊擎 牖熱и 瞪濠 憮貲 л熱檜棻.
        
    <SSA縑憮 雖錳腎朝 憲堅葬闈 薑爾>

    sigAlg : KCDSA, DSA, RSA (ssa.h曖 SSA_SUPPORT_PUBLIC_KEY_ALG 霤褻)
    hashAlg: HAS160, SHA1, MD5 (ssa.h曖 SSA_SUPPORT_HASH_ENCRYPTION_ALG 霤褻)

	  @param certBuf      [out] 憮貲辨 檣隸憮 
    @param sigVal       [out] 儅撩脹 瞪濠憮貲高檜 高檜 轎溘腆 幗ぷ 
    @param sigValLen    [out] 儅撩脹 瞪濠憮貲高 sigVal曖 夥檜お 欽嬪 望檜
    @param sigValMaxLen [in]  sigVal 幗ぷ曖 譆渠 望檜 
    @param message      [in]  瞪濠憮貲й 等檜攪曖 殮溘 幗ぷ
    @param messageLen   [in]  瞪濠憮貲й 等檜攪曖 夥檜お 欽嬪 望檜
    
    @return SSA_ERRORS
    
    @see BG_SSA_SG_VerifySigVal BG_SSA_SG_Sign BG_SSA_SG_Verify
    */

DSS BOOL DSS_SigVal (char    *certBuf,
										 int     *certBufLen,
										 int      certBufMaxLen,
						 			   void    *sigVal,
										 int     *sigValLen,
										 int      sigValMaxLen,
										 void    *message,
										 int      messageLen);

DSS BOOL DSS_SigValSelf(OUT void *sigVal,
 							          OUT   int  *sigValLen,
							          const int   sigValMaxLen,
							          const void *message,
							          const int   messageLen,
                        const char *pszSigKeyName,
                        const char *password);

/** DSS_VerifySigVal 式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
    @ingroup SSA_SG
    @brief 瞪濠 憮貲 匐隸 л熱(No Message Format)
    
    瞪濠 憮貲高 sigVal婁 錳僥 message蒂 殮溘 嫡嬴 cert縑 んл腎橫 氈朝 奢偃酈煎 <br>
    瞪濠憮貲高擊 匐隸ж堅 匐隸 唸婁蒂 葬欐и棻. 

    殮溘高縑 詭衛雖 ん裝檜 んл腎雖 彊擎 牖熱и 瞪濠憮貲高 匐隸 л熱檜棻.
    
    檜 匐隸л熱縑憮朝 檣隸憮 匐隸擎 雖錳ж雖 彊朝棻.(檣隸憮 匐隸擎 ssa_check.h蒂 霤褻.)

    @param sigVal     [in] 匐隸й 瞪濠憮貲高曖 幗ぷ 
    @param sigValLen  [in] sigVal曖 夥檜お 欽嬪 望檜
    @param message    [in] 錳僥 等檜攪曖 殮溘 幗ぷ
    @param messageLen [in] message曖 夥檜お 欽嬪 望檜
    @param certBuf    [in] 檣隸憮 幗ぷ
    
    @return SSA_ERRORS
    
    @see BG_SSA_SG_GenSigVal BG_SSA_SG_Sign BG_SSA_SG_Verify
*/    

DSS BOOL DSS_VerifySigVal (void       *sigVal,
													 int         sigValLen,
													 void       *message,
													 int         messageLen,
													 const char *certBuf,
													 int         certBufLen,
													 const char *paramBuf    = NULL,
													 int         paramBufLen = 0);



DSS BOOL DSS_VerifySigValSelf (const void *sigVal,
										           const int   sigValLen,
											         const char *certBuf,
											         const int   certBufLen);

// 憮貲 檣隸憮曖 keyName擊 橢橫螞棻
// ISSAC-File 餌辨濠陛 嬴棲塭賊  ISign煎斜檣 餌辨濠曖 高擊 陛螳螞棻.

DSS BOOL DSS_GetSigKeyPathName(OUT char *pszKeyPath,IN const int keyPathAlloc);


//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
// Func   :  DSS_CheckCardInsert
// Desc   :  card陛 葬渦晦縑 氈朝雖 匐餌.
// Parm   :  
// return :  1    = 饜贖 Inserted
//           0    = 饜贖 removed
//           405  = 饜贖葬渦 open error  
//           else = 斜 諼 縑楝
//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
//DSS INT  DSS_CheckCardInsert(void);
//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
// Func   :  DSS_IsIFLogon
// Desc   :  衛蝶蠱 煎斜螞 顫殮擊 橢橫鹵
//           ms-logon 檣雖 issac-file logon檣雖 憲嬴魚棻. 
// Parm   :  
// return :  0    = IF煎斜螞
//           1    = MS煎斜螞
//           3    = func縑楝
//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式

DSS INT DSS_IsIFLogon(void);

//旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬
//早                                                                              早
//早                          JNI 煎 椰ё脹 API                                   早
//早  2004. 08.23 梯鼻з                                                          早
//早                                                                              早
//早  1.  IF_CheckCardInsert                                                      早
//早  2.  IF_GetLogonType                                                         早
//早  3.  IF_VerifyUserFromTMAX                                                   早
//早  4.  IF_GetEmpInfoFromTMAX                                                   早
//曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭

//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
// Func   :  DSS_CheckCard
// Desc   :  card陛 葬渦晦縑 氈朝雖 匐餌.
// Parm   :  
// return :  0    = 饜贖 Inserted
//           1    = 饜贖 removed
//           405  = 饜贖葬渦 open error  
//           else = 斜 諼 縑楝
//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式

DSS INT  DSS_CheckCard(void);


//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
// Func   :  DSS_GetSSOStatus
// Desc   :  SSO Login 顫殮擊 憲嬴魚棻.
// Parm   :  
// return :  0    = ISSAC-File Logined - ISSAC-File曖 濠翕煎斜檣 晦棟戲煎 煎斜檣
//                                       и 唳辦
//           1    = OAC Logined - 螞塭檣 檣隸撫攪縑憮 嫦晝嫡嬴 ISign Desktop戲煎 
//                                煎斜檣 и 唳辦
//           2    = Logouted - 
//           3    = ISign not installed
//           4    = �秣瞍麥� 縑楝 (溯雖蝶お葬)
//           5    = UNKNOWN_ERR
//           203  = 塭檜粽楝葬蒂 煎萄й 熱 橈蝗棲棻
//           204  = л熱蒂 ��轎й 熱 橈蝗棲棻
//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式

DSS INT DSS_GetSSOStatus (void);


//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
// Func   :  DSS_VerifyEmp
// Desc   :  TMAX蒂 檜辨и 雖薑脹 憮幗煎 睡攪 餌辨濠 檣隸擊 �挫� 嫡朝棻.
//           TMAX 憮幗 撲薑擎 tmax.env蒂 檜辨ж紫煙 и棻(logagt縑憮 餌辨)
// Parm   :  pResult        [out] 檣隸 唸婁
//           pszEmpNum      [out] 霜錳 廓��
//           pEmpNumLen     [in]  pszEmpNum曖 幗ぷ觼晦
//                          [out] 橢橫螞 霜錳廓��曖 夥檜お 欽嬪 望檜 
//           pszEmpName     [out] 霜錳 檜葷
//           prEmpNameLen   [in]  pszEmpNum曖 幗ぷ觼晦
//                          [out] 橢橫螞 霜錳檜葷曖 夥檜お 欽嬪 望檜 
// return :  rResult = 
//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式

DSS BOOL DSS_VerifyEmp(INT   *pResult, 
											 TCHAR *pszEmpNum, 
											 INT   *pEmpNumLen,
											 TCHAR *pszEmpName,
											 INT   *pEmpNameLen);

//旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬
//早                                                                              早
//早                          DSS_VerifyEmp	    		                              早
//早  2004. 08.23 梯鼻з                                                          早
//早                                                                              早
//早  1.  殮溘高 褻餌				                                                      早
//早  2.  SSO縑 煎斜檣 鼻鷓檣雖 褻餌                                              早
//早  3.  瞪歎й ぬ韃 掘ж晦 (CN,Serial)                                          早
//早  4.  TMAX 撲薑							                                                  早
//早  5.  send    							                                                  早
//早  6.  receive 							                                                  早
//早  7.  唸婁高 return 				                                                  早
//曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭

DSS INT DSS_VerifyEmp(INT   *pResult,							
                      TCHAR *pszEmpNum, 	
                      INT   *pEmpNumLen,
                      TCHAR *pszEmpName,	
                      INT   *pEmpNameLen);

//旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬
//早                                                                              早
//早                          DSS_GetSSOStatus	                                  早
//早  2004. 08.22 梯鼻з                                                          早
//早                                                                              早
//早  1.  衛蝶蠱縑 MS煎 煎斜檣 ц朝雖, IF煎 煎斜檣 ц朝雖 憲嬴魚棻                早
//早  2.  SSO縑 煎斜檣 ц朝雖 憲嬴魚棻                                            早
//早  3.  唸婁                                                                    早
//曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭

DSS INT DSS_GetSSOStatus (void);

//旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬
//早                                                                              早
//早                          DSS_CheckCard   		                                早
//早  2004. 08.22 梯鼻з                                                          早
//早                                                                              早
//早  蝶葆お饜贖曖 鳶殮罹睡蒂 憲嬴魚棻.                                           早
//早                                                                              早
//早                                                                              早
//早  return value :  0  = card Inserted                                          早
//早                  1  = card removed                                           早
//早                  IDN_ERR_CODE_405  = 饜贖葬渦 open error 								    早
//早                  SspMod_CONTEXT_NULL                                         早
//曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭

DSS INT DSS_CheckCard(void);

//--------------------------------------------------------------------------
// 2006.11.24

DSS BOOL DSS_GetUserImagePathCheckDownLoad(IN  LPCTSTR lpcszDN, 
                                           OUT LPTSTR  lpszPath, 
                                           IN  UINT    nBufLen);
                                           
DSS BOOL DSS_HttpDownLoad(IN     LPCTSTR lpcszURL,
                          IN     LPCTSTR lpcszEmpNum, 
                          IN OUT LPTSTR  lpszSavePath, 
                          IN     UINT    nBufLen);

DSS BOOL DSS_HttpCon_DataDownLoad(IN  LPCTSTR lpcszURL, 
                                  OUT LPCTSTR lpcszSavePath);

DSS BOOL DSS_GetRegImageDirectory(OUT LPTSTR lpszPath);

DSS BOOL DSS_GetRegUserImagePath(IN  LPCTSTR lpcszDN, 
                                 OUT LPTSTR lpszImagePath);

DSS BOOL DSS_GetRegEmployeeNumber(IN  LPCTSTR lpcszDN, 
                                  OUT LPTSTR  lpszEmpNum);

DSS BOOL DSS_GetLDAPEmployeeNumber(IN  LPCTSTR lpcszDN, 
                                   OUT LPTSTR  lpszEmpNum, 
                                   OUT UINT    *nEmpNumLen, 
                                   IN  UINT    nEmpNumSize);

DSS BOOL DSS_SetRegUserMap(IN HKEY    hOpenKey, 
                           IN LPCTSTR lpcszDN, 
                           IN LPCTSTR lpcszData,
                           IN LPCTSTR lpcszValue);

DSS BOOL DSS_GetRegDefaultImage(OUT LPTSTR lpszPath,
                                IN  DWORD  cbBufSzie);

DSS BOOL DSS_DeleteUserImageInfo(IN LPCTSTR lpcszDN, 
                                 IN LPCTSTR lpcszFileName);

DSS BOOL DSS_GetVersion(OUT LPTSTR lpszVersion, 
                        IN  DWORD cbBufSize);

DSS INT DSS_GetGroupAdmin(IN LPCTSTR lpcszDN);

DSS INT DSS_GetGroup(IN LPCTSTR lpcszDN);

//----------------------------------------------------------------------
// 2006.11.24 歜謙僥 (濛撩濠 : 梯繹掏)
// SendLogTmax
DSS BOOL DSS_SendLog(CHAR level, 
                     CHAR appCode, 
                     INT  errCode, 
                     CHAR *errString,
                     INT  logType,
                     BOOL useMutex = TRUE);


DSS BOOL DSS_WriteLog(CHAR *msgID, 
											UINT logCode, 
											CHAR level, 
											CHAR *disc, 
											BOOL bDirectSend, 
											int* nOutError);
//----------------------------------------------------------------------
// 2006.12.29 �姦凶�
//雖僥檣隸

#define DSS_FAILED 80000


#define INIT MyDestroy __mydestory; \
        if(__mydestory.m_result==-1) \
          return DSS_FAILED


#define OPEN MyOpen __myopen;\
        if(__myopen.m_result==-1) \
          return DSS_FAILED


extern int g_resource;
extern char g_errorstr[1024];
extern int g_select_device_id;
extern bool isInit;
extern HWND g_hparentwnd;
extern TCHAR g_payloadData[2048];


long WriteFIRToScard(PBYTE pBinaryStream, DWORD dwStreamLength);

long ReadFIRFromScard(PBYTE pBuf, DWORD dwBufLen, DWORD *dwReadLen);




typedef struct _DSS_FP_ENUMDEVICE_INFO
{
  int device_id;//蛤夥檜蝶 嬴檜蛤
  char device_name[256];// 蛤夥檜蝶 檜葷
}DSS_FP_ENUMDEVICE_INFO;
// 蛤夥檜蝶 濰纂蒂 陛螳螃晦 嬪и 掘褻羹 殮棲棻.


DSS int DSS_FP_Enroll_Stream(char** outstream,int *len);
DSS int DSS_FP_Enroll_Stream_Write(char* block,int len,char* payload);



/**     
    2008.10.24
    薑翱遵
    雖薑и 葬渦晦縑 雖僥薑爾蒂 殮溘ж晦 
    晦襄縑 氈湍 л熱菟擊 葬渦晦 檜葷擊 嫡啪莠 ж罹 熱薑п憮 蹺陛ж紫煙 и棻.
*/
DSS int DSS_FP_Enroll_StreamEx(char** outstream,int *len, char* readername);
DSS int DSS_FP_Enroll_Stream_WriteEx(char* block,int len,char* payload, char* readername);
long WriteFIRToScardEx(PBYTE pBinaryStream, DWORD dwStreamLength, char* readername);
long ReadFIRFromScardEx(PBYTE pBuf, DWORD dwBufLen, DWORD *dwReadLen, char* readername);
DSS int DSS_FP_EnrollEx(TCHAR * strpayload=NULL, char *readername=NULL);
DSS int __stdcall DSS_FP_EnrollStdEx(TCHAR * strpayload=NULL, char *readername=NULL);
DSS int DSS_FP_VerifyEx(TCHAR ** strpayload=NULL, char *readername=NULL);
DSS int __stdcall  DSS_FP_VerifyStdEx(TCHAR ** strpayload=NULL, char *readername=NULL);
DSS int DSS_FP_ChangePayloadEx(TCHAR *strpayload,bool flag=true, char *readername=NULL);
DSS int __stdcall DSS_FP_ChangePayloadStdEx(TCHAR *strpayload,bool flag=true, char *readername=NULL);
long DSS_FP_CheckScardEx(char *readername);
DSS int DSS_FP_CheckCardFingerEx(char *readername);
DSS int __stdcall DSS_FP_CheckCardFingerStdEx(char *readername);




DSS int DSS_FP_Capture(char** outstream, int *len);
DSS int DSS_FP_CaptureBase64(char* outBuf, const int outBufSize);
DSS int __stdcall DSS_FP_CaptureBase64Std(char* outBuf, const int outBufSize);
DSS int DSS_FP_CapturedVerify(BYTE *byteData, int dwReadLen);

// 20080415 梯繹掏 衛濛
// DSS_FP_VerifyWithICSл熱朝 頂睡瞳戲煎 DSS_FP_Initialize, DSS_FP_Destroy蒂 ��轎м棲棻.
DSS int DSS_FP_VerifyWithICS(int *errCode, char* errMsg, char *name, char *resid_hmac, char *empNum, int onlyICS);
DSS int __stdcall DSS_FP_VerifyWithICSStd(int *errCode, char* errMsg, char *name, char *resid_hmac, char *empNum, int onlyICS);
// 20080415 梯繹掏 部

DSS int DSS_FP_Enroll(TCHAR * strpayload=NULL);
DSS int __stdcall DSS_FP_EnrollStd(TCHAR * strpayload=NULL);
//雖僥擊 蛔煙й陽 餌辨ж賊 腌棲棻.
  //payload陛 氈戲貊 strpayload縑 厥橫憮 爾頂賊 腌棲棻.



DSS int DSS_FP_Verify(TCHAR ** strpayload=NULL);
DSS int __stdcall  DSS_FP_VerifyStd(TCHAR ** strpayload=NULL);
//雖僥 檣醞擊 衛紫ж貊 
// 檣隸 撩奢衛 strpayload縑 payload高擊 厥蝗棲棻. NULL橾陽朝 彊厥蝗棲棻.
// 輿模高擊 厥橫 輿賊 詭賅葬蒂 й渡п憮 厥橫鄹棲棻. 餌辨濠陛 憲嬴憮 詭賅葬蒂 п薯擁撿 м棲棻.
//stl string 檜釭 CString 戲煎 ж堅 談戲賊 離�� 熱薑ж紫煙 ж雖蹂


DSS int DSS_FP_GetControlUnitTime(int *npStartTick, int *npCapture_StartTick, int *npCapture_EndTick);

DSS int DSS_FP_SetEnrollSecurityLevel(unsigned int secuLevel);
DSS int DSS_FP_SetVerifySecurityLevel(unsigned int secuLevel);
DSS int DSS_FP_GetEnrollSecurityLevel(unsigned int *nEnrollLevel);
DSS int DSS_FP_GetVerifySecurityLevel(unsigned int *nVerifyLevel);

DSS int DSS_FP_ChangePayload(TCHAR *strpayload,bool flag=true);
DSS int __stdcall DSS_FP_ChangePayloadStd(TCHAR *strpayload,bool flag=true);

//flag 陛 false 檜賊 檣隸璽檜 嗑雖 彊朝棻. flag陛 true賊 檣隸璽檜 嗤棻.
//payload高擊 滲唳й陽 餌辨ж貊 strpayload縑 高戲煎 payload 高擊 滲唳м棲棻.



// 20070903 歜謙僥
DSS int DSS_FP_InitializeEx(HWND hwnd,int skinflag=0,int libflag=0);
DSS int DSS_FP_Initialize(HWND hwnd,int skinflag=0,int libflag=0);
DSS int __stdcall  DSS_FP_InitializeStd(HWND hwnd,int skinflag=0,int libflag=0);
//蟾晦�� л熱 檜貊 譆蟾 и廓虜 ��轎ж賊 腌棲棻.
//skinflag 蝶鑑擊 夥羞棻. 0檜賊 �盛搎� 1檜賊 羶煙儀檜棻.
//libflag 餌辨ж朝 塭檜粽楝葬蒂 夥羞棻. 0檜賊 棲お薇 1檜賊 BioApi檜棻.




DSS int DSS_FP_CheckCardFinger();
DSS int __stdcall DSS_FP_CheckCardFingerStd();


DSS int DSS_FP_CardClear();
DSS int __stdcall DSS_FP_CardClearStd();

DSS void DSS_FP_Destroy();
DSS void __stdcall  DSS_FP_DestroyStd();

DSS LPCSTR DSS_FP_GetErrorStr();
DSS LPCSTR __stdcall DSS_FP_GetErrorStrStd();


DSS int DSS_FP_GetErrorCode();
DSS int __stdcall DSS_FP_GetErrorStrCode();


////////////////////////////////////////////////////////


long DSS_FP_CheckScard();

void DSS_FP_CreateAnimationCtrl();
void DSS_FP_CloseAnimationCtrl();
void DSS_FP_PlayAnimationCtrl(LPCSTR str=NULL);
void DSS_FP_StopAnimationCtrl();



extern HANDLE g_threadid;
extern HWND g_hwndDlg;


class CBioApiObject;
extern CBioApiObject *g_bioobject;



class CLog
{
private:

  FILE *m_file;
public:

  CLog()
  {
  }

  CLog(int a)
  {
   
    char buffer[50];
    m_file=fopen("c:\\dss.txt","a+");

    sprintf(buffer,"蟾晦�� 蘋遴攪:%d",a);
    fwrite(buffer,strlen(buffer),1,m_file);
    fwrite("\r\n",strlen("\r\n"),1,m_file);
  }

  CLog(char *str)
  {

    m_file=fopen("c:\\dss.txt","a+");

    fwrite(str,strlen(str),1,m_file);
    fwrite("\r\n",strlen("\r\n"),1,m_file);
  }

  ~CLog()
  {

    fclose(m_file);
  }

};


/* *******************************************************************

	SCM縑憮 雖僥蛔煙擊 п撿й 衛,
	SCM詭景曖 爾寰饜贖, 爾寰蘋萄 塭蛤螃 幗が婁 鼻婦橈檜 
	issac-file縑憮 煎斜檣 и 爾寰 衙羹蒂 檗朝 梱殼戲煎,

	SspMod_open-> OpenbyReaderName擊 餌辨ж晦 嬪п
	檣濠蒂 嫡晦 嬪ж罹 棻擠婁 偽擎 л熱菟擊 蹺陛 濛撩ж艘蝗棲棻.

	2008.10.02 檜渠撥

	* DSS_FP_VerifyEx
	* DSS_FP_Enroll_StreamEx
	* DSS_FP_Enroll_Stream_WriteEx
	* DSS_FP_EnrollEx
	* DSS_FP_CheckCardFingerEx
	* DSS_FP_ChangePayloadEx

	蹺陛 檣濠朝 integer 陛 ж釭 菴縑 稱蝗棲棻. 
	≦ 蹺�� character pointer煎	熱薑腆 蕨薑
	
 ******************************************************************* */


//

#define LOG(s) CLog c(s)


class CBioApiObject
{
  
protected:
  int m_resource;
  int m_init;
public:
  
public:
  CBioApiObject()
  {
    m_init=0;
  }
  
  virtual int DSS_FP_Init()=0;
  virtual void DSS_FP_Destroy_nBio()=0;
  virtual int DSS_FP_CheckCardFinger()=0;
	virtual int DSS_FP_CheckCardFingerEx(char* readername)=0;
	virtual int DSS_FP_GetControlUnitTime(int *npStartTick, int *npCapture_StartTick, int *npCapture_EndTick)=0;
	virtual int DSS_FP_SetEnrollSecurityLevel(unsigned int secuLevel)=0;
	virtual int DSS_FP_SetVerifySecurityLevel(unsigned int secuLevel)=0;
  virtual int DSS_FP_Enroll(TCHAR * strpayload)=0;
	virtual int DSS_FP_EnrollEx(TCHAR * strpayload,char* readername)=0;
  virtual int DSS_FP_EnumDevice(DSS_FP_ENUMDEVICE_INFO **device_list)=0;
  virtual int DSS_FP_Initialize(HWND hwnd,int flag);
  virtual int DSS_FP_Verify(TCHAR ** strpayload)=0;
	virtual int DSS_FP_VerifyEx(TCHAR ** strpayload, char* readername)=0;
  virtual int DSS_FP_ChangePayload(TCHAR *strPayload,bool flag)=0;
	virtual int DSS_FP_ChangePayloadEx(TCHAR *strPayload,bool flag, char* readername)=0;
  virtual int DeviceOpen()=0;
  virtual int DeviceClose()=0;
  virtual int DSS_FP_Enroll_Stream(char**,int*)=0;
  virtual int DSS_FP_Enroll_Stream_Write(char* btTmpBuf,int len,char *ppayload)=0;
	virtual int DSS_FP_Enroll_StreamEx(char**,int*,char*)=0;
  virtual int DSS_FP_Enroll_Stream_WriteEx(char* btTmpBuf,int len,char *ppayload,char* readername)=0;
	virtual int DSS_FP_Capture(char**,int*)=0;
	virtual int DSS_FP_CapturedVerify(BYTE*, int)=0;
  
public:
  virtual void DSS_FP_Destroy();
  void DSS_FP_Destroy_Object();
  void Error(int );
  
};

//----------------------------------------------------------------------


//----------------------------------------------------------------------


extern DssFpError g_fperror;



#ifdef _DEBUG
#define LOGPRINT(a,b)   { \
                        const char *sp=g_fperror.GetErrorStr(b);\
                        if(sp==NULL) sp=a;\
                        memcpy(g_errorstr,sp,strlen(sp) );\
                        memcpy(g_errorstr+strlen(sp)," (DestSecs.dll)",16);\
                        }

/*
#define LOGPRINT(a,b)   { \
														char msg[512] = {0,};\
														sprintf(msg,"%s : %d",a,b);\
														LOG(msg);\
												}
*/
#else
#define LOGPRINT(a,b)   { \
                            const char *sp=g_fperror.GetErrorStr(b);\
                            if(sp==NULL) sp=a;\
                            memcpy(g_errorstr,sp,strlen(sp) );\
                        }

#endif






#ifdef __cplusplus
}
#endif 
