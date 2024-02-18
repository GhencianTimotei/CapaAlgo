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
/*! \addtogroup Dem_ERec
 *  \{
 *  \file       Dem_ERec_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) Implementation file for processing ERec specific DCM service requests 
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_EREC_IMPLEMENTATION_H)
#define DEM_EREC_IMPLEMENTATION_H

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
#include "Dem_ERec_Interface.h"

/* Includes to access public functions belonging to other (top level)/ (logical)/- units to be used by this Unit */
/* ------------------------------------------------------------------------- */
#include "Dem_FaultMemory_Interface.h"
#include "Dem_Core_Interface.h"
#include "Dem_Client_Interface.h"
#include "Dem_DataReport_Interface.h"
#include "Dem_DTCReadoutBuffer_Interface.h"
#include "Dem_Infrastructure_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*! Filename declaration */
#define DEM_EREC_IMPLEMENTATION_FILENAME "Dem_ERec_Implementation.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/* ********************************************************************************************************************

 *  SUBCOMPONENT PRIVATE FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_ERec_Private Private Methods
 * \{
 */
/* ****************************************************************************
 * Dem_Dcm_ERec_ERecIter_Exists
 *****************************************************************************/
/*!
 * \brief         Test if the iterator points to a valid element
 *
 * \details       Test if the iterator points to a valid element
 *
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \return        TRUE
 *                Return value of Dem_Dcm_ERec_ERecIter_Get() is valid
 * \return        FALSE
 *                Return value of Dem_Dcm_ERec_ERecIter_Get() is invalid
 *
 * \pre           IterPtr has been initialized
 *                Feature Service 0x19 16 or 1A is enabled and extended data records are
 *                configured.
 *
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Dcm_ERec_ERecIter_Exists(
  CONSTP2CONST(Dem_Dcm_ERec_ERecNumberIterType, AUTOMATIC, AUTOMATIC)  IterPtr
);

/* ****************************************************************************
 * Dem_Dcm_ERec_ERecIter_Get
 *****************************************************************************/
/*!
 * \brief         Get the element pointed to by the iterator
 *
 * \details       Get the element pointed to by the iterator
 *
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \return        Event Id that has Extended Data Record 
 *                configured
 *
 * \pre           IterPtr has been initialized
 *                Feature Service 0x19 16 or 1A is enabled and extended data records are
 *                configured.
 *
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Dcm_ERec_ERecIter_Get(
  CONSTP2CONST(Dem_Dcm_ERec_ERecNumberIterType, AUTOMATIC, AUTOMATIC)  IterPtr
);

/* ****************************************************************************
 * Dem_Dcm_ERec_ERecIter_Init
 *****************************************************************************/
/*!
 * \brief         Initialize the iterator
 *
 * \details       Initializes the iterator to enumerate data elements
 *
 * \param[in]     ERecDataCollectionTableIndex
 *                The index of the extended data record in the data collection table
 * \param[out]    IterPtr
 *                Pointer to the iterator
 *
 * \pre           Feature Service 0x19 16 or 1A is enabled and extended data records are
 *                configured.
 *
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Dcm_ERec_ERecIter_Init(
  Dem_Cfg_ERecIndexType ERecDataCollectionTableIndex,
  CONSTP2VAR(Dem_Dcm_ERec_ERecNumberIterType, AUTOMATIC, AUTOMATIC)  IterPtr
);

/* ****************************************************************************
* Dem_Dcm_ERec_ERecIter_Invalidate
*****************************************************************************/
/*!
* \brief         Invalidates the iterator
*
* \details       Invalidates the iterator
*
* \param[out]    IterPtr
*                Pointer to the iterator
*
* \pre           Feature Service 0x19 16 or 1A is enabled and extended data records are
 *                configured.
* \config        -
*
* \context       TASK|ISR2
* \synchronous   TRUE
* \reentrant     TRUE
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Dcm_ERec_ERecIter_Invalidate(
  CONSTP2VAR(Dem_Dcm_ERec_ERecNumberIterType, AUTOMATIC, AUTOMATIC)  IterPtr
);

/* ****************************************************************************
 * Dem_Dcm_ERec_ERecIter_Next
 *****************************************************************************/
/*!
 * \brief         Move the iterator to the next element
 *
 * \details       Move the iterator to the next element
 *
 * \param[in,out] IterPtr
 *                Pointer to the iterator
 *
 * \pre           IterPtr has been initialized
 *                Feature Extended Data Record and Service 0x19 16 or 1A is enabled
 * \config        -
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Dcm_ERec_ERecIter_Next(
  CONSTP2VAR(Dem_Dcm_ERec_ERecNumberIterType, AUTOMATIC, AUTOMATIC)  IterPtr
);


/* ****************************************************************************
 % Dem_Dcm_ERec_DataCollectionERecIter_Exists
 *****************************************************************************/
/*!
 * \brief         Test if the iterator points to a valid element
 *
 * \details       Test if the iterator points to a valid element
 *
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \return        TRUE
 *                Return value of Dem_Dcm_ERec_DataCollectionERecIter_Get() is valid
 * \return        FALSE
 *                Return value of Dem_Dcm_ERec_DataCollectionERecIter_Get() is invalid
 *
 * \pre           IterPtr has been initialized
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Dcm_ERec_DataCollectionERecIter_Exists(
  CONSTP2CONST(Dem_Dcm_ERec_DataCollectionERecIterType, AUTOMATIC, AUTOMATIC)  IterPtr
);

/* ****************************************************************************
 % Dem_Dcm_ERec_DataCollectionERecIter_Get
 *****************************************************************************/
/*!
 * \brief         Get the element pointed to by the iterator
 *
 * \details       Get the element pointed to by the iterator
 *
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \return        Event Id that has Extended Data Record
 *                configured
 *
 * \pre           IterPtr has been initialized
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_DidIndexType, DEM_CODE)
Dem_Dcm_ERec_DataCollectionERecIter_Get(
  CONSTP2CONST(Dem_Dcm_ERec_DataCollectionERecIterType, AUTOMATIC, AUTOMATIC)  IterPtr
);

/* ****************************************************************************
 % Dem_Dcm_ERec_DataCollectionERecIter_Init
 *****************************************************************************/
/*!
 * \brief         Initialize the iterator
 *
 * \details       Initializes the iterator to enumerate data elements
 *
 * \param[in]     ERecIndex
 *                The index of the extended data record in the data collection table
 * \param[out]    IterPtr
 *                Pointer to the iterator
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Dcm_ERec_DataCollectionERecIter_Init(
  CONSTP2VAR(Dem_Dcm_ERec_DataCollectionERecIterType, AUTOMATIC, AUTOMATIC)  IterPtr
);

/* ****************************************************************************
 % Dem_Dcm_ERec_DataCollectionERecIter_Next
 *****************************************************************************/
/*!
 * \brief         Move the iterator to the next element
 *
 * \details       Move the iterator to the next element
 *
 * \param[in,out] IterPtr
 *                Pointer to the iterator
 *
 * \pre           IterPtr has been initialized
 * \config        -
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Dcm_ERec_DataCollectionERecIter_Next(
  CONSTP2VAR(Dem_Dcm_ERec_DataCollectionERecIterType, AUTOMATIC, AUTOMATIC)  IterPtr
);

/* ****************************************************************************
 * Dem_Dcm_ERec_0x1916_InitGlobalERecNumberFilter
 *****************************************************************************/
/*!
 * \brief         Initializes Global ERec filter part.
 *
 * \details       Initializes Global Extended Data Record filter part.
 *
 * \param[in]     ExtendedDataFilterPtr
 *                Pointer to an ExtendedDataFilter.
 *
 * \pre           Feature Service 0x19 16 is enabled and extended data records are
 *                configured.
 *
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Dcm_ERec_0x1916_InitGlobalERecNumberFilter(
  CONSTP2VAR(Dem_Cfg_ExtendedDataRecordIterator_FilterType, AUTOMATIC, AUTOMATIC) ExtendedDataFilterPtr
);

/* ****************************************************************************
 * Dem_Dcm_ERec_0x1916_InitStoredEntryERecNumberFilter
 *****************************************************************************/
/*!
 * \brief         Initializes filter data for 'internal' or 'user' ERec.
 *
 * \details       Initializes filter data for 'internal' or 'user' ERec.
 *
 * \param[in]     ExtendedDataFilterPtr
 *                Pointer to an ExtendedDataFilter.
 *
 * \pre           Feature Service 0x19 16 is enabled and extended data records are
 *                configured.
 *
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Dcm_ERec_0x1916_InitStoredEntryERecNumberFilter(
  CONSTP2VAR(Dem_Cfg_ExtendedDataRecordIterator_FilterType, AUTOMATIC, AUTOMATIC) ExtendedDataFilterPtr
  );

/* ****************************************************************************
 * Dem_Dcm_ERec_0x1916_CalcNumberofGlobalERecs
 *****************************************************************************/
 /*!
 * \brief         Provides the number of global extended data records.
 *
 * \details       Provides the number of global extended data records.
 *
 * \param[in]     ERecDataCollectionTableIdx
 *                Index of extended data record in DataCollectionTable.
 * \param[out]    NumberOfFilteredRecords
 *                Pointer to receive the number of filtered records.
 *
 * \pre           Feature Service 0x19 16 is enabled and extended data records are
 *                configured.
 *
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Dcm_ERec_0x1916_CalcNumberofGlobalERecs(
  Dem_Cfg_ERecIndexType ERecDataCollectionTableIdx,
  P2VAR(uint16, AUTOMATIC, DEM_DCM_DATA)  NumberOfFilteredRecords
);

/* ****************************************************************************
 * Dem_Dcm_ERec_0x1916_CalcNumberofStoredERecs
 *****************************************************************************/
/*!
 * \brief         Provides the number of stored extended data records.
 *
 * \details       Provides the number of stored extended data records.
 *
 * \param[in]     ERecDataCollectionTableIdx
 *                Index of extended data record in DataCollectionTable.
 * \param[out]    NumberOfFilteredRecords
 *                Pointer to receive the number of filtered records.
 *
 * \pre           Feature Service 0x19 16 is enabled and extended data records are
 *                configured.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Dcm_ERec_0x1916_CalcNumberofStoredERecs(
  Dem_Cfg_ERecIndexType ERecDataCollectionTableIdx,
  P2VAR(uint16, AUTOMATIC, DEM_DCM_DATA)  NumberOfFilteredRecords
);


/* ****************************************************************************
 * Dem_Dcm_ERec_0x1916_GetNextGlobalERecData
 *****************************************************************************/
/*!
 * \brief         Provides the next global extended data record data,
 *                when filtered by record number.
 *
 * \details       Provides the next global extended data record data,
 *                when filtered by record number.
 *
 * \param[in]     ExtendedDataFilterId
 *                The extended data record filter identifier
 * \param[out]    EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[out]    DestBuffer
 *                Destination buffer, in which the ERec data is written
 * \param[in,out] BufSize
 *                In: Size of Buffer
 *                Out: Number of written byte
 *
 * \return        E_OK
 *                Data was found and returned
 * \return        DEM_NO_SUCH_ELEMENT
 *                The requested record is not available
 * \return        DEM_PENDING
 *                Data is concurrently updated, try readout later
 * \return        DEM_BUFFER_TOO_SMALL
 *                Size of given buffer is smaller than size of requested record
 *
 * \pre           Feature Service 0x19 16 is enabled and extended data records are
 *                configured.
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE for different ExtendedDataFilterId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_ERec_0x1916_GetNextGlobalERecData(
  Dem_Dcm_ERec_0x1916_RecordNumberFilter_HandleType ExtendedDataFilterId,
  P2VAR(Dem_EventIdType, AUTOMATIC, DEM_DCM_DATA) EventId,
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA) DestBuffer,
  P2VAR(uint16, AUTOMATIC, DEM_DCM_DATA) BufSize
);

/* ****************************************************************************
 * Dem_Dcm_ERec_0x1916_GetNextStoredERecData
 *****************************************************************************/
/*!
 * \brief         Provides the next stored extended data record data,
 *                when filtered by record number.
 *
 * \details       Provides the next stored extended data record data,
 *                when filtered by record number.
 *
 * \param[in]     ExtendedDataFilterId
 *                The extended data record filter identifier
 * \param[out]    EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[out]    DestBuffer
 *                Destination buffer, in which the ERec data is written
 * \param[in,out] BufSize
 *                In: Size of Buffer
 *                Out: Number of written byte
 *
 * \return        E_OK
 *                Data was found and returned
 * \return        DEM_NO_SUCH_ELEMENT
 *                The requested record is not available
 * \return        DEM_PENDING
 *                Data is concurrently updated, try readout later
 * \return        DEM_BUFFER_TOO_SMALL
 *                Size of given buffer is smaller than size of requested record
 *
 * \pre           Feature Service 0x19 16 is enabled and extended data records are
 *                configured.
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE for different ExtendedDataFilterId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_ERec_0x1916_GetNextStoredERecData(
  Dem_Dcm_ERec_0x1916_RecordNumberFilter_HandleType ExtendedDataFilterId,
  P2VAR(Dem_EventIdType, AUTOMATIC, DEM_DCM_DATA) EventId,
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA) DestBuffer,
  P2VAR(uint16, AUTOMATIC, DEM_DCM_DATA) BufSize
);

/* ****************************************************************************
 * Dem_Dcm_ERec_0x1916_CopyERecs
 *****************************************************************************/
/*!
 * \brief         Provides the next extended data record data
 *
 * \details       Provides the next stored extended data record data for
 *                record number filtering.
 *
 * \param[in]     ERecDataCollectionTableIdx
 *                Index of extended data record in DataCollectionTable
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     ExtendedEntryIndex
 *                Index to 'user' extended data record in event entry
 * \param[out]    EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[out]    DestinationBuffer
 *                Destination buffer, structure in which the ERec data 
 *                and used buffer size is written.
 * \return        E_OK
 *                Data was found and returned
 * \return        DEM_NO_SUCH_ELEMENT
 *                The requested record is not available
 * \return        DEM_PENDING
 *                Data is concurrently updated, try readout later
 * \return        DEM_BUFFER_TOO_SMALL
 *                Size of given buffer is smaller than size of requested record
 *
 * \pre           Feature Service 0x19 16 is enabled and extended data records are
 *                configured.
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_ERec_0x1916_CopyERecs(
  Dem_Cfg_ERecIndexType ERecDataCollectionTableIdx,
  Dem_Cfg_MemoryEntryHandleType MemoryEntryId,
  uint8 ExtendedEntryIndex,
  Dem_EventIdType EventId,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  );

/* ****************************************************************************
 * Dem_Dcm_ERec_0x1916_GetRecordNumberFilter
 *****************************************************************************/
/*!
 * \brief         Get the RecordNumberFilter referenced by filter id.
 *
 * \details       Get the RecordNumberFilter referenced by filter id.
 *
 * \param[in]     ExtendedDataFilterId
 *                The ExtendedDataFilter identifier
 *
 * \return        ExtendedDataFilter specified by the identifier
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_ExtendedDataRecordIterator_FilterType, DEM_CODE)
Dem_Dcm_ERec_0x1916_GetRecordNumberFilter(
  CONST(Dem_Dcm_ERec_0x1916_RecordNumberFilter_HandleType, AUTOMATIC)  ExtendedDataFilterId
);

/* ****************************************************************************
 * Dem_Dcm_ERec_0x1916_SetRecordNumberFilter
 *****************************************************************************/
/*!
 * \brief         Set the RecordNumberFilter.
 *
 * \details       Set the RecordNumberFilter for a certain id.
 *
 * \param[in]     ExtendedDataFilterId
 *                The ExtendedDataFilter identifier
 * \param[in]     ExtendedDataFilterPtr
 *                Pointer to a ExtendedDataFilter data structure, which shall be copied
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Dcm_ERec_0x1916_SetRecordNumberFilter(
  CONST(Dem_Dcm_ERec_0x1916_RecordNumberFilter_HandleType, AUTOMATIC)  ExtendedDataFilterId,
  CONSTP2CONST(Dem_Cfg_ExtendedDataRecordIterator_FilterType, AUTOMATIC, AUTOMATIC)  ExtendedDataFilterPtr
);

/* ****************************************************************************
 * Dem_Dcm_ERec_FindDataCollectionTableIndexByRecordnumber
 *****************************************************************************/
/*!
 * \brief         Find a certain ERec number in the DataCollectionTable.
 *
 * \details       Find a certain extended data record number in the DataCollectionTable.
 *
 * \param[in]     RecordNumber
 *                Record number to find in DataCollectionTable
 * \param[out]    DataCollectionIndex
 *                Index of the record number in DataCollectionTable
 *
 * \return        TRUE
 *                Record number was found in the DataCollectionTable
 *                FALSE
 *                Record number was not found in the DataCollectionTable
 *
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Dcm_ERec_FindDataCollectionTableIndexByRecordnumber(
  uint8 RecordNumber,
  CONSTP2VAR(Dem_Cfg_ERecIndexType, AUTOMATIC, AUTOMATIC) DataCollectionIndex
);


#if ((DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_ERECS == STD_ON)\
    && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 * Dem_Dcm_ERec_CopyERec_FromSubEventMemoryEntry
 *****************************************************************************/
/*!
 * \brief         Copies the requested extended data record from a selected
 *                memory entry to the destination buffer.
 *
 * \details       Copies the requested extended data record from a selected
 *                memory entry to the destination buffer. Subevent memory entry
 *                is identified by the index to the readout buffer array.
 *
 * \param[in]     ERecId
 *                Identifier of the requested extended data record
 * \param[in]     ReadoutBufferId
 *                Unique handle of the readout buffer
 * \param[in]     ReadoutBufferDataIndex
 *                Index to ReadoutBufferData in ReadoutBuffer
 * \param[in,out] DestinationBuffer
 *                Pointer to DestinationBuffer structure
 *
 * \pre           - A DTC belonging to combined group type 2 has been selected
 *                  and copied to readout buffer
 *                - Function must be only called for copying User and Internal
 *                  extended data records from a subevent memory entry
 *                - Caller must ensure that the requested records are stored
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON &&
 *                DEM_CFG_SUPPORT_ERECS == STD_ON &&
 *                DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ReadoutBufferIds
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Dcm_ERec_CopyERec_FromSubEventMemoryEntry(
  CONST(uint8, AUTOMATIC) ERecId,
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(Dem_DTCReadoutBuffer_ReadoutBufferDataIndexType, AUTOMATIC)  ReadoutBufferDataIndex,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
);
#endif


#if ((DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_ERECS == STD_ON)\
    && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 * Dem_Dcm_ERec_CopyERec_CombinedDTC
 *****************************************************************************/
/*!
 * \brief         Reads the requested extended data record from all available
 *                subevents of a combined DTC
 *
 * \details       Reads the requested extended data record from all available
 *                subevents of a combined DTC
 *
 * \param[in]     ERecId
 *                Extended Data Record Identifier to be copied
 * \param[in]     ERecEntryIndex
 *                Index of the extended data record inside the Dem data collection
 *                table
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
 *                DEM_CFG_SUPPORT_ERECS == STD_ON &&
 *                DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ReadoutBufferIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_ERec_CopyERec_CombinedDTC(
  CONST(uint8, AUTOMATIC) ERecId,
  CONST(Dem_Cfg_ERecIndexType, AUTOMATIC) ERecEntryIndex,
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
);
#endif


#if ((DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 * Dem_Dcm_ERec_ReadNextRecord_CombinedEvent
 *****************************************************************************/
/*!
 * \brief         Validates the request to get an extended data record belonging
 *                to a combined DTC in UDS format and copies the data.
 *
 * \details       Validates the request to get an extended data record belonging
 *                to a combined DTC in UDS format and copies data into the given buffer.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 * \param[out]    DestBuffer
 *                Pointer to the destination buffer
 * \param[in,out] BufSize
 *                In: Available space in the receiving buffer
 *                Out: Number of written bytes.
 *
 * \return        E_OK
 *                Read extended data record successful.
 * \return        DEM_BUFFER_TOO_SMALL
 *                Provided buffer size too small.
 * \return        DEM_NO_SUCH_ELEMENT
 *                Record number is not supported by configuration and
 *                therefore invalid
 *
 * \pre           Function must be only invoked when a combined DTC is selected
 * \config        (DEM_CFG_SUPPORT_DCM == STD_ON)
 *                && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ClientIds.
 ****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_ERec_ReadNextRecord_CombinedEvent(
  CONST(uint8, AUTOMATIC)  ClientId,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
);
#endif


#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_Dcm_ERec_ReadNextRecord_NormalEvent
 *****************************************************************************/
/*!
 * \brief         Validates the request to get an extended data record in UDS
 *                format and copies the data.
 *
 * \details       Copies data into the given buffer.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 * \param[out]    DestBuffer
 *                Pointer to the destination buffer
 * \param[in,out] BufSize
 *                In: Available space in the receiving buffer
 *                Out: Number of written bytes.
 *
 * \return        E_OK
 *                Read extended data record successful.
 * \return        DEM_BUFFER_TOO_SMALL
 *                provided buffer size too small.
 * \return        DEM_NO_SUCH_ELEMENT
 *                Record number is not supported by configuration and
 *                therefore invalid
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ClientIds.
 ****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_ERec_ReadNextRecord_NormalEvent(
  CONST(uint8, AUTOMATIC)  ClientId,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
);
#endif


#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_Dcm_ERec_GetSize_NormalEvent
 *****************************************************************************/
/*!
 * \brief         Get the size of one or all extended data record(s) belonging
 *                to a non combined event.
 *
 * \details       Get the size of one or all extended data record(s) belonging
 *                to a non combined event.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 * \param[out]    SizeOfExtendedDataRecord
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
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_ERec_GetSize_NormalEvent(
  CONST(uint8, AUTOMATIC) ClientId,
  CONSTP2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  SizeOfExtendedDataRecord
);
#endif


#if ((DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 * Dem_Dcm_ERec_GetSize_CombinedEvent
 *****************************************************************************/
/*!
 * \brief         Get the size of one or all extended data record(s) belonging
 *                to a combined DTC.
 *
 * \details       Get the size of one or all extended data record(s) belonging
 *                to a combined DTC.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 * \param[out]    SizeOfExtendedDataRecord
 *                Size of selected extended data record in bytes.
 *
 * \return        E_OK
 *                Data was found and returned
 * \return        DEM_NO_SUCH_ELEMENT
 *                The requested record is not available
 *
 * \pre           A memory entry has to be locked for Dcm readout
 * \config        (DEM_CFG_SUPPORT_DCM == STD_ON)
 *                && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_ERec_GetSize_CombinedEvent(
  CONST(uint8, AUTOMATIC) ClientId,
  CONSTP2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  SizeOfExtendedDataRecord
);
#endif


#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_ERECS == STD_ON)
/* ****************************************************************************
 * Dem_Dcm_ERec_TestRecordMatch
 *****************************************************************************/
/*!
 * \brief         Test whether filter for extended data record(s) matches
 *
 * \details       Return whether the given RecordNumber is accepted by the
 *                RecordNumberFilter set in Readoutbuffer
 *                Following RecordNumbers are accepted:
 *                 - 0xFF: Records 0x01 .. 0xEF are always accepted
 *                 - 0xFE: Records 0x90 .. 0xEF are always accepted
 *                 - otherwise only RecordNumbers which equal the RecordNumberFilter
 * \param[in]     ReadoutBufferId
 *                Unique handle of the readout buffer
 * \param[in]     RecordNumber
 *                Extended data record number
 *
 * \return        TRUE
 *                The filter matches
 *
 * \return        FALSE
 *                The filter does not match
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON &&
 *                DEM_CFG_SUPPORT_ERECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE boolean Dem_Dcm_ERec_TestRecordMatch(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(uint8, AUTOMATIC) RecordNumber
);
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_ERECS == STD_ON)
/* ****************************************************************************
 * Dem_Dcm_ERec_CopyNextRecord
 *****************************************************************************/
/*!
 * \brief         Copies an extended data record into the given buffer
 *
 * \details       Copies records with types "internal", "global" and "user"
 *
 * \param[in]     ReadoutBufferId
 *                Unique handle of the readout buffer
 * \param[in,out] DestinationBuffer
 *                Pointer to DestinationBuffer context
 * \param[in]     ReadoutBufferDataIndex
 *                Index to ReadoutBufferData inside the ReadoutBuffer
 *
 *
 * \return        E_OK
 *                Reading succeeded
 *
 * \return        DEM_BUFFER_TOO_SMALL
 *                provided buffer size too small
 *
 * \return        DEM_NO_SUCH_ELEMENT
 *                Record number is not supported by configuration and
 *                therefore invalid
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON &&
 *                DEM_CFG_SUPPORT_ERECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_ERec_CopyNextRecord(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(Dem_DTCReadoutBuffer_ReadoutBufferDataIndexType, AUTOMATIC)  ReadoutBufferDataIndex
);
#endif


#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_ERECS == STD_ON)
/* ****************************************************************************
 * Dem_Dcm_ERec_CalculateSize
 *****************************************************************************/
/*!
 * \brief         Calculates the size of an extended data record
 *
 * \details       Calculates the size of an extended data record
 *
 * \param[in]     CfgERecIndex
 *                Handle to Extended Data Record descriptor table
 * \param[in]     ReadoutBufferId
 *                Handle to readout buffer
 * \param[in]     MemoryEntryId
 *                Handle to memory entry
 * \param[in]     ExtendedEntryIndex
 *                Index of the extended data record
 *
 * \return        E_OK
 *                Data was found and returned
 * \return        DEM_NO_SUCH_ELEMENT
 *                The requested record is not available
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON &&
 *                DEM_CFG_SUPPORT_ERECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Dcm_ERec_CalculateSize(
  CONST(Dem_Cfg_ERecIndexType, AUTOMATIC) CfgERecIndex,
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC)  ExtendedEntryIndex
);
#endif


#if ((DEM_CFG_SUPPORT_DCM == STD_ON)\
    && (DEM_CFG_SUPPORT_ERECS == STD_ON)\
    && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 * Dem_Dcm_ERec_CalculateSizeSingleERec_CombinedDTC
 *****************************************************************************/
/*!
 * \brief         Calculates the size of an extended data record over all
 *                subevents of a combined DTC
 *
 * \details       Calculates the size of an extended data record over all
 *                subevents of a combined DTC
 *
 * \param[in]     ERecId
 *                Identifier of the extended data record
 * \param[in]     ERecEntryIndex
 *                Index of the extended data record in the Dem_Cfg_DataCollectionTable
 * \param[in]     ReadoutBufferId
 *                Handle to readout buffer
 * \param[in]     CombinedGroupId
 *                Identifier of the combined DTC group
 *
 * \return        Size of the requested extended data record
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON &&
 *                DEM_CFG_SUPPORT_ERECS == STD_ON &&
 *                DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different clients (ReadoutBuffer Ids)
 *****************************************************************************/
DEM_LOCAL FUNC(uint16, DEM_CODE)
Dem_Dcm_ERec_CalculateSizeSingleERec_CombinedDTC(
  CONST(uint8, AUTOMATIC)  ERecId,
  CONST(Dem_Cfg_ERecIndexType, AUTOMATIC)  ERecEntryIndex,
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC) CombinedGroupId
);
#endif

 /* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/

 /* ****************************************************************************
 % Dem_Dcm_ERec_ERecIter_Exists
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Dcm_ERec_ERecIter_Exists(                                                                                                    /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONSTP2CONST(Dem_Dcm_ERec_ERecNumberIterType, AUTOMATIC, AUTOMATIC)  IterPtr
)
{
  return (boolean)(IterPtr->mIdx < IterPtr->mEndIdx);
}

/* ****************************************************************************
 % Dem_Dcm_ERec_ERecIter_Get
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Dcm_ERec_ERecIter_Get(
  CONSTP2CONST(Dem_Dcm_ERec_ERecNumberIterType, AUTOMATIC, AUTOMATIC)  IterPtr
)
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr);                                                                                     /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return Dem_Cfg_GetEventTable_ERec2EventIdInd(IterPtr->mIdx);
}

/* ****************************************************************************
 % Dem_Dcm_ERec_ERecIter_Init
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Dcm_ERec_ERecIter_Init(
  Dem_Cfg_ERecIndexType ERecDataCollectionTableIndex,
  CONSTP2VAR(Dem_Dcm_ERec_ERecNumberIterType, AUTOMATIC, AUTOMATIC)  IterPtr
)
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(ERecDataCollectionTableIndex);                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  IterPtr->mIdx = Dem_Cfg_GetEventTable_ERec2EventIdIndStartIdxOfDataCollectionTable(ERecDataCollectionTableIndex);              /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  IterPtr->mEndIdx = Dem_Cfg_GetEventTable_ERec2EventIdIndEndIdxOfDataCollectionTable(ERecDataCollectionTableIndex);             /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}

/* ****************************************************************************
% Dem_Dcm_ERec_ERecIter_Invalidate
*****************************************************************************/
/*!
* Internal comment removed.
 *
 *
*/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Dcm_ERec_ERecIter_Invalidate(
  CONSTP2VAR(Dem_Dcm_ERec_ERecNumberIterType, AUTOMATIC, AUTOMATIC)  IterPtr
)
{
  IterPtr->mIdx = DEM_CFG_NO_DATAELEMENTTABLECOL2ELMTINDSTARTIDXOFDATACOLLECTIONTABLE;                                             /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  IterPtr->mEndIdx = DEM_CFG_NO_DATAELEMENTTABLECOL2ELMTINDENDIDXOFDATACOLLECTIONTABLE;                                            /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}

/* ****************************************************************************
 % Dem_Dcm_ERec_ERecIter_Next
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Dcm_ERec_ERecIter_Next(                                                                                                      /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONSTP2VAR(Dem_Dcm_ERec_ERecNumberIterType, AUTOMATIC, AUTOMATIC)  IterPtr                                                     /* PRQA S 3673 */ /* MD_DEM_8.13_fp */
)
{
  IterPtr->mIdx += 1u;                                                                                                           /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}

/* ****************************************************************************
 % Dem_Dcm_ERec_DataCollectionERecIter_Exists
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Dcm_ERec_DataCollectionERecIter_Exists(                                                                                      /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONSTP2CONST(Dem_Dcm_ERec_DataCollectionERecIterType, AUTOMATIC, AUTOMATIC)  IterPtr
)
{
  return (boolean)(IterPtr->mIdx < IterPtr->mEndIdx);
}

/* ****************************************************************************
 % Dem_Dcm_ERec_DataCollectionERecIter_Get
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_DidIndexType, DEM_CODE)
Dem_Dcm_ERec_DataCollectionERecIter_Get(                                                                                         /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONSTP2CONST(Dem_Dcm_ERec_DataCollectionERecIterType, AUTOMATIC, AUTOMATIC)  IterPtr
)
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return Dem_Cfg_GetDataCollectionTableErec2CollInd(IterPtr->mIdx);
}

/* ****************************************************************************
 % Dem_Dcm_ERec_DataCollectionERecIter_Init
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Dcm_ERec_DataCollectionERecIter_Init(                                                                                        /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONSTP2VAR(Dem_Dcm_ERec_DataCollectionERecIterType, AUTOMATIC, AUTOMATIC)  IterPtr
)
{
  IterPtr->mIdx    = Dem_Cfg_GetDataCollectionTableErec2CollIndStartIdxOfExtendedDataRecordTable(0);                             /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  IterPtr->mEndIdx = Dem_Cfg_GetDataCollectionTableErec2CollIndEndIdxOfExtendedDataRecordTable(0);                               /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}

/* ****************************************************************************
 % Dem_Dcm_ERec_DataCollectionERecIter_Next
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Dcm_ERec_DataCollectionERecIter_Next(                                                                                        /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONSTP2VAR(Dem_Dcm_ERec_DataCollectionERecIterType, AUTOMATIC, AUTOMATIC) IterPtr                                              /* PRQA S 3673 */ /* MD_DEM_8.13_fp */
)
{
  IterPtr->mIdx += 1u;                                                                                                           /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}

/* ****************************************************************************
 % Dem_Dcm_ERec_0x1916_InitGlobalERecNumberFilter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Dcm_ERec_0x1916_InitGlobalERecNumberFilter(
  CONSTP2VAR(Dem_Cfg_ExtendedDataRecordIterator_FilterType, AUTOMATIC, AUTOMATIC) ExtendedDataFilterPtr
) 
{
  Dem_Dcm_ERec_ERecIter_Init(ExtendedDataFilterPtr->DataCollectionTableIdx,                                                      /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
                             &(ExtendedDataFilterPtr->ERecIterator));
  ExtendedDataFilterPtr->StoredMemoryIndex = DEM_MEM_INVALID_MEMORY_INDEX;                                                       /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}

/* ****************************************************************************
 % Dem_Dcm_ERec_0x1916_InitStoredEntryERecNumberFilter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Dcm_ERec_0x1916_InitStoredEntryERecNumberFilter(
  CONSTP2VAR(Dem_Cfg_ExtendedDataRecordIterator_FilterType, AUTOMATIC, AUTOMATIC) ExtendedDataFilterPtr
)
{
  Dem_Memory_MemEntryIterType lPrimaryEventEntryIter;
  Dem_Memory_MemEntry_IterInit(DEM_CFG_MEMORYID_PRIMARY, &lPrimaryEventEntryIter);                                               /* SBSW_DEM_POINTER_FORWARD_STACK */
  ExtendedDataFilterPtr->StoredMemoryIndex = Dem_Memory_MemEntry_IterGetMemoryIndex(&lPrimaryEventEntryIter);                    /* SBSW_DEM_POINTER_WRITE_ARGUMENT */ /* SBSW_DEM_POINTER_FORWARD_STACK */

  Dem_Dcm_ERec_ERecIter_Invalidate(&(ExtendedDataFilterPtr->ERecIterator));                                                      /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    
}


/* ****************************************************************************
 % Dem_Dcm_ERec_0x1916_CalcNumberofGlobalERecs
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
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Dcm_ERec_0x1916_CalcNumberofGlobalERecs(
  Dem_Cfg_ERecIndexType  ERecDataCollectionTableIdx,
  P2VAR(uint16, AUTOMATIC, DEM_DCM_DATA)  NumberOfFilteredRecords
)
{
  uint16 lERecCount;
  Dem_Dcm_ERec_ERecNumberIterType lERecIter;

  lERecCount = 0;
  for (Dem_Dcm_ERec_ERecIter_Init(ERecDataCollectionTableIdx, &lERecIter);                                                       /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Dcm_ERec_ERecIter_Exists(&lERecIter) == TRUE;                                                                         /* PRQA S 2994 */ /* MD_DEM_2994 */ /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Dcm_ERec_ERecIter_Next(&lERecIter))                                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_EventIdType lEventId;
    lEventId = Dem_Dcm_ERec_ERecIter_Get(&lERecIter);                                                                            /* SBSW_DEM_POINTER_FORWARD_STACK */

    if ((lEventId == Dem_Cfg_GetMasterEvent(lEventId))
      && (Dem_Cfg_EventUdsDtc(lEventId) != DEM_CFG_DTC_UDS_INVALID)
      && (Dem_Cfg_EventDestination(lEventId) == DEM_CFG_MEMORYID_PRIMARY)
      && (Dem_DTC_TestSuppressionOnDtcRetrieval(lEventId) == FALSE))                                                             /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
    {
      lERecCount++;
    }
  }

  *NumberOfFilteredRecords = lERecCount;                                                                                         /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */


/* ****************************************************************************
 % Dem_Dcm_ERec_0x1916_CalcNumberofStoredERecs
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
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Dcm_ERec_0x1916_CalcNumberofStoredERecs(
  Dem_Cfg_ERecIndexType  ERecDataCollectionTableIdx,
  P2VAR(uint16, AUTOMATIC, DEM_DCM_DATA)  NumberOfFilteredRecords
)
{
  uint16 lERecCount;
  Dem_Memory_MemEntryIterType lPrimaryEventEntryIter;
  Dem_Cfg_MemoryIndexType lMemoryIndex;
  Dem_Cfg_MemoryEntryHandleType lMemoryEntryId;
  Dem_EventIdType lEventId;

  lERecCount = 0;

  for (Dem_Memory_MemEntry_IterInit(DEM_CFG_MEMORYID_PRIMARY, &lPrimaryEventEntryIter);                                          /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Memory_MemEntry_IterExists(&lPrimaryEventEntryIter) == TRUE;                                                          /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Memory_MemEntry_IterNext(&lPrimaryEventEntryIter))                                                                    /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    lMemoryIndex = Dem_Memory_MemEntry_IterGetMemoryIndex(&lPrimaryEventEntryIter);                                               /* SBSW_DEM_CALL_ITERATOR_POINTER */
    lMemoryEntryId = Dem_MemoryEntry_GetId(lMemoryIndex);
    lEventId = Dem_MemoryEntry_GetEventId(lMemoryEntryId);

    if ( (lEventId != DEM_EVENT_INVALID)
      && (Dem_DTC_TestDtcSuppression(lEventId) == FALSE)                                                                         /* PRQA S 3415 */ /* MD_DEM_13.5_volatile */
      && (Dem_DTC_TestDtcAvailableInVariant(lEventId) == TRUE)
      && (Dem_MemoryEntry_TestAgingOnlyEntry(lMemoryEntryId) == FALSE))                                                          /* PRQA S 3415 */ /* MD_DEM_13.5_volatile */
    {
      Dem_ExtendedEntry_IterType lExtendedEntryIter;
      uint8 lExtendedEntryIndex;
      lExtendedEntryIndex = 0u; /*Iterator over 'user' extended data records in event entry*/

      for (Dem_ExtendedEntry_IterInit(lEventId, &lExtendedEntryIter);                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
           Dem_ExtendedEntry_IterExists(&lExtendedEntryIter) == TRUE;                                                            /* PRQA S 2994 */ /* MD_DEM_2994 */ /* SBSW_DEM_CALL_ITERATOR_POINTER */
           Dem_ExtendedEntry_IterNext(&lExtendedEntryIter))                                                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
      {
        if (ERecDataCollectionTableIdx == Dem_ExtendedEntry_IterGet(&lExtendedEntryIter))                                        /* SBSW_DEM_CALL_ITERATOR_POINTER */
        {
          if ((Dem_Cfg_ERecType(Dem_ExtendedEntry_IterGet(&lExtendedEntryIter)) != DEM_CFG_EREC_TYPE_USER)                       /* SBSW_DEM_CALL_ITERATOR_POINTER */
            || (Dem_ExtendedEntry_IteratorIsExtendedRecordStored(lMemoryEntryId, lExtendedEntryIndex) == TRUE))                  /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
          {
            lERecCount++;
          }
          break;
        }
# if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON)
        if (Dem_Cfg_ERecType(Dem_ExtendedEntry_IterGet(&lExtendedEntryIter)) == DEM_CFG_EREC_TYPE_USER)                          /* SBSW_DEM_CALL_ITERATOR_POINTER */
        {
          lExtendedEntryIndex += 1u;
        }
# endif
      }
    }
  }

  *NumberOfFilteredRecords = lERecCount;                                                                                         /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */


/* ****************************************************************************
 % Dem_Dcm_ERec_0x1916_GetNextGlobalERecData
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
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_ERec_0x1916_GetNextGlobalERecData(
  Dem_Dcm_ERec_0x1916_RecordNumberFilter_HandleType ExtendedDataFilterId,
  P2VAR(Dem_EventIdType, AUTOMATIC, DEM_DCM_DATA) EventId,
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA) DestBuffer,
  P2VAR(uint16, AUTOMATIC, DEM_DCM_DATA) BufSize
)
{
  Std_ReturnType lReturnValue;
  Dem_Cfg_ExtendedDataRecordIterator_FilterType lERecNumberFilter;

  lReturnValue = DEM_NO_SUCH_ELEMENT;
  lERecNumberFilter = Dem_Dcm_ERec_0x1916_GetRecordNumberFilter(ExtendedDataFilterId);

  for (/*Already initialzed on SetFilter - */;                                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
      (Dem_Dcm_ERec_ERecIter_Exists(&lERecNumberFilter.ERecIterator) == TRUE);                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Dcm_ERec_ERecIter_Next(&lERecNumberFilter.ERecIterator))                                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_EventIdType lEventId;
    lEventId = Dem_Dcm_ERec_ERecIter_Get(&lERecNumberFilter.ERecIterator);                                                       /* SBSW_DEM_CALL_ITERATOR_POINTER */

    if ( (lEventId == Dem_Cfg_GetMasterEvent(lEventId))
      && (Dem_Cfg_EventUdsDtc(lEventId) != DEM_CFG_DTC_UDS_INVALID)
      && (Dem_Cfg_EventDestination(lEventId) == DEM_CFG_MEMORYID_PRIMARY)
      && (Dem_DTC_TestSuppressionOnDtcRetrieval(lEventId) == FALSE))                                                             /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
      {
        Dem_Data_DestinationBuffer lDestinationBuffer;
        Dem_Data_InitDestinationBuffer(&lDestinationBuffer, DestBuffer, *BufSize);                                               /* SBSW_DEM_CALL_DESTINATIONBUFFER_INIT */

        lReturnValue = Dem_Dcm_ERec_0x1916_CopyERecs(lERecNumberFilter.DataCollectionTableIdx, 
          DEM_MEMORYENTRY_HANDLE_INVALID /* unused parameter*/, 0 /* unused parameter*/, lEventId, &lDestinationBuffer);         /* SBSW_DEM_POINTER_LOCAL_DESTINATIONBUFFER */

        if (lReturnValue != DEM_NO_SUCH_ELEMENT)
        {
          if (lReturnValue == E_OK)
          {
            *EventId = lEventId;                                                                                                 /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
            *BufSize = lDestinationBuffer.WriteIndex;                                                                            /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
            Dem_Dcm_ERec_ERecIter_Next(&lERecNumberFilter.ERecIterator);                                                         /* PRQA S 2469 */ /* MD_DEM_14.2_LoopControlHandledInternally */ /* SBSW_DEM_CALL_ITERATOR_POINTER */
          }

          /* record found - we are done here for this call */
          break;
        }
      }
  }
  Dem_Dcm_ERec_0x1916_SetRecordNumberFilter(ExtendedDataFilterId, &lERecNumberFilter);                                           /* SBSW_DEM_POINTER_FORWARD_STACK */
  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_Dcm_ERec_0x1916_GetNextStoredERecData
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
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_ERec_0x1916_GetNextStoredERecData(
  Dem_Dcm_ERec_0x1916_RecordNumberFilter_HandleType ExtendedDataFilterId,
  P2VAR(Dem_EventIdType, AUTOMATIC, DEM_DCM_DATA) EventId,
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA) DestBuffer,
  P2VAR(uint16, AUTOMATIC, DEM_DCM_DATA) BufSize
)
{
  Std_ReturnType lReturnValue;
  Dem_Memory_MemEntryIterType lPrimaryEventEntryIter;
  Dem_Cfg_MemoryIndexType lStoredMemoryIndex;
  Dem_Cfg_ExtendedDataRecordIterator_FilterType lERecNumberFilter;

  lReturnValue = DEM_NO_SUCH_ELEMENT;

  lERecNumberFilter = Dem_Dcm_ERec_0x1916_GetRecordNumberFilter(ExtendedDataFilterId);
  lStoredMemoryIndex = lERecNumberFilter.StoredMemoryIndex;
  
  for (Dem_Memory_MemEntry_IterResume_FromIndex(DEM_CFG_MEMORYID_PRIMARY, lStoredMemoryIndex, &lPrimaryEventEntryIter);          /* SBSW_DEM_CALL_ITERATOR_POINTER */
      (Dem_Memory_MemEntry_IterExists(&lPrimaryEventEntryIter) == TRUE);                                                         /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Memory_MemEntry_IterNext(&lPrimaryEventEntryIter))                                                                    /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_MemoryIndexType lMemoryIndex;
    Dem_Cfg_MemoryEntryHandleType lMemoryEntryId;
    Dem_EventIdType lEventId;

    lMemoryIndex = Dem_Memory_MemEntry_IterGetMemoryIndex(&lPrimaryEventEntryIter);                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */
    lMemoryEntryId = Dem_MemoryEntry_GetId(lMemoryIndex);
    lEventId = Dem_MemoryEntry_GetEventId(lMemoryEntryId);
    
    if ( (lEventId != DEM_EVENT_INVALID)
      && (Dem_DTC_TestDtcSuppression(lEventId) == FALSE)                                                                         /* PRQA S 3415 */ /* MD_DEM_13.5_volatile */
      && (Dem_DTC_TestDtcAvailableInVariant(lEventId) == TRUE)
      && (Dem_MemoryEntry_TestAgingOnlyEntry(lMemoryEntryId) == FALSE))                                                          /* PRQA S 3415 */ /* MD_DEM_13.5_volatile */
    {
      Dem_ExtendedEntry_IterType lExtendedEntryIter;
      uint8 lExtendedEntryIndex;
      lExtendedEntryIndex = 0u; /*Iterator over 'user' extended data records in event entry*/

      for (Dem_ExtendedEntry_IterInit(lEventId, &lExtendedEntryIter);                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
           Dem_ExtendedEntry_IterExists(&lExtendedEntryIter) == TRUE;                                                            /* PRQA S 2994 */ /* MD_DEM_2994 */ /* SBSW_DEM_CALL_ITERATOR_POINTER */
           Dem_ExtendedEntry_IterNext(&lExtendedEntryIter))                                                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
      {
        if (lERecNumberFilter.DataCollectionTableIdx == Dem_ExtendedEntry_IterGet(&lExtendedEntryIter))                          /* SBSW_DEM_CALL_ITERATOR_POINTER */
        {
          if ( (Dem_Cfg_ERecType(Dem_ExtendedEntry_IterGet(&lExtendedEntryIter)) != DEM_CFG_EREC_TYPE_USER)                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
           || (Dem_ExtendedEntry_IteratorIsExtendedRecordStored(lMemoryEntryId, lExtendedEntryIndex) == TRUE))                   /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
          {
            /* Record is stored */

            Dem_Data_DestinationBuffer lDestinationBuffer;

            Dem_Data_InitDestinationBuffer(&lDestinationBuffer, DestBuffer, *BufSize);                                           /* SBSW_DEM_CALL_DESTINATIONBUFFER_INIT */

            lReturnValue = Dem_Dcm_ERec_0x1916_CopyERecs(lERecNumberFilter.DataCollectionTableIdx,
                                         lMemoryEntryId, lExtendedEntryIndex, lEventId, &lDestinationBuffer);                    /* SBSW_DEM_POINTER_LOCAL_DESTINATIONBUFFER */

            if (lReturnValue == E_OK)
            {
              *EventId = lEventId;                                                                                               /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
              *BufSize = lDestinationBuffer.WriteIndex;                                                                          /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
              Dem_Memory_MemEntry_IterNext(&lPrimaryEventEntryIter);                                                             /* PRQA S 2469 */ /* MD_DEM_14.2_LoopControlHandledInternally */ /* SBSW_DEM_CALL_ITERATOR_POINTER */
            }
          }
          /* Record found - end search for event*/
          break;
        }
# if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON)
        if (Dem_Cfg_ERecType(Dem_ExtendedEntry_IterGet(&lExtendedEntryIter)) == DEM_CFG_EREC_TYPE_USER)                          /* SBSW_DEM_CALL_ITERATOR_POINTER */
        {
          lExtendedEntryIndex += 1u;
        }
# endif
      }
    }

    if (lReturnValue != DEM_NO_SUCH_ELEMENT)
    {
      /* record found - we are done here for this call */
      break;
    }
  }
  /* Write back iterator for next call on extended data record readout */
  lERecNumberFilter.StoredMemoryIndex = Dem_Memory_MemEntry_IterGetMemoryIndex(&lPrimaryEventEntryIter);                         /* SBSW_DEM_CALL_ITERATOR_POINTER */
  Dem_Dcm_ERec_0x1916_SetRecordNumberFilter(ExtendedDataFilterId, &lERecNumberFilter);                                           /* SBSW_DEM_POINTER_FORWARD_STACK */
  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_Dcm_ERec_0x1916_CopyERecs
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
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_ERec_0x1916_CopyERecs(
  Dem_Cfg_ERecIndexType ERecDataCollectionTableIdx,
  Dem_Cfg_MemoryEntryHandleType MemoryEntryId,                                                                                   /* PRQA S 3206 */ /* MD_DEM_3206 */
  uint8 ExtendedEntryIndex,
  Dem_EventIdType EventId,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  )
{
  Std_ReturnType lReturnValue;
  boolean lModificationDetected;
  uint8 lRecordType;
  lRecordType = Dem_Cfg_ERecType(ERecDataCollectionTableIdx);

  if (Dem_Cfg_DidSize(Dem_Cfg_ERecDid(ERecDataCollectionTableIdx)) > (DestinationBuffer->BufferSize - DestinationBuffer->WriteIndex))
  {
    lReturnValue = DEM_BUFFER_TOO_SMALL;
  }
  else
  {
    do
    {
      uint8 lUpdateState;

      /*Assert preconditions for copying the ERec are fulfilled by caller*/
      Dem_Internal_AssertReturnValue((lRecordType == DEM_CFG_EREC_TYPE_GLOBAL) || (MemoryEntryId != DEM_MEMORYENTRY_HANDLE_INVALID), DEM_E_INCONSISTENT_STATE, E_NOT_OK)

      lModificationDetected = FALSE;
      lUpdateState = Dem_Event_GetDataCommitState(EventId);

      if (Dem_Event_TestDataUpdateInProgress(lUpdateState) == FALSE)
      {
        Dem_DataReport_DidCopyInfoType lDidCopyInfo;

        Dem_DataReport_InitDidCopyInfo( &lDidCopyInfo, DestinationBuffer, EventId, MemoryEntryId, NULL_PTR );                  /* SBSW_DEM_CALL_DIDCOPYINFO_INIT */

        /* This call does not currently interrupt a concurrent data update */
        lReturnValue = Dem_DataReport_CopyExtendedDataRecord(                                                                  /* SBSW_DEM_POINTER_LOCAL_DIDCOPYINFO */
                                                               ExtendedEntryIndex,
                                                               ERecDataCollectionTableIdx,
                                                               &lDidCopyInfo
                                                              );
        if (lUpdateState != Dem_Event_GetDataCommitState(EventId))
        { /* The event data has been modified while trying to copy the data. */
          /* We cannot be sure it is correct, so start from the beginning */
          Dem_Data_ResetWriteIndexDestinationBuffer(DestinationBuffer);                                                          /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
          lModificationDetected = TRUE;
        }
      }
      else
      { /* The caller task has higher priority than Dem_MainFunction, but we cannot 'wait' for
        the update to complete. The requested data is not available at this moment. */
        lReturnValue = DEM_PENDING;
      }
    } while (lModificationDetected == TRUE);
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_Dcm_ERec_0x1916_GetRecordNumberFilter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_ExtendedDataRecordIterator_FilterType, DEM_CODE)
Dem_Dcm_ERec_0x1916_GetRecordNumberFilter(
  CONST(Dem_Dcm_ERec_0x1916_RecordNumberFilter_HandleType, AUTOMATIC)  ExtendedDataFilterId
)
{
  return Dem_Cfg_GetExtendedDataRecordIteratorTable(ExtendedDataFilterId);
}

/* ****************************************************************************
 % Dem_Dcm_ERec_0x1916_SetRecordNumberFilter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Dcm_ERec_0x1916_SetRecordNumberFilter(
  CONST(Dem_Dcm_ERec_0x1916_RecordNumberFilter_HandleType, AUTOMATIC)  ExtendedDataFilterId,
  CONSTP2CONST(Dem_Cfg_ExtendedDataRecordIterator_FilterType, AUTOMATIC, AUTOMATIC)  ExtendedDataFilterPtr
)
{                                                                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(ExtendedDataFilterPtr);
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (ExtendedDataFilterId >= Dem_Cfg_GetSizeOfExtendedDataRecordIteratorTable())
  {
    Dem_Error_RunTimeCheckFailed(DEM_EREC_IMPLEMENTATION_FILENAME, __LINE__);                                                    /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    Dem_Cfg_SetExtendedDataRecordIteratorTable(ExtendedDataFilterId, *ExtendedDataFilterPtr);                                    /* SBSW_DEM_ARRAY_WRITE_EXTENDEDDATARECORDITERATORTABLE */ /* PRQA S 2841 */ /* MD_DEM_Dir4.1_RunTimeCheckWriteOperation */
  }
}


/* ****************************************************************************
 % Dem_Dcm_ERec_FindDataCollectionTableIndexByRecordnumber
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Dcm_ERec_FindDataCollectionTableIndexByRecordnumber(
  uint8 RecordNumber,
  CONSTP2VAR(Dem_Cfg_ERecIndexType, AUTOMATIC, AUTOMATIC) DataCollectionIndex
)
{
  boolean lIndexFound;
  Dem_Cfg_ERecIndexType lDataCollectionIndex;
  Dem_Dcm_ERec_DataCollectionERecIterType lExtendedEntryIter;
  lIndexFound = FALSE;

  /* Find the requested record */
  for (Dem_Dcm_ERec_DataCollectionERecIter_Init(&lExtendedEntryIter);                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_Dcm_ERec_DataCollectionERecIter_Exists(&lExtendedEntryIter) == TRUE;                                                     /* PRQA S 2994 */ /* MD_DEM_2994 */ /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_Dcm_ERec_DataCollectionERecIter_Next(&lExtendedEntryIter))                                                               /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    lDataCollectionIndex = Dem_Dcm_ERec_DataCollectionERecIter_Get(&lExtendedEntryIter);                                         /* SBSW_DEM_CALL_ITERATOR_POINTER */
    if (RecordNumber == Dem_Cfg_DidNumber(Dem_Cfg_ERecDid(lDataCollectionIndex)))                                                
    {                                                                                                                            
      lIndexFound = TRUE;                                                                                                        
      *DataCollectionIndex = lDataCollectionIndex;                                                                               /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      break;                                                                                                                     
    }                                                                                                                                                                                                                                                       
  }

  return lIndexFound;
}


#if ((DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_ERECS == STD_ON)\
    && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 % Dem_Dcm_ERec_CopyERec_FromSubEventMemoryEntry
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Dcm_ERec_CopyERec_FromSubEventMemoryEntry(
  CONST(uint8, AUTOMATIC) ERecId,
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(Dem_DTCReadoutBuffer_ReadoutBufferDataIndexType, AUTOMATIC)  ReadoutBufferDataIndex,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  )
{
  boolean lERecCopied;
  uint8 lExtendedEntryIndex;
  Dem_ExtendedEntry_IterType lExtendedEntryIter;

  lERecCopied = FALSE;
  lExtendedEntryIndex = Dem_DTCReadoutBuffer_GetExtendedEntryIndex(
                          ReadoutBufferId,
                          ReadoutBufferDataIndex);
  lExtendedEntryIter = Dem_DTCReadoutBuffer_GetExtendedEntryIterator(
                          ReadoutBufferId,
                          ReadoutBufferDataIndex);

  /* Extended entry iterator is initialized during selection */
  while (Dem_ExtendedEntry_IterExists(&lExtendedEntryIter) == TRUE)                                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_ERecIndexType lCfgERecIndex;

    lCfgERecIndex = Dem_ExtendedEntry_IterGet(&lExtendedEntryIter);                                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */

    /* If the extended data number matches */
    if (ERecId == (uint8)Dem_Cfg_DidNumber(Dem_Cfg_ERecDid(lCfgERecIndex)))
    {
      Dem_EventIdType lEventId;
      Dem_Cfg_MemoryEntryHandleType lMemoryEntryId;

      lEventId = Dem_DTCReadoutBuffer_GetEventId(ReadoutBufferId, ReadoutBufferDataIndex);
      lMemoryEntryId = Dem_DTCReadoutBuffer_GetMemoryEntryId(ReadoutBufferId, ReadoutBufferDataIndex);

      if ((Dem_Cfg_ERecType(lCfgERecIndex) == DEM_CFG_EREC_TYPE_INTERNAL)
# if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON)
          || (Dem_ExtendedEntry_IteratorIsExtendedRecordStored(lMemoryEntryId, lExtendedEntryIndex) == TRUE)                     /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
# endif
         )
      {
        Dem_DataReport_DidCopyInfoType lDidCopyInfo;
        Dem_Data_WriteDestinationBufferUint8(DestinationBuffer, (uint8)Dem_Cfg_DidNumber(Dem_Cfg_ERecDid(lCfgERecIndex)));       /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */

        Dem_DataReport_InitDidCopyInfo( &lDidCopyInfo,                                                                         /* SBSW_DEM_CALL_DIDCOPYINFO_INIT */
                                          DestinationBuffer,
                                          lEventId,
                                          lMemoryEntryId,
                                          Dem_DTCReadoutBuffer_GetMemIndependentCounterPtr(ReadoutBufferId)
                                        );
        (void) Dem_DataReport_CopyExtendedDataRecord( lExtendedEntryIndex,                                                     /* SBSW_DEM_POINTER_LOCAL_DIDCOPYINFO */
                                                        lCfgERecIndex,
                                                        &lDidCopyInfo
                                                      );
        lERecCopied = TRUE;
      }
    }

    Dem_ExtendedEntry_IterNext(&lExtendedEntryIter);                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
# if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON)
    if (Dem_Cfg_ERecType(lCfgERecIndex) == DEM_CFG_EREC_TYPE_USER)
    {
      lExtendedEntryIndex++;
    }
# endif
    if (lERecCopied == TRUE)
    {
      break;
    }
  }

  Dem_Internal_AssertContinue((lERecCopied == TRUE), DEM_E_INCONSISTENT_STATE)
  Dem_DTCReadoutBuffer_SetExtendedEntryIterator(ReadoutBufferId,
                                                ReadoutBufferDataIndex,
                                                lExtendedEntryIter);
  Dem_DTCReadoutBuffer_SetExtendedEntryIndex(ReadoutBufferId,
                                             ReadoutBufferDataIndex,
                                             lExtendedEntryIndex);
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif

#if ((DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_ERECS == STD_ON)\
    && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 % Dem_Dcm_ERec_CopyERec_CombinedDTC
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
Dem_Dcm_ERec_CopyERec_CombinedDTC(
  CONST(uint8, AUTOMATIC) ERecId,
  CONST(Dem_Cfg_ERecIndexType, AUTOMATIC) ERecEntryIndex,
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  )
{
  Std_ReturnType lReturnValue;
  Dem_Cfg_CombinedGroupIndexType lCombinedDTCGroupId;

  lCombinedDTCGroupId = Dem_Cfg_EventCombinedGroup(Dem_DTCReadoutBuffer_GetMasterEventId(ReadoutBufferId));

  if ((DestinationBuffer->BufferSize - DestinationBuffer->WriteIndex)
       < Dem_Dcm_ERec_CalculateSizeSingleERec_CombinedDTC(
           ERecId, ERecEntryIndex, ReadoutBufferId, lCombinedDTCGroupId)
     )
  { /* Supported record, but the buffer is not large enough for all the data */
    lReturnValue = DEM_BUFFER_TOO_SMALL;
  }
  else
  {
    Dem_Cfg_ExtendedDataRecordEventIterType lExtendedDataRecordEventIter;

    /* Return E_OK wherein:
      - Internal ERec has no memory entry
      - Internal or User ERecs and selected data elements cannot be read
      - User ERec is not stored
    */
    lReturnValue = E_OK;
    switch (Dem_Cfg_ERecType(ERecEntryIndex))
    {
      case DEM_CFG_EREC_TYPE_GLOBAL:
      {
        for (Dem_Cfg_ExtendedDataRecordEventIterInit(&lExtendedDataRecordEventIter, lCombinedDTCGroupId, ERecId);                /* SBSW_DEM_CALL_ITERATOR_POINTER */
             Dem_Cfg_ExtendedDataRecordEventIterExists(&lExtendedDataRecordEventIter) == TRUE;                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
             Dem_Cfg_ExtendedDataRecordEventIterNext(&lExtendedDataRecordEventIter))                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
        {
          Dem_EventIdType lEventId;

          lEventId = Dem_Cfg_ExtendedDataRecordEventIterGet(&lExtendedDataRecordEventIter);                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
          if ((Dem_Cfg_EventAvailableByVariant(lEventId) == TRUE)
            && (Dem_EventInternalStatus_TestEventDisconnected(Dem_Event_GetInternalStatus(lEventId)) == FALSE))                  
          {
            Dem_DataReport_DidCopyInfoType lDidCopyInfo;
            
            Dem_Data_WriteDestinationBufferUint8(DestinationBuffer, (uint8)Dem_Cfg_DidNumber(Dem_Cfg_ERecDid(ERecEntryIndex)));  /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */

            
            Dem_DataReport_InitDidCopyInfo( &lDidCopyInfo,                                                                     /* SBSW_DEM_CALL_DIDCOPYINFO_INIT */
                                              DestinationBuffer,
                                              lEventId,
                                              DEM_MEMORYENTRY_HANDLE_INVALID,
                                              Dem_DTCReadoutBuffer_GetMemIndependentCounterPtr(ReadoutBufferId)
                                            );
                                              
            (void)Dem_DataReport_CopyExtendedDataRecord( 0x00U /* Unused parameter for Global ERecs */,                        /* SBSW_DEM_POINTER_LOCAL_DIDCOPYINFO */
                                                           ERecEntryIndex,
                                                           &lDidCopyInfo
                                                         );
          }
        }
        break;
      }

      case DEM_CFG_EREC_TYPE_INTERNAL:
      {
        for (Dem_Cfg_ExtendedDataRecordEventIterInit(&lExtendedDataRecordEventIter, lCombinedDTCGroupId, ERecId);                /* SBSW_DEM_CALL_ITERATOR_POINTER */
             Dem_Cfg_ExtendedDataRecordEventIterExists(&lExtendedDataRecordEventIter) == TRUE;                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
             Dem_Cfg_ExtendedDataRecordEventIterNext(&lExtendedDataRecordEventIter))                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
        {
          Dem_EventIdType lEventId;
          Dem_DTCReadoutBuffer_ReadoutBufferDataIndexType lReadoutBufferEventDataIndex;

          lEventId = Dem_Cfg_ExtendedDataRecordEventIterGet(&lExtendedDataRecordEventIter);                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
          lReadoutBufferEventDataIndex = Dem_DTCReadoutBuffer_GetEventDataIndex(ReadoutBufferId, lEventId);

          /* Event has a memory entry, try to copy content */
          if (lReadoutBufferEventDataIndex != Dem_Cfg_SizeOfReadOutBufferData())
          {
            Dem_Dcm_ERec_CopyERec_FromSubEventMemoryEntry(ERecId,                                                                /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
                                                          ReadoutBufferId,
                                                          lReadoutBufferEventDataIndex,
                                                          DestinationBuffer);
          }
        }
        break;
      }

# if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON)
      case DEM_CFG_EREC_TYPE_USER:
      {
        uint8 lUserERecStorageIndex;
        uint8 lNumOccupiedReadoutBufferSlots;
        Dem_DTCReadoutBuffer_ReadoutBufferDataIndexType lReadoutBufferEventDataIndex;

        lReadoutBufferEventDataIndex = DEM_DTCREADOUTBUFFER_DATAINDEX_DEFAULT;
        lNumOccupiedReadoutBufferSlots = Dem_DTCReadoutBuffer_GetNumberOfOccupiedSlots(ReadoutBufferId);
        lUserERecStorageIndex = Dem_ExtendedEntry_CalculateUserERecStorageIndex(ERecId, lCombinedDTCGroupId);

        for ( /* Initialized to default slot */;
            lReadoutBufferEventDataIndex < lNumOccupiedReadoutBufferSlots;
            lReadoutBufferEventDataIndex++)
        {

          Dem_Cfg_MemoryEntryHandleType lReadoutBufferMemoryEntryId;

          lReadoutBufferMemoryEntryId = Dem_DTCReadoutBuffer_GetMemoryEntryId(ReadoutBufferId, lReadoutBufferEventDataIndex);
          if (Dem_ExtendedEntry_GetUserERecStorageStatus(lUserERecStorageIndex, lReadoutBufferMemoryEntryId) == TRUE)
          {
            Dem_Dcm_ERec_CopyERec_FromSubEventMemoryEntry(ERecId,                                                                /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
                                                          ReadoutBufferId,
                                                          lReadoutBufferEventDataIndex,
                                                          DestinationBuffer);
          }
        }
        break;
      }
# endif
      default:                                                                                                                   /* PRQA S 2016 */ /* MD_MSR_EmptyClause */
        /* Do nothing */
        Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE)
        break;
    }
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6030, 6050 */ /* MD_MSR_STCYC, MD_MSR_STCAL */
#endif

#if ((DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 % Dem_Dcm_ERec_ReadNextRecord_CombinedEvent
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
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_ERec_ReadNextRecord_CombinedEvent(
  CONST(uint8, AUTOMATIC)  ClientId,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer                                                         /* PRQA S 3673 */ /* MD_DEM_8.13_fp */
  )
{
  Std_ReturnType lReturnValue;

  lReturnValue = DEM_NO_SUCH_ELEMENT;

# if (DEM_CFG_SUPPORT_ERECS == STD_ON)
  {
    Dem_DTCReadoutBuffer_HandleType lReadoutBufferId;
    uint8 lRecordNumber;
    Dem_Cfg_ERecIndexType lERecEntryIndex;
    Dem_DTCReadoutBuffer_RecordNumberIteratorType lRecordNumberIterator;

    lReadoutBufferId = Dem_Client_ClientAccess_GetReadoutBuffer(ClientId);
    lRecordNumberIterator = Dem_DTCReadoutBuffer_GetRecordNumberIterator(lReadoutBufferId);

    for (/* Already initialized during ERec selection */;
         Dem_Cfg_DTCExtendedDataRecordIterExists(&lRecordNumberIterator) == TRUE;                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Cfg_DTCExtendedDataRecordIterNext(&lRecordNumberIterator))                                                          /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      lRecordNumber = Dem_Cfg_DTCExtendedDataRecordIterGetRecordNr(&lRecordNumberIterator);                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */

      lERecEntryIndex = Dem_Cfg_DTCExtendedDataRecordIterGetERecIndex(&lRecordNumberIterator);                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */

      if (Dem_Dcm_ERec_TestRecordMatch(lReadoutBufferId, lRecordNumber) == TRUE)
      {
        lReturnValue = Dem_Dcm_ERec_CopyERec_CombinedDTC(lRecordNumber, lERecEntryIndex,                                         /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
                                                         lReadoutBufferId, DestinationBuffer);
      }

      if (lReturnValue != DEM_NO_SUCH_ELEMENT)
      {
        /* record was found */
        break;
      }
    }

    /* Increment the iterator in case of a positive match
      For negative match does not make any difference */
    Dem_Cfg_DTCExtendedDataRecordIterNext(&lRecordNumberIterator);                                                               /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_DTCReadoutBuffer_SetRecordNumberIterator(lReadoutBufferId, &lRecordNumberIterator);                                      /* SBSW_DEM_POINTER_FORWARD_STACK */
  }
# else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(ClientId)                                                                                     /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DestinationBuffer)                                                                            /* PRQA S 3112 */ /* MD_DEM_14.2 */
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Dcm_ERec_ReadNextRecord_NormalEvent
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
Dem_Dcm_ERec_ReadNextRecord_NormalEvent(
  CONST(uint8, AUTOMATIC)  ClientId,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer                                                         /* PRQA S 3673 */ /* MD_DEM_8.13_fp */
)
{
  Std_ReturnType lReturnValue;

  lReturnValue = DEM_NO_SUCH_ELEMENT;

# if (DEM_CFG_SUPPORT_ERECS == STD_ON)
  {
    Dem_DTCReadoutBuffer_HandleType lReadoutBufferId;
    Dem_ExtendedEntry_IterType lExtendedEntryIter;

    lReadoutBufferId = Dem_Client_ClientAccess_GetReadoutBuffer(ClientId);
    lExtendedEntryIter = Dem_DTCReadoutBuffer_GetExtendedEntryIterator(
                           lReadoutBufferId,
                           DEM_DTCREADOUTBUFFER_DATAINDEX_DEFAULT);

    /* Find next record. */
    while (Dem_ExtendedEntry_IterExists(&lExtendedEntryIter) == TRUE)                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      Dem_Cfg_ERecIndexType lCfgERecIndex;

      lCfgERecIndex = Dem_ExtendedEntry_IterGet(&lExtendedEntryIter);                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */

      /* If the extended data number matches */
      if (Dem_Dcm_ERec_TestRecordMatch(lReadoutBufferId,
                                       (uint8)Dem_Cfg_DidNumber(Dem_Cfg_ERecDid(lCfgERecIndex))) == TRUE)
      {
        lReturnValue = Dem_Dcm_ERec_CopyNextRecord(lReadoutBufferId,
                                                   DestinationBuffer,                                                            /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
                                                   DEM_DTCREADOUTBUFFER_DATAINDEX_DEFAULT);
      }

      Dem_ExtendedEntry_IterNext(&lExtendedEntryIter);                                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
      Dem_DTCReadoutBuffer_SetExtendedEntryIterator(lReadoutBufferId,
                                                    DEM_DTCREADOUTBUFFER_DATAINDEX_DEFAULT,
                                                    lExtendedEntryIter);
      Dem_DTCReadoutBuffer_IncExtendedEntryIndex(lReadoutBufferId,
                                                 DEM_DTCREADOUTBUFFER_DATAINDEX_DEFAULT,
                                                 Dem_Cfg_ERecType(lCfgERecIndex));

      if (lReturnValue != DEM_NO_SUCH_ELEMENT)
      {
        break;
      }
    }
  }
# else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(ClientId)                                                                                     /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DestinationBuffer)                                                                            /* PRQA S 3112 */ /* MD_DEM_14.2 */
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif /* (DEM_CFG_SUPPORT_DCM == STD_ON) */

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Dcm_ERec_GetSize_NormalEvent
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
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_ERec_GetSize_NormalEvent(
  CONST(uint8, AUTOMATIC)  ClientId,
  CONSTP2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  SizeOfExtendedDataRecord                                                         /* PRQA S 3673 */ /* MD_DEM_8.13_fp */
  )
{
  Std_ReturnType lReturnValue;

  /* Find the Record number */
  lReturnValue = DEM_NO_SUCH_ELEMENT;

# if (DEM_CFG_SUPPORT_ERECS == STD_ON)
  {
    uint16 lAccumulatedSize;
    Dem_DTCReadoutBuffer_HandleType lReadoutBufferId;
    uint8 lRecordNumber;
    Dem_ExtendedEntry_IterType lExtendedEntryIter;
    Dem_DTCReadoutBuffer_ReadoutBufferDataIndexType ReadoutBufferMemoryIndex;

    lAccumulatedSize = 0u;
    lReadoutBufferId = Dem_Client_ClientAccess_GetReadoutBuffer(ClientId);
    lRecordNumber = Dem_DTCReadoutBuffer_GetExtendedRecordNumber(lReadoutBufferId);
    ReadoutBufferMemoryIndex = DEM_DTCREADOUTBUFFER_DATAINDEX_DEFAULT;

    if (lRecordNumber < 0xf0U)
    {
      Dem_EventIdType lEventId;
      Dem_Cfg_MemoryEntryHandleType lMemoryEntryId;
      uint8 lExtendedEntryIndex;

      lEventId = Dem_DTCReadoutBuffer_GetEventId(lReadoutBufferId, ReadoutBufferMemoryIndex);
      lMemoryEntryId = Dem_DTCReadoutBuffer_GetMemoryEntryId(lReadoutBufferId, ReadoutBufferMemoryIndex);
      lExtendedEntryIndex = 0u;

      /* Look for one specific record */
      for (Dem_ExtendedEntry_IterInit(lEventId, &lExtendedEntryIter);                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
           Dem_ExtendedEntry_IterExists(&lExtendedEntryIter) == TRUE;                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
           Dem_ExtendedEntry_IterNext(&lExtendedEntryIter))                                                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
      {
        Dem_Cfg_ERecIndexType lCfgERecIndex;

        lCfgERecIndex = Dem_ExtendedEntry_IterGet(&lExtendedEntryIter);                                                          /* SBSW_DEM_CALL_ITERATOR_POINTER */
        if (lRecordNumber == Dem_Cfg_DidNumber(Dem_Cfg_ERecDid(lCfgERecIndex)))
        { /* If the record is supported, the result is always 'OK' */
          lReturnValue = E_OK;
          lAccumulatedSize = Dem_Dcm_ERec_CalculateSize(lCfgERecIndex,
                                                        lReadoutBufferId,
                                                        lMemoryEntryId,
                                                        lExtendedEntryIndex);
          break;
        }

# if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON)
        if (Dem_Cfg_ERecType(lCfgERecIndex) == DEM_CFG_EREC_TYPE_USER)
        {
          lExtendedEntryIndex += 1u;
        }
# endif
      }
    }
    else
    {
      /* Look for all supported records */
      uint8 lERecMinNumber;
      Dem_EventIdType lEventId;
      if (lRecordNumber == 0xffU)
      {
        lERecMinNumber = 0x00U;
        lEventId = Dem_DTCReadoutBuffer_GetEventId(lReadoutBufferId, ReadoutBufferMemoryIndex);
      }
      else if ( (Dem_Cfg_IsObdSupportedInVariant() == TRUE)
             && (lRecordNumber == 0xfeU))
      {
        lERecMinNumber = 0x8fU;
        lEventId = Dem_DTCReadoutBuffer_GetEventId(lReadoutBufferId, ReadoutBufferMemoryIndex);
      }
      else
      {
        lERecMinNumber = 0xffU;
        lEventId = DEM_EVENT_INVALID;
      }

      if (lEventId != DEM_EVENT_INVALID)
      {
        Dem_Cfg_MemoryEntryHandleType lMemoryEntryId;
        uint8 lExtendedEntryIndex;

        lMemoryEntryId = Dem_DTCReadoutBuffer_GetMemoryEntryId(lReadoutBufferId, ReadoutBufferMemoryIndex);
        lExtendedEntryIndex = 0u;

        for (Dem_ExtendedEntry_IterInit(lEventId, &lExtendedEntryIter);                                                          /* SBSW_DEM_CALL_ITERATOR_POINTER */
             Dem_ExtendedEntry_IterExists(&lExtendedEntryIter) == TRUE;                                                          /* SBSW_DEM_CALL_ITERATOR_POINTER */
             Dem_ExtendedEntry_IterNext(&lExtendedEntryIter))                                                                    /* SBSW_DEM_CALL_ITERATOR_POINTER */
        {
          Dem_Cfg_ERecIndexType lCfgERecIndex;

          lCfgERecIndex = Dem_ExtendedEntry_IterGet(&lExtendedEntryIter);                                                        /* SBSW_DEM_CALL_ITERATOR_POINTER */
          if (Dem_Cfg_DidNumber(Dem_Cfg_ERecDid(lCfgERecIndex)) > lERecMinNumber)
          { /* At least one record found - the result should be negative in case the event doesn't
                support any of the requested extended records. */
            lReturnValue = E_OK;
            lAccumulatedSize =
              (uint16)(lAccumulatedSize + Dem_Dcm_ERec_CalculateSize(lCfgERecIndex,
                                                                     lReadoutBufferId,
                                                                     lMemoryEntryId,
                                                                     lExtendedEntryIndex));
          }
# if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON)
          if (Dem_Cfg_ERecType(lCfgERecIndex) == DEM_CFG_EREC_TYPE_USER)
          {
            lExtendedEntryIndex += 1u;
          }
# endif
        }
      }
    }

    if (lReturnValue == E_OK)
    {
      *SizeOfExtendedDataRecord = lAccumulatedSize;                                                                              /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    }
  }
# else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(ClientId)                                                                                     /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(SizeOfExtendedDataRecord)                                                                     /* PRQA S 3112 */ /* MD_DEM_14.2 */
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6030, 6050, 6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
#endif /* (DEM_CFG_SUPPORT_DCM == STD_ON) */

#if ((DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 % Dem_Dcm_ERec_GetSize_CombinedEvent
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
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_ERec_GetSize_CombinedEvent(
  CONST(uint8, AUTOMATIC)  ClientId,
  CONSTP2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  SizeOfExtendedDataRecord                                                         /* PRQA S 3673 */ /* MD_DEM_8.13_fp */
  )
{
  uint16 lAccumulatedSize;
  Std_ReturnType lReturnValue;

  /* Find the Record number */
  lAccumulatedSize = 0x00U;
  lReturnValue = DEM_NO_SUCH_ELEMENT;

# if (DEM_CFG_SUPPORT_ERECS == STD_ON)
  {
    uint8 lSelectedRecordNumber;
    Dem_Cfg_ERecIndexType lERecEntryIndex;
    Dem_DTCReadoutBuffer_HandleType lReadoutBufferId;
    Dem_Cfg_CombinedGroupIndexType lCombinedDTCGroup;

    lReadoutBufferId = Dem_Client_ClientAccess_GetReadoutBuffer(ClientId);
    lSelectedRecordNumber = Dem_DTCReadoutBuffer_GetExtendedRecordNumber(lReadoutBufferId);
    lCombinedDTCGroup = Dem_Cfg_EventCombinedGroup(Dem_DTCReadoutBuffer_GetMasterEventId(lReadoutBufferId));

    if (lSelectedRecordNumber < 0xf0U)
    { /* Process single record selection */
      if (Dem_ExtendedEntry_TestDTCHasERecConfigured(lSelectedRecordNumber, lCombinedDTCGroup, &lERecEntryIndex) == TRUE)        /* SBSW_DEM_POINTER_FORWARD_STACK */
      {
        lAccumulatedSize = Dem_Dcm_ERec_CalculateSizeSingleERec_CombinedDTC(
                             lSelectedRecordNumber,
                             lERecEntryIndex,
                             lReadoutBufferId,
                             lCombinedDTCGroup);
        lReturnValue = E_OK;
      }
    }
    else
    { /* Process multiple record selection */
      uint8 lERecMinNumber;
      Dem_Cfg_DTCExtendedDataRecordIterType lDTCExtendedDataRecordIter;

      if (lSelectedRecordNumber == 0xffU)
      {
        lERecMinNumber = 0x00U;
      }
      else if ( (Dem_Cfg_IsObdSupportedInVariant() == TRUE)
             && (lSelectedRecordNumber == 0xfeU))
      {
        lERecMinNumber = 0x8fU;
      }
      else
      {
        lERecMinNumber = 0xffU;
      }

      for (Dem_Cfg_DTCExtendedDataRecordIterInit(&lDTCExtendedDataRecordIter, lCombinedDTCGroup);                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
          (Dem_Cfg_DTCExtendedDataRecordIterExists(&lDTCExtendedDataRecordIter) == TRUE);                                        /* SBSW_DEM_CALL_ITERATOR_POINTER */
           Dem_Cfg_DTCExtendedDataRecordIterNext(&lDTCExtendedDataRecordIter))                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
      {
        uint8 lERecId;

        lERecId = Dem_Cfg_DTCExtendedDataRecordIterGetRecordNr(&lDTCExtendedDataRecordIter);                                     /* SBSW_DEM_CALL_ITERATOR_POINTER */

        if (lERecId > lERecMinNumber)
        {
          Dem_Cfg_ERecIndexType lERecEntryIdx;

          /* At least one record found - the return should only be negative in case the event does not
             support any of the requested extended records. */
          lReturnValue = E_OK;
          lERecEntryIdx = Dem_Cfg_DTCExtendedDataRecordIterGetERecIndex(&lDTCExtendedDataRecordIter);                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
          lAccumulatedSize += Dem_Dcm_ERec_CalculateSizeSingleERec_CombinedDTC(
                                lERecId,
                                lERecEntryIdx,
                                lReadoutBufferId,
                                lCombinedDTCGroup
                                );
        }
      }
    }

    if (lReturnValue == E_OK)
    {
      *SizeOfExtendedDataRecord = lAccumulatedSize;                                                                              /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    }
  }
# else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(ClientId)                                                                                     /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(SizeOfExtendedDataRecord)                                                                     /* PRQA S 3112 */ /* MD_DEM_14.2 */
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif


#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_ERECS == STD_ON)
/* ****************************************************************************
 % Dem_Dcm_ERec_TestRecordMatch
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE boolean Dem_Dcm_ERec_TestRecordMatch(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(uint8, AUTOMATIC) RecordNumber
  )
{
  boolean lMatch;
  uint8 lRecordNumberFilter;
  lRecordNumberFilter = Dem_DTCReadoutBuffer_GetExtendedRecordNumber(ReadoutBufferId);

  lMatch = FALSE;
  if ( (lRecordNumberFilter == DEM_DCM_EXTENDEDDATARECORD_ALL)
    && (RecordNumber >= DEM_DCM_EXTENDEDDATARECORD_FIRST)
    && (RecordNumber <= DEM_DCM_EXTENDEDDATARECORD_LAST))
  {
    lMatch = TRUE;
  }
  else if ((Dem_Cfg_IsObdSupportedInVariant() == TRUE)
    && (lRecordNumberFilter == DEM_DCM_EXTENDEDDATARECORD_OBD)
    && (RecordNumber >= DEM_DCM_EXTENDEDDATARECORD_FIRST_OBD)
    && (RecordNumber <= DEM_DCM_EXTENDEDDATARECORD_LAST))
  {
    lMatch = TRUE;
  }
  else if (lRecordNumberFilter == RecordNumber)
  {
# if (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
    if (Dem_DTCReadoutBuffer_TestCombinedEventSelected(ReadoutBufferId) == TRUE)
    {
      Dem_Cfg_CombinedGroupIndexType lCombinedDTCGroupId;

      lCombinedDTCGroupId = Dem_Cfg_EventCombinedGroup(Dem_DTCReadoutBuffer_GetMasterEventId(ReadoutBufferId));
      lMatch = Dem_ExtendedEntry_ERecIsSupportedByAvailableCombinedEvent(lCombinedDTCGroupId, RecordNumber);
    }
    else
# endif
    {
      lMatch = TRUE;
    }
  }
  else
  {
    /* lMatch already set to FALSE*/
  }

  return lMatch;
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_ERECS == STD_ON)
/* ****************************************************************************
 % Dem_Dcm_ERec_CopyNextRecord
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
Dem_Dcm_ERec_CopyNextRecord(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(Dem_DTCReadoutBuffer_ReadoutBufferDataIndexType, AUTOMATIC)  ReadoutBufferDataIndex
  )
{
  uint8 lERecType;
  Dem_ExtendedEntry_IterType lExtendedEntryIter;
  Dem_Cfg_ERecIndexType lCfgERecIndex;
  Std_ReturnType lReturnValue;

  lReturnValue = E_NOT_OK;

  lExtendedEntryIter = Dem_DTCReadoutBuffer_GetExtendedEntryIterator(
                         ReadoutBufferId,
                         ReadoutBufferDataIndex);
  if (Dem_ExtendedEntry_IterExists(&lExtendedEntryIter) == TRUE)                                                                 /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_MemoryEntryHandleType lMemoryEntryId;
    Dem_EventIdType lEventId;
    uint8 lExtendedEntryIndex;

    lMemoryEntryId = Dem_DTCReadoutBuffer_GetMemoryEntryId(
                       ReadoutBufferId,
                       ReadoutBufferDataIndex);
    lExtendedEntryIndex = Dem_DTCReadoutBuffer_GetExtendedEntryIndex(
                          ReadoutBufferId,
                          ReadoutBufferDataIndex);
    lEventId = Dem_DTCReadoutBuffer_GetEventId(
                 ReadoutBufferId,
                 ReadoutBufferDataIndex);

    lCfgERecIndex = Dem_ExtendedEntry_IterGet(&lExtendedEntryIter);                                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */
    lERecType = Dem_Cfg_ERecType(lCfgERecIndex);

    if ((lERecType == DEM_CFG_EREC_TYPE_GLOBAL)
      || ((Dem_DTCReadoutBuffer_TestStoredDataAvailable(ReadoutBufferId) == TRUE)                                                
# if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON)
      && ((lERecType == DEM_CFG_EREC_TYPE_INTERNAL)
      || (Dem_ExtendedEntry_IteratorIsExtendedRecordStored(lMemoryEntryId, lExtendedEntryIndex) == TRUE)                         /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
      )
# endif
      )
      )
    {
      /* Check buffer size after stored status - the buffer does not need to be large enough for an empty response */
      if ((Dem_Cfg_DidSize(Dem_Cfg_ERecDid(lCfgERecIndex)) + 1u) > (uint16)(DestinationBuffer->BufferSize - DestinationBuffer->WriteIndex))  /* PRQA S 2897 */ /* MD_DEM_Dir1.1_WriteIndexInitialization */
      {
        lReturnValue = DEM_BUFFER_TOO_SMALL;
      }
      else
      {
        Dem_DataReport_DidCopyInfoType lDidCopyInfo;
        Dem_Data_WriteDestinationBufferUint8(DestinationBuffer, (uint8)Dem_Cfg_DidNumber(Dem_Cfg_ERecDid(lCfgERecIndex)));       /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */

        Dem_DataReport_InitDidCopyInfo( &lDidCopyInfo,                                                                         /* SBSW_DEM_CALL_DIDCOPYINFO_INIT */
                                          DestinationBuffer,
                                          lEventId,
                                          lMemoryEntryId,
                                          Dem_DTCReadoutBuffer_GetMemIndependentCounterPtr(ReadoutBufferId)
                                        );
        (void)Dem_DataReport_CopyExtendedDataRecord( lExtendedEntryIndex,                                                      /* SBSW_DEM_POINTER_LOCAL_DIDCOPYINFO */
                                                       lCfgERecIndex,
                                                       &lDidCopyInfo
                                                     );

        lReturnValue = E_OK;
      }
    }
    else
    {
      /* records currently not stored are returned with empty content */
      lReturnValue = E_OK;
      Dem_Data_ResetWriteIndexDestinationBuffer(DestinationBuffer);                                                              /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    }
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if ((DEM_CFG_SUPPORT_DCM == STD_ON)\
    && (DEM_CFG_SUPPORT_ERECS == STD_ON)\
    && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 % Dem_Dcm_ERec_CalculateSizeSingleERec_CombinedDTC
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
DEM_LOCAL FUNC(uint16, DEM_CODE)
Dem_Dcm_ERec_CalculateSizeSingleERec_CombinedDTC(
  CONST(uint8, AUTOMATIC)  ERecId,
  CONST(Dem_Cfg_ERecIndexType, AUTOMATIC)  ERecEntryIndex,
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC) CombinedGroupId
  )
{
  uint16 lSizeOfExtRec;
  Dem_Cfg_ExtendedDataRecordEventIterType lExtendedDataRecordEventIter;

  lSizeOfExtRec = 0u;

  switch (Dem_Cfg_ERecType(ERecEntryIndex))
  {
    case DEM_CFG_EREC_TYPE_GLOBAL:
    {
      for (Dem_Cfg_ExtendedDataRecordEventIterInit(&lExtendedDataRecordEventIter, CombinedGroupId, ERecId);                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
           Dem_Cfg_ExtendedDataRecordEventIterExists(&lExtendedDataRecordEventIter) == TRUE;                                     /* SBSW_DEM_CALL_ITERATOR_POINTER */
           Dem_Cfg_ExtendedDataRecordEventIterNext(&lExtendedDataRecordEventIter))                                               /* SBSW_DEM_CALL_ITERATOR_POINTER */
      {
        Dem_EventIdType lEventId;
        lEventId = Dem_Cfg_ExtendedDataRecordEventIterGet(&lExtendedDataRecordEventIter);                                        /* SBSW_DEM_CALL_ITERATOR_POINTER */
        if ((Dem_Cfg_EventAvailableByVariant(lEventId) == TRUE)
          && (Dem_EventInternalStatus_TestEventDisconnected(Dem_Event_GetInternalStatus(lEventId)) == FALSE))                    
        { /* Add one byte for RecordId */
          lSizeOfExtRec += (uint16)(Dem_Cfg_DidSize(Dem_Cfg_ERecDid(ERecEntryIndex)) + 1u);
        }
      }
      break;
    }

    case DEM_CFG_EREC_TYPE_INTERNAL:
    {
      for (Dem_Cfg_ExtendedDataRecordEventIterInit(&lExtendedDataRecordEventIter, CombinedGroupId, ERecId);                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
        Dem_Cfg_ExtendedDataRecordEventIterExists(&lExtendedDataRecordEventIter) == TRUE;                                        /* SBSW_DEM_CALL_ITERATOR_POINTER */
        Dem_Cfg_ExtendedDataRecordEventIterNext(&lExtendedDataRecordEventIter))                                                  /* SBSW_DEM_CALL_ITERATOR_POINTER */
      {
        Dem_DTCReadoutBuffer_ReadoutBufferDataIndexType lReadoutBufferDataIndex;
        Dem_EventIdType lEventId;

        lEventId = Dem_Cfg_ExtendedDataRecordEventIterGet(&lExtendedDataRecordEventIter);                                        /* SBSW_DEM_CALL_ITERATOR_POINTER */

        lReadoutBufferDataIndex = Dem_DTCReadoutBuffer_GetEventDataIndex(ReadoutBufferId, lEventId);

        /* Only count size of internal extended data records if the event has a memory entry */
        if ((lReadoutBufferDataIndex != Dem_Cfg_SizeOfReadOutBufferData())
            && (Dem_Data_ERecAllDataElementsStored(Dem_Cfg_ERecDid(ERecEntryIndex), ReadoutBufferId,                             /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
                  lReadoutBufferDataIndex) == TRUE)
           )
        { /* Add one byte for RecordId */
          lSizeOfExtRec += (uint16)(Dem_Cfg_DidSize(Dem_Cfg_ERecDid(ERecEntryIndex)) + 1u);
        }
      }
      break;
    }

# if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON)
    case DEM_CFG_EREC_TYPE_USER:
    {
      uint8 lUserERecStorageIndex;
      uint8 lNumOccupiedReadoutBufferSlots;
      Dem_DTCReadoutBuffer_ReadoutBufferDataIndexType lReadoutBufferDataIndex;

      lReadoutBufferDataIndex = DEM_DTCREADOUTBUFFER_DATAINDEX_DEFAULT;
      lNumOccupiedReadoutBufferSlots = Dem_DTCReadoutBuffer_GetNumberOfOccupiedSlots(ReadoutBufferId);
      lUserERecStorageIndex = Dem_ExtendedEntry_CalculateUserERecStorageIndex(ERecId, CombinedGroupId);

      for ( /* Initialized to default slot */;
          lReadoutBufferDataIndex < lNumOccupiedReadoutBufferSlots;
          lReadoutBufferDataIndex++)
      {

        Dem_Cfg_MemoryEntryHandleType lReadoutBufferMemoryEntryId;

        lReadoutBufferMemoryEntryId = Dem_DTCReadoutBuffer_GetMemoryEntryId(ReadoutBufferId, lReadoutBufferDataIndex);

        if ((Dem_ExtendedEntry_GetUserERecStorageStatus(lUserERecStorageIndex, lReadoutBufferMemoryEntryId) == TRUE)
          && (Dem_Data_ERecAllDataElementsStored(Dem_Cfg_ERecDid(ERecEntryIndex), ReadoutBufferId, lReadoutBufferDataIndex) == TRUE))  /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
        { /* Add one byte for RecordId */
          lSizeOfExtRec += (uint16)(Dem_Cfg_DidSize(Dem_Cfg_ERecDid(ERecEntryIndex)) + 1u);
        }
      }
      break;
    }
# endif

    default:                                                                                                                     /* PRQA S 2016 */ /* MD_MSR_EmptyClause */ 
      Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
      break;
  }

  return lSizeOfExtRec;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_ERECS == STD_ON)
/* ****************************************************************************
 % Dem_Dcm_ERec_CalculateSize
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
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Dcm_ERec_CalculateSize(
  CONST(Dem_Cfg_ERecIndexType, AUTOMATIC) CfgERecIndex,
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC)  ExtendedEntryIndex
  )
{
  uint16 lSizeOfExtRec;
  uint8 lERecType;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(ExtendedEntryIndex)                                                                           /* PRQA S 3112 */ /* MD_DEM_14.2 */

  lSizeOfExtRec = 0u;
  lERecType = Dem_Cfg_ERecType(CfgERecIndex);

  if (lERecType != DEM_CFG_EREC_TYPE_GLOBAL)
  {
    /* Test if event has a memory entry */
    if (Dem_DTCReadoutBuffer_TestStoredDataAvailable(ReadoutBufferId) == TRUE)
    {
# if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON)
      if (  (lERecType == DEM_CFG_EREC_TYPE_INTERNAL)
        /* Test if requested record is stored for event */
        || (Dem_ExtendedEntry_IteratorIsExtendedRecordStored(MemoryEntryId, ExtendedEntryIndex) == TRUE))                        /* PRQA S 3415 */ /* MD_DEM_13.5_cf */                        
# endif
      {
        if (Dem_Data_ERecAllDataElementsStored(
              Dem_Cfg_ERecDid(CfgERecIndex),
              ReadoutBufferId,
              DEM_DTCREADOUTBUFFER_DATAINDEX_DEFAULT) == TRUE)
        {
          lSizeOfExtRec = (uint16)(Dem_Cfg_DidSize(Dem_Cfg_ERecDid(CfgERecIndex)) + 1u);
        } /* else lSizeOfExtRec is already set to 0 */
      } /* else lSizeOfExtRec is already set to 0 */
    } /* else lSizeOfExtRec is already set to 0 */
  }
  else
  { /* Currently statistic data is always available, add record id to data size */
    lSizeOfExtRec = (uint16)(Dem_Cfg_DidSize(Dem_Cfg_ERecDid(CfgERecIndex)) + 1u);
  }

  return lSizeOfExtRec;
}
#endif /* (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_ERECS == STD_ON) */

/*!
 * \}
 */
# define DEM_STOP_SEC_CODE
# include "MemMap.h"                                                                                                             /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DEFINITIONS
 *********************************************************************************************************************/
# define DEM_START_SEC_CODE
# include "MemMap.h"                                                                                                             /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \addtogroup Dem_ERec_Public
 * \{
 */

 /* ****************************************************************************
 % Dem_Dcm_ERec_0x1916_IsService19_16Enabled
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Dcm_ERec_0x1916_IsService19_16Enabled(
  void 
)
{
  return (boolean) (DEM_CFG_SUPPORT_SVC19_16 == STD_ON);
}

 /* ****************************************************************************
 % Dem_Dcm_ERec_0x1916_TestFilterSet
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
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Dcm_ERec_0x1916_TestFilterSet(
  CONST(Dem_Dcm_ERec_0x1916_RecordNumberFilter_HandleType, AUTOMATIC)  ExtendedDataFilterId
)
{
  boolean lResultValue;
  lResultValue = TRUE;

  if (Dem_Dcm_ERec_0x1916_GetRecordNumberFilter(ExtendedDataFilterId).DataCollectionTableIdx 
                                                 == DEM_DCM_EREC_DATACOLLECTIONTABLE_INVALID)
  {
    lResultValue = FALSE;
  }

  return lResultValue;
}


/* ****************************************************************************
 % Dem_Dcm_ERec_0x1916_InitERecNumberFilter
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
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Dcm_ERec_0x1916_InitERecNumberFilter(
  CONST(Dem_Dcm_ERec_0x1916_RecordNumberFilter_HandleType, AUTOMATIC)  ExtendedDataFilterId
)
{
  Dem_Cfg_ExtendedDataRecordIterator_FilterType lTempRecordFilter;
  lTempRecordFilter = Dem_Dcm_ERec_0x1916_GetRecordNumberFilter(ExtendedDataFilterId);
  
  Dem_Dcm_ERec_ERecIter_Invalidate(&(lTempRecordFilter.ERecIterator));                                                           /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */

  lTempRecordFilter.StoredMemoryIndex = DEM_MEM_INVALID_MEMORY_INDEX;
  lTempRecordFilter.DTCOrigin = DEM_DTC_ORIGIN_PRIMARY_MEMORY;
  lTempRecordFilter.DTCFormat = DEM_DTC_FORMAT_UDS;
  lTempRecordFilter.DataCollectionTableIdx = DEM_DCM_EREC_DATACOLLECTIONTABLE_INVALID;

  Dem_Dcm_ERec_0x1916_SetRecordNumberFilter(ExtendedDataFilterId, &lTempRecordFilter);                                           /* SBSW_DEM_POINTER_FORWARD_STACK */
}

 /* ****************************************************************************
  % Dem_Dcm_ERec_0x1916_SetRecordFilter
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
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_ERec_0x1916_SetRecordFilter(
  CONST(Dem_Dcm_ERec_0x1916_RecordNumberFilter_HandleType, AUTOMATIC) ExtendedDataFilterId,
  CONST(uint8, AUTOMATIC) RecordNumber
)
{
  Std_ReturnType lReturnValue;
  boolean lERecFound;
  Dem_Cfg_ERecIndexType lDataCollectionTableIndex;

  lReturnValue = E_NOT_OK;
  lDataCollectionTableIndex = DEM_DCM_EREC_DATACOLLECTIONTABLE_INVALID;
  lERecFound = Dem_Dcm_ERec_FindDataCollectionTableIndexByRecordnumber(RecordNumber, &lDataCollectionTableIndex);                /* SBSW_DEM_POINTER_FORWARD_STACK */

  if (lERecFound == TRUE)
  {
    uint8 lERecType;
    Dem_Cfg_ExtendedDataRecordIterator_FilterType RecordFilterTemp;

    RecordFilterTemp = Dem_Dcm_ERec_0x1916_GetRecordNumberFilter(ExtendedDataFilterId);
    RecordFilterTemp.DataCollectionTableIdx = lDataCollectionTableIndex;

    lERecType = Dem_Cfg_ERecType(lDataCollectionTableIndex);
    if (lERecType == DEM_CFG_EREC_TYPE_GLOBAL)
    {
      Dem_Dcm_ERec_0x1916_InitGlobalERecNumberFilter(&RecordFilterTemp);                                                         /* SBSW_DEM_POINTER_FORWARD_STACK */
    }
    else
    {
      Dem_Dcm_ERec_0x1916_InitStoredEntryERecNumberFilter(&RecordFilterTemp);                                                    /* SBSW_DEM_POINTER_FORWARD_STACK */
    }

    Dem_Dcm_ERec_0x1916_SetRecordNumberFilter(ExtendedDataFilterId, &RecordFilterTemp);                                          /* SBSW_DEM_POINTER_FORWARD_STACK */
    lReturnValue = E_OK;
  }
  return lReturnValue;
}


/* ****************************************************************************
 % Dem_Dcm_ERec_0x1916_CalcNumberofERecs
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
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Dcm_ERec_0x1916_CalcNumberofERecs(
  Dem_Dcm_ERec_0x1916_RecordNumberFilter_HandleType ExtendedDataFilterId,
  P2VAR(uint16, AUTOMATIC, DEM_DCM_DATA)  NumberOfFilteredRecords,
  P2VAR(uint16, AUTOMATIC, DEM_DCM_DATA)  SizeOfExtendedDataRecord
)
{
  uint8 lRecordType;
  Dem_Cfg_ERecIndexType lDataCollectionTableIdx;

  lDataCollectionTableIdx = Dem_Dcm_ERec_0x1916_GetRecordNumberFilter(ExtendedDataFilterId).DataCollectionTableIdx;
  lRecordType = Dem_Cfg_ERecType(lDataCollectionTableIdx);
  if (lRecordType == DEM_CFG_EREC_TYPE_GLOBAL)
  {
    Dem_Dcm_ERec_0x1916_CalcNumberofGlobalERecs(lDataCollectionTableIdx, NumberOfFilteredRecords);                               /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }
  else
  {
    Dem_Dcm_ERec_0x1916_CalcNumberofStoredERecs(lDataCollectionTableIdx, NumberOfFilteredRecords);                               /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }

  *SizeOfExtendedDataRecord = Dem_Cfg_DidSize(lDataCollectionTableIdx);                                                          /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}

/* ****************************************************************************
 % Dem_Dcm_ERec_0x1916_GetNextFilteredERecData
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
Dem_Dcm_ERec_0x1916_GetNextFilteredERecData(
  Dem_Dcm_ERec_0x1916_RecordNumberFilter_HandleType ExtendedDataFilterId,
  P2VAR(uint32, AUTOMATIC, DEM_DCM_DATA) DTC,
  P2VAR(uint8,  AUTOMATIC, DEM_DCM_DATA) DTCStatus,
  P2VAR(uint8,  AUTOMATIC, DEM_DCM_DATA) DestBuffer,
  P2VAR(uint16, AUTOMATIC, DEM_DCM_DATA) BufSize
)
{
  Std_ReturnType lReturnValue;
  Dem_EventIdType lEventId;
  Dem_Cfg_ERecIndexType lDataCollectionTableIdx;

  lEventId = DEM_EVENT_INVALID;

  lDataCollectionTableIdx = Dem_Dcm_ERec_0x1916_GetRecordNumberFilter(ExtendedDataFilterId).DataCollectionTableIdx;
  if (Dem_Cfg_ERecType(lDataCollectionTableIdx) == DEM_CFG_EREC_TYPE_GLOBAL)
  {
    lReturnValue = Dem_Dcm_ERec_0x1916_GetNextGlobalERecData(ExtendedDataFilterId, &lEventId, DestBuffer, BufSize);              /* SBSW_DEM_POINTER_FORWARD_STACK */ /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }
  else
  {
    lReturnValue = Dem_Dcm_ERec_0x1916_GetNextStoredERecData(ExtendedDataFilterId, &lEventId, DestBuffer, BufSize);              /* SBSW_DEM_POINTER_FORWARD_STACK */ /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }

  if(lReturnValue == E_OK)
  {
    *DTC = Dem_Cfg_EventUdsDtc(lEventId);                                                                                        /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    *DTCStatus = Dem_DTC_GetExternalDTCStatus(lEventId);                                                                         /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  }
  else
  {
    *BufSize = 0u;                                                                                                               /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  }

  return lReturnValue;
}



#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Dcm_ERec_ReadNextRecord
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_ERec_ReadNextRecord(
  CONST(uint8, AUTOMATIC)  ClientId,
  CONSTP2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)  DestBuffer,                                                                       /* PRQA S 3673 */ /* MD_DEM_8.13_fp */
  CONSTP2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  BufSize                                                                          /* PRQA S 3673 */ /* MD_DEM_8.13_fp */
)
{
  Std_ReturnType lReturnValue;
  Dem_Data_DestinationBuffer lDestinationBuffer;

  Dem_Data_InitDestinationBuffer(&lDestinationBuffer, DestBuffer, *BufSize);                                                     /* SBSW_DEM_CALL_DESTINATIONBUFFER_INIT */

# if (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
  if (Dem_DTCReadoutBuffer_TestCombinedEventSelected(Dem_Client_ClientAccess_GetReadoutBuffer(ClientId)) == TRUE)
  {
    lReturnValue = Dem_Dcm_ERec_ReadNextRecord_CombinedEvent(ClientId, &lDestinationBuffer);                                     /* SBSW_DEM_POINTER_LOCAL_DESTINATIONBUFFER */
  }
  else
# endif
  {
    lReturnValue = Dem_Dcm_ERec_ReadNextRecord_NormalEvent(ClientId, &lDestinationBuffer);                                       /* SBSW_DEM_POINTER_LOCAL_DESTINATIONBUFFER */
  }

  if (lReturnValue == E_OK)
  {
    /* return number of written bytes */
    *BufSize = lDestinationBuffer.WriteIndex;                                                                                    /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  }

  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Dcm_ERec_GetSize
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_ERec_GetSize(
  CONST(uint8, AUTOMATIC) ClientId,
  CONSTP2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  SizeOfExtendedDataRecord
  )
{
  Std_ReturnType lRetVal;

# if (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
  if (Dem_DTCReadoutBuffer_TestCombinedEventSelected(Dem_Client_ClientAccess_GetReadoutBuffer(ClientId)) == TRUE)
  {
    lRetVal = Dem_Dcm_ERec_GetSize_CombinedEvent(ClientId, SizeOfExtendedDataRecord);                                            /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }
  else
# endif
  {
    lRetVal = Dem_Dcm_ERec_GetSize_NormalEvent(ClientId, SizeOfExtendedDataRecord);                                              /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }

  return lRetVal;
}
#endif


#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Dcm_ERec_SelectRecord
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Dcm_ERec_SelectRecord(
  CONST(uint8, AUTOMATIC) ClientId,
  CONST(uint8, AUTOMATIC)  RecordNumber
  )
{
  Dem_DTCReadoutBuffer_HandleType lReadoutBufferId;

  lReadoutBufferId = Dem_Client_ClientAccess_GetReadoutBuffer(ClientId);
  Dem_DTCReadoutBuffer_SelectExtendedDataRecord(lReadoutBufferId, RecordNumber);
}
#endif

/*!
 * \}
 */
# define DEM_STOP_SEC_CODE
# include "MemMap.h"                                                                                                             /* PRQA S 5087 */ /* MD_MSR_MemMap */


/* ****************************************************************************
 % Dem_Dcm_ERec_0x191A_IsService19_1AEnabled
*****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Dcm_ERec_0x191A_IsService19_1AEnabled(
  void
)
{
  return (boolean)(DEM_CFG_SUPPORT_SVC19_1A == STD_ON);
}

/* ****************************************************************************
 % Dem_Dcm_ERec_0x191A_SetDTCFilterByExtendedDataRecordNumber
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
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_ERec_0x191A_SetDTCFilterByExtendedDataRecordNumber(
  Dem_FilterData_HandleType DTCFilterId,
  uint8 ExtendedDataRecordNumber
)
{
  Std_ReturnType lReturnValue = E_NOT_OK;
  boolean lERecFound;
  Dem_Cfg_FilterInfoTablePtrType lDTCFilterPtr;

  lDTCFilterPtr = Dem_Client_FilterData_GetFilterDataPtrSafe(DTCFilterId);
  lERecFound = Dem_Dcm_ERec_FindDataCollectionTableIndexByRecordnumber(ExtendedDataRecordNumber,
                                                                       &lDTCFilterPtr->TableIndex.DataCollectionTableIdx);       /* SBSW_DEM_POINTER_FORWARD_ARGUMENT_STRUCT_MEMBER */

  if (lERecFound == TRUE)
  {
    lDTCFilterPtr->FilterDtcStrategy = Dem_FilterData_FilterEventBased_ExtendendDataRecord;                                      /* SBSW_DEM_POINTER_WRITE_ARGUMENT */

    Dem_Dcm_ERec_ERecIter_Init(lDTCFilterPtr->TableIndex.DataCollectionTableIdx,
                               &lDTCFilterPtr->Iterator.ERecIterator);                                                           /* SBSW_DEM_POINTER_FORWARD_ARGUMENT_STRUCT_MEMBER */

    Dem_Client_FilterData_InitCombinedGroupProcessed(lDTCFilterPtr);                                                                    /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */

    lReturnValue = E_OK;
  }

  return lReturnValue;

}

/* ****************************************************************************
 % Dem_Dcm_ERec_0x191A_GetNumberOfFilteredDTCsByERecNumber
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
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Dcm_ERec_0x191A_GetNumberOfFilteredDTCsByERecNumber(                                                                         /* PRQA S 3219 */ /* MD_DEM_14.1_CONFIGURATION_SWITCH */
  Dem_Cfg_ERecIndexType DataCollectionTableIdx
)
{
  uint16 lCount;
  Dem_Dcm_ERec_ERecNumberIterType lExtendedDataRecordIter;
  Dem_Cfg_ProcessedCombinedDTCGroupType lProcessedCombinedDTCGroups;
  
  lCount = 0;
  Dem_DTC_InitCombinedGroupProcessed(lProcessedCombinedDTCGroups);                                                               /* SBSW_DEM_POINTER_FORWARD_STACK */


  for (Dem_Dcm_ERec_ERecIter_Init(DataCollectionTableIdx, &lExtendedDataRecordIter);                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
      (Dem_Dcm_ERec_ERecIter_Exists(&lExtendedDataRecordIter) == TRUE);                                                          /* PRQA S 2994 */ /* MD_DEM_2994 */ /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Dcm_ERec_ERecIter_Next(&lExtendedDataRecordIter))                                                                     /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_EventIdType lEventId;
    lEventId = Dem_Dcm_ERec_ERecIter_Get(&lExtendedDataRecordIter);                                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */

    if ( (Dem_DTC_TestCombinedGroupProcessed(Dem_Cfg_EventCombinedGroup(lEventId), lProcessedCombinedDTCGroups) == FALSE )       /* PRQA S 3415 */ /* MD_DEM_13.5_volatile */ /* SBSW_DEM_POINTER_FORWARD_STACK */
      && (Dem_Cfg_GetMemoryRepresentative(lEventId) == lEventId)
      && (Dem_Cfg_EventUdsDtc(lEventId) != DEM_CFG_DTC_UDS_INVALID)
      && (Dem_Cfg_EventDestination(lEventId) == DEM_CFG_MEMORYID_PRIMARY)
      && (Dem_DTC_TestSuppressionByRepresentiveEvent(lEventId) == FALSE))                                                        /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
    {
      Dem_DTC_SetCombinedGroupProcessed(Dem_Cfg_EventCombinedGroup(lEventId), lProcessedCombinedDTCGroups);                      /* SBSW_DEM_POINTER_FORWARD_STACK */
      lCount++;
    }
  }

  return lCount;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_Dcm_ERec_0x191A_FilterDTCByERecNumber
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
DEM_LOCAL FUNC(Dem_EventIdType, DEM_CODE)
Dem_Dcm_ERec_0x191A_FilterDTCByERecNumber(                                                                                       /* PRQA S 3219 */ /* MD_DEM_14.1_CONFIGURATION_SWITCH */
  CONSTP2VAR(Dem_Cfg_FilterData_InfoType, AUTOMATIC, AUTOMATIC)  DTCFilterPtr                                                    /* PRQA S 3673 */ /* MD_DEM_8.13_fp */
  )
{
  Dem_EventIdType lReturnEventIdValue;

  lReturnEventIdValue = DEM_EVENT_INVALID;

  for (/*Already initialzed on SetFilter - */;
    (Dem_Dcm_ERec_ERecIter_Exists(&DTCFilterPtr->Iterator.ERecIterator) == TRUE);                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
     Dem_Dcm_ERec_ERecIter_Next(&DTCFilterPtr->Iterator.ERecIterator))                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_EventIdType lEventId;
    lEventId = Dem_Dcm_ERec_ERecIter_Get(&DTCFilterPtr->Iterator.ERecIterator);                                                  /* SBSW_DEM_CALL_ITERATOR_POINTER */

    if ( (Dem_Client_FilterData_TestCombinedGroupProcessed(Dem_Cfg_EventCombinedGroup(lEventId), DTCFilterPtr) == FALSE)                /* PRQA S 3415 */ /* MD_DEM_13.5_volatile */ /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
      && (Dem_Cfg_GetMemoryRepresentative(lEventId) == lEventId)
      && (Dem_Cfg_EventUdsDtc(lEventId) != DEM_CFG_DTC_UDS_INVALID)
      && (Dem_Cfg_EventDestination(lEventId) == DEM_CFG_MEMORYID_PRIMARY)
      && (Dem_DTC_TestSuppressionByRepresentiveEvent(lEventId) == FALSE))                                                        /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
    {
      lReturnEventIdValue = lEventId;
      Dem_Client_FilterData_SetCombinedGroupProcessed(Dem_Cfg_EventCombinedGroup(lEventId), DTCFilterPtr);                              /* PRQA S 2469 */ /* MD_DEM_14.2_FalsePositive */ /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
      Dem_Dcm_ERec_ERecIter_Next(&DTCFilterPtr->Iterator.ERecIterator);                                                          /* PRQA S 2469 */ /* MD_DEM_14.2_LoopControlHandledInternally */ /* SBSW_DEM_CALL_ITERATOR_POINTER */
      break;
    }
  }

  return lReturnEventIdValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

#endif /* DEM_EREC_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_ERec_Implemnetation.h
 *********************************************************************************************************************/
