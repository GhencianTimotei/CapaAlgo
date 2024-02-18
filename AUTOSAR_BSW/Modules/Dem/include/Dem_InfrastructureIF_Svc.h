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
 *  \defgroup   Dem_InfrastructureIF Dem InfrastructureIF Functionality
 *  \{
 *  \file       Dem_InfrastructureIF_Svc.h
 *  \brief      Service implementation of unit InfrastructureIF.
 *  \details    Realizes the Dem external service APIs.
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_INFRASTRUCTUREIF_SVC_H)
#define DEM_INFRASTRUCTUREIF_SVC_H

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

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */

                                                    /* Used subcomponent API */
/* ------------------------------------------------------------------------- */

#include "Dem_APIChecks_Interface.h"
#include "Dem_ConfigValidation_Interface.h"
#include "Dem_EventQueue_Interface.h"
#include "Dem_InitState_Interface.h"
#include "Dem_Nvm_Interface.h"
#include "Dem_Scheduler_Interface.h"
#include "Dem_Error_Interface.h"


#include "Dem_RecordReader_Interface.h"
#include "Dem_Satellite_Interface.h"
#include "Dem_Core_Interface.h"
#include "Dem_GlobalDiagnostics_Interface.h"
#include "Dem_DiagnosticObserver_Interface.h"
#include "Dem_FaultMemory_Interface.h"
#include "Dem_Client_Interface.h"
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
#define DEM_INFRASTRUCTUREIF_SVC_FILENAME "Dem_InfrastructureIF_Svc.h"

 /* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_InfrastructureIF_Private Private Methods
 * \{
 */

/* ****************************************************************************
 * Dem_MasterMainFunctionTimer
 *****************************************************************************/
/*!
 * \brief         Cyclic DemMaster timer task.
 *
 * \details       This function creates the time base for the DemMaster module.
 *
 *                Call this function in a cyclic manner, with the configured
 *                cycle time. The run-time of this function is as minimal as
 *                possible, so it can be called on a higher priority task with
 *                minimal impact.
 *
 * \pre           DemMaster has been pre-initialized.
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(void, DEM_CODE)
Dem_MasterMainFunctionTimer(
  void
  );


/* ****************************************************************************
 * Dem_MasterMainFunctionWorker
 *****************************************************************************/
/*!
 * \brief         Cyclic DemMaster worker task.
 *
 * \details       This function processes the asynchronous status changes, e.g.
 *                storing event data into the event memory, clearing the event
 *                memory and processing operation cycle changes.
 *
 *                The run-time of this function can be high depending on the
 *                configuration, and the API calls that happen to coincide.
 *
 * \pre           DemMaster has been pre-initialized.
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(void, DEM_CODE)
Dem_MasterMainFunctionWorker(
  void
  );



/* ****************************************************************************
 * Dem_MainFunctionTimer
 *****************************************************************************/
/*!
 * \brief         Cyclic Dem timer task
 *
 * \details       This function creates the time base for the Dem module.
 *
 *                Call this function in a cyclic manner, with the configured
 *                cycle time. The run-time of this function is as minimal as
 *                possible, so it can be called on a higher priority task with
 *                minimal impact.
 *
 *                If the Dem module is not initialized, calling this function
 *                has no effect.
 *
 * \pre           Dem has been pre-initialized
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MainFunctionTimer(
  void
);

/* ****************************************************************************
 * Dem_MainFunctionWorker
 *****************************************************************************/
/*!
 * \brief         Cyclic Dem worker task
 *
 * \details       This function processes the asynchronous status changes, e.g.
 *                storing event data into the event memory, clearing the event
 *                memory and processing operation cycle changes.
 *
 *                The run-time of this function can be high depending on the
 *                configuration, and the API calls that happen to coincide.
 *
 *                If the Dem module is not initialized, calling this function
 *                has no effect.
 *
 * \pre           Dem has been pre-initialized
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MainFunctionWorker(
  void
);

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DEFINITION
 *********************************************************************************************************************/

/* ****************************************************************************
 % Dem_MainFunctionTimer
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MainFunctionTimer(
  void
  )
{
  Dem_MasterMainFunctionTimer();
  Dem_SatelliteMainFunction();
}

/* ****************************************************************************
 % Dem_MainFunctionWorker
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MainFunctionWorker(
  void
  )
{
  Dem_MasterMainFunctionWorker();
}

/* ****************************************************************************
 % Dem_MasterMainFunctionTimer
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, DEM_CODE)
Dem_MasterMainFunctionTimer(
  void
  )
{
  Dem_Det_ErrorRegisterDefine()

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
  if (Dem_APIChecks_MasterAtLeastInState(DEM_INITSTATE_PREINITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  {
    /* ----- Implementation ------------------------------------------------ */
    if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == TRUE)
    {
      Dem_Timer_MainFunction();
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_MAINFUNCTION_APIID, Dem_Det_ErrorRegisterGet());
  }
}

/* ****************************************************************************
 % Dem_MasterMainFunctionWorker
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, DEM_CODE)
Dem_MasterMainFunctionWorker(
  void
  )
{
  Dem_Det_ErrorRegisterDefine()

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
  if (Dem_APIChecks_MasterAtLeastInState(DEM_INITSTATE_PREINITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  {
    /* ----- Implementation ------------------------------------------------ */
    if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == TRUE)
    {
      Dem_Scheduler_MainFunction();
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_MAINFUNCTION_APIID, Dem_Det_ErrorRegisterGet());
  }
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \addtogroup Dem_InfrastructureIF_Public
 * \{
 */
                                                   /* Interface EcuM <-> Dem */
/* ------------------------------------------------------------------------- */

/* ****************************************************************************
 % Dem_InitMemory
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, DEM_CODE)
Dem_InitMemory(
  void
  )
{
  Dem_Satellite_IdType lSatelliteId;
  for (lSatelliteId = 0u;
       lSatelliteId < Dem_Cfg_GlobalSatelliteCount();
       ++lSatelliteId)
  {
    Dem_SatelliteCore_MemoryInit(lSatelliteId);
  }

  Dem_InitState_SetInitState(DEM_INITSTATE_UNINITIALIZED);

  Dem_ConfigurationValidation_SetGlobalConfigPointerInitState(DEM_CONFIGVALIDATION_CONFIGPTR_UNINITIALIZED);
}

/* ****************************************************************************
 % Dem_MainFunction
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, DEM_CODE)
Dem_MainFunction(
  void
  )
{
  Dem_MainFunctionTimer();
  Dem_MainFunctionWorker();
}

/* ****************************************************************************
 % Dem_SatellitePreInit
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
FUNC(void, DEM_CODE)
Dem_SatellitePreInit(
  Dem_SatelliteInfoType SatelliteId
  )
{
  Dem_Det_ErrorRegisterDefine()

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
  if (Dem_APIChecks_GlobalConfigPointerInState(DEM_CONFIGVALIDATION_CONFIGPTR_PREINITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  if (Dem_APIChecks_MasterInState(DEM_INITSTATE_PREINITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  if (Dem_APIChecks_SatelliteInState(SatelliteId, DEM_INITSTATE_UNINITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  {
    /* ----- Implementation ------------------------------------------------ */
    Dem_SatelliteSat_PreInit(SatelliteId);
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_SATELLITEPREINIT_APIID, Dem_Det_ErrorRegisterGet());
  }
}


/* ****************************************************************************
 % Dem_SafePreInit
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
FUNC(void, DEM_CODE)
Dem_SafePreInit(
  P2CONST(Dem_ConfigType, AUTOMATIC, DEM_INIT_DATA)  ConfigPtr                                                                   /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  uint8 lCfgPtrInitState;
  Dem_Det_ErrorRegisterDefine()

  lCfgPtrInitState = DEM_CONFIGVALIDATION_CONFIGPTR_ERROR;
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
  if ((Dem_APIChecks_GlobalConfigPointerInState(DEM_CONFIGVALIDATION_CONFIGPTR_UNINITIALIZED) == FALSE)
     && (Dem_APIChecks_GlobalConfigPointerInState(DEM_CONFIGVALIDATION_CONFIGPTR_ERROR) == FALSE))
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  if (Dem_APIChecks_MasterInState(DEM_INITSTATE_UNINITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#if (DEM_CFG_USE_INIT_POINTER == STD_ON)
  if (ConfigPtr == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
# if (DEM_CFG_VARIANT_POSTBUILD_LOADABLE == STD_ON)
    EcuM_BswErrorHook((uint16) DEM_MODULE_ID, (uint8) ECUM_BSWERROR_NULLPTR);
# endif
  }
  else
  {
    /* ----- Implementation ------------------------------------------------ */   
    if(Dem_ConfigurationValidation_ValidateAndSetConfigPtr(ConfigPtr) == E_OK)                                                   /* SBSW_DEM_POINTER_FORWARD_API */
    {
      lCfgPtrInitState = DEM_CONFIGVALIDATION_CONFIGPTR_PREINITIALIZED;
    }
  }

  Dem_ConfigurationValidation_SetGlobalConfigPointerInitState(lCfgPtrInitState);
#else
  {
    DEM_IGNORE_UNUSED_VARIABLE(lCfgPtrInitState)                                                                                 /* PRQA S 3112 */ /* MD_DEM_14.2 */
    DEM_IGNORE_UNUSED_ARGUMENT(ConfigPtr)                                                                                        /* PRQA S 1338, 3112 */ /*  MD_MSR_DummyStmt, MD_DEM_14.2 */  
  }
#endif

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_SAFEPREINIT_APIID, Dem_Det_ErrorRegisterGet());
  }
}


/* ****************************************************************************
 % Dem_MasterPreInit
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
 *
 *
 */
FUNC(void, DEM_CODE)
Dem_MasterPreInit(
  P2CONST(Dem_ConfigType, AUTOMATIC, DEM_INIT_DATA)  ConfigPtr                                                                   /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  Dem_Det_ErrorRegisterDefine()

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  DEM_IGNORE_UNUSED_ARGUMENT(ConfigPtr)                                                                                          /* PRQA S 1338, 3112 */ /*  MD_MSR_DummyStmt, MD_DEM_14.2 */

  /* ----- Development Error Checks ---------------------------------------- */

  if (Dem_APIChecks_MasterInState(DEM_INITSTATE_UNINITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  {
#if (DEM_CFG_USE_INIT_POINTER == STD_ON)
    boolean lConfigPtrValid;
    lConfigPtrValid = FALSE;

    if (ConfigPtr == NULL_PTR)
    {
      Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
# if (DEM_CFG_VARIANT_POSTBUILD_LOADABLE == STD_ON)
      EcuM_BswErrorHook((uint16) DEM_MODULE_ID, (uint8) ECUM_BSWERROR_NULLPTR);
# endif
    }
    else
    if ((Dem_ConfigurationValidation_TestGlobalCfgPointerInState(DEM_CONFIGVALIDATION_CONFIGPTR_PREINITIALIZED) == FALSE)
      && (Dem_ConfigurationValidation_TestGlobalCfgPointerInState(DEM_CONFIGVALIDATION_CONFIGPTR_UNINITIALIZED) == FALSE)
      )
    {
      Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION);
    }
    else
    {
      if (Dem_ConfigurationValidation_TestGlobalCfgPointerInState(DEM_CONFIGVALIDATION_CONFIGPTR_PREINITIALIZED) == TRUE)
      {
        lConfigPtrValid = TRUE;
      }
      else
      if (Dem_ConfigurationValidation_ValidateAndSetConfigPtr(ConfigPtr) == E_OK)                                                /* SBSW_DEM_POINTER_FORWARD_API */
      {
        lConfigPtrValid = TRUE;
      }
      else
      {
        /* MISRA */
      }
    }
    if (lConfigPtrValid == TRUE)
#endif
    {
      /* ----- Implementation ---------------------------------------------- */
#if (DEM_CFG_USE_INIT_POINTER == STD_ON)
      Dem_ConfigurationValidation_SetGlobalConfigPointerInitState(DEM_CONFIGVALIDATION_CONFIGPTR_PREINITIALIZED);
#endif

      Dem_Error_InitErrorDetection();
      /* Initialize flag to be able to detect a call of Dem_Nvm_InitAdminData
      after pre-initialization */
      Dem_Memory_SetInitAdminDataRequested(FALSE);

      Dem_EnableCondition_PreInit();
      Dem_StorageCondition_PreInit();
      Dem_OperationCycle_PreInit();
      Dem_Event_PreInit();
      Dem_DTC_PreInit();
      Dem_Dtr_PreInit();

      /* At this point:
       - BSW error reporting is enabled (Dem_ReportErrorStatus)
       - NvM has write access to RAM buffers (Dem may not access them!) */
      Dem_InitState_SetInitState(DEM_INITSTATE_PREINITIALIZED);
    }
#if (DEM_CFG_USE_INIT_POINTER == STD_ON)
    else
    {
      /* MISRA */
    }
#endif
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_PREINIT_APIID, Dem_Det_ErrorRegisterGet());
  }
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_PreInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, DEM_CODE)
Dem_PreInit(
  P2CONST(Dem_ConfigType, AUTOMATIC, DEM_INIT_DATA)  ConfigPtr                                                                   /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  Dem_Det_ErrorRegisterDefine()

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
  if (Dem_APIChecks_SingleSatellite() == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  {
    /* ----- Implementation ------------------------------------------------ */
    Dem_MasterPreInit(ConfigPtr);                                                                                                /* SBSW_DEM_POINTER_FORWARD_API */
    Dem_SatellitePreInit(DEM_SATELLITE_APPLICATION_ZERO);
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_PREINIT_APIID, Dem_Det_ErrorRegisterGet());
  }
}

/* ****************************************************************************
 % Dem_SatelliteInit
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
FUNC(void, DEM_CODE)
Dem_SatelliteInit(
  Dem_SatelliteInfoType  SatelliteId
  )
{
  Dem_Det_ErrorRegisterDefine()

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
  if (Dem_APIChecks_GlobalConfigPointerInState(DEM_CONFIGVALIDATION_CONFIGPTR_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  if (Dem_APIChecks_MasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  if (Dem_APIChecks_SatelliteInState(SatelliteId, DEM_INITSTATE_PREINITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  {
    /* ----- Implementation ------------------------------------------------ */
    Dem_SatelliteSat_Init(SatelliteId);
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_SATELLITEINIT_APIID, Dem_Det_ErrorRegisterGet());
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */


/* ****************************************************************************
 % Dem_SafeInit
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
FUNC(void, DEM_CODE)
Dem_SafeInit(
  P2CONST(Dem_ConfigType, AUTOMATIC, DEM_INIT_DATA)  ConfigPtr                                                                   /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  uint8 lCfgPtrInitState;
  Dem_Det_ErrorRegisterDefine()

  lCfgPtrInitState = DEM_CONFIGVALIDATION_CONFIGPTR_ERROR;
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
  if (Dem_APIChecks_GlobalConfigPointerInState(DEM_CONFIGVALIDATION_CONFIGPTR_PREINITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  if (Dem_APIChecks_MasterInState(DEM_INITSTATE_PREINITIALIZED) == FALSE)                                           
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  if (Dem_InitState_TestAllSatellitesAtLeastInState(DEM_INITSTATE_PREINITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#if (DEM_CFG_USE_INIT_POINTER == STD_ON)
  {
    /* ----- Implementation ------------------------------------------------ */
    if (ConfigPtr == NULL_PTR)
    {
      lCfgPtrInitState = DEM_CONFIGVALIDATION_CONFIGPTR_INITIALIZED;
    }
    else
    if (Dem_ConfigurationValidation_ValidateAndSetConfigPtr(ConfigPtr) == E_OK)                                             /* SBSW_DEM_POINTER_FORWARD_API */
    {
      lCfgPtrInitState = DEM_CONFIGVALIDATION_CONFIGPTR_INITIALIZED;
    }
    else
    {
      /* MISRA */
    }
  }
  
  Dem_ConfigurationValidation_SetGlobalConfigPointerInitState(lCfgPtrInitState);
#else
  {
    DEM_IGNORE_UNUSED_VARIABLE(lCfgPtrInitState)                                                                                 /* PRQA S 3112 */ /* MD_DEM_14.2 */
    DEM_IGNORE_UNUSED_ARGUMENT(ConfigPtr)                                                                                        /* PRQA S 1338, 3112 */ /*  MD_MSR_DummyStmt, MD_DEM_14.2 */  
  }
#endif

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_SAFEINIT_APIID, Dem_Det_ErrorRegisterGet());
  }
}                                                                                                                                /* PRQA S 6080 */ /* MD_MSR_STMIF */


/* ****************************************************************************
 % Dem_MasterInit
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
FUNC(void, DEM_CODE)
Dem_MasterInit(
  P2CONST(Dem_ConfigType, AUTOMATIC, DEM_INIT_DATA)  ConfigPtr                                                                   /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  Dem_Det_ErrorRegisterDefine()

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  DEM_IGNORE_UNUSED_ARGUMENT(ConfigPtr)                                                                                          /* PRQA S 1338, 3112 */ /*  MD_MSR_DummyStmt, MD_DEM_14.2 */

  /* ----- Development Error Checks ---------------------------------------- */
  if ( (Dem_APIChecks_MasterInState(DEM_INITSTATE_PREINITIALIZED) == FALSE)
    && (Dem_APIChecks_MasterInState(DEM_INITSTATE_SHUTDOWN) == FALSE) )                                                                                                         
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  if (Dem_InitState_TestAllSatellitesAtLeastInState(DEM_INITSTATE_PREINITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#if (DEM_DEV_ERROR_DETECT == STD_ON)
# if (DEM_CFG_USE_INIT_POINTER == STD_ON)
  if ( (Dem_APIChecks_MasterInState(DEM_INITSTATE_SHUTDOWN) == TRUE)
    && (ConfigPtr != NULL_PTR)
    && (Dem_GlobalConfigPtr != ConfigPtr) )
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  if ((Dem_ConfigurationValidation_TestGlobalCfgPointerInState(DEM_CONFIGVALIDATION_CONFIGPTR_UNINITIALIZED) == TRUE)
     || (Dem_ConfigurationValidation_TestGlobalCfgPointerInState(DEM_CONFIGVALIDATION_CONFIGPTR_ERROR) == TRUE))
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION);
  }
  else
# endif
#endif
  {
    /* ----- Implementation ------------------------------------------------ */
#if (DEM_CFG_USE_INIT_POINTER == STD_ON)
    if (Dem_ConfigurationValidation_TestGlobalCfgPointerInState(DEM_CONFIGVALIDATION_CONFIGPTR_PREINITIALIZED) == TRUE)
    {
      if (ConfigPtr == NULL_PTR)
      {
        Dem_ConfigurationValidation_SetGlobalConfigPointerInitState(DEM_CONFIGVALIDATION_CONFIGPTR_INITIALIZED);
      }
      else
      if (Dem_ConfigurationValidation_ValidateAndSetConfigPtr(ConfigPtr) == E_OK)                                           /* SBSW_DEM_POINTER_FORWARD_API */
      {
        Dem_ConfigurationValidation_SetGlobalConfigPointerInitState(DEM_CONFIGVALIDATION_CONFIGPTR_INITIALIZED);
      }
      else
      {
        /* MISRA */
      }
    }

    if (Dem_ConfigurationValidation_TestGlobalCfgPointerInState(DEM_CONFIGVALIDATION_CONFIGPTR_INITIALIZED) == TRUE)
#endif
    {
      Dem_Scheduler_Init();
      Dem_Timer_Init();
      Dem_Client_ClientAccess_Init();
      Dem_EventQueueCore_Init();
      Dem_ClearTask_Init();
      Dem_Queue_Init();
      Dem_Nvm_Init();
      Dem_Memory_Init();
      Dem_Indicator_Init();
      Dem_Event_Init();
      Dem_DTC_Init();
      Dem_OperationCycle_Init();
      Dem_Mem_Init_RestoreMemoryObd();
      Dem_Memory_TimeSeries_RestoreOnInit();
      if (Dem_Cfg_IsPermanentSupportedInVariant() == TRUE)
      {
#if (DEM_CFG_SUPPORT_PERMANENTDTC_ACTIVATION_DISTANCE == STD_ON)
        if ( (Dem_Cfg_IsObdIISupportedInVariant() == TRUE)
          && (Dem_Mem_GetPermanentActivationState() == TRUE) )
#endif
        {
          Dem_Memory_PermanentFillUp();
        }
      }

      Dem_Dtr_Init();
      Dem_Dcm_Init();
      Dem_Iumpr_Init();

      Dem_InitState_SetInitState(DEM_INITSTATE_INITIALIZED);
#if (DEM_CFG_NOTIFY_MONITOR_STATUS_FIM == STD_ON)
# if (DEM_CFG_USE_MULTI_PARTITION_FIM == STD_ON)
      FiM_DemInitMaster();
# else
      FiM_DemInit();
# endif
#endif
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_INIT_APIID, Dem_Det_ErrorRegisterGet());
  }
}                                                                                                                                /* PRQA S 6030, 6050, 6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_Init
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, DEM_CODE)
Dem_Init(
  P2CONST(Dem_ConfigType, AUTOMATIC, DEM_INIT_DATA)  ConfigPtr                                                                   /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  Dem_Det_ErrorRegisterDefine()

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
  if (Dem_APIChecks_SingleSatellite() == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  {
    /* ----- Implementation ------------------------------------------------ */
    if (Dem_InitState_TestMasterInState(DEM_INITSTATE_SHUTDOWN) == TRUE)
    {
      Dem_MasterInit(ConfigPtr);                                                                                                 /* SBSW_DEM_POINTER_FORWARD_API */
    }
    else
    {
      Dem_MasterInit(ConfigPtr);                                                                                                 /* SBSW_DEM_POINTER_FORWARD_API */
      Dem_SatelliteInit(DEM_SATELLITE_APPLICATION_ZERO);
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_INIT_APIID, Dem_Det_ErrorRegisterGet());
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_Shutdown
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
FUNC(void, DEM_CODE)
Dem_Shutdown(
  void
  )
{
  Dem_Det_ErrorRegisterDefine()

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
  if (Dem_APIChecks_MasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
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

#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
    boolean lPostRunRequested;
    lPostRunRequested = FALSE;
    (void)Dem_PostRunRequested(&lPostRunRequested);                                                                              /* SBSW_DEM_POINTER_FORWARD_STACK */
    if (lPostRunRequested == TRUE)
    { /* Only set the error, but perform the shutdown. We are not going to stop
       * the shutdown anyway, so rescue as much state as possible */
      Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
    }
#endif

    Dem_InitState_SetInitState(DEM_INITSTATE_SHUTDOWN);

    Dem_Dtr_Shutdown();

    Dem_OperationCycle_Shutdown();

    /* copy debounce values from debounce array to nvram mirror */
    Dem_Mem_CopyDataDebounceNv(DEM_NVM_BLOCKSTATE_DIRTY);

#if (DEM_CFG_USE_NVM == STD_ON)
    Dem_Nvm_Shutdown();
#endif
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_SHUTDOWN_APIID, Dem_Det_ErrorRegisterGet());
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_MasterMainFunction
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, DEM_CODE)
Dem_MasterMainFunction(
  void
  )
{
  Dem_MasterMainFunctionTimer();
  Dem_MasterMainFunctionWorker();
}

/* ****************************************************************************
 % Dem_SatelliteMainFunction
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
FUNC(void, DEM_CODE)
Dem_SatelliteMainFunction(
  void
  )
{
  Dem_Det_ErrorRegisterDefine()

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
  if (Dem_APIChecks_GlobalConfigPointerAtleastInState(DEM_CONFIGVALIDATION_CONFIGPTR_PREINITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  {
    Dem_Satellite_IdType lSatelliteId;
    lSatelliteId = Dem_Satellite_GetCurrentSatelliteId();

    if (Dem_APIChecks_SatelliteAtLeastInState(lSatelliteId, DEM_INITSTATE_PREINITIALIZED) == FALSE)
    {
      Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
    }
    else
    {
      /* ----- Implementation ------------------------------------------------ */
      if ((Dem_InitState_TestSatelliteAtLeastInState(lSatelliteId, DEM_INITSTATE_INITIALIZED) == TRUE)
        && (Dem_APIChecks_GlobalConfigPointerInState(DEM_CONFIGVALIDATION_CONFIGPTR_INITIALIZED) == TRUE))
      {
        Dem_SatelliteSat_MainFunction(lSatelliteId);
      }
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_SATELLITEMAINFUNCTION_APIID, Dem_Det_ErrorRegisterGet());
  }
}

#if (DEM_CFG_SUPPORT_NVM_APPL_SYNCHRONIZE == STD_ON)
/* ****************************************************************************
 % Dem_RequestNvSynchronization
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
Dem_RequestNvSynchronization(
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
  if (Dem_APIChecks_IsMasterPartition() == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  {
    /* ----- Implementation ------------------------------------------------ */
# if (DEM_CFG_USE_NVM == STD_ON)
    Dem_Nvm_SetSynchronizationFlag();
    lReturnValue = E_OK;
# else
    lReturnValue = E_NOT_OK;
# endif
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_REQUESTNVSYNCHRONIZATION_APIID, Dem_Det_ErrorRegisterGet());
  }
  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_VERSION_INFO == STD_ON)
/* ****************************************************************************
 % Dem_GetVersionInfo
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, DEM_CODE)
Dem_GetVersionInfo(
  P2VAR(Std_VersionInfoType, AUTOMATIC, DEM_APPL_DATA)  versioninfo
  )
{
  Dem_Det_ErrorRegisterDefine()

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
  if (Dem_APIChecks_NullPointer(versioninfo) == FALSE)                                                                           /* SBSW_DEM_POINTER_NULLPTR_CHECKING */ /* PRQA S 0315 */ /* MD_DEM_Dir1.1 */
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  {
    /* ----- Implementation ------------------------------------------------ */
    versioninfo->vendorID = DEM_VENDOR_ID;                                                                                       /* SBSW_DEM_POINTER_WRITE_API */
    versioninfo->moduleID = DEM_MODULE_ID;                                                                                       /* SBSW_DEM_POINTER_WRITE_API */
    versioninfo->sw_major_version = DEM_SW_MAJOR_VERSION;                                                                        /* SBSW_DEM_POINTER_WRITE_API */
    versioninfo->sw_minor_version = DEM_SW_MINOR_VERSION;                                                                        /* SBSW_DEM_POINTER_WRITE_API */
    versioninfo->sw_patch_version = DEM_SW_PATCH_VERSION;                                                                        /* SBSW_DEM_POINTER_WRITE_API */
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETVERSIONINFO_APIID, Dem_Det_ErrorRegisterGet());
  }
}
#endif /* (DEM_CFG_SUPPORT_VERSION_INFO == STD_ON) */

                                                     /* Extension to Autosar */
/* ------------------------------------------------------------------------- */

/* ****************************************************************************
 % Dem_PostRunRequested
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
Dem_PostRunRequested(
  P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA)  IsRequested
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
  if (Dem_APIChecks_NullPointer(IsRequested) == FALSE)                                                                           /* SBSW_DEM_POINTER_NULLPTR_CHECKING */  /* PRQA S 0315 */ /* MD_DEM_Dir1.1 */
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
#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
    if ( (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == TRUE)
      && (Dem_Nvm_IsCurrentlyWrittenBlockModified() == TRUE ) )                                                                  
    { /* Currently waiting for NvM JobResult, and the same block is still in the process
         of committing a previous data set - we are not allowed to mark this block using
         NvM_SetRamBlockStatus -> return TRUE to request more time untile the situation
         has resulved itself */
      *IsRequested = TRUE;                                                                                                       /* SBSW_DEM_POINTER_WRITE_API */
    }
    else
    {
      *IsRequested = FALSE;                                                                                                      /* SBSW_DEM_POINTER_WRITE_API */
    }
    lReturnValue = E_OK;
#else
  /* No immediate Nv-Write is supported, always return false */
    *IsRequested = FALSE;                                                                                                        /* SBSW_DEM_POINTER_WRITE_API */
    lReturnValue = E_OK;
#endif
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_POSTRUNREQUESTED_APIID, Dem_Det_ErrorRegisterGet());
  }
  return lReturnValue;
}
                                                                /* Callbacks */
/* ------------------------------------------------------------------------- */

/* ****************************************************************************
 % Dem_NvM_InitAdminData
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
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_NvM_InitAdminData(
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
    uint8 lCycleIterator;

    /* ----- Implementation ------------------------------------------------ */
    Dem_Memory_SetInitAdminDataRequested(TRUE);

    Dem_Cfg_AdminData.ImplementationVersion = Dem_Make16Bit(DEM_SW_MAJOR_VERSION, DEM_SW_MINOR_VERSION);
    Dem_Cfg_AdminData.ConfigurationId = Dem_Cfg_GlobalConfigurationId();

    for (lCycleIterator = 0U; lCycleIterator < Dem_Cfg_GlobalCycleCount(); ++lCycleIterator)
    {
      Dem_OperationCycle_SetCycleCounter(lCycleIterator, 0U);
    }
#if (DEM_FEATURE_NEED_OVFLIND == STD_ON)
    Dem_Cfg_AdminData.MemoryOverflow = 0U;
#endif

#if (DEM_CFG_SUPPORT_OPCYCLE_STORAGE == STD_ON)
    Dem_Cfg_AdminData.CycleState = 0x00U;
    Dem_Cfg_AdminData.CycleState = (Dem_Cfg_AdminData.CycleState | ((uint16)1 << Dem_Cfg_GlobalObdDrivingCycleId()));
#endif
#if (DEM_FEATURE_NEED_OBD == STD_ON)
    /* clear the qualified driving cycle state and the Pfc cycle state */
    Dem_OperationCycle_SetObdCycleStates(0x00u);
#endif

#if (DEM_FEATURE_NEED_GLOBAL_MIL_STATE == STD_ON)
    /* Clear PID21 and PID4D aging counter */
    Dem_Mem_SetPidAgingCounter(0u);
#endif

#if (DEM_CFG_SUPPORT_PID21 == STD_ON)
    /* Clear Odometer for MIL on */
    Dem_Mem_SetOdometerMilOn(0u);
#endif
#if (DEM_CFG_SUPPORT_PID30 == STD_ON)
    /* Clear WarmUpCountAtClear */
    Dem_Mem_SetWarmUpCountSinceClear(0u);
#endif
#if (DEM_CFG_SUPPORT_PID31 == STD_ON)
    /* Set Odometer at clear to invalid, so the first valid odometer is stored on main task */
    Dem_Mem_SetOdometerAtClear(DEM_MEM_SET_ODOMETER_INVALID(0u));
#endif
#if (DEM_CFG_SUPPORT_PID4D == STD_ON)
    Dem_Mem_SetEngineTimeMilOn(0u);
#endif
#if (DEM_CFG_SUPPORT_PID4E == STD_ON)
    Dem_Mem_SetEngineTimeSinceClear(0u);
#endif
#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
    Dem_Mem_SetB1Counter(0u);
    Dem_Mem_SetB1HealingCounter(0u);
    Dem_Mem_SetContinuousMiCounter(0u);
    Dem_Mem_SetContinuousMiAgingCounter(DEM_DATA_CONTINUOUS_MI_AGING_COUNTER_AGED);
    Dem_Mem_SetContinuousMiHealingCounter(DEM_DATA_CONTINUOUS_MI_HEALING_COUNTER_HEALED);
    Dem_Mem_SetContinuousMiAgingTimer(DEM_DATA_CONTINUOUS_MI_AGING_TIMER_AGED);
    Dem_Mem_SetCumulativeEngRuntime(0u);
#endif
    /* Clear Ignition Cycle Counter(s) */
    Dem_Iumpr_InitCycleCounter();                                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2_CONFIGURATION_SWITCH */

#if (DEM_CFG_SUPPORT_PERMANENTDTC_ACTIVATION_DISTANCE == STD_ON)
    Dem_Mem_SetPermanentActivationState(FALSE);
    Dem_Mem_SetPermanentActivationDistance(DEM_MEM_SET_ODOMETER_INVALID(0u));
#endif
#if (DEM_FEATURE_NEED_PID41_CALCULATION == STD_ON)
    Dem_Mem_SetPid41DisabledMask(0u);
#endif
  }

  /* ----- Development Error Report ---------------------------------------- */
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_NVMINIT_APIID, Dem_Det_ErrorRegisterGet());
  }

  /* The DEM expects that the NVM by itself marks the NVRAM block as dirty */
  return E_OK;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

#if ((DEM_CFG_USE_NVM == STD_ON) && (DEM_CFG_SUPPORT_NVM_POLLING == STD_OFF))
/* ****************************************************************************
 % Dem_NvM_JobFinished
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_NvM_JobFinished(
  uint8  ServiceId,                                                                                                              /* PRQA S 3206 */ /* MD_DEM_3206 */
  NvM_RequestResultType  JobResult                                                                                               /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_ARGUMENT(ServiceId)                                                                                          /* PRQA S 1338, 3112 */ /* MD_MSR_DummyStmt, MD_DEM_14.2 */
  Dem_Nvm_ChangeNVWriteState(JobResult);
  return E_OK;
}
#endif /* ((DEM_CFG_USE_NVM == STD_ON) && (DEM_CFG_SUPPORT_NVM_POLLING == STD_OFF)) */
/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ********************************************************************************************************************
 *  FILE SPECIFIC MISRA VIOLATIONS
 *********************************************************************************************************************/
/* PRQA L:DEM_API_IMPL */


#endif /* DEM_INFRASTRUCTUREIF_SVC_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_InfrastructureIF_Svc.h
 *********************************************************************************************************************/
