// DssFpError.h: interface for the DssFpError class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DSSFPERROR_H__5B44D893_FD2B_46C2_9F08_8AE3A32EF6DF__INCLUDED_)
#define AFX_DSSFPERROR_H__5B44D893_FD2B_46C2_9F08_8AE3A32EF6DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class DssFpError  
{
  int m_size;
  int m_errorcode;
public:
	DssFpError();
	virtual ~DssFpError();
  int GetErrorCode();
  const char *GetErrorStr(int);
};





#endif // !defined(AFX_DSSFPERROR_H__5B44D893_FD2B_46C2_9F08_8AE3A32EF6DF__INCLUDED_)
