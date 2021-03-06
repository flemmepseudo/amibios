/*++

Copyright (c) 2004, Intel Corporation                                                         
All rights reserved. This program and the accompanying materials                          
are licensed and made available under the terms and conditions of the BSD License         
which accompanies this distribution.  The full text of the license may be found at        
http://opensource.org/licenses/bsd-license.php                                            
                                                                                          
THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,                     
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.             

Module Name:

  FirmwareVolumeBlock.c

Abstract:

  Firmware Volume Block protocol as defined in the Tiano Firmware Volume
  specification.

  Low level firmware device access routines to abstract firmware device
  hardware.
 
--*/

#include "Tiano.h"
#include EFI_PROTOCOL_DEFINITION (FirmwareVolumeBlock)

EFI_GUID  gFramerworkEfiFirmwareVolumeBlockProtocolGuid = FRAMEWORK_EFI_FIRMWARE_VOLUME_BLOCK_PROTOCOL_GUID;  //;;## ...AMI_OVERRIDE... Support PI1.x
EFI_GUID  gEfiFirmwareVolumeBlockProtocolGuid = EFI_FIRMWARE_VOLUME_BLOCK_PROTOCOL_GUID;
EFI_GUID  gEfiFirmwareVolumeBlock2ProtocolGuid = EFI_FIRMWARE_VOLUME_BLOCK2_PROTOCOL_GUID; //;;## ...AMI_OVERRIDE... Support PI1.x

EFI_GUID_STRING(&gFramerworkEfiFirmwareVolumeBlockProtocolGuid, "FirmwareVolumeBlock Protocol", "Framework Firmware Volume Block protocol");  //;;## ...AMI_OVERRIDE... Support PI1.x
EFI_GUID_STRING(&gEfiFirmwareVolumeBlock2ProtocolGuid, "FirmwareVolumeBlock2 Protocol", "Firmware Volume Block2 protocol"); //;;## ...AMI_OVERRIDE... Support PI1.x

