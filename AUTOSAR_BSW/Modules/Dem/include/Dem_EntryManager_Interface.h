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
/*! \ingroup    Dem_TimeSeries
 *  \defgroup   Dem_EntryManager EntryManager
 *  \{
 *  \file       Dem_EntryManager_Interface.h
 *  \brief      Manages time series memory entries.
 *  \details    Creates an time series memory entry for event if storage trigger is reached and collects the required data. Manages virtual buffer state handling.
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_ENTRYMANAGER_INTERFACE_H)
#define DEM_ENTRYMANAGER_INTERFACE_H

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
/* PRQA S 3415 EOF */ /* MD_DEM_13.5_cf */

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_EntryManager_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT PUBLIC PROPERTIES DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_EntryManager_PublicProperties Public Properties
 * \{
 */

/* ****************************************************************************
 * Dem_Memory_TimeSeries_EntryManager_EventDidIterExists
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
 *                Dem_Memory_TimeSeries_EntryManager_EventDidIterGet() will return
 *                a valid element on this iterator
 * \return        FALSE
 *                Dem_Memory_TimeSeries_EntryManager_EventDidIterGet() is undefined
 *                on this iterator
 *
 * \pre           IterPtr has been initialized
 *
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_EventDidIterExists(
CONSTP2CONST(Dem_Cfg_EventDidIterType, AUTOMATIC, AUTOMATIC)  IterPtr
);

/* ****************************************************************************
 * Dem_Memory_TimeSeries_EntryManager_EventDidIterGet
 *****************************************************************************/
/*!
 * \brief         Get the element pointed to by the iterator
 *
 * \details       Get the element pointed to by the iterator
 *
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \return        Handle to DID descriptor table
 *
 * \pre           IterPtr has been initialized
 *
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_DidIndexType, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_EventDidIterGet(
CONSTP2CONST(Dem_Cfg_EventDidIterType, AUTOMATIC, AUTOMATIC)  IterPtr
);

/* ****************************************************************************
 * Dem_Memory_TimeSeries_EntryManager_EventDidIterInit
 *****************************************************************************/
/*!
 * \brief         Init the iterator
 *
 * \details       Initializes the iterator to enumerate DIDs configured for an
 *                event (i.e. Snapshot content)
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[out]    IterPtr
 *                Pointer to the iterator
 *
 * \pre           -
 *
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_EventDidIterInit(
CONST(Dem_EventIdType, AUTOMATIC)  EventId,
CONSTP2VAR(Dem_Cfg_EventDidIterType, AUTOMATIC, AUTOMATIC)  IterPtr
);

/* ****************************************************************************
 * Dem_Memory_TimeSeries_EntryManager_EventDidIterNext
 *****************************************************************************/
/*!
 * \brief         Move the iterator to the next element
 *
 * \details       Move the iterator to the next element
 *
 * \param[in,out] IterPtr
 *                Pointer to the iterator
 *
 * \pre           IterPtr has been initialized
 *
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_EventDidIterNext(
CONSTP2VAR(Dem_Cfg_EventDidIterType, AUTOMATIC, AUTOMATIC)  IterPtr
);

/* ****************************************************************************
 * Dem_Memory_TimeSeries_EntryManager_GetTimeSinceLastSample
 *****************************************************************************/
/*!
 * \brief         Return time since last sample collection of entry.
 *
 * \details       Return time since last sample collection of entry.
 *
 * \param[in]     Entry
 *                Pointer to the time series entry.
 *
 * \return        Time since last sample collection.
 *
 * \pre           -
 *
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_GetTimeSinceLastSample(
  Dem_Mem_ConstTimeSeriesEntryPtrType Entry
  );

 /* ****************************************************************************
 * Dem_Memory_TimeSeries_EntryManager_GetUnusedPastSamplesNormal
 *****************************************************************************/
/*!
 * \brief         Return number of unused past (normal) samples of time series entry
 *
 * \details       Return number of unused past (normal) samples of time series entry if available
 *
 * \param[in]     Entry
 *                Pointer to the time series entry
 *
 * \return        Number of unused past (normal) samples of time series entry.
 *
 * \pre           -
 *
 * \config        DEM_CFG_SUPPORT_TIME_SERIES_PAST_NORMAL == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_GetUnusedPastSamplesNormal(
  Dem_Mem_ConstTimeSeriesEntryPtrType Entry
  );

 /* ****************************************************************************
 * Dem_Memory_TimeSeries_EntryManager_GetUnusedPastSamplesFast
 *****************************************************************************/
 /*!
 * \brief         Return number of unused past (fast) samples of time series entry
 *
 * \details       Return number of unused past (fast) samples of time series entry if available
 *
 * \param[in]     Entry
 *                Pointer to the time series entry
 *
 * \return        Number of unused past (fast) samples of time series entry.
 *
 * \pre           -
 *
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_GetUnusedPastSamplesFast(
  Dem_Mem_ConstTimeSeriesEntryPtrType Entry
  );

/* ****************************************************************************
 * Dem_Memory_TimeSeries_EntryManager_GetUnusedFutureSamplesNormal
 *****************************************************************************/
/*!
 * \brief         Return number of unused future (normal) samples of time series entry
 *
 * \details       Return number of unused future (normal) samples of time series entry
 *                if available and otherwise 0.
 *
 * \param[in]     Entry
 *                Pointer to the time series entry
 *
 * \return        Number of unused future (normal) samples of time series entry.
 * 
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_GetUnusedFutureSamplesNormal(
  Dem_Mem_ConstTimeSeriesEntryPtrType Entry
  );

/* ****************************************************************************
 * Dem_Memory_TimeSeries_EntryManager_GetUnusedFutureSamplesFast
 *****************************************************************************/
/*!
 * \brief         Return number of unused future (fast) samples of time series entry
 *
 * \details       Return number of unused future (fast) samples of time series entry 
 *                if available and otherwise 0.
 *
 * \param[in]     Entry
 *                Pointer to the time series entry
 * 
 * \return        Number of unused future (fast) samples of time series entry.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_GetUnusedFutureSamplesFast(
  Dem_Mem_ConstTimeSeriesEntryPtrType Entry
  );

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 * Dem_Memory_TimeSeries_EntryManager_GetClientCounter
 *****************************************************************************/
 /*!
 * \brief         Get client counter of time series entry.
 *
 * \details       Get client counter of time series entry.
 *
 * \param[in]     EntryCompanion
 *                Pointer to Time Series Entry Companion
 *
 * \return        client counter of the time series entry
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_TIME_SERIES == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_GetClientCounter(
  Dem_Mem_ConstTimeSeriesEntryCompanionConstPtrType  EntryCompanion
);
#endif


#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 * Dem_Memory_TimeSeries_EntryManager_GetReadoutState
 *****************************************************************************/
 /*!
 * \brief         Get readout status of the time series entry.
 *
 * \details       Get readout status of the time series entry.
 *
 * \param[in]     Entry
 *                Pointer to the time series entry
 *
 * \return        The readout status of the time series entry.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_TIME_SERIES == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Memory_TimeSeries_EntryManager_ReadoutStatusType, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_GetReadoutState(
  Dem_Mem_ConstTimeSeriesEntryCompanionConstPtrType  EntryCompanion
);
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 * Dem_Memory_TimeSeries_EntryManager_SetReadoutState
 *****************************************************************************/
 /*!
 * \brief         Set readout state of time series entry.
 *
 * \details       Set readout state of time series entry.
 *
 * \param[in]     Entry
 *                Pointer to Time Series Entry
 *
 * \param[in]     State
 *                New readout state to be set
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_TIME_SERIES == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_SetReadoutState(
  Dem_Mem_TimeSeriesEntryCompanionConstPtrType  EntryCompanion,
  Dem_Memory_TimeSeries_EntryManager_ReadoutStatusType  State
);
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 * Dem_Memory_TimeSeries_EntryManager_InitClientCounter
 *****************************************************************************/
 /*!
 * \brief         Initialize client counter of time series entry to 0.
 *
 * \details       Initialize client counter of time series entry to 0.
 *
 * \param[in]     EntryCompanion
 *                Pointer to Time Series Entry Companion
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_TIME_SERIES == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_InitClientCounter(
  Dem_Mem_TimeSeriesEntryCompanionConstPtrType  EntryCompanion
);
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 * Dem_Memory_TimeSeries_EntryManager_GetClientCounter
 *****************************************************************************/
 /*!
 * \brief         Get client counter of time series entry.
 *
 * \details       Get client counter of time series entry.
 *
 * \param[in]     EntryCompanion
 *                Ppinter to Time Series Entry Companion
 *
 * \return        client counter of the time series entry
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_TIME_SERIES == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_GetClientCounter(
  Dem_Mem_ConstTimeSeriesEntryCompanionConstPtrType EntryCompanion
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
 * \defgroup Dem_EntryManager_Public Public Methods
 * \{
 */

/* ****************************************************************************
 * Dem_Memory_TimeSeries_EntryManager_GetNormalConstDataPtr
 *****************************************************************************/
/*!
 * \brief         Get the indexed normal rate data buffer of the time series entry
 *
 * \details       Get the indexed normal rate data buffer of the time series entry
 *
 * \param[in]     MemoryEntry
 *                Pointer to the time series entry
 * \param[in]     SeriesIndex
 *                Index of the time series snapshot record
 *
 * \return        Pointer to the indexed normal rate data buffer
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_ConstSharedDataPtrType, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_GetNormalConstDataPtr(
  Dem_Mem_ConstTimeSeriesEntryPtrType  MemoryEntry,
  uint8  SeriesIndex
  );

/* ****************************************************************************
 * Dem_Memory_TimeSeries_EntryManager_GetFastConstDataPtr
 *****************************************************************************/
/*!
 * \brief         Get the indexed fast rate data buffer of the time series entry
 *
 * \details       Get the indexed fast rate data buffer of the time series entry
 *
 * \param[in]     MemoryEntry
 *                Pointer to the time series entry
 * \param[in]     SeriesIndex
 *                Index of the time series snapshot record
 *
 * \return        Pointer to the indexed fast rate data buffer
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_ConstSharedDataPtrType, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_GetFastConstDataPtr(
  Dem_Mem_ConstTimeSeriesEntryPtrType  MemoryEntry,
  uint8  SeriesIndex
  );

#if (DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_NORMAL == STD_ON)
/* ****************************************************************************
 * Dem_Memory_TimeSeries_EntryManager_SetMissingNormalSamples
 *****************************************************************************/
/*!
 * \brief         Set the missing normal rate samples of the indexed time series
 *                snapshot record.
 *
 * \details       Set the missing normal rate samples of the indexed time series
 *                snapshot record.
 *
 * \param[in]     EntryCompanion
 *                Pointer to Time Series Entry Companion
 * \param[in]     Value
 *                New value
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_NORMAL == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_SetMissingNormalSamples(
  Dem_Mem_TimeSeriesEntryCompanionConstPtrType  EntryCompanion,
  uint8  Value
  );
#endif

#if (DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_FAST == STD_ON)
/* ****************************************************************************
 * Dem_Memory_TimeSeries_EntryManager_SetMissingFastSamples
 *****************************************************************************/
/*!
 * \brief         Set the missing fast samples of the indexed time series
 *                snapshot record.
 *
 * \details       Set the missing fast samples of the indexed time series
 *                snapshot record.
 *
 * \param[in]     EntryCompanion
 *                Pointer to Time Series Entry Companion
 * \param[in]     Value
 *                New value
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_FAST == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_SetMissingFastSamples(
  Dem_Mem_TimeSeriesEntryCompanionConstPtrType  EntryCompanion,
  uint8  Value
  );
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 * Dem_Memory_TimeSeries_EntryManager_EntryInit
 *****************************************************************************/
/*!
 * \brief         Initializes a time series entry
 *
 * \details       Initializes a time series entry
 *
 * \param[in]     TimeSeriesEntry
 *                Pointer to the time series entry
 *
 * \pre           -
 *
 * \config        DEM_FEATURE_NEED_TIME_SERIES == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_EntryInit(
  Dem_Mem_TimeSeriesEntryConstPtrType TimeSeriesEntry
  );
#endif

/* ****************************************************************************
 * Dem_Memory_TimeSeries_EntryManager_InitCompanionEntries
 *****************************************************************************/
/*!
 * \brief         Initializes all time series companion entries to unused
 *
 * \details       Initializes all time series companion entries to unused
 *
 *
 * \pre           -
 *
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_InitCompanionEntries(
  void
  );

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON) 
/* ****************************************************************************
 * Dem_Memory_TimeSeries_EntryManager_EntryCompanionInit
 *****************************************************************************/
/*!
 * \brief         Initializes a time series entry companion
 *
 * \details       Initializes a time series entry companion
 *
 * \param[in]     TimeSeriesEntryCompanion
 *                Pointer to the time series entry companion
 * \param[in]     State
 *                New readout state to be set
 *
 * \pre           -
 *
 * \config        DEM_FEATURE_NEED_TIME_SERIES == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_EntryCompanionInit(
  Dem_Mem_TimeSeriesEntryCompanionConstPtrType TimeSeriesEntryCompanion,
  Dem_Memory_TimeSeries_EntryManager_ReadoutStatusType State
  );
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES_PAST == STD_ON)
/* ****************************************************************************
 * Dem_Memory_TimeSeries_EntryManager_StorePastSamples
 *****************************************************************************/
/*!
 * \brief         Store past samples for given event
 *
 * \details       Store past samples for given event
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     MemoryIndex
 *                Handle of the memory block
 *
 * \pre           time series entry allocated for event
 * \config        DEM_FEATURE_NEED_TIME_SERIES_PAST == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_StorePastSamples(
  Dem_EventIdType  EventId,
  Dem_Cfg_MemoryIndexType  MemoryIndex
  );
#endif

 #if (DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_NORMAL == STD_ON)
/* ****************************************************************************
 * Dem_Memory_TimeSeries_EntryManager_StoreNormalFutureSamples
 *****************************************************************************/
/*!
 * \brief         Store future normal samples for given entry
 *
 * \details       Store future normal samples for given entry
 *
 * \param[in]     Entry
 *                Time Series Entry
 * \param[in]     EntryCompanion
 *                Pointer to Time Series Entry Companion
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_NORMAL == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_StoreNormalFutureSamples(
  Dem_Cfg_MemoryIndexType MemoryIndex,
  CONST(Dem_Mem_TimeSeriesEntryPtrType, AUTOMATIC)  Entry,
  Dem_Mem_TimeSeriesEntryCompanionConstPtrType  EntryCompanion
  );
#endif

#if (DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_FAST == STD_ON)
/* ****************************************************************************
 * Dem_Memory_TimeSeries_EntryManager_StoreFastFutureSamples
 *****************************************************************************/
/*!
 * \brief         Store future fast samples for given entry
 *
 * \details       Store future fast samples for given entry
 *
 * \param[in]     Entry
 *                Time Series Entry
 * \param[in]     EntryCompanion
 *                Pointer to Time Series Entry Companion
 *
 * \return        TRUE
 *                Entry has changed
 * \return        FALSE
 *                Entry has not changed
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_FAST == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_StoreFastFutureSamples(
  Dem_Cfg_MemoryIndexType MemoryIndex,
  CONST(Dem_Mem_TimeSeriesEntryPtrType, AUTOMATIC)  Entry,
  Dem_Mem_TimeSeriesEntryCompanionConstPtrType  EntryCompanion
  );
#endif

#if ((DEM_FEATURE_NEED_TIME_SERIES == STD_ON) && (DEM_CFG_SUPPORT_DCM == STD_ON))
/* ****************************************************************************
 * Dem_Memory_TimeSeries_EntryManager_Lock
 *****************************************************************************/
 /*!
  * \brief         Update the entry readout status and increment client counter
  *
  * \details       Update the entry readout status and increment client counter
  *
  * \param[in]     EntryCompanion
  *                Pointer to Time Series Entry Companion
  * \pre           EntryCompanion's state is UNLOCKED or LOCKED
  *
  * \config        DEM_FEATURE_NEED_TIME_SERIES == STD_ON
  *                && DEM_CFG_SUPPORT_DCM == STD_ON
  *
  * \context       TASK|ISR2
  * \synchronous   TRUE
  * \reentrant     TRUE
  *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_Lock(
  Dem_Mem_TimeSeriesEntryCompanionConstPtrType EntryCompanion
);
#endif

#if ((DEM_FEATURE_NEED_TIME_SERIES == STD_ON) && (DEM_CFG_SUPPORT_DCM == STD_ON))
/* ****************************************************************************
 * Dem_Memory_TimeSeries_EntryManager_ReleaseLock
 *****************************************************************************/
 /*!
  * \brief         Decrements the entry client counter and update the readout status
  *
  * \details       Decrements the entry client counter and update the readout status
  *
  * \param[in]     EntryCompanion
  *                Pointer to Time Series Entry Companion
  *
  * \return        TRUE
  *                Entry should be freed
  * \return        FALSE
  *                Entry should not be freed
  *
  * \pre           -
  *
  * \config        DEM_FEATURE_NEED_TIME_SERIES == STD_ON
  *                && DEM_CFG_SUPPORT_DCM == STD_ON
  *
  * \context       TASK|ISR2
  * \synchronous   TRUE
  * \reentrant     TRUE
  *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_ReleaseLock(
  Dem_Mem_TimeSeriesEntryCompanionConstPtrType EntryCompanion
);
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 * Dem_Memory_TimeSeries_EntryManager_RequestDeletion
 *****************************************************************************/
 /*!
  * \brief         Request entry deletion and return whether the entry should be freed
  *
  * \details       Request entry deletion and return whether the entry should be freed
  *
  * \param[in]     EntryCompanion
  *                Pointer to Time Series Entry Companion
  *
  * \return        TRUE
  *                Entry should be freed
  * \return        FALSE
  *                Entry should not be freed
  *
  * \pre           -
  * \config        DEM_FEATURE_NEED_TIME_SERIES == STD_ON
  *
  * \context       TASK|ISR2
  * \synchronous   TRUE
  * \reentrant     TRUE
  *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_RequestDeletion(
  Dem_Mem_TimeSeriesEntryCompanionConstPtrType EntryCompanion
);
#endif

/* ****************************************************************************
 * Dem_Memory_TimeSeries_EntryManager_GetConstDataPtr
 *****************************************************************************/
/*!
 * \brief         Get the indexed rate data buffer of the time series entry
 *
 * \details       Get the indexed rate data buffer of the time series entry
 *
 * \param[in]     MemoryEntry
 *                Pointer to the time series entry
 * \param[in]     SeriesIndex
 *                Index of the time series snapshot record
 *
 * \return        Pointer to the indexed normal rate data buffer
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_ConstSharedDataPtrType, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_GetConstDataPtr(
  CONST(Dem_Mem_ConstTimeSeriesEntryPtrType, AUTOMATIC)  MemoryEntry,
  CONST(uint8, AUTOMATIC)  SeriesIndex
);

#if (DEM_CFG_SUPPORT_TIME_SERIES_POWERTRAIN == STD_ON) 
/* ****************************************************************************
 * Dem_Memory_TimeSeries_EntryManager_RoundFloatToUint16
 *****************************************************************************/
/*!
 * \brief         Round a floating point value to the nearest uint16 value.
 *
 * \details       Round a floating point value to the nearest uint16 value.
 *
 * \param[in]     Value
 *                Float32 value
 *
 * \return        value in uint16 format
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_TIME_SERIES_POWERTRAIN == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_RoundFloatToUint16(
  float32 Value
);
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_ENTRYMANAGER_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_EntryManager_Interface.h
 *********************************************************************************************************************/
