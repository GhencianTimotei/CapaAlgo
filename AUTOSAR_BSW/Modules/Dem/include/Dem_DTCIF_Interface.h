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
/*! \ingroup    Dem_DTC
 *  \defgroup   Dem_DTCIF DTC Status IF
 *  \{
 *  \file       Dem_DTCIF_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Public interfaces of DTCIF subcomponent
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_DTCIF_INTERFACE_H)
#define DEM_DTCIF_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_DTCIF_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_DTC_PublicProperties Public Properties
 * \{
 */
/* ****************************************************************************
 * Dem_DTC_IsEventCombinationEnabled
 *****************************************************************************/
/*!
 * \brief         Returns true if feature 'Event Combination' is enabled.
 * \details       -
 *
 * \return        TRUE
 *                Support for 'Event Combination'
 * \return        FALSE
 *                No support for 'Event Combination'
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_IsEventCombinationEnabled(
void
);

/* ****************************************************************************
 * Dem_DTC_IsMemIndependentCycleCounterEnabled
 *****************************************************************************/
/*!
 * \brief         Returns true if feature 'memory independent cycle counter' is enabled.
 * \details       -
 *
 * \return        TRUE
 *                Support for 'memory independent cycle counter'
 * \return        FALSE
 *                No support for 'memory independent cycle counter'
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_IsMemIndependentCycleCounterEnabled(
  void
);

/* ****************************************************************************
 * Dem_DTC_IsEventCombinationType2Enabled
 *****************************************************************************/
/*!
 * \brief         Returns true if feature 'Event Combination Type 2' is enabled.
 * \details       -
 *
 * \return        TRUE
 *                Support for 'Event Combination Type 2'
 * \return        FALSE
 *                No support for 'Event Combination Type 2'
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_IsEventCombinationType2Enabled(
void
);

/* ****************************************************************************
 * Dem_DTC_GetInternalStatus
 *****************************************************************************/
/*!
 * \brief         Get the internal status byte with consideration of event
 *                combination
 *
 * \details       This function retrieves the event's internal status byte for
 *                normal events, and the group's internal status byte for
 *                combined events.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        The internal status byte relevant for the event or group.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTC_InternalStatusType, DEM_CODE)
Dem_DTC_GetInternalStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

/* ****************************************************************************
 * Dem_DTC_SetInternalStatus
 *****************************************************************************/
/*!
 * \brief         Set the internal status byte with consideration of event
 *                combination
 *
 * \details       This function stores the event's internal status byte for
 *                normal events, and the group's internal status byte for
 *                combined events.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     InternalStatus
 *                New internal status to set
 *
 * \pre           Must be called within critical section DiagMonitor
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_SetInternalStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_DTC_InternalStatusType, AUTOMATIC)  InternalStatus
  );

/* ****************************************************************************
 * Dem_DTC_SetQualifyStatus
 *****************************************************************************/
/*!
 * \brief         Set current qualification status of the DTC
 *
 * \details       Set current qualification status of the event and all subevents
 *                in case of event combination
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
Dem_DTC_SetQualifyStatus(
  CONST(Dem_EventIdType, AUTOMATIC) EventId,
  CONST(uint8, AUTOMATIC) Status
  );

#if (DEM_CFG_DATA_AGED_COUNTER == STD_ON)
/* ****************************************************************************
 * Dem_DTC_GetAgedCounter
 *****************************************************************************/
/*!
 * \brief         Gets the Aged Counter of the respective DTC.
 *
 * \details       Gets the Aged Counter of the respective DTC.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \config        DEM_CFG_DATA_AGED_COUNTER == STD_ON
 *
 * \return        Aged Counter of the DTC.
 *
 * \pre           Event has a dedicated entry in the aged counter array.
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DTC_GetAgedCounter(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

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
 * \defgroup Dem_DTC_Public Public Methods
 * \{
 */

 /* ****************************************************************************
 * Dem_DTC_InvokeInitMonitorCallbacks
 *****************************************************************************/
 /*!
 * \brief         Function invokes the InitMonitorForE and InitMonitorForF callback
 *                for the DTC
 *
 * \details       Function invokes the InitMonitorForEvent and InitMonitorForFunction
 *                callback for the DTC
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           Function must be called only when the Dem is Initialized and
 *                Operation cycle has been started.
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_InvokeInitMonitorCallbacks(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
);




 /* ****************************************************************************
 * Dem_DTC_GetFailedCycleCounter
 *****************************************************************************/
 /*!
 * \brief         Get the memory independent failed cycle counter of
 *                the respective DTC.
 *
 * \details       Get the memory independent failed cycle counter of
 *                the respective DTC.
 *
 * \param[in]     FailedCycleCounterIndex
 *                Index to array FailedCycleCounter.
 *                The Index must be in range [1..DEM_CFG_MAX_NUMBER_FAILED_CYCLE_DTCS[.
 * \return        Memory independent failed cycle counter
 *
 * \pre           -
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DTC_GetFailedCycleCounter(
  Dem_Cfg_FailedCycleCounterIndexOfEventTableType FailedCycleCounterIndex
);

 /* ****************************************************************************
 * Dem_DTC_GetFaultPendingCounter
 *****************************************************************************/
 /*!
 * \brief         Get the memory independent fault pending counter of
 *                the respective DTC.
 *
 * \details       Get the memory independent fault pending counter of
 *                the respective DTC.
 *
 * \param[in]     FaultPendingCounterIndex
 *                Index to array FaultPendingCounter.
 *                The Index must be in range [1..DEM_CFG_MAX_NUMBER_FAULT_PENDING_DTCS[.
 * \return        Memory independent fault pending counter
 *
 * \pre           -
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DTC_GetFaultPendingCounter(
  Dem_Cfg_FaultPendingCounterIndexOfEventTableType FaultPendingCounterIndex
  );
  
/* ****************************************************************************
 * Dem_DTC_ResetFaultPendingCounter
 *****************************************************************************/
/*!
 * \brief         Reset the memory independent fault pending counter of 
 *                the respective DTC.
 *
 * \details       Reset the memory independent fault pending counter of 
 *                the respective DTC.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           Feature memory independent fault pending counter is supported.
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DTC_ResetFaultPendingCounter(
  Dem_EventIdType EventId
  );

/* ****************************************************************************
 * Dem_DTC_UpdateMemIndependentCycleCounter
 *****************************************************************************/
/*!
 * \brief         Update the memory dependent cycle counter if event is tested
 *                failed for the first time in operation cycle.
 *
 * \details       Update the failed cycle and fault pending counter if event 
 *                is tested failed for the first time in operation cycle.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     UpdateFlags
 *                DTC trigger of this event from failed report.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_UpdateMemIndependentCycleCounter(
  Dem_EventIdType  EventId,
  Dem_Cfg_StorageTriggerType UpdateFlags
  );

 /* ****************************************************************************
 * Dem_DTC_RetryStorage
 *****************************************************************************/
 /*!
 * \brief         Test if storage shall be retried for event.
 *
 * \details       Test if storage shall be retried for event.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE
 *                Retry storage precondition fulfilled
 * \return        FALSE
 *                Retry storage precondition not fulfilled
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_RetryStorage(
  Dem_EventIdType EventId
);

/* ****************************************************************************
 * Dem_DTC_Cleared_Internal
 *****************************************************************************/
/*!
 * \brief         Clears a DTC
 *
 * \details       Clears a DTC
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
Dem_DTC_Cleared_Internal(
CONST(Dem_EventIdType, AUTOMATIC)  EventId
);

#if (DEM_FEATURE_SUPPORT_EVENTCOMBINATION == STD_ON)
/* ****************************************************************************
 * Dem_DTC_SetCombinedGroupUDSStatus
 *****************************************************************************/
/*!
 * \brief         Set current status of the combined group
 *
 * \details       -
 *
 * \param[in]     GroupId
 *                Unique handle of the combined group
 * \param[in]     Status
 *                New status of the combined group
 *
 * \pre           -
 * \config        DEM_FEATURE_SUPPORT_EVENTCOMBINATION == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_SetCombinedGroupUDSStatus(
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC) GroupId,
  CONST(uint8, AUTOMATIC) Status
  );
#endif

/* ****************************************************************************
 * Dem_DTC_InitCombinedGroupProcessed()
 *****************************************************************************/
/*!
 * \brief         Clear the bitfield of processed Combined DTC groups array.
 *
 * \details       Clear the bitfield of processed Combined DTC groups array.
 *
 * \param[in]     ProcessedCombinedDTCGroup
 *                Bitfield for Combined Groups
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_InitCombinedGroupProcessed(
VAR(Dem_Cfg_ProcessedCombinedDTCGroupType, AUTOMATIC) ProcessedCombinedDTCGroup
);

/* ****************************************************************************
 * Dem_DTC_SetCombinedGroupProcessed
 *****************************************************************************/
/*!
 * \brief         Marks the combined group as processed for
 *               given bitfield.
 *
 * \details       Marks the combined group as processed for
 *               given bitfield
 *
 * \param[in]     GroupId
 * \param[in]     ProcessedCombinedDTCGroup
 *                Bitfield for Combined Groups
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_SetCombinedGroupProcessed(
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC) GroupId,
  VAR(Dem_Cfg_ProcessedCombinedDTCGroupType, AUTOMATIC) ProcessedCombinedDTCGroup
  );


/* ****************************************************************************
 * Dem_DTC_TestCombinedGroupProcessed
 *****************************************************************************/
/*!
 * \brief         Tests whether the combined group was already processed for
 *               given bitfield.
 *
 * \details       Tests whether the combined group was already processed for
 *               given bitfield.
 *
 * \param[in]     GroupId
 * \param[in]     ProcessedCombinedDTCGroup
 *                Bitfield for Combined Groups
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_TestCombinedGroupProcessed(
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC) GroupId,
  CONST(Dem_Cfg_ProcessedCombinedDTCGroupType, AUTOMATIC) ProcessedCombinedDTCGroup
  );


#if (DEM_FEATURE_SUPPORT_EVENTCOMBINATION == STD_ON)
/* ****************************************************************************
 * Dem_DTC_CalculateCombineGroupUdsStatus
 *****************************************************************************/
/*!
 * \brief         Gets the combined event group status of a combined event
 *
 * \details       This calculates the logical OR of all subevent status bytes.
 *                Combined event status bytes only change on the main function,
 *                so no critical section is required from the main function.
 *
 * \param[in]     GroupId
 *                Unique identifier of the combined event group
 *
 * \return        'Raw' combined UDS status of the DTC consisting of the
 *                logical OR of the UDS status of all its events.
 *
 *
 * \pre           -
 * \config        DEM_FEATURE_SUPPORT_EVENTCOMBINATION == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(Dem_DTC_UDSStatusType, DEM_CODE)
Dem_DTC_CalculateCombineGroupUdsStatus(
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC)  GroupId
  );
#endif

#if (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
/* ****************************************************************************
 * Dem_DTC_CalculateCombinedGroupType2_ExternalUdsStatus
 *****************************************************************************/
/*!
 * \brief         Gets the combined event group status of a combined event
 *                taking visibility of Confirmed and Wir bits into consideration.
 *
 * \details       Gets the combined event group status of a combined event
 *                taking visibility of Confirmed and Wir bits into consideration.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        Combined UDS status of the DTC consisting of the
 *                logical OR of the UDS status of all its events. The visibility
 *                of Confirmed and Wirt bits are also taken into consideration.
 *
 *
 * \pre           OBDII or User controlled WIR bit enabled
 * \config        DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(Dem_DTC_UDSStatusType, DEM_CODE)
Dem_DTC_CalculateCombinedGroupType2_ExternalUdsStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

/* ****************************************************************************
 * Dem_DTC_ApplyCombinedStatus
 *****************************************************************************/
/*!
 * \brief         Apply interdependent status bits on a combined status
 *
 * \details       This function corrects the status byte inconsistencies
 *                resulting from event combination, according to the Autosar
 *                specification.
 *
 * \param[in]     DtcStatus
 *                Unmodified DTC status byte
 *
 * \return        The resulting DTC status
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTC_UDSStatusType, DEM_CODE)
Dem_DTC_ApplyCombinedStatus(
  CONST(Dem_DTC_UDSStatusType, AUTOMATIC)  DtcStatus
  );


/* ****************************************************************************
 * Dem_DTC_GenerateExternalOnlyStatus
 *****************************************************************************/
/*!
 * \brief         Apply correction term for DTC status modification
 *
 * \details       This function applies a filter to the DTC status byte to set
 *                bits that are forced to true by different mechanisms than
 *                event status modification.
 *                Also, status bits not contained in the status availability
 *                mask are masked out.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     DtcStatus
 *                Unmodified DTC status byte
 *
 * \return        The resulting DTC status
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(Dem_DTC_UDSStatusType, DEM_CODE)
Dem_DTC_GenerateExternalOnlyStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_DTC_UDSStatusType, AUTOMATIC)  DtcStatus
  );

#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF)
/* ****************************************************************************
 * Dem_DTC_AgingCycle
 *****************************************************************************/
/*!
 * \brief         Processes the aging cycle for a DTC
 *
 * \details       Processes the aging cycle for a DTC
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     CycleCounter
 *                Current cycle count
 * \param[in]     MemoryIndex
 *                Handle of the memory block
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_AgingCycle(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint16, AUTOMATIC)  CycleCounter,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  );
#endif

#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF)
/* ****************************************************************************
 * Dem_DTC_Aged
 *****************************************************************************/
/*!
 * \brief         Completes aging of a DTC.
 *
 * \details       Depending on configuration this will clear the DTC's memory
 *                entry, or simply mark it as 'aged'.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     MemoryIndex
 *                Handle of the memory block
 * \param[in]     SuppressNotifications
 *                Suppress DTC and Event Status Change Notifications
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_Aged(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex,
  CONST(boolean, AUTOMATIC)  SuppressNotifications
  );
#endif

/* ****************************************************************************
 * Dem_DTC_ClearOBDFreezeFrame
 *****************************************************************************/
/*!
 * \brief         Clears OBD FreezeFrame data
 *
 * \details       Clears OBD FreezeFrame data if stored by passed event and 
 *                if ObdII is enabled
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
Dem_DTC_ClearOBDFreezeFrame(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

#if ((DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_ON) || (DEM_CFG_SUPPORT_TRIGGER_PASSED ==STD_ON))
/* ****************************************************************************
 * Dem_DTC_Passed_CalcDTCEffects
 *****************************************************************************/
/*!
 * \brief         Calculate DTC triggers on 'Passed' status report.
 *
 * \details       If the DTC has a combined group calculate the DTC triggers
 *                from DTC's changed UDS status byte. If the DTC has no
 *                combined group, the DTC trigger equals event triggers.
 *
 * \param[in,out] DTCContext
 *                DTC processing context. This function updates the DTC trigger
 *                member.
 * \param[in]     EventEffects
 *                Event trigger mask holding the relevant event status changes.
 *
 * \pre           -
 *
 * \config        DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_ON
 *                || DEM_CFG_SUPPORT_TRIGGER_PASSED == STD_ON
 *
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_Passed_CalcDTCEffects(
  CONSTP2VAR(Dem_DTC_ContextType, AUTOMATIC, AUTOMATIC) DTCContext,
  CONST(Dem_Cfg_StorageTriggerType, AUTOMATIC) EventEffects
  );
#endif

/* ****************************************************************************
 * Dem_DTC_InitMemIndependentCycleCounterDataNv
 *****************************************************************************/
/*!
 * \brief         Initializes memory independent cycle counter Nv data.
 *
 * \details       Initializes memory independent cycle counter Nv data to zero.
 *
 * \pre           Feature memory independent cycle counter is supported
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_InitMemIndependentCycleCounterDataNv(
  void
);

/* ****************************************************************************
 * Dem_DTC_Cleared
 *****************************************************************************/
/*!
 * \brief         Clears an event from the given origin memory, if allowed
 *
 * \details       This function clears an event based on the return value of
 *                its 'clear event allowed' callback.
 *                InitMonitor notifications are called also when the event is
 *                not allowed to be cleared.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE
 *                The event was cleared
 * \return        FALSE
 *                The event was not cleared
 *
 * \pre           RTE must be started
 * \config        -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_Cleared(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF) \
 && (DEM_CFG_SUPPORT_DISPLACEMENT == STD_ON)
/* ****************************************************************************
 * Dem_DTC_Displaced
 *****************************************************************************/
/*!
 * \brief         Updates the status of a displaced DTC
 *
 * \details       Updates the status of a displaced DTC
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF &&
 *                DEM_CFG_SUPPORT_DISPLACEMENT == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_Displaced(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_ON)
/* ****************************************************************************
 * Dem_DTC_CustomizedDisplacement
 *****************************************************************************/
/*!
 * \brief         Updates the status of a displaced DTC
 *
 * \details       Updates the status of a displaced DTC
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     SI30
 *                Status Indicator byte of the displaced event
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_CustomizedDisplacement(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  SI30
  );
#endif

/* ****************************************************************************
 * Dem_DTC_GetFaultDetectionCounter
 *****************************************************************************/
/*!
 * \brief         Gets the FaultDetectionCounter (FDC) of a DTC
 *
 * \details       This function retrieves the DTC's FDC. If the DTC has a
 *                combined event group, the largest FDC of all subevents is
 *                returned.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[out]    FaultDetectionCounter
 *                Pointer to receive the FDC value
 *
 * \return        The current FDC of the event or group.
 *
 * \pre           RTE must be started
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_DTC_GetFaultDetectionCounter(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONSTP2VAR(sint8, AUTOMATIC, DEM_APPL_DATA)  FaultDetectionCounter
  );

#if ( (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON) \
   && ( ( ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_MAX_FDC_DURING_CURRENT_CYCLE == STD_ON) ) \
     || ((DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF) && (DEM_CFG_DATA_MAX_FDC_SINCE_LAST_CLEAR == STD_ON) ) ) )
/* ****************************************************************************
 * Dem_DTC_CombinedGroupGetFDCMax
 *****************************************************************************/
/*!
 * \brief         Calculates the maximum fault detection counter this cycle of
 *                a combined event
 *
 * \details       This function iterates through all sub-events, and takes the
 *                largest maximum fault detection counter to represent the
 *                combined maximum FDC.
 *
 * \param[in]     GroupId
 *                Unique identifier of the combined event group
 *
 * \return        The maximum FDC value
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON
 *                && ( ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
 *                && DEM_CFG_DATA_MAX_FDC_DURING_CURRENT_CYCLE == STD_ON)
 *                || (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF && DEM_CFG_DATA_MAX_FDC_SINCE_LAST_CLEAR == STD_ON) )
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE for different events
 *****************************************************************************/
DEM_LOCAL FUNC(sint8, DEM_CODE)
Dem_DTC_CombinedGroupGetFDCMax(
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC)  GroupId
  );
#endif

/* ****************************************************************************
 * Dem_DTC_GetDTCStatus
 *****************************************************************************/
/*!
 * \brief         Gets the UDS status byte of a DTC
 *
 * \details       This function retrieves the event's status byte for normal
 *                events, and the combined event group's status byte for
 *                combined events.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        The status byte relevant for the event or group
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTC_UDSStatusType, DEM_CODE)
Dem_DTC_GetDTCStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

/* ****************************************************************************
 * Dem_DTC_GetExternalDTCStatus
 *****************************************************************************/
 /*!
 * \brief         Gets the externally visible UDS status byte of a DTC
 *
 * \details       This function retrieves the external event's status byte for 
 *                normal events, and the combined event group's status byte for
 *                combined events.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        External DTC UDS status
 *               
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(Dem_DTC_UDSStatusType, DEM_CODE)
Dem_DTC_GetExternalDTCStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
);

/* ****************************************************************************
 * Dem_DTC_RetrieveStatus
 *****************************************************************************/
/*!
 * \brief         Retrieve the Combined DTC status or the Event's status.
 *
 * \details       This function retrieves the Combined DTC status or event's
 *                status according to configuration.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        The status byte relevant for the event or DTC.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTC_UDSStatusType, DEM_CODE)
Dem_DTC_RetrieveStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

#if (DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON)
/* ****************************************************************************
 * Dem_DTC_ResetDtcSuppression
 *****************************************************************************/
/*!
 * \brief         Marks an event's DTC un-suppressed
 *
 * \details       This function sets an event's DTC un-suppressed.
 *                For combined events, it does not matter which sub-event is
 *                passed to this function.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_ResetDtcSuppression(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

#if (DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON)
/* ****************************************************************************
 * Dem_DTC_ChangeDtcSuppression
 *****************************************************************************/
/*!
 * \brief         Change suppression of a DTC
 *
 * \details       This function suppresses the DTC or releases its suppression.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \param[in]     SuppressionStatus
 *                TRUE: Suppress the DTC
 *                FALSE: Lift suppression of the DTC
 *
 * \return        E_OK
 *                The suppression was changed successfully
 * \return        E_NOT_OK
 *                The request was rejected because of invalid event
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_DTC_ChangeDtcSuppression(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(boolean, AUTOMATIC)  SuppressionStatus
  );
#endif

/* ****************************************************************************
 * Dem_DTC_TestDtcAvailable
 *****************************************************************************/
/*!
 * \brief         Tests if a DTC is available based on runtime calibration
 *
 * \details       Tests if a event or combined event group is available based
 *                on runtime calibration. Any event of a combined group can be
 *                passed to this function.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE
 *                The event or combined event group is available
 * \return        FALSE
 *                The event or combined event group is not available
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_TestDtcAvailable(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );



/* ****************************************************************************
* Dem_DTC_TestSuppressionByRepresentiveEvent
*****************************************************************************/
/*!
* \brief         Tests if a representive event of a DTC is suppressed/available,
*                based on runtime calibration
*
* \details       Tests if the repreentive event is suppressed/available based
*                on runtime calibration. Any event of a combined DTC can be
*                passed to this function.
*
* \param[in]     EventId
*                Unique handle of the Event.
*                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
*
* \return        TRUE
*                The event or combined event group is available
* \return        FALSE
*                The event or combined event group is not available
*
* \pre           -
*
* \context       TASK|ISR2
* \synchronous   TRUE
* \reentrant     TRUE
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_TestSuppressionByRepresentiveEvent(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
);



/* ****************************************************************************
 * Dem_DTC_TestDtcAvailableInVariant
 *****************************************************************************/
/*!
 * \brief         Tests if a DTC is available based on the PB-S variant
 *
 * \details       For normal events, this function simply looks up the event
 *                configuration. A combined event group is available only if at
 *                least one sub-event is available in the active variant.
 *                Any event of a combined group can be passed to this function.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE
 *                The event or combined event group is available in the selected
 *                variant
 * \return        FALSE
 *                The event or combined event group is not available in the
 *                selected variant
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_TestDtcAvailableInVariant(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

/* ****************************************************************************
 * Dem_DTC_TestDtcSuppression
 *****************************************************************************/
/*!
 * \brief         Tests if a DTC is suppressed for reporting API
 *
 * \details       Tests if an event or combined event group is suppressed for
 *                reporting API. Any event of a combined group can be passed
 *                to this function.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE
 *                The event or combined event group is suppressed
 * \return        FALSE
 *                The event or comined event group is not suppressed
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_TestDtcSuppression(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

/* ****************************************************************************
 * Dem_DTC_TestSuppressionOnDtcRetrieval
 *****************************************************************************/
/*!
 * \brief         Tests a DTC can be considered for reporting API
 *
 * \details       Tests all options due to which an event or combined event group
 *                has to be excluded from reporting API, based on the combined event group
 *                for combined events type 1 and type 2. Any event of a combined
 *                group can be passed to this function.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE
 *                The event or combined event group is currently suppressed
 * \return        FALSE
 *                The event or combined event group is currently not suppressed
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_TestSuppressionOnDtcRetrieval(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

#if (DEM_FEATURE_NEED_AGING_TRIGGER_CYCLE == STD_ON) && (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF)
/* ****************************************************************************
 * Dem_DTC_OpCycleEnd_Aging
 *****************************************************************************/
/*!
 * \brief         Processes aging at the end of the DTC's operation cycle
 *
 * \details       Processes aging at the end of the DTC's operation cycle.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     OldUdsStatus
 *                Dtc/Event status before cycle restart
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_AGING_TRIGGER_CYCLE == STD_ON)
 *                 && (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF)
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_OpCycleEnd_Aging(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_DTC_UDSStatusType, AUTOMATIC)  OldUdsStatus
  );
#endif

/* ****************************************************************************
 * Dem_DTC_GetQualifyStatus
 *****************************************************************************/
/*!
 * \brief         Get the qualification status of the DTC.
 *
 * \details       Combines and returns the qualification status of all subevents
 *                of a combined event or just the event qualification state if
 *                event is not a combined event.
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
DEM_LOCAL FUNC(Dem_DTC_UDSStatusType, DEM_CODE)
Dem_DTC_GetQualifyStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/* ****************************************************************************
 * Dem_DTC_TestStatusForPermanentStorage
 *****************************************************************************/
/*!
 * \brief         Test if the DTC UDS status allows for the storage of
 *                a permanent DTC.
 *
 * \details       Test if the DTC UDS status allows for the storage of
 *                a permanent DTC. For B1 DTC addtionally the B1 Counter is checked.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE if the event can store a permanent DTC
 *                FALSE if the event can not store a permanent DTC
 *
 * \pre           EventId must be a class A or B1 DTC for WWHOBD configurations.
 *
 * \config        DEM_CFG_SUPPORT_PERMANENT == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_DTC_TestStatusForPermanentStorage(
  CONST(Dem_EventIdType, AUTOMATIC) EventId
);
#endif

/* ****************************************************************************
 * Dem_DTC_TestEventStoresPermanentDTC
 *****************************************************************************/
/*!
 * \brief         Test if the (event) configuration allows to store a permanent DTC.
 *
 * \details       Test if the (event) configuration allows to store a permanent DTC.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE if the event can store a permanent DTC
 *                FALSE if the event can not store a permanent DTC
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_DTC_TestEventStoresPermanentDTC(
CONST(Dem_EventIdType, AUTOMATIC) EventId
);

/* ****************************************************************************
 * Dem_DTC_TestPfcRequired
 *****************************************************************************/
/*!
 * \brief         Tests whether evaluation of the permanent fault condition
 *                is required.
 *
 * \details       Tests whether evaluation of the permanent fault condition
 *                is required.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE
 *                Evaluation of the permanent fault condition is required
 *                for event.
 * \return        FALSE
 *                Evaluation of the permanent fault condition is not required
 *                for event.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_TestPfcRequired(
  CONST(Dem_EventIdType, AUTOMATIC) EventId
  );

/* ****************************************************************************
 * Dem_DTC_TestStoredStatus
 *****************************************************************************/
/*!
 * \brief         Tests whether a memory entry exists for the DTC
 *
 * \details       Tests whether a memory entry exists for the DTC.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE
 *                Memory entry for DTC exists.
 * \return        FALSE
 *                Memory entry for DTC does not exist.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
  Dem_DTC_TestStoredStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

/* ****************************************************************************
 * Dem_DTC_InitDTCContext
 *****************************************************************************/
/*!
 * \brief         Initialize context of DTC's status report processing.
 *
 * \details       -
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[out]    DTCContext
 *                DTC processing context
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_InitDTCContext(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONSTP2VAR(Dem_DTC_ContextType, AUTOMATIC, AUTOMATIC) DTCContext
  );

/* ****************************************************************************
 * Dem_DTC_CalculateDTCStatus
 *****************************************************************************/
/*!
 * \brief         Update of DTC UDS status byte
 *
 * \details       If the DTC has a combined group, the UDS status is calculated
 *                from the UDS status of all its subevents. Without combined
 *                group the DTC status equals the event status.
 *
 * \param[in,out] DTCContext
 *                DTC processing context
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_CalculateDTCStatus(
  CONSTP2VAR(Dem_DTC_ContextType, AUTOMATIC, AUTOMATIC) DTCContext
  );

/* ****************************************************************************
 * Dem_DTC_CalculateFailedEffects
 *****************************************************************************/
/*!
 * \brief         Calculate storage independent DTC triggers on 'Failed'
 *                status report.
 *
 * \details       If the DTC has a combined group calculate the storage independent
 *                DTC triggers from DTC's changed UDS status byte. If the DTC
 *                has no combined group the DTC trigger equals event triggers.
 *
 * \param[in,out] DTCContext
 *                DTC processing context. This function updates the DTC trigger
 *                member.
 * \param[in]     EventEffects
 *                Event trigger mask holding the relevant event status changes.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_CalculateFailedEffects(
  CONSTP2VAR(Dem_DTC_ContextType, AUTOMATIC, AUTOMATIC) DTCContext,
  CONST(Dem_Cfg_StorageTriggerType, AUTOMATIC)  EventEffects
  );

/* ****************************************************************************
 * Dem_DTC_CalculateFailedEffects_OnStorage
 *****************************************************************************/
/*!
 * \brief         Calculate storage dependent DTC triggers on 'Failed'
 *                status report.
 *
 * \details       If the DTC has a combined group calculate the storage dependent
 *                DTC triggers from DTC's changed UDS status byte. If the DTC
 *                has no combined group the DTC trigger equals event triggers.
 *
 * \param[in,out] DTCContext
 *                DTC processing context. This function updates the DTC trigger
 *                member.
 * \param[in]     EventEffects
 *                Event trigger mask holding the relevant event status changes.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_CalculateFailedEffects_OnStorage(
  CONSTP2VAR(Dem_DTC_ContextType, AUTOMATIC, AUTOMATIC) DTCContext,
  CONST(Dem_Cfg_StorageTriggerType, AUTOMATIC)  EventEffects
  );

/* ****************************************************************************
 * Dem_DTC_ProcessFailedEffects
 *****************************************************************************/
/*!
 * \brief         Process DTC triggers on 'Failed' status report.
 *
 * \details       Set internal state of the DTC to 'stored'.
 *
 * \param[in]     DTCContext
 *                DTC processing context
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_ProcessFailedEffects(
  CONSTP2CONST(Dem_DTC_ContextType, AUTOMATIC, AUTOMATIC) DTCContext
  );

/* ****************************************************************************
 * Dem_DTC_Passed_ProcessDTCEffects
 *****************************************************************************/
/*!
 * \brief         Process DTC triggers on 'Passed' status report.
 *
 * \details       Process DTC triggers on 'Passed' status report.
 *
 * \param[in,out] EventContext
 *                Event processing context
 * \param[in]     DTCContext
 *                DTC processing context
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_Passed_ProcessDTCEffects(
  CONSTP2VAR(Dem_Event_ContextType, AUTOMATIC, AUTOMATIC) EventContext,
  CONSTP2CONST(Dem_DTC_ContextType, AUTOMATIC, AUTOMATIC)  DTCContext
  );

/* ****************************************************************************
 * Dem_DTC_ProcessStorage
 *****************************************************************************/
/*!
 * \brief         Process Dtc storage into event memory
 *
 * \details       Processes Dtc storage into event memory and triggers
 *                updating the stored data.
 *
 * \param[in,out] EventContext
 *                Event processing context
 * \param[in,out] DTCContext
 *                DTC processing context
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_ProcessStorage(
  CONSTP2VAR(Dem_Event_ContextType, AUTOMATIC, AUTOMATIC) EventContext,
  CONSTP2VAR(Dem_DTC_ContextType, AUTOMATIC, AUTOMATIC) DTCContext
  );

/* ****************************************************************************
 * Dem_DTC_ResetFdcToc
 *****************************************************************************/
/*!
 * \brief         Resets Fdc trip flag for the DTC
 *
 * \details       Resets Fdc trip flag of the DTC in the DTC internal status
 *                field.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_ResetFdcToc(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF) && \
    ((DEM_CFG_SUPPORT_TRIGGER_FDC_FIRST_IN_CYCLE == STD_ON) || (DEM_CFG_STORAGE_AT_FDC == STD_ON))
/* ****************************************************************************
 * Dem_DTC_FdcTrip
 *****************************************************************************/
/*!
 * \brief         Updates event data due to exceeding a FDC threshold
 *
 * \details       Updates event data due to exceeding a FDC threshold
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF &&
 *                (DEM_CFG_SUPPORT_TRIGGER_FDC_FIRST_IN_CYCLE == STD_ON ||
 *                 DEM_CFG_STORAGE_AT_FDC == STD_ON)
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_FdcTrip(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_ON)
/* ****************************************************************************
 * Dem_DTC_CustomizedFdcTrip
 *****************************************************************************/
/*!
 * \brief         Updates event data due to exceeding a FDC threshold
 *
 * \details       Updates event data due to exceeding a FDC threshold
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     TCTOC
 *                Flag to mark if the event was already tested this cycle
 * \param[in]     FdcThresholdExceeded
 *                FDC Storage threshold was exceeded
 * \param[in]     FdcMaximumExceeded
 *                FDC Maximum (this cycle) was exceeded
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_CustomizedFdcTrip(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(boolean, AUTOMATIC)  TCTOC,
  CONST(boolean, AUTOMATIC)  FdcThresholdExceeded,
  CONST(boolean, AUTOMATIC)  FdcMaximumExceeded
  );
#endif

#if ((DEM_CFG_DATA_MAX_FDC_SINCE_LAST_CLEAR == STD_ON) \
      && (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF))
/* ****************************************************************************
 * Dem_DTC_UpdateFdcMax
 *****************************************************************************/
/*!
 * \brief         Update event data 'maximum FDC since last clear'
 *
 * \details       Update event data 'maximum FDC since last clear'
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 * \config        DEM_CFG_DATA_MAX_FDC_SINCE_LAST_CLEAR == STD_ON
 *                && DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_UpdateFdcMax(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
/* ****************************************************************************
 * Dem_DTC_Disconnect
 *****************************************************************************/
/*!
 * \brief         Disconnects a DTC
 *
 * \details       Disconnect the DTC's event. If the DTC has a combined group,
 *                disconnect all its subevents.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 *
 * \config        DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
  Dem_DTC_Disconnect(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
/* ****************************************************************************
 * Dem_DTC_Reconnect
 *****************************************************************************/
/*!
 * \brief         Reconnects a DTC
 *
 * \details       Reconnect the DTC's event. If the DTC has a combined group,
 *                reconnect all its subevents.
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
  Dem_DTC_Reconnect(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
/* ****************************************************************************
 * Dem_DTC_TestRemainingEventforDtc
 *****************************************************************************/
/*!
 * \brief         For Stored DTCs having a combined group, test if another event
 *                is available beside the event to set unavailable.
 *
 * \details       -
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE
 *                Another event is still available
 *                FALSE
 *                All events are now unavailable (DTC is now unavailable)
 *
 * \pre           -
 *
 * \config        DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_TestRemainingEventforDtc(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

#if (DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON)
/* ****************************************************************************
 ! Dem_DTC_GetWIRStatus
 *****************************************************************************/
/*!
 * \brief         Get the user controlled WIR status
 *
 * \details       -
 *
 * \param[in]     EventId
 *                Unique handle of the Event
 *
 * \return        TRUE
 *                User controlled WIR bit is set
 *
 * \return        FALSE
 *                User controlled WIR bit is not set
 *
 * \config        DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_GetWIRStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

#endif

#if (DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON)
/* ****************************************************************************
 ! Dem_DTC_SetWIRStatus
 *****************************************************************************/
/*!
 * \brief         Sets or resets the WIR status bit manually
 *
 * \details       Sets or resets the WIR status bit manually
 *
 * \param[in]     EventId
 *                Unique handle of the Event
 *
 * \param[in]     WIRStatus
 *                TRUE:  Latch WIR-bit to TRUE
 *                FALSE: Release the latch
 *
 * \return        E_OK
 *                Request processed successfully
 *
 * \return        E_NOT_OK
 *                The request was rejected due to variant coding
 *
 * \config        DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_DTC_SetWIRStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(boolean, AUTOMATIC) WIRStatus
  );
#endif

#if DEM_FEATURE_NEED_OBD == STD_ON
/* ****************************************************************************
 * Dem_DTC_CycleQualifyDcy
 *****************************************************************************/
/*!
 * \brief         Forward application of OBD driving cycle qualification on DTC.
 *
 * \details       Forward application of OBD driving cycle qualification on DTC.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_OBD == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_CycleQualifyDcy(
  void
  );
#endif

/* ****************************************************************************
 * Dem_DTC_OpCycle
 *****************************************************************************/
/*!
 * \brief         Updates the DTC and its sub-events due to operation cycle change.
 *
 * \details       -
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
Dem_DTC_OpCycle(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  CycleStatus
  );

/* ****************************************************************************
 * Dem_DTC_Init
 *****************************************************************************/
/*!
 * \brief         Initializes the DTC status processing sub-component
 *
 * \details       Initializes the DTC status processing sub-component
 *
 * \pre           May be called only during module initialization
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_Init(
  void
  );

/* ****************************************************************************
 * Dem_DTC_PreInit
 *****************************************************************************/
/*!
 * \brief         Pre-Initializes the Dem DTCs
 *
 * \details       Pre-Initializes the Dem DTCs
 *
 * \pre           May be called only during module pre-initialization
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_PreInit(
  void
  );

/* ****************************************************************************
 * Dem_DTC_InitQualification
 *****************************************************************************/
/*!
 * \brief         Initializes the qualification states derived from DTC storage
 *
 * \details       Initializes the qualification states derived from DTC storage
 *
 * \pre           May be called only during module initialization
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_InitQualification(
  void
  );

/* ****************************************************************************
 * Dem_DTC_SetAgingCounter
 *****************************************************************************/
/*!
 * \brief         Sets the aging target for the event.
 *
 * \details       Sets the aging target for the event in the respective
 *                array based on the selected aging compliance.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \param[in]     MemoryIndex
 *                Handle of the memory block
 *
 * \param[in]     AgingCounter
 *                The aging counter to be set in the memory entry or array
 *
 * \pre           -
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DTC_SetAgingCounter(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex,
  CONST(uint16, AUTOMATIC) AgingCounter
  );

/* ****************************************************************************
 * Dem_DTC_GetAgingCounter
 *****************************************************************************/
/*!
 * \brief         Gets the aging counter of the event.
 *
 * \details       Gets the aging counter of the event.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        Aging counter of the event.
 *
 * \pre           -
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(uint16, DEM_CODE)
Dem_DTC_GetAgingCounter(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC) MemoryEntryId
  );

#if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON)
/* ****************************************************************************
 * Dem_DTC_TestAndInvalidateAgingCounter
 *****************************************************************************/
/*!
 * \brief         Tests and invalidates aging counter of the event.
 *
 * \details       Tests and invalidates aging counter of the event.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DTC_TestAndInvalidateAgingCounter(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

/* ****************************************************************************
 * Dem_DTC_ResetAging
 *****************************************************************************/
/*!
 * \brief         Reset aging of the event.
 *
 * \details       Reset the ongoing aging process of the event.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_ResetAging(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

#if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON)
/* ****************************************************************************
 * Dem_DTC_GetAgingStatus
 *****************************************************************************/
/*!
 * \brief         Function returns the current aging status of an event.
 *
 * \details       Function returns the current aging status of an event.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        Current aging status of the event.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(Dem_DTC_AgingStatusType, DEM_CODE)
Dem_DTC_GetAgingStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif


#if (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
/* ****************************************************************************
 * Dem_DTC_SetQualificationProcessedCombinedDTC
 *****************************************************************************/
/*!
 * \brief         Marks the qualification 'processed' for the given combined event.
 *
 * \details       Marks the qualification 'processed' for the given combined event.
 *
 * \param[in]     GroupId
 *                Unique identifier of the combined event group
 * \pre           -
 * \config        DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_SetQualificationProcessedCombinedDTC(                                                                                    /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC) GroupId
  );
#endif

/* ****************************************************************************
 * Dem_DTC_QualifySingleDTC
 *****************************************************************************/
/*!
 * \brief         Make CDTC and WIR bit visible without DCY qualification
 *
 * \details       Make CDTC and WIR bit visible without DCY qualification
 *
 * \param[in]     EventId
 *                Unique handle of the event
 *
 * \pre           OBD freeze frame is stored at confirmation and 
 *                visibility is suppressed until qualified confirmed
 * \pre           OBD freeze frame is already visible
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_QualifySingleDTC(                                                                                    /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  const Dem_EventIdType EventId
  );

/* ****************************************************************************
 * Dem_DTC_TestDtcActive
 *****************************************************************************/
/*!
 * \brief         Test whether Dtc is active for J1939 filtering
 *
 * \details       Test whether Dtc is active for J1939 filtering
 *
 * \param[in]     EventId
 *                Unique handle of the event
 * \pre           -
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_TestDtcActive(                                                                                    /* PRQA S 3219 */ /* MD_DEM_14.1_CONFIGURATION_SWITCH */
  const Dem_EventIdType EventId
  );

/* ****************************************************************************
 * Dem_DTC_TestDtcPreviouslyActive
 *****************************************************************************/
/*!
 * \brief         Test whether Dtc is previously active for J1939 filtering
 *
 * \details       Test whether Dtc is previously active for J1939 filtering
 *
 * \param[in]     EventId
 *                Unique handle of the event
 * \pre           -
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_TestDtcPreviouslyActive(                                                                                    /* PRQA S 3219 */ /* MD_DEM_14.1_CONFIGURATION_SWITCH */
  const Dem_EventIdType EventId
  );


/* ****************************************************************************
 * Dem_DTC_GetFormatedDTCByEvent
 *****************************************************************************/
/*!
 * \brief         Provides DTC of an event in requested format.
 *
 * \details       Provides DTC of an event in requested format.
 *
 *
 * \param[in]     EventId
 *                Unique handle of the event
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     DTCFormat
 *                Defines the output-format of the requested DTC
 * \param[out]    DTC
 *                Pointer to receive the DTC number
 *
 * \return        E_OK
 *                DTC returned in requested format
 * \return        E_NOT_OK
 *                Requested DTCFormat not available in configuration or variant
 *
 * \pre           -
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_DTC_GetFormatedDTCByEvent(
  Dem_EventIdType lEventId,
  Dem_DTCFormatType DTCFormat,
  CONSTP2VAR(uint32, AUTOMATIC, DEM_DCM_DATA)  DTC
);

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_DTCIF_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_DTCIF_Interface.h
 *********************************************************************************************************************/
