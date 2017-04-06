  
#pragma once
  
#define _NBioAPI_LOAD_LIBRARY
#include "NBioAPI.h"
#include "DSS.h"
  
  
class CNBioApi: public CBioApiObject
{
  
  
private:
  
  HINSTANCE      m_hLib;
  NBioAPI_HANDLE m_hNBioBSP;
  NBioAPI_FIR_HANDLE      m_hFIR;
  //NBioAPI_FIR							m_FullFIR;
  NBioAPI_FIR_FORMAT			m_nFIRFormat;
  //NBioAPI_FIR_TEXTENCODE  m_TextFIR;
  
  NBioAPI_WINDOW_OPTION   m_WinOption;
  
  BYTE*                   m_BinaryStream;
  DWORD										m_dwStreamLength;
  char*                   m_TextStream;
 // int DSS_FP_CheckHeader(NBioAPI_FIR* pFullFIR);
  //NBioAPI_WINDOW_OPTION_2 m_WinOption2;
  
  
	// Init/Terminate Function   
	FP_NBioAPI_Init                  NBioAPI_Init;
	FP_NBioAPI_Terminate             NBioAPI_Terminate;
	
	// Basic Functions
	FP_NBioAPI_GetVersion            NBioAPI_GetVersion;
	FP_NBioAPI_GetInitInfo           NBioAPI_GetInitInfo;
	FP_NBioAPI_SetInitInfo           NBioAPI_SetInitInfo;
	
	// Device Functions
	FP_NBioAPI_EnumerateDevice       NBioAPI_EnumerateDevice;
	FP_NBioAPI_EnumerateDeviceEx     NBioAPI_EnumerateDeviceEx;
	FP_NBioAPI_OpenDevice            NBioAPI_OpenDevice;
	FP_NBioAPI_CloseDevice           NBioAPI_CloseDevice;
	FP_NBioAPI_GetDeviceInfo         NBioAPI_GetDeviceInfo;
	FP_NBioAPI_SetDeviceInfo         NBioAPI_SetDeviceInfo;
	FP_NBioAPI_AdjustDevice          NBioAPI_AdjustDevice;
	
	//Memory Functions
	FP_NBioAPI_FreeFIRHandle         NBioAPI_FreeFIRHandle;
	FP_NBioAPI_GetFIRFromHandle      NBioAPI_GetFIRFromHandle;
	FP_NBioAPI_GetHeaderFromHandle   NBioAPI_GetHeaderFromHandle;
	FP_NBioAPI_FreeFIR               NBioAPI_FreeFIR;
	FP_NBioAPI_FreePayload           NBioAPI_FreePayload;
	
	// TextEncode Funtions
	FP_NBioAPI_GetTextFIRFromHandle  NBioAPI_GetTextFIRFromHandle;
	FP_NBioAPI_FreeTextFIR           NBioAPI_FreeTextFIR;
  
	// Extened Functions
	FP_NBioAPI_GetExtendedFIRFromHandle       NBioAPI_GetExtendedFIRFromHandle;
	FP_NBioAPI_GetExtendedHeaderFromHandle    NBioAPI_GetExtendedHeaderFromHandle;
	FP_NBioAPI_GetExtendedTextFIRFromHandle   NBioAPI_GetExtendedTextFIRFromHandle;
	
	// BSP Functions
	FP_NBioAPI_Capture               NBioAPI_Capture;
	FP_NBioAPI_Process               NBioAPI_Process;
	FP_NBioAPI_CreateTemplate        NBioAPI_CreateTemplate;
	FP_NBioAPI_VerifyMatch           NBioAPI_VerifyMatch;
	FP_NBioAPI_Enroll                NBioAPI_Enroll;
	FP_NBioAPI_Verify                NBioAPI_Verify;
	
	// Skin Function
	FP_NBioAPI_SetSkinResource       NBioAPI_SetSkinResource;
  
protected:
  long MakeStreamFromFIR(NBioAPI_FIR FIR, BYTE* pBinaryStream);
  long MakeFIRFromStream(BYTE* pBinaryStream, DWORD dwStreamLength, NBioAPI_FIR* pFullFIR);
  
public:
  
  CNBioApi();
  
  ~CNBioApi()
  {
    DSS_FP_Destroy();
  }
  
  int DSS_FP_ChangePayload(TCHAR *strPayload,bool flag);
	int DSS_FP_ChangePayloadEx(TCHAR *strPayload,bool flag,char *readername);
  int DSS_FP_CheckCardFinger();
	int DSS_FP_CheckCardFingerEx(char *readername);
  int DSS_FP_CheckHeader(NBioAPI_FIR* pFullFIR);
	int DSS_FP_GetControlUnitTime(int *npStartTick, int *npCapture_StartTick, int *npCapture_EndTick){ return 0; };
	int DSS_FP_SetEnrollSecurityLevel(unsigned int secuLevel) { return 0; };
	int DSS_FP_SetVerifySecurityLevel(unsigned int secuLevel) { return 0; };
  //void DSS_FP_Destroy();
  void DSS_FP_Destroy_nBio();
  int DSS_FP_Enroll(TCHAR * strpayload);
	int DSS_FP_EnrollEx(TCHAR * strpayload, char *readername);
  int DSS_FP_EnumDevice(DSS_FP_ENUMDEVICE_INFO **device_list);
 // void DSS_FP_Initialize(HWND hwnd,int flag);
  int DSS_FP_Init();
  int DeviceOpen();
  int DeviceClose();
  int DSS_FP_SetEnumDevice(int device_id);
  int DSS_FP_Verify(TCHAR ** strpayload);
	int DSS_FP_VerifyEx(TCHAR ** strpayload, char *readername);
  long GetFirLength(NBioAPI_FIR pFIR);
  
  int DSS_FP_Enroll_Stream(char**,int*);
  int DSS_FP_Enroll_Stream_Write(char* btTmpBuf,int len,char *ppayload);
	int DSS_FP_Enroll_StreamEx(char**,int*,char*);
  int DSS_FP_Enroll_Stream_WriteEx(char* btTmpBuf,int len,char *ppayload,char *readername);

	int DSS_FP_Capture(char**,int*);
	int DSS_FP_CapturedVerify(BYTE*, int);
  
};
