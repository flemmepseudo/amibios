//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
//**********************************************************************
//
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtWrapperDxe/BdsBoot.c 2     5/14/14 9:52p Tristinchou $
//
// $Revision: 2 $
//
// $Date: 5/14/14 9:52p $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtWrapperDxe/BdsBoot.c $
// 
// 2     5/14/14 9:52p Tristinchou
// [TAG]  		EIP167030
// [Category]  	Improvement
// [Description]  	Remove the variable runtime attribute and keep original
// attributes.
// 
// 1     2/08/12 1:08a Klzhan
// Initial Check in 
// 
// 1     2/25/11 1:43a Klzhan
// Initial Check-in
// 
// 1     12/03/10 5:10a Klzhan
// Initial Check-in.
// 
//
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:            BdsBoot.c
//
// Description:     Create or Process Boot option by AMT.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>
/*++

Copyright (c) 2004, Intel Corporation                                                         
All rights reserved. This program and the accompanying materials                          
are licensed and made available under the terms and conditions of the BSD License         
which accompanies this distribution.  The full text of the license may be found at        
http://opensource.org/licenses/bsd-license.php                                            
                                                                                          
THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,                     
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.             

Module Name:

  BdsBoot.c

Abstract:

  BDS Lib functions which relate with create or process the boot
  option.

--*/

#include "BdsLib.h"

BOOLEAN mEnumBootDevice = FALSE;

EFI_STATUS
BdsLibDoLegacyBoot (
  IN  BDS_COMMON_OPTION           *Option
  )
/*++

Routine Description:
 
  Boot the legacy system with the boot option

Arguments:

  Option           - The legacy boot option which have BBS device path

Returns:

  EFI_UNSUPPORTED  - There is no legacybios protocol, do not support
                     legacy boot.
                         
  EFI_STATUS       - Return the status of LegacyBios->LegacyBoot ().

--*/
{
  EFI_STATUS                Status;
  EFI_LEGACY_BIOS_PROTOCOL  *LegacyBios;

  Status = gBS->LocateProtocol (&gEfiLegacyBiosProtocolGuid, NULL, &LegacyBios);
  if (EFI_ERROR (Status)) {
    //
    // If no LegacyBios protocol we do not support legacy boot
    //
    return EFI_UNSUPPORTED;
  }
  //
  // Notes: if we seperate the int 19, then we don't need to refresh BBS
  //
  BdsRefreshBbsTableForBoot (Option);

  //
  // Write boot to OS performance data to a file
  //
  WRITE_BOOT_TO_OS_PERFORMANCE_DATA;

  DEBUG ((EFI_D_INFO | EFI_D_LOAD, "Legacy Boot: %S\n", Option->Description));
  return LegacyBios->LegacyBoot (
                      LegacyBios,
                      (BBS_BBS_DEVICE_PATH *) Option->DevicePath,
                      Option->LoadOptionsSize,
                      Option->LoadOptions
                      );
}

EFI_STATUS
BdsLibBootViaBootOption (
  IN  BDS_COMMON_OPTION             * Option,
  IN  EFI_DEVICE_PATH_PROTOCOL      * DevicePath,
  OUT UINTN                         *ExitDataSize,
  OUT CHAR16                        **ExitData OPTIONAL
  )
/*++

Routine Description:

  Process the boot option follow the EFI 1.1 specification and 
  special treat the legacy boot option with BBS_DEVICE_PATH.

Arguments:

  Option       - The boot option need to be processed
  
  DevicePath   - The device path which describe where to load 
                 the boot image or the legcy BBS device path 
                 to boot the legacy OS

  ExitDataSize - Returned directly from gBS->StartImage ()

  ExitData     - Returned directly from gBS->StartImage ()

Returns:

  EFI_SUCCESS   - Status from gBS->StartImage (),
                  or BdsBootByDiskSignatureAndPartition ()

  EFI_NOT_FOUND - If the Device Path is not found in the system

--*/
{
  EFI_STATUS                Status;
  EFI_HANDLE                Handle;
  EFI_HANDLE                ImageHandle;
  EFI_DEVICE_PATH_PROTOCOL  *TempDevicePath;
  EFI_DEVICE_PATH_PROTOCOL  *FilePath;
  EFI_LOADED_IMAGE_PROTOCOL *ImageInfo;
  EFI_EVENT                 ReadyToBootEvent;
  EFI_ACPI_S3_SAVE_PROTOCOL *AcpiS3Save;
  EFI_LIST_ENTRY            TempBootLists;
  UINT32                    VarAttr;
  UINTN                     VarSize;
//;;##  EFI_TCG_PLATFORM_PROTOCOL *TcgPlatformProtocol;

  *ExitDataSize = 0;
  *ExitData     = NULL;

  //
  // Notes: put EFI64 ROM Shadow Solution
  //
  EFI64_SHADOW_ALL_LEGACY_ROM ();

  //
  // Notes: this code can be remove after the s3 script table
  // hook on the event EFI_EVENT_SIGNAL_READY_TO_BOOT or
  // EFI_EVENT_SIGNAL_LEGACY_BOOT
  //
  Status = gBS->LocateProtocol (&gEfiAcpiS3SaveGuid, NULL, &AcpiS3Save);
  if (!EFI_ERROR (Status)) {
    AcpiS3Save->S3Save (AcpiS3Save, NULL);
  }
  //
  // If it's Device Path that starts with a hard drive path,
  // this routine will do the booting.
  //
  Status = BdsBootByDiskSignatureAndPartition (
            Option,
            (HARDDRIVE_DEVICE_PATH *) DevicePath,
            Option->LoadOptionsSize,
            Option->LoadOptions,
            ExitDataSize,
            ExitData
            );
  if (!EFI_ERROR (Status)) {
    //
    // If we found a disk signature and partition device path return success
    //
    return EFI_SUCCESS;
  }
  //
  // Signal the EFI_EVENT_SIGNAL_READY_TO_BOOT event
  //

// AMI Override: Replace
// Abstract: Modified for EFI 2.0 required
#if defined(EFI_EVENT_SIGNAL_READY_TO_BOOT) && EFI_SPECIFICATION_VERSION<0x20000
    Status = gBS->CreateEvent(
                EFI_EVENT_SIGNAL_READY_TO_BOOT | EFI_EVENT_NOTIFY_SIGNAL_ALL,
                EFI_TPL_CALLBACK,
                NULL,
                NULL,
                &ReadyToBootEvent
                );
#else
    Status = EfiCreateEventReadyToBoot(
                EFI_TPL_CALLBACK,
                NULL,
                NULL,
                &ReadyToBootEvent
                );
#endif
// AMI Override End
  if (!EFI_ERROR (Status)) {
    gBS->SignalEvent (ReadyToBootEvent);
    gBS->CloseEvent (ReadyToBootEvent);
  }
  //
  // Set Boot Current
  //
  VarAttr = 0;
  VarSize = 0;

  Status = gRT->GetVariable(
                L"BootCurrent",
                &gEfiGlobalVariableGuid,
                &VarAttr,
                &VarSize,
                NULL );
  if( EFI_ERROR(Status) && (Status != EFI_BUFFER_TOO_SMALL) )
  {
    VarAttr = EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS;
    VarSize = sizeof(UINT16);
  }

  gRT->SetVariable(
        L"BootCurrent",
        &gEfiGlobalVariableGuid,
        VarAttr,
        VarSize,
        &Option->BootCurrent );

  if ((DevicePathType (Option->DevicePath) == BBS_DEVICE_PATH) &&
      (DevicePathSubType (Option->DevicePath) == BBS_BBS_DP)
    ) {
    //
    // Check to see if we should legacy BOOT. If yes then do the legacy boot
    //
    return BdsLibDoLegacyBoot (Option);
  }
  
  //
  // If the boot option point to Internal FV shell, make sure it is valid
  //
  Status = BdsLibUpdateFvFileDevicePath (&DevicePath, &gEfiShellFileGuid);
  if (!EFI_ERROR(Status)) {
    if (Option->DevicePath != NULL) {
      gBS->FreePool(Option->DevicePath);
    }
    Option->DevicePath  = EfiLibAllocateZeroPool (EfiDevicePathSize (DevicePath));
    EfiCopyMem (Option->DevicePath, DevicePath, EfiDevicePathSize (DevicePath));
    //
    // Update the shell boot option
    //
    InitializeListHead (&TempBootLists);
    BdsLibRegisterNewOption (&TempBootLists, DevicePath, L"EFI Internal Shell", L"BootOrder"); 
    //
    // free the temporary device path created by BdsLibUpdateFvFileDevicePath()
    //
    gBS->FreePool (DevicePath); 
    DevicePath = Option->DevicePath;
  }
/* //;;##
  //
  // Measure GPT Table
  //
  Status = gBS->LocateProtocol (
                  &gEfiTcgPlatformProtocolGuid,
                  NULL,
                  &TcgPlatformProtocol
                  );  
  if (!EFI_ERROR (Status)) {
    Status = TcgPlatformProtocol->MeasureGptTable (DevicePath);
  }
*/ //;;##
  
  //
  // Drop the TPL level from EFI_TPL_DRIVER to EFI_TPL_APPLICATION
  //
  gBS->RestoreTPL (EFI_TPL_APPLICATION);

  DEBUG ((EFI_D_INFO | EFI_D_LOAD, "Booting EFI 1.1 way %S\n", Option->Description));

  Status = gBS->LoadImage (
                  TRUE,
                  mBdsImageHandle,
                  DevicePath,
                  NULL,
                  0,
                  &ImageHandle
                  );

  //
  // If we didn't find an image, we may need to load the default
  // boot behavior for the device.
  //
  if (EFI_ERROR (Status)) {
    //
    // Find a Simple File System protocol on the device path. If the remaining
    // device path is set to end then no Files are being specified, so try
    // the removable media file name.
    //
    TempDevicePath = DevicePath;
    Status = gBS->LocateDevicePath (
                    &gEfiSimpleFileSystemProtocolGuid,
                    &TempDevicePath,
                    &Handle
                    );
    if (!EFI_ERROR (Status) && IsDevicePathEnd (TempDevicePath)) {
      FilePath = EfiFileDevicePath (Handle, DEFAULT_REMOVABLE_FILE_NAME);
      if (FilePath) {
        Status = gBS->LoadImage (
                        TRUE,
                        mBdsImageHandle,
                        FilePath,
                        NULL,
                        0,
                        &ImageHandle
                        );
        if (EFI_ERROR (Status)) {
          //
          // The DevicePath failed, and it's not a valid
          // removable media device.
          //
          goto Done;
        }
      }
    } else {
      Status = EFI_NOT_FOUND;
    }
  }

  if (EFI_ERROR (Status)) {
    //
    // It there is any error from the Boot attempt exit now.
    //
    goto Done;
  }
  //
  // Provide the image with it's load options
  //
  Status = gBS->HandleProtocol (ImageHandle, &gEfiLoadedImageProtocolGuid, &ImageInfo);
  ASSERT_EFI_ERROR (Status);

  if (Option->LoadOptionsSize != 0) {
    ImageInfo->LoadOptionsSize  = Option->LoadOptionsSize;
    ImageInfo->LoadOptions      = Option->LoadOptions;
  }
  //
  // Before calling the image, enable the Watchdog Timer for
  // the 5 Minute period
  //
  gBS->SetWatchdogTimer (5 * 60, 0x0000, 0x00, NULL);

  Status = gBS->StartImage (ImageHandle, ExitDataSize, ExitData);
  DEBUG ((EFI_D_INFO | EFI_D_LOAD, "Image Return Status = %r\n", Status));

  //
  // Clear the Watchdog Timer after the image returns
  //
  gBS->SetWatchdogTimer (0x0000, 0x0000, 0x0000, NULL);

Done:
  //
  // Clear Boot Current
  //
  gRT->SetVariable(
        L"BootCurrent",
        &gEfiGlobalVariableGuid,
        VarAttr,
        0,
        &Option->BootCurrent );

  //
  // Raise the TPL level back to EFI_TPL_DRIVER
  //
  gBS->RaiseTPL (EFI_TPL_DRIVER);

  return Status;
}

EFI_STATUS
BdsBootByDiskSignatureAndPartition (
  IN  BDS_COMMON_OPTION          * Option,
  IN  HARDDRIVE_DEVICE_PATH      * HardDriveDevicePath,
  IN  UINT32                     LoadOptionsSize,
  IN  VOID                       *LoadOptions,
  OUT UINTN                      *ExitDataSize,
  OUT CHAR16                     **ExitData OPTIONAL
  )
/*++

Routine Description:

  Check to see if a hard ware device path was passed in. If it was then search
  all the block IO devices for the passed in hard drive device path. 
  
Arguments:

  Option - The current processing boot option.

  HardDriveDevicePath - EFI Device Path to boot, if it starts with a hard
                        drive device path.

  LoadOptionsSize - Passed into gBS->StartImage ()
                    via the loaded image protocol.

  LoadOptions     - Passed into gBS->StartImage ()
                    via the loaded image protocol.

  ExitDataSize - returned directly from gBS->StartImage ()

  ExitData     - returned directly from gBS->StartImage ()

Returns:

  EFI_SUCCESS   - Status from gBS->StartImage (),
                  or BootByDiskSignatureAndPartition ()
                  
  EFI_NOT_FOUND - If the Device Path is not found in the system

--*/
{
  EFI_STATUS                Status;
  UINTN                     BlockIoHandleCount;
  EFI_HANDLE                *BlockIoBuffer;
  EFI_DEVICE_PATH_PROTOCOL  *BlockIoDevicePath;
  EFI_DEVICE_PATH_PROTOCOL  *BlockIoHdDevicePath;
  HARDDRIVE_DEVICE_PATH     *TmpHdPath;
  EFI_DEVICE_PATH_PROTOCOL  *DevicePath;
  EFI_DEVICE_PATH_PROTOCOL  *NewDevicePath;
  UINTN                     Index;
  BOOLEAN                   DevicePathMatch;
  HARDDRIVE_DEVICE_PATH     *TempPath;

  *ExitDataSize = 0;
  *ExitData     = NULL;

  if ( !((DevicePathType (&HardDriveDevicePath->Header) == MEDIA_DEVICE_PATH) &&
          (DevicePathSubType (&HardDriveDevicePath->Header) == MEDIA_HARDDRIVE_DP))
        ) {
    //
    // If the HardDriveDevicePath does not start with a Hard Drive Device Path
    // exit.
    //
    return EFI_NOT_FOUND;
  }
  //
  // The boot device have already been connected
  //
  Status = gBS->LocateHandleBuffer (ByProtocol, &gEfiBlockIoProtocolGuid, NULL, &BlockIoHandleCount, &BlockIoBuffer);
  if (EFI_ERROR (Status) || BlockIoHandleCount == 0) {
    //
    // If there was an error or there are no device handles that support
    // the BLOCK_IO Protocol, then return.
    //
    return EFI_NOT_FOUND;
  }
  //
  // Loop through all the device handles that support the BLOCK_IO Protocol
  //
  for (Index = 0; Index < BlockIoHandleCount; Index++) {

    Status = gBS->HandleProtocol (BlockIoBuffer[Index], &gEfiDevicePathProtocolGuid, (VOID *) &BlockIoDevicePath);
    if (EFI_ERROR (Status) || BlockIoDevicePath == NULL) {
      continue;
    }
    //
    // Make PreviousDevicePath == the device path node before the end node
    //
    DevicePath          = BlockIoDevicePath;
    BlockIoHdDevicePath = NULL;

    //
    // find HardDriver device path node
    //
    while (!IsDevicePathEnd (DevicePath)) {
      if ((DevicePathType (DevicePath) == MEDIA_DEVICE_PATH) && 
          (DevicePathSubType (DevicePath) == MEDIA_HARDDRIVE_DP)
          ) {
        BlockIoHdDevicePath = DevicePath;
        break;
      }

      DevicePath = NextDevicePathNode (DevicePath);
    }

    if (BlockIoHdDevicePath == NULL) {
      continue;
    }
    //
    // See if the harddrive device path in blockio matches the orig Hard Drive Node
    //
    DevicePathMatch = FALSE;

    TmpHdPath       = (HARDDRIVE_DEVICE_PATH *) BlockIoHdDevicePath;
    TempPath        = (HARDDRIVE_DEVICE_PATH *) BdsLibUnpackDevicePath ((EFI_DEVICE_PATH_PROTOCOL *) HardDriveDevicePath);

    //
    // Only several fields will be checked. NOT whole NODE
    //
    if ( TmpHdPath->PartitionNumber == TempPath->PartitionNumber &&
        TmpHdPath->MBRType == TempPath->MBRType &&
        TmpHdPath->SignatureType == TempPath->SignatureType &&
        EfiCompareGuid ((EFI_GUID *) TmpHdPath->Signature, (EFI_GUID *) TempPath->Signature)) {
      //
      // Get the matched device path
      //
      DevicePathMatch = TRUE;
    }
    //
    // Only do the boot, when devicepath match
    //
    if (DevicePathMatch) {
      //
      // Combine the Block IO and Hard Drive Device path together and try
      // to boot from it.
      //
      DevicePath    = NextDevicePathNode ((EFI_DEVICE_PATH_PROTOCOL *) HardDriveDevicePath);
      NewDevicePath = EfiAppendDevicePath (BlockIoDevicePath, DevicePath);

      //
      // Recursive boot with new device path
      //
      Status = BdsLibBootViaBootOption (Option, NewDevicePath, ExitDataSize, ExitData);
      if (!EFI_ERROR (Status)) {
        break;
      }
    }
  }

  gBS->FreePool (BlockIoBuffer);
  return Status;
}


EFI_STATUS
EFIAPI
BdsLibUpdateFvFileDevicePath (
  IN  OUT EFI_DEVICE_PATH_PROTOCOL      ** DevicePath,
  IN  EFI_GUID                          *FileGuid
  )
/*++

Routine Description:
   According to a file guild, check a Fv file device path is valid. If it is invalid,
   try to return the valid device path.
   FV address maybe changes for memory layout adjust from time to time, use this funciton 
   could promise the Fv file device path is right.

Arguments:
  DevicePath - on input, the Fv file device path need to check
                    on output, the updated valid Fv file device path
                    
  FileGuid - the Fv file guild
  
Returns:
  EFI_INVALID_PARAMETER - the input DevicePath or FileGuid is invalid parameter
  EFI_UNSUPPORTED - the input DevicePath does not contain Fv file guild at all
  EFI_ALREADY_STARTED - the input DevicePath has pointed to Fv file, it is valid
  EFI_SUCCESS - has successfully updated the invalid DevicePath, and return the updated
                          device path in DevicePath
                
--*/
{
  EFI_DEVICE_PATH_PROTOCOL      *TempDevicePath;
  EFI_DEVICE_PATH_PROTOCOL      *LastDeviceNode;
  EFI_STATUS                    Status;
  EFI_GUID                      *GuidPoint;
  UINTN                         Index;
  UINTN                         FvHandleCount;
  EFI_HANDLE                    *FvHandleBuffer;
  EFI_FV_FILETYPE               Type;
  UINTN                         Size;
  EFI_FV_FILE_ATTRIBUTES        Attributes;
  UINT32                        AuthenticationStatus;
  BOOLEAN                       FindFvFile;
  EFI_LOADED_IMAGE_PROTOCOL     *LoadedImage;
#if (PI_SPECIFICATION_VERSION < 0x00010000)
  EFI_FIRMWARE_VOLUME_PROTOCOL  *Fv;
#else
  EFI_FIRMWARE_VOLUME2_PROTOCOL *Fv;
#endif
  MEDIA_FW_VOL_FILEPATH_DEVICE_PATH FvFileNode;
  EFI_HANDLE                    FoundFvHandle;
  EFI_DEVICE_PATH_PROTOCOL      *NewDevicePath;
  
  if ((DevicePath == NULL) || (*DevicePath == NULL)) {
    return EFI_INVALID_PARAMETER;
  }
  if (FileGuid == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  //
  // Check whether the device path point to the default the input Fv file
  //
  TempDevicePath = *DevicePath; 
  LastDeviceNode = TempDevicePath;
  while (!EfiIsDevicePathEnd (TempDevicePath)) {
     LastDeviceNode = TempDevicePath;
     TempDevicePath = EfiNextDevicePathNode (TempDevicePath);
  }
  GuidPoint = EfiGetNameGuidFromFwVolDevicePathNode (
                (MEDIA_FW_VOL_FILEPATH_DEVICE_PATH *) LastDeviceNode
                );
  if (GuidPoint == NULL) {
    //
    // if this option does not points to a Fv file, just return EFI_UNSUPPORTED
    //
    return EFI_UNSUPPORTED;
  }
  if (!EfiCompareGuid (GuidPoint, FileGuid)) {
    //
    // If the Fv file is not the input file guid, just return EFI_UNSUPPORTED
    //
    return EFI_UNSUPPORTED;
  }
  
  //
  // Check whether the input Fv file device path is valid
  //
  TempDevicePath = *DevicePath; 
  FoundFvHandle = NULL;
  Status = gBS->LocateDevicePath (
                #if (PI_SPECIFICATION_VERSION < 0x00010000)    
                  &gEfiFirmwareVolumeProtocolGuid,
                #else
                  &gEfiFirmwareVolume2ProtocolGuid,
                #endif 
                  &TempDevicePath, 
                  &FoundFvHandle
                  );
  if (!EFI_ERROR (Status)) {
    Status = gBS->HandleProtocol (
                    FoundFvHandle,
                  #if (PI_SPECIFICATION_VERSION < 0x00010000)    
                    &gEfiFirmwareVolumeProtocolGuid,
                  #else
                    &gEfiFirmwareVolume2ProtocolGuid,
                  #endif
                    (VOID **) &Fv
                    );
    if (!EFI_ERROR (Status)) {
      //
      // Set FV ReadFile Buffer as NULL, only need to check whether input Fv file exist there
      //
      Status = Fv->ReadFile (
                    Fv,
                    FileGuid,
                    NULL,
                    &Size,
                    &Type,
                    &Attributes,
                    &AuthenticationStatus
                    );
      if (!EFI_ERROR (Status)) {
        return EFI_ALREADY_STARTED;
      }
    }
  }
 
  //
  // Look for the input wanted FV file in current FV
  // First, try to look for in Bds own FV. Bds and input wanted FV file usually are in the same FV
  //
  FindFvFile = FALSE;
  FoundFvHandle = NULL;
  Status = gBS->HandleProtocol (
             mBdsImageHandle,
             &gEfiLoadedImageProtocolGuid,
             &LoadedImage
             );
  if (!EFI_ERROR (Status)) {
    Status = gBS->HandleProtocol (
                    LoadedImage->DeviceHandle,
                  #if (PI_SPECIFICATION_VERSION < 0x00010000)    
                    &gEfiFirmwareVolumeProtocolGuid,
                  #else
                    &gEfiFirmwareVolume2ProtocolGuid,
                  #endif
                    (VOID **) &Fv
                    );
    if (!EFI_ERROR (Status)) {
      Status = Fv->ReadFile (
                    Fv,
                    FileGuid,
                    NULL,
                    &Size,
                    &Type,
                    &Attributes,
                    &AuthenticationStatus
                    );
      if (!EFI_ERROR (Status)) {
        FindFvFile = TRUE;
        FoundFvHandle = LoadedImage->DeviceHandle;
      }
    }
  }
  //
  // Second, if fail to find, try to enumerate all FV
  //
  if (!FindFvFile) {
    FvHandleBuffer = NULL;
    gBS->LocateHandleBuffer (
          ByProtocol,
       #if (PI_SPECIFICATION_VERSION < 0x00010000)
          &gEfiFirmwareVolumeProtocolGuid,
       #else
          &gEfiFirmwareVolume2ProtocolGuid,
       #endif   
          NULL,
          &FvHandleCount,
          &FvHandleBuffer
          );
    for (Index = 0; Index < FvHandleCount; Index++) {
      gBS->HandleProtocol (
            FvHandleBuffer[Index],
         #if (PI_SPECIFICATION_VERSION < 0x00010000)
            &gEfiFirmwareVolumeProtocolGuid,
         #else
            &gEfiFirmwareVolume2ProtocolGuid,
         #endif   
            (VOID **) &Fv
            );

      Status = Fv->ReadFile (
                    Fv,
                    FileGuid,
                    NULL,
                    &Size,
                    &Type,
                    &Attributes,
                    &AuthenticationStatus
                    );
      if (EFI_ERROR (Status)) {
        //
        // Skip if input Fv file not in the FV
        //
        continue;
      }
      FindFvFile = TRUE;
      FoundFvHandle = FvHandleBuffer[Index];
      break;
    }  
    
    if (FvHandleBuffer !=NULL ) {
      gBS->FreePool (FvHandleBuffer);  
    }
  }

  if (FindFvFile) {
    //
    // Build the shell device path
    //
    NewDevicePath = EfiDevicePathFromHandle (FoundFvHandle);
    EfiInitializeFwVolDevicepathNode (&FvFileNode, FileGuid);
    NewDevicePath = EfiAppendDevicePathNode (NewDevicePath, (EFI_DEVICE_PATH_PROTOCOL *) &FvFileNode);
    *DevicePath = NewDevicePath;    
    return EFI_SUCCESS;
  }
  return EFI_NOT_FOUND;
}
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************