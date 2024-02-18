/* polyspace MISRA-C3:1.1 [Justified:Unset] "All macro definitions are needed." */
/**********************************************************************************************************************
  COPYRIGHT
-----------------------------------------------------------------------------------------------------------------------
  \par      copyright
  \verbatim
  Copyright (c) 2019 by Vector Informatik GmbH.                                                  All rights reserved.

                This software is copyright protected and proprietary to Vector Informatik GmbH.
                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
                All other rights remain with Vector Informatik GmbH.
  \endverbatim
-----------------------------------------------------------------------------------------------------------------------
  FILE DESCRIPTION
-----------------------------------------------------------------------------------------------------------------------
  \file  File:  Dcm_Callout_Stubs.c
      Project:  Vector Basic Runtime System for MICROSAR4
       Module:  BrsMain

  \brief Description:  File for implementation of DCM callouts.
                       This file is a template only - please implement the callouts according to your needs.

  \attention Please note:
    The demo and example programs only show special aspects of the software. With regard to the fact
    that these programs are meant for demonstration purposes only, Vector Informatik liability shall be
    expressly excluded in cases of ordinary negligence, to the extent admissible by law or statute.
**********************************************************************************************************************/

/**********************************************************************************************************************
  AUTHOR IDENTITY
 ----------------------------------------------------------------------------------------------------------------------
  Name                          Initials      Company
  ----------------------------  ------------  -------------------------------------------------------------------------
  Benjamin Walter               visbwa        Vector Informatik GmbH
  Sascha Mauser                 vismaa        Vector Informatik GmbH
-----------------------------------------------------------------------------------------------------------------------
  REVISION HISTORY
 ----------------------------------------------------------------------------------------------------------------------
  Version   Date        Author  Description
 ----------------------------------------------------------------------------------------------------------------------
  01.00.00  2015-07-14  visbwa  Initial creation for usage with StartApplication
  01.00.01  2016-06-22  visbwa  Added sample code information block
  01.00.02  2016-08-29  visbwa  Added Dcm_DiagnosticService_0x38()
  01.00.03  2017-08-31  visbwa  Added callouts for Dcm_DiagnosticService 0x00, 0xB2, 0xB6 and 0xB7
  01.00.04  2017-12-06  visbwa  Reworked sample/example code disclaimer
  01.00.05  2019-02-01  visbwa  Added support for DCM ASR Version 4.2.2
  01.00.06  2019-03-11  vismaa  Changed DYNAMIC PART for Dcm_DiagnosticServiceXX
**********************************************************************************************************************/

/**********************************************************************************************************************
*  EXAMPLE CODE ONLY
*  -------------------------------------------------------------------------------------------------------------------
*  This Example Code is only intended for illustrating an example of a possible BSW integration and BSW configuration.
*  The Example Code has not passed any quality control measures and may be incomplete. The Example Code is neither
*  intended nor qualified for use in series production. The Example Code as well as any of its modifications and/or
*  implementations must be tested with diligent care and must comply with all quality requirements which are necessary
*  according to the state of the art before their use.
*********************************************************************************************************************/

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
#include "Platform_Types.h"
#include "Dcm.h"
#include "Dcm_Cfg.h"
#include "MemMap.h"
#include "Mcu.h"
#include "Std_Types.h"
#include "Com.h"
#include "CAN_DiagUsr.h"
#include "can_appl.h"


/**********************************************************************************************************************
  LOCAL FUNCTIONS
**********************************************************************************************************************/
/* polyspace+5 MISRA-C3:2.5 [Justified:Low] "Macro should be kept for future usage" */
#define DCM_START_SEC_CALLOUT_CODE
#define LOW_VALUE_DCM 0x8164U
#define HIGH_VALUE_DCM 0x7E9CU
#define START_ROUTINE_SPEED 0x05U
#define START_ROUTINE_PROPULSION 0x95U
#define START_ROUTINE_ECU_BLOCKED 0x81U

/* Address of the BL Variable named ResetResponseFlag which is written by BL using function ApplFblNvWriteResetResponseFlag() */
#ifndef TESSY
#define kEepAddressResetResponseFlag  (0x20006EC0uL + 2uL)
#else
static uint32* kEepAddressResetResponseFlag = (uint32*)(0x20006EC0uL + 2uL);
#endif
/* Defines for response after reset */
/* polyspace+6 MISRA-C3:2.5 [Justified:Low] "Macro should be kept for future usage" */
#define RESET_RESPONSE_NOT_REQUIRED             0x00u    /**< No response required */
#define RESET_RESPONSE_SDS_REQUIRED             0x01u    /**< Response to SesseionControl-DefaultSession required */
#define RESET_RESPONSE_ECURESET_REQUIRED        0x02u    /**< Response to EcuReset-HardReset required */
#define RESET_RESPONSE_KEYOFFON_REQUIRED        0x03u    /**< Response to EcuReset-KeyOffOnReset required */
#define RESET_RESPONSE_OSU_REQUIRED             0x04u    /**< Response to One-Step-Updater required */
#define RESET_RESPONSE_OTA_REQUIRED             0x05u    /**< Response to OTA required */

/* polyspace < MISRA-C3:8.2 :  Not a defect : Justify with annotations > The function type is same as in prototype form. */
/* polyspace < MISRA-C3:8.4: Not a defect : Justify with annotations > External Usage dependent on project setup*/
void DCM_Dummy_1() {}
/* polyspace < MISRA-C3:8.2 :  Not a defect : Justify with annotations > The function type is same as in prototype form. */
/* polyspace < MISRA-C3:8.4: Not a defect : Justify with annotations > External Usage dependent on project setup*/
void Dcm_Service19_10Processor() {}
/* polyspace < MISRA-C3:8.5 :Justified : Unset >The extern is used for backwards compatibility */
/* polyspace < MISRA-C3:17.7 : Justified : Unset > This function performs a micro-controller reset by using the hardware feature of the micro-controller. In case the function returns, the user must reset the platform using an alternate reset mechanism */

/* polyspace <MISRA-C3:2.7: Not a defect : Justify with annotations >"Paremeter should be kept for future usage" */
/* polyspace <MISRA-C3:5.9 : Not a defect : Justify with annotations > "Variable ErrorCode is static from Os_Stubs.c is static" */
/* polyspace <MISRA-C3:8.13 : Not a defect : Justify with annotations > "A const pointer not possible here" */
/* polyspace <MISRA-C3:8.13 : Not a defect : Justify with annotations > "A const pointer not possible here" */

/* polyspace+8 MISRA-C3:8.13 [Justified:Low] "A const pointer not possible here" */
/* polyspace+7 MISRA-C3:5.9 [Justified:Low] "variable ErrorCode is static from Os_Stubs.c is static" */
/* polyspace+2 MISRA-C3:D4.5 [Justified:Low] "No overlapping visibility" */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CheckProgrammingPreconditions(
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) DcmDspStartRoutineOutSignal_Return,
  P2VAR(uint16, AUTOMATIC, DCM_VAR_NOINIT) DataLength,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode
  )
  {
    BOOL nm_propulsionSystem = FALSE;
    uint8 U8_index = 0;

    (void)OpStatus;

    // (void)Com_ReceiveSignal(ComConf_ComSignal_MM_PropulsionSystemActive_XIX_OBD_04_XIX_HCP4_CANFD01_f6874ca1_Rx, &nm_propulsionSystem);

    if(BO_VehSpeedCondFulfilled == FALSE)
    {
      DcmDspStartRoutineOutSignal_Return[U8_index] = START_ROUTINE_SPEED;
      U8_index++;
    }
    else
    {
      /* do nothing */
    }

    if (nm_propulsionSystem == TRUE)
    {
      DcmDspStartRoutineOutSignal_Return[U8_index] = START_ROUTINE_PROPULSION;
      U8_index++;
    }
    else
    {
      /* do nothing */
    }

    if (Diag__EepData_AU8[DIAG__EEP_SEC_ACC_DELAY_ADDR] == KEEP_SEC_ACCESS_DELAY_ACTIVE)
    {
      DcmDspStartRoutineOutSignal_Return[U8_index] = START_ROUTINE_ECU_BLOCKED;
      U8_index++;
    }
    else
    {
      /* do nothing */
    }

    *DataLength = U8_index;

    return E_OK;
  }
/**********************************************************************************************************************
  PART 1 - STATIC PART
   These Callouts are announced within Dcm_Core.h.
   The existence is configuration specific
**********************************************************************************************************************/
/* polyspace <MISRA-C3:2.7 : Not a defect : Justify with annotations > "Paremeter should be kept for future usage" */
/* polyspace:begin <MISRA-C3:D4.5 : Not a defect : Justify with annotations > "No overlapping visibility" */
FUNC(void, DCM_CALLOUT_CODE) Dcm_Confirmation(Dcm_IdContextType idContext
                                             ,PduIdType dcmRxPduId
                                             ,Dcm_ConfirmationStatusType status)
/* polyspace:end <MISRA-C3:D4.5 : Not a defect : Justify with annotations > "No overlapping visibility" */
{
}

#if (DCM_DIAG_JUMPFROMFBL_ENABLED == STD_ON)
/* polyspace <MISRA-C3:8.13 : Not a defect : Justify with annotations > "A const pointer not possible here" */
/* polyspace < MISRA-C3:2.7 : Not a defect : Justify with annotations > Paremeter should be kept for future usage */
FUNC(Dcm_EcuStartModeType, DCM_CALLOUT_CODE) Dcm_GetProgConditions(Dcm_ProgConditionsPtrType progConditions)
{
  /* polyspace+2 MISRA-C3:11.4 [Justified:Low] "A cast should not be performed" */
  Dcm_EcuStartModeType retEcuStartMode = DCM_COLD_START;
  uint8 *pResetResponseFlagFromBL = (uint8*)kEepAddressResetResponseFlag;

  /* Check if the BL requested to responde to the Reset request */
  switch(*pResetResponseFlagFromBL)
  {
    case RESET_RESPONSE_ECURESET_REQUIRED:  // UDS 1101
      progConditions->Sid = 0x11;
      progConditions->SubFuncId = 0x01;

      retEcuStartMode = DCM_WARM_START;
      break;

    case RESET_RESPONSE_SDS_REQUIRED: // UDS 1001
      progConditions->Sid = 0x10;
      progConditions->SubFuncId = 0x01;

      retEcuStartMode = DCM_WARM_START;
      break;

    /* Reset response not required by BL */
    default:
      retEcuStartMode = DCM_COLD_START;
      break;
  }

  /* When Reset reponse is required, fill the precondition data */
  if (retEcuStartMode != DCM_COLD_START)
  {
      /* HandleId for DCM Tx connections in ASW are switched from FBL (ASW: ISO = 0, OBDC = 1, FBL: OBDC = 0, ISO = 1) */
      if (Diag__EepData_AU8[DIAG__EEP_TESTER_ADDR] == 1)
      {
        /* OBDC */
        progConditions->TesterSourceAddr = 0x0217u;
      }
      else
      {
        /* ISO */
        progConditions->TesterSourceAddr = 0x0017u;
      }

      progConditions->ReprogrammingRequest = FALSE;
      progConditions->ApplUpdated = TRUE;
      progConditions->ResponseRequired = TRUE;
  }

  return retEcuStartMode;
}
#endif

#if (DCM_DCM_AR_VERSION >= DCM_DCM_AR_VERSION_422)
# if (DCM_SVC_23_SUPPORT_ENABLED == STD_ON)
FUNC(Dcm_ReturnReadMemoryType, DCM_CALLOUT_CODE) Dcm_ReadMemory(Dcm_OpStatusType OpStatus
                                                               ,uint8  MemoryIdentifier
                                                               ,uint32 MemoryAddress
                                                               ,uint32 MemorySize
                                                               ,Dcm_MsgType MemoryData
                                                               ,Dcm_NegativeResponseCodePtrType ErrorCode)
{
  *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
  return DCM_E_NOT_OK;
}
# endif

# if (DCM_SVC_3D_SUPPORT_ENABLED == STD_ON)
FUNC(Dcm_ReturnWriteMemoryType, DCM_CALLOUT_CODE) Dcm_WriteMemory(Dcm_OpStatusType OpStatus
                                                                 ,uint8  MemoryIdentifier
                                                                 ,uint32 MemoryAddress
                                                                 ,uint32 MemorySize
                                                                 ,Dcm_MsgType MemoryData
                                                                 ,Dcm_NegativeResponseCodePtrType ErrorCode)
{
  *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
  return DCM_E_NOT_OK;
}
# endif

#else
# if (DCM_SVC_23_SUPPORT_ENABLED == STD_ON)
FUNC(Dcm_ReturnReadMemoryType, DCM_CALLOUT_CODE) Dcm_ReadMemory(Dcm_OpStatusType OpStatus
                                                               ,uint8  MemoryIdentifier
                                                               ,uint32 MemoryAddress
                                                               ,uint32 MemorySize
                                                               ,Dcm_MsgType MemoryData)
{
  return DCM_E_NOT_OK;
}
# endif

# if (DCM_SVC_3D_SUPPORT_ENABLED == STD_ON)
/* polyspace < MISRA-C3:8.4: Not a defect : Justify with annotations > External Usage dependent on project setup*/
FUNC(Dcm_ReturnWriteMemoryType, DCM_CALLOUT_CODE) Dcm_WriteMemory(Dcm_OpStatusType OpStatus
                                                                 ,uint8  MemoryIdentifier
                                                                 ,uint32 MemoryAddress
                                                                 ,uint32 MemorySize
                                                                 ,Dcm_MsgType MemoryData)
{
  return DCM_E_NOT_OK;
}
# endif
#endif /*DCM_DCM_AR_VERSION_422*/

/**********************************************************************************************************************
  PART 2 - DYNAMIC PART
   These Callouts are announced within Dcm_Lcfg.h.
   The existence is configuration specific
**********************************************************************************************************************/
#if (DCM_DCM_AR_VERSION >= DCM_DCM_AR_VERSION_422)
/* polyspace <MISRA-C3:2.7 : Not a defect :Justify with annotations >"Paremeter should be kept for future usage" */
/* polyspace <MISRA-C3:D4.5 : Not a defect : Justify with annotations >"No overlapping visibility" */
/* polyspace <MISRA-C3:5.9 : Not a defect : Justify with annotations >"Variable ErrorCode is static from Os_Stubs.c is static" */
/* polyspace < MISRA-C3:8.4 : Not a defect : Justify with annotations > External Usage dependent on project setup*/
/* polyspace <MISRA-C3:8.13 : Not a defect : Justify with annotations > "A const pointer not possible here" */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_DiagnosticService_0x00(Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext, Dcm_NegativeResponseCodePtrType ErrorCode)
{
  *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
  return E_NOT_OK;
}
/* polyspace <MISRA-C3:2.7: Not a defect : Justify with annotations > "Paremeter should be kept for future usage" */
/* polyspace <MISRA-C3:D4.5: Not a defect : Justify with annotations > "No overlapping visibility" */
/* polyspace <MISRA-C3:5.9 : Not a defect : Justify with annotations > "Variable ErrorCode is static from Os_Stubs.c is static" */
/* polyspace < MISRA-C3:8.4: Not a defect : Justify with annotations > External Usage dependent on project setup*/
/* polyspace <MISRA-C3:8.13: Not a defect : Justify with annotations > "A const pointer not possible here" */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_DiagnosticService_0x34(Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext, Dcm_NegativeResponseCodePtrType ErrorCode)
{
  *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
  return E_NOT_OK;
}
/* polyspace< MISRA-C3:2.7 : Not a defect : Justify with annotations > "Paremeter should be kept for future usage" */
/* polyspace< MISRA-C3:D4.5 : Not a defect : Justify with annotations > "No overlapping visibility" */
/* polyspace< MISRA-C3:5.9 : Not a defect : Justify with annotations > "Variable ErrorCode is static from Os_Stubs.c is static" */
/* polyspace < MISRA-C3:8.4 : Not a defect : Justify with annotations > External Usage dependent on project setup*/
/* polyspace< MISRA-C3:8.13 : Not a defect : Justify with annotations > "A const pointer not possible here" */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_DiagnosticService_0x35(Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext, Dcm_NegativeResponseCodePtrType ErrorCode)
{
  *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
  return E_NOT_OK;
}

/* polyspace <MISRA-C3:D4.5 : Not a defect : Justify with annotations > "No overlapping visibility" */
/* polyspace <MISRA-C3:5.9 : Not a defect : Justify with annotations > "Variable ErrorCode is static from Os_Stubs.c is static" */
/* polyspace <MISRA-C3:8.13 : Not a defect : Justify with annotations > "A const pointer not possible here" */
/* polyspace < MISRA-C3:8.4: Not a defect : Justify with annotations > External Usage dependent on project setup*/
/* polyspace < MISRA-C3:2.7 : Not a defect : Justify with annotations > Paremeter should be kept for future usage */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_DiagnosticService_0x36(Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext, Dcm_NegativeResponseCodePtrType ErrorCode)
{
  *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
  return E_NOT_OK;
}
/* polyspace <MISRA-C3:2.7 : Not a defect : Justify with annotations >"Paremeter should be kept for future usage." */
/* polyspace <MISRA-C3:D4.5 : Not a defect : Justify with annotations > "No overlapping visibility" */
/* polyspace <MISRA-C3:5.9 : Not a defect : Justify with annotations > "Variable ErrorCode is static from Os_Stubs.c is static" */
/* polyspace < MISRA-C3:8.4: Not a defect : Justify with annotations > External Usage dependent on project setup*/
/* polyspace <MISRA-C3:8.13 : Not a defect : Justify with annotations > "A const pointer not possible here" */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_DiagnosticService_0x37(Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext, Dcm_NegativeResponseCodePtrType ErrorCode)
{
  *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
  return E_NOT_OK;
}
/* polyspace <MISRA-C3:D4.5 : Not a defect : Justify with annotations > "No overlapping visibility" */
/* polyspace <MISRA-C3:5.9 : Not a defect : Justify with annotations > "Variable ErrorCode is static from Os_Stubs.c is static" */
/* polyspace < MISRA-C3:8.4: Not a defect : Justify with annotations > External Usage dependent on project setup*/
/* polyspace <MISRA-C3:8.13 : Not a defect : Justify with annotations > "A const pointer not possible here" */
/* polyspace < MISRA-C3:2.7 : Not a defect : Justify with annotations > Paremeter should be kept for future usage */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_DiagnosticService_0xB2(Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext, Dcm_NegativeResponseCodePtrType ErrorCode)
{
  *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
  return E_NOT_OK;
}
/* polyspace <MISRA-C3:D4.5 : Not a defect : Justify with annotations > "No overlapping visibility" */
/* polyspace < MISRA-C3:8.4: Not a defect : Justify with annotations > External Usage dependent on project setup*/
/* polyspace <MISRA-C3:8.13: Not a defect : Justify with annotations > "A const pointer not possible here" */
/* polyspace < MISRA-C3:2.7 : Not a defect : Justify with annotations > Paremeter should be kept for future usage */
/* polyspace <MISRA-C3:5.9 : Not a defect : Justify with annotations > Variable ErrorCode is static from Os_Stubs.c is static */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_DiagnosticService_0xB6(Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext, Dcm_NegativeResponseCodePtrType ErrorCode)
{
  *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
  return E_NOT_OK;
}
/* polyspace <MISRA-C3:D4.5 : Not a defect : Justify with annotations >"No overlapping visibility" */
/* polyspace <MISRA-C3:5.9 : Not a defect : Justify with annotations > "Variable ErrorCode is static from Os_Stubs.c is static" */
/* polyspace < MISRA-C3:8.4 : Not a defect : Justify with annotations > External Usage dependent on project setup*/
/* polyspace <MISRA-C3:8.13 : Not a defect : Justify with annotations > "A const pointer not possible here" */
/* polyspace < MISRA-C3:2.7 : Not a defect : Justify with annotations > Paremeter should be kept for future usage */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_DiagnosticService_0xB7(Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext, Dcm_NegativeResponseCodePtrType ErrorCode)
{
  *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
  return E_NOT_OK;
}

#else
/* polyspace <MISRA-C3:D4.5 : Not a defect : Justify with annotations > "No overlapping visibility" */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_DiagnosticService_0x00(Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext)
{
  return E_NOT_OK;
}
/* polyspace <MISRA-C3:D4.5 : Not a defect : Justify with annotations >"No overlapping visibility" */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_DiagnosticService_0x34(Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext)
{
  return E_NOT_OK;
}
/* polyspace <MISRA-C3:D4.5 : Not a defect : Justify with annotations > "No overlapping visibility" */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_DiagnosticService_0x35(Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext)
{
  return E_NOT_OK;
}
/* polyspace <MISRA-C3:D4.5 : Not a defect : Justify with annotations > "No overlapping visibility" */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_DiagnosticService_0x36(Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext)
{
  return E_NOT_OK;
}
/* polyspace <MISRA-C3:D4.5 : Not a defect : Justify with annotations > "No overlapping visibility" */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_DiagnosticService_0x37(Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext)
{
  return E_NOT_OK;
}
/* polyspace <MISRA-C3:D4.5 : Not a defect : Justify with annotations > "No overlapping visibility" */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_DiagnosticService_0x38(Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext)
{
  return E_NOT_OK;
}
/* polyspace <MISRA-C3:D4.5 : Not a defect : Justify with annotations >"No overlapping visibility" */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_DiagnosticService_0xB2(Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext)
{
  return E_NOT_OK;
}
/* polyspace <MISRA-C3:D4.5 : Not a defect : Justify with annotations > "No overlapping visibility" */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_DiagnosticService_0xB6(Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext)
{
  return E_NOT_OK;
}
/* polyspace <MISRA-C3:D4.5 : Not a defect : Justify with annotations >"No overlapping visibility" */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_DiagnosticService_0xB7(Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext)
{
  return E_NOT_OK;
}
#endif /*DCM_DCM_AR_VERSION_422*/

/**********************************************************************************************************************
  END of User implementation area
**********************************************************************************************************************/
#define DCM_STOP_SEC_CALLOUT_CODE
/* polyspace <MISRA-C3:20.1 : Not a defect : Justify with annotations > "The file inclusion is used for memory mapping." */
#include "MemMap.h"
