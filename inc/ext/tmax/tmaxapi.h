
/* ------------------------ usrinc/tmaxapi.h ------------------ */
/*								*/
/*              Copyright (c) 2000 Tmax Soft Co., Ltd		*/
/*                   All Rights Reserved  			*/
/*								*/
/* ------------------------------------------------------------ */

#ifndef _TMAXAPI_H
#define _TMAXAPI_H

#include <sys/types.h>
#include <atmi.h>
#ifdef _WIN32
#include <winsock2.h>
#include <svct.h>
#include <sdl.h>
#else
#include <sys/socket.h>
#define __cdecl
#endif

/* client logout type */
#define CLIENT_CLOSE_NORMAL	0
#define CLIENT_CLOSE_ABNORMAL	1
#define CLIENT_PRUNED		2

/* RQ Sub-queue type */
#define TMAX_ANY_QUEUE		0
#define TMAX_FAIL_QUEUE		1
#define TMAX_REQ_QUEUE		2
#define TMAX_RPLY_QUEUE		3
#define TMAX_MAX_QUEUE          4

extern char _rq_sub_queue_name[TMAX_MAX_QUEUE][XATMI_SERVICE_NAME_LENGTH];

/* RQ related macros */
#define RQ_NAME_LENGTH		16

/* unsolicited msg type */
#define UNSOL_TPPOST		1
#define UNSOL_TPBROADCAST	2
#define UNSOL_TPNOTIFY		3
#define UNSOL_TPSENDTOCLI	4

/* Check SVCINFO cmds */
#define ISSVC_FORWARDED	0x00000001
#define ISSVC_NOREPLY	0x00000002

/* TPEVCTL ctl_flags */
#define	TPEV_SVC	0x00000001
#define	TPEV_PROC	0x00000002

struct tpevctl {
    long ctl_flags;
    long post_flags;
    char svc[XATMI_SERVICE_NAME_LENGTH];
    char qname[RQ_NAME_LENGTH];
};

typedef struct tpevctl TPEVCTL;
typedef void __cdecl Unsolfunc(char *, long, long);
#define TPUNSOLERR      ((Unsolfunc *) -1)

/* Multicast call related structures */
struct svglist {
    int	ns_entry;	/* number of entries of s_list */
    int	nf_entry;	/* number of entries of f_list */
    int *s_list;	/* list of server group numbers */
    int *f_list;	/* list of server group numbers */
};

#if defined (__cplusplus)
extern "C" {
#endif

/* ----- unsolicited messaging API ----- */
long __cdecl tpsubscribe(char *eventexpr, char *filter, TPEVCTL *ctl, long flags);
int __cdecl tpunsubscribe(long sd, long flags);
int __cdecl tppost(char *eventname, char *data, long len, long flags);
int __cdecl tpbroadcast(char *lnid, char *usrname, char *cltname, char *data,
	    long len, long flags);
Unsolfunc *__cdecl tpsetunsol(Unsolfunc *func);
int __cdecl tpsetunsol_flag(int flag);
int __cdecl tpgetunsol(int type, char **data, long *len, long flags);
int __cdecl tpclearunsol(void);

/* ----- RQS API -------- */
int __cdecl tpenq(char *qname, char *svc, char *data, long len, long flags);
int __cdecl tpdeq(char *qname, char *svc, char **data, long *len, long flags);
int __cdecl tpqstat(char *qname, long type);
int __cdecl tpqsvcstat(char *qname, char *svc, long type);
int __cdecl tpextsvcname(char *data, char *svc);
int __cdecl tpextsvcinfo(char *data, char *svc, int *type, int *errcode);
int __cdecl tpreissue(char *qname, char *filter, long flags);
char *__cdecl tpsubqname(int type);

/* ----- server API -------- */
int __cdecl tpgetminsvr(void);
int __cdecl tpgetmaxsvr(void);
int __cdecl tpgetmaxuser(void);
int __cdecl tpgetsvrseqno(void);
int __cdecl tpgetmysvrid(void);
int __cdecl tpgetmaxuser(void);
int __cdecl tpsendtocli(int clid, char *data, long len, long flags);
int __cdecl tpgetclid(void);
int __cdecl tpgetpeer_ipaddr(struct sockaddr *name, int *namelen);
int __cdecl tpchkclid(int clid);
int __cdecl tmax_clh_maxuser(void);
int __cdecl tmax_chk_svcinfo(int cmd);

/* ----- etc API ----------- */
int __cdecl tp_sleep(int sec);
int __cdecl tp_usleep(int usec);
int __cdecl tpset_timeout(int sec);
int __cdecl tmaxreadenv(char *file, char *label);
char *__cdecl tpgetenv(char* str);
int __cdecl tpputenv(char* str);
int __cdecl tpgetsockname(struct sockaddr *name, int *namelen);
int __cdecl tpgetpeername(struct sockaddr *name, int *namelen);
int __cdecl tpgetactivesvr(char *nodename, char **outbufp);
int __cdecl tperrordetail(int i);
int __cdecl tpreset(void);
int __cdecl tptobackup();
struct svglist *__cdecl 
    tpmcall(char *qname, char *svc, char *data, long len, long flags);
struct svglist *__cdecl tpgetsvglist(char *svc, long flags);
int __cdecl tpsvgcall(int svgno, char *qname, 
	char *svc, char *data, long len, long flags);
int __cdecl tpflush();
char *__cdecl tmaxlastsvc(char *idata, char *odata, long flags);

#ifndef _TMAX_KERNEL
/* ------- User supplied routines ---------- */
int __cdecl tpsvrinit(int argc, char *argv[]);
int __cdecl tpsvrdone();
void __cdecl tpsvctimeout(TPSVCINFO *msg);
#endif

/* 
   Internal functions: ONLY BE CALLED FROM AUTOMATICALLY 
   GENERATED STUB FILES. DO NOT DIRECTLY CALL THESE FUNCTIONS.
 */
int __cdecl get_clhfd(void);
#if defined(_WIN32)
int __cdecl _tmax_regfn(void *initFn, void *doneFn, void *timeoutFn, void *userMainFn);
int __cdecl _tmax_regtab(int svcTabSz, _svc_t *svcTab, int funcTabSz, void *funcTab);
int __cdecl _tmax_regsdl(int _sdl_table_size2, struct _sdl_struct_s *_sdl_table2,
	int _sdl_field_table_size2, struct _sdl_field_s *_sdl_field_table2);
int __cdecl _tmax_main(int argc, char *argv[]);
int __cdecl _double_encode(char *in, char *out);
int __cdecl _double_decode(char *in, char *out);
#endif

#if defined (__cplusplus)
}
#endif

#endif       /* end of _TMAXAPI_H  */
