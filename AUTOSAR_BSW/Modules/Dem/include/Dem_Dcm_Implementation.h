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
 *  \file       Dem_Dcm_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) Implementation file
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

#if !defined (DEM_DCM_IMPLEMENTATION_H)
#define DEM_DCM_IMPLEMENTATION_H

/* ********************************************************************************************************************
 *  GLOBAL MISRA JUSTIFICATIONS
 *********************************************************************************************************************/
/* PRQA S 2880 EOF */ /* MD_DEM_2.1_UNREACHABLE_STATEMENT */
/* PRQA S 2982 EOF */ /* MD_DEM_2982 */
/* PRQA S 2983 EOF */ /* MD_DEM_2983 */
/* PRQA S 2985 EOF */ /* MD_DEM_2985 */
/* PRQA S 2986 EOF */ /* MD_DEM_2986 */
/* PRQA S 2987 EOF */ /* MD_DEM_2987 */
/* PRQA S 2991 EOF */ /* MD_DEM_2991 */
/* PRQA S 2992 EOF */ /* MD_DEM_2992 */
/* PRQA S 2995 EOF */ /* MD_DEM_2995 */
/* PRQA S 2996 EOF */ /* MD_DEM_2996 */
/* PRQA S 0759 EOF */ /* MD_MSR_Union */

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_Dcm_Interface.h"

/* Includes to access public functions belonging to other (top level)/ (logical)/- units to be used by this Unit */
/* ------------------------------------------------------------------------- */
#include "Dem_Infrastructure_Interface.h"
#include "Dem_FaultMemory_Interface.h"
#include "Dem_Core_Interface.h"
#include "Dem_Client_Interface.h"
#include "Dem_DiagnosticObserver_Interface.h"
#include "Dem_DataReport_Interface.h"
#include "Dem_DTCReadoutBuffer_Interface.h"


/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*! Filename declaration */
#define DEM_DCM_IMPLEMENTATION_FILENAME "Dem_Dcm_Implementation.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/


/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_Dcm_Private Private Methods
 * \{
 */



# if ((DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 * Dem_Dcm_SRec_ReadNextRecord_CombinedDTC
 *****************************************************************************/
/*!
 * \brief         Validates the request to copy snapshot record in UDS format
 *                and invokes the relevant functions to copy data to the given 
 *                buffer.
 *
 * \details       Validates the request to copy snapshot record in UDS format
 *                and invokes the relevant functions to copy data to the given 
 *                buffer.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 * \param[in,out] DestinationBuffer
 *                Pointer to destination buffer structure
 *
 * \return        DEM_NO_SUCH_ELEMENT
 *                Selection function is not called.
 *
 * \return        DEM_BUFFER_TOO_SMALL
 *                provided buffer size too small.
 *
 * \return        DEM_NO_SUCH_ELEMENT
 *                Record number is not supported by configuration and
 *                therefore invalid
 *
 * \pre           Function shall be invoked only when a DTC supporting event
 *                combination type 2 has been selected.
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *                && DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ClientIds.
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_SRec_ReadNextRecord_CombinedDTC(
  CONST(uint8, AUTOMATIC) ClientId,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  );
#endif


# if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_Dcm_SRec_ReadNextRecord_NormalEvent
 *****************************************************************************/
/*!
 * \brief         Validates the request to get an extended data record in UDS
 *                format, and copies the data.
 *
 * \details       Copies data into the given buffer.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 * \param[in,out] DestinationBuffer
 *                Pointer to destination buffer structure
 *
 * \return        DEM_NO_SUCH_ELEMENT
 *                Selection function is not called.
 *
 * \return        DEM_BUFFER_TOO_SMALL
 *                provided buffer size too small.
 *
 * \return        DEM_PENDING: The requested value is calculated
 *                asynchronously and currently not available. The
 *                caller can retry later.
 *
 * \return        DEM_NO_SUCH_ELEMENT
 *                Record number is not supported by configuration and
 *                therefore invalid
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *              
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ClientIds.
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_SRec_ReadNextRecord_NormalEvent(
  CONST(uint8, AUTOMATIC) ClientId,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  );
#endif


#if ((DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 * Dem_Dcm_SRec_SelectFirstSource_CombinedEvent
 *****************************************************************************/
/*!
 * \brief         Select the first snapshot record source for a combined DTC
 *
 * \details       Select the first snapshot record source for a combined DTC
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 *
 * \param[in]     RecordNumber
 *                The record number to select
 *
 * \pre           -
 * \config        ((DEM_CFG_SUPPORT_DCM == STD_ON) 
 *                && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)) 
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) 
Dem_Dcm_SRec_SelectFirstSource_CombinedEvent(
  CONST(uint8, AUTOMATIC) ClientId,
  CONST(uint8, AUTOMATIC) RecordNumber
  );
#endif


#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_Dcm_SRec_SelectFirstSource_NormalEvent
 *****************************************************************************/
/*!
 * \brief         Select the first snapshot record source
 *
 * \details       Select the first snapshot record source
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 *
 * \param[in]     RecordNumber
 *                The record number to select
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) 
Dem_Dcm_SRec_SelectFirstSource_NormalEvent(
  CONST(uint8, AUTOMATIC) ClientId,
  CONST(uint8, AUTOMATIC) RecordNumber
  );
#endif


#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_Dcm_SRec_GetSize_NormalEvent
 *****************************************************************************/
/*!
 * \brief         Get the size of one or all formatted snapshot record() 
 *                stored for a DTC (19 04).
 *
 * \details       Get the size of one or all formatted snapshot record() 
 *                stored for a DTC (19 04).
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 * \param[out]    SizeOfFreezeFrame
 *                Pointer to receive the size in bytes
 *
 * \return        E_OK
 *                The requested data was returned
 * \return        E_NOT_OK
 *                Selection function is not called.
 * \return        DEM_NO_SUCH_ELEMENT
 *                The requested record is not available
 * \return        DEM_PENDING
 *                Not used by this implementation
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   FALSE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_SRec_GetSize_NormalEvent(
  CONST(uint8, AUTOMATIC)  ClientId,
  CONSTP2VAR(uint16, AUTOMATIC, DEM_DCM_DATA)  SizeOfFreezeFrame
  );
#endif


#if ((DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_SRECS == STD_ON) \
    && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 * Dem_Dcm_SRec_GetSize_SingleRecordCombinedEvent
 *****************************************************************************/
/*!
 * \brief         Calculates the size of a snapshot record belonging
 *                to a combined DTC
 *
 * \details       Calculates the size of a snapshot record belonging
 *                to a combined DTC
 *
 * \param[in]     ReadoutBufferId
 *                Unique handle of the readout buffer
 * \param[in]     RecordNumber
 *                Snapshot record number
 * \param[out]    SizeOfFreezeFrame
 *                Number of bytes.
 *
 * \return        E_OK
 *                Data was found and returned
 * \return        DEM_NO_SUCH_ELEMENT
 *                The requested record is not available
 *
 * \pre           A memory entry has to be locked for Dcm readout
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON &&
 *                DEM_CFG_SUPPORT_SRECS == STD_ON &&
 *                DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_SRec_GetSize_SingleRecordCombinedEvent(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(uint8, AUTOMATIC)  RecordNumber,
  CONSTP2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  SizeOfFreezeFrame
  );
#endif


#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) \
  &&  (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON) \
  &&  ( (DEM_CFG_SUPPORT_SRECS == STD_ON) \
     || ((DEM_CFG_SUPPORT_OBDII == STD_ON) && (DEM_CFG_SUPPORT_OBDII_FREEZEFRAME_IN_SVC19 == STD_ON))))
/* ****************************************************************************
 * Dem_Dcm_SRec_CalculateSize_AllCombinedEvent
 *****************************************************************************/
/*!
 * \brief         Calculates the size of all snapshot records belonging to a 
 *                combined DTC.
 *
 * \details       Calculates the size of all snapshot records belonging to a 
 *                combined DTC .i.e. the sum of all snapshot records belonging
 *                to each subevent of the combined DTC.
 *
 * \param[in]     ReadoutBufferId
 *                Unique handle of the readout buffer
 * \param[out]    SizeOfFreezeFrame
 *                Number of bytes.
 *
 * \return        E_OK
 *                Data was found and returned
 * \return        DEM_NO_SUCH_ELEMENT
 *                No snapshot records available
 *
 * \pre           The relevant subevent memory entries has to be locked for 
 *                Dcm readout
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON &&
 *                DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON
 *                ( DEM_CFG_SUPPORT_SRECS == STD_ON ||
 *                ((DEM_CFG_SUPPORT_OBDII == STD_ON) && (DEM_CFG_SUPPORT_OBDII_FREEZEFRAME_IN_SVC19 == STD_ON)))
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_SRec_CalculateSize_AllCombinedEvent(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONSTP2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  SizeOfFreezeFrame
  );
#endif


#if ((DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 * Dem_Dcm_SRec_GetSize_CombinedEvent
 *****************************************************************************/
/*!
 * \brief         Get the size of one or all formatted snapshot record() 
 *                stored for a combined DTC (19 04).
 *
 * \details       Get the size of one or all formatted snapshot record() 
 *                stored for a combined DTC (19 04).
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 * \param[out]    SizeOfFreezeFrame
 *                Pointer to receive the size in bytes
 *
 * \return        E_OK
 *                The requested data was returned
 * \return        DEM_NO_SUCH_ELEMENT
 *                The requested record is not available.
 *
 * \pre           -
 * \config        (DEM_CFG_SUPPORT_DCM == STD_ON) &&
 *                (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   FALSE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_SRec_GetSize_CombinedEvent(
  CONST(uint8, AUTOMATIC)  ClientId,
  CONSTP2VAR(uint16, AUTOMATIC, DEM_DCM_DATA)  SizeOfFreezeFrame                                                                 /* PRQA S 3673 */ /* MD_DEM_8.13_fp */
  );
#endif


#if ((DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_SRECS == STD_ON)\
    && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 * Dem_Dcm_SRec_CopySRec_CombinedSubEvent
 *****************************************************************************/
/*!
 * \brief         Copies the requested snapshot record from a selected subevent 
 *                to the destination buffer.
 *
 * \details       Copies the requested snapshot record from a selected subevent 
 *                to the destination buffer. Subevent memory entry is identified
 *                by the index to the readout buffer array.
 *
 * \param[in]     ReadoutBufferId
 *                Unique handle of the readout buffer
 * \param[in]     ReadoutBufferDataIndex
 *                Index to ReadoutBufferData in ReadoutBuffer
 * \param[in,out] DestinationBuffer
 *                Pointer to DestinationBuffer structure
 *
 * \pre           A DTC belonging to combined group type 2 has been selected
 *                and copied to readout buffer
 * 
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON &&
 *                DEM_CFG_SUPPORT_SRECS == STD_ON &&
 *                DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ReadoutBufferIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Dcm_SRec_CopySRec_CombinedSubEvent(
  CONST(uint8, AUTOMATIC) SRecId,
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(Dem_DTCReadoutBuffer_ReadoutBufferDataIndexType, AUTOMATIC)  ReadoutBufferDataIndex,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  );
#endif


#if ((DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_SRECS == STD_ON)\
    && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 * Dem_Dcm_SRec_CopySRec_CombinedDTC
 *****************************************************************************/
/*!
 * \brief         Reads the next snapshot record belonging to a combined DTC
 *                based on the snapshot record selection.
 *
 * \details       Reads the next snapshot record belonging to a combined DTC
 *                based on the snapshot record selection.
 *
 * \param[in]     SRecId
 *                Snapshot Record Identifier to be copied
 * \param[in]     SnapshotHeaderBitMaskIndex
 *                Index pointing to position of SRecId inside the DTC specific
 *                Record Number list
 * \param[in]     ReadoutBufferId
 *                Unique handle of the readout buffer
 * \param[in,out] DestinationBuffer
 *                Pointer to DestinationBuffer structure
 *
 * \return        DEM_BUFFER_TOO_SMALL
 *                Provided buffer size too small.
 * \return        E_OK
 *                Data was copied successfully.
 *
 * \pre           A DTC belonging to combined group type 2 has been selected
 *                and copied to readout buffer
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON &&
 *                DEM_CFG_SUPPORT_SRECS == STD_ON &&
 *                DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ReadoutBufferIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_SRec_CopySRec_CombinedDTC(
  CONST(uint8, AUTOMATIC) SRecId,
  CONST(uint8, AUTOMATIC) SnapshotHeaderBitMaskIndex,
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  );
#endif


#if ((DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_SRECS == STD_ON)\
    && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 * Dem_Dcm_ReadNextSRec_CombinedDTC
 *****************************************************************************/
/*!
 * \brief         Reads the next snapshot record belonging to a combined DTC
 *                based on the snapshot record selection.
 *
 * \details       Reads the next snapshot record belonging to a combined DTC
 *                based on the snapshot record selection.
 *
 * \param[in]     ReadoutBufferId
 *                Unique handle of the readout buffer
 * \param[in,out] DestinationBuffer
 *                Pointer to DestinationBuffer structure
 *
 * \return        DEM_BUFFER_TOO_SMALL
 *                Provided buffer size too small
 * \return        DEM_NO_SUCH_ELEMENT
 *                Record number is not supported by configuration and
 *                therefore invalid
 * \return        E_OK
 *                Record was copied successfully
 *
 * \pre           A DTC belonging to combined group type 2 has been selected
 *                and copied to readout buffer
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON &&
 *                DEM_CFG_SUPPORT_SRECS == STD_ON &&
 *                DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ReadoutBufferIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_ReadNextSRec_CombinedDTC(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  );
#endif


# if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_Dcm_SRec_TestRecordMatch
 *****************************************************************************/
/*!
 * \brief         Test whether filter for snapshot record(s) matches
 *
 * \details       Return whether the given RecordNumber is accepted by the filter
 *
 * \param[in]     ReadoutBufferId
 *                Unique handle of the readout buffer
 * \param[in]     RecordNumber
 *                Snapshot data record number
 *
 * \return        TRUE
 *                The filter matches
 *
 * \return        FALSE
 *                The filter does not match
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE) 
Dem_Dcm_SRec_TestRecordMatch(
 CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
 CONST(uint8, AUTOMATIC) RecordNumber
  );
#endif


# if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_Dcm_SRec_InitSnapshotIterator
 *****************************************************************************/
/*!
 * \brief         Initializes the given snapshot iterator
 *
 * \details       Initializes the given snapshot iterator depending on the
 *                selected source.
 *
 * \param[in]     ReadoutBufferId
 *                Unique handle of the readout buffer
 * \param[in]     ReadoutBufferDataIndex
 *                Index to ReadoutBufferData inside the ReadoutBuffer
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ReadoutBufferIds
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE) 
Dem_Dcm_SRec_InitSnapshotIterator(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(Dem_DTCReadoutBuffer_ReadoutBufferDataIndexType, AUTOMATIC)  ReadoutBufferDataIndex
  );
#endif


# if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_Dcm_SRec_SelectNextSource
 *****************************************************************************/
/*!
 * \brief         Select the next snapshot record source
 *
 * \details       Move the source iterater to the next source depending
 *                on the selected record.
 *
 * \param[in]     ReadoutBufferId
 *                Unique handle of the readout buffer
 *
 * \return        E_OK
 *                The next data source was selected
 * \return        DEM_NO_SUCH_ELEMENT
 *                No data source selected (end of iteration)
 *
 * \pre           -
 * \config        (DEM_CFG_SUPPORT_SRECS == STD_ON)
 *                 || (DEM_CFG_SUPPORT_OBDII == STD_ON)
 *                 || (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
 *                 || (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ReadoutBufferIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE) 
Dem_Dcm_SRec_SelectNextSource(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_Dcm_SRec_ReadNextRecord_Obd
 *****************************************************************************/
/*!
 * \brief         Reads the OBD freeze frame
 *
 * \details       Reads the OBD freeze frame
 *
 * \param[in]     ReadoutBufferId
 *                Unique handle of the readout buffer
 * \param[in,out] DestinationBuffer
 *                Pointer to a DestinationBuffer structure
 *
 * \return        E_NOT_OK
 *                Selection function is not called.
 * \return        DEM_BUFFER_TOO_SMALL
 *                Provided buffer size too small.
 * \return        DEM_NO_SUCH_ELEMENT
 *                Record number is not supported by configuration and
 *                therefore invalid
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ReadoutBufferIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_SRec_ReadNextRecord_Obd(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  );
#endif


# if ((DEM_CFG_SUPPORT_DCM == STD_ON) \
  && (DEM_FEATURE_NEED_TIME_SERIES == STD_ON) \
  && (DEM_CFG_SUPPORT_TIME_SERIES_POWERTRAIN == STD_OFF))
/* ****************************************************************************
 * Dem_Dcm_SRec_ReadNextRecord_TimeSeriesNormal
 *****************************************************************************/
/*!
 * \brief         Reads a time series snapshot record
 *
 * \details       Reads a time series snapshot record
 *
 * \param[in]     ReadoutBufferId
 *                Unique handle of the readout buffer
 * \param[in,out] DestinationBuffer
 *                Pointer to DestinationBuffer structure
 *
 * \return        E_NOT_OK
 *                Selection function is not called.
 * \return        DEM_BUFFER_TOO_SMALL
 *                Provided buffer size too small.
 * \return        DEM_NO_SUCH_ELEMENT
 *                Record number is not supported by configuration and
 *                therefore invalid
 *
 * \pre           -
 * \config        ((DEM_CFG_SUPPORT_DCM == STD_ON) 
 *                 && (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
 *                 && (DEM_CFG_SUPPORT_TIME_SERIES_POWERTRAIN == STD_OFF))
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ReadoutBufferIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_SRec_ReadNextRecord_TimeSeriesNormal(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
* Dem_Dcm_SRec_ReadNextRecord_TimeSeriesPowertrain
*****************************************************************************/
/*!
* \brief         Reads a time series powertrain snapshot record
*
* \details       Reads a time series powertrain snapshot record and writes 
*                DIDs in the required packet structure to the output buffer.
*
* \param[in]     ReadoutBufferId
*                Unique handle of the readout buffer
* \param[in,out] DestinationBuffer
*                Pointer to DestinationBuffer structure
*
* \return        E_OK
*                Data was copied to buffer (if available).
* \return        DEM_BUFFER_TOO_SMALL
*                Provided buffer size too small.
* \return        DEM_NO_SUCH_ELEMENT
*                Record number is not supported by configuration and
*                therefore invalid
*
* \pre           -
* \config        DEM_CFG_SUPPORT_DCM == STD_ON
*
* \context       TASK|ISR2
* \synchronous   TRUE
* \reentrant     TRUE for different ReadoutBufferIds
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_SRec_ReadNextRecord_TimeSeriesPowertrain(
  Dem_DTCReadoutBuffer_HandleType ReadoutBufferId,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  );
#endif

# if ((DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON))
/* ****************************************************************************
 * Dem_Dcm_SRec_ReadNextRecord_Global
 *****************************************************************************/
/*!
 * \brief         Reads a global snapshot record
 *
 * \details       Reads a global snapshot record
 *
 * \param[in]     ReadoutBufferId
 *                Unique handle of the readout buffer
 * \param[in,out] DestinationBuffer
 *                Pointer to DestinationBuffer structure
 *
 * \return        E_NOT_OK
 *                Selection function is not called.
 * \return        DEM_BUFFER_TOO_SMALL
 *                Provided buffer size too small.
 * \return        DEM_NO_SUCH_ELEMENT
 *                Record number is not supported by configuration and
 *                therefore invalid
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON &&
 *                DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ReadoutBufferIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_SRec_ReadNextRecord_Global(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  );
#endif


# if ((DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_SRECS == STD_ON))
/* ****************************************************************************
 * Dem_Dcm_SRec_ReadNextRecord_Standard
 *****************************************************************************/
/*!
 * \brief         Reads a standard snapshot record
 *
 * \details       Reads a standard snapshot record
 *
 * \param[in]     ReadoutBufferId
 *                Unique handle of the readout buffer
 * \param[in,out] DestinationBuffer
 *                Pointer to DestinationBuffer structure
 *
 * \return        E_NOT_OK
 *                Selection function is not called.
 * \return        DEM_BUFFER_TOO_SMALL
 *                Provided buffer size too small.
 * \return        DEM_NO_SUCH_ELEMENT
 *                Record number is not supported by configuration and
 *                therefore invalid
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON &&
 *                DEM_CFG_SUPPORT_SRECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ReadoutBufferIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_SRec_ReadNextRecord_Standard(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON) \
    && (DEM_FEATURE_NEED_TIME_SERIES == STD_ON) && (DEM_CFG_SUPPORT_TIME_SERIES_POWERTRAIN == STD_OFF) 
/* ****************************************************************************
 * Dem_Dcm_SRec_CalculateSize_TimeSeriesNormal
 *****************************************************************************/
/*!
 * \brief         Calculates the size of a normal time series snapshot record
 *
 * \details       Calculates the size of a normal time series snapshot record
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     RecordNumber
 *                Snapshot record number
 * \param[out]    SizeOfFreezeFrame
 *                Number of bytes.
 *
 * \return        E_OK
 *                Data was found and returned
 * \return        DEM_NO_SUCH_ELEMENT
 *                The requested record is not available
 *
 * \pre           A memory entry has to be locked for Dcm readout
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON &&
 *                DEM_FEATURE_NEED_TIME_SERIES == STD_ON
 *                && DEM_CFG_SUPPORT_TIME_SERIES_POWERTRAIN == STD_OFF
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_SRec_CalculateSize_TimeSeriesNormal(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  RecordNumber,
  CONSTP2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  SizeOfFreezeFrame
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
* Dem_Dcm_SRec_CalculateSize_TimeSeriesPowertrain
*****************************************************************************/
/*!
* \brief         Calculates the size of a powertrain time series snapshot record
*
* \details       Calculates the size of a powertrain time series snapshot record
*
* \param[in]     ReadoutBufferId
*                Index of the ReadoutBuffer
* \param[in]     EventId
*                Unique handle of the Event.
*                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
* \param[out]    SizeOfFreezeFrame
*                Number of bytes.
*
* \return        E_OK
*                Data was found and size returned
* \return        DEM_NO_SUCH_ELEMENT
*                The requested record is not available
*
* \pre           A memory entry has to be locked for Dcm readout
* \config        DEM_CFG_SUPPORT_DCM == STD_ON
*
* \context       TASK|ISR2
* \synchronous   TRUE
* \reentrant     TRUE
*****************************************************************************/
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_SRec_CalculateSize_TimeSeriesPowertrain(
  Dem_DTCReadoutBuffer_HandleType ReadoutBufferId,
  Dem_EventIdType EventId,
  CONSTP2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  SizeOfFreezeFrame
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_SRECS == STD_ON)
/* ****************************************************************************
 * Dem_Dcm_SRec_CalculateSize_SingleRecordNormalEvent
 *****************************************************************************/
/*!
 * \brief         Calculates the size of a standard snapshot record
 *
 * \details       Calculates the size of a standard snapshot record
 *
 * \param[in]     ReadoutBufferId
 *                Unique handle of the readout buffer
 * \param[in]     RecordNumber
 *                Snapshot record number
 * \param[out]    SizeOfFreezeFrame
 *                Number of bytes.
 *
 * \return        E_OK
 *                Data was found and returned
 * \return        DEM_NO_SUCH_ELEMENT
 *                The requested record is not available
 *
 * \pre           A memory entry has to be locked for Dcm readout
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON &&
 *                DEM_CFG_SUPPORT_SRECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_SRec_CalculateSize_SingleRecordNormalEvent(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(uint8, AUTOMATIC)  RecordNumber,
  CONSTP2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  SizeOfFreezeFrame
  );
#endif


#if ((DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_SRECS == STD_ON) \
    && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 * Dem_Dcm_SRec_CalculateSize_SingleRecordCombinedEvent
 *****************************************************************************/
/*!
 * \brief         Calculates the size of a single stored snapshot record belonging
 *                to a combined DTC
 *
 * \details       Calculates the size of a single store snapshot record belonging
 *                to a combined DTC. The function adds up snapshot UDS sizes of
 *                all events which have the respective record stored.
 *
 * \param[in]     ReadoutBufferId
 *                Unique handle of the readout buffer
 * \param[in]     RecordNumber
 *                Snapshot record number
 * \param[in]     SnapshotHeaderBitMaskIndex
 *                Index of the SRec inside the DTC specifc SRec list
 *
 * \return        Accumulated size of stored record Id over all sub-events
 *
 * \pre           A memory entry has to be locked for Dcm readout
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON &&
 *                DEM_CFG_SUPPORT_SRECS == STD_ON &&
 *                DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL FUNC(uint16, DEM_CODE)
Dem_Dcm_SRec_CalculateSize_SingleRecordCombinedEvent(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(uint8, AUTOMATIC)  RecordNumber,
  CONST(uint8, AUTOMATIC)  SnapshotHeaderBitMaskIndex
  );
#endif


#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) \
  && ( (DEM_CFG_SUPPORT_SRECS == STD_ON) \
    || (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON) \
    || (DEM_FEATURE_NEED_TIME_SERIES == STD_ON) \
    || ((DEM_CFG_SUPPORT_OBDII == STD_ON) && (DEM_CFG_SUPPORT_OBDII_FREEZEFRAME_IN_SVC19 == STD_ON)) \
    || (DEM_CFG_SUPPORT_WWHOBD == STD_ON) ) )
/* ****************************************************************************
 * Dem_Dcm_SRec_CalculateSize_AllNormalEvent
 *****************************************************************************/
/*!
 * \brief         Calculates the size of all snapshot records
 *
 * \details       Calculates the size of all snapshot records
 *
 * \param[in]     ReadoutBufferId
 *                Unique handle of the readout buffer
 * \param[out]    SizeOfFreezeFrame
 *                Number of bytes.
 *
 * \return        E_OK
 *                Data was found and returned
 * \return        DEM_NO_SUCH_ELEMENT
 *                No snapshot records available
 *
 * \pre           A memory entry has to be locked for Dcm readout
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON &&
 *                ( DEM_CFG_SUPPORT_SRECS == STD_ON ||
 *                  DEM_FEATURE_NEED_TIME_SERIES == STD_ON ||
 *                  DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON ||
 *                  ((DEM_CFG_SUPPORT_OBDII == STD_ON) && (DEM_CFG_SUPPORT_OBDII_FREEZEFRAME_IN_SVC19 == STD_ON)) ||
 *                  DEM_CFG_SUPPORT_WWHOBD == STD_ON )
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_SRec_CalculateSize_AllNormalEvent(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONSTP2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  SizeOfFreezeFrame
  );
#endif


#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_OBDII == STD_ON) )
/* ****************************************************************************
 * Dem_Dcm_SRec_CopyNextRecord_ObdII
 *****************************************************************************/
/*!
 * \brief         Validates the request to get the OBD-II FreezeFrame in UDS
 *                Format, and copies the data.
 *
 * \details       This function does the necessary validations and eventually
 *                calls Dem_DataReport_ObdIIFreezeFrameCopyUdsData to copy the OBD
 *                freeze frame data.
 *                If errors are detected, the appropriate negative response is
 *                returned.
 *
 * \param[in]     ReadoutBufferId
 *                Unique handle of the readout buffer
 * \param[in,out] DestinationBuffer
 *                Pointer to DestinationBuffer stucture
 *
 * \return        E_OK
 *                Data was found and returned
 * \return        E_NOT_OK
 *                The requested record is not available for EventId
 * \return        DEM_BUFFER_TOO_SMALL
 *                The destination buffer is too small
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON &&
 *                DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_SRec_CopyNextRecord_ObdII(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  );
#endif


#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 * Dem_Dcm_SRec_CopyNextRecord_WwhObd
 *****************************************************************************/
/*!
 * \brief         Validates the request to get the WWH-OBD FreezeFrame in UDS
 *                Format, and copies the data.
 *
 * \details       This function does the necessary validations and eventually
 *                calls Dem_DataReport_WWHOBDFreezeFrameCopyData to copy the WWH-OBD
 *                freeze frame data.
 *                If errors are detected, the appropriate negative response is
 *                returned.
 *
 * \param[in]     ReadoutBufferId
 *                Unique handle of the readout buffer
 * \param[in,out] DestinationBuffer
 *                Pointer to DestinationBuffer structure
 *
 * \return        E_OK
 *                Data was found and returned
 * \return        E_NOT_OK
 *                The requested record is not available for EventId
 * \return        DEM_BUFFER_TOO_SMALL
 *                The destination buffer is too small
 *
 * \pre           A memory entry has to be locked for Dcm readout
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON &&
 *                DEM_CFG_SUPPORT_WWHOBD == STD_ON
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_SRec_CopyNextRecord_WwhObd(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  );
#endif


#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_Dcm_SRec_CalculateSize_ObdII
 *****************************************************************************/
/*!
 * \brief         Calculates the total size of the OBD II freeze frame, when
 *                formatted as UDS snapshot record (19 04)
 *
 * \details       Calculates the total size of the OBD II freeze frame, when
 *                formatted as UDS snapshot record (19 04)
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[out]    SizeOfFreezeFrame
 *                Number of bytes.
 *
 * \return        E_OK
 *                Data was found and returned
 * \return        DEM_NO_SUCH_ELEMENT
 *                The requested record is not available
 *
 * \pre           A memory entry has to be locked for Dcm readout
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_SRec_CalculateSize_ObdII(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONSTP2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  SizeOfFreezeFrame
  );
#endif


#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_Dcm_SRec_CalculateSize_WwhObd
 *****************************************************************************/
/*!
 * \brief         Calculates the total size of the WWH-OBD freeze frame, when
 *                formatted as UDS snapshot record (19 04)
 *
 * \details       Calculates the total size of the WWH-OBD freeze frame, when
 *                formatted as UDS snapshot record (19 04)
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[out]    SizeOfFreezeFrame
 *                Number of bytes.
 *
 * \return        E_OK
 *                Data was found and returned
 * \return        DEM_NO_SUCH_ELEMENT
 *                The requested record is not available
 *
 * \pre           A memory entry has to be locked for Dcm readout
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_SRec_CalculateSize_WwhObd(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONSTP2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  SizeOfFreezeFrame
  );
#endif

/* ****************************************************************************
 * Dem_Dcm_SRec_GetEventTimeSeriesPowertrainUdsSize
 *****************************************************************************/
/*!
 * \brief         Function retrieves the size in bytes of the events time series 
 *                powertrain snapshot data.
 *
 * \details       Function retrieves the size in bytes of the events time series 
 *                powertrain snapshot data. This function considers the custom 
 *                packet structure required for powertrain ECUs (Sum of
 *                sequential DID size, additional header 
 *                structure containing Xn, Ts, Td, Magic Number, SRec Id and 
 *                Number of Sequential Dids. 
 *                
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.               
 *
 * \return        Size in bytes of the events time series powertrain snapshot data. 
 *                Events without configured snapshot return 0.
 *
 * \pre           The EventId referenced event needs atleast one TimeSeries Snapshot assigned.
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Dcm_SRec_GetEventTimeSeriesPowertrainUdsSize(
  Dem_EventIdType  EventId
  );

#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_SRECS == STD_ON) && (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 * Dem_Dcm_TimeSeriesSRecCountOfVirtualBuffer
 *****************************************************************************/
/*!
 * \brief         Counts the number of snapshot records stored in a time series
 *                virtual buffer
 *
 * \details       Counts the number of snapshot records stored in a time series
 *                virtual buffer
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 *
 * \return        Number of time series snapshot records which are readable through
 *                the readout buffer
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON &&
 *                DEM_FEATURE_NEED_TIME_SERIES == STD_ON &&
 *                DEM_CFG_SUPPORT_SRECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Dcm_TimeSeriesSRecCountOfVirtualBuffer(
  Dem_DTCReadoutBuffer_HandleType ReadoutBufferId
  );
#endif

#if (DEM_CFG_SUPPORT_SRECS == STD_ON) && (DEM_FEATURE_NEED_TIME_SERIES == STD_ON) && (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_Dcm_TimeSeriesSRecIsReadableInVirtualBuffer
 *****************************************************************************/
/*!
 * \brief         Tests whether a time series snapshot record is currently readable
 *                in virtual buffer
 *
 * \details       Tests whether a time series snapshot record is currently readable
 *                in virtual buffer
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 * \param[in]     RecordNumber
 *                Snapshot record number
 *
 * \return        TRUE
 *                The record is readable
 * \return        FALSE
 *                The record is not readable
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_SRECS == STD_ON && 
 *                DEM_FEATURE_NEED_TIME_SERIES == STD_ON &&
 *                DEM_CFG_SUPPORT_DCM == STD_ON == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Dcm_TimeSeriesSRecIsReadableInVirtualBuffer(
  Dem_DTCReadoutBuffer_HandleType ReadoutBufferId,
  uint8  RecordNumber
  );
#endif

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/

# if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Dcm_SRec_ReadNextRecord_NormalEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_SRec_ReadNextRecord_NormalEvent(
  CONST(uint8, AUTOMATIC) ClientId,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer                                                         /* PRQA S 3673 */ /* MD_DEM_8.13_fp */
  )
{
  Std_ReturnType lReturnValue;
  boolean lContinue;
  Dem_DTCReadoutBuffer_HandleType lReadoutBufferId;

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DestinationBuffer)                                                                            /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = DEM_NO_SUCH_ELEMENT;
  lContinue = TRUE;
  lReadoutBufferId = Dem_Client_ClientAccess_GetReadoutBuffer(ClientId);

  while (lContinue == TRUE)
  {
    Std_ReturnType lReadNextReturnValue;
    lReadNextReturnValue = DEM_NO_SUCH_ELEMENT;

    switch (Dem_DTCReadoutBuffer_GetSnapshotRecordSource(lReadoutBufferId))
    {
    case Dem_DTCReadoutBuffer_SnapshotSource_Obd:
      if ( (Dem_Cfg_IsWwhObdSupportedInVariant() == TRUE) || (Dem_Dcm_IsObdIIFreezeFrameInService19EnabledInVariant() == TRUE))
      {
        lReadNextReturnValue = Dem_Dcm_SRec_ReadNextRecord_Obd(lReadoutBufferId, DestinationBuffer);                             /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
      }
      break;
    case Dem_DTCReadoutBuffer_SnapshotSource_Srec:
    case Dem_DTCReadoutBuffer_SnapshotSource_Srec_GreaterThan_0x30:
# if (DEM_CFG_SUPPORT_SRECS == STD_ON)
      lReadNextReturnValue = Dem_Dcm_SRec_ReadNextRecord_Standard(lReadoutBufferId, DestinationBuffer);                          /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
# endif
      break;
    case Dem_DTCReadoutBuffer_SnapshotSource_TimeSeries_Normal:
    case Dem_DTCReadoutBuffer_SnapshotSource_TimeSeries_Fast:
# if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON) && (DEM_CFG_SUPPORT_TIME_SERIES_POWERTRAIN == STD_OFF)
      lReadNextReturnValue = Dem_Dcm_SRec_ReadNextRecord_TimeSeriesNormal(lReadoutBufferId, DestinationBuffer);                  /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
# endif
      break;
    case Dem_DTCReadoutBuffer_SnapshotSource_TimeSeries_PowerTrain:
      if (Dem_Memory_TimeSeries_IsPowertrainEnabled() == TRUE)
      {
        lReadNextReturnValue = Dem_Dcm_SRec_ReadNextRecord_TimeSeriesPowertrain(lReadoutBufferId, DestinationBuffer);            /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
      }
      break;
    case Dem_DTCReadoutBuffer_SnapshotSource_Global:
# if (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
      lReadNextReturnValue = Dem_Dcm_SRec_ReadNextRecord_Global(lReadoutBufferId, DestinationBuffer);                            /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
# endif
      break;
    default:                                                                                                                     /* PRQA S 2016 */ /* MD_MSR_EmptyClause */
      /* Dem_DTCReadoutBuffer_SnapshotSource_Invalid */
      break;
    }

    if (lReadNextReturnValue == DEM_NO_SUCH_ELEMENT)
    {
      Std_ReturnType lSelectNextReturnValue;

      lSelectNextReturnValue = Dem_Dcm_SRec_SelectNextSource(lReadoutBufferId);

      if (lSelectNextReturnValue == DEM_NO_SUCH_ELEMENT)
      {
        lReturnValue = lSelectNextReturnValue;
        lContinue = FALSE;
      }
    }
    else
    {
      lReturnValue = lReadNextReturnValue;
      lContinue = FALSE;
    }
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6030, 6050, 6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
#endif

# if ((DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_TYPE2_COMBINATION))
/* ****************************************************************************
 % Dem_Dcm_SRec_ReadNextRecord_CombinedDTC
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_SRec_ReadNextRecord_CombinedDTC(
  CONST(uint8, AUTOMATIC) ClientId,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer                                                         /* PRQA S 3673 */ /* MD_DEM_8.13_fp */
  )
{
  Std_ReturnType lReturnValue;
  boolean lContinue;
  Dem_DTCReadoutBuffer_HandleType lReadoutBufferId;

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DestinationBuffer)                                                                            /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = DEM_NO_SUCH_ELEMENT;
  lContinue = TRUE;
  lReadoutBufferId = Dem_Client_ClientAccess_GetReadoutBuffer(ClientId);

  while (lContinue == TRUE)
  {
    Std_ReturnType lReadNextReturnValue;
    lReadNextReturnValue = DEM_NO_SUCH_ELEMENT;

    switch (Dem_DTCReadoutBuffer_GetSnapshotRecordSource(lReadoutBufferId))
    {
    case Dem_DTCReadoutBuffer_SnapshotSource_Obd:
      if (Dem_Dcm_IsObdIIFreezeFrameInService19EnabledInVariant() == TRUE)
      {
        lReadNextReturnValue = Dem_Dcm_SRec_ReadNextRecord_Obd(lReadoutBufferId, DestinationBuffer);                             /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
      }
      break;
    case Dem_DTCReadoutBuffer_SnapshotSource_Srec:
# if (DEM_CFG_SUPPORT_SRECS == STD_ON)
      lReadNextReturnValue = Dem_Dcm_ReadNextSRec_CombinedDTC(lReadoutBufferId, DestinationBuffer);                              /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
# endif
      break;
    default:                                                                                                                     /* PRQA S 2016 */ /* MD_MSR_EmptyClause */
      /* Currently unsupported containers */
      /* Dem_DTCReadoutBuffer_SnapshotSource_TimeSeries_Normal */
      /* Dem_DTCReadoutBuffer_SnapshotSource_TimeSeries_Fast */
      /* Dem_DTCReadoutBuffer_SnapshotSource_Global */
      /* Dem_DTCReadoutBuffer_SnapshotSource_Invalid */
      break;
    }

    if (lReadNextReturnValue == DEM_NO_SUCH_ELEMENT)
    {
      Std_ReturnType lSelectNextReturnValue;

      lSelectNextReturnValue = Dem_Dcm_SRec_SelectNextSource(lReadoutBufferId);

      if (lSelectNextReturnValue == DEM_NO_SUCH_ELEMENT)
      {
        lReturnValue = lSelectNextReturnValue;
        lContinue = FALSE;
      }
    }
    else
    {
      lReturnValue = lReadNextReturnValue;
      lContinue = FALSE;
    }
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif

#if ((DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 % Dem_Dcm_SRec_SelectFirstSource_CombinedEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Dcm_SRec_SelectFirstSource_CombinedEvent(
  CONST(uint8, AUTOMATIC) ClientId,
  CONST(uint8, AUTOMATIC) RecordNumber
  )
{
  Dem_DTCReadoutBuffer_HandleType lReadoutBufferId;
  Dem_DTCReadoutBuffer_SnapshotSourceType lSource;

  lReadoutBufferId = Dem_Client_ClientAccess_GetReadoutBuffer(ClientId);

  Dem_DTCReadoutBuffer_SelectSnapshotRecord(
    lReadoutBufferId,
    RecordNumber);

  if ( (RecordNumber == DEM_DCM_SNAPSHOTDATARECORD_OBD)
    || (RecordNumber == DEM_DCM_SNAPSHOTDATARECORD_ALL) )
  {
    if (Dem_Dcm_IsObdIIFreezeFrameInService19EnabledInVariant() == TRUE)
    {
      lSource = Dem_DTCReadoutBuffer_SnapshotSource_Obd;
    }
    else
    {
#  if (DEM_CFG_SUPPORT_SRECS == STD_ON)
      if (RecordNumber == DEM_DCM_SNAPSHOTDATARECORD_ALL)
      {
        lSource = Dem_DTCReadoutBuffer_SnapshotSource_Srec;
      }
      else
#  endif
      {
        lSource = Dem_DTCReadoutBuffer_SnapshotSource_Invalid;
      }
    }
  }
  else
  {
# if (DEM_CFG_SUPPORT_SRECS == STD_ON)
    lSource = Dem_DTCReadoutBuffer_SnapshotSource_Srec;
# else
    lSource = Dem_DTCReadoutBuffer_SnapshotSource_Invalid;
# endif
  }

  Dem_DTCReadoutBuffer_SetSnapshotRecordSource(lReadoutBufferId, lSource);

  /* Snapshot source iterator used during readout only for OBDII freeze frames */
  if (Dem_Dcm_IsObdIIFreezeFrameInService19EnabledInVariant() == TRUE)
  {
    if (lSource == Dem_DTCReadoutBuffer_SnapshotSource_Obd)
    {
      Dem_Cfg_ComplexIterType lSourceIterator;

      lSourceIterator = Dem_DTCReadoutBuffer_GetSnapshotSourceIterator(
        lReadoutBufferId,
        DEM_DTCREADOUTBUFFER_DATAINDEX_DEFAULT);

      Dem_Cfg_ComplexIterInit(&lSourceIterator, 0, 1);                                                                           /* SBSW_DEM_POINTER_FORWARD_STACK */

      Dem_DTCReadoutBuffer_SetSnapshotSourceIterator(lReadoutBufferId,
        DEM_DTCREADOUTBUFFER_DATAINDEX_DEFAULT,
        lSourceIterator);
    }
  }

# if (DEM_CFG_SUPPORT_SRECS == STD_ON)
  {
    Dem_DTCReadoutBuffer_RecordNumberIteratorType lReadoutBufferRecordNumberIter;

    Dem_Cfg_DTCFreezeFrameRecordIterInit(&lReadoutBufferRecordNumberIter,                                                        /* SBSW_DEM_CALL_ITERATOR_POINTER */
                                         Dem_Cfg_EventCombinedGroup(Dem_DTCReadoutBuffer_GetMasterEventId(lReadoutBufferId)));
    Dem_DTCReadoutBuffer_SetRecordNumberIterator(lReadoutBufferId, &lReadoutBufferRecordNumberIter);                             /* SBSW_DEM_POINTER_FORWARD_STACK */
  }
# endif
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Dcm_SRec_SelectFirstSource_NormalEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Dcm_SRec_SelectFirstSource_NormalEvent(
  CONST(uint8, AUTOMATIC) ClientId,
  CONST(uint8, AUTOMATIC) RecordNumber
  )
{
  Dem_DTCReadoutBuffer_HandleType lReadoutBufferId;
  Dem_DTCReadoutBuffer_SnapshotSourceType lSource;

  lReadoutBufferId = Dem_Client_ClientAccess_GetReadoutBuffer(ClientId);

  Dem_DTCReadoutBuffer_SelectSnapshotRecord(
    lReadoutBufferId,
    RecordNumber);

  if ( (RecordNumber == DEM_DCM_SNAPSHOTDATARECORD_OBD)
    || (RecordNumber == DEM_DCM_SNAPSHOTDATARECORD_ALL) )
  {
    if ( (Dem_Cfg_IsWwhObdSupportedInVariant() == TRUE) || (Dem_Dcm_IsObdIIFreezeFrameInService19EnabledInVariant() == TRUE))
    {
      lSource = Dem_DTCReadoutBuffer_SnapshotSource_Obd;
    }
    else
    {
      if (RecordNumber == DEM_DCM_SNAPSHOTDATARECORD_ALL)
      {
# if (DEM_CFG_SUPPORT_SRECS_CALCULATED == STD_ON)
        lSource = Dem_DTCReadoutBuffer_SnapshotSource_Srec;
# else
        lSource = Dem_DTCReadoutBuffer_SnapshotSource_Global;
# endif
      }
      else
      {
        lSource = Dem_DTCReadoutBuffer_SnapshotSource_Invalid;
      }
    }
  }
  else
# if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
#  if (DEM_CFG_SUPPORT_TIME_SERIES_POWERTRAIN == STD_OFF)
#   if (DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON)
  if ((RecordNumber >= DEM_DCM_SNAPSHOTDATARECORD_TIMESERIES_FAST_FIRST) && (RecordNumber <= 0x2Fu))
  {
    lSource = Dem_DTCReadoutBuffer_SnapshotSource_TimeSeries_Fast;
  }
  else
#   endif
  if ((RecordNumber >= DEM_DCM_SNAPSHOTDATARECORD_TIMESERIES_NORMAL_FIRST)
    && (RecordNumber <= DEM_DCM_SNAPSHOTDATARECORD_TIMESERIES_NORMAL_LAST))
  {
    lSource = Dem_DTCReadoutBuffer_SnapshotSource_TimeSeries_Normal;
  }
  else
#  else
  if (RecordNumber == DEM_DCM_SNAPSHOTDATARECORD_TIMESERIES_POWERTRAIN)
  {
    lSource = Dem_DTCReadoutBuffer_SnapshotSource_TimeSeries_PowerTrain;
  }
  else
#  endif
# endif
# if (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
  if (RecordNumber == Dem_Cfg_GlobalSRecId())
  {
    lSource = Dem_DTCReadoutBuffer_SnapshotSource_Global;
  }
  else
# endif
  {
# if (DEM_CFG_SUPPORT_SRECS == STD_ON)
    lSource = Dem_DTCReadoutBuffer_SnapshotSource_Srec;
# else
    lSource = Dem_DTCReadoutBuffer_SnapshotSource_Invalid;
# endif
  }

  Dem_DTCReadoutBuffer_SetSnapshotRecordSource(lReadoutBufferId, lSource);

  Dem_Dcm_SRec_InitSnapshotIterator(lReadoutBufferId, DEM_DTCREADOUTBUFFER_DATAINDEX_DEFAULT);
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Dcm_SRec_GetSize_NormalEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_SRec_GetSize_NormalEvent(
  CONST(uint8, AUTOMATIC)  ClientId,
  CONSTP2VAR(uint16, AUTOMATIC, DEM_DCM_DATA)  SizeOfFreezeFrame                                                                 /* PRQA S 3673 */ /* MD_DEM_8.13_fp */
  )
{
  Std_ReturnType lReturnValue;

# if ( (DEM_CFG_SUPPORT_SRECS == STD_ON) \
    || (DEM_CFG_SUPPORT_OBDII_FREEZEFRAME_IN_SVC19 == STD_ON) \
    || (DEM_CFG_SUPPORT_WWHOBD == STD_ON) \
    || (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON) \
    || (DEM_FEATURE_NEED_TIME_SERIES == STD_ON))
  Dem_EventIdType lEventId;                                                                                                      /* PRQA S 3203 */ /* MD_DEM_3203 */
  uint8 lMemoryId;                                                                                                               /* PRQA S 3203 */ /* MD_DEM_3203 */
  uint8 lRecordNumber;
  Dem_DTCReadoutBuffer_HandleType lReadoutBufferId;

  lReadoutBufferId = Dem_Client_ClientAccess_GetReadoutBuffer(ClientId);
  lEventId = Dem_DTCReadoutBuffer_GetEventId(lReadoutBufferId, DEM_DTCREADOUTBUFFER_DATAINDEX_DEFAULT);                          /* PRQA S 3203 */ /* MD_DEM_3203 */
  lMemoryId = Dem_DTCReadoutBuffer_GetMemoryId(lReadoutBufferId);                                                                /* PRQA S 3203 */ /* MD_DEM_3203 */
  lRecordNumber = Dem_DTCReadoutBuffer_GetSnapshotRecordNumber(lReadoutBufferId);

  if (lRecordNumber == 0x00u)
  {
    if (lMemoryId == DEM_CFG_MEMORYID_PRIMARY)
    {
      if (Dem_Dcm_IsObdIIFreezeFrameInService19EnabledInVariant() == TRUE)
      {
        lReturnValue = Dem_Dcm_SRec_CalculateSize_ObdII(lEventId, SizeOfFreezeFrame);                                            /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
      }
      else 
      if (Dem_Cfg_IsWwhObdSupportedInVariant() == TRUE)
      {
        lReturnValue = Dem_Dcm_SRec_CalculateSize_WwhObd(lEventId, SizeOfFreezeFrame);                                           /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
      }
      else
      {
        lReturnValue = DEM_NO_SUCH_ELEMENT;
      }
    }
    else
    {
      lReturnValue = DEM_NO_SUCH_ELEMENT;
    }
  }
  else
#  if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON) && (DEM_CFG_SUPPORT_TIME_SERIES_POWERTRAIN == STD_OFF)
  if ((lRecordNumber >= DEM_DCM_SNAPSHOTDATARECORD_TIMESERIES_FIRST)
      && (lRecordNumber <= DEM_DCM_SNAPSHOTDATARECORD_TIMESERIES_LAST))
  {
    lReturnValue = Dem_Dcm_SRec_CalculateSize_TimeSeriesNormal(lReadoutBufferId, lEventId, lRecordNumber, SizeOfFreezeFrame);    /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }
  else
#   endif
  if ( (Dem_Memory_TimeSeries_IsPowertrainEnabled() == TRUE)
      && (lRecordNumber == DEM_DCM_SNAPSHOTDATARECORD_TIMESERIES_POWERTRAIN))
  {
    lReturnValue = Dem_Dcm_SRec_CalculateSize_TimeSeriesPowertrain(lReadoutBufferId, lEventId, SizeOfFreezeFrame);               /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }
  else
#  if (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
  if (lRecordNumber == Dem_Cfg_GlobalSRecId())
  {
    lReturnValue = E_OK;
    if (Dem_DTCReadoutBuffer_TestGlobalSnapshotStored(
          lReadoutBufferId, DEM_DTCREADOUTBUFFER_DATAINDEX_DEFAULT) == TRUE)
    {
      *SizeOfFreezeFrame = Dem_Cfg_GlobalSRecUdsSize();                                                                          /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    }
    else
    {
      *SizeOfFreezeFrame = 0u;                                                                                                   /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    }
  }
  else
#  endif
  if (lRecordNumber == DEM_DCM_SNAPSHOTDATARECORD_ALL)
  {
    lReturnValue = Dem_Dcm_SRec_CalculateSize_AllNormalEvent(lReadoutBufferId, SizeOfFreezeFrame);                               /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }
  else
#  if (DEM_CFG_SUPPORT_SRECS == STD_ON)
  {
    lReturnValue = Dem_Dcm_SRec_CalculateSize_SingleRecordNormalEvent(lReadoutBufferId, lRecordNumber, SizeOfFreezeFrame);       /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }
#  else
  {
    lReturnValue = DEM_NO_SUCH_ELEMENT;
  }
#  endif
# else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(ClientId)                                                                                     /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(SizeOfFreezeFrame)                                                                            /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = DEM_NO_SUCH_ELEMENT;
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) \
    && (DEM_CFG_SUPPORT_SRECS == STD_ON) \
    && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 % Dem_Dcm_SRec_GetSize_SingleRecordCombinedEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_SRec_GetSize_SingleRecordCombinedEvent(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(uint8, AUTOMATIC)  RecordNumber,
  CONSTP2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  SizeOfFreezeFrame
  )
{
  uint8 lSnapshotHeaderBitMaskIndex;
  Std_ReturnType lReturnValue;
  Dem_EventIdType lMasterEventId;
  Dem_Cfg_CombinedGroupIndexType lCombinedDTCGroup;

  lMasterEventId = Dem_DTCReadoutBuffer_GetMasterEventId(ReadoutBufferId);
  lCombinedDTCGroup = Dem_Cfg_EventCombinedGroup(lMasterEventId);
  lSnapshotHeaderBitMaskIndex = Dem_SnapshotEntry_FindSRecIndexInCombinedDTCSRecList(RecordNumber, lCombinedDTCGroup);

  if ((lSnapshotHeaderBitMaskIndex == DEM_SNAPSHOTENTRY_CONFIGURED_SREC_INDEX_INVALID)
    || (Dem_SnapshotEntry_SRecIsSupportedByAvailableCombinedEvent(lCombinedDTCGroup, RecordNumber) == FALSE))                    /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
  {
    *SizeOfFreezeFrame = 0x00U;                                                                                                  /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    lReturnValue = DEM_NO_SUCH_ELEMENT;
  }
  else
  {
    *SizeOfFreezeFrame = Dem_Dcm_SRec_CalculateSize_SingleRecordCombinedEvent(ReadoutBufferId,                                   /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
                                                                              RecordNumber,
                                                                              lSnapshotHeaderBitMaskIndex);
    lReturnValue = E_OK;
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) \
   && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON) \
   && ( (DEM_CFG_SUPPORT_SRECS == STD_ON) \
     || ((DEM_CFG_SUPPORT_OBDII == STD_ON) && (DEM_CFG_SUPPORT_OBDII_FREEZEFRAME_IN_SVC19 == STD_ON))\
    ) )
/* ****************************************************************************
 % Dem_Dcm_SRec_CalculateSize_AllCombinedEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_SRec_CalculateSize_AllCombinedEvent(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONSTP2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  SizeOfFreezeFrame
  )
{
  Std_ReturnType lReturnValue;
  uint16 lSizeOfFreezeFrame;

  /* Initialize the negative return value */
  lSizeOfFreezeFrame = 0x00U;
  lReturnValue = DEM_NO_SUCH_ELEMENT;

# if (DEM_CFG_SUPPORT_SRECS == STD_ON)
  {
    Dem_EventIdType lEventId;
    Dem_DTCReadoutBuffer_ReadoutBufferDataIndexType lReadoutBufferDataIndex;
    uint8 lNumOccupiedReadoutBufferEntries;
    Dem_Cfg_MemoryEntryHandleType lReadoutBufferMemoryEntryId;
    Dem_DTCReadoutBuffer_RecordNumberIteratorType lRecordNumberIterator;

    lRecordNumberIterator = Dem_DTCReadoutBuffer_GetRecordNumberIterator(ReadoutBufferId);
    if (Dem_Cfg_DTCFreezeFrameRecordIterExists(&lRecordNumberIterator) == TRUE)                                         /* SBSW_DEM_POINTER_FORWARD_STACK */
    {
      lSizeOfFreezeFrame = 0x00U;
      lNumOccupiedReadoutBufferEntries = Dem_DTCReadoutBuffer_GetNumberOfOccupiedSlots(ReadoutBufferId);

      for (lReadoutBufferDataIndex = DEM_DTCREADOUTBUFFER_DATAINDEX_DEFAULT;
           lReadoutBufferDataIndex < lNumOccupiedReadoutBufferEntries;
           lReadoutBufferDataIndex++)
      {
        lReadoutBufferMemoryEntryId = Dem_DTCReadoutBuffer_GetMemoryEntryId(ReadoutBufferId, lReadoutBufferDataIndex);
        lEventId = Dem_DTCReadoutBuffer_GetEventId(ReadoutBufferId, lReadoutBufferDataIndex);
        lSizeOfFreezeFrame += ((uint16)(Dem_SnapshotEntry_GetNumberOfStoredSnapshotRecords(lReadoutBufferMemoryEntryId)
                                          * Dem_Cfg_EventSRecUdsSize(lEventId)));
      }
      lReturnValue = E_OK;
    }
  }
# endif

  if (Dem_Dcm_IsObdIIFreezeFrameInService19EnabledInVariant() == TRUE)
  {
    if (Dem_DTCReadoutBuffer_GetOBDData_IsStored(ReadoutBufferId) == TRUE)
    {
      lSizeOfFreezeFrame += Dem_Cfg_GlobalObdIIFFUdsSize();
    }
    lReturnValue = E_OK;
  }

  *SizeOfFreezeFrame = lSizeOfFreezeFrame;                                                                                       /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if ((DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 % Dem_Dcm_SRec_GetSize_CombinedEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_SRec_GetSize_CombinedEvent(
  CONST(uint8, AUTOMATIC)  ClientId,
  CONSTP2VAR(uint16, AUTOMATIC, DEM_DCM_DATA)  SizeOfFreezeFrame                                                                 /* PRQA S 3673 */ /* MD_DEM_8.13_fp */
  )
{
  Std_ReturnType lReturnValue;

# if ( (DEM_CFG_SUPPORT_SRECS == STD_ON)\
    || ((DEM_CFG_SUPPORT_OBDII == STD_ON) && (DEM_CFG_SUPPORT_OBDII_FREEZEFRAME_IN_SVC19 == STD_ON)))
  uint8 lMemoryId;                                                                                                               /* PRQA S 3203 */ /* MD_DEM_3203 */
  uint8 lRecordNumber;
  Dem_DTCReadoutBuffer_HandleType lReadoutBufferId;

  lReadoutBufferId = Dem_Client_ClientAccess_GetReadoutBuffer(ClientId);
  lMemoryId = Dem_DTCReadoutBuffer_GetMemoryId(lReadoutBufferId);                                                                /* PRQA S 3203 */ /* MD_DEM_3203 */
  lRecordNumber = Dem_DTCReadoutBuffer_GetSnapshotRecordNumber(lReadoutBufferId);

  if (lRecordNumber == 0x00u)
  {
    if (lMemoryId == DEM_CFG_MEMORYID_PRIMARY)
    {
      if (Dem_Dcm_IsObdIIFreezeFrameInService19EnabledInVariant() == TRUE)
      {
        if (Dem_DTCReadoutBuffer_GetOBDData_IsStored(lReadoutBufferId) == TRUE)
        {
          *SizeOfFreezeFrame = Dem_Cfg_GlobalObdIIFFUdsSize();                                                                     /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
        }
        else
        {
          *SizeOfFreezeFrame = 0u;                                                                                                  /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
        }

        lReturnValue = E_OK;
      }
      else
      {
        lReturnValue = DEM_NO_SUCH_ELEMENT;
      }
    }
    else
    {
      lReturnValue = DEM_NO_SUCH_ELEMENT;
    }
  }
  else if (lRecordNumber == DEM_DCM_SNAPSHOTDATARECORD_ALL)
  {
    lReturnValue = Dem_Dcm_SRec_CalculateSize_AllCombinedEvent(lReadoutBufferId, SizeOfFreezeFrame);                             /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }
  else
#  if (DEM_CFG_SUPPORT_SRECS == STD_ON)
  {
    lReturnValue = Dem_Dcm_SRec_GetSize_SingleRecordCombinedEvent(                                                               /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
                     lReadoutBufferId, lRecordNumber, SizeOfFreezeFrame);
  }
#  else
  {
    lReturnValue = DEM_NO_SUCH_ELEMENT;
  }
#  endif
# else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(ClientId)                                                                                     /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(SizeOfFreezeFrame)                                                                            /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = DEM_NO_SUCH_ELEMENT;
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if ((DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_SRECS == STD_ON)\
    && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 % Dem_Dcm_SRec_CopySRec_CombinedSubEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Dcm_SRec_CopySRec_CombinedSubEvent(
  CONST(uint8, AUTOMATIC) SRecId,
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(Dem_DTCReadoutBuffer_ReadoutBufferDataIndexType, AUTOMATIC)  ReadoutBufferDataIndex,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  )
{
  Dem_Cfg_SnapshotEntry_IterType lSnapshotEntryIter;
  Dem_Cfg_SRecIndexType lSRecIndex;

  lSnapshotEntryIter = Dem_DTCReadoutBuffer_GetSnapshotEntryIterator(
                         ReadoutBufferId,
                         ReadoutBufferDataIndex);

  while (Dem_SnapshotEntry_IteratorExists(&lSnapshotEntryIter) == TRUE)                                                          /* SBSW_DEM_POINTER_FORWARD_STACK */
  {
    lSRecIndex = Dem_SnapshotEntry_IteratorGetSnapshotRecordIndex(&lSnapshotEntryIter);                                          /* SBSW_DEM_POINTER_FORWARD_STACK */
    if (SRecId == Dem_Cfg_SRecId(lSRecIndex))
    {
        Dem_Data_WriteDestinationBufferUint8(DestinationBuffer, Dem_Cfg_SRecId(lSRecIndex));                                     /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
        Dem_DataReport_SRecCopyData(DestinationBuffer,                                                                         /* SBSW_DEM_POINTER_DESTINATIONBUFFER_SOURCEBUFFER */
                                      Dem_SnapshotEntry_IteratorGetSnapshotRecordDataConstPtr(&lSnapshotEntryIter),              /* SBSW_DEM_POINTER_FORWARD_STACK */
                                      Dem_DTCReadoutBuffer_GetEventId(ReadoutBufferId, ReadoutBufferDataIndex),
                                      Dem_DTCReadoutBuffer_GetMemoryEntryId(ReadoutBufferId, ReadoutBufferDataIndex),
                                      Dem_DTCReadoutBuffer_GetMemIndependentCounterPtr(ReadoutBufferId));

      break;
    }
    else
    {
      /* otherwise next snapshot record */
    }

    Dem_SnapshotEntry_IteratorNext(&lSnapshotEntryIter);                                                                         /* SBSW_DEM_POINTER_FORWARD_STACK */
  }

  /* Detect an Inconsistent state.
     - Between the snapshot record storage status and DTC record storage status
     - Between DTC record storage status and configuration
  */
  Dem_Internal_AssertContinue(Dem_SnapshotEntry_IteratorExists(&lSnapshotEntryIter), DEM_E_INCONSISTENT_STATE)                   /* SBSW_DEM_POINTER_FORWARD_STACK */

  Dem_SnapshotEntry_IteratorNext(&lSnapshotEntryIter);                                                                           /* SBSW_DEM_POINTER_FORWARD_STACK */
  Dem_DTCReadoutBuffer_SetSnapshotEntryIterator(ReadoutBufferId,
                                                ReadoutBufferDataIndex,
                                                lSnapshotEntryIter);

}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif

#if ((DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_SRECS == STD_ON)\
    && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 % Dem_Dcm_SRec_CopySRec_CombinedDTC
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_SRec_CopySRec_CombinedDTC(
  CONST(uint8, AUTOMATIC) SRecId,
  CONST(uint8, AUTOMATIC)  SnapshotHeaderBitMaskIndex,
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  )
{
  Std_ReturnType lReturnValue;
  Dem_Cfg_CombinedGroupIndexType lCombinedDTCGroupId;

  lCombinedDTCGroupId = Dem_Cfg_EventCombinedGroup(Dem_DTCReadoutBuffer_GetMasterEventId(ReadoutBufferId));
  if (Dem_SnapshotEntry_SRecIsSupportedByAvailableCombinedEvent(lCombinedDTCGroupId, SRecId) == FALSE)
  {
    lReturnValue = DEM_NO_SUCH_ELEMENT;
  }
  else if (DestinationBuffer->BufferSize < Dem_Dcm_SRec_CalculateSize_SingleRecordCombinedEvent(ReadoutBufferId, SRecId, SnapshotHeaderBitMaskIndex))
  { /* Supported record, but the buffer is not large enough for all the data */
    lReturnValue = DEM_BUFFER_TOO_SMALL;
  }
  else
  {
    uint8 lNumOccupiedReadoutBufferEntries;
    Dem_Cfg_MemoryEntryHandleType lReadoutBufferMemoryEntryId;
    Dem_DTCReadoutBuffer_ReadoutBufferDataIndexType ReadoutBufferMemoryIndex;

    ReadoutBufferMemoryIndex = DEM_DTCREADOUTBUFFER_DATAINDEX_DEFAULT;
    lNumOccupiedReadoutBufferEntries = Dem_DTCReadoutBuffer_GetNumberOfOccupiedSlots(ReadoutBufferId);

    for (; ReadoutBufferMemoryIndex < lNumOccupiedReadoutBufferEntries; ReadoutBufferMemoryIndex++)
    {
      lReadoutBufferMemoryEntryId = Dem_DTCReadoutBuffer_GetMemoryEntryId(ReadoutBufferId, ReadoutBufferMemoryIndex);
      if (Dem_SnapshotEntry_GetSRecStorageStatus(SRecId, SnapshotHeaderBitMaskIndex, lReadoutBufferMemoryEntryId) == TRUE)
      {
        Dem_Dcm_SRec_CopySRec_CombinedSubEvent(SRecId, ReadoutBufferId, ReadoutBufferMemoryIndex, DestinationBuffer);            /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
      }
    }
    lReturnValue = E_OK;
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if ((DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_SRECS == STD_ON)\
    && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 % Dem_Dcm_ReadNextSRec_CombinedDTC
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_ReadNextSRec_CombinedDTC(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  )
{
  Std_ReturnType lReturnValue;
  uint8 lRecordNumber;
  Dem_DTCReadoutBuffer_RecordNumberIteratorType lRecordNumberIterator;

  lReturnValue = DEM_NO_SUCH_ELEMENT;
  lRecordNumberIterator = Dem_DTCReadoutBuffer_GetRecordNumberIterator(ReadoutBufferId);

  for (/* Already initialized during SRec selection */;
       Dem_Cfg_DTCFreezeFrameRecordIterExists(&lRecordNumberIterator) == TRUE;                                          /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_DTCFreezeFrameRecordIterNext(&lRecordNumberIterator))                                                    /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    lRecordNumber = Dem_Cfg_DTCFreezeFrameRecordIterGet(&lRecordNumberIterator);                                        /* SBSW_DEM_CALL_ITERATOR_POINTER */

    if (Dem_Dcm_SRec_TestRecordMatch(ReadoutBufferId, lRecordNumber) == TRUE)
    {
      uint8 lSnapshotHeaderBitMaskIndex;
      Dem_Cfg_CombinedGroupIndexType lCombinedDTCGroup;
      lCombinedDTCGroup = Dem_Cfg_EventCombinedGroup(Dem_DTCReadoutBuffer_GetMasterEventId(ReadoutBufferId));
      lSnapshotHeaderBitMaskIndex = Dem_DTCReadoutBuffer_GetSnapShotHeaderBitMaskIndex(                                          /* SBSW_DEM_POINTER_FORWARD_STACK */
                                      &lRecordNumberIterator, lCombinedDTCGroup);
      lReturnValue = Dem_Dcm_SRec_CopySRec_CombinedDTC(lRecordNumber,                                                    /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
                       lSnapshotHeaderBitMaskIndex, ReadoutBufferId, DestinationBuffer);
      break;
    }
  }

  /* Increment the iterator in case of a positive match
     For negative match does not make any difference */
  Dem_Cfg_DTCFreezeFrameRecordIterNext(&lRecordNumberIterator);                                                         /* SBSW_DEM_CALL_ITERATOR_POINTER */
  Dem_DTCReadoutBuffer_SetRecordNumberIterator(ReadoutBufferId, &lRecordNumberIterator);                                         /* SBSW_DEM_POINTER_FORWARD_STACK */

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

# if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Dcm_SRec_TestRecordMatch
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE) Dem_Dcm_SRec_TestRecordMatch(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(uint8, AUTOMATIC) RecordNumber
  )
{
  boolean lMatch;
  uint8 lRecordNumberFilter;
  lRecordNumberFilter = Dem_DTCReadoutBuffer_GetSnapshotRecordNumber(ReadoutBufferId);

  if (lRecordNumberFilter == DEM_DCM_SNAPSHOTDATARECORD_ALL)
  {
    if ( (Dem_Cfg_IsWwhObdSupportedInVariant() == TRUE) || (Dem_Dcm_IsObdIIFreezeFrameInService19EnabledInVariant() == TRUE))
    {
      lMatch = TRUE;
    }
    else
    {
      /* exclude OBD Snapshot if necessary */
      if (RecordNumber == DEM_DCM_SNAPSHOTDATARECORD_OBD)
      {
        lMatch = FALSE;
      }
      else
      {
        lMatch = TRUE;
      }
    }
  }
  else
  {
    if (lRecordNumberFilter == RecordNumber)
    {
      lMatch = TRUE;
    }
    else
    {
      lMatch = FALSE;
    }
  }
  return lMatch;
}
#endif

# if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Dcm_SRec_InitSnapshotIterator
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE) Dem_Dcm_SRec_InitSnapshotIterator(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(Dem_DTCReadoutBuffer_ReadoutBufferDataIndexType, AUTOMATIC)  ReadoutBufferDataIndex
  )
{
  Dem_Cfg_ComplexIterType lSourceIterator;

  lSourceIterator = Dem_DTCReadoutBuffer_GetSnapshotSourceIterator(
                      ReadoutBufferId,
                      ReadoutBufferDataIndex);
  switch (Dem_DTCReadoutBuffer_GetSnapshotRecordSource(ReadoutBufferId))
  {
    case Dem_DTCReadoutBuffer_SnapshotSource_Obd:
    case Dem_DTCReadoutBuffer_SnapshotSource_Global:
    case Dem_DTCReadoutBuffer_SnapshotSource_TimeSeries_PowerTrain:
    {
      Dem_Cfg_ComplexIterInit(&lSourceIterator, 0, 1);                                                                           /* SBSW_DEM_POINTER_FORWARD_STACK */
    }
    break;

    case Dem_DTCReadoutBuffer_SnapshotSource_Srec:
    case Dem_DTCReadoutBuffer_SnapshotSource_Srec_GreaterThan_0x30:
    {
      Dem_Cfg_ComplexIterInit(&lSourceIterator, 0, 0);                                                                           /* SBSW_DEM_POINTER_FORWARD_STACK */
    }
    break;

    case Dem_DTCReadoutBuffer_SnapshotSource_TimeSeries_Fast:
    {
      Dem_EventIdType lEventId;

      lEventId = Dem_DTCReadoutBuffer_GetEventId(ReadoutBufferId, ReadoutBufferDataIndex);
      if (Dem_Memory_TimeSeries_TestEventSupportFast(lEventId) == TRUE)
      {
        Dem_Cfg_ComplexIterInit(&lSourceIterator,                                                                                /* SBSW_DEM_POINTER_FORWARD_STACK */
          DEM_DCM_SNAPSHOTDATARECORD_TIMESERIES_FAST_FIRST,
          (uint16_least)DEM_DCM_SNAPSHOTDATARECORD_TIMESERIES_FAST_FIRST +
          Dem_Cfg_TimeSeriesPastSamplesFast() + Dem_Cfg_TimeSeriesFutureSamplesFast());
      }
      else
      {
        Dem_Cfg_ComplexIterInit(&lSourceIterator, 0, 0);                                                                         /* SBSW_DEM_POINTER_FORWARD_STACK */
      }
    }
    break;

    case Dem_DTCReadoutBuffer_SnapshotSource_TimeSeries_Normal:
    {
      Dem_EventIdType lEventId;

      lEventId = Dem_DTCReadoutBuffer_GetEventId(ReadoutBufferId, ReadoutBufferDataIndex);

      if (Dem_Memory_TimeSeries_TestEventSupportNormal(lEventId) == TRUE)
      {
        Dem_Cfg_ComplexIterInit(&lSourceIterator,                                                                                /* SBSW_DEM_POINTER_FORWARD_STACK */
          DEM_DCM_SNAPSHOTDATARECORD_TIMESERIES_NORMAL_FIRST,
          (uint16_least)DEM_DCM_SNAPSHOTDATARECORD_TIMESERIES_NORMAL_FIRST +
          Dem_Cfg_TimeSeriesPastSamplesNormal() + Dem_Cfg_TimeSeriesFutureSamplesNormal());
      }
      else
      {
        Dem_Cfg_ComplexIterInit(&lSourceIterator, 0, 0);                                                                         /* SBSW_DEM_POINTER_FORWARD_STACK */
      }
    }
    break;

    default:
    {
      Dem_Cfg_ComplexIterInit(&lSourceIterator, 0, 0);                                                                           /* SBSW_DEM_POINTER_FORWARD_STACK */
    }
    break;
  }

  Dem_DTCReadoutBuffer_SetSnapshotSourceIterator(ReadoutBufferId,
                                                 ReadoutBufferDataIndex,
                                                 lSourceIterator);
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

# if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Dcm_SRec_SelectNextSource
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_SRec_SelectNextSource(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId
  )
{
  Std_ReturnType lReturnValue;

  if (Dem_DTCReadoutBuffer_GetSnapshotRecordNumber(ReadoutBufferId)
        == DEM_DCM_SNAPSHOTDATARECORD_ALL)
  {
    switch (Dem_DTCReadoutBuffer_GetSnapshotRecordSource(ReadoutBufferId))
    {
    case Dem_DTCReadoutBuffer_SnapshotSource_Obd:
# if (DEM_CFG_SUPPORT_SRECS_CALCULATED == STD_ON)
      Dem_DTCReadoutBuffer_SetSnapshotRecordSource(ReadoutBufferId, Dem_DTCReadoutBuffer_SnapshotSource_Srec);
# else
      Dem_DTCReadoutBuffer_SetSnapshotRecordSource(ReadoutBufferId, Dem_DTCReadoutBuffer_SnapshotSource_Global);
# endif
      lReturnValue = E_OK;
      break;
    case Dem_DTCReadoutBuffer_SnapshotSource_Srec:
# if (DEM_CFG_SUPPORT_SRECS_CALCULATED == STD_ON)
      Dem_DTCReadoutBuffer_SetSnapshotRecordSource(ReadoutBufferId, Dem_DTCReadoutBuffer_SnapshotSource_Global);
# elif (DEM_CFG_SUPPORT_TIME_SERIES_POWERTRAIN == STD_ON)
      Dem_DTCReadoutBuffer_SetSnapshotRecordSource(ReadoutBufferId, Dem_DTCReadoutBuffer_SnapshotSource_TimeSeries_PowerTrain);
# else
      Dem_DTCReadoutBuffer_SetSnapshotRecordSource(ReadoutBufferId, Dem_DTCReadoutBuffer_SnapshotSource_TimeSeries_Fast);
# endif
      lReturnValue = E_OK;
      break;
    case Dem_DTCReadoutBuffer_SnapshotSource_Global:
#  if (DEM_CFG_SUPPORT_SRECS_CALCULATED == STD_ON)
      Dem_DTCReadoutBuffer_SetSnapshotRecordSource(ReadoutBufferId, Dem_DTCReadoutBuffer_SnapshotSource_TimeSeries_Fast);
#  else
      Dem_DTCReadoutBuffer_SetSnapshotRecordSource(ReadoutBufferId, Dem_DTCReadoutBuffer_SnapshotSource_Srec);
#  endif
      lReturnValue = E_OK;
      break;
    case Dem_DTCReadoutBuffer_SnapshotSource_TimeSeries_Fast:
      Dem_DTCReadoutBuffer_SetSnapshotRecordSource(ReadoutBufferId, Dem_DTCReadoutBuffer_SnapshotSource_TimeSeries_Normal);
      lReturnValue = E_OK;
      break;
    case Dem_DTCReadoutBuffer_SnapshotSource_TimeSeries_Normal:
      Dem_DTCReadoutBuffer_SetSnapshotRecordSource(ReadoutBufferId, Dem_DTCReadoutBuffer_SnapshotSource_Invalid);
      lReturnValue = DEM_NO_SUCH_ELEMENT;
      break;
    case Dem_DTCReadoutBuffer_SnapshotSource_TimeSeries_PowerTrain:
      Dem_DTCReadoutBuffer_SetSnapshotRecordSource(ReadoutBufferId, Dem_DTCReadoutBuffer_SnapshotSource_Srec_GreaterThan_0x30);
      lReturnValue = E_OK;
      break;
    case Dem_DTCReadoutBuffer_SnapshotSource_Srec_GreaterThan_0x30:
      Dem_DTCReadoutBuffer_SetSnapshotRecordSource(ReadoutBufferId, Dem_DTCReadoutBuffer_SnapshotSource_Invalid);
      lReturnValue = DEM_NO_SUCH_ELEMENT;
      break;
    default:
      /* Dem_DTCReadoutBuffer_SnapshotSource_Invalid */
      lReturnValue = DEM_NO_SUCH_ELEMENT;
      break;
    }
  }
  else
  {
    Dem_DTCReadoutBuffer_SetSnapshotRecordSource(ReadoutBufferId, Dem_DTCReadoutBuffer_SnapshotSource_Invalid);
    lReturnValue = DEM_NO_SUCH_ELEMENT;
  }

  Dem_Dcm_SRec_InitSnapshotIterator(ReadoutBufferId, DEM_DTCREADOUTBUFFER_DATAINDEX_DEFAULT);

  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON) 
/* ****************************************************************************
 % Dem_Dcm_SRec_ReadNextRecord_Obd
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_SRec_ReadNextRecord_Obd(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer                                                         /* PRQA S 3673 */ /* MD_DEM_8.13_fp */
)
{
  Dem_Cfg_ComplexIterType lSourceIterator;
  Std_ReturnType lReturnValue;

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DestinationBuffer)                                                                            /* PRQA S 3112 */ /* MD_DEM_14.2 */

  lSourceIterator = Dem_DTCReadoutBuffer_GetSnapshotSourceIterator(
                      ReadoutBufferId,
                      DEM_DTCREADOUTBUFFER_DATAINDEX_DEFAULT);

  if (Dem_Cfg_ComplexIterExists(&lSourceIterator) == FALSE)                                                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    lReturnValue = DEM_NO_SUCH_ELEMENT;
  }
  else
  {
    if (Dem_Dcm_SRec_TestRecordMatch(ReadoutBufferId, 0x00u) == TRUE)
    {
      if (Dem_DTCReadoutBuffer_GetMemoryId(ReadoutBufferId) == DEM_CFG_MEMORYID_PRIMARY)
      {
# if (DEM_CFG_SUPPORT_OBDII == STD_ON)
        if (Dem_Dcm_IsObdIIFreezeFrameInService19EnabledInVariant() == TRUE)
        {
          lReturnValue = Dem_Dcm_SRec_CopyNextRecord_ObdII(ReadoutBufferId, DestinationBuffer);                                  /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
        }
        else
#endif
# if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
        if (Dem_Cfg_IsWwhObdSupportedInVariant() == TRUE)
        {
          lReturnValue = Dem_Dcm_SRec_CopyNextRecord_WwhObd(ReadoutBufferId, DestinationBuffer);                                 /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
        }
        else
# endif
        {
          lReturnValue = DEM_NO_SUCH_ELEMENT;
        }
      }
      else
      {
        lReturnValue = DEM_NO_SUCH_ELEMENT;
      }
    }
    else
    {
      lReturnValue = DEM_NO_SUCH_ELEMENT;
    }

    Dem_Cfg_ComplexIterNext(&lSourceIterator);                                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
  }

  Dem_DTCReadoutBuffer_SetSnapshotSourceIterator(ReadoutBufferId,
                                                 DEM_DTCREADOUTBUFFER_DATAINDEX_DEFAULT,
                                                 lSourceIterator);

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif

#if ((DEM_CFG_SUPPORT_DCM == STD_ON) \
   && (DEM_FEATURE_NEED_TIME_SERIES == STD_ON) && (DEM_CFG_SUPPORT_TIME_SERIES_POWERTRAIN == STD_OFF))
/* ****************************************************************************
 % Dem_Dcm_SRec_ReadNextRecord_TimeSeriesNormal
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_SRec_ReadNextRecord_TimeSeriesNormal(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  )
{
  Std_ReturnType lReturnValue;
  Dem_Cfg_ComplexIterType lSourceIterator;

  lReturnValue = DEM_NO_SUCH_ELEMENT;
  lSourceIterator = Dem_DTCReadoutBuffer_GetSnapshotSourceIterator(
                      ReadoutBufferId,
                      DEM_DTCREADOUTBUFFER_DATAINDEX_DEFAULT);

  while (Dem_Cfg_ComplexIterExists(&lSourceIterator) == TRUE)                                                                    /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    uint8 lRecordNumber;
    Dem_EventIdType lEventId;

    lRecordNumber = (uint8)Dem_Cfg_ComplexIterGet(&lSourceIterator);                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
    lEventId = Dem_DTCReadoutBuffer_GetEventId(ReadoutBufferId, DEM_DTCREADOUTBUFFER_DATAINDEX_DEFAULT);

    if (Dem_Dcm_SRec_TestRecordMatch(ReadoutBufferId, lRecordNumber) == TRUE)
    {
      if (Dem_Cfg_EventSRecUdsSize(lEventId) > DestinationBuffer->BufferSize)
      {
        lReturnValue = DEM_BUFFER_TOO_SMALL;
      }
      else
      {
        lReturnValue = E_OK;
        if (Dem_Dcm_TimeSeriesSRecIsReadableInVirtualBuffer(ReadoutBufferId, lRecordNumber) == TRUE)
        {
          Dem_ConstSharedDataPtrType lpSourceBuffer;
          Dem_Mem_ConstTimeSeriesEntryPtrType  lTimeSeriesEntry;
          lTimeSeriesEntry = Dem_Memory_TimeSeries_GetEntrySafe(Dem_DTCReadoutBuffer_GetTimeSeriesEntryIndex(ReadoutBufferId));

# if (DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON)
          if ( (lRecordNumber >= DEM_DCM_SNAPSHOTDATARECORD_TIMESERIES_FAST_FIRST)
             && (lRecordNumber <= DEM_DCM_SNAPSHOTDATARECORD_TIMESERIES_FAST_LAST) )
          {
            lpSourceBuffer = 
              Dem_Memory_TimeSeries_EntryManager_GetFastConstDataPtr(lTimeSeriesEntry,
                                                         lRecordNumber - DEM_DCM_SNAPSHOTDATARECORD_TIMESERIES_FAST_FIRST);      /* SBSW_DEM_POINTER_FORWARD_STACK */
          }
          else
# endif
          {
            lpSourceBuffer =
              Dem_Memory_TimeSeries_EntryManager_GetNormalConstDataPtr(lTimeSeriesEntry,
                                                        lRecordNumber - DEM_DCM_SNAPSHOTDATARECORD_TIMESERIES_NORMAL_FIRST);     /* SBSW_DEM_POINTER_FORWARD_STACK */
          }

          /* Initialize a DestinationBuffer Context. */
          Dem_Data_WriteDestinationBufferUint8(DestinationBuffer, lRecordNumber);                                                /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */

          Dem_DataReport_SRecCopyData(DestinationBuffer,                                                                       /* SBSW_DEM_POINTER_DESTINATIONBUFFER_SOURCEBUFFER */
                                        lpSourceBuffer,
                                        lEventId,
                                        Dem_DTCReadoutBuffer_GetMemoryEntryId(ReadoutBufferId, DEM_DTCREADOUTBUFFER_DATAINDEX_DEFAULT),
                                        Dem_DTCReadoutBuffer_GetMemIndependentCounterPtr(ReadoutBufferId));
        }
      }
      Dem_Cfg_ComplexIterNext(&lSourceIterator);                                                                                 /* SBSW_DEM_CALL_ITERATOR_POINTER */
      break;
    }

    Dem_Cfg_ComplexIterNext(&lSourceIterator);                                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
  }

  Dem_DTCReadoutBuffer_SetSnapshotSourceIterator(ReadoutBufferId,
                                                 DEM_DTCREADOUTBUFFER_DATAINDEX_DEFAULT,
                                                 lSourceIterator);

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Dcm_SRec_ReadNextRecord_TimeSeriesPowertrain
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_SRec_ReadNextRecord_TimeSeriesPowertrain(
  Dem_DTCReadoutBuffer_HandleType ReadoutBufferId,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  )
{
  Dem_EventIdType lEventId;
  Std_ReturnType lReturnValue;
  Dem_Cfg_ComplexIterType lSourceIterator;

  lEventId = Dem_DTCReadoutBuffer_GetEventId(ReadoutBufferId, DEM_DTCREADOUTBUFFER_DATAINDEX_DEFAULT);
  lSourceIterator = Dem_DTCReadoutBuffer_GetSnapshotSourceIterator(
                     ReadoutBufferId,
                     DEM_DTCREADOUTBUFFER_DATAINDEX_DEFAULT);

  if (Dem_Cfg_ComplexIterExists(&lSourceIterator) == FALSE)                                                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    /* Time series powertrain read with previous read operation, there is no second one */
    lReturnValue = DEM_NO_SUCH_ELEMENT;
  }
  else if (Dem_Memory_TimeSeries_TestEventSupportTimeSeries(lEventId) == FALSE)
  {
    /* Event does not have a time series powertrain configured */
    lReturnValue = DEM_NO_SUCH_ELEMENT;
  }
  else
  {
    if (DestinationBuffer->BufferSize < Dem_Dcm_SRec_GetEventTimeSeriesPowertrainUdsSize(lEventId))
    {
      /* supported record, but the buffer is not large enough for all the data */
      lReturnValue = DEM_BUFFER_TOO_SMALL;
    }
    else
    {
      if (Dem_DTCReadoutBuffer_GetTimeSeriesEntryIndex(ReadoutBufferId) != DEM_MEM_INVALID_MEMORY_INDEX)
      {
        Dem_Data_WriteDestinationBufferUint8(DestinationBuffer, (uint8)DEM_DCM_SNAPSHOTDATARECORD_TIMESERIES_POWERTRAIN);        /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
        Dem_DataReport_TimeSeriesPowertrainCopyData(ReadoutBufferId, 
                                                      DestinationBuffer);                                                        /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
      }

      lReturnValue = E_OK;
      Dem_Cfg_ComplexIterNext(&lSourceIterator);                                                                                 /* SBSW_DEM_CALL_ITERATOR_POINTER */
      Dem_DTCReadoutBuffer_SetSnapshotSourceIterator(ReadoutBufferId,
        DEM_DTCREADOUTBUFFER_DATAINDEX_DEFAULT,
        lSourceIterator);
    }
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if ((DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_SRECS == STD_ON))
/* ****************************************************************************
 % Dem_Dcm_SRec_ReadNextRecord_Standard
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_SRec_ReadNextRecord_Standard(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  )
{
  Std_ReturnType lReturnValue;
  Dem_Cfg_SnapshotEntry_IterType lSnapshotEntryIter;
  Dem_Cfg_SRecIndexType lSRecIndex;

  lReturnValue = DEM_NO_SUCH_ELEMENT;
  lSnapshotEntryIter = Dem_DTCReadoutBuffer_GetSnapshotEntryIterator(
                         ReadoutBufferId,
                         DEM_DTCREADOUTBUFFER_DATAINDEX_DEFAULT);

  while (Dem_SnapshotEntry_IteratorExists(&lSnapshotEntryIter) == TRUE)                                                          /* PRQA S 0771 */ /* MD_DEM_15.4_opt */ /* SBSW_DEM_POINTER_FORWARD_STACK */
  {
# if (DEM_CFG_SUPPORT_SRECS_CALCULATED == STD_ON)
    uint8 lRecordNumber;
# endif

    lSRecIndex = Dem_SnapshotEntry_IteratorGetSnapshotRecordIndex(&lSnapshotEntryIter);                                          /* SBSW_DEM_POINTER_FORWARD_STACK */

# if (DEM_CFG_SUPPORT_SRECS_CALCULATED == STD_ON)
    lRecordNumber = Dem_DTCReadoutBuffer_GetSnapshotRecordNumber(ReadoutBufferId);
    if (lRecordNumber < Dem_Cfg_SRecId(lSRecIndex))
    {
      /* overshoot -> snapshot not supported */
      lReturnValue = DEM_NO_SUCH_ELEMENT;
      break;
    }
    else
# endif
# if (DEM_CFG_SUPPORT_TIME_SERIES_POWERTRAIN == STD_ON)
    if (   (Dem_DTCReadoutBuffer_GetSnapshotRecordNumber(ReadoutBufferId) == DEM_DCM_SNAPSHOTDATARECORD_ALL)
        && (Dem_Cfg_SRecId(lSRecIndex) > DEM_DCM_SNAPSHOTDATARECORD_TIMESERIES_POWERTRAIN)
        && (Dem_DTCReadoutBuffer_GetSnapshotRecordSource(ReadoutBufferId) != Dem_DTCReadoutBuffer_SnapshotSource_Srec_GreaterThan_0x30)) /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
    {
      lReturnValue = DEM_NO_SUCH_ELEMENT;
      break;
    }
    else
# endif
    if (Dem_Dcm_SRec_TestRecordMatch(ReadoutBufferId, Dem_Cfg_SRecId(lSRecIndex)) == TRUE)
    {
      Dem_EventIdType lEventId;
      lEventId = Dem_DTCReadoutBuffer_GetEventId(ReadoutBufferId, DEM_DTCREADOUTBUFFER_DATAINDEX_DEFAULT);
      if (DestinationBuffer->BufferSize < Dem_Cfg_EventSRecUdsSize(lEventId))
      {
        /* supported record, but the buffer is not large enough for all the data */
        lReturnValue = DEM_BUFFER_TOO_SMALL;
      }
      else
      {
        if (Dem_SnapshotEntry_IteratorIsSnapshotRecordStored(&lSnapshotEntryIter) == TRUE)                                       /* SBSW_DEM_POINTER_FORWARD_STACK */
        {
          Dem_Data_WriteDestinationBufferUint8(DestinationBuffer, Dem_Cfg_SRecId(lSRecIndex));                                   /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
          Dem_DataReport_SRecCopyData(DestinationBuffer,                                                                       /* SBSW_DEM_POINTER_DESTINATIONBUFFER_SOURCEBUFFER */
                                        Dem_SnapshotEntry_IteratorGetSnapshotRecordDataConstPtr(&lSnapshotEntryIter),            /* SBSW_DEM_POINTER_FORWARD_STACK */
                                        lEventId,
                                        Dem_DTCReadoutBuffer_GetMemoryEntryId(ReadoutBufferId,
                                        DEM_DTCREADOUTBUFFER_DATAINDEX_DEFAULT),
                                        Dem_DTCReadoutBuffer_GetMemIndependentCounterPtr(ReadoutBufferId));
        }

        lReturnValue = E_OK;
      }

      Dem_SnapshotEntry_IteratorNext(&lSnapshotEntryIter);                                                                       /* SBSW_DEM_POINTER_FORWARD_STACK */
      break;
    }
    else
    {
      /* otherwise next snapshot record */
    }

    Dem_SnapshotEntry_IteratorNext(&lSnapshotEntryIter);                                                                         /* SBSW_DEM_POINTER_FORWARD_STACK */
  }

  Dem_DTCReadoutBuffer_SetSnapshotEntryIterator(ReadoutBufferId,
                                                DEM_DTCREADOUTBUFFER_DATAINDEX_DEFAULT,
                                                lSnapshotEntryIter);

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif /* (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_SRECS == STD_ON) */

#if ((DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON))
/* ****************************************************************************
 % Dem_Dcm_SRec_ReadNextRecord_Global
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_SRec_ReadNextRecord_Global(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  )
{
  Dem_Cfg_ComplexIterType lSourceIterator;
  Std_ReturnType lReturnValue;

  lSourceIterator = Dem_DTCReadoutBuffer_GetSnapshotSourceIterator(
                      ReadoutBufferId,
                      DEM_DTCREADOUTBUFFER_DATAINDEX_DEFAULT);

  if (Dem_Cfg_ComplexIterExists(&lSourceIterator) == FALSE)                                                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    /* Global snapshot read with previous read operation, there is no second one */
    lReturnValue = DEM_NO_SUCH_ELEMENT;
  }
  else
  {
    if (DestinationBuffer->BufferSize < Dem_Cfg_GlobalSRecUdsSize())
    {
      /* supported record, but the buffer is not large enough for all the data */
      lReturnValue = DEM_BUFFER_TOO_SMALL;
    }
    else
    {
      if (Dem_DTCReadoutBuffer_TestGlobalSnapshotStored(ReadoutBufferId, DEM_DTCREADOUTBUFFER_DATAINDEX_DEFAULT) == TRUE)
      {
        Dem_ConstDataPtrType lGlobalSnapshotDataPtr;
        Dem_Cfg_MemoryEntryHandleType lReadoutBufferMemoryEntryId;

        lReadoutBufferMemoryEntryId = Dem_DTCReadoutBuffer_GetMemoryEntryId(ReadoutBufferId,
                                                                            DEM_DTCREADOUTBUFFER_DATAINDEX_DEFAULT);
        lGlobalSnapshotDataPtr = Dem_DTCReadoutBuffer_GetGlobalSnapshotDataPtr(
                                   ReadoutBufferId, DEM_DTCREADOUTBUFFER_DATAINDEX_DEFAULT);

        Dem_Data_WriteDestinationBufferUint8(DestinationBuffer, Dem_Cfg_GlobalSRecId());                                         /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
        Dem_DataReport_GlobalSnapshotCopyData(DestinationBuffer,                                                               /* SBSW_DEM_POINTER_DESTINATIONBUFFER_SOURCEBUFFER */
                                                lGlobalSnapshotDataPtr,                                                          /* SBSW_DEM_POINTER_FORWARD_STACK */
                                                lReadoutBufferMemoryEntryId,
                                                Dem_DTCReadoutBuffer_GetMemIndependentCounterPtr(ReadoutBufferId));
      }

      lReturnValue = E_OK;
    }
    Dem_Cfg_ComplexIterNext(&lSourceIterator);                                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
  }

  Dem_DTCReadoutBuffer_SetSnapshotSourceIterator(ReadoutBufferId,
                                                 DEM_DTCREADOUTBUFFER_DATAINDEX_DEFAULT,
                                                 lSourceIterator);
  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif /* (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON) */

#if (DEM_CFG_SUPPORT_DCM == STD_ON) \
    && (DEM_FEATURE_NEED_TIME_SERIES == STD_ON) && (DEM_CFG_SUPPORT_TIME_SERIES_POWERTRAIN == STD_OFF) 
/* ****************************************************************************
 % Dem_Dcm_SRec_CalculateSize_TimeSeriesNormal
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_SRec_CalculateSize_TimeSeriesNormal(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  RecordNumber,
  CONSTP2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  SizeOfFreezeFrame
  )
{
  Std_ReturnType lReturnValue;

  if (Dem_Dcm_TimeSeriesSRecIsValid(EventId, RecordNumber) == TRUE)
  {
    lReturnValue = E_OK;
    if (Dem_Dcm_TimeSeriesSRecIsReadableInVirtualBuffer(ReadoutBufferId, RecordNumber) == TRUE)
    {
      *SizeOfFreezeFrame = Dem_Cfg_EventSRecUdsSize(EventId);                                                                    /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    }
    else
    {
      *SizeOfFreezeFrame = 0u;                                                                                                   /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    }
  }
  else
  {
    lReturnValue = DEM_NO_SUCH_ELEMENT;
  }

  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Dcm_SRec_CalculateSize_TimeSeriesPowertrain
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
*/
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_SRec_CalculateSize_TimeSeriesPowertrain(                                                                                 /* PRQA S 3219 */ /* MD_DEM_14.1_CONFIGURATION_SWITCH */
  Dem_DTCReadoutBuffer_HandleType ReadoutBufferId,
  Dem_EventIdType EventId,
  CONSTP2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  SizeOfFreezeFrame
  )
{
  Std_ReturnType lReturnValue;
  
  lReturnValue = DEM_NO_SUCH_ELEMENT;
  *SizeOfFreezeFrame = 0x00;                                                                                                     /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */

  if (Dem_Memory_TimeSeries_TestEventSupportTimeSeries(EventId) == TRUE)
  {
    if (Dem_DTCReadoutBuffer_GetTimeSeriesEntryIndex(ReadoutBufferId) != DEM_MEM_INVALID_MEMORY_INDEX)
    {
      *SizeOfFreezeFrame = Dem_Dcm_SRec_GetEventTimeSeriesPowertrainUdsSize(EventId);                                            /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    }

    lReturnValue = E_OK;
  }

  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_SRECS == STD_ON)
/* ****************************************************************************
 % Dem_Dcm_SRec_CalculateSize_SingleRecordNormalEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_SRec_CalculateSize_SingleRecordNormalEvent(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(uint8, AUTOMATIC)  RecordNumber,
  CONSTP2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  SizeOfFreezeFrame
  )
{
  Std_ReturnType lReturnValue;

  /* Specific record not found is a negative result */
  Dem_Cfg_SnapshotEntry_IterType lSnapshotEntryIter;
  Dem_EventIdType lEventId;
  Dem_Cfg_MemoryEntryHandleType lReadoutBufferMemoryEntryId;

  lReturnValue = E_OK;
  lEventId = Dem_DTCReadoutBuffer_GetEventId(ReadoutBufferId, DEM_DTCREADOUTBUFFER_DATAINDEX_DEFAULT);
  lReadoutBufferMemoryEntryId = Dem_DTCReadoutBuffer_GetMemoryEntryId(ReadoutBufferId, DEM_DTCREADOUTBUFFER_DATAINDEX_DEFAULT);

  for (Dem_SnapshotEntry_IteratorInit(lEventId, lReadoutBufferMemoryEntryId, &lSnapshotEntryIter);                               /* SBSW_DEM_POINTER_FORWARD_STACK */
        Dem_SnapshotEntry_IteratorExists(&lSnapshotEntryIter) == TRUE;                                                           /* SBSW_DEM_POINTER_FORWARD_STACK */
        Dem_SnapshotEntry_IteratorNext(&lSnapshotEntryIter))                                                                     /* SBSW_DEM_POINTER_FORWARD_STACK */
  {
    Dem_Cfg_SRecIndexType lCfgSRecIndex;
    lCfgSRecIndex = Dem_SnapshotEntry_IteratorGetSnapshotRecordIndex(&lSnapshotEntryIter);                                       /* SBSW_DEM_POINTER_FORWARD_STACK */
    DEM_IGNORE_UNUSED_VARIABLE(lCfgSRecIndex)                                                                                    /* PRQA S 3112 */ /* MD_DEM_14.2 */

    if (Dem_Cfg_SRecId(lCfgSRecIndex) == RecordNumber)
    {
      if (Dem_SnapshotEntry_IteratorIsSnapshotRecordStored(&lSnapshotEntryIter) == TRUE)                                         /* SBSW_DEM_POINTER_FORWARD_STACK */
      {
        *SizeOfFreezeFrame = Dem_Cfg_EventSRecUdsSize(lEventId);                                                                 /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      }
      else
      {
        *SizeOfFreezeFrame = 0u;                                                                                                  /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      }
      break;
    }
  }

  if (Dem_SnapshotEntry_IteratorExists(&lSnapshotEntryIter) == FALSE)                                                            /* SBSW_DEM_POINTER_FORWARD_STACK */
  {
    lReturnValue = DEM_NO_SUCH_ELEMENT;
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) \
    && (DEM_CFG_SUPPORT_SRECS == STD_ON) \
    && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 % Dem_Dcm_SRec_CalculateSize_SingleRecordCombinedEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(uint16, DEM_CODE)
Dem_Dcm_SRec_CalculateSize_SingleRecordCombinedEvent(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(uint8, AUTOMATIC)  RecordNumber,
  CONST(uint8, AUTOMATIC)  SnapshotHeaderBitMaskIndex
  )
{
  uint16 lSizeOfFreezeFrame;
  uint8 lNumOccupiedReadoutBufferEntries;
  Dem_Cfg_MemoryEntryHandleType lReadoutBufferMemoryEntryId;
  Dem_DTCReadoutBuffer_ReadoutBufferDataIndexType ReadoutBufferDataIndex;

  lSizeOfFreezeFrame = 0x00U;
  lNumOccupiedReadoutBufferEntries = Dem_DTCReadoutBuffer_GetNumberOfOccupiedSlots(ReadoutBufferId);

  for (ReadoutBufferDataIndex = DEM_DTCREADOUTBUFFER_DATAINDEX_DEFAULT;
       ReadoutBufferDataIndex < lNumOccupiedReadoutBufferEntries;
       ReadoutBufferDataIndex++)
  {
    lReadoutBufferMemoryEntryId = Dem_DTCReadoutBuffer_GetMemoryEntryId(ReadoutBufferId, ReadoutBufferDataIndex);
    if (Dem_SnapshotEntry_GetSRecStorageStatus(RecordNumber, SnapshotHeaderBitMaskIndex, lReadoutBufferMemoryEntryId) == TRUE)
    {
      lSizeOfFreezeFrame += Dem_Cfg_EventSRecUdsSize(
        Dem_DTCReadoutBuffer_GetEventId(ReadoutBufferId, ReadoutBufferDataIndex));
    }
  }

  return lSizeOfFreezeFrame;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) \
   && ( (DEM_CFG_SUPPORT_SRECS == STD_ON) \
     || (DEM_FEATURE_NEED_TIME_SERIES == STD_ON) \
     || (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON) \
     || ((DEM_CFG_SUPPORT_OBDII == STD_ON) && (DEM_CFG_SUPPORT_OBDII_FREEZEFRAME_IN_SVC19 == STD_ON)) \
     || (DEM_CFG_SUPPORT_WWHOBD == STD_ON) ) )
/* ****************************************************************************
 % Dem_Dcm_SRec_CalculateSize_AllNormalEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_SRec_CalculateSize_AllNormalEvent(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONSTP2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  SizeOfFreezeFrame
  )
{
  Std_ReturnType lReturnValue;
  uint16 lSizeOfFreezeFrame;
  uint16 lSizeOfOBDFreezeFrame;
  uint16 lSizeOfTimeSeriesPowertrain;
  Dem_EventIdType lEventId;

  lEventId = Dem_DTCReadoutBuffer_GetEventId(ReadoutBufferId, DEM_DTCREADOUTBUFFER_DATAINDEX_DEFAULT);
# if (DEM_CFG_SUPPORT_SRECS == STD_ON)
  {
    Dem_Cfg_MemoryEntryHandleType lReadoutBufferMemoryEntryId;

    lReadoutBufferMemoryEntryId = Dem_DTCReadoutBuffer_GetMemoryEntryId(ReadoutBufferId,
                                                                        DEM_DTCREADOUTBUFFER_DATAINDEX_DEFAULT);
    lSizeOfFreezeFrame =
      (uint16)(Dem_SnapshotEntry_GetNumberOfStoredSnapshotRecords(lReadoutBufferMemoryEntryId)
                 * Dem_Cfg_EventSRecUdsSize(lEventId));
  }
  lReturnValue = E_OK;
# else
  lSizeOfFreezeFrame = 0u;
  lReturnValue = DEM_NO_SUCH_ELEMENT;
# endif

# if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON) && (DEM_CFG_SUPPORT_TIME_SERIES_POWERTRAIN == STD_OFF)
  {
    /* lReturnValue = E_OK already set since time series cannot be active if
    DEM_CFG_SUPPORT_SRECS is off */
    lSizeOfFreezeFrame += (uint16)(Dem_Dcm_TimeSeriesSRecCountOfVirtualBuffer(ReadoutBufferId)
                                  * Dem_Cfg_EventSRecUdsSize(lEventId));
  }
#endif

  if (Dem_Memory_TimeSeries_IsPowertrainEnabled() == TRUE)
  {
    if (Dem_Dcm_SRec_CalculateSize_TimeSeriesPowertrain(ReadoutBufferId, lEventId, &lSizeOfTimeSeriesPowertrain) == E_OK)        /* SBSW_DEM_POINTER_FORWARD_STACK */
    {
      lSizeOfFreezeFrame += lSizeOfTimeSeriesPowertrain;
      lReturnValue = E_OK;
    }
  }

# if (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
  {
#  if (DEM_CFG_SUPPORT_SRECS == STD_OFF)
    lReturnValue = E_OK;
#  endif
    if (Dem_DTCReadoutBuffer_TestGlobalSnapshotStored(
          ReadoutBufferId, DEM_DTCREADOUTBUFFER_DATAINDEX_DEFAULT) == TRUE)
    {
      lSizeOfFreezeFrame += Dem_Cfg_GlobalSRecUdsSize();                                                                         
    }
  }
# endif

  if (Dem_Dcm_IsObdIIFreezeFrameInService19EnabledInVariant() == TRUE)
  {
    if (Dem_Dcm_SRec_CalculateSize_ObdII(lEventId, &lSizeOfOBDFreezeFrame) == E_OK)                                              /* SBSW_DEM_POINTER_FORWARD_STACK */
    {
      lReturnValue = E_OK;
      lSizeOfFreezeFrame += lSizeOfOBDFreezeFrame;
    }
  }

  if (Dem_Cfg_IsWwhObdSupportedInVariant() == TRUE)
  {
    if (Dem_Dcm_SRec_CalculateSize_WwhObd(lEventId, &lSizeOfOBDFreezeFrame) == E_OK)                                             /* SBSW_DEM_POINTER_FORWARD_STACK */
    {
      lReturnValue = E_OK;
      lSizeOfFreezeFrame += lSizeOfOBDFreezeFrame;
    }
  }

 # if (DEM_CFG_SUPPORT_SRECS == STD_OFF && DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_OFF)
  if (lReturnValue == E_OK)
# endif
  {
    /* At least one snapshot is configured for event */
    *SizeOfFreezeFrame = lSizeOfFreezeFrame;                                                                                     /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_OBDII == STD_ON) )
/* ****************************************************************************
 % Dem_Dcm_SRec_CopyNextRecord_ObdII
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_SRec_CopyNextRecord_ObdII(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  )
{
  Std_ReturnType lReturnValue;
  Dem_EventIdType lEventId;

  lEventId = Dem_DTCReadoutBuffer_GetEventId(ReadoutBufferId, DEM_DTCREADOUTBUFFER_DATAINDEX_DEFAULT);
  if (Dem_Cfg_EventObdRelated(lEventId) == FALSE)
  {
    lReturnValue = DEM_NO_SUCH_ELEMENT;
  }
  else
  {
    lReturnValue = E_OK;
    if ( (Dem_DTCReadoutBuffer_GetOBDData_IsStored(ReadoutBufferId) == TRUE))
    {
      /* Event has a stored OBD freeze frame */
      if ((((uint32)DestinationBuffer->WriteIndex) + Dem_Cfg_GlobalObdIIFFUdsSize()) > DestinationBuffer->BufferSize)
      {
        /* supported record, but the buffer is not large enough for the data */
        lReturnValue = DEM_BUFFER_TOO_SMALL;
      }
      else
      {
        /* Read Freeze Frame */
        Dem_DataReport_BufferIndexType lBufferIdx;                                                                             /* PRQA S 0759 */ /* MD_MSR_Union */
        lBufferIdx.ReadoutBufferId = ReadoutBufferId;

        Dem_Data_WriteDestinationBufferUint8(DestinationBuffer, 0x00U);                                                          /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
        Dem_DataReport_ObdIIFreezeFrameCopyUdsData(lBufferIdx,
                                                     DestinationBuffer,
                                                     DEM_DATAREPORT_SOURCE_OBDII_FF_READOUTBUFFER);                            /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */


        lReturnValue = E_OK;
      }
    } /* else FreezeFrame is not stored */
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif /* (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_OBDII == STD_ON) */

#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 % Dem_Dcm_SRec_CopyNextRecord_WwhObd
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_SRec_CopyNextRecord_WwhObd(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  )
{
  Std_ReturnType lReturnValue;
  Dem_EventIdType lEventId;

  lEventId = Dem_DTCReadoutBuffer_GetEventId(ReadoutBufferId, DEM_DTCREADOUTBUFFER_DATAINDEX_DEFAULT);

  if (Dem_Cfg_EventObdRelated(lEventId) == FALSE)
  {
    lReturnValue = DEM_NO_SUCH_ELEMENT;
  }
  else
  {
    if (Dem_Cfg_EventWwhObdFFUdsSize(lEventId) > DestinationBuffer->BufferSize)
    { /* supported record, but the buffer is not large enough for all the data */
      lReturnValue = DEM_BUFFER_TOO_SMALL;
    }
    else
    {
      Dem_Cfg_MemoryIndexType lMemoryIndex;

      lMemoryIndex = Dem_Memory_FindIndex(lEventId);
      lReturnValue = E_OK;

      if (lMemoryIndex != DEM_MEM_INVALID_MEMORY_INDEX)
      { /* process request if Freeze Frame is stored */
# if (DEM_FEATURE_NEED_AGING_REALLOCATION == STD_ON)                                                                             /* COV_DEM_UNSUPPORTED_FEATURE TX */
        if (DEM_MEM_TEST_AGING_ONLY(Dem_MemoryEntry_GetState(Dem_MemoryEntry_GetId(lMemoryIndex))) == FALSE)
# endif
        {
          Dem_Cfg_MemoryEntryHandleType lReadoutBufferMemoryEntryId;

          lReadoutBufferMemoryEntryId = Dem_DTCReadoutBuffer_GetMemoryEntryId(
                                          ReadoutBufferId, DEM_DTCREADOUTBUFFER_DATAINDEX_DEFAULT);
          Dem_Data_WriteDestinationBufferUint8(DestinationBuffer, 0x00u);                                                         /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
          Dem_DataReport_WWHOBDFreezeFrameCopyData(DestinationBuffer,                                                          /* SBSW_DEM_POINTER_DESTINATIONBUFFER_SOURCEBUFFER */
            (Dem_ConstSharedDataPtrType) Dem_MemoryEntry_GetWwhObdFreezeFrameDataPtr(lReadoutBufferMemoryEntryId),
            lEventId,
            lReadoutBufferMemoryEntryId,
            Dem_DTCReadoutBuffer_GetMemIndependentCounterPtr(ReadoutBufferId));
        }
      }
    }
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif /* (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_WWHOBD == STD_ON) */

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Dcm_SRec_CalculateSize_ObdII
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_SRec_CalculateSize_ObdII(                                                                                                /* PRQA S 3219 */ /* MD_DEM_14.1_CONFIGURATION_SWITCH */
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONSTP2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  SizeOfFreezeFrame
  )
{
  Std_ReturnType lReturnValue;

  if (Dem_Cfg_EventObdRelated(EventId) == FALSE)
  {
    lReturnValue = DEM_NO_SUCH_ELEMENT;
  }
  else
  { /* scan the freeze frame memory for the requested DTC */
    uint8 lSelectedIndex;
    lSelectedIndex = Dem_Mem_FreezeFrameFindIndex(EventId);

    /* Check if FreezeFrame is available */
    if (lSelectedIndex != Dem_Cfg_GlobalObdIIFFCount())
    {
      *SizeOfFreezeFrame = Dem_Cfg_GlobalObdIIFFUdsSize();                                                                       /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    }
    else
    { /* FreezeFrame is not stored */
      *SizeOfFreezeFrame = 0u;                                                                                                    /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    }
    lReturnValue = E_OK;
  }

  return lReturnValue;
}
#endif /* (DEM_CFG_SUPPORT_DCM == STD_ON) */

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Dcm_SRec_CalculateSize_WwhObd
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_SRec_CalculateSize_WwhObd(                                                                                               /* PRQA S 3219 */ /* MD_DEM_14.1_CONFIGURATION_SWITCH */
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONSTP2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  SizeOfFreezeFrame
  )
{
  Std_ReturnType lReturnValue;

  if (Dem_Cfg_EventObdRelated(EventId) == FALSE)
  {
    lReturnValue = DEM_NO_SUCH_ELEMENT;
  }
  else
  {
    Dem_Cfg_MemoryIndexType lMemoryIndex;

    lReturnValue = E_OK;
    lMemoryIndex = Dem_Memory_FindIndex(EventId);

    if (lMemoryIndex != DEM_MEM_INVALID_MEMORY_INDEX)
    { /* process request if Freeze Frame is stored */
# if (DEM_FEATURE_NEED_AGING_REALLOCATION == STD_ON)                                                                             /* COV_DEM_UNSUPPORTED_FEATURE TX */
      if (DEM_MEM_TEST_AGING_ONLY(Dem_MemoryEntry_GetState(Dem_MemoryEntry_GetId(lMemoryIndex))) == TRUE)
      {
        *SizeOfFreezeFrame = 0u;                                                                                                  /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      }
      else
# endif
      {
        *SizeOfFreezeFrame = Dem_Cfg_EventWwhObdFFUdsSize(EventId);                                                              /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      }
    }
    else
    {
      *SizeOfFreezeFrame = 0u;                                                                                                    /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    }
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

/* ****************************************************************************
 % Dem_Dcm_SRec_GetEventTimeSeriesPowertrainUdsSize
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Dcm_SRec_GetEventTimeSeriesPowertrainUdsSize(                                                                                /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  Dem_EventIdType  EventId                                                                                                       /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  uint16 lSRecUdsSize;
  lSRecUdsSize = (uint16)0x00;

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */

#if ((DEM_FEATURE_NEED_TIME_SERIES == STD_ON) && (DEM_CFG_SUPPORT_TIME_SERIES_POWERTRAIN == STD_ON))
  if (((boolean)(Dem_Cfg_IsTimeSeriesNormalOfEventTable(EventId))) == TRUE)
  {
    lSRecUdsSize = Dem_Cfg_GetRecordSizeUdsOfNormalRateTimeSeriesPowertrainOfFreezeFrameTable(Dem_Cfg_GetFreezeFrameTableDevFFBIdxOfEventTable(EventId));
  }
  else /* TimeSeries Fast */
  {
    lSRecUdsSize = Dem_Cfg_GetRecordSizeUdsOfFastRateTimeSeriesPowertrainOfFreezeFrameTable(Dem_Cfg_GetFreezeFrameTableDevFFBIdxOfEventTable(EventId));
  }
#endif

  return lSRecUdsSize;
}

#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_SRECS == STD_ON) && (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 % Dem_Dcm_TimeSeriesSRecCountOfVirtualBuffer
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Dcm_TimeSeriesSRecCountOfVirtualBuffer(                                                                                       /* PRQA S 3219 */ /* MD_DEM_14.1_CONFIGURATION_SWITCH */
  Dem_DTCReadoutBuffer_HandleType ReadoutBufferId
)
{
  uint8 lReturnValue;

  lReturnValue = 0u;
  if (Dem_DTCReadoutBuffer_GetTimeSeriesEntryIndex(ReadoutBufferId) != DEM_MEM_INVALID_MEMORY_INDEX)
  {
    Dem_Mem_ConstTimeSeriesEntryPtrType  lTimeSeriesEntry;
    lTimeSeriesEntry = Dem_Memory_TimeSeries_GetEntrySafe(Dem_DTCReadoutBuffer_GetTimeSeriesEntryIndex(ReadoutBufferId));

    lReturnValue += (Dem_Cfg_TimeSeriesPastSamplesNormal() 
    - Dem_Memory_TimeSeries_EntryManager_GetUnusedPastSamplesNormal(lTimeSeriesEntry));                                          /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */

    lReturnValue += (Dem_Cfg_TimeSeriesFutureSamplesNormal() 
    - Dem_DTCReadoutBuffer_GetUnusedFutureSamplesNormal(ReadoutBufferId));

    lReturnValue += (Dem_Cfg_TimeSeriesPastSamplesFast() 
    - Dem_Memory_TimeSeries_EntryManager_GetUnusedPastSamplesFast(lTimeSeriesEntry));                                            /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */

    lReturnValue += (Dem_Cfg_TimeSeriesFutureSamplesFast()
    - Dem_DTCReadoutBuffer_GetUnusedFutureSamplesFast(ReadoutBufferId));
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif


#if (DEM_CFG_SUPPORT_SRECS == STD_ON) && (DEM_FEATURE_NEED_TIME_SERIES == STD_ON) && (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Dcm_TimeSeriesSRecIsReadableInVirtualBuffer
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Dcm_TimeSeriesSRecIsReadableInVirtualBuffer(                                                                                /* PRQA S 3219 */ /* MD_DEM_14.1_CONFIGURATION_SWITCH */
  Dem_DTCReadoutBuffer_HandleType ReadoutBufferId,
  uint8  RecordNumber
)
{
  boolean lIsStored;
  if (Dem_DTCReadoutBuffer_GetTimeSeriesEntryIndex(ReadoutBufferId) == DEM_MEM_INVALID_MEMORY_INDEX)
  {
    lIsStored = FALSE;
  }
  else
  {
    Dem_Mem_ConstTimeSeriesEntryPtrType  lTimeSeriesEntry;
    uint8 lSRecStoredIndex;
    lTimeSeriesEntry = Dem_Memory_TimeSeries_GetEntrySafe(Dem_DTCReadoutBuffer_GetTimeSeriesEntryIndex(ReadoutBufferId));

    if (RecordNumber >= 0x30u)
    {
      lSRecStoredIndex = RecordNumber - 0x30u;
      if (lSRecStoredIndex >= Dem_Cfg_TimeSeriesPastSamplesNormal())
      {
        lSRecStoredIndex -= Dem_Cfg_TimeSeriesPastSamplesNormal();
        lIsStored = (lSRecStoredIndex < (Dem_Cfg_TimeSeriesFutureSamplesNormal() - Dem_DTCReadoutBuffer_GetUnusedFutureSamplesNormal(ReadoutBufferId)));
      }
      else
      {
        lIsStored = (lSRecStoredIndex >= Dem_Memory_TimeSeries_EntryManager_GetUnusedPastSamplesNormal(lTimeSeriesEntry));       /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
      }
    }
    else /* RecordNumber is fast sample */
    {
      lSRecStoredIndex = RecordNumber - 0x10u;
      if (lSRecStoredIndex >= Dem_Cfg_TimeSeriesPastSamplesFast())
      {
        lSRecStoredIndex -= Dem_Cfg_TimeSeriesPastSamplesFast();
        lIsStored = (lSRecStoredIndex < (Dem_Cfg_TimeSeriesFutureSamplesFast() - Dem_DTCReadoutBuffer_GetUnusedFutureSamplesFast(ReadoutBufferId)));
      }
      else
      {
        lIsStored = (lSRecStoredIndex >= Dem_Memory_TimeSeries_EntryManager_GetUnusedPastSamplesFast(lTimeSeriesEntry));         /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
      }
    }
  }
  return lIsStored;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif


/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \addtogroup Dem_Dcm_Public
 * \{
 */

#if (DEM_CFG_SUPPORT_SRECS == STD_ON) && (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 % Dem_Dcm_TimeSeriesSRecIsValid
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_Dcm_TimeSeriesSRecIsValid(                                                                                                   /* PRQA S 3219 */ /* MD_DEM_14.1_CONFIGURATION_SWITCH */
  Dem_EventIdType  EventId,
  uint8  RecordNumber
  )
{
  boolean lIsValid;

  lIsValid = FALSE;

  if (RecordNumber >= 0x30u)
  {
    if (Dem_Memory_TimeSeries_TestEventSupportNormal(EventId) == TRUE)
    {
      if (RecordNumber < (0x30u + (Dem_Cfg_TimeSeriesPastSamplesNormal() + Dem_Cfg_TimeSeriesFutureSamplesNormal())))
      {
        lIsValid = TRUE;
      }
    }
  }
  else
  {
    if (Dem_Memory_TimeSeries_TestEventSupportFast(EventId) == TRUE)
    {
      if ( (RecordNumber >= 0x10u)
        && (RecordNumber < (0x10u + (Dem_Cfg_TimeSeriesPastSamplesFast() + Dem_Cfg_TimeSeriesFutureSamplesFast()))))
      {
        lIsValid = TRUE;
      }
    }
  }

  return lIsValid;
}
#endif

 /* ****************************************************************************
 % Dem_Dcm_IsObdIIFreezeFrameInService19EnabledInVariant
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Dcm_IsObdIIFreezeFrameInService19EnabledInVariant(                                                                                    /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
)
{
  return (Dem_Cfg_IsObdIISupportedInVariant() && Dem_Cfg_IsObdIIFreezeFrameInService19Enabled());
}


/* ****************************************************************************
 % Dem_Dcm_Init
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Dcm_Init(
  void
  )
{
  Dem_DTCReporting_SetObdHideOccurrences();
}

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Dcm_SRec_SelectFirstSource
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Dcm_SRec_SelectFirstSource(
  CONST(uint8, AUTOMATIC) ClientId,
  CONST(uint8, AUTOMATIC)  RecordNumber
  )
{
#if (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
  if (Dem_DTCReadoutBuffer_TestCombinedEventSelected(Dem_Client_ClientAccess_GetReadoutBuffer(ClientId)) == TRUE)
  {
    Dem_Dcm_SRec_SelectFirstSource_CombinedEvent(ClientId, RecordNumber);
  }
  else
#endif
  {
    Dem_Dcm_SRec_SelectFirstSource_NormalEvent(ClientId, RecordNumber);
  }
}
#endif


#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Dcm_SRec_ReadNextRecord
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_SRec_ReadNextRecord(
  CONST(uint8, AUTOMATIC) ClientId,
  CONSTP2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)  DestBuffer,                                                                       /* PRQA S 3673 */ /* MD_DEM_8.13_fp */
  CONSTP2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  BufSize                                                                          /* PRQA S 3673 */ /* MD_DEM_8.13_fp */
  )
{
  Std_ReturnType lReturnValue;
  Dem_Data_DestinationBuffer lDestinationBuffer;

  /* Initialize a DestinationBuffer Context. */
  Dem_Data_InitDestinationBuffer(&lDestinationBuffer, DestBuffer, *BufSize);                                                     /* SBSW_DEM_CALL_DESTINATIONBUFFER_INIT */

# if (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
  if (Dem_DTCReadoutBuffer_TestCombinedEventSelected(Dem_Client_ClientAccess_GetReadoutBuffer(ClientId)) == TRUE)
  {
    lReturnValue = Dem_Dcm_SRec_ReadNextRecord_CombinedDTC(ClientId, &lDestinationBuffer);                                       /* SBSW_DEM_POINTER_LOCAL_DESTINATIONBUFFER */
  }
  else
# endif
  {
    lReturnValue = Dem_Dcm_SRec_ReadNextRecord_NormalEvent(ClientId, &lDestinationBuffer);                                       /* SBSW_DEM_POINTER_LOCAL_DESTINATIONBUFFER */
  }

  if (lReturnValue == E_OK)
  {
    *BufSize = lDestinationBuffer.WriteIndex;                                                                                    /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  }

  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Dcm_SRec_GetSize
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_SRec_GetSize(
  CONST(uint8, AUTOMATIC)  ClientId,
  CONSTP2VAR(uint16, AUTOMATIC, DEM_DCM_DATA)  SizeOfFreezeFrame
  )
{
  Std_ReturnType lRetVal;
# if (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
  if (Dem_DTCReadoutBuffer_TestCombinedEventSelected(Dem_Client_ClientAccess_GetReadoutBuffer(ClientId)) == TRUE)
  {
    lRetVal = Dem_Dcm_SRec_GetSize_CombinedEvent(ClientId, SizeOfFreezeFrame);                                                   /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }
  else
# endif
  {
    lRetVal = Dem_Dcm_SRec_GetSize_NormalEvent(ClientId, SizeOfFreezeFrame);                                                     /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }

  return lRetVal;
}
#endif

#if (DEM_CFG_SUPPORT_PID01 == STD_ON)
/* ****************************************************************************
 % Dem_Dcm_ReadDataOfPID01
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_ReadDataOfPID01(
  CONSTP2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  PID01value,
  CONST(uint8, AUTOMATIC) BufferSize
  )
{
  Std_ReturnType lReturn;
  if (Dem_Cfg_IsObdSupportedInVariant() == TRUE)
  {
    DEM_IGNORE_UNUSED_CONST_ARGUMENT(BufferSize)                                                                                   /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
    if (BufferSize < 4u)
    {
      Dem_Error_RunTimeCheckFailed(DEM_DCM_IMPLEMENTATION_FILENAME, __LINE__);                                                     /* SBSW_DEM_POINTER_RUNTIME_CHECK */
    }
    else
#endif
    {
      /*If major monitors is supported */
#if (DEM_CFG_SUPPORT_MAJOR_MONITORS == STD_ON)
      uint32 lPid01;

      /* Set all groups to not supported and not completed (not supported = 0, supported = 1, completed/na = 0, not completed = 1u) */
      lPid01 = 0x007000FFUL;

      /* If Event Availabilty is supported the configuration contains only engine type,
         otherwise supported state of readines groups is also provided */
      lPid01 |= Dem_Cfg_GlobalPid01SupportedMask();
#endif
      /* If OBDII is supported */
      if (Dem_Cfg_IsObdIISupportedInVariant() == TRUE)
      {
        /* If feature reset Confimred DTC on overflow or major monitors and event availablity is supported */
#if ((DEM_CFG_PROCESS_CDTC_ALL_DTC == STD_OFF) && \
        ((DEM_CFG_SUPPORT_MAJOR_MONITORS == STD_OFF) || (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_OFF)))
        Dem_Memory_AllocMemEntriesIterType lStoredEventsIter;
#endif
#if (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
        Dem_Cfg_ProcessedCombinedDTCGroupType lProcessedCombinedDTCGroups;
#endif

        Dem_EventIdType lConfirmedEvents;
        Dem_EventIdType lEventId;
        uint8 lGlobalMilState;
#if (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
        Dem_DTC_InitCombinedGroupProcessed(lProcessedCombinedDTCGroups);                                                           /* SBSW_DEM_POINTER_FORWARD_STACK */
#endif
        lConfirmedEvents = 0u;

#if ((DEM_CFG_PROCESS_CDTC_ALL_DTC == STD_ON) || \
        ((DEM_CFG_SUPPORT_MAJOR_MONITORS == STD_ON) && (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)))
        /* Scan for events in confirmed state */
        for (lEventId = Dem_Cfg_GlobalPrimaryFirst();
          lEventId <= Dem_Cfg_GlobalPrimaryLast();
          lEventId++)
        {
# if (DEM_CFG_SUPPORT_MAJOR_MONITORS == STD_ON && DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
          uint8 lReadinessGroup;
          lReadinessGroup = Dem_Cfg_EventReadinessGroup(lEventId);
          /* If event is available and assigned to a valid readiness group */
          if ((lReadinessGroup != DEM_CFG_READINESS_NONE)
            && (Dem_Event_TestEventUnavailable(lEventId) == FALSE))                                                                /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
          {
            /* Set readiness group to supported*/
            Dem_Util_SetReadinessGroupSupported(TRUE, lReadinessGroup, &lPid01);                                                   /* SBSW_DEM_POINTER_FORWARD_STACK */
          }
# endif
# if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
          if (lEventId != Dem_Cfg_GetMasterEvent(lEventId))
          { /* Don't match dependent combined events, only the group event */
            continue;
          }
# endif
#else
        /* Only the stored events are in confirmed state -> iterate over all stored events and count
        the number of OBD releated events */
        for (Dem_Memory_AllocMemEntriesChrono_IterInit(DEM_CFG_MEMORYID_PRIMARY, &lStoredEventsIter);                              /* SBSW_DEM_CALL_ITERATOR_POINTER */
          Dem_Memory_AllocMemEntriesChrono_IterExists(&lStoredEventsIter) == TRUE;                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */
          Dem_Memory_AllocMemEntriesChrono_IterNext(&lStoredEventsIter))                                                        /* SBSW_DEM_CALL_ITERATOR_POINTER */
        {
          /* Get EventId for current index */
          lEventId = Dem_MemoryEntry_GetEventId(
            Dem_MemoryEntry_GetId(Dem_Memory_AllocMemEntriesChrono_IterGetMemoryIndex(&lStoredEventsIter)));                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
          /* verify that a valid EventId was returned */
          if (Dem_Event_TestValidHandle(lEventId) == TRUE)
#endif
          { /* count Event if it is OBD related and confirmed bit is qualified */
            if ((Dem_Cfg_EventObdRelated(lEventId) == TRUE)
#if (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
              && (Dem_DTC_TestCombinedGroupProcessed(Dem_Cfg_EventCombinedGroup(lEventId), lProcessedCombinedDTCGroups) == FALSE) /* PRQA S 3415 */ /* MD_DEM_13.5_volatile */ /* SBSW_DEM_POINTER_FORWARD_STACK */
#endif
              )
            {
              uint8 lDtcStatus;
              lDtcStatus = Dem_DTC_GenerateExternalOnlyStatus(lEventId, Dem_DTC_GetDTCStatus(lEventId));
              if (Dem_UDSStatus_Test_CDTC(lDtcStatus) == TRUE)
              {
                lConfirmedEvents++;
              }
#if (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
              Dem_DTC_SetCombinedGroupProcessed(Dem_Cfg_EventCombinedGroup(lEventId), lProcessedCombinedDTCGroups);               /* SBSW_DEM_POINTER_FORWARD_STACK */
#endif
            }
          }
        }

        /* set max value if count exceeds 127 */
        if (lConfirmedEvents > 0x7fU)
        {
          lConfirmedEvents = 0x7fU;
        }

        if (Dem_Indicator_TestMilReportedActive() == TRUE)
        {
          lGlobalMilState = 0x80U;
        }
        else
        {
          lGlobalMilState = 0x00U;
        }

        /* MIL status and number of OBD relevant confirmed events */
        PID01value[0] = (uint8)((lGlobalMilState | (uint8)lConfirmedEvents));                                                      /* SBSW_DEM_POINTER_WRITE_ARGUMENT_BUFFER */
      }

      /* Otherwise if WWHOBD is supported */
      if (Dem_Cfg_IsWwhObdSupportedInVariant() == TRUE)
      {
      /* If major monitors and event availablity is supported */
#if (DEM_CFG_SUPPORT_MAJOR_MONITORS == STD_ON && DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
        Dem_EventIdType lEventId;
        for (lEventId = Dem_Cfg_GlobalPrimaryFirst();
          lEventId <= Dem_Cfg_GlobalPrimaryLast();
          lEventId++)
        {
          uint8 lReadinessGroup = Dem_Cfg_EventReadinessGroup(lEventId);
          /* If event is assigned to readiness group and available */
          if ((lReadinessGroup != DEM_CFG_READINESS_NONE)
            && (Dem_Event_TestEventUnavailable(lEventId) == FALSE)                                                                 /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
            )
          {
            /* Set readiness group to supported*/
            Dem_Util_SetReadinessGroupSupported(TRUE, Dem_Cfg_EventReadinessGroup(lEventId), &lPid01);                             /* SBSW_DEM_POINTER_FORWARD_STACK */
          }
        }
#endif
        PID01value[0] = 0x00u;                                                                                                     /* SBSW_DEM_POINTER_WRITE_ARGUMENT_BUFFER */
    }
       /* If major monitors is supported */
#if (DEM_CFG_SUPPORT_MAJOR_MONITORS == STD_ON)
      /* Get completed state of readiness groups and set value of remaining bytes in Pid01 (completed = 0, not completed = 1u) */
      lPid01 &= Dem_Mem_GetPid01CompletedMask();
      Dem_Data_SetStaticallyCalculatedReadinessStatus(&lPid01, DEM_DATA_PIDCONTEXT_PID01);                                         /* SBSW_DEM_POINTER_FORWARD_STACK */

      PID01value[1] = Dem_GetHiLoByte(lPid01);                                                                                     /* SBSW_DEM_POINTER_WRITE_ARGUMENT_BUFFER */
      PID01value[2] = Dem_GetLoHiByte(lPid01);                                                                                     /* SBSW_DEM_POINTER_WRITE_ARGUMENT_BUFFER */
      PID01value[3] = Dem_GetLoLoByte(lPid01);                                                                                     /* SBSW_DEM_POINTER_WRITE_ARGUMENT_BUFFER */
#else
      /* Otherwise set remaining bytes in Pid01 to static values (Byte B = 0x04, Byte C = 0x00, Byte D = 0x00) */
      PID01value[1] = 0x04u; /* Comprehensive component monitoring supported and ready */                                           /* SBSW_DEM_POINTER_WRITE_ARGUMENT_BUFFER */
      PID01value[2] = 0x00u; /* not supported */                                                                                    /* SBSW_DEM_POINTER_WRITE_ARGUMENT_BUFFER */
      PID01value[3] = 0x00u; /* not supported */                                                                                    /* SBSW_DEM_POINTER_WRITE_ARGUMENT_BUFFER */
#endif
    }
    lReturn = E_OK;
  }
  else
  {
    lReturn = E_NOT_OK;
  }
  return lReturn;
}                                                                                                                                /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STPTH */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Dcm_GetStatusOfSelectedDTC
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_GetStatusOfSelectedDTC(
  uint8  ClientId,
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  DTCStatus
  )
{
  Std_ReturnType lReturnValue;
  uint8 lMemoryId;

  lMemoryId = Dem_Client_ClientAccess_GetSelectedMemoryId(ClientId);
  switch (lMemoryId)
  {
  case DEM_CFG_MEMORYID_PERMANENT:
    lReturnValue = DEM_NO_SUCH_ELEMENT;
    break;
  case DEM_CFG_MEMORYID_PRIMARY:
  case DEM_CFG_MEMORYID_SECONDARY:
    {
      Dem_EventIdType lEventId;

      lEventId = Dem_Client_ClientAccess_GetSelectedEventId(ClientId);

      if (lEventId != DEM_EVENT_INVALID)
      {
        if (Dem_DTC_TestSuppressionOnDtcRetrieval(lEventId) == TRUE)
        {
          lReturnValue = DEM_WRONG_DTC;
        }
        else
        {
          *DTCStatus = Dem_DTC_GetExternalDTCStatus(lEventId);                                                                   /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
          lReturnValue = E_OK;
        }
      }
      else
      {
        lReturnValue = E_NOT_OK;
      }
    }
    break;

  default:
    lReturnValue = E_NOT_OK;
    break;
  }
  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Dcm_GetSeverityOfSelectedDTC
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_GetSeverityOfSelectedDTC(
  CONST(uint8, AUTOMATIC)  ClientId,
  P2VAR(Dem_DTCSeverityType, AUTOMATIC, DEM_DCM_DATA)  DTCSeverity
  )
{
  Std_ReturnType lReturnValue;
  Dem_EventIdType lEventId;

  lEventId = Dem_Client_ClientAccess_GetSelectedEventId(ClientId);

  if (lEventId != DEM_EVENT_INVALID)
  {
    if (Dem_DTC_TestSuppressionOnDtcRetrieval(lEventId) == TRUE)
    {
      lReturnValue = DEM_WRONG_DTC;
    }
    else
    {
      if ( (Dem_DTCReporting_TestObdHideOccurrences() == TRUE)
        && (Dem_Cfg_EventSignificance(lEventId) == DEM_CFG_EVENT_SIGNIFICANCE_OCCURRENCE)
        && (Dem_Cfg_EventObdRelated(lEventId) == TRUE) )
      { /* Special case - skip Dependent OBD DTCs */
        lReturnValue = DEM_WRONG_DTC;
      }
      else
      {
        *DTCSeverity = Dem_Cfg_EventSeverity(lEventId);                                                                          /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
        lReturnValue = E_OK;
      }
    }
  }
  else
  {
    lReturnValue = E_NOT_OK;
  }

  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Dcm_GetFunctionalUnitOfSelectedDTC
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_GetFunctionalUnitOfSelectedDTC(
  CONST(uint8, AUTOMATIC)  ClientId,
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  DTCFunctionalUnit
  )
{
  Std_ReturnType lReturnValue;
  Dem_EventIdType lEventId;

  lEventId = Dem_Client_ClientAccess_GetSelectedEventId(ClientId);

  if (lEventId != DEM_EVENT_INVALID)
  {
    if (Dem_DTC_TestSuppressionOnDtcRetrieval(lEventId) == TRUE)
    {
      lReturnValue = DEM_WRONG_DTC;
    }
    else
    {
      if ( (Dem_DTCReporting_TestObdHideOccurrences() == TRUE)
        && (Dem_Cfg_EventSignificance(lEventId) == DEM_CFG_EVENT_SIGNIFICANCE_OCCURRENCE)
        && (Dem_Cfg_EventObdRelated(lEventId) == TRUE) )
      { /* Special case - skip Dependent OBD DTCs */
        lReturnValue = DEM_WRONG_DTC;
      }
      else
      {
        *DTCFunctionalUnit = Dem_Cfg_EventFunctionalUnit(lEventId);                                                              /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
        lReturnValue = E_OK;
      }
    }
  }
  else
  {
    lReturnValue = E_NOT_OK;
  }

  return lReturnValue;
}
#endif

/* ****************************************************************************
 % Dem_Dcm_GetEventIdOfSelectedDTC
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_GetEventIdOfSelectedDTC(
  CONST(uint8, AUTOMATIC)  ClientId,
  P2VAR(Dem_EventIdType, AUTOMATIC, DEM_APPL_DATA)  EventId
  )
{
  Std_ReturnType lReturnValue;
  Dem_EventIdType lEventId;

  lEventId = Dem_Client_ClientAccess_GetSelectedEventId(ClientId);

  if (lEventId != DEM_EVENT_INVALID)
  {
    *EventId = lEventId;                                                                                                         /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    lReturnValue = E_OK;
  }
  else
  {
    lReturnValue = E_NOT_OK;
  }

  return lReturnValue;
}

#if ((DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_WWHOBD == STD_ON) && (DEM_CFG_SUPPORT_PID91 == STD_ON))
/* ****************************************************************************
 % Dem_Dcm_TranslateActivationMode
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Dcm_TranslateActivationMode(
  CONST(Dem_IndicatorStatusType, AUTOMATIC)  ActivationMode
  )
{
  uint8 lReturnValue;

  switch (ActivationMode)
  {
  case DEM_INDICATOR_CONTINUOUS:
    lReturnValue = 0x03U;
    break;
  case DEM_INDICATOR_SHORT:
    lReturnValue = 0x02U;
    break;
  case DEM_INDICATOR_ON_DEMAND:
    lReturnValue = 0x01U;
    break;
  case DEM_INDICATOR_OFF:
    lReturnValue = 0x00U;
    break;
  default:
    Dem_Error_ReportError(DEM_INTERNAL_APIID, DEM_E_INCONSISTENT_STATE);
    lReturnValue = 0x00U;
    break;
  }
  return lReturnValue;
}
#endif
/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_DCM_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Dcm_Implementation.h
 *********************************************************************************************************************/
