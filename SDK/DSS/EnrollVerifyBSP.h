#if !defined(AFX_EnrollVerifyAPI_H__3A7F78BE_68B6_4102_ADDD_C3A98B018E9B__INCLUDED_)
#define AFX_EnrollVerifyAPI_H__3A7F78BE_68B6_4102_ADDD_C3A98B018E9B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CEnrollVerifyBSP dialog

class CEnrollVerifyBSP 
{
// Construction
public:

    CEnrollVerifyBSP(); 

    bool Bio_Load(CString &strRC);
    bool Bio_Attach(CString &strRC);
    bool Bio_Verify(CString &strRC);
    bool Bio_Enroll(CString &strName, CString &strRC);
    bool Bio_Detach(CString &strRC);
    bool Bio_Unload(CString &strRC);
    bool Bio_FreeBIRs(CString &strRC);
    bool Bio_Identify(CString &strRC);

    BioAPI_BSP_SCHEMA *m_pSchema; 
    bool m_bModuleLoaded;
    BioAPI_HANDLE m_hAttachedSession; // one per loaded BSP
    bool m_bEnrolled;
    BioAPI_EventHandler m_EventHandler; // one per loaded BSP

    BioAPI_BIR_ARRAY_POPULATION m_birArray;
};

#endif // !defined(AFX_EnrollVerifyAPI_H__3A7F78BE_68B6_4102_ADDD_C3A98B018E9B__INCLUDED_)
