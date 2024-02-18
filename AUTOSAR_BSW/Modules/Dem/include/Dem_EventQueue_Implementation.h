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
/*! \addtogroup Dem_EventQueue
 *  \{
 *  \file       Dem_EventQueue_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Implementation of EventQueue subcomponent
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_EVENTQUEUE_IMPLEMENTATION_H)
#define DEM_EVENTQUEUE_IMPLEMENTATION_H

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
#include "Dem_EventQueue_Interface.h"

/* Includes to access public functions belonging to other (top level)/ (logical)/- units to be used by this Unit */
/* ------------------------------------------------------------------------- */
#include "Dem_Core_Interface.h"
#include "Dem_FaultMemory_Interface.h"
#include "Dem_DiagnosticObserver_Interface.h"
#include "Dem_Satellite_Interface.h"
#include "Dem_Infrastructure_Interface.h"
#include "Dem_Scheduler_Interface.h"
#include "Dem_Nvm_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*! Filename declaration */
#define DEM_EVENTQUEUE_IMPLEMENTATION_FILENAME "Dem_EventQueue_Implementation.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DEFINITIONS
 *********************************************************************************************************************/
/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE PROPERTIES DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_EventQueue_PrivateProperties Private Properties
 * \{
 */
/* ****************************************************************************
 * Dem_EventQueue_TestSimilarConditionStatusChanged
 *****************************************************************************/
/*!
 * \brief         Test if 'similar condition status changed' is set in the
 *                queue status.
 *
 * \details       Test if 'similar condition status changed' is set in the
 *                queue status.
 *
 * \param[in]     QueueStatus
 *                Queue status byte
 *
 * \return        TRUE
 *                Flag is set
 * \return        FALSE
 *                Flag is not set
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EventQueue_TestSimilarConditionStatusChanged(
  CONST(Dem_EventQueue_StatusType, AUTOMATIC)  QueueStatus
  );


/* ****************************************************************************
 * Dem_EventQueue_ResetSimilarConditionStatusChanged
 *****************************************************************************/
/*!
 * \brief         Reset 'similar condition status changed' in the queue status
 *
 * \details       Reset flag 'similar condition status changed' in the queue 
 *                status
 *
 * \param[in]     QueueStatus
 *                Queue status byte
 *
 * \return        Queue status without flag set.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventQueue_StatusType, DEM_CODE)
Dem_EventQueue_ResetSimilarConditionStatusChanged(
  CONST(Dem_EventQueue_StatusType, AUTOMATIC)  QueueStatus
  );


/* ****************************************************************************
 * Dem_EventQueue_TestFdcTripStatus
 *****************************************************************************/
/*!
 * \brief         Test if event fdc trip is set in the queue status.
 *
 * \details       Test if event fdc trip is set in the queue status.
 *
 * \param[in]     QueueStatus
 *                Queue status byte
 *
 * \return        TRUE
 *                Flag is set
 * \return        FALSE
 *                Flag is not set
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EventQueue_TestFdcTripStatus(
  CONST(Dem_EventQueue_StatusType, AUTOMATIC) QueueStatus
  );


/* ****************************************************************************
 * Dem_EventQueue_TestFdcMaxSLCStatus
 *****************************************************************************/
/*!
 * \brief         Test if 'event fdc maximum exceeded' is set in the queue status.
 *
 * \details       Test if 'event fdc maximum exceeded' is set in the queue status.
 *
 * \param[in]     QueueStatus
 *                Queue status byte
 *
 * \return        TRUE
 *                Flag is set
 * \return        FALSE
 *                Flag is not set
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EventQueue_TestFdcMaxSLCStatus(
  CONST(Dem_EventQueue_StatusType, AUTOMATIC) QueueStatus
  );


/* ****************************************************************************
 * Dem_EventQueue_TestFdcProcessingStatus
 *****************************************************************************/
/*!
 * \brief         Test if 'event fdc maximum exceeded' is set in the queue status.
 *
 * \details       Test if 'event fdc maximum exceeded' is set in the queue status.
 *
 * \param[in]     QueueStatus
 *                Queue status byte
 *
 * \return        TRUE
 *                Flag is set
 * \return        FALSE
 *                Flag is not set
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EventQueue_TestFdcProcessingStatus(
CONST(Dem_EventQueue_StatusType, AUTOMATIC) QueueStatus
);


/* ****************************************************************************
 * Dem_EventQueue_TestResetTestFailedRequested
 *****************************************************************************/
/*!
 * \brief         Test if 'ResetTestFailedRequested' is set in the queue status.
 *
 * \details       Test if 'ResetTestFailedRequested' is set in the queue status.
 *
 * \param[in]     QueueStatus
 *                Queue status byte
 *
 * \return        TRUE
 *                Flag is set
 * \return        FALSE
 *                Flag is not set
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EventQueue_TestResetTestFailedRequested(
CONST(Dem_EventQueue_StatusType, AUTOMATIC) QueueStatus
);


/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE PROPERTIES DEFINITIONS
 *********************************************************************************************************************/


/* ****************************************************************************
 % Dem_EventQueue_TestSimilarConditionStatusChanged
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EventQueue_TestSimilarConditionStatusChanged(                                                                                /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_EventQueue_StatusType, AUTOMATIC)  QueueStatus
  )
{
  boolean lReturn;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(QueueStatus)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_SUPPORT_SIMILAR_CONDITIONS == STD_ON)
  if(Dem_Cfg_IsObdSupportedInVariant() == TRUE)
  {
    lReturn = (boolean)((QueueStatus & DEM_EVENTQUEUE_SIMILAR_CONDITIONS) != 0u);
  }
  else
#endif
  {
    lReturn = FALSE;
  }
  return lReturn;
}


/* ****************************************************************************
 % Dem_EventQueue_ResetSimilarConditionStatusChanged
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventQueue_StatusType, DEM_CODE)
Dem_EventQueue_ResetSimilarConditionStatusChanged(                                                                               /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_EventQueue_StatusType, AUTOMATIC)  QueueStatus
  )
{
  return (Dem_EventQueue_StatusType)(QueueStatus & DEM_EVENTQUEUE_SIMILAR_CONDITIONS_MASK);
}


/* ****************************************************************************
 % Dem_EventQueue_TestFdcTripStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EventQueue_TestFdcTripStatus(                                                                                                /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_EventQueue_StatusType, AUTOMATIC)  QueueStatus                                                                       /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  return (boolean)((QueueStatus & DEM_EVENTQUEUE_FDC_TRIP) != 0u);
}


/* ****************************************************************************
 % Dem_EventQueue_TestFdcMaxSLCStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EventQueue_TestFdcMaxSLCStatus(                                                                                              /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_EventQueue_StatusType, AUTOMATIC)  QueueStatus                                                                       /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
#if (DEM_CFG_DATA_MAX_FDC_SINCE_LAST_CLEAR == STD_ON)
  return (boolean)((QueueStatus & DEM_EVENTQUEUE_FDC_MAX_SLC) != 0u);
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(QueueStatus)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return FALSE;
#endif
}


/* ****************************************************************************
 % Dem_EventQueue_TestFdcProcessingStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EventQueue_TestFdcProcessingStatus(
  CONST(Dem_EventQueue_StatusType, AUTOMATIC)  QueueStatus                                                                       /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(QueueStatus)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_FEATURE_NEED_FDC_TRIP == STD_ON)
  return (boolean)((QueueStatus & DEM_EVENTQUEUE_FDC_PROCESSING) != 0u);
#else
  return FALSE;
#endif
}


/* ****************************************************************************
 % Dem_EventQueue_TestResetTestFailedRequested
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EventQueue_TestResetTestFailedRequested(
  CONST(Dem_EventQueue_StatusType, AUTOMATIC)  QueueStatus                                                                       /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  return (boolean)((QueueStatus & DEM_EVENTQUEUE_RESET_TESTFAILED) != 0u);
}
/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/* ********************************************************************************************************************
 *  SUBCOMPONENT PUBLIC PROPERTIES DEFINITIONS
 *********************************************************************************************************************/

#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \addtogroup Dem_EventQueue_PublicProperties
 * \{
 */


/* ****************************************************************************
 % Dem_EventQueue_GetInitialQueueStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventQueue_StatusType, DEM_CODE)
Dem_EventQueue_GetInitialQueueStatus(void)
{
  return DEM_EVENTQUEUE_STATE_INITIAL;
}

/* ****************************************************************************
 % Dem_EventQueue_SetSimilarConditionStatusChanged
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventQueue_StatusType, DEM_CODE)
Dem_EventQueue_SetSimilarConditionStatusChanged(                                                                                 /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_EventQueue_StatusType, AUTOMATIC)  QueueStatus
  )
{
  return (Dem_EventQueue_StatusType)(QueueStatus | DEM_EVENTQUEUE_SIMILAR_CONDITIONS);
}

/* ****************************************************************************
 % Dem_EventQueue_SetFdcTripStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventQueue_StatusType, DEM_CODE)
Dem_EventQueue_SetFdcTripStatus(
  CONST(Dem_EventQueue_StatusType, AUTOMATIC)  QueueStatus
  )
{
  return (Dem_EventQueue_StatusType)(QueueStatus | DEM_EVENTQUEUE_FDC_TRIP);
}

/* ****************************************************************************
 % Dem_EventQueue_SetFdcMaxSLCStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventQueue_StatusType, DEM_CODE)
Dem_EventQueue_SetFdcMaxSLCStatus(
  CONST(Dem_EventQueue_StatusType, AUTOMATIC)  QueueStatus
  )
{
  return (Dem_EventQueue_StatusType)(QueueStatus | DEM_EVENTQUEUE_FDC_MAX_SLC);
}

/* ****************************************************************************
 % Dem_EventQueue_SetFdcProcessingStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventQueue_StatusType, DEM_CODE)
Dem_EventQueue_SetFdcProcessingStatus(
  CONST(Dem_EventQueue_StatusType, AUTOMATIC)  QueueStatus
  )
{
  return (Dem_EventQueue_StatusType)(QueueStatus | DEM_EVENTQUEUE_FDC_PROCESSING);
}

/* ****************************************************************************
 % Dem_EventQueue_SetResetTestFailedRequested
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventQueue_StatusType, DEM_CODE)
Dem_EventQueue_SetResetTestFailedRequested(
  CONST(Dem_EventQueue_StatusType, AUTOMATIC)  QueueStatus
  )
{
  return (Dem_EventQueue_StatusType)(QueueStatus | DEM_EVENTQUEUE_RESET_TESTFAILED);
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
 * \defgroup Dem_EventQueue_Private Private Methods
 * \{
 */


/* ****************************************************************************
 * Dem_EventQueue_GetQueueAction
 *****************************************************************************/
/*!
 * \brief         Get the queue action from a queue status container.
 *
 * \details       Get the queue action from a queue status container.
 *
 * \param[in]     QueueStatus
 *                Queue status data value
 *
 * \return        Queue action element stored in the queue status data
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_EventQueue_GetQueueAction(
  CONST(Dem_EventQueue_StatusType, AUTOMATIC) QueueStatus
  );


/* ****************************************************************************
 * Dem_EventQueue_SetQueueAction
 *****************************************************************************/
/*!
 * \brief         Set the queue action in a queue status container.
 *
 * \details       Set the queue action in a queue status container.
 *
 * \param[in]     QueueStatus
 *                Queue status data value
 * \param[in]     Action
 *                Queue action to set
 *
 * \return        Queue status with new queue action
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventQueue_StatusType, DEM_CODE)
Dem_EventQueue_SetQueueAction(
  CONST(Dem_EventQueue_StatusType, AUTOMATIC) QueueStatus,
  CONST(uint8, AUTOMATIC) Action
  );


/* ****************************************************************************
 * Dem_EventQueueCore_ProcessQueuedEventActions
 *****************************************************************************/
/*!
 * \brief         Processes events queued with the QUEUED mechanism.
 *
 * \details       This function decodes the sequence of event reports stored
 *                for the given event, and calls the respective event processor
 *                functions, selecting the QUEUED processor variant to also
 *                handle transitions of asynchronous bit.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     QueueStatus
 *                Queued state of the event
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EventQueueCore_ProcessQueuedEventActions(
  CONST(Dem_EventQueue_StatusType, AUTOMATIC)  QueueStatus,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );


/* ****************************************************************************
 * Dem_EventQueue_ProcessEventQueuedEventActions
 *****************************************************************************/
/*!
 * \brief         Processes the queued actions of an event.
 *
 * \details       This function unqueues an event and calls the appropriate 
 *                processor.
 *
 * \param[in]     QueueStatus
 *                Queued state of the event
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
Dem_EventQueue_ProcessEventQueuedEventActions(
  CONST(Dem_EventQueue_StatusType, AUTOMATIC)  QueueStatus,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );


/* ****************************************************************************
 * Dem_EventQueue_ProcessSatelliteSimilarCondition
 *****************************************************************************/
/*!
 * \brief         Synchronize similar condition state between satellite and master.
 *
 * \details       Synchronize similar condition state between satellite and master.
 *
 * \param[in]     QueueStatus
 *                Current queued state of the event
 * \param[in]     SatelliteId
 *                Unique handle of the Satellite.
 *                The SatelliteId must be in range [1..Dem_Cfg_GlobalSatelliteCount()[.
 * \param[in]     MonitorId
 *                Satellite specific Event Id whose similar condition flag is to be evaluated
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        Modified queued state of the event (without similar condition 
 *                flag)
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventQueue_StatusType, DEM_CODE)
Dem_EventQueue_ProcessSatelliteSimilarCondition(
  CONST(Dem_EventQueue_StatusType, AUTOMATIC)  QueueStatus,
  CONST(Dem_Satellite_IdType, AUTOMATIC) SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC) MonitorId,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );


/* ****************************************************************************
 * Dem_EventQueue_ProcessSatelliteQueuedEventActions
 *****************************************************************************/
/*!
 * \brief         Processes all queued events.
 *
 * \details       This function processes queued event status changes for all
 *                events.
 *
 * \param[in]     SatelliteId
 *                Unique handle of the Satellite.
 *                The SatelliteId must be in range [1..Dem_Cfg_GlobalSatelliteCount()[.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EventQueue_ProcessSatelliteQueuedEventActions(
  CONST(Dem_Satellite_IdType, AUTOMATIC) SatelliteId
  );

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/

/* ****************************************************************************
 % Dem_EventQueue_GetQueueAction
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_EventQueue_GetQueueAction(
  CONST(Dem_EventQueue_StatusType, AUTOMATIC) QueueStatus
  )
{
  return (uint8)(QueueStatus & DEM_EVENTQUEUE_ACTION);
}

/* ****************************************************************************
 % Dem_EventQueue_SetQueueAction
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventQueue_StatusType, DEM_CODE)
Dem_EventQueue_SetQueueAction(
  CONST(Dem_EventQueue_StatusType, AUTOMATIC) QueueStatus,
  CONST(uint8, AUTOMATIC) Action
  )
{
  return (Dem_EventQueue_StatusType)(
       (QueueStatus & DEM_EVENTQUEUE_ACTION_MASK)
     | (Action & DEM_EVENTQUEUE_ACTION) );
}

/* ****************************************************************************
 % Dem_EventQueueCore_ProcessQueuedEventActions
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
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EventQueueCore_ProcessQueuedEventActions(
  CONST(Dem_EventQueue_StatusType, AUTOMATIC)  QueueStatus,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  uint8 lQueueAction;

  if (Dem_EventQueue_TestResetTestFailedRequested(QueueStatus) == TRUE)
  {
    Dem_Event_ResetTestFailed(EventId);
  }
#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_ON)
  if (Dem_EventQueue_TestFdcProcessingStatus(QueueStatus) == TRUE)
  {
    boolean lTestCompleted;
    /* First completed test this cycle */
    lTestCompleted = ( (Dem_EventQueue_GetQueueAction(QueueStatus) != 0u)
                           && (Dem_UDSStatus_Test_TNCTOC(Dem_Event_GetUDSStatus(EventId)) == TRUE) );                            

    Dem_DTC_CustomizedFdcTrip(EventId, 
      lTestCompleted, 
      (boolean)(Dem_EventQueue_TestFdcTripStatus(QueueStatus) == TRUE),
      (boolean)(Dem_EventQueue_TestFdcMaxSLCStatus(QueueStatus) == TRUE));
  }
#else
  if (Dem_EventQueue_TestFdcProcessingStatus(QueueStatus) == TRUE)
  {
    Dem_Event_ProcessFdc(EventId,
      (boolean)(Dem_EventQueue_TestFdcTripStatus(QueueStatus) == TRUE),
      (boolean)(Dem_EventQueue_TestFdcMaxSLCStatus(QueueStatus) == TRUE));
  }
#endif

  lQueueAction = Dem_EventQueue_GetQueueAction(QueueStatus);

  if (lQueueAction != DEM_EVENTQUEUE_STATE_INITIAL)
  {
    switch (lQueueAction)
    {
    case DEM_EVENTQUEUE_PASSED:
      Dem_Event_Passed(EventId);
      break;
    case DEM_EVENTQUEUE_PASSED_FAILED:
      Dem_Event_Passed(EventId);
      Dem_Event_Failed(EventId);
      break;
    case DEM_EVENTQUEUE_PASSED_FAILED_PASSED:
      Dem_Event_Passed(EventId);
      Dem_Event_Failed(EventId);
      Dem_Event_Passed(EventId);
      break;
    case DEM_EVENTQUEUE_FAILED:
      Dem_Event_Failed(EventId);
      break;
    case DEM_EVENTQUEUE_FAILED_PASSED:
      Dem_Event_Failed(EventId);
      Dem_Event_Passed(EventId);
      break;
    case DEM_EVENTQUEUE_FAILED_PASSED_FAILED:
      Dem_Event_Failed(EventId);
      Dem_Event_Passed(EventId);
      Dem_Event_Failed(EventId);
      break;
    default:                                                                                                                     /* PRQA S 2016 */ /* MD_MSR_EmptyClause */
    /* No action */
      break;
    }

    (void)Dem_Iumpr_ReportRatioFault(EventId, Dem_Iumpr_FaultOrigin_EventReport);

  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_EventQueue_ProcessEventQueuedEventActions
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EventQueue_ProcessEventQueuedEventActions(
  CONST(Dem_EventQueue_StatusType, AUTOMATIC)  QueueStatus,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
  Dem_Prestore_EventPrestorageLock(EventId);
#endif

  Dem_EventQueueCore_ProcessQueuedEventActions(QueueStatus, EventId);

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
  Dem_Prestore_EventPrestorageRelease();
#endif
}

/* ****************************************************************************
 % Dem_EventQueue_ProcessSatelliteSimilarCondition
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
DEM_LOCAL_INLINE FUNC(Dem_EventQueue_StatusType, DEM_CODE)
Dem_EventQueue_ProcessSatelliteSimilarCondition(
  CONST(Dem_EventQueue_StatusType, AUTOMATIC)  QueueStatus,
  CONST(Dem_Satellite_IdType, AUTOMATIC) SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC) MonitorId,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_EventQueue_StatusType lQueueStatus;
  lQueueStatus = QueueStatus;
  if (Dem_EventQueue_TestSimilarConditionStatusChanged(QueueStatus) == TRUE)
  {
    Dem_DTC_ExtendedStatusType lOldExtendedStatus;
    boolean lOldSimilarConditionStatus;
    boolean lNewSimilarConditionStatus;

    Dem_Internal_AssertContinue(Dem_Cfg_EventObdRelated(EventId), DEM_E_INCONSISTENT_STATE)
    lOldExtendedStatus = Dem_Event_GetExtendedStatus(EventId);
    lOldSimilarConditionStatus = Dem_EventInternalStatus_TestSimilarConditions(lOldExtendedStatus);
    lNewSimilarConditionStatus = Dem_Satellite_GetSimilarConditionStatus(SatelliteId, MonitorId);

    if (lNewSimilarConditionStatus != lOldSimilarConditionStatus)
    {
      Dem_Event_ExtendedStatusType lNewExtendedStatus;
      if (lNewSimilarConditionStatus == TRUE)
      {
        lNewExtendedStatus = Dem_EventInternalStatus_SetSimilarConditions(lOldExtendedStatus);
      }
      else
      {
        lNewExtendedStatus = Dem_EventInternalStatus_ResetSimilarConditions(lOldExtendedStatus);
      }
      Dem_Event_SetExtendedStatus(EventId, lNewExtendedStatus);
      Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_STATUS), 
                                  DEM_NVM_BLOCKSTATE_DIRTY);
    }
    lQueueStatus = Dem_EventQueue_ResetSimilarConditionStatusChanged(lQueueStatus);
  }
  return lQueueStatus;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_EventQueue_ProcessSatelliteQueuedEventActions
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EventQueue_ProcessSatelliteQueuedEventActions(
  CONST(Dem_Satellite_IdType, AUTOMATIC) SatelliteId
  )
{
  Dem_Satellite_MonitorIdType lMonitorId;

  for (lMonitorId = 0u;
       lMonitorId < Dem_Cfg_GetEventCountOfSatelliteInfo(SatelliteId);
       ++lMonitorId)
  {
    if (Dem_Satellite_PeekEventQueueStatus(SatelliteId, lMonitorId) != DEM_EVENTQUEUE_STATE_INITIAL)
    {
      Dem_EventQueue_StatusType lQueueStatus;
      Dem_EventIdType lEventId;

      lEventId = Dem_Satellite_GetEventId(SatelliteId, lMonitorId);
      lQueueStatus = Dem_SatelliteCore_ConsumeEventQueueStatus(SatelliteId, lMonitorId);

      lQueueStatus = Dem_EventQueue_ProcessSatelliteSimilarCondition(lQueueStatus, SatelliteId, lMonitorId, lEventId);
      if (lQueueStatus != DEM_EVENTQUEUE_STATE_INITIAL)
      {
        Dem_EventQueue_ProcessEventQueuedEventActions(lQueueStatus, lEventId);
      }
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
 * \addtogroup Dem_EventQueue_Public
 * \{
 */

/* ****************************************************************************
 % Dem_EventQueue_TestQueueOverflow
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EventQueue_TestQueueOverflow(
  CONST(Dem_EventQueue_StatusType, AUTOMATIC)  QueueStatus,
  CONST(Dem_EventStatusType, AUTOMATIC)  MonitorTrigger
  )
{
  boolean lReturnValue;
  uint8 lQueueAction;

  lQueueAction = Dem_EventQueue_GetQueueAction(QueueStatus);

  if ( ((MonitorTrigger == DEM_EVENT_STATUS_FAILED) && (lQueueAction == DEM_EVENTQUEUE_PASSED_FAILED_PASSED))
    || ((MonitorTrigger == DEM_EVENT_STATUS_PASSED) && (lQueueAction == DEM_EVENTQUEUE_FAILED_PASSED_FAILED)))
  {
    lReturnValue = TRUE;
  }
  else
  {
    lReturnValue = FALSE;
  }

  return lReturnValue;
}

/* ****************************************************************************
 % Dem_EventQueue_CalculateQueueStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventQueue_StatusType, DEM_CODE)
Dem_EventQueue_CalculateQueueStatus(
  CONST(Dem_EventQueue_StatusType, AUTOMATIC)  QueueStatus,
  CONST(Dem_EventStatusType, AUTOMATIC)  MonitorTrigger
  )
{
  Dem_EventQueue_StatusType lReturnValue;

  if (MonitorTrigger == DEM_EVENT_STATUS_FAILED)
  {
    switch (Dem_EventQueue_GetQueueAction(QueueStatus))
    {
    case DEM_EVENTQUEUE_STATE_INITIAL:
      lReturnValue = Dem_EventQueue_SetQueueAction(QueueStatus, DEM_EVENTQUEUE_FAILED);
      break;
    case DEM_EVENTQUEUE_PASSED:
    case DEM_EVENTQUEUE_FAILED_PASSED:
      lReturnValue = (Dem_EventQueue_StatusType)(QueueStatus + 1u);
      break;
    default:
      lReturnValue = QueueStatus;
      break;
    }
  }
  else if (MonitorTrigger == DEM_EVENT_STATUS_PASSED)
  {
    switch (Dem_EventQueue_GetQueueAction(QueueStatus))
    {
    case DEM_EVENTQUEUE_STATE_INITIAL:
      lReturnValue = Dem_EventQueue_SetQueueAction(QueueStatus, DEM_EVENTQUEUE_PASSED);
      break;
    case DEM_EVENTQUEUE_FAILED:
    case DEM_EVENTQUEUE_PASSED_FAILED:
      lReturnValue = (Dem_EventQueue_StatusType)(QueueStatus + 1u);
      break;
    default:
      lReturnValue = QueueStatus;
      break;
    }
  }
  else
  {
    /* Not a qualified result */
    lReturnValue = QueueStatus;
  }

  return lReturnValue;
}

/* ****************************************************************************
 % Dem_EventQueueCore_Init
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EventQueueCore_Init(
  void
  )
{
  Dem_Scheduler_EnableTask(Dem_Scheduler_Task_EventQueue);
}

/* ****************************************************************************
 % Dem_EventQueueCore_MainFunction
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
Dem_EventQueueCore_MainFunction(
  void
  )
{
  boolean lEventActionsProcessed;
  Dem_Satellite_IdType lSatelliteId;

  lEventActionsProcessed = FALSE;

  for (lSatelliteId = 0u; lSatelliteId < Dem_Cfg_GlobalSatelliteCount(); ++lSatelliteId)
  {
    if (Dem_SatelliteCore_TestAndClearEventQueueUpdated(lSatelliteId) == TRUE)
    {
      Dem_EventQueue_ProcessSatelliteQueuedEventActions(lSatelliteId);
      lEventActionsProcessed = TRUE;
    }
  }

  if (lEventActionsProcessed == TRUE)
  {
    Dem_Iumpr_MainFunction();
  }
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */


#endif /* DEM_EVENTQUEUE_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_EventQueue_Implementation.h
 *********************************************************************************************************************/
