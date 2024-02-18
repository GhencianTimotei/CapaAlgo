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
/**        \file  Dcm_Debug.h
 *        \brief  Contains public inline function definitions of Debug unit.
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
#if !defined(DCM_DEBUG_H)
# define DCM_DEBUG_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Dcm_DebugInt.h"
# include "Dcm_UtilsInt.h"

# if (DCM_DEV_ERROR_REPORT == STD_ON)
#  include "Det.h"
# endif

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION DECLARATIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA DECLARATIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
# define DCM_START_SEC_CODE
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */
# if !defined(DCM_NOUNIT_SWITCHES)                                                                                                                   /* COV_DCM_NOUNIT TX */
/**********************************************************************************************************************
 *  Dcm_DebugIsDevErrorDetectEnabled()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(boolean, DCM_CODE) Dcm_DebugIsDevErrorDetectEnabled(                                                                          /* PRQA S 3219, 1527 */ /* MD_MSR_Unreachable, MD_MSR_Unreachable */
  void
  )
{
  return (DCM_DEV_ERROR_DETECT == STD_ON);                                                                                                           /* PRQA S 2995, 2996 */ /* MD_Dcm_ConstExpr */
}

/**********************************************************************************************************************
 *  Dcm_DebugIsDevRuntimeChecksEnabled()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(boolean, DCM_CODE) Dcm_DebugIsDevRuntimeChecksEnabled(                                                                        /* PRQA S 3219, 1527 */ /* MD_MSR_Unreachable */
  void
  )
{
  return (DCM_DEV_RUNTIME_CHECKS == STD_ON);                                                                                                         /* PRQA S 2995, 2996 */ /* MD_Dcm_ConstExpr */
}
# endif /* !defined(DCM_NOUNIT_SWITCHES) */

# if !defined(DCM_NOUNIT_DEBUG)                                                                                                                      /* COV_DCM_NOUNIT TX */
/**********************************************************************************************************************
 *  Dcm_DebugDetectError()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(boolean, DCM_CODE) Dcm_DebugDetectError(                                                                                      /* PRQA S 3219, 1527 */ /* MD_MSR_Unreachable */
  boolean condition
  )
{
  DCM_IGNORE_UNREF_PARAM(condition);                                                                                                                 /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
  return (Dcm_DebugIsDevErrorDetectEnabled() && condition);
}

/**********************************************************************************************************************
 *  Dcm_DebugDetectRuntimeError()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(boolean, DCM_CODE) Dcm_DebugDetectRuntimeError(                                                                               /* PRQA S 3219, 1527 */ /* MD_MSR_Unreachable */
  boolean condition
  )
{
  DCM_IGNORE_UNREF_PARAM(condition);                                                                                                                 /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
  return (Dcm_DebugIsDevRuntimeChecksEnabled() && condition);
}

/**********************************************************************************************************************
 *  Dcm_DebugReportError()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_DebugReportError(                                                                                         /* PRQA S 3219, 1527 */ /* MD_MSR_Unreachable */
  uint8 sid,
  uint8 errorId
  )
{
#  if (DCM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != DCM_E_NO_ERROR)
  {
    (void)Det_ReportError(DCM_MODULE_ID, 0u, sid, errorId);
  }
#  else
  DCM_IGNORE_UNREF_PARAM(sid);                                                                                                                       /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
  DCM_IGNORE_UNREF_PARAM(errorId);                                                                                                                   /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
#  endif
}

/**********************************************************************************************************************
 *  Dcm_DebugAssert()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_DebugAssert(                                                                                              /* PRQA S 3219, 1527 */ /* MD_MSR_Unreachable */
  boolean condition,
  uint8 sid,
  uint8 errorId
  )
{
  if(!condition)
  {
    Dcm_DebugReportError(sid, errorId);
  }
}
# endif /* !defined(DCM_NOUNIT_DEBUG) */
# define DCM_STOP_SEC_CODE
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* !defined(DCM_DEBUG_H) */

/**********************************************************************************************************************
 *  END OF FILE: Dcm_Debug.h
 *********************************************************************************************************************/
