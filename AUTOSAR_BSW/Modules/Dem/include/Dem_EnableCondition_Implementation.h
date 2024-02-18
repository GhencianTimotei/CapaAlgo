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
/*! \addtogroup Dem_EnableCondition
 *  \{
 *  \file       Dem_EnableCondition_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Implementation of the EnableCondition subcomponent
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_ENABLECONDITION_IMPLEMENTATION_H)
#define DEM_ENABLECONDITION_IMPLEMENTATION_H

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
#include "Dem_EnableCondition_Interface.h"

/* Includes to access public functions belonging to other (top level)/ (logical)/- units to be used by this Unit */
/* ------------------------------------------------------------------------- */
#include "Dem_Infrastructure_Interface.h"
#include "Dem_Core_Interface.h"
#include "Dem_Satellite_Interface.h"
#include "Dem_DiagnosticObserver_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*! Filename declaration */
#define DEM_ENABLECONDITION_IMPLEMENTATION_FILENAME "Dem_EnableCondition_Implementation.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DEFINITIONS
 *********************************************************************************************************************/
/* ********************************************************************************************************************
 *  SUBCOMPONENT PUBLIC PROPERTIES DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \addtogroup Dem_EnableCondition_PublicProperties
 * \{
 */

/* ****************************************************************************
 % Dem_EnableCondition_GetGlobalEnableConditionCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_EnableCondition_GetGlobalEnableConditionCount(
  void
  )
{
  return DEM_CFG_GLOBAL_ENABLE_COND_COUNT;
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
 * \defgroup Dem_EnableCondition_Private Private Methods
 * \{
 */


/* ****************************************************************************
 * Dem_EnableCondition_GetGlobalEnableConditionGroupCount
 *****************************************************************************/
/*!
 * \brief         Get the number of configured enable condition groups
 *
 * \details       Get the number of configured enable condition groups
 *
 * \return        The number of configured enable condition groups
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_EnableCondition_GetGlobalEnableConditionGroupCount(
  void
  );


/* ****************************************************************************
 * Dem_EnableCondition_GetEnableConditionInitValue
 *****************************************************************************/
/*!
 * \brief         Get the initial value of enable condition
 *
 * \details       Get the initial value of enable condition
 *
 * \param[in]     EnableCondition
 *                Unique handle of the enable condition.
 *
 * \return        TRUE
 *                The initial value of enable condition is TRUE
 * \return        FALSE
 *                The initial value of enable condition is FALSE
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EnableCondition_GetEnableConditionInitValue(
  CONST(uint8, AUTOMATIC) EnableCondition
  );


#if ((DEM_CFG_SUPPORT_ENABLE_CONDITIONS == STD_ON) || (DEM_CFG_SUPPORT_DCM == STD_ON) \
    ||((DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON) && (DEM_CFG_SUPPORT_USER_CONTROLLED_WIR_DURING_CDTCS == STD_OFF)))
/* ****************************************************************************
 * Dem_EnableCondition_GetEnableConditionActive
 *****************************************************************************/
/*!
 * \brief         Get current activation state of enable condition
 *
 * \details       Get current activation state of enable condition
 *
 * \param[in]     EnableCondition
 *                Unique handle of the enable condition
 *
 * \return        The activation state of enable condition
 *
 * \pre           -
 * \config        (DEM_CFG_SUPPORT_ENABLE_CONDITIONS == STD_ON) || (DEM_CFG_SUPPORT_DCM == STD_ON) \
 *                ||( (DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON) \
 *                    &&(DEM_CFG_SUPPORT_USER_CONTROLLED_WIR_DURING_CDTCS == STD_OFF) )
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EnableCondition_GetEnableConditionActive(
  CONST(uint8, AUTOMATIC)  EnableCondition
  );
#endif


/* ****************************************************************************
 * Dem_EnableCondition_GetEventEnableConditionGroup
 *****************************************************************************/
/*!
 * \brief         Get the enable condition group for an event
 *
 * \details       Get the enable condition group for an event
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()].
 *
 * \return        Enable condition group for the event
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_EnableCondition_GetEventEnableConditionGroup(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );


/* ****************************************************************************
 * Dem_EnableCondition_GetEnableConditionGroupState
 *****************************************************************************/
/*!
 * \brief         Get current internal state of enable condition group
 *
 * \details       Get current internal state of enable condition group
 *
 * \param[in]     EnableConditionGroup
 *                Unique handle of the enable condition group
 *
 * \return        Current activation state of the enable condition group
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_EnableCondition_GetEnableConditionGroupState(
  CONST(uint16, AUTOMATIC)  EnableConditionGroup
  );


/* ****************************************************************************
 * Dem_EnableCondition_GetEnableConditionGroupCounter
 *****************************************************************************/
/*!
 * \brief         Get current internal counter of enable condition group
 *
 * \details       Get current internal counter of enable condition group
 *
 * \param[in]     EnableConditionGroup
 *                Unique handle of the enable condition group
 *
 * \return        Current number of enable conditions currently disabling the 
 *                group.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_EnableCondition_GetEnableConditionGroupCounter(
  CONST(uint16, AUTOMATIC)  EnableConditionGroup
  );


/* ****************************************************************************
 * Dem_EnableCondition_SetEnableConditionActive
 *****************************************************************************/
/*!
 * \brief         Set current activation status of enable condition
 *
 * \details       Set current activation status of enable condition
 *
 * \param[in]     EnableConditionID
 *                Unique handle of the enable condition
 * \param[in]     ActiveStatus
 *                New activation state of the enable condition
 *
 * \pre           -
 * 
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EnableCondition_SetEnableConditionActive(
  CONST(uint8, AUTOMATIC)  EnableConditionID,
  CONST(boolean, AUTOMATIC)  ActiveStatus
  );


/* ****************************************************************************
 * Dem_EnableCondition_SetEnableConditionGroupState
 *****************************************************************************/
/*!
 * \brief         Set current internal state of enable condition group
 *
 * \details       Set current internal state of enable condition group
 *
 * \param[in]     EnableConditionGroup
 *                Unique handle of the enable condition group
 * \param[in]     State
 *                New internal state of the enable condition group
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EnableCondition_SetEnableConditionGroupState(
  CONST(uint16, AUTOMATIC)  EnableConditionGroup,
  CONST(uint8, AUTOMATIC)  State
  );


/* ****************************************************************************
 * Dem_EnableCondition_SetEnableConditionGroupCounter
 *****************************************************************************/
/*!
 * \brief         Set current internal counter of enable condition group
 *
 * \details       Set current internal counter of enable condition group
 *
 * \param[in]     EnableConditionGroup
 *                 Unique handle of the enable condition group
 * \param[in]     Counter
 *                New internal counter of the enable condition group
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EnableCondition_SetEnableConditionGroupCounter(
  CONST(uint16, AUTOMATIC)  EnableConditionGroup,
  CONST(uint8, AUTOMATIC)  Counter
  );


/* ****************************************************************************
 * Dem_EnableCondition_ProcessQueueEventEnableConditions
 *****************************************************************************/
/*!
 * \brief         Processes changes of enable condition states
 *
 * \details       This function resets or freezes debouncing of an event, based
 *                on the changes of the enable condition states since this
 *                function was called last. When the event is re-enabled, this
 *                function also calls the init monitor notifications.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EnableCondition_ProcessQueueEventEnableConditions(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );                      


/* ****************************************************************************
 * Dem_EnableCondition_GroupIterExists
 *****************************************************************************/
/*!
 * \brief         Test if the iterator points to a valid element
 *
 * \details       Test if the iterator points to a valid element
 *
 * \param[in]     IterPtr
 *                Pointer to the iterator
 * 
 * \return        TRUE
 *                Dem_EnableCondition_GroupIterGet() will return a valid element
 *                on this iterator
 * \return        FALSE
 *                Dem_EnableCondition_GroupIterGet() is undefined on this iterator
 *
 * \pre           IterPtr has been initialized
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EnableCondition_GroupIterExists(
  CONSTP2CONST(Dem_Cfg_EventEnableConditionGroupIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );


/* ****************************************************************************
 * Dem_EnableCondition_GroupIterGet
 *****************************************************************************/
/*!
 * \brief         Get the element pointed to by the iterator
 *
 * \details       Get the element pointed to by the iterator
 *
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \return        Handle to Enable condition group descriptor table
 *
 * \pre           IterPtr has been initialized
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_EnableCondition_GroupIterGet(
  CONSTP2CONST(Dem_Cfg_EventEnableConditionGroupIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );


/* ****************************************************************************
 * Dem_EnableCondition_GroupIterInit
 *****************************************************************************/
/*!
 * \brief         Init the iterator
 *
 * \details       Initializes the iterator to enumerate enable condition groups
 *                referencing given enable condition
 *
 * \param[in]     EnableConditionID
 *                Unique handle of the enable condition.
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EnableCondition_GroupIterInit(
  CONST(uint8, AUTOMATIC)  EnableConditionID,
  CONSTP2VAR(Dem_Cfg_EventEnableConditionGroupIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );


/* ****************************************************************************
 * Dem_EnableCondition_GroupIterNext
 *****************************************************************************/
/*!
 * \brief         Move the iterator to the next element
 *
 * \details       Move the iterator to the next element
 *
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \pre           IterPtr has been initialized
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EnableCondition_GroupIterNext(
  CONSTP2VAR(Dem_Cfg_EventEnableConditionGroupIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/

/* ****************************************************************************
 % Dem_EnableCondition_GetGlobalEnableConditionGroupCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_EnableCondition_GetGlobalEnableConditionGroupCount(
  void
  )
{
  return (uint8)Dem_Cfg_GetSizeOfEnableConditionGroupTable();
}

/* ****************************************************************************
 % Dem_EnableCondition_GetEnableConditionInitValue
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EnableCondition_GetEnableConditionInitValue(
  CONST(uint8, AUTOMATIC) EnableCondition
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EnableCondition)                                                                              /* PRQA S 3112 */ /* MD_DEM_14.2 */
    return Dem_Cfg_IsFulfilledAtInitOfEnableConditionInitTable(EnableCondition);
}

#if ((DEM_CFG_SUPPORT_ENABLE_CONDITIONS == STD_ON) || (DEM_CFG_SUPPORT_DCM == STD_ON) \
    ||((DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON) && (DEM_CFG_SUPPORT_USER_CONTROLLED_WIR_DURING_CDTCS == STD_OFF)))
/* ****************************************************************************
 % Dem_EnableCondition_GetEnableConditionActive
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EnableCondition_GetEnableConditionActive(
  CONST(uint8, AUTOMATIC)  EnableCondition
  )
{
  return Dem_Cfg_IsEnableConditionFulfilled(EnableCondition);
}
#endif

/* ****************************************************************************
 % Dem_EnableCondition_GetEventEnableConditionGroup
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_EnableCondition_GetEventEnableConditionGroup(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */

#if (DEM_CFG_SUPPORT_ENABLE_CONDITIONS == STD_ON)
    return (uint16)(Dem_Cfg_GetEnableConditionGroupTableIdxOfEventTable(EventId));
#else
    return (uint16)DEM_ENABLECONDITION_CONTROLDTCSETTING;
#endif
}

/* ****************************************************************************
 % Dem_EnableCondition_GetEnableConditionGroupState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_EnableCondition_GetEnableConditionGroupState(
  CONST(uint16, AUTOMATIC)  EnableConditionGroup
  )
{
  return Dem_Cfg_GetEnableConditionGroupState(EnableConditionGroup);                                                             /* PRQA S 2843 */ /* MD_DEM_Dir4.1_ReadOperation */
}

/* ****************************************************************************
 % Dem_EnableCondition_GetEnableConditionGroupCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_EnableCondition_GetEnableConditionGroupCounter(
  CONST(uint16, AUTOMATIC)  EnableConditionGroup
  )
{
  return Dem_Cfg_GetEnableConditionGroupCounter(EnableConditionGroup);
}

/* ****************************************************************************
 % Dem_EnableCondition_SetEnableConditionActive
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EnableCondition_SetEnableConditionActive(
  CONST(uint8, AUTOMATIC)  EnableConditionID,
  CONST(boolean, AUTOMATIC)  ActiveStatus
  )
{
#if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (EnableConditionID >= Dem_Cfg_GetSizeOfEnableConditionFulfilled())
  {
    Dem_Error_RunTimeCheckFailed(DEM_ENABLECONDITION_IMPLEMENTATION_FILENAME, __LINE__);                                         /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
#endif
  {
    Dem_Cfg_SetEnableConditionFulfilled(EnableConditionID, ActiveStatus);                                                        /* SBSW_DEM_ARRAY_WRITE_ENABLECONDITIONFULFILLED */
  }
}

/* ****************************************************************************
 % Dem_EnableCondition_SetEnableConditionGroupState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EnableCondition_SetEnableConditionGroupState(
  CONST(uint16, AUTOMATIC)  EnableConditionGroup,
  CONST(uint8, AUTOMATIC)  State
  )
{
#if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (EnableConditionGroup >= Dem_Cfg_GetSizeOfEnableConditionGroupState())
  {
    Dem_Error_RunTimeCheckFailed(DEM_ENABLECONDITION_IMPLEMENTATION_FILENAME, __LINE__);                                         /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
#endif
  {
    Dem_Cfg_SetEnableConditionGroupState(EnableConditionGroup, State);                                                           /* SBSW_DEM_ARRAY_WRITE_ENABLECONDITIONGROUPSTATE */
  }
}

/* ****************************************************************************
 % Dem_EnableCondition_SetEnableConditionGroupCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EnableCondition_SetEnableConditionGroupCounter(
  CONST(uint16, AUTOMATIC)  EnableConditionGroup,
  CONST(uint8, AUTOMATIC)  Counter
  )
{
#if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (EnableConditionGroup >= Dem_Cfg_GetSizeOfEnableConditionGroupCounter())
  {
    Dem_Error_RunTimeCheckFailed(DEM_ENABLECONDITION_IMPLEMENTATION_FILENAME, __LINE__);                                         /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
#endif
  {
    Dem_Cfg_SetEnableConditionGroupCounter(EnableConditionGroup, Counter);                                                       /* SBSW_DEM_ARRAY_WRITE_ENABLECONDITIONGROUPCOUNTER */
  }
}

/* ****************************************************************************
 % Dem_EnableCondition_ProcessQueueEventEnableConditions
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
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EnableCondition_ProcessQueueEventEnableConditions(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  uint16 lEnableConditionGroup;
  uint8 lGroupState;

  lEnableConditionGroup = Dem_EnableCondition_GetEventEnableConditionGroup(EventId);
  lGroupState = Dem_EnableCondition_GetEnableConditionGroupState(lEnableConditionGroup);

  /* Reset/Freeze debouncing on enable condition state change unlocked -> locked */
  if (DEM_ENABLECONDITION_TEST_ENABLECONDITIONGROUP_PROCESS_DISABLE(lGroupState))
  {
    if (Dem_EnableCondition_GetEnableConditionGroupCounter(lEnableConditionGroup) == 1u)
    {
      /* Enable conditions become disabled.
       * If DEM_CFG_RESET_DEBOUNCE_ON_ENABLE_ENABLE_CONDITIONS:
       * If the event is configured to freeze and not continue, or will not continue counting at all: freeze it
       * If DEM_CFG_RESET_DEBOUNCE_ON_DISABLE_ENABLE_CONDITIONS:
       * If the event is configured to freeze: freeze it
       * Otherwise: reset it
       */
#if (DEM_CFG_RESET_DEBOUNCE_ON_ENABLE_ENABLE_CONDITIONS == STD_ON)
      if (Dem_Cfg_EventDebounceContinuous(EventId) == FALSE)
      {
        Dem_SatelliteCore_FreezeDebounceStatus(
          Dem_Cfg_EventSatelliteId(EventId),
          Dem_Cfg_EventSatelliteEventId(EventId));
      }
#endif
#if (DEM_CFG_RESET_DEBOUNCE_ON_DISABLE_ENABLE_CONDITIONS == STD_ON)
      if (Dem_Cfg_EventDebounceReset(EventId) == FALSE)
      {
        Dem_SatelliteCore_FreezeDebounceStatus(
          Dem_Cfg_EventSatelliteId(EventId),
          Dem_Cfg_EventSatelliteEventId(EventId));
      }
      else
      {
        Dem_SatelliteCore_ResetDebounceStatus(
          Dem_Cfg_EventSatelliteId(EventId),
          Dem_Cfg_EventSatelliteEventId(EventId));

      }
#endif
    }
  }


#if ( (DEM_CFG_NOTIFY_ENABLECONDITION == STD_ON) \
   || (DEM_CFG_RESET_DEBOUNCE_ON_ENABLE_ENABLE_CONDITIONS == STD_ON) )
  if (DEM_ENABLECONDITION_TEST_ENABLECONDITIONGROUP_PROCESS_ENABLE(lGroupState))
  {
    if (Dem_EnableCondition_GetEnableConditionGroupCounter(lEnableConditionGroup) == 0u)
    {
      /* 
       * If the event is configured to reset, and the global setting is to reset on enable EC:
       *   -Reset the debouncing
       * If the event is configured to freeze, and the global setting is to freeze on enable EC:
       *   -Freeze the debouncing
       * Call InitMonitor for event/function:
       * If any are configured
       */
# if (DEM_CFG_RESET_DEBOUNCE_ON_ENABLE_ENABLE_CONDITIONS == STD_ON)
      if (Dem_Cfg_EventDebounceReset(EventId) == TRUE)
      {
        Dem_SatelliteCore_ResetDebounceStatus(
          Dem_Cfg_EventSatelliteId(EventId),
          Dem_Cfg_EventSatelliteEventId(EventId));
      }
      else
      {
        if(Dem_Cfg_EventDebounceContinuous(EventId) == TRUE)
        {
          Dem_SatelliteCore_FreezeDebounceStatus(
          Dem_Cfg_EventSatelliteId(EventId),
          Dem_Cfg_EventSatelliteEventId(EventId));
        }
      }
# endif
      Dem_Notifications_InitMonitorForEvent(EventId, DEM_INIT_MONITOR_REENABLED);
      Dem_Notifications_InitMonitorForFunction(EventId);
    }
  }
#endif
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */


/* ****************************************************************************
 % Dem_EnableCondition_GroupIterExists
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EnableCondition_GroupIterExists(
  CONSTP2CONST(Dem_Cfg_EventEnableConditionGroupIterType, AUTOMATIC, AUTOMATIC) IterPtr                                          /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  return (boolean)(IterPtr->mIdx < IterPtr->mEndIdx);
}


/* ****************************************************************************
 % Dem_EnableCondition_GroupIterGet
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_EnableCondition_GroupIterGet(
  CONSTP2CONST(Dem_Cfg_EventEnableConditionGroupIterType, AUTOMATIC, AUTOMATIC) IterPtr                                          /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return Dem_Cfg_GetEnableConditionGroupTableInd(IterPtr->mIdx);
}

/* ****************************************************************************
 % Dem_EnableCondition_GroupIterInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EnableCondition_GroupIterInit(
  CONST(uint8, AUTOMATIC)  EnableConditionID,                                                                                    /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONSTP2VAR(Dem_Cfg_EventEnableConditionGroupIterType, AUTOMATIC, AUTOMATIC) IterPtr                                            /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_8.13_fp */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EnableConditionID)                                                                            /* PRQA S 3112 */ /* MD_DEM_14.2 */
  IterPtr->mIdx = Dem_Cfg_GetEnableConditionGroupTableIndStartIdxOfEnableConditionTable(EnableConditionID);                      /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  IterPtr->mEndIdx = Dem_Cfg_GetEnableConditionGroupTableIndEndIdxOfEnableConditionTable(EnableConditionID);                     /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}

/* ****************************************************************************
 % Dem_EnableCondition_GroupIterNext
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EnableCondition_GroupIterNext(
  CONSTP2VAR(Dem_Cfg_EventEnableConditionGroupIterType, AUTOMATIC, AUTOMATIC) IterPtr                                            /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_8.13_fp */
  )
{
  IterPtr->mIdx += 1u;                                                                                                          /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
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
 * \addtogroup Dem_EnableCondition_Public
 * \{
 */

#if (DEM_CFG_SUPPORT_ENABLE_CONDITIONS == STD_ON) || (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_EnableCondition_SetEnableConditionFulfilled
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
  Dem_EnableCondition_SetEnableConditionFulfilled(
  CONST(uint8, AUTOMATIC)  EnableConditionID
  )
{
  boolean lEnableConditionGroupStatePending;

  lEnableConditionGroupStatePending = FALSE;

  /* >>>> -------------------------------- Enter Critical Section: StateManager */
  Dem_EnterCritical_StateManager();

  if (Dem_EnableCondition_GetEnableConditionActive(EnableConditionID) == FALSE)
  {
    Dem_Cfg_EventEnableConditionGroupIterType lEnableConditionIter;
    for (Dem_EnableCondition_GroupIterInit(EnableConditionID, &lEnableConditionIter);                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_EnableCondition_GroupIterExists(&lEnableConditionIter) == TRUE;                                                     /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_EnableCondition_GroupIterNext(&lEnableConditionIter))                                                               /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      uint16 lEnableConditionGroup;
      uint8 lGroupState;

      lEnableConditionGroup = Dem_EnableCondition_GroupIterGet(&lEnableConditionIter);                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
      if (Dem_EnableCondition_GetEnableConditionGroupCounter(lEnableConditionGroup) > 0u)
# endif
      {
        Dem_EnableCondition_SetEnableConditionGroupCounter(lEnableConditionGroup,
          (uint8)(Dem_EnableCondition_GetEnableConditionGroupCounter(lEnableConditionGroup) - 1u));
      }

      lGroupState = Dem_EnableCondition_GetEnableConditionGroupState(lEnableConditionGroup);
      lGroupState = DEM_ENABLECONDITION_SET_ENABLECONDITIONGROUP_QUEUE_ENABLE(lGroupState);
      Dem_EnableCondition_SetEnableConditionGroupState(lEnableConditionGroup, lGroupState);
      lEnableConditionGroupStatePending = TRUE;
    }
    Dem_EnableCondition_SetEnableConditionActive(EnableConditionID, TRUE);
  }

  Dem_LeaveCritical_StateManager();
  /* <<<< -------------------------------- Leave Critical Section: StateManager */

  if (lEnableConditionGroupStatePending == TRUE)
  {
    Dem_Scheduler_EnableTaskOnce(Dem_Scheduler_Task_EnableCondition);
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_CFG_SUPPORT_ENABLE_CONDITIONS == STD_ON) || (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_EnableCondition_ResetEnableConditionFulfilled
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
Dem_EnableCondition_ResetEnableConditionFulfilled(
  CONST(uint8, AUTOMATIC)  EnableConditionID
  )
{
  boolean lEnableConditionGroupStatePending;

  lEnableConditionGroupStatePending = FALSE;

  /* >>>> -------------------------------- Enter Critical Section: StateManager */
  Dem_EnterCritical_StateManager();

  if (Dem_EnableCondition_GetEnableConditionActive(EnableConditionID) == TRUE)
  {
    Dem_Cfg_EventEnableConditionGroupIterType lEnableConditionIter;
    for (Dem_EnableCondition_GroupIterInit(EnableConditionID, &lEnableConditionIter);                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
      Dem_EnableCondition_GroupIterExists(&lEnableConditionIter) == TRUE;                                                        /* SBSW_DEM_CALL_ITERATOR_POINTER */
      Dem_EnableCondition_GroupIterNext(&lEnableConditionIter))                                                                  /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      uint16 lEnableConditionGroup;
      uint8 lGroupState;

      lEnableConditionGroup = Dem_EnableCondition_GroupIterGet(&lEnableConditionIter);                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
      Dem_EnableCondition_SetEnableConditionGroupCounter(lEnableConditionGroup, 
        (uint8)(Dem_EnableCondition_GetEnableConditionGroupCounter(lEnableConditionGroup) + 1u));

      lGroupState = Dem_EnableCondition_GetEnableConditionGroupState(lEnableConditionGroup);
      lGroupState = DEM_ENABLECONDITION_RESET_ENABLECONDITIONGROUP_ACTIVE(lGroupState);
      lGroupState = DEM_ENABLECONDITION_SET_ENABLECONDITIONGROUP_QUEUE_DISABLE(lGroupState);
      lGroupState = DEM_ENABLECONDITION_RESET_ENABLECONDITIONGROUP_QUEUE_ENABLE(lGroupState);
      Dem_EnableCondition_SetEnableConditionGroupState(lEnableConditionGroup, lGroupState);

      lEnableConditionGroupStatePending = TRUE;
    }
    Dem_EnableCondition_SetEnableConditionActive(EnableConditionID, FALSE);
  }

  Dem_LeaveCritical_StateManager();
  /* <<<< -------------------------------- Leave Critical Section: StateManager */

  if (lEnableConditionGroupStatePending == TRUE)
  {
    Dem_Scheduler_EnableTaskOnce(Dem_Scheduler_Task_EnableCondition);
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

/* ****************************************************************************
 % Dem_EnableCondition_MainFunction
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
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EnableCondition_MainFunction(
  void
  )
{
  Dem_EventIdType lEventId;
  uint8 lEnableConditionGroup;

  /* >>>> -------------------------------- Enter Critical Section: StateManager */
  Dem_EnterCritical_StateManager();

  for (lEnableConditionGroup = 0u; 
       lEnableConditionGroup < Dem_EnableCondition_GetGlobalEnableConditionGroupCount();
       ++lEnableConditionGroup)
  {
    uint8 lGroupState;
    lGroupState = Dem_EnableCondition_GetEnableConditionGroupState(lEnableConditionGroup);
    if (DEM_ENABLECONDITION_TEST_ENABLECONDITIONGROUP_QUEUE_DISABLE(lGroupState))
    {
      lGroupState = DEM_ENABLECONDITION_SET_ENABLECONDITIONGROUP_PROCESS_DISABLE(lGroupState);
      lGroupState = DEM_ENABLECONDITION_RESET_ENABLECONDITIONGROUP_QUEUE_DISABLE(lGroupState);
    }
    if (DEM_ENABLECONDITION_TEST_ENABLECONDITIONGROUP_QUEUE_ENABLE(lGroupState))
    {
      lGroupState = DEM_ENABLECONDITION_SET_ENABLECONDITIONGROUP_PROCESS_ENABLE(lGroupState);
      lGroupState = DEM_ENABLECONDITION_RESET_ENABLECONDITIONGROUP_QUEUE_ENABLE(lGroupState);
    }
    Dem_EnableCondition_SetEnableConditionGroupState(lEnableConditionGroup, lGroupState);
  }

  Dem_LeaveCritical_StateManager();
  /* <<<< -------------------------------- Leave Critical Section: StateManager */

  for (lEventId = DEM_EVENT_FIRST; lEventId < Dem_Cfg_GlobalEventCount(); ++lEventId)
  {
    if (Dem_Cfg_EventAvailableByVariant(lEventId) == TRUE)
    {
      if (Dem_EventInternalStatus_TestEventDisconnected(Dem_Event_GetInternalStatus(lEventId)) == FALSE)
      {
        /* Process enable condition groups for every event */
        Dem_EnableCondition_ProcessQueueEventEnableConditions(lEventId);
      }
    }
  }

  /* >>>> -------------------------------- Enter Critical Section: StateManager */
  Dem_EnterCritical_StateManager();

  /* Remove process flags from group state of all enable condition groups */
  for (lEnableConditionGroup = 0u; 
       lEnableConditionGroup < Dem_EnableCondition_GetGlobalEnableConditionGroupCount(); 
       ++lEnableConditionGroup)
  {
    uint8 lGroupState;
    lGroupState = Dem_EnableCondition_GetEnableConditionGroupState(lEnableConditionGroup);
    if (DEM_ENABLECONDITION_TEST_ENABLECONDITIONGROUP_PROCESS_ENABLE(lGroupState))
    {
      if (Dem_EnableCondition_GetEnableConditionGroupCounter(lEnableConditionGroup) == 0u)
      {
        lGroupState = DEM_ENABLECONDITION_SET_ENABLECONDITIONGROUP_ACTIVE(lGroupState);
      }
    }
    lGroupState = DEM_ENABLECONDITION_RESET_ENABLECONDITIONGROUP_PROCESS_DISABLE(lGroupState);
    lGroupState = DEM_ENABLECONDITION_RESET_ENABLECONDITIONGROUP_PROCESS_ENABLE(lGroupState);
    Dem_EnableCondition_SetEnableConditionGroupState(lEnableConditionGroup, lGroupState);
  }

  Dem_LeaveCritical_StateManager();
  /* <<<< -------------------------------- Leave Critical Section: StateManager */
}                                                                                                                                /* PRQA S 6080, 6050 */ /* MD_MSR_STMIF, MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_EnableCondition_Init
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EnableCondition_Init(
  void
  )
{
  uint8 lGroupState;
  uint8 lEnableCondition;
  /* Initialize enable condition group counter and set enable condition group state active */
  Dem_MemSet((Dem_DataPtrType)&Dem_Cfg_GetEnableConditionGroupCounter(0),                                                        /* PRQA S 0310, 0312, 0602 */ /* MD_DEM_11.4_cpy, MD_DEM_11.8, MD_DEM_20.2 */ /* SBSW_DEM_MEMSET_ENABLECONDITIONGROUPCOUNTER */
    0,
    Dem_Cfg_GetSizeOfEnableConditionGroupCounter() * sizeof(Dem_Cfg_GetEnableConditionGroupCounter(0)));

  lGroupState = 0u;
  lGroupState = DEM_ENABLECONDITION_SET_ENABLECONDITIONGROUP_ACTIVE(lGroupState);

  Dem_MemSet((Dem_DataPtrType)&Dem_Cfg_GetEnableConditionGroupState(0),                                                          /* PRQA S 0310, 0312, 0602 */ /* MD_DEM_11.4_cpy, MD_DEM_11.8, MD_DEM_20.2 */ /* SBSW_DEM_MEMSET_ENABLECONDITIONGROUPSTATE */
    lGroupState,
    Dem_Cfg_GetSizeOfEnableConditionGroupState() * sizeof(Dem_Cfg_GetEnableConditionGroupState(0)));

  for (lEnableCondition = 0u; 
       lEnableCondition < Dem_EnableCondition_GetGlobalEnableConditionCount();
       ++lEnableCondition)
  {
    boolean lEnableConditionInitState;
    Dem_Cfg_EventEnableConditionGroupIterType lEnableConditionIter;

    lEnableConditionInitState = Dem_EnableCondition_GetEnableConditionInitValue(lEnableCondition);

    if (lEnableConditionInitState == FALSE)
    {
      for (Dem_EnableCondition_GroupIterInit(lEnableCondition, &lEnableConditionIter);                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
        Dem_EnableCondition_GroupIterExists(&lEnableConditionIter) == TRUE;                                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
        Dem_EnableCondition_GroupIterNext(&lEnableConditionIter))                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
      {
        uint16 lEnableConditionGroup;

        lEnableConditionGroup = Dem_EnableCondition_GroupIterGet(&lEnableConditionIter);                                         /* SBSW_DEM_CALL_ITERATOR_POINTER */
        Dem_EnableCondition_SetEnableConditionGroupCounter(lEnableConditionGroup, 
          (uint8)(Dem_EnableCondition_GetEnableConditionGroupCounter(lEnableConditionGroup) + 1u));

        lGroupState = DEM_ENABLECONDITION_RESET_ENABLECONDITIONGROUP_ACTIVE
                      (Dem_EnableCondition_GetEnableConditionGroupState(lEnableConditionGroup));
        Dem_EnableCondition_SetEnableConditionGroupState(lEnableConditionGroup, lGroupState);
      }
    }
    Dem_EnableCondition_SetEnableConditionActive(lEnableCondition, lEnableConditionInitState);
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_EnableCondition_PreInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EnableCondition_PreInit(
  void
  )
{
  uint8 lGroupState;
  uint8 lEnableCondition;

  /* Initialize enable and storage conditions (all enabled due to init phase) */
  for (lEnableCondition = 0u;
    lEnableCondition < Dem_Cfg_GetSizeOfEnableConditionFulfilled();
    ++lEnableCondition)
  {
    Dem_EnableCondition_SetEnableConditionActive(lEnableCondition, TRUE);
  }
  
  Dem_MemSet((Dem_DataPtrType)&Dem_Cfg_GetEnableConditionGroupCounter(0),                                                        /* PRQA S 0310, 0312, 0602, 4404 */ /* MD_DEM_11.4_cpy, MD_DEM_11.8, MD_DEM_20.2, MD_MSR_AutosarBoolean */ /* SBSW_DEM_MEMSET_ENABLECONDITIONGROUPCOUNTER */
    FALSE,
    Dem_Cfg_GetSizeOfEnableConditionGroupCounter()*sizeof(Dem_Cfg_GetEnableConditionGroupCounter(0)));

  lGroupState = 0u;
  lGroupState = DEM_ENABLECONDITION_SET_ENABLECONDITIONGROUP_ACTIVE(lGroupState);

  Dem_MemSet((Dem_DataPtrType)&Dem_Cfg_GetEnableConditionGroupState(0),                                                          /* PRQA S 0310, 0312, 0602 */ /* MD_DEM_11.4_cpy, MD_DEM_11.8, MD_DEM_20.2 */ /* SBSW_DEM_MEMSET_ENABLECONDITIONGROUPSTATE */
    lGroupState,
    Dem_Cfg_GetSizeOfEnableConditionGroupState()*sizeof(Dem_Cfg_GetEnableConditionGroupState(0)));
} 

/* ****************************************************************************
 % Dem_EnableCondition_TestEventEnableConditionsFulfilled
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EnableCondition_TestEventEnableConditionsFulfilled(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  uint16 lEnableConditionGroup;
  uint8 lGroupState;

  lEnableConditionGroup = Dem_EnableCondition_GetEventEnableConditionGroup(EventId);
  lGroupState = Dem_EnableCondition_GetEnableConditionGroupState(lEnableConditionGroup);

  return (boolean)DEM_ENABLECONDITION_TEST_ENABLECONDITIONGROUP_ACTIVE(lGroupState);
}                                                                                                                              

#if ((DEM_CFG_SUPPORT_ENABLE_CONDITIONS == STD_ON) \
     ||((DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON) && (DEM_CFG_SUPPORT_USER_CONTROLLED_WIR_DURING_CDTCS == STD_OFF)))
/* ****************************************************************************
 % Dem_EnableCondition_TestEnableConditionFulfilled
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
  Dem_EnableCondition_TestEnableConditionFulfilled(
  CONST(uint8, AUTOMATIC)  EnableCondition
  )
{
  return Dem_EnableCondition_GetEnableConditionActive(EnableCondition);
}
#endif

#if (DEM_CFG_SUPPORT_ENABLE_CONDITIONS == STD_ON)
/* ****************************************************************************
 % Dem_EnableCondition_TestEventProcessingPrecondition
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EnableCondition_TestEventProcessingPrecondition(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  uint16 lEnableConditionGroup;
  uint8 lCounter;
  boolean ConditionFulfilled;

  ConditionFulfilled = FALSE;
  lEnableConditionGroup = Dem_EnableCondition_GetEventEnableConditionGroup(EventId);
  lCounter = Dem_EnableCondition_GetEnableConditionGroupCounter(lEnableConditionGroup);

  /* all enable conditions fulfilled*/
  if (lCounter == 0u)
  {
    ConditionFulfilled = TRUE;
  }
  /* all enable conditions fulfilled except of ControlDTCSetting */
  else if ((Dem_EnableCondition_TestEnableConditionFulfilled(DEM_ENABLECONDITION_CONTROLDTCSETTING) == FALSE)
            && (lCounter == 1u))
  {
    ConditionFulfilled = TRUE;
  }
  else
  {
     /* MISRA */
  }

  return ConditionFulfilled;
}
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */


#endif /* DEM_ENABLECONDITION_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_EnableCondition_Implementation.h
 *********************************************************************************************************************/
