/** @file
  GUID for Power On boot mode.

@copyright
  Copyright (c) 1999 - 2012 Intel Corporation. All rights reserved
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

  This file contains 'Framework Code' and is licensed as such
  under the terms of your license agreement with Intel or your
  vendor.  This file may not be modified, except as allowed by
  additional terms of your license agreement.
**/
#ifndef _POWER_ON_HOB_GUID_H_
#define _POWER_ON_HOB_GUID_H_

#define EFI_POWER_ON_HOB_GUID \
  { \
    0x468a601, 0xc535, 0x46fd, 0xa9, 0x5d, 0xbb, 0xab, 0x99, 0x1b, 0x17, 0x8c \
  }

extern EFI_GUID gEfiPowerOnHobGuid;

#endif
