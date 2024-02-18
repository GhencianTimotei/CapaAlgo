/**********************************************************************************************************************
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
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Dcm_DebugInt.h
 *        \brief  Contains public function declarations and complex type definitions of Debug unit.
 *
 *      \details  MICROSAR DCM based on AR 4.0.3
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/
#if !defined(DCM_DEBUGINT_H)
# define DCM_DEBUGINT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Dcm_DebugTypes.h"

# include "Dcm.h"

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/*! Debug sub-component initialization states */
# define DCM_UNINIT                                                  (0x00u) /*!< DCM is not or partially initialized. In this state DCM is completely isolated from the other BSWs/SW-C in the ECU */
# define DCM_INIT                                                    (0x01u) /*!< DCM is initialized. In this state DCM is fully operable */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
/*! Puts DCM into uninitialized state (isolate from the rest of the world) */
# define Dcm_DebugDeInit()                                           (Dcm_DebugInitState = DCM_UNINIT)                                               /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Puts DCM into initialized state */
# define Dcm_DebugInit()                                             (Dcm_DebugInitState = DCM_INIT)                                                 /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Checks whether DCM is initialized */
# define Dcm_DebugIsModuleInitialized()                              (Dcm_DebugInitState == DCM_INIT)                                                /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION DECLARATIONS
 *********************************************************************************************************************/
# define DCM_START_SEC_CODE
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */
/**********************************************************************************************************************
 *  Dcm_DebugIsDevErrorDetectEnabled()
 *********************************************************************************************************************/
/*! \brief          Returns DCM_DEV_ERROR_DETECT as boolean.
 *  \details        -
 *  \return         TRUE         DCM_DEV_ERROR_DETECT is STD_ON
 *  \return         FALSE        DCM_DEV_ERROR_DETECT is STD_OFF
 *  \context        ISR1|ISR2|TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(boolean, DCM_CODE) Dcm_DebugIsDevErrorDetectEnabled(
  void
  );

/**********************************************************************************************************************
 *  Dcm_DebugIsDevRuntimeChecksEnabled()
 *********************************************************************************************************************/
/*! \brief          Returns DCM_DEV_RUNTIME_CHECKS as boolean.
 *  \details        -
 *  \return         TRUE         DCM_DEV_RUNTIME_CHECKS is STD_ON
 *  \return         FALSE        DCM_DEV_RUNTIME_CHECKS is STD_OFF
 *  \context        ISR1|ISR2|TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(boolean, DCM_CODE) Dcm_DebugIsDevRuntimeChecksEnabled(
  void
  );

/**********************************************************************************************************************
 *  Dcm_DebugDetectError()
 *********************************************************************************************************************/
/*! \brief          Checks for Development Error Detection.
 *  \details        -
 *  \param[in]      condition    Condition to evaluate
 *  \return         TRUE         Condition is true and Error Detection is active
 *  \return         FALSE        Condition is false and/or Error Detection is disabled
 *  \context        ISR1|ISR2|TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(boolean, DCM_CODE) Dcm_DebugDetectError(
  boolean condition
  );

/**********************************************************************************************************************
 *  Dcm_DebugDetectRuntimeError()
 *********************************************************************************************************************/
/*! \brief          Checks for Runtime Error Detection.
 *  \details        -
 *  \param[in]      condition    Condition to evaluate
 *  \return         TRUE         Condition is true and Runtime Error Detection is active
 *  \return         FALSE        Condition is false and/or Runtime Error Detection is disabled
 *  \context        ISR1|ISR2|TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(boolean, DCM_CODE) Dcm_DebugDetectRuntimeError(
  boolean condition
  );

/**********************************************************************************************************************
 *  Dcm_DebugReportError()
 *********************************************************************************************************************/
/*! \brief          Checks for Development Error Report.
 *  \details        -
 *  \param[in]      sid          API Service ID
 *  \param[in]      errorId      Error ID
 *  \context        ISR1|ISR2|TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_DebugReportError(
  uint8 sid,
  uint8 errorId
  );

/**********************************************************************************************************************
 *  Dcm_DebugAssert()
 *********************************************************************************************************************/
/*! \brief          Supports DCM internal debugging for additional, deeper analysis
 *  \details        -
 *  \param[in]      sid          API Service ID
 *  \param[in]      errorId      Error ID
 *  \context        ISR1|ISR2|TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_DebugAssert(
  boolean condition,
  uint8 sid,
  uint8 errorId
  );
# define DCM_STOP_SEC_CODE
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL DATA DECLARATIONS
 *********************************************************************************************************************/
# define DCM_START_SEC_VAR_INIT_8
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*! Dedicated RAM allocation for modules initialization state */
extern VAR(uint8, DCM_VAR_INIT) Dcm_DebugInitState;
# define DCM_STOP_SEC_VAR_INIT_8
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

#endif /* !defined(DCM_DEBUGINT_H) */

/**********************************************************************************************************************
 *  END OF FILE: Dcm_DebugInt.h
 *********************************************************************************************************************/
