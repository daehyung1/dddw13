#define	ICWB_SUCCESS	0
#define	ICWB_FAIL		-1

//	win function error
#define ERR_ICWB_LOADLIB_FAIL		-3000	//	LoadLibrary ����.
#define ERR_ICWB_GETPROCADDR_FAIL	-2999	//	GetProcAddress ����.
#define ERR_ICWB_FILE_ACCESS_FAIL	-2998	//	file access ����.

//	win registry error
#define ERR_ICWB_NO_KEY				-2950	//	Registry key access�ÿ� Key�� ����.
#define ERR_ICWB_NO_VALUE			-2949	//	Registry data access�ÿ� DataName�� ����.
#define ERR_ICWB_ACCESS_DENIED		-2948	//	Registry Key access�ÿ� access denied error.
#define ERR_ICWB_CREATE_KEY_FAIL	-2947	//	ICWB_WriteRegValue���� Registry key create fail.
#define ERR_ICWB_NO_HKEY			-2946	//	root key�� ���ǵ��� ����.

//	icwb registry error
#define ERR_ICWB_COPY_FAIL			-2900	//	Registry data�� LOCAL_MACHINE�κ��� CURRENT_USER�� copy����.
#define ERR_ICWB_GETPATH_FAIL		-2899	//	������Ʈ���κ��� �ش� ��⿡ ���� �н�ȹ�濡 ����.
#define ERR_ICWB_NO_QUERY			-2898	//	query�� data�� status���� value���� ������� ����.

//	icwb_rac registry error
#define ERR_ICWB_REMOVE_RAC_FAIL	-2850	//	RAC ���� ����.
#define ERR_ICWB_CREATE_RAC_FAIL	-2849	//	RAC ���� ����.
#define ERR_ICWB_READ_RAC_FAIL		-2848	//	Registry data�� RAC�� �дµ� ����.
#define ERR_ICWB_RAC_OFF			-2847	//	Check RAC���� RAC�� Off�� �����Ǿ� �ִ�.

//	icwb function error
#define ERR_ICWB_USER_ABORT			-2800	//	Ȯ���� ��ȯ �� ������ �̸��� ������ �� User�� ��� ����.
#define ERR_ICWB_INVALID_EXT		-2799	//	�������� ���� Ȯ����.
#define ERR_ICWB_FAIL_QUIT			-2798	//	���� ���� �� �ߴ�.
#define ERR_ICWB_NO_SUPPORT			-2797	//	�������� �ʴ� �۾��� ��û.
#define ERR_ICWB_GETOSVER_FAIL		-2796	//	OS Version ���� ȹ�� ����.
#define ERR_ICWB_INVALID_HANDLE		-2795	//	�������� ���� HANDLE.
#define ERR_ICWB_INVALID_PARAMETER	-2794	//	�������� ���� parameter.
