/**********************************************************************************************************************
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
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  NvM_Qry.c
 *        \brief  NvM query submodule source file
 *      \details  This sub-module implements the queries to be executed to evaluate the conditions
 *                for a state transition
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#define NVM_QRY_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
/* NvM_JobProc.h includes all needed headers, e.g. configuration, action, query... */
#include "NvM_JobProc.h"
#include "NvM_Queue.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#ifndef NVM_LOCAL /* COV_NVM_COMPATIBILITY */
# define NVM_LOCAL static
#endif


/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define NVM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 * NvM_QryBlockRelevantForWriteAll
 *********************************************************************************************************************/
/*! \brief Check if the block is relevant for NvM_WriteAll().
 *  \details -
 *  \return TRUE block shall be written during WriteAll
 *  \return FALSE otherwise
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryBlockRelevantForWriteAll(void);

/**********************************************************************************************************************
 * NvM_QryCancelWriteAll
 *********************************************************************************************************************/
/*! \brief Checks whether a NvM_CancelWriteAll request was setup.
 *  \details Checks whether a NvM_CancelWriteAll request was setup.
 *  \return TRUE CancelWriteAll setup
 *  \return FALSE otherwise
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryCancelWriteAll(void);

#if (NVM_KILL_WRITEALL_API == STD_ON)
/**********************************************************************************************************************
 * NvM_QryWriteAllKilled
 *********************************************************************************************************************/
/*! \brief Checks whether a NvM_KillWriteAll request was setup.
 *  \details Checks whether a NvM_KillWriteAll request was setup.
 *  \return TRUE KillWriteAll setup
 *  \return FALSE otherwise
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \config KillWriteAll is enabled
 *  \pre -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryWriteAllKilled(void);
#endif /* (NVM_KILL_WRITEALL_API == STD_ON) */

/**********************************************************************************************************************
 * NvM_QryCrcMatch
 *********************************************************************************************************************/
/*! \brief Check whether the recalculated Crc matches the read one, in case the is a configured Crc.
 *  \details Check whether the recalculated Crc matches the read one, in case the is a configured Crc.
 *  \return TRUE Crc matches
 *  \return FALSE no Crc configured or the Crc does not match
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryCrcMatch(void);

/**********************************************************************************************************************
 * NvM_QryCrcBusy
 *********************************************************************************************************************/
/*! \brief Checks the current block CRC calculation state.
 *  \details -
 *  \return TRUE if the CRC is busy, FALSE otherwise.
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryCrcBusy(void);

/**********************************************************************************************************************
 * NvM_QryDataCopyBusy
 *********************************************************************************************************************/
/*!
 * \brief       Checks the current block's ByteCount value.
 * \details     -
 * \return      TRUE, if ByteCount > 0, FALSE otherwise.
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 * \pre         -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryDataCopyBusy(void);

/**********************************************************************************************************************
 * NvM_QryLastBlockDone_ReadAll
 *********************************************************************************************************************/
/*! \brief Check whether the NvM_ReadAll job is finished.
 *  \details Check whether the NvM_ReadAll job is finished.
 *  \return TRUE NvM_ReadAll job is finished
 *  \return FALSE otherwise
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryLastBlockDone_ReadAll(void);

/**********************************************************************************************************************
 * NvM_QryLastBlockDone_WriteAll
 *********************************************************************************************************************/
/*! \brief Checks whether the NvM_WriteAll job is finished.
 *  \details Checks whether the NvM_WriteAll job is finished.
 *  \return TRUE WriteAll job is finished
 *  \return FALSE otherwise
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryLastBlockDone_WriteAll(void);

/**********************************************************************************************************************
 * NvM_QryLastResultOk
 *********************************************************************************************************************/
/*! \brief Checks whether the last MemIf job was successful.
 *  \details Checks whether the last MemIf job was successful.
 *  \return TRUE last MemIf job was successful
 *  \return FALSE otherwise
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryLastResultOk(void);

/**********************************************************************************************************************
 * NvM_QryMainFsmRunning
 *********************************************************************************************************************/
/*! \brief Checks whether the main-FSM is currently pending.
 *  \details Checks whether the main-FSM is currently pending.
 *  \return TRUE main-FSM is pending
 *  \return FALSE otherwise
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryMainFsmRunning(void);

/**********************************************************************************************************************
 * NvM_QryMultiJob
 *********************************************************************************************************************/
/*! \brief Checks whether a multi block job is requested.
 *  \details Checks whether a multi block job is requested.
 *  \return TRUE multi block job is setup
 *  \return FALSE otherwise
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryMultiJob(void);

/**********************************************************************************************************************
 * NvM_QryNvBusy
 *********************************************************************************************************************/
/*! \brief Checks whether the underlying module for current job is busy.
 *  \details we differ between polling mode on and off: in case we are running in polling mode and the corresponding
 *           underlying module is not busy, we set the current job result, too. In case we are running with polling
 *           mode off, we set the job to pending - the underlying module has to invoke the corresponding job-end or
 *           job-error callback to signal a finished job.
 *  \return TRUE underlying module is busy
 *  \return FALSE otherwise
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryNvBusy(void);

/**********************************************************************************************************************
 * NvM_QryMemHwaBusy
 *********************************************************************************************************************/
/*! \brief Check whether the underlying modules are busy.
 *  \details Check whether the underlying modules are busy.
 *  \return TRUE at least one underlying module is busy
 *  \return FALSE otherwise
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryMemHwaBusy(void);

/**********************************************************************************************************************
 * NvM_QryPrimaryRedundantBlock
 *********************************************************************************************************************/
/*!
 * \brief           Test if the current block has been configured redundant AND addresses the primary redundant block
 * \details         -
 * \return          TRUE if current block is redundant and primary redundant block, FALSE otherwise
 * \pre             -
 * \context         TASK
 * \reentrant       TRUE
 * \synchronous     TRUE
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryPrimaryRedundantBlock(void);

/**********************************************************************************************************************
 *  NvM_QrySecondaryRedundantBlock
 *********************************************************************************************************************/
/*!
 * \brief           Test if the current block has been configured redundant AND addresses the secondary redundant block
 * \details         -
 * \return          TRUE if current block is redundant and secondary redundant block, FALSE otherwise
 * \pre             -
 * \context         TASK
 * \reentrant       TRUE
 * \synchronous     TRUE
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QrySecondaryRedundantBlock(void);

/**********************************************************************************************************************
 * NvM_QrySkipBlock
 *********************************************************************************************************************/
/*! \brief Checks whether the block is not selected for NvM_ReadAll-job or it isn't a dataset block (shall be skipped)
 *  \details Checks whether the block is not selected for NvM_ReadAll-job or it isn't a dataset block (shall be skipped)
 *  \return TRUE block shall be skipped
 *  \return FALSE otherwise
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QrySkipBlock(void);

/**********************************************************************************************************************
 * NvM_QrySubFsmRunning
 *********************************************************************************************************************/
/*! \brief Checks whether the sub-FSM is currently pending.
 *  \details Checks whether the sub-FSM is currently pending.
 *  \return TRUE sub-FSM is pending
 *  \return FALSE otherwise
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QrySubFsmRunning(void);

/**********************************************************************************************************************
 * NvM_QryTrue
 *********************************************************************************************************************/
/*! \brief Simply returns TRUE.
 *  \details Simply returns TRUE.
 *  \return always TRUE
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryTrue(void);

/**********************************************************************************************************************
 * NvM_QryWriteBlockOnce
 *********************************************************************************************************************/
/*! \brief Checks whether the block is a write once block.
 *  \details Checks whether the block is a write once block.
 *  \return TRUE in case the current block is write once
 *  \return FALSE otherwise
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryWriteBlockOnce(void);

/**********************************************************************************************************************
 * NvM_QryWriteRetriesExceeded
 *********************************************************************************************************************/
/*! \brief Checks whether the current number of write retries do not exceed the allowed boundary.
 *  \details Checks whether the current number of write retries do not exceed the allowed boundary.
 *  \return FALSE in case the write retries counter exceeded
 *  \return TRUE otherwise
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryWriteRetriesExceeded(void);

/**********************************************************************************************************************
 * NvM_QryHasRom
 *********************************************************************************************************************/
/*! \brief Checks whether the current block has defaults (ROM block or Init callback)
 *  \details Checks whether the current block has defaults (ROM block or Init callback)
 *  \return FALSE block has no defaults
 *  \return TRUE otherwise
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryHasRom(void);

/**********************************************************************************************************************
 * NvM_QryExtRuntime
 *********************************************************************************************************************/
/*! \brief Checks whether for current block the extended runtime preparation shall be executed.
 *  \details Checks whether for current block the extended runtime preparation shall be executed.
 *  \return FALSE normal runtime preparation shall be executed
 *  \return TRUE extended runtime preparation shall be executed
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryExtRuntime(void);

#if (NVM_REPAIR_REDUNDANT_BLOCKS_API == STD_ON)
/**********************************************************************************************************************
 * NvM_QrySuspendRepairRedundantBlocks
 *********************************************************************************************************************/
/*!
 * \brief Checks whether the pending background repair redundant blocks job shall be suspended (non-Destructively) or not.
 * \details Since the redundant block repairing is a background job, it can be suspended in a non-destructive way 
 *          by all possible jobs - single or multi block. This query checks whether there is a normal priority job,
 *          or multi block job (ReadAll or WriteAll). It does not care about the high priority jobs - NvM handles this itself.
 * \return FALSE 
 * \return TRUE 
 * \context TASK
 * \reentrant FALSE
 * \synchronous TRUE
 * \config Repair Redundant Blocks Api is enabled
 * \pre -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QrySuspendRepairRedundantBlocks(void);

/**********************************************************************************************************************
 * NvM_QryRepairRedBlockDefect
 *********************************************************************************************************************/
/*!
 * \brief Checks whether current redundant block can and shall be repaired or not.
 * \details We decide between three situations:
 *          1. both blocks are valid, nothing to repair
 *          2. both blocks are defect, NvM cannot repair
 *          3. only one block is defect, NvM will try to repair the redundancy
 * \return FALSE block does not have to be repaired or cannot be repaired
 * \return TRUE  block is defect and shall be repaired
 * \context TASK
 * \reentrant FALSE
 * \synchronous TRUE
 * \config Repair Redundant Blocks Api is enabled
 * \pre -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryRepairRedBlockDefect(void);
#endif

/**********************************************************************************************************************
 * NvM_QryCRCCompMechanismSkipWrite
 *********************************************************************************************************************/
/*!
 * \brief Checks whether the block writing shall be skipped because of CRCCompMechanism and clean block.
 * \details -
 * \return TRUE  if the block shall be skipped
 * \return FALSE if the block shall not be skipped
 * \context TASK
 * \reentrant FALSE
 * \synchronous TRUE
 * \config -
 * \pre -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryCRCCompMechanismSkipWrite(void);

/**********************************************************************************************************************
 * NvM_QryPostReadTransform
 *********************************************************************************************************************/
/*!
 * \brief       Invokes the post read transformation callback with the read data and returns its result.
 * \details     Within post read transformation the user can decide whether the data is valid or not - in case it isn't
 *              NvM shall behave same as in case the CRC does not match or there is no data.
 * \return      TRUE, if the post read transformation callback returns OK, or is not configured; FALSE otherwise
 * \pre         -
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryPostReadTransform(void);

/**********************************************************************************************************************
 * NvM_QryCsmRetryNecessary
 *********************************************************************************************************************/
/*! \brief Checks the last CSM job return value and whether the current number of CSM retries do not exceed the allowed boundary.
 *  \details -
 *  \return TRUE in case the last CSM job return value was either CRYPTO_E_BUSY or CRYPTO_E_QUEUE_FULL AND retries not exceeded
 *  \return FALSE otherwise
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryCsmRetryNecessary(void);

/**********************************************************************************************************************
 *  NvM_QryBlockCheckLossOfRedundancy
 *********************************************************************************************************************/
/*!
 * \brief           Checks if the current block has checking for loss of redundancy flag enabled
 * \details         -
 * \return          TRUE if flag is set, FALSE otherwise
 * \pre             -
 * \context         TASK
 * \reentrant       TRUE
 * \synchronous     TRUE
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryBlockCheckLossOfRedundancy(void);

/**********************************************************************************************************************
 *  NvM_QryFirstRedundantBlockFailed
 *********************************************************************************************************************/
/*!
 * \brief           Checks if the first redundant block state has an error marker
 * \details         -
 * \return          TRUE if any error flag is set, FALSE otherwise (block state==UPTODATE)
 * \pre             -
 * \context         TASK
 * \reentrant       TRUE
 * \synchronous     TRUE
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryFirstRedundantBlockFailed(void);

/**********************************************************************************************************************
 *  NvM_QryRedundantCrcMatches
 *********************************************************************************************************************/
/*!
 * \brief           Checks if primary and secondary CRC matches of a redundant block
 * \details         -
 * \return          TRUE if CRCs match, FALSE otherwise
 * \pre             Primary block must be read out successfully, secondary CRC data must be read.
 * \context         TASK
 * \reentrant       FALSE
 * \synchronous     TRUE
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryRedundantCrcMatches(void);

#define NVM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
#define NVM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

CONST(NvM_QryFctPtrType, NVM_PRIVATE_CONST) NvM_QueryTable_ap[(uint32)NVM_QRY_ID_TRUE + 1u] = /* PRQA S 1533 */ /* MD_NvM_8.9 */
{
    NvM_QryBlockRelevantForWriteAll,
    NvM_QryCancelWriteAll,
#if (NVM_KILL_WRITEALL_API == STD_ON)
    NvM_QryWriteAllKilled,
#endif
    NvM_QryCrcBusy,
    NvM_QryDataCopyBusy,
    NvM_QryCrcMatch,
    NvM_QryLastBlockDone_ReadAll,
    NvM_QryLastBlockDone_WriteAll,
    NvM_QryLastResultOk,
    NvM_QryMainFsmRunning,
    NvM_QryMultiJob,
#if (NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS)
    NvM_QryNormalPrioJob,
# if (NVM_JOB_PRIORISATION == STD_ON)
    NvM_QryHighPrioJob,
# endif
#endif
    NvM_QryNvBusy,
    NvM_QryMemHwaBusy,
#if (NVM_SET_RAM_BLOCK_STATUS_API == STD_ON)
    NvM_QryCalcRamBlockCrcEnabledAndRamValid,
#endif
    NvM_QryPrimaryRedundantBlock,
    NvM_QrySecondaryRedundantBlock,
    NvM_QrySkipBlock,
    NvM_QrySubFsmRunning,
    NvM_QryWriteBlockOnce,
    NvM_QryWriteRetriesExceeded,
    NvM_QryHasRom,
    NvM_QryExtRuntime,
#if (NVM_REPAIR_REDUNDANT_BLOCKS_API == STD_ON)
    NvM_QrySuspendRepairRedundantBlocks,
    NvM_QryRepairRedBlockDefect,
#endif
    NvM_QryCRCCompMechanismSkipWrite,
    NvM_QryPostReadTransform,
    NvM_QryReadAllKilled,
    NvM_QrySyncDecrypt,
    NvM_QrySyncEncrypt,
    NvM_QryCsmRetryNecessary,
    NvM_QryBlockCheckLossOfRedundancy,
    NvM_QryFirstRedundantBlockFailed,
    NvM_QryRedundantCrcMatches,
    NvM_QryTrue
};

#define NVM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS: PUBLISHED VIA NvM_QueryTable_ap
 *********************************************************************************************************************/
#define NVM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
*  NvM_QryBlockRelevantForWriteAll
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryBlockRelevantForWriteAll(void)
{
  boolean retVal_isRelevantForWriteAll = FALSE;

  boolean isSelectedForWriteAll = NvM_IsBooleanBitfieldTrue(
      NvM_CurrentBlockInfo_t.Descriptor_pt->Flags.SelectBlockForWriteAllEnabled);

  boolean isWriteableAndUnlocked =
      (NvM_CurrentBlockInfo_t.Mngmt_pt->NvRamAttributes_u8 & (NVM_WR_PROT_SET | NVM_LOCK_STAT_SET)) == 0u;

  if (isSelectedForWriteAll && isWriteableAndUnlocked)
  {
#if (NVM_SET_RAM_BLOCK_STATUS_API == STD_ON)
    boolean useSetRamBlockStatus = NvM_IsBooleanBitfieldTrue(
        NvM_CurrentBlockInfo_t.Descriptor_pt->Flags.BlockUseSetRamBlockStatusEnabled);

    if (useSetRamBlockStatus)
    {
      /* Block using NvMBlockUseSetRamBlockStatus feature -> write only if changed data was indicated via API */
      const NvM_BitFieldType bitfieldValidChanged = (NVM_STATE_CHANGED_SET | NVM_STATE_VALID_SET);
      retVal_isRelevantForWriteAll =
          (NvM_CurrentBlockInfo_t.Mngmt_pt->NvRamAttributes_u8 & bitfieldValidChanged) == bitfieldValidChanged;
    }
    else
    {
      /* Block not using NvMBlockUseSetRamBlockStatus feature -> must be written */
      retVal_isRelevantForWriteAll = TRUE;
    }
#else
    /* RAM block status API disabled -> all relevant block must be written */
    retVal_isRelevantForWriteAll = TRUE;
#endif
  }

  return retVal_isRelevantForWriteAll;
}

/**********************************************************************************************************************
*  NvM_QryCancelWriteAll
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryCancelWriteAll(void)
{
  return ((NvM_ApiFlags_u8 & NVM_APIFLAG_CANCEL_WR_ALL_SET) != 0u);
}

#if (NVM_KILL_WRITEALL_API == STD_ON)
/**********************************************************************************************************************
*  NvM_QryWriteAllKilled
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryWriteAllKilled(void)
{
    return (boolean)((NvM_CurrentJob_t.JobServiceId_t == NVM_INT_FID_WRITE_ALL) && 
        ((NvM_ApiFlags_u8 & NVM_APIFLAG_KILL_WR_ALL_SET) != 0u));
}
#endif /* (NVM_KILL_WRITEALL_API == STD_ON) */

/**********************************************************************************************************************
*  NvM_QryCrcMatch
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryCrcMatch(void)
{
    return (boolean)NvM_CrcJob_Compare(&NvM_CurrentBlockInfo_t.BlockCrcJob_t); /* SBSW_NvM_FuncCall_PtrParam_CurrBlockInfo */
}

/**********************************************************************************************************************
*  NvM_QryCrcBusy
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryCrcBusy(void)
{
    return (boolean)(NvM_CrcJob_isBusy(&NvM_CurrentBlockInfo_t.BlockCrcJob_t));
}

/**********************************************************************************************************************
*  NvM_QryDataCopyBusy
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryDataCopyBusy(void)
{
    return (boolean)(NvM_CurrentBlockInfo_t.ByteCount_u16 > 0u);
}

/**********************************************************************************************************************
*  NvM_QryLastBlockDone_ReadAll
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryLastBlockDone_ReadAll(void)
{
    return (boolean)(NvM_CurrentJob_t.JobBlockId_t >= NvM_NoOfBlockIds_t);
}

/**********************************************************************************************************************
*  NvM_QryLastBlockDone_WriteAll
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryLastBlockDone_WriteAll(void)
{
    return (boolean)(NvM_CurrentJob_t.JobBlockId_t == 0u);
}

/**********************************************************************************************************************
*  NvM_QryLastResultOk
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryLastResultOk(void)
{
    return (boolean)(NVM_REQ_OK == NvM_CurrentBlockInfo_t.LastResult_t);
}

/**********************************************************************************************************************
*  NvM_QryMainFsmRunning
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryMainFsmRunning(void)
{
    return (boolean)(NVM_STATE_FSM_FINISHED != NvM_JobMainState_t);
}

/**********************************************************************************************************************
*  NvM_QryMultiJob
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryMultiJob(void)
{
    return (boolean)((NvM_ApiFlags_u8 &
        (NVM_APIFLAG_WRITE_ALL_SET | NVM_APIFLAG_READ_ALL_SET 
#if (NVM_REPAIR_REDUNDANT_BLOCKS_API == STD_ON)  /* ECO_IGNORE_LINE */
        | NVM_APIFLAG_REPAIR_REDUNDANT_BLOCKS_SET
#endif  /* ECO_IGNORE_LINE */
        )) != 0u);
}

/**********************************************************************************************************************
*  NvM_QryNvBusy
**********************************************************************************************************************/
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
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryNvBusy(void)
{
#if(NVM_POLLING_MODE == STD_ON)
    const uint8 deviceId = (uint8)NvM_CurrentBlockInfo_t.Descriptor_pt->DeviceId_u8;
    boolean retVal = FALSE;

    if(NvM_CurrentBlockInfo_t.LastResult_t == NVM_REQ_PENDING)
    {
        if (MEMIF_BUSY == MemIf_GetStatus(deviceId))
        {
            retVal = TRUE;
        }
        else
        {
            switch(MemIf_GetJobResult(deviceId))
            {
                case MEMIF_JOB_OK:
                    NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_OK;
                    break;

                case MEMIF_BLOCK_INCONSISTENT:
                    NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_INTEGRITY_FAILED;
                    break;

                case MEMIF_BLOCK_INVALID:
                    NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_NV_INVALIDATED;
                    break;

                default:
                    NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_NOT_OK;
                    break;
            }
        }
    }
    return retVal;
#else
    return (boolean)(NvM_CurrentBlockInfo_t.LastResult_t == NVM_REQ_PENDING);
#endif
}

/**********************************************************************************************************************
*  NvM_QryMemHwaBusy
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryMemHwaBusy(void)
{
  const MemIf_StatusType MemHwaStatus = MemIf_GetStatus(MEMIF_BROADCAST_ID);

  return (boolean)((MemHwaStatus == MEMIF_BUSY) || (MemHwaStatus == MEMIF_BUSY_INTERNAL));
}

/**********************************************************************************************************************
*  NvM_QryPrimaryRedundantBlock
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryPrimaryRedundantBlock(void)
{
  return (boolean)(
      ((NvM_CurrentBlockInfo_t.Descriptor_pt->MngmtType_t & NVM_BLOCK_REDUNDANT) != 0u) &&
      ((NvM_CurrentBlockInfo_t.NvIdentifier_u16 & 0x0001u) == 0u));
}

/**********************************************************************************************************************
*  NvM_QrySecondaryRedundantBlock
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QrySecondaryRedundantBlock(void)
{
  return (boolean)(
      ((NvM_CurrentBlockInfo_t.Descriptor_pt->MngmtType_t & NVM_BLOCK_REDUNDANT) != 0u) &&
      ((NvM_CurrentBlockInfo_t.NvIdentifier_u16 & 0x0001u) == 1u));
}

/**********************************************************************************************************************
*  NvM_QrySkipBlock
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QrySkipBlock(void)
{
  return (boolean)(
      (NvM_IsBooleanBitfieldTrue(NvM_CurrentBlockInfo_t.Descriptor_pt->Flags.SelectBlockForReadAllEnabled) == FALSE)
#if (NVM_DYNAMIC_CONFIGURATION == STD_ON) /* ECO_IGNORE_LINE */
      || ((!NvM_QryHasRom()) && (NvM_QryExtRuntime())) /* PRQA S 3415 */ /* MD_NvM_13.5 */
#endif /* ECO_IGNORE_LINE */
      );
}

/**********************************************************************************************************************
*  NvM_QrySubFsmRunning
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QrySubFsmRunning(void)
{
  return (boolean)(NVM_STATE_FSM_FINISHED != NvM_JobSubState_t);
}

/**********************************************************************************************************************
*  NvM_QryTrue
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryTrue(void)
{
  return TRUE;
}

/**********************************************************************************************************************
*  NvM_QryWriteBlockOnce
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryWriteBlockOnce(void)
{
  boolean writeOnce = FALSE;

  if (NvM_IsBooleanBitfieldTrue(NvM_CurrentBlockInfo_t.Descriptor_pt->Flags.BlockWriteBlockOnceEnabled))
  {
#if(NVM_DYNAMIC_CONFIGURATION == STD_ON) /* ECO_IGNORE_LINE */
    if (!NvM_QryExtRuntime())
#endif /* ECO_IGNORE_LINE */
    {
      writeOnce = TRUE;
    }
  }

  return writeOnce;
}

/**********************************************************************************************************************
*  NvM_QryWriteRetriesExceeded
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryWriteRetriesExceeded(void)
{
  /* the initial try is also counted as retry. Therefore the total number of
       write retries may reach the configured number of attempts. */
  return (boolean)(NvM_CurrentBlockInfo_t.WriteRetryCounter_u8 > NVM_NOOFWRITEATTEMPTS);
}

#if ((NVM_SET_RAM_BLOCK_STATUS_API == STD_ON) || (NVM_CRC_INT_BUFFER == STD_ON))
/**********************************************************************************************************************
*  NvM_QryRamValid
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryCalcRamBlockCrcEnabledAndRamValid(void)
{
  return (NvM_IsBooleanBitfieldTrue(NvM_CurrentBlockInfo_t.Descriptor_pt->Flags.CalcRamBlockCrcEnabled)
      && ((NvM_CurrentBlockInfo_t.Mngmt_pt->NvRamAttributes_u8 & NVM_STATE_VALID_SET) == NVM_STATE_VALID_SET));         /* COV_NVM_NO_BLOCK_WITH_CALCRAMBLOCKCRC_CONFIGURED */
}
#endif /* ((NVM_SET_RAM_BLOCK_STATUS_API == STD_ON) || (NVM_CRC_INT_BUFFER == STD_ON)) */

/**********************************************************************************************************************
*  NvM_QryHasRom
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryHasRom(void)
{
  return (
      (NvM_CurrentBlockInfo_t.Descriptor_pt->RomBlockDataAddr_pt != NULL_PTR)
      || (NvM_QryIsInitCallbackConfigured(NvM_CurrentBlockInfo_t.Descriptor_pt)                                         /* PRQA S 3415 */ /* MD_NvM_13.5 */
          && NvM_IsBooleanBitfieldTrue(NvM_CurrentBlockInfo_t.Descriptor_pt->Flags.InvokeCallbacksForReadAllEnabled))   /* PRQA S 3415 */ /* MD_NvM_13.5 */
         );                                                                                                             /* SBSW_NvM_FuncCall_PtrParam_CurrBlockInfo */
}

/**********************************************************************************************************************
*  NvM_QryExtRuntime
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryExtRuntime(void)
{
#if (NVM_DYNAMIC_CONFIGURATION == STD_ON)
  return (
      (NvM_IsBooleanBitfieldTrue(NvM_CurrentBlockInfo_t.Descriptor_pt->Flags.ResistantToChangedSwEnabled) == FALSE)
      && ((NvM_CurrentBlockInfo_t.InternalFlags_u8 & NVM_INTFLAG_DYN_MISMATCH_SET) != 0u)
  );
#else
  return FALSE;
#endif
}

#if (NVM_REPAIR_REDUNDANT_BLOCKS_API == STD_ON)
/**********************************************************************************************************************
 * NvM_QrySuspendRepairRedundantBlocks
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QrySuspendRepairRedundantBlocks(void)
{
  /* we do not have to check the high priority job here - it is done within NvM processing */
  return (
#if (NVM_API_CONFIG_CLASS > NVM_API_CONFIG_CLASS_1) /* ECO_IGNORE_LINE */
      (NvM_QryNormalPrioJob()) ||
#endif /* ECO_IGNORE_LINE */
      ((NvM_ApiFlags_u8 & NVM_APIFLAG_READ_ALL_SET) != 0u) ||
      ((NvM_ApiFlags_u8 & NVM_APIFLAG_WRITE_ALL_SET) != 0u));
}

/**********************************************************************************************************************
 * NvM_QryRepairRedBlockDefect
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryRepairRedBlockDefect(void)
{
  boolean firstBlockOk = ((NvM_RepairRedBlockState.NvBlockState & 0x0Fu) == NVM_NVBLOCK_STATE_UPTODATE);
  boolean secondBlockOk = (((NvM_RepairRedBlockState.NvBlockState & 0xF0u) >> ((uint8)4u)) == NVM_NVBLOCK_STATE_UPTODATE);

  /* #10 block is defect in case one sub-block is already marked as defect, no matter whether the block has a Crc or not */
  boolean blockDefect = (firstBlockOk != secondBlockOk);

  /* #20 in case both sub-blocks are valid and the block is configured with Crc */
  if((firstBlockOk && secondBlockOk) && (NvM_CurrentBlockInfo_t.Descriptor_pt->CrcSettings != NVM_BLOCK_USE_CRC_OFF))
  {
    /* #21 check whether the Crc values fit to each other - block is defect in case the Crcs differ! */
    blockDefect = (boolean)(NvM_RepairRedBlockState.CrcBuffer != NvM_CurrentBlockInfo_t.BlockCrcJob_t.CurrentCrcValue);

    /* #22 for different Crcs we assume the second block is defect - NvM shall repair it (overwrite with first block data) */
    if(blockDefect == TRUE)
    {
      NvM_RepairRedBlockState.NvBlockState |= (NVM_NVBLOCK_STATE_DEFECT << 4);
    }
  }

  return blockDefect;
}
#endif

/**********************************************************************************************************************
 * NvM_QryCRCCompMechanismSkipWrite
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryCRCCompMechanismSkipWrite(void)
{
  boolean skipWrite = FALSE;

  if(NvM_CurrentBlockInfo_t.Descriptor_pt->CRCCompMechanismCrcAddr_t != NULL_PTR)
  {
    NvM_CrcJob_ImportBufferedValue(
        &NvM_CurrentBlockInfo_t.BlockCrcJob_t,
        NvM_CurrentBlockInfo_t.Descriptor_pt->CRCCompMechanismCrcAddr_t); /* SBSW_NvM_FuncCall_PtrParam_CurrBlockInfo */

    skipWrite = NvM_CrcJob_Compare(&NvM_CurrentBlockInfo_t.BlockCrcJob_t); /* SBSW_NvM_FuncCall_PtrParam_CurrBlockInfo */
  }

  return skipWrite;
}

/**********************************************************************************************************************
 * NvM_QryPostReadTransform
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryPostReadTransform(void)
{
  boolean retVal = TRUE;

  if(NvM_CurrentBlockInfo_t.Descriptor_pt->CbkPostReadTransform != NULL_PTR)
  {
    retVal = (NvM_CurrentBlockInfo_t.Descriptor_pt->CbkPostReadTransform(
        NvM_CurrentJob_t.JobBlockId_t, /* SBSW_NvM_FuncPtrCall_UserCallbacks */
        NvM_CurrentBlockInfo_t.RamAddr_t, /* PRQA S 0315 */ /* MD_NvM_Dir1.1_CastToVoidPtr */
        NvM_CurrentBlockInfo_t.Descriptor_pt->NvBlockLength_u16) == E_OK);
  }

  return retVal;
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  NvM_QryReadAllKilled
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryReadAllKilled(void)
{
  return ((NvM_ApiFlags_u8 & NVM_APIFLAG_KILL_READ_ALL_SET) == NVM_APIFLAG_KILL_READ_ALL_SET);
}

/**********************************************************************************************************************
*  NvM_QryIsInitCallbackConfigured
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryIsInitCallbackConfigured(NvM_BlockDescrPtrType BlockDescriptor)
{
  return ((BlockDescriptor->InitCbkFunc_pt != NULL_PTR) || (BlockDescriptor->InitCbkExtFunc_pt != NULL_PTR));
}

#if (NVM_USE_CSM == STD_ON)
/**********************************************************************************************************************
 * NvM_QryIsCipherBlock
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryIsCipherBlock(NvM_BlockDescrPtrType BlockDescriptor)
{
  return (BlockDescriptor->NvCryptoReference < NVM_NR_OF_CSM_JOBS);
}
#endif /* (NVM_USE_CSM == STD_ON) */

/**********************************************************************************************************************
 * NvM_QrySyncDecrypt
 *********************************************************************************************************************/
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
FUNC(boolean, NVM_PRIVATE_CODE) NvM_QrySyncDecrypt(void)
{
  /* #100 CSM enabled and the current block has a CSM job reference (must be decrypted). */
#if (NVM_USE_CSM == STD_ON)
    boolean retVal = FALSE;
    if(NvM_QryIsCipherBlock(NvM_CurrentBlockInfo_t.Descriptor_pt) == TRUE) /* SBSW_NvM_FuncCall_PtrParam_CurrBlockInfo */
    {
      /* #110 Decrypt data and check the result length: only in case the CSM returns E_OK and the length matches
       * the configured user data length, the decryption is successful! */
      /* Initialize with the expected length for test purposes only, real CSM will overwrite the value with
       * actual length of the decrypted data. */
      uint32 decryptResultLength = NvM_CurrentBlockInfo_t.Descriptor_pt->NvBlockLength_u16;

      NvM_CurrentBlockInfo_t.CsmJobReturnValue_u8 = Csm_Decrypt(NvM_CsmJobs[NvM_CurrentBlockInfo_t.Descriptor_pt->NvCryptoReference].DecryptJobId, NVM_CSM_OP_MODE, /* SBSW_NvM_FuncCall_PtrParam_Csm */
          /* Do not add the CRC length here!!! the NVRAMDataLength stores the length of the ciphered data! */
          NvM_CurrentBlockInfo_t.NvRamAddr_t, NvM_CurrentBlockInfo_t.Descriptor_pt->NvBlockNVRAMDataLength,
          NvM_CurrentBlockInfo_t.RamAddr_t, &decryptResultLength);

      /* #120 Update counter for every CSM job set up */
      NvM_CurrentBlockInfo_t.CsmJobRetryCounter_u8++;

      if(NvM_CurrentBlockInfo_t.CsmJobReturnValue_u8 == E_OK)
      {
          if(decryptResultLength == NvM_CurrentBlockInfo_t.Descriptor_pt->NvBlockLength_u16)
          {
              /* #121 Successful decryption, user buffer holds the encrypted data. */
              retVal = TRUE;
          }
      }
    }
    /* #200 CSM disabled, or the passed block does not have any CSM job reference (shall not be decrypted) -> return TRUE,
     * everything is fine, not touching the data. */
    else
    {
        retVal = TRUE;
    }
    return retVal;
#else
    return TRUE;
#endif
}

/**********************************************************************************************************************
 * NvM_QrySyncEncrypt
 *********************************************************************************************************************/
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
FUNC(boolean, NVM_PRIVATE_CODE) NvM_QrySyncEncrypt(void)
{
  /* #100 CSM enabled and the current block has a CSM job reference (must be encrypted). */
#if (NVM_USE_CSM == STD_ON)
  boolean retVal = FALSE;
  if(NvM_QryIsCipherBlock(NvM_CurrentBlockInfo_t.Descriptor_pt) == TRUE) /* SBSW_NvM_FuncCall_PtrParam_CurrBlockInfo */
  {
    /* #110 Encrypt data and check the result length: only in case the CSM returns E_OK and the length matches
     * the configured NV RAM data length, the encryption is successful! */
    /* Initialize with the expected length for test purposes only, real CSM will overwrite the value with
     * actual length of the encrypted data. */
    uint32 encryptResultLength = NvM_CurrentBlockInfo_t.Descriptor_pt->NvBlockNVRAMDataLength;

    NvM_CurrentBlockInfo_t.CsmJobReturnValue_u8 = Csm_Encrypt(NvM_CsmJobs[NvM_CurrentBlockInfo_t.Descriptor_pt->NvCryptoReference].EncryptJobId, NVM_CSM_OP_MODE, /* SBSW_NvM_FuncCall_PtrParam_Csm */
            /* Do not add the CRC length here!!! the NvBlockLength stores the number of bytes to cipher! */
            NvM_CurrentBlockInfo_t.RamAddr_t, NvM_CurrentBlockInfo_t.Descriptor_pt->NvBlockLength_u16,
            NvM_CurrentBlockInfo_t.NvRamAddr_t, &encryptResultLength);

    /* #120 Update counter for every CSM job set up */
    NvM_CurrentBlockInfo_t.CsmJobRetryCounter_u8++;

    if(NvM_CurrentBlockInfo_t.CsmJobReturnValue_u8 == E_OK)
    {
        if(encryptResultLength == NvM_CurrentBlockInfo_t.Descriptor_pt->NvBlockNVRAMDataLength)
        {
            /* #121 Successful encryption, internal cipher data buffer holds the encrypted data. */
            retVal = TRUE;
        }
    }
  }
  /* #200 CSM disabled, or the passed block does not have any CSM job reference (shall not be encrypted) -> return TRUE,
   * everything is fine, not touching the data. */
  else
  {
      retVal = TRUE;
  }
  return retVal;
#else
    return TRUE;
#endif
}

/**********************************************************************************************************************
* NvM_QryCsmRetryNecessary
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryCsmRetryNecessary(void)
{
  /* #10 CSM enabled and the current block has a CSM job reference */
#if (NVM_USE_CSM == STD_ON)
    /* the initial try is also counted as retry. Therefore the total number of
       CSM retries is incremented. */
    return (boolean)(
        ((NvM_CurrentBlockInfo_t.CsmJobReturnValue_u8 == CRYPTO_E_BUSY)
            || (NvM_CurrentBlockInfo_t.CsmJobReturnValue_u8 == CRYPTO_E_QUEUE_FULL)
        )
        && (NvM_CurrentBlockInfo_t.CsmJobRetryCounter_u8 < (NVM_CSM_RETRY_COUNT + 1u))); /* COV_NVM_CSM_RETRY_ZERO */
#else
    return FALSE;
#endif
}

/**********************************************************************************************************************
 *  NvM_QryBlockCheckLossOfRedundancy
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryBlockCheckLossOfRedundancy(void)
{
  return NvM_IsBooleanBitfieldTrue(NvM_CurrentBlockInfo_t.Descriptor_pt->Flags.BlockCheckLossOfRedundancyEnabled);
}

/**********************************************************************************************************************
 *  NvM_QryBlockCheckLossOfRedundancy
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryFirstRedundantBlockFailed(void)
{
  return NVM_EXTRACT_NVSTATE_PRIMARY(NvM_CurrentBlockInfo_t.NvState_u8) != NVM_NVBLOCK_STATE_UPTODATE;
}

/**********************************************************************************************************************
 *  NvM_QryRedundantCrcMatches
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryRedundantCrcMatches(void)
{
  /* Note: This requires that the primary redundant block was read and checked successfully for integrity + secondary
   *       CRC data was read from NV.
   */
  return NvM_CrcJob_CompareToExternal(&NvM_CurrentBlockInfo_t.BlockCrcJob_t, NvM_SecondaryRedundantBlockCrcData);       /* SBSW_NvM_FuncCall_PtrParam_CurrBlockInfo */
}

#define NVM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  END OF FILE: NvM_Qry.c
 *********************************************************************************************************************/
