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
 *  \defgroup   Dem_TimeSeriesIF TimeSeriesIF
 *  \{
 *  \file       Dem_TimeSeriesIF_Interface.h
 *  \brief      Manages time series functionality.
 *  \details    Public Interfaces of TimeSeriesIF subcomponent
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_TIMESERIESIF_INTERFACE_H)
#define DEM_TIMESERIESIF_INTERFACE_H

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
#include "Dem_TimeSeriesIF_Types.h"

/* Includes for Other Types used by the Implementation */
/* ------------------------------------------------------------------------- */
#include "Dem_MemoryIF_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT PUBLIC PROPERTIES DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /*MD_MSR_MemMap */
/*!
 * \defgroup Dem_TimeSeries_PublicProperties Public Properties
 * \{
 */

/* ****************************************************************************
 * Dem_Memory_TimeSeries_TestEventSupportTimeSeries
 *****************************************************************************/
/*!
 * \brief         Test if the event stores a time series
 *
 * \details       Test if the event stores a time series
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE
 *                The event stores a time series
 * \return        TRUE
 *                The events does not store a time series
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Memory_TimeSeries_TestEventSupportTimeSeries(
  Dem_EventIdType  EventId
  );


/* ****************************************************************************
 * Dem_Memory_TimeSeries_IsPowertrainEnabled
 *****************************************************************************/
 /*!
 * \brief         Returns true if feature time series powertrain is enabled.
 *
 * \details       -
 *
 * \return        TRUE
 *                Time series powertrain is enabled
 * \return        FALSE
 *                Time series powertrain is not enabled
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Memory_TimeSeries_IsPowertrainEnabled(
  void
  );

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 * Dem_Memory_TimeSeries_TestEntryDisplaceable
 *****************************************************************************/
 /*!
 * \brief         Test whether the time series entry can be displaced
 *
 * \details       -
 *
 * \param[in]     MemoryIndex
 *                Handle of the memory block
 *
 * \return        TRUE
 *                The entry can be displaced
 * \return        FALSE
 *                The entry can not be displaced
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_TIME_SERIES == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Memory_TimeSeries_TestEntryDisplaceable(
  Dem_Cfg_MemoryIndexType  MemoryIndex
);
#endif
/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /*MD_MSR_MemMap */

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /*MD_MSR_MemMap */
/*!
 * \defgroup Dem_TimeSeries_Public Public Methods
 * \{
 */

/* ****************************************************************************
 * Dem_Memory_TimeSeries_InvalidateEntryOfEvent
 *****************************************************************************/
/*!
 * \brief         Remove a time series snapshot.
 *
 * \details       This function clears a time series snapshot stored for the
 *                passed Event and marks the block for nv-storage.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     BlockStatus
 *                New status of the memory block.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_InvalidateEntryOfEvent(
  Dem_EventIdType EventId,
  uint8  BlockStatus
  );

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 * Dem_Memory_TimeSeries_GetEntrySafe
 *****************************************************************************/
/*!
 * \brief         Get the indexed time series entry
 *
 * \details       Get the indexed time series entry
 *
 * \param[in]     MemoryIndex
 *                Handle of the memory block
 *
 * \return        Pointer to the indexed time series entry
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_TIME_SERIES == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Mem_TimeSeriesEntryPtrType, DEM_CODE)
Dem_Memory_TimeSeries_GetEntrySafe(
  Dem_Cfg_MemoryIndexType  MemoryIndex
  );
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 * Dem_Memory_TimeSeries_GetEntryCompanionSafe
 *****************************************************************************/
/*!
 * \brief         Get the indexed time series entry companion
 *
 * \details       Get the indexed time series entry companion
 *
 * \param[in]     MemoryIndex
 *                Handle of the memory block
 *
 * \return        Pointer to the indexed time series entry companion
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_TIME_SERIES == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Mem_TimeSeriesEntryCompanionPtrType, DEM_CODE)
Dem_Memory_TimeSeries_GetEntryCompanionSafe(
  Dem_Cfg_MemoryIndexType  MemoryIndex
  );
#endif

/* ****************************************************************************
* Dem_Memory_TimeSeries_TestEventSupportNormal
*****************************************************************************/
/*!
* \brief         Test if the event stores a normal rate time series record.
*
* \details       Test if the event stores a normal rate time series record.
*
* \param[in]     EventId
*                Unique handle of the Event.
*                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
*
* \return        TRUE
*                The event stores a normal rate time series record.
* \return        FALSE
*                The events does not store a normal rate time series record.
*
* \pre           -
*
* \context       TASK|ISR2
* \synchronous   TRUE
* \reentrant     TRUE
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Memory_TimeSeries_TestEventSupportNormal(
  Dem_EventIdType EventId
  );

/* ****************************************************************************
* Dem_Memory_TimeSeries_TestEventSupportFast
*****************************************************************************/
/*!
* \brief         Test if the event stores a fast rate time series record.
*
* \details       Test if the event stores a fast rate time series record.
*
* \param[in]     EventId
*                Unique handle of the Event.
*                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
*
* \return        TRUE
*                The event stores a fast rate time series record
* \return        FALSE
*                The events does not store a fast rate time series record
*
* \pre           -
*
* \context       TASK|ISR2
* \synchronous   TRUE
* \reentrant     TRUE
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Memory_TimeSeries_TestEventSupportFast(
  Dem_EventIdType EventId
  );

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 * Dem_Memory_TimeSeries_UpdateNormalFutureSamples
 *****************************************************************************/
/*!
 * \brief         Store normal rate time series record future samples for all entries
 *
 * \details       Store normal rate time series record future samples for all entries
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
Dem_Memory_TimeSeries_UpdateNormalFutureSamples(
  void
  );
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON)
/* ****************************************************************************
 * Dem_Memory_TimeSeries_UpdateFastFutureSamples
 *****************************************************************************/
/*!
 * \brief         Store fast rate time series record future samples for all entries
 *
 * \details       Store fast rate time series record future samples for all entries
 *
 * \pre           -
 *
 * \config        DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_UpdateFastFutureSamples(
  void
  );
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 * Dem_Memory_TimeSeries_TestEntryForEvent
 *****************************************************************************/
/*!
 * \brief         Test if given event occupies time series entry linked to given index
 *
 * \details       Test if given event occupies time series entry linked to given index
 *
 * \param[in]     Index
 *                Handle of the memory block
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \return        TRUE
 *                Given event allocates given entry
 * \return        FALSE
 *                Given event does not allocate given entry
 * \pre           -
 *
 * \config        DEM_FEATURE_NEED_TIME_SERIES == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Memory_TimeSeries_TestEntryForEvent(
  uint16 Index, 
  Dem_EventIdType EventId
  );
#endif

/* ****************************************************************************
 * Dem_Memory_TimeSeries_IsTimeSeriesPowertrainStoredByEvent
 *****************************************************************************/
 /*!
 * \brief         Test whether TimeSeries Powertrain Snapshot is ready to be reported.
 *
 * \details       Test whether TimeSeries Powertrain Snapshot is ready to be reported.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \return        TRUE
 *                TimeSeries Powertrain Snapshot ready to be reported 
 * \return        FALSE
 *                No TimeSeries Powertrain Snapshot ready or was already reported
 * \pre           -
 *
 * \config        DEM_FEATURE_NEED_TIME_SERIES == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Memory_TimeSeries_IsTimeSeriesPowertrainStoredByEvent(
  Dem_EventIdType EventId
);


#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 * Dem_Memory_TimeSeries_FreeEntry
 *****************************************************************************/
/*!
 * \brief         Free time series entry linked to given index
 *
 * \details       Free time series entry linked to given index
 *
 * \param[in]     Index
 *                Handle of the memory
 * \pre           -
 *
 * \config        DEM_FEATURE_NEED_TIME_SERIES == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_FreeEntry(
  uint16 Index
  );
#endif

/* ****************************************************************************
 * Dem_Memory_TimeSeries_Init
 *****************************************************************************/
/*!
 * \brief         Initializes time series functionality
 *
 * \details       Initializes time series sampler, ringbuffer and 
 *                time series entry companion
 *
 * \pre           NvM must have restored NV mirrors
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_Init(
  void
  );

/* ****************************************************************************
 * Dem_Memory_TimeSeries_InitNvData
 *****************************************************************************/
/*!
 * \brief         Initializes time series entries
 *
 * \details       This function initializes time series entries and
 *                time series memory control structures.
 *
 * \pre           NvM must have restored NV mirrors
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_InitNvData(
  void
  );

/* ****************************************************************************
 * Dem_Memory_TimeSeries_RestoreOnInit
 *****************************************************************************/
/*!
 * \brief         Validate and recover time series entries
 *
 * \details       This function verifies the integrity of time series entries
 *                and links them up into the runtime control structures.
 *
 * \pre           NvM must have restored NV mirrors
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_RestoreOnInit(
  void
  );

/* ****************************************************************************
 * Dem_Memory_TimeSeries_CreateEntry
 *****************************************************************************/
/*!
 * \brief         Allocate a time series entry
 *
 * \details       This function tries to allocate a time series entry for
 *                the given event. This can displace existing time series
 *                entries if all time series entries are occupied.
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
Dem_Memory_TimeSeries_CreateEntry(
  Dem_EventIdType  EventId
  );

#if ((DEM_FEATURE_NEED_TIME_SERIES == STD_ON) && (DEM_CFG_SUPPORT_DCM == STD_ON))
/* ****************************************************************************
 * Dem_Memory_TimeSeries_LockEntry
 *****************************************************************************/
 /*!
 * \brief         Lock the time series entry
 *
 * \details       Lock the time series entry
 *
 * \param[in]     MemoryIndex
 *                Index of the time series entry
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
Dem_Memory_TimeSeries_LockEntry(
  Dem_Cfg_MemoryIndexType MemoryIndex
);
#endif

#if ((DEM_FEATURE_NEED_TIME_SERIES == STD_ON) && (DEM_CFG_SUPPORT_DCM == STD_ON))
/* ****************************************************************************
 * Dem_Memory_TimeSeries_ReleaseEntry
 *****************************************************************************/
/*!
 * \brief         Release lock of the time series entry
 *
 * \details       Release lock of the time series entry
 *
 * \param[in]     MemoryIndex
 *                Index of the time series entry
 * \pre           -
 *
 * \config        DEM_FEATURE_NEED_TIME_SERIES == STD_ON
 *                && DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_ReleaseEntry(
  Dem_Cfg_MemoryIndexType MemoryIndex
);
#endif

/* ****************************************************************************
 * Dem_Memory_TimeSeries_ProcessWorkerTask
 *****************************************************************************/
/*!
 * \brief         Processes asynchronous tasks related to time series snapshot records
 *
 * \details       -
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_ProcessWorkerTask(
  void
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /*MD_MSR_MemMap */

#endif /* DEM_TIMESERIESIF_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_TimeSeriesIF_Interface.h
 *********************************************************************************************************************/
