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
/*! \addtogroup Dem_Scheduler
 *  \{
 *  \file       Dem_Scheduler_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Implementation of Scheduler subcomponent
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_SCHEDULER_IMPLEMENTATION_H)
#define DEM_SCHEDULER_IMPLEMENTATION_H

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
#include "Dem_Scheduler_Interface.h"

/* Includes to access public functions belonging to other (top level)/ (logical)/- units to be used by this Unit */
/* ------------------------------------------------------------------------- */
#include "Dem_DiagnosticObserver_Interface.h"
#include "Dem_Core_Interface.h"
#include "Dem_GlobalDiagnostics_Interface.h"
#include "Dem_Client_Interface.h"
#include "Dem_FaultMemory_Interface.h"
#include "Dem_Com_Interface.h"
#include "Dem_EventQueue_Interface.h"
#include "Dem_Error_Interface.h"
#include "Dem_Nvm_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*! Filename declaration */
#define DEM_SCHEDULER_IMPLEMENTATION_FILENAME "Dem_Scheduler_Implementation.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/
#define DEM_START_SEC_VAR_NOINIT_32BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

DEM_LOCAL volatile VAR(uint32, DEM_VAR_NOINIT) Dem_Scheduler_ScheduledMultipleInvocationTasks;
DEM_LOCAL volatile VAR(uint32, DEM_VAR_NOINIT) Dem_Scheduler_ScheduledSingleInvocationTasks;

#define DEM_STOP_SEC_VAR_NOINIT_32BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_Scheduler_Private Private Methods
 * \{
 */


/* ****************************************************************************
 * Dem_Scheduler_GetAndClearScheduledTasks
 *****************************************************************************/
/*!
 * \brief         Consume the 'scheduled once' task bitmask
 *
 * \details       Atomically fetches the currently 'scheduled once' task bitmap
 *                and clears it
 *
 * \return        The current 'scheduled once' task bitmap
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint32, DEM_CODE)
Dem_Scheduler_GetAndClearScheduledTasks(
  void
  );


/* ****************************************************************************
 * Dem_Scheduler_CallTask
 *****************************************************************************/
/*!
 * \brief         Call the given worker task
 *
 * \details       Call the given worker task
 *
 * \param[in]     TaskId
 *                Handle of the worker task
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Scheduler_CallTask(
  CONST(Dem_Scheduler_TaskIdType, AUTOMATIC) TaskId
  );

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/

/* ****************************************************************************
 % Dem_Scheduler_GetAndClearScheduledTasks
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint32, DEM_CODE)
Dem_Scheduler_GetAndClearScheduledTasks(
  void
  )
{
  uint32 lScheduledTasks;
  do
  {
    lScheduledTasks = Dem_Scheduler_ScheduledSingleInvocationTasks;
    if (lScheduledTasks == 0u)
    {
      break;
    }
  }
  while (Dem_Com_SyncCompareAndSwap(&Dem_Scheduler_ScheduledSingleInvocationTasks, lScheduledTasks, 0) == FALSE);                /* SBSW_DEM_POINTER_FORWARD_GLOBAL */
  return lScheduledTasks;
}

/* ****************************************************************************
 % Dem_Scheduler_CallTask
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Scheduler_CallTask(
  CONST(Dem_Scheduler_TaskIdType, AUTOMATIC) TaskId
  )
{
  switch (TaskId)
  {
  case Dem_Scheduler_Task_Dtr:
    Dem_Dtr_MainFunction();
    break;
  case Dem_Scheduler_Task_Prestorage:
    Dem_Prestore_MainFunction();
    break;
  case Dem_Scheduler_Task_ClearTask:
    Dem_ClearTask_MainFunction();
    break;
  case Dem_Scheduler_Task_Event:
    Dem_Event_MainFunction();
    break;
  case Dem_Scheduler_Task_TimeSeries:
    Dem_Memory_TimeSeries_ProcessWorkerTask();
    break;
  case Dem_Scheduler_Task_FilterEventData:
    Dem_Client_ClientAccess_FillDTCReadoutBufferData();
    break;
  case Dem_Scheduler_Task_EnableCondition:
    Dem_EnableCondition_MainFunction();
    break;
  case Dem_Scheduler_Task_EventQueue:
    Dem_EventQueueCore_MainFunction();
    break;
  case Dem_Scheduler_Task_StatusIndicator:
    Dem_StatusIndicator_MainFunction();
    break;
  case Dem_Scheduler_Task_IUMPR:
    Dem_Iumpr_MainFunction();
    break;
  case Dem_Scheduler_Task_OperationCycle:
    Dem_OperationCycle_MainFunction();
    break;
  case Dem_Scheduler_Task_Odometer:
    Dem_Queue_ProcessOdometer();
    break;
  case Dem_Scheduler_Task_EngineRuntime:
    Dem_Queue_ProcessEngineRuntime();
    break;
  case Dem_Scheduler_Task_PID01:
    Dem_Queue_CalculatePid01();
    break;
  case Dem_Scheduler_Task_NvM:
    Dem_Nvm_MainFunction();
    break;
  default:                                                                                                                       /* PRQA S 2016 */ /* MD_MSR_EmptyClause */
    Dem_Internal_AssertAlways(DEM_E_PARAM_CONFIG)
    break;
  }
}                                                                                                                                /* PRQA S 6030, 6050 */ /* MD_MSR_STCYC, MD_MSR_STCAL */

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
 * \addtogroup Dem_Scheduler_Public
 * \{
 */

/* ****************************************************************************
 % Dem_Scheduler_Init
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Scheduler_Init(
  void
  )
{
  Dem_Scheduler_ScheduledMultipleInvocationTasks = 0U;
  Dem_Scheduler_ScheduledSingleInvocationTasks = 0U;
}

/* ****************************************************************************
 % Dem_Scheduler_MainFunction
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Scheduler_MainFunction(
  void
  )
{
  uint32 lActiveTasks;
  uint8 lCurrentTask;

  lActiveTasks = (uint32)(Dem_Scheduler_ScheduledMultipleInvocationTasks | Dem_Scheduler_GetAndClearScheduledTasks());
  lCurrentTask = 0u;

  while (lActiveTasks != 0u)
  {
    while (DEM_TEST_BIT(lActiveTasks, 0u) == FALSE)
    {
      lActiveTasks = (uint32)(lActiveTasks >> 1u);
      ++lCurrentTask;
    }

    Dem_Scheduler_CallTask((Dem_Scheduler_TaskIdType)lCurrentTask);                                                              /* PRQA S 4342 */ /* MD_DEM_Rule10.5_Enum */

    lActiveTasks = (uint32)(lActiveTasks >> 1u);
    ++lCurrentTask;
  }
}

/* ****************************************************************************
 % Dem_Scheduler_EnableTask
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Scheduler_EnableTask(
  CONST(Dem_Scheduler_TaskIdType, AUTOMATIC) TaskId
  )
{
  Dem_Com_SyncSetBitInBitfield(&Dem_Scheduler_ScheduledMultipleInvocationTasks, 1u, (Dem_HandleType)TaskId);                      /* SBSW_DEM_POINTER_FORWARD_GLOBAL */
}

/* ****************************************************************************
 % Dem_Scheduler_EnableTaskOnce
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Scheduler_EnableTaskOnce(
  CONST(Dem_Scheduler_TaskIdType, AUTOMATIC) TaskId
  )
{
  Dem_Com_SyncSetBitInBitfield(&Dem_Scheduler_ScheduledSingleInvocationTasks, 1u, (Dem_HandleType)TaskId);                        /* SBSW_DEM_POINTER_FORWARD_GLOBAL */
}

/* ****************************************************************************
 % Dem_Scheduler_DisableTask
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Scheduler_DisableTask(
  CONST(Dem_Scheduler_TaskIdType, AUTOMATIC) TaskId
  )
{
  Dem_Com_SyncResetBitInBitfield(&Dem_Scheduler_ScheduledMultipleInvocationTasks, 1u, (Dem_HandleType)TaskId);                    /* SBSW_DEM_POINTER_FORWARD_GLOBAL */
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */


#endif /* DEM_SCHEDULER_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Scheduler_Implementation.h
 *********************************************************************************************************************/
