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
/*! \addtogroup Dem_ExternalCommunication
 *  \{
 *  \file       Dem_ExtCom_Implementation.h
 *  \brief      Implementation file for the MICROSAR Dem
 *  \details    Implementation of external communication subcomponent
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_EXTCOM_IMPLEMENTATION_H)
#define DEM_EXTCOM_IMPLEMENTATION_H

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
 /* External component header */
#if (((DEM_CFG_NOTIFY_MONITOR_STATUS_FIM == STD_ON) && (DEM_CFG_USE_MULTI_PARTITION_FIM == STD_ON)) || (DEM_CFG_SUPPORT_EXTENDED_FIM == STD_ON))
#include "FiM.h"
#endif

 /* ------------------------------------------------------------------------- */
                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_ExtCom_Interface.h"

                                                    /* Used subcomponent API */
/* ------------------------------------------------------------------------- */

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*! Filename declaration */
#define DEM_EXTCOM_IMPLEMENTATION_FILENAME "Dem_ExtCom_Implementation.h"

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
 *  SUBCOMPONENT PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \addtogroup Dem_ExternalCommunication_Public
 * \{
 */

/* ****************************************************************************
 % Dem_ExtCom_TestCurrentPartitionIsMaster()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE) Dem_ExtCom_TestCurrentPartitionIsMaster(
  void
  )
{
  boolean lRetVal;

  lRetVal = TRUE;

#if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    lRetVal = FALSE;
  }
#endif  

  return lRetVal;
}

/* ****************************************************************************
 % Dem_ExtCom_GetCurrentApplicationId()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_ExtCom_ApplicationType, DEM_CODE) Dem_ExtCom_GetCurrentApplicationId(
  void
  )
{
  Dem_ExtCom_ApplicationType lReturn;
#if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  lReturn = GetCurrentApplicationID();
#else
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE)
  lReturn = (Dem_ExtCom_ApplicationType)0;
#endif
  return lReturn;
}

/* ****************************************************************************
 % Dem_ExtCom_FimInitSatellite()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) Dem_ExtCom_FimInitSatellite(
  Dem_ExtCom_ApplicationType ApplicationId
  )
{
#if ((DEM_CFG_NOTIFY_MONITOR_STATUS_FIM == STD_ON) && (DEM_CFG_USE_MULTI_PARTITION_FIM == STD_ON))
  FiM_DemInitSatellite((ApplicationType)ApplicationId);
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(ApplicationId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
}

/* ****************************************************************************
 % Dem_ExtCom_FimGetFunctionPendingStatus()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE) Dem_ExtCom_FimGetFunctionPendingStatus(
  CONST(Dem_ExtCom_FiMFunctionIdType, AUTOMATIC) FID,
  CONSTP2VAR(boolean, AUTOMATIC, AUTOMATIC) FimFaultPending
  )
{
  Std_ReturnType lFiMReturnValue;

#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
  lFiMReturnValue = FiM_GetFunctionPendingStatus(FID, FimFaultPending);                                                          /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(FID)                                                                                          /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lFiMReturnValue = E_NOT_OK;
  *FimFaultPending = TRUE;                                                                                                       /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
#endif

  return lFiMReturnValue;
}

/*!
 * \}
 */

/* ****************************************************************************
 % Dem_ExtCom_FimDemTriggerOnUnconfirmed()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE) Dem_ExtCom_FimDemTriggerOnUnconfirmed(
  Dem_EventIdType EventId
  )
{
#if (DEM_CFG_SUPPORT_EXTENDED_FIM == STD_ON)
    FiM_DemTriggerOnUnconfirmed(EventId);
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)
#endif
}

#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_EXTCOM_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_ExtCom_Implementation.h
 *********************************************************************************************************************/
