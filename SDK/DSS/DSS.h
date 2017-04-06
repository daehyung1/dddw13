

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
    long    time;      //���߿� �̰��� localtime()�� ȣ���ؼ� display�Ҽ��ִ�.
  }IFDNLIST, FAR *LPIFDNLIST;
  
  
  typedef struct tagIFFILELIST
  {
    INT			nSucc;
    TCHAR		szSrcName[MAX_PATH]; // �ڡڡ� ���� ����� �ݵ�� fullpath�� �Ѿ�;� �Ѵ�.
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



/** DSS_SigVal ��������������������������������������������������������������������
    @ingroup SSA_SG
    @brief ���� ���� ���� �Լ�(No Message Format)
    
    message�� �Է����� �޾� cnk�� ���ԵǾ� �ִ� �����Ű�� ���ڼ����� ������ 
    ����� sigVal�� ����Ѵ�. 

    ��°��� �޽��� ������ ���Ե��� ���� ������ ���� ���� �Լ��̴�.
        
    <SSA���� �����Ǵ� �˰��� ����>

    sigAlg : KCDSA, DSA, RSA (ssa.h�� SSA_SUPPORT_PUBLIC_KEY_ALG ����)
    hashAlg: HAS160, SHA1, MD5 (ssa.h�� SSA_SUPPORT_HASH_ENCRYPTION_ALG ����)

	  @param certBuf      [out] ����� ������ 
    @param sigVal       [out] ������ ���ڼ����� ���� ��µ� ���� 
    @param sigValLen    [out] ������ ���ڼ��� sigVal�� ����Ʈ ���� ����
    @param sigValMaxLen [in]  sigVal ������ �ִ� ���� 
    @param message      [in]  ���ڼ����� �������� �Է� ����
    @param messageLen   [in]  ���ڼ����� �������� ����Ʈ ���� ����
    
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

/** DSS_VerifySigVal ������������������������������������������������������������
    @ingroup SSA_SG
    @brief ���� ���� ���� �Լ�(No Message Format)
    
    ���� ���� sigVal�� ���� message�� �Է� �޾� cert�� ���ԵǾ� �ִ� ����Ű�� <br>
    ���ڼ����� �����ϰ� ���� ����� �����Ѵ�. 

    �Է°��� �޽��� ������ ���Ե��� ���� ������ ���ڼ��� ���� �Լ��̴�.
    
    �� �����Լ������� ������ ������ �������� �ʴ´�.(������ ������ ssa_check.h�� ����.)

    @param sigVal     [in] ������ ���ڼ����� ���� 
    @param sigValLen  [in] sigVal�� ����Ʈ ���� ����
    @param message    [in] ���� �������� �Է� ����
    @param messageLen [in] message�� ����Ʈ ���� ����
    @param certBuf    [in] ������ ����
    
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

// ���� �������� keyName�� ���´�
// ISSAC-File ����ڰ� �ƴ϶��  ISign�α��� ������� ���� �����´�.

DSS BOOL DSS_GetSigKeyPathName(OUT char *pszKeyPath,IN const int keyPathAlloc);


//������������������������������������������������������������������������������
// Func   :  DSS_CheckCardInsert
// Desc   :  card�� �����⿡ �ִ��� �˻�.
// Parm   :  
// return :  1    = ��ū Inserted
//           0    = ��ū removed
//           405  = ��ū���� open error  
//           else = �� �� ����
//������������������������������������������������������������������������������
//DSS INT  DSS_CheckCardInsert(void);
//������������������������������������������������������������������������������
// Func   :  DSS_IsIFLogon
// Desc   :  �ý��� �α׿� Ÿ���� ��
//           ms-logon ���� issac-file logon���� �˾Ƴ���. 
// Parm   :  
// return :  0    = IF�α׿�
//           1    = MS�α׿�
//           3    = func����
//������������������������������������������������������������������������������

DSS INT DSS_IsIFLogon(void);

//����������������������������������������������������������������������������������
//��                                                                              ��
//��                          JNI �� ���ε� API                                   ��
//��  2004. 08.23 �����                                                          ��
//��                                                                              ��
//��  1.  IF_CheckCardInsert                                                      ��
//��  2.  IF_GetLogonType                                                         ��
//��  3.  IF_VerifyUserFromTMAX                                                   ��
//��  4.  IF_GetEmpInfoFromTMAX                                                   ��
//����������������������������������������������������������������������������������

//������������������������������������������������������������������������������
// Func   :  DSS_CheckCard
// Desc   :  card�� �����⿡ �ִ��� �˻�.
// Parm   :  
// return :  0    = ��ū Inserted
//           1    = ��ū removed
//           405  = ��ū���� open error  
//           else = �� �� ����
//������������������������������������������������������������������������������

DSS INT  DSS_CheckCard(void);


//������������������������������������������������������������������������������
// Func   :  DSS_GetSSOStatus
// Desc   :  SSO Login Ÿ���� �˾Ƴ���.
// Parm   :  
// return :  0    = ISSAC-File Logined - ISSAC-File�� �ڵ��α��� ������� �α���
//                                       �� ���
//           1    = OAC Logined - �¶��� �������Ϳ��� �߱޹޾� ISign Desktop���� 
//                                �α��� �� ���
//           2    = Logouted - 
//           3    = ISign not installed
//           4    = ȯ�漳�� ���� (������Ʈ��)
//           5    = UNKNOWN_ERR
//           203  = ���̺귯���� �ε��� �� �����ϴ�
//           204  = �Լ��� ȣ���� �� �����ϴ�
//������������������������������������������������������������������������������

DSS INT DSS_GetSSOStatus (void);


//������������������������������������������������������������������������������
// Func   :  DSS_VerifyEmp
// Desc   :  TMAX�� �̿��� ������ ������ ���� ����� ������ Ȯ�� �޴´�.
//           TMAX ���� ������ tmax.env�� �̿��ϵ��� �Ѵ�(logagt���� ���)
// Parm   :  pResult        [out] ���� ���
//           pszEmpNum      [out] ���� ��ȣ
//           pEmpNumLen     [in]  pszEmpNum�� ����ũ��
//                          [out] ���� ������ȣ�� ����Ʈ ���� ���� 
//           pszEmpName     [out] ���� �̸�
//           prEmpNameLen   [in]  pszEmpNum�� ����ũ��
//                          [out] ���� �����̸��� ����Ʈ ���� ���� 
// return :  rResult = 
//������������������������������������������������������������������������������

DSS BOOL DSS_VerifyEmp(INT   *pResult, 
											 TCHAR *pszEmpNum, 
											 INT   *pEmpNumLen,
											 TCHAR *pszEmpName,
											 INT   *pEmpNameLen);

//����������������������������������������������������������������������������������
//��                                                                              ��
//��                          DSS_VerifyEmp	    		                              ��
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

DSS INT DSS_VerifyEmp(INT   *pResult,							
                      TCHAR *pszEmpNum, 	
                      INT   *pEmpNumLen,
                      TCHAR *pszEmpName,	
                      INT   *pEmpNameLen);

//����������������������������������������������������������������������������������
//��                                                                              ��
//��                          DSS_GetSSOStatus	                                  ��
//��  2004. 08.22 �����                                                          ��
//��                                                                              ��
//��  1.  �ý��ۿ� MS�� �α��� �ߴ���, IF�� �α��� �ߴ��� �˾Ƴ���                ��
//��  2.  SSO�� �α��� �ߴ��� �˾Ƴ���                                            ��
//��  3.  ���                                                                    ��
//����������������������������������������������������������������������������������

DSS INT DSS_GetSSOStatus (void);

//����������������������������������������������������������������������������������
//��                                                                              ��
//��                          DSS_CheckCard   		                                ��
//��  2004. 08.22 �����                                                          ��
//��                                                                              ��
//��  ����Ʈ��ū�� ���Կ��θ� �˾Ƴ���.                                           ��
//��                                                                              ��
//��                                                                              ��
//��  return value :  0  = card Inserted                                          ��
//��                  1  = card removed                                           ��
//��                  IDN_ERR_CODE_405  = ��ū���� open error 								    ��
//��                  SspMod_CONTEXT_NULL                                         ��
//����������������������������������������������������������������������������������

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
// 2006.11.24 ������ (�ۼ��� : ��ö��)
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
// 2006.12.29 ȫ����
//��������

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
  int device_id;//����̽� ���̵�
  char device_name[256];// ����̽� �̸�
}DSS_FP_ENUMDEVICE_INFO;
// ����̽� ��ġ�� �������� ���� ����ü �Դϴ�.


DSS int DSS_FP_Enroll_Stream(char** outstream,int *len);
DSS int DSS_FP_Enroll_Stream_Write(char* block,int len,char* payload);



/**     
    2008.10.24
    ������
    ������ �����⿡ ���������� �Է��ϱ� 
    ������ �ִ� �Լ����� ������ �̸��� �ްԲ� �Ͽ� �����ؼ� �߰��ϵ��� �Ѵ�.
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

// 20080415 ��ö�� ����
// DSS_FP_VerifyWithICS�Լ��� ���������� DSS_FP_Initialize, DSS_FP_Destroy�� ȣ���մϴ�.
DSS int DSS_FP_VerifyWithICS(int *errCode, char* errMsg, char *name, char *resid_hmac, char *empNum, int onlyICS);
DSS int __stdcall DSS_FP_VerifyWithICSStd(int *errCode, char* errMsg, char *name, char *resid_hmac, char *empNum, int onlyICS);
// 20080415 ��ö�� ��

DSS int DSS_FP_Enroll(TCHAR * strpayload=NULL);
DSS int __stdcall DSS_FP_EnrollStd(TCHAR * strpayload=NULL);
//������ ����Ҷ� ����ϸ� �˴ϴ�.
  //payload�� ������ strpayload�� �־ ������ �˴ϴ�.



DSS int DSS_FP_Verify(TCHAR ** strpayload=NULL);
DSS int __stdcall  DSS_FP_VerifyStd(TCHAR ** strpayload=NULL);
//���� ������ �õ��ϸ� 
// ���� ������ strpayload�� payload���� �ֽ��ϴ�. NULL�϶��� �ʳֽ��ϴ�.
// �ּҰ��� �־� �ָ� �޸𸮸� �Ҵ��ؼ� �־��ݴϴ�. ����ڰ� �˾Ƽ� �޸𸮸� �����־� �մϴ�.
//stl string �̳� CString ���� �ϰ� ������ ���� �����ϵ��� ������


DSS int DSS_FP_GetControlUnitTime(int *npStartTick, int *npCapture_StartTick, int *npCapture_EndTick);

DSS int DSS_FP_SetEnrollSecurityLevel(unsigned int secuLevel);
DSS int DSS_FP_SetVerifySecurityLevel(unsigned int secuLevel);
DSS int DSS_FP_GetEnrollSecurityLevel(unsigned int *nEnrollLevel);
DSS int DSS_FP_GetVerifySecurityLevel(unsigned int *nVerifyLevel);

DSS int DSS_FP_ChangePayload(TCHAR *strpayload,bool flag=true);
DSS int __stdcall DSS_FP_ChangePayloadStd(TCHAR *strpayload,bool flag=true);

//flag �� false �̸� ����â�� ���� �ʴ´�. flag�� true�� ����â�� ���.
//payload���� �����Ҷ� ����ϸ� strpayload�� ������ payload ���� �����մϴ�.



// 20070903 ������
DSS int DSS_FP_InitializeEx(HWND hwnd,int skinflag=0,int libflag=0);
DSS int DSS_FP_Initialize(HWND hwnd,int skinflag=0,int libflag=0);
DSS int __stdcall  DSS_FP_InitializeStd(HWND hwnd,int skinflag=0,int libflag=0);
//�ʱ�ȭ �Լ� �̸� ���� �ѹ��� ȣ���ϸ� �˴ϴ�.
//skinflag ��Ų�� �ٲ۴�. 0�̸� Ȳ�ݻ� 1�̸� û�ϻ��̴�.
//libflag ����ϴ� ���̺귯���� �ٲ۴�. 0�̸� ��Ʈ�� 1�̸� BioApi�̴�.




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

    sprintf(buffer,"�ʱ�ȭ ī����:%d",a);
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

	SCM���� ��������� �ؾ��� ��,
	SCM�޴��� ������ū, ����ī�� ���� ��ư�� ������� 
	issac-file���� �α��� �� ���� ��ü�� �д� �������,

	SspMod_open-> OpenbyReaderName�� ����ϱ� ����
	���ڸ� �ޱ� ���Ͽ� ������ ���� �Լ����� �߰� �ۼ��Ͽ����ϴ�.

	2008.10.02 �̴뼷

	* DSS_FP_VerifyEx
	* DSS_FP_Enroll_StreamEx
	* DSS_FP_Enroll_Stream_WriteEx
	* DSS_FP_EnrollEx
	* DSS_FP_CheckCardFingerEx
	* DSS_FP_ChangePayloadEx

	�߰� ���ڴ� integer �� �ϳ� �ڿ� �ٽ��ϴ�. 
	�� ���� character pointer��	������ ����
	
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
