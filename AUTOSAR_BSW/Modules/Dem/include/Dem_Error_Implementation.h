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
/*! \addtogroup Dem_Error
 *  \{
 *  \file       Dem_Error_Implementation.h
 *  \brief      Implementation file for the MICROSAR Dem
 *  \details    Implementation of Error subcomponent
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_ERROR_IMPLEMENTATION_H)
#define DEM_ERROR_IMPLEMENTATION_H

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
 /* ------------------------------------------------------------------------- */
#if (DEM_DEV_ERROR_REPORT == STD_ON)
#include "Det.h"
#endif
                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_Error_Interface.h"

/* Includes to access public functions belonging to other (top level)/ (logical)/- units to be used by this Unit */
/* ------------------------------------------------------------------------- */
#include "Dem_InitState_Interface.h"

/* ********************************************************************************************************************
 *  FILE SPECIFIC MISRA VIOLATIONS
 *********************************************************************************************************************/
/* PRQA S 3406 DEM_ERROR_IMPL */ /* MD_DEM_8.6 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/
#define DEM_START_SEC_VAR_NOINIT_16BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Stores the code line where a run-time error has occurred */
VAR(uint16, DEM_VAR_NOINIT) Dem_LineOfRuntimeError;

#define DEM_STOP_SEC_VAR_NOINIT_16BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define DEM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Stores the filename where a run-time error has occurred */
P2CONST(Dem_CharacterType, DEM_VAR_NOINIT, DEM_CONST) Dem_FileOfRuntimeError;

#define DEM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DEFINITIONS
 *********************************************************************************************************************/
/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE PROPERTIES DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_DTC_PrivateProperties Private Properties
 * \{
 */
/* ****************************************************************************
 * Dem_Error_isDevErrorDetectEnabled
 *****************************************************************************/
/*!
 * \brief         Returns true if development error detection is enabled.
 * \details       -
 *
 * \return        TRUE
 *                Support for development error detection
 * \return        FALSE
 *                No support for development error detection
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Error_isDevErrorDetectEnabled(
  void
);

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE PROPERTIES DEFINITIONS
 *********************************************************************************************************************/

/* ****************************************************************************
 % Dem_Error_isDevErrorDetectEnabled()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Error_isDevErrorDetectEnabled(
  void
  )
{
  return (boolean)(DEM_DEV_ERROR_DETECT == STD_ON);
}
/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/* ********************************************************************************************************************
 *  SUBCOMPONENT PUBLIC PROPERTIES DEFINITIONS
 *********************************************************************************************************************/

#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \addtogroup Dem_Error_PublicProperties
 * \{
 */


/* ****************************************************************************
 % Dem_Error_isDevRunTimeChecksEnabled()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Error_isDevRunTimeChecksEnabled(void)
{
  return (boolean)(DEM_DEV_RUNTIME_CHECKS == STD_ON);
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* *********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DEFINITIONS
 **********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \addtogroup Dem_Error_Public
 * \{
 */

 /* ****************************************************************************
 % Dem_Error_InitErrorDetection
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Error_InitErrorDetection(
  void
)
{
  if (Dem_Error_isDevRunTimeChecksEnabled() == TRUE)
  {
    Dem_LineOfRuntimeError = 0u;
    Dem_FileOfRuntimeError = "";
  }
}

 /* ****************************************************************************
 % Dem_Error_DetectionHandler
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Error_DetectionHandler(
  boolean Verdict
  )
{
  return (boolean)((Dem_Error_isDevErrorDetectEnabled() == FALSE) || (Verdict));
}

/* ****************************************************************************
 % Dem_Error_ReportError
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Error_ReportError(
  CONST(uint8, AUTOMATIC) ApiId,
  CONST(uint8, AUTOMATIC) ErrorCode
  )
{
#if (DEM_DEV_ERROR_REPORT == STD_ON)
  (void)Det_ReportError(DEM_MODULE_ID, 0, ApiId, ErrorCode);
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(ApiId)                                                                                        /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(ErrorCode)                                                                                    /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
}

/* ****************************************************************************
 % Dem_Error_RunTimeCheckFailed
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Error_RunTimeCheckFailed(
  CONSTP2CONST(Dem_CharacterType, AUTOMATIC, DEM_CONST) FileName,
  CONST(uint16, AUTOMATIC) Line
  )
{
  Dem_FileOfRuntimeError = FileName;
  Dem_LineOfRuntimeError = Line;
# if (DEM_DEV_DISABLE_ON_RUNTIME_ERRORS == STD_ON)                                                                               /* COV_DEM_FAILED_RUNTIME_CHECKS TX */
  Dem_InitState_SetInitState(DEM_INITSTATE_HALTED_AFTER_ERROR);
# endif
  Dem_Error_ReportError(DEM_ERROR_INTERNAL_APIID, DEM_E_INCONSISTENT_STATE);
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ********************************************************************************************************************
 *  FILE SPECIFIC MISRA VIOLATIONS
 *********************************************************************************************************************/
/* PRQA L:DEM_ERROR_IMPL */

#endif /* DEM_ERROR_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Error_Implementation.h
 *********************************************************************************************************************/
