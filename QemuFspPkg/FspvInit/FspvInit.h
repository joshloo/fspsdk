/** @file
  FSP-V implementation related header file.

  Copyright (c) 2017 - 2018, Intel Corporation. All rights reserved.<BR>
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php.

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/
#ifndef _FSPV_INIT_H_
#define _FSPV_INIT_H_

#include <Library/HobLib.h>
#include <Library/DebugLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/PcdLib.h>
#include <FspvUpd.h>

///
/// Global ID for FW_VAL_PPI_GUID.
///
#define FSPV_FW_VAL_PPI_GUID \
  { \
    0xc3bb61a9, 0x5fc1, 0x4713, { 0x9b, 0x75, 0x6b, 0xbb, 0xd2, 0x3c, 0x55, 0x10 } \
  }

//
// Forward declaration for the FW_VAL_PPI.
//
typedef struct _FW_VAL_PPI FW_VAL_PPI;

typedef struct {
  UINT8                     TestIp[32];
} FSP_V_VAL_STRUCT;

//
//  Function to Validate IP Init code.
//
typedef
EFI_STATUS
(EFIAPI *FW_VAL_VALIDATE_IP) (
  IN  VOID    
  );

///
/// This PPI provides function to Validate IP Init
///
struct _FW_VAL_PPI {
  FW_VAL_VALIDATE_IP  ValidateIp;
};

extern EFI_GUID  gFspvFwValPpiGuid;

#endif // _FW_VAL_INIT_MODULE_H_
