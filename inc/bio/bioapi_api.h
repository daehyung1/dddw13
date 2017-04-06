/*****************************************************************************/
/* Copyright (C) 2005 OSS Nokalva, Inc.  All rights reserved.                */
/*****************************************************************************/
/*****************************************************************************/
/* $Id: bioapi_api.h,v 1.1.1.1 2006/06/06 20:09:05 alek Exp $ 
 *
 * Defined BioAPI 2.0 calls between applications and the framework
 *****************************************************************************/

#ifndef _BIOAPI_API_H_INCLUDED
#define _BIOAPI_API_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
// 8.1  Component Management Functions
// 
// The following functions are handled by the BioAPI Framework component. Some 
// are handled internally and others are passed through to a BSP via the SPI.
// Return value BioAPI_RETURN in all of them indicates success or specifying 
// a particular error condition. The value BioAPI_OK indicates success. 
// All other values represent an error condition.
//*****************************************************************************

/**
    \par 8.1.1 BioAPI_Init

    This function initializes the BioAPI Framework and verifies that the 
    version of the BioAPI Framework expected by the application is compatible 
    with the version of the BioAPI Framework on the system. This function 
    should be called at least once by the application.

    Any call to BioAPI_Init which occurs while there are previous calls to 
    BioAPI_Init that have not been followed by a corresponding call to 
    BioAPI_Terminate will be handled as follows: The BioAPI Framework will 
    respond with either BioAPI_OK (if and only if the handling of the proposed 
    version number by the framework is compatible with the handling of the 
    version number that was proposed by the previous Init) or 
    BioAPIERR_INCOMPATIBLE_VERSION, but will not reinitialize. A count of the 
    number of successful BioAPI_Inits will be maintained by the Framework, 
    which will not terminate until a corresponding number of BioAPI Terminates 
    have been issued.

    This function is handled internally within the BioAPI Framework and is not 
    passed through to a BSP.

    @param[in] Version
        a pointer to the major and minor version number of the BioAPI 
        specification that the biometric application is compatible with.

    @return 
            A BioAPI_RETURN value indicating success or specifying a particular
        error condition. The value BioAPI_OK indicates success. All other 
        values represent an error condition.

    \par Errors:
        BioAPIERR_INCOMPATIBLE_VERSION
*/    

    DLLAPI BioAPI_RETURN BioAPI BioAPI_Init (
    IN BioAPI_VERSION Version);
 
typedef BioAPI_RETURN (BioAPI *BioAPI_Init_PTR) (
    IN BioAPI_VERSION Version);

 
/**
    \par 8.1.2 BioAPI_Terminate

    This function terminates a biometric application's use of the BioAPI 
    Framework. The Framework can cleanup all internal state associated with 
    the calling application. This function shall only be called if there is 
    at least one successful call to BioAPI_Init for which a corresponding call 
    to this function has not yet been made. BioAPI_Terminate shall not perform 
    any actions if there are any outstanding calls to BioAPI_Init (i.e., calls 
    to BioAPI_Init that have not been followed by corresponding calls to 
    BioAPI_Terminate).

    This function should not be called by the application if there is a call 
    to BioAPI_BSPLoad for which a corresponding call to BioAPI_BSPUnload (for 
    a given BSP UUID) has not yet been made. However, should this function be 
    called while there are still BSPs loaded, then for each call to 
    BioAPI_BSPLoad without a corresponding call to BioAPI_BSPUnload, the 
    actions relative to the missing corresponding call to BioAPI_BSPUnload 
    shall be implicitly performed by the Framework (as though the 
    corresponding function had been called at that time), followed by the 
    actions relative to BioAPI_Terminate (i.e, the Framework shall unload any 
    BSPs prior to terminating).

    This function is handled internally within the BioAPI Framework and is not 
    passed through to a BSP, except where a BioAPI_BSPUnload is implied, as 
    specified above.

    @return
        A BioAPI_RETURN value indicating success or specifying a particular 
        error condition. The value BioAPI_OK indicates success. All other 
        values represent an error condition.

    @note 
        A BioAPI_Terminate operation is typically not expected to fail; 
        however, should an anomally condition occur, the application is 
        not required to take any further action.
*/

DLLAPI BioAPI_RETURN BioAPI BioAPI_Terminate (void);

typedef BioAPI_RETURN (BioAPI *BioAPI_Terminate_PTR) (void);
 
  
/**
    \par 8.1.3 BioAPI_GetFrameworkInfo

    This function returns information about the BioAPI framework itself. Since 
    multiple frameworks may exist on a computer, applications will need 
    information about them in order to choose the one to use.

    @param[out] FrameworkSchema
        A pointer to memory where the schema information will be returned.

    @return
        A BioAPI_RETURN value indicating success or specifying a particular 
        error condition. The value BioAPI_OK indicates success. All other 
        values represent an error condition.
*/

DLLAPI BioAPI_RETURN BioAPI BioAPI_GetFrameworkInfo (
    OUT BioAPI_FRAMEWORK_SCHEMA *FrameworkSchema);

typedef BioAPI_RETURN (BioAPI *BioAPI_GetFrameworkInfo_PTR) (
    OUT BioAPI_FRAMEWORK_SCHEMA *FrameworkSchema);

 
/**
    \par 8.1.4 BioAPI_EnumBSPs

    This function provides information about all BSPs currently installed in 
    the component registry. It performs the following actions (in order):

    -# allocates a memory block large enough to contain an array of elements 
       of type BioAPI_BSP_SCHEMA with as many elements as the number of 
       installed BSPs;
    -# fills the array with the BSP schemas of all installed BSPs; and
    -# returns the address of the array in the BspSchemaArray parameter and 
       the number of elements of the array in the NumberOfElements parameter.

    This function shall only be called if there is at least one call to 
    BioAPI_Init for which a corresponding call to BioAPI_Terminate has not yet 
    been made.

    This function is handled internally within the BioAPI Framework and is not 
    passed through to any BSP. The memory block containing the array shall 
    be freed by the application via a call to BioAPI_Free (see clause 8.7.2) 
    when it is no longer needed by the application. The memory block pointed 
    to by the Path member within each element of the array shall also be 
    freed by the application via a call to BioAPI_Free when it is no longer 
    needed by the application.

    @param[out] BSPSchemaArray
        A pointer to the address of the array of elements of the type 
        BioAPI_BSP_SCHEMA (allocated by the framework) containing the BSP
        schema information.

    @param[out] NumberOfElements
        A pointer to the number of elements of the array (which is also the 
        number of BSP schemas in the component registry).

    @return
        A BioAPI_RETURN value indicating success or specifying a particular 
        error condition. The value BioAPI_OK indicates success. All other 
        values represent an error condition.
*/

DLLAPI BioAPI_RETURN BioAPI BioAPI_EnumBSPs (
    OUT BioAPI_BSP_SCHEMA **BSPSchemaArray,
    OUT uint32_t *NumberOfElements);


typedef BioAPI_RETURN (BioAPI *BioAPI_EnumBSPs_PTR) (
    OUT BioAPI_BSP_SCHEMA **BSPSchemaArray,
    OUT uint32_t *NumberOfElements);

 
/**
    \par 8.1.5 BioAPI_BSPLoad

    This function initializes a BSP using the BioSPI_BSPLoad (see clause 
    9.3.1.1). Initialization includes registering the application’s event 
    handler for the specified BSP and enabling all events. The application can 
    choose to provide an event handler function to receive notification of 
    events. Many applications can independently and concurrently load the same 
    BSP, and each application can establish its own event handler.

    They will all receive notification of an event. The same or different event
    handlers can be used if an application loads multiple BSPs.

    An application may establish as many event handlers as it wishes, for a 
    given BSP, by calling BioAPI_BSPLoad one or more times for that BSP. An 
    event handler is identified by a combination of address and context.

    When an event occurs in a BSP, the BSP may send an event notification to 
    the Framework by calling the Framework's event handler.

    When the Framework receives an event notification from a BSP, it shall 
    send one notification to each event handler established by each application
    for which that event notification is enabled for that BSP. Therefore, a
    single event notification callback made from a BSP to the Framework may 
    result in zero or more callbacks made by the Framework to zero or more 
    applications.

    When the framework receives an event notification from a BSP, it shall 
    call all the event handlers established by each application for that BSP. 
    If an application has set up multiple event handlers, they shall be called
    one at a time (in any order chosen by the Framework) rather than 
    concurrently.

    Event notification may occur at any time, either during a BioAPI call 
    (related or unrelated to the event) or while there is no BioAPI call in 
    execution. Application writers should ensure that all callbacks are 
    properly and safely handled by the application, no matter when the 
    application receives them.

    NOTE: This usually requires the use of thread synchronization techniques 
    and discipline in the actions performed by the application code placed in 
    event handlers.

    There is a “use count?on the establishment of event handlers; they have 
    to be de-established (by BSPUnload) as many times as they were established.
    When a BSP is loaded (BSPLoad), it shall raise an “insert?event 
    immediately for each present BioAPI Unit. This will indicate to the 
    biometric application that it can go ahead and do a BSPAttach. If the 
    hardware component for a specific functionality is not present, the 
    “insert?event cannot be raised until the hardware component has been 
    plugged in.

    This function shall only be called if there is at least one call to 
    BioAPI_Init for which a corresponding call to BioAPI_Terminate has not 
    yet been made. The function BioAPI_BSPAttach can be invoked multiple times 
    for each call to BioAPI_BSPLoad.

    The BioAPI_BSPLoad function is not to be called unless the BSP has been 
    installed using BioAPI_BSPInstall. A determination of installed BSPs can 
    be made through a call to BioAPI_EnumBSPs.

    @param[in] BSPUuid
        the UUID of the BSP selected for loading.

    @param[in] AppNotifyCallback (optional)
        the event notification function provided by the caller. This defines
        the callback for event notifications from the loaded (and later
        attached) service provider.

    @param[in] AppNotifyCallbackCtx (optional)
        when the selected service provider raises an event, this context is
        passed as an input to the event handler specified by AppNotifyCallback.

    @return
        A BioAPI_RETURN value indicating success or specifying a particular
        error condition. The value BioAPI_OK indicates success. All other 
        values represent an error condition.

    \par Errors:
        BioAPIERR_BSP_LOAD_FAIL \n
        BioAPIERR_INVALID_UUID
*/

DLLAPI BioAPI_RETURN BioAPI BioAPI_BSPLoad (
    IN const BioAPI_UUID *BSPUuid,
    IN OPTIONAL BioAPI_EventHandler AppNotifyCallback,
    IN OPTIONAL void *AppNotifyCallbackCtx);


typedef BioAPI_RETURN (BioAPI *BioAPI_BSPLoad_PTR) (
    IN const BioAPI_UUID *BSPUuid,
    IN OPTIONAL BioAPI_EventHandler AppNotifyCallback,
    IN OPTIONAL void *AppNotifyCallbackCtx);



/**
    \par 8.1.6 BioAPI_BSPUnload

    The function de-registers event notification callbacks for the caller 
    identified by BSPUuid.

    BioAPI_BSPUnload is the analogue call to BioAPI_BSPLoad. If all callbacks 
    registered with BioAPI are removed, then BioAPI unloads (for that 
    biometric application) the BSP that was loaded by calls to BioAPI_BSPLoad.

    The BioAPI uses the three input parameters; BSPUuid, AppNotifyCallback, 
    and AppNotifyCallbackCtx to uniquely identify registered callbacks.

    This function shall only be called (for a given BSP UUID) if there is at 
    least one call to BioAPI_BSPLoad (for that BSP UUID) for which a 
    corresponding call to this function has not yet been made.
                
    This function should not be called by the application if there is a call 
    to BioAPI_BSPAttach for which a corresponding call to BioAPI_BSPDetach 
    (for a given BSP handle) has not yet been made. However, should this 
    function be called while the BSP is still attached, then for each call to 
    BioAPI_BSPAttach without a corresponding call to BioAPI_BSPDetach, the 
    actions relative to the missing corresponding call to BioAPI_BSPDetach 
    shall be implicitly performed by the BioAPI Framework (as though the 
    corresponding function had been called at that time), followed by the 
    actions relative to BioAPI_BSPUnload, (i.e., the Framework will detach the 
    BSP prior to unloading it).

    This includes the case in which the actions relative to a missing call to 
    BioAPI_BSPUnload are implicitly performed by the BioAPI Framework during a 
    call to BioAPI_Terminate (see clause 8.1.2).

    @param[in] BSPUuid
        the UUID of the BSP selected for unloading.

    @param[in] AppNotifyCallback (optional)
        the event notification function to be deregistered. The function shall
        have been provided by the caller in BioAPI_BSPLoad.

    @param[in] AppNotifyCallbackCtx (optional)
        the event notification context that was provided in the corresponding
        call to BioAPI_BSPLoad.

    @return
        A BioAPI_RETURN value indicating success or specifying a particular 
        error condition. The value BioAPI_OK indicates success. All other 
        values represent an error condition.

    \par Errors:
        BioAPIERR_INVALID_UUID \n
        BioAPIERR_BSP_NOT_LOADED
*/

DLLAPI BioAPI_RETURN BioAPI BioAPI_BSPUnload (
    IN const BioAPI_UUID *BSPUuid,
    IN OPTIONAL BioAPI_EventHandler AppNotifyCallback,
    IN OPTIONAL void *AppNotifyCallbackCtx);


typedef BioAPI_RETURN (BioAPI *BioAPI_BSPUnload_PTR) (
    IN const BioAPI_UUID *BSPUuid,
    IN OPTIONAL BioAPI_EventHandler AppNotifyCallback,
    IN OPTIONAL void *AppNotifyCallbackCtx);

 
/**
    \par 8.1.7 BioAPI_BSPAttach

    This function initiates a BSP attach session and verifies that the version
    of the BSP expected by the application is compatible with the version on 
    the system. The caller shall specify a list of zero or more BioAPI Units(s)
    that the BSP is to use in the attach session being created.

    This function shall only be called (for a given BSP UUID) if there is at 
    least one call to BioAPI_BSPLoad (for that BSP UUID) for which a 
    corresponding call to BioAPI_BSPUnload has not yet been made. The function 
    BioAPI_BSPAttach can be invoked multiple times for each call to 
    BioAPI_BSPLoad (prior to a call to BioAPI_BSPUnload), for the same BSP, 
    creating multiple invocations of that BSP.

    @param[in] BSPUuid
        a pointer to the UUID structure containing the global unique
        identifier for the BSP.

    @param[in] Version
        the major and minor version number of the BioAPI specification that
        the application is expecting the BSP to support. The BSP shall
        determine whether it is compatible with the required version.

    @param[in] UnitList
        a pointer to a buffer containing a list of BioAPI_UNIT_LIST_ELEMENT
        structures indicating to the BSP which BioAPI Units (supported by the
        BSP) it is to use for this attach session. The structures contain the
        ID and category of each BioAPI Unit. The application may specify one
        of the following for each category of BioAPI Unit:
        -# Select a specific BioAPI Unit: To specify a particular BioAPI Unit 
           to use for this attach session, the ID and category of that BioAPI 
           Unit will be provided for that element.
        -# Select any BioAPI Unit: When the UnitID is set to BioAPI_DONT_CARE
           in a particular element, the BSP will choose which BioAPI Unit of 
           that category to use, or will give an error return if it does not 
           support any BioAPI Units of that category. If a particular category
           is not listed, the BSP will likewise choose a BioAPI Unit of that 
           category to use if it supports a BioAPI Unit of that category 
           (however, there is no error return if it does not).
        -# Select no BioAPI Unit: When the UnitID is set to 0xFFFFFFFF the BSP
           will explicitly not attach a BioAPI Unit of the given category, even
           if it supports one of that category.  NOTE: Any subsequent calls 
           requiring use of a BioAPI Unit of this category will fail with an
           error return.

    @param[in] NumUnits
        The number of BioAPI Unit elements in the list that the pointer
        UnitList is pointing to. If this parameter contains ?? the BSP
        selects the BioAPI Unit for all categories of BioAPI Units that the BSP
        manages directly or indirectly. NOTE: Only one BioAPI Unit of each
        category can be attached by a biometric application for each BSP attach
        session at any time.

    @param[out] NewBSPHandle
        a new handle that can be used to interact with the requested service
        provider. The value will be set to 
        BioAPIERR_FRAMEWORK_INVALID_BSP_HANDLE if the function fails.

    @return
        A BioAPI_RETURN value indicating success or specifying a particular 
        error condition. The value BioAPI_OK indicates success. All other 
        values represent an error condition.

    \par Errors:
        BioAPIERR_INCOMPATIBLE_VERSION \n
        BioAPIERR_BSP_NOT_LOADED \n
        BioAPIERR_INVALID UNIT_ID \n
        BioAPIERR_INVALID_UUID \n
        BioAPIERR_UNIT_IN_USE \n
        BioAPIERR_INVALID_CATEGORY
*/

DLLAPI BioAPI_RETURN BioAPI BioAPI_BSPAttach (
    IN const BioAPI_UUID *BSPUuid,
    IN BioAPI_VERSION Version, 
    IN const BioAPI_UNIT_LIST_ELEMENT *UnitList,
    IN uint32_t NumUnits,
    OUT BioAPI_HANDLE *NewBSPHandle);


typedef BioAPI_RETURN (BioAPI *BioAPI_BSPAttach_PTR) (
    IN const BioAPI_UUID *BSPUuid,
    IN BioAPI_VERSION Version, 
    IN const BioAPI_UNIT_LIST_ELEMENT *UnitList,
    IN uint32_t NumUnits,
    OUT BioAPI_HANDLE *NewBSPHandle);


/**
    \par 8.1.8 BioAPI_BSPDetach

    This function detaches the biometric application from the BSP invocation.
    At this time, all BSP allocated resources associated with the BSP attach 
    session shall be freed or released or invalidated. This is especially 
    important for BIR, BSP, and database handles. At this time, all set 
    callbacks associated with the BSP attach session shall become invalid.

    This function shall only be called after BioAPI_BSPAttach has been called,
    and shall not be called more than once for the same BSP handle created by
    the call to BioAPI_BSPAttach.

    @param[in] BSPHandle
        the handle that identifies the attach session.

    @return
        A BioAPI_RETURN value indicating success or specifying a particular 
        error condition. The value BioAPI_OK indicates success. All other 
        values represent an error condition.

    \par Errors:
        BioAPIERR_INVALID_BSP_HANDLE
*/

DLLAPI BioAPI_RETURN BioAPI BioAPI_BSPDetach (
    IN BioAPI_HANDLE BSPHandle);


typedef BioAPI_RETURN (BioAPI *BioAPI_BSPDetach_PTR) (
    IN BioAPI_HANDLE BSPHandle);

 
/**
    \par 8.1.9 BioAPI_QueryUnits

    This function provides information about all BioAPI units that are managed
    directly or indirectly by the BSP identified by the given BSP UUID and are
    currently in the inserted state. It performs the following actions (in 
    order):
    -# determines the set of BioAPI units that are managed directly or 
       indirectly by the BSP and are currently in the inserted state;
    -# allocates a memory block large enough to contain an array of elements
       of type BioAPI_UNIT_SCHEMA with as many elements as the number of 
       BioAPI units determined in (a);
    -# fills the array with the unit schemas of all BioAPI units determined in
       (a); and
    -# returns the address of the array in the UnitSchemaArray parameter and
       the size of the array in the NumberOfElements parameter.

    NOTE: When the Framework calls the function BioSPI_QueryUnits of a BSP, the
    BSP allocates memory for the data to be returned to the Framework. In some
    implementation architectures, the Framework will simply pass to the 
    application the data and the addresses exactly as returned by the BSP 
    because the application will interpret the addresses in the same way as 
    the BSP and will be able to access the data that the BSP has placed at 
    those addresses. In other implementation architectures, the framework 
    will need to move all the data returned by the BSP to newly allocated 
    memory blocks accessible to the application, and will call BioSPI_Free
    after copying each memory block but before returning from the 
    BioAPI_QueryUnits call. In the former case, when the application calls
    BioAPI_Free, the Framework will make a corresponding call to BioSPI_Free.
    In the latter case, the calls to BioAPI_Free will be handled internally 
    by the framework. However, such differences in the behavior of the 
    Framework are not visible to the application. The memory block containing
    the array shall be freed by the application via a call to BioAPI_Free 
    (see clause 8.7.2) when it is no longer needed by the application. The 
    memory block pointed to by the UnitProperty member within each element 
    of the array shall also be freed by the application via a call to 
    BioAPI_Free when it is no longer needed by the application.

    This function shall only be called after BioAPI_Load has been called for
    the specified BSP, and shall not be called after BioAPI_Unload has been 
    called for the BSP.

    @param[in] BSPUuid
        The unique identifier for the BSP for which the unit information is to
        be returned.

    @param[out] UnitSchemaArray
        A pointer to the address of the array of elements of type 
        BioAPI_UNIT_SCHEMA (allocated by the BSP - but see note above) 
        containing the unit schema information.

    @param[out] NumberOfElements
        A pointer to the number of elements in the array.

    @return
        A BioAPI_RETURN value indicating success or specifying a particular
        error condition. The value BioAPI_OK indicates success. All other 
        values represent an error condition.

    \par Errors:
        BioAPIERR_BSP_NOT_LOADED \n
        BioAPIERR_INVALID_UUID
*/

DLLAPI BioAPI_RETURN BioAPI BioAPI_QueryUnits (
    IN const BioAPI_UUID *BSPUuid,
    OUT BioAPI_UNIT_SCHEMA  **UnitSchemaArray,
    OUT uint32_t *NumberOfElements);


typedef BioAPI_RETURN (BioAPI *BioAPI_QueryUnits_PTR) (
    IN const BioAPI_UUID *BSPUuid,
    OUT BioAPI_UNIT_SCHEMA  **UnitSchemaArray,
    OUT uint32_t *NumberOfElements);

 
/**
    \par 8.1.10 BioAPI_EnumBFPs

    This function provides information about all BFPs currently installed in 
    the component registry. It performs the following actions (in order):

    -# allocates a memory block large enough to contain an array of elements
       of type BioAPI_BFP_SCHEMA with as many elements as the number of 
       installed BFPs;
    -# fills the array with the BFP schemas of all installed BFPs; and
    -# returns the address of the array in the BfpSchemaArray parameter and 
       the number of elements of the array in the NumberOfElements parameter.

    This function shall only be called if there is at least one call to 
    BioAPI_Init for which a corresponding call to BioAPI_Terminate has not yet
    been made.

    This function is handled internally within the BioAPI Framework and is 
    not passed through to any BSP. The memory block containing the array 
    shall be freed by the application via a call to BioAPI_Free (see clause 
    8.7.2) when it is no longer needed by the application.

    The memory blocks pointed to by the Path and BFPProperty members within
    each element of the array shall also be freed by the application via a 
    call to BioAPI_Free when they are no longer needed by the application.

    @param[out] BFPSchemaArray
        A pointer to the address of the array of elements of type
        BioAPI_BFP_SCHEMA (allocated by the framework) containing the BFP
        schema information.

    @param[out] NumberOfElements
        A pointer to the number of elements of the array (which is also the
        number of BFP schemas in the component registry).

    @return
        A BioAPI_RETURN value indicating success or specifying a particular
        error condition. The value BioAPI_OK indicates success. All other 
        values represent an error condition.
*/

DLLAPI BioAPI_RETURN BioAPI BioAPI_EnumBFPs (
    OUT BioAPI_BFP_SCHEMA **BFPSchemaArray,
    OUT uint32_t *NumberOfElements);

typedef BioAPI_RETURN ( BioAPI *BioAPI_EnumBFPs_PTR) (
    OUT BioAPI_BFP_SCHEMA **BFPSchemaArray,
    OUT uint32_t *NumberOfElements);

 
/**
    \par 8.1.11 BioAPI_QueryBFPs

    This function returns a list of BFPs which are currently installed in the
    component registry and supported by the BSP identified by the given BSP 
    handle. It performs the following actions (in order):

    -# determines which among all currently installed BFPs are supported by 
       the BSP;
    -# allocates a memory block large enough to contain an array of elements
       of type BioAPI_BFP_LIST_ELEMENT with as many elements as the number of
       BFPs determined in (a);
    -# fills the array with identification information (category and UUID) 
       about the BFPs determined in (a); and
    -# returns the address of the array in the BFPList parameter and the 
       number of elements of the array in the NumberOfElements parameter.

    NOTE: When the Framework calls the function BioSPI_QueryBFPs of a BSP, 
    the BSP allocates memory for the data to be returned to the Framework. In
    some implementation architectures, the Framework will simply pass to the 
    application the data and the addresses exactly as returned by the BSP 
    because the application will interpret the addresses in the same way as 
    the BSP and will be able to access the data that the BSP has placed at 
    those addresses. In other implementation architectures, the framework will
    need to move all the data returned by the BSP to newly allocated memory
    blocks accessible to the application, and call BioSPI_Free after copying
    each memory block but before returning from the BioAPI_QueryBFPs call. In
    the former case, when the application calls BioAPI_Free, the Framework will
    make a corresponding call to BioSPI_Free. In the latter case, the calls to
    BioAPI_Free will be handled internally by the framework. However, such 
    differences in the behavior of the Framework are not visible to the 
    application.

    Additional information about the supported BFPs can be retrieved by 
    calling BioAPI_EnumBFPs and analyzing the BfpSchemaArray at the matching
    BfpUuids.

    This function shall only be called after BioAPI_BSPAttach has been called,
    and shall not be called after BioAPI_BSPDetach has been called for the 
    BSP handle created by the call to BioAPI_BSPAttach.

    The memory block containing the array shall be freed by the application 
    via a call to BioAPI_Free (see clause 8.7.2) when it is no longer needed 
    by the application.

    @param[in] BSPUuid
        The unique identifier for the BSP for which the unit information is to
        be returned.

    @param[out] BFPList
        A pointer to the address of the array of elements of type
        BioAPI_BFP_LIST_ELEMENT (allocated by the BSP - but see note above) a
        buffer containing the BFP identification information.

    @param[out] NumberOfElements
        A pointer to the number of elements in the array.

    @return
        A BioAPI_RETURN value indicating success or specifying a particular
        error condition. The value BioAPI_OK indicates success. All other 
        values represent an error condition.

    \par Errors:
        <br>BioAPIERR_INVALID_BSP_HANDLE
*/        
    
DLLAPI BioAPI_RETURN BioAPI BioAPI_QueryBFPs (
    IN const BioAPI_UUID  *BSPUuid,
    OUT BioAPI_BFP_LIST_ELEMENT **BFPList,
    OUT uint32_t *NumberOfElements);


typedef BioAPI_RETURN (BioAPI *BioAPI_QueryBFPs_PTR) (
    IN const BioAPI_UUID  *BSPUuid,
    OUT BioAPI_BFP_LIST_ELEMENT **BFPList,
    OUT uint32_t *NumberOfElements);

 
/**
    \par 8.1.12 BioAPI_ControlUnit

    This function sends control data from the application to the BioAPI Unit
    and receives status or operation data from there. The content of the 
    ControlCode, the send (input) data, and the receive (output) data will be
    specified in the related interface specification for this BioAPI Unit 
    (or associated FPI, if present).

    @param[in] BSPHandle
        The handle of the attached BioAPI service provider.

    @param[in] UnitId
        ID of the BioAPI Unit.

    @param[in] ControlCode
        The function code in the BioAPI Unit to be called.

    @param[in] InputData
        Address and length of a buffer containing the data to be sent to the
        BioAPI Unit related to the given ControlCode.

    @param[out] OutputData
        Pointer to a BioAPI_DATA structure.  On output, this shall contain
        the address and length of a data buffer containing the data received
        from the BioAPI Unit after processing the function indicated by the
        ControlCode. If no memory block has been allocated by the function,
        the address shall be set to NULL and the length shall be set to
        zero.

    @return
        A BioAPI_RETURN value indicating success or specifying a particular
        error condition. The value BioAPI_OK indicates success. All other
        values represent an error condition.

    \par Errors:
        BioAPIERR_BIOAPI_UNIT_NOT_INSERTED \n
        BioAPIERR_INVALID_UNIT_ID \n
        BioAPIERR_UNIT_IN_USE \n
        BioAPIERR_INVALID_BSP_HANDLE
*/        

DLLAPI BioAPI_RETURN BioAPI BioAPI_ControlUnit (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_UNIT_ID UnitID,
    IN uint32_t ControlCode,
    IN const BioAPI_DATA *InputData,
    OUT BioAPI_DATA *OutputData);


typedef BioAPI_RETURN (BioAPI *BioAPI_ControlUnit_PTR) (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_UNIT_ID UnitID,
    IN uint32_t ControlCode,
    IN const BioAPI_DATA *InputData,
    OUT BioAPI_DATA *OutputData);


//*****************************************************************************
// 8.2  BIR Handle Operations
//*****************************************************************************

/**
    \par 8.2.1 BioAPI_FreeBIRHandle

    This function frees the memory and resources associated with the specified
    BIR Handle. The associated BIR is no longer referenceable through that
    handle. If necessary, the biometric application can store the BIR into a 
    BSP-controlled BIR database (using BioAPI_DbStoreBIR) before calling
    BioAPI_FreeBIRHandle.

    Alternatively, the application can call BioAPI_GetBIRFromHandle (which will
    retrieve the BIR and free the handle) instead of calling 
    BioAPI_FreeBIRHandle.

    This function shall only be called after BioAPI_BSPAttach has been called,
    and shall not be called after BioAPI_BSPDetach has been called for the BSP
    handle created by the call to BioAPI_BSPAttach.

    @param[in] BSPHandle
        The handle of an attached BSP.

    @param[in] Handle
        The BIR handle to be freed.

    @return
        A BioAPI_RETURN value indicating success or specifying a particular
        error condition. The value BioAPI_OK indicates success. All other
        values represent an error condition.

    \par Errors:
        BioAPIERR_INVALID_BIR_HANDLE \n
        BioAPIERR_INVALID_BSP_HANDLE
*/

DLLAPI BioAPI_RETURN BioAPI BioAPI_FreeBIRHandle (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_BIR_HANDLE   Handle); 


typedef BioAPI_RETURN (BioAPI *BioAPI_FreeBIRHandle_PTR) (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_BIR_HANDLE   Handle); 


/**
    \par 8.2.2 BioAPI_GetBIRFromHandle

    This function returns the BIR associated with a BIR handle returned by a
    BSP. The referenced BSP allocates the storage for both the retrieved BIR
    structure and its data members. The BIR handle is freed by the BSP before
    the function returns.

    @param[in] BSPHandle
        The handle of the attached BioAPI service provider.

    @param[in] Handle
        The handle of the BIR to be retrieved.

    @param[out] BIR
        Pointer to the retrieved BIR.

    @return
        A BioAPI_RETURN value indicating success or specifying a particular
        error condition. The value BioAPI_OK indicates success. All other
        values represent an error condition.

    \par Errors:
        BioAPIERR_INVALID_BIR_HANDLE \n
        BioAPIERR_INVALID_BSP_HANDLE
*/

DLLAPI BioAPI_RETURN BioAPI BioAPI_GetBIRFromHandle (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_BIR_HANDLE   Handle,
    OUT BioAPI_BIR *BIR); 


typedef BioAPI_RETURN (BioAPI *BioAPI_GetBIRFromHandle_PTR) (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_BIR_HANDLE   Handle,
    OUT BioAPI_BIR *BIR); 

/**
    \par 8.2.3 BioAPI_GetHeaderFromHandle

    This function retrieves the BIR header identified by Handle. The BIR Handle
    is not freed by the BSP.

    @param[in] BSPHandle
        The handle of the attached BioAPI service provider.

    @param[in] Handle
        The handle of the BIR whose header is to be retrieved.

    @param[out] Header
        The header of the specified BIR.

    @return
        A BioAPI_RETURN value indicating success or specifying a particular
        error condition. The value BioAPI_OK indicates success. All other
        values represent an error condition.

    \par Errors:
        BioAPIERR_INVALID_BIR_HANDLE \n
        BioAPIERR_INVALID_BSP_HANDLE
*/
    
DLLAPI BioAPI_RETURN BioAPI BioAPI_GetHeaderFromHandle (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_BIR_HANDLE   Handle,
    OUT BioAPI_BIR_HEADER *Header);


typedef BioAPI_RETURN (BioAPI *BioAPI_GetHeaderFromHandle_PTR) (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_BIR_HANDLE   Handle,
    OUT BioAPI_BIR_HEADER *Header);



//*****************************************************************************
// 8.3  Callback and Event Operations
//*****************************************************************************

/**
    \par 8.3.1 BioAPI_EnableEvents

    This function enables the events specified by the Event Mask coming from
    all the BioAPI units selected in the BSP attach session identified by the
    BSP Handle, and disables all other events from those BioAPI units for this
    biometric application.  Events from other BioAPI units directly or
    indirectly managed by the same BSP (possibly selected in other attach
    sessions but not selected in the specified attach session) are not
    affected. In some cases, "INSERT" events cannot be suppressed
    (see 7.27.2).

    @param[in] BSPHandle
        The handle of the attached BioAPI service provider.

    @param[in] Events
        A mask indicating which events to enable.

    @return
        A BioAPI_RETURN value indicating success or specifying a particular
        error condition. The value BioAPI_OK indicates success. All other
        values represent an error condition.
*/

DLLAPI BioAPI_RETURN BioAPI BioAPI_EnableEvents (
    IN BioAPI_HANDLE  BSPHandle,
    IN BioAPI_EVENT_MASK  Events);


typedef BioAPI_RETURN (BioAPI *BioAPI_EnableEvents_PTR) (
    IN BioAPI_HANDLE  BSPHandle,
    IN BioAPI_EVENT_MASK  Events);


/**
    \par 8.3.2 BioAPI_SetGUICallbacks

    This function allows the application to establish callbacks so that the
    application may control the “look-andfeel?of the biometric user interface
    by receiving from the BSP a sequence of bit-map images, called streaming
    data, for display by the biometric application.

    NOTE: Not all BSPs support the provision of streaming data.

    @param[in] BSPHandle
        The handle of the attached BioAPI service provider.

    @param[in] GuiStreamingCallback
        A pointer to an application callback to deal with the presentation of
        biometric streaming data.

    @param[in] GuiStreamingCallbackCtx
        A generic pointer to context information provided by the application
        that will be presented on the callback.

    @param[in] GuiStateCallback
        A pointer to an application callback to deal with GUI state changes.

    @param[in] GuiStateCallbackCtx
        A generic pointer to context information provided by the application
        that will be presented on the callback.
    
    @return
        A BioAPI_RETURN value indicating success or specifying a particular
        error condition. The value BioAPI_OK indicates success. All other
        values represent an error condition.

    \par Errors:
        BioAPIERR_INVALID_POINTER \n 
        BioAPIERR_INVALID_BSP_HANDLE
*/

DLLAPI BioAPI_RETURN BioAPI BioAPI_SetGUICallbacks (
    IN BioAPI_HANDLE    BSPHandle,
    IN OPTIONAL BioAPI_GUI_STREAMING_CALLBACK  GuiStreamingCallback, // optional see C.7.3    
    IN void   *GuiStreamingCallbackCtx, 
    IN BioAPI_GUI_STATE_CALLBACK  GuiStateCallback,
    IN void   *GuiStateCallbackCtx);


typedef BioAPI_RETURN (BioAPI *BioAPI_SetGUICallbacks_PTR) (
    IN BioAPI_HANDLE    BSPHandle,
    IN OPTIONAL BioAPI_GUI_STREAMING_CALLBACK  GuiStreamingCallback,
    IN void   *GuiStreamingCallbackCtx, 
    IN BioAPI_GUI_STATE_CALLBACK  GuiStateCallback,
    IN void   *GuiStateCallbackCtx);



//*****************************************************************************
// 8.4  Biometric Operations
//*****************************************************************************

/**
    \par 8.4.1 BioAPI_Capture

    This function captures samples for the purpose specified, and the BSP
    returns either an “intermediate?type BIR (if the Process function needs
    to be called), or a “processed?BIR (if not). The Purpose is recorded in
    the header of the CapturedBIR. If AuditData is non-NULL, a BIR of type
    “raw?may be returned. The function returns handles to whatever data is
    collected, and all local operations can be completed through use of the 
    handles. If the application needs to acquire the data either to store it
    in a BIR database or to send it to a server, the application can retrieve
    the data with the BioAPI_GetBIRFromHandle function.

    By default, the BSP is responsible for providing the user interface
    associated with the capture operation. The application may, however,
    request control of the GUI “look-and-feel?by providing a GUI callback
    pointer in BioAPI_SetGUICallbacks. See clause C.7 for additional
    explanation of user interface features.

    Capture serializes use of the sensor device. If two or more biometric
    applications are racing for the sensor, the losers will wait until the
    operation completes or the timeout expires. This serialization takes place
    in all functions that capture data. The BSP is responsible for serializing.
    It may do this by either returning ‘busy?(BioAPI_UNIT_IN_USE) or by
    queuing requests.

    The BIR Handle returned by the function shall be released by the
    application (via BioAPI_FreeBIRHandle) when it is no longer needed.

    @param[in] BSPHandle
        The handle of the attached BioAPI service provider.

    @param[in] Purpose
        A value indicating the purpose of the biometric data capture.

    @param[in] Subtype (optional) 
            Specifies which subtype (e.g., left/right eye) to capture. A value of
        BioAPI_NO_SUBTYPE_AVAILABLE (0x00) indicates that the BSP is to select the
        subtype(s).

    @param[in] OutputFormat (optional) 
            Specifies which BDB format to use for the returned CapturedBIR, if the
        BSP supports more than one format. A NULL pointer value indicates the
        BSP is to select the format.

    @param[out] CapturedBIR
        A handle to a BIR containing captured data. This data is either an
        “intermediate?type BIR, (which can only be used by either the Process,
        CreateTemplate, or ProcessWithAuxData functions, depending on the
        purpose), or a “processed?BIR, (which can be used directly by
        VerifyMatch or IdentifyMatch, depending on the purpose).

    @param[in] Timeout
        An integer specifying the timeout value (in milliseconds) for the
        operation. If this timeout is reached, the function returns an error,
        and no results. This value can be any positive number. A ?1?value
        means the BSP’s default timeout value will be used.

    @param[out] AuditData (optional) 
            A handle to a BIR containing raw biometric data. This data may be used
        to provide human-identifiable data of the person at the sensor unit. If
        the pointer is NULL on input, no audit data is collected. Not all BSPs
        support the collection of audit data. A BSP may return a BIR handle
        value of BioAPI_UNSUPPORTED_BIR_HANDLE to indicate AuditData is not
        supported, or a value of BioAPI_INVALID_BIR_HANDLE to indicate that no
        audit data is available.

    @return
        A BioAPI_RETURN value indicating success or specifying a particular
        error condition. The value BioAPI_OK indicates success. All other
        values represent an error condition.

    \par Errors:
        BioAPIERR_USER_CANCELLED \n
        BioAPIERR_UNABLE_TO_CAPTURE \n
        BioAPIERR_TOO_MANY_HANDLES \n
        BioAPIERR_TIMEOUT_EXPIRED \n
        BioAPIERR_PURPOSE_NOT_SUPPORTED \n
        BioAPIERR_UNSUPPORTED_FORMAT \n
        BioAPIERR_UNIT_IN_USE
*/

DLLAPI BioAPI_RETURN BioAPI BioAPI_Capture (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_BIR_PURPOSE   Purpose,
    IN OPTIONAL BioAPI_BIR_SUBTYPE Subtype,
    IN OPTIONAL const BioAPI_BIR_BIOMETRIC_DATA_FORMAT *OutputFormat,
    OUT BioAPI_BIR_HANDLE *CapturedBIR,
    IN int32_t Timeout,
    OUT OPTIONAL BioAPI_BIR_HANDLE *AuditData);


typedef BioAPI_RETURN (BioAPI *BioAPI_Capture_PTR) (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_BIR_PURPOSE   Purpose,
    IN OPTIONAL BioAPI_BIR_SUBTYPE Subtype,
    IN OPTIONAL const BioAPI_BIR_BIOMETRIC_DATA_FORMAT *OutputFormat,
    OUT BioAPI_BIR_HANDLE *CapturedBIR,
    IN int32_t Timeout,
    OUT OPTIONAL BioAPI_BIR_HANDLE *AuditData);

 
/**
    \par 8.4.2 BioAPI_CreateTemplate

    This function takes a BIR containing biometric data in intermediate form
    for the purpose of creating a new enrollment template. A new BIR is
    constructed from the CapturedBIR, and (optionally) it may perform an update
    based on an existing ReferenceTemplate. The old ReferenceTemplate remains
    unchanged.

    The optional input ReferenceTemplate is provided for use in creating the
    NewTemplate, if the BSP supports this capability. When present, use of the
    input ReferenceTemplate by the BSP, to create the output NewTemplate is
    optional.

    If the BSP supports an internal or BSP-controlled BIR database (e.g.,
    smartcard or identification engine), it may optionally return the UUID
    assigned to the newly created NewTemplate as stored within that
    BSPcontrolled BIR database. The UUID value shall be the same as that
    included in the BIR header, if present.

    The BIR handle returned by the function shall be released by the
    application (via BioAPI_FreeBIRHandle) when it is no longer needed. The
    BIR may be retrieved by calling BioAPI_GetBIRFromHandle, which also 
    releases the handle.

    @param[in] BSPHandle
        The handle of the attached BioAPI service provider.

    @param[in] CapturedBIR
        The captured BIR or its handle.

    @param[in] ReferenceTemplate (optional)
        Optionally, the template to be updated, or its key in a BIR database,
        or its handle.

    @param[in] OutputFormat (optional)
        Specifies which BDB format to use for the returned NewTemplate, if the
        BSP supports more than one format. A value of NULL indicates that the
        BSP is to select the format.

    @param[out] NewTemplate
        A handle to a newly created template that is derived from the
        CapturedBIR and (optionally) the ReferenceTemplate.

    @param[in] Payload (optional)
        A pointer to data that will be stored by the BSP. This parameter is
        ignored if NULL.

    @param[out] TemplateUUID (optional)
        A pointer to a 16-byte memory block where the BSP-assigned UUID
        associated with the ReferenceTemplate (as stored internally in a
        BSP-controlled BIR database) will optionally be returned. The pointer
        shall be set to NULL to indicate that no UUID is being returned.

    @return
        A BioAPI_RETURN value indicating success or specifying a particular
        error condition. The value BioAPI_OK indicates success. All other
        values represent an error condition.

    \par Errors:
        BioAPIERR_INVALID_BIR_HANDLE \n
        BioAPIERR_INVALID_BIR \n
        BioAPIERR_BIR_SIGNATURE_FAILURE \n
        BioAPIERR_TOO_MANY_HANDLES \n
        BioAPIERR_UNABLE_TO_STORE_PAYLOAD \n
        BioAPIERR_INCONSISTENT_PURPOSE \n
        BioAPIERR_PURPOSE_NOT_SUPPORTED \n
        BioAPIERR_UNSUPPORTED_FORMAT \n
        BioAPIERR_RECORD_NOT_FOUND \n
        BioAPIERR_QUALITY_ERROR
*/

DLLAPI BioAPI_RETURN BioAPI BioAPI_CreateTemplate (
    IN BioAPI_HANDLE BSPHandle,
    IN const BioAPI_INPUT_BIR *CapturedBIR,
    IN OPTIONAL const BioAPI_INPUT_BIR  *ReferenceTemplate,
    IN OPTIONAL const BioAPI_BIR_BIOMETRIC_DATA_FORMAT *OutputFormat,
    OUT BioAPI_BIR_HANDLE   *NewTemplate,
    IN OPTIONAL const BioAPI_DATA *Payload,
    OUT OPTIONAL BioAPI_UUID *TemplateUUID);


typedef BioAPI_RETURN (BioAPI *BioAPI_CreateTemplate_PTR) (
    IN BioAPI_HANDLE BSPHandle,
    IN const BioAPI_INPUT_BIR *CapturedBIR,
    IN OPTIONAL const BioAPI_INPUT_BIR  *ReferenceTemplate,
    IN OPTIONAL const BioAPI_BIR_BIOMETRIC_DATA_FORMAT *OutputFormat,
    OUT BioAPI_BIR_HANDLE   *NewTemplate,
    IN OPTIONAL const BioAPI_DATA *Payload,
    OUT OPTIONAL BioAPI_UUID *TemplateUUID);

 
/**
    \par 8.4.3 BioAPI_Process
 
    This function processes the intermediate data captured via a call to
    BioAPI_Capture for the purpose of either verification or identification.
    If the processing capability is supported by the attached BSP invocation,
    the BSP builds a “processed biometric sample?BIR; otherwise, ProcessedBIR
    is set to NULL, and this function returns 
    BioAPIERR_BSP_FUNCTION_NOT_SUPPORTED.

    This function results in the creation of a BIR by the BSP. The application
    can retrieve the BIR using the BIR handle through a call to 
    BioAPI_GetBIRFromHandle, which also frees the handle, or can release the 
    memory associated with the BIR handle only through a call to
    BioAPI_FreeBIRHandle.

    @param[in] BSPHandle
            The handle of the attached BioAPI service provider.

    @param[in] CapturedBIR
        The captured BIR or its handle.

    @param[in] OutputFormat (optional)
        Specifies which BDB format to use for the returned ProcessedBIR, if the
        BSP supports more than one format. A NULL pointer indicates the BSP is
        to select the format.

    @param[out] ProcessedBIR
        A handle for the newly constructed “processed?BIR.

    @return
        A BioAPI_RETURN value indicating success or specifying a particular
        error condition. The value BioAPI_OK indicates success. All other
        values represent an error condition.

    \par Errors:
        BioAPIERR_INVALID_BIR_HANDLE \n
        BioAPIERR_INVALID_BIR \n
        BioAPIERR_BIR_SIGNATURE_FAILURE \n
        BioAPIERR_TOO_MANY_HANDLES \n
        BioAPIERR_INCONSISTENT_PURPOSE \n
        BioAPIERR_PURPOSE_NOT_SUPPORTED \n
        BioAPIERR_UNSUPPORTED_FORMAT \n
        BioAPIERR_RECORD_NOT_FOUND \n
        BioAPIERR_FUNCTION_NOT_SUPPORTED \n
        BioAPIERR_QUALITY_ERROR
*/

DLLAPI BioAPI_RETURN BioAPI BioAPI_Process (
    IN BioAPI_HANDLE BSPHandle,
    IN const BioAPI_INPUT_BIR  *CapturedBIR,
    IN OPTIONAL const BioAPI_BIR_BIOMETRIC_DATA_FORMAT *OutputFormat,
    OUT BioAPI_BIR_HANDLE *ProcessedBIR);


typedef BioAPI_RETURN (BioAPI *BioAPI_Process_PTR) (
    IN BioAPI_HANDLE BSPHandle,
    IN const BioAPI_INPUT_BIR  *CapturedBIR,
    IN OPTIONAL const BioAPI_BIR_BIOMETRIC_DATA_FORMAT *OutputFormat,
    OUT BioAPI_BIR_HANDLE *ProcessedBIR);


/**
    \par 8.4.3 BioAPI_ProcessWithAuxBIR

    This function processes the intermediate data previously captured via a
    call to BioAPI_Capture in conjunction with auxiliary data, creating
    processed biometric samples for the purpose of subsequent verification or
    identification. It enables implementations that require the input of
    auxiliary data to the process operation.

    NOTE: This capability may be used to support biometric match-on-card (MOC).
    See clause C.8 for a description of BioAPI use within the overall MOC
    process.

    If the processing with auxiliary data capability is supported by the
    attached BSP invocation, the BSP builds a “processed biometric sample?
    BIR, otherwise, ProcessedBIR is set to NULL, and this function returns 
    BioAPIERR_BSP_FUNCTION_NOT_SUPPORTED.

    This function results in the creation of a BIR by the BSP. The application
    can retrieve the BIR using the BIR handle through a call to
    BioAPI_GetBIRFromHandle, which also frees the handle, or can release the 
    memory associated with the BIR handle only through a call to
    BioAPI_FreeBIRHandle.

    @param[in] BSPHandle
            The handle of the attached BioAPI service provider.

    @param[in] CapturedBIR
            A BIR obtained from the BioAPI_Capture function previously called.

    @param[in] AuxiliaryData
        A BIR structure containing auxiliary data used in the processing
        operation. NOTE 1: An example of auxiliary data is information related
        to the enrollment template which allows the processing operation to
        properly crop an input image to maximize the possibility of a
        subsequent match (e.g., to ensure that the processed BIR for
        verification and the enrollment template are derived from the same
        portion of a finger). Another would be passing of biometric algorithm
        parameters. NOTE 2: The content and format of the auxiliary data are
        specified by the BIR Biometric Data Format field in the auxiliary BIR
        header and may be specific to a BSP.

    @param[in] OutputFormat (optional)
        Specifies which BDB format to use for the returned ProcessedBIR, if the
        BSP supports more than one format. A NULL pointer value indicates the
        BSP is to select the format.

    @param[out] ProcessedBIR
        A handle for the newly constructed “processed?BIR.

    @return
        A BioAPI_RETURN value indicating success or specifying a particular
        error condition. The value BioAPI_OK indicates success. All other
        values represent an error condition.

    \par Errors:
        BioAPIERR_INVALID_BIR_HANDLE \n
        BioAPIERR_INVALID_BIR \n
        BioAPIERR_BIR_SIGNATURE_FAILURE \n
        BioAPIERR_TOO_MANY_HANDLES \n
        BioAPIERR_INCONSISTENT_PURPOSE \n
        BioAPIERR_PURPOSE_NOT_SUPPORTED \n
        BioAPIERR_UNSUPPORTED_FORMAT \n
        BioAPIERR_RECORD_NOT_FOUND \n
        BioAPIERR_FUNCTION_NOT_SUPPORTED
*/        
    
DLLAPI BioAPI_RETURN BioAPI BioAPI_ProcessWithAuxBIR (
    IN BioAPI_HANDLE BSPHandle,
    IN const BioAPI_INPUT_BIR *CapturedBIR,
    IN const BioAPI_INPUT_BIR *AuxiliaryData,
    IN OPTIONAL const BioAPI_BIR_BIOMETRIC_DATA_FORMAT *OutputFormat,
    OUT BioAPI_BIR_HANDLE *ProcessedBIR); 


typedef BioAPI_RETURN (BioAPI *BioAPI_ProcessWithAuxBIR_PTR) (
    IN BioAPI_HANDLE BSPHandle,
    IN const BioAPI_INPUT_BIR *CapturedBIR,
    IN const BioAPI_INPUT_BIR *AuxiliaryData,
    IN OPTIONAL const BioAPI_BIR_BIOMETRIC_DATA_FORMAT *OutputFormat,
    OUT BioAPI_BIR_HANDLE *ProcessedBIR); 


/**
    \par 8.4.5 BioAPI_VerifyMatch
        
    This function performs a verification (1-to-1) match between two BIRs: 
    the ProcessedBIR and the ReferenceTemplate. The ProcessedBIR is the 
    “processed?BIR constructed specifically for this verification.

    The ReferenceTemplate was created at enrollment. The application shall
    request a maximum FMR value criterion for a successful match. The Boolean
    Result indicates whether verification was successful or not, and the
    FMRAchieved is a FMR value indicating how closely the BIRs actually 
    matched.

    NOTE: See clause C.4 for information on the use of the FMR concept for
    normalized scoring and thresholding. 
    
    By setting the AdaptedBIR pointer to non-NULL, the application can request
    that a BIR be constructed by adapting the ReferenceTemplate using the
    ProcessedBIR. A new handle is returned to the AdaptedBIR. If the match
    is successful, an attempt may be made to adapt the ReferenceTemplate with
    information taken from the ProcessedBIR. (Not all BSPs perform adaptation).
    The resulting AdaptedBIR should now be considered an optimal enrollment
    template, and be saved in the BIR database. (It is up to the application
    whether or not it uses or discards this data.) It is important to note
    that adaptation may not occur in all cases.

    In the event of an adaptation, this function stores the handle to the new
    BIR in the memory pointed to by the AdaptedBIR parameter.

    If a Payload is associated with the ReferenceTemplate, the Payload may be
    returned upon successful verification if the FMRAchieved is sufficiently
    stringent; this is controlled by the policy of the BSP and specified in
    its schema.

    The memory block returned by the BioAPI function call shall be freed by
    the application as soon as it is no longer needed using BioAPI_Free
    (see clause 8.7.2). If an adapted BIR is returned, its handle can be 
    released through a call to BioAPI_FreeBIRHandle.
        
    @param[in] BSPHandle
        The handle of the attached BioAPI service provider.

    @param[in] MaxFMRRequested
        The requested FMR criterion for successful verification (i.e., the
        matching threshold).

    @param[in] ProcessedBIR
        The BIR to be verified, or its handle.

    @param[in] ReferenceTemplate
        The BIR to be verified against, or its key in a BIR database, or its
        handle.

    @param[out] AdaptedBIR (optional)
        A pointer to the handle of the adapted BIR. This parameter can be NULL
        if an adapted BIR is not desired. Not all BSPs support the adaptation
        of BIRs. The function may return a handle value of
        BioAPI_UNSUPPORTED_BIR_HANDLE to indicate that adaptation is not
        supported or a value of BioAPI_INVALID_BIR_HANDLE to indicate that
        adaptation was not possible.

    @param[out] Result
        A pointer to a Boolean value indicating (BioAPI_TRUE/BioAPI_FALSE)
        whether the BIRs matched or not according to the specified criteria.

    @param[out] FMRAchieved
        A pointer to an FMR value indicating the closeness of the match (i.e.,
        the match score).

    @param[out] Payload (optional)
        If a payload is associated with the ReferenceTemplate, it is returned
        in an allocated BioAPI_DATA structure if the FMRAchieved satisfies the
        policy of the BSP.

    @return
        A BioAPI_RETURN value indicating success or specifying a particular
        error condition. The value BioAPI_OK indicates success. All other
        values represent an error condition.

    \par Errors:
        BioAPIERR_INVALID_BIR_HANDLE \n
        BioAPIERR_INVALID_BIR \n
        BioAPIERR_BIR_SIGNATURE_FAILURE \n
        BioAPIERR_INCONSISTENT_PURPOSE \n
        BioAPIERR_BIR_NOT_FULLY_PROCESSED \n
        BioAPIERR_RECORD_NOT_FOUND \n
        BioAPIERR_QUALITY_ERROR
*/

DLLAPI BioAPI_RETURN BioAPI BioAPI_VerifyMatch (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_FMR MaxFMRRequested, 
    IN const BioAPI_INPUT_BIR *ProcessedBIR,
    IN const BioAPI_INPUT_BIR *ReferenceTemplate,
    OUT OPTIONAL BioAPI_BIR_HANDLE *AdaptedBIR,
    OUT BioAPI_BOOL *Result,
    OUT BioAPI_FMR *FMRAchieved,
    OUT OPTIONAL BioAPI_DATA *Payload);


typedef BioAPI_RETURN (BioAPI *BioAPI_VerifyMatch_PTR) (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_FMR MaxFMRRequested, 
    IN const BioAPI_INPUT_BIR *ProcessedBIR,
    IN const BioAPI_INPUT_BIR *ReferenceTemplate,
    OUT OPTIONAL BioAPI_BIR_HANDLE *AdaptedBIR,
    OUT BioAPI_BOOL *Result,
    OUT BioAPI_FMR *FMRAchieved,
    OUT OPTIONAL BioAPI_DATA *Payload);


/**
    \par 8.4.6 BioAPI_IdentifyMatch

    This function performs an identification (1-to-many) match between a 
    ProcessedBIR and a set of reference BIRs. The ProcessedBIR is the 
    “processed?BIR captured specifically for this identification. The 
    population that the match takes place against can be presented in one 
    of two ways:

    -# In a BIR database identified by an open database handle;
    -# Input in an array of BIRs;

    NOTE: When using a BSP-controlled BIR database, this database must
    previously have been opened using BioAPI_DbOpen.

    There is an option to use an array of BIRs, which can be specified in 
    BioAPI_IDENTIFY_POPULATION_TYPE in the BioAPI_IDENTIFY_POPULATION 
    structure. If it is specified as BioAPI_PRESET_ARRAY_TYPE (3), the array 
    of BIRs which had been previously set in the 
    BioAPI_PresetIdentifyPopulation call will be used. The preset array of 
    BIRs will be freed internally by the BSP when BioAPI_BSPDetach is called.

    The function performs the following actions (in order):

    -# determines the set of candidates from the population that match
       according to the specified criteria;
    -# allocates a memory block large enough to contain an array of elements
       of type BioAPI_CANDIDATE with as many elements as the number of 
       candidates determined in (a);
    -# fills the array with the candidate information for all candidates
       determined in (a), including the FMRAchieved of each candidate; and
    -# returns the address of the array in the Candidates parameter and 
       the size of the array in the NumberOfResults parameter.

    NOTE: See clause C.4 for information on the use of the FMR concept for
    normalized scoring and thresholding.

    The memory block returned by the BioAPI function call shall be freed by
    the application using BioAPI_Free (see clause 8.7.2).

    NOTE 1: Not all BSPs support 1:N identification.

    NOTE 2: Depending on the BSP and the location and size of the database
    to be searched, this operation could take a significant amount of time to
    perform.

    NOTE 3: The number of match candidates found by the BSP is dependent 
    on the actual FMR of the matching algorithm at the MaxFMRRequested
    threshold setting.

    @param[in] BSPHandle
        The handle of the attached BioAPI service provider.

    @param[in] MaxFMRRequested
        The requested FMR criterion for successful verification (i.e., the
        matching threshold).

    @param[in] ProcessedBIR
        The BIR to be identified.

    @param[in] Population
        The population of BIRs against which the identification is performed
        (by this BSP).

    @param[in] TotalNumberOfTemplates
        Specifies the total number of templates stored by the application in
        the population. A value of NULL is used if not specified. NOTE: If the
        total population is distributed over several databases/partitions, then
        the total size of the population will be greater than the population
        seen by the BSP. The BSP may map the FARRequested to its internal
        matching threshold based on this total population size.

    @param[in] Binning
        A Boolean indicating whether Binning is on or off. NOTE 1: Binning is 
        a search optimization technique that the BSP may employ. It is based on
        searching the population according to the intrinsic characteristics of
        the biometric data. While it may improve the speed of the Match
        operation, it may also increase the probability of missing a candidate
        (due to the possibility of mis-binning and as a result, searching a bin
        which should, but does not, contain the matching BIR). NOTE 2:
        Additional information regarding binning is located in clause
        A.4.6.2.10.

    @param[in] MaxNumberOfResults
        Specifies the maximum number of match candidates to be returned as a
        result of the 1:N match. A value of zero is a request for all
        candidates.

    @param[out] NumberOfResults
        A pointer to the number of candidates returned in the Candidates array
        as a result of the 1:N match.

    @param[out] Candidates
        A pointer to the address of an array of elements of type
        BioAPI_CANDIDATE containing information about the BIRs identified as a
        result of the match process (i.e., indices associated with BIRs found
        to exceed the match threshold). This list is in rank order, with the
        highest scoring (closest matching) record being first. If no matches
        are found, no array is allocated and a NULL address is returned. If the
        Population was presented in a BIR database (i.e., the value of
        BioAPI_IDENTIFY_POPULATION_TYPE is BioAPI_DB_TYPE), the array contains
        pointers to UUID’s corresponding to BIR’s stored in the BSP-controlled
        BIR database. If the Population was presented as a passed-in array of
        BIRs, then BioAPI_IDENTIFY_POPULATION_TYPE has the value
        BioAPI_ARRAY_TYPE and the array contains pointers to relative indices
        into the passed-in array.

    @param[in] Timeout
        An integer specifying the timeout value (in milliseconds) for the
        operation. If this timeout is reached, the function returns an error,
        no array is allocated, and a NULL address is returned. This value can
        be any positive number. A ?1?value means the BSP’s default timeout
        value will be used.

    @return
        A BioAPI_RETURN value indicating success or specifying a particular
        error condition. The value BioAPI_OK indicates success. All other
        values represent an error condition.

    \par Errors:
        BioAPIERR_INVALID_BIR_HANDLE \n
        BioAPIERR_BIR_SIGNATURE_FAILURE \n
        BioAPIERR_TIMEOUT_EXPIRED \n
        BioAPIERR_NO_INPUT_BIRS \n
        BioAPIERR_FUNCTION_NOT_SUPPORTED \n
        BioAPIERR_INCONSISTENT_PURPOSE \n
        BioAPIERR_BIR_NOT_FULLY_PROCESSED \n
        BioAPIERR_RECORD_NOT_FOUND \n
        BioAPIERR_QUALITY_ERROR \n
        BioAPIERR_FUNCTION_FAILED \n
        BioAPIERR_PRESET_BIR_DOES_NOT_EXIST \n
        BioAPIERR_INVALID_DB_HANDLE
*/

DLLAPI BioAPI_RETURN BioAPI BioAPI_IdentifyMatch (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_FMR MaxFMRRequested,
    IN const BioAPI_INPUT_BIR *ProcessedBIR,
    IN const BioAPI_IDENTIFY_POPULATION   *Population,
    IN uint32_t TotalNumberOfTemplates,
    IN BioAPI_BOOL Binning,
    IN  uint32_t MaxNumberOfResults,
    OUT uint32_t *NumberOfResults,
    OUT BioAPI_CANDIDATE **Candidates,
    IN int32_t Timeout);


typedef BioAPI_RETURN (BioAPI *BioAPI_IdentifyMatch_PTR) (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_FMR MaxFMRRequested,
    IN const BioAPI_INPUT_BIR *ProcessedBIR,
    IN const BioAPI_IDENTIFY_POPULATION   *Population,
    IN uint32_t TotalNumberOfTemplates,
    IN BioAPI_BOOL Binning,
    IN  uint32_t MaxNumberOfResults,
    OUT uint32_t *NumberOfResults,
    OUT BioAPI_CANDIDATE **Candidates,
    IN int32_t Timeout);


/**
    \par 8.4.7 BioAPI_Enroll
        
    This function captures biometric data from the attached device (sensor 
    unit) for the purpose of creating a ProcessedBIR for the purpose of 
    enrollment (i.e., a reference template).

    The optional input ReferenceTemplate is provided for use in creating the
    NewTemplate, if the BSP supports the template update capability. When
    present, use of the input ReferenceTemplate by the BSP to create the output
    NewTemplate is optional.

    If the BSP supports an internal (or BSP-controlled) BIR database (e.g.,
    smartcard or identification engine), it may optionally return the UUID
    assigned to the newly created ReferenceTemplate as stored within that
    BSPcontrolled BIR database. The UUID value shall be the same as that
    included in the BIR header, if present.

    The BSP is responsible for providing the user interface associated with
    the enrollment operation as a default.

    The application may request control of the GUI “look-and-feel?by
    providing a GUI callback pointer in BioAPI_SetGUICallbacks. See clause C.7
    for additional explanation of user interface features.

    Since the Enroll operation includes a capture, it serializes use of the
    sensor device. If two or more applications are racing for the device,
    the losers will wait until the operation completes or the timeout expires.

    This serialization takes place in all functions that capture data. The BSP
    is responsible for serializing. It may do this by either returning ‘busy?
    (BioAPI_UNIT_IN_USE) or by queuing requests.

    The memory block returned by the BioAPI function call shall be freed by
    the application as soon as it is no longer needed using BioAPI_Free (see
    clause 8.7.2). Output BIRs can be retrieved by a call to 
    BioAPI_GetBIRFromHandle, which releases the handle, or the handle can be
    released without retrieving the BIR through BioAPI_FreeBIRHandle.

    @param[in] BSPHandle
        The handle of the attached BioAPI service provider.

    @param[in] Purpose
        A value indicating the desired purpose of Enrollment.

    @param[in] Subtype (optional)
        Specifies which subtype (e.g., left/right eye) to enroll. A value of
        BioAPI_NO_SUBTYPE_AVAILABLE (0x00) indicates that the BSP is to select 
        the subtype(s).

    @param[in] OutputFormat (optional)
        Specifies which BDB format to use for the returned NewTemplate, if the
        BSP supports more than one format. A value of NULL indicates the BSP is
        to select the format.

    @param[in] ReferenceTemplate (optional)
        Optionally, the BIR to be adapted (updated), or it’s key in a BIR
        database, or its handle.

    @param[out] NewTemplate
        A handle to a newly created template that is derived from the new raw
        samples and (optionally) the ReferenceTemplate.

    @param[in] Payload (optional)
        A pointer to data that will be stored by the BSP. This parameter is
        ignored if NULL.

    @param[in] Timeout
        An integer specifying the timeout value (in milliseconds) for the
        operation. If this timeout is reached, the function returns an error,
        and no results. This value can be any positive number. A ?1?value
        means the BSP’s default timeout value will be used.

    @param[out] AuditData (optional)
        A handle to a BIR containing raw biometric data. This data may be used
        to provide a human-identifiable data of the person at the sensor unit.
        If the pointer is NULL on input, no audit data is collected. Not all
        BSPs support the collection of audit data. A BSP may return a BIR
        handle value of BioAPI_UNSUPPORTED_BIR_HANDLE to indicate AuditData is
        not supported, or a value of BioAPI_INVALID_BIR_HANDLE to indicate that
        no audit data is available.

    @param[out] TemplateUUID (optional)
        A pointer to a 16-byte memory block where the BSP-assigned UUID
        associated with the ReferenceTemplate (as stored internally in a
        BSP-controlled BIR database) will optionally be returned. The pointer
        shall be set to NULL to indicate that no UUID is being returned.

    @return
        A BioAPI_RETURN value indicating success or specifying a particular
        error condition. The value BioAPI_OK indicates success. All other
        values represent an error condition.

    \par Errors:
        BioAPIERR_USER_CANCELLED \n
        BioAPIERR_UNABLE_TO_CAPTURE \n
        BioAPIERR_INVALID_BIR_HANDLE \n
        BioAPIERR_TOO_MANY_HANDLES \n
        BioAPIERR_UNABLE_TO_STORE_PAYLOAD \n
        BioAPIERR_TIMEOUT_EXPIRED \n
        BioAPIERR_PURPOSE_NOT_SUPPORTED \n
        BioAPIERR_UNSUPPORTED_FORMAT \n
        BioAPIERR_RECORD_NOT_FOUND \n
        BioAPIERR_QUALITY_ERROR \n
        BioAPIERR_UNIT_IN_USE
*/

DLLAPI BioAPI_RETURN BioAPI BioAPI_Enroll (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_BIR_PURPOSE Purpose,
    IN OPTIONAL BioAPI_BIR_SUBTYPE Subtype,
    IN OPTIONAL const BioAPI_BIR_BIOMETRIC_DATA_FORMAT *OutputFormat,
    IN OPTIONAL const BioAPI_INPUT_BIR  *ReferenceTemplate,
    OUT BioAPI_BIR_HANDLE *NewTemplate,
    IN OPTIONAL const BioAPI_DATA *Payload,
    IN int32_t Timeout,
    OUT OPTIONAL BioAPI_BIR_HANDLE *AuditData,
    OUT OPTIONAL BioAPI_UUID *TemplateUUID);


typedef BioAPI_RETURN (BioAPI *BioAPI_Enroll_PTR) (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_BIR_PURPOSE Purpose,
    IN OPTIONAL BioAPI_BIR_SUBTYPE Subtype,
    IN OPTIONAL const BioAPI_BIR_BIOMETRIC_DATA_FORMAT *OutputFormat,
    IN OPTIONAL const BioAPI_INPUT_BIR  *ReferenceTemplate,
    OUT BioAPI_BIR_HANDLE *NewTemplate,
    IN OPTIONAL const BioAPI_DATA *Payload,
    IN int32_t Timeout,
    OUT OPTIONAL BioAPI_BIR_HANDLE *AuditData,
    OUT OPTIONAL BioAPI_UUID *TemplateUUID);


/**
    \par 8.4.8 BioAPI_Verify
        
    This function captures biometric data from the attached device (sensor 
    unit), and compares it against the ReferenceTemplate.

    The application shall request a maximum FMR value criterion for a
    successful match. The Boolean Result indicates whether verification was
    successful or not, and the FMRAchieved is a FMR value indicating how 
    closely the BIRs actually matched.

    NOTE: See clause C.4 for information on the use of the FMR concept for
    normalized scoring and thresholding.

    By setting the AdaptedBIR pointer to non-NULL, the application can request
    that a BIR be constructed by adapting the ReferenceTemplate using the
    ProcessedBIR. A new handle is returned to the AdaptedBIR. If the match
    is successful, an attempt may be made to adapt the ReferenceTemplate
    with information taken from the ProcessedBIR. (Not all BSPs perform 
    adaptation). The resulting AdaptedBIR should now be considered an optimal
    enrolment template, and be saved in the BIR database. (It is up to the
    application whether or not it uses or discards this data). It is important
    to note that adaptation may not occur in all cases. In the event of an
    adaptation, this function stores the handle to the new BIR in the memory
    pointed to by the AdaptedBIR parameter.

    If a Payload is associated with the ReferenceTemplate, the Payload may be
    returned upon successful verification if the FMRAchieved is sufficiently
    stringent; this is controlled by the policy of the BSP and specified in
    its schema.

    NOTE: See clause C.5 for information on the use of Payloads.

    The BSP is responsible for providing the user interface associated with
    the verify operation as a default. The application may request control of
    the GUI “look-and-feel?by providing a GUI callback pointer in 
    BioAPI_SetGUICallbacks. See clause C.7 for additional explanation of user
    interface features.

    Since the BioAPI_Verify operation includes a capture, it serializes use
    of the sensor device. If two or more applications are racing for the
    device, the losers will wait until the operation completes or the timeout
    expires.

    This serialization takes place in all functions that capture data. The
    BSP is responsible for serializing. It may do this by either returning
    ‘busy?(BioAPI_UNIT_IN_USE) or by queuing requests.

    The memory block returned by the BioAPI function call shall be freed by
    the application as soon as it is no longer needed using BioAPI_Free (see
    clause 8.7.2). Output BIRs can be retrieved by a call to 
    BioAPI_GetBIRFromHandle, which releases the handle, or the handle can
    be released without retrieving the BIR through BioAPI_FreeBIRHandle.
        
    @param[in] BSPHandle
        The handle of the attached BioAPI service provider.

    @param[in] MaxFMRRequested
        The requested FMR criterion for successful verification (i.e., the
        matching threshold).

    @param[in] ReferenceTemplate
        The BIR to be verified against, or its key in a BIR database, or its
        handle.

    @param[in] Subtype (optional)
        Specifies which subtype (e.g., left/right eye) to capture for
        verification. A value of BioAPI_NO_SUBTYPE_AVAILABLE (0x00) indicates 
        that the BSP is to select the subtype(s).

    @param[out] AdaptedBIR (optional)
        A pointer to the handle of the adapted BIR. This parameter can be NULL
        if an adapted BIR is not desired. Not all BSPs support the adaptation
        of BIRs. The function may return a handle value of
        BioAPI_UNSUPPORTED_BIR_HANDLE to indicate that adaptation is not
        supported or a value of BioAPI_INVALID_BIR_HANDLE to indicate that
        adaptation was not possible.

    @param[out] Result
        A pointer to a Boolean value indicating (BioAPI_TRUE/BioAPI_FALSE)
        whether the BIRs matched or not according to the specified criteria.

    @param[out] FMRAchieved
        A pointer to an FMR value indicating the closeness of the match (i.e.,
        the match score).

    @param[out] Payload (optional)
        If a payload is associated with the ReferenceTemplate, it is returned
        in an allocated BioAPI_DATA structure if the FMRAchieved satisfies the
        policy of the BSP.

    @param[in] Timeout
        An integer specifying the timeout value (in milliseconds) for the
        operation. If this timeout is reached, the function returns an error,
        and no results. This value can be any positive number. A ?1?value
        means the BSP’s default timeout value will be used.

    @param[out] AuditData (optional)
        A handle to a BIR containing raw biometric data. This data may be used
        to provide human-identifiable data of the person at the sensor unit. If
        the pointer is NULL on input, no audit data is collected. Not all BSPs
        support the collection of audit data. A BSP may return a BIR handle
        value of BioAPI_UNSUPPORTED_BIR_HANDLE to indicate AuditData is not
        supported, or a value of BioAPI_INVALID_BIR_HANDLE to indicate that no
        audit data is available.

    @return
        A BioAPI_RETURN value indicating success or specifying a particular
        error condition. The value BioAPI_OK indicates success. All other
        values represent an error condition.

    \par Errors:
        BioAPIERR_USER_CANCELLED \n
        BioAPIERR_UNABLE_TO_CAPTURE \n
        BioAPIERR_INVALID_BIR_HANDLE \n
        BioAPIERR_BIR_SIGNATURE_FAILURE \n
        BioAPIERR_TOO_MANY_HANDLES \n
        BioAPIERR_TIMEOUT_EXPIRED \n
        BioAPIERR_INCONSISTENT_PURPOSE \n
        BioAPIERR_UNSUPPORTED_FORMAT \n
        BioAPIERR_RECORD_NOT_FOUND \n
        BioAPIERR_QUALITY_ERROR \n
        BioAPIERR_UNIT_IN_USE
*/

DLLAPI BioAPI_RETURN BioAPI BioAPI_Verify (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_FMR MaxFMRRequested,
    IN const BioAPI_INPUT_BIR *ReferenceTemplate,
    IN OPTIONAL BioAPI_BIR_SUBTYPE Subtype,
    OUT OPTIONAL BioAPI_BIR_HANDLE *AdaptedBIR,
    OUT BioAPI_BOOL *Result,
    OUT BioAPI_FMR *FMRAchieved,
    OUT OPTIONAL BioAPI_DATA *Payload, 
    IN int32_t Timeout,
    OUT OPTIONAL BioAPI_BIR_HANDLE *AuditData);


typedef BioAPI_RETURN (BioAPI *BioAPI_Verify_PTR) (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_FMR MaxFMRRequested,
    IN const BioAPI_INPUT_BIR *ReferenceTemplate,
    IN OPTIONAL BioAPI_BIR_SUBTYPE Subtype,
    OUT OPTIONAL BioAPI_BIR_HANDLE *AdaptedBIR,
    OUT BioAPI_BOOL *Result,
    OUT BioAPI_FMR *FMRAchieved,
    OUT OPTIONAL BioAPI_DATA *Payload, 
    IN int32_t Timeout,
    OUT OPTIONAL BioAPI_BIR_HANDLE *AuditData);


/**
    \par 8.4.9 BioAPI_Identify
        
    This function captures biometric data from the attached device (sensor 
    unit), and compares it against a set of reference BIRs (the Population).

    The population that the match takes place against can be presented in one
    of two ways:

    -# in a BIR database identified by an open database handle;
    -# input in an array of BIRs;

    NOTE: When using a BSP-controlled BIR database, this database must
    previously have been opened using BioAPI_DbOpen.

    There is an option to use an array of BIRs, which can be specified in
    BioAPI_IDENTIFY_POPULATION_TYPE in the BioAPI_IDENTIFY_POPULATION
    structure. If it is specified as BioAPI_PRESET_ARRAY_TYPE (3), the array
    of BIRs which had been previously set in the 
    BioAPI_PresetIdentifyPopulation call will be used. The preset array of
    BIRs will be freed internally by the BSP when BioAPI_BSPDetach is called.

    The application shall request a maximum FMR value criterion for a
    successful match.

    The function performs the following actions (in order):

    -# captures a sample and processes it as appropriate;
    -# determines the set of candidates from the population that match
       according to the specified criteria;
    -# allocates a memory block large enough to contain an array of elements
        of type BioAPI_CANDIDATE with as many elements as the number of
        candidates determined in (b);
    -# fills the array with the candidate information for all candidates
       determined in (b), including the FMRAchieved of each candidate; and
    -# returns the address of the array in the Candidates parameter and the
       size of the array in the NumberOfResults parameter.

    NOTE: See clause C.4 for information on the use of the FMR concept for
    normalized scoring and thresholding.

    By default, the BSP is responsible for providing the user interface
    associated with the identify operation. The application may, however,
    request control of the GUI “look-and-feel?by providing a GUI callback
    pointer in BioAPI_SetGUICallbacks. See clause C.7 for additional
    explanation of user interface features.

    Since the BioAPI_Identify operation includes a capture, it serializes
    use of the sensor device. If two or more biometric applications are
    racing for the sensor, the losers will wait until the operation completes
    or the timeout expires. This serialization takes place in all functions
    that capture data. The BSP is responsible for serializing. It may do this
    by either returning ‘busy?(BioAPI_UNIT_IN_USE) or by queuing requests.

    The memory block returned by this BioAPI function call shall be freed by
    the application using BioAPI_Free (see clause 8.7.2). Output BIRs can be
    retrieved by a call to BioAPI_GetBIRFromHandle, which releases the handle,
    or the handle can be released without retrieving the BIR through
    BioAPI_FreeBIRHandle.

    NOTE 1: Not all BSPs support 1:N identification. See your BSP programmer’s
    manual to determine if the BSP(s) you are using supports this capability.

    NOTE 2: Depending on the BSP and the location and size of the database to
    be searched, this operation can take a significant amount of time to
    perform. Check your BSP manual for recommended Timeout values.

    NOTE 3: The number of match candidates found by the BSP is dependent on
    the actual FMR of the matching algorithm at the MaxFMRRequested threshold
    setting.

    @param[in] BSPHandle
        The handle of the attached BioAPI service provider.

    @param[in] MaxFMRRequested
        The requested FMR criterion for successful identification (i.e., the
        matching threshold).

    @param[in] Subtype (optional)
        Specifies which subtype (e.g., left/right eye) to capture for
        identification. A value of BioAPI_NO_SUBTYPE_AVAILABLE (0x00) indicates 
        that the BSP is to select the subtype(s).

    @param[in] Population
        The population of Templates against which the identification is
        performed (by this BSP).

    @param[in] TotalNumberOfTemplates
        Specifies the total number of templates stored by the application in
        the population. A value of NULL is used if not specified. NOTE: If the
        total population is distributed over several databases/partitions, then
        the total size of the population will be greater than the population
        seen by the BSP. The BSP may map the FARRequested to its internal
        matching threshold based on this total population size.

    @param[in] Binning
            A Boolean indicating whether binning is on or off. NOTE 1: Binning is 
            a search optimization technique that the BSP may oy. It is based on
        emplsearching the population according to the insic characteristics of
        intrthe biometric data. While it may improve speed of the Match
        the operation, it may also increase the probability issing a candidate
        of m(due to the possibility of misbinning and as a lt, searching a bin
        resuwhich should, but does not, contain the hing BIR). NOTE 2:
        matcAdditional information regarding binning is ted in clause
        locaA.4.6.2.10.

    @param[in] MaxNumberOfResults
        Specifies the maximum number of match candidates to be returned as a
        result of the 1:N match. A value of zero is a request for all
        candidates.

    @param[out] NumberOfResults
        A pointer to the number of candidates returned in the Candidates array
        as a result of the 1:N match.

    @param[out] Candidates
        A pointer to the address of an array of elements of type
        BioAPI_CANDIDATE containint information about the BIRs identified as a
        result of the match process (i.e., indices associated with BIRs found
        to exceed the match threshold). This list is in rank order, with the
        highest scoring (closest matching) record being first. If no matches
        are found, no array is allocated and a NULL address is returned. If the
        Population was presented in a BIR database (i.e., the value of
        BioAPI_IDENTIFY_POPULATION_TYPE is BioAPI_DB_TYPE), the array contains
        pointers to UUID’s corresponding to BIRs stored in the BSP-controlled
        BIR database. If the Population was presented as a passed-in array of
        BIRs, then BioAPI_IDENTIFY_POPULATION_TYPE has the value
        BioAPI_ARRAY_TYPE and the array contains pointers to relative indices
        into the passed-in array.

    @param[in] Timeout
        an integer specifying the timeout value (in milliseconds) for the
        operation. If this timeout is reached, the function returns an error,
        no array is allocated, and a NULL address is returned for the
        Candidates parameter. This value can be any positive number. A ?1?
        value means the BSP’s default timeout value will be used.

    @param[out] AuditData (optional)
        a handle to a BIR containing raw biometric data. This data may be used
        to provide human-identifiable data of the person at the sensor unit. If
        the pointer is NULL on\ input, no audit data is collected. Not all BSPs
        support the collection of audit data. A BSP may return a handle value 
        of BioAPI_UNSUPPORTED_BIR_HANDLE to indicate AuditData is not 
        supported, or a value of BioAPI_INVALID_BIR_HANDLE to indicate that no
        audit data is available.

    @return
        A BioAPI_RETURN value indicating success or specifying a particular
        error condition. The value BioAPI_OK indicates success. All other
        values represent an error condition.

    \par Errors:
        BioAPIERR_USER_CANCELLED \n
        BioAPIERR_UNABLE_TO_CAPTURE \n
        BioAPIERR_TOO_MANY_HANDLES \n
        BioAPIERR_BIR_SIGNATURE_FAILURE \n
        BioAPIERR_TIMEOUT_EXPIRED \n
        BioAPIERR_NO_INPUT_BIRS \n
        BioAPIERR_FUNCTION_NOT_SUPPORTED \n
        BioAPIERR_INCONSISTENT_PURPOSE \n
        BioAPIERR_RECORD_NOT_FOUND \n
        BioAPIERR_QUALITY_ERROR \n
        BioAPIERR_UNIT_IN_USE \n
        BioAPIERR_PRESET_BIR_DOES_NOT_EXIST \n
        BioAPIERR_INVALID_DB_HANDLE
*/

DLLAPI BioAPI_RETURN BioAPI BioAPI_Identify (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_FMR MaxFMRRequested,
    IN OPTIONAL BioAPI_BIR_SUBTYPE Subtype,
    IN const BioAPI_IDENTIFY_POPULATION   *Population,
    IN uint32_t TotalNumberOfTemplates,
    IN BioAPI_BOOL Binning,
    IN  uint32_t MaxNumberOfResults,
    OUT uint32_t *NumberOfResults,
    OUT BioAPI_CANDIDATE **Candidates,
    IN int32_t Timeout,
    OUT OPTIONAL BioAPI_BIR_HANDLE *AuditData);


typedef BioAPI_RETURN (BioAPI *BioAPI_Identify_PTR) (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_FMR MaxFMRRequested,
    IN OPTIONAL BioAPI_BIR_SUBTYPE Subtype,
    IN const BioAPI_IDENTIFY_POPULATION   *Population,
    IN uint32_t TotalNumberOfTemplates,
    IN BioAPI_BOOL Binning,
    IN  uint32_t MaxNumberOfResults,
    OUT uint32_t *NumberOfResults,
    OUT BioAPI_CANDIDATE **Candidates,
    IN int32_t Timeout,
    OUT OPTIONAL BioAPI_BIR_HANDLE *AuditData);

 
/**
    \par 8.4.10 BioAPI_Import
        
    This function passes raw biometric data obtained by a biometric
    application by any means, and requests the specified BSP attach session
    to construct a BIR for the purpose specified. InputData identifies the
    memory buffer containing the raw biometric data, while InputFormat
    identifies the form of the raw biometric data. The InputFormats that a
    particular BSP will be prepared to accept are determined by the BSP (see
    the error BioAPIERR_UNSUPPORTED_FORMAT). The function returns a handle to
    the ConstructedBIR. If the application needs to acquire the BIR either
    to store it in a database or to send it to a server, the application can
    retrieve the data with the BioAPI_GetBIRFromHandle function, or store it
    directly using BioAPI_DbStoreBIR.

    The output ConstructedBIR can be retrieved by a call to
    BioAPI_GetBIRFromHandle, which releases the handle, or the handle can be
    released without retrieving the BIR through BioAPI_FreeBIRHandle.

    @param[in] BSPHandle
        The handle of the attached BioAPI service provider.

    @param[in] InputData
        A pointer to image/stream data to import into a Processed BIR. The
        image/stream conforms to the standard identified by InputFormat.

    @param[in] InputFormat
        The format of the InputData.

    @param[in] OutputFormat (optional)
        Specifies which BDB format to use for the returned ConstructedBIR, if
        the BSP supports more than one format. A NULL pointer value indicates
        the BSP is to select the format.

    @param[in] Purpose
        A value indicating the purpose of the ConstructedBIR.

    @param[out] ConstructedBIR
        A handle to a BIR constructed from the imported biometric data. This
        BIR may be either an Intermediate or Processed BIR (to be indicated in
        the header).

    @return
        A BioAPI_RETURN value indicating success or specifying a particular
        error condition. The value BioAPI_OK indicates success. All other
        values represent an error condition.

    \par Errors:
        BioAPIERR_UNSUPPORTED_FORMAT \n
        BioAPIERR_UNABLE_TO_IMPORT \n
        BioAPIERR_TOO_MANY_HANDLES \n
        BioAPIERR_FUNCTION_NOT_SUPPORTED \n
        BioAPIERR_PURPOSE_NOT_SUPPORTED
*/

DLLAPI BioAPI_RETURN BioAPI BioAPI_Import (
    IN BioAPI_HANDLE BSPHandle,
    IN const BioAPI_DATA *InputData,
    IN const BioAPI_BIR_BIOMETRIC_DATA_FORMAT *InputFormat,
    IN OPTIONAL const BioAPI_BIR_BIOMETRIC_DATA_FORMAT *OutputFormat,
    IN BioAPI_BIR_PURPOSE Purpose,
    OUT BioAPI_BIR_HANDLE *ConstructedBIR);


typedef BioAPI_RETURN (BioAPI *BioAPI_Import_PTR) (
    IN BioAPI_HANDLE BSPHandle,
    IN const BioAPI_DATA *InputData,
    IN const BioAPI_BIR_BIOMETRIC_DATA_FORMAT *InputFormat,
    IN OPTIONAL const BioAPI_BIR_BIOMETRIC_DATA_FORMAT *OutputFormat,
    IN BioAPI_BIR_PURPOSE Purpose,
    OUT BioAPI_BIR_HANDLE *ConstructedBIR);


/**
    \par 8.4.11 BioAPI_PresetIdentifyPopulation
        
    This function provides the population of BIRs to the BSP, as specified in
    the BSPHandle. The enrollment population to be matched against can be
    presented in one of two ways:

    -# in a BIR database identified by an open database handle;
    -# input in an array of BIRs;

    The BSP allocates a memory block and transfers the population of BIRs to
    the memory block with a data format (not standardized) which is supported
    by the currently attached matching algorithm BioAPI Unit. After this
    function is called successfully, an application can call BioAPI_Identify
    or BioAPI_IdentifyMatch, specifying BioAPI_PRESET_ARRAY_TYPE in the
    BioAPI_IDENTIFY_POPULATION structure. The BSP keeps this memory block
    until another BioAPI_PresetIdentifyPopulation or BioAPI_BSPDetach is
    called.

    @param[in] BSPHandle
        The handle of the attached BioAPI service provider.

    @param[in] Population
        The population of BIRs against which the Identify matching is 
        performed.

    \par Errors:
        BioAPIERR_INVALID_BIR_HANDLE \n
        BioAPIERR_BIR_SIGNATURE_FAILURE \n
        BioAPIERR_NO_INPUT_BIRS \n
        BioAPIERR_FUNCTION_NOT_SUPPORTED \n
        BioAPIERR_INCONSISTENT_PURPOSE \n
        BioAPIERR_BIR_NOT_FULLY_PROCESSED \n
        BioAPIERR_RECORD_NOT_FOUND \n
        BioAPIERR_QUALITY_ERROR \n
        BioAPIERR_FUNCTION_FAILED
*/

DLLAPI BioAPI_RETURN BioAPI BioAPI_PresetIdentifyPopulation (
    IN BioAPI_HANDLE BSPHandle,
    IN const BioAPI_IDENTIFY_POPULATION *Population);


typedef BioAPI_RETURN (BioAPI *BioAPI_PresetIdentifyPopulation_PTR) (
    IN BioAPI_HANDLE BSPHandle,
    IN const BioAPI_IDENTIFY_POPULATION *Population);


//*********************************************************************************
// 8.5  Database Operations
//
// The database operations provide application access to BIR databases on archive 
// BioAPI Units (either directly managed by a BSP or implemented via a BFP).
// Note 1: See clause C.6 for an explanation of the context for and usage of the 
// database functions.
// Note 2: Authorization mechanisms to control a biometric application's right to 
// create or delete or write to a database are outside the scope of this 
// International Standard (but may be addressed in 19784-2, Biometric Archive 
// Function Provider Interface).
//
//*********************************************************************************

/**
    \par 8.5.1 BioAPI_DbOpen
        
    This function opens a BIR database maintained by the currently attached
    archive of the identified BSP invocation, using the access mode specified
    by the AccessRequest. A new marker is created and set to point to the
    first record in the BIR database, and a handle for that marker is returned.

    Some BSPs may only support a single BIR database or may have a preferred
    database. The application can allow the BSP to select the BIR database to 
    open by using a NULL pointer value for the database UUID parameter.

    NOTE: Every call to this function should be followed at some point by a
    call to BioAPI_DbFreeMarker, to allow the marker resources to be released.
    Applications should be aware that every call to BioAPI_DbOpen results in
    the allocation of some resources that cannot be automatically freed 
    (otherwise it would be impossible to iterate through the database using
    the returned marker handle). If the application doesn’t want to iterate
    through the BIR database, it should call BioAPI_DbFreeMarker immediately,
    otherwise it should do so after terminating the iteration.

    @param[in] BSPHandle
        The handle of an attached BSP invocation.

    @param[in] DbUuid
        A pointer to a UUID identifying the BIR database to be opened. If this
        value is set to NULL, then the BSP shall select the BIR database to
        open.

    @param[in] AccessRequest
        An indicator of the requested access mode for the BIR database, read or
        write. On a single system, only one application at a time is allowed to
        open a target database in BioAPI_DB_ACCESS_WRITE mode.

    @param[out] DbHandle
        A handle for the opened BIR database. The value will be set to
        BioAPI_DB_INVALID_HANDLE if the function fails.

    @param[out] MarkerHandle
        A marker handle that can be subsequently used by the application to
        iterate through the BIR database from the first record.

    @return
        A BioAPI_RETURN value indicating success or specifying a particular
        error condition. The value BioAPI_OK indicates success. All other
        values represent an error condition.

    \par Errors:
        BioAPIERR_UNABLE_TO_OPEN_DATABASE \n
        BioAPIERR_DATABASE_IS_OPEN \n
        BioAPIERR_DATABASE_IS_LOCKED \n
        BioAPIERR_DATABASE_DOES_NOT_EXIST \n
        BioAPIERR_INVALID_UUID \n
        BioAPIERR_INVALID_ACCESS_REQUEST \n
        BioAPIERR_ DATABASE_IS_CORRUPT
*/

DLLAPI BioAPI_RETURN BioAPI BioAPI_DbOpen (
    IN BioAPI_HANDLE BSPHandle,
    IN const BioAPI_UUID *DbUuid,
    IN BioAPI_DB_ACCESS_TYPE  AccessRequest,
    OUT BioAPI_DB_HANDLE *DbHandle,
    OUT BioAPI_DB_MARKER_HANDLE *MarkerHandle);


typedef BioAPI_RETURN (BioAPI *BioAPI_DbOpen_PTR) (
    IN BioAPI_HANDLE BSPHandle,
    IN const BioAPI_UUID *DbUuid,
    IN BioAPI_DB_ACCESS_TYPE  AccessRequest,
    OUT BioAPI_DB_HANDLE *DbHandle,
    OUT BioAPI_DB_MARKER_HANDLE *MarkerHandle);

/**
    \par 8.5.2 BioAPI_DbClose
                
    This function closes an open BIR database. All markers currently set for
    records in the database are freed and their handles become invalid.

    NOTE: A database opened in DB_ACCESS_WRITE mode can be damaged if it is
    left unclosed.

    @param[in] BSPHandle
        The handle of the attached BioAPI service provider.

    @param[in] DbHandle
        The DB handle for an open BIR database controlled by the BSP. This
        specifies the open database to be closed.

    @return
        A BioAPI_RETURN value indicating success or specifying a particular
        error condition. The value BioAPI_OK indicates success. All other
        values represent an error condition.

    \par Errors:
        BioAPIERR_UNABLE_TO_CLOSE_DATABASE \n
        BioAPIERR_INVALID_DB_HANDLE \n
        BioAPIERR_DATABASE_IS_CORRUPT
*/

DLLAPI BioAPI_RETURN BioAPI BioAPI_DbClose (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_DB_HANDLE DbHandle); 


typedef BioAPI_RETURN (BioAPI *BioAPI_DbClose_PTR) (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_DB_HANDLE DbHandle); 


/**
    \par 8.5.3 BioAPI_DbCreate
        
    This function creates and opens a new BIR database on the currently
    attached archive unit of the identified BSP invocation. The identification
    of the new database is specified by the input parameter DbUuid which shall
    be created by the biometric application, and shall be distinct from any
    current database UUID supported by that archive unit, whether currently
    open or not. The newly created BIR database is opened under the specified
    access mode.

    NOTE: The function is used create a new BIR database. It does not
    transport any information to the archive unit about the new database
    except its UUID and access conditions. There are archives which are only
    able to deal with static database sizes or where much higher effort will
    be needed to manage a database with dynamic size (e.g., smartcards storing
    templates in transparent or structured files, which might have a static
    size dependent on the characteristics of the smartcard operating system).
    Archives may need size information to create a new BIR database. Because
    the calling application might not have the knowledge about typical or
    maximum template sizes in bytes, the number of records to be stored at
    maximum in the database will be provided. Archives which are able to deal
    with database sizes dynamically may ignore the NbrRecords parameter.

    @param[in] BSPHandle 
        The handle of the attached BioAPI service provider.

    @param[in] DbUuid
        A pointer to a UUID identifying the BIR database to be created.

    @param[in] NumberOfRecords
        The maximum number of records to be stored at in the BIR database.

    @param[in] AccessRequest
        An indicator of the requested access mode for the BIR database, such as
        read or write. On a single system, only one application at a time is
        allowed to open a target database in BioAPI_DB_ACCESS_WRITE mode.

    @param[out] DbHandle
        The handle to the newly created and open database. The value will be
        set to BioAPI_DB_INVALID_HANDLE if the function fails.

    @return
        A BioAPI_RETURN value indicating success or specifying a particular
        error condition. The value BioAPI_OK indicates success. All other
        values represent an error condition.

    \par Errors:
        BioAPIERR_UNABLE_TO_CREATE_DATABASE \n
        BioAPIERR_DATABASE_ALREADY_EXISTS \n
        BioAPIERR_INVALID_UUID \n
        BioAPIERR_INVALID_ACCESS_REQUEST
*/

DLLAPI BioAPI_RETURN BioAPI BioAPI_DbCreate (
    IN BioAPI_HANDLE BSPHandle,
    IN const BioAPI_UUID *DbUuid,
    IN uint32_t NumberOfRecords,
    IN BioAPI_DB_ACCESS_TYPE AccessRequest,
    OUT BioAPI_DB_HANDLE *DbHandle);


typedef BioAPI_RETURN (BioAPI *BioAPI_DbCreate_PTR) (
    IN BioAPI_HANDLE BSPHandle,
    IN const BioAPI_UUID *DbUuid,
    IN uint32_t NumberOfRecords,
    IN BioAPI_DB_ACCESS_TYPE AccessRequest,
    OUT BioAPI_DB_HANDLE *DbHandle);

/**
    \par 8.5.4 BioAPI_DbDelete
         
    This function deletes all records from the specified BIR database and
    removes all state information associated with that database.
        
    @param[in] BSPHandle
        The handle of the attached BioAPI service provider.

    @param[in] DbUuid
        A pointer to a UUID identifying the BIR database to be deleted.

    @return
        A BioAPI_RETURN value indicating success or specifying a particular
        error condition. The value BioAPI_OK indicates success. All other
        values represent an error condition.

    \par Errors:
        BioAPIERR_DATABASE_IS_OPEN \n
        BioAPIERR_INVALID_UUID
*/

DLLAPI BioAPI_RETURN BioAPI BioAPI_DbDelete (
    IN BioAPI_HANDLE BSPHandle,
    IN const BioAPI_UUID *DbUuid);


typedef BioAPI_RETURN (BioAPI *BioAPI_DbDelete_PTR) (
    IN BioAPI_HANDLE BSPHandle,
    IN const BioAPI_UUID *DbUuid);



/**
    \par 8.5.5 BioAPI_DbSetMarker
        
    The marker identified by the MarkerHandle is set to point to the record
    indicated by the KeyValue in the BIR database identified by the DbHandle.
    A NULL value will set the marker to the first record in the database.

    NOTE: When an error occurs, the position of the marker does not change.

    @param[in] BSPHandle
        The handle of the attached BioAPI service provider.

    @param[in] DbHandle
        A handle to the open BIR database on the attached archive BioAPI Unit.

    @param[in] KeyValue
        The key into the database of the BIR to which the marker is to be set.

    @param[in] MarkerHandle
        The handle of the marker that is to be set. This marker handle can be
        subsequently used by the application to iterate through the BIR
        database from the new position.

    @return
        A BioAPI_RETURN value indicating success or specifying a particular
        error condition. The value BioAPI_OK indicates success. All other
        values represent an error condition.

    \par Errors:
        BioAPIERR_INVALID_DB_HANDLE \n
        BioAPIERR_RECORD_NOT_FOUND
*/

DLLAPI BioAPI_RETURN BioAPI BioAPI_DbSetMarker (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_DB_HANDLE DbHandle,
    IN const BioAPI_UUID *KeyValue,
    IN  BioAPI_DB_MARKER_HANDLE MarkerHandle);


typedef BioAPI_RETURN (BioAPI *BioAPI_DbSetMarker_PTR) (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_DB_HANDLE DbHandle,
    IN const BioAPI_UUID *KeyValue,
    IN  BioAPI_DB_MARKER_HANDLE MarkerHandle);



/**
    \par 8.5.6 BioAPI_DbFreeMarker

    Frees memory and resources associated with the specified marker and
    invalidates the MarkerHandle.

    @param[in] BSPHandle
        The handle of the attached BioAPI service provider.

    @param[in] MarkerHandle
        The handle of the BIR database marker to be freed.

    @return
        A BioAPI_RETURN value indicating success or specifying a particular
        error condition. The value BioAPI_OK indicates success. All other
        values represent an error condition.

    \par Errors:
        BioAPIERR_MARKER_HANDLE_IS_INVALID
*/

DLLAPI BioAPI_RETURN BioAPI BioAPI_DbFreeMarker (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_DB_MARKER_HANDLE MarkerHandle); 


typedef BioAPI_RETURN (BioAPI *BioAPI_DbFreeMarker_PTR) (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_DB_MARKER_HANDLE MarkerHandle); 

 
/**
    \par 8.5.7 BioAPI_DbStoreBIR
                
    The BIR identified by the BIRToStore parameter is stored in the open BIR
    database identified by the DbHandle parameter. If the BIRToStore is
    identified by a BIR Handle, the input BIR Handle is freed. If the 
    BIRToStore is identified by a database key value, the BIR is retrieved
    and stored in (copied to) the open database. A new UUID is assigned to
    the new BIR in the database, and this UUID can be used as a key value to
    access the BIR later.

    @param[in] BSPHandle
        The handle of the attached BioAPI service provider.

    @param[in] BIRToStore
        The BIR to be stored in the open BIR database (either the BIR, or its
        handle, or the index to it in another open database).

    @param[in] DbHandle
        The handle to the open BIR database.

    @param[out] BirUuid
        A UUID that uniquely identifies the new BIR in the BIR database. This
        UUID cannot be changed. To associate a different BIR with the user, it
        is necessary to delete the old one, store a new one in the BIR
        database, and then replace the old UUID with the new one in the
        application account database. The BIR is added to the tail end of the
        database.

    @return
        A BioAPI_RETURN value indicating success or specifying a particular
        error condition. The value BioAPI_OK indicates success. All other
        values represent an error condition.

    \par Errors:
        BioAPIERR_INVALID_DB_HANDLE
*/

DLLAPI BioAPI_RETURN BioAPI BioAPI_DbStoreBIR (
    IN BioAPI_HANDLE BSPHandle,
    IN const BioAPI_INPUT_BIR *BIRToStore,
    IN BioAPI_DB_HANDLE DbHandle,
    OUT BioAPI_UUID *BirUuid);


typedef BioAPI_RETURN (BioAPI *BioAPI_DbStoreBIR_PTR) (
    IN BioAPI_HANDLE BSPHandle,
    IN const BioAPI_INPUT_BIR *BIRToStore,
    IN BioAPI_DB_HANDLE DbHandle,
    OUT BioAPI_UUID *BirUuid);


/**
    \par 8.5.8 BioAPI_DbGetBIR
        
    The BIR identified by the KeyValue parameter in the open BIR database
    identified by the DbHandle parameter is retrieved. The BIR is copied into
    BSP storage and a handle to it is returned. A marker is created and set
    to point to the record following the retrieved BIR in the BIR database
    (or to the first record in the database if the retrieved BIR is the last),
    and a handle for the marker is returned. The memory block returned by
    the BioAPI function call shall be freed by the application using
    BioAPI_Free (see clause 8.7.2).

    @param[in] BSPHandle
        The handle of the attached BioAPI service provider.

    @param[in] DbHandle
        The handle to the open BIR database.

    @param[in] KeyValue
        The key into the database of the BIR to retrieve.

    @param[in] RetrievedBIR
        A handle to the retrieved BIR.

    @param[out] MarkerHandle
        A marker handle that can be subsequently used to iterate through the
        BIR database from the record following the retrieved BIR.

    @return
        A BioAPI_RETURN value indicating success or specifying a particular
        error condition. The value BioAPI_OK indicates success. All other
        values represent an error condition.

    \par Errors:
        BioAPIERR_RECORD_NOT_FOUND \n
        BioAPIERR_INVALID_DB_HANDLE
*/

DLLAPI BioAPI_RETURN BioAPI BioAPI_DbGetBIR (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_DB_HANDLE DbHandle,
    IN const BioAPI_UUID *KeyValue,
    OUT BioAPI_BIR_HANDLE   *RetrievedBIR,
    OUT BioAPI_DB_MARKER_HANDLE *MarkerHandle);


typedef BioAPI_RETURN (BioAPI *BioAPI_DbGetBIR_PTR) (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_DB_HANDLE DbHandle,
    IN const BioAPI_UUID *KeyValue,
    OUT BioAPI_BIR_HANDLE   *RetrievedBIR,
    OUT BioAPI_DB_MARKER_HANDLE *MarkerHandle);

 
/**
    \par 8.5.9 BioAPI_DbGetNextBIR
        
    The BIR identified by the MarkerHandle parameter is retrieved. The BIR is
    copied into BSP storage and a handle to it is returned, and a pointer to
    the UUID that uniquely identifies the BIR in the database is returned. The
    marker is updated to point to the next record in the database.

    NOTE: If there are no more records left in the BIR database, the marker
    points to an invalid position.

    @param[in] BSPHandle
        The handle of the attached BioAPI service provider.

    @param[in] DbHandle
        The handle to the open BIR database.

    @param[in,out] MarkerHandle
        A marker handle indicating which record to retrieve.

    @param[out] RetrievedBIR
        A handle to the retrieved BIR.

    @param[out] BirUuid
        The UUID that uniquely identifies the retrieved BIR in the BIR 
        database.

    @return
        A BioAPI_RETURN value indicating success or specifying a particular
        error condition. The value BioAPI_OK indicates success. All other
        values represent an error condition.

    \par Errors:
        BioAPIERR_END_OF_DATABASE \n
        BioAPIERR_MARKER_HANDLE_IS_INVALID \n
        BioAPIERR_INVALID_DB_HANDLE
*/

DLLAPI BioAPI_RETURN BioAPI BioAPI_DbGetNextBIR (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_DB_HANDLE DbHandle,
    IN BioAPI_DB_MARKER_HANDLE MarkerHandle,
    OUT BioAPI_BIR_HANDLE *RetrievedBIR,
    OUT BioAPI_UUID *BirUuid);


typedef BioAPI_RETURN (BioAPI *BioAPI_DbGetNextBIR_PTR) (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_DB_HANDLE DbHandle,
    IN BioAPI_DB_MARKER_HANDLE MarkerHandle,
    OUT BioAPI_BIR_HANDLE *RetrievedBIR,
    OUT BioAPI_UUID *BirUuid);

 
/**
    \par 8.5.10 BioAPI_DbDeleteBIR
        
    The BIR identified by the KeyValue parameter in the open BIR database
    identified by the DbHandle parameter is deleted from the database. If
    there is a marker set to the deleted BIR, then:

    -# if that BIR was not the last BIR in the database, then the marker is
       moved to the next sequential BIR;
    -# otherwise, the marker points to an invalid position. However, its
       marker handle remains valid and can be used in a subsequent call to
       BioAPI_DbSetMarker to set the marker to point to a different record.
        
    @param[in] BSPHandle
        The handle of the attached BioAPI service provider.

    @param[in] DbHandle
        The handle to the open BIR database.

    @param[in] KeyValue
        The UUID of the BIR to be deleted.

    @return
        A BioAPI_RETURN value indicating success or specifying a particular
        error condition. The value BioAPI_OK indicates success. All other
        values represent an error condition.

    \par Errors:
        BioAPIERR_RECORD_NOT_FOUND \n
        BioAPIERR_INVALID_DB_HANDLE
*/
    
DLLAPI BioAPI_RETURN BioAPI BioAPI_DbDeleteBIR (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_DB_HANDLE DbHandle,
    IN const BioAPI_UUID *KeyValue);


typedef BioAPI_RETURN (BioAPI *BioAPI_DbDeleteBIR_PTR) (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_DB_HANDLE DbHandle,
    IN const BioAPI_UUID *KeyValue);


 
//*********************************************************************************
// 8.6  BioAPI Unit Operations
//*********************************************************************************

/**
    \par 8.6.1 BioAPI_SetPowerMode
        
    This function sets the currently attached BioAPI Unit of the referenced
    BSP attach session to the requested power mode if the BioAPI Unit
    supports it.

    @param[in] BSPHandle
        The handle of the attached BioAPI service provider.

    @param[in] UnitId
        The ID of the BioAPI Unit for which the power mode is to be set. The
        BioAPI_DONT_CARE option is not valid for this function.

    @param[in] PowerMode
        A 32-bit value indicating the power mode to set the BioAPI Unit to.

    @return
        A BioAPI_RETURN value indicating success or specifying a particular
        error condition. The value BioAPI_OK indicates success. All other
        values represent an error condition.

    \par Errors:
        BioAPIERR_FUNCTION_NOT_SUPPORTED \n
        BioAPIERR_INVALID_UNIT_ID \n
        BioAPIERR_UNIT_NOT_INSERTED \n
        BioAPIERR_UNIT_IN_USE
*/

DLLAPI BioAPI_RETURN BioAPI BioAPI_SetPowerMode (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_UNIT_ID UnitId,
    IN BioAPI_POWER_MODE   PowerMode);


typedef BioAPI_RETURN (BioAPI *BioAPI_SetPowerMode_PTR) (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_UNIT_ID UnitId,
    IN BioAPI_POWER_MODE   PowerMode);


/**
    \par 8.6.2 BioAPI_SetIndicatorStatus
        
    This function sets the BioAPI Unit to the requested indicator status if
    the BioAPI Unit supports it. After BioAPI_INDICATOR_ACCEPT or
    BioAPI_INDICATOR_REJECT is set in the IndicatorStatus parameter, the 
    status will not be changed until the application sets another value.

    @param[in] BSPHandle
        The handle of the attached BioAPI service provider.

    @param[in] UnitId
        The ID of the BioAPI Unit for which the indicator status is to be set.
        The BioAPI_DONT_CARE option is not valid for this function.

    @param[in] IndicatorStatus
        A value to which to set the indicator status of the BioAPI Unit.

    @return
        A BioAPI_RETURN value indicating success or specifying a particular
        error condition. The value BioAPI_OK indicates success. All other
        values represent an error condition.

    \par Errors:
        BioAPIERR_FUNCTION_NOT_SUPPORTED \n
        BioAPIERR_INVALID_UNIT_ID \n
        BioAPIERR_UNIT_NOT_INSERTED \n
        BioAPIERR_UNIT_IN_USE
*/

DLLAPI BioAPI_RETURN BioAPI BioAPI_SetIndicatorStatus (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_UNIT_ID UnitId,
    IN BioAPI_INDICATOR_STATUS   IndicatorStatus);


typedef BioAPI_RETURN (BioAPI *BioAPI_SetIndicatorStatus_PTR) (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_UNIT_ID UnitId,
    IN BioAPI_INDICATOR_STATUS   IndicatorStatus);


/**
    \par 8.6.3 BioAPI_GetIndicatorStatus
        
    This function gets the indicator status of the BioAPI Unit if the BioAPI
    Unit supports it.

    @param[in] BSPHandle
        The handle of the attached BioAPI service provider.

    @param[in] UnitId
        The ID of the BioAPI Unit for which the indicator status is to be
        obtained. The BioAPI_DONT_CARE option is not valid for this function.

    @param[out] IndicatorStatus
        A value for the indicator status of the BioAPI Unit.

    @return
        A BioAPI_RETURN value indicating success or specifying a particular
        error condition. The value BioAPI_OK indicates success. All other
        values represent an error condition.

    \par Errors:
        BioAPIERR_FUNCTION_NOT_SUPPORTED \n
        BioAPIERR_INVALID_UNIT_ID \n
        BioAPIERR_UNIT_NOT_INSERTED \n
        BioAPIERR_UNIT_IN_USE
*/        

DLLAPI BioAPI_RETURN BioAPI BioAPI_GetIndicatorStatus (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_UNIT_ID UnitId,
    OUT BioAPI_INDICATOR_STATUS *IndicatorStatus);


typedef BioAPI_RETURN (BioAPI *BioAPI_GetIndicatorStatus_PTR) (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_UNIT_ID UnitId,
    OUT BioAPI_INDICATOR_STATUS *IndicatorStatus);


/**
    \par 8.6.3 BioAPI_CalibrateSensor

    This function performs a calibration of the attached sensor unit if that
    sensor unit supports it.
        
    @param[in] BSPHandle
        The handle of the attached BioAPI service provider.

    @param[in] Timeout
        An integer specifying the timeout value (in milliseconds) for the
        operation. If this timeout is reached, the function returns an error.
        This value can be any positive number. A ?1?value means the BSP’s
        default calibration timeout value will be used.

    @return
        A BioAPI_RETURN value indicating success or specifying a particular
        error condition. The value BioAPI_OK indicates success. All other
        values represent an error condition.

    \par Errors:
        BioAPIERR_FUNCTION_NOT_SUPPORTED \n
        BioAPIERR_UNIT_IN_USE \n
        BioAPIERR_INVALID_UNIT_ID \n
        BioAPIERR_UNIT_NOT_INSERTED \n
        BioAPIERR_CALIBRATION_NOT_SUCCESSFUL \n
        BioAPIERR_TIMEOUT_EXPIRED
*/

DLLAPI BioAPI_RETURN BioAPI BioAPI_CalibrateSensor (
    IN BioAPI_HANDLE BSPHandle,
    IN int32_t Timeout);


typedef BioAPI_RETURN (BioAPI *BioAPI_CalibrateSensor_PTR) (
    IN BioAPI_HANDLE BSPHandle,
    IN int32_t Timeout);



//*********************************************************************************
// 8.7  Utility Functions
//*********************************************************************************

/**
    \par 8.7.1 BioAPI_Cancel
        
    This function shall cancel any presently blocked calls associated with
    BSPHandle. The function shall not return until all blocking calls have
    been cancelled.
        
    @param[in] BSPHandle
        The handle of the attached BSP.

    @return
        A BioAPI_RETURN value indicating success or specifying a particular
        error condition. The value BioAPI_OK indicates success. All other
        values represent an error condition.
*/        
    
DLLAPI BioAPI_RETURN BioAPI BioAPI_Cancel (
    IN BioAPI_HANDLE BSPHandle);


typedef BioAPI_RETURN (BioAPI *BioAPI_Cancel_PTR) (
    IN BioAPI_HANDLE BSPHandle);

 
/**
    \par 8.7.2 BioAPI_Free
        
    This function causes the space pointed to by Ptr to be deallocated. If Ptr
    is NULL, no action occurs. Otherwise, if Ptr does not match a pointer
    earlier returned by the BioAPI functions, or if the space already has been
    deallocated by a call to BioAPI_Free, the behavior is undefined.

    There are some BioSPI functions in which the BSP allocates a memory block
    which is to be freed by the Framework by calling BioSPI_Free. Whenever the
    Framework passes one such memory block up to the application, it makes the
    application responsible for deallocating the memory block. In such cases,
    the application will simply call BioAPI_Free, and the Framework (on
    reception of that call) must either free the memory block or call
    BioSPI_Free on the appropriate attach session of the appropriate BSP.

    NOTE: The Framework may be implemented in such a way that the BSP
    allocated pointers are not passed to the application. The Framework will
    in this case move the data returned by the BSP to newly allocated memory,
    and will call BioSPI_Free after copying the memory, but before returning
    back to the application. However, such differences in the behaviour of
    the Framework are not visible to the application.

    In other cases, the Framework itself allocates a memory block and passes
    it to the application. In such cases, when the application calls
    BioAPI_Free, the Framework must simply deallocate the memory block,
    and must not call BioSPI_Free on any BSP.

    This mechanism requires that the Framework keep track of which memory
    blocks it has allocated itself and which memory blocks it has received
    from a BSP. For the latter, it must keep track of the BSP and the attach
    session from which the Framework has received the memory block.
        
    @param[in] Ptr
        A pointer to the memory to free.

    @return
        A BioAPI_RETURN value indicating success or specifying a particular
        error condition. The value BioAPI_OK indicates success. All other
        values represent an error condition.
*/

DLLAPI BioAPI_RETURN BioAPI BioAPI_Free (
    IN void* Ptr);

typedef BioAPI_RETURN (BioAPI *BioAPI_Free_PTR) (
    void* Ptr);


#ifdef __cplusplus
}
#endif

#endif  /* _BIOAPI_API_H_INCLUDED */
