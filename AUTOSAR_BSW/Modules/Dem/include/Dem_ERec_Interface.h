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
 *  \defgroup   Dem_ERec ERec
 *  \{
 *  \file       Dem_ERec_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) Interface declaration file for processing ERec specific DCM service requests 
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined ( DEM_EREC_INTERFACE_H)
#define  DEM_EREC_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_ERec_Types.h"
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

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DECLARATIONS
 *********************************************************************************************************************/
# define DEM_START_SEC_CODE
# include "MemMap.h"                                                                                                             /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_ERec_Public Public Methods
 * \{
 */

/* ****************************************************************************
 *  Dem_Dcm_ERec_0x1916_IsService19_16Enabled
 *****************************************************************************/
 /*!
 * \brief         Returns true if service 19 16 is enabled
 * \details       Returns true if service 19 subfunction 16 is enabled
 *
 * \return        TRUE
 *                Support for service 19 subfunction 16
 * \return        FALSE
 *                No support for service 19 16
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
 Dem_Dcm_ERec_0x1916_IsService19_16Enabled(
  void
);

 /* ****************************************************************************
 *  Dem_Dcm_ERec_0x1916_TestFilterSet
 *****************************************************************************/
 /*!
 * \brief         Test that extended data record filter has been set.
 *
 * \details       Test that extended data record number filter has been set.
 *
 * \param[in]     ExtendedDataFilterId
 *                The extended data iterator handle to test.
 *
 * \return        TRUE
 *                The extended data record number filter can be used.
 * \return        FALSE
 *                The extended data record number filter is not well defined.
 *
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
 Dem_Dcm_ERec_0x1916_TestFilterSet(
  CONST( Dem_Dcm_ERec_0x1916_RecordNumberFilter_HandleType, AUTOMATIC)  ExtendedDataFilterId
);


/* ****************************************************************************
 *  Dem_Dcm_ERec_0x1916_InitERecNumberFilter
 *****************************************************************************/
/*!
 * \brief         Initializes extended data record number of a client.
 *
 * \details       Initializes extended data record number of a client.
 *
 * \param[in]     ExtendedDataFilterId
 *                The extended data filter identifier.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ClientIDs
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
 Dem_Dcm_ERec_0x1916_InitERecNumberFilter(
  CONST( Dem_Dcm_ERec_0x1916_RecordNumberFilter_HandleType, AUTOMATIC)  ExtendedDataFilterId
);

 /* ****************************************************************************
  *  Dem_Dcm_ERec_0x1916_SetRecordFilter
  *****************************************************************************/
 /*!
  * \brief         Initialize the extended data iterator with given criteria.
  *
  * \details       Initialize the extended data iterator with given criteria.
  *
  * \param[in]     ExtendedDataFilterId
  *                The extended data iterator handle.
  * \param[in]     RecordNumber
  *                Requested record number.
  *
  * \pre           -
  *
  * \context       TASK|ISR2
  * \synchronous   TRUE for different ClientID
  * \reentrant     TRUE for different ClientIDs
  *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
 Dem_Dcm_ERec_0x1916_SetRecordFilter(
  CONST( Dem_Dcm_ERec_0x1916_RecordNumberFilter_HandleType, AUTOMATIC) ExtendedDataFilterId,
  CONST(uint8, AUTOMATIC) RecordNumber
);

/* ****************************************************************************
 *  Dem_Dcm_ERec_0x1916_CalcNumberofERecs
 *****************************************************************************/
/*!
 * \brief         Calculate number of extended data record with a certain record number
 *
 * \details       Calculate number of extended data record with a certain record number
 *
 * \param[in]     ExtendedDataFilterId
 *                The extended data iterator handle.
 * \param[out]    NumberOfFilteredRecords
 *                The count of all readable ERecs.
 * \param[out]    SizeOfExtendedDataRecord
 *                Size of one extended data record.
 *
 * \pre           Feature Service 0x19 16 is enabled and extended data records are 
 *                configured.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ClientIDs
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
 Dem_Dcm_ERec_0x1916_CalcNumberofERecs(
  Dem_Dcm_ERec_0x1916_RecordNumberFilter_HandleType ExtendedDataFilterId,
  P2VAR(uint16, AUTOMATIC, DEM_DCM_DATA)  NumberOfFilteredRecords,
  P2VAR(uint16, AUTOMATIC, DEM_DCM_DATA)  SizeOfExtendedDataRecord
);


/* ****************************************************************************
 *  Dem_Dcm_ERec_0x1916_GetNextFilteredERecData
 *****************************************************************************/
/*!
 * \brief         Provides the next extended data record data and DTCStatus.
 *
 * \details       Provides the next extended data record data and DTCStatus.
 *
 * \param[in]     ExtendedDataFilterId
 *                The extended data iterator handle.
 * \param[out]    DTC
 *                DTC identifier in the requested format.
 * \param[out]    DTCStatus
 *                Current UDS status of the DTC.
 * \param[out]    DestBuffer
 *                Destination buffer, in which the ERec extended data record 
 *                is written to.
 * \param[in,out] BufSize
 *                In:  Size of Buffer.
 *                Out: Number of written bytes.
 *
 * \return        E_OK
 *                Record copied.
 * \return        DEM_NO_SUCH_ELEMENT
 *                No record found or reporting done.
 * \return        DEM_PENDING
 *                Record is concurrently updated.
 *
 * \pre           Feature Service 0x19 16 is enabled and extended data records are
 *                configured.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ClientIDs
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
 Dem_Dcm_ERec_0x1916_GetNextFilteredERecData(
  Dem_Dcm_ERec_0x1916_RecordNumberFilter_HandleType ExtendedDataFilterId,
  P2VAR(uint32, AUTOMATIC, DEM_DCM_DATA) DTC,
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA) DTCStatus,
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA) DestBuffer,
  P2VAR(uint16, AUTOMATIC, DEM_DCM_DATA) BufSize
);


#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_Dcm_ERec_ReadNextRecord
 *****************************************************************************/
/*!
 * \brief         Validates the request to get an extended data record in UDS
 *                format and invokes the correct function to copy the data.
 *
 * \details       Validates the request to get an extended data record in UDS
 *                format and invokes the correct function to copy the data.
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
Dem_Dcm_ERec_ReadNextRecord(
  CONST(uint8, AUTOMATIC)  ClientId,
  CONSTP2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)  DestBuffer,
  CONSTP2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  BufSize
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_Dcm_ERec_GetSize
 *****************************************************************************/
/*!
 * \brief         Invokes the correct function to get the size of one or all 
 *                extended data record(s)
 *
 * \details       Invokes the correct function to get the size of one or all 
 *                extended data record(s) based on whether a combined event was
 *                selected or not.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 * \param[out]    SizeOfExtendedDataRecord
 *                Number of bytes.
 *
 * \return        E_OK
 *                Data was found and returned
 *
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
Dem_Dcm_ERec_GetSize(
  CONST(uint8, AUTOMATIC) ClientId,
  CONSTP2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  SizeOfExtendedDataRecord
  );
#endif


#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_Dcm_ERec_SelectRecord
 *****************************************************************************/
/*!
 * \brief         Select the the given extended data record
 *
 * \details       Select the the given extended data record
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
Dem_Dcm_ERec_SelectRecord(
  CONST(uint8, AUTOMATIC) ClientId,
  CONST(uint8, AUTOMATIC)  RecordNumber
  );
#endif

/* ****************************************************************************
 *  Dem_Dcm_ERec_0x191A_IsService19_1AEnabled
*****************************************************************************/
/*!
 * \brief         Returns true if service 19 1A is enabled
 * \details       Returns true if service 19 subfunction 1A is enabled
 *
 * \return        TRUE
 *                Support for service 19 subfunction 1A
 * \return        FALSE
 *                No support for service 19 1A
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Dcm_ERec_0x191A_IsService19_1AEnabled(
  void
);

/* ****************************************************************************
 *  Dem_Dcm_ERec_0x191A_SetDTCFilterByExtendedDataRecordNumber
*****************************************************************************/
/*!
 * \brief         Initialize the DTC filter for extended data record number filtering.
 *
 * \details       Initialize the DTC filter for extended data record number filtering.
 *
 * \param[in]     DTCFilterId
 *                The DTC filter handle.
 * \param[in]     ExtendedDataRecordNumber
 *                Number of the extended data record.
 *
 * \pre           Feature Service 0x19 1A is enabled and DCM support is enabled
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different DTCFilterIds
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dcm_ERec_0x191A_SetDTCFilterByExtendedDataRecordNumber(
  Dem_FilterData_HandleType DTCFilterId,
  uint8 ExtendedDataRecordNumber
);

/* ****************************************************************************
 *  Dem_Dcm_ERec_0x191A_GetNumberOfFilteredDTCsByERecNumber
 *****************************************************************************/
/*!
 * \brief         Calculate number of DTCs with a certain extended data record
 *
 * \details       Calculate number of DTCs with a certain extended data record
 *
 * \param[in]     DataCollectionTableIdx
 *                Index of the Data Collection Table.
 *
 * \return        Number of DTCs
 *
 * \pre           Feature Service 0x19 1A is enabled and DCM support is enabled
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Dcm_ERec_0x191A_GetNumberOfFilteredDTCsByERecNumber(
  Dem_Cfg_ERecIndexType DataCollectionTableIdx
);

/* ****************************************************************************
 * Dem_Dcm_ERec_0x191A_FilterDTCByERecNumber
 *****************************************************************************/
/*!
 * \brief         Iterates over events with a certain extended data record.
 *
 * \details       Iterates over events with a certain extended data record.
 *                The events with a certain extended data record is specified in DTC Filter.
 *                
 *
 * \param[in]     DTCFilterPtr
 *                Pointer to a DTC filter.
 *
 * \return        EventId of the next event maching the extended data record filter criteria.
 *
 * \pre           Feature Service 0x19 1A is enabled and DCM support is enabled
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE for different DTCFilterIds
 *****************************************************************************/
DEM_LOCAL FUNC(Dem_EventIdType, DEM_CODE)
Dem_Dcm_ERec_0x191A_FilterDTCByERecNumber(
  CONSTP2VAR(Dem_Cfg_FilterData_InfoType, AUTOMATIC, AUTOMATIC)  DTCFilterPtr
);

/*!
 * \}
 */
# define DEM_STOP_SEC_CODE
# include "MemMap.h"                                                                                                             /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /*  DEM_EREC_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE:  Dem_ERec_Interface.h
 *********************************************************************************************************************/
