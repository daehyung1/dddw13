
/* --------------------- usrinc/fbuf.h ------------------------ */
/*								*/
/*              Copyright (c) 2000 Tmax Soft Co., Ltd		*/
/*                   All Rights Reserved  			*/
/*								*/
/* ------------------------------------------------------------ */

#ifndef _TMAX_FBUF_H
#define _TMAX_FBUF_H

#include  <stdio.h>
#include  <sdl.h>

#ifndef _WIN32
#define __cdecl
#endif
#ifndef THLVAR
#define THLVAR
#endif

/* field types */
#define FB_CHAR	        SDL_CHAR
#define FB_SHORT	SDL_SHORT
#define FB_INT   	SDL_INT
#define FB_LONG	        SDL_LONG
#define FB_LLONG	SDL_LLONG
#define FB_FLOAT	SDL_FLOAT
#define FB_DOUBLE	SDL_DOUBLE
#define FB_STRING	SDL_STRING
#define FB_CARRAY	SDL_CARRAY

#define BADFLDKEY       0
#define FIRSTFLDKEY     0

/* ---- type definition --- */
typedef int     FLDKEY;
typedef int     FLDLEN;
typedef struct  fbuf_s FBUF;
typedef FBUF*   pFBUF;


/* ----- fb op mode ----- */
#define FBMOVE          1
#define FBCOPY          2
#define FBCOMP          3
#define FBCONCAT        4
#define FBJOIN          5
#define FBOJOIN         6
#define FBUPDATE        7

/* ------- fberror code ----- */
#define FBEBADFB        3
#define FBEINVAL	4
#define FBELIMIT	5
#define FBENOENT	6
#define FBEOS	        7
#define FBEBADFLD       8
#define FBEPROTO	9
#define FBENOSPACE	10
#define FBEMALLOC	11
#define FBESYSTEM	12
#define FBETYPE	        13
#define FBEMATCH	14
#define FBEBADSTRUCT	15
#define FBEMAXNO	19

#define FBGET(fbuf, fldid, loc)    fbget(fbuf, fldid, loc, 0, 0)
#define FBPUT(fbuf, fldid, val)    fbget(fbuf, fldid, loc, -1, 0)

/* --------- External declarations ----------  */
#ifdef _WIN32
#if defined(__cplusplus)
extern "C" {
#endif
/*
   Internal functions: ONLY BE CALLED FROM AUTOMATICALLY
   GENERATED STUB FILES. DO NOT DIRECTLY CALL THESE FUNCTIONS.
 */
int *__cdecl _tmget_fberror_addr(void);

int  __cdecl getfberror(void);
int  __cdecl getfberrno(void);
#ifndef _MTHRCLI_MODULE
#ifdef _TMAX_KERNEL
extern THLVAR int fberror;
#else
#define fberror	 (*_tmget_fberror_addr())
#endif
#endif

#if defined(__cplusplus)
}
#endif

#else
#ifdef _MTHRCLI_MODULE
int getfberror(void);
int getfberrno(void);
#else
extern int fberror;
#endif
#endif


/* ------- FBUF API ------- */
#if defined(__cplusplus)
extern "C" {
#endif

int __cdecl fbget(FBUF *fbuf, FLDKEY fldkey, char *loc, int *fldlen);
int __cdecl fbput(FBUF *fbuf, FLDKEY fldkey, char *value, int fldlen);
int __cdecl fbinsert(FBUF *fbuf, FLDKEY fldkey, int nth, char *value, int fldlen);
int __cdecl fbupdate(FBUF *fbuf, FLDKEY fldkey, int nth, char *value, int fldlen);
int __cdecl fbdelete(FBUF *fbuf, int fldkey, int nth);
char *__cdecl  fbgetval(FBUF *fbuf, FLDKEY fldkey, int nth, FLDLEN *len);
int __cdecl fbgetnth(FBUF *fbuf, FLDKEY fldkey, char *value, FLDLEN len);
int __cdecl fbkeyoccur(FBUF *fbuf, FLDKEY fldkey);
int __cdecl fbgetf(FBUF *fbuf, FLDKEY fldkey, char *loc, int *fldlen, int *pos);

int __cdecl fbdelall(FBUF *fbuf, int fldkey);
int __cdecl fbfldcount(FBUF *fbuf);
int __cdecl fbispres(FBUF *fbuf, FLDKEY fldkey, int nth);
char *__cdecl fbgetvals(FBUF *fbuf, FLDKEY fldkey, int nth);
int __cdecl fbgetvali(FBUF *fbuf, FLDKEY fldkey, int nth);

char *__cdecl fbtypecvt(FLDLEN *tolen, int totype, char *fromval, int fromtype, 
         FLDLEN fromlen);
int __cdecl fbputt(FBUF *fbuf, FLDKEY fldkey, char *value, FLDLEN len, int type);
char *__cdecl fbgetvalt(FBUF *fbuf, FLDKEY fldkey, int nth, FLDLEN *len, int totype);
int __cdecl fbgetntht(FBUF *fbuf, FLDKEY fldkey, char *value, FLDLEN len, int fromtype);

FLDKEY  __cdecl fbget_fldkey(char *name);
char *__cdecl fbget_fldname(FLDKEY fldkey);
int  __cdecl fbget_fldno(FLDKEY fldkey);
int  __cdecl fbget_fldtype(FLDKEY fldkey);
char *__cdecl fbget_strfldtype(FLDKEY fldkey);
FLDKEY __cdecl fbmake_fldkey(int type, int no);
void __cdecl fbnmkey_unload();
void __cdecl fbkeynm_unload();

int __cdecl fbisfbuf(FBUF *fbuf);
long __cdecl fbcalcsize(int count, FLDLEN datalen);
int __cdecl fbinit(FBUF *fbuf, FLDLEN buflen);
FBUF *__cdecl  fballoc(int count, int len);
int __cdecl fbfree(FBUF *fbuf);
long __cdecl fbget_fbsize(FBUF *fbuf);
long __cdecl fbget_unused(FBUF *fbuf);
long __cdecl fbget_used(FBUF *fbuf);
FBUF *__cdecl  fbrealloc(FBUF *fbuf, int ncount, int nlen);

int __cdecl fbbufop(FBUF *dest, FBUF *src, int mode);
int __cdecl fbbufop_proj(FBUF *dest, FBUF *src, FLDKEY *fldkey);

int __cdecl fbread(FBUF *fbuf, FILE *iop);
int __cdecl fbwrite(FBUF *fbuf, FILE *iop);
int __cdecl fbprint(FBUF *fbuf);
int __cdecl fbfprint(FBUF *fbuf, FILE *iop);

int __cdecl fbchg_tu(FBUF *fbuf, FLDKEY fldkey, int nth, char *value, int fldlen);
int __cdecl fbdelall_tu(FBUF *fbuf, int *fldkey);
char *__cdecl fbgetval_last_tu(FBUF *fbuf, FLDKEY fldkey, int *nth, FLDLEN *len);
int __cdecl fbget_tu(FBUF *fbuf, FLDKEY fldkey, int nth, char *loc, int *maxlen);
char *__cdecl fbgetalloc_tu(FBUF *fbuf, FLDKEY fldkey, int nth, int *extralen);
int __cdecl fbgetlast_tu(FBUF *fbuf, FLDKEY fldkey, int *nth, char *loc, int *maxlen);
int __cdecl fbnext_tu(FBUF *fbuf, FLDKEY *fldkey, int *nth, char *value, int *len);
char *__cdecl fbgetvals_tu(FBUF *fbuf, FLDKEY fldkey, int nth);
long __cdecl fbgetvall_tu(FBUF *fbuf, FLDKEY fldkey, int nth);
int __cdecl fbchg_tut(FBUF *fbuf, FLDKEY fldkey, int nth, char *value, FLDLEN len, 
         int type);
int __cdecl fbget_tut(FBUF *fbuf, FLDKEY fldkey, int nth, char *loc, FLDLEN *len, 
         int type);
char *__cdecl fbgetalloc_tut(FBUF *fbuf, FLDKEY fldkey, int nth, int totype, 
          FLDLEN *extralen);
int  __cdecl fbgetlen(FBUF *fbuf, FLDKEY fldkey, int nth);

int __cdecl fbftos(FBUF *fbuf, char *cstruct, char *stname);
int __cdecl fbstof(FBUF *fbuf, char *cstruct, int mode, char *stname);
int __cdecl fbsnull(char *cstruct, char *cname, int nth, char *stname);
int __cdecl fbstinit(char *cstruct, char *stname);
int __cdecl fbstelinit(char *cstruct, char *cname, char *stname);

char *__cdecl fbstrerror(int err_no);

/*
   Internal functions: ONLY BE CALLED FROM AUTOMATICALLY
   GENERATED STUB FILES. DO NOT DIRECTLY CALL THESE FUNCTIONS.
 */
char *__cdecl _find_matching_fldkey(FBUF *fbuf, FLDKEY fldkey, int nth);
int __cdecl _get_alen_from_curpos(char *cur);
int __cdecl _get_fldlen_from_curpos(char *cur);

#if defined(__cplusplus)
}
#endif


#endif
