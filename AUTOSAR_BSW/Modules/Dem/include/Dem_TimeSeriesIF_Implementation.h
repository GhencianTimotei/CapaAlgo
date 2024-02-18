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
/*! \addtogroup Dem_TimeSeriesIF
 *  \{
 *  \file       Dem_TimeSeriesIF_Implementation.h
 *  \brief      Manages time series functionality.
 *  \details    Implementation of TimeSeries subcomponent
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_TIMESERIESIF_IMPLEMENTATION_H)
#define DEM_TIMESERIESIF_IMPLEMENTATION_H

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
#include "Dem_TimeSeriesIF_Interface.h"

/* Includes to access public functions belonging to other (top level)/ (logical)/- units to be used by this Unit */
/* ------------------------------------------------------------------------- */
#include "Dem_EntryManager_Interface.h"
#include "Dem_RingBuffer_Interface.h"
#include "Dem_Sampler_Interface.h"

#include "Dem_Core_Interface.h"
#include "Dem_Infrastructure_Interface.h"
#include "Dem_MemAccess_Interface.h"
#include "Dem_MemState_Interface.h"
#include "Dem_MemoryIF_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

  /*! Filename declaration */
#define DEM_TIMESERIESIF_IMPLEMENTATION_FILENAME "Dem_TimeSeriesIF_Implementation.h"

 /* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/
#define DEM_START_SEC_VAR_NOINIT_8BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /*MD_MSR_MemMap */
#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/*! Virtual buffer deletion request flag */
DEM_LOCAL VAR(boolean, DEM_VAR_NOINIT)           Dem_Memory_TimeSeries_RequestCleanUp;
#endif
#define DEM_STOP_SEC_VAR_NOINIT_8BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /*MD_MSR_MemMap */
/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DEFINITIONS
 *********************************************************************************************************************/
 
/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE PROPERTIES DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /*MD_MSR_MemMap */
/*!
 * \defgroup Dem_TimeSeries_PrivateProperties Private Properties
 * \{
 */

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
 /* ****************************************************************************
 * Dem_Memory_TimeSeries_TestEntryAvailable
 *****************************************************************************/
/*!
 * \brief         Test whether the entry is available based on whether it is in 
 *                readout staus DELETION CANDIDATE
 *
 * \details       Test whether the entry is available based on whether it is in 
 *                readout staus DELETION CANDIDATE
 *
 * \param[in]     MemoryIndex
 *                Handle of the memory
 *
 * \pre           -
 *
 * \return        TRUE
 *                The time series entry is available.
 * \return        FALSE
 *                The time series entry is not available.
 * \config        DEM_FEATURE_NEED_TIME_SERIES == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Memory_TimeSeries_TestEntryAvailable(
  Dem_Cfg_MemoryIndexType  MemoryIndex
);
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 * Dem_Memory_TimeSeries_TestEntryNeedToBeCleaned
 *****************************************************************************/
 /*!
 * \brief         Test whether the time series entry with readout state of DELETION CANDIDATE
 *                can be deleted due to finished readout
 *
 * \details       -
 *
 * \param[in]     MemoryIndex
 *                Handle of the memory block
 *
 * \return        TRUE
 *                The entry needs to be deleted with the main function
 * \return        FALSE
 *                The entry does not need to be deleted with the main function
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_TIME_SERIES == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Memory_TimeSeries_TestEntryNeedToBeCleaned(
  Dem_Cfg_MemoryIndexType  MemoryIndex
);
#endif

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE PROPERTIES DEFINITIONS
 *********************************************************************************************************************/

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
 /* ****************************************************************************
 % Dem_Memory_TimeSeries_TestEntryAvailable
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Memory_TimeSeries_TestEntryAvailable(
  Dem_Cfg_MemoryIndexType  MemoryIndex
)
{
  Dem_Mem_ConstTimeSeriesEntryCompanionPtrType lEntryCompanion;
  lEntryCompanion = Dem_Memory_TimeSeries_GetEntryCompanionSafe(MemoryIndex);

  return (boolean)(Dem_Memory_TimeSeries_EntryManager_GetReadoutState(lEntryCompanion)                                           /* SBSW_DEM_POINTER_WRITE_TIMESERIESENTRYCOMPANION */
    != DEM_MEMORY_TIMESERIES_ENTRYMANAGER_READOUTSTATUS_DELETION_CANDIDATE);
}
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 % Dem_Memory_TimeSeries_TestEntryNeedToBeCleaned
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Memory_TimeSeries_TestEntryNeedToBeCleaned(
  Dem_Cfg_MemoryIndexType  MemoryIndex
)
{
  Dem_Memory_TimeSeries_EntryManager_ReadoutStatusType lReadoutStatus;
  uint8 lClientCounter;
  lReadoutStatus = Dem_Memory_TimeSeries_EntryManager_GetReadoutState(Dem_Memory_TimeSeries_GetEntryCompanionSafe(MemoryIndex));     /* SBSW_DEM_POINTER_WRITE_TIMESERIESENTRYCOMPANION */
  lClientCounter = Dem_Memory_TimeSeries_EntryManager_GetClientCounter(Dem_Memory_TimeSeries_GetEntryCompanionSafe(MemoryIndex));    /* SBSW_DEM_POINTER_WRITE_TIMESERIESENTRYCOMPANION */

  return (boolean)((lReadoutStatus == DEM_MEMORY_TIMESERIES_ENTRYMANAGER_READOUTSTATUS_DELETION_CANDIDATE) && (lClientCounter == 0x00U));
}
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /*MD_MSR_MemMap */

/* ********************************************************************************************************************
 *  SUBCOMPONENT PUBLIC PROPERTIES DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /*MD_MSR_MemMap */
/*!
 * \addtogroup Dem_TimeSeries_PublicProperties
 * \{
 */
/* ****************************************************************************
 % Dem_Memory_TimeSeries_TestEventSupportTimeSeries
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
Dem_Memory_TimeSeries_TestEventSupportTimeSeries(                                                                                  /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  Dem_EventIdType  EventId                                                                                                         /* PRQA S 3206 */ /* MD_DEM_3206 */
)
{
  boolean lReturnValue;

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
  lReturnValue = (boolean)(Dem_Cfg_IsTimeSeriesNormalOfEventTable(EventId));
# if (DEM_CFG_SUPPORT_TIME_SERIES_POWERTRAIN == STD_ON)
  lReturnValue = (boolean)(lReturnValue || (Dem_Cfg_IsTimeSeriesFastOfEventTable(EventId) == TRUE));
# endif
#else
    lReturnValue = FALSE;
#endif

  return lReturnValue;
}

  /* ****************************************************************************
 % Dem_Memory_TimeSeries_IsPowertrainEnabled
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Memory_TimeSeries_IsPowertrainEnabled(
  void
)
{
  return (boolean)(DEM_CFG_SUPPORT_TIME_SERIES_POWERTRAIN == STD_ON);
}


#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 % Dem_Memory_TimeSeries_TestEntryDisplaceable
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Memory_TimeSeries_TestEntryDisplaceable(                                                                                     /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  Dem_Cfg_MemoryIndexType  MemoryIndex
)
{
  Dem_Memory_TimeSeries_EntryManager_ReadoutStatusType lReadoutStatus;
  lReadoutStatus = 
    Dem_Memory_TimeSeries_EntryManager_GetReadoutState(Dem_Memory_TimeSeries_GetEntryCompanionSafe(MemoryIndex));                /* SBSW_DEM_POINTER_WRITE_TIMESERIESENTRYCOMPANION */

  return (boolean)(lReadoutStatus == DEM_MEMORY_TIMESERIES_ENTRYMANAGER_READOUTSTATUS_UNLOCKED);
}
#endif



/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /*MD_MSR_MemMap */

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /*MD_MSR_MemMap */
/*!
 * \defgroup Dem_TimeSeries_Private Private Methods
 * \{
 */
/* ****************************************************************************
 * Dem_Memory_TimeSeries_FreeIndex
 *****************************************************************************/
/*!
 * \brief         Frees a time series entry
 *
 * \details       This function frees a time series entry.
 *
 * \param[in]     TimeSeriesIndex
 *                Time series memory index
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_FreeIndex(
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  TimeSeriesIndex
  );

 /* ****************************************************************************
 * Dem_Memory_TimeSeries_TestIndexIsTimeSeriesEntry
 *****************************************************************************/
 /*!
 * \brief         Test if given memory index is in range of time series entries
 *
 * \details       Test if given memory index is in range of time series entries
 *
 * \param[in]     MemoryIndex
 *                Handle of the memory block
 *
 * \return        TRUE
 *                Entry belongs to time series
 * \return        TRUE
 *                Entry does not belong to time series
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Memory_TimeSeries_TestIndexIsTimeSeriesEntry(
  Dem_Cfg_MemoryIndexType MemoryIndex
  );

/* ****************************************************************************
 * Dem_Memory_TimeSeries_AllocateIndex
 *****************************************************************************/
/*!
 * \brief         Selects a time series entry for an event
 *
 * \details       This function manages the time series snapshot data storage.
 *                If a free slot is available, it is returned directly. In case
 *                no free slot is available, the configured displacement
 *                algorithm is applied to free a slot.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        The memory index of the allocated time series entry if one
 *                could be identified. DEM_MEM_INVALID_MEMORY_INDEX if no entry
 *                was allocated.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Memory_TimeSeries_AllocateIndex(
  Dem_EventIdType EventId
  );


#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 * Dem_Memory_TimeSeries_ProcessCleanUp
 *****************************************************************************/
/*!
 * \brief         Processes asynchronous tasks to clean up the time series entries
 *
 * \details       Remove time series entries, which were requested to be deleted and
 *                are not used as virtual readout buffer any more.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_TIME_SERIES == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_ProcessCleanUp(
  void
  );
#endif

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/
 /*!
 * \}
 */
/* ****************************************************************************
 % Dem_Memory_TimeSeries_FreeIndex
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
*/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_FreeIndex(                                                                                                 /* PRQA S 3219 */ /* MD_DEM_14.1_CONFIGURATION_SWITCH */
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  TimeSeriesIndex
  )
{
#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
  Dem_MemState_MemoryInfoPtrType lMemoryInfo;

  lMemoryInfo = Dem_MemState_MemoryInfoInit(DEM_CFG_MEMORYID_TIMESERIES);
  Dem_MemAccess_MemoryFreeIndex(lMemoryInfo, TimeSeriesIndex);                                                                   /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(TimeSeriesIndex)                                                                              /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
}

/* ****************************************************************************
% Dem_Memory_TimeSeries_TestIndexIsTimeSeriesEntry
*****************************************************************************/
/*!
* Internal comment removed.
 *
 *
*/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Memory_TimeSeries_TestIndexIsTimeSeriesEntry(                                                                                /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  Dem_Cfg_MemoryIndexType MemoryIndex
  )
{
#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
  boolean lLowerBoundOk;
  boolean lUpperBoundOk;

  lLowerBoundOk = (Dem_Cfg_MemoryTimeSeriesStartIndex() <= MemoryIndex);
  lUpperBoundOk = ((Dem_Cfg_MemoryTimeSeriesStartIndex() + Dem_Cfg_GlobalTimeSeriesMaxCount()) > MemoryIndex);
  return (boolean)(lLowerBoundOk && lUpperBoundOk);
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryIndex)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return FALSE;
#endif
}

/* ****************************************************************************
 % Dem_Memory_TimeSeries_AllocateIndex
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
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Memory_TimeSeries_AllocateIndex(
  Dem_EventIdType EventId
  )
{
#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
  Dem_MemState_MemoryInfoPtrType lMemoryInfo;
  Dem_Cfg_MemoryIndexType lMemoryIndex;
  Dem_EventIdType lMasterEventId;

  lMemoryInfo = Dem_MemState_MemoryInfoInit(DEM_CFG_MEMORYID_TIMESERIES);
  lMasterEventId = Dem_Cfg_GetMasterEvent(EventId);

  if (Dem_MemState_MemoryGetMaxSize(lMemoryInfo) == Dem_MemState_MemoryGetCurrentSize(lMemoryInfo))                              /* SBSW_DEM_CALL_MEMORYINFO_POINTER */  /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
  { /* Memory is filled up */
    lMemoryIndex = Dem_MemAccess_SelectDisplacedIndex(lMemoryInfo, EventId);                                                     /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
    if (lMemoryIndex != DEM_MEM_INVALID_MEMORY_INDEX)
    { /* a displaced DTC was identified, now remove that DTC */
      Dem_EventIdType lDisplacedEventId;
      lDisplacedEventId = Dem_Memory_TimeSeries_GetEntrySafe(lMemoryIndex)->EventId;
      Dem_Event_DataUpdateStart(lDisplacedEventId);

      Dem_Memory_TimeSeries_FreeIndex(lMemoryIndex);

      Dem_Event_DataUpdateFinish(lDisplacedEventId);
    }
  }
  else
  { /* Memory is not full -> Find first free entry */
    lMemoryIndex = Dem_Memory_FindTimeSeriesIndex(DEM_EVENT_INVALID);
    /* if not found : lMemoryIndex == DEM_MEM_INVALID_MEMORY_INDEX */
  }

  if (lMemoryIndex != DEM_MEM_INVALID_MEMORY_INDEX)
  {
    Dem_Mem_TimeSeriesEntryPtrType lEntry;
    Dem_Mem_TimeSeriesEntryCompanionPtrType lEntryCompanion;
    uint8 lMemorySize;

    lEntry = Dem_Memory_TimeSeries_GetEntrySafe(lMemoryIndex);
    lEntryCompanion = Dem_Memory_TimeSeries_GetEntryCompanionSafe(lMemoryIndex);
    lMemorySize = Dem_MemState_MemoryGetCurrentSize(lMemoryInfo);                                                                /* SBSW_DEM_CALL_MEMORYINFO_POINTER */

    /* fill the chrono record with event id and lock the referenced time series slot */
    Dem_MemState_MemorySetChronology(lMemoryInfo, lMemorySize, lMemoryIndex);                                                    /* SBSW_DEM_CALL_MEMORYINFO_POINTER */

    Dem_Memory_TimeSeries_GetEntrySafe(lMemoryIndex)->EventId = lMasterEventId;                                                  /* SBSW_DEM_POINTER_WRITE_TIMESERIESENTRY */
    Dem_Memory_TimeSeries_GetEntrySafe(lMemoryIndex)->Timestamp = Dem_MemState_GetCurrentTimestamp();                            /* SBSW_DEM_POINTER_WRITE_TIMESERIESENTRY */

    Dem_Memory_TimeSeries_EntryManager_EntryInit(lEntry);                                                                        /* SBSW_DEM_POINTER_WRITE_TIMESERIESENTRY */
    Dem_Memory_TimeSeries_EntryManager_EntryCompanionInit(lEntryCompanion,                                                       /* SBSW_DEM_POINTER_WRITE_TIMESERIESENTRYCOMPANION */
      DEM_MEMORY_TIMESERIES_ENTRYMANAGER_READOUTSTATUS_UNLOCKED); 

    Dem_MemState_SetCurrentTimestamp(Dem_MemState_GetCurrentTimestamp() + 1u);
    Dem_MemState_MemorySetCurrentSize(lMemoryInfo, (uint8)(lMemorySize + 1u));                                                   /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
  }
  return lMemoryIndex;
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return DEM_MEM_INVALID_MEMORY_INDEX;
#endif
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 % Dem_Memory_TimeSeries_ProcessCleanUp
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_ProcessCleanUp(
  void
  )
{
  Dem_Memory_MemEntryIterType lTimeSeriesEntryIter;

  for (Dem_Memory_MemEntry_IterInit(DEM_CFG_MEMORYID_TIMESERIES, &lTimeSeriesEntryIter);                                         /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Memory_MemEntry_IterExists(&lTimeSeriesEntryIter);                                                                    /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Memory_MemEntry_IterNext(&lTimeSeriesEntryIter))                                                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_MemoryIndexType lMemoryIndex;
    lMemoryIndex = Dem_Memory_MemEntry_IterGetMemoryIndex(&lTimeSeriesEntryIter);                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */

    if (Dem_Memory_TimeSeries_TestEntryNeedToBeCleaned(lMemoryIndex))
    {
      Dem_Memory_TimeSeries_FreeIndex(lMemoryIndex);
      Dem_Nvm_SetTimeSeriesMemoryBlockState(lMemoryIndex, DEM_NVM_BLOCKSTATE_DIRTYIMMEDIATE);
    }
  }
}
#endif

#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /*MD_MSR_MemMap */

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /*MD_MSR_MemMap */
/*!
 * \addtogroup Dem_TimeSeries_Public
 * \{
 */

/* ****************************************************************************
 % Dem_Memory_TimeSeries_InvalidateEntryOfEvent
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
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_InvalidateEntryOfEvent(
  Dem_EventIdType EventId,
  uint8  BlockStatus
  )
{
#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
  {
    Dem_Cfg_MemoryIndexType lTimeSeriesIndex;

    lTimeSeriesIndex = Dem_Memory_FindTimeSeriesIndex(EventId);
    if (lTimeSeriesIndex != DEM_MEM_INVALID_MEMORY_INDEX)
    {
      Dem_Mem_TimeSeriesEntryCompanionPtrType lEntryCompanion;
      lEntryCompanion = Dem_Memory_TimeSeries_GetEntryCompanionSafe(lTimeSeriesIndex);

      /* request to remove the time series entry */
      if (Dem_Memory_TimeSeries_EntryManager_RequestDeletion(lEntryCompanion) == TRUE)                                           /* SBSW_DEM_POINTER_WRITE_TIMESERIESENTRYCOMPANION */
      {
        /* remove the time series entry immediately */
        Dem_Memory_TimeSeries_FreeIndex(lTimeSeriesIndex);
        Dem_Nvm_SetTimeSeriesMemoryBlockState(lTimeSeriesIndex, BlockStatus);
      }

    }
  }
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(BlockStatus)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
}

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 % Dem_Memory_TimeSeries_GetEntrySafe
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
*/
DEM_LOCAL_INLINE FUNC(Dem_Mem_TimeSeriesEntryPtrType, DEM_CODE)
Dem_Memory_TimeSeries_GetEntrySafe(
  Dem_Cfg_MemoryIndexType  MemoryIndex
)
{
  Dem_Mem_TimeSeriesEntryPtrType lReturnValue;

# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (Dem_Memory_TimeSeries_TestIndexIsTimeSeriesEntry(MemoryIndex) == FALSE)
  {
    Dem_Error_RunTimeCheckFailed(DEM_TIMESERIESIF_IMPLEMENTATION_FILENAME, __LINE__);                                              /* SBSW_DEM_POINTER_RUNTIME_CHECK */
    lReturnValue = (Dem_Mem_TimeSeriesEntryPtrType)Dem_Cfg_MemoryDataPtr[Dem_Cfg_MemoryTimeSeriesStartIndex()];                  /* PRQA S 0310, 3305 */ /* MD_DEM_11.4_nvm, MD_DEM_3305 */
  }
  else
# endif
  {
    lReturnValue = (Dem_Mem_TimeSeriesEntryPtrType)Dem_Cfg_MemoryDataPtr[MemoryIndex];                                           /* PRQA S 0310, 3305 */ /* MD_DEM_11.4_nvm, MD_DEM_3305 */
  }
  return lReturnValue;
}
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 % Dem_Memory_TimeSeries_GetEntryCompanionSafe
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
*/
DEM_LOCAL_INLINE FUNC(Dem_Mem_TimeSeriesEntryCompanionPtrType, DEM_CODE)
Dem_Memory_TimeSeries_GetEntryCompanionSafe(
  Dem_Cfg_MemoryIndexType  MemoryIndex
)
{
  Dem_Cfg_TimeSeriesEntryCompanionType* lReturnValue;
  uint8 lEntryCompanionIndex;
  lEntryCompanionIndex = MemoryIndex - Dem_Cfg_MemoryTimeSeriesStartIndex();

# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (lEntryCompanionIndex >= Dem_Cfg_GlobalTimeSeriesMaxCount())
  {
    Dem_Error_RunTimeCheckFailed(DEM_TIMESERIESIF_IMPLEMENTATION_FILENAME, __LINE__);                                              /* SBSW_DEM_POINTER_RUNTIME_CHECK */
    lReturnValue = &Dem_Cfg_TimeSeriesEntryCompanion[0u];                                                                        /* PRQA S 0310, 3305 */ /* MD_DEM_11.4_nvm, MD_DEM_3305 */
  }
  else
# endif
  {
    lReturnValue = &Dem_Cfg_TimeSeriesEntryCompanion[lEntryCompanionIndex];                                                       /* PRQA S 0310, 3305 */ /* MD_DEM_11.4_nvm, MD_DEM_3305 */
  }
  return lReturnValue;
}
#endif

/* ****************************************************************************
% Dem_Memory_TimeSeries_TestEventSupportNormal
*****************************************************************************/
/*!
* Internal comment removed.
 *
 *
 *
*/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Memory_TimeSeries_TestEventSupportNormal(                                                                                    /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
Dem_EventIdType  EventId                                                                                                         /* PRQA S 3206 */ /* MD_DEM_3206 */
)
{
  boolean lReturnValue;

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
  lReturnValue = (boolean)(Dem_Cfg_IsTimeSeriesNormalOfEventTable(EventId));
#else
    lReturnValue = FALSE;
#endif

  return lReturnValue;
}

/* ****************************************************************************
% Dem_Memory_TimeSeries_TestEventSupportFast
*****************************************************************************/
/*!
* Internal comment removed.
 *
 *
*/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Memory_TimeSeries_TestEventSupportFast(                                                                                      /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  Dem_EventIdType EventId                                                                                                        /* PRQA S 3206 */ /* MD_DEM_3206 */
)
{
  boolean lReturnValue;

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */

#if (DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON)
    lReturnValue = (boolean)(Dem_Cfg_IsTimeSeriesFastOfEventTable(EventId));
#else
    lReturnValue = FALSE;
#endif

  return lReturnValue;
}

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 % Dem_Memory_TimeSeries_UpdateNormalFutureSamples
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_UpdateNormalFutureSamples(
  void
  )
{
# if (DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_NORMAL == STD_ON)
  Dem_Memory_MemEntryIterType lTimeSeriesEntryIter;

  for (Dem_Memory_MemEntry_IterInit(DEM_CFG_MEMORYID_TIMESERIES, &lTimeSeriesEntryIter);                                         /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Memory_MemEntry_IterExists(&lTimeSeriesEntryIter);                                                                    /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Memory_MemEntry_IterNext(&lTimeSeriesEntryIter))                                                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_MemoryIndexType lMemoryIndex;
    Dem_Mem_TimeSeriesEntryPtrType lEntry;
    Dem_Mem_TimeSeriesEntryCompanionPtrType lEntryCompanion;

    lMemoryIndex = Dem_Memory_MemEntry_IterGetMemoryIndex(&lTimeSeriesEntryIter);                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
    lEntry = Dem_Memory_TimeSeries_GetEntrySafe(lMemoryIndex);
    lEntryCompanion = Dem_Memory_TimeSeries_GetEntryCompanionSafe(lMemoryIndex);

    if ( (lEntry->EventId != DEM_EVENT_INVALID)
      && (Dem_Memory_TimeSeries_TestEntryAvailable(lMemoryIndex) == TRUE))
    {
      Dem_Memory_TimeSeries_EntryManager_StoreNormalFutureSamples(lMemoryIndex, lEntry, lEntryCompanion);                        /* SBSW_DEM_POINTER_FORWARD_STACK */
    }
  }
# endif
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON)
/* ****************************************************************************
 % Dem_Memory_TimeSeries_UpdateFastFutureSamples
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_UpdateFastFutureSamples(
  void
  )
{
# if (DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_FAST == STD_ON)
  Dem_Memory_MemEntryIterType lTimeSeriesEntryIter;

  for (Dem_Memory_MemEntry_IterInit(DEM_CFG_MEMORYID_TIMESERIES, &lTimeSeriesEntryIter);                                         /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Memory_MemEntry_IterExists(&lTimeSeriesEntryIter);                                                                    /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Memory_MemEntry_IterNext(&lTimeSeriesEntryIter))                                                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_MemoryIndexType lMemoryIndex;
    Dem_Mem_TimeSeriesEntryPtrType lEntry;
    Dem_Mem_TimeSeriesEntryCompanionPtrType lEntryCompanion;

    lMemoryIndex = Dem_Memory_MemEntry_IterGetMemoryIndex(&lTimeSeriesEntryIter);                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
    lEntry = Dem_Memory_TimeSeries_GetEntrySafe(lMemoryIndex);
    lEntryCompanion = Dem_Memory_TimeSeries_GetEntryCompanionSafe(lMemoryIndex);                                                     

    if ( (lEntry->EventId != DEM_EVENT_INVALID)
      && (Dem_Memory_TimeSeries_TestEntryAvailable(lMemoryIndex) == TRUE) 
      && (Dem_Memory_TimeSeries_TestEventSupportFast(lEntry->EventId) == TRUE) )
    {
      Dem_Memory_TimeSeries_EntryManager_StoreFastFutureSamples(lMemoryIndex, lEntry, lEntryCompanion);                          /* SBSW_DEM_POINTER_WRITE_TIMESERIESENTRY */
    }
  }
# endif
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 % Dem_Memory_TimeSeries_TestEntryForEvent
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
Dem_Memory_TimeSeries_TestEntryForEvent(
  uint16 Index, 
  Dem_EventIdType EventId
  )
{
  Dem_EventIdType lEventId;
  boolean lEntryAvailable;

  lEventId = Dem_Memory_TimeSeries_GetEntrySafe((Dem_Cfg_MemoryIndexType)Index)->EventId; 
  lEntryAvailable = Dem_Memory_TimeSeries_TestEntryAvailable((Dem_Cfg_MemoryIndexType)Index);
  
  return (boolean)((lEventId == EventId) && (lEntryAvailable == TRUE));
}
#endif

/* ****************************************************************************
% Dem_Memory_TimeSeries_IsTimeSeriesPowertrainStoredByEvent
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
Dem_Memory_TimeSeries_IsTimeSeriesPowertrainStoredByEvent(                                                                       /* PRQA S 3219 */ /* MD_DEM_14.1_CONFIGURATION_SWITCH */
  Dem_EventIdType EventId
)
{
  boolean lReturn;
  lReturn = FALSE;


  if ((Dem_Memory_TimeSeries_IsPowertrainEnabled() == TRUE)
    && (Dem_Memory_TimeSeries_TestEventSupportTimeSeries(EventId) == TRUE)
    && (Dem_Memory_FindTimeSeriesIndex(EventId) != DEM_MEM_INVALID_MEMORY_INDEX)
    )
  {
    lReturn = TRUE;
  }

  return lReturn;
}

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 % Dem_Memory_TimeSeries_FreeEntry
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
Dem_Memory_TimeSeries_FreeEntry(
  uint16 Index
  )
{
  Dem_Memory_TimeSeries_GetEntrySafe((Dem_Cfg_MemoryIndexType)Index)->EventId = DEM_EVENT_INVALID;                                   /* SBSW_DEM_POINTER_WRITE_TIMESERIESENTRY */
  Dem_Memory_TimeSeries_GetEntrySafe((Dem_Cfg_MemoryIndexType)Index)->Timestamp = 0;                                                 /* SBSW_DEM_POINTER_WRITE_TIMESERIESENTRY */

/* No critical section needed for setting readout state and client counter since this entry-to-free function is unreachable for external APIs (Dem_EnableDtcRecordupdate). */
  Dem_Memory_TimeSeries_EntryManager_SetReadoutState(Dem_Memory_TimeSeries_GetEntryCompanionSafe((Dem_Cfg_MemoryIndexType)Index),
    DEM_MEMORY_TIMESERIES_ENTRYMANAGER_READOUTSTATUS_UNUSED);                                                                    /* SBSW_DEM_POINTER_WRITE_TIMESERIESENTRYCOMPANION */
  Dem_Memory_TimeSeries_EntryManager_InitClientCounter(Dem_Memory_TimeSeries_GetEntryCompanionSafe((Dem_Cfg_MemoryIndexType)Index)); /* SBSW_DEM_POINTER_WRITE_TIMESERIESENTRYCOMPANION */
}
#endif

/* ****************************************************************************
 % Dem_Memory_TimeSeries_Init
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_Init(
  void
  )
{
#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
  Dem_Memory_TimeSeries_RequestCleanUp = FALSE;
#endif
  Dem_Memory_TimeSeries_Sampler_Init();
  Dem_Memory_TimeSeries_RingBuffer_Init();
  Dem_Memory_TimeSeries_EntryManager_InitCompanionEntries();
}

/* ****************************************************************************
 % Dem_Memory_TimeSeries_InitNvData
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_InitNvData(
  void
)
{
#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
  Dem_MemState_MemoryInfoPtrType lMemoryInfo;
  Dem_Memory_MemEntryIterType lMemEntryIter;
  lMemoryInfo = Dem_MemState_MemoryInfoInit(DEM_CFG_MEMORYID_TIMESERIES);
  Dem_MemState_MemorySetCurrentSize(lMemoryInfo, 0);                                                                             /* SBSW_DEM_CALL_MEMORYINFO_POINTER */

  for (Dem_Memory_MemEntry_IterInit(DEM_CFG_MEMORYID_TIMESERIES, &lMemEntryIter);                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Memory_MemEntry_IterExists(&lMemEntryIter) == TRUE;                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Memory_MemEntry_IterNext(&lMemEntryIter))                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Mem_TimeSeriesEntryPtrType lEntry;
    Dem_Cfg_MemoryIndexType lMemoryIndex;

    lMemoryIndex = Dem_Memory_MemEntry_IterGetMemoryIndex(&lMemEntryIter);                                                       /* SBSW_DEM_CALL_ITERATOR_POINTER */
    lEntry = Dem_Memory_TimeSeries_GetEntrySafe(lMemoryIndex);
    Dem_MemCpy((Dem_NvDataPtrType)lEntry,                                                                                        /* PRQA S 0310, 0311, 0602 */ /* MD_DEM_11.4_cpy, MD_DEM_11.8, MD_DEM_20.2 */ /* SBSW_DEM_POINTER_MEMCPY_TIMESERIESENTRY */
                (Dem_ConstDataPtrType)(&Dem_Cfg_TimeSeriesEntryInit),                                                            /* PRQA S 0311 */ /* MD_DEM_11.8 */
                sizeof(*lEntry));
  }
#endif
}

/* ****************************************************************************
 % Dem_Memory_TimeSeries_RestoreOnInit
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
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_RestoreOnInit(
  void
)
{
#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
  Dem_MemState_MemoryInfoPtrType lMemoryInfo;
  Dem_Cfg_MemoryIndexType lTimeSeriesIndex;
  Dem_Mem_TimeSeriesEntryCompanionPtrType lEntryCompanion;

  lMemoryInfo = Dem_MemState_MemoryInfoInit(DEM_CFG_MEMORYID_TIMESERIES);
  Dem_MemState_MemorySetCurrentSize(lMemoryInfo, 0);                                                                             /* SBSW_DEM_CALL_MEMORYINFO_POINTER */

  /* Iterate through all time series entries. The iteration order must be identical to Dem_MemAccess_MemoryFindIndex. */
  for (lTimeSeriesIndex = Dem_MemState_MemoryGetFirstIndex(lMemoryInfo);                                                         /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
       lTimeSeriesIndex < Dem_MemState_MemoryGetLastIndex(lMemoryInfo);                                                          /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
       ++lTimeSeriesIndex)
  {
    Dem_EventIdType lEventId;

    lEventId = Dem_Memory_TimeSeries_GetEntrySafe(lTimeSeriesIndex)->EventId;
    if (lEventId != DEM_EVENT_INVALID)
    {
      uint32 lTimestamp;
      uint8 lSortedIndex;
      Dem_Cfg_MemoryIndexType lOtherIndex;

      if ( (lEventId >= Dem_Cfg_GlobalEventCount())
# if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
        || (lEventId != Dem_Cfg_GetMasterEvent(lEventId))                                                                        
# endif
        )
      {
        /* The time series entry is not allocated to the master event. Remove it. */
        lMemoryInfo->FreeEntryFctPtr(lTimeSeriesIndex);                                                                          /* SBSW_DEM_CALL_FUNCPTR_MEMORYINFO_POINTER */
        Dem_Nvm_SetTimeSeriesMemoryBlockState(lTimeSeriesIndex, DEM_NVM_BLOCKSTATE_DIRTYIMMEDIATE);

        /* DET: To get this inconsistency, it requires a configuration change without clearing the NV contents */
        Dem_Error_ReportError(DEM_INIT_APIID, DEM_E_INCONSISTENT_STATE);
        continue;                                                                                                                
      }

      /* find duplicate of time series entry */
      lOtherIndex = Dem_Memory_FindTimeSeriesIndex(lEventId);
      lTimestamp = Dem_Memory_TimeSeries_GetEntrySafe(lTimeSeriesIndex)->Timestamp;

      if (lOtherIndex != lTimeSeriesIndex)
      {
        /* Clear the older entry */
        if (lTimestamp > Dem_Memory_TimeSeries_GetEntrySafe(lOtherIndex)->Timestamp)
        {
          Dem_Memory_TimeSeries_FreeIndex(lOtherIndex);
          Dem_Nvm_SetTimeSeriesMemoryBlockState(lOtherIndex, DEM_NVM_BLOCKSTATE_DIRTYIMMEDIATE);
        }
        else
        {
          lMemoryInfo->FreeEntryFctPtr(lTimeSeriesIndex);                                                                        /* SBSW_DEM_CALL_FUNCPTR_MEMORYINFO_POINTER */
          Dem_Nvm_SetTimeSeriesMemoryBlockState(lTimeSeriesIndex, DEM_NVM_BLOCKSTATE_DIRTYIMMEDIATE);
          continue;                                                                                                              
        }
      }

      {
# if (DEM_CFG_PROCESS_CDTC_STOREDONLY == STD_ON) || (DEM_CFG_SUPPORT_TIME_SERIES_POWERTRAIN == STD_ON)
        /* clear time series entry if no primary entry for event is available */
        Dem_Cfg_MemoryIndexType lMemoryIndex;
        lMemoryIndex = Dem_Memory_FindIndex(lEventId);
        if (lMemoryIndex == DEM_MEM_INVALID_MEMORY_INDEX)
# else
        /* clear time series entry if CDTC bit of the DTC is not set */
        Dem_DTC_UDSStatusType lDTCStatus;
        lDTCStatus = Dem_DTC_RetrieveStatus(lEventId);
        if ((Dem_UDSStatus_Test_CDTC(lDTCStatus) == FALSE))
# endif
        {
          lMemoryInfo->FreeEntryFctPtr(lTimeSeriesIndex);                                                                        /* SBSW_DEM_CALL_FUNCPTR_MEMORYINFO_POINTER */
          Dem_Nvm_SetTimeSeriesMemoryBlockState(lTimeSeriesIndex, DEM_NVM_BLOCKSTATE_DIRTYIMMEDIATE);
          continue;
        }
      }

      /* reset the readout status and client counter for virtual buffer */
      lEntryCompanion = Dem_Memory_TimeSeries_GetEntryCompanionSafe(lTimeSeriesIndex);
      Dem_Memory_TimeSeries_EntryManager_SetReadoutState(lEntryCompanion,
                                                         DEM_MEMORY_TIMESERIES_ENTRYMANAGER_READOUTSTATUS_UNLOCKED);             /* SBSW_DEM_POINTER_WRITE_TIMESERIESENTRYCOMPANION */

      /* Synchronize the global timestamp with the timestamp stored in the time series entry */
      if (lTimestamp > Dem_MemState_GetCurrentTimestamp())
      {
        Dem_MemState_SetCurrentTimestamp(lTimestamp);
      }

      /* Sort the memory entry into the chronological list */
      lSortedIndex = Dem_MemState_MemoryGetCurrentSize(lMemoryInfo);                                                             /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
      while ( (lSortedIndex > 0u)
           && (Dem_Memory_TimeSeries_GetEntrySafe(Dem_MemState_MemoryGetChronology(lMemoryInfo, lSortedIndex - 1u))->Timestamp       /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
                > lTimestamp))                                 /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
      {
        Dem_MemState_MemorySetChronology(lMemoryInfo,                                                                            /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
          lSortedIndex,
          Dem_MemState_MemoryGetChronology(lMemoryInfo, lSortedIndex - 1u));                                                     /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
        --lSortedIndex;
      }

      Dem_MemState_MemorySetChronology(lMemoryInfo, lSortedIndex, lTimeSeriesIndex);                                             /* SBSW_DEM_CALL_MEMORYINFO_POINTER */

      /* Update the number of occupied memory entries */
      Dem_MemState_MemorySetCurrentSize(lMemoryInfo,                                                                             /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
        (uint8)(Dem_MemState_MemoryGetCurrentSize(lMemoryInfo) + 1u));                                                           /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
    }
  }
  /* Update the global timestamp */
  Dem_MemState_SetCurrentTimestamp(Dem_MemState_GetCurrentTimestamp() + 1u);
#endif
}                                                                                                                               /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_Memory_TimeSeries_CreateEntry
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
Dem_Memory_TimeSeries_CreateEntry(
  Dem_EventIdType  EventId
  )
{
  Dem_EventIdType lMemoryRepresentativeEventId;
  Dem_Cfg_MemoryIndexType lMemoryIndex;

  /* check if there is already a time series entry for this DTC */
  lMemoryRepresentativeEventId = Dem_Cfg_GetMemoryRepresentative(EventId);
  lMemoryIndex = Dem_Memory_FindTimeSeriesIndex(lMemoryRepresentativeEventId);

  if (lMemoryIndex == DEM_MEM_INVALID_MEMORY_INDEX)
  {
    /* get time series entry for this event if possible */
    lMemoryIndex = Dem_Memory_TimeSeries_AllocateIndex(EventId);

    if (lMemoryIndex != DEM_MEM_INVALID_MEMORY_INDEX)
    {
# if (DEM_FEATURE_NEED_TIME_SERIES_PAST == STD_ON)
      Dem_Memory_TimeSeries_EntryManager_StorePastSamples(EventId, lMemoryIndex);
# endif

# if (DEM_FEATURE_NEED_TIME_SERIES_FUTURE == STD_OFF)
      if (Dem_Cfg_EventSupportImmediateNv(EventId) == TRUE)
      {
        Dem_Nvm_SetTimeSeriesMemoryBlockState(lMemoryIndex, DEM_NVM_BLOCKSTATE_DIRTYIMMEDIATE);
      }
      else
# endif
      {
        Dem_Nvm_SetTimeSeriesMemoryBlockState(lMemoryIndex, DEM_NVM_BLOCKSTATE_DIRTY);
      }

# if (DEM_FEATURE_NEED_TIME_SERIES_FUTURE == STD_ON)
      {
        Dem_Mem_TimeSeriesEntryCompanionPtrType lEntryCompanion;
        lEntryCompanion = Dem_Memory_TimeSeries_GetEntryCompanionSafe(lMemoryIndex);

#  if (DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_NORMAL == STD_ON)
        /* determine missing future samples */
        Dem_Memory_TimeSeries_EntryManager_SetMissingNormalSamples(lEntryCompanion, Dem_Cfg_TimeSeriesFutureSamplesNormal());    /* SBSW_DEM_POINTER_WRITE_TIMESERIESENTRYCOMPANION */
#  endif
#  if (DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_FAST == STD_ON)
        if (Dem_Memory_TimeSeries_TestEventSupportFast(EventId) == TRUE)
        {
          Dem_Memory_TimeSeries_EntryManager_SetMissingFastSamples(lEntryCompanion, Dem_Cfg_TimeSeriesFutureSamplesFast());      /* SBSW_DEM_POINTER_WRITE_TIMESERIESENTRYCOMPANION */
        }
#  endif
      }
# endif
    }
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */


#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON) && (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Memory_TimeSeries_LockEntry
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_LockEntry(
  Dem_Cfg_MemoryIndexType MemoryIndex
)
{
  Dem_Memory_TimeSeries_EntryManager_Lock(Dem_Memory_TimeSeries_GetEntryCompanionSafe(MemoryIndex));                             /* SBSW_DEM_POINTER_WRITE_TIMESERIESENTRYCOMPANION */
}
#endif

#if ((DEM_FEATURE_NEED_TIME_SERIES == STD_ON) && (DEM_CFG_SUPPORT_DCM == STD_ON))
/* ****************************************************************************
 % Dem_Memory_TimeSeries_ReleaseEntry
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_ReleaseEntry(
  Dem_Cfg_MemoryIndexType MemoryIndex
)
{
  Dem_Mem_TimeSeriesEntryCompanionPtrType lEntryCompanion;
  lEntryCompanion = Dem_Memory_TimeSeries_GetEntryCompanionSafe(MemoryIndex);

  if (Dem_Memory_TimeSeries_EntryManager_ReleaseLock(lEntryCompanion) == TRUE)                                                   /* SBSW_DEM_POINTER_WRITE_TIMESERIESENTRYCOMPANION */
  {
    Dem_Memory_TimeSeries_RequestCleanUp = TRUE;
  }
}
#endif

/* ****************************************************************************
 % Dem_Memory_TimeSeries_ProcessWorkerTask
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_ProcessWorkerTask(
  void
  )
{
  Dem_Memory_TimeSeries_Sampler_ProcessWorkerTask();
#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
  if (Dem_Memory_TimeSeries_RequestCleanUp == TRUE)
  {
    Dem_Memory_TimeSeries_RequestCleanUp = FALSE;
    Dem_Memory_TimeSeries_ProcessCleanUp();
  }
#endif
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /*MD_MSR_MemMap */

#endif /* DEM_TIMESERIESIF_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_TimeSeriesIF_Implementation.h
 *********************************************************************************************************************/
