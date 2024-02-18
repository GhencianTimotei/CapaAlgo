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
/*! \addtogroup Dem_ClientAccessIF
 *  \{
 *  \file       Dem_ClientAccessIF_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) Implementation file
 *  \details    Implementation of ClientAccess subcomponent
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_CLIENTACCESSIF_IMPLEMENTATION_H)
#define DEM_CLIENTACCESSIF_IMPLEMENTATION_H

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
#include "Dem_ClientAccessIF_Interface.h"

/* Includes to access public functions belonging to other (top level)/ (logical)/- units to be used by this Unit */
/* ------------------------------------------------------------------------- */
#include "Dem_Infrastructure_Interface.h"
#include "Dem_Core_Interface.h"
#include "Dem_FaultMemory_Interface.h"
#include "Dem_RecordReader_Interface.h"
#include "Dem_FilterData_Interface.h"
#include "Dem_FreezeFrameIterator_Interface.h"
#include "Dem_DTCSelector_Interface.h"
#include "Dem_DTCReporting_Interface.h"
#include "Dem_ClearDTC_Interface.h"
#include "Dem_ClientData_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/

#define DEM_START_SEC_CONST_8BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Mapping table DtcOrigin -> MemoryId */
DEM_LOCAL CONST(uint8, DEM_CONST) Dem_Client_ClientAccess_MemoryIdMapping[6] =                                                          /* PRQA S 3218 */ /* MD_DEM_8.7 */
{
  /* 0: Invalid */
  DEM_CFG_MEMORYID_INVALID,
  /* DEM_DTC_ORIGIN_PRIMARY_MEMORY */
  DEM_CFG_MEMORYID_PRIMARY,
  /* DEM_DTC_ORIGIN_MIRROR_MEMORY */
  DEM_CFG_MEMORYID_MIRROR,
  /* DEM_DTC_ORIGIN_PERMANENT_MEMORY */
  DEM_CFG_MEMORYID_PERMANENT,
  /* DEM_DTC_ORIGIN_OBD_RELEVANT_MEMORY */
  DEM_CFG_MEMORYID_INVALID,
  /* DEM_DTC_ORIGIN_SECONDARY_MEMORY */
  DEM_CFG_MEMORYID_SECONDARY
};

#define DEM_STOP_SEC_CONST_8BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */


/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DEFINITIONS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \addtogroup Dem_ClientAccess_Public
 * \{
 */

/* ****************************************************************************
 % Dem_Client_ClientAccess_MemoryIdFromOrigin
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Client_ClientAccess_MemoryIdFromOrigin(
  CONST(Dem_DTCOriginType, AUTOMATIC)  DTCOrigin
  )
{
  return Dem_Client_ClientAccess_MemoryIdMapping[DTCOrigin];
}

/* ****************************************************************************
 % Dem_Client_ClientAccess_GlobalClientCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Client_ClientAccess_GlobalClientCount(
  void
  )
{
  return  Dem_Cfg_GetSizeOfClientTable();
}
       
/* ****************************************************************************
 % Dem_Client_ClientAccess_TestSelectorValid
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Client_ClientAccess_TestSelectorValid(                                                                                              /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  ClientId
  )
{
  return (boolean)(Dem_ClientData_GetDTCSelector(ClientId) != DEM_CFG_DTCSELECTOR_INVALID);
}

/* ****************************************************************************
 % Dem_Client_ClientAccess_TestClientIdValid
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Client_ClientAccess_TestClientIdValid(                                                                                              /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  ClientId
)
{
  return (boolean)(ClientId < Dem_Client_ClientAccess_GlobalClientCount());
}

/* ****************************************************************************
 % Dem_Client_ClientAccess_SelectDTC
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
Dem_Client_ClientAccess_SelectDTC(
  CONST(uint8, AUTOMATIC)  ClientId,
  CONST(uint32, AUTOMATIC)  DTC,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat,
  CONST(Dem_DTCOriginType, AUTOMATIC)  DTCOrigin
  )
{
  Dem_DTCSelector_HandleType lDTCSelectorId;
  Dem_ClearDTC_HandleType lClearDTCHandle;

  lClearDTCHandle = Dem_ClientData_GetClearDTCStatusHandle(ClientId);
  /* Client is configured to clear DTCs */
  if (lClearDTCHandle != DEM_CLEARDTC_HANDLE_INVALID)
  {
    Dem_ClearDTC_ResetClearStatus(lClearDTCHandle);
  }

  lDTCSelectorId = Dem_ClientData_GetDTCSelector(ClientId);
  if (lDTCSelectorId != DEM_CFG_DTCSELECTOR_INVALID)
  {
    uint8 lMemoryId;
    Dem_DTCOriginType lMappedOrigin;
    if (DTCOrigin == DEM_DTC_ORIGIN_OBD_RELEVANT_MEMORY)
    {
      lMappedOrigin = DEM_DTC_ORIGIN_PRIMARY_MEMORY;
    }
    else
    {
      lMappedOrigin = DTCOrigin;
    }
    lMemoryId = Dem_Client_ClientAccess_MemoryIdFromOrigin(lMappedOrigin);
    Dem_DTCSelector_SelectDTC(lDTCSelectorId, DTC, DTCFormat, DTCOrigin, lMemoryId);
  }
}

/* ****************************************************************************
 % Dem_Client_ClientAccess_GetSelectionResult
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTCSelector_ResultType, DEM_CODE)
Dem_Client_ClientAccess_GetSelectionResult(
  CONST(uint8, AUTOMATIC) ClientId
  )
{
  Dem_DTCSelector_HandleType lDTCSelectorId;
  Dem_DTCSelector_ResultType lReturnValue;

  lDTCSelectorId = Dem_ClientData_GetDTCSelector(ClientId);
  if (lDTCSelectorId != DEM_CFG_DTCSELECTOR_INVALID)
  {
    lReturnValue = Dem_DTCSelector_GetSelectionResult(lDTCSelectorId);
  }
  else
  {
    lReturnValue = DEM_DTCSELECTOR_SELECTION_INIT;
  }

  return lReturnValue;
}

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Client_ClientAccess_GetSelectedMemoryId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Client_ClientAccess_GetSelectedMemoryId(
  CONST(uint8, AUTOMATIC) ClientId
  )
{
  Dem_DTCSelector_HandleType lDTCSelectorId;
  uint8 lReturnValue;

  lDTCSelectorId = Dem_ClientData_GetDTCSelector(ClientId);
  if (lDTCSelectorId != DEM_CFG_DTCSELECTOR_INVALID)
  {
    lReturnValue = Dem_DTCSelector_GetMemoryId(lDTCSelectorId);
  }
  else
  {
    lReturnValue = DEM_CFG_MEMORYID_INVALID;
  }

  return lReturnValue;
}
#endif

/* ****************************************************************************
 % Dem_Client_ClientAccess_GetSelectedEventId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Client_ClientAccess_GetSelectedEventId(
  CONST(uint8, AUTOMATIC) ClientId
  )
{
  Dem_DTCSelector_HandleType lDTCSelectorId;
  Dem_EventIdType lReturnValue;

  lDTCSelectorId = Dem_ClientData_GetDTCSelector(ClientId);
  if (lDTCSelectorId != DEM_CFG_DTCSELECTOR_INVALID)
  {
    lReturnValue = Dem_DTCSelector_GetEventId(lDTCSelectorId);
  }
  else
  {
    lReturnValue = DEM_EVENT_INVALID;
  }

  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Client_ClientAccess_TestSelectDTCLocked
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
Dem_Client_ClientAccess_TestSelectDTCLocked(                                                                                            /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC) ClientId
  )
{
  Dem_DTCSelector_HandleType lDTCSelectorId;
  boolean lReturnValue;

  lDTCSelectorId = Dem_ClientData_GetDTCSelector(ClientId);
  if (lDTCSelectorId != DEM_CFG_DTCSELECTOR_INVALID)
  {
    lReturnValue = Dem_DTCSelector_TestSelectDTCLocked(lDTCSelectorId);
  }
  else
  {
    lReturnValue = FALSE;
  }

  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Client_ClientAccess_TestFilterValid
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Client_ClientAccess_TestFilterValid(                                                                                                /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  ClientId
  )
{
  return (boolean) (Dem_ClientData_GetFilterId(ClientId) != DEM_CFG_FILTER_INVALID);
}

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Client_ClientAccess_SetDTCFilter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Client_ClientAccess_SetDTCFilter(
  CONST(uint8, AUTOMATIC)  ClientId,
  CONST(uint8, AUTOMATIC)  DTCStatusMask,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat,
  CONST(Dem_DTCOriginType, AUTOMATIC)  DTCOrigin,
  CONST(boolean, AUTOMATIC)  FilterWithSeverity,
  CONST(Dem_DTCSeverityType, AUTOMATIC)  DTCSeverityMask,
  CONST(boolean, AUTOMATIC)  FilterForFDC
  )
{
  Std_ReturnType lReturnValue;
  Dem_FilterData_HandleType lFilterId;

  lFilterId = Dem_ClientData_GetFilterId(ClientId);

  if (lFilterId != DEM_CFG_FILTER_INVALID)
  {
    Dem_DTCOriginType lMappedOrigin;
    boolean lFilterEmissionRelatedDtcs;
    uint8 lMemoryId;

    if (DTCOrigin == DEM_DTC_ORIGIN_OBD_RELEVANT_MEMORY)
    {
      lMappedOrigin = DEM_DTC_ORIGIN_PRIMARY_MEMORY;
      lFilterEmissionRelatedDtcs = TRUE;
    }
    else
    {
      lMappedOrigin = DTCOrigin;
      lFilterEmissionRelatedDtcs = FALSE;
    }

    lMemoryId = Dem_Client_ClientAccess_MemoryIdFromOrigin(lMappedOrigin);
    lReturnValue = Dem_Client_FilterData_SetDTCFilter(lFilterId,
                                               DTCStatusMask,
                                               DTCFormat,
                                               lMemoryId,
                                               lFilterEmissionRelatedDtcs,
                                               FilterWithSeverity,
                                               DTCSeverityMask,
                                               FilterForFDC);
  }
  else
  {
    lReturnValue = E_NOT_OK;
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6060 */ /* MD_MSR_STPAR */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Client_ClientAccess_GetNextFilteredDTC
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Client_ClientAccess_GetNextFilteredDTC(
  CONST(uint8, AUTOMATIC)  ClientId,
  CONSTP2VAR(Dem_FilterData_ResultType, AUTOMATIC, AUTOMATIC)  FilterResult
  )
{
  Std_ReturnType lReturnValue;
  Dem_FilterData_HandleType lFilterId;

  lFilterId = Dem_ClientData_GetFilterId(ClientId);

  if (lFilterId != DEM_CFG_FILTER_INVALID)
  {
    lReturnValue = Dem_Client_FilterData_GetNextFilteredDTC(lFilterId, FilterResult);                                                   /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }
  else
  {
    lReturnValue = E_NOT_OK;
  }
  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Client_ClientAccess_TestDTCFilterSet
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Client_ClientAccess_TestDTCFilterSet(                                                                                               /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  ClientId
  )
{
  boolean lReturnValue;
  Dem_FilterData_HandleType lFilterId;

  lFilterId = Dem_ClientData_GetFilterId(ClientId);

  if (lFilterId != DEM_CFG_FILTER_INVALID)
  {
    lReturnValue = Dem_Client_FilterData_TestFilterSet(lFilterId, DEM_FILTERDATA_FILTER_DTC);
  }
  else
  {
    lReturnValue = FALSE;
  }

  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Client_ClientAccess_TestDTCFilterWithFDCSet
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
  Dem_Client_ClientAccess_TestDTCFilterWithFDCSet(                                                                                      /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  ClientId
  )
{
  boolean lReturnValue;
  Dem_FilterData_HandleType lFilterId;

  lFilterId = Dem_ClientData_GetFilterId(ClientId);

  if (lFilterId != DEM_CFG_FILTER_INVALID)
  {
    lReturnValue = (boolean)((Dem_Client_FilterData_TestFilterSet(lFilterId, DEM_FILTERDATA_FILTER_DTC) == TRUE)
                     && (Dem_Client_FilterData_TestUseFdc(lFilterId) == TRUE));                                                         /* PRQA S 3415 */ /* MD_DEM_13.5_cf */ 
  }
  else
  {
    lReturnValue = FALSE;
  }

  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Client_ClientAccess_TestDTCFilterWithSeveritySet
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Client_ClientAccess_TestDTCFilterWithSeveritySet(                                                                                   /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  ClientId
  )
{
  boolean lReturnValue;
  Dem_FilterData_HandleType lFilterId;

  lFilterId = Dem_ClientData_GetFilterId(ClientId);

  if (lFilterId != DEM_CFG_FILTER_INVALID)
  {
    lReturnValue = (boolean)((Dem_Client_FilterData_TestFilterSet(lFilterId, DEM_FILTERDATA_FILTER_DTC) == TRUE)
                    && (Dem_Client_FilterData_TestUseSeverity(lFilterId) == TRUE));                                                     /* PRQA S 3415 */ /* MD_DEM_13.5_cf */ 
  }
  else
  {
    lReturnValue = FALSE;
  }

  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
/* ****************************************************************************
 % Dem_Client_ClientAccess_TestJ1939DTCFilterSet
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Client_ClientAccess_TestJ1939DTCFilterSet(                                                                                          /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  ClientId
  )
{
  boolean lReturnValue;
  Dem_FilterData_HandleType lFilterId;

  lFilterId = Dem_ClientData_GetFilterId(ClientId);

  if (lFilterId != DEM_CFG_FILTER_INVALID)
  {
    lReturnValue = Dem_Client_FilterData_TestFilterSet(lFilterId, DEM_FILTERDATA_FILTER_J1939DTC);
  }
  else
  {
    lReturnValue = FALSE;
  }

  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
/* ****************************************************************************
 % Dem_Client_ClientAccess_TestJ1939DTCFilterWithLampStatusSet
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Client_ClientAccess_TestJ1939DTCFilterWithLampStatusSet(                                                                            /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  ClientId
  )
{
  boolean lReturnValue;
  Dem_FilterData_HandleType lFilterId;

  lFilterId = Dem_ClientData_GetFilterId(ClientId);

  if (lFilterId != DEM_CFG_FILTER_INVALID)
  {
    lReturnValue = Dem_Client_FilterData_TestFilterSet(lFilterId, DEM_FILTERDATA_FILTER_J1939DTCLAMP);
  }
  else
  {
    lReturnValue = FALSE;
  }

  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
/* ****************************************************************************
 % Dem_Client_ClientAccess_TestJ1939FreezeFrameFilterSet
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Client_ClientAccess_TestJ1939FreezeFrameFilterSet(                                                                                  /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  ClientId
  )
{
  boolean lReturnValue;
  Dem_FreezeFrameIterator_HandleType lFreezeFrameIteratorId;

  lFreezeFrameIteratorId = Dem_ClientData_GetFreezeFrameIteratorId(ClientId);

  if (lFreezeFrameIteratorId != DEM_CFG_FREEZEFRAMEITERATOR_INVALID)
  {
    lReturnValue = Dem_FreezeFrameIterator_TestJ1939FreezeFrameFilterSet(lFreezeFrameIteratorId);
  }
  else
  {
    lReturnValue = FALSE;
  }

  return lReturnValue;
}
#endif

/* ****************************************************************************
 % Dem_Client_ClientAccess_Init
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
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Client_ClientAccess_Init(
  void
  )
{
  uint8 lClientId;
  for (lClientId = 0u; 
       lClientId < Dem_Client_ClientAccess_GlobalClientCount(); 
       ++lClientId)
  {
    Dem_DTCSelector_HandleType lDTCSelectorId;
#if (DEM_CFG_SUPPORT_DCM == STD_ON)
    Dem_DTCReadoutBuffer_HandleType lReadoutBufferId;
#endif
#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) || (DEM_CFG_SUPPORT_J1939_DM31 == STD_ON) || (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON) )
    Dem_FilterData_HandleType lFilterId;
#endif
#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) ||(DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON) )
    Dem_FreezeFrameIterator_HandleType lFreezeFrameIteratorId;
#endif
    Dem_Dcm_ERec_0x1916_RecordNumberFilter_HandleType lExtendedDataFilterId;


    lDTCSelectorId = Dem_ClientData_GetDTCSelector(lClientId);
#if (DEM_CFG_SUPPORT_DCM == STD_ON)
    lReadoutBufferId = Dem_ClientData_GetReadoutBufferId(lClientId);
#endif
#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) || (DEM_CFG_SUPPORT_J1939_DM31 == STD_ON) || (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON) )
    lFilterId = Dem_ClientData_GetFilterId(lClientId);
#endif
#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) ||(DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON) )
    lFreezeFrameIteratorId = Dem_ClientData_GetFreezeFrameIteratorId(lClientId);
#endif

    if (lDTCSelectorId != DEM_CFG_DTCSELECTOR_INVALID)
    {
      Dem_DTCSelector_InitDefault(lDTCSelectorId);
    }

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
    if (lReadoutBufferId != DEM_CFG_READOUTBUFFER_INVALID)
    {
      Dem_DTCReadoutBuffer_Init(lReadoutBufferId);
    }
#endif

#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) || (DEM_CFG_SUPPORT_J1939_DM31 == STD_ON) || (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON) )
    if (lFilterId != DEM_CFG_FILTER_INVALID)
    {
      Dem_Client_FilterData_InitDefault(lFilterId);
    }
#endif

#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) ||(DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON) )
    if (lFreezeFrameIteratorId != DEM_CFG_FREEZEFRAMEITERATOR_INVALID)
    {
      Dem_FreezeFrameIterator_InitDefault(lFreezeFrameIteratorId);
    }
#endif

    if (Dem_Dcm_ERec_0x1916_IsService19_16Enabled() == TRUE)
    {
      lExtendedDataFilterId = Dem_ClientData_GetExtendedDataFilterId(lClientId);
      if (lExtendedDataFilterId != DEM_CFG_FILTER_INVALID)
      {
        Dem_Dcm_ERec_0x1916_InitERecNumberFilter(lExtendedDataFilterId);
      }
    }
  }

  Dem_ClearDTC_Init();
  return;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Client_ClientAccess_TestReadoutBufferValid
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Client_ClientAccess_TestReadoutBufferValid(                                                                                         /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  ClientId
  )
{
  return (boolean) (Dem_ClientData_GetReadoutBufferId(ClientId) != DEM_CFG_READOUTBUFFER_INVALID);
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Client_ClientAccess_GetReadoutBuffer
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTCReadoutBuffer_HandleType, DEM_CODE)
Dem_Client_ClientAccess_GetReadoutBuffer(
  CONST(uint8, AUTOMATIC)  ClientId
  )
{
  return Dem_ClientData_GetReadoutBufferId(ClientId);
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Client_ClientAccess_TestDTCRecordUpdateRequested
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Client_ClientAccess_TestDTCRecordUpdateRequested(                                                                                   /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  ClientId
  )
{
  boolean lReturnValue;
  Dem_DTCReadoutBuffer_HandleType lReadoutBufferId;

  lReadoutBufferId = Dem_ClientData_GetReadoutBufferId(ClientId);

  if (lReadoutBufferId != DEM_CFG_READOUTBUFFER_INVALID)
  {
    lReturnValue = Dem_DTCReadoutBuffer_TestDataRequested(lReadoutBufferId);
  }
  else
  {
    lReturnValue = FALSE;
  }

  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Client_ClientAccess_TestDTCRecordUpdateDisabled
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Client_ClientAccess_TestDTCRecordUpdateDisabled(
  CONST(uint8, AUTOMATIC)  ClientId
  )
{
  boolean lReturnValue;
  Dem_DTCReadoutBuffer_HandleType lReadoutBufferId;

  lReadoutBufferId = Dem_ClientData_GetReadoutBufferId(ClientId);

  if (lReadoutBufferId != DEM_CFG_READOUTBUFFER_INVALID)
  {
    lReturnValue = Dem_DTCReadoutBuffer_TestResultReady(lReadoutBufferId);
  }
  else
  {
    lReturnValue = FALSE;
  }

  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Client_ClientAccess_TestSnapshotRecordSelected
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Client_ClientAccess_TestSnapshotRecordSelected(                                                                                     /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  ClientId
  )
{
  boolean lReturnValue;
  Dem_DTCReadoutBuffer_HandleType lReadoutBufferId;

  lReadoutBufferId = Dem_ClientData_GetReadoutBufferId(ClientId);

  if (lReadoutBufferId != DEM_CFG_READOUTBUFFER_INVALID)
  {
    lReturnValue = Dem_DTCReadoutBuffer_TestSnapshotRecordSelected(lReadoutBufferId);
  }
  else
  {
    lReturnValue = FALSE;
  }

  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Client_ClientAccess_TestExtendedRecordSelected
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Client_ClientAccess_TestExtendedRecordSelected(                                                                                     /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  ClientId
  )
{
  boolean lReturnValue;
  Dem_DTCReadoutBuffer_HandleType lReadoutBufferId;

  lReadoutBufferId = Dem_ClientData_GetReadoutBufferId(ClientId);

  if (lReadoutBufferId != DEM_CFG_READOUTBUFFER_INVALID)
  {
    lReturnValue = Dem_DTCReadoutBuffer_TestExtendedRecordSelected(lReadoutBufferId);
  }
  else
  {
    lReturnValue = FALSE;
  }

  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Client_ClientAccess_DisableDTCRecordUpdate
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
Dem_Client_ClientAccess_DisableDTCRecordUpdate(
  CONST(uint8, AUTOMATIC) ClientId
  )
{
  Std_ReturnType lReturnValue;
  Dem_DTCSelector_ResultType lSelectionResult;

  lReturnValue = E_NOT_OK;
  lSelectionResult = Dem_Client_ClientAccess_GetSelectionResult(ClientId);
  if (lSelectionResult == DEM_DTCSELECTOR_SELECTION_DTC)
  {
    Dem_EventIdType lEventId;
    /* get event id from selectDTC */
    lEventId = Dem_Client_ClientAccess_GetSelectedEventId(ClientId);
    Dem_Internal_AssertReturnValue(lEventId != DEM_EVENT_INVALID, DEM_E_INCONSISTENT_STATE, E_NOT_OK)

    if (Dem_DTC_TestSuppressionOnDtcRetrieval(lEventId) == FALSE)
    {
      uint8 lMemoryId;
      Dem_DTCReadoutBuffer_HandleType lReadoutBufferId;

      lMemoryId = Dem_Client_ClientAccess_GetSelectedMemoryId(ClientId);
      Dem_Internal_AssertReturnValue(lMemoryId != DEM_CFG_MEMORYID_INVALID, DEM_E_INCONSISTENT_STATE, E_NOT_OK)

      lReadoutBufferId = Dem_ClientData_GetReadoutBufferId(ClientId);
      if (lReadoutBufferId != DEM_CFG_READOUTBUFFER_INVALID)
      {
        Dem_DTCSelector_HandleType lSelector;
        lSelector = Dem_ClientData_GetDTCSelector(ClientId);
        lReturnValue = Dem_DTCReadoutBuffer_CheckAndSetState(lReadoutBufferId, lEventId, lMemoryId, lSelector);
      }
    }
    else
    {
      lReturnValue = DEM_WRONG_DTC;
    }
  }
  else
  {
    /* missing SelectDTC call or incorrect arguments in that call */
    switch (lSelectionResult)
    {
      case DEM_DTCSELECTOR_SELECTION_GROUP:
      case DEM_DTCSELECTOR_SELECTION_ALL_DTCS:
      case DEM_DTCSELECTOR_SELECTION_NO_MATCH:
        lReturnValue = DEM_WRONG_DTC;
        break;
      case DEM_DTCSELECTOR_SELECTION_WRONG_ORIGIN:
        lReturnValue = DEM_WRONG_DTCORIGIN;
        break;
      case DEM_DTCSELECTOR_SELECTION_INIT:
      default:                                                                                                                   /* PRQA S 2016 */ /* MD_MSR_EmptyClause */
        /* ReturnValue E_NOT_OK */
        break;
    }
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Client_ClientAccess_EnableDTCRecordUpdate
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
Dem_Client_ClientAccess_EnableDTCRecordUpdate(
  CONST(uint8, AUTOMATIC) ClientId
  )
{
  Std_ReturnType lReturnValue;
  Dem_DTCReadoutBuffer_HandleType lReadoutBufferId;
  Dem_DTCSelector_HandleType lSelector;

  lReturnValue = E_NOT_OK;

  lReadoutBufferId = Dem_ClientData_GetReadoutBufferId(ClientId);
  lSelector = Dem_ClientData_GetDTCSelector(ClientId);

  if (lReadoutBufferId != DEM_CFG_READOUTBUFFER_INVALID)
  {
    Dem_DTCReadoutBuffer_FreeBuffer(lReadoutBufferId, lSelector);
    lReturnValue = E_OK;
  }

  return lReturnValue;
}
#endif

/* ****************************************************************************
 % Dem_Client_ClientAccess_FillDTCReadoutBufferData
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Client_ClientAccess_FillDTCReadoutBufferData(
  void
  )
{
#if (DEM_CFG_SUPPORT_DCM == STD_ON)
  uint8 lClientId;

  for (lClientId = 0u; 
       lClientId < Dem_Client_ClientAccess_GlobalClientCount(); 
       ++lClientId)
  {
    Dem_DTCReadoutBuffer_HandleType lReadoutBufferId;
    Dem_DTCSelector_HandleType lSelector;

    lReadoutBufferId = Dem_ClientData_GetReadoutBufferId(lClientId);
    lSelector = Dem_ClientData_GetDTCSelector(lClientId);

#if (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
    if (Dem_DTCReadoutBuffer_TestCombinedEventSelected(lReadoutBufferId) == TRUE)
    {
      Dem_DTCReadoutBuffer_FillData_CombinedEvent(lReadoutBufferId, lSelector);
    }
    else
#endif
    {
      Dem_DTCReadoutBuffer_FillData_NormalEvent(lReadoutBufferId, lSelector);
    }
  }
#endif
}

/* ****************************************************************************
 % Dem_Client_ClientAccess_ClearDTC
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
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE) Dem_Client_ClientAccess_ClearDTC(
  CONST(uint8, AUTOMATIC) ClientId
  )
{
  Std_ReturnType lReturnValue;
  Dem_ClearDTC_HandleType lClearDTCHandle;
  Dem_ClearDTC_StatusType lClearDTCStatus;

  lReturnValue = DEM_CLEAR_FAILED;

  lClearDTCHandle = Dem_ClientData_GetClearDTCStatusHandle(ClientId);
  /* Client is configured to clear DTCs */
  if (lClearDTCHandle != DEM_CLEARDTC_HANDLE_INVALID)
  {
    lClearDTCStatus = Dem_ClearDTC_GetClearStatus(lClearDTCHandle);
    switch (lClearDTCStatus)
    {
    case DEM_CLEARDTC_STATUS_IDLE:
    {
      Dem_DTCSelector_HandleType lSelector;
      lSelector = Dem_ClientData_GetDTCSelector(ClientId);
      lReturnValue = Dem_ClearDTC_StartClear(lClearDTCHandle, lSelector);
    }
    break;
    case DEM_CLEARDTC_STATUS_PENDING:
      lReturnValue = DEM_PENDING;
      break;
    case DEM_CLEARDTC_STATUS_DONE:
      Dem_ClearDTC_ResetClearStatus(lClearDTCHandle);
      lReturnValue = E_OK;
      break;
    case DEM_CLEARDTC_STATUS_FAILED:
      Dem_ClearDTC_ResetClearStatus(lClearDTCHandle);
      lReturnValue = DEM_CLEAR_FAILED;
      break;
    case DEM_CLEARDTC_STATUS_NV_ERROR:
      Dem_ClearDTC_ResetClearStatus(lClearDTCHandle);
      lReturnValue = DEM_CLEAR_MEMORY_ERROR;
      break;
    default:                                                                                                                     /* PRQA S 2016 */ /* MD_MSR_EmptyClause */
      /* return DEM_CLEAR_FAILED */
      break;
    }
  }
  return lReturnValue;
}

#if (DEM_CFG_SUPPORT_J1939_CLEAR_DTC == STD_ON) 
/* ****************************************************************************
 % Dem_Client_ClientAccess_J1939ClearDTC
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
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE) 
Dem_Client_ClientAccess_J1939ClearDTC(
  CONST(uint8, AUTOMATIC)  ClientId,
  CONST(uint8, AUTOMATIC)  DTCTypeFilter,
  CONST(Dem_DTCOriginType, AUTOMATIC)  DTCOrigin
  )
{
  Std_ReturnType lReturnValue;
  Dem_ClearDTC_HandleType lClearDTCHandle;

  lReturnValue = DEM_CLEAR_FAILED;

  lClearDTCHandle = Dem_ClientData_GetClearDTCStatusHandle(ClientId);
  /* Client is configured to clear DTCs */
  if (lClearDTCHandle != DEM_CLEARDTC_HANDLE_INVALID)
  {
    Dem_ClearDTC_StatusType lClearDTCStatus;

    lClearDTCStatus = Dem_ClearDTC_GetClearStatus(lClearDTCHandle);
    switch (lClearDTCStatus)
    {
    case DEM_CLEARDTC_STATUS_IDLE:
      if (Dem_Client_ClientAccess_TestNodeValid(ClientId) == TRUE)
      {
        Dem_DTCSelector_HandleType lSelector;
        lSelector = Dem_ClientData_GetDTCSelector(ClientId);
        (void)Dem_Client_ClientAccess_SelectDTC(ClientId, DEM_DTC_GROUP_ALL_DTCS, DEM_DTC_FORMAT_J1939, DTCOrigin);
        if (Dem_Client_ClientAccess_GetSelectionResult(ClientId) == DEM_DTCSELECTOR_SELECTION_ALL_DTCS)
        {
          lReturnValue = Dem_ClearDTC_StartClearJ1939(lClearDTCHandle, lSelector, DTCTypeFilter, Dem_Client_ClientAccess_GetNode(ClientId));
        }
        else
        {
          lReturnValue = DEM_WRONG_DTCORIGIN;
        }
      }
      else
      {
        lReturnValue = DEM_CLEAR_FAILED;
      }
      break;
    case DEM_CLEARDTC_STATUS_PENDING:
      lReturnValue = DEM_PENDING;
      break;
    case DEM_CLEARDTC_STATUS_DONE:
      Dem_ClearDTC_ResetClearStatus(lClearDTCHandle);
      lReturnValue = E_OK;
      break;
    case DEM_CLEARDTC_STATUS_FAILED:
      Dem_ClearDTC_ResetClearStatus(lClearDTCHandle);
      lReturnValue = DEM_CLEAR_FAILED;
      break;
    default:                                                                                                                     /* PRQA S 2016 */ /* MD_MSR_EmptyClause */
      /* return DEM_CLEAR_FAILED */
      break;
    }
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) || (DEM_CFG_SUPPORT_J1939 == STD_ON) )
/* ****************************************************************************
 % Dem_Client_ClientAccess_TestFreezeFrameIteratorValid
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Client_ClientAccess_TestFreezeFrameIteratorValid(                                                                                   /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  ClientId
  )
{
  return (boolean) (Dem_ClientData_GetFreezeFrameIteratorId(ClientId) != DEM_CFG_FREEZEFRAMEITERATOR_INVALID);
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Client_ClientAccess_TestFreezeFrameFilterSet
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Client_ClientAccess_TestFreezeFrameFilterSet(                                                                                       /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  ClientId
  )
{
  boolean lReturnValue;
  Dem_FreezeFrameIterator_HandleType lFreezeFrameIteratorId;

  lFreezeFrameIteratorId = Dem_ClientData_GetFreezeFrameIteratorId(ClientId);

  if (lFreezeFrameIteratorId != DEM_CFG_FREEZEFRAMEITERATOR_INVALID)
  {
    lReturnValue = Dem_FreezeFrameIterator_TestFilterSet(lFreezeFrameIteratorId);
  }
  else
  {
    lReturnValue = FALSE;
  }

  return lReturnValue;
}
#endif

#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) \
   && ((DEM_CFG_SUPPORT_SRECS == STD_ON) || (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)))
/* ****************************************************************************
 % Dem_Client_ClientAccess_StartFreezeFrameIterator
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
Dem_Client_ClientAccess_StartFreezeFrameIterator(
  CONST(uint8, AUTOMATIC)  ClientId,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat,
  CONSTP2VAR(uint16, AUTOMATIC, DEM_DCM_DATA)  NumberOfFilteredRecords
  )
{
  Std_ReturnType lReturnValue;
  Dem_FreezeFrameIterator_HandleType lFreezeFrameIteratorId;

  lFreezeFrameIteratorId = Dem_ClientData_GetFreezeFrameIteratorId(ClientId);
  if (lFreezeFrameIteratorId != DEM_CFG_FREEZEFRAMEITERATOR_INVALID)
  {
    Dem_Cfg_MemoryIndexType               lFirstIndex;
    uint16                                lRecordCount;
    Dem_FreezeFrameIterator_DTCFormatType lDtcFormat;

    /* Count stored snapshot records in primary memory to prevent concurrent modification
    of the chrono index to have an effect on the iteration */
    lFirstIndex = Dem_Memory_GetFirstMemoryIndex(DEM_CFG_MEMORYID_PRIMARY);
    lDtcFormat = DEM_FREEZEFRAMEITERATOR_DTCFORMAT_INIT;

    if (DTCFormat == DEM_DTC_FORMAT_UDS)
    { /* Set filter for output format of DTCs to UDS */
      lDtcFormat = DEM_FREEZEFRAMEITERATOR_DTCFORMAT_UDS;
    }
    else
    if ( (Dem_Cfg_IsObdIISupportedInVariant() == TRUE) &&
         (DTCFormat == DEM_DTC_FORMAT_OBD) )
    { /* Set filter for output format of DTCs to OBD */
      lDtcFormat = DEM_FREEZEFRAMEITERATOR_DTCFORMAT_OBD;
    }
    else
# if (DEM_CFG_SUPPORT_J1939 == STD_ON)
    if (DTCFormat == DEM_DTC_FORMAT_J1939)
    { /* Set filter for output format of DTCs to J1939 */
      lDtcFormat = DEM_FREEZEFRAMEITERATOR_DTCFORMAT_J1939;
    }
    else
# endif
    {
      /* Unreachable MISRA case */
    }

    /* Count stored snapshot records */
    lRecordCount = Dem_FreezeFrameIterator_GetNumberOfFreezeFrameRecords();

    /* Prepare iterations to get the data of the records when later calling Dem_GetNextFilteredRecord. */
    Dem_FreezeFrameIterator_StartIterator(lFreezeFrameIteratorId, lDtcFormat, lFirstIndex);

    *NumberOfFilteredRecords = lRecordCount;                                                                                     /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    lReturnValue = E_OK;
  }
  else
  {
    lReturnValue = E_NOT_OK;
  }

  return lReturnValue;
}
#endif /* (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_SRECS == STD_ON) */

#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) \
   && ((DEM_CFG_SUPPORT_SRECS == STD_ON) || (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)))
/* ****************************************************************************
 % Dem_Client_ClientAccess_GetNextFreezeFrameRecord
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
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Client_ClientAccess_GetNextFreezeFrameRecord(
  CONST(uint8, AUTOMATIC)  ClientId,
  CONSTP2VAR(uint32, AUTOMATIC, DEM_DCM_DATA)  DTC,                                                                              /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_8.13 */
  CONSTP2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  RecordNumber                                                                       /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_8.13 */
  )
{
  Dem_FreezeFrameIterator_HandleType  lFreezeFrameIteratorId;
  boolean                             lReturnValue;
  lReturnValue = FALSE;

  lFreezeFrameIteratorId = Dem_ClientData_GetFreezeFrameIteratorId(ClientId);
  if (lFreezeFrameIteratorId != DEM_CFG_FREEZEFRAMEITERATOR_INVALID)
  {
    if (Dem_FreezeFrameIterator_TestFilterSet(lFreezeFrameIteratorId) == TRUE)
    {
      lReturnValue = Dem_FreezeFrameIterator_GetNext(lFreezeFrameIteratorId, DTC, RecordNumber);                                 /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    }
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6030, 6080 */ /* MD_MSR_STCYC, MD_MSR_STMIF */
#endif /* ((DEM_CFG_SUPPORT_DCM == STD_ON) 
          && ((DEM_CFG_SUPPORT_SRECS == STD_ON) || (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON))) */


#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Client_ClientAccess_GetDTCByOccurrenceTime
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
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Client_ClientAccess_GetDTCByOccurrenceTime(
  CONST(Dem_DTCRequestType, AUTOMATIC)  DTCRequest,
  CONSTP2VAR(uint32, AUTOMATIC, DEM_DCM_DATA)  DTC
  )
{
  boolean lReturnValue;
  Dem_EventIdType lEventId;

  lReturnValue = FALSE;
  lEventId = DEM_EVENT_INVALID;

  switch (DTCRequest)
  {
  case DEM_FIRST_FAILED_DTC:
    lEventId = Dem_Statistics_GetFirstFailedEvent();
    break;
  case DEM_MOST_RECENT_FAILED_DTC:
    lEventId = Dem_Statistics_GetMostRecentFailedEvent();
    break;
  case DEM_FIRST_DET_CONFIRMED_DTC:
    lEventId = Dem_Statistics_GetFirstConfirmedEvent();
    break;
  case DEM_MOST_REC_DET_CONFIRMED_DTC:
    lEventId = Dem_Statistics_GetMostRecentConfirmedEvent();
    break;
  default:                                                                                                                       /* PRQA S 2016 */ /* MD_MSR_EmptyClause */
    /* Do nothing */
    break;
  }

  if (lEventId != DEM_EVENT_INVALID)
  { /* Only EventIds with a valid DTC number should be stored in, so the EventId->DTC mapping will return always a valid DTC number */
    if ( (Dem_DTCReporting_TestObdHideOccurrences() == FALSE)
      || (Dem_Cfg_EventSignificance(lEventId) != DEM_CFG_EVENT_SIGNIFICANCE_OCCURRENCE)                                          
      || (Dem_Cfg_EventObdRelated(lEventId) == FALSE))                                                                           
    {
      if (Dem_DTC_TestSuppressionOnDtcRetrieval(lEventId) == FALSE)
      {
        *DTC = Dem_Cfg_EventUdsDtc(lEventId);                                                                                    /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
        lReturnValue = TRUE;
      }
    }
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6030, 6050, 6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Client_ClientAccess_FilterNumberMemory
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Client_ClientAccess_FilterNumberMemory(
  CONST(uint8, AUTOMATIC)  ClientId
  )
{
  uint16 lNumberOfDTCs;
  Dem_FilterData_HandleType lFilterId;
  lFilterId = Dem_ClientData_GetFilterId(ClientId);

  if (lFilterId != DEM_CFG_FILTER_INVALID)
  {
    lNumberOfDTCs =  Dem_Client_FilterData_CountMatchingDTCs(lFilterId);
  }
  else
  {
    lNumberOfDTCs = 0u;
  }
  return lNumberOfDTCs;
}                                                                                                                                /* PRQA S 6010, 6030, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STMIF*/
#endif /* (DEM_CFG_SUPPORT_DCM == STD_ON) */

#if (DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON)
/* ****************************************************************************
 % Dem_Client_ClientAccess_EventChangeDtcSuppression
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Client_ClientAccess_EventChangeDtcSuppression(
  CONST(uint8, AUTOMATIC)  ClientId,
  CONST(boolean, AUTOMATIC)  SuppressionStatus
  )
{
  Dem_EventIdType lEventId;
  lEventId = Dem_Client_ClientAccess_GetSelectedEventId(ClientId);

  return Dem_DTC_ChangeDtcSuppression(lEventId, SuppressionStatus);
}                                                                                                                                /* PRQA S 6010, 6030, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STMIF*/
#endif /* (DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON) */

#if (DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON)
/* ****************************************************************************
 % Dem_Client_ClientAccess_EventRetrieveDtcSuppression
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Client_ClientAccess_EventRetrieveDtcSuppression(
  CONST(uint8, AUTOMATIC)  ClientId,
  CONSTP2VAR(boolean, AUTOMATIC, DEM_APPL_DATA)  SuppressionStatus
  )
{
  Std_ReturnType lReturnValue;
  Dem_EventIdType lEventId;
  lEventId = Dem_Client_ClientAccess_GetSelectedEventId(ClientId);

  if (lEventId != DEM_EVENT_INVALID)
  {
    *SuppressionStatus = Dem_DTC_TestDtcSuppression(lEventId);                                                                   /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    lReturnValue = E_OK;
  }
  else
  {
    lReturnValue = E_NOT_OK;
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6010, 6030, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STMIF*/
#endif /* (DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON) */

#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
/* ****************************************************************************
 % Dem_Client_ClientAccess_TestNodeValid
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Client_ClientAccess_TestNodeValid(                                                                                                  /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  ClientId
  )
{
  return (boolean) (Dem_ClientData_GetNodeId(ClientId) != DEM_CFG_NMNODEID_INVALID);
}
#endif

#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
/* ****************************************************************************
 % Dem_Client_ClientAccess_GetNode
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Client_ClientAccess_GetNode(                                                                                                        /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  ClientId
  )
{
  return Dem_Cfg_FindJ1939NodeFromNmNode(Dem_ClientData_GetNodeId(ClientId));
}
#endif

#if (DEM_CFG_SUPPORT_J1939_DM31 == STD_ON) || (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON)
/* ****************************************************************************
 % Dem_Client_ClientAccess_SetFirstDTCWithLampStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Client_ClientAccess_SetFirstDTCWithLampStatus(
  CONST(uint8, AUTOMATIC)  ClientId
  )
{
  Dem_FilterData_HandleType lFilterId;

  lFilterId = Dem_ClientData_GetFilterId(ClientId);

  if ( (lFilterId != DEM_CFG_FILTER_INVALID) && (Dem_Client_ClientAccess_TestNodeValid(ClientId) == TRUE) )                             
  {
    Dem_Client_FilterData_SetFirstDTCWithLampStatus(lFilterId, Dem_Client_ClientAccess_GetNode(ClientId));
  }
}
#endif

#if (DEM_CFG_SUPPORT_J1939_DM31 == STD_ON) || (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON)
/* ****************************************************************************
 % Dem_Client_ClientAccess_GetNextDTCwithLampStatus
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
Dem_Client_ClientAccess_GetNextDTCwithLampStatus(
  CONST(uint8, AUTOMATIC)  ClientId,
  CONSTP2VAR(Dem_J1939DcmLampStatusType, AUTOMATIC, DEM_J1939DCM_DATA)  LampStatus,
  CONSTP2VAR(uint32, AUTOMATIC, DEM_J1939DCM_DATA)  J1939DTC,
  CONSTP2VAR(uint8, AUTOMATIC, DEM_J1939DCM_DATA)  OccurrenceCounter
  )
{
  Std_ReturnType lReturnValue;
  Dem_FilterData_HandleType lFilterId;

  lReturnValue = DEM_NO_SUCH_ELEMENT;
  lFilterId = Dem_ClientData_GetFilterId(ClientId);

  if (lFilterId != DEM_CFG_FILTER_INVALID)
  {
    if (Dem_Client_FilterData_TestFilterSet(lFilterId, DEM_FILTERDATA_FILTER_J1939DTCLAMP) == TRUE)
    {
      Dem_FilterData_ResultType lFilterResult;
      /* MISRA initialization */
      lFilterResult.DTC = 0u;                                                                                                    /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      lFilterResult.OccurrenceCounter = 0u;                                                                                      /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      (lFilterResult.LampStatus).LampStatus = 0u;                                                                                /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      (lFilterResult.LampStatus).FlashLampStatus = 0u;                                                                           /* SBSW_DEM_POINTER_WRITE_ARGUMENT */

      lReturnValue = Dem_Client_FilterData_GetNextDTCWithLampStatus(lFilterId, &lFilterResult);                                         /* SBSW_DEM_POINTER_FORWARD_STACK */
      if (lReturnValue == E_OK)
      {
        *J1939DTC = lFilterResult.DTC;                                                                                           /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
        *OccurrenceCounter = lFilterResult.OccurrenceCounter;                                                                    /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
        *LampStatus = lFilterResult.LampStatus;                                                                                  /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      }
    }
  }
  return lReturnValue;
}
#endif /* (DEM_CFG_SUPPORT_J1939 == STD_ON) && (DEM_CFG_SUPPORT_J1939_DM31 == STD_ON) */

#if (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON)
/* ****************************************************************************
 % Dem_Client_ClientAccess_SetJ1939DTCFilter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Client_ClientAccess_SetJ1939DTCFilter(
  CONST(uint8, AUTOMATIC)  ClientId,
  CONST(Dem_J1939DcmDTCStatusFilterType, AUTOMATIC)  DTCStatusFilter,
  CONST(Dem_DTCKindType, AUTOMATIC)  DTCKind,
  CONST(Dem_DTCOriginType, AUTOMATIC)  DTCOrigin,
  CONSTP2VAR(Dem_J1939DcmLampStatusType, AUTOMATIC, DEM_J1939DCM_DATA)  LampStatus
  )
{
  Std_ReturnType lReturnValue;
  Dem_FilterData_HandleType lFilterId;

  lFilterId = Dem_ClientData_GetFilterId(ClientId);

  if ( (lFilterId != DEM_CFG_FILTER_INVALID) && (Dem_Client_ClientAccess_TestNodeValid(ClientId) == TRUE) )                             
  {
    lReturnValue = Dem_Client_FilterData_SetJ1939DTCFilter(lFilterId, 
                                                    DTCStatusFilter,
                                                    DTCKind, 
                                                    Dem_Client_ClientAccess_MemoryIdFromOrigin(DTCOrigin),
                                                    Dem_Client_ClientAccess_GetNode(ClientId),
                                                    LampStatus);                                                                 /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }
  else
  {
    lReturnValue = E_NOT_OK;
  }
  return lReturnValue;
}
#endif /* (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON) */

#if (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON)
/* ****************************************************************************
 % Dem_Client_ClientAccess_GetNumberOfFilteredJ1939DTC
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Client_ClientAccess_GetNumberOfFilteredJ1939DTC(
  CONST(uint8, AUTOMATIC)  ClientId
  )
{
  uint16 lNumberOfDTCs;
  Dem_FilterData_HandleType lFilterId;

  lNumberOfDTCs = 0u;
  lFilterId = Dem_ClientData_GetFilterId(ClientId);

  if (lFilterId != DEM_CFG_FILTER_INVALID)
  {
    if (Dem_Client_FilterData_TestFilterSet(lFilterId, DEM_FILTERDATA_FILTER_J1939DTC) == TRUE)
    {
      lNumberOfDTCs = Dem_Client_FilterData_GetNumberOfFilteredJ1939DTC(lFilterId);
    }
  }

  return lNumberOfDTCs;
}
#endif /* (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON) */

#if (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON)
/* ****************************************************************************
 % Dem_Client_ClientAccess_GetNextFilteredJ1939DTC
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
Dem_Client_ClientAccess_GetNextFilteredJ1939DTC(
  CONST(uint8, AUTOMATIC)  ClientId,
  CONSTP2VAR(uint32, AUTOMATIC, DEM_J1939DCM_DATA)  J1939DTC,
  CONSTP2VAR(uint8, AUTOMATIC, DEM_J1939DCM_DATA)  OccurrenceCounter
  )
{
  Std_ReturnType lReturnValue;
  Dem_FilterData_HandleType lFilterId;

  lReturnValue = DEM_NO_SUCH_ELEMENT;
  lFilterId = Dem_ClientData_GetFilterId(ClientId);

  if (lFilterId != DEM_CFG_FILTER_INVALID)
  {
    if (Dem_Client_FilterData_TestFilterSet(lFilterId, DEM_FILTERDATA_FILTER_J1939DTC) == TRUE)
    {
      Dem_FilterData_ResultType lFilterResult;
      lReturnValue = Dem_Client_FilterData_GetNextFilteredJ1939DTC(lFilterId, &lFilterResult);                                          /* SBSW_DEM_POINTER_FORWARD_STACK */
      if (lReturnValue == E_OK)
      {
        *J1939DTC = lFilterResult.DTC;                                                                                           /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
        *OccurrenceCounter = lFilterResult.OccurrenceCounter;                                                                    /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      }
    }
  }

  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_J1939_READINESS1 == STD_ON)
/* ****************************************************************************
 % Dem_Client_ClientAccess_ReadDiagnosticReadiness
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Client_ClientAccess_ReadDiagnosticReadiness(
  CONST(uint8, AUTOMATIC)  ClientId,
  CONSTP2VAR(Dem_J1939DcmDiagnosticReadiness1Type, AUTOMATIC, DEM_J1939DCM_DATA)  DiagnosticReadiness
  )
{
  Std_ReturnType lReturnValue;
  Dem_FilterData_HandleType lFilterId;
  lFilterId = Dem_ClientData_GetFilterId(ClientId);

  if ( (lFilterId != DEM_CFG_FILTER_INVALID) && (Dem_Client_ClientAccess_TestNodeValid(ClientId) == TRUE) )                             
  {
    Dem_Client_FilterData_GetDiagnosticReadiness(lFilterId, Dem_Client_ClientAccess_GetNode(ClientId), DiagnosticReadiness);                   /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    lReturnValue = E_OK;
  }
  else
  {
    lReturnValue = E_NOT_OK;
  }
  return lReturnValue;
}
#endif /* (DEM_CFG_SUPPORT_J1939_READINESS1 == STD_ON) */

#if (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON)
/* ****************************************************************************
 % Dem_Client_ClientAccess_SetJ1939FreezeFrameIterator
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Client_ClientAccess_SetJ1939FreezeFrameIterator(
  CONST(uint8, AUTOMATIC)  ClientId,
  CONST(Dem_J1939DcmSetFreezeFrameFilterType, AUTOMATIC) FreezeFrameKind
  )
{
  Std_ReturnType lReturnValue;
  Dem_FreezeFrameIterator_HandleType lFreezeFrameIteratorId;

  lFreezeFrameIteratorId = Dem_ClientData_GetFreezeFrameIteratorId(ClientId);
  if ( (lFreezeFrameIteratorId != DEM_CFG_FREEZEFRAMEITERATOR_INVALID) && (Dem_Client_ClientAccess_TestNodeValid(ClientId) == TRUE) )   
  {
    lReturnValue = Dem_FreezeFrameIterator_StartJ1939Iterator(lFreezeFrameIteratorId, FreezeFrameKind, Dem_Client_ClientAccess_GetNode(ClientId));
  }
  else
  {
    lReturnValue = E_NOT_OK;
  }

  return lReturnValue;
}
#endif /* (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON) */

#if (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON)
/* ****************************************************************************
 % Dem_Client_ClientAccess_GetNextJ1939FreezeFrame
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
Dem_Client_ClientAccess_GetNextJ1939FreezeFrame(
  CONST(uint8, AUTOMATIC)  ClientId,
  CONSTP2VAR(uint32, AUTOMATIC, DEM_J1939DCM_DATA)  J1939DTC,
  CONSTP2VAR(uint8, AUTOMATIC, DEM_J1939DCM_DATA)  OccurrenceCounter,
  CONSTP2VAR(uint8, AUTOMATIC, DEM_J1939DCM_DATA)  DestBuffer,
  CONSTP2VAR(uint8, AUTOMATIC, DEM_J1939DCM_DATA)  BufSize 
  )
{
  Std_ReturnType lReturnValue;
  Dem_FreezeFrameIterator_HandleType  lFreezeFrameIteratorId;

  lReturnValue = DEM_NO_SUCH_ELEMENT;

  lFreezeFrameIteratorId = Dem_ClientData_GetFreezeFrameIteratorId(ClientId);
  if (lFreezeFrameIteratorId != DEM_CFG_FREEZEFRAMEITERATOR_INVALID)
  {
    if (Dem_FreezeFrameIterator_TestJ1939FreezeFrameFilterSet(lFreezeFrameIteratorId) == TRUE)
    {
      lReturnValue = Dem_FreezeFrameIterator_GetNextJ1939FreezeFrame(lFreezeFrameIteratorId,                                     /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
                                                                     J1939DTC, 
                                                                     OccurrenceCounter,
                                                                     DestBuffer,
                                                                     BufSize);
    }
  }

  return lReturnValue;
}
#endif /* (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON) */

/* ****************************************************************************
 % Dem_Client_ClientAccess_TestExtendedDataFilterValid
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Client_ClientAccess_TestExtendedDataFilterValid(                                                                                    /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  uint8 ClientId
)
{
  return (boolean)(Dem_ClientData_GetExtendedDataFilterId(ClientId) != DEM_CFG_FILTER_INVALID);
}

/* ****************************************************************************
 % Dem_Client_ClientAccess_TestExtendedDataFilterSet
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Client_ClientAccess_TestExtendedDataFilterSet(                                                                                      /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  uint8 ClientId
)
{
  return Dem_Dcm_ERec_0x1916_TestFilterSet((Dem_Dcm_ERec_0x1916_RecordNumberFilter_HandleType)ClientId);
}

/* ****************************************************************************
 % Dem_Client_ClientAccess_TestDTCFormatSupported
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Client_ClientAccess_TestDTCFormatSupported(                                                                                      /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  Dem_DTCFormatType  DTCFormat
)
{
  boolean lReturn;

  switch (DTCFormat)
  {
    case DEM_DTC_FORMAT_UDS:
      lReturn = TRUE;
      break;

#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
    case DEM_DTC_FORMAT_J1939:
      lReturn = TRUE;
      break;
#endif /* (DEM_CFG_SUPPORT_J1939 == STD_ON) */

    case DEM_DTC_FORMAT_OBD:
      lReturn = Dem_Cfg_IsObdSupportedInVariant();
      break;

    default: /*MISRA CASE */
      lReturn = FALSE;
      break;
  }
  return lReturn;
}

/* ****************************************************************************
 % Dem_Client_ClientAccess_SetExtendedDataRecordFilter
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
Dem_Client_ClientAccess_SetExtendedDataRecordFilter(
  uint8 ClientId,
  uint8 RecordNumber
)
{
  Std_ReturnType lReturnValue;
  lReturnValue = E_NOT_OK;

  if (Dem_Dcm_ERec_0x1916_IsService19_16Enabled() == TRUE)
  {
    Dem_Dcm_ERec_0x1916_RecordNumberFilter_HandleType lExtendedDataFilterId;
    lExtendedDataFilterId = Dem_ClientData_GetExtendedDataFilterId(ClientId);
    if (lExtendedDataFilterId != DEM_CFG_FILTER_INVALID)
    {
      lReturnValue = Dem_Dcm_ERec_0x1916_SetRecordFilter(lExtendedDataFilterId, RecordNumber);
    }
  }
  return lReturnValue;
}


/* ****************************************************************************
 % Dem_Client_ClientAccess_GetNumberOfFilteredExtendedDataRecords
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
Dem_Client_ClientAccess_GetNumberOfFilteredExtendedDataRecords(
  uint8 ClientId,
  P2VAR(uint16, AUTOMATIC, DEM_DCM_DATA)  NumberOfFilteredRecords,
  P2VAR(uint16, AUTOMATIC, DEM_DCM_DATA)  SizeOfExtendedDataRecord
)
{
  Std_ReturnType lReturnValue;
  lReturnValue = E_NOT_OK;

  if (Dem_Dcm_ERec_0x1916_IsService19_16Enabled() == TRUE)
  {
    Dem_Dcm_ERec_0x1916_RecordNumberFilter_HandleType lExtendedDataFilterId;
    lExtendedDataFilterId = Dem_ClientData_GetExtendedDataFilterId(ClientId);
    if (lExtendedDataFilterId != DEM_CFG_FILTER_INVALID)
    {
      Dem_Dcm_ERec_0x1916_CalcNumberofERecs(lExtendedDataFilterId, NumberOfFilteredRecords, SizeOfExtendedDataRecord);  /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
      lReturnValue = E_OK;
    }
  }

  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Client_ClientAccess_GetNextFilteredERecData
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
Dem_Client_ClientAccess_GetNextFilteredERecData(
  uint8 ClientId,
  P2VAR(uint32, AUTOMATIC, DEM_DCM_DATA) DTC,
  P2VAR(uint8,  AUTOMATIC, DEM_DCM_DATA) DTCStatus,
  P2VAR(uint8,  AUTOMATIC, DEM_DCM_DATA) DestBuffer,
  P2VAR(uint16, AUTOMATIC, DEM_DCM_DATA) BufSize
)
{
  Std_ReturnType lReturnValue;
  lReturnValue = E_NOT_OK;
  
  if (Dem_Dcm_ERec_0x1916_IsService19_16Enabled() == TRUE)
  {
    Dem_Dcm_ERec_0x1916_RecordNumberFilter_HandleType lExtendedDataFilterId;
    lExtendedDataFilterId = Dem_ClientData_GetExtendedDataFilterId(ClientId);
    if (lExtendedDataFilterId != DEM_CFG_FILTER_INVALID)
    {
      lReturnValue = Dem_Dcm_ERec_0x1916_GetNextFilteredERecData(lExtendedDataFilterId, DTC, DTCStatus, DestBuffer, BufSize);  /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    }
  }

  return lReturnValue;
}


/* ****************************************************************************
 % Dem_Client_ClientAccess_SetDtcFilterByReadinessGroup
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
Dem_Client_ClientAccess_SetDtcFilterByReadinessGroup(
  uint8 ClientId,
  Dem_EventOBDReadinessGroupType ReadinessGroup
)
{
  Std_ReturnType lReturnValue;
  lReturnValue = E_NOT_OK;

  if (Dem_FilterData_0x1956_IsService0x1956Enabled() == TRUE)
  {
    Dem_FilterData_HandleType lFilterId;
    lFilterId = Dem_ClientData_GetFilterId(ClientId);
    if (lFilterId != DEM_CFG_FILTER_INVALID)
    {
      Dem_Client_FilterData_SetDtcFilterByReadinessGroup(lFilterId, (Dem_Cfg_ReadinessGroupOfReadinessGroupTableType)ReadinessGroup);
      lReturnValue = E_OK;
    }
  }
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Client_ClientAccess_SetDTCFilterByExtendedDataRecordNumber
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
Dem_Client_ClientAccess_SetDTCFilterByExtendedDataRecordNumber(
  uint8 ClientId,
  uint8 ExtendedDataRecordNumber
)
{
  Std_ReturnType lReturnValue;
  lReturnValue = E_NOT_OK;

  if (Dem_Dcm_ERec_0x191A_IsService19_1AEnabled() == TRUE)
  {
    Dem_FilterData_HandleType lFilterId;
    lFilterId = Dem_ClientData_GetFilterId(ClientId);
    if (lFilterId != DEM_CFG_FILTER_INVALID)
    {
      lReturnValue = Dem_Client_FilterData_SetDTCFilterByExtendedDataRecordNumber(lFilterId, ExtendedDataRecordNumber);
    }
  }
  return lReturnValue;
}


/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */


#endif /* DEM_CLIENTACCESSIF_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_ClientAccessIF_Implementation.h
 *********************************************************************************************************************/
