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
/*!  Project    MICROSAR Diagnostic Event Manager (Dem)
 *
 *  \addtogroup Dem_DebounceIF
 *  \{
 *  \file       Dem_DebounceIF_Types.h
 *  \brief      Implementation file for the MICROSAR Dem
 *  \details    Public types of DebounceIF subcomponent
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_DEBOUNCEIF_TYPES_H)
#define DEM_DEBOUNCEIF_TYPES_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_Int.h"

                                                           /* Required types */
/* ------------------------------------------------------------------------- */
#include "Dem_DebounceBase_Types.h"
#include "Dem_DebounceCounterBased_Types.h"
#include "Dem_DebounceTimeBased_Types.h"
#include "Dem_DebounceMonitorInternal_Types.h"


/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/*! General debounce type. */
typedef union Dem_Debounce_InfoType_u Dem_Debounce_InfoType;

/*! General debounce type. */
union Dem_Debounce_InfoType_u
{                                                                                                                                /* PRQA S 0750 */ /* MD_MSR_Union */
  Dem_DebounceBase_InfoType InvalidDebounce;                /*!< Used in case that the selected debounce algorithm is invalid. */
  Dem_DebounceCounterBased_InfoType CounterBased;           /*!< Data storage for counter based debouncing. */
  Dem_DebounceMonitorInternal_InfoType MonitorInternal;     /*!< Data storage for monitor internal debouncing. */
  Dem_DebounceTimeBased_InfoType TimeBased;                 /*!< Data storage for time based debouncing. */
};


#endif /* DEM_DEBOUNCEIF_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_DebounceIF_Types.h
 *********************************************************************************************************************/
