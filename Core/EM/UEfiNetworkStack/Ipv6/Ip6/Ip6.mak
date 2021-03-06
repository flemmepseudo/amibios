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
# $Header: /Alaska/BIN/Modules/Network/UEFINetworkStack II/IPV6/Ip6/Ip6.mak 2     5/01/12 11:23a Hari $
#
# Revision: $
#
# $Date: 5/01/12 11:23a $
#**********************************************************************
# Revision History
# ----------------
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	Ip6.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
all : Ip6

Ip6 : $(BUILD_DIR)\Ip6.ffs

!IF "$(x64_BUILD)"=="1"
$(BUILD_DIR)\Ip6.ffs : $(Ip6_DIR)\Ip6Dxe.efi
!ELSE
$(BUILD_DIR)\Ip6.ffs : $(Ip6_DIR)\Ip6DxeIa32.efi
!ENDIF
	$(MAKE) /f Core\FFS.mak \
	BUILD_DIR=$(BUILD_DIR) \
	GUID=8F92960E-2880-4659-B857-915A8901BDC8\
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