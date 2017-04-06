/*****************************************************************************/
/* Copyright (C) 2005 OSS Nokalva, Inc.  All rights reserved.                */
/*****************************************************************************/
/*****************************************************************************/
/* $Id: biospi.h,v 1.1.1.1 2006/06/06 20:09:05 alek Exp $ 
 *
 * Header for all BioAPI applications. Includes all necessary header files.
 *****************************************************************************/

#ifndef _BIOSPI_H
#define _BIOSPI_H

#include "bioapi_type.h"
#include "bioapi_err.h"

// The following ifdef block allows to build either a BSP DLL that exports the 
// SPI functions or a framework that imports them. The framework should not 
// define the BIOSPI_EXPORTS 

#ifdef BIOSPI_EXPORTS
#define DLLSPI DllExport
#else
#define DLLSPI DllImport
#endif
#include "bioapi_spi.h"

#endif  /* _BIOSPI_H */
