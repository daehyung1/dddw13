#define	ICWB_SUCCESS	0
#define	ICWB_FAIL		-1

//	win function error
#define ERR_ICWB_LOADLIB_FAIL		-3000	//	LoadLibrary 실패.
#define ERR_ICWB_GETPROCADDR_FAIL	-2999	//	GetProcAddress 실패.
#define ERR_ICWB_FILE_ACCESS_FAIL	-2998	//	file access 실패.

//	win registry error
#define ERR_ICWB_NO_KEY				-2950	//	Registry key access시에 Key가 없음.
#define ERR_ICWB_NO_VALUE			-2949	//	Registry data access시에 DataName이 없음.
#define ERR_ICWB_ACCESS_DENIED		-2948	//	Registry Key access시에 access denied error.
#define ERR_ICWB_CREATE_KEY_FAIL	-2947	//	ICWB_WriteRegValue에서 Registry key create fail.
#define ERR_ICWB_NO_HKEY			-2946	//	root key가 정의되지 않음.

//	icwb registry error
#define ERR_ICWB_COPY_FAIL			-2900	//	Registry data를 LOCAL_MACHINE로부터 CURRENT_USER로 copy실패.
#define ERR_ICWB_GETPATH_FAIL		-2899	//	레지스트리로부터 해당 모듈에 대한 패스획득에 실패.
#define ERR_ICWB_NO_QUERY			-2898	//	query할 data가 status인지 value인지 명시하지 않음.

//	icwb_rac registry error
#define ERR_ICWB_REMOVE_RAC_FAIL	-2850	//	RAC 삭제 실패.
#define ERR_ICWB_CREATE_RAC_FAIL	-2849	//	RAC 생성 실패.
#define ERR_ICWB_READ_RAC_FAIL		-2848	//	Registry data의 RAC를 읽는데 실패.
#define ERR_ICWB_RAC_OFF			-2847	//	Check RAC에서 RAC가 Off로 설정되어 있다.

//	icwb function error
#define ERR_ICWB_USER_ABORT			-2800	//	확장자 변환 중 동일한 이름이 존재할 때 User가 취소 선택.
#define ERR_ICWB_INVALID_EXT		-2799	//	적합하지 않은 확장자.
#define ERR_ICWB_FAIL_QUIT			-2798	//	연산 실패 시 중단.
#define ERR_ICWB_NO_SUPPORT			-2797	//	지원되지 않는 작업을 요청.
#define ERR_ICWB_GETOSVER_FAIL		-2796	//	OS Version 정보 획득 실패.
#define ERR_ICWB_INVALID_HANDLE		-2795	//	적합하지 않은 HANDLE.
#define ERR_ICWB_INVALID_PARAMETER	-2794	//	적합하지 않은 parameter.
