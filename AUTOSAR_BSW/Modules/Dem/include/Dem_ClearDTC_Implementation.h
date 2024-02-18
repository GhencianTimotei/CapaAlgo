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
/*! \addtogroup Dem_ClearDTC
 *  \{
 *  \file       Dem_ClearDTC_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Implementation of ClearDTC subcomponent
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_CLEARDTC_IMPLEMENTATION_H)
#define DEM_CLEARDTC_IMPLEMENTATION_H

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
#include "Dem_ClearDTC_Interface.h"

/* Includes to access public functions belonging to other (top level)/ (logical)/- units to be used by this Unit */
/* ------------------------------------------------------------------------- */
#include "Dem_ClearTask_Interface.h"
#include "Dem_DTCSelector_Interface.h"
#include "Dem_Infrastructure_Interface.h"
#include "Dem_DiagnosticObserver_Interface.h"
#include "Dem_Core_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*! Filename declaration */
#define DEM_CLEARDTC_IMPLEMENTATION_FILENAME "Dem_ClearDTC_Implementation.h"

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
 *  SUBCOMPONENT OBJECT FUNCTION DEFINITIONS
 *********************************************************************************************************************/
/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE PROPERTIES DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_ClearDTC_PrivateProperties Private Properties
 * \{
 */

/* ****************************************************************************
 * Dem_ClearDTC_GetClearData()
 *****************************************************************************/
/*!
 * \brief         Get the data of a clear operation.
 *
 * \details       Get the data of a clear operation.
 *
 * \param[in]     ClearDTCHandle
 *                The ClearDTC handle to read.

 * \return        The data of the clear operation
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_ClearDTC_DataType, DEM_CODE) Dem_ClearDTC_GetClearData(
  CONST(Dem_ClearDTC_HandleType, AUTOMATIC)  ClearDTCHandle
  );


/* ****************************************************************************
 * Dem_ClearDTC_TestClearWwhObdAllDTCsAllowed()
 *****************************************************************************/
/*!
 * \brief         Test if clearing of all WWH-OBD related DTCs is allowed.
 *
 * \details       Test if clearing of all WWH-OBD related DTCs is allowed.
 *
 * \return        TRUE
 *                Clearing WWH-OBD DTCs is allowed
 * \return        FALSE
 *                Clearing WWH-OBD DTCs is not allowed
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different ClearDTCHandle
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE) Dem_ClearDTC_TestClearWwhObdAllDTCsAllowed(
  void
  );


/* ****************************************************************************
 * Dem_ClearDTC_TestClearObdAllDTCsAllowed()
 *****************************************************************************/
/*!
 * \brief         Test if clearing of all OBD related DTCs is allowed.
 *
 * \details       Test if clearing of all OBD related DTCs is allowed.
 *
 * \return        TRUE
 *                Clearing OBD DTCs is allowed
 * \return        FALSE
 *                Clearing OBD DTCs is not allowed
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different ClearDTCHandle
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE) Dem_ClearDTC_TestClearObdAllDTCsAllowed(
  void
  );

/* ****************************************************************************
 * Dem_ClearDTC_SetClearStatus()
 *****************************************************************************/
/*!
 * \brief         Set the status of a clear operation.
 *
 * \details       Set the status of a clear operation.
 *
 * \param[in]     ClearDTCHandle
 *                The ClearDTC handle to modify.
 * \param[in]     ClearDTCStatus
 *                The ClearDTCStatus to set.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different ClearDTCHandle
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) Dem_ClearDTC_SetClearStatus(
  CONST(Dem_ClearDTC_HandleType, AUTOMATIC)  ClearDTCHandle,
  CONST(Dem_ClearDTC_StatusType, AUTOMATIC)  ClearDTCStatus
  );


/* ****************************************************************************
 * Dem_ClearDTC_GetClearSelector()
 *****************************************************************************/
/*!
 * \brief         Get the DTCSelector of a clear operation.
 *
 * \details       Get the DTCSelector of a clear operation.
 *
 * \param[in]     ClearDTCHandle
 *                The ClearDTC handle to read.
 *
 * \return        The DTCSelector of the clear operation
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different ClearDTCHandle
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTCSelector_HandleType, DEM_CODE) Dem_ClearDTC_GetClearSelector(
  CONST(Dem_ClearDTC_HandleType, AUTOMATIC)  ClearDTCHandle
  );


/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE PROPERTIES DEFINITIONS
 *********************************************************************************************************************/

/* ****************************************************************************
 % Dem_ClearDTC_GetClearData()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_ClearDTC_DataType, DEM_CODE) Dem_ClearDTC_GetClearData(
  CONST(Dem_ClearDTC_HandleType, AUTOMATIC)  ClearDTCHandle
  )
{
  return Dem_Cfg_GetClearDTCTable(ClearDTCHandle);
}



/* ****************************************************************************
 % Dem_ClearDTC_TestClearWwhObdAllDTCsAllowed()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE) Dem_ClearDTC_TestClearWwhObdAllDTCsAllowed(
  void
  )
{
  boolean lReturnValue;
#if (DEM_CFG_CLEAR_WWHOBD_GROUP_DTCS == STD_ON)
  if (Dem_Cfg_IsWwhObdSupportedInVariant() == TRUE)
  {
    lReturnValue = TRUE;
  }
  else
#endif
  {
    lReturnValue = FALSE;
  }

  return lReturnValue;
}


/* ****************************************************************************
 % Dem_ClearDTC_TestClearObdAllDTCsAllowed()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE) Dem_ClearDTC_TestClearObdAllDTCsAllowed(
  void
  )
{
  boolean lReturnValue;
#if (DEM_CFG_CLEAR_OBDII_GROUP_DTCS == STD_ON)
  if (Dem_Cfg_IsObdIISupportedInVariant() == TRUE)
  {
    lReturnValue = TRUE;
  }
  else
#endif
  {
    lReturnValue = FALSE;
  }
  return lReturnValue;
}


/* ****************************************************************************
 % Dem_ClearDTC_SetClearStatus()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) Dem_ClearDTC_SetClearStatus(
  CONST(Dem_ClearDTC_HandleType, AUTOMATIC)  ClearDTCHandle,
  CONST(Dem_ClearDTC_StatusType, AUTOMATIC)  ClearDTCStatus
  )
{
  Dem_ClearDTC_DataType lClearData;

  lClearData = Dem_ClearDTC_GetClearData(ClearDTCHandle);
  lClearData.ClearDTCStatus = ClearDTCStatus;
  Dem_ClearDTC_SetClearData(ClearDTCHandle, lClearData);
}

/* ****************************************************************************
 % Dem_ClearDTC_GetClearSelector()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTCSelector_HandleType, DEM_CODE) Dem_ClearDTC_GetClearSelector(
  CONST(Dem_ClearDTC_HandleType, AUTOMATIC)  ClearDTCHandle
  )
{
  return Dem_ClearDTC_GetClearData(ClearDTCHandle).DTCSelector;
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
 * \addtogroup Dem_ClearDTC_PublicProperties
 * \{
 */

/* ****************************************************************************
 % Dem_ClearDTC_GetClearStatus()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_ClearDTC_StatusType, DEM_CODE) Dem_ClearDTC_GetClearStatus(
  CONST(Dem_ClearDTC_HandleType, AUTOMATIC)  ClearDTCHandle
  )
{
  return Dem_ClearDTC_GetClearData(ClearDTCHandle).ClearDTCStatus;
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
 * \defgroup Dem_ClearDTC_Private Private Methods
 * \{
 */


/* ****************************************************************************
 * Dem_ClearDTC_CallStartNotifications()
 *****************************************************************************/
/*!
 * \brief         Call all clear start notification callbacks.
 *
 * \details       Call all clear start notification callbacks.
 *
 * \param[in]     ClearDTCHandle
 *                The ClearDTC handle.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) Dem_ClearDTC_CallStartNotifications(
  CONST(Dem_ClearDTC_HandleType, AUTOMATIC)  ClearDTCHandle
  );


/* ****************************************************************************
 * Dem_ClearDTC_CallEndNotifications()
 *****************************************************************************/
/*!
 * \brief         Call all clear end notification callbacks.
 *
 * \details       Call all clear end notification callbacks.
 *
 * \param[in]     ClearDTCHandle
 *                The ClearDTC handle.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) Dem_ClearDTC_CallEndNotifications(
  CONST(Dem_ClearDTC_HandleType, AUTOMATIC)  ClearDTCHandle
  );


/* ****************************************************************************
 * Dem_ClearDTC_StartClearOperation()
 *****************************************************************************/
/*!
 * \brief         Try to start a clear DTC operation
 *
 * \details       Starts a clear operation
 *
 * \param[in]     ClearRequest
 *                The ClearDTC request
 * \param[in]     DTCSelector
 *                The selector holding the selected DTC to clear
 *
 * \return        DEM_PENDING
 *                The Clear DTC operation was started
 * \return        DEM_CLEAR_BUSY
 *                Another Clear DTC operation is active
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different ClearDTCHandle
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE) Dem_ClearDTC_StartClearOperation(
  CONST(Dem_ClearTask_ClearRequestConstPtrType, AUTOMATIC)  ClearRequest,
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelector
  );


/* ****************************************************************************
 * Dem_ClearDTC_StartClearEvent()
 *****************************************************************************/
/*!
 * \brief         Start clear DTC for a single event
 *
 * \details       Initializes a clear DTC handler to process clearing a single
 *                event
 *
 * \param[in]     ClearRequest
 *                Pointer to clear request structure
 * \param[in]     DTCSelector
 *                The selector holding the selected DTC to clear
 *
 * \return        Status of the started clear operation
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different ClearDTCHandle
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE) Dem_ClearDTC_StartClearEvent(
  Dem_ClearTask_ClearRequestPtrType  ClearRequest,
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelector
  );


/* ****************************************************************************
 * Dem_ClearDTC_StartClearAllDTCs()
 *****************************************************************************/
/*!
 * \brief         Start clear all DTCs
 *
 * \details       Initializes a clear DTC handler to process clearing all
 *                events of a DTC group or all DTCs
 *
 * \param[in]     ClearRequest
 *                Pointer to clear request structure
 * \param[in]     DTCSelector
 *                The selector holding the selected DTC group to clear
 *                DEM_DTCSELECTOR_GROUP_WWH_OBD_ALL_DTC
 *                  - All WWH-OBD DTCs.
 *                DEM_DTCSELECTOR_GROUP_EMISSION_RELATED
 *                  - All emission related DTCs.
 *                None of the above applies: all DTCs will be cleared
 *
 * \return        DEM_WRONG_DTC
 *                Selected DTC group does not exist or clearing the
 *                group is not supported
 * \return        DEM_PENDING
 *                The clear operation was started and is currently processed
 * \return        DEM_CLEAR_BUSY
 *                Another clear operation is currently processing
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different ClearDTCHandle
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE) Dem_ClearDTC_StartClearAllDTCs(
  Dem_ClearTask_ClearRequestPtrType  ClearRequest,
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelector
  );


/* ****************************************************************************
 * Dem_ClearDTC_StartClearGroup()
 *****************************************************************************/
/*!
 * \brief         Start clear DTC for a single event
 *
 * \details       Initializes a clear DTC handler to process clearing a single
 *                event
 *
 * \param[in]     ClearRequest
 *                Pointer to clear request structure
 * \param[in]     DTCSelector
 *                The selector holding the selected DTC to clear
 *
 * \return        Status of the started clear operation
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different ClearDTCHandle
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE) Dem_ClearDTC_StartClearGroup(
  Dem_ClearTask_ClearRequestPtrType  ClearRequest,
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelector
  );

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/

/* ****************************************************************************
 % Dem_ClearDTC_CallStartNotifications()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) Dem_ClearDTC_CallStartNotifications(
  CONST(Dem_ClearDTC_HandleType, AUTOMATIC)  ClearDTCHandle
  )
{
  Dem_DTCSelector_HandleType lDTCSelector;
  Dem_DTCSelector_RequestType lSelectionRequest;

  lDTCSelector = Dem_ClearDTC_GetClearSelector(ClearDTCHandle);
  lSelectionRequest = Dem_DTCSelector_GetSelectionArguments(lDTCSelector);
  Dem_Notifications_ClearDTCStart(
    lSelectionRequest.DTC,
    lSelectionRequest.DTCFormat,
    lSelectionRequest.DTCOrigin);
}

/* ****************************************************************************
 % Dem_ClearDTC_CallEndNotifications()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) Dem_ClearDTC_CallEndNotifications(
  CONST(Dem_ClearDTC_HandleType, AUTOMATIC)  ClearDTCHandle
  )
{
  Dem_DTCSelector_HandleType lDTCSelector;
  Dem_DTCSelector_RequestType lSelectionRequest;

  lDTCSelector = Dem_ClearDTC_GetClearSelector(ClearDTCHandle);
  lSelectionRequest = Dem_DTCSelector_GetSelectionArguments(lDTCSelector);
  Dem_Notifications_ClearDTCEnd(
    lSelectionRequest.DTC,
    lSelectionRequest.DTCFormat,
    lSelectionRequest.DTCOrigin);
  Dem_DTCSelector_ReleaseSelectDTC(lDTCSelector);
}

/* ****************************************************************************
 % Dem_ClearDTC_StartClearOperation()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE) Dem_ClearDTC_StartClearOperation(
  CONST(Dem_ClearTask_ClearRequestConstPtrType, AUTOMATIC)  ClearRequest,
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelector
  )
{
  Std_ReturnType lReturnValue;
  Std_ReturnType lClearStarted;

  lClearStarted = Dem_ClearTask_TryNewClear(ClearRequest, DTCSelector);                                                          /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */

  if (lClearStarted == E_OK)
  {
    lReturnValue = DEM_PENDING;
  }
  else
  {
    lReturnValue = DEM_CLEAR_BUSY;
  }

  return lReturnValue;
}

/* ****************************************************************************
 % Dem_ClearDTC_StartClearEvent()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE) Dem_ClearDTC_StartClearEvent(
  Dem_ClearTask_ClearRequestPtrType  ClearRequest,                                                                               /* PRQA S 3673 */ /* MD_DEM_8.13_fp */
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelector
  )
{
  Std_ReturnType lReturnValue;
#if (DEM_CFG_CLEAR_SINGLE_DTCS == STD_ON)
  Dem_EventIdType lEventId;
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(ClearRequest)                                                                                 /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DTCSelector)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif

#if (DEM_CFG_CLEAR_SINGLE_DTCS == STD_ON)
  lEventId = Dem_DTCSelector_GetEventId(DTCSelector);
  if (Dem_DTC_TestSuppressionOnDtcRetrieval(lEventId) == FALSE)
  {
    ClearRequest->ClearEventId = lEventId;                                                                                       /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    lReturnValue = Dem_ClearDTC_StartClearOperation(ClearRequest, DTCSelector);                                                  /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }
  else
  {
    lReturnValue = DEM_WRONG_DTC;
  }
#else
  lReturnValue = DEM_WRONG_DTC;
#endif
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_ClearDTC_StartClearGroup()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE) Dem_ClearDTC_StartClearGroup(
  Dem_ClearTask_ClearRequestPtrType  ClearRequest,                                                                               /* PRQA S 3673 */ /* MD_DEM_8.13_fp */
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelector
  )
{
  Std_ReturnType lReturnValue;

#if (DEM_CFG_CLEAR_GROUP_DTCS == STD_ON)
  ClearRequest->ClearGroup = Dem_DTCSelector_GetGroupMask(DTCSelector);                                                          /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  lReturnValue = Dem_ClearDTC_StartClearOperation(ClearRequest, DTCSelector);                                                    /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(ClearRequest)                                                                                 /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DTCSelector)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */

  lReturnValue = DEM_WRONG_DTC;
#endif

  return lReturnValue;
}

/* ****************************************************************************
 % Dem_ClearDTC_StartClearAllDTCs()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE) Dem_ClearDTC_StartClearAllDTCs(
  Dem_ClearTask_ClearRequestPtrType  ClearRequest,
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelector
  )
{
  Std_ReturnType lReturnValue;

  if (Dem_DTCSelector_GetGroupId(DTCSelector) == DEM_DTCSELECTOR_GROUP_WWH_OBD_ALL_DTC)
  {
    if ((Dem_ClearDTC_TestClearWwhObdAllDTCsAllowed() == TRUE)
      && (ClearRequest->ClearMemoryId == DEM_CFG_MEMORYID_PRIMARY))
    {
      lReturnValue = E_OK;
    }
    else
    {
      lReturnValue = DEM_WRONG_DTC;
    }
  }
  else
  if (Dem_DTCSelector_GetGroupId(DTCSelector) == DEM_DTCSELECTOR_GROUP_EMISSION_RELATED)
  {
    if ((Dem_ClearDTC_TestClearObdAllDTCsAllowed() == TRUE)
      && (ClearRequest->ClearMemoryId == DEM_CFG_MEMORYID_PRIMARY))
    {
      lReturnValue = E_OK;
    }
    else
    {
      lReturnValue = DEM_WRONG_DTC;
    }
  }
  else
  {
    lReturnValue = E_OK;
  }

  if (lReturnValue == E_OK)
  {
    ClearRequest->ClearGroup = DEM_CFG_GROUPMASK_ALLDTCS;                                                                        /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    lReturnValue = Dem_ClearDTC_StartClearOperation(ClearRequest, DTCSelector);                                                  /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
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
 * \addtogroup Dem_ClearDTC_Public
 * \{
 */

/* ****************************************************************************
 % Dem_ClearDTC_Init()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) Dem_ClearDTC_Init(
  void
  )
{
  Dem_ClearDTC_HandleType lClearClient;
  
  for (lClearClient = 0u;
       lClearClient < Dem_Cfg_GetSizeOfClearDTCTable();
       ++lClearClient)
  {
    Dem_ClearDTC_SetClearStatus(lClearClient, DEM_CLEARDTC_STATUS_IDLE);
  }
}

/* ****************************************************************************
 % Dem_ClearDTC_SetClearData()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) Dem_ClearDTC_SetClearData(
  CONST(Dem_ClearDTC_HandleType, AUTOMATIC)  ClearDTCHandle,
  CONST(Dem_ClearDTC_DataType, AUTOMATIC)  ClearDTCData
  )
{
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (ClearDTCHandle >= Dem_Cfg_GetSizeOfClearDTCTable())
  {
    Dem_Error_RunTimeCheckFailed(DEM_CLEARDTC_IMPLEMENTATION_FILENAME, __LINE__);                                                /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    Dem_Cfg_SetClearDTCTable(ClearDTCHandle, ClearDTCData);                                                                      /* SBSW_DEM_ARRAY_WRITE_CLEARDTCTABLE */
  }  
}

#if (DEM_CFG_SUPPORT_J1939_CLEAR_DTC == STD_ON)
/* ****************************************************************************
 % Dem_ClearDTC_StartClearJ1939()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE) Dem_ClearDTC_StartClearJ1939(
  CONST(Dem_ClearDTC_HandleType, AUTOMATIC)  ClearDTCHandle,
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelector,
  CONST(uint8, AUTOMATIC)  DTCTypeFilter,
  CONST(uint8, AUTOMATIC)  Node
  )
{
  Dem_ClearTask_ClearRequestType lClearRequest;
  lClearRequest.ClearClient = ClearDTCHandle;
  lClearRequest.ClearEventId = DEM_EVENT_INVALID;
  lClearRequest.ClearGroup = DEM_CFG_GROUPMASK_ALLDTCS;
  lClearRequest.ClearFilter = DTCTypeFilter;

  lClearRequest.ClearMemoryId = Dem_DTCSelector_GetMemoryId(DTCSelector);
  lClearRequest.ClearNode = Node;

  return Dem_ClearDTC_StartClearOperation(&lClearRequest, DTCSelector);                                                          /* SBSW_DEM_POINTER_FORWARD_STACK */
}
#endif

/* ****************************************************************************
 % Dem_ClearDTC_StartClear()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE) Dem_ClearDTC_StartClear(
  CONST(Dem_ClearDTC_HandleType, AUTOMATIC)  ClearDTCHandle,
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelector
  )
{
  Std_ReturnType lReturnValue;
  Dem_ClearTask_ClearRequestType lClearRequest;

  lClearRequest.ClearClient = ClearDTCHandle;
  lClearRequest.ClearEventId = DEM_EVENT_INVALID;
  lClearRequest.ClearGroup = DEM_CFG_GROUPMASK_NONE;
  lClearRequest.ClearFilter = 0xFF;
  lClearRequest.ClearMemoryId = Dem_DTCSelector_GetMemoryId(DTCSelector);
  lClearRequest.ClearNode = DEM_CFG_J1939_NODE_INVALID;
  
  switch (Dem_DTCSelector_GetSelectionResult(DTCSelector))
  {
  case DEM_DTCSELECTOR_SELECTION_DTC:
    lReturnValue = Dem_ClearDTC_StartClearEvent(&lClearRequest, DTCSelector);                                                    /* SBSW_DEM_POINTER_FORWARD_STACK */
    break;
  case DEM_DTCSELECTOR_SELECTION_GROUP:
    lReturnValue = Dem_ClearDTC_StartClearGroup(&lClearRequest, DTCSelector);                                                    /* SBSW_DEM_POINTER_FORWARD_STACK */
    break;
  case DEM_DTCSELECTOR_SELECTION_ALL_DTCS:
    lReturnValue = Dem_ClearDTC_StartClearAllDTCs(&lClearRequest, DTCSelector);                                                  /* SBSW_DEM_POINTER_FORWARD_STACK */
    break;
  case DEM_DTCSELECTOR_SELECTION_NO_MATCH:
  case DEM_DTCSELECTOR_SELECTION_WRONG_ORIGIN:
  case DEM_DTCSELECTOR_SELECTION_INIT:
  default:
    /* cannot reach: cases already handled by caller */
    lReturnValue = DEM_CLEAR_FAILED;
    break;
  }
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_ClearDTC_ResetClearStatus()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) Dem_ClearDTC_ResetClearStatus(
  CONST(Dem_ClearDTC_HandleType, AUTOMATIC)  ClearDTCHandle
  )
{
  Dem_ClearDTC_DataType lClearData;
  lClearData = Dem_ClearDTC_GetClearData(ClearDTCHandle);
  if (lClearData.ClearDTCStatus != DEM_CLEARDTC_STATUS_PENDING)
  {
    lClearData.ClearDTCStatus = DEM_CLEARDTC_STATUS_IDLE;
    Dem_ClearDTC_SetClearData(ClearDTCHandle, lClearData);
  }
}

/* ****************************************************************************
 % Dem_ClearDTC_NotifyClearResult()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) Dem_ClearDTC_NotifyClearResult(
  CONST(uint8, AUTOMATIC)  QueueClearState
  )
{
  Dem_ClearDTC_HandleType lClearHandle;
  lClearHandle = Dem_ClearTask_GetClearClient();
  if (Dem_ClearDTC_GetClearStatus(lClearHandle) != DEM_CLEARDTC_STATUS_IDLE)
  {
    switch (QueueClearState)
    {
    case DEM_CLEARTASK_INPROGRESS:
      Dem_ClearDTC_CallStartNotifications(lClearHandle);
      break;

    case DEM_CLEARTASK_DONE:
      Dem_ClearDTC_CallEndNotifications(lClearHandle);
      Dem_ClearDTC_SetClearStatus(lClearHandle, DEM_CLEARDTC_STATUS_DONE);
      break;
    case DEM_CLEARTASK_FAILED:
      Dem_ClearDTC_CallEndNotifications(lClearHandle);
      Dem_ClearDTC_SetClearStatus(lClearHandle, DEM_CLEARDTC_STATUS_FAILED);
      break;
    case DEM_CLEARTASK_NVERROR:
      Dem_ClearDTC_CallEndNotifications(lClearHandle);
      Dem_ClearDTC_SetClearStatus(lClearHandle, DEM_CLEARDTC_STATUS_NV_ERROR);
      break;
    case DEM_CLEARTASK_IDLE:
    default:                                                                                                                     /* PRQA S 2016 */ /* MD_MSR_EmptyClause */
      /* no update */
      break;
    }
  }
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */


#endif /* DEM_CLEARDTC_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_ClearDTC_Implementation.h
 *********************************************************************************************************************/
