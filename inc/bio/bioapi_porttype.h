/*****************************************************************************/
/* Copyright (C) 2005 OSS Nokalva, Inc.  All rights reserved.                */
/*****************************************************************************/
/*****************************************************************************/
/* $Id: bioapi_porttype.h,v 1.1.1.1 2006/06/06 20:09:05 alek Exp $ 
 *
 * Platform dependant type definitions.
 *****************************************************************************/

#ifndef _BIOAPI_PORTTYPE_H_INCLUDED
#define _BIOAPI_PORTTYPE_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#if defined (WIN32)
#define BioAPI __stdcall
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
// 7.55	BioAPI_PROC_ADDR
typedef FARPROC BioAPI_PROC_ADDR;

#define DllImport       __declspec( dllimport )
#define DllExport       __declspec( dllexport )
#else
#define BioAPI
typedef void (BioAPI *BioAPI_PROC_ADDR) ();

#define DllImport
#define DllExport
#define __declspec( attr )
#define __stdcall
#define IN 
#define OUT
#define OPTIONAL
#endif /* WIN32 */

#ifdef WIN32
/// The separator of entries in the PATH environment variable.
#define PATH_SEPARATOR ';'

#define DIRECTORY_SEPARATOR '\\'
#define DIRECTORY_SEPARATOR_STRING "\\"
#else
#define DIRECTORY_SEPARATOR '/'
#define DIRECTORY_SEPARATOR_STRING "/"
#endif

// C99 types, not all compilers typedef those
typedef unsigned char  uint8_t;
typedef char           sint8_t;
//±è´ëÇü
//typedef char           int8_t;
//typedef char           int8_t;
typedef signed char           int8_t;
typedef unsigned short uint16_t;
typedef short          sint16_t;
typedef short          int16_t;
typedef unsigned int   uint32_t;
typedef int            sint32_t;
typedef int            int32_t;

#ifdef WIN32
typedef  __int64           sint64_t;
typedef unsigned __int64   uint64_t;
#else
typedef  long long         sint64_t;
typedef unsigned long long uint64_t;
#endif

#ifdef __cplusplus
}
#endif

#endif  /* _BIOAPI_PORTTYPE_H_INCLUDED */
