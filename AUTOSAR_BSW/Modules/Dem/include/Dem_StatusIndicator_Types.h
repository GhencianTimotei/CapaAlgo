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
/*! \addtogroup Dem_StatusIndicator
 *  \{
 *  \file       Dem_StatusIndicator_Types.h
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

#if !defined (DEM_STATUSINDICATOR_TYPES_H)
#define DEM_STATUSINDICATOR_TYPES_H

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
/*! Handle for StatusIndicator actions set on satellite, read on master*/

/*!
 * \defgroup  Dem_StatusIndicator_QueueStates  Macros encoding StatusIndicator queue states
 * Macros encoding StatusIndicator queue state
 * \{
 */
# define DEM_STATUSINDICATOR_QUEUE_INITIAL                   ((uint8)(0x00U))   /*!< Initial state */
# define DEM_STATUSINDICATOR_QUEUE_SYMPTOM_REACHED           ((uint8)(0x04U))   /*!< Set StatusIndicator symptom shall be executed */
/*!
 * \}
 */

/*!
 * \defgroup  Dem_StatusIndicator_BitPosition  Macros encoding bit indexes of StatusIndicator byte
 * Macros encoding bit indexes of StatusIndicator byte
 * \{
 */
/*! Bit position in StatusIndicator byte indicating Unconfirmed DTC */
#  define DEM_STATUSINDICATOR_UDTC      (1U)
/*! Bit position in StatusIndicator byte indicating Unconfirmed DTC This Operation Cycle */
#  define DEM_STATUSINDICATOR_UDTCTOC   (2U)
/*! Bit position in StatusIndicator byte indicating Unconfirmed DTC Since Last Clear */
#  define DEM_STATUSINDICATOR_UDTCSLC   (4U)
/*! Bit position in StatusIndicator byte indicating Aged DTC */
#  define DEM_STATUSINDICATOR_ADTC      (8U)
/*! Bit position in StatusIndicator byte indicating Symptom Since Last Clear */
#  define DEM_STATUSINDICATOR_SSLC      (16U)
/*! Bit position in StatusIndicator byte indicating Warning Indicator Since Last Clear */
#  define DEM_STATUSINDICATOR_WIRSLC    (32U)
/*! Bit position in StatusIndicator byte indicating Emission Related DTC */
#  define DEM_STATUSINDICATOR_ERDTC     (64U)
/*! Bit position in StatusIndicator byte indicating Test Failed Since Last Clear */
#  define DEM_STATUSINDICATOR_TFSLC     (128U)
/*!
 * \}
 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/*! Type to store the StatusIndicator status of an event */
typedef uint8 Dem_StatusIndicator_Type;

/*! Type to store the StatusIndicator queued action */
typedef uint8 Dem_StatusIndicator_QueueActionType;

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/

#endif /* DEM_STATUSINDICATOR_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_StatusIndicator_Types.h
 *********************************************************************************************************************/
