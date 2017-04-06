
/* ------------------------ usrinc/usignal.h ------------------ */
/*								*/
/*              Copyright (c) 2000 Tmax Soft Co., Ltd		*/
/*                   All Rights Reserved  			*/
/*								*/
/* ------------------------------------------------------------ */

#ifndef _TMAX_USIGNAL_H
#define _TMAX_USIGNAL_H

#ifndef _WIN32
#define __cdecl
#endif

#define TMAX_DEFER_GET  0
#define TMAX_DEFER_SET  1
#define TMAX_DEFER_INC  2

#if defined (__cplusplus)
extern "C" {
#endif

typedef void __cdecl Sigfunc(int);

int __cdecl _tmax_signal_control();
int __cdecl _tmax_defer_sigs(int method, int value);
Sigfunc *__cdecl _tmax_signal(int signo, Sigfunc *func);

/*
   Following macros are provided for compatibility.
 */
#define UDEFERSIGS()	_tmax_defer_sigs(TMAX_DEFER_INC, 1)
#define URESUMESIGS()	_tmax_defer_sigs(TMAX_DEFER_INC, -1)
#define USDEFERLEVEL(level)	_tmax_defer_sigs(TMAX_DEFER_SET, level)
#define UGDEFERLEVEL(level)	_tmax_defer_sigs(TMAX_DEFER_GET, 0)
#define UENSURESIGS()	_tmax_defer_sigs(TMAX_DEFER_SET, 0)

#define Usiginit()	_tmax_signal_control()
#define Usignal(signo, func)	_tmax_signal(signo, func)
#define USIGTYP		void

#if defined (__cplusplus)
}
#endif

#endif       /* end of _TMAX_USIGNAL_H  */
