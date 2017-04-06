#ifndef _SCMOD_H_
#define _SCMOD_H_

#include "base_define.h"
#include "ckm_pkcrypt.h"

#ifdef SCMOD_EXPORTS
#define SCMOD_LIBSPEC __declspec(dllexport)
#else
#define SCMOD_LIBSPEC __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_READERNAME_LEN 256
#define MAX_RESPONSE_LEN 2048

enum SspMod_ERROR {
  SspMod_CONTEXT_NULL         = -1,
  SspMod_CARD_NOT_FOUND       = -2,
  SspMod_SESS_KEY_NOT_ESTABLISHED = -3,
  SspMod_ACCESS_DENYED = -4,
  SspMod_PIN_BLOCKED = -5,
  SspMod_EXCEED_VALID_TERM = -6,
  SspMod_EXCEED_FIELD_LEN = -7,
  SspMod_INVALID_USERNAME = -8,
};

typedef void* SCCtx;

SCMOD_LIBSPEC SCCtx SspMod_Open(int port); 
SCMOD_LIBSPEC void  SspMod_Close(SCCtx ctx);
SCMOD_LIBSPEC int   SspMod_GetPort(SCCtx ctx);

SCMOD_LIBSPEC int SspMod_WaitChange(SCCtx ctx);
SCMOD_LIBSPEC int SspMod_SuspendCheckCard(SCCtx ctx);
SCMOD_LIBSPEC int SspMod_ResumeCheckCard(SCCtx ctx);

SCMOD_LIBSPEC int SspMod_IsCardIn(SCCtx ctx);
SCMOD_LIBSPEC int SspMod_GetReaderName(int num, PCHAR Readername);

SCMOD_LIBSPEC int SspMod_EstablishSessKey(SCCtx ctx);
SCMOD_LIBSPEC int SspMod_VerifyPin(SCCtx ctx);
SCMOD_LIBSPEC int SspMod_BlockPIN(SCCtx ctx);

SCMOD_LIBSPEC int SspMod_ReadCardID(BYTE *bin, int *binLen, SCCtx ctx);
SCMOD_LIBSPEC int SspMod_GetVersion(BYTE *ver, SCCtx ctx);
SCMOD_LIBSPEC int SspMod_GetUserInfo(BYTE *userInfo, int *userInfoLen, SCCtx ctx);
SCMOD_LIBSPEC int SspMod_GetSCertInfo(char *sdn, char *idn, char *sn, int *snLen, SCCtx ctx);
SCMOD_LIBSPEC int SspMod_GetECertInfo(char *sdn, char *idn, char *sn, int *snLen, SCCtx ctx);
SCMOD_LIBSPEC int SspMod_GetSPriKey(PrivateKeyInfo **priKeyInfo, SCCtx ctx, char *passwd);
SCMOD_LIBSPEC int SspMod_GetEPriKey(PrivateKeyInfo **priKeyInfo, SCCtx ctx, char *passwd);
SCMOD_LIBSPEC int SspMod_GetSymmKey(BYTE *symmKey, int *symmKeyLen, SCCtx ctx, char *passwd);
SCMOD_LIBSPEC int SspMod_GetPwdInfo(int *mpn, int *scr, time_t *lu, SCCtx ctx);
SCMOD_LIBSPEC int SspMod_GetTermInfo(time_t *notBefore, time_t *notAfter, SCCtx ctx);

SCMOD_LIBSPEC int SspMod_SetSCertInfo(Certificate *cert, SCCtx ctx);
SCMOD_LIBSPEC int SspMod_SetECertInfo(Certificate *cert, SCCtx ctx);
SCMOD_LIBSPEC int SspMod_SetSPriKey(PrivateKeyInfo *priInfo, SCCtx ctx, char *passwd);
SCMOD_LIBSPEC int SspMod_SetEPriKey(PrivateKeyInfo *priInfo, SCCtx ctx, char *passwd);
SCMOD_LIBSPEC int SspMod_SetSymmKey(char *symKey, int symKeyLen, char *passwd, SCCtx ctx);

SCMOD_LIBSPEC int SspMod_IsFirstUse(SCCtx ctx);
SCMOD_LIBSPEC int SspMod_CheckValidTime(time_t now, SCCtx ctx);
SCMOD_LIBSPEC int SspMod_VerifyUser(char *passwd, char *userName, time_t now, time_t validTerm, SCCtx ctx);
SCMOD_LIBSPEC int SspMod_ChangePwd( char *oldPasswd, char *newPasswd, SCCtx ctx);

SCMOD_LIBSPEC void SspMod_FreePriKey(PrivateKeyInfo  *priKeyInfo);
SCMOD_LIBSPEC int SspMod_SelectFile(SCCtx ctx, PBYTE df_aid);

#ifdef SCMOD_MANAGER
SCMOD_LIBSPEC int SspMod_VerifyMngPin(SCCtx ctx);
SCMOD_LIBSPEC int SspMod_UnblockPIN(SCCtx ctx);
SCMOD_LIBSPEC int SspMod_WriteBin(BYTE fid, BWT offset, BYTE *bin, int binLen, SCCtx ctx);
SCMOD_LIBSPEC int SspMod_ReadBin(BYTE fid, BWT offset, BYTE *bin, int *binLen, SCCtx ctx);
SCMOD_LIBSPEC int SspMod_WriteBinEx(BYTE *bin, int binLen, SCCtx ctx);
SCMOD_LIBSPEC int SspMod_ReadBinEx(BYTE *buf, int bufLen, long* pReadLen, SCCtx ctx);
#endif

#ifdef __cplusplus
}
#endif

#endif
