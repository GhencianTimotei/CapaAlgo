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
/*! \addtogroup Dem_IumprIF
 *  \{
 *  \file       Dem_IumprIF_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Implementation of the Obd IumprIF subcomponent which manages calculation of the IUMPR ratios.
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_IUMPRIF_IMPLEMENTATION_H)
#define DEM_IUMPRIF_IMPLEMENTATION_H

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
#include "Dem_IumprIF_Interface.h"

/* Includes to access public functions belonging to other (top level)/ (logical)/- units to be used by this Unit */
/* ------------------------------------------------------------------------- */
#include "Dem_Infrastructure_Interface.h"
#include "Dem_Core_Interface.h"
#include "Dem_FaultMemory_Interface.h"
#include "Dem_Client_Interface.h"
#include "Dem_Ratio_Interface.h"

/* ********************************************************************************************************************
 *  FILE SPECIFIC MISRA VIOLATIONS
 *********************************************************************************************************************/
/* PRQA S 3406 DEM_IUMPR_IMPL */ /* MD_DEM_8.6 */


/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*! Filename declaration */
#define DEM_IUMPRIF_IMPLEMENTATION_FILENAME "Dem_IumprIF_Implementation.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/

#define DEM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Filter data for IUMPR readout */
DEM_LOCAL VAR(Dem_IumprFilter_InfoType, DEM_VAR_NOINIT)  Dem_Iumpr_FilterInfo;

#define DEM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */


/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE PROPERTIES DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_Iumpr_PrivateProperties Private Properties
 * \{
 */
 /* ****************************************************************************
 * Dem_Iumpr_RatioIter_Exists
 *****************************************************************************/
 /*!
 * \brief         Test if the iterator points to a valid element
 *
 * \details       Test if the iterator points to a valid element
 *
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \return        TRUE
 *                Dem_Iumpr_RatioIter_GetIdx() will return a valid element
 *                on this iterator
 * \return        FALSE
 *                Dem_Iumpr_RatioIter_GetIdx() is undefined on this iterator
 *
 * \pre           IterPtr has been initialized
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_RatioIter_Exists(
  CONSTP2CONST(Dem_Cfg_ObdRatioIdIterType, AUTOMATIC, AUTOMATIC)  IterPtr
);

/* ****************************************************************************
 * Dem_Iumpr_RatioIter_GetIdx
 *****************************************************************************/
/*!
 * \brief         Get the element pointed to by the iterator
 *
 * \details       Get the element pointed to by the iterator
 *
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \return        Unique handle of the Ratio
 *
 * \pre           IterPtr has been initialized
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_RatioIdIndexType, DEM_CODE)
Dem_Iumpr_RatioIter_GetIdx(
  CONSTP2CONST(Dem_Cfg_ObdRatioIdIterType, AUTOMATIC, AUTOMATIC)  IterPtr
);

/* ****************************************************************************
 * Dem_Iumpr_RatioIter_Init
 *****************************************************************************/
/*!
 * \brief         Init the iterator
 *
 * \details       Initializes the iterator to enumerate all configured ratios
 *
 * \param[out]    IterPtr
 *                Pointer to the iterator
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_RatioIter_Init(
  CONSTP2VAR(Dem_Cfg_ObdRatioIdIterType, AUTOMATIC, AUTOMATIC)  IterPtr
);

/* ****************************************************************************
 * Dem_Iumpr_RatioIter_Next
 *****************************************************************************/
/*!
 * \brief         Move the iterator to the next element
 *
 * \details       Move the iterator to the next element
 *
 * \param[in,out] IterPtr
 *                Pointer to the iterator
 *
 * \pre           IterPtr has been initialized
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_RatioIter_Next(
  CONSTP2VAR(Dem_Cfg_ObdRatioIdIterType, AUTOMATIC, AUTOMATIC)  IterPtr
);

/* ****************************************************************************
 * Dem_Iumpr_IsHybridCycleCounterEnabled
 *****************************************************************************/
/*!
 * \brief         Returns true if IUMPR Hybrid Cycle Counter feature set is enabled.
 * \details       -
 *
 * \return        TRUE
 *                Support for IUMPR Hybrid Cycle Counter
 * \return        FALSE
 *                No support for IUMPR Hybrid Cycle Counter
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_IsHybridCycleCounterEnabled(
  void
);

/* ****************************************************************************
 * Dem_Iumpr_CycleCounter_TestHybridCounterIncremented
 *****************************************************************************/
/*!
 * \brief         Test hybrid ignition cycle counter incremented state in 
 *                global hybrid ignition cycle state
 *
 * \details       -
 *
 *
 * \return        TRUE
 *                Hybrid ignition cyclce counter was incremented
 * \return        FALSE
 *                Hybrid ignition cyclce counter was not incremented
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_CycleCounter_TestHybridCounterIncremented(void);

/* ****************************************************************************
 * Dem_Iumpr_CycleCounter_SetHybridCounterIncremented
 *****************************************************************************/
/*!
 * \brief         Set hybrid ignition cycle counter incremented state in
 *                global hybrid ignition cycle state
 *
 * \details       -
 *
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_CycleCounter_SetHybridCounterIncremented(void);

/* ****************************************************************************
 * Dem_Iumpr_CycleCounter_ResetIncrementedHybridCycleCounter
 *****************************************************************************/
/*!
 * \brief         Reset hybrid ignition cycle counter incremented state in 
 *                global hybrid ignition cycle state
 *
 * \details       -
 *
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_CycleCounter_ResetIncrementedHybridCycleCounter(void);

/* ****************************************************************************
 * Dem_Iumpr_CycleCounter_IncrementHybridCycleCounter
 *****************************************************************************/
/*!
 * \brief         Increment hybrid ignition cycle counter
 *
 * \details       Increment hybrid ignition cycle counter
 *
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_CycleCounter_IncrementHybridCycleCounter(void);

/* ****************************************************************************
 * Dem_Iumpr_CycleCounter_ResetHybridCycleCounter
 *****************************************************************************/
/*!
 * \brief         Reset hybrid ignition cycle counter
 *
 * \details       Reset hybrid ignition cycle counter

 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_CycleCounter_ResetHybridCycleCounter(void);

/* ****************************************************************************
 * Dem_Iumpr_CycleCounter_IncrementIgnitionCycleCounter
 *****************************************************************************/
/*!
 * \brief         Increment ignition cycle counter
 *
 * \details       Increment ignition cycle counter
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_CycleCounter_IncrementIgnitionCycleCounter(void);

/* ****************************************************************************
 * Dem_Iumpr_CycleCounter_ResetIgnitionCycleCounter
 *****************************************************************************/
/*!
 * \brief         Reset ignition cycle counter
 *
 * \details       Reset ignition cycle counter
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_CycleCounter_ResetIgnitionCycleCounter(void);

/* ****************************************************************************
 * Dem_Iumpr_CycleCounter_GetIgnitionCycleCounter
 *****************************************************************************/
/*!
 * \brief         Get ignition cycle counter
 *
 * \details       Get ignition cycle counter
 *
 * \return        Value of the ignition cycle counter
 *
 * \pre           Feature IUMPR is supported
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Iumpr_CycleCounter_GetIgnitionCycleCounter(void);

/* ****************************************************************************
 * Dem_Iumpr_CycleCounter_GetHybridCycleCounter
 *****************************************************************************/
/*!
 * \brief         Get hybrid ignition cycle counter value
 *
 * \details       Get hybrid ignition cycle counter value
 *
 * \return        Value of the hybrid ignition cycle counter
 *
 * \pre           Feature IUMPR and hybrid ingnition cycle is supported
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Iumpr_CycleCounter_GetHybridCycleCounter(void);


/* ****************************************************************************
 * Dem_Iumpr_OBDDenominator_GetValue
 *****************************************************************************/
/*!
 * \brief         Get the general denominator counter
 *
 * \details       Get the general denominator counter
 *
 * \return        The value of the general denominator counter
 *
 * \pre           Feature IUMPR is supported
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Iumpr_OBDDenominator_GetValue(
  void
);

/* ****************************************************************************
 * Dem_Iumpr_OBDDenominator_SetValue
 *****************************************************************************/
/*!
 * \brief         Set the general denominator counter
 *
 * \details       Set the general denominator counter
 *
 * \param[in]     Value
 *                The new counter value
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different RatioIdx
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_OBDDenominator_SetValue(
  CONST(uint16, AUTOMATIC) Value
);

/* ****************************************************************************
 * Dem_Iumpr_ConditionStatus_SetReached
 *****************************************************************************/
/*!
 * \brief         Set global denominator conditions reached state
 *
 * \details       Set global denominator conditions reached state
 *
 * \param[in]     ConditionId
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_ConditionStatus_SetReached(
  Dem_IumprDenomCondIdType ConditionId
);

/* ****************************************************************************
 * Dem_Iumpr_ConditionStatus_ResetReached
 *****************************************************************************/
/*!
 * \brief         Reset global conditions reached state
 *
 * \details       Reset global conditions reached state
 *
 * \param[in]     ConditionId
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_ConditionStatus_ResetReached(
  Dem_IumprDenomCondIdType ConditionId
);

/* ****************************************************************************
 * Dem_Iumpr_ConditionStatus_TestInhibited
 *****************************************************************************/
/*!
 * \brief         Test conditions inhibited state
 *
 * \details       Test conditions inhibited state
 *
 * \param[in]     ConditionId
 *
 * \return        TRUE
 *                Denominator condition is currently inhibited
 * \return        FALSE
 *                Denominator condition is currently uninhibited
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_ConditionStatus_TestInhibited(
  Dem_IumprDenomCondIdType ConditionId
);

/* ****************************************************************************
 * Dem_Iumpr_ConditionStatus_SetInhibited
 *****************************************************************************/
/*!
 * \brief         Set conditions inhibited state
 *
 * \details       Set conditions inhibited state
 *
 * \param[in]     ConditionId
 *
 * \return        TRUE: Condition was inhibited
 *                FALSE: No condition was inhibited
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_ConditionStatus_SetInhibited(
  Dem_IumprDenomCondIdType ConditionId
);

/* ****************************************************************************
 * Dem_Iumpr_ConditionStatus_ResetInhibited
 *****************************************************************************/
/*!
 * \brief         Reset conditions inhibited state
 *
 * \details       Reset conditions inhibited state
 *
 * \param[in]     ConditionId
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_ConditionStatus_ResetInhibited(
  Dem_IumprDenomCondIdType ConditionId
);

/* ****************************************************************************
 * Dem_Iumpr_ConditionStatus_SetNotReached
 *****************************************************************************/
/*!
 * \brief         Reset conditions reached state
 *
 * \details       Reset conditions reached state, currently only supported for
 *                General Individual Denominator condition
 *
 * \param[in]     ConditionId
 *
 * \param[out]    TRUE: Condition reached state was reset
 *                FALSE: No condition reached state was reset
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_ConditionStatus_SetNotReached(
  Dem_IumprDenomCondIdType ConditionId
  );

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE PROPERTIES DEFINITIONS
 *********************************************************************************************************************/

 /* ****************************************************************************
 % Dem_Iumpr_RatioIter_Exists
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_RatioIter_Exists(
  CONSTP2CONST(Dem_Cfg_ObdRatioIdIterType, AUTOMATIC, AUTOMATIC)  IterPtr
)
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
    return (boolean)(*IterPtr < Dem_Cfg_GetSizeOfRatioIdTable());
#else
    return FALSE;
#endif
}

/* ****************************************************************************
 % Dem_Iumpr_RatioIter_GetIdx
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_RatioIdIndexType, DEM_CODE)
Dem_Iumpr_RatioIter_GetIdx(
  CONSTP2CONST(Dem_Cfg_ObdRatioIdIterType, AUTOMATIC, AUTOMATIC)  IterPtr
)
{
  return (Dem_RatioIdIndexType)*IterPtr;
}

/* ****************************************************************************
 % Dem_Iumpr_RatioIter_Init
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_RatioIter_Init(
  CONSTP2VAR(Dem_Cfg_ObdRatioIdIterType, AUTOMATIC, AUTOMATIC)  IterPtr
)
{
  *IterPtr = 0u;                                                                                                                  /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}

/* ****************************************************************************
 % Dem_Iumpr_RatioIter_Next
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_RatioIter_Next(
  CONSTP2VAR(Dem_Cfg_ObdRatioIdIterType, AUTOMATIC, AUTOMATIC)  IterPtr
)
{
  *IterPtr += 1u;                                                                                                                 /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}

/* ****************************************************************************
 % Dem_Iumpr_ConditionStatus_SetReached
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_ConditionStatus_SetReached(
  Dem_IumprDenomCondIdType ConditionId
)
{
  switch (ConditionId)
  {
   case DEM_IUMPR_GENERAL_OBDCOND:
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
    /* For general OBD denominator this bit means that denominator is incremented */
    Dem_Cfg_ObdIumprData.DenominatorConditionStatusReached = ((uint8)(Dem_Cfg_ObdIumprData.DenominatorConditionStatusReached | DEM_IUMPR_CONDITIONSTATUS_GENOBD));
#endif
    break;
  case DEM_IUMPR_GENERAL_INDIVIDUAL_DENOMINATOR:
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
    Dem_Cfg_ObdIumprData.DenominatorConditionStatusReached = ((uint8)(Dem_Cfg_ObdIumprData.DenominatorConditionStatusReached | DEM_IUMPR_CONDITIONSTATUS_GENIND));
#endif
    break;

  case DEM_IUMPR_DEN_COND_COLDSTART:
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
    Dem_Cfg_ObdIumprData.DenominatorConditionStatusReached = ((uint8)(Dem_Cfg_ObdIumprData.DenominatorConditionStatusReached | DEM_IUMPR_CONDITIONSTATUS_COLDSTART));
#endif
    break;

  case DEM_IUMPR_DEN_COND_EVAP:
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
    Dem_Cfg_ObdIumprData.DenominatorConditionStatusReached = ((uint8)(Dem_Cfg_ObdIumprData.DenominatorConditionStatusReached | DEM_IUMPR_CONDITIONSTATUS_EVAP));
#endif
    break;

  case DEM_IUMPR_DEN_COND_500MI:
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
    Dem_Cfg_ObdIumprData.DenominatorConditionStatusReached = ((uint8)(Dem_Cfg_ObdIumprData.DenominatorConditionStatusReached | DEM_IUMPR_CONDITIONSTATUS_500MI));
#endif
    break;

  case DEM_IUMPR_DEN_COND_INDEPENDENT:
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
    Dem_Cfg_ObdIumprData.DenominatorConditionStatusReached = ((uint8)(Dem_Cfg_ObdIumprData.DenominatorConditionStatusReached | DEM_IUMPR_CONDITIONSTATUS_INDEPENDENT));
#endif
    break;

  default:
    /* MISRA Case */
    break;
  }
}

/* ****************************************************************************
 % Dem_Iumpr_ConditionStatus_ResetReached
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_ConditionStatus_ResetReached(
  Dem_IumprDenomCondIdType ConditionId
)
{
  switch (ConditionId)
  {
    case DEM_IUMPR_GENERAL_OBDCOND:
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
      /* For general OBD denominator this bit means that denominator is incremented */
      Dem_Cfg_ObdIumprData.DenominatorConditionStatusReached = ((uint8)(Dem_Cfg_ObdIumprData.DenominatorConditionStatusReached & DEM_IUMPR_CONDITIONSTATUS_GENOBD_MASK));
#endif
    break;
  case DEM_IUMPR_GENERAL_INDIVIDUAL_DENOMINATOR:
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
    Dem_Cfg_ObdIumprData.DenominatorConditionStatusReached = ((uint8)(Dem_Cfg_ObdIumprData.DenominatorConditionStatusReached & DEM_IUMPR_CONDITIONSTATUS_GENIND_MASK));
#endif
    break;

  case DEM_IUMPR_DEN_COND_COLDSTART:
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
    Dem_Cfg_ObdIumprData.DenominatorConditionStatusReached = ((uint8)(Dem_Cfg_ObdIumprData.DenominatorConditionStatusReached & DEM_IUMPR_CONDITIONSTATUS_COLDSTART_MASK));
#endif
    break;

  case DEM_IUMPR_DEN_COND_EVAP:
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
    Dem_Cfg_ObdIumprData.DenominatorConditionStatusReached = ((uint8)(Dem_Cfg_ObdIumprData.DenominatorConditionStatusReached & DEM_IUMPR_CONDITIONSTATUS_EVAP_MASK));
#endif
    break;

  case DEM_IUMPR_DEN_COND_500MI:
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
    Dem_Cfg_ObdIumprData.DenominatorConditionStatusReached = ((uint8)(Dem_Cfg_ObdIumprData.DenominatorConditionStatusReached & DEM_IUMPR_CONDITIONSTATUS_500MI_MASK));
#endif
    break;

  case DEM_IUMPR_DEN_INDEPENDENT:
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
    Dem_Cfg_ObdIumprData.DenominatorConditionStatusReached = ((uint8)(Dem_Cfg_ObdIumprData.DenominatorConditionStatusReached & DEM_IUMPR_CONDITIONSTATUS_INDEPENDENT_MASK));
#endif
    break;

  default:
    /* MISRA Case */
    break;
  }
}

/* ****************************************************************************
 % Dem_Iumpr_ConditionStatus_TestInhibited
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_ConditionStatus_TestInhibited(
  Dem_IumprDenomCondIdType ConditionId
)
{
  boolean lReturnValue = FALSE;
  switch (ConditionId)
  {
  case DEM_IUMPR_GENERAL_OBDCOND:
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
    lReturnValue = ((Dem_Cfg_ObdIumprData.DenominatorConditionStatusInhibited & DEM_IUMPR_CONDITIONSTATUS_GENOBD) != 0u);
#endif
    break;
  case DEM_IUMPR_GENERAL_INDIVIDUAL_DENOMINATOR:
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
    lReturnValue = ((Dem_Cfg_ObdIumprData.DenominatorConditionStatusInhibited & DEM_IUMPR_CONDITIONSTATUS_GENIND) != 0u);
#endif
    break;
  default:
    /* currently only general denominators can be inhibited, return FALSE */
    break;
  }

  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Iumpr_ConditionStatus_SetInhibited
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_ConditionStatus_SetInhibited(
  Dem_IumprDenomCondIdType ConditionId
)
{
  boolean lInhibitedCondition = FALSE;
  switch (ConditionId)
  {
  case DEM_IUMPR_GENERAL_OBDCOND:
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
    Dem_Cfg_ObdIumprData.DenominatorConditionStatusInhibited = ((uint8)(Dem_Cfg_ObdIumprData.DenominatorConditionStatusInhibited | DEM_IUMPR_CONDITIONSTATUS_GENOBD));
    lInhibitedCondition = TRUE;
#endif
    break;
  case DEM_IUMPR_GENERAL_INDIVIDUAL_DENOMINATOR:
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
    Dem_Cfg_ObdIumprData.DenominatorConditionStatusInhibited = ((uint8)(Dem_Cfg_ObdIumprData.DenominatorConditionStatusInhibited | DEM_IUMPR_CONDITIONSTATUS_GENIND));
    lInhibitedCondition = TRUE;
#endif
    break;
  default:
    /* currently only general denominators can be inhibited, return FALSE */
    break;
  }

  return lInhibitedCondition;
}

/* ****************************************************************************
 % Dem_Iumpr_ConditionStatus_ResetInhibited
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_ConditionStatus_ResetInhibited(
  Dem_IumprDenomCondIdType ConditionId
)
{
    switch (ConditionId)
  {
  case DEM_IUMPR_GENERAL_OBDCOND:
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
    Dem_Cfg_ObdIumprData.DenominatorConditionStatusInhibited = ((uint8)(Dem_Cfg_ObdIumprData.DenominatorConditionStatusInhibited & DEM_IUMPR_CONDITIONSTATUS_GENOBD_MASK));
#endif
    break;
  case DEM_IUMPR_GENERAL_INDIVIDUAL_DENOMINATOR:
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
    Dem_Cfg_ObdIumprData.DenominatorConditionStatusInhibited = ((uint8)(Dem_Cfg_ObdIumprData.DenominatorConditionStatusInhibited & DEM_IUMPR_CONDITIONSTATUS_GENIND_MASK));
#endif
    break;
  default:
    /* currently only general denominators can be inhibited, do nothing */
    break;
  }
}

/* ****************************************************************************
 % Dem_Iumpr_ConditionStatus_SetNotReached
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_ConditionStatus_SetNotReached(
  Dem_IumprDenomCondIdType ConditionId
)
{
  boolean lReachedStateReset = FALSE;
  if (ConditionId == DEM_IUMPR_GENERAL_INDIVIDUAL_DENOMINATOR)
  {
    Dem_Iumpr_ConditionStatus_ResetReached(ConditionId);
    lReachedStateReset = TRUE;
  }
  return lReachedStateReset;
}

/* ****************************************************************************
 % Dem_Iumpr_OBDDenominator_SetValue
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_OBDDenominator_SetValue(
CONST(uint16, AUTOMATIC) Value
)
{
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
  Dem_Cfg_ObdIumprData.GeneralDenominator = Value;
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(Value)                                                                                        /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
}

/* ****************************************************************************
 % Dem_Iumpr_OBDDenominator_GetValue
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Iumpr_OBDDenominator_GetValue(
  void
)
{
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
  return (uint16)(Dem_Cfg_ObdIumprData.GeneralDenominator);
#else
  return (uint16)0;
#endif
}

/* ****************************************************************************
 % Dem_Iumpr_IsHybridCycleCounterEnabled()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_IsHybridCycleCounterEnabled(void)
{
  return (boolean)(DEM_CFG_SUPPORT_CYCLE_IGNITION_HYBRID == STD_ON);
}

/* ****************************************************************************
 % Dem_Iumpr_CycleCounter_ResetHybridCycleCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_CycleCounter_ResetHybridCycleCounter(void)                                                                                               /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
{
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON) && (DEM_CFG_SUPPORT_CYCLE_IGNITION_HYBRID)
  Dem_Cfg_AdminData.IgnitionCycleHybridCounter = 0u;
#endif
}

/* ****************************************************************************
 % Dem_Iumpr_CycleCounter_TestHybridCounterIncremented
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_CycleCounter_TestHybridCounterIncremented(void)
{
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
  return (((Dem_Cfg_ObdIumprData.GlobalHybridStatus)& DEM_IUMPR_IGN_CYC_HYBRID_INCREMENTED) != 0u);
#else
  return FALSE;
#endif
}

/* ****************************************************************************
 % Dem_Iumpr_CycleCounter_SetHybridCounterIncremented
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_CycleCounter_SetHybridCounterIncremented(void)
{
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
  Dem_Cfg_ObdIumprData.GlobalHybridStatus = ((Dem_Cfg_ObdIumprData.GlobalHybridStatus) | DEM_IUMPR_IGN_CYC_HYBRID_INCREMENTED);
  Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_IUMPR),
      DEM_NVM_BLOCKSTATE_DIRTY);
#endif
}

/* ****************************************************************************
 % Dem_Iumpr_CycleCounter_ResetIncrementedHybridCycleCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_CycleCounter_ResetIncrementedHybridCycleCounter(void)                                                                                    /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
{
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
  Dem_Cfg_ObdIumprData.GlobalHybridStatus = ((Dem_Cfg_ObdIumprData.GlobalHybridStatus)& DEM_IUMPR_IGN_CYC_HYBRID_INCREMENTED_MASK);
#endif
}

/* ****************************************************************************
 % Dem_Iumpr_CycleCounter_IncrementHybridCycleCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_CycleCounter_IncrementHybridCycleCounter(void)
{
  /* Overflow handling is done with an reset to 0, which is the expected c behaviour  */
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON) && (DEM_CFG_SUPPORT_CYCLE_IGNITION_HYBRID == STD_ON)
  Dem_Cfg_AdminData.IgnitionCycleHybridCounter = Dem_Cfg_AdminData.IgnitionCycleHybridCounter + 1u;
#endif
  Dem_Iumpr_CycleCounter_SetHybridCounterIncremented();
}

/* ****************************************************************************
 % Dem_Iumpr_CycleCounter_IncrementIgnitionCycleCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_CycleCounter_IncrementIgnitionCycleCounter(void)
{
  /* Overflow handling is done with an reset to 0, which is the expected c behaviour  */
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
  Dem_Cfg_AdminData.IgnitionCycleCounter = Dem_Cfg_AdminData.IgnitionCycleCounter + 1u;
#endif
}

/* ****************************************************************************
 % Dem_Iumpr_CycleCounter_ResetIgnitionCycleCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_CycleCounter_ResetIgnitionCycleCounter(void)                                                                                                     /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
{
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
  Dem_Cfg_AdminData.IgnitionCycleCounter = 0u;
#endif
}

/* ****************************************************************************
 % Dem_Iumpr_CycleCounter_GetHybridCycleCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Iumpr_CycleCounter_GetHybridCycleCounter(void)                                                                                            /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
{
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON) && (DEM_CFG_SUPPORT_CYCLE_IGNITION_HYBRID)
  return Dem_Cfg_AdminData.IgnitionCycleHybridCounter;
#else
  return 0;
#endif
}

/* ****************************************************************************
 % Dem_Iumpr_CycleCounter_GetIgnitionCycleCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Iumpr_CycleCounter_GetIgnitionCycleCounter(void)
{
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
  return Dem_Cfg_AdminData.IgnitionCycleCounter;
#else
  return 0;
#endif
}
/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT PUBLIC PROPERTIES DEFINITIONS
 *********************************************************************************************************************/

#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \addtogroup Dem_Iumpr_PublicProperties
 * \{
 */

/* ****************************************************************************
 % Dem_Iumpr_IsEnabled()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_IsEnabled(void)
{
  return (boolean)(DEM_CFG_SUPPORT_IUMPR == STD_ON);
}


/* ****************************************************************************
% Dem_Iumpr_ConditionStatus_TestReached
*****************************************************************************/
/*!
* Internal comment removed.
 *
 *
*/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_ConditionStatus_TestReached(
  Dem_IumprDenomCondIdType ConditionId
)
{
  boolean lReturnValue = FALSE;

  switch (ConditionId)
  {
    case DEM_IUMPR_GENERAL_OBDCOND:
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
    /* For general OBD denominator this bit means that denominator is incremented */
    lReturnValue = ((Dem_Cfg_ObdIumprData.DenominatorConditionStatusReached & DEM_IUMPR_CONDITIONSTATUS_GENOBD) != 0u);
#endif
    break;
  case DEM_IUMPR_GENERAL_INDIVIDUAL_DENOMINATOR:
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
    lReturnValue = ((Dem_Cfg_ObdIumprData.DenominatorConditionStatusReached & DEM_IUMPR_CONDITIONSTATUS_GENIND) != 0u);
#endif
    break;
  case DEM_IUMPR_DEN_COND_COLDSTART:
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
    lReturnValue = ((Dem_Cfg_ObdIumprData.DenominatorConditionStatusReached & DEM_IUMPR_CONDITIONSTATUS_COLDSTART) != 0u);
#endif
    break;
  case DEM_IUMPR_DEN_COND_EVAP:
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
    lReturnValue = ((Dem_Cfg_ObdIumprData.DenominatorConditionStatusReached & DEM_IUMPR_CONDITIONSTATUS_EVAP) != 0u);
#endif
    break;
  case DEM_IUMPR_DEN_COND_500MI:
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
    lReturnValue = ((Dem_Cfg_ObdIumprData.DenominatorConditionStatusReached & DEM_IUMPR_CONDITIONSTATUS_500MI) != 0u);
#endif
    break;
  case DEM_IUMPR_DEN_INDEPENDENT:
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
    lReturnValue = ((Dem_Cfg_ObdIumprData.DenominatorConditionStatusReached & DEM_IUMPR_CONDITIONSTATUS_INDEPENDENT) != 0u);
#endif
    break;
  default:
    /* MISRA Case */
    break;
  }

  return lReturnValue;
}



/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_Iumpr_Private Private Methods
 * \{
 */

/* ****************************************************************************
 * Dem_Iumpr_UpdateConditionStatus
 *****************************************************************************/
/*!
 * \brief         Report denominator condition to all monitor specific denominators.
 *
 * \details       Report denominator condition to all monitor specific denominators.
 *
 * \param[in]     ConditionId
 *                The denominator group for which the conditions are reported.
 * \param[in]     ConditionStatus
 *                The new status of the given ConditionId
 *
 *
 * \pre           RTE is active (if RTE is used)
 * \config        Feature IUMPR is supported
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   FALSE
 * \reentrant     TRUE for different ConditionIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_UpdateConditionStatus(
CONST(Dem_IumprDenomCondIdType, AUTOMATIC) ConditionId,
CONST(Dem_IumprDenomCondStatusType, AUTOMATIC) ConditionStatus
);

/* ****************************************************************************
 * Dem_Iumpr_SetOBDDenominatorCondition()
 *****************************************************************************/
/*!
 * \brief         Set general OBD condition reached, not-reached, or inhibited.
 *
 * \details       Set general OBD condition status.
 *                If reported reached: Increment general denominator,
 *                if it has not been incremented in the current operation cycle.
 *                If reported inhibited: Set the general denominator increase to
 *                inhibited, for the current operation cycle.
 *
 *
 * \param[in]     ConditionStatus
 *                The new status of the general OBD condition
 *
 * \return        E_OK
 *                Condition status was accepted
 * \return        E_NOT_OK
 *                Condition status is rejected, since general denominator
 *                increase is inhibited.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_Iumpr_SetOBDDenominatorCondition(
Dem_IumprDenomCondStatusType ConditionStatus
);


/* ****************************************************************************
 * Dem_Iumpr_SetDenominatorConditionStatus()
 *****************************************************************************/
/*!
 * \brief         Set denominator conditions reached, not-reached or inhibited.
 *
 * \details       Set denominator conditions reached, not-reached or inhibited.
 *                Only the general denomniator can be inhibited.
 *
 * \param[in]     DenominatorGroup
 *                Unique handle of denominator group
 * \param[in]     ConditionStatus
 *                The new status of the given ConditionId
 *
 * \return        E_OK
 *                Condition status was accepted
 * \return        E_NOT_OK
 *                Condition status is rejected, since general denominator
 *                increase is inhibited.
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   FALSE
 * \reentrant     TRUE for different ConditionIds
 *****************************************************************************/
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_Iumpr_SetDenominatorConditionStatus(
Dem_IumprDenomCondIdType ConditionId,
Dem_IumprDenomCondStatusType ConditionStatus
);

/* ****************************************************************************
 * Dem_Iumpr_CycleCounter_InitStatus()
 *****************************************************************************/
/*!
 * \brief        Initialize global hybrid ignition cycle status 
 *
 * \details       -
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   FALSE
 * \reentrant     TRUE for different ConditionIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_CycleCounter_InitStatus(
  void
);

/* ****************************************************************************
 * Dem_Iumpr_CycleCounter_InitMemory
 *****************************************************************************/
/*!
 * \brief         Initialize ignition cycle counters
 *
 * \details       Initialize ignition cycle counter and hybrid cycle counter
 *
 *
 * \pre           Feature IUMPR is supported
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_CycleCounter_InitMemory(void);

/* ****************************************************************************
 * Dem_Iumpr_CycleCounter_GetValue()
 *****************************************************************************/
/*!
 * \brief        Retrieve value of cycle counter
 *
 * \details       -
 *
 * \param[in]     CycleCounter
 *                Ignition Cycle Counter or Ignition Hybrid Cycle Counter
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   FALSE
 * \reentrant     TRUE for different ConditionIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Iumpr_CycleCounter_GetValue(
  Dem_Iumpr_CycleCounter_CycleCounterType CycleCounter
);

/* ****************************************************************************
 * Dem_Iumpr_CycleCounter_Increment()
 *****************************************************************************/
/*!
 * \brief         Increment value of cycle counter
 *
 * \details       -
 *
 * \param[in]     CycleCounter
 *                Ignition Cycle Counter or Ignition Hybrid Cycle Counter
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   FALSE
 * \reentrant     TRUE for different ConditionIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_CycleCounter_Increment(
  Dem_Iumpr_CycleCounter_CycleCounterType CycleCounter
);

/*****************************************************************************
 * Dem_Iumpr_RestartDcy
 *****************************************************************************/
/*!
* \brief         Resets global and ratio specific IUMPR status information.
*
* \details        Resets event specific ratio status information
*                 Resets general OBD denominator status.
*                 Resets global IUMPR denominator status.
*                 Resets the hybrid ignition cycles status
*                 Resets the numerator locked status
*
* \pre           Feature IUMPR is supported
*
* \context       TASK
* \synchronous   TRUE
* \reentrant     FALSE
*/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_RestartDcy(
  void
);

/* ****************************************************************************
 * Dem_Iumpr_OBDDenominator_InitStatus()
 *****************************************************************************/
/*!
 * \brief         Initialize global OBD denominator cycle status
 *
 * \details       -
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   FALSE
 * \reentrant     TRUE for different ConditionIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_OBDDenominator_InitStatus(
  void
);

/* ****************************************************************************
 * Dem_Iumpr_OBDDenominator_InitNv
 *****************************************************************************/
/*!
 * \brief         Initalize general OBD denominator
 *
 * \details       Initalize general OBD denominator
 *
 *
 * \pre           Feature IUMPR is supported
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_OBDDenominator_InitNv(
  void
);

/* ****************************************************************************
 * Dem_Iumpr_OBDDenominator_Increment
 *****************************************************************************/
/*!
 * \brief         Increment the general denominator counter
 *
 * \details       Increment the general denominator counter
 *
 * \param[out]    UpdateNvM
 *                TRUE: Counter value has changed
 *                FALSE: Counter value has not changed
 * \return        E_OK
 *                Incrementing is not inhibited
 * \return        E_NOT_OK
 *                Incrementing is inhibited
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Iumpr_OBDDenominator_Increment(
  CONSTP2VAR(boolean, AUTOMATIC, AUTOMATIC)  UpdateNvM
);

/* ****************************************************************************
 * Dem_Iumpr_OBDDenominator_Inhibit
 *****************************************************************************/
/*!
 * \brief         Set the general OBD denominator to inhibited
 *
 * \details       Set the general OBD denominator to inhibited
 *
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_OBDDenominator_Inhibit(
  void
);

/* ****************************************************************************
 * Dem_Iumpr_ConditionStatus_InitStatus()
 *****************************************************************************/
/*!
 * \brief         Initialize condition status
 *
 * \details       Initialize condition status
 *
 * \param[in]     ConditionId
 *
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   FALSE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_ConditionStatus_InitStatus(
  Dem_IumprDenomCondIdType ConditionId
);

/* ****************************************************************************
* Dem_Iumpr_ProcessIgnCycleCounterIncrement
*****************************************************************************/
/*!
* \brief         Increment ignition cycle counter
*
* \details       Increments ignition cycle counter if conditions are fulfilled
*
* \pre           Feature IUMPR is supported
*
* \context       TASK
* \synchronous   TRUE
* \reentrant     FALSE
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_ProcessIgnCycleCounterIncrement(
  void
);



/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/                                                                                                                               /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_Iumpr_UpdateConditionStatus()
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
 *
 *****************************************************************************/
DEM_LOCAL_INLINE  FUNC(void, DEM_CODE)
Dem_Iumpr_UpdateConditionStatus(
  CONST(Dem_IumprDenomCondIdType, AUTOMATIC) ConditionId,
  CONST(Dem_IumprDenomCondStatusType, AUTOMATIC) ConditionStatus
  )
{
  /* Conditions for a denominator group have been changed and general denominator conditions are not inhibited */
  Dem_Cfg_ObdRatioIdIterType lRatioIter;
  boolean lUpdateNvM;
  boolean lUpdateRatio;

  lUpdateNvM = FALSE;
  lUpdateRatio = FALSE;

  /* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
  Dem_EnterCritical_DiagMonitor();

  /* update global denominator condition status */
  switch (ConditionStatus)
  {
  case DEM_IUMPR_DEN_STATUS_REACHED:
    if (Dem_Iumpr_ConditionStatus_TestReached(ConditionId) == FALSE)
    {
      Dem_Iumpr_ConditionStatus_SetReached(ConditionId);
      lUpdateNvM = TRUE;
    }
    /* Update ratio unconditionally to increment denominators that were locked by FID at the last condition update */
    lUpdateRatio = TRUE;
    break;
  case DEM_IUMPR_DEN_STATUS_NOT_REACHED:
    if (Dem_Iumpr_ConditionStatus_TestReached(ConditionId) == TRUE)
    {
      lUpdateNvM = Dem_Iumpr_ConditionStatus_SetNotReached(ConditionId);
    }
    break;
  case DEM_IUMPR_DEN_STATUS_INHIBITED:
    if (Dem_Iumpr_ConditionStatus_TestInhibited(ConditionId) == FALSE)
    {
      lUpdateNvM = Dem_Iumpr_ConditionStatus_SetInhibited(ConditionId);
    }
    break;
  default:
    /* do nothing */
    break;
  }
  Dem_LeaveCritical_DiagMonitor();
  /* <<<< -------------------------------- Leave Critical Section: DiagMonitor */
 
  for (Dem_Iumpr_RatioIter_Init(&lRatioIter);                                                                                    /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_Iumpr_RatioIter_Exists(&lRatioIter) == TRUE;                                                                             /* PRQA S 2994 */ /* MD_DEM_2994 */ /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_Iumpr_RatioIter_Next(&lRatioIter))                                                                                       /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_RatioIdIndexType lRatioIndex;

    lRatioIndex = Dem_Iumpr_RatioIter_GetIdx(&lRatioIter);                                                                       /* SBSW_DEM_CALL_ITERATOR_POINTER */

    /* Queue relevent ratios for an update  */
    if ( ((Dem_Iumpr_Ratio_Denominator_GetDenominatorGroup(lRatioIndex) == ConditionId)
      || (ConditionId == DEM_IUMPR_GENERAL_INDIVIDUAL_DENOMINATOR))
      && (lUpdateRatio ==TRUE)
      && (Dem_Iumpr_Ratio_Denominator_TestIncremented(lRatioIndex) == FALSE) )                                                   /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
    {
      Dem_Iumpr_Ratio_QueueUpdate(lRatioIndex, TRUE);
      Dem_Scheduler_EnableTaskOnce(Dem_Scheduler_Task_IUMPR);
    }
  }

  if (lUpdateNvM == TRUE)
  {
    Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_IUMPR), DEM_NVM_BLOCKSTATE_DIRTY);
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_Iumpr_SetOBDDenominatorCondition()
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
 *****************************************************************************/
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_Iumpr_SetOBDDenominatorCondition(
Dem_IumprDenomCondStatusType ConditionStatus
)
{
  Std_ReturnType lReturnValue;
  boolean lUpdateNvM;

  lReturnValue = E_OK;
  lUpdateNvM = FALSE;

  switch (ConditionStatus)
  {
  case DEM_IUMPR_DEN_STATUS_REACHED:
    /* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
    Dem_EnterCritical_DiagMonitor();
    lReturnValue = Dem_Iumpr_OBDDenominator_Increment(&lUpdateNvM);                                                              /* SBSW_DEM_POINTER_FORWARD_STACK */
    Dem_LeaveCritical_DiagMonitor();
    /* <<<< -------------------------------- Leave Critical Section: DiagMonitor */
    break;

  case DEM_IUMPR_DEN_STATUS_INHIBITED:
    /* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
    Dem_EnterCritical_DiagMonitor();
    Dem_Iumpr_OBDDenominator_Inhibit();
    Dem_LeaveCritical_DiagMonitor();
    /* <<<< -------------------------------- Leave Critical Section: DiagMonitor */
    lUpdateNvM = TRUE;
    break;

  case DEM_IUMPR_DEN_STATUS_NOT_REACHED:
    if (Dem_Iumpr_ConditionStatus_TestInhibited(DEM_IUMPR_GENERAL_OBDCOND) == TRUE)
    {
      lReturnValue = E_NOT_OK;
    }
    break;

  default:                                                                                                                       /* PRQA S 2016 */ /* MD_MSR_EmptyClause */
    /* MISRA Case */
    break;
  }


  if (lUpdateNvM == TRUE)
  {
    /* update NvM */
    Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_IUMPR), DEM_NVM_BLOCKSTATE_DIRTY);
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */



/* ****************************************************************************
 % Dem_Iumpr_SetDenominatorConditionStatus()
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
 *****************************************************************************/
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_Iumpr_SetDenominatorConditionStatus(
Dem_IumprDenomCondIdType ConditionId,                                                                                            /* PRQA S 1330 */ /* MD_DEM_8.3_rte */
Dem_IumprDenomCondStatusType ConditionStatus
)
{
  Std_ReturnType lReturnValue;

  if (Dem_Iumpr_ConditionStatus_TestInhibited(DEM_IUMPR_GENERAL_INDIVIDUAL_DENOMINATOR) == FALSE)
  {
    Dem_Iumpr_UpdateConditionStatus(ConditionId, ConditionStatus);
    lReturnValue = E_OK;
  }
  else if ((ConditionId == DEM_IUMPR_GENERAL_INDIVIDUAL_DENOMINATOR) && (ConditionStatus == DEM_IUMPR_DEN_STATUS_INHIBITED))
  {
    /* General Indivdual Denominator is already inhibited, nothing to do */
    lReturnValue = E_OK;
  }
  else
  {
    lReturnValue = E_NOT_OK;
  }

  return lReturnValue;
}

/* ****************************************************************************
% Dem_Iumpr_ProcessIgnCycleCounterIncrement
*****************************************************************************/
/*!
* Internal comment removed.
 *
 *
 *
 *
*/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_ProcessIgnCycleCounterIncrement(void)                                                                                          /* PRQA S 3219 */ /* MD_DEM_14.1_CONFIGURATION_SWITCH */
{
  Dem_FimFid_PendingStateType lFiMPendingState;

  /* increment ignition cycle counter when DCY is qualified and increment is not inhibited by an input fault */
  lFiMPendingState = Dem_FimFid_QueryPendingState(Dem_FimFid_GetIgnitionCycle());
  if (lFiMPendingState == Dem_FimFid_PendingState_NotPending)
  {
    Dem_Iumpr_CycleCounter_Increment(Dem_Iumpr_CycleCounter_IgnitionCycleCounter);                                                                                                       /* PRQA S 3112 */ /* MD_DEM_14.2_CONFIGURATION_SWITCH */
  }
}

/* ****************************************************************************
 % Dem_Iumpr_CycleCounter_GetValue()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Iumpr_CycleCounter_GetValue(Dem_Iumpr_CycleCounter_CycleCounterType CycleCounter)                                                                                            /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
{
  uint16 lCycleCounterValue;
  lCycleCounterValue = 0;
  switch (CycleCounter)
  {
  case Dem_Iumpr_CycleCounter_IgnitionCycleCounter:
    lCycleCounterValue = Dem_Iumpr_CycleCounter_GetIgnitionCycleCounter();
    break;
  case Dem_Iumpr_CycleCounter_IgnitionHybridCycleCounter:
    lCycleCounterValue = Dem_Iumpr_CycleCounter_GetHybridCycleCounter();
    break;
  default:
    /* No valid cycle counter type */
    break;
  }
  return lCycleCounterValue;
}

/* ****************************************************************************
 % Dem_Iumpr_CycleCounter_Increment()
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
Dem_Iumpr_CycleCounter_Increment(Dem_Iumpr_CycleCounter_CycleCounterType CycleCounter)                                                                                            /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
{

  switch (CycleCounter)
  {
  case Dem_Iumpr_CycleCounter_IgnitionCycleCounter:
    Dem_Iumpr_CycleCounter_IncrementIgnitionCycleCounter();
    break;
  case Dem_Iumpr_CycleCounter_IgnitionHybridCycleCounter:
    Dem_Iumpr_CycleCounter_IncrementHybridCycleCounter();
    break;
  default:
    /* No valid cycle counter type */
    break;
  }
}

/* ****************************************************************************
 % Dem_Iumpr_CycleCounter_InitStatus()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_CycleCounter_InitStatus(void)                                                                                            /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
{
  Dem_Iumpr_CycleCounter_ResetIncrementedHybridCycleCounter();
}

/* ****************************************************************************
 % Dem_Iumpr_CycleCounter_InitMemory
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_CycleCounter_InitMemory(void)                                                                                                 /* PRQA S 3219 */ /* MD_DEM_14.1_CONFIGURATION_SWITCH */
{
  if (Dem_Iumpr_IsEnabled() == TRUE)
  {
    Dem_Iumpr_CycleCounter_ResetIgnitionCycleCounter();

    if (Dem_Iumpr_IsHybridCycleCounterEnabled() == TRUE)
    {
      Dem_Iumpr_CycleCounter_ResetHybridCycleCounter();
    }
  }
}

/* ****************************************************************************
 % Dem_Iumpr_OBDDenominator_InitStatus()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_OBDDenominator_InitStatus(void)                                                                                            /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
{
  Dem_Iumpr_ConditionStatus_ResetReached(DEM_IUMPR_GENERAL_OBDCOND);
  Dem_Iumpr_ConditionStatus_ResetInhibited(DEM_IUMPR_GENERAL_OBDCOND);
}

/* ****************************************************************************
 % Dem_Iumpr_OBDDenominator_InitNv
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_OBDDenominator_InitNv(
  void
)
{
  Dem_Iumpr_OBDDenominator_SetValue(0);
  Dem_Iumpr_OBDDenominator_InitStatus();
}

/* ****************************************************************************
 % Dem_Iumpr_OBDDenominator_Increment
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
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Iumpr_OBDDenominator_Increment(
  CONSTP2VAR(boolean, AUTOMATIC, AUTOMATIC)  UpdateNvM
)
{
  Std_ReturnType lReturnValue = E_OK;
  if (Dem_Iumpr_ConditionStatus_TestInhibited(DEM_IUMPR_GENERAL_OBDCOND) == FALSE)
  {
    if (Dem_Iumpr_ConditionStatus_TestReached(DEM_IUMPR_GENERAL_OBDCOND) == FALSE)
    {
      /* general conditions fulfilled and denominator not yet incremented in this DCY */
      Dem_Iumpr_ConditionStatus_SetReached(DEM_IUMPR_GENERAL_OBDCOND);
      *UpdateNvM = TRUE;                                                                                                         /* SBSW_DEM_POINTER_WRITE_ARGUMENT */

      /* --> no overrun handling; value shall rollover and increment to zero  [CCR1968.2 (g)(5.2.1)(E)] */
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
      Dem_Iumpr_OBDDenominator_SetValue(Dem_Iumpr_OBDDenominator_GetValue() + 1u);
#endif
    }
  }
  else
  {
    lReturnValue = E_NOT_OK;
  }
  return lReturnValue;
}


/* ****************************************************************************
 % Dem_Iumpr_OBDDenominator_Inhibit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_OBDDenominator_Inhibit(void)
{
  (void)Dem_Iumpr_ConditionStatus_SetInhibited(DEM_IUMPR_GENERAL_OBDCOND);
  /* set incremented flag to prevent, that general denominator is incremented in this DCY */
  Dem_Iumpr_ConditionStatus_SetReached(DEM_IUMPR_GENERAL_OBDCOND);
}

/* ****************************************************************************
 % Dem_Iumpr_ConditionStatus_InitStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_ConditionStatus_InitStatus(
  Dem_IumprDenomCondIdType ConditionId
)
{
  switch (ConditionId)
  {
    case DEM_IUMPR_GENERAL_INDIVIDUAL_DENOMINATOR:
      Dem_Iumpr_ConditionStatus_ResetReached(DEM_IUMPR_GENERAL_INDIVIDUAL_DENOMINATOR);
      Dem_Iumpr_ConditionStatus_ResetInhibited(DEM_IUMPR_GENERAL_INDIVIDUAL_DENOMINATOR);
      break;
    case DEM_IUMPR_DEN_COND_COLDSTART:
      Dem_Iumpr_ConditionStatus_ResetReached(DEM_IUMPR_DEN_COND_COLDSTART);
      break;
    case DEM_IUMPR_DEN_COND_EVAP:
      Dem_Iumpr_ConditionStatus_ResetReached(DEM_IUMPR_DEN_COND_EVAP);
      break;
    case DEM_IUMPR_DEN_COND_500MI:
      Dem_Iumpr_ConditionStatus_ResetReached(DEM_IUMPR_DEN_COND_500MI);
      break;
    case DEM_IUMPR_DEN_COND_INDEPENDENT:
      Dem_Iumpr_ConditionStatus_ResetReached(DEM_IUMPR_DEN_COND_INDEPENDENT);
      break;
    default:
      /* MISRA Case */
      break;
  }
}

/* ****************************************************************************
 % Dem_Iumpr_RestartDcy
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
 *   - Mark the NvM IUMPR block state as 'DIRTY'
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_RestartDcy(void)                                                                                                       /* PRQA S 3219 */ /* MD_DEM_14.1_CONFIGURATION_SWITCH */
{
  Dem_Cfg_ObdRatioIdIterType    lRatioIter;
  Dem_RatioIdIndexType          lRatioIndex;

  /* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
  Dem_EnterCritical_DiagMonitor();


  /* Process DCY start for each Ratio */
  for (Dem_Iumpr_RatioIter_Init(&lRatioIter);                                                                                    /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_Iumpr_RatioIter_Exists(&lRatioIter) == TRUE;                                                                             /* PRQA S 2994 */ /* MD_DEM_2994 */ /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_Iumpr_RatioIter_Next(&lRatioIter))                                                                                       /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    lRatioIndex = Dem_Iumpr_RatioIter_GetIdx(&lRatioIter);                                                                       /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_Iumpr_Ratio_OpCycleStart(lRatioIndex);
  }

  /* reset general individual denominator and general OBD denominator status bits to the following setting:
  * - general denominator not incremented
  * - general conditions not inhibited
  * - general denominator increase not inhibited
  * - general conditions not fulfilled
  */
  Dem_Iumpr_OBDDenominator_InitStatus();
  Dem_Iumpr_ConditionStatus_InitStatus(DEM_IUMPR_GENERAL_INDIVIDUAL_DENOMINATOR);

  /* reset denominator group states */
  Dem_Iumpr_ConditionStatus_InitStatus(DEM_IUMPR_DEN_COND_COLDSTART);
  Dem_Iumpr_ConditionStatus_InitStatus(DEM_IUMPR_DEN_COND_EVAP);
  Dem_Iumpr_ConditionStatus_InitStatus(DEM_IUMPR_DEN_COND_500MI);
  Dem_Iumpr_ConditionStatus_InitStatus(DEM_IUMPR_DEN_COND_INDEPENDENT);

  /* reset hybrid status to the following setting:
  * - hybrid ignition cycle counter not incremented
  */
  Dem_Iumpr_CycleCounter_InitStatus();

  /* reset Numerators status to the following setting:
  * - Numerators Unlocked
  */
  Dem_Iumpr_Ratio_Numerator_ReleaseLock();

  Dem_LeaveCritical_DiagMonitor();
  /* <<<< -------------------------------- Leave Critical Section: DiagMonitor */

  /* update NvRam blocks */
  Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_IUMPR),
    DEM_NVM_BLOCKSTATE_DIRTY);
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */


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
 * \addtogroup Dem_Iumpr_Public
 * \{
 */

/* ****************************************************************************
 % Dem_Iumpr_InitNv
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_InitNv(
 void
)
{
  if (Dem_Iumpr_IsEnabled() == TRUE)
  {
    Dem_Cfg_ObdRatioIdIterType     lRatioIter;

    /* ----- Implementation ------------------------------------------------ */
    /* initialize general data */

    Dem_Iumpr_OBDDenominator_InitNv();
    Dem_Iumpr_ConditionStatus_InitStatus(DEM_IUMPR_GENERAL_INDIVIDUAL_DENOMINATOR);

    /* initalize denominator group status */
    Dem_Iumpr_ConditionStatus_InitStatus(DEM_IUMPR_DEN_COND_COLDSTART);
    Dem_Iumpr_ConditionStatus_InitStatus(DEM_IUMPR_DEN_COND_EVAP);
    Dem_Iumpr_ConditionStatus_InitStatus(DEM_IUMPR_DEN_COND_500MI);
    Dem_Iumpr_ConditionStatus_InitStatus(DEM_IUMPR_DEN_COND_INDEPENDENT);

    /* unlock numerators */
    Dem_Iumpr_Ratio_Numerator_ReleaseLock();

    /* initalize cycle counter */
    Dem_Iumpr_CycleCounter_InitStatus();

    /* initialize all ratios */
    for (Dem_Iumpr_RatioIter_Init(&lRatioIter);                                                                                        /* SBSW_DEM_CALL_ITERATOR_POINTER */
      Dem_Iumpr_RatioIter_Exists(&lRatioIter) == TRUE;                                                                                 /* SBSW_DEM_CALL_ITERATOR_POINTER */
      Dem_Iumpr_RatioIter_Next(&lRatioIter))                                                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      Dem_Iumpr_Ratio_InitNv(Dem_Iumpr_RatioIter_GetIdx(&lRatioIter));                                                                 /* SBSW_DEM_CALL_ITERATOR_POINTER */
    }
  }
}                                                                                                                                      /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_Iumpr_GetGeneralIumprData
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_GetGeneralIumprData(
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  GeneralDenominator,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  IgnitionCycles,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  IgnitionCyclesHybrid
)
{
  if ( (Dem_Iumpr_IsEnabled() == TRUE)
    && (Dem_Cfg_IsObdSupportedInVariant() == TRUE))
  {
    *GeneralDenominator = Dem_Iumpr_OBDDenominator_GetValue();                                                                   /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    *IgnitionCycles = Dem_Iumpr_CycleCounter_GetValue(Dem_Iumpr_CycleCounter_IgnitionCycleCounter);                              /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    *IgnitionCyclesHybrid = Dem_Iumpr_CycleCounter_GetValue(Dem_Iumpr_CycleCounter_IgnitionHybridCycleCounter);                  /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  }
}

/* ****************************************************************************
 % Dem_Iumpr_SetDenominatorCondition
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
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Iumpr_SetDenominatorCondition(
Dem_IumprDenomCondIdType ConditionId,                                                                                            /* PRQA S 1330 */ /* MD_DEM_8.3_rte */
Dem_IumprDenomCondStatusType ConditionStatus
)
{
  /* ----- Implementation ------------------------------------------------ */
  Std_ReturnType lReturnValue;
  if (Dem_Cfg_IsObdSupportedInVariant() == TRUE)
  {
    if (ConditionId == DEM_IUMPR_GENERAL_DENOMINATOR)
    {
      Std_ReturnType lOBDCONDReturnValue;
      Std_ReturnType lDenominatorReturnValue;
      /* --- General OBD Denominator Forwarding --- */
      lOBDCONDReturnValue = Dem_Iumpr_SetOBDDenominatorCondition(ConditionStatus);
      /* --- General Individual Denominator Forwarding --- */
      lDenominatorReturnValue = Dem_Iumpr_SetDenominatorConditionStatus(DEM_IUMPR_GENERAL_INDIVIDUAL_DENOMINATOR, ConditionStatus);
      

      if ((lOBDCONDReturnValue == E_OK) && (lDenominatorReturnValue == E_OK))
      {
        lReturnValue = E_OK;
      }
      else
      {
        lReturnValue = E_NOT_OK;
      }
    }
    else if (ConditionId == DEM_IUMPR_GENERAL_OBDCOND)
    {
      /* --- General OBD Condition Handling --- */
      lReturnValue = Dem_Iumpr_SetOBDDenominatorCondition(ConditionStatus);
    }
    else if ((ConditionId == DEM_IUMPR_GENERAL_INDIVIDUAL_DENOMINATOR) || (ConditionStatus != DEM_IUMPR_DEN_STATUS_INHIBITED))
    {
      /* --- Monitor Specific Denominator and General Individual Denominator Handling --- */
      lReturnValue = Dem_Iumpr_SetDenominatorConditionStatus(ConditionId, ConditionStatus);
    }
    else
    {
      /* ConditionId != GENERAL and ConditionStatus == INHIBITED */
      lReturnValue = E_NOT_OK;
    }
  }
  else
  {
    lReturnValue = E_NOT_OK;
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6080 */ /* MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_Iumpr_ResetPendingFids
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_ResetPendingFids(void)                                                                                                 /* PRQA S 3219 */ /* MD_DEM_14.1_CONFIGURATION_SWITCH */
{
  if (Dem_Iumpr_IsEnabled() == TRUE)
  {
    Dem_Cfg_ObdRatioIdIterType lRatioIter;
    uint8 lLeaveCSCounter;

    lLeaveCSCounter = 0u;
    /* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
    Dem_EnterCritical_DiagMonitor();

    for (Dem_Iumpr_RatioIter_Init(&lRatioIter);                                                                                  /* SBSW_DEM_CALL_ITERATOR_POINTER */
      Dem_Iumpr_RatioIter_Exists(&lRatioIter) == TRUE;                                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
      Dem_Iumpr_RatioIter_Next(&lRatioIter))                                                                                     /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      Dem_Iumpr_Ratio_ResetFidPending(Dem_Iumpr_RatioIter_GetIdx(&lRatioIter));                                                  /* SBSW_DEM_CALL_ITERATOR_POINTER */

      ++lLeaveCSCounter;
      if (lLeaveCSCounter >= DEM_IUMPR_RESET_PENDING_RATIO)
      {
        Dem_LeaveCritical_DiagMonitor();
        lLeaveCSCounter = 0u;
        Dem_EnterCritical_DiagMonitor();
      }
    }

    Dem_LeaveCritical_DiagMonitor();
    /* <<<< -------------------------------- Leave Critical Section: DiagMonitor */

    Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_IUMPR),
      DEM_NVM_BLOCKSTATE_DIRTYCLEAREDIMMEDIATE);
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_Iumpr_ReportOperationCycleChange
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
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_ReportOperationCycleChange(
  uint8 CycleId,
  uint8 CycleStatus
)
{
  if ( (Dem_Iumpr_IsEnabled() == TRUE)
    && (Dem_Cfg_IsObdSupportedInVariant() == TRUE))
  {
    if (Dem_Cfg_CycleIsObdDcy(CycleId) == TRUE)
    {
      if ((CycleStatus & DEM_OPERATIONCYCLE_CYCLE_STARTED) != 0u)
      {
        /* Process DCY start for IUMPR data elements */
        Dem_Iumpr_RestartDcy();
      }

      if (CycleStatus == DEM_OPERATIONCYCLE_CYCLE_QUALIFIED)
      {
        Dem_Iumpr_ProcessIgnCycleCounterIncrement();
      }
    }
    else
    {
      /* Unrelated Cycle, Misra case */
    }
  }
}

/* ****************************************************************************
 % Dem_Iumpr_IsIgnitionHybrid
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_IsIgnitionHybrid(                                                                                                      /* PRQA S 3219 */ /* MD_DEM_14.1_CONFIGURATION_SWITCH */
CONST(uint8, AUTOMATIC) CycleId                                                                                                  /* PRQA S 3206 */ /* MD_DEM_3206 */
)
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(CycleId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return (boolean)(Dem_Cfg_GetOpCycleTypeOfCycleIdTable(CycleId) == DEM_CFG_OPCYC_IGNITION_HYBRID);
}


/* ****************************************************************************
 % Dem_Iumpr_MainFunction
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
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Iumpr_MainFunction(
void
)
{
  if ((Dem_Iumpr_IsEnabled() == TRUE)
    && (Dem_Cfg_IsObdSupportedInVariant() == TRUE))
  {
    Dem_Cfg_ObdRatioIdIterType    lRatioIter;
    Dem_RatioIdIndexType          lRatioIndex;
    boolean                       lUpdatePending;

    lUpdatePending = Dem_Iumpr_Ratio_TestAndClearAnyUpdatePending();

    if (lUpdatePending == TRUE)
    {
      /* are general conditions available (i.e.: no input faults have been reported in this DCY)? */
      if (Dem_Iumpr_ConditionStatus_TestInhibited(DEM_IUMPR_GENERAL_INDIVIDUAL_DENOMINATOR) == FALSE)
      {
        boolean lUpdateNvM;
        lUpdateNvM = FALSE;

        /* check each ratio */
        for (Dem_Iumpr_RatioIter_Init(&lRatioIter);                                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
          Dem_Iumpr_RatioIter_Exists(&lRatioIter) == TRUE;                                                                         /* SBSW_DEM_CALL_ITERATOR_POINTER */
          Dem_Iumpr_RatioIter_Next(&lRatioIter))                                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
        {
          lRatioIndex = Dem_Iumpr_RatioIter_GetIdx(&lRatioIter);                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
          
          /* process any pending operation on this ratio if needed/allowed */
          if (Dem_Iumpr_Ratio_ProcessUpdate(lRatioIndex) == TRUE)
          {
            lUpdateNvM = TRUE;
          }
        }

        /* --- update NvM --- */
        if (lUpdateNvM == TRUE)
        {
          Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_IUMPR),
            DEM_NVM_BLOCKSTATE_DIRTY);
        }
      }
    }
  }
  /* else: general conditions not yet reached; nothing to do */
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_Iumpr_CalculateObdRatio
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
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Iumpr_CalculateObdRatio(                                                                                                     /* PRQA S 3219 */ /* MD_DEM_14.1_CONFIGURATION_SWITCH */
CONST(Dem_EventIdType, AUTOMATIC) EventId,
CONSTP2VAR(uint16, AUTOMATIC, AUTOMATIC) Numerator,
CONSTP2VAR(uint16, AUTOMATIC, AUTOMATIC) Denominator
)
{
  Dem_RatioIdIndexType  lRatioIndex;
  lRatioIndex = Dem_Event_GetRatioIdx(EventId);

  if ((lRatioIndex != DEM_CFG_RATIOINDEX_INVALID)
    && ((Dem_DTC_IsEventCombinationType2Enabled() == TRUE) || (Dem_Cfg_EventIsCombined(EventId) == FALSE))                       
    )
  {
    Dem_Iumpr_Ratio_GetRatio(lRatioIndex, Numerator, Denominator);                                                               /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }
  else
  {
    *Numerator = 0x00;                                                                                                           /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    *Denominator = 0x00;                                                                                                         /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  }
}


/* ****************************************************************************
 % Dem_Iumpr_ReportRatioFault
 *****************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 *
 *
 *
  */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Iumpr_ReportRatioFault(
  const Dem_EventIdType EventId,
  const Dem_Iumpr_FaultOriginType FaultOrigin
)
{
  Std_ReturnType lReturnValue;
  if (Dem_Cfg_IsObdSupportedInVariant() == TRUE)
  {
    Dem_RatioIdIndexType lRatioIndex;

    lRatioIndex = Dem_Event_GetRatioIdx(EventId);

    /* If Iumpr is disabled, all events have invalid ratio index */
    if ((lRatioIndex != DEM_CFG_RATIOINDEX_INVALID)
     && (Dem_Iumpr_GetRatioReportingType(lRatioIndex) == (uint8)FaultOrigin))
    {
      Dem_Iumpr_Ratio_ReportRatioFault(lRatioIndex, FaultOrigin);
    }
    lReturnValue = E_OK;
  }
  else
  {
    lReturnValue = E_NOT_OK;
  }
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Iumpr_SetRatioAvailability
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Iumpr_SetRatioAvailability(                                                                                                  /* PRQA S 3219 */ /* MD_DEM_14.1_CONFIGURATION_SWITCH */
CONST(Dem_EventIdType, AUTOMATIC) EventId,
CONST(Dem_Iumpr_RatioAvailabilityType, AUTOMATIC) availabiltyCommand
)
{
  Dem_RatioIdIndexType  lRatioIndex;
  lRatioIndex = Dem_Event_GetRatioIdx(EventId);

  if ( (lRatioIndex != DEM_CFG_RATIOINDEX_INVALID)
    && (Dem_Cfg_IsObdSupportedInVariant() == TRUE))
  {
    switch (availabiltyCommand)
    {
      case Dem_Iumpr_ReconnectRatio:
        Dem_Iumpr_Ratio_Reconnect(lRatioIndex);
      break;

      case Dem_Iumpr_DisconnectRatio:
        Dem_Iumpr_Ratio_Disconnect(lRatioIndex);
      break;
      default:
        /* MISRA CASE */
      break;
    }
  }
}



/* ****************************************************************************
 % Dem_Iumpr_ProcessIgnHybridCycleCounterIncrement
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
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_ProcessIgnHybridCycleCounterIncrement(                                                                                 /* PRQA S 3219 */ /* MD_DEM_14.1_CONFIGURATION_SWITCH */
CONST(Dem_OperationCycleStateType, AUTOMATIC) CycleState
)
{
  /* increment optional ignition cycle counter once per driving cycle */
  if (CycleState == DEM_CYCLE_STATE_START)
  {
    if (Dem_Iumpr_CycleCounter_TestHybridCounterIncremented() == FALSE)
    {
      Dem_FimFid_PendingStateType lFiMPendingState;

      lFiMPendingState = Dem_FimFid_QueryPendingState(Dem_FimFid_GetIgnitionCycle());
      if (lFiMPendingState == Dem_FimFid_PendingState_NotPending)
      {
        Dem_Iumpr_CycleCounter_Increment(Dem_Iumpr_CycleCounter_IgnitionHybridCycleCounter);                                     /* PRQA S 3112 */ /* MD_DEM_14.2_CONFIGURATION_SWITCH */
      }
    }
  }
}


/* ****************************************************************************
 % Dem_Iumpr_LockNumerators
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Iumpr_LockNumerators(
  void
)
{
  Std_ReturnType lReturnValue;
  if (Dem_Cfg_IsObdSupportedInVariant() == TRUE)
  {
    /* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
    Dem_EnterCritical_DiagMonitor();

    Dem_Iumpr_Ratio_Numerator_Lock();

    Dem_LeaveCritical_DiagMonitor();
    /* <<<< -------------------------------- Leave Critical Section: DiagMonitor */

    Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_IUMPR),
      DEM_NVM_BLOCKSTATE_DIRTY);

    lReturnValue = E_OK;
  }
  else
  {
    lReturnValue = E_NOT_OK;
  }
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Iumpr_LockRatioDenominator
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Iumpr_LockRatioDenominator(
  Dem_RatioIdType RatioID
  )
{
  Std_ReturnType lReturnValue;
  if (Dem_Cfg_IsObdSupportedInVariant() == TRUE)
  {
    Dem_RatioIdIndexType  lRatioIndex;

    /* ----- Implementation ---------------------------------------------- */

    lRatioIndex = Dem_Event_GetRatioIdx(RatioID);
    /* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
    Dem_EnterCritical_DiagMonitor();

    /* set locked state */
    Dem_Iumpr_Ratio_Denominator_Lock(lRatioIndex);

    Dem_LeaveCritical_DiagMonitor();
    /* <<<< -------------------------------- Leave Critical Section: DiagMonitor */

    lReturnValue = E_OK;
  }
  else
  {
    lReturnValue = E_NOT_OK;
  }
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Iumpr_ReleaseRatioDenominator
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
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Iumpr_ReleaseRatioDenominator(
Dem_RatioIdType RatioID
)
{
  Std_ReturnType lReturnValue;
  if (Dem_Cfg_IsObdSupportedInVariant() == TRUE)
  {
    Dem_RatioIdIndexType lRatioIndex;
    boolean lDenominatorAlreadyIncremented;

    lRatioIndex = Dem_Event_GetRatioIdx(RatioID);
    /* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
    Dem_EnterCritical_DiagMonitor();
                                                                                                                                                                                                                                                               
    /* clear locked state */                                                                                                       
    lDenominatorAlreadyIncremented = Dem_Iumpr_Ratio_Denominator_Release(lRatioIndex);
                                                                                                                                 
    Dem_LeaveCritical_DiagMonitor();
    /* <<<< -------------------------------- Leave Critical Section: DiagMonitor */                                                
                                                                                                                                 
    if (lDenominatorAlreadyIncremented == FALSE)
    {                                                                                                                              
      /* conditions for increment seem to be fulfilled; set pending flag and increment on task level */                            
      Dem_Iumpr_Ratio_QueueUpdate(lRatioIndex, TRUE);                                                                               
      Dem_Scheduler_EnableTaskOnce(Dem_Scheduler_Task_IUMPR);                                                                      
    }                                                                                                                              
                                                                                                                                 
    lReturnValue = E_OK;
  }
  else
  {
    lReturnValue = E_NOT_OK;
  }
  return lReturnValue;                                                                                                           
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */


/* ****************************************************************************
 % Dem_Iumpr_Filter_SetFilter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Iumpr_Filter_SetFilter(
Dem_IumprReadinessGroupType IumprReadinessGroup,
Dem_DTCOriginType DTCOrigin
)
{
  Std_ReturnType lReturnValue;
  if (Dem_Cfg_IsObdSupportedInVariant() == TRUE)
  {
    uint8 memoryId;

    Dem_Iumpr_FilterInfo.ReadinessGroup = IumprReadinessGroup;
    Dem_Iumpr_FilterInfo.CurrentEvent = DEM_EVENT_INVALID;

    memoryId = Dem_Client_ClientAccess_MemoryIdFromOrigin(DTCOrigin);

    if ((memoryId == DEM_CFG_MEMORYID_PRIMARY) || (memoryId == DEM_CFG_MEMORYID_SECONDARY))
    {
      Dem_Iumpr_FilterInfo.FirstEvent = Dem_Memory_GetFirstEvent(memoryId);
      Dem_Iumpr_FilterInfo.LastEvent = Dem_Memory_GetLastEvent(memoryId);
      lReturnValue = E_OK;
    }
    else
    {
      /* not supported memory location for IUMPR filtering */
      lReturnValue = E_NOT_OK;
    }
  }
  else
  {
    lReturnValue = E_NOT_OK;
  }
  return lReturnValue;
}


/* ****************************************************************************
 % Dem_Iumpr_Init
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Init(
void
)
{
  if ( (Dem_Iumpr_IsEnabled() == TRUE)
    && (Dem_Cfg_IsObdSupportedInVariant() == TRUE))
  {
    Dem_Iumpr_FilterInfo.FirstEvent = DEM_EVENT_INVALID;
    Dem_Iumpr_Ratio_SetAnyUpdatePending();
  }
}

/* ****************************************************************************
 % Dem_Iumpr_Filter_GetFirstEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Iumpr_Filter_GetFirstEvent(
void
)
{
  return Dem_Iumpr_FilterInfo.FirstEvent;
}

/* ****************************************************************************
 % Dem_Iumpr_Filter_GetCurrentEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Iumpr_Filter_GetCurrentEvent(
void
)
{
  return Dem_Iumpr_FilterInfo.CurrentEvent;
}

/* ****************************************************************************
 % Dem_Iumpr_Filter_GetCount
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
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Iumpr_Filter_GetCount(
P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  NumberOfFilteredRatios                                                                  /* PRQA S 1330 */ /* MD_DEM_8.3_rte */
)
{
  Std_ReturnType lReturnValue;
  Dem_EventIdType lEventId;

  lReturnValue = E_NOT_OK;

  lEventId = Dem_Iumpr_FilterInfo.FirstEvent;
  if (lEventId != DEM_EVENT_INVALID)
  {
    *NumberOfFilteredRatios = 0u;                                                                                                 /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    for (lEventId = Dem_Iumpr_FilterInfo.FirstEvent;
      lEventId <= Dem_Iumpr_FilterInfo.LastEvent;
      ++lEventId)
    {
      Dem_RatioIdIndexType  lRatioIndex;
      lRatioIndex = Dem_Event_GetRatioIdx(lEventId);

      /* Skip suppressed or deactivated events. RatioId == EventId */
      if ((lRatioIndex != DEM_CFG_RATIOINDEX_INVALID)                                                                            /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
        && (Dem_Event_TestSuppressionOnEventRetrieval(lEventId) == FALSE)                                                        /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
        )
      {
        /* either only a specific ratio group is selected or all groups are selected */
        if ((Dem_Iumpr_FilterInfo.ReadinessGroup == Dem_Iumpr_Ratio_GetReadinessGroupType(lRatioIndex))
          || (Dem_Iumpr_FilterInfo.ReadinessGroup == DEM_IUMPR_ALLGROUPS))
        {
          ++(*NumberOfFilteredRatios);                                                                                           /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
        }
      }
    }
    lReturnValue = E_OK;
  }
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Iumpr_Filter_GetNext
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
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Iumpr_Filter_GetNext(
P2VAR(uint32, AUTOMATIC, DEM_APPL_DATA)  UdsDtcNumber,
P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  ObdDtcNumber,
P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  Denominator,
P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  Numerator
)
{
  Std_ReturnType lReturnValue;
  Dem_EventIdType lEventId;

  lReturnValue = E_NOT_OK;

  lEventId = Dem_Iumpr_FilterInfo.FirstEvent;
  if (lEventId != DEM_EVENT_INVALID)
  {
    lEventId = Dem_Iumpr_FilterInfo.CurrentEvent;

    if (Dem_Iumpr_FilterInfo.CurrentEvent == DEM_EVENT_INVALID)
    { /* Initial call after set filter, set current event to first event */
      lEventId = Dem_Iumpr_FilterInfo.FirstEvent;
    }
    else
    {
      lEventId += 1u; /* add 1 for the next possible element */
    }


    for (; lEventId <= Dem_Iumpr_FilterInfo.LastEvent; ++lEventId)
    {
      Dem_RatioIdIndexType  lRatioIndex;

      lRatioIndex = Dem_Event_GetRatioIdx(lEventId);

      /* Skip suppressed or deactivated events. RatioId == EventId */
      if ((lRatioIndex != DEM_CFG_RATIOINDEX_INVALID)                                                                            /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
        && (Dem_Event_TestSuppressionOnEventRetrieval(lEventId) == FALSE))                                                       /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
      {
        /* either only a specific ratio group is selected or all groups are selected */
        if ((Dem_Iumpr_FilterInfo.ReadinessGroup == Dem_Iumpr_Ratio_GetReadinessGroupType(lRatioIndex))
          || (Dem_Iumpr_FilterInfo.ReadinessGroup == DEM_IUMPR_ALLGROUPS))
        {
          *UdsDtcNumber = Dem_Cfg_EventUdsDtc(lEventId);                                                                         /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
          *ObdDtcNumber = Dem_Cfg_EventObdDtc(lEventId);                                                                         /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
          Dem_Iumpr_Ratio_GetRatio(lRatioIndex, Numerator, Denominator);                                                         /* SBSW_DEM_POINTER_WRITE_ARGUMENT */

          lReturnValue = E_OK;
          break;
        }
      }
    }

    if (lEventId <= Dem_Iumpr_FilterInfo.LastEvent)
    {
      Dem_Iumpr_FilterInfo.CurrentEvent = lEventId;
    }
  }
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Iumpr_Filter_GetCurrent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Iumpr_Filter_GetCurrent(
P2VAR(uint32, AUTOMATIC, DEM_APPL_DATA)  UdsDtcNumber,
P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  ObdDtcNumber,
P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  Denominator,
P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  Numerator
)
{
  Std_ReturnType lReturnValue;
  Dem_EventIdType lEventId;

  lReturnValue = E_NOT_OK;

  lEventId = Dem_Iumpr_FilterInfo.CurrentEvent;
  if (lEventId != DEM_EVENT_INVALID)
  {
    Dem_RatioIdIndexType  lRatioIndex;

    lRatioIndex = Dem_Event_GetRatioIdx(lEventId);

    /* Exclude suppressed or deactivated events. RatioId == EventId */
    if ((lRatioIndex != DEM_CFG_RATIOINDEX_INVALID)                                                                              /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
      && (Dem_Event_TestSuppressionOnEventRetrieval(lEventId) == FALSE)                                                          /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
      )
    {
      *UdsDtcNumber = Dem_Cfg_EventUdsDtc(lEventId);                                                                             /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      *ObdDtcNumber = Dem_Cfg_EventObdDtc(lEventId);                                                                             /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      Dem_Iumpr_Ratio_GetRatio(lRatioIndex, Numerator, Denominator);                                                                         /* SBSW_DEM_POINTER_WRITE_ARGUMENT */

      lReturnValue = E_OK;
    }
  }
  return lReturnValue;
}



/* ****************************************************************************
 % Dem_Iumpr_GetRatioReportingType
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Iumpr_GetRatioReportingType(
CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
)
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(RatioIndex)                                                                                   /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
  return Dem_Cfg_GetRatioIdTypeOfRatioIdTable(RatioIndex);
#else
    return (uint8)DEM_RATIO_REPORTINGTYPE_INVALID;
#endif
}

/* ****************************************************************************
 % Dem_Iumpr_GetDenGroupOfRatio
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Iumpr_GetDenGroupOfRatio(
CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex                                                                                            /* PRQA S 3206, 3219 */ /* MD_DEM_3206, MD_DEM_14.1_ACCESSOR */
)
{
  return Dem_Iumpr_Ratio_Denominator_GetDenominatorGroup(RatioIndex);
}

/* ****************************************************************************
 % Dem_Iumpr_InitCycleCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_InitCycleCounter(                                                                                                      /* PRQA S 3219 */ /* MD_DEM_14.1_CONFIGURATION_SWITCH */
  void
)
{
  Dem_Iumpr_CycleCounter_InitMemory();
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ********************************************************************************************************************
 *  FILE SPECIFIC MISRA VIOLATIONS
 *********************************************************************************************************************/
/* PRQA L:DEM_IUMPR_IMPL */

#endif /* DEM_IUMPR_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Iumpr_Implementation.h
 *********************************************************************************************************************/
