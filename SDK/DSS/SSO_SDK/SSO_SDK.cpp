  // SSO_SDK.cpp : Defines the entry point for the DLL application.
//
#include "Winsock2.h"
#include "stdafx.h"
#include "SSO_SDK.h"
#include "ISignDtpDLL.h"
#include "DllLoad.h"
#include "resource.h"
#include "stdio.h"


#define CERT_STATUS_GOOD    (0x00)
#define CERT_STATUS_REVOKE  (0x01)
#define CERT_STATUS_UNKNOWN (0x02)

#define CERT_PERIOD_VALID      (0x00)
#define CERT_PERIOD_NOTVALID   (0x01)

#define RET_RECV_ERROR         100


#define STATUS_GOOD_AND_PERIOD_VALID      (0x00)
#define STATUS_GOOD_AND_PERIOD_NOTVALID   (0x01)
#define STATUS_REVOKE_AND_PERIOD_VALID    (0x02)
#define STATUS_REVOKE_AND_PERIOD_NOTVALID (0x03)


#define REG_SSOSDK_KEY							TEXT("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon\\Notify\\ssosdk")
#define REG_SSOSDK_EVENT_WINDOWNAME TEXT("EventWindowName")

#define SEND_EVENT_ID        TEXT('D')
#define SEND_EVENT_SRCFRAME  TEXT("SSO")
#define SEND_EVENT_DSTFRAME  TEXT("JBT")
#define SEND_EVENT_LOCK      TEXT("LOCK")
#define SEND_EVENT_UNLOCK    TEXT("UNLOCK")
#define SEND_EVENT_DWDATA    200

HINSTANCE g_hInst;
enum SCREENLOCK_
{
	SCREEN_LOCK = 0,
	SCREEN_UNLOCK
};

SCREENLOCK_ g_nLock;


static INT IsIFLogon(void);

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved )
{
	g_hInst = (HINSTANCE)hModule;
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
		break;
   }
   
	return TRUE;
}







//����������������������������������������������������������������������������������
//��                                                                              ��
//��                          IF_VerifyEmp			                                  ��
//��  2004. 08.23 �����                                                          ��
//��                                                                              ��
//��  1.  �Է°� ����				                                                      ��
//��  2.  SSO�� �α��� �������� ����                                              ��
//��  3.  ������ ��Ŷ ���ϱ� (CN,Serial)                                          ��
//��  4.  TMAX ����							                                                  ��
//��  5.  send    							                                                  ��
//��  6.  receive 							                                                  ��
//��  7.  ����� return 				                                                  ��
//����������������������������������������������������������������������������������
INT SSO_VerifyEmp(INT   *pResult,							
				  				 TCHAR *pszEmpNum, 	INT   *pEmpNumLen,
									 TCHAR *pszEmpName,	INT   *pEmpNameLen)
{
	// return code 
  enum {
		VE_SUCCESS =  0,
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
  // 1 . �Է°� ����
	//---------------------------------------------------------------
	if( pszEmpNum    <= 0  || 
		  *pEmpNumLen  <= 7  ||
	  	pszEmpName   <= 0  || 
			*pEmpNameLen <= 5 ) 
	{
		*pResult =	VE_INVALID_INPUT;
		OutputDebugString("SSO_VerifyEmp - �Է°� ���� ����\n");
		return FAIL;
	}


	//---------------------------------------------------------------
  // 2 . ISignDtp.dll Load
	//---------------------------------------------------------------

	// 2-1. dll load
	CISignDtpDLL ISignDllOBJ;
	int ret = ISignDllOBJ.LoadDLL("isigndtp.dll");
	if(ret != SUCCESS) 
	{
		if(ret == 3) {
			*pResult = VE_ISIGN_NOT_INSTALLED;
		}
		else if ( ret == 4) {
		  *pResult = VE_ISIGN_ENV_ERROR;
		}
		else {
			// VE_ISIGN_CAN_NOT_LOAD_LIBRARY
			// VE_ISIGN_CAN_NOT_FIND_FUN
			*pResult = ret;  
		}
		OutputDebugString("SSO_VerifyEmp - ISignDtop load ����\n");

		return FAIL;
	}

  //---------------------------------------------------------------
  // 2 . SSO�� �α��� �������� �˾Ƴ���
	//---------------------------------------------------------------
	if(ISignDllOBJ.IsLogin()==FALSE) 
	{
		*pResult = VE_LOGOUTED; // not login
		OutputDebugString("SSO_VerifyEmp - IsLogin logout������\n");
		return FAIL;
	}

	//---------------------------------------------------------------
  // 3 .  ������ ��Ŷ ���ϱ� 
	// 3-1. CN
	// 3-2. Cert Serial
	// 3-3. ���� �����
	//---------------------------------------------------------------

	// 3-1. CN ���ϱ�
	TCHAR szCN[MAX_PATH] = {0,};
  int   nCNSize        = sizeof(szCN);

	if( 1 != ISignDllOBJ.GetCurUserID(szCN,nCNSize) )
	{
		*pResult = VE_FAIL_GET_CUR_USER_CN; // cn ���Ҽ� ����
		OutputDebugString("SSO_VerifyEmp - CN���� �� ����\n");
		return FAIL;
	}
  
  // 3-2. serial ���ϱ�
	TCHAR szCert[2048] = {0,};
  int   nCertLen     = sizeof(szCert);

	 if( 1 != ISignDllOBJ.GetCurUserPKICert(szCert,&nCertLen,nCertLen))
	{
		*pResult = VE_FAIL_GET_CUR_USER_CERT_SERIAL;  // serial ���� �� ����
		OutputDebugString("SSO_VerifyEmp - serial���ϱ� \n");
		return FAIL;
	}

	TCHAR   szSerial[MAX_PATH] = {0,};
	int     serialMaxLen       = sizeof(szSerial);
	
	// ssa.dll  �ε� 

	TCHAR	szISSACPath[MAX_PATH] = {0,};

	if( GetISSACFileDirectory(szISSACPath) == TRUE )
		_tcscat(szISSACPath, _T("\\"));
	
	_tcscat(szISSACPath, _T("ssa.dll"));

	HMODULE hModule = LoadLibraryEx(szISSACPath,0, LOAD_WITH_ALTERED_SEARCH_PATH);
 
	if(hModule == NULL) 
	{
		*pResult = VE_ISIGN_CAN_NOT_LOAD_LIBRARY;
		OutputDebugString("SSO_VerifyEmp - ssa.dll�ε���� \n");
		return FAIL;
	}

	typedef struct _SSACert {
  void *certificate;  /* CIS Certificate type */
  void *parameter;    /* CIS Parameter */
	} SSACert; 

	typedef (*F_BG_SSACert_Create)(SSACert *cert);
	typedef (*F_BG_SSACert_ReadMemory)(SSACert *cert,
                                     const char *certBuf, int certBufLen,
                                     const char *paramBuf, int paramBufLen);
  typedef (*F_BG_SSACert_GetSerialNumber)(char *serial, int serialMaxLen, SSACert *cert);
  typedef (*F_BG_SSACert_Delete)(SSACert *cert);

	F_BG_SSACert_Create           fBG_SSACert_Create     = (F_BG_SSACert_Create)           GetProcAddress(hModule,"BG_SSACert_Create");
  F_BG_SSACert_ReadMemory       fBG_SSACert_ReadMemory = (F_BG_SSACert_ReadMemory)      GetProcAddress(hModule,"BG_SSACert_ReadMemory");
	F_BG_SSACert_GetSerialNumber  fBG_SSACert_GetSerialNumber = (F_BG_SSACert_GetSerialNumber) GetProcAddress(hModule,"BG_SSACert_GetSerialNumber");
  F_BG_SSACert_Delete           fBG_SSACert_Delete     = (F_BG_SSACert_Delete)          GetProcAddress(hModule,"BG_SSACert_Delete");

	if(fBG_SSACert_Create          == NULL ||	fBG_SSACert_ReadMemory == NULL ||
		 fBG_SSACert_GetSerialNumber == NULL || fBG_SSACert_Delete     == NULL ) 
	{
		*pResult = VE_ISIGN_CAN_NOT_FIND_FUN;
		return FAIL;
	}

	SSACert cert;
	fBG_SSACert_Create(&cert);
	fBG_SSACert_ReadMemory(&cert,szCert,nCertLen,NULL,0);
  fBG_SSACert_GetSerialNumber(szSerial, serialMaxLen,&cert);
	fBG_SSACert_Delete(&cert);
/*
  SSACert cert;
	BG_SSACert_Create(&cert);
	BG_SSACert_ReadMemory(&cert,szCert,nCertLen,NULL,0);
  BG_SSACert_GetSerialNumber(szSerial, serialMaxLen,&cert);
	BG_SSACert_Delete(&cert);
*/
	// serial �� üũ
	if(strlen(szSerial) != CERT_SERIAL_SIZE)
	{
		*pResult = VE_INVALID_SERIAL;
		OutputDebugString("SSO_VerifyEmp - serial �� üũ ����\n");
		return FAIL;
	}

  // 3-2. ���� �����

	TCHAR sendBuf[MAX_PATH] = {0,};
	sendBuf[0] = (char)0xca;
	sendBuf[1] = 1/*(char)0xca*/ + 1 /*sendBuf[1]*/+ strlen(szSerial) + strlen(szCN) +1 /*NULL*/ ;
	memcpy(sendBuf+2,szSerial,strlen(szSerial));
	memcpy(sendBuf+2 + strlen(szSerial), szCN,strlen(szCN)+1);

	//---------------------------------------------------------------
  // 4 . TMAX ����
	//---------------------------------------------------------------

	// 4-1. issac-file���� ����.
	HKEY  hKey;
	LONG  regRet;
	char  pszFullFileName[MAX_PATH];
	DWORD len  = MAX_PATH;

	regRet = RegOpenKeyEx( HKEY_LOCAL_MACHINE,
												 "SOFTWARE\\Penta Security Systems\\ISSAC-File",
 												 0,  KEY_ALL_ACCESS,  &hKey);	

	if(regRet != ERROR_SUCCESS) return -1;
	
	regRet = RegQueryValueEx(hKey, "TargetDir", NULL, NULL,(LPBYTE) pszFullFileName,&len);

	RegCloseKey(hKey);
	if(regRet != ERROR_SUCCESS)
	{
		*pResult = VE_ENV_ERR; //ȯ�漳�� ����
		return FAIL;
	}

	strcat(pszFullFileName,"\\conf\\");
	strcat(pszFullFileName,"TMAX.ENV");

  CDllLoad tmaxOBJ;
	HMODULE hTmaxDll = tmaxOBJ.LoadDLL("tmax.dll",0);
  
	struct	tpstart_t {
  char	usrname[MAXTIDENT+2];	/* usr name */
  char	cltname[MAXTIDENT+2];	/* application client name */
  char  dompwd[MAX_PASSWD_LENGTH+2]; /* domain password */
  char  usrpwd[MAX_PASSWD_LENGTH+2]; /* passwd for usrid */
  int   flags;
	};
	typedef	struct	tpstart_t TPSTART_T;

	typedef (*F_tmaxreadenv)(char *file, char *label);
	typedef (*F_tpstart)(TPSTART_T *);
  typedef (*F_tpalloc)(char *type,char *subtype, long size);
	//typedef (*F_tpset_timeout)(int sec);
	typedef (*F_tpcall)(char *svc, char *idata, long ilen, char **odata, 
       	      long *olen, long flags);
	typedef (*F_gettperrno)(void);
	typedef (*F_tpend)();
	typedef (*F_tpfree)(char *ptr);

	F_tmaxreadenv   ftmaxreadenv   = (F_tmaxreadenv)GetProcAddress(hTmaxDll,"tmaxreadenv");
  F_tpstart       ftpstart       = (F_tpstart)GetProcAddress(hTmaxDll, "tpstart");
	F_tpalloc       ftpalloc       = (F_tpalloc)GetProcAddress(hTmaxDll, "tpalloc");
	//F_tpset_timeout ftpset_timeout = (F_tpset_timeout)GetProcAddress(hTmaxDll, "tpset_timeout");
	F_tpcall        ftpcall        = (F_tpcall)GetProcAddress(hTmaxDll, "tpcall");
	F_gettperrno    fgettperrno    = (F_gettperrno)GetProcAddress(hTmaxDll, "gettperrno");
	F_tpfree        ftpfree        = (F_tpfree)GetProcAddress(hTmaxDll, "tpfree");
	F_tpend         ftpend         = (F_tpend)GetProcAddress(hTmaxDll, "tpend");

	// 4-2. env ���Ϸ�  ���� �õ� 
	if (ftmaxreadenv(pszFullFileName, "SSO") < 0) 
	{
		*pResult = VE_TMAX_CONF_ERR;
		OutputDebugString("SSO_VerifyEmp - ftmaxreadenv���� \n");
		return FAIL;
	}

	if((int)(ftpstart((TPSTART_T *)NULL)) ==-1 )	
	{
		*pResult = VE_TMAX_START_ERR;
		int ret = fgettperrno();
		OutputDebugString("SSO_VerifyEmp - ftpstart ����\n");
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
    
   //��û�� ������ ���۸� ������ �ޱ� ���� ���۷ε� ��� 
  //ftpset_timeout(7);
  if (ftpcall("VCERTSVC", returnBuff, sndLen, 
             &returnBuff, &returnBuffLen, TPNOFLAGS) == -1)
  {
		  int err = fgettperrno();
      ftpfree(returnBuff);
      ftpend();
			*pResult = VE_TRANSE_DATA_ERR;
			OutputDebugString("SSO_VerifyEmp - tpcall ����\n");
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
	  *pEmpNumLen = strlen(pRecvData->empNum);                // ��� ���� 
		 strncpy(pszEmpNum, pRecvData->empNum, *pEmpNumLen +1); // ���

		 char *cn = strtok(szCN,"_"); 
		 ZeroMemory(pszEmpName,*pEmpNameLen);
		 strcpy(pszEmpName,cn);
		 *pEmpNameLen = strlen(cn);

		 // �����
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


//����������������������������������������������������������������������������������
//��                                                                              ��
//��                          SSO_GetSSOStatus	                                  ��
//��  2004. 08.22 �����                                                          ��
//��                                                                              ��
//��  1.  �ý��ۿ� MS�� �α��� �ߴ���, IF�� �α��� �ߴ��� �˾Ƴ���                ��
//��  2.  SSO�� �α��� �ߴ��� �˾Ƴ���                                            ��
//��  3.  ���                                                                    ��
//����������������������������������������������������������������������������������
INT SSO_GetSSOStatus (void)
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
  // 1 . �ý��ۿ� MS�� �α��� �ߴ���, IF�� �α��� �ߴ��� �˾Ƴ���
	//---------------------------------------------------------------

	nLoginStatus = IsIFLogon(); 

	//---------------------------------------------------------------
  // 2 . SSO�� �α��� �ߴ��� �˾Ƴ���
	// 2-1. ISign Desktop�� ��ġ�Ǿ��ִ��� üũ
	// 2-2. isigndtp.dll�� �ִ� ��θ� ����
	// 2-3. isigndtp.dll �ε��Ͽ� ISignDtop_IsLogin() ȣ��
	//---------------------------------------------------------------

	// 2-1. dll load

	CISignDtpDLL ISignDllOBJ;
	int ret = ISignDllOBJ.LoadDLL("isigndtp.dll");
	if(ret != SUCCESS) {
		return ret;
	}

	// 2-2. login �����ΰ�?
  BOOL bLogin = ISignDllOBJ.IsLogin();

	if(bLogin) {
	  nLoginStatus = (nLoginStatus == enumIF_LOGINED) ? enumIF_LOGINED : enumOAC_LOGINED;
	}
	else {
	  nLoginStatus = enumLOGOUTED;			
	}
		
	//---------------------------------------------------------------
  // 3 . ��� 
	//---------------------------------------------------------------

	return nLoginStatus;
}




//����������������������������������������������������������������������������������
//��                                                                              ��
//��                          IF_CheckCard   		                                  ��
//��  2004. 08.22 �����                                                          ��
//��                                                                              ��
//��  ����Ʈī���� ���Կ��θ� �˾Ƴ���.                                           ��
//��                                                                              ��
//��                                                                              ��
//��  return value :  0  = card Inserted                                          ��
//��                  1  = card removed                                           ��
//��                  IDN_ERR_CODE_405  = ī�帮�� open error 								    ��
//��                  SspMod_CONTEXT_NULL                                         ��
//����������������������������������������������������������������������������������
INT SSO_CheckCard(void)
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

	typedef (*F_SspMod_Open)(int port); 
  typedef (*F_SspMod_IsCardIn)(SCCtx scctx); 
	typedef (*F_SspMod_Close)(SCCtx scctx);

	F_SspMod_Open     fSspMod_Open     = (F_SspMod_Open)     GetProcAddress(hModule,"SspMod_Open");
	F_SspMod_IsCardIn fSspMod_IsCardIn = (F_SspMod_IsCardIn) GetProcAddress(hModule,"SspMod_IsCardIn");
	F_SspMod_Close    fSspMod_Close    = (F_SspMod_Close)    GetProcAddress(hModule,"SspMod_Close"); 

	if( fSspMod_Open == NULL || fSspMod_IsCardIn == NULL || fSspMod_Close == NULL) 
	{
		return NOT_FOUND_FUNCTION; //dll ���� ���캼��
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
							sprintf(msgBuf,"\nSSO_CheckCard() Error code : %d\n",nRet);
							OutputDebugString(msgBuf);
							nRet = READER_OPEN_ERROR;
						}
						break;
	}

	fSspMod_Close(ctx);
	
	return nRet;
}


static INT IsIFLogon(void)
{
	enum ISIFLOGON {
		ISIFLOGON_IF = 0,
		ISIFLOGON_MS,
		ISIFLOGON_UNKNOWN = 3
	};

	INT    nRet ,regRet;
	TCHAR  szBuf[MAX_PATH] = {0,};
	DWORD  cb,word;
	DWORD  dwType = REG_SZ;
	HKEY   hKey;

	// �����ϸ� �⺻���� ISIFLOGON_UNKNOWN ����.
	nRet = ISIFLOGON_UNKNOWN;

	regRet = RegCreateKeyEx( HKEY_LOCAL_MACHINE,
									  			 TEXT("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon"),
													 0, NULL, 0, KEY_ALL_ACCESS, NULL, &hKey, &word);

	if(ERROR_SUCCESS == regRet) 
	{
		cb     = sizeof(szBuf);
		regRet = RegQueryValueEx(hKey,TEXT("GinaDLL"), 0, &dwType, (LPBYTE)szBuf, &cb);	

		if(ERROR_SUCCESS == regRet)	
		{
			strupr(szBuf);
			char *pDest = strstr(szBuf,"LGM");
			nRet = pDest ? ISIFLOGON_IF : ISIFLOGON_MS;
		}
	}

	RegCloseKey(hKey);
	return nRet;
}



/*
Window �̸� : "OperaClient"
 
Format : ���а�(1) + 
         ScrFrame(3) + 
				 Scrȭ���ȣ(20) + 
				 Scrȭ�� Caption(60)+
				 DstFrame(3) + 
				 Dstȭ���ȣ(20) + 
				 Dstȭ�� Caption(60) + 
				 ������(10000)
 
���а�   : "D"
ScrFrame : "SSO" (�۽��ϴ� �������� ����)
DstFrame : "JBT"
������   : "UNLOCK" ; ī�尡 ���ŵɶ�
           "LOCK"   ; ī�尡 ���Եɶ�
 
�׿��� ��Ÿ �׸� : Space�� �ڸ��� ��ŭ ä���.
*/
struct SEND_EVENT_DATA{
	char Id;
	char szSrcFrame[3];
	char szSrcScreenNum[20];
	char szSrcCaption[60];
	char szDstFrame[3];
	char szDstScreenNum[20];
	char szDstCaption[60];
	char szData[10000];
};

struct SENDDATA_PARAM 
{
	HWND hSrcWnd;
	char szWindowName[MAX_PATH];
};

BOOL CALLBACK DlgProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK EnumWindowsProc(HWND hwnd , LPARAM lp);


INT SSO_OnScreenLock(void)
{
	OutputDebugString("SSO_OnScreenLock �Լ� ȣ���");
	// 1. IF�α����� ��츸 Event������.
	if( IsIFLogon() != 0)
	{
		OutputDebugString("ISSAC-File�α��� ���°� �ƴϹǷ� SSO_OnScreenLock ����");
		return 0;
	}

  // 2. Event�� ������.
  g_nLock = SCREEN_LOCK;
  DialogBox( g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc );
	OutputDebugString("SSO_OnScreenLock �Լ� �Ϸ�");
	return 0;
}


INT SSO_OnScreenUnlock(void)
{
	OutputDebugString("SSO_OnScreenUnlock �Լ� ȣ���");
	// 1. IF�α����� ��츸 Event������.
	if( IsIFLogon() != 0) 
	{
		OutputDebugString("ISSAC-File�α��� ���°� �ƴϹǷ� SSO_OnScreenUnlock ����");
		return 0;
	}

  // 2. Event�� ������.
  g_nLock = SCREEN_UNLOCK;
  DialogBox( g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc );
	OutputDebugString("SSO_OnScreenUnLock �Լ� �Ϸ�");
	return 0;
}


BOOL CALLBACK DlgProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HWND  hDstWnd = 0;
	HDESK hDesk;
	SENDDATA_PARAM dataPram;

	HKEY  hKey;
	LONG  lResult; 
	DWORD dwValueLen = 256;
	char szMsg[256];

	
	switch(iMsg)
	{
	case WM_INITDIALOG :

		if(ERROR_SUCCESS != RegOpenKeyEx( HKEY_LOCAL_MACHINE, REG_SSOSDK_KEY, 0, KEY_READ, &hKey))
		{		
			MessageBox(NULL, "Event���� ������ �̸��� ���� �� �����ϴ�","SSO_SDK",MB_OK);
			EndDialog(hwnd, 0);
			return TRUE;
		}

		lResult = RegQueryValueEx( hKey, REG_SSOSDK_EVENT_WINDOWNAME, NULL, NULL, (LPBYTE)dataPram.szWindowName, &dwValueLen);
		RegCloseKey(hKey); 

		if(ERROR_SUCCESS != lResult)
		{
			char temp[MAX_PATH];
			sprintf(temp,"Event���� ������ �̸��� ���� �� �����ϴ�\nlock = %d\n",g_nLock);
			//OutputDebugString(temp);
			MessageBox(NULL,temp ,"SSO_SDK",MB_OK);
			EndDialog(hwnd, 0);
			return TRUE;
		}
		sprintf(szMsg,"Event���� ������ �̸� ���� :%s",dataPram.szWindowName);
		OutputDebugString(szMsg);
		dataPram.hSrcWnd = hwnd;
			
		hDesk = OpenDesktop("Default", 0, FALSE, DESKTOP_ENUMERATE);
		EnumDesktopWindows(hDesk, EnumWindowsProc , (LPARAM)&dataPram) ;		
		CloseDesktop(hDesk);
	
		EndDialog(hwnd, 0);
		
		return TRUE;

	}
	return FALSE;
}



BOOL CALLBACK EnumWindowsProc(HWND hwnd , LPARAM lPram)
{
	char szMsg[256];
	char text[MAX_PATH] ;
	::GetWindowText(hwnd,text,MAX_PATH);

	SENDDATA_PARAM *pPram = reinterpret_cast<SENDDATA_PARAM *>(lPram);


	if(strcmp(text,pPram->szWindowName)==0)
	{
		SEND_EVENT_DATA data;
		memset(&data,' ',sizeof(SEND_EVENT_DATA));
		data.Id = SEND_EVENT_ID;
		memcpy(data.szSrcFrame,SEND_EVENT_SRCFRAME,strlen(SEND_EVENT_SRCFRAME));
		memcpy(data.szDstFrame,SEND_EVENT_DSTFRAME,strlen(SEND_EVENT_DSTFRAME));

		if(g_nLock == SCREEN_LOCK) {
			memcpy(data.szData,SEND_EVENT_LOCK,strlen(SEND_EVENT_LOCK));
		}
		else if(g_nLock == SCREEN_UNLOCK) {
			memcpy(data.szData,SEND_EVENT_UNLOCK,strlen(SEND_EVENT_UNLOCK));
		}
    
		sprintf(szMsg,"��� ������ ã�� (hwnd : %x)",hwnd);
		OutputDebugString(szMsg);

		COPYDATASTRUCT copyDataOBJ;
		copyDataOBJ.cbData = sizeof(SEND_EVENT_DATA);
		copyDataOBJ.lpData = (PVOID)&data;
		copyDataOBJ.dwData = SEND_EVENT_DWDATA;

		
		OutputDebugString("\n\n=== ������ ������ ====");
		sprintf(szMsg,"dwData : %x\nszData : %s\nszSrcFrame : %s\nszDstFrame :%s",
			copyDataOBJ.dwData,data->szData,data->szSrcFrame,data->szDstFrame);
		OutputDebugString(szMsg);
		OutputDebugString("=================\n\n");
		SendMessage(hwnd,WM_COPYDATA,(WPARAM)pPram->hSrcWnd,(LPARAM)(LPVOID)&copyDataOBJ);		
	}
	
	return TRUE;
}