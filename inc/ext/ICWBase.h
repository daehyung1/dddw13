
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the ICWBASE_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// ICWBASE_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef ICWBASE_EXPORTS
#define ICWBASE_API __declspec(dllexport)
#else
#define ICWBASE_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
	ICWBase Structure
*/

/*
	Version������ ȹ���ϱ� ���� ����ü	
*/
typedef struct tagICWB_OSVER
{
	DWORD dwMajor;
	DWORD dwMinor;
	DWORD dwPlatformID;
	TCHAR szCSDVersion[128];
}ICWB_OSVER;

/*
	ICWBase Function
*/

/*
	OS Version Info
*/

/*
	ICWBASE_API long ICWB_GetOSVer(ICWB_OSVER *pverOSVer)

	parameter:
		pverOSVer: ȹ���� OS Version Ȥ�� 0/NULL.

	return value: 
		ICWB_SUCCESS: OS Version ȹ�� ����.
		ERR_ICWB_GETOSVER_FAIL: GetVersionEx call ����.
*/
ICWBASE_API long ICWB_GetOSVer(ICWB_OSVER *pverOSVer/*out*/);

/*
	ICWBASE_API long ICWB_IsWinXP(BOOL *pbXP)
	
	parameter:
		pbXP: WindowsXP or Windows .NET Server�̸� true �ƴϸ� false.

	return value: 
		ICWB_SUCCESS: OS Version ȹ�� ����.
		ERR_ICWB_GETOSVER_FAIL: GetVersionEx call ����.
*/
ICWBASE_API long ICWB_IsWinXP(BOOL *pbXP/*out*/);

/*
	ICWBASE_API long ICWB_IsWin2K(BOOL *pb2K)
	
	parameter:
		pb2K: Windows2K�̸� true �ƴϸ� false.

	return value: 
		ICWB_SUCCESS: OS Version ȹ�� ����.
		ERR_ICWB_GETOSVER_FAIL: GetVersionEx call ����.
*/
ICWBASE_API long ICWB_IsWin2K(BOOL *pb2K/*out*/);

/*
	ICWBASE_API long ICWB_IsWinNT(BOOL *pbNT)
	
	parameter:
		pbNT: WindowsNT�̸� true �ƴϸ� false.

	return value: 
		ICWB_SUCCESS: OS Version ȹ�� ����.
		ERR_ICWB_GETOSVER_FAIL: GetVersionEx call ����.
*/
ICWBASE_API long ICWB_IsWinNT(BOOL *pbNT/*out*/);

/*
	ICWBASE_API long ICWB_IsWinME(BOOL *pbME)
	
	parameter:
		pbME: WindowsME�̸� true �ƴϸ� false.

	return value: 
		ICWB_SUCCESS: OS Version ȹ�� ����.
		ERR_ICWB_GETOSVER_FAIL: GetVersionEx call ����.
*/
ICWBASE_API long ICWB_IsWinME(BOOL *pbME/*out*/);

/*
	ICWBASE_API long ICWB_IsWin98(BOOL *pb98)
	
	parameter:
		pb98: Windows98�̸� true �ƴϸ� false.

	return value: 
		ICWB_SUCCESS: OS Version ȹ�� ����.
		ERR_ICWB_GETOSVER_FAIL: GetVersionEx call ����.
*/
ICWBASE_API long ICWB_IsWin98(BOOL *pb98/*out*/);

/*
	ICWBASE_API long ICWB_IsPlatformNT(BOOL *pbNT)
	
	parameter:
		pbNT: Windows NT�迭�̸� true �ƴϸ� false.

	return value: 
		ICWB_SUCCESS: OS Version ȹ�� ����.
		ERR_ICWB_GETOSVER_FAIL: GetVersionEx call ����.
*/
ICWBASE_API long ICWB_IsPlatformNT(BOOL *pbNT/*out*/);

/*
	ICWBASE_API long ICWB_IsPlatform9X(BOOL *pb9X)
	
	parameter:
		pb9X: Windows 9X�迭�̸� true �ƴϸ� false.

	return value: 
		ICWB_SUCCESS: OS Version ȹ�� ����.
		ERR_ICWB_GETOSVER_FAIL: GetVersionEx call ����.
*/
ICWBASE_API long ICWB_IsPlatform9X(BOOL *pb9X/*out*/);

/*
	User Info
*/

/*
	ICWBASE_API long ICWBF_GetUserAccount(LPTSTR lpszAccount, UINT nFlag)
	
	parameter:
		lpszAccount: ���� logon�� user�� system account. 
					flag�� ���� domain name�� ������ �� �ִ�. ���� 2K�� ����.
		nFlag: domain ���� ����. default�� domain name�� �������� �ʴ´�.

	return value: 
		ICWB_SUCCESS: ���� logon�� user�� system account ȹ�� ����.
		ICWB_FAIL: ���� logon�� user�� system account ȹ�� ����.
		ERR_ICWB_GETOSVER_FAIL: GetVersionEx call ����.
		ERR_ICWB_NO_SUPPORT: ���� �Լ����� ������ OS�� ���� �������� ����.
		ERR_ICWB_GETPATH_FAIL: domain ������ �� registry�κ��� dll�� pathȹ�� ����.
		ERR_ICWB_LOADLIB_FAIL: domain ������ �� dll load����.
		ERR_ICWB_GETPROCADDR_FAIL: domain ������ �� function load����.
*/
#define ICWBF_NO_DOMAIN	0x00000000
#define ICWBF_DOMAIN	0x00000001
ICWBASE_API long ICWB_GetUserAccount(LPTSTR lpszAccount/*out*/, UINT nFlag/*in*/);

/*
	ICWBASE_API long ICWBF_IsAdminAuth(BOOL *pbAuth)
	
	parameter:
		pbAuth: Admin ������ ������ true �ƴϸ� false.

	return value: 
		ICWB_SUCCESS: ���� üũ ����.
		ICWB_FAIL: ���� üũ ����.
		ERR_ICWB_GETOSVER_FAIL: GetVersionEx call ����.
		ERR_ICWB_GETPATH_FAIL: registry�κ��� 2K Ȥ�� NT dll�� pathȹ�� ����.
		ERR_ICWB_LOADLIB_FAIL: 2K Ȥ�� NT dll load����.
		ERR_ICWB_GETPROCADDR_FAIL: 2K Ȥ�� NT function load����.
*/
ICWBASE_API long ICWB_IsAdminAuth(BOOL *pbAuth/*out*/);

/*
	MessageBox
*/

/*
	ICWBASE_API long ICWB_Message(LPTSTR lpszTitle, LPTSTR lpszMessage, UINT nFlag)
	
	parameter:
		lpszTitle: MessageBox�� title. 
		lpszMessage: MessageBox�� text.
		nFlag: MessageBox�� ����. default�� error-ok-systemmodal message�̴�. 

	return value: 
		flag�� ���� messagebox�� return value.
*/
//	button style
#define ICWBF_OK				0x00000000		//	return IDOK
#define ICWBF_YESNO				0x00000001		//	return IDYES or IDNO
#define ICWBF_YESNOCANCEL		0x00000002		//	return IDYES or IDNO or IDCANCEL
#define ICWBF_RETRYCANCEL		0x00000004		//	return IDRETRY or IDCANCEL
#define ICWBF_OKCANCEL			0x00000008		//	return IDOK or IDCANCEL

//	icon style
#define ICWBF_ERROR				0x00000000
#define ICWBF_QUESTION			0x00000010
#define ICWBF_INFORMATION		0x00000020
#define ICWBF_WARNING			0x00000040

ICWBASE_API int ICWB_Message(LPTSTR lpszTitle/*in*/, LPTSTR lpszMessage/*in*/, UINT nFlag/*in*/);

/*
	File System
*/

/*
	ICWBASE_API long ICWB_ConvertExt(LPTSTR lpszFromExt, LPTSTR lpszToExt, LPTSTR lpszPath, 
		UINT nFlag)
	
	parameter:
		lpszFromExt: ��ȯ���� source file�� Ȯ����. ".xxx"�� ����. 
		lpszToExt: �������� target file�� Ȯ����. ".xxx"�� ����. 
		lpszPath: ������ Ȯ���ڰ� �ִ� ��ü���. 
		nFlag: �������� filename���� �̹� file�� ������ ��� �� subdirectory�� ���� ���࿩��.

	return value: 
		ICWB_SUCCESS: Ȯ���� ��ȯ ����.
		ICWB_FAIL: Ȯ���� ��ȯ ����.
		ERR_ICWB_USER_ABORT: Ȯ���� ��ȯ �� ������ �̸��� ������ �� User�� ��� ����.
		ERR_ICWB_INVALID_EXT: invalid extension.
*/

#define ICWBF_RECURSIVE		0x00000000
#define ICWBF_NO_RECURSIVE	0x00000001

#define ICWBF_EXIST_QUIT		0x00000000
#define ICWBF_EXIST_NEW_NAME	0x00000010
#define ICWBF_EXIST_OVERWRITE	0x00000020

ICWBASE_API long ICWB_ConvertExt(LPTSTR lpszFromExt/*in*/, LPTSTR lpszToExt/*in*/, LPTSTR lpszPath/*in*/, UINT nFlag/*in*/);

/*
	ICWBASE_API long ICWB_RemoveFile(LPTSTR lpszFilePath, int nLevel)
	
	parameter:
		lpszFilePath: ������ file�� ��ü���.
		nLevel(0 ~ 3): remove level. 0�̸� ���������� �����ȴ�.

	return value: 
		ICWB_SUCCESS: file ���� ����.
		ICWB_FAIL: file ���� ����.
		ERR_ICWB_INVALID_HANDLE: invalid handle.
		ERR_ICWB_INVALID_PARAMETER: invalid parameter.(remove level)
*/
ICWBASE_API long ICWB_RemoveFile(LPTSTR lpszFilePath/*in*/, int nLevel/*in*/);

/*
	ICWBASE_API long ICWB_RemoveFolder(LPTSTR lpszPath, int nLevel, UINT nFlag, int nCount, 
		LPTSTR *lplpszExts)	
	parameter:
		lpszPath: ������ file�� ��ü���.
		nLevel(0 ~ 3): remove level. 0�̸� ���������� �����ȴ�.
		nFlag: ���� ������ ���, subdirectory�� ���� ����, ���/�Ϻ� Ȯ���� ���� ����.
		nCount: �Ϻ� Ȯ���ڸ� ������ ��� Ȯ���� ����.
		lplpszExts. �Ϻ� Ȯ���ڸ� ������ ��� Ȯ���� list.

	return value: 
		ICWB_SUCCESS: file ���� ����.
		ICWB_FAIL: file ���� ����.
		ERR_ICWB_INVALID_HANDLE: invalid handle.
		ERR_ICWB_INVALID_PARAMETER: invalid parameter.(remove level)
		ERR_ICWB_FAIL_QUIT: file ���� ���н� �ߴ�.
*/

//	#define ICWBF_RECURSIVE		0x00000000
//	#define ICWBF_NO_RECURSIVE	0x00000001

#define ICWBF_FAIL_SKIP		0x00000000
#define ICWBF_FAIL_QUIT		0x00000010

#define ICWBF_EXT_ALL		0x00000000
#define ICWBF_EXT_SOME		0x00000100
ICWBASE_API long ICWB_RemoveFolder(LPTSTR lpszPath/*in*/, int nLevel/*in*/, UINT nFlag/*in*/, int nCount/*in*/, LPTSTR *lplpszExts/*in*/);

/*
	ICWBASE_API long ICWB_SelectFolder(LPTSTR lpszTitle, LPTSTR lpszPath)
	
	parameter:
		lpszTitle: ������ �����ϴ� ���̾�α��� title.
		lpszPath: ���õ� ������ ��ü���.

	return value: 
		ICWB_SUCCESS: ���� ���� ����.
		ICWB_FAIL: ��� ��ư ������ ������ ���� ���� ����.
*/
ICWBASE_API long ICWB_SelectFolder(LPTSTR lpszTitle/*in*/, LPTSTR lpszPath/*out*/);

/*
	Registry
*/
#define ICWB_REG_SET_ON		"On"
#define ICWB_REG_SET_OFF	"Off"

/*
	ICWBASE_API long ICWB_SelfRegister(LPTSTR lpszFullPath, UINT nFlag)
	ICWBASE_API long ICWB_SelfUnRegister(LPTSTR lpszFullPath, UINT nFlag)
	
	parameter:
		lpszFullPath: ȣ���� dll�� ��ü ���.
		nFlag: shell�� notify�� �������� ����.

	return value: 
		ERR_ICWB_LOADLIB_FAIL: lpszFullPath dll load����.
		ERR_ICWB_GETPROCADDR_FAIL: lpszFullPath function load����.
		others: DllRegisterServer/DllUnregisterServer�� return value.
*/
#define ICWBF_NOTIFY_OFF	0x00000000
#define ICWBF_NOTIFY_ON		0x00000001
ICWBASE_API long ICWB_SelfRegister(LPTSTR lpszFullPath/*in*/, UINT nFlag/*in*/);
ICWBASE_API long ICWB_SelfUnRegister(LPTSTR lpszFullPath/*in*/, UINT nFlag/*in*/);

/*
	ICWBASE_API long ICWB_CreateRegKeyOther(HKEY hKey, LPTSTR lpszKey, UINT nFlag, PHKEY phKey)
	
	parameter:
		hKey: ������ registry�� root key.
		lpszKey: key name.
		nFlag: ������ �� handle��뿩��.
		phKey: ������ registry handle.

	return value: 
		ICWB_SUCCESS: key ���� ����.
		ICWB_FAIL: key ���� ����.
*/
#define ICWBF_USE_HKEY		0x00000000
#define ICWBF_NO_USE_HKEY	0x00000001
ICWBASE_API long ICWB_CreateRegKeyOther(HKEY hKey/*in*/, LPTSTR lpszKey/*in*/, UINT nFlag/*in*/, PHKEY phKey/*out*/);

/*
	ICWBASE_API long ICWB_RemoveRegKeyOther(HKEY hKey, LPTSTR lpszKey, UINT nFlag)
	
	parameter:
		hKey: ������ registry�� root key.
		lpszKey: key name.
		nFlag: subkey ���� ����.

	return value: 
		ICWB_SUCCESS: key ���� ����.
		ICWB_FAIL: key ���� ����.
		ERR_ICWB_GETOSVER_FAIL: GetVersionEx call ����.
		ERR_ICWB_NO_KEY: ������ key�� ����.
		ERR_ICWB_ACCESS_DENIED: registry access�� access denied error.
		ERR_ICWB_NO_SUPPORT: ���� �Լ����� ������ OS�� ���� �������� ����.
*/

//	#define ICWBF_RECURSIVE		0x00000000
//	#define ICWBF_NO_RECURSIVE	0x00000001
ICWBASE_API long ICWB_RemoveRegKeyOther(HKEY hKey/*in*/, LPTSTR lpszKey/*in*/, UINT nFlag/*in*/);

/*
	ICWBASE_API long ICWB_RemoveRegDataOther(HKEY hKey, LPTSTR lpszKey, LPTSTR lpszName)
	
	parameter:
		hKey: ������ registry data name�� root key.
		lpszKey: key name.
		lpszName: data name.

	return value: 
		ICWB_SUCCESS: data ���� ����.
		ICWB_FAIL: data ���� ����.
		ERR_ICWB_NO_KEY: ������ data�� key�� ����.
		ERR_ICWB_ACCESS_DENIED: registry access�� access denied error.
		ERR_ICWB_NO_VALUE: ������ Data�� ����.
*/
ICWBASE_API long ICWB_RemoveRegDataOther(HKEY hKey/*in*/, LPTSTR lpszKey/*in*/, LPTSTR lpszName/*in*/);

/*
	ICWBASE_API long ICWB_ReadRegDataOther(HKEY hKey, LPTSTR lpszKey, LPTSTR lpszName, 
		LPBYTE lpbyValue, LPDWORD lpdwLen)	
	parameter:
		hKey: ���� registry data�� root key.
		lpszKey: key name.
		lpszName: data name.
		lpbyValue: data value.
		lpdwLen: lpbyValue�� length.

	return value: 
		ICWB_SUCCESS: data �б� ����.
		ICWB_FAIL: data �б� ����.
		ERR_ICWB_NO_KEY: ���� data�� key�� ����.
		ERR_ICWB_ACCESS_DENIED: registry access�� access denied error.
		ERR_ICWB_NO_VALUE: ���� Data�� ����.
*/
ICWBASE_API long ICWB_ReadRegDataOther(HKEY hKey/*in*/, LPTSTR lpszKey/*in*/, LPTSTR lpszName/*in*/, LPBYTE lpbyValue/*out*/, LPDWORD lpdwLen/*inout*/);

/*
	ICWBASE_API long ICWB_WriteRegDataOther(HKEY hKey, LPTSTR lpszKey, LPTSTR lpszName, 
		LPBYTE lpbyValue, DWORD dwType, DWORD dwLen);
	parameter:
		hKey: ����� registry data�� root key.
		lpszKey: key name.
		lpszName: data name.
		lpbyValue: data value.
		dwType: data type.
		lpdwLen: lpbyValue�� length.

	return value: 
		ICWB_SUCCESS: data �б� ����.
		ICWB_FAIL: data �б� ����.
		ERR_ICWB_NO_KEY: ���� data�� key�� ����.
		ERR_ICWB_ACCESS_DENIED: registry access�� access denied error.
*/
ICWBASE_API long ICWB_WriteRegDataOther(HKEY hKey/*in*/, LPTSTR lpszKey/*in*/, LPTSTR lpszName/*in*/, LPBYTE lpbyValue/*in*/, DWORD dwType/*in*/, DWORD dwLen/*in*/);

/*
	ICWBASE_API long ICWB_RemoveRegKey(LPTSTR lpszKey, UINT nFlag)
	
	parameter:
		lpszKey: key name.
		nFlag: subkey ���� ���� �� root key ����.

	return value: 
		ICWB_SUCCESS: key ���� ����.
		ICWB_FAIL: key ���� ����.
		ERR_ICWB_GETOSVER_FAIL: GetVersionEx call ����.
		ERR_ICWB_NO_KEY: ������ key�� ����.
		ERR_ICWB_ACCESS_DENIED: registry access�� access denied error.
		ERR_ICWB_NO_SUPPORT: ���� �Լ����� ������ OS�� ���� �������� ����.
		ERR_ICWB_NO_HKEY: root key�� ���ǵ��� ����.
*/

//	#define ICWBF_RECURSIVE		0x00000000
//	#define ICWBF_NO_RECURSIVE	0x00000001

//	�ݵ�� �����Ǿ�� �Ѵ�.
#define ICWBF_USER			0x00000010
#define ICWBF_SYSTEM		0x00000020
#define ICWBF_ALL			0x00000030
ICWBASE_API long ICWB_RemoveRegKey(LPTSTR lpszKey/*in*/, UINT nFlag/*in*/);

/*
	ICWBASE_API long ICWB_RemoveRegData(LPTSTR lpszKey, LPTSTR lpszName, UINT nFlag)
	
	parameter:
		lpszKey: key name.
		lpszName: data name.
		nFlag: root key ����.

	return value: 
		ICWB_SUCCESS: data ���� ����.
		ICWB_FAIL: data ���� ����.
		ERR_ICWB_NO_KEY: ������ data�� key�� ����.
		ERR_ICWB_ACCESS_DENIED: registry access�� access denied error.
		ERR_ICWB_NO_VALUE: ������ Data�� ����.
		ERR_ICWB_NO_HKEY: root key�� ���ǵ��� ����.
*/

//	�ݵ�� �����Ǿ�� �Ѵ�.
#define ICWBF_USER			0x00000010
#define ICWBF_SYSTEM		0x00000020
#define ICWBF_ALL			0x00000030
ICWBASE_API long ICWB_RemoveRegData(LPTSTR lpszKey/*in*/, LPTSTR lpszName/*in*/, UINT nFlag/*in*/);

/*
	ICWBASE_API long ICWB_ReadRegData(LPTSTR lpszSubKey, LPTSTR lpszName, LPBYTE lpbyValue, 
		LPDWORD lpdwLen, UINT nFlag, UINT *lpnStatusRAC)
	
	parameter:
		lpszSubKey: key name.
		lpszName: data name.
		lpbyValue: data value.
		lpdwLen: lpbyValue�� length.
		nFlag: root key ����, query�� data, data�� copy����, data�� status.

	return value: 
		ICWB_SUCCESS: data query ����.
		ICWB_FAIL: data query ����.
		ERR_ICWB_NO_QUERY: query�� data�� status���� value���� �������� ����.
		ERR_ICWB_NO_KEY: query�� data�� key�� ����.
		ERR_ICWB_ACCESS_DENIED: registry access�� access denied error.
		ERR_ICWB_NO_VALUE: ������ Data�� ����.
		ERR_ICWB_COPY_FAIL: Registry data�� LOCAL_MACHINE�κ��� CURRENT_USER�� copy����.
*/
#define ICWBF_RW_AUTO		0x00000000
#define ICWBF_RW_USER		0x00000001
#define ICWBF_RW_SYSTEM		0x00000002

//	�ݵ�� �����Ǿ�� �Ѵ�.
#define ICWBF_READ_VALUE	0x00000010
#define ICWBF_READ_RAC		0x00000020
#define ICWBF_READ_ALL		0x00000030

//	ISSAC_BASE_REG_RW_AUTO�� ���ǵ� ���...
#define ICWBF_READ_NO_COPY	0x00000000
#define ICWBF_READ_COPY		0x00000100

//	nStatusAC�� output����
#define ICWBS_RAC_USE		0x00000001
#define ICWBS_RAC_NO_USE	0x00000002
#define ICWBS_RAC_USE_ERR	0x00000004
#define ICWBS_RAC_ON		0x00000010
#define ICWBS_RAC_OFF		0x00000020
#define ICWBS_RAC_ERR		0x00000040
ICWBASE_API long ICWB_ReadRegData(LPTSTR lpszSubKey/*in*/, LPTSTR lpszName/*in*/, LPBYTE lpbyValue/*out*/, LPDWORD lpdwLen/*inout*/, UINT nFlag/*in*/, UINT *lpnStatusRAC/*out*/);

/*
	ICWBASE_API long ICWB_WriteRegData(LPTSTR lpszSubKey, LPTSTR lpszName, LPBYTE lpbyValue, 
		DWORD dwType, DWORD dwLen, UINT nFlag)
	
	parameter:
		lpszSubKey: key name.
		lpszName: data name.
		lpbyValue: data value.
		dwType: lpszName�� data type.
		dwLen: lpbyValue�� length.
		nFlag: root key ����, key create ����, RAC check ����, RAC set ����, RAC value.

	return value: 
		ICWB_SUCCESS: data set ����.
		ICWB_FAIL: data set ����.
		ERR_ICWB_READ_RAC_FAIL: RAC�� �дµ� ����.	
		ERR_ICWB_RAC_OFF: RAC�� Off�� �����Ǿ� �ִ�.
		ERR_ICWB_NO_KEY: set�� data�� key�� ����.
		ERR_ICWB_ACCESS_DENIED: registry access�� access denied error.
		ERR_ICWB_CREATE_KEY_FAIL: Registry key create fail.
		ERR_ICWB_REMOVE_RAC_FAIL: RAC ���� ����.
		ERR_ICWB_CREATE_RAC_FAIL: RAC ���� ����.
*/
#define ICWBF_RW_AUTO		0x00000000
#define ICWBF_RW_USER		0x00000001
#define ICWBF_RW_SYSTEM		0x00000002

//	ISSAC_BASE_REG_RW_USER/ISSAC_BASE_REG_RW_SYSTEM�� ���ǵ� ���...
#define ICWBF_WRITE_CREATE		0x00000000
#define ICWBF_WRITE_NO_CREATE	0x00000010

#define ICWBF_WRITE_RAC_CHECK	0x00000000
#define ICWBF_WRITE_RAC_IGNORE	0x00000100

//	IBF_REG_WRITE_IGNORE_RAC�� ���ǵ� ���...
#define ICWBF_WRITE_RAC_NO_SET	0x00000000
#define ICWBF_WRITE_RAC_SET		0x00001000
#define ICWBF_WRITE_RAC_REMOVE	0x00002000

//	IBF_REG_WRITE_SET_RAC�� ���...
#define ICWBF_WRITE_RAC_ON	0x00000000
#define ICWBF_WRITE_RAC_OFF	0x00010000

ICWBASE_API long ICWB_WriteRegData(LPTSTR lpszSubKey/*in*/, LPTSTR lpszName/*in*/, LPBYTE lpbyValue/*in*/, DWORD dwType/*in*/, DWORD dwLen/*in*/, UINT nFlag/*in*/);

/*
	File Info.
*/

/*
	ICWBASE_API long ICWB_GetFileDesc(LPTSTR lpszPath, LPTSTR lpszName, LPTSTR lpszData, UINT *lpnData);
	parameter:
		lpszPath: file�� ��ü ���.
		lpszName: ����� �ϴ� �ΰ� ����.
		lpszData: lpszName�� value buffer.
		lpnData: lpszData�� length

	return value: 
		ICWB_SUCCESS: file desc ȹ�� ����.
		ICWB_FAIL: file desc ȹ�� ����.
*/

ICWBASE_API long ICWB_GetFileDesc(LPTSTR lpszPath/*in*/, LPTSTR lpszName/*in*/, LPTSTR lpszData/*out*/, UINT *lpnData/*inout*/);

/*
	ICWBASE_API long ICWB_GetFileVer(LPTSTR lpszPath, LPTSTR lpszVer, UINT *lpnVer);
	parameter:
		lpszPath: file�� ��ü ���.
		lpszVer: file version buffer.
		lpnVer: lpszVer�� length.

	return value: 
		ICWB_SUCCESS: file version ȹ�� ����.
		ICWB_FAIL: file version ȹ�� ����.
*/

ICWBASE_API long ICWB_GetFileVer(LPTSTR lpszPath/*in*/, LPTSTR lpszVer/*out*/, UINT *lpnVer/*inout*/);

#ifdef __cplusplus
}
#endif
