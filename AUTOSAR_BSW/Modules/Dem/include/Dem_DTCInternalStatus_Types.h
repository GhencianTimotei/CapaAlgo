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
/*! \addtogroup Dem_DTCInternalStatus
 *  \{
 *  \file       Dem_DTCInternalStatus_Types.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Public types of DTCInternalStatus subcomponent
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_DTCINTERNALSTATUS_TYPES_H)
#define DEM_DTCINTERNALSTATUS_TYPES_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_Int.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*!
 * \defgroup  Dem_DTCInternalStatusBitPosition  Macros encoding bit position for internal status
 * Macros encoding bit position for internal status
 * \{
 */
 
#define DEM_DTCINTERNALSTATUS_STORED_STATUS_POS                0u  /*!< bit start position of stored status */
#define DEM_DTCINTERNALSTATUS_SUPPRESSED_DTC_POS               2u  /*!< bit start position of DTC suppressed */
#define DEM_DTCINTERNALSTATUS_FDC_TOC_POS                      5u /*!< bit start position of fault detection counter threshold this cycle */
#define DEM_DTCINTERNALSTATUS_USER_CONTROLLED_WIR_POS          7u  /*!< bit position of user controlled warning indicator request */

/*!
 * \}
 */


/*!
 * \defgroup  Dem_Esm_StoredStatus  Encoding stored status states
 * \{
 */
 
/*! Enum to encode stored status states */
enum Dem_DTCInternal_StoredStatus
{
  Dem_DTCInternalStatus_StoredStatus_None   = (0U << DEM_DTCINTERNALSTATUS_STORED_STATUS_POS), /*!< Not stored */                 /* PRQA S 0779 */ /* MD_MSR_Rule5.2 */
  Dem_DTCInternalStatus_StoredStatus_Active = (1U << DEM_DTCINTERNALSTATUS_STORED_STATUS_POS), /*!< Active memory entry exists */ /* PRQA S 0779 */ /* MD_MSR_Rule5.2 */
  Dem_DTCInternalStatus_StoredStatus_Aging  = (2U << DEM_DTCINTERNALSTATUS_STORED_STATUS_POS), /*!< Aging memory entry exists */  /* PRQA S 0779 */ /* MD_MSR_Rule5.2 */
  Dem_DTCInternalStatus_StoredStatus_Aged   = (3U << DEM_DTCINTERNALSTATUS_STORED_STATUS_POS),  /*!< Aged memory entry exists */   /* PRQA S 0779 */ /* MD_MSR_Rule5.2 */
  Dem_DTCInternalStatus_StoredStatus_Invalid = (4U << DEM_DTCINTERNALSTATUS_STORED_STATUS_POS)  /*!< First invalid value, see content of event internal status */ /* PRQA S 0779 */ /* MD_MSR_Rule5.2 */
};
typedef enum Dem_DTCInternal_StoredStatus Dem_DTCInternal_StoredStatusType;

/*!
 * \}
 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/*! Type to store the internal status of an DTC */
typedef uint8 Dem_DTC_InternalStatusType;
/*! Type to store the extended status of an DTC */
typedef uint8 Dem_DTC_ExtendedStatusType;

#endif /* DEM_DTCINTERNALSTATUS_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_DTCInternalStatus_Types.h
 *********************************************************************************************************************/
