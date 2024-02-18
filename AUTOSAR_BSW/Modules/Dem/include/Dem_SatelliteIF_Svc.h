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
 *  \addtogroup Dem_SatelliteIF
 *  \{
 *  \file       Dem_SatelliteIF_Svc.h
 *  \brief      Service implementation file for the MICROSAR Dem
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

#if !defined (DEM_SATELLITEIF_SVC_H)                                                                                    /* PRQA S 0883 */ /* MD_DEM_19.15 */
#define DEM_SATELLITEIF_SVC_H

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
/* PRQA S 0759 EOF */ /* MD_MSR_Union */

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

/* Includes to access public functions belonging to other (top level)/ (logical)/- units to be used by this Unit */
/* ------------------------------------------------------------------------- */
#include "Dem_Satellite_Interface.h"

#include "Dem_Infrastructure_Interface.h"
#include "Dem_Core_Interface.h"
#include "Dem_FaultMemory_Interface.h"
#include "Dem_DiagnosticObserver_Interface.h"

/* ********************************************************************************************************************
 *  FILE SPECIFIC MISRA VIOLATIONS
 *********************************************************************************************************************/
/* PRQA S 3406 DEM_API_IMPL */ /* MD_DEM_8.6 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*! Filename declaration */
#define DEM_SATELLITEIF_SVC_FILENAME "Dem_SatelliteIF_Svc.h"

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
 % Dem_SetEventStatus
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
Dem_SetEventStatus(
  Dem_EventIdType     EventId,                                                                                                   /* PRQA S 1330 */ /* MD_DEM_8.3_rte */
  Dem_EventStatusType EventStatus
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
  if (Dem_APIChecks_GlobalConfigPointerAtleastInState(DEM_CONFIGVALIDATION_CONFIGPTR_PREINITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (Dem_APIChecks_EventId(EventId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if ( (Dem_APIChecks_SatelliteInState(Dem_Cfg_EventSatelliteId(EventId), DEM_INITSTATE_PREINITIALIZED) == FALSE)
    && (Dem_APIChecks_SatelliteInState(Dem_Cfg_EventSatelliteId(EventId), DEM_INITSTATE_INITIALIZED) == FALSE))                  
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (Dem_APIChecks_ReportedStatus(EventStatus) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (Dem_APIChecks_ReportedSimilarConditions(EventId, EventStatus) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (Dem_APIChecks_DebounceCounterNvConditions(EventId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  if (Dem_APIChecks_EventApplicationId(EventId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  /* ----- Global Precondition Checks ---------------------------------------- */
  if (Dem_OperationCycle_GetCurrentCycleStatus(Dem_Cfg_EventOperationCycle(EventId)) != DEM_OPERATIONCYCLE_CYCLE_STARTED)
  {
    lReturnValue = E_NOT_OK;
  }
  else
  if (Dem_Event_TestEventAvailable(EventId) == FALSE)
  {
    lReturnValue = E_NOT_OK;
  }
  else
  {
    /* ----- Implementation ------------------------------------------------ */
    lReturnValue =
      Dem_SatelliteSat_UpdateMonitorTrigger(
      Dem_Cfg_EventSatelliteId(EventId),
      Dem_Cfg_EventSatelliteEventId(EventId),
      EventStatus);
  }
  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_SETEVENTSTATUS_APIID, Dem_Det_ErrorRegisterGet());
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6030, 6050, 6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_ReportErrorStatus
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
FUNC(void, DEM_CODE)
Dem_ReportErrorStatus(
  Dem_EventIdType     EventId,
  Dem_EventStatusType EventStatus
  )
{
  Dem_Det_ErrorRegisterDefine()

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
  if (Dem_APIChecks_GlobalConfigPointerAtleastInState(DEM_CONFIGVALIDATION_CONFIGPTR_PREINITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (Dem_APIChecks_EventId(EventId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if ( (Dem_APIChecks_SatelliteInState(Dem_Cfg_EventSatelliteId(EventId), DEM_INITSTATE_PREINITIALIZED) == FALSE)
    && (Dem_APIChecks_SatelliteInState(Dem_Cfg_EventSatelliteId(EventId), DEM_INITSTATE_INITIALIZED) == FALSE) )
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (Dem_APIChecks_ReportedStatus(EventStatus) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (Dem_APIChecks_ReportedSimilarConditions(EventId, EventStatus) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (Dem_APIChecks_DebounceCounterNvConditions(EventId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  if (Dem_APIChecks_EventApplicationId(EventId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  /* ----- Global Precondition Checks ---------------------------------------- */
  if (Dem_OperationCycle_GetCurrentCycleStatus(Dem_Cfg_EventOperationCycle(EventId)) != DEM_OPERATIONCYCLE_CYCLE_STARTED)
  {
    /* Do nothing */
  }
  else
  if (Dem_Event_TestEventAvailable(EventId) == FALSE)
  {
    /* Do nothing */
  }
  else
  {
    /* ----- Implementation ------------------------------------------------ */
    (void)Dem_SatelliteSat_UpdateMonitorTrigger(
            Dem_Cfg_EventSatelliteId(EventId),
            Dem_Cfg_EventSatelliteEventId(EventId),
            EventStatus);
  }
  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_REPORTERRORSTATUS_APIID, Dem_Det_ErrorRegisterGet());
  }
}                                                                                                                                /* PRQA S 6030, 6050, 6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_ResetEventStatus
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
Dem_ResetEventStatus(
  Dem_EventIdType  EventId                                                                                                       /* PRQA S 1330 */ /* MD_DEM_8.3_rte */
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
  if (Dem_APIChecks_SatelliteInState(Dem_Cfg_EventSatelliteId(EventId), DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (Dem_APIChecks_EventApplicationId(EventId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
   /* ----- Global Precondition Checks ---------------------------------------- */
  if (Dem_UDSStatus_Test_TNCTOC(Dem_Event_GetUDSStatus(EventId)) == FALSE)
  {
    lReturnValue = E_NOT_OK;
  }
  else
  if (Dem_Event_TestEventAvailable(EventId) == FALSE)
  {
    lReturnValue = E_NOT_OK;
  }
  else
  if ( (Dem_Cfg_IsWwhObdSupportedInVariant() == TRUE)
    && (Dem_Event_TestMilSupport(EventId) == TRUE)
    && (Dem_UDSStatus_Test_CDTC(Dem_Event_GetUDSStatus(EventId)) == TRUE) )
  {
    /* Confirmed (independent of qualification state) WWH OBD events with MIL can't
       reset their test failed bit as this will effect the activation mode */
    lReturnValue = E_NOT_OK;
  }
  else
    /* ----- Implementation ------------------------------------------------ */
  {
      lReturnValue = Dem_SatelliteSat_ResetMonitorStatus(
                          Dem_Cfg_EventSatelliteId(EventId),
                          Dem_Cfg_EventSatelliteEventId(EventId));
  }
  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_RESETEVENTSTATUS_APIID, Dem_Det_ErrorRegisterGet());
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */


/* ****************************************************************************
 % Dem_ResetEventDebounceStatus
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
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_ResetEventDebounceStatus(
  Dem_EventIdType  EventId,                                                                                                      /* PRQA S 1330 */ /* MD_DEM_8.3_rte */
  Dem_DebounceResetStatusType  DebounceResetStatus
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
  if (Dem_APIChecks_GlobalConfigPointerAtleastInState(DEM_CONFIGVALIDATION_CONFIGPTR_PREINITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (Dem_APIChecks_EventId(EventId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if ( (Dem_APIChecks_SatelliteInState(Dem_Cfg_EventSatelliteId(EventId), DEM_INITSTATE_PREINITIALIZED) == FALSE)
    && (Dem_APIChecks_SatelliteInState(Dem_Cfg_EventSatelliteId(EventId), DEM_INITSTATE_INITIALIZED) == FALSE) )                 
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (Dem_APIChecks_EventApplicationId(EventId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (DebounceResetStatus >= DEM_DEBOUNCE_STATUS_INVALID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (Dem_APIChecks_DebounceCounterNvConditions(EventId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  {
    /* ----- Implementation ------------------------------------------------ */
    if ( (Dem_Event_TestEventAvailable(EventId) == TRUE)
         && (Dem_Cfg_EventDebounceType(EventId) != DEM_CFG_DEBOUNCETYPE_MONITORINTERNAL) )                                       
    {
      if (DebounceResetStatus == DEM_DEBOUNCE_STATUS_RESET)
      {
        Dem_SatelliteSat_ResetDebounceStatus(
            Dem_Cfg_EventSatelliteId(EventId),
            Dem_Cfg_EventSatelliteEventId(EventId));

      }
      else
      {
        Dem_SatelliteSat_FreezeDebounceStatus(
            Dem_Cfg_EventSatelliteId(EventId),
            Dem_Cfg_EventSatelliteEventId(EventId));
      }
      lReturnValue = E_OK;
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_RESETEVENTDEBOUNCESTATUS_APIID, Dem_Det_ErrorRegisterGet());
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_GetDebouncingOfEvent
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
Dem_GetDebouncingOfEvent(
  Dem_EventIdType  EventId,                                                                                                      /* PRQA S 1330 */ /* MD_DEM_8.3_rte */
  P2VAR(Dem_DebouncingStateType, AUTOMATIC, DEM_APPL_DATA)  DebouncingState
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
  if (Dem_APIChecks_NullPointer(DebouncingState) == FALSE)                                                                       /* SBSW_DEM_POINTER_NULLPTR_CHECKING */ /* PRQA S 0315 */ /* MD_DEM_Dir1.1 */
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  {
    /* ----- Implementation ------------------------------------------------ */
    if ( (Dem_Event_TestEventAvailable(EventId) == TRUE) )
    {
      (*DebouncingState) =                                                                                                       /* SBSW_DEM_POINTER_WRITE_API */
          Dem_SatelliteSat_GetDebouncingState(
              Dem_Cfg_EventSatelliteId(EventId),
              Dem_Cfg_EventSatelliteEventId(EventId));
      lReturnValue = E_OK;
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETDEBOUNCINGOFEVENT_APIID, Dem_Det_ErrorRegisterGet());
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_GetMonitorStatus
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
Dem_GetMonitorStatus(
  Dem_EventIdType  EventId,
  P2VAR(Dem_MonitorStatusType, AUTOMATIC, DEM_APPL_DATA)  MonitorStatus
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
  if (Dem_APIChecks_NullPointer(MonitorStatus) == FALSE)                                                                       /* SBSW_DEM_POINTER_NULLPTR_CHECKING */ /* PRQA S 0315 */ /* MD_DEM_Dir1.1 */
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  {
    /* ----- Implementation ------------------------------------------------ */
    if ( (Dem_Event_TestEventAvailable(EventId) == TRUE) )
    {
      (*MonitorStatus) = Dem_Satellite_GetMonitorStatus(                                                                         /* SBSW_DEM_POINTER_WRITE_API */
                           Dem_Cfg_EventSatelliteId(EventId),
                           Dem_Cfg_EventSatelliteEventId(EventId)
                           );
      lReturnValue = E_OK;
    }
    else
    {
      lReturnValue = E_NOT_OK;
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETMONITORSTATUS_APIID, Dem_Det_ErrorRegisterGet());
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6080, 6050 */ /* MD_MSR_STMIF, MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_GetFaultDetectionCounter
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
Dem_GetFaultDetectionCounter(
  Dem_EventIdType  EventId,                                                                                                      /* PRQA S 1330 */ /* MD_DEM_8.3_rte */
  P2VAR(sint8, AUTOMATIC, DEM_APPL_DATA)  FaultDetectionCounter                                                                  /* PRQA S 3673 */ /* MD_DEM_8.13 */
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
  if (Dem_APIChecks_NullPointer(FaultDetectionCounter) == FALSE)                                                                 /* SBSW_DEM_POINTER_NULLPTR_CHECKING */  /* PRQA S 0315 */ /* MD_DEM_Dir1.1 */
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  {
    /* ----- Implementation ------------------------------------------------ */
    if (Dem_Event_TestEventAvailable(EventId) == TRUE)
    {
      lReturnValue =
          Dem_Satellite_GetFaultDetectionCounter(                                                                                /* SBSW_DEM_POINTER_FORWARD_API */
              Dem_Cfg_EventSatelliteId(EventId),
              Dem_Cfg_EventSatelliteEventId(EventId),
              FaultDetectionCounter);
    }
    else
    {
      lReturnValue = E_NOT_OK;
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETFAULTDETECTIONCOUNTER_APIID, Dem_Det_ErrorRegisterGet());
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6030, 6050, 6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */


/* ****************************************************************************
 % Dem_NvM_InitDebounceData
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_NvM_InitDebounceData(
  void
  )
{
  Dem_Det_ErrorRegisterDefine()

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_Mem_IsDebounceNvEnabled() == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_CONFIG)
  }
  else
# endif
  if (Dem_APIChecks_MasterNotInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  {
    /* ----- Implementation ------------------------------------------------ */
#if (DEM_CFG_SUPPORT_DEBOUNCE_NV == STD_ON) /* Symbol Dem_Cfg_DebounceData not available in all configurations */
    Dem_MemSet((Dem_NvDataPtrType)&Dem_Cfg_DebounceData[0], 0x00, Dem_Cfg_GlobalDebounceStorageEventCount()*sizeof(Dem_Cfg_DebounceData[0]));       /* PRQA S 0602, 0310 */ /* MD_DEM_20.2, MD_DEM_11.4_cpy */ /* SBSW_DEM_MEMSET_DEBOUNCEDATA */
#endif
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_NVMINIT_APIID, Dem_Det_ErrorRegisterGet());
  }


  /* The DEM expects that the NVM by itself marks the NVRAM block as dirty */
  return E_OK;
}

/* ****************************************************************************
 % Dem_SetSI30Symptom
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
Dem_SetSI30Symptom(
  Dem_EventIdType EventId
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
  if (Dem_APIChecks_GlobalConfigPointerAtleastInState(DEM_CONFIGVALIDATION_CONFIGPTR_PREINITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (Dem_APIChecks_EventId(EventId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if ((Dem_APIChecks_SatelliteInState(Dem_Cfg_EventSatelliteId(EventId), DEM_INITSTATE_PREINITIALIZED) == FALSE)
    && (Dem_APIChecks_SatelliteInState(Dem_Cfg_EventSatelliteId(EventId), DEM_INITSTATE_INITIALIZED) == FALSE))
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (Dem_APIChecks_EventApplicationId(EventId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (Dem_APIChecks_IsCounterDebounce(EventId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  {
    /* ----- Implementation ------------------------------------------------ */
    if (Dem_Event_TestEventAvailable(EventId) == TRUE)
    {
      Dem_Satellite_SetStatusIndicatorSymptom(EventId);

      lReturnValue = E_OK;
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_SETSI30SYMPTOM_APIID, Dem_Det_ErrorRegisterGet());
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ********************************************************************************************************************
 *  FILE SPECIFIC MISRA VIOLATIONS
 *********************************************************************************************************************/
/* PRQA L:DEM_API_IMPL */


#endif /* DEM_SATELLITEIF_SVC_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_SatelliteIF_Implementation.h
 *********************************************************************************************************************/
