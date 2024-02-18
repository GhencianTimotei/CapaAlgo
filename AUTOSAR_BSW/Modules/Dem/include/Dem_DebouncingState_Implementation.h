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
/*! \addtogroup Dem_DebouncingState
 *  \{
 *  \file       Dem_DebouncingState_Implementation.h
 *  \brief      Debouncing State
 *  \details    Encapsulation of AUTOSAR Debouncing State
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_DEBOUNCINGSTATE_IMPLEMENTATION_H)
#define DEM_DEBOUNCINGSTATE_IMPLEMENTATION_H

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
#include "Dem_DebouncingState_Interface.h"

/* Includes to access public functions belonging to other (top level)/ (logical)/- units to be used by this Unit */
/* ------------------------------------------------------------------------- */

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*! Filename declaration */
#define DEM_DEBOUNCINGSTATE_IMPLEMENTATION_FILENAME "Dem_DebouncingState_Implementation.h"
#define DEM_DEBOUNCINGSTATE_INITVALUE            0         /*!< The debouncing status initialization value */


/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DEFINITIONS
 *********************************************************************************************************************/
/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE PROPERTIES DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_DebouncingState_PrivateProperties Private Properties
 * \{
 */
/* ****************************************************************************
 * Dem_DebouncingState_TestTemporarilyDefective()
 *****************************************************************************/
/*!
 * \brief         Test the TemporarilyDefective flag of the given DebounceStatus
 *
 * \details       Get the TemporarilyDefective flag of the given DebounceStatus
 *
 * \param[in]     DebounceStatus
 *                The debounce status
 *
 * \return        TRUE
 *                The TemporarilyDefective flag is set
 * \return        FALSE
 *                The TemporarilyDefective flag is not set
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DebouncingState_TestTemporarilyDefective(
  CONST(Dem_DebouncingStateType, AUTOMATIC) DebounceStatus
  );


/* ****************************************************************************
 * Dem_DebouncingState_TestTemporarilyHealed()
 *****************************************************************************/
/*!
 * \brief         Test the TemporarilyHealed flag of the given DebounceStatus
 *
 * \details       Get the TemporarilyHealed flag of the given DebounceStatus
 *
 * \param[in]     DebounceStatus
 *                The debounce status
 *
 * \return        TRUE
 *                The TemporarilyHealed flag is set
 * \return        FALSE
 *                The TemporarilyHealed flag is not set
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DebouncingState_TestTemporarilyHealed(                                                                                       
  CONST(Dem_DebouncingStateType, AUTOMATIC) DebounceStatus
  );


/* ****************************************************************************
 * Dem_DebouncingState_TestTestComplete()
 *****************************************************************************/
/*!
 * \brief         Test the TestComplete flag of the given DebounceStatus
 *
 * \details       Get the TestComplete flag of the given DebounceStatus
 *
 * \param[in]     DebounceStatus
 *                The debounce status
 *
 * \return        TRUE
 *                The TestComplete flag is set
 * \return        FALSE
 *                The TestComplete flag is not set
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DebouncingState_TestTestComplete(
  CONST(Dem_DebouncingStateType, AUTOMATIC) DebounceStatus
  );


/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE PROPERTIES DEFINITIONS
 *********************************************************************************************************************/


/* ****************************************************************************
 % Dem_DebouncingState_TestTemporarilyDefective()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DebouncingState_TestTemporarilyDefective(                                                                                    /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_DebouncingStateType, AUTOMATIC) DebounceStatus
  )
{
  return (boolean)((DebounceStatus & DEM_TEMPORARILY_DEFECTIVE) != 0u);
}


/* ****************************************************************************
 % Dem_DebouncingState_TestTemporarilyHealed()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DebouncingState_TestTemporarilyHealed(                                                                                       /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_DebouncingStateType, AUTOMATIC) DebounceStatus
  )
{
  return (boolean)((DebounceStatus & DEM_TEMPORARILY_HEALED) != 0u);
}


/* ****************************************************************************
 % Dem_DebouncingState_TestTestComplete()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DebouncingState_TestTestComplete(                                                                                            /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_DebouncingStateType, AUTOMATIC) DebounceStatus
  )
{
  return (boolean)((DebounceStatus & DEM_TEST_COMPLETE) != 0u);
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
 * \addtogroup Dem_DebouncingState_PublicProperties
 * \{
 */


/* ****************************************************************************
 % Dem_DebouncingState_GetInitValue()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DebouncingStateType, DEM_CODE)
Dem_DebouncingState_GetInitValue(
  void
  )
{
  return DEM_DEBOUNCINGSTATE_INITVALUE;
}

/* ****************************************************************************
 % Dem_DebouncingState_SetTemporarilyDefective()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DebouncingStateType, DEM_CODE)
Dem_DebouncingState_SetTemporarilyDefective(
  CONST(Dem_DebouncingStateType, AUTOMATIC) DebounceStatus
  )
{
  return (Dem_DebouncingStateType)(DebounceStatus | DEM_TEMPORARILY_DEFECTIVE);
}

/* ****************************************************************************
 % Dem_DebouncingState_TestFinallyDefective()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DebouncingState_TestFinallyDefective(                                                                                        /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_DebouncingStateType, AUTOMATIC) DebounceStatus
  )
{
  return (boolean)((DebounceStatus & DEM_FINALLY_DEFECTIVE) != 0u);
}

/* ****************************************************************************
 % Dem_DebouncingState_SetFinallyDefective()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DebouncingStateType, DEM_CODE)
Dem_DebouncingState_SetFinallyDefective(
  CONST(Dem_DebouncingStateType, AUTOMATIC) DebounceStatus
  )
{
  return (Dem_DebouncingStateType)(DebounceStatus | DEM_FINALLY_DEFECTIVE);
}

/* ****************************************************************************
 % Dem_DebouncingState_SetTemporarilyHealed()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DebouncingStateType, DEM_CODE)
Dem_DebouncingState_SetTemporarilyHealed(
  CONST(Dem_DebouncingStateType, AUTOMATIC) DebounceStatus
  )
{
  return (Dem_DebouncingStateType)(DebounceStatus | DEM_TEMPORARILY_HEALED);
}

/* ****************************************************************************
 % Dem_DebouncingState_SetTestComplete()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DebouncingStateType, DEM_CODE)
Dem_DebouncingState_SetTestComplete(
  CONST(Dem_DebouncingStateType, AUTOMATIC) DebounceStatus
  )
{
  return (Dem_DebouncingStateType)(DebounceStatus | DEM_TEST_COMPLETE);
}

/* ****************************************************************************
 % Dem_DebouncingState_TestDtrUpdate()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DebouncingState_TestDtrUpdate(                                                                                             /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_DebouncingStateType, AUTOMATIC) DebounceStatus
  )
{
  return (boolean)((DebounceStatus & DEM_DTR_UPDATE) != 0u);
}

/* ****************************************************************************
 % Dem_DebouncingState_SetDtrUpdate()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DebouncingStateType, DEM_CODE)
Dem_DebouncingState_SetDtrUpdate(
  CONST(Dem_DebouncingStateType, AUTOMATIC) DebounceStatus
  )
{
  return (Dem_DebouncingStateType)(DebounceStatus | DEM_DTR_UPDATE);
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_DEBOUNCINGSTATE_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_DebouncingState_Implementation.h
 *********************************************************************************************************************/
