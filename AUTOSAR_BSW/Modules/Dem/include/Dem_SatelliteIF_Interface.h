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
 *  \defgroup   Dem_SatelliteIF Dem SatelliteIF Functionality
 *  \{
 *  \file       Dem_SatelliteIF_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Public interface of SatelliteIF subcomponent
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_SATELLITEIF_INTERFACE_H)
#define DEM_SATELLITEIF_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                   /* Includes for own Types */
/* ------------------------------------------------------------------------- */
#include "Dem_SatelliteIF_Types.h"

                      /* Includes for Other Types used by the Implementation */
/* ------------------------------------------------------------------------- */
#include "Dem_Core_Types.h"
#include "Dem_FaultMemory_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_Satellite_PublicProperties Public Properties
 * \{
 */
 /* ****************************************************************************
 * Dem_SatelliteSat_IsLRTimeDebouncingEnabled
 *****************************************************************************/
 /*!
 * \brief         Test if feature low resolution time is supported in by configuration
 *
 * \details       Test if feature low resolution time is supported in by configuration
 *
 *
 * \return        TRUE
 *                Feature is supported
 * \return        FALSE
 *                Feature is not supported
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_SatelliteSat_IsLRTimeDebouncingEnabled(
  void
);

/* ****************************************************************************
 * Dem_SatelliteSat_IsHRTimeDebouncingEnabled
 *****************************************************************************/
/*!
 * \brief         Test if feature high resolution time is supported in by configuration
 *
 * \details       Test if feature high resolution time is supported in by configuration
 *
 *
 * \return        TRUE
 *                Feature is supported
 * \return        FALSE
 *                Feature is not supported
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_SatelliteSat_IsHRTimeDebouncingEnabled(
  void
);


/* ****************************************************************************
 * Dem_Satellite_GetEventId
 *****************************************************************************/
/*!
 * \brief         Get the global Event Id from the Monitor Id.
 *
 * \details       Get the global Event Id from the satellite specific Event Id.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \param[in]     MonitorId
 *                Satellite specific Event Id
 *
 * \return        The global Event Id
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Satellite_GetEventId(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  );


/* ****************************************************************************
 * Dem_Satellite_CheckEventApplicationId
 *****************************************************************************/
/*!
 * \brief         Check whether the event can be processed in the current
 *                execution context
 *
 * \details       Checks whether the given event is configured to be processed
 *                on the current OS application. In single partition
 *                configurations, this is always the case.
 *
 * \param[in]     EventId
 *                Global Event Id
 *
 * \return        TRUE
 *                The event can be processed
 * \return        FALSE
 *                The event belongs to a different OS application
 *
 * \pre           -
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Satellite_CheckEventApplicationId(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  );




/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */


/* ********************************************************************************************************************
 *  SUBCOMPONENT API PUBLIC FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_Satellite_Public Public Methods
 * \{
 */

/* ****************************************************************************
 * Dem_SatelliteSat_SetPrestoreQueueUpdated
 *****************************************************************************/
/*!
 * \brief         Sets the prestorage update flag of the given satellite.
 *
 * \details       Sets the prestorage update flag of the given satellite.
 *
 * \param[in]     SatelliteId
 *                Satellite Index
 *
 * \pre           Function should only be invoked when the features "Support 
 *                prestorage of freeze frames" and "Multiple Satellites" are supported.
 *
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_SatelliteSat_SetPrestoreQueueUpdated(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId
  );

/* ****************************************************************************
 * Dem_SatelliteSat_FreezeDebounceStatus
 *****************************************************************************/
/*!
 * \brief         Pauses the debouncing of an event.
 *
 * \details       Pauses the debouncing of an event.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \param[in]     MonitorId
 *                Satellite specific Event Id
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_SatelliteSat_FreezeDebounceStatus(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  );

/* ****************************************************************************
 * Dem_SatelliteCore_FreezeDebounceStatus
 *****************************************************************************/
/*!
 * \brief         Pauses the debouncing of an event.
 *
 * \details       Pauses the debouncing of an event.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \param[in]     MonitorId
 *                Satellite specific Event Id
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_SatelliteCore_FreezeDebounceStatus(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  );

/* ****************************************************************************
 * Dem_SatelliteSat_GetDebouncingState
 *****************************************************************************/
/*!
 * \brief         Calculates the debouncing state of an event.
 *
 * \details       Calculates the debouncing state of an event.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \param[in]     MonitorId
 *                Satellite specific Event Id
 *
 * \return        The debouncing state of the event
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(Dem_DebouncingStateType, DEM_CODE)
Dem_SatelliteSat_GetDebouncingState(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  );

/* ****************************************************************************
 * Dem_SatelliteSat_ResetMonitorStatus
 *****************************************************************************/
/*!
 * \brief         Reset the event status of an event.
 *
 * \details       Checks for valid reset conditions and triggers the
 *                updating of the monitor status in case of valid conditions.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \param[in]     MonitorId
 *                Satellite specific Event Id
 *
 * \return        E_OK
 *                The reset request was accepted
 * \return        E_NOT_OK
 *                The monitor result was rejected due to unfulfilled conditions
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_SatelliteSat_ResetMonitorStatus(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  );


/* ****************************************************************************
 * Dem_Satellite_GetSimilarConditionStatus
 *****************************************************************************/
/*!
 * \brief         Get the similar condition status of the Monitor Id.
 *
 * \details       -
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \param[in]     MonitorId
 *                Satellite specific Event Id
 *
 * \return        Similar condition status of the respective monitorr.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Satellite_GetSimilarConditionStatus(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  );

/* ****************************************************************************
 * Dem_SatelliteSat_UpdatePrestoreActionQueue
 *****************************************************************************/
/*!
 * \brief         Updates the queued prestore action of an event.
 *
 * \details       Enqueues the prestorage of an freeze frame or the clear of an
 *                already prestored freeze frame. A previously queued action is
 *                dequeued.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \param[in]     MonitorId
 *                Satellite specific Event Id
 *
 * \param[in]     NewPrestoreAction
 *                Handle of prestore action to queue
 *
 * \pre           Function should only be invoked when features "Prestorage of 
 *                freeze frames" and "Multiple Satellites" are supported
 *
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_SatelliteSat_UpdatePrestoreActionQueue(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId,
  CONST(Dem_Prestore_QueueActionType, AUTOMATIC)  NewPrestoreAction
  );

/* ****************************************************************************
 * Dem_SatelliteSat_MainFunction
 *****************************************************************************/
/*!
 * \brief         Processes all deferred operations.
 *
 * \details       This function is the task function of the Dem module.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \pre           The given SatelliteId is the ID of the caller satellite.
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SatelliteSat_MainFunction(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId
  );

/* ****************************************************************************
 * Dem_SatelliteSat_ResetDebounceStatus
 *****************************************************************************/
/*!
 * \brief         Resets the debouncing of an event.
 *
 * \details       Resets the debouncing of an event.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \param[in]     MonitorId
 *                Satellite specific Event Id
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SatelliteSat_ResetDebounceStatus(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  );

/* ****************************************************************************
 * Dem_SatelliteCore_ResetDebounceStatus
 *****************************************************************************/
/*!
 * \brief         Resets the debouncing of an event.
 *
 * \details       Resets the debouncing of an event.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \param[in]     MonitorId
 *                Satellite specific Event Id
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SatelliteCore_ResetDebounceStatus(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  );

/* ****************************************************************************
 * Dem_SatelliteCore_ClearEvent
 *****************************************************************************/
/*!
 * \brief         Resets the debouncing, the monitor status and all queued
 *                actions for an event.
 *
 * \details       Resets the debouncing, the monitor status and all queued
 *                actions for an event.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 * \param[in]     MonitorId
 *                Satellite specific Event Id
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SatelliteCore_ClearEvent(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  );

/* ****************************************************************************
 * Dem_SatelliteCore_RestartEvent
 *****************************************************************************/
/*!
 * \brief         Resets the debouncing and all queued actions for an event.
 *                Sets the TestNotCompletedThisCycle flag of the monitor status.
 *
 * \details       Resets the debouncing and all queued actions for an event.
 *                Sets the TestNotCompletedThisCycle flag of the monitor status.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 * \param[in]     MonitorId
 *                Satellite specific Event Id
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SatelliteCore_RestartEvent(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  );


/* ****************************************************************************
 * Dem_SatelliteCore_TestAndClearEventQueueUpdated
 *****************************************************************************/
/*!
 * \brief         Gets and resets the update flag of the given satellite.
 *
 * \details       Gets and resets the update flag of the given satellite.
 *
 * \param[in]     SatelliteId
 *                Satellite Index
 *
 * \return        The update flag of the satellite
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_SatelliteCore_TestAndClearEventQueueUpdated(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId
  );

/* ****************************************************************************
 * Dem_SatelliteCore_TestAndClearPrestoreQueueUpdated
 *****************************************************************************/
/*!
 * \brief         Gets and resets the update flag of the given satellite.
 *
 * \details       Gets and resets the update flag of the given satellite.
 *
 * \param[in]     SatelliteId
 *                Satellite Index
 *
 * \return        The update flag of the satellite
 *
 * \pre           Function should only be invoked when the feature "Support 
 *                prestorage of freeze frames" is supported.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_SatelliteCore_TestAndClearPrestoreQueueUpdated(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId
  );

/* ****************************************************************************
 * Dem_Satellite_PeekEventQueueStatus
 *****************************************************************************/
/*!
 * \brief         Gets the queue status of an event.
 *
 * \details       Gets the queue status of an event.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \param[in]     MonitorId
 *                Satellite specific Event Id
 *
 * \return        The queue status of the event
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventQueue_StatusType, DEM_CODE)
Dem_Satellite_PeekEventQueueStatus(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  );

/* ****************************************************************************
 * Dem_Satellite_PeekPrestoreActionQueue
 *****************************************************************************/
/*!
 * \brief         Gets the queued prestore action of an event.
 *
 * \details       Gets the queued prestore action of an event.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \param[in]     MonitorId
 *                Satellite specific Event Id
 *
 * \return        The queued prestore action of the event
 *
 * \pre           Function should only be invoked when the features "Support 
 *                prestorage of freeze frames" and "Multiple Satellites" are
 *                supported.
 *
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Prestore_QueueActionType, DEM_CODE)
Dem_Satellite_PeekPrestoreActionQueue(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  );

/* ****************************************************************************
 * Dem_SatelliteCore_ConsumeEventQueueStatus
 *****************************************************************************/
/*!
 * \brief         Gets and resets the queue status of an event.
 *
 * \details       Gets and resets the queue status of an event.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \param[in]     MonitorId
 *                Satellite specific Event Id
 *
 * \return        The old event queue status
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventQueue_StatusType, DEM_CODE)
Dem_SatelliteCore_ConsumeEventQueueStatus(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  );

/* ****************************************************************************
 * Dem_Satellite_ConsumePrestoreActionQueue
 *****************************************************************************/
/*!
 * \brief         Gets and resets the queued prestore action of an event.
 *
 * \details       Gets and resets the queued prestore action of an event.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \param[in]     MonitorId
 *                Satellite specific Event Id
 *
 * \return        Handle of queued prestore action
 *
 * \pre           Function should only be invoked when the features "Support 
 *                prestorage of freeze frames" and "Multiple Satellites" are
 *                supported.
 *
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Prestore_QueueActionType, DEM_CODE)
Dem_Satellite_ConsumePrestoreActionQueue(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  );

/* ****************************************************************************
 * Dem_SatelliteCore_MemoryInit
 *****************************************************************************/
/*!
 * \brief         Un-Initializes the satellite.
 *
 * \details       Un-Initializes the satellite.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SatelliteCore_MemoryInit(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId
  );

/* ****************************************************************************
 * Dem_SatelliteSat_PreInit
 *****************************************************************************/
/*!
 * \brief         Pre-Initializes the satellite.
 *
 * \details       Pre-Initializes the satellite.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SatelliteSat_PreInit(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId
  );

/* ****************************************************************************
 * Dem_SatelliteSat_Init
 *****************************************************************************/
/*!
 * \brief         Initializes the satellite.
 *
 * \details       Initializes the satellite.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SatelliteSat_Init(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId
  );

/* ****************************************************************************
 * Dem_Satellite_GetFaultDetectionCounter
 *****************************************************************************/
/*!
 * \brief         Reads the fault detection counter of an event.
 *
 * \details       Reads the fault detection counter of an event.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 * \param[in]     MonitorId
 *                Satellite specific Event Id
 * \param[out]    FaultDetectionCounter
 *                Pointer receiving the current fault detection counter
 *
 * \return        E_OK
 *                The FDC was stored into FaultDetectionCounter
 * \return        DEM_E_NO_FDC_AVAILABLE
 *                The debouncing for the event is done within the application,
 *                but no callback was configured to read the FDC.
 * \return        E_NOT_OK
 *                The request was rejected, e.g. due to variant coding (see
 *                Dem_SetEventAvailable() )
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Satellite_GetFaultDetectionCounter(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId,
  CONSTP2VAR(sint8, AUTOMATIC, DEM_APPL_DATA)  FaultDetectionCounter
  );

/* ****************************************************************************
 * Dem_Satellite_GetMaxFaultDetectionCounter
 *****************************************************************************/
/*!
 * \brief         Gets the maximum fault detection counter of an event.
 *
 * \details       This function retrieves the maximum value of the FDC in
 *                the current operation cycle. In case of monitor internal
 *                debouncing, this function returns an estimate based on the
 *                event's UDS status byte.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \param[in]     MonitorId
 *                Satellite specific Event Id
 *
 * \return        The maximum FDC this operation cycle
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(sint8, DEM_CODE)
Dem_Satellite_GetMaxFaultDetectionCounter(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  );

/* ****************************************************************************
 * Dem_SatelliteCore_RestoreDebounceValue
 *****************************************************************************/
/*!
 * \brief         Restores the given debouncing value of an event.
 *
 * \details       Value is restored, if
 *                 - the given debouncing value is not qualified
 *                 - the debouncing value is qualified and the reached
 *                   threshold equals the ExpectedThreshold.
 *
 *                Otherwise Value is not restored.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \param[in]     MonitorId
 *                Satellite specific Event Id
 *
 * \param[in]     Value
 *                The value to be restored
 *
 * \param[in]     ExpectedThreshold
 *                Specifies whether the negative threshold is expected to be
 *                reached (TRUE), or the positive one (FALSE).
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SatelliteCore_RestoreDebounceValue(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId,
  CONST(sint16, AUTOMATIC) Value,
  CONST(boolean, AUTOMATIC) ExpectedThreshold
  );

/* ****************************************************************************
 * Dem_Satellite_GetDebounceValue
 *****************************************************************************/
/*!
 * \brief         Gets the debounce data of the given event.
 *
 * \details       -
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \param[in]     MonitorId
 *                Satellite specific Event Id
 *
 * \return        The current debounce data of the event
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Debounce_DataType, DEM_CODE)
Dem_Satellite_GetDebounceValue(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  );

/* ****************************************************************************
 * Dem_Satellite_GetInitState
 *****************************************************************************/
/*!
 * \brief         Get the Dem initialization state.
 *
 * \details       Get the Dem initialization state.
 *
 * \param[in]     SatelliteId
 *                Satellite Index
 * \return        The current initialization state
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Satellite_GetInitState(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId
  );

/* ****************************************************************************
 * Dem_Satellite_GetMonitorStatus
 *****************************************************************************/
/*!
 * \brief         Gets the monitor status of the given event.
 *
 * \details       Gets the monitor status of the given event.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \param[in]     MonitorId
 *                Satellite specific Event Id
 *
 * \return        The current monitor status of the event
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_MonitorStatusType, DEM_CODE)
Dem_Satellite_GetMonitorStatus(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  );

/* ****************************************************************************
 * Dem_SatelliteSat_UpdateMonitorTrigger
 *****************************************************************************/
/*!
 * \brief         Processes asynchronous monitor reports.
 *
 * \details       This function processes event debouncing and queues
 *                qualified test results.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \param[in]     MonitorId
 *                Satellite specific Event Id whose data is updated
 *
 * \param[in]     MonitorTrigger
 *                The monitor result
 *
 * \return        E_OK
 *                The monitor result was processed
 * \return        E_NOT_OK
 *                The monitor result was discarded.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different MonitorId or SatelliteId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_SatelliteSat_UpdateMonitorTrigger(
  CONST(Dem_Satellite_IdType, AUTOMATIC)        SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC) MonitorId,
  CONST(Dem_EventStatusType, AUTOMATIC)         MonitorTrigger
  );

/* ****************************************************************************
 * Dem_Satellite_GetCurrentSatelliteId
 *****************************************************************************/
/*!
 * \brief         Identify the current satellite context.
 *
 * \details       Get the satellite id of the satellite corresponding to the
 *                current OS application.
 *
 * \return        The satellite id of the satellite corresponding to the
 *                current OS application.
 *
 * \pre           OS applications must be started.
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Satellite_IdType, DEM_CODE)
Dem_Satellite_GetCurrentSatelliteId(
  void
  );

/* ****************************************************************************
 * Dem_SatelliteCore_TestAndClearStatusIndicatorQueueUpdated
 *****************************************************************************/
/*!
 * \brief         Gets and resets the StatusIndicator queue updated flag for 
 *                the given satellite.
 *
 * \details       Gets and resets the StatusIndicator queue updated flag for 
 *                the given satellite.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event.
 *
 * \return        StatusIndicator queue updated status for the given satellite.
 *
 * \pre           Function should only be invoked when the feature "Support
 *                Extended FiM" is enabled.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_SatelliteCore_TestAndClearStatusIndicatorQueueUpdated(
  Dem_Satellite_IdType SatelliteId
  );

/* ****************************************************************************
 * Dem_Satellite_PeekStatusIndicatorActionQueue
 *****************************************************************************/
/*!
 * \brief         Gets the queued StatusIndicator symptom requested action 
 *                of an event.
 *
 * \details       Gets the queued StatusIndicator symptom requested action 
 *                of an event.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \param[in]     MonitorId
 *                Satellite specific Event Id
 *
 * \return        The queued queued StatusIndicator aymptom requested 
 *                action of the event
 *
 * \pre           Function should only be invoked when the feature "Support
 *                Extended FiM" is enabled.
 *
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_StatusIndicator_QueueActionType, DEM_CODE)
Dem_Satellite_PeekStatusIndicatorActionQueue(
  Dem_Satellite_IdType SatelliteId,
  Dem_Satellite_MonitorIdType MonitorId
  );

/* ****************************************************************************
 * Dem_Satellite_SetStatusIndicatorSymptom
 *****************************************************************************/
/*!
 * \brief         Queues StatusIndicator symptom requested action if 
 *                preconditions are met.
 *
 * \details       Queues StatusIndicator symptom requested action if 
 *                 preconditions are met.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           Function should only be invoked when the feature "Support
 *                Extended FiM" is enabled.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Satellite_SetStatusIndicatorSymptom(
  Dem_EventIdType EventId                                                                                                        /* PRQA S 3206 */ /* MD_DEM_3206 */
  );

/* ****************************************************************************
 * Dem_Satellite_ConsumeStatusIndicatorActionQueue
 *****************************************************************************/
/*!
 * \brief         Gets and resets the StatusIndicator symptom requested 
 *                action of an event.
 *
 * \details       Gets and resets the StatusIndicator symptom requested 
 *                action of an event.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \param[in]     MonitorId
 *                Satellite specific Event Id
 *
 * \return        Queued StatusIndicator symptom requested action.
 *
 * \pre           Function should only be invoked when the feature "Support
 *                Extended FiM" is enabled.
 *
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_StatusIndicator_QueueActionType, DEM_CODE)
Dem_Satellite_ConsumeStatusIndicatorActionQueue(
  Dem_Satellite_IdType SatelliteId,
  Dem_Satellite_MonitorIdType MonitorId
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_SATELLITEIF_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_SatelliteIF_Interface.h
 *********************************************************************************************************************/
