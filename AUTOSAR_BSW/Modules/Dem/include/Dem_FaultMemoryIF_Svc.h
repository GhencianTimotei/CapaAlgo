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
/*! 
 *  \defgroup   Dem_FaultMemoryIF Dem FaultMemoryIF Functionality
 *  \{
 *  \file       Dem_FaultMemoryIF_Svc.h
 *  \brief      Svc of unit FaultMemoryIF.
 *  \details    Realizes the public interfaces of its parent logical unit, i.e. both Dem external service APIs and Dem internal APIs.
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_FAULTMEMORYIF_SVC_H)
#define DEM_FAULTMEMORYIF_SVC_H

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
/* PRQA S 3415 EOF */ /* MD_DEM_13.5_cf */

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                    /* Used subcomponent API */
/* ------------------------------------------------------------------------- */
#include "Dem_Memory_Interface.h"
#include "Dem_Prestore_Interface.h"

#include "Dem_Infrastructure_Interface.h"
#include "Dem_Core_Interface.h"
                                                   /* Subcomponents callbacks*/
/* ------------------------------------------------------------------------- */

/* ********************************************************************************************************************
 *  FILE SPECIFIC MISRA VIOLATIONS
 *********************************************************************************************************************/
/* PRQA S 3406 DEM_API_IMPL */ /* MD_DEM_8.6 */


/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

  /*! Filename declaration */
#define DEM_FAULTMEMORYIF_SVC_FILENAME "Dem_FaultMemoryIF_Svc.h"

 /* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \addtogroup Dem_FaultMemoryIF_Public
 * \{
 */

/* ****************************************************************************
 % Dem_PrestoreFreezeFrame
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_PrestoreFreezeFrame(
  Dem_EventIdType  EventId                                                                                                       /* PRQA S 1330 */ /* MD_DEM_8.3_rte */
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
  if (Dem_APIChecks_GlobalConfigPointerInState(DEM_CONFIGVALIDATION_CONFIGPTR_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (Dem_APIChecks_MasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (Dem_APIChecks_EventId(EventId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (Dem_APIChecks_SatelliteInState(Dem_Cfg_EventSatelliteId(EventId), DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (Dem_APIChecks_EventApplicationId(EventId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  /* ----- Global Precondition Checks -------------------------------------- */
  if (Dem_Cfg_EventUdsDtc(EventId) == DEM_CFG_DTC_UDS_INVALID)
  {
    lReturnValue = E_NOT_OK;
  }
  else
  if (Dem_Cfg_EventPrestorageIndex(EventId) == DEM_PRESTORE_NOT_CONFIGURED_FOR_EVENT)
  {
    lReturnValue = E_NOT_OK;
  }
  else
  if (Dem_Event_TestEventAvailable(EventId) == FALSE)
  {
    lReturnValue = E_NOT_OK;
  }
  /* ----- Implementation -------------------------------------------------- */
  else
  {
    lReturnValue = Dem_Prestore_EventPrestoreFreezeFrame(EventId);
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_PRESTOREFREEZEFRAME_APIID, Dem_Det_ErrorRegisterGet());
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_ClearPrestoredFreezeFrame
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_ClearPrestoredFreezeFrame(
  Dem_EventIdType  EventId                                                                                                       /* PRQA S 1330 */ /* MD_DEM_8.3_rte */
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
  if (Dem_APIChecks_GlobalConfigPointerInState(DEM_CONFIGVALIDATION_CONFIGPTR_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (Dem_APIChecks_MasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (Dem_APIChecks_EventId(EventId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (Dem_APIChecks_SatelliteInState(Dem_Cfg_EventSatelliteId(EventId), DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (Dem_APIChecks_EventApplicationId(EventId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  /* ----- Global Precondition Checks -------------------------------------- */
  if (Dem_Cfg_EventUdsDtc(EventId) == DEM_CFG_DTC_UDS_INVALID)
  {
    lReturnValue = E_NOT_OK;
  }
  else
  if (Dem_Cfg_EventPrestorageIndex(EventId) == DEM_PRESTORE_NOT_CONFIGURED_FOR_EVENT)
  {
    lReturnValue = E_NOT_OK;
  }
  else
  if (Dem_Event_TestEventAvailable(EventId) == FALSE)
  {
    lReturnValue = E_NOT_OK;
  }
  else
  {
  /* ----- Implementation -------------------------------------------------- */
    lReturnValue = Dem_Prestore_EventClearPrestoredFreezeFrame(EventId);
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_CLEARPRESTOREDFREEZEFRAME_APIID, Dem_Det_ErrorRegisterGet());
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */

                                /* Service Interface EvMemOverflowIndication */
/* ------------------------------------------------------------------------- */

#if (DEM_CFG_SUPPORT_OVFLIND_API == STD_ON)
/* ****************************************************************************
 % Dem_GetEventMemoryOverflow
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetEventMemoryOverflow(
  uint8  ClientId,
  Dem_DTCOriginType  DTCOrigin,                                                                                                  /* PRQA S 1330 */ /* MD_DEM_8.3_rte */
  P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA)  OverflowIndication
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
  if (Dem_APIChecks_MasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (Dem_APIChecks_ClientId(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (DTCOrigin == 0u)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (DTCOrigin >= DEM_DTC_ORIGIN_INVALID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
# endif
  if (Dem_APIChecks_NullPointer(OverflowIndication) == FALSE)                                                                    /* SBSW_DEM_POINTER_NULLPTR_CHECKING */ /* PRQA S 0315 */ /* MD_DEM_Dir1.1 */
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (Dem_APIChecks_IsMasterPartition() == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  {
    /* ----- Implementation ------------------------------------------------ */
    switch (DTCOrigin)
    {
    case DEM_DTC_ORIGIN_PRIMARY_MEMORY:
      *OverflowIndication = Dem_Memory_GetOverflow(DEM_CFG_MEMORYID_PRIMARY);                                                    /* SBSW_DEM_POINTER_WRITE_API */
      lReturnValue = E_OK;
      break;

# if (DEM_CFG_SUPPORT_SECONDARY == STD_ON)
    case DEM_DTC_ORIGIN_SECONDARY_MEMORY:
      *OverflowIndication = Dem_Memory_GetOverflow(DEM_CFG_MEMORYID_SECONDARY);                                                  /* SBSW_DEM_POINTER_WRITE_API */
      lReturnValue = E_OK;
      break;
# endif

    case DEM_DTC_ORIGIN_PERMANENT_MEMORY:
      if (Dem_Cfg_IsPermanentSupportedInVariant() == TRUE)
      {
        *OverflowIndication = Dem_Memory_GetOverflow(DEM_CFG_MEMORYID_PERMANENT);                                                /* SBSW_DEM_POINTER_WRITE_API */
        lReturnValue = E_OK;
      }
      break;

    default:                                                                                                                     /* PRQA S 2016 */ /* MD_MSR_EmptyClause */
      /* E_NOT_OK */
      break;
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETEVENTMEMORYOVERFLOW_APIID, Dem_Det_ErrorRegisterGet());
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6030, 6080 */ /* MD_MSR_STCYC, MD_MSR_STMIF */
#endif /* (DEM_CFG_SUPPORT_OVFLIND_API == STD_ON) */

#if (DEM_CFG_SUPPORT_OVFLIND_API == STD_ON)
/* ****************************************************************************
 % Dem_GetNumberOfEventMemoryEntries
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetNumberOfEventMemoryEntries(
  uint8  ClientId,
  Dem_DTCOriginType  DTCOrigin,                                                                                                  /* PRQA S 1330 */ /* MD_DEM_8.3_rte */
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)  NumberOfEventMemoryEntries
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
  if (Dem_APIChecks_MasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (Dem_APIChecks_ClientId(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (DTCOrigin == 0u)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (DTCOrigin >= DEM_DTC_ORIGIN_INVALID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
# endif
  if (Dem_APIChecks_NullPointer(NumberOfEventMemoryEntries) == FALSE)                                                                       /* SBSW_DEM_POINTER_NULLPTR_CHECKING */ /* PRQA S 0315 */ /* MD_DEM_Dir1.1 */
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (Dem_APIChecks_IsMasterPartition() == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  {
    /* ----- Implementation ------------------------------------------------ */
    switch (DTCOrigin)
    {
    case DEM_DTC_ORIGIN_PRIMARY_MEMORY:
      *NumberOfEventMemoryEntries = Dem_Memory_GetNumAllocatedMemoryEntry(DEM_CFG_MEMORYID_PRIMARY);                             /* SBSW_DEM_POINTER_WRITE_API */
      lReturnValue = E_OK;
      break;

# if (DEM_CFG_SUPPORT_SECONDARY == STD_ON)
    case DEM_DTC_ORIGIN_SECONDARY_MEMORY:
      *NumberOfEventMemoryEntries = Dem_Memory_GetNumAllocatedMemoryEntry(DEM_CFG_MEMORYID_SECONDARY);                           /* SBSW_DEM_POINTER_WRITE_API */
      lReturnValue = E_OK;
      break;
# endif

    case DEM_DTC_ORIGIN_PERMANENT_MEMORY:
      if (Dem_Cfg_IsPermanentSupportedInVariant() == TRUE)
      {
        *NumberOfEventMemoryEntries = Dem_Memory_GetNumAllocatedMemoryEntry(DEM_CFG_MEMORYID_PERMANENT);                         /* SBSW_DEM_POINTER_WRITE_API */
        lReturnValue = E_OK;
      }
      break;

    default:                                                                                                                     /* PRQA S 2016 */ /* MD_MSR_EmptyClause */
      /* E_NOT_OK */
      break;
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETNUMBEROFEVENTMEMORYENTRIES_APIID, Dem_Det_ErrorRegisterGet());
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6030, 6080 */ /* MD_MSR_STCYC, MD_MSR_STMIF */
#endif /* (DEM_CFG_SUPPORT_OVFLIND_API == STD_ON) */




                                             /* Permanent Storage Activation */
/* ------------------------------------------------------------------------- */
#if (DEM_CFG_SUPPORT_PERMANENTDTC_ACTIVATION_DISTANCE == STD_ON)
/* ****************************************************************************
 % Dem_EnablePermanentStorage
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_EnablePermanentStorage(
  void
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
  if (Dem_APIChecks_MasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (Dem_APIChecks_IsObdIISupportedInVariant() == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  if (Dem_APIChecks_IsMasterPartition() == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  {
    /* ----- Implementation ------------------------------------------------ */
    if(Dem_Cfg_IsObdIISupportedInVariant())
    {
      boolean lCurrentPermanentActivationState;

/* >>>> -------------------------------- Enter Critical Section: DcmApi
 * Critical section to read current value and write new value. This guarantees Dem_Memory_PermanentFillUp is called
 * only once.  */
      Dem_EnterCritical_DcmApi();

      /* PDTC storage may be activated from task level or by a diagnostic request */
      lCurrentPermanentActivationState = Dem_Mem_GetPermanentActivationState();
      if (lCurrentPermanentActivationState == FALSE)
      {
        /* permanent storage is not yet active */
        Dem_Mem_SetPermanentActivationState(TRUE);
      }

      Dem_LeaveCritical_DcmApi();
/* <<<< -------------------------------- Leave Critical Section: DcmApi */

      if (lCurrentPermanentActivationState == FALSE)
      {
        Dem_Memory_PermanentFillUp();
      } /* else: permanent storage is already active; nothing to do */

      lReturnValue = E_OK;
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_ENABLEPERMANENTSTORAGE_APIID, Dem_Det_ErrorRegisterGet());
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif /* (DEM_CFG_SUPPORT_PERMANENTDTC_ACTIVATION_DISTANCE == STD_ON) */

#if (DEM_CFG_SUPPORT_PERMANENTDTC_ACTIVATION_DISTANCE == STD_ON)
/* ****************************************************************************
 % Dem_GetPermanentStorageState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetPermanentStorageState(
  P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA)  isEnabled
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
  if (Dem_APIChecks_MasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (Dem_APIChecks_IsObdIISupportedInVariant() == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  if (Dem_APIChecks_NullPointer(isEnabled) == FALSE)                                                                       /* SBSW_DEM_POINTER_NULLPTR_CHECKING */  /* PRQA S 0315 */ /* MD_DEM_Dir1.1 */
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (Dem_APIChecks_IsMasterPartition() == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  {
    /* ----- Implementation ------------------------------------------------ */
    if (Dem_Cfg_IsObdIISupportedInVariant())
    {
      *isEnabled = (boolean)(Dem_Mem_GetPermanentActivationState() == TRUE);                                                     /* SBSW_DEM_POINTER_WRITE_API */
      lReturnValue = E_OK;
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETPERMANENTSTORAGESTATE_APIID, Dem_Det_ErrorRegisterGet());
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* (DEM_CFG_SUPPORT_PERMANENTDTC_ACTIVATION_DISTANCE == STD_ON) */



#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_NvM_InitObdFreezeFrameData
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_NvM_InitObdFreezeFrameData(
  void
  )
{
  Dem_Det_ErrorRegisterDefine()

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
  if (Dem_APIChecks_MasterNotInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  {
    uint8 lFreezeFrameIndex;

    /* ----- Implementation ------------------------------------------------ */
    lFreezeFrameIndex = Dem_Cfg_GlobalObdIIFFCount();

    while (lFreezeFrameIndex != 0U)
    {
      lFreezeFrameIndex--;
      Dem_MemObdFreezeFrame_FreezeFrameFreeEntry(lFreezeFrameIndex);
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_NVMINIT_APIID, Dem_Det_ErrorRegisterGet());
  }


  /* The DEM expects that the NVM by itself marks the NVRAM block as dirty */
  return E_OK;
}
#endif /* (DEM_CFG_SUPPORT_OBDII == STD_ON) */

#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/* ****************************************************************************
 % Dem_NvM_InitObdPermanentData
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_NvM_InitObdPermanentData(
  void
  )
{
  /* ----- Development Error Checks ---------------------------------------- */

  /* Do not check for preinitialization phase */

  /* ----- Implementation -------------------------------------------------- */
  uint8 lPermanentIndex;

  lPermanentIndex = Dem_Cfg_GlobalPermanentMaxCount();

  while(lPermanentIndex != 0u)
  {
    --lPermanentIndex;
    Dem_Mem_PermanentSetEvent(lPermanentIndex, DEM_EVENT_INVALID);
    Dem_Mem_PermanentSetStatus(lPermanentIndex, DEM_ESM_PERMANENT_NONE);
  }

  Dem_Mem_PermanentSetInitPattern(DEM_MEM_PERMANENT_INIT_PATTERN);

  /* ----- Development Error Report ---------------------------------------- */

  /* The DEM expects that the NVM by itself marks the NVRAM block as dirty */
  return E_OK;
}
#endif /* (DEM_CFG_SUPPORT_PERMANENT == STD_ON) */


#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_OBDII == STD_ON) && (DEM_CFG_SUPPORT_COMPATIBILITY == STD_OFF)
/* ****************************************************************************
 % Dem_DcmGetDTCOfOBDFreezeFrame
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_DcmGetDTCOfOBDFreezeFrame(
  uint8  FrameNumber,
  P2VAR(uint32, AUTOMATIC, DEM_DCM_DATA)  DTC, 
  Dem_DTCFormatType  DTCFormat
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
  if (Dem_APIChecks_MasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (Dem_APIChecks_IsObdIISupportedInVariant() == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  if (Dem_APIChecks_NullPointer(DTC) == FALSE)                                                                       /* SBSW_DEM_POINTER_NULLPTR_CHECKING */  /* PRQA S 0315 */ /* MD_DEM_Dir1.1 */
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (Dem_APIChecks_IsDTCFormatSupported(DTCFormat) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (FrameNumber != 0x00u)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else  
# endif
  if (Dem_APIChecks_IsMasterPartition() == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  {
    uint8 lSelectedIndex;
    Dem_EventIdType lEventId;

    /* ----- Implementation ------------------------------------------------ */
    /* copy Mode02 index on the stack as it might change in the background */
    lSelectedIndex = Dem_Mem_FreezeFrameIndexMode02;
    lEventId = Dem_Mem_FreezeFrameGetEvent(lSelectedIndex);

    if ( (Dem_Cfg_GlobalObdIIFFCount() != lSelectedIndex)
      && (Dem_Event_TestValidHandle(lEventId) == TRUE)
      && (Dem_DTC_TestDtcSuppression(lEventId) == FALSE)                                                                         /* PRQA S 3415 */ /* MD_DEM_13.5_cf */                                      
      )
    {
      lReturnValue = Dem_DTC_GetFormatedDTCByEvent(lEventId, DTCFormat, DTC);                                                    /* SBSW_DEM_POINTER_FORWARD_API_ARGUMENT_BUFFER */
    }
    /* else No Freeze Frame stored, return value lReturnValue = E_NOT_OK initially set */
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_DCMGETDTCOFOBDFREEZEFRAME_APIID, Dem_Det_ErrorRegisterGet());
  }

  DEM_IGNORE_UNUSED_ARGUMENT(FrameNumber)                                                                                        /* PRQA S 1338, 3112 */ /*  MD_MSR_DummyStmt, MD_DEM_14.2 */
  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_OBDII == STD_ON) && (DEM_CFG_SUPPORT_COMPATIBILITY == STD_ON)
/* ****************************************************************************
 % Dem_DcmGetDTCOfOBDFreezeFrame
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_DcmGetDTCOfOBDFreezeFrame(
  uint8  FrameNumber,
  P2VAR(uint32, AUTOMATIC, DEM_DCM_DATA)  DTC
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  Dem_DTCFormatType DTCFormat;
  DTCFormat = DEM_DTC_FORMAT_OBD;

  lReturnValue = E_NOT_OK;
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
  if (Dem_APIChecks_MasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (Dem_APIChecks_IsObdIISupportedInVariant() == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  if (Dem_APIChecks_NullPointer(DTC) == FALSE)                                                                       /* SBSW_DEM_POINTER_NULLPTR_CHECKING */  /* PRQA S 0315 */ /* MD_DEM_Dir1.1 */
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (FrameNumber != 0x00u)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else  
# endif
  if (Dem_APIChecks_IsMasterPartition() == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  {
    uint8 lSelectedIndex;
    Dem_EventIdType lEventId;

    /* ----- Implementation ------------------------------------------------ */
    /* copy Mode02 index on the stack as it might change in the background */
    lSelectedIndex = Dem_Mem_FreezeFrameIndexMode02;
    lEventId = Dem_Mem_FreezeFrameGetEvent(lSelectedIndex);

    if ( (Dem_Cfg_GlobalObdIIFFCount() != lSelectedIndex)
      && (Dem_Event_TestValidHandle(lEventId) == TRUE)
      && (Dem_DTC_TestDtcSuppression(lEventId) == FALSE)                                                                         /* PRQA S 3415 */ /* MD_DEM_13.5_cf */                                      
      )
    {
      lReturnValue = Dem_DTC_GetFormatedDTCByEvent(lEventId, DTCFormat, DTC);                                                    /* SBSW_DEM_POINTER_FORWARD_API_ARGUMENT_BUFFER */
    }
    /* else No Freeze Frame stored, return value lReturnValue = E_NOT_OK initially set */
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_DCMGETDTCOFOBDFREEZEFRAME_APIID, Dem_Det_ErrorRegisterGet());
  }

  DEM_IGNORE_UNUSED_ARGUMENT(FrameNumber)                                                                                        /* PRQA S 1338, 3112 */ /*  MD_MSR_DummyStmt, MD_DEM_14.2 */
  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif
/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ********************************************************************************************************************
 *  FILE SPECIFIC MISRA VIOLATIONS
 *********************************************************************************************************************/
/* PRQA L:DEM_API_IMPL */


#endif /* DEM_FAULTMEMORYIF_SVC_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_FaultMemoryIF_Svc.h
 *********************************************************************************************************************/
