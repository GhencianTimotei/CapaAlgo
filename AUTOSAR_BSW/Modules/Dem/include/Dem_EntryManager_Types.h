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
 *  \file       Dem_EntryManager_Types.h
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

#if !defined (DEM_ENTRYMANAGER_TYPES_H)
#define DEM_ENTRYMANAGER_TYPES_H

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
#include "Dem_Int.h"
#include "Dem_TimeSeriesIF_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

 /* Max number of samples that can be stored in a time series powertrain memory entry. - Used for runtime checks */
#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
# if (DEM_CFG_TIMESERIES_NORMAL_PAST_SAMPLES > DEM_CFG_TIMESERIES_FAST_PAST_SAMPLES)
# define DEM_MEMORY_TIMESERIES_ENTRYMANAGER_MAXSAMPLES DEM_CFG_TIMESERIES_NORMAL_PAST_SAMPLES
# else
# define DEM_MEMORY_TIMESERIES_ENTRYMANAGER_MAXSAMPLES DEM_CFG_TIMESERIES_FAST_PAST_SAMPLES
# endif
#else
# define DEM_MEMORY_TIMESERIES_ENTRYMANAGER_MAXSAMPLES 0u
#endif

/* Init value of time series memory entry used in time series powertrain - Indicate that none past sample was ever stored */
#define DEM_MEMORY_TIMESERIES_ENTRYMANAGER_UNUSEDSAMPLES_INITVALUE (0xFFu) 

 /* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
 /*!
  * \defgroup  Dem_Memory_TimeSeries_EntryManager_ReadoutStatusType Dem_Memory_TimeSeries_EntryManager_ReadoutStatusType
  * \{
  */
  /*! This type is used to encode the time-series memory entry readout status */
typedef uint8 Dem_Memory_TimeSeries_EntryManager_ReadoutStatusType;


#define DEM_MEMORY_TIMESERIES_ENTRYMANAGER_READOUTSTATUS_UNUSED                        0u  /*!< Initialization value, time-series entry is unused */
#define DEM_MEMORY_TIMESERIES_ENTRYMANAGER_READOUTSTATUS_UNLOCKED                      1u  /*!< Time-series entry is allocated to an event. No on-going readout */
#define DEM_MEMORY_TIMESERIES_ENTRYMANAGER_READOUTSTATUS_LOCKED_FOR_READOUT            2u  /*!< Time-series entry is being read out via service 19 subfunction 04 */
#define DEM_MEMORY_TIMESERIES_ENTRYMANAGER_READOUTSTATUS_DELETION_CANDIDATE            3u  /*!< Time-series entry is being read out via service 19 subfunction 04 and it should be freed immediately when all ongoing readout finish */
/*!
 * \}
 */
#endif /* DEM_ENTRYMANAGER_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_EntryManager_Types.h
 *********************************************************************************************************************/
