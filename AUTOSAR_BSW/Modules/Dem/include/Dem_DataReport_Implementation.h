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
 *  \file       Dem_DataReport_Implementation.h
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

#if !defined (DEM_DATAREPORT_IMPLEMENTATION_H)
#define DEM_DATAREPORT_IMPLEMENTATION_H

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
#include "Dem_DataReport_Interface.h"

/* Includes to access public functions belonging to other (top level)/ (logical)/- units to be used by this Unit */
/* ------------------------------------------------------------------------- */
#include "Dem_Infrastructure_Interface.h"
#include "Dem_FaultMemory_Interface.h"
#include "Dem_Client_Interface.h"
#include "Dem_DTCReadoutBuffer_Interface.h"
#include "Dem_IntDataElement_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*! Filename declaration */
#define DEM_DATAREPORT_IMPLEMENTATION_FILENAME "Dem_DataReport_Implementation.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DEFINITIONS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_DataReportIF_Private Private Methods
 * \{
 */


#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) \
   || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_DataReport_FindDataElementKind
 *****************************************************************************/
/*!
 * \brief         Function returns the generic data element kind.
 *
 * \details       Function calculates if the data element corresponding to the 
 *                data index is 'internally calculated' or 'externally 
 *                retrieved' by the DEM and returns this information.
 *
 * \param[in]     DataIndex
 *                Unique handle of the data element
 *
 * \return        DEM_DATAREPORT_DATAELEMENT_INTERNAL
 *                Data element is internally calculated by the DEM.
 * \return        DEM_DATAREPORT_DATAELEMENT_EXTERNAL
 *                Data element is externally retrieved from application.
 * \return        DEM_DATAREPORT_DATAELEMENT_INVALID
 *                Input DataIndex is invalid.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DataReport_FindDataElementKind(
  CONST(Dem_Cfg_DataIndexType, AUTOMATIC)  DataIndex                                                                             
  );
#endif


#if ( (DEM_CFG_SUPPORT_SRECS == STD_ON) \
   || (DEM_CFG_SUPPORT_OBDII == STD_ON) \
   || (DEM_CFG_SUPPORT_WWHOBD == STD_ON) \
   || (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON) \
   || (DEM_FEATURE_NEED_TIME_SERIES == STD_ON) )
/* ****************************************************************************
 * Dem_DataReport_SkipDid
 *****************************************************************************/
/*!
 * \brief         Skip data elements
 *
 * \details       Moves the read (source) pointer in the copy context to skip
 *                the stored data for the given DID. This function has no
 *                effect if the DID does not have persisted data, e.g. if the
 *                DID is composed of statistical values.
 *
 * \param[in,out] DidSourceBufferReadInfoPtr
 *                Information on current source buffer read position.
 * \param[in]     DidIndex
 *                Unique handle of the DID
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_SRECS == STD_ON ||
 *                DEM_CFG_SUPPORT_OBDII == STD_ON ||
 *                DEM_CFG_SUPPORT_WWHOBD == STD_ON ||
 *                DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON ||
 *                DEM_FEATURE_NEED_TIME_SERIES == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DataReport_SkipDid(
  CONST(Dem_DataReport_DidSourceBufferReadInfoPtrType, AUTOMATIC) DidSourceBufferReadInfoPtr,
  CONST(Dem_Cfg_DidIndexType, AUTOMATIC)  DidIndex
  );
#endif


#if (DEM_CFG_SUPPORT_DCM == STD_ON) || (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 * Dem_DataReport_CopyReplacementBytes
 *****************************************************************************/
/*!
 * \brief         Pads the destination buffer with 0xff for unavailable data.
 *
 * \details       Pads the destination buffer with 0xff for unavailable data.
 *
 * \param[in,out] DestinationBuffer
 *                Destination buffer structure
 * \param[in]     DataSize
 *                Number of padding bytes to write
 *
 * \return        TRUE
 *                Always.
 *
 * \pre           Pointer to DestinationBuffer is valid
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *                or (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DataReport_CopyReplacementBytes(
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint16, AUTOMATIC)  DataSize
  );
#endif


#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) \
   || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_DataReport_CopyStoredUserData
 *****************************************************************************/
/*!
 * \brief         Retrieves the user data stored in the event memory entry or
 *                time series entry
 *
 * \details       Retrieves the user data stored in the event memory entry or
 *                time series entry
 *
 * \param[in]     DidCopyInfoPtr
 *                CopyDid context
 * \param[in,out] DidSourceBufferReadInfoPtr
 *                Information on current source buffer read position.
 * \param[in]     DataIndex
 *                Index of requested data element
 *
 * \return        TRUE
 *                Always.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DataReport_CopyStoredUserData(
  CONST(Dem_DataReport_DidCopyInfoBasePtrType, AUTOMATIC)  DidCopyInfoBasePtr,
  CONST(Dem_DataReport_DidSourceBufferReadInfoPtrType, AUTOMATIC) DidSourceBufferReadInfoPtr,
  CONST(Dem_Cfg_DataIndexType, AUTOMATIC)  DataIndex
  );
#endif


#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) \
   || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_DataReport_CopyStoredDataElement
 *****************************************************************************/
/*!
 * \brief         Copies stored data element into a buffer.
 *
 * \details       Copies a stored data element or an internal data element
 *                into the destination buffer.
 *
 * \param[in,out] DidCopyInfoPtr
 *                CopyDid context
 * \param[in,out] DidSourceBufferReadInfoPtr
 *                Information on current source buffer read position.
 * \param[in]     DataIndex
 *                Unique handle of the data element
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           A memory entry has to be locked for Dcm readout
 * \config        DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DataReport_CopyStoredDataElement(
  CONST(Dem_DataReport_DidCopyInfoPtrType, AUTOMATIC)  DidCopyInfoPtr,
  CONST(Dem_DataReport_DidSourceBufferReadInfoPtrType, AUTOMATIC) DidSourceBufferReadInfoPtr ,
  CONST(Dem_Cfg_DataIndexType, AUTOMATIC)  DataIndex
  );
#endif


#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) \
   || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_DataReport_CopyDid
 *****************************************************************************/
/*!
 * \brief         Copies DID data into a buffer.
 *
 * \details       Copies all stored data elements attached to a data identifier
 *                object into the destination buffer, filling in internal data
 *                where needed.
 *                Note that a data identifier in this context is not only a
 *                UDS DID, but can also be an extended data record or PID.
 *
 * \param[in,out] DidCopyInfoPtr
 *                CopyDid context
 * \param[in,out] DidSourceBufferReadInfoPtr
 *                Information on current source buffer read position.
 * \param[in]     DidIndex
 *                Unique handle of the DID
 *
 * \return        TRUE
 *                All data was copied (can be 0 bytes dependent on config)
 * \return        FALSE
 *                Not all data was copied
 *
 * \pre           A memory entry has to be locked for Dcm readout
 * \config        DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON  ||
 *                DEM_FEATURE_NEED_OBD == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_DataReport_CopyDid(
  CONST(Dem_DataReport_DidCopyInfoPtrType, AUTOMATIC)  DidCopyInfoPtr,
  CONST(Dem_DataReport_DidSourceBufferReadInfoPtrType, AUTOMATIC) DidSourceBufferReadInfoPtr,
  CONST(Dem_Cfg_DidIndexType, AUTOMATIC)  DidIndex
  );
#endif


#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 * Dem_DataReport_CopyDid_NoInternalData
 *****************************************************************************/
/*!
 * \brief         Copies DID data into a buffer.
 *
 * \details       Copies all stored data elements attached to a data identifier
 *                object into the destination buffer, padding internal data
 *                elements with 0xff.
 *
 * \param[in]     DidCopyInfoBasePtr
 *                Basic CopyDid context
 * \param[in,out] DidSourceBufferReadInfoPtr
 *                Information on current source buffer read position.
 * \param[in]     DidIndex
 *                Unique handle of the DID
 *
 * \return        TRUE
 *                All data was copied (can be 0 bytes dependent on config)
 * \return        FALSE
 *                Not all data was copied
 *
 * \pre           A memory entry has to be locked for Dcm readout
 * \config        DEM_FEATURE_NEED_TIME_SERIES == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_DataReport_CopyDid_NoInternalData(
  CONST(Dem_DataReport_DidCopyInfoBasePtrType, AUTOMATIC)  DidCopyInfoBasePtr,
  CONST(Dem_DataReport_DidSourceBufferReadInfoPtrType, AUTOMATIC) DidSourceBufferReadInfoPtr,
  CONST(Dem_Cfg_DidIndexType, AUTOMATIC)  DidIndex
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DataReport_WriteTimeSeriesPowertrainData
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
 * \param[in,out] DidCount
 *                Counter of writen DIDs
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
Dem_DataReport_WriteTimeSeriesPowertrainData(
  Dem_DTCReadoutBuffer_HandleType  ReadoutBufferId,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONSTP2VAR(uint16, AUTOMATIC, AUTOMATIC) DidCount
);
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DataReport_GetTimeSeriesPowertrainSequentialInfo
 *****************************************************************************/
/*!
 * \brief         Copies sequential DID into a buffer.
 *
 * \details       Copies a sequential DID into the provided buffer. In case 
 *                required number of samples are not present, padding is also
 *                done.
 *
 * \param[in]     SourceEntry
 *                Pointer to the time series entry
 * \param[in]     EventId
 *                Unique handle of the Event
 * \param[out]    TimeSeriesInfo
 *                Pointer to struct containing meta information about the TimeSeries SRec
 *
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
Dem_DataReport_GetTimeSeriesPowertrainSequentialInfo(
  Dem_Mem_ConstTimeSeriesEntryPtrType SourceEntry,
  Dem_EventIdType EventId,
  CONSTP2VAR(Dem_DataReport_PowertrainTimeSeriesInfoType, AUTOMATIC,AUTOMATIC) TimeSeriesInfo
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DataReport_WriteTimeSeriesPowertrainSequentialHeader
 *****************************************************************************/
/*!
 * \brief         Writes sequential DID header into a buffer.
 *
 * \details       Writes sequential DID header into a buffer.
 *
 * \param[in,out] DestinationBuffer
 *                Destination buffer structure
 * \param[in]     SourceEntry
 *                Pointer to the time series entry
 * \param[in]     TimeSeriesInfo
 *                Pointer to struct containing meta information about the TimeSeries SRec
 *
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
Dem_DataReport_WriteTimeSeriesPowertrainSequentialHeader(
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationHeaderBuffer,
  Dem_Mem_ConstTimeSeriesEntryPtrType SourceEntry,
  CONSTP2CONST(Dem_DataReport_PowertrainTimeSeriesInfoType, AUTOMATIC, AUTOMATIC) TimeSeriesInfo
);
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DataReport_WriteTimeSeriesPowertrainSequentialDid
 *****************************************************************************/
/*!
 * \brief         Writes sequential DID into a buffer.
 *
 * \details       Writes a sequential DID into the provided buffer. In case 
 *                required number of samples are not present, padding is also
 *                done.
 *
 * \param[in,out] DestinationBuffer
 *                Destination buffer structure
 * \param[in]     SourceEntry
 *                Pointer to the time series entry
 * \param[in]     TimeSeriesInfo
 *                Pointer to struct containing meta information about the TimeSeries SRec
 * \param[in]     DidIndex
 *                Unique handle of the DID
 * \param[in]     lSourceBufferIndex
 *                Index of the DID inside the source buffer
 *
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
Dem_DataReport_WriteTimeSeriesPowertrainSequentialDid(
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  Dem_Mem_ConstTimeSeriesEntryPtrType SourceEntry,
  CONSTP2CONST(Dem_DataReport_PowertrainTimeSeriesInfoType, AUTOMATIC, AUTOMATIC) TimeSeriesInfo,
  Dem_Cfg_DidIndexType DidIndex,
  uint16 SourceBufferIndex
  );
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) \
   || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_DataReport_InitDidSourceBufferReadInfo
 *****************************************************************************/
/*!
 * \brief         Initializes the passed DidSourceBufferReadInfo context.
 *
 * \details       Initializes the passed DidSourceBufferReadInfo context.
 *
 * \param[in,out] DidSourceBufferReadInfoPtr
 *                Pointer to DidSourceBufferReadInfo context
 * \param[in]     SourceBuffer
 *                Pointer to source buffer
 *
 * \pre           Pointer to DidSourceBufferReadInfo is valid and passed 
 *                SourceBuffer is valid
 * \config        DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON  ||
 *                DEM_FEATURE_NEED_OBD == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DataReport_InitDidSourceBufferReadInfo(
  CONST(Dem_DataReport_DidSourceBufferReadInfoPtrType, AUTOMATIC)  DidSourceBufferReadInfoPtr,
  CONST(Dem_ConstSharedDataPtrType, AUTOMATIC)  SourceBuffer
  );
#endif

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) \
   || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 % Dem_DataReport_FindDataElementKind
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DataReport_FindDataElementKind(
  CONST(Dem_Cfg_DataIndexType, AUTOMATIC)  DataIndex                                                                            
  )
{
  uint8 lDataElementKind;
  uint8 lDataCallbackType;
  
  lDataCallbackType = Dem_Cfg_DataCallbackType(DataIndex);
  switch (lDataCallbackType)
  {
  case DEM_CFG_DATA_FROM_AGINGCTR:
  case DEM_CFG_DATA_FROM_OCCCTR:
  case DEM_CFG_DATA_FROM_OCCCTR_2BYTE:
  case DEM_CFG_DATA_FROM_OVFLIND:
  case DEM_CFG_DATA_FROM_SIGNIFICANCE:
  case DEM_CFG_DATA_FROM_PRIORITY:
  case DEM_CFG_DATA_FROM_AGINGCTR_INVERTED:
  case DEM_CFG_DATA_FROM_MAX_FDC_SINCE_LAST_CLEAR:
  case DEM_CFG_DATA_FROM_MAX_FDC_DURING_CURRENT_CYCLE:
  case DEM_CFG_DATA_FROM_CYCLES_SINCE_LAST_FAILED:
  case DEM_CFG_DATA_FROM_CYCLES_SINCE_FIRST_FAILED:
  case DEM_CFG_DATA_FROM_FAILED_CYCLES:
  case DEM_CFG_DATA_FROM_CONSECUTIVE_FAILED_CYCLES:
  case DEM_CFG_DATA_FROM_FAULT_PENDING_COUNTER:
  case DEM_CFG_DATA_FROM_CYCLES_TESTED_SINCE_FIRST_FAILED:
  case DEM_CFG_DATA_FROM_CYCLES_TESTED_SINCE_LAST_FAILED:
  case DEM_CFG_DATA_FROM_HEALINGCTR_DOWNCNT:
  case DEM_CFG_DATA_FROM_ROOTCAUSE_EVENTID:
  case DEM_CFG_DATA_FROM_OBDDTC:
  case DEM_CFG_DATA_FROM_OBDDTC_3BYTE:
  case DEM_CFG_DATA_FROM_OBD_RATIO:
  case DEM_CFG_DATA_FROM_CYCLES_SINCE_LAST_UNCONFIRMED:
  case DEM_CFG_DATA_FROM_CYCLES_PASSED_SINCE_LAST_UNCONFIRMED:
  case DEM_CFG_DATA_FROM_CYCLES_SINCE_FIRST_UNCONFIRMED:
  case DEM_CFG_DATA_FROM_UNCONFIRMED_CYCLES:
  case DEM_CFG_DATA_FROM_CYCLES_PASSED_OR_UNCONFIRMED_SINCE_FIRST_UNCONFIRMED:
  case DEM_CFG_DATA_FROM_CURRENT_FDC:
  case DEM_CFG_DATA_FROM_AGED_COUNTER:
  case DEM_CFG_DATA_FROM_DTC_STATUS_INDICATOR:
  case DEM_CFG_DATA_FROM_STANDARD_ENV_DATA:
  case DEM_CFG_DATA_FROM_EXTENDED_ENV_DATA:
  case DEM_CFG_DATA_FROM_WUC_SINCE_LAST_FAILED:
  case DEM_CFG_DATA_FROM_SI30_STATUS:
    lDataElementKind = DEM_DATAREPORT_DATAELEMENT_INTERNAL;
    break;
  
  case DEM_CFG_DATA_FROM_CBK:
  case DEM_CFG_DATA_FROM_CBK_WITH_EVENTID:
  case DEM_CFG_DATA_FROM_SR_PORT_BOOLEAN:
  case DEM_CFG_DATA_FROM_SR_PORT_SINT8:
  case DEM_CFG_DATA_FROM_SR_PORT_UINT8:
  case DEM_CFG_DATA_FROM_SR_PORT_SINT16:
  case DEM_CFG_DATA_FROM_SR_PORT_SINT16_INTEL:
  case DEM_CFG_DATA_FROM_SR_PORT_UINT16:
  case DEM_CFG_DATA_FROM_SR_PORT_UINT16_INTEL:
  case DEM_CFG_DATA_FROM_SR_PORT_SINT32:
  case DEM_CFG_DATA_FROM_SR_PORT_SINT32_INTEL:
  case DEM_CFG_DATA_FROM_SR_PORT_UINT32:
  case DEM_CFG_DATA_FROM_SR_PORT_UINT32_INTEL:
  case DEM_CFG_DATA_FROM_SR_PORT_SINT8_N:
  case DEM_CFG_DATA_FROM_SR_PORT_UINT8_N:
    lDataElementKind = DEM_DATAREPORT_DATAELEMENT_EXTERNAL;
    break;

  default: 
    lDataElementKind = DEM_DATAREPORT_DATAELEMENT_INVALID;
    break;
  }

  return lDataElementKind;
}
#endif

#if ( (DEM_CFG_SUPPORT_SRECS == STD_ON) \
   || (DEM_CFG_SUPPORT_OBDII == STD_ON) \
   || (DEM_CFG_SUPPORT_WWHOBD == STD_ON) \
   || (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON) \
   || (DEM_FEATURE_NEED_TIME_SERIES == STD_ON) )
/* ****************************************************************************
 % Dem_DataReport_SkipDid
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DataReport_SkipDid(
  CONST(Dem_DataReport_DidSourceBufferReadInfoPtrType, AUTOMATIC) DidSourceBufferReadInfoPtr,
  CONST(Dem_Cfg_DidIndexType, AUTOMATIC)  DidIndex
  )
{
  Dem_Cfg_DidDataIterType lDataIter;

  /* Iterate all data elements in the DID */
  for (Dem_Cfg_DidDataIterInit(DidIndex, &lDataIter);                                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_DidDataIterExists(&lDataIter) == TRUE;                                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_DidDataIterNext(&lDataIter))                                                                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_DataIndexType lDataIndex;
    lDataIndex = Dem_Cfg_DidDataIterGet(&lDataIter);                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */

    if (Dem_Cfg_DataIsStoredInNV(lDataIndex) == TRUE)
    {
      switch (Dem_Cfg_DataCallbackType(lDataIndex))
      {
      case DEM_CFG_DATA_FROM_ROOTCAUSE_EVENTID:
      case DEM_CFG_DATA_FROM_CBK:
      case DEM_CFG_DATA_FROM_CBK_WITH_EVENTID:
      case DEM_CFG_DATA_FROM_SR_PORT_BOOLEAN:
      case DEM_CFG_DATA_FROM_SR_PORT_SINT8:
      case DEM_CFG_DATA_FROM_SR_PORT_UINT8:
      case DEM_CFG_DATA_FROM_SR_PORT_SINT16:
      case DEM_CFG_DATA_FROM_SR_PORT_SINT16_INTEL:
      case DEM_CFG_DATA_FROM_SR_PORT_UINT16:
      case DEM_CFG_DATA_FROM_SR_PORT_UINT16_INTEL:
      case DEM_CFG_DATA_FROM_SR_PORT_SINT32:
      case DEM_CFG_DATA_FROM_SR_PORT_SINT32_INTEL:
      case DEM_CFG_DATA_FROM_SR_PORT_UINT32:
      case DEM_CFG_DATA_FROM_SR_PORT_UINT32_INTEL:
      case DEM_CFG_DATA_FROM_SR_PORT_SINT8_N:
      case DEM_CFG_DATA_FROM_SR_PORT_UINT8_N:
            DidSourceBufferReadInfoPtr->ReadIndex += Dem_Cfg_DataSize(lDataIndex);                                               /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
        break;

      default:                                                                                                                   /* PRQA S 2016 */ /* MD_MSR_EmptyClause */
        /* Do nothing */
        break;
      }
    }
  }
}
#endif /* (DEM_CFG_SUPPORT_SRECS == STD_ON) || (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)|| (DEM_CFG_SUPPORT_OBDII == STD_ON) || (DEM_CFG_SUPPORT_WWHOBD == STD_ON) || (DEM_FEATURE_NEED_TIME_SERIES == STD_ON) */

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON) || (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_DataReport_CopyReplacementBytes
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DataReport_CopyReplacementBytes(
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint16, AUTOMATIC)  DataSize
  )
{
  uint16 lWriteIndex = DestinationBuffer->WriteIndex;
  if (Dem_Data_IncrementWriteIndexDestinationBuffer(DestinationBuffer, DataSize) == E_OK)                                        /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  {
    Dem_MemSet(&DestinationBuffer->Buffer[lWriteIndex],                                                                          /* PRQA S 0602 */ /* MD_DEM_20.2 */ /* SBSW_DEM_MEMSET_DESTINATIONBUFFER */
                DEM_DATAREPORT_INVALID_DATA_PATTERN,
                DataSize);
  }
  return TRUE;
}
#endif


/* ------------------------------------------------------------------------- */
#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) \
   || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 % Dem_DataReport_CopyStoredUserData
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DataReport_CopyStoredUserData(
  CONST(Dem_DataReport_DidCopyInfoBasePtrType, AUTOMATIC)  DidCopyInfoBasePtr,                                               /* PRQA S 3673 */ /* MD_DEM_8.13_fp */
  CONST(Dem_DataReport_DidSourceBufferReadInfoPtrType, AUTOMATIC) DidSourceBufferReadInfoPtr,
  CONST(Dem_Cfg_DataIndexType, AUTOMATIC)  DataIndex
  )
{
  uint8 lDataSize;
  Dem_Internal_AssertReturnValue(DidSourceBufferReadInfoPtr->SourceBuffer !=
                                 NULL_PTR, DEM_E_INCONSISTENT_STATE, FALSE)
  lDataSize = Dem_Cfg_DataSize(DataIndex);
  
  Dem_Data_WriteDestinationBuffer(DidCopyInfoBasePtr->DestinationBuffer,                                                        /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
                                 &DidSourceBufferReadInfoPtr->SourceBuffer[DidSourceBufferReadInfoPtr->ReadIndex],               /* PRQA S 2821 */ /* MD_DEM_Dir4.1_ReadOperation */
                                  lDataSize);

  DidSourceBufferReadInfoPtr->ReadIndex += lDataSize;                                                                            /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  return TRUE;
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) \
   || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 % Dem_DataReport_CopyStoredDataElement
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DataReport_CopyStoredDataElement(
  CONST(Dem_DataReport_DidCopyInfoPtrType, AUTOMATIC)  DidCopyInfoPtr,
  CONST(Dem_DataReport_DidSourceBufferReadInfoPtrType, AUTOMATIC) DidSourceBufferReadInfoPtr ,
  CONST(Dem_Cfg_DataIndexType, AUTOMATIC)  DataIndex
  )
{
  boolean lReturnValue;
  uint8 lDataElementKind;

  lDataElementKind = Dem_DataReport_FindDataElementKind(DataIndex);
  if (lDataElementKind == DEM_DATAREPORT_DATAELEMENT_INTERNAL)
  {
    lReturnValue = Dem_IntDataElement_CopyInternalDataElement(DidCopyInfoPtr, DidSourceBufferReadInfoPtr, DataIndex);          /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }
  else
  if (lDataElementKind == DEM_DATAREPORT_DATAELEMENT_EXTERNAL)
  {
    lReturnValue = Dem_DataReport_CopyStoredUserData(&(DidCopyInfoPtr->Base), DidSourceBufferReadInfoPtr, DataIndex);          /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }
  else
  {
    lReturnValue = FALSE;
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6030, 6050 */ /* MD_MSR_STCYC, MD_MSR_STCAL */
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) \
   || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 % Dem_DataReport_CopyDid
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
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_DataReport_CopyDid(
  CONST(Dem_DataReport_DidCopyInfoPtrType, AUTOMATIC)  DidCopyInfoPtr,
  CONST(Dem_DataReport_DidSourceBufferReadInfoPtrType, AUTOMATIC) DidSourceBufferReadInfoPtr ,
  CONST(Dem_Cfg_DidIndexType, AUTOMATIC)  DidIndex
  )
{
  boolean lReturnValue;
  Dem_Cfg_DidDataIterType lDataIter;

  lReturnValue = TRUE;
  for (Dem_Cfg_DidDataIterInit(DidIndex, &lDataIter);                                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_Cfg_DidDataIterExists(&lDataIter) == TRUE;                                                                               /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_Cfg_DidDataIterNext(&lDataIter))                                                                                         /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_DataIndexType lDataIndex;
    lDataIndex = Dem_Cfg_DidDataIterGet(&lDataIter);                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */

    if (Dem_Cfg_DataIsStoredInNV(lDataIndex) == TRUE)
    {
      lReturnValue = Dem_DataReport_CopyStoredDataElement(DidCopyInfoPtr, DidSourceBufferReadInfoPtr, lDataIndex) && lReturnValue;                         /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    }
    else
    {
      lReturnValue = Dem_ExtDataElement_CollectDataElement(&(DidCopyInfoPtr->Base), lDataIndex) && lReturnValue;                        /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    }
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6030, 6050 */ /* MD_MSR_STCYC, MD_MSR_STCAL */
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 % Dem_DataReport_CopyDid_NoInternalData
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
 */
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_DataReport_CopyDid_NoInternalData(
  CONST(Dem_DataReport_DidCopyInfoBasePtrType, AUTOMATIC)  DidCopyInfoBasePtr,
  CONST(Dem_DataReport_DidSourceBufferReadInfoPtrType, AUTOMATIC) DidSourceBufferReadInfoPtr ,
  CONST(Dem_Cfg_DidIndexType, AUTOMATIC)  DidIndex
  )
{
  boolean lReturnValue;
  Dem_Cfg_DidDataIterType lDataIter;

  lReturnValue = TRUE;

  for (Dem_Cfg_DidDataIterInit(DidIndex, &lDataIter);                                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_Cfg_DidDataIterExists(&lDataIter) == TRUE;                                                                               /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_Cfg_DidDataIterNext(&lDataIter))                                                                                         /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_DataIndexType lDataIndex;
    lDataIndex = Dem_Cfg_DidDataIterGet(&lDataIter);                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */

    if (Dem_Cfg_DataIsStoredInNV(lDataIndex) == TRUE)
    {
      switch (Dem_Cfg_DataCallbackType(lDataIndex))
      {
      case DEM_CFG_DATA_FROM_CBK:
      case DEM_CFG_DATA_FROM_CBK_WITH_EVENTID:
      case DEM_CFG_DATA_FROM_SR_PORT_BOOLEAN:
      case DEM_CFG_DATA_FROM_SR_PORT_SINT8:
      case DEM_CFG_DATA_FROM_SR_PORT_UINT8:
      case DEM_CFG_DATA_FROM_SR_PORT_SINT16:
      case DEM_CFG_DATA_FROM_SR_PORT_SINT16_INTEL:
      case DEM_CFG_DATA_FROM_SR_PORT_UINT16:
      case DEM_CFG_DATA_FROM_SR_PORT_UINT16_INTEL:
      case DEM_CFG_DATA_FROM_SR_PORT_SINT32:
      case DEM_CFG_DATA_FROM_SR_PORT_SINT32_INTEL:
      case DEM_CFG_DATA_FROM_SR_PORT_UINT32:
      case DEM_CFG_DATA_FROM_SR_PORT_UINT32_INTEL:
      case DEM_CFG_DATA_FROM_SR_PORT_SINT8_N:
      case DEM_CFG_DATA_FROM_SR_PORT_UINT8_N:
        if (Dem_DataReport_CopyStoredUserData(DidCopyInfoBasePtr, DidSourceBufferReadInfoPtr, lDataIndex) == FALSE)           /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
        {
          lReturnValue = FALSE;                
        }
        break;

      default:
        if (Dem_DataReport_CopyReplacementBytes(DidCopyInfoBasePtr->DestinationBuffer, Dem_Cfg_DataSize(lDataIndex)) == FALSE)/* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
        {
          lReturnValue = FALSE;
        }
        break;
      }
    }
    else
    {
      if (Dem_ExtDataElement_CollectDataElement(DidCopyInfoBasePtr, lDataIndex) == FALSE)                                     /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
      {
        lReturnValue = FALSE;
      }
    }
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6060 */ /* MD_MSR_STCAL, MD_MSR_STPAR */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_DataReport_WriteTimeSeriesPowertrainData
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
Dem_DataReport_WriteTimeSeriesPowertrainData(
  Dem_DTCReadoutBuffer_HandleType  ReadoutBufferId,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONSTP2VAR(uint16, AUTOMATIC, AUTOMATIC) DidCount
)
{
  /* Sequential Did Iteration Data */
  Dem_Cfg_EventDidIterType lDidIter;
  Dem_Mem_ConstTimeSeriesEntryPtrType lTimeSeriesEntryPtr;
  uint16 lDidSourceBufferIndex;
  
  /* Sequential DID Header Data */
  Dem_Data_DestinationBuffer lSourceHeaderBuffer;
  uint8 lHeaderBuffer[DEM_DATAREPORT_TIMESERIES_SEQUENTIALDID_HEADERSIZE];

  /* Sequential DID Meta Data*/
  Dem_EventIdType lEventId;
  Dem_DataReport_PowertrainTimeSeriesInfoType lTimeSeriesInfo;
  Dem_Cfg_TimeSeriesEntryType lDummyTimeSeriesEntry = { 0 };

  lDidSourceBufferIndex = 0x00u;

  /* Get the event id from the time series memory entry */
  lTimeSeriesEntryPtr = &lDummyTimeSeriesEntry;
  lEventId = Dem_DTCReadoutBuffer_GetEventId(ReadoutBufferId, DEM_DTCREADOUTBUFFER_DATAINDEX_DEFAULT);
#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON) && (DEM_CFG_SUPPORT_TIME_SERIES_POWERTRAIN == STD_ON)
  lTimeSeriesEntryPtr = Dem_Memory_TimeSeries_GetEntrySafe(Dem_DTCReadoutBuffer_GetTimeSeriesEntryIndex(ReadoutBufferId));
#endif

  /* Get meta information about the time series record */
  Dem_DataReport_GetTimeSeriesPowertrainSequentialInfo(lTimeSeriesEntryPtr, lEventId, &lTimeSeriesInfo);                     /* SBSW_DEM_POINTER_FORWARD_STACK */

  /* Initialize DestinationBuffer Context for the source header buffer */
  Dem_Data_InitDestinationBuffer(&lSourceHeaderBuffer, lHeaderBuffer, DEM_DATAREPORT_TIMESERIES_SEQUENTIALDID_HEADERSIZE);  /* SBSW_DEM_CALL_DESTINATIONBUFFER_INIT */

  /* Fill source header buffer */
  Dem_DataReport_WriteTimeSeriesPowertrainSequentialHeader(&lSourceHeaderBuffer,                                             /* SBSW_DEM_POINTER_FORWARD_STACK */
    lTimeSeriesEntryPtr, &lTimeSeriesInfo);

  for (Dem_Memory_TimeSeries_EntryManager_EventDidIterInit(lEventId, &lDidIter);                                               /* SBSW_DEM_CALL_ITERATOR_POINTER */
        Dem_Memory_TimeSeries_EntryManager_EventDidIterExists(&lDidIter) == TRUE;                                              /* PRQA S 2994 */ /* MD_DEM_2994 */ /* SBSW_DEM_CALL_ITERATOR_POINTER */
        Dem_Memory_TimeSeries_EntryManager_EventDidIterNext(&lDidIter))                                                        /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_DidIndexType lDidIndex;
    uint8 lDidSize;
  
    lDidIndex = Dem_Memory_TimeSeries_EntryManager_EventDidIterGet(&lDidIter);                                                 /* SBSW_DEM_CALL_ITERATOR_POINTER */
    lDidSize  = Dem_DataStorage_GetDidNVSize(lDidIndex);

    Dem_Data_WriteDestinationBuffer(DestinationBuffer, lSourceHeaderBuffer.Buffer, lSourceHeaderBuffer.BufferSize);            /* SBSW_DEM_POINTER_FORWARD_STACK */

    Dem_DataReport_WriteTimeSeriesPowertrainSequentialDid(DestinationBuffer,                                                 /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
      lTimeSeriesEntryPtr, &lTimeSeriesInfo, lDidIndex, lDidSourceBufferIndex);
    *DidCount = *DidCount + 1u;                                                                                                /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    lDidSourceBufferIndex += lDidSize;
  }
  
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_DataReport_GetTimeSeriesPowertrainSequentialInfo
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
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DataReport_GetTimeSeriesPowertrainSequentialInfo(
  Dem_Mem_ConstTimeSeriesEntryPtrType SourceEntry,
  Dem_EventIdType EventId,
  CONSTP2VAR(Dem_DataReport_PowertrainTimeSeriesInfoType, AUTOMATIC,AUTOMATIC) TimeSeriesInfo
  )
{
  if (Dem_Memory_TimeSeries_TestEventSupportNormal(EventId))
  {
    TimeSeriesInfo->NumberOfConfiguredSamples = Dem_Cfg_TimeSeriesPastSamplesNormal();                                           /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    TimeSeriesInfo->NumberOfNotStoredSamples  = Dem_Memory_TimeSeries_EntryManager_GetUnusedPastSamplesNormal(SourceEntry);      /* SBSW_DEM_POINTER_WRITE_ARGUMENT */ /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */

    /* Disable requirement to support float when time series powertrain is disabled */
#  if (DEM_CFG_SUPPORT_TIME_SERIES_POWERTRAIN == STD_ON)
    TimeSeriesInfo->SamplingRate = Dem_Memory_TimeSeries_EntryManager_RoundFloatToUint16((float32)Dem_Cfg_TimeSeriesNormalRate() * Dem_Cfg_DemTaskTime());   /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
#  else
    TimeSeriesInfo->SamplingRate = 0x00u;                                                                                        /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
#  endif
  }
  else 
  {
    TimeSeriesInfo->NumberOfConfiguredSamples = Dem_Cfg_TimeSeriesPastSamplesFast();                                             /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    TimeSeriesInfo->NumberOfNotStoredSamples  = Dem_Memory_TimeSeries_EntryManager_GetUnusedPastSamplesFast(SourceEntry);        /* SBSW_DEM_POINTER_WRITE_ARGUMENT */ /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */

    /* Disable requirement to support float when time series powertrain is disabled */
#  if (DEM_CFG_SUPPORT_TIME_SERIES_POWERTRAIN == STD_ON)
    TimeSeriesInfo->SamplingRate = Dem_Memory_TimeSeries_EntryManager_RoundFloatToUint16((float32)Dem_Cfg_TimeSeriesFastRate() * Dem_Cfg_DemTaskTime()); /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
#  else
    TimeSeriesInfo->SamplingRate = 0x00u;                                                                                        /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
#  endif
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif


#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_DataReport_WriteTimeSeriesPowertrainSequentialHeader
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DataReport_WriteTimeSeriesPowertrainSequentialHeader(
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationHeaderBuffer,
  Dem_Mem_ConstTimeSeriesEntryPtrType SourceEntry,
  CONSTP2CONST(Dem_DataReport_PowertrainTimeSeriesInfoType, AUTOMATIC, AUTOMATIC) TimeSeriesInfo
)
{
  Dem_Data_WriteDestinationBufferUint16(DestinationHeaderBuffer, (uint16)DEM_DATAREPORT_TIMESERIES_ENTRYMANAGER_MAGICNUMBER);           /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  Dem_Data_WriteDestinationBufferUint8 (DestinationHeaderBuffer, TimeSeriesInfo->NumberOfConfiguredSamples);                               /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  Dem_Data_WriteDestinationBufferUint16(DestinationHeaderBuffer, TimeSeriesInfo->SamplingRate);                                            /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  Dem_Data_WriteDestinationBufferUint16(DestinationHeaderBuffer, Dem_Memory_TimeSeries_EntryManager_GetTimeSinceLastSample(SourceEntry));  /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */ /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_DataReport_WriteTimeSeriesPowertrainSequentialDid
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DataReport_WriteTimeSeriesPowertrainSequentialDid(
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  Dem_Mem_ConstTimeSeriesEntryPtrType SourceEntry,
  CONSTP2CONST(Dem_DataReport_PowertrainTimeSeriesInfoType, AUTOMATIC, AUTOMATIC) TimeSeriesInfo,
  Dem_Cfg_DidIndexType DidIndex,
  uint16 SourceBufferIndex
)
{
  uint8 lSampleIndex;
  uint8 lDidSize;
  uint16 lDidIdentifier;

  lDidSize = Dem_DataStorage_GetDidNVSize(DidIndex);
  lDidIdentifier = Dem_Cfg_DidNumber(DidIndex);

  for (lSampleIndex = 0x00u; lSampleIndex < TimeSeriesInfo->NumberOfConfiguredSamples; lSampleIndex++)                           /* PRQA S 2994 */ /* MD_DEM_2994 */
  {
    Dem_Data_WriteDestinationBufferUint16(DestinationBuffer, lDidIdentifier);                                                    /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    if (lSampleIndex < TimeSeriesInfo->NumberOfNotStoredSamples)
    {
      (void)Dem_DataReport_CopyReplacementBytes(DestinationBuffer, lDidSize);                                                  /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    }
    else
    {
      Dem_ConstSharedDataPtrType lSourceBuffer;
      lSourceBuffer = Dem_Memory_TimeSeries_EntryManager_GetConstDataPtr(SourceEntry, lSampleIndex);                             /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
      Dem_Data_WriteDestinationBuffer(DestinationBuffer, &lSourceBuffer[SourceBufferIndex], lDidSize);                           /* PRQA S 2821 */ /* MD_DEM_Dir4.1_NullPointerDereference */ /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    }
  }
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) \
   || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 % Dem_DataReport_InitDidSourceBufferReadInfo
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DataReport_InitDidSourceBufferReadInfo(
  CONST(Dem_DataReport_DidSourceBufferReadInfoPtrType, AUTOMATIC)  DidSourceBufferReadInfoPtr,
  CONST(Dem_ConstSharedDataPtrType, AUTOMATIC)  SourceBuffer
  )
{
  DidSourceBufferReadInfoPtr->SourceBuffer = SourceBuffer;                                                                       /* SBSW_DEM_CALL_DIDSOURCEBUFFERREADINFO_INIT */
  DidSourceBufferReadInfoPtr->ReadIndex    = 0u;                                                                                 /* SBSW_DEM_CALL_DIDSOURCEBUFFERREADINFO_INIT */
}
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
 * \addtogroup Dem_DataReportIF_Public
 * \{
 */


/* ****************************************************************************
 % Dem_DataReport_InitDidCopyInfo
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DataReport_InitDidCopyInfo(
  CONST(Dem_DataReport_DidCopyInfoPtrType, AUTOMATIC)  DidCopyInfoPtr,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(Dem_Cfg_ReadoutMemIndeCounterPtrType, AUTOMATIC) MemIndeCounterPtr
  )
{
  DidCopyInfoPtr->Base.DestinationBuffer = DestinationBuffer;                                                                    /* SBSW_DEM_CALL_DIDCOPYINFO_INIT */
  DidCopyInfoPtr->Base.EventId = EventId;                                                                                        /* SBSW_DEM_CALL_DIDCOPYINFO_INIT */
  DidCopyInfoPtr->MemoryEntryId = MemoryEntryId;                                                                                 /* SBSW_DEM_CALL_DIDCOPYINFO_INIT */
#if (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_OFF)
  DidCopyInfoPtr->MemIndeCounterPtr = MemIndeCounterPtr;                                                                         /* SBSW_DEM_CALL_DIDCOPYINFO_INIT */
#else
  DidCopyInfoPtr->MemIndeCounterPtr = NULL_PTR;                                                                                  /* SBSW_DEM_CALL_DIDCOPYINFO_INIT */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemIndeCounterPtr)                                                                            /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif

}


#if (DEM_CFG_SUPPORT_DCM == STD_ON) && ((DEM_CFG_SUPPORT_SRECS == STD_ON) || (DEM_FEATURE_NEED_TIME_SERIES == STD_ON))
/* ****************************************************************************
 % Dem_DataReport_SRecCopyData
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
Dem_DataReport_SRecCopyData(
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(Dem_ConstSharedDataPtrType, AUTOMATIC)  SourceBuffer,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(Dem_Cfg_ReadoutMemIndeCounterPtrType, AUTOMATIC) MemIndeCounterPtr
)
{
  uint16 lWriteIndex;

  /* Reserve one byte for Did count */
  lWriteIndex = DestinationBuffer->WriteIndex;
  if (Dem_Data_IncrementWriteIndexDestinationBuffer(DestinationBuffer, 1) == E_OK)                                               /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  {
    uint16 lDidCount;
    Dem_Cfg_EventDidIterType lDidIter;
    Dem_DataReport_DidCopyInfoType lDidCopyInfo;
    Dem_DataReport_DidSourceBufferReadInfoType lDidSourceBufferReadInfo;

    /* Initialize a CopyDid Context. */
    Dem_DataReport_InitDidCopyInfo(&lDidCopyInfo, DestinationBuffer, EventId , MemoryEntryId, MemIndeCounterPtr);              /* SBSW_DEM_CALL_DIDCOPYINFO_INIT */
    Dem_DataReport_InitDidSourceBufferReadInfo(&lDidSourceBufferReadInfo, SourceBuffer);                                       /* SBSW_DEM_CALL_DIDSOURCEBUFFERREADINFO_INIT */
    
    /* Initialize number of DIDs */
    lDidCount = 0u;
    for (Dem_Cfg_EventDidIterInit(EventId, &lDidIter);                                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
      Dem_Cfg_EventDidIterExists(&lDidIter) == TRUE;                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
      Dem_Cfg_EventDidIterNext(&lDidIter))                                                                                       /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {

      Dem_Cfg_DidIndexType lDidIndex;
      lDidIndex = Dem_Cfg_EventDidIterGet(&lDidIter);                                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */

      ++lDidCount;

      Dem_Data_WriteDestinationBufferUint16(lDidCopyInfo.Base.DestinationBuffer, Dem_Cfg_DidNumber(lDidIndex));                  /* SBSW_DEM_POINTER_LOCAL_COPYDID_DESTINATIONBUFFER */
# if (DEM_FEATURE_NEED_DID_LENGTH_FOR_SVC19_04 == STD_ON)
      Dem_Data_WriteDestinationBufferUint8(lDidCopyInfo.Base.DestinationBuffer, Dem_GetLoByte(Dem_Cfg_DidSize(lDidIndex)));      /* SBSW_DEM_POINTER_LOCAL_COPYDID_DESTINATIONBUFFER */
# endif

# if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
      /* if event has no primary entry no internal data can be copied */
      if (lDidCopyInfo.Base.EventId == DEM_EVENT_INVALID)
      {
        (void)Dem_DataReport_CopyDid_NoInternalData(&(lDidCopyInfo.Base), &lDidSourceBufferReadInfo, lDidIndex);               /* SBSW_DEM_POINTER_LOCAL_DIDCOPYINFO */
      }
      else
# endif
      {
        (void)Dem_DataReport_CopyDid(&lDidCopyInfo, &lDidSourceBufferReadInfo, lDidIndex);                                     /* SBSW_DEM_POINTER_LOCAL_DIDCOPYINFO */
      }
    }

    /* Set the DID count to 0 in case of more than 255 DIDs. */
    if (lDidCount > 255u)
    {
      lDidCount = 0u;
    }
    /* first byte contains record number */
    Dem_Data_WriteDestinationBufferAtIndex(lDidCopyInfo.Base.DestinationBuffer, lWriteIndex, Dem_GetLoByte(lDidCount));          /* SBSW_DEM_POINTER_LOCAL_COPYDID_DESTINATIONBUFFER */
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif /* (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_SRECS == STD_ON) */

#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
/* ****************************************************************************
 % Dem_DataReport_GlobalSnapshotCopyData
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
Dem_DataReport_GlobalSnapshotCopyData(
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(Dem_ConstSharedDataPtrType, AUTOMATIC)  SourceBuffer,
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(Dem_Cfg_ReadoutMemIndeCounterPtrType, AUTOMATIC) MemIndeCounterPtr
  )
{
  if (DestinationBuffer->BufferSize > DestinationBuffer->WriteIndex)
  {
    uint16 lDidCount;
    uint16 lWriteIndex;
    Dem_Cfg_EventObdDidIterType lDidIter;
    Dem_DataReport_DidCopyInfoType lDidCopyInfo;
    Dem_DataReport_DidSourceBufferReadInfoType lDidSourceBufferReadInfo;
    Dem_EventIdType lEventId;

    /* Initialize a CopyDid Context. Reserve one byte at the start for the DID count. */
    lWriteIndex = DestinationBuffer->WriteIndex;
    lEventId = Dem_MemoryEntry_GetEventId(MemoryEntryId);
    (void)Dem_Data_IncrementWriteIndexDestinationBuffer(DestinationBuffer, 1);                                                   /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    Dem_DataReport_InitDidCopyInfo(&lDidCopyInfo, DestinationBuffer, lEventId, MemoryEntryId, MemIndeCounterPtr);              /* SBSW_DEM_CALL_DIDCOPYINFO_INIT */
    Dem_DataReport_InitDidSourceBufferReadInfo(&lDidSourceBufferReadInfo, SourceBuffer);                                       /* SBSW_DEM_CALL_DIDSOURCEBUFFERREADINFO_INIT */

    lDidCount = 0u;
     
    for (Dem_Cfg_GlobalSnapshotDidIterInit(&lDidIter);                                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Cfg_GlobalSnapshotDidIterExists(&lDidIter) == TRUE;                                                                 /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Cfg_GlobalSnapshotDidIterNext(&lDidIter))                                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      Dem_Cfg_DidIndexType lDidIndex;
      lDidIndex = Dem_Cfg_GlobalSnapshotDidIterGet(&lDidIter);                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */

      ++lDidCount;

      Dem_Data_WriteDestinationBufferUint16(lDidCopyInfo.Base.DestinationBuffer, Dem_Cfg_DidNumber(lDidIndex));                  /* SBSW_DEM_POINTER_LOCAL_COPYDID_DESTINATIONBUFFER */
# if (DEM_FEATURE_NEED_DID_LENGTH_FOR_SVC19_04 == STD_ON)
      Dem_Data_WriteDestinationBufferUint8(lDidCopyInfo.Base.DestinationBuffer, Dem_GetLoByte(Dem_Cfg_DidSize(lDidIndex)));      /* SBSW_DEM_POINTER_LOCAL_COPYDID_DESTINATIONBUFFER */
# endif
      (void)Dem_DataReport_CopyDid(&lDidCopyInfo, &lDidSourceBufferReadInfo, lDidIndex);                                       /* SBSW_DEM_POINTER_LOCAL_DIDCOPYINFO */
    }

    /* Set the DID count to 0 in case of more than 255 DIDs. */
    if (lDidCount > 255u)
    {
      lDidCount = 0u;
    }
    Dem_Data_WriteDestinationBufferAtIndex(lDidCopyInfo.Base.DestinationBuffer, lWriteIndex, Dem_GetLoByte(lDidCount));          /* SBSW_DEM_POINTER_LOCAL_COPYDID_DESTINATIONBUFFER */
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_DataReport_TimeSeriesPowertrainCopyData
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
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DataReport_TimeSeriesPowertrainCopyData(
  Dem_DTCReadoutBuffer_HandleType  ReadoutBufferId,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  )
{
  uint16 lDidCount;
  uint16 lDidCountWriteIndex;

  /* Initialize a CopyDid Context. Reserve one byte at the start for the DID count. */
  lDidCount = 0x00u;
  lDidCountWriteIndex = DestinationBuffer->WriteIndex;
  (void)Dem_Data_IncrementWriteIndexDestinationBuffer(DestinationBuffer, 1);                                                     /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */

  /* Copy powertrain time series data */
  Dem_DataReport_WriteTimeSeriesPowertrainData(ReadoutBufferId, DestinationBuffer, &lDidCount);                                /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */ /* SBSW_DEM_POINTER_FORWARD_STACK */ 

  /* Set the DID count to 255 in case of more than 255 DIDs. */
  if (lDidCount > 255u)
  {
    lDidCount = 255u;
  }

  Dem_Data_WriteDestinationBufferAtIndex(DestinationBuffer, lDidCountWriteIndex, Dem_GetLoByte(lDidCount));                      /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
}                                                                                                                                
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 % Dem_DataReport_WWHOBDFreezeFrameCopyData
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
Dem_DataReport_WWHOBDFreezeFrameCopyData(
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(Dem_ConstSharedDataPtrType, AUTOMATIC)  SourceBuffer,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(Dem_Cfg_ReadoutMemIndeCounterPtrType, AUTOMATIC) MemIndeCounterPtr
  )
{
  if (DestinationBuffer->BufferSize > DestinationBuffer->WriteIndex)
  {
    uint16 lDidCount;
    uint16 lWriteIndex;
    Dem_Cfg_EventObdDidIterType lDidIter;
    Dem_DataReport_DidCopyInfoType lDidCopyInfo;
    Dem_DataReport_DidSourceBufferReadInfoType lDidSourceBufferReadInfo;

    /* Initialize a CopyDid Context. Reserve one byte at the start for the DID count. */
    lWriteIndex = DestinationBuffer->WriteIndex;
    (void)Dem_Data_IncrementWriteIndexDestinationBuffer(DestinationBuffer, 1);                                                   /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    Dem_DataReport_InitDidCopyInfo(&lDidCopyInfo, DestinationBuffer, EventId, MemoryEntryId, MemIndeCounterPtr);               /* SBSW_DEM_CALL_DIDCOPYINFO_INIT */
    Dem_DataReport_InitDidSourceBufferReadInfo(&lDidSourceBufferReadInfo, SourceBuffer);                                       /* SBSW_DEM_CALL_DIDSOURCEBUFFERREADINFO_INIT */

    lDidCount = 0u;
     
    for (Dem_Cfg_EventObdDidIterInit(EventId, &lDidIter);                                                                        /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Cfg_EventObdDidIterExists(&lDidIter) == TRUE;                                                                       /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Cfg_EventObdDidIterNext(&lDidIter))                                                                                 /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      Dem_Cfg_DidIndexType lDidIndex;
      lDidIndex = Dem_Cfg_EventObdDidIterGet(&lDidIter);                                                                         /* SBSW_DEM_CALL_ITERATOR_POINTER */

      ++lDidCount;

      Dem_Data_WriteDestinationBufferUint16(lDidCopyInfo.Base.DestinationBuffer, Dem_Cfg_DidNumber(lDidIndex));                  /* SBSW_DEM_POINTER_LOCAL_COPYDID_DESTINATIONBUFFER */
# if (DEM_FEATURE_NEED_DID_LENGTH_FOR_SVC19_04 == STD_ON)
      Dem_Data_WriteDestinationBufferUint8(lDidCopyInfo.Base.DestinationBuffer, Dem_GetLoByte(Dem_Cfg_DidSize(lDidIndex)));      /* SBSW_DEM_POINTER_LOCAL_COPYDID_DESTINATIONBUFFER */
# endif
      (void)Dem_DataReport_CopyDid(&lDidCopyInfo, &lDidSourceBufferReadInfo, lDidIndex);                                       /* SBSW_DEM_POINTER_LOCAL_DIDCOPYINFO */
    }

    /* Set the DID count to 0 in case of more than 255 DIDs. */
    if (lDidCount > 255u)
    {
      lDidCount = 0u;
    }
    Dem_Data_WriteDestinationBufferAtIndex(lDidCopyInfo.Base.DestinationBuffer, lWriteIndex, Dem_GetLoByte(lDidCount));          /* SBSW_DEM_POINTER_LOCAL_COPYDID_DESTINATIONBUFFER */
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_DataReport_ObdIIFreezeFrameCopyPidData
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
Dem_DataReport_ObdIIFreezeFrameCopyPidData(
  CONST(uint8, AUTOMATIC)  FreezeFrameIndex,
  CONST(uint8, AUTOMATIC)  Pid,
  CONST(uint8, AUTOMATIC)  DataElementIndex,
  CONSTP2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  Buffer,
  CONSTP2VAR(uint16, AUTOMATIC, DEM_DCM_DATA)  BufSize
  )
{
  uint16_least              lSrcBufferOffset;
  Dem_Cfg_GlobalPidIterType lPidIter;
  Std_ReturnType            lReturnValue;

  lSrcBufferOffset = 0u;
  lReturnValue     = E_NOT_OK;

  for (Dem_Cfg_GlobalPidIterInit(&lPidIter);                                                                                     /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_GlobalPidIterExists(&lPidIter) == TRUE;                                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_GlobalPidIterNext(&lPidIter))                                                                                     /* SBSW_DEM_CALL_ITERATOR_POINTER */
  { /* look for the requested PID */
    Dem_Cfg_DidIndexType lDidIndex;
    lDidIndex = Dem_Cfg_GlobalPidIterGet(&lPidIter);                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */

    /* Check for the requested PID -> the PID value stored in the configuration is from type uint16 with a
       leading 0xF4 which is only used from UDS services */
    if (Pid == Dem_GetLoByte(Dem_Cfg_DidNumber(lDidIndex)))
    {
      /* This is the requested PID, now find the requested data element */
      Dem_Cfg_DidDataIterType lDataIter;
      uint8 lDataElementIndex;

      /* Each DID consists of 1-* data elements. */
      lDataElementIndex = 0u;
      for (Dem_Cfg_DidDataIterInit(lDidIndex, &lDataIter);                                                                       /* SBSW_DEM_CALL_ITERATOR_POINTER */
           Dem_Cfg_DidDataIterExists(&lDataIter) == TRUE;                                                                        /* SBSW_DEM_CALL_ITERATOR_POINTER */
           Dem_Cfg_DidDataIterNext(&lDataIter))                                                                                  /* SBSW_DEM_CALL_ITERATOR_POINTER */
      { /* look for the requested data element of the PID */
        Dem_Cfg_DataIndexType lDataIndex;
        uint16 lElementSize;

        lDataIndex = Dem_Cfg_DidDataIterGet(&lDataIter);                                                                         /* SBSW_DEM_CALL_ITERATOR_POINTER */
        lElementSize = Dem_Cfg_DataSize(lDataIndex);
        if (DataElementIndex == lDataElementIndex)
        {
          /* This is the requested element index, check if data fits into the provided buffer */
          if (lElementSize <= *BufSize)
          {
            Dem_ConstSharedDataPtrType lObdFreezeFrameDataPtr;

            lObdFreezeFrameDataPtr = Dem_Mem_FreezeFrameObdIIGetDataPtr(FreezeFrameIndex);

            Dem_MemCpy(Buffer, &lObdFreezeFrameDataPtr[lSrcBufferOffset], lElementSize);                                         /* PRQA S 0311, 0602 */ /* MD_DEM_11.8, MD_DEM_20.2 */ /* SBSW_DEM_POINTER_WRITE_ARGUMENT_BUFFER */
            *BufSize = lElementSize;                                                                                             /* SBSW_DEM_POINTER_WRITE_ARGUMENT */

            lReturnValue = E_OK;
          }
          /* data element of PID identified, leave loop */
          break;
        }
        ++lDataElementIndex;
        lSrcBufferOffset = (uint16_least)(lSrcBufferOffset + lElementSize);
      }
      /* PID identified, leave loop */
      break;
    }
    lSrcBufferOffset = (uint16_least)(lSrcBufferOffset + Dem_Cfg_DidSize(lDidIndex));
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif /* (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_OBDII == STD_ON) */


#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_DataReport_ObdIIFreezeFrameCopyUdsData
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
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DataReport_ObdIIFreezeFrameCopyUdsData(
  CONST(Dem_DataReport_BufferIndexType, AUTOMATIC)  BufferIdx,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint8, AUTOMATIC)  Source
  )
{
  if ((DestinationBuffer->BufferSize - DestinationBuffer->WriteIndex) > 0u)
  {
    uint16 lDidCount;
    uint16 lWriteIndex;
    Dem_Cfg_GlobalPidIterType lPidIter;
    Dem_DataReport_DidCopyInfoType  lDidCopyInfo;
    Dem_DataReport_DidSourceBufferReadInfoType lDidSourceBufferReadInfo;
    Dem_ConstSharedDataPtrType lPtrToSource;

    DEM_IGNORE_UNUSED_CONST_ARGUMENT(Source)                                                                                     /* PRQA S 3112 */ /* MD_DEM_14.2 */
# if(DEM_CFG_SUPPORT_OBDII_FREEZEFRAME_IN_SVC19 == STD_ON)
    if (Source == DEM_DATAREPORT_SOURCE_OBDII_FF_READOUTBUFFER)
    {
      lPtrToSource = (Dem_ConstSharedDataPtrType)Dem_DTCReadoutBuffer_GetPtrToOBDFreezeFrameBuffer(BufferIdx.ReadoutBufferId);
    }
    else
# endif
    {
      lPtrToSource = (Dem_ConstSharedDataPtrType)Dem_Mem_FreezeFrameObdIIGetDataPtr(BufferIdx.FreezeFrameIndex);
    }
    /* Initialize a CopyDid Context. Reserve one byte at the start for the DID count. */
    lWriteIndex = DestinationBuffer->WriteIndex;
    (void) Dem_Data_IncrementWriteIndexDestinationBuffer(DestinationBuffer, 1);                                                  /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    Dem_DataReport_InitDidCopyInfo(&lDidCopyInfo                                                                               /* SBSW_DEM_CALL_DIDCOPYINFO_INIT */
                                   , DestinationBuffer
                                   , DEM_EVENT_INVALID
                                   , DEM_MEMORYENTRY_HANDLE_INVALID
                                   , NULL_PTR);
    Dem_DataReport_InitDidSourceBufferReadInfo(&lDidSourceBufferReadInfo, lPtrToSource);                                       /* SBSW_DEM_CALL_DIDSOURCEBUFFERREADINFO_INIT */

    /* initialize PID counter */
    lDidCount = 0u;

    for (Dem_Cfg_GlobalPidIterInit(&lPidIter);                                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Cfg_GlobalPidIterExists(&lPidIter) == TRUE;                                                                         /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Cfg_GlobalPidIterNext(&lPidIter))                                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      Dem_Cfg_DidIndexType lDidIndex;
      lDidIndex = Dem_Cfg_GlobalPidIterGet(&lPidIter);                                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */

      /* Count the PIDs */
      ++lDidCount;

        /* Store the UDS DID number 0xF4 <PID> into the destination buffer */
      Dem_Data_WriteDestinationBufferUint8(lDidCopyInfo.Base.DestinationBuffer, 0xf4U);                                          /* SBSW_DEM_POINTER_LOCAL_COPYDID_DESTINATIONBUFFER */
      Dem_Data_WriteDestinationBufferUint8(lDidCopyInfo.Base.DestinationBuffer, Dem_GetLoByte(Dem_Cfg_DidNumber(lDidIndex)));    /* SBSW_DEM_POINTER_LOCAL_COPYDID_DESTINATIONBUFFER */
# if (DEM_FEATURE_NEED_DID_LENGTH_FOR_SVC19_04 == STD_ON)
        /* If configurared also store the PID length into the destination buffer */
      Dem_Data_WriteDestinationBufferUint8(lDidCopyInfo.Base.DestinationBuffer, Dem_GetLoByte(Dem_Cfg_DidSize(lDidIndex)));      /* SBSW_DEM_POINTER_LOCAL_COPYDID_DESTINATIONBUFFER */
# endif

      /* Copy the PID data into the destination buffer */
      (void)Dem_DataReport_CopyDid(&lDidCopyInfo, &lDidSourceBufferReadInfo, lDidIndex);                                       /* SBSW_DEM_POINTER_LOCAL_DIDCOPYINFO */

    }
    /* Store the number of PIDs to the first byte of the destination buffer.
     * Set the DID count to 0 in case of more than 255 DIDs. */
    if (lDidCount > 255u)
    {
      lDidCount = 0u;
    }
    Dem_Data_WriteDestinationBufferAtIndex(lDidCopyInfo.Base.DestinationBuffer, lWriteIndex, Dem_GetLoByte(lDidCount));          /* SBSW_DEM_POINTER_LOCAL_COPYDID_DESTINATIONBUFFER */
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif /* (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_OBDII == STD_ON) */

/* ****************************************************************************
 % Dem_DataReport_CopyExtendedDataRecord
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_DataReport_CopyExtendedDataRecord(                                                                                         /* PRQA S 3219 */ /* MD_DEM_14.1_CONFIGURATION_SWITCH */
  CONST(uint8, AUTOMATIC) ExtendedEntryIndex,
  CONST(Dem_Cfg_ERecIndexType, AUTOMATIC) CfgERecIndex,
  CONST(Dem_DataReport_DidCopyInfoPtrType, AUTOMATIC)  DidCopyInfoPtr                                                          /* PRQA S 3673 */ /* MD_DEM_8.13_fp */
)
{
  Std_ReturnType lReturnValue;
#if (DEM_CFG_SUPPORT_ERECS == STD_ON)
  Dem_DataReport_DidSourceBufferReadInfoType lDidSourceBufferReadInfo;
  Dem_ConstSharedDataPtrType lSourceBuffer;

# if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON)  
  uint8 lERecType;
  lERecType = Dem_Cfg_ERecType(CfgERecIndex);
# endif

  lReturnValue = E_OK;

# if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON)
  if (lERecType == DEM_CFG_EREC_TYPE_USER)
  {
    lSourceBuffer = Dem_ExtendedEntry_IteratorGetExtendedRecordDataConstPtr(DidCopyInfoPtr->MemoryEntryId, ExtendedEntryIndex);
  }
  else /*lERecType == DEM_CFG_EREC_TYPE_GLOBAL or lERecType == DEM_CFG_EREC_TYPE_INTERNAL*/
# endif
  {
    lSourceBuffer = (Dem_ConstSharedDataPtrType)NULL_PTR;
  }

  Dem_DataReport_InitDidSourceBufferReadInfo(&lDidSourceBufferReadInfo, lSourceBuffer);                                        /* SBSW_DEM_CALL_DIDSOURCEBUFFERREADINFO_INIT */

  if (Dem_DataReport_CopyDid(DidCopyInfoPtr, &lDidSourceBufferReadInfo, Dem_Cfg_ERecDid(CfgERecIndex)) == FALSE)               /* SBSW_DEM_POINTER_LOCAL_DIDCOPYINFO */
  {
    lReturnValue = DEM_NO_SUCH_ELEMENT;
    Dem_Data_ResetWriteIndexDestinationBuffer(DidCopyInfoPtr->Base.DestinationBuffer);                                           /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(CfgERecIndex)                                                                                 /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DidCopyInfoPtr)                                                                               /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = DEM_NO_SUCH_ELEMENT;
#endif
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(ExtendedEntryIndex)                                                                           /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 % Dem_DataReport_CopyDidFromWwhObdFreezeFrame
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
Dem_DataReport_CopyDidFromWwhObdFreezeFrame(
  CONST(uint16, AUTOMATIC)  DataId,
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC) MemoryEntry,
  CONST(Dem_ConstSharedDataPtrType, AUTOMATIC)  SourceBuffer,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  )
{
  Std_ReturnType lReturnValue;
  Dem_Cfg_EventObdDidIterType   lDidIter;
  Dem_DataReport_DidCopyInfoType lDidCopyInfo;
  Dem_DataReport_DidSourceBufferReadInfoType lDidSourceBufferReadInfo;
  Dem_EventIdType lEventId;

  /* Initialize a CopyDid Context. */
  lEventId = Dem_MemoryEntry_GetEventId(MemoryEntry);
  Dem_DataReport_InitDidCopyInfo(&lDidCopyInfo                                                                                 /* SBSW_DEM_CALL_DIDCOPYINFO_INIT */
                                 , DestinationBuffer
                                 , lEventId
                                 , MemoryEntry
                                 , NULL_PTR);
  Dem_DataReport_InitDidSourceBufferReadInfo(&lDidSourceBufferReadInfo, SourceBuffer);                                         /* SBSW_DEM_CALL_DIDSOURCEBUFFERREADINFO_INIT */

  lReturnValue = DEM_NO_SUCH_ELEMENT;

  for (Dem_Cfg_EventObdDidIterInit(lEventId, &lDidIter);                                                                         /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_Cfg_EventObdDidIterExists(&lDidIter) == TRUE;                                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_Cfg_EventObdDidIterNext(&lDidIter))                                                                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_DidIndexType lDidIndex;
    lDidIndex = Dem_Cfg_EventObdDidIterGet(&lDidIter);                                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */

    if (Dem_Cfg_DidNumber(lDidIndex) == DataId)
    {
      if (Dem_Cfg_DidSize(lDidIndex) <= lDidCopyInfo.Base.DestinationBuffer->BufferSize)
      {
        (void)Dem_DataReport_CopyDid(&lDidCopyInfo, &lDidSourceBufferReadInfo, lDidIndex);                                     /* SBSW_DEM_POINTER_LOCAL_DIDCOPYINFO */
        lReturnValue = E_OK;
      }
      else
      {
        lReturnValue = DEM_BUFFER_TOO_SMALL;
      }
      break;
    }
    else
    { /* not the requested DID */
      Dem_DataReport_SkipDid(&lDidSourceBufferReadInfo, lDidIndex);                                                            /* SBSW_DEM_POINTER_LOCAL_DIDCOPYINFO */
    }
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6030, 6050, 6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
#endif

#if ((DEM_FEATURE_NEED_TIME_SERIES == STD_ON) && (DEM_CFG_SUPPORT_POWERTRAIN == STD_OFF))
/* ****************************************************************************
 % Dem_DataReport_CopyDidTimeSeriesSRec
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
Dem_DataReport_CopyDidTimeSeriesSRec(
  CONST(uint16, AUTOMATIC)  DataId,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_ConstSharedDataPtrType, AUTOMATIC)  SourceBuffer,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  )
{
  Std_ReturnType lReturnValue;
  Dem_Cfg_EventDidIterType lDidIter;
  Dem_DataReport_DidCopyInfoType lDidCopyInfo;
  Dem_DataReport_DidSourceBufferReadInfoType lDidSourceBufferReadInfo;
  Dem_Cfg_MemoryEntryHandleType lMemoryEntryId;
  Dem_EventIdType lEventId;

  if (MemoryIndex == DEM_MEM_INVALID_MEMORY_INDEX)
  {
    lMemoryEntryId = DEM_MEMORYENTRY_HANDLE_INVALID;
    lEventId = DEM_EVENT_INVALID;
  }
  else
  {
    lMemoryEntryId = Dem_MemoryEntry_GetId(MemoryIndex);
    lEventId = EventId;
  }

  /* Initialize a CopyDid Context. */
  Dem_DataReport_InitDidCopyInfo(&lDidCopyInfo                                                                                 /* SBSW_DEM_CALL_DIDCOPYINFO_INIT */
                                 , DestinationBuffer
                                 , lEventId
                                 , lMemoryEntryId
                                 , NULL_PTR);
  Dem_DataReport_InitDidSourceBufferReadInfo(&lDidSourceBufferReadInfo, SourceBuffer);                                         /* SBSW_DEM_CALL_DIDSOURCEBUFFERREADINFO_INIT */

  lReturnValue = DEM_NO_SUCH_ELEMENT;

  for (Dem_Cfg_EventDidIterInit(EventId, &lDidIter);                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_EventDidIterExists(&lDidIter) == TRUE;                                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_EventDidIterNext(&lDidIter))                                                                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_DidIndexType lDidIndex;
    lDidIndex = Dem_Cfg_EventDidIterGet(&lDidIter);                                                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */

    if (Dem_Cfg_DidNumber(lDidIndex) == DataId)
    {
      uint16 DataSize;
      DataSize = Dem_Cfg_DidSize(lDidIndex);
      if (DataSize <= lDidCopyInfo.Base.DestinationBuffer->BufferSize)
      {
        if (lDidCopyInfo.Base.EventId == DEM_EVENT_INVALID)
        {
          (void)Dem_DataReport_CopyDid_NoInternalData(&(lDidCopyInfo.Base), &lDidSourceBufferReadInfo, lDidIndex);             /* SBSW_DEM_POINTER_LOCAL_DIDCOPYINFO */
        }
        else
        {
          (void)Dem_DataReport_CopyDid(&lDidCopyInfo, &lDidSourceBufferReadInfo, lDidIndex);                                   /* SBSW_DEM_POINTER_LOCAL_DIDCOPYINFO */
        }

        lReturnValue = E_OK;
      }
      else
      {
        lReturnValue = DEM_BUFFER_TOO_SMALL;
      }
      break;
    }
    else
    { /* not the requested DID */
      Dem_DataReport_SkipDid(&lDidSourceBufferReadInfo, lDidIndex);                                                            /* SBSW_DEM_POINTER_LOCAL_DIDCOPYINFO */
    }
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
#endif

#if (DEM_CFG_SUPPORT_SRECS == STD_ON)
/* ****************************************************************************
 % Dem_DataReport_CopyDidSRec
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
Dem_DataReport_CopyDidSRec(
  CONST(uint16, AUTOMATIC)  DataId,
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntry,
  CONST(Dem_ConstSharedDataPtrType, AUTOMATIC)  SourceBuffer,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  )
{
  Std_ReturnType lReturnValue;

  Dem_Cfg_EventDidIterType lDidIter;
  Dem_DataReport_DidCopyInfoType lDidCopyInfo;
  Dem_DataReport_DidSourceBufferReadInfoType lDidSourceBufferReadInfo;

  /* Initialize a CopyDid Context */
  Dem_DataReport_InitDidCopyInfo(&lDidCopyInfo                                                                                 /* SBSW_DEM_CALL_DIDCOPYINFO_INIT */
                                 , DestinationBuffer
                                 , Dem_MemoryEntry_GetEventId(MemoryEntry)
                                 , MemoryEntry
                                 , NULL_PTR);
  Dem_DataReport_InitDidSourceBufferReadInfo(&lDidSourceBufferReadInfo, SourceBuffer);                                         /* SBSW_DEM_CALL_DIDSOURCEBUFFERREADINFO_INIT */

  lReturnValue = DEM_NO_SUCH_ELEMENT;

  for (Dem_Cfg_EventDidIterInit(lDidCopyInfo.Base.EventId, &lDidIter);                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_EventDidIterExists(&lDidIter) == TRUE;                                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_EventDidIterNext(&lDidIter))                                                                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_DidIndexType lDidIndex;
    lDidIndex = Dem_Cfg_EventDidIterGet(&lDidIter);                                                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */

    if (Dem_Cfg_DidNumber(lDidIndex) == DataId)
    {
      uint16 DataSize;
      DataSize = Dem_Cfg_DidSize(lDidIndex);
      if (DataSize <= lDidCopyInfo.Base.DestinationBuffer->BufferSize)
      {
        (void)Dem_DataReport_CopyDid(&lDidCopyInfo, &lDidSourceBufferReadInfo, lDidIndex);                                     /* SBSW_DEM_POINTER_LOCAL_DIDCOPYINFO */
        lReturnValue = E_OK;
      }
      else
      {
        lReturnValue = DEM_BUFFER_TOO_SMALL;
      }
      break;
    }
    else
    { /* not the requested DID */
      Dem_DataReport_SkipDid(&lDidSourceBufferReadInfo, lDidIndex);                                                            /* SBSW_DEM_POINTER_LOCAL_DIDCOPYINFO */
    }
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
#endif /* (DEM_CFG_SUPPORT_SRECS == STD_ON) */

#if (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
/* ****************************************************************************
 % Dem_DataReport_CopyDidGlobalSRec
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
Dem_DataReport_CopyDidGlobalSRec(
  CONST(uint16, AUTOMATIC)  DataId,
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntry,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  )
{
  Std_ReturnType lReturnValue;

  Dem_Cfg_EventDidIterType lDidIter;
  Dem_DataReport_DidCopyInfoType lDidCopyInfo;
  Dem_DataReport_DidSourceBufferReadInfoType lDidSourceBufferReadInfo;

  /* Initialize a CopyDid Context */
  Dem_DataReport_InitDidCopyInfo(&lDidCopyInfo                                                                                 /* SBSW_DEM_CALL_DIDCOPYINFO_INIT */
                                 , DestinationBuffer
                                 , Dem_MemoryEntry_GetEventId(MemoryEntry)
                                 , MemoryEntry
                                 , NULL_PTR);
  Dem_DataReport_InitDidSourceBufferReadInfo(&lDidSourceBufferReadInfo,                                                        /* SBSW_DEM_CALL_DIDSOURCEBUFFERREADINFO_INIT */
                                               Dem_MemoryEntry_GetGlobalSnapshotRecordDataPtr(MemoryEntry));

  lReturnValue = DEM_NO_SUCH_ELEMENT;

  for (Dem_Cfg_GlobalSnapshotDidIterInit(&lDidIter);                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_GlobalSnapshotDidIterExists(&lDidIter) == TRUE;                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_GlobalSnapshotDidIterNext(&lDidIter))                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_DidIndexType lDidIndex;
    lDidIndex = Dem_Cfg_GlobalSnapshotDidIterGet(&lDidIter);                                                                     /* SBSW_DEM_CALL_ITERATOR_POINTER */

    if (Dem_Cfg_DidNumber(lDidIndex) == DataId)
    {
      uint16 DataSize;
      DataSize = Dem_Cfg_DidSize(lDidIndex);
      if (DataSize <= lDidCopyInfo.Base.DestinationBuffer->BufferSize)
      {
        (void)Dem_DataReport_CopyDid(&lDidCopyInfo, &lDidSourceBufferReadInfo, lDidIndex);                                     /* SBSW_DEM_POINTER_LOCAL_DIDCOPYINFO */
        lReturnValue = E_OK;
      }
      else
      {
        lReturnValue = DEM_BUFFER_TOO_SMALL;
      }
      break;
    }
    else
    { /* not the requested DID */
      Dem_DataReport_SkipDid(&lDidSourceBufferReadInfo, lDidIndex);                                                            /* SBSW_DEM_POINTER_LOCAL_DIDCOPYINFO */
    }
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
#endif /* (DEM_CFG_SUPPORT_SRECS == STD_ON) */

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_DataReport_CopyPidFromObdIIFreezeFrame
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
Dem_DataReport_CopyPidFromObdIIFreezeFrame(
  CONST(uint16, AUTOMATIC)  DataId,
  CONST(Dem_ConstSharedDataPtrType, AUTOMATIC)  SourceBuffer,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  )
{
  Std_ReturnType lReturnValue;
  Dem_Cfg_GlobalPidIterType  lPidIter;
  Dem_DataReport_DidCopyInfoType lDidCopyInfo;
  Dem_DataReport_DidSourceBufferReadInfoType lDidSourceBufferReadInfo;

  lReturnValue = DEM_NO_SUCH_ELEMENT;

  /* Initialize a CopyDid Context */
  Dem_DataReport_InitDidCopyInfo(&lDidCopyInfo                                                                                 /* SBSW_DEM_CALL_DIDCOPYINFO_INIT */
                                , DestinationBuffer
                                , DEM_EVENT_INVALID
                                , DEM_MEMORYENTRY_HANDLE_INVALID
                                , NULL_PTR);
  Dem_DataReport_InitDidSourceBufferReadInfo(&lDidSourceBufferReadInfo, SourceBuffer);                                         /* SBSW_DEM_CALL_DIDSOURCEBUFFERREADINFO_INIT */

  for (Dem_Cfg_GlobalPidIterInit(&lPidIter);                                                                                     /* SBSW_DEM_CALL_ITERATOR_POINTER */
        Dem_Cfg_GlobalPidIterExists(&lPidIter) == TRUE;                                                                          /* SBSW_DEM_CALL_ITERATOR_POINTER */
        Dem_Cfg_GlobalPidIterNext(&lPidIter))                                                                                    /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_DidIndexType lDidIndex;
    lDidIndex = Dem_Cfg_GlobalPidIterGet(&lPidIter);                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */

    if (Dem_GetLoByte(Dem_Cfg_DidNumber(lDidIndex)) == Dem_GetLoByte(DataId))
    {
      uint16 DataSize;
      DataSize = Dem_Cfg_DidSize(lDidIndex);
      if (DataSize <= lDidCopyInfo.Base.DestinationBuffer->BufferSize)
      {
        (void)Dem_DataReport_CopyDid(&lDidCopyInfo, &lDidSourceBufferReadInfo, lDidIndex);                                     /* SBSW_DEM_POINTER_LOCAL_DIDCOPYINFO */
        lReturnValue = E_OK;
      }
      else
      {
        lReturnValue = DEM_BUFFER_TOO_SMALL;
      }
      break;
    }
    else
    { /* not the requested DID */
      Dem_DataReport_SkipDid(&lDidSourceBufferReadInfo, lDidIndex);                                                            /* SBSW_DEM_POINTER_LOCAL_DIDCOPYINFO */
    }
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif /* (DEM_CFG_SUPPORT_OBDII == STD_ON) */



/* ------------------------------------------------------------------------- */
/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_DATAREPORT_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_DataReport_Implementation.h
 *********************************************************************************************************************/
