// DllLoad.cpp: implementation of the CDllLoad class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DSS.h"
#include "DllLoad.h"
#include "assert.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDllLoad::CDllLoad() :m_hModule(NULL)
{

}

CDllLoad::~CDllLoad()
{
	if(m_hModule) 
	{
		FreeLibrary(m_hModule);
		m_hModule = NULL;
	}
}

HMODULE CDllLoad::LoadDLL(LPCTSTR lpszDLLName,int nPathtype)
{
	assert(lpszDLLName >  0);
	assert(nPathtype   >= 0);
	assert(m_hModule   == NULL);

	char szFullName[MAX_PATH] = {0,};
  int  nPathLen         = sizeof(szFullName);

	int nRet = GetDllPathByType(szFullName,nPathLen,nPathtype);
	if ( SUCCESS != nRet)	{
		m_nLastError = nRet;
		return NULL;
	}

	strcat(szFullName, lpszDLLName);

  // load
  m_hModule = LoadLibraryEx(szFullName,NULL,LOAD_WITH_ALTERED_SEARCH_PATH);
 
	if(NULL == m_hModule) 
	{
		m_nLastError = ::GetLastError();
	}
  
	return (m_hModule > 0 ) ?  m_hModule : NULL;
}

// rPathLen [in/out] in  -> szDllPath������ ũ��
//                   out -> ��ȯ�� szDllPath byte ����
//
// nPathType - 0 : �ƹ��͵� ����. //Ȯ�� �ؾ� ��.
//             1 : ISSAC-File ���
//             2 : ISign���
//             3 : Program Files ���
//             4 : Windows ���  
//
int CDllLoad::GetDllPathByType(LPSTR szDllPath,int &rPathLen, int nPathType)
{
	// 
	switch(nPathType) {
	case 0:		return SUCCESS;
	case 1:
		break;
	default: break;
	}
	return 0;	
}

HMODULE CDllLoad::GetHModule()
{
	return m_hModule;
}