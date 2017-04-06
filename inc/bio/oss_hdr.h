/*****************************************************************************/
/* Copyright (C) 2003-2004 OSS Nokalva, Inc.  All rights reserved.           */
/*****************************************************************************/
/*****************************************************************************
 * $Id: oss_hdr.h,v 1.1.1.1 2006/06/06 20:09:05 alek Exp $
 *
 * Platform dependant type definitions.
 *****************************************************************************/

#ifndef OSS_HDR_H_INCLUDED
#define OSS_HDR_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#if defined (_WIN32)
#define BioAPI __stdcall
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
typedef FARPROC BioAPI_PROC_ADDR;
#else
#define BioAPI
typedef void (BioAPI *BioAPI_PROC_ADDR) ();
#endif /* _WIN32 */

typedef unsigned char	    uint8;
typedef unsigned short	    uint16;
typedef short		    sint16;
typedef unsigned int	    uint32;
typedef int		    sint32;
typedef char		    sint8;

#ifdef _WIN32
typedef __int64		    int64;
typedef unsigned __int64    uint64;
#else
typedef long long	    int64;
typedef unsigned long long  uint64;
#endif

#ifdef __cplusplus
}
#endif

#endif  /* OSS_HDR_H_INCLUDED */
