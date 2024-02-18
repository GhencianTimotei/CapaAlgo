/* ********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 */
/*!
 *  \defgroup   Dem_RecordReaderIF Dem RecordReaderIF Functionality
 *  \{
 *  \file       Dem_RecordReaderIF_Svc.h
 *  \brief      Service implementation of unit RecordReaderIF.
 *  \details    Realizes Dem external service APIs.
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_RECORDREADERIF_SVC_H)
#define DEM_RECORDREADERIF_SVC_H

/* ********************************************************************************************************************
 *  GLOBAL MISRA JUSTIFICATIONS
 *********************************************************************************************************************/
/* PRQA S 2880 EOF */ /* MD_DEM_2.1_UNREACHABLE_STATEMENT */
/* PRQA S 2982 EOF */ /* MD_DEM_2982 */
/* PRQA S 2983 EOF */ /* MD_DEM_2983 */
/* PRQA S 2985 EOF */ /* MD_DEM_2985 */
/* PRQA S 2986 EOF */ /* MD_DEM_2986 */
/* PRQA S 2987 EOF */ /* MD_DEM_2987 */
/* PRQA S 2991 EOF */ /* MD_DEM_2991 */
/* PRQA S 2992 EOF */ /* MD_DEM_2992 */
/* PRQA S 2995 EOF */ /* MD_DEM_2995 */
/* PRQA S 2996 EOF */ /* MD_DEM_2996 */
/* PRQA S 3415 EOF */ /* MD_DEM_13.5_cf */

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                    /* Used subcomponent API */
/* ------------------------------------------------------------------------- */
#include "Dem_EnvDataSwcApi_Interface.h"
#include "Dem_Dcm_Interface.h"
#include "Dem_DataReport_Interface.h"
#include "Dem_ERec_Interface.h"

#include "Dem_FaultMemory_Interface.h"
#include "Dem_Infrastructure_Interface.h"
#include "Dem_Core_Interface.h"
#include "Dem_Client_Interface.h"
                                                   /* Subcomponents callbacks*/
/* ------------------------------------------------------------------------- */

/* ********************************************************************************************************************
 *  FILE SPECIFIC MISRA VIOLATIONS
 *********************************************************************************************************************/
/* PRQA S 3406 DEM_API_IMPL */ /* MD_DEM_8.6 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

  /*! Filename declaration */
#define DEM_RECORDREADERIF_SVC_FILENAME "Dem_RecordReaderIF_Svc.h"

 /* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \addtogroup Dem_RecordReaderIF_Public
 * \{
 */

/* ****************************************************************************
 % Dem_GetEventFreezeFrameDataEx
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetEventFreezeFrameDataEx(
  Dem_EventIdType  EventId,                                                                                                      /* PRQA S 1330, 3206 */ /* MD_DEM_8.3_rte, MD_DEM_3206 */
  uint8  RecordNumber,                                                                                                           /* PRQA S 3206 */ /* MD_DEM_3206 */
  uint16  DataId,                                                                                                                /* PRQA S 3206 */ /* MD_DEM_3206 */
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)  DestBuffer,                                                                            /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_8.13 */
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  BufSize                                                                               /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_8.13 */
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
  if (Dem_APIChecks_MasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (Dem_APIChecks_EventId(EventId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (Dem_APIChecks_NullPointer(DestBuffer) == FALSE)                                                                            /* SBSW_DEM_POINTER_NULLPTR_CHECKING */ /* PRQA S 0315 */ /* MD_DEM_Dir1.1 */
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (Dem_APIChecks_NullPointer(BufSize) == FALSE)                                                                               /* SBSW_DEM_POINTER_NULLPTR_CHECKING */ /* PRQA S 0315 */ /* MD_DEM_Dir1.1 */
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (Dem_APIChecks_IsMasterPartition() == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  {
    /* ----- Implementation ------------------------------------------------ */
    lReturnValue = Dem_EnvDataSwcApi_GetEventFreezeFrameDataEx(EventId, RecordNumber, DataId, DestBuffer, BufSize);              /* SBSW_DEM_POINTER_FORWARD_API_ARGUMENT_BUFFER */
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETEVENTFREEZEFRAMEDATAEX_APIID, Dem_Det_ErrorRegisterGet());
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_GetEventExtendedDataRecordEx
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetEventExtendedDataRecordEx(
  Dem_EventIdType  EventId,                                                                                                      /* PRQA S 1330, 3206 */ /* MD_DEM_8.3_rte, MD_DEM_3206 */
  uint8  RecordNumber,                                                                                                           /* PRQA S 3206 */ /* MD_DEM_3206 */
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)  DestBuffer,                                                                            /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_8.13 */
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  BufSize                                                                               /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_8.13 */
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
  if (Dem_APIChecks_MasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (Dem_APIChecks_EventId(EventId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (Dem_APIChecks_NullPointer(DestBuffer) == FALSE)                                                                       /* SBSW_DEM_POINTER_NULLPTR_CHECKING */ /* PRQA S 0315 */ /* MD_DEM_Dir1.1 */
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (Dem_APIChecks_NullPointer(BufSize) == FALSE)                                                                       /* SBSW_DEM_POINTER_NULLPTR_CHECKING */ /* PRQA S 0315 */ /* MD_DEM_Dir1.1 */
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (Dem_APIChecks_IsMasterPartition() == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  {
    /* ----- Implementation ------------------------------------------------ */
    lReturnValue = Dem_EnvDataSwcApi_GetEventExtendedDataRecordEx(EventId, RecordNumber, DestBuffer, BufSize);                   /* SBSW_DEM_POINTER_FORWARD_API_ARGUMENT_BUFFER */
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETEVENTEXTENDEDDATARECORDEX_APIID, Dem_Det_ErrorRegisterGet());
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */


#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_DisableDTCRecordUpdate
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_DisableDTCRecordUpdate(
  uint8  ClientId
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
  if (Dem_APIChecks_MasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (Dem_APIChecks_IsMasterPartition() == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_Client_ClientAccess_TestReadoutBufferValid(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (Dem_Client_ClientAccess_GetSelectionResult(ClientId) == DEM_DTCSELECTOR_SELECTION_INIT)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    lReturnValue = Dem_Client_ClientAccess_DisableDTCRecordUpdate(ClientId);

    if (lReturnValue == E_NOT_OK)
    {
      /* new request with different parameters than ongoing request */
#  if (DEM_DEV_ERROR_DETECT == STD_ON)
      Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
#  endif
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_DISABLEDTCRECORDUPDATE_APIID, Dem_Det_ErrorRegisterGet());
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_EnableDTCRecordUpdate
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_EnableDTCRecordUpdate(
  uint8  ClientId
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
  if (Dem_APIChecks_MasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_Client_ClientAccess_TestReadoutBufferValid(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else  
# endif
  if (Dem_APIChecks_IsMasterPartition() == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  {
    /* ----- Implementation ------------------------------------------------ */
    lReturnValue = Dem_Client_ClientAccess_EnableDTCRecordUpdate(ClientId);
    
#  if (DEM_DEV_ERROR_DETECT == STD_ON)
    if (lReturnValue == E_NOT_OK)
    {
      Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
    }
#  endif
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_ENABLEDTCRECORDUPDATE_APIID, Dem_Det_ErrorRegisterGet());
  }

  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_SelectFreezeFrameData
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_SelectFreezeFrameData(
  CONST(uint8, AUTOMATIC)  ClientId,
  CONST(uint8, AUTOMATIC)  RecordNumber
)
{
  Std_ReturnType lReturnValue;

  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
  if (Dem_APIChecks_MasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (Dem_APIChecks_ClientId(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else  
  if (Dem_APIChecks_IsMasterPartition() == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_Client_ClientAccess_GetSelectionResult(ClientId) == DEM_DTCSELECTOR_SELECTION_INIT)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  if (Dem_Client_ClientAccess_TestDTCRecordUpdateRequested(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
#if (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
    if (Dem_Client_ClientAccess_TestDTCRecordUpdateDisabled(ClientId) == FALSE)
    {
      lReturnValue = DEM_PENDING;
    }
    else
#endif
    {
      Dem_Dcm_SRec_SelectFirstSource(ClientId, RecordNumber);
      lReturnValue = E_OK;
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_SELECTFREEZEFRAMEDATA_APIID, Dem_Det_ErrorRegisterGet());
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_GetNextFreezeFrameData
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetNextFreezeFrameData(
  CONST(uint8, AUTOMATIC)  ClientId,
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  DestBuffer,
  P2VAR(uint16, AUTOMATIC, DEM_DCM_DATA)  BufSize
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
  if (Dem_APIChecks_MasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (Dem_APIChecks_NullPointer(DestBuffer ) == FALSE)                                                                       /* SBSW_DEM_POINTER_NULLPTR_CHECKING */  /* PRQA S 0315 */ /* MD_DEM_Dir1.1 */
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (Dem_APIChecks_NullPointer(BufSize ) == FALSE)                                                                       /* SBSW_DEM_POINTER_NULLPTR_CHECKING */  /* PRQA S 0315 */ /* MD_DEM_Dir1.1 */
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (Dem_APIChecks_ClientId(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else  
  if (Dem_APIChecks_IsMasterPartition() == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_Client_ClientAccess_GetSelectionResult(ClientId) == DEM_DTCSELECTOR_SELECTION_INIT)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  if (Dem_Client_ClientAccess_TestDTCRecordUpdateRequested(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  if (Dem_Client_ClientAccess_TestSnapshotRecordSelected(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    if (Dem_Client_ClientAccess_TestDTCRecordUpdateDisabled(ClientId) == FALSE)
    {
      lReturnValue = DEM_PENDING;
    }
    else
    {
      lReturnValue = Dem_Dcm_SRec_ReadNextRecord(ClientId, DestBuffer, BufSize);                                                 /* SBSW_DEM_POINTER_FORWARD_API_ARGUMENT_BUFFER */
    }
  }
  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETNEXTFREEZEFRAMEDATA_APIID, Dem_Det_ErrorRegisterGet());
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6030, 6050, 6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_GetSizeOfFreezeFrameSelection
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetSizeOfFreezeFrameSelection(
  CONST(uint8, AUTOMATIC)  ClientId,
  P2VAR(uint16, AUTOMATIC, DEM_DCM_DATA)  SizeOfFreezeFrame
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

    /* ----- Development Error Checks ---------------------------------------- */
  if (Dem_APIChecks_MasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (Dem_APIChecks_NullPointer(SizeOfFreezeFrame ) == FALSE)                                                                       /* SBSW_DEM_POINTER_NULLPTR_CHECKING */  /* PRQA S 0315 */ /* MD_DEM_Dir1.1 */
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (Dem_APIChecks_ClientId(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else  
  if (Dem_APIChecks_IsMasterPartition() == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_Client_ClientAccess_GetSelectionResult(ClientId) == DEM_DTCSELECTOR_SELECTION_INIT)
  {
    /* missing prior call to Dem_SelectDTC() */
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  if (Dem_Client_ClientAccess_TestDTCRecordUpdateRequested(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  if (Dem_Client_ClientAccess_TestSnapshotRecordSelected(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    if (Dem_Client_ClientAccess_TestDTCRecordUpdateDisabled(ClientId) == FALSE)
    {
      lReturnValue = DEM_PENDING;
    }
    else
    {
      lReturnValue = Dem_Dcm_SRec_GetSize(ClientId, SizeOfFreezeFrame);                                                          /* SBSW_DEM_POINTER_FORWARD_API */
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETSIZEOFFREEZEFRAMESELECTION_APIID, Dem_Det_ErrorRegisterGet());
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_SelectExtendedDataRecord
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_SelectExtendedDataRecord(
  CONST(uint8, AUTOMATIC)  ClientId,
  CONST(uint8, AUTOMATIC)  ExtendedDataNumber
  )
{
  Std_ReturnType lReturnValue;

  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
  if (Dem_APIChecks_MasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (Dem_APIChecks_ClientId(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else  
  if (Dem_APIChecks_IsMasterPartition() == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_Client_ClientAccess_TestDTCRecordUpdateRequested(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    if (Dem_Client_ClientAccess_TestDTCRecordUpdateDisabled(ClientId) == FALSE)
    {
      lReturnValue = DEM_PENDING;
    }
    else
    {
      Dem_Dcm_ERec_SelectRecord(ClientId, ExtendedDataNumber);
      lReturnValue = E_OK;
    }
  }
  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_SELECTEXTENDEDDATARECORD_APIID, Dem_Det_ErrorRegisterGet());
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6030, 6080 */ /* MD_MSR_STCYC, MD_MSR_STMIF */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_GetNextExtendedDataRecord
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
  FUNC(Std_ReturnType, DEM_CODE)
Dem_GetNextExtendedDataRecord(
  CONST(uint8, AUTOMATIC)  ClientId,
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  DestBuffer,                                                                             /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_8.13 */
  P2VAR(uint16, AUTOMATIC, DEM_DCM_DATA)  BufSize                                                                                /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_8.13 */
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
  if (Dem_APIChecks_MasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (Dem_APIChecks_NullPointer(DestBuffer ) == FALSE)                                                                       /* SBSW_DEM_POINTER_NULLPTR_CHECKING */  /* PRQA S 0315 */ /* MD_DEM_Dir1.1 */
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (Dem_APIChecks_NullPointer(BufSize ) == FALSE)                                                                       /* SBSW_DEM_POINTER_NULLPTR_CHECKING */  /* PRQA S 0315 */ /* MD_DEM_Dir1.1 */
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (Dem_APIChecks_ClientId(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else  
  if (Dem_APIChecks_IsMasterPartition() == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_Client_ClientAccess_GetSelectionResult(ClientId) == DEM_DTCSELECTOR_SELECTION_INIT)
  {
    /* missing prior call to Dem_SelectDTC() */
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  if (Dem_Client_ClientAccess_TestDTCRecordUpdateRequested(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  if (Dem_Client_ClientAccess_TestExtendedRecordSelected(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    if (Dem_Client_ClientAccess_TestDTCRecordUpdateDisabled(ClientId) == FALSE)
    {
      lReturnValue = DEM_PENDING;
    }
    else
    {
      lReturnValue = Dem_Dcm_ERec_ReadNextRecord(ClientId, DestBuffer, BufSize);                                                 /* SBSW_DEM_POINTER_FORWARD_API_ARGUMENT_BUFFER */
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETNEXTEXTENDEDDATARECORD_APIID, Dem_Det_ErrorRegisterGet());
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6030, 6050, 6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_GetSizeOfExtendedDataRecordSelection
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetSizeOfExtendedDataRecordSelection(
  CONST(uint8, AUTOMATIC) ClientId,                                                                                              /* PRQA S 3206 */ /* MD_DEM_3206 */
  P2VAR(uint16, AUTOMATIC, DEM_DCM_DATA)  SizeOfExtendedDataRecord                                                               /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_8.13 */
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
  if (Dem_APIChecks_MasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (Dem_APIChecks_NullPointer(SizeOfExtendedDataRecord ) == FALSE)                                                                       /* SBSW_DEM_POINTER_NULLPTR_CHECKING */  /* PRQA S 0315 */ /* MD_DEM_Dir1.1 */
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (Dem_APIChecks_ClientId(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else  
  if (Dem_APIChecks_IsMasterPartition() == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_Client_ClientAccess_GetSelectionResult(ClientId) == DEM_DTCSELECTOR_SELECTION_INIT)
  {
    /* missing prior call to Dem_SelectDTC() */
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  if (Dem_Client_ClientAccess_TestDTCRecordUpdateRequested(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  if (Dem_Client_ClientAccess_TestExtendedRecordSelected(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    if (Dem_Client_ClientAccess_TestDTCRecordUpdateDisabled(ClientId) == FALSE)
    {
      lReturnValue = DEM_PENDING;
    }
    else
    {
      lReturnValue = Dem_Dcm_ERec_GetSize(ClientId, SizeOfExtendedDataRecord);                                                   /* SBSW_DEM_POINTER_FORWARD_API */
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETSIZEOFEXTENDEDDATARECORDSELECTION_APIID, Dem_Det_ErrorRegisterGet());
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif


#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_DcmGetOBDFreezeFrameData
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_DcmGetOBDFreezeFrameData(
  P2VAR(uint32, AUTOMATIC, DEM_DCM_DATA)  DTC,                                                                                   /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_8.13 */
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  DestBuffer,                                                                             /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_8.13 */
  P2VAR(uint16, AUTOMATIC, DEM_DCM_DATA)  BufSize                                                                                /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_8.13 */
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
  if (Dem_APIChecks_MasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (Dem_APIChecks_IsObdIISupportedInVariant() == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  if (Dem_APIChecks_NullPointer(DTC) == FALSE)                                                                       /* SBSW_DEM_POINTER_NULLPTR_CHECKING */  /* PRQA S 0315 */ /* MD_DEM_Dir1.1 */
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (Dem_APIChecks_NullPointer(DestBuffer) == FALSE)                                                                       /* SBSW_DEM_POINTER_NULLPTR_CHECKING */  /* PRQA S 0315 */ /* MD_DEM_Dir1.1 */
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (Dem_APIChecks_NullPointer(BufSize) == FALSE)                                                                       /* SBSW_DEM_POINTER_NULLPTR_CHECKING */  /* PRQA S 0315 */ /* MD_DEM_Dir1.1 */
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else  
  if (Dem_APIChecks_IsMasterPartition() == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  {
# if (DEM_CFG_SUPPORT_OBDII == STD_ON)
    if (Dem_Cfg_IsObdIISupportedInVariant() == TRUE)
    {
      uint8  lSelectedIndex;
      Dem_EventIdType lEventId;
      boolean lModificationDetected;

      /* ----- Implementation ------------------------------------------------ */
      /* Check if provided buffer is large enough */
      if (*BufSize >= (Dem_Cfg_GlobalObdIIFFUdsSize() - 1u)) /* -1 as RecordNumber is not taken into account here */
      {
        do
        {
          lModificationDetected = FALSE;
          /* copy Mode02 index on the stack as it might change in the background */
          lSelectedIndex = Dem_Mem_GetFreezeFrameIndexMode02();

          /* first check if FF0 is available */
          if ((lSelectedIndex != Dem_Cfg_GlobalObdIIFFCount())
            && (Dem_DTC_TestDtcSuppression(Dem_Mem_FreezeFrameGetEvent(lSelectedIndex)) == FALSE)                                /* PRQA S 3415 */ /* MD_DEM_13.5_volatile */
            )
          {
            uint32 lUdsDtc;
            uint8 lUpdateState;
            
            lEventId = Dem_Mem_FreezeFrameGetEvent(lSelectedIndex);
            lUdsDtc = Dem_Cfg_EventUdsDtc(lEventId);
            lUpdateState = Dem_Event_GetDataCommitState(lEventId);

            if (Dem_Event_TestDataUpdateInProgress(lUpdateState) == FALSE)
            {
              Dem_Data_DestinationBuffer lDestinationBuffer;
              Dem_DataReport_BufferIndexType lBufferIdx;                                                                       /* PRQA S 0759 */ /* MD_MSR_Union */
              lBufferIdx.FreezeFrameIndex = lSelectedIndex;
              /* Initialize a DestinationBuffer Context. */
              Dem_Data_InitDestinationBuffer(&lDestinationBuffer, DestBuffer, *BufSize);                                         /* SBSW_DEM_CALL_DESTINATIONBUFFER_INIT */

              Dem_DataReport_ObdIIFreezeFrameCopyUdsData(lBufferIdx,
                &lDestinationBuffer,
                DEM_DATAREPORT_SOURCE_OBDII_FF_BUFFER);                               /* SBSW_DEM_POINTER_LOCAL_DESTINATIONBUFFER */


              if (lUpdateState != Dem_Event_GetDataCommitState(lEventId))
              { /* The event data has been modified while trying to copy the stored data. */
                /* We cannot be sure the OBD FF slot is still used by the same event nor data, so start from the
                beginning */
                lModificationDetected = TRUE;
              }
              else if ((Dem_Cfg_EventUdsDtc(Dem_Mem_FreezeFrameGetEvent(lSelectedIndex)) == lUdsDtc)
                && (Dem_Mem_FreezeFrameGetEvent(lSelectedIndex) != DEM_EVENT_INVALID))                                           /* PRQA S 3415 */ /* MD_DEM_13.5_volatile */
              {
                /* verify that the FreezeFrame EventId is still the same and valid */
                lReturnValue = E_OK;
                *DTC = lUdsDtc;                                                                                                  /* SBSW_DEM_POINTER_WRITE_API */
                *BufSize = (uint16)(Dem_Cfg_GlobalObdIIFFUdsSize() - 1u); /* -1 as RecordNumber is not taken into account here */   /* SBSW_DEM_POINTER_WRITE_API */
              }
              else
              { /* EventId has changed, so the freeze frame data too */
                lReturnValue = E_OK;
                *BufSize = 0u;                                                                                                   /* SBSW_DEM_POINTER_WRITE_API */
              }
            }
            else
            {
              /* The caller task has higher priority than Dem_MainFunction, but we cannot 'wait' for
              the update to complete. The requested data is not available at this moment. */
              lReturnValue = E_NOT_OK;
            }
          }
          else
          { /* OBD freezeFrame not available */
            *BufSize = 0u;                                                                                                       /* SBSW_DEM_POINTER_WRITE_API */
            lReturnValue = E_OK;
          }
        } while (lModificationDetected == TRUE);
      }
    }
    /* lReturnValue = E_NOT_OK initially set */
# endif /* (DEM_CFG_SUPPORT_OBDII == STD_ON) */
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_DCMGETOBDFREEZEFRAMEDATA_APIID, Dem_Det_ErrorRegisterGet());
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6030, 6050, 6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
#endif

                                           /* Dcm <-> Dem : OBD Freeze Frame */
/* ------------------------------------------------------------------------- */

#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_OBDII == STD_ON) && (DEM_CFG_SUPPORT_COMPATIBILITY == STD_OFF)
/* ****************************************************************************
 % Dem_DcmReadDataOfOBDFreezeFrame
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_DcmReadDataOfOBDFreezeFrame(
  uint8  PID,
  uint8  DataElementIndexOfPID,
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  DestBuffer,
  P2VAR(uint16, AUTOMATIC, DEM_DCM_DATA)  BufSize
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
  if (Dem_APIChecks_MasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (Dem_APIChecks_IsObdIISupportedInVariant() == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  if (Dem_APIChecks_NullPointer(DestBuffer) == FALSE)                                                                            /* SBSW_DEM_POINTER_NULLPTR_CHECKING */  /* PRQA S 0315 */ /* MD_DEM_Dir1.1 */
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (Dem_APIChecks_NullPointer(BufSize) == FALSE)                                                                               /* SBSW_DEM_POINTER_NULLPTR_CHECKING */  /* PRQA S 0315 */ /* MD_DEM_Dir1.1 */
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else  
  if (Dem_APIChecks_IsMasterPartition() == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  {
    Dem_EventIdType lFreezeFrameEventId;
    uint8 lSelectedIndex;

    /* ----- Implementation ------------------------------------------------ */
    boolean lModificationDetected;

    do
    {
      lModificationDetected = FALSE;

      /* copy Mode02 index on the stack as it might change in the background */
      lSelectedIndex = Dem_Mem_GetFreezeFrameIndexMode02();

      /* Verify that DTC is not suppressed and that OBD FreezeFrame is available and visible */
      if ( (Dem_Cfg_GlobalObdIIFFCount() != lSelectedIndex)
        && (Dem_DTC_TestDtcSuppression(Dem_Mem_FreezeFrameGetEvent(lSelectedIndex)) == FALSE)                                    /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
        )
      {
        uint8 lUpdateState;
        lFreezeFrameEventId = Dem_Mem_FreezeFrameGetEvent(lSelectedIndex);
        lUpdateState = Dem_Event_GetDataCommitState(lFreezeFrameEventId);

        if (Dem_Event_TestDataUpdateInProgress(lUpdateState) == FALSE)
        {
          {
            uint16 lTempBufSize;
            lTempBufSize = *BufSize;
            lReturnValue = Dem_DataReport_ObdIIFreezeFrameCopyPidData(lSelectedIndex, PID, DataElementIndexOfPID, DestBuffer, &lTempBufSize);  /* SBSW_DEM_POINTER_FORWARD_API_ARGUMENT_BUFFER */ /* SBSW_DEM_POINTER_FORWARD_STACK */
            *BufSize = lTempBufSize;                                                                                             /* SBSW_DEM_POINTER_WRITE_ARGUMENT */

            if ( (lReturnValue == E_OK)
              && (lUpdateState != Dem_Event_GetDataCommitState(lFreezeFrameEventId)) )                                           /* PRQA S 3415 */ /* MD_DEM_13.5_volatile */
            { /* The event data has been modified while trying to copy the stored data. */
              /* We cannot be sure the OBD FF slot is still used by the same event nor data, so start from the
              beginning */
              lReturnValue = E_NOT_OK;
              lModificationDetected = TRUE;
            }
            else if ( (Dem_Mem_FreezeFrameGetEvent(lSelectedIndex) != lFreezeFrameEventId)
              && (Dem_Mem_FreezeFrameGetEvent(lSelectedIndex) != DEM_EVENT_INVALID) )                                            /* PRQA S 3415 */ /* MD_DEM_13.5_volatile */
            {
              /* Verify that Freeze Frame event Id has not changed, no data can be returned */
              lReturnValue = E_NOT_OK;
            }
            else
            {
              /* MISRA */
            }
          }
        }
        else
        {
          /* The caller task has higher priority than Dem_MainFunction, but we cannot 'wait' for
          the update to complete. The requested data is not available at this moment. */
          lReturnValue = E_NOT_OK;
        }
      }
    }
    while (lModificationDetected == TRUE);
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_DCMREADDATAOFOBDFREEZEFRAME_APIID, Dem_Det_ErrorRegisterGet());
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6030, 6050, 6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
#endif


#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_OBDII == STD_ON) && (DEM_CFG_SUPPORT_COMPATIBILITY == STD_ON)
/* ****************************************************************************
 % Dem_DcmReadDataOfOBDFreezeFrame
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_DcmReadDataOfOBDFreezeFrame(
  uint8  PID,
  uint8  DataElementIndexOfPID,
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  DestBuffer,
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  BufSize
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
  if (Dem_APIChecks_MasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (Dem_APIChecks_IsObdIISupportedInVariant() == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  if (Dem_APIChecks_NullPointer(DestBuffer) == FALSE)                                                                            /* SBSW_DEM_POINTER_NULLPTR_CHECKING */  /* PRQA S 0315 */ /* MD_DEM_Dir1.1 */
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (Dem_APIChecks_NullPointer(BufSize) == FALSE)                                                                               /* SBSW_DEM_POINTER_NULLPTR_CHECKING */  /* PRQA S 0315 */ /* MD_DEM_Dir1.1 */
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else  
  if (Dem_APIChecks_IsMasterPartition() == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  {
    Dem_EventIdType lFreezeFrameEventId;
    uint8 lSelectedIndex;

    /* ----- Implementation ------------------------------------------------ */
    boolean lModificationDetected;

    do
    {
      lModificationDetected = FALSE;

      /* copy Mode02 index on the stack as it might change in the background */
      lSelectedIndex = Dem_Mem_GetFreezeFrameIndexMode02();

      /* Verify that DTC is not suppressed and that OBD FreezeFrame is available and visible */
      if ( (Dem_Cfg_GlobalObdIIFFCount() != lSelectedIndex)
        && (Dem_DTC_TestDtcSuppression(Dem_Mem_FreezeFrameGetEvent(lSelectedIndex)) == FALSE)                                    /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
        )
      {
        uint8 lUpdateState;
        lFreezeFrameEventId = Dem_Mem_FreezeFrameGetEvent(lSelectedIndex);
        lUpdateState = Dem_Event_GetDataCommitState(lFreezeFrameEventId);

        if (Dem_Event_TestDataUpdateInProgress(lUpdateState) == FALSE)
        {
          {
            uint16 lTempBufSize;
            lTempBufSize = *BufSize;
            lReturnValue = Dem_DataReport_ObdIIFreezeFrameCopyPidData(lSelectedIndex, PID, DataElementIndexOfPID, DestBuffer, &lTempBufSize);  /* SBSW_DEM_POINTER_FORWARD_API_ARGUMENT_BUFFER */ /* SBSW_DEM_POINTER_FORWARD_STACK */
            *BufSize = (uint8)lTempBufSize;                                                                                      /* SBSW_DEM_POINTER_WRITE_ARGUMENT */

            if ( (lReturnValue == E_OK)
              && (lUpdateState != Dem_Event_GetDataCommitState(lFreezeFrameEventId)) )                                           /* PRQA S 3415 */ /* MD_DEM_13.5_volatile */
            { /* The event data has been modified while trying to copy the stored data. */
              /* We cannot be sure the OBD FF slot is still used by the same event nor data, so start from the
              beginning */
              lReturnValue = E_NOT_OK;
              lModificationDetected = TRUE;
            }
            else if ( (Dem_Mem_FreezeFrameGetEvent(lSelectedIndex) != lFreezeFrameEventId)
              && (Dem_Mem_FreezeFrameGetEvent(lSelectedIndex) != DEM_EVENT_INVALID) )                                            /* PRQA S 3415 */ /* MD_DEM_13.5_volatile */
            {
              /* Verify that Freeze Frame event Id has not changed, no data can be returned */
              lReturnValue = E_NOT_OK;
            }
            else
            {
              /* MISRA */
            }
          }
        }
        else
        {
          /* The caller task has higher priority than Dem_MainFunction, but we cannot 'wait' for
          the update to complete. The requested data is not available at this moment. */
          lReturnValue = E_NOT_OK;
        }
      }
    }
    while (lModificationDetected == TRUE);
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_DCMREADDATAOFOBDFREEZEFRAME_APIID, Dem_Det_ErrorRegisterGet());
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6030, 6050, 6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
#endif


/* ****************************************************************************
 % Dem_SetExtendedDataRecordFilter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetExtendedDataRecordFilter(
  CONST(uint8, AUTOMATIC) ClientId,
  CONST(uint8, AUTOMATIC) RecordNumber,
  CONST(Dem_DTCOriginType, AUTOMATIC)  DTCOrigin,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat
)
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
  if (Dem_APIChecks_IsService19_16Enabled() == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  if (Dem_APIChecks_MasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (Dem_APIChecks_IsExtendedDataRecordFilterValid(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else 
  if (Dem_APIChecks_IsDTCOriginSupportedFor0x1916(DTCOrigin) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (Dem_APIChecks_IsDTCFormatSupportedFor0x1916(DTCFormat) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (Dem_APIChecks_IsMasterPartition() == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  if ((DTCOrigin != DEM_DTC_ORIGIN_PRIMARY_MEMORY) || (DTCFormat != DEM_DTC_FORMAT_UDS))
  {
    lReturnValue = E_NOT_OK;
  }
  else
  {
    /* ----- Implementation ------------------------------------------------ */
    lReturnValue = Dem_Client_ClientAccess_SetExtendedDataRecordFilter(ClientId, RecordNumber);
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_SETEXTENDEDDATARECORDFILTER_APIID, Dem_Det_ErrorRegisterGet());
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_GetNumberOfFilteredExtendedDataRecords
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetNumberOfFilteredExtendedDataRecords(
  CONST(uint8, AUTOMATIC) ClientId,
  P2VAR(uint16, AUTOMATIC, DEM_DCM_DATA)  NumberOfFilteredRecords,
  P2VAR(uint16, AUTOMATIC, DEM_DCM_DATA)  SizeOfExtendedDataRecord
)
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
  if (Dem_APIChecks_IsService19_16Enabled() == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  if (Dem_APIChecks_MasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (Dem_APIChecks_IsExtendedDataRecordFilterValid(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (Dem_APIChecks_IsExtendedDataRecordFilterSet(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  if (Dem_APIChecks_NullPointer(NumberOfFilteredRecords) == FALSE)                                                               /* SBSW_DEM_POINTER_NULLPTR_CHECKING */ /* PRQA S 0315 */ /* MD_DEM_Dir1.1 */
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (Dem_APIChecks_NullPointer(SizeOfExtendedDataRecord) == FALSE)                                                              /* SBSW_DEM_POINTER_NULLPTR_CHECKING */ /* PRQA S 0315 */ /* MD_DEM_Dir1.1 */
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (Dem_APIChecks_IsMasterPartition() == FALSE)                                                                                 
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  {
    /* ----- Implementation ------------------------------------------------ */                                                  
    lReturnValue = Dem_Client_ClientAccess_GetNumberOfFilteredExtendedDataRecords(                                                      /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    ClientId, NumberOfFilteredRecords, SizeOfExtendedDataRecord);  
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETNUMBEROFFILTEREDEXTENDEDDATARECORDS_APIID, Dem_Det_ErrorRegisterGet());
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_GetNextFilteredExtendedDataRecord
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetNextFilteredExtendedDataRecord(
  CONST(uint8, AUTOMATIC) ClientId,
  P2VAR(uint32, AUTOMATIC, DEM_DCM_DATA)  DTC,
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  DTCStatus,
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  DestBuffer,
  P2VAR(uint16, AUTOMATIC, DEM_DCM_DATA)  BufSize
)
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
  if (Dem_APIChecks_IsService19_16Enabled() == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  if (Dem_APIChecks_MasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (Dem_APIChecks_IsExtendedDataRecordFilterValid(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (Dem_APIChecks_IsExtendedDataRecordFilterSet(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  if (Dem_APIChecks_NullPointer(DTC) == FALSE)                                                                                   /* SBSW_DEM_POINTER_NULLPTR_CHECKING */ /* PRQA S 0315 */ /* MD_DEM_Dir1.1 */
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (Dem_APIChecks_NullPointer(DTCStatus) == FALSE)                                                                             /* SBSW_DEM_POINTER_NULLPTR_CHECKING */ /* PRQA S 0315 */ /* MD_DEM_Dir1.1 */
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (Dem_APIChecks_NullPointer(DestBuffer) == FALSE)                                                                            /* SBSW_DEM_POINTER_NULLPTR_CHECKING */ /* PRQA S 0315 */ /* MD_DEM_Dir1.1 */
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (Dem_APIChecks_NullPointer(BufSize) == FALSE)                                                                               /* SBSW_DEM_POINTER_NULLPTR_CHECKING */ /* PRQA S 0315 */ /* MD_DEM_Dir1.1 */
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (Dem_APIChecks_IsMasterPartition() == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  {
    /* ----- Implementation ------------------------------------------------ */
    lReturnValue = Dem_Client_ClientAccess_GetNextFilteredERecData(ClientId, DTC, DTCStatus, DestBuffer, BufSize);                      /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETNEXTFILTEREDEXTENDEDDATARECORD_APIID, Dem_Det_ErrorRegisterGet());
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6030, 6050, 6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

#if (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON)
/* ****************************************************************************
 % Dem_J1939DcmSetFreezeFrameFilter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_J1939DcmSetFreezeFrameFilter(
  Dem_J1939DcmSetFreezeFrameFilterType  FreezeFrameKind,
  uint8  ClientId
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
  if (Dem_APIChecks_MasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if ( (FreezeFrameKind != DEM_J1939DCM_FREEZEFRAME) && (FreezeFrameKind != DEM_J1939DCM_EXPANDED_FREEZEFRAME) )
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (Dem_Client_ClientAccess_TestNodeValid(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (Dem_Client_ClientAccess_TestFreezeFrameIteratorValid(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
# endif
  if (Dem_APIChecks_IsMasterPartition() == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  {
    /* ----- Implementation ------------------------------------------------ */
    lReturnValue = Dem_Client_ClientAccess_SetJ1939FreezeFrameIterator(ClientId, FreezeFrameKind);
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_J1939DCMSETFREEZEFRAMEFILTER_APIID, Dem_Det_ErrorRegisterGet());
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON */

#if (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON)
/* ****************************************************************************
 % Dem_J1939DcmGetNextFreezeFrame
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_J1939DcmGetNextFreezeFrame(
  P2VAR(uint32, AUTOMATIC, DEM_J1939DCM_DATA)  J1939DTC,
  P2VAR(uint8, AUTOMATIC, DEM_J1939DCM_DATA)  OccurrenceCounter,
  P2VAR(uint8, AUTOMATIC, DEM_J1939DCM_DATA)  DestBuffer,
  P2VAR(uint8, AUTOMATIC, DEM_J1939DCM_DATA)  BufSize, 
  uint8  ClientId
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = DEM_NO_SUCH_ELEMENT;

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
  if (Dem_APIChecks_MasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (Dem_APIChecks_NullPointer(J1939DTC ) == FALSE)                                                                             /* SBSW_DEM_POINTER_NULLPTR_CHECKING */  /* PRQA S 0315 */ /* MD_DEM_Dir1.1 */
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (Dem_APIChecks_NullPointer(OccurrenceCounter ) == FALSE)                                                                    /* SBSW_DEM_POINTER_NULLPTR_CHECKING */  /* PRQA S 0315 */ /* MD_DEM_Dir1.1 */
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (Dem_APIChecks_NullPointer(DestBuffer ) == FALSE)                                                                           /* SBSW_DEM_POINTER_NULLPTR_CHECKING */  /* PRQA S 0315 */ /* MD_DEM_Dir1.1 */
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (Dem_APIChecks_NullPointer(BufSize ) == FALSE)                                                                              /* SBSW_DEM_POINTER_NULLPTR_CHECKING */  /* PRQA S 0315 */ /* MD_DEM_Dir1.1 */
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_Client_ClientAccess_TestNodeValid(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (Dem_Client_ClientAccess_TestJ1939FreezeFrameFilterSet(ClientId) == FALSE)
  { 
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# endif
  if (Dem_APIChecks_IsMasterPartition() == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  {
    /* ----- Implementation ------------------------------------------------ */
    lReturnValue = Dem_Client_ClientAccess_GetNextJ1939FreezeFrame(ClientId, J1939DTC, OccurrenceCounter, DestBuffer, BufSize);         /* SBSW_DEM_POINTER_FORWARD_API_ARGUMENT_BUFFER */
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_J1939DCMGETNEXTFREEZEFRAME_APIID, Dem_Det_ErrorRegisterGet());
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON */

#if (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON)
/* ****************************************************************************
 % Dem_J1939DcmGetNextSPNInFreezeFrame
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_J1939DcmGetNextSPNInFreezeFrame(
  P2VAR(uint32, AUTOMATIC, DEM_J1939DCM_DATA)  SPNSupported,                                                                     /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_8.13 */
  P2VAR(uint8, AUTOMATIC, DEM_J1939DCM_DATA)  SPNDataLength,                                                                     /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_8.13 */
  uint8 ClientId
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = DEM_NO_SUCH_ELEMENT;
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
  if (Dem_APIChecks_MasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (Dem_APIChecks_NullPointer(SPNSupported ) == FALSE)                                                                         /* SBSW_DEM_POINTER_NULLPTR_CHECKING */  /* PRQA S 0315 */ /* MD_DEM_Dir1.1 */
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (Dem_APIChecks_NullPointer(SPNDataLength ) == FALSE)                                                                        /* SBSW_DEM_POINTER_NULLPTR_CHECKING */  /* PRQA S 0315 */ /* MD_DEM_Dir1.1 */
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_Client_ClientAccess_TestNodeValid(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
# endif
  if (Dem_APIChecks_IsMasterPartition() == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  {
    /* ----- Implementation ------------------------------------------------ */
    DEM_IGNORE_UNUSED_ARGUMENT(ClientId)                                                                                         /* PRQA S 1338, 3112 */ /* MD_MSR_DummyStmt, MD_DEM_14.2 */
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_J1939DCMGETNEXTSPNINFREEZEFRAME_APIID, Dem_Det_ErrorRegisterGet());
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON */

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ********************************************************************************************************************
 *  FILE SPECIFIC MISRA VIOLATIONS
 *********************************************************************************************************************/
/* PRQA L:DEM_API_IMPL */


#endif /* DEM_RECORDREADERIF_SVC_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_RecordReaderIF_Svc.h
 *********************************************************************************************************************/
