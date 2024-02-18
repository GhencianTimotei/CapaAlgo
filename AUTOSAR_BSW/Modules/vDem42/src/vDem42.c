/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2018 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  vDem42.c
 *        \brief  vDem42 SWC
 *
 *      \details  Implementation of the vDem42 SWC
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the VERSION CHECK below.
 *********************************************************************************************************************/

#define VDEM42_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "vDem42.h"
#include "Rte_vDem42.h"

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* Check the version of vDem42 header file */
#if (  (VDEM42_SW_MAJOR_VERSION != (1u)) \
    || (VDEM42_SW_MINOR_VERSION != (2u)) \
    || (VDEM42_SW_PATCH_VERSION != (0u)) )
# error "Vendor specific version numbers of vDem42.c and vDem42.h are inconsistent"
#endif

#if (  (VDEM42_TYPES_MAJOR_VERSION != 1u) \
    || (VDEM42_TYPES_MINOR_VERSION != 2u) \
    || (VDEM42_TYPES_PATCH_VERSION != 0u) )
# error "Vendor specific version numbers of vDem42.c and vDem42_Types.h are inconsistent"
#endif

/* Check the version of the configuration header file */
#if (  (VDEM42_CFG_SW_MAJOR_VERSION != (1u)) \
    || (VDEM42_CFG_SW_MINOR_VERSION != (2u)) )
# error "Version numbers of vDem42.c and vDem42_Cfg.h are inconsistent!"
#endif

/* Check the version of the generator */
#if (  (VDEM42_CFG_GEN_MAJOR_VERSION != (1u)) \
    || (VDEM42_CFG_GEN_MINOR_VERSION != (2u)) )
# error "Version numbers of vDem42.c and vDem42_Cfg.h are inconsistent!"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#if !defined (VDEM42_LOCAL)                                                                                                                          /* COV_VDEM42_MACRO_OVERRIDE */
# define VDEM42_LOCAL static
#endif

#if !defined (VDEM42_LOCAL_INLINE)                                                                                                                   /* COV_VDEM42_MACRO_OVERRIDE */
# define VDEM42_LOCAL_INLINE LOCAL_INLINE
#endif

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

#define VDEM42_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_19.1 */

VDEM42_LOCAL VDem42_ClearDTC_SelectionState vDem42_ClearDTC_SelectionState =
  /* lastSelected_DTC * lastSelected_DTCFormat * lastSelected_DTCOrigin * isDTCSelected */
  {  UINT32_MAX,        UINT8_MAX,               UINT8_MAX,               FALSE }; /* initialize as not selected */

#define VDEM42_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define VDEM42_START_SEC_CODE
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  VDem42_InitMemory()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, VDEM42_CODE) VDem42_InitMemory(void)
{
  vDem42_ClearDTC_SelectionState.isDTCSelected = FALSE;
}

/**********************************************************************************************************************
 * VDem42_Init()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, VDEM42_CODE) VDem42_Init(void* configPtr)                                                                                                 /* PRQA S 3673 */ /* MD_vDem42_Design_3673 */
{
  VDEM42_IGNORE_UNREF_PARAM(configPtr);                                                                                                              /* PRQA S 3112 */ /* MD_vDem42_3112 */
  vDem42_ClearDTC_SelectionState.isDTCSelected = FALSE;
}

/**********************************************************************************************************************
 * VDem42_ClearDTC()
 *********************************************************************************************************************/
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
FUNC(VDem42_ReturnClearDTCType, VDEM42_CODE) VDem42_ClearDTC(uint32 DTC,
                                                             VDem42_DTCFormatType DTCFormat,
                                                             VDem42_DTCOriginType DTCOrigin)
{
  Std_ReturnType lStdRetValueDem43ClearDTC;
  Std_ReturnType lRetValueVDem42;

  /* If another DTC has already been selected */
  if ( (vDem42_ClearDTC_SelectionState.isDTCSelected == TRUE)
       && ( (vDem42_ClearDTC_SelectionState.lastSelected_DTC != DTC)
         || (vDem42_ClearDTC_SelectionState.lastSelected_DTCFormat != DTCFormat)
         || (vDem42_ClearDTC_SelectionState.lastSelected_DTCOrigin != DTCOrigin) ) )
  {
    vDem42_ClearDTC_SelectionState.isDTCSelected = FALSE;
  }

  if (vDem42_ClearDTC_SelectionState.isDTCSelected == FALSE)
  {
    Std_ReturnType lStdRetValueSelectDTC;
    lStdRetValueSelectDTC = Rte_Call_ClearDTC_vDem42_SelectDTC(DTC,
                                                               DTCFormat,
                                                               DTCOrigin);
    if (lStdRetValueSelectDTC == E_OK)
    {
      vDem42_ClearDTC_SelectionState.isDTCSelected = TRUE;
      vDem42_ClearDTC_SelectionState.lastSelected_DTC = DTC;
      vDem42_ClearDTC_SelectionState.lastSelected_DTCFormat = DTCFormat;
      vDem42_ClearDTC_SelectionState.lastSelected_DTCOrigin = DTCOrigin;
    }
  }

  if (vDem42_ClearDTC_SelectionState.isDTCSelected == TRUE)
  {
    lStdRetValueDem43ClearDTC = Rte_Call_ClearDTC_vDem42_ClearDTC();

    if (lStdRetValueDem43ClearDTC != RTE_E_ClearDTC_DEM_PENDING)
    {
      vDem42_ClearDTC_SelectionState.isDTCSelected = FALSE;
    }

    /* Map the return value from AR4.2.2 to AR4.3 */
    switch (lStdRetValueDem43ClearDTC)
    {
      case E_OK:
        lRetValueVDem42 = E_OK;
        break;
      case RTE_E_ClearDTC_DEM_PENDING:
        lRetValueVDem42 = RTE_E_CddIf_DEM_CLEAR_PENDING;
        break;
      case RTE_E_ClearDTC_DEM_CLEAR_BUSY:
        lRetValueVDem42 = RTE_E_CddIf_DEM_CLEAR_BUSY;
        break;
      case RTE_E_ClearDTC_DEM_CLEAR_MEMORY_ERROR:
        lRetValueVDem42 = RTE_E_CddIf_DEM_CLEAR_MEMORY_ERROR;
        break;
      case RTE_E_ClearDTC_DEM_CLEAR_FAILED:
        lRetValueVDem42 = RTE_E_CddIf_DEM_CLEAR_FAILED;
        break;
      case RTE_E_ClearDTC_DEM_WRONG_DTC:
        lRetValueVDem42 = RTE_E_CddIf_DEM_CLEAR_WRONG_DTC;
        break;
      case RTE_E_ClearDTC_DEM_WRONG_DTCORIGIN:
        lRetValueVDem42 = RTE_E_CddIf_DEM_CLEAR_WRONG_DTCORIGIN;
        break;
      default:
        lRetValueVDem42 = RTE_E_CddIf_DEM_CLEAR_FAILED;
        break;
    }
  }
  else
  {
    lRetValueVDem42 = RTE_E_CddIf_DEM_CLEAR_FAILED;
  }

  return lRetValueVDem42;
}                                                                                                                                                    /* PRQA S 6010, 6030 */ /* MD_MSR_STPTH, MD_MSR_STCYC */

/**********************************************************************************************************************
 * VDem42_GetDTCOfEvent()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, VDEM42_CODE) VDem42_GetDTCOfEvent(VDem42_EventIdType EventId,                                                                   /* PRQA S 1330 */ /* MD_Rte_1330 */
                                                       VDem42_DTCFormatType DTCFormat,
                                                       P2VAR(uint32, AUTOMATIC, VDEM42_APPL_VAR) DTCOfEvent)
{
  Std_ReturnType lRetValue;
  Std_ReturnType lRetValueVDem42;

  lRetValue = Rte_Call_GeneralEvtInfo43_GetDTCOfEvent(EventId,
                                                      DTCFormat,
                                                      DTCOfEvent);
  switch (lRetValue)
  {
    case E_OK:
      lRetValueVDem42 = E_OK;
      break;
    case E_NOT_OK:
      lRetValueVDem42 = E_NOT_OK;
      break;
    case RTE_E_GeneralDiagnosticInfo43_DEM_E_NO_DTC_AVAILABLE:
      lRetValueVDem42 = RTE_E_GeneralDiagnosticInfo422_DEM_E_NO_DTC_AVAILABLE;
      break;
    default:
      lRetValueVDem42 = E_NOT_OK;
      break;
  }
  return lRetValueVDem42;
}

/**********************************************************************************************************************
 * VDem42_GetDebouncingOfEvent()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, VDEM42_CODE) VDem42_GetDebouncingOfEvent(
                                          VDem42_EventIdType EventId,                                                                                /* PRQA S 1330 */ /* MD_Rte_1330 */
                                          P2VAR(VDem42_DebouncingStateType, AUTOMATIC, VDEM42_APPL_VAR) DebouncingState)
{
  Std_ReturnType lRetValue;
  Std_ReturnType lRetValueVDem42;

  lRetValue = Rte_Call_GeneralEvtInfo43_GetDebouncingOfEvent(EventId,
                                                             DebouncingState);
  switch (lRetValue)
  {
    case E_OK:
      lRetValueVDem42 = E_OK;
      break;
    case E_NOT_OK:
      lRetValueVDem42 = E_NOT_OK;
      break;
    default:
      lRetValueVDem42 = E_NOT_OK;
      break;
  }
  return lRetValueVDem42;
}

/**********************************************************************************************************************
 * VDem42_GetEventExtendedDataRecord()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, VDEM42_CODE) VDem42_GetEventExtendedDataRecord(VDem42_EventIdType EventId,                                                      /* PRQA S 1330 */ /* MD_Rte_1330 */
                                                                    uint8 RecordNumber,
                                                                    P2VAR(uint8, AUTOMATIC, VDEM42_APPL_VAR) DestBuffer)
{
  Std_ReturnType lRetValueVDem42;
  uint16 lBufSize = sizeof(Dem_MaxDataValueType);

  lRetValueVDem42 = VDem42_GetEventExtendedDataRecordEx(EventId,
                                                        RecordNumber,
                                                        DestBuffer,
                                                        &lBufSize);

  if (lRetValueVDem42 == RTE_E_GeneralDiagnosticInfo422_DEM_E_WRONG_BUFFERSIZE)
  {
    lRetValueVDem42 = E_NOT_OK;
  }
  return lRetValueVDem42;
}

/**********************************************************************************************************************
 * VDem42_GetEventExtendedDataRecordEx()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, VDEM42_CODE) VDem42_GetEventExtendedDataRecordEx(
                                                                    VDem42_EventIdType EventId,                                                      /* PRQA S 1330 */ /* MD_Rte_1330 */
                                                                    uint8 RecordNumber,
                                                                    P2VAR(uint8, AUTOMATIC, VDEM42_APPL_VAR) DestBuffer,
                                                                    P2VAR(uint16, AUTOMATIC, VDEM42_APPL_VAR) BufSize)
{
  Std_ReturnType lRetValue;
  Std_ReturnType lRetValueVDem42;

  lRetValue = Rte_Call_GeneralEvtInfo43_GetEventExtendedDataRecordEx(EventId,
                                                                     RecordNumber,
                                                                     DestBuffer,
                                                                     BufSize);
  switch (lRetValue)
  {
    case E_OK:
      lRetValueVDem42 = E_OK;
      break;
    case E_NOT_OK:
      lRetValueVDem42 = E_NOT_OK;
      break;
    case RTE_E_GeneralDiagnosticInfo43_DEM_NO_SUCH_ELEMENT:
      /* could be any of the following ASR422 errors:
       *   DEM_E_WRONG_RECORDNUMBER
       *   DEM_E_NODATAAVAILABLE
       * cannot determine which one is the correct one - use generic E_NOT_OK instead
       */
      lRetValueVDem42 = E_NOT_OK;
      break;
    case RTE_E_GeneralDiagnosticInfo43_DEM_BUFFER_TOO_SMALL:
      lRetValueVDem42 = RTE_E_GeneralDiagnosticInfo422_DEM_E_WRONG_BUFFERSIZE;
      break;
    default:
      lRetValueVDem42 = E_NOT_OK;
      break;
  }
  return lRetValueVDem42;
}

/**********************************************************************************************************************
 * VDem42_GetEventFailed()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, VDEM42_CODE) VDem42_GetEventFailed(VDem42_EventIdType EventId,                                                                  /* PRQA S 1330 */ /* MD_Rte_1330 */
                                                        P2VAR(boolean, AUTOMATIC, VDEM42_APPL_VAR) EventFailed)
{
  Std_ReturnType lRetValue;
  Std_ReturnType lRetValueVDem42;

  lRetValue = Rte_Call_GeneralEvtInfo43_GetEventFailed(EventId,
                                                       EventFailed);
  switch (lRetValue)
  {
    case E_OK:
      lRetValueVDem42 = E_OK;
      break;
    case E_NOT_OK:
      lRetValueVDem42 = E_NOT_OK;
      break;
    default:
      lRetValueVDem42 = E_NOT_OK;
      break;
  }
  return lRetValueVDem42;
}

/**********************************************************************************************************************
 * VDem42_GetEventTested()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, VDEM42_CODE) VDem42_GetEventTested(VDem42_EventIdType EventId,                                                                  /* PRQA S 1330 */ /* MD_Rte_1330 */
                                                        P2VAR(boolean, AUTOMATIC, VDEM42_APPL_VAR) EventTested)
{
  Std_ReturnType lRetValue;
  Std_ReturnType lRetValueVDem42;

  lRetValue = Rte_Call_GeneralEvtInfo43_GetEventTested(EventId,
                                                       EventTested);
  switch (lRetValue)
  {
    case E_OK:
      lRetValueVDem42 = E_OK;
      break;
    case E_NOT_OK:
      lRetValueVDem42 = E_NOT_OK;
      break;
    default:
      lRetValueVDem42 = E_NOT_OK;
      break;
  }
  return lRetValueVDem42;
}

/**********************************************************************************************************************
 * VDem42_GetEventFreezeFrameData()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VDEM42_CODE) VDem42_GetEventFreezeFrameData(VDem42_EventIdType EventId,                                                         /* PRQA S 1330 */ /* MD_Rte_1330 */
                                                                 uint8 RecordNumber,
                                                                 boolean ReportTotalRecord,
                                                                 uint16 DataId,
                                                                 P2VAR(uint8, AUTOMATIC, VDEM42_APPL_VAR) DestBuffer)
{
  Std_ReturnType lRetValueVDem42;

  if (ReportTotalRecord == TRUE)
  {
    lRetValueVDem42 = E_NOT_OK;
  }
  else
  {
    uint16 lBufSize = sizeof(Dem_MaxDataValueType);
    lRetValueVDem42 = VDem42_GetEventFreezeFrameDataEx(EventId,
                                                       RecordNumber,
                                                       DataId,
                                                       DestBuffer,
                                                       &lBufSize);

    if (lRetValueVDem42 == RTE_E_GeneralDiagnosticInfo422_DEM_E_WRONG_BUFFERSIZE)
    {
      lRetValueVDem42 = E_NOT_OK;
    }
  }
  return lRetValueVDem42;
}

/**********************************************************************************************************************
 * VDem42_GetEventFreezeFrameDataEx()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, VDEM42_CODE) VDem42_GetEventFreezeFrameDataEx(VDem42_EventIdType EventId,                                                       /* PRQA S 1330 */ /* MD_Rte_1330 */
                                                                   uint8 RecordNumber,
                                                                   uint16 DataId,
                                                                   P2VAR(uint8, AUTOMATIC, VDEM42_APPL_VAR) DestBuffer,
                                                                   P2VAR(uint16, AUTOMATIC, VDEM42_APPL_VAR) BufSize)
{
  Std_ReturnType lRetValue;
  Std_ReturnType lRetValueVDem42;

  lRetValue = Rte_Call_GeneralEvtInfo43_GetEventFreezeFrameDataEx(EventId,
                                                                  RecordNumber,
                                                                  DataId,
                                                                  DestBuffer,
                                                                  BufSize);
  switch (lRetValue)
  {
    case E_OK:
      lRetValueVDem42 = E_OK;
      break;
    case E_NOT_OK:
      lRetValueVDem42 = E_NOT_OK;
      break;
    case RTE_E_GeneralDiagnosticInfo43_DEM_NO_SUCH_ELEMENT:
      /* could be any of the following ASR422 errors:
       *   DEM_E_WRONG_RECORDNUMBER
       *   DEM_E_NODATAAVAILABLE
       *   DEM_E_WRONG_DIDNUMBER
       * cannot determine which one is the correct one - use generic E_NOT_OK instead
       */
      lRetValueVDem42 = E_NOT_OK;
      break;
    case RTE_E_GeneralDiagnosticInfo43_DEM_BUFFER_TOO_SMALL:
      lRetValueVDem42 = RTE_E_GeneralDiagnosticInfo422_DEM_E_WRONG_BUFFERSIZE;
      break;
    default:
      lRetValueVDem42 = E_NOT_OK;
      break;
  }
  return lRetValueVDem42;
}

/**********************************************************************************************************************
 * VDem42_GetEventStatus()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, VDEM42_CODE) VDem42_GetEventStatus(VDem42_EventIdType EventId,                                                                  /* PRQA S 1330 */ /* MD_Rte_1330 */
                                            P2VAR(VDem42_UdsStatusByteType, AUTOMATIC, VDEM42_APPL_VAR) EventStatusByte)
{
  Std_ReturnType lRetValue;
  Std_ReturnType lRetValueVDem42;

  lRetValue = Rte_Call_GeneralEvtInfo43_GetEventUdsStatus(EventId,
                                                          EventStatusByte);

  switch (lRetValue)
  {
    case E_OK:
      lRetValueVDem42 = E_OK;
      break;
    case E_NOT_OK:
      lRetValueVDem42 = E_NOT_OK;
      break;
    default:
      lRetValueVDem42 = E_NOT_OK;
      break;
  }
  return lRetValueVDem42;
}

/**********************************************************************************************************************
 * VDem42_GetFaultDetectionCounter()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, VDEM42_CODE) VDem42_GetFaultDetectionCounter(VDem42_EventIdType EventId,                                                        /* PRQA S 1330 */ /* MD_Rte_1330 */
                                                         P2VAR(sint8, AUTOMATIC, VDEM42_APPL_VAR) FaultDetectionCounter)
{
  Std_ReturnType lRetValue;
  Std_ReturnType lRetValueVDem42;

  lRetValue = Rte_Call_GeneralEvtInfo43_GetFaultDetectionCounter(EventId,
                                                                 FaultDetectionCounter);
  switch (lRetValue)
  {
    case E_OK:
      lRetValueVDem42 = E_OK;
      break;
    case E_NOT_OK:
      lRetValueVDem42 = E_NOT_OK;
      break;
    case RTE_E_GeneralDiagnosticInfo43_DEM_E_NO_FDC_AVAILABLE:
      lRetValueVDem42 = RTE_E_GeneralDiagnosticInfo422_DEM_E_NO_FDC_AVAILABLE;
      break;
    default:
      lRetValueVDem42 = E_NOT_OK;
      break;
  }
  return lRetValueVDem42;
}

#if (VDEM42_CFG_SUPPORT_DTCSUPPRESSION == STD_ON)
/**********************************************************************************************************************
* VDem42_SetDTCSuppression()
*********************************************************************************************************************/
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
FUNC(Std_ReturnType, VDEM42_CODE) VDem42_SetDTCSuppression(uint32 DTC,
                                                           VDem42_DTCFormatType DTCFormat,
                                                           boolean SuppressionStatus)
{
  Std_ReturnType lRetValue;
  Std_ReturnType lStdRetValSelectDTC;

  lStdRetValSelectDTC = Rte_Call_ClearDTC_vDem42_SelectDTC(DTC,
                                                           DTCFormat,
                                                           DEM_DTC_ORIGIN_PRIMARY_MEMORY);
  /* a new DTC was selected so a potentially existing selection for a ClearDTC operation is no longer valid */
  vDem42_ClearDTC_SelectionState.isDTCSelected = FALSE;

  if (lStdRetValSelectDTC != E_OK)
  {
    /* If DTC not in PRIMARY_MEMORY, try to select in SECONDARY_MEMORY */
    lStdRetValSelectDTC = Rte_Call_ClearDTC_vDem42_SelectDTC(DTC, DTCFormat, DEM_DTC_ORIGIN_SECONDARY_MEMORY);
  }

  if (lStdRetValSelectDTC == E_OK)
  {
    Std_ReturnType lStdRetValSetDTCSuppression;

    /* If one of the requests to select the DTC is successful set the suppression for the DTC */
    lStdRetValSetDTCSuppression = Rte_Call_ControlDTCSuppression43_vDem42_SetDTCSuppression(SuppressionStatus);
    if (lStdRetValSetDTCSuppression == E_OK)
    {
      lRetValue = E_OK;
    }
    else
    {
      lRetValue = RTE_E_DTCSuppression422_E_NOT_OK;
    }
  }
  else
  {
    lRetValue = RTE_E_DTCSuppression422_E_NOT_OK;
  }

  return lRetValue;
}
#endif

#if (VDEM42_CFG_SUPPORT_DTCSUPPRESSION == STD_ON)
/**********************************************************************************************************************
* VDem42_GetDTCSuppression()
*********************************************************************************************************************/
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
FUNC(Std_ReturnType, VDEM42_CODE) VDem42_GetDTCSuppression(uint32 DTC,
                                                           VDem42_DTCFormatType DTCFormat,
                                                           P2VAR(boolean, AUTOMATIC, VDEM42_APPL_VAR) SuppressionStatus)
{
  Std_ReturnType lRetValue;
  Std_ReturnType lStdRetValSelectDTC;

  lStdRetValSelectDTC = Rte_Call_ClearDTC_vDem42_SelectDTC(DTC,
                                                           DTCFormat,
                                                           DEM_DTC_ORIGIN_PRIMARY_MEMORY);
  /* a new DTC was selected so a potentially existing selection for a ClearDTC operation is no longer valid */
  vDem42_ClearDTC_SelectionState.isDTCSelected = FALSE;

  if (lStdRetValSelectDTC != E_OK)
  {
    /* If DTC not in PRIMARY_MEMORY, try to select in SECONDARY_MEMORY */
    lStdRetValSelectDTC = Rte_Call_ClearDTC_vDem42_SelectDTC(DTC, DTCFormat, DEM_DTC_ORIGIN_SECONDARY_MEMORY);
  }

  if (lStdRetValSelectDTC == E_OK)
  {
    Std_ReturnType lStdRetValGetDTCSuppression;

    /* If one of the requests to select the DTC is successful get the suppression for the DTC */
    lStdRetValGetDTCSuppression = Rte_Call_ControlDTCSuppression43_vDem42_GetDTCSuppression(SuppressionStatus);
    if (lStdRetValGetDTCSuppression == E_OK)
    {
      lRetValue = E_OK;
    }
    else
    {
      lRetValue = RTE_E_DTCSuppression422_E_NOT_OK;
    }
  }
  else
  {
    lRetValue = RTE_E_DTCSuppression422_E_NOT_OK;
  }

  return lRetValue;
}
#endif

#if (VDEM42_GLOBAL_EVENT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  VDem42_GlobalCbk_StatusChanged()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, vDem42_CODE) VDem42_GeneralCallbackEventUdsStatusChanged(Dem_EventIdType EventId,
                                                                    Dem_UdsStatusByteType EventUdsStatusByteOld,
                                                                    Dem_UdsStatusByteType EventUdsStatusByteNew)
{
  (void)(Rte_Call_GeneralCBStatusEvt422_EventStatusChanged(EventId,
                                                           EventUdsStatusByteOld,
                                                           EventUdsStatusByteNew));
}
#endif

#define VDEM42_STOP_SEC_CODE
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ----------------------------------------------
 ~&&&   MISRA
---------------------------------------------- */
/* module specific MISRA deviations:
   MD_vDem42_3112:
     Description: Rule 14.2
                  All non-null statements shall either
                    (i)  have at least one side-effect however executed, or
                    (ii) cause control flow to change.
     Reason:      This statement is used to avoid warnings caused by unused parameters. Parameters are defined by
                  standardized API requirements, and not needed in case a feature is disabled by configuration.
                  It is either impossible due to API standardization or necessary code duplication (severe maintenance
                  increase) to provide feature dependent APIs with different signatures.
     Risk:        Unavoidable compiler warning or error because of either unused statements or unused parameter.
     Prevention:  None.

   MD_vDem42_Design_3673:
     Description: Rule 16.7
                  A pointer parameter in a function prototype should be declared as pointer to const if the pointer is
                  not used to modify the addressed object.
     Reason:      The API has to be compatible to a common prototype, defined by module's design to serve generic
                  purposes.
     Risk:        None.
     Prevention:  None.
*/

/* ----------------------------------------------
 ~&&&   COVERAGE
---------------------------------------------- */
/* COV_JUSTIFICATION_BEGIN

\ID COV_VDEM42_MACRO_OVERRIDE
  \ACCEPT TX
  \ACCEPT XF
  \REASON The value of a macro may be overridden by user config for test purposes. Since this is not officially
          supported, it is not covered by the test suite.

COV_JUSTIFICATION_END */

/**********************************************************************************************************************
 *  END OF FILE: vDem42.c
 *********************************************************************************************************************/
