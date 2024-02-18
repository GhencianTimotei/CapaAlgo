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
/*! \addtogroup Dem_OperationCycle
 *  \{
 *  \file       Dem_OperationCycle_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_OPERATIONCYCLE_IMPLEMENTATION_H)
#define DEM_OPERATIONCYCLE_IMPLEMENTATION_H

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
#include "Dem_OperationCycle_Interface.h"

/* Includes to access public functions belonging to other (top level)/ (logical)/- units to be used by this Unit */
/* ------------------------------------------------------------------------- */
#include "Dem_FaultMemory_Interface.h"
#include "Dem_Infrastructure_Interface.h"
#include "Dem_DiagnosticObserver_Interface.h"
#include "Dem_GlobalDiagnostics_Interface.h"
#include "Dem_Event_Interface.h"
#include "Dem_DTC_Interface.h"
#include "Dem_UDSStatus_Interface.h"
#include "Dem_Esm_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*! Filename declaration */
#define DEM_OPERATIONCYCLE_IMPLEMENTATION_FILENAME "Dem_OperationCycle_Implementation.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/
/*! Test if cycle change is pending for 'CycleId' */
#define Dem_OperationCycle_IsPendingCycle(CycleId)   ((Dem_OperationCycle_CycleFlag & ((uint16)1 << CycleId)) != 0u)


/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/

#define DEM_START_SEC_VAR_NOINIT_16BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Current operating cycle states */
DEM_LOCAL VAR(uint16, DEM_VAR_NOINIT)               Dem_OperationCycle_CurrentCycleState;
/*! Pending operating cycle states - protected by critical section DEM_EXCLUSIVE_AREA_1 (StateManager) */
DEM_LOCAL VAR(uint16, DEM_VAR_NOINIT)               Dem_OperationCycle_PendingCycleState;
/*! Operating cycle states update flags - protected by critical section DEM_EXCLUSIVE_AREA_1 (StateManager) */
DEM_LOCAL volatile VAR(uint16, DEM_VAR_NOINIT)      Dem_OperationCycle_CycleFlag;

#define DEM_STOP_SEC_VAR_NOINIT_16BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */



/* ********************************************************************************************************************
 *  SUBCOMPONENT PUBLIC PROPERTIES DEFINITIONS
 *********************************************************************************************************************/

#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \addtogroup Dem_OperationCycle_PublicProperties
 * \{
 */

/* ****************************************************************************
 % Dem_OperationCycle_GetCycleCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_OperationCycle_GetCycleCounter(
  CONST(uint8, AUTOMATIC)  CycleId
  )
{
  return Dem_Cfg_AdminData.CycleCounter[CycleId];
}

/* ****************************************************************************
 % Dem_OperationCycle_SetCycleCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_SetCycleCounter(
  CONST(uint8, AUTOMATIC)  CycleId,
  CONST(uint16, AUTOMATIC)  CycleCounter
  )
{
#if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (CycleId >= Dem_Cfg_GlobalCycleCount())
  {
    Dem_Error_RunTimeCheckFailed(DEM_OPERATIONCYCLE_IMPLEMENTATION_FILENAME, __LINE__);                                          /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
#endif
  {
    Dem_Cfg_AdminData.CycleCounter[CycleId] = CycleCounter;                                                                      /* SBSW_DEM_ARRAY_WRITE_ADMINDATA_CYCLECOUNTER */
  }
}

/* ****************************************************************************
 % Dem_OperationCycle_GetCurrentCycleStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_OperationCycle_GetCurrentCycleStatus(
  CONST(uint8, AUTOMATIC)  CycleId
  )
{
  return (uint8)(((Dem_OperationCycle_CurrentCycleState &  ((uint16)1 << CycleId)) != 0u)
    ? DEM_OPERATIONCYCLE_CYCLE_STARTED
    : DEM_OPERATIONCYCLE_CYCLE_STOPPED);
}


/* ****************************************************************************
 % Dem_OperationCycle_AddCycleCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_OperationCycle_AddCycleCount(
  CONST(uint16, AUTOMATIC)  CurrentCounter,
  CONST(uint8, AUTOMATIC)  DeltaValue
  )
{
  uint16 lTargetCycle;
  lTargetCycle = CurrentCounter + DeltaValue;

  if (lTargetCycle > DEM_OPERATIONCYCLE_CYCLECOUNT_MAX)
  { /* Overflow needs to wrap around at DEM_OPERATIONCYCLE_CYCLECOUNT_MAX */
    lTargetCycle = (uint16)(lTargetCycle - DEM_OPERATIONCYCLE_CYCLECOUNT_MAX);
  }

  return lTargetCycle;
}

/* ****************************************************************************
 % Dem_OperationCycle_CycleCountDistance
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL FUNC(uint16, DEM_CODE)
Dem_OperationCycle_CycleCountDistance(                                                                                           /* PRQA S 3219 */ /* MD_DEM_14.1_LIB */
  CONST(uint16, AUTOMATIC)  CurrentCounter,
  CONST(uint16, AUTOMATIC)  TargetCounter
  )
{
  uint16 lReturnValue;

  if (TargetCounter < CurrentCounter)
  {
    lReturnValue = (uint16)((DEM_OPERATIONCYCLE_CYCLECOUNT_MAX - CurrentCounter) + TargetCounter);
  }
  else
  {
    lReturnValue = (uint16)(TargetCounter - CurrentCounter);
  }

  return lReturnValue;
}



/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_OperationCycle_Private Private Methods
 * \{
 */

/* ****************************************************************************
* Dem_OperationCycle_ResetMemIndependentCycleCounterOnOpEnd
*****************************************************************************/
/*!
* \brief         Update memory independent cycle counter on operation
*                cycle end.
*
* \details       Calculate reset trigger of memory independent fault pending 
*                counter on operation cycle end and reset counter if fulfilled.
*
* \param[in]     EventId
*                Unique handle of the Event.
*
* \param[in]     CycleStatus
*                Cycle status changes
*
* \pre           Memory independent cycle counters are supported.
*
* \context       TASK|ISR2
* \synchronous   TRUE
* \reentrant     FALSE
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_ResetMemIndependentCycleCounterOnOpEnd(
  Dem_EventIdType EventId,
  uint8 CycleStatus
  );

#if (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
/* ****************************************************************************
 * Dem_OperationCycle_UpdateDTCCycleCounter
 *****************************************************************************/
/*!
 * \brief         Recalculates consecutive failed cycles and cycles tested since
 *                first failed data elements for all subevents.
 *
 * \details       Recalculates consecutive failed cycles and cycles tested since
 *                first failed data elements for all subevents.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *
 * \param[in]     CycleStatus
 *                Cycle status changes
 *
 * \pre           Event belongs to a Type 2 combined DTC group.
 *
 * \config        DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_UpdateDTCCycleCounter(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  CycleStatus
  );
#endif


/* ****************************************************************************
 * Dem_OperationCycle_GetPendingCycle
 *****************************************************************************/
/*!
 * \brief         Looks up a pending cycle state change
 *
 * \details       This function looks up a pending cycle state change.
 *                The value returned is only meaningful if the modification
 *                flag is also set for this cycle
 *                (see Dem_OperationCycle_CycleFlag).
 *
 * \param[in]     CycleId
 *                Unique handle of the Cycle.
 *
 * \return        DEM_OPERATIONCYCLE_CYCLE_STARTED
 *                Cycle state change to start is pending
 * \return        DEM_OPERATIONCYCLE_CYCLE_STOPPED
 *                Cycle state change to stop is pending
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_OperationCycle_GetPendingCycle(
  CONST(uint8, AUTOMATIC)  CycleId
  );


/* ****************************************************************************
 * Dem_OperationCycle_SetPendingCycle
 *****************************************************************************/
/*!
 * \brief         Stores a pending cycle state change
 *
 * \details       This function stores a pending cycle state change to be
 *                processed later on task context.
 *
 *                The queue can encode one STOP, one START or one STOP->START
 *                action. The modification flag (see
 *                Dem_OperationCycle_CycleFlag) is set always.
 *
 * \param[in]     CycleId
 *                Unique handle of the Cycle.
 * \param[in]     Status
 *                DEM_OPERATIONCYCLE_CYCLE_STARTED  To start a cycle
 *                DEM_OPERATIONCYCLE_CYCLE_STOPPED  To stop a cycle
 *
 * \pre           Must be called within critical section 'StateManager'
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_SetPendingCycle(
  CONST(uint8, AUTOMATIC)  CycleId,
  CONST(uint8, AUTOMATIC)  Status
  );

/* ****************************************************************************
 * Dem_OperationCycle_QualifyDcy
 *****************************************************************************/
/*!
 * \brief         Qualifies the OBD driving cycle
 *
 * \details       If feature OBD II or WWH-OBD is enabled, the environmental data,
 *                ConfirmedDTC bit and WIR bit become visible for external
 *                testers and the application when the driving cycle is qualified.
 *
 *                If the ConfirmedDTC bit qualifies of an event holding the OBD
 *                FreezeFrame, the FreezeFrame becomes visible as well.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_QualifyDcy(
  void
  );

/* ****************************************************************************
 * Dem_OperationCycle_ProcessCycles
 *****************************************************************************/
/*!
 * \brief         Process all queued operation cycles
 *
 * \details       The function processes cycle management for aging and
 *                operation cycle management (readiness bits etc)
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_ProcessCycles(
  void
  );


#if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON)
/* ****************************************************************************
 * Dem_OperationCycle_ProcessCycleUpdate_AllEvents
 *****************************************************************************/
/*!
 * \brief         Processes cycle update for all events
 *
 * \details       This function invokes functions to recalculate the aging cycle
 *                counter threshold for all events. Also invokes the
 *                functions for re-calculation of operation cycle counter
 *                latching.
 *
 * \param[in]     CycleId
 *                Unique Id of the cycle
 * \param[in]     CycleCounter
 *                Current cycle count
 *
 * \pre           Cycle counter has already been incremented for the cycle
 * \config        (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON)
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_ProcessCycleUpdate_AllEvents(
  CONST(uint8, AUTOMATIC)  CycleId,
  CONST(uint16, AUTOMATIC)  CycleCounter
  );
#endif


#if ((DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_OFF) \
     && ((DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF) || (DEM_FEATURE_NEED_CYCLE_COUNTERS == STD_ON)))
/* ****************************************************************************
 * Dem_OperationCycle_ProcessCycleUpdate_StoredEvents
 *****************************************************************************/
/*!
 * \brief         Processes cycle update for stored entries
 *
 * \details       This function recalculates the aging cycle
 *                counter threshold and operation cycle counter latching
 *                 for stored events.
 *
 * \param[in]     CycleId
 *                Unique Id of the cycle
 * \param[in]     CycleCounter
 *                Current cycle count
 *
 * \pre           Cycle counter has already been incremented for the cycle
 * \config        ((DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_OFF)
 *                  && ((DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF)
                        || (DEM_FEATURE_NEED_CYCLE_COUNTERS == STD_ON)))
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_ProcessCycleUpdate_StoredEvents(
  CONST(uint8, AUTOMATIC)  CycleId,
  CONST(uint16, AUTOMATIC)  CycleCounter
  );
#endif


#if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON)
/* ****************************************************************************
 * Dem_OperationCycle_RecalculateAgingThreshold_AllEvents
 *****************************************************************************/
/*!
 * \brief         Function recalculates the aging counter threshold
 *
 * \details       This function recalculates the aging counter threshold for
 *                all master events which are either confirmed or stored in
 *                memory based on the status. If the aging
 *                threshold for the event is reached, it is aged.
 *
 * \param[in]     CycleId
 *                Unique Id of the cycle
 * \param[in]     CycleCounter
 *                Current cycle count
 *
 * \pre           Cycle counter has already been incremented for the cycle
 * \config        DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_RecalculateAgingThreshold_AllEvents(
  CONST(uint8, AUTOMATIC)  CycleId,
  CONST(uint16, AUTOMATIC)  CycleCounter
  );
#endif


#if ((DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON) && (DEM_FEATURE_NEED_CYCLE_COUNTERS == STD_ON))
/* ****************************************************************************
 * Dem_OperationCycle_LatchCycleCounters
 *****************************************************************************/
/*!
 * \brief         Processes latching for cycle counters
 *
 * \details       This function iterates through all the memory
 *                entries and latches the operation cycle counters if required.
 *
 * \param[in]     CycleId
 *                Unique Id of the cycle
 * \param[in]     CycleCounter
 *                Current cycle count
 *
 * \pre           Cycle counter has already been incremented for the cycle
 * \config        (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON)
 *                 && (DEM_FEATURE_NEED_CYCLE_COUNTERS == STD_ON)
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_LatchCycleCounters(
  CONST(uint8, AUTOMATIC)  CycleId,
  CONST(uint16, AUTOMATIC)  CycleCounter
  );
#endif


/* ****************************************************************************
 * Dem_OperationCycle_UpdateTestEventAffected
 *****************************************************************************/
/*!
 * \brief         Checks if passed event is affected by cycle update
 *
 * \details       Checks if passed event is affected by cycle update
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *
 * \param[in]     CycleId
 *                Unique Id of the cycle
 *
 * \return        FALSE
 *                - CycleId does not match operation cycle of event.
 *                - Event is unavailable.
 *                - For combined events: event is not the master event.
 * \return        TRUE
 *                - Otherwise.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_OperationCycle_UpdateTestEventAffected(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  CycleId
  );


/* ****************************************************************************
 * Dem_OperationCycle_UpdateProcessEvent
 *****************************************************************************/
/*!
 * \brief         Processes the operation cycle update for the passed event
 *
 * \details       Updates status and stored entry for the passed event
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *
 * \param[in]     CycleStatus
 *                Cycle status changes
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_UpdateProcessEvent(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  CycleStatus
  );


/* ****************************************************************************
 * Dem_OperationCycle_CycleUpdateReadiness
 *****************************************************************************/
/*!
 * \brief         Processes operation cycle updates
 *
 * \details       This function processes the operation cycle updates for all
 *                events using that cycle as operation cycle.
 *
 *                Since operation cycles can restart or only stop/start, the
 *                cycle status can be one of DEM_OPERATIONCYCLE_CYCLE_STARTED,
 *                DEM_OPERATIONCYCLE_CYCLE_STOPPED or
 *                DEM_OPERATIONCYCLE_CYCLE_RESTARTED (most other APIs only
 *                accept the first two states).
 *
 * \param[in]     CycleId
 *                Unique Id of the cycle
 * \param[in]     CycleStatus
 *                Cycle status changes
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_CycleUpdateReadiness(
  CONST(uint8, AUTOMATIC)  CycleId,
  CONST(uint8, AUTOMATIC)  CycleStatus
  );

/* ****************************************************************************
 * Dem_OperationCycle_UpdateObdDcy_End
 *****************************************************************************/
/*!
 * \brief         Processes driving cycle updates at stop trigger
 *
 * \details       This function processes the OBD driving cycle specific state
 *                transitions.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_UpdateObdDcy_End(
  void
  );

/* ****************************************************************************
 * Dem_OperationCycle_UpdateObdWarmup_End
 *****************************************************************************/
/*!
 * \brief         Processes warmup cycle updates at stop trigger
 *
 * \details       This function processes the warm-up cycle specific state
 *                transitions if WwhObd is globally supported. This does not 
 *                include aging, as aging is handled generically.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_UpdateObdWarmup_End(
  void
  );

/* ****************************************************************************
 * Dem_OperationCycle_UpdateObdDcy_Start
 *****************************************************************************/
/*!
 * \brief         Processes driving cycle updates at start trigger
 *
 * \details       This function processes the OBD driving cycle specific state
 *                transitions, e.g. IUMPR and DCY qualification. This does not
 *                include healing and status bit processing, as those are
 *                handled generically.
 *
 * \pre           -
 * \config        Feature OBD II or WWH-OBD is enabled
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_UpdateObdDcy_Start(
  void
  );

#if (DEM_FEATURE_NEED_GLOBAL_MIL_STATE == STD_ON)
/* ****************************************************************************
 * Dem_OperationCycle_UpdateObdAging
 *****************************************************************************/
/*!
 * \brief         Processes aging of OBD global statistics
 *
 * \details       Processes aging of OBD global statistics
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_GLOBAL_MIL_STATE == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_OperationCycle_UpdateObdAging(
  void
  );
#endif

/* ****************************************************************************
 * Dem_OperationCycle_UpdateObdWarmup_Start
 *****************************************************************************/
/*!
 * \brief         Processes warmup cycle updates at start trigger
 *
 * \details       This function processes the warm-up cycle specific state
 *                transitions. This does not include aging, as aging is handled
 *                generically.
 *
 * \pre           Feature OBD II or WWH-OBD is enabled
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_UpdateObdWarmup_Start(
  void
  );

/* ****************************************************************************
 * Dem_OperationCycle_SetStateObdDcy
 *****************************************************************************/
/*!
 * \brief         Queues restart or qualification of OBD driving cycle
 *
 * \details       Queues restart or qualification of OBD driving cycle if 
 *                feature OBD II or WWH-OBD is enabled
 *
 * \param[in]     ObdDcyId
 *                Unique Id of the OBD driving cycle
 *
 * \param[in]     CycleState
 *                DEM_CYCLE_STATE_START: Qualify OBD driving cycle
 *                DEM_CYCLE_STATE_END:   Restart OBD driving cycle.
 *
 * \return        E_OK
 *                Cycle state was queued successfully
 *
 * \return        E_NOT_OK
 *                Cycle state was not queued
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_OperationCycle_SetStateObdDcy(
  CONST(uint8, AUTOMATIC)  ObdDcyId,
  CONST(Dem_OperationCycleStateType, AUTOMATIC)  CycleState
  );

# if (DEM_CFG_SUPPORT_DELAY_WUC_TO_DCY == STD_ON)
/* ****************************************************************************
 * Dem_OperationCycle_SetStateWarmUp
 *****************************************************************************/
/*!
 * \brief         Queues state for WarmUp Cycle
 *
 * \details       Queues state for WarmUp Cycle
 *
 * \param[in]     CycleState
 *                DEM_CYCLE_STATE_START: Start a stopped cycle, or restart an
 *                                       active cycle.
 *                DEM_CYCLE_STATE_END:   Stop an active cycle.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DELAY_WUC_TO_DCY == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
  Dem_OperationCycle_SetStateWarmUp(
  CONST(Dem_OperationCycleStateType, AUTOMATIC)  CycleState
  );
#endif


/* ****************************************************************************
 * Dem_OperationCycle_CycleUpdateEnd
 *****************************************************************************/
/*!
 * \brief         Updates cycle state when cycle is ended
 *
 * \details       Processes global cycle counter and aging cycles
 *
 * \param[in]     CycleId
 *                Unique Id of the cycle
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_CycleUpdateEnd(
  CONST(uint8, AUTOMATIC)  CycleId
  );


#if (DEM_FEATURE_NEED_PID41_CALCULATION == STD_ON)
/* ****************************************************************************
 * Dem_OperationCycle_CycleUpdatePID41
 *****************************************************************************/
/*!
 * \brief         Updates pid41 when cycle is started
 *
 * \details       Processes PID41
 *
 * \param[in]     CycleId
 *                Unique Id of the cycle
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_PID41_CALCULATION == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_CycleUpdatePID41(
  CONST(uint8, AUTOMATIC)  CycleId
  );
#endif

/* ****************************************************************************
* Dem_OperationCycle_ProcessInitMonitorNotificationsOnStart
*****************************************************************************/
/*!
* \brief         Updates cycle state when cycle is started
*
* \details       Updates cycle state when cycle is started
*
* \param[in]     CycleId
*                Unique Id of the cycle
*
* \pre           -
*
* \context       TASK
* \synchronous   TRUE
* \reentrant     FALSE
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_ProcessInitMonitorNotificationsOnStart(
  CONST(uint8, AUTOMATIC)  CycleId
);

/* ****************************************************************************
 * Dem_OperationCycle_ObdCycleStop
 *****************************************************************************/
/*!
 * \brief         Stops passed Obd cycle
 *
 * \details       Stops passed Obd warm up or driving cycle
 *
 * \param[in]     CycleId
 *                Unique Id of the cycle
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_ObdCycleStop(
  CONST(uint8, AUTOMATIC)  CycleId
  );

/* ****************************************************************************
 * Dem_OperationCycle_ObdCycleStart
 *****************************************************************************/
/*!
 * \brief         Starts passed Obd cycle
 *
 * \details       Starts passed Obd warm up or driving cycle
 *
 * \param[in]     CycleId
 *                Unique Id of the cycle
 *
 * \pre           Feature OBD II or WWH-OBD is enabled
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_ObdCycleStart(
  CONST(uint8, AUTOMATIC)  CycleId
  );

/* ****************************************************************************
 * Dem_OperationCycle_ObdCycleUpdate
 *****************************************************************************/
/*!
 * \brief         Updates status of passed Obd cycle
 *
 * \details       Updates status of passed Obd warm up or driving cycle
 *
 * \param[in]     CycleId
 *                Unique Id of the cycle
 *
 * \param[in]     CycleStatus
 *                Cycle status changes
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_ObdCycleUpdate(
  CONST(uint8, AUTOMATIC)  CycleId,
  CONST(uint8, AUTOMATIC)  CycleStatus
  );

/* ****************************************************************************
 * Dem_OperationCycle_SetCycleStatus
 *****************************************************************************/
/*!
 * \brief         Set current state of a cycle.
 *
 * \details       Set current state of a cycle.
 *
 * \param[in]     CycleId
 *                Unique Id of the cycle
 * \param[in]     Status
 *                The state of the cycle
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_SetCycleStatus(
  CONST(uint8, AUTOMATIC)  CycleId,
  CONST(uint8, AUTOMATIC)  Status
  );


# if (DEM_CFG_SUPPORT_PID30 == STD_ON)
/* ****************************************************************************
 * Dem_OperationCycle_IncrementPID30
 *****************************************************************************/
/*!
 * \brief         Increment the PID30 Warm-Up cycle counter
 *
 * \details       Increment the PID30 Warm-Up cycle counter, latching at 0xff
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PID30 == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_IncrementPID30(
  void
  );
#endif

/* ****************************************************************************
 * Dem_OperationCycle_TestOBDDcyAutomaticRestart
 *****************************************************************************/
/*!
 * \brief         Test if the OBD driving cycle will be restarted automatically during 
 *                Dem Initialization
 *
 * \details       Test if the OBD driving cycle will be restarted automatically during 
 *                Dem Initialization
 *
 * \return        TRUE
 *                OBD driving cycle will be re-started
 *
 * \return        FALSE
 *                OBD driving cycle will not be re-started
 *
 * \pre           -
 *
 * \config        -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_OperationCycle_TestOBDDcyAutomaticRestart(
  void
);

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/

/* ****************************************************************************
 % Dem_OperationCycle_SetCycleStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_SetCycleStatus(
  CONST(uint8, AUTOMATIC)  CycleId,
  CONST(uint8, AUTOMATIC)  Status
  )
{
  uint16 lMask;

  lMask = (uint16)1 << CycleId;
  if (Status == DEM_OPERATIONCYCLE_CYCLE_STOPPED)
  {
    lMask = (uint16) (~lMask);
    Dem_OperationCycle_CurrentCycleState = (uint16)(Dem_OperationCycle_CurrentCycleState & lMask);
  }
  else
  {
    Dem_OperationCycle_CurrentCycleState = (uint16)(Dem_OperationCycle_CurrentCycleState | lMask);
  }
}
# if (DEM_CFG_SUPPORT_PID30 == STD_ON)
/* ****************************************************************************
 % Dem_OperationCycle_IncrementPID30
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_IncrementPID30(
  void
  )
{
  uint8 lWarmUpCount;

  lWarmUpCount = Dem_Mem_GetWarmUpCountSinceClear();
  /* Check if counter is latched */
  if (lWarmUpCount < 0xffU)
  {
    lWarmUpCount++;
    Dem_Mem_SetWarmUpCountSinceClear(lWarmUpCount);
  }
}
#endif


/* ****************************************************************************
 % Dem_OperationCycle_TestOBDDcyAutomaticRestart
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_OperationCycle_TestOBDDcyAutomaticRestart(                                                                                   /* PRQA S 3219 */ /* MD_DEM_14.1_CONFIGURATION_SWITCH */
  void
)
{
  boolean lReturnValue;

#if ((DEM_FEATURE_NEED_OBD == STD_ON) && (DEM_FEATURE_NEED_CYCLEAUTOMATICEND == STD_ON))
  if ( (Dem_Cfg_IsObdSupportedInVariant() == TRUE)
    && (Dem_Cfg_CycleIsAutomaticEnd(Dem_Cfg_GlobalObdDrivingCycleId()) == TRUE)
    && (DEM_OPERATIONCYCLE_TEST_DCY_QUALIFIED(Dem_OperationCycle_GetObdCycleStates()) == TRUE))
  {
    lReturnValue = TRUE;
  }
  else
#endif
  {
    lReturnValue = FALSE;
  }

  return lReturnValue;
}

#if (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
/* ****************************************************************************
 % Dem_OperationCycle_UpdateDTCCycleCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_UpdateDTCCycleCounter(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  CycleStatus
  )
{
  /* Precondition: DTC belongs to a Type 2 combined DTC group */
  Dem_Cfg_CombinedGroupIterType lCombinedIter;
  Dem_EventIdType lSubEventId;
  Dem_Cfg_CombinedGroupIndexType lGroupId;

  lGroupId = Dem_Cfg_EventCombinedGroup(EventId);

  /* Iterate through all active sub-events */
  for (Dem_Cfg_CombinedGroupIterInit(lGroupId, &lCombinedIter);                                                                  /* SBSW_DEM_CALL_ITERATOR_POINTER */
        Dem_Cfg_CombinedGroupIterExists(&lCombinedIter) == TRUE;                                                                 /* SBSW_DEM_CALL_ITERATOR_POINTER */
        Dem_Cfg_CombinedGroupIterNext(&lCombinedIter))                                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    lSubEventId = Dem_Cfg_CombinedGroupIterGet(&lCombinedIter);                                                                  /* SBSW_DEM_CALL_ITERATOR_POINTER */

    if (Dem_DTC_TestStoredStatus(lSubEventId) == TRUE)
    {
      Dem_Memory_UpdateEventsCycleCounter(lSubEventId, CycleStatus);
    }
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

/* ****************************************************************************
 % Dem_OperationCycle_GetPendingCycle
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_OperationCycle_GetPendingCycle(
  CONST(uint8, AUTOMATIC)  CycleId
  )
{
  return (uint8)(((Dem_OperationCycle_PendingCycleState & ((uint16)1 << CycleId)) != 0U)
          ? DEM_OPERATIONCYCLE_CYCLE_STARTED
          : DEM_OPERATIONCYCLE_CYCLE_STOPPED);
}

/* ****************************************************************************
 % Dem_OperationCycle_SetPendingCycle
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_SetPendingCycle(
  CONST(uint8, AUTOMATIC)  CycleId,
  CONST(uint8, AUTOMATIC)  Status
  )
{
  uint16 lMask;
  lMask = (uint16)1 << CycleId;

  Dem_OperationCycle_CycleFlag = (Dem_OperationCycle_CycleFlag | lMask);

  if (Status == DEM_OPERATIONCYCLE_CYCLE_STOPPED)
  {
    Dem_OperationCycle_PendingCycleState = Dem_OperationCycle_PendingCycleState & ((uint16)(~lMask));
  }
  else
  {
    Dem_OperationCycle_PendingCycleState = Dem_OperationCycle_PendingCycleState | lMask;
  }

  Dem_Scheduler_EnableTaskOnce(Dem_Scheduler_Task_OperationCycle);
}



/* ****************************************************************************
 % Dem_OperationCycle_QualifyDcy
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
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_QualifyDcy(
  void
  )
{
#if (DEM_FEATURE_NEED_OBD == STD_ON)
  if(Dem_Cfg_IsObdSupportedInVariant() == TRUE)
  {
# if (DEM_FEATURE_NEED_GLOBAL_MIL_STATE == STD_ON)
    boolean lOldMilIsActive;

    lOldMilIsActive = Dem_Indicator_TestMilReportedActive();
# endif

    Dem_DTC_CycleQualifyDcy();

  /* Synchronize the special indicator states */
    Dem_Indicator_UpdateSpecialIndicators();
# if (DEM_FEATURE_NEED_GLOBAL_MIL_STATE == STD_ON)
   if ( (lOldMilIsActive == FALSE)                                                                                                 
      && (Dem_Indicator_TestMilReportedActive() == TRUE) )                                                                         /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
    {
      Dem_Indicator_UpdatePIDsMilEnabled();
    }
# endif

    Dem_Iumpr_ReportOperationCycleChange(Dem_Cfg_GlobalObdDrivingCycleId(), DEM_OPERATIONCYCLE_CYCLE_QUALIFIED);

/* >>>> -------------------------------- Enter Critical Section: StateManager */
    Dem_EnterCritical_StateManager();

    Dem_OperationCycle_SetObdCycleStates(DEM_OPERATIONCYCLE_SET_DCY_QUALIFIED(Dem_OperationCycle_GetObdCycleStates()));

    Dem_LeaveCritical_StateManager();
/* <<<< -------------------------------- Leave Critical Section: StateManager */
  }
#endif /* (DEM_FEATURE_NEED_OBD == STD_ON) */
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_OperationCycle_ProcessCycles
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
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_ProcessCycles(
  void
  )
{
  uint8 lCycleId;
  uint16 lDem_Queue_CycleState;
  uint16 lDem_Queue_CycleFlag;
  uint16 lObdDcyMask;
  
  if (Dem_Cfg_IsObdSupportedInVariant() == TRUE)
  {
    lObdDcyMask  = (uint16)1 << Dem_Cfg_GlobalObdDrivingCycleId();
  }
  else
  {
    lObdDcyMask = 0u;
  }

/* >>>> -------------------------------- Enter Critical Section: StateManager */
  Dem_EnterCritical_StateManager();

  lDem_Queue_CycleState = Dem_OperationCycle_PendingCycleState;
  Dem_OperationCycle_PendingCycleState = (uint16)(Dem_OperationCycle_PendingCycleState & lObdDcyMask);

  lDem_Queue_CycleFlag = Dem_OperationCycle_CycleFlag;
  /* Queue state for the OBD driving cycle has to be reset after processing to prevent new
     restart while restart is still processed */
  Dem_OperationCycle_CycleFlag = (uint16)(Dem_OperationCycle_CycleFlag & lObdDcyMask);

  Dem_LeaveCritical_StateManager();
/* <<<< -------------------------------- Leave Critical Section: StateManager */

  lCycleId = 0u;
  while (lDem_Queue_CycleFlag != 0u)
  {
    if ((lDem_Queue_CycleFlag & 0x01U) != 0u)
    {
      uint8 lNewStatus;
      uint8 lOldStatus;
      lNewStatus = (uint8)(((lDem_Queue_CycleState & 0x01U) != 0u)
        ? DEM_OPERATIONCYCLE_CYCLE_STARTED : DEM_OPERATIONCYCLE_CYCLE_STOPPED);
      lOldStatus = Dem_OperationCycle_GetCurrentCycleStatus(lCycleId);
      if (lNewStatus == DEM_OPERATIONCYCLE_CYCLE_STARTED)
      {
#if (DEM_CFG_SUPPORT_DELAY_WUC_TO_DCY == STD_ON)
        if ( (Dem_Cfg_IsObdSupportedInVariant() == TRUE)
          && (Dem_Cfg_CycleIsObdDcy(lCycleId) == TRUE)
          && (DEM_OPERATIONCYCLE_TEST_WARMUP_CYCLE(Dem_OperationCycle_GetObdCycleStates()) == TRUE) )
        { /* Move the WarmupCycle start to a different trigger
            (respective bit lDem_Queue_CycleFlag may not be set for warmup cycles) */
          Dem_OperationCycle_CycleUpdate(Dem_Cfg_GlobalWarmupCycleId(), DEM_OPERATIONCYCLE_CYCLE_RESTARTED);
        }
#endif

        if (lNewStatus == lOldStatus)
        {
          Dem_OperationCycle_CycleUpdate(lCycleId, DEM_OPERATIONCYCLE_CYCLE_RESTARTED);
        }
        else
        {
          Dem_OperationCycle_CycleUpdate(lCycleId, DEM_OPERATIONCYCLE_CYCLE_STARTED);
        }
      }
      else
      {
        Dem_OperationCycle_CycleUpdate(lCycleId, DEM_OPERATIONCYCLE_CYCLE_STOPPED);
      }
    }
    ++lCycleId;
    lDem_Queue_CycleFlag = (uint16)(lDem_Queue_CycleFlag >> 1U);
    lDem_Queue_CycleState = (uint16)(lDem_Queue_CycleState >> 1U);
  }
  if ((Dem_Cfg_IsObdSupportedInVariant() == TRUE))
  {
    /* >>>> -------------------------------- Enter Critical Section: StateManager */
    Dem_EnterCritical_StateManager();
    /* Reset the queue state for the OBD driving cycle after processing */
    Dem_OperationCycle_PendingCycleState = (uint16)(Dem_OperationCycle_PendingCycleState & (uint16)(~lObdDcyMask));
    Dem_OperationCycle_CycleFlag = (uint16)(Dem_OperationCycle_CycleFlag & (uint16)(~lObdDcyMask));
    Dem_LeaveCritical_StateManager();
    /* <<<< -------------------------------- Leave Critical Section: StateManager */
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

#if ((DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_OFF) \
     && ((DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF) || (DEM_FEATURE_NEED_CYCLE_COUNTERS == STD_ON)))
/* ****************************************************************************
 % Dem_OperationCycle_ProcessCycleUpdate_StoredEvents
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
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_ProcessCycleUpdate_StoredEvents(
  CONST(uint8, AUTOMATIC)  CycleId,
  CONST(uint16, AUTOMATIC)  CycleCounter
  )
{
  Dem_Cfg_MemoryIndexType lMemoryIndex;
  Dem_Memory_AllEventMemEntriesIterType MemEntryIter;

  /* Iterate through the primary indices - the chronological index becomes
      invalid in case an event ages */
  for (Dem_Memory_AllEventMemEntries_IterInit(&MemEntryIter);                                                                    /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Memory_AllEventMemEntries_IterExists(&MemEntryIter) == TRUE;                                                          /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Memory_AllEventMemEntries_IterNext(&MemEntryIter))                                                                    /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_EventIdType lEventId;

    lMemoryIndex = Dem_Memory_AllEventMemEntries_IterGetMemoryIndex(&MemEntryIter);                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */
    lEventId = Dem_MemoryEntry_GetEventId(Dem_MemoryEntry_GetId(lMemoryIndex));
    if (Dem_Event_TestValidHandle(lEventId) == TRUE)
    {
# if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF)
      if (Dem_Cfg_EventAgingCycle(lEventId) == CycleId)
      {
        Dem_DTC_AgingCycle(lEventId, CycleCounter, lMemoryIndex);
      }
# endif
# if (DEM_FEATURE_NEED_CYCLE_COUNTERS == STD_ON)
      if (Dem_Cfg_EventOperationCycle(lEventId) == CycleId)
      {
        Dem_Memory_LatchCycleCounters(lMemoryIndex, CycleCounter);
      }
# endif
    }
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON)
/* ****************************************************************************
 % Dem_OperationCycle_ProcessCycleUpdate_AllEvents
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_ProcessCycleUpdate_AllEvents(
  CONST(uint8, AUTOMATIC)  CycleId,
  CONST(uint16, AUTOMATIC)  CycleCounter
  )
{
  Dem_OperationCycle_RecalculateAgingThreshold_AllEvents(CycleId, CycleCounter);

# if (DEM_FEATURE_NEED_CYCLE_COUNTERS == STD_ON)
  {
    Dem_OperationCycle_LatchCycleCounters(CycleId, CycleCounter);
  }
# endif
}
#endif

#if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON)
/* ****************************************************************************
 % Dem_OperationCycle_RecalculateAgingThreshold_AllEvents
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
Dem_OperationCycle_RecalculateAgingThreshold_AllEvents(
  CONST(uint8, AUTOMATIC)  CycleId,
  CONST(uint16, AUTOMATIC)  CycleCounter
  )
{
  Dem_Cfg_MemoryIndexType lMemoryIndex;
  Dem_EventIdType lEventId;
  Dem_DTCInternal_StoredStatusType lStoredStatus;

  /* Iterate over all events, considering only Master Events,  */
  for (lEventId = DEM_EVENT_FIRST; lEventId < Dem_Cfg_GlobalEventCount(); ++lEventId)
  {
    /* Events which do not have a DTC configured need not be handled */
    if (Dem_Cfg_EventUdsDtc(lEventId) == DEM_CFG_DTC_UDS_INVALID)
    {
      continue;                                                                                                                  
    }

# if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
    /* Only process master events because combined events have the same DTC */
    if (Dem_Cfg_GetMasterEvent(lEventId) != lEventId)
    {
      continue;                                                                                                                  
    }
# endif

    /* Event is currently active (normal case) or aging with a memory entry */
    lStoredStatus = Dem_DTCInternalStatus_GetStoredStatus(Dem_DTC_GetInternalStatus(lEventId));
    if ( (lStoredStatus == Dem_DTCInternalStatus_StoredStatus_Active)
      || (lStoredStatus == Dem_DTCInternalStatus_StoredStatus_Aging) )
    {
      if (Dem_Cfg_EventAgingCycle(lEventId) == CycleId)
      {
        lMemoryIndex = Dem_Memory_FindMemoryIndex_StoredEvent(lEventId);
        Dem_DTC_AgingCycle(lEventId, CycleCounter, lMemoryIndex);
        continue;                                                                                                                
      }
    }

    /* Event is currently aging without a memory entry */
    if (Dem_DTC_GetAgingStatus(lEventId) == Dem_DTC_AgingStatusInProgress)
    {
      if (Dem_Cfg_EventAgingCycle(lEventId) == CycleId)
      {
        Dem_DTC_AgingCycle(lEventId, CycleCounter, DEM_MEM_INVALID_MEMORY_INDEX);
      }
    }
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if ((DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON) && (DEM_FEATURE_NEED_CYCLE_COUNTERS == STD_ON))
/* ****************************************************************************
 % Dem_OperationCycle_LatchCycleCounters
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_LatchCycleCounters(
  CONST(uint8, AUTOMATIC)  CycleId,
  CONST(uint16, AUTOMATIC)  CycleCounter
  )
{
  Dem_Cfg_MemoryIndexType lMemoryIndex;
  Dem_Memory_AllEventMemEntriesIterType MemEntryIter;

  /* Iterate through the primary indices - the chronological index becomes
      invalid in case an event ages */
  for (Dem_Memory_AllEventMemEntries_IterInit(&MemEntryIter);                                                                    /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Memory_AllEventMemEntries_IterExists(&MemEntryIter) == TRUE;                                                          /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Memory_AllEventMemEntries_IterNext(&MemEntryIter))                                                                    /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_EventIdType lEventId;

    lMemoryIndex = Dem_Memory_AllEventMemEntries_IterGetMemoryIndex(&MemEntryIter);                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */
    lEventId = Dem_MemoryEntry_GetEventId(Dem_MemoryEntry_GetId(lMemoryIndex));
    if (Dem_Event_TestValidHandle(lEventId) == TRUE)
    {
      if (Dem_Cfg_EventOperationCycle(lEventId) == CycleId)
      {
        Dem_Memory_LatchCycleCounters(lMemoryIndex, CycleCounter);
      }
    }
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

/* ****************************************************************************
 % Dem_OperationCycle_UpdateTestEventAffected
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
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_OperationCycle_UpdateTestEventAffected(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  CycleId
  )
{
  boolean lReturnValue;
  lReturnValue = TRUE;

  if (Dem_Cfg_EventOperationCycle(EventId) != CycleId)
  { /* Event needs to depend on the modified cycle */
    lReturnValue = FALSE;
  }
#if (DEM_CFG_ISCONST_AVAILABLEINVARIANT == STD_OFF)
  if (Dem_DTC_TestDtcAvailableInVariant(EventId) == FALSE)
  { /* Don't process unavailable DTCs */
    lReturnValue = FALSE;
  }
#endif
  if (Dem_Cfg_GetMasterEvent(EventId) != EventId)
  { /* Make sure to only process each event once */
    lReturnValue = FALSE;
  }
  if (Dem_DTC_TestDtcAvailable(EventId) == FALSE)
  { /* Don't process unavailable DTCs */
    lReturnValue = FALSE;
  }

  return lReturnValue;
}

/* ****************************************************************************
% Dem_OperationCycle_ResetMemIndependentCycleCounterOnOpEnd
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
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_ResetMemIndependentCycleCounterOnOpEnd(
  Dem_EventIdType EventId,
  uint8 CycleStatus
)
{
  Dem_DTC_UDSStatusType lUDSStatus;
  lUDSStatus = Dem_DTC_ApplyCombinedStatus(Dem_DTC_RetrieveStatus(EventId));

  if (((CycleStatus & DEM_OPERATIONCYCLE_CYCLE_STOPPED) != 0u)
    && (Dem_UDSStatus_Test_TNCTOC(lUDSStatus) == FALSE))                                                                         
  {
    if (Dem_UDSStatus_Test_TFTOC(lUDSStatus) == FALSE)
    { /* reset the 'consecutive failed cycles' */
      Dem_DTC_ResetFaultPendingCounter(EventId);
    }
  }
}
/* ****************************************************************************
 % Dem_OperationCycle_UpdateProcessEvent
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
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_UpdateProcessEvent(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  CycleStatus
  )
{
  Dem_DTC_UDSStatusType lOldDtcStatus;
  Dem_DTC_UDSStatusType lOldExternalDtcStatus;
  Dem_DTC_UDSStatusType lNewDtcStatus;

  Dem_Event_DataUpdateStart(EventId);
  if(Dem_DTC_IsMemIndependentCycleCounterEnabled() == TRUE)
  {
    Dem_OperationCycle_ResetMemIndependentCycleCounterOnOpEnd(EventId, CycleStatus);
  }

  {
#if (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
    Dem_Cfg_CombinedGroupIndexType lGroupId;

    lGroupId = Dem_Cfg_EventCombinedGroup(EventId);
    if (lGroupId != DEM_CFG_COMBINED_GROUP_INVALID)
    {
      Dem_OperationCycle_UpdateDTCCycleCounter(EventId, CycleStatus);
    }
    else
#endif
    {
      if (Dem_DTC_TestStoredStatus(EventId) == TRUE)
      {
        Dem_Memory_UpdateEventsCycleCounter(EventId, CycleStatus);
      }
    }
  }

  lOldDtcStatus = Dem_DTC_GetDTCStatus(EventId);
  lOldExternalDtcStatus = Dem_DTC_GenerateExternalOnlyStatus(EventId, lOldDtcStatus);
  Dem_DTC_OpCycle(EventId, CycleStatus);
  lNewDtcStatus = Dem_DTC_GetDTCStatus(EventId);

  Dem_Event_DataUpdateFinish(EventId);

  /* Process permanent memory healing */
  if (Dem_DTC_TestEventStoresPermanentDTC(EventId) == TRUE)
  {
    if (Dem_Cfg_IsObdIISupportedInVariant() == TRUE)
    {
      Dem_Data_PermanentEntryUpdate(EventId, lOldDtcStatus, lNewDtcStatus);
    }
    else if ((Dem_Cfg_IsWwhObdSupportedInVariant() == TRUE))
    {
      Dem_Data_PermanentEntryUpdateOnDCyEnd(EventId, lOldDtcStatus);
    }
    else
    {
      /* MISRA case */
    }
  }

  /* Skip notifications if the cycle is started during Dem_Init - the
  environment is not initialized yet and cannot handle callbacks */
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == TRUE)
  {
    Dem_Notifications_DtcStatusChanged(EventId,
                                       lOldExternalDtcStatus,
                                       Dem_DTC_GenerateExternalOnlyStatus(EventId, lNewDtcStatus),
                                       DEM_NOTIFICATIONS_DTC_REINIT);
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_OperationCycle_CycleUpdateReadiness
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
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_CycleUpdateReadiness(
  CONST(uint8, AUTOMATIC)  CycleId,
  CONST(uint8, AUTOMATIC)  CycleStatus
  )
{
  Dem_EventIdType lEventId;
  uint8 lOldPermanentCount;

  /* Perform transitions due to cycle end or tick */
  if (Dem_Cfg_IsPermanentSupportedInVariant() == TRUE)
  {
    lOldPermanentCount = Dem_Memory_GetNumAllocatedMemoryEntry(DEM_CFG_MEMORYID_PERMANENT);
  }
  else
  {
    lOldPermanentCount = 0;
  }

  for (lEventId = DEM_EVENT_FIRST; lEventId < Dem_Cfg_GlobalEventCount(); ++lEventId)
  {
    if (Dem_OperationCycle_UpdateTestEventAffected(lEventId, CycleId) == TRUE)
    {
      Dem_OperationCycle_UpdateProcessEvent(lEventId, CycleStatus);
    }
  } /* while (lEventId > DEM_EVENT_INVALID) */

  if ( (Dem_Cfg_IsPermanentSupportedInVariant() == TRUE)
    && (lOldPermanentCount == Dem_Cfg_GlobalPermanentMaxCount())
    && (lOldPermanentCount > Dem_Memory_GetNumAllocatedMemoryEntry(DEM_CFG_MEMORYID_PERMANENT)) )
  { /* One or more events healed from full permanent memory, fill up */
    Dem_Memory_PermanentFillUp();
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_OperationCycle_UpdateObdDcy_End
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
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_UpdateObdDcy_End(
  void
  )
{
# if (DEM_FEATURE_NEED_GLOBAL_MIL_STATE == STD_ON)
  /* Reset PID aging counter if at least one DTC triggers the MIL */
  if (Dem_Indicator_TestMilReportedActive() == TRUE)
  {
    Dem_Mem_SetPidAgingCounter(DEM_MEM_PID_AGING_COUNTER_THRESHOLD);
  }
# endif
# if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
  if (Dem_Cfg_IsWwhObdSupportedInVariant() == TRUE)
  { 
    uint8 lB1HealingCounter;
    uint8 lContinuousMiHealingCounter;

    /* Process B1 counter Healing */
    lB1HealingCounter = Dem_Mem_GetB1HealingCounter();

    if (lB1HealingCounter < DEM_DATA_B1_HEALING_COUNTER_THRESHOLD)
    {
      ++lB1HealingCounter;
      Dem_Mem_SetB1HealingCounter(lB1HealingCounter);
    }

    /* clear the B1 counter if it has healed */
    if ( (Dem_Indicator_GetDtcClassMILCount(DEM_ESM_WWHOBD_DTCCLASS_B1) == 0u)
      && (lB1HealingCounter >= DEM_DATA_B1_HEALING_COUNTER_THRESHOLD) )
    {
      Dem_Mem_SetB1Counter(0);
    }

    lContinuousMiHealingCounter = Dem_Mem_GetContinuousMiHealingCounter();

    if (lContinuousMiHealingCounter == DEM_DATA_CONTINUOUS_MI_HEALING_COUNTER_LOCKED)
    { /* Start Healing */
      Dem_Mem_SetContinuousMiHealingCounter(0);
    }
    else if (lContinuousMiHealingCounter < DEM_DATA_CONTINUOUS_MI_HEALING_COUNTER_HEALED)
    {  /* Healing is active */
      ++lContinuousMiHealingCounter;

      if (lContinuousMiHealingCounter == DEM_DATA_CONTINUOUS_MI_HEALING_COUNTER_THRESHOLD)
      {
        lContinuousMiHealingCounter = DEM_DATA_CONTINUOUS_MI_HEALING_COUNTER_HEALED;
        Dem_Mem_SetContinuousMiAgingCounter(0);
        Dem_Mem_SetContinuousMiAgingTimer(0);
      }
      Dem_Mem_SetContinuousMiHealingCounter(lContinuousMiHealingCounter);
    }
    else
    {
      /* nothing to do here */
    }
  }
# endif
}

/* ****************************************************************************
 % Dem_OperationCycle_UpdateObdWarmup_End
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
Dem_OperationCycle_UpdateObdWarmup_End(
  void
  )
{
#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
  uint8 lContinuousMiAgingCounter;

  lContinuousMiAgingCounter = Dem_Mem_GetContinuousMiAgingCounter();

  if (lContinuousMiAgingCounter < DEM_DATA_CONTINUOUS_MI_AGING_COUNTER_AGED)
  { /* Aging is active, process MI aging counter */
    ++lContinuousMiAgingCounter;

    if (lContinuousMiAgingCounter == DEM_DATA_CONTINUOUS_MI_AGING_COUNTER_THRESHOLD)
    {
      Dem_Mem_SetContinuousMiCounter(0);
      lContinuousMiAgingCounter = DEM_DATA_CONTINUOUS_MI_AGING_COUNTER_AGED;
      Dem_Mem_SetContinuousMiAgingTimer(DEM_DATA_CONTINUOUS_MI_AGING_TIMER_AGED);
    }
    Dem_Mem_SetContinuousMiAgingCounter(lContinuousMiAgingCounter);
  }
#endif
}

/* ****************************************************************************
 % Dem_OperationCycle_UpdateObdDcy_Start
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
Dem_OperationCycle_UpdateObdDcy_Start(
  void
  )
{
# if (DEM_FEATURE_NEED_MIL_GROUPS == STD_ON)
  /* ----- MIL group handling at DCY restart ----- */
  {
    uint16  MilGroupIndex = Dem_Cfg_GlobalMilGroupCount();

    while (MilGroupIndex != DEM_CFG_MIL_GROUP_INVALID)
    {
      MilGroupIndex--;
      /* reset incremented flag for each MIL group */
      Dem_Mem_ResetMilGroupIncremented(MilGroupIndex);

      /* reset trip counter of MIL group if no events are pending */
      if (Dem_EventInternalStatus_GetMilGroupPendingCount(MilGroupIndex) == 0u)
      {
        Dem_Mem_ResetMilGroupTripCount(MilGroupIndex);
      }
    }
  }
# endif /* (DEM_FEATURE_NEED_MIL_GROUPS == STD_ON) */

#if (DEM_FEATURE_NEED_OBD == STD_ON)
  {
    uint8  lObdCycleStates;
    /* The reset of the DCY and the PFC cycle must be done at last,
     * so all preceding actions may use the correct states.
     */
/* >>>> -------------------------------- Enter Critical Section: StateManager */
    Dem_EnterCritical_StateManager();

    lObdCycleStates = Dem_OperationCycle_GetObdCycleStates();
    lObdCycleStates = DEM_OPERATIONCYCLE_RESET_DCY_QUALIFIED(lObdCycleStates);
    lObdCycleStates = DEM_OPERATIONCYCLE_RESET_PFC_CYCLE(lObdCycleStates);
# if (DEM_CFG_SUPPORT_DELAY_WUC_TO_DCY == STD_ON)
    lObdCycleStates = DEM_OPERATIONCYCLE_RESET_WARMUP_CYCLE(lObdCycleStates);
#  if(DEM_CFG_SUPPORT_PID30 == STD_ON)
    lObdCycleStates = DEM_OPERATIONCYCLE_RESET_WARMUP_CYCLE_INCREMENTED(lObdCycleStates);
#  endif
# endif
    Dem_OperationCycle_SetObdCycleStates(lObdCycleStates);

    Dem_LeaveCritical_StateManager();
/* <<<< -------------------------------- Leave Critical Section: StateManager */
  }
#endif
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

#if (DEM_FEATURE_NEED_GLOBAL_MIL_STATE == STD_ON)
/* ****************************************************************************
 % Dem_OperationCycle_UpdateObdAging
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
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_OperationCycle_UpdateObdAging(
  void
  )
{
  uint8 lPidAgingCounter;

  lPidAgingCounter = Dem_Mem_GetPidAgingCounter();

  if (lPidAgingCounter != 0u)
  {
    --lPidAgingCounter;

    if (lPidAgingCounter == 0u)
    { /* Reset the PIDs */
# if (DEM_CFG_SUPPORT_PID21 == STD_ON)
/* >>>> -------------------------------- Enter Critical Section: NonAtomic32bit */
      Dem_EnterCritical_NonAtomic32bit();
      /* Clear Odometer for MIL on */
      Dem_Mem_SetOdometerMilOn(0u);
      Dem_LeaveCritical_NonAtomic32bit();
/* <<<< -------------------------------- Leave Critical Section: NonAtomic32bit */
# endif
# if (DEM_CFG_SUPPORT_PID4D == STD_ON)
      Dem_Mem_SetEngineTimeMilOn(0u);
# endif
    }
    Dem_Mem_SetPidAgingCounter(lPidAgingCounter);
  }
}
#endif /* (DEM_FEATURE_NEED_GLOBAL_MIL_STATE == STD_ON) */


/* ****************************************************************************
 % Dem_OperationCycle_UpdateObdWarmup_Start
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_UpdateObdWarmup_Start(
  void
  )
{
#if (DEM_CFG_SUPPORT_PID30 == STD_ON && DEM_CFG_SUPPORT_DELAY_WUC_TO_DCY == STD_OFF)
  /* If WUC is delayed to DCY restart counter is incremented synchronous with Dem_SetOperationCycleState() */
  Dem_OperationCycle_IncrementPID30();
#endif
#if (DEM_FEATURE_NEED_GLOBAL_MIL_STATE == STD_ON)
  /* Process PID aging if MIL is reported as inactive */
  if (Dem_Indicator_TestMilReportedActive() == FALSE)
  {
    Dem_OperationCycle_UpdateObdAging();
  }
#endif
}

/* ****************************************************************************
 % Dem_OperationCycle_SetStateObdDcy
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
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_OperationCycle_SetStateObdDcy(
  CONST(uint8, AUTOMATIC)  ObdDcyId,
  CONST(Dem_OperationCycleStateType, AUTOMATIC)  CycleState
  )
{
#if (DEM_FEATURE_NEED_OBD == STD_ON)
  Std_ReturnType lReturnValue;

  lReturnValue = E_OK;

  /* The OBD driving cycle is always started but changes between qualified and not qualified */
  if (CycleState == DEM_CYCLE_STATE_START)
  { /* Qualify Driving Cycle */
    if ( (Dem_OperationCycle_IsPendingDcyCycle() == FALSE)
      && (DEM_OPERATIONCYCLE_TEST_DCY_QUALIFIED(Dem_OperationCycle_GetObdCycleStates()) == FALSE))
    { /* Queue the qualification of driving cycle unless already qualified */
      if (Dem_OperationCycle_IsPendingCycle(ObdDcyId) == FALSE)
      {
        Dem_OperationCycle_SetPendingDcyCycle();
        Dem_Scheduler_EnableTaskOnce(Dem_Scheduler_Task_OperationCycle);
      }
      else
      {
        /* Stop-Start shall notify the application that no action was taken */
        lReturnValue = E_NOT_OK;
      }
    }
  }
  else
  {
    /* Restart DCY */
    if (DEM_OPERATIONCYCLE_TEST_DCY_QUALIFIED(Dem_OperationCycle_GetObdCycleStates()) == TRUE)
    {
      if (Dem_OperationCycle_IsPendingCycle(ObdDcyId) == FALSE)
      {
        /* >>>> -------------------------------- Enter Critical Section: StateManager */
        Dem_EnterCritical_StateManager();
        /* Qualified driving cycle is re-started */
        Dem_OperationCycle_SetPendingCycle(ObdDcyId, DEM_OPERATIONCYCLE_CYCLE_STARTED);

        Dem_LeaveCritical_StateManager();
        /* <<<< -------------------------------- Leave Critical Section: StateManager */
      }
      else
      {
        /* Stop-Stop is silently ignored */
      }
    }
  }
  return lReturnValue;
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(ObdDcyId)                                                                                     /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(CycleState)                                                                                   /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return E_NOT_OK;
#endif
}

#if (DEM_CFG_SUPPORT_DELAY_WUC_TO_DCY == STD_ON)
/* ****************************************************************************
 % Dem_OperationCycle_SetStateWarmUp
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
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
  Dem_OperationCycle_SetStateWarmUp(
  CONST(Dem_OperationCycleStateType, AUTOMATIC)  CycleState
  )
{
  if (CycleState == DEM_CYCLE_STATE_START)
  { /* Don't actually start the cycle, only set flag this DCY */
    /* >>>> -------------------------------- Enter Critical Section: StateManager */
    Dem_EnterCritical_StateManager();

    Dem_OperationCycle_SetObdCycleStates(DEM_OPERATIONCYCLE_SET_WARMUP_CYCLE(Dem_OperationCycle_GetObdCycleStates()));

# if(DEM_CFG_SUPPORT_PID30 == STD_ON)
    if(DEM_OPERATIONCYCLE_TEST_WARMUP_CYCLE_INCREMENTED(Dem_OperationCycle_GetObdCycleStates()) == FALSE)
    {
      Dem_OperationCycle_IncrementPID30();
      Dem_OperationCycle_SetObdCycleStates(DEM_OPERATIONCYCLE_SET_WARMUP_CYCLE_INCREMENTED(Dem_OperationCycle_GetObdCycleStates()));
    }
# endif

    Dem_LeaveCritical_StateManager();
    /* <<<< -------------------------------- Leave Critical Section: StateManager */
  }
  /* Else: Ignore */
}
#endif

/* ****************************************************************************
 % Dem_OperationCycle_CycleUpdateEnd
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
Dem_OperationCycle_CycleUpdateEnd(
  CONST(uint8, AUTOMATIC)  CycleId
  )
{
  uint16 lCycleCounter;
#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
  uint8 lMode02FreezeFrameOld;
  lMode02FreezeFrameOld = Dem_Mem_FreezeFrameIndexMode02;
#endif
  /* Tick the cycle if necessary */
  lCycleCounter = Dem_OperationCycle_GetCycleCounter(CycleId);
  lCycleCounter = Dem_OperationCycle_AddCycleCount(lCycleCounter, 1U);
  Dem_OperationCycle_SetCycleCounter(CycleId, lCycleCounter);

#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF) || (DEM_FEATURE_NEED_CYCLE_COUNTERS == STD_ON)
  /* Aging cycle start */
# if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON)
  Dem_OperationCycle_ProcessCycleUpdate_AllEvents(CycleId, lCycleCounter);
# else
  Dem_OperationCycle_ProcessCycleUpdate_StoredEvents(CycleId, lCycleCounter);
# endif
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
  if (Dem_Cfg_IsObdIISupportedInVariant() == TRUE)
  {
    /* If no Event is visible (index has changed during aging) in Mode02 after aging, scan for a new one */
    if (lMode02FreezeFrameOld != Dem_Mem_FreezeFrameIndexMode02)
    {
      Dem_Mem_FreezeFrameIndexMode02 = Dem_MemObdFreezeFrame_SelectHighestPriorFreezeFrame();
    }
  }
#endif
}

#if (DEM_FEATURE_NEED_PID41_CALCULATION == STD_ON)
/* ****************************************************************************
 % Dem_OperationCycle_CycleUpdatePID41
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_CycleUpdatePID41(
  CONST(uint8, AUTOMATIC)  CycleId
  )
{
  if (Dem_Cfg_CycleIsObdDcy(CycleId) == TRUE)
  {
    Dem_Mem_SetPid41DisabledMask(0);
  }
}
#endif

/* ****************************************************************************
% Dem_OperationCycle_ProcessInitMonitorNotificationsOnStart
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
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_ProcessInitMonitorNotificationsOnStart(
  CONST(uint8, AUTOMATIC)  CycleId
)
{
  /* Skip notifications if the cycle is started during Dem_Init - the
  environment is not initialized yet and cannot handle callbacks */
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == TRUE)
  {
    Dem_EventIdType lEventId;
    for (lEventId = DEM_EVENT_FIRST; lEventId < Dem_Cfg_GlobalEventCount(); ++lEventId)
    {
      if (Dem_OperationCycle_UpdateTestEventAffected(lEventId, CycleId) == TRUE)
      {
        /* Call Init Monitor Callbacks */
        Dem_DTC_InvokeInitMonitorCallbacks(lEventId);
      }
    }
  }
}


/* ****************************************************************************
 % Dem_OperationCycle_ObdCycleStop
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
Dem_OperationCycle_ObdCycleStop(
  CONST(uint8, AUTOMATIC)  CycleId
  )
{
  if (CycleId == Dem_Cfg_GlobalObdDrivingCycleId())
  {
    Dem_OperationCycle_UpdateObdDcy_End();
  }

  if ( (Dem_Cfg_IsWwhObdSupportedInVariant() == TRUE) 
    && (CycleId == Dem_Cfg_GlobalWarmupCycleId()) )
  {
    Dem_OperationCycle_UpdateObdWarmup_End();
  }
}

/* ****************************************************************************
 % Dem_OperationCycle_ObdCycleStart
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
Dem_OperationCycle_ObdCycleStart(
  CONST(uint8, AUTOMATIC)  CycleId
  )
{
  /* If WarmUpCycle -> raise WUC counter */
  if (Dem_Cfg_CycleIsWarmup(CycleId) == TRUE)
  {
    Dem_OperationCycle_UpdateObdWarmup_Start();
  }

  if (Dem_Cfg_CycleIsObdDcy(CycleId) == TRUE)
  {
    Dem_OperationCycle_UpdateObdDcy_Start();
  }
}

/* ****************************************************************************
 % Dem_OperationCycle_ObdCycleUpdate
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
Dem_OperationCycle_ObdCycleUpdate(
  CONST(uint8, AUTOMATIC)  CycleId,
  CONST(uint8, AUTOMATIC)  CycleStatus
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(CycleId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(CycleStatus)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  if (Dem_Cfg_IsObdSupportedInVariant() == TRUE)
  {
    if ((CycleStatus & DEM_OPERATIONCYCLE_CYCLE_STOPPED) != 0U)
    {
      Dem_OperationCycle_ObdCycleStop(CycleId);
    }

    if ((CycleStatus & DEM_OPERATIONCYCLE_CYCLE_STARTED) != 0U)
    {
      Dem_OperationCycle_ObdCycleStart(CycleId);
    }
  }
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
/*!
 * \addtogroup Dem_OperationCycle_Public
 * \{
 */

/* ****************************************************************************
 % Dem_OperationCycle_UpdateCycleStatesInNvBlock
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_UpdateCycleStatesInNvBlock(
  void
  )
{
#if (DEM_CFG_SUPPORT_OPCYCLE_STORAGE == STD_ON)
  /* copy back cycle state for NVRAM storage */
  Dem_Cfg_AdminData.CycleState = Dem_OperationCycle_CurrentCycleState;
#endif
}

/* ****************************************************************************
 % Dem_OperationCycle_MainFunction
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
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_MainFunction(
  void
  )
{
  if ( (Dem_Cfg_IsObdSupportedInVariant() == TRUE)
    && (Dem_OperationCycle_IsPendingDcyCycle() == TRUE))
  {
    Dem_OperationCycle_QualifyDcy();

    Dem_OperationCycle_ClearPendingDcyCycle();
  }

  if (Dem_OperationCycle_CycleFlag != 0U)
  {
    Dem_OperationCycle_ProcessCycles();
  }
}

/* ****************************************************************************
 % Dem_OperationCycle_CycleUpdate
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
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_OperationCycle_CycleUpdate(
  CONST(uint8, AUTOMATIC)  CycleId,
  CONST(uint8, AUTOMATIC)  CycleStatus
  )
{
  Dem_OperationCycle_SetCycleStatus(CycleId, DEM_OPERATIONCYCLE_CYCLE_STOPPED);

  if ((CycleStatus & DEM_OPERATIONCYCLE_CYCLE_STOPPED) != 0U)
  {
    Dem_OperationCycle_CycleUpdateEnd(CycleId);
  }

#if (DEM_FEATURE_NEED_PID41_CALCULATION == STD_ON)
  if ((CycleStatus & DEM_OPERATIONCYCLE_CYCLE_STARTED) != 0U)
  {
    Dem_OperationCycle_CycleUpdatePID41(CycleId);
  }
#endif

  Dem_Iumpr_ReportOperationCycleChange(CycleId, CycleStatus);
  /* Operation Cycle start / end */
  Dem_OperationCycle_CycleUpdateReadiness(CycleId, CycleStatus);

  Dem_OperationCycle_ObdCycleUpdate(CycleId, CycleStatus);

  if ((CycleStatus & DEM_OPERATIONCYCLE_CYCLE_STARTED) != 0U)
  {
    Dem_OperationCycle_SetCycleStatus(CycleId, DEM_OPERATIONCYCLE_CYCLE_STARTED);
    Dem_OperationCycle_ProcessInitMonitorNotificationsOnStart(CycleId);
  }
}

/* ****************************************************************************
 % Dem_OperationCycle_SetState
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
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_OperationCycle_SetState(
  CONST(uint8, AUTOMATIC)  CycleId,
  CONST(Dem_OperationCycleStateType, AUTOMATIC)  CycleState
  )
{
  Std_ReturnType lReturnValue;
  lReturnValue = E_OK;

  /* If OBD is enabled, the driving cycle is handled different */
  if (Dem_Cfg_CycleIsObdDcy(CycleId) == TRUE)
  {
    lReturnValue = Dem_OperationCycle_SetStateObdDcy(CycleId, CycleState);
  }
  else if ( (Dem_Cfg_IsObdSupportedInVariant() == TRUE)
         && (Dem_Iumpr_IsIgnitionHybrid(CycleId) == TRUE))
  {
    Dem_Iumpr_ProcessIgnHybridCycleCounterIncrement(CycleState);
    Dem_OperationCycle_SetStateNormalCycle(CycleId, CycleState);
  }
# if (DEM_CFG_SUPPORT_DELAY_WUC_TO_DCY == STD_ON)
  else if (Dem_Cfg_CycleIsWarmup(CycleId) == TRUE)
  {
    Dem_OperationCycle_SetStateWarmUp(CycleState);
  }
# endif
  else
  {
    Dem_OperationCycle_SetStateNormalCycle(CycleId, CycleState);
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_OperationCycle_SetStateNormalCycle
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
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_SetStateNormalCycle(
CONST(uint8, AUTOMATIC)  CycleId,
CONST(Dem_OperationCycleStateType, AUTOMATIC)  CycleState
)
{
  uint8 lOldCycleStatus;
  lOldCycleStatus = Dem_OperationCycle_GetCurrentCycleStatus(CycleId);

  if ((lOldCycleStatus != DEM_OPERATIONCYCLE_CYCLE_STOPPED)
    || (CycleState != DEM_CYCLE_STATE_END))
  {
    /* >>>> -------------------------------- Enter Critical Section: StateManager */
    Dem_EnterCritical_StateManager();

    if (Dem_OperationCycle_IsPendingCycle(CycleId) == TRUE)
    {
      uint8 lPendingCycleStatus;

      lPendingCycleStatus = Dem_OperationCycle_GetPendingCycle(CycleId);

      if (lPendingCycleStatus == DEM_OPERATIONCYCLE_CYCLE_STOPPED)
      { /* START->END, END->START through two calls to the function is accepted and queued */
        if (CycleState == DEM_CYCLE_STATE_START)
        {
          Dem_OperationCycle_SetPendingCycle(CycleId, DEM_OPERATIONCYCLE_CYCLE_STARTED);
        }
      }
    }
    else
    {
      Dem_OperationCycle_SetPendingCycle(CycleId,
        ((CycleState == DEM_CYCLE_STATE_START)
        ? DEM_OPERATIONCYCLE_CYCLE_STARTED
        : DEM_OPERATIONCYCLE_CYCLE_STOPPED)
        );
    }

    Dem_LeaveCritical_StateManager();
    /* <<<< -------------------------------- Leave Critical Section: StateManager */
  }
}

/* ****************************************************************************
 % Dem_OperationCycle_GetCycleState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_OperationCycleStateType, DEM_CODE)
Dem_OperationCycle_GetCycleState(
  CONST(uint8, AUTOMATIC)  CycleId
  )
{
  Dem_OperationCycleStateType lReturnValue;

#if (DEM_FEATURE_NEED_OBD == STD_ON)
  if (Dem_Cfg_CycleIsObdDcy(CycleId) == TRUE)
  {
    if (DEM_OPERATIONCYCLE_TEST_DCY_QUALIFIED(Dem_OperationCycle_GetObdCycleStates()) == TRUE)
    {
      lReturnValue = DEM_CYCLE_STATE_START;
    }
    else
    {
      lReturnValue = DEM_CYCLE_STATE_END;
    }
  }
  else
#endif
  {
    if (Dem_OperationCycle_GetCurrentCycleStatus(CycleId) == DEM_OPERATIONCYCLE_CYCLE_STARTED)
    {
      lReturnValue = DEM_CYCLE_STATE_START;
    }
    else
    {
      lReturnValue = DEM_CYCLE_STATE_END;
    }
  }
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_OperationCycle_PreInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_PreInit(
  void
  )
{
  Dem_OperationCycle_CurrentCycleState = 0U;
#if (DEM_CFG_SUPPORT_RESTART_CYCLE == STD_ON)
  Dem_OperationCycle_CurrentCycleState = Dem_OperationCycle_CurrentCycleState | ((uint16)1 << Dem_Cfg_GlobalRestartCycleId());
#endif
  if (Dem_Cfg_IsObdSupportedInVariant() == TRUE)
  {
    Dem_OperationCycle_CurrentCycleState = Dem_OperationCycle_CurrentCycleState | ((uint16)1 << Dem_Cfg_GlobalObdDrivingCycleId());
  }

  Dem_OperationCycle_PendingCycleState = 0U;
  Dem_OperationCycle_CycleFlag = 0U;
  if (Dem_Cfg_IsObdSupportedInVariant() == TRUE)
  {
    Dem_OperationCycle_ClearPendingDcyCycle();
  }
}

/* ****************************************************************************
 % Dem_OperationCycle_Init
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
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_Init(
  void
  )
{
#if (DEM_CFG_SUPPORT_OPCYCLE_STORAGE == STD_ON)
  /* If operation cycle states are stored in NV, restore them */
  Dem_OperationCycle_CurrentCycleState = Dem_Cfg_AdminData.CycleState;
#endif

  if (Dem_Cfg_IsObdSupportedInVariant() == TRUE)
  {
    /* In OBD configurations, make sure the OBD DCY is in state 'started' */
    Dem_OperationCycle_CurrentCycleState = Dem_OperationCycle_CurrentCycleState | ((uint16)1 << Dem_Cfg_GlobalObdDrivingCycleId());

  /* Start the relevant cycles. */
#if (DEM_FEATURE_NEED_CYCLEAUTOMATICEND == STD_ON)
    if (Dem_OperationCycle_TestOBDDcyAutomaticRestart() == TRUE)
    { /* Driving Cycle was/is confirmed, restart driving cycle */
# if (DEM_CFG_SUPPORT_DELAY_WUC_TO_DCY == STD_ON)
      if (DEM_OPERATIONCYCLE_TEST_WARMUP_CYCLE(Dem_OperationCycle_GetObdCycleStates()) == TRUE)
      {
        Dem_OperationCycle_CycleUpdate(Dem_Cfg_GlobalWarmupCycleId(), DEM_OPERATIONCYCLE_CYCLE_RESTARTED);
      }
# endif
      Dem_OperationCycle_CycleUpdate(Dem_Cfg_GlobalObdDrivingCycleId(), DEM_OPERATIONCYCLE_CYCLE_RESTARTED);
    }
#endif /* (DEM_FEATURE_NEED_CYCLEAUTOMATICEND == STD_ON) */
  }
#if (DEM_CFG_SUPPORT_RESTART_CYCLE == STD_ON)
# if (DEM_CFG_SUPPORT_OPCYCLE_STORAGE == STD_ON)
  if (DEM_OPERATIONCYCLE_CYCLE_STARTED == Dem_OperationCycle_GetCurrentCycleStatus(Dem_Cfg_GlobalRestartCycleId()))
  {
    Dem_OperationCycle_CycleUpdate(Dem_Cfg_GlobalRestartCycleId(), DEM_OPERATIONCYCLE_CYCLE_RESTARTED);
  }
  else
# endif
  {
    Dem_OperationCycle_CycleUpdate(Dem_Cfg_GlobalRestartCycleId(), DEM_OPERATIONCYCLE_CYCLE_STARTED);
  }
#endif
  Dem_Scheduler_EnableTask(Dem_Scheduler_Task_OperationCycle);
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_OperationCycle_Shutdown
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
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_Shutdown(
  void
  )
{
#if (DEM_CFG_SUPPORT_OPCYCLE_STORAGE == STD_OFF) || (DEM_CFG_SUPPORT_OPCYCLE_AUTOMATIC_END == STD_ON)
  uint8 lCycleIndex;

# if (DEM_CFG_SUPPORT_RESTART_CYCLE == STD_ON)
  boolean lGlobalCycleStopped;
  lGlobalCycleStopped = FALSE;
# endif

  for (lCycleIndex = 0u; lCycleIndex < Dem_Cfg_GlobalCycleCount(); ++lCycleIndex)
  {
    /* Never stop the OBD_DCY */
    if (Dem_Cfg_CycleIsObdDcy(lCycleIndex) == FALSE)
    {
      if ( (DEM_OPERATIONCYCLE_CYCLE_STARTED == Dem_OperationCycle_GetCurrentCycleStatus(lCycleIndex))
        && (Dem_Cfg_CycleIsAutomaticEnd(lCycleIndex) == TRUE)                                                                    
        )
      {
# if (DEM_CFG_SUPPORT_RESTART_CYCLE == STD_ON)
        if (lCycleIndex == Dem_Cfg_GlobalRestartCycleId())
        {
          lGlobalCycleStopped = TRUE;
        }
# endif
        Dem_OperationCycle_CycleUpdate(lCycleIndex, DEM_OPERATIONCYCLE_CYCLE_STOPPED);
      }
    }
  }
#endif

  Dem_OperationCycle_UpdateCycleStatesInNvBlock();

#if (DEM_CFG_SUPPORT_OPCYCLE_STORAGE == STD_OFF) || (DEM_CFG_SUPPORT_OPCYCLE_AUTOMATIC_END == STD_ON)
# if (DEM_CFG_SUPPORT_RESTART_CYCLE == STD_ON)
  if (lGlobalCycleStopped == TRUE)
  {
  /* If it was automatically stopped during shutdown, set state of global restart cycle as "Started"
     to facilitate event reporting between demshutdown and masterinit */
    Dem_OperationCycle_CurrentCycleState =
      (uint16)(Dem_OperationCycle_CurrentCycleState | ((uint16)1U << (uint16)Dem_Cfg_GlobalRestartCycleId()));
  }
# endif
#endif

  {
    Dem_EventIdType lEventId;
    boolean lOBDDcyAutomaticRestart;

    lOBDDcyAutomaticRestart = Dem_OperationCycle_TestOBDDcyAutomaticRestart();

    for (lEventId = DEM_EVENT_FIRST; lEventId < Dem_Cfg_GlobalEventCount(); ++lEventId)
    {
      if ( ((lOBDDcyAutomaticRestart == TRUE) && (Dem_Cfg_EventOperationCycle(lEventId) == Dem_Cfg_GlobalObdDrivingCycleId()))
# if (DEM_CFG_SUPPORT_RESTART_CYCLE == STD_ON) 
          || (Dem_Cfg_EventOperationCycle(lEventId) == Dem_Cfg_GlobalRestartCycleId()) 
# endif
         )
      {
        Dem_Event_ResetEventReporting(lEventId);
      }
    } /* while (lEventId > DEM_EVENT_INVALID) */
  }

  Dem_OperationCycle_PendingCycleState = 0U;
  Dem_OperationCycle_CycleFlag = 0U;

  if (Dem_Cfg_IsObdSupportedInVariant() == TRUE)
  {
    Dem_OperationCycle_ClearPendingDcyCycle();
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_OPERATIONCYCLE_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_OperationCycle_Implementation.h
 *********************************************************************************************************************/
