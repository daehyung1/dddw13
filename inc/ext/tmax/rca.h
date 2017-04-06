
/* ------------------------ usrinc/rca.h ---------------------- */
/*								*/
/*              Copyright (c) 2000 Tmax Soft Co., Ltd		*/
/*                   All Rights Reserved  			*/
/*								*/
/* ------------------------------------------------------------ */

#ifndef _TMAX_RCA_H
#define _TMAX_RCA_H

#ifndef _WIN32
#include <sys/time.h>
#define __cdecl
#endif

typedef struct wthr_s WTHR_T;

#if defined (__cplusplus)
extern "C" {
#endif

#if defined(_WIN32)
int __cdecl _rcah_main(int argc, char *argv[]);
#endif
int __cdecl tcpread(WTHR_T *wthrp, char *buf, int len, int timeout);
int __cdecl tcpwrite(WTHR_T *wthrp, char *buf, int len);

#if defined (__cplusplus)
}
#endif


#endif
