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
/*! \addtogroup Dem_Iumpr_RatioIF
 *  \{
 *  \file       Dem_RatioIF_Implementation.h
 *  \brief      IUMPR RatioIF subcomponent.
 *  \details    Implementation of Ratio subcomponent which provides functionality to manipulate IUMPR ratios for the 
 *              Dem_Iumpr subcomponent.
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_RATIOIF_IMPLEMENTATION_H)
#define DEM_RATIOIF_IMPLEMENTATION_H

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
#include "Dem_RatioIF_Interface.h"

/* Includes to access public functions belonging to other (top level)/ (logical)/- units to be used by this Unit */
/* ------------------------------------------------------------------------- */
#include "Dem_Infrastructure_Interface.h"
#include "Dem_Denominator_Interface.h"
#include "Dem_FimFid_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

  /*! Filename declaration */
#define DEM_RATIO_IMPLEMENTATION_FILENAME "Dem_Ratio_Implementation.h"

 /* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/


#define DEM_START_SEC_VAR_NOINIT_8BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

 /*! Flag indicating if any Ratio needs to be processed */
DEM_LOCAL VAR(boolean, DEM_VAR_NOINIT)  Dem_Iumpr_Ratio_AnyUpdatePending;

#define DEM_STOP_SEC_VAR_NOINIT_8BIT
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
 * \defgroup Dem_Iumpr_Ratio_PrivateProperties Private Properties
 * \{
 */

 /* ****************************************************************************
 * Dem_Iumpr_Ratio_Numerator_SetValue
 *****************************************************************************/
 /*!
 * \brief         Set the numerator of the ratio
 *
 * \details       Set the numerator of the ratio
 *
 * \param[in]     RatioIndex
 *                Unique handle of the ratio
 * \param[in]     Value
 *                New numerator
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different RatioIndex
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_Numerator_SetValue(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex,
  CONST(uint16, AUTOMATIC) Value
  );

/* ****************************************************************************
 * Dem_Iumpr_Ratio_Numerator_GetValue
 *****************************************************************************/
/*!
 * \brief         Get numerator value
 *
 * \details       Get numerator value
 *
 * \param[in]     RatioIndex
 *                Unique handle of the ratio
 *
 * \return        Numerator value
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Iumpr_Ratio_Numerator_GetValue(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  );

/* ****************************************************************************
 * Dem_Iumpr_Ratio_Numerator_ResetIncremented
 *****************************************************************************/
/*!
 * \brief         Reset numerator incremented state of a ratio
 *
 * \details       Reset numerator incremented state of a ratio
 *
 * \param[in]     RatioIndex
 *                Unique handle of the ratio
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_Numerator_ResetIncremented(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  );


/* ****************************************************************************
 * Dem_Iumpr_Ratio_Numerator_SetIncremented
 *****************************************************************************/
/*!
 * \brief         Set numerator incremented state of a ratio
 *
 * \details       Set numerator incremented state of a ratio
 *
 * \param[in]     RatioIndex
 *                Unique handle of the ratio
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_Numerator_SetIncremented(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  );

/* ****************************************************************************
 * Dem_Iumpr_Ratio_Numerator_TestIncremented
 *****************************************************************************/
/*!
 * \brief         Test numerator incremented state of a ratio
 *
 * \details       Test numerator incremented state of a ratio
 *
 * \param[in]     RatioIndex
 *                Unique handle of the ratio
 *
 * \return        TRUE
 *                Numerators are incremented for this operation cycle
 * \return        FALSE
 *                Numerators are not incremented for this operation cycle
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_Ratio_Numerator_TestIncremented(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  );

/* ****************************************************************************
 * Dem_Iumpr_Ratio_Numerator_TestFaultDetect
 *****************************************************************************/
/*!
 * \brief         Test fault detection completed state of a ratio
 *
 * \details       Test fault detection completed state of a ratio
 *
 * \param[in]     RatioIndex
 *                Unique handle of the ratio
 *
 * \return        TRUE
 *                Fault detected for the ratio
 * \return        FALSE
 *                No fault detected for the ratio
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_Ratio_Numerator_TestFaultDetect(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  );

/* ****************************************************************************
 * Dem_Iumpr_Ratio_Numerator_ResetFaultDetect
 *****************************************************************************/
/*!
 * \brief         Reset fault detection completed state of a ratio
 *
 * \details       Reset fault detection completed state of a ratio
 *
 * \param[in]     RatioIndex
 *                Unique handle of the ratio
 *
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_Numerator_ResetFaultDetect(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  );

/* ****************************************************************************
 * Dem_Iumpr_Ratio_Numerator_TestLock
 *****************************************************************************/
/*!
 * \brief         Test numerators locked state in global iumpr state
 *
 * \details       Test numerators locked state in global iumpr state
 *
 * \param[in]     Param
 *                Desc
 *
 * \return        TRUE
 *                Numerators are currently locked
 * \return        FALSE
 *                Numerators are currently unlocked
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_Ratio_Numerator_TestLock(
  void
  );

/* ****************************************************************************
 * Dem_Iumpr_Ratio_Numerator_Increment
 *****************************************************************************/
/*!
 * \brief         Set numerator incremented state of a ratio
 *
 * \details       Set numerator incremented state of a ratio
 *
 * \param[in]     Param
 *                Desc
 *
 * \return        E_OK
 *                Condition
 * \return        E_NOT_OK
 *                Condition
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different RatioIndex
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_Ratio_Numerator_Increment(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  );

/* ****************************************************************************
 * Dem_Iumpr_Ratio_TestFidPending
 *****************************************************************************/
/*!
 * \brief         Test if the ratio is blocked by pending FiD state
 *
 * \details       Test if the ratio is blocked by pending FiD state
 *
 * \param[in]     RatioIndex
 *                Unique handle of the ratio
 *
 * \return        TRUE
 *                At least one FID of the ratio is pending
 * \return        FALSE
 *                No FID of the ratio is pending
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_Ratio_TestFidPending(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  );

/* ****************************************************************************
 * Dem_Iumpr_Ratio_SetFidPending
 *****************************************************************************/
/*!
 * \brief         Set the ratio as blocked by a FiD
 *
 * \details       Set the ratio as blocked by a FiD
 *
 * \param[in]     RatioIndex
 *                Unique handle of the ratio
 *
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different RatioIndex
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_SetFidPending(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  );

/* ****************************************************************************
 * Dem_Iumpr_Ratio_TestDisconnect
 *****************************************************************************/
/*!
 * \brief         Test ratio disconnected state of a ratio
 *
 * \details       Test ratio disconnected state of a ratio
 *
 * \param[in]     RatioIndex
 *                Unique handle of the ratio
 *
 * \return        TRUE
 *                Ratio is available
 * \return        FALSE
 *                Ratio is unavailable
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_Ratio_TestDisconnect(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  );

/* ****************************************************************************
 * Dem_Iumpr_Ratio_IsUpdatePending
 *****************************************************************************/
/*!
 * \brief         Get the update state of the ratio
 *
 * \details       Get the update state of the ratio for Iumpr queue processing.
 *                An update state of TRUE, means that an unprocessed change has
 *                occurred to either the numerator or denominator of the ratio.
 *                Which has to be processed in the next Dem main function.
 *                Do not mistake it with Fim Fid pending. Both are completly
 *                independent of each other.
 *
 * \param[in]     RatioIndex
 *                Unique handle of the ratio
 *
 * \return        The update state
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_Ratio_IsUpdatePending(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  );

/* ****************************************************************************
 * Dem_Iumpr_Ratio_GetCount
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
Dem_Iumpr_Ratio_GetCount(
  void
  );

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE PROPERTIES DEFINITIONS
 *********************************************************************************************************************/

 /* ****************************************************************************
 % Dem_Iumpr_Ratio_Numerator_SetValue
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_Numerator_SetValue(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex,
  CONST(uint16, AUTOMATIC) Value
  )
{
  if ((Dem_Error_isDevRunTimeChecksEnabled() == TRUE)
    && (RatioIndex >= Dem_Iumpr_Ratio_GetCount()))                                                                                     
  {
    Dem_Error_RunTimeCheckFailed(DEM_RATIO_IMPLEMENTATION_FILENAME, __LINE__);                                                   /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
  {
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
    Dem_Cfg_ObdIumprData.Numerator[RatioIndex] = Value;                                                                          /* SBSW_DEM_ARRAY_WRITE_OBDIUMPRDATA_NUMERATOR */
#else
    DEM_IGNORE_UNUSED_CONST_ARGUMENT(Value)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
  }
}

/* ****************************************************************************
 % Dem_Iumpr_Ratio_Numerator_GetValue
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Iumpr_Ratio_Numerator_GetValue(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  )
{
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
  return Dem_Cfg_ObdIumprData.Numerator[RatioIndex];                                                                             /* PRQA S 2842 */ /* MD_DEM_Dir4.1_ReadOperation */
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(RatioIndex)                                                                                   /* PRQA S 3112 */ /* MD_DEM_14.2 */
    return (uint16)0;
#endif
}

/* ****************************************************************************
 % Dem_Iumpr_Ratio_Numerator_SetIncremented
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_Numerator_SetIncremented(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  )
{
  Dem_Iumpr_Ratio_SetRatioStatusUtil(RatioIndex, (Dem_Iumpr_Ratio_GetRatioStatusUtil(RatioIndex) | DEM_RATIO_NUM_INCREMENTED));
}

/* ****************************************************************************
 % Dem_Iumpr_Ratio_Numerator_ResetIncremented
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_Numerator_ResetIncremented(                                                                                      /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  )
{
  Dem_Iumpr_Ratio_SetRatioStatusUtil(RatioIndex, (Dem_Iumpr_Ratio_GetRatioStatusUtil(RatioIndex) & DEM_RATIO_NUM_INCREMENTED_MASK));
}

/* ****************************************************************************
 % Dem_Iumpr_Ratio_Numerator_TestIncremented
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_Ratio_Numerator_TestIncremented(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  )
{
  return ((Dem_Iumpr_Ratio_GetRatioStatusUtil(RatioIndex) & DEM_RATIO_NUM_INCREMENTED) != 0u);
}

/* ****************************************************************************
 % Dem_Iumpr_Ratio_Numerator_TestFaultDetect
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_Ratio_Numerator_TestFaultDetect(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  )
{
  return ((Dem_Iumpr_Ratio_GetRatioStatusUtil(RatioIndex)& DEM_RATIO_NUM_FAULTDETECT) != 0u);
}

/* ****************************************************************************
 % Dem_Iumpr_Ratio_Numerator_ResetFaultDetect
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_Numerator_ResetFaultDetect(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  )
{
  Dem_Iumpr_Ratio_SetRatioStatusUtil(RatioIndex, (Dem_Iumpr_Ratio_GetRatioStatusUtil(RatioIndex) & DEM_RATIO_NUM_FAULTDETECT_MASK));
}

/* ****************************************************************************
 % Dem_Iumpr_Ratio_Numerator_TestLock
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_Ratio_Numerator_TestLock(
  void
  )
{
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
  return (((Dem_Cfg_ObdIumprData.GlobalNumeratorsLocked)& DEM_RATIO_NUMERATORS_LOCKED) != 0u);
#else
  return FALSE;
#endif
}


/* ****************************************************************************
 % Dem_Iumpr_Ratio_Numerator_Increment
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_Ratio_Numerator_Increment(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  )
{
  boolean lUpdateNvM = FALSE;
  /* is numerator not yet incremented in this DCY and are the numerator conditions fulfilled? */
  if ( (Dem_Iumpr_Ratio_Numerator_TestIncremented(RatioIndex) == FALSE) /* Not yet incremented */
    && (Dem_Iumpr_Ratio_Numerator_TestFaultDetect(RatioIndex) == TRUE)                                                           /* PRQA S 3415 */ /* MD_DEM_13.5_cf */            
    && (Dem_Iumpr_Ratio_Numerator_TestLock() == FALSE) )                                                                                      
  {
    Dem_Iumpr_Ratio_Numerator_SetValue(RatioIndex, Dem_Iumpr_Ratio_Numerator_GetValue(RatioIndex) + 1u);
    Dem_Iumpr_Ratio_Numerator_SetIncremented(RatioIndex);
    lUpdateNvM = TRUE;
  }

  return lUpdateNvM;
}

/* ****************************************************************************
 % Dem_Iumpr_Ratio_TestFidPending
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_Ratio_TestFidPending(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  )
{
  return ((Dem_Iumpr_Ratio_GetRatioStatusUtil(RatioIndex) & DEM_RATIO_FID_PENDING) != 0u);
}

/* ****************************************************************************
 % Dem_Iumpr_Ratio_SetFidPending
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_SetFidPending(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  )
{
  Dem_Iumpr_Ratio_SetRatioStatusUtil(RatioIndex, (Dem_Iumpr_Ratio_GetRatioStatusUtil(RatioIndex) | DEM_RATIO_FID_PENDING));
}

/* ****************************************************************************
 % Dem_Iumpr_Ratio_TestDisconnect
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_Ratio_TestDisconnect(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  )
{
  return ((Dem_Iumpr_Ratio_GetRatioStatusUtil(RatioIndex) & DEM_RATIO_DISCONNECTED) != 0u);
}

/* ****************************************************************************
 % Dem_Iumpr_Ratio_IsUpdatePending
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_Ratio_IsUpdatePending(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(RatioIndex)                                                                                   /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
    return (boolean)Dem_Cfg_IsObdIumprUpdatePending(RatioIndex);
#else
    return FALSE;
#endif
}

/* ****************************************************************************
 % Dem_Iumpr_Ratio_GetCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Iumpr_Ratio_GetCount(
  void
  )
{
  return DEM_G_NUMBER_OF_RATIO_IDS;
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
 * \addtogroup Dem_Iumpr_Ratio_PublicProperties
 * \{
 */

/* ****************************************************************************
 % Dem_Iumpr_Ratio_Numerator_Lock
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_Numerator_Lock(
  void
  )
{
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
  Dem_Cfg_ObdIumprData.GlobalNumeratorsLocked = ((uint8)((Dem_Cfg_ObdIumprData.GlobalNumeratorsLocked) | DEM_RATIO_NUMERATORS_LOCKED));
#endif
}

/* ****************************************************************************
 % Dem_Iumpr_Ratio_Numerator_ReleaseLock
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_Numerator_ReleaseLock(
  void
  )
{
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
  Dem_Cfg_ObdIumprData.GlobalNumeratorsLocked = ((uint8)((Dem_Cfg_ObdIumprData.GlobalNumeratorsLocked) & DEM_RATIO_NUMERATORS_LOCKED_MASK));
#endif
}

/* ****************************************************************************
 % Dem_Iumpr_Ratio_ResetFidPending
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_ResetFidPending(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  )
{
  Dem_Iumpr_Ratio_SetRatioStatusUtil(RatioIndex, (Dem_Iumpr_Ratio_GetRatioStatusUtil(RatioIndex) & DEM_RATIO_FID_PENDING_MASK));
}

/* ****************************************************************************
 % Dem_Iumpr_Ratio_Disconnect
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_Disconnect(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  )
{
  Dem_Iumpr_Ratio_SetRatioStatusUtil(RatioIndex, ((Dem_Iumpr_Ratio_GetRatioStatusUtil(RatioIndex) | DEM_RATIO_DISCONNECTED)));
}

/* ****************************************************************************
 % Dem_Iumpr_Ratio_Reconnect
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_Reconnect(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  )
{
  Dem_Iumpr_Ratio_SetRatioStatusUtil(RatioIndex, ((Dem_Iumpr_Ratio_GetRatioStatusUtil(RatioIndex) & DEM_RATIO_DISCONNECTED_MASK)));
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
 * \defgroup Dem_Iumpr_Ratio_Private Private Methods
 * \{
 */

/* ****************************************************************************
 * Dem_Iumpr_Ratio_TestProcessingAllowed
 *****************************************************************************/
/*!
 * \brief         Test if any assigned Fim Fid is pending
 *
 * \details       Test if any assigned Fim Fid is pending
 *
 * \param[in]     RatioIndex
 *                Unique handle of the Ratio
 *
 * \return        FALSE
 *                At least one Fim Fid is pending
 *                TRUE
 *                No Fim Fid is pending
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_Ratio_TestProcessingAllowed(
  Dem_RatioIdIndexType RatioIndex
  );



/* ****************************************************************************
 * Dem_Iumpr_Ratio_Numerator_HandleOverflow
 *****************************************************************************/
/*!
 * \brief         Apply overflow handling operation, to the ratio numerator
 *
 * \details       Apply overflow handling operation, to the ratio numerator
 *
 * \param[in]     RatioIndex
 *                Unique handle of the Ratio
 *
 *
 * \pre           Should only be used with Dem_Iumpr_Ratio_Denominator_HandleOverflow
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different RatioIndex
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_Numerator_HandleOverflow(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  );

/* ****************************************************************************
 * Dem_Iumpr_Ratio_Numerator_InitNv
 *****************************************************************************/
/*!
 * \brief         Initalize numerator status and counter value
 *
 * \details       Initalize numerator status and counter value
  *
 * \param[in]     RatioIndex
 *                Unique handle of the Ratio
 *
 * \pre           Feature IUMPR is supported
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different RatioIndex
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_Numerator_InitNv(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  );

/* ****************************************************************************
 * Dem_Iumpr_Ratio_Numerator_SetFaultDetect
 *****************************************************************************/
/*!
 * \brief         Set fault detection completed state of a ratio
 *
 * \details       Set fault detection completed state of a ratio
 *
 * \param[in]     RatioIndex
 *                Unique handle of the ratio
 *
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_Ratio_Numerator_SetFaultDetect(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  );

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/
/* ****************************************************************************
 % Dem_Iumpr_Ratio_TestProcessingAllowed
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
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_Ratio_TestProcessingAllowed(
  Dem_RatioIdIndexType RatioIndex
  )
{
  boolean lProcessingAllowed;
  lProcessingAllowed = FALSE; /* At least one FID has to be tested and not be pending. */

  if (Dem_Iumpr_Ratio_TestDisconnect(RatioIndex) == FALSE)
  {
    if (Dem_Iumpr_Ratio_TestFidPending(RatioIndex) == FALSE)
    {
      Dem_Cfg_ObdFimFidIterType lFIDIter;
      Dem_FimFid_PendingStateType lFiMPendingState;

      /* until now, the FiM did not report a pending fault for this ratio; check again */
      for (Dem_FimFidIter_Init(RatioIndex, &lFIDIter);                                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
        Dem_FimFidIter_Exists(&lFIDIter) == TRUE;                                                                                /* PRQA S 2994 */ /* MD_DEM_2994 */ /* SBSW_DEM_CALL_ITERATOR_POINTER */
        Dem_FimFidIter_Next(&lFIDIter))                                                                                          /* SBSW_DEM_CALL_ITERATOR_POINTER */
      {
        lFiMPendingState = Dem_FimFid_QueryPendingState(Dem_FimFidIter_Get(&lFIDIter));                                          /* SBSW_DEM_CALL_ITERATOR_POINTER */ /* SBSW_DEM_POINTER_FORWARD_STACK */

        /* if any FID inhibits the ratio, stop checking the FIDs and do not modify the ratio */
        if (lFiMPendingState == Dem_FimFid_PendingState_Pending)
        {
          /* remember this FID status */
          /* Note: no interrupt lock needed; when FID is pending, the other status bits */
          /* become irrelevant as the ratio is blocked at least until the end of this cycle */
          Dem_Iumpr_Ratio_SetFidPending(RatioIndex);
          Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_IUMPR), DEM_NVM_BLOCKSTATE_DIRTY);
          lProcessingAllowed = FALSE;
          break;
        }
        else
        {
          /* No tested FID was pending, but at least one was tested */
          lProcessingAllowed = TRUE;
        }
      }
    }
  }

  return lProcessingAllowed;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_Iumpr_Ratio_Numerator_HandleOverflow
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_Numerator_HandleOverflow(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  )
{
  /* divide by two if max value has been reached   [CCR1968.2 (g)(5.2.1)(C)] */
  Dem_Iumpr_Ratio_Numerator_SetValue(RatioIndex, Dem_Iumpr_Ratio_Numerator_GetValue(RatioIndex) >> 1);
}
/* ****************************************************************************
 % Dem_Iumpr_Ratio_Numerator_InitNv
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
Dem_Iumpr_Ratio_Numerator_InitNv(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  )
{
  Dem_Iumpr_Ratio_Numerator_ResetIncremented(RatioIndex);
  Dem_Iumpr_Ratio_Numerator_ResetFaultDetect(RatioIndex);
  Dem_Iumpr_Ratio_Numerator_SetValue(RatioIndex, 0);
}

/* ****************************************************************************
 % Dem_Iumpr_Ratio_Numerator_SetFaultDetect
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_Ratio_Numerator_SetFaultDetect(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  )
{
  boolean isIncremented;
  /* only trigger increment of numerator if it is not yet incremented */
  if (Dem_Iumpr_Ratio_Numerator_TestIncremented(RatioIndex) == FALSE)
  {
    isIncremented = TRUE;
    Dem_Iumpr_Ratio_SetRatioStatusUtil(RatioIndex, (Dem_Iumpr_Ratio_GetRatioStatusUtil(RatioIndex) | DEM_RATIO_NUM_FAULTDETECT));
  }
  else
  {
    isIncremented = FALSE;
  }
  return isIncremented;
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
 * \addtogroup Dem_Iumpr_Ratio_Public
 * \{
 */

/* ****************************************************************************
 % Dem_Iumpr_Ratio_TestAndClearAnyUpdatePending()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_Ratio_TestAndClearAnyUpdatePending(
  void
)
{
  boolean lReturnValue;

  lReturnValue = Dem_Iumpr_Ratio_AnyUpdatePending;
  Dem_Iumpr_Ratio_AnyUpdatePending = FALSE;

  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Iumpr_Ratio_SetAnyUpdatePending()
 *****************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_SetAnyUpdatePending(
  void
)
{
  Dem_Iumpr_Ratio_AnyUpdatePending = TRUE;
}


/* ****************************************************************************
 % Dem_Iumpr_Ratio_QueueUpdate
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
Dem_Iumpr_Ratio_QueueUpdate(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex,
  CONST(boolean, AUTOMATIC) Value
  )
{
  uint8 lUpdatePendingSize;
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
  lUpdatePendingSize = Dem_Cfg_GetSizeOfObdIumprUpdatePending();
#else
  lUpdatePendingSize = 0u;
#endif

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(RatioIndex)                                                                                   /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(Value)                                                                                        /* PRQA S 3112 */ /* MD_DEM_14.2 */

  if ((Dem_Error_isDevRunTimeChecksEnabled() == TRUE) &&                                                                         
    (RatioIndex >= lUpdatePendingSize))
  {
    Dem_Error_RunTimeCheckFailed(DEM_RATIO_IMPLEMENTATION_FILENAME, __LINE__);                                                   /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
  {
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
    Dem_Cfg_SetObdIumprUpdatePending(RatioIndex, Value);                                                                         /* PRQA S 3112 */ /* MD_DEM_14.2_CONFIGURATION_SWITCH */ /* SBSW_DEM_ARRAY_WRITE_OBDIUMPRRUPDATEPENDING */
    if (Value == TRUE)
    {
      Dem_Iumpr_Ratio_SetAnyUpdatePending();
    }
#endif
  }
}

/* ****************************************************************************
 % Dem_Iumpr_Ratio_GetRatioStatusUtil
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Iumpr_Ratio_GetRatioStatusUtil(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  )
{
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
  return Dem_Cfg_ObdIumprData.Status[RatioIndex];                                                                                /* PRQA S 2842 */ /* MD_DEM_Dir4.1_ReadOperation */
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(RatioIndex)                                                                                   /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return (uint8)0;
#endif
}

/* ****************************************************************************
 % Dem_Iumpr_Ratio_SetRatioStatusUtil
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_SetRatioStatusUtil(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex,
  CONST(uint8, AUTOMATIC) Value
  )
{
  if ((Dem_Error_isDevRunTimeChecksEnabled() == TRUE)
    && (RatioIndex >= Dem_Iumpr_Ratio_GetCount()))                                                                               
  {
    Dem_Error_RunTimeCheckFailed(DEM_RATIO_IMPLEMENTATION_FILENAME, __LINE__);                                                   /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
  {
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
    Dem_Cfg_ObdIumprData.Status[RatioIndex] = Value;                                                                             /* SBSW_DEM_ARRAY_WRITE_OBDIUMPRDATA_STATUS */
#else
    DEM_IGNORE_UNUSED_CONST_ARGUMENT(Value)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
  }
}

/* ****************************************************************************
 % Dem_Iumpr_Ratio_OpCycleStart
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
Dem_Iumpr_Ratio_OpCycleStart(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  )
{
  Dem_Iumpr_Ratio_ResetFidPending(RatioIndex);
  Dem_Iumpr_Ratio_QueueUpdate(RatioIndex, FALSE);     /* reset pending status of this ratio */

  Dem_Iumpr_Ratio_Numerator_ResetIncremented(RatioIndex);
  Dem_Iumpr_Ratio_Numerator_ResetFaultDetect(RatioIndex);
  Dem_Iumpr_Ratio_Denominator_OpCycleStart(RatioIndex);
}                                                                                                                               /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_Iumpr_Ratio_GetReadinessGroupType
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_IumprReadinessGroupType, DEM_CODE)
Dem_Iumpr_Ratio_GetReadinessGroupType(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(RatioIndex)                                                                                   /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
    return (Dem_IumprReadinessGroupType)Dem_Cfg_GetIumprGroupOfRatioIdTable(RatioIndex);
#else
    return (Dem_IumprReadinessGroupType) 0;
#endif
}


/* ****************************************************************************
 % Dem_Iumpr_Ratio_ProcessUpdate
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
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_Ratio_ProcessUpdate(
  Dem_RatioIdIndexType RatioIndex
  )
{
  boolean lUpdateNvM;
  lUpdateNvM = FALSE;

  if (Dem_Iumpr_Ratio_IsUpdatePending(RatioIndex) == TRUE)
  {
    /* reset pending status of this ratio */
    Dem_Iumpr_Ratio_QueueUpdate(RatioIndex, FALSE);
    
    /* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
    Dem_EnterCritical_DiagMonitor();

    if (Dem_Iumpr_Ratio_Denominator_UpdateRatioStatus(RatioIndex) == TRUE)
    {
      lUpdateNvM = TRUE;
    }

    if (Dem_Iumpr_Ratio_TestProcessingAllowed(RatioIndex) == TRUE)
    {

      /* --- Denominator --- */
      if (Dem_Iumpr_Ratio_Denominator_Increment(RatioIndex) == TRUE)
      {
        lUpdateNvM = TRUE;
      }

      /* --- Numerator --- */
      if (Dem_Iumpr_Ratio_Numerator_Increment(RatioIndex) == TRUE)
      {
        lUpdateNvM = TRUE;
      }

      /* --- overflow check --- */
      if ((Dem_Iumpr_Ratio_Numerator_GetValue(RatioIndex) == DEM_RATIO_MAX_VALUE)
        || (Dem_Iumpr_Ratio_Denominator_GetValue(RatioIndex) == DEM_RATIO_MAX_VALUE))                                                        
      {
        /* divide by two if max value has been reached   [CCR1968.2 (g)(5.2.1)(C)] */
        Dem_Iumpr_Ratio_Denominator_HandleOverflow(RatioIndex);
        Dem_Iumpr_Ratio_Numerator_HandleOverflow(RatioIndex);
      }
    }

    Dem_LeaveCritical_DiagMonitor();
    /* <<<< -------------------------------- Leave Critical Section: DiagMonitor */
  }

  return lUpdateNvM;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_Iumpr_Ratio_InitNv
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
Dem_Iumpr_Ratio_InitNv(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  )
{
  /* Init this */
  Dem_Iumpr_Ratio_Reconnect(RatioIndex);
  Dem_Iumpr_Ratio_ResetFidPending(RatioIndex);
  Dem_Iumpr_Ratio_QueueUpdate(RatioIndex, FALSE);     /* reset pending status of this ratio */

  /* Init children */
  Dem_Iumpr_Ratio_Numerator_InitNv(RatioIndex);
  Dem_Iumpr_Ratio_Denominator_InitNv(RatioIndex);
}

/* ****************************************************************************
 % Dem_Iumpr_Ratio_ReportRatioFault
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
Dem_Iumpr_Ratio_ReportRatioFault(
  Dem_RatioIdIndexType RatioIndex,
  Dem_Iumpr_FaultOriginType FaultOrigin
  )
{
  boolean bIncrementNumerator;
  /* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
  Dem_EnterCritical_DiagMonitor();

  /* set fault detect flag */
  bIncrementNumerator = Dem_Iumpr_Ratio_Numerator_SetFaultDetect(RatioIndex);
  if (bIncrementNumerator == TRUE)
  {
    /* set pending flags --> check for increment on task level */
    Dem_Iumpr_Ratio_QueueUpdate(RatioIndex, TRUE);
    /* If fault was reported by API, schedule iumpr task, else iumpr updates are be processed together with event status changes */
    if (FaultOrigin == Dem_Iumpr_FaultOrigin_API)
    {
      Dem_Scheduler_EnableTaskOnce(Dem_Scheduler_Task_IUMPR);
    }
  }
  Dem_LeaveCritical_DiagMonitor();
  /* <<<< -------------------------------- Leave Critical Section: DiagMonitor */
}

/* ****************************************************************************
 % Dem_Iumpr_Ratio_GetRatio
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_GetRatio(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex,
  CONSTP2VAR(uint16, AUTOMATIC, AUTOMATIC) Numerator,
  CONSTP2VAR(uint16, AUTOMATIC, AUTOMATIC) Denominator
  )
{
  *Numerator = Dem_Iumpr_Ratio_Numerator_GetValue(RatioIndex);                                                                               /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  *Denominator = Dem_Iumpr_Ratio_Denominator_GetValue(RatioIndex);                                                                           /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_RATIOIF_IMPLEMENTATION_H */



/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_RatioIF_Implementation.h
 *********************************************************************************************************************/
