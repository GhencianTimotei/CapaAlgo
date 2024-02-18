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
/*! \addtogroup Dem_SatelliteIF
 *  \{
 *  \file       Dem_SatelliteIF_Types.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Public types of the SatelliteIF subcomponent
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_SATELLITEIF_TYPES_H)
#define DEM_SATELLITEIF_TYPES_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

               /* Includes to inherit types belonging to other logical units */
/* ------------------------------------------------------------------------- */
#include "Dem_Int.h"
#include "Dem_Infrastructure_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/
#define DEM_SATELLITE_APPLICATION_ZERO           0

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
 /*! Iterator type for iteration over all high resolution debounce timers */
typedef struct Dem_Cfg_ComplexIterType_s Dem_Satellite_DebounceHiResIterType;
/*! Iterator type for iteration over all low resolution debounce timers */
typedef struct Dem_Cfg_ComplexIterType_s Dem_Satellite_DebounceLoResIterType;

/*! Type for the current value of the satellite specific low resolution tick timer */
typedef uint8 Dem_Satellite_DebounceLoResTimerType;

/*! Handle of Satellite instances. Valid range [0 .. Dem_Cfg_GlobalSatelliteCount()[ . */
typedef Dem_SatelliteInfoType  Dem_Satellite_IdType;
/*! Handle of Monitors within satellite instances. Valid range [0 .. Dem_Cfg_GetEventCountOfSatelliteInfo(SatelliteId)[ . */
typedef uint16 Dem_Satellite_MonitorIdType;

/*! OS Application type wrapper. The type must be provided by the Os */
typedef Dem_ExtCom_ApplicationType Dem_Satellite_ApplicationType;


#endif /* DEM_SATELLITEIF_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_SatelliteIF_Types.h
 *********************************************************************************************************************/
