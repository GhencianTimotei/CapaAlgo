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
/*!
 *  \addtogroup Dem_Dcm
 *  \{
 *  \file       Dem_Dcm_Types.h
 *  \brief      Diagnostic Event Manager (Dem) Type and Macro definition file
 *  \details
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_DCM_TYPES_H)
#define DEM_DCM_TYPES_H

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
 * \defgroup  Dem_Dcm_ExtendedDataRecord_Value Extended Data Records
 * List of special extended data record values
 * \{
 */
#define DEM_DCM_EXTENDEDDATARECORD_INVALID         (0x00u)     /*! Invalid extended record */
#define DEM_DCM_EXTENDEDDATARECORD_FIRST           (0x01u)     /*! The first valid extended record */
#define DEM_DCM_EXTENDEDDATARECORD_FIRST_OBD       (0x90u)     /*! The first valid OBD extended record */
#define DEM_DCM_EXTENDEDDATARECORD_LAST            (0xEFu)     /*! The last valid extended record */
#define DEM_DCM_EXTENDEDDATARECORD_FIRST_RESERVED  (0xF0u)     /*! The first reserved extended record */
#define DEM_DCM_EXTENDEDDATARECORD_OBD             (0xFEu)     /*! Select all OBD records */
#define DEM_DCM_EXTENDEDDATARECORD_ALL             (0xFFu)     /*! Select all extended records */
/*!
 * \}
 */
 
/*!
 * \defgroup  Dem_Dcm_SnapshotDataRecord_Value Snapshot data Records
 * List of special snapshot data record values
 * \{
 */
#define DEM_DCM_SNAPSHOTDATARECORD_TIMESERIES_FIRST        (0x10u)     /*! The first valid classic time series record */
#define DEM_DCM_SNAPSHOTDATARECORD_TIMESERIES_LAST         (0x4Fu)     /*! The last  valid classic time series record */
#define DEM_DCM_SNAPSHOTDATARECORD_TIMESERIES_FAST_FIRST   (0x10u)     /*! The first valid classic fast time series record */
#define DEM_DCM_SNAPSHOTDATARECORD_TIMESERIES_FAST_LAST    (0x2Fu)     /*! The last  valid classic fast time series record */
#define DEM_DCM_SNAPSHOTDATARECORD_TIMESERIES_NORMAL_FIRST (0x30u)     /*! The first valid classic normal time series record */
#define DEM_DCM_SNAPSHOTDATARECORD_TIMESERIES_NORMAL_LAST  (0x4Fu)     /*! The last  valid classic normal time series record */
#define DEM_DCM_SNAPSHOTDATARECORD_OBD                     (0x00u)     /*! OBD record */
#define DEM_DCM_SNAPSHOTDATARECORD_TIMESERIES_POWERTRAIN   (0x30u)     /*! Powertrain TimeSeries record */
#define DEM_DCM_SNAPSHOTDATARECORD_STANDARD_FIRST          (0x01u)     /*! The first vaild standard snapshot data record */
#define DEM_DCM_SNAPSHOTDATARECORD_STANDARD_LAST           (0xFEu)     /*! The last valid standard snapshot data record */
#define DEM_DCM_SNAPSHOTDATARECORD_ALL                     (0xFFu)     /*! All snapshot data records */
/*!
 * \}
 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#endif /* DEM_DCM_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Dcm_Types.h
 *********************************************************************************************************************/
