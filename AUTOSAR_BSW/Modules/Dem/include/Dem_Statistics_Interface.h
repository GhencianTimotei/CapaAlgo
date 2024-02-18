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
/*! \ingroup    Dem_Master
 *  \defgroup   Dem_Statistics Statistics
 *  \{
 *  \file       Dem_Statistics_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Interface of the Statistics subcomponent which calculates global and event related statistics.
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_STATISTICS_INTERFACE_H)
#define DEM_STATISTICS_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_Statistics_Types.h"

                      /* Includes for Other Types used by the Implementation */
/* ------------------------------------------------------------------------- */
#include "Dem_DataReport_Types.h"

/* ------------------------------------------------------------------------- */

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_Statistics_PublicProperties Public Properties
 * \{
 */

/* ****************************************************************************
 * Dem_Statistics_GetFirstFailedEvent
 *****************************************************************************/
/*!
 * \brief         Get the first failed event.
 *
 * \details       Get the first failed event.
 *
 * \return        The first failed event.
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Statistics_GetFirstFailedEvent(
  void
  );

/* ****************************************************************************
 * Dem_Statistics_SetFirstFailedEvent
 *****************************************************************************/
/*!
 * \brief         Set the first failed event.
 *
 * \details       Set the first failed event.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Statistics_SetFirstFailedEvent(
  Dem_EventIdType EventId
  );

/* ****************************************************************************
 * Dem_Statistics_GetFirstConfirmedEvent
 *****************************************************************************/
/*!
 * \brief         Get the first confirmed event.
 *
 * \details       Get the first confirmed event.
 *
 * \return        The first confirmed event.
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Statistics_GetFirstConfirmedEvent(
  void
  );


/* ****************************************************************************
 * Dem_Statistics_SetFirstConfirmedEvent
 *****************************************************************************/
/*!
 * \brief         Set the first confirmed event.
 *
 * \details       Set the first confirmed event.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Statistics_SetFirstConfirmedEvent(
  Dem_EventIdType EventId
  );

/* ****************************************************************************
 * Dem_Statistics_GetMostRecentFailedEvent
 *****************************************************************************/
/*!
 * \brief         Get the most recently failed event.
 *
 * \details       Get the most recently failed event.
 *
 * \return        The most recently failed event.
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Statistics_GetMostRecentFailedEvent(
  void
  );

/* ****************************************************************************
 * Dem_Statistics_SetMostRecentFailedEvent
 *****************************************************************************/
/*!
 * \brief         Set the most recently failed event.
 *
 * \details       Set the most recently failed event.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Statistics_SetMostRecentFailedEvent(
  Dem_EventIdType EventId
  );

/* ****************************************************************************
 * Dem_Statistics_GetMostRecentConfirmedEvent
 *****************************************************************************/
/*!
 * \brief         Get the most recently confirmed event.
 *
 * \details       Get the most recently confirmed event.
 *
 * \return        The most recently confirmed event.
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Statistics_GetMostRecentConfirmedEvent(
  void
  );

/* ****************************************************************************
 * Dem_Statistics_SetMostRecentConfirmedEvent
 *****************************************************************************/
/*!
 * \brief         Set the most recently confirmed event.
 *
 * \details       Set the most recently confirmed event.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Statistics_SetMostRecentConfirmedEvent(
  Dem_EventIdType EventId
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
 * \defgroup Dem_Statistics_Public Public Methods
 * \{
 */

/* ****************************************************************************
 * Dem_Statistics_UpdateGlobalFailureStatistics
 *****************************************************************************/
/*!
 * \brief         This function updates global failure statistics.
 *
 * \details       This function updates global failure statistics like first
 *                and most recently failed event, first and most recently
 *                confirmed event.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     Effects
 *                Trigger flags
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Statistics_UpdateGlobalFailureStatistics(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_StorageTriggerType, AUTOMATIC)  Effects
  );

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_AGINGCTR == STD_ON)
/* ****************************************************************************
 * Dem_Statistics_CalculateUpwardsAgingCounter
 *****************************************************************************/
/*!
 * \brief         Function calculates the upward counting aging counter of the
 *                event holding the event memory entry.
 *
 * \details       Function calculates the upward counting aging counter of the
 *                event holding the event memory entry.
 *
 * \param[in]     EventId
 *                Unique handle of the event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        Value of upward counting aging counter.
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON) &&
 *                DEM_CFG_DATA_AGINGCTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(uint8, DEM_CODE)
Dem_Statistics_CalculateUpwardsAgingCounter(
  Dem_Cfg_MemoryEntryHandleType MemoryEntryId,
  Dem_EventIdType               EventId
  );
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_OCCCTR == STD_ON)
/* ****************************************************************************
 * Dem_Statistics_Calculate1ByteOccurrenceCounter
 *****************************************************************************/
/*!
 * \brief         Function calculates the 1 Byte occurrence counter of the
 *                event holding the event memory entry.
 *
 * \details       Function calculates the 1 Byte occurrence counter of the
 *                event holding the event memory entry.
 *
 * \param[in]     DidCopyInfoPtr
 *                CopyDid context
 *
 * \return        Value of 1 Byte occurrence counter.
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON) &&
 *                DEM_CFG_DATA_OCCCTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Statistics_Calculate1ByteOccurrenceCounter(
  CONST(Dem_DataReport_DidCopyInfoPtrType, AUTOMATIC)  DidCopyInfoPtr
  );
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_SIGNIFICANCE == STD_ON)
/* ****************************************************************************
 * Dem_Statistics_CalculateEventSignificance
 *****************************************************************************/
/*!
 * \brief         Function calculates the significance of the event.
 *
 * \details       Function calculates the significance of the event.
 *
 * \param[in]     DidCopyInfoPtr
 *                CopyDid context
 *
 * \return        Value of event significance.
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON) &&
 *                DEM_CFG_DATA_SIGNIFICANCE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Statistics_CalculateEventSignificance(
  CONST(Dem_DataReport_DidCopyInfoPtrType, AUTOMATIC)  DidCopyInfoPtr
  );
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_AGINGCTR_INVERTED == STD_ON)
/* ****************************************************************************
 * Dem_Statistics_CalculateDownwardsAgingCounter
 *****************************************************************************/
/*!
 * \brief         Function calculates the downward counting aging counter of the
 *                event holding the event memory entry.
 *
 * \details       Function calculates the downward counting aging counter of the
 *                event holding the event memory entry.
 *
 * \param[in]     EventId
 *                Unique handle of the event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        Value of downward counting aging counter.
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON) &&
 *                DEM_CFG_DATA_AGINGCTR_INVERTED == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(uint8, DEM_CODE)
Dem_Statistics_CalculateDownwardsAgingCounter(
  Dem_Cfg_MemoryEntryHandleType MemoryEntryId,
  Dem_EventIdType               EventId
  );
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_MAX_FDC_SINCE_LAST_CLEAR == STD_ON)
/* ****************************************************************************
 * Dem_Statistics_CalculateMaxFdcSinceLastClear
 *****************************************************************************/
/*!
 * \brief         Function calculates the maximum fault detection counter since
 *                last clear of the event holding the event memory entry.
 *
 * \details       Function calculates the maximum fault detection counter since
 *                last clear of the event holding the event memory entry.
 *
 * \param[in]     DidCopyInfoPtr
 *                CopyDid context
 *
 * \return        Value of maximum fault detection counter since last clear.
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON) &&
 *                DEM_CFG_DATA_MAX_FDC_SINCE_LAST_CLEAR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(sint8, DEM_CODE)
Dem_Statistics_CalculateMaxFdcSinceLastClear(
  CONST(Dem_DataReport_DidCopyInfoPtrType, AUTOMATIC)  DidCopyInfoPtr
  );
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_MAX_FDC_DURING_CURRENT_CYCLE == STD_ON)
/* ****************************************************************************
 * Dem_Statistics_CalculateMaxFdcThisCycle
 *****************************************************************************/
/*!
 * \brief         Function calculates the maximum fault detection counter during
 *                current cycle of the event holding the event memory entry.
 *
 * \details       Function calculates the maximum fault detection counter during
 *                current cycle of the event holding the event memory entry.
 *
 * \param[in]     DidCopyInfoPtr
 *                CopyDid context
 *
 * \return        Value of maximum fault detection counter during current cycle.
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON) &&
 *                DEM_CFG_DATA_MAX_FDC_DURING_CURRENT_CYCLE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(sint8, DEM_CODE)
Dem_Statistics_CalculateMaxFdcThisCycle(
  CONST(Dem_DataReport_DidCopyInfoPtrType, AUTOMATIC)  DidCopyInfoPtr
  );
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_CYCLES_SINCE_LAST_FAILED == STD_ON)
/* ****************************************************************************
 * Dem_Statistics_CalculateCyclesSinceLastFailed
 *****************************************************************************/
/*!
 * \brief         Function calculates number of cycles since last failed report
 *                of the event holding the event memory entry.
 *
 * \details       Function calculates number of cycles since last failed report
 *                of the event holding the event memory entry.
 *
 * \param[in]     DidCopyInfoPtr
 *                CopyDid context
 *
 * \return        Value of number of cycles since last failed report.
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON) &&
 *                DEM_CFG_DATA_CYCLES_SINCE_LAST_FAILED == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Statistics_CalculateCyclesSinceLastFailed(
  CONST(Dem_DataReport_DidCopyInfoPtrType, AUTOMATIC)  DidCopyInfoPtr
  );
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_WUC_SINCE_LAST_FAILED == STD_ON)
/* ****************************************************************************
* Dem_Statistics_CalculateWarmUpCyclesSinceLastFailed
*****************************************************************************/
/*!
* \brief         Function calculates number of WarmUp cycles since last failed report
*                of the event holding the event memory entry.
*
* \details       Function calculates number of WarmUp cycles since last failed report
*                of the event holding the event memory entry.
*
* \param[in]     DidCopyInfoPtr
*                CopyDid context
*
* \return        Value of number of WarmUp cycles since last failed report.
*
* \pre           -
* \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
*                DEM_FEATURE_NEED_OBD == STD_ON) &&
*                DEM_CFG_DATA_WUC_SINCE_LAST_FAILED == STD_ON
*
* \context       TASK|ISR2
* \synchronous   TRUE
* \reentrant     TRUE
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Statistics_CalculateWarmUpCyclesSinceLastFailed(
  CONST(Dem_DataReport_DidCopyInfoPtrType, AUTOMATIC)  DidCopyInfoPtr
  );
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_CYCLES_SINCE_FIRST_FAILED == STD_ON)
/* ****************************************************************************
 * Dem_Statistics_CalculateCyclesSinceFirstFailed
 *****************************************************************************/
/*!
 * \brief         Function calculates number of cycles since first failed report
 *                of the event holding the event memory entry.
 *
 * \details       Function calculates number of cycles since first failed report
 *                of the event holding the event memory entry.
 *
 * \param[in]     DidCopyInfoPtr
 *                CopyDid context
 *
 * \return        Value of number of cycles since first failed.
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON) &&
 *                DEM_CFG_DATA_CYCLES_SINCE_FIRST_FAILED == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Statistics_CalculateCyclesSinceFirstFailed(
  CONST(Dem_DataReport_DidCopyInfoPtrType, AUTOMATIC)  DidCopyInfoPtr
  );
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_CYCLES_TESTED_SINCE_LAST_FAILED == STD_ON)
/* ****************************************************************************
 * Dem_Statistics_CalculateCyclesTestedSinceLastFailed
 *****************************************************************************/
/*!
 * \brief         Function calculates the number of cycles tested since last
 *                failed report of the event.
 *
 * \details       Function calculates the number of cycles tested since last
 *                failed report of the event.
 *
 * \param[in]     EventId
 *                Unique handle of the event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        Value of the number of cycles tested since last failed report.
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON) &&
 *                DEM_CFG_DATA_CYCLES_TESTED_SINCE_LAST_FAILED == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(uint8, DEM_CODE)
Dem_Statistics_CalculateCyclesTestedSinceLastFailed(
  Dem_EventIdType  EventId
  );
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_FAULT_PENDING_COUNTER == STD_ON)
/* ****************************************************************************
 * Dem_Statistics_CalculateFaultPendingCounter
 *****************************************************************************/
/*!
 * \brief         Function calculates the 'fault pending counter' of the event.
 *
 * \details       Function calculates the 'fault pending counter' of the event.
 *
 * \param[in]     EventId
 *                Unique handle of the event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        Value of the number of consecutive cycles tested failed with
 *                a maximum value that is reached when the DTC confirms.
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON) &&
 *                DEM_CFG_DATA_FAULT_PENDING_COUNTER == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(uint8, DEM_CODE)
Dem_Statistics_CalculateFaultPendingCounter(
  Dem_Cfg_MemoryEntryHandleType MemoryEntryId,
  Dem_EventIdType               EventId
  );
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_FAILED_CYCLES == STD_ON)
/* ****************************************************************************
* Dem_Statistics_CalculateFailedCycleCounter
*****************************************************************************/
/*!
* \brief         Function calculates the 'failed cycle counter' of the event.
*
* \details       Function calculates the 'failed cycle counter' of the event.
*
* \param[in]     EventId
*                Unique handle of the event.
*                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
* \param[in]     MemoryEntryId
*                The memory entry handle
*
* \return        Value of the number of failed cycles.
*
* \pre           -
* \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
*                DEM_FEATURE_NEED_OBD == STD_ON) &&
*                DEM_CFG_DATA_FAILED_CYCLES == STD_ON
*
* \context       TASK|ISR2
* \synchronous   TRUE
* \reentrant     TRUE
*****************************************************************************/
DEM_LOCAL FUNC(uint8, DEM_CODE)
Dem_Statistics_CalculateFailedCycleCounter(
  Dem_Cfg_MemoryEntryHandleType MemoryEntryId,
  Dem_EventIdType               EventId
);
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_HEALINGCTR_DOWNCNT == STD_ON)
/* ****************************************************************************
 * Dem_Statistics_CalculateInvertedHealingCounter
 *****************************************************************************/
/*!
 * \brief         Function calculates the inverted healing counter of the event.
 *
 * \details       Function calculates the inverted healing counter of the event.
 *
 * \param[in]     EventId
 *                Unique handle of the event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        Value of the inverted healing counter.
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON) &&
 *                DEM_CFG_DATA_HEALINGCTR_DOWNCNT == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(uint8, DEM_CODE)
Dem_Statistics_CalculateInvertedHealingCounter(
  Dem_EventIdType  EventId
  );
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && \
( (DEM_CFG_DATA_STANDARD_ENV_DATA == STD_ON) || (DEM_CFG_DATA_EXTENDED_ENV_DATA == STD_ON) )
/* ****************************************************************************
 * Dem_Statistics_CalculateCustomizedAgingCounter
 *****************************************************************************/
/*!
 * \brief         Function calculates standard environment data specific
 *                upward counting aging counter for the event holding 
 *                the event memory entry.
 *
 * \details       Function calculates standard environment data specific
 *                upward counting aging counter for the event holding 
 *                the event memory entry.
 *
 * \param[in]     DidCopyInfoPtr
 *                CopyDid context
 *
 * \return        Value of environment data specific upward counting aging counter.
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON) &&
 *                (DEM_CFG_DATA_STANDARD_ENV_DATA == STD_ON ||
 *                DEM_CFG_DATA_EXTENDED_ENV_DATA == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Statistics_CalculateCustomizedAgingCounter(
  CONST(Dem_DataReport_DidCopyInfoPtrType, AUTOMATIC)  DidCopyInfoPtr
  );
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_STATISTICS_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Statistics_Interface.h
 *********************************************************************************************************************/
