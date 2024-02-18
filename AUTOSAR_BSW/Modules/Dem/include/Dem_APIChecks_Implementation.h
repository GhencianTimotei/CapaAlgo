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
/*! \addtogroup Dem_APIChecks
 *  \{
 *  \file       Dem_APIChecks_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Implementation of all DET checks used in API sub-components.
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_APICHECKS_IMPLEMENTATION_H)
#define DEM_APICHECKS_IMPLEMENTATION_H

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
#include "Dem_APIChecks_Interface.h"

/* Includes to access public functions belonging to other (top level)/ (logical)/- units to be used by this Unit */
/* ------------------------------------------------------------------------- */
#include "Dem_ExtCom_Interface.h"
#include "Dem_InitState_Interface.h"
#include "Dem_ConfigValidation_Interface.h"
#include "Dem_Error_Interface.h"

#include "Dem_Core_Interface.h"
#include "Dem_Satellite_Interface.h"
#include "Dem_Client_Interface.h"
#include "Dem_RecordReader_Interface.h"
#include "Dem_DiagnosticObserver_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

  /*! Filename declaration */
#define DEM_APICHECKS_IMPLEMENTATION_FILENAME "Dem_APIChecks_Implementation.h"

 /* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/

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
 * \addtogroup Dem_APIChecks_Public
 * \{
 */
 /* ****************************************************************************
 % Dem_APIChecks_SatelliteInState
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_SatelliteInState(                                                                                                  /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(uint8, AUTOMATIC) InitState
)
{
  return Dem_Error_DetectionHandler(Dem_InitState_TestSatelliteInState(SatelliteId, InitState));
}

 /* ****************************************************************************
 % Dem_APIChecks_MasterInState
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_MasterInState(
  CONST(uint8, AUTOMATIC) InitState
)
{
  return Dem_Error_DetectionHandler(Dem_InitState_TestMasterInState(InitState));
}

 /* ****************************************************************************
 % Dem_APIChecks_GlobalConfigPointerInState
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_GlobalConfigPointerInState(
  CONST(uint8, AUTOMATIC) InitState
)
{
  boolean lRetVal;

  lRetVal = Dem_Error_DetectionHandler(Dem_ConfigurationValidation_TestGlobalCfgPointerInState(InitState));

  return lRetVal;
}


 /* ****************************************************************************
 % Dem_APIChecks_GlobalConfigPointerAtleastInState
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_GlobalConfigPointerAtleastInState(
  CONST(uint8, AUTOMATIC) InitState
)
{
  boolean lRetVal;

  lRetVal = Dem_Error_DetectionHandler(Dem_ConfigurationValidation_TestGlobalCfgPointerAtleastInState(InitState));

  return lRetVal;
}

/* ****************************************************************************
 % Dem_APIChecks_MasterNotInState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_MasterNotInState(
  CONST(uint8, AUTOMATIC) InitState
)
{
  return Dem_Error_DetectionHandler(Dem_InitState_TestMasterInState(InitState) == FALSE);
}

/* ****************************************************************************
 % Dem_APIChecks_MasterAtLeastInState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_MasterAtLeastInState(
  CONST(uint8, AUTOMATIC) InitState
)
{
  return Dem_Error_DetectionHandler(Dem_InitState_TestMasterAtLeastInState(InitState));
}

/* ****************************************************************************
 % Dem_APIChecks_SatelliteAtLeastInState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_SatelliteAtLeastInState(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(uint8, AUTOMATIC) InitState
)
{
  return Dem_Error_DetectionHandler(Dem_InitState_TestSatelliteAtLeastInState(SatelliteId, InitState));
}

/* ****************************************************************************
 % Dem_APIChecks_IsMasterPartition
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_IsMasterPartition(
  void
)
{
  return Dem_Error_DetectionHandler(Dem_ExtCom_TestCurrentPartitionIsMaster());
}

/* ****************************************************************************
 % Dem_APIChecks_IsBoolean
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_IsBoolean(                                                                                                         /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  boolean  Parameter
)
{
  return Dem_Error_DetectionHandler((Parameter == TRUE) || (Parameter == FALSE));
}

/* ****************************************************************************
 % Dem_APIChecks_SingleSatellite
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_SingleSatellite(
  void
)
{
  return Dem_Error_DetectionHandler((boolean)(Dem_Cfg_GlobalSatelliteCount() == 1u));
}

/* ****************************************************************************
 % Dem_APIChecks_DebounceCounterNvConditions
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_DebounceCounterNvConditions(                                                                                       /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  Dem_EventIdType  EventId
)
{
  boolean lReturn;
  lReturn = (boolean)((Dem_Event_TestDebounceCounterStoredInNv(EventId) == FALSE)
    || ((Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == TRUE)                                                     
       && (Dem_ConfigurationValidation_TestGlobalCfgPointerInState(DEM_CONFIGVALIDATION_CONFIGPTR_INITIALIZED) == TRUE)));       

  return Dem_Error_DetectionHandler(lReturn);
}

 /* ****************************************************************************
 % Dem_APIChecks_ReportedSimilarConditions
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_ReportedSimilarConditions(                                                                                         /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  Dem_EventIdType  EventId,
  Dem_EventStatusType EventStatus
)
{
  boolean lReturn;
  lReturn = (boolean)((EventStatus <= DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED)
    || ((Dem_Cfg_EventObdRelated(EventId) == TRUE)                                                                               
      && (Dem_Event_IsSimilarConditionsEnabled() == TRUE)));                                                                     

  return Dem_Error_DetectionHandler(lReturn);
}

 /* ****************************************************************************
 % Dem_APIChecks_EventId
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_EventId(                                                                                                           /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  Dem_EventIdType  EventId
)
{
  return Dem_Error_DetectionHandler(Dem_Event_TestValidHandle(EventId));
}

/* ****************************************************************************
 % Dem_APIChecks_ClientId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_ClientId(
  uint8  ClientId
  )
{
  return Dem_Error_DetectionHandler(Dem_Client_ClientAccess_TestClientIdValid(ClientId));
}

/* ****************************************************************************
 % Dem_APIChecks_NullPointer
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_NullPointer(
  CONSTP2CONST(void, AUTOMATIC, DEM_SHARED_DATA)  ExternalPtr
)
{
  return Dem_Error_DetectionHandler((boolean)(ExternalPtr != NULL_PTR));
}

 /* ****************************************************************************
 % Dem_APIChecks_ReportedStatus
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_ReportedStatus(
  Dem_EventStatusType EventStatus
)
{
  return Dem_Error_DetectionHandler(EventStatus < DEM_EVENT_STATUS_INVALID);
}

/* ****************************************************************************
 % Dem_APIChecks_IsIUMPRRatioIDValid
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_IsIUMPRRatioIDValid(
  Dem_RatioIdType  RatioID
)
{
  Dem_RatioIdIndexType lRatioIndex;
  lRatioIndex = Dem_Event_GetRatioIdx(RatioID);
  return Dem_Error_DetectionHandler(lRatioIndex != DEM_CFG_RATIOINDEX_INVALID);
}

/* ****************************************************************************
 % Dem_APIChecks_IsRatioIDOfApiType
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_IsRatioIDOfApiType(
  Dem_RatioIdType  RatioID
)
{
  Dem_RatioIdIndexType lRatioIndex;
  lRatioIndex = Dem_Event_GetRatioIdx(RatioID);
  return Dem_Error_DetectionHandler(Dem_Iumpr_GetRatioReportingType(lRatioIndex) == DEM_RATIO_API);
}

/* ****************************************************************************
 % Dem_APIChecks_IsRatioDenominatorLockable
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_IsRatioDenominatorLockable(
  Dem_RatioIdType  RatioID
)
{
  Dem_RatioIdIndexType lRatioIndex;
  boolean lLockable;

  lRatioIndex = Dem_Event_GetRatioIdx(RatioID);

  lLockable = ((Dem_Iumpr_GetDenGroupOfRatio(lRatioIndex) == DEM_IUMPR_DEN_PHYS_API) 
            || (Dem_Iumpr_GetDenGroupOfRatio(lRatioIndex) == DEM_IUMPR_DEN_INDEPENDENT));

  return Dem_Error_DetectionHandler(lLockable);
}

/* ****************************************************************************
 % Dem_APIChecks_EventApplicationId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_EventApplicationId(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
)
{
  return Dem_Error_DetectionHandler(Dem_Satellite_CheckEventApplicationId(EventId));
}


/* ****************************************************************************
 % Dem_APIChecks_IsObdSupportedInVariant
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_IsObdSupportedInVariant(
  void
)
{
  return Dem_Error_DetectionHandler(Dem_Cfg_IsObdSupportedInVariant());
}


/* ****************************************************************************
 % Dem_APIChecks_IsObdIISupportedInVariant
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_IsObdIISupportedInVariant(                                                                                         /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
)
{
  return Dem_Error_DetectionHandler(Dem_Cfg_IsObdIISupportedInVariant());
}

/* ****************************************************************************
 % Dem_APIChecks_IsWwhObdSupportedInVariant
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_IsWwhObdSupportedInVariant(                                                                                        /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
)
{
  return Dem_Error_DetectionHandler(Dem_Cfg_IsWwhObdSupportedInVariant());
}



/* ****************************************************************************
 % Dem_APIChecks_IsService19_16Enabled
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_IsService19_16Enabled(                                                                                             /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
 void
)
{
  return Dem_Error_DetectionHandler(Dem_Dcm_ERec_0x1916_IsService19_16Enabled());
}


/* ****************************************************************************
 % Dem_APIChecks_IsExtendedDataRecordFilterValid
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_IsExtendedDataRecordFilterValid(                                                                                   /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  uint8  ClientId
)
{
  return Dem_Error_DetectionHandler(Dem_Client_ClientAccess_TestExtendedDataFilterValid(ClientId));
}

/* ****************************************************************************
 % Dem_APIChecks_IsExtendedDataRecordFilterSet
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_IsExtendedDataRecordFilterSet(                                                                                     /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  uint8  ClientId
)
{
  return Dem_Error_DetectionHandler(Dem_Client_ClientAccess_TestExtendedDataFilterSet(ClientId));
}

/* ****************************************************************************
 % Dem_APIChecks_IsDTCOriginSupportedFor0x1916
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_IsDTCOriginSupportedFor0x1916(                                                                  /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  Dem_DTCOriginType  DTCOrigin
)
{
  return Dem_Error_DetectionHandler(DTCOrigin == DEM_DTC_ORIGIN_PRIMARY_MEMORY);
}

/* ****************************************************************************
 % Dem_APIChecks_IsDTCFormatSupported
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_IsDTCFormatSupported(                                                                                              /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  Dem_DTCFormatType  DTCFormat
)
{
  return Dem_Error_DetectionHandler(Dem_Client_ClientAccess_TestDTCFormatSupported(DTCFormat));
}

/* ****************************************************************************
 % Dem_APIChecks_IsDTCFormatSupportedFor0x1916
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_IsDTCFormatSupportedFor0x1916(                                                                                     /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  Dem_DTCFormatType  DTCFormat
)
{
  return Dem_Error_DetectionHandler(DTCFormat == DEM_DTC_FORMAT_UDS);
}

/* ****************************************************************************
 % Dem_APIChecks_IsService19_56Enabled
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_IsService19_56Enabled(                                                                                             /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
)
{
  return Dem_Error_DetectionHandler(Dem_FilterData_0x1956_IsService0x1956Enabled());
}

/* ****************************************************************************
 % Dem_ApiChecks_TestReadinessGroupValid
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_ApiChecks_TestReadinessGroupValid(                                                                                           /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  Dem_EventOBDReadinessGroupType ReadinessGroup
)
{
  return Dem_Error_DetectionHandler((boolean)(ReadinessGroup < DEM_CFG_READINESS_GROUP_INVALID));
}

/* ****************************************************************************
 % Dem_ApiChecks_TestDTCFilterValid
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_ApiChecks_TestDTCFilterValid(                                                                                                /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  uint8 ClientId
)
{
  return Dem_Error_DetectionHandler((boolean)Dem_Client_ClientAccess_TestFilterValid(ClientId));
}


/* ****************************************************************************
 % Dem_APIChecks_IsExtendedFiMEnabled
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_IsExtendedFiMEnabled(                                                                                              /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
  )
{
  return Dem_Error_DetectionHandler(Dem_StatusIndicator_IsExtendedFimEnabled());
}

/* ****************************************************************************
 % Dem_APIChecks_IsCounterDebounce
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_IsCounterDebounce(                                                                                                 /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  Dem_EventIdType EventId
  )
{
  return Dem_Error_DetectionHandler(Dem_Cfg_EventDebounceType(EventId) == DEM_CFG_DEBOUNCETYPE_COUNTER);
}

/* ****************************************************************************
 % Dem_APIChecks_IsService19_1AEnabled
*****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_IsService19_1AEnabled(                                                                                             /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
)
{
  return Dem_Error_DetectionHandler(Dem_Dcm_ERec_0x191A_IsService19_1AEnabled());
}

/* ****************************************************************************
 % Dem_ApiChecks_TestExtendedDataRecordNumberValid
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_ApiChecks_TestExtendedDataRecordNumberValid(                                                                                 /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  uint8 ExtendedDataRecordNumber
)
{
  return Dem_Error_DetectionHandler((boolean)(ExtendedDataRecordNumber > DEM_DCM_EREC_DATACOLLECTIONTABLE_INVALID));
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_APICHECKS_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_APIChecks_Implementation.h
 *********************************************************************************************************************/
