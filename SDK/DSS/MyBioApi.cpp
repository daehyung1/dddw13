#include "stdafx.h"
#include "MyBioApi.h"
#include <process.h>
#include "tchar.h"
#define HAVE_STDINT_H 1
#define BIOAPI_REQUIRED_VERSION (0x20)
#define ARRAY_CNT( array)		(sizeof( array) / sizeof(array[0]))



BioAPI_RETURN BioAPI Bio_EventHandler(
				const BioAPI_UUID		*BSPUuid,
				BioAPI_UNIT_ID			UnitId,		
				void 			*AppNotifyCallbackCtx,
				const BioAPI_UNIT_SCHEMA	*UnitSchema,
				BioAPI_EVENT			 eventType)
{
		return BioAPI_OK;
}


int CMyBioApi::DSS_FP_Init()
{
  BioAPI_RETURN rc;

  if(isInit)
    return 0;

/////////////////
  BioAPI_Init=NULL;
  BioAPI_Terminate=NULL;
  BioAPI_EnumBSPs=NULL;
  m_BinaryStream = NULL;
  m_NumberOfElements=0;

//////////////////////////
  
  m_hLib=NULL;
  m_hLib = LoadLibrary("bioapi20.dll");
  
  
  char buffer[MAX_PATH+1];
  GetWindowsDirectory(buffer,MAX_PATH);
  memcpy(buffer+strlen(buffer),"\\NTGBioBSP20.ini",17);
  
  
  if(m_resource==0)
    WritePrivateProfileString("Skin","Path","NBSP2Kor_ye.dll",buffer);
  else if(m_resource==1)
    WritePrivateProfileString("Skin","Path","NBSP2Kor_gr.dll",buffer);


  WritePrivateProfileString("InitInfo","MaxFinger","2",buffer);



  if(m_hLib==NULL)
  {
    LOGPRINT("��Ʈ�� ����Ʈ��� ��ġ���� �ʾҽ��ϴ�",50001);
    return DSS_FAILED;
  }

  BioAPI_Init=(BioAPI_Init_PTR) GetProcAddress(m_hLib, "BioAPI_Init");
  if(!BioAPI_Init)
  {
    LOGPRINT("BioAPI_Init �� Address�� �о���� ���߽��ϴ�.",8013);
    return DSS_FAILED;
  }

  BioAPI_Terminate=(BioAPI_Terminate_PTR) GetProcAddress(m_hLib, "BioAPI_Terminate");
  if(!BioAPI_Terminate)
  {
    LOGPRINT("BioAPI_Terminate �� Address�� �о���� ���߽��ϴ�.",8013);
    return DSS_FAILED;
  }

  BioAPI_EnumBSPs=(BioAPI_EnumBSPs_PTR) GetProcAddress(m_hLib, "BioAPI_EnumBSPs");
  if(!BioAPI_EnumBSPs)
  {
    LOGPRINT("BioAPI_EnumBSPs �� Address�� �о���� ���߽��ϴ�.",8013);
    return DSS_FAILED;
  }
  
  
  BioAPI_BSPLoad=(BioAPI_BSPLoad_PTR) GetProcAddress(m_hLib, "BioAPI_BSPLoad");
  if(!BioAPI_BSPLoad)
  {
    LOGPRINT("BioAPI_BSPLoad �� Address�� �о���� ���߽��ϴ�.",8013);
    return DSS_FAILED;
  }


  BioAPI_BSPUnload=(BioAPI_BSPUnload_PTR) GetProcAddress(m_hLib, "BioAPI_BSPUnload");
  if(!BioAPI_BSPUnload)
  {
    LOGPRINT("BioAPI_BSPUnload �� Address�� �о���� ���߽��ϴ�.",8013);
    return DSS_FAILED;
  }


  BioAPI_BSPAttach=(BioAPI_BSPAttach_PTR) GetProcAddress(m_hLib, "BioAPI_BSPAttach");
  if(!BioAPI_BSPAttach)
  {
    LOGPRINT("BioAPI_BSPAttach �� Address�� �о���� ���߽��ϴ�.",8013);
    return DSS_FAILED;
  }


  BioAPI_BSPDetach=(BioAPI_BSPDetach_PTR) GetProcAddress(m_hLib, "BioAPI_BSPDetach");
  if(!BioAPI_BSPDetach)
  {
    LOGPRINT("BioAPI_BSPDetach �� Address�� �о���� ���߽��ϴ�.",8013);
    return DSS_FAILED;
  }


  BioAPI_Enroll=(BioAPI_Enroll_PTR) GetProcAddress(m_hLib, "BioAPI_Enroll");
  if(!BioAPI_Enroll)
  {
    LOGPRINT("BioAPI_Enroll �� Address�� �о���� ���߽��ϴ�.",8013);
    return DSS_FAILED;
  }

  BioAPI_Verify=(BioAPI_Verify_PTR) GetProcAddress(m_hLib, "BioAPI_Verify");
  if(!BioAPI_Verify)
  {
    LOGPRINT("BioAPI_Verify �� Address�� �о���� ���߽��ϴ�.",8013);
    return DSS_FAILED;
  }

  BioAPI_Capture=(BioAPI_Capture_PTR) GetProcAddress(m_hLib, "BioAPI_Capture");
  if(!BioAPI_Capture)
  {
    LOGPRINT("BioAPI_Capture �� Address�� �о���� ���߽��ϴ�.",8013);
    return DSS_FAILED;
  }


  BioAPI_CreateTemplate=(BioAPI_CreateTemplate_PTR) GetProcAddress(m_hLib, "BioAPI_CreateTemplate");
  if(!BioAPI_CreateTemplate)
  {
    LOGPRINT("BioAPI_CreateTemplate �� Address�� �о���� ���߽��ϴ�.2",8013);
    return DSS_FAILED;
  }

  BioAPI_GetBIRFromHandle=(BioAPI_GetBIRFromHandle_PTR) GetProcAddress(m_hLib, "BioAPI_GetBIRFromHandle");
  if(!BioAPI_GetBIRFromHandle)
  {
    LOGPRINT("BioAPI_GetBIRFromHandle �� Address�� �о���� ���߽��ϴ�.",8013);
    return DSS_FAILED;
  }

  BioAPI_FreeBIRHandle=(BioAPI_FreeBIRHandle_PTR) GetProcAddress(m_hLib, "BioAPI_FreeBIRHandle");
  if(!BioAPI_FreeBIRHandle)
  {
    LOGPRINT("BioAPI_FreeBIRHandle �� Address�� �о���� ���߽��ϴ�.",8013);
    return DSS_FAILED;
  }

  BioAPI_Free=(BioAPI_Free_PTR) GetProcAddress(m_hLib, "BioAPI_Free");
  if(!BioAPI_Free)
  {
    LOGPRINT("BioAPI_Free �� Address�� �о���� ���߽��ϴ�.",8013);
    return DSS_FAILED;
  }

	BioAPI_ControlUnit=(BioAPI_ControlUnit_PTR) GetProcAddress(m_hLib, "BioAPI_ControlUnit");

  if(!BioAPI_ControlUnit)
  {
    LOGPRINT("BioAPI_ControlUnit �� Address�� �о���� ���߽��ϴ�.",8013);
    return DSS_FAILED;
  }
  
  //////////////////////////////
  /////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////
  //////////////////////////////
  
  
  rc = BioAPI_Init(BIOAPI_REQUIRED_VERSION); 
  if(rc!=BioAPI_OK)
  {
    LOGPRINT("��Ʈ�� ����Ʈ��� ��ġ ���� �ʾҽ��ϴ�",50000);
    return DSS_FAILED;
  }
  
  
  /*
    BioAPI_FRAMEWORK_SCHEMA frameworkSchema;
    memset(&frameworkSchema, 0, sizeof(BioAPI_FRAMEWORK_SCHEMA));
    BioAPI_RETURN bioReturn = BioAPI_GetFrameworkInfo (&frameworkSchema);
    BioAPI_Free(frameworkSchema.Path);
  */
  
  int reg=0;
  

  while(1)
  {
    rc=BioAPI_EnumBSPs(&m_pBSPs,&m_NumberOfElements);

    if(m_pBSPs==NULL||m_NumberOfElements==0)
    {
      if(reg==1)
      {
        LOGPRINT("��Ʈ�� ����Ʈ��� ��ġ�����ʾҽ��ϴ�",50002);
        return DSS_FAILED;
      }

      if(Register()!=0)
        return DSS_FAILED;
    }
    else
      break;

    
      reg=1;
   }
  
  
  if(rc!=BioAPI_OK)
  {
    LOGPRINT("��Ʈ�� ����Ʈ��� ��ġ�����ʾҽ��ϴ�",50003);
    return DSS_FAILED;
  }
  
  
  
  UINT i;
  for(i=0;i<m_NumberOfElements;i++)
  {
   
    if(strcmp((char*)m_pBSPs[i].BSPUuid,"?ǰ&BJ	��.ď.?NITGEN Fingerprint BSP v2.0"))
      break;
  }
  
  if(i==m_NumberOfElements)
  {
    LOGPRINT("��Ʈ�� ����Ʈ��� ��ġ�����ʾҽ��ϴ�",8012);
    return DSS_FAILED;
  }
  
  BioAPI_EventHandler eh=Bio_EventHandler;
  

  memcpy(m_bspuuid,m_pBSPs[i].BSPUuid,sizeof(m_pBSPs[i].BSPUuid));
  rc=BioAPI_BSPLoad(&m_pBSPs[i].BSPUuid,eh,NULL);
  
  if(rc!=BioAPI_OK)
  {
    LOGPRINT("��Ʈ�� ����Ʈ��� ��ġ�����ʾҽ��ϴ�",50004);
    return DSS_FAILED;
  }
  
  
  
  BioAPI_UNIT_LIST_ELEMENT	UnitList[4] = 
	{
		{BioAPI_CATEGORY_SENSOR,					1},					
		{BioAPI_CATEGORY_PROCESSING_ALG, 	2},
		{BioAPI_CATEGORY_MATCHING_ALG,		3},
    {BioAPI_CATEGORY_ARCHIVE,		BioAPI_DONT_INCLUDE} 
	};
  
  
  rc=BioAPI_BSPAttach(&m_pBSPs[i].BSPUuid,BIOAPI_REQUIRED_VERSION,UnitList,
    ARRAY_CNT(UnitList),&m_hAttachedSession);
  
  
  if(rc!=BioAPI_OK)
  {
    LOGPRINT("��Ʈ�� ����Ʈ��� ��ġ�����ʾҽ��ϴ�",50005);
    return DSS_FAILED;
  }
  
  
  isInit=true;
  
  return 0;
}

int CMyBioApi::DeviceOpen()
{

  return 0;

}

int CMyBioApi::DeviceClose()
{

  return 0;

}

long CMyBioApi::MakeStreamFromFIR(BioAPI_BIR *FIR, BYTE* pMyStreamData)
{

  uint32_t nMyStreamLen = sizeof(FIR->Header)+ sizeof(FIR->BiometricData.Length) +\
            FIR->BiometricData.Length+ sizeof(FIR->SecurityBlock.Length) +\
            FIR->SecurityBlock.Length+sizeof(uint32_t);


  if(!pMyStreamData)
    return -1;

  uint32_t pos = 0;
    
  memcpy(pMyStreamData + pos, &(nMyStreamLen), sizeof(nMyStreamLen));
  pos += sizeof(nMyStreamLen);
  memcpy(pMyStreamData + pos, &(FIR->Header), sizeof(FIR->Header));
  pos += sizeof(FIR->Header);
  memcpy(pMyStreamData + pos, &(FIR->BiometricData.Length),sizeof(FIR->BiometricData.Length));
  pos += sizeof(FIR->BiometricData.Length);
  memcpy(pMyStreamData + pos, FIR->BiometricData.Data,FIR->BiometricData.Length);
  pos += FIR->BiometricData.Length;
  memcpy(pMyStreamData + pos, &(FIR->SecurityBlock.Length),sizeof(FIR->SecurityBlock.Length));
  pos += sizeof(FIR->SecurityBlock.Length);
  memcpy(pMyStreamData + pos, FIR->SecurityBlock.Data,FIR->SecurityBlock.Length);


 
  return 0;
}

uint32_t CMyBioApi::GetFirLength(BioAPI_BIR *pFIR)
{

    uint32_t nMyStreamLen = sizeof(pFIR->Header)+ sizeof(pFIR->BiometricData.Length) + \
      pFIR->BiometricData.Length + \
      sizeof(pFIR->SecurityBlock.Length) +\
      pFIR->SecurityBlock.Length+sizeof(uint32_t);

  return nMyStreamLen;
}

long CMyBioApi::MakeFIRFromStream(BYTE* pBinaryStream, DWORD dwStreamLength, BioAPI_BIR* pFullFIR)
{
  
  // Convert Stream Data to BIR

  uint32_t nLoadStreamLen = 0;
  uint8_t* pLoadStreamData = pBinaryStream;
  uint32_t nMyStreamLen = 0;


  int pos = 0;

  memcpy(&nMyStreamLen,pLoadStreamData + pos,sizeof(nMyStreamLen));
  pos+=sizeof(nMyStreamLen);
  

  if(nMyStreamLen!=dwStreamLength)
    return -1;

  memcpy(&(pFullFIR->Header), pLoadStreamData + pos, sizeof(pFullFIR->Header));

  pos += sizeof(pFullFIR->Header);

  memcpy(&(pFullFIR->BiometricData.Length), pLoadStreamData + pos,
    sizeof(pFullFIR->BiometricData.Length));

  if(pFullFIR->BiometricData.Length>2048)
    return -1;

  pos += sizeof(pFullFIR->BiometricData.Length);
  pFullFIR->BiometricData.Data = new uint8_t[pFullFIR->BiometricData.Length];


  memcpy(pFullFIR->BiometricData.Data, pLoadStreamData + pos,
    pFullFIR->BiometricData.Length);
  pos += pFullFIR->BiometricData.Length;
  memcpy(&(pFullFIR->SecurityBlock.Length), pLoadStreamData + pos,
    sizeof(pFullFIR->SecurityBlock.Length));

  if(pFullFIR->SecurityBlock.Length>2048)
    return -1;

  pos += sizeof(pFullFIR->SecurityBlock.Length);

  pFullFIR->SecurityBlock.Data = new uint8_t[pFullFIR->SecurityBlock.Length];
  memcpy(pFullFIR->SecurityBlock.Data, pLoadStreamData + pos,
    pFullFIR->SecurityBlock.Length);


  //delete[] pLoadStreamData;
            // User loadBIR ...
  //delete[] loadBIR.BiometricData.Data;
  //delete[] loadBIR.SecurityBlock.Data;

	return 0;
} 


int CMyBioApi::DSS_FP_Enroll(TCHAR * strpayload)
{
 
  BioAPI_BIR m_FullFIR;
  BioAPI_RETURN ret;
  BioAPI_BIR_HANDLE hEnrolledFIR;
  BioAPI_DATA payload;


  bool isstored=false;
  

  if (!isInit || !BioAPI_Enroll) 
	{

    LOGPRINT("�ʱ�ȭ ���� �ʾҽ��ϴ�",8013);
		return DSS_FAILED;
	}
  
  
  BioAPI_INPUT_BIR input_fir;
  
  
  BioAPI_BIR tmpFIR;
  ZeroMemory(&tmpFIR,sizeof(tmpFIR));
  
  
  
	BYTE btTmpBuf[2048];
	memset(btTmpBuf, 0x00, 2048);
	DWORD dwReadLen;



	if( ReadFIRFromScard( btTmpBuf, 2048, &dwReadLen ) != 1 )
	{	
		
		return DSS_FAILED;
	}
	else
	{
    
		if(MakeFIRFromStream(btTmpBuf, dwReadLen, &tmpFIR)!=-1)
    {
      
    if(DSS_FP_CheckHeader(&tmpFIR)==0)
      {

        input_fir.Form=BioAPI_FULLBIR_INPUT;
        input_fir.InputBIR.BIR=&tmpFIR; 
        
        isstored=true;
      }
      else
      {

        if(tmpFIR.BiometricData.Data!=NULL)
         delete[] tmpFIR.BiometricData.Data;

        if(tmpFIR.SecurityBlock.Data!=NULL)
          delete[] tmpFIR.SecurityBlock.Data;

        tmpFIR.BiometricData.Data=NULL;
        tmpFIR.SecurityBlock.Data=NULL;

      }
      
    }//end if
   
	}//end else
  

  
  if(strpayload!=NULL&&_tcscmp(strpayload,_T("")))
	{
		payload.Length = lstrlen(strpayload) + 1;
		payload.Data =(void*) new TCHAR[payload.Length];
		memcpy(payload.Data, strpayload, payload.Length);
		
    if(isstored)
        ret = BioAPI_Enroll(	m_hAttachedSession,BioAPI_PURPOSE_ENROLL_FOR_VERIFICATION_ONLY,
			  BioAPI_DONT_CARE,	NULL,	&input_fir,&hEnrolledFIR,&payload,-1,NULL, NULL);	
     else
      ret = BioAPI_Enroll(	m_hAttachedSession,BioAPI_PURPOSE_ENROLL_FOR_VERIFICATION_ONLY,
			  BioAPI_DONT_CARE,	NULL,	NULL,&hEnrolledFIR,&payload,-1,NULL, NULL);
		
		delete [] payload.Data;
	}
	else
	{
    if(isstored)
      ret = BioAPI_Enroll(	m_hAttachedSession,BioAPI_PURPOSE_ENROLL_FOR_VERIFICATION_ONLY,
			  BioAPI_DONT_CARE,	NULL,	&input_fir,&hEnrolledFIR,NULL,-1,NULL, NULL);
    else
     ret = BioAPI_Enroll(	m_hAttachedSession,BioAPI_PURPOSE_ENROLL_FOR_VERIFICATION_ONLY,
			  BioAPI_DONT_CARE,	NULL,	NULL,&hEnrolledFIR,NULL,-1,NULL, NULL);
	}


  if(tmpFIR.BiometricData.Data!=NULL)
    delete[] tmpFIR.BiometricData.Data;

  if(tmpFIR.SecurityBlock.Data!=NULL)
    delete[] tmpFIR.SecurityBlock.Data;
  
  tmpFIR.BiometricData.Data=NULL;
  tmpFIR.SecurityBlock.Data=NULL;


	if(ret!=BioAPI_OK)
	{

    Error(ret);

		return DSS_FAILED;
	}

  ret = BioAPI_GetBIRFromHandle(m_hAttachedSession,hEnrolledFIR,&m_FullFIR);
    
	if( ret  )
	{

    LOGPRINT("���������� ��ȯ�� �����߽��ϴ�",8013);
		return DSS_FAILED;
	}
	
  
	if (m_BinaryStream)
  {
		delete[] m_BinaryStream;
    m_BinaryStream=NULL;
  }
  
  
	m_dwStreamLength = GetFirLength(&m_FullFIR);
  
  
	m_BinaryStream = new BYTE[m_dwStreamLength];  
  
	memset( m_BinaryStream, 0x00, m_dwStreamLength );
  
	MakeStreamFromFIR(&m_FullFIR, m_BinaryStream );
  
  ret=MakeFIRFromStream(m_BinaryStream, m_dwStreamLength, &tmpFIR);
  

  if(ret!=BioAPI_OK)
  {


    if(tmpFIR.BiometricData.Data!=NULL)
      delete[] tmpFIR.BiometricData.Data;

    if(tmpFIR.SecurityBlock.Data!=NULL)
      delete[] tmpFIR.SecurityBlock.Data;


    if (m_BinaryStream)
    {
	    delete[] m_BinaryStream;
      m_BinaryStream=NULL;
    }

     LOGPRINT("��ĵ�� ���������Ϳ� �̻��� �ֽ��ϴ�",7005);
    return DSS_FAILED;
  }
  

  DWORD len;
  len=GetFirLength(&tmpFIR);


  if(m_dwStreamLength!=len)
  {


   if(tmpFIR.BiometricData.Data!=NULL)
      delete[] tmpFIR.BiometricData.Data;

    if(tmpFIR.SecurityBlock.Data!=NULL)
      delete[] tmpFIR.SecurityBlock.Data;


    if (m_BinaryStream)
    {
	    delete[] m_BinaryStream;
      m_BinaryStream=NULL;
    }

    LOGPRINT("��ĵ�� ���������Ϳ� �̻��� �ֽ��ϴ�",7006);
    return DSS_FAILED;
  }
  
 
  if(tmpFIR.BiometricData.Data!=NULL)
    delete[] tmpFIR.BiometricData.Data;

  if(tmpFIR.SecurityBlock.Data!=NULL)
    delete[] tmpFIR.SecurityBlock.Data;

  
	// scmod �� ����
	if( WriteFIRToScard( m_BinaryStream, m_dwStreamLength ) != 1 )
  {


    if (m_BinaryStream)
    {
	    delete[] m_BinaryStream;
      m_BinaryStream=NULL;
    }

    return DSS_FAILED;
  }
	
  

  if (m_BinaryStream)
  {
	  delete[] m_BinaryStream;
    m_BinaryStream=NULL;
  }

  return 0;
}

int CMyBioApi::DSS_FP_EnrollEx(TCHAR * strpayload, char *readername)
{
 
  BioAPI_BIR m_FullFIR;
  BioAPI_RETURN ret;
  BioAPI_BIR_HANDLE hEnrolledFIR;
  BioAPI_DATA payload;


  bool isstored=false;
  

  if (!isInit || !BioAPI_Enroll) 
	{

    LOGPRINT("�ʱ�ȭ ���� �ʾҽ��ϴ�",8013);
		return DSS_FAILED;
	}
  
  
  BioAPI_INPUT_BIR input_fir;
  
  
  BioAPI_BIR tmpFIR;
  ZeroMemory(&tmpFIR,sizeof(tmpFIR));
  
  
  
	BYTE btTmpBuf[2048];
	memset(btTmpBuf, 0x00, 2048);
	DWORD dwReadLen;



	if( ReadFIRFromScardEx( btTmpBuf, 2048, &dwReadLen, readername ) != 1 )
	{	
		
		return DSS_FAILED;
	}
	else
	{
    
		if(MakeFIRFromStream(btTmpBuf, dwReadLen, &tmpFIR)!=-1)
    {
      
    if(DSS_FP_CheckHeader(&tmpFIR)==0)
      {

        input_fir.Form=BioAPI_FULLBIR_INPUT;
        input_fir.InputBIR.BIR=&tmpFIR; 
        
        isstored=true;
      }
      else
      {

        if(tmpFIR.BiometricData.Data!=NULL)
         delete[] tmpFIR.BiometricData.Data;

        if(tmpFIR.SecurityBlock.Data!=NULL)
          delete[] tmpFIR.SecurityBlock.Data;

        tmpFIR.BiometricData.Data=NULL;
        tmpFIR.SecurityBlock.Data=NULL;

      }
      
    }//end if
   
	}//end else
  

  
  if(strpayload!=NULL&&_tcscmp(strpayload,_T("")))
	{
		payload.Length = lstrlen(strpayload) + 1;
		payload.Data =(void*) new TCHAR[payload.Length];
		memcpy(payload.Data, strpayload, payload.Length);
		
    if(isstored)
        ret = BioAPI_Enroll(	m_hAttachedSession,BioAPI_PURPOSE_ENROLL_FOR_VERIFICATION_ONLY,
			  BioAPI_DONT_CARE,	NULL,	&input_fir,&hEnrolledFIR,&payload,-1,NULL, NULL);	
     else
      ret = BioAPI_Enroll(	m_hAttachedSession,BioAPI_PURPOSE_ENROLL_FOR_VERIFICATION_ONLY,
			  BioAPI_DONT_CARE,	NULL,	NULL,&hEnrolledFIR,&payload,-1,NULL, NULL);
		
		delete [] payload.Data;
	}
	else
	{
    if(isstored)
      ret = BioAPI_Enroll(	m_hAttachedSession,BioAPI_PURPOSE_ENROLL_FOR_VERIFICATION_ONLY,
			  BioAPI_DONT_CARE,	NULL,	&input_fir,&hEnrolledFIR,NULL,-1,NULL, NULL);
    else
     ret = BioAPI_Enroll(	m_hAttachedSession,BioAPI_PURPOSE_ENROLL_FOR_VERIFICATION_ONLY,
			  BioAPI_DONT_CARE,	NULL,	NULL,&hEnrolledFIR,NULL,-1,NULL, NULL);
	}


  if(tmpFIR.BiometricData.Data!=NULL)
    delete[] tmpFIR.BiometricData.Data;

  if(tmpFIR.SecurityBlock.Data!=NULL)
    delete[] tmpFIR.SecurityBlock.Data;
  
  tmpFIR.BiometricData.Data=NULL;
  tmpFIR.SecurityBlock.Data=NULL;


	if(ret!=BioAPI_OK)
	{

    Error(ret);

		return DSS_FAILED;
	}

  ret = BioAPI_GetBIRFromHandle(m_hAttachedSession,hEnrolledFIR,&m_FullFIR);
    
	if( ret  )
	{

    LOGPRINT("���������� ��ȯ�� �����߽��ϴ�",8013);
		return DSS_FAILED;
	}
	
  
	if (m_BinaryStream)
  {
		delete[] m_BinaryStream;
    m_BinaryStream=NULL;
  }
  
  
	m_dwStreamLength = GetFirLength(&m_FullFIR);
  
  
	m_BinaryStream = new BYTE[m_dwStreamLength];  
  
	memset( m_BinaryStream, 0x00, m_dwStreamLength );
  
	MakeStreamFromFIR(&m_FullFIR, m_BinaryStream );
  
  ret=MakeFIRFromStream(m_BinaryStream, m_dwStreamLength, &tmpFIR);
  

  if(ret!=BioAPI_OK)
  {


    if(tmpFIR.BiometricData.Data!=NULL)
      delete[] tmpFIR.BiometricData.Data;

    if(tmpFIR.SecurityBlock.Data!=NULL)
      delete[] tmpFIR.SecurityBlock.Data;


    if (m_BinaryStream)
    {
	    delete[] m_BinaryStream;
      m_BinaryStream=NULL;
    }

     LOGPRINT("��ĵ�� ���������Ϳ� �̻��� �ֽ��ϴ�",7005);
    return DSS_FAILED;
  }
  

  DWORD len;
  len=GetFirLength(&tmpFIR);


  if(m_dwStreamLength!=len)
  {


   if(tmpFIR.BiometricData.Data!=NULL)
      delete[] tmpFIR.BiometricData.Data;

    if(tmpFIR.SecurityBlock.Data!=NULL)
      delete[] tmpFIR.SecurityBlock.Data;


    if (m_BinaryStream)
    {
	    delete[] m_BinaryStream;
      m_BinaryStream=NULL;
    }

    LOGPRINT("��ĵ�� ���������Ϳ� �̻��� �ֽ��ϴ�",7006);
    return DSS_FAILED;
  }
  
 
  if(tmpFIR.BiometricData.Data!=NULL)
    delete[] tmpFIR.BiometricData.Data;

  if(tmpFIR.SecurityBlock.Data!=NULL)
    delete[] tmpFIR.SecurityBlock.Data;

  
	// scmod �� ����
	if( WriteFIRToScardEx( m_BinaryStream, m_dwStreamLength, readername ) != 1 )
  {


    if (m_BinaryStream)
    {
	    delete[] m_BinaryStream;
      m_BinaryStream=NULL;
    }

    return DSS_FAILED;
  }
	
  

  if (m_BinaryStream)
  {
	  delete[] m_BinaryStream;
    m_BinaryStream=NULL;
  }

  return 0;
}


void CMyBioApi::DSS_FP_Destroy_nBio()
{

  BioAPI_RETURN rc;

  isInit=false;

  rc=BioAPI_BSPDetach(m_hAttachedSession);

  rc=BioAPI_BSPUnload(&m_bspuuid,Bio_EventHandler,NULL);


  for (uint32_t i=0; i < m_NumberOfElements; i++)
  {
      if (m_pBSPs[i].Path)
          BioAPI_Free(m_pBSPs[i].Path);
      if (m_pBSPs[i].BSPSupportedFormats)
          BioAPI_Free(m_pBSPs[i].BSPSupportedFormats);
  }

  if (m_pBSPs)
      BioAPI_Free(m_pBSPs);

  rc = BioAPI_Terminate();
}


int CMyBioApi::DSS_FP_CheckCardFinger()
{
  
  BioAPI_BIR tmpFIR;
  
  
  if (!isInit) 
	{
    LOGPRINT("�ʱ�ȭ ���� �ʾҽ��ϴ�.",8013);
		return DSS_FAILED;
	}
  
	memset(&tmpFIR, 0, sizeof(BioAPI_BIR));
  
	BYTE btTmpBuf[2048];
	memset(btTmpBuf, 0x00, 2048);
	DWORD dwReadLen;
  
  
	if( ReadFIRFromScard( btTmpBuf, 2048, &dwReadLen ) != 1 )
	{	
		return DSS_FAILED;
	}
	else
	{
    BioAPI_BIR* pFullFIR;
    pFullFIR=&tmpFIR;
    
    
    memcpy(&pFullFIR->Header, btTmpBuf+sizeof(uint32_t), sizeof(pFullFIR->Header));
    
    if(DSS_FP_CheckHeader(pFullFIR)!=0)
    {
     LOGPRINT("��ū�� ���������Ͱ� �����ϴ�.",8008);
      return DSS_FAILED;
    }
  }
  
  LOGPRINT("",0);
  
  return 0;
}


int CMyBioApi::DSS_FP_CheckCardFingerEx(char *readername)
{
  
  BioAPI_BIR tmpFIR;
  
  
  if (!isInit) 
	{
    LOGPRINT("�ʱ�ȭ ���� �ʾҽ��ϴ�.",8013);
		return DSS_FAILED;
	}
  
	memset(&tmpFIR, 0, sizeof(BioAPI_BIR));
  
	BYTE btTmpBuf[2048];
	memset(btTmpBuf, 0x00, 2048);
	DWORD dwReadLen;
  
  
	if( ReadFIRFromScardEx( btTmpBuf, 2048, &dwReadLen, readername ) != 1 )
	{	
		return DSS_FAILED;
	}
	else
	{
    BioAPI_BIR* pFullFIR;
    pFullFIR=&tmpFIR;
    
    
    memcpy(&pFullFIR->Header, btTmpBuf+sizeof(uint32_t), sizeof(pFullFIR->Header));
    
    if(DSS_FP_CheckHeader(pFullFIR)!=0)
    {
			LOGPRINT("��ū�� ���������Ͱ� �����ϴ�.",8008);
      return DSS_FAILED;
    }
  }
  
  LOGPRINT("",0);
  
  return 0;
}


int CMyBioApi::DSS_FP_CheckHeader(BioAPI_BIR* pFullFIR)
{
  

  if(pFullFIR->Header.Type>80)
    return -1;

  if(pFullFIR->Header.Purpose>6)
    return -1;

  if(pFullFIR->Header.FactorsMask!=8)
    return -1;


  if(pFullFIR->Header.CreationDTG.Date.Year>9999 || 
    pFullFIR->Header.CreationDTG.Date.Month>12 || 
      pFullFIR->Header.CreationDTG.Date.Day>31 ||
        pFullFIR->Header.CreationDTG.Time.Hour>24 ||
        pFullFIR->Header.CreationDTG.Time.Minute>60 ||
        pFullFIR->Header.CreationDTG.Time.Second >60)

    return -1;


  if(pFullFIR->Header.Subtype>80)
    return -1;


  if(pFullFIR->Header.ExpirationDate.Year>9999 ||
    pFullFIR->Header.ExpirationDate.Month>12 ||
    pFullFIR->Header.ExpirationDate.Day>31 )
    return -1;


  if(pFullFIR->BiometricData.Length>2048)
    return -1;

  if(pFullFIR->SecurityBlock.Length>2048)
    return -1;


  return 0;
}

int CMyBioApi::DSS_FP_Verify(TCHAR ** strpayload)
{
 
  BioAPI_RETURN err;
  BioAPI_DATA payload;
  BioAPI_INPUT_BIR input_fir;
  BioAPI_BIR tmpFIR;
  BioAPI_FMR		 MaxFMRRequested	= 0x7fffffff / 10000;
  BioAPI_BOOL		 verified			= BioAPI_FALSE;
  BioAPI_FMR		 FMRAchieved		= 0;
	
  
  if (!isInit || !BioAPI_Verify) 
	{
    LOGPRINT("�ʱ�ȭ ���� �ʾҽ��ϴ�",8013);
		return DSS_FAILED;
	}
  
	memset(&tmpFIR, 0, sizeof(BioAPI_BIR));


	BYTE btTmpBuf[2048];
	memset(btTmpBuf, 0x00, 2048);
	DWORD dwReadLen;


	if( ReadFIRFromScard( btTmpBuf, 2048, &dwReadLen ) != 1 )
	{	
		Sleep(10);
		return DSS_FAILED;
	}
	else
	{
		if(MakeFIRFromStream(btTmpBuf, dwReadLen, &tmpFIR)==-1)
    {
      LOGPRINT("��ū�� ������ �����ϴ�.",8008);
      return DSS_FAILED;
    }

    if(DSS_FP_CheckHeader(&tmpFIR)!=0)
    {
      if(tmpFIR.BiometricData.Data!=NULL)
        delete[] tmpFIR.BiometricData.Data;

      if(tmpFIR.SecurityBlock.Data!=NULL)
        delete[] tmpFIR.SecurityBlock.Data;
      
      LOGPRINT("��ū�� ������ �����ϴ�.",8008);
      return DSS_FAILED;
    }

	}
  
  
  input_fir.Form=BioAPI_FULLBIR_INPUT;
  input_fir.InputBIR.BIR=&tmpFIR; 
	
  
	//err = NBioAPI_Verify(m_hNBioBSP, &input_fir, &result, &payload, 10000, NULL, NULL);	
 	
  
  err = BioAPI_Verify(	m_hAttachedSession,
						MaxFMRRequested,	// BioAPI_FMR *MaxFMRRequested,
						&input_fir,		// BioAPI_INPUT_BIR	*ReferenceTemplate,
						BioAPI_DONT_CARE,	// BioAPI_BIR_SUBTYPE Subtype
						NULL,				// OUT OPTIONAL	BioAPI_BIR_HANDLE *Ad'aptedBIR,
						&verified,			// OUT	BioAPI_BOOL	*Result,
						&FMRAchieved,		// OUT	BioAPI_FMR	*FMRAchieved,
						&payload, //&Payload,			// OUT OPTIONAL	BioAPI_DATA	*Payload, 
						-1,					// Use default BSP timeout 
						NULL);				// We are not interested in audit data 
  
   
	if (err!=BioAPI_OK || !verified)
	{
    
    if(tmpFIR.BiometricData.Data!=NULL)
      delete[] tmpFIR.BiometricData.Data;
    
    if(tmpFIR.SecurityBlock.Data!=NULL)
      delete[] tmpFIR.SecurityBlock.Data;
    
    Error(err);
    
	// ���������� ���� �� ��� payload.Data�� NULL, payload.Length�� 0�� �����Ѵ�. Free�� ���� �ʿ䰡 ���� ���̴�.
	// CP���� payload.Data�� Free�ϸ鼭 ������ �߻��߾���.
	//BioAPI_Free(payload.Data);
    
		return DSS_FAILED;
	}
  
  if(strpayload!=NULL)
  {
    *strpayload=NULL;
    
		if (payload.Length)
		{
      memcpy(g_payloadData,payload.Data,payload.Length);
    }
    else
    {
      memcpy(g_payloadData,"",2);
    }
    
		*strpayload=(TCHAR*)g_payloadData;
	}
  
  
  if(tmpFIR.BiometricData.Data!=NULL)
    delete[] tmpFIR.BiometricData.Data;
  
  if(tmpFIR.SecurityBlock.Data!=NULL)
    delete[] tmpFIR.SecurityBlock.Data;
  
  
  BioAPI_Free(payload.Data);
  
  return 0;
}

int CMyBioApi::DSS_FP_VerifyEx(TCHAR ** strpayload, char *readername)
{
 
  BioAPI_RETURN err;
  BioAPI_DATA payload;
  BioAPI_INPUT_BIR input_fir;
  BioAPI_BIR tmpFIR;
  BioAPI_FMR		 MaxFMRRequested	= 0x7fffffff / 10000;
  BioAPI_BOOL		 verified			= BioAPI_FALSE;
  BioAPI_FMR		 FMRAchieved		= 0;
	
  
  if (!isInit || !BioAPI_Verify) 
	{
    LOGPRINT("�ʱ�ȭ ���� �ʾҽ��ϴ�",8013);
		return DSS_FAILED;
	}
  
	memset(&tmpFIR, 0, sizeof(BioAPI_BIR));


	BYTE btTmpBuf[2048];
	memset(btTmpBuf, 0x00, 2048);
	DWORD dwReadLen;


	if( ReadFIRFromScardEx( btTmpBuf, 2048, &dwReadLen, readername ) != 1 )
	{	
		Sleep(10);
		return DSS_FAILED;
	}
	else
	{
		if(MakeFIRFromStream(btTmpBuf, dwReadLen, &tmpFIR)==-1)
    {
      LOGPRINT("��ū�� ������ �����ϴ�.",8008);
      return DSS_FAILED;
    }

    if(DSS_FP_CheckHeader(&tmpFIR)!=0)
    {
      if(tmpFIR.BiometricData.Data!=NULL)
        delete[] tmpFIR.BiometricData.Data;

      if(tmpFIR.SecurityBlock.Data!=NULL)
        delete[] tmpFIR.SecurityBlock.Data;
      
      LOGPRINT("��ū�� ������ �����ϴ�.",8008);
      return DSS_FAILED;
    }

	}
  
  
  input_fir.Form=BioAPI_FULLBIR_INPUT;
  input_fir.InputBIR.BIR=&tmpFIR; 
	
  
	//err = NBioAPI_Verify(m_hNBioBSP, &input_fir, &result, &payload, 10000, NULL, NULL);	
 	
  
  err = BioAPI_Verify(	m_hAttachedSession,
						MaxFMRRequested,	// BioAPI_FMR *MaxFMRRequested,
						&input_fir,		// BioAPI_INPUT_BIR	*ReferenceTemplate,
						BioAPI_DONT_CARE,	// BioAPI_BIR_SUBTYPE Subtype
						NULL,				// OUT OPTIONAL	BioAPI_BIR_HANDLE *Ad'aptedBIR,
						&verified,			// OUT	BioAPI_BOOL	*Result,
						&FMRAchieved,		// OUT	BioAPI_FMR	*FMRAchieved,
						&payload, //&Payload,			// OUT OPTIONAL	BioAPI_DATA	*Payload, 
						-1,					// Use default BSP timeout 
						NULL);				// We are not interested in audit data 
  
   
	if (err!=BioAPI_OK || !verified)
	{
    
    if(tmpFIR.BiometricData.Data!=NULL)
      delete[] tmpFIR.BiometricData.Data;
    
    if(tmpFIR.SecurityBlock.Data!=NULL)
      delete[] tmpFIR.SecurityBlock.Data;
    
    Error(err);
    BioAPI_Free(payload.Data);
    
		return DSS_FAILED;
	}
  
  if(strpayload!=NULL)
  {
    *strpayload=NULL;
    
		if (payload.Length)
		{
      memcpy(g_payloadData,payload.Data,payload.Length);
    }
    else
    {
      memcpy(g_payloadData,"",2);
    }
    
		*strpayload=(TCHAR*)g_payloadData;
	}
  
  
  if(tmpFIR.BiometricData.Data!=NULL)
    delete[] tmpFIR.BiometricData.Data;
  
  if(tmpFIR.SecurityBlock.Data!=NULL)
    delete[] tmpFIR.SecurityBlock.Data;
  
  
  BioAPI_Free(payload.Data);
  
  return 0;
}



int CMyBioApi::DSS_FP_ChangePayload(TCHAR *strPayload,bool flag)
{
  
  BioAPI_RETURN err;
  BioAPI_DATA payload;
  BioAPI_INPUT_BIR input_fir;
  BioAPI_BIR tmpFIR;
  BioAPI_FMR		 MaxFMRRequested	= 0x7fffffff / 10000;
  BioAPI_BOOL		 verified			= BioAPI_FALSE;
  BioAPI_FMR		 FMRAchieved		= 0;
  
  
  if (!isInit || !BioAPI_Verify)
	{
    
    LOGPRINT("�ʱ�ȭ ���� �ʾҽ��ϴ�",8013);
		return DSS_FAILED;
	}
	
	memset(&tmpFIR, 0, sizeof(BioAPI_BIR));
  
  
  BYTE btTmpBuf[2048];
	memset(btTmpBuf, 0x00, 2048);
  DWORD dwReadLen;
  
  
	if( ReadFIRFromScard( btTmpBuf, 2048, &dwReadLen ) != 1 )
	{	
    
		return DSS_FAILED;
	}
	else
	{
    
		if(MakeFIRFromStream(btTmpBuf, dwReadLen, &tmpFIR)!=0)
    {
      LOGPRINT("��ū�� ������ �����ϴ�.",8008);
      return DSS_FAILED;
    }
	}
  
  if(DSS_FP_CheckHeader(&tmpFIR)!=0)
  {
    LOGPRINT("��ū�� ������ �����ϴ�.",8008);
    return DSS_FAILED;
  }


  input_fir.Form=BioAPI_FULLBIR_INPUT;
  input_fir.InputBIR.BIR=&tmpFIR; 
  
  
  if(flag==true)
  { 
 	  
    err = BioAPI_Verify(	m_hAttachedSession,
						MaxFMRRequested,	// BioAPI_FMR *MaxFMRRequested,
						&input_fir,		// BioAPI_INPUT_BIR	*ReferenceTemplate,
						BioAPI_DONT_CARE,	// BioAPI_BIR_SUBTYPE Subtype
						NULL,				// OUT OPTIONAL	BioAPI_BIR_HANDLE *AdaptedBIR,
						&verified,			// OUT	BioAPI_BOOL	*Result,
						&FMRAchieved,		// OUT	BioAPI_FMR	*FMRAchieved,
						&payload, //&Payload,			// OUT OPTIONAL	BioAPI_DATA	*Payload, 
						-1,					// Use default BSP timeout 
						NULL);				// We are not interested in audit data 


	  if (err||!verified)
	  {

      if(tmpFIR.BiometricData.Data!=NULL)
        delete[] tmpFIR.BiometricData.Data;

      if(tmpFIR.SecurityBlock.Data!=NULL)
        delete[] tmpFIR.SecurityBlock.Data;

      Error(err);
		  return DSS_FAILED;
	  }

  }
  
  
  BioAPI_RETURN	ret;
  BioAPI_BIR_HANDLE hNewTemplate;
  
  
  payload.Length = lstrlen(strPayload) + 1;          // Set payload length
  payload.Data = new BYTE [payload.Length]; // Set payload data
  memcpy(payload.Data, strPayload, payload.Length);
  
  

  
  ret = BioAPI_CreateTemplate(m_hAttachedSession, &input_fir,NULL, NULL,&hNewTemplate, &payload,NULL);
  
  delete[] payload.Data;
  
  
  if(tmpFIR.BiometricData.Data!=NULL)
    delete[] tmpFIR.BiometricData.Data;
  
  if(tmpFIR.SecurityBlock.Data!=NULL)
    delete[] tmpFIR.SecurityBlock.Data;
  
  if(ret)
  {
    LOGPRINT("payload ���濡 �����߽��ϴ�",8011);
    return DSS_FAILED;
  }
  
  
  BioAPI_BIR							m_FullFIR;
	BioAPI_BIR_HANDLE  hEnrolledFIR=hNewTemplate;
  
  
	ret = BioAPI_GetBIRFromHandle(m_hAttachedSession, hEnrolledFIR, &m_FullFIR);
  
  if( ret != BioAPI_OK )
	{
    
    LOGPRINT("���� ������ ��ȯ�� �����߽��ϴ�",8013);
		return DSS_FAILED;
	}
	
  
	if (m_BinaryStream)
		delete[] m_BinaryStream;
  
  
	m_dwStreamLength = GetFirLength(&m_FullFIR);
	m_BinaryStream = new BYTE[m_dwStreamLength];  //@@���� �޸𸮸� �ݵ�� �����ؾ���
	memset( m_BinaryStream, 0x00, m_dwStreamLength );
  
  
	MakeStreamFromFIR( &m_FullFIR, m_BinaryStream );
  
  
	// scmod �� ����
	if( WriteFIRToScard( m_BinaryStream, m_dwStreamLength ) != 1 )
  {
    
    delete[] m_BinaryStream;
    m_BinaryStream=NULL;
    
    
    return DSS_FAILED;
  }
  
  
  delete[] m_BinaryStream;
  m_BinaryStream=NULL;
  
  return 0;
} 
  

int CMyBioApi::DSS_FP_ChangePayloadEx(TCHAR *strPayload,bool flag, char *readername)
{
  
  BioAPI_RETURN err;
  BioAPI_DATA payload;
  BioAPI_INPUT_BIR input_fir;
  BioAPI_BIR tmpFIR;
  BioAPI_FMR		 MaxFMRRequested	= 0x7fffffff / 10000;
  BioAPI_BOOL		 verified			= BioAPI_FALSE;
  BioAPI_FMR		 FMRAchieved		= 0;
  
  
  if (!isInit || !BioAPI_Verify)
	{
    
    LOGPRINT("�ʱ�ȭ ���� �ʾҽ��ϴ�",8013);
		return DSS_FAILED;
	}
	
	memset(&tmpFIR, 0, sizeof(BioAPI_BIR));
  
  
  BYTE btTmpBuf[2048];
	memset(btTmpBuf, 0x00, 2048);
  DWORD dwReadLen;
  
  
	if( ReadFIRFromScardEx( btTmpBuf, 2048, &dwReadLen, readername ) != 1 )
	{	
    
		return DSS_FAILED;
	}
	else
	{
    
		if(MakeFIRFromStream(btTmpBuf, dwReadLen, &tmpFIR)!=0)
    {
      LOGPRINT("��ū�� ������ �����ϴ�.",8008);
      return DSS_FAILED;
    }
	}
  
  if(DSS_FP_CheckHeader(&tmpFIR)!=0)
  {
    LOGPRINT("��ū�� ������ �����ϴ�.",8008);
    return DSS_FAILED;
  }


  input_fir.Form=BioAPI_FULLBIR_INPUT;
  input_fir.InputBIR.BIR=&tmpFIR; 
  
  
  if(flag==true)
  { 
 	  
    err = BioAPI_Verify(	m_hAttachedSession,
						MaxFMRRequested,	// BioAPI_FMR *MaxFMRRequested,
						&input_fir,		// BioAPI_INPUT_BIR	*ReferenceTemplate,
						BioAPI_DONT_CARE,	// BioAPI_BIR_SUBTYPE Subtype
						NULL,				// OUT OPTIONAL	BioAPI_BIR_HANDLE *AdaptedBIR,
						&verified,			// OUT	BioAPI_BOOL	*Result,
						&FMRAchieved,		// OUT	BioAPI_FMR	*FMRAchieved,
						&payload, //&Payload,			// OUT OPTIONAL	BioAPI_DATA	*Payload, 
						-1,					// Use default BSP timeout 
						NULL);				// We are not interested in audit data 


	  if (err||!verified)
	  {

      if(tmpFIR.BiometricData.Data!=NULL)
        delete[] tmpFIR.BiometricData.Data;

      if(tmpFIR.SecurityBlock.Data!=NULL)
        delete[] tmpFIR.SecurityBlock.Data;

      Error(err);
		  return DSS_FAILED;
	  }

  }
  
  
  BioAPI_RETURN	ret;
  BioAPI_BIR_HANDLE hNewTemplate;
  
  
  payload.Length = lstrlen(strPayload) + 1;          // Set payload length
  payload.Data = new BYTE [payload.Length]; // Set payload data
  memcpy(payload.Data, strPayload, payload.Length);
  
  

  
  ret = BioAPI_CreateTemplate(m_hAttachedSession, &input_fir,NULL, NULL,&hNewTemplate, &payload,NULL);
  
  delete[] payload.Data;
  
  
  if(tmpFIR.BiometricData.Data!=NULL)
    delete[] tmpFIR.BiometricData.Data;
  
  if(tmpFIR.SecurityBlock.Data!=NULL)
    delete[] tmpFIR.SecurityBlock.Data;
  
  if(ret)
  {
    LOGPRINT("payload ���濡 �����߽��ϴ�",8011);
    return DSS_FAILED;
  }
  
  
  BioAPI_BIR							m_FullFIR;
	BioAPI_BIR_HANDLE  hEnrolledFIR=hNewTemplate;
  
  
	ret = BioAPI_GetBIRFromHandle(m_hAttachedSession, hEnrolledFIR, &m_FullFIR);
  
  if( ret != BioAPI_OK )
	{
    
    LOGPRINT("���� ������ ��ȯ�� �����߽��ϴ�",8013);
		return DSS_FAILED;
	}
	
  
	if (m_BinaryStream)
		delete[] m_BinaryStream;
  
  
	m_dwStreamLength = GetFirLength(&m_FullFIR);
	m_BinaryStream = new BYTE[m_dwStreamLength];  //@@���� �޸𸮸� �ݵ�� �����ؾ���
	memset( m_BinaryStream, 0x00, m_dwStreamLength );
  
  
	MakeStreamFromFIR( &m_FullFIR, m_BinaryStream );
  
  
	// scmod �� ����
	if( WriteFIRToScardEx( m_BinaryStream, m_dwStreamLength, readername ) != 1 )
  {
    
    delete[] m_BinaryStream;
    m_BinaryStream=NULL;
    
    
    return DSS_FAILED;
  }
  
  
  delete[] m_BinaryStream;
  m_BinaryStream=NULL;
  
  return 0;
} 

  
int CMyBioApi::Register()
{ 
  
  char buffer[MAX_PATH];
  BioAPI_INSTALL_ERROR error;
  BioAPI_BSP_SCHEMA bspSchema;     
  
  
  
  
  memcpy(buffer,"NTGBioBSP20.dll",strlen("NTGBioBSP20.dll")+1);
  HINSTANCE	hModule	= LoadLibrary(buffer);
 
  if(hModule==NULL)
  {
    LOGPRINT("NTGBioBSP20.dll �� ��ġ���� �ʾҽ��ϴ�.",8012);
    FreeLibrary(hModule);
    return DSS_FAILED;
  }
  
  
  //CStrConverter s("ss");
  //bspSchema.Path=ss;
   
  
  BioSPIRI_BSPGetSchema=(BioSPIRI_BSPGetSchema_PTR)GetProcAddress(hModule,"BioSPIRI_BSPGetSchema");
  if(BioSPIRI_BSPGetSchema==NULL)
  {
    LOGPRINT("BioSPIRI_BSPGetSchema �� Address�� �о���� ���߽��ϴ�.",8013);
    FreeLibrary(hModule);
    return DSS_FAILED;
  }

  BioSPI_Free = (BioSPI_Free_PTR) GetProcAddress(hModule, "BioSPI_Free");
  if(BioSPI_Free==NULL)
  {
    LOGPRINT("BioSPI_Free �� Address�� �о���� ���߽��ϴ�.",8013);
    FreeLibrary(hModule);
    return DSS_FAILED;
  }
  
  BioAPI_Util_InstallBSP=(BioAPI_Util_InstallBSP_PTR)GetProcAddress(m_hLib,"BioAPI_Util_InstallBSP");
  if(BioAPI_Util_InstallBSP==NULL)
  {
    LOGPRINT("BioAPI_Util_InstallBSP �� Address�� �о���� ���߽��ϴ�.",8013);
    FreeLibrary(hModule);
    return DSS_FAILED;
  }
  
    
  if (BioAPI_OK != BioSPIRI_BSPGetSchema(&bspSchema))
  {
    LOGPRINT("��Ű���� �ҷ����� ���߽��ϴ�.",8013);
    FreeLibrary(hModule);
    return DSS_FAILED;
  }
  
  
  bspSchema.Path=(unsigned char*)buffer;
  if (BioAPI_OK != BioAPI_Util_InstallBSP(BioAPI_INSTALL_ACTION_INSTALL, &error, &bspSchema))
  {
    LOGPRINT("��Ű�� ��Ͽ� �����߽��ϴ�.",8013);
  
  
    if (bspSchema.BSPSupportedFormats)
	    BioSPI_Free(bspSchema.BSPSupportedFormats);
  
  
    FreeLibrary(hModule);
    return DSS_FAILED;
  }
  
  FreeLibrary(hModule);
  return 0;
}
  






int CMyBioApi::DSS_FP_Enroll_Stream(char **fp,int *len)
{


  BioAPI_BIR m_FullFIR;
  BioAPI_RETURN ret;
  BioAPI_BIR_HANDLE hEnrolledFIR;
//  BioAPI_DATA payload;


  bool isstored=false;
  

  if (!isInit || !BioAPI_Enroll) 
	{

    LOGPRINT("�ʱ�ȭ ���� �ʾҽ��ϴ�",8013);
		return DSS_FAILED;
	}
  
  
  BioAPI_INPUT_BIR input_fir;
  
  
  BioAPI_BIR tmpFIR;
  ZeroMemory(&tmpFIR,sizeof(tmpFIR));
  
  
  
	BYTE btTmpBuf[2048];
	memset(btTmpBuf, 0x00, 2048);
	DWORD dwReadLen;



	if( ReadFIRFromScard( btTmpBuf, 2048, &dwReadLen ) != 1 )
	{	
		
		return DSS_FAILED;
	}
	else
	{
    
		if(MakeFIRFromStream(btTmpBuf, dwReadLen, &tmpFIR)!=-1)
    {
      
    if(DSS_FP_CheckHeader(&tmpFIR)==0)
      {

        input_fir.Form=BioAPI_FULLBIR_INPUT;
        input_fir.InputBIR.BIR=&tmpFIR; 
        
        isstored=true;
      }
      else
      {

        if(tmpFIR.BiometricData.Data!=NULL)
         delete[] tmpFIR.BiometricData.Data;

        if(tmpFIR.SecurityBlock.Data!=NULL)
          delete[] tmpFIR.SecurityBlock.Data;

        tmpFIR.BiometricData.Data=NULL;
        tmpFIR.SecurityBlock.Data=NULL;

      }
      
    }//end if
   
	}//end else


	
  if(isstored)
    ret = BioAPI_Enroll(	m_hAttachedSession,BioAPI_PURPOSE_ENROLL_FOR_VERIFICATION_ONLY,
			BioAPI_DONT_CARE,	NULL,	&input_fir,&hEnrolledFIR,NULL,-1,NULL, NULL);
  else
   ret = BioAPI_Enroll(	m_hAttachedSession,BioAPI_PURPOSE_ENROLL_FOR_VERIFICATION_ONLY,
			BioAPI_DONT_CARE,	NULL,	NULL,&hEnrolledFIR,NULL,-1,NULL, NULL);



  if(tmpFIR.BiometricData.Data!=NULL)
    delete[] tmpFIR.BiometricData.Data;

  if(tmpFIR.SecurityBlock.Data!=NULL)
    delete[] tmpFIR.SecurityBlock.Data;
  
  tmpFIR.BiometricData.Data=NULL;
  tmpFIR.SecurityBlock.Data=NULL;


	if(ret!=BioAPI_OK)
	{

    Error(ret);

		return DSS_FAILED;
	}

  ret = BioAPI_GetBIRFromHandle(m_hAttachedSession,hEnrolledFIR,&m_FullFIR);
    
	if( ret  )
	{

    LOGPRINT("���������� ��ȯ�� �����߽��ϴ�",8013);
		return DSS_FAILED;
	}
	
  

  
	m_dwStreamLength = GetFirLength(&m_FullFIR);
	//m_BinaryStream = new BYTE[m_dwStreamLength];  
  
  
	memset( g_payloadData, 0x00, m_dwStreamLength );
	MakeStreamFromFIR(&m_FullFIR,(unsigned char*) g_payloadData );

  *fp=g_payloadData;
  *len=m_dwStreamLength;

  return 0;
}



int CMyBioApi::DSS_FP_Enroll_StreamEx(char **fp, int *len, char *readername)
{


  BioAPI_BIR m_FullFIR;
  BioAPI_RETURN ret;
  BioAPI_BIR_HANDLE hEnrolledFIR;
//  BioAPI_DATA payload;


  bool isstored=false;
  

  if (!isInit || !BioAPI_Enroll) 
	{

    LOGPRINT("�ʱ�ȭ ���� �ʾҽ��ϴ�",8013);
		return DSS_FAILED;
	}
  
  
  BioAPI_INPUT_BIR input_fir;
  
  
  BioAPI_BIR tmpFIR;
  ZeroMemory(&tmpFIR,sizeof(tmpFIR));
  
  
  
	BYTE btTmpBuf[2048];
	memset(btTmpBuf, 0x00, 2048);
	DWORD dwReadLen;



	if( ReadFIRFromScardEx( btTmpBuf, 2048, &dwReadLen, readername ) != 1 )
	{	
		
		return DSS_FAILED;
	}
	else
	{
    
		if(MakeFIRFromStream(btTmpBuf, dwReadLen, &tmpFIR)!=-1)
    {
      
    if(DSS_FP_CheckHeader(&tmpFIR)==0)
      {

        input_fir.Form=BioAPI_FULLBIR_INPUT;
        input_fir.InputBIR.BIR=&tmpFIR; 
        
        isstored=true;
      }
      else
      {

        if(tmpFIR.BiometricData.Data!=NULL)
         delete[] tmpFIR.BiometricData.Data;

        if(tmpFIR.SecurityBlock.Data!=NULL)
          delete[] tmpFIR.SecurityBlock.Data;

        tmpFIR.BiometricData.Data=NULL;
        tmpFIR.SecurityBlock.Data=NULL;

      }
      
    }//end if
   
	}//end else


	
  if(isstored)
    ret = BioAPI_Enroll(	m_hAttachedSession,BioAPI_PURPOSE_ENROLL_FOR_VERIFICATION_ONLY,
			BioAPI_DONT_CARE,	NULL,	&input_fir,&hEnrolledFIR,NULL,-1,NULL, NULL);
  else
   ret = BioAPI_Enroll(	m_hAttachedSession,BioAPI_PURPOSE_ENROLL_FOR_VERIFICATION_ONLY,
			BioAPI_DONT_CARE,	NULL,	NULL,&hEnrolledFIR,NULL,-1,NULL, NULL);



  if(tmpFIR.BiometricData.Data!=NULL)
    delete[] tmpFIR.BiometricData.Data;

  if(tmpFIR.SecurityBlock.Data!=NULL)
    delete[] tmpFIR.SecurityBlock.Data;
  
  tmpFIR.BiometricData.Data=NULL;
  tmpFIR.SecurityBlock.Data=NULL;


	if(ret!=BioAPI_OK)
	{

    Error(ret);

		return DSS_FAILED;
	}

  ret = BioAPI_GetBIRFromHandle(m_hAttachedSession,hEnrolledFIR,&m_FullFIR);
    
	if( ret  )
	{

    LOGPRINT("���������� ��ȯ�� �����߽��ϴ�",8013);
		return DSS_FAILED;
	}
	
  

  
	m_dwStreamLength = GetFirLength(&m_FullFIR);
	//m_BinaryStream = new BYTE[m_dwStreamLength];  
  
  
	memset( g_payloadData, 0x00, m_dwStreamLength );
	MakeStreamFromFIR(&m_FullFIR,(unsigned char*) g_payloadData );

  *fp=g_payloadData;
  *len=m_dwStreamLength;

  return 0;
}


int CMyBioApi::DSS_FP_Enroll_Stream_Write(char* btTmpBuf,int len,char *strpayload)
{

  BioAPI_DATA payload;
  BioAPI_INPUT_BIR input_fir;
  BioAPI_BIR tmpFIR;
  BioAPI_FMR		 MaxFMRRequested	= 0x7fffffff / 10000;
  BioAPI_BOOL		 verified			= BioAPI_FALSE;
  BioAPI_FMR		 FMRAchieved		= 0;
  
  
  if (!isInit || !BioAPI_Verify)
	{
    
    LOGPRINT("�ʱ�ȭ ���� �ʾҽ��ϴ�",8013);
		return DSS_FAILED;
	}
	
	memset(&tmpFIR, 0, sizeof(BioAPI_BIR));
  


  if(MakeFIRFromStream((unsigned char*)btTmpBuf, len, &tmpFIR)!=0)
  {
    LOGPRINT("Enroll�� �߸��Ǿ����ϴ�.",8007);
    return DSS_FAILED;
  }

  

  input_fir.Form=BioAPI_FULLBIR_INPUT;
  input_fir.InputBIR.BIR=&tmpFIR; 
  
  
  
  BioAPI_RETURN	ret;
  BioAPI_BIR_HANDLE hNewTemplate;
  
  
  payload.Length = lstrlen(strpayload) + 1;          // Set payload length
  payload.Data = new BYTE [payload.Length]; // Set payload data
  memcpy(payload.Data, strpayload, payload.Length);
  
  

  
  ret = BioAPI_CreateTemplate(m_hAttachedSession, &input_fir,NULL, NULL,&hNewTemplate, &payload,NULL);
  
  delete[] payload.Data;
  
  
  if(tmpFIR.BiometricData.Data!=NULL)
    delete[] tmpFIR.BiometricData.Data;
  
  if(tmpFIR.SecurityBlock.Data!=NULL)
    delete[] tmpFIR.SecurityBlock.Data;
  
  if(ret)
  {
    LOGPRINT("payload ���濡 �����߽��ϴ�",8011);
    return DSS_FAILED;
  }
  
  
  BioAPI_BIR							m_FullFIR;
	BioAPI_BIR_HANDLE  hEnrolledFIR=hNewTemplate;
  
  
	ret = BioAPI_GetBIRFromHandle(m_hAttachedSession, hEnrolledFIR, &m_FullFIR);
  
  if( ret != BioAPI_OK )
	{
    
    LOGPRINT("���� ������ ��ȯ�� �����߽��ϴ�",8013);
		return DSS_FAILED;
	}
	
  
	if (m_BinaryStream)
		delete[] m_BinaryStream;
  
  
	m_dwStreamLength = GetFirLength(&m_FullFIR);
	m_BinaryStream = new BYTE[m_dwStreamLength];  //@@���� �޸𸮸� �ݵ�� �����ؾ���
	memset( m_BinaryStream, 0x00, m_dwStreamLength );
  
  
	MakeStreamFromFIR( &m_FullFIR, m_BinaryStream );
  
  
	// scmod �� ����
	if( WriteFIRToScard( m_BinaryStream, m_dwStreamLength ) != 1 )
  {
    
    delete[] m_BinaryStream;
    m_BinaryStream=NULL;
    
    
    return DSS_FAILED;
  }
  
  
  delete[] m_BinaryStream;
  m_BinaryStream=NULL;
  


  return 0;//DSS_FAILED
}


int CMyBioApi::DSS_FP_Enroll_Stream_WriteEx(char* btTmpBuf,int len,char *strpayload, char *readername)
{

  BioAPI_DATA payload;
  BioAPI_INPUT_BIR input_fir;
  BioAPI_BIR tmpFIR;
  BioAPI_FMR		 MaxFMRRequested	= 0x7fffffff / 10000;
  BioAPI_BOOL		 verified			= BioAPI_FALSE;
  BioAPI_FMR		 FMRAchieved		= 0;
  
  
  if (!isInit || !BioAPI_Verify)
	{
    
    LOGPRINT("�ʱ�ȭ ���� �ʾҽ��ϴ�",8013);
		return DSS_FAILED;
	}
	
	memset(&tmpFIR, 0, sizeof(BioAPI_BIR));
  


  if(MakeFIRFromStream((unsigned char*)btTmpBuf, len, &tmpFIR)!=0)
  {
    LOGPRINT("Enroll�� �߸��Ǿ����ϴ�.",8007);
    return DSS_FAILED;
  }

  

  input_fir.Form=BioAPI_FULLBIR_INPUT;
  input_fir.InputBIR.BIR=&tmpFIR; 
  
  
  
  BioAPI_RETURN	ret;
  BioAPI_BIR_HANDLE hNewTemplate;
  
  
  payload.Length = lstrlen(strpayload) + 1;          // Set payload length
  payload.Data = new BYTE [payload.Length]; // Set payload data
  memcpy(payload.Data, strpayload, payload.Length);
  
  

  
  ret = BioAPI_CreateTemplate(m_hAttachedSession, &input_fir,NULL, NULL,&hNewTemplate, &payload,NULL);
  
  delete[] payload.Data;
  
  
  if(tmpFIR.BiometricData.Data!=NULL)
    delete[] tmpFIR.BiometricData.Data;
  
  if(tmpFIR.SecurityBlock.Data!=NULL)
    delete[] tmpFIR.SecurityBlock.Data;
  
  if(ret)
  {
    LOGPRINT("payload ���濡 �����߽��ϴ�",8011);
    return DSS_FAILED;
  }
  
  
  BioAPI_BIR							m_FullFIR;
	BioAPI_BIR_HANDLE  hEnrolledFIR=hNewTemplate;
  
  
	ret = BioAPI_GetBIRFromHandle(m_hAttachedSession, hEnrolledFIR, &m_FullFIR);
  
  if( ret != BioAPI_OK )
	{
    
    LOGPRINT("���� ������ ��ȯ�� �����߽��ϴ�",8013);
		return DSS_FAILED;
	}
	
  
	if (m_BinaryStream)
		delete[] m_BinaryStream;
  
  
	m_dwStreamLength = GetFirLength(&m_FullFIR);
	m_BinaryStream = new BYTE[m_dwStreamLength];  //@@���� �޸𸮸� �ݵ�� �����ؾ���
	memset( m_BinaryStream, 0x00, m_dwStreamLength );
  
  
	MakeStreamFromFIR( &m_FullFIR, m_BinaryStream );
  
  
	// scmod �� ����
	if( WriteFIRToScardEx( m_BinaryStream, m_dwStreamLength, readername ) != 1 )
  {
    
    delete[] m_BinaryStream;
    m_BinaryStream=NULL;
    
    
    return DSS_FAILED;
  }
  
  
  delete[] m_BinaryStream;
  m_BinaryStream=NULL;
  


  return 0;//DSS_FAILED
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  ���� : ���� Capture �ð��� �����Ͽ� ������ ���� ��´�.
//
//	���� : npStartTick
//					- ĸ�İ� ���۵Ǵ� ������ Tick Count�� ���´�.
//				 npCapture_StartTick
//					- ĸ�� ������ ó������ ������ �ԷµǴ� ����(Progressive Bar�� �����̴� ����)�� Tick Count�� ���´�.
//				 npCapture_EndTick
//					- ĸ���� ����Ǵ� ������ Tick Count�� ���´�.
//
//	��� : Capture�� ����� ���� Sensor�� Unit�� ControlUnit ����� ���� ���� ��´�.
//
//				 BioAPI_ControlUnit( ���� Attach�� BSP�� Handle, Unit ID (Sensor�� Unit ID�� 1), 
//														 Control Code (3 ~ 5 �� ���), ������ �� Data, ���� �� Data);
//
//	Control Code -> 3 : ĸ�İ� ���۵Ǵ� ������ Tick Count�� ���´�.
//									4 : ĸ�� ������ ó������ ������ �ԷµǴ� ����(Progressive Bar�� �����̴� ����)�� Tick Count�� ���´�.
//									5 : ĸ�İ� ����Ǵ� ������ Tick Count�� ���´�.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CMyBioApi::DSS_FP_GetControlUnitTime(int *npStartTick, int *npCapture_StartTick, int *npCapture_EndTick)
{
	BYTE			NITGEN_UUID[16] = {0xde, 0x62, 0xc7, 0xb0, 0x26, 0x42, 0x4a, 0x09, 0x83, 0xe6, 0x10, 0xc4, 0x8f, 0x17, 0xb2, 0x22};
	uint32_t	iBSP=0;
		
	if( m_NumberOfElements == 0 )
	{
		LOGPRINT("��Ʈ�� ����Ʈ��� ��ġ�����ʾҽ��ϴ�",50002);
		return DSS_FAILED;
	}
	
	for ( iBSP=0; iBSP < m_NumberOfElements; iBSP++ )
	{
		// ���� ���� Attach�� BSP�� ��Ʈ���� BSP�� ������쿡�� ����...
		if( memcmp(m_pBSPs[iBSP].BSPUuid, NITGEN_UUID, sizeof(NITGEN_UUID)) == 0 )
		{
			BioAPI_RETURN bioReturn;
			BioAPI_DATA		bioTempData, bioOutData;
			
			memset(&bioTempData, 0, sizeof(BioAPI_DATA));
			memset(&bioOutData,  0, sizeof(BioAPI_DATA));

			// �� ����� NTGBioBSP20.dll�� ���� v2.3.0.0 �̻��̰� NBioBSP.dll�� ���� v4.7.6.0 �̻��϶��� �����Ѵ�.
			bioReturn = BioAPI_ControlUnit(m_hAttachedSession, 1, 3, &bioTempData, &bioOutData);
			memcpy(npStartTick, bioOutData.Data, bioOutData.Length);
			BioAPI_Free(bioOutData.Data);
			
			bioReturn = BioAPI_ControlUnit(m_hAttachedSession, 1, 4, &bioTempData, &bioOutData);
			memcpy(npCapture_StartTick, bioOutData.Data, bioOutData.Length);
			BioAPI_Free(bioOutData.Data);
			
			bioReturn = BioAPI_ControlUnit(m_hAttachedSession, 1, 5, &bioTempData, &bioOutData);
			memcpy(npCapture_EndTick, bioOutData.Data, bioOutData.Length);
			BioAPI_Free(bioOutData.Data);
			return 0;
		}
	}

	LOGPRINT("��Ʈ�� ����Ʈ���� ������ ���� �ʽ��ϴ�.",8019);
	return DSS_FAILED;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  ���� : ���� ��Ͻ� Security Level�� �����Ѵ�.
//
//	���� : secuLevel
//					- Security Level�� �����Ѵ�. ( 1 ~ 9 )
//					 => ���� �������� ���� ������ ���е��� ��������.
//
//	��� : ���� ����̳� ������ �ϱ� ������ Matching�� Unit�� ControlUnit ����� ���� �����Ѵ�.
//
//				 BioAPI_ControlUnit( ���� Attach�� BSP�� Handle, Unit ID (Maching�� Unit ID�� 3), 
//														 Control Code (0 = ������ Security Level / 1 = ��Ͽ�), ������ �� Data, ������ �� Data)
//									 
//					- ���� Ȯ�θ� �� ��쿡�� ������ �� Data�� NULL�� �־ �ȴ�.
//					- ���� ������ �� ��쿡�� ������ �� Data�� NULL�� �־ �ȴ�.
//					- ���� �ٲ��� BSP Handle�� Detach�ϸ� ���� �ʱ�ȭ �Ǿ� �������� �ٽ� Attach�� �� ��쿡�� �� ���� ���־�� �Ѵ�.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CMyBioApi::DSS_FP_SetEnrollSecurityLevel(unsigned int secuLevel)
{
	BYTE			NITGEN_UUID[16] = {0xde, 0x62, 0xc7, 0xb0, 0x26, 0x42, 0x4a, 0x09, 0x83, 0xe6, 0x10, 0xc4, 0x8f, 0x17, 0xb2, 0x22};
	uint32_t	iBSP=0;

	if( m_NumberOfElements == 0 )
	{
		LOGPRINT("��Ʈ�� ����Ʈ��� ��ġ�����ʾҽ��ϴ�",50002);
		return DSS_FAILED;
	}
		
	for ( iBSP=0; iBSP < m_NumberOfElements; iBSP++ )
	{
		// ���� ���� Attach�� BSP�� ��Ʈ���� BSP�� ������쿡�� ����...
		if( memcmp(m_pBSPs[iBSP].BSPUuid, NITGEN_UUID, sizeof(NITGEN_UUID)) == 0 )
		{
			BioAPI_RETURN bioReturn;
			BioAPI_DATA bioData, bioOutData;
			memset(&bioData, 0, sizeof(BioAPI_DATA));
			
			// �� ����� NTGBioBSP20.dll�� ���� v2.3.0.0 �̻��̰� NBioBSP.dll v4.7.6.0 �̻��϶��� �����Ѵ�.
			uint32_t secuLevel = 3;
			bioData.Length = sizeof(uint32_t);
			bioData.Data = &secuLevel;
			
			bioReturn = BioAPI_ControlUnit(m_hAttachedSession, 3, 1, &bioData, &bioOutData);
			
			BioAPI_Free(bioOutData.Data);

			return 0;
		}
	}

	LOGPRINT("��Ʈ�� ����Ʈ���� ������ ���� �ʽ��ϴ�.",8019);
	return DSS_FAILED;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  ���� : ���� ������ Security Level�� �����Ѵ�.
//
//	���� : secuLevel
//					- Security Level�� �����Ѵ�. ( 1 ~ 9 )
//					 => ���� �������� ���� ������ ���е��� ��������.
//
//	��� : ���� ����̳� ������ �ϱ� ������ Matching�� Unit�� ControlUnit ����� ���� �����Ѵ�.
//
//				 BioAPI_ControlUnit( ���� Attach�� BSP�� Handle, Unit ID (Maching�� Unit ID�� 3), 
//														 Control Code (0 = ������ Security Level / 1 = ��Ͽ�), ������ �� Data, ������ �� Data)
//									 
//					- ���� Ȯ�θ� �� ��쿡�� ������ �� Data�� NULL�� �־ �ȴ�.
//					- ���� ������ �� ��쿡�� ������ �� Data�� NULL�� �־ �ȴ�.
//					- ���� �ٲ��� BSP Handle�� Detach�ϸ� ���� �ʱ�ȭ �Ǿ� �������� �ٽ� Attach�� �� ��쿡�� �� ���� ���־�� �Ѵ�.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CMyBioApi::DSS_FP_SetVerifySecurityLevel(unsigned int secuLevel)
{
	BYTE			NITGEN_UUID[16] = {0xde, 0x62, 0xc7, 0xb0, 0x26, 0x42, 0x4a, 0x09, 0x83, 0xe6, 0x10, 0xc4, 0x8f, 0x17, 0xb2, 0x22};
	uint32_t	iBSP=0;

	if( m_NumberOfElements == 0 )
	{
		LOGPRINT("��Ʈ�� ����Ʈ��� ��ġ�����ʾҽ��ϴ�",50002);
		return DSS_FAILED;
	}
		
	for ( iBSP=0; iBSP < m_NumberOfElements; iBSP++ )
	{
		// ���� ���� Attach�� BSP�� ��Ʈ���� BSP�� ������쿡�� ����...
		if( memcmp(m_pBSPs[iBSP].BSPUuid, NITGEN_UUID, sizeof(NITGEN_UUID)) == 0 )
		{
			BioAPI_RETURN bioReturn;
			BioAPI_DATA bioData, bioOutData;
			memset(&bioData, 0, sizeof(BioAPI_DATA));
			
			// �� ����� NTGBioBSP20.dll�� ���� v2.3.0.0 �̻��̰� NBioBSP.dll v4.7.6.0 �̻��϶��� �����Ѵ�.
			uint32_t secuLevel = 3;
			bioData.Length = sizeof(uint32_t);
			bioData.Data = &secuLevel;
			
			bioReturn = BioAPI_ControlUnit(m_hAttachedSession, 3, 0, &bioData, &bioOutData);
			
			return 0;
		}
	}

	LOGPRINT("��Ʈ�� ����Ʈ���� ������ ���� �ʽ��ϴ�.",8019);
	return DSS_FAILED;
}

/*
int CMyBioApi::DSS_FP_Capture(char **fp,int *len)
{


  BioAPI_BIR m_FullFIR;
  BioAPI_RETURN ret;
  BioAPI_BIR_HANDLE hEnrolledFIR;
//  BioAPI_DATA payload;

  if (!isInit || !BioAPI_Capture) 
	{

    LOGPRINT("�ʱ�ȭ ���� �ʾҽ��ϴ�",8013);
		return DSS_FAILED;
	}
  
  
  BioAPI_INPUT_BIR input_fir;
  
  
  BioAPI_BIR tmpFIR;
  ZeroMemory(&tmpFIR,sizeof(tmpFIR));
  
  
  
	BYTE btTmpBuf[2048];
	memset(btTmpBuf, 0x00, 2048);
	DWORD dwReadLen;



//	if( ReadFIRFromScard( btTmpBuf, 2048, &dwReadLen ) != 1 )
//	{	
//		
//		return DSS_FAILED;
//	}
//	else
//	{
//    
//		if(MakeFIRFromStream(btTmpBuf, dwReadLen, &tmpFIR)!=-1)
//    {
//      
//    if(DSS_FP_CheckHeader(&tmpFIR)==0)
//      {
//
//        input_fir.Form=BioAPI_FULLBIR_INPUT;
//        input_fir.InputBIR.BIR=&tmpFIR; 
//        
//      }
//      else
//      {
//
//        if(tmpFIR.BiometricData.Data!=NULL)
//         delete[] tmpFIR.BiometricData.Data;
//
//        if(tmpFIR.SecurityBlock.Data!=NULL)
//          delete[] tmpFIR.SecurityBlock.Data;
//
//        tmpFIR.BiometricData.Data=NULL;
//        tmpFIR.SecurityBlock.Data=NULL;
//
//      }
//      
//    }//end if
//   
//	}//end else


	ret = BioAPI_Capture(m_hAttachedSession, BioAPI_PURPOSE_VERIFY, BioAPI_DONT_CARE, NULL, &hEnrolledFIR, -1, NULL);


//
//  if(tmpFIR.BiometricData.Data!=NULL)
//    delete[] tmpFIR.BiometricData.Data;
//
//  if(tmpFIR.SecurityBlock.Data!=NULL)
//    delete[] tmpFIR.SecurityBlock.Data;
//  
//  tmpFIR.BiometricData.Data=NULL;
//  tmpFIR.SecurityBlock.Data=NULL;


	if(ret!=BioAPI_OK)
	{

    Error(ret);

		return DSS_FAILED;
	}

  ret = BioAPI_GetBIRFromHandle(m_hAttachedSession,hEnrolledFIR,&m_FullFIR);
    
	if( ret  )
	{

    LOGPRINT("���������� ��ȯ�� �����߽��ϴ�",8013);
		return DSS_FAILED;
	}
	
  m_FullFIR.Header.Purpose = 4;

  
	m_dwStreamLength = GetFirLength(&m_FullFIR);
	//m_BinaryStream = new BYTE[m_dwStreamLength];  
  
  
	memset( g_payloadData, 0x00, m_dwStreamLength );
	MakeStreamFromFIR(&m_FullFIR,(unsigned char*) g_payloadData );

  *fp=g_payloadData;
  *len=m_dwStreamLength;



	{
	
	BioAPI_RETURN err;
  BioAPI_DATA payload;
//  BioAPI_INPUT_BIR input_fir;
//  BioAPI_BIR tmpFIR;
  BioAPI_FMR		 MaxFMRRequested	= 0x7fffffff / 10000;
  BioAPI_BOOL		 verified			= BioAPI_FALSE;
  BioAPI_FMR		 FMRAchieved		= 0;

	memcpy(btTmpBuf, g_payloadData, m_dwStreamLength);
	dwReadLen = m_dwStreamLength;

		if(MakeFIRFromStream(btTmpBuf, dwReadLen, &tmpFIR)!=-1)
    {
      
			if(DSS_FP_CheckHeader(&tmpFIR)==0)
      {
				
        input_fir.Form=BioAPI_FULLBIR_INPUT;
        input_fir.InputBIR.BIR=&tmpFIR; 
        
      }
      else
      {
				
        if(tmpFIR.BiometricData.Data!=NULL)
					delete[] tmpFIR.BiometricData.Data;
				
        if(tmpFIR.SecurityBlock.Data!=NULL)
          delete[] tmpFIR.SecurityBlock.Data;
				
        tmpFIR.BiometricData.Data=NULL;
        tmpFIR.SecurityBlock.Data=NULL;
				
      }
      
    }//end if


		err = BioAPI_Verify(	m_hAttachedSession,
						MaxFMRRequested,	// BioAPI_FMR *MaxFMRRequested,
						&input_fir,		// BioAPI_INPUT_BIR	*ReferenceTemplate,
						BioAPI_DONT_CARE,	// BioAPI_BIR_SUBTYPE Subtype
						NULL,				// OUT OPTIONAL	BioAPI_BIR_HANDLE *Ad'aptedBIR,
						&verified,			// OUT	BioAPI_BOOL	*Result,
						&FMRAchieved,		// OUT	BioAPI_FMR	*FMRAchieved,
						NULL, //&Payload,			// OUT OPTIONAL	BioAPI_DATA	*Payload, 
						-1,					// Use default BSP timeout 
						NULL);				// We are not interested in audit data 
		
		
		if (err!=BioAPI_OK || !verified)
		{
			
			if(tmpFIR.BiometricData.Data!=NULL)
				delete[] tmpFIR.BiometricData.Data;
			
			if(tmpFIR.SecurityBlock.Data!=NULL)
				delete[] tmpFIR.SecurityBlock.Data;
			
			Error(err);
			BioAPI_Free(payload.Data);
			
			return DSS_FAILED;
		}
		
	
	}


  return 0;
}
*/

int CMyBioApi::DSS_FP_Capture(char **fp,int *len)
{
  BioAPI_BIR m_FullFIR;
  BioAPI_RETURN ret;
  BioAPI_BIR_HANDLE hEnrolledFIR;

  if (!isInit || !BioAPI_Capture) 
	{
    LOGPRINT("�ʱ�ȭ ���� �ʾҽ��ϴ�",8013);
		return DSS_FAILED;
	}
  
	ret = BioAPI_Capture(m_hAttachedSession, BioAPI_PURPOSE_VERIFY, BioAPI_DONT_CARE, NULL, &hEnrolledFIR, -1, NULL);

	if(ret!=BioAPI_OK)
	{
    Error(ret);
		return DSS_FAILED;
	}

  ret = BioAPI_GetBIRFromHandle(m_hAttachedSession,hEnrolledFIR,&m_FullFIR);
    
	if( ret  )
	{
    LOGPRINT("���������� ��ȯ�� �����߽��ϴ�",8013);
		return DSS_FAILED;
	}
	
//  m_FullFIR.Header.Purpose = 4;
 
	m_dwStreamLength = GetFirLength(&m_FullFIR);
  
	memset( g_payloadData, 0x00, m_dwStreamLength );
	MakeStreamFromFIR(&m_FullFIR,(unsigned char*) g_payloadData );

  *fp=g_payloadData;
  *len=m_dwStreamLength;

  return 0;
}


int CMyBioApi::DSS_FP_CapturedVerify(BYTE *byteData, int dwReadLen)
{
	BioAPI_RETURN err;
	BioAPI_INPUT_BIR input_fir;
	BioAPI_BIR tmpFIR;
  BioAPI_FMR		 MaxFMRRequested	= 0x7fffffff / 10000;
  BioAPI_BOOL		 verified			= BioAPI_FALSE;
  BioAPI_FMR		 FMRAchieved		= 0;
	
	if(MakeFIRFromStream(byteData, dwReadLen, &tmpFIR)!=-1)
  {
		if(DSS_FP_CheckHeader(&tmpFIR)==0)
    {
      input_fir.Form=BioAPI_FULLBIR_INPUT;
      input_fir.InputBIR.BIR=&tmpFIR; 
    }
    else
    {
      if(tmpFIR.BiometricData.Data!=NULL)
				delete[] tmpFIR.BiometricData.Data;
			
      if(tmpFIR.SecurityBlock.Data!=NULL)
        delete[] tmpFIR.SecurityBlock.Data;
			
      tmpFIR.BiometricData.Data=NULL;
      tmpFIR.SecurityBlock.Data=NULL;
    }
    
  }//end if
	
	err = BioAPI_Verify(	m_hAttachedSession,
					MaxFMRRequested,	// BioAPI_FMR *MaxFMRRequested,
					&input_fir,		// BioAPI_INPUT_BIR	*ReferenceTemplate,
					BioAPI_DONT_CARE,	// BioAPI_BIR_SUBTYPE Subtype
					NULL,				// OUT OPTIONAL	BioAPI_BIR_HANDLE *Ad'aptedBIR,
					&verified,			// OUT	BioAPI_BOOL	*Result,
					&FMRAchieved,		// OUT	BioAPI_FMR	*FMRAchieved,
					NULL, //&Payload,			// OUT OPTIONAL	BioAPI_DATA	*Payload, 
					-1,					// Use default BSP timeout 
					NULL);				// We are not interested in audit data 
	
	
	if (err!=BioAPI_OK || !verified)
	{
		if(tmpFIR.BiometricData.Data!=NULL)
			delete[] tmpFIR.BiometricData.Data;
		
		if(tmpFIR.SecurityBlock.Data!=NULL)
			delete[] tmpFIR.SecurityBlock.Data;
		
		Error(err);

		return DSS_FAILED;
	}

	return 0;	
}