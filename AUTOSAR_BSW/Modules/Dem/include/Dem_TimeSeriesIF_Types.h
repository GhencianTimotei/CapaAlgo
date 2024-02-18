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
 *  \file       Dem_TimeSeriesIF_Types.h
 *  \brief      Manages time series functionality.
 *  \details    Typedefinitions of TimeSeriesIF subcomponent
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_TIMESERIESIF_TYPES_H)
#define DEM_TIMESERIESIF_TYPES_H

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

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

#define DEM_MEMORY_TIMERSERIES_UINT16_MAXVALUE (65535u)

 /* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/
 
/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
 /*! Pointer to a time-series memory entry */
typedef P2VAR(Dem_Cfg_TimeSeriesEntryType, TYPEDEF, DEM_NVM_DATA)    Dem_Mem_TimeSeriesEntryPtrType;
 /*! Pointer to a time-series memory entry */
typedef CONSTP2VAR(Dem_Cfg_TimeSeriesEntryType, TYPEDEF, DEM_NVM_DATA) Dem_Mem_TimeSeriesEntryConstPtrType;
/*! Non-writeable Pointer to a time-series memory entry */
typedef P2CONST(Dem_Cfg_TimeSeriesEntryType, TYPEDEF, DEM_NVM_DATA)  Dem_Mem_ConstTimeSeriesEntryPtrType;

 /*! Pointer to a time-series memory entry companion */
typedef P2VAR(Dem_Cfg_TimeSeriesEntryCompanionType, AUTOMATIC, AUTOMATIC) Dem_Mem_TimeSeriesEntryCompanionPtrType;

 /*! Pointer to a const time-series memory entry companion */
typedef P2CONST(Dem_Cfg_TimeSeriesEntryCompanionType, AUTOMATIC, AUTOMATIC) Dem_Mem_ConstTimeSeriesEntryCompanionPtrType;

/*! Const pointer to a time-series memory entry companion */
typedef CONSTP2VAR(Dem_Cfg_TimeSeriesEntryCompanionType, AUTOMATIC, AUTOMATIC) Dem_Mem_TimeSeriesEntryCompanionConstPtrType;

 /*! Const pointer to a const time-series memory entry companion */
typedef CONSTP2CONST(Dem_Cfg_TimeSeriesEntryCompanionType, AUTOMATIC, AUTOMATIC) Dem_Mem_ConstTimeSeriesEntryCompanionConstPtrType;

#endif /* DEM_TIMESERIESIF_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_TimeSeriesIF_Types.h
 *********************************************************************************************************************/
