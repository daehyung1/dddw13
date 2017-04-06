// ISignDtpDLL.h: interface for the CISignDtpDLL class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ISIGNDTPDLL_H__DE60EA87_2466_4AAB_B25D_5017366707F7__INCLUDED_)
#define AFX_ISIGNDTPDLL_H__DE60EA87_2466_4AAB_B25D_5017366707F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000




typedef struct tagISIGNERROR
{
	int		code;
	int		group;
}	ISIGNERROR;


class CISignDtpDLL  
{
public:
	CISignDtpDLL();
	virtual ~CISignDtpDLL();

	int            LoadDLL(LPCTSTR lpszDLLName);
	inline HMODULE GetHandle() {return m_hMoudle;}

	int  GetLastError(ISIGNERROR *pErr);
	BOOL IsLogin(void);
	int  GetCurUserDN(TCHAR *  pszDn, int nBufSize);
	int  GetCurUserPKICert(char *pBuf, int *pLen, int nBufSize);
	int  GetCurUserID(LPSTR pszID, int nBufSize);
	//   int  ISignDtop_GetLastError(ISIGNERROR *pErr)
	//   BOOL ISignDtop_IsLogin(void)
	//   int  ISignDtop_GetCurUserDN(TCHAR *  pszDn, int nBufSize)
	//   int  ISignDtop_GetCurUserPKICert(char *pBuf, int *pLen, int nBufSize)
private: 
	HMODULE m_hMoudle;
	//±è´ëÇü
	//typedef I(*F_ISignDtop_IsLogin)();
	typedef INT_PTR (*F_ISignDtop_IsLogin)();
	typedef INT_PTR (*F_ISignDtop_GetLastError)(ISIGNERROR *pErr);
	typedef INT_PTR (*F_ISignDtop_GetCurUserDN)(TCHAR *  pszDn, int nBufSize);
	typedef INT_PTR (*F_ISignDtop_GetCurUserPKICert)(char *pBuf, int *pLen, int nBufSize);
	typedef INT_PTR (*F_ISignDtop_GetCurUserID)(LPSTR pszID, int nBufSize);

  F_ISignDtop_IsLogin           m_fpIsLogin;
	F_ISignDtop_GetLastError      m_fpGetLastError;
	F_ISignDtop_GetCurUserDN      m_fpGetCurUserDN;
	F_ISignDtop_GetCurUserPKICert m_fpGetCurUserPKICert;
	F_ISignDtop_GetCurUserID      m_fpGetCurUserID;
};

#endif // !defined(AFX_ISIGNDTPDLL_H__DE60EA87_2466_4AAB_B25D_5017366707F7__INCLUDED_)
