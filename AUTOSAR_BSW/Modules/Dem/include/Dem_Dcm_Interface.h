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
 *  \defgroup   Dem_Dcm DEM DCM Interface
 *  \{
 *  \file       Dem_Dcm_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) Interface declaration file
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

#if !defined (DEM_DCM_INTERFACE_H)
#define DEM_DCM_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_Dcm_Types.h"
/* ------------------------------------------------------------------------- */


/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_Dcm_Public Public Methods
 * \{
 */

 /* ****************************************************************************
 * Dem_Dcm_IsObdIIFreezeFrameInService19EnabledInVariant
 *****************************************************************************/
 /*!
 * \brief         Return if OBDII freeze frame is supported in service 19 in variant.
 * \details       -
 *
 * \return        TRUE
 *                OBD-II freeze frame supported in service 19 
 *                and OBD II is active in variant.
 * \return        FALSE
 *                Either OBD-II freeze frame not supported in service 19 
 *                or OBD II is not active in variant.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Dcm_IsObdIIFreezeFrameInService19EnabledInVariant(
  void
  );



/* ****************************************************************************
 * Dem_Dcm_Init
 *****************************************************************************/
/*!
 * \brief         Initializes DCM state variables
 *
 * \details       Initializes DCM state variables
 *
 * \pre           May be called only during module initialization
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Dcm_Init(
  void
  );

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_Dcm_SRec_SelectFirstSource
 *****************************************************************************/
/*!
 * \brief         Invokes the correct function to select the first snapshot
 *                record source based on the selected DTC.
 *
 * \details       Invokes the correct function to select the first snapshot
 *                record source based on the selected DTC.
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
Dem_Dcm_SRec_SelectFirstSource(
  CONST(uint8, AUTOMATIC) ClientId,
  CONST(uint8, AUTOMATIC)  RecordNumber
  );
#endif


# if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_Dcm_SRec_ReadNextRecord
 *****************************************************************************/
/*!
 * \brief         Validates the request to copy snapshot record in UDS format
 *                and invokes the relevant functions to copy data to the given 
 *                buffer
 *
 * \details       Validates the request to copy snapshot record in UDS format
 *                and invokes the relevant functions to copy data to the given 
 *                buffer
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
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *              
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ClientIds.
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_SRec_ReadNextRecord(
  CONST(uint8, AUTOMATIC) ClientId,
  CONSTP2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)  DestBuffer,
  CONSTP2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  BufSize
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_Dcm_SRec_GetSize
 *****************************************************************************/
/*!
 * \brief         Invoke the correct function to retrieve size of selected
 *                freeze frame data.
 *
 * \details       Invoke the correct function to retrieve size of selected
 *                freeze frame data.
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
Dem_Dcm_SRec_GetSize(
  CONST(uint8, AUTOMATIC)  ClientId,
  CONSTP2VAR(uint16, AUTOMATIC, DEM_DCM_DATA)  SizeOfFreezeFrame
  );
#endif

#if (DEM_CFG_SUPPORT_PID01 == STD_ON)
/* ****************************************************************************
 * Dem_Dcm_ReadDataOfPID01
 *****************************************************************************/
/*!
 * \brief         Provides the monitoring status since DTCs cleared
 *
 * \details       Provides the monitoring status since DTCs cleared, formatted
 *                according to OBD-II
 *
 * \param[out]    PID01value
 *                Pointer to destination buffer. The PID data is formatted as such:
 *                supported - 0 == FALSE; 1 == TRUE
 *                ready     - 0 == TRUE; 1 == FALSE
 *                Byte 0
 *                  bit 0...6 - # of DTCs stored in this ECU
 *                  bit 7 - Malfunction Indicator Lamp (MIL) Status
 *                Byte 1
 *                  bit 0 - Misfire monitoring supported
 *                  bit 1 - Fuel system monitoring supported
 *                  bit 2 - Comprehensive component monitoring supported
 *                  bit 3 - Compression ignition monitoring supported
 *                  bit 4 - Misfire monitoring ready
 *                  bit 5 - Fuel system monitoring ready
 *                  bit 6 - Comprehensive component monitoring ready
 *                  bit 7 - reserved
 *                Byte 2
 *                  bit 0 - Catalyst monitoring supported
 *                  bit 1 - Heated catalyst monitoring supported
 *                  bit 2 - Evaporative system monitoring supported
 *                  bit 3 - Secondary air system monitoring supported
 *                  bit 4 - reserved
 *                  bit 5 - Oxygen sensor monitoring supported
 *                  bit 6 - Oxygen sensor heater monitoring
 *                  bit 7 - EGR system monitoring supported
 *                Byte3
 *                  bit 0 - Catalyst monitoring ready
 *                  bit 1 - Heated catalyst monitoring ready
 *                  bit 2 - Evaporative system monitoring ready
 *                  bit 3 - Secondary air system monitoring ready
 *                  bit 4 - reserved
 *                  bit 5 - Oxygen sensor monitoring ready
 *                  bit 6 - Oxygen sensor heater monitoring ready
 *                  bit 7 - EGR system monitoring ready
 * \param[in]     BufferSize
 *                Size of destination buffer
 * \return        E_OK
 *                Read PID01 succesful
 * \return        E_NOT_OK
 *                OBD not supported
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PID01 == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_ReadDataOfPID01(
  CONSTP2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  PID01value,
  CONST(uint8, AUTOMATIC) BufferSize
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_Dcm_GetStatusOfSelectedDTC
 *****************************************************************************/
/*!
 * \brief         Get the current Uds status of a selected DTC
 *
 * \details       Get the current Uds status of a selected DTC
 *
 * \param[in]     ClientId
 *                The client to query.
 *
 * \param[out]    DTCStatus
 *                Pointer to receive the Uds status
 *
 * \return        E_OK
 *                The requested status was stored in DTCStatus
 * \return        DEM_WRONG_DTC
 *                DTC is suppressed
 * \return        E_NOT_OK
 *                EventId of selection is invalid
 * \return        DEM_NO_SUCH_ELEMENT
 *                The selected DTC does not support a status
 *                (in case that permanent memory was selected as origin)
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           Requires a preceding DTC selection by Dem_SelectDTC
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_GetStatusOfSelectedDTC(
  uint8  ClientId,
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  DTCStatus
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_Dcm_GetSeverityOfSelectedDTC
 *****************************************************************************/
/*!
 * \brief         Get the severity of a selected DTC
 *
 * \details       Get the severity of a selected DTC
 *
 * \param[in]     ClientId
 *                The client to query.
 *
 * \param[out]    DTCSeverity
 *                Pointer to receive the severity
 *
 * \return        E_OK
 *                The requested severity was stored in DTCSeverity
 * \return        DEM_WRONG_DTC
 *                DTC is suppressed or a hidden dependent Secondary ECU DTC
 * \return        E_NOT_OK
 *                EventId of selection is invalid
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           Requires a preceding DTC selection by Dem_SelectDTC
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_GetSeverityOfSelectedDTC(
  CONST(uint8, AUTOMATIC)  ClientId,
  P2VAR(Dem_DTCSeverityType, AUTOMATIC, DEM_DCM_DATA)  DTCSeverity
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_Dcm_GetFunctionalUnitOfSelectedDTC
 *****************************************************************************/
/*!
 * \brief         Get the functional unit of a selected DTC
 *
 * \details       Get the functional unit of a selected DTC
 *
 * \param[in]     ClientId
 *                The client to query.
 *
 * \param[out]    DTCFunctionalUnit
 *                Pointer to receive the functional unit
 *
 * \return        E_OK
 *                The requested functional unit was stored in DTCFunctionalUnit
 * \return        DEM_WRONG_DTC
 *                DTC is suppressed or a hidden dependent Secondary ECU DTC
 * \return        E_NOT_OK
 *                EventId of selection is invalid
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           Requires a preceding DTC selection by Dem_SelectDTC
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_GetFunctionalUnitOfSelectedDTC(
  CONST(uint8, AUTOMATIC)  ClientId,
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  DTCFunctionalUnit
  );
#endif

/* ****************************************************************************
 * Dem_Dcm_GetEventIdOfSelectedDTC
 *****************************************************************************/
/*!
 * \brief         Get the EventId of a selected DTC
 *
 * \details       Get the EventId of a selected DTC
 *
 * \param[in]     ClientId
 *                The client to query.
 *
 * \param[out]    EventId
 *                Pointer to receive the EventId
 *
 * \return        E_OK
 *                The requested EventId was stored in EventId
 * \return        E_NOT_OK
 *                EventId of selection is invalid
 *
 * \pre           Requires a preceding DTC selection by Dem_SelectDTC
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_GetEventIdOfSelectedDTC(
  CONST(uint8, AUTOMATIC)  ClientId,
  P2VAR(Dem_EventIdType, AUTOMATIC, DEM_APPL_DATA)  EventId
  );

#if ((DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_WWHOBD == STD_ON) && (DEM_CFG_SUPPORT_PID91 == STD_ON))                                                                                         
/* ****************************************************************************
 * Dem_Dcm_TranslateActivationMode
 *****************************************************************************/
/*!
 * \brief         Maps the activation mode state to DCM format
 *
 * \details       This function maps the given activation mode state to the
 *                respective DCM representation:
 *                DEM_INDICATOR_CONTINUOUS -> 0x03
 *                DEM_INDICATOR_SHORT      -> 0x02
 *                DEM_INDICATOR_ON_DEMAND  -> 0x01
 *                DEM_INDICATOR_OFF        -> 0x00
 *
 * \param[in]     ActivationMode
 *                The internal activation mode state
 *
 * \return        DCM encoded Activation Mode
 *
 * \pre           -
 * \config          ((DEM_CFG_SUPPORT_DCM == STD_ON) \
 *                && (DEM_CFG_SUPPORT_WWHOBD == STD_ON) \ 
 *                && (DEM_CFG_SUPPORT_PID91 == STD_ON))    
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Dcm_TranslateActivationMode(
  CONST(Dem_IndicatorStatusType, AUTOMATIC)  ActivationMode
  );
#endif

#if (DEM_CFG_SUPPORT_SRECS == STD_ON) && (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 * Dem_Dcm_TimeSeriesSRecIsValid
 *****************************************************************************/
/*!
 * \brief         Tests whether a time series snapshot record number is valid
 *
 * \details       Tests whether a time series snapshot record number is valid
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     RecordNumber
 *                Snapshot record number
 *
 * \return        TRUE
 *                The record number is valid
 * \return        FALSE
 *                The record number is invalid
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_SRECS == STD_ON && 
 *                DEM_FEATURE_NEED_TIME_SERIES == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_Dcm_TimeSeriesSRecIsValid(
  Dem_EventIdType EventId,
  uint8 RecordNumber
  );
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */


#endif /* DEM_DCM_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Dcm_Interface.h
 *********************************************************************************************************************/
