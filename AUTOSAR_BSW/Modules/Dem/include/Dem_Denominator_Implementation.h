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
/*! \addtogroup Dem_Denominator
 *  \{
 *  \file       Dem_Denominator_Implementation.h
 *  \brief      IUMPR Ratio Denominator subcomponent.
 *  \details    Provides functionality to manipulate IUMPR ratio denominators, and react to denominator condition changes.
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_DENOMINATOR_IMPLEMENTATION_H)
#define DEM_DENOMINATOR_IMPLEMENTATION_H

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
#include "Dem_Denominator_Interface.h"

/* Includes to access public functions belonging to other (top level)/ (logical)/- units to be used by this Unit */
/* ------------------------------------------------------------------------- */
#include "Dem_Infrastructure_Interface.h"
#include "Dem_RatioIF_Interface.h"
#include "Dem_IumprIF_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

  /*! Filename declaration */
#define DEM_DENOMINATOR_IMPLEMENTATION_FILENAME "Dem_Denominator_Implementation.h"

 /* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DEFINITIONS
 *********************************************************************************************************************/
/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE PROPERTIES DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_Iumpr_Ratio_Denominator_PrivateProperties Private Properties
 * \{
 */

/* ****************************************************************************
 * Dem_Iumpr_Ratio_Denominator_GetCount
 *****************************************************************************/
/*!
 * \brief         Get the number of configured ratios
 *
 * \details       Get the number of configured ratios
 *
 * \return        The number of configured ratios
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Iumpr_Ratio_Denominator_GetCount(
  void
  );


/* ****************************************************************************
 * Dem_Iumpr_Ratio_Denominator_IncrementValue
 *****************************************************************************/
/*!
 * \brief         Increment denominator value of a ratio
 *
 * \details       Increment denominator value of a ratio
 *
 * \param[in]     -
 *
 * \return        E_OK
 *                Condition
 * \return        E_NOT_OK
 *                Condition
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different RatioIdx
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_Denominator_IncrementValue(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  );

/* ****************************************************************************
 * Dem_Iumpr_Ratio_Denominator_SetIncremented
 *****************************************************************************/
/*!
 * \brief         Set denominator incremented state of the ratio
 *
 * \details       Set denominator incremented state of the ratio
 *
 * \param[in]     RatioIndex
 *                Unique handle of the Ratio
 *
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_Denominator_SetIncremented(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  );

/* ****************************************************************************
 * Dem_Iumpr_Ratio_Denominator_ResetIncremented
 *****************************************************************************/
/*!
 * \brief         Reset denominator incremented state of the ratio
 *
 * \details       Reset denominator incremented state of the ratio
 *
 * \param[in]     RatioIndex
 *                Unique handle of the Ratio
 *
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_Denominator_ResetIncremented(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  );


/* ****************************************************************************
 * Dem_Iumpr_Ratio_Denominator_TestLocked
 *****************************************************************************/
/*!
 * \brief         Test denominator locked state of the ratio
 *
 * \details       Test denominator locked state of the ratio
 *
 * \param[in]     RatioIndex
 *                Unique handle of the Ratio
 *
 * \return        TRUE
 *                Denominator was incremented in the current operation cycle
 * \return        FALSE
 *                Denominator was not incremented in the current operation cycle
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_Ratio_Denominator_TestLocked(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  );

/* ****************************************************************************
 * Dem_Iumpr_Ratio_Denominator_TestConditionsReached
 *****************************************************************************/
/*!
 * \brief         Test denominator conditions reached state of the ratio
 *
 * \details       Test denominator conditions reached state of the ratio
 *
 * \param[in]     RatioIndex
 *                Unique handle of the Ratio
 *
 * \return        TRUE
 *                Denominator was reported reached
 * \return        FALSE
 *                Denominator was not reported reached
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_Ratio_Denominator_TestConditionsReached(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  );


/* ****************************************************************************
 * Dem_Iumpr_Ratio_Denominator_SetConditionsReached
 *****************************************************************************/
/*!
 * \brief         Set denominator conditions reached state of the ratio
 *
 * \details       Set denominator conditions reached state of the ratio
 *
 * \param[in]     Param
 *                Desc
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_Denominator_SetConditionsReached(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  );

/* ****************************************************************************
 * Dem_Iumpr_Ratio_Denominator_ResetConditionsReached
 *****************************************************************************/
/*!
 * \brief         Reset denominator conditions reached state of the ratio
 *
 * \details       Reset denominator conditions reached state of the ratio
 *
 * \param[in]     RatioIndex
 *                Unique handle of the Ratio
 *
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_Denominator_ResetConditionsReached(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  );


/* ****************************************************************************
 * Dem_Iumpr_Ratio_Denominator_TestGeneralIndividualConditionReached
 *****************************************************************************/
/*!
 * \brief         Test general denominator conditions fulfilled
 *
 * \details       Test general denominator conditions fulfilled
 *
 * \param[in]     RatioIndex
 *                Unique handle of the Ratio
 *
 * \return        TRUE
 *                General Individual Denominator condition was reported reached
 * \return        FALSE
 *                General Individual Denominator condition was not reported reached
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_Ratio_Denominator_TestGeneralIndividualConditionReached(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  );

/* ****************************************************************************
 * Dem_Iumpr_Ratio_Denominator_SetGeneralIndividualConditionReached
 *****************************************************************************/
/*!
 * \brief         Set general denominator conditions fulfilled
 *
 * \details       Set general denominator conditions fulfilled
 *
 * \param[in]     RatioIndex
 *                Unique handle of the Ratio
 *
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_Denominator_SetGeneralIndividualConditionReached(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  );

/* ****************************************************************************
 * Dem_Iumpr_Ratio_Denominator_ResetGeneralIndividualConditionReached
 *****************************************************************************/
/*!
 * \brief         Reset general denominator conditions fulfilled
 *
 * \details       Reset general denominator conditions fulfilled
 *
 * \param[in]     RatioIndex
 *                Unique handle of the Ratio
 *
 * \return        E_OK
 *                Condition
 * \return        E_NOT_OK
 *                Condition
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_Denominator_ResetGeneralIndividualConditionReached(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  );

/* ****************************************************************************
 * Dem_Iumpr_Ratio_Denominator_SetValue
 *****************************************************************************/
/*!
 * \brief         Set denominator value
 *
 * \details       Test denominator incremented state of the ratio
 *
 * \param[in]     RatioIndex
 *                Unique handle of the Ratio
 *
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_Denominator_SetValue(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex,
  CONST(uint16, AUTOMATIC) Value
  );

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE PROPERTIES DEFINITIONS
 *********************************************************************************************************************/

/* ****************************************************************************
 % Dem_Iumpr_Ratio_Denominator_GetCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Iumpr_Ratio_Denominator_GetCount(
void
)
{
  return DEM_G_NUMBER_OF_RATIO_IDS;
}


/* ****************************************************************************
 % Dem_Iumpr_Ratio_Denominator_IncrementValue
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_Denominator_IncrementValue(CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex)
{

  Dem_Iumpr_Ratio_Denominator_SetValue(RatioIndex, Dem_Iumpr_Ratio_Denominator_GetValue(RatioIndex) + 1u);
  Dem_Iumpr_Ratio_Denominator_SetIncremented(RatioIndex);

}

/* ****************************************************************************
 % Dem_Iumpr_Ratio_Denominator_SetIncremented
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_Denominator_SetIncremented(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  )
{
  Dem_Iumpr_Ratio_SetRatioStatusUtil(RatioIndex, (Dem_Iumpr_Ratio_GetRatioStatusUtil(RatioIndex) | DEM_DENOMINATOR_INCREMENTED));
}

/* ****************************************************************************
 % Dem_Iumpr_Ratio_Denominator_ResetIncremented
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_Denominator_ResetIncremented(                                                                                                /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  )
{
  Dem_Iumpr_Ratio_SetRatioStatusUtil(RatioIndex, (Dem_Iumpr_Ratio_GetRatioStatusUtil(RatioIndex) & DEM_DENOMINATOR_INCREMENTED_MASK));
}

/* ****************************************************************************
 % Dem_Iumpr_Ratio_Denominator_TestLocked
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_Ratio_Denominator_TestLocked(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  )
{
  return (((Dem_Iumpr_Ratio_GetRatioStatusUtil(RatioIndex))& DEM_DENOMINATOR_LOCKED) != 0u);
}

/* ****************************************************************************
 % Dem_Iumpr_Ratio_Denominator_TestConditionsReached
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_Ratio_Denominator_TestConditionsReached(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  )
{
  return (((Dem_Iumpr_Ratio_GetRatioStatusUtil(RatioIndex))& DEM_DENOMINATOR_CONDITIONS_REACHED) != 0u);
}

/* ****************************************************************************
 % Dem_Iumpr_Ratio_Denominator_SetConditionsReached
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_Denominator_SetConditionsReached(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  )
{
  Dem_Iumpr_Ratio_SetRatioStatusUtil(RatioIndex, (Dem_Iumpr_Ratio_GetRatioStatusUtil(RatioIndex) | DEM_DENOMINATOR_CONDITIONS_REACHED));
}

/* ****************************************************************************
 % Dem_Iumpr_Ratio_Denominator_ResetConditionsReached
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_Denominator_ResetConditionsReached(                                                                              /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  )
{
  Dem_Iumpr_Ratio_SetRatioStatusUtil(RatioIndex, (Dem_Iumpr_Ratio_GetRatioStatusUtil(RatioIndex) & DEM_DENOMINATOR_CONDITIONS_REACHED_MASK));
}

/* ****************************************************************************
 % Dem_Iumpr_Ratio_Denominator_TestGeneralIndividualConditionReached
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_Ratio_Denominator_TestGeneralIndividualConditionReached(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  )
{
  return ((Dem_Iumpr_Ratio_GetRatioStatusUtil(RatioIndex) & DEM_DENOMINATOR_INDIGENDEN_CONDITIONS_REACHED) != 0u);
}

/* ****************************************************************************
 % Dem_Iumpr_Ratio_Denominator_SetGeneralIndividualConditionReached
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_Denominator_SetGeneralIndividualConditionReached(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  )
{
  Dem_Iumpr_Ratio_SetRatioStatusUtil(RatioIndex, (Dem_Iumpr_Ratio_GetRatioStatusUtil(RatioIndex) | DEM_DENOMINATOR_INDIGENDEN_CONDITIONS_REACHED));
}


/* ****************************************************************************
 % Dem_Iumpr_Ratio_Denominator_ResetGeneralIndividualConditionReached
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_Denominator_ResetGeneralIndividualConditionReached(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  )
{
  Dem_Iumpr_Ratio_SetRatioStatusUtil(RatioIndex, (Dem_Iumpr_Ratio_GetRatioStatusUtil(RatioIndex) & DEM_DENOMINATOR_INDIGENDEN_CONDITIONS_REACHED_MASK));
}


/* ****************************************************************************
 % Dem_Iumpr_Ratio_Denominator_SetValue
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_Denominator_SetValue(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex, CONST(uint16, AUTOMATIC) Value
  )
{
  if ((Dem_Error_isDevRunTimeChecksEnabled() == TRUE)
    && (RatioIndex >= Dem_Iumpr_Ratio_Denominator_GetCount()))                                                                               
  {
    Dem_Error_RunTimeCheckFailed(DEM_DENOMINATOR_IMPLEMENTATION_FILENAME, __LINE__);                                             /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
  {
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
    Dem_Cfg_ObdIumprData.Denominator[RatioIndex] = Value;                                                                        /* SBSW_DEM_ARRAY_WRITE_OBDIUMPRDATA_DENOMINATOR */
#else 
    DEM_IGNORE_UNUSED_CONST_ARGUMENT(Value)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
  }
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
 * \addtogroup Dem_Iumpr_Ratio_Denominator_PublicProperties
 * \{
 */

/* ****************************************************************************
 % Dem_Iumpr_Ratio_Denominator_GetValue
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Iumpr_Ratio_Denominator_GetValue(CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex)
{
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
  return (uint16)(Dem_Cfg_ObdIumprData.Denominator[RatioIndex]);
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(RatioIndex)                                                                                   /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return (uint16)0;
#endif
}

/* ****************************************************************************
 % Dem_Iumpr_Ratio_Denominator_TestIncremented
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_Ratio_Denominator_TestIncremented(CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex)
{
  return (((Dem_Iumpr_Ratio_GetRatioStatusUtil(RatioIndex))& DEM_DENOMINATOR_INCREMENTED) != 0u);
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */


/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \addtogroup Dem_Iumpr_Ratio_Denominator_Private
 * \{
 */

 /* ****************************************************************************
 * Dem_Iumpr_Ratio_DenNoneIncrement
 *****************************************************************************/
 /*!
 * \brief         Increment ratio
 *
 * \details       Increment ratio, if all conditions for denominator group None
 *                are fulfilled.
 *
 * \param[in]     RatioIndex
 *                Ratio identifier
 *
 * \return        TRUE
 *                Ratio has changed
 * \return        FALSE
 *                Ratio hasn't changed
 *
 * \pre           Should only be called, for denominator's of type none or PhysAPI
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_Ratio_DenNone_Increment(CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex);

/* ****************************************************************************
 * Dem_Iumpr_Ratio_ColdStart_Increment
 *****************************************************************************/
/*!
 * \brief         Increment ratio
 *
 * \details       Increment ratio, if all conditions for denominator group ColdStart
 *                are fulfilled.
 *
 * \param[in]     RatioIndex
 *                Ratio identifier
 *
 * \return        TRUE
 *                Ratio has changed
 * \return        FALSE
 *                Ratio hasn't changed
 *
 * \pre           Should only be called, for denominator's of type cold start
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different RatioIdx
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_Ratio_ColdStart_Increment(CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex);

/* ****************************************************************************
 * Dem_Iumpr_Ratio_PhysAPI_Increment
 *****************************************************************************/
/*!
 * \brief         Increment ratio
 *
 * \details       Increment ratio, if all conditions for denominator group
 *                PhysAPI are fulfilled.
 *
 * \param[in]     RatioIndex
 *                Ratio identifier
 *
 * \return        TRUE
 *                Ratio has changed
 * \return        FALSE
 *                Ratio hasn't changed
 *
 * \pre           Should only be called, for denominator's of type none or PhysAPI
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_Ratio_PhysAPI_Increment(CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex);


/* ****************************************************************************
 * Dem_Iumpr_Ratio_Independent_Increment
 *****************************************************************************/
 /*!
  * \brief         Increment ratio
  *
  * \details       Increment ratio, if all conditions for denominator group
  *                Independent are fulfilled.
  *
  * \param[in]     RatioIndex
  *                Ratio identifier
  *
  * \return        TRUE
  *                Ratio has changed
  * \return        FALSE
  *                Ratio hasn't changed
  *
  * \pre           Should only be called, for denominator's of type Independent
  *
  * \context       TASK|ISR2
  * \synchronous   TRUE
  * \reentrant     TRUE for different RatioIdx
  *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_Ratio_Independent_Increment(CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex);


/* ****************************************************************************
 * Dem_Iumpr_Ratio_Evap_Increment
 *****************************************************************************/
/*!
 * \brief         Increment ratio
 *
 * \details       Increment ratio, if all conditions for denominator group Evap
 *                are fulfilled.
 *
 * \param[in]     RatioIndex
 *                Ratio identifier
 *
 * \return        TRUE
 *                Ratio has changed
 * \return        FALSE
 *                Ratio hasn't changed
 *
 * \pre           Should only be called, for denominator's of type evap
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different RatioIdx
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_Ratio_Evap_Increment(CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex);

/* ****************************************************************************
 * Dem_Iumpr_Ratio_500Mi_Increment
 *****************************************************************************/
/*!
 * \brief         Increment ratio
 *
 * \details       Increment ratio, if all conditions for denominator group 500mi
 *                are fulfilled.
 *
 * \param[in]     RatioIndex
 *                Ratio identifier
 *
 * \return        TRUE
 *                Ratio has changed
 * \return        FALSE
 *                Ratio hasn't changed
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_Ratio_500Mi_Increment(CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex);

/* ****************************************************************************
 * Dem_Iumpr_Ratio_Denominator_SetSpecialConditionReached
 *****************************************************************************/
/*!
 * \brief         Set special denominator condition reached
 *
 * \details       Set special denominator condition reached for a specific ratio
 *
 * \param[in]     RatioIndex
 *                Unique handle of the Ratio
 *
 * \return        TRUE
 *                Ratio status has changed
 * \return        FALSE
 *                Ratio status hasn't changed
 *
 * \pre           Should only be called, for denominator's of type cold start
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_Ratio_Denominator_SetSpecialConditionReached(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex,
  CONST(Dem_IumprDenomCondIdType, AUTOMATIC) ConditionId
);

/* ****************************************************************************
 * Dem_Iumpr_Ratio_500Mi_OpCycleStart
 *****************************************************************************/
/*!
 * \brief         Reset status bits of 500mi denominator on OBD DCY restart
 *
 * \details       -
 *
 * \param[in]     RatioIndex
 *                Unique handle of the Ratio
 *
 * \pre           Should only be called, for denominator's of type 500mi
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_500Mi_OpCycleStart(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
);

/* ****************************************************************************
 * Dem_Iumpr_Ratio_Denominator_Reach
 *****************************************************************************/
/*!
 * \brief         Mark a condition as reached
 *
 * \details       Mark a condition as reached for a specific ratio
 *
 * \param[in]     RatioIndex
 *                Unique handle of the Ratio
 * \param[in]     ConditionId
 *                The denominator group which reached state shall be set.
 *
 * \return        TRUE
 *                Ratio status has changed
 * \return        FALSE
 *                Ratio status hasn't changed
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_Ratio_Denominator_Reach(CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex, CONST(Dem_IumprDenomCondIdType, AUTOMATIC) ConditionId);

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/

/* ****************************************************************************
 % Dem_Iumpr_Ratio_DenNone_Increment
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_Ratio_DenNone_Increment(CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex)
{
  boolean lUpdateRatio;
  lUpdateRatio = FALSE;
  if ((Dem_Iumpr_Ratio_Denominator_TestIncremented(RatioIndex) == FALSE)
    && (Dem_Iumpr_ConditionStatus_TestReached(DEM_IUMPR_GENERAL_INDIVIDUAL_DENOMINATOR) == TRUE))                                  
  {
    Dem_Iumpr_Ratio_Denominator_IncrementValue(RatioIndex);
    lUpdateRatio = TRUE;
  }
  return lUpdateRatio;
}

/* ****************************************************************************
 % Dem_Iumpr_Ratio_PhysAPI_Increment
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_Ratio_PhysAPI_Increment(CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex)
{
  boolean lUpdateRatio;
  lUpdateRatio = FALSE;
  if ( (Dem_Iumpr_Ratio_Denominator_TestIncremented(RatioIndex) == FALSE)
    && (Dem_Iumpr_Ratio_Denominator_TestLocked(RatioIndex) == FALSE)                                                             /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
    && (Dem_Iumpr_ConditionStatus_TestReached(DEM_IUMPR_GENERAL_INDIVIDUAL_DENOMINATOR) == TRUE) )                                  
  {
    Dem_Iumpr_Ratio_Denominator_IncrementValue(RatioIndex);
    lUpdateRatio = TRUE;
  }
  return lUpdateRatio;
}

/* ****************************************************************************
 % Dem_Iumpr_Ratio_Independent_Increment
 *****************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 *
 *
 *
  */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_Ratio_Independent_Increment(CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex)
{
  boolean lUpdateRatio;
  lUpdateRatio = FALSE;
  if ( (Dem_Iumpr_Ratio_Denominator_TestIncremented(RatioIndex) == FALSE)
    && (Dem_Iumpr_Ratio_Denominator_TestLocked(RatioIndex) == FALSE)                                                             /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
    && (Dem_Iumpr_ConditionStatus_TestReached(DEM_IUMPR_DEN_COND_INDEPENDENT) == TRUE) )                                                  
  {
    Dem_Iumpr_Ratio_Denominator_IncrementValue(RatioIndex);
    lUpdateRatio = TRUE;
  }
  return lUpdateRatio;
}


/* ****************************************************************************
 % Dem_Iumpr_Ratio_ColdStart_Increment
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_Ratio_ColdStart_Increment(CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex)
{
  boolean lUpdateRatio;
  lUpdateRatio = FALSE;

  if ((Dem_Iumpr_Ratio_Denominator_TestIncremented(RatioIndex) == FALSE)
    && (Dem_Iumpr_ConditionStatus_TestReached(DEM_IUMPR_GENERAL_INDIVIDUAL_DENOMINATOR) == TRUE)
    && (Dem_Iumpr_ConditionStatus_TestReached(DEM_IUMPR_DEN_COND_COLDSTART) == TRUE) )                                                             
  {
    Dem_Iumpr_Ratio_Denominator_IncrementValue(RatioIndex);
    lUpdateRatio = TRUE;
  }
  return lUpdateRatio;
}

/* ****************************************************************************
 % Dem_Iumpr_Ratio_Evap_Increment
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_Ratio_Evap_Increment(CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex)
{
  boolean lUpdateRatio;
  lUpdateRatio = FALSE;

  if ((Dem_Iumpr_Ratio_Denominator_TestIncremented(RatioIndex) == FALSE)
    && (Dem_Iumpr_ConditionStatus_TestReached(DEM_IUMPR_GENERAL_INDIVIDUAL_DENOMINATOR) == TRUE)
    && (Dem_Iumpr_ConditionStatus_TestReached(DEM_IUMPR_DEN_COND_EVAP)== TRUE))
  {
    Dem_Iumpr_Ratio_Denominator_IncrementValue(RatioIndex);
    lUpdateRatio = TRUE;
  }
  return lUpdateRatio;
}

/* ****************************************************************************
 % Dem_Iumpr_Ratio_500Mi_Increment
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
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_Ratio_500Mi_Increment(CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex)
{
  boolean lUpdateRatio;
  lUpdateRatio = FALSE;

  if ( (Dem_Iumpr_Ratio_Denominator_TestIncremented(RatioIndex) == FALSE)
    && (Dem_Iumpr_Ratio_Denominator_TestGeneralIndividualConditionReached(RatioIndex) == TRUE)                                   /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
    && (Dem_Iumpr_Ratio_Denominator_TestConditionsReached(RatioIndex) == TRUE) )                                                 /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
  {
    Dem_Iumpr_Ratio_Denominator_IncrementValue(RatioIndex);
    Dem_Iumpr_Ratio_Denominator_ResetGeneralIndividualConditionReached(RatioIndex);
    Dem_Iumpr_Ratio_Denominator_ResetConditionsReached(RatioIndex);
    lUpdateRatio = TRUE;
  }
  return lUpdateRatio;
}

/* ****************************************************************************
 % Dem_Iumpr_Ratio_Denominator_SetSpecialConditionReached 
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_Ratio_Denominator_SetSpecialConditionReached(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex,
  CONST(Dem_IumprDenomCondIdType, AUTOMATIC) ConditionId
  )
{
  boolean lUpdateRatio;
  lUpdateRatio = FALSE;

  /* Set additional conditions reached */
  if (Dem_Iumpr_Ratio_Denominator_GetDenominatorGroup(RatioIndex) == ConditionId)
  {
    Dem_Iumpr_Ratio_Denominator_SetConditionsReached(RatioIndex);
    lUpdateRatio = TRUE;
  }
  return lUpdateRatio;
}

/* ****************************************************************************
 % Dem_Iumpr_Ratio_Denominator_Reach
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_Ratio_Denominator_Reach(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex, 
  CONST(Dem_IumprDenomCondIdType, AUTOMATIC) ConditionId
)
{
  boolean lUpdateRatio;
  lUpdateRatio = FALSE;

  if (Dem_Iumpr_Ratio_Denominator_TestIncremented(RatioIndex) == FALSE)
  {
    /* Calls to child sub-components */
    switch (ConditionId)
    {
    case DEM_IUMPR_GENERAL_INDIVIDUAL_DENOMINATOR:
      if (Dem_Iumpr_Ratio_Denominator_TestGeneralIndividualConditionReached(RatioIndex) == FALSE)
      {
        Dem_Iumpr_Ratio_Denominator_SetGeneralIndividualConditionReached(RatioIndex);
        lUpdateRatio = TRUE;
      }
      break;

    case DEM_IUMPR_DEN_500MI:
      lUpdateRatio = Dem_Iumpr_Ratio_Denominator_SetSpecialConditionReached(RatioIndex, ConditionId);
      break;

    default:
      /* Calls to DenNone and PhysApi are unnecessary, since they depend only on general individual conditions */
      /* Calls to Independent, ColdStart and Evap are unnecessary, since their reached condition state is global*/
      break;
    }
  }
  return lUpdateRatio;
}

/* ****************************************************************************
 % Dem_Iumpr_Ratio_500Mi_OpCycleStart
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
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_500Mi_OpCycleStart(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
)
{
  Dem_Iumpr_Ratio_Denominator_ResetIncremented(RatioIndex);
  (void)Dem_Iumpr_Ratio_Denominator_Release(RatioIndex);
}

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
 * \addtogroup Dem_Iumpr_Ratio_Denominator_Public
 * \{
 */



/* ****************************************************************************
 % Dem_Iumpr_Ratio_Denominator_Increment
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_Ratio_Denominator_Increment(CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex)
{
  boolean lUpdateRatio;
  lUpdateRatio = FALSE;

  /* Calls to specialized denominator implementation */
  switch (Dem_Iumpr_Ratio_Denominator_GetDenominatorGroup(RatioIndex))
  {
  case DEM_IUMPR_DEN_NONE:
    lUpdateRatio = Dem_Iumpr_Ratio_DenNone_Increment(RatioIndex);
    break;
  case DEM_IUMPR_DEN_PHYS_API:
    lUpdateRatio = Dem_Iumpr_Ratio_PhysAPI_Increment(RatioIndex);
    break;
  case DEM_IUMPR_DEN_COLDSTART:
    lUpdateRatio = Dem_Iumpr_Ratio_ColdStart_Increment(RatioIndex);
    break;
  case DEM_IUMPR_DEN_EVAP:
    lUpdateRatio = Dem_Iumpr_Ratio_Evap_Increment(RatioIndex);
    break;
  case DEM_IUMPR_DEN_500MI:
    lUpdateRatio = Dem_Iumpr_Ratio_500Mi_Increment(RatioIndex);
    break;
  case DEM_IUMPR_DEN_INDEPENDENT:
    lUpdateRatio = Dem_Iumpr_Ratio_Independent_Increment(RatioIndex);
    break;
  default:                                                                                                                     /* PRQA S 2016 */ /* MD_MSR_EmptyClause */
    /* Do nothing */
    break;
  }

  return lUpdateRatio;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_Iumpr_Ratio_Denominator_HandleOverflow
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_Denominator_HandleOverflow(CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex)
{
  /* divide by two if max value has been reached   [CCR1968.2 (g)(5.2.1)(C)] */
  Dem_Iumpr_Ratio_Denominator_SetValue(RatioIndex, (Dem_Iumpr_Ratio_Denominator_GetValue(RatioIndex) >> 1u));
}

/* ****************************************************************************
 % Dem_Iumpr_Ratio_Denominator_Lock
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_Denominator_Lock(CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex)
{
  Dem_Iumpr_Ratio_SetRatioStatusUtil(RatioIndex, (Dem_Iumpr_Ratio_GetRatioStatusUtil(RatioIndex) | DEM_DENOMINATOR_LOCKED));
}

/* ****************************************************************************
 % Dem_Iumpr_Ratio_Denominator_Release
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_Ratio_Denominator_Release(CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex)
{
  Dem_Iumpr_Ratio_SetRatioStatusUtil(RatioIndex, (Dem_Iumpr_Ratio_GetRatioStatusUtil(RatioIndex) & DEM_DENOMINATOR_LOCKED_MASK));
  return Dem_Iumpr_Ratio_Denominator_TestIncremented(RatioIndex);
}

/* ****************************************************************************
% Dem_Iumpr_Ratio_Denominator_UpdateRatioStatus
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
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_Ratio_Denominator_UpdateRatioStatus(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
)
{
  boolean lUpdateRatio;
  Dem_RatioIdIndexType lDenRatioGroup;

  lUpdateRatio = FALSE;
  lDenRatioGroup = Dem_Iumpr_Ratio_Denominator_GetDenominatorGroup(RatioIndex);

  if (lDenRatioGroup == DEM_IUMPR_DEN_500MI)
  {
    if (Dem_Iumpr_ConditionStatus_TestReached(DEM_IUMPR_DEN_500MI) == TRUE)
    {
      if (Dem_Iumpr_Ratio_Denominator_Reach(RatioIndex, DEM_IUMPR_DEN_500MI))
      {
        lUpdateRatio = TRUE;
      }
    }

    if (Dem_Iumpr_ConditionStatus_TestReached(DEM_IUMPR_GENERAL_INDIVIDUAL_DENOMINATOR) == TRUE)
    {
      if (Dem_Iumpr_Ratio_Denominator_Reach(RatioIndex, DEM_IUMPR_GENERAL_INDIVIDUAL_DENOMINATOR))
      {
        lUpdateRatio = TRUE;
      }
    }
  }

  return lUpdateRatio;
}

/* ****************************************************************************
 % Dem_Iumpr_Ratio_Denominator_GetDenominatorGroup
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Iumpr_Ratio_Denominator_GetDenominatorGroup(
CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex                                                                                            /* PRQA S 3206 */ /* MD_DEM_3206 */
)
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(RatioIndex)                                                                                   /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
    return Dem_Cfg_GetIumprDenGroupOfRatioIdTable(RatioIndex);
#else
    return 0;
#endif
}

/* ****************************************************************************
 % Dem_Iumpr_Ratio_Denominator_InitNv
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
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_Denominator_InitNv(
CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex

)
{
  /* Clear all status bits, independent of specific type */
  Dem_Iumpr_Ratio_Denominator_ResetIncremented(RatioIndex);
  Dem_Iumpr_Ratio_Denominator_ResetConditionsReached(RatioIndex);
  Dem_Iumpr_Ratio_Denominator_ResetGeneralIndividualConditionReached(RatioIndex);
  (void)Dem_Iumpr_Ratio_Denominator_Release(RatioIndex);

  Dem_Iumpr_Ratio_Denominator_SetValue(RatioIndex, 0); /* Reset the denominator counter value to 0 */
}


/* ****************************************************************************
 % Dem_Iumpr_Ratio_Denominator_OpCycleStart
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
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_Denominator_OpCycleStart(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
)
{
  /* Calls to specialized denominator instances that overwrite this function */
  switch (Dem_Iumpr_Ratio_Denominator_GetDenominatorGroup(RatioIndex))
  {
    case DEM_IUMPR_DEN_500MI:
    {
      Dem_Iumpr_Ratio_500Mi_OpCycleStart(RatioIndex);
      break;
    }
    default:
    {
      /* All other Denominator use the base implementation */
      Dem_Iumpr_Ratio_Denominator_ResetIncremented(RatioIndex);
      (void)Dem_Iumpr_Ratio_Denominator_Release(RatioIndex);
      Dem_Iumpr_Ratio_Denominator_ResetConditionsReached(RatioIndex);
      Dem_Iumpr_Ratio_Denominator_ResetGeneralIndividualConditionReached(RatioIndex);
      break;
    }
  }
}


/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_DENOMINATOR_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Denominator_Implementation.h
 *********************************************************************************************************************/
