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
/*! \addtogroup Dem_Statistics
 *  \{
 *  \file       Dem_Statistics_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Implementation of the Statistics subcomponent which calculates global and event related statistics.
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_STATISTICS_IMPLEMENTATION_H)
#define DEM_STATISTICS_IMPLEMENTATION_H

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
#include "Dem_Statistics_Interface.h"

/* Includes to access public functions belonging to other (top level)/ (logical)/- units to be used by this Unit */
/* ------------------------------------------------------------------------- */
#include "Dem_FaultMemory_Interface.h"
#include "Dem_Core_Interface.h"
#include "Dem_Satellite_Interface.h"
#include "Dem_Core_Interface.h"
                                                   /* Subcomponents callbacks*/
/* ------------------------------------------------------------------------- */

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*! Filename declaration */
#define DEM_STATISTICS_IMPLEMENTATION_FILENAME "Dem_Statistics_Implementation.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DEFINITIONS
 *********************************************************************************************************************/
/* ********************************************************************************************************************
 *  SUBCOMPONENT PUBLIC PROPERTIES DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \addtogroup Dem_Statistics_PublicProperties
 * \{
 */

/* ****************************************************************************
 % Dem_Statistics_GetFirstFailedEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Statistics_GetFirstFailedEvent(                                                                                              /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
  )
{
  return (Dem_EventIdType)Dem_Cfg_StatusData.FirstFailedEvent;
}


/* ****************************************************************************
 % Dem_Statistics_SetFirstFailedEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Statistics_SetFirstFailedEvent(                                                                                              /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  Dem_EventIdType EventId
  )
{
  Dem_Cfg_StatusData.FirstFailedEvent = EventId;
}

/* ****************************************************************************
 % Dem_Statistics_GetFirstConfirmedEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Statistics_GetFirstConfirmedEvent(                                                                                           /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
  )
{
  return (Dem_EventIdType)Dem_Cfg_StatusData.FirstConfirmedEvent;
}

/* ****************************************************************************
 % Dem_Statistics_SetFirstConfirmedEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Statistics_SetFirstConfirmedEvent(                                                                                           /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  Dem_EventIdType EventId
  )
{
  Dem_Cfg_StatusData.FirstConfirmedEvent = EventId;
}

/* ****************************************************************************
 % Dem_Statistics_GetMostRecentFailedEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Statistics_GetMostRecentFailedEvent(                                                                                         /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
  )
{
  return (Dem_EventIdType)Dem_Cfg_StatusData.MostRecentFailedEvent;
}

/* ****************************************************************************
 % Dem_Statistics_SetMostRecentFailedEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Statistics_SetMostRecentFailedEvent(                                                                                         /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  Dem_EventIdType EventId
  )
{
  Dem_Cfg_StatusData.MostRecentFailedEvent = EventId;
}

/* ****************************************************************************
 % Dem_Statistics_GetMostRecentConfirmedEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Statistics_GetMostRecentConfirmedEvent(                                                                                      /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
  )
{
  return (Dem_EventIdType)Dem_Cfg_StatusData.MostRecentConfmdEvent;
}

/* ****************************************************************************
 % Dem_Statistics_SetMostRecentConfirmedEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Statistics_SetMostRecentConfirmedEvent(                                                                                      /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  Dem_EventIdType EventId
  )
{
  Dem_Cfg_StatusData.MostRecentConfmdEvent = EventId;
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
 * \defgroup Dem_Statistics_Private Private Methods
 * \{
 */


#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && \
( (DEM_CFG_DATA_CYCLES_TESTED_SINCE_LAST_FAILED == STD_ON) || (DEM_CFG_DATA_HEALINGCTR_DOWNCNT == STD_ON) )
/* ****************************************************************************
 * Dem_Statistics_TestHealingCounterReadable
 *****************************************************************************/
/*!
 * \brief         Returns if the healing counter can be read.
 *
 * \details       The healing counter (corresponding to 'Cycles Tested
 *                Since Last Failed') can be read, if the event is currently
 *                healing or is already healed.
 *                In order that the counter is not reported, if the event was
 *                never tested failed, the TFSLC status bit has to be set.
 *                In order that the counter is not reported, if healing hasn't
 *                been started for the event, the PDTC status bit has to be
 *                unset (in configurations with PDTC status bit set
 *                'Stored Only' this is only secure, if the event is stored).
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE
 *                The healing counter can be read.
 *                FALSE
 *                The healing counter can not be read.
 *
 * \pre           -
 * \config        ((DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                  DEM_FEATURE_NEED_OBD == STD_ON) &&
 *                 (DEM_CFG_DATA_CYCLES_TESTED_SINCE_LAST_FAILED == STD_ON ||
 *                  DEM_CFG_DATA_HEALINGCTR_DOWNCNT == STD_ON))
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Statistics_TestHealingCounterReadable(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/


#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && \
( (DEM_CFG_DATA_CYCLES_TESTED_SINCE_LAST_FAILED == STD_ON) || (DEM_CFG_DATA_HEALINGCTR_DOWNCNT == STD_ON) )
/* ****************************************************************************
 % Dem_Statistics_TestHealingCounterReadable
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
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Statistics_TestHealingCounterReadable(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  boolean lCounterReadable;
  uint8 lUdsStatus;

  lCounterReadable = FALSE;

  lUdsStatus = Dem_DTC_RetrieveStatus(EventId);

  if ( (Dem_UDSStatus_Test_TFSLC(lUdsStatus) == TRUE) && (Dem_UDSStatus_Test_PDTC(lUdsStatus) == FALSE) )                        
  {
    lCounterReadable = TRUE;
  }

  return lCounterReadable;
}
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
 * \addtogroup Dem_Statistics_Public
 * \{
 */

/* ****************************************************************************
 % Dem_Statistics_UpdateGlobalFailureStatistics
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
Dem_Statistics_UpdateGlobalFailureStatistics(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_StorageTriggerType, AUTOMATIC)  Effects
  )
{
  if ( (EventId >= Dem_Cfg_GlobalPrimaryFirst())
    && (EventId <= Dem_Cfg_GlobalPrimaryLast()) )                                                                                
  {
    if ((Effects & DEM_CFG_TRIGGER_CONFIRMED) != 0u)
    {
      if (Dem_Statistics_GetFirstConfirmedEvent() == DEM_EVENT_INVALID)
      {
        Dem_Statistics_SetFirstConfirmedEvent(EventId);
      }

      Dem_Statistics_SetMostRecentConfirmedEvent(EventId);
    }

    if (Dem_Statistics_GetFirstFailedEvent() == DEM_EVENT_INVALID)
    {
      Dem_Statistics_SetFirstFailedEvent(EventId);
    }
    Dem_Statistics_SetMostRecentFailedEvent(EventId);
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_AGINGCTR == STD_ON)
/* ****************************************************************************
 % Dem_Statistics_CalculateUpwardsAgingCounter
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
Dem_Statistics_CalculateUpwardsAgingCounter(
  Dem_Cfg_MemoryEntryHandleType MemoryEntryId,
  Dem_EventIdType               EventId
  )
{
  uint8 lAgingCounter;

  if ( (Dem_DTC_GetAgingCounter(EventId, MemoryEntryId) == DEM_OPERATIONCYCLE_CYCLECOUNT_INVALID)
# if (DEM_CFG_AGING_COUNT_ONLY_AGEABLE == STD_ON)
    || (Dem_Cfg_EventSupportAging(EventId) == FALSE)                                                             
# endif
     )
  {
    lAgingCounter = 0x00U;
  }
  else
  if (Dem_DTC_GetAgingCounter(EventId, MemoryEntryId) == DEM_OPERATIONCYCLE_CYCLECOUNT_LATCHED)
  {
    lAgingCounter = Dem_Cfg_GetAgingCycleCounterThresholdOfEventTable(EventId); /* Event cannot age, so the counter stays at aging counter threshold. */
  }
# if ((DEM_CFG_AGING_RETAIN_MEMORY_ENTRY == STD_ON) || (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON))
  else
  if (Dem_DTC_GetAgingCounter(EventId, MemoryEntryId) == DEM_OPERATIONCYCLE_CYCLECOUNT_AGED)
  {
# if(DEM_CFG_DATA_AGED_COUNTER == STD_ON)
    lAgingCounter = 0x00U; /* Aged information can be retrieved from 'aged' counter, return 0 is a special customer requirement */
# else
    lAgingCounter = (uint8)(Dem_Cfg_EventAgingTarget(EventId));
# endif
  }
# endif
  else
  {
    uint16 lTarget = Dem_DTC_GetAgingCounter(EventId, MemoryEntryId);
    uint16 lCurrent = Dem_OperationCycle_GetCycleCounter(Dem_Cfg_EventAgingCycle(EventId));
    lAgingCounter = (uint8)(Dem_Cfg_EventAgingTarget(EventId) - Dem_OperationCycle_CycleCountDistance(lCurrent, lTarget));
# if (DEM_CFG_AGING_REPORT_ZERO_AS_ONE == STD_ON)
    if (lAgingCounter == 0x00U)
    {
      lAgingCounter = 0x01U;
    }
# endif
  }

  return lAgingCounter;
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_OCCCTR == STD_ON)
/* ****************************************************************************
 % Dem_Statistics_Calculate1ByteOccurrenceCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Statistics_Calculate1ByteOccurrenceCounter(
  CONST(Dem_DataReport_DidCopyInfoPtrType, AUTOMATIC)  DidCopyInfoPtr                                                          /* PRQA S 3673 */ /* MD_DEM_8.13_Internal */
  )
{
  uint8 lOccurrenceCounter;

# if (DEM_CFG_DATA_OCCCTR_2BYTE == STD_ON)
  {
    uint16 lOccurrenceCounter2Byte;
    lOccurrenceCounter2Byte = Dem_MemoryEntry_GetOccurrenceCounter2Byte(DidCopyInfoPtr->MemoryEntryId);
    if (lOccurrenceCounter2Byte > 0xffU)
    {
      lOccurrenceCounter = 0xffU;
    }
    else
    {
      lOccurrenceCounter = (uint8) lOccurrenceCounter2Byte;
    }
  }
# else
  lOccurrenceCounter = (uint8)Dem_MemoryEntry_GetOccurrenceCounter1Byte(DidCopyInfoPtr->MemoryEntryId);
# endif

  return lOccurrenceCounter;
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_SIGNIFICANCE == STD_ON)
/* ****************************************************************************
 % Dem_Statistics_CalculateEventSignificance
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Statistics_CalculateEventSignificance(
  CONST(Dem_DataReport_DidCopyInfoPtrType, AUTOMATIC)  DidCopyInfoPtr                                                          /* PRQA S 3673 */ /* MD_DEM_8.13_Internal */
  )
{
  uint8 lEventSignificance;

  lEventSignificance = Dem_Cfg_EventSignificance(DidCopyInfoPtr->Base.EventId);
  return lEventSignificance;
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_AGINGCTR_INVERTED == STD_ON)
/* ****************************************************************************
 % Dem_Statistics_CalculateDownwardsAgingCounter
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
DEM_LOCAL FUNC(uint8, DEM_CODE)
Dem_Statistics_CalculateDownwardsAgingCounter(
  Dem_Cfg_MemoryEntryHandleType MemoryEntryId,
  Dem_EventIdType               EventId
  )
{
  uint8 lAgingCounterInverted;

  if ((Dem_DTC_GetAgingCounter(EventId, MemoryEntryId) == DEM_OPERATIONCYCLE_CYCLECOUNT_INVALID) 
# if (DEM_CFG_AGING_COUNT_ONLY_AGEABLE == STD_ON)
    || (Dem_Cfg_EventSupportAging(EventId) == FALSE)                                                             
# endif
     )
  {
    lAgingCounterInverted = Dem_Cfg_EventAgingTarget(EventId);
  }
  else
  if (Dem_DTC_GetAgingCounter(EventId, MemoryEntryId) == DEM_OPERATIONCYCLE_CYCLECOUNT_LATCHED)
  {
    lAgingCounterInverted = 0x00U;
  }
  else
# if ((DEM_CFG_AGING_RETAIN_MEMORY_ENTRY == STD_ON) || (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON))
  if((Dem_DTC_GetAgingCounter(EventId, MemoryEntryId) == DEM_OPERATIONCYCLE_CYCLECOUNT_AGED))
  {
# if(DEM_CFG_DATA_AGED_COUNTER == STD_ON)
    /* That event aged can be retrieved from 'aged' counter, return 'aging target' is a special customer requirement */
    lAgingCounterInverted = (uint8)(Dem_Cfg_EventAgingTarget(EventId));
# else
    lAgingCounterInverted = 0x00U;
# endif
  }
  else
# endif
  {
    uint16 lTarget = Dem_DTC_GetAgingCounter(EventId, MemoryEntryId);
    uint16 lCurrent = Dem_OperationCycle_GetCycleCounter(Dem_Cfg_EventAgingCycle(EventId));
    lAgingCounterInverted = (uint8)(Dem_OperationCycle_CycleCountDistance(lCurrent, lTarget));
  }

  return lAgingCounterInverted;
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_MAX_FDC_SINCE_LAST_CLEAR == STD_ON)
/* ****************************************************************************
 % Dem_Statistics_CalculateMaxFdcSinceLastClear
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
DEM_LOCAL_INLINE FUNC(sint8, DEM_CODE)
Dem_Statistics_CalculateMaxFdcSinceLastClear(
  CONST(Dem_DataReport_DidCopyInfoPtrType, AUTOMATIC)  DidCopyInfoPtr                                                          /* PRQA S 3673 */ /* MD_DEM_8.13_Internal */
  )
{
  sint8 lMaxFdcSinceLastClear;

# if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_ON)
  lMaxFdcSinceLastClear = Dem_DebounceCounterBased_CalculateFaultDetectionCounter(DidCopyInfoPtr->Base.EventId,
                            Dem_MemoryEntry_GetDebounceValueMax(DidCopyInfoPtr->MemoryEntryId));
# else
  {
    if (Dem_UDSStatus_Test_TFSLC(Dem_DTC_RetrieveStatus(DidCopyInfoPtr->Base.EventId)) == TRUE)
    {
      lMaxFdcSinceLastClear = 127;
    }
    else
    {
      lMaxFdcSinceLastClear = (sint8)Dem_MemoryEntry_GetDebounceValueMax(DidCopyInfoPtr->MemoryEntryId);
    }
  }
# endif

  return lMaxFdcSinceLastClear;
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_MAX_FDC_DURING_CURRENT_CYCLE == STD_ON)
/* ****************************************************************************
 % Dem_Statistics_CalculateMaxFdcThisCycle
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(sint8, DEM_CODE)
Dem_Statistics_CalculateMaxFdcThisCycle(
  CONST(Dem_DataReport_DidCopyInfoPtrType, AUTOMATIC)  DidCopyInfoPtr                                                          /* PRQA S 3673 */ /* MD_DEM_8.13_Internal */
  )
{
  sint8 lMaxFdcThisCycle;

# if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  Dem_Cfg_CombinedGroupIndexType lGroupId;
  lGroupId = Dem_Cfg_EventCombinedGroup(DidCopyInfoPtr->Base.EventId);
  if (lGroupId != DEM_CFG_COMBINED_GROUP_INVALID)
  {
    lMaxFdcThisCycle = Dem_DTC_CombinedGroupGetFDCMax(lGroupId);
  }
  else
# endif
  {
    lMaxFdcThisCycle = Dem_Satellite_GetMaxFaultDetectionCounter(
                         Dem_Cfg_EventSatelliteId(DidCopyInfoPtr->Base.EventId),
                         Dem_Cfg_EventSatelliteEventId(DidCopyInfoPtr->Base.EventId)
                         );
  }

  return lMaxFdcThisCycle;
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_CYCLES_SINCE_LAST_FAILED == STD_ON)
/* ****************************************************************************
 % Dem_Statistics_CalculateCyclesSinceLastFailed
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Statistics_CalculateCyclesSinceLastFailed(
  CONST(Dem_DataReport_DidCopyInfoPtrType, AUTOMATIC)  DidCopyInfoPtr                                                          /* PRQA S 3673 */ /* MD_DEM_8.13_Internal */
  )
{
  uint8 lCyclesSinceLastFailed;

  if (Dem_MemoryEntry_GetCyclesSinceLastFailed(DidCopyInfoPtr->MemoryEntryId) == DEM_OPERATIONCYCLE_CYCLECOUNT_INVALID)
  {
    lCyclesSinceLastFailed = 0x00U;
  }
  else
  if (Dem_MemoryEntry_GetCyclesSinceLastFailed(DidCopyInfoPtr->MemoryEntryId) == DEM_OPERATIONCYCLE_CYCLECOUNT_LATCHED)
  {
    lCyclesSinceLastFailed = 0xffU;
  }
  else
  {
    lCyclesSinceLastFailed = (uint8)Dem_OperationCycle_CycleCountDistance(
                                      Dem_MemoryEntry_GetCyclesSinceLastFailed(DidCopyInfoPtr->MemoryEntryId),
                                      Dem_OperationCycle_GetCycleCounter(
                                      Dem_Cfg_EventOperationCycle(DidCopyInfoPtr->Base.EventId))
                                      );
  }

  return lCyclesSinceLastFailed;
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_WUC_SINCE_LAST_FAILED == STD_ON)
/* ****************************************************************************
% Dem_Statistics_CalculateWarmUpCyclesSinceLastFailed
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
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Statistics_CalculateWarmUpCyclesSinceLastFailed(
  CONST(Dem_DataReport_DidCopyInfoPtrType, AUTOMATIC)  DidCopyInfoPtr                                                          /* PRQA S 3673 */ /* MD_DEM_8.13_Internal */
  )
{
  uint8 lWarmUpCyclesSinceLastFailed;

  if (Dem_MemoryEntry_GetWarmUpCyclesSinceLastFailed(DidCopyInfoPtr->MemoryEntryId) == DEM_OPERATIONCYCLE_CYCLECOUNT_INVALID)
  {
    lWarmUpCyclesSinceLastFailed = 0x00U;
  }
  else
  if (Dem_MemoryEntry_GetWarmUpCyclesSinceLastFailed(DidCopyInfoPtr->MemoryEntryId) == DEM_OPERATIONCYCLE_CYCLECOUNT_LATCHED)
  {
    lWarmUpCyclesSinceLastFailed = 0xffU;
  }
  else
  {
    lWarmUpCyclesSinceLastFailed = (uint8)Dem_OperationCycle_CycleCountDistance(
                                            Dem_MemoryEntry_GetWarmUpCyclesSinceLastFailed(DidCopyInfoPtr->MemoryEntryId),
                                            Dem_OperationCycle_GetCycleCounter(Dem_Cfg_GlobalWarmupCycleId())
                                            );
  }

  return lWarmUpCyclesSinceLastFailed;
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_CYCLES_SINCE_FIRST_FAILED == STD_ON)
/* ****************************************************************************
 % Dem_Statistics_CalculateCyclesSinceFirstFailed
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Statistics_CalculateCyclesSinceFirstFailed(
  CONST(Dem_DataReport_DidCopyInfoPtrType, AUTOMATIC)  DidCopyInfoPtr                                                          /* PRQA S 3673 */ /* MD_DEM_8.13_Internal */
  )
{
  uint8 lCyclesSinceFirstFailed;

  if (Dem_MemoryEntry_GetCyclesSinceFirstFailed(DidCopyInfoPtr->MemoryEntryId) == DEM_OPERATIONCYCLE_CYCLECOUNT_INVALID)
  {
    lCyclesSinceFirstFailed = 0x00U;
  }
  else
  if (Dem_MemoryEntry_GetCyclesSinceFirstFailed(DidCopyInfoPtr->MemoryEntryId) == DEM_OPERATIONCYCLE_CYCLECOUNT_LATCHED)
  {
    lCyclesSinceFirstFailed = 0xffU;
  }
  else
  {
    lCyclesSinceFirstFailed = (uint8)Dem_OperationCycle_CycleCountDistance(
                                       Dem_MemoryEntry_GetCyclesSinceFirstFailed(DidCopyInfoPtr->MemoryEntryId),
                                       Dem_OperationCycle_GetCycleCounter(
                                       Dem_Cfg_EventOperationCycle(DidCopyInfoPtr->Base.EventId))
                                       );
  }

  return lCyclesSinceFirstFailed;
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_CYCLES_TESTED_SINCE_LAST_FAILED == STD_ON)
/* ****************************************************************************
 % Dem_Statistics_CalculateCyclesTestedSinceLastFailed
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
DEM_LOCAL FUNC(uint8, DEM_CODE)
Dem_Statistics_CalculateCyclesTestedSinceLastFailed(
  Dem_EventIdType  EventId
  )
{
  uint8 lCyclesTestedSinceLastFailed;

  if (Dem_Statistics_TestHealingCounterReadable(EventId) == TRUE)
  {
    lCyclesTestedSinceLastFailed = Dem_Event_GetTripCount(EventId);
  }
  else
  {
    lCyclesTestedSinceLastFailed = 0x00;
  }

  return lCyclesTestedSinceLastFailed;
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_FAULT_PENDING_COUNTER == STD_ON)
/* ****************************************************************************
 % Dem_Statistics_CalculateFaultPendingCounter
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
DEM_LOCAL FUNC(uint8, DEM_CODE)
Dem_Statistics_CalculateFaultPendingCounter(
  Dem_Cfg_MemoryEntryHandleType MemoryEntryId,
  Dem_EventIdType               EventId
  )
{
  uint8 lFaultPendingCounter;

  if(Dem_DTC_IsMemIndependentCycleCounterEnabled() == FALSE)
  {
    lFaultPendingCounter = Dem_MemoryEntry_GetConsecutiveFailedCycleCounter(MemoryEntryId);
  }
  else
  {
    Dem_Cfg_FaultPendingCounterIndexOfEventTableType lFaultPendingCounterIndex;
    lFaultPendingCounterIndex = Dem_Cfg_GetFaultPendingCounterIndexOfEventTable(EventId);

    if(lFaultPendingCounterIndex != DEM_CFG_FAULTPENDINGCOUNTER_INDEX_INVALID)
    {
      lFaultPendingCounter = Dem_DTC_GetFaultPendingCounter(lFaultPendingCounterIndex);
    }
    else
    {
      /* event without DTC has this memory independent fault pending counter configured */
      lFaultPendingCounter = 0x00U;
    }
  }

  if (lFaultPendingCounter > (Dem_Cfg_EventTripTarget(EventId) + 1u))
  {
    /* Different to the trip counter, the 'consecutive failed cycle counter'
       takes first failed cycle into account */
    lFaultPendingCounter = Dem_Cfg_EventTripTarget(EventId) + 1u;
  }

  return lFaultPendingCounter;
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_FAILED_CYCLES == STD_ON)
/* ****************************************************************************
% Dem_Statistics_CalculateFailedCycleCounter
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
DEM_LOCAL FUNC(uint8, DEM_CODE)
Dem_Statistics_CalculateFailedCycleCounter(
  Dem_Cfg_MemoryEntryHandleType MemoryEntryId,
  Dem_EventIdType EventId
)
{
  uint8 lFailedCycleCounter;

  if (Dem_DTC_IsMemIndependentCycleCounterEnabled() == FALSE)
  {
    lFailedCycleCounter = Dem_MemoryEntry_GetFailedCycleCounter(MemoryEntryId);
  }
  else
  {
    Dem_Cfg_FailedCycleCounterIndexOfEventTableType lFailedCounterIndex;
    lFailedCounterIndex = Dem_Cfg_GetFailedCycleCounterIndexOfEventTable(EventId);

    if (lFailedCounterIndex != DEM_CFG_FAILEDCYCLECOUNTER_INDEX_INVALID)
    {
      lFailedCycleCounter = Dem_DTC_GetFailedCycleCounter(lFailedCounterIndex);
    }
    else
    {
      /* event without DTC has this memory independent failed cycle counter configured */
      lFailedCycleCounter = 0x00U;
    }
  }
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return lFailedCycleCounter;
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_HEALINGCTR_DOWNCNT == STD_ON)
/* ****************************************************************************
 % Dem_Statistics_CalculateInvertedHealingCounter
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
DEM_LOCAL FUNC(uint8, DEM_CODE)
Dem_Statistics_CalculateInvertedHealingCounter(
  Dem_EventIdType  EventId
  )
{
  uint8 lHealingCounterInverted;

  if (Dem_Statistics_TestHealingCounterReadable(EventId) == TRUE)
  {
    if (Dem_Event_GetTripCount(EventId) < Dem_Cfg_EventHealingTarget(EventId))
    {
      lHealingCounterInverted = (Dem_Cfg_EventHealingTarget(EventId) - Dem_Event_GetTripCount(EventId));
    }
    else
    {
      lHealingCounterInverted = 0x00;
    }
  }
  else
  {
    lHealingCounterInverted = Dem_Cfg_EventHealingTarget(EventId);
  }

  return lHealingCounterInverted;
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && \
( (DEM_CFG_DATA_STANDARD_ENV_DATA == STD_ON) || (DEM_CFG_DATA_EXTENDED_ENV_DATA == STD_ON) )
/* ****************************************************************************
 % Dem_Statistics_CalculateCustomizedAgingCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Statistics_CalculateCustomizedAgingCounter(
  CONST(Dem_DataReport_DidCopyInfoPtrType, AUTOMATIC)  DidCopyInfoPtr                                                          /* PRQA S 3673 */ /* MD_DEM_8.13_Internal */
  )
{
  uint8 lAgingCounter;

  if (Dem_DTC_GetAgingCounter(DidCopyInfoPtr->Base.EventId, DidCopyInfoPtr->MemoryEntryId) == DEM_OPERATIONCYCLE_CYCLECOUNT_INVALID)
  {
    lAgingCounter = 0x00U;
  }
  else
  if (Dem_DTC_GetAgingCounter(DidCopyInfoPtr->Base.EventId, DidCopyInfoPtr->MemoryEntryId) == DEM_OPERATIONCYCLE_CYCLECOUNT_LATCHED)
  {
    lAgingCounter = 0xffU;
  }
  else
  {
    uint16 lTarget = Dem_DTC_GetAgingCounter(DidCopyInfoPtr->Base.EventId, DidCopyInfoPtr->MemoryEntryId);
    uint16 lCurrent = Dem_OperationCycle_GetCycleCounter(Dem_Cfg_EventAgingCycle(DidCopyInfoPtr->Base.EventId));
    lAgingCounter = (uint8)(Dem_Cfg_EventAgingTarget(DidCopyInfoPtr->Base.EventId) - 
                            Dem_OperationCycle_CycleCountDistance(lCurrent, lTarget));
  }

  return lAgingCounter;
}
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */


#endif /* DEM_STATISTICS_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Statistics_Implementation.h
 *********************************************************************************************************************/
