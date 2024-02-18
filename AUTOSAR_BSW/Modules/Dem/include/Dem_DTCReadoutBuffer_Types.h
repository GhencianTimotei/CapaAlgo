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
/*! \addtogroup Dem_DTCReadoutBuffer
 *  \{
 *  \file       Dem_DTCReadoutBuffer_Types.h
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

#if !defined (DEM_DTCREADOUTBUFFER_TYPES_H)
#define DEM_DTCREADOUTBUFFER_TYPES_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_Int.h"
#include "Dem_Cfg_Types.h"
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
/*!
 * \defgroup  Dem_DTCReadoutBuffer_HandleType Dem_DTCReadoutBuffer_HandleType
 * \{
 */
/*! This used for DTCReadoutBuffer handles. */
typedef uint8 Dem_DTCReadoutBuffer_HandleType;

/*!
 * \}
 */

/*!
 * \defgroup  Dem_DTCReadoutBuffer_ReadoutBufferDataIndexType Dem_DTCReadoutBuffer_ReadoutBufferDataIndexType
 * \{
 */
/*! This used for DTCReadoutBuffer Memory Entry Indexing. */
typedef uint8 Dem_DTCReadoutBuffer_ReadoutBufferDataIndexType;

/*!
 * \}
 */

/*!
 * \defgroup  Dem_DTCReadoutBuffer_StatusType Dem_DTCReadoutBuffer_StatusType
 * \{
 */
/*! This type is used to encode the result of a DTC selection */
typedef uint8 Dem_DTCReadoutBuffer_StatusType;

/*!
 * \}
 */

/*! Identifies a snapshot source */
typedef enum
{
  Dem_DTCReadoutBuffer_SnapshotSource_Obd,                         /*!< OBD snapshot */
  Dem_DTCReadoutBuffer_SnapshotSource_Srec,                        /*!< Snapshot record source */
  Dem_DTCReadoutBuffer_SnapshotSource_TimeSeries_Fast,             /*!< Classic Time Series source 0x10 <= RecordId <= 0x2F */
  Dem_DTCReadoutBuffer_SnapshotSource_TimeSeries_Normal,           /*!< Classic Time Series source 0x30 <= RecordId <= 0x4F */
  Dem_DTCReadoutBuffer_SnapshotSource_TimeSeries_PowerTrain,       /*!< Time Series Powertrain record source */
  Dem_DTCReadoutBuffer_SnapshotSource_Global,                      /*!< Global Snapshot record source */
  Dem_DTCReadoutBuffer_SnapshotSource_Srec_GreaterThan_0x30,       /*!< Snapshot record source with record numbers greater than 0x30 
                                                                        To be used to continue iteration after processing Time Series Powertrain */
  Dem_DTCReadoutBuffer_SnapshotSource_Invalid                      /*!< Not initialize or end of list identifier */
} Dem_DTCReadoutBuffer_SnapshotSourceType;

/*! Iterator for event list containing list of events which have the record configured.
    This shall be completed when the 0x19-04 for Combined Event Type 2 is implemented */
typedef struct
{
  uint8 Dummy;
} Dem_DTCReadoutBuffer_EventIteratorType;

/*! This iterator shall contain start and end index to the list of freeze frame 
    corresponding to the Combined DTC */
typedef Dem_Cfg_ComplexIterType Dem_DTCReadoutBuffer_RecordNumberIteratorType;

/*!
 * \defgroup  Dem_DTCReadoutBuffer_MemoryEntryIndexValues
 * \{
 */
/*!< Default value indicating which memory entry inside Readout Buffer shall be used. 
     By default for events in non-combined type 2 configurations, the memory entry at 
     index 0x00 shall be used */
#define DEM_DTCREADOUTBUFFER_DATAINDEX_DEFAULT      (Dem_DTCReadoutBuffer_ReadoutBufferDataIndexType)0x00U  

/*!
 * \}
 */

#endif /* DEM_DTCREADOUTBUFFER_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_DTCReadoutBuffer_Types.h
 *********************************************************************************************************************/

