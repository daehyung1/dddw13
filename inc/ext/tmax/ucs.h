
/* ------------------------ usrinc/ucs.h ---------------------- */
/*								*/
/*              Copyright (c) 2000 Tmax Soft Co., Ltd		*/
/*                   All Rights Reserved  			*/
/*								*/
/* ------------------------------------------------------------ */

#ifndef _TMAX_UCS_H
#define _TMAX_UCS_H

#ifndef _WIN32
#include <sys/time.h>
#define __cdecl
#endif

#define	UCS_ERROR	(-1)
#define	UCS_TMAX_MSG	1
#define UCS_USER_MSG	2

typedef struct {
	long	urcode;
	int	errcode;
	int	msgtype;
	int	cd;
	int	len;
	char	*data;
} UCSMSGINFO;

typedef int (__cdecl *UcsCallback)(UCSMSGINFO*);
#define CTX_USR_SIZE    256
#ifdef _TMAX_KERNEL
typedef struct ctx_s CTX_T;
#else
typedef struct {
	int   version[4];
	char  data[CTX_USR_SIZE - 16];
} CTX_T;
#endif

#if defined (__cplusplus)
extern "C" {
#endif

#ifndef _TMAX_KERNEL
int __cdecl usermain(int argc, char *argv[]);
#endif
int __cdecl tpschedule(int sec);
int __cdecl tpuschedule(int usec);

/* register and unregister monitoring fds */
int __cdecl tpsetfd(int fd);
int __cdecl tpissetfd(int fd);
int __cdecl tpclrfd(int fd);

/* register and unregister callback function */
int __cdecl tpregcb(UcsCallback);
int __cdecl tpunregcb();

int __cdecl tpsvrdown();
int __cdecl tprelay(char *svc, char *data, long len, long flags, CTX_T *ctxp);
CTX_T * __cdecl tpsavectx();
int __cdecl tpgetctx(CTX_T *ctxp);
int __cdecl tpcancelctx(CTX_T *ctxp);

#if defined (__cplusplus)
}
#endif


#endif
