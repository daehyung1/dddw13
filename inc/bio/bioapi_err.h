/*****************************************************************************/
/* Copyright (C) 2005 OSS Nokalva, Inc.  All rights reserved.                */
/*****************************************************************************/
/*****************************************************************************/
/* $Id: bioapi_err.h,v 1.1.1.1 2006/06/06 20:09:05 alek Exp $ 
 *
 * Defines BioAPI 2.0 error codes.
 *****************************************************************************/

#ifndef _BIOAPIERR_H_
#define _BIOAPIERR_H_
 
//
// 11.2.1   BioAPI Error Value Constants
//
//{ TRACE
// {::NOTE::}
// A different code for BIOAPI_FRAMEWORK_ERROR (e.g. 0x80000000) would be desirable
// so, when omitted, it won't be confused with the framework facility.
//} TRACE
#define BIOAPI_FRAMEWORK_ERROR (0x00000000)
#define BIOAPI_BSP_ERROR       (0x01000000)

// {::NOTE::} the  BIOAPI_UNIT_ERROR is intentionally not used by the BSP code
// because there is no clear guidelines about when this bit has to be set.
// It's possible that it will be removed from future versions of BioAPI.
#define BIOAPI_UNIT_ERROR      (0x02000000)

// {::NOTE::} additional helper macros not defined in the standard
#define ERROR_SOURCE_MASK       (0xFF000000)
#define ERROR_CODE_MASK         (0x00FFFFFF)
#define FRAMEWORK_ERROR(e)      ((e) | BIOAPI_FRAMEWORK_ERROR)
#define BSP_ERROR(e)            ((e) | BIOAPI_BSP_ERROR)
#define ERROR_CODE(e)           ((e) & ERROR_CODE_MASK)


//
// 11.2.2   Implementation-Specific Error Codes
//
// The error codes 0x000000 - 0x0000ff are reserved for implementation-specific usage.
#define BioAPIERR_IMPLEMENTATION_SPECIFIC                   (0x000000FF)

//
// 11.2.3   General Error Codes
//
// General system error indicates that an operating system or internal state 
// error has occurred and the system may not be in a known state.
#define BioAPIERR_INTERNAL_ERROR                            (0x000101)

// A memory error occurred.
#define BioAPIERR_MEMORY_ERROR                              (0x000102)

// An input/output function parameter or input/output field inside of a data 
// structure is an invalid pointer. 
#define BioAPIERR_INVALID_POINTER                           (0x000103)

// An input function parameter or input field in a data structure is an invalid pointer
#define BioAPIERR_INVALID_INPUT_POINTER                     (0x000104)
 
// An output function parameter or output field in a data structure is an invalid pointer
#define BioAPIERR_INVALID_OUTPUT_POINTER                    (0x000105)

// The function is not implemented by the service provider
#define BioAPIERR_FUNCTION_NOT_SUPPORTED                    (0x000106)

// The operating system denied access to a required resource
#define BioAPIERR_OS_ACCESS_DENIED                          (0x000107)

// The function failed for an unknown reason.
#define BioAPIERR_FUNCTION_FAILED                           (0x000108)

// Invalid UUID
#define BioAPIERR_INVALID_UUID                              (0x000109)

// Version incompatibility 
#define BioAPIERR_INCOMPATIBLE_VERSION                      (0x00010a)

// The data in an input parameter is invalid
#define BioAPIERR_INVALID_DATA                              (0x00010b)

// The associated BSP is unable to capture raw samples from the requested device
#define BioAPIERR_UNABLE_TO_CAPTURE                         (0x00010c)
// {::NOTE::} returned for unsupported subtype (not defined in the standard)
#define BioAPIERR_UNSUPPORTED_SUBTYPE                       BioAPIERR_UNABLE_TO_CAPTURE

// The associated BSP has no more space to allocate BIR handles
#define BioAPIERR_TOO_MANY_HANDLES                          (0x00010d)

// The function has been terminated because the timeout value has expired
#define BioAPIERR_TIMEOUT_EXPIRED                           (0x00010e)

// The input BIR is invalid for the purpose required
#define BioAPIERR_INVALID_BIR                               (0x00010f)

//The associated BSP could not validate the signature on the BIR
#define BioAPIERR_BIR_SIGNATURE_FAILURE                     (0x000110)

// The associated BSP is unable to store the payload 
#define BioAPIERR_UNABLE_TO_STORE_PAYLOAD                   (0x000111)
 
// The identify population is NULL
#define BioAPIERR_NO_INPUT_BIRS                             (0x000112)

// The associated BSP does not support the BDB format for the Import function
#define BioAPIERR_UNSUPPORTED_FORMAT                        (0x000113)

// The associated BSP was unable to construct a BIR from the input data
#define BioAPIERR_UNABLE_TO_IMPORT                          (0x000114)

// The purpose recorded in the BIR, and the requested purpose, 
// are inconsistent with the function being performed.
#define BioAPIERR_INCONSISTENT_PURPOSE                      (0x000115)

// The function requires a fully processed BIR.
#define BioAPIERR_BIR_NOT_FULLY_PROCESSED                   (0x000116)

// The BSP does not support the requested purpose.
#define BioAPIERR_PURPOSE_NOT_SUPPORTED                     (0x000117)

// User cancelled operation before completion or timeout
#define BioAPIERR_USER_CANCELLED                            (0x000118)

// BSP (or BioAPI Unit attached to BSP) is currently being used by another biometric application.
#define BioAPIERR_UNIT_IN_USE                               (0x000119)

// The given BSP handle is not valid
#define BioAPIERR_INVALID_BSP_HANDLE                        (0x00011a)
// {::NOTE::} duirng a biometric operation on a specifc session the required 
// unit may not be atached. This error is retuned then  (not defined in the standard)
#define BioAPIERR_REQUIRED_UNIT_NOT_ATTACHED                BioAPIERR_INVALID_BSP_HANDLE

// A function has been called without initializing the BioAPI Framework
#define BioAPIERR_FRAMEWORK_NOT_INITIALIZED                 (0x00011b)

// BIR handle is invalid (does not exist or has been released).
#define BioAPIERR_INVALID_BIR_HANDLE                        (0x00011c)

//The attempted calibration of a sensor unit was not able to be successfully completed.
#define BioAPIERR_CALIBRATION_NOT_SUCCESSFUL                (0x00011d)

// No preset BIR population has been established
#define BioAPIERR_PRESET_BIR_DOES_NOT_EXIST                 (0x00011e)

// The BSP could not decrypt an input BIR (and thus was unable to use it for the requested operation).
#define BioAPIERR_BIR_DECRYPTION_FAILURE                    (0x00011f)


//
// 11.2.4   Component Management Error Codes
//
// A reference to the component file cannot be obtained
#define BioAPIERR_COMPONENT_FILE_REF_NOT_FOUND              (0x000201)

//Framework was unable to successfully load the BSP.
#define BioAPIERR_BSP_LOAD_FAIL                             (0x000202)

// BSP for which an action was requested is not loaded.
#define BioAPIERR_BSP_NOT_LOADED                            (0x000203)

// BioAPI Unit for which an action was requested is not in the inserted state.
#define BioAPIERR_UNIT_NOT_INSERTED                         (0x000204)

// An invalid BioAPI Unit ID was requested
#define BioAPIERR_INVALID_UNIT_ID                           (0x000205)

// An invalid category of BFP or BioAPI Unit was requested
#define BioAPIERR_INVALID_CATEGORY                          (0x000206)

//
// 11.2.5   Database Error Values
//

// Invalid database handle
#define BioAPIERR_INVALID_DB_HANDLE                         (0x000300)

// The associated BSP is unable to open the specified database
#define BioAPIERR_UNABLE_TO_OPEN_DATABASE                   (0x000301)

// The database cannot be opened for the access requested because it is locked
#define BioAPIERR_DATABASE_IS_LOCKED                        (0x000302)

// The specified database does not exist
#define BioAPIERR_DATABASE_DOES_NOT_EXIST                   (0x000303)

// Create failed because the database already exists
#define BioAPIERR_DATABASE_ALREADY_EXISTS                   (0x000304)

// Invalid database name
#define BioAPIERR_INVALID_DATABASE_NAME                     (0x000305)

// No record exists with the requested key
#define BioAPIERR_RECORD_NOT_FOUND                          (0x000306)

// The specified marker handle is invalid
#define BioAPIERR_MARKER_HANDLE_IS_INVALID                  (0x000307)

// The database is already open
#define BioAPIERR_DATABASE_IS_OPEN                          (0x000308)

// Unrecognized access type
#define BioAPIERR_INVALID_ACCESS_REQUEST                    (0x000309)

// End of database has been reached.
#define BioAPIERR_END_OF_DATABASE                           (0x00030a)

// The associated BSP cannot create the database
#define BioAPIERR_UNABLE_TO_CREATE_DATABASE                 (0x00030b)

// The associated BSP cannot close the database
#define BioAPIERR_UNABLE_TO_CLOSE_DATABASE                  (0x00030c)

// The associated BSP cannot delete the database
#define BioAPIERR_UNABLE_TO_DELETE_DATABASE                 (0x00030d)

// The specified database is corrupt
#define BioAPIERR_DATABASE_IS_CORRUPT                       (0x00030e)

//
// 11.2.6.1 General location error codes
// 

// A general location error.
#define BioAPIERR_LOCATION_ERROR                            (0x000400)

// Invalid horizontal or vertical position.
#define BioAPIERR_OUT_OF_FRAME                              (0x000401)

// Invalid crosswise position.
#define BioAPIERR_INVALID_CROSSWISE_POSITION                (0x000402)

// Invalid lengthwise position.
#define BioAPIERR_INVALID_LENGTHWISE_POSITION               (0x000403)

// Invalid distance.
#define BioAPIERR_INVALID_DISTANCE                          (0x000404)

//
// 11.2.6.2 Specific location error codes
//

// The position was too far to the right.
#define BioAPIERR_LOCATION_TOO_RIGHT                        (0x000405)

// The position was too far to the left.
#define BioAPIERR_LOCATION_TOO_LEFT                         (0x000406)

// The position was too high.
#define BioAPIERR_LOCATION_TOO_HIGH                         (0x000407)

// The position was too low.
#define BioAPIERR_LOCATION_TOO_LOW                          (0x000408)

// The position was too far away.
#define BioAPIERR_LOCATION_TOO_FAR                          (0x000409)

// The position was too near (close).
#define BioAPIERR_LOCATION_TOO_NEAR                         (0x00040a)

// The position was too far forward.
#define BioAPIERR_LOCATION_TOO_FORWARD                      (0x00040b)

// The position was too far backward.
#define BioAPIERR_LOCATION_TOO_BACKWARD                     (0x00040c)


//
// 11.2.6.3 Quality Error Codes
// NOTE:  Quality errors can be returned from any function which receives a BioAPI BIR input.

// Sample quality is too poor for the operation to succeed
#define BioAPIERR_QUALITY_ERROR                             (0x000501)


/*******************************************************************
{::NOTE::}

The following errors are not specified by ISO/IEC 19794-1:2005 (BioAPI 2.0).
The Reference Implementation defines these errors as aliases to standard
BioAPI errors.  Future versions of the Reference Implementation may specify
different values for these errors.

/*******************************************************************/

// Internal error. Attempt to use the component that internal initialization has
// failed or while the component is being destroyed.
#define BioAPIERR_COMPONENT_STATE_IS_CORRUPT            BioAPIERR_INTERNAL_ERROR

// Internal error. Orphaned attachment entry was detected.
#define BioAPIERR_ORPHANED_ATTACHMENT                   BioAPIERR_INVALID_BSP_HANDLE

// Internal error. Failure when freeing memory and/or synchronization objects.
#define BioAPIERR_UNABLE_TO_FREE_RESOURCES              BioAPIERR_INTERNAL_ERROR

// Time out when serializing access to the framework. One of possible reasons
// of the error is the deadlock condition.
#define BioAPIERR_ACCESS_DENIED                         BioAPIERR_INTERNAL_ERROR

// Attempt to load the component registry has failed.
#define BioAPIERR_UNABLE_TO_LOAD_CRDS                   BioAPIERR_FUNCTION_FAILED

// Time out when serializing access to the list of units. One of possible
// reasons of the error is the deadlock condition.
#define BioAPIERR_UNIT_LIST_ACCESS_DENIED               BioAPIERR_INTERNAL_ERROR

// Internal error. Unable to add new entry to the list of units. 
#define BioAPIERR_UNABLE_TO_ADD_UNIT                    BioAPIERR_MEMORY_ERROR

// Internal error. Unable to remove the entry from the list of units.
#define BioAPIERR_UNABLE_TO_REMOVE_UNIT                 BioAPIERR_INVALID_UNIT_ID

// Time out when serializing access to the CRDS. One of possible reasons of
// the error is the deadlock condition.
#define BioAPIERR_CRDS_ACCESS_DENIED                    BioAPIERR_INTERNAL_ERROR

// Time out when serializing access to the BSP table. One of possible reasons
// of the error is the deadlock condition.
#define BioAPIERR_BSP_TABLE_ACCESS_DENIED               BioAPIERR_INTERNAL_ERROR

// Time out when serializing access to the attachment table. One of possible
// reasons of the error is the deadlock condition.
#define BioAPIERR_ATTACHMENT_TABLE_ACCESS_DENIED        BioAPIERR_INTERNAL_ERROR

// Time out when serializing access to the BSP. One of possible reasons of
// the error is the deadlock condition.
#define BioAPIERR_BSP_ACCESS_DENIED                     BioAPIERR_INTERNAL_ERROR

// Time out when serializing access to the attachment entry. One of possible
// reasons of the error is the deadlock condition.
#define BioAPIERR_SESSION_ACCESS_DENIED                 BioAPIERR_INTERNAL_ERROR

// Attempt to install/refresh or uninstall component registry or framework when the framework is in use.
#define BioAPIERR_FRAMEWORK_IS_IN_USE                   BioAPIERR_OS_ACCESS_DENIED

// CRDS specific error codes returned by component registry functions
// BioAPI_InstallBSP/BFP.

// Generic failure when opening the component registry database.
#define BioAPIERR_UNABLE_TO_OPEN_CRDS                   BioAPIERR_FUNCTION_FAILED
// Needs standartized error code

// The operation has failed due to the component registry database is locked by another process.
#define BioAPIERR_CRDS_IS_LOCKED                        BioAPIERR_OS_ACCESS_DENIED

// The component registry database does not exist.
#define BioAPIERR_CRDS_DOES_NOT_EXIST                   BioAPIERR_FUNCTION_FAILED
// Needs standartized error code

// The creation of the component registry database has failed because the database exists.
#define BioAPIERR_CRDS_ALREADY_EXISTS                   BioAPIERR_FUNCTION_FAILED

// The record for the framework, BSP of BFP with the requested UUID does not exist.
#define BioAPIERR_RECORD_NOT_FOUND_IN_CRDS              BioAPIERR_FUNCTION_FAILED
// Needs standartized error code

// The record for the framework, BSP of BFP with the requested UUID already exists.
#define BioAPIERR_RECORD_ALREADY_EXISTS_IN_CRDS         BioAPIERR_FUNCTION_FAILED
// Needs standartized error code

// Generic failure when attempting to create the component registry database.
#define BioAPIERR_UNABLE_TO_CREATE_CRDS                 BioAPIERR_FUNCTION_FAILED

// Generic failure when attempting to delete the component registry database.
#define BioAPIERR_UNABLE_TO_DELETE_CRDS                 BioAPIERR_FUNCTION_FAILED

// The component registry database is corrupt.
#define BioAPIERR_CRDS_IS_CORRUPT                       BioAPIERR_FUNCTION_FAILED
// Needs standartized error code

// Internal error. The operation cannot be performed because the component registry is closed.
#define BioAPIERR_CRDS_IS_CLOSED                        BioAPIERR_INTERNAL_ERROR

// Internal error. The operation cannot be performed because the component registry is open.
#define BioAPIERR_CRDS_IS_OPEN                          BioAPIERR_INTERNAL_ERROR

#endif /* _BIOAPIERR_H_ */
