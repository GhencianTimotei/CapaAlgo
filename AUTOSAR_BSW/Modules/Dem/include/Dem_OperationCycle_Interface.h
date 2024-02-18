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
 *  \defgroup   Dem_OperationCycle OperationCycle
 *  \{
 *  \file       Dem_OperationCycle_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_OPERATIONCYCLE_INTERFACE_H)
#define DEM_OPERATIONCYCLE_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_OperationCycle_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_OperationCycle_PublicProperties Public Properties
 * \{
 */
/* ****************************************************************************
 * Dem_OperationCycle_GetCurrentCycleStatus
 *****************************************************************************/
/*!
 * \brief         Gets the current state of a cycle.
 *
 * \details       Gets the current state of a cycle.
 *
 * \param[in]     CycleId
 *                Unique Id of the cycle
 *
 * \return        DEM_OPERATIONCYCLE_CYCLE_STARTED
 *                The cycle is currently started
 * \return        DEM_OPERATIONCYCLE_CYCLE_STOPPED
 *                The cycle is currently stopped
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_OperationCycle_GetCurrentCycleStatus(
  CONST(uint8, AUTOMATIC)  CycleId
  );


/* ****************************************************************************
 * Dem_OperationCycle_GetCycleCounter
 *****************************************************************************/
/*!
 * \brief         Get current counter of the cycle
 *
 * \details       Get current counter of the cycle
 *
 * \param[in]     CycleId
 *                Unique handle of the cycle
 *
 * \return        Current counter of the cycle
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_OperationCycle_GetCycleCounter(
  CONST(uint8, AUTOMATIC) CycleId
  );

/* ****************************************************************************
 * Dem_OperationCycle_SetCycleCounter
 *****************************************************************************/
/*!
 * \brief         Set current counter value of the cycle
 *
 * \details       Set current counter value of the cycle
 *
 * \param[in]     CycleId
 *                Unique handle of the cycle
 * \param[in]     CycleCounter
 *                New counter value of the cycle
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_SetCycleCounter(
  CONST(uint8, AUTOMATIC) CycleId,
  CONST(uint16, AUTOMATIC) CycleCounter
  );

/* ****************************************************************************
 * Dem_OperationCycle_AddCycleCount
 *****************************************************************************/
/*!
 * \brief         Calculates wrapped cycle counter
 *
 * \details       This function increments and wraps a cycle count avoiding
 *                overflow and 'magic numbers'.
 *
 * \param[in]     CurrentCounter
 *                Current value of the cycle counter
 * \param[in]     DeltaValue
 *                Value by which CurrentCounter is incremented.
 *
 * \return        Value of (CurrentCounter + DeltaValue) mod X
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_OperationCycle_AddCycleCount(
  CONST(uint16, AUTOMATIC)  CurrentCounter,
  CONST(uint8, AUTOMATIC)  DeltaValue
  );

/* ****************************************************************************
 * Dem_OperationCycle_CycleCountDistance
 *****************************************************************************/
/*!
 * \brief         Calculates the distance between cycle counter values
 *
 * \details       Calculates the distance between cycle counter values
 *
 * \param[in]     CurrentCounter
 *                Current value of the cycle counter
 * \param[in]     TargetCounter
 *                Target counter value to find the distance to
 *
 * \return        Number of increments until current counter reaches target
 *                counter
 *
 * \pre           -
*
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(uint16, DEM_CODE)
Dem_OperationCycle_CycleCountDistance(
  CONST(uint16, AUTOMATIC)  CurrentCounter,
  CONST(uint16, AUTOMATIC)  TargetCounter
  );





/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_OperationCycle_Public Public Methods
 * \{
 */

/* ****************************************************************************
 * Dem_OperationCycle_UpdateCycleStatesInNvBlock
 *****************************************************************************/
/*!
 * \brief         Update the cycle states in Nv block
 *
 * \details       Update the cycle states in Nv block
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_UpdateCycleStatesInNvBlock(
  void
  );

/* ****************************************************************************
 * Dem_OperationCycle_MainFunction
 *****************************************************************************/
/*!
 * \brief         Process all queued operation cycle changes
 *
 * \details       Process all queued operation cycle changes
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_MainFunction(
  void
  );

/* ****************************************************************************
 * Dem_OperationCycle_CycleUpdate
 *****************************************************************************/
/*!
 * \brief         Updates cycle state
 *
 * \details       Updates cycle state
 *
 * \param[in]     CycleId
 *                Unique Id of the cycle
 *
 * \param[in]     CycleStatus
 *                Cycle status changes
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_OperationCycle_CycleUpdate(
  CONST(uint8, AUTOMATIC)  CycleId,
  CONST(uint8, AUTOMATIC)  CycleStatus
  );

/* ****************************************************************************
 * Dem_OperationCycle_SetState
 *****************************************************************************/
/*!
 * \brief         Queues the cycle state
 *
 * \details       Queues the cycle state
 *
 * \param[in]     CycleId
 *                Unique Id of the cycle
 *
 * \param[in]     CycleState
 *                DEM_CYCLE_STATE_START: Start a stopped cycle, or restart an
 *                                       active cycle.
 *                DEM_CYCLE_STATE_END:   Stop an active cycle.
 *
 * \return        E_OK
 *                Cycle state was queued successfully
 *
 * \return        E_NOT_OK
 *                Cycle state was not queued
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_OperationCycle_SetState(
  CONST(uint8, AUTOMATIC)  CycleId,
  CONST(Dem_OperationCycleStateType, AUTOMATIC)  CycleState
  );

/* ****************************************************************************
 * Dem_OperationCycle_SetStateNormalCycle
 *****************************************************************************/
/*!
 * \brief         Queues the cycle state
 *
 * \details       Queues the cycle state for a normal operation cycle (no
 *                OBD driving, WarmUp or HybridIgnition cycle)
 *
 * \param[in]     CycleId
 *                Unique Id of the cycle
 *
 * \param[in]     CycleState
 *                DEM_CYCLE_STATE_START: Start a stopped cycle, or restart an
 *                                       active cycle.
 *                DEM_CYCLE_STATE_END:   Stop an active cycle.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_SetStateNormalCycle(
CONST(uint8, AUTOMATIC)  CycleId,
CONST(Dem_OperationCycleStateType, AUTOMATIC)  CycleState
);

/* ****************************************************************************
 * Dem_OperationCycle_GetCycleState
 *****************************************************************************/
/*!
 * \brief         Get the current operation cycle state
 *
 * \details       Maps internal cycle state to the equivalent reported
 *                operation cycle state and return it.
 *
 * \param[in]     CycleId
 *                Unique identifier of the operation cycle
 *
 * \return        The current indicator status
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_OperationCycleStateType, DEM_CODE)
Dem_OperationCycle_GetCycleState(
  CONST(uint8, AUTOMATIC)  CycleId
  );

/* ****************************************************************************
 * Dem_OperationCycle_PreInit
 *****************************************************************************/
/*!
 * \brief         Pre-Initializes Dem queue states
 *
 * \details       This function initializes the operation cycle states.
 *
 * \pre           May be called only during pre-initialization
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_PreInit(
  void
  );

/* ****************************************************************************
 * Dem_OperationCycle_Init
 *****************************************************************************/
/*!
 * \brief         Initializes the Dem queue states
 *
 * \details       This function can be used to restore the operation cycle
 *                state stored in NV ram.
 *
 * \pre           May be called only during initialization
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_Init(
  void
  );

/* ****************************************************************************
 * Dem_OperationCycle_Shutdown
 *****************************************************************************/
/*!
 * \brief         Prepare operation cycle for shutdown
 *
 * \details       This function stops all running operation cycles and prepares
 *                the NV state for writeback
 *
 * \pre           May be called only during module shutdown
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_Shutdown(
  void
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_OPERATIONCYCLE_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_OperationCycle_Interface.h
 *********************************************************************************************************************/
