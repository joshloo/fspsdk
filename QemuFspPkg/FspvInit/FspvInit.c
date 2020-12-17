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
  EFI_STATUS                  Status;
  FSPV_UPD                    *FspvUpd;
  FSP_INFO_HEADER             *FspInfoHeader;

  Status = EFI_SUCCESS;
  FspvUpd = NULL;

  DEBUG ((DEBUG_INFO, "FspvInitEntryPoint() - Begin\n"));
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

  DEBUG ((DEBUG_INFO, "Done adding, installing PPI\n"));
  //
  // Install FW Validation PPI
  //
  Status = PeiServicesInstallPpi (mFwValPpiList);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "FspvInitEntryPoint() - End\n"));
  return EFI_SUCCESS;
}
