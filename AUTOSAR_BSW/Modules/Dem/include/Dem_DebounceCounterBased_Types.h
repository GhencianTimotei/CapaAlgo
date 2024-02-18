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
 *  \addtogroup Dem_DebounceCounterBased
 *  \{
 *  \file       Dem_DebounceCounterBased_Types.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Public types of DebounceCounterBased subcomponent
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_DEBOUNCECOUNTERBASED_TYPES_H)
#define DEM_DEBOUNCECOUNTERBASED_TYPES_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_Int.h"
#include "Dem_DebounceBase_Types.h"
/* ------------------------------------------------------------------------- */


/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/
/*! Initial debounce value for counter based debouncing */
#define DEM_DEBOUNCE_COUNTERBASED_INIT_VALUE           0


/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

typedef struct Dem_DebounceCounterBased_InfoType_s Dem_DebounceCounterBased_InfoType;

/*! Data for counter-based debouncing
 *  \extends Dem_DebounceBase_InfoType_s  */
struct Dem_DebounceCounterBased_InfoType_s
{
  Dem_DebounceBase_InfoType Base;      /*!< Base class object. This attribute must come first! */
  sint16 OldDebounceValue;             /*!< [in] debounce counter before processing */
  sint16 NewDebounceValue;             /*!< [out] debounce counter after processing */
};

/*! Pointer to debounce algorithm management data */
typedef P2VAR(Dem_DebounceCounterBased_InfoType, TYPEDEF, AUTOMATIC) Dem_DebounceCounterBased_InfoPtrType;
/*! Non-writeable pointer to debounce algorithm management data */
typedef P2CONST(Dem_DebounceCounterBased_InfoType, TYPEDEF, AUTOMATIC) Dem_DebounceCounterBased_ConstInfoPtrType;

#endif /* DEM_DEBOUNCECOUNTERBASED_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_DebounceCounterBased_Types.h
 *********************************************************************************************************************/
