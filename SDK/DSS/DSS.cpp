// DSS.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "DSS.h"
#include "MyNBioApi.h"
#include "MyBioApi.h"
#include "ISignDtpDLL.h"
#include "DllLoad.h"
#include "scmod.h"
#include "tchar.h"
#include <list>
#include <string>
#include <commctrl.h>
#include "resource.h"
#include <process.h>
#include "mydestroy.h"
#include "DssFpError.h"
#include "base64.h"
#include <assert.h>
#include "..\..\util\common\ifgetpath.h"




using namespace std;


#define DFID	"\xB7\x00"
#define DFID_FINGER_FLD	"\xB7\x15"


#define CERT_STATUS_GOOD    (0x00)
#define CERT_STATUS_REVOKE  (0x01)
#define CERT_STATUS_UNKNOWN (0x02)

#define CERT_PERIOD_VALID      (0x00)
#define CERT_PERIOD_NOTVALID   (0x01)

#define STATUS_GOOD_AND_PERIOD_VALID      (0x00)
#define STATUS_GOOD_AND_PERIOD_NOTVALID   (0x01)
#define STATUS_REVOKE_AND_PERIOD_VALID    (0x02)
#define STATUS_REVOKE_AND_PERIOD_NOTVALID (0x03)

#define RET_RECV_ERROR         100

HWND g_hwndAnim;
HANDLE g_instance;
HWND g_hwndDlg=NULL;
HWND g_hparentwnd=NULL;
TCHAR g_payloadData[2048];
DssFpError g_fperror;





char g_textMsg[512]= {0,};
bool isInit=false;
#define UM_SETTEXT WM_USER+100
#define UM_DESTROY WM_USER+101


HANDLE g_threadid=0;
CBioApiObject *g_bioobject=NULL;

BOOL g_bDirectDisplay = FALSE; // 20070831 김철권

void LoadControlImage(HINSTANCE hInstance);
void DeleteControlImage();

CNBioApi g_nbioapi;
CMyBioApi g_mybioapi;

LRESULT CALLBACK DSS_FP_PROC(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);


BOOL APIENTRY DllMain( HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved )
{


  switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
       
      g_instance=hModule;
			LoadControlImage((HINSTANCE)g_instance);
      break;

		case DLL_THREAD_ATTACH:
      break;

    case DLL_THREAD_DETACH:
      {
        break;
      }
      
		case DLL_PROCESS_DETACH:

      if(g_bioobject)
      {
        g_bioobject->DSS_FP_Destroy_Object();
      }
			DeleteControlImage();
      
		break;
  }
  
  return TRUE;
}


// 파일 암호화/복호화 ------------------------------------------------------
BOOL DSS_EncryptFiles (IFFILELIST *pFileList, INT *pFileCnt)
{
  return IF_EncryptFiles(pFileList, pFileCnt);
}

BOOL DSS_EncryptFilesTo (IFFILELIST *pFileList, INT *pFileCnt)
{
  return IF_EncryptFilesTo(pFileList, pFileCnt);
}

BOOL DSS_EncryptAdd (LPTSTR lpszEncryptedFileName)
{
  return IF_EncryptAdd(lpszEncryptedFileName);
}

BOOL DSS_DecryptFiles (IFFILELIST *pFileList, INT	*pFileCnt)
{
  return IF_DecryptFiles(pFileList, pFileCnt);
}
//--------------------------------------------------------------------------

// 파일 서명/검증 ------------------------------------------------------
BOOL DSS_ESignFiles(LPIFFILELIST pFileList, INT *pFileCnt)
{
  return IF_ESignFiles(pFileList, pFileCnt);
}

INT  DSS_MyESignAddToESignFile(LPTSTR lpszFile)
{
  return IF_MyESignAddToESignFile(lpszFile);
}

INT  DSS_SearchMyESign(LPTSTR lpszFile)
{
  return IF_SearchMyESign(lpszFile);
}

BOOL DSS_ESignVerify(LPTSTR szSignedFileName, LPTSTR szDn)
{
  return IF_ESignVerify(szSignedFileName, szDn);
}

BOOL DSS_GetDnFromESignFile(char *lpszFileName, LPIFDNLIST pDnList, int *pDnCount)
{
  return IF_GetDnFromESignFile(lpszFileName, pDnList, pDnCount);
}
//--------------------------------------------------------------------------

BOOL DSS_ExportCnKToPfx (LPTSTR lpszFileName, LPTSTR lpszPin)
{
  return IF_ExportCnKToPfx(lpszFileName, lpszPin);
}

INT  DSS_VerifyCardPin(char *pin)
{
  return IF_VerifyCardPin(pin);
}

INT  DSS_GetLastError()
{
  return IF_GetLastError();
}

INT DSS_SetLastError(INT nErrorCode)
{
  return IF_SetLastError(nErrorCode);
}

INT DSS_OriginFile(LPTSTR lpszSource, LPTSTR lpszTarget)
{
  return IF_OriginFile(lpszSource, lpszTarget);
}

BOOL DSS_OriginFiles(LPIFFILELIST pFileList, INT *pFileCnt)
{
  return IF_OriginFiles(pFileList, pFileCnt);
}

BOOL DSS_GetUserName(char *szUserName)
{
  return IF_GetUserName(szUserName);
}

INT DSS_ChangeCardPin(LPTSTR szOldPin, LPTSTR szNewPin)
{
  return IF_ChangeCardPin(szOldPin, szNewPin);
}

INT DSS_GetUserInfoFromSC(BYTE *lpUserInfo, int cSize)
{
  return IF_GetUserInfoFromSC(lpUserInfo, cSize);
}

INT DSS_GetSubjectCnFromSC(LPTSTR sdn,int *snLen)
{
  return IF_GetSubjectCnFromSC(sdn,snLen);
}

BOOL DSS_SigVal (char *certBuf, int *certBufLen, int certBufMaxLen, void *sigVal,
									  int *sigValLen, int sigValMaxLen, void *message, int messageLen)
{
  return IF_SigVal(certBuf, certBufLen, certBufMaxLen, sigVal, sigValLen, sigValMaxLen, message, messageLen);
}

BOOL DSS_SigValSelf(OUT void *sigVal, OUT int *sigValLen, const int sigValMaxLen, const void *message, 
                       const int messageLen, const char *pszSigKeyName, const char *password)
{
  return IF_SigValSelf(sigVal, sigValLen, sigValMaxLen, message, messageLen, pszSigKeyName, password);
}

BOOL DSS_VerifySigVal (void *sigVal, int sigValLen, void *message, int messageLen, 
                          const char *certBuf, int certBufLen, const char *paramBuf, int paramBufLen)
{
  return IF_VerifySigVal(sigVal, sigValLen, message, messageLen, certBuf, certBufLen, paramBuf, paramBufLen);
}

BOOL DSS_VerifySigValSelf  (const void *sigVal, const int   sigValLen,
											         const char *certBuf, const int   certBufLen)
{
  return IF_VerifySigValSelf(sigVal, sigValLen, certBuf, certBufLen);
}

BOOL DSS_GetSigKeyPathName(OUT char *pszKeyPath,IN const int keyPathAlloc)
{
  return IF_GetSigKeyPathName(pszKeyPath, keyPathAlloc);
}

INT  DSS_CheckCardInsert(void)
{
  return IF_CheckCardInsert();
}

INT DSS_IsIFLogon(void)
{
  return IF_IsIFLogon();
}

//--------------------------------------------------------------------------
// 2006.11.24 임종문

BOOL DSS_GetUserImagePathCheckDownLoad(IN LPCTSTR lpcszDN, OUT LPTSTR lpszPath, IN UINT nBufLen)
{
  return IF_GetUserImagePathCheckDownLoad(lpcszDN, lpszPath, nBufLen);
}

BOOL DSS_HttpDownLoad(IN     LPCTSTR lpcszURL,     IN LPCTSTR lpcszEmpNum, 
                      IN OUT LPTSTR  lpszSavePath, IN UINT    nBufLen)
{
  return IF_HttpDownLoad(lpcszURL, lpcszEmpNum, lpszSavePath, nBufLen);
}

BOOL DSS_HttpCon_DataDownLoad(IN LPCTSTR lpcszURL, OUT LPCTSTR lpcszSavePath)
{
  return IF_HttpCon_DataDownLoad(lpcszURL, lpcszSavePath);
}

BOOL DSS_GetRegImageDirectory(OUT LPTSTR lpszPath)
{
  return DSS_GetRegImageDirectory(lpszPath);
}

BOOL DSS_GetRegUserImagePath(IN LPCTSTR lpcszDN, OUT LPTSTR lpszImagePath)
{
  return IF_GetRegUserImagePath(lpcszDN, lpszImagePath);
}

BOOL DSS_GetRegEmployeeNumber(IN LPCTSTR lpcszDN, OUT LPTSTR lpszEmpNum)
{
  return IF_GetRegEmployeeNumber(lpcszDN, lpszEmpNum);
}

BOOL DSS_GetLDAPEmployeeNumber(IN  LPCTSTR lpcszDN,     OUT LPTSTR lpszEmpNum,
                               OUT UINT    *nEmpNumLen, IN  UINT   nEmpNumSize)
{
  return IF_GetLDAPEmployeeNumber(lpcszDN, lpszEmpNum, nEmpNumLen, nEmpNumSize);
}

BOOL DSS_SetRegUserMap(IN HKEY hOpenKey, IN LPCTSTR lpcszDN, IN LPCTSTR lpcszData, IN LPCTSTR lpcszValue)
{
  return IF_SetRegUserMap(hOpenKey, lpcszDN, lpcszData, lpcszValue);
}

BOOL DSS_GetRegDefaultImage(OUT LPTSTR lpszPath, IN DWORD cbBufSize)
{
  return IF_GetRegDefaultImage(lpszPath, cbBufSize);
}

BOOL DSS_DeleteUserImageInfo(IN LPCTSTR lpcszDN, IN LPCTSTR lpcszFileName)
{
  return IF_DeleteUserImageInfo(lpcszDN, lpcszFileName);
}

INT DSS_GetGroupAdmin(IN LPCTSTR lpcszDN)
{
  return IF_GetGroupAdmin(lpcszDN);
}

INT DSS_GetGroup(IN LPCTSTR lpcszDN)
{
  return IF_GetGroup(lpcszDN);
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
// 2006.12.14 임종문
// SendLogTmax
BOOL DSS_SendLog( CHAR level, CHAR appCode, INT errCode, CHAR* errString, INT logType, BOOL  useMutex )
{
  return IF_SendLog( level, appCode, errCode, errString, logType, useMutex );
}


//------------------------------------------------------------------------------------------------
// 2007.7.11 임종문 (작성자 : 김철권)
// IF_WriteLog
// msgID       : 로그 식별자 다음과 같은 규칙이다.
//               -> hw.unlock.fingerprint.gina.DSP.penta
// logCode     : 로그 코드, 리턴값, 오류값등.
// level       : 로그레벨 3단계로 설정 할 수 있도록 한다.
//               -> 1단계 : 치명적 오류, 2단계 : 오류, 3단계 : 정보, 4단계 : info, 5단계 : debug
// disc        : 부가적인 설명.
// bDirectSend : 전송 방법.
// nOutError   : 반환값.
BOOL DSS_WriteLog(CHAR *msgID, UINT logCode, CHAR level, CHAR *disc, BOOL bDirectSend, int* nOutError)
{
  return IF_WriteLog(msgID, logCode, level, disc, bDirectSend, nOutError);
}

//--------------------------------------------------------------------------


//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
//┃                                                                              ┃
//┃                          DSS_VerifyEmp			                                  ┃
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
INT DSS_VerifyEmp(INT   *pResult,
	TCHAR *pszEmpNum, INT   *pEmpNumLen,
	TCHAR *pszEmpName, INT   *pEmpNameLen)
{
	// return code 
	enum {
		VE_SUCCESS = 0,
		VE_STATUS_GOOD__PERIOD_NOTVALID,
		VE_STATUS_REVOKE__PERIOD_VALID,
		VE_STATUS_REVOKE__PERIOD_NOTVALID,
		VE_LOGOUTED,
		VE_FAIL_GET_CUR_USER_CN,
		VE_FAIL_GET_CUR_USER_CERT_SERIAL,
		VE_INVALID_SERIAL,
		VE_ENV_ERR,
		VE_TMAX_CONF_ERR,
		VE_TMAX_START_ERR,
		VE_TRANSE_DATA_ERR,

		VE_NO_MATCH_CN = 101,
		VE_FAIL_PKIDB,
		VE_NO_SUCH_CERT,
		VE_NO_SUCH_EMPLOYEE,
		VE_EMPNUM_TOO_LONG,

		VE_RECV_UNKNOWN_MSG,

		VE_ISIGN_NOT_INSTALLED = 200,
		VE_ISIGN_ENV_ERROR = 201,
		VE_ISIGN_CAN_NOT_LOAD_LIBRARY = 203,
		VE_ISIGN_CAN_NOT_FIND_FUN = 221,

		VE_INVALID_INPUT = 300
		//VE_NOT_INSTALLED_,
		//VE_NOT_FOUND_FUNCTION
	};



	//---------------------------------------------------------------
  // 1 . 입력값 조사
	//---------------------------------------------------------------
	if (pszEmpNum <= 0 ||
		*pEmpNumLen <= 7 ||
		pszEmpName <= 0 ||
		*pEmpNameLen <= 5)
	{
		*pResult = VE_INVALID_INPUT;
		OutputDebugString("SSO_VerifyEmp - 입력값 조사 실패\n");
		return FAIL;
	}


	//---------------------------------------------------------------
  // 2 . ISignDtp.dll Load
	//---------------------------------------------------------------

	// 2-1. dll load
	CISignDtpDLL ISignDllOBJ;
	int ret = ISignDllOBJ.LoadDLL("isigndtp.dll");
	if (ret != SUCCESS)
	{
		if (ret == 3) {
			*pResult = VE_ISIGN_NOT_INSTALLED;
		}
		else if (ret == 4) {
			*pResult = VE_ISIGN_ENV_ERROR;
		}
		else {
			// VE_ISIGN_CAN_NOT_LOAD_LIBRARY
			// VE_ISIGN_CAN_NOT_FIND_FUN
			*pResult = ret;
		}
		OutputDebugString("SSO_VerifyEmp - ISignDtop load 실패\n");

		return FAIL;
	}

	//---------------------------------------------------------------
	// 2 . SSO에 로그인 상태인지 알아낸다
	  //---------------------------------------------------------------
	if (ISignDllOBJ.IsLogin() == FALSE)
	{
		*pResult = VE_LOGOUTED; // not login
		OutputDebugString("SSO_VerifyEmp - IsLogin logout상태임\n");
		return FAIL;
	}

	//---------------------------------------------------------------
  // 3 .  전송할 패킷 구하기 
	// 3-1. CN
	// 3-2. Cert Serial
	// 3-3. 전문 만들기
	//---------------------------------------------------------------

	// 3-1. CN 구하기
	TCHAR szCN[MAX_PATH] = { 0, };
	int   nCNSize = sizeof(szCN);

	if (1 != ISignDllOBJ.GetCurUserID(szCN, nCNSize))
	{
		*pResult = VE_FAIL_GET_CUR_USER_CN; // cn 구할수 없음
		OutputDebugString("SSO_VerifyEmp - CN구할 수 없음\n");
		return FAIL;
	}

	// 3-2. serial 구하기
	TCHAR szCert[2048] = { 0, };
	int   nCertLen = sizeof(szCert);

	if (1 != ISignDllOBJ.GetCurUserPKICert(szCert, &nCertLen, nCertLen))
	{
		*pResult = VE_FAIL_GET_CUR_USER_CERT_SERIAL;  // serial 구할 수 없음
		OutputDebugString("SSO_VerifyEmp - serial구하기 \n");
		return FAIL;
	}

	TCHAR   szSerial[MAX_PATH] = { 0, };
	int     serialMaxLen = sizeof(szSerial);


	// ssa.dll  로드 
	TCHAR	szISSACPath[MAX_PATH] = { 0, };

	if (GetISSACFileDirectory(szISSACPath) == TRUE)
		_tcscat(szISSACPath, _T("\\"));

	_tcscat(szISSACPath, _T("ssa.dll"));

	HMODULE hModule = LoadLibraryEx(szISSACPath, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);

	if (hModule == NULL)
	{
		*pResult = VE_ISIGN_CAN_NOT_LOAD_LIBRARY;
		OutputDebugString("SSO_VerifyEmp - ssa.dll로드실패 \n");
		return FAIL;
	}

	typedef struct _SSACert {
		void *certificate;  /* CIS Certificate type */
		void *parameter;    /* CIS Parameter */
	} SSACert;
	//김대형
	typedef INT_PTR(*F_BG_SSACert_Create)(SSACert *cert);
	typedef INT_PTR(*F_BG_SSACert_ReadMemory)(SSACert *cert,
		const char *certBuf, int certBufLen,
		const char *paramBuf, int paramBufLen);
	typedef INT_PTR(*F_BG_SSACert_GetSerialNumber)(char *serial, int serialMaxLen, SSACert *cert);
	typedef INT_PTR(*F_BG_SSACert_Delete)(SSACert *cert);

	F_BG_SSACert_Create           fBG_SSACert_Create = (F_BG_SSACert_Create)GetProcAddress(hModule, "BG_SSACert_Create");
	F_BG_SSACert_ReadMemory       fBG_SSACert_ReadMemory = (F_BG_SSACert_ReadMemory)GetProcAddress(hModule, "BG_SSACert_ReadMemory");
	F_BG_SSACert_GetSerialNumber  fBG_SSACert_GetSerialNumber = (F_BG_SSACert_GetSerialNumber)GetProcAddress(hModule, "BG_SSACert_GetSerialNumber");
	F_BG_SSACert_Delete           fBG_SSACert_Delete = (F_BG_SSACert_Delete)GetProcAddress(hModule, "BG_SSACert_Delete");

	if (fBG_SSACert_Create == NULL || fBG_SSACert_ReadMemory == NULL ||
		fBG_SSACert_GetSerialNumber == NULL || fBG_SSACert_Delete == NULL)
	{
		*pResult = VE_ISIGN_CAN_NOT_FIND_FUN;
		return FAIL;
	}

	SSACert cert;
	fBG_SSACert_Create(&cert);
	fBG_SSACert_ReadMemory(&cert, szCert, nCertLen, NULL, 0);
	fBG_SSACert_GetSerialNumber(szSerial, serialMaxLen, &cert);
	fBG_SSACert_Delete(&cert);
	/*
	  SSACert cert;
		BG_SSACert_Create(&cert);
		BG_SSACert_ReadMemory(&cert,szCert,nCertLen,NULL,0);
	  BG_SSACert_GetSerialNumber(szSerial, serialMaxLen,&cert);
		BG_SSACert_Delete(&cert);
	*/
	// serial 값 체크
	if (strlen(szSerial) != CERT_SERIAL_SIZE)
	{
		*pResult = VE_INVALID_SERIAL;
		OutputDebugString("SSO_VerifyEmp - serial 값 체크 실패\n");
		return FAIL;
	}

	// 3-2. 전문 만들기

	TCHAR sendBuf[MAX_PATH] = { 0, };
	sendBuf[0] = (char)0xca;
	sendBuf[1] = 1/*(char)0xca*/ + 1 /*sendBuf[1]*/ + strlen(szSerial) + strlen(szCN) + 1 /*NULL*/;
	memcpy(sendBuf + 2, szSerial, strlen(szSerial));
	memcpy(sendBuf + 2 + strlen(szSerial), szCN, strlen(szCN) + 1);

	//---------------------------------------------------------------
  // 4 . TMAX 설정
	//---------------------------------------------------------------

	// 4-1. issac-file폴더 구함.
	HKEY  hKey;
	LONG  regRet;
	char  pszFullFileName[MAX_PATH];
	DWORD len = MAX_PATH;

	regRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		"SOFTWARE\\Penta Security Systems\\ISSAC-File",
		0, KEY_ALL_ACCESS, &hKey);

	if (regRet != ERROR_SUCCESS) return -1;

	regRet = RegQueryValueEx(hKey, "TargetDir", NULL, NULL, (LPBYTE)pszFullFileName, &len);

	RegCloseKey(hKey);
	if (regRet != ERROR_SUCCESS)
	{
		*pResult = VE_ENV_ERR; //환경설정 에러
		return FAIL;
	}

	strcat(pszFullFileName, "\\conf\\");
	strcat(pszFullFileName, "TMAX.ENV");

	CDllLoad tmaxOBJ;
	HMODULE hTmaxDll = tmaxOBJ.LoadDLL("tmax.dll", 0);

	struct	tpstart_t {
		char	usrname[MAXTIDENT + 2];	/* usr name */
		char	cltname[MAXTIDENT + 2];	/* application client name */
		char  dompwd[MAX_PASSWD_LENGTH + 2]; /* domain password */
		char  usrpwd[MAX_PASSWD_LENGTH + 2]; /* passwd for usrid */
		int   flags;
	};
	typedef	struct	tpstart_t TPSTART_T;
	//김대형 ->에러날 가능성 있음
	typedef INT_PTR(*F_tmaxreadenv)(char *file, char *label);
	typedef  INT_PTR(*F_tpstart)(TPSTART_T *);
	typedef  INT_PTR(*F_tpalloc)(char *type, char *subtype, long size);
	//typedef (*F_tpset_timeout)(int sec);
	typedef  INT_PTR(*F_tpcall)(char *svc, char *idata, long ilen, char **odata,
		long *olen, long flags);
	typedef INT_PTR(*F_gettperrno)(void);
	typedef INT_PTR(*F_tpend)();
	typedef INT_PTR(*F_tpfree)(char *ptr);

	F_tmaxreadenv   ftmaxreadenv = (F_tmaxreadenv)GetProcAddress(hTmaxDll, "tmaxreadenv");
	F_tpstart       ftpstart = (F_tpstart)GetProcAddress(hTmaxDll, "tpstart");
	F_tpalloc       ftpalloc = (F_tpalloc)GetProcAddress(hTmaxDll, "tpalloc");
	//F_tpset_timeout ftpset_timeout = (F_tpset_timeout)GetProcAddress(hTmaxDll, "tpset_timeout");
	F_tpcall        ftpcall = (F_tpcall)GetProcAddress(hTmaxDll, "tpcall");
	F_gettperrno    fgettperrno = (F_gettperrno)GetProcAddress(hTmaxDll, "gettperrno");
	F_tpfree        ftpfree = (F_tpfree)GetProcAddress(hTmaxDll, "tpfree");
	F_tpend         ftpend = (F_tpend)GetProcAddress(hTmaxDll, "tpend");

	// 4-2. env 파일로  접속 시도 
	if (ftmaxreadenv(pszFullFileName, "SSO") < 0) 
	{
		*pResult = VE_TMAX_CONF_ERR;
		OutputDebugString("SSO_VerifyEmp - ftmaxreadenv실패 \n");
		return FAIL;
	}

	if((int)(ftpstart((TPSTART_T *)NULL)) ==-1 )	
	{
		*pResult = VE_TMAX_START_ERR;
		int ret = fgettperrno();
		OutputDebugString("SSO_VerifyEmp - ftpstart 실패\n");
		return FAIL;
	}
	
	//---------------------------------------------------------------
  // 5 . Send / receive Data
	//---------------------------------------------------------------
	
	char *returnBuff;
  int sndLen = sendBuf[1];
  returnBuff = (char *)ftpalloc("CARRAY", NULL, 100);
	memcpy(returnBuff,sendBuf,sndLen);
	long returnBuffLen = 100;
    
   //요청을 보내는 버퍼를 응답을 받기 위한 버퍼로도 사용 
  //ftpset_timeout(7);
  if (ftpcall("VCERTSVC", returnBuff, sndLen, 
             &returnBuff, &returnBuffLen, TPNOFLAGS) == -1)
  {
		  int err = fgettperrno();
      ftpfree(returnBuff);
      ftpend();
			*pResult = VE_TRANSE_DATA_ERR;
			OutputDebugString("SSO_VerifyEmp - tpcall 실패\n");
      return FAIL;
  }

	
	struct RECVDATA{
		char id;
		char error;
		char revoke;
		char period;
		char empNum[16];
	};

	RECVDATA *pRecvData = reinterpret_cast<RECVDATA *>(returnBuff);

	//---------------------------------------------------------------
  // 7 . return
	//---------------------------------------------------------------
	if(pRecvData->id != (char)0xca) 
	{
		*pResult = VE_RECV_UNKNOWN_MSG;
		ftpfree(returnBuff);
	  ftpend();
		return FAIL;
	}

  int nRet = SUCCESS;
	if(pRecvData->error ==  SUCCESS) 
	{
	  *pEmpNumLen = strlen(pRecvData->empNum);                // 행번 길이 
		 strncpy(pszEmpNum, pRecvData->empNum, *pEmpNumLen +1); // 행번

		 char *cn = strtok(szCN,"_"); 
		 ZeroMemory(pszEmpName,*pEmpNameLen);
		 strcpy(pszEmpName,cn);
		 *pEmpNameLen = strlen(cn);

		 // 결과값
		 if(pRecvData->revoke == CERT_STATUS_GOOD) 
		 {
				if(pRecvData->period == CERT_PERIOD_VALID) 
			 {
				 *pResult = STATUS_GOOD_AND_PERIOD_VALID; 
			 }
			 else if(pRecvData->period == CERT_PERIOD_NOTVALID) 
			 {
				 *pResult = STATUS_GOOD_AND_PERIOD_NOTVALID; 
			 }
			 else
			 {
				 *pResult = VE_RECV_UNKNOWN_MSG ;
				 nRet = FAIL;
			 }
		 }
		 else if(pRecvData->revoke == CERT_STATUS_REVOKE) 
		 {
			 if(pRecvData->period == CERT_PERIOD_VALID) 
			 {
				 *pResult = STATUS_REVOKE_AND_PERIOD_VALID; 
			 }
			 else if(pRecvData->period == CERT_PERIOD_NOTVALID) 
			 {
					*pResult = STATUS_REVOKE_AND_PERIOD_NOTVALID; 
			 }
			 else
			 {
				 *pResult = VE_RECV_UNKNOWN_MSG;
				 nRet = FAIL;
			 }
		 }
		 else
		 {
			 *pResult = VE_RECV_UNKNOWN_MSG;
			 nRet = FAIL;
		 }
	}
	else
	{/*
		#define RET_ERR_NOMATCH_CN       (0x01) + RET_RECV_ERROR == 	VE_NO_MATCH_CN = 101,
		#define RET_ERR_FAIL_PKIDB       (0x02) + RET_RECV_ERROR == 	VE_FAIL_PKIDB
		#define RET_ERR_NO_SUCH_CERT     (0x03) + RET_RECV_ERROR == 	VE_NO_SUCH_CERT
		#define RET_ERR_NO_SUCH_EMPLOYEE (0x04) + RET_RECV_ERROR == 	VE_NO_SUCH_EMPLOYEE
		#define RET_ERR_EMPNUM_TOO_LONG  (0x05) + RET_RECV_ERROR == 	VE_EMPNUM_TOO_LONG
		#define RET_RECV_UNKNOWN_MSG     (0x06) + RET_RECV_ERROR ==   VE_RECV_UNKNOWN_MSG	
		#define RET_RECV_ERROR           100           */
	  *pResult = pRecvData->error + RET_RECV_ERROR;
		nRet = FAIL;
	}

	
	ftpfree(returnBuff);
  ftpend();

	return nRet;
}


//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
//┃                                                                              ┃
//┃                          DSS_GetSSOStatus	                                ┃
//┃  2004. 08.22 김상학                                                          ┃
//┃                                                                              ┃
//┃  1.  시스템에 MS로 로그인 했는지, IF로 로그인 했는지 알아낸다                ┃
//┃  2.  SSO에 로그인 했는지 알아낸다                                            ┃
//┃  3.  결과                                                                    ┃
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
INT DSS_GetSSOStatus (void)
{
	// return code
	enum LOGONSTATUS { enumIF_LOGINED = 0, 
		                 enumOAC_LOGINED, 
										 enumLOGOUTED, 
										 enumISIGN_NOT_INSTALLED, 
										 enumENV_ERR,
										 enumUNKNOWN_ERR };
	INT nLoginStatus;
	//IF_SetLastError(SUCCESS);

  //---------------------------------------------------------------
  // 1 . 시스템에 MS로 로그인 했는지, IF로 로그인 했는지 알아낸다
	//---------------------------------------------------------------

	nLoginStatus = IF_IsIFLogon(); 

	//---------------------------------------------------------------
  // 2 . SSO에 로그인 했는지 알아낸다
	// 2-1. ISign Desktop이 설치되어있는지 체크
	// 2-2. isigndtp.dll이 있는 경로를 구함
	// 2-3. isigndtp.dll 로드하여 ISignDtop_IsLogin() 호출
	//---------------------------------------------------------------

	// 2-1. dll load

	CISignDtpDLL ISignDllOBJ;
	int ret = ISignDllOBJ.LoadDLL("isigndtp.dll");
	if(ret != SUCCESS) {
		return ret;
	}

	// 2-2. login 상태인가?
  BOOL bLogin = ISignDllOBJ.IsLogin();

	if(bLogin) {
	  nLoginStatus = (nLoginStatus == enumIF_LOGINED) ? enumIF_LOGINED : enumOAC_LOGINED;
	}
	else {
	  nLoginStatus = enumLOGOUTED;			
	}
		
	//---------------------------------------------------------------
  // 3 . 결과 
	//---------------------------------------------------------------

	return nLoginStatus;
}




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
INT DSS_CheckCard(void)
{
	//---------------------------------------------------------
	// set return code
	//---------------------------------------------------------

	enum {
		CARD_INSERTED = 0,
		CARD_REMOVED,
		READER_OPEN_ERROR,
		NOT_INSTALLED_SSO,
		NOT_FOUND_FUNCTION
	};

  //---------------------------------------------------------
  // scmod.dll load
  //---------------------------------------------------------
	TCHAR	szISSACPath[MAX_PATH] = {0,};

	if( GetISSACFileDirectory(szISSACPath) == TRUE )
		_tcscat(szISSACPath, _T("\\"));

	_tcscat(szISSACPath, _T("scmod.dll"));

	HMODULE hModule = LoadLibraryEx(szISSACPath, 0, LOAD_WITH_ALTERED_SEARCH_PATH);
 
	if(hModule == NULL) 
	{
		return NOT_INSTALLED_SSO;
	}

	// 
	typedef void* SCCtx;
	//김대형
	//typedef (*F_SspMod_Open)(int port);
	typedef int (*F_SspMod_Open)(int port); 
  typedef   int (*F_SspMod_IsCardIn)(SCCtx scctx); 
	typedef  int (*F_SspMod_Close)(SCCtx scctx);

	F_SspMod_Open     fSspMod_Open     = (F_SspMod_Open)     GetProcAddress(hModule,"SspMod_Open");
	F_SspMod_IsCardIn fSspMod_IsCardIn = (F_SspMod_IsCardIn) GetProcAddress(hModule,"SspMod_IsCardIn");
	F_SspMod_Close    fSspMod_Close    = (F_SspMod_Close)    GetProcAddress(hModule,"SspMod_Close"); 

	if( fSspMod_Open == NULL || fSspMod_IsCardIn == NULL || fSspMod_Close == NULL) 
	{
		return NOT_FOUND_FUNCTION; //dll 버전 살펴볼것
	}

	//---------------------------------------------------------
	// card check
	//---------------------------------------------------------
  
	SCCtx ctx;
	ctx = (void *)fSspMod_Open(0);
	if(NULL == ctx)
	{
		return READER_OPEN_ERROR;
	}
  
	int nRet = fSspMod_IsCardIn(ctx);
	
	switch(nRet) {
	case 1:	 	  nRet = CARD_INSERTED;	break;
	case 0:		  nRet = CARD_REMOVED;	break;
	default :	{
							char msgBuf[100];
							wsprintf(msgBuf,"\nSSO_CheckCard() Error code : %d\n",nRet);
							OutputDebugString(msgBuf);
							nRet = READER_OPEN_ERROR;
						}
						break;
	}
  
	fSspMod_Close(ctx);
	
	return nRet;
}


BOOL DSS_GetVersion(OUT LPTSTR lpszVersion, IN DWORD cbBufSize)
{
  if( cbBufSize <= 0 || cbBufSize <= (unsigned int) lstrlen(DSS_SDK_VERSION) )
    return FALSE;  
  
  ZeroMemory( lpszVersion, cbBufSize );
  lstrcpy(lpszVersion, DSS_SDK_VERSION);
  return TRUE;
}

int DSS_FP_GetEnrollSecurityLevel(unsigned int *nEnrollLevel)
{
	HKEY  hKey = NULL;
	LONG  retKey;
	DWORD cbsize;
	
	retKey = RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Penta Security Systems\\LogonManager"),	0, KEY_ALL_ACCESS , &hKey);
	
	if (ERROR_SUCCESS == retKey)
	{
		cbsize = sizeof(int);
		retKey = RegQueryValueEx(hKey, "EnrollSecurityLevel",  NULL, NULL, (LPBYTE)nEnrollLevel, &cbsize);
		
		if( ERROR_SUCCESS != retKey )
		{
			DWORD  dwEnrollLevel = 9;
			cbsize = sizeof(dwEnrollLevel);
			retKey = RegSetValueEx(hKey, "EnrollSecurityLevel", 0, REG_DWORD, (LPBYTE)&dwEnrollLevel, cbsize);
		}
				
		retKey = RegQueryValueEx(hKey, "EnrollSecurityLevel",  NULL, NULL, (LPBYTE)nEnrollLevel, &cbsize);
		
		if( ERROR_SUCCESS != retKey )	return -1;
	}
	
	RegCloseKey(hKey);
	return 0;
}

int DSS_FP_GetVerifySecurityLevel(unsigned int *nVerifyLevel)
{
	HKEY  hKey = NULL;
	LONG  retKey;
	DWORD cbsize;

	retKey = RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Penta Security Systems\\LogonManager"),	0, KEY_ALL_ACCESS , &hKey);
	
	if (ERROR_SUCCESS == retKey)
	{
		cbsize = sizeof(int);
		
		retKey = RegQueryValueEx(hKey, "VerifySecurityLevel", NULL, NULL, (LPBYTE)nVerifyLevel, &cbsize);
	
		if( ERROR_SUCCESS != retKey )
		{
			DWORD  dwVerifyLevel = 5;
			cbsize = sizeof(dwVerifyLevel);
			retKey = RegSetValueEx(hKey, "VerifySecurityLevel", 0, REG_DWORD, (LPBYTE)&dwVerifyLevel, cbsize);
		}

		retKey = RegQueryValueEx(hKey, "VerifySecurityLevel", NULL, NULL, (LPBYTE)nVerifyLevel, &cbsize);
		
		if( ERROR_SUCCESS != retKey )	return -1;			
	}
	
	RegCloseKey(hKey);
	return 0;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//////////////////////////////


int g_resource;
char g_errorstr[1024];
int g_select_device_id=-1;




LRESULT CALLBACK DSS_FP_PROC(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{ 
   
  HDC hdc;
  static HBITMAP hbitmap;
  static HBITMAP holdbitmap;
  static HDC memdc;
  static HFONT h=NULL,oldh;
  
  switch (message) 
  { 

  case UM_DESTROY:
    SelectObject(memdc,holdbitmap);
    DeleteDC(memdc);
    DSS_FP_CloseAnimationCtrl();

    return TRUE;

  case WM_DESTROY:
    return TRUE;

  case WM_CLOSE:
    return FALSE;

  case WM_PAINT:

    RECT rt;
    GetClientRect(hDlg, &rt);
    hdc = GetWindowDC(hDlg);

    BitBlt(hdc,0,0,rt.right-rt.left,rt.bottom-rt.top,  memdc,0,0,SRCCOPY);
    
    SetBkMode(hdc,TRANSPARENT);

    int len;
    len=strlen(g_textMsg);
    if(h!=NULL)
      oldh=(HFONT)SelectObject(hdc,h);
    
		//
    TextOut(hdc,85,50,g_textMsg,len);
    
    if(h!=NULL)
      SelectObject(hdc,oldh);
    
		ReleaseDC(hDlg,hdc);
		
    return FALSE;

      case UM_SETTEXT:
      {

        strcpy(g_textMsg,(LPCSTR)lParam);
        InvalidateRect(hDlg,NULL,TRUE);
      }
      return TRUE;

      case WM_INITDIALOG: 
         // CheckDlgButton(g_hwndDlg, ID_ABSREL, fRelative); 
        g_hwndDlg=hDlg;

        BITMAP bmp; 
        
        SetWindowLong(hDlg,GWL_EXSTYLE,WS_EX_TOPMOST);
        
        if(g_resource==0)
          hbitmap=LoadBitmap((HINSTANCE)g_instance,(char*)IDB_BITMAP1);
        else
          hbitmap=LoadBitmap((HINSTANCE)g_instance,(char*)IDB_BITMAP2);

        memdc=CreateCompatibleDC(NULL);
        holdbitmap=(HBITMAP)SelectObject(memdc,hbitmap);
        
        GetObject(hbitmap,sizeof(BITMAP),(LPSTR)&bmp);
        
				DeleteObject(hbitmap);

        GetWindowRect(hDlg,&rt);
        MoveWindow(hDlg,rt.left,rt.top,bmp.bmWidth,bmp.bmHeight,TRUE);

        //CenterWindow(hDlg);

        DSS_FP_CreateAnimationCtrl();

        h=(HFONT)SendMessage(g_hwndDlg,WM_GETFONT,(WPARAM) 0,(LPARAM)0);
			

        return TRUE; 

      case WM_SHOWWINDOW:
        {

			RECT rect = {0,},rc = {0,};
          int x,y;

//					TITLEBARINFO ti;
//					SCROLLBARINFO sbi;

//          HWND p=GetParent(hDlg);
          HWND p=g_hparentwnd;	// 20070919 김철권 (버그땜시..)

          GetWindowRect(p,&rect);
					GetClientRect(hDlg,&rc);
/*
										
										rect.left -= (GetSystemMetrics(SM_CXFIXEDFRAME) * 2);
										rect.left -= (GetSystemMetrics(SM_CXFRAME) * 2);
										rect.left -= (GetSystemMetrics(SM_CXBORDER) * 2);
										if (GetScrollBarInfo(p, OBJID_HSCROLL, &sbi))
											rect.left -= (GetSystemMetrics(SM_CXHSCROLL));
					
										
										if (GetTitleBarInfo(p, &ti))
											rect.top -= GetSystemMetrics(SM_CYCAPTION);
													if (GetMenu(p) != NULL)
											rect.top -= GetSystemMetrics(SM_CYMENU);
										if (GetScrollBarInfo(p, OBJID_VSCROLL, &sbi))
											rect.left -= (GetSystemMetrics(SM_CYVSCROLL));
													
										rect.top -= (GetSystemMetrics(SM_CYFIXEDFRAME) * 2);
*/

					if (rc.right < (rect.right-rect.left)) 
						x = (rect.left+((rect.right-rect.left)/2)) - (rc.right/2);
					else if (rc.right > (rect.right-rect.left)) 
						x = (rect.left+((rect.right-rect.left)/2)) + (rc.right/2);
					else
						x = (rect.left+((rect.right-rect.left)/2));

					if (rc.bottom < (rect.bottom-rect.top))
						y = (rect.top+((rect.bottom-rect.top)/2)) - (rc.bottom/2);
					else if (rc.bottom > (rect.bottom-rect.top))
						y = (rect.top+((rect.bottom-rect.top)/2)) + (rc.bottom/2);
					else
						y = (rect.top+((rect.bottom-rect.top)/2));

					SetWindowPos(hDlg, HWND_TOPMOST, x, y, 0, 0, SWP_NOSIZE);
        }
        return TRUE;


      default:
         DefWindowProc(hDlg, message, wParam, lParam);
         return FALSE;
  } 

    
} 



void MyThread(void *);

int __stdcall  DSS_FP_InitializeStd(HWND hwnd,int skinflag,int libflag)
{

  return DSS_FP_Initialize(hwnd,(int)skinflag,(int)libflag);
}

DSS int DSS_FP_Initialize(HWND hwnd,int skinflag,int libflag)
{
  if(g_bioobject==NULL)
  { 
    
    if(libflag==0)
      g_bioobject=&g_nbioapi;
    else if(libflag==1)
      g_bioobject=&g_mybioapi;
    else
    {
      LOGPRINT("3번째 인자값을 잘못 주었습니다.(0: nitgen,1: bioapi)",7000);
      return DSS_FAILED;
    }
  }
  
  return g_bioobject->DSS_FP_Initialize(hwnd,skinflag);
}
  
// 20070903 임종문
DSS int DSS_FP_InitializeEx(HWND hwnd,int skinflag,int libflag)
{
  g_bDirectDisplay = TRUE;

	return DSS_FP_Initialize(hwnd, skinflag, libflag);
}

void __stdcall CALLBACK DSS_FP_DestroyStd()
{

  DSS_FP_Destroy();
}

void DSS_FP_Destroy()
{

  if(g_bioobject)
  {
    g_bioobject->DSS_FP_Destroy();
  }
}

long DSS_FP_CheckScard()
{
	int ret;
  SCCtx ctx;
  
  
  DSS_FP_PlayAnimationCtrl("토큰를 체크 중입니다.");

	ctx = SspMod_Open(0);
	if(!ctx) 
  {
    LOGPRINT("리더기를 오픈하지 못했습니다",8000);
    DSS_FP_StopAnimationCtrl();
		return DSS_FAILED;
  }
	

	ret = SspMod_IsCardIn(ctx);	
	if(ret == 1) ;
	else if(ret == 0) 
	{
		SspMod_Close(ctx);
    LOGPRINT("단말기에 토큰가 없습니다",8001);
    DSS_FP_StopAnimationCtrl();
		return DSS_FAILED;	//	단말기에 토큰가 없습니다.
	}
	else
	{
		SspMod_Close(ctx);
    LOGPRINT("토큰에 문제가 있습니다",8002);
    DSS_FP_StopAnimationCtrl();
		return DSS_FAILED;	//	토큰 문제
	}


	ret = SspMod_EstablishSessKey(ctx);
	if(ret != 0)
	{
		SspMod_Close(ctx);
    LOGPRINT("토큰에 문제가 있습니다",8002);
    DSS_FP_StopAnimationCtrl();
		return DSS_FAILED;	
	}
	
	ret = SspMod_VerifyPin(ctx);	
	if( ret == SspMod_PIN_BLOCKED ) 
	{
		SspMod_Close(ctx);
    LOGPRINT("잠긴 토큰입니다",8003);
    DSS_FP_StopAnimationCtrl();
		return DSS_FAILED;	//	잠긴 토큰입니다.
	}
	else if(ret != 0)
	{
		SspMod_Close(ctx);
    LOGPRINT("인식할 수 없는 토큰입니다",8004);
    DSS_FP_StopAnimationCtrl();
		return DSS_FAILED;	//	인식할 수 없는 토큰입니다.
	}

	if(ctx) SspMod_Close(ctx);

  DSS_FP_StopAnimationCtrl();

	return 1;
}

long DSS_FP_CheckScardEx(char *readername)
{
	int ret;
  SCCtx ctx;
	char buffer[255] = {0,};
  
  DSS_FP_PlayAnimationCtrl("토큰를 체크 중입니다.");
	
	ctx = SspMod_OpenByReaderName( 0, readername);
	if(!ctx) 
  {
    LOGPRINT("리더기를 오픈하지 못했습니다",8000);
    DSS_FP_StopAnimationCtrl();
		return DSS_FAILED;
  }
	
	
	ret = SspMod_IsCardIn(ctx);	
	if(ret == 1) ;
	else if(ret == 0) 
	{
		SspMod_Close(ctx);
    LOGPRINT("단말기에 토큰가 없습니다",8001);
    DSS_FP_StopAnimationCtrl();
		return DSS_FAILED;	//	단말기에 토큰가 없습니다.
	}
	else
	{
		SspMod_Close(ctx);
    LOGPRINT("토큰에 문제가 있습니다",8002);
    DSS_FP_StopAnimationCtrl();
		return DSS_FAILED;	//	토큰 문제
	}
	
	
	ret = SspMod_EstablishSessKey(ctx);
	if(ret != 0)
	{
		SspMod_Close(ctx);
    LOGPRINT("토큰에 문제가 있습니다",8002);
    DSS_FP_StopAnimationCtrl();
		return DSS_FAILED;	
	}
	
	ret = SspMod_VerifyPin(ctx);	
	if( ret == SspMod_PIN_BLOCKED ) 
	{
		SspMod_Close(ctx);
    LOGPRINT("잠긴 토큰입니다",8003);
    DSS_FP_StopAnimationCtrl();
		return DSS_FAILED;	//	잠긴 토큰입니다.
	}
	else if(ret != 0)
	{
		SspMod_Close(ctx);
    LOGPRINT("인식할 수 없는 토큰입니다",8004);
    DSS_FP_StopAnimationCtrl();
		return DSS_FAILED;	//	인식할 수 없는 토큰입니다.
	}
	
	if(ctx) SspMod_Close(ctx);
	
  DSS_FP_StopAnimationCtrl();
	
	return 1;
}


long ReadFIRFromScard(PBYTE pBuf, DWORD dwBufLen, DWORD *dwReadLen)
{
	int ret=-1;
  SCCtx ctx;

  DSS_FP_PlayAnimationCtrl("토큰를 읽는 중입니다.");
	

	ctx = SspMod_Open(0);
	if(!ctx) 
  {
    LOGPRINT("리더기를 오픈하지 못했습니다",8000);
    DSS_FP_StopAnimationCtrl();
		return -1;
  }
	
	ret = SspMod_IsCardIn(ctx);	
	if(ret == 1) ;
	else if(ret == 0) 
	{
		SspMod_Close(ctx);
    LOGPRINT("단말기에 토큰가 없습니다",8001);
    DSS_FP_StopAnimationCtrl();
		return -1;	//	단말기에 토큰가 없습니다.
	}
	else
	{
		SspMod_Close(ctx);
    LOGPRINT("토큰에 문제가 있습니다",8002);
    DSS_FP_StopAnimationCtrl();
		return -1;	//	토큰 문제
	}


	ret = SspMod_EstablishSessKey(ctx);
	if(ret != 0)
	{
		SspMod_Close(ctx);
    LOGPRINT("토큰에 문제가 있습니다",8002);
    DSS_FP_StopAnimationCtrl();
		return -1;	
	}
	
	ret = SspMod_VerifyPin(ctx);	
	if( ret == SspMod_PIN_BLOCKED ) 
	{
		SspMod_Close(ctx);
    LOGPRINT("잠긴 토큰입니다",8003);
    DSS_FP_StopAnimationCtrl();
		return -1;	//	잠긴 토큰입니다.
	}
	else if(ret != 0)
	{
		SspMod_Close(ctx);
    LOGPRINT("인식할 수 없는 토큰입니다",8004);
    DSS_FP_StopAnimationCtrl();
		return -1;	//	인식할 수 없는 토큰입니다.
	}

	// 20070529 자바토큰인지 식별한다.(임종문)
	if( !SspMod_IsJavaOpenCard(ctx) )
	{
		SspMod_Close(ctx);
		LOGPRINT("Native Card는 지문 데이터를 사용 할 수 없습니다",8018);
		DSS_FP_StopAnimationCtrl();
		return -1;
	}


	if( SspMod_SelectFile(ctx, (PBYTE)DFID) != SUCCESS )
  {
    LOGPRINT("SspMod_SelectFile에서 실패했습니다",8005);
    DSS_FP_StopAnimationCtrl();
		return -1;
  }

	if( SspMod_SelectFile(ctx, (PBYTE)DFID_FINGER_FLD) != SUCCESS )
  {
    LOGPRINT("SspMod_SelectFile에서 실패했습니다",8005);
    DSS_FP_StopAnimationCtrl();
		return -1;
  }


  	if( SspMod_ReadBinEx( pBuf, dwBufLen, (long*)dwReadLen, ctx ) != SUCCESS )
    {
      LOGPRINT("토큰 읽기에 실패했습니다",8005);
      DSS_FP_StopAnimationCtrl();
	  	return -1;
    }

	if(ctx) SspMod_Close(ctx);

  

  DSS_FP_StopAnimationCtrl();

	return 1;
}



long ReadFIRFromScardEx(PBYTE pBuf, DWORD dwBufLen, DWORD *dwReadLen, char *readername)
{
	int ret=-1;
  SCCtx ctx;
	char buffer[255] = {0,};
  
  DSS_FP_PlayAnimationCtrl("토큰를 읽는 중입니다.");

	ctx = SspMod_OpenByReaderName( 0, readername );
	if(!ctx) 
  {
    LOGPRINT("리더기를 오픈하지 못했습니다",8000);
    DSS_FP_StopAnimationCtrl();
		return -1;
  }
	
	ret = SspMod_IsCardIn(ctx);	
	if(ret == 1) ;
	else if(ret == 0) 
	{
		SspMod_Close(ctx);
    LOGPRINT("단말기에 토큰가 없습니다",8001);
    DSS_FP_StopAnimationCtrl();
		return -1;	//	단말기에 토큰가 없습니다.
	}
	else
	{
		SspMod_Close(ctx);
    LOGPRINT("토큰에 문제가 있습니다",8002);
    DSS_FP_StopAnimationCtrl();
		return -1;	//	토큰 문제
	}
	
	
	ret = SspMod_EstablishSessKey(ctx);
	if(ret != 0)
	{
		SspMod_Close(ctx);
    LOGPRINT("토큰에 문제가 있습니다",8002);
    DSS_FP_StopAnimationCtrl();
		return -1;	
	}
	
	ret = SspMod_VerifyPin(ctx);	
	if( ret == SspMod_PIN_BLOCKED ) 
	{
		SspMod_Close(ctx);
    LOGPRINT("잠긴 토큰입니다",8003);
    DSS_FP_StopAnimationCtrl();
		return -1;	//	잠긴 토큰입니다.
	}
	else if(ret != 0)
	{
		SspMod_Close(ctx);
    LOGPRINT("인식할 수 없는 토큰입니다",8004);
    DSS_FP_StopAnimationCtrl();
		return -1;	//	인식할 수 없는 토큰입니다.
	}
	
	// 20070529 자바토큰인지 식별한다.(임종문)
	if( !SspMod_IsJavaOpenCard(ctx) )
	{
		SspMod_Close(ctx);
		LOGPRINT("Native Card는 지문 데이터를 사용 할 수 없습니다",8018);
		DSS_FP_StopAnimationCtrl();
		return -1;
	}
	
	
	if( SspMod_SelectFile(ctx, (PBYTE)DFID) != SUCCESS )
  {
    LOGPRINT("SspMod_SelectFile에서 실패했습니다",8005);
    DSS_FP_StopAnimationCtrl();
		return -1;
  }
	
	if( SspMod_SelectFile(ctx, (PBYTE)DFID_FINGER_FLD) != SUCCESS )
  {
    LOGPRINT("SspMod_SelectFile에서 실패했습니다",8005);
    DSS_FP_StopAnimationCtrl();
		return -1;
  }
	
	
	if( SspMod_ReadBinEx( pBuf, dwBufLen, (long*)dwReadLen, ctx ) != SUCCESS )
	{
		LOGPRINT("토큰 읽기에 실패했습니다",8005);
		DSS_FP_StopAnimationCtrl();
	  	return -1;
	}
	
	if(ctx) SspMod_Close(ctx);
	
  
	
  DSS_FP_StopAnimationCtrl();
	
	return 1;
}


long WriteFIRToScard(PBYTE pBinaryStream, DWORD dwStreamLength)
{
 

	int ret=-1;
  SCCtx ctx;

  DSS_FP_PlayAnimationCtrl("토큰에 쓰는 중입니다.");

	ctx = SspMod_Open(0);
	if(!ctx) 
  {
    LOGPRINT("토큰 리더기를 오픈하지 못했습니다",8000);
    DSS_FP_StopAnimationCtrl();
		return -1;
  }
	
	ret = SspMod_IsCardIn(ctx);	
	if(ret == 1) ;
	else if(ret == 0) 
	{
		SspMod_Close(ctx);
    LOGPRINT("단말기에 토큰가 없습니다",8001);
    DSS_FP_StopAnimationCtrl();
		return -1;	//	단말기에 토큰가 없습니다.
	}
	else
	{
		SspMod_Close(ctx);
    LOGPRINT("토큰에 문제가 있습니다",8002);
    DSS_FP_StopAnimationCtrl();
		return -1;	//	토큰 문제
	}

	ret = SspMod_EstablishSessKey(ctx);
	if(ret != 0)
	{
		SspMod_Close(ctx);
    LOGPRINT("SspMod_EstablishSessKey에서 에러가 발생했습니다",8005);
    DSS_FP_StopAnimationCtrl();
		return -1;	
	}
	
	ret = SspMod_VerifyPin(ctx);	
	if( ret == SspMod_PIN_BLOCKED ) 
	{
		SspMod_Close(ctx);
    LOGPRINT("잠긴 토큰 입니다",8003);
    DSS_FP_StopAnimationCtrl();
		return -1;	//	잠긴 토큰입니다.
	}
	else if(ret != 0)
	{
		SspMod_Close(ctx);
    LOGPRINT("인식할 수 없는 토큰입니다",8004);
    DSS_FP_StopAnimationCtrl();
		return -1;	//	인식할 수 없는 토큰입니다.
	}

	if( SspMod_SelectFile(ctx, (PBYTE)DFID) != SUCCESS )
  {
    LOGPRINT("SspMod_SelectFile에서 에러가 발생했습니다",8005);
    DSS_FP_StopAnimationCtrl();
		return -1;
  }

	if( SspMod_SelectFile(ctx, (PBYTE)DFID_FINGER_FLD) != SUCCESS )
  {
    LOGPRINT("SspMod_SelectFile에서 에러가 발생했습니다",8005);
    DSS_FP_StopAnimationCtrl();
		return -1;
  }


  /*
  {
    int len;
    len=fwrite(pBinaryStream,1,dwStreamLength,file);
    
  }*/
  
  
	if( SspMod_WriteBinEx( pBinaryStream, dwStreamLength, ctx ) != SUCCESS )
  {
    LOGPRINT("SspMod_SelectFile에서 에러가 발생했습니다",8005);
    DSS_FP_StopAnimationCtrl();
		return -1;
  }
    
	if(ctx) SspMod_Close(ctx);

  
  DSS_FP_StopAnimationCtrl();

	return 1;
}


long WriteFIRToScardEx(PBYTE pBinaryStream, DWORD dwStreamLength, char *readername)
{
	int ret=-1;
  SCCtx ctx;
	char buffer[255] = {0,};
  
	DSS_FP_PlayAnimationCtrl("토큰에 쓰는 중입니다.");

	ctx = SspMod_OpenByReaderName( 0, readername);
	if(!ctx) 
  {
    LOGPRINT("토큰 리더기를 오픈하지 못했습니다",8000);
    DSS_FP_StopAnimationCtrl();
		return -1;
  }
	
	ret = SspMod_IsCardIn(ctx);	
	if(ret == 1) ;
	else if(ret == 0) 
	{
		SspMod_Close(ctx);
    LOGPRINT("단말기에 토큰가 없습니다",8001);
    DSS_FP_StopAnimationCtrl();
		return -1;	//	단말기에 토큰가 없습니다.
	}
	else
	{
		SspMod_Close(ctx);
    LOGPRINT("토큰에 문제가 있습니다",8002);
    DSS_FP_StopAnimationCtrl();
		return -1;	//	토큰 문제
	}

	ret = SspMod_EstablishSessKey(ctx);
	if(ret != 0)
	{
		SspMod_Close(ctx);
    LOGPRINT("SspMod_EstablishSessKey에서 에러가 발생했습니다",8005);
    DSS_FP_StopAnimationCtrl();
		return -1;	
	}
	
	ret = SspMod_VerifyPin(ctx);	
	if( ret == SspMod_PIN_BLOCKED ) 
	{
		SspMod_Close(ctx);
    LOGPRINT("잠긴 토큰 입니다",8003);
    DSS_FP_StopAnimationCtrl();
		return -1;	//	잠긴 토큰입니다.
	}
	else if(ret != 0)
	{
		SspMod_Close(ctx);
    LOGPRINT("인식할 수 없는 토큰입니다",8004);
    DSS_FP_StopAnimationCtrl();
		return -1;	//	인식할 수 없는 토큰입니다.
	}

	if( SspMod_SelectFile(ctx, (PBYTE)DFID) != SUCCESS )
  {
    LOGPRINT("SspMod_SelectFile에서 에러가 발생했습니다",8005);
    DSS_FP_StopAnimationCtrl();
		return -1;
  }

	if( SspMod_SelectFile(ctx, (PBYTE)DFID_FINGER_FLD) != SUCCESS )
  {
    LOGPRINT("SspMod_SelectFile에서 에러가 발생했습니다",8005);
    DSS_FP_StopAnimationCtrl();
		return -1;
  }


  /*
  {
    int len;
    len=fwrite(pBinaryStream,1,dwStreamLength,file);
    
  }*/
  
  
	if( SspMod_WriteBinEx( pBinaryStream, dwStreamLength, ctx ) != SUCCESS )
  {
    LOGPRINT("SspMod_SelectFile에서 에러가 발생했습니다",8005);
    DSS_FP_StopAnimationCtrl();
		return -1;
  }
    
	if(ctx) SspMod_Close(ctx);

  
  DSS_FP_StopAnimationCtrl();

	return 1;
}


int __stdcall DSS_FP_EnrollStd(TCHAR * strpayload)
{
  return DSS_FP_Enroll(strpayload);
}

int __stdcall DSS_FP_EnrollStdEx(TCHAR * strpayload)
{
  return DSS_FP_EnrollEx(strpayload);
}

int DSS_FP_Enroll_Stream(char** outstream,int *len)
{
  INIT;

  return g_bioobject->DSS_FP_Enroll_Stream(outstream,len);
}


int DSS_FP_Enroll_Stream_Write(char*block,int len,char * payload)
{
  INIT;
  
  return g_bioobject->DSS_FP_Enroll_Stream_Write(block,len,payload);
}

int DSS_FP_Enroll_StreamEx(char** outstream,int *len, char* readername)
{
  INIT;
	
  return g_bioobject->DSS_FP_Enroll_StreamEx(outstream, len, readername);
}


int DSS_FP_Enroll_Stream_WriteEx(char*block,int len,char * payload, char *readername)
{
  INIT;
  
  return g_bioobject->DSS_FP_Enroll_Stream_WriteEx(block,len,payload,readername);
}

int DSS_FP_Capture(char** outstream,int *len)
{
  INIT;
	
  return g_bioobject->DSS_FP_Capture(outstream,len);
}

int DSS_FP_CaptureBase64(char* outBuf, const int outBufSize)
{
	char *FPData = NULL;
	int   len = 0;
  int ret = DSS_FP_Capture(&FPData, &len);
	if(ret != SUCCESS)
		return ret;
	
	char base64Data[4096];
	ret = Base64_Encode(base64Data, 4096, (LPBYTE)FPData, len);
	
	if ( (ret !=  SUCCESS) || (outBufSize < strlen(base64Data)+1) )
		return -22;
	
	strcpy(outBuf, base64Data);
	
	return SUCCESS;
}

DSS int __stdcall DSS_FP_CaptureBase64Std(char* outBuf, const int outBufSize)
{
	return DSS_FP_CaptureBase64(outBuf, outBufSize);
}

int DSS_FP_CapturedVerify(BYTE *byteData, int dwReadLen)
{
  INIT;
	
  return g_bioobject->DSS_FP_CapturedVerify(byteData,dwReadLen);
}


// 20080415 김철권 시작

enum SA_ERROR_RETURN
{
  SA_SUCCESS = 0,
		SA_FAIL,
		ER_INVALID_INPUT,
		ER_SA_EA_CAN_NOT_MAKE_CHALLENGE,
		ER_SA_EA_INSUFFICIENT_BUFFER_LEN,
		ER_SA_EA_CAN_NOT_MAKE_RESPONSE,
		EA_SA_EA_AUTHENTICATION_FAIL,
		ER_SA_EA_NO_RESPONSE,
		ER_SA_EA_NO_PROVER_CERT,
		ER_SA_EA_NO_PROVER_INFO,
		ER_SA_FAIL_STADDR_NULL,        // = 10
		ER_SA_FAIL_CONNECT,
		ER_SA_FAIL_SEND_DATALEN,
		ER_SA_FAIL_SEND_DATA,
		ER_SA_FAIL_CLOSED_SOCKET,
		ER_SA_FAIL_RCV_TIMEOUT,     //15
		ER_SA_FAIL_RCV_DATALEN,
		ER_SA_FAIL_RCV_INVALID_LEN,
		ER_SA_FAIL_RCV_DATA,
		ER_SA_FAIL_PKI_CLIENT_OP,
		ER_SA_FAIL_CONNECT_PKI, //20
		ER_SA_INVALID_ADD_RESPONSE,
		ER_SA_EA_INSUFFICIENT_MSG_TYPE,
		ER_SA_CARD_REMOVED,
		ER_SA_CERT_AND_KEY_LOAD_FAIL,
		ER_SA_EA_INVALID_AUTH_MECHANISM, //25
		ER_SA_INVALID_RESPONSE,
		ER_EA_FINGER_CAN_NOT_MAKE_RESPONSE,
		ER_EA_FINGER_CAN_NOT_SUPPORT_LIBRARY,
		ER_EA_FINGER_CAN_NOT_FIND_LIBRARY,
		ER_EA_FINGER_AUTH_VERIFY_FAILED, //30
		ER_EA_FINGER_CAN_NOT_FIND_DEVICE,
		ER_EA_FINGER_DRIVER_NOT_INSTALL,
		ER_EA_FINGER_CAN_NOT_INIT_DEVICE,
		ER_EA_FINGER_CAN_NOT_CAPTUER_USERDATA,
		ER_EA_FINGER_CONFIG_FAILURE,
		ER_VE_LOGOUTED = 50,             //  SSO 로그인 상태가 아닙니다
		ER_VE_FAIL_GET_CUR_USER_CN,
		ER_VE_FAIL_GET_CUR_USER_CERT_SERIAL,
		ER_VE_INVALID_SERIAL,
		ER_VE_TMAX_FAIL_READ_CONF_FILE,
		ER_VE_TMAX_FAIL_START = 55, 
		ER_VE_TMAX_FAIL_TRANS_DATA,
		ER_VE_ISIGN_NOT_INSTALLED,
		ER_VE_ISIGN_ENV,
		ER_VE_ISIGN_LOAD_LIBRARY,
		ER_VE_ISIGN_FIND_FUNC = 60,
		ER_VE_NO_SUCH_CERT,
		ER_VE_CERT_STATUS_REVOKE,
		ER_VE_CERT_STATUS_UNKNOWN,
		ER_VE_CERT_PERIOD_EXPIRED,
		ER_VE_UNKOWN 
};


typedef struct _FPSVRAUTHDLGPARAM
{
  int  resCode;
  char errStr[256];
  char name[32];
  char resid_hmac[32];
  char empNum[32];
}FPSVRAUTHDLGPARAM;


#define AR_INDEX_ON			  0
#define AR_INDEX_DOWN		  1
#define AR_INDEX_ROLLOVER	2
#define AR_INDEX_DISABLE	3

#define BTN_CTL_OK			  0
#define BTN_CTL_CANCEL	  1

#define IMGBTN_COUNT		  2 // 확인, 취소

static HBITMAP g_hBtnBmp_G[IMGBTN_COUNT][4]; // 녹색 OK, Cancel버튼
static BITMAP  g_bmBtnInfo_G[IMGBTN_COUNT];
static int	   arrCtrlRollover[IMGBTN_COUNT];

HWND   g_EmpFpDlgWnd = NULL; 
BOOL CALLBACK FPSvrAuthDlgProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam); 
LRESULT CALLBACK BtnProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
static WNDPROC BtnOldProc;

#if(_WIN32_WINNT < 0x0400)


//#define WM_MOUSELEAVE   WM_USER+2
//#define TME_LEAVE               1

//typedef struct tagTRACKMOUSEEVENT {
//	DWORD cbSize;
//	DWORD dwFlags;
//	HWND  hwndTrack;
//} TRACKMOUSEEVENT, *LPTRACKMOUSEEVENT;


VOID CALLBACK TrackMouseTimerProc(HWND hWnd,UINT uMsg,UINT idEvent,DWORD dwTime) {
	RECT rect;
	POINT pt;
	
	GetClientRect(hWnd,&rect);
	MapWindowPoints(hWnd,NULL,(LPPOINT)&rect,2);
	GetCursorPos(&pt);
	if (!PtInRect(&rect,pt) || (WindowFromPoint(pt) != hWnd)) {
		if (!KillTimer(hWnd,idEvent)) {
			// Error killing the timer!
		}
		
		PostMessage(hWnd,WM_MOUSELEAVE,0,0);
	}
}

BOOL TrackMouseEvent2(LPTRACKMOUSEEVENT ptme) {
	OutputDebugString(TEXT("TrackMouseEvent\n"));
	
	if (!ptme || ptme->cbSize < sizeof(TRACKMOUSEEVENT)) {
		OutputDebugString(TEXT("TrackMouseEvent: invalid "
			"TRACKMOUSEEVENT structure\n"));
		return FALSE;
	}
	
	if (!IsWindow(ptme->hwndTrack)) {
		OutputDebugString(
			TEXT("TrackMouseEvent: invalid hwndTrack\n"));
		return FALSE;
	}
	
	if (!(ptme->dwFlags & TME_LEAVE)) {
		OutputDebugString(TEXT("TrackMouseEvent: invalid dwFlags\n"));
		return FALSE;
	}
	
	return SetTimer(ptme->hwndTrack, ptme->dwFlags,	100,(TIMERPROC)TrackMouseTimerProc);
}
#endif

void LoadControlImage(HINSTANCE hInstance)
{
  // OK버튼
	g_hBtnBmp_G[BTN_CTL_OK][AR_INDEX_ON]          = (HBITMAP)LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BTN_G_OK_ON));
	g_hBtnBmp_G[BTN_CTL_OK][AR_INDEX_DOWN]        = (HBITMAP)LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BTN_G_OK_DOWN));
	g_hBtnBmp_G[BTN_CTL_OK][AR_INDEX_ROLLOVER]    = (HBITMAP)LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BTN_G_OK_OVER));
	g_hBtnBmp_G[BTN_CTL_OK][AR_INDEX_DISABLE]     = (HBITMAP)LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BTN_G_OK_ON));
	GetObject(g_hBtnBmp_G[BTN_CTL_OK][AR_INDEX_ON], sizeof(BITMAP), &g_bmBtnInfo_G[BTN_CTL_OK]);
	
	// 닫기
	g_hBtnBmp_G[BTN_CTL_CANCEL][AR_INDEX_ON]       = (HBITMAP)LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BTN_G_CANCEL_ON));
	g_hBtnBmp_G[BTN_CTL_CANCEL][AR_INDEX_DOWN]     = (HBITMAP)LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BTN_G_CANCEL_DOWN));
	g_hBtnBmp_G[BTN_CTL_CANCEL][AR_INDEX_ROLLOVER] = (HBITMAP)LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BTN_G_CANCEL_OVER));
	g_hBtnBmp_G[BTN_CTL_CANCEL][AR_INDEX_DISABLE]  = (HBITMAP)LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BTN_G_CANCEL_ON));
	GetObject(g_hBtnBmp_G[BTN_CTL_CANCEL][AR_INDEX_ON], sizeof(BITMAP), &g_bmBtnInfo_G[BTN_CTL_CANCEL]);
	
}

void DeleteControlImage()
{
	// OK버튼
  int i,j;
	
  for(i = 0; i < IMGBTN_COUNT ; i++) 
  {
    for(j = 0; j < 4 ; j++)
    {
      if(g_hBtnBmp_G[i][j] != NULL)
      {
        DeleteObject((HBITMAP)g_hBtnBmp_G[i][j]);
        g_hBtnBmp_G[i][j] = NULL;
      }
    }
  }
}

//김대형 ->winnt 버전에 상관없이 dss에서 사용됨..
VOID CALLBACK TrackMouseTimerProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime) {
	RECT rect;
	POINT pt;

	GetClientRect(hWnd, &rect);
	MapWindowPoints(hWnd, NULL, (LPPOINT)&rect, 2);
	GetCursorPos(&pt);
	if (!PtInRect(&rect, pt) || (WindowFromPoint(pt) != hWnd)) {
		if (!KillTimer(hWnd, idEvent)) {
			// Error killing the timer!
		}

		PostMessage(hWnd, WM_MOUSELEAVE, 0, 0);
	}
}

BOOL TrackMouseEvent2(LPTRACKMOUSEEVENT ptme) {
	OutputDebugString(TEXT("TrackMouseEvent\n"));

	if (!ptme || ptme->cbSize < sizeof(TRACKMOUSEEVENT)) {
		OutputDebugString(TEXT("TrackMouseEvent: invalid "
			"TRACKMOUSEEVENT structure\n"));
		return FALSE;
	}

	if (!IsWindow(ptme->hwndTrack)) {
		OutputDebugString(
			TEXT("TrackMouseEvent: invalid hwndTrack\n"));
		return FALSE;
	}

	if (!(ptme->dwFlags & TME_LEAVE)) {
		OutputDebugString(TEXT("TrackMouseEvent: invalid dwFlags\n"));
		return FALSE;
	}

	return SetTimer(ptme->hwndTrack, ptme->dwFlags, 100, (TIMERPROC)TrackMouseTimerProc);
}




LRESULT CALLBACK BtnProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static BOOL bMouseLeave = FALSE;
	TRACKMOUSEEVENT tme;
	
  HWND hParentWnd = GetParent(hWnd);
	if (GetActiveWindow() != hParentWnd)
		return CallWindowProc(BtnOldProc, hWnd, msg, wParam, lParam);
	
	switch(msg)
	{
	case WM_MOUSEMOVE:
		if (!bMouseLeave) {
			if (GetDlgItem(hParentWnd, IDOK) == hWnd)
				arrCtrlRollover[BTN_CTL_OK] = TRUE;
			if (GetDlgItem(hParentWnd, IDCANCEL) == hWnd)
				arrCtrlRollover[BTN_CTL_CANCEL] = TRUE;
      {			
        RECT rect;
        GetClientRect(hWnd, &rect);
        InvalidateRect(hWnd, &rect, FALSE);
      }
			bMouseLeave = TRUE;
			tme.cbSize = sizeof(TRACKMOUSEEVENT);
			tme.dwFlags = TME_LEAVE;
			tme.hwndTrack = hWnd;
			if (!TrackMouseEvent2(&tme)) {
				MessageBox(hWnd,
					TEXT("TrackMouseEvent Failed"),
					TEXT("Mouse Leave"),MB_OK);
			}
		}
		break;
		
	case WM_MOUSELEAVE:
		bMouseLeave = FALSE;
		arrCtrlRollover[BTN_CTL_CANCEL] = FALSE;
		arrCtrlRollover[BTN_CTL_OK] = FALSE;
    {
      RECT rect;
      GetClientRect(hWnd, &rect);
      InvalidateRect(hWnd, &rect, FALSE);
    }
    break;
	}	
	
	return CallWindowProc(BtnOldProc, hWnd, msg, wParam, lParam);
}


void DrawRoundedButton( HDC  dc,        //  Device context to draw on.
											 UINT ctrId,		  // ctrl ID
											 HWND hWnd,		  // hWnd
											 RECT rect,      //  The bounding box of the button.
											 int  defButton, //  1 if this is a default button.
											 int  pressed,   //  1 if the button is pressed.
											 int  focused,	  //  1 if the button has the focus.
											 int  disabled,  //  1 if the button has the disable.
											 HBITMAP   hBmp[IMGBTN_COUNT][4],
											 BITMAP   *bmp)  
{
	HBITMAP hBitmap[4] = { NULL, };
	BITMAP	Bmp = { 0, };
	
	HDC  hBtnMemDC = CreateCompatibleDC(dc);
	if (ctrId == IDOK)
	{
		hBitmap[AR_INDEX_ON]       = hBmp[BTN_CTL_OK][AR_INDEX_ON];
		hBitmap[AR_INDEX_DOWN]     = hBmp[BTN_CTL_OK][AR_INDEX_DOWN];
		hBitmap[AR_INDEX_ROLLOVER] = hBmp[BTN_CTL_OK][AR_INDEX_ROLLOVER];
		hBitmap[AR_INDEX_DISABLE]  = hBmp[BTN_CTL_OK][AR_INDEX_DISABLE];
		Bmp = bmp[BTN_CTL_OK];
		
    if (arrCtrlRollover[BTN_CTL_OK])
			defButton = 1;
	}
	else if (ctrId == IDCANCEL)
	{
		hBitmap[AR_INDEX_ON]       = hBmp[BTN_CTL_CANCEL][AR_INDEX_ON];
		hBitmap[AR_INDEX_DOWN]     = hBmp[BTN_CTL_CANCEL][AR_INDEX_DOWN];
		hBitmap[AR_INDEX_ROLLOVER] = hBmp[BTN_CTL_CANCEL][AR_INDEX_ROLLOVER];
		hBitmap[AR_INDEX_DISABLE]  = hBmp[BTN_CTL_CANCEL][AR_INDEX_DISABLE];
		Bmp = bmp[BTN_CTL_CANCEL];
		
		if (arrCtrlRollover[BTN_CTL_CANCEL])
			defButton = 1;
	}
	
	
	if( defButton || focused )
	{
		SelectObject(hBtnMemDC, hBitmap[AR_INDEX_ROLLOVER]);
		if (focused)
			SetFocus(hWnd);
	}
	else
	{
		SelectObject(hBtnMemDC, hBitmap[AR_INDEX_ON]);
	}
	
	if( pressed )
	{
		SelectObject(hBtnMemDC, hBitmap[AR_INDEX_DOWN]);
	}
	else
	{
		// 멀넣을까???
	}
	
	if (disabled)
	{
		SelectObject(hBtnMemDC, hBitmap[AR_INDEX_DISABLE]);
	}
	
	BitBlt(dc, 0, 0, Bmp.bmWidth, Bmp.bmHeight, hBtnMemDC, 0, 0, SRCCOPY);
	DeleteDC(hBtnMemDC);
}

void DrawItemBtn(LPDRAWITEMSTRUCT item, HBITMAP hBmp[IMGBTN_COUNT][4], BITMAP *bmp)
{
	DrawRoundedButton(item->hDC,
		item->CtlID,
		item->hwndItem,
		item->rcItem,
		item->itemState & ODS_DEFAULT,
		item->itemState & ODS_SELECTED,
		item->itemState & ODS_FOCUS,
		item->itemState & ODS_DISABLED,
		hBmp, bmp);
}

static BOOL CenterWindow(HWND hWnd)
{
  int  DlgWidth,DlgHeight,cxscreen,cyscreen,xLeft,yTop;
  RECT rcDlg;
	
  GetWindowRect(hWnd, &rcDlg);
  DlgWidth  = rcDlg.right  - rcDlg.left;
  DlgHeight = rcDlg.bottom - rcDlg.top;
  
  cxscreen  = GetSystemMetrics(SM_CXSCREEN);
  cyscreen  = GetSystemMetrics(SM_CYSCREEN);
  xLeft     = cxscreen / 2 - DlgWidth  / 2 ;
  yTop      = cyscreen / 2 - DlgHeight / 2 ;
  
	
  return SetWindowPos(hWnd, HWND_TOPMOST, xLeft, yTop, -1, -1,SWP_NOSIZE );
}

static int getICSServerInfo( char *svrIP, char *svrCert, int *svrPort)
{
  HKEY  hKey = NULL;
  LONG  lRet;
  DWORD dwType,dwRet;
  DWORD dwSize;
  CHAR  iSignPath[MAX_PATH];
  char  szCfgFile[MAX_PATH];
  char  szTmp[MAX_PATH];
	
  const PCHAR REG_ISIGN_PATH   = "SOFTWARE\\Penta Security Systems\\ISign\\Path\\";
  const PCHAR REG_ISSAC_COMMON = "SOFTWARE\\Penta Security Systems\\ISSAC Common\\";
  const PCHAR APP_SECTION      = "APP--ISign System Agent";
  
  //-------------------------------------------------------------------
  // 1. ISign 설치 폴더를 알아낸다
  //-------------------------------------------------------------------
  
  if(ERROR_SUCCESS !=  RegOpenKey(HKEY_LOCAL_MACHINE,REG_ISIGN_PATH, &hKey))
    return FAIL;
  
  dwSize = sizeof(iSignPath);
  lRet = RegQueryValueEx(hKey, "BinDir", 0, &dwType, (BYTE*)iSignPath, &dwSize);
  RegCloseKey(hKey);
  
  if(ERROR_SUCCESS != lRet) 
    return FAIL;
	
  //-------------------------------------------------------------------
  // 2. 환경파일의 위치를 알아낸다
  //-------------------------------------------------------------------
	
  if(ERROR_SUCCESS != RegOpenKey(HKEY_LOCAL_MACHINE,REG_ISSAC_COMMON, &hKey))
    return FAIL;
  
  dwSize = sizeof(szTmp);
  lRet = RegQueryValueEx(hKey, "conf_path", 0, &dwType, (BYTE*)szTmp, &dwSize);
  RegCloseKey(hKey);
  
  if(ERROR_SUCCESS != lRet) 
    return FAIL;
	
  dwRet = GetPrivateProfileString(APP_SECTION,"TMAX_ENV",NULL,szTmp,MAX_PATH,szTmp);
  if(dwRet < 1 )   return FAIL;
	
  _snprintf(szCfgFile,sizeof(szCfgFile),"%s\\%s",iSignPath,szTmp);
  
  //-------------------------------------------------------------------
  // 3. 환경 파일 ini 읽기
  //-------------------------------------------------------------------
	
  *svrPort = GetPrivateProfileInt("ICS", "ICS_PORT", 0, szCfgFile);
  if(*svrPort == 0)
    return FAIL;
	
  dwRet = GetPrivateProfileString("ICS","ICS_ADDR",NULL,svrIP,MAX_IP_LEN,szCfgFile);
  if(dwRet < 1 )   return FAIL;
  dwRet = GetPrivateProfileString("ICS","ICS_CERT",NULL,szTmp,MAX_PATH,szCfgFile);
  if(dwRet < 1 )   return FAIL;
	
	_snprintf(svrCert,MAX_PATH,"%s\\%s",iSignPath,szTmp);
  return SUCCESS;
}


static BOOL CaptureBioData(OUT char *pBioData, IN const UINT bioDataAlloc, OUT int *pBioDataLen, OUT char *errMsg, OUT int *pErrCode)
{
  CHAR    *tmpFPdata = NULL;
  INT      ret = 0,tmpFPDataLen = 0;
	
  ret = DSS_FP_Capture(&tmpFPdata, &tmpFPDataLen);
  if( ret == SUCCESS )
  {
    assert( tmpFPDataLen <= (signed)bioDataAlloc);
    memcpy( pBioData, tmpFPdata, tmpFPDataLen );
    *pBioDataLen = tmpFPDataLen;
  }
  else // DSS_FP_Capture fail
  {
    *pErrCode = ER_EA_FINGER_CAN_NOT_CAPTUER_USERDATA;
    strcpy( errMsg , "ER_EA_FINGER_CAN_NOT_CAPTUER_USERDATA(사용자의 지문을 획득하는데 실패하였습니다.(%d) )");
  }
  
  return (ret == SUCCESS) ? TRUE : FALSE;
}

static BOOL VerifyBioDataByICS( IN char *pEmpNum, IN char *pB64FPData, OUT FPSVRAUTHDLGPARAM *pDlgParam)
{

	HKEY  hKey = NULL;
	char szPathName[MAX_PATH] = {0};
	DWORD	dwSize = sizeof(szPathName);
	DWORD	dwType = REG_SZ;


  typedef int (*F_VerifyByICS) (char*, int, char*, char*, char*, char*, char*, char*, char*, char*,int*,char*);
  F_VerifyByICS VerifyByICS;
  HMODULE hModule;
  
  char desc[256] = {0,}, svrIP[MAX_IP_LEN] = {0,}, svrCert[MAX_PATH] = {0,}, *pTmp;
  int  svrPort, resCode;
	
  // 1. 서버 접속정보 읽기
  if ( SUCCESS != getICSServerInfo( svrIP, svrCert, &svrPort) )
  {
    pDlgParam->resCode = ER_EA_FINGER_CONFIG_FAILURE;
    strcpy( pDlgParam->errStr, 
			"ER_EA_FINGER_CONFIG_FAILURE(지문서버 환경 구성에 실패했습니다. dssptok.env파일을 확인해 주세요)");
    return FALSE;
  } 
	
  // 2. 서버에 검증요청

	// 경로얻기 추가.
	if(ERROR_SUCCESS == RegOpenKey(HKEY_LOCAL_MACHINE,"SOFTWARE\\Penta Security Systems\\ISign\\Path\\", &hKey))
	{
		dwSize = sizeof(szPathName);
		dwType = REG_SZ;
		if(ERROR_SUCCESS == RegQueryValueEx(hKey, "BinDir", 0, &dwType, (BYTE*)szPathName, &dwSize))
		{
			strcat(szPathName,"\\ICS_Client.dll");
		}  // RegQueryValueEx
		else
		{
			strcpy(szPathName, "ICS_Client.dll");
		}
	} // RegOpenKey
	else
	{
		strcpy(szPathName, "ICS_Client.dll");
	}
	RegCloseKey(hKey);

  hModule = LoadLibraryEx(szPathName, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
  if(NULL == hModule)
  {
    pDlgParam->resCode = ER_EA_FINGER_CAN_NOT_FIND_LIBRARY;
    strcpy(pDlgParam->errStr, "CAN_NOT_FIND_LIBRARY(지문인증 라이브러리<ICS_Client.dll>를 찾을 수 없습니다)");
    return FALSE;
  }
	
  VerifyByICS = (F_VerifyByICS)GetProcAddress(hModule, "VerifyByICS");
  if ( NULL == VerifyByICS )
  {
    pDlgParam->resCode = ER_EA_FINGER_CAN_NOT_SUPPORT_LIBRARY;
    strcpy( pDlgParam->errStr, 
			"ER_EA_FINGER_CAN_NOT_SUPPORT_LIBRARY(지문인증 라이브러리(ICS_Client.dll의 버전이 맞지 않습니다)"); 
		
    FreeLibrary(hModule);
    return FALSE;
  }
	
  VerifyByICS( svrIP, svrPort, svrCert, "BBB", "1.1.1.1", "1111", "BE", pEmpNum, "", pB64FPData, &resCode, desc); 
  if ( resCode != SUCCESS )
  {
    pDlgParam->resCode = resCode;
    sprintf(pDlgParam->errStr,"ER_EA_FINGER_AUTH_VERIFY_FAILED(지문 인증 실패 - %s)", desc);
    return FALSE;
  }
	
  pTmp = strstr(desc,"_");
  strncpy(pDlgParam->name, desc, pTmp-desc);
  strcpy(pDlgParam->resid_hmac, pTmp+1);
  strcpy(pDlgParam->empNum, pEmpNum);
  pDlgParam->resCode = SUCCESS;
	
  return TRUE;
}

//
// 2008.3.17 김 상 학
// 행번과 지문캡쳐창을 하나로 해달라는 국민은행의 요청
// 지문캡쳐창은 니트젠에서 제공하는 모듈이고 이를 수정할 수 없어서
// 그럴듯하게 보이도록 대화상자를 만듬
//
BOOL CALLBACK FPSvrAuthDlgProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
  static FPSVRAUTHDLGPARAM *pDlgParam;
	static HBITMAP hInfoBit;

  switch(iMsg)
	{
	case WM_INITDIALOG:
    g_EmpFpDlgWnd = hwnd;
		pDlgParam     = (FPSVRAUTHDLGPARAM*)(lParam);
    ZeroMemory(pDlgParam, sizeof(FPSVRAUTHDLGPARAM));
    hInfoBit   = LoadBitmap((HINSTANCE)g_instance, MAKEINTRESOURCE(IDB_SVRFPAUTH_INNER_BODY_G));
 		//김대형
	    BtnOldProc = (WNDPROC)SetWindowLong(GetDlgItem(hwnd, IDOK),     GWLP_WNDPROC, (LONG)BtnProc);
		BtnOldProc = (WNDPROC)SetWindowLong(GetDlgItem(hwnd, IDCANCEL), GWLP_WNDPROC, (LONG)BtnProc);
    
    SetWindowText(hwnd,"서버지문인증 요청");
    SetFocus(hwnd);

		CenterWindow(hwnd); 

    SetForegroundWindow(hwnd);
 	return FALSE;


  case WM_CLOSE:
	  //김대형
    SetWindowLong(GetDlgItem(hwnd, IDCANCEL), GWLP_WNDPROC, (LONG)BtnOldProc);
    DeleteObject(hInfoBit);
    return TRUE;

	case WM_DRAWITEM:
		if (((LPDRAWITEMSTRUCT)lParam)->hwndItem == GetDlgItem(hwnd, IDOK) ||
	  		((LPDRAWITEMSTRUCT)lParam)->hwndItem == GetDlgItem(hwnd, IDCANCEL) )
			DrawItemBtn((LPDRAWITEMSTRUCT)lParam, g_hBtnBmp_G, g_bmBtnInfo_G);
    return TRUE;

	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
			case IDCANCEL:
				EndDialog(hwnd,IDCANCEL);
				return FALSE;
      
      case IDOK:
			{
        int  ret = FAIL, FPDataLen = 0, inputEmpNumLen;
        HMODULE hModule = NULL;
        char FPData[2048] = {0,};
        char szEncordFPData[4096] = {0,};
        const int ENUM_LEN = 7;

        //////////////////////////////////////////////////////////////////////////
        // 1. 행번 체크 
        //////////////////////////////////////////////////////////////////////////

				char szEmpNum[32] = {0,};
				GetDlgItemText(hwnd, IDC_EDIT_EMP, szEmpNum, sizeof(szEmpNum));
        inputEmpNumLen = strlen(szEmpNum);
				if (inputEmpNumLen == 0)
				{
					MessageBox(hwnd, "행번을 입력하여 주십시오.", "알림", MB_OK | MB_ICONINFORMATION);
					SetFocus(hwnd);
					SetFocus(GetDlgItem(hwnd, IDC_EDIT_EMP));
					return FALSE;
				}
        else if ( inputEmpNumLen > ENUM_LEN )
        {
					MessageBox(hwnd, "입력하신 행번의 길이가 너무 깁니다.\n행번을 확인하여 주십시오.", "알림", MB_OK | MB_ICONINFORMATION);
					SetFocus(hwnd);
					SetFocus(GetDlgItem(hwnd, IDC_EDIT_EMP));
					return FALSE;
        }


        // 행번과 관련된 UI를 숨긴다.
        ShowWindow(GetDlgItem(hwnd, IDC_EDIT_EMP),SW_HIDE);
        ShowWindow(GetDlgItem(hwnd, IDOK),        SW_HIDE);
        ShowWindow(GetDlgItem(hwnd, IDCANCEL),    SW_HIDE);

        //////////////////////////////////////////////////////////////////////////
        // 2. 지문 캡쳐
        //////////////////////////////////////////////////////////////////////////
        
        if( !CaptureBioData(FPData, sizeof(FPData), &FPDataLen, pDlgParam->errStr, &pDlgParam->resCode ))
        {
          EndDialog(hwnd,IDOK);
          return FALSE;
        }

        Base64_Encode(szEncordFPData, sizeof(szEncordFPData), (LPBYTE)FPData, FPDataLen);

        
        // 안내창을 보인다.
        {
          HDC MemDC,hdc;
          HBITMAP OldBitmap;
          int bx,by;
          BITMAP bit;
          hdc         = GetDC(hwnd);
          MemDC       = CreateCompatibleDC(hdc);
          OldBitmap   = (HBITMAP)SelectObject(MemDC, hInfoBit);
          
          GetObject(hInfoBit,sizeof(BITMAP),&bit);
          bx = bit.bmWidth;
          by = bit.bmHeight;
          
          BitBlt(hdc,22,27,bx,by,MemDC,0,0,SRCCOPY);
          SelectObject(MemDC,OldBitmap);
          DeleteDC(MemDC);
          ReleaseDC(hwnd,hdc);
        }

        //////////////////////////////////////////////////////////////////////////
        // 3. 행번과 지문을 서버에 검증 요청한다.
        //////////////////////////////////////////////////////////////////////////
 
        // 안내메시지
        VerifyBioDataByICS(szEmpNum,szEncordFPData,pDlgParam);

        EndDialog(hwnd,IDOK);
        return FALSE;
      } // IDOK
		}
		return TRUE;
	}

	return FALSE;
}


int DSS_FP_VerifyWithICS(int *errCode, char* errMsg, char *name, char *resid_hmac, char *empNum, int onlyICS)
{
	int ret;
	
	if (1 != onlyICS)
	{
		DSS_FP_Destroy();
		DSS_FP_Initialize(NULL, 0, 1);
		char *sp;
		ret = DSS_FP_Verify(&sp);

		if (SUCCESS == ret)
		{
			*errCode = 0;
			DSS_FP_Destroy();
			return ret;
		}
		else
		{
			int nErrCode = DSS_FP_GetErrorCode();
			switch(nErrCode)
			{
				case 8000: break;	// 토큰 리더기를 오픈하지 못했습니다
				case 8001: break; // 보안토큰가 존재하지 않습니다
				case 8002: break; // 보안토큰가 정상적으로 동작하지 않습니다
				case 8003: break; // 보안토큰가 잠김상태 입니다
				case 8004: break; // 비 정상적인 보안토큰 입니다
				case 8005: break; // 보안토큰 또는 리더기가 정상적으로 동작하지 않습니다
				case 8008: break; // 보안토큰에 지문정보가 존재하지 않습니다
				case 8010: break; // 보안토큰의 지문정보가 비정상적입니다
				case 8018: break; // 현재 보안토큰는 지문인증을 사용 할수 없는 토큰입니다.
				default: 
					{
					*errCode = nErrCode;
					strcpy(errMsg, DSS_FP_GetErrorStr());
					DSS_FP_Destroy();
					return ret;
					}
			}
		}
	}

	FPSVRAUTHDLGPARAM dlgParam;
	DSS_FP_Destroy();
	DSS_FP_Initialize(NULL, 1, 1);
	ret = DialogBoxParam((HINSTANCE)g_instance, MAKEINTRESOURCE(IDD_EMP_FP), NULL, (DLGPROC)FPSvrAuthDlgProc,(LPARAM)&dlgParam);
	if ( IDOK == ret )
	{
		if(SUCCESS == dlgParam.resCode)
		{
			strcpy(name,       dlgParam.name);
			strcpy(resid_hmac, dlgParam.resid_hmac);
			strcpy(empNum,     dlgParam.empNum);
			
			*errCode = 0;
			DSS_FP_Destroy();
			return SUCCESS;
		}
		else
		{
			strcpy(errMsg, dlgParam.errStr);
			*errCode = dlgParam.resCode;
			DSS_FP_Destroy();
			return SUCCESS;
		}
	}
	else
	{
		strcpy(errMsg, "FINGER_AUTH_VERIFY_FAILED(지문 검증에 실패하였습니다. 사용자가 취소 하였습니다)");
		*errCode = ER_EA_FINGER_AUTH_VERIFY_FAILED; 
		DSS_FP_Destroy();
		return -1;
	}	
}


int __stdcall DSS_FP_VerifyWithICSStd(int *errCode, char* errMsg, char *name, char *resid_hmac, char *empNum, int onlyICS)
{
	return DSS_FP_VerifyWithICS(errCode, errMsg, name, resid_hmac, empNum, onlyICS);
}

// 20080415 김철권 끝



int DSS_FP_Enroll(TCHAR * strpayload)
{
	INIT;

  if(g_bioobject==NULL)
  {
    LOGPRINT("DSS_FP_Initialize를 호출하지 않았습니다.",7001);
    return DSS_FAILED;
  }
  return g_bioobject->DSS_FP_Enroll(strpayload);
}

int DSS_FP_EnrollEx(TCHAR * strpayload, char *readername)
{
	INIT;
	
  if(g_bioobject==NULL)
  {
    LOGPRINT("DSS_FP_Initialize를 호출하지 않았습니다.",7001);
    return DSS_FAILED;
  }
  return g_bioobject->DSS_FP_EnrollEx(strpayload, readername);
}

int __stdcall  DSS_FP_VerifyStd(TCHAR ** strpayload)
{

  return DSS_FP_Verify(strpayload);
}

int DSS_FP_Verify(TCHAR ** strpayload)
{
  INIT;
///
  return g_bioobject->DSS_FP_Verify(strpayload);
}

int __stdcall  DSS_FP_VerifyStdEx(TCHAR ** strpayload, char *readername)
{
	
  return DSS_FP_VerifyEx(strpayload, readername);
}

int DSS_FP_VerifyEx(TCHAR ** strpayload,char *readername)
{
  INIT;
	///
  return g_bioobject->DSS_FP_VerifyEx(strpayload, readername);
}

int DSS_FP_SetEnumDevice(int device_id)
{
  return ((CNBioApi*)g_bioobject)->DSS_FP_SetEnumDevice(device_id);
}


int DSS_FP_EnumDevice(DSS_FP_ENUMDEVICE_INFO **device_list)
{

  INIT;
  return g_bioobject->DSS_FP_EnumDevice(device_list);
}

int __stdcall DSS_FP_ChangePayloadStd(TCHAR *strPayload,bool flag)
{

  return DSS_FP_ChangePayload(strPayload,flag);
}

int __stdcall DSS_FP_ChangePayloadStdEx(TCHAR *strPayload,bool flag, char *readername)
{
	
  return DSS_FP_ChangePayloadEx(strPayload,flag, readername);
}

int DSS_FP_ChangePayload(TCHAR *strPayload,bool flag)
{
  INIT;
  return g_bioobject->DSS_FP_ChangePayload(strPayload,flag);
}

int DSS_FP_ChangePayloadEx(TCHAR *strPayload,bool flag, char *readername)
{
  INIT;
  return g_bioobject->DSS_FP_ChangePayloadEx(strPayload,flag, readername);
}

DSS int __stdcall DSS_FP_CheckCardFingerStd()
{

  return DSS_FP_CheckCardFinger();
}

DSS int DSS_FP_CheckCardFinger()
{
  INIT;
  return g_bioobject->DSS_FP_CheckCardFinger();
}

DSS int __stdcall DSS_FP_CheckCardFingerStdEx(char *readername)
{
	
  return DSS_FP_CheckCardFingerEx(readername);
}

DSS int DSS_FP_CheckCardFingerEx(char *readername)
{
  INIT;
  return g_bioobject->DSS_FP_CheckCardFingerEx(readername);
}

DSS int DSS_FP_GetControlUnitTime(int *npStartTick, int *npCapture_StartTick, int *npCapture_EndTick)
{
	INIT;
	return g_bioobject->DSS_FP_GetControlUnitTime(npStartTick, npCapture_StartTick, npCapture_EndTick);
}

DSS int DSS_FP_SetEnrollSecurityLevel(unsigned int secuLevel)
{
	INIT;
	return g_bioobject->DSS_FP_SetEnrollSecurityLevel(secuLevel);
}

DSS int DSS_FP_SetVerifySecurityLevel(unsigned int secuLevel)
{
	INIT;
	return g_bioobject->DSS_FP_SetVerifySecurityLevel(secuLevel);
}


int __stdcall DSS_FP_CardClearStd()
{
  return DSS_FP_CardClear();
}

int DSS_FP_CardClear()
{

  int len=sizeof(NBioAPI_FIR_FORMAT)+sizeof(NBioAPI_FIR_HEADER);
  unsigned char buffer[512]={0};
  	// scmod 로 쓰기
  if( WriteFIRToScard( buffer, 512 ) != 1 )
  {
    return DSS_FAILED;
  }
	
  return 0;
}

LPCSTR __stdcall DSS_FP_GetErrorStrStd()
{
  
  return DSS_FP_GetErrorStr();
}

LPCSTR DSS_FP_GetErrorStr()
{

  return (LPCSTR)g_errorstr;
}


int DSS_FP_GetErrorCode()
{
 
  
  return g_fperror.GetErrorCode();
}


int __stdcall DSS_FP_GetErrorCodeStd()
{

  return DSS_FP_GetErrorCode();
}



void DSS_FP_CreateAnimationCtrl() 
{ 

    HWND hwndAnim = NULL; 
    RECT rc; 
    POINT pt; 

  
    hwndAnim = Animate_Create(g_hwndDlg,100/* IDC_ANIMATE*/, 
         WS_CHILD, (HINSTANCE)g_instance); 

    // Get the screen coordinates of the specified control button. 
    GetWindowRect(g_hwndDlg, &rc); 

    // Convert the coordinates of the lower-left corner to 
    // client coordinates. 
   // pt.x = rc.left; 
  //  pt.y = rc.bottom; 
   // ScreenToClient(g_hwndDlg, &pt); 


    pt.x=(rc.right-rc.left-131)/2;
    pt.y=(rc.bottom-rc.top-60);
    // Position the animation control below the Stop button. 
    SetWindowPos(hwndAnim, 0, pt.x, pt.y , 
        131, 9, 
        SWP_NOZORDER | SWP_DRAWFRAME); 

    // Open the AVI clip, and show the animation control. 
    
    BOOL resut=Animate_Open(hwndAnim, IDR_AVI1); 

    ShowWindow(hwndAnim, SW_SHOW); 

    g_hwndAnim=hwndAnim;
    //ShowWindow(g_hwndAnim,SW_HIDE);
    
    return ; 
} 

void DSS_FP_CloseAnimationCtrl() 
{

  Animate_Stop(g_hwndAnim);

  Animate_Close(g_hwndAnim);

}

void MyThread(void * )
{
  BOOL bRet;
  MSG msg;

//	HWND hwndGoto = CreateDialog((HINSTANCE)g_instance,(LPCTSTR)IDD_DSS_FP_DIALOG,g_hparentwnd,(DLGPROC)DSS_FP_PROC);
  HWND hwndGoto = CreateDialog((HINSTANCE)g_instance,(LPCTSTR)IDD_DSS_FP_DIALOG,NULL,(DLGPROC)DSS_FP_PROC); // 20070919 김철권 버그수정(-_-;;)
	
	// 부모가 포커스를 받지못해서 SendMessage()를 호출해서 포커스를 줌. 김철권(20070528)
	::SendMessage(g_hparentwnd, WM_SETFOCUS, (WPARAM)hwndGoto, 0);

  while ( (bRet = GetMessage(&msg,NULL , 0, 0)) != 0 ) 
  {   
      if (bRet == -1 )
      {
        //break;
          // handle the error and possibly exit
      }
      else if (!IsWindow(g_hwndDlg) || !IsDialogMessage(g_hwndDlg, &msg)) 
      { 
          TranslateMessage(&msg); 
          DispatchMessage(&msg); 
      } 
  }
 
  DSS_FP_PROC(NULL,UM_DESTROY, 0, 0);

}

void DSS_FP_PlayAnimationCtrl(LPCSTR str)
{

  if(str!=NULL)
    SendMessage(g_hwndDlg,UM_SETTEXT,0,(LPARAM)str);
  ShowWindow(g_hwndDlg,SW_SHOW);

//	if (g_bDirectDisplay) 
	{
		SendMessage(g_hwndDlg, WM_PAINT, 0, 0);
	}
	
  //ShowWindow(g_hwndAnim,SW_SHOW);
  BOOL result=Animate_Play(g_hwndAnim,0,-1,-1);
}

void DSS_FP_StopAnimationCtrl()
{
  Animate_Stop(g_hwndAnim);
  //ShowWindow(g_hwndAnim,SW_HIDE);
  ShowWindow(g_hwndDlg,SW_HIDE);
}

int DSS_FP_Test(HWND h)
{

  static int ak=0;


  if(ak==0)
  {

    DSS_FP_Initialize(h);
    Sleep(500);

    DSS_FP_PlayAnimationCtrl();

    ak=1;
  }
  else
  {

    DSS_FP_StopAnimationCtrl();
    ak=0;
  }

  return 0;
}

int CBioApiObject::DSS_FP_Initialize(HWND hwnd,int flag)
{ 
  
  m_init++;
  
  if(m_init>1)
  {
    return 0;
  }
  

  if(g_threadid!=0)
  {
    LOGPRINT("이미 DSS_FP_Initialize를 호출했습니다.",7002);
    return DSS_FAILED;
  }
  
  m_resource=g_resource=flag;
  
  
  g_hparentwnd=hwnd;
  
// 20070831 김철권 시작
	if(g_threadid==0) {

    g_threadid=(HANDLE)_beginthread(MyThread,0,NULL);

	}
// 20070831 김철권 끝  
 
 // BOOL bRet;
  //MSG msg;
  
  //msg_wait(g_threadid,INFINITE);

 /* while(1)
  {
    MsgWaitForMultipleObjects(1,&g_threadid,FALSE,INFINITE,QS_ALLEVENTS);
   
    
    if( (bRet = GetMessage(&msg,NULL , 0, 0)) != 0 ) 
    {   
      
    *//*  if (bRet == -1 )
      {
        //break;
        // handle the error and possibly exit
      }
      else if (!IsWindow(g_hwndDlg) || !IsDialogMessage(g_hwndDlg, &msg)) *//*
      
      { 
        TranslateMessage(&msg); 
        DispatchMessage(&msg); 
      }
      
      if(g_hwndDlg)
        break;
    }
    
  };*/
  

  return DSS_FP_Init();
}

void CBioApiObject::DSS_FP_Destroy()
{

  if(m_init>1)
  {
    m_init--;
    return;
  }
  
  m_init=0;
  DSS_FP_Destroy_nBio();
  DSS_FP_Destroy_Object();
}

void CBioApiObject::DSS_FP_Destroy_Object()
{
  
  if(g_threadid==0)
    return ;
  
  
  
  
  if(g_hwndDlg)
  {
    PostMessage(g_hwndDlg,WM_QUIT,0,0);
    g_hwndDlg=NULL;
    WaitForSingleObject(g_threadid,INFINITE);
  }
  
  g_threadid=0;
  
  //delete g_bioobject;
  g_bioobject=NULL;
}

void CBioApiObject::Error(int err)
{

    if(err==16777480)
    {
      LOGPRINT("지문 장치를 오픈할 수 없습니다.",8015);  
    }
    else if(err==16777496)
    {
      LOGPRINT("작업을 취소했습니다.",8016);
    }
    else if(err==16777486)
    {
      LOGPRINT("지문 인증 시간을 초과했습니다.",8017);
    }
    else 
    {
      LOGPRINT("지문 검증에 실패했습니다.",8009);
    }
}

