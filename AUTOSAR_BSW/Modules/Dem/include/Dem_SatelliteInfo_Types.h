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
/*! \addtogroup Dem_SatelliteInfo
 *  \{
 *  \file       Dem_SatelliteInfo_Types.h
 *  \brief      Implementation file for the MICROSAR Dem
 *  \details    Public types of SatelliteInfo subcomponent
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_SATELLITEINFO_TYPES_H)
#define DEM_SATELLITEINFO_TYPES_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

               /* Includes to inherit types belonging to other logical units */
/* ------------------------------------------------------------------------- */
#include "Dem_Int.h"
#include "Dem_Infrastructure_Types.h"
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

/*! The data of a satellite */
struct Dem_SatelliteInfo_s
{
  uint8 InitStatus;                              /*!< Initialization status */
  uint8 SatelliteStatus;                         /*!< Status flags */
};

/*! Converts between a Dem_SatelliteInfo_Type and a raw data type. */
union Dem_SatelliteInfo_Type_u
{                                                                                                                                /* PRQA S 0750 */ /* MD_MSR_Union */
  volatile struct Dem_SatelliteInfo_s Data;      /*!< The detailed data type. */
  volatile Dem_Com_ProcessorWordType   Raw;      /*!< The raw data type intended for queue communication. */
};

/*! Converts between a Dem_SatelliteInfo_Type and a raw data type. */
typedef union Dem_SatelliteInfo_Type_u Dem_SatelliteInfo_Type;

#endif /* DEM_SATELLITEINFO_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_SatelliteInfo_Types.h
 *********************************************************************************************************************/
