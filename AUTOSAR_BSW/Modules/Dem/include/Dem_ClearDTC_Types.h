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
/*! \addtogroup Dem_ClearDTC
 *  \{
 *  \file       Dem_ClearDTC_Types.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Public types of ClearDTC subcomponent
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_CLEARDTC_TYPES_H)
#define DEM_CLEARDTC_TYPES_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_Int.h"
#include "Dem_DTCSelector_Types.h"
/* ------------------------------------------------------------------------- */


/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/
#define DEM_CLEARDTC_HANDLE_INVALID              0xffU     /*!< Value for an invalid clear DTC handle */

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/*! Type to identify clear a operation handler */
typedef uint8 Dem_ClearDTC_HandleType;

/*!
 * \defgroup  Dem_ClearDTC_StatusType Dem_ClearDTC_StatusType
 * \{
 */
/*! Type to encode the state of a clear operation */
typedef uint8 Dem_ClearDTC_StatusType;
#define DEM_CLEARDTC_STATUS_IDLE                 0u  /*!< No clear operation in progress */
#define DEM_CLEARDTC_STATUS_PENDING              1u  /*!< Currently clearing of DTCs is in progress */
#define DEM_CLEARDTC_STATUS_DONE                 2u  /*!< ClearDTC has finished sucessfully */
#define DEM_CLEARDTC_STATUS_FAILED               3u  /*!< ClearDTC has not finished sucessfully */
#define DEM_CLEARDTC_STATUS_NV_ERROR             4u  /*!< NV write error during ClearDTC */

/*!
 * \}
 */

/*! Type to store the state of a clear operation */
struct Dem_ClearDTC_DataType_s
{
  Dem_ClearDTC_StatusType ClearDTCStatus;        /*!< The status of the clear operation */
  Dem_DTCSelector_HandleType DTCSelector;
};

/*! Type for the state of a clear operation */
typedef struct Dem_ClearDTC_DataType_s Dem_ClearDTC_DataType;

#endif /* DEM_CLEARDTC_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_ClearDTC_Types.h
 *********************************************************************************************************************/
