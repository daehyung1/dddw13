/*****************************************************************************/
/* Copyright (C) 2005 OSS Nokalva, Inc.  All rights reserved.                */
/*****************************************************************************/
/*****************************************************************************
 * $Id: bioapi_reg.h,v 1.1.1.1 2006/06/06 20:09:05 alek Exp $
 *****************************************************************************/

#ifndef BIOAPI_REG_H_INCLUDED
#define BIOAPI_REG_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif



//*********************************************************************************
// 10.2 Component registry functions
//
// The following component registry utility functions are provided to ease the
// development of BioAPI compatible applications and BSPs.
// 
// Installation functions are provided so that a BSP or BFP implementer can
// populate the BSP or BFP schema within the component registry. The component
// registry is independent of the operating system.
//*********************************************************************************

// 10.2.1    BioAPI_Util_InstallBSP --------------------------------------------
//    Description
//        This function installs, updates (refreshes), or removes the 
//        references to a BSP in the component registry. In most cases it
//        is the responsibility of the BSP installation program to 
//        allocate the related memory; however, in the case of 
//        *Path and *BspSupportedFormats, the installation program 
//        shall free this memory when it is no longer needed.
//
//        Upon initiation of this function for an install, the BioAPI
//        Framework shall create the BSP schema entry in the component
//        registry and populate it with the content of the input BSP 
//        schema. 
//    
//        Upon initiation of this function for a refresh, the BioAPI
//        Framework shall replace the existing entries for the BSP 
//        schema in the component registry with the content of the input
//        BSP schema, based on the UUID of the BSP within that schema.
//
//        Upon initiation of this function for a deinstallation, the
//        BioAPI Framework shall remove the BSP schema entry in the
//        component registry for the BSP indicated by the BSPId (UUID)
//        within the input schema.
//    Parameters
//        Action (input) – Installation action to be performed. Valid 
//               values are:
//               Value                            Description
//               --------------------------------------------
//               BioAPI_INSTALL_ACTION_INSTALL    Install BSP
//               BioAPI_INSTALL_ACTION_REFRESH    Refresh the information 
//                                                in the component 
//                                                registry.
//               BioAPI_INSTALL_ACTION_UNINSTALL  Uninstall the BSP
//        Error (output) – A pointer to a BioAPI_INSTALL_ERROR 
//              structure. If the function fails, the structure contains 
//              additional information regarding the error state.
//        BSPSchema (input) – A pointer to elements of the BSP 
//              schema (defined in 7.16) describing the features and
//              characteristics of the BSP to be installed. When the 
//              function is called with Action set to 
//              BioAPI_INSTALL_ACTION_UNINSTALL, it is only necessary to 
//              set the BSPUuid element of the BSPSchema parameter.
//    Return Values
//        If the function is successful, it returns BioAPI_OK. If the
//        function fails, it returns a valid BioAPI error code (see
//        clause 11). The parameter Error contains additional error
//        information.

DLLAPI BioAPI_RETURN BioAPI BioAPI_Util_InstallBSP (
    IN BioAPI_INSTALL_ACTION Action,
    OUT BioAPI_INSTALL_ERROR *Error,
    IN const BioAPI_BSP_SCHEMA *BSPSchema);

typedef BioAPI_RETURN (BioAPI *BioAPI_Util_InstallBSP_PTR) (
    IN BioAPI_INSTALL_ACTION Action,
    OUT BioAPI_INSTALL_ERROR *Error,
    IN const BioAPI_BSP_SCHEMA *BSPSchema);


// 10.2.2    BioAPI_Util_InstallBFP --------------------------------------------
//    Description
//        This function installs, updates (refreshes), or removes the
//        entries for a BioAPI BFP in the component registry. In every 
//        case it is the responsibility of the BFP installation program
//        to allocate and release the related memory.
//    Parameters
//        Action (input) – Installation action to be performed. Valid 
//               values are:
//               Value                            Description
//               --------------------------------------------
//               BioAPI_INSTALL_ACTION_INSTALL    Install BSP
//               BioAPI_INSTALL_ACTION_REFRESH    Refresh the information
//                                                in the component 
//                                                registry.
//               BioAPI_INSTALL_ACTION_UNINSTALL  Uninstall the BSP
//        Error (output) – A pointer to a BioAPI_INSTALL_ERROR 
//              structure. If the function fails, the structure contains 
//              additional information regarding the error state.
//        BFPSchema (input) – A pointer to component registry 
//              elements describing the features and characteristics
//              of the BFP to be installed (see clause 7.3). When the
//              function is called with Action set to 
//              BioAPI_INSTALL_ACTION_UNINSTALL, it is only necessary to set
//              the BFPUuid element of the BFPSchema parameter.
//    Return Values
//        If the function is successful, it returns BioAPI_OK. If the
//        function fails, it returns a valid BioAPI error code (see
//        clause 11). The parameter Error contains additional error
//        information.

DLLAPI BioAPI_RETURN BioAPI BioAPI_Util_InstallBFP (
    IN BioAPI_INSTALL_ACTION Action,
    OUT BioAPI_INSTALL_ERROR *Error,
    IN const BioAPI_BFP_SCHEMA *BFPSchema);

typedef BioAPI_RETURN (BioAPI *BioAPI_Util_InstallBFP_PTR) (
    IN BioAPI_INSTALL_ACTION Action,
    OUT BioAPI_INSTALL_ERROR *Error,
    IN const BioAPI_BFP_SCHEMA *BFPSchema);

#ifdef __cplusplus
}
#endif

#endif /* BIOAPI_REG_H_INCLUDED */
