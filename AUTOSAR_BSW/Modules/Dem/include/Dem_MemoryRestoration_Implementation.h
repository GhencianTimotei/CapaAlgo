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
/*! \addtogroup Dem_MemoryRestoration
 *  \{
 *  \file       Dem_MemoryRestoration_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Implementation of the Memory Restoration subcomponent which restores the status of a memory entry, 
 *              fixes memory entry allocation errors etc.
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_MEMORYRESTORATION_IMPLEMENTATION_H)
#define DEM_MEMORYRESTORATION_IMPLEMENTATION_H

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
#include "Dem_MemoryRestoration_Interface.h"

/* Includes to access public functions belonging to other (top level)/ (logical)/- units to be used by this Unit */
/* ------------------------------------------------------------------------- */
#include "Dem_Core_Interface.h"
#include "Dem_Infrastructure_Interface.h"
#include "Dem_DiagnosticObserver_Interface.h"
#include "Dem_MemoryIF_Interface.h"
#include "Dem_MemState_Interface.h"
#include "Dem_MemoryEntry_Interface.h"
#include "Dem_MemAccess_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DEFINITIONS
 *********************************************************************************************************************/


/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_MemoryRestoration_Private Private Methods
 * \{
 */


#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_ON)
/* ****************************************************************************
 * Dem_MemoryRestoration_RestoreCustomizedStatusBits
 *****************************************************************************/
/*!
 * \brief         Restore status bits and internal status of an event.
 *
 * \details       Restore status bits and internal status of an event.
 *
 * \param[in]     MemoryEntryId
 *                Memory Entry Id of the current memory entry.
 * \param[in]     EventId
 *                EventId stored at the memory index.
 * \param[in]     InternalStatus
 *                Current internal status of the event.
 *
 * \return        Updated value for the internal status.
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_ON)
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Event_InternalStatusType, DEM_CODE)
Dem_MemoryRestoration_RestoreCustomizedStatusBits(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)    MemoryEntryId,
  CONST(Dem_EventIdType, AUTOMATIC)               EventId,
  CONST(Dem_Event_InternalStatusType, AUTOMATIC)  InternalStatus
  );
#endif

#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF)
/* ****************************************************************************
* Dem_MemoryRestoration_RestoreAgingCounter
*****************************************************************************/
/*!
* \brief         Restores the aging counter target of an event.
*
* \details       Restores the aging counter target of an event.
*                Based on current aging cycle value and aging threshold.
*                If aging would take longer than aging threshold defines.
*
* \param[in]     MemoryEntryId
*                Memory Entry Id of the current memory entry.
* \param[in]     MemoryIndex
*                Block Index of the current memory entry.
* \param[in]     EventId
*                EventId stored at the memory index.
*
* \pre           -
* \config        (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF)
*
* \context       TASK
* \synchronous   TRUE
* \reentrant     TRUE
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryRestoration_RestoreAgingCounter(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC) MemoryEntryId,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)       MemoryIndex,
  CONST(Dem_EventIdType, AUTOMATIC)               EventId);
#endif

#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF)
/* ****************************************************************************
 * Dem_MemoryRestoration_RestoreStoredStatusFromEntry
 *****************************************************************************/
/*!
 * \brief         Update the aging status of an event in it's internal status.
 *
 * \details       Update the aging status of an event in it's internal status.
 *
 * \param[in]     MemoryEntryId
 *                Memory Entry Id of the current memory entry.
 * \param[in]     EventId
 *                EventId stored at the memory index.
 * \param[in]     InternalStatus
 *                Current internal status of the event.
 *
 * \return        Updated value for the internal status.
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF)
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Event_InternalStatusType, DEM_CODE)
Dem_MemoryRestoration_RestoreStoredStatusFromEntry(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)    MemoryEntryId,
  CONST(Dem_EventIdType, AUTOMATIC)               EventId,
  CONST(Dem_Event_InternalStatusType, AUTOMATIC)  InternalStatus
  );
#endif


#if ((DEM_CFG_STORAGE_AT_CONFIRMED == STD_ON) && (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF))
/* ****************************************************************************
 * Dem_MemoryRestoration_RestoreStatusBits_OnConfirmedStorage
 *****************************************************************************/
/*!
 * \brief         Restore parts of the UDS status, using redundant data.
 *
 * \details       Restore parts of the UDS status, using redundant data, when
 *                storage happens on confirmed.
 *
 * \param[in]     MemoryEntryId
 *                Memory Entry Id of the current memory entry.
 * \param[in]     EventId
 *                EventId stored at the memory index.
 *
 * \pre           -
 * \config        (DEM_CFG_STORAGE_AT_CONFIRMED == STD_ON) 
 *                &&(DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF)
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryRestoration_RestoreStatusBits_OnConfirmedStorage(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)    MemoryEntryId,
  CONST(Dem_EventIdType, AUTOMATIC)               EventId
  );
#endif


#if ((DEM_CFG_STORAGE_AT_FAILED == STD_ON) && (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF))
/* ****************************************************************************
 * Dem_MemoryRestoration_RestoreStatusBits_OnFailedStorage
 *****************************************************************************/
/*!
 * \brief         Restore parts of the UDS status, using redundant data.
 *
 * \details       Restore parts of the UDS status, using redundant data, when
 *                storage happens on failed.
 *
 * \param[in]     MemoryEntryId
 *                Memory Entry Id of the current memory entry.
 * \param[in]     EventId
 *                EventId stored at the memory index.
 *
 * \pre           -
 * \config        (DEM_CFG_STORAGE_AT_FAILED == STD_ON)
 *                && (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF)
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryRestoration_RestoreStatusBits_OnFailedStorage(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)    MemoryEntryId,
  CONST(Dem_EventIdType, AUTOMATIC)               EventId
  );
#endif


#if ((DEM_CFG_STORAGE_AT_FDC == STD_ON) && (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF))
/* ****************************************************************************
 * Dem_MemoryRestoration_RestoreStatusBits_OnFdcThresholdStorage
 *****************************************************************************/
/*!
 * \brief         Restore parts of the UDS status, using redundant data.
 *
 * \details       Restore parts of the UDS status, using redundant data, when
 *                storage happens at a FDC threshold.
 *
 * \param[in]     MemoryEntryId
 *                Memory Entry Id of the current memory entry.
 * \param[in]     EventId
 *                EventId stored at the memory index.
 *
 * \pre           -
 * \config        (DEM_CFG_STORAGE_AT_FDC == STD_ON)
 *                && (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF)
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryRestoration_RestoreStatusBits_OnFdcThresholdStorage(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)    MemoryEntryId,
  CONST(Dem_EventIdType, AUTOMATIC)               EventId
  );
#endif


#if ((DEM_CFG_STORAGE_AT_PENDING == STD_ON) && (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF))
/* ****************************************************************************
 * Dem_MemoryRestoration_RestoreStatusBits_OnPendingStorage
 *****************************************************************************/
/*!
 * \brief         Restore parts of the UDS status, using redundant data.
 *
 * \details       Restore parts of the UDS status, using redundant data, when
 *                storage happens on pending.
 *
 * \param[in]     MemoryEntryId
 *                Memory Entry Id of the current memory entry.
 * \param[in]     EventId
 *                EventId stored at the memory index.
 *
 * \pre           -
 * \config        (DEM_CFG_STORAGE_AT_PENDING == STD_ON)
 *                && (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF)
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryRestoration_RestoreStatusBits_OnPendingStorage(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)    MemoryEntryId,
  CONST(Dem_EventIdType, AUTOMATIC)               EventId
  );
#endif

/* ****************************************************************************
 * Dem_MemoryRestoration_RestoreStatusBitsFromCFCC
 *****************************************************************************/
/*!
 * \brief         Restore parts of the UDS status from Consecutive Failed
 *                Cycle Counter.
 *
 * \details       Restore parts of the UDS status from Consecutive Failed
 *                Cycle Counter.
 *
 * \param[in]     MemoryEntryId
 *                Memory Entry Id of the current memory entry.
 * \param[in]     EventId
 *                EventId stored at the memory index.
 * \param[in]     EventStatus
 *                Status of the event
 *
 * \return        The updated event status
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL FUNC(uint8, DEM_CODE)
Dem_MemoryRestoration_RestoreStatusBitsFromCFCC(
  Dem_Cfg_MemoryEntryHandleType MemoryEntryId,
  Dem_EventIdType EventId,
  uint8 EventStatus
);

/* ****************************************************************************
 * Dem_MemoryRestoration_RestoreCombinedEventStatusBitsFromEntry
 ****************************************************************************/
/*!
 * \brief         Evaluates primary/secondary memory entry to restore parts of
 *                the UDS status of a combined event.
 *
 * \details       Restores parts of the UDS status of the combined event
 *                that caused storage of the memory entry from root cause
 *                event Id in environmental data.
 *
 * \param[in]     MemoryEntryId
 *                Memory Entry Id of the current memory entry.
 * \param[in]     EventId
 *                EventId stored at the memory index.
 *
 * \config        -
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryRestoration_RestoreCombinedEventStatusBitsFromEntry(
  Dem_Cfg_MemoryEntryHandleType MemoryEntryId,
  Dem_EventIdType EventId
  );

#if ( (DEM_CFG_DATA_ROOTCAUSE_EVENTID == STD_ON) \
    && (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON) \
    && (DEM_CFG_STORAGE_AT_FDC == STD_OFF))
/* ****************************************************************************
 * Dem_MemoryRestoration_RecoverRootCauseEventIdFromSRecs
 *****************************************************************************/
/*!
 * \brief         Retrieves the first RootCauseEventId found in a Snapshot
 *                Record stored in DTC's memory entry.
 *
 * \details       Retrieves a RootCauseEventId that might be stored in 
 *                Snapshot Records of a DTC with a memory entry. It
 *                iterates over all stored Snapshot Records until the first
 *                occurence of the RootCauseEventId.
 *
 * \param[in]     MemoryEntryId
 *                Memory Entry Id of the current memory entry.
 * \param[in]     EventId
 *                EventId stored at the memory index.
 *
 * \return        RootCauseEventId, an invalid Id is returned in case the 
 *                data element could not be found in stored snapshot records.
 *
 * \pre           -
 * \config        DEM_CFG_DATA_ROOTCAUSE_EVENTID == STD_ON &&
 *                DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON &&
 *                DEM_CFG_STORAGE_AT_FDC == STD_OFF
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType , DEM_CODE)
Dem_MemoryRestoration_RecoverRootCauseEventIdFromSRecs(
  Dem_Cfg_MemoryEntryHandleType MemoryEntryId,
  Dem_EventIdType EventId
  );
#endif

#if ( (DEM_CFG_DATA_ROOTCAUSE_EVENTID == STD_ON) \
    && (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON) \
    && (DEM_CFG_STORAGE_AT_FDC == STD_OFF) \
    && ( (DEM_CFG_SUPPORT_USER_ERECS == STD_ON)  \
      || (DEM_CFG_SUPPORT_SRECS == STD_ON)))
/* ****************************************************************************
 * Dem_MemoryRestoration_RecoverRootCauseEventIdFromDID
 *****************************************************************************/
/*!
 * \brief         Retrieves the first RootCauseEventId found in an
 *                Extended Data Record stored in DTC's memory entry.
 *
 * \details       Retrieves a RootCauseEventId that might be stored in an
 *                Extended Data Record of a DTC with a memory entry. It
 *                iterates through all data elements until the first
 *                occurence of the RootCauseEventId.
 *
 * \param[in]     DidIndex
 *                Handle to DID descriptor table
 * \param[in]     IndexedDataRecordBufferInfoPtr
 *                Const Pointer to the indexed extended data record buffer
 *
 * \return        RootCauseEventId, an invalid Id is returned in case the
 *                data element could not be found in DID.
 *
 * \pre           -
 * \config        DEM_CFG_DATA_ROOTCAUSE_EVENTID == STD_ON &&
 *                DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON &&
 *                DEM_CFG_STORAGE_AT_FDC == STD_OFF &&
 *                (DEM_CFG_SUPPORT_USER_ERECS == STD_ON ||
 *                 DEM_CFG_SUPPORT_SRECS == STD_ON)
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(Dem_EventIdType, DEM_CODE)
Dem_MemoryRestoration_RecoverRootCauseEventIdFromDID(
  Dem_Cfg_DidIndexType DidIndex,
  CONSTP2VAR(Dem_MemoryRestoration_IndexedDataRecordBufferInfoType, AUTOMATIC, AUTOMATIC) IndexedDataRecordBufferInfoPtr
  );
#endif

#if ( (DEM_CFG_DATA_ROOTCAUSE_EVENTID == STD_ON) \
    && (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON) \
    && (DEM_CFG_STORAGE_AT_FDC == STD_OFF))
/* ****************************************************************************
 * Dem_MemoryRestoration_RecoverRootCauseEventIdFromERecs
 *****************************************************************************/
/*!
 * \brief         Retrieves the first RootCauseEventId found in Extended Data
 *                Records stored in DTC's memory entry.
 *
 * \details       Retrieves a RootCauseEventId that might be stored in
 *                Extended Data Records of a DTC with a memory entry. It
 *                iterates over all stored Extended Data Records until the first
 *                occurence of the RootCauseEventId.
 *
 * \param[in]     MemoryEntryId
 *                Memory Entry Id of the current memory entry.
 * \param[in]     EventId
 *                EventId stored at the memory index.
 *
 * \return        RootCauseEventId, an invalid Id is returned in case the 
 *                data element could not be found in stored extended data records.
 *
 * \pre           -
 * \config        DEM_CFG_DATA_ROOTCAUSE_EVENTID == STD_ON &&
 *                DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON &&
 *                DEM_CFG_STORAGE_AT_FDC == STD_OFF
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType , DEM_CODE)
Dem_MemoryRestoration_RecoverRootCauseEventIdFromERecs(
  Dem_Cfg_MemoryEntryHandleType MemoryEntryId,
  Dem_EventIdType EventId
  );
#endif

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/

#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_ON)
/* ****************************************************************************
 % Dem_MemoryRestoration_RestoreCustomizedStatusBits
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
DEM_LOCAL_INLINE FUNC(Dem_Event_InternalStatusType, DEM_CODE)
Dem_MemoryRestoration_RestoreCustomizedStatusBits(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Event_InternalStatusType, AUTOMATIC)  InternalStatus
  )
{
  uint8 lEventStatus;
  Dem_Event_InternalStatusType lInternalStatus;

  /* If the entry is aged, clear CDTC bit */
  lEventStatus = Dem_Event_GetUDSStatus(EventId);
  if (DEM_DTC_TEST_PC_STATUS_ADTC(Dem_MemoryEntry_GetPreConfirmedStatus(MemoryEntryId)) == TRUE)
  {
    lEventStatus = Dem_UDSStatus_Reset_CDTC(lEventStatus);
  }
  else
  {
    lEventStatus = Dem_MemoryRestoration_RestoreStatusBitsFromCFCC(MemoryEntryId, EventId, lEventStatus);
  }

  /* Store the modified bits for the event */
  Dem_Event_SetUDSStatus(EventId, lEventStatus);

  /* Mark the event as ACTIVE */
  lInternalStatus = Dem_DTCInternalStatus_SetStoredStatus(InternalStatus, Dem_DTCInternalStatus_StoredStatus_Active);

  return lInternalStatus;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif


#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF)
/* ****************************************************************************
% Dem_MemoryRestoration_RestoreAgingCounter
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
Dem_MemoryRestoration_RestoreAgingCounter(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC) MemoryEntryId,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)       MemoryIndex,
  CONST(Dem_EventIdType, AUTOMATIC)               EventId)
{
  uint16 lAgingTarget;

#if ( ( (DEM_CFG_DATA_CONSECUTIVE_FAILED_CYCLES == STD_ON)  \
      ||((DEM_CFG_DATA_FAULT_PENDING_COUNTER == STD_ON) && (DEM_CFG_SUPPORT_MEM_INDEPENDENT_CYCLE_COUNTERS == STD_OFF))) \
    && (DEM_CFG_AGING_START_TESTS_TFTOC == STD_ON) \
    && (DEM_CFG_AGING_START_TRIGGER_PASSED == STD_OFF) \
    && (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON) )

  if (Dem_MemoryEntry_GetConsecutiveFailedCycleCounter(MemoryEntryId) > 0u)
  {
    Dem_DTC_TestAndInvalidateAgingCounter(EventId);
  }
#endif

  lAgingTarget = Dem_DTC_GetAgingCounter(EventId, MemoryEntryId);
  if ((lAgingTarget <= DEM_OPERATIONCYCLE_CYCLECOUNT_MAX) && (Dem_Cfg_EventSupportAging(EventId)))
  {
    uint16 lAgingCurrent;
    uint8  lAgingThreshold;

    lAgingCurrent   = Dem_OperationCycle_GetCycleCounter(Dem_Cfg_EventAgingCycle(EventId));
    lAgingThreshold = Dem_Cfg_EventAgingTarget(EventId);

    if (Dem_OperationCycle_CycleCountDistance(lAgingCurrent, lAgingTarget) > lAgingThreshold)
    {
      lAgingTarget = Dem_OperationCycle_AddCycleCount(lAgingCurrent, lAgingThreshold);
      Dem_DTC_SetAgingCounter(EventId, MemoryIndex, lAgingTarget);
    }
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif


#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF)
/* ****************************************************************************
 % Dem_MemoryRestoration_RestoreStoredStatusFromEntry
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
DEM_LOCAL_INLINE FUNC(Dem_Event_InternalStatusType, DEM_CODE)
Dem_MemoryRestoration_RestoreStoredStatusFromEntry(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)    MemoryEntryId,
  CONST(Dem_EventIdType, AUTOMATIC)               EventId,
  CONST(Dem_Event_InternalStatusType, AUTOMATIC)  InternalStatus
  )
{
  Dem_Event_InternalStatusType  lReturnValue;
  uint16 lAgingTarget;

  lAgingTarget = Dem_DTC_GetAgingCounter(EventId, MemoryEntryId);
  /* If the memory entry is currently aging, mark the event as AGING */
  if ((lAgingTarget <= DEM_OPERATIONCYCLE_CYCLECOUNT_MAX) || (lAgingTarget == DEM_OPERATIONCYCLE_CYCLECOUNT_LATCHED))
  {
    lReturnValue = Dem_DTCInternalStatus_SetStoredStatus(InternalStatus, Dem_DTCInternalStatus_StoredStatus_Aging);
  }
  else
#if (DEM_CFG_AGING_RETAIN_MEMORY_ENTRY == STD_ON)
  /* Otherwise if aging keeps memory entries intact and the entry is aged, mark the event as AGED */
  if (lAgingTarget == DEM_OPERATIONCYCLE_CYCLECOUNT_AGED)
  {
    lReturnValue = Dem_DTCInternalStatus_SetStoredStatus(InternalStatus, Dem_DTCInternalStatus_StoredStatus_Aged);
  }
  else
#endif /* (DEM_CFG_AGING_RETAIN_MEMORY_ENTRY == STD_ON) */
  /* Otherwise: Mark the event as ACTIVE */
  {
    lReturnValue = Dem_DTCInternalStatus_SetStoredStatus(InternalStatus, Dem_DTCInternalStatus_StoredStatus_Active);
  }

  return lReturnValue;
}
#endif



#if ((DEM_CFG_STORAGE_AT_CONFIRMED == STD_ON) && (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF))
/* ****************************************************************************
 % Dem_MemoryRestoration_RestoreStatusBits_OnConfirmedStorage
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
Dem_MemoryRestoration_RestoreStatusBits_OnConfirmedStorage(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)    MemoryEntryId,
  CONST(Dem_EventIdType, AUTOMATIC)               EventId
  )
{
  /* If the event belongs to a combined group, ignore the event */
# if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  if (DEM_CFG_COMBINED_GROUP_INVALID == Dem_Cfg_EventCombinedGroup(EventId))
# endif
  {
    /* If retaining memory after aging is supported, ignore aged events 
       else process the event */
# if (DEM_CFG_AGING_RETAIN_MEMORY_ENTRY == STD_ON)
    if (Dem_DTC_GetAgingCounter(EventId, MemoryEntryId) != DEM_OPERATIONCYCLE_CYCLECOUNT_AGED)
# endif
    {
      uint8 lEventStatus;
      lEventStatus = Dem_Event_GetUDSStatus(EventId);

      /* Since DTCs are stored only on confirmed, set CDTC and TFSLC bits */
      lEventStatus = Dem_UDSStatus_Set_TFSLC(lEventStatus);
      lEventStatus = Dem_UDSStatus_Set_CDTC(lEventStatus);

      lEventStatus = Dem_MemoryRestoration_RestoreStatusBitsFromCFCC(MemoryEntryId, EventId, lEventStatus);

      /* Store the modified bits for the event */
      Dem_Event_SetUDSStatus(EventId, lEventStatus);
    }
  }
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if ((DEM_CFG_STORAGE_AT_FAILED == STD_ON) && (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF))
/* ****************************************************************************
 % Dem_MemoryRestoration_RestoreStatusBits_OnFailedStorage
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
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryRestoration_RestoreStatusBits_OnFailedStorage(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)    MemoryEntryId,
  CONST(Dem_EventIdType, AUTOMATIC)               EventId
  )
{
  /* If the event belongs to a combined group, ignore the event */
# if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  if (DEM_CFG_COMBINED_GROUP_INVALID == Dem_Cfg_EventCombinedGroup(EventId))
# endif
  {
    uint8 lEventStatus;
    lEventStatus = Dem_Event_GetUDSStatus(EventId);

# if (DEM_CFG_AGING_RETAIN_MEMORY_ENTRY == STD_ON)
    if (Dem_DTC_GetAgingCounter(EventId, MemoryEntryId) != DEM_OPERATIONCYCLE_CYCLECOUNT_AGED)
# endif
    {
      /* Set TFSLC bit */
      lEventStatus = Dem_UDSStatus_Set_TFSLC(lEventStatus);

# if ( (DEM_CFG_DATA_CONSECUTIVE_FAILED_CYCLES == STD_ON) \
    ||((DEM_CFG_DATA_FAULT_PENDING_COUNTER == STD_ON) && (DEM_CFG_SUPPORT_MEM_INDEPENDENT_CYCLE_COUNTERS == STD_OFF)))
      lEventStatus = Dem_MemoryRestoration_RestoreStatusBitsFromCFCC(MemoryEntryId, EventId, lEventStatus);
# else
      /* If event has trip target == 0, set CDTC bit */
      if (Dem_Cfg_EventTripTarget(EventId) == 0u)
      {
        lEventStatus = Dem_UDSStatus_Set_CDTC(lEventStatus);
      }
# endif
    }

    /* Store the modified bits for the event */
    Dem_Event_SetUDSStatus(EventId, lEventStatus);
  }
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if ((DEM_CFG_STORAGE_AT_FDC == STD_ON) && (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF))
/* ****************************************************************************
 % Dem_MemoryRestoration_RestoreStatusBits_OnFdcThresholdStorage
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
Dem_MemoryRestoration_RestoreStatusBits_OnFdcThresholdStorage(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)    MemoryEntryId,
  CONST(Dem_EventIdType, AUTOMATIC)               EventId
  )
{
  /* If the event belongs to a combined group, ignore the event */
# if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  if (DEM_CFG_COMBINED_GROUP_INVALID == Dem_Cfg_EventCombinedGroup(EventId))
# endif
  {
    uint8 lEventStatus;
    lEventStatus = Dem_Event_GetUDSStatus(EventId);

# if (DEM_CFG_AGING_RETAIN_MEMORY_ENTRY == STD_ON)
    if (Dem_DTC_GetAgingCounter(EventId, MemoryEntryId) != DEM_OPERATIONCYCLE_CYCLECOUNT_AGED)
# endif
    {
# if ( (DEM_CFG_DATA_CONSECUTIVE_FAILED_CYCLES == STD_ON) \
   || ((DEM_CFG_DATA_FAULT_PENDING_COUNTER == STD_ON) && (DEM_CFG_SUPPORT_MEM_INDEPENDENT_CYCLE_COUNTERS == STD_OFF)))
      lEventStatus = Dem_MemoryRestoration_RestoreStatusBitsFromCFCC(MemoryEntryId, EventId, lEventStatus);
# elif ((DEM_CFG_DATA_OCCCTR_2BYTE == STD_ON) || (DEM_CFG_DATA_OCCCTR == STD_ON))
      /* If there is an occurrence counter > 0, set TFSLC bit, as we know about some TF 0->1 transitions */
      if (Dem_MemoryEntry_GetOccurrenceCounter(MemoryEntryId) > 0u)
      {
        lEventStatus = Dem_UDSStatus_Set_TFSLC(lEventStatus);
      }
# endif
    }

    /* Store the modified bits for the event */
    Dem_Event_SetUDSStatus(EventId, lEventStatus);
  }
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if ((DEM_CFG_STORAGE_AT_PENDING == STD_ON) && (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF))
/* ****************************************************************************
 % Dem_MemoryRestoration_RestoreStatusBits_OnPendingStorage
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
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryRestoration_RestoreStatusBits_OnPendingStorage(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)    MemoryEntryId,
  CONST(Dem_EventIdType, AUTOMATIC)               EventId
  )
{
  /* If the event belongs to a combined group, ignore the event */
# if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  if (DEM_CFG_COMBINED_GROUP_INVALID == Dem_Cfg_EventCombinedGroup(EventId))
# endif
  {
    uint8 lEventStatus;
    lEventStatus = Dem_Event_GetUDSStatus(EventId);

# if (DEM_CFG_AGING_RETAIN_MEMORY_ENTRY == STD_ON)
    if (Dem_DTC_GetAgingCounter(EventId, MemoryEntryId) != DEM_OPERATIONCYCLE_CYCLECOUNT_AGED)
# endif
    {
      /* Set TFSLC bit */
      lEventStatus = Dem_UDSStatus_Set_TFSLC(lEventStatus);

#if ( (DEM_CFG_DATA_CONSECUTIVE_FAILED_CYCLES == STD_ON) \
   || ((DEM_CFG_DATA_FAULT_PENDING_COUNTER == STD_ON) && (DEM_CFG_SUPPORT_MEM_INDEPENDENT_CYCLE_COUNTERS == STD_OFF)))
      lEventStatus = Dem_MemoryRestoration_RestoreStatusBitsFromCFCC(MemoryEntryId, EventId, lEventStatus);
# else
      /* If event has trip target == 0, set CDTC bit */
      if (Dem_Cfg_EventTripTarget(EventId) == 0u)
      {
        lEventStatus = Dem_UDSStatus_Set_CDTC(lEventStatus);
      }
# endif
    }

    /* Store the modified bits for the event */
    Dem_Event_SetUDSStatus(EventId, lEventStatus);
  }
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

/* ****************************************************************************
 % Dem_MemoryRestoration_RestoreStatusBitsFromCFCC
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
DEM_LOCAL FUNC(uint8, DEM_CODE)
Dem_MemoryRestoration_RestoreStatusBitsFromCFCC(                                                                                 /* PRQA S 3219 */ /* MD_DEM_14.1_CONFIGURATION_SWITCH */
  Dem_Cfg_MemoryEntryHandleType MemoryEntryId,
  Dem_EventIdType EventId,
  uint8 EventStatus
  )
{
  uint8 lEventStatus;

#if ( (DEM_CFG_DATA_CONSECUTIVE_FAILED_CYCLES == STD_ON) \
   || ((DEM_CFG_DATA_FAULT_PENDING_COUNTER == STD_ON) && (DEM_CFG_SUPPORT_MEM_INDEPENDENT_CYCLE_COUNTERS == STD_OFF)))
  uint8 lConsecutiveFailedCycleCounter;

  lEventStatus = EventStatus;
  lConsecutiveFailedCycleCounter = Dem_MemoryEntry_GetConsecutiveFailedCycleCounter(MemoryEntryId);

  /* If consecutive failed cycle counter > 0, set PDTC and TFSLC bit */
  if (lConsecutiveFailedCycleCounter > 0u)
  {
    lEventStatus = Dem_UDSStatus_Set_TFSLC(lEventStatus);
    lEventStatus = Dem_UDSStatus_Set_PDTC(lEventStatus);
  }

  /* If the consecutive failed cycle counter exceeded the trip target, set CDTC bit */
  if (lConsecutiveFailedCycleCounter > Dem_Cfg_EventTripTarget(EventId))
  {
    lEventStatus = Dem_UDSStatus_Set_CDTC(lEventStatus);
    if ( (Dem_Indicator_TestHasIndicator(EventId) == TRUE)
      && (Dem_Cfg_EventHealingTarget(EventId) > 0u) )
    {
      lEventStatus = Dem_UDSStatus_Set_WIR(lEventStatus);
    }
  }
#else
  DEM_IGNORE_UNUSED_ARGUMENT(MemoryEntryId)                                                                                      /* PRQA S 1338, 3112 */ /* MD_MSR_DummyStmt, MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_ARGUMENT(EventId)                                                                                            /* PRQA S 1338, 3112 */ /* MD_MSR_DummyStmt, MD_DEM_14.2 */
  lEventStatus = EventStatus;
#endif
  return lEventStatus;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_MemoryRestoration_RestoreCombinedEventStatusBitsFromEntry
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
Dem_MemoryRestoration_RestoreCombinedEventStatusBitsFromEntry(                                                                   /* PRQA S 3219 */ /* MD_DEM_14.1_CONFIGURATION_SWITCH */
  Dem_Cfg_MemoryEntryHandleType MemoryEntryId,
  Dem_EventIdType EventId
)
{
#if ( (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON) \
     && (DEM_CFG_STORAGE_AT_FDC == STD_OFF) \
     && (DEM_CFG_DATA_ROOTCAUSE_EVENTID == STD_ON) )
# if (DEM_CFG_AGING_RETAIN_MEMORY_ENTRY == STD_ON)
  if (Dem_DTC_GetAgingCounter(EventId, MemoryEntryId) != DEM_OPERATIONCYCLE_CYCLECOUNT_AGED)
# endif
  {
    Dem_EventIdType lRootCauseEventId;

    lRootCauseEventId = Dem_MemoryRestoration_RecoverRootCauseEventIdFromSRecs(MemoryEntryId, EventId);
    if (lRootCauseEventId == DEM_EVENT_INVALID)
    {
      lRootCauseEventId = Dem_MemoryRestoration_RecoverRootCauseEventIdFromERecs(MemoryEntryId, EventId);
    }
    if (lRootCauseEventId != DEM_EVENT_INVALID)
    {
      if ((EventId == lRootCauseEventId)                                                                                         
        || (Dem_Cfg_EventCombinedGroup(EventId) == Dem_Cfg_EventCombinedGroup(lRootCauseEventId)))
      {
        uint8 lRootCauseEventStatus;
        lRootCauseEventStatus = Dem_Event_GetUDSStatus(lRootCauseEventId);
        lRootCauseEventStatus = Dem_UDSStatus_Set_TFSLC(lRootCauseEventStatus);
        /* TNCSLC is reset at initialization of event status later */
#   if (DEM_CFG_STORAGE_AT_CONFIRMED == STD_OFF)
        if (Dem_Cfg_EventTripTarget(lRootCauseEventId) == 0u)
#   endif
        {
          lRootCauseEventStatus = Dem_UDSStatus_Set_CDTC(lRootCauseEventStatus);
        }
        Dem_Event_SetUDSStatus(lRootCauseEventId, lRootCauseEventStatus);
      }
      else
      {
        /* DET: To get this inconsistency, it requires a configuration change without clearing the NV contents */
        Dem_Error_ReportError(DEM_INIT_APIID, DEM_E_INCONSISTENT_STATE);
      }
    }
    else
    {
      /*E.g. RootCauseEventId not configured for DTC, or SRec and ERecs not stored, ...*/
    }
  }
#else
  DEM_IGNORE_UNUSED_ARGUMENT(MemoryEntryId)                                                                                      /* PRQA S 1338, 3112 */ /* MD_MSR_DummyStmt, MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_ARGUMENT(EventId)                                                                                            /* PRQA S 1338, 3112 */ /* MD_MSR_DummyStmt, MD_DEM_14.2 */
#endif
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

#if ( (DEM_CFG_DATA_ROOTCAUSE_EVENTID == STD_ON) \
    && (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON) \
    && (DEM_CFG_STORAGE_AT_FDC == STD_OFF))
/* ****************************************************************************
 % Dem_MemoryRestoration_RecoverRootCauseEventIdFromSRecs
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
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_MemoryRestoration_RecoverRootCauseEventIdFromSRecs(
  Dem_Cfg_MemoryEntryHandleType MemoryEntryId,
  Dem_EventIdType EventId
  )
{
  Dem_EventIdType lRootCauseEventId;
# if (DEM_CFG_SUPPORT_SRECS == STD_ON)
  Dem_Cfg_SnapshotEntry_IterType lSnapshotEntryIter;

  lRootCauseEventId = DEM_EVENT_INVALID;

  /* Find the Record number */
  for (Dem_SnapshotEntry_IteratorInit(EventId, MemoryEntryId, &lSnapshotEntryIter);                                              /* SBSW_DEM_POINTER_FORWARD_STACK */
       Dem_SnapshotEntry_IteratorExists(&lSnapshotEntryIter) == TRUE;                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_SnapshotEntry_IteratorNext(&lSnapshotEntryIter))                                                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    if (Dem_SnapshotEntry_IteratorIsSnapshotRecordStored(&lSnapshotEntryIter) == TRUE)                                            /* SBSW_DEM_POINTER_FORWARD_STACK */
    {
      uint8 lSnapshotEntryIndex;
      Dem_MemoryRestoration_IndexedDataRecordBufferInfoType lIndexedDataRecordBufferInfo;
      Dem_Cfg_EventDidIterType lDidIter;

      lSnapshotEntryIndex = Dem_SnapshotEntry_IteratorGetSnapshotEntryIndex(&lSnapshotEntryIter);                                /* SBSW_DEM_CALL_ITERATOR_POINTER */

      lIndexedDataRecordBufferInfo.SourceBuffer = Dem_MemoryEntry_GetSnapshotRecordDataPtr(MemoryEntryId, lSnapshotEntryIndex);  /* SBSW_DEM_POINTER_WRITE_MEMORYENTRY */
      lIndexedDataRecordBufferInfo.ReadIndex = 0;

      for (Dem_Cfg_EventDidIterInit(EventId, &lDidIter);                                                                         /* SBSW_DEM_POINTER_FORWARD_STACK */
           Dem_Cfg_EventDidIterExists(&lDidIter) == TRUE;                                                                        /* SBSW_DEM_CALL_ITERATOR_POINTER */
           Dem_Cfg_EventDidIterNext(&lDidIter))                                                                                  /* SBSW_DEM_CALL_ITERATOR_POINTER */
      {
        Dem_Cfg_DidIndexType lDidIndex;
        lDidIndex = Dem_Cfg_EventDidIterGet(&lDidIter);                                                                          /* SBSW_DEM_CALL_ITERATOR_POINTER */
        lRootCauseEventId = Dem_MemoryRestoration_RecoverRootCauseEventIdFromDID(lDidIndex, &lIndexedDataRecordBufferInfo);      /* SBSW_DEM_POINTER_WRITE_MEMORYENTRY */

        if (lRootCauseEventId != DEM_EVENT_INVALID)
        {
          /* Found a RootCauseEventId - End Search in other DIDs*/
          break;
        }
      }
    }

    if (lRootCauseEventId != DEM_EVENT_INVALID)
    {
      /* Found a RootCauseEventId - End Search in other SRecs*/
      break;
    }
  }
# else
    DEM_IGNORE_UNUSED_ARGUMENT(MemoryEntryId)                                                                                   /* PRQA S 1338, 3112 */ /* MD_MSR_DummyStmt, MD_DEM_14.2 */
    DEM_IGNORE_UNUSED_ARGUMENT(EventId)                                                                                         /* PRQA S 1338, 3112 */ /* MD_MSR_DummyStmt, MD_DEM_14.2 */
    lRootCauseEventId = DEM_EVENT_INVALID;
# endif
  return lRootCauseEventId;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif

#if ( (DEM_CFG_DATA_ROOTCAUSE_EVENTID == STD_ON) \
    && (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON) \
    && (DEM_CFG_STORAGE_AT_FDC == STD_OFF) \
    && ( (DEM_CFG_SUPPORT_USER_ERECS == STD_ON)  \
      || (DEM_CFG_SUPPORT_SRECS == STD_ON)))
/* ****************************************************************************
 % Dem_MemoryRestoration_RecoverRootCauseEventIdFromDID
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
DEM_LOCAL FUNC(Dem_EventIdType, DEM_CODE)
Dem_MemoryRestoration_RecoverRootCauseEventIdFromDID(
  Dem_Cfg_DidIndexType DidIndex,
  CONSTP2VAR(Dem_MemoryRestoration_IndexedDataRecordBufferInfoType, AUTOMATIC, AUTOMATIC) IndexedDataRecordBufferInfoPtr
  )
{
  Dem_Cfg_DidDataIterType lDataIter;
  Dem_EventIdType lRootCauseEventId;

  lRootCauseEventId = DEM_EVENT_INVALID;

  for (Dem_Cfg_DidDataIterInit(DidIndex, &lDataIter);                                                                            /* SBSW_DEM_POINTER_FORWARD_STACK */
       Dem_Cfg_DidDataIterExists(&lDataIter) == TRUE;                                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_DidDataIterNext(&lDataIter))                                                                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_DataIndexType lDataIndex;
    lDataIndex = Dem_Cfg_DidDataIterGet(&lDataIter);                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */

    if (Dem_Cfg_DataIsStoredInNV(lDataIndex) == TRUE)
    {
      switch (Dem_Cfg_DataCallbackType(lDataIndex))
      {
      case DEM_CFG_DATA_FROM_ROOTCAUSE_EVENTID:
      {
        uint8 lHighByte;
        uint8 lLowByte;
        Dem_EventIdType lEventIdTmp;

        lHighByte = IndexedDataRecordBufferInfoPtr->SourceBuffer[IndexedDataRecordBufferInfoPtr->ReadIndex];
        lLowByte = IndexedDataRecordBufferInfoPtr->SourceBuffer[IndexedDataRecordBufferInfoPtr->ReadIndex + 1u];

        lEventIdTmp = (Dem_EventIdType)(Dem_Make16Bit(lHighByte, lLowByte));

        if (lEventIdTmp < Dem_Cfg_GlobalEventCount())
        {
          lRootCauseEventId = lEventIdTmp;
        }
        else
        {
          /* Invalid RootCauseEventId */
          IndexedDataRecordBufferInfoPtr->ReadIndex += Dem_Cfg_DataSize(lDataIndex);                                             /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
        }
        break;
      }
      case DEM_CFG_DATA_FROM_CBK:
      case DEM_CFG_DATA_FROM_CBK_WITH_EVENTID:
      case DEM_CFG_DATA_FROM_SR_PORT_BOOLEAN:
      case DEM_CFG_DATA_FROM_SR_PORT_SINT8:
      case DEM_CFG_DATA_FROM_SR_PORT_UINT8:
      case DEM_CFG_DATA_FROM_SR_PORT_SINT16:
      case DEM_CFG_DATA_FROM_SR_PORT_SINT16_INTEL:
      case DEM_CFG_DATA_FROM_SR_PORT_UINT16:
      case DEM_CFG_DATA_FROM_SR_PORT_UINT16_INTEL:
      case DEM_CFG_DATA_FROM_SR_PORT_SINT32:
      case DEM_CFG_DATA_FROM_SR_PORT_SINT32_INTEL:
      case DEM_CFG_DATA_FROM_SR_PORT_UINT32:
      case DEM_CFG_DATA_FROM_SR_PORT_UINT32_INTEL:
      case DEM_CFG_DATA_FROM_SR_PORT_SINT8_N:
      case DEM_CFG_DATA_FROM_SR_PORT_UINT8_N:
      {
        IndexedDataRecordBufferInfoPtr->ReadIndex += Dem_Cfg_DataSize(lDataIndex);                                               /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
        break;
      }

      default:                                                                                                                   /* PRQA S 2024 */ /* MD_DEM_16.3_Continue */
        /* Found data element not stored in buffer -> skip it */
        continue;
      }
    }
    else
    {
      /* Data elements not stored in buffer -> skip it */
      continue;
    }

    if (lRootCauseEventId != DEM_EVENT_INVALID)
    {
      /* Found a RootCauseEventId - End search in other DIDs*/
      break;
    }
  }

  return lRootCauseEventId;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if ( (DEM_CFG_DATA_ROOTCAUSE_EVENTID == STD_ON) \
    && (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON) \
    && (DEM_CFG_STORAGE_AT_FDC == STD_OFF))
/* ****************************************************************************
 % Dem_MemoryRestoration_RecoverRootCauseEventIdFromERecs
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
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_MemoryRestoration_RecoverRootCauseEventIdFromERecs(
  Dem_Cfg_MemoryEntryHandleType MemoryEntryId,
  Dem_EventIdType EventId
  )
{
  Dem_EventIdType lRootCauseEventId;
#if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON)
  uint8 lExtendedEntryIndex;
  Dem_ExtendedEntry_IterType lExtendedEntryIter;
#endif

  lRootCauseEventId = DEM_EVENT_INVALID;

#if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON)
  lExtendedEntryIndex = 0u;
  /* Find the Record number */
  for (Dem_ExtendedEntry_IterInit(EventId, &lExtendedEntryIter);                                                                 /* SBSW_DEM_POINTER_FORWARD_STACK */
       Dem_ExtendedEntry_IterExists(&lExtendedEntryIter) == TRUE;                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_ExtendedEntry_IterNext(&lExtendedEntryIter))                                                                          /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_ERecIndexType lCfgERecIndex;
    lCfgERecIndex = Dem_ExtendedEntry_IterGet(&lExtendedEntryIter);                                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */

    if (Dem_Cfg_ERecType(lCfgERecIndex) == DEM_CFG_EREC_TYPE_USER)
    {
      if (Dem_ExtendedEntry_IteratorIsExtendedRecordStored(MemoryEntryId, lExtendedEntryIndex) == TRUE)                          /* SBSW_DEM_POINTER_FORWARD_STACK */
      {
        Dem_Cfg_DidIndexType lDidIndex;
        Dem_MemoryRestoration_IndexedDataRecordBufferInfoType lIndexedDataRecordBufferInfo;

        lIndexedDataRecordBufferInfo.SourceBuffer = Dem_MemoryEntry_GetExtendedRecordDataPtr(
                                                       MemoryEntryId,
                                                       lExtendedEntryIndex
                                                    );
        lIndexedDataRecordBufferInfo.ReadIndex = 0;

        lDidIndex = Dem_Cfg_ERecDid(lCfgERecIndex);
        {
          lRootCauseEventId = Dem_MemoryRestoration_RecoverRootCauseEventIdFromDID(lDidIndex, &lIndexedDataRecordBufferInfo);    /* SBSW_DEM_POINTER_LOCAL_DIDCOPYINFO */

          if (lRootCauseEventId != DEM_EVENT_INVALID)
          {
            /* Found a RootCauseEventId - End Search in other ERecs*/
            break;
          }
        }
      }
      lExtendedEntryIndex +=1u;
    }
  }
# else
  DEM_IGNORE_UNUSED_ARGUMENT(MemoryEntryId)                                                                                      /* PRQA S 1338, 3112 */ /* MD_MSR_DummyStmt, MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_ARGUMENT(EventId)                                                                                            /* PRQA S 1338, 3112 */ /* MD_MSR_DummyStmt, MD_DEM_14.2 */
# endif
    return lRootCauseEventId;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif

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
 * \addtogroup Dem_MemoryRestoration_Public
 * \{
 */

/* ****************************************************************************
 % Dem_MemoryRestoration_FixCorruptMemoryEntry
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
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MemoryRestoration_FixCorruptMemoryEntry(
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)  MemoryInfo,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  )
{
  boolean lReturnValue;
  Dem_Cfg_MemoryEntryHandleType lMemoryEntryId;
  Dem_EventIdType lEventId;

  lReturnValue = FALSE;
  lMemoryEntryId = Dem_MemoryEntry_GetId(MemoryIndex);
  lEventId = Dem_MemoryEntry_GetEventId(lMemoryEntryId);

  if (lEventId != DEM_EVENT_INVALID)
  {
    if ((lEventId >= Dem_Cfg_GlobalEventCount())                                                                                 
      || (Dem_Cfg_EventDestination(lEventId) != Dem_MemState_MemoryGetId(MemoryInfo))                                             /* PRQA S 3415 */ /* MD_DEM_13.5_cf */ /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
      || (lEventId != Dem_Cfg_GetMasterEvent(lEventId))                                                                          
#endif
      )
    {
      /* The memory entry is not allocated to the master event. Remove it. */
      Dem_MemoryEntry_SetEventId(lMemoryEntryId, DEM_EVENT_INVALID);
      Dem_MemoryEntry_SetTimestamp(lMemoryEntryId, 0U);
      Dem_Nvm_SetEventMemoryBlockState(MemoryIndex, DEM_NVM_BLOCKSTATE_DIRTYIMMEDIATE);

      /* DET: To get this inconsistency, it requires a configuration change without clearing the NV contents */
      Dem_Error_ReportError(DEM_INIT_APIID, DEM_E_INCONSISTENT_STATE);

      lReturnValue = TRUE;  /* caller shall continue with next memory entry */
    }
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_MemoryRestoration_FixDoubleAllocation
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
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MemoryRestoration_FixDoubleAllocation(
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)  MemoryInfo,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  )
{
  boolean lReturnValue;
  Dem_Cfg_MemoryEntryHandleType lMemoryEntryId;
  Dem_EventIdType lEventId;

  lReturnValue = FALSE;
  lMemoryEntryId = Dem_MemoryEntry_GetId(MemoryIndex);
  lEventId = Dem_MemoryEntry_GetEventId(lMemoryEntryId);
  if (lEventId != DEM_EVENT_INVALID)
  {
    Dem_Event_InternalStatusType lInternalStatus;
    lInternalStatus = Dem_DTC_GetInternalStatus(lEventId);

    if (Dem_DTCInternalStatus_GetStoredStatus(lInternalStatus) != Dem_DTCInternalStatus_StoredStatus_None)
    { 
      /* Runtime error, no DET. This can happen due to NV errors */
      Dem_Cfg_MemoryIndexType lOtherIndex;
      uint32 lTimestamp;

      /* Dem_MemAccess_MemoryFindIndex will always succeed since we are processing a duplicate */
      lOtherIndex = Dem_MemAccess_FindMemoryIndex_StoredEvent(MemoryInfo, lEventId);                                             /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
      lTimestamp = Dem_MemoryEntry_GetTimestamp(lMemoryEntryId);

      /* Clear the older memory entry */
      if (Dem_MemoryEntry_GetTimestamp(Dem_MemoryEntry_GetId(lOtherIndex)) < lTimestamp)
      {
        Dem_MemAccess_MemoryFreeIndex(MemoryInfo, lOtherIndex);                                                                  /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
        Dem_Nvm_SetEventMemoryBlockState(lOtherIndex, DEM_NVM_BLOCKSTATE_DIRTYIMMEDIATE);
      }
      else
      {
        Dem_MemoryEntry_SetEventId(lMemoryEntryId, DEM_EVENT_INVALID);
        Dem_MemoryEntry_SetTimestamp(lMemoryEntryId, 0U);
        Dem_Nvm_SetEventMemoryBlockState(MemoryIndex, DEM_NVM_BLOCKSTATE_DIRTYIMMEDIATE);
        lReturnValue = TRUE;  /* caller shall continue with next memory entry */
      }
    }
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6060 */ /* MD_MSR_STCAL, MD_MSR_STPAR */

/* ****************************************************************************
 % Dem_MemoryRestoration_RestoreEventStatus
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
Dem_MemoryRestoration_RestoreEventStatus(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)       MemoryIndex,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_Event_InternalStatusType lInternalStatus;
  lInternalStatus = Dem_DTC_GetInternalStatus(EventId);

  /* Dependent on the available redundancy, restore UDS status bits and the internal status */
#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_ON)                                                                    /* PRQA S 0883 */ /* MD_DEM_19.15 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryIndex)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lInternalStatus = Dem_MemoryRestoration_RestoreCustomizedStatusBits(MemoryEntryId, EventId, lInternalStatus);
#else
# if (DEM_CFG_STORAGE_AT_CONFIRMED == STD_ON)
  Dem_MemoryRestoration_RestoreStatusBits_OnConfirmedStorage(MemoryEntryId, EventId);
# endif
# if (DEM_CFG_STORAGE_AT_FAILED == STD_ON)
  Dem_MemoryRestoration_RestoreStatusBits_OnFailedStorage(MemoryEntryId, EventId);
# endif
# if (DEM_CFG_STORAGE_AT_FDC == STD_ON)
  Dem_MemoryRestoration_RestoreStatusBits_OnFdcThresholdStorage(MemoryEntryId, EventId);
# endif
# if (DEM_CFG_STORAGE_AT_PENDING == STD_ON)
  Dem_MemoryRestoration_RestoreStatusBits_OnPendingStorage(MemoryEntryId, EventId);
# endif
  Dem_MemoryRestoration_RestoreAgingCounter(MemoryEntryId, MemoryIndex, EventId);
  lInternalStatus = Dem_MemoryRestoration_RestoreStoredStatusFromEntry(MemoryEntryId, EventId, lInternalStatus);
#endif

  /*Store the modified internal status for the event*/
  Dem_DTC_SetInternalStatus(EventId, lInternalStatus);

#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  if (Dem_Cfg_EventIsCombined(EventId) == TRUE)
  {
    Dem_MemoryRestoration_RestoreCombinedEventStatusBitsFromEntry(MemoryEntryId, EventId);
  }
#endif
}

/* ****************************************************************************
% Dem_MemoryRestoration_RestoreTripCountFromCFCC
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
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryRestoration_RestoreTripCountFromCFCC(
  Dem_Cfg_MemoryEntryHandleType  MemoryEntryId,
  Dem_EventIdType  EventId
 )
{
#if ( ((DEM_CFG_DATA_CONSECUTIVE_FAILED_CYCLES == STD_ON) \
   || ((DEM_CFG_DATA_FAULT_PENDING_COUNTER == STD_ON) && (DEM_CFG_SUPPORT_MEM_INDEPENDENT_CYCLE_COUNTERS == STD_OFF))) \
   && (DEM_CFG_SUPPORT_MULTITRIP == STD_ON))
  /* If the event belongs to a combined group, ignore the event */
# if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  if (Dem_Cfg_EventIsCombined(EventId) == FALSE)
# endif
  {
    /* If retaining memory after aging is supported, ignore aged events 
    else process the event */
# if (DEM_CFG_AGING_RETAIN_MEMORY_ENTRY == STD_ON)
#  if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_ON)
    if (DEM_DTC_TEST_PC_STATUS_ADTC(Dem_MemoryEntry_GetPreConfirmedStatus(MemoryEntryId)) == TRUE)
#  else
    if (Dem_DTC_GetAgingCounter(EventId, MemoryEntryId) != DEM_OPERATIONCYCLE_CYCLECOUNT_AGED)
#  endif
# endif
    {
      uint8 lConsecutiveFailedCycleCounter;
      lConsecutiveFailedCycleCounter = Dem_MemoryEntry_GetConsecutiveFailedCycleCounter(MemoryEntryId);
      if (lConsecutiveFailedCycleCounter > 0u)
      {
        if (lConsecutiveFailedCycleCounter > Dem_Cfg_EventTripTarget(EventId))
        {
          /* Set trip count to max. value */
          Dem_Event_SetTripCount(EventId, Dem_Cfg_EventTripTarget(EventId));
        }
        else
        {
          /* 0 < ConsecutiveFailedCounter <= event trip target*/
          if (lConsecutiveFailedCycleCounter > Dem_Event_GetTripCount(EventId))
          {
  #  if (DEM_CFG_SUPPORT_OPCYCLE_STORAGE == STD_OFF || DEM_CFG_SUPPORT_OPCYCLE_AUTOMATIC_END == STD_ON)
            /* Operation Cycle is stopped at Shutdown (or counts as stopped on power
            loss) and trip count has same value as CFCC */
            Dem_Event_SetTripCount(EventId, lConsecutiveFailedCycleCounter);
  #  else
            /* Operation Cycle can outlast Shutdown-Init-Phase, CFCC might already
            be incremented and trip counter incremented with next operation cycle end,
            set trip count to CFC -1 to avoid confirmation one cycle to early */
            Dem_Event_SetTripCount(EventId, (uint8)(lConsecutiveFailedCycleCounter - 1u));
  #  endif
          }
        }
      }
    }
  }
#else
  DEM_IGNORE_UNUSED_ARGUMENT(MemoryEntryId)                                                                                      /* PRQA S 1338, 3112 */ /* MD_MSR_DummyStmt, MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_ARGUMENT(EventId)                                                                                            /* PRQA S 1338, 3112 */ /* MD_MSR_DummyStmt, MD_DEM_14.2 */
#endif
}                                                                                                                                /* PRQA S 6080 */ /* MD_MSR_STMIF */

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */


#endif /* DEM_MEMORYRESTORATION_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_MemoryRestoration_Implementation.h
 *********************************************************************************************************************/
