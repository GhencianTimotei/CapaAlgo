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
/*! \addtogroup Dem_IumprIF
 *  \{
 *  \file       Dem_IumprIF_Types.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Types of the Obd IumprIF subcomponent which manages calculation of the IUMPR ratios.
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_IUMPRIF_TYPES_H)
#define DEM_IUMPRIF_TYPES_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_Int.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/
/*
 * Bitmask to encode the different denominator conditions in denominator condition status in Iumpr data block
 * - Dem_Cfg_ObdIumprData.DenominatorConditionStatusReached:   Bits indicate whether the denominator condition is REACHED
 *                                                             Note: As the the general OBD denominator is incremented 
 *                                                                   immediately with a 'Reached' report, for the general
 *                                                                   OBD denominator conditions the bit indicates also
 *                                                                   whether the denominator is INCREMENTED this cycle
 * - Dem_Cfg_ObdIumprData.DenominatorConditionStatusInhibited: Bits indicate whether the denominator condition is INHIBITED
 *
 * Bit position || Denominator condition
 * -------------------------------------
 * 0            || General Obd Denominator Conditions
 * 1            || General Individual Denominator Conditions
 * 2            || Coldstart Denominator Conditions
 * 3            || Evap Denominator Conditions
 * 4            || 500 Mile Denominator Conditions
 * 5            || Independent Denominator Conditions
 *
*/
 /*!
 * \defgroup  DEM_IUMPRConditionStatus  Macros encoding denominator conditions
 * Macros encoding denominator conditions
 * \{
 */
# define DEM_IUMPR_CONDITIONSTATUS_GENOBD             ((uint8)(0x01U))  /*!< General OBD denominator condition */
# define DEM_IUMPR_CONDITIONSTATUS_GENOBD_MASK        ((uint8)(0xfeU))  /*!< Mask to reset 'General OBD denominator condition' */
# define DEM_IUMPR_CONDITIONSTATUS_GENIND             ((uint8)(0x02U))  /*!< General Individual denominator condition */
# define DEM_IUMPR_CONDITIONSTATUS_GENIND_MASK        ((uint8)(0xfdU))  /*!< Mask to reset 'General Individual denominator condition' */
# define DEM_IUMPR_CONDITIONSTATUS_COLDSTART          ((uint8)(0x04U))  /*!< Coldstart denominator condition */
# define DEM_IUMPR_CONDITIONSTATUS_COLDSTART_MASK     ((uint8)(0xfbU))  /*!< Mask to reset 'Coldstart denominator condition' */
# define DEM_IUMPR_CONDITIONSTATUS_EVAP               ((uint8)(0x08U))  /*!< Evap denominator condition */
# define DEM_IUMPR_CONDITIONSTATUS_EVAP_MASK          ((uint8)(0xf7U))  /*!< Mask to reset 'Evap denominator condition' */
# define DEM_IUMPR_CONDITIONSTATUS_500MI              ((uint8)(0x10U))  /*!< 500Mi denominator condition */
# define DEM_IUMPR_CONDITIONSTATUS_500MI_MASK         ((uint8)(0xefU))  /*!< Mask to reset '500Mi denominator condition' */
# define DEM_IUMPR_CONDITIONSTATUS_INDEPENDENT        ((uint8)(0x20U))  /*!< Independent denominator condition */
# define DEM_IUMPR_CONDITIONSTATUS_INDEPENDENT_MASK   ((uint8)(0xdfU))  /*!< Mask to reset 'independent denominator condition' */
 /*!
 * \}
 */

/*!
 * \defgroup  Dem_Iumpr_Invalid Macros encoding specific invalid values
 * Macros encoding invalid condition and readiness group
 * \{
 */
# define DEM_DENOMINATOR_COND_INVALID                ((Dem_IumprDenomCondIdType)(0x08U))  /*!< First out of range value of Dem_IumprDenomCondIdType */
# define DEM_IUMPR_READINESS_GROUP_INVALID        ((Dem_IumprReadinessGroupType)(0x11U))  /*!< First out of range value of Dem_IumprReadinessGroupType */
/*!
 * \}
 */


/*!
 * \defgroup  DEM_IUMPRHybridIgnitionCounterState  Macros encoding hybrid ignition cycle counter states
 * Macros encoding hybrid ignition counter states
 * \{
 */
# define DEM_IUMPR_IGN_CYC_HYBRID_INCREMENTED            ((uint8)(0x01U))  /*!< Hybrid ignition cycle counter incremented this DCY */
# define DEM_IUMPR_IGN_CYC_HYBRID_INCREMENTED_MASK       ((uint8)(0xfeU))  /*!< Reset mask hybrid ignition cycle counter incremented this DCY */
/*!
 * \}
 */




/*! Number of ratios which are processed at most before critical section 'DiagMonitor' is left for a short time. */
# define DEM_IUMPR_RESET_PENDING_RATIO                   ((uint8)50u)

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/*! Filter data for IUMPR requests */
struct Dem_IumprFilter_InfoType_s
{
  Dem_EventIdType      FirstEvent;     /*!< First event matching the request */
  Dem_EventIdType      CurrentEvent;   /*!< Current event id */
  Dem_EventIdType      LastEvent;      /*!< Last event matching the request */
  uint8                ReadinessGroup; /*!< Filtered readiness group */
};

/*! Filtering strategy for DTC filtering */
typedef enum Dem_Iumpr_RatioAvailability
{
  Dem_Iumpr_ReconnectRatio = 0, /*!< Command to connect ratio */
  Dem_Iumpr_DisconnectRatio   /*!< Command to disconnect ratio */
} Dem_Iumpr_RatioAvailabilityType;

/*! Filter data type for IUMPR requests */
typedef struct Dem_IumprFilter_InfoType_s Dem_IumprFilter_InfoType;

/*! Ignition cycle type */
typedef enum Dem_Iumpr_CycleCounter_CycleCounterType
{
  Dem_Iumpr_CycleCounter_IgnitionCycleCounter = 0,    /*!< Ignition cycle counter */
  Dem_Iumpr_CycleCounter_IgnitionHybridCycleCounter   /*!< Ignition Hybrid cycle counter */
} Dem_Iumpr_CycleCounter_CycleCounterType;

/*! Origin of fault reporting */
typedef enum Dem_Iumpr_FaultOriginType
{
  Dem_Iumpr_FaultOrigin_API = DEM_RATIO_API,                        /*!< Fault was reported by API */
  Dem_Iumpr_FaultOrigin_EventReport = DEM_RATIO_OBSERVER,           /*!< Fault was reported by SetEventStatus*/
  Dem_Iumpr_FaultOrigin_Invalid = DEM_RATIO_REPORTINGTYPE_INVALID   /*!< Invalid Reporting Type */
} Dem_Iumpr_FaultOriginType;

#endif /* DEM_IUMPRIF_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_IumprIF_Types.h
 *********************************************************************************************************************/
