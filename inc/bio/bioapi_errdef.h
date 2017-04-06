#include "bioapi_err.h"

MT_GROUP_EN("11.2.3 General Error Codes")

MT_MESSAGE_EN(
    BioAPI_OK,
    "The operation completed successfully."
)
MT_MESSAGE_EN(
    BioAPIERR_INTERNAL_ERROR,
    "General system error: an operating system or internal state error has occurred and the system may not be in a known state."
)
MT_MESSAGE_EN(
    BioAPIERR_MEMORY_ERROR,
    "A memory error occurred."
)
MT_MESSAGE_EN(
    BioAPIERR_INVALID_POINTER,
    "An input/output function parameter or input/output field inside of a data structure is an invalid pointer."
)
MT_MESSAGE_EN(
    BioAPIERR_INVALID_INPUT_POINTER,
    "An input function parameter or input field in a data structure is an invalid pointer."
)
MT_MESSAGE_EN(
    BioAPIERR_INVALID_OUTPUT_POINTER,
    "An output function parameter or output field in a data structure is an invalid pointer."
)
MT_MESSAGE_EN(
    BioAPIERR_FUNCTION_NOT_SUPPORTED,
    "The function is not implemented by the service provider."
)
MT_MESSAGE_EN(
    BioAPIERR_OS_ACCESS_DENIED,
    "The operating system denied access to a required resource."
)
MT_MESSAGE_EN(
    BioAPIERR_FUNCTION_FAILED,
    "The function failed for an unknown reason."
)
MT_MESSAGE_EN(
    BioAPIERR_INVALID_UUID,
    "Invalid UUID."
)
MT_MESSAGE_EN(
    BioAPIERR_INCOMPATIBLE_VERSION,
    "Version incompatibility."
)
MT_MESSAGE_EN(
    BioAPIERR_INVALID_DATA,
    "The data in an input parameter is invalid."
)
MT_MESSAGE_EN(
    BioAPIERR_UNABLE_TO_CAPTURE,
    "The associated BSP is unable to capture raw samples from the requested device."
)
MT_MESSAGE_EN(
    BioAPIERR_TOO_MANY_HANDLES,
    "The framework has no more space to allocate attachment handles or the associated BSP has no more space to allocate BIR handles."
)
MT_MESSAGE_EN(
    BioAPIERR_TIMEOUT_EXPIRED,
    "The function has been terminated because the timeout value has expired."
)
MT_MESSAGE_EN(
    BioAPIERR_INVALID_BIR,
    "The input BIR is invalid for the purpose required."
)
MT_MESSAGE_EN(
    BioAPIERR_BIR_SIGNATURE_FAILURE,
    "The associated BSP could not validate the signature on the BIR."
)
MT_MESSAGE_EN(
    BioAPIERR_UNABLE_TO_STORE_PAYLOAD,
    "The associated BSP is unable to store the payload."
)
MT_MESSAGE_EN(
    BioAPIERR_NO_INPUT_BIRS,
    "The identify population is NULL."
)
MT_MESSAGE_EN(
    BioAPIERR_UNSUPPORTED_FORMAT,
    "The associated BSP does not support the BDB format."
)
MT_MESSAGE_EN(
    BioAPIERR_UNABLE_TO_IMPORT,
    "The associated BSP was unable to construct a BIR from the input data."
)
MT_MESSAGE_EN(
    BioAPIERR_INCONSISTENT_PURPOSE,
    "The purpose recorded in the BIR and the requested purpose are inconsistent with the function being performed."
)
MT_MESSAGE_EN(
    BioAPIERR_BIR_NOT_FULLY_PROCESSED,
    "The function requires a fully processed BIR."
)
MT_MESSAGE_EN(
    BioAPIERR_PURPOSE_NOT_SUPPORTED,
    "The BSP does not support the requested purpose."
)
MT_MESSAGE_EN(
    BioAPIERR_USER_CANCELLED,
    "User cancelled operation before completion or timeout."
)
MT_MESSAGE_EN(
    BioAPIERR_UNIT_IN_USE,
    "BSP (or BioAPI Unit attached to BSP) is currently being used by another biometric application."
)
MT_MESSAGE_EN(
    BioAPIERR_INVALID_BSP_HANDLE,
    "The given BSP handle is not valid."
)
MT_MESSAGE_EN(
    BioAPIERR_FRAMEWORK_NOT_INITIALIZED,
    "A function has been called without initializing the BioAPI Framework."
)
MT_MESSAGE_EN(
    BioAPIERR_INVALID_BIR_HANDLE,
    "BIR handle is invalid (does not exist or has been released)."
)
MT_MESSAGE_EN(
    BioAPIERR_CALIBRATION_NOT_SUCCESSFUL,
    "The attempted calibration of a sensor unit was not able to be successfully completed."
)
MT_MESSAGE_EN(
    BioAPIERR_PRESET_BIR_DOES_NOT_EXIST,
    "No preset BIR population has been established."
)
MT_MESSAGE_EN(
    BioAPIERR_BIR_DECRYPTION_FAILURE,
    "The BSP could not decrypt an input BIR (and thus was unable to use it for the requested operation)."
)

MT_GROUP_EN("11.2.4 Component Management Error Codes")

MT_MESSAGE_EN(
    BioAPIERR_COMPONENT_FILE_REF_NOT_FOUND,
    "A reference to the component file cannot be obtained."
)
MT_MESSAGE_EN(
    BioAPIERR_BSP_LOAD_FAIL,
    "Framework was unable to successfully load the BSP."
)
MT_MESSAGE_EN(
    BioAPIERR_BSP_NOT_LOADED,
    "BSP for which an action was requested is not loaded."
)
MT_MESSAGE_EN(
    BioAPIERR_UNIT_NOT_INSERTED,
    "BioAPI Unit for which an action was requested is not in the inserted state."
)
MT_MESSAGE_EN(
    BioAPIERR_INVALID_UNIT_ID,
    "An invalid BioAPI Unit ID was requested."
)
MT_MESSAGE_EN(
    BioAPIERR_INVALID_CATEGORY,
    "An invalid category of BFP or BioAPI Unit was requested."
)

MT_GROUP_EN("11.2.5 Database Error Values")

MT_MESSAGE_EN(
    BioAPIERR_INVALID_DB_HANDLE,
    "Invalid database handle."
)
MT_MESSAGE_EN(
    BioAPIERR_UNABLE_TO_OPEN_DATABASE,
    "The associated BSP is unable to open the specified database."
)
MT_MESSAGE_EN(
    BioAPIERR_DATABASE_IS_LOCKED,
    "The database cannot be opened for the access requested because it is locked."
)
MT_MESSAGE_EN(
    BioAPIERR_DATABASE_DOES_NOT_EXIST,
    "The specified database does not exist."
)
MT_MESSAGE_EN(
    BioAPIERR_DATABASE_ALREADY_EXISTS,
    "Create failed because the database already exists."
)
MT_MESSAGE_EN(
    BioAPIERR_INVALID_DATABASE_NAME,
    "Invalid database name."
)
MT_MESSAGE_EN(
    BioAPIERR_RECORD_NOT_FOUND,
    "No record exists with the requested key."
)
MT_MESSAGE_EN(
    BioAPIERR_MARKER_HANDLE_IS_INVALID,
    "The specified marker handle is invalid."
)
MT_MESSAGE_EN(
    BioAPIERR_DATABASE_IS_OPEN,
    "The database is already open."
)
MT_MESSAGE_EN(
    BioAPIERR_INVALID_ACCESS_REQUEST,
    "Unrecognized access type."
)
MT_MESSAGE_EN(
    BioAPIERR_END_OF_DATABASE,
    "End of database has been reached."
)
MT_MESSAGE_EN(
    BioAPIERR_UNABLE_TO_CREATE_DATABASE,
    "The associated BSP cannot create the database."
)
MT_MESSAGE_EN(
    BioAPIERR_UNABLE_TO_CLOSE_DATABASE,
    "The associated BSP cannot close the database."
)
MT_MESSAGE_EN(
    BioAPIERR_UNABLE_TO_DELETE_DATABASE,
    "The associated BSP cannot delete the database."
)
MT_MESSAGE_EN(
    BioAPIERR_DATABASE_IS_CORRUPT,
    "The specified database is corrupt."
)

MT_GROUP_EN("11.2.6.1 General location error codes")

MT_MESSAGE_EN(
    BioAPIERR_LOCATION_ERROR,
    "A general location error."
)
MT_MESSAGE_EN(
    BioAPIERR_OUT_OF_FRAME,
    "Invalid horizontal or vertical position."
)
MT_MESSAGE_EN(
    BioAPIERR_INVALID_CROSSWISE_POSITION,
    "Invalid crosswise position."
)
MT_MESSAGE_EN(
    BioAPIERR_INVALID_LENGTHWISE_POSITION,
    "Invalid lengthwise position."
)
MT_MESSAGE_EN(
    BioAPIERR_INVALID_DISTANCE,
    "Invalid distance."
)

MT_GROUP_EN("11.2.6.2 Specific location error codes")

MT_MESSAGE_EN(
    BioAPIERR_LOCATION_TOO_RIGHT,
    "The position was too far to the right."
)
MT_MESSAGE_EN(
    BioAPIERR_LOCATION_TOO_LEFT,
    "The position was too far to the left."
)
MT_MESSAGE_EN(
    BioAPIERR_LOCATION_TOO_HIGH,
    "The position was too high."
)
MT_MESSAGE_EN(
    BioAPIERR_LOCATION_TOO_LOW,
    "The position was too low."
)
MT_MESSAGE_EN(
    BioAPIERR_LOCATION_TOO_FAR,
    "The position was too far away."
)
MT_MESSAGE_EN(
    BioAPIERR_LOCATION_TOO_NEAR,
    "The position was too near (close)."
)
MT_MESSAGE_EN(
    BioAPIERR_LOCATION_TOO_FORWARD,
    "The position was too far forward."
)
MT_MESSAGE_EN(
    BioAPIERR_LOCATION_TOO_BACKWARD,
    "The position was too far backward."
)

MT_GROUP_EN("11.2.6.3 Quality Error Codes. Quality errors can be returned from any function which receives a BioAPI BIR input.")

MT_MESSAGE_EN(
    BioAPIERR_QUALITY_ERROR,
    "Sample quality is too poor for the operation to succeed."
)
