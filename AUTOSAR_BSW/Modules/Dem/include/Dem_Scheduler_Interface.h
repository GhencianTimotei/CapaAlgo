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
/*! \ingroup    Dem_Master
 *  \defgroup   Dem_Scheduler Scheduler
 *  \{
 *  \file       Dem_Scheduler_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Public interface of Scheduler subcomponent
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_SCHEDULER_INTERFACE_H)
#define DEM_SCHEDULER_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_Scheduler_Types.h"
/* ------------------------------------------------------------------------- */


/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_Scheduler_Public Public Methods
 * \{
 */

/* ****************************************************************************
 * Dem_Scheduler_Init
 *****************************************************************************/
/*!
 * \brief         Init asynchronous tasks.
 *
 * \details       Init asynchronous tasks.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Scheduler_Init(
  void
  );

/* ****************************************************************************
 * Dem_Scheduler_MainFunction
 *****************************************************************************/
/*!
 * \brief         Process asynchronous tasks.
 *
 * \details       This function performs asynchronous tasks.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Scheduler_MainFunction(
  void
  );

/* ****************************************************************************
 * Dem_Scheduler_EnableTask
 *****************************************************************************/
/*!
 * \brief         Enable asynchronous task.
 *
 * \details       Schedules the given task
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
Dem_Scheduler_EnableTask(
  CONST(Dem_Scheduler_TaskIdType, AUTOMATIC) TaskId
  );


/* ****************************************************************************
 * Dem_Scheduler_EnableTaskOnce
 *****************************************************************************/
/*!
 * \brief         Enable asynchronous task.
 *
 * \details       Schedules the given task and disables it afterwards.
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
Dem_Scheduler_EnableTaskOnce(
  CONST(Dem_Scheduler_TaskIdType, AUTOMATIC) TaskId
  );

/* ****************************************************************************
 * Dem_Scheduler_DisableTask
 *****************************************************************************/
/*!
 * \brief         Disable asynchronous task.
 *
 * \details       Stops scheduling of the given task.
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
Dem_Scheduler_DisableTask(
  CONST(Dem_Scheduler_TaskIdType, AUTOMATIC) TaskId
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_SCHEDULER_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Scheduler_Interface.h
 *********************************************************************************************************************/
