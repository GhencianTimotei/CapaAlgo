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
/*! \addtogroup Dem_EnableCondition
 *  \{
 *  \file       Dem_EnableCondition_Types.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_ENABLECONDITION_TYPES_H)
#define DEM_ENABLECONDITION_TYPES_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_Int.h"
/* ------------------------------------------------------------------------- */


/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*! Handle for enable condition 'ControlDTCSetting' */
#define DEM_ENABLECONDITION_CONTROLDTCSETTING    0u

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/*! Test the active state of an enable condition group */
#define DEM_ENABLECONDITION_TEST_ENABLECONDITIONGROUP_ACTIVE(State)            (((State) & 0x01U) != 0u)
/*! Set the active state of an enable condition group */
#define DEM_ENABLECONDITION_SET_ENABLECONDITIONGROUP_ACTIVE(State)             ((uint8)((State) | 0x01U))
/*! Reset the active state of an enable condition group */
#define DEM_ENABLECONDITION_RESET_ENABLECONDITIONGROUP_ACTIVE(State)           ((uint8)((State) & 0xfeU))

/*! Test the 'queued disable' state of an enable condition group */
#define DEM_ENABLECONDITION_TEST_ENABLECONDITIONGROUP_QUEUE_DISABLE(State)     (((State) & 0x02U) != 0u)
/*! Set the 'queued disable' state of an enable condition group */
#define DEM_ENABLECONDITION_SET_ENABLECONDITIONGROUP_QUEUE_DISABLE(State)      ((uint8)((State) | 0x02U))
/*! Reset the 'queued disable' state of an enable condition group */
#define DEM_ENABLECONDITION_RESET_ENABLECONDITIONGROUP_QUEUE_DISABLE(State)    ((uint8)((State) & 0xfdU))

/*! Test the 'queued enable' state of an enable condition group */
#define DEM_ENABLECONDITION_TEST_ENABLECONDITIONGROUP_QUEUE_ENABLE(State)      (((State) & 0x04U) != 0u)
/*! Set the 'queued enable' state of an enable condition group */
#define DEM_ENABLECONDITION_SET_ENABLECONDITIONGROUP_QUEUE_ENABLE(State)       ((uint8)((State) | 0x04U))
/*! Reset the 'queued enable' state of an enable condition group */
#define DEM_ENABLECONDITION_RESET_ENABLECONDITIONGROUP_QUEUE_ENABLE(State)     ((uint8)((State) & 0xfbU))

/*! Test the 'process disable' state of an enable condition group */
#define DEM_ENABLECONDITION_TEST_ENABLECONDITIONGROUP_PROCESS_DISABLE(State)   (((State) & 0x08U) != 0u)
/*! Set the 'process disable' state of an enable condition group */
#define DEM_ENABLECONDITION_SET_ENABLECONDITIONGROUP_PROCESS_DISABLE(State)    ((uint8)((State) | 0x08U))
/*! Reset the 'process disable' state of an enable condition group */
#define DEM_ENABLECONDITION_RESET_ENABLECONDITIONGROUP_PROCESS_DISABLE(State)  ((uint8)((State) & 0xf7U))

/*! Test the 'process enable' state of an enable condition group */
#define DEM_ENABLECONDITION_TEST_ENABLECONDITIONGROUP_PROCESS_ENABLE(State)    (((State) & 0x10U) != 0u)
/*! Set the 'process enable' state of an enable condition group */
#define DEM_ENABLECONDITION_SET_ENABLECONDITIONGROUP_PROCESS_ENABLE(State)     ((uint8)((State) | 0x10U))
/*! Reset the 'process enable' state of an enable condition group */
#define DEM_ENABLECONDITION_RESET_ENABLECONDITIONGROUP_PROCESS_ENABLE(State)   ((uint8)((State) & 0xefU))


/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/*! Iterator type for iteration over enable conditions of an enable condition group */
typedef struct Dem_Cfg_ComplexIterType_s Dem_Cfg_EventEnableConditionGroupIterType;

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/

#endif /* DEM_ENABLECONDITION_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_EnableCondition_Types.h
 *********************************************************************************************************************/
