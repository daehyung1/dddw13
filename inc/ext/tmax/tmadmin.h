
/* ------------------------ usrinc/tmadmin.h ------------------ */
/*								*/
/*              Copyright (c) 2000 Tmax Soft Co., Ltd		*/
/*                   All Rights Reserved  			*/
/*								*/
/* ------------------------------------------------------------ */

#ifndef _TMADMIN_H
#define _TMADMIN_H
#define _TMADMIN_VERSION	10000	/* 01.00.00 */

#include <sys/types.h>
#ifdef _WIN32
#include <winsock2.h>
#else
#include <sys/socket.h>
#define __cdecl
#endif

/* 
   TMADMIN COMMANDS 
 */

/* simple commands */
#define TMADM_DISCON		1	/* client disconnect */
#define TMADM_CLIINFO		2	/* client information */
#define TMADM_QPURGE		3	/* server q purge */
#define TMADM_BOOT		4	/* tmboot */
#define TMADM_DOWN		5	/* tmdown */
#define TMADM_SUSPEND		6	/* suspend process */
#define TMADM_RESUME		7	/* resume process */
#define TMADM_RESTAT		8	/* reset statistics */

/* statistics */
#define TMADM_SVC_STAT		11
#define TMADM_SPR_STAT		12
#define TMADM_SVR_STAT		13

/* configuration */
#define TMADM_TMAX_INFO		20
#define TMADM_DOMAIN_CONF	21
#define TMADM_NODE_CONF		22
#define TMADM_SVG_CONF		23
#define TMADM_SVR_CONF		24
#define TMADM_SVC_CONF		25

/* tmadmin option flags */
#ifndef TPNOFLAGS
#define TPNOFLAGS       0x00000000
#endif
#define TMADM_AFLAG	0x00000001	/* ALL */
#define TMADM_CFLAG	0x00000002	/* CLH or Client */
#define TMADM_FFLAG	0x00000004	/* Force */
#define TMADM_GFLAG	0x00000008	/* SVG or Gateway */
#define TMADM_IFLAG	0x00000010	/* Immediate or Idle */
#define TMADM_NFLAG	0x00000020	/* Not Ready or Node or Number */
#define TMADM_PFLAG	0x00000040	/* Server Process */
#define TMADM_RFLAG	0x00000080	/* RQ */
#define TMADM_SFLAG	0x00000100	/* SVR or SVC */
#define TMADM_TFLAG	0x00000200	/* TMS */
#define TMADM_VFLAG	0x00000400	/* SVR */

/* ETC macros */
#define MAX_NUM_PORTNO		8	/* >= MAX_LISTEN	*/
#define MAX_NUM_CLH		10	/* >= MAX_CLHS		*/

#define TMAX_NAME_SIZE		16
#define TMAX_PATH_LENGTH	256
#define TMAX_CLOPT_LENGTH	256
#define TMAX_DBINFO_SIZE	256

/* Fixed header structure */
struct tmadm_header {
	int	version;	/* I: _TMADMIN_VERSION */
	int	size;		/* I: totoal buffer size */
	int	offset;		/* I: fetch offset */
	int	num_entry;	/* O: number of fetched entries */
	int	num_left;	/* O: number of entries to fetch */
	int	opt_int;	/* I: optional integer argument */
	int	reserve_int[2];			
	char	opt_char[TMAX_NAME_SIZE]; /* I: optinal string */
};


/* TMADM_DOMAIN_CONF return structures */
struct tmadm_domain_conf_body {
	int	no;				/* reserved */
	int	domain_id;
	int	shmkey;
	int	minclh;
	int	maxclh;
	int	maxuser;
	int	tportno;
	int	racport;
	int	cpc;
	int	blocktime;
	int	txtime;
	int	clichkint;
	int	nliveinq;
	int	nclhchkint;
	int	cmtret;
	int	security;
	/* -- client/server table paramters -- */
	int	maxsacall;
	int	maxcacall;
	int	maxconvn;
	int	maxconvs;
	/* --- maximum configuration values --- */
	int	maxnode;
	int	maxsvg;
	int	maxsvr;
	int	maxsvc;
	int	maxspr;
	int	maxtms;
	int	maxcpc;
	int	maxrout;
	int	maxroutsvg;
	int	maxrq;
	int	maxgw;
	int	maxcousin;
	int	maxcousinsvg;
	int	maxbackup;
	int	maxbackupsvg;
	int	maxtotalsvg;
	int	maxprod;
	int	maxfunc;
	/* ------------------------------------ */
	int	reserve_int[2];
	char	name[TMAX_NAME_SIZE];	/* domain name */
	char	owner[TMAX_NAME_SIZE];
};

struct tmadm_domain_conf {
	/* fixed header */
	struct tmadm_header header;
	/* fixed body */
	struct tmadm_domain_conf_body body;
};


/* TMADM_NODE_CONF return structures */
struct tmadm_node_conf_body {
	int	no;
	int	shmkey;
	int	shmsize;
	int	minclh;
	int	maxclh;
	int	maxuser;
	int	clhqtimeout;
	int	idletime;
	int	clichkint;
	int	racport;
	int	rscpc;
	int	ipcperm;
	unsigned int ip;
	int	maxsvg;
	int	maxsvr;
	int	maxspr;
	int	maxtms;
	int	maxcpc;
	int	reserve_int[2];			/* reserved */
	int	scaport[MAX_NUM_PORTNO];
	int	tmaxport[MAX_NUM_PORTNO];
	char	name[TMAX_NAME_SIZE];
	char	logoutsvc[TMAX_NAME_SIZE];
	char	realsvr[TMAX_NAME_SIZE];
	char	reserve_str[TMAX_NAME_SIZE];	/* reserved */
	char	tmaxdir[TMAX_PATH_LENGTH];
	char	appdir[TMAX_PATH_LENGTH];
	char	pathdir[TMAX_PATH_LENGTH];
	char	tlogdir[TMAX_PATH_LENGTH];
	char	slogdir[TMAX_PATH_LENGTH];
	char	ulogdir[TMAX_PATH_LENGTH];
	char	envfile[TMAX_PATH_LENGTH];
	/* ----- other information -----  */
	int	curclh;
	int	clh_maxuser;
	int	svgcount;
	int	svrcount;
	int	svccount;
	int	sprcount;
	int	reserve_int2[2];		/* reserved */
	int	clicount[MAX_NUM_CLH];
};

struct tmadm_node_conf {
	/* fixed header */
	struct tmadm_header header;
	/* fixed body */
	struct tmadm_node_conf_body body;
};


/* TMADM_SVG_CONF return structures */
struct tmadm_svg_conf_body {
	int	no;
	int	curtms;
	int	mintms;
	int	maxtms;
	int	reserve_int[4];			/* reserved */
	char	name[TMAX_NAME_SIZE];
	char	svgtype[TMAX_NAME_SIZE];
	char	owner[TMAX_NAME_SIZE];
	char	dbname[TMAX_NAME_SIZE];
	char	tmsname[TMAX_NAME_SIZE];
	char	appdir[TMAX_PATH_LENGTH];
	char	ulogdir[TMAX_PATH_LENGTH];
	char	envfile[TMAX_PATH_LENGTH];
	char	openinfo[TMAX_DBINFO_SIZE];
	char	closeinfo[TMAX_DBINFO_SIZE];
};

struct tmadm_svg_conf {
	/* fixed header */
	struct tmadm_header header;
	/* variable length body */
	struct tmadm_svg_conf_body svg[1];
};


/* TMADM_SVR_CONF return structures */
struct tmadm_svr_conf_body {
	int	no;
	int	svgno;
	int	cursvr;
	int	minsvr;
	int	maxsvr;
	int	conv;
	int	maxqcount;
	int	asqcount;
	int	maxrstart;
	int	gperiod;
	int	restart;
	int	cpc;
	int	reserve_int[4];			/* reserved */
	char	name[TMAX_NAME_SIZE];
	char	target[TMAX_NAME_SIZE];
	char	svrtype[TMAX_NAME_SIZE];
	char	reserve_str[TMAX_NAME_SIZE];	/* reserved */
	char	clopt[TMAX_CLOPT_LENGTH];
	char	ulogdir[TMAX_PATH_LENGTH];
};

struct tmadm_svr_conf {
	/* fixed header */
	struct tmadm_header header;
	/* variable length body */
	struct tmadm_svr_conf_body svr[1];
};


/* TMADM_SVR_CONF return structures */
struct tmadm_svc_conf_body {
	int	svctime;
	int	svri;	/* -1 means this node does not support this svc */
	int	reserve_int[2];			/* reserved */
	char	name[TMAX_NAME_SIZE];
	char	reserve_str[TMAX_NAME_SIZE];	/* reserved */
};

struct tmadm_svc_conf {
	/* fixed header */
	struct tmadm_header header;
	/* variable length body */
	struct tmadm_svc_conf_body svc[1];
};


/* TMADM_TMAX_INFO return structures */
struct tmadm_tmax_info_body {
	int	sysinfo;	/* OS version */
	int	version;	/* major*10000 + minor*100 + patch */
	int	expdate;	/* if demo license year*10000 + month*100 + day,
				   otherwise 0 */
	int	maxuser;	/* if unlimited, maxuser = -1 */
	int	nodecount;
	int	svgcount;
	int	svrcount;
	int	svccount;
	int	rqcount;
	int	gwcount;
	int	rout_gcount;	/* rout group count */
	int	rout_count;
	int	cousin_gcount;	/* cousin group count: svg  */
	int	cousin_count;
	int	backup_gcount;	/* backup group count: svg */
	int	backup_count;
	/* for TopEnd */
	int	prod_count;
	int	func_count;
	int	reserve[6];
};

struct tmadm_node_summary {
	int	no;		/* node number */
	int	port;		/* TPORTNO[0] */
	int	racport;
	int	shmkey;
	int	shmsize;
	int	minclh;
	int	maxclh;
	unsigned int	ip;
	char	name[TMAX_NAME_SIZE];
	int	reserve[4];
};

struct tmadm_tmax_info {
	/* fixed header */
	struct tmadm_header header;
	/* fixed body */
	struct tmadm_tmax_info_body body;
	/* variable length body */
	struct tmadm_node_summary node[1];
};


/* TMADM_SVC_STAT return structures */
struct tmadm_svc_stat_body {
	int	no;
	int	clhno;
	int	count;
	int	cq_count;
	int	aq_count;
	int	reserve[3];
	float	average;
	float	q_average;
	char	name[TMAX_NAME_SIZE];
	char	status[TMAX_NAME_SIZE];
	/* char	reserve_str[TMAX_NAME_SIZE*2]; */
};

struct tmadm_svc_stat {
	/* fixed header */
	struct tmadm_header header;
	/* variable length body */
	struct tmadm_svc_stat_body svc[1];
};


/* TMADM_SPR_STAT return structures */
struct tmadm_spr_stat_body {
	int	no;
	int	clhno;
	int	count;
	int	reserve[4];
	float	average;
	char	name[TMAX_NAME_SIZE];
	char	svgname[TMAX_NAME_SIZE];
	char	status[TMAX_NAME_SIZE];
	char	service[TMAX_NAME_SIZE];
};

struct tmadm_spr_stat {
	/* fixed header */
	struct tmadm_header header;
	/* variable length body */
	struct tmadm_spr_stat_body spr[1];
};


/* TMADM_SVR_STAT return structures */
struct tmadm_svr_stat_body {
	int	svri;
	int	clhno;
	int	count;
	int	qcount;
	int	qpcount;
	int	emcount;
	int	reserve_int[2];
	char	name[TMAX_NAME_SIZE];
	char	status[TMAX_NAME_SIZE];
	char	reserve_str[TMAX_NAME_SIZE*2];
};

struct tmadm_svr_stat {
	/* fixed header */
	struct tmadm_header header;
	/* variable length body */
	struct tmadm_svr_stat_body svr[1];
};


/* TMADM_CLIINFO return structures */
struct tmadm_cliinfo_body {
	int	no;	/* cli index */
	int	clid;	/* CLID */
	int	clhno;
	int	count;	
	int	idle;
	int	reserve_int[3];
	char	status[TMAX_NAME_SIZE];
	char	addr[TMAX_NAME_SIZE];
	char	usrname[TMAX_NAME_SIZE];
	char	reserve_str[TMAX_NAME_SIZE];
};

struct tmadm_cliinfo {
	/* fixed header */
	struct tmadm_header header;
	/* variable length body */
	struct tmadm_cliinfo_body cli[1];
};


/* TMADM_BOOT return structures */
struct tmadm_boot_body {
	int	count;
	int	opt_int[3];
	char	name1[TMAX_NAME_SIZE];
	char	name2[TMAX_NAME_SIZE];
	char	clopt[TMAX_CLOPT_LENGTH];
};

struct tmadm_boot {
	/* fixed header */
	struct tmadm_header header;
	/* fixed body */
	struct tmadm_boot_body args;
};


/* TMADM_DOWN return structures */
struct tmadm_down_body {
	int	count;
	int	opt_int[3];
	char	name1[TMAX_NAME_SIZE];
	char	name2[TMAX_NAME_SIZE];
};

struct tmadm_down {
	/* fixed header */
	struct tmadm_header header;
	/* fixed body */
	struct tmadm_down_body args;
};


#if defined (__cplusplus)
extern "C" {
#endif

/*
   tmadmin(TMADM_DISCON, int *clid, TMADM_FFLAG, TPNOFLAGS);
   tmadmin(TMADM_NODE_INFO, struct tmadm_node_info *info, TPNOFLAGS, TPNOFLAGS);
 */
int __cdecl tmadmin(int cmd, void *arg, int opt, long flags);

#if defined (__cplusplus)
}
#endif

#endif       /* end of _TMADMIN_H  */
