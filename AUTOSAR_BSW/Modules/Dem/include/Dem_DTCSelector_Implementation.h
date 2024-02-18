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
/*! \addtogroup Dem_DTCSelector
 *  \{
 *  \file       Dem_DTCSelector_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) Implementation file
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_DTCSELECTOR_IMPLEMENTATION_H)
#define DEM_DTCSELECTOR_IMPLEMENTATION_H

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
#include "Dem_DTCSelector_Interface.h"

/* Includes to access public functions belonging to other (top level)/ (logical)/- units to be used by this Unit */
/* ------------------------------------------------------------------------- */
#include "Dem_Core_Interface.h"
#include "Dem_Infrastructure_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*! Filename declaration */
#define DEM_DTCSELECTOR_IMPLEMENTATION_FILENAME "Dem_DTCSelector_Implementation.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE PROPERTIES DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*!
 * \defgroup Dem_DTCSelector_PrivateProperties Private Properties
 * \{
 */

/* ****************************************************************************
 * Dem_DTCSelector_GetSelectionData()
 *****************************************************************************/
/*!
 * \brief         Return pointer to a DTC selector table entry.
 *
 * \details       Return pointer to a DTC selector table entry.
 *
 * \param[in]     DTCSelectorId
 *                The selector to read.

 * \return        Pointer to DTC selector table entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTCSelector_DataPtrType, DEM_CODE)
Dem_DTCSelector_GetSelectionData(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId
  );

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE PROPERTIES DEFINITIONS
 *********************************************************************************************************************/

/* ****************************************************************************
 % Dem_DTCSelector_GetSelectionData()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTCSelector_DataPtrType, DEM_CODE)
Dem_DTCSelector_GetSelectionData(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId
  )
{
  return Dem_Cfg_GetAddrDTCSelectorTable(DTCSelectorId);
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
 * \addtogroup Dem_DTCSelector_PublicProperties
 * \{
 */

/* ****************************************************************************
 % Dem_DTCSelector_GetGroupId()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTCSelector_GroupIdType, DEM_CODE)
Dem_DTCSelector_GetGroupId(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId
  )
{
  Dem_DTCSelector_GroupIdType lReturnValue;

  if (Dem_DTCSelector_GetSelectionData(DTCSelectorId)->SelectorState == DEM_DTCSELECTOR_SELECTION_ALL_DTCS)
  {
    lReturnValue = Dem_DTCSelector_GetSelectionData(DTCSelectorId)->Selection.GroupId;
  }
  else
  {
    lReturnValue = DEM_DTCSELECTOR_GROUP_INVALID;
  }
  return lReturnValue;
}

#if (DEM_CFG_CLEAR_GROUP_DTCS == STD_ON)
/* ****************************************************************************
 % Dem_DTCSelector_GetGroupMask()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DTCSelector_GetGroupMask(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId
  )
{
  uint8 lReturnValue;

  if (Dem_DTCSelector_GetSelectionData(DTCSelectorId)->SelectorState == DEM_DTCSELECTOR_SELECTION_GROUP)
  {
    lReturnValue = Dem_DTCSelector_GetSelectionData(DTCSelectorId)->Selection.GroupMask;
  }
  else
  {
    lReturnValue = DEM_CFG_GROUPMASK_NONE;
  }
  return lReturnValue;
}
#endif

/* ****************************************************************************
 % Dem_DTCSelector_GetEventId()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_DTCSelector_GetEventId(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId
  )
{
  Dem_EventIdType lReturnValue;

  if (Dem_DTCSelector_GetSelectionData(DTCSelectorId)->SelectorState == DEM_DTCSELECTOR_SELECTION_DTC)
  {
    lReturnValue = Dem_DTCSelector_GetSelectionData(DTCSelectorId)->Selection.EventId;
  }
  else
  {
    lReturnValue = DEM_EVENT_INVALID;
  }
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_DTCSelector_GetMemoryId()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DTCSelector_GetMemoryId(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId
  )
{
  uint8 lReturnValue;

  if (Dem_DTCSelector_GetSelectionData(DTCSelectorId)->SelectorState != DEM_DTCSELECTOR_SELECTION_NO_MATCH)
  {
    lReturnValue = Dem_DTCSelector_GetSelectionData(DTCSelectorId)->MemoryId;
  }
  else
  {
    lReturnValue = DEM_CFG_MEMORYID_INVALID;
  }
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_DTCSelector_GetSelectionResult()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTCSelector_ResultType, DEM_CODE)
Dem_DTCSelector_GetSelectionResult(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId
  )
{
  return Dem_DTCSelector_GetSelectionData(DTCSelectorId)->SelectorState;
}

/* ****************************************************************************
 % Dem_DTCSelector_GetSelectionArguments
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTCSelector_RequestType, DEM_CODE) Dem_DTCSelector_GetSelectionArguments(
  CONST(uint8, AUTOMATIC)  DTCSelectorId
  )
{
  return Dem_DTCSelector_GetSelectionData(DTCSelectorId)->Request;
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
 * \defgroup Dem_DTCSelector_Private Private Methods
 * \{
 */


/* ****************************************************************************
 * Dem_DTCSelector_SetSelectionData()
 *****************************************************************************/
/*!
 * \brief         Stores input parameters to the valid DTC selector.
 *
 * \details       Checks if passed selector handle is valid and stores input 
 *                parameters to the valid DTC selector.
 *
 * \param[in]     DTCSelectorId
 *                The selector to modify.
 * \param[in]     DTCNumber
 *                The DTC number
 * \param[in]     DTCFormat
 *                The DTC number format (OBD/UDS/J1939).
 * \param[in]     DTCOrigin
 *                The event memory of the requested DTC or group of DTC.
 * \param[in]     MemoryId
 *                The event memory handle to store in the selection
 * \param[in]     DTCSelectionType
 *                The type for selection data
 * \param[in]     DTCSelectionResult
 *                The result of a DTC selection
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different DTCSelectorId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCSelector_SetSelectionData(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId,
  CONST(uint32, AUTOMATIC)  DTCNumber,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat,
  CONST(Dem_DTCOriginType, AUTOMATIC)  DTCOrigin,
  CONST(uint8, AUTOMATIC)  MemoryId,
  CONST(Dem_DTCSelector_SelectionType, AUTOMATIC) DTCSelectionType,
  CONST(Dem_DTCSelector_ResultType, AUTOMATIC) DTCSelectionResult
  );


/* ****************************************************************************
 * Dem_DTCSelector_SetSelectionData_ActiveAsyncOps()
 *****************************************************************************/
/*!
 * \brief         Stores input parameter to the valid DTC selector.
 *
 * \details       Checks if passed selector handle is valid and stores input
 *                parameter to the valid DTC selector.
 *
 * \param[in]     DTCSelectorId
 *                The selector to modify.
 * \param[in]     ActiveAsyncOps
 *                The number of active asynchronous operations requiring Dem_SelectDTC()
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different DTCSelectorId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCSelector_SetSelectionData_ActiveAsyncOps(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId,
  CONST(uint8, AUTOMATIC)  ActiveAsyncOps
  );


/* ****************************************************************************
 * Dem_DTCSelector_InitGroupId()
 *****************************************************************************/
/*!
 * \brief         Initialize a selector with a group id selection.
 *
 * \details       Initializes a selector with a group id selection.
 *
 * \param[in]     DTCSelectorId
 *                The selector to modify.
 * \param[in]     DTCNumber
 *                The DTC number
 * \param[in]     DTCFormat
 *                The DTC number format (OBD/UDS/J1939).
 * \param[in]     DTCOrigin
 *                The event memory of the requested DTC or group of DTC.
 * \param[in]     MemoryId
 *                The event memory handle to store in the selection
 * \param[in]     GroupId
 *                The group id to store in the selection
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different DTCSelectorId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCSelector_InitGroupId(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId,
  CONST(uint32, AUTOMATIC)  DTCNumber,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat,
  CONST(Dem_DTCOriginType, AUTOMATIC)  DTCOrigin,
  CONST(uint8, AUTOMATIC)  MemoryId,
  CONST(Dem_DTCSelector_GroupIdType, AUTOMATIC)  GroupId
  );


/* ****************************************************************************
 * Dem_DTCSelector_InitGroupMask()
 *****************************************************************************/
/*!
 * \brief         Initialize a selector with a group mask selection.
 *
 * \details       Initializes a selector with a group mask selection.
 *
 * \param[in]     DTCSelectorId
 *                The selector to modify.
 * \param[in]     DTCNumber
 *                The DTC number
 * \param[in]     DTCFormat
 *                The DTC number format (OBD/UDS/J1939).
 * \param[in]     DTCOrigin
 *                The event memory of the requested DTC or group of DTC.
 * \param[in]     MemoryId
 *                The event memory handle to store in the selection
 * \param[in]     GroupMask
 *                The group mask to store in the selection
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different DTCSelectorId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCSelector_InitGroupMask(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId,
  CONST(uint32, AUTOMATIC)  DTCNumber,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat,
  CONST(Dem_DTCOriginType, AUTOMATIC)  DTCOrigin,
  CONST(uint8, AUTOMATIC)  MemoryId,
  CONST(uint8, AUTOMATIC)  GroupMask
  );


/* ****************************************************************************
 * Dem_DTCSelector_InitEventId()
 *****************************************************************************/
/*!
 * \brief         Initialize a selector with an event id selection.
 *
 * \details       Initializes a selector with an event id selection.
 *
 * \param[in]     DTCSelectorId
 *                The selector to modify.
 * \param[in]     DTCNumber
 *                The DTC number
 * \param[in]     DTCFormat
 *                The DTC number format (OBD/UDS/J1939).
 * \param[in]     DTCOrigin
 *                The event memory of the requested DTC or group of DTC.
 * \param[in]     MemoryId
 *                The event memory handle to store in the selection
 * \param[in]     EventId
 *                The event id to store in the selection
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different DTCSelectorId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCSelector_InitEventId(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId,
  CONST(uint32, AUTOMATIC)  DTCNumber,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat,
  CONST(Dem_DTCOriginType, AUTOMATIC)  DTCOrigin,
  CONST(uint8, AUTOMATIC)  MemoryId,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );


/* ****************************************************************************
 * Dem_DTCSelector_InitInvalid()
 *****************************************************************************/
/*!
 * \brief         Initialize a selector with an invalid selection
 *
 * \details       Initialize a selector with an invalid selection. The different 
 *                invalid states are used to calculate the corresponding negative
 *                return value of API Dem_GetDTCSelectionResult.
 *
 * \param[in]     DTCSelectorId
 *                The selector to modify.
 * \param[in]     DTCNumber
 *                The DTC number
 * \param[in]     DTCFormat
 *                The DTC number format (OBD/UDS/J1939).
 * \param[in]     DTCOrigin
 *                The event memory of the requested DTC or group of DTC.
 * \param[in]     SelectorState
 *                Possible invalid states are 'Initialization', 'Wrong Origin' or 
 *                'No Match'
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different DTCSelectorId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCSelector_InitInvalid(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId,
  CONST(uint32, AUTOMATIC)  DTCNumber,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat,
  CONST(Dem_DTCOriginType, AUTOMATIC)  DTCOrigin,
  CONST(Dem_DTCSelector_ResultType, AUTOMATIC)  SelectorState
  );


/* ****************************************************************************
 * Dem_DTCSelector_FindGroupMaskFromUdsDtc
 *****************************************************************************/
/*!
 * \brief         Find a DTC group mask in the configuration tables.
 *
 * \details       Find a DTC group mask in the configuration tables.
 *
 * \param[in]     DTC
 *                DTC number
 *
 * \return        The group mask matching the passed DTC group number.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DTCSelector_FindGroupMaskFromUdsDtc(
  CONST(uint32, AUTOMATIC)  DTC
  );


/* ****************************************************************************
 * Dem_DTCSelector_TestForAllDtc
 *****************************************************************************/
/*!
 * \brief         Test whether a DTC number encodes an 'AllDTC' mask.
 *
 * \details       Test whether a DTC number encodes an 'AllDTC' mask.
 *
 * \param[in]     DTC
 *                DTC number
 * \param[in]     DTCFormat
 *                The DTC number format (OBD/UDS/J1939).
 *
 * \return        DEM_DTCSELECTOR_GROUP_ALL_DTCS
 *                The DTC matches the ALL DTC group
 * \return        DEM_DTCSELECTOR_GROUP_EMISSION_RELATED
 *                The DTC matches the emission related DTCs group
 * \return        DEM_DTCSELECTOR_GROUP_WWH_OBD_ALL_DTC
 *                The DTC matches the WWH-OBD ALL DTC group
 * \return        DEM_DTCSELECTOR_GROUP_INVALID if no 'all DTC' group matches
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTCSelector_GroupIdType, DEM_CODE)
Dem_DTCSelector_TestForAllDtc(
  CONST(uint32, AUTOMATIC)  DTC,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat
  );


/* ****************************************************************************
 * Dem_DTCSelector_TestForGroupDtc
 *****************************************************************************/
/*!
 * \brief         Test if a DTC number encodes a specific DTC group (not
 *                ALLDTCs).
 *
 * \details       Test if a DTC number encodes a specific DTC group (not
 *                ALLDTCs).
 *
 * \param[in]     DTC
 *                DTC number
 * \param[in]     DTCFormat
 *                The DTC number format (OBD/UDS/J1939).
 *
 * \return        DEM_CFG_GROUPMASK_NONE if the DTC does not matches a DTC group,
 *                otherwise this function returns the configured group mask
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DTCSelector_TestForGroupDtc(
  CONST(uint32, AUTOMATIC)  DTC,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat
  );


/* ****************************************************************************
 * Dem_DTCSelector_TestForSingleDtc
 *****************************************************************************/
/*!
 * \brief         Test if a DTC number encodes a specific DTC
 *
 * \details       Test if a DTC number encodes a specific DTC. If so,
 *                this function initializes the DTCSelector.
 *
 * \param[in]     DTC
 *                DTC number
 * \param[in]     DTCFormat
 *                The DTC number format (OBD/UDS/J1939).
 * \param[in]     MemoryId
 *                The event memory handle
 *
 * \return        DEM_EVENT_INVALID if the DTC has not matched a DTC, otherwise
 *                this function returns the matching EventId
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_DTCSelector_TestForSingleDtc(
  CONST(uint32, AUTOMATIC)  DTC,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat,
  CONST(uint8, AUTOMATIC)  MemoryId
  );


/* ****************************************************************************
 * Dem_DTCSelector_TestForSupportedMemoryId()
 *****************************************************************************/
/*!
 * \brief         Test if memory id is valid in context of DTC selection.
 *
 * \details       Test if memory id is valid in context of DTC selection.
 *
 * \param[in]     MemoryId
 *                The event memory handle
 *
 * \return        TRUE   The MemoryId is supported
 * \return        FALSE  The MemoryId is not supported
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTCSelector_TestForSupportedMemoryId(
  CONST(uint8, AUTOMATIC) MemoryId
  );

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/

/* ****************************************************************************
 % Dem_DTCSelector_SetSelectionData()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCSelector_SetSelectionData(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId,
  CONST(uint32, AUTOMATIC)  DTCNumber,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat,
  CONST(Dem_DTCOriginType, AUTOMATIC)  DTCOrigin,
  CONST(uint8, AUTOMATIC)  MemoryId,
  CONST(Dem_DTCSelector_SelectionType, AUTOMATIC) DTCSelectionType,
  CONST(Dem_DTCSelector_ResultType, AUTOMATIC) DTCSelectionResult
  )
{
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (DTCSelectorId >= Dem_Cfg_GetSizeOfDTCSelectorTable())
  {
    Dem_Error_RunTimeCheckFailed(DEM_DTCSELECTOR_IMPLEMENTATION_FILENAME, __LINE__);                                             /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  { 
    Dem_DTCSelector_DataPtrType lDTCSelector;
    lDTCSelector = Dem_Cfg_GetAddrDTCSelectorTable(DTCSelectorId);
    lDTCSelector->Request.DTC = DTCNumber;                                                                                       /* SBSW_DEM_ARRAY_POINTER_DTCSELECTORTABLE */
    lDTCSelector->Request.DTCFormat = DTCFormat;                                                                                 /* SBSW_DEM_ARRAY_POINTER_DTCSELECTORTABLE */
    lDTCSelector->Request.DTCOrigin = DTCOrigin;                                                                                 /* SBSW_DEM_ARRAY_POINTER_DTCSELECTORTABLE */
    lDTCSelector->MemoryId = MemoryId;                                                                                           /* SBSW_DEM_ARRAY_POINTER_DTCSELECTORTABLE */
    lDTCSelector->Selection = DTCSelectionType;                                                                                  /* SBSW_DEM_ARRAY_POINTER_DTCSELECTORTABLE */
    lDTCSelector->SelectorState = DTCSelectionResult;                                                                            /* SBSW_DEM_ARRAY_POINTER_DTCSELECTORTABLE */
  }
}                                                                                                                                /* PRQA S 6060 */ /* MD_MSR_STPAR */

/* ****************************************************************************
 % Dem_DTCSelector_SetSelectionData_ActiveAsyncOps()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCSelector_SetSelectionData_ActiveAsyncOps(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId,
  CONST(uint8, AUTOMATIC)  ActiveAsyncOps
  )
{
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (DTCSelectorId >= Dem_Cfg_GetSizeOfDTCSelectorTable())
  {
    Dem_Error_RunTimeCheckFailed(DEM_DTCSELECTOR_IMPLEMENTATION_FILENAME, __LINE__);                                             /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    Dem_DTCSelector_DataPtrType lDTCSelector;
    lDTCSelector = Dem_Cfg_GetAddrDTCSelectorTable(DTCSelectorId);
    lDTCSelector->ActiveAsyncOps = ActiveAsyncOps;                                                                               /* SBSW_DEM_ARRAY_POINTER_DTCSELECTORTABLE */
  }
}

/* ****************************************************************************
 % Dem_DTCSelector_InitGroupId()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCSelector_InitGroupId(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId,
  CONST(uint32, AUTOMATIC)  DTCNumber,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat,
  CONST(Dem_DTCOriginType, AUTOMATIC)  DTCOrigin,
  CONST(uint8, AUTOMATIC)  MemoryId,
  CONST(Dem_DTCSelector_GroupIdType, AUTOMATIC)  GroupId
  )
{
  Dem_DTCSelector_SelectionType lDTCSelectionType;                                                                               /* PRQA S 0759 */ /* MD_MSR_Union */
  Dem_DTCSelector_ResultType lDTCSelectionResult;

  lDTCSelectionType.GroupId = GroupId;
  lDTCSelectionResult = DEM_DTCSELECTOR_SELECTION_ALL_DTCS;

  Dem_DTCSelector_SetSelectionData(DTCSelectorId,
                                   DTCNumber,
                                   DTCFormat,
                                   DTCOrigin,
                                   MemoryId,
                                   lDTCSelectionType,
                                   lDTCSelectionResult);
}                                                                                                                                /* PRQA S 6060 */ /* MD_MSR_STPAR */

/* ****************************************************************************
 % Dem_DTCSelector_InitGroupMask()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCSelector_InitGroupMask(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId,
  CONST(uint32, AUTOMATIC)  DTCNumber,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat,
  CONST(Dem_DTCOriginType, AUTOMATIC)  DTCOrigin,
  CONST(uint8, AUTOMATIC)  MemoryId,
  CONST(uint8, AUTOMATIC)  GroupMask
  )
{
  Dem_DTCSelector_SelectionType lDTCSelectionType;                                                                               /* PRQA S 0759 */ /* MD_MSR_Union */
  Dem_DTCSelector_ResultType lDTCSelectionResult;

  lDTCSelectionType.GroupMask = GroupMask;
  lDTCSelectionResult = DEM_DTCSELECTOR_SELECTION_GROUP;

  Dem_DTCSelector_SetSelectionData(DTCSelectorId,
                                   DTCNumber,
                                   DTCFormat,
                                   DTCOrigin,
                                   MemoryId,
                                   lDTCSelectionType,
                                   lDTCSelectionResult);
}                                                                                                                                /* PRQA S 6060 */ /* MD_MSR_STPAR */

/* ****************************************************************************
 % Dem_DTCSelector_InitEventId()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCSelector_InitEventId(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId,
  CONST(uint32, AUTOMATIC)  DTCNumber,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat,
  CONST(Dem_DTCOriginType, AUTOMATIC)  DTCOrigin,
  CONST(uint8, AUTOMATIC)  MemoryId,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_DTCSelector_SelectionType lDTCSelectionType;                                                                               /* PRQA S 0759 */ /* MD_MSR_Union */
  Dem_DTCSelector_ResultType lDTCSelectionResult;

  lDTCSelectionType.EventId = EventId;
  lDTCSelectionResult = DEM_DTCSELECTOR_SELECTION_DTC;

  Dem_DTCSelector_SetSelectionData(DTCSelectorId,
                                   DTCNumber,
                                   DTCFormat,
                                   DTCOrigin,
                                   MemoryId,
                                   lDTCSelectionType,
                                   lDTCSelectionResult);
}                                                                                                                                /* PRQA S 6060 */ /* MD_MSR_STPAR */

/* ****************************************************************************
 % Dem_DTCSelector_InitInvalid()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCSelector_InitInvalid(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId,
  CONST(uint32, AUTOMATIC)  DTCNumber,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat,
  CONST(Dem_DTCOriginType, AUTOMATIC)  DTCOrigin,
  CONST(Dem_DTCSelector_ResultType, AUTOMATIC)  SelectorState
  )
{
  Dem_DTCSelector_SelectionType lDTCSelectionType;                                                                               /* PRQA S 0759 */ /* MD_MSR_Union */
  Dem_DTCSelector_ResultType lDTCSelectionResult;

  lDTCSelectionType.EventId = DEM_EVENT_INVALID;
  lDTCSelectionResult = SelectorState;

  Dem_DTCSelector_SetSelectionData(DTCSelectorId,
                                   DTCNumber,
                                   DTCFormat,
                                   DTCOrigin,
                                   DEM_CFG_MEMORYID_INVALID,
                                   lDTCSelectionType,
                                   lDTCSelectionResult);

  Dem_DTCSelector_SetSelectionData_ActiveAsyncOps(DTCSelectorId,
                                                  0x00U);
}


/************************************************************************************************************
 %  Dem_DTCSelector_FindGroupMaskFromUdsDtc
 ***********************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DTCSelector_FindGroupMaskFromUdsDtc(
  CONST(uint32, AUTOMATIC)  DTC
  )
{
  uint8 lGroupMask;

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DTC)                                                                                          /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lGroupMask = DEM_DTCSELECTOR_GROUP_INVALID;
#if (Dem_Cfg_HasDtcGroupMask() == TRUE)
  {
    uint8_least lGroupIterator;
    for (lGroupIterator = 0u; lGroupIterator < Dem_Cfg_GetSizeOfDtcGroupMask(); lGroupIterator++)
    {
      if (Dem_Cfg_GetUdsGroupDtcOfDtcGroupMask(lGroupIterator) == DTC)
      {
        lGroupMask = Dem_Cfg_GetGroupMaskOfDtcGroupMask(lGroupIterator);
        break;
      }
    }
  }
#endif

  return lGroupMask;
}

/* ****************************************************************************
 % Dem_DTCSelector_TestForAllDtc
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
DEM_LOCAL_INLINE FUNC(Dem_DTCSelector_GroupIdType, DEM_CODE)
Dem_DTCSelector_TestForAllDtc(
  CONST(uint32, AUTOMATIC)  DTC,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat
  )
{
  Dem_DTCSelector_GroupIdType lReturnValue;

  if ( (DTCFormat == DEM_DTC_FORMAT_UDS)
    || (DTCFormat == DEM_DTC_FORMAT_OBD) )
  {
    if (DTC == DEM_DTC_GROUP_ALL_DTCS)
    {
      lReturnValue = DEM_DTCSELECTOR_GROUP_ALL_DTCS;
    }
    else if (DTC == DEM_DTC_GROUP_EMISSION_REL_DTCS)
    {
      lReturnValue = DEM_DTCSELECTOR_GROUP_EMISSION_RELATED;
    }
    else if (DTC == DEM_DTC_GROUP_WWHOBD_DTCS)
    {
      lReturnValue = DEM_DTCSELECTOR_GROUP_WWH_OBD_ALL_DTC;
    }
    else
    {
      lReturnValue = DEM_DTCSELECTOR_GROUP_INVALID;
    }
  }
  else
  {
    /* DTC Format J1939 */
    if (DTC == DEM_DTC_GROUP_ALL_DTCS)
    {
      lReturnValue = DEM_DTCSELECTOR_GROUP_ALL_DTCS;
    }
    else
    {
      lReturnValue = DEM_DTCSELECTOR_GROUP_INVALID;
    }
  }
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_DTCSelector_TestForGroupDtc
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DTCSelector_TestForGroupDtc(
  CONST(uint32, AUTOMATIC)  DTC,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat
  )
{
  uint8 lReturnValue;
  if (DTCFormat == DEM_DTC_FORMAT_UDS)
  {
    lReturnValue = Dem_DTCSelector_FindGroupMaskFromUdsDtc(DTC);
  }
  else
  {
    lReturnValue = DEM_CFG_GROUPMASK_NONE;
  }
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_DTCSelector_TestForSingleDtc
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
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_DTCSelector_TestForSingleDtc(
  CONST(uint32, AUTOMATIC)  DTC,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat,
  CONST(uint8, AUTOMATIC)  MemoryId
  )
{
  Dem_EventIdType lEventId;

  if (DTCFormat == DEM_DTC_FORMAT_UDS)
  {
    if (DTC == 0u)
    {
      lEventId = DEM_EVENT_INVALID;
    }
    else
    {
      lEventId = Dem_Cfg_GetMasterEvent(Dem_Cfg_FindEventFromUdsDtc(DTC, MemoryId));
    }
  }
  else
#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
  if (DTCFormat == DEM_DTC_FORMAT_J1939)
  {
    if (DTC == 0u)
    { /* DTC does not exist */
      lEventId = DEM_EVENT_INVALID;
    }
    else
    { /* Dem_Cfg_FindEventFromJ1939Dtc can not be called with '0' */
      lEventId = Dem_Cfg_GetMasterEvent(Dem_Cfg_FindEventFromJ1939Dtc(DTC, MemoryId));
    }
  }
  else
#endif
  {
    lEventId = DEM_EVENT_INVALID;
  }

  return lEventId;
}

/* ****************************************************************************
 % Dem_DTCSelector_TestForSupportedMemoryId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTCSelector_TestForSupportedMemoryId(
  CONST(uint8, AUTOMATIC)  MemoryId
  )
{
  boolean lReturnValue;

  lReturnValue = FALSE;
  switch (MemoryId)
    {
    case DEM_CFG_MEMORYID_PRIMARY:
      lReturnValue = TRUE;
      break;

# if (DEM_CFG_SUPPORT_SECONDARY == STD_ON)
    case DEM_CFG_MEMORYID_SECONDARY:
      lReturnValue = TRUE;
      break;
# endif

    case DEM_CFG_MEMORYID_PERMANENT:
      if (Dem_Cfg_IsPermanentSupportedInVariant() == TRUE)
      {
        lReturnValue = TRUE;
      }
      break;

    default:                                                                                                                     /* PRQA S 2016 */ /* MD_MSR_EmptyClause */
      /* FALSE */
      break;
    }
  return lReturnValue;
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
 * \addtogroup Dem_DTCSelector_Public
 * \{
 */

/* ****************************************************************************
 % Dem_DTCSelector_InitDefault()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCSelector_InitDefault(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId
  )
{
  Dem_DTCSelector_InitInvalid(DTCSelectorId, 
                              DEM_CFG_DTC_UDS_INVALID, 
                              DEM_DTC_FORMAT_INVALID, 
                              DEM_DTC_ORIGIN_INVALID, 
                              DEM_DTCSELECTOR_SELECTION_INIT);
}

/* ****************************************************************************
 % Dem_DTCSelector_SelectDTC()
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
Dem_DTCSelector_SelectDTC(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId,
  CONST(uint32, AUTOMATIC)  DTCNumber,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat,
  CONST(Dem_DTCOriginType, AUTOMATIC)  DTCOrigin,
  CONST(uint8, AUTOMATIC)  MemoryId
  )
{
  Dem_DTCSelector_GroupIdType lGroupId;

  if (Dem_DTCSelector_TestForSupportedMemoryId(MemoryId) == FALSE)
  {
    Dem_DTCSelector_InitInvalid(DTCSelectorId, DTCNumber, DTCFormat, DTCOrigin, DEM_DTCSELECTOR_SELECTION_WRONG_ORIGIN);
  }
  else
  {
    lGroupId = Dem_DTCSelector_TestForAllDtc(DTCNumber, DTCFormat);
    if (lGroupId != DEM_DTCSELECTOR_GROUP_INVALID)
    {
      Dem_DTCSelector_InitGroupId(DTCSelectorId, DTCNumber, DTCFormat, DTCOrigin, MemoryId, lGroupId);
    }
    else
    {
      uint8 lGroupMask;
      lGroupMask = Dem_DTCSelector_TestForGroupDtc(DTCNumber, DTCFormat);
      if (lGroupMask != DEM_CFG_GROUPMASK_NONE)
      {
        Dem_DTCSelector_InitGroupMask(DTCSelectorId, DTCNumber, DTCFormat, DTCOrigin, MemoryId, lGroupMask);
      }
      else
      {
        Dem_EventIdType lEventId;
        lEventId = Dem_DTCSelector_TestForSingleDtc(DTCNumber, DTCFormat, MemoryId);
        if (lEventId != DEM_EVENT_INVALID)
        {
          Dem_DTCSelector_InitEventId(DTCSelectorId, DTCNumber, DTCFormat, DTCOrigin, MemoryId, lEventId);
        }
        else
        {
          Dem_DTCSelector_InitInvalid(DTCSelectorId, DTCNumber, DTCFormat, DTCOrigin, DEM_DTCSELECTOR_SELECTION_NO_MATCH);
        }
      }
    }
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_DTCSelector_LockSelectDTC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCSelector_LockSelectDTC(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId
  )
{
  uint8 lActiveAsyncOps;

  lActiveAsyncOps = Dem_DTCSelector_GetSelectionData(DTCSelectorId)->ActiveAsyncOps;
  Dem_Internal_AssertReturnVoid(lActiveAsyncOps < 255, DEM_E_INCONSISTENT_STATE)
  lActiveAsyncOps++;
  Dem_DTCSelector_SetSelectionData_ActiveAsyncOps(DTCSelectorId, lActiveAsyncOps);
}

/* ****************************************************************************
 % Dem_DTCSelector_ReleaseSelectDTC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCSelector_ReleaseSelectDTC(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId
  )
{
  uint8 lActiveAsyncOps;

  lActiveAsyncOps = Dem_DTCSelector_GetSelectionData(DTCSelectorId)->ActiveAsyncOps;
  Dem_Internal_AssertReturnVoid(lActiveAsyncOps > 0, DEM_E_INCONSISTENT_STATE)
  lActiveAsyncOps--;
  Dem_DTCSelector_SetSelectionData_ActiveAsyncOps(DTCSelectorId, lActiveAsyncOps);
}

/* ****************************************************************************
 % Dem_DTCSelector_TestSelectDTCLocked()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTCSelector_TestSelectDTCLocked(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId
  )
{
  return (boolean) (Dem_DTCSelector_GetSelectionData(DTCSelectorId)->ActiveAsyncOps > 0u);
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_DTCSELECTOR_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_DTCSelector_Implementation.h
 *********************************************************************************************************************/
