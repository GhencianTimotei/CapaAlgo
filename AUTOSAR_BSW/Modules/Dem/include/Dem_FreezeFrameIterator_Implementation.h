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
/*! \addtogroup Dem_FreezeFrameIterator
 *  \{
 *  \file       Dem_FreezeFrameIterator_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) Implementation file
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_FREEZEFRAMEITERATOR_IMPLEMENTATION_H)
#define DEM_FREEZEFRAMEITERATOR_IMPLEMENTATION_H

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
#include "Dem_FreezeFrameIterator_Interface.h"

/* Includes to access public functions belonging to other (top level)/ (logical)/- units to be used by this Unit */
/* ------------------------------------------------------------------------- */
#include "Dem_FaultMemory_Interface.h"
#include "Dem_RecordReader_Interface.h"
#include "Dem_Core_Interface.h"
#include "Dem_Infrastructure_Interface.h"
#include "Dem_DTCReporting_Interface.h"


/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*! Filename declaration */
#define DEM_FREEZEFRAMEITERATOR_IMPLEMENTATION_FILENAME "Dem_FreezeFrameIterator_Implementation.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_FreezeFrameIterator_Private Private Methods
 * \{
 */

#if ((DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_FEATURE_NEED_TIME_SERIES == STD_ON) && (DEM_CFG_SUPPORT_POWERTRAIN == STD_OFF))
/* ****************************************************************************
 * Dem_FreezeFrameIterator_TimeSeriesGetNextValidSRec
 *****************************************************************************/
/*!
 * \brief         Gets the next valid time series snapshot record number
 *
 * \details       Gets the next valid time series snapshot record number
 *
 * \param[in]     TimeSeriesEntry
 *                Pointer to the time series entry
 * \param[in]     RecordNumber
 *                Snapshot record number
 *
 * \return        Next valid record number larger than the given record number
 *
 * \pre           -
 * \config        (DEM_CFG_SUPPORT_DCM == STD_ON)
 *                && (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
 *                && (DEM_CFG_SUPPORT_POWERTRAIN == STD_OFF)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_FreezeFrameIterator_TimeSeriesGetNextValidSRec(
  CONST(Dem_Mem_ConstTimeSeriesEntryPtrType, AUTOMATIC)  TimeSeriesEntry,
  uint8  RecordNumber
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_SRECS == STD_ON) && (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 * Dem_FreezeFrameIterator_TimeSeriesSRecCount
 *****************************************************************************/
/*!
 * \brief         Counts the number of snapshot records stored in a time series
 *                entry
 *
 * \details       Counts the number of snapshot records stored in a time series
 *                entry
 *
 * \param[in]     TimeSeriesEntry
 *                Pointer to the time series entry
 *
 * \return        Number of stored time series snapshot records
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON &&
 *                DEM_FEATURE_NEED_TIME_SERIES == STD_ON &&
 *                DEM_CFG_SUPPORT_SRECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_FreezeFrameIterator_TimeSeriesSRecCount(
  CONST(Dem_Mem_ConstTimeSeriesEntryPtrType, AUTOMATIC)  TimeSeriesEntry
  );
#endif

 /* ****************************************************************************
 * Dem_FreezeFrameIterator_SetTimeSeriesPowertrainReportedState
 *****************************************************************************/
/*!
 * \brief         Set the time series powertrain reported state of a
 *                snapshot iterator.
 *
 * \details       Set the time series powertrain reported state of a
 *                snapshot iterator.
 *
 * \param[in,out] FreezeFrameFilterPtr
 *                Pointer to the current freeze frame filter
 * \param[in]     ReportedState
 *                New time series powertrain reported state
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different FreezeFrameIterator Ids
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_FreezeFrameIterator_SetTimeSeriesPowertrainReportedState(
  CONSTP2VAR(Dem_Cfg_FreezeFrameIterator_FilterType, AUTOMATIC, AUTOMATIC)  FreezeFrameFilterPtr,
  boolean ReportedState
);

/* ****************************************************************************
 * Dem_FreezeFrameIterator_GetTimeSeriesPowertrainReportedState
 *****************************************************************************/
/*!
 * \brief         Get the time series powertrain reported state of a
 *                snapshot iterator.
 *
 * \details       Get the time series powertrain reported state of a
 *                snapshot iterator.
 *
 * \param[in]     FreezeFrameFilterPtr
 *                Pointer to the current freeze frame filter
 *
 * \return        TRUE
 *                Time series powertrain was reported
 * \return        False
 *                Time series powertrain was not yet reported
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different FreezeFrameIterator Ids
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_FreezeFrameIterator_GetTimeSeriesPowertrainReportedState(
  CONSTP2CONST(Dem_Cfg_FreezeFrameIterator_FilterType, AUTOMATIC, AUTOMATIC)  FreezeFrameFilterPtr
);

/* ****************************************************************************
 * Dem_FreezeFrameIterator_SetFreezeFrameFilterData()
 *****************************************************************************/
/*!
 * \brief         Set the filter data of a freeze frame iterator.
 *
 * \details       Set the filter data of a freeze frame iterator.
 *
 * \param[in]     FreezeFrameIteratorId
 *                Index in FreezeFrameIteratorTable, derived from the ClientId.
 * \param[in]     FreezeFrameFilterData
 *                The freeze frame filter data to be set.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different FreezeFrameIterator Ids
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) 
Dem_FreezeFrameIterator_SetFreezeFrameFilterData(
  CONST(Dem_FreezeFrameIterator_HandleType, AUTOMATIC)  FreezeFrameIteratorId,
  CONST(Dem_Cfg_FreezeFrameIterator_FilterType, AUTOMATIC)  FreezeFrameFilterData
  );


/* ****************************************************************************
 * Dem_FreezeFrameIterator_GetFreezeFrameFilterData()
 *****************************************************************************/
/*!
 * \brief         Get the filter data of a freeze frame iterator.
 *
 * \details       Get the filter data of a freeze frame iterator.
 *
 * \param[in]     FreezeFrameIteratorId
 *                Index in FreezeFrameIteratorTable, derived from the ClientId.

 * \return        The filter data of the freeze frame iterator
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_FreezeFrameIterator_FilterType, DEM_CODE) 
Dem_FreezeFrameIterator_GetFreezeFrameFilterData(
  CONST(Dem_FreezeFrameIterator_HandleType, AUTOMATIC)  FreezeFrameIteratorId
  );


#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_FreezeFrameIterator_GetDTCFormat
 *****************************************************************************/
/*!
 * \brief         Get the DTCFormat of the FreezeFrameIterator.
 *
 * \details       Get the DTCFormat of the FreezeFrameIterator.
 *
 * \param[in]     FreezeFrameIteratorId
 *                Index in FreezeFrameIteratorTable, derived from the ClientId.
 *
 * \return        DEM_FREEZEFRAMEITERATOR_DTCFORMAT_INIT
 *                Initialization value, filter/iterator is unused.
 *
 *                DEM_FREEZEFRAMEITERATOR_DTCFORMAT_UDS
 *                The filter selects the 3-byte UDS DTC format
 *                (refer to configuration parameter DemUdsDTC).
 *
 *                DEM_FREEZEFRAMEITERATOR_DTCFORMAT_OBD
 *                The filter selects the 2-byte OBD DTC format
 *                (refer to configuration parameter DemObdDTC).
 *
 *                DEM_FREEZEFRAMEITERATOR_DTCFORMAT_J1939
 *                Selects the merged SPN + FMI to 3-byte J1939 DTC format
 *                (refer to configuration parameter DemJ1939DTC).
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different FreezeFrameIterator Ids
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_FreezeFrameIterator_DTCFormatType, DEM_CODE)
Dem_FreezeFrameIterator_GetDTCFormat(
  CONST(Dem_FreezeFrameIterator_HandleType, AUTOMATIC)  FreezeFrameIteratorId
  );
#endif


#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_FreezeFrameIterator_GetMemoryIndex
 *****************************************************************************/
/*!
 * \brief         Get the MemoryIndex of the FreezeFrameIterator.
 *
 * \details       Get the MemoryIndex of the FreezeFrameIterator.
 *
 * \param[in]     FreezeFrameIteratorId
 *                Index in FreezeFrameIteratorTable, derived from the ClientId.
 *
 * \return        The memory entry iterator position.
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different FreezeFrameIterator Ids
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_FreezeFrameIterator_GetMemoryIndex(
  CONST(Dem_FreezeFrameIterator_HandleType, AUTOMATIC)  FreezeFrameIteratorId
  );
#endif


#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
/* ****************************************************************************
 * Dem_FreezeFrameIterator_GetNodeId
 *****************************************************************************/
/*!
 * \brief         Get the node Id of the FreezeFrameIterator.
 *
 * \details       Get the node Id of the FreezeFrameIterator.
 *
 * \param[in]     FreezeFrameIteratorId
 *                Index in FreezeFrameIteratorTable, derived from the ClientId.
 *
 * \return        The node Id of the FreezeFrameIterator.
 *
 * \config        DEM_CFG_SUPPORT_J1939 == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different FreezeFrameIterator Ids
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_FreezeFrameIterator_GetNodeId(
  CONST(Dem_FreezeFrameIterator_HandleType, AUTOMATIC)  FreezeFrameIteratorId
  );
#endif


#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
/* ****************************************************************************
 * Dem_FreezeFrameIterator_GetFilterState
 *****************************************************************************/
/*!
 * \brief         Get the filter state of the FreezeFrameIterator.
 *
 * \details       Get the filter state of the FreezeFrameIterator.
 *
 * \param[in]     FreezeFrameIteratorId
 *                Index in FreezeFrameIteratorTable, derived from the ClientId.
 *
 * \return        The filter state of the FreezeFrameIterator.
 *
 * \config        DEM_CFG_SUPPORT_J1939 == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different FreezeFrameIterator Ids
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_FreezeFrameIterator_GetFilterState(
  CONST(Dem_FreezeFrameIterator_HandleType, AUTOMATIC)  FreezeFrameIteratorId
  );
#endif

#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) \
   && ((DEM_CFG_SUPPORT_SRECS == STD_ON) || (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)))
/* ****************************************************************************
 * Dem_FreezeFrameIterator_NextEvent
 *****************************************************************************/
/*!
 * \brief         Proceed FreezeFrameIterator to next event.
 *
 * \details       Proceed FreezeFrameIterator to next event memroy entry and 
 *                reset snapshot specific flags and iterators.
 *
 * \param[in,out] FreezeFrameFilterPtr
 *                Pointer to the current freeze frame filter
 * \param[in,out] MemEntryIter
 *                Pointer to processed and next event memory entry
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON and
 *                (DEM_CFG_SUPPORT_SRECS == STD_ON or
 *                DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different FreezeFrameIterator Ids
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_FreezeFrameIterator_NextEvent(
  CONSTP2VAR(Dem_Cfg_FreezeFrameIterator_FilterType, AUTOMATIC, AUTOMATIC)  FreezeFrameFilterPtr,
  CONSTP2VAR(Dem_Memory_MemEntryIterType, AUTOMATIC, AUTOMATIC) MemEntryIter
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
/* ****************************************************************************
 * Dem_FreezeFrameIterator_GetNextFilteredGlobalSRecNumber
 *****************************************************************************/
/*!
 * \brief         Filter for global snapshot
 *
 * \details       Filter for global snapshot
 *
 * \param[in,out] FreezeFrameFilterPtr
 *                Pointer to the freeze frame filter iterator
 *
 * \return        SRecNumber
 *                SRecNumber identifying the global SRec
 *
 * \pre           SnapshotEntryIter has been initialized
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON ||
 *                DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_FreezeFrameIterator_GetNextFilteredGlobalSRecNumber(
  CONSTP2VAR(Dem_Cfg_FreezeFrameIterator_FilterType, AUTOMATIC, AUTOMATIC)  FreezeFrameFilterPtr
  );
#endif


#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) \
   && ((DEM_CFG_SUPPORT_SRECS == STD_ON) || (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)))
/* ****************************************************************************
 * Dem_FreezeFrameIterator_FilterSRec
 *****************************************************************************/
/*!
 * \brief         Filters the snapshot records of events stored in primary
 *                memory.
 * \details       Filters the snapshot records of events stored in primary
 *                memory.
 *
 * \param[in]     FreezeFrameIteratorId
 *                The FreezeFrameIteratorId that defines the filter.
 * \param[out]    DTC
 *                Pointer to receive the UDS DTC number
 * \param[out]    RecordNumber
 *                Pointer to receive the snapshot record number
 *
 * \return        TRUE
 *                Next record was found
 *                FALSE
 *                No more record found
 *
 * \pre           The record filter has been initialized by
 *                Dem_SetFreezeFrameRecordFilter
 * \config        (DEM_CFG_SUPPORT_DCM == STD_ON)
 *                && ((DEM_CFG_SUPPORT_SRECS == STD_ON) 
 *                   || (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON))
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_FreezeFrameIterator_FilterSRec(
  CONST(Dem_FreezeFrameIterator_HandleType, AUTOMATIC)  FreezeFrameIteratorId,
  CONSTP2VAR(uint32, AUTOMATIC, DEM_DCM_DATA)  DTC,
  CONSTP2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  RecordNumber
  );
# endif


#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) \
   && ((DEM_CFG_SUPPORT_SRECS == STD_ON) || (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)))
/* ****************************************************************************
 * Dem_FreezeFrameIterator_GetNextFilteredSRecNumber
 *****************************************************************************/
 /*!
 * \brief         Get next stored Snapshot Record Number for an event.
 *
 * \details       Get next stored Snapshot Record Number for the provided event,
 *                based on the provided freeze frame filter data.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     FreezeFrameFilterPtr
 *                Pointer to the current freeze frame filter
 *
 * \return        RecordNumber
 *                Unique identifier of the next SRec
 *
 * \pre           The record filter has been initialized by
 *                Dem_SetFreezeFrameRecordFilter
 * \config        (DEM_CFG_SUPPORT_DCM == STD_ON)
 *                && ((DEM_CFG_SUPPORT_SRECS == STD_ON)
 *                   || (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON))
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_FreezeFrameIterator_GetNextFilteredSRecNumber(                                                                               /* PRQA S 2889 */ /* MD_DEM_15.5 */
  CONST(Dem_EventIdType, AUTOMATIC) EventId,
  CONSTP2VAR(Dem_Cfg_FreezeFrameIterator_FilterType, AUTOMATIC, AUTOMATIC)  FreezeFrameFilterPtr
);
#endif

#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) \
   && (DEM_CFG_SUPPORT_SRECS == STD_ON) )
/* ****************************************************************************
 * Dem_FreezeFrameIterator_GetNextFilteredEventSpecificSRecNumber
 *****************************************************************************/
 /*!
 * \brief         Get next stored Snapshot Record Number specific to the event.
 *
 * \details       Get next stored Snapshot Record Number specific to the event
 *                (which excludes Global Snapshot Records).
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     FreezeFrameFilterPtr
 *                Pointer to the current freeze frame filter
 *
 * \return        RecordNumber
 *                Unique identifier of the next SRec
 *
 * \pre           The record filter has been initialized by
 *                Dem_SetFreezeFrameRecordFilter
 * \config        (   DEM_CFG_SUPPORT_DCM   == STD_ON)
 *                && (DEM_CFG_SUPPORT_SRECS == STD_ON) )
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_FreezeFrameIterator_GetNextFilteredEventSpecificSRecNumber(                                                                  /* PRQA S 2889 */ /* MD_DEM_15.5 */
  CONST(Dem_EventIdType, AUTOMATIC) EventId,
  CONSTP2VAR(Dem_Cfg_FreezeFrameIterator_FilterType, AUTOMATIC, AUTOMATIC)  FreezeFrameFilterPtr
);
#endif

# if ((DEM_CFG_SUPPORT_SRECS == STD_ON) && (DEM_FEATURE_NEED_TIME_SERIES == STD_ON) && (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_POWERTRAIN == STD_OFF))
/* ****************************************************************************
 * Dem_FreezeFrameIterator_FilterTimeSeriesSRec
 *****************************************************************************/
/*!
 * \brief         Filters the time series snapshot records
 *
 * \details       Filters the time series snapshot records
 *
 * \param[in]     FreezeFrameIteratorId
 *                The FreezeFrameIteratorId that defines the filter.
 * \param[out]    DTC
 *                Pointer to receive the UDS DTC number
 * \param[out]    RecordNumber
 *                Pointer to receive the snapshot record number
 *
 * \return        TRUE
 *                Next record was found
 *                FALSE
 *                No more record found
 *
 * \pre           The record filter has been initialized by
 *                Dem_SetFreezeFrameRecordFilter
 * \config        (DEM_CFG_SUPPORT_DCM == STD_ON)
 *                && (DEM_CFG_SUPPORT_SRECS == STD_ON)
 *                && (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
 *                && (DEM_CFG_SUPPORT_POWERTRAIN == STD_OFF)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_FreezeFrameIterator_FilterTimeSeriesSRec(
  CONST(Dem_FreezeFrameIterator_HandleType, AUTOMATIC)  FreezeFrameIteratorId,
  CONSTP2VAR(uint32, AUTOMATIC, DEM_DCM_DATA)  DTC,
  CONSTP2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  RecordNumber
  );
# endif


#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) \
   && ((DEM_CFG_SUPPORT_SRECS == STD_ON) || (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)))
/* ****************************************************************************
 * Dem_FreezeFrameIterator_GetNumberOfSRec
 *****************************************************************************/
/*!
 * \brief         Gets the number of stored snapshot records
 *
 * \details       Gets the number of stored snapshot records
 *
 * \return        Number of stored records
 *
 * \pre           -
 * \config        (DEM_CFG_SUPPORT_DCM == STD_ON)
 *                && ((DEM_CFG_SUPPORT_SRECS == STD_ON) 
 *                   || (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON))
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_FreezeFrameIterator_GetNumberOfSRec(
  void
  );
# endif


# if (DEM_CFG_SUPPORT_SRECS == STD_ON) && (DEM_FEATURE_NEED_TIME_SERIES == STD_ON) && (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_POWERTRAIN == STD_OFF)
/* ****************************************************************************
 * Dem_FreezeFrameIterator_GetNumberOfTimeSeriesSRec
 *****************************************************************************/
/*!
 * \brief         Gets the number of stored time series snapshot records
 *
 * \details       Gets the number of stored time series snapshot records
 *
 * \return        number of stored records
 *
 * \pre           -
 * \config        (DEM_CFG_SUPPORT_DCM == STD_ON)
 *                && (DEM_CFG_SUPPORT_SRECS == STD_ON)
 *                && (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
 *                && (DEM_CFG_SUPPORT_POWERTRAIN == STD_OFF)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_FreezeFrameIterator_GetNumberOfTimeSeriesSRec(
  void
  );
# endif


#if (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON)
/* ****************************************************************************
 * Dem_FreezeFrameIterator_FindNextJ1939DTC
 *****************************************************************************/
/*!
 * \brief         Filters the next J1939 DTC
 *
 * \details       Filters the next J1939 DTC
 *
 * \param[in]     FreezeFrameIteratorId
 *                Current iteration handle
 * \param[in]     LastEventId
 *                Current iteration position
 * \param[in]     FreezeFrameKind
 *                DEM_J1939DCM_FREEZEFRAME 
 *                Find the next event with a freeze frame
 *                DEM_J1939DCM_EXPANDED_FREEZEFRAME 
 *                Find the next event with an expanded freeze frame
 *
 * \return        E_OK
 *                A DTC was returned
 * \return        DEM_NO_SUCH_ELEMENT
 *                No DTC left to iterate
 *
 * \pre           A J1939 freeze frame filter has been set up by 
 *                Dem_FreezeFrameIterator_StartJ1939Iterator
 * \config        DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_FreezeFrameIterator_FindNextJ1939DTC(
  CONST(Dem_FreezeFrameIterator_HandleType, AUTOMATIC)  FreezeFrameIteratorId,
  CONST(Dem_EventIdType, AUTOMATIC)  LastEventId,
  CONST(uint8, AUTOMATIC)  FreezeFrameKind
  );
#endif

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/
 #if ((DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_FEATURE_NEED_TIME_SERIES == STD_ON) && (DEM_CFG_SUPPORT_POWERTRAIN == STD_OFF))
/* ****************************************************************************
 % Dem_FreezeFrameIterator_TimeSeriesGetNextValidSRec
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
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_FreezeFrameIterator_TimeSeriesGetNextValidSRec(
  CONST(Dem_Mem_ConstTimeSeriesEntryPtrType, AUTOMATIC)  TimeSeriesEntry,
  uint8  RecordNumber
  )
{
  uint8 lNextRecord;

  lNextRecord = RecordNumber + 1u;

  if (lNextRecord < 0x30u)
  {
    if (lNextRecord < (0x10u + Dem_Memory_TimeSeries_EntryManager_GetUnusedPastSamplesFast(TimeSeriesEntry)))                    /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    {
      lNextRecord = 0x10u + Dem_Memory_TimeSeries_EntryManager_GetUnusedPastSamplesFast(TimeSeriesEntry);                        /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    }
    else
    if (lNextRecord >= (0x10u + ((Dem_Cfg_TimeSeriesPastSamplesFast() + Dem_Cfg_TimeSeriesFutureSamplesFast()) 
    - Dem_Memory_TimeSeries_EntryManager_GetUnusedFutureSamplesFast(TimeSeriesEntry))))                                          /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    {
      lNextRecord = 0x30u;
    }
    else
    {
      /* valid range - nothing to do here*/
    }
  }

  if (lNextRecord >= 0x30u)
  {
    if (lNextRecord < (0x30u + Dem_Memory_TimeSeries_EntryManager_GetUnusedPastSamplesNormal(TimeSeriesEntry)) )                 /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    {
      lNextRecord = 0x30u + Dem_Memory_TimeSeries_EntryManager_GetUnusedPastSamplesNormal(TimeSeriesEntry);                      /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    }
    else if (lNextRecord >= (0x30u + ((Dem_Cfg_TimeSeriesPastSamplesNormal() + Dem_Cfg_TimeSeriesFutureSamplesNormal()) 
    - Dem_Memory_TimeSeries_EntryManager_GetUnusedFutureSamplesNormal(TimeSeriesEntry))))                                        /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    {
      lNextRecord = 0x50u;
    }
    else
    {
      /* valid range - nothing to do here */
    }
  }
  return lNextRecord;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_SRECS == STD_ON) && (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 % Dem_FreezeFrameIterator_TimeSeriesSRecCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_FreezeFrameIterator_TimeSeriesSRecCount(                                                                                                    /* PRQA S 3219 */ /* MD_DEM_14.1_CONFIGURATION_SWITCH */
  CONST(Dem_Mem_ConstTimeSeriesEntryPtrType, AUTOMATIC)  TimeSeriesEntry
)
{
  uint8 lReturnValue;

  lReturnValue = 0u;

  lReturnValue += (Dem_Cfg_TimeSeriesPastSamplesNormal() 
  - Dem_Memory_TimeSeries_EntryManager_GetUnusedPastSamplesNormal(TimeSeriesEntry));                                             /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */

  lReturnValue += (Dem_Cfg_TimeSeriesFutureSamplesNormal() 
  - Dem_Memory_TimeSeries_EntryManager_GetUnusedFutureSamplesNormal(TimeSeriesEntry));                                           /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */

  lReturnValue += (Dem_Cfg_TimeSeriesPastSamplesFast() 
  - Dem_Memory_TimeSeries_EntryManager_GetUnusedPastSamplesFast(TimeSeriesEntry));                                               /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */

  lReturnValue += (Dem_Cfg_TimeSeriesFutureSamplesFast()
  - Dem_Memory_TimeSeries_EntryManager_GetUnusedFutureSamplesFast(TimeSeriesEntry));                                             /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif


/* ****************************************************************************
 % Dem_FreezeFrameIterator_SetTimeSeriesPowertrainReportedState
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_FreezeFrameIterator_SetTimeSeriesPowertrainReportedState(                                                                    /* PRQA S 3219 */ /* MD_DEM_14.1_CONFIGURATION_SWITCH */
  CONSTP2VAR(Dem_Cfg_FreezeFrameIterator_FilterType, AUTOMATIC, AUTOMATIC)  FreezeFrameFilterPtr,                                /* PRQA S 3673 */ /* MD_DEM_8.13_fp */
  boolean ReportedState
)
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(FreezeFrameFilterPtr)                                                                         /* PRQA S 1338, 3112 */ /* MD_MSR_DummyStmt, MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_ARGUMENT(ReportedState)                                                                                      /* PRQA S 1338, 3112 */ /* MD_MSR_DummyStmt, MD_DEM_14.2 */

#if DEM_CFG_SUPPORT_TIME_SERIES_POWERTRAIN == STD_ON
    FreezeFrameFilterPtr->TimeSeriesSnapshotReported = ReportedState;                                                            /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
#endif
}

/* ****************************************************************************
% Dem_FreezeFrameIterator_GetTimeSeriesPowertrainReportedState
*****************************************************************************/
/*!
* Internal comment removed.
 *
 *
*/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_FreezeFrameIterator_GetTimeSeriesPowertrainReportedState(                                                                    /* PRQA S 3219 */ /* MD_DEM_14.1_CONFIGURATION_SWITCH */
  CONSTP2CONST(Dem_Cfg_FreezeFrameIterator_FilterType, AUTOMATIC, AUTOMATIC)  FreezeFrameFilterPtr
)
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(FreezeFrameFilterPtr)                                                                         /* PRQA S 1338, 3112 */ /* MD_MSR_DummyStmt, MD_DEM_14.2 */

#if DEM_CFG_SUPPORT_TIME_SERIES_POWERTRAIN == STD_ON
    return FreezeFrameFilterPtr->TimeSeriesSnapshotReported;                                                                     /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
#else
    return TRUE;
#endif
}

/* ****************************************************************************
 % Dem_FreezeFrameIterator_SetFreezeFrameFilterData()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) 
Dem_FreezeFrameIterator_SetFreezeFrameFilterData(                                                                                /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_FreezeFrameIterator_HandleType, AUTOMATIC)  FreezeFrameIteratorId,
  CONST(Dem_Cfg_FreezeFrameIterator_FilterType, AUTOMATIC)  FreezeFrameFilterData
  )
{
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (FreezeFrameIteratorId >= Dem_Cfg_GetSizeOfFreezeFrameIteratorTable())
  {
    Dem_Error_RunTimeCheckFailed(DEM_FREEZEFRAMEITERATOR_IMPLEMENTATION_FILENAME, __LINE__);                                     /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    Dem_Cfg_SetFreezeFrameIteratorTable(FreezeFrameIteratorId, FreezeFrameFilterData);                                           /* PRQA S 2841 */ /* MD_DEM_Dir4.1_RunTimeCheckWriteOperation */ /* SBSW_DEM_ARRAY_WRITE_FREEZEFRAMEITERATORTABLE */ 
  }
}

/* ****************************************************************************
 % Dem_FreezeFrameIterator_GetFreezeFrameFilterData()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_FreezeFrameIterator_FilterType, DEM_CODE) 
Dem_FreezeFrameIterator_GetFreezeFrameFilterData(                                                                                /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_FreezeFrameIterator_HandleType, AUTOMATIC)  FreezeFrameIteratorId
  )
{
  return Dem_Cfg_GetFreezeFrameIteratorTable(FreezeFrameIteratorId);
}

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_FreezeFrameIterator_GetDTCFormat
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_FreezeFrameIterator_DTCFormatType, DEM_CODE)
Dem_FreezeFrameIterator_GetDTCFormat(
  CONST(Dem_FreezeFrameIterator_HandleType, AUTOMATIC)  FreezeFrameIteratorId
  )
{
  return Dem_FreezeFrameIterator_GetFreezeFrameFilterData(FreezeFrameIteratorId).FilterDTCFormat;
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_FreezeFrameIterator_GetMemoryIndex
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_FreezeFrameIterator_GetMemoryIndex(                                                                                          /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_FreezeFrameIterator_HandleType, AUTOMATIC)  FreezeFrameIteratorId
  )
{
  return Dem_FreezeFrameIterator_GetFreezeFrameFilterData(FreezeFrameIteratorId).MemoryIndex;
}
#endif

#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
/* ****************************************************************************
 % Dem_FreezeFrameIterator_GetNodeId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_FreezeFrameIterator_GetNodeId(                                                                                               /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_FreezeFrameIterator_HandleType, AUTOMATIC)  FreezeFrameIteratorId
  )
{
  return Dem_FreezeFrameIterator_GetFreezeFrameFilterData(FreezeFrameIteratorId).NodeId;
}
#endif

#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
/* ****************************************************************************
 % Dem_FreezeFrameIterator_GetFilterState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_FreezeFrameIterator_GetFilterState(                                                                                          /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_FreezeFrameIterator_HandleType, AUTOMATIC)  FreezeFrameIteratorId
  )
{
  return Dem_FreezeFrameIterator_GetFreezeFrameFilterData(FreezeFrameIteratorId).FilterState;
}
#endif


#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) \
   && ((DEM_CFG_SUPPORT_SRECS == STD_ON) || (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)))
/* ****************************************************************************
 % Dem_FreezeFrameIterator_NextEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_FreezeFrameIterator_NextEvent(
  CONSTP2VAR(Dem_Cfg_FreezeFrameIterator_FilterType, AUTOMATIC, AUTOMATIC)  FreezeFrameFilterPtr,
  CONSTP2VAR(Dem_Memory_MemEntryIterType, AUTOMATIC, AUTOMATIC) MemEntryIter
  )
{
  Dem_Memory_MemEntry_IterNext(MemEntryIter);                                                                                    /* PRQA S 2469 */ /* MD_DEM_14.2_LoopControlHandledInternally */ /* SBSW_DEM_CALL_ITERATOR_POINTER */
  FreezeFrameFilterPtr->MemoryIndex = Dem_Memory_MemEntry_IterGetMemoryIndex(MemEntryIter);                                      /* SBSW_DEM_POINTER_FORWARD_STACK */ /* SBSW_DEM_CALL_ITERATOR_POINTER */
  Dem_SnapshotEntry_IteratorInit(DEM_EVENT_INVALID, DEM_MEMORYENTRY_HANDLE_INVALID, &FreezeFrameFilterPtr->SnapshotEntryIter);   /* SBSW_DEM_POINTER_FORWARD_STACK */

# if(DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
  FreezeFrameFilterPtr->GlobalSnapshotReported = FALSE;                                                                          /* SBSW_DEM_POINTER_FORWARD_STACK */
# endif
# if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON) && (DEM_CFG_SUPPORT_TIME_SERIES_POWERTRAIN == STD_ON)
  FreezeFrameFilterPtr->TimeSeriesSnapshotReported = FALSE;                                                                      /* SBSW_DEM_POINTER_FORWARD_STACK */
# endif
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
/* ****************************************************************************
 % Dem_FreezeFrameIterator_GetNextFilteredGlobalSRecNumber
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_FreezeFrameIterator_GetNextFilteredGlobalSRecNumber(
  CONSTP2VAR(Dem_Cfg_FreezeFrameIterator_FilterType, AUTOMATIC, AUTOMATIC)  FreezeFrameFilterPtr
  )
{
  uint8 lRecordNumber;
  lRecordNumber = DEM_FREEZEFRAMEITERATOR_INVALID_RECORDNUMBER;

  if (FreezeFrameFilterPtr->GlobalSnapshotReported == FALSE)
  {
     Dem_Cfg_MemoryEntryHandleType lMemoryEntryId;
     lMemoryEntryId = Dem_MemoryEntry_GetId(FreezeFrameFilterPtr->MemoryIndex);

    /* Global snapshot not yet reported for this memory entry */
    if (Dem_MemoryEntry_TestGlobalSnapshotRecordStored(lMemoryEntryId) == TRUE)
    {
      lRecordNumber = Dem_Cfg_GlobalSRecId();
      FreezeFrameFilterPtr->GlobalSnapshotReported = TRUE;                                                                       /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    }
  }
  return lRecordNumber;
}
#endif /* (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON) */

#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) \
   && ((DEM_CFG_SUPPORT_SRECS == STD_ON) || (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)))
/* ****************************************************************************
 % Dem_FreezeFrameIterator_FilterSRec
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
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_FreezeFrameIterator_FilterSRec(                                                                                              /* PRQA S 2889 */ /* MD_DEM_15.5 */
  CONST(Dem_FreezeFrameIterator_HandleType, AUTOMATIC)  FreezeFrameIteratorId,
  CONSTP2VAR(uint32, AUTOMATIC, DEM_DCM_DATA)  DTC,                                                                              /* PRQA S 3673 */ /* MD_DEM_8.13 */
  CONSTP2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  RecordNumber
  )
{
  Dem_Memory_MemEntryIterType MemEntryIter;
  Dem_Cfg_FreezeFrameIterator_FilterType lFreezeFrameFilterData;

  lFreezeFrameFilterData = Dem_FreezeFrameIterator_GetFreezeFrameFilterData(FreezeFrameIteratorId);

  for (Dem_Memory_MemEntry_IterResume_FromIndex(DEM_CFG_MEMORYID_PRIMARY, lFreezeFrameFilterData.MemoryIndex, &MemEntryIter);    /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Memory_MemEntry_IterExists(&MemEntryIter) == TRUE;)                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_MemoryEntryHandleType lMemoryEntryId;
    Dem_EventIdType lEventId;

    lMemoryEntryId = Dem_MemoryEntry_GetId(lFreezeFrameFilterData.MemoryIndex);
    lEventId = Dem_MemoryEntry_GetEventId(lMemoryEntryId);

    if ( (Dem_Event_TestValidHandle(lEventId) == TRUE)
      && (Dem_DTC_TestSuppressionOnDtcRetrieval(lEventId) == FALSE) )                                                            /* PRQA S 3415 */ /* MD_DEM_13.5_cf */                                                            
    {
      /* Skip Events which do not have an OBD DTC but filter is set for OBD format */
      if ( (Dem_Cfg_EventObdRelated(lEventId) == TRUE)
        || (lFreezeFrameFilterData.FilterDTCFormat != DEM_FREEZEFRAMEITERATOR_DTCFORMAT_OBD) )
      {
        /* Special case - skip Dependent OBD DTCs */
        if ((Dem_DTCReporting_TestObdHideOccurrences() == FALSE)
          || (Dem_Cfg_EventSignificance(lEventId) != DEM_CFG_EVENT_SIGNIFICANCE_OCCURRENCE)
          || (Dem_Cfg_EventObdRelated(lEventId) == FALSE))
        {
          uint8 lRecordNumber;

          /* Initialize Snapshot Iterator */
          if (Dem_SnapshotEntry_IteratorGetMemoryEntryHandle(&lFreezeFrameFilterData.SnapshotEntryIter) == DEM_MEMORYENTRY_HANDLE_INVALID) /* SBSW_DEM_POINTER_FORWARD_STACK */
          {
#  if (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
            Dem_SnapshotEntry_CombinationOnRetrival_IteratorInit(lEventId, lMemoryEntryId, &lFreezeFrameFilterData.SnapshotEntryIter); /* SBSW_DEM_POINTER_FORWARD_STACK */
#  else
            Dem_SnapshotEntry_IteratorInit(lEventId, lMemoryEntryId, &lFreezeFrameFilterData.SnapshotEntryIter);                 /* SBSW_DEM_POINTER_FORWARD_STACK */
#  endif
          }

          /* Get next filtered record number */
          lRecordNumber = Dem_FreezeFrameIterator_GetNextFilteredSRecNumber(lEventId, &lFreezeFrameFilterData);                  /* SBSW_DEM_POINTER_FORWARD_STACK */
          if (lRecordNumber != DEM_FREEZEFRAMEITERATOR_INVALID_RECORDNUMBER)
          {
            *RecordNumber = lRecordNumber;                                                                                       /* SBSW_DEM_POINTER_WRITE_ARGUMENT */

            /* Assign DTC in requested format */
            if (lFreezeFrameFilterData.FilterDTCFormat == DEM_FREEZEFRAMEITERATOR_DTCFORMAT_OBD)
            {
              *DTC = (uint32)(((uint32)Dem_Cfg_EventObdDtc(lEventId)) << 8u);                                                    /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
            }
            else
# if (DEM_CFG_SUPPORT_J1939 == STD_ON)
            if (lFreezeFrameFilterData.FilterDTCFormat == DEM_FREEZEFRAMEITERATOR_DTCFORMAT_J1939)
            {
              *DTC = Dem_Cfg_EventJ1939Dtc(lEventId);                                                                            /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
            }
            else
# endif
            { /* Only EventIds with a valid DTC number are processed here */
              /* -> DTC mapping will always return a valid DTC number */
              *DTC = Dem_Cfg_EventUdsDtc(lEventId);                                                                              /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
            }

            Dem_FreezeFrameIterator_SetFreezeFrameFilterData(FreezeFrameIteratorId, lFreezeFrameFilterData);
            return TRUE;
          }
        }
      }
    }
    Dem_FreezeFrameIterator_NextEvent(&lFreezeFrameFilterData, &MemEntryIter);                                                   /* PRQA S 2469 */ /* MD_DEM_14.2_LoopControlHandledInternally */ /* SBSW_DEM_POINTER_FORWARD_STACK */ /* SBSW_DEM_CALL_ITERATOR_POINTER */

# if (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
    Dem_DTC_SetCombinedGroupProcessed(Dem_Cfg_EventCombinedGroup(lEventId), lFreezeFrameFilterData.ProcessedCombinedDTCGroups);  /* SBSW_DEM_POINTER_FORWARD_STACK */
# endif
  }

  Dem_FreezeFrameIterator_SetFreezeFrameFilterData(FreezeFrameIteratorId, lFreezeFrameFilterData);
  return FALSE;
}                                                                                                                                /* PRQA S 6030, 6050, 6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
#endif

#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) \
  && ((DEM_CFG_SUPPORT_SRECS == STD_ON) || (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)))
/* ****************************************************************************
 % Dem_FreezeFrameIterator_GetNextFilteredSRecNumber
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
Dem_FreezeFrameIterator_GetNextFilteredSRecNumber(                                                                               /* PRQA S 2889 */ /* MD_DEM_15.5 */
  CONST(Dem_EventIdType, AUTOMATIC) EventId,
  CONSTP2VAR(Dem_Cfg_FreezeFrameIterator_FilterType, AUTOMATIC, AUTOMATIC)  FreezeFrameFilterPtr
  )
{
  uint8 lRecordNumber;
  lRecordNumber = DEM_FREEZEFRAMEITERATOR_INVALID_RECORDNUMBER;

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 1338, 3112 */ /* MD_MSR_DummyStmt, MD_DEM_14.2 */


  # if(DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON) && (DEM_CFG_SUPPORT_SRECS_CONFIGURED == STD_ON)
  /* Global snapshots for configured snapshots */
  lRecordNumber = Dem_FreezeFrameIterator_GetNextFilteredGlobalSRecNumber(FreezeFrameFilterPtr);                                 /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  # endif

  # if (DEM_CFG_SUPPORT_SRECS == STD_ON)
  if (lRecordNumber == DEM_FREEZEFRAMEITERATOR_INVALID_RECORDNUMBER)
  {
    lRecordNumber = Dem_FreezeFrameIterator_GetNextFilteredEventSpecificSRecNumber(EventId, FreezeFrameFilterPtr);               /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }
  # endif

  # if(DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON) && (DEM_CFG_SUPPORT_SRECS_CALCULATED == STD_ON)
  if (lRecordNumber == DEM_FREEZEFRAMEITERATOR_INVALID_RECORDNUMBER)
  {
    /* Global snapshots for calculated snapshots */
    lRecordNumber = Dem_FreezeFrameIterator_GetNextFilteredGlobalSRecNumber(FreezeFrameFilterPtr);                               /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }
  # endif

  return lRecordNumber;
}
#endif


#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) \
   && (DEM_CFG_SUPPORT_SRECS == STD_ON) )
/* ****************************************************************************
 % Dem_FreezeFrameIterator_GetNextFilteredEventSpecificSRecNumber
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
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_FreezeFrameIterator_GetNextFilteredEventSpecificSRecNumber(                                                                  /* PRQA S 2889 */ /* MD_DEM_15.5 */
  CONST(Dem_EventIdType, AUTOMATIC) EventId,
  CONSTP2VAR(Dem_Cfg_FreezeFrameIterator_FilterType, AUTOMATIC, AUTOMATIC)  FreezeFrameFilterPtr
)
{
  uint8 lRecordNumber;
  lRecordNumber = DEM_FREEZEFRAMEITERATOR_INVALID_RECORDNUMBER;

  /* Normal snapshots */
  #  if (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
  if (Dem_DTC_TestCombinedGroupProcessed(Dem_Cfg_EventCombinedGroup(EventId),                                                    /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    FreezeFrameFilterPtr->ProcessedCombinedDTCGroups) == FALSE)
  #  endif
  {
    if (Dem_SnapshotEntry_SearchStoredEntry(&FreezeFrameFilterPtr->SnapshotEntryIter) == TRUE)                                   /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    {
      lRecordNumber = Dem_SnapshotEntry_IteratorGetStoredRecordNumber(&FreezeFrameFilterPtr->SnapshotEntryIter);                 /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */

      if ((lRecordNumber > DEM_FREEZEFRANEITERATOR_TIMESERIES_POWERTRAIN_RECORDNUMBER)
        && (Dem_Memory_TimeSeries_IsTimeSeriesPowertrainStoredByEvent(EventId) == TRUE)
        && (Dem_FreezeFrameIterator_GetTimeSeriesPowertrainReportedState(FreezeFrameFilterPtr) == FALSE)                         /* PRQA S 3415 */ /* MD_DEM_13.5_cf */ /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
        )
      {
        lRecordNumber = DEM_FREEZEFRANEITERATOR_TIMESERIES_POWERTRAIN_RECORDNUMBER;
        Dem_FreezeFrameIterator_SetTimeSeriesPowertrainReportedState(FreezeFrameFilterPtr, TRUE);                                /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
      }
      else
      {
        /* Increment in global state, the next iteration will continue with the next record */
  #  if (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
        Dem_SnapshotEntry_CombinationOnRetrival_IteratorNext(&FreezeFrameFilterPtr->SnapshotEntryIter);                          /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  #  else
        Dem_SnapshotEntry_IteratorNext(&FreezeFrameFilterPtr->SnapshotEntryIter);                                                /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  #  endif
      }
    }
    else if ((Dem_Memory_TimeSeries_IsTimeSeriesPowertrainStoredByEvent(EventId) == TRUE)
          && (Dem_FreezeFrameIterator_GetTimeSeriesPowertrainReportedState(FreezeFrameFilterPtr) == FALSE)                       /* PRQA S 3415 */ /* MD_DEM_13.5_cf */ /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
      )
    {
      lRecordNumber = DEM_FREEZEFRANEITERATOR_TIMESERIES_POWERTRAIN_RECORDNUMBER;
      Dem_FreezeFrameIterator_SetTimeSeriesPowertrainReportedState(FreezeFrameFilterPtr, TRUE);                                  /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    }
    else
    {
      /* MISRA Case */
    }
  }

  return lRecordNumber;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif


# if ((DEM_CFG_SUPPORT_SRECS == STD_ON) && (DEM_FEATURE_NEED_TIME_SERIES == STD_ON) && (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_POWERTRAIN == STD_OFF))
/* ****************************************************************************
 % Dem_FreezeFrameIterator_FilterTimeSeriesSRec
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
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_FreezeFrameIterator_FilterTimeSeriesSRec(                                                                                    /* PRQA S 2889 */ /* MD_DEM_15.5 */
  CONST(Dem_FreezeFrameIterator_HandleType, AUTOMATIC)  FreezeFrameIteratorId,
  CONSTP2VAR(uint32, AUTOMATIC, DEM_DCM_DATA)  DTC,                                                                              /* PRQA S 3673 */ /* MD_DEM_8.13 */
  CONSTP2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  RecordNumber
  )
{
  Dem_Memory_MemEntryIterType MemEntryIter;
  Dem_Cfg_FreezeFrameIterator_FilterType lFreezeFrameFilterData;

  lFreezeFrameFilterData = Dem_FreezeFrameIterator_GetFreezeFrameFilterData(FreezeFrameIteratorId);

  for (Dem_Memory_MemEntry_IterResume_FromIndex(DEM_CFG_MEMORYID_TIMESERIES, lFreezeFrameFilterData.MemoryIndex, &MemEntryIter); /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Memory_MemEntry_IterExists(&MemEntryIter) == TRUE;)                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_EventIdType lEventId;
    Dem_Mem_ConstTimeSeriesEntryPtrType lTimeSeriesEntry;
    
    lTimeSeriesEntry = Dem_Memory_TimeSeries_GetEntrySafe(lFreezeFrameFilterData.MemoryIndex);
    lEventId = lTimeSeriesEntry->EventId;

    if ( (Dem_Event_TestValidHandle(lEventId) == TRUE)
      && (Dem_DTC_TestSuppressionOnDtcRetrieval(lEventId) == FALSE) )                                                            /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
    {
      /* suppress record for OBD related events if the confirmed bit is not qualified yet.
      UDS only events are not taken into account or OBD related events which have a qualified DCY */

      /* Skip Events which do not have an OBD DTC but filter is set for OBD format */
      if ( (Dem_Cfg_EventObdRelated(lEventId) == TRUE)
        || (lFreezeFrameFilterData.FilterDTCFormat != DEM_FREEZEFRAMEITERATOR_DTCFORMAT_OBD) )
      {
        /* Special case - skip Dependent OBD DTCs */
        if ( (Dem_DTCReporting_TestObdHideOccurrences() == FALSE)
          || (Dem_Cfg_EventSignificance(lEventId) != DEM_CFG_EVENT_SIGNIFICANCE_OCCURRENCE)                                      
          || (Dem_Cfg_EventObdRelated(lEventId) == FALSE) )                                                                      
        {
          if (lFreezeFrameFilterData.TimeSeriesRecordNumber < 0x10u)
          {
            lFreezeFrameFilterData.TimeSeriesRecordNumber = Dem_FreezeFrameIterator_TimeSeriesGetNextValidSRec(lTimeSeriesEntry, lFreezeFrameFilterData.TimeSeriesRecordNumber);            /* SBSW_DEM_POINTER_WRITE_TIMESERIESENTRY */
          }

          if (lFreezeFrameFilterData.TimeSeriesRecordNumber <= 0x4fu)
          {
            if (Dem_Dcm_TimeSeriesSRecIsValid(lEventId, lFreezeFrameFilterData.TimeSeriesRecordNumber) == TRUE)
            {
              if (Dem_FreezeFrameIterator_TimeSeriesSRecIsStored(lTimeSeriesEntry, lFreezeFrameFilterData.TimeSeriesRecordNumber) == FALSE)     /* SBSW_DEM_POINTER_WRITE_TIMESERIESENTRY */
              {
                /* Continue immediately with the next possible record in this iteration, the Dcm always expects a record */
                lFreezeFrameFilterData.TimeSeriesRecordNumber = Dem_FreezeFrameIterator_TimeSeriesGetNextValidSRec(lTimeSeriesEntry, lFreezeFrameFilterData.TimeSeriesRecordNumber);        /* SBSW_DEM_POINTER_WRITE_TIMESERIESENTRY */
                continue;                                                                                                        
              }
            }
            else
            {
              /* Continue immediately with the next possible record in this iteration, the Dcm always expects a record */
              lFreezeFrameFilterData.TimeSeriesRecordNumber = Dem_FreezeFrameIterator_TimeSeriesGetNextValidSRec(lTimeSeriesEntry, lFreezeFrameFilterData.TimeSeriesRecordNumber);          /* SBSW_DEM_POINTER_WRITE_TIMESERIESENTRY */
              continue;                                                                                                          
            }

            if (lFreezeFrameFilterData.FilterDTCFormat == DEM_FREEZEFRAMEITERATOR_DTCFORMAT_OBD)
            {
              *DTC = (uint32)(((uint32)Dem_Cfg_EventObdDtc(lEventId)) << 8u);                                                    /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
            }
            else
            { /* Only EventIds with a valid DTC number are processed here */
              /* -> DTC mapping will always return a valid DTC number */
              *DTC = Dem_Cfg_EventUdsDtc(lEventId);                                                                              /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
            }

            *RecordNumber = lFreezeFrameFilterData.TimeSeriesRecordNumber;                                                       /* SBSW_DEM_POINTER_WRITE_ARGUMENT */

            /* Increment in global state, the next iteration will continue with the next record */
            lFreezeFrameFilterData.TimeSeriesRecordNumber = Dem_FreezeFrameIterator_TimeSeriesGetNextValidSRec(lTimeSeriesEntry, lFreezeFrameFilterData.TimeSeriesRecordNumber); /* SBSW_DEM_POINTER_WRITE_TIMESERIESENTRY */
            Dem_FreezeFrameIterator_SetFreezeFrameFilterData(FreezeFrameIteratorId, lFreezeFrameFilterData);
            return TRUE;
          }
        }
      }
    }
    Dem_Memory_MemEntry_IterNext(&MemEntryIter);                                                                                 /* PRQA S 2469 */ /* MD_DEM_14.2_LoopControlHandledInternally */ /* SBSW_DEM_CALL_ITERATOR_POINTER */
    lFreezeFrameFilterData.MemoryIndex = Dem_Memory_MemEntry_IterGetMemoryIndex(&MemEntryIter);                                  /* SBSW_DEM_CALL_ITERATOR_POINTER */
    lFreezeFrameFilterData.TimeSeriesRecordNumber = 0x00;
  }
  Dem_FreezeFrameIterator_SetFreezeFrameFilterData(FreezeFrameIteratorId, lFreezeFrameFilterData);

  return FALSE;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
# endif

#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) \
   && ((DEM_CFG_SUPPORT_SRECS == STD_ON) || (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)))
/* ****************************************************************************
 % Dem_FreezeFrameIterator_GetNumberOfSRec
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
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_FreezeFrameIterator_GetNumberOfSRec(
  void
  )
{
  Dem_Memory_MemEntryIterType MemEntryIter;
  uint16 lRecordCount;


# if (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
  Dem_Cfg_ProcessedCombinedDTCGroupType lProcessedCombinedDTCGroups;
  Dem_DTC_InitCombinedGroupProcessed(lProcessedCombinedDTCGroups);                                                               /* SBSW_DEM_POINTER_FORWARD_STACK */
# endif
 
  /* Count stored snapshot records in primary memory to prevent concurrent modification
  of the chrono index to have an effect on the iteration */
  lRecordCount = 0u;
  for (Dem_Memory_MemEntry_IterInit(DEM_CFG_MEMORYID_PRIMARY, &MemEntryIter);                                                    /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Memory_MemEntry_IterExists(&MemEntryIter) == TRUE;                                                                    /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Memory_MemEntry_IterNext(&MemEntryIter))                                                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_EventIdType lEventId;
    Dem_Cfg_MemoryEntryHandleType lMemoryEntryId;

    lMemoryEntryId = Dem_Memory_MemEntry_IterGetEntryId(&MemEntryIter);                                                          /* SBSW_DEM_CALL_ITERATOR_POINTER */
    lEventId = Dem_MemoryEntry_GetEventId(lMemoryEntryId);

    if ( (Dem_Event_TestValidHandle(lEventId) == TRUE)
      && (Dem_DTC_TestSuppressionOnDtcRetrieval(lEventId) == FALSE) )                                                            /* PRQA S 3415 */ /* MD_DEM_13.5_cf */                                                            
    {
      if ((Dem_DTCReporting_TestObdHideOccurrences() == FALSE)
        || (Dem_Cfg_EventSignificance(lEventId) != DEM_CFG_EVENT_SIGNIFICANCE_OCCURRENCE)                                        
        || (Dem_Cfg_EventObdRelated(lEventId) == FALSE))                                                                         
      {
        /* Occupied Entry */
# if (DEM_CFG_SUPPORT_SRECS == STD_ON)
#  if (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
        if (Dem_Cfg_EventIsCombined(lEventId) == TRUE)
        {
          Dem_Cfg_CombinedGroupIndexType lGroupId;
          lGroupId = Dem_Cfg_EventCombinedGroup(lEventId);

          if (Dem_DTC_TestCombinedGroupProcessed(lGroupId, lProcessedCombinedDTCGroups) == FALSE)                                /* SBSW_DEM_POINTER_FORWARD_STACK */
          {
            Dem_DTC_SetCombinedGroupProcessed(lGroupId, lProcessedCombinedDTCGroups);                                            /* SBSW_DEM_POINTER_FORWARD_STACK */
            lRecordCount = (uint16)(lRecordCount +                                                                               /* SBSW_DEM_CALL_ITERATOR_POINTER */
              Dem_SnapshotEntry_GetNumberOfStoredCombinedSnapshotRecords(MemEntryIter, lGroupId)); 
          }
        }
        else
#  endif
        {
          lRecordCount = (uint16)(lRecordCount + Dem_SnapshotEntry_GetNumberOfStoredSnapshotRecords(lMemoryEntryId));
        }
# endif

        if (Dem_Memory_TimeSeries_IsPowertrainEnabled() == TRUE)
        {
          if ((Dem_Memory_TimeSeries_TestEventSupportTimeSeries(lEventId) == TRUE)
            && (Dem_Memory_FindTimeSeriesIndex(lEventId) != DEM_MEM_INVALID_MEMORY_INDEX))
          {
            lRecordCount = lRecordCount + 1u;
          }
        }

# if (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
        if (Dem_MemoryEntry_TestGlobalSnapshotRecordStored(lMemoryEntryId) == TRUE)
        {
          lRecordCount++;
        }
# endif
      }
    }

  }

  return lRecordCount;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif

# if (DEM_CFG_SUPPORT_SRECS == STD_ON) && (DEM_FEATURE_NEED_TIME_SERIES == STD_ON) && (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_POWERTRAIN == STD_OFF)
/* ****************************************************************************
 % Dem_FreezeFrameIterator_GetNumberOfTimeSeriesSRec
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
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
  Dem_FreezeFrameIterator_GetNumberOfTimeSeriesSRec(
  void
  )
{
  Dem_Memory_MemEntryIterType MemEntryIter;
  uint16 lRecordCount;

  lRecordCount = 0u;

  for (Dem_Memory_MemEntry_IterInit(DEM_CFG_MEMORYID_TIMESERIES, &MemEntryIter);                                                 /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Memory_MemEntry_IterExists(&MemEntryIter) == TRUE;                                                                    /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Memory_MemEntry_IterNext(&MemEntryIter))                                                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_MemoryIndexType lMemoryIndex;
    Dem_EventIdType lEventId;

    lMemoryIndex = Dem_Memory_MemEntry_IterGetMemoryIndex(&MemEntryIter);                                                        /* SBSW_DEM_CALL_ITERATOR_POINTER */
    lEventId = Dem_Memory_TimeSeries_GetEntrySafe(lMemoryIndex)->EventId;
    if ( (Dem_Event_TestValidHandle(lEventId) == TRUE)
      && (Dem_DTC_TestSuppressionOnDtcRetrieval(lEventId) == FALSE) )                                                            /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
    {
      if ( (Dem_DTCReporting_TestObdHideOccurrences() == FALSE)
        || (Dem_Cfg_EventSignificance(lEventId) != DEM_CFG_EVENT_SIGNIFICANCE_OCCURRENCE)                                        /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
        || (Dem_Cfg_EventObdRelated(lEventId) == FALSE))                                                                         /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
      {
        /* Occupied entry */
        lRecordCount = (uint16)(lRecordCount + Dem_FreezeFrameIterator_TimeSeriesSRecCount(Dem_Memory_TimeSeries_GetEntrySafe(lMemoryIndex)));          /* SBSW_DEM_POINTER_WRITE_TIMESERIESENTRY */
      }
    }
  }

  return lRecordCount;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
# endif

#if (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON)
/* ****************************************************************************
 % Dem_FreezeFrameIterator_FindNextJ1939DTC
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
Dem_FreezeFrameIterator_FindNextJ1939DTC(
  CONST(Dem_FreezeFrameIterator_HandleType, AUTOMATIC)  FreezeFrameIteratorId,
  CONST(Dem_EventIdType, AUTOMATIC)  LastEventId,
  CONST(uint8, AUTOMATIC)  FreezeFrameKind
  )
{
  Dem_EventIdType lEventId;
  Dem_Cfg_EventJ1939NodeIterType lNodeIter;

  for (lEventId = LastEventId; lEventId <= Dem_Cfg_GlobalPrimaryLast(); lEventId++)
  {
    if (Dem_DTC_TestSuppressionOnDtcRetrieval(lEventId) == TRUE)
    { /* Don't match suppressed events */
      continue;                                                                                                                  
    }
    if (Dem_DTCInternalStatus_GetStoredStatus(Dem_DTC_GetInternalStatus(lEventId)) == Dem_DTCInternalStatus_StoredStatus_None)
    { /* only consider stored events */
      continue;                                                                                                                  
    }

    if ( ((FreezeFrameKind == DEM_J1939DCM_FREEZEFRAME) && (Dem_Cfg_EventJ1939FFExists(lEventId) == FALSE))                      
      || ((FreezeFrameKind == DEM_J1939DCM_EXPANDED_FREEZEFRAME) && (Dem_Cfg_EventJ1939ExpFFExists(lEventId) == FALSE)) )        
    { /* the event does not support the requested data (also: no J1939 DTC) */
      continue;                                                                                                                  
    }

# if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
    if (lEventId != Dem_Cfg_GetMasterEvent(lEventId))
    { /* Don't match dependent combined events, only the group event */
      continue;                                                                                                                  
    }
# endif

    for (Dem_Cfg_EventJ1939NodeIterInit(lEventId, &lNodeIter);                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Cfg_EventJ1939NodeIterExists(&lNodeIter) == TRUE;                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Cfg_EventJ1939NodeIterNext(&lNodeIter))                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      if (Dem_FreezeFrameIterator_GetNodeId(FreezeFrameIteratorId) == Dem_Cfg_EventJ1939NodeIterGet(&lNodeIter))                 /* SBSW_DEM_CALL_ITERATOR_POINTER */
      {
        break;
      }
    }
    if (Dem_Cfg_EventJ1939NodeIterExists(&lNodeIter) == FALSE)                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
    { /* The DTC is not supported on the requested node */
      continue;                                                                                                                  
    }

    /* Found a candidate */
    break;
  }

  if (lEventId > Dem_Cfg_GlobalPrimaryLast())
  { /* Did not find a candidate */
    lEventId = DEM_EVENT_INVALID;
  }

  return lEventId;
}                                                                                                                                /* PRQA S 6010, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCAL */
#endif


/*!
 * \}
 */
# define DEM_STOP_SEC_CODE
# include "MemMap.h"                                                                                                             /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DEFINITIONS
 *********************************************************************************************************************/
# define DEM_START_SEC_CODE
# include "MemMap.h"                                                                                                             /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \addtogroup Dem_FreezeFrameIterator_Public
 * \{
 */

#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) || (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON) )
/* ****************************************************************************
 % Dem_FreezeFrameIterator_InitDefault
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_FreezeFrameIterator_InitDefault(
  CONST(Dem_FreezeFrameIterator_HandleType, AUTOMATIC)  FreezeFrameIteratorId
  )
{
  Dem_Cfg_FreezeFrameIterator_FilterType lFreezeFrameFilterData;
  lFreezeFrameFilterData = Dem_FreezeFrameIterator_GetFreezeFrameFilterData(FreezeFrameIteratorId);

# if (DEM_CFG_SUPPORT_DCM == STD_ON)
  lFreezeFrameFilterData.FilterDTCFormat = DEM_FREEZEFRAMEITERATOR_DTCFORMAT_INIT;
# endif
# if (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON)
  lFreezeFrameFilterData.FilterState = DEM_FREEZEFRAMEITERATOR_J1939STATE_INIT;
# endif

  Dem_FreezeFrameIterator_SetFreezeFrameFilterData(FreezeFrameIteratorId, lFreezeFrameFilterData);
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_FreezeFrameIterator_TestFilterSet
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_FreezeFrameIterator_TestFilterSet(
  CONST(Dem_FreezeFrameIterator_HandleType, AUTOMATIC)  FreezeFrameIteratorId
  )
{
  return (boolean)(Dem_FreezeFrameIterator_GetDTCFormat(FreezeFrameIteratorId) != DEM_FREEZEFRAMEITERATOR_DTCFORMAT_INIT);
}
#endif

#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
/* ****************************************************************************
 % Dem_FreezeFrameIterator_TestJ1939FreezeFrameFilterSet
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_FreezeFrameIterator_TestJ1939FreezeFrameFilterSet(
  CONST(Dem_FreezeFrameIterator_HandleType, AUTOMATIC)  FreezeFrameIteratorId
  )
{
  return (boolean)(Dem_FreezeFrameIterator_GetFilterState(FreezeFrameIteratorId) != DEM_FREEZEFRAMEITERATOR_J1939STATE_INIT);
}
#endif

#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) \
   && ((DEM_CFG_SUPPORT_SRECS == STD_ON) || (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)))
/* ****************************************************************************
 % Dem_FreezeFrameIterator_StartIterator
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_FreezeFrameIterator_StartIterator(
  CONST(Dem_FreezeFrameIterator_HandleType, AUTOMATIC)  FreezeFrameIteratorId,
  CONST(Dem_FreezeFrameIterator_DTCFormatType, AUTOMATIC)  FilterDTCFormat,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  )
{
  Dem_Cfg_SnapshotEntry_IterType lSnapshotEntryIter;
  Dem_Cfg_FreezeFrameIterator_FilterType lFreezeFrameFilterData;

  Dem_SnapshotEntry_IteratorInit(DEM_EVENT_INVALID, DEM_MEMORYENTRY_HANDLE_INVALID, &lSnapshotEntryIter);                        /* SBSW_DEM_POINTER_FORWARD_STACK */


  lFreezeFrameFilterData = Dem_FreezeFrameIterator_GetFreezeFrameFilterData(FreezeFrameIteratorId);
  lFreezeFrameFilterData.MemoryIndex = MemoryIndex;
  lFreezeFrameFilterData.SnapshotEntryIter = lSnapshotEntryIter;
  lFreezeFrameFilterData.FilterDTCFormat = FilterDTCFormat;
# if(DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
  lFreezeFrameFilterData.GlobalSnapshotReported = FALSE;
# endif
# if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
#  if DEM_CFG_SUPPORT_TIME_SERIES_POWERTRAIN == STD_ON
   lFreezeFrameFilterData.TimeSeriesSnapshotReported = FALSE;
#  endif
  lFreezeFrameFilterData.TimeSeriesRecordNumber = 0u;
# endif  
# if (DEM_CFG_SUPPORT_J1939 == STD_ON)
  lFreezeFrameFilterData.FilterState = DEM_FREEZEFRAMEITERATOR_J1939STATE_INIT;
# endif
# if (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
  Dem_DTC_InitCombinedGroupProcessed(lFreezeFrameFilterData.ProcessedCombinedDTCGroups);                                         /* SBSW_DEM_POINTER_FORWARD_STACK */
# endif
  Dem_FreezeFrameIterator_SetFreezeFrameFilterData(FreezeFrameIteratorId, lFreezeFrameFilterData);
}
#endif

#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) \
   && ((DEM_CFG_SUPPORT_SRECS == STD_ON) || (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)))
/* ****************************************************************************
 % Dem_FreezeFrameIterator_GetNext
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_FreezeFrameIterator_GetNext(
CONST(Dem_FreezeFrameIterator_HandleType, AUTOMATIC)    FreezeFrameIteratorId,
P2VAR(uint32, AUTOMATIC, DEM_DCM_DATA)                  DTC,                                                                     /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_8.13 */
P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)                   RecordNumber                                                             /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_8.13 */
)
{
  boolean lReturnValue;
  lReturnValue = FALSE;

  if (Dem_FreezeFrameIterator_FilterSRec(FreezeFrameIteratorId, DTC, RecordNumber) == TRUE)                                      /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  {
    lReturnValue = TRUE;
  }
# if ((DEM_FEATURE_NEED_TIME_SERIES == STD_ON) && (DEM_CFG_SUPPORT_POWERTRAIN == STD_OFF))
  else
  {
    Dem_Cfg_FreezeFrameIterator_FilterType lFreezeFrameFilterData;

    lFreezeFrameFilterData = Dem_FreezeFrameIterator_GetFreezeFrameFilterData(FreezeFrameIteratorId);

    if (lFreezeFrameFilterData.MemoryIndex < Dem_Memory_GetFirstMemoryIndex(DEM_CFG_MEMORYID_TIMESERIES))
    {
      lFreezeFrameFilterData.MemoryIndex = Dem_Memory_GetFirstMemoryIndex(DEM_CFG_MEMORYID_TIMESERIES);
      Dem_FreezeFrameIterator_SetFreezeFrameFilterData(FreezeFrameIteratorId, lFreezeFrameFilterData);
    }

    if (Dem_FreezeFrameIterator_FilterTimeSeriesSRec(FreezeFrameIteratorId, DTC, RecordNumber) == TRUE)                          /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    {
      lReturnValue = TRUE;
    }
  }
# endif

  return lReturnValue;
}
#endif

#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) \
   && ((DEM_CFG_SUPPORT_SRECS == STD_ON) || (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)))
/* ****************************************************************************
 % Dem_FreezeFrameIterator_GetNumberOfFreezeFrameRecords
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
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_FreezeFrameIterator_GetNumberOfFreezeFrameRecords(
  void
  )
{
  uint16 lRecordCount;
  
  /* Count stored snapshot records */
  lRecordCount = Dem_FreezeFrameIterator_GetNumberOfSRec();
# if ((DEM_FEATURE_NEED_TIME_SERIES == STD_ON) && (DEM_CFG_SUPPORT_POWERTRAIN == STD_OFF))
  lRecordCount = (uint16)(lRecordCount + Dem_FreezeFrameIterator_GetNumberOfTimeSeriesSRec());
# endif
  return lRecordCount;
}
#endif

#if (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON)
/* ****************************************************************************
 % Dem_FreezeFrameIterator_StartJ1939Iterator
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
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_FreezeFrameIterator_StartJ1939Iterator(
  CONST(Dem_FreezeFrameIterator_HandleType, AUTOMATIC)  FreezeFrameIteratorId,
  CONST(Dem_J1939DcmSetFreezeFrameFilterType, AUTOMATIC)  FreezeFrameKind,
  CONST(uint8, AUTOMATIC)  NodeId
  )
{
  Std_ReturnType lReturnValue;

# if (DEM_CFG_SUPPORT_J1939_FREEZEFRAME == STD_ON)
  if (FreezeFrameKind == DEM_J1939DCM_FREEZEFRAME)
  {
    lReturnValue = E_OK;
  }
  else
# endif
# if (DEM_CFG_SUPPORT_J1939_EXPANDED_FREEZEFRAME == STD_ON)
  if (FreezeFrameKind == DEM_J1939DCM_EXPANDED_FREEZEFRAME)
  {
    lReturnValue = E_OK;
  }
  else
# endif
  {
    lReturnValue = E_NOT_OK;
  }

  if (lReturnValue == E_OK)
  {
    Dem_Cfg_FreezeFrameIterator_FilterType lFreezeFrameFilterData;
    lFreezeFrameFilterData = Dem_FreezeFrameIterator_GetFreezeFrameFilterData(FreezeFrameIteratorId);

    lFreezeFrameFilterData.FreezeFrameKind = FreezeFrameKind;
    lFreezeFrameFilterData.EventId = Dem_Cfg_GlobalPrimaryFirst();
    lFreezeFrameFilterData.NodeId = NodeId;
    lFreezeFrameFilterData.FilterState = DEM_FREEZEFRAMEITERATOR_J1939STATE_USED;
# if (DEM_CFG_SUPPORT_DCM == STD_ON)
    lFreezeFrameFilterData.FilterDTCFormat = DEM_FREEZEFRAMEITERATOR_DTCFORMAT_INIT;
# endif

    Dem_FreezeFrameIterator_SetFreezeFrameFilterData(FreezeFrameIteratorId, lFreezeFrameFilterData);
  }

  return lReturnValue;
}
#endif

#if (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON)
/* ****************************************************************************
 % Dem_FreezeFrameIterator_GetNextJ1939FreezeFrame
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
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_FreezeFrameIterator_GetNextJ1939FreezeFrame(
  CONST(Dem_FreezeFrameIterator_HandleType, AUTOMATIC)  FreezeFrameIteratorId,
  CONSTP2VAR(uint32, AUTOMATIC, DEM_J1939DCM_DATA)  J1939DTC,
  CONSTP2VAR(uint8, AUTOMATIC, DEM_J1939DCM_DATA)  OccurrenceCounter,
  CONSTP2VAR(uint8, AUTOMATIC, DEM_J1939DCM_DATA)  DestBuffer,
  CONSTP2VAR(uint8, AUTOMATIC, DEM_J1939DCM_DATA)  BufSize 
  )
{
  Std_ReturnType lReturnValue;

  Dem_Cfg_FreezeFrameIterator_FilterType lFreezeFrameFilterData;
  lFreezeFrameFilterData = Dem_FreezeFrameIterator_GetFreezeFrameFilterData(FreezeFrameIteratorId);
  
  lReturnValue = DEM_NO_SUCH_ELEMENT;
  
  if (lFreezeFrameFilterData.EventId != DEM_EVENT_INVALID)
  {
    boolean lCopyData;

    lCopyData = FALSE;
    if (lFreezeFrameFilterData.FilterState == DEM_FREEZEFRAMEITERATOR_J1939STATE_PENDING)
    { /* process event again if still stored. This event is already the
       * combined group event in case of combination, so no aditional check
       * in this context */
      if (Dem_DTCInternalStatus_GetStoredStatus(Dem_DTC_GetInternalStatus(lFreezeFrameFilterData.EventId)) != Dem_DTCInternalStatus_StoredStatus_None)
      {
        lCopyData = TRUE;
      }
      else
      { /* proceed with next EventId */
        lFreezeFrameFilterData.EventId = lFreezeFrameFilterData.EventId + 1u;
        lFreezeFrameFilterData.FilterState = DEM_FREEZEFRAMEITERATOR_J1939STATE_USED;
      }
    }

    if (lFreezeFrameFilterData.FilterState == DEM_FREEZEFRAMEITERATOR_J1939STATE_USED)
    { /* Search the next/first J1939DTC which is currently stored */
      lFreezeFrameFilterData.EventId = Dem_FreezeFrameIterator_FindNextJ1939DTC(FreezeFrameIteratorId, 
                                                                                lFreezeFrameFilterData.EventId, 
                                                                                lFreezeFrameFilterData.FreezeFrameKind);

      if (lFreezeFrameFilterData.EventId == DEM_EVENT_INVALID)
      { /* primary EventId range exceeded, finish processing */
        lFreezeFrameFilterData.EventId = DEM_EVENT_INVALID;
        lFreezeFrameFilterData.FilterState = DEM_FREEZEFRAMEITERATOR_J1939STATE_USED;
      }
      else
      {
        lCopyData = TRUE;
      }
    }

    if (lCopyData == TRUE)
    {
      Dem_Cfg_MemoryIndexType lMemoryIndex;
      uint8 lUpdateState;
      boolean lModificationDetected;

      lMemoryIndex = Dem_Memory_FindIndex(lFreezeFrameFilterData.EventId);

      if (lMemoryIndex != DEM_MEM_INVALID_MEMORY_INDEX)
      {
        lUpdateState = Dem_Event_GetDataCommitState(lFreezeFrameFilterData.EventId);
        lModificationDetected = FALSE;

        /* check for concurrent access to the memory entry */
        if (Dem_Event_TestDataUpdateInProgress(lUpdateState) == FALSE)
        {
          Dem_Cfg_MemoryEntryHandleType lMemoryEntryId;
          Dem_ConstSharedDataPtrType lFreezeFramePtr;
          uint8  lSize;
          Dem_MemoryEntry_OccurrenceCounterType lOccurrenceCounter;
          uint16 lSourceOffset;

          lMemoryEntryId = Dem_MemoryEntry_GetId(lMemoryIndex);
          lFreezeFramePtr = Dem_MemoryEntry_GetJ1939FreezeFramePtr(lMemoryEntryId);
          lSourceOffset = 0u;
          /* set the source buffer offset and the size to copy */
          if (lFreezeFrameFilterData.FreezeFrameKind == DEM_J1939DCM_FREEZEFRAME)
          {            
            lSize = (uint8)Dem_Cfg_GlobalJ1939FFRawSize();
          }
          else
          {
# if (DEM_CFG_SUPPORT_J1939_FREEZEFRAME == STD_ON) && (DEM_CFG_SUPPORT_J1939_EXPANDED_FREEZEFRAME == STD_ON)
            lSourceOffset = Dem_Cfg_GlobalJ1939FFRawSize();
# endif
            lSize = (uint8)Dem_Cfg_GlobalJ1939ExpFFRawSize();
          }

          if (*BufSize >= lSize)
          {
            Dem_MemCpy(DestBuffer, &(lFreezeFramePtr[lSourceOffset]), lSize);                                                    /* PRQA S 0311, 0602 */ /* MD_DEM_11.8, MD_DEM_20.2 */ /* SBSW_DEM_POINTER_WRITE_ARGUMENT_BUFFER */

            *BufSize = lSize;                                                                                                    /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
            *J1939DTC = Dem_Cfg_EventJ1939Dtc(lFreezeFrameFilterData.EventId);                                                   /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
            lOccurrenceCounter = Dem_MemoryEntry_GetOccurrenceCounter(lMemoryEntryId);

            if (lOccurrenceCounter > 0x7eU)
            { /* Occurrence counter > 126u shall be reported as 126 */
              lOccurrenceCounter = 0x7eU;
            }

            *OccurrenceCounter = (uint8)lOccurrenceCounter;                                                                      /* SBSW_DEM_POINTER_WRITE_ARGUMENT */

            if (lUpdateState != Dem_Event_GetDataCommitState(lFreezeFrameFilterData.EventId))
            { /* concurrent access to memory entry during copy process */
              lModificationDetected = TRUE;
            }
          }
          else
          {
            lReturnValue = DEM_BUFFER_TOO_SMALL;
          }
        }
        else
        { /* concurrent access detected */
          lModificationDetected = TRUE;
        }

        if (lModificationDetected == TRUE)
        { /* retry next call of this interface */
          lFreezeFrameFilterData.FilterState = DEM_FREEZEFRAMEITERATOR_J1939STATE_PENDING;
          lReturnValue = DEM_PENDING;
        }
        else if (lReturnValue != DEM_BUFFER_TOO_SMALL)
        { /* copy finished */
          lFreezeFrameFilterData.EventId = lFreezeFrameFilterData.EventId + 1u;
          lFreezeFrameFilterData.FilterState = DEM_FREEZEFRAMEITERATOR_J1939STATE_USED;
          lReturnValue = E_OK;
        }
        else
        {
          /* Return DEM_BUFFER_TOO_SMALL */
        }
      }
    }

    Dem_FreezeFrameIterator_SetFreezeFrameFilterData(FreezeFrameIteratorId, lFreezeFrameFilterData);
  }
  /* else processing finished lReturnValue = DEM_NO_SUCH_ELEMENT initially set */

  return lReturnValue;
}                                                                                                                                /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
#endif

#if (DEM_CFG_SUPPORT_SRECS == STD_ON) && (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 % Dem_FreezeFrameIterator_TimeSeriesSRecIsStored
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
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_FreezeFrameIterator_TimeSeriesSRecIsStored(                                                                                                  /* PRQA S 3219 */ /* MD_DEM_14.1_CONFIGURATION_SWITCH */
  CONST(Dem_Mem_ConstTimeSeriesEntryPtrType, AUTOMATIC)  TimeSeriesEntry,
  uint8  RecordNumber
  )
{
  uint8 lSRecStoredIndex;
  boolean lIsStored;

  if (RecordNumber >= 0x30u) 
  {
    /* Normal Sample */
    lSRecStoredIndex = RecordNumber - 0x30u;
    if (lSRecStoredIndex >= Dem_Cfg_TimeSeriesPastSamplesNormal())
    {
      /* Future Sample */
      lSRecStoredIndex -= Dem_Cfg_TimeSeriesPastSamplesNormal();
      lIsStored = (lSRecStoredIndex < (Dem_Cfg_TimeSeriesFutureSamplesNormal() 
      - Dem_Memory_TimeSeries_EntryManager_GetUnusedFutureSamplesNormal(TimeSeriesEntry)));                                      /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    }
    else
    {
      /* Past Sample */
      lIsStored = (lSRecStoredIndex >= Dem_Memory_TimeSeries_EntryManager_GetUnusedPastSamplesNormal(TimeSeriesEntry));          /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    }
  }
  else
  {
    /* Fast Sample */
    lSRecStoredIndex = RecordNumber - 0x10u;
    if (lSRecStoredIndex >= Dem_Cfg_TimeSeriesPastSamplesFast())
    {
      /* Future Sample */
      lSRecStoredIndex -= Dem_Cfg_TimeSeriesPastSamplesFast();
      lIsStored = (lSRecStoredIndex < (Dem_Cfg_TimeSeriesFutureSamplesFast() 
      - Dem_Memory_TimeSeries_EntryManager_GetUnusedFutureSamplesFast(TimeSeriesEntry)));                                        /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    }
    else
    { 
      /* Past Sample */
      lIsStored = (lSRecStoredIndex >= Dem_Memory_TimeSeries_EntryManager_GetUnusedPastSamplesFast(TimeSeriesEntry));            /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    }
  }

  return lIsStored;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

/*!
 * \}
 */
# define DEM_STOP_SEC_CODE
# include "MemMap.h"                                                                                                             /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_FREEZEFRAMEITERATOR_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_FreezeFrameIterator_Implementation.h
 *********************************************************************************************************************/
