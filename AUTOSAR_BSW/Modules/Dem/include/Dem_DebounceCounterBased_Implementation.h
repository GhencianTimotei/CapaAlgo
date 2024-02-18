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
 *  \addtogroup Dem_DebounceCounterBased
 *  \{
 *
 *  \file       Dem_DebounceCounterBased_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Implementation of DebounceCounterBased subcomponent
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_DEBOUNCECOUNTERBASED_IMPLEMENTATION_H)
#define DEM_DEBOUNCECOUNTERBASED_IMPLEMENTATION_H

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
#include "Dem_DebounceCounterBased_Interface.h"

/* Includes to access public functions belonging to other (top level)/ (logical)/- units to be used by this Unit */
/* ------------------------------------------------------------------------- */
#include "Dem_Infrastructure_Interface.h"
#include "Dem_GlobalDiagnostics_Interface.h"
#include "Dem_Core_Interface.h"
#include "Dem_SatelliteData_Interface.h"
#include "Dem_DebounceBase_Interface.h"
#include "Dem_DebouncingState_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*! Filename declaration */
#define DEM_DEBOUNCECOUNTERBASED_IMPLEMENTATION_FILENAME "Dem_DebounceCounterBased_Implementation.h"

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

DEM_LOCAL CONST(Dem_DebounceFunctionTableType, DEM_CONST) Dem_DebounceCounterBased_FunctionTable =                               /* PRQA S 3218 */ /* MD_DEM_8.7 */
{
   Dem_DebounceCounterBased_Calculate,
   Dem_DebounceCounterBased_Freeze,
   Dem_DebounceCounterBased_Reset,
   Dem_DebounceCounterBased_GetDebouncingState,
   Dem_DebounceCounterBasedSat_UpdateDebounceValueMax,
   Dem_DebounceCounterBasedSat_ResetDebounceValueMax,
   Dem_DebounceCounterBased_GetFaultDetectionCounter,
   Dem_DebounceCounterBased_GetMaxFaultDetectionCounter,
   Dem_DebounceCounterBased_GetDebouncingResult,
   Dem_DebounceCounterBased_RestoreDebounceValue
};

#define DEM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

 /* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DEFINITIONS
 *********************************************************************************************************************/
/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE PROPERTIES DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
 /*!
 * \defgroup Dem_DebounceCounterBased_PrivateProperties Private Properties
 * \{
 */


/* ****************************************************************************
 * Dem_DebounceCounterBased_isPreConfirmedTargetEnabled
 *****************************************************************************/
/*!
 * \brief         Returns true if preconfirmed storage target is enabled.
 * \details       -
 *
 * \return        TRUE
 *                Support for 'preconfirmed storage target'
 * \return        FALSE
 *                No support for 'preconfirmed storage target'
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DebounceCounterBased_isPreConfirmedTargetEnabled(
  void
);


/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE PROPERTIES DEFINITIONS
 *********************************************************************************************************************/


 /* ****************************************************************************
 % Dem_DebounceCounterBased_isPreConfirmedTargetEnabled()
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DebounceCounterBased_isPreConfirmedTargetEnabled(void)
{
  return (boolean)(DEM_FEATURE_NEED_EVENT_PRECONFIRMED == STD_ON);
}
/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ********************************************************************************************************************
 *  SUBCOMPONENT API PRIVATE FUNCTION DECALRATIONS
 *********************************************************************************************************************/

/*!
 * \defgroup Dem_DebounceCounterBased_Private Private Methods
 * \{
 */


/* ****************************************************************************
 * Dem_DebounceCounterBased_CheckDebounceInfoPtr
 *****************************************************************************/
/*!
 * \brief         Checks whether the DebounceInfoPtr is initialized for counter 
 *                based debouncing.
 *
 * \details       Checks whether the DebounceInfoPtr is initialized for counter 
 *                based debouncing.
 *
 * \param[in]     DebounceInfoPtr
 *                Pointer to debounce base object.
 *
 * \return        TRUE: DebounceInfoPtr is initialized for counter based debouncing.
 *                FALSE: Otherwise.
 *
 * \pre           -
 * 
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DebounceCounterBased_CheckDebounceInfoPtr(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
  );


/* ****************************************************************************
 * Dem_DebounceCounterBased_Base2CounterBased
 *****************************************************************************/
/*!
 * \brief         Derives the counter based object from the given base object.
 *
 * \details       Derives the counter based debounce object from the given base
 *                debounceobject.
 *
 * \param[in]     DebounceInfoPtr
 *                Pointer to debounce base object.
 *
 * \return        Pointer to counter based debounce object.
 *
 * \pre           DebounceInfoPtr was initialized for counter based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DebounceCounterBased_InfoPtrType, DEM_CODE)
Dem_DebounceCounterBased_Base2CounterBased(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)  DebounceInfoPtr
  );


/* ****************************************************************************
 * Dem_DebounceCounterBased_ConstBase2CounterBased
 *****************************************************************************/
/*!
 * \brief         Derives the counter based object from the given base object.
 *
 * \details       Derives the counter based debounce object from the given base
 *                debounceobject.
 *
 * \param[in]     DebounceInfoPtr
 *                Pointer to base debounce object.
 *
 * \return        Pointer to counter based debounce object.
 *
 * \pre           DebounceInfoPtr was initialized for counter based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DebounceCounterBased_ConstInfoPtrType, DEM_CODE)
Dem_DebounceCounterBased_ConstBase2CounterBased(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
  );


/* ****************************************************************************
 * Dem_DebounceCounterBased_GetNewDebounceValue
 *****************************************************************************/
/*!
 * \brief         Gets the new debounce value.
 *
 * \details       Gets the new debounce value.
 *
 * \param[in]     DebounceInfoPtr
 *                Pointer to base debounce object.
 *
 * \return        The new debounce value.
 *
 * \pre           DebounceInfoPtr was initialized for counter based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(sint16, DEM_CODE)
Dem_DebounceCounterBased_GetNewDebounceValue(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
  );


/* ****************************************************************************
 * Dem_DebounceCounterBased_SetNewDebounceValue
 *****************************************************************************/
/*!
 * \brief         Sets the new debounce value to the given value.
 *
 * \details       Sets the new debounce value to the given value.
 *
 * \param[in,out] DebounceInfoPtr
 *                Pointer to base debounce object.
 *
 * \param[in]     DebounceValue
 *                Debounce value to be set
 *
 * \pre           DebounceInfoPtr was initialized for counter based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DebounceCounterBased_SetNewDebounceValue(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)  DebounceInfoPtr,
  CONST(sint16, AUTOMATIC)  DebounceValue
  );


/* ****************************************************************************
 * Dem_DebounceCounterBased_CalculatePrepassed
 *****************************************************************************/
/*!
 * \brief         Process the counter based debouncing of an event which has
 *                been reported as prepassed.
 *
 * \details       Process the counter based debouncing of an event which has
 *                been reported as prepassed.
 *
 * \param[in,out] DebounceInfoData
 *                The counter based specific debouncing information.
 *
 * \pre           The event must use counter based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different events
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DebounceCounterBased_CalculatePrepassed(
  CONST(Dem_DebounceCounterBased_InfoPtrType, AUTOMATIC)  DebounceInfoData
  );


/* ****************************************************************************
 * Dem_DebounceCounterBased_CalculatePassed
 *****************************************************************************/
/*!
 * \brief         Process the counter based debouncing of an event which has
 *                been reported as passed.
 *
 * \details       Process the counter based debouncing of an event which has
 *                been reported as passed.
 *
 * \param[in,out] DebounceInfoData
 *                The counter based specific debouncing information.
 *
 * \pre           The event must use counter based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different events
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DebounceCounterBased_CalculatePassed(
  CONST(Dem_DebounceCounterBased_InfoPtrType, AUTOMATIC)  DebounceInfoData
  );


/* ****************************************************************************
 * Dem_DebounceCounterBased_CalculatePrefailed
 *****************************************************************************/
/*!
 * \brief         Process the counter based debouncing of an event which has
 *                been reported as prefailed.
 *
 * \details       Process the counter based debouncing of an event which has
 *                been reported as prefailed.
 *
 * \param[in,out] DebounceInfoData
 *                The counter based specific debouncing information.
 *
 * \pre           The event must use counter based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different events
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DebounceCounterBased_CalculatePrefailed(
  CONST(Dem_DebounceCounterBased_InfoPtrType, AUTOMATIC)  DebounceInfoData
  );


/* ****************************************************************************
 * Dem_DebounceCounterBased_CalculateFailed
 *****************************************************************************/
/*!
 * \brief         Process the counter based debouncing of an event which has
 *                been reported as failed.
 *
 * \details       Process the counter based debouncing of an event which has
 *                been reported as failed.
 *
 * \param[in,out] DebounceInfoData
 *                The counter based specific debouncing information.
 *
 * \pre           The event must use counter based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different events
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DebounceCounterBased_CalculateFailed(
  CONST(Dem_DebounceCounterBased_InfoPtrType, AUTOMATIC)  DebounceInfoData
  );

/* ********************************************************************************************************************
 *  SUBCOMPONENT API PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/

/* ****************************************************************************
 % Dem_DebounceCounterBased_CheckDebounceInfoPtr
 *****************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 *
 *
 *
  *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DebounceCounterBased_CheckDebounceInfoPtr(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr                                                           
  )
{
  boolean lDebounceInfoPtrValid;

  if ( (Dem_Error_isDevRunTimeChecksEnabled() == TRUE)
    && (DebounceInfoPtr->FunctionTable != &Dem_DebounceCounterBased_FunctionTable))
  {
    Dem_Error_RunTimeCheckFailed(DEM_DEBOUNCECOUNTERBASED_IMPLEMENTATION_FILENAME, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
    lDebounceInfoPtrValid = FALSE;
  }
  else
  { 
    lDebounceInfoPtrValid = TRUE;
  }

  return lDebounceInfoPtrValid;
}

/* ****************************************************************************
 % Dem_DebounceCounterBased_Base2CounterBased
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DebounceCounterBased_InfoPtrType, DEM_CODE)
Dem_DebounceCounterBased_Base2CounterBased(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)  DebounceInfoPtr
  )
{
  return (Dem_DebounceCounterBased_InfoPtrType)DebounceInfoPtr;                                                                  /* PRQA S 0310 */ /* MD_DEM_11.4_inh */
}

/* ****************************************************************************
 % Dem_DebounceCounterBased_ConstBase2CounterBased
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DebounceCounterBased_ConstInfoPtrType, DEM_CODE)
Dem_DebounceCounterBased_ConstBase2CounterBased(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
  )
{
  return (Dem_DebounceCounterBased_ConstInfoPtrType)DebounceInfoPtr;                                                             /* PRQA S 0310 */ /* MD_DEM_11.4_inh */
}

/* ****************************************************************************
 % Dem_DebounceCounterBased_GetNewDebounceValue
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(sint16, DEM_CODE)
Dem_DebounceCounterBased_GetNewDebounceValue(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
  )
{
  sint16 lNewDebounceValue;

  Dem_Internal_AssertContinue(DebounceInfoPtr->FunctionTable == &Dem_DebounceCounterBased_FunctionTable, DEM_E_INCONSISTENT_STATE)
  lNewDebounceValue = Dem_DebounceCounterBased_ConstBase2CounterBased(DebounceInfoPtr)->NewDebounceValue;                        /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  return lNewDebounceValue;
}

/* ****************************************************************************
 % Dem_DebounceCounterBased_SetNewDebounceValue
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DebounceCounterBased_SetNewDebounceValue(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)  DebounceInfoPtr,
  CONST(sint16, AUTOMATIC)  DebounceValue
  )
{
  if (Dem_DebounceCounterBased_CheckDebounceInfoPtr((Dem_DebounceBase_ConstInfoPtrType)DebounceInfoPtr) == TRUE)                 /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  { 
    Dem_DebounceCounterBased_InfoPtrType lDebounceCounterBasedInfoPtr;
    lDebounceCounterBasedInfoPtr = Dem_DebounceCounterBased_Base2CounterBased(DebounceInfoPtr);                                  /* SBSW_DEM_CALL_DEBOUNCECOUNTERBASED_INFOPTR_INIT */
    lDebounceCounterBasedInfoPtr->NewDebounceValue = DebounceValue;                                                              /* SBSW_DEM_DEBOUNCECOUNTERBASED_INFOPTR_WRITE_STACK */      
  }
  else
  {
    /* MISRA */
  }
}

/* ****************************************************************************
 % Dem_DebounceCounterBased_CalculatePrepassed
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DebounceCounterBased_CalculatePrepassed(
  CONST(Dem_DebounceCounterBased_InfoPtrType, AUTOMATIC)  DebounceInfoData
  )
{
  Dem_EventIdType lEventId;
  sint16 lJumpToValue;
  boolean lEnableConditionsSatisfied;

  lEventId = Dem_DebounceBase_GetEventId(&(DebounceInfoData->Base));                                                             /* SBSW_DEM_DEBOUNCECOUNTERBASED_INFO_BASE_PTR */
  lJumpToValue = Dem_Cfg_EventJumpDownValue(lEventId);
  lEnableConditionsSatisfied = Dem_EnableCondition_TestEventEnableConditionsFulfilled(lEventId);

  if (DebounceInfoData->OldDebounceValue > lJumpToValue)
  {
    if (Dem_Cfg_EventSupportJumpDown(lEventId) == TRUE)
    {
      /* JumpDown */
      DebounceInfoData->NewDebounceValue = lJumpToValue;                                                                         /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    }
  }

  if (DebounceInfoData->NewDebounceValue <=
    (Dem_Cfg_EventPassedTarget(lEventId) - Dem_Cfg_EventPrepassedStep(lEventId))) /* No overflow possible */
  {
    DebounceInfoData->NewDebounceValue = Dem_Cfg_EventPassedTarget(lEventId);                                                    /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    if (lEnableConditionsSatisfied == TRUE)
    {
      /* qualified result, set result and final de-bounce counter */
      Dem_DebounceBase_SetMonitorTrigger(&(DebounceInfoData->Base), DEM_EVENT_STATUS_PASSED);                                    /* SBSW_DEM_DEBOUNCECOUNTERBASED_INFO_BASE_PTR */
    }
  }
  else
  {
    DebounceInfoData->NewDebounceValue = (sint16)                                                                                /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      (DebounceInfoData->NewDebounceValue + Dem_Cfg_EventPrepassedStep(lEventId)); /* No overflow possible */
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_DebounceCounterBased_CalculatePassed
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DebounceCounterBased_CalculatePassed(
  CONST(Dem_DebounceCounterBased_InfoPtrType, AUTOMATIC)  DebounceInfoData
  )
{
  Dem_EventIdType lEventId;
  boolean lEnableConditionsSatisfied;

  lEventId = Dem_DebounceBase_GetEventId(&(DebounceInfoData->Base));                                                             /* SBSW_DEM_DEBOUNCECOUNTERBASED_INFO_BASE_PTR */
  lEnableConditionsSatisfied = Dem_EnableCondition_TestEventEnableConditionsFulfilled(lEventId);

  /* Qualified result - directly load threshold de-bounce counter from configuration */
  /* This also reduces exceeded counter values to match the passed threshold exactly (latch at bottom) */
  DebounceInfoData->NewDebounceValue = Dem_Cfg_EventPassedTarget(lEventId);                                                      /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  if (lEnableConditionsSatisfied == FALSE)
  {
    Dem_DebounceBase_SetMonitorTrigger(&(DebounceInfoData->Base), DEM_EVENT_STATUS_PREPASSED);                                   /* SBSW_DEM_DEBOUNCECOUNTERBASED_INFO_BASE_PTR */
  }
}

/* ****************************************************************************
 % Dem_DebounceCounterBased_CalculatePrefailed
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DebounceCounterBased_CalculatePrefailed(
  CONST(Dem_DebounceCounterBased_InfoPtrType, AUTOMATIC)  DebounceInfoData
  )
{
  Dem_EventIdType lEventId;
  sint16 lJumpToValue;
  boolean lEnableConditionsSatisfied;

  lEventId = Dem_DebounceBase_GetEventId(&(DebounceInfoData->Base));                                                             /* SBSW_DEM_DEBOUNCECOUNTERBASED_INFO_BASE_PTR */
  lJumpToValue = Dem_Cfg_EventJumpUpValue(lEventId);
  lEnableConditionsSatisfied = Dem_EnableCondition_TestEventEnableConditionsFulfilled(lEventId);

  if (DebounceInfoData->OldDebounceValue < lJumpToValue)
  {
    if (Dem_Cfg_EventSupportJumpUp(lEventId) == TRUE)
    {
      /* JumpUp */
      DebounceInfoData->NewDebounceValue = lJumpToValue;                                                                         /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    }
  }

  if (DebounceInfoData->NewDebounceValue >=
    (Dem_Cfg_EventFailedTarget(lEventId) - Dem_Cfg_EventPrefailedStep(lEventId))) /* No overflow possible */
  {
    /* qualified result, set result and final de-bounce counter */
    DebounceInfoData->NewDebounceValue = Dem_Cfg_EventFailedTarget(lEventId);                                                    /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    if (lEnableConditionsSatisfied == TRUE)
    {
      Dem_DebounceBase_SetMonitorTrigger(&(DebounceInfoData->Base), DEM_EVENT_STATUS_FAILED);                                    /* SBSW_DEM_DEBOUNCECOUNTERBASED_INFO_BASE_PTR */
    }
  }
  else
  {
    DebounceInfoData->NewDebounceValue = (sint16)                                                                                /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      (DebounceInfoData->NewDebounceValue + Dem_Cfg_EventPrefailedStep(lEventId));  /* No overflow possible */
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_DebounceCounterBased_CalculateFailed
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DebounceCounterBased_CalculateFailed(
  CONST(Dem_DebounceCounterBased_InfoPtrType, AUTOMATIC)  DebounceInfoData
  )
{
  Dem_EventIdType lEventId;
  boolean lEnableConditionsSatisfied;

  lEventId = Dem_DebounceBase_GetEventId(&(DebounceInfoData->Base));                                                             /* SBSW_DEM_DEBOUNCECOUNTERBASED_INFO_BASE_PTR */
  lEnableConditionsSatisfied = Dem_EnableCondition_TestEventEnableConditionsFulfilled(lEventId);

  /* Qualified result - directly load threshold de-bounce counter from configuration */
  /* This also reduces counter values to match the failed threshold exactly (latch at ceiling) */
  DebounceInfoData->NewDebounceValue = Dem_Cfg_EventFailedTarget(lEventId);                                                      /* SBSW_DEM_POINTER_WRITE_ARGUMENT */

  if (lEnableConditionsSatisfied == FALSE)
  {
    Dem_DebounceBase_SetMonitorTrigger(&(DebounceInfoData->Base), DEM_EVENT_STATUS_PREFAILED);                                   /* SBSW_DEM_DEBOUNCECOUNTERBASED_INFO_BASE_PTR */
  }
}

/*!
 * \}
 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION IMPLEMENTATION
 *********************************************************************************************************************/
/*!
 * \addtogroup Dem_DebounceCounterBased_Public
 * \{
 */

/* ****************************************************************************
 % Dem_DebounceCounterBased_InfoInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_DebounceBase_InfoPtrType, DEM_CODE)
Dem_DebounceCounterBased_InfoInit(
  CONSTP2VAR(Dem_DebounceCounterBased_InfoType, AUTOMATIC, AUTOMATIC) DebounceInfoData,
  CONST(Dem_EventIdType, AUTOMATIC) EventId,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteData
  )
{
  Dem_DebounceBase_InfoPtrType lReturnValue;
  lReturnValue = Dem_DebounceBase_InfoInitDefault(&(DebounceInfoData->Base),                                                     /* SBSW_DEM_CALL_DEBOUNCEINFO_INIT */
                                                  &Dem_DebounceCounterBased_FunctionTable,                                       /* SBSW_DEM_POINTER_FORWARD_GLOBAL */
                                                  EventId);  
  DebounceInfoData->OldDebounceValue = (sint16) Dem_SatelliteData_GetDebounceData(SatelliteData);                                /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  DebounceInfoData->NewDebounceValue = (sint16) Dem_SatelliteData_GetDebounceData(SatelliteData);                                /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_DebounceCounterBased_Calculate
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
 *
 *
 *
 */
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_DebounceCounterBased_Calculate(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)  DebounceInfoPtr
  )
{
  Dem_EventIdType lEventId;
  Dem_DebounceCounterBased_InfoPtrType lDebounceInfo;
  boolean lEnableConditionsSatisfied;
  boolean lReturnValue;

  if (Dem_DebounceCounterBased_CheckDebounceInfoPtr((Dem_DebounceBase_ConstInfoPtrType)DebounceInfoPtr) == TRUE)                 /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  {
    lDebounceInfo = Dem_DebounceCounterBased_Base2CounterBased(DebounceInfoPtr);                                                 /* SBSW_DEM_CALL_DEBOUNCECOUNTERBASED_INFOPTR_INIT */
    lEventId = Dem_DebounceBase_GetEventId(DebounceInfoPtr);                                                                     /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    lEnableConditionsSatisfied = Dem_EnableCondition_TestEventEnableConditionsFulfilled(lEventId);

    /* Monitor status for this event not supported */
    if (Dem_DebounceBase_GetMonitorTrigger(DebounceInfoPtr) == DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED)                           /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    {
      Dem_Error_ReportError(DEM_INTERNAL_APIID, DEM_E_PARAM_DATA);
      lReturnValue = FALSE;
    }
    else
    {
      if ((lEnableConditionsSatisfied == TRUE)
        || (Dem_Cfg_EventDebounceContinuous(lEventId) == TRUE))                                                                  
      {
        switch (Dem_DebounceBase_GetMonitorTrigger(DebounceInfoPtr))                                                             /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
        {
        case DEM_EVENT_STATUS_PREPASSED:
          Dem_DebounceCounterBased_CalculatePrepassed(lDebounceInfo);                                                            /* SBSW_DEM_DEBOUNCECOUNTERBASED_INFOPTR_FORWARD_ARGUMENT */
          break;

        case DEM_EVENT_STATUS_PASSED:
          Dem_DebounceCounterBased_CalculatePassed(lDebounceInfo);                                                               /* SBSW_DEM_DEBOUNCECOUNTERBASED_INFOPTR_FORWARD_ARGUMENT */
          break;

        case DEM_EVENT_STATUS_PREFAILED:
          Dem_DebounceCounterBased_CalculatePrefailed(lDebounceInfo);                                                            /* SBSW_DEM_DEBOUNCECOUNTERBASED_INFOPTR_FORWARD_ARGUMENT */
          break;

        case DEM_EVENT_STATUS_FAILED:
          Dem_DebounceCounterBased_CalculateFailed(lDebounceInfo);                                                               /* SBSW_DEM_DEBOUNCECOUNTERBASED_INFOPTR_FORWARD_ARGUMENT */
          break;

        default:                                                                                                                 /* PRQA S 2016 */ /* MD_MSR_EmptyClause */
          /* Satisfy Misra */
          break;
        }

        if ((Dem_DTC_RetryStorage(lEventId) == TRUE)
          && (Dem_DebounceBase_GetMonitorTrigger(DebounceInfoPtr) == DEM_EVENT_STATUS_FAILED)                                     /* PRQA S 3415 */ /* MD_DEM_13.5_cf */ /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
          && (lEnableConditionsSatisfied == TRUE))
        {
          Dem_DebounceBase_SetDebouncingChanged(DebounceInfoPtr);                                                                /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
        }
        else
        {
          if (lDebounceInfo->OldDebounceValue != lDebounceInfo->NewDebounceValue)
          {
            Dem_DebounceBase_SetDebouncingChanged(DebounceInfoPtr);                                                              /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
          }
        }

        if (Dem_DebounceCounterBased_isPreConfirmedTargetEnabled() == TRUE)
        {
          if ( (lDebounceInfo->NewDebounceValue >= (sint16)Dem_Cfg_EventPreconfirmedTarget(lEventId))
            && (lDebounceInfo->OldDebounceValue < (sint16)Dem_Cfg_EventPreconfirmedTarget(lEventId)) )
          {
            Dem_DebounceBase_SetFdcThresholdExceeded(DebounceInfoPtr);                                                         /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
            Dem_DebounceBase_SetRequestFdcProcessing(DebounceInfoPtr);                                                         /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
          }
          if (lDebounceInfo->NewDebounceValue > Dem_DebounceBaseSat_GetDebounceValueMax(lEventId))
          {
            Dem_DebounceBase_SetMaximumFdcExceeded(DebounceInfoPtr);                                                           /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
            Dem_DebounceBase_SetRequestFdcProcessing(DebounceInfoPtr);                                                         /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
          }
        }
        else
        {
          if (lEnableConditionsSatisfied == TRUE)
          {
            if ((lDebounceInfo->NewDebounceValue >= (sint16)Dem_Cfg_EventStorageTarget(lEventId))
            && (lDebounceInfo->OldDebounceValue < (sint16)Dem_Cfg_EventStorageTarget(lEventId)))                                 
            {
              Dem_DebounceBase_SetFdcThresholdExceeded(DebounceInfoPtr);                                                         /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
              Dem_DebounceBase_SetRequestFdcProcessing(DebounceInfoPtr);                                                         /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
            }
            /* Possible update of SLC based on update of TOC */
            if (lDebounceInfo->NewDebounceValue > Dem_DebounceBaseSat_GetDebounceValueMax(lEventId))
            {
              Dem_DebounceBase_SetMaximumFdcExceeded(DebounceInfoPtr);                                                           /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
              Dem_DebounceBase_SetRequestFdcProcessing(DebounceInfoPtr);                                                         /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
            }
          }
        }
        lReturnValue = TRUE;
      } /* (lEnableConditionsSatisfied == TRUE) || (Dem_Cfg_EventDebounceContinuous(lEventId) == TRUE) */
      else
      {
        lReturnValue = FALSE;
      }
    }
  }
  else
  {
    lReturnValue = FALSE;
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_DebounceCounterBased_Freeze
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DebounceCounterBased_Freeze(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)  DebounceInfoPtr                                                                /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_8.13_Internal */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DebounceInfoPtr)                                                                              /* PRQA S 3112 */ /* MD_DEM_14.2 */
  /* No action necessary */
}

/* ****************************************************************************
 % Dem_DebounceCounterBased_Reset
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DebounceCounterBased_Reset(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)  DebounceInfoPtr                                                                /* PRQA S 3673 */ /* MD_DEM_8.13_Internal */
  )
{
  Dem_DebounceCounterBased_SetNewDebounceValue(DebounceInfoPtr, (sint16) DEM_DEBOUNCE_COUNTERBASED_INIT_VALUE);                  /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
}

/* ****************************************************************************
 % Dem_DebounceCounterBased_GetDebouncingState
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
DEM_LOCAL FUNC(Dem_DebouncingStateType, DEM_CODE)
Dem_DebounceCounterBased_GetDebouncingState(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr                                                           /* PRQA S 3673 */ /* MD_DEM_8.13_Internal */
  )
{
  Dem_EventIdType lEventId;
  sint16 lNewDebounceValue;
  Dem_DebouncingStateType lDebouncingState;

  lEventId = Dem_DebounceBase_GetEventId(DebounceInfoPtr);                                                                       /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  lNewDebounceValue = Dem_DebounceCounterBased_GetNewDebounceValue(DebounceInfoPtr);                                             /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  lDebouncingState = Dem_DebouncingState_GetInitValue();

  if (lNewDebounceValue == Dem_Cfg_EventFailedTarget(lEventId))
  {
    lDebouncingState = Dem_DebouncingState_SetFinallyDefective(lDebouncingState);
    lDebouncingState = Dem_DebouncingState_SetTestComplete(lDebouncingState);
    if ( (Dem_EnableCondition_TestEventEnableConditionsFulfilled(lEventId) == TRUE)
      && (Dem_StorageCondition_TestEventStorageConditionsFulfilled(lEventId) == TRUE) )                                          
    {
      lDebouncingState = Dem_DebouncingState_SetDtrUpdate(lDebouncingState);
    }
  }
  else if (lNewDebounceValue == Dem_Cfg_EventPassedTarget(lEventId))
  {
    lDebouncingState = Dem_DebouncingState_SetTestComplete(lDebouncingState);
    if ((Dem_EnableCondition_TestEventEnableConditionsFulfilled(lEventId) == TRUE)
      && (Dem_StorageCondition_TestEventStorageConditionsFulfilled(lEventId) == TRUE))                                           
    {
      lDebouncingState = Dem_DebouncingState_SetDtrUpdate(lDebouncingState);
    }
  }
  else if (lNewDebounceValue > 0)
  {
    lDebouncingState = Dem_DebouncingState_SetTemporarilyDefective(lDebouncingState);
  }
  else if (lNewDebounceValue < 0)
  { 
    lDebouncingState = Dem_DebouncingState_SetTemporarilyHealed(lDebouncingState);
  }
  else
  {
    /* de-bouncing state 0 */
  }

  return lDebouncingState;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_DebounceCounterBasedSat_UpdateDebounceValueMax
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DebounceCounterBasedSat_UpdateDebounceValueMax(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
  )
{
  Dem_EventIdType lEventId;
  lEventId = Dem_DebounceBase_GetEventId(DebounceInfoPtr);                                                                       /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  Dem_DebounceBaseSat_SetDebounceValueMax(lEventId, Dem_DebounceCounterBased_GetNewDebounceValue(DebounceInfoPtr));              /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
}

/* ****************************************************************************
 % Dem_DebounceCounterBasedSat_ResetDebounceValueMax
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DebounceCounterBasedSat_ResetDebounceValueMax(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
  )
{
  Dem_EventIdType lEventId;
  lEventId = Dem_DebounceBase_GetEventId(DebounceInfoPtr);                                                                       /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  Dem_DebounceBaseSat_SetDebounceValueMax(lEventId, 0);
}

/* ****************************************************************************
 % Dem_DebounceCounterBased_GetFaultDetectionCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_DebounceCounterBased_GetFaultDetectionCounter(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr,
  P2VAR(sint8, AUTOMATIC, DEM_APPL_DATA) FaultDetectionCounter
  )
{
  Dem_EventIdType lEventId;

  lEventId = Dem_DebounceBase_GetEventId(DebounceInfoPtr);                                                                       /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */

  *FaultDetectionCounter = Dem_DebounceCounterBased_CalculateFaultDetectionCounter(                                              /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
                             lEventId,
                             Dem_DebounceCounterBased_GetNewDebounceValue(DebounceInfoPtr));                                     /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */

  return E_OK;
}

/* *****************************************************************************
 % Dem_DebounceCounterBased_GetMaxFaultDetectionCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_DebounceCounterBased_GetMaxFaultDetectionCounter(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr,
  P2VAR(sint8, AUTOMATIC, DEM_APPL_DATA) FaultDetectionCounter
  )
{
  Dem_EventIdType lEventId;
  lEventId = Dem_DebounceBase_GetEventId(DebounceInfoPtr);                                                                       /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  *FaultDetectionCounter = Dem_DebounceCounterBased_CalculateFaultDetectionCounter(                                              /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
                             lEventId,
                             Dem_DebounceBaseSat_GetDebounceValueMax(lEventId));
  return E_OK;
}

/* ****************************************************************************
 % Dem_DebounceCounterBased_GetDebouncingResult
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_DebounceCounterBased_GetDebouncingResult(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteData
  )
{
  Dem_SatelliteData_DataType lReturnValue;                                                                                       /* PRQA S 0759 */ /* MD_MSR_Union */
  lReturnValue = Dem_SatelliteData_SetDebounceData(
                    SatelliteData,
                    (Dem_Debounce_DataType) Dem_DebounceCounterBased_GetNewDebounceValue(DebounceInfoPtr));                      /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_DebounceCounterBased_RestoreDebounceValue()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_DebounceCounterBased_RestoreDebounceValue(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC) SatelliteData,
  CONST(sint16, AUTOMATIC) Value,
  CONST(boolean, AUTOMATIC) ExpectedThreshold
  )
{
  Dem_EventIdType lEventId;
  Dem_SatelliteData_DataType lReturnValue;                                                                                       /* PRQA S 0759 */ /* MD_MSR_Union */

  lEventId = Dem_DebounceBase_GetEventId(DebounceInfoPtr);                                                                       /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */

  if ( /* Unqualified de-bounce state is ok */
       ( (Dem_Cfg_EventFailedTarget(lEventId) > Value) && (Dem_Cfg_EventPassedTarget(lEventId) < Value) )                        
       /* If de-bouncing counter has reached qualified threshold, the event status must match */
    || ( (Dem_Cfg_EventFailedTarget(lEventId) == Value) && (ExpectedThreshold == TRUE))                                          
    || ( (Dem_Cfg_EventPassedTarget(lEventId) == Value) && (ExpectedThreshold == FALSE)) )                                       
  {
    lReturnValue = Dem_SatelliteData_SetDebounceData(
                      SatelliteData,
                      (Dem_Debounce_DataType) Value);
  }
  else
  {
    lReturnValue = SatelliteData;
  }

  return lReturnValue;
}

/* ****************************************************************************
 % Dem_DebounceCounterBased_CalculateFaultDetectionCounter
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
DEM_LOCAL FUNC(sint8, DEM_CODE)
Dem_DebounceCounterBased_CalculateFaultDetectionCounter(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(sint16, AUTOMATIC)  DebounceValue
  )
{
  sint8 lReturnedFdc;

  if (DebounceValue == 0)
  {
    lReturnedFdc = 0;
  }
  else
  {
    sint16 lFailedTarget;
    sint16 lPassedTarget;

    lFailedTarget = Dem_Cfg_EventFailedTarget(EventId);
    lPassedTarget = Dem_Cfg_EventPassedTarget(EventId);

    if (DebounceValue >= lFailedTarget)
    {
      lReturnedFdc = 127;
    }
    else if (DebounceValue <= lPassedTarget)
    {
      lReturnedFdc = -128;
    }
    else
    { /* current debounce counter value is somewhere in range of passed threshold and failed threshold but not 0 */
      if (DebounceValue > 0)
      {
        lReturnedFdc = (sint8)(((sint32)DebounceValue * 127) / lFailedTarget);
        /* result has to be greater than 0 */
        if (lReturnedFdc == 0)
        {
          lReturnedFdc = 1;
        }
      }
      else
      {
        lReturnedFdc = (sint8)(((sint32)DebounceValue * -128)  / lPassedTarget);
        /* result has to be smaller than 0 */
        if (lReturnedFdc == 0)
        {
          lReturnedFdc = -1;
        }
      }
    }
  }

  return lReturnedFdc;
}                                                                                                                                /* PRQA S 6080 */ /* MD_MSR_STMIF */
/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_DEBOUNCECOUNTERBASED_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_DebounceCounterBased_Implementations.h
 *********************************************************************************************************************/
