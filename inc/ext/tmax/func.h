
/* ---------------------- include/func.h ---------------------- */
/*								*/
/*              Copyright (c) 2000 Tmax Soft Co., Ltd		*/
/*                   All Rights Reserved  			*/
/*								*/
/* ------------------------------------------------------------ */

#ifndef TMAX_FUNC_H
#define TMAX_FUNC_H

#ifndef _WIN32
#define __cdecl
#endif

typedef struct { /* header from clh to server */
  char  *name;
  void  (__cdecl *func) (tp_ms_inf_t *info, 
		  tp_ms_area_t *input,
		  tp_ms_area_t *work,
		  tp_ms_area_t *output,
		  tp_ms_area_t *save);
  int   svci;
} _func_t;

extern _func_t _func_tab[];
extern int _func_tab_size;

#endif
