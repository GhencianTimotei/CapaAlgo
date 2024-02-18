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
/*! \ingroup    Dem_Shared
 *  \defgroup   Dem_Error Assertion and Error handling
 *  \{
 *  \file       Dem_Error_Interface.h
 *  \brief      Implementation file for the MICROSAR Dem
 *  \details    Public interface of Error subcomponent
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_ERROR_INTERFACE_H)
#define DEM_ERROR_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
                                                        /* Dem module header */
#include "Dem_Error_Types.h"
/* ------------------------------------------------------------------------- */


/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/
#if !defined (__LINE__)                                                                                                          /* COV_DEM_PREPROCESSOR_DEFINE XF */
/*! substitute a number if the preprocessor does not support __LINE__ */
# define __LINE__                                0xffffu
#endif

/*! Filename declaration */
#define DEM_ERROR_INTERNAL_APIID                  (0xffU)              /*< Service ID: Internal Functions */

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

                                                               /* Assertions */
/* ------------------------------------------------------------------------- */

/*! Define local variable for DET error code */
# define Dem_Det_ErrorRegisterDefine()           uint8 lErrorId;
/*! Set error register with DET error code */
# define Dem_Det_ErrorRegisterSet(value)         lErrorId = (value);
/*! Get error register with DET error code */
# define Dem_Det_ErrorRegisterGet()              lErrorId

/* Internal Development Assertion Macros */
/*! Unconditional assertion, also calls DET if enabled */
#define Dem_Internal_AssertAlways(ErrorCode)
/*! Conditional assertion, also calls DET if enabled. Returns in case the assertion fails */
#define Dem_Internal_AssertReturnVoid(Condition, ErrorCode)
/*! Conditional assertion, also calls DET if enabled. Returns 'ReturnValue' in case the assertion fails */
#define Dem_Internal_AssertReturnValue(Condition, ErrorCode, ReturnValue)
/*! Conditional assertion, also calls DET if enabled. Continues with execution in case the assertion fails */
#define Dem_Internal_AssertContinue(Condition, ErrorCode)

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/
#define DEM_START_SEC_VAR_NOINIT_16BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
/*! Stores the code line where a run-time error has occurred */
extern VAR(uint16, DEM_VAR_NOINIT) Dem_LineOfRuntimeError;
#endif

#define DEM_STOP_SEC_VAR_NOINIT_16BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define DEM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
/*! Stores the filename where a run-time error has occurred */
extern P2CONST(Dem_CharacterType, DEM_VAR_NOINIT, DEM_CONST) Dem_FileOfRuntimeError;
#endif

#define DEM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_DTC_PublicProperties Public Properties
 * \{
 */

/* ****************************************************************************
 * Dem_Error_isDevRunTimeChecksEnabled
 *****************************************************************************/
/*!
 * \brief         Returns true if development runtime checks are enabled.
 * \details       -
 *
 * \return        TRUE
 *                Supported
 * \return        FALSE
 *                Not supported
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Error_isDevRunTimeChecksEnabled(
  void
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
 * \defgroup Dem_Error_Public Public Methods
 * \{
 */

 /* ****************************************************************************
 % Dem_Error_InitErrorDetection
 *****************************************************************************/
 /*!
 * \brief         Initiate global runtime error variables.
 *
 * \details       Initiate global runtime error variables,
 *                if development runtime checks are enabled.
 *
 *
 * \pre           -
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Error_InitErrorDetection(
  void
);

 /* ****************************************************************************
 % Dem_Error_DetectionHandler
 *****************************************************************************/
/*!
 * \brief         Decides if a passed verdict is processed.
 *
 * \details       Decides if a passed verdict is processed.
 *
 * \param[in]     Verdict
 *                The verdict of check.
 *
 * \return        TRUE
 *                Verdict not processed or verdict indicates 'no error'
 * \return        FALSE
 *                Verdict is processed and indicates 'error'
 *
 * \pre           -
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Error_DetectionHandler(
  boolean Verdict
  );

/* ****************************************************************************
 % Dem_Error_ReportError
 *****************************************************************************/
/*!
 * \brief         Call DET error report.
 *
 * \details       Calls DET error report with the module Id of the Dem.
 *
 * \param[in]     ApiId
 *                API Id of the function calling this function
 * \param[in]     ErrorCode
 *                Error Code describing the error
 *
 * \pre           -
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Error_ReportError(
  CONST(uint8, AUTOMATIC) ApiId,
  CONST(uint8, AUTOMATIC) ErrorCode
  );

/* ****************************************************************************
 * Dem_Error_RunTimeCheckFailed
 *****************************************************************************/
/*!
 * \brief         Call DET error report.
 *
 * \details       Calls DET error report with the module Id of the Dem.
 *
 * \param[in]     FileName
 *                FileName in which the runtime error has occurred
 * \param[in]     Line
 *                Line on which the runtime error has occurred
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Error_RunTimeCheckFailed(
  CONSTP2CONST(Dem_CharacterType, AUTOMATIC, DEM_CONST) FileName,
  CONST(uint16, AUTOMATIC) Line
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_ERROR_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Error_Interface.h
 *********************************************************************************************************************/
