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
/*! \addtogroup Dem_Nvm
 *  \{
 *  \file       Dem_Nvm_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Control modification state of NV blocks and background synchronization with NvM
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_NVM_IMPLEMENTATION_H)
#define DEM_NVM_IMPLEMENTATION_H

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
#include "Dem_Nvm_Interface.h"

/* Includes to access public functions belonging to other (top level)/ (logical)/- units to be used by this Unit */
/* ------------------------------------------------------------------------- */
#include "Dem_FaultMemory_Interface.h"
#include "Dem_Core_Interface.h"
#include "Dem_Client_Interface.h"
#include "Dem_Scheduler_Interface.h"
#include "Dem_InitState_Interface.h"
#include "Dem_Error_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*! Filename declaration */
#define DEM_NVM_IMPLEMENTATION_FILENAME "Dem_Nvm_Implementation.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/
#define DEM_START_SEC_VAR_NOINIT_8BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON) && (DEM_FEATURE_NEED_EVENTAVAILABLE_NV == STD_ON)
/*! Pending status update for the event availability NV block */
DEM_LOCAL VAR(uint8, DEM_VAR_NOINIT)             Dem_Nvm_PendingEventAvailabilityBlockState;
#endif

#if (DEM_CFG_USE_NVM == STD_ON) && (DEM_CFG_SUPPORT_NVM_APPL_SYNCHRONIZE == STD_ON)
/*! Pending request for NV synchronization */
DEM_LOCAL VAR(boolean, DEM_VAR_NOINIT)             Dem_Nvm_IsSynchronizationRequested;
#endif

#define DEM_STOP_SEC_VAR_NOINIT_8BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define DEM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
/*! Management data needed for immediate NV updates */
DEM_LOCAL VAR(Dem_Nvm_CommitDataType, DEM_VAR_NOINIT)  Dem_Nvm_CommitData;
#endif

#define DEM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DEFINITIONS
 *********************************************************************************************************************/
/* ********************************************************************************************************************
 *  SUBCOMPONENT PUBLIC PROPERTIES DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \addtogroup Dem_Nvm_PublicProperties
 * \{
 */

/* ****************************************************************************
 % Dem_Nvm_GetSingleBlockId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Nvm_GetSingleBlockId(                                                                                                        /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Nvm_BlockType, AUTOMATIC)  BlockType
  )
{
  Dem_Cfg_MemoryIndexType lBlockIndex;

#if (DEM_CFG_USE_NVM == STD_ON)
  switch (BlockType)
  {
  case DEM_NVM_BLOCKTYPE_ADMIN:
    lBlockIndex = Dem_Cfg_MemoryAdminIndex();
    break;
  case DEM_NVM_BLOCKTYPE_STATUS:
    lBlockIndex = Dem_Cfg_MemoryStatusIndex();
    break;
# if (DEM_FEATURE_NEED_EVENTAVAILABLE_NV == STD_ON)
  case DEM_NVM_BLOCKTYPE_AVAILABILITY:
    lBlockIndex = Dem_Cfg_MemoryEventAvailableIndex();
    break;
# endif
# if (DEM_CFG_SUPPORT_DEBOUNCE_NV == STD_ON)
  case DEM_NVM_BLOCKTYPE_DEBOUNCE:
    lBlockIndex = Dem_Cfg_MemoryDebounceIndex();
    break;
# endif
# if (DEM_CFG_SUPPORT_DTR == STD_ON)
  case DEM_NVM_BLOCKTYPE_DTR:
    lBlockIndex = Dem_Cfg_MemoryDtrIndex();
    break;
# endif
  case DEM_NVM_BLOCKTYPE_PERMANENT:
    lBlockIndex = Dem_Cfg_MemoryPermanentIndex();
    break;
  case DEM_NVM_BLOCKTYPE_OBDFREEZEFRAME:
    lBlockIndex = Dem_Cfg_MemoryFreezeFrameIndex();
    break;
  case DEM_NVM_BLOCKTYPE_IUMPR:
    lBlockIndex = Dem_Mem_MemoryIndexofIumpr();
    break;
# if (DEM_FEATURE_NEED_AGING_DATA == STD_ON)
  case DEM_NVM_BLOCKTYPE_AGINGDATA:
    lBlockIndex = Dem_Cfg_MemoryAgingDataIndex();
    break;
# endif
# if (DEM_FEATURE_NEED_CYCLE_COUNTER_DATA == STD_ON)
  case DEM_NVM_BLOCKTYPE_CYCLECOUNTERDATA:
    lBlockIndex = Dem_Cfg_MemoryCycleCounterDataIndex();
    break;
# endif
  default:
    lBlockIndex = 0u;
    Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE)
    break;
  }
#else
  lBlockIndex = 0u;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(BlockType)                                                                                    /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif

  return lBlockIndex;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_Nvm_SetAllBlocksDirty
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_SetAllBlocksDirty(
  void
  )
{
  Dem_MemSet((Dem_DataPtrType)&Dem_Cfg_GetMemoryStatus(0), DEM_NVM_BLOCKSTATE_DIRTY, Dem_Cfg_GetSizeOfMemoryStatus()*sizeof(Dem_Cfg_GetMemoryStatus(0)));   /* PRQA S 0602 */ /* MD_DEM_20.2 */ /* SBSW_DEM_MEMSET_MEMORYSTATUS */
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
 * \defgroup Dem_Nvm_Private Private Methods
 * \{
 */


#if (DEM_CFG_USE_NVM == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_GetPrivateBlockState
 *****************************************************************************/
/*!
 * \brief         Gets the status of the memory block
 *
 * \details       Gets the status of the memory block
 *
 * \param[in]     BlockIndex
 *                Handle of the memory block
 *
 * \return        The status of the memory block
 *
 * \pre           -
 * \config        DEM_CFG_USE_NVM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Nvm_GetPrivateBlockState(
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  BlockIndex
  );
#endif


#if (DEM_CFG_USE_NVM == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_SetPrivateBlockState
 *****************************************************************************/
/*!
 * \brief         Sets the status of the memory block
 *
 * \details       Sets the status of the memory block
 *
 * \param[in]     BlockIndex
 *                Handle of the memory block
 * \param[in]     Status
 *                New status of the memory block
 *
 * \pre           -
 * \config        DEM_CFG_USE_NVM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_SetPrivateBlockState(
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  BlockIndex,
  CONST(uint8, AUTOMATIC)  Status
  );
#endif


/* ****************************************************************************
 * Dem_Nvm_TestBlockStateDirtyWithoutImmediate
 *****************************************************************************/
/*!
 * \brief         Tests if the 'Dirty' flag of the block state is set
 *
 * \details       Tests if the 'Dirty' flag of the block state is set
 *
 * \param[in]     BlockState
 *                The block state of a memory block
 *
 * \return        TRUE
 *                The 'Dirty' flag of the block state is set
 *                FALSE
 *                The 'Dirty' flag of the block state is set
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Nvm_TestBlockStateDirtyWithoutImmediate(
  CONST(uint8, AUTOMATIC)  BlockState
  );


/* ****************************************************************************
 * Dem_Nvm_TestBlockStateImmediate
 *****************************************************************************/
/*!
 * \brief         Tests if the 'Commit immediately' flag of the block state is
 *                set
 *
 * \details       Tests if the 'Commit immediately' flag of the block state is
 *                set
 *
 * \param[in]     BlockState
 *                The block state of a memory block
 *
 * \return        TRUE
 *                The 'Commit immediately' flag of the block state is set
 *                FALSE
 *                The 'Commit immediately' flag of the block state is set
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Nvm_TestBlockStateImmediate(
  CONST(uint8, AUTOMATIC)  BlockState
  );


/* ****************************************************************************
 * Dem_Nvm_TestBlockStateClear
 *****************************************************************************/
/*!
 * \brief         Tests if the 'Clear' flag of the block state is set
 *
 * \details       Tests if the 'Clear' flag of the block state is set
 *
 * \param[in]     BlockState
 *                The block state of a memory block
 *
 * \return        TRUE
 *                The 'Clear' flag of the block state is set
 *                FALSE
 *                The 'Clear' flag of the block state is set
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Nvm_TestBlockStateClear(
  CONST(uint8, AUTOMATIC)  BlockState
  );


#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_GetCurrentBlockIndex
 *****************************************************************************/
/*!
 * \brief         Gets the currently processed memory block
 *
 * \details       Gets the currently processed memory block
 *
 * \return        The handle of the memory block
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Nvm_GetCurrentBlockIndex(
  void
  );
#endif


#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_SetCurrentBlockIndex
 *****************************************************************************/
/*!
 * \brief         Sets the currently processed memory block
 *
 * \details       Sets the currently processed memory block
 *
 * \param[in]     BlockIndex
 *                The handle of the memory block to be processed
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_SetCurrentBlockIndex(
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  BlockIndex
  );
#endif


#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_GetCurrentCommitState
 *****************************************************************************/
/*!
 * \brief         Gets the state of the current commit
 *
 * \details       Gets the state of the current commit
 *
 * \return        DEM_NVM_COMMIT_IDLE
 *                No commit in progress
 *                DEM_NVM_COMMIT_WRITING
 *                Data commit is in progress
 *                DEM_NVM_COMMIT_FINISHED
 *                Data commit is completed
 *                DEM_NVM_COMMIT_FAILED
 *                Data commit is completed, but failed
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Nvm_GetCurrentCommitState(
  void
  );
#endif


#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_SetCurrentCommitState
 *****************************************************************************/
/*!
 * \brief         Sets the state of the current commit
 *
 * \details       Sets the state of the current commit
 *
 * \param[in]     CommitState
 *                The state of the current commit
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_SetCurrentCommitState(
  CONST(uint8, AUTOMATIC)  CommitState
  );
#endif


#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON) && (DEM_CFG_CLEAR_NV_END_RESPONSE == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_TestCurrentBlockIsCleared
 *****************************************************************************/
/*!
 * \brief         Tests if the currently processed block was cleared
 *
 * \details       Tests if the currently processed block was cleared
 *
 * \return        TRUE
 *                The currently processed block was cleared
 *                FALSE
 *                The currently processed block was not cleared
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON &&
 *                DEM_CFG_CLEAR_NV_END_RESPONSE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Nvm_TestCurrentBlockIsCleared(
  void
  );
#endif


#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON) && (DEM_CFG_CLEAR_NV_END_RESPONSE == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_SetCurrentBlockIsCleared
 *****************************************************************************/
/*!
 * \brief         Sets the value of the 'BlockIsCleared' flag for the currently
 *                processed block
 *
 * \details       Sets the value of the 'BlockIsCleared' flag for the currently
 *                processed block
 *
 * \param[in]     BlockIsCleared
 *                Flag to tell whether or not the current block is cleared or
 *                modified.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON &&
 *                DEM_CFG_CLEAR_NV_END_RESPONSE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_SetCurrentBlockIsCleared(
  CONST(boolean, AUTOMATIC)  BlockIsCleared
  );
#endif


#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_TestPendingCommits
 *****************************************************************************/
/*!
 * \brief         Tests if NvRAM blocks have to be processed
 *
 * \details       Tests if NvRAM blocks have to be processed
 *
 * \return        TRUE
 *                NvRAM blocks have to be processed
 *                FALSE
 *                No NvRAM blocks have to be processed
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Nvm_TestPendingCommits(
  void
  );
#endif


#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_IncrementPendingCommits
 *****************************************************************************/
/*!
 * \brief         Increments the number of to be processed NvRAM blocks
 *
 * \details       Increments the number of to be processed NvRAM blocks
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_IncrementPendingCommits(
  void
  );
#endif


#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_DecrementPendingCommits
 *****************************************************************************/
/*!
 * \brief         Decrements the number of to be processed NvRAM blocks
 *
 * \details       Decrements the number of to be processed NvRAM blocks
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_DecrementPendingCommits(
  void
  );
#endif


#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_ResetPendingCommits
 *****************************************************************************/
/*!
 * \brief         Resets the number of to be processed NvRAM blocks
 *
 * \details       Resets the number of to be processed NvRAM blocks
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_ResetPendingCommits(
  void
  );
#endif


#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON) && (DEM_CFG_CLEAR_NV_END_RESPONSE == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_TestPendingClearCommits
 *****************************************************************************/
/*!
 * \brief         Tests if cleared NvRAM blocks have to be processed
 *
 * \details       Tests if cleared NvRAM blocks have to be processed
 *
 * \return        TRUE
 *                Cleared NvRAM blocks have to be processed
 *                FALSE
 *                No cleared NvRAM blocks have to be processed
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON &&
 *                DEM_CFG_CLEAR_NV_END_RESPONSE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Nvm_TestPendingClearCommits(
  void
  );
#endif


#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON) && (DEM_CFG_CLEAR_NV_END_RESPONSE == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_IncrementPendingClearCommits
 *****************************************************************************/
/*!
 * \brief         Increments the number of to be cleared NvRAM blocks
 *
 * \details       Increments the number of to be cleared NvRAM blocks
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON &&
 *                DEM_CFG_CLEAR_NV_END_RESPONSE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_IncrementPendingClearCommits(
  void
  );
#endif


#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON) && (DEM_CFG_CLEAR_NV_END_RESPONSE == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_DecrementPendingClearCommits
 *****************************************************************************/
/*!
 * \brief         Decrements the number of to be cleared NvRAM blocks
 *
 * \details       Decrements the number of to be cleared NvRAM blocks
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON &&
 *                DEM_CFG_CLEAR_NV_END_RESPONSE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_DecrementPendingClearCommits(
  void
  );
#endif


#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON) && (DEM_CFG_CLEAR_NV_END_RESPONSE == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_ResetPendingClearCommits
 *****************************************************************************/
/*!
 * \brief         Resets the number of to be cleared NvRAM blocks
 *
 * \details       Resets the number of to be cleared NvRAM blocks
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON &&
 *                DEM_CFG_CLEAR_NV_END_RESPONSE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_ResetPendingClearCommits(
  void
  );
#endif


#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_MemorySetBlockStateImmediate
 *****************************************************************************/
/*!
 * \brief         Marks an event memory entry block as 'dirty' and commits it to
 *                NvM
 *
 * \details       This function checks the occurrence limit (if configured) and
 *                removes an immediate update request if necessary. Otherwise
 *                it behaves like Dem_Nvm_SetBlockStateImmediate.
 *
 * \param[in]     BlockIndex
 *                Handle of the memory block
 * \param[in]     BlockState
 *                State modification of the block
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different blocks
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_MemorySetBlockStateImmediate(
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  BlockIndex,
  CONST(uint8, AUTOMATIC)  BlockState
  );
#endif


#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_SetBlockStateImmediate
 *****************************************************************************/
/*!
 * \brief         Marks a block as 'dirty' and commits it to NvM
 *
 * \details       This function processes the NV block according to BlockState:
 *                DEM_NVM_BLOCKSTATE_IMMEDIATEFLAG - The block is queued for
 *                immediate NV update.
 *                DEM_NVM_BLOCKSTATE_CLEARFLAG - The block was cleared.
 *                DEM_NVM_BLOCKSTATE_DIRTY - The block should be synchronized
 *                to NV-Ram during WriteAll.
 *                The NV block state will not downgrade, e.g. setting a block
 *                to DIRTY will not remove a CLEARFLAG or IMMEDIATEFLAG.
 *
 * \param[in]     BlockIndex
 *                Handle of the memory block
 * \param[in]     BlockState
 *                State modification of the block
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different blocks
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Nvm_SetBlockStateImmediate(
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  BlockIndex,
  CONST(uint8, AUTOMATIC)  BlockState
  );
#endif


#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_RestoreBlockStateImmediate
 *****************************************************************************/
/*!
 * \brief         Restore internal state for block marked as 'dirty'
 *
 * \details       This function processes the NV block according to BlockState:
 *                DEM_NVM_BLOCKSTATE_IMMEDIATEFLAG - The block is queued for
 *                immediate NV update.
 *                DEM_NVM_BLOCKSTATE_CLEARFLAG - The block was cleared.
 *                DEM_NVM_BLOCKSTATE_DIRTY - The block should be synchronized
 *                to NV-Ram during WriteAll.
 *
 * \param[in]     BlockIndex
 *                Handle of the memory block
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different blocks
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_RestoreBlockStateImmediate(
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  BlockIndex
  );
#endif


#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_FindNextBlockToCommit
 *****************************************************************************/
/*!
 * \brief         Find the next modified block to commit
 *
 * \details       Find the next modified block to commit
 *
 * \return        TRUE
 *                A block was found
 *                FALSE
 *                No block was found
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Nvm_FindNextBlockToCommit(
  void
  );
#endif


#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_CommitBlock
 *****************************************************************************/
/*!
 * \brief         Processes NvM synchronization
 *
 * \details       This function writes the memory block marked for immediate
 *                synchronization into the NV storage.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_CommitBlock(
  void
  );
#endif


#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_ProcessQueue
 *****************************************************************************/
/*!
 * \brief         Process updates of deferred dirty markers
 *
 * \details       To avoid critical sections some NV block status updates are
 *                deferred. This function processes those updates.
 *                This function also processes the application request for
 *                complete NV-Ram synchronization.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_ProcessQueue(
  void
  );
#endif


#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON) && (DEM_CFG_SUPPORT_NVM_POLLING == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_GetNvMResult
 *****************************************************************************/
/*!
 * \brief         Poll the result of an ongoing write job
 *
 * \details       Poll the result of an ongoing write job
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON &&
 *                DEM_CFG_SUPPORT_NVM_POLLING == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_GetNvMResult(
  void
  );
#endif


#if (DEM_CFG_USE_NVM == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_InitStartup
 *****************************************************************************/
/*!
 * \brief         Initializes the NvM management
 *
 * \details       Initializes the NvM management on startup
 *
 * \pre           May be called only during module initialization
 * \config        DEM_CFG_USE_NVM == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_InitStartup(
  void
  );
#endif


#if (DEM_CFG_USE_NVM == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_InitWakeup
 *****************************************************************************/
/*!
 * \brief         Initializes the NvM management
 *
 * \details       Initializes the NvM management on wake up
 *
 * \pre           May be called only during module initialization
 * \config        DEM_CFG_USE_NVM == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_InitWakeup(
  void
  );
#endif

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/

#if (DEM_CFG_USE_NVM == STD_ON)
/* ****************************************************************************
 % Dem_Nvm_GetPrivateBlockState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Nvm_GetPrivateBlockState(
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  BlockIndex
  )
{
  return Dem_Cfg_GetMemoryStatus(BlockIndex);                                                                                    /* PRQA S 2842, 2843 */ /* MD_DEM_Dir4.1_ReadOperation, MD_DEM_Dir4.1_ReadOperation */
}
#endif

#if (DEM_CFG_USE_NVM == STD_ON)
/* ****************************************************************************
 % Dem_Nvm_SetPrivateBlockState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_SetPrivateBlockState(
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  BlockIndex,
  CONST(uint8, AUTOMATIC)  Status
  )
{
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (BlockIndex >= Dem_Cfg_GetSizeOfMemoryStatus())
  {
    Dem_Error_RunTimeCheckFailed(DEM_NVM_IMPLEMENTATION_FILENAME, __LINE__);                                                     /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    Dem_Cfg_SetMemoryStatus(BlockIndex, Status);                                                                                 /* PRQA S 2841 */ /* MD_DEM_Dir4.1_RunTimeCheckWriteOperation */ /* SBSW_DEM_ARRAY_WRITE_MEMORYSTATUS */
  }
}
#endif

/* ****************************************************************************
 % Dem_Nvm_TestBlockStateDirtyWithoutImmediate
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Nvm_TestBlockStateDirtyWithoutImmediate(                                                                                     /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  BlockState
  )
{
  return (boolean)((BlockState & (DEM_NVM_BLOCKSTATE_IMMEDIATEFLAG | DEM_NVM_BLOCKSTATE_DIRTY)) == DEM_NVM_BLOCKSTATE_DIRTY);
}

/* ****************************************************************************
 % Dem_Nvm_TestBlockStateImmediate
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Nvm_TestBlockStateImmediate(                                                                                                 /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  BlockState
  )
{
  return (boolean)((BlockState & DEM_NVM_BLOCKSTATE_IMMEDIATEFLAG) != 0u);
}

/* ****************************************************************************
 % Dem_Nvm_TestBlockStateClear
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Nvm_TestBlockStateClear(                                                                                                     /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  BlockState
  )
{
  return (boolean)((BlockState & DEM_NVM_BLOCKSTATE_CLEARFLAG) != 0u);
}

#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
/* ****************************************************************************
 % Dem_Nvm_GetCurrentBlockIndex
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Nvm_GetCurrentBlockIndex(
  void
  )
{
  return Dem_Nvm_CommitData.BlockIndex;
}
#endif

#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
/* ****************************************************************************
 % Dem_Nvm_SetCurrentBlockIndex
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_SetCurrentBlockIndex(
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  BlockIndex
  )
{
  Dem_Nvm_CommitData.BlockIndex = BlockIndex;
}
#endif

#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
/* ****************************************************************************
 % Dem_Nvm_GetCurrentCommitState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Nvm_GetCurrentCommitState(
  void
  )
{
  return Dem_Nvm_CommitData.CommitState;
}
#endif

#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
/* ****************************************************************************
 % Dem_Nvm_SetCurrentCommitState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_SetCurrentCommitState(
  CONST(uint8, AUTOMATIC)  CommitState
  )
{
  Dem_Nvm_CommitData.CommitState = CommitState;
}
#endif

#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON) && (DEM_CFG_CLEAR_NV_END_RESPONSE == STD_ON)
/* ****************************************************************************
 % Dem_Nvm_TestCurrentBlockIsCleared
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Nvm_TestCurrentBlockIsCleared(
  void
  )
{
  return Dem_Nvm_CommitData.BlockIsCleared;
}
#endif

#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON) && (DEM_CFG_CLEAR_NV_END_RESPONSE == STD_ON)
/* ****************************************************************************
 % Dem_Nvm_SetCurrentBlockIsCleared
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_SetCurrentBlockIsCleared(
  CONST(boolean, AUTOMATIC)  BlockIsCleared
  )
{
  Dem_Nvm_CommitData.BlockIsCleared = BlockIsCleared;
}
#endif

#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
/* ****************************************************************************
 % Dem_Nvm_TestPendingCommits
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Nvm_TestPendingCommits(
  void
  )
{
  return (boolean) (Dem_Nvm_CommitData.PendingCount > 0u);
}
#endif

#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
/* ****************************************************************************
 % Dem_Nvm_IncrementPendingCommits
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_IncrementPendingCommits(
  void
  )
{
  Dem_Internal_AssertReturnVoid(Dem_Nvm_CommitData.PendingCount <= DEM_CFG_MEMORYINDEX_MAX, DEM_E_INCONSISTENT_STATE)
  Dem_Nvm_CommitData.PendingCount++;
}
#endif

#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
/* ****************************************************************************
 % Dem_Nvm_DecrementPendingCommits
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_DecrementPendingCommits(
  void
  )
{
  Dem_Internal_AssertReturnVoid(Dem_Nvm_CommitData.PendingCount > 0, DEM_E_INCONSISTENT_STATE)
  Dem_Nvm_CommitData.PendingCount--;
}
#endif

#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
/* ****************************************************************************
 % Dem_Nvm_ResetPendingCommits
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_ResetPendingCommits(
  void
  )
{
  Dem_Nvm_CommitData.PendingCount = 0u;
}
#endif

#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON) && (DEM_CFG_CLEAR_NV_END_RESPONSE == STD_ON)
/* ****************************************************************************
 % Dem_Nvm_TestPendingClearCommits
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Nvm_TestPendingClearCommits(
  void
  )
{
  return (boolean) (Dem_Nvm_CommitData.PendingClearCount > 0u);
}
#endif

#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON) && (DEM_CFG_CLEAR_NV_END_RESPONSE == STD_ON)
/* ****************************************************************************
 % Dem_Nvm_IncrementPendingClearCommits
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_IncrementPendingClearCommits(
  void
  )
{
  Dem_Internal_AssertReturnVoid(Dem_Nvm_CommitData.PendingClearCount <= DEM_CFG_MEMORYINDEX_MAX, DEM_E_INCONSISTENT_STATE)
  Dem_Nvm_CommitData.PendingClearCount++;
}
#endif

#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON) && (DEM_CFG_CLEAR_NV_END_RESPONSE == STD_ON)
/* ****************************************************************************
 % Dem_Nvm_DecrementPendingClearCommits
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_DecrementPendingClearCommits(
  void
  )
{
  Dem_Internal_AssertReturnVoid(Dem_Nvm_CommitData.PendingClearCount > 0, DEM_E_INCONSISTENT_STATE)
  Dem_Nvm_CommitData.PendingClearCount--;
}
#endif

#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON) && (DEM_CFG_CLEAR_NV_END_RESPONSE == STD_ON)
/* ****************************************************************************
 % Dem_Nvm_ResetPendingClearCommits
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_ResetPendingClearCommits(
  void
  )
{
  Dem_Nvm_CommitData.PendingClearCount = 0u;
}
#endif

#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
/* ****************************************************************************
 % Dem_Nvm_MemorySetBlockStateImmediate
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
Dem_Nvm_MemorySetBlockStateImmediate(
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  BlockIndex,
  CONST(uint8, AUTOMATIC)  BlockState
  )
{
  uint8 lBlockState;
  Dem_Internal_AssertReturnVoid((BlockIndex != Dem_Cfg_GlobalNvBlockCount()), DEM_E_INCONSISTENT_STATE)

# if (DEM_CFG_SUPPORT_NVM_WRITELIMIT == STD_ON)
  if (BlockState == DEM_NVM_BLOCKSTATE_DIRTYIMMEDIATE)
  { /* downgrade immediate update when occurrence limit is reached */
    Dem_MemoryEntry_OccurrenceCounterType lOccurrenceCounter;
    lOccurrenceCounter = Dem_MemoryEntry_GetOccurrenceCounter(Dem_MemoryEntry_GetId(BlockIndex));

    if (lOccurrenceCounter >= Dem_Cfg_GlobalNvStorageLimit())
    {
      lBlockState = DEM_NVM_BLOCKSTATE_DIRTY;
    }
    else
    {
      lBlockState = BlockState;
    }
  }
  else
# endif
  {
    lBlockState = BlockState;
  }

  Dem_Nvm_SetBlockStateImmediate(BlockIndex, lBlockState);
}                                                                                                                                /* PRQA S 6010, 6030 */ /* MD_MSR_STPTH, MD_MSR_STCYC */
#endif /* (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON) */

#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
/* ****************************************************************************
 % Dem_Nvm_SetBlockStateImmediate
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
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Nvm_SetBlockStateImmediate(
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  BlockIndex,
  CONST(uint8, AUTOMATIC)  BlockState
  )
{
  Dem_Internal_AssertReturnVoid((BlockIndex != Dem_Cfg_GlobalNvBlockCount()), DEM_E_INCONSISTENT_STATE)

  if ( (Dem_Nvm_TestBlockStateImmediate(Dem_Nvm_GetPrivateBlockState(BlockIndex)) == FALSE)
    && (Dem_Nvm_TestBlockStateImmediate(BlockState) == TRUE) )                                                                   
  {
    Dem_Nvm_IncrementPendingCommits();
  }

# if (DEM_CFG_CLEAR_NV_END_RESPONSE == STD_ON)
  if ( (Dem_Nvm_TestBlockStateClear(Dem_Nvm_GetPrivateBlockState(BlockIndex)) == FALSE)
    && (Dem_Nvm_TestBlockStateClear(BlockState) == TRUE) )                                                                       
  { /* Only if clear flag is being set, not if it is already set */
    Dem_Nvm_IncrementPendingClearCommits();
  }
# endif /* (DEM_CFG_CLEAR_NV_END_RESPONSE == STD_ON) */

  if (Dem_Nvm_GetPrivateBlockState(BlockIndex) < BlockState)
  { /* Only if no information is lost (e.g. do not replace clear with dirty) */
    Dem_Nvm_SetPrivateBlockState(BlockIndex, BlockState);
  }
}                                                                                                                                /* PRQA S 6010, 6030 */ /* MD_MSR_STPTH, MD_MSR_STCYC */
#endif /* (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON) */

#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
/* ****************************************************************************
 % Dem_Nvm_RestoreBlockStateImmediate
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_RestoreBlockStateImmediate(
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  BlockIndex
  )
{
  Dem_Internal_AssertReturnVoid((BlockIndex < Dem_Cfg_GlobalNvBlockCount()), DEM_E_INCONSISTENT_STATE)

  if (Dem_Nvm_TestBlockStateImmediate(Dem_Nvm_GetPrivateBlockState(BlockIndex)) == TRUE)
  {
    Dem_Nvm_IncrementPendingCommits();
  }

# if (DEM_CFG_CLEAR_NV_END_RESPONSE == STD_ON)
  if (Dem_Nvm_TestBlockStateClear(Dem_Nvm_GetPrivateBlockState(BlockIndex)) == TRUE)
  {
    Dem_Nvm_IncrementPendingClearCommits();
  }
# endif /* (DEM_CFG_CLEAR_NV_END_RESPONSE == STD_ON) */
}
#endif /* (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON) */

#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
/* ****************************************************************************
 % Dem_Nvm_FindNextBlockToCommit
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
Dem_Nvm_FindNextBlockToCommit(
  void
  )
{
  boolean lFoundBlock;
  /* Permanent has highest prio: check for modification and write it */
  if ( (Dem_Cfg_IsPermanentSupportedInVariant() == TRUE) 
    && (Dem_Nvm_TestBlockStateImmediate(Dem_Nvm_GetPrivateBlockState(Dem_Cfg_MemoryPermanentIndex())) == TRUE) )
  {
    Dem_Nvm_SetCurrentBlockIndex(Dem_Cfg_MemoryPermanentIndex());
    lFoundBlock = TRUE;
  }
  else
  /* Freezeframe has next highest prio: check for modification and write it */
  if ( (Dem_Cfg_IsObdIISupportedInVariant() == TRUE)
    && (Dem_Nvm_TestBlockStateImmediate(Dem_Nvm_GetPrivateBlockState(Dem_Cfg_MemoryFreezeFrameIndex())) == TRUE) )
  {
    Dem_Nvm_SetCurrentBlockIndex(Dem_Cfg_MemoryFreezeFrameIndex());
    lFoundBlock = TRUE;
  }
  else
  /* Event states first, they are bound to be modified quickly */
  if (Dem_Nvm_TestBlockStateImmediate(Dem_Nvm_GetPrivateBlockState(Dem_Cfg_MemoryStatusIndex())) == TRUE)
  {
    Dem_Nvm_SetCurrentBlockIndex(Dem_Cfg_MemoryStatusIndex());
    lFoundBlock = TRUE;
  }
  else
  {
    /* Start at last inspected index to write blocks fairly */
    Dem_Cfg_MemoryIndexType lBlockIndex;
    Dem_Cfg_MemoryIndexType lEndIndex;

    lFoundBlock = FALSE;
    lBlockIndex = Dem_Nvm_GetCurrentBlockIndex();
    lEndIndex = lBlockIndex;
    do
    {
      Dem_WrappingIncrement(lBlockIndex, Dem_Cfg_GlobalNvBlockCount())

      if (Dem_Nvm_TestBlockStateImmediate(Dem_Nvm_GetPrivateBlockState(lBlockIndex)) == TRUE)
      { /* Found a block that needs to be committed */
        Dem_Nvm_SetCurrentBlockIndex(lBlockIndex);
        lFoundBlock = TRUE;
        break;
      }
    }
    while (lBlockIndex != lEndIndex);   /* Stop when all slots have been inspected */
  }
  return lFoundBlock;
}                                                                                                                                /* PRQA S  6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif

#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
/* ****************************************************************************
 % Dem_Nvm_CommitBlock
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
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_CommitBlock(
  void
  )
{
  Dem_Cfg_MemoryIndexType lBlockIndex;
  lBlockIndex = Dem_Nvm_GetCurrentBlockIndex();

# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (lBlockIndex >= Dem_Cfg_GlobalNvBlockCount())
  {
    Dem_Error_RunTimeCheckFailed(DEM_NVM_IMPLEMENTATION_FILENAME, __LINE__);                                                     /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    Std_ReturnType lNvmResult;

# if (DEM_CFG_CLEAR_NV_END_RESPONSE == STD_ON)
    Dem_Nvm_SetCurrentBlockIsCleared(Dem_Nvm_TestBlockStateClear(Dem_Nvm_GetPrivateBlockState(lBlockIndex)));
# endif
    if (lBlockIndex == Dem_Cfg_MemoryAdminIndex())
    {
      Dem_Nvm_SetPrivateBlockState(lBlockIndex, DEM_NVM_BLOCKSTATE_DIRTY);
    }
    else
    {
      Dem_Nvm_SetPrivateBlockState(lBlockIndex, DEM_NVM_BLOCKSTATE_UNMODIFIED);
    }

# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
    if ((Dem_Cfg_MemoryDataSizeType)sizeof(Dem_Cfg_CommitBuffer) < Dem_Cfg_MemoryDataSize[lBlockIndex])
    {
      Dem_Error_RunTimeCheckFailed(DEM_NVM_IMPLEMENTATION_FILENAME, __LINE__);                                                   /* SBSW_DEM_POINTER_RUNTIME_CHECK */
      lNvmResult = E_NOT_OK;
    }
    else
# endif
    {
      Dem_MemCpy((Dem_DataPtrType)&Dem_Cfg_CommitBuffer.mRaw[0],                                                                 /* PRQA S 0602 */ /* MD_DEM_20.2 */ /* SBSW_DEM_MEMCOPY_MEMORY_DATA */
                 Dem_Cfg_MemoryDataPtr[lBlockIndex],
                 Dem_Cfg_MemoryDataSize[lBlockIndex]);

      /* Job End notification might return immediately - set the commit state before WriteBlock */
      Dem_Nvm_SetCurrentCommitState(DEM_NVM_COMMIT_WRITING);
      lNvmResult = NvM_WriteBlock((NvM_BlockIdType)Dem_Cfg_MemoryBlockId[lBlockIndex],                                           /* SBSW_DEM_NVM_WRITEBLOCK */
                                &Dem_Cfg_CommitBuffer.mRaw[0]);
    }

    if (lNvmResult != E_OK)
    { /* Write attempt failed - act as if callback had returned failed. This case is handled by Dem_NvM_MainFunction */
      Dem_Nvm_SetCurrentCommitState(DEM_NVM_COMMIT_FAILED);
    }
  }
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif /* (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON) */

#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
/* ****************************************************************************
 % Dem_Nvm_ProcessQueue
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
Dem_Nvm_ProcessQueue(
  void
  )
{
  /* Process queued modification status of the status data block */
# if (DEM_FEATURE_NEED_EVENTAVAILABLE_NV == STD_ON)
  if (Dem_Nvm_PendingEventAvailabilityBlockState != DEM_NVM_BLOCKSTATE_UNMODIFIED)
  {
    Dem_Nvm_SetBlockStateImmediate(Dem_Cfg_MemoryEventAvailableIndex(), Dem_Nvm_PendingEventAvailabilityBlockState);
    Dem_Nvm_PendingEventAvailabilityBlockState = DEM_NVM_BLOCKSTATE_UNMODIFIED;
  }
# endif

# if (DEM_CFG_SUPPORT_NVM_APPL_SYNCHRONIZE == STD_ON)
  /* Process queued request for full NV sync */
  if (Dem_Nvm_IsSynchronizationRequested == TRUE)
  {
    Dem_Cfg_MemoryIndexType lBlockIndex;
    for (lBlockIndex = 0u; lBlockIndex < Dem_Cfg_GlobalNvBlockCount(); ++lBlockIndex)
    {
      if (Dem_Nvm_TestBlockStateDirtyWithoutImmediate(Dem_Nvm_GetPrivateBlockState(lBlockIndex)) == TRUE)
      {
        Dem_Nvm_SetBlockStateImmediate(lBlockIndex, DEM_NVM_BLOCKSTATE_DIRTYIMMEDIATE);
      }
    }
    Dem_OperationCycle_UpdateCycleStatesInNvBlock();
    Dem_Mem_CopyDataDebounceNv(DEM_NVM_BLOCKSTATE_DIRTYIMMEDIATE);
    Dem_Nvm_IsSynchronizationRequested = FALSE;
  }
# endif
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON) && (DEM_CFG_SUPPORT_NVM_POLLING == STD_ON )
/* ****************************************************************************
 % Dem_Nvm_GetNvMResult
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
Dem_Nvm_GetNvMResult(
  void
  )
{
  if (Dem_Nvm_GetCurrentCommitState() == DEM_NVM_COMMIT_WRITING)
  {
    NvM_RequestResultType lRequestResult;
    Std_ReturnType lCallResult;

    lRequestResult = NVM_REQ_NOT_OK;

    lCallResult = NvM_GetErrorStatus((NvM_BlockIdType)Dem_Cfg_MemoryBlockId[Dem_Nvm_GetCurrentBlockIndex()], &lRequestResult);   /* SBSW_DEM_POINTER_FORWARD_STACK */
    if (lCallResult == E_OK)
    {
      if (lRequestResult != NVM_REQ_PENDING)
      {
        if (lRequestResult != NVM_REQ_OK)
        { /* Write request aborted or otherwise failed. */
          Dem_Nvm_SetCurrentCommitState(DEM_NVM_COMMIT_FAILED);
        }
        else
        {
          /* continue with next block */
          Dem_Nvm_SetCurrentCommitState(DEM_NVM_COMMIT_FINISHED);
        }
      }
      /* else: NvM is still busy, wait */
    }
    else
    {
      Dem_Nvm_SetCurrentCommitState(DEM_NVM_COMMIT_FAILED);
    }
  }
}
#endif

#if (DEM_CFG_USE_NVM == STD_ON)
/* ****************************************************************************
 % Dem_Nvm_InitStartup
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
Dem_Nvm_InitStartup(
  void
  )
{
  Dem_MemSet((Dem_DataPtrType)&Dem_Cfg_GetMemoryStatus(0), DEM_NVM_BLOCKSTATE_UNMODIFIED, Dem_Cfg_GetSizeOfMemoryStatus()*sizeof(Dem_Cfg_GetMemoryStatus(0))); /* PRQA S 0602 */ /* MD_DEM_20.2 */ /* SBSW_DEM_MEMSET_MEMORYSTATUS */
  Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_ADMIN),
                              DEM_NVM_BLOCKSTATE_DIRTY);

# if (DEM_CFG_SUPPORT_NVM_APPL_SYNCHRONIZE == STD_ON)
  Dem_Nvm_IsSynchronizationRequested = FALSE;
# endif
# if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
#  if (DEM_FEATURE_NEED_EVENTAVAILABLE_NV == STD_ON)
  Dem_Nvm_PendingEventAvailabilityBlockState = DEM_NVM_BLOCKSTATE_UNMODIFIED;
#  endif
  Dem_Nvm_SetCurrentBlockIndex(0);
  Dem_Nvm_ResetPendingCommits();
  Dem_Nvm_SetCurrentCommitState(DEM_NVM_COMMIT_IDLE);
#  if (DEM_CFG_CLEAR_NV_END_RESPONSE == STD_ON)
  Dem_Nvm_ResetPendingClearCommits();
  Dem_Nvm_SetCurrentBlockIsCleared(FALSE);
#  endif
# endif
}                                                                                                                                /* PRQA S  6050 */ /* MD_MSR_STCAL */
#endif /* (DEM_CFG_USE_NVM == STD_ON) */

#if (DEM_CFG_USE_NVM == STD_ON)
/* ****************************************************************************
 % Dem_Nvm_InitWakeup
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_InitWakeup(
  void
  )
{
# if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
  Dem_Cfg_MemoryIndexType lBlockIndex;
  for (lBlockIndex = 0u; lBlockIndex < Dem_Cfg_GlobalNvBlockCount(); ++lBlockIndex)
  {
    uint8 lBlockState;
    lBlockState = Dem_Nvm_GetPrivateBlockState(lBlockIndex);
    if (lBlockState != DEM_NVM_BLOCKSTATE_UNMODIFIED)
    {
      {
        Dem_Nvm_RestoreBlockStateImmediate(lBlockIndex);
      }
    }
  }
# endif
}                                                                                                                                /* PRQA S  6050 */ /* MD_MSR_STCAL */
#endif /* (DEM_CFG_USE_NVM == STD_ON) */

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
 * \addtogroup Dem_Nvm_Public
 * \{
 */

/* ****************************************************************************
 % Dem_Nvm_SetSingleBlockState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Nvm_SetSingleBlockState(                                                                                                     /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  BlockIndex,
CONST(uint8, AUTOMATIC)  Status
)
{
#if (DEM_CFG_USE_NVM == STD_ON)
# if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
#  if (DEM_FEATURE_NEED_EVENTAVAILABLE_NV == STD_ON)
  if (BlockIndex == Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_AVAILABILITY))
  {
    Dem_Nvm_PendingEventAvailabilityBlockState = Status;
  }
  else
#  endif
  {
    Dem_Nvm_SetBlockStateImmediate(BlockIndex, Status);
  }
# else
  Dem_Nvm_SetPrivateBlockState(BlockIndex, Status);
# endif
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(BlockIndex)                                                                                   /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(Status)                                                                                       /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
}


/* ****************************************************************************
 % Dem_Nvm_SetEventMemoryBlockState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Nvm_SetEventMemoryBlockState(                                                                                                /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  BlockIndex,
CONST(uint8, AUTOMATIC)  Status
)
{
#if (DEM_CFG_USE_NVM == STD_ON)
# if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
  Dem_Nvm_MemorySetBlockStateImmediate(BlockIndex, Status);
# else
  Dem_Nvm_SetPrivateBlockState(BlockIndex, Status);
# endif
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(BlockIndex)                                                                                   /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(Status)                                                                                       /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
}


/* ****************************************************************************
 % Dem_Nvm_SetTimeSeriesMemoryBlockState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Nvm_SetTimeSeriesMemoryBlockState(                                                                                           /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  BlockIndex,
CONST(uint8, AUTOMATIC)  Status
)
{
#if (DEM_CFG_USE_NVM == STD_ON)
# if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
  Dem_Nvm_SetBlockStateImmediate(BlockIndex, Status);
# else
  Dem_Nvm_SetPrivateBlockState(BlockIndex, Status);
# endif
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(BlockIndex)                                                                                   /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(Status)                                                                                       /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
}

#if (DEM_CFG_USE_NVM == STD_ON) && (DEM_CFG_SUPPORT_NVM_WRITELIMIT == STD_ON)
/* ****************************************************************************
 % Dem_Nvm_TestAndSetBlockStateImmediate
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
Dem_Nvm_TestAndSetBlockStateImmediate(
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  BlockIndex,
  CONST(uint16, AUTOMATIC)  OldOccCounter,
  CONST(uint16, AUTOMATIC)  NewOccCounter
  )
{
  if ( (NewOccCounter > Dem_Cfg_GlobalNvStorageLimit())
    || ( (NewOccCounter == Dem_Cfg_GlobalNvStorageLimit())                                                                       
      && (NewOccCounter == OldOccCounter) ) )
  {
    Dem_Nvm_SetBlockStateImmediate(BlockIndex, DEM_NVM_BLOCKSTATE_DIRTY);
  }
  else
  {
    Dem_Nvm_SetBlockStateImmediate(BlockIndex, DEM_NVM_BLOCKSTATE_DIRTYIMMEDIATE);
  }
}
#endif

/* ****************************************************************************
 % Dem_Nvm_SetStatusBlockChanged
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_SetStatusBlockChanged(
  void
  )
{
#if (DEM_CFG_USE_NVM == STD_ON)
  Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_STATUS),
                              DEM_NVM_BLOCKSTATE_DIRTY);
#else
  return;
#endif
}

#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
/* ****************************************************************************
 % Dem_Nvm_IsCurrentlyWrittenBlockModified
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Nvm_IsCurrentlyWrittenBlockModified(
  void
  )
{
  return (boolean) ( (Dem_Nvm_GetCurrentCommitState() == DEM_NVM_COMMIT_WRITING)
    && (Dem_Nvm_GetPrivateBlockState(Dem_Nvm_GetCurrentBlockIndex()) != DEM_NVM_BLOCKSTATE_UNMODIFIED) );                        
}
#endif

#if ((DEM_CFG_USE_NVM == STD_ON) && (DEM_CFG_SUPPORT_NVM_POLLING == STD_OFF))
/* ****************************************************************************
 % Dem_Nvm_ChangeNVWriteState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_ChangeNVWriteState(
  CONST(NvM_RequestResultType, AUTOMATIC)  JobResult
  )
{
# if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
  if (Dem_Nvm_GetCurrentCommitState() == DEM_NVM_COMMIT_WRITING)
  {
    if (JobResult != NVM_REQ_OK)
    { /* Write request aborted or otherwise failed. */
      Dem_Nvm_SetCurrentCommitState(DEM_NVM_COMMIT_FAILED);
    }
    else
    {
      /* Continue with next block */
      Dem_Nvm_SetCurrentCommitState(DEM_NVM_COMMIT_FINISHED);
    }
  }
  /* else: the NvM has finished with some job,  e.g. restoring a block
     during ReadAll.
     We must ignore these notifications, since the value passed as
     ServiceId is not specified. */
# else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(JobResult)                                                                                    /* PRQA S 3112 */ /* MD_DEM_14.2 */
# endif
}
#endif

/* ****************************************************************************
 % Dem_Nvm_Init
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_Init(
  void
  )
{
#if (DEM_CFG_USE_NVM == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_SHUTDOWN) == TRUE)
  {
    Dem_Nvm_InitWakeup();
  }
  else
  {
    Dem_Nvm_InitStartup();
  }

  Dem_Scheduler_EnableTask(Dem_Scheduler_Task_NvM);
#endif
}

#if (DEM_CFG_USE_NVM == STD_ON)
/* ****************************************************************************
 % Dem_Nvm_Shutdown
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
Dem_Nvm_Shutdown(
  void
  )
{
  Dem_Cfg_MemoryIndexType lBlockIndex;

# if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
#  if (DEM_FEATURE_NEED_EVENTAVAILABLE_NV == STD_ON)
  /* Process queued modification status of the status data block */
  if (Dem_Nvm_PendingEventAvailabilityBlockState != DEM_NVM_BLOCKSTATE_UNMODIFIED)
  {
    Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_AVAILABILITY),
                                Dem_Nvm_PendingEventAvailabilityBlockState);
    Dem_Nvm_PendingEventAvailabilityBlockState = DEM_NVM_BLOCKSTATE_UNMODIFIED;
  }
#  endif
# endif

  for (lBlockIndex = 0u; lBlockIndex < Dem_Cfg_GlobalNvBlockCount(); ++lBlockIndex)
  {
    if (Dem_Nvm_GetPrivateBlockState(lBlockIndex) != DEM_NVM_BLOCKSTATE_UNMODIFIED)
    {
      (void)NvM_SetRamBlockStatus((NvM_BlockIdType)Dem_Cfg_MemoryBlockId[lBlockIndex], TRUE);
    }
  }

# if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
  Dem_Nvm_SetCurrentBlockIndex(0);
  Dem_Nvm_ResetPendingCommits();
  Dem_Nvm_SetCurrentCommitState(DEM_NVM_COMMIT_IDLE);
#  if (DEM_CFG_CLEAR_NV_END_RESPONSE == STD_ON)
  Dem_Nvm_ResetPendingClearCommits();
  Dem_Nvm_SetCurrentBlockIsCleared(FALSE);
#  endif
# endif
}                                                                                                                                /* PRQA S 6010, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCAL */
#endif /* (DEM_CFG_USE_NVM == STD_ON) */

/* ****************************************************************************
 % Dem_Nvm_MainFunction
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
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_MainFunction(
  void
  )
{
#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
  Dem_Nvm_ProcessQueue();

  /* Check for ongoing NV commit */
  if (Dem_Nvm_TestPendingCommits() == TRUE)
  {
# if (DEM_CFG_SUPPORT_NVM_POLLING == STD_ON)
    Dem_Nvm_GetNvMResult();
# endif

    switch (Dem_Nvm_GetCurrentCommitState())
    {
    case DEM_NVM_COMMIT_FAILED:
      {
        /* Error handling:
           This implementation will mark the block as dirty in case of failed
           NvM_WriteBlock. Another immediate update is done only if the block
           changes again */
        (void)NvM_SetRamBlockStatus((NvM_BlockIdType)Dem_Cfg_MemoryBlockId[Dem_Nvm_GetCurrentBlockIndex()], TRUE);
# if (DEM_CFG_CLEAR_NV_END_RESPONSE == STD_ON)
        if (Dem_Nvm_TestCurrentBlockIsCleared() == TRUE)
        {
          Dem_ClearTask_NotifyClearWriteError();
        }
# endif
      }
    /* FALL THROUGH */

    case DEM_NVM_COMMIT_FINISHED:                                                                                                /* PRQA S 2003 */ /* MD_DEM_15.2 */
      {
        /* Post-processing of NV update */
        Dem_Nvm_DecrementPendingCommits();
# if (DEM_CFG_CLEAR_NV_END_RESPONSE == STD_ON)
        if (Dem_Nvm_TestCurrentBlockIsCleared() == TRUE)
        {
          Dem_Nvm_SetCurrentBlockIsCleared(FALSE);
          Dem_Nvm_DecrementPendingClearCommits();
          if (Dem_Nvm_TestPendingClearCommits() == FALSE)
          {
            Dem_ClearTask_NotifyClearCompleted();
          }
        }
# endif
      }
    /* FALL THROUGH */

    case DEM_NVM_COMMIT_IDLE:                                                                                                    /* PRQA S 2003 */ /* MD_DEM_15.2 */
      {
        /* Look for next dirty/immediate NV block */
        if (Dem_Nvm_TestPendingCommits() == TRUE)
        {
          if (Dem_Nvm_FindNextBlockToCommit() == FALSE)
          {
            Dem_Nvm_SetCurrentCommitState(DEM_NVM_COMMIT_IDLE);
            break; /* We will continue looking for the pending block in the next task */
          }

          Dem_Nvm_CommitBlock();
        }
        else
        {
          Dem_Nvm_SetCurrentCommitState(DEM_NVM_COMMIT_IDLE);
        }
      }
      break;

    default:                                                                                                                     /* PRQA S 2016 */ /* MD_MSR_EmptyClause */
      /* DEM_NVM_COMMIT_WRITING - NvM is still busy, do nothing until this changes (no timeout) */
      break;

    } /* end switch */
  } /* end if (Dem_Nvm_TestPendingCommits() == TRUE) */
#endif /* (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON) */
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

#if (DEM_CFG_SUPPORT_NVM_APPL_SYNCHRONIZE == STD_ON) && (DEM_CFG_USE_NVM == STD_ON)
/* ****************************************************************************
 % Dem_Nvm_SetSynchronizationFlag
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_SetSynchronizationFlag(
    void
    )
{
  Dem_Nvm_IsSynchronizationRequested = TRUE;
}
#endif /* (DEM_CFG_SUPPORT_NVM_APPL_SYNCHRONIZE == STD_ON) && (DEM_CFG_USE_NVM == STD_ON) */

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_NVM_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Nvm_Implementation.h
 *********************************************************************************************************************/
