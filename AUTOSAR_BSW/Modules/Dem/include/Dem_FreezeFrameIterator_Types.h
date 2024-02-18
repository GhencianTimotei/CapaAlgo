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
/*! \addtogroup Dem_FreezeFrameIterator
 *  \{
 *  \file       Dem_FreezeFrameIterator_Types.h
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

#if !defined (DEM_FREEZEFRAMEITERATOR_TYPES_H)
#define DEM_FREEZEFRAMEITERATOR_TYPES_H

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


/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/


/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/*! This used for FreezeFrameIterator handles. */
typedef uint8 Dem_FreezeFrameIterator_HandleType;

/*!
 * \defgroup  Dem_FreezeFrameIterator_DTCFormatType Dem_FreezeFrameIterator_DTCFormatType
 * \{
 */
/*! This type is used to encode the Dem_DTCFormatType of a FreezeFrameIterator. */
typedef uint8 Dem_FreezeFrameIterator_DTCFormatType;
#define DEM_FREEZEFRAMEITERATOR_DTCFORMAT_INIT           0u  /*!< Initialization value, filter is unused */
#define DEM_FREEZEFRAMEITERATOR_DTCFORMAT_UDS            1u  /*!< Selects the 3-byte UDS DTC format (refer to configuration parameter DemUdsDTC) */
#define DEM_FREEZEFRAMEITERATOR_DTCFORMAT_OBD            2u  /*!< Selects the 2-byte OBD DTC format (refer to configuration parameter DemObdDTC) */
#define DEM_FREEZEFRAMEITERATOR_DTCFORMAT_J1939          3u  /*!< Selects the merged SPN + FMI to 3-byte J1939 DTC format (refer to DemJ1939DTC) */
/*!
 * \}
 */

/*!
 * \defgroup  Dem_FreezeFrameIterator_J1939State Macros encoding state for J1939 freeze frame filtering
 * \{
 */
#define DEM_FREEZEFRAMEITERATOR_J1939STATE_INIT           (0U)  /*!< Initialization value, J1939 freeze frame iterator is unused */
#define DEM_FREEZEFRAMEITERATOR_J1939STATE_USED           (1U)  /*!< A J1939 freeze frame filter was set up */
#define DEM_FREEZEFRAMEITERATOR_J1939STATE_PENDING        (2U)  /*!< A J1939 freeze frame filter was set up, filtering was interrupted 
                                                                     by data modification and will be continued in next iteration */
/*!
 * \}
 */

 /*!
 * \defgroup  This type is used in service 0x19 03 indicating reserved record number values
 * \{
 */
#define DEM_FREEZEFRANEITERATOR_TIMESERIES_POWERTRAIN_RECORDNUMBER   (0x30u) /*!< Powertrain Timeseries specific record number */
#define DEM_FREEZEFRAMEITERATOR_INVALID_RECORDNUMBER                 (255U)  /*!< First invalid freeze frame record number */
 /*!
 * \}
 */


#endif /* DEM_FREEZEFRAMEITERATOR_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_FreezeFrameIterator_Types.h
 *********************************************************************************************************************/
