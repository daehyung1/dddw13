/*****************************************************************************/
/* Copyright (C) 2005 OSS Nokalva, Inc.  All rights reserved.                */
/*****************************************************************************/
/*****************************************************************************/
/* $Id: bioapi_type.h,v 1.1.1.1 2006/06/06 20:09:05 alek Exp $ 
 *
 * BioAPI type definitions.
 * NOTE: the comment before each type definition provides the number of clause 
 * in the BioAPI 2.0, that defines the type.
 *****************************************************************************/

#ifndef _BIOAPI_TYPE_H_INCLUDED
#define _BIOAPI_TYPE_H_INCLUDED

#include "bioapi_porttype.h"

#ifdef __cplusplus
extern "C" {
#endif

// Function parameters helpers.
// The arguments of the BioAPI functions that are passed *by pointer* can be 
// the combination of the following:
// IN - arguments that are "read-only" and should NOT be modified inside the 
//      function. These usually have the 'const' modifier unless the argument is both
//      IN and OUT. IN parameters are alway allocated/de-allocated by the caller.
//      If the function implementer needs to retain such data, it should make a copy and 
//      never store the pointer, because the memory can be released by the caller as 
//      soon as the function returns.
// OUT - Return values. The argument can be either: 
//      (a) a 'refernce', meaning the memory is provided (allocated) by the caller 
//      and expected to be modified (filled in) by the function.  Any pointers that
//      are part of that data are allocated by the function. 
//      (b) a pointer to pointer - where memory for the returned data is allocated 
//      by the function and then the pointer to this memory is retuned via this argument.
//      Any data allocated by the function must be later de-allocated 
//      by the caller via BioAPI_Free() or BioSPI_Free(). In case the function fails
//      it should free any allocated memory and return an error. 
// OPTIONAL - arguments that are well.. optional and, when not provided, are 
//      usually are set to NULL.
#define IN          
#define OUT         
#define OPTIONAL            

 

/*****************************************************************************
 * BioAPI general purpose types.
 *****************************************************************************/

    
// 7.50 BioAPI_RETURN 
/// This data type is returned by all BioAPI functions. The permitted values include:
/// ?  BioAPI_OK
/// ?  All Error Values defined in this specification
/// ?  BSP-specific error  values defined and returned by a specific service provider
/// ?  All Error Values defined for lower level components
/// ?  Device-specific error values defined and returned by a specific service provider
/// BioAPI_OK ?Indicates operation was successful
/// All other values ?Indicates the operation was unsuccessful and 
/// identifies the specific, detected error that resulted in the failure.  
/// See bioapi_err.h for the list of standardised error codes.

typedef uint32_t BioAPI_RETURN;
#define BioAPI_OK   (0)

// 7.15 BioAPI_BOOL 
///This data type is used to indicate a true or false condition.
 
typedef  uint32_t BioAPI_BOOL;
#define BioAPI_FALSE (0)
#define BioAPI_TRUE  (!BioAPI_FALSE)


// 7.38 BioAPI_HANDLE
/// A unique identifier, returned on BioAPI_BSPAttach, that identifies an attached BioAPI BSP session.
typedef uint32_t BioAPI_HANDLE;
// {::NOTE::} This definition is not in agreement with the specification's text at 8.1.7.2:
// "NewBSPHandle (output) ?a new handle that can be used to interact with the requested BSP.  
// The value will be set to BioAPIERR_FRAMEWORK_INVALID_BSP_HANDLE if the function fails." 
// We've used this value since we expect a corrigendum to be released to address this issue.
#define BioAPI_INVALID_HANDLE (0)

// 7.51 BioAPI_STRING
/// This is used by BioAPI data structures to represent a character string inside of a fixed-length buffer.
/// The character string is expected to be NULL-terminated.
/// The character string shall consist of ISO/IEC 10646 characters encoded in UTF-8.
typedef uint8_t BioAPI_STRING [269];


// 7.19 BioAPI_DATA
/// The BioAPI_DATA structure is used to associate a length, in bytes, with an arbitrary block of
/// contiguous memory.
typedef struct bioapi_data{
    uint32_t Length; /* in bytes */
    void *Data;
} BioAPI_DATA;


// 7.18 BioAPI_CATEGORY
/// This bitmask describes the category of BFP or BioAPI Unit. BFPs can provide more than one functionality
/// while BioAPI Units provide exactly one functionality.

typedef uint32_t BioAPI_CATEGORY;

#define BioAPI_CATEGORY_ARCHIVE        (0x00000001)
#define BioAPI_CATEGORY_MATCHING_ALG   (0x00000002)
#define BioAPI_CATEGORY_PROCESSING_ALG (0x00000004)
#define BioAPI_CATEGORY_SENSOR         (0x00000008)

// The highest significant bit is reserved and does not indicate a category of BFP or BioAPI Unit.
// {::NOTE::} additional helper macro  (not defined in the standard)
#define BioAPIRI_CATEGORY_MASK         (0x7FFFFFFF)


// 7.56 BioAPI_UUID
/// A universally unique identifier used to identify and address components (BSPs, BFPs, BioAPI Units, and the
/// BioAPI Framework), to identify BIR databases, and as a database index for BSP-controlled BIR databases.
/// NOTE 1: UUIDs are defined in ISO/IEC 9834-8.
/// NOTE 2: The BioAPI UUID within a BIR header corresponds to the “CBEFF_BDB_index?in ISO/IEC 19785-1.
typedef uint8_t BioAPI_UUID[16];


// 7.57 BioAPI_VERSION
// This structure is used to represent the version of the BioAPI or FPI specification to which
/// components or data have been implemented. The primary use of this value is within the BIR header and
/// within schemas of the component registry.
/// The version corresponding to this International Standard has an integer value of (decimal) 32, or (hex) 20,
/// corresponding to a Major value of 2 and a Minor value of zero.
/// NOTE 1: This structure is not used for product versions, which are generally represented by strings.
/// NOTE 2: The BioAPI Version used within the BIR header corresponds to the “CBEFF_patron_header_version?in
/// ISO/IEC 19785-1.
/// Definitions
/// The BioAPI Version is a concatenation of the major and minor version values such that first hex digit
/// represents the major version and the second hex digit represents the minor version:
/// BioAPI_VERSION 0xnm,  where n = MajorVersion and m=MinorVersion:
typedef uint8_t BioAPI_VERSION;

// 7.20 BioAPI_DATE
/// Defines the date when the BIR was created or when it is no longer valid.
/// NOTE 1: The year 2000 AD is represented by a Year value of 2000.
/// NOTE 2: The condition NO_VALUE_AVAILABLE is indicated by setting all fields to zero. When used within the
/// Creation DTG within a BIR header, if no date information is available, then the NO_DATE_AVAILABLE value shall be
/// used.
/// NOTE 3: When used for ExpirationDate in a BIR header, corresponds to the “Valid to?portion of the
/// “CBEFF_BDB_validity_period?in ISO/IEC 19785-1.

typedef struct bioapi_date {
    uint16_t Year; ///< valid range: 1900 ?9999 
    uint8_t Month; ///< valid range: 01 ?12 
    uint8_t Day;   ///< valid range: 01 ?31, consistent with associated month/year 
} BioAPI_DATE;

#define BioAPI_NO_YEAR_AVAILABLE  (0)
#define BioAPI_NO_MONTH_AVAILABLE (0)
#define BioAPI_NO_DAY_AVAILABLE   (0)
// {::NOTE::} additional helper macro  (not defined in the standard)
#define BioAPIRI_NO_DATE_AVAILABLE  {BioAPI_NO_YEAR_AVAILABLE,BioAPI_NO_MONTH_AVAILABLE,BioAPI_NO_DAY_AVAILABLE}

// 7.52 BioAPI_TIME
/// Defines the time when the BIR was created.
/// NOTE: The condition NO_VALUE_AVAILABLE is indicated by setting all fields to ?9? When used within the
/// Creation DTG within a BIR header, if no time information is available, then the NO_TIME_AVAILABLE value shall be
/// used.
typedef struct bioapi_time {
    uint8_t Hour;    ///< valid range: 00 ?23 
    uint8_t Minute ; ///< valid range: 00 ?59 
    uint8_t Second ; ///< valid range: 00 ?59 
} BioAPI_TIME;

#define BioAPI_NO_HOUR_AVAILABLE   (99)
#define BioAPI_NO_MINUTE_AVAILABLE (99)
#define BioAPI_NO_SECOND_AVAILABLE (99)
// {::NOTE::} additional helper macro  (not defined in the standard)
#define BioAPIRI_NO_TIME_AVAILABLE   {BioAPI_NO_HOUR_AVAILABLE, BioAPI_NO_MINUTE_AVAILABLE, BioAPI_NO_SECOND_AVAILABLE}


// {::NOTE::} additional helper macro  (not defined in the standard)
// A const that indicates the default timeout in BioAPI calls that have the timeout parameter
#define BioAPIRI_DEFAULT_TIMEOUT (-1)


/*****************************************************************************
 * BIR data types.
******************************************************************************/

// 7.10 BioAPI_BIR_HANDLE
/// A handle to refer to a BioAPI BIR that exists within a BSP.
/// NOTE: A handle that is a pointer to a BIR is a positive non-zero value. Other values of BioAPI_BIR_HANDLE are
/// reserved for exception indications, currently only minus 1 and minus 2.

typedef int32_t BioAPI_BIR_HANDLE;

#define BioAPI_INVALID_BIR_HANDLE     (-1)
#define BioAPI_UNSUPPORTED_BIR_HANDLE (-2)


// 7.6  BioAPI_BIR_BIOMETRIC_DATA_FORMAT
/// Defines the format of the data contained within the “opaque?data block (BDB) of the BioAPI BIR,
/// BiometricData element.
/// NOTE: This structure is primarily used within a BIR header; however, it is also used as an input parameter for
/// functions that capture biometric data. BioAPI_DONT_CARE (corresponding to a BIR Biometric Data Format value of
/// 0x00000000) is used as a function parameter when the application allows the BSP to determine which format to use
/// in returning captured data. This value is never to be used in the BIR header.

typedef struct bioapi_bir_biometric_data_format {
    uint16_t FormatOwner; ///<  assigned and registered by the CBEFF Registration Authority.  
    uint16_t FormatType;  ///<  assigned by the Format Owner and may optionally be registered. 
} BioAPI_BIR_BIOMETRIC_DATA_FORMAT;

// 7.7 BioAPI_BIR_BIOMETRIC_PRODUCT_ID
/// Provides the product identifier (PID) for the BSP that generated the BDB in the BIR (the BiometricData
/// element).
typedef struct bioapi_bir_biometric_product_ID {
    uint16_t ProductOwner;
    uint16_t ProductType;
} BioAPI_BIR_BIOMETRIC_PRODUCT_ID;

#define BioAPI_NO_PRODUCT_OWNER_AVAILABLE (0x0000)
#define BioAPI_NO_PRODUCT_TYPE_AVAILABLE  (0x0000)
// {::NOTE::} additional helper macro  (not defined in the standard)
#define BioAPIRI_NO_BIR_BIOMETRIC_PRODUCT_ID_AVAILABLE {BioAPI_NO_PRODUCT_OWNER_AVAILABLE, BioAPI_NO_PRODUCT_TYPE_AVAILABLE}

// 7.8 BioAPI_BIR_BIOMETRIC_TYPE
/// A mask that describes the set of biometric types (factors) contained within a BioAPI BIR or supported by a BSP.
/// NOTE 1: “MULTIPLE?is used to indicate that the biometric samples contained within the BDB (BIR BiometricData)
/// include biometric samples from more than one type of biometric sensor unit (e.g., fingerprint and facial data).
/// Location of the individual samples within the BDB is specified by the Format Owner and identified by the value of the
/// Format Type.
/// NOTE 2: The condition NO_VALUE_AVAILABLE is indicated by setting the value to zero. BIRs that are not
/// originally created by BioAPI BSPs should use this value when transformed into a BioAPI BIR if Biometric Type
/// information is not available in the original source record. Transformed BIRs whose biometric type does not
/// correspond to one of the defined types shall use the value for OTHER.
/// NOTE 3: The BioAPI BIR Biometric Type corresponds to the “CBEFF_BDB_biometric_type?in ISO/IEC 19785-1.

typedef uint32_t BioAPI_BIR_BIOMETRIC_TYPE;

#define BioAPI_NO_TYPE_AVAILABLE       (0x00000000)
#define BioAPI_TYPE_MULTIPLE           (0x00000001)
#define BioAPI_TYPE_FACIAL_FEATURES    (0x00000002)
#define BioAPI_TYPE_VOICE              (0x00000004)
#define BioAPI_TYPE_FINGERPRINT        (0x00000008)
#define BioAPI_TYPE_IRIS               (0x00000010)
#define BioAPI_TYPE_RETINA             (0x00000020)
#define BioAPI_TYPE_HAND_GEOMETRY      (0x00000040)
#define BioAPI_TYPE_SIGNATURE_DYNAMICS (0x00000080)
#define BioAPI_TYPE_KEYSTOKE_DYNAMICS  (0x00000100)
#define BioAPI_TYPE_LIP_MOVEMENT       (0x00000200)
#define BioAPI_TYPE_THERMAL_FACE_IMAGE (0x00000400)
#define BioAPI_TYPE_THERMAL_HAND_IMAGE (0x00000800)
#define BioAPI_TYPE_GAIT               (0x00001000)
#define BioAPI_TYPE_OTHER              (0x40000000)
#define BioAPI_TYPE_PASSWORD           (0x80000000)

// 7.9 BioAPI_BIR_DATA_TYPE
/// This data type is used for three different purposes:
/// a) it identifies the type of biometric sample (raw, intermediate, or processed) that is contained in the BDB;
/// b) it identifies whether the BioAPI BIR is encrypted and/or signed;
/// c) it identifies whether or not an index value is included as part of the BIR header.
/// NOTE: If the BIR has been encrypted by a BSP, it may not be readable by an application or by another BSP.
///
/// Exactly one of the three flags "raw", "intermediate" and "processed" shall be set. If a BIR carrying a
/// BIR data type with multiple flags set is passed to the BioAPI Framework in a parameter of a function call, a
/// BioAPIERR_INVALID_BIR error shall be returned.
/// NOTE: BIRs that are not originally created by a BioAPI BSP but have been transformed from another data format
/// and for which sample type information is not available may not have set a flag. (BioAPI BSPs set one of the three
/// flags.)
///
/// Each of the flags "encrypted" and "signed" may or may not be set.
/// The ‘index?flag shall be set if an index is present in the BIR header and not set if no index is present
/// in the BIR header.
///
/// NOTE: The BioAPI BIR Data Type corresponds to a combination of the “CBEFF_BDB_processed_level?
typedef uint8_t BioAPI_BIR_DATA_TYPE;

#define BioAPI_BIR_DATA_TYPE_RAW          (0x01)
#define BioAPI_BIR_DATA_TYPE_INTERMEDIATE (0x02)
#define BioAPI_BIR_DATA_TYPE_PROCESSED    (0x04)
#define BioAPI_BIR_DATA_TYPE_ENCRYPTED    (0x10)
#define BioAPI_BIR_DATA_TYPE_SIGNED       (0x20)
#define BioAPI_BIR_INDEX_PRESENT          (0x80)


// 7.49 BioAPI_QUALITY
/// A value indicating the relative quality of the BDB. 
/// The performance of biometrics varies with the quality of the biometric sample. Since a universally
/// accepted definition of quality does not exist, BioAPI has defined the following structure with the goal of
/// relatively quantifying the effect of quality on usage of the BIR (as envisioned by the BSP implementer). The
/// scores as reported by the BSP are based on the purpose (BIR_PURPOSE) indicated by the application (e.g.,
/// Capture for Enroll, Capture for Verify Only, Capture for Identify Only, etc.). Additionally, the demands upon
/// the biometric vary based on the actual customer application and/or environment (i.e., a particular application
/// usage may require higher quality samples than would normally be required by less demanding applications).
///
/// Quality measurements are reported as an integral value in the range 0-100 except as follows:
/// Value of ?1? BioAPI_QUALITY was not set by the BSP (reference the BSP implementer’s
/// documentation for an explanation).
/// Value of ?2? BioAPI_QUALITY is not supported by the BSP.
/// 
/// There are two objectives in providing BioAPI_QUALITY feedback to the biometric application:
///         a) The primary objective is to have the BSP inform the application how suitable the biometric sample is for
///         the purpose (BioAPI_PURPOSE) specified by the application (as intended by the BSP implementer
///         based on the use scenario envisioned by that BSP implementer).
///         d) The secondary objective is to provide the application with relative results (e.g., current sample is
///         better/worse than previous sample).
/// Quality scores in the range 0-100 have the following general interpretation:
///         0-25: UNACCEPTABLE: The BDB cannot be used for the purpose specified by the application
///                 (BioAPI_PURPOSE). The BDB needs to be replaced using one or more new biometric
///                 samples.
///         26-50: MARGINAL: The BDB will provide poor performance for the purpose specified by the
///                 application (BioAPI_PURPOSE) and in most application environments will compromise the
///                 intent of the application. The BDB needs to be replaced using one or more new biometric
///                 samples.
///         51-75: ADEQUATE: The biometric data will provide good performance in most application
///                 environments based on the purpose specified by the application (BioAPI_PURPOSE). The
///                 application should attempt to obtain higher quality data if the application developer anticipates
///                 demanding usage.
///         76-100: EXCELLENT: The biometric data will provide good performance for the purpose specified by
///                 the application (BioAPI_BIR_PURPOSE).
/// NOTE: The BioAPI Quality corresponds to the “CBEFF_BDB_quality?in ISO/IEC 19785-1.

typedef  int8_t  BioAPI_QUALITY;

// {::NOTE::} additional helper macro  (not defined in the standard)
// These are specified in the text but no identifiers are offered
#define BioAPIRI_QUALITY_NOTSET           (-1)
#define BioAPIRI_QUALITY_UNSUPPORTED      (-2)
#define BioAPIRI_QUALITY_MIN              0
#define BioAPIRI_QUALITY_MAX              100
#define BioAPIRI_QUALITY_MAX_UNACCEPTABLE 25
#define BioAPIRI_QUALITY_MAX_MARGINAL     50
#define BioAPIRI_QUALITY_MAX_ADEQUATE     75
#define BioAPIRI_QUALITY_MAX_EXCELLENT    100



// 7.12 BioAPI_BIR_PURPOSE
/// 7.12.1 A value which defines the purpose for which the BioAPI BIR is intended (when used as an input to a
/// BioAPI function) or is suitable (when used as an output from a BioAPI function or within the BIR header).
/// NOTE: The condition NO_VALUE_AVAILABLE is indicated by setting the value to zero. This value is used only for
/// BIRs that are not originally generated by a BioAPI BSP, but originate from another source and have been
/// transformed into a BioAPI BIR. BSPs shall not use this value.
/// 7.12.2 The Purpose value is utilized in two ways. First, it is used as an input parameter to allow the
/// application to indicate to the BSP the purpose for which the resulting BIR is intended, thus allowing the BSP to
/// perform the appropriate capturing and/or processing to create the proper BIR for this purpose. The second
/// use is within the BIR header to indicate to the application (or to the BSP during subsequent operations) what
/// purpose the BIR is suitable for. For example, some BSPs use different BDB formats depending on whether
/// the data is to be used for verification or identification, the latter generally including additional information to
/// enhance speed or accuracy. Similarly, many BSPs use different data formats depending on whether the data
/// is to be used as a sample for immediate verification or as a reference template for future matching (i.e.,
/// enrollment).
/// 7.12.3 Restrictions on the use of BIR data of a particular purpose include:
/// a) All purposes are valid in the BIR header.
/// b) Purposes of Verify and Identify are only valid as input to the Capture function.
/// c) Purposes of Enroll, Enroll_for_Verification_Only, and Enroll_for_Identification_Only are only valid as
/// input to the Capture, Enroll, and Import functions.
/// d) The Audit purpose is not valid as input to any function, but is only used in the BIR header.
/// e) The Process, CreateTemplate, and ProcessWithAuxData functions do not have Purpose as an
/// input parameter, but read the Purpose field from the BIR header of the input CapturedBIR.
/// f) The Process function may accept as input any intermediate BIR with a Purpose of Verify or Identify,
/// and shall output only BIRs with the same purpose as the input BIR.
/// g) The CreateTemplate function may accept as input any intermediate BIR with a Purpose of Enroll,
/// Enroll_for_Verification_Only, or Enroll_for_Identification_Only, and shall output only BIRs with the
/// same Purpose as the input BIR.
/// h) If a BIR is suitable for enrollment for either subsequent verification or subsequent identification, then
/// the output BIR shall have a Purpose of Enroll.
/// NOTE: The BioAPI BIR Purpose in a BIR header corresponds to the “CBEFF_BDB_purpose?in ISO/IEC
/// 19785-1.
typedef uint8_t BioAPI_BIR_PURPOSE;

#define BioAPI_PURPOSE_VERIFY                         (1)
#define BioAPI_PURPOSE_IDENTIFY                       (2)
#define BioAPI_PURPOSE_ENROLL                         (3)
#define BioAPI_PURPOSE_ENROLL_FOR_VERIFICATION_ONLY   (4)
#define BioAPI_PURPOSE_ENROLL_FOR_IDENTIFICATION_ONLY (5)
#define BioAPI_PURPOSE_AUDIT                          (6)
#define BioAPI_NO_PURPOSE_AVAILABLE                   (0)

// 7.13 BioAPI_BIR_SECURITY_BLOCK_FORMAT
/// Defines the format of the data contained within the security block (SB) of the BioAPI BIR, BiometricData
/// element.
/// NOTE 1: If neither the ‘encrypt?or ‘signed?flags are set within the BioAPI_BIR_DATA_TYPE field of the BIR Header,
/// then the SecurityFormatOwner and SecurityFormatType are each set to 0x00 and no security block is present.
/// NOTE2: SecurityFormatOwner values are assigned and registered by the CBEFF Registration Authority. Security
/// Format Type is assigned by the Security Format Owner and may optionally be registered. Registration authority
/// information is located in ISO/IEC 19875-2.
/// NOTE 3: SecurityFormatIDs are analogous to Format IDs and the registration process is the same. A single vendor
/// can register for one Format/Product/Security Owner value that can be used in all associated fields.
/// NOTE 4: The content of the Security Block itself may include a digital signature or message authentication code
/// (calculated on the BIR Header + BDB), BDB encryption parameters (e.g., encryption algorithm, key length), and/or
/// BIR integrity parameters (e.g., algorithm ID, keyname, version).
/// NOTE 5: The BioAPI BIR Security Block Format in a BIR header corresponds to the “CBEFF_SB_format_owner?
/// and “CBEFF_SB_format_type?in ISO/IEC 19785-1.
typedef struct bioapi_bir_security_block_format {
    uint16_t SecurityFormatOwner;
    uint16_t SecurityFormatType;
} BioAPI_BIR_SECURITY_BLOCK_FORMAT;
// {::NOTE::} additional helper macro  (not defined in the standard)
#define BioAPIRI_NO_BIR_SECURITY_BLOCK_FORMAT_AVAILABLE {0,0}


// 7.14 BioAPI_BIR_SUBTYPE
/// 7.14.1 This identifies a subtype within the BDB type (specified in the BioAPI_BIR_Biometric_Type). Its
/// values and their meaning are defined by the specifier of that BDB type.
/// 7.14.2 Each of the feature flags "left" and "right" may or may not be set (zero, one, or both).
/// 7.14.3 Either none or exactly one of the five finger subtypes may be set.
/// 
/// NOTE 1: The condition NO_VALUE_AVAILABLE is indicated by setting the value to zero. BIRs that are not
/// originally created by a BioAPI BSP but have been transformed from another data format and for which subtype
/// information is not available may use this value.
/// NOTE 2: The BioAPI BIR Subtype corresponds to the “CBEFF_BDB_biometric_subtype?in ISO/IEC 19785-1.
/// NOTE 3: This structure is primarily used within a BIR header; however, it is also used as an input parameter for
/// functions that capture biometric data. The NO_SUBTYPE_AVAILABLE value is used in the BIR header when
/// either this field is not applicable or information is not available. BioAPI_NO_SUBTYPE_AVAILABLE is also used 
/// as a function parameter when the application allows the BSP to determine which subtype is to be captured.

typedef uint8_t BioAPI_BIR_SUBTYPE;

#define BioAPI_BIR_SUBTYPE_LEFT          (0x01)
#define BioAPI_BIR_SUBTYPE_RIGHT         (0x02)
#define BioAPI_BIR_SUBTYPE_THUMB         (0x04)
#define BioAPI_BIR_SUBTYPE_POINTERFINGER (0x08)
#define BioAPI_BIR_SUBTYPE_MIDDLEFINGER  (0x10)
#define BioAPI_BIR_SUBTYPE_RINGFINGER    (0x20)
#define BioAPI_BIR_SUBTYPE_LITTLEFINGER  (0x40)
#define BioAPI_BIR_SUBTYPE_MULTIPLE      (0x80)
#define BioAPI_NO_SUBTYPE_AVAILABLE      (0x00)

// 7.25 BioAPI_DTG
/// Defines the date and time when the BIR was created.
/// NOTE: The BioAPI DTG in a BIR header corresponds to the “CBEFF_creation_date?in ISO/IEC 19785-1.
typedef struct bioapi_DTG {
    BioAPI_DATE Date;
    BioAPI_TIME Time;
} BioAPI_DTG;


// 7.11 BioAPI_BIR_HEADER
/// Standard information which describes the content of the opaque biometric data (BDB) that follows. This
/// information is readable by the application and is provided to allow it to make processing and routing decisions
/// regarding the BIR. The header is not encrypted by the BSP.
/// NOTE 1: The BioAPI BIR Header corresponds to the SBH in CBEFF, ISO/IEC 19785-1.
/// NOTE 2: Expiration date corresponds to the ‘Valid to?portion of the “CBEFF_BDB_validity_period?in ISO/IEC
/// 19785-1. The Index field corresponds to the “CBEFF_BDB_index?in ISO/IEC 19785-1.
/// NOTE 3: It is possible that a BioAPI BIR may exist that has not been created by a BioAPI BSP but has been
/// transformed from another data format. In this case, some of the header fields that are optional in CBEFF (ISO/IEC
/// 19785-1) but required by BioAPI may not be present. For this reason, NO_VAUE_AVAILABLE or default values
/// have been identified for these fields (within their corresponding data structures). However, all BIRs created by
/// BioAPI BSPs shall include valid data for these fields and shall not use the NO_VALUE_AVAILABLEW value. (The
/// exception to this is BioAPI_Quality, which is optional in the BioAPI BIR header.) If such a non-BioAPI generated BIR
/// is provided as an input parameter to a BioAPI BSP, the BSP may return an “Invalid BIR?error.
/// NOTE 4: The storage format for the BIR includes an explicit length field, which is not necessary in the C structure.
/// See Annex B for the BIR storage format.
typedef struct bioapi_bir_header {
    BioAPI_VERSION                   HeaderVersion;
    BioAPI_BIR_DATA_TYPE             Type;
    BioAPI_BIR_BIOMETRIC_DATA_FORMAT Format;
    BioAPI_QUALITY                   Quality;
    BioAPI_BIR_PURPOSE               Purpose;
    BioAPI_BIR_BIOMETRIC_TYPE        FactorsMask;
    BioAPI_BIR_BIOMETRIC_PRODUCT_ID  ProductID;
    BioAPI_DTG                       CreationDTG;
    BioAPI_BIR_SUBTYPE               Subtype;
    BioAPI_DATE                      ExpirationDate;
    BioAPI_BIR_SECURITY_BLOCK_FORMAT SBFormat;
    BioAPI_UUID                      Index;
} BioAPI_BIR_HEADER;


// 7.4  BioAPI_BIR
/// A container for biometric data. A BioAPI_BIR consists of 
/// a BioAPI_BIR_HEADER, a BDB, and an optional SB. 
/// The BDB may contain raw sample data, partially processed (intermediate) data, 
/// or completely processed data. The BioAPI_BIR may be used to enroll a user 
/// (thus being stored persistently), or may be used to verify or identify a user 
/// (thus being used transiently). 
/// The BDB and SB are an integral number of octets and are of variable length, 
/// up to 2**32-1 octets. If the SB contains a signature, it is calculated on 
/// the combined BioAPI_BIR_Header and BDB. 
typedef struct bioapi_bir {
    BioAPI_BIR_HEADER   Header;
    BioAPI_DATA         BiometricData; ///< type is self delimiting 
    BioAPI_DATA         SecurityBlock; ///< SecurityBlock.Data=NULL if no SB 
} BioAPI_BIR;


// 7.5  BioAPI_BIR_ARRAY_POPULATION

/// An array of BIRs, generally used during identification operations (as input to Identify or IdentifyMatch).
typedef struct bioapi_bir_array_population {
    uint32_t NumberOfMembers;
    BioAPI_BIR  *Members; ///< A pointer to an array of BIRs 
} BioAPI_BIR_ARRAY_POPULATION;





/*****************************************************************************
 * BIR database related types.
 *****************************************************************************/

// 7.21 BioAPI_DB_ACCESS_TYPE
/// This bitmask describes a biometric application's desired level of access to a BSP-controlled BIR database.
/// The BSP may use the mask to determine what lock to obtain on the BIR database.
typedef uint32_t BioAPI_DB_ACCESS_TYPE;

#define BioAPI_DB_ACCESS_READ  (0x00000001)
#define BioAPI_DB_ACCESS_WRITE (0x00000002)

// 7.22 BioAPI_DB_MARKER_HANDLE
/// A marker handle.
/// A marker is an internal (not standardized) data structure managed by a BSP, which dynamically points to a
/// record in an open BSP-controlled BIR database. A marker handle is created and returned to a biometric
/// application by the functions BioAPI_DbOpen and BioAPI_DbGetBIR. The internal state of the marker
/// includes the open database handle and also the position of a record in that open database. All markers (and
/// their handles) held by a biometric application to an open BIR database become invalid when the database is
/// closed by the biometric application.
typedef uint32_t BioAPI_DB_MARKER_HANDLE;

//{ TRACE
// {::NOTE::} the standard doesn't define a value for an invalid marker handle
//#define BioAPI_DB_MARKER_INVALID_HANDLE (BioAPI_DB_MARKER_HANDLE)(-1)
//} TRACE


// 7.23 BioAPI_DB_HANDLE
/// A handle to an open BIR database initially provided by a BSP to a biometric application and later used by that
/// application to address the database through the BSP.
typedef int32_t BioAPI_DB_HANDLE, *BioAPI_DB_HANDLE_PTR;

#define BioAPI_DB_INVALID_HANDLE   (-1)
#define BioAPI_DB_DEFAULT_HANDLE   (0)
#define BioAPI_DB_DEFAULT_UUID_PTR (NULL)

// 7.24 BioAPI_DBBIR_ID
/// A structure providing the handle to a BIR database managed by a BSP, and the UUID of a BIR in that database.
typedef struct bioapi_dbbir_id {
    BioAPI_DB_HANDLE DbHandle;
    BioAPI_UUID KeyValue;
} BioAPI_DBBIR_ID;



/*****************************************************************************
 * BioAPI biometric operations supporting types.
 *****************************************************************************/

// 7.43 BioAPI_INPUT_BIR_FORM
/// A value indicating the form/method by which a BIR is provided.

typedef uint8_t BioAPI_INPUT_BIR_FORM;

#define BioAPI_DATABASE_ID_INPUT (1)
#define BioAPI_BIR_HANDLE_INPUT  (2)
#define BioAPI_FULLBIR_INPUT     (3)


// 7.42 BioAPI_INPUT_BIR
/// A structure used to input a BIR to the API. Such input can be in one of three forms:
/// a) a BIR Handle;
/// b) a key to a BIR in a database controlled by the BSP. If the DbHandle is zero, a database selected by
/// the BSP is assumed. [A DbHandle is returned when a BIR database is opened];
/// c) an actual BIR.
typedef struct bioapi_input_bir {
    BioAPI_INPUT_BIR_FORM Form;
    union {
    BioAPI_DBBIR_ID *BIRinDb;
    BioAPI_BIR_HANDLE *BIRinBSP;
    BioAPI_BIR *BIR;
    } InputBIR;
} BioAPI_INPUT_BIR;


// 7.40 BioAPI_IDENTIFY_POPULATION_TYPE
/// A value indicating the method of BIR input to an Identify or IdentifyMatch operation, 
/// whether it is via a passed-in array or a pointer to a database.
typedef uint8_t BioAPI_IDENTIFY_POPULATION_TYPE;
#define BioAPI_DB_TYPE           (1)
#define BioAPI_ARRAY_TYPE        (2) 
#define BioAPI_PRESET_ARRAY_TYPE (3)


// 7.39 BioAPI_IDENTIFY_POPULATION
/// A structure used to identify the set of BIRs to be used as input to an Identify or IdentifyMatch operation.
/// If BioAPI_PRESET_ARRAY_TYPE is specified in BioAPI_IDENTIFY_POPULATION_TYPE,
/// BioAPI_BIR_ARRAY_POPULATION_PTR shall be selected with BIRArray set to NULL.
typedef struct bioapi_identify_population {
    BioAPI_IDENTIFY_POPULATION_TYPE Type;
    union {
    BioAPI_DB_HANDLE *BIRDataBase;
    BioAPI_BIR_ARRAY_POPULATION *BIRArray;
    } BIRs;
} BioAPI_IDENTIFY_POPULATION;


// 7.29 BioAPI_FMR
/// A 32-bit integer value (N) that indicates a probable False Match Rate of N/(231-1). The larger the value, the
/// worse the result. Negative values are used to signal exceptional conditions. The only negative value
/// currently defined is minus one.
// "The larger the value, the worse the result" means the less the data match the larger FMR is returned.
typedef int32_t BioAPI_FMR;

#define BioAPI_NOT_SET (-1)


// 7.17 BioAPI_CANDIDATE
/// One of a set of candidates returned by Identify or IdentifyMatch indicating a successful match.

typedef struct bioapi_candidate {
    BioAPI_IDENTIFY_POPULATION_TYPE Type;
    union {
    BioAPI_UUID *BIRInDataBase;
    uint32_t *BIRInArray;
    } BIR;
    BioAPI_FMR FMRAchieved;
} BioAPI_CANDIDATE;



/*****************************************************************************
 * BioAPI schemas.
 *****************************************************************************/

// 7.46 BioAPI_OPERATIONS_MASK
/// A mask that indicates what operations are supported by the BioAPI service provider.
typedef uint32_t BioAPI_OPERATIONS_MASK;

#define BioAPI_ENABLEEVENTS             (0x00000001)
#define BioAPI_SETGUICALLBACKS          (0x00000002)
#define BioAPI_CAPTURE                  (0x00000004)
#define BioAPI_CREATETEMPLATE           (0x00000008)
#define BioAPI_PROCESS                  (0x00000010)
#define BioAPI_PROCESSWITHAUXBIR        (0x00000020)
#define BioAPI_VERIFYMATCH              (0x00000040)
#define BioAPI_IDENTIFYMATCH            (0x00000080)
#define BioAPI_ENROLL                   (0x00000100)
#define BioAPI_VERIFY                   (0x00000200)
#define BioAPI_IDENTIFY                 (0x00000400)
#define BioAPI_IMPORT                   (0x00000800)
#define BioAPI_PRESETIDENTIFYPOPULATION (0x00001000)
#define BioAPI_DATABASEOPERATIONS       (0x00002000)
#define BioAPI_SETPOWERMODE             (0x00004000)
#define BioAPI_SETINDICATORSTATUS       (0x00008000)
#define BioAPI_GETINDICATORSTATUS       (0x00010000)
#define BioAPI_CALIBRATESENSOR          (0x00020000)
#define BioAPI_UTILITIES                (0X00040000)
#define BioAPI_QUERYUNITS               (0x00100000)
#define BioAPI_QUERYBFPS                (0x00200000)
#define BioAPI_CONTROLUNIT              (0X00400000)

// 7.47 BioAPI_OPTIONS_MASK
/// A mask that indicates what options are supported by the BioAPI Service Provider. Note that optional functions
/// are identified within the BioAPI_OPERATIONS_MASK and not repeated here.
typedef uint32_t BioAPI_OPTIONS_MASK;

/// BioAPI_OPTIONS_MASK flag, indicates that the BSP supports the return of raw/audit data.
#define BioAPI_RAW                  (0x00000001)
/// BioAPI_OPTIONS_MASK flag, the BSP supports the return of a quality value (in the BIR header) for raw biometric data.
#define BioAPI_QUALITY_RAW          (0x00000002)
/// BioAPI_OPTIONS_MASK flag, the BSP supports the return of a quality value (in the BIR header) for intermediate biometric data.
#define BioAPI_QUALITY_INTERMEDIATE (0x00000004)
/// BioAPI_OPTIONS_MASK flag, the BSP supports the return of quality value (in the BIR header) for processed biometric data.
#define BioAPI_QUALITY_PROCESSED    (0x00000008)

/// BioAPI_OPTIONS_MASK flag, the BSP supports application control of the GUI.
#define BioAPI_APP_GUI              (0x00000010)
/// If set, the BSP provides GUI streaming data.
#define BioAPI_APP_GUI_STREAMING    (0x00000020)

/// BioAPI_OPTIONS_MASK flag, the BSP supports the detection of the presence a biometric characteristic at the biometric sensor.
#define BioAPI_SOURCEPRESENT        (0x00000040)
/// BioAPI_OPTIONS_MASK flag, the BSP supports payload carry (accepts payload during Enroll/CreateTemplate and returns payroll
/// upon successful Verify/VerifyMatch).
#define BioAPI_PAYLOAD              (0x00000080)
/// BioAPI_OPTIONS_MASK flag, the BSP returns signed BIRs.
#define BioAPI_BIR_SIGN             (0x00000100)
/// BioAPI_OPTIONS_MASK flag, the BSP returns encrypted BIRs (BDB portion).
#define BioAPI_BIR_ENCRYPT          (0x00000200)
/// BioAPI_OPTIONS_MASK flag, the BSP updates any provided input reference template as part of the enrollment or template creation
/// operation.
#define BioAPI_TEMPLATEUPDATE       (0x00000400)
/// BioAPI_OPTIONS_MASK flag, the BSP supports BIR adaptation in the return parameters of a Verify or VerifyMatch operation.
#define BioAPI_ADAPTATION           (0x00000800)
/// BioAPI_OPTIONS_MASK flag, the BSP supports binning (in Identify and IdentifyMatch operations).
#define BioAPI_BINNING              (0x00001000)
/// BioAPI_OPTIONS_MASK flag, the BSP is supporting a self-contained device.
#define BioAPI_SELFCONTAINEDDEVICE  (0x00002000)
/// BioAPI_OPTIONS_MASK flag, the BSP directly supports matching on a smartcard.
#define BioAPI_MOC                  (0x00004000)
/// BioAPI_OPTIONS_MASK flag, the BSP supports specification by the application of which biometric subtype to capture and will act on it.
#define BioAPI_SUBTYPE_TO_CAPTURE   (0x00008000)
/// BioAPI_OPTIONS_MASK flag, the BSP supports management of a sensor unit through a BFP.
#define BioAPI_SENSORBFP            (0x00010000)
/// BioAPI_OPTIONS_MASK flag, the BSP supports management of an archive unit through a BFP.
#define BioAPI_ARCHIVEBFP           (0x00020000)
/// BioAPI_OPTIONS_MASK flag, the BSP supports management of a matching algorithm unit through a BFP.
#define BioAPI_MATCHINGBFP          (0x00040000)
/// BioAPI_OPTIONS_MASK flag, the BSP supports managment of a processing algorithm unit through a BFP.
#define BioAPI_PROCESSINGBFP        (0x00080000)
/// BioAPI_OPTIONS_MASK flag, the BSP returns scores which are coarsely quantized (see clause C.4.6).
#define BioAPI_COARSESCORES         (0x00100000)

// 7.30 BioAPI_FRAMEWORK_SCHEMA
/// The framework schema entry for a BioAPI Framework as recorded in the component registry.
typedef struct bioapi_framework_schema {
    BioAPI_UUID FrameworkUuid;    // UUID of the Framework component.
    BioAPI_STRING FwDescription;  // description of the Framework.
    uint8_t *Path;                // path of the Framework code, including the filename. The path may be a URL.
    BioAPI_VERSION SpecVersion;   // version of the BioAPI specification to which the Framework was implemented.
    BioAPI_STRING ProductVersion; // The version string of the Framework software.
    BioAPI_STRING Vendor;         // name of the Framework vendor.
    BioAPI_UUID FwPropertyId;     // UUID of the format of the following Framework property.
    BioAPI_DATA FwProperty;       // Address and length of a memory buffer containing the Framework property..
} BioAPI_FRAMEWORK_SCHEMA;

// 7.16 BioAPI_BSP_SCHEMA
/// Information about a BSP component  maintained in the BioAPI component registry.
typedef struct bioapi_bsp_schema {
    BioAPI_UUID BSPUuid; ///<  UUID of the BSP
    BioAPI_STRING BSPDescription; ///<  description of the BSP
    uint8_t *Path; ///<  Path of the BSP file, including the filename. The path may be a URL.
    BioAPI_VERSION SpecVersion; ///<  version of the BioAPI specification to which the BFP was implemented.
    BioAPI_STRING ProductVersion; ///<  The version string of the BSP software.
    BioAPI_STRING Vendor; ///<  the name of the BSP vendor.
    BioAPI_BIR_BIOMETRIC_DATA_FORMAT *BSPSupportedFormats; ///<  supported BDB formats.
    uint32_t NumSupportedFormats; ///<  Number of supported formats contained in BspSupportedFormats.
    BioAPI_BIR_BIOMETRIC_TYPE FactorsMask; ///<  biometric types are supported by the BSP.
    BioAPI_OPERATIONS_MASK Operations; ///<  operations are supported by the BSP.
    BioAPI_OPTIONS_MASK Options; ///<  options are supported by the BSP.
    BioAPI_FMR PayloadPolicy; ///<  minimum FMR value to release the payload after successful verification.
    uint32_t MaxPayloadSize; ///<  Maximum payload size (in bytes) that the BSP can accept.
    int32_t  DefaultVerifyTimeout; ///<  Milliseconds when no timeout is specified by the application.
    int32_t  DefaultIdentifyTimeout;
    int32_t  DefaultCaptureTimeout;
    int32_t  DefaultEnrollTimeout;
    int32_t  DefaultCalibrateTimeout;
    uint32_t  MaxBSPDbSize; ///<  Maximum size of a BSP-controlled BIR database.
    uint32_t  MaxIdentify; ///<  Largest population. Unlimited = FFFFFFFF.
}BioAPI_BSP_SCHEMA;



// 7.2 BioAPI_BFP_LIST_ELEMENT
/// Identifies a BFP, giving its category and UUID. A list is returned by a BSP when 
/// queried for the installed BFPs that it supports.
typedef struct _bioapi_bfp_list_element {
    BioAPI_CATEGORY BFPCategory; ///< Defines the category of the BioAPI Unit that it supports.
    BioAPI_UUID BFPUuid; ///< UUID of the BFP in the component registry. 
}BioAPI_BFP_LIST_ELEMENT;


// 7.3  BioAPI_BFP_SCHEMA
/// Information about a BFP maintained in the BioAPI component registry.
typedef struct bioapi_bfp_schema {
    BioAPI_UUID BFPUuid; ///<  UUID of the BFP.
    BioAPI_CATEGORY BFPCategory; ///<  Category of the BFP identified by the BFPUuid.
    BioAPI_STRING BFPDescription; ///<  A NUL-terminated string containing a text description of the BFP.
    uint8_t *Path; ///<  Path of the BFP file, including the filename. The path may be a URL.
    BioAPI_VERSION SpecVersion; ///<  version of the FPI specification to which the BFP was implemented.
    BioAPI_STRING ProductVersion; ///<  The version string of the BFP software.
    BioAPI_STRING Vendor; ///<  the name of the BFP vendor.
    BioAPI_BIR_BIOMETRIC_DATA_FORMAT *BFPSupportedFormats; ///<  A pointer to an array of supported BDB formats.
    uint32_t NumSupportedFormats; ///<  Number of supported formats contained in BfpSupportedFormats.
    BioAPI_BIR_BIOMETRIC_TYPE FactorsMask; ///<  A mask which indicates which biometric types are supported by the BFP.
    BioAPI_UUID BFPPropertyID; ///<  UUID of the format of the following BFP property.
    BioAPI_DATA BFPProperty; ///<  Address and length of a memory buffer containing the BFP property. The format and content can either be 
                             ///<  specified by a vendor or can be specified in a related standard.
//{ TRACE
    // {::NOTE::} these are parameters, identical to those in BSP schema, are not part of the BFP schema
    //BioAPI_OPERATIONS_MASK Operations; // indicates which operations are supported by the BFP
    //BioAPI_OPTIONS_MASK Options; // indicates which options are supported by the BFP
    //BioAPI_FAR PayloadPolicy;  // Threshold to release the payload 
    //uint32_t MaxPayloadSize; // Maximum payload size (in bytes) that the BSP can accept
    //int32_t DefaultCaptureTimeout; // milliseconds for capture operations when no timeout is specified by the application.
    //uint32_t MaxBspDbSize; // Maximum size of BSP owned BIR database.  If zero, no database exists
    //uint32_t MaxIdentify; // Largest population supported by the identify function.  Unlimited = FFFFFFF
//} TRACE
}BioAPI_BFP_SCHEMA;


// 7.53 BioAPI_UNIT_ID
/// 32-bit integer assigned to a BioAPI Unit by a BSP that manages (directly or indirectly) the BioAPI Unit.
/// When during BioAPI_BSPAttach the UnitID is set to zero the BSP will use the default BioAPI Unit of the given category. 
/// If a particular category is not listed also the default BioAPI Unit will be attached by the BSP. 
/// When the UnitID is set to 0xFFFFFFFF the BSP will explicitly not attach a BioAPI Unit of the given category.
typedef uint32_t BioAPI_UNIT_ID, *BioAPI_UNIT_ID_PTR;
#define BioAPI_DONT_CARE    (0x00000000) 
#define BioAPI_DONT_INCLUDE (0xFFFFFFFF)

// {::NOTE::} other values for UnitIds  (not defined in the standard)
//#define UNIT_UNSPECIFIED 0xFFFFFFFD
//#define UNIT_ID_INVALID  0xFFFFFFFE


// 7.54 BioAPI_UNIT_LIST_ELEMENT
/// BioAPI Unit by category and ID. A list of these elements is used to establish an attach session.
typedef struct _bioapi_unit_list_element {
    BioAPI_CATEGORY UnitCategory; ///<  Defines the category of the BioAPI Unit.
    BioAPI_UNIT_ID UnitId; ///<  The ID of a BioAPI Unit to be used in this attach session. 
                           ///<  This will be created by the BSP uniquely.
}BioAPI_UNIT_LIST_ELEMENT;



// 7.55 BioAPI_UNIT_SCHEMA
/// A BioAPI Unit schema indicates the specific characteristics of the BioAPI Unit.
typedef struct bioapi_unit_schema {
    BioAPI_UUID BSPUuid; ///<  UUID of the BSP supporting this BioAPI Unit
    BioAPI_UUID UnitManagerUuid; ///<  UUID of the component directly managing the Unit (BSP itself or a BFP)
    BioAPI_UNIT_ID UnitId; ///<  ID of the Unit during this attach session, created by the BSP uniquely
    BioAPI_CATEGORY UnitCategory; ///<  Defines the category of the BioAPI Unit
    BioAPI_UUID UnitProperties; ///<  UUID of a set of properties of the BioAPI Unit. 
                                ///<  The set can be either specified by each vendor or following a related standard.
    BioAPI_STRING VendorInformation; ///<  Contains vendor proprietary information.
    uint32_t SupportedEvents; ///<  A mask indicating which types of events are supported by the hardware.
    BioAPI_UUID UnitPropertyID; ///<  UUID of the format of the following structure describing the BioAPI Unit.
                                ///<  The format can be either specified by each vendor or follow a related standard.
    BioAPI_DATA UnitProperty; ///<  A buffer containing vendor or standard information about the BioAPI Unit. 
                              ///<  The memory is allocated by the BSP and has to be freed by the application.
    BioAPI_STRING HardwareVersion; ///<  version number of the hardware.  Empty if not available.
    BioAPI_STRING FirmwareVersion; ///<  version number of the firmware.  Empty if not available.
    BioAPI_STRING SoftwareVersion; ///<  version number of the software (e.g. of the BFP).  Empty if not available.
    BioAPI_STRING HardwareSerialNumber; ///<  vendor defined unique serial number of the hardware component. Empty if not available.
    BioAPI_BOOL AuthenticatedHardware; ///<  A boolean value that indicates whether the hardware component has been authenticated
    uint32_t MaxBSPDbSize; ///<  Maximum size database supported by Unit. If zero, no database exists.
    uint32_t MaxIdentify; ///<  Largest identify population supported by Unit. Unlimited = FFFFFFFF.
} BioAPI_UNIT_SCHEMA;



/*****************************************************************************
 * BioAPI events/callback types
******************************************************************************/

// 7.26 BioAPI_EVENT
/// This enumeration defines the event types that can be raised by a BSP, BFP, or BioAPI Unit. Biometric
/// applications can define event handling callback functions of type BioAPI_EventHandler to receive and
/// manage these events. Callback functions are registered using the BioAPI_BSPLoad function. Example
/// events include the addition (insertion) or removal of a biometric sensor. Events are asynchronous.
/// BioAPI_SOURCE_PRESENT and BioAPI_SOURCE_REMOVED events are generated by devices (sensor
/// units) that can detect when the user may be available to provide a biometric sample (e.g., the user has to
/// place a finger on a fingerprint device). BioAPI_SOURCE_PRESENT indicates that a sample may be available,
/// while BioAPI_SOURCE_REMOVED indicates that a sample is probably no longer available. There is no
/// requirement that these events must occur in pairs; several BioAPI_SOURCE_PRESENT events may occur in
/// succession.
typedef uint32_t BioAPI_EVENT;

#define BioAPI_NOTIFY_INSERT         (1)
#define BioAPI_NOTIFY_REMOVE         (2)
#define BioAPI_NOTIFY_FAULT          (3)
#define BioAPI_NOTIFY_SOURCE_PRESENT (4)
#define BioAPI_NOTIFY_SOURCE_REMOVED (5)

// 7.27 BioAPI_EVENT_MASK
/// 7.27.1 This type defines a mask with bit positions for each event type. The mask is used to enable/disable
/// event notification, and to indicate what events are supported by a BSP.
/// 7.27.2 Insert events are non-maskable (i.e., cannot be suppressed).
/// NOTE: The INSERT event coming from an attach session of a BSP cannot be masked, because it may occur just
/// after a BSPLoad call, before any EnableEvents call has had any chance to be processed. This is because
/// EnableEvents requires a handle which is provided by BSPAttach, and BSPAttach itself shall follow BSPLoad. An
/// INSERT event will be raised by the BSP on the BSPLoad call if a BioAPI Unit is already "inserted", and this event will
/// reach the application before the application can call EnableEvents.
typedef uint32_t BioAPI_EVENT_MASK;

#define BioAPI_NOTIFY_INSERT_BIT         (0x00000001)
#define BioAPI_NOTIFY_REMOVE_BIT         (0x00000002)
#define BioAPI_NOTIFY_FAULT_BIT          (0x00000004)
#define BioAPI_NOTIFY_SOURCE_PRESENT_BIT (0x00000008)
#define BioAPI_NOTIFY_SOURCE_REMOVED_BIT (0x00000010)



// 7.28 BioAPI_EventHandler
/// This is the event handler interface that an application is required to support if it wishes to receive
/// asynchronous notification of events such as the availability of a biometric sample or a fault detected by a BSP.
/// The event handler process is registered with the BioAPI Framework as part of the BioAPI_BSPLoad function.
/// This is the caller’s event handler for all general BSP events over all of the caller’s attach sessions with the
/// loaded BSP. General event notifications are processed through the BioAPI Framework.
/// The event handler function and any functions invoked (directly or indirectly) by that function shall not issue
/// BioAPI calls. These circular calls may result in deadlock in numerous situations; hence the event handler shall
/// be implemented without using BioAPI services (however, enumeration functions can be used at any time).
/// The BioAPI_EventHandler can be invoked multiple times in response to a single event occurring in the
/// associated BSP. The event handler and the calling application shall track receipt of event notifications and
/// ignore duplicates.
/// If the EventType is BioAPI_NOTIFY_INSERT, then a unit schema shall be provided (that is, UnitSchema shall
/// point to a variable of type BioAPI_UNIT_SCHEMA). Otherwise, UnitSchema shall be NULL.
/// When the application receives a call to an event handler that carries a unit schema, the application shall not
/// call BioAPI_Free to free the memory block containing the unit schema or a memory block pointed to by any of
/// its members.

typedef BioAPI_RETURN (BioAPI *BioAPI_EventHandler) (
    const BioAPI_UUID *BSPUuid, ///<  The UUID of the BSP raising the event.
    BioAPI_UNIT_ID UnitID,      ///<  The unit ID of the BioAPI Unit associated with the event.
    void* AppNotifyCallbackCtx, ///<  The application context specified in BioAPI_BSPLoad( ) 
                                ///<  that established the event handler.
    const BioAPI_UNIT_SCHEMA *UnitSchema, ///<  unit schema if EventType = BioAPI_NOTIFY_INSERT, NULL otherwise
    BioAPI_EVENT EventType);    ///<  The BioAPI_EVENT that has occurred.



/*****************************************************************************
 * GUI supporting types.
 *****************************************************************************/
// 7.31 BioAPI_GUI_BITMAP
/// This structure provides a graphic for display by the application.
/// Bitmap  - a series of 8-bit grayscale pixels (where ?0?= black and ‘FF?= white), 
/// read from left to right, top to bottom, as follows: Table 1.  GUI Bitmap Format

/// Byte Position   Meaning                     Description
/// 0               line 0, pixel 0             first pixel of first line
/// 1               line 0, pixel 1             second pixel of first line
/// ?              ?   
/// width-1         line 0, pixel(width-1)      last pixel of first line
/// width           line 1, pixel 0             first pixel of second line
/// ?              ?   
/// (width*height)-1    line(width?), pixel(height?)  last line, last pixel

/// NOTE:  This is used with the application controlled GUI option.  
/// See BioAPI_GUI_STATE_CALLBACK and BioAPI_GUI_STREAMING_CALLBACK descriptions under 7.36 and 7.37

typedef struct bioapi_gui_bitmap {
    uint32_t Width; /* Width of bitmap in pixels (i.e., number of pixels for each line)*/
    uint32_t Height; /* Height of bitmap in pixels (i.e., number of lines) */
    BioAPI_DATA Bitmap;
} BioAPI_GUI_BITMAP;


// 7.32 BioAPI_GUI_MESSAGE
/// This structure provides a message for display by the application.
/// NOTE: This is used with the application-controlled GUI option. See BioAPI_GUI_STATE_CALLBACK description under 7.36.
typedef uint32_t BioAPI_GUI_MESSAGE;

// 7.33 BioAPI_GUI_PROGRESS
/// A value that indicates the percentage progress (% complete) for an in-progress BSP operation to the
/// application for display purposes.
/// NOTE: This is used with the application-controlled GUI option. See BioAPI_GUI_STATE_CALLBACK description under 7.36.
typedef uint8_t BioAPI_GUI_PROGRESS;

// 7.34 BioAPI_GUI_RESPONSE
/// Return value from the biometric application during a callback operation.
/// NOTE: This is used with the application controlled GUI option. See BioAPI_GUI_STATE_CALLBACK description under 7.36.
typedef uint8_t BioAPI_GUI_RESPONSE;
#define BioAPI_CAPTURE_SAMPLE (1) /* Instruction to BSP to capture sample */
#define BioAPI_CANCEL         (2) /* User cancelled operation */
#define BioAPI_CONTINUE       (3) /* User or application selects to proceed */
#define BioAPI_VALID_SAMPLE   (4) /* Valid sample received */
#define BioAPI_INVALID_SAMPLE (5) /* Invalid sample received */

// 7.35 BioAPI_GUI_STATE
/// A mask that indicates GUI state, and also what other parameter values are provided in the GUI State Callback
/// (this information is provided by the BSP through the GUI State Callback to the application).
/// NOTE: This is used with the application-controlled GUI option. See BioAPI_GUI_STATE_CALLBACK description under 7.36.
typedef uint32_t BioAPI_GUI_STATE;
#define BioAPI_SAMPLE_AVAILABLE  (0x0001) /* Sample captured and available */
#define BioAPI_MESSAGE_PROVIDED  (0x0002) /* BSP provided message for display */
#define BioAPI_PROGRESS_PROVIDED (0x0004) /* BSP provide progress for display */

// 7.36 BioAPI_GUI_STATE_CALLBACK
/// This structure is a function pointer type - a callback function that an application supplies to allow the
/// service provider to pass GUI state information to the application through the Framework, and to receive
/// responses back.
/// Return of a value different from BioAPI_OK will make the calling function (e.g., BioAPI_Enroll) to immediately
/// return to the caller with that value as its error code.
/// Parameters
/// GuiStateCallbackCtx (input) - A generic pointer to context information that was provided by the
///     original requester and is being returned to its originator.
/// GuiState (input) ?an indication of the current state of the BSP with respect to the GUI, plus an
///     indication of what others parameters are available.
/// Response (output) ?A pointer to the response from the application back to the service provider on
///     return from the Callback.
/// Message (input/optional) ?The number of a message to display to the user. Message numbers and
///     message text are not standardized, and are BSP dependent. GuiState indicates if a Message is
///     provided; if not, the parameter is NULL.
/// Progress (input/optional) ?A value that indicates (as a percentage) the amount of progress in the
///     development of a Sample/BIR. The value may be used to display a progress bar. Not all BSPs
///     support a progress indication. GuiState indicates if a sample Progress value is provided in the call; if
///     not, the parameter is NULL.
/// SampleBuffer (input/optional) ?The current sample buffer for the application to display. GuiState
///     indicates if a sample Buffer is provided; if not, the parameter is NULL.

typedef BioAPI_RETURN (BioAPI *BioAPI_GUI_STATE_CALLBACK) (
    void *GuiStateCallbackCtx,
    BioAPI_GUI_STATE GuiState,
    BioAPI_GUI_RESPONSE *Response,
    BioAPI_GUI_MESSAGE Message,
    BioAPI_GUI_PROGRESS Progress,
    const BioAPI_GUI_BITMAP *SampleBuffer);

// 7.37 BioAPI_GUI_STREAMING_CALLBACK
/// This is a function pointer type ?a callback function that a biometric application supplies to allow a
/// BSP to stream data for display, in the form of a sequence of bitmaps, to the application through the
/// Framework.
/// Return of a value different from BioAPI_OK will make the calling function (e.g., BioAPI_Enroll) to immediately
/// return to the caller with that value as its error code.
/// Parameters
/// GuiStreamingCallbackCtx (input) - A generic pointer to context information that was provided by the
///     original requester and is being returned to its originator.
/// Bitmap (input) ?a pointer to the bitmap to be displayed.

typedef BioAPI_RETURN (BioAPI *BioAPI_GUI_STREAMING_CALLBACK) (
    void *GuiStreamingCallbackCtx,
    const BioAPI_GUI_BITMAP *Bitmap);


// 7.41 BioAPI_INDICATOR_STATUS
/// This type is used by a biometric application to get and set device (BioAPI Unit) indicators supported by a BSP.
/// The precise physical form of these indicators (and their availability) is BSP-dependent.
typedef uint8_t BioAPI_INDICATOR_STATUS, *BioAPI_INDICATOR_STATUS_PTR;

#define BioAPI_INDICATOR_ACCEPT  (1)
#define BioAPI_INDICATOR_REJECT  (2)
#define BioAPI_INDICATOR_READY   (3)
#define BioAPI_INDICATOR_BUSY    (4)
#define BioAPI_INDICATOR_FAILURE (5)



/*****************************************************************************
 * Install/configuration/power supporting types.
 *****************************************************************************/

// 7.44 BioAPI_INSTALL_ACTION
/// Specifies the action to be taken during BSP installation operations.

typedef uint32_t  BioAPI_INSTALL_ACTION;
#define BioAPI_INSTALL_ACTION_INSTALL   (1) 
#define BioAPI_INSTALL_ACTION_REFRESH   (2) 
#define BioAPI_INSTALL_ACTION_UNINSTALL (3) 


// 7.45 BioAPI_INSTALL_ERROR
/// A structure which contains additional information regarding an error state 
/// that has occurred during an installation operation.

typedef struct _install_error {
    BioAPI_RETURN ErrorCode;
    BioAPI_STRING ErrorString;
}BioAPI_INSTALL_ERROR;

// 7.48 BioAPI_POWER_MODE
/// An enumeration that specifies the types of power modes the BSP and its attached devices (BioAPI Units) will
/// try to use.

typedef uint32_t BioAPI_POWER_MODE;

/* All functions available */
#define BioAPI_POWER_NORMAL (1)
/* Able to detect (for example) insertion/finger on/person present type of events */
#define BioAPI_POWER_DETECT (2)
/* Minimum mode. All functions off */
#define BioAPI_POWER_SLEEP  (3)


#ifdef __cplusplus
}
#endif

#endif  /* _BIOAPI_TYPE_H_INCLUDED */
