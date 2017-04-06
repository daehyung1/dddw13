
/* --------------------- usrinc/svct.h ------------------------ */
/*								*/
/*              Copyright (c) 2000 Tmax Soft Co., Ltd		*/
/*                   All Rights Reserved  			*/
/*								*/
/* ------------------------------------------------------------ */

#ifndef TMAX_SVCT_H
#define TMAX_SVCT_H

#ifndef _WIN32
#define __cdecl
#endif

typedef struct {	/* header from clh to server */
  char  *name;
#ifdef _WIN32
  void  (__cdecl *func) (TPSVCINFO *);
#else
  void  (*func) (TPSVCINFO *);
#endif
  int   svci;
} _svc_t;

#endif
