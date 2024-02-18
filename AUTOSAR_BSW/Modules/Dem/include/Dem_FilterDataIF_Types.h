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
/*! \addtogroup Dem_FilterDataIF
 *  \{
 *  \file       Dem_FilterDataIF_Types.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Public types of FilterDataIF subcomponent
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_FILTERDATAIF_TYPES_H)
#define DEM_FILTERDATAIF_TYPES_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_Int.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*! Number of bitfields in pre client in Dem_Cfg_ReportedEventsOfFilter */
#define DEM_BITFIELDS_IN_REPORTEDEVENTBUFFER     DEM_CFG_GLOBAL_PROCESSORWORDS_PER_REPORTEDEVENTSTYPE

/*!
 * \defgroup  Dem_FilterData_Filter Macros encoding filter type
 * \{
 */
#define DEM_FILTERDATA_FILTER_INIT               0u  /*!< Initialization value */
#define DEM_FILTERDATA_FILTER_DTC                1u  /*!< A filter for DTCs was set up */
#define DEM_FILTERDATA_FILTER_J1939DTCLAMP       2u  /*!< A filter for J1939 DTCs with lamp status was set up */
#define DEM_FILTERDATA_FILTER_J1939DTC           3u  /*!< A filter for J1939 DTCs was set up */
/*!
 * \}
 */

/*!
 * \defgroup  Dem_FilterData_J1939Filter Macros encoding DTC status filter types for J1939Dcm filter requests
 * \{
 */
#define DEM_FILTERDATA_J1939FILTER_ACTIVE               (1U)  /*!< Filter active DTCs */
#define DEM_FILTERDATA_J1939FILTER_PREVIOUSLY_ACTIVE    (2U)  /*!< Filter previously active DTCs */
#define DEM_FILTERDATA_J1939FILTER_PENDING              (3U)  /*!< Filter pending DTCs */
#define DEM_FILTERDATA_J1939FILTER_CURRENTLY_ACTIVE     (4U)  /*!< Filter currently active DTCs */
/*!
 * \}
 */


/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/


/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/*! Type is used for FilterData handles. */
typedef uint8 Dem_FilterData_HandleType;

/*! Type of used filter, see Dem_FilterData_Filter for possible values */
typedef uint8 Dem_FilterData_FilterType;

/*! Function pointer type for event filter functions */
typedef P2FUNC(Dem_EventIdType, DEM_CODE, Dem_FilterData_FuncPtrType) (
  Dem_FilterData_HandleType FilterId
  );

/*! Filtering strategy for DTC filtering */
enum Dem_FilterData_DTCFilteringStrategy
{
  Dem_FilterData_Invalid = 0,                         /*!< Invalid filtering */
  Dem_FilterData_FilterChronological,                 /*!< Chronological filtering */
  Dem_FilterData_FilterEventBased,                    /*!< Non-ordered filtering */
  Dem_FilterData_FilterEventBased_PermanentMemory,    /*!< Non-ordered filtering in permanent memory */  
  Dem_FilterData_FilterEventBased_ReadinessGroup,     /*!< Non-ordered filtering by readiness group */
  Dem_FilterData_FilterEventBased_ExtendendDataRecord /*!< Non-ordered filtering by extended data record */
};

/*! Filtering strategy data type for DTC filtering */
typedef enum Dem_FilterData_DTCFilteringStrategy Dem_FilterData_DTCFilteringStrategyType;


struct Dem_FilterData_ResultType_s
{
  uint32 DTC;
  sint8 FDC;
  uint8 DTCStatus;
  Dem_DTCSeverityType Severity;
  uint8 FunctionalUnit;
  uint8 OccurrenceCounter;
  Dem_J1939DcmLampStatusType LampStatus;
};
  
typedef struct Dem_FilterData_ResultType_s Dem_FilterData_ResultType;



#endif /* DEM_FILTERDATAIF_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_FilterDataIF_Types.h
 *********************************************************************************************************************/
