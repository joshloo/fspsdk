/** @file
  FSP-V component implementation.

  Copyright (c) 2020, Intel Corporation. All rights reserved.<BR>
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php.

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "FspvInit.h"
#include <Library/ReportStatusCodeLib.h>
#include <Library/PerformanceLib.h>
#include <FspStatusCode.h>

//
// Function to Validate IP Init code.
//
EFI_STATUS
EFIAPI
ValidateIp (
  IN  VOID
  )
{
  DEBUG ((DEBUG_INFO, "ValidateIp() Start\n"));


  return EFI_SUCCESS;
}


FW_VAL_PPI mFwValPpi = {
  ValidateIp
};

static EFI_PEI_PPI_DESCRIPTOR  mFwValPpiList[] = {
  {
    EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
    &gFspvFwValPpiGuid,
    &mFwValPpi
  }
};

/**
  This function reports and installs new FV

  @retval     EFI_SUCCESS          The function completes successfully
**/
EFI_STATUS
ReportAndInstallNewFv (
  VOID
  )
{
  FSP_INFO_HEADER                *FspInfoHeader;
  EFI_FIRMWARE_VOLUME_HEADER     *FvHeader;
  UINT8                          *CurPtr;
  UINT8                          *EndPtr;

  FspInfoHeader = GetFspInfoHeaderFromApiContext();
  if (FspInfoHeader->Signature != FSP_INFO_HEADER_SIGNATURE) {
    DEBUG ((DEBUG_ERROR, "The signature of FspInfoHeader getting from API context is invalid at %p.\n", FspInfoHeader));
    FspInfoHeader = GetFspInfoHeader();
  }

  CurPtr = (UINT8 *)(UINTN)FspInfoHeader->ImageBase;
  EndPtr = CurPtr + FspInfoHeader->ImageSize - 1;

  while (CurPtr < EndPtr) {
    FvHeader = (EFI_FIRMWARE_VOLUME_HEADER *)CurPtr;
    if (FvHeader->Signature != EFI_FVH_SIGNATURE) {
      break;
    }
    PeiServicesInstallFvInfoPpi (
      NULL,
      (VOID *)FvHeader,
      (UINT32)FvHeader->FvLength,
      NULL,
      NULL
      );
    CurPtr += FvHeader->FvLength;
  }

  return EFI_SUCCESS;
}


/**
  FSP-V FW Validation Init Code

  @param[in] FileHandle           The file handle of the file, Not used.
  @param[in] PeiServices          General purpose services available to every PEIM.

  @retval EFI_SUCCESS             The function completes successfully
**/
EFI_STATUS
EFIAPI
FspvInitEntryPoint (
  IN    EFI_PEI_FILE_HANDLE       FileHandle,
  IN    CONST EFI_PEI_SERVICES    **PeiServices
  )
{

  EFI_STATUS                  Status = EFI_SUCCESS;


  FSPV_UPD                    *FspvUpd;
  FSP_INFO_HEADER             *FspInfoHeader;

  DEBUG ((DEBUG_INFO, "This is the only test string in FSPV for now.\n"));
  Status = EFI_SUCCESS;
  FspvUpd = NULL;
  FspInfoHeader = GetFspInfoHeaderFromApiContext ();
  SetFspInfoHeader (FspInfoHeader);
  
  FspvUpd = (FSPV_UPD *)GetFspApiParameter();
  if (FspvUpd == NULL) {
    //
    // Use the UpdRegion as default
    //
    FspvUpd = (FSPV_UPD *)(UINTN)(FspInfoHeader->ImageBase + FspInfoHeader->CfgRegionOffset);
  }
  SetFspValidationInitUpdDataPointer (FspvUpd);

  //
  // Install FW Validation PPI
  //
  Status = PeiServicesInstallPpi (mFwValPpiList);
  ASSERT_EFI_ERROR (Status);

  // This is the end of the FspValidationInit API
  // Give control back to the boot loader
  //
  FspValidationInitDone ();

  //
  // Give control back after ValidationApi
  //
  ReportAndInstallNewFv ();
  return EFI_SUCCESS;
}
