
/* --------------------- usrinc/atmi.h ------------------------ */
/*								*/
/*              Copyright (c) 2000 Tmax Soft Co., Ltd		*/
/*                   All Rights Reserved  			*/
/*								*/
/* ------------------------------------------------------------ */

#ifndef _TMAX_ATMI_H
#define _TMAX_ATMI_H

#ifndef _WIN32
#define __cdecl
#endif
#ifndef THLVAR
#define THLVAR
#endif

/* Flags to tpinit() for Tuxeedo compatability */
#define TPU_MASK	0x00000007	
#define TPU_SIG		0x00000001	
#define TPU_DIP		0x00000002	
#define TPU_IGN		0x00000004	
#define TPSA_FASTPATH	0x00000008	
#define TPSA_PROTECTED	0x00000010	

/* ---------- flags from API ----- */
/* Most Significant Two Bytes are reserved for internal use */
#ifndef TPNOFLAGS
#define TPNOFLAGS       0x00000000
#endif
#define TPNOBLOCK	0x00000001
#define TPSIGRSTRT      0x00000002
#define TPNOREPLY	0x00000004
#define TPNOTRAN	0x00000008
#define TPTRAN		0x00000010
#define TPNOTIME	0x00000020
#define TPNOGETANY	0x00000040
#define TPGETANY	0x00000080
#define TPNOCHANGE	0x00000100
#define TPBLOCK	        0x00000200
#define TPFLOWCONTROL	0x00000400
#define TPSENDONLY	0x00000800
#define TPRECVONLY	0x00001000
#define TPUDP           0x00002000
#define TPRQS		0x00004000
#define TPFUNC		0x00008000	/* API dependent functional flag */
#define	TPABSOLUTE	(TPFUNC)
#define	TPACK		(TPFUNC)

/* --- flags used in tpstart() --- */
#define TPUNSOL_MASK	0x00000007	
#define TPUNSOL_HND     0x00000001
#define TPUNSOL_IGN     0x00000002
#define TPUNSOL_POLL    0x00000004
#define TPUNIQUE	0x00000010
#define TPONLYONE	0x00000020

#define TPFAIL		0x0001
#define TPSUCCESS	0x0002
#define TPEXIT	        0x0004
#define TPDOWN		0x0008

/* ------ flags for reply type check ----- */
#define TPREQ           0
#define TPERR           -1

/* -------- for Tuxedo Compatability ------- */
/* Flags to tpscmt() - Valid TP_COMMIT_CONTROL characteristic values */
#define TP_CMT_LOGGED	0x01	/* return after commit decision is logged */
#define TP_CMT_COMPLETE	0x02	/* return after commit has completed */

/* Return values to tpchkauth() */
#define TPNOAUTH	0	/* no authentication */
#define TPSYSAUTH	1	/* system authentication */
#define TPAPPAUTH	2	/* system and application authentication */

#define XATMI_SERVICE_NAME_LENGTH 16	/* where x must be > 15 */

struct clid_t {
    long clientdata[4];
};
typedef struct clid_t CLIENTID;

struct tpsvcinfo {
  char name[XATMI_SERVICE_NAME_LENGTH];
  char *data;
  long len;
  long flags;
  int	cd;
  CLIENTID cltid;
};
typedef struct tpsvcinfo TPSVCINFO;

#ifdef _WIN32
#if defined(__cplusplus)
extern "C" {
#endif
/*
   Internal functions: ONLY BE CALLED FROM AUTOMATICALLY
   GENERATED STUB FILES. DO NOT DIRECTLY CALL THESE FUNCTIONS.
 */
int *__cdecl _tmget_tperrno_addr(void);
long *__cdecl _tmget_tpurcode_addr(void);
int __cdecl gettperrno(void);
long __cdecl gettpurcode(void);

#ifndef _MTHRCLI_MODULE
#ifdef _TMAX_KERNEL
extern THLVAR int tperrno;
extern THLVAR long tpurcode;
#else
#define tperrno	(*_tmget_tperrno_addr())
#define tpurcode (*_tmget_tpurcode_addr())
#endif
#endif

#if defined(__cplusplus)
}
#endif
#else
#ifdef _MTHRCLI_MODULE
int gettperrno(void);
long gettpurcode(void);
#else
extern int tperrno;
extern long tpurcode;
#endif
#endif


#define TPEBADDESC	2
#define TPEBLOCK	3
#define TPEINVAL	4
#define TPELIMIT	5
#define TPENOENT	6
#define TPEOS	        7
#define TPEPROTO	9
#define TPESVCERR	10
#define TPESVCFAIL	11
#define TPESYSTEM	12
#define TPETIME		13
#define TPETRAN		14
#define TPGOTSIG	15
#define TPEITYPE	17
#define TPEOTYPE	18
#define TPEEVENT	22
#define TPEMATCH	23
#define TPENOREADY	24
#define TPESECURITY	25
#define TPEQFULL	26
#define TPEQPURGE	27
#define TPECLOSE	28
#define TPESVRDOWN	29
#define TPEPRESVC	30
#define TPEMAXNO	31


/* ---- flags used in conv[]: don't use dummy flags ----*/
#define TPEV_DISCONIMM	0x00000001
#define TPEV_SVCERR	0x00000002
#define TPEV_SVCFAIL	0x00000004
#define TPEV_SVCSUCC	0x00000008
#define TPEV_SENDONLY	0x00000020
#define TPCONV_DUMMY1	0x00000800  /* don't use this flag: TPSENDONLY */
#define TPCONV_DUMMY2	0x00001000  /* don't use this flag: TPRECVONLY */
#define TPCONV_OUT	0x00010000
#define TPCONV_IN	0x00020000


#define X_OCTET		"X_OCTET"
#define X_C_TYPE	"X_C_TYPE"
#define X_COMMON	"X_COMMON"

#define TMTYPEFAIL	-1
#define TMTYPESUCC      0


#ifndef MAXTIDENT
#define MAXTIDENT	XATMI_SERVICE_NAME_LENGTH /* max len of identifier */
#endif

#ifndef MAX_PASSWD_LENGTH
#define MAX_PASSWD_LENGTH  16
#endif
#ifndef MAX_MNAME_LENGTH
#define MAX_MNAME_LENGTH  16
#endif


struct	tpstart_t {
  char	usrname[MAXTIDENT+2];	/* usr name */
  char	cltname[MAXTIDENT+2];	/* application client name */
  char  dompwd[MAX_PASSWD_LENGTH+2]; /* domain password */
  char  usrpwd[MAX_PASSWD_LENGTH+2]; /* passwd for usrid */
  int   flags;
};
typedef	struct	tpstart_t TPSTART_T;


/* X/Open Typed Buffer related Function */ 

#if defined (__cplusplus)
extern "C" {
#endif

/* ----- client API ----- */
int __cdecl tpstart(TPSTART_T *);
int __cdecl tpend();
char *__cdecl  tpalloc(char *type,char *subtype, long size);
char *__cdecl  tprealloc(char *ptr, long size);
long __cdecl tptypes(char *ptr,char *type,char *subtype);
void __cdecl tpfree(char *ptr);
int __cdecl tpcall(char *svc, char *idata, long ilen, char **odata, 
       	      long *olen, long flags);
int __cdecl tpacall(char *svc, char *data, long len, long flags);
int __cdecl tpgetrply(int *cd, char **data, long *len, long flags);
int __cdecl tpcancel(int cd);
char *__cdecl  tpstrerror(int err_no);

/* ----- conversational API ----- */
int __cdecl tpconnect(char *svc, char *data, long lenl, long flagsl);
int __cdecl tpdiscon(int cd);
int __cdecl tpsend(int cd, char *data, long lenl, long flagsl, long *revent);
int __cdecl tprecv(int cd, char **data, long *len, long flagsl, long *revent);

/* ----- server API -------- */
void __cdecl tpreturn(int rval, long rcode, char *data, long len, long flags);
void __cdecl tpforward(char *svc, char *data, long len, long flags);

#if defined (__cplusplus)
}
#endif

#endif       /* end of _TMAX_ATMI_H  */
