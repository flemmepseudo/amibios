/*++
  This file contains 'Framework Code' and is licensed as such   
  under the terms of your license agreement with Intel or your  
  vendor.  This file may not be modified, except as allowed by  
  additional terms of your license agreement.                   
--*/
/*++

Copyright (c)  1999 - 2001 Intel Corporation. All rights reserved
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.


Module Name:
  
    Authorization.c

Abstract:

  Guid Definition for the EFI Authorization Protocol

--*/

#include "Tiano.h"
#include EFI_PROTOCOL_DEFINITION (Authorization)

EFI_GUID  gEfiAuthorizationProtocolGuid = EFI_AUTHORIZATION_PROTOCOL_GUID;

EFI_GUID_STRING(&gEfiAuthorizationProtocolGuid, "EFI Authorization Protocol", "EFI Authorization");
