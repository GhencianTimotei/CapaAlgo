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
/*! \ingroup    Dem_Event
 *  \defgroup   Dem_EventIF Interface for Events IF
 *  \{
 *  \file       Dem_EventIF_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Public interface of the EventIF subcomponent
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_EVENTIF_INTERFACE_H)
#define DEM_EVENTIF_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_EventIF_Types.h"

/* ------------------------------------------------------------------------- */
#include "Dem_DTC_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

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
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*!
 * \defgroup Dem_Event_PublicProperties Public Properties
 * \{
 */

 /* ****************************************************************************
 * Dem_Event_IsSimilarConditionsEnabled
 *****************************************************************************/
 /*!
 * \brief         Returns true if feature similar condition is enabled.
 * \details       -
 *
 * \return        TRUE
 *                Supported
 * \return        FALSE
 *                Not supported
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Event_IsSimilarConditionsEnabled(
  void
);



/* ****************************************************************************
 * Dem_Event_TestValidHandle
 *****************************************************************************/
/*!
 * \brief         Test whether a handle is a valid event ID
 *
 * \details       This function tests whether a handle is in the valid range
 *                of EventIds. This function does not consider calibration or
 *                runtime-availability.
 *
 * \param[in]     EventId
 *                Handle to test against range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE
 *                EventId is valid
 * \return        FALSE
 *                EventId is not valid
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Event_TestValidHandle(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

/* ****************************************************************************
 * Dem_Event_TestMilSupport
 *****************************************************************************/
/*!
 * \brief         Returns if the event supports the Mil indicator.
 *
 * \details       Returns if the event supports the Mil indicator.
 *
 * \param[in]     EventId
 *                Unique handle of the event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE
 *                The MIL is supported.
 *                FALSE
 *                The MIL is not supported.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Event_TestMilSupport(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );


/* ****************************************************************************
 * Dem_Event_TestDebounceCounterStoredInNv
 *****************************************************************************/
/*!
 * \brief         Test if the event stores the debounce counter in NV
 *
 * \details       Test if the event stores the debounce counter in NV
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE
 *                The event stores the debounce counter in NV
 * \return        FALSE
 *                The event does not stores the debounce counter in NV
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Event_TestDebounceCounterStoredInNv(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );


/* ****************************************************************************
 * Dem_Event_TestObdVisibilityDelayed
 *****************************************************************************/
/*!
 * \brief         Returns if the external visibility of OBD CDTC / WIR status
 *                bits (and all related changes in visibility) is delayed until
 *                DCY qualification.
 *
 * \details       -
 *
 * \param[in]     EventId
 *                Unique handle of the event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE
 *                External visibility is delayed until DCY qualification.
 *                FALSE
 *                Immediate visibility.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Event_TestObdVisibilityDelayed(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
);


/* ****************************************************************************
 * Dem_Event_GetInternalStatus
 *****************************************************************************/
/*!
 * \brief         Get current internal status of the event
 *
 * \details       Get current internal status of the event
 *
 * \param[in]     EventId
 *                Unique handle of the event
 *
 * \return        Current internal status of the event
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Event_InternalStatusType, DEM_CODE)
Dem_Event_GetInternalStatus(
  CONST(Dem_EventIdType, AUTOMATIC) EventId
  );

/* ****************************************************************************
 * Dem_Event_SetInternalStatus
 *****************************************************************************/
/*!
 * \brief         Set current internal status value of the event
 *
 * \details       Set current internal status value of the event
 *
 * \param[in]     EventId
 *                Unique handle of the event
 * \param[in]     Status
 *                New internal status of the event
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_SetInternalStatus(
  CONST(Dem_EventIdType, AUTOMATIC) EventId,
  CONST(Dem_Event_InternalStatusType, AUTOMATIC) Status
  );

/* ****************************************************************************
 * Dem_Event_GetExtendedStatus
 *****************************************************************************/
/*!
 * \brief         Get current extended status of the event
 *
 * \details       Get current extended status of the event
 *
 * \param[in]     EventId
 *                Unique handle of the event
 *
 * \return        Current extended status of the event
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTC_ExtendedStatusType, DEM_CODE)
Dem_Event_GetExtendedStatus(
  CONST(Dem_EventIdType, AUTOMATIC) EventId
  );

/* ****************************************************************************
 * Dem_Event_SetExtendedStatus
 *****************************************************************************/
/*!
 * \brief         Set current extended status value of the event
 *
 * \details       Set current extended status value of the event
 *
 * \param[in]     EventId
 *                Unique handle of the event
 * \param[in]     Status
 *                New extended status of the event
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_SetExtendedStatus(
  CONST(Dem_EventIdType, AUTOMATIC) EventId,
  CONST(Dem_DTC_ExtendedStatusType, AUTOMATIC) Status
  );

#if (DEM_FEATURE_NEED_TRIPCOUNTER == STD_ON)
/* ****************************************************************************
 * Dem_Event_GetTripCount
 *****************************************************************************/
/*!
 * \brief         Get current trip count of the event
 *
 * \details       Get current trip count of the event
 *
 * \param[in]     EventId
 *                Unique handle of the event
 *
 * \return        Current trip count of the event
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_TRIPCOUNTER == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Event_GetTripCount(
  CONST(Dem_EventIdType, AUTOMATIC) EventId
  );
#endif

#if (DEM_FEATURE_NEED_TRIPCOUNTER == STD_ON)
/* ****************************************************************************
 * Dem_Event_SetTripCount
 *****************************************************************************/
/*!
 * \brief         Set current trip count of the event
 *
 * \details       Set current trip count of the event
 *
 * \param[in]     EventId
 *                Unique handle of the event
 * \param[in]     TripCount
 *                New trip count of the event
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_TRIPCOUNTER == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_SetTripCount(
  CONST(Dem_EventIdType, AUTOMATIC) EventId,
  CONST(uint8, AUTOMATIC) TripCount
  );
#endif

/* ****************************************************************************
 * Dem_Event_GetQualifyStatus
 *****************************************************************************/
/*!
 * \brief         Get current qualification status of the event
 *
 * \details       Get current qualification status of the event
 *
 * \param[in]     EventId
 *                Unique handle of the event
 *
 * \return        Current qualification status of the event
 *
 * \pre           Obd is enabled
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Event_GetQualifyStatus(
  CONST(Dem_EventIdType, AUTOMATIC) EventId
  );

/* ****************************************************************************
 * Dem_Event_SetQualifyStatus
 *****************************************************************************/
/*!
 * \brief         Set current qualification status of the event
 *
 * \details       Set current qualification status of the event
 *
 * \param[in]     EventId
 *                Unique handle of the event
 * \param[in]     Status
 *                New qualification status of the event
 *
 * \pre           Event is OBD related
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_SetQualifyStatus(
  CONST(Dem_EventIdType, AUTOMATIC) EventId,
  CONST(uint8, AUTOMATIC) Status
  );

/* ****************************************************************************
 * Dem_Event_GetUDSStatus
 *****************************************************************************/
/*!
 * \brief         Get current UDS status of the event
 *
 * \details       Get current UDS status of the event
 *
 * \param[in]     EventId
 *                Unique handle of the event
 *
 * \return        Current UDS status of the event
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_Event_GetUDSStatus(
  CONST(Dem_EventIdType, AUTOMATIC) EventId
  );

/* ****************************************************************************
 * Dem_Event_SetUDSStatus
 *****************************************************************************/
/*!
 * \brief         Set current UDS status value of the event
 *
 * \details       Set current UDS status value of the event
 *
 * \param[in]     EventId
 *                Unique handle of the event
 * \param[in]     Status
 *                New UDS status of the event
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_SetUDSStatus(
  CONST(Dem_EventIdType, AUTOMATIC) EventId,
  CONST(Dem_UDSStatus_Type, AUTOMATIC) Status
  );

/* ****************************************************************************
 * Dem_Event_GetExternalUDSStatus
 *****************************************************************************/
/*!
 * \brief         Get the current external UDS status of the event
 *
 * \details       Get the current external UDS status of the event.
 *                In case of OBD the non-qualified status bits are masked out.
 *
 * \param[in]     EventId
 *                Unique handle of the event
 * \param[in]     EventStatus
 *                The current internal event status of the event
 *
 * \return        Current external UDS status of the event
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_Event_GetExternalUDSStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  EventStatus
  );


/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_Event_Public Public Methods
 * \{
 */

 /* ****************************************************************************
 * Dem_Event_GetDataCommitState
 *****************************************************************************/
 /*!
 * \brief         Get the update state for readable data of this event.
 *
 * \details       Get the update state for readable data of this event.
 *
 * \param[in]     EventId
 *                Index in update state array
 *
 * \return        The update state of event's readable data.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Event_GetDataCommitState(
  Dem_EventIdType EventId
);

/* ****************************************************************************
 * Dem_Event_TestDataUpdateInProgress
 *****************************************************************************/
/*!
 * \brief         Test commit started state of event data update transaction.
 *
 * \details       Test commit started state of event data update transaction.
 *
 * \param[in]     The update state of the event data.
 *
 * \return        TRUE if commit has started.
 * \return        FALSE if commit has not started.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Event_TestDataUpdateInProgress(
  CONST(uint8, AUTOMATIC)  DataState
  );


/* ****************************************************************************
 * Dem_Event_DataUpdateStart
 *****************************************************************************/
/*!
 * \brief         Mark update started for the event.
 *
 * \details       Mark update started for the event.
 *
 * \param[in]     EventId
 *                Index in update state array
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_DataUpdateStart(
  Dem_EventIdType EventId
  );

/* ****************************************************************************
 * Dem_Event_DataUpdateFinish
 *****************************************************************************/
/*!
 * \brief         Mark update finished for the event.
 *
 * \details       Mark update finished for the event.
 *
 * \param[in]     EventId
 *                Index in update state array
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_DataUpdateFinish(
  Dem_EventIdType EventId
  );

#if ((DEM_FEATURE_NEED_OBD == STD_ON) \
    && (DEM_CFG_PROCESS_CDTC_ALL_DTC == STD_OFF))
/* ****************************************************************************
 * Dem_Event_UpdateQualificationStatus
 *****************************************************************************/
/*!
 * \brief         Persist the newest qualification status of event to memory.
 *
 * \details       Persist the newest qualification status of event to memory.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     MemoryIndex
 *                Valid Handle of the memory block
 *
 * \pre           -
 *
 * \config        (DEM_FEATURE_NEED_OBD == STD_ON)
 *                 && (DEM_CFG_PROCESS_CDTC_ALL_DTC == STD_OFF
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Event_UpdateQualificationStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  );
#endif

/* ****************************************************************************
 * Dem_Event_TestEventMayAge
 *****************************************************************************/
/*!
 * \brief         Tests whether an event may age
 *
 * \details       Tests whether an event may age
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     EventStatus
 *                Current event status of the event
 *
 * \return        TRUE
 *                The event may age
 * \return        FALSE
 *                The event may not age
 *
 * \pre           -
 *
 * \config        DEM_FEATURE_NEED_HEALING == STD_ON
 *                  && DEM_FEATURE_NEED_AGING_AFTER_HEALING == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_Event_TestEventMayAge(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  EventStatus
  );

#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
/* ****************************************************************************
 * Dem_Event_Disconnect_Normal
 *****************************************************************************/
/*!
 * \brief         Marks a normal event unavailable
 *
 * \details       This function sets the event unavailable if it is not stored.
 *
 *                Do not call directly, use Dem_Event_Disconnect instead.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           Must be called in critical section DiagMonitor
 * \config        DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_Disconnect_Normal(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
/* ****************************************************************************
 * Dem_Event_Disconnect
 *****************************************************************************/
/*!
 * \brief         Marks an event unavailable
 *
 * \details       This function sets an event unavailable, if its state allows
 *                to do so.
 *
 *                In case the event is set unavailable, its event status byte
 *                is changed to 0x00 and the FiM is informed.
 *
 *                Otherwise, this function returns E_NOT_OK.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        E_OK
 *                The event was set to unavailable
 * \return        E_NOT_OK
 *                The event was not set to unavailable
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Event_Disconnect(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
/* ****************************************************************************
 * Dem_Event_Reconnect_Normal
 *****************************************************************************/
/*!
 * \brief         Marks a normal event available
 *
 * \details       This function sets the event available.
 *
 *                Do not call directly, use Dem_Event_Reconnect instead.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_Reconnect_Normal(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

/* ****************************************************************************
 * Dem_Event_TestEventAvailable
 *****************************************************************************/
/*!
 * \brief         Tests if an Event is available based on configuration variant
 *                and runtime calibration
 *
 * \details       -
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE
 *                The event is available
 * \return        FALSE
 *                The event is not available
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Event_TestEventAvailable(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

/* ****************************************************************************
 * Dem_Event_TestEventRuntimeAvailable
 *****************************************************************************/
/*!
 * \brief         Tests if an Event is available based on runtime calibration
 *
 * \details       -
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE
 *                The event is available
 * \return        FALSE
 *                The event is not available
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Event_TestEventRuntimeAvailable(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

/* ****************************************************************************
 * Dem_Event_TestSuppressionOnEventRetrieval
 *****************************************************************************/
/*!
 * \brief         Tests if an event can be considered for reporting API
 *
 * \details       Tests all options due to which an event has to be excluded
 *                from reporting API, based on an individual event.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE
 *                The event is currently suppressed
 * \return        FALSE
 *                The event is currently not suppressed
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Event_TestSuppressionOnEventRetrieval(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

#if (DEM_FEATURE_NEED_PID01_CALCULATION == STD_ON) \
 || (DEM_FEATURE_NEED_PID41_CALCULATION == STD_ON)
/* ****************************************************************************
 * Dem_Event_TestEventUnavailable
 *****************************************************************************/
/*!
 * \brief         Tests if an event is unavailable
 *
 * \details       Tests all options due to which an event can be set
 *                unavailable, based on an individual event.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE
 *                The event is currently unavailable
 * \return        FALSE
 *                The event is currently available
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_PID01_CALCULATION == STD_ON)
 *                || (DEM_FEATURE_NEED_PID41_CALCULATION == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Event_TestEventUnavailable(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

#if (DEM_FEATURE_NEED_EVENTAVAILABLE_DEFAULT == STD_ON) \
 || (DEM_FEATURE_NEED_EVENTAVAILABLE_NV == STD_ON)
/* ****************************************************************************
 * Dem_Event_SetDisconnectedBit
 *****************************************************************************/
/*!
 * \brief         Set an event's disconnected bit
 *
 * \details       -
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     IsDisconnected
 *                TRUE: Set disconnected bit to TRUE
 *                FALSE: Set disconnected bit to FALSE
 *
 * \pre           Must be called within critical section DiagMonitor
 * \config        (DEM_FEATURE_NEED_EVENTAVAILABLE_DEFAULT == STD_ON)
 *                || (DEM_FEATURE_NEED_EVENTAVAILABLE_NV == STD_ON)
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_SetDisconnectedBit(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(boolean, AUTOMATIC)  IsDisconnected
  );
#endif

#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
/* ****************************************************************************
 * Dem_Event_MayDisconnect
 *****************************************************************************/
/*!
 * \brief         Tests precondition for event disconnect
 *
 * \details       -
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \return        TRUE
 *                The event may be disconnected
 * \return        FALSE
 *                The event may not be disconnected
 * \pre           Must be called within critical section DiagMonitor
 * \config        DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_Event_MayDisconnect(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
/* ****************************************************************************
 * Dem_Event_Reconnect
 *****************************************************************************/
/*!
 * \brief         Marks an event available
 *
 * \details       This function sets an event available.
 *
 *                In case the event is set available, its event status byte is
 *                changed to 0x50 and the FiM is informed.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_Reconnect(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF)
/* ****************************************************************************
 * Dem_Event_ProcessFdc
 *****************************************************************************/
/*!
 * \brief         Process the event's FDC trip actions
 *
 * \details       This function processes the stored triggers from debounce
 *                values passing the FDC trip threshold.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     FdcThresholdExceeded
 *                FDC Storage threshold was exceeded
 * \param[in]     FdcMaximumExceeded
 *                FDC Maximum (this cycle) was exceeded
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_ProcessFdc(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(boolean, AUTOMATIC)  FdcThresholdExceeded,
  CONST(boolean, AUTOMATIC)  FdcMaximumExceeded
  );
#endif

/* ****************************************************************************
 * Dem_Event_Passed
 *****************************************************************************/
/*!
 * \brief         Process the event's queued qualified passed result
 *
 * \details       This function processes a passed result stored on the
 *                event queue, for events using the QUEUED mechanism. The
 *                triggers resulting from the status bit changes are calculated
 *                within this function, based on the current event status.
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
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Event_Passed(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

/* ****************************************************************************
 * Dem_Event_Healed
 *****************************************************************************/
/*!
 * \brief         Heals an event
 *
 * \details       Resets all warning indicator requests from the given event.
 *                This can modify the global indicator state if the indicator
 *                is no longer requested at all.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     EventStatus
 *                Current event status of the event
 *
 * \return        Modified event status based on the status passed
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL FUNC(uint8, DEM_CODE)
Dem_Event_Healed(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  EventStatus
  );

/* ****************************************************************************
 * Dem_Event_Failed
 *****************************************************************************/
/*!
 * \brief         Process the event's queued qualified failed result
 *
 * \details       This function processes a failed result stored on the
 *                event queue.
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
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Event_Failed(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

/* ****************************************************************************
 * Dem_Event_OpCycle
 *****************************************************************************/
/*!
 * \brief         Updates an event's state due to operation cycle change
 *
 * \details       -
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in,out] ArgPtr
 *                Arguments: CycleStatus - encoding of cycle modification
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Event_OpCycle(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_DTC_ForEachCombinedArgPtrType, AUTOMATIC)  ArgPtr
  );

/* ****************************************************************************
 * Dem_Event_ResetTestFailed
 *****************************************************************************/
/*!
 * \brief         Resets the 'TestFailed' bit
 *
 * \details       Resets the 'TestFailed' bit
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different events
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_ResetTestFailed(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF)
/* ****************************************************************************
 * Dem_Event_Aged
 *****************************************************************************/
/*!
 * \brief         Updates an event due to aging
 *
 * \details       -
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in,out] ArgPtr
 *                Arguments: none
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_Aged(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_DTC_ForEachCombinedArgPtrType, AUTOMATIC)  ArgPtr
  );
#endif


/* ****************************************************************************
 * Dem_Event_ProcessCleared
 *****************************************************************************/
/*!
 * \brief         Clears an event.
 *
 * \details       Invokes the 'Clear allowed' callbacks, clears an event,
 *                and invokes the 'init monitor for event' notifications.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE
 *                Event has been cleared.
 * \return        FALSE
 *                Event is not allowed to be cleared.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_Event_ProcessCleared(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

/* ****************************************************************************
 * Dem_Event_Cleared
 *****************************************************************************/
/*!
 * \brief         Clears an event's state in volatile RAM
 *
 * \details       Clears an event's state in volatile RAM
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in,out] ArgPtr
 *                Arguments: none
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_Cleared(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_DTC_ForEachCombinedArgPtrType, AUTOMATIC)  ArgPtr
  );

#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF) \
 && (DEM_CFG_SUPPORT_DISPLACEMENT == STD_ON)
/* ****************************************************************************
 * Dem_Event_Displaced
 *****************************************************************************/
/*!
 * \brief         Updates an event's status due to displacement
 *
 * \details       Do not call this function directly, it is part of
 *                Dem_DTC_Displaced
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in,out] ArgPtr
 *                Arguments: none
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF
 *             && DEM_CFG_SUPPORT_DISPLACEMENT == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_Displaced(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_DTC_ForEachCombinedArgPtrType, AUTOMATIC)  ArgPtr
  );
#endif

#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_ON)
/* ****************************************************************************
 * Dem_Event_CustomizedDisplacement
 *****************************************************************************/
/*!
 * \brief         Updates an event's status due to displacement
 *
 * \details       Do not call this function directly, it is part of
 *                Dem_DTC_CustomizedDisplacement
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in,out] ArgPtr
 *                Arguments: SI30 - Status Indicator byte
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_CustomizedDisplacement(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_DTC_ForEachCombinedArgPtrType, AUTOMATIC)  ArgPtr
  );
#endif

/* ****************************************************************************
 * Dem_Event_GetEventUDSStatus
 *****************************************************************************/
/*!
 * \brief         Gets the current event status
 *
 * \details       -
 *
 * \param[in]     EventId
 *                Unique handle of the Event
 *
 * \param[out]    EventUDSStatus
 *                Pointer receiving the event Uds status
 *
 * \return        E_OK
 *                EventUDSStatus now contains the event status
 *
 * \return        E_NOT_OK
 *                The request was rejected due to variant coding
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Event_GetEventUDSStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONSTP2VAR(Dem_UdsStatusByteType, AUTOMATIC, DEM_APPL_DATA)  EventUDSStatus
  );

/* ****************************************************************************
 * Dem_Event_GetEventFailed
 *****************************************************************************/
/*!
 * \brief         Gets Bit0 (TestFailed) of the current event status
 *
 * \details       -
 *
 * \param[in]     EventId
 *                Unique handle of the Event
 *
 * \param[out]    EventFailed
 *                Pointer receiving Bit0
 *
 * \return        E_OK
 *                EventFailed now contains Bit0
 *
 * \return        E_NOT_OK
 *                The request was rejected due to variant coding
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Event_GetEventFailed(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONSTP2VAR(boolean, AUTOMATIC, DEM_APPL_DATA)  EventFailed
  );

/* ****************************************************************************
 * Dem_Event_GetEventTested
 *****************************************************************************/
/*!
 * \brief         Gets Bit6 (TestNotCompletedThisOperationCycle) of the current event status
 *
 * \details       -
 *
 * \param[in]     EventId
 *                Unique handle of the Event
 *
 * \param[out]    EventTested
 *                Pointer receiving Bit6
 *
 * \return        E_OK
 *                EventTested now contains Bit6
 *
 * \return        E_NOT_OK
 *                The request was rejected due to variant coding
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Event_GetEventTested(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONSTP2VAR(boolean, AUTOMATIC, DEM_APPL_DATA)  EventTested
  );

#if (DEM_FEATURE_NEED_OBD == STD_ON)
/* ****************************************************************************
 * Dem_Event_CycleQualifyDcy
 *****************************************************************************/
/*!
 * \brief         Updates an event's state due to dcy qualification
 *
 * \details       -
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in,out] ArgPtr
 *                Arguments: none
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_OBD == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Event_CycleQualifyDcy(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_DTC_ForEachCombinedArgPtrType, AUTOMATIC)  ArgPtr
  );
#endif

#if ((DEM_FEATURE_NEED_OBD == STD_ON) \
    && (DEM_CFG_PROCESS_CDTC_ALL_DTC == STD_OFF) \
    && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 * Dem_Event_ProcessDCYQualificationCombinedDTC_StoredOnly
 *****************************************************************************/
/*!
 * \brief         Function recalculates the qualification state of WIR and
 *                Confirmed bits for a combined event in a configuration with
 *                CDTC processing set as 'STORED_ONLY'.
 *
 * \details       Function recalculates the qualification state of WIR and
 *                Confirmed bits for a combined event.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     ArgPtr
 *                Arguments passed to the operation.
 *
 * \pre           -
 *
 * \config        (DEM_FEATURE_NEED_OBD == STD_ON)
 *                && (DEM_CFG_PROCESS_CDTC_ALL_DTC == STD_OFF)
 *                && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
 *
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_ProcessDCYQualificationCombinedDTC_StoredOnly(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_DTC_ForEachCombinedArgPtrType, AUTOMATIC)  ArgPtr
  );
#endif

#if ((DEM_FEATURE_NEED_OBD == STD_ON) \
    && (DEM_CFG_PROCESS_CDTC_ALL_DTC == STD_OFF) \
    && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 * Dem_Event_ProcessDCYQualificationNonCombinedDTC_StoredOnly
 *****************************************************************************/
/*!
 * \brief         Function recalculates the qualification state of WIR and
 *                Confirmed bits for a normal event in a
 *                configuration with CDTC processing set as 'STORED_ONLY'.
 *
 * \details       Function recalculates the qualification state of WIR and
 *                Confirmed bits for a normal event.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     MemoryIndex
 *                Valid Handle of the memory block
 * \param[in]     ArgPtr
 *                Arguments passed to the operation.
 *
 * \pre           -
 *
 * \config        (DEM_FEATURE_NEED_OBD == STD_ON)
 *                && (DEM_CFG_PROCESS_CDTC_ALL_DTC == STD_OFF)
 *                && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
 *
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_ProcessDCYQualificationNonCombinedDTC_StoredOnly(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex,
  CONST(Dem_DTC_ForEachCombinedArgPtrType, AUTOMATIC)  ArgPtr
  );
#endif

/* ****************************************************************************
 * Dem_Event_TestLatchedTestFailed
 *****************************************************************************/
/*!
 * \brief         Tests whether an event's latched failed restriction applies
 *
 * \details       -
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE
 *                The event is latched at TestFailed
 * \return        FALSE
 *                The event is not latched, process it normally
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Event_TestLatchedTestFailed(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

/* ****************************************************************************
 * Dem_Event_InitNvData
 *****************************************************************************/
/*!
 * \brief         Initializes the event status processing sub-component
 *
 * \details       Initializes the event status processing sub-component
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           May be called only during module initialization
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_InitNvData(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

/* ****************************************************************************
 * Dem_Event_Init
 *****************************************************************************/
/*!
 * \brief         Initializes the event status processing sub-component
 *
 * \details       Initializes the event status processing sub-component
 *
 * \pre           May be called only during module initialization
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_Init(
  void
  );

/* ****************************************************************************
 * Dem_Event_PreInit
 *****************************************************************************/
/*!
 * \brief         Pre-Initializes the Dem events
 *
 * \details       Pre-Initializes the Dem events
 *
 * \pre           May be called only during module pre-initialization
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_PreInit(
  void
  );

/* ****************************************************************************
 * Dem_Event_MainFunction
 *****************************************************************************/
/*!
 * \brief         Process queued event availability changes
 *
 * \details       Process queued event availability changes
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_MainFunction(
  void
  );

/* ****************************************************************************
 * Dem_Event_SetAgingCounter
 *****************************************************************************/
/*!
 * \brief         Stored the event's aging counter inside the dedicated aging
 *                counter array.
 *
 * \details       Stored the event's aging counter inside the dedicated aging
 *                counter array.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \param[in]     AgingCounter
 *                The aging counter to be stored.
 *
 * \pre           -
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_SetAgingCounter(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint16, AUTOMATIC) AgingCounter
  );

/* ****************************************************************************
 * Dem_Event_GetAgingCounter
 *****************************************************************************/
/*!
 * \brief         Retrieve the event's aging counter stored in the dedicated
 *                aging counter array.
 *
 * \details       Retrieve the event's aging counter stored in the dedicated
 *                aging counter array.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        The aging counter of the event.
 *
 * \pre           -
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Event_GetAgingCounter(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

/* ****************************************************************************
 * Dem_Event_TestHighPriorReadinessGroup
 *****************************************************************************/
/*!
 * \brief         Test if EventId belongs to a high prior readiness group
 *
 * \details       Test if EventId belongs to readiness group misfire or fuel system
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE
 *                Major monitors are supported and readiness group of event is
 *                FLSYS_NONCONT, FLSYS or MISF
 * \return        FALSE
 *                Major monitors are not supported or readiness group of event is
 *                other than FLSYS_NONCONT, FLSYS or MISF
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_Event_TestHighPriorReadinessGroup(                                                                                           /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
CONST(Dem_EventIdType, AUTOMATIC)  EventId
);

/* ****************************************************************************
 * Dem_Event_GetRatioIdx
 *****************************************************************************/
/*!
 * \brief         Get the ratio index of an event
 *
 * \details       Get the ratio index of an event
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        Handle to the ratio configuration for an event
 *
 * \pre           The event must have a ratio configured. Feature IUMPR is supported.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_RatioIdIndexType, DEM_CODE)
Dem_Event_GetRatioIdx(
CONST(Dem_EventIdType, AUTOMATIC)  EventId
);

/* ****************************************************************************
 * Dem_Event_ResetEventReporting
 *****************************************************************************/
/*!
 * \brief         Reset debouncing and queue status
 *
 * \details       Reset debouncing and queue status to enable 
 *                correct event reporting/ debouncing for events. This function shall
 *                be invoked during the start of the event's operation cycle/ during 
 *                shutdown.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_ResetEventReporting(
  Dem_EventIdType  EventId
);

/* ****************************************************************************
 * Dem_Event_InitUdsFromStatusIndicator
 *****************************************************************************/
/*!
 * \brief         Initializes event status using the status indicator
 *
 * \details       Initializes event status using the status indicator
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()].
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \pre           May be called only during module initialization
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_InitUdsFromStatusIndicator(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
);

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_EVENTIF_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_EventIF_Interface.h
 *********************************************************************************************************************/
