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
/*!  Project    MICROSAR Diagnostic Event Manager (Dem)
 *
 *  \addtogroup Dem_DebounceIF
 *  \{
 *  \file       Dem_DebounceIF_Implementation.h
 *  \brief      Implementation file for the MICROSAR Dem
 *  \details    Implementation of DebounceIF subcomponent
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_DEBOUNCEIF_IMPLEMENTATION_H)
#define DEM_DEBOUNCEIF_IMPLEMENTATION_H

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

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_DebounceIF_Interface.h"

/* Includes to access public functions belonging to other (top level)/ (logical)/ - units to be used by this Unit */
/* ------------------------------------------------------------------------- */
#include "Dem_DebounceBase_Interface.h"
#include "Dem_DebounceCounterBased_Interface.h"
#include "Dem_DebounceMonitorInternal_Interface.h"
#include "Dem_DebounceTimeBased_Interface.h"

#include "Dem_Infrastructure_Interface.h"
#include "Dem_SatelliteData_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*! Filename declaration */
#define DEM_DEBOUNCEIF_IMPLEMENTATION_FILENAME "Dem_DebounceIF_Implementation.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/


#define DEM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

DEM_LOCAL CONST(Dem_DebounceFunctionTableType, DEM_CONST) Dem_Debounce_InvalidFunctionTable =                                    /* PRQA S 3218 */ /* MD_DEM_8.7 */
{
  Dem_Debounce_InvalidCalculate,
  Dem_Debounce_InvalidVoid,
  Dem_Debounce_InvalidVoid,
  Dem_Debounce_InvalidGetDebouncingState,
  Dem_Debounce_InvalidUpdateMax,
  Dem_Debounce_InvalidUpdateMax,
  Dem_Debounce_InvalidGetFDC,
  Dem_Debounce_InvalidGetFDC,
  Dem_Debounce_InvalidGetDebouncingResult,
  Dem_Debounce_InvalidRestoreDebounceValue
};

#define DEM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ********************************************************************************************************************
 *  SUBCOMPONENT API PRIVATE FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*!
 * \defgroup Dem_Debounce_Private Private Methods
 * \{
 */


/* ****************************************************************************
 * Dem_Debounce_RemoveSimilarConditionQualifier
 *****************************************************************************/
/*!
 * \brief         Remove similar condition qualifier for debouncing calculation.
 *
 * \details       Remove similar condition qualifier for debouncing calculation.
 *
 * \param[in]     MonitorTrigger
 *                The reported MonitorTrigger.
 *
 * \return        The monitor trigger mapped to the basic event status type.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different events
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventStatusType, DEM_CODE)
Dem_Debounce_RemoveSimilarConditionQualifier(
  CONST(Dem_EventStatusType, AUTOMATIC)  MonitorTrigger
  );

/* ********************************************************************************************************************
 *  SUBCOMPONENT API PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/

/* ****************************************************************************
 % Dem_Debounce_RemoveSimilarConditionQualifier
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventStatusType, DEM_CODE)
Dem_Debounce_RemoveSimilarConditionQualifier(
  CONST(Dem_EventStatusType, AUTOMATIC)  MonitorTrigger
  )
{
  Dem_EventStatusType lMonitorTrigger;

  if ( (Dem_SatelliteData_IsSimilarConditionsEnabled() == TRUE)
    && (Dem_Cfg_IsObdSupportedInVariant() == TRUE))
  {
    switch (MonitorTrigger)
    {
    case DEM_EVENT_STATUS_PREPASSED_CONDITIONS_NOT_FULFILLED:
      lMonitorTrigger = DEM_EVENT_STATUS_PREPASSED;
      break;
    case DEM_EVENT_STATUS_PASSED_CONDITIONS_NOT_FULFILLED:
      lMonitorTrigger = DEM_EVENT_STATUS_PASSED;
      break;
    case DEM_EVENT_STATUS_PREFAILED_CONDITIONS_NOT_FULFILLED:
      lMonitorTrigger = DEM_EVENT_STATUS_PREFAILED;
      break;
    case DEM_EVENT_STATUS_FAILED_CONDITIONS_NOT_FULFILLED:
      lMonitorTrigger = DEM_EVENT_STATUS_FAILED;
      break;
    default:
      lMonitorTrigger = MonitorTrigger;
      break;
    }
  }
  else
  {
    lMonitorTrigger = MonitorTrigger;
  }

  return lMonitorTrigger;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION IMPLEMENTATION
 *********************************************************************************************************************/

/*!
 * \addtogroup Dem_Debounce_Public
 * \{
 */

/* ****************************************************************************
 % Dem_Debounce_GetDebouncingResult
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_Debounce_GetDebouncingResult(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteData
  )
{
  return Dem_DebounceBase_GetDebouncingResult(DebounceInfoPtr, SatelliteData);                                                   /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
}

/* ****************************************************************************
 % Dem_Debounce_ResetDebouncing
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_Debounce_ResetDebouncing(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)  DebounceInfoPtr,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteData
  )
{
  Dem_DebounceBase_Reset(DebounceInfoPtr);                                                                                       /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  return Dem_DebounceBase_GetDebouncingResult(DebounceInfoPtr, SatelliteData);                                                   /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
}

/* ****************************************************************************
 % Dem_Debounce_FreezeDebouncing
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_Debounce_FreezeDebouncing(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)  DebounceInfoPtr,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteData
  )
{
  Dem_DebounceBase_Freeze(DebounceInfoPtr);                                                                                      /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  return Dem_DebounceBase_GetDebouncingResult(DebounceInfoPtr, SatelliteData);                                                   /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
}

/* ****************************************************************************
 % Dem_Debounce_CalculateDebouncing
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Debounce_CalculateDebouncing(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)  DebounceInfoPtr
  )
{
  Dem_EventStatusType lOldMonitorTrigger;
  Dem_EventStatusType lNewMonitorTrigger;

  lOldMonitorTrigger = Dem_DebounceBase_GetMonitorTrigger(DebounceInfoPtr);                                                      /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  lNewMonitorTrigger = Dem_Debounce_RemoveSimilarConditionQualifier(lOldMonitorTrigger);

  Dem_DebounceBase_SetMonitorTrigger(DebounceInfoPtr, lNewMonitorTrigger);                                                       /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  return Dem_DebounceBase_CalculateDebouncing(DebounceInfoPtr);                                                                  /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
}

/* ****************************************************************************
 % Dem_Debounce_SetMonitorTrigger
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Debounce_SetMonitorTrigger(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)  DebounceInfoPtr,
  CONST(Dem_EventStatusType, AUTOMATIC)           MonitorTrigger
  )
{
  Dem_DebounceBase_SetMonitorTrigger(DebounceInfoPtr, MonitorTrigger);                                                           /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
}

/* ****************************************************************************
 % Dem_Debounce_GetMonitorTrigger
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventStatusType, DEM_CODE)
Dem_Debounce_GetMonitorTrigger(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
  )
{
  return Dem_DebounceBase_GetMonitorTrigger(DebounceInfoPtr);                                                                    /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
}

/* ****************************************************************************
 % Dem_Debounce_TestRequestFdcProcessing()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Debounce_TestRequestFdcProcessing(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr
  )
{
  return Dem_DebounceBase_TestRequestFdcProcessing(DebounceInfoPtr);                                                             /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
}

/* ****************************************************************************
 % Dem_Debounce_TestFdcThresholdExceeded()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Debounce_TestFdcThresholdExceeded(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr
  )
{
  return Dem_DebounceBase_TestFdcThresholdExceeded(DebounceInfoPtr);                                                             /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
}

/* ****************************************************************************
 % Dem_Debounce_TestMaximumFdcExceeded()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Debounce_TestMaximumFdcExceeded(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr
  )
{
  return Dem_DebounceBase_TestMaximumFdcExceeded(DebounceInfoPtr);                                                               /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
}

/* ****************************************************************************
 %  Dem_Debounce_GetFaultDetectionCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Debounce_GetFaultDetectionCounter(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr,
  CONSTP2VAR(sint8, AUTOMATIC, DEM_APPL_DATA) FaultDetectionCounter
  )
{
  return Dem_DebounceBase_GetFaultDetectionCounter(DebounceInfoPtr, FaultDetectionCounter);                                      /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
}

/* ****************************************************************************
 % Dem_Debounce_GetMaxFaultDetectionCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(sint8, DEM_CODE)
Dem_Debounce_GetMaxFaultDetectionCounter(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr
  )
{
  sint8 lFdcMax;
  (void)Dem_DebounceBase_GetMaxFaultDetectionCounter(DebounceInfoPtr, &lFdcMax);                                                 /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  return lFdcMax;
}

/* ****************************************************************************
 % Dem_Debounce_GetEventId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Debounce_GetEventId(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr
  )
{
  return Dem_DebounceBase_GetEventId(DebounceInfoPtr);                                                                           /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
}

/* ****************************************************************************
 % Dem_Debounce_GetDebouncingState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_DebouncingStateType, DEM_CODE)
Dem_Debounce_GetDebouncingState(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
  )
{
  return Dem_DebounceBase_GetDebouncingState(DebounceInfoPtr);                                                                   /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
}

/* ****************************************************************************
 % Dem_Debounce_TestDebouncingChanged
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Debounce_TestDebouncingChanged(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
  )
{
  return Dem_DebounceBase_TestDebouncingChanged(DebounceInfoPtr);                                                                /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
}

/* ****************************************************************************
 % Dem_Debounce_DebounceInfoInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_DebounceBase_InfoPtrType, DEM_CODE)
Dem_Debounce_DebounceInfoInit(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONSTP2VAR(Dem_Debounce_InfoType, AUTOMATIC, AUTOMATIC)  DebounceInfoData,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteData
  )
{
  Dem_DebounceBase_InfoPtrType base;

  switch(Dem_Cfg_EventDebounceType(EventId))
  {
  case DEM_CFG_DEBOUNCETYPE_COUNTER:
    base = Dem_DebounceCounterBased_InfoInit(&(DebounceInfoData->CounterBased), EventId, SatelliteData);                         /* SBSW_DEM_CALL_DEBOUNCEINFO_INIT */
    break;
  case DEM_CFG_DEBOUNCETYPE_TIMER:
    base = Dem_DebounceTimeBased_InfoInit(&(DebounceInfoData->TimeBased), EventId, SatelliteData);                               /* SBSW_DEM_CALL_DEBOUNCEINFO_INIT */
    break;
  case DEM_CFG_DEBOUNCETYPE_MONITORINTERNAL: 
    base = Dem_DebounceMonitorInternal_InfoInit(&(DebounceInfoData->MonitorInternal), EventId, SatelliteData);                   /* SBSW_DEM_CALL_DEBOUNCEINFO_INIT */
    break;
  default:
    if (Dem_Error_isDevRunTimeChecksEnabled() == TRUE)
    {
      Dem_Error_RunTimeCheckFailed(DEM_DEBOUNCEIF_IMPLEMENTATION_FILENAME, __LINE__);                                              /* SBSW_DEM_POINTER_RUNTIME_CHECK */
    } 
    base = Dem_DebounceBase_InfoInitDefault(&(DebounceInfoData->InvalidDebounce), &Dem_Debounce_InvalidFunctionTable, EventId);  /* SBSW_DEM_CALL_DEBOUNCEINFO_INIT */
    break;
  }

  return base;
}


/* ****************************************************************************
 % Dem_Debounce_TestQualifiedResult
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Debounce_TestQualifiedResult(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
  )
{
  return (boolean)(Dem_DebounceBase_GetMonitorTrigger(DebounceInfoPtr) <= DEM_EVENT_STATUS_FAILED);                              /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
}

/* ****************************************************************************
 % Dem_Debounce_PreInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Debounce_PreInit(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  )
{
  Dem_DebounceBase_PreInit(SatelliteId, MonitorId);
}

/* ****************************************************************************
 % Dem_Debounce_RestoreDebounceValue
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_Debounce_RestoreDebounceValue(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC) SatelliteData,
  CONST(sint16, AUTOMATIC) Value,
  CONST(boolean, AUTOMATIC) ExpectedThreshold
  )
{
  return Dem_DebounceBase_RestoreDebounceValue(DebounceInfoPtr, SatelliteData, Value, ExpectedThreshold);                        /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
}


/* ****************************************************************************
 % Dem_Debounce_InvalidCalculate
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_Debounce_InvalidCalculate(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)  DebounceInfoPtr                                                                /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_8.13_Internal */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DebounceInfoPtr)                                                                              /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Error_ReportError(DEM_INTERNAL_APIID, DEM_E_PARAM_CONFIG);
  return FALSE;
}

/* ****************************************************************************
 % Dem_Debounce_InvalidVoid
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Debounce_InvalidVoid(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)  DebounceInfoPtr                                                                /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_8.13_Internal */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DebounceInfoPtr)                                                                              /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Error_ReportError(DEM_INTERNAL_APIID, DEM_E_PARAM_CONFIG);
}


/* ****************************************************************************
 % Dem_Debounce_InvalidUpdateMax
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Debounce_InvalidUpdateMax(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr                                                           /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_8.13_Internal */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DebounceInfoPtr)                                                                              /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Error_ReportError(DEM_INTERNAL_APIID, DEM_E_PARAM_CONFIG);
}

/* ****************************************************************************
 % Dem_Debounce_InvalidGetDebouncingState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL FUNC(Dem_DebouncingStateType, DEM_CODE)
Dem_Debounce_InvalidGetDebouncingState(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr                                                           /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_8.13_Internal */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DebounceInfoPtr)                                                                              /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Error_ReportError(DEM_INTERNAL_APIID, DEM_E_PARAM_CONFIG);
  return 0;
}

/* ****************************************************************************
 % Dem_Debounce_InvalidGetDebouncingResult
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_Debounce_InvalidGetDebouncingResult(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC) SatelliteData
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DebounceInfoPtr)                                                                              /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Error_ReportError(DEM_INTERNAL_APIID, DEM_E_PARAM_CONFIG);
  return SatelliteData;
}

/* ****************************************************************************
 % Dem_Debounce_InvalidGetFDC
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_Debounce_InvalidGetFDC(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr,                                                           /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONSTP2VAR(sint8, AUTOMATIC, DEM_APPL_DATA) FaultDetectionCounter                                                              /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_8.13_Internal */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DebounceInfoPtr)                                                                              /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(FaultDetectionCounter)                                                                        /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Error_ReportError(DEM_INTERNAL_APIID, DEM_E_PARAM_CONFIG);
  return E_NOT_OK;
}

/* ****************************************************************************
 * Dem_Debounce_InvalidRestoreDebounceValue
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_Debounce_InvalidRestoreDebounceValue(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr,                                                           /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONST(Dem_SatelliteData_DataType, AUTOMATIC) SatelliteData,                                                                    /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_8.13_Internal */
  CONST(sint16, AUTOMATIC) Value,                                                                                                /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONST(boolean, AUTOMATIC) ExpectedThreshold                                                                                    /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DebounceInfoPtr)                                                                              /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(SatelliteData)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(Value)                                                                                        /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(ExpectedThreshold)                                                                            /* PRQA S 3112 */ /* MD_DEM_14.2 */

  Dem_Error_ReportError(DEM_INTERNAL_APIID, DEM_E_PARAM_CONFIG);

  return SatelliteData;
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_DEBOUNCEIF_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_DebounceIF_Implementation.h
 *********************************************************************************************************************/
