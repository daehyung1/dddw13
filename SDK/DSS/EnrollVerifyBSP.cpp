#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// BioAPI event handler callback function prototype
BioAPI_RETURN BioAPI Bio_EventHandler
	(const	BioAPI_UUID				*BSPUuid,	
			BioAPI_UNIT_ID			UnitID,		
			void*					AppNotifyCallbackCtx, 
	 const	BioAPI_UNIT_SCHEMA		*UnitSchema, 
			BioAPI_EVENT			EventType); 


// CEnrollVerifyBSP constructor
CEnrollVerifyBSP::CEnrollVerifyBSP()
{
	m_bModuleLoaded	   = false;
	m_EventHandler	   = NULL;
	m_hAttachedSession = BioAPI_INVALID_HANDLE;
	m_bEnrolled		   = false;
	m_pSchema		   = NULL;

    memset(&m_birArray, 0, sizeof(BioAPI_BIR_ARRAY_POPULATION));
}

bool CEnrollVerifyBSP::Bio_Load(CString &strRC)
{
	CEnrollVerifyDlg * dlgObj = (CEnrollVerifyDlg*) (AfxGetApp()->m_pMainWnd);
	BioAPI_RETURN rc = BioAPI_OK;

	int nRegisterEventHandler = dlgObj->MessageBox("BioAPI_BSPLoad() allows you to register BSP"
		" events handler that receives notifications from Units and populates the list of units."
		" Without registering this notification only default units can be attached"
		" (selected for biometric operations).\n\n"
		"Do you want to receive events?",
		"Loading BSP DLL",MB_YESNO | MB_ICONQUESTION);
    
	dlgObj->m_listDevices.AddString("<attach any available>");

	if (nRegisterEventHandler == IDYES)
	{
		// events from the BSP will populate the unit list 
		m_EventHandler = Bio_EventHandler;
	}
	else
	{
		// no events accepted from BSP, only default units are available for attachment 
		m_EventHandler = NULL;
	}

    rc = BioAPI_BSPLoad(&m_pSchema->BSPUuid, m_EventHandler, NULL);

	if (rc == BioAPI_OK)
		m_bModuleLoaded = true;
	else
	{
		dlgObj->m_listDevices.ResetContent();
		m_EventHandler = NULL;
	}

    TCHAR szDescr[128] = "";
    CErrors::Code2Description(szDescr, sizeof(szDescr)/sizeof(TCHAR), rc);
    CString szTrim(szDescr);
    szTrim.TrimLeft();
    szTrim.TrimRight();
	strRC.Format("%d, BioAPI_BSPLoad(%s) ret=%s(0x%04X)", GetCurrentThreadId(), m_pSchema->BSPDescription, szTrim, rc) ;

	return (rc == BioAPI_OK);
}

bool CEnrollVerifyBSP::Bio_Unload(CString &strRC)
{
	BioAPI_RETURN rc = BioAPI_OK;

	CEnrollVerifyDlg * dlgObj = (CEnrollVerifyDlg*) (AfxGetApp()->m_pMainWnd);

	if (m_bModuleLoaded)
	{
		// clear list of units
		dlgObj->m_listDevices.ResetContent();

		rc = BioAPI_BSPUnload(&m_pSchema->BSPUuid, m_EventHandler, NULL);

		m_EventHandler = NULL;
		m_bModuleLoaded = false;


        TCHAR szDescr[128] = "";
        CErrors::Code2Description(szDescr, sizeof(szDescr)/sizeof(TCHAR), rc);
        CString szTrim(szDescr);
        szTrim.TrimLeft();
        szTrim.TrimRight();
        strRC.Format("%d, BioAPI_BSPUnload(%s) ret=%s(0x%04X)", 
            GetCurrentThreadId(), m_pSchema->BSPDescription, szTrim, rc) ;
	}

	return (rc == BioAPI_OK);
}


bool CEnrollVerifyBSP::Bio_Attach(CString &strRC)
{
	CString strItem;

	CEnrollVerifyDlg * dlgObj = (CEnrollVerifyDlg*) (AfxGetApp()->m_pMainWnd);
	
    // No more than 4 units (one for each category) can be selected.
	BioAPI_UNIT_LIST_ELEMENT	UnitList[4] = 
	{
		{BioAPI_CATEGORY_SENSOR,		 1}, //BioAPI_UNIT_ID_DEFAULT
		{BioAPI_CATEGORY_PROCESSING_ALG, 2},
		{BioAPI_CATEGORY_MATCHING_ALG,	 3},
        {BioAPI_CATEGORY_ARCHIVE,		 BioAPI_DONT_INCLUDE} 
	}; 

	// For simplicity we just attach first four selected and don't care 
    // about any duplicate categories that may be selected by mistake
    int nItems = dlgObj->m_listDevices.GetSelCount();
	
    int cUnitsTotal = 0;

	if (nItems > 0)
	{
		int * pSelItems = new int[nItems];

		dlgObj->m_listDevices.GetSelItems(nItems, pSelItems);

		for (int i = 0; i < nItems && i < 4; i++)
		{
			BioAPI_UNIT_ID nUnitId;

			dlgObj->m_listDevices.GetText(pSelItems[i],strItem);

         char szTemp[64];
			sscanf(strItem,STR_UNIT_FORMAT, &nUnitId, szTemp); 
			CString strCategory = szTemp;

			if (strCategory == STR_SENSOR)
            {
				UnitList[cUnitsTotal].UnitId = nUnitId;
				UnitList[cUnitsTotal].UnitCategory = BioAPI_CATEGORY_SENSOR;
                cUnitsTotal++;
            }
            else  if (strCategory == STR_PROCESS)
            {
				UnitList[cUnitsTotal].UnitId = nUnitId;
				UnitList[cUnitsTotal].UnitCategory = BioAPI_CATEGORY_PROCESSING_ALG;
                cUnitsTotal++;
            }
			else if (strCategory == STR_MATCH)
            {
				UnitList[cUnitsTotal].UnitId = nUnitId;
				UnitList[cUnitsTotal].UnitCategory = BioAPI_CATEGORY_MATCHING_ALG;
                cUnitsTotal++;
            }
			else if (strCategory == STR_ARCHIVE)
            {
				UnitList[cUnitsTotal].UnitId = nUnitId;
				UnitList[cUnitsTotal].UnitCategory = BioAPI_CATEGORY_ARCHIVE;
                cUnitsTotal++;
            }
        }

		delete [] pSelItems;
	}

	BioAPI_RETURN rc;

	rc = BioAPI_BSPAttach(&m_pSchema->BSPUuid,
							BIOAPI_REQUIRED_VERSION,
							UnitList, 
                            cUnitsTotal > 0 ? cUnitsTotal : ARRAY_CNT(UnitList),
							&m_hAttachedSession);


    // compose the log entry
    CString strCatAndId;

    if (cUnitsTotal = 0)
        strCatAndId = "don't care";
    else
    {
        strCatAndId = "cat/id:";

        for (int i = 0; i < 4; i++)
        {
            CString strTemp;
            strTemp.Format(" %d/%d", UnitList[i].UnitCategory, UnitList[i].UnitId);
            strCatAndId += strTemp;
        }

        TCHAR szDescr[128] = "";
        CErrors::Code2Description(szDescr, sizeof(szDescr)/sizeof(TCHAR), rc);
        CString szTrim(szDescr);
        szTrim.TrimLeft();
        szTrim.TrimRight();
        strRC.Format("%d, BioAPI_BSPAttach(%s), ret (handle 0x%08x) %s(0x%04X)", 
					    GetCurrentThreadId(), strCatAndId,
					    m_hAttachedSession, szTrim, rc) ;
    }

	if (rc == BioAPI_OK)
	{
		dlgObj->m_txtName.EnableWindow();
		dlgObj->m_btnEnroll.EnableWindow();
        dlgObj->m_btnIdentify.EnableWindow();
        dlgObj->m_btnAttach.SetWindowText("De&tach");
		dlgObj->m_listDevices.EnableWindow(FALSE);
	}

	return (rc == BioAPI_OK);
}


bool CEnrollVerifyBSP::Bio_Detach(CString &strRC)
{
	BioAPI_RETURN rc = BioAPI_OK;
	CEnrollVerifyDlg * dlgObj = (CEnrollVerifyDlg*) (AfxGetApp()->m_pMainWnd);
	dlgObj->m_txtName.EnableWindow(FALSE);
	dlgObj->m_btnEnroll.EnableWindow(FALSE);
    dlgObj->m_btnIdentify.EnableWindow(FALSE);
	dlgObj->m_btnAttach.SetWindowText("A&ttach");
	dlgObj->m_listDevices.EnableWindow();


	if (m_hAttachedSession != BioAPI_INVALID_HANDLE)
	{
		rc = BioAPI_BSPDetach(m_hAttachedSession);

        TCHAR szDescr[128] = "";
        CErrors::Code2Description(szDescr, sizeof(szDescr)/sizeof(TCHAR), rc);
        CString szTrim(szDescr);
        szTrim.TrimLeft();
        szTrim.TrimRight();
		  strRC.Format("%d, BioAPI_BSPDetach(0x%08x) ret=%s(0x%04X)", GetCurrentThreadId(), m_hAttachedSession, szTrim, rc) ;

		m_hAttachedSession = BioAPI_INVALID_HANDLE;
	}

	return (rc == BioAPI_OK);
}

bool CEnrollVerifyBSP::Bio_FreeBIRs(CString &strRC)
{
	BioAPI_RETURN rc = BioAPI_OK;

	// do we own the Attach handle? If yes, we'll use it as indicator 
	// suggesting that this BSP might also have BIRs allocated.
	
	if (m_hAttachedSession != BioAPI_INVALID_HANDLE)
	{
		CEnrollVerifyDlg * dlgObj = (CEnrollVerifyDlg*) (AfxGetApp()->m_pMainWnd);

		// loop through the list of enrolled BIRs and freem them
		for (int i=0; i< dlgObj->m_listBIRs.GetCount();i++)
		{
            BioAPI_BIR* pBIR = (BioAPI_BIR*)dlgObj->m_listBIRs.GetItemData(i);
            if (pBIR->BiometricData.Data)
                BioAPI_Free(pBIR->BiometricData.Data);
            if (pBIR->SecurityBlock.Data)
                BioAPI_Free(pBIR->SecurityBlock.Data);
            delete pBIR;
        
            TCHAR szDescr[128] = "";
            CErrors::Code2Description(szDescr, sizeof(szDescr)/sizeof(TCHAR), rc);
            CString szTrim(szDescr);
            szTrim.TrimLeft();
            szTrim.TrimRight();
			   strRC.Format("%d, BioAPI_FreeBIRHandle(0x%08x,%d) ret=%s(0x%04X)", GetCurrentThreadId(), m_hAttachedSession, i, szTrim, rc) ;

			// populate the list in the loop, since mutilple lines cannot be returned
			dlgObj->m_listBioAPILog.AddString(strRC);
			strRC = ""; // we added it to the list already
		}

		dlgObj->m_listBIRs.ResetContent();
		dlgObj->m_btnVerify.EnableWindow(FALSE);

	}

	return true;
}

bool CEnrollVerifyBSP::Bio_Verify(CString &strRC)
{
	BioAPI_RETURN rc	= BioAPI_OK;

	CString strItem;
	CString strTemp;

	CEnrollVerifyDlg * dlgObj = (CEnrollVerifyDlg*) (AfxGetApp()->m_pMainWnd);

	// The maximum False Match Rate that is acceptable for the application. 
	// We specify something around 0.01% of acceptance (max value / 10000).
	BioAPI_FMR		 MaxFMRRequested	= 0x7fffffff / 10000;
	BioAPI_BOOL		 verified			= BioAPI_FALSE; // The result of verification
	BioAPI_FMR		 FMRAchieved		= 0; // Actual FAR for the Verify operations
	//BioAPI_DATA		 Payload			= {0,NULL};		// The payload that can be returned on successful verification
	BioAPI_INPUT_BIR birTemplate; // The biometric template to compare with

	// use the enrolled template
	dlgObj->m_listBIRs.GetText(dlgObj->m_listBIRs.GetCurSel(), strItem);
	BioAPI_BIR* pBIR = (BioAPI_BIR*)dlgObj->m_listBIRs.GetItemData(dlgObj->m_listBIRs.GetCurSel());

	birTemplate.Form = BioAPI_FULLBIR_INPUT;
	birTemplate.InputBIR.BIR = pBIR;

	rc = BioAPI_Verify(	m_hAttachedSession,
						MaxFMRRequested,	// BioAPI_FMR *MaxFMRRequested,
						&birTemplate,		// BioAPI_INPUT_BIR	*ReferenceTemplate,
						BioAPI_DONT_CARE,	// BioAPI_BIR_SUBTYPE Subtype
						NULL,				// OUT OPTIONAL	BioAPI_BIR_HANDLE *AdaptedBIR,
						&verified,			// OUT	BioAPI_BOOL	*Result,
						&FMRAchieved,		// OUT	BioAPI_FMR	*FMRAchieved,
						NULL, //&Payload,			// OUT OPTIONAL	BioAPI_DATA	*Payload, 
						-1,					// Use default BSP timeout 
						NULL);				// We are not interested in audit data 


    TCHAR szDescr[128] = "";
    CErrors::Code2Description(szDescr, sizeof(szDescr)/sizeof(TCHAR), rc);
    CString szTrim(szDescr);
    szTrim.TrimLeft();
    szTrim.TrimRight();
	 strRC.Format("%d, BioAPI_Verify(0x%08x) ret=%s(0x%04X)", GetCurrentThreadId(), m_hAttachedSession, szTrim, rc) ;

	if (rc != BioAPI_OK) 
		return false;

	if (verified != BioAPI_FALSE)
		strTemp.Format("Verification succeeded");
	else
		strTemp.Format("Verification failed");

	dlgObj->MessageBox(strTemp);

//	if (Payload.Data)
//		BioAPI_Free(Payload.Data);

	return (verified != BioAPI_FALSE);
}



bool CEnrollVerifyBSP::Bio_Enroll(CString &strName, CString &strRC)
{

	CEnrollVerifyDlg * dlgObj = (CEnrollVerifyDlg*) (AfxGetApp()->m_pMainWnd);

	BioAPI_RETURN rc;
	BioAPI_BIR_HANDLE birTemplate;
	//CString strPayload;
	//strPayload = "Payload for " + strName;
	//BioAPI_DATA samplePayload = {strPayload.GetLength()+1, (void*) (LPCTSTR) strPayload};

	// Call BioAPI_Enroll() to generate the template. 
	// Neigher BIR for adaptation nor audit data are provided for this sample.

    rc = BioAPI_Enroll(	m_hAttachedSession,
						BioAPI_PURPOSE_ENROLL_FOR_VERIFICATION_ONLY,
						BioAPI_DONT_CARE,	// Subtype,
						NULL,				// don't care
						NULL,				// No adaptation, *ReferenceTemplate,
						&birTemplate,		// New enrolled tempalte
						NULL,           //&samplePayload,
						-1,				// Use BSP default timeout for the operation 
						NULL, NULL);	// No audit data, no template UUID

    TCHAR szDescr[128] = "";
    CErrors::Code2Description(szDescr, sizeof(szDescr)/sizeof(TCHAR), rc);
    CString szTrim(szDescr);
    szTrim.TrimLeft();
    szTrim.TrimRight();
	 strRC.Format("%d, BioAPI_Enroll(0x%08x) ret=%s(0x%04X)", GetCurrentThreadId(), m_hAttachedSession, szTrim, rc) ;

	if (rc != BioAPI_OK) 
		return false;

	int index = dlgObj->m_listBIRs.AddString(strName);

    BioAPI_BIR* pBIR = new BioAPI_BIR;
    BioAPI_GetBIRFromHandle(m_hAttachedSession, birTemplate, pBIR);
    DWORD dwBIR = (DWORD)pBIR;
	dlgObj->m_listBIRs.SetItemData(index, dwBIR);

	dlgObj->m_txtName.SetWindowText("");

	m_bEnrolled = true;

	return m_bEnrolled;
}


// Application's module event handler. Being called by loaded BSPs to notify
// about unit events, i.e. attchment of a unit for biometric operations.
// This event handler can be called either syncronously (i.e. during ModuleLoad)
// or asynchronously on a separate thread. Keep this in mind when communicating 
// with the GUI thread/objects for proper sysncronization and objects passing.
BioAPI_RETURN BioAPI Bio_EventHandler(
					const BioAPI_UUID		*BSPUuid,
					BioAPI_UNIT_ID			UnitId,		
					void *AppNotifyCallbackCtx,
					const BioAPI_UNIT_SCHEMA		*UnitSchema,
					BioAPI_EVENT			 eventType)
{

	// to display event types as user friendly strings 
	const char * szEvents[] = {	"unknown",
							"BioAPI_NOTIFY_INSERT",
							"BioAPI_NOTIFY_REMOVE",
							"BioAPI_NOTIFY_FAULT",
							"BioAPI_NOTIFY_SOURCE_PRESENT",
							"BioAPI_NOTIFY_SOURCE_REMOVED"};
	const char * szCategories[] = {	
							"unknown",
							"Archive",			
							"Matching",	
							"unknown",
							"Processing",	
							"unknown",
							"unknown",
							"unknown",
							"Sensor"};

	// Do not call MFC CWin object created by another thread, use m_hWnd instead 
	HWND hWndMain = AfxGetApp()->m_pMainWnd->m_hWnd;

    CString *pstrLog = new CString; 

	pstrLog->Format("%d, BSP event received (unit=%d, event=%s)",
						GetCurrentThreadId(),
						UnitId, 
						eventType < ARRAY_CNT(szEvents) ? szEvents[eventType] : "unknown") ;
	

	// Notify the GUI thread without blocking. 
	::PostMessage(hWndMain, ID_ADD_STR_TO_LOG, 0, (LPARAM) pstrLog);
    

	// add unit to the list if units
	CString *pstrDev = new CString; 
    
    if (UnitSchema)
	    pstrDev->Format(STR_UNIT_FORMAT, UnitId, 
		    UnitSchema->UnitCategory < ARRAY_CNT(szCategories) ? szCategories[UnitSchema->UnitCategory] : "unknown");
    else
	    pstrDev->Format(STR_UNIT_FORMAT, UnitId,"");

	
	switch (eventType)
	{
		case BioAPI_NOTIFY_INSERT:

			// add new units only
			::PostMessage(hWndMain, ID_ADD_STR_TO_DEV, 0, (LPARAM) pstrDev);

			break;

		case BioAPI_NOTIFY_REMOVE:

			// we assume that no Attach should exist for the removed unit, 
			// hence just remove it from the list and don't call any Detach here
			::PostMessage(hWndMain, ID_DEL_STR_FROM_DEV, 0, (LPARAM) pstrDev);

			break;

		default:
            delete pstrDev;
	}

	return BioAPI_OK;
}

bool CopyBIR(BioAPI_BIR * dest_pBIR, BioAPI_BIR * src_pBIR)
{
    if (dest_pBIR == NULL || src_pBIR == NULL)
        return true;

    BioAPI_BIR NewBIR; // temp BIR

    memcpy(&NewBIR, src_pBIR, sizeof(BioAPI_BIR));

    // allocate and copy BiometricData (if any)
    if (src_pBIR->BiometricData.Data && src_pBIR->BiometricData.Length)
        if (NULL == (NewBIR.BiometricData.Data = malloc(src_pBIR->BiometricData.Length)))
            return false;
        else
            memcpy(NewBIR.BiometricData.Data, src_pBIR->BiometricData.Data, src_pBIR->BiometricData.Length);

    // allocate and copy SecurityBlock (if any)
    if (src_pBIR->SecurityBlock.Data && src_pBIR->SecurityBlock.Length)
        if (NULL == (NewBIR.SecurityBlock.Data = malloc(src_pBIR->SecurityBlock.Length)))
        {
            if (NewBIR.BiometricData.Data) 
                free(NewBIR.BiometricData.Data);

            return false;
        }
        else
            memcpy(NewBIR.SecurityBlock.Data, src_pBIR->SecurityBlock.Data, src_pBIR->SecurityBlock.Length);


    memcpy(dest_pBIR, &NewBIR, sizeof(BioAPI_BIR));

    return true;
}

bool CEnrollVerifyBSP::Bio_Identify(CString &strRC)
{
    BioAPI_RETURN rc	= BioAPI_OK;

    CEnrollVerifyDlg * dlgObj = (CEnrollVerifyDlg*) (AfxGetApp()->m_pMainWnd);

    m_birArray.NumberOfMembers = dlgObj->m_listBIRs.GetCount();
    m_birArray.Members = new BioAPI_BIR [m_birArray.NumberOfMembers];

    uint32_t i;
    for (i = 0; i < m_birArray.NumberOfMembers; i++) {
        BioAPI_BIR* pBIR = (BioAPI_BIR*)dlgObj->m_listBIRs.GetItemData(i);
        CopyBIR(&(m_birArray.Members[i]), pBIR);
    }

    BioAPI_IDENTIFY_POPULATION population;
    population.Type = BioAPI_ARRAY_TYPE;
    population.BIRs.BIRArray = &m_birArray;


    CString strItem;
    CString strTemp;

    

    // The maximum False Match Rate that is acceptable for the application. 
    // We specify something around 0.01% of acceptance (max value / 10000).
    BioAPI_FMR		 MaxFMRRequested	= 0x7fffffff / 10000;

    uint32_t nNumberOfResult;
    BioAPI_CANDIDATE *pCandidates;

    rc = BioAPI_Identify(	m_hAttachedSession,
        MaxFMRRequested,	// BioAPI_FMR *MaxFMRRequested,
        BioAPI_NO_SUBTYPE_AVAILABLE,
        &population,
        m_birArray.NumberOfMembers,
        BioAPI_FALSE,
        1,
        &nNumberOfResult,
        &pCandidates,
        -1,					// Use default BSP timeout 
        NULL);				// We are not interested in audit data 


    TCHAR szDescr[128] = "";
    CErrors::Code2Description(szDescr, sizeof(szDescr)/sizeof(TCHAR), rc);
    CString szTrim(szDescr);
    szTrim.TrimLeft();
    szTrim.TrimRight();
    strRC.Format("%d, BioAPI_Identify(0x%08x) ret=%s(0x%04X)", GetCurrentThreadId(), m_hAttachedSession, szTrim, rc) ;

    if (rc == BioAPI_OK) {
        if (nNumberOfResult != 0) {
            CString szID;
            dlgObj->m_listBIRs.GetText(pCandidates->BIR.BIRInArray[0], szID);
            strTemp.Format("Identification succeeded, ID=%s", szID);
        } else {
            strTemp.Format("Identification failed");
        }

        dlgObj->MessageBox(strTemp);

        if (pCandidates) {
            if (pCandidates->BIR.BIRInArray)
                BioAPI_Free(pCandidates->BIR.BIRInArray);
            BioAPI_Free(pCandidates);
        }

    } else
        nNumberOfResult = 0;

    //	if (Payload.Data)
    //		BioAPI_Free(Payload.Data);

    for (i = 0; i < m_birArray.NumberOfMembers; i++) {
        if (m_birArray.Members[i].BiometricData.Data)
            free(m_birArray.Members[i].BiometricData.Data);
        if (m_birArray.Members[i].SecurityBlock.Data)
            free(m_birArray.Members[i].SecurityBlock.Data);
    }
    delete[] m_birArray.Members;

    return (nNumberOfResult != 0);
}
