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
/*! \addtogroup Dem_Communication
 *  \{
 *  \file       Dem_Com_Implementation.h
 *  \brief      Implementation file for the MICROSAR Dem
 *  \details    Implementation of communication subcomponent
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_COM_IMPLEMENTATION_H)
#define DEM_COM_IMPLEMENTATION_H

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
#include "Dem_Com_Interface.h"

/* Includes to access public functions belonging to other (top level)/ (logical)/- units to be used by this Unit */
/* ------------------------------------------------------------------------- */
#include "Dem_Error_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*! Filename declaration */
#define DEM_COM_IMPLEMENTATION_FILENAME "Dem_Com_Implementation.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*!
 * \defgroup Dem_Communication_Private Private Methods
 * \{
 */


/* ****************************************************************************
 * Dem_Com_GetBitfieldWordIndex
 *****************************************************************************/
/*!
 * \brief         Calculate the word index of a bit in a bitfield.
 *
 * \details       Calculate the word index of a bit in the bitfield.
 *
 * \param[in]     BitPosition
 *                Absolute position of the bit
 *
 * \return        Word index of the bit in the bitfield array
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_HandleType, DEM_CODE)
Dem_Com_GetBitfieldWordIndex(
  CONST(Dem_HandleType, AUTOMATIC) BitPosition
  );


/* ****************************************************************************
 * Dem_Com_GetBitfieldBitIndex
 *****************************************************************************/
/*!
 * \brief         Calculate the bit index of a bit in a bitfield.
 *
 * \details       Calculate the bit index of a bit in the bitfield relative to
 *                the word it is stored in.
 *
 * \param[in]     BitPosition
 *                Absolute position of the bit
 *
 * \return        Bit index of the bit in the bitfield word
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Com_GetBitfieldBitIndex(
  CONST(Dem_HandleType, AUTOMATIC) BitPosition
  );


#if (DEM_CFG_SUPPORT_USER_CAS == STD_OFF)
/* ****************************************************************************
 * Dem_Com_DefaultSyncCompareAndSwap
 *****************************************************************************/
/*!
 * \brief         Default implementation of compare and swap.
 *
 * \details       Implementation of CompareAndSwap using a critical section.
 *                This implementation should be exchanged with a version based
 *                on platform specific hardware support.
 *
 * \param[in]     AddressPtr
 *                Pointer to the memory location to compare and swap
 * \param[in]     OldValue
 *                Expected value at the memory location
 * \param[in]     NewValue
 *                New value to write to the memory location
 *
 * \return        TRUE
 *                The value was written successfully
 * \return        FALSE
 *                The value could not be written due to modification
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_USER_CAS == STD_OFF
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Com_DefaultSyncCompareAndSwap(
  volatile CONSTP2VAR(Dem_Com_ProcessorWordType, DEM_VAR_UNCACHED, AUTOMATIC) AddressPtr,
  CONST(Dem_Com_ProcessorWordType, AUTOMATIC) OldValue,
  CONST(Dem_Com_ProcessorWordType, AUTOMATIC) NewValue
  );
#endif


/* ****************************************************************************
 % Dem_Com_GetBitfieldWordIndex
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_HandleType, DEM_CODE)
Dem_Com_GetBitfieldWordIndex(
  CONST(Dem_HandleType, AUTOMATIC) BitPosition
  )
{
  Dem_HandleType lReturnValue;

  lReturnValue = (Dem_HandleType)(BitPosition / DEM_COM_BITS_PER_WORD);

  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Com_GetBitfieldBitIndex
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Com_GetBitfieldBitIndex(
  CONST(Dem_HandleType, AUTOMATIC) BitPosition
  )
{
  uint8 lReturnValue;

  lReturnValue = (uint8)(BitPosition % DEM_COM_BITS_PER_WORD);

  return lReturnValue;
}

#if (DEM_CFG_SUPPORT_USER_CAS == STD_OFF)
/* ****************************************************************************
 % Dem_Com_DefaultSyncCompareAndSwap
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Com_DefaultSyncCompareAndSwap(
 volatile CONSTP2VAR(Dem_Com_ProcessorWordType, DEM_VAR_UNCACHED, AUTOMATIC) AddressPtr,
 CONST(Dem_Com_ProcessorWordType, AUTOMATIC) OldValue,
 CONST(Dem_Com_ProcessorWordType, AUTOMATIC) NewValue
 )
{
  boolean lReturnValue;

/* >>>> -------------------------------- Enter Critical Section: CrossCoreComm */
  Dem_EnterCritical_CrossCoreComm();

  if (*AddressPtr == OldValue)
  {
    *AddressPtr = NewValue;                                                                                                      /* SBSW_DEM_POINTER_WRITE_ARGUMENT */                                                                                           
    lReturnValue = TRUE;
  }
  else
  {
    lReturnValue = FALSE;
  }

  Dem_LeaveCritical_CrossCoreComm();
/* <<<< -------------------------------- Leave Critical Section: CrossCoreComm */

  return lReturnValue;
}
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */


/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \addtogroup Dem_Communication_Public
 * \{
 */

/* ****************************************************************************
 % Dem_Com_SyncCompareAndSwap
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Com_SyncCompareAndSwap(
  volatile CONSTP2VAR(Dem_Com_ProcessorWordType, DEM_VAR_UNCACHED, AUTOMATIC) AddressPtr,
  CONST(Dem_Com_ProcessorWordType, AUTOMATIC) OldValue,
  CONST(Dem_Com_ProcessorWordType, AUTOMATIC) NewValue
  )
{
#if (DEM_CFG_SUPPORT_USER_CAS == STD_ON)
  return ApplDem_SyncCompareAndSwap(AddressPtr, OldValue, NewValue);                                                             /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
#else
  return Dem_Com_DefaultSyncCompareAndSwap(AddressPtr, OldValue, NewValue);                                                      /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
#endif
}

/* ****************************************************************************
 % Dem_Com_TestBitInBitfield
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Com_TestBitInBitfield(                                                                                                       /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  volatile CONSTP2CONST(Dem_Com_ProcessorWordType, DEM_VAR_UNCACHED, AUTOMATIC) BitfieldPtr,
  CONST(Dem_HandleType, AUTOMATIC) BitfieldSize,
  CONST(Dem_HandleType, AUTOMATIC) BitPosition
  )
{
  Dem_Com_ProcessorWordType lBitMask;
  boolean lIsBitSet;

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(BitfieldSize)                                                                                 /* PRQA S 3112 */ /* MD_DEM_14.2 */

  Dem_Internal_AssertReturnValue(Dem_Com_GetBitfieldWordIndex(BitPosition) < BitfieldSize, DEM_E_INCONSISTENT_STATE, TRUE)

  lBitMask = DEM_BIT(Dem_Com_GetBitfieldBitIndex(BitPosition));
  lIsBitSet = (boolean)((BitfieldPtr[Dem_Com_GetBitfieldWordIndex(BitPosition)] & lBitMask) != 0u);

  return lIsBitSet;
}

/* ****************************************************************************
 % Dem_Com_SyncSetBitInBitfield
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Com_SyncSetBitInBitfield(
  volatile CONSTP2VAR(Dem_Com_ProcessorWordType, DEM_VAR_UNCACHED, AUTOMATIC) BitfieldPtr,
  CONST(Dem_HandleType, AUTOMATIC) BitfieldSize,
  CONST(Dem_HandleType, AUTOMATIC) BitPosition
  )
{
  volatile P2VAR(Dem_Com_ProcessorWordType, DEM_VAR_UNCACHED, AUTOMATIC) lWordPtr;
  Dem_Com_ProcessorWordType lOldValue;
  Dem_Com_ProcessorWordType lNewValue;
  Dem_Com_ProcessorWordType lBitMask;
  Dem_HandleType lWordIndex;

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(BitfieldSize)                                                                                 /* PRQA S 3112 */ /* MD_DEM_14.2 */

  lWordIndex = Dem_Com_GetBitfieldWordIndex(BitPosition);

#if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (lWordIndex >= BitfieldSize)
  {
    Dem_Error_RunTimeCheckFailed(DEM_COM_IMPLEMENTATION_FILENAME, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
#endif
  {
    lWordPtr = &BitfieldPtr[lWordIndex];
    lBitMask = DEM_BIT(Dem_Com_GetBitfieldBitIndex(BitPosition));
    do
    {
      lOldValue = *lWordPtr;
      lNewValue = (lOldValue | lBitMask);
    }
    while (Dem_Com_SyncCompareAndSwap(lWordPtr, lOldValue, lNewValue) == FALSE);                                                 /* SBSW_DEM_CALL_SYNC_COMPARE_AND_SWAP */
  }
}

/* ****************************************************************************
 % Dem_Com_SyncResetBitInBitfield
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Com_SyncResetBitInBitfield(
  volatile CONSTP2VAR(Dem_Com_ProcessorWordType, DEM_VAR_UNCACHED, AUTOMATIC) BitfieldPtr,
  CONST(Dem_HandleType, AUTOMATIC) BitfieldSize,
  CONST(Dem_HandleType, AUTOMATIC) BitPosition
  )
{
  volatile P2VAR(Dem_Com_ProcessorWordType, DEM_VAR_UNCACHED, AUTOMATIC) lWordPtr;
  Dem_Com_ProcessorWordType lOldValue;
  Dem_Com_ProcessorWordType lNewValue;
  Dem_Com_ProcessorWordType lBitMask;
  Dem_HandleType lWordIndex;

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(BitfieldSize)                                                                                 /* PRQA S 3112 */ /* MD_DEM_14.2 */

  lWordIndex = Dem_Com_GetBitfieldWordIndex(BitPosition);

#if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (lWordIndex >= BitfieldSize)
  {
    Dem_Error_RunTimeCheckFailed(DEM_COM_IMPLEMENTATION_FILENAME, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
#endif
  {
    lWordPtr = &BitfieldPtr[lWordIndex];
    lBitMask = (Dem_Com_ProcessorWordType) (~(DEM_BIT(Dem_Com_GetBitfieldBitIndex(BitPosition))));
    do
    {
      lOldValue = *lWordPtr;
      lNewValue = (lOldValue & lBitMask);
    } while (Dem_Com_SyncCompareAndSwap(lWordPtr, lOldValue, lNewValue) == FALSE);                                               /* SBSW_DEM_CALL_SYNC_COMPARE_AND_SWAP */
  }
}

/* ****************************************************************************
 % Dem_Com_SetBitInBitfield
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Com_SetBitInBitfield(                                                                                                        /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  volatile CONSTP2VAR(Dem_Com_ProcessorWordType, DEM_VAR_UNCACHED, AUTOMATIC) BitfieldPtr,
  CONST(Dem_HandleType, AUTOMATIC) BitfieldSize,
  CONST(Dem_HandleType, AUTOMATIC) BitPosition
  )
{
  Dem_Com_ProcessorWordType lBitMask;
  Dem_HandleType lWordPosition;
  volatile P2VAR(Dem_Com_ProcessorWordType, DEM_VAR_UNCACHED, AUTOMATIC) lWordPtr;

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(BitfieldSize)                                                                                 /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lWordPosition = Dem_Com_GetBitfieldWordIndex(BitPosition);

#if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (lWordPosition >= BitfieldSize)
  {
    Dem_Error_RunTimeCheckFailed(DEM_COM_IMPLEMENTATION_FILENAME, __LINE__);                                                     /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
#endif
  {
    lBitMask = DEM_BIT(Dem_Com_GetBitfieldBitIndex(BitPosition));
    lWordPtr = &BitfieldPtr[lWordPosition];
    *lWordPtr |= lBitMask;                                                                                                       /* SBSW_DEM_POINTER_WRITE_BIT_POSITION */
  }
}

/* ****************************************************************************
 % Dem_Com_ResetBitInBitfield
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Com_ResetBitInBitfield(                                                                                                      /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  volatile CONSTP2VAR(Dem_Com_ProcessorWordType, DEM_VAR_UNCACHED, AUTOMATIC) BitfieldPtr,
  CONST(Dem_HandleType, AUTOMATIC) BitfieldSize,
  CONST(Dem_HandleType, AUTOMATIC) BitPosition
  )
{
  Dem_Com_ProcessorWordType lBitMask;
  Dem_HandleType lWordPosition;
  volatile P2VAR(Dem_Com_ProcessorWordType, DEM_VAR_UNCACHED, AUTOMATIC) lWordPtr;

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(BitfieldSize)                                                                                 /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lWordPosition = Dem_Com_GetBitfieldWordIndex(BitPosition);

#if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (lWordPosition >= BitfieldSize)
  {
    Dem_Error_RunTimeCheckFailed(DEM_COM_IMPLEMENTATION_FILENAME, __LINE__);                                                     /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
#endif
  {
    lBitMask = (Dem_Com_ProcessorWordType) (~(DEM_BIT(Dem_Com_GetBitfieldBitIndex(BitPosition))));
    lWordPtr = &BitfieldPtr[lWordPosition];
    *lWordPtr &= lBitMask;                                                                                                       /* SBSW_DEM_POINTER_WRITE_BIT_POSITION */
  }
}

/*!
 * \}
 */

#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_COM_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Com_Implementation.h
 *********************************************************************************************************************/
