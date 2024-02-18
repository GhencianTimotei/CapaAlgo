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
/*! \ingroup    Dem_ClientAccess
 *  \defgroup   Dem_DTCReadoutBuffer DTCReadoutBuffer
 *  \{
 *  \file       Dem_DTCReadoutBuffer_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) Interface declaration file
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_DTCREADOUTBUFFER_INTERFACE_H)
#define DEM_DTCREADOUTBUFFER_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_DTCReadoutBuffer_Types.h"
#include "Dem_FaultMemory_Types.h"


/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_DTCReadoutBuffer_PublicProperties Public Properties
 * \{
 */

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
* Dem_DTCReadoutBuffer_GetTimeSeriesEntryIndex
*****************************************************************************/
/*!
* \brief         Returns handle to the selected events time series entry 
*                memory block
*
* \details       Returns handle to the selected events time series entry 
*                memory block
*
* \param[in]     ReadoutBufferId
*                Index of the ReadoutBuffer
*
* \return        MemoryIndex
*                Handle of the memory block
*
* \pre           -
* \config        DEM_CFG_SUPPORT_DCM == STD_ON
*
* \context       TASK|ISR2
* \synchronous   TRUE
* \reentrant     TRUE
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_DTCReadoutBuffer_GetTimeSeriesEntryIndex(
  Dem_DTCReadoutBuffer_HandleType  ReadoutBufferId
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
* Dem_DTCReadoutBuffer_GetUnusedFutureSamplesNormal
*****************************************************************************/
/*!
* \brief         Returns the captured event's unused future samples of 
*                normal rate sampling
*
* \details       -
*
* \param[in]     ReadoutBufferId
*                Index of the ReadoutBuffer
*
* \return        Unused future samples of normal rate sampling
*
* \pre           -
* \config        DEM_CFG_SUPPORT_DCM == STD_ON
*
* \context       TASK|ISR2
* \synchronous   TRUE
* \reentrant     TRUE
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DTCReadoutBuffer_GetUnusedFutureSamplesNormal(
  Dem_DTCReadoutBuffer_HandleType  ReadoutBufferId
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
* Dem_DTCReadoutBuffer_GetUnusedFutureSamplesFast
*****************************************************************************/
/*!
* \brief         Returns the captured event's unused future samples of 
*                fast rate sampling
*
* \details       -
*
* \param[in]     ReadoutBufferId
*                Index of the ReadoutBuffer
*
* \return        Unused future samples of fast rate sampling
*
* \pre           -
* \config        DEM_CFG_SUPPORT_DCM == STD_ON
*
* \context       TASK|ISR2
* \synchronous   TRUE
* \reentrant     TRUE
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DTCReadoutBuffer_GetUnusedFutureSamplesFast(
  Dem_DTCReadoutBuffer_HandleType  ReadoutBufferId
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_TestDataRequested
 *****************************************************************************/
/*!
 * \brief         Returns whether data was requested for the given buffer
 *
 * \details       Returns whether data was requested for the given buffer
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 *
 * \return        TRUE
 *                The given buffer contains or will contain data
 * \return        FALSE
 *                There is no data requested for the given buffer
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTCReadoutBuffer_TestDataRequested(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_TestResultReady
 *****************************************************************************/
/*!
 * \brief         Returns whether the result of the data selection is available
 *
 * \details       Returns whether the result of the data selection is available
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 *
 * \return        TRUE
 *                The given buffer is ready.
 * \return        FALSE
 *                The given buffer is still updating.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTCReadoutBuffer_TestResultReady(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_TestStoredDataAvailable
 *****************************************************************************/
/*!
 * \brief         Returns whether data is stored or not
 *
 * \details       Returns whether data is stored or not
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 *
 * \return        TRUE
 *                The buffer holds the data stored for the requested event
 * \return        FALSE
 *                There is no stored data for the requested event
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTCReadoutBuffer_TestStoredDataAvailable(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_GetExtendedEntryIndex
 *****************************************************************************/
/*!
 * \brief         Returns the extended entry index
 *
 * \details       Returns the current extended entry index of the readout
 *                buffer
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 * \param[in]     ReadoutBufferDataIndex
 *                Index to ReadoutBufferData inside the ReadoutBuffer
 *
 * \return        The extended entry index
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DTCReadoutBuffer_GetExtendedEntryIndex(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId,
  CONST(Dem_DTCReadoutBuffer_ReadoutBufferDataIndexType, AUTOMATIC)  ReadoutBufferDataIndex
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_GetExtendedEntryIterator
 *****************************************************************************/
/*!
 * \brief         Returns the extended entry iterator
 *
 * \details       Returns the extended entry iterator
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 * \param[in]     ReadoutBufferDataIndex
 *                Index to ReadoutBufferData inside the ReadoutBuffer
 *
 * \return        The extended entry iterator
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_ExtendedEntry_IterType, DEM_CODE)
Dem_DTCReadoutBuffer_GetExtendedEntryIterator(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId,
  CONST(Dem_DTCReadoutBuffer_ReadoutBufferDataIndexType, AUTOMATIC)  ReadoutBufferDataIndex
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_SetExtendedEntryIterator
 *****************************************************************************/
/*!
 * \brief         Sets the extended entry iterator
 *
 * \details       Sets the extended entry iterator
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 * \param[in]     ReadoutBufferDataIndex
 *                Index to ReadoutBufferData inside the ReadoutBuffer
 * \param[in]     ExtendedEntryIter
 *                The new extended entry iterator
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCReadoutBuffer_SetExtendedEntryIterator(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId,
  CONST(Dem_DTCReadoutBuffer_ReadoutBufferDataIndexType, AUTOMATIC)  ReadoutBufferDataIndex,
  CONST(Dem_ExtendedEntry_IterType, AUTOMATIC)  ExtendedEntryIter
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_IncExtendedEntryIndex
 *****************************************************************************/
/*!
 * \brief         Increments the extended entry index
 *
 * \details       Increments the extended entry index of the readout buffer
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 * \param[in]     ReadoutBufferDataIndex
 *                Index to ReadoutBufferData inside the ReadoutBuffer
 * \param[in]     ERecType
 *                Type of ExtendedData Record
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCReadoutBuffer_IncExtendedEntryIndex(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId,
  CONST(Dem_DTCReadoutBuffer_ReadoutBufferDataIndexType, AUTOMATIC)  ReadoutBufferDataIndex,
  CONST(uint8, AUTOMATIC)  ERecType
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_GetExtendedRecordNumber
 *****************************************************************************/
/*!
 * \brief         Returns the extended data record number
 *
 * \details       Returns the extended data record number
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 *
 * \return        The extended data record number
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DTCReadoutBuffer_GetExtendedRecordNumber(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId
  );
#endif




#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_TestSnapshotRecordSelected
 *****************************************************************************/
/*!
 * \brief         Returns whether a snapshot record is selected
 *
 * \details       Returns whether a snapshot record is selected
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 *
 * \return        TRUE
 *                A snapshot record has been selected
 * \return        FALSE
 *                No snapshot record has been selected
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTCReadoutBuffer_TestSnapshotRecordSelected(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId
  );
#endif




#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_TestExtendedRecordSelected
 *****************************************************************************/
/*!
 * \brief         Returns whether an extended data record record is selected
 *
 * \details       Returns whether an extended data record record is selected
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 *
 * \return        TRUE
 *                An extended data record has been selected
 * \return        FALSE
 *                An extended data record has not been selected
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTCReadoutBuffer_TestExtendedRecordSelected(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId
  );
#endif




#if ((DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_SRECS == STD_ON))
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_GetSnapshotEntryIterator
 *****************************************************************************/
/*!
 * \brief         Return the snapshot record entry iterator
 *
 * \details       Return the snapshot record entry iterator
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 * \param[in]     ReadoutBufferDataIndex
 *                Index to ReadoutBufferData inside the ReadoutBuffer
 *
 * \return        The snapshot record entry iterator
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON && DEM_CFG_SUPPORT_SRECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_SnapshotEntry_IterType, DEM_CODE)
Dem_DTCReadoutBuffer_GetSnapshotEntryIterator(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId,
  CONST(Dem_DTCReadoutBuffer_ReadoutBufferDataIndexType, AUTOMATIC)  ReadoutBufferDataIndex
);
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_SetSnapshotEntryIterator
 *****************************************************************************/
/*!
 * \brief         Sets the snapshot record entry iterator
 *
 * \details       Sets the snapshot record entry iterator
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 * \param[in]     ReadoutBufferDataIndex
 *                Index to ReadoutBufferData inside the ReadoutBuffer
 * \param[in]     SnapshotEntryIter
 *                The new value
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCReadoutBuffer_SetSnapshotEntryIterator(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId,
  CONST(Dem_DTCReadoutBuffer_ReadoutBufferDataIndexType, AUTOMATIC)  ReadoutBufferDataIndex,
  CONST(Dem_Cfg_SnapshotEntry_IterType, AUTOMATIC)  SnapshotEntryIter
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_GetSnapshotRecordNumber
 *****************************************************************************/
/*!
 * \brief         Returns the selected snapshot record number
 *
 * \details       Returns the selected snapshot record number
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 *
 * \return        The record number of the selected snapshot record
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DTCReadoutBuffer_GetSnapshotRecordNumber(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId
  );
#endif




#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_GetSnapshotRecordSource
 *****************************************************************************/
/*!
 * \brief         Returns the source
 *
 * \details       Returns the snapshot record source
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 *
 * \return        The source
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTCReadoutBuffer_SnapshotSourceType, DEM_CODE)
Dem_DTCReadoutBuffer_GetSnapshotRecordSource(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_SetSnapshotRecordSource
 *****************************************************************************/
/*!
 * \brief         Sets the snapshot source type
 *
 * \details       Sets the snapshot source type
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 * \param[in]     Source
 *                The new value
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCReadoutBuffer_SetSnapshotRecordSource(                                                                                    
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId,
  CONST(Dem_DTCReadoutBuffer_SnapshotSourceType, AUTOMATIC)  Source
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_GetSnapshotSourceIterator
 *****************************************************************************/
/*!
 * \brief         Returns the source iterator
 *
 * \details       Returns the source iterator
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 * \param[in]     ReadoutBufferDataIndex
 *                Index to ReadoutBufferData inside the ReadoutBuffer
 *
 * \return        The source iterator
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_ComplexIterType, DEM_CODE)
Dem_DTCReadoutBuffer_GetSnapshotSourceIterator(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId, 
  CONST(Dem_DTCReadoutBuffer_ReadoutBufferDataIndexType, AUTOMATIC)  ReadoutBufferDataIndex
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_SetSnapshotSourceIterator
 *****************************************************************************/
/*!
 * \brief         Sets the source iterator
 *
 * \details       Sets the source iterator
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 * \param[in]     ReadoutBufferDataIndex
 *                Index to ReadoutBufferData inside the ReadoutBuffer
 * \param[in]     SourceIterator
 *                The new value
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCReadoutBuffer_SetSnapshotSourceIterator(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId,
  CONST(Dem_DTCReadoutBuffer_ReadoutBufferDataIndexType, AUTOMATIC)  ReadoutBufferDataIndex,
  CONST(Dem_Cfg_ComplexIterType, AUTOMATIC)  SourceIterator
);
#endif

/* ****************************************************************************
 * Dem_DTCReadoutBuffer_GetMemoryEntryId
 *****************************************************************************/
/*!
 * \brief         Returns the memory entry Id for the given readout buffer
 *
 * \details       Returns the memory entry Id for the given readout buffer
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 * \param[in]     ReadoutBufferDataIndex
 *                Index to ReadoutBufferData inside the ReadoutBuffer
 *
 * \return        The memory entry Id
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryEntryHandleType, DEM_CODE)
Dem_DTCReadoutBuffer_GetMemoryEntryId(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(Dem_DTCReadoutBuffer_ReadoutBufferDataIndexType, AUTOMATIC)  ReadoutBufferDataIndex
  );

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_GetEventId
 *****************************************************************************/
/*!
 * \brief         Get EventId of readout buffer.
 *
 * \details       Get EventId of readout buffer.
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer, derived from the ClientId.
 * \param[in]     ReadoutBufferDataIndex
 *                Index to ReadoutBufferData inside the ReadoutBuffer
 *
 * \return        The EventId of the readout buffer
 *
 * \pre           Dem_DTCReadoutBuffer_GetState() != DEM_DTCREADOUTBUFFER_UNUSED
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_DTCReadoutBuffer_GetEventId(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(Dem_DTCReadoutBuffer_ReadoutBufferDataIndexType, AUTOMATIC)  ReadoutBufferDataIndex
  );
#endif




#if ((DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_GetMasterEventId
 *****************************************************************************/
/*!
 * \brief         Get Master EventId of readout buffer.
 *
 * \details       Get Master EventId of readout buffer.
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer, derived from the ClientId.
 *
 * \return        Master event Id of the combined DTC group.
 *
 * \pre           -
 * \config        (DEM_CFG_SUPPORT_DCM == STD_ON) 
 *                && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_DTCReadoutBuffer_GetMasterEventId(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId
  );
#endif




#if ((DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_GetNumberOfOccupiedSlots
 *****************************************************************************/
/*!
 * \brief         Get number of occupied ReadoutBufferData entries.
 *
 * \details       Get number of occupied ReadoutBufferData entries.
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer, derived from the ClientId.
 *
 * \return        Number of occupied slots in readout buffer.
 *
 * \pre           -
 * \config        (DEM_CFG_SUPPORT_DCM == STD_ON) 
 *                && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DTCReadoutBuffer_GetNumberOfOccupiedSlots(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId
  );
#endif




#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_GetMemoryId
 *****************************************************************************/
/*!
 * \brief         Get the memory location
 *
 * \details       Get the memory locations of the given record
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer, derived from the ClientId.
 *
 * \return        Size of a memory entry Data record in bytes.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DTCReadoutBuffer_GetMemoryId(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_GetOBDData_IsStored
 *****************************************************************************/
/*!
 * \brief         Returns the stored status of OBD FreezeFrame
 *
 * \details       Returns the stored status of OBD FreezeFrame for requested
 *                ReadoutBufferId
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer, derived from the ClientId.
 *
 * \return        Stored status of OBD FreezeFrame
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTCReadoutBuffer_GetOBDData_IsStored(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId
  );
#endif

#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) \
   && (DEM_CFG_SUPPORT_OBDII == STD_ON) \
   && (DEM_CFG_SUPPORT_OBDII_FREEZEFRAME_IN_SVC19 == STD_ON) )
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_GetPtrToOBDFreezeFrameBuffer
 *****************************************************************************/
/*!
 * \brief         Returns pointer to OBD FreezeFrame buffer
 *
 * \details       Returns pointer to OBD FreezeFrame buffer in ReadoutBuffer
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer, derived from the ClientId.
 *
 * \return        Pointer to OBD FreezeFrame buffer in ReadoutBuffer
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *                && DEM_CFG_SUPPORT_OBDII == STD_ON
 *                && DEM_CFG_SUPPORT_OBDII_FREEZEFRAME_IN_SVC19 == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DataPtrType, DEM_CODE)
Dem_DTCReadoutBuffer_GetPtrToOBDFreezeFrameBuffer(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_SetExtendedEntryIndex
 *****************************************************************************/
/*!
 * \brief         Sets the extended entry index
 *
 * \details       Sets the new extended entry index of the readout
 *                buffer
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 * \param[in]     ReadoutBufferDataIndex
 *                Index to ReadoutBufferData inside the ReadoutBuffer
 * \param[in]     ExtendedEntryIndex
 *                New extended entry index
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCReadoutBuffer_SetExtendedEntryIndex(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId,
  CONST(Dem_DTCReadoutBuffer_ReadoutBufferDataIndexType, AUTOMATIC)  ReadoutBufferDataIndex,
  CONST(uint8, AUTOMATIC)  ExtendedEntryIndex
  );
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_DTCReadoutBuffer_Public Public Methods
 * \{
 */

/* ****************************************************************************
* Dem_DTCReadoutBuffer_GetMemIndependentCounterPtr
*****************************************************************************/
/*!
* \brief         Get pointer to copied memory indepedent counter in readout buffer.
*
* \details       Get pointer to copied memory indepedent counter in readout buffer.
*
* \param[in]     ReadoutBufferId
*                Index of the ReadoutBuffer, derived from the ClientId.
* \return        Pointer to memory indepedent counter copy in corresponding
*                readout buffer
* \pre           -
*
* \context       TASK|ISR2
* \synchronous   TRUE
* \reentrant     TRUE
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_ReadoutMemIndeCounterPtrType, DEM_CODE)
Dem_DTCReadoutBuffer_GetMemIndependentCounterPtr(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId
);

#if (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_TestCombinedEventSelected
 *****************************************************************************/
/*!
 * \brief         Tests whether a combined DTC is selected in the readout buffer.
 *
 * \details       Tests whether a combined DTC is selected in the readout buffer.
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 *
 * \return        TRUE: Combined DTC is selected
 *                FALSE: Non-Combined DTC is selected
 *                
 * \pre           -
 * \config        DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON 
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTCReadoutBuffer_TestCombinedEventSelected(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId
  );
#endif

#if ((DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON) && (DEM_CFG_SUPPORT_SRECS == STD_ON))
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_GetSnapShotHeaderBitMaskIndex
 *****************************************************************************/
/*!
 * \brief         Get the index which is currently pointed to by the iterator
 *
 * \details       Get the index which is currently pointed to by the iterator
 *
 * \param[in]     IterPtr
 *                Pointer to the iterator
 * \param[in]     CombinedGroupIdx
 *                Index to the combined DTC group
 *
 * \return        Index which is currently pointed to by the iterator
 *
 * \pre           IterPtr has been initialized
 * \config        (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON) 
 *                && (DEM_CFG_SUPPORT_SRECS == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DTCReadoutBuffer_GetSnapShotHeaderBitMaskIndex(
  CONSTP2CONST(Dem_DTCReadoutBuffer_RecordNumberIteratorType, AUTOMATIC, AUTOMATIC)  IterPtr,
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC) CombinedGroupIdx
  );
#endif

#if ((DEM_CFG_SUPPORT_DCM == STD_ON)\
     && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)\
     && ((DEM_CFG_SUPPORT_SRECS == STD_ON) || (DEM_CFG_SUPPORT_ERECS == STD_ON))) 
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_GetRecordNumberIterator
 *****************************************************************************/
/*!
 * \brief         Return the readout buffer record number iterator
 *
 * \details       Return the readout buffer record number iterator
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 * \param[in]     RequestedRecordType
 *                Indicates whether the snapshot record or extended data record 
 *                has to be fetched
 *
 * \return        The readout buffer record number iterator
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *                && DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON 
 *                && (DEM_CFG_SUPPORT_SRECS == STD_ON || DEM_CFG_SUPPORT_ERECS == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTCReadoutBuffer_RecordNumberIteratorType, DEM_CODE)
Dem_DTCReadoutBuffer_GetRecordNumberIterator(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId
  );
#endif

#if ((DEM_CFG_SUPPORT_DCM == STD_ON)\
     && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)\
     && ((DEM_CFG_SUPPORT_SRECS == STD_ON) || (DEM_CFG_SUPPORT_ERECS == STD_ON))) 
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_SetRecordNumberIterator
 *****************************************************************************/
/*!
 * \brief         Sets the snapshot record entry iterator
 *
 * \details       Sets the snapshot record entry iterator
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 * \param[in]     RecordIterPtr
 *                The new value for readout buffer record number iterator
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *                && DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON 
 *                && (DEM_CFG_SUPPORT_SRECS == STD_ON || DEM_CFG_SUPPORT_ERECS == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCReadoutBuffer_SetRecordNumberIterator(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId,
  CONSTP2CONST(Dem_DTCReadoutBuffer_RecordNumberIteratorType, AUTOMATIC, AUTOMATIC) RecordIterPtr
  );
#endif

#if ((DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON))
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_GetGlobalSnapshotDataPtr
 *****************************************************************************/
/*!
 * \brief         Returns the pointer to the global snapshot data in the 
 *                memory entry of the readout buffer.
 *
 * \details       Returns the pointer to the global snapshot data in the 
 *                memory entry of the readout buffer.
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer, derived from the ClientId.
 * \param[in]     ReadoutBufferDataIndex
 *                Index to ReadoutBufferData inside the ReadoutBuffer
 *
 * \return        Pointer to the beginning of the global snapshot data set.
 *
 * \pre           Readout buffer is initiliazed.
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON &&
 *                DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DataPtrType, DEM_CODE)
  Dem_DTCReadoutBuffer_GetGlobalSnapshotDataPtr(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(Dem_DTCReadoutBuffer_ReadoutBufferDataIndexType, AUTOMATIC)  ReadoutBufferDataIndex
  );
#endif

#if ((DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON))
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_TestGlobalSnapshotStored
 *****************************************************************************/
/*!
 * \brief         Returns whether global snapshot is stored.
 *
 * \details       Returns whether global snapshot is stored.
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer, derived from the ClientId.
 * \param[in]     ReadoutBufferDataIndex
 *                Index to ReadoutBufferData inside the ReadoutBuffer
 *
 * \return        TRUE, global snapshot is stored
 *
 * \return        FALSE, global snapshot is not stored
 *
 * \pre           Readout buffer is initiliazed.
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON &&
 *                DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
  Dem_DTCReadoutBuffer_TestGlobalSnapshotStored(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(Dem_DTCReadoutBuffer_ReadoutBufferDataIndexType, AUTOMATIC)  ReadoutBufferDataIndex
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_Init
 *****************************************************************************/
/*!
 * \brief         Initialize memory entry.
 *
 * \details       Initialize memory entry.
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer, derived from the ClientId.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ReadoutBuffer Ids
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCReadoutBuffer_Init(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_CheckAndSetState
 *****************************************************************************/
/*!
 * \brief         Check state of a ReadoutBuffer entry, save current request if
 *                it is new.
 *
 * \details       Check state of a ReadoutBuffer entry, save current request if
 *                it is new.
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer, derived from the ClientId.
 * \param[in]     EventId
 *                New EventId for comparison, stored in ReadoutBuffer with a
 *                new request.
 * \param[in]     MemoryId
 *                New MemoryId for comparison, stored in ReadoutBuffer with a
 *                new request.
 * \param[in]     DTCSelector
 *                Handle for DTC Selector
 *
 * \return        E_OK
 *                ReadoutBuffer contains given EventId, MemoryId
 *                configuration and the copying of event data (MainFunction)
 *                has finished - current request is identical repetition of
 *                previous, no data change.
 * \return        DEM_PENDING
 *                Either ReadoutBuffer is unused, so it contains no valid
 *                data - store current request as new request and QUEUE it for
 *                MainFunction to copy the event data.
 *                Or ReadoutBuffer contains given EventId, MemoryId
 *                configuration but the copying of event data (MainFunction)
 *                has NOT finished yet - no data change.
 * \return        E_NOT_OK
 *                ReadoutBuffer contains different EventId, MemoryId
 *                configuration, current request is different to previous -
 *                no data change.
 *
 * \pre           For event combination type 1 and 2 passed EventId must be the 
 *                MasterEventId of the combined group
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ReadoutBuffer Ids
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_DTCReadoutBuffer_CheckAndSetState(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)      ReadoutBufferId,
  CONST(Dem_EventIdType, AUTOMATIC)                      EventId,
  CONST(uint8, AUTOMATIC)                                MemoryId,
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)           DTCSelector
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_FillData_NormalEvent
 *****************************************************************************/
/*!
 * \brief         Populate readout buffer with data.
 *
 * \details       Populate readout buffer with data by copying the record from
 *                the primary/secondary memory.
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer, derived from the ClientId.
 * \param[in]     DTCSelector
 *                Handle for DTC Selector 
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ReadoutBuffer Ids
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
  Dem_DTCReadoutBuffer_FillData_NormalEvent(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)      DTCSelector
  );
#endif

#if ((DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_FillData_CombinedEvent
 *****************************************************************************/
/*!
 * \brief         Populate readout buffer with data from all subevents of a 
 *                combined DTC.
 *
 * \details       Populate readout buffer with data from all subevents of a 
 *                combined DTC.
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer, derived from the ClientId.
 * \param[in]     DTCSelector
 *                Handle for DTC Selector 
 *
 * \pre           Function shall be called only for combined events belonging
 *                to a Type 2 combined group
 *
 * \config        ((DEM_CFG_SUPPORT_DCM == STD_ON) 
 *                 && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ReadoutBuffer Ids
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
  Dem_DTCReadoutBuffer_FillData_CombinedEvent(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)      DTCSelector
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_FreeBuffer
 *****************************************************************************/
/*!
 * \brief         Release the memory entry.
 *
 * \details       Release the memory entry calling Dem_EnableDTCRecordUpdate.
 * 
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer, derived from the ClientId.
 * \param[in]     DTCSelector
 *                Handle for DTC Selector 
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ReadoutBuffer Ids
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCReadoutBuffer_FreeBuffer(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)      DTCSelector
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_SelectExtendedDataRecord
 *****************************************************************************/
/*!
 * \brief         Selects a data record
 *
 * \details       Initializes the iterator for the selected event.
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 * \param[in]     ExtendedDataNumber
 *                The extended data number
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ReadoutBuffer Ids
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCReadoutBuffer_SelectExtendedDataRecord(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(uint8, AUTOMATIC) ExtendedDataNumber
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_SelectSnapshotRecord
 *****************************************************************************/
/*!
 * \brief         Selects a data record
 *
 * \details       Initializes the iterator for the selected event.
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 * \param[in]     RecordNumber
 *                The selected record number
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ReadoutBuffer Ids
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCReadoutBuffer_SelectSnapshotRecord(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(uint8, AUTOMATIC) RecordNumber
  );
#endif

#if ((DEM_CFG_SUPPORT_ERECS == STD_ON) && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_GetEventDataIndex
 *****************************************************************************/
/*!
 * \brief         Retrieves the readout buffer data index corresponding 
 *                to an event
 *
 * \details       Retrieves the readout buffer data index corresponding 
 *                to an event
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 * \param[in]     EventId
 *                The requested EventId
 *
 * \return        Valid ReadoutBuffer Data Index
 *                If the requested event is stored in Readout Buffer
 *                DEM_CFG_NUMBER_OF_SUBEVENT_DATA_READOUTBUFFERS
 *                If the requested event is not stored in Readout Buffer
 *
 * \pre           -
 * \config        (DEM_CFG_SUPPORT_ERECS == STD_ON) 
 *                 && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(Dem_DTCReadoutBuffer_ReadoutBufferDataIndexType, DEM_CODE)
Dem_DTCReadoutBuffer_GetEventDataIndex(                                                                                        /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(Dem_EventIdType, AUTOMATIC) EventId
);
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_DTCREADOUTBUFFER_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_DTCReadoutBuffer_Interface.h
 *********************************************************************************************************************/
