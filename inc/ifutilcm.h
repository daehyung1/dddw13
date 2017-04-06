#ifndef __IFUTILCM_H__
#define __IFUTILCM_H__

#include <windows.h>

#ifdef UTILCOMMON_EXPORTS
#define UTILCOMMON_LIBSPEC __declspec( dllexport )
#else
#define UTILCOMMON_LIBSPEC
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef BOOL (CALLBACK *PROCENUMPROC)(DWORD, WORD, LPSTR, LPARAM);

UTILCOMMON_LIBSPEC BOOL IFUtilCommon_IsNt();

UTILCOMMON_LIBSPEC BOOL IFUtilCommon_IsWin7();

UTILCOMMON_LIBSPEC BOOL WINAPI IFUtilCommon_EnumProcs(PROCENUMPROC lpProc, LPARAM lParam);

UTILCOMMON_LIBSPEC BOOL WINAPI IFUtilCommon_IsProcessRunning(char *processName);

// return  0  : the module is used in the process
//         -1 : the process is found but the module is not used in the process;
//         -2 : the process is not found in this system;
//         -3 : an internal error occured.
UTILCOMMON_LIBSPEC int WINAPI IFUtilCommon_CheckModuleInProcess(const char *pszModuleName, const char *pszProcessName);
UTILCOMMON_LIBSPEC int WINAPI IFUtilCommon_GetIFGinaModuleNameAndProcessName(char *pszModuleName, char *pszProcessName, int nBufSize);

#ifdef __cplusplus
}
#endif
#endif // __IFUTILCM_H__