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
/*! \addtogroup Dem_FilterDataIF
 *  \{
 *  \file       Dem_FilterDataIF_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Implementation of FilterDataIF subcomponent
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_FILTERDATAIF_IMPLEMENTATION_H)
#define DEM_FILTERDATAIF_IMPLEMENTATION_H

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
#include "Dem_FilterDataIF_Interface.h"

/* Includes to access public functions belonging to other (top level)/ (logical)/- units to be used by this Unit */
/* ------------------------------------------------------------------------- */
#include "Dem_Infrastructure_Interface.h"
#include "Dem_FaultMemory_Interface.h"
#include "Dem_Core_Interface.h"
#include "Dem_DiagnosticObserver_Interface.h"
#include "Dem_RecordReader_Interface.h"
#include "Dem_DTCReporting_Interface.h"
#include "Dem_0x1956_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*! Filename declaration */
#define DEM_FILTERDATAIF_IMPLEMENTATION_FILENAME "Dem_FilterDataIF_Implementation.h"

/*!
 * \defgroup  Dem_FilterData_FilterFlags  Macros encoding the filter flags of a filter.
 * \{
 */
#define DEM_FILTERDATA_FILTERFLAGS_USESTATUSMASK                   (0x01U) /*!< Status mask is used for filtering */
#define DEM_FILTERDATA_FILTERFLAGS_USEFDC                          (0x02U) /*!< FDC is used for filtering */
#define DEM_FILTERDATA_FILTERFLAGS_USESEVERITY                     (0x04U) /*!< Severity is used for filtering */
#define DEM_FILTERDATA_FILTERFLAGS_USEFORMATOBD                    (0x08U) /*!< DTCFormat OBD is used for filtering */
#define DEM_FILTERDATA_FILTERFLAGS_FILTEREMISSIONRELEVANT          (0x10U) /*!< Filtering for emsission relevant DTCs */

#define DEM_FILTERDATA_FILTERFLAGS_INITIAL                         (0x00U) /*!< Initial value of filter flags */

/*! The inverse of DEM_FILTERDATA_FILTERFLAGS_USESTATUSMASK */
#define DEM_FILTERDATA_FILTERFLAGS_USESTATUSMASK_MASK              DEM_BIT_MASK(0, DEM_1BYTE)

/*! The inverse of DEM_FILTERDATA_FILTERFLAGS_USEFDC */
#define DEM_FILTERDATA_FILTERFLAGS_USEFDC_MASK                     DEM_BIT_MASK(1, DEM_1BYTE)

/*! The inverse of DEM_FILTERDATA_FILTERFLAGS_USESEVERITY */
#define DEM_FILTERDATA_FILTERFLAGS_USESEVERITY_MASK                DEM_BIT_MASK(2, DEM_1BYTE)

/*! The inverse of DEM_FILTERDATA_FILTERFLAGS_DTCFORMATOBD */
#define DEM_FILTERDATA_FILTERFLAGS_USEFORMATOBD_MASK               DEM_BIT_MASK(3, DEM_1BYTE)

/*! The inverse of DEM_FILTERDATA_FILTERFLAGS_FILTEREMISSIONRELEVANT */
#define DEM_FILTERDATA_FILTERFLAGS_FILTEREMISSIONRELEVANT_MASK     DEM_BIT_MASK(4, DEM_1BYTE)
/*!
 * \}
 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/
/* Marker for already filtered events for DTC Filter ------------ */
/*! Size of bitfield of already filtered events */
#define DEM_FILTERDATA_FILTEREDEVENTS_SIZE(NumEvents)         (uint16)(((NumEvents)+7)/8)
/*! Index of event in bitfield of already filtered events */
#define DEM_FILTERDATA_FILTEREDEVENTS_INDEX(EventId)          (uint16)((EventId)/8)
/*! Bitmask for bitfield of already filtered events */
#define DEM_FILTERDATA_FILTEREDEVENTS_MASK(EventId)           (uint8)(0x01u << ((uint8)((EventId) % 8)))

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE PROPERTIES DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_FilterData_PrivateProperties Private Properties
 * \{
 */

/* ****************************************************************************
 * Dem_Client_FilterData_GetFilterData()
 *****************************************************************************/
 /*!
 * \brief         Get the data of a DTC filter.
 *
 * \details       Get the data of a DTC filter.
 *
 * \param[in]     FilterId
 *                The object to read from.
 * \return        The data of the DTC filter
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_FilterData_InfoType, DEM_CODE)
Dem_Client_FilterData_GetFilterData(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  );


/* ****************************************************************************
 * Dem_Client_FilterData_GetState()
 *****************************************************************************/
/*!
 * \brief         Get the filter state of the given filter object.
 *
 * \details       Get the filter state of the given filter object.
 *
 * \param[in]     FilterId
 *                The object to read from.
 *
 * \return        The filter state of the filter object.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_FilterData_FilterType, DEM_CODE)
Dem_Client_FilterData_GetState(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  );

/* ****************************************************************************
 * Dem_Client_FilterData_TestUseStatusMask()
 *****************************************************************************/
/*!
 * \brief         Get the UseStatusMask flag of the given filter flags.
 *
 * \details       Get the UseStatusMask flag of the given filter flags.
 *
 * \param[in]     FilterId
 *                The Filter object handle.
 *
 * \return        The state of the UseStatusMask flag.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Client_FilterData_TestUseStatusMask(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  );


/* ****************************************************************************
 * Dem_Client_FilterData_TestUseFormatOBD()
 *****************************************************************************/
/*!
 * \brief         Get the UseFormatOBD flag of the given filter flags.
 *
 * \details       Get the UseFormatOBD flag of the given filter flags.
 *
 * \param[in]     FilterId
 *                The Filter object handle.
 *
 * \return        The state of the UseFormatOBD flag.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Client_FilterData_TestUseFormatOBD(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  );


/* ****************************************************************************
 * Dem_Client_FilterData_TestFilterEmissionRelevant()
 *****************************************************************************/
/*!
 * \brief         Test the emission relevant flag in the filter flags
 *
 * \details       Test the emission relevant flag in the filter flags
 *
 * \param[in]     FilterId
 *                The Filter object handle
 *
 * \return        TRUE
 *                The emission relevant flag is set
 * \return        TRUE
 *                The emission relevant flag is not set
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Client_FilterData_TestFilterEmissionRelevant(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  );


/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE PROPERTIES DEFINITIONS
 *********************************************************************************************************************/

/* ****************************************************************************
 % Dem_Client_FilterData_GetFilterData()
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_FilterData_InfoType, DEM_CODE)
Dem_Client_FilterData_GetFilterData(                                                                                                    /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
)
{
  return Dem_Cfg_GetFilterInfoTable(FilterId);                                                                                   
}

/* ****************************************************************************
 % Dem_Client_FilterData_GetState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_FilterData_FilterType, DEM_CODE)
Dem_Client_FilterData_GetState(                                                                                                         /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
CONST(Dem_FilterData_HandleType, AUTOMATIC) FilterId
)
{
  return Dem_Cfg_GetFilterInfoTable(FilterId).FilterState;                                                                       
}



/* ****************************************************************************
 % Dem_Client_FilterData_TestUseStatusMask()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Client_FilterData_TestUseStatusMask(                                                                                                /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  )
{
  return (boolean)((Dem_Cfg_GetFilterInfoTable(FilterId).FilterFlags & DEM_FILTERDATA_FILTERFLAGS_USESTATUSMASK) != 0u);
}


/* ****************************************************************************
 % Dem_Client_FilterData_TestUseFormatOBD()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Client_FilterData_TestUseFormatOBD(                                                                                                 /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  )
{
  return (boolean)((Dem_Cfg_GetFilterInfoTable(FilterId).FilterFlags & DEM_FILTERDATA_FILTERFLAGS_USEFORMATOBD) != 0u);
}


/* ****************************************************************************
 % Dem_Client_FilterData_TestFilterEmissionRelevant()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Client_FilterData_TestFilterEmissionRelevant(                                                                                       /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  )
{
  return (boolean)((Dem_Cfg_GetFilterInfoTable(FilterId).FilterFlags & DEM_FILTERDATA_FILTERFLAGS_FILTEREMISSIONRELEVANT) != 0u);  
}
/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/* ********************************************************************************************************************
 *  SUBCOMPONENT PUBLIC PROPERTIES DEFINITIONS
 *********************************************************************************************************************/

#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \addtogroup Dem_FilterData_PublicProperties
 * \{
 */


/* ****************************************************************************
 % Dem_Client_FilterData_TestFilterSet
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Client_FilterData_TestFilterSet(                                                                                                    /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_FilterData_HandleType, AUTOMATIC) FilterId,
  CONST(Dem_FilterData_FilterType, DEM_CODE) Filter
  )
{
  return (boolean)(Dem_Client_FilterData_GetState(FilterId) == Filter);
}

/* ****************************************************************************
 % Dem_Client_FilterData_TestUseFdc()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Client_FilterData_TestUseFdc(                                                                                                       /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  )
{
  return (boolean)((Dem_Cfg_GetFilterInfoTable(FilterId).FilterFlags & DEM_FILTERDATA_FILTERFLAGS_USEFDC) != 0u);                
}

/* ****************************************************************************
 % Dem_Client_FilterData_TestUseSeverity()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Client_FilterData_TestUseSeverity(                                                                                                  /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  )
{
  return (boolean)((Dem_Cfg_GetFilterInfoTable(FilterId).FilterFlags & DEM_FILTERDATA_FILTERFLAGS_USESEVERITY) != 0u);           
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_FilterData_Private Private Methods
 * \{
 */


 /* ****************************************************************************
 * Dem_Client_FilterData_SetFilterData()
 *****************************************************************************/
 /*!
 * \brief         Set the data of a DTC filter.
 *
 * \details       Set the data of a DTC filter.
 *                Used when a majority of data elements have to be set in bulk.
 *
 * \param[in]     FilterId
 *                The object to write to.
 * \param[in]     FilterData
 *                The filter data to be set.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different FilterId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Client_FilterData_SetFilterData(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId,
  CONST(Dem_Cfg_FilterData_InfoType, AUTOMATIC)  FilterData
);


/* ****************************************************************************
 * Dem_Client_FilterData_InitFilterFlagsAndMasks()
 *****************************************************************************/
/*!
 * \brief         Initialize the filter flags and masks for a 'filter DTC' request.
 *
 * \details       Initialize the filter flags and the status and severity mask
 *                for a 'filter DTC' request.
 *
 * \param[in]     FilterId
 *                The filter to be set.
 * \param[in]     DTCFormat
 *                The DTC number format (OBD/UDS/J1939) to be used for the filter.
 * \param[in]     StatusMask
 *                The status mask to be set in the filter.
 * \param[in]     FilterForOBD
 *                Defines if filtering is restricted to OBD related DTCs.
 * \param[in]     FilterWithSeverity
 *                Defines if severity information is used for filtering.
 * \param[in]     SeverityMask
 *                The severity mask to be set in the filter (only evaluated
 *                if severity information is used for filtering).
 * \param[in]     FilterForFDC
 *                Defines if FDC information is used for filtering.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different FilterId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Client_FilterData_InitFilterFlagsAndMasks(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId,
  CONST(uint8, AUTOMATIC)  StatusMask,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat,
  CONST(boolean, AUTOMATIC)  FilterForOBD,
  CONST(boolean, AUTOMATIC)  FilterWithSeverity,
  CONST(Dem_DTCSeverityType, AUTOMATIC)  SeverityMask,
  CONST(boolean, AUTOMATIC)  FilterForFDC
);


/* ****************************************************************************
 * Dem_Client_FilterData_SetState()
 *****************************************************************************/
/*!
 * \brief         Set the filter state in the given filter object
 *
 * \details       Set the filter state in the given filter object to the given value
 *
 * \param[in]     FilterId
 *                The object to write to.
 * \param[in]     NewState
 *                The new state to be set in the filter object.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Client_FilterData_SetState(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId,
  CONST(Dem_FilterData_FilterType, AUTOMATIC)  NewState
);

/* ****************************************************************************
 * Dem_Client_FilterData_GetEventId()
 *****************************************************************************/
 /*!
 * \brief         Get the event Id stored in the filter object.
 *
 * \details       Get the event Id  stored in the filter object for DTC 
 *                filtering.
 *
 * \param[in]     FilterId
 *                The object to read from.
 *
 * \return        The event Id  stored in the filter object for DTC 
 *                filtering.
 *
 * \return        DEM_EVENT_INVALID if no DTC filter is set up.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Client_FilterData_GetEventId(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  );


/* ****************************************************************************
 * Dem_Client_FilterData_GetChronoIter()
 *****************************************************************************/
/*!
 * \brief         Get the Chrono Index stored in the filter object.
 *
 * \details       Get the Chrono Index in the filter object for DTC filtering.
 *
 * \param[in]     FilterId
 *                The object to read from.
 *
 * \return        The Chrono Index stored in the filter object for DTC filtering.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Client_FilterData_GetChronoIter(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  );


/* ****************************************************************************
 * Dem_Client_FilterData_GetStatusMask()
 *****************************************************************************/
/*!
 * \brief         Get the status mask stored in the filter object.
 *
 * \details       Get the status mask stored in the filter object for DTC filtering.
 *
 * \param[in]     FilterId
 *                The object to read from.
 *
 * \return        The status mask stored in the filter object for DTC filtering.
 *
 * \return        0x00 if no DTC filter is set up.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Client_FilterData_GetStatusMask(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  );


/* ****************************************************************************
 * Dem_Client_FilterData_GetFDC()
 *****************************************************************************/
/*!
 * \brief         Get the fault detection counter in the given filter object.
 *
 * \details       Set the fault detection counter in the given filter object.
 *
 * \param[in]     FilterId
 *                The object to read from.
 *
 * \return        The FDC stored filter object.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(sint8, DEM_CODE)
Dem_Client_FilterData_GetFDC(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  );


/* ****************************************************************************
 * Dem_Client_FilterData_GetMemoryId()
 *****************************************************************************/
/*!
 * \brief         Get the MemoryId stored in the filter object.
 *
 * \details       Get the MemoryId stored in the filter object for DTC filtering.
 *
 * \param[in]     FilterId
 *                The object to read from.
 *
 * \return        The MemoryId stored in the filter object for DTC filtering.
 *
 * \return        DEM_CFG_MEMORYID_INVALID if no DTC filter is set up.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Client_FilterData_GetMemoryId(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  );


/* ****************************************************************************
 * Dem_Client_FilterData_GetSeverityMask()
 *****************************************************************************/
/*!
 * \brief         Get the severity mask stored in the filter object.
 *
 * \details       Get the severity mask stored in the filter object for DTC filtering.
 *
 * \param[in]     FilterId
 *                The object to read from.
 *
 * \return        The severity mask stored in the filter object for DTC filtering.
 *
 * \return        0x00 if no DTC filter is set up.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTCSeverityType, DEM_CODE)
Dem_Client_FilterData_GetSeverityMask(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  );


#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_Client_FilterData_GetDTCFilteringStrategy()
 *****************************************************************************/
/*!
 * \brief         Get the DTC filtering strategy.
 *
 * \details       Get an enumerator indicating the DTC filtering strategy  
 *                corresponding to the filter object.
 *
 * \param[in]     FilterId
 *                The object to read from.
 *
 * \return        An enumerator indicating the DTC filtering strategy 
 *                corresponding to the filter object.
 *
 * \return        0x00 if no DTC filtering strategy is configured.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_FilterData_DTCFilteringStrategyType, DEM_CODE)
Dem_Client_FilterData_GetDTCFilteringStrategy(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  );
#endif


#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_Client_FilterData_GetDTCFilterFunction()
 *****************************************************************************/
/*!
 * \brief         Get the DTC filter function.
 *
 * \details       Get the DTC filter function corresponding to the DTC
 *                filtering strategy.
 *
 * \param[in]     DTCFilteringStrategy
 *                The DTC filtering strategy.
 *
 * \return        Function pointer of the corresponding DTC filter function.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_FilterData_FuncPtrType, DEM_CODE)
Dem_Client_FilterData_GetDTCFilterFunction(
  CONST(Dem_FilterData_DTCFilteringStrategyType, AUTOMATIC)  DTCFilteringStrategy
  );
#endif


/* ****************************************************************************
 * Dem_Client_FilterData_GetNodeId()
 *****************************************************************************/
/*!
 * \brief         Get the node Id stored in the filter object.
 *
 * \details       Get the node Id  stored in the filter object for DTC 
 *                filtering.
 *
 * \param[in]     FilterId
 *                The object to read from.
 *
 * \return        The node Id  stored in the filter object for DTC 
 *                filtering.
 *
 * \return        DEM_CFG_J1939_NODE_INVALID if no DTC filter is set up.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Client_FilterData_GetNodeId(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  );


/* ****************************************************************************
 * Dem_Client_FilterData_GetDTCStatusFilterType()
 *****************************************************************************/
/*!
 * \brief         Get the DTC status filter type stored in the filter object.
 *
 * \details       Get the DTC status filter type stored in the filter object 
 *                for DTC filtering.
 *
 * \param[in]     FilterId
 *                The object to read from.
 *
 * \return        The DTC status filter type stored in the filter object for 
 *                DTC filtering.
 *
 * \return        0 if no DTC filter is set up.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_J1939DcmDTCStatusFilterType, DEM_CODE)
Dem_Client_FilterData_GetDTCStatusFilterType(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  );


/* ****************************************************************************
 * Dem_Client_FilterData_SetFDC()
 *****************************************************************************/
/*!
 * \brief         Set the status mask in the given filter object.
 *
 * \details       Set the status mask in the given filter object for DTC filtering.
 *
 * \param[in]     FilterId
 *                The object to write to.
 *
 * \param[in]     FDC
 *                The FDC to be set in the filter object for DTC filtering.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Client_FilterData_SetFDC(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId,
  CONST(sint8, AUTOMATIC)  FDC
  );


/* ****************************************************************************
 * Dem_Client_FilterData_SetUseStatusMask()
 *****************************************************************************/
/*!
 * \brief         Set the UseStatusMask flag in the filter flags.
 *
 * \details       Set the UseStatusMask flag in the filter flags.
 *
 * \param[in]     FilterFlags
 *                The current filter flags
 *
 * \return        The modified filter flags
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Client_FilterData_SetUseStatusMask(
  CONST(uint8, AUTOMATIC)  FilterFlags
  );


/* ****************************************************************************
 * Dem_Client_FilterData_ResetUseStatusMask()
 *****************************************************************************/
/*!
 * \brief         Reset the UseStatusMask flag in the filter flags.
 *
 * \details       Reset the UseStatusMask flag in the filter flags.
 *
 * \param[in]     FilterFlags
 *                The current filter flags
 *
 * \return        The modified filter flags
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Client_FilterData_ResetUseStatusMask(
  CONST(uint8, AUTOMATIC)  FilterFlags
  );


/* ****************************************************************************
 * Dem_Client_FilterData_SetUseFdc()
 *****************************************************************************/
/*!
 * \brief         Set the UseFdc flag in the filter flags.
 *
 * \details       Set the UseFdc flag in the filter flags.
 *
 * \param[in]     FilterFlags
 *                The current filter flags
 *
 * \return        The modified filter flags
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Client_FilterData_SetUseFdc(
  CONST(uint8, AUTOMATIC)  FilterFlags
  );


/* ****************************************************************************
 * Dem_Client_FilterData_ResetUseFdc()
 *****************************************************************************/
/*!
 * \brief         Reset the UseStatusMask flag in the filter flags.
 *
 * \details       Reset the UseStatusMask flag in the filter flags.
 *
 * \param[in]     FilterFlags
 *                The current filter flags
 *
 * \return        The modified filter flags
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Client_FilterData_ResetUseFdc(
  CONST(uint8, AUTOMATIC)  FilterFlags
  );


/* ****************************************************************************
 * Dem_Client_FilterData_SetUseSeverity()
 *****************************************************************************/
/*!
 * \brief         Set the UseSeverity flag in the filter flags.
 *
 * \details       Set the UseSeverity flag in the filter flags.
 *
 * \param[in]     FilterFlags
 *                The current filter flags
 *
 * \return        The modified filter flags
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Client_FilterData_SetUseSeverity(
  CONST(uint8, AUTOMATIC)  FilterFlags
  );


/* ****************************************************************************
 * Dem_Client_FilterData_ResetUseSeverity()
 *****************************************************************************/
/*!
 * \brief         Reset the UseSeverity flag in the filter flags.
 *
 * \details       Reset the UseSeverity flag in the filter flags.
 *
 * \param[in]     FilterFlags
 *                The current filter flags
 *
 * \return        The modified filter flags
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Client_FilterData_ResetUseSeverity(
  CONST(uint8, AUTOMATIC)  FilterFlags
  );


/* ****************************************************************************
 * Dem_Client_FilterData_SetUseFormatOBD()
 *****************************************************************************/
/*!
 * \brief         Set the UseFormatOBD flag in the filter flags.
 *
 * \details       Set the UseFormatOBD flag in the filter flags.
 *
 * \param[in]     FilterFlags
 *                The current filter flags
 *
 * \return        The modified filter flags
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Client_FilterData_SetUseFormatOBD(
  CONST(uint8, AUTOMATIC)  FilterFlags
  );


/* ****************************************************************************
 * Dem_Client_FilterData_ResetUseFormatOBD()
 *****************************************************************************/
/*!
 * \brief         Reset the UseFormatOBD flag in the filter flags.
 *
 * \details       Reset the UseFormatOBD flag in the filter flags.
 *
 * \param[in]     FilterFlags
 *                The current filter flags
 *
 * \return        The modified filter flags
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Client_FilterData_ResetUseFormatOBD(
  CONST(uint8, AUTOMATIC)  FilterFlags
  );


/* ****************************************************************************
 * Dem_Client_FilterData_SetFilterEmissionRelevant()
 *****************************************************************************/
/*!
 * \brief         Set the emission relevant flag in the filter flags
 *
 * \details       Set the emission relevant flag in the filter flags
 *
 * \param[in]     FilterFlags
 *                The current filter flags
 *
 * \return        The modified filter flags
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
  *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Client_FilterData_SetFilterEmissionRelevant(
  CONST(uint8, AUTOMATIC)  FilterFlags
  );


/* ****************************************************************************
 * Dem_Client_FilterData_ResetFilterEmissionRelevant()
 *****************************************************************************/
/*!
 * \brief         Set the emission relevant flag in the filter flags
 *
 * \details       Set the emission relevant flag in the filter flags
 *
 * \param[in]     FilterFlags
 *                The current filter flags
 *
 * \return        The modified filter flags
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Client_FilterData_ResetFilterEmissionRelevant(
  CONST(uint8, AUTOMATIC)  FilterFlags
  );


#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_Client_FilterData_ResetReportedEvents()
 *****************************************************************************/
/*!
 * \brief         Clear the bitfield of reported events for the given filter.
 *
 * \details       Clear the bitfield of reported events for the given filter.
 *                Function does nothing if chronological reporting is not 
 *                required.
 *
 * \param[in]     FilterId
 *                The object to write to.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Client_FilterData_ResetReportedEvents(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  );
#endif


#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_Client_FilterData_SetEventReported()
 *****************************************************************************/
/*!
 * \brief         Marks an event as reported in the corresponding filter's bitfield.
 *
 * \details       Marks an event as reported in the corresponding filter's bitfield.
 *
 * \param[in]     FilterId
 *                The object to write to.
 * \param[in]     EventId
 *                Id of the corresponding event
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Client_FilterData_SetEventReported(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId,
  CONST(Dem_EventIdType, AUTOMATIC) EventId
  );
#endif


#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_Client_FilterData_TestEventReported()
 *****************************************************************************/
/*!
 * \brief         Tests whether an event is already reported.
 *
 * \details       Tests whether bit corresponding to the event is set in the
 *                filter's bitfield.
 *
 * \param[in]     FilterId
 *                The identifier to read from.
 * \param[in]     EventId
 *                Id of the corresponding event.
 *
 * \return        TRUE
 *                The event was already reported.
 * \return        FALSE
 *                The event is not yet reported.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Client_FilterData_TestEventReported(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId,
  CONST(Dem_EventIdType, AUTOMATIC) EventId
  );
#endif


#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_Client_FilterData_InitDTCFilter()
 *****************************************************************************/
/*!
 * \brief         Initialize a filter for a 'filter DTC' request.
 *
 * \details       Initialize the event and memory Id and the filter function
 *                for a 'filter DTC' request.
 *
 * \param[in]     FilterId
 *                The filter to be set.
 * \param[in]     MemoryId
 *                The event memory handle to be set in the filter.
 * \param[in]     StatusMask
 *                The status mask to be considered in the filter.
 *
 * \return        E_OK
 *                The filter was initialized.
 * \return        E_NOT_OK
 *                The filter was not initialized due to an unconfigured memory.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different FilterId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Client_FilterData_InitDTCFilter(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId,
  CONST(uint8, AUTOMATIC)  MemoryId,
  CONST(uint8, AUTOMATIC)  StatusMask
  );
#endif


#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_Client_FilterData_FilterForEventMatch()
 *****************************************************************************/
/*!
 * \brief         Test whether a given EventId matches the filter.
 *
 * \details       Test whether a given EventId matches the filter.
 *
 * \param[in]     FilterId
 *                The filter to be set.
 * \param[in]     EventId
 *                Unique handle of the Event
 *
 * \return        E_OK
 *                EventId matches the filter criteria
 * \return        E_NOT_OK
 *                EventId does not mmatche the filter criteria
 *
 * \pre           A filter was set for the FilterId with 
 *                Dem_Client_FilterData_InitFilterFlagsAndMasks()
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different FilterId
 *****************************************************************************/
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_Client_FilterData_FilterForEventMatch(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif


#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_Client_FilterData_FilterMemoryByEvent
 *****************************************************************************/
/*!
 * \brief         Iterates events in the event memory matching the Dcm DTC filter.
 *
 * \details       This function iterates all events in order of their event ID.
 *                Events which have been reported before by the chronological
 *                iterator Dem_Dcm_FilterMemoryChrono will be ignored.
 *
 * \param[in]     FilterId
 *                The filter to be used.
 *
 * \return        EventId of the next event maching the filter criteria.
 *
 * \pre           A Dcm filter has been set.
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL FUNC(Dem_EventIdType, DEM_CODE)
Dem_Client_FilterData_FilterMemoryByEvent(
  Dem_FilterData_HandleType  FilterId
  );
#endif


#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_Client_FilterData_FilterPermanentByEvent
 *****************************************************************************/
/*!
 * \brief         Iterates events in permanent memory matching the Dcm DTC
 *                filter.
 *
 * \details       This function iterates all events in order of their event ID.
 *                Events which have been reported before by the chronological
 *                iterator will be ignored.
 *
 * \param[in]     FilterId
 *                The filter to be used.
 *
 * \return        EventId of the next event maching the filter criteria.
 *
 * \pre           A Dcm filter has been set.
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL FUNC(Dem_EventIdType, DEM_CODE)
Dem_Client_FilterData_FilterPermanentByEvent(
  Dem_FilterData_HandleType  FilterId
  );
#endif


#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_Client_FilterData_FilterMemoryChrono
 *****************************************************************************/
/*!
 * \brief         Iterates events in memory matching the Dcm DTC
 *                filter.
 *
 * \details       If chronological reporting is required this function iterates 
 *                all events in order of occurrence.
 *                If all stored events have been checked, this function
 *                replaces the iterator function by the non-chronological
 *                version Dem_Dcm_FilterMemoryByEvent to also find the
 *                remaining events.
 *                If chronological reporting is not required the function
 *                directly starts filtering events in configuration order.
 *
 * \param[in]     FilterId
 *                The filter to be used.
 *
 * \return        EventId of the next event maching the filter criteria.
 *
 * \pre           A Dcm filter has been set.
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL FUNC(Dem_EventIdType, DEM_CODE)
Dem_Client_FilterData_FilterMemoryChrono(
  Dem_FilterData_HandleType  FilterId
  );
#endif


#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_Client_FilterData_CountMatchesInPermanentMemory
 *****************************************************************************/
/*!
 * \brief         Calculates the number of filtered DTCs for permanent memory.
 *
 * \details       Calculates the number of filtered DTCs for permanent memory.
 *
 * \return        Number of DTCs matching the filter criteria.
 *
 * \pre           A Dcm filter has been set.
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Client_FilterData_CountMatchesInPermanentMemory(
  void
  );
#endif


#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_Client_FilterData_CountMatchesInEventMemory
 *****************************************************************************/
/*!
 * \brief         Calculates the number of filtered events in a standard event memory.
 *
 * \details       Calculates the number of filtered events in a standard event memory.
 *
 * \param[in]     FilterId
 *                The filter to be used.
 *
 * \return        Number of DTCs matching the filter criteria.
 *
 * \pre           A Dcm filter has been set.
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Client_FilterData_CountMatchesInEventMemory(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  );
#endif


#if ( (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON) || (DEM_CFG_SUPPORT_J1939_READINESS1 == STD_ON) )
/* ****************************************************************************
 * Dem_Client_FilterData_TestEventMatchesJ1939DTCFilter
 *****************************************************************************/
/*!
 * \brief         Checks if the passed EventId matches the J1939 DTC filter 
 *                criteria.
 *
 * \details       Checks if the passed EventId matches the J1939 DTC filter 
 *                criteria.
 *
 * \param[in]     DTCStatusFilterType
 *                DTC Status filter type
 * \param[in]     NodeId
 *                Node Id
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE
 *                The event matches the filter criteria
 * \return        FALSE
 *                The event does not match the filter criteria
 *
 * \pre           J1939 filter has been set
 * \config           DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON
 *                || DEM_CFG_SUPPORT_J1939_READINESS1 == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Client_FilterData_TestEventMatchesJ1939DTCFilter(
  CONST(Dem_J1939DcmDTCStatusFilterType, AUTOMATIC)  DTCStatusFilterType,
  CONST(uint8, AUTOMATIC)  NodeId,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif


/* ****************************************************************************
 * Dem_Client_FilterData_GetNumberOfFilteredDTCsByReadinessGroup
 *****************************************************************************/
/*!
 * \brief         Calculate number of DTCs of a certain readiness group
 *
 * \details       Calculate number of DTCs of a certain readiness group
 *
 * \param[in]     DTCFilterId
 *                The DTC filter handle.
 *
 * \pre           Feature Service 0x19 56 is enabled and DCM support is enabled
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Client_FilterData_GetNumberOfFilteredDTCsByReadinessGroup(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  DTCFilterId
);


/* ****************************************************************************
 * Dem_Client_FilterData_FilterDTCByReadinessGroup
 *****************************************************************************/
/*!
 * \brief         Iterates over events of a certain readiness group.
 *
 * \details       Iterates over events of a certain readiness group.
 *                The readiness group is specified in DTC Filter.
 *
 *
 * \param[in]     FilterId
 *                The filter to be used.
 *
 * \return        EventId of the next event maching the readiness group filter criteria.
 *
 * \pre           Feature Service 0x19 56 is enabled and DCM support is enabled
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE for different DTCFilterIds
 *****************************************************************************/
DEM_LOCAL FUNC(Dem_EventIdType, DEM_CODE)
Dem_Client_FilterData_FilterDTCByReadinessGroup(
  Dem_FilterData_HandleType  DTCFilterId
);

/* ****************************************************************************
 * Dem_Client_FilterData_GetNumberOfFilteredDTCsByERecNumber
 *****************************************************************************/
/*!
 * \brief         Calculate number of DTCs of a certain extended data record
 *
 * \details       Calculate number of DTCs of a certain extended data record
 *
 * \param[in]     DTCFilterId
 *                The DTC filter handle.
 *
 * \pre           Feature Service 0x19 1A is enabled and DCM support is enabled
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Client_FilterData_GetNumberOfFilteredDTCsByERecNumber(
  Dem_FilterData_HandleType DTCFilterId
);

/* ****************************************************************************
 * Dem_Client_FilterData_FilterDTCByERecNumber
 *****************************************************************************/
/*!
 * \brief         Iterates over events with a certain extended data record number.
 *
 * \details       Iterates over events with a certain extended data record number.
 *                The events which match the extended data record number are specified in DTC Filter.
 *
 *
 * \param[in]     DTCFilterId
 *                The filter to be used.
 *
 * \return        EventId of the next event maching the extended data record number filter criteria.
 *
 * \pre           Feature Service 0x19 1A is enabled and DCM support is enabled
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE for different DTCFilterIds
 *****************************************************************************/
DEM_LOCAL FUNC(Dem_EventIdType, DEM_CODE)
Dem_Client_FilterData_FilterDTCByERecNumber(
  Dem_FilterData_HandleType DTCFilterId
);


/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/


 /* ****************************************************************************
 % Dem_Client_FilterData_SetFilterData()
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Client_FilterData_SetFilterData(                                                                                                    /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId,
  CONST(Dem_Cfg_FilterData_InfoType, AUTOMATIC)  FilterData
)
{
#if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (FilterId >= Dem_Cfg_GetSizeOfFilterInfoTable())
  {
    Dem_Error_RunTimeCheckFailed(DEM_FILTERDATAIF_IMPLEMENTATION_FILENAME, __LINE__);                                              /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
#endif
  {
    Dem_Cfg_SetFilterInfoTable(FilterId, FilterData);                                                                            /* SBSW_DEM_ARRAY_WRITE_FILTERINFOTABLE */
  }
}

/* ****************************************************************************
% Dem_Client_FilterData_InitFilterFlagsAndMasks()
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
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Client_FilterData_InitFilterFlagsAndMasks(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId,
  CONST(uint8, AUTOMATIC)  StatusMask,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat,
  CONST(boolean, AUTOMATIC)  FilterForOBD,
  CONST(boolean, AUTOMATIC)  FilterWithSeverity,
  CONST(Dem_DTCSeverityType, AUTOMATIC)  SeverityMask,
  CONST(boolean, AUTOMATIC)  FilterForFDC
)
{
  Dem_Cfg_FilterInfoTablePtrType lFilterDataPtr;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DTCFormat)                                                                                    /* PRQA S 3112 */ /* MD_DEM_14.2 */

  lFilterDataPtr = Dem_Client_FilterData_GetFilterDataPtrSafe(FilterId);

  /* Check if filter shall ignore Dtc status or not */
  if (StatusMask == 0x00u)
  {
    lFilterDataPtr->FilterFlags = Dem_Client_FilterData_ResetUseStatusMask(lFilterDataPtr->FilterFlags);                                /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
  }
  else
  {                                                                                                                              
    lFilterDataPtr->StatusMask = StatusMask & Dem_Cfg_GlobalStatusMask();                                                        /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
    lFilterDataPtr->FilterFlags = Dem_Client_FilterData_SetUseStatusMask(lFilterDataPtr->FilterFlags);                                  /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
  }

  /* Check if filter shall use severity */
  if (FilterWithSeverity == TRUE)
  {
    lFilterDataPtr->SeverityMask = SeverityMask & Dem_Cfg_GlobalSeverityMask();                                                  /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
    lFilterDataPtr->FilterFlags = Dem_Client_FilterData_SetUseSeverity(lFilterDataPtr->FilterFlags);                                    /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
  }
  else
  {
    lFilterDataPtr->FilterFlags = Dem_Client_FilterData_ResetUseSeverity(lFilterDataPtr->FilterFlags);                                  /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
  }

  /* Check if filter shall use fault detection counter */
  if (FilterForFDC == TRUE)
  {
    lFilterDataPtr->FilterFlags = Dem_Client_FilterData_SetUseFdc(lFilterDataPtr->FilterFlags);                                         /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
  }
  else
  {
    lFilterDataPtr->FilterFlags = Dem_Client_FilterData_ResetUseFdc(lFilterDataPtr->FilterFlags);                                       /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
  }

  /* Check if filtering for emission relevant DTCs was requested */
  if (FilterForOBD == TRUE)
  {
    lFilterDataPtr->FilterFlags = Dem_Client_FilterData_SetFilterEmissionRelevant(lFilterDataPtr->FilterFlags);                         /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
  }
  else
  {
    lFilterDataPtr->FilterFlags = Dem_Client_FilterData_ResetFilterEmissionRelevant(lFilterDataPtr->FilterFlags);                       /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
  }

  /* Check if output format of DTCs shall be OBD */
  if (Dem_Cfg_IsObdIISupportedInVariant() == TRUE)
  {
    if (DTCFormat == DEM_DTC_FORMAT_OBD)
    {
      lFilterDataPtr->FilterFlags = Dem_Client_FilterData_SetUseFormatOBD(lFilterDataPtr->FilterFlags);                                 /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
    }
    else
    {
      lFilterDataPtr->FilterFlags = Dem_Client_FilterData_ResetUseFormatOBD(lFilterDataPtr->FilterFlags);                               /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
    }
  }
}                                                                                                                                /* PRQA S 6050, 6060 */ /* MD_MSR_STCAL, MD_MSR_STPAR */


/* ****************************************************************************
 % Dem_Client_FilterData_SetState
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Client_FilterData_SetState(                                                                                                         /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_FilterData_HandleType, AUTOMATIC) FilterId,
  CONST(Dem_FilterData_FilterType, AUTOMATIC) NewState
)
{
  Dem_Cfg_FilterInfoTablePtrType lFilterDataPtr;

  lFilterDataPtr = Dem_Client_FilterData_GetFilterDataPtrSafe(FilterId);
  lFilterDataPtr->FilterState = NewState;                                                                                        /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
}


/* ****************************************************************************
 % Dem_Client_FilterData_GetEventId()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Client_FilterData_GetEventId(                                                                                                       /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  )
{
  return Dem_Cfg_GetFilterInfoTable(FilterId).Iterator.EventIndex;
}

/* ****************************************************************************
 % Dem_Client_FilterData_GetChronoIter()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Client_FilterData_GetChronoIter(                                                                                                    /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  )
{
  return Dem_Cfg_GetFilterInfoTable(FilterId).Iterator.ChronoIter;
}

/* ****************************************************************************
 % Dem_Client_FilterData_GetStatusMask()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Client_FilterData_GetStatusMask(                                                                                                    /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  )
{
  return Dem_Cfg_GetFilterInfoTable(FilterId).StatusMask;
}

/* ****************************************************************************
 % Dem_Client_FilterData_GetFDC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(sint8, DEM_CODE)
Dem_Client_FilterData_GetFDC(                                                                                                           /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  )
{
  return Dem_Cfg_GetFilterInfoTable(FilterId).FaultDetectionCounter;
}

/* ****************************************************************************
 % Dem_Client_FilterData_GetMemoryId()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Client_FilterData_GetMemoryId(                                                                                                      /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  )
{
  return Dem_Cfg_GetFilterInfoTable(FilterId).MemoryId;
}

/* ****************************************************************************
 % Dem_Client_FilterData_GetSeverityMask()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTCSeverityType, DEM_CODE)
Dem_Client_FilterData_GetSeverityMask(                                                                                                  /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  )
{
  return Dem_Cfg_GetFilterInfoTable(FilterId).SeverityMask;
}

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Client_FilterData_GetDTCFilteringStrategy()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_FilterData_DTCFilteringStrategyType, DEM_CODE)
Dem_Client_FilterData_GetDTCFilteringStrategy(                                                                                          /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  )
{
  return Dem_Cfg_GetFilterInfoTable(FilterId).FilterDtcStrategy;
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Client_FilterData_GetDTCFilterFunction()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_FilterData_FuncPtrType, DEM_CODE)
Dem_Client_FilterData_GetDTCFilterFunction(                                                                                             /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_FilterData_DTCFilteringStrategyType, AUTOMATIC)  DTCFilteringStrategy
  )
{
  Dem_FilterData_FuncPtrType lDTCFilterFunction;

  switch (DTCFilteringStrategy)
  {
  case Dem_FilterData_FilterChronological:
    lDTCFilterFunction = Dem_Client_FilterData_FilterMemoryChrono;
    break;
  case Dem_FilterData_FilterEventBased:
    lDTCFilterFunction = Dem_Client_FilterData_FilterMemoryByEvent;
    break;
  case Dem_FilterData_FilterEventBased_PermanentMemory:
    lDTCFilterFunction = Dem_Client_FilterData_FilterPermanentByEvent;
    break;
  case Dem_FilterData_FilterEventBased_ReadinessGroup:
    lDTCFilterFunction = Dem_Client_FilterData_FilterDTCByReadinessGroup;
    break;
  case Dem_FilterData_FilterEventBased_ExtendendDataRecord:
    lDTCFilterFunction = Dem_Client_FilterData_FilterDTCByERecNumber;
    break;
  default:
    lDTCFilterFunction = Dem_Client_FilterData_FilterMemoryByEvent;
    break;
    
  }
  return lDTCFilterFunction;
}
#endif

/* ****************************************************************************
 % Dem_Client_FilterData_GetNodeId()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Client_FilterData_GetNodeId(                                                                                                        /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  )
{
  return Dem_Cfg_GetFilterInfoTable(FilterId).NodeId;
}

/* ****************************************************************************
 % Dem_Client_FilterData_GetDTCStatusFilterType()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_J1939DcmDTCStatusFilterType, DEM_CODE)
Dem_Client_FilterData_GetDTCStatusFilterType(                                                                                           /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  )
{                                                                                                                                
  return Dem_Cfg_GetFilterInfoTable(FilterId).DTCStatusFilterType;
}



/* ****************************************************************************
 % Dem_Client_FilterData_SetFDC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Client_FilterData_SetFDC(                                                                                                           /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId,
  CONST(sint8, AUTOMATIC)  FDC
  )
{
  Dem_Cfg_FilterInfoTablePtrType lFilterDataPtr;

  lFilterDataPtr = Dem_Client_FilterData_GetFilterDataPtrSafe(FilterId);
  lFilterDataPtr->FaultDetectionCounter = FDC;                                                                                   /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
}

/* ****************************************************************************
 % Dem_Client_FilterData_SetUseStatusMask()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Client_FilterData_SetUseStatusMask(                                                                                                 /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  FilterFlags
  )
{
  return (uint8) (FilterFlags | DEM_FILTERDATA_FILTERFLAGS_USESTATUSMASK);
}

/* ****************************************************************************
 % Dem_Client_FilterData_ResetUseStatusMask()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Client_FilterData_ResetUseStatusMask(                                                                                               /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  FilterFlags
  )
{
  return (uint8) (FilterFlags & DEM_FILTERDATA_FILTERFLAGS_USESTATUSMASK_MASK);
}

/* ****************************************************************************
 % Dem_Client_FilterData_SetUseFdc()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Client_FilterData_SetUseFdc(                                                                                                        /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  FilterFlags
  )
{
  return (uint8) (FilterFlags | DEM_FILTERDATA_FILTERFLAGS_USEFDC);
}

/* ****************************************************************************
 % Dem_Client_FilterData_ResetUseFdc()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Client_FilterData_ResetUseFdc(                                                                                                      /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  FilterFlags
  )
{
  return (uint8) (FilterFlags & DEM_FILTERDATA_FILTERFLAGS_USEFDC_MASK);
}

/* ****************************************************************************
 % Dem_Client_FilterData_SetUseSeverity()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Client_FilterData_SetUseSeverity(                                                                                                   /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  FilterFlags
  )
{
  return (uint8) (FilterFlags | DEM_FILTERDATA_FILTERFLAGS_USESEVERITY);
}

/* ****************************************************************************
 % Dem_Client_FilterData_ResetUseSeverity()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Client_FilterData_ResetUseSeverity(                                                                                                 /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  FilterFlags
  )
{
  return (uint8) (FilterFlags & DEM_FILTERDATA_FILTERFLAGS_USESEVERITY_MASK);
}

/* ****************************************************************************
 % Dem_Client_FilterData_SetUseFormatOBD()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Client_FilterData_SetUseFormatOBD(                                                                                                  /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  FilterFlags
  )
{
  return (uint8) (FilterFlags | DEM_FILTERDATA_FILTERFLAGS_USEFORMATOBD);
}

/* ****************************************************************************
 % Dem_Client_FilterData_ResetUseFormatOBD()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Client_FilterData_ResetUseFormatOBD(                                                                                                /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  FilterFlags
  )
{
  return (uint8) (FilterFlags & DEM_FILTERDATA_FILTERFLAGS_USEFORMATOBD_MASK);
}

/* ****************************************************************************
 % Dem_Client_FilterData_SetFilterEmissionRelevant()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Client_FilterData_SetFilterEmissionRelevant(                                                                                        /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  FilterFlags
  )
{
  return (uint8) (FilterFlags | DEM_FILTERDATA_FILTERFLAGS_FILTEREMISSIONRELEVANT);
}

/* ****************************************************************************
 % Dem_Client_FilterData_ResetFilterEmissionRelevant()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Client_FilterData_ResetFilterEmissionRelevant(                                                                                      /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  FilterFlags
  )
{
  return (uint8) (FilterFlags & DEM_FILTERDATA_FILTERFLAGS_FILTEREMISSIONRELEVANT_MASK);
}

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Client_FilterData_ResetReportedEvents()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Client_FilterData_ResetReportedEvents(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  )
{
#if (DEM_FEATURE_NEED_REPORT_CHRONOLOGICALLY == STD_ON)
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (FilterId >= Dem_Cfg_GetSizeOfReportedEventsOfFilter())
  {
    Dem_Error_RunTimeCheckFailed(DEM_FILTERDATAIF_IMPLEMENTATION_FILENAME, __LINE__);                                              /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    uint16_least lBitfieldIterator;
    for (lBitfieldIterator = 0u;
         lBitfieldIterator < DEM_BITFIELDS_IN_REPORTEDEVENTBUFFER;
         lBitfieldIterator++)
    {
      (Dem_Cfg_GetReportedEventsOfFilter(FilterId))[lBitfieldIterator] = 0u;                                                     /* SBSW_DEM_ARRAY_WRITE_REPORTEDEVENTSOFFILTER */
    }
  }
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(FilterId)                                                                                     /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Client_FilterData_SetEventReported()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Client_FilterData_SetEventReported(                                                                                                 /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId,
  CONST(Dem_EventIdType, AUTOMATIC) EventId
  )
{
#if (DEM_FEATURE_NEED_REPORT_CHRONOLOGICALLY == STD_ON)
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (FilterId >= Dem_Cfg_GetSizeOfReportedEventsOfFilter())
  {
    Dem_Error_RunTimeCheckFailed(DEM_FILTERDATAIF_IMPLEMENTATION_FILENAME, __LINE__);                                              /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    /* identified an Event which matches the filter criteria, mark event as reported */
    Dem_Com_SetBitInBitfield(Dem_Cfg_GetReportedEventsOfFilter(FilterId),                                                        /* SBSW_DEM_POINTER_FORWARD_REPORTED_EVENTS_OF_FILTER */
                             DEM_BITFIELDS_IN_REPORTEDEVENTBUFFER, 
                             EventId);
  }
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(FilterId)                                                                                     /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Client_FilterData_TestEventReported()
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
Dem_Client_FilterData_TestEventReported(                                                                                                /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId,
  CONST(Dem_EventIdType, AUTOMATIC) EventId
  )
{
  boolean lEventReported;
  lEventReported = FALSE;

#if (DEM_FEATURE_NEED_REPORT_CHRONOLOGICALLY == STD_ON)
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  /* Per Design only valid pointer are forwarded to other function in safety context, */
  /* even if pointer is not used for write operation */
  if (FilterId >= Dem_Cfg_GetSizeOfReportedEventsOfFilter())
  {
    Dem_Error_RunTimeCheckFailed(DEM_FILTERDATAIF_IMPLEMENTATION_FILENAME, __LINE__);                                              /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else  
# endif
  {
    /* Check whether bit in the corresponding bit field is set */
    lEventReported = Dem_Com_TestBitInBitfield(Dem_Cfg_GetReportedEventsOfFilter(FilterId),                                      /* SBSW_DEM_POINTER_FORWARD_REPORTED_EVENTS_OF_FILTER */                                                
                                               DEM_BITFIELDS_IN_REPORTEDEVENTBUFFER,
                                               EventId);
  }
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(FilterId)                                                                                     /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif

  return lEventReported;
}
#endif


#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Client_FilterData_InitDTCFilter()
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
Dem_Client_FilterData_InitDTCFilter(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId,
  CONST(uint8, AUTOMATIC)  MemoryId,
  CONST(uint8, AUTOMATIC)  StatusMask
  )
{
  Std_ReturnType lReturnValue;
  Dem_Cfg_FilterInfoTablePtrType lFilterDataPtr;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(StatusMask)                                                                                   /* PRQA S 3112 */ /* MD_DEM_14.2 */

  lFilterDataPtr = Dem_Client_FilterData_GetFilterDataPtrSafe(FilterId);

  switch (MemoryId)
  {
  case DEM_CFG_MEMORYID_PRIMARY:
    lFilterDataPtr->MemoryId = MemoryId;                                                                                         /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
    if ( (StatusMask == 0x04u) || (StatusMask == 0x08u) || (StatusMask == 0x0Cu) )
    { /* reporting shall be in chronological order */
      lFilterDataPtr->Iterator.ChronoIter = DEM_FILTERDATA_FILTER_INIT;                                                          /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
      lFilterDataPtr->FilterDtcStrategy = Dem_FilterData_FilterChronological;                                                    /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
    }
    else
    { /* report by event id, set first event index */
      lFilterDataPtr->Iterator.EventIndex = Dem_Cfg_GlobalPrimaryFirst();                                                        /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
      lFilterDataPtr->FilterDtcStrategy = Dem_FilterData_FilterEventBased;                                                       /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
    }
    lReturnValue = E_OK;
    break;

#if (DEM_CFG_SUPPORT_SECONDARY == STD_ON)
  case DEM_CFG_MEMORYID_SECONDARY:
    lFilterDataPtr->MemoryId = MemoryId;                                                                                         /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
    if ( (StatusMask == 0x04u) || (StatusMask == 0x08u) || (StatusMask == 0x0Cu) )
    { /* reporting shall be in chronological order */
      lFilterDataPtr->Iterator.ChronoIter = DEM_FILTERDATA_FILTER_INIT;                                                          /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
      lFilterDataPtr->FilterDtcStrategy = Dem_FilterData_FilterChronological;                                                    /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
    }
    else
    { /* report by event id, set first event index */
      lFilterDataPtr->Iterator.EventIndex = Dem_Cfg_GlobalSecondaryFirst();                                                      /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
      lFilterDataPtr->FilterDtcStrategy = Dem_FilterData_FilterEventBased;                                                       /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
    }
    lReturnValue = E_OK;
    break;
#endif

  case DEM_CFG_MEMORYID_PERMANENT:
    if (Dem_Cfg_IsPermanentSupportedInVariant() == TRUE)
    {
      lFilterDataPtr->MemoryId = MemoryId;                                                                                       /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
      /* report by event id, set max number of permanent memory entries */
      lFilterDataPtr->Iterator.PermanentIndex = Dem_Cfg_GlobalPermanentMaxCount();                                               /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
      lFilterDataPtr->FilterDtcStrategy = Dem_FilterData_FilterEventBased_PermanentMemory;                                       /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
      lReturnValue = E_OK;
    }
    else
    {
      lReturnValue = E_NOT_OK;
    }
    break;

  default:
    lReturnValue = E_NOT_OK;
    break;
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Client_FilterData_FilterForEventMatch
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
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_Client_FilterData_FilterForEventMatch(                                                                                              /* PRQA S 2889 */ /* MD_DEM_15.5 */
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  uint8    lEventStatus;

  if (Dem_Cfg_EventUdsDtc(EventId) == DEM_CFG_DTC_UDS_INVALID)
  {
    return E_NOT_OK;
  }
  if (EventId != Dem_Cfg_GetMasterEvent(EventId))
  {
    return E_NOT_OK;
  }

# if (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
  if ( (Dem_DTC_TestSuppressionOnDtcRetrieval(EventId) == TRUE)
# else
  if ( (Dem_DTC_TestDtcAvailableInVariant(EventId) == FALSE)
    || ((Dem_DTC_TestDtcAvailable(EventId) == FALSE)                                                                             
      && (Dem_DTC_TestStoredStatus(EventId) == FALSE))                                                                           /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
# endif
    || ( (Dem_DTC_TestDtcSuppression(EventId) == TRUE)                                                                           /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
# if (DEM_CFG_REPORT_SUPPRESSED_DTCS_IN_19_0A == STD_ON)
      && ((Dem_Client_FilterData_TestUseStatusMask(FilterId) == TRUE)                                                                   /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
        || (Dem_Client_FilterData_GetMemoryId(FilterId) != DEM_CFG_MEMORYID_PRIMARY))                                                   /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
# endif
       ))
  {
    /* Suppressed DTCs are skipped */
    return E_NOT_OK;
  }

  if ( (Dem_Client_FilterData_TestUseFormatOBD(FilterId) == TRUE)
    || (Dem_Client_FilterData_TestFilterEmissionRelevant(FilterId) == TRUE))                                                            /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
  {
    /* Filter specifically for OBD DTCs */
    if (Dem_Cfg_EventObdRelated(EventId) == FALSE)
    { 
      /* skip non-OBD DTCs */
      return E_NOT_OK;
    }
  }
  else
  { 
    /* Do not filter for OBD DTCs, all DTCs pass */
    if ( (Dem_Cfg_EventObdRelated(EventId) == TRUE)
      && (Dem_Cfg_EventSignificance(EventId) == DEM_CFG_EVENT_SIGNIFICANCE_OCCURRENCE)
      && (Dem_DTCReporting_TestObdHideOccurrences() == TRUE))
    { 
      /* Special case - skip Dependent OBD DTCs */
      return E_NOT_OK;
    }
  }

  lEventStatus = Dem_DTC_GenerateExternalOnlyStatus(EventId, Dem_DTC_GetDTCStatus(EventId));

  if ( (Dem_Client_FilterData_TestUseStatusMask(FilterId) == TRUE)
    && ((Dem_Client_FilterData_GetStatusMask(FilterId) & lEventStatus) == 0u))                                                          /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
  {
    /* Skip DTCs not matching the requested status mask */
    return E_NOT_OK;
  }

  if ( (Dem_Client_FilterData_TestUseSeverity(FilterId) == TRUE)
    && ((Dem_Client_FilterData_GetSeverityMask(FilterId) & Dem_Cfg_EventSeverity(EventId)) == 0u))                                      /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
  { /* Skip DTCs not matching the requested severity */
    return E_NOT_OK;
  }

  if (Dem_Client_FilterData_TestUseFdc(FilterId) == TRUE)
  {
    Std_ReturnType lGetFdcReturnValue;
    sint8 lFdc;

    lGetFdcReturnValue = Dem_DTC_GetFaultDetectionCounter(EventId, &lFdc);                                                       /* SBSW_DEM_POINTER_FORWARD_STACK */

    if (lGetFdcReturnValue != E_OK)
    { /* If FDC cannot be retrieved, the DTC does not match */
      return E_NOT_OK;
    }

    if ( (lFdc <= 0)
      || (lFdc == 0x7f))
    { /* skip passed, passing and qualified failed DTCs */
      return E_NOT_OK;
    }
    else
    {
      /* store the matching FDC for later */
      Dem_Client_FilterData_SetFDC(FilterId, lFdc);
    }
  }

  /* If all tests pass, keep this DTC for processing */
  return E_OK;
}                                                                                                                                /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON) 
/* ****************************************************************************
 % Dem_Client_FilterData_FilterMemoryByEvent
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
DEM_LOCAL FUNC(Dem_EventIdType, DEM_CODE)
Dem_Client_FilterData_FilterMemoryByEvent(
  Dem_FilterData_HandleType FilterId
  )
{
  Dem_EventIdType lEventId;
  Dem_EventIdType lReturnValue;

  lEventId = Dem_Client_FilterData_GetEventId(FilterId);
  lReturnValue = DEM_EVENT_INVALID;

  /* if last EventId is not valid or was still analyzed skip the filtering */
  if (lEventId != DEM_EVENT_INVALID)
  {
    Dem_Cfg_FilterInfoTablePtrType lFilterDataPtr;
    Dem_EventIdType lEventIdLast;

    lEventIdLast = Dem_Memory_GetLastEvent(Dem_Client_FilterData_GetMemoryId(FilterId));
    /* iterate through the EventIds and check filter criteria */
    for (; lEventId <= lEventIdLast; lEventId++)
    {
# if (DEM_FEATURE_NEED_REPORT_CHRONOLOGICALLY == STD_ON)
      /* take event into account if it was not reported before */
      if (Dem_Client_FilterData_TestEventReported(FilterId, Dem_Cfg_GetMasterEvent(lEventId)) == FALSE)
# endif
      {
        /* EventId was not reported before, proceed */
        if (Dem_Client_FilterData_FilterForEventMatch(FilterId, lEventId) == E_OK)
        {
          /* identified an Event which matches the filter criteria */
          lReturnValue = lEventId;
          break;
        }
      }
    }

    lFilterDataPtr = Dem_Client_FilterData_GetFilterDataPtrSafe(FilterId);

    if (lEventId >= lEventIdLast)
    { /* last EventId has been processed */
      lFilterDataPtr->Iterator.EventIndex = DEM_EVENT_INVALID;                                                                   /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
    }
    else
    { /* write back the next event to process */
      lFilterDataPtr->Iterator.EventIndex = (Dem_EventIdType)(lEventId + 1u);                                                    /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
    }
  }
  /* else lReturnValue = DEM_EVENT_INVALID initially set */

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Client_FilterData_FilterPermanentByEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(Dem_EventIdType, DEM_CODE)
Dem_Client_FilterData_FilterPermanentByEvent(
  Dem_FilterData_HandleType FilterId
  )
{
  Dem_EventIdType lPermanentEventId;

  lPermanentEventId = DEM_EVENT_INVALID;

#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
  if (Dem_Cfg_IsPermanentSupportedInVariant() == TRUE)
  {
    Dem_Cfg_FilterInfoTablePtrType lFilterDataPtr;
    uint8 lPermanentIndex;

    lFilterDataPtr = Dem_Client_FilterData_GetFilterDataPtrSafe(FilterId);
    lPermanentIndex = lFilterDataPtr->Iterator.PermanentIndex;                                                                   /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */

    /* if last EventId is not valid or was still analysed skip the filtering */
    while (lPermanentIndex != 0u)
    {
      --lPermanentIndex;

      if (DEM_ESM_TEST_PERMANENT_VISIBLE(Dem_Mem_PermanentGetStatus(lPermanentIndex)) == TRUE)
      { /* Visible Event identified, return it and stop processing */
        lPermanentEventId = Dem_Mem_PermanentGetEvent(lPermanentIndex);
        if (lPermanentEventId != DEM_EVENT_INVALID)
        {
          if ( (Dem_DTC_TestEventStoresPermanentDTC(lPermanentEventId) == TRUE) 
            && (Dem_DTC_TestSuppressionOnDtcRetrieval(lPermanentEventId) == FALSE))                                              /* PRQA S 3415 */ /* MD_DEM_13.5_volatile */
          {
            break;
          }
          else
          {
            /*Invalidate return value for this entry*/
            lPermanentEventId = DEM_EVENT_INVALID;
          }
        }
      }
    }

    /* store current position in permanent memory */
    lFilterDataPtr->Iterator.PermanentIndex = lPermanentIndex;                                                                   /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
  }

#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(FilterId)                                                                                     /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
  return lPermanentEventId;
}                                                                                                                                /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Client_FilterData_FilterMemoryChrono
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
 */
DEM_LOCAL FUNC(Dem_EventIdType, DEM_CODE)
Dem_Client_FilterData_FilterMemoryChrono(
  Dem_FilterData_HandleType  FilterId
  )
{
  Dem_EventIdType lEventId;
  Dem_Cfg_FilterInfoTablePtrType lFilterDataPtr;

# if (DEM_FEATURE_NEED_REPORT_CHRONOLOGICALLY == STD_ON)
  uint8 lMemoryId;
  Dem_Cfg_MemoryIndexType lStoredChronoIter;
  Dem_Memory_AllocMemEntriesIterType lStoredEventsIter;

  lStoredChronoIter = Dem_Client_FilterData_GetChronoIter(FilterId);
  lEventId = DEM_EVENT_INVALID;
  lMemoryId = Dem_Client_FilterData_GetMemoryId(FilterId);
    
  if (lStoredChronoIter == DEM_FILTERDATA_FILTER_INIT)
  {
    /* index set to 0 indicates that the filter was reset */
    Dem_Memory_AllocMemEntriesChrono_IterInit(lMemoryId, &lStoredEventsIter);                                                    /* SBSW_DEM_CALL_ITERATOR_POINTER */
  }
  else
  {
    /* last stored index loaded, set and increment it*/
    Dem_Memory_AllocMemEntriesChrono_IterResume(lMemoryId, lStoredChronoIter, &lStoredEventsIter);                               /* SBSW_DEM_CALL_ITERATOR_POINTER */
  }

  for (; Dem_Memory_AllocMemEntriesChrono_IterExists(&lStoredEventsIter) == TRUE;                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
        Dem_Memory_AllocMemEntriesChrono_IterNext(&lStoredEventsIter))                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    /* Get EventId for current index and marker if event was reported before */
    lEventId = 
        Dem_MemoryEntry_GetEventId(Dem_MemoryEntry_GetId(
        Dem_Memory_AllocMemEntriesChrono_IterGetMemoryIndex(&lStoredEventsIter)));                                               /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    /* verify that a valid EventId was returned */
    if (Dem_Event_TestValidHandle(lEventId) == TRUE)
    {
      /* EventId was not reported before, proceed */
# if ((DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
      /* Verify that combined event group of type 2 was not reported previously */
      if (Dem_Client_FilterData_TestEventReported(FilterId, Dem_Cfg_GetMasterEvent(lEventId)) == FALSE)
      {
        if(Dem_Client_FilterData_FilterForEventMatch(FilterId, Dem_Cfg_GetMasterEvent(lEventId)) == E_OK)
        {
          /* identified an Event which matches the filter criteria, mark event as reported */
          Dem_Client_FilterData_SetEventReported(FilterId, Dem_Cfg_GetMasterEvent(lEventId));
          break;
        }
        else
        { /* No filter match, continue with loop */
          lEventId = DEM_EVENT_INVALID;
        }
      }
# else
      if (Dem_Client_FilterData_FilterForEventMatch(FilterId, lEventId) == E_OK)
      {
        /* identified an Event which matches the filter criteria, mark event as reported */
        Dem_Client_FilterData_SetEventReported(FilterId, lEventId);
        break;
      }
# endif        
      else
      { /* No filter match, continue with loop */
        lEventId = DEM_EVENT_INVALID;
      }
    }
  }
  Dem_Memory_AllocMemEntriesChrono_IterNext(&lStoredEventsIter);                                                                 /* SBSW_DEM_CALL_ITERATOR_POINTER */
  lFilterDataPtr = Dem_Client_FilterData_GetFilterDataPtrSafe(FilterId);
  /* If end of chrono stack is reached, switch to filter by event id */
  if (Dem_Memory_AllocMemEntriesChrono_IterExists(&lStoredEventsIter) == FALSE)                                                  /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    lFilterDataPtr->Iterator.EventIndex = Dem_Memory_GetFirstEvent(lMemoryId);                                                   /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
    lFilterDataPtr->FilterDtcStrategy = Dem_FilterData_FilterEventBased;                                                         /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */

    if (lEventId == DEM_EVENT_INVALID)
    { /* no valid match, proceed with filtering by EventId */
      lEventId = Dem_Client_FilterData_FilterMemoryByEvent(FilterId);
    }
  }
  else
  {
    /* store current position of chrono stack */
    lFilterDataPtr->Iterator.ChronoIter = Dem_Memory_AllocMemEntriesChrono_IterGet(&lStoredEventsIter);                          /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */ /* SBSW_DEM_CALL_ITERATOR_POINTER */
  }
# else
  lFilterDataPtr = Dem_Client_FilterData_GetFilterDataPtrSafe(FilterId);

  lFilterDataPtr->Iterator.EventIndex = Dem_Memory_GetFirstEvent(Dem_Client_FilterData_GetMemoryId(FilterId));                          /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
  lFilterDataPtr->FilterDtcStrategy = Dem_FilterData_FilterEventBased;                                                           /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
  lEventId = Dem_Client_FilterData_FilterMemoryByEvent(FilterId);
# endif

  return lEventId;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Client_FilterData_CountMatchesInPermanentMemory
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Client_FilterData_CountMatchesInPermanentMemory(
  void
  )
{
  uint16 lNumberOfEvents;

  lNumberOfEvents = 0u;

# if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
  if (Dem_Cfg_IsPermanentSupportedInVariant() == TRUE)
  {
    uint8 lPermanentIndex;
    lPermanentIndex = Dem_Cfg_GlobalPermanentMaxCount();

    /* scan the permanent memory for visible events */
    while (lPermanentIndex != 0u)
    {
      --lPermanentIndex;
      if (DEM_ESM_TEST_PERMANENT_VISIBLE(Dem_Mem_PermanentGetStatus(lPermanentIndex)) == TRUE)
      {
        if ( (Dem_Mem_PermanentGetEvent(lPermanentIndex) != DEM_EVENT_INVALID)
          && (Dem_DTC_TestEventStoresPermanentDTC(Dem_Mem_PermanentGetEvent(lPermanentIndex)) == TRUE)                           /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
          && (Dem_DTC_TestSuppressionOnDtcRetrieval(Dem_Mem_PermanentGetEvent(lPermanentIndex)) == FALSE) )                      /* PRQA S 3415 */ /* MD_DEM_13.5_cf */ 
        {
          ++lNumberOfEvents;
        }
      }
    }
  }
# endif

  return lNumberOfEvents;
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Client_FilterData_CountMatchesInEventMemory
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
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Client_FilterData_CountMatchesInEventMemory(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  )
{
  uint16 lNumberOfEvents;
  Dem_EventIdType lEventId;
  uint8 lMemoryId;

  lNumberOfEvents = 0u;
  lMemoryId = Dem_Client_FilterData_GetMemoryId(FilterId);

  if (Dem_Memory_GetFirstEvent(lMemoryId) != DEM_EVENT_INVALID)
  {
    /* at least one event is available which may match the filter criteria */
    for (lEventId = Dem_Memory_GetFirstEvent(lMemoryId);
          lEventId <= Dem_Memory_GetLastEvent(lMemoryId);
          ++lEventId)
    {
      if (Dem_Client_FilterData_FilterForEventMatch(FilterId, lEventId) == E_OK)
      {
        ++lNumberOfEvents;
      }
    }
  }
  return lNumberOfEvents;
}
#endif

#if ( (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON) || (DEM_CFG_SUPPORT_J1939_READINESS1 == STD_ON) )
/* ****************************************************************************
 % Dem_Client_FilterData_TestEventMatchesJ1939DTCFilter
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
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Client_FilterData_TestEventMatchesJ1939DTCFilter(
  CONST(Dem_J1939DcmDTCStatusFilterType, AUTOMATIC)  DTCStatusFilterType,
  CONST(uint8, AUTOMATIC)  NodeId,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  boolean lEventMatch;
  lEventMatch = FALSE;

  /* Does the event support a J1939Dtc */
  if (Dem_Cfg_EventJ1939Dtc(EventId) != DEM_CFG_DTC_J1939_INVALID)
  {
# if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
    /* don't match dependent combined events */
    if (Dem_Cfg_GetMasterEvent(EventId) == EventId)
# endif
    {
      if (Dem_DTC_TestSuppressionOnDtcRetrieval(EventId) == FALSE)
      {
        uint8 lEventStatus;
        Dem_Cfg_EventJ1939NodeIterType lNodeIter;

        /* filter event only if it is linked to the requested node */
        for (Dem_Cfg_EventJ1939NodeIterInit(EventId, &lNodeIter);                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
             Dem_Cfg_EventJ1939NodeIterExists(&lNodeIter) == TRUE;                                                               /* SBSW_DEM_CALL_ITERATOR_POINTER */
             Dem_Cfg_EventJ1939NodeIterNext(&lNodeIter))                                                                         /* SBSW_DEM_CALL_ITERATOR_POINTER */
        {
          if (NodeId == Dem_Cfg_EventJ1939NodeIterGet(&lNodeIter))                                                               /* SBSW_DEM_CALL_ITERATOR_POINTER */
          {
            break;
          }
        }
        if (Dem_Cfg_EventJ1939NodeIterExists(&lNodeIter) == TRUE)                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
        {
          lEventStatus = Dem_DTC_GenerateExternalOnlyStatus(EventId, Dem_DTC_GetDTCStatus(EventId));

          switch (DTCStatusFilterType)
          {
          case DEM_FILTERDATA_J1939FILTER_ACTIVE:
            if (Dem_DTC_TestDtcActive(EventId) == TRUE)
            {
              lEventMatch = TRUE;
            }
            break;

          case DEM_FILTERDATA_J1939FILTER_PREVIOUSLY_ACTIVE:
            if (Dem_DTC_TestDtcPreviouslyActive(EventId) == TRUE)
            {
              lEventMatch = TRUE;
            }
            break;

          case DEM_FILTERDATA_J1939FILTER_PENDING:
            if (Dem_UDSStatus_Test_PDTC(lEventStatus) == TRUE)
            {
              lEventMatch = TRUE;
            }
            break;

          case DEM_FILTERDATA_J1939FILTER_CURRENTLY_ACTIVE:
            if (Dem_UDSStatus_Test_TF(lEventStatus) == TRUE)
            {
              lEventMatch = TRUE;
            }
            break;

          default:                                                                                                               /* PRQA S 2016 */ /* MD_MSR_EmptyClause */
            /* lEventMatch == FALSE already set */
            break;
          }
        }
      }
    }
  }

  return lEventMatch;
}                                                                                                                                /* PRQA S 6030, 6050, 6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
#endif /* (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON) || (DEM_CFG_SUPPORT_J1939_READINESS1 == STD_ON) */


/* ****************************************************************************
 % Dem_Client_FilterData_GetNumberOfFilteredDTCsByReadinessGroup
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Client_FilterData_GetNumberOfFilteredDTCsByReadinessGroup(                                                                          /* PRQA S 3219 */ /* MD_DEM_14.1_CONFIGURATION_SWITCH */
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  DTCFilterId
)
{
  uint8 lReadinessGroupIdx;
  lReadinessGroupIdx = Dem_Client_FilterData_GetFilterDataPtrSafe(DTCFilterId)->TableIndex.ReadinessGroupIdx;                           /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
  return Dem_FilterData_0x1956_GetNumberOfFilteredDTCsByReadinessGroup(lReadinessGroupIdx);
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_Client_FilterData_FilterDTCByReadinessGroup
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(Dem_EventIdType, DEM_CODE)
Dem_Client_FilterData_FilterDTCByReadinessGroup(                                                                                        /* PRQA S 3219 */ /* MD_DEM_14.1_CONFIGURATION_SWITCH */
  Dem_FilterData_HandleType  DTCFilterId
)
{
  Dem_EventIdType lReturnEventIdValue;
  Dem_Cfg_FilterInfoTablePtrType lDTCFilterTemp;
  lDTCFilterTemp = Dem_Client_FilterData_GetFilterDataPtrSafe(DTCFilterId);

  lReturnEventIdValue = Dem_FilterData_0x1956_FilterDTCByReadinessGroup(lDTCFilterTemp);                                        /* SBSW_DEM_POINTER_FORWARD_STACK */

  return lReturnEventIdValue;
}

/* ****************************************************************************
 % Dem_Client_FilterData_GetNumberOfFilteredDTCsByERecNumber
*****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Client_FilterData_GetNumberOfFilteredDTCsByERecNumber(                                                                              /* PRQA S 3219 */ /* MD_DEM_14.1_CONFIGURATION_SWITCH */
  Dem_FilterData_HandleType DTCFilterId
)
{
  Dem_Cfg_ERecIndexType lDataCollectionTableIdx;
  lDataCollectionTableIdx = Dem_Client_FilterData_GetFilterDataPtrSafe(DTCFilterId)->TableIndex.DataCollectionTableIdx;                 /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
  return Dem_Dcm_ERec_0x191A_GetNumberOfFilteredDTCsByERecNumber(lDataCollectionTableIdx);
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_Client_FilterData_FilterDTCByERecNumber
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(Dem_EventIdType, DEM_CODE)
Dem_Client_FilterData_FilterDTCByERecNumber(                                                                                            /* PRQA S 3219 */ /* MD_DEM_14.1_CONFIGURATION_SWITCH */
  Dem_FilterData_HandleType  DTCFilterId
)
{
  Dem_EventIdType lReturnEventIdValue;
  Dem_Cfg_FilterInfoTablePtrType lDTCFilterTemp;
  lDTCFilterTemp = Dem_Client_FilterData_GetFilterDataPtrSafe(DTCFilterId);

  lReturnEventIdValue = Dem_Dcm_ERec_0x191A_FilterDTCByERecNumber(lDTCFilterTemp);                                               /* SBSW_DEM_POINTER_FORWARD_STACK */

  return lReturnEventIdValue;
}

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
 * \addtogroup Dem_FilterData_Public
 * \{
 */

#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) || (DEM_CFG_SUPPORT_J1939_DM31 == STD_ON) || (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON) )
 /* ****************************************************************************
 % Dem_Client_FilterData_InitDefault()
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
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Client_FilterData_InitDefault(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
)
{
  Dem_Cfg_FilterData_InfoType lFilterData;
  lFilterData = Dem_Client_FilterData_GetFilterData(FilterId);

  lFilterData.FilterState = DEM_FILTERDATA_FILTER_INIT;
  lFilterData.MemoryId = DEM_CFG_MEMORYID_INVALID;
  lFilterData.Iterator.EventIndex = DEM_EVENT_INVALID;
# if (DEM_CFG_SUPPORT_DCM == STD_ON)
  lFilterData.StatusMask = 0x00u;
  lFilterData.SeverityMask = DEM_SEVERITY_NO_SEVERITY;
  lFilterData.FaultDetectionCounter = 0x00;
  lFilterData.FilterDtcStrategy = Dem_FilterData_FilterEventBased;
# endif
# if ( (DEM_CFG_SUPPORT_J1939_DM31 == STD_ON) || (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON) )
  lFilterData.NodeId = DEM_CFG_J1939_NODE_INVALID;
  lFilterData.DTCStatusFilterType = 0u;
  lFilterData.NumberOfDTCsTested = 0u;
# endif
# if (DEM_CFG_SUPPORT_SVC19_56 == STD_ON)
  lFilterData.TableIndex.ReadinessGroupIdx = 0u;
  Dem_Client_FilterData_InitCombinedGroupProcessed(&lFilterData);                                                                       /* SBSW_DEM_POINTER_FORWARD_STACK */
# endif


  Dem_Client_FilterData_SetFilterData(FilterId, lFilterData);
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

/* ****************************************************************************
 % Dem_Client_FilterData_GetFilterDataPtrSafe()
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_FilterInfoTablePtrType, DEM_CODE)
Dem_Client_FilterData_GetFilterDataPtrSafe(                                                                                             /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
)
{
  Dem_Cfg_FilterInfoTablePtrType lResult;
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (FilterId >= Dem_Cfg_GetSizeOfFilterInfoTable())
  {
    Dem_Error_RunTimeCheckFailed(DEM_FILTERDATAIF_IMPLEMENTATION_FILENAME, __LINE__);                                              /* SBSW_DEM_POINTER_RUNTIME_CHECK */
    lResult = &Dem_Cfg_GetFilterInfoTable(0);
  }
  else
# endif
  {
    lResult = &Dem_Cfg_GetFilterInfoTable(FilterId);
  }

  return lResult;
}

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Client_FilterData_SetDTCFilter()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Client_FilterData_SetDTCFilter(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId,
  CONST(uint8, AUTOMATIC)  DTCStatusMask,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat,
  CONST(uint8, AUTOMATIC)  MemoryId,
  CONST(boolean, AUTOMATIC)  FilterForOBD,
  CONST(boolean, AUTOMATIC)  FilterWithSeverity,
  CONST(Dem_DTCSeverityType, AUTOMATIC)  DTCSeverityMask,
  CONST(boolean, AUTOMATIC)  FilterForFDC
  )
{
  Std_ReturnType lReturnValue;

  lReturnValue = Dem_Client_FilterData_InitDTCFilter(FilterId, MemoryId, DTCStatusMask);

  if (lReturnValue == E_OK)
  {
    /* Clear list of identified and reported events */
    Dem_Client_FilterData_ResetReportedEvents(FilterId);

    Dem_Client_FilterData_SetState(FilterId, DEM_FILTERDATA_FILTER_DTC);
    Dem_Client_FilterData_InitFilterFlagsAndMasks(FilterId,
                                           DTCStatusMask,
                                           DTCFormat,
                                           FilterForOBD,
                                           FilterWithSeverity,
                                           DTCSeverityMask,
                                           FilterForFDC);
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6060 */ /* MD_MSR_STPAR */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Client_FilterData_GetNextFilteredDTC
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
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE) Dem_Client_FilterData_GetNextFilteredDTC(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId,
  CONSTP2VAR(Dem_FilterData_ResultType, AUTOMATIC, AUTOMATIC)  FilterResult
  )
{
  Std_ReturnType lReturnValue;
  Dem_EventIdType lNextEvent;

  lNextEvent = Dem_Client_FilterData_GetDTCFilterFunction(Dem_Client_FilterData_GetDTCFilteringStrategy(FilterId))(FilterId);                  /* SBSW_DEM_CALL_DTCFILTER_FPTR */

  if (lNextEvent == DEM_EVENT_INVALID)
  {
    lReturnValue = DEM_NO_SUCH_ELEMENT;
  }
  else
  {
    if ( (Dem_Cfg_IsObdIISupportedInVariant() == TRUE)
      && (Dem_Client_FilterData_TestUseFormatOBD(FilterId) == TRUE) )                                                                   /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
    {
      FilterResult->DTC = (uint32)(((uint32)Dem_Cfg_EventObdDtc(lNextEvent)) << 8u);                                             /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    }
    else
    {
      FilterResult->DTC = Dem_Cfg_EventUdsDtc(lNextEvent);                                                                       /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    }

# if (DEM_CFG_REPORT_SUPPRESSED_DTCS_IN_19_0A == STD_ON)
    if ( (Dem_Client_FilterData_TestUseStatusMask(FilterId) == FALSE)
      && (Dem_Client_FilterData_GetMemoryId(FilterId) == DEM_CFG_MEMORYID_PRIMARY)                                                      /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
      && (Dem_DTC_TestDtcSuppression(lNextEvent) == TRUE)                                                                        /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
      )      
    {
      FilterResult->DTCStatus = 0u;                                                                                              /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    }
    else
# endif
    {
      FilterResult->DTCStatus = (uint8)(Dem_DTC_GenerateExternalOnlyStatus(                                                      /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
        lNextEvent,
        Dem_DTC_GetDTCStatus(lNextEvent)) & Dem_Cfg_GlobalStatusMask()                                                           
        );
    }

    if (Dem_Client_FilterData_TestUseFdc(FilterId) == TRUE)
    {
      FilterResult->FDC = Dem_Client_FilterData_GetFDC(FilterId);                                                                       /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    }

    if (Dem_Client_FilterData_TestUseSeverity(FilterId) == TRUE)
    {
      FilterResult->Severity = Dem_Cfg_EventSeverity(lNextEvent);                                                                /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      FilterResult->FunctionalUnit = Dem_Cfg_EventFunctionalUnit(lNextEvent);                                                    /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    }

    lReturnValue = E_OK;
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Client_FilterData_CountMatchingDTCs
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
DEM_LOCAL FUNC(uint16, DEM_CODE)
Dem_Client_FilterData_CountMatchingDTCs(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  )
{
  uint16 lNumberOfDTCs;

  if (Dem_Client_FilterData_GetDTCFilteringStrategy(FilterId) == Dem_FilterData_FilterEventBased_ReadinessGroup)
  {
    lNumberOfDTCs = Dem_Client_FilterData_GetNumberOfFilteredDTCsByReadinessGroup(FilterId);
  }
  else if (Dem_Client_FilterData_GetDTCFilteringStrategy(FilterId) == Dem_FilterData_FilterEventBased_ExtendendDataRecord)
  {
    lNumberOfDTCs = Dem_Client_FilterData_GetNumberOfFilteredDTCsByERecNumber(FilterId);
  }
  else
  {
    switch (Dem_Client_FilterData_GetMemoryId(FilterId))
    {
    case DEM_CFG_MEMORYID_PERMANENT:
      lNumberOfDTCs = Dem_Client_FilterData_CountMatchesInPermanentMemory();
      break;

    case DEM_CFG_MEMORYID_PRIMARY:
    case DEM_CFG_MEMORYID_SECONDARY:
      lNumberOfDTCs = Dem_Client_FilterData_CountMatchesInEventMemory(FilterId);
      break;

    default:
      /* no other supported memory can contain DTCs */
      lNumberOfDTCs = 0u;
      break;
    }
  }

  return lNumberOfDTCs;
}   
#endif

#if (DEM_CFG_SUPPORT_J1939_DM31 == STD_ON) || (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON)
/* ****************************************************************************
 % Dem_Client_FilterData_SetFirstDTCWithLampStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Client_FilterData_SetFirstDTCWithLampStatus(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId,
  CONST(uint8, AUTOMATIC)  NodeId
  )
{
  Dem_Cfg_FilterInfoTablePtrType lFilterDataPtr;

  lFilterDataPtr = Dem_Client_FilterData_GetFilterDataPtrSafe(FilterId);                                                                /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
  lFilterDataPtr->Iterator.EventIndex = Dem_Cfg_GlobalPrimaryFirst();                                                            /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
  lFilterDataPtr->NodeId = NodeId;                                                                                               /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
  lFilterDataPtr->FilterState = DEM_FILTERDATA_FILTER_J1939DTCLAMP;                                                              /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
}   
#endif

#if (DEM_CFG_SUPPORT_J1939_DM31 == STD_ON) || (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON)
/* ****************************************************************************
 % Dem_Client_FilterData_GetNextDTCWithLampStatus
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
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE) 
Dem_Client_FilterData_GetNextDTCWithLampStatus(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId,
  CONSTP2VAR(Dem_FilterData_ResultType, AUTOMATIC, AUTOMATIC)  FilterResult
  )
{
  Dem_Cfg_FilterInfoTablePtrType lFilterDataPtr;
  Std_ReturnType lReturnValue;
  Dem_EventIdType lEventId;

  lReturnValue = DEM_NO_SUCH_ELEMENT;
  lFilterDataPtr = Dem_Client_FilterData_GetFilterDataPtrSafe(FilterId);
  lEventId = lFilterDataPtr->Iterator.EventIndex;

  /* if last EventId is not valid or was still analyzed skip the filtering */
  if (lEventId != DEM_EVENT_INVALID)
  {
    Dem_EventIdType lEventIdLast;

    lEventIdLast = Dem_Cfg_GlobalPrimaryLast();
    /* iterate through the EventIds and check filter criteria */
    for (; lEventId <= lEventIdLast; lEventId++)
    {
      if (Dem_Cfg_EventJ1939Dtc(lEventId) == DEM_CFG_DTC_J1939_INVALID)
      { /* Don't match non-J1939 events */
        continue;                                                                                                                
      }
      if (Dem_DTC_TestSuppressionOnDtcRetrieval(lEventId) == TRUE)
      { /* Don't match suppressed events */
        continue;                                                                                                                
      }
# if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
      if (lEventId != Dem_Cfg_GetMasterEvent(lEventId))
      { /* Don't match dependent combined events */
        continue;                                                                                                                
      }
# endif

      /*Get lamp status*/
      lReturnValue = Dem_Indicator_CalculateEventJ1939LampStatus(lEventId, lFilterDataPtr->NodeId, FilterResult);                /* SBSW_DEM_POINTER_FORWARD_STACK */ 
      if (lReturnValue == E_OK)
      {
        /* Get OCC and DTC */
        FilterResult->DTC = Dem_Cfg_EventJ1939Dtc(lEventId);                                                                     /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
        FilterResult->OccurrenceCounter = Dem_Util_J1939OccurrenceCounter(lEventId);                                             /* SBSW_DEM_POINTER_WRITE_ARGUMENT */

        break;
      }
    }

    if (lEventId > lEventIdLast)
    { /* last EventId has been processed */
      lFilterDataPtr->Iterator.EventIndex = DEM_EVENT_INVALID;                                                                   /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
    }
    else
    { /* write back the EventId (which was raised by 1 for the next repetition) */
      lFilterDataPtr->Iterator.EventIndex = (Dem_EventIdType)(lEventId + 1u);                                                    /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
    }

  } /* (lEventId != DEM_EVENT_INVALID) */
  /* else return value DEM_NO_SUCH_ELEMENT initially set */

  return lReturnValue;
}                                                                                                                                /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
#endif

#if (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON)
/* ****************************************************************************
 % Dem_Client_FilterData_SetJ1939DTCFilter()
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
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Client_FilterData_SetJ1939DTCFilter(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId,
  CONST(Dem_J1939DcmDTCStatusFilterType, AUTOMATIC)  DTCStatusFilter,
  CONST(Dem_DTCKindType, AUTOMATIC)  DTCKind,
  CONST(uint8, AUTOMATIC)  MemoryId,
  CONST(uint8, AUTOMATIC)  NodeId,
  CONSTP2VAR(Dem_J1939DcmLampStatusType, AUTOMATIC, DEM_J1939DCM_DATA)  LampStatus
  )
{
  Std_ReturnType lReturnValue;
  Dem_Cfg_FilterInfoTablePtrType lFilterDataPtr;

  lReturnValue = E_OK;
  lFilterDataPtr = Dem_Client_FilterData_GetFilterDataPtrSafe(FilterId);

  if (DTCKind == DEM_DTC_KIND_ALL_DTCS)
  {
    uint8 lDTCStatusFilterType;

    /* Set the first index dependent on the requested DTC status and configuration */
    switch (DTCStatusFilter)
    {
      case DEM_J1939DTC_PENDING:
        lDTCStatusFilterType = DEM_FILTERDATA_J1939FILTER_PENDING;
        break;
      case DEM_J1939DTC_ACTIVE:
        lDTCStatusFilterType = DEM_FILTERDATA_J1939FILTER_ACTIVE;
        break;
      case DEM_J1939DTC_PREVIOUSLY_ACTIVE:
        lDTCStatusFilterType = DEM_FILTERDATA_J1939FILTER_PREVIOUSLY_ACTIVE;
        break;
      case DEM_J1939DTC_CURRENTLY_ACTIVE:
        lDTCStatusFilterType = DEM_FILTERDATA_J1939FILTER_CURRENTLY_ACTIVE;
        break;
      default:
        lDTCStatusFilterType = 0u;
        lReturnValue = E_NOT_OK;
        break;
    }

    if (lReturnValue == E_OK)
    {
      lFilterDataPtr->DTCStatusFilterType = lDTCStatusFilterType;                                                                /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */

      /* Dispatch the Event target */
      switch (MemoryId)
      {
        case DEM_CFG_MEMORYID_PRIMARY:
          lFilterDataPtr->MemoryId = MemoryId;                                                                                   /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
          lFilterDataPtr->Iterator.EventIndex = Dem_Cfg_GlobalPrimaryFirst();                                                    /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
          break;

# if (DEM_CFG_SUPPORT_SECONDARY == STD_ON)
        case DEM_CFG_MEMORYID_SECONDARY:
          lFilterDataPtr->MemoryId = MemoryId;                                                                                   /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
          lFilterDataPtr->Iterator.EventIndex = Dem_Cfg_GlobalSecondaryFirst();                                                  /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
          break;
# endif

        default:
          lReturnValue = E_NOT_OK;
          break;
      }

      if (lReturnValue == E_OK)
      {
        lFilterDataPtr->NodeId = NodeId;                                                                                         /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
        lFilterDataPtr->NumberOfDTCsTested = 0u;                                                                                 /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
       }

        /* calculate node related lamp status */
      *LampStatus = Dem_Indicator_CalculateGlobalJ1939LampStatus(NodeId);                                                        /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    }
  }
  else /* DTCKind != DEM_DTC_KIND_ALL_DTCS */
  { /* Wrong filter */ 
    lReturnValue = E_NOT_OK;
  }

  lFilterDataPtr->FilterState = DEM_FILTERDATA_FILTER_J1939DTC;                                                                  /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6060 */ /* MD_MSR_STCAL, MD_MSR_STPAR */
#endif

#if (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON)
/* ****************************************************************************
 % Dem_Client_FilterData_GetNumberOfFilteredJ1939DTC
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL FUNC(uint16, DEM_CODE)
Dem_Client_FilterData_GetNumberOfFilteredJ1939DTC(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  )
{
  uint16 lNumberOfFilteredDTC;
  Dem_EventIdType lEventId;
  P2CONST(Dem_Cfg_FilterData_InfoType, AUTOMATIC, AUTOMATIC) lFilterDataPtr;

  lFilterDataPtr = Dem_Client_FilterData_GetFilterDataPtrSafe(FilterId);
  lNumberOfFilteredDTC = 0u;

  /* iterate through the EventIds and check filter criteria */
  for (lEventId = Dem_Memory_GetFirstEvent(lFilterDataPtr->MemoryId);
       lEventId <= Dem_Memory_GetLastEvent(lFilterDataPtr->MemoryId);
       lEventId++)
  {
    if (Dem_Client_FilterData_TestEventMatchesJ1939DTCFilter(lFilterDataPtr->DTCStatusFilterType, lFilterDataPtr->NodeId, lEventId) == TRUE)
    {
      lNumberOfFilteredDTC++;
    }
  }

  return lNumberOfFilteredDTC;
}   
#endif

#if (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON)
/* ****************************************************************************
 % Dem_Client_FilterData_GetNextFilteredJ1939DTC
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
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE) 
Dem_Client_FilterData_GetNextFilteredJ1939DTC(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId,
  CONSTP2VAR(Dem_FilterData_ResultType, AUTOMATIC, AUTOMATIC)  FilterResult
  )
{
  Std_ReturnType lReturnValue;
  Dem_EventIdType lEventId;
  Dem_Cfg_FilterInfoTablePtrType lFilterDataPtr;

  lFilterDataPtr = Dem_Client_FilterData_GetFilterDataPtrSafe(FilterId);
  lReturnValue = DEM_NO_SUCH_ELEMENT;
  lEventId = lFilterDataPtr->Iterator.EventIndex;

  /* if last EventId is not valid or was still analyzed skip the filtering */
  if (lEventId != DEM_EVENT_INVALID)
  {
    Dem_EventIdType lEventIdLast;

    lEventIdLast = Dem_Memory_GetLastEvent(lFilterDataPtr->MemoryId);

    /* iterate through the EventIds and check filter criteria */
    for (; lEventId <= lEventIdLast; ++lEventId)                                                                                 /* PRQA S 0771 */ /* MD_DEM_15.4_opt */
    {
      if (lFilterDataPtr->NumberOfDTCsTested < Dem_Cfg_GlobalJ1939ReadDtcRuntimeLimit())
      {
# if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
        /* don't count dependent combined events */
        if (Dem_Cfg_GetMasterEvent(lEventId) == lEventId)
# endif
        {
          ++lFilterDataPtr->NumberOfDTCsTested;                                                                                  /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
        }

        if (Dem_Client_FilterData_TestEventMatchesJ1939DTCFilter(lFilterDataPtr->DTCStatusFilterType, lFilterDataPtr->NodeId, lEventId) == TRUE)
        {
          /* identified an Event which matches the filter criteria */
          /* Only EventIds with a valid DTC number should be processed here, so the EventId->DTC mapping will return always a valid DTC number */
          FilterResult->DTC = Dem_Cfg_EventJ1939Dtc(lEventId);                                                                   /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
          FilterResult->OccurrenceCounter = Dem_Util_J1939OccurrenceCounter(lEventId);                                           /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
          
          /* write back the EventId (which was raised by 1 for the next repetition) */
          lFilterDataPtr->Iterator.EventIndex = (Dem_EventIdType)(lEventId + 1u);                                                /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
          
          lReturnValue = E_OK;
          break;
        }

      }
      else
      {
        lFilterDataPtr->NumberOfDTCsTested = 0u;                                                                                 /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
        /* write back the current EventId (do NOT raise it as event has not yet been tested) */
        lFilterDataPtr->Iterator.EventIndex = lEventId;                                                                          /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
        lReturnValue = DEM_PENDING;
        break;
      }
    }

    if (lEventId > lEventIdLast)
    { /* last EventId has been processed */
      lFilterDataPtr->NumberOfDTCsTested = 0u;                                                                                   /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
      lFilterDataPtr->Iterator.EventIndex = DEM_EVENT_INVALID;                                                                   /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
    }

  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_CFG_SUPPORT_J1939_READINESS1 == STD_ON)
/* ****************************************************************************
 % Dem_Client_FilterData_GetDiagnosticReadiness
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
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Client_FilterData_GetDiagnosticReadiness(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId,
  CONST(uint8, AUTOMATIC)  NodeId,
  CONSTP2VAR(Dem_J1939DcmDiagnosticReadiness1Type, AUTOMATIC, DEM_J1939DCM_DATA)  DiagnosticReadiness
  )
{
  Dem_Cfg_FilterInfoTablePtrType lFilterDataPtr;
  uint8 lNumberOfFilteredDTC;
  Dem_EventIdType lEventId;

  DiagnosticReadiness->OBDCompliance = Dem_Cfg_GlobalObdRequirements();                                                          /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  DiagnosticReadiness->ContinuouslyMonitoredSystemsSupport_Status = 0u;                                                          /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  DiagnosticReadiness->NonContinuouslyMonitoredSystemsSupport = 0u;                                                              /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  DiagnosticReadiness->NonContinuouslyMonitoredSystemsStatus = 0u;                                                               /* SBSW_DEM_POINTER_WRITE_ARGUMENT */

  /* set DTC filter for active DTCs */
  lFilterDataPtr = Dem_Client_FilterData_GetFilterDataPtrSafe(FilterId);
  lFilterDataPtr->DTCStatusFilterType = DEM_FILTERDATA_J1939FILTER_ACTIVE;                                                       /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
  lFilterDataPtr->NodeId = NodeId;                                                                                               /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */
  
  /* get number of active DTCs */
  lNumberOfFilteredDTC = 0u;
  for (lEventId = Dem_Cfg_GlobalPrimaryFirst();
       lEventId <= Dem_Cfg_GlobalPrimaryLast();
       ++lEventId)
  {
    if (Dem_Client_FilterData_TestEventMatchesJ1939DTCFilter(lFilterDataPtr->DTCStatusFilterType, lFilterDataPtr->NodeId, lEventId) == TRUE)
    {
      lNumberOfFilteredDTC++;
      if (lNumberOfFilteredDTC == 250u)
      {
        break;
      }
    }
  }
  DiagnosticReadiness->ActiveTroubleCodes = lNumberOfFilteredDTC;                                                                /* SBSW_DEM_POINTER_WRITE_ARGUMENT */

  /* set DTC filter for previously active DTCs */
  lFilterDataPtr->DTCStatusFilterType = DEM_FILTERDATA_J1939FILTER_PREVIOUSLY_ACTIVE;                                            /* SBSW_DEM_ARRAY_POINTER_FILTERDATA */

  /* get number of previously active DTCs */
  lNumberOfFilteredDTC = 0u;
  for (lEventId = Dem_Cfg_GlobalPrimaryFirst();
        lEventId <= Dem_Cfg_GlobalPrimaryLast();
        ++lEventId)
  {
    if (Dem_Client_FilterData_TestEventMatchesJ1939DTCFilter(lFilterDataPtr->DTCStatusFilterType, lFilterDataPtr->NodeId, lEventId) == TRUE)
    {
      lNumberOfFilteredDTC++;
      if (lNumberOfFilteredDTC == 250u)
      {
        break;
      }
    }
  }
  DiagnosticReadiness->PreviouslyActiveDiagnosticTroubleCodes = lNumberOfFilteredDTC;                                            /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}
#endif


/* ****************************************************************************
 % Dem_Client_FilterData_InitCombinedGroupProcessed()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Client_FilterData_InitCombinedGroupProcessed(                                                                                       /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONSTP2VAR(Dem_Cfg_FilterData_InfoType, AUTOMATIC, AUTOMATIC)  DTCFilterPtr                                                    /* PRQA S 3673 */ /* MD_DEM_8.13_fp */
)
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DTCFilterPtr)                                                                                 /* PRQA S 3112 */ /* MD_DEM_14.2 */

#if(DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON) && ((DEM_CFG_SUPPORT_SVC19_56 == STD_ON) || (DEM_CFG_SUPPORT_SVC19_1A == STD_ON))
  Dem_DTC_InitCombinedGroupProcessed(DTCFilterPtr->ProcessedCombinedDTCGroups);                                                  /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
#endif
}


/* ****************************************************************************
 % Dem_Client_FilterData_SetCombinedGroupProcessed()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Client_FilterData_SetCombinedGroupProcessed(                                                                                        /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  Dem_Cfg_CombinedGroupIndexType GroupId,
  CONSTP2VAR(Dem_Cfg_FilterData_InfoType, AUTOMATIC, AUTOMATIC)  DTCFilterPtr                                                    /* PRQA S 3673 */ /* MD_DEM_8.13_fp */
)
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(GroupId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DTCFilterPtr)                                                                                 /* PRQA S 3112 */ /* MD_DEM_14.2 */

#if(DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON) && (DEM_CFG_SUPPORT_SVC19_56 == STD_ON || DEM_CFG_SUPPORT_SVC19_1A == STD_ON)
  Dem_DTC_SetCombinedGroupProcessed(GroupId, DTCFilterPtr->ProcessedCombinedDTCGroups);                                          /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
#endif
}


/* ****************************************************************************
 % Dem_Client_FilterData_TestCombinedGroupProcessed()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Client_FilterData_TestCombinedGroupProcessed(                                                                                       /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  Dem_Cfg_CombinedGroupIndexType GroupId,
  CONSTP2CONST(Dem_Cfg_FilterData_InfoType, AUTOMATIC, AUTOMATIC)  DTCFilterPtr
)
{
  boolean lGroupProcessed;
  lGroupProcessed = FALSE;
  
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(GroupId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DTCFilterPtr)                                                                                 /* PRQA S 3112 */ /* MD_DEM_14.2 */

#if(DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON) && (DEM_CFG_SUPPORT_SVC19_56 == STD_ON)
    lGroupProcessed = Dem_DTC_TestCombinedGroupProcessed(GroupId, DTCFilterPtr->ProcessedCombinedDTCGroups);                     /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
#endif
  return lGroupProcessed;
}


/* ****************************************************************************
 % Dem_Client_FilterData_SetDtcFilterByReadinessGroup
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Client_FilterData_SetDtcFilterByReadinessGroup(
  Dem_FilterData_HandleType DTCFilterId,
  Dem_Cfg_ReadinessGroupOfReadinessGroupTableType ReadinessGroup
)
{
  Dem_Client_FilterData_InitFilterFlagsAndMasks(DTCFilterId, 0xFFu, DEM_DTC_FORMAT_UDS, TRUE, FALSE, 0x00u, FALSE);
  Dem_FilterData_0x1956_SetDtcFilterByReadinessGroup(DTCFilterId, ReadinessGroup);                                           /* SBSW_DEM_POINTER_FORWARD_STACK */
  Dem_Client_FilterData_SetState(DTCFilterId, DEM_FILTERDATA_FILTER_DTC);
}

/* ****************************************************************************
 % Dem_Client_FilterData_SetDTCFilterByExtendedDataRecordNumber
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Client_FilterData_SetDTCFilterByExtendedDataRecordNumber(
  Dem_FilterData_HandleType DTCFilterId,
  uint8 ExtendedDataRecordNumber
)
{
  Std_ReturnType lReturnValue;
  lReturnValue = Dem_Dcm_ERec_0x191A_SetDTCFilterByExtendedDataRecordNumber(DTCFilterId, ExtendedDataRecordNumber);            /* SBSW_DEM_POINTER_FORWARD_STACK */

  if (lReturnValue == E_OK)
  {
    Dem_Client_FilterData_SetState(DTCFilterId, DEM_FILTERDATA_FILTER_DTC);
    Dem_Client_FilterData_InitFilterFlagsAndMasks(DTCFilterId, 0xFFu, DEM_DTC_FORMAT_UDS, TRUE, FALSE, 0x00u, FALSE);
  }

  return lReturnValue;
}


/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_FILTERDATAIF_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_FilterDataIF_Implementation.h
 *********************************************************************************************************************/
