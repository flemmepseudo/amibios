/** @file
  Header file for PCH SMM Handler

@copyright
  Copyright (c) 2012 Intel Corporation. All rights reserved
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

  This file contains an 'Intel Peripheral Driver' and uniquely
  identified as "Intel Reference Module" and is
  licensed for Intel CPUs and chipsets under the terms of your
  license agreement with Intel or your vendor.  This file may
  be modified by the user, subject to additional terms of the
  license agreement
**/

#ifndef _PCHLATEINITSMM_H_
#define _PCHLATEINITSMM_H_

///
/// External include files do NOT need to be explicitly specified in real EDKII
/// environment
///
#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGlueDxe.h"
#include "PchAccess.h"
#include "PchPlatformLib.h"
#include "PchInitVar.h"
#include "pci22.h"
#endif
///
/// Driver Consumed Protocol Prototypes
///
#include EFI_PROTOCOL_DEPENDENCY (SmmBase)
#include EFI_PROTOCOL_DEPENDENCY (SmmIoTrapDispatch)
#include EFI_PROTOCOL_DEPENDENCY (SmmSxDispatch)

#define EFI_PCI_CAPABILITY_ID_PCIPM 0x01

#define DeviceD0 0x00
#define DeviceD3 0x03

#define ARRAY_SIZE(data) (sizeof (data) / sizeof (data[0]))

typedef enum {
  PciCfg,
  PciMmr
} PCH_PCI_ACCESS_TYPE;

typedef enum {
  Acpi,
  Rcrb,
  Tco
} PCH_ACCESS_TYPE;

typedef struct {
  PCH_ACCESS_TYPE AccessType;
  UINT32          Address;
  UINT32          Data;
  UINT32          Mask;
  UINT8           Width;
} PCH_SAVE_RESTORE_REG;

typedef struct {
  PCH_SAVE_RESTORE_REG* PchSaveRestoreReg;
  UINT8                 size;
  PCH_SERIES            PchSeries;
} PCH_SAVE_RESTORE_REG_WRAP;

struct _PCH_SAVE_RESTORE_PCI;

typedef struct _PCH_SAVE_RESTORE_PCI{
  PCH_PCI_ACCESS_TYPE AccessType;
  UINT8            Device;
  UINT8            Function;
  UINT8            BarOffset;
  UINT16           Offset;
  UINT32           Data;
  UINT32           Mask;
  UINT8            Width;
  VOID            (*RestoreFunction)(struct _PCH_SAVE_RESTORE_PCI *PchSaveRestorePci);
} PCH_SAVE_RESTORE_PCI;

typedef struct {
  PCH_SAVE_RESTORE_PCI* PchSaveRestorePci;
  UINT8                 size;
  PCH_SERIES            PchSeries;
} PCH_SAVE_RESTORE_PCI_WRAP;

typedef struct {
  UINT8           Device;
  UINT8           Function;
  UINT8           PowerState;
} DEVICE_POWER_STATE;

VOID
RestorePxDevSlp(
  IN PCH_SAVE_RESTORE_PCI   *PchSaveRestorePci
  );

#endif
