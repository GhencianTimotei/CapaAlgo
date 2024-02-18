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
 *  \file       Dem_Scheduler_Types.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Public types of Scheduler subcomponent
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_SCHEDULER_TYPES_H)
#define DEM_SCHEDULER_TYPES_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_Int.h"
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
/*! Task Handle, in order of priority, up to 32 tasks can be defined since these enums are mapped to uint32 bitfield Dem_Scheduler_XXX */
enum Dem_Scheduler_TaskId
{
  Dem_Scheduler_Task_Dtr,
  Dem_Scheduler_Task_Prestorage,
  Dem_Scheduler_Task_ClearTask,
  Dem_Scheduler_Task_Event,
  Dem_Scheduler_Task_TimeSeries,
  Dem_Scheduler_Task_FilterEventData,
  Dem_Scheduler_Task_EnableCondition,
  Dem_Scheduler_Task_EventQueue,
  Dem_Scheduler_Task_StatusIndicator,
  Dem_Scheduler_Task_IUMPR,
  Dem_Scheduler_Task_OperationCycle,
  Dem_Scheduler_Task_Odometer,
  Dem_Scheduler_Task_EngineRuntime,
  Dem_Scheduler_Task_PID01,
  Dem_Scheduler_Task_NvM,
  Dem_Scheduler_Task_Invalid          /* First enum value that is not yet used */
};

typedef enum Dem_Scheduler_TaskId Dem_Scheduler_TaskIdType;

#endif /* DEM_SCHEDULER_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Scheduler_Types.h
 *********************************************************************************************************************/
