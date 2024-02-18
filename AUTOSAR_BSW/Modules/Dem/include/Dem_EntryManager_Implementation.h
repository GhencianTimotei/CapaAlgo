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
/*! \addtogroup Dem_EntryManager
 *  \{
 *  \file       Dem_EntryManager_Implementation.h
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

#if !defined (DEM_ENTRYMANAGER_IMPLEMENTATION_H)
#define DEM_ENTRYMANAGER_IMPLEMENTATION_H

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
#include "Dem_EntryManager_Interface.h"

/* Includes to access public functions belonging to other (top level)/ (logical)/- units to be used by this Unit */
/* ------------------------------------------------------------------------- */
#include "Dem_Infrastructure_Interface.h"
#include "Dem_Client_Interface.h"
#include "Dem_DataStorage_Interface.h"
#include "Dem_MemoryIF_Interface.h"
#include "Dem_RingBuffer_Interface.h"
#include "Dem_Sampler_Interface.h"
#include "Dem_TimeSeriesIF_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

  /*! Filename declaration */
#define DEM_ENTRYMANAGER_IMPLEMENTATION_FILENAME "Dem_EntryManager_Implementation.h"

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
 *  SUBCOMPONENT PRIVATE PROPERTIES DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_EntryManager_PrivateProperties Private Properties
 * \{
 */
 #if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 * Dem_Memory_TimeSeries_EntryManager_SetUnusedFutureSamplesNormal
 *****************************************************************************/
/*!
 * \brief         Sets number of unused future (normal) samples in time series entry
 *
 * \details       Sets number of unused future (normal) samples in time series entry if available
 *
 * \param[in]     TimeSeriesEntry
 *                Pointer to the time series entry
 * \param[in]     UnusedFutureSamples
 *                Number of unused future (normal) samples
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_TIME_SERIES == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_SetUnusedFutureSamplesNormal(
  Dem_Mem_TimeSeriesEntryConstPtrType Entry,
  uint8 UnusedFutureSamples
);
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 * Dem_Memory_TimeSeries_EntryManager_SetUnusedFutureSamplesFast
 *****************************************************************************/
/*!
 * \brief         Sets number of unused future (fast) samples in time series entry
 *
 * \details       Sets number of unused future (fast) samples in time series entry if available
 *
 * \param[in]     Entry
 *                Pointer to the time series entry
 * \param[in]     UnusedFutureSamples
 *                Number of unused samples future (fast) samples
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_TIME_SERIES == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_SetUnusedFutureSamplesFast(
  Dem_Mem_TimeSeriesEntryConstPtrType Entry,
  uint8 UnusedFutureSamples
);
#endif

#if (DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_NORMAL == STD_ON)
/* ****************************************************************************
 * Dem_Memory_TimeSeries_EntryManager_GetMissingFutureNormalSample
 *****************************************************************************/
/*!
 * \brief         Get the missing future (normal) samples of the indexed time series
 *                snapshot record.
 *
 * \details       Get the missing future (normal) samples of the indexed time series
 *                snapshot record.
 *
 * \param[in]     Index
 *                Index of the time series snapshot record
 *
 * \return        Number of missing future (normal) samples
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_NORMAL == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_GetMissingFutureNormalSample(
  Dem_Mem_ConstTimeSeriesEntryCompanionConstPtrType EntryCompanion
  );
#endif

#if (DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_FAST == STD_ON)
/* ****************************************************************************
 * Dem_Memory_TimeSeries_EntryManager_GetMissingFuturesFastSamples
 *****************************************************************************/
/*!
 * \brief         Get the missing future (fast) samples of the indexed time series
 *                snapshot record.
 *
 * \details       Get the missing future (fast) samples of the indexed time series
 *                snapshot record.
 *
 * \param[in]     Index
 *                Index of the time series snapshot record
 *
 * \return        Number of missing future (fast) samples
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_FAST == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_GetMissingFuturesFastSamples(
  Dem_Mem_ConstTimeSeriesEntryCompanionConstPtrType EntryCompanion
  );
#endif

/* ****************************************************************************
 * Dem_Memory_TimeSeries_EntryManager_SetTimeSinceLastSample
 *****************************************************************************/
/*!
 * \brief         Sets time since the last sample in time series entry
 *                was collected
 *
 * \details       Sets time since the last sample in time series entry 
 *                was collected. Only sets the value, if time series powertrain 
 *                is enabled
 *
 * \param[in]     Entry
 *                Pointer to the time series entry
 * \param[in]     TimeSinceLastSample
 *                Time since the last sample was collected
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different entries.
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_SetTimeSinceLastSample(
  Dem_Mem_TimeSeriesEntryConstPtrType Entry,
  uint16 TimeSinceLastSample
  );

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 * Dem_Memory_TimeSeries_EntryManager_SetUnusedPastSamples
 *****************************************************************************/
/*!
 * \brief         Sets number of unused past samples in time series entry
 *
 * \details       Sets number of unused past samples in time series entry if available
 *
 * \param[in]     Entry
 *                Pointer to the time series entry
 * \param[in]     UnusedPastSamples
 *                Number of unused past samples
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_TIME_SERIES == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_SetUnusedPastSamples(
  Dem_Mem_TimeSeriesEntryConstPtrType Entry,
  uint8 UnusedPastSamples
);
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 * Dem_Memory_TimeSeries_EntryManager_SetUnusedPastSamplesNormal
 *****************************************************************************/
/*!
 * \brief         Sets the number of unused past (normal) samples in time series entry
 *
 * \details       Sets the number of unused past (normal) samples in time series entry
 *                if available
 *
 * \param[in]     Entry
 *                Pointer to the time series entry
 * \param[in]     UnusedPastSamples
 *                Number of unused past (normal) samples
 * \pre           -
 * \config        DEM_FEATURE_NEED_TIME_SERIES == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_SetUnusedPastSamplesNormal(
  Dem_Mem_TimeSeriesEntryPtrType Entry,
  uint8 UnusedPastSamples
  );
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 * Dem_Memory_TimeSeries_EntryManager_SetUnusedPastSamplesFast
 *****************************************************************************/
/*!
 * \brief         Sets number of past (fast) samples in time series entry
 *
 * \details       Sets number of past (fast) samples in time series entry if available
 *
 * \param[in]     Entry
 *                Pointer to the time series entry
 * \param[in]     UnusedPastSamples
 *                Number of unused past (fast) samples
 * \pre           -
 * \config        DEM_FEATURE_NEED_TIME_SERIES == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_SetUnusedPastSamplesFast(
  Dem_Mem_TimeSeriesEntryConstPtrType Entry,
  uint8 UnusedPastSamples
  );
#endif


#if ((DEM_FEATURE_NEED_TIME_SERIES == STD_ON) && (DEM_CFG_SUPPORT_DCM == STD_ON))
/* ****************************************************************************
 * Dem_Memory_TimeSeries_EntryManager_IncrementClientCounter
 *****************************************************************************/
 /*!
 * \brief         Increment the client counter of the time series entry
 *
 * \details       Increment the client counter of the time series entry
 *
 * \param[in]     EntryCompanion
 *                Pointer to Time Series Entry Companion
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_TIME_SERIES == STD_ON
 *                && DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_IncrementClientCounter(
  Dem_Mem_TimeSeriesEntryCompanionConstPtrType  EntryCompanion
);
#endif

#if ((DEM_FEATURE_NEED_TIME_SERIES == STD_ON) && (DEM_CFG_SUPPORT_DCM == STD_ON))
/* ****************************************************************************
 * Dem_Memory_TimeSeries_EntryManager_DecrementClientCounter
 *****************************************************************************/
 /*!
 * \brief         Decrement the client counter of the time series entry
 *
 * \details       Decrement the client counter of the time series entry
 *
 * \param[in]     EntryCompanion
 *                Pointer to Time Series Entry Companion
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_TIME_SERIES == STD_ON
 *                && DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_DecrementClientCounter(
  Dem_Mem_TimeSeriesEntryCompanionConstPtrType  EntryCompanion
);
#endif

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE PROPERTIES DEFINITIONS
 *********************************************************************************************************************/

 #if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
 /* ****************************************************************************
 % Dem_Memory_TimeSeries_EntryManager_SetUnusedFutureSamplesNormal
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_SetUnusedFutureSamplesNormal(
  Dem_Mem_TimeSeriesEntryConstPtrType Entry,                                                                                     /* PRQA S 3673 */ /* MD_DEM_8.13_fp */
  uint8 UnusedFutureSamples
)
{
# if (DEM_CFG_SUPPORT_TIME_SERIES_POWERTRAIN == STD_OFF)
  Entry->UnusedFutureSamples_NormalRate = UnusedFutureSamples;                                                                   /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
# endif
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(Entry)                                                                                        /* PRQA S 1338, 3112 */ /* MD_MSR_DummyStmt, MD_DEM_14.2 */ 
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(UnusedFutureSamples)                                                                          /* PRQA S 1338, 3112 */ /* MD_MSR_DummyStmt, MD_DEM_14.2 */ 
}
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 % Dem_Memory_TimeSeries_EntryManager_SetUnusedFutureSamplesFast
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_SetUnusedFutureSamplesFast(
  Dem_Mem_TimeSeriesEntryConstPtrType Entry,                                                                                     /* PRQA S 3673 */ /* MD_DEM_8.13_fp */
  uint8 UnusedFutureSamples
)
{
# if (DEM_CFG_SUPPORT_TIME_SERIES_POWERTRAIN == STD_OFF)
#  if (DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_FAST == STD_ON)
  Entry->UnusedFutureSamples_FastRate = UnusedFutureSamples;                                                                     /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
#  endif
# endif
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(Entry)                                                                                        /* PRQA S 1338, 3112 */ /* MD_MSR_DummyStmt, MD_DEM_14.2 */ 
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(UnusedFutureSamples)                                                                          /* PRQA S 1338, 3112 */ /* MD_MSR_DummyStmt, MD_DEM_14.2 */ 
}
#endif

#if (DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_NORMAL == STD_ON)
/* ****************************************************************************
 % Dem_Memory_TimeSeries_EntryManager_GetMissingFutureNormalSample
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_GetMissingFutureNormalSample(
  Dem_Mem_ConstTimeSeriesEntryCompanionConstPtrType EntryCompanion
  )
{
  return EntryCompanion->MissingFutureNormalSample;                                                                             /* PRQA S 2842, 2843 */ /* MD_DEM_Dir4.1_ReadOperation, MD_DEM_Dir4.1_ReadOperation */ /* SBSW_DEM_POINTER_WRITE_TIMESERIESENTRYCOMPANION */
}
#endif


#if (DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_FAST == STD_ON)
/* ****************************************************************************
 % Dem_Memory_TimeSeries_EntryManager_GetMissingFuturesFastSamples
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_GetMissingFuturesFastSamples(
  Dem_Mem_ConstTimeSeriesEntryCompanionConstPtrType EntryCompanion
  )
{
  return EntryCompanion->MissingFutureFastSample;                                                                               /* PRQA S 2842, 2843 */ /* MD_DEM_Dir4.1_ReadOperation, MD_DEM_Dir4.1_ReadOperation */ /* SBSW_DEM_POINTER_WRITE_TIMESERIESENTRYCOMPANION */
}
#endif

/* ****************************************************************************
 % Dem_Memory_TimeSeries_EntryManager_SetTimeSinceLastSample
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_SetTimeSinceLastSample(                                                                       /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  Dem_Mem_TimeSeriesEntryConstPtrType Entry,                                                                                     /* PRQA S 3673 */ /* MD_DEM_8.13_fp */
  uint16 TimeSinceLastSample
)
{
#if (DEM_CFG_SUPPORT_TIME_SERIES_POWERTRAIN == STD_ON)
  Entry->Td = TimeSinceLastSample;                                                                                               /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(Entry)                                                                                        /* PRQA S 1338, 3112 */ /* MD_MSR_DummyStmt, MD_DEM_14.2 */ 
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(TimeSinceLastSample)                                                                          /* PRQA S 1338, 3112 */ /* MD_MSR_DummyStmt, MD_DEM_14.2 */ 
#endif
}

#if(DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
 /* ****************************************************************************
 % Dem_Memory_TimeSeries_EntryManager_SetUnusedPastSamples
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_SetUnusedPastSamples(
  Dem_Mem_TimeSeriesEntryConstPtrType Entry,                                                                                     /* PRQA S 3673 */ /* MD_DEM_8.13_fp */
  uint8 UnusedPastSamples
)
{
# if (DEM_CFG_SUPPORT_TIME_SERIES_POWERTRAIN == STD_ON)
  Entry->UnusedPastSamples = UnusedPastSamples;                                                                                  /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(Entry)                                                                                        /* PRQA S 1338, 3112 */ /* MD_MSR_DummyStmt, MD_DEM_14.2 */ 
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(UnusedPastSamples)                                                                            /* PRQA S 1338, 3112 */ /* MD_MSR_DummyStmt, MD_DEM_14.2 */ 
# endif
}
#endif

#if(DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 % Dem_Memory_TimeSeries_EntryManager_SetUnusedPastSamplesNormal
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_SetUnusedPastSamplesNormal(
  Dem_Mem_TimeSeriesEntryPtrType Entry,
  uint8 UnusedPastSamples
)
{
# if (DEM_CFG_SUPPORT_TIME_SERIES_POWERTRAIN == STD_ON)
  Entry->UnusedPastSamples = UnusedPastSamples;                                                                                  /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
# else
  Entry->UnusedPastSamples_NormalRate = UnusedPastSamples;                                                                       /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
# endif
}
#endif

#if(DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 % Dem_Memory_TimeSeries_EntryManager_SetUnusedPastSamplesFast
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_SetUnusedPastSamplesFast(
  Dem_Mem_TimeSeriesEntryConstPtrType Entry,                                                                                     /* PRQA S 3673 */ /* MD_DEM_8.13_fp */
  uint8 UnusedPastSamples
)
{
# if (DEM_CFG_SUPPORT_TIME_SERIES_POWERTRAIN == STD_ON)
  Entry->UnusedPastSamples = UnusedPastSamples;                                                                                  /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
# else
#  if (DEM_CFG_SUPPORT_TIME_SERIES_PAST_FAST == STD_ON)
  Entry->UnusedPastSamples_FastRate = UnusedPastSamples;                                                                         /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
#  endif
# endif
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(Entry)                                                                                        /* PRQA S 1338, 3112 */ /* MD_MSR_DummyStmt, MD_DEM_14.2 */ 
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(UnusedPastSamples)                                                                            /* PRQA S 1338, 3112 */ /* MD_MSR_DummyStmt, MD_DEM_14.2 */ 
}
#endif

#if ((DEM_FEATURE_NEED_TIME_SERIES == STD_ON) && (DEM_CFG_SUPPORT_DCM == STD_ON))
/* ****************************************************************************
 % Dem_Memory_TimeSeries_EntryManager_IncrementClientCounter
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_IncrementClientCounter(
  Dem_Mem_TimeSeriesEntryCompanionConstPtrType EntryCompanion
)
{
  ++(EntryCompanion->ClientCounter);                                                                                             /* SBSW_DEM_POINTER_WRITE_TIMESERIESENTRYCOMPANION */
}
#endif

#if ((DEM_FEATURE_NEED_TIME_SERIES == STD_ON) && (DEM_CFG_SUPPORT_DCM == STD_ON))
/* ****************************************************************************
 % Dem_Memory_TimeSeries_EntryManager_DecrementClientCounter
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_DecrementClientCounter(
  Dem_Mem_TimeSeriesEntryCompanionConstPtrType EntryCompanion
)
{
  Dem_Internal_AssertReturnVoid(EntryCompanion->ClientCounter > 0x00U, DEM_E_INCONSISTENT_STATE)
  --(EntryCompanion->ClientCounter);                                                                                             /* SBSW_DEM_POINTER_WRITE_TIMESERIESENTRYCOMPANION */
}
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ********************************************************************************************************************
 *  SUBCOMPONENT PUBLIC PROPERTIES DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \addtogroup Dem_EntryManager_PublicProperties
 * \{
 */

/* ****************************************************************************
 % Dem_Memory_TimeSeries_EntryManager_EventDidIterExists
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_EventDidIterExists(                                                                           /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
CONSTP2CONST(Dem_Cfg_EventDidIterType, AUTOMATIC, AUTOMATIC)  IterPtr
)
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
    return (boolean)(IterPtr->mIdx < IterPtr->mEndIdx);
#else
    return FALSE;
#endif
}

/* ****************************************************************************
 % Dem_Memory_TimeSeries_EntryManager_EventDidIterGet
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_DidIndexType, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_EventDidIterGet(                                                                              /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
CONSTP2CONST(Dem_Cfg_EventDidIterType, AUTOMATIC, AUTOMATIC)  IterPtr                                                            /* PRQA S 3206 */ /* MD_DEM_3206 */
)
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
    return Dem_Cfg_GetDataCollectionTableFfm2CollInd(IterPtr->mIdx);
#else
    return (Dem_Cfg_DidIndexType)0x00;
#endif
}


/* ****************************************************************************
 % Dem_Memory_TimeSeries_EntryManager_EventDidIterInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_EventDidIterInit(                                                                             /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
CONST(Dem_EventIdType, AUTOMATIC)  EventId,                                                                                      /* PRQA S 3206 */ /* MD_DEM_3206 */
CONSTP2VAR(Dem_Cfg_EventDidIterType, AUTOMATIC, AUTOMATIC)  IterPtr                                                              /* PRQA S 3673 */ /* MD_DEM_8.13_fp */
)
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
# if(DEM_CFG_SUPPORT_TIME_SERIES_POWERTRAIN == STD_ON)
  IterPtr->mIdx = Dem_Cfg_GetDataCollectionTableFfm2CollIndStartIdxOfFreezeFrameTable(Dem_Cfg_GetFreezeFrameTableDevFFBIdxOfEventTable(EventId));   /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  IterPtr->mEndIdx = Dem_Cfg_GetDataCollectionTableFfm2CollIndEndIdxOfFreezeFrameTable(Dem_Cfg_GetFreezeFrameTableDevFFBIdxOfEventTable(EventId));  /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
# else
  IterPtr->mIdx = Dem_Cfg_GetDataCollectionTableFfm2CollIndStartIdxOfFreezeFrameTable(Dem_Cfg_GetFreezeFrameTableStdFFIdxOfEventTable(EventId));   /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  IterPtr->mEndIdx = Dem_Cfg_GetDataCollectionTableFfm2CollIndEndIdxOfFreezeFrameTable(Dem_Cfg_GetFreezeFrameTableStdFFIdxOfEventTable(EventId));  /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
# endif
#else
  IterPtr->mIdx = 0x00u;                                                                                                        /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  IterPtr->mEndIdx = 0x00u;                                                                                                     /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
#endif
}


/* ****************************************************************************
 % Dem_Memory_TimeSeries_EntryManager_EventDidIterNext
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_EventDidIterNext(                                                                             /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
CONSTP2VAR(Dem_Cfg_EventDidIterType, AUTOMATIC, AUTOMATIC)  IterPtr                                                              /* PRQA S 3673 */ /* MD_DEM_8.13_fp */
)
{
#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
  IterPtr->mIdx += 1u;                                                                                                           /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
#else
  IterPtr->mIdx = 0x00u;                                                                                                         /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
#endif
}


/* ****************************************************************************
 % Dem_Memory_TimeSeries_EntryManager_GetTimeSinceLastSample
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_GetTimeSinceLastSample(                                                                       /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  Dem_Mem_ConstTimeSeriesEntryPtrType Entry
  )
{
# if (DEM_CFG_SUPPORT_TIME_SERIES_POWERTRAIN == STD_ON)
  return Entry->Td;
# else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(Entry)                                                                                        /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return (uint16) 0x00U;
# endif
}

 /* ****************************************************************************
 % Dem_Memory_TimeSeries_EntryManager_GetUnusedPastSamplesNormal
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_GetUnusedPastSamplesNormal(                                                                   /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  Dem_Mem_ConstTimeSeriesEntryPtrType Entry
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(Entry)                                                                                        /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_SUPPORT_TIME_SERIES_PAST_NORMAL == STD_ON)
# if (DEM_CFG_SUPPORT_TIME_SERIES_POWERTRAIN == STD_ON)
  return Entry->UnusedPastSamples;
# else
  return Entry->UnusedPastSamples_NormalRate;
# endif
#else
  return (uint8)0x00U;
#endif
}

/* ****************************************************************************
 % Dem_Memory_TimeSeries_EntryManager_GetUnusedPastSamplesFast
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_GetUnusedPastSamplesFast(                                                                     /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  Dem_Mem_ConstTimeSeriesEntryPtrType Entry
)
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(Entry)                                                                                        /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_SUPPORT_TIME_SERIES_PAST_FAST == STD_ON)
# if (DEM_CFG_SUPPORT_TIME_SERIES_POWERTRAIN == STD_ON)
  return Entry->UnusedPastSamples;
# else
  return Entry->UnusedPastSamples_FastRate;
# endif
#else
  return (uint8)0x00U;
#endif
}

/* ****************************************************************************
 % Dem_Memory_TimeSeries_EntryManager_GetUnusedFutureSamplesNormal
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_GetUnusedFutureSamplesNormal(                                                                 /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  Dem_Mem_ConstTimeSeriesEntryPtrType Entry
)
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(Entry)                                                                                        /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_NORMAL == STD_ON)
  return Entry->UnusedFutureSamples_NormalRate;
#else
  return 0;
#endif
}


/* ****************************************************************************
 % Dem_Memory_TimeSeries_EntryManager_GetUnusedFutureSamplesFast
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_GetUnusedFutureSamplesFast(                                                                   /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  Dem_Mem_ConstTimeSeriesEntryPtrType Entry
)
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(Entry)                                                                                        /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if(DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_FAST == STD_ON)
  return Entry->UnusedFutureSamples_FastRate;
#else
  return 0;
#endif
}

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 % Dem_Memory_TimeSeries_EntryManager_GetClientCounter
 *****************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_GetClientCounter(
  Dem_Mem_ConstTimeSeriesEntryCompanionConstPtrType EntryCompanion
)
{
  return (EntryCompanion->ClientCounter);
}
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 % Dem_Memory_TimeSeries_EntryManager_GetReadoutState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Memory_TimeSeries_EntryManager_ReadoutStatusType, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_GetReadoutState(
  Dem_Mem_ConstTimeSeriesEntryCompanionConstPtrType  EntryCompanion
)
{
  return (EntryCompanion->ReadoutStatus);
}
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 % Dem_Memory_TimeSeries_EntryManager_SetReadoutState
 *****************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_SetReadoutState(
  Dem_Mem_TimeSeriesEntryCompanionConstPtrType EntryCompanion,
  Dem_Memory_TimeSeries_EntryManager_ReadoutStatusType State
)
{
  EntryCompanion->ReadoutStatus = State;                                                                                         /* SBSW_DEM_POINTER_WRITE_TIMESERIESENTRYCOMPANION */
}
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 % Dem_Memory_TimeSeries_EntryManager_InitClientCounter
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_InitClientCounter(
  Dem_Mem_TimeSeriesEntryCompanionConstPtrType EntryCompanion
)
{
  EntryCompanion->ClientCounter = 0;                                                                                             /* SBSW_DEM_POINTER_WRITE_TIMESERIESENTRYCOMPANION */
}
#endif

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
 * \defgroup Dem_EntryManager_Private Private Methods
 * \{
 */


#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON) && (DEM_CFG_SUPPORT_TIME_SERIES_POWERTRAIN ==STD_ON)
/* ****************************************************************************
 * Dem_Memory_TimeSeries_EntryManager_GetDataPtr
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
 * \return        Pointer to the indexed rate data buffer
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_TIME_SERIES == STD_ON
 *                DEM_CFG_SUPPORT_TIME_SERIES_POWERTRAIN ==STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SharedDataPtrType, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_GetDataPtr(
  CONST(Dem_Mem_TimeSeriesEntryPtrType, AUTOMATIC)  MemoryEntry,
  CONST(uint8, AUTOMATIC)  SeriesIndex
);
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 * Dem_Memory_TimeSeries_EntryManager_GetNormalDataPtr
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
 * \config        DEM_FEATURE_NEED_TIME_SERIES == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SharedDataPtrType, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_GetNormalDataPtr(
  CONST(Dem_Mem_TimeSeriesEntryPtrType, AUTOMATIC)  MemoryEntry,
  CONST(uint8, AUTOMATIC)  SeriesIndex
  );
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON)
/* ****************************************************************************
 * Dem_Memory_TimeSeries_EntryManager_GetFastDataPtr
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
 * \config        DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SharedDataPtrType, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_GetFastDataPtr(
  CONST(Dem_Mem_TimeSeriesEntryPtrType, AUTOMATIC)  MemoryEntry,
  CONST(uint8, AUTOMATIC)  SeriesIndex
  );
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 * Dem_Memory_TimeSeries_EntryManager_CopyNormalDidsFromRingBuffer
 *****************************************************************************/
/*!
 * \brief         Copy time series samples from the normal rate sample ringbuffer
 *
 * \details       Copy time series samples from the normal rate sample ringbuffer
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     SourceIndex
 *                RingBuffer Index to copy. 0: Oldest Sample
 * \param[out]    DestinationBuffer
 *                Pointer to the buffer to store the data
 * \param[in]     BufferSize
 *                Size of the destination buffer
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_TIME_SERIES == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_CopyNormalDidsFromRingBuffer(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  SourceIndex,
  CONST(Dem_SharedDataPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint16, AUTOMATIC)  BufferSize
  );
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON)
/* ****************************************************************************
 * Dem_Memory_TimeSeries_EntryManager_CopyFastDidsFromRingBuffer
 *****************************************************************************/
/*!
 * \brief         Copy time series samples from the fast rate sample ringbuffer
 *
 * \details       Copy time series samples from the fast rate sample ringbuffer
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     SourceIndex
 *                RingBuffer Index to copy. 0: Oldest Sample
 * \param[out]    DestinationBuffer
 *                Pointer to the buffer to store the data
 * \param[in]     BufferSize
 *                Size of the destination buffer
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_CopyFastDidsFromRingBuffer(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  SourceIndex,
  CONST(Dem_SharedDataPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint16, AUTOMATIC)  BufferSize
  );
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
 /* ****************************************************************************
 * Dem_Memory_TimeSeries_EntryManager_GetRecMaxRawSize
 *****************************************************************************/
 /*!
 * \brief         Get the maximum raw size of a time series record
 *
 * \details       Get the maximum raw size of a time series record.
 *                This only counts the data that needs to be stored in NVRam.
 *
 * \return        The maximum raw size of an time series record
 *                1 if no no freeze frame record class configured.
 *
 * \pre           -
 *
 * \config        DEM_FEATURE_NEED_TIME_SERIES == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_GetRecMaxRawSize(
  void
);
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES_FUTURE == STD_ON)
/* ****************************************************************************
 * Dem_Memory_TimeSeries_EntryManager_TriggerNvMStorageOnFutureSampleUpdate
 *****************************************************************************/
/*!
 * \brief         Mark the time series entry changed for NvM persistence.
 *
 * \details       Mark the time series entry changed for NvM persistence.
 *                Depending on configuration either 'dirty' or 'dirty immediate'
 *
 * \param[in]     MemoryIndex
 *                Handle of the memory block
 * \param[in]     EntryCompanion
 *                Pointer to Time Series Entry Companion
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 *
 * \config        DEM_FEATURE_NEED_TIME_SERIES_FUTURE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_TriggerNvMStorageOnFutureSampleUpdate(
  Dem_Cfg_MemoryIndexType  MemoryIndex,
  Dem_Mem_ConstTimeSeriesEntryCompanionConstPtrType  EntryCompanion,
  Dem_EventIdType  EventId
  );
#endif

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON) && (DEM_CFG_SUPPORT_TIME_SERIES_POWERTRAIN ==STD_ON)
/* ****************************************************************************
 % Dem_Memory_TimeSeries_EntryManager_GetDataPtr
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_SharedDataPtrType, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_GetDataPtr(
  CONST(Dem_Mem_TimeSeriesEntryPtrType, AUTOMATIC)  MemoryEntry,
  CONST(uint8, AUTOMATIC)  SeriesIndex
)
{
  Dem_SharedDataPtrType lReturnValue;
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (SeriesIndex >= DEM_MEMORY_TIMESERIES_ENTRYMANAGER_MAXSAMPLES)
  {
    Dem_Error_RunTimeCheckFailed(DEM_MEM_IMPLEMENTATION_FILENAME, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
    lReturnValue = &MemoryEntry->SnapshotData[0][0];
  }
  else
# endif
  {
    lReturnValue = &MemoryEntry->SnapshotData[SeriesIndex][0];
  }
  return lReturnValue;
}
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 % Dem_Memory_TimeSeries_EntryManager_GetNormalDataPtr
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_SharedDataPtrType, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_GetNormalDataPtr(
  CONST(Dem_Mem_TimeSeriesEntryPtrType, AUTOMATIC)  MemoryEntry,                                                                 /* PRQA S 3673 */ /* MD_DEM_8.13_fp */
  CONST(uint8, AUTOMATIC)  SeriesIndex
  )
{
#if (DEM_CFG_SUPPORT_TIME_SERIES_POWERTRAIN == STD_OFF)
  Dem_SharedDataPtrType lReturnValue;
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (SeriesIndex >= (Dem_Cfg_TimeSeriesPastSamplesNormal() + Dem_Cfg_TimeSeriesFutureSamplesNormal()))
  {
    Dem_Error_RunTimeCheckFailed(DEM_MEM_IMPLEMENTATION_FILENAME, __LINE__);                                                     /* SBSW_DEM_POINTER_RUNTIME_CHECK */
    lReturnValue = &MemoryEntry->SnapshotData_NormalRate[0][0];
  }
  else
# endif
  {
    lReturnValue = &MemoryEntry->SnapshotData_NormalRate[SeriesIndex][0];
  }
  return lReturnValue;
#else
  return Dem_Memory_TimeSeries_EntryManager_GetDataPtr(MemoryEntry, SeriesIndex);                                                /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
#endif
}
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON)
/* ****************************************************************************
 % Dem_Memory_TimeSeries_EntryManager_GetFastDataPtr
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_SharedDataPtrType, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_GetFastDataPtr(
  CONST(Dem_Mem_TimeSeriesEntryPtrType, AUTOMATIC)  MemoryEntry,                                                                 /* PRQA S 3673 */ /* MD_DEM_8.13_fp */
  CONST(uint8, AUTOMATIC)  SeriesIndex
  )
{
#if (DEM_CFG_SUPPORT_TIME_SERIES_POWERTRAIN == STD_OFF)
  Dem_SharedDataPtrType lReturnValue;
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (SeriesIndex >= (Dem_Cfg_TimeSeriesPastSamplesFast() + Dem_Cfg_TimeSeriesFutureSamplesFast()))
  {
    Dem_Error_RunTimeCheckFailed(DEM_MEM_IMPLEMENTATION_FILENAME, __LINE__);                                                     /* SBSW_DEM_POINTER_RUNTIME_CHECK */
    lReturnValue = &MemoryEntry->SnapshotData_FastRate[0][0];
  }
  else
# endif
  {
    lReturnValue = &MemoryEntry->SnapshotData_FastRate[SeriesIndex][0];
  }
  return lReturnValue;
# else
  return Dem_Memory_TimeSeries_EntryManager_GetDataPtr(MemoryEntry, SeriesIndex);                                                /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
# endif
}
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 % Dem_Memory_TimeSeries_EntryManager_CopyNormalDidsFromRingBuffer
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_CopyNormalDidsFromRingBuffer(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  SourceIndex,
  CONST(Dem_SharedDataPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint16, AUTOMATIC)  BufferSize                                                                                           /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  Dem_Cfg_EventDidIterType lDidIter;
  Dem_ConstSharedDataPtrType lSourceBuffer;
  Dem_Data_DestinationBuffer lDestinationBuffer;

  /* Initialize destination buffer context */
  Dem_Data_InitDestinationBuffer(&lDestinationBuffer, DestinationBuffer, BufferSize);                                            /* SBSW_DEM_CALL_DESTINATIONBUFFER_INIT */

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(BufferSize)                                                                                   /* PRQA S 3112 */ /* MD_DEM_14.2 */

# if (DEM_CFG_SUPPORT_TIME_SERIES_PAST_NORMAL == STD_ON)
  if (Dem_Memory_TimeSeries_RingBuffer_GetNormalSampleCount() < Dem_Cfg_TimeSeriesPastSamplesNormal())
  {
    lSourceBuffer = Dem_Memory_TimeSeries_RingBuffer_GetNormalSlot(SourceIndex);
  }
  else
  {
    lSourceBuffer = Dem_Memory_TimeSeries_RingBuffer_GetNormalSlot(
      (Dem_Memory_TimeSeries_RingBuffer_GetCurrentIndexNormal() + SourceIndex) % Dem_Cfg_TimeSeriesPastSamplesNormal()
      );
  }
# else
  lSourceBuffer = Dem_Memory_TimeSeries_RingBuffer_GetNormalSlot(SourceIndex);
# endif
  for (Dem_Memory_TimeSeries_EntryManager_EventDidIterInit(EventId, &lDidIter);                                                  /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Memory_TimeSeries_EntryManager_EventDidIterExists(&lDidIter) == TRUE;                                                 /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Memory_TimeSeries_EntryManager_EventDidIterNext(&lDidIter))                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_DidIndexType lDidIndex;
    uint8 lDidSize;
    uint16 lWriteIndex;

    lDidIndex = Dem_Memory_TimeSeries_EntryManager_EventDidIterGet(&lDidIter);                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
    lDidSize = Dem_DataStorage_GetDidNVSize(lDidIndex);
    lWriteIndex = lDestinationBuffer.WriteIndex;

    if (Dem_Data_IncrementWriteIndexDestinationBuffer(&lDestinationBuffer, lDidSize) == E_OK)                                    /* SBSW_DEM_POINTER_FORWARD_STACK */
    {
      Dem_MemCpy(&lDestinationBuffer.Buffer[lWriteIndex],                                                                        /* PRQA S 0311, 0602 */ /* MD_DEM_11.8, MD_DEM_20.2 */ /* SBSW_DEM_WRITE_DESTINATIONBUFFER */
        &lSourceBuffer[Dem_Cfg_DidBufferIndexNormal(lDidIndex)],
        lDidSize);
    }
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON)
/* ****************************************************************************
 % Dem_Memory_TimeSeries_EntryManager_CopyFastDidsFromRingBuffer
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_CopyFastDidsFromRingBuffer(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  SourceIndex,
  CONST(Dem_SharedDataPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint16, AUTOMATIC)  BufferSize                                                                                           /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  Dem_Cfg_EventDidIterType lDidIter;
  Dem_ConstSharedDataPtrType lSourceBuffer;
  Dem_Data_DestinationBuffer lDestinationBuffer;

  /* Initialize destination buffer context */
  Dem_Data_InitDestinationBuffer(&lDestinationBuffer, DestinationBuffer, BufferSize);                                            /* SBSW_DEM_CALL_DESTINATIONBUFFER_INIT */

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(BufferSize)                                                                                   /* PRQA S 3112 */ /* MD_DEM_14.2 */

# if (DEM_CFG_SUPPORT_TIME_SERIES_PAST_FAST == STD_ON)
  if (Dem_Memory_TimeSeries_RingBuffer_GetFastSampleCount() < Dem_Cfg_TimeSeriesPastSamplesFast())
  {
    lSourceBuffer = Dem_Memory_TimeSeries_RingBuffer_GetFastSlot(SourceIndex);
  }
  else
  {
    lSourceBuffer = Dem_Memory_TimeSeries_RingBuffer_GetFastSlot(
      (Dem_Memory_TimeSeries_RingBuffer_GetCurrentIndexFast() + SourceIndex) % Dem_Cfg_TimeSeriesPastSamplesFast()
      );
  }
# else
  lSourceBuffer = Dem_Memory_TimeSeries_RingBuffer_GetFastSlot(SourceIndex);
# endif

  for (Dem_Memory_TimeSeries_EntryManager_EventDidIterInit(EventId, &lDidIter);                                                  /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Memory_TimeSeries_EntryManager_EventDidIterExists(&lDidIter) == TRUE;                                                 /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Memory_TimeSeries_EntryManager_EventDidIterNext(&lDidIter))                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_DidIndexType lDidIndex;
    uint8 lDidSize;
    uint16 lWriteIndex;

    lDidIndex = Dem_Memory_TimeSeries_EntryManager_EventDidIterGet(&lDidIter);                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
    lDidSize = Dem_DataStorage_GetDidNVSize(lDidIndex);
    lWriteIndex = lDestinationBuffer.WriteIndex;

    if (Dem_Data_IncrementWriteIndexDestinationBuffer(&lDestinationBuffer, lDidSize) == E_OK)                                    /* SBSW_DEM_POINTER_FORWARD_STACK */
    {
      Dem_MemCpy(&lDestinationBuffer.Buffer[lWriteIndex],                                                                        /* PRQA S 0311, 0602 */ /* MD_DEM_11.8, MD_DEM_20.2 */ /* SBSW_DEM_WRITE_DESTINATIONBUFFER */
        &lSourceBuffer[Dem_Cfg_DidBufferIndexFast(lDidIndex)],
        lDidSize);
    }
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES_FUTURE == STD_ON)
/* ****************************************************************************
 % Dem_Memory_TimeSeries_EntryManager_TriggerNvMStorageOnFutureSampleUpdate
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_TriggerNvMStorageOnFutureSampleUpdate(
  Dem_Cfg_MemoryIndexType  MemoryIndex,
  Dem_Mem_ConstTimeSeriesEntryCompanionConstPtrType  EntryCompanion,
  Dem_EventIdType  EventId
  )
{
  uint16 lMissingSamples;

  lMissingSamples = 0u;
# if (DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_NORMAL == STD_ON)
  lMissingSamples += Dem_Memory_TimeSeries_EntryManager_GetMissingFutureNormalSample(EntryCompanion);                            /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
# endif
# if (DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_FAST == STD_ON)
  lMissingSamples += Dem_Memory_TimeSeries_EntryManager_GetMissingFuturesFastSamples(EntryCompanion);                            /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
# endif

  if ( (lMissingSamples == 0u)
    && (Dem_Cfg_EventSupportImmediateNv(EventId) == TRUE) )
  {
    Dem_Nvm_SetTimeSeriesMemoryBlockState(MemoryIndex, DEM_NVM_BLOCKSTATE_DIRTYIMMEDIATE);
  }
  else
  {
    Dem_Nvm_SetTimeSeriesMemoryBlockState(MemoryIndex, DEM_NVM_BLOCKSTATE_DIRTY);
  }
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EntryCompanion);                                                                              /* PRQA S 3112 */ /* MD_DEM_14.2 */
}
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 % Dem_Memory_TimeSeries_EntryManager_GetRecMaxRawSize
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_GetRecMaxRawSize(
  void
)
{
  return DEM_CFG_MAX_SIZE_TIMESERIESSNAPSHOT;
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
 * \addtogroup Dem_EntryManager_Public
 * \{
 */

/* ****************************************************************************
 % Dem_Memory_TimeSeries_EntryManager_GetConstDataPtr
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_ConstSharedDataPtrType, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_GetConstDataPtr(                                                                              /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Mem_ConstTimeSeriesEntryPtrType, AUTOMATIC)  MemoryEntry,
  CONST(uint8, AUTOMATIC)  SeriesIndex
)
{
#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON) && (DEM_CFG_SUPPORT_TIME_SERIES_POWERTRAIN ==STD_ON)
  Dem_Internal_AssertReturnValue(SeriesIndex < DEM_MEMORY_TIMESERIES_ENTRYMANAGER_MAXSAMPLES\
                                 , DEM_E_INCONSISTENT_STATE \
                                 , &(MemoryEntry->SnapshotData[0][0]))

  return &MemoryEntry->SnapshotData[SeriesIndex][0];
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntry)                                                                                  /* PRQA S 1338, 3112 */ /* MD_MSR_DummyStmt, MD_DEM_14.2 */ 
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(SeriesIndex)                                                                                  /* PRQA S 1338, 3112 */ /* MD_MSR_DummyStmt, MD_DEM_14.2 */ 
  return (Dem_ConstSharedDataPtrType) NULL_PTR;
#endif
}

/* ****************************************************************************
 % Dem_Memory_TimeSeries_EntryManager_GetNormalConstDataPtr
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_ConstSharedDataPtrType, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_GetNormalConstDataPtr(                                                                        /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  Dem_Mem_ConstTimeSeriesEntryPtrType  MemoryEntry,
  uint8  SeriesIndex
  )
{
#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON) && (DEM_CFG_SUPPORT_TIME_SERIES_POWERTRAIN == STD_OFF)
  Dem_Internal_AssertReturnValue((SeriesIndex < (Dem_Cfg_TimeSeriesPastSamplesNormal() + Dem_Cfg_TimeSeriesFutureSamplesNormal()))\
                                 , DEM_E_INCONSISTENT_STATE \
                                 , &(MemoryEntry->SnapshotData_NormalRate[0][0]))
  return &MemoryEntry->SnapshotData_NormalRate[SeriesIndex][0];
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntry)                                                                                  /* PRQA S 1338, 3112 */ /* MD_MSR_DummyStmt, MD_DEM_14.2 */ 
  DEM_IGNORE_UNUSED_ARGUMENT(SeriesIndex)                                                                                        /* PRQA S 1338, 3112 */ /* MD_MSR_DummyStmt, MD_DEM_14.2 */ 
  return (Dem_ConstSharedDataPtrType) NULL_PTR;
#endif
}

/* ****************************************************************************
 % Dem_Memory_TimeSeries_EntryManager_GetFastConstDataPtr
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_ConstSharedDataPtrType, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_GetFastConstDataPtr(                                                                          /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  Dem_Mem_ConstTimeSeriesEntryPtrType  MemoryEntry,
  uint8 SeriesIndex
  )
{
#if (DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON) && (DEM_CFG_SUPPORT_TIME_SERIES_POWERTRAIN == STD_OFF)
  Dem_Internal_AssertReturnValue((SeriesIndex < (Dem_Cfg_TimeSeriesPastSamplesFast() + Dem_Cfg_TimeSeriesFutureSamplesFast()))\
                                  , DEM_E_INCONSISTENT_STATE \
                                  , &(MemoryEntry->SnapshotData_FastRate[0][0]))
  return &MemoryEntry->SnapshotData_FastRate[SeriesIndex][0];
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntry)                                                                                  /* PRQA S 1338, 3112 */ /* MD_MSR_DummyStmt, MD_DEM_14.2 */ 
  DEM_IGNORE_UNUSED_ARGUMENT(SeriesIndex)                                                                                        /* PRQA S 1338, 3112 */ /* MD_MSR_DummyStmt, MD_DEM_14.2 */ 
  return (Dem_ConstSharedDataPtrType)NULL_PTR;
#endif
}

#if (DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_NORMAL == STD_ON)
/* ****************************************************************************
 % Dem_Memory_TimeSeries_EntryManager_SetMissingNormalSamples
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_SetMissingNormalSamples(
  Dem_Mem_TimeSeriesEntryCompanionConstPtrType  EntryCompanion,
  uint8 Value
  )
{
  EntryCompanion->MissingFutureNormalSample = Value;                                                                             /* SBSW_DEM_POINTER_WRITE_TIMESERIESENTRYCOMPANION */
}
#endif

#if (DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_FAST == STD_ON)
/* ****************************************************************************
 % Dem_Memory_TimeSeries_EntryManager_SetMissingFastSamples
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_SetMissingFastSamples(
  Dem_Mem_TimeSeriesEntryCompanionConstPtrType  EntryCompanion,
  uint8  Value
  )
{
  EntryCompanion->MissingFutureFastSample = Value;                                                                               /* SBSW_DEM_POINTER_WRITE_TIMESERIESENTRYCOMPANION */
}
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 % Dem_Memory_TimeSeries_EntryManager_EntryInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_EntryInit(
  Dem_Mem_TimeSeriesEntryConstPtrType  TimeSeriesEntry
  )
{
  /* clear information about stored time series entries */
  Dem_Memory_TimeSeries_EntryManager_SetUnusedPastSamplesNormal(TimeSeriesEntry, Dem_Cfg_TimeSeriesPastSamplesNormal());         /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  Dem_Memory_TimeSeries_EntryManager_SetUnusedFutureSamplesNormal(TimeSeriesEntry, Dem_Cfg_TimeSeriesFutureSamplesNormal());     /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  Dem_Memory_TimeSeries_EntryManager_SetUnusedPastSamplesFast(TimeSeriesEntry, Dem_Cfg_TimeSeriesPastSamplesFast());             /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  Dem_Memory_TimeSeries_EntryManager_SetUnusedFutureSamplesFast(TimeSeriesEntry, Dem_Cfg_TimeSeriesFutureSamplesFast());         /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  Dem_Memory_TimeSeries_EntryManager_SetUnusedPastSamples(TimeSeriesEntry,
                     DEM_MEMORY_TIMESERIES_ENTRYMANAGER_UNUSEDSAMPLES_INITVALUE);                                                /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

/* ****************************************************************************
 % Dem_Memory_TimeSeries_EntryManager_InitCompanionEntries
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_InitCompanionEntries(
  void
  )
{
#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON) 
  uint8 lIndex;
  for (lIndex = 0; lIndex < Dem_Cfg_GetSizeOfTimeSeriesEntryCompanion(); lIndex++)
  {
    Dem_Memory_TimeSeries_EntryManager_EntryCompanionInit(Dem_Cfg_GetAddrTimeSeriesEntryCompanion(lIndex),                      /* SBSW_DEM_ARRAY_WRITE_TIMESERIESENTRYCOMPANION */
      DEM_MEMORY_TIMESERIES_ENTRYMANAGER_READOUTSTATUS_UNUSED);
  }
#endif
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON) 
/* ****************************************************************************
 % Dem_Memory_TimeSeries_EntryManager_EntryCompanionInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_EntryCompanionInit(
  Dem_Mem_TimeSeriesEntryCompanionConstPtrType TimeSeriesEntryCompanion,
  Dem_Memory_TimeSeries_EntryManager_ReadoutStatusType State
  )
{
  Dem_Memory_TimeSeries_EntryManager_SetReadoutState(TimeSeriesEntryCompanion,                                                   /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
                     State);                                                 
  Dem_Memory_TimeSeries_EntryManager_InitClientCounter(TimeSeriesEntryCompanion);                                                /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */

# if DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_FAST == STD_ON
    Dem_Memory_TimeSeries_EntryManager_SetMissingFastSamples(TimeSeriesEntryCompanion, 0u);                                      /* SBSW_DEM_POINTER_WRITE_TIMESERIESENTRYCOMPANION */
# endif
# if DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_NORMAL == STD_ON
      Dem_Memory_TimeSeries_EntryManager_SetMissingNormalSamples(TimeSeriesEntryCompanion, 0u);                                  /* SBSW_DEM_POINTER_WRITE_TIMESERIESENTRYCOMPANION */
# endif
}
#endif

#if (DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_NORMAL == STD_ON)
/* ****************************************************************************
 % Dem_Memory_TimeSeries_EntryManager_StoreNormalFutureSamples
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_StoreNormalFutureSamples(
  Dem_Cfg_MemoryIndexType MemoryIndex,
  CONST(Dem_Mem_TimeSeriesEntryPtrType, AUTOMATIC)  Entry,
  Dem_Mem_TimeSeriesEntryCompanionConstPtrType  EntryCompanion
  )
{
  uint8 lMissingSamples;

  lMissingSamples = Dem_Memory_TimeSeries_EntryManager_GetMissingFutureNormalSample(EntryCompanion);                             /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */

  if (lMissingSamples > 0u)
  {
    uint8 lSourceSample;
    uint8 lTargetSample;

    lTargetSample = (Dem_Cfg_TimeSeriesPastSamplesNormal() + Dem_Cfg_TimeSeriesFutureSamplesNormal()) - lMissingSamples;
# if (DEM_CFG_SUPPORT_TIME_SERIES_PAST_NORMAL == STD_ON)
    lSourceSample = (Dem_Memory_TimeSeries_RingBuffer_GetNormalSampleCount() - 1u); /* Most Recent sample */
# else
    lSourceSample = 0u;
# endif

    Dem_Memory_TimeSeries_EntryManager_CopyNormalDidsFromRingBuffer(                                                             /* SBSW_DEM_POINTER_TIMESERIESENTRY_NORMALBUFFER */
      Entry->EventId,
      lSourceSample,
      Dem_Memory_TimeSeries_EntryManager_GetNormalDataPtr(Entry, lTargetSample),                                                 /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
      Dem_Memory_TimeSeries_EntryManager_GetRecMaxRawSize()
      );

    --lMissingSamples;
    Dem_Memory_TimeSeries_EntryManager_SetUnusedFutureSamplesNormal(Entry, lMissingSamples);                                     /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    Dem_Memory_TimeSeries_EntryManager_SetMissingNormalSamples(EntryCompanion, lMissingSamples);                                 /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */

    Dem_Memory_TimeSeries_EntryManager_TriggerNvMStorageOnFutureSampleUpdate(MemoryIndex, EntryCompanion, Entry->EventId);       /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_FAST == STD_ON)
/* ****************************************************************************
 % Dem_Memory_TimeSeries_EntryManager_StoreFastFutureSamples
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_StoreFastFutureSamples(
  Dem_Cfg_MemoryIndexType MemoryIndex,
  CONST(Dem_Mem_TimeSeriesEntryPtrType, AUTOMATIC)  Entry,
  Dem_Mem_TimeSeriesEntryCompanionConstPtrType  EntryCompanion
)
{
  uint8 lMissingSamples;

  lMissingSamples = Dem_Memory_TimeSeries_EntryManager_GetMissingFuturesFastSamples(EntryCompanion);                             /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */

  if (lMissingSamples > 0u)
  {
    uint8 lSourceSample;
    uint8 lTargetSample;

    lTargetSample = (Dem_Cfg_TimeSeriesPastSamplesFast() + Dem_Cfg_TimeSeriesFutureSamplesFast()) - lMissingSamples;
# if (DEM_CFG_SUPPORT_TIME_SERIES_PAST_FAST == STD_ON)
    lSourceSample = (Dem_Memory_TimeSeries_RingBuffer_GetFastSampleCount() - 1u); /* Most Recent sample */
# else
    lSourceSample = 0u;
# endif

    Dem_Memory_TimeSeries_EntryManager_CopyFastDidsFromRingBuffer(                                                               /* SBSW_DEM_POINTER_TIMESERIESENTRY_FASTBUFFER */
      Entry->EventId,
      lSourceSample,
      Dem_Memory_TimeSeries_EntryManager_GetFastDataPtr(Entry, lTargetSample),                                                   /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
      Dem_Memory_TimeSeries_EntryManager_GetRecMaxRawSize()
      );

    --lMissingSamples;
    Dem_Memory_TimeSeries_EntryManager_SetUnusedFutureSamplesFast(Entry, lMissingSamples);                                       /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    Dem_Memory_TimeSeries_EntryManager_SetMissingFastSamples(EntryCompanion, lMissingSamples);                                   /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */

    Dem_Memory_TimeSeries_EntryManager_TriggerNvMStorageOnFutureSampleUpdate(MemoryIndex, EntryCompanion, Entry->EventId);       /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES_PAST == STD_ON)
/* ****************************************************************************
 % Dem_Memory_TimeSeries_EntryManager_StorePastSamples
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_StorePastSamples(
  Dem_EventIdType EventId,
  Dem_Cfg_MemoryIndexType MemoryIndex
  )
{
  Dem_Mem_TimeSeriesEntryPtrType lEntry;

  lEntry = Dem_Memory_TimeSeries_GetEntrySafe(MemoryIndex);

# if (DEM_CFG_SUPPORT_TIME_SERIES_PAST_NORMAL == STD_ON)
  if(Dem_Memory_TimeSeries_TestEventSupportNormal(EventId) == TRUE)
  {
    uint8 lSourceSample;
    uint8 lNumberStoredSamples;
    uint8 lNumberNotStoredSamples;
    uint16 lTimeSinceLastSample;

    lNumberStoredSamples = Dem_Memory_TimeSeries_RingBuffer_GetNormalSampleCount();
    lNumberNotStoredSamples = Dem_Cfg_TimeSeriesPastSamplesNormal() - lNumberStoredSamples;

    /* Disable requirement to support float when time series powertrain is disabled */
#  if (DEM_CFG_SUPPORT_TIME_SERIES_POWERTRAIN == STD_ON)
    lTimeSinceLastSample = Dem_Memory_TimeSeries_EntryManager_RoundFloatToUint16(
                             (float32)(Dem_Cfg_TimeSeriesNormalRate() - Dem_Memory_TimeSeries_Sampler_GetNormalRateTimer())      /* PRQA S 4394 */ /* MD_DEM_10.8_TdIntermediateIntegerToFloat */
                             * Dem_Cfg_DemTaskTime()
                           );
#  else
    lTimeSinceLastSample = 0x00U;
#  endif

    for (lSourceSample = 0u; lSourceSample < lNumberStoredSamples; ++lSourceSample)
    {
      uint8 lTargetSample;
      lTargetSample = lSourceSample + lNumberNotStoredSamples;

      Dem_Memory_TimeSeries_EntryManager_CopyNormalDidsFromRingBuffer(                                                           /* SBSW_DEM_POINTER_TIMESERIESENTRY_NORMALBUFFER */
        EventId,
        lSourceSample,
        Dem_Memory_TimeSeries_EntryManager_GetNormalDataPtr(lEntry, lTargetSample),                                              /* SBSW_DEM_POINTER_WRITE_TIMESERIESENTRY */
        Dem_Memory_TimeSeries_EntryManager_GetRecMaxRawSize()
        );
    }
    Dem_Memory_TimeSeries_EntryManager_SetUnusedPastSamplesNormal(lEntry, lNumberNotStoredSamples);                              /* SBSW_DEM_POINTER_WRITE_TIMESERIESENTRY */
    Dem_Memory_TimeSeries_EntryManager_SetTimeSinceLastSample(lEntry, lTimeSinceLastSample);                                     /* SBSW_DEM_POINTER_WRITE_TIMESERIESENTRY */
  }
# endif

# if (DEM_CFG_SUPPORT_TIME_SERIES_PAST_FAST == STD_ON)
  if (Dem_Memory_TimeSeries_TestEventSupportFast(EventId) == TRUE)
  {
    uint8 lSourceSample;
    uint8 lNumberStoredSamples;
    uint8 lNumberNotStoredSamples;
    uint16 lTimeSinceLastSample;

    lNumberStoredSamples = Dem_Memory_TimeSeries_RingBuffer_GetFastSampleCount();
    lNumberNotStoredSamples = Dem_Cfg_TimeSeriesPastSamplesFast() - lNumberStoredSamples;

    /* Disable requirement to support float when time series powertrain is disabled */
#  if (DEM_CFG_SUPPORT_TIME_SERIES_POWERTRAIN == STD_ON)
    lTimeSinceLastSample = Dem_Memory_TimeSeries_EntryManager_RoundFloatToUint16(
                             (float32)(Dem_Cfg_TimeSeriesFastRate() - Dem_Memory_TimeSeries_Sampler_GetFastRateTimer())   /* PRQA S 4394 */ /* MD_DEM_10.8_TdIntermediateIntegerToFloat */
                             * Dem_Cfg_DemTaskTime()
                           );
#  else
    lTimeSinceLastSample = 0x00U;
#  endif

    for (lSourceSample = 0u; lSourceSample < lNumberStoredSamples; ++lSourceSample)
    {
      uint8 lTargetSample;
      lTargetSample = lSourceSample + lNumberNotStoredSamples;

      Dem_Memory_TimeSeries_EntryManager_CopyFastDidsFromRingBuffer(                                                             /* SBSW_DEM_POINTER_TIMESERIESENTRY_FASTBUFFER */
        EventId,
        lSourceSample,
        Dem_Memory_TimeSeries_EntryManager_GetFastDataPtr(lEntry, lTargetSample),                                                /* SBSW_DEM_POINTER_WRITE_TIMESERIESENTRY */
        Dem_Memory_TimeSeries_EntryManager_GetRecMaxRawSize()
        );
    }
    Dem_Memory_TimeSeries_EntryManager_SetUnusedPastSamplesFast(lEntry, lNumberNotStoredSamples);                                /* SBSW_DEM_POINTER_WRITE_TIMESERIESENTRY */
    Dem_Memory_TimeSeries_EntryManager_SetTimeSinceLastSample(lEntry, lTimeSinceLastSample);                                     /* SBSW_DEM_POINTER_WRITE_TIMESERIESENTRY */
  }
# endif

}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif


#if ((DEM_FEATURE_NEED_TIME_SERIES == STD_ON) && (DEM_CFG_SUPPORT_DCM == STD_ON))
/* ****************************************************************************
 % Dem_Memory_TimeSeries_EntryManager_Lock
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
Dem_Memory_TimeSeries_EntryManager_Lock(
  Dem_Mem_TimeSeriesEntryCompanionConstPtrType EntryCompanion
)
{
/* >>>> -------------------------------- Enter Critical Section: DcmApi */
/* This function is involed in main function. To prevent that the readout status and client counter are
 * modified due to enable DTC update, a critical section is needed */
  Dem_EnterCritical_DcmApi();
  if (Dem_Memory_TimeSeries_EntryManager_GetReadoutState(EntryCompanion) == DEM_MEMORY_TIMESERIES_ENTRYMANAGER_READOUTSTATUS_UNLOCKED)  /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  {
    Dem_Memory_TimeSeries_EntryManager_SetReadoutState(EntryCompanion,
      DEM_MEMORY_TIMESERIES_ENTRYMANAGER_READOUTSTATUS_LOCKED_FOR_READOUT);                                                      /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }

  Dem_Internal_AssertReturnVoid(Dem_Memory_TimeSeries_EntryManager_GetReadoutState(EntryCompanion)                               /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
      == DEM_MEMORY_TIMESERIES_ENTRYMANAGER_READOUTSTATUS_LOCKED_FOR_READOUT, DEM_E_INCONSISTENT_STATE);

  Dem_Memory_TimeSeries_EntryManager_IncrementClientCounter(EntryCompanion);                                                     /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */


  Dem_LeaveCritical_DcmApi();
/* <<<< -------------------------------- Leave Critical Section: DcmApi */
}
#endif

#if ((DEM_FEATURE_NEED_TIME_SERIES == STD_ON) && (DEM_CFG_SUPPORT_DCM == STD_ON))
/* ****************************************************************************
 % Dem_Memory_TimeSeries_EntryManager_ReleaseLock
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
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_ReleaseLock(
  Dem_Mem_TimeSeriesEntryCompanionConstPtrType  EntryCompanion
)
{
  boolean lReturn;
  lReturn = FALSE;

/* >>>> -------------------------------- Enter Critical Section: DcmApi */
/* this function is involved when a client enables the DTC update. A critical section is needed to prevent the status being modified from main function */
  Dem_EnterCritical_DcmApi();
  Dem_Memory_TimeSeries_EntryManager_DecrementClientCounter(EntryCompanion);                                                     /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  if (Dem_Memory_TimeSeries_EntryManager_GetClientCounter(EntryCompanion) == 0x00U)                                              /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */                                               
  {
    if (Dem_Memory_TimeSeries_EntryManager_GetReadoutState(EntryCompanion)
      == DEM_MEMORY_TIMESERIES_ENTRYMANAGER_READOUTSTATUS_LOCKED_FOR_READOUT )                                                   /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    {
      Dem_Memory_TimeSeries_EntryManager_SetReadoutState(EntryCompanion,                                                         /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
        DEM_MEMORY_TIMESERIES_ENTRYMANAGER_READOUTSTATUS_UNLOCKED);
    }

    if (Dem_Memory_TimeSeries_EntryManager_GetReadoutState(EntryCompanion)
      == DEM_MEMORY_TIMESERIES_ENTRYMANAGER_READOUTSTATUS_DELETION_CANDIDATE)                                                    /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    {
      lReturn = TRUE;
    }
  }
  Dem_LeaveCritical_DcmApi();
/* <<<< -------------------------------- Leave Critical Section: DcmApi */

  return lReturn;
}
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 % Dem_Memory_TimeSeries_EntryManager_RequestDeletion
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
Dem_Memory_TimeSeries_EntryManager_RequestDeletion(
  Dem_Mem_TimeSeriesEntryCompanionConstPtrType EntryCompanion
)
{
  boolean lReturn;
  lReturn = FALSE;
/* >>>> -------------------------------- Enter Critical Section: DcmApi */
/* This function is involed in main function. To prevent that the readout status is modified due to enable DTC update, a critical section is needed */
  Dem_EnterCritical_DcmApi();
  if (Dem_Memory_TimeSeries_EntryManager_GetReadoutState(EntryCompanion)
    == DEM_MEMORY_TIMESERIES_ENTRYMANAGER_READOUTSTATUS_LOCKED_FOR_READOUT)                                                      /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  {
    Dem_Memory_TimeSeries_EntryManager_SetReadoutState(EntryCompanion, 
      DEM_MEMORY_TIMESERIES_ENTRYMANAGER_READOUTSTATUS_DELETION_CANDIDATE);                                                      /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }
  Dem_LeaveCritical_DcmApi();
/* <<<< -------------------------------- Leave Critical Section: DcmApi */
                                                                                                                                 
  if (Dem_Memory_TimeSeries_EntryManager_GetReadoutState(EntryCompanion)                                                         /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    == DEM_MEMORY_TIMESERIES_ENTRYMANAGER_READOUTSTATUS_UNLOCKED)  
  {/* The client counter and readout status of an entry with readout status of UNLOCKED can only be changed within main function 
      So no critical section is needed */
    lReturn = TRUE;
  }

  return lReturn;
}
#endif

#if (DEM_CFG_SUPPORT_TIME_SERIES_POWERTRAIN == STD_ON)
/* ****************************************************************************
 % Dem_Memory_TimeSeries_EntryManager_RoundFloatToUint16
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
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Memory_TimeSeries_EntryManager_RoundFloatToUint16(
  float32 Value
)
{
  uint16 lConvertedValue;

  if (Value > 0.0f)
  {
    if (Value < (float32)DEM_MEMORY_TIMERSERIES_UINT16_MAXVALUE)
    {
      lConvertedValue = (uint16)(Value + 0.5f);                                                                                  /* PRQA S 4395 */ /* MD_DEM_10.8_TdFloatToInteger */  
    }
    else /* values overstepping the max uint16 values are replaced by the max value */
    {
      lConvertedValue = DEM_MEMORY_TIMERSERIES_UINT16_MAXVALUE;
    }
  }
  else /* negative values are replaced by 0 */
  {
    lConvertedValue = 0u;                                                                                                       
  }

  return  lConvertedValue;
}
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_ENTRYMANAGER_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_EntryManager_Implementation.h
 *********************************************************************************************************************/
