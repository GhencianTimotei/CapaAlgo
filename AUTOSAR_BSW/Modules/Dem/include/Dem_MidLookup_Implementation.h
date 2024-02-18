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
/*!  Project    MICROSAR Diagnostic Event Manager (Dem)
 *
 *  \addtogroup Dem_MidLookup
 *  \{
 *  \file       Dem_MidLookup_Implementation.h
 *  \brief      Implementation file for the MICROSAR Dem
 *  \details    Implementation of MidLookup subcomponent
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_MIDLOOKUP_IMPLEMENTATION_H)
#define DEM_MIDLOOKUP_IMPLEMENTATION_H

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
#include "Dem_MidLookup_Interface.h"

/* Includes to access public functions belonging to other (top level)/ (logical)/- units to be used by this Unit */
/* ------------------------------------------------------------------------- */
#include "Dem_Infrastructure_Interface.h"
#include "Dem_DtrData_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*! Filename declaration */
#define DEM_MIDLOOKUP_IMPLEMENTATION_FILENAME "Dem_MidLookup_Implementation.h"

/*! Maximum number of 'supported MID' bitmasks (MIDs 0x00, 0x20, ...) */
#define DEM_MIDLOOKUP_MAX_NUMBER_SUPPORTED_MIDS  (0x08U)

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/
#define DEM_START_SEC_VAR_NOINIT_8BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/*! Visibility change of DTR(s) is pending. Used to serialize recalculation of MID visibilty when TIDs change visibility. */
DEM_LOCAL volatile VAR(boolean, DEM_VAR_NOINIT)  Dem_MidLookup_VisibilityChanged;
#endif

#define DEM_STOP_SEC_VAR_NOINIT_8BIT
#include "MemMap.h"


#define DEM_START_SEC_VAR_NOINIT_32BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/*! 'supported MID' values (MIDS 0x00, 0x20, ...) */
DEM_LOCAL VAR(uint32, DEM_VAR_NOINIT)  Dem_MidLookup_SupportedMidMask[DEM_MIDLOOKUP_MAX_NUMBER_SUPPORTED_MIDS];
#endif

#define DEM_STOP_SEC_VAR_NOINIT_32BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define DEM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/*! DTR lookup cache to improve performance of TID lookup. */
DEM_LOCAL VAR(Dem_MidLookup_CacheType, DEM_VAR_NOINIT)  Dem_MidLookup_Cache;                                                     /* PRQA S 3218 */ /* MD_DEM_8.7 */
#endif

#define DEM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */


/*!
 * \defgroup Dem_MidLookup_Private Private Methods
 * \{
 */


#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_MidLookup_GetMidValue
 *****************************************************************************/
/*!
 * \brief         Get the Mid value for the Mid Index.
 *
 * \details       Get the Mid value for the Mid Index.
 *
 * \param[in]     MidHandle
 *                The Mid Index must be in range [0..NumberOfMids-1[.
 *
 * \return        Mid value for the Mid Index.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MidLookup_GetMidValue(
  CONST(uint16, AUTOMATIC) MidHandle
  );
#endif


#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_MidLookup_GetMidTidValue
 *****************************************************************************/
/*!
 * \brief         Get the Tid value for the Mid Index.
 *
 * \details       Get the Tid value for the Mid Index.
 *
 * \param[in]     MidHandle
 *                The Mid Index must be in range [0..NumberOfMids-1[.
 *
 * \return        Tid value for the Mid Index.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MidLookup_GetMidTidValue(
  CONST(uint16, AUTOMATIC) MidHandle
  );
#endif


#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_MidLookup_GetMidDtrId
 *****************************************************************************/
/*!
 * \brief         Get the Dtr Id for the Mid Index.
 *
 * \details       Get the Dtr Id for the Mid Index.
 *
 * \param[in]     MidHandle
 *                The Mid Index must be in range [0..NumberOfMids-1[.
 *
 * \return        Dtr Id for the Mid Index.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(DTRIdType, DEM_CODE)
Dem_MidLookup_GetMidDtrId(
  CONST(uint16, AUTOMATIC) MidHandle
  );
#endif


#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_MidLookup_MidIterExists
 *****************************************************************************/
/*!
 * \brief         Test if the iterator points to a valid element.
 *
 * \details       Test if the iterator points to a valid element.
 *
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \return        TRUE
 *                Dem_Cfg_MidIterGet() will return a valid element on this iterator
 * \return        FALSE
 *                Dem_Cfg_MidIterGet() is undefined on this iterator
 *
 * \pre           IterPtr has been initialized.
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MidLookup_MidIterExists(
  CONSTP2CONST(Dem_ComplexIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );
#endif


#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_MidLookup_MidIterGet
 *****************************************************************************/
/*!
 * \brief         Get the element pointed to by the iterator.
 *
 * \details       Get the element pointed to by the iterator.
 *
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \return        Handle to MID descriptor table
 *
 * \pre           IterPtr has been initialized.
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MidLookup_MidIterGet(
  CONSTP2CONST(Dem_ComplexIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );
#endif


#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_MidLookup_MidIterInit
 *****************************************************************************/
/*!
 * \brief         Init the iterator.
 *
 * \details       Initializes the iterator to enumerate MIDs.
 *
 * \param[in]     MidTableStartIndex
 *                StartIndex in MidTable
 *                The MidTableStartIndex must be in range [0..NumberOfMids-1[.
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MidLookup_MidIterInit(
  CONST(uint16, AUTOMATIC) MidTableStartIndex,
  CONSTP2VAR(Dem_ComplexIterType, AUTOMATIC, AUTOMATIC) IterPtr
);
#endif


#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_MidLookup_MidIterNext
 *****************************************************************************/
/*!
 * \brief         Move the iterator to the next element.
 *
 * \details       Move the iterator to the next element.
 *
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \pre           IterPtr has been initialized.
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MidLookup_MidIterNext(
  CONSTP2VAR(Dem_ComplexIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );
#endif


#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_MidLookup_TestAvailabilityMid
 *****************************************************************************/
/*!
 * \brief         Tests if input Mid is an availability Mid.
 *
 * \details       Tests if input Mid is an availability Mid.
 *
 * \param[in]     Mid
 *                Mid value
 *
 * \return        True: Input Mid is an availability Mid.
 *                False: Input Mid is not an availability Mid.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MidLookup_TestAvailabilityMid(
  CONST(uint8, AUTOMATIC) Mid
  );
#endif


#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_MidLookup_GetSupportedMidIndexOfMid
 *****************************************************************************/
/*!
 * \brief         Get the index of a supported Mid based on a Mid.
 *
 * \details       Get the index of a supported Mid based on a Mid.
 *
 * \param[in]     Mid
 *                Mid value
 *
 * \return        The SupportedMid index
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MidLookup_GetSupportedMidIndexOfMid(
  CONST(uint8, AUTOMATIC) Mid
  );
#endif


#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_MidLookup_GetSupportedMidBitPositionOfMid
 *****************************************************************************/
/*!
 * \brief         Get bit position of a Mid within the supported Mid mask.
 *
 * \details       Get bit position of a Mid within the supported Mid mask.
 *
 * \param[in]     Mid
 *                Mid value
 *
 * \return        The bit position within the supported Mid
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MidLookup_GetSupportedMidBitPositionOfMid(
  CONST(uint8, AUTOMATIC) Mid
  );
#endif


#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_MidLookup_GetInitialSupportedMidMask
 *****************************************************************************/
/*!
 * \brief         Get the initial 'Supported Mid mask' of MID.
 *
 * \details       Get the initial 'Supported Mid mask' of MID.
 *
 * \param[in]     SupportedMidIndex
 *                SupportedMidIndex must be in range [0..DEM_MIDLOOKUP_MAX_NUMBER_SUPPORTED_MIDS[.
 *
 * \return        The initial 'Supported Mid Mask'
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint32, DEM_CODE)
Dem_MidLookup_GetInitialSupportedMidMask(
  CONST(uint8, AUTOMATIC) SupportedMidIndex
  );
#endif


#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_MidLookup_GetSupportedMidMask
 *****************************************************************************/
/*!
 * \brief         Get the current 'Supported Mid Mask' of MID.
 *
 * \details       Get the current 'Supported Mid Mask' of MID.
 *
 * \param[in]     SupportedMidIndex
 *                SupportedMidIndex must be in range [0..DEM_MIDLOOKUP_MAX_NUMBER_SUPPORTED_MIDS[.
 *
 * \return        The current 'Supported Mid Mask'
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint32, DEM_CODE)
Dem_MidLookup_GetSupportedMidMask(
  CONST(uint8, AUTOMATIC) SupportedMidIndex
  );
#endif


#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_MidLookup_SetSupportedMidMask
 *****************************************************************************/
/*!
 * \brief         Set the current 'Supported Mid Mask' of MIDs.
 *
 * \details       Set the current 'Supported Mid Mask' of MIDs.
 *
 * \param[in]     SupportedMidIndex
 *                SupportedMidIndex must be in range [0..DEM_DTR_MAX_NUMBER_SUPPORTED_MID_MASKS[.
 * \param[in]     SupportedMidValue
 *                The new 'Supported Mid Mask'.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MidLookup_SetSupportedMidMask(
  CONST(uint8, AUTOMATIC) SupportedMidIndex,
  CONST(uint32, AUTOMATIC) SupportedMidValue
  );
#endif


#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_MidLookup_TestVisibilityChanged
 *****************************************************************************/
/*!
 * \brief         Get the 'Visibility Changed' flag.
 *
 * \details       Get the 'Visibility Changed' flag.
 *
 * \return        The 'Visibility Changed' flag.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MidLookup_TestVisibilityChanged(
  void
  );
#endif


#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_MidLookup_SetVisibilityChanged
 *****************************************************************************/
/*!
 * \brief         Set the 'Visibility Changed' flag.
 *
 * \details       Set the 'Visibility Changed' flag.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MidLookup_SetVisibilityChanged(
  void
  );
#endif


#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_MidLookup_ResetVisibilityChanged
 *****************************************************************************/
/*!
 * \brief         Reset the 'Visibility Changed' flag.
 *
 * \details       Reset the 'Visibility Changed' flag.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MidLookup_ResetVisibilityChanged(
  void
  );
#endif


#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_MidLookup_IsMidSupported
 *****************************************************************************/
/*!
 * \brief         Tests whether a Mid is supported.
 *
 * \details       Tests whether a Mid is supported.
 *
 * \param[in]     Mid
 *                Mid value
 *
 * \return        TRUE
 *                The Mid is supported
 * \return        FALSE
 *                The Mid is not supported
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MidLookup_IsMidSupported(
  CONST(uint8, AUTOMATIC)  Mid
  );
#endif


#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_MidLookup_FindHandleOfMid
 *****************************************************************************/
/*!
 * \brief         Returns the handle into the configuration table of the Mid.
 *
 * \details       Returns the handle into the configuration table of the Mid.
 *
 * \param[in]     Mid
 *                Mid value
 *
 * \return        The Mid handle
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_MidLookup_FindHandleOfMid(
  CONST(uint8, AUTOMATIC) Mid
  );
#endif


#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_MidLookup_GetMidValue
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MidLookup_GetMidValue(
  CONST(uint16, AUTOMATIC) MidHandle
  )
{
  uint8 lReturnValue;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MidHandle)                                                                                    /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = Dem_Cfg_GetMidOfMidTable(MidHandle);
  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_MidLookup_GetMidTidValue
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MidLookup_GetMidTidValue(
  CONST(uint16, AUTOMATIC) MidHandle
  )
{
  uint8 lReturnValue;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MidHandle)                                                                                    /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = Dem_Cfg_GetTidOfMidTable(MidHandle);
  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_MidLookup_GetMidDtrId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(DTRIdType, DEM_CODE)
Dem_MidLookup_GetMidDtrId(
  CONST(uint16, AUTOMATIC) MidHandle
  )
{
  DTRIdType lReturnValue;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MidHandle)                                                                                    /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = Dem_Cfg_GetDtrTableIdxOfMidTable(MidHandle);
  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_MidLookup_MidIterExists
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MidLookup_MidIterExists(
  CONSTP2CONST(Dem_ComplexIterType, AUTOMATIC, AUTOMATIC) IterPtr
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return (boolean)(IterPtr->mIdx < IterPtr->mEndIdx);
}
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_MidLookup_MidIterGet
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MidLookup_MidIterGet(
  CONSTP2CONST(Dem_ComplexIterType, AUTOMATIC, AUTOMATIC) IterPtr
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return (uint8)(IterPtr->mIdx);
}
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_MidLookup_MidIterInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MidLookup_MidIterInit(
  CONST(uint16, AUTOMATIC) MidTableStartIndex,
  CONSTP2VAR(Dem_ComplexIterType, AUTOMATIC, AUTOMATIC) IterPtr
  )
{
  IterPtr->mIdx = MidTableStartIndex;                                                                                            /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  IterPtr->mEndIdx = Dem_Cfg_GetSizeOfDtrTable();                                                                                /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_MidLookup_MidIterNext
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MidLookup_MidIterNext(
  CONSTP2VAR(Dem_ComplexIterType, AUTOMATIC, AUTOMATIC) IterPtr
  )
{
  IterPtr->mIdx += 1u;                                                                                                            /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ********************************************************************************************************************
 *  SUBCOMPONENT API PRIVATE FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \addtogroup Dem_MidLookup_Private
 * \{
 */

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_MidLookup_TestAvailabilityMid
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
Dem_MidLookup_TestAvailabilityMid(
  CONST(uint8, AUTOMATIC) Mid
  )
{  
  return (boolean)((Mid % 32U) == 0u);
}
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_MidLookup_GetSupportedMidIndexOfMid
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MidLookup_GetSupportedMidIndexOfMid(
  CONST(uint8, AUTOMATIC) Mid
  )
{
  return (uint8)((Mid-1u) / 32U);
}
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_MidLookup_GetSupportedMidBitPositionOfMid
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MidLookup_GetSupportedMidBitPositionOfMid(
  CONST(uint8, AUTOMATIC) Mid
  )
{
  return (uint8)(32U - (Mid % 32U));
}
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_MidLookup_GetInitialSupportedMidMask
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint32, DEM_CODE)
Dem_MidLookup_GetInitialSupportedMidMask(
  CONST(uint8, AUTOMATIC) SupportedMidIndex
  )
{
  uint32 lReturnValue;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(SupportedMidIndex)                                                                            /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = Dem_Cfg_GetSupportedMidMaskOfSupportedMidsTable(SupportedMidIndex);
  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_MidLookup_GetSupportedMidMask
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint32, DEM_CODE)
Dem_MidLookup_GetSupportedMidMask(
  CONST(uint8, AUTOMATIC) SupportedMidIndex
  )
{
  uint32 lReturnValue;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(SupportedMidIndex)                                                                            /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = Dem_MidLookup_SupportedMidMask[SupportedMidIndex];
  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_MidLookup_SetSupportedMidMask
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MidLookup_SetSupportedMidMask(
  CONST(uint8, AUTOMATIC) SupportedMidIndex,
  CONST(uint32, AUTOMATIC) SupportedMidValue
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(SupportedMidIndex)                                                                            /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(SupportedMidValue)                                                                            /* PRQA S 3112 */ /* MD_DEM_14.2 */
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (SupportedMidIndex >= DEM_MIDLOOKUP_MAX_NUMBER_SUPPORTED_MIDS)
  {
    Dem_Error_RunTimeCheckFailed(DEM_MIDLOOKUP_IMPLEMENTATION_FILENAME, __LINE__);                                               /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    Dem_MidLookup_SupportedMidMask[SupportedMidIndex] = SupportedMidValue;                                                       /* SBSW_DEM_ARRAY_WRITE_SUPPORTEDMIDMASK */
  }
}
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_MidLookup_TestVisibilityChanged
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MidLookup_TestVisibilityChanged(
  void
  )
{
  boolean lReturnValue;
  lReturnValue = Dem_MidLookup_VisibilityChanged;
  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_MidLookup_SetVisibilityChanged
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MidLookup_SetVisibilityChanged(
  void
  )
{
  Dem_MidLookup_VisibilityChanged = TRUE;
}
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_MidLookup_ResetVisibilityChanged
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MidLookup_ResetVisibilityChanged(
  void
  )
{
  Dem_MidLookup_VisibilityChanged = FALSE;
}
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_MidLookup_IsMidSupported
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
Dem_MidLookup_IsMidSupported(
  CONST(uint8, AUTOMATIC)  Mid
  )
{
  boolean lMidSupported;
  uint8 lSupportedMidIndex;
  uint8 lSupportedMidBitPosition;

  lSupportedMidIndex = Dem_MidLookup_GetSupportedMidIndexOfMid(Mid);
  lSupportedMidBitPosition = Dem_MidLookup_GetSupportedMidBitPositionOfMid(Mid);

  if ((Dem_MidLookup_TestAvailabilityMid(Mid) == FALSE)
     && (DEM_TEST_BIT(Dem_MidLookup_GetSupportedMidMask(lSupportedMidIndex), lSupportedMidBitPosition) == TRUE))
  {
    lMidSupported = TRUE;
  }
  else
  {
    lMidSupported = FALSE;
  }
  return lMidSupported;
}
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_MidLookup_FindHandleOfMid
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
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_MidLookup_FindHandleOfMid(
  CONST(uint8, AUTOMATIC) Mid
  )
{
  uint16 lMidHandle;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(Mid)                                                                                          /* PRQA S 3112 */ /* MD_DEM_14.2 */

  if (Mid == Dem_MidLookup_Cache.Mid)
  {
    lMidHandle = Dem_MidLookup_Cache.MidHandle;
  }
  else
  {
    uint8 lMid;
    uint8 lSupportedMidIndex;
    Dem_ComplexIterType lMidIter;

    lMid = 0x00;
    lMidHandle = 0x00;
    lSupportedMidIndex = Dem_MidLookup_GetSupportedMidIndexOfMid(Mid);
    DEM_IGNORE_UNUSED_VARIABLE(lSupportedMidIndex)                                                                               /* PRQA S 3112 */ /* MD_DEM_14.2 */ 

    for (Dem_MidLookup_MidIterInit(Dem_Cfg_GetStartIdxMidTableOfSupportedMidsTable(lSupportedMidIndex), &lMidIter);              /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_MidLookup_MidIterExists(&lMidIter) == TRUE;                                                                         /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_MidLookup_MidIterNext(&lMidIter))                                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      if (lMid < Mid)
      {
        lMidHandle = Dem_MidLookup_MidIterGet(&lMidIter);                                                                        /* SBSW_DEM_CALL_ITERATOR_POINTER */
        lMid = Dem_MidLookup_GetMidValue(lMidHandle);
      }
      else
      {
        break;
      }
    }

    Dem_MidLookup_Cache.Mid = Mid;
    Dem_MidLookup_Cache.MidHandle = lMidHandle;
  }
  return lMidHandle;
}
#endif

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
 * \addtogroup Dem_MidLookup_Public
 * \{
 */

/* ****************************************************************************
 % Dem_MidLookup_Init
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MidLookup_Init(
  void
  )
{
#if (DEM_CFG_SUPPORT_DTR == STD_ON)
  uint8 lSupportedMidIndex;

  Dem_MidLookup_Cache.MidHandle = 0u;
  Dem_MidLookup_Cache.Mid = Dem_MidLookup_GetMidValue(0);

  for (lSupportedMidIndex = 0u;
       lSupportedMidIndex < (uint8) Dem_Cfg_GetSizeOfSupportedMidsTable();
       ++lSupportedMidIndex)
  {
    Dem_MidLookup_SetSupportedMidMask(lSupportedMidIndex, Dem_MidLookup_GetInitialSupportedMidMask(lSupportedMidIndex));
  }

  for (lSupportedMidIndex = (uint8) Dem_Cfg_GetSizeOfSupportedMidsTable();
       lSupportedMidIndex < DEM_MIDLOOKUP_MAX_NUMBER_SUPPORTED_MIDS;                                                             /* PRQA S 2994 */ /* MD_DEM_2994 */
       ++lSupportedMidIndex)
  {
    Dem_MidLookup_SetSupportedMidMask(lSupportedMidIndex, 0);
  }
#endif
}

/* ****************************************************************************
 % Dem_MidLookup_PreInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MidLookup_PreInit(
  void
  )
{
#if (DEM_CFG_SUPPORT_DTR == STD_ON)
  Dem_MidLookup_ResetVisibilityChanged();
#endif
}

/* ****************************************************************************
 % Dem_MidLookup_UpdateMidVisibility
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
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MidLookup_UpdateMidVisibility(
  void
  )
{
#if (DEM_CFG_SUPPORT_DTR == STD_ON)
  if (Dem_MidLookup_TestVisibilityChanged() == TRUE)
  {
    Dem_ComplexIterType lMidIter;
    boolean lVisible;
    uint8 lMid;
    uint8 lLastMid;
    uint8 lSupportedMidIndex;
    uint8 lSupportedMidBitIndex;
    uint16 lMaxSupportedMidIndex;
    uint32 lSupportedMid;

    Dem_MidLookup_ResetVisibilityChanged();

    lVisible = FALSE;
    lMid = 0u;

    for (lSupportedMidIndex = 0u;
         lSupportedMidIndex < DEM_MIDLOOKUP_MAX_NUMBER_SUPPORTED_MIDS;
         ++lSupportedMidIndex)
    {
      Dem_MidLookup_SetSupportedMidMask(lSupportedMidIndex, 0);
    }

    lSupportedMidIndex = 0u;
    lSupportedMidBitIndex = 0u;

    for (Dem_MidLookup_MidIterInit(0, &lMidIter);                                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_MidLookup_MidIterExists(&lMidIter) == TRUE;                                                                         /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_MidLookup_MidIterNext(&lMidIter))                                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      uint8 lMidIndex;

      lLastMid = lMid;
      lMidIndex = Dem_MidLookup_MidIterGet(&lMidIter);                                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
      lMid = Dem_MidLookup_GetMidValue(lMidIndex);

      if (lMid != lLastMid)
      {
        lSupportedMidIndex = Dem_MidLookup_GetSupportedMidIndexOfMid(lMid);
        lSupportedMidBitIndex = Dem_MidLookup_GetSupportedMidBitPositionOfMid(lMid);
        lVisible = FALSE;
      }

      if (lVisible == FALSE)
      {
        DTRIdType lDtrId;

        lDtrId = Dem_MidLookup_GetMidDtrId(lMidIndex);
        if (Dem_DtrData_TestDtrVisibility(lDtrId) == TRUE)
        {
          lVisible = TRUE;
          lSupportedMid = Dem_MidLookup_GetSupportedMidMask(lSupportedMidIndex);
          lSupportedMid = DEM_SET_BIT(lSupportedMid, lSupportedMidBitIndex);
          Dem_MidLookup_SetSupportedMidMask(lSupportedMidIndex, lSupportedMid);
        }
      }
    }

    lMaxSupportedMidIndex = lSupportedMidIndex;
    for (lSupportedMidIndex = 0u; lSupportedMidIndex < lMaxSupportedMidIndex; ++lSupportedMidIndex)
    {
      lSupportedMid = Dem_MidLookup_GetSupportedMidMask(lSupportedMidIndex);
      lSupportedMid = DEM_SET_BIT(lSupportedMid, 0);
      Dem_MidLookup_SetSupportedMidMask(lSupportedMidIndex, lSupportedMid);
    }
  }
#endif
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_MidLookup_NotifyVisibilityChanged
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MidLookup_NotifyVisibilityChanged(
  void
  )
{
  Dem_MidLookup_SetVisibilityChanged();
}
#endif


/* ****************************************************************************
 % Dem_MidLookup_IsSupportedMid
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MidLookup_IsSupportedMid(
  CONST(uint8, AUTOMATIC)  Mid
  )
{
  return (boolean)((Mid % 32U) == 0u);
}

/* ****************************************************************************
 % Dem_MidLookup_GetSupportedMidValue
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint32, DEM_CODE)
Dem_MidLookup_GetSupportedMidValue(
  CONST(uint8, AUTOMATIC)  Mid
  )
{
  uint32 lReturnValue;
#if (DEM_CFG_SUPPORT_DTR == STD_ON)
  uint8 lSupportedMidIndex;
#endif

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(Mid)                                                                                          /* PRQA S 3112 */ /* MD_DEM_14.2 */

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
  Dem_MidLookup_UpdateMidVisibility();

  if (Dem_MidLookup_IsSupportedMid(Mid) == TRUE)
  {
    /* +1: one arbitrary Mid in the range of the SupportedMid */
    lSupportedMidIndex = Dem_MidLookup_GetSupportedMidIndexOfMid(Mid + 1u);
  }
  else
  {
    lSupportedMidIndex = Dem_MidLookup_GetSupportedMidIndexOfMid(Mid);
  }
  lReturnValue = Dem_MidLookup_GetSupportedMidMask(lSupportedMidIndex);
#else
  lReturnValue = 0UL;
#endif
  return lReturnValue;
}


/* ****************************************************************************
 % Dem_MidLookup_GetTidCountOfMid
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
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_MidLookup_GetTidCountOfMid(
  CONST(uint8, AUTOMATIC)  Mid,                                                                                                  /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONSTP2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  TidCount                                                                           /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_8.13_fp */
  )
{
  Std_ReturnType lReturnValue;

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(Mid)                                                                                          /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(TidCount)                                                                                     /* PRQA S 3112 */ /* MD_DEM_14.2 */
   
  lReturnValue = E_NOT_OK;

  /* ----- Implementation ------------------------------------------------ */
#if (DEM_CFG_SUPPORT_DTR == STD_ON)
  Dem_MidLookup_UpdateMidVisibility();

  if (Dem_MidLookup_IsMidSupported(Mid) == TRUE)
  {
    uint16 lMidHandle;
    uint8 lNumberOfTIDs;
    Dem_ComplexIterType lMidIter;

    lMidHandle = Dem_MidLookup_FindHandleOfMid(Mid);
    lNumberOfTIDs = 0u;

    for (Dem_MidLookup_MidIterInit(lMidHandle, &lMidIter);                                                                       /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_MidLookup_MidIterExists(&lMidIter) == TRUE;                                                                         /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_MidLookup_MidIterNext(&lMidIter))                                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      uint8 lMid;

      lMidHandle = Dem_MidLookup_MidIterGet(&lMidIter);                                                                          /* SBSW_DEM_CALL_ITERATOR_POINTER */
      lMid = Dem_MidLookup_GetMidValue(lMidHandle);

      if (lMid == Mid)
      {
        DTRIdType lDtrId;

        lDtrId = Dem_MidLookup_GetMidDtrId(lMidHandle);
        if (Dem_DtrData_TestDtrVisibility(lDtrId) == TRUE)
        {
          lNumberOfTIDs++;
        }
      }
      else
      {
        break;
      }
    }

    *TidCount = lNumberOfTIDs;                                                                                                   /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    lReturnValue = E_OK;
  }
#endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_MidLookup_FindDtrId
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
DEM_LOCAL_INLINE FUNC(DTRIdType, DEM_CODE)
Dem_MidLookup_FindDtrId(
  CONST(uint8, AUTOMATIC) Mid,                                                                                                   /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONST(uint8, AUTOMATIC) TidIndex,                                                                                              /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONSTP2VAR(uint8, AUTOMATIC, AUTOMATIC)  Tid                                                                                   /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_8.13_fp */
  )
{
  DTRIdType lReturnValue;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(Mid)                                                                                          /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(TidIndex)                                                                                     /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(Tid)                                                                                          /* PRQA S 3112 */ /* MD_DEM_14.2 */

  lReturnValue = DEM_DTR_INVALIDDTRID;

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
  if (Dem_MidLookup_IsMidSupported(Mid) == TRUE)
  {
    uint16 lMidHandle;
    uint8 lTidIndex;
    Dem_ComplexIterType lMidIter;

    lMidHandle = Dem_MidLookup_FindHandleOfMid(Mid);
    lTidIndex = 0u;

    for (Dem_MidLookup_MidIterInit(lMidHandle, &lMidIter);                                                                       /* PRQA S 0771 */ /* MD_DEM_15.4_opt */ /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_MidLookup_MidIterExists(&lMidIter) == TRUE;                                                                         /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_MidLookup_MidIterNext(&lMidIter))                                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      uint8 lMid;

      lMidHandle = Dem_MidLookup_MidIterGet(&lMidIter);                                                                          /* SBSW_DEM_CALL_ITERATOR_POINTER */
      lMid = Dem_MidLookup_GetMidValue(lMidHandle);

      if (lMid == Mid)
      {
        DTRIdType lDtrId;

        lDtrId = Dem_MidLookup_GetMidDtrId(lMidHandle);
        if (Dem_DtrData_TestDtrVisibility(lDtrId) == TRUE)
        {
          if (lTidIndex == TidIndex)
          {
            lReturnValue = lDtrId;
            *Tid = Dem_MidLookup_GetMidTidValue(lMidHandle);                                                                     /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
            break;
          }
          lTidIndex++;
        }
      }
      else
      {
        break;
      }
    }
  }
#endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6030, 6050, 6060, 6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STPAR, MD_MSR_STMIF */

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */


#endif /* DEM_MIDLOOKUP_IMPLEMENTATION_H */
/*!
 * \}
 */
/* *********************************************************************************************************************
 *  END OF FILE: Dem_MidLookup_Implementation.h
 **********************************************************************************************************************/
