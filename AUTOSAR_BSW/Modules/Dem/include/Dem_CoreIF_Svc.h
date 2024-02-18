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
 *  \defgroup   Dem_CoreIF Dem CoreIF Functionality
 *  \{
 *  \file       Dem_CoreIF_Svc.h
 *  \brief      Service implementation of unit CoreIF.
 *  \details    Realizes the Dem external service APIs.
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_COREIF_SVC_H)
#define DEM_COREIF_SVC_H

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
#include "Dem_OperationCycle_Interface.h"
#include "Dem_DTC_Interface.h"
#include "Dem_Event_Interface.h"
#include "Dem_UDSStatus_Interface.h"
#include "Dem_StatusIndicator_Interface.h"

#include "Dem_Infrastructure_Interface.h"
#include "Dem_DiagnosticObserver_Interface.h"
#include "Dem_FaultMemory_Interface.h"
#include "Dem_RecordReader_Interface.h"
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
#define DEM_COREIF_SVC_FILENAME "Dem_CoreIF_Svc.h"

 /* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \addtogroup Dem_CoreIF_Public
 * \{
 */
  
#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
/* ****************************************************************************
 % Dem_SetEventAvailable
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
Dem_SetEventAvailable(
  Dem_EventIdType  EventId,
  boolean  AvailableStatus
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
#  if ( (DEM_FEATURE_NEED_EVENTAVAILABLE_NV == STD_ON) || (DEM_FEATURE_NEED_EVENTAVAILABLE_DEFAULT == STD_ON) )
  if (Dem_APIChecks_MasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
#  else
  if (Dem_APIChecks_MasterAtLeastInState(DEM_INITSTATE_PREINITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
#  endif
  else
  if (Dem_APIChecks_EventId(EventId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (Dem_APIChecks_IsBoolean(AvailableStatus) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (Dem_APIChecks_IsMasterPartition() == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  {
    /* ----- Implementation ------------------------------------------------ */
    if (Dem_Cfg_EventAvailableByVariant(EventId) == TRUE)
    {
      if (AvailableStatus == TRUE)
      {
        Dem_Event_Reconnect(EventId);
        lReturnValue = E_OK;
      }
      else
      {
        lReturnValue = Dem_Event_Disconnect(EventId);
      }
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_SETEVENTAVAILABLE_APIID, Dem_Det_ErrorRegisterGet());
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif /* (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON) */


                                         /* Service Interface EventAvailable */
/* ------------------------------------------------------------------------- */
#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
/* ****************************************************************************
 % Dem_GetEventAvailable
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
Dem_GetEventAvailable(
  Dem_EventIdType  EventId,                                                                                                      /* PRQA S 1330, 3206 */ /* MD_DEM_8.3_rte, MD_DEM_3206 */
  P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA)  AvailableStatus
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */

#  if (DEM_FEATURE_NEED_EVENTAVAILABLE_NV == STD_ON)
  if (Dem_APIChecks_MasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
#  else
  if (Dem_APIChecks_MasterAtLeastInState(DEM_INITSTATE_PREINITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
#  endif
  else
  if (Dem_APIChecks_EventId(EventId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (Dem_APIChecks_NullPointer(AvailableStatus) == FALSE)                                                                       /* SBSW_DEM_POINTER_NULLPTR_CHECKING */  /* PRQA S 0315 */ /* MD_DEM_Dir1.1 */
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
    *AvailableStatus = (boolean)( (Dem_Event_TestEventAvailable(EventId) == TRUE) );                                             /* SBSW_DEM_POINTER_WRITE_API */

    lReturnValue = E_OK;
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETEVENTAVAILABLE_APIID, Dem_Det_ErrorRegisterGet());
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON) */

/* ****************************************************************************
 % Dem_SetOperationCycleState
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
Dem_SetOperationCycleState(
  uint8  OperationCycleId,                                                                                                       /* PRQA S 1330 */ /* MD_DEM_8.3_rte */
  Dem_OperationCycleStateType  CycleState
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
#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (OperationCycleId >= Dem_Cfg_GlobalCycleCount())
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (CycleState >= DEM_CYCLE_STATE_INVALID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
#endif
  if (Dem_APIChecks_IsMasterPartition() == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  {
    /* ----- Implementation ------------------------------------------------ */
    lReturnValue = Dem_OperationCycle_SetState(OperationCycleId, CycleState);
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_SETOPERATIONCYCLESTATE_APIID, Dem_Det_ErrorRegisterGet());
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6030, 6050, 6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_GetOperationCycleState
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
Dem_GetOperationCycleState(
  uint8  OperationCycleId,                                                                                                       /* PRQA S 1330 */ /* MD_DEM_8.3_rte */
  P2VAR(Dem_OperationCycleStateType, AUTOMATIC, DEM_APPL_DATA)  CycleState
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
#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (OperationCycleId >= Dem_Cfg_GlobalCycleCount())
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
#endif
  if (Dem_APIChecks_NullPointer(CycleState) == FALSE)                                                                       /* SBSW_DEM_POINTER_NULLPTR_CHECKING */ /* PRQA S 0315 */ /* MD_DEM_Dir1.1 */
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
     lReturnValue = E_OK;
     *CycleState = Dem_OperationCycle_GetCycleState(OperationCycleId);                                                           /* SBSW_DEM_POINTER_WRITE_API */
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETOPERATIONCYCLESTATE_APIID, Dem_Det_ErrorRegisterGet());
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6030, 6050, 6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

 
#if (DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON)
/* ****************************************************************************
 % Dem_GetWIRStatus
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
Dem_GetWIRStatus(
  Dem_EventIdType EventId,                                                                                                       /* PRQA S 1330 */ /* MD_DEM_8.3_rte */
  P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA) WIRStatus
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
  if (Dem_APIChecks_NullPointer(WIRStatus) == FALSE)                                                                       /* SBSW_DEM_POINTER_NULLPTR_CHECKING */ /* PRQA S 0315 */ /* MD_DEM_Dir1.1 */
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
    if ( (Dem_Event_TestEventAvailable(EventId) == TRUE) )
    {
      *WIRStatus = Dem_DTC_GetWIRStatus(EventId);                                                                                /* SBSW_DEM_POINTER_WRITE_API */
      lReturnValue = E_OK;
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETWIRSTATUS_APIID, Dem_Det_ErrorRegisterGet());
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif /* (DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON) */

#if (DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON)
/* ****************************************************************************
 % Dem_SetWIRStatus
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
Dem_SetWIRStatus(
  Dem_EventIdType EventId,                                                                                                       /* PRQA S 1330 */ /* MD_DEM_8.3_rte */
  boolean WIRStatus
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
  if (Dem_APIChecks_IsBoolean(WIRStatus) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (Dem_APIChecks_IsMasterPartition() == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  {
    /* ----- Implementation ------------------------------------------------ */
    if ( (Dem_Event_TestEventAvailable(EventId) == TRUE) )
    {
      lReturnValue = Dem_DTC_SetWIRStatus(EventId, WIRStatus);
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_SETWIRSTATUS_APIID, Dem_Det_ErrorRegisterGet());
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif /* (DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON) */

/* ****************************************************************************
 % Dem_GetEventUdsStatus
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
Dem_GetEventUdsStatus(
  Dem_EventIdType  EventId,                                                                                                      /* PRQA S 1330 */ /* MD_DEM_8.3_rte */
  P2VAR(Dem_UdsStatusByteType, AUTOMATIC, DEM_APPL_DATA)  UDSStatusByte
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
  if (Dem_APIChecks_GlobalConfigPointerInState(DEM_CONFIGVALIDATION_CONFIGPTR_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
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
  if (Dem_APIChecks_NullPointer(UDSStatusByte) == FALSE)                                                                         /* SBSW_DEM_POINTER_NULLPTR_CHECKING */ /* PRQA S 0315 */ /* MD_DEM_Dir1.1 */
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  {
    /* ----- Implementation ------------------------------------------------ */
    lReturnValue = Dem_Event_GetEventUDSStatus(EventId, UDSStatusByte);                                                          /* SBSW_DEM_POINTER_FORWARD_API */
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETEVENTUDSSTATUS_APIID, Dem_Det_ErrorRegisterGet());
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6080 */ /* MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_GetEventFailed
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
Dem_GetEventFailed(
  Dem_EventIdType  EventId,                                                                                                      /* PRQA S 1330 */ /* MD_DEM_8.3_rte */
  P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA)  EventFailed
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
  if (Dem_APIChecks_GlobalConfigPointerInState(DEM_CONFIGVALIDATION_CONFIGPTR_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
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
  if (Dem_APIChecks_NullPointer(EventFailed) == FALSE)                                                                           /* SBSW_DEM_POINTER_NULLPTR_CHECKING */ /* PRQA S 0315 */ /* MD_DEM_Dir1.1 */
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  {
    /* ----- Implementation ------------------------------------------------ */
    lReturnValue = Dem_Event_GetEventFailed(EventId, EventFailed);                                                               /* SBSW_DEM_POINTER_FORWARD_API */
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETEVENTFAILED_APIID, Dem_Det_ErrorRegisterGet());
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6080 */ /* MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_GetEventTested
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
Dem_GetEventTested(
  Dem_EventIdType  EventId,                                                                                                      /* PRQA S 1330 */ /* MD_DEM_8.3_rte */
  P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA)  EventTested
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
  if (Dem_APIChecks_GlobalConfigPointerInState(DEM_CONFIGVALIDATION_CONFIGPTR_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
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
  if (Dem_APIChecks_NullPointer(EventTested) == FALSE)                                                                           /* SBSW_DEM_POINTER_NULLPTR_CHECKING */ /* PRQA S 0315 */ /* MD_DEM_Dir1.1 */
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  {
    /* ----- Implementation ------------------------------------------------ */
    lReturnValue = Dem_Event_GetEventTested(EventId, EventTested);                                                               /* SBSW_DEM_POINTER_FORWARD_API */
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETEVENTTESTED_APIID, Dem_Det_ErrorRegisterGet());
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */

                                         /* Service Interface DiagnosticInfo */
/* ------------------------------------------------------------------------- */
/* ****************************************************************************
 % Dem_GetDTCOfEvent
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
Dem_GetDTCOfEvent(
  Dem_EventIdType  EventId,                                                                                                      /* PRQA S 1330 */ /* MD_DEM_8.3_rte */
  Dem_DTCFormatType  DTCFormat,
  P2VAR(uint32, AUTOMATIC, DEM_APPL_DATA)  DTCOfEvent
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
  if (Dem_APIChecks_GlobalConfigPointerInState(DEM_CONFIGVALIDATION_CONFIGPTR_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
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
#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (DTCFormat >= DEM_DTC_FORMAT_INVALID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
#endif
  if (Dem_APIChecks_NullPointer(DTCOfEvent) == FALSE)                                                                            /* SBSW_DEM_POINTER_NULLPTR_CHECKING */  /* PRQA S 0315 */ /* MD_DEM_Dir1.1 */
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  {
    /* ----- Implementation ------------------------------------------------ */
    if ( (Dem_Event_TestEventAvailable(EventId) == TRUE) )
    {
      if (Dem_DTC_GetFormatedDTCByEvent(EventId, DTCFormat, DTCOfEvent) == E_OK)                                                  /* SBSW_DEM_POINTER_FORWARD_API_ARGUMENT_BUFFER */
      {
        lReturnValue = E_OK;
      }
      else
      {
        lReturnValue = DEM_E_NO_DTC_AVAILABLE;
      }
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETDTCOFEVENT_APIID, Dem_Det_ErrorRegisterGet());
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */


/* ****************************************************************************
 % Dem_NvM_InitStatusData
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
Dem_NvM_InitStatusData(
  void
  )
{
  Dem_Det_ErrorRegisterDefine()

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
  if (Dem_APIChecks_MasterNotInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  {
    Dem_EventIdType lEventId;

    /* ----- Implementation ------------------------------------------------ */
    for (lEventId = DEM_EVENT_FIRST; lEventId < Dem_Cfg_GlobalEventCount(); ++lEventId)
    {
      Dem_Event_InitNvData(lEventId);
    }

#if (DEM_FEATURE_NEED_MIL_GROUPS == STD_ON)
    {
      uint16 lMilGroupIndex;
      lMilGroupIndex = Dem_Cfg_GlobalMilGroupCount();
      while (lMilGroupIndex != DEM_CFG_MIL_GROUP_INVALID)
      {
        lMilGroupIndex--;
        Dem_Mem_InitMilGroupTripCount(lMilGroupIndex);
        Dem_EventInternalStatus_SetMilGroupPendingCount(lMilGroupIndex, 0u);
      }
    }
#endif

#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
    {
      Dem_Memory_InitConfirmedChronology();
    }
#endif

#if (DEM_FEATURE_NEED_PID01_CALCULATION == STD_ON)
    /* all monitors are set to not complete -> reserved bits are set to 0 */
    if ((Dem_Cfg_GlobalPid01SupportedMask() & DEM_READINESS_SUPPORT_COMPRESSION) != 0u)
    {
      Dem_Mem_SetPid01CompletedMask(DEM_READINESS_INITIALIZE_PID01COMPLETED_COMPRESSION);
    }
    else
    {
      Dem_Mem_SetPid01CompletedMask(DEM_READINESS_INITIALIZE_PID01COMPLETED_SPARK);
    }
#endif

    Dem_Statistics_SetFirstFailedEvent(DEM_EVENT_INVALID);
    Dem_Statistics_SetFirstConfirmedEvent(DEM_EVENT_INVALID);
    Dem_Statistics_SetMostRecentFailedEvent(DEM_EVENT_INVALID);
    Dem_Statistics_SetMostRecentConfirmedEvent(DEM_EVENT_INVALID);
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_NVMINIT_APIID, Dem_Det_ErrorRegisterGet());
  }


  /* The DEM expects that the NVM by itself marks the NVRAM block as dirty */
  return E_OK;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

 
#if (DEM_CFG_SUPPORT_EVENTAVAILABLE_NV == STD_ON)
/* ****************************************************************************
 % Dem_NvM_InitEventAvailableData
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_NvM_InitEventAvailableData(
  void
  )
{
  Dem_Det_ErrorRegisterDefine()

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
  if (Dem_APIChecks_MasterNotInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  {
    /* ----- Implementation ------------------------------------------------ */
    Dem_MemSet((Dem_NvDataPtrType)&Dem_Cfg_EventAvailableData[0], 0x00, Dem_Cfg_GlobalEventAvailableDataSize() * sizeof(Dem_Cfg_EventAvailableData[0]));   /* PRQA S 0310, 0602 */ /* MD_DEM_11.4_cpy, MD_DEM_20.2 */ /* SBSW_DEM_MEMSET_EVENTAVAILABLEDATA */
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_NVMINIT_APIID, Dem_Det_ErrorRegisterGet());
  }


  /* The DEM expects that the NVM by itself marks the NVRAM block as dirty */
  return E_OK;
}
#endif


#if (DEM_FEATURE_NEED_AGING_DATA == STD_ON)
/* ****************************************************************************
 % Dem_NvM_InitAgingData
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
Dem_NvM_InitAgingData(
  void
  )
{
  Dem_Det_ErrorRegisterDefine()

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
  if (Dem_APIChecks_MasterNotInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  {
    /* ----- Implementation ------------------------------------------------ */
# if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON)
    /* Set all aging counter array entries to invalid */
    Dem_MemSet((Dem_DataPtrType)&(Dem_Cfg_GetAgingData().AgingCounter[0]),                                                       /* PRQA S 0310, 0602 */ /* MD_DEM_11.4_cpy, MD_DEM_20.2 */ /* SBSW_DEM_MEMSET_AGINGDATA_AGINGCOUNTER */
      0xFF,
      DEM_CFG_MAX_NUMBER_AGING_DTCS * sizeof(Dem_Cfg_GetAgingData().AgingCounter[0]));
# endif

# if (DEM_CFG_DATA_AGED_COUNTER == STD_ON)
    /* Set all aged counter array entries to the initial value */
    Dem_MemSet((Dem_DataPtrType)&(Dem_Cfg_GetAgingData().AgedCounter[0]),                                                        /* PRQA S 0310, 0602 */ /* MD_DEM_11.4_cpy, MD_DEM_20.2 */ /* SBSW_DEM_MEMSET_AGINGDATA_AGEDCOUNTER */
      DEM_DTC_AGED_COUNTER_INIT_VALUE,
      DEM_CFG_MAX_NUMBER_AGED_DTCS * sizeof(Dem_Cfg_GetAgingData().AgedCounter[0]));
# endif
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_NVMINIT_APIID, Dem_Det_ErrorRegisterGet());
  }


  /* The DEM expects that the NVM by itself marks the NVRAM block as dirty */
  return E_OK;
}
#endif

/* ****************************************************************************
% Dem_NvM_InitCycleCounterData
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
Dem_NvM_InitCycleCounterData(
  void
)
{
  Dem_Det_ErrorRegisterDefine()

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
  if (Dem_APIChecks_MasterNotInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  {
    Dem_DTC_InitMemIndependentCycleCounterDataNv();
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_NVMINIT_APIID, Dem_Det_ErrorRegisterGet());
  }

  return E_OK;
}

/* ****************************************************************************
 * Dem_GetSI30Status
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
Dem_GetSI30Status(
  Dem_EventIdType EventId,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) Status
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
  if (Dem_APIChecks_IsExtendedFiMEnabled() == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  if (Dem_APIChecks_GlobalConfigPointerAtleastInState(DEM_CONFIGVALIDATION_CONFIGPTR_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (Dem_APIChecks_MasterAtLeastInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (Dem_APIChecks_EventId(EventId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (Dem_APIChecks_NullPointer(Status) == FALSE)                                                                                /* SBSW_DEM_POINTER_NULLPTR_CHECKING */ /* PRQA S 0315 */ /* MD_DEM_Dir1.1 */
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  {
    /* ----- Implementation ------------------------------------------------ */
    if (Dem_Event_TestEventAvailable(EventId) == TRUE)
    {
      lReturnValue = Dem_StatusIndicator_GetStatusIndicator(EventId, Status);                                                    /* SBSW_DEM_POINTER_FORWARD_API */
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETSI30STATUS_APIID, Dem_Det_ErrorRegisterGet());
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ********************************************************************************************************************
 *  FILE SPECIFIC MISRA VIOLATIONS
 *********************************************************************************************************************/
/* PRQA L:DEM_API_IMPL */


#endif /* DEM_COREIF_SVC_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_CoreIF_Svc.h
 *********************************************************************************************************************/
