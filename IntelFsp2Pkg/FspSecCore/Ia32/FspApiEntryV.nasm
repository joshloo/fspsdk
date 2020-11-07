;; @file
;  Provide FSP API entry points.
;
; Copyright (c) 2020, Intel Corporation. All rights reserved.<BR>
; SPDX-License-Identifier: BSD-2-Clause-Patent
;;

    SECTION .text

;
; Following functions will be provided in C
;
extern ASM_PFX(FspApiCommon)

;----------------------------------------------------------------------------
; FspApiCommonContinue API
;
; This is the FSP API common entry point to resume the FSP execution
;
;----------------------------------------------------------------------------
global ASM_PFX(FspApiCommonContinue)
ASM_PFX(FspApiCommonContinue):
  jmp $

;----------------------------------------------------------------------------
; NotifyPhase API
;
; This FSP API will notify the FSP about the different phases in the boot
; process
;
;----------------------------------------------------------------------------
global ASM_PFX(NotifyPhaseApi)
ASM_PFX(NotifyPhaseApi):
  mov    eax,  2 ; FSP_API_INDEX.NotifyPhaseApiIndex
  jmp    ASM_PFX(FspApiCommon)

;----------------------------------------------------------------------------
; FspValInit API
;
; This FSP API initializes the validation parameters to capture test related
; data of silicon initialization.
;
;----------------------------------------------------------------------------
global ASM_PFX(FspValInitApiIndex)
ASM_PFX(FspValInitApi):
  mov    eax,  7 ; FSP_API_INDEX.FspValInitApiIndex
  jmp    ASM_PFX(FspApiCommon)

;----------------------------------------------------------------------------
; Module Entrypoint API
;----------------------------------------------------------------------------
global ASM_PFX(_ModuleEntryPoint)
ASM_PFX(_ModuleEntryPoint):
  jmp  $
  ; Add reference to APIs so that it will not be optimized by compiler
  jmp  ASM_PFX(FspValInitApi)
  jmp  ASM_PFX(NotifyPhaseApi)
