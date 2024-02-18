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
/*! \addtogroup Dem_FimFid
 *  \{
 *  \file       Dem_FimFid_Implementation.h
 *  \brief      IUMPR Fim Fid subcomponent.
 *  \details    Provides functionality to access FIM Fid specific information.
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_FIMFID_IMPLEMENTATION_H)
#define DEM_FIMFID_IMPLEMENTATION_H

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
#include "Dem_FimFid_Interface.h"

/* Includes to access public functions belonging to other (top level)/ (logical)/- units to be used by this Unit */
/* ------------------------------------------------------------------------- */
#include "Dem_Infrastructure_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

  /*! Filename declaration */
#define Dem_FimFid_IMPLEMENTATION_FILENAME "Dem_FimFid_Implementation.h"

 /* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \addtogroup Dem_FimFid_Public
 * \{
 */

/* ****************************************************************************
 % Dem_FimFid_GetIgnitionCycle
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_ExtCom_FiMFunctionIdType, DEM_CODE)
Dem_FimFid_GetIgnitionCycle(
  void
  )
{
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
  return Dem_Cfg_GetFimFidIgnCycle(0);
#else
  return (Dem_ExtCom_FiMFunctionIdType)0;
#endif
}

/* ****************************************************************************
 % Dem_FimFid_QueryPendingState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_FimFid_PendingStateType, DEM_CODE)
Dem_FimFid_QueryPendingState(
  CONST(Dem_ExtCom_FiMFunctionIdType, AUTOMATIC) FID
)
{
  boolean lFimFaultPending;
  Std_ReturnType lFiMReturnValue;
  Dem_FimFid_PendingStateType lReturnValue;

  lFiMReturnValue = Dem_ExtCom_FimGetFunctionPendingStatus(FID, &lFimFaultPending);                                              /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  if ((lFiMReturnValue == E_OK) && (lFimFaultPending == FALSE))
  {
    lReturnValue = Dem_FimFid_PendingState_NotPending;
  }
  else
  {
    lReturnValue = Dem_FimFid_PendingState_Pending;
  }

  return lReturnValue;
}

/* ****************************************************************************
 % Dem_FimFidIter_Exists
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_FimFidIter_Exists(
  CONSTP2CONST(Dem_Cfg_ObdFimFidIterType, AUTOMATIC, AUTOMATIC)  IterPtr
  )
{
  return (boolean)(IterPtr->mIdx < IterPtr->mEndIdx);
}

/* ****************************************************************************
 % Dem_FimFidIter_Get
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_ExtCom_FiMFunctionIdType, DEM_CODE)
Dem_FimFidIter_Get(
  CONSTP2CONST(Dem_Cfg_ObdFimFidIterType, AUTOMATIC, AUTOMATIC)  IterPtr                                                           /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
    return (Dem_ExtCom_FiMFunctionIdType)(Dem_Cfg_GetFidSymbolicNameOfFimFid(IterPtr->mIdx));
#else
    return (Dem_ExtCom_FiMFunctionIdType)0;
#endif
}

/* ****************************************************************************
 % Dem_FimFidIter_Init
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_FimFidIter_Init(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex,                                                                                           /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONSTP2VAR(Dem_Cfg_ObdFimFidIterType, AUTOMATIC, AUTOMATIC)  IterPtr
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(RatioIndex)                                                                                   /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
  IterPtr->mIdx = Dem_Cfg_GetFimFidStartIdxOfRatioIdTable(RatioIndex);                                                           /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  IterPtr->mEndIdx = Dem_Cfg_GetFimFidEndIdxOfRatioIdTable(RatioIndex);                                                          /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
#else
  IterPtr->mIdx = 0u;                                                                                                             /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  IterPtr->mEndIdx = 0u;                                                                                                          /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
#endif
}

/* ****************************************************************************
 % Dem_FimFidIter_Next
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_FimFidIter_Next(
  CONSTP2VAR(Dem_Cfg_ObdFimFidIterType, AUTOMATIC, AUTOMATIC)  IterPtr
  )
{
  IterPtr->mIdx += 1u;                                                                                                            /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_FIMFID_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_FimFid_Implementation.h
 *********************************************************************************************************************/
