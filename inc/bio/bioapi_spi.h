/*****************************************************************************/
/* Copyright (C) 2005 OSS Nokalva, Inc.  All rights reserved.                */
/*****************************************************************************/
/*****************************************************************************/
/* $Id: bioapi_spi.h,v 1.1.1.1 2006/06/06 20:09:05 alek Exp $ 
 *
 * Service Providers API
 *****************************************************************************/

#ifndef _BIOAPI_SPI_H_INCLUDED
#define _BIOAPI_SPI_H_INCLUDED

#include "bioapi_type.h"

#ifdef __cplusplus
extern "C" {
#endif

// 9.2.1    BioSPI_EventHandler
//  The BioAPI_EventHandler function prototype is used to define the event handler interface that enables the
//  BioAPI Framework to receive asynchronous notification of events of type BioAPI_EVENT from a BSP.
//  Example events include insertion or removal of a BioAPI Unit or a fault detection.
//  The address of a BioSPI_EventHandler function is passed to the BSP during BioSPI_BSPLoad. This is the
//  single event handler that a BSP should call to notify the BioAPI Framework of event types that occur in a
//  loaded BSP.
//  There is only one event handler for any given BSP that is loaded as a result of a BioAPI_BSPLoad from one
//  or more applications. It is the responsibility of the BioAPI Framework to notify the (possibly multiple) biometric
//  application event handlers for applications that have loaded the BSP in which an event occurs. Where an
//  insert event has been notified to the Framework before a biometric application loads the BSP, the Framework
//  remembers that event and notifies the biometric application handler immediately after the load by the
//  biometric application.
//  The BioAPI Framework forwards events to the biometric application that invoked the corresponding
//  BioAPI_BSPLoad function. The handler specified in BioSPI_EventHandler can (but need not) be invoked
//  multiple times in response to a single event.

typedef BioAPI_RETURN (BioAPI *BioSPI_EventHandler) (
    const BioAPI_UUID *BSPUuid,         // The UUID of the service provider raising the event.
    BioAPI_UNIT_ID UnitID,          // The unit ID of the BioAPI Unit associated with the event.
    const BioAPI_UNIT_SCHEMA *UnitSchema,   // The schema of the BioAPI Unit raising the event.
    BioAPI_EVENT EventType);            // The BioAPI_EVENT that has occurred

// {::NOTE::} to distinguish the type "BioSPI_EVENTHANDLER" from the function name "BioSPI_EventHandler" 
// and to be consistent with typedef's for other handlers (i.e. BioSPI_BFP_ENUMERATION_HANDLER, 
// BioSPI_MEMORY_FREE_HANDLER) we typedef BioSPIRI_EVENTHANDLER  (not defined in the standard)
typedef BioSPI_EventHandler BioSPIRI_EVENTHANDLER;

// 9.2.2 BioSPI_BFP_ENUMERATION_HANDLER
//  Description
//      This is a callback that the BioAPI Framework exposes to the BSPs to enable them to obtain information about
//      the installed BFPs. This callback is similar to the BioAPI function BioAPI_EnumBFPs, but unlike that function,
//      it is not part of the BioAPI API, and thus it is not exposed to applications. Conversely, a BSP can use this
//      callback in order to obtain the same information that an application would obtain by calling the BioAPI function
//      BioAPI_EnumBFPs.
//      The address of the BioSPI_BFP_ENUMERATION_HANDLER callback is provided by the Framework to a
//      BSP as an input parameter of the BioSPI_BSPLoad function.
//      This callback provides information about all BFPs currently installed in the component registry. It performs the
//      following actions (in order):
//      a) allocates a memory block large enough to contain an array of elements of type
//      BioAPI_BFP_SCHEMA with as many elements as the number of installed BFPs;
//      b) fills the array with the BFP schemas of all installed BFPs; and
//      c) returns the address of the array in the BfpSchemaArray parameter and the number of elements of the
//      array in the NumberOfElements parameter.
//      The memory block containing the array shall be freed by the BSP via a callback to the framework's memory
//      deallocation handler (see clause 9.2.3) when it is no longer needed by the BSP.
//      The memory blocks pointed to by the Path and BFPProperty members within each element of the array shall
//      also be freed by the BSP via a callback to the framework's memory deallocation handler (see clause 9.2.3)
//      when they are no longer needed by the application.
//  Parameters
//      BFPSchemaArray (output) – A pointer to the address of the array of elements of type
//      BioAPI_BFP_SCHEMA (allocated by the framework) containing the BFP schema information.
//      NumberOfElements (output) – A pointer to the number of elements of the array (which is also the
//      number of BFP schemas in the component registry).
//  Return Value
//      A BioAPI_RETURN value indicating success or specifying a particular error condition. The value
//      BioAPI_OK indicates success. All other values represent an error condition.
    
typedef BioAPI_RETURN (BioAPI *BioSPI_BFP_ENUMERATION_HANDLER) (
    BioAPI_BFP_SCHEMA **BFPSchemaArray, 
    uint32_t *NumberOfElements);


// 9.2.3 BioSPI_MEMORY_FREE_HANDLER
//  Description
//      This is also called the memory deallocation handler. It is a callback that the BioAPI Framework exposes to
//      the BSPs to enable them to request the deallocation of a memory block that was allocated by the framework
//      to return data to the BSP during a prior callback. Such allocations occur when a BSP calls the framework's
//      BFP enumeration handler (see clause 9.2.2). The memory deallocation handler is is similar to the BioAPI
//      function BioAPI_Free, but unlike that function, it is not part of the BioAPI API, and thus it is not exposed to
//      applications.
//      The address of the BioSPI_MEMORY_FREE_HANDLER callback is provided by the Framework to a BSP as
//      an input parameter of the BioSPI_BSPLoad function.
//      This callback causes the memory block pointed to by Ptr to be deallocated by the framework. If Ptr is NULL,
//      no action occurs. Otherwise, if Ptr does not match a pointer earlier returned by a callback, or if the memory
//      block already has been deallocated by an earlier call to the memory deallocation handler, the behavior is
//      undefined.
//      NOTE: Unlike in the function BioAPI_Free, no requests made to a memory deallocation handler result in a call to
//      BioSPI_Free.
//  arameters
//      Ptr (input) – A pointer to the memory block to free.
//  Return Value
//      A BioAPI_RETURN value indicating success or specifying a particular error condition. The value
//      BioAPI_OK indicates success. All other values represent an error condition.

typedef BioAPI_RETURN (BioAPI *BioSPI_MEMORY_FREE_HANDLER) (void* Ptr);
    
//*********************************************************************************
// 9.3.1    SPI Component Management Operations
//*********************************************************************************

//  9.3.1.1 BioSPI_BSPLoad
//  Description
//      This function completes the component initialization process between BioAPI and the biometric service
//      provider. The function BioSPI_BSPLoad shall not be called more than once without a corresponding call to
//      BioSPI_BSPUnload.
//      The BSPUuid identifies the invoked BSP.
//      The BioAPINotifyCallback defines a callback used to notify the BioAPI Framework of events of type
//      BioAPI_EVENT in any ongoing, attached sessions. The BSP shall retain this information for later use.
//      The BFPEnumerationHandler is the address of the BFP enumeration handler callback provided by the
//      Framework to the BSP. The BSP shall retain this information for later use. The BSP can use the callback
//      whenever it needs to obtain information about the BFPs installed in the Framework.
//      The MemoryFreeHandler is the address of the memory deallocation handler callback provided by the
//      Framework to the BSP. The BSP shall retain this information for later use. The BSP shall use the callback
//      whenever it needs to deallocate a memory block that was allocated by the Framework during a prior callback
//      to the BFP enumeration handler.
//      NOTE: This is a sister function to BioAPI_BSPLoad (see clause 8.1.5).
//  Parameters
//      BSPUuid (input) – The UUID of the invoked BioAPI service provider, provided as a consistency check.
//      BioAPINotifyCallback (input) – A function pointer for the BioAPI event handler that manages events of
//          type BioAPI_EVENT.
//      BFPEnumerationHandler (input) – A function pointer to the Framework’s BFP enumeration handler
//          that returns BFP schema information for all the installed BFPs.
//      MemoryFreeHandler (input) – A function pointer to the Framework's memory deallocation handler.

DLLSPI BioAPI_RETURN BioAPI BioSPI_BSPLoad (
    IN const BioAPI_UUID *BSPUuid,
    IN BioSPIRI_EVENTHANDLER BioAPINotifyCallback,
    IN BioSPI_BFP_ENUMERATION_HANDLER BFPEnumerationHandler,
    IN BioSPI_MEMORY_FREE_HANDLER MemoryFreeHandler);

typedef BioAPI_RETURN (BioAPI *BioSPI_BSPLoad_PTR) (
    IN const BioAPI_UUID *BSPUuid,
    IN BioSPIRI_EVENTHANDLER BioAPINotifyCallback,
    IN BioSPI_BFP_ENUMERATION_HANDLER BFPEnumerationHandler,
    IN BioSPI_MEMORY_FREE_HANDLER MemoryFreeHandler);
 

// 9.3.1.2  BioSPI_BSPUnload
//      Description
//      This function disables events and de-registers the event-notification function. The biometric service provider
//      may perform cleanup operations, reversing the initialization performed in BioSPI_BSPLoad.
//      NOTE: This is a sister function to BioAPI_BSPUnload (see clause 8.1.6).
//  Parameters
//      BSPUuid (input) – The UUID of the invoked BioAPI service provider.
//  
DLLSPI BioAPI_RETURN BioAPI BioSPI_BSPUnload (
    IN const BioAPI_UUID * BSPUuid);

typedef BioAPI_RETURN (BioAPI *BioSPI_BSPUnload_PTR) (
    IN const BioAPI_UUID * BSPUuid);

 
// 9.3.1.3 BioSPI_BSPAttach
//  Description
//      This function is invoked by the Framework once for each invocation of BioAPI_BSPAttach specifying the
//      BSP identified by BSPUuid.
//      The service provider shall verify compatibility with the version level specified by Version. If the version is not
//      compatible, then this function fails. The BSP should perform all initializations required to support the new BSP
//      invocation.
//      The BSP shall attach the specified BioAPI Units if they are supported.
//      NOTE: Only one BioAPI Unit of each category can be attached for each attach session at any time.
//      NOTE: This is a sister function to BioAPI_BSPAttach (see clause 8.1.7).
//  Parameters
//      BSPUuid (input) – The UUID of the invoked BioAPI service provider.
//      Version (input) – The major and minor version number of the BioAPI specification that the application
//          is expecting the BSP to support. The BSP shall determine whether it is compatible with the required
//          version.
//      UnitList (input) – a pointer to a buffer containing a list of BioAPI_UNIT_LIST_ELEMENT structures
//          indicating to the BSP which BioAPI Units (supported by the BSP) it is to use for this attach session.
//          The structures contain the ID and category of each BioAPI Unit. One of the following will be specified
//          for each category of BioAPI Unit:
//          a. Selection of a specific BioAPI Unit: The particular BioAPI Unit to be used in this attach
//          session is specified by inclusion of its ID and category.
//          b. Selection of any BioAPI Unit: When the UnitID is set to BioAPI_DONT_CARE in a particular
//          element, the BSP will choose which BioAPI Unit of that category to use, or will give an error
//          return if it does not support any BioAPI Units of that category. If a particular category is not
//          listed, the BSP will likewise choose a BioAPI Unit of that category to use if it supports a BioAPI
//          Unit of that category (however, there is no error return if it does not).
//          c. Selection of no BioAPI Unit: When the UnitID is set to 0xFFFFFFFF the BSP will explicitly
//          not attach a BioAPI Unit of the given category, even if it supports one of that category.
//          NOTE: Any subsequent calls requiring use of a BioAPI Unit of this category will fail with an error
//          return.
//      NumUnits (input) – The number of BioAPI Unit elements in the list that the pointer UnitList is pointing
//          to. If this parameter contains “0”, the BSP selects the BioAPI Unit for all categories of BioAPI Units
//          that the BSP manages directly or indirectly.
//      BSPHandle (input) – The BioAPI_HANDLE value assigned by the Framework and associated with the
//          tach session being created by this function.
    
DLLSPI BioAPI_RETURN BioAPI BioSPI_BSPAttach (
    IN  const BioAPI_UUID *BSPUuid,
    IN  BioAPI_VERSION Version, 
    IN  const BioAPI_UNIT_LIST_ELEMENT *UnitList,
    IN  uint32_t NumUnits,
    IN  BioAPI_HANDLE BSPHandle );

typedef BioAPI_RETURN (BioAPI* BioSPI_BSPAttach_PTR) (
    IN  const BioAPI_UUID *BSPUuid,
    IN  BioAPI_VERSION Version, 
    IN  const BioAPI_UNIT_LIST_ELEMENT *UnitList,
    IN  uint32_t NumUnits,
    IN  BioAPI_HANDLE BSPHandle );

 
// 9.3.1.4  BioSPI_BSPDetach
//  Description
//      This function is invoked by BioAPI once for each invocation of BioAPI_BSPDetach specifying the attachsession
//      identified by BSPHandle. The service provider shall perform all cleanup operations associated with
//      the specified attach handle.
//      NOTE: This is a sister function to BioAPI_BSPDetach (see clause 8.1.8).
//  Parameters
//      BSPHandle (input) – The BioAPI_HANDLE value associated with the attach session being terminated
//      by this function.

DLLSPI BioAPI_RETURN BioAPI BioSPI_BSPDetach (
    IN BioAPI_HANDLE BSPHandle);

typedef BioAPI_RETURN (BioAPI* BioSPI_BSPDetach_PTR) (
    IN BioAPI_HANDLE BSPHandle);


// 9.3.1.5      BioSPI_QueryUnits
// NOTE: Details of the function definition are located in clause 8.1.9, BioAPI_QueryUnits.

DLLSPI BioAPI_RETURN BioAPI BioSPI_QueryUnits (
    IN const BioAPI_UUID *Uuid,
    OUT BioAPI_UNIT_SCHEMA  **UnitSchemaArray,
    OUT uint32_t *NumberOfElements);

typedef BioAPI_RETURN (BioAPI  *BioSPI_QueryUnits_PTR) (
    const BioAPI_UUID *Uuid, 
    BioAPI_UNIT_SCHEMA  **UnitSchemaArray,
    uint32_t *NumberOfElements);
   
 
// 9.3.1.6  BioSPI_QueryBFPs
//  NOTE 1: On an incoming call to this function, the BSP can use the BFP Enumeration Handler callback (see clause
//  9.2.2) to obtain information about all installed BFPs, and can then create the list of all supported BFPs by checking
//  each entry of the array returned by the callback.
//  NOTE 2: Details of the function definition are located in clause 8.1.11, BioAPI_QueryBFPs.
//
DLLSPI BioAPI_RETURN BioAPI BioSPI_QueryBFPs (
    IN const BioAPI_UUID  *BSPUuid,
    OUT BioAPI_BFP_LIST_ELEMENT **BFPList,
    OUT uint32_t *NumberOfElements);
 
typedef BioAPI_RETURN (BioAPI *BioSPI_QueryBFPs_PTR) (
    const BioAPI_UUID  *BSPUuid,
    BioAPI_BFP_LIST_ELEMENT **BFPList,
    uint32_t *NumberOfElements);


// 9.3.1.7  BioSPI_ControlUnit
// NOTE: Details of the function definition are located in clause 8.1.12, BioAPI_ControlUnit.

DLLSPI BioAPI_RETURN BioAPI BioSPI_ControlUnit (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_UNIT_ID UnitID,
    IN uint32_t ControlCode,
    IN const BioAPI_DATA *InputData,
    OUT  BioAPI_DATA *OutputData);
 
typedef BioAPI_RETURN (BioAPI *BioSPI_ControlUnit_PTR) (
    BioAPI_HANDLE BSPHandle, 
    BioAPI_UNIT_ID UnitID,
    uint32_t ControlCode,
    IN const BioAPI_DATA *InputData,
    OUT  BioAPI_DATA *OutputData);


            

//*********************************************************************************
// SPI Handle Operations
//*********************************************************************************


//9.3.2.1   BioSPI_FreeBIRHandle
// NOTE:  Details of function definition are located in Clause 8.2.1, BioAPI_FreeBIRHandle.

DLLSPI BioAPI_RETURN BioAPI BioSPI_FreeBIRHandle (
    IN  BioAPI_HANDLE BSPHandle,
    IN  BioAPI_BIR_HANDLE Handle);

typedef BioAPI_RETURN (BioAPI  *BioSPI_FreeBIRHandle_PTR) (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_BIR_HANDLE Handle);
            
            
// 9.3.2.2  BioSPI_GetBIRFromHandle
// NOTE:  Details of function definition are located in Clause 8.2.2, BioAPI_GetBIRFromHandle.

DLLSPI BioAPI_RETURN BioAPI BioSPI_GetBIRFromHandle (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_BIR_HANDLE   Handle,
    OUT BioAPI_BIR *BIR);
 
typedef BioAPI_RETURN (BioAPI  *BioSPI_GetBIRFromHandle_PTR) (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_BIR_HANDLE Handle,
    OUT BioAPI_BIR *BIR); 
            
// 9.3.2.3  BioSPI_GetHeaderFromHandle
// NOTE:  Details of function definition are located in Clause 8.2.3, BioAPI_GETHeaderFromHandle.

DLLSPI BioAPI_RETURN  BioAPI  BioSPI_GetHeaderFromHandle (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_BIR_HANDLE   Handle,
    OUT  BioAPI_BIR_HEADER *Header);
 
typedef BioAPI_RETURN  (BioAPI  *BioSPI_GetHeaderFromHandle_PTR) (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_BIR_HANDLE Handle,
    OUT BioAPI_BIR_HEADER *Header);

            
//*********************************************************************************
// 9.3.3    SPI Callback and Event Operations
//*********************************************************************************

// 9.3.3.1  BioSPI_EnableEvents
// NOTE:  Details of function definition are located in Clause 8.3.1, BioAPI_EnableEvents.

DLLSPI BioAPI_RETURN BioAPI BioSPI_EnableEvents (
    IN  BioAPI_HANDLE BSPHandle,
    IN  BioAPI_EVENT_MASK Events);
     
typedef BioAPI_RETURN (BioAPI *BioSPI_EnableEvents_PTR) (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_EVENT_MASK Events);

            
// 9.3.3.2  BioSPI_SetGUICallbacks
// NOTE:  Details of function definition are located in Clause 8.3.2, BioAPI_SetGUICallbacks.
DLLSPI BioAPI_RETURN BioAPI BioSPI_SetGUICallbacks (
    IN  BioAPI_HANDLE BSPHandle,
    IN  OPTIONAL BioAPI_GUI_STREAMING_CALLBACK GuiStreamingCallback, // optional per C.7.3.
    IN  const void * GuiStreamingCallbackCtx,
    IN  BioAPI_GUI_STATE_CALLBACK GuiStateCallback,
    IN  const void * GuiStateCallbackCtx);

typedef BioAPI_RETURN (BioAPI *BioSPI_SetGUICallbacks_PTR) (
    IN BioAPI_HANDLE BSPHandle,
    IN OPTIONAL BioAPI_GUI_STREAMING_CALLBACK  GuiStreamingCallback,
    IN const void * GuiStreamingCallbackCtx,
    IN BioAPI_GUI_STATE_CALLBACK GuiStateCallback,
    IN const void * GuiStateCallbackCtx);

//*********************************************************************************
// 9.3.4    SPI Biometric Operations
//*********************************************************************************
 
// 9.3.4.1  BioSPI_Capture
// NOTE:  Details of function definition are located in Clause 8.4.1, BioAPI_Capture.
DLLSPI BioAPI_RETURN BioAPI BioSPI_Capture (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_BIR_PURPOSE   Purpose,
    IN BioAPI_BIR_SUBTYPE Subtype,
    IN const BioAPI_BIR_BIOMETRIC_DATA_FORMAT *OutputFormat,
    OUT BioAPI_BIR_HANDLE *CapturedBIR,
    IN int32_t Timeout,
    OUT OPTIONAL BioAPI_BIR_HANDLE *AuditData);

typedef BioAPI_RETURN (BioAPI *BioSPI_Capture_PTR) (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_BIR_PURPOSE   Purpose,
    IN BioAPI_BIR_SUBTYPE Subtype,
    IN const BioAPI_BIR_BIOMETRIC_DATA_FORMAT *OutputFormat,
    OUT BioAPI_BIR_HANDLE *CapturedBIR,
    IN int32_t Timeout,
    OUT OPTIONAL BioAPI_BIR_HANDLE *AuditData);

// 9.3.4.2  BioSPI_CreateTemplate
// NOTE:  Details of function definition are located in Clause 8.4.2, BioAPI_CreateTemplate.
DLLSPI BioAPI_RETURN BioAPI BioSPI_CreateTemplate (
    IN BioAPI_HANDLE BSPHandle,
    IN const BioAPI_INPUT_BIR *CapturedBIR,
    IN OPTIONAL const BioAPI_INPUT_BIR *ReferenceTemplate,
    IN const BioAPI_BIR_BIOMETRIC_DATA_FORMAT *OutputFormat,
    OUT BioAPI_BIR_HANDLE *NewTemplate,
    IN OPTIONAL const BioAPI_DATA *Payload,
    OUT OPTIONAL BioAPI_UUID *TemplateUUID);

typedef BioAPI_RETURN (BioAPI *BioSPI_CreateTemplate_PTR) (
    IN BioAPI_HANDLE BSPHandle,
    IN const BioAPI_INPUT_BIR *CapturedBIR,
    IN OPTIONAL const BioAPI_INPUT_BIR *ReferenceTemplate,
    IN const BioAPI_BIR_BIOMETRIC_DATA_FORMAT *OutputFormat,
    OUT BioAPI_BIR_HANDLE *NewTemplate,
    IN OPTIONAL const BioAPI_DATA *Payload,
    OUT OPTIONAL BioAPI_UUID *TemplateUUID);

// 9.3.4.3  BioSPI_Process
// NOTE:  Details of function definition are located in Clause 8.4.3, BioAPI_Process.
DLLSPI BioAPI_RETURN BioAPI BioSPI_Process (
    IN BioAPI_HANDLE BSPHandle,
    IN const BioAPI_INPUT_BIR *CapturedBIR,
    IN const BioAPI_BIR_BIOMETRIC_DATA_FORMAT *OutputFormat,
    OUT BioAPI_BIR_HANDLE *ProcessedBIR);

typedef BioAPI_RETURN (BioAPI *BioSPI_Process_PTR) (
    IN BioAPI_HANDLE BSPHandle,
    IN const BioAPI_INPUT_BIR *CapturedBIR,
    IN const BioAPI_BIR_BIOMETRIC_DATA_FORMAT *OutputFormat,
    OUT BioAPI_BIR_HANDLE *ProcessedBIR);


// 9.3.4.4  BioSPI_ProcessWithAuxBIR
// NOTE:  Details of function definition are located in Clause 8.4.4, BioAPI_ProcessWithAuxBIR.
DLLSPI BioAPI_RETURN BioAPI BioSPI_ProcessWithAuxBIR (
    IN BioAPI_HANDLE BSPHandle,
    IN const BioAPI_INPUT_BIR *CapturedBIR,
    IN const BioAPI_INPUT_BIR *AuxiliaryData,
    IN const BioAPI_BIR_BIOMETRIC_DATA_FORMAT *OutputFormat,
    OUT BioAPI_BIR_HANDLE *ProcessedBIR); 

typedef BioAPI_RETURN  (BioAPI *BioSPI_ProcessWithAuxBIR_PTR) (
    IN BioAPI_HANDLE BSPHandle,
    IN const BioAPI_INPUT_BIR *CapturedBIR,
    IN const BioAPI_INPUT_BIR *AuxiliaryData,
    IN const BioAPI_BIR_BIOMETRIC_DATA_FORMAT *OutputFormat,
    OUT BioAPI_BIR_HANDLE *ProcessedBIR);

 
// 9.3.4.5  BioSPI_VerifyMatch
// NOTE:  Details of function definition are located in Clause 8.4.5, BioAPI_VerifyMatch.
DLLSPI BioAPI_RETURN BioAPI BioSPI_VerifyMatch (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_FMR    MaxFMRRequested, 
    IN const BioAPI_INPUT_BIR *ProcessedBIR,
    IN const BioAPI_INPUT_BIR *ReferenceTemplate,
    OUT OPTIONAL BioAPI_BIR_HANDLE *AdaptedBIR,
    OUT BioAPI_BOOL *Result,
    OUT BioAPI_FMR *FMRAchieved,
    OUT OPTIONAL BioAPI_DATA *Payload);

typedef BioAPI_RETURN (BioAPI *BioSPI_VerifyMatch_PTR) (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_FMR    MaxFMRRequested, 
    IN const BioAPI_INPUT_BIR *ProcessedBIR,
    IN const BioAPI_INPUT_BIR *ReferenceTemplate,
    OUT OPTIONAL BioAPI_BIR_HANDLE *AdaptedBIR,
    OUT BioAPI_BOOL *Result,
    OUT BioAPI_FMR *FMRAchieved,
    OUT OPTIONAL BioAPI_DATA *Payload);

// 9.3.4.6  BioSPI_IdentifyMatch
// NOTE:  Details of function definition are located in Clause 8.4.6, BioAPI_IdentifyMatch.
DLLSPI BioAPI_RETURN BioAPI BioSPI_IdentifyMatch (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_FMR MaxFMRRequested,
    IN const BioAPI_INPUT_BIR *ProcessedBIR,
    IN const BioAPI_IDENTIFY_POPULATION  *Population,
    IN uint32_t TotalNumberOfTemplates,
    IN BioAPI_BOOL Binning,
    IN  uint32_t MaxNumberOfResults,
    OUT uint32_t *NumberOfResults,
    OUT BioAPI_CANDIDATE **Candidates,
    IN int32_t Timeout);

typedef BioAPI_RETURN (BioAPI *BioSPI_IdentifyMatch_PTR) (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_FMR MaxFMRRequested,
    IN const BioAPI_INPUT_BIR *ProcessedBIR,
    IN const BioAPI_IDENTIFY_POPULATION  *Population,
    IN uint32_t TotalNumberOfTemplates,
    IN BioAPI_BOOL Binning,
    IN  uint32_t MaxNumberOfResults,
    OUT uint32_t *NumberOfResults,
    OUT BioAPI_CANDIDATE **Candidates,
    IN int32_t Timeout);


// 9.3.4.7  BioSPI_Enroll
// NOTE:  Details of function definition are located in Clause 8.4.7, BioAPI_Enroll.
DLLSPI BioAPI_RETURN BioAPI BioSPI_Enroll (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_BIR_PURPOSE Purpose,
    IN BioAPI_BIR_SUBTYPE Subtype,
    IN const BioAPI_BIR_BIOMETRIC_DATA_FORMAT *OutputFormat,
    IN OPTIONAL const BioAPI_INPUT_BIR * ReferenceTemplate,
    OUT BioAPI_BIR_HANDLE * NewTemplate,
    IN OPTIONAL const BioAPI_DATA * Payload,
    IN int32_t Timeout,
    OUT OPTIONAL BioAPI_BIR_HANDLE * AuditData,
    OUT OPTIONAL BioAPI_UUID * TemplateUUID);

typedef BioAPI_RETURN (BioAPI *BioSPI_Enroll_PTR) (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_BIR_PURPOSE Purpose,
    IN BioAPI_BIR_SUBTYPE Subtype,
    IN const BioAPI_BIR_BIOMETRIC_DATA_FORMAT *OutputFormat,
    IN OPTIONAL const BioAPI_INPUT_BIR * pReferenceTemplate,
    OUT BioAPI_BIR_HANDLE * pNewTemplate,
    IN OPTIONAL const BioAPI_DATA * pPayload,
    IN int32_t Timeout,
    OUT OPTIONAL BioAPI_BIR_HANDLE * pAuditData,
    OUT OPTIONAL BioAPI_UUID * pTemplateUUID);


// 9.3.4.8  BioSPI_Verify
// NOTE:  Details of function definition are located in Clause 8.4.8, BioAPI_Verify.
DLLSPI BioAPI_RETURN BioAPI BioSPI_Verify (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_FMR MaxFMRRequested,
    IN const BioAPI_INPUT_BIR *ReferenceTemplate,
    IN BioAPI_BIR_SUBTYPE Subtype,
    OUT OPTIONAL BioAPI_BIR_HANDLE *AdaptedBIR,
    OUT BioAPI_BOOL *Result,
    OUT BioAPI_FMR *FMRAchieved,
    OUT OPTIONAL BioAPI_DATA *Payload, 
    IN int32_t Timeout,
    OUT OPTIONAL BioAPI_BIR_HANDLE *AuditData);

typedef BioAPI_RETURN (BioAPI *BioSPI_Verify_PTR) (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_FMR MaxFMRRequested,
    IN const BioAPI_INPUT_BIR *ReferenceTemplate,
    IN BioAPI_BIR_SUBTYPE Subtype,
    OUT OPTIONAL BioAPI_BIR_HANDLE *AdaptedBIR,
    OUT BioAPI_BOOL *Result,
    OUT BioAPI_FMR *FMRAchieved,
    OUT OPTIONAL BioAPI_DATA *Payload, 
    IN int32_t Timeout,
    OUT OPTIONAL BioAPI_BIR_HANDLE *AuditData);


// 9.3.4.9  BioSPI_Identify
// NOTE:  Details of function definition are located in Clause 8.4.9, BioAPI_Identify.
DLLSPI BioAPI_RETURN BioAPI BioSPI_Identify(
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_FMR MaxFMRRequested,
    IN BioAPI_BIR_SUBTYPE Subtype,
    IN const BioAPI_IDENTIFY_POPULATION *Population,
    IN uint32_t TotalNumberOfTemplates,
    IN BioAPI_BOOL Binning,
    IN  uint32_t MaxNumberOfResults,
    OUT uint32_t *NumberOfResults,
    OUT BioAPI_CANDIDATE **Candidates,
    IN int32_t Timeout,
    OUT OPTIONAL BioAPI_BIR_HANDLE *AuditData);

typedef BioAPI_RETURN (BioAPI *BioSPI_Identify_PTR) (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_FMR MaxFMRRequested,
    IN BioAPI_BIR_SUBTYPE Subtype,
    IN const BioAPI_IDENTIFY_POPULATION *Population,
    IN uint32_t TotalNumberOfTemplates,
    IN BioAPI_BOOL Binning,
    IN  uint32_t MaxNumberOfResults,
    OUT uint32_t *NumberOfResults,
    OUT BioAPI_CANDIDATE **Candidates,
    IN int32_t Timeout,
    OUT OPTIONAL BioAPI_BIR_HANDLE *AuditData);


// 9.3.4.10 BioSPI_Import
//NOTE:  Details of function definition are located in Clause 8.4.10, BioAPI_Import.
DLLSPI BioAPI_RETURN BioAPI BioSPI_Import (
    IN BioAPI_HANDLE BSPHandle,
    IN const BioAPI_DATA *InputData,
    IN const BioAPI_BIR_BIOMETRIC_DATA_FORMAT *InputFormat,
    IN const BioAPI_BIR_BIOMETRIC_DATA_FORMAT *OutputFormat,
    IN BioAPI_BIR_PURPOSE Purpose,
    OUT BioAPI_BIR_HANDLE *ConstructedBIR);

typedef BioAPI_RETURN (BioAPI *BioSPI_Import_PTR) (
    IN BioAPI_HANDLE BSPHandle,
    IN const BioAPI_DATA *InputData, 
    IN const BioAPI_BIR_BIOMETRIC_DATA_FORMAT *InputFormat,
    IN const BioAPI_BIR_BIOMETRIC_DATA_FORMAT *OutputFormat,
    IN BioAPI_BIR_PURPOSE Purpose,
    OUT BioAPI_BIR_HANDLE *ConstructedBIR);

// 9.3.4.11     BioSPI_PresetIdentifyPopulation
// NOTE:  Details of function definition are located in Clause 8.4.11, BioAPI_PresetIdentifyPopulation.
DLLSPI BioAPI_RETURN BioAPI BioSPI_PresetIdentifyPopulation (
    IN BioAPI_HANDLE BSPHandle,
    IN const BioAPI_IDENTIFY_POPULATION   *Population);

typedef BioAPI_RETURN (BioAPI *BioSPI_PresetIdentifyPopulation_PTR) (
    IN BioAPI_HANDLE BSPHandle,
    IN const BioAPI_IDENTIFY_POPULATION   *Population);

 
//*********************************************************************************
// 9.3.5    SPI Database Operations
//*********************************************************************************

// 9.3.5.1  BioSPI_DbOpen
// NOTE:  Details of function definition are located in Clause 8.5.1, BioAPI_DbOpen.
DLLSPI BioAPI_RETURN BioAPI BioSPI_DbOpen (
    IN BioAPI_HANDLE BSPHandle,
    IN const BioAPI_UUID *DbUuid,
    IN BioAPI_DB_ACCESS_TYPE  AccessRequest,
    OUT BioAPI_DB_HANDLE *DbHandle,
    OUT BioAPI_DB_MARKER_HANDLE *MarkerHandle);

typedef BioAPI_RETURN (BioAPI *BioSPI_DbOpen_PTR) (
    IN BioAPI_HANDLE BSPHandle,
    IN const BioAPI_UUID *DbUuid,
    IN BioAPI_DB_ACCESS_TYPE  AccessRequest,
    OUT BioAPI_DB_HANDLE *DbHandle,
    OUT BioAPI_DB_MARKER_HANDLE *MarkerHandle);

// 9.3.5.2  BioSPI_DbClose
// NOTE:  Details of function definition are located in Clause 8.5.2, BioAPI_DbClose.
DLLSPI BioAPI_RETURN BioAPI BioSPI_DbClose (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_DB_HANDLE DbHandle); 

typedef BioAPI_RETURN (BioAPI *BioSPI_DbClose_PTR) (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_DB_HANDLE DbHandle); 

// 9.3.5.3  BioSPI_DbCreate
// NOTE:  Details of function definition are located in Clause 8.5.3, BioAPI_DbCreate.
DLLSPI BioAPI_RETURN BioAPI BioSPI_DbCreate (
    IN BioAPI_HANDLE BSPHandle,
    IN const BioAPI_UUID *DbUuid, 
    IN uint32_t NumberOfRecords,
    IN BioAPI_DB_ACCESS_TYPE AccessRequest,
    OUT BioAPI_DB_HANDLE *DbHandle);

typedef BioAPI_RETURN (BioAPI *BioSPI_DbCreate_PTR) (
    IN BioAPI_HANDLE BSPHandle,
    IN const BioAPI_UUID *DbUuid,
    IN uint32_t NumberOfRecords,
    IN BioAPI_DB_ACCESS_TYPE AccessRequest,
    OUT BioAPI_DB_HANDLE *DbHandle);

// 9.3.5.4  BioSPI_DbDelete
// NOTE:  Details of function definition are located in Clause 8.5.4, BioAPI_DbDelete.
DLLSPI BioAPI_RETURN BioAPI BioSPI_DbDelete (
    IN BioAPI_HANDLE BSPHandle,
    IN const BioAPI_UUID *DbUuid);

typedef BioAPI_RETURN (BioAPI *BioSPI_DbDelete_PTR) (
    IN BioAPI_HANDLE BSPHandle,
    IN const BioAPI_UUID *DbUuid);

// 9.3.5.5  BioSPI_DbSetMarker
// NOTE:  Details of function definition are located in Clause 8.5.5, BioAPI_DbSetMarker.
DLLSPI BioAPI_RETURN BioAPI BioSPI_DbSetMarker (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_DB_HANDLE DbHandle,
    IN const BioAPI_UUID *KeyValue,
    IN  BioAPI_DB_MARKER_HANDLE MarkerHandle); 

typedef BioAPI_RETURN (BioAPI *BioSPI_DbSetMarker_PTR)(
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_DB_HANDLE DbHandle,
    IN const BioAPI_UUID *KeyValue,
    IN  BioAPI_DB_MARKER_HANDLE MarkerHandle); 

// 9.3.5.6  BioSPI_DbFreeMarker
// NOTE:  Details of function definition are located in Clause 8.5.6, BioAPI_DbFreeMarker.
DLLSPI BioAPI_RETURN BioAPI BioSPI_DbFreeMarker (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_DB_MARKER_HANDLE MarkerHandle); 

typedef BioAPI_RETURN (BioAPI *BioSPI_DbFreeMarker_PTR)(
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_DB_MARKER_HANDLE MarkerHandle); 

// 9.3.5.7  BioSPI_DbStoreBIR
// NOTE:  Details of function definition are located in Clause 8.5.7, BioAPI_DbStoreBIR.
DLLSPI BioAPI_RETURN BioAPI BioSPI_DbStoreBIR (
    IN BioAPI_HANDLE BSPHandle,
    IN const BioAPI_INPUT_BIR *BIRToStore,
    IN BioAPI_DB_HANDLE DbHandle,
    OUT BioAPI_UUID *BirUuid);

typedef BioAPI_RETURN (BioAPI *BioSPI_DbStoreBIR_PTR)(
    IN BioAPI_HANDLE BSPHandle,
    IN const BioAPI_INPUT_BIR *BIRToStore,
    IN BioAPI_DB_HANDLE DbHandle,
    OUT BioAPI_UUID *BirUuid);

// 9.3.5.8  BioSPI_DbGetBIR
// NOTE:  Details of function definition are located in Clause 8.5.8, BioAPI_DbGetBIR.
DLLSPI BioAPI_RETURN BioAPI BioSPI_DbGetBIR (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_DB_HANDLE DbHandle,
    IN const BioAPI_UUID *KeyValue,
    OUT BioAPI_BIR_HANDLE   *RetrievedBIR,
    OUT BioAPI_DB_MARKER_HANDLE *MarkerHandle);

typedef BioAPI_RETURN (BioAPI *BioSPI_DbGetBIR_PTR)(
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_DB_HANDLE DbHandle,
    IN const BioAPI_UUID *KeyValue,
    OUT BioAPI_BIR_HANDLE   *RetrievedBIR,
    OUT BioAPI_DB_MARKER_HANDLE *MarkerHandle);

// 9.3.5.9  BioSPI_DbGetNextBIR
// NOTE:  Details of function definition are located in Clause 8.5.9, BioAPI_DbGetNextBIR.
DLLSPI BioAPI_RETURN BioAPI BioSPI_DbGetNextBIR (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_DB_HANDLE DbHandle,
    IN BioAPI_DB_MARKER_HANDLE MarkerHandle,
    OUT BioAPI_BIR_HANDLE *RetrievedBIR,
    OUT BioAPI_UUID *BirUuid);

typedef BioAPI_RETURN (BioAPI *BioSPI_DbGetNextBIR_PTR)(
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_DB_HANDLE DbHandle,
    IN BioAPI_DB_MARKER_HANDLE MarkerHandle,
    OUT BioAPI_BIR_HANDLE *RetrievedBIR,
    OUT BioAPI_UUID *BirUuid);

// 9.3.5.10 BioSPI_DbDeleteBIR
//NOTE:  Details of function definition are located in Clause 8.5.10, BioAPI_DbDeleteBIR.
DLLSPI BioAPI_RETURN BioAPI BioSPI_DbDeleteBIR (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_DB_HANDLE DbHandle,
    IN const BioAPI_UUID *KeyValue);
 
typedef BioAPI_RETURN (BioAPI *BioSPI_DbDeleteBIR_PTR)(
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_DB_HANDLE DbHandle,
    IN const BioAPI_UUID *KeyValue);

//*********************************************************************************
// 9.3.6    SPI BioAPI Unit Operations
//*********************************************************************************

// 9.3.6.1  BioSPI_SetPowerMode
// NOTE:  Details of function definition are located in Clause 8.6.1, BioAPI_SetPowerMode.
DLLSPI BioAPI_RETURN BioAPI BioSPI_SetPowerMode (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_UNIT_ID UnitId,
    IN BioAPI_POWER_MODE PowerMode);

typedef BioAPI_RETURN (BioAPI *BioSPI_SetPowerMode_PTR)(
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_UNIT_ID UnitId,
    IN BioAPI_POWER_MODE PowerMode);

// 9.3.6.2  BioSPI_SetIndicatorStatus
// NOTE:  Details of function definition are located in Clause 8.6.2, BioAPI_SetIndicatorStatus.
DLLSPI BioAPI_RETURN BioAPI BioSPI_SetIndicatorStatus (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_UNIT_ID UnitId,
    IN BioAPI_INDICATOR_STATUS IndicatorStatus);

typedef BioAPI_RETURN  (BioAPI *BioSPI_SetIndicatorStatus_PTR)(
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_UNIT_ID UnitId,
    IN BioAPI_INDICATOR_STATUS IndicatorStatus);

// 9.3.6.3  BioSPI_GetIndicatorStatus
// NOTE:  Details of function definition are located in Clause 8.6.3, BioAPI_GetIndicatorStatus.
DLLSPI BioAPI_RETURN BioAPI BioSPI_GetIndicatorStatus (
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_UNIT_ID UnitId,
    OUT BioAPI_INDICATOR_STATUS *IndicatorStatus);

typedef BioAPI_RETURN  (BioAPI *BioSPI_GetIndicatorStatus_PTR)(
    IN BioAPI_HANDLE BSPHandle,
    IN BioAPI_UNIT_ID UnitId,
    OUT BioAPI_INDICATOR_STATUS *IndicatorStatus);

// 9.3.6.4 BioAPI_CalibrateSensor
//NOTE: Details of the function definition are located in clause 8.6.4, BioAPI_CalibrateSensor.
DLLSPI BioAPI_RETURN BioAPI BioSPI_CalibrateSensor (
    IN BioAPI_HANDLE BSPHandle,
    IN int32_t Timeout);

typedef BioAPI_RETURN (BioAPI *BioSPI_CalibrateSensor_PTR) (
    IN BioAPI_HANDLE BSPHandle,
    IN int32_t Timeout);

//*********************************************************************************
// 9.3.7    SPI Utility Functions
//*********************************************************************************
 
// 9.3.7.1  BioSPI_Cancel
// NOTE:  Details of function definition are located in Clause 8.7.1, BioAPI_Cancel.
DLLSPI BioAPI_RETURN BioAPI BioSPI_Cancel (
    BioAPI_HANDLE BSPHandle);

typedef BioAPI_RETURN (BioAPI *BioSPI_Cancel_PTR) (
    BioAPI_HANDLE BSPHandle);

//9.3.7.2   BioSPI_Free
// NOTE:  Details of function definition are located in Clause 8.7.2, BioAPI_Free.
DLLSPI BioAPI_RETURN BioAPI BioSPI_Free (
    void *Ptr);

typedef BioAPI_RETURN (BioAPI *BioSPI_Free_PTR) (
    void* Ptr);


//*********************************************************************************
// BSP Installation and configuration
//*********************************************************************************
// {::NOTE::} This function is not part of the BioAPI standard.
//
// Installation utilities are vendor-specific and they "know" where/how to get the 
// scheama of the installed BSP. At the same time, the schema is a "static" 
// information, that is developed along with the BSP itself and doesn't change once
// the BSP is deployed. Storing the schema separately may get out-of-synch or be
// mismatched with the wrong BSP, so an OSS-supplied helper function that is exported 
// by the BSP and allows to read its schema making it easy to perform installation 
// and administrative tasks. 
// This function is  optional and, when it is not exported or fails, the caller 
// (an installation utility) should look elsewhere for the schema.
DLLSPI BioAPI_RETURN BioAPI  BioSPIRI_BSPGetSchema (
    OUT BioAPI_BSP_SCHEMA* pBSPSchema);

typedef BioAPI_RETURN (BioAPI * BioSPIRI_BSPGetSchema_PTR) (
    OUT BioAPI_BSP_SCHEMA* pBSPSchema);

#ifdef __cplusplus
}
#endif

#endif  /* _BIOAPI_SPI_H_INCLUDED */
