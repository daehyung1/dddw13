#pragma once
#include "BioApi.h"
#include "bioapi_reg.h"
#include "biospi.h"

#include "DSS.h"

#define MAX_BSPS 20


class CMyBioApi :public CBioApiObject
{
protected:


  BYTE*													m_BinaryStream;
  HINSTANCE											m_hLib;

  BioAPI_Init_PTR								BioAPI_Init;
  BioAPI_Terminate_PTR					BioAPI_Terminate;
  BioAPI_EnumBSPs_PTR						BioAPI_EnumBSPs;
  BioAPI_BSPLoad_PTR						BioAPI_BSPLoad;
  BioAPI_BSPUnload_PTR					BioAPI_BSPUnload;
  BioAPI_BSPAttach_PTR					BioAPI_BSPAttach;
  BioAPI_BSPDetach_PTR					BioAPI_BSPDetach;

  BioAPI_Enroll_PTR							BioAPI_Enroll;
  BioAPI_Verify_PTR							BioAPI_Verify;
  BioAPI_GetBIRFromHandle_PTR		BioAPI_GetBIRFromHandle;
  BioAPI_CreateTemplate_PTR			BioAPI_CreateTemplate;
	
	BioAPI_ControlUnit_PTR				BioAPI_ControlUnit;

  BioAPI_FreeBIRHandle_PTR			BioAPI_FreeBIRHandle;
  BioAPI_Free_PTR								BioAPI_Free;

  BioAPI_Util_InstallBSP_PTR		BioAPI_Util_InstallBSP;
  BioSPIRI_BSPGetSchema_PTR			BioSPIRI_BSPGetSchema;
  BioSPI_Free_PTR								BioSPI_Free;

	BioAPI_Capture_PTR						BioAPI_Capture;				// 20080204 ±Ë√∂±«

 
  //BioAPI_BSP_SCHEMA   m_BSPs[MAX_BSPS];  
  UINT m_NumberOfElements;
  BioAPI_BSP_SCHEMA * m_pBSPs;
  BioAPI_UUID m_bspuuid;
  BioAPI_HANDLE m_hAttachedSession;
  uint32_t		m_dwStreamLength;

protected:
   long MakeFIRFromStream(BYTE* pBinaryStream, DWORD dwStreamLength, BioAPI_BIR* pFullFIR);
   uint32_t GetFirLength(BioAPI_BIR *pFIR);
   long MakeStreamFromFIR(BioAPI_BIR *FIR, BYTE* pBinaryStream);
   int DSS_FP_CheckHeader(BioAPI_BIR* pFullFIR);

public:

  CMyBioApi(){}
  ~CMyBioApi(){}

public:
  int DSS_FP_Init();
  void DSS_FP_Destroy_nBio();
	int Register();
  int DSS_FP_ChangePayload(TCHAR *strPayload,bool flag);
	int DSS_FP_ChangePayloadEx(TCHAR *strPayload,bool flag, char *readername);
  int DSS_FP_CheckCardFinger();
	int DSS_FP_CheckCardFingerEx(char *readername);
	int DSS_FP_GetControlUnitTime(int *npStartTick, int *npCapture_StartTick, int *npCapture_EndTick);
	int DSS_FP_SetEnrollSecurityLevel(unsigned int secuLevel);
	int DSS_FP_SetVerifySecurityLevel(unsigned int secuLevel);
  //int DSS_FP_CheckHeader(NBioAPI_FIR* pFullFIR){}
  //void DSS_FP_Destroy(){}
  

  int DSS_FP_Enroll(TCHAR * strpayload);
	int DSS_FP_EnrollEx(TCHAR * strpayload, char *readername);

  int DSS_FP_EnumDevice(DSS_FP_ENUMDEVICE_INFO **device_list)
  {
    return 0;
  }

 
  int DSS_FP_SetEnumDevice(int device_id)
  {
    return 0;
  }
  
  int DSS_FP_Verify(TCHAR ** strpayload);
	int DSS_FP_VerifyEx(TCHAR ** strpayload,char *readername);

  int DeviceOpen();
  int DeviceClose();


  int DSS_FP_Enroll_Stream(char**,int*);
  int DSS_FP_Enroll_Stream_Write(char* btTmpBuf,int len,char *ppayload);

	int DSS_FP_Enroll_StreamEx(char**,int*,char*);
  int DSS_FP_Enroll_Stream_WriteEx(char* btTmpBuf,int len,char *ppayload,char *readername);

	int DSS_FP_Capture(char**,int*);
	int DSS_FP_CapturedVerify(BYTE*, int);

};
