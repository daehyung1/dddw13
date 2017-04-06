

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
    long    time;      //나중에 이값은 localtime()를 호출해서 display할수있다.
  }IFDNLIST, FAR *LPIFDNLIST;
  
  
  typedef struct tagIFFILELIST
  {
    INT			nSucc;
    TCHAR		szSrcName[MAX_PATH]; // ★★★ 전자 서명시 반드시 fullpath로 넘어와야 한다.
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



/** DSS_SigVal ──────────────────────────────────
    @ingroup SSA_SG
    @brief 전자 서명 생성 함수(No Message Format)
    
    message를 입력으로 받아 cnk에 포함되어 있는 비공개키로 전자서명을 생성해 
    결과를 sigVal에 출력한다. 

    출력값에 메시지 포맷이 포함되지 않은 순수한 전자 서명 함수이다.
        
    <SSA에서 지원되는 알고리즘 정보>

    sigAlg : KCDSA, DSA, RSA (ssa.h의 SSA_SUPPORT_PUBLIC_KEY_ALG 참조)
    hashAlg: HAS160, SHA1, MD5 (ssa.h의 SSA_SUPPORT_HASH_ENCRYPTION_ALG 참조)

	  @param certBuf      [out] 서명용 인증서 
    @param sigVal       [out] 생성된 전자서명값이 값이 출력될 버퍼 
    @param sigValLen    [out] 생성된 전자서명값 sigVal의 바이트 단위 길이
    @param sigValMaxLen [in]  sigVal 버퍼의 최대 길이 
    @param message      [in]  전자서명할 데이터의 입력 버퍼
    @param messageLen   [in]  전자서명할 데이터의 바이트 단위 길이
    
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

/** DSS_VerifySigVal ──────────────────────────────
    @ingroup SSA_SG
    @brief 전자 서명 검증 함수(No Message Format)
    
    전자 서명값 sigVal과 원문 message를 입력 받아 cert에 포함되어 있는 공개키로 <br>
    전자서명값을 검증하고 검증 결과를 리턴한다. 

    입력값에 메시지 포맷이 포함되지 않은 순수한 전자서명값 검증 함수이다.
    
    이 검증함수에서는 인증서 검증은 지원하지 않는다.(인증서 검증은 ssa_check.h를 참조.)

    @param sigVal     [in] 검증할 전자서명값의 버퍼 
    @param sigValLen  [in] sigVal의 바이트 단위 길이
    @param message    [in] 원문 데이터의 입력 버퍼
    @param messageLen [in] message의 바이트 단위 길이
    @param certBuf    [in] 인증서 버퍼
    
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

// 서명 인증서의 keyName을 얻어온다
// ISSAC-File 사용자가 아니라면  ISign로그인 사용자의 값을 가져온다.

DSS BOOL DSS_GetSigKeyPathName(OUT char *pszKeyPath,IN const int keyPathAlloc);


//───────────────────────────────────────
// Func   :  DSS_CheckCardInsert
// Desc   :  card가 리더기에 있는지 검사.
// Parm   :  
// return :  1    = 토큰 Inserted
//           0    = 토큰 removed
//           405  = 토큰리더 open error  
//           else = 그 외 에러
//───────────────────────────────────────
//DSS INT  DSS_CheckCardInsert(void);
//───────────────────────────────────────
// Func   :  DSS_IsIFLogon
// Desc   :  시스템 로그온 타입을 얻어냄
//           ms-logon 인지 issac-file logon인지 알아낸다. 
// Parm   :  
// return :  0    = IF로그온
//           1    = MS로그온
//           3    = func에러
//───────────────────────────────────────

DSS INT DSS_IsIFLogon(void);

//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
//┃                                                                              ┃
//┃                          JNI 로 랩핑된 API                                   ┃
//┃  2004. 08.23 김상학                                                          ┃
//┃                                                                              ┃
//┃  1.  IF_CheckCardInsert                                                      ┃
//┃  2.  IF_GetLogonType                                                         ┃
//┃  3.  IF_VerifyUserFromTMAX                                                   ┃
//┃  4.  IF_GetEmpInfoFromTMAX                                                   ┃
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

//───────────────────────────────────────
// Func   :  DSS_CheckCard
// Desc   :  card가 리더기에 있는지 검사.
// Parm   :  
// return :  0    = 토큰 Inserted
//           1    = 토큰 removed
//           405  = 토큰리더 open error  
//           else = 그 외 에러
//───────────────────────────────────────

DSS INT  DSS_CheckCard(void);


//───────────────────────────────────────
// Func   :  DSS_GetSSOStatus
// Desc   :  SSO Login 타입을 알아낸다.
// Parm   :  
// return :  0    = ISSAC-File Logined - ISSAC-File의 자동로그인 기능으로 로그인
//                                       한 경우
//           1    = OAC Logined - 온라인 인증센터에서 발급받아 ISign Desktop으로 
//                                로그인 한 경우
//           2    = Logouted - 
//           3    = ISign not installed
//           4    = 환경설정 에러 (레지스트리)
//           5    = UNKNOWN_ERR
//           203  = 라이브러리를 로드할 수 없습니다
//           204  = 함수를 호출할 수 없습니다
//───────────────────────────────────────

DSS INT DSS_GetSSOStatus (void);


//───────────────────────────────────────
// Func   :  DSS_VerifyEmp
// Desc   :  TMAX를 이용한 지정된 서버로 부터 사용자 인증을 확인 받는다.
//           TMAX 서버 설정은 tmax.env를 이용하도록 한다(logagt에서 사용)
// Parm   :  pResult        [out] 인증 결과
//           pszEmpNum      [out] 직원 번호
//           pEmpNumLen     [in]  pszEmpNum의 버퍼크기
//                          [out] 얻어온 직원번호의 바이트 단위 길이 
//           pszEmpName     [out] 직원 이름
//           prEmpNameLen   [in]  pszEmpNum의 버퍼크기
//                          [out] 얻어온 직원이름의 바이트 단위 길이 
// return :  rResult = 
//───────────────────────────────────────

DSS BOOL DSS_VerifyEmp(INT   *pResult, 
											 TCHAR *pszEmpNum, 
											 INT   *pEmpNumLen,
											 TCHAR *pszEmpName,
											 INT   *pEmpNameLen);

//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
//┃                                                                              ┃
//┃                          DSS_VerifyEmp	    		                              ┃
//┃  2004. 08.23 김상학                                                          ┃
//┃                                                                              ┃
//┃  1.  입력값 조사				                                                      ┃
//┃  2.  SSO에 로그인 상태인지 조사                                              ┃
//┃  3.  전송할 패킷 구하기 (CN,Serial)                                          ┃
//┃  4.  TMAX 설정							                                                  ┃
//┃  5.  send    							                                                  ┃
//┃  6.  receive 							                                                  ┃
//┃  7.  결과값 return 				                                                  ┃
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

DSS INT DSS_VerifyEmp(INT   *pResult,							
                      TCHAR *pszEmpNum, 	
                      INT   *pEmpNumLen,
                      TCHAR *pszEmpName,	
                      INT   *pEmpNameLen);

//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
//┃                                                                              ┃
//┃                          DSS_GetSSOStatus	                                  ┃
//┃  2004. 08.22 김상학                                                          ┃
//┃                                                                              ┃
//┃  1.  시스템에 MS로 로그인 했는지, IF로 로그인 했는지 알아낸다                ┃
//┃  2.  SSO에 로그인 했는지 알아낸다                                            ┃
//┃  3.  결과                                                                    ┃
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

DSS INT DSS_GetSSOStatus (void);

//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
//┃                                                                              ┃
//┃                          DSS_CheckCard   		                                ┃
//┃  2004. 08.22 김상학                                                          ┃
//┃                                                                              ┃
//┃  스마트토큰의 삽입여부를 알아낸다.                                           ┃
//┃                                                                              ┃
//┃                                                                              ┃
//┃  return value :  0  = card Inserted                                          ┃
//┃                  1  = card removed                                           ┃
//┃                  IDN_ERR_CODE_405  = 토큰리더 open error 								    ┃
//┃                  SspMod_CONTEXT_NULL                                         ┃
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

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
// 2006.11.24 임종문 (작성자 : 김철권)
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
// 2006.12.29 홍정우
//지문인증

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
  int device_id;//디바이스 아이디
  char device_name[256];// 디바이스 이름
}DSS_FP_ENUMDEVICE_INFO;
// 디바이스 장치를 가져오기 위한 구조체 입니다.


DSS int DSS_FP_Enroll_Stream(char** outstream,int *len);
DSS int DSS_FP_Enroll_Stream_Write(char* block,int len,char* payload);



/**     
    2008.10.24
    정연욱
    지정한 리더기에 지문정보를 입력하기 
    기존에 있던 함수들을 리더기 이름을 받게끔 하여 수정해서 추가하도록 한다.
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

// 20080415 김철권 시작
// DSS_FP_VerifyWithICS함수는 내부적으로 DSS_FP_Initialize, DSS_FP_Destroy를 호출합니다.
DSS int DSS_FP_VerifyWithICS(int *errCode, char* errMsg, char *name, char *resid_hmac, char *empNum, int onlyICS);
DSS int __stdcall DSS_FP_VerifyWithICSStd(int *errCode, char* errMsg, char *name, char *resid_hmac, char *empNum, int onlyICS);
// 20080415 김철권 끝

DSS int DSS_FP_Enroll(TCHAR * strpayload=NULL);
DSS int __stdcall DSS_FP_EnrollStd(TCHAR * strpayload=NULL);
//지문을 등록할때 사용하면 됩니다.
  //payload가 있으며 strpayload에 넣어서 보내면 됩니다.



DSS int DSS_FP_Verify(TCHAR ** strpayload=NULL);
DSS int __stdcall  DSS_FP_VerifyStd(TCHAR ** strpayload=NULL);
//지문 인중을 시도하며 
// 인증 성공시 strpayload에 payload값을 넣습니다. NULL일때는 않넣습니다.
// 주소값을 넣어 주면 메모리를 할당해서 넣어줍니다. 사용자가 알아서 메모리를 해제애야 합니다.
//stl string 이나 CString 으로 하고 싶으면 차후 수정하도록 하지요


DSS int DSS_FP_GetControlUnitTime(int *npStartTick, int *npCapture_StartTick, int *npCapture_EndTick);

DSS int DSS_FP_SetEnrollSecurityLevel(unsigned int secuLevel);
DSS int DSS_FP_SetVerifySecurityLevel(unsigned int secuLevel);
DSS int DSS_FP_GetEnrollSecurityLevel(unsigned int *nEnrollLevel);
DSS int DSS_FP_GetVerifySecurityLevel(unsigned int *nVerifyLevel);

DSS int DSS_FP_ChangePayload(TCHAR *strpayload,bool flag=true);
DSS int __stdcall DSS_FP_ChangePayloadStd(TCHAR *strpayload,bool flag=true);

//flag 가 false 이면 인증창이 뜨지 않는다. flag가 true면 인증창이 뜬다.
//payload값을 변경할때 사용하며 strpayload에 값으로 payload 값을 변경합니다.



// 20070903 임종문
DSS int DSS_FP_InitializeEx(HWND hwnd,int skinflag=0,int libflag=0);
DSS int DSS_FP_Initialize(HWND hwnd,int skinflag=0,int libflag=0);
DSS int __stdcall  DSS_FP_InitializeStd(HWND hwnd,int skinflag=0,int libflag=0);
//초기화 함수 이며 최초 한번만 호출하면 됩니다.
//skinflag 스킨을 바꾼다. 0이면 황금색 1이면 청록색이다.
//libflag 사용하는 라이브러리를 바꾼다. 0이면 니트젠 1이면 BioApi이다.




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

    sprintf(buffer,"초기화 카운터:%d",a);
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

	SCM에서 지문등록을 해야할 시,
	SCM메뉴의 보안토큰, 보안카드 라디오 버튼과 상관없이 
	issac-file에서 로그인 한 보안 매체를 읽는 까닭으로,

	SspMod_open-> OpenbyReaderName을 사용하기 위해
	인자를 받기 위하여 다음과 같은 함수들을 추가 작성하였습니다.

	2008.10.02 이대섭

	* DSS_FP_VerifyEx
	* DSS_FP_Enroll_StreamEx
	* DSS_FP_Enroll_Stream_WriteEx
	* DSS_FP_EnrollEx
	* DSS_FP_CheckCardFingerEx
	* DSS_FP_ChangePayloadEx

	추가 인자는 integer 가 하나 뒤에 붙습니다. 
	※ 추후 character pointer로	수정될 예정
	
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
