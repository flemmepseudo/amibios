/** @file
  Define the variable data structures used for TrEE physical presence.
  The TPM2 request from firmware or OS is saved to variable. And it is
  cleared after it is processed in the next boot cycle. The TPM2 response
  is saved to variable.

@copyright
  Copyright (c) 2012 Intel Corporation. All rights reserved
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

  This file contains a 'Sample Driver' and is licensed as such
  under the terms of your license agreement with Intel or your
  vendor.  This file may be modified by the user, subject to
  the additional terms of the license agreement
**/

#ifndef __TREE_PHYSICAL_PRESENCE_DATA_GUID_H__
#define __TREE_PHYSICAL_PRESENCE_DATA_GUID_H__

#define EFI_TREE_PHYSICAL_PRESENCE_DATA_GUID \
  { \
    0xf24643c2, 0xc622, 0x494e, { 0x8a, 0xd, 0x46, 0x32, 0x57, 0x9c, 0x2d, 0x5b }\
  }

#define TREE_PHYSICAL_PRESENCE_VARIABLE  L"TrEEPhysicalPresence"

typedef struct {
  UINT8   PPRequest;      ///< Physical Presence request command.
  UINT8   LastPPRequest;
  UINT32  PPResponse;
  UINT8   Flags;
} EFI_TREE_PHYSICAL_PRESENCE;

//
// The definition bit of the flags
//
#define TREE_FLAG_NO_PPI_CLEAR                        0x2
#define TREE_FLAG_RESET_TRACK                         0x8

//
// The definition of physical presence operation actions
//
#define TREE_PHYSICAL_PRESENCE_NO_ACTION                               0
#define TREE_PHYSICAL_PRESENCE_CLEAR_CONTROL_CLEAR                     5
#define TREE_PHYSICAL_PRESENCE_CLEAR_CONTROL_CLEAR_2                   14
#define TREE_PHYSICAL_PRESENCE_SET_NO_PPI_CLEAR_FALSE                  17
#define TREE_PHYSICAL_PRESENCE_SET_NO_PPI_CLEAR_TRUE                   18
#define TREE_PHYSICAL_PRESENCE_CLEAR_CONTROL_CLEAR_3                   21
#define TREE_PHYSICAL_PRESENCE_CLEAR_CONTROL_CLEAR_4                   22

#define TREE_PHYSICAL_PRESENCE_NO_ACTION_MAX                           20

extern EFI_GUID  gEfiTrEEPhysicalPresenceGuid;

#endif

