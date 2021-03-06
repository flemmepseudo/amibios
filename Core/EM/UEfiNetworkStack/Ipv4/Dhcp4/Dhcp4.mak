#//**********************************************************************
#//**********************************************************************
#//**                                                                  **
#//**        (C)Copyright 1985-2008, American Megatrends, Inc.         **
#//**                                                                  **
#//**                       All Rights Reserved.                       **
#//**                                                                  **
#//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
#//**                                                                  **
#//**                       Phone: (770)-246-8600                      **
#//**                                                                  **
#//**********************************************************************
#//**********************************************************************

#**********************************************************************
# $Header: /Alaska/BIN/Modules/Network/UEFINetworkStack II/IPV4/Dhcp4/Dhcp4.mak 2     5/01/12 10:11a Hari $
#
# Revision: $
#
# $Date: 5/01/12 10:11a $
#**********************************************************************
# Revision History
# ----------------
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	Dhcp6.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
all : Dhcp4

Dhcp4 : $(BUILD_DIR)\Dhcp4.ffs

!IF "$(x64_BUILD)"=="1"
$(BUILD_DIR)\Dhcp4.ffs : $(Dhcp4_DIR)\Dhcp4Dxe.efi
!ELSE
$(BUILD_DIR)\Dhcp4.ffs : $(Dhcp4_DIR)\Dhcp4DxeIa32.efi
!ENDIF
	$(MAKE) /f Core\FFS.mak \
	BUILD_DIR=$(BUILD_DIR) \
	GUID=8DD9176E-EE87-4f0e-8A84-3F998311F930\
	TYPE=EFI_FV_FILETYPE_DRIVER \
	PEFILE=$** FFSFILE=$@ COMPRESS=1 NAME=$(**B)
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2004, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************