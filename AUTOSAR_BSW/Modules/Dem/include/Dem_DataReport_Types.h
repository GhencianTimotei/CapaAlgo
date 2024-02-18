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
/*! \addtogroup Dem_DataReport
 *  \{
 *  \file       Dem_DataReport_Types.h
 *  \brief      Diagnostic Event Manager (Dem) header file
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

#if !defined (DEM_DATAREPORT_TYPES_H)
#define DEM_DATAREPORT_TYPES_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_Int.h"
#include "Dem_Data_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/
/*! Data byte value substituted when callbacks fail to retrieve data */
#define DEM_DATAREPORT_INVALID_DATA_PATTERN            (0xffU)

/*! Source from where OBDII FreezeFrame shall be copied */
#define DEM_DATAREPORT_SOURCE_OBDII_FF_BUFFER            (0x00U)  /*!< Copy data from OBDII FreezeFrame buffer */
#define DEM_DATAREPORT_SOURCE_OBDII_FF_READOUTBUFFER     (0x01U)  /*!< Copy data from ReadoutBuffer */

/* Size of time series sequential did header */
#define DEM_DATAREPORT_TIMESERIES_SEQUENTIALDID_HEADERSIZE             (7u)
/* Magic number to indicate beginning of a sequential DID in time series powertrain response */
#define DEM_DATAREPORT_TIMESERIES_ENTRYMANAGER_MAGICNUMBER             (0xDCFFu)

/*!
 * \defgroup  Dem_DataReportIF_DataElementType Macros encoding data element kind
 * \{
 */
#define DEM_DATAREPORT_DATAELEMENT_INTERNAL               (0x00U)  /*!< Internally calculated data element */
#define DEM_DATAREPORT_DATAELEMENT_EXTERNAL               (0x01U)  /*!< Externally retrieved data element */
#define DEM_DATAREPORT_DATAELEMENT_INVALID                (0xffU)  /*!< Invalid data element kind */
/*!
 * \}
 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/*! Union Type for OBD FreezeFrame buffer and OBD ReadOutBuffer */
union Dem_DataReport_BufferIndex
{                                                                                                                                /* PRQA S 0750 */ /* MD_MSR_Union */
  Dem_DTCReadoutBuffer_HandleType  ReadoutBufferId;        /*!< Index to OBD ReadOutBuffer */           
  uint8                            FreezeFrameIndex;       /*!< Index to OBD FreezeFrame buffer */  
};

/*! Index Type for OBD FreezeFrame buffer and OBD ReadOutBuffer */
typedef union Dem_DataReport_BufferIndex Dem_DataReport_BufferIndexType;

/*! Structure for basic DID data copy */
struct Dem_DataReport_DidCopyInfoBaseType_s
{
  Dem_Data_DestinationBufferPtrType          DestinationBuffer; /*!< destination buffer context */
  Dem_EventIdType                            EventId;           /*!< EventId for which data is collected */
};

/*! Type for basic DID data copy */
typedef struct Dem_DataReport_DidCopyInfoBaseType_s Dem_DataReport_DidCopyInfoBaseType;
/*! Pointer to type for DID data copy */
typedef P2VAR(Dem_DataReport_DidCopyInfoBaseType, TYPEDEF, AUTOMATIC) Dem_DataReport_DidCopyInfoBasePtrType;
/*! Non-writable pointer to type for DID data copy */
typedef P2CONST(Dem_DataReport_DidCopyInfoBaseType, TYPEDEF, AUTOMATIC) Dem_DataReport_ConstDidCopyInfoBasePtrType;


/*! Structure for DID data copy */
struct Dem_DataReport_DidCopyInfoType_s
{
  Dem_DataReport_DidCopyInfoBaseType      Base;              /*!< Basic information for DID data copy */
  Dem_Cfg_MemoryEntryHandleType              MemoryEntryId;     /*!< Id of memory entry holding the DTC data */
  Dem_Cfg_ReadoutMemIndeCounterPtrType       MemIndeCounterPtr; /*!< Pointer to readout buffer copy of the event memory
                                                                  indepedent counter for Dcm requests or NULL_PTR for 
                                                                  Swc requests*/
};

/*! Structure for DID data read */
struct Dem_DataReport_DidSourceBufferReadInfoType_s
{
  Dem_ConstSharedDataPtrType                 SourceBuffer; /*!< source buffer providing the DID data */
  uint16                                     ReadIndex;    /*!< Current read index from the source buffer */
};

/*! Structure containing meta information about the TimeSeries SRec for DID data readout */
typedef struct Dem_DataReport_PowertrainTimeSeriesInfoType_s {
  uint16 SamplingRate;                /*!< Sampling rate of the DID */
  uint8  NumberOfConfiguredSamples;   /*!< Number of configured DID samples */
  uint8  NumberOfNotStoredSamples;    /*!< Number of configured DID samples which are not stored*/
} Dem_DataReport_PowertrainTimeSeriesInfoType;

/*! Type for DID data copy */
typedef struct Dem_DataReport_DidCopyInfoType_s Dem_DataReport_DidCopyInfoType;
/*! Pointer to type for DID data copy */
typedef P2VAR(Dem_DataReport_DidCopyInfoType, TYPEDEF, AUTOMATIC) Dem_DataReport_DidCopyInfoPtrType;
/*! Non-writable pointer to type for DID data copy */
typedef P2CONST(Dem_DataReport_DidCopyInfoType, TYPEDEF, AUTOMATIC) Dem_DataReport_ConstDidCopyInfoPtrType;

/*! Type for DID data source read */
typedef struct Dem_DataReport_DidSourceBufferReadInfoType_s Dem_DataReport_DidSourceBufferReadInfoType;
/*! Pointer to type for DID data source read */
typedef P2VAR(Dem_DataReport_DidSourceBufferReadInfoType, TYPEDEF, AUTOMATIC)
  Dem_DataReport_DidSourceBufferReadInfoPtrType;
/*! Non-writable pointer to type for DID data source read */
typedef P2CONST(Dem_DataReport_DidSourceBufferReadInfoType, TYPEDEF, AUTOMATIC)
  Dem_DataReport_ConstDidSourceBufferReadInfoPtrType;

#endif /* DEM_DATAREPORT_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_DataReport_Types.h
 *********************************************************************************************************************/
