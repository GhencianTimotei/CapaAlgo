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
/*! \addtogroup Dem_Iumpr_RatioIF
 *  \{
 *  \file       Dem_RatioIF_Types.h
 *  \brief      IUMPR RatioIF subcomponent.
 *  \details    Typedefinitions of Ratio subcomponent which provides functionality to manipulate IUMPR ratios for the 
 *              Dem_Iumpr subcomponent.
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_RATIOIF_TYPES_H)
#define DEM_RATIOIF_TYPES_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_Int.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*!
 * \defgroup  DEM_IUMPRGlobalNumeratorsState  Macros encoding Iumpr numerator states
 * Macros encoding Iumpr numerator locked states
 * \{
 */
# define DEM_RATIO_NUMERATORS_LOCKED                     ((uint8)(0x01U))  /*!< Ratio numerators locked globally */
# define DEM_RATIO_NUMERATORS_LOCKED_MASK                ((uint8)(0xfeU))  /*!< Reset mask for Ratio numerators locked globally */
/*!
 * \}
 */

/*! Maximum counter value for numerator / denominator */
# define DEM_RATIO_MAX_VALUE                             ((uint16)0xffffU)

/*!
 * \defgroup  DEM_IUMPRNumeratorStatus  Macros encoding ratio specific numerator states
 * Macros encoding ratio specific numerator states
 * \{
 */
# define DEM_RATIO_NUM_INCREMENTED                       ((uint8)(0x10U))  /*!< Numerator incremented this DCY */
# define DEM_RATIO_NUM_INCREMENTED_MASK                  ((uint8)(0xefU))  /*!< Reset mask for numerator incremented this DCY */
# define DEM_RATIO_NUM_FAULTDETECT                       ((uint8)(0x20U))  /*!< Fault detection completed this DCY */
# define DEM_RATIO_NUM_FAULTDETECT_MASK                  ((uint8)(0xdfU))  /*!< Reset mask for fault detection completed this DCY */
# define DEM_RATIO_DISCONNECTED                          ((uint8)(0x40U))  /*!< Ratio disconnected (suppressed) */
# define DEM_RATIO_DISCONNECTED_MASK                     ((uint8)(0xbfU))  /*!< Reset mask for ratio disconnected (suppressed) */
/*!
 * \}
 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/



#endif /* DEM_RATIOIF_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_RatioIF_Types.h
 *********************************************************************************************************************/
