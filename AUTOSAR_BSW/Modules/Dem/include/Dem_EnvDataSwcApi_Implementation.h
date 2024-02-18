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
/*! \addtogroup Dem_EnvDataSwcApi
 *  \{
 *  \file       Dem_EnvDataSwcApi_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    The EnvDataSwcApi subcomponent contains APIs to read the environmental data (ExtendedData, FreezeFrame...) 
                for SWC APIs.
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_ENVDATASWCAPI_IMPLEMENTATION_H)
#define DEM_ENVDATASWCAPI_IMPLEMENTATION_H

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
#include "Dem_EnvDataSwcApi_Interface.h"

/* Includes to access public functions belonging to other (top level)/ (logical)/- units to be used by this Unit */
/* ------------------------------------------------------------------------- */
#include "Dem_Core_Interface.h"
#include "Dem_FaultMemory_Interface.h"
#include "Dem_Client_Interface.h"
#include "Dem_DataReport_Interface.h"
#include "Dem_Dcm_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_EnvDataSwcApi_Private Private Methods
 * \{
 */

/* ****************************************************************************
 * Dem_EnvDataSwcApi_CopyPidFromObdIIFreezeFrame
 *****************************************************************************/
/*!
 * \brief         Extracts the OBD freezeframe, or a single PID from it
 *
 * \details       The stored OBD freezeframe data of an event is written to
 *                DestBuffer in no particular format (raw hex).
 *
 * \param[in]     RepresentativeEventId
 *                Unique handle of the UDS DTC.
 *                The RepresentativeEventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     DataId
 *                Return only the data of this PID.
 * \param[in,out] DestinationBuffer
 *                Pointer to the destination buffer structure.
 *
 * \return        E_OK
 *                The requested data was copied to the destination buffer.
 * \return        DEM_NO_SUCH_ELEMENT
 *                The data is currently not stored for the requested event
 *                or
 *                the event is not OBD relevant
 *                or
 *                the PID is undefined for the event.
 * \return        DEM_BUFFER_TOO_SMALL
 *                The provided buffer size is too small.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_EnvDataSwcApi_CopyPidFromObdIIFreezeFrame(
  CONST(Dem_EventIdType, AUTOMATIC)  RepresentativeEventId,
  CONST(uint16, AUTOMATIC)  DataId,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  );

/* ****************************************************************************
 * Dem_EnvDataSwcApi_CopyDidFromWwhObdFreezeFrame
 *****************************************************************************/
/*!
 * \brief         Extracts the WWH-OBD freezeframe, or a single DID from it
 *
 * \details       The stored WWH-OBD freezeframe data of an event is written to
 *                DestBuffer in no particular format (raw hex).
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     DataId
 *                Return only the data of this DID.
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
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_EnvDataSwcApi_CopyDidFromWwhObdFreezeFrame(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint16, AUTOMATIC)  DataId,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  );

#if ((DEM_FEATURE_NEED_TIME_SERIES == STD_ON) && (DEM_CFG_SUPPORT_POWERTRAIN == STD_OFF))
/* ****************************************************************************
 * Dem_EnvDataSwcApi_CopyDidFromTimeSeriesSRec
 *****************************************************************************/
/*!
 * \brief         Extracts a time series snapshot record, or a single DID from it
 *
 * \details       The stored time series snapshot data of the event is written to
 *                DestBuffer in no particular format.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     RecordNumber
 *                Snapshot record number.
 * \param[in]     DataId
 *                Return only the data of this DID.
 * \param[in,out] DestinationBuffer
 *                Pointer to destination buffer structure
 *
 * \return        E_OK
 *                The requested data was copied to the destination buffer
 * \return        E_NOT_OK
 *                Operation could not be performed, e.g. when the data is
 *                concurrently updated.
 * \return        DEM_NO_SUCH_ELEMENT
 *                The data is currently not stored for the requested event
 *                or
 *                the RecordNumber for the given event is undefined
 *                or
 *                the data indentifier within the requested record is
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
Dem_EnvDataSwcApi_CopyDidFromTimeSeriesSRec(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  RecordNumber,
  CONST(uint16, AUTOMATIC)  DataId,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  );
#endif


#if (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
/* ****************************************************************************
 * Dem_EnvDataSwcApi_CopyDidFromGlobalSRec
 *****************************************************************************/
/*!
 * \brief         Extracts requested DID of global snapshot record
 *
 * \details       The stored global snapshot data of the event is written to
 *                DestBuffer in no particular format.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     DataId
 *                Return only the data of this DID.
 * \param[in,out] DestinationBuffer
 *                Pointer to the destination buffer structure.
 *
 * \return        E_OK
 *                The requested data was copied to the destination buffer.
 * \return        E_NOT_OK
 *                The requested data was not copied due to an error. E.g. when
 *                called with invalid arguments, or the data is concurrently
 *                updated.
 * \return        DEM_NO_SUCH_ELEMENT
 *                The requested event data is not currently stored (but the
 *                request was valid)
 *                or
 *                the requested DataId is not supported by the event.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_EnvDataSwcApi_CopyDidFromGlobalSRec(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint16, AUTOMATIC)  DataId,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  );
#endif


#if (DEM_CFG_SUPPORT_SRECS == STD_ON)
/* ****************************************************************************
 * Dem_EnvDataSwcApi_CopyDidFromSRec
 *****************************************************************************/
/*!
 * \brief         Extracts a snapshot record, or a single DID from it
 *
 * \details       The stored snapshot data of the event is written to
 *                DestBuffer in no particular format.
 *                The record number 0xff (in this case: most recent snapshot)
 *                is supported only in configurations using "calculated" record
 *                numbers.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     RecordNumber
 *                Snapshot record number.
 * \param[in]     DataId
 *                Return only the data of this DID.
 * \param[in,out] DestinationBuffer
 *                Pointer to the destination buffer structure.
 *
 * \return        E_OK
 *                The requested data was copied to the destination buffer.
 * \return        E_NOT_OK
 *                The requested data was not copied due to an error. E.g. when
 *                called with invalid arguments, or the data is concurrently
 *                updated.
 * \return        DEM_NO_SUCH_ELEMENT
 *                The requested event data is not currently stored (but the
 *                request was valid)
 *                or
 *                the requested RecordNumber is not supported by the event
 *                or
 *                the requested DataId is not supported by the event.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_SRECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_EnvDataSwcApi_CopyDidFromSRec(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  RecordNumber,
  CONST(uint16, AUTOMATIC)  DataId,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  );
#endif


#if (DEM_CFG_SUPPORT_ERECS == STD_ON)
/* ****************************************************************************
 * Dem_EnvDataSwcApi_CopyERecs
 *****************************************************************************/
/*!
 * \brief         Extract an extended data record for an event
 *
 * \details       Read and copy the stored extended data record of an event. The
 *                data is written to DestBuffer in no particular format.
 *                The record numbers 0xfe and 0xff are not supported.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     RecordNumber
 *                Extended record number
 * \param[in,out] DestinationBuffer
 *                Pointer to DestinationBuffer context
 *
 *
 * \return        E_OK
 *                Operation was successful.
 *                The requested data was copied to the destination buffer.
 * \return        E_NOT_OK
 *                Operation could not be performed, e.g. when the data is
 *                concurrently updated.
 * \return        DEM_NO_SUCH_ELEMENT
 *                The requested event data is not currently stored (but the
 *                request was valid) OR The requested record number is not
 *                supported by the event.
 * \return        DEM_BUFFER_TOO_SMALL
 *                The provided buffer size is too small.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_ERECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_EnvDataSwcApi_CopyERecs(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  RecordNumber,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer                                                         /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_8.13 */
  );
#endif

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/

/* ****************************************************************************
 % Dem_EnvDataSwcApi_CopyPidFromObdIIFreezeFrame
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
Dem_EnvDataSwcApi_CopyPidFromObdIIFreezeFrame(
  CONST(Dem_EventIdType, AUTOMATIC)  RepresentativeEventId,
  CONST(uint16, AUTOMATIC)  DataId,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer                                                         /* PRQA S 3673 */ /* MD_DEM_8.13_fp */
)
{
  Std_ReturnType lReturnValue;

  lReturnValue = DEM_NO_SUCH_ELEMENT;
#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
  if (Dem_Cfg_EventObdRelated(RepresentativeEventId) == TRUE)
  {
    if ((Dem_GetHiByte(DataId) == 0xf4U)
      || (Dem_GetHiByte(DataId) == 0x00U))
    {
      boolean lModificationDetected;

      do
      {
        uint8 lSelectedIndex;
        lModificationDetected = FALSE;
        
        lSelectedIndex = Dem_Mem_FreezeFrameFindIndex(RepresentativeEventId);
        if (lSelectedIndex != Dem_Cfg_GlobalObdIIFFCount())
        { /* Event has a stored OBD freeze frame */
          Dem_ConstSharedDataPtrType lSourceBuffer;
          uint8 lUpdateState;
          lUpdateState = Dem_Event_GetDataCommitState(RepresentativeEventId);

          if (Dem_Event_TestDataUpdateInProgress(lUpdateState) == FALSE)
          {
            lSourceBuffer = (Dem_ConstSharedDataPtrType)Dem_Mem_FreezeFrameObdIIGetDataPtr(lSelectedIndex);
            lReturnValue = Dem_DataReport_CopyPidFromObdIIFreezeFrame(DataId,                                                    /* SBSW_DEM_POINTER_DESTINATIONBUFFER_SOURCEBUFFER */
              lSourceBuffer,
              DestinationBuffer);

            if ( (lReturnValue == E_OK)
              && (lUpdateState != Dem_Event_GetDataCommitState(RepresentativeEventId)) )                                         /* PRQA S 3415 */ /* MD_DEM_13.5_volatile */
            { /* The OBD II FF block has been modified while trying to copy the stored data. */
              /* We cannot be sure it is still used by the same event nor data, so start from the
              beginning */
              lModificationDetected = TRUE;
              Dem_Data_ResetWriteIndexDestinationBuffer(DestinationBuffer);                                                      /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
            }
          }
          else
          {
            /* The caller task has higher priority than Dem_MainFunction, but we cannot 'wait' for
            the update to complete. The requested data is not available at this moment. */
            lReturnValue = E_NOT_OK;
          }
        }
      }
      while (lModificationDetected == TRUE);
    }
  }
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(RepresentativeEventId)                                                                        /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DataId)                                                                                       /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DestinationBuffer)                                                                            /* PRQA S 3112 */ /* MD_DEM_14.2 */ 
#endif
  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_EnvDataSwcApi_CopyDidFromWwhObdFreezeFrame
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
Dem_EnvDataSwcApi_CopyDidFromWwhObdFreezeFrame(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint16, AUTOMATIC)  DataId,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer                                                         /* PRQA S 3673 */ /* MD_DEM_8.13_fp */
)
{
  Std_ReturnType lReturnValue;
  lReturnValue = DEM_NO_SUCH_ELEMENT;
#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
  if (Dem_Cfg_EventObdRelated(EventId) == TRUE)
  {
    Dem_Cfg_MemoryIndexType lMemoryIndex;
    boolean lModificationDetected;

    do
    {
      lModificationDetected = FALSE;
      lMemoryIndex = Dem_Memory_FindIndex(EventId);

      if (lMemoryIndex != DEM_MEM_INVALID_MEMORY_INDEX)
      {
        uint8 lUpdateState;

        /* The record exists as soon as an primary entry exists, but without critical section it could age or displace */
        lUpdateState = Dem_Event_GetDataCommitState(EventId);

        if (Dem_Event_TestDataUpdateInProgress(lUpdateState) == FALSE)
        { 
          /* This call does not currently interrupt a concurrent data update */
          Dem_Cfg_MemoryEntryHandleType lMemoryEntry;
          Dem_ConstSharedDataPtrType lSourceBuffer;

          lMemoryEntry = Dem_MemoryEntry_GetId(lMemoryIndex);
          lSourceBuffer = (Dem_ConstSharedDataPtrType)Dem_MemoryEntry_GetWwhObdFreezeFrameDataPtr(lMemoryEntry);    

          lReturnValue = Dem_DataReport_CopyDidFromWwhObdFreezeFrame(DataId, lMemoryEntry, lSourceBuffer, DestinationBuffer);    /* SBSW_DEM_POINTER_DESTINATIONBUFFER_SOURCEBUFFER */

          if ( (lReturnValue == E_OK)
            && (lUpdateState != Dem_Event_GetDataCommitState(EventId)) )                                                         /* PRQA S 3415 */ /* MD_DEM_13.5_volatile */
          { /* The memory entry has been modified while trying to copy the stored data. */
            /* We cannot be sure it is still used by the same event, so start from the
            beginning */
            lModificationDetected = TRUE;
            Dem_Data_ResetWriteIndexDestinationBuffer(DestinationBuffer);                                                        /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
          }
        }
        else
        {
          /* The caller task has higher priority than Dem_MainFunction, but we cannot 'wait' for
          the update to complete. The requested data is not available at this moment. */
          lReturnValue = E_NOT_OK;
        }
      }
      else
      {
        /* The requested event is currently not stored in the event memory */
        lReturnValue = DEM_NO_SUCH_ELEMENT;
      }
    } while (lModificationDetected == TRUE);
  }
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DataId)                                                                                       /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DestinationBuffer)                                                                            /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
  return lReturnValue;
}                                                                                                                                /* PRQA S 6030, 6050, 6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

#if ((DEM_FEATURE_NEED_TIME_SERIES == STD_ON) && (DEM_CFG_SUPPORT_POWERTRAIN == STD_OFF))
/* ****************************************************************************
 % Dem_EnvDataSwcApi_CopyDidFromTimeSeriesSRec
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
Dem_EnvDataSwcApi_CopyDidFromTimeSeriesSRec(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  RecordNumber,
  CONST(uint16, AUTOMATIC)  DataId,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
)
{
  Std_ReturnType lReturnValue;

  if (Dem_Dcm_TimeSeriesSRecIsValid(EventId, RecordNumber) == FALSE)
  {
    lReturnValue = DEM_NO_SUCH_ELEMENT;
  }
  else
  {
    Dem_Cfg_MemoryIndexType lTimeSeriesMemoryIndex;
    boolean lModificationDetected;

    do
    {
      Dem_Data_ResetWriteIndexDestinationBuffer(DestinationBuffer);                                                              /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
      lModificationDetected = FALSE;
      lTimeSeriesMemoryIndex = Dem_Memory_FindTimeSeriesIndex(EventId);

      if (lTimeSeriesMemoryIndex == DEM_MEM_INVALID_MEMORY_INDEX)
      {
        /* The requested event is currently not stored in the event memory */
        lReturnValue = DEM_NO_SUCH_ELEMENT;
      }
      else
      { /* The record currently exists, but without critical section it could age or displace */
        uint8 lUpdateState;

        lUpdateState = Dem_Event_GetDataCommitState(EventId);
        if (Dem_Event_TestDataUpdateInProgress(lUpdateState) == TRUE)
        {
          /* The caller task has higher priority than Dem_MainFunction, but we cannot 'wait' for
          the update to complete. The requested data is not available at this moment. */
          lReturnValue = E_NOT_OK;
        }
        else
        { /* This call does not currently interrupt a concurrent data update */
          Dem_Mem_ConstTimeSeriesEntryPtrType lEntry;
          lEntry = Dem_Memory_TimeSeries_GetEntrySafe(lTimeSeriesMemoryIndex);

          if (Dem_FreezeFrameIterator_TimeSeriesSRecIsStored(lEntry, RecordNumber) == TRUE)                                                     /* SBSW_DEM_POINTER_WRITE_TIMESERIESENTRY */
          {
            Dem_ConstSharedDataPtrType lSourceBuffer;
            Dem_Cfg_MemoryIndexType lMemoryIndex;

            if (RecordNumber >= DEM_DCM_SNAPSHOTDATARECORD_TIMESERIES_NORMAL_FIRST)
            {
              lSourceBuffer = 
                Dem_Memory_TimeSeries_EntryManager_GetNormalConstDataPtr(lEntry,                                                 /* SBSW_DEM_POINTER_WRITE_TIMESERIESENTRY */
                RecordNumber - DEM_DCM_SNAPSHOTDATARECORD_TIMESERIES_NORMAL_FIRST
                ); 
            }
#if (DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON)
            else
            {
              lSourceBuffer = 
                Dem_Memory_TimeSeries_EntryManager_GetFastConstDataPtr(lEntry,                                                   /* SBSW_DEM_POINTER_WRITE_TIMESERIESENTRY */
                RecordNumber - DEM_DCM_SNAPSHOTDATARECORD_TIMESERIES_FAST_FIRST
                );    
            }
#else
            else
            {
              lSourceBuffer = NULL_PTR;
            }
#endif
            lMemoryIndex = Dem_Memory_FindIndex(lEntry->EventId);

            lReturnValue = Dem_DataReport_CopyDidTimeSeriesSRec(DataId, 
                           lMemoryIndex,
                           lEntry->EventId,
                           lSourceBuffer,
                           DestinationBuffer
                           );                                                                                                    /* SBSW_DEM_POINTER_DESTINATIONBUFFER_SOURCEBUFFER */                                    
          }
          else
          {
            /* The requested data is currently not stored in a time series entry */
            lReturnValue = DEM_NO_SUCH_ELEMENT;
          }

          if ((lReturnValue == E_OK) &&
              (lUpdateState != Dem_Event_GetDataCommitState(EventId)))                                                           /* PRQA S 3415 */ /* MD_DEM_13.5_volatile */
          { /* The memory entry has been modified while trying to copy the stored data. */
            /* We cannot be sure it is still used by the same event, so start from the
            beginning */
            lModificationDetected = TRUE;
          }
        }
      }
    } while (lModificationDetected == TRUE);
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
#endif

#if (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
/* ****************************************************************************
 % Dem_EnvDataSwcApi_CopyDidFromGlobalSRec
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
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_EnvDataSwcApi_CopyDidFromGlobalSRec(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint16, AUTOMATIC)  DataId,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
)
{
  Std_ReturnType lReturnValue;
  Dem_Cfg_MemoryIndexType lMemoryIndex;
  boolean lModificationDetected;

  do
  {
    lModificationDetected = FALSE;
    lMemoryIndex = Dem_Memory_FindIndex(EventId);

    if (lMemoryIndex != DEM_MEM_INVALID_MEMORY_INDEX)
    { 
      /* The record currently exists, but without critical section it could age or displace */
      uint8 lUpdateState;

      lUpdateState = Dem_Event_GetDataCommitState(EventId);

      if (Dem_Event_TestDataUpdateInProgress(lUpdateState) == FALSE)
      { 
        /* This call does not currently interrupt a concurrent data update */
        Dem_Cfg_MemoryEntryHandleType lMemoryEntryId;
        lMemoryEntryId = Dem_MemoryEntry_GetId(lMemoryIndex);

        if (Dem_MemoryEntry_TestGlobalSnapshotStored(lMemoryEntryId) == TRUE)                                                    /* SBSW_DEM_POINTER_FORWARD_STACK */
        {
          lReturnValue = Dem_DataReport_CopyDidGlobalSRec(DataId,                                                                /* SBSW_DEM_POINTER_DESTINATIONBUFFER_SOURCEBUFFER */
                                                      lMemoryEntryId,
                                                      DestinationBuffer);
        }
        else
        {
          lReturnValue = DEM_NO_SUCH_ELEMENT;
        }

        if ((lReturnValue == E_OK)
          && (Dem_Event_GetDataCommitState(EventId) != lUpdateState))                                                            /* PRQA S 3415 */ /* MD_DEM_13.5_volatile */
        { /* The memory entry has been modified while trying to copy the stored data. */
          /* We cannot be sure it is still used by the same event, so start from the
          beginning */
          lModificationDetected = TRUE;
          Dem_Data_ResetWriteIndexDestinationBuffer(DestinationBuffer);                                                          /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
        }
      }
      else
      {
        /* The caller task has higher priority than Dem_MainFunction, but we cannot 'wait' for
        the update to complete. The requested data is not available at this moment. */
        lReturnValue = E_NOT_OK;
      }
    }
    else
    {
      /* The requested event is currently not stored in the event memory */
      lReturnValue = DEM_NO_SUCH_ELEMENT;
    }
  } while (lModificationDetected == TRUE);
  return lReturnValue;
}                                                                                                                                /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
#endif /* (DEM_CFG_SUPPORT_SRECS == STD_ON) */

#if (DEM_CFG_SUPPORT_SRECS == STD_ON)
/* ****************************************************************************
 % Dem_EnvDataSwcApi_CopyDidFromSRec
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
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_EnvDataSwcApi_CopyDidFromSRec(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  RecordNumber,
  CONST(uint16, AUTOMATIC)  DataId,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
)
{
  Std_ReturnType lReturnValue;

# if (DEM_CFG_SUPPORT_SRECS_CONFIGURED == STD_ON)
  if (RecordNumber == 0xffu)
  {
    lReturnValue = E_NOT_OK;
  }
  else
# endif
  {
    Dem_Cfg_MemoryIndexType lMemoryIndex;
    boolean lModificationDetected;

    do
    {
      lModificationDetected = FALSE;
      lMemoryIndex = Dem_Memory_FindIndex(EventId);

      if (lMemoryIndex != DEM_MEM_INVALID_MEMORY_INDEX)
      { 
        /* The record currently exists, but without critical section it could age or displace */
        uint8 lUpdateState;

        lUpdateState = Dem_Event_GetDataCommitState(EventId);

        if (Dem_Event_TestDataUpdateInProgress(lUpdateState) == FALSE)
        { 
          /* This call does not currently interrupt a concurrent data update */
          Dem_Cfg_SnapshotEntry_IterType lSnapshotEntryIter;

# if (DEM_CFG_SUPPORT_SRECS_CALCULATED == STD_ON)
          if (RecordNumber == 0xffU)
          {
            Dem_SnapshotEntry_IteratorFindLastStoredEntry(EventId, 
              Dem_MemoryEntry_GetId(lMemoryIndex), &lSnapshotEntryIter);                                                         /* SBSW_DEM_POINTER_FORWARD_STACK */
          }
          else
# endif
          {
            Dem_SnapshotEntry_IteratorFindEntryWithRecordNumber(EventId, RecordNumber,
              Dem_MemoryEntry_GetId(lMemoryIndex), &lSnapshotEntryIter);                                                         /* SBSW_DEM_POINTER_FORWARD_STACK */
          }

          if (Dem_SnapshotEntry_IteratorExists(&lSnapshotEntryIter) == TRUE)                                                     /* SBSW_DEM_POINTER_FORWARD_STACK */
          {
            Dem_Cfg_MemoryEntryHandleType lMemoryEntry;
            Dem_ConstSharedDataPtrType lSourceBuffer;

            lSourceBuffer = Dem_SnapshotEntry_IteratorGetSnapshotRecordDataConstPtr(&lSnapshotEntryIter);                        /* SBSW_DEM_POINTER_FORWARD_STACK */
            lMemoryEntry = Dem_SnapshotEntry_IteratorGetMemoryEntryHandle(&lSnapshotEntryIter);                                  /* SBSW_DEM_POINTER_FORWARD_STACK */
            lReturnValue = Dem_DataReport_CopyDidSRec(DataId,                                                                    /* SBSW_DEM_POINTER_DESTINATIONBUFFER_SOURCEBUFFER */
                                                        lMemoryEntry,
                                                        lSourceBuffer,
                                                        DestinationBuffer);
          }
          else
          {
            lReturnValue = DEM_NO_SUCH_ELEMENT;
          }

          if ((lReturnValue == E_OK)
            && (Dem_Event_GetDataCommitState(EventId) != lUpdateState))                                                          /* PRQA S 3415 */ /* MD_DEM_13.5_volatile */
          { /* The memory entry has been modified while trying to copy the stored data. */
            /* We cannot be sure it is still used by the same event, so start from the
            beginning */
            lModificationDetected = TRUE;
            Dem_Data_ResetWriteIndexDestinationBuffer(DestinationBuffer);                                                        /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
          }
        }
        else
        {
          /* The caller task has higher priority than Dem_MainFunction, but we cannot 'wait' for
          the update to complete. The requested data is not available at this moment. */
          lReturnValue = E_NOT_OK;
        }
      }
      else
      {
        /* The requested event is currently not stored in the event memory */
        lReturnValue = DEM_NO_SUCH_ELEMENT;
      }
    } while (lModificationDetected == TRUE);
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
#endif /* (DEM_CFG_SUPPORT_SRECS == STD_ON) */

#if (DEM_CFG_SUPPORT_ERECS == STD_ON)
/* ****************************************************************************
 % Dem_EnvDataSwcApi_CopyERecs
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
Dem_EnvDataSwcApi_CopyERecs(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  RecordNumber,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  )
{
  Std_ReturnType lReturnValue;
  Dem_Cfg_ERecIndexType lCfgERecIndex;
  Dem_ExtendedEntry_IterType lExtendedEntryIter;
  uint8 lExtendedEntryIndex;

  lCfgERecIndex = 0u;
  lExtendedEntryIndex = 0u;  

  /* Find the requested record, and it's storage location */
  for (Dem_ExtendedEntry_IterInit(EventId, &lExtendedEntryIter);                                                                 /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_ExtendedEntry_IterExists(&lExtendedEntryIter) == TRUE;                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_ExtendedEntry_IterNext(&lExtendedEntryIter))                                                                          /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    lCfgERecIndex = Dem_ExtendedEntry_IterGet(&lExtendedEntryIter);                                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */

    if (RecordNumber == Dem_Cfg_DidNumber(Dem_Cfg_ERecDid(lCfgERecIndex)))
    {
      break;
    }

# if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON)
    if (Dem_Cfg_ERecType(lCfgERecIndex) == DEM_CFG_EREC_TYPE_USER)
    {
      lExtendedEntryIndex += 1u;
    }
# endif
  }

  if (Dem_ExtendedEntry_IterExists(&lExtendedEntryIter) == TRUE)                                                                 /* SBSW_DEM_CALL_ITERATOR_POINTER */
  { /* Found the record, retrieve it from its storage */
    uint8 lRecordType;
    lRecordType = Dem_Cfg_ERecType(lCfgERecIndex);


    { /* A stored record needs to be retrieved from event memory */
      Dem_Cfg_MemoryIndexType lMemoryIndex;
      Dem_Cfg_MemoryEntryHandleType lMemoryEntryId;
      boolean lModificationDetected;
      do
      {
        lModificationDetected = FALSE;
        lMemoryIndex = ((lRecordType != DEM_CFG_EREC_TYPE_GLOBAL) ? Dem_Memory_FindIndex(EventId) : DEM_MEMORYENTRY_HANDLE_INVALID);

        if ((lRecordType == DEM_CFG_EREC_TYPE_GLOBAL) || (lMemoryIndex != DEM_MEM_INVALID_MEMORY_INDEX))
        { /* The record currently exists, but without critical section it could age or displace */
          uint8 lUpdateState;
          lUpdateState = Dem_Event_GetDataCommitState(EventId);

          if (Dem_Event_TestDataUpdateInProgress(lUpdateState) == FALSE)
          { /* This call does not currently interrupt a concurrent data update */
            lMemoryEntryId = ((lRecordType != DEM_CFG_EREC_TYPE_GLOBAL) ? Dem_MemoryEntry_GetId(lMemoryIndex) : DEM_MEMORYENTRY_HANDLE_INVALID);

# if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON)
            /* Supported record, test if it is currently stored */
            if ( (lRecordType == DEM_CFG_EREC_TYPE_USER)
              && (Dem_ExtendedEntry_IteratorIsExtendedRecordStored(lMemoryEntryId, lExtendedEntryIndex) == FALSE))               /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
            { /* The DTC has an event entry, but the requested record was not yet stored */
              Dem_Data_ResetWriteIndexDestinationBuffer(DestinationBuffer);                                                      /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
              lReturnValue = DEM_NO_SUCH_ELEMENT;
            }
            else
# endif
            {
              if (Dem_Cfg_DidSize(Dem_Cfg_ERecDid(lCfgERecIndex)) > (DestinationBuffer->BufferSize - DestinationBuffer->WriteIndex))
              {
                Dem_Data_ResetWriteIndexDestinationBuffer(DestinationBuffer);                                                    /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
                lReturnValue = DEM_BUFFER_TOO_SMALL;
              }
              else
              {
                Dem_DataReport_DidCopyInfoType lDidCopyInfo;
                Dem_DataReport_InitDidCopyInfo( &lDidCopyInfo, DestinationBuffer, EventId, lMemoryEntryId, NULL_PTR);          /* SBSW_DEM_CALL_DIDCOPYINFO_INIT */
                lReturnValue = Dem_DataReport_CopyExtendedDataRecord(lExtendedEntryIndex, lCfgERecIndex, &lDidCopyInfo);       /* SBSW_DEM_POINTER_LOCAL_DIDCOPYINFO */
              }
            }

            if (lUpdateState != Dem_Event_GetDataCommitState(EventId))
            { /* The event data has been modified while trying to copy the data. */
              /* We cannot be sure it is correct, so start from the beginning */
              Dem_Data_ResetWriteIndexDestinationBuffer(DestinationBuffer);                                                      /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
              lModificationDetected = TRUE; 
            }
          }
          else
          { /* The caller task has higher priority than Dem_MainFunction, but we cannot 'wait' for
            the update to complete. The requested data is not available at this moment. */
            Dem_Data_ResetWriteIndexDestinationBuffer(DestinationBuffer);                                                        /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
            lReturnValue = E_NOT_OK;
          }
        }
        else
        { /* The requested data is currently not stored in the event memory */
          Dem_Data_ResetWriteIndexDestinationBuffer(DestinationBuffer);                                                          /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
          lReturnValue = DEM_NO_SUCH_ELEMENT;
        }
      } while (lModificationDetected == TRUE);
    }
  }
  else
  {
    Dem_Data_ResetWriteIndexDestinationBuffer(DestinationBuffer);                                                                /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    lReturnValue = DEM_NO_SUCH_ELEMENT;
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
#endif /* (DEM_CFG_SUPPORT_ERECS == STD_ON) */



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
 * \addtogroup Dem_EnvDataSwcApi_Public
 * \{
 */

/* ****************************************************************************
 % Dem_EnvDataSwcApi_GetEventFreezeFrameDataEx
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
Dem_EnvDataSwcApi_GetEventFreezeFrameDataEx(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  RecordNumber,
  CONST(uint16, AUTOMATIC)  DataId,
  CONSTP2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)  DestBuffer,                                                                       /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_8.13_fp */
  CONSTP2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  BufSize
  )
{
  Std_ReturnType lReturnValue;
  Dem_Data_DestinationBuffer lDestinationBuffer;

  /* Initialize a Destination Buffer */
  Dem_Data_InitDestinationBuffer(&lDestinationBuffer, DestBuffer, *BufSize);                                                     /* SBSW_DEM_CALL_DESTINATIONBUFFER_INIT */

  lReturnValue = E_NOT_OK;
  *BufSize = 0u;                                                                                                                  /* SBSW_DEM_POINTER_WRITE_ARGUMENT */

  if ((Dem_Cfg_EventAvailableByVariant(EventId) == TRUE)
    && (Dem_EventInternalStatus_TestEventDisconnected(Dem_Event_GetInternalStatus(EventId)) == FALSE))                           
  {
    if (RecordNumber == 0x00u)
    {
      Dem_EventIdType lMemoryRepresentativeEventId;

      lMemoryRepresentativeEventId = Dem_Cfg_GetMemoryRepresentative(EventId);

      if (Dem_Cfg_IsObdIISupportedInVariant() == TRUE)
      {
        lReturnValue = Dem_EnvDataSwcApi_CopyPidFromObdIIFreezeFrame(lMemoryRepresentativeEventId, DataId,                       /* SBSW_DEM_POINTER_LOCAL_DESTINATIONBUFFER */
          &lDestinationBuffer);
      }
      else if (Dem_Cfg_IsWwhObdSupportedInVariant() == TRUE)
      {
        lReturnValue = Dem_EnvDataSwcApi_CopyDidFromWwhObdFreezeFrame(lMemoryRepresentativeEventId, DataId,                      /* SBSW_DEM_POINTER_LOCAL_DESTINATIONBUFFER */
          &lDestinationBuffer);
      }
      else
      {
        lReturnValue = DEM_NO_SUCH_ELEMENT;
      }
    }
#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
# if (DEM_CFG_SUPPORT_TIME_SERIES_POWERTRAIN == STD_OFF)
    else if ((RecordNumber >= 0x10u) && (RecordNumber <= 0x4Fu))
    {
      Dem_EventIdType lMemoryRepresentativeEventId;

      lMemoryRepresentativeEventId = Dem_Cfg_GetMemoryRepresentative(EventId);
      lReturnValue = Dem_EnvDataSwcApi_CopyDidFromTimeSeriesSRec(lMemoryRepresentativeEventId, RecordNumber, DataId,             /* SBSW_DEM_POINTER_LOCAL_DESTINATIONBUFFER */
                                                                 &lDestinationBuffer);     
    }
# else 
    else if (RecordNumber == 0x30u)
    {
      /* E_NOT_OK - SWC readout of time series powertrain snapshot not supported */
    }
# endif
#endif
#if (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON) 
    else if (RecordNumber == Dem_Cfg_GlobalSRecId())
    {
      Dem_EventIdType lMemoryRepresentativeEventId;

      lMemoryRepresentativeEventId = Dem_Cfg_GetMemoryRepresentative(EventId);
      lReturnValue = Dem_EnvDataSwcApi_CopyDidFromGlobalSRec(lMemoryRepresentativeEventId, DataId,                               /* SBSW_DEM_POINTER_LOCAL_DESTINATIONBUFFER */
                                                             &lDestinationBuffer);         
    }
#endif
#if (DEM_CFG_SUPPORT_SRECS == STD_ON)
    else
    {
      Dem_EventIdType lMemoryRepresentativeEventId;

      lMemoryRepresentativeEventId = Dem_Cfg_GetMemoryRepresentative(EventId);
      lReturnValue = Dem_EnvDataSwcApi_CopyDidFromSRec(lMemoryRepresentativeEventId, RecordNumber, DataId,                       /* SBSW_DEM_POINTER_LOCAL_DESTINATIONBUFFER */
                                                       &lDestinationBuffer);               
    }
#else
    else
    {
      /* Requested record number not configured */
      if (RecordNumber != 0xFFu)
      {
        lReturnValue = DEM_NO_SUCH_ELEMENT;
      }
      else
      {
        /*return E_NOT_OK - 0xFF not supported for SRecs not supported */
      }
    }
#endif /* (DEM_CFG_SUPPORT_SRECS == STD_ON) */
  }

  if (lReturnValue == E_OK)
  {
#if ((DEM_CFG_SUPPORT_SRECS == STD_OFF) && (DEM_FEATURE_NEED_TIME_SERIES == STD_OFF))
    if (Dem_Cfg_IsObdSupportedInVariant() == TRUE)
#endif
    {
      *BufSize = lDestinationBuffer.WriteIndex;                                                                                    /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    }
  }

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DataId)                                                                                       /* PRQA S 3112 */ /* MD_DEM_14.2 */

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_EnvDataSwcApi_GetEventExtendedDataRecordEx
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_EnvDataSwcApi_GetEventExtendedDataRecordEx(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  RecordNumber,
  CONSTP2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)  DestBuffer,                                                                       /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_8.13_fp */
  CONSTP2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  BufSize
  )
{
  Std_ReturnType lReturnValue;
  Dem_Data_DestinationBuffer lDestinationBuffer;
  Dem_Data_InitDestinationBuffer(&lDestinationBuffer, DestBuffer, *BufSize);                                                     /* SBSW_DEM_CALL_DESTINATIONBUFFER_INIT */

#if (DEM_CFG_SUPPORT_ERECS == STD_ON)
  if ( (Dem_Cfg_EventAvailableByVariant(EventId) == TRUE)
    && (Dem_EventInternalStatus_TestEventDisconnected(Dem_Event_GetInternalStatus(EventId)) == FALSE) )                          
  {
    /* Find the Record number */
    Dem_EventIdType lMemoryRepresentativeEventId;
    lMemoryRepresentativeEventId = Dem_Cfg_GetMemoryRepresentative(EventId);
    lReturnValue = Dem_EnvDataSwcApi_CopyERecs(lMemoryRepresentativeEventId, RecordNumber, &lDestinationBuffer);                 /* SBSW_DEM_POINTER_LOCAL_DESTINATIONBUFFER */
  }
  else
  {
    Dem_Data_ResetWriteIndexDestinationBuffer(&lDestinationBuffer);                                                              /* SBSW_DEM_POINTER_LOCAL_DESTINATIONBUFFER */
    lReturnValue = E_NOT_OK;
  }

  *BufSize = lDestinationBuffer.WriteIndex;                                                                                      /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
#else /* (DEM_CFG_SUPPORT_ERECS == STD_ON) */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(RecordNumber)                                                                                 /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DestBuffer)                                                                                   /* PRQA S 3112 */ /* MD_DEM_14.2 */
  *BufSize = 0u;                                                                                                                  /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  lReturnValue = E_NOT_OK;
#endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */


/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_ENVDATASWCAPI_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_EnvDataSwcApi_Implementation.h
 *********************************************************************************************************************/
