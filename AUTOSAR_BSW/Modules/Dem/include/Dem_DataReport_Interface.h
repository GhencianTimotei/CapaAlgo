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
/*! \ingroup    Dem_RecordReader
 *  \defgroup   Dem_DataReport DataReport
 *  \{
 *  \file       Dem_DataReport_Interface.h
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

#if !defined (DEM_DATAREPORT_INTERFACE_H)
#define DEM_DATAREPORT_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_DataReport_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_DataReportIF_Public Public Methods
 * \{
 */
#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_DataReport_CopyPidFromObdIIFreezeFrame
 *****************************************************************************/
/*!
 * \brief         Copy the requested PID data into the given buffer
 *
 * \details       The stored OBD freezeframe data of an event is written to
 *                DestinationBuffer in no particular format (raw hex).
 *
 * \param[in]     DataId
 *                Return only the data of this PID.
 * \param[in]     SourceBuffer
 *                Pointer to the source buffer containing freeze frame.
 * \param[in,out] DestinationBuffer
 *                Pointer to the destination buffer structure.
 *
 * \return        E_OK
 *                The requested data was copied to the destination buffer.
 * \return        DEM_NO_SUCH_ELEMENT
 *                The PID is undefined for the event.
 * \return        DEM_BUFFER_TOO_SMALL
 *                The provided buffer size is too small.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_DataReport_CopyPidFromObdIIFreezeFrame(
  CONST(uint16, AUTOMATIC)  DataId,
  CONST(Dem_ConstSharedDataPtrType, AUTOMATIC)  SourceBuffer,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  );
#endif

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 * Dem_DataReport_CopyDidFromWwhObdFreezeFrame
 *****************************************************************************/
/*!
 * \brief         Copy DID data into the given buffer
 *
 * \details       The stored WWH-OBD freezeframe data of an event is written to
 *                DestinationBuffer in no particular format (raw hex).
 *
 * \param[in]     DataId
 *                Return only the data of this DID.
 * \param[in]     MemoryEntry
 *                Handle to memory entry
 * \param[in]     SourceBuffer
 *                Source buffer of WWH-OBD freeze frame data
 * \param[in,out] DestinationBuffer
 *                Pointer to the destination buffer structure.
 *
 * \return        E_OK
 *                The requested data was copied to the destination buffer.
 * \return        E_NOT_OK
 *                Operation could not be performed, e.g. when the data is
 *                concurrently updated.
 * \return        DEM_E_NODATAAVAILABLE
 *                The data is currently not stored for the requested event
 *                or
 *                the event is not WWH-OBD relevant
 *                or
 *                the requested data identifier is undefined for the event.
 * \return        DEM_BUFFER_TOO_SMALL
 *                The provided buffer size is too small.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_WWHOBD == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_DataReport_CopyDidFromWwhObdFreezeFrame(
  CONST(uint16, AUTOMATIC)  DataId,
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC) MemoryEntry,
  CONST(Dem_ConstSharedDataPtrType, AUTOMATIC)  SourceBuffer,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  );
#endif


#if ((DEM_FEATURE_NEED_TIME_SERIES == STD_ON) && (DEM_CFG_SUPPORT_POWERTRAIN == STD_OFF))
/* ****************************************************************************
 * Dem_DataReport_CopyDidTimeSeriesSRec
 *****************************************************************************/
/*!
 * \brief         Extracts a time series snapshot record, or a single DID from it.
 *
 * \details       The stored time series snapshot data of a time series entry
 *                is written to DestinationBuffer in no particular format (raw hex). 
 *
 * \param[in]     DataId
 *                Return only the data of this DID.
 * \param[in]     MemoryIndex
 *                Index to the memory block of the event.
 * \param[in]     EventId
 *                Unique handle of the event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     SourceBuffer
 *                Source buffer of time series snapshot record.
 * \param[in,out] DestinationBuffer
 *                Pointer to destination buffer structure.
 *
 * \return        E_OK
 *                The requested data was copied to the destination buffer.
 * \return        DEM_NO_SUCH_ELEMENT
 *                The data indentifier within the requested record is
 *                undefined.
 * \return        DEM_BUFFER_TOO_SMALL
 *                The provided buffer size is too small.
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
 *                && (DEM_CFG_SUPPORT_POWERTRAIN == STD_OFF)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_DataReport_CopyDidTimeSeriesSRec(
  CONST(uint16, AUTOMATIC)  DataId,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_ConstSharedDataPtrType, AUTOMATIC)  SourceBuffer,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  );
#endif

#if ((DEM_CFG_SUPPORT_DCM == STD_ON)   && (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON))
/* ****************************************************************************
 * Dem_DataReport_GlobalSnapshotCopyData
 *****************************************************************************/
/*!
 * \brief         Copies the contents of a stored global snapshot record
 *
 * \details       This function formats the global snapshot data stored in the 
 *                source according to the UDS specification and copies the result 
 *                into the given destination buffer.
 *                The function will abort copying data if the destination is
 *                too small.
 *
 * \param[in,out] DestinationBuffer
 *                Pointer to the destination buffer structure
 * \param[in]     SourceBuffer
 *                Pointer to the source buffer
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     MemoryEntryId
 *                The memory entry handle from the readout buffer
 * \param[in]     MemIndeCounterPtr
 *                Pointer to copy of memory indepedent counter in readout buffer or NULL_PTR
 *
 * \pre           A memory entry must have been copied to the intermediate
 *                buffer (see Dem_DcmDisableDTCRecordUpdate)
 * \pre           Existence of the record must be verified before calling this
 *                function, otherwise random data will be copied.
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON &&
 *                DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DataReport_GlobalSnapshotCopyData(
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(Dem_ConstSharedDataPtrType, AUTOMATIC)  SourceBuffer,
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(Dem_Cfg_ReadoutMemIndeCounterPtrType, AUTOMATIC) MemIndeCounterPtr
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DataReport_TimeSeriesPowertrainCopyData
 *****************************************************************************/
/*!
 * \brief         Copies the contents of a time series powertrain snapshot record
 *
 * \details       This function formats the time series powertrain snapshot data 
 *                stored in the source according to the specification and 
 *                copies the result into the given destination buffer.
 *                The function will abort copying data if the destination buffer is
 *                too small.
 *
 * \param[in]     ReadoutBufferId
 *                Handle to readout buffer
 * \param[in,out] DestinationBuffer
 *                Pointer to the destination buffer structure
 *
 * \pre           A time series powertrain snapshot memory entry must have been 
 *                locked (see Dem_DcmDisableDTCRecordUpdate)
 * \pre           Existence of the record must be verified before calling this
 *                function, otherwise random data will be copied.
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DataReport_TimeSeriesPowertrainCopyData(
  Dem_DTCReadoutBuffer_HandleType  ReadoutBufferId,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  );
#endif

#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) \
   && ((DEM_CFG_SUPPORT_SRECS == STD_ON) || (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)) )
/* ****************************************************************************
 * Dem_DataReport_SRecCopyData
 *****************************************************************************/
/*!
 * \brief         Copies the contents of a stored snapshot record
 *
 * \details       This function formats the snapshot data stored in the source
 *                according to the UDS specification and copies the result into
 *                the given destination buffer.
 *                The function will abort copying data if the destination is
 *                too small.
 *
 * \param[in,out] DestinationBuffer
 *                Pointer to the destination buffer structure
 * \param[in]     SourceBuffer
 *                Pointer to the source buffer
 * \param[in]     EventId
 *                Unique handle of the event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     MemIndeCounterPtr
 *                Pointer to copy of memory indepedent counter in readout buffer or NULL_PTR
 *
 * \pre           A memory entry must have been copied to the intermediate
 *                buffer (see Dem_DcmDisableDTCRecordUpdate)
 * \pre           Existence of the record must be verified before calling this
 *                function, otherwise random data will be copied.
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON &&
 *                (DEM_CFG_SUPPORT_SRECS == STD_ON ||
 *                DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DataReport_SRecCopyData(
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(Dem_ConstSharedDataPtrType, AUTOMATIC)  SourceBuffer,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(Dem_Cfg_ReadoutMemIndeCounterPtrType, AUTOMATIC) MemIndeCounterPtr
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 * Dem_DataReport_WWHOBDFreezeFrameCopyData
 *****************************************************************************/
/*!
 * \brief         Copies the contents of the WWH-OBD freeze frame
 *
 * \details       This function formats the WWH-OBD freeze frame data stored in
 *                the source according to the UDS snapshot record specification
 *                and copies the result into the given destination buffer.
 *                The function will abort copying data if the destination is
 *                too small.
 *
 * \param[in,out] DestinationBuffer
 *                Pointer to DestinationBuffer structure
 * \param[in]     SourceBuffer
 *                Pointer to the source buffer
 * \param[in]     EventId
 *                Unique handle of the event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     MemIndeCounterPtr
 *                Pointer to copy of memory indepedent counter in readout buffer or NULL_PTR
 *
 * \pre           A memory entry must have been copied to the intermediate
 *                buffer (see Dem_DcmDisableDTCRecordUpdate)
 * \pre           Existence of the record must be verified before calling this
 *                function, otherwise random data will be copied.
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON &&
 *                DEM_CFG_SUPPORT_WWHOBD == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DataReport_WWHOBDFreezeFrameCopyData(
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(Dem_ConstSharedDataPtrType, AUTOMATIC)  SourceBuffer,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(Dem_Cfg_ReadoutMemIndeCounterPtrType, AUTOMATIC) MemIndeCounterPtr
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_DataReport_ObdIIFreezeFrameCopyPidData
 *****************************************************************************/
/*!
 * \brief         Copy the contents of a PID from the FreezeFrame
 *
 * \details       This function copies the requested data element of a PID into
 *                the provided buffer.
 *
 * \param[in]     FreezeFrameIndex
 *                Index of the event's freeze frame
 * \param[in]     Pid
 *                The PID number
 * \param[in]     DataElementIndex
 *                The index of the data element
 * \param[out]    Buffer
 *                Pointer to the destination buffer
 * \param[in,out] BufSize
 *                In: Size of Buffer. Must be large enough to hold the data.
 *                Out: Number of written bytes.
 *
 * \return        E_OK
 *                The requested PID exists and data was copied
 * \return        E_NOT_OK
 *                The requested PID is not available and data was not copied
 *
 * \pre           Existence of the FreezeFrame must be verified before calling
 *                this function.
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON &&
 *                DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_DataReport_ObdIIFreezeFrameCopyPidData(
  CONST(uint8, AUTOMATIC)  FreezeFrameIndex,
  CONST(uint8, AUTOMATIC)  Pid,
  CONST(uint8, AUTOMATIC)  DataElementIndex,
  CONSTP2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  Buffer,
  CONSTP2VAR(uint16, AUTOMATIC, DEM_DCM_DATA)  BufSize
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_DataReport_ObdIIFreezeFrameCopyUdsData
 *****************************************************************************/
/*!
 * \brief         Copies the contents of an OBD freeze frame.
 *
 * \details       This function formats the OBD freeze frame data stored in the
 *                source according to the UDS snpashot record specification and
 *                copies the result into the given destination buffer.
 *                The function will abort copying data if the destination is
 *                too small.
 *
 * \param[in]     BufferIdx
 *                Index of the event's obd freeze frame
 * \param[in,out] DestinationBuffer
 *                Pointer to DestinationBuffer structure
 * \param[in]     Source
 *                Specifies if ReadoutOutBuffer or OBD FreezeFrame Buffer is used as 
 *                source
 *
 * \pre           Existence of the FreezeFrame must be verified before calling
 *                this function.
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON &&
 *                DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DataReport_ObdIIFreezeFrameCopyUdsData(
  CONST(Dem_DataReport_BufferIndexType, AUTOMATIC)  BufferIdx,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint8, AUTOMATIC)  Source
  );
#endif

#if (DEM_CFG_SUPPORT_SRECS == STD_ON)
/* ****************************************************************************
 * Dem_DataReport_CopyDidSRec
 *****************************************************************************/
/*!
 * \brief         Extracts a snapshot record, or a single DID from it.
 *
 * \details       The stored snapshot data of an event memory entry is written
 *                to DestinationBuffer in no particular format.
 *                The record number 0xff (in this case: most recent snapshot)
 *                is supported only in configurations using "calculated" record
 *                numbers.
 *
 * \param[in]     DataId
 *                Return only the data of this DID.
 * \param[in]     MemoryEntry
 *                Handle to memory entry
 * \param[in]     SourceBuffer
 *                Source buffer of snapshot data
 * \param[in,out] DestinationBuffer
 *                Pointer to the destination buffer structure.
 *
 * \return        E_OK
 *                The requested data was copied to the destination buffer.
 * \return        DEM_NO_SUCH_ELEMENT
 *                The requested data indentifier is undefined within the
 *                requested record.
 * \return        DEM_BUFFER_TOO_SMALL
 *                The provided buffer size is too small.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_SRECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_DataReport_CopyDidSRec(
  CONST(uint16, AUTOMATIC)  DataId,
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntry,
  CONST(Dem_ConstSharedDataPtrType, AUTOMATIC)  SourceBuffer,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  );
#endif

#if (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
/* ****************************************************************************
 * Dem_DataReport_CopyDidGlobalSRec
 *****************************************************************************/
/*!
 * \brief         Extracts a single DID from a global snapshot record.
 *
 * \details       DID data of a stored global snapshot is written to 
 *                DestinationBuffer in no particular format.
 *
 * \param[in]     DataId
 *                Return only the data of this DID.
 * \param[in]     MemoryEntry
 *                Handle to memory entry
 * \param[in,out] DestinationBuffer
 *                Pointer to the destination buffer structure.
 *
 * \return        E_OK
 *                The requested data was copied to the destination buffer.
 * \return        DEM_NO_SUCH_ELEMENT
 *                The requested data indentifier is undefined within the
 *                requested record.
 * \return        DEM_BUFFER_TOO_SMALL
 *                The provided buffer size is too small.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_DataReport_CopyDidGlobalSRec(
  CONST(uint16, AUTOMATIC)  DataId,
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntry,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  );
#endif

/* ****************************************************************************
 * Dem_DataReport_CopyExtendedDataRecord
 *****************************************************************************/
/*!
 * \brief         Copy a record into the given buffer
 *
 * \details       Copy records of types "internal", "global" and "user"
 *
 * \param[in]     ExtendedEntryIndex
 *                Index of the extended data record
 * \param[in]     CfgERecIndex
 *                Handle to the extended record descriptor table
 * \param[in]     DidCopyInfoPtr
 *                CopyDid context
 *
 * \return        E_OK
 *                Data was copied
 * \return        DEM_NO_SUCH_ELEMENT
 *                No data was copied
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_DataReport_CopyExtendedDataRecord(
  CONST(uint8, AUTOMATIC) ExtendedEntryIndex,
  CONST(Dem_Cfg_ERecIndexType, AUTOMATIC) CfgERecIndex,
  CONST(Dem_DataReport_DidCopyInfoPtrType, AUTOMATIC)  DidCopyInfoPtr
  );

/* ****************************************************************************
 * Dem_DataReport_InitDidCopyInfo
 *****************************************************************************/
/*!
 * \brief         Initializes the passed DidCopyInfo context.
 *
 * \details       Initializes the passed DidCopyInfo context with the values,
 *                passed as function arguments.
 *
 * \param[in,out] DidCopyInfoPtr
 *                Pointer to DidCopyInfo context
 * \param[in]     DestinationBuffer
 *                Destination buffer structure
 * \param[in]     EventId
 *                Unique handle of the Event
 * \param[in]     MemoryEntryId
 *                Handle for memory entry
 * \param[in]     MemIndeCounterPtr
 *                Pointer to copy of memory indepedent counters in readout buffer 
 *                or NULL_PTR for OBD II freeze frame or Swc read-outs

 *
 * \pre           Pointer to CopdDidInfo is valid and passed DestinationBuffer is valid
 * \config        DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON  ||
 *                DEM_FEATURE_NEED_OBD == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DataReport_InitDidCopyInfo(
  CONST(Dem_DataReport_DidCopyInfoPtrType, AUTOMATIC)  DidCopyInfoPtr,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(Dem_Cfg_ReadoutMemIndeCounterPtrType, AUTOMATIC) MemIndeCounterPtr
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_DATAREPORT_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_DataReport_Interface.h
 *********************************************************************************************************************/
