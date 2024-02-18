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
/*! \ingroup    Dem_API
 *  \defgroup   Dem_EnvDataSwcApi EnvDataSwcApi
 *  \{
 *  \file       Dem_EnvDataSwcApi_Interface.h
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

#if !defined (DEM_ENVDATASWCAPI_INTERFACE_H)
#define DEM_ENVDATASWCAPI_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_EnvDataSwcApi_Types.h"
/* ------------------------------------------------------------------------- */

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_EnvDataSwcApi_Public Public Methods
 * \{
 */

/* ****************************************************************************
 * Dem_EnvDataSwcApi_GetEventFreezeFrameDataEx
 *****************************************************************************/
/*!
 * \brief         Implementation of SWC API Dem_GetEventFreezeFrameDataEx().
 *
 * \details       This API is intended to be called via RTE_CALL interface,
 *                as Operation of port interface 'DiagnosticInfo'.
 *
 *                Dem_GetEventFreezeFrameDataEx() copies data from the stored
 *                snapshot data of an event into DestBuffer, following no
 *                particular format and contains no header-information like
 *                RecordNumber or DataId.
 *
 *                Only the DID data actually stored in the event storage is
 *                returned here. If the Dcm adds additional parts to a DID,
 *                these will be missing.
 *
 *                The record number 0xff is a magic value used to read the most
 *                recently stored record. This is only supported in case record
 *                numbers are calculated (DemTypeOfFreezeFrameRecordNumeration).
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 * \param[in]     RecordNumber
 *                SnapshotRecord number to read. Contrary to usual usage, 0xFF
 *                returns the most recently stored record. (See notes.)
 * \param[in]     DataId
 *                Return only the data of this DID.
 * \param[out]    DestBuffer
 *                Buffer to receive the data.
 * \param[in,out] BufSize
 *                In: Size of the buffer.
 *                Out: Number of bytes written.
 *
 * \return        E_OK
 *                The requested data was copied to the destination buffer.
 * \return        DEM_NO_SUCH_ELEMENT
 *                The data is currently not stored for the requested event.
 *                or
 *                the requested RecordNumber is not supported for the given
 *                event
 *                or
 *                the requested data identifier is not supported within the
 *                requested record (freeze frame).
 * \return        E_NOT_OK
 *                The request was rejected, e.g. due to variant coding (see
 *                Dem_SetEventAvailable() )
 *                or
 *                the requested data is currently not accessible (e.g. in case
 *                of asynchronous preempted data retrieval from application).
 * \return        DEM_BUFFER_TOO_SMALL
 *                The provided buffer is too small.
 *
 * \pre           RTE is active (if RTE is used).
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_EnvDataSwcApi_GetEventFreezeFrameDataEx(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  RecordNumber,
  CONST(uint16, AUTOMATIC)  DataId,
  CONSTP2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)  DestBuffer,
  CONSTP2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  BufSize
  );

/* ****************************************************************************
 * Dem_EnvDataSwcApi_GetEventExtendedDataRecordEx
 *****************************************************************************/
/*!
 * \brief         Implementaion of SWC API Dem_GetEventExtendedDataRecordEx().
 *
 * \details       This API is intended to be called via RTE_CALL interface,
 *                as Operation of port interface 'DiagnosticInfo'.
 *
 *                Dem_GetEventExtendedDataRecordEx() copies extended data
 *                available or stored for an event into the passed buffer.
 *                This is particularly useful to retrieve statistic data, like
 *                occurrence counter or aging counter - if these are mapped to
 *                an extended data record.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 * \param[in]     RecordNumber
 *                Extended DataRecord number to read. The record numbers 0xfe
 *                and 0xff are reserved.
 * \param[out]    DestBuffer
 *                Buffer to receive the data.
 * \param[in,out] BufSize
 *                In:  Size of the buffer.
 *                Out: Number of bytes written.
 *
 * \return        E_OK
 *                The requested data was copied to the destination buffer.
 * \return        DEM_NO_SUCH_ELEMENT
 *                The data is not currently stored for the requested event
 *                or
 *                the requested data was not copied due to an undefined
 *                RecordNumber for the given event.
 * \return        E_NOT_OK
 *                The request was rejected, e.g. due to variant coding (see
 *                Dem_SetEventAvailable() )
 *                or
 *                the requested data is currently not accessible (e.g. in case
 *                of asynchronous preempted data retrieval from application).
 * \return        DEM_BUFFER_TOO_SMALL
 *                The provided buffer is too small.
 *
 * \pre           RTE is active (if RTE is used).
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_EnvDataSwcApi_GetEventExtendedDataRecordEx(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  RecordNumber,
  CONSTP2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)  DestBuffer,
  CONSTP2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  BufSize
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_ENVDATASWCAPI_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_EnvDataSwcApi_Interface.h
 *********************************************************************************************************************/
