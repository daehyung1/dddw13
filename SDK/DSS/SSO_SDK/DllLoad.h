// DllLoad.h: interface for the CDllLoad class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DLLLOAD_H__1890D277_5A06_4BB3_A4B6_0F4306FA9CA4__INCLUDED_)
#define AFX_DLLLOAD_H__1890D277_5A06_4BB3_A4B6_0F4306FA9CA4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum CDllLoad_ERROR
{
	DLL_CAN_NOT_LOAD = 5,
	ISSAC_FILE_NOT_INSTALLED = 10,
	ISIGN_NOT_INSTALLED
};

class CDllLoad  
{
	HMODULE m_hModule;
  int     m_nLastError;
public:
	CDllLoad();
	virtual ~CDllLoad();
	
  int     GetLastErr();
	HMODULE LoadDLL(LPCTSTR lpszDLLName, int nPathType);
	int     GetDllPathByType(LPSTR szDllPath,int &rPathLen, int nPathType);
	HMODULE GetHModule();
};

#endif // !defined(AFX_DLLLOAD_H__1890D277_5A06_4BB3_A4B6_0F4306FA9CA4__INCLUDED_)
