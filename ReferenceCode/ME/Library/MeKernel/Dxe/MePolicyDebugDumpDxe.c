/** @file
  Dump whole DXE_ME_POLICY_PROTOCOL and serial out.

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

//
// External include files do NOT need to be explicitly specified in real EDKII
// environment
//
#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGlueDxe.h"
#include "MePolicyLib.h"
#endif

extern DXE_ME_POLICY_PROTOCOL  *mDxePlatformMePolicy;

/**
  Dump DXE ME Platform Policy

  @param[in] None.

  @retval None
**/
VOID
DxeMePolicyDebugDump (
  VOID
  )
{
  EFI_STATUS Status;

  Status = MePolicyLibInit ();
  if (EFI_ERROR (Status)) {
    return;
  }

#ifdef EFI_DEBUG
  DEBUG ((EFI_D_INFO, "\n------------------------ MePlatformPolicy Dump Begin -----------------\n"));
  DEBUG ((EFI_D_INFO, " Revision : 0x%x\n", mDxePlatformMePolicy->Revision));
  DEBUG ((EFI_D_INFO, "MeConfig ---\n"));
  //
  // Byte 0, bit definition for functionality enable/disable
  //
  DEBUG ((EFI_D_INFO, " MeFwDownGrade : 0x%x\n", mDxePlatformMePolicy->MeConfig.MeFwDownGrade));
  DEBUG ((EFI_D_INFO, " MeLocalFwUpdEnabled : 0x%x\n", mDxePlatformMePolicy->MeConfig.MeLocalFwUpdEnabled));
  DEBUG ((EFI_D_INFO, " EndOfPostEnabled : 0x%x\n", mDxePlatformMePolicy->MeConfig.EndOfPostEnabled));
  DEBUG ((EFI_D_INFO, " EndOfPostDone : 0x%x\n", mDxePlatformMePolicy->MeConfig.EndOfPostDone));
  DEBUG ((EFI_D_INFO, " MdesCapability : 0x%x\n", mDxePlatformMePolicy->MeConfig.MdesCapability));
  DEBUG ((EFI_D_INFO, " SvtForPchCap : 0x%x\n", mDxePlatformMePolicy->MeConfig.SvtForPchCap));
  DEBUG ((EFI_D_INFO, " MdesForBiosState : 0x%x\n", mDxePlatformMePolicy->MeConfig.MdesForBiosState));

  DEBUG ((EFI_D_INFO, "MeMiscConfig ---\n"));
  DEBUG ((EFI_D_INFO, " FviSmbiosType : 0x%x\n", mDxePlatformMePolicy->MeMiscConfig.FviSmbiosType));
  DEBUG ((EFI_D_INFO, "\n------------------------ MePlatformPolicy Dump End -------------------\n"));
#endif
}

