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
/*! \addtogroup Dem_InitState
 *  \{
 *  \file       Dem_InitState_Types.h
 *  \brief      Diagnostic Event Manager (Dem) Type and Macro definition file
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_INITSTATE_TYPES_H)
#define DEM_INITSTATE_TYPES_H

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
/*!
 * \defgroup  Dem_InitState_State  Macros encoding the initialization states
 * Macros encoding the initialization states
 * \{
 */
#define DEM_INITSTATE_UNINITIALIZED              (0U)                /*!< Initialization state directly after system startup - If value changed to not zero, change Initialization of SatelitteInfo.InitStatus too*/
#define DEM_INITSTATE_HALTED_AFTER_ERROR         (1U)                /*!< Initialization state after a failed runtime check has disabled the module */
#define DEM_INITSTATE_PREINITIALIZED             (2U)                /*!< Initialization state after Dem_PreInit */
#define DEM_INITSTATE_SHUTDOWN                   (3U)                /*!< Initialization state after Dem_Shutdown */
#define DEM_INITSTATE_INITIALIZED                (4U)                /*!< Initialization state after Dem_Init */
/*!
 * \}
 */


/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/


/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


#endif /* DEM_INITSTATE_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_InitState_Types.h
 *********************************************************************************************************************/
