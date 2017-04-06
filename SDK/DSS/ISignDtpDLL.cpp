// ISignDtpDLL.cpp: implementation of the CISignDtpDLL class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DSS.h"
#include "ISignDtpDLL.h"
#include <ASSERT.H>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CISignDtpDLL::CISignDtpDLL() :  m_hMoudle(NULL), m_fpIsLogin(NULL), 
        m_fpGetLastError(NULL), m_fpGetCurUserDN(NULL),m_fpGetCurUserPKICert(NULL) 
{

}


CISignDtpDLL::~CISignDtpDLL()
{
	if(m_hMoudle) 
		FreeLibrary(m_hMoudle);
}



int CISignDtpDLL::GetCurUserID(LPSTR pszID, int nBufSize)
{
	assert(m_hMoudle && m_fpGetCurUserID);
	assert(pszID);
  assert(nBufSize > 0);

	char szID[MAX_PATH] = {0,};
	int  bufSize        = sizeof(szID);

	int ret = m_fpGetCurUserID(szID, bufSize);

	if(ret == 1) 
	{
		strncpy(pszID, szID, nBufSize);
	}

	return ret;
}

int CISignDtpDLL::GetLastError(ISIGNERROR *pErr)
{
	assert(m_hMoudle && m_fpGetLastError);
	
	return m_fpGetLastError(pErr);
}

BOOL CISignDtpDLL::IsLogin(void)
{
	assert(m_hMoudle && m_fpIsLogin);

	return m_fpIsLogin();
}

int CISignDtpDLL::GetCurUserDN(TCHAR *pszDn, int nBufSize)
{
	assert(m_hMoudle && m_fpGetCurUserDN);
	assert(pszDn);
  assert(nBufSize > 0);

	char szDn[MAX_PATH] = {0};
	int  bufSize = sizeof(szDn);
  int  ret     = m_fpGetCurUserDN(szDn,bufSize);

	if(ret == 1) {
		strncpy(pszDn, szDn, nBufSize);
	}

	return ret;
}

int CISignDtpDLL::GetCurUserPKICert(char *pBuf, int *pLen, int nBufSize)
{
	assert(m_hMoudle && m_fpGetCurUserPKICert);
  
	char szBuf[2048] = {0,};
	int  len = sizeof(szBuf);
	int  ret = m_fpGetCurUserPKICert(szBuf,&len,len);
	
	if(ret == 1) {
		memcpy(pBuf, szBuf, len);
    *pLen = len;
	}

	return ret;
}

int CISignDtpDLL::LoadDLL(LPCTSTR lpszDLLName)
{
	enum LOGONSTATUS { enumISIGN_NOT_INSTALLED = 3, 
										 enumENV_ERR,
										 enumUNKNOWN_ERR };

	if(m_hMoudle) FreeLibrary(m_hMoudle); 

	HKEY  hKey = NULL;
	LONG  lReg;
	TCHAR szDllName[MAX_PATH]         = {0};
	TCHAR szIntalledVersion[MAX_PATH] = {0};
	DWORD	dwSize                      = sizeof(szIntalledVersion);
	DWORD	dwType                      = REG_SZ;
	
	// 1. ISign이 설치 되어있는지 체크 
	lReg = RegOpenKey(HKEY_LOCAL_MACHINE,TEXT("SOFTWARE\\Penta Security Systems\\ISign\\Version\\"),&hKey);

	if( ERROR_SUCCESS != lReg) {
		return enumISIGN_NOT_INSTALLED;
	}

	lReg = RegQueryValueEx(hKey,TEXT("InstalledVersion"),0,&dwType,(BYTE*)szIntalledVersion,&dwSize);
	RegCloseKey(hKey);

	if( ERROR_SUCCESS != lReg) {
		return enumISIGN_NOT_INSTALLED;
	}

	// 2. 설치되어 있다. dll위치를 구한다.(설치경로)
  lReg = RegOpenKey(HKEY_LOCAL_MACHINE,TEXT("SOFTWARE\\Penta Security Systems\\ISign\\Path\\"),&hKey);

	if( ERROR_SUCCESS != lReg) {
		return enumENV_ERR;
	}

	dwSize = sizeof(szDllName);
	dwType = REG_SZ;
	lReg   = RegQueryValueEx(hKey, "BinDir", 0, &dwType, (BYTE*)szDllName, &dwSize);
	RegCloseKey(hKey);

  if(ERROR_SUCCESS != lReg) {
		return enumENV_ERR;	
  }

	// 3. dll load
	strcat(szDllName,"\\");
	strcat(szDllName,lpszDLLName);
	m_hMoudle = LoadLibraryEx(szDllName,NULL,LOAD_WITH_ALTERED_SEARCH_PATH);
	
	// GetProcAddress
	int nRet = FAIL;
	if(m_hMoudle)
	{
		m_fpIsLogin           = (F_ISignDtop_IsLogin)          GetProcAddress(m_hMoudle,"ISignDtop_IsLogin");
		m_fpGetLastError      = (F_ISignDtop_GetLastError)     GetProcAddress(m_hMoudle,"ISignDtop_GetLastError");
		m_fpGetCurUserDN      = (F_ISignDtop_GetCurUserDN)     GetProcAddress(m_hMoudle,"ISignDtop_GetCurUserDN");
		m_fpGetCurUserPKICert = (F_ISignDtop_GetCurUserPKICert)GetProcAddress(m_hMoudle,"ISignDtop_GetCurUserPKICert"); 
    m_fpGetCurUserID      = (F_ISignDtop_GetCurUserID)     GetProcAddress(m_hMoudle,"ISignDtop_GetCurUserID");

		if( m_fpIsLogin           && 
			  m_fpGetLastError      && 
				m_fpGetCurUserDN      && 
				m_fpGetCurUserPKICert && 
				m_fpGetCurUserID) {

			nRet = SUCCESS;
		}
		else	{
			nRet = IDN_ERR_CODE_221; //IDS_ERR_CODE_221	"함수를 찾을 수 없습니다 GetProcAddress실패"
		}
	}
	else
	{
		nRet = IDN_ERR_CODE_203;
	}

	return nRet;
}
