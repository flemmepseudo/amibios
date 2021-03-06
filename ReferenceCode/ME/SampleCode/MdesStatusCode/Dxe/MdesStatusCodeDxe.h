/** @file
  Header file to provides an interface to call function to send HECI message.

@copyright
  Copyright (c) 2011 - 2012 Intel Corporation. All rights reserved
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

--*/
#ifndef _MDES_STATUS_CODE_DXE_H_
#define _MDES_STATUS_CODE_DXE_H_

#define MDES_STATUS_CODE_PROTOCOL_GUID \
  { \
    0xe5d0875a, 0xf647, 0x4e16, 0xbe, 0x4d, 0x95, 0x02, 0x40, 0x29, 0xcc, 0x44 \
  }

/**
  This function is called in case of status code appears.
  Provides an interface to call function to send HECI message.

  @param[in] Type                 Indicates the type of status code being reported.
  @param[in] Value                Describes the current status of a hardware or software entity.
                                  This included information about the class and subclass that is
                                  used to classify the entity as well as an operation.
  @param[in] Instance             The enumeration of a hardware or software entity within
                                  the system. Valid instance numbers start with 1.
  @param[in] CallerId             This optional parameter may be used to identify the caller.
                                  This parameter allows the status code driver to apply different
                                  rules to different callers.
  @param[in] Data                 This optional parameter may be used to pass additional data.

  @retval EFI_STATUS              HECI sent with success.
**/
typedef
EFI_STATUS
(EFIAPI *SEND_STATUS_CODE) (
  IN EFI_STATUS_CODE_TYPE         Type,
  IN EFI_STATUS_CODE_VALUE        Value,
  IN UINT32                       Instance,
  IN EFI_GUID                     *CallerId OPTIONAL,
  IN EFI_STATUS_CODE_DATA         *Data OPTIONAL
  );

typedef struct _MDES_STATUS_CODE_PROTOCOL {
  SEND_STATUS_CODE                SendMdesStatusCode;
} MDES_STATUS_CODE_PROTOCOL;

#endif
