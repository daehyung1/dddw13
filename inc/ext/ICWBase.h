
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
	Version정보를 획득하기 위한 구조체	
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
		pverOSVer: 획득한 OS Version 혹은 0/NULL.

	return value: 
		ICWB_SUCCESS: OS Version 획득 성공.
		ERR_ICWB_GETOSVER_FAIL: GetVersionEx call 실패.
*/
ICWBASE_API long ICWB_GetOSVer(ICWB_OSVER *pverOSVer/*out*/);

/*
	ICWBASE_API long ICWB_IsWinXP(BOOL *pbXP)
	
	parameter:
		pbXP: WindowsXP or Windows .NET Server이면 true 아니면 false.

	return value: 
		ICWB_SUCCESS: OS Version 획득 성공.
		ERR_ICWB_GETOSVER_FAIL: GetVersionEx call 실패.
*/
ICWBASE_API long ICWB_IsWinXP(BOOL *pbXP/*out*/);

/*
	ICWBASE_API long ICWB_IsWin2K(BOOL *pb2K)
	
	parameter:
		pb2K: Windows2K이면 true 아니면 false.

	return value: 
		ICWB_SUCCESS: OS Version 획득 성공.
		ERR_ICWB_GETOSVER_FAIL: GetVersionEx call 실패.
*/
ICWBASE_API long ICWB_IsWin2K(BOOL *pb2K/*out*/);

/*
	ICWBASE_API long ICWB_IsWinNT(BOOL *pbNT)
	
	parameter:
		pbNT: WindowsNT이면 true 아니면 false.

	return value: 
		ICWB_SUCCESS: OS Version 획득 성공.
		ERR_ICWB_GETOSVER_FAIL: GetVersionEx call 실패.
*/
ICWBASE_API long ICWB_IsWinNT(BOOL *pbNT/*out*/);

/*
	ICWBASE_API long ICWB_IsWinME(BOOL *pbME)
	
	parameter:
		pbME: WindowsME이면 true 아니면 false.

	return value: 
		ICWB_SUCCESS: OS Version 획득 성공.
		ERR_ICWB_GETOSVER_FAIL: GetVersionEx call 실패.
*/
ICWBASE_API long ICWB_IsWinME(BOOL *pbME/*out*/);

/*
	ICWBASE_API long ICWB_IsWin98(BOOL *pb98)
	
	parameter:
		pb98: Windows98이면 true 아니면 false.

	return value: 
		ICWB_SUCCESS: OS Version 획득 성공.
		ERR_ICWB_GETOSVER_FAIL: GetVersionEx call 실패.
*/
ICWBASE_API long ICWB_IsWin98(BOOL *pb98/*out*/);

/*
	ICWBASE_API long ICWB_IsPlatformNT(BOOL *pbNT)
	
	parameter:
		pbNT: Windows NT계열이면 true 아니면 false.

	return value: 
		ICWB_SUCCESS: OS Version 획득 성공.
		ERR_ICWB_GETOSVER_FAIL: GetVersionEx call 실패.
*/
ICWBASE_API long ICWB_IsPlatformNT(BOOL *pbNT/*out*/);

/*
	ICWBASE_API long ICWB_IsPlatform9X(BOOL *pb9X)
	
	parameter:
		pb9X: Windows 9X계열이면 true 아니면 false.

	return value: 
		ICWB_SUCCESS: OS Version 획득 성공.
		ERR_ICWB_GETOSVER_FAIL: GetVersionEx call 실패.
*/
ICWBASE_API long ICWB_IsPlatform9X(BOOL *pb9X/*out*/);

/*
	User Info
*/

/*
	ICWBASE_API long ICWBF_GetUserAccount(LPTSTR lpszAccount, UINT nFlag)
	
	parameter:
		lpszAccount: 현재 logon한 user의 system account. 
					flag에 따라 domain name을 포함할 수 있다. 현재 2K만 지원.
		nFlag: domain 포함 여부. default는 domain name을 포함하지 않는다.

	return value: 
		ICWB_SUCCESS: 현재 logon한 user의 system account 획득 성공.
		ICWB_FAIL: 현재 logon한 user의 system account 획득 실패.
		ERR_ICWB_GETOSVER_FAIL: GetVersionEx call 실패.
		ERR_ICWB_NO_SUPPORT: 위의 함수에서 현재의 OS에 대해 지원하지 않음.
		ERR_ICWB_GETPATH_FAIL: domain 포함할 때 registry로부터 dll의 path획득 실패.
		ERR_ICWB_LOADLIB_FAIL: domain 포함할 때 dll load실패.
		ERR_ICWB_GETPROCADDR_FAIL: domain 포함할 때 function load실패.
*/
#define ICWBF_NO_DOMAIN	0x00000000
#define ICWBF_DOMAIN	0x00000001
ICWBASE_API long ICWB_GetUserAccount(LPTSTR lpszAccount/*out*/, UINT nFlag/*in*/);

/*
	ICWBASE_API long ICWBF_IsAdminAuth(BOOL *pbAuth)
	
	parameter:
		pbAuth: Admin 권한을 가지면 true 아니면 false.

	return value: 
		ICWB_SUCCESS: 권한 체크 성공.
		ICWB_FAIL: 권한 체크 실패.
		ERR_ICWB_GETOSVER_FAIL: GetVersionEx call 실패.
		ERR_ICWB_GETPATH_FAIL: registry로부터 2K 혹은 NT dll의 path획득 실패.
		ERR_ICWB_LOADLIB_FAIL: 2K 혹은 NT dll load실패.
		ERR_ICWB_GETPROCADDR_FAIL: 2K 혹은 NT function load실패.
*/
ICWBASE_API long ICWB_IsAdminAuth(BOOL *pbAuth/*out*/);

/*
	MessageBox
*/

/*
	ICWBASE_API long ICWB_Message(LPTSTR lpszTitle, LPTSTR lpszMessage, UINT nFlag)
	
	parameter:
		lpszTitle: MessageBox의 title. 
		lpszMessage: MessageBox의 text.
		nFlag: MessageBox의 종류. default는 error-ok-systemmodal message이다. 

	return value: 
		flag에 따른 messagebox의 return value.
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
		lpszFromExt: 변환전의 source file의 확장자. ".xxx"의 형태. 
		lpszToExt: 변경후의 target file의 확장자. ".xxx"의 형태. 
		lpszPath: 변경할 확장자가 있는 전체경로. 
		nFlag: 변경후의 filename으로 이미 file이 존재할 경우 및 subdirectory에 대한 실행여부.

	return value: 
		ICWB_SUCCESS: 확장자 변환 성공.
		ICWB_FAIL: 확장자 변환 실패.
		ERR_ICWB_USER_ABORT: 확장자 변환 중 동일한 이름이 존재할 때 User가 취소 선택.
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
		lpszFilePath: 삭제할 file의 전체경로.
		nLevel(0 ~ 3): remove level. 0이면 휴지통으로 삭제된다.

	return value: 
		ICWB_SUCCESS: file 삭제 성공.
		ICWB_FAIL: file 삭제 실패.
		ERR_ICWB_INVALID_HANDLE: invalid handle.
		ERR_ICWB_INVALID_PARAMETER: invalid parameter.(remove level)
*/
ICWBASE_API long ICWB_RemoveFile(LPTSTR lpszFilePath/*in*/, int nLevel/*in*/);

/*
	ICWBASE_API long ICWB_RemoveFolder(LPTSTR lpszPath, int nLevel, UINT nFlag, int nCount, 
		LPTSTR *lplpszExts)	
	parameter:
		lpszPath: 삭제할 file의 전체경로.
		nLevel(0 ~ 3): remove level. 0이면 휴지통으로 삭제된다.
		nFlag: 삭제 실패할 경우, subdirectory에 대한 실행, 모두/일부 확장자 삭제 여부.
		nCount: 일부 확장자만 삭제할 경우 확장자 갯수.
		lplpszExts. 일부 확장자만 삭제할 경우 확장자 list.

	return value: 
		ICWB_SUCCESS: file 삭제 성공.
		ICWB_FAIL: file 삭제 실패.
		ERR_ICWB_INVALID_HANDLE: invalid handle.
		ERR_ICWB_INVALID_PARAMETER: invalid parameter.(remove level)
		ERR_ICWB_FAIL_QUIT: file 삭제 실패시 중단.
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
		lpszTitle: 폴더를 선택하는 다이얼로그의 title.
		lpszPath: 선택된 폴더의 전체경로.

	return value: 
		ICWB_SUCCESS: 폴더 선택 성공.
		ICWB_FAIL: 취소 버튼 선택을 포함한 폴더 선택 실패.
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
		lpszFullPath: 호출할 dll의 전체 경로.
		nFlag: shell에 notify할 것인지의 여부.

	return value: 
		ERR_ICWB_LOADLIB_FAIL: lpszFullPath dll load실패.
		ERR_ICWB_GETPROCADDR_FAIL: lpszFullPath function load실패.
		others: DllRegisterServer/DllUnregisterServer의 return value.
*/
#define ICWBF_NOTIFY_OFF	0x00000000
#define ICWBF_NOTIFY_ON		0x00000001
ICWBASE_API long ICWB_SelfRegister(LPTSTR lpszFullPath/*in*/, UINT nFlag/*in*/);
ICWBASE_API long ICWB_SelfUnRegister(LPTSTR lpszFullPath/*in*/, UINT nFlag/*in*/);

/*
	ICWBASE_API long ICWB_CreateRegKeyOther(HKEY hKey, LPTSTR lpszKey, UINT nFlag, PHKEY phKey)
	
	parameter:
		hKey: 생성할 registry의 root key.
		lpszKey: key name.
		nFlag: 생성한 후 handle사용여부.
		phKey: 생성한 registry handle.

	return value: 
		ICWB_SUCCESS: key 생성 성공.
		ICWB_FAIL: key 생성 실패.
*/
#define ICWBF_USE_HKEY		0x00000000
#define ICWBF_NO_USE_HKEY	0x00000001
ICWBASE_API long ICWB_CreateRegKeyOther(HKEY hKey/*in*/, LPTSTR lpszKey/*in*/, UINT nFlag/*in*/, PHKEY phKey/*out*/);

/*
	ICWBASE_API long ICWB_RemoveRegKeyOther(HKEY hKey, LPTSTR lpszKey, UINT nFlag)
	
	parameter:
		hKey: 삭제할 registry의 root key.
		lpszKey: key name.
		nFlag: subkey 삭제 여부.

	return value: 
		ICWB_SUCCESS: key 삭제 성공.
		ICWB_FAIL: key 삭제 실패.
		ERR_ICWB_GETOSVER_FAIL: GetVersionEx call 실패.
		ERR_ICWB_NO_KEY: 삭제할 key가 없음.
		ERR_ICWB_ACCESS_DENIED: registry access시 access denied error.
		ERR_ICWB_NO_SUPPORT: 위의 함수에서 현재의 OS에 대해 지원하지 않음.
*/

//	#define ICWBF_RECURSIVE		0x00000000
//	#define ICWBF_NO_RECURSIVE	0x00000001
ICWBASE_API long ICWB_RemoveRegKeyOther(HKEY hKey/*in*/, LPTSTR lpszKey/*in*/, UINT nFlag/*in*/);

/*
	ICWBASE_API long ICWB_RemoveRegDataOther(HKEY hKey, LPTSTR lpszKey, LPTSTR lpszName)
	
	parameter:
		hKey: 삭제할 registry data name의 root key.
		lpszKey: key name.
		lpszName: data name.

	return value: 
		ICWB_SUCCESS: data 삭제 성공.
		ICWB_FAIL: data 삭제 실패.
		ERR_ICWB_NO_KEY: 삭제할 data의 key가 없음.
		ERR_ICWB_ACCESS_DENIED: registry access시 access denied error.
		ERR_ICWB_NO_VALUE: 삭제할 Data가 없음.
*/
ICWBASE_API long ICWB_RemoveRegDataOther(HKEY hKey/*in*/, LPTSTR lpszKey/*in*/, LPTSTR lpszName/*in*/);

/*
	ICWBASE_API long ICWB_ReadRegDataOther(HKEY hKey, LPTSTR lpszKey, LPTSTR lpszName, 
		LPBYTE lpbyValue, LPDWORD lpdwLen)	
	parameter:
		hKey: 읽을 registry data의 root key.
		lpszKey: key name.
		lpszName: data name.
		lpbyValue: data value.
		lpdwLen: lpbyValue의 length.

	return value: 
		ICWB_SUCCESS: data 읽기 성공.
		ICWB_FAIL: data 읽기 실패.
		ERR_ICWB_NO_KEY: 읽을 data의 key가 없음.
		ERR_ICWB_ACCESS_DENIED: registry access시 access denied error.
		ERR_ICWB_NO_VALUE: 읽을 Data가 없음.
*/
ICWBASE_API long ICWB_ReadRegDataOther(HKEY hKey/*in*/, LPTSTR lpszKey/*in*/, LPTSTR lpszName/*in*/, LPBYTE lpbyValue/*out*/, LPDWORD lpdwLen/*inout*/);

/*
	ICWBASE_API long ICWB_WriteRegDataOther(HKEY hKey, LPTSTR lpszKey, LPTSTR lpszName, 
		LPBYTE lpbyValue, DWORD dwType, DWORD dwLen);
	parameter:
		hKey: 기록할 registry data의 root key.
		lpszKey: key name.
		lpszName: data name.
		lpbyValue: data value.
		dwType: data type.
		lpdwLen: lpbyValue의 length.

	return value: 
		ICWB_SUCCESS: data 읽기 성공.
		ICWB_FAIL: data 읽기 실패.
		ERR_ICWB_NO_KEY: 읽을 data의 key가 없음.
		ERR_ICWB_ACCESS_DENIED: registry access시 access denied error.
*/
ICWBASE_API long ICWB_WriteRegDataOther(HKEY hKey/*in*/, LPTSTR lpszKey/*in*/, LPTSTR lpszName/*in*/, LPBYTE lpbyValue/*in*/, DWORD dwType/*in*/, DWORD dwLen/*in*/);

/*
	ICWBASE_API long ICWB_RemoveRegKey(LPTSTR lpszKey, UINT nFlag)
	
	parameter:
		lpszKey: key name.
		nFlag: subkey 삭제 여부 및 root key 종류.

	return value: 
		ICWB_SUCCESS: key 삭제 성공.
		ICWB_FAIL: key 삭제 실패.
		ERR_ICWB_GETOSVER_FAIL: GetVersionEx call 실패.
		ERR_ICWB_NO_KEY: 삭제할 key가 없음.
		ERR_ICWB_ACCESS_DENIED: registry access시 access denied error.
		ERR_ICWB_NO_SUPPORT: 위의 함수에서 현재의 OS에 대해 지원하지 않음.
		ERR_ICWB_NO_HKEY: root key가 정의되지 않음.
*/

//	#define ICWBF_RECURSIVE		0x00000000
//	#define ICWBF_NO_RECURSIVE	0x00000001

//	반드시 설정되어야 한다.
#define ICWBF_USER			0x00000010
#define ICWBF_SYSTEM		0x00000020
#define ICWBF_ALL			0x00000030
ICWBASE_API long ICWB_RemoveRegKey(LPTSTR lpszKey/*in*/, UINT nFlag/*in*/);

/*
	ICWBASE_API long ICWB_RemoveRegData(LPTSTR lpszKey, LPTSTR lpszName, UINT nFlag)
	
	parameter:
		lpszKey: key name.
		lpszName: data name.
		nFlag: root key 종류.

	return value: 
		ICWB_SUCCESS: data 삭제 성공.
		ICWB_FAIL: data 삭제 실패.
		ERR_ICWB_NO_KEY: 삭제할 data의 key가 없음.
		ERR_ICWB_ACCESS_DENIED: registry access시 access denied error.
		ERR_ICWB_NO_VALUE: 삭제할 Data가 없음.
		ERR_ICWB_NO_HKEY: root key가 정의되지 않음.
*/

//	반드시 설정되어야 한다.
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
		lpdwLen: lpbyValue의 length.
		nFlag: root key 종류, query할 data, data의 copy여부, data의 status.

	return value: 
		ICWB_SUCCESS: data query 성공.
		ICWB_FAIL: data query 실패.
		ERR_ICWB_NO_QUERY: query할 data가 status인지 value인지 정의하지 않음.
		ERR_ICWB_NO_KEY: query할 data의 key가 없음.
		ERR_ICWB_ACCESS_DENIED: registry access시 access denied error.
		ERR_ICWB_NO_VALUE: 삭제할 Data가 없음.
		ERR_ICWB_COPY_FAIL: Registry data를 LOCAL_MACHINE로부터 CURRENT_USER로 copy실패.
*/
#define ICWBF_RW_AUTO		0x00000000
#define ICWBF_RW_USER		0x00000001
#define ICWBF_RW_SYSTEM		0x00000002

//	반드시 설정되어야 한다.
#define ICWBF_READ_VALUE	0x00000010
#define ICWBF_READ_RAC		0x00000020
#define ICWBF_READ_ALL		0x00000030

//	ISSAC_BASE_REG_RW_AUTO가 정의된 경우...
#define ICWBF_READ_NO_COPY	0x00000000
#define ICWBF_READ_COPY		0x00000100

//	nStatusAC의 output형태
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
		dwType: lpszName의 data type.
		dwLen: lpbyValue의 length.
		nFlag: root key 종류, key create 여부, RAC check 여부, RAC set 여부, RAC value.

	return value: 
		ICWB_SUCCESS: data set 성공.
		ICWB_FAIL: data set 실패.
		ERR_ICWB_READ_RAC_FAIL: RAC를 읽는데 실패.	
		ERR_ICWB_RAC_OFF: RAC가 Off로 설정되어 있다.
		ERR_ICWB_NO_KEY: set할 data의 key가 없음.
		ERR_ICWB_ACCESS_DENIED: registry access시 access denied error.
		ERR_ICWB_CREATE_KEY_FAIL: Registry key create fail.
		ERR_ICWB_REMOVE_RAC_FAIL: RAC 삭제 실패.
		ERR_ICWB_CREATE_RAC_FAIL: RAC 생성 실패.
*/
#define ICWBF_RW_AUTO		0x00000000
#define ICWBF_RW_USER		0x00000001
#define ICWBF_RW_SYSTEM		0x00000002

//	ISSAC_BASE_REG_RW_USER/ISSAC_BASE_REG_RW_SYSTEM가 정의된 경우...
#define ICWBF_WRITE_CREATE		0x00000000
#define ICWBF_WRITE_NO_CREATE	0x00000010

#define ICWBF_WRITE_RAC_CHECK	0x00000000
#define ICWBF_WRITE_RAC_IGNORE	0x00000100

//	IBF_REG_WRITE_IGNORE_RAC가 정의된 경우...
#define ICWBF_WRITE_RAC_NO_SET	0x00000000
#define ICWBF_WRITE_RAC_SET		0x00001000
#define ICWBF_WRITE_RAC_REMOVE	0x00002000

//	IBF_REG_WRITE_SET_RAC인 경우...
#define ICWBF_WRITE_RAC_ON	0x00000000
#define ICWBF_WRITE_RAC_OFF	0x00010000

ICWBASE_API long ICWB_WriteRegData(LPTSTR lpszSubKey/*in*/, LPTSTR lpszName/*in*/, LPBYTE lpbyValue/*in*/, DWORD dwType/*in*/, DWORD dwLen/*in*/, UINT nFlag/*in*/);

/*
	File Info.
*/

/*
	ICWBASE_API long ICWB_GetFileDesc(LPTSTR lpszPath, LPTSTR lpszName, LPTSTR lpszData, UINT *lpnData);
	parameter:
		lpszPath: file의 전체 경로.
		lpszName: 얻고자 하는 부가 정보.
		lpszData: lpszName의 value buffer.
		lpnData: lpszData의 length

	return value: 
		ICWB_SUCCESS: file desc 획득 성공.
		ICWB_FAIL: file desc 획득 실패.
*/

ICWBASE_API long ICWB_GetFileDesc(LPTSTR lpszPath/*in*/, LPTSTR lpszName/*in*/, LPTSTR lpszData/*out*/, UINT *lpnData/*inout*/);

/*
	ICWBASE_API long ICWB_GetFileVer(LPTSTR lpszPath, LPTSTR lpszVer, UINT *lpnVer);
	parameter:
		lpszPath: file의 전체 경로.
		lpszVer: file version buffer.
		lpnVer: lpszVer의 length.

	return value: 
		ICWB_SUCCESS: file version 획득 성공.
		ICWB_FAIL: file version 획득 실패.
*/

ICWBASE_API long ICWB_GetFileVer(LPTSTR lpszPath/*in*/, LPTSTR lpszVer/*out*/, UINT *lpnVer/*inout*/);

#ifdef __cplusplus
}
#endif
