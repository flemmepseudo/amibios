//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Core/EDK/GUID/StatusCodeDataTypeId.h 3     1/12/12 12:13p Oleksiyy $
//
// $Revision: 3 $
//
// $Date: 1/12/12 12:13p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/EDK/GUID/StatusCodeDataTypeId.h $
// 
// 3     1/12/12 12:13p Oleksiyy
// [TAG]  		EIP75246
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	PI 1.2 Errata C Status Code
// [RootCause]  	PI 1.2 Errata C introduced changies in definitions.
// [Solution]  	Defenitions fixed up to PI 1.2 Errata C.
// [Files]  		AmiStatusCodes.h, StatusCodes.h, StatusCodeDataTypeId.h
// 
// 2     5/13/11 6:32p Oleksiyy
// [TAG]  		EIP56645 
// [Category]  	Improvement
// [Description]  	Status Code PI 1.2 Specification Update
// [Files]  		DebugSupport.h, StatusCodeDataTypeId.h and StatusCodes.h
// 
// 1     5/19/06 11:29p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	StatusCodeDataTypeId.h
//
// Description:	Statuc Code Data Type ID GUIDs
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __STATUS_CODE_DATA_TYPE_GUIDS__H__
#define __STATUS_CODE_DATA_TYPE_GUIDS__H__
#ifdef __cplusplus
extern "C" {
#endif

#include <StatusCodes.h>
//GUID_VARIABLE_DECLARATION(gEfiCallerIdGuid, EFI_STANDARD_CALLER_ID_GUID);

//
// The size of string
//
#define EFI_STATUS_CODE_DATA_MAX_STRING_SIZE  150

//
// This is the max data size including all the headers which can be passed
// as Status Code data. This data should be multiple of 8 byte
// to avoid any kind of boundary issue. Also, sum of this data size (inclusive
// of size of EFI_STATUS_CODE_DATA should not exceed the max record size of
// data hub
//
#define EFI_STATUS_CODE_DATA_MAX_SIZE 200

//
// String Data Type defintion. This is part of Status Code Specification
//
#ifndef EFI_STATUS_CODE_DATA_TYPE_STRING_GUID
#define EFI_STATUS_CODE_DATA_TYPE_STRING_GUID \
  { \
    0x92D11080, 0x496F, 0x4D95, 0xBE, 0x7E, 0x03, 0x74, 0x88, 0x38, 0x2B, 0x0A \
  }
#endif

extern EFI_GUID gEfiStatusCodeDataTypeStringGuid;

//
// This GUID indicates that the format of the accompanying data depends
// upon the Status Code Value, but follows this Specification
//
#ifndef EFI_STATUS_CODE_SPECIFIC_DATA_GUID
#define EFI_STATUS_CODE_SPECIFIC_DATA_GUID \
  { \
    0x335984bd, 0xe805, 0x409a, 0xb8, 0xf8, 0xd2, 0x7e, 0xce, 0x5f, 0xf7, 0xa6 \
  }
#endif

extern EFI_GUID gEfiStatusCodeSpecificDataGuid;

//already defined in StatusCodes.h
/*#pragma pack(1)
typedef enum {
  EfiStringAscii,
  EfiStringUnicode,
  EfiStringToken
} EFI_STRING_TYPE;

typedef struct {
  EFI_STRING_TYPE StringType;
  //
  // NULL terminated string follows here
  //
} EFI_STATUS_CODE_STRING_DATA;
#pragma pack()*/
//
// Debug Assert Data. This is part of Status Code Specification
//
#define EFI_STATUS_CODE_DATA_TYPE_ASSERT_GUID \
  { \
    0xDA571595, 0x4D99, 0x487C, 0x82, 0x7C, 0x26, 0x22, 0x67, 0x7D, 0x33, 0x07 \
  }

GUID_VARIABLE_DECLARATION(gEfiStatusCodeDataTypeAssertGuid, EFI_STATUS_CODE_DATA_TYPE_ASSERT_GUID);
//extern EFI_GUID gEfiStatusCodeDataTypeAssertGuid;

//
// Exception Data type (CPU REGS)
//
#define EFI_STATUS_CODE_DATA_TYPE_EXCEPTION_HANDLER_GUID \
  { \
    0x3BC2BD12, 0xAD2E, 0x11D5, 0x87, 0xDD, 0x00, 0x06, 0x29, 0x45, 0xC3, 0xB9 \
  }

extern EFI_GUID gEfiStatusCodeDataTypeExceptionHandlerGuid;

//
// Debug DataType defintions. User Defined Data Types.
//
#define EFI_STATUS_CODE_DATA_TYPE_DEBUG_GUID \
  { \
    0x9A4E9246, 0xD553, 0x11D5, 0x87, 0xE2, 0x00, 0x06, 0x29, 0x45, 0xC3, 0xb9 \
  }

#pragma pack(1)

typedef struct {
  UINT32  ErrorLevel;
  //
  // 12 * sizeof (UINT64) Var Arg stack
  //
  // ascii DEBUG () Format string
  //
} EFI_DEBUG_INFO;

#pragma pack()

//extern EFI_GUID gEfiStatusCodeDataTypeDebugGuid;
GUID_VARIABLE_DECLARATION(gEfiStatusCodeDataTypeDebugGuid, EFI_STATUS_CODE_DATA_TYPE_DEBUG_GUID);

//
// Progress Code. User Defined Data Type Guid.
//
#define EFI_STATUS_CODE_DATA_TYPE_ERROR_GUID \
  { \
    0xAB359CE3, 0x99B3, 0xAE18, 0xC8, 0x9D, 0x95, 0xD3, 0xB0, 0x72, 0xE1, 0x9B \
  }

extern EFI_GUID gEfiStatusCodeDataTypeErrorGuid;

//
// declaration for EFI_EXP_DATA. This may change
//
typedef UINTN   EFI_EXP_DATA;

//
// Voltage Extended Error Data
//
#if PI_SPECIFICATION_VERSION>=0x0001000A
typedef struct {
  EFI_STATUS_CODE_DATA  DataHeader;
  EFI_EXP_BASE10_DATA          Voltage; 
  EFI_EXP_BASE10_DATA          Threshold;
} EFI_COMPUTING_UNIT_VOLTAGE_ERROR_DATA;
#else
typedef struct {
  EFI_STATUS_CODE_DATA  DataHeader;
  EFI_EXP_DATA          Voltage; 
  EFI_EXP_DATA          Threshold; 
} EFI_COMPUTING_UNIT_VOLTAGE_ERROR_DATA;
#endif
//
// Microcode Update Extended Error Data
//
typedef struct {
  EFI_STATUS_CODE_DATA  DataHeader;
  UINT32                Version;
} EFI_COMPUTING_UNIT_MICROCODE_UPDATE_ERROR_DATA;

//
// Asynchronous Timer Extended Error Data
//
#if PI_SPECIFICATION_VERSION>=0x0001000A
typedef struct {
  EFI_STATUS_CODE_DATA  DataHeader;
  EFI_EXP_BASE10_DATA          TimerLimit;
} EFI_COMPUTING_UNIT_TIMER_EXPIRED_ERROR_DATA;
#else
typedef struct {
  EFI_STATUS_CODE_DATA  DataHeader;
  EFI_EXP_DATA          TimerLimit;
} EFI_COMPUTING_UNIT_TIMER_EXPIRED_ERROR_DATA;
#endif
//
// Host Processor Mismatch Extended Error Data
//
typedef struct {
  EFI_STATUS_CODE_DATA  DataHeader;
  UINT32                Instance;
  UINT16                Attributes;
} EFI_HOST_PROCESSOR_MISMATCH_ERROR_DATA;

//
// EFI_COMPUTING_UNIT_MISMATCH_ATTRIBUTES
// All other attributes are reserved for future use and
// must be initialized to 0.
//
#define EFI_COMPUTING_UNIT_MISMATCH_SPEED       0x0001
#define EFI_COMPUTING_UNIT_MISMATCH_FSB_SPEED   0x0002
#define EFI_COMPUTING_UNIT_MISMATCH_FAMILY      0x0004
#define EFI_COMPUTING_UNIT_MISMATCH_MODEL       0x0008
#define EFI_COMPUTING_UNIT_MISMATCH_STEPPING    0x0010
#define EFI_COMPUTING_UNIT_MISMATCH_CACHE_SIZE  0x0020
#define EFI_COMPUTING_UNIT_MISMATCH_OEM1        0x1000
#define EFI_COMPUTING_UNIT_MISMATCH_OEM2        0x2000
#define EFI_COMPUTING_UNIT_MISMATCH_OEM3        0x4000
#define EFI_COMPUTING_UNIT_MISMATCH_OEM4        0x8000

//
// Thermal Extended Error Data
//
#if PI_SPECIFICATION_VERSION>=0x0001000A
typedef struct {
  EFI_STATUS_CODE_DATA  DataHeader;
  EFI_EXP_BASE10_DATA          Temperature;
  EFI_EXP_BASE10_DATA          Threshold;
} EFI_COMPUTING_UNIT_THERMAL_ERROR_DATA;
#else
typedef struct {
  EFI_STATUS_CODE_DATA  DataHeader;
  EFI_EXP_DATA          Temperature;
  EFI_EXP_DATA          Threshold;
} EFI_COMPUTING_UNIT_THERMAL_ERROR_DATA;
#endif
//
// Processor Disabled Extended Error Data
//
typedef struct {
  EFI_STATUS_CODE_DATA  DataHeader;
  UINT32                Cause;
  BOOLEAN               SoftwareDisabled;
} EFI_COMPUTING_UNIT_CPU_DISABLED_ERROR_DATA;

typedef enum {
  EfiInitCacheDataOnly,
  EfiInitCacheInstrOnly,
  EfiInitCacheBoth,
  EfiInitCacheUnspecified
} EFI_INIT_CACHE_TYPE;

#if PI_SPECIFICATION_VERSION>=0x0001000A
//************************************************************
// EFI_CPU_STATE_CHANGE_CAUSE
//************************************************************
typedef UINT32 EFI_CPU_STATE_CHANGE_CAUSE;
//
// The reason a processor was disabled
//
#define EFI_CPU_CAUSE_INTERNAL_ERROR    0x0001
#define EFI_CPU_CAUSE_THERMAL_ERROR     0x0002
#define EFI_CPU_CAUSE_SELFTEST_FAILURE  0x0004
#define EFI_CPU_CAUSE_PREBOOT_TIMEOUT   0x0008
#define EFI_CPU_CAUSE_FAILED_TO_START   0x0010
#define EFI_CPU_CAUSE_CONFIG_ERROR      0x0020
#define EFI_CPU_CAUSE_USER_SELECTION    0x0080
#define EFI_CPU_CAUSE_BY_ASSOCIATION    0x0100
#define EFI_CPU_CAUSE_UNSPECIFIED       0x8000

#endif
//
// Embedded cache init extended data
//
typedef struct {
  EFI_STATUS_CODE_DATA  DataHeader;
  UINT32                Level;
  EFI_INIT_CACHE_TYPE   Type;
} EFI_CACHE_INIT_DATA;

//
// Memory Extended Error Data
//
//
// Memory Error Granularity Definition
//
typedef UINT8 EFI_MEMORY_ERROR_GRANULARITY;

//
// Memory Error Operation Definition
//
typedef UINT8 EFI_MEMORY_ERROR_OPERATION;

typedef struct {
  EFI_STATUS_CODE_DATA          DataHeader;
  EFI_MEMORY_ERROR_GRANULARITY  Granularity;
  EFI_MEMORY_ERROR_OPERATION    Operation;
#if PI_SPECIFICATION_VERSION>=0x0001000A
  UINT32                        Syndrome;
#else
  UINTN                         Syndrome;
#endif
  EFI_PHYSICAL_ADDRESS          Address;
  UINTN                         Resolution;
} EFI_MEMORY_EXTENDED_ERROR_DATA;

//
// Memory Error Granularities
//
#define EFI_MEMORY_ERROR_OTHER      0x01
#define EFI_MEMORY_ERROR_UNKNOWN    0x02
#define EFI_MEMORY_ERROR_DEVICE     0x03
#define EFI_MEMORY_ERROR_PARTITION  0x04

//
// Memory Error Operations
//
#define EFI_MEMORY_OPERATION_OTHER          0x01
#define EFI_MEMORY_OPERATION_UNKNOWN        0x02
#define EFI_MEMORY_OPERATION_READ           0x03
#define EFI_MEMORY_OPERATION_WRITE          0x04
#define EFI_MEMORY_OPERATION_PARTIAL_WRITE  0x05

//
// Define shorthands to describe Group Operations
// Many memory init operations are essentially group
// operations.
// A shorthand to describe that the operation is performed
// on multiple devices within the array
//
#define EFI_MULTIPLE_MEMORY_DEVICE_OPERATION  0xfffe
//
// A shorthand to describe that the operation is performed // on all devices within the array
//
#define EFI_ALL_MEMORY_DEVICE_OPERATION 0xffff
//
// A shorthand to describe that the operation is performed // on multiple arrays
//
#define EFI_MULTIPLE_MEMORY_ARRAY_OPERATION 0xfffe
//
// A shorthand to describe that the operation is performed // on all the arrays
//
#define EFI_ALL_MEMORY_ARRAY_OPERATION  0xffff

//
// DIMM number
//
#pragma pack(1)
typedef struct {
  EFI_STATUS_CODE_DATA  DataHeader;
  UINT16                Array;
  UINT16                Device;
} EFI_STATUS_CODE_DIMM_NUMBER;
#pragma pack()
//
// Memory Module Mismatch Extended Error Data
//
typedef struct {
  EFI_STATUS_CODE_DATA        DataHeader;
  EFI_STATUS_CODE_DIMM_NUMBER Instance;
} EFI_MEMORY_MODULE_MISMATCH_ERROR_DATA;

//
// Memory Range Extended Data
//
typedef struct {
  EFI_STATUS_CODE_DATA  DataHeader;
  EFI_PHYSICAL_ADDRESS  Start;
  EFI_PHYSICAL_ADDRESS  Length;
} EFI_MEMORY_RANGE_EXTENDED_DATA;

//
// Device handle Extended Data. Used for many
// errors and progress codes to point to the device.
//
typedef struct {
  EFI_STATUS_CODE_DATA  DataHeader;
  EFI_HANDLE            Handle;
} EFI_DEVICE_HANDLE_EXTENDED_DATA;

#if PI_SPECIFICATION_VERSION>=0x0001000A
//
//Extended data about the device path, which is used for many errors and progress codes 
//to point to the device.
//
typedef struct {
    EFI_STATUS_CODE_DATA    DataHeader;
    UINT8                   *DevicePath;
} EFI_DEVICE_PATH_EXTENDED_DATA;

//
// Resource Allocation Failure Extended Error Data
//
typedef struct {
    EFI_STATUS_CODE_DATA DataHeader;
    UINT32      Bar;
    UINT16      DevicePathSize;
    UINT16      ReqResSize;
    UINT16      AllocResSize;
	UINT8 		*DevicePath;
	UINT8		*ReqRes;
	UINT8		*AllocRes;
} EFI_RESOURCE_ALLOC_FAILURE_ERROR_DATA;
#else
typedef struct {
  EFI_STATUS_CODE_DATA      DataHeader;
  EFI_DEVICE_PATH_PROTOCOL  *DevicePath;
  UINT32                    Bar;
  VOID                      *ReqRes;
  VOID                      *AllocRes;
} EFI_RESOURCE_ALLOC_FAILURE_ERROR_DATA;
#endif

/*Already defined in StatusCodes.h
//
// Extended Error Data for Assert
//
typedef struct {
  EFI_STATUS_CODE_DATA        DataHeader;
  UINT32                      LineNumber;
  UINT32                      FileNameSize;
  EFI_STATUS_CODE_STRING_DATA *FileName;
} EFI_DEBUG_ASSERT_DATA;
*/
//
// System Context Data EBC/IA32/IPF
//
#ifndef GUID_VARIABLE_DEFINITION
#include <Protocol/DebugSupport.h>

typedef union {
  EFI_SYSTEM_CONTEXT_EBC  SystemContextEbc;
  EFI_SYSTEM_CONTEXT_IA32 SystemContextIa32;
  EFI_SYSTEM_CONTEXT_IPF  SystemContextIpf;
#if PI_SPECIFICATION_VERSION>=0x0001000A
  EFI_SYSTEM_CONTEXT_X64  SystemContextX64;
  EFI_SYSTEM_CONTEXT_ARM  SystemContextArm;
#endif
} EFI_STATUS_CODE_EXCEP_SYSTEM_CONTEXT;

typedef struct {
  EFI_STATUS_CODE_DATA                  DataHeader;
  EFI_STATUS_CODE_EXCEP_SYSTEM_CONTEXT  Context;
} EFI_STATUS_CODE_EXCEP_EXTENDED_DATA;
#endif
//
// Legacy Oprom extended data
//
typedef struct {
  EFI_STATUS_CODE_DATA  DataHeader;
  EFI_HANDLE            DeviceHandle;
  EFI_PHYSICAL_ADDRESS  RomImageBase;
} EFI_LEGACY_OPROM_EXTENDED_DATA;

#if PI_SPECIFICATION_VERSION>=0x0001000A
typedef struct {
  EFI_STATUS_CODE_DATA DataHeader;
  EFI_HANDLE ControllerHandle;
  EFI_HANDLE DriverBindingHandle;
  UINT16 DevicePathSize;
  UINT8 *RemainingDevicePath;
} EFI_STATUS_CODE_START_EXTENDED_DATA;
#endif
//
// Progress Code. User Defined Data Type Guid.
//
#define EFI_STATUS_CODE_DATA_TYPE_PROGRESS_CODE_GUID \
  { \
    0xA356AB39, 0x35C4, 0x35DA, 0xB3, 0x7A, 0xF8, 0xEA, 0x9E, 0x8B, 0x36, 0xA3 \
  }

extern EFI_GUID gEfiStatusCodeDataTypeProgressCodeGuid;

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************