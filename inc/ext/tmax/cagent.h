
/* ----------------------- usrinc/cagent.h -------------------- */
/*								*/
/*              Copyright (c) 2000 Tmax Soft Co., Ltd		*/
/*                   All Rights Reserved  			*/
/*								*/
/* ------------------------------------------------------------ */

#ifndef _TMAX_CAGENT_H
#define _TMAX_CAGENT_H

#include <tmaxapi.h>
#ifndef _WIN32
#include <sys/time.h>
#define __cdecl
#endif

/* cagent shutdown code */
#define CA_SHUTDOWN_NORMAL	(0)
#define CA_SHUTDOWN_ERROR	(1)

/* ca_xxx function return value */
#define	CA_OK		(0)
#define CA_ERROR	(-1)
#define CA_DROP_CLIENT	(-2)
#define CA_DROP_MSG	(-3)

/* cagent client close type */
#define CA_CLOSE_NORMAL	(CLIENT_CLOSE_NORMAL)
#define CA_CLOSE_ERROR	(CLIENT_CLOSE_ABNORMAL)
#define CA_CLOSE_IDLE	(CLIENT_PRUNED)

/* ca_info_t type field */
#define	CA_REQ_MSG	(0)
#define	CA_RPLY_MSG	(1)
#define	CA_UNSOL_MSG	(2)
#define	CA_UNKNOWN_MSG	(3)

/* etc macros */
#define CA_MSG_RESERVE  (512)

typedef struct {
	char	svcname[16];
	int	type;
	int	urcode;
	int	errcode;
	int	uid;
	int	len;
	int	flags;
} ca_info_t;

typedef struct {
	int len;
	char *dp;
} rush_data_t;


#if defined (__cplusplus)
extern "C" {
#endif

extern int ca_header_size;

#if defined(_WIN32) && defined(_TMAX_KERNEL)
extern int (__cdecl *ca_init)(int port, int argc, char *argv[]);
extern int (__cdecl *ca_shutdown)(int code);
extern int (__cdecl *ca_connected)(int clid);
extern int (__cdecl *ca_closed)(int clid, int reason);
extern int (__cdecl *ca_get_length)(int clid, char *ca_header);
extern int (__cdecl *ca_msg_to_tmax)(int clid, char *ca_header, char *ca_body,
	            ca_info_t *tmax_header, char *tmax_body);
extern int (__cdecl *ca_msg_from_tmax)(int clid, char *ca_header, char *ca_body,
	            ca_info_t *tmax_header, char *tmax_body);
#else

int __cdecl ca_init(int port, int argc, char *argv[]);
int __cdecl ca_shutdown(int code);
int __cdecl ca_connected(int clid);
int __cdecl ca_closed(int clid, int reason);
int __cdecl ca_get_length(int clid, char *ca_header);
int __cdecl ca_msg_to_tmax(int clid, char *ca_header, char *ca_body,
	            ca_info_t *tmax_header, char *tmax_body);
int __cdecl ca_msg_from_tmax(int clid, char *ca_header, char *ca_body,
	            ca_info_t *tmax_header, char *tmax_body);

#if defined(_WIN32)
/* 
    Internal functions: ONLY BE CALLED FROM AUTOMATICALLY 
    GENERATED STUB FILES. DO NOT DIRECTLY CALL THESE FUNCTIONS.
 */
int __cdecl _ca_regfn(int *headerSz, void *initFn, void *shutdownFn, 
	void *conFn, void *closeFn, void *lenFn, void *toFn, void *fromFn);
int __cdecl _ca_main(int argc, char *argv[]);
#endif
#endif

#if defined (__cplusplus)
}
#endif


#endif
