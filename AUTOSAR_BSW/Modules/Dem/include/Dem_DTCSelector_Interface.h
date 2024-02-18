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
 *  \defgroup   Dem_DTCSelector DTCSelector
 *  \{
 *  \file       Dem_DTCSelector_Interface.h
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

#if !defined (DEM_DTCSELECTOR_INTERFACE_H)
#define DEM_DTCSELECTOR_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_DTCSelector_Types.h"
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
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_DTCSelector_PublicProperties Public Properties
 * \{
 */

/* ****************************************************************************
 * Dem_DTCSelector_GetGroupId()
 *****************************************************************************/
/*!
 * \brief         Get the GroupId stored in the selector object
 *
 * \details       Get the GroupId stored in the selector object
 *
 * \param[in]     DTCSelectorId
 *                The object to read from.
 *
 * \return        one of
 *                 - DEM_DTCSELECTOR_GROUP_ALL_DTCS
 *                 - DEM_DTCSELECTOR_GROUP_EMISSION_RELATED
 *                 - DEM_DTCSELECTOR_GROUP_WWH_OBD_ALL_DTC
 *                if DEM_DTCSELECTOR_SELECTION_ALL_DTCS was selected
 * \return        DEM_DTCSELECTOR_GROUP_INVALID if no group was selected.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTCSelector_GroupIdType, DEM_CODE)
Dem_DTCSelector_GetGroupId(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId
  );

#if (DEM_CFG_CLEAR_GROUP_DTCS == STD_ON)
 /* ****************************************************************************
  * Dem_DTCSelector_GetGroupMask()
  *****************************************************************************/
 /*!
  * \brief         Get the Group mask stored in the selector object
  *
  * \details       Get the GroupMask stored in the selector object
  *
  * \param[in]     DTCSelectorId
  *                The object to read from.
  *
  * \return        The GroupMask stored in the selector object.
  * \return        DEM_CFG_GROUPMASK_NONE if no group was selected.
  *
  * \pre           -
  * \config        DEM_CFG_CLEAR_GROUP_DTCS == STD_ON
  *
  * \context       TASK|ISR2
  * \synchronous   TRUE
  * \reentrant     TRUE
  *****************************************************************************/
 DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
 Dem_DTCSelector_GetGroupMask(
   CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId
   );
#endif

/* ****************************************************************************
 * Dem_DTCSelector_GetEventId()
 *****************************************************************************/
/*!
 * \brief         Get the EventId stored in the selector object
 *
 * \details       Get the EventId stored in the selector object
 *
 * \param[in]     DTCSelectorId
 *                The object to read from.
 *
 * \return        The EventId stored in the selector object.
 * \return        DEM_EVENT_INVALID if no event was selected
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_DTCSelector_GetEventId(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId
  );

/* ****************************************************************************
 * Dem_DTCSelector_GetMemoryId()
 *****************************************************************************/
/*!
 * \brief         Get the MemoryId stored in the selector object
 *
 * \details       Get the MemoryId stored in the selector object
 *
 * \param[in]     DTCSelectorId
 *                The object to read from.
 *
 * \return        The MemoryId stored in the selector object.
 *                DEM_CFG_MEMORYID_INVALID if no selection was requested
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DTCSelector_GetMemoryId(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId
  );

/* ****************************************************************************
 * Dem_DTCSelector_GetSelectionResult()
 *****************************************************************************/
/*!
 * \brief         Get the result of the last selection
 *
 * \details       Get the result of the last selection
 *
 * \param[in]     DTCSelectorId
 *                The object to read from.
 *
 * \return        DEM_DTCSELECTOR_SELECTION_INVALID
 *                Error, no DTC or group was selected
 * \return        DEM_DTCSELECTOR_SELECTION_DTC
 *                A DTC was selected
 * \return        DEM_DTCSELECTOR_SELECTION_GROUP
 *                A DTC group was selected
 * \return        DEM_DTCSELECTOR_SELECTION_WRONG_MEMORY
 *                The DTC or group does not belong to the selected memory
 * \return        DEM_DTCSELECTOR_SELECTION_WRONG_DTC
 *                The selected number does not map to a DTC or DTC group
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTCSelector_ResultType, DEM_CODE)
Dem_DTCSelector_GetSelectionResult(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId
  );

/* ****************************************************************************
 * Dem_DTCSelector_GetSelectionArguments
 *****************************************************************************/
/*!
 * \brief         Returns the original arguments of the selection.
 *
 * \details       Returns the original arguments of the selection.
 *
 * \param[in]     DTCSelectorId
 *                The object to read from.
 *
 * \return        DTC selection arguments.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTCSelector_RequestType, DEM_CODE) Dem_DTCSelector_GetSelectionArguments(
  CONST(uint8, AUTOMATIC)  DTCSelectorId
  );

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
 * \defgroup Dem_DTCSelector_Public Public Methods
 * \{
 */

/* ****************************************************************************
 * Dem_DTCSelector_InitDefault()
 *****************************************************************************/
/*!
 * \brief         Initialize a selector.
 *
 * \details       Initializes a selector, the selector does not contain a
 *                selection afterwards.
 *
 * \param[in]     DTCSelectorId
 *                The selector to modify.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different DTCSelectorId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCSelector_InitDefault(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId
  );

/* ****************************************************************************
 * Dem_DTCSelector_SelectDTC()
 *****************************************************************************/
/*!
 * \brief         Initialize a selector from DTC information.
 *
 * \details       Initializes a selector based on the passed DTC number information.
 *
 * \param[in]     DTCSelectorId
 *                The object to read from.
 * \param[in]     DTCNumber
 *                The DTC number
 * \param[in]     DTCFormat
 *                The DTC number format (OBD/UDS/J1939).
 * \param[in]     DTCOrigin
 *                The event memory of the requested DTC or group of DTC.
 * \param[in]     MemoryId
 *                The event memory handle
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different DTCSelectorId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCSelector_SelectDTC(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId,
  CONST(uint32, AUTOMATIC)  DTCNumber,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat,
  CONST(Dem_DTCOriginType, AUTOMATIC)  DTCOrigin,
  CONST(uint8, AUTOMATIC)  MemoryId
  );

/* ****************************************************************************
 * Dem_DTCSelector_LockSelectDTC()
 *****************************************************************************/
/*!
 * \brief         Locks access to the API Dem_SelectDTC
 *
 * \details       Incrementing internal counter for active asynchronous 
 *                operations that require Dem_SelectDTC in the selector object  
 *
 * \param[in]     DTCSelectorId
 *                Handle for DTC Selector
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCSelector_LockSelectDTC(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId
  );

/* ****************************************************************************
 * Dem_DTCSelector_ReleaseSelectDTC()
 *****************************************************************************/
/*!
 * \brief         Releases access to the API Dem_SelectDTC
 *
 * \details       Decrementing internal counter for active asynchronous 
 *                operations that require Dem_SelectDTC in the selector object 
 *
 * \param[in]     DTCSelectorId
 *                Handle for DTC Selector
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCSelector_ReleaseSelectDTC(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId
  );

/* ****************************************************************************
 * Dem_DTCSelector_TestSelectDTCLocked()
 *****************************************************************************/
/*!
 * \brief         Tests if access to API Dem_SelectDTC is allowed
 *
 * \details       Tests if internal counter stored in the selector object is 
 *                equal 0 or not. 
 *
 * \param[in]     DTCSelectorId
 *                Handle for DTC Selector
 *
 * \return        TRUE
 *                API access is locked
 *
 * \return        FALSE
 *                API access is granted
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTCSelector_TestSelectDTCLocked(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_DTCSELECTOR_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_DTCSelector_Interface.h
 *********************************************************************************************************************/
