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
/*!        \file  NvM_Act.c
 *        \brief  NvM action sub module source file
 *      \details  This sub-module implements all state machines' action handlers to be executed upon state transitions.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#define NVM_ACT_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
/* NvM_JobProc.h includes all needed headers, e.g. configuration, action, query... */
#include "NvM_JobProc.h"
#include "NvM_Queue.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
/* define the maximum number of bytes to by copied by NVM MainFunction.                             *
 * We want to limit maximum run-time of NvM_MainFunction (make it independent from block-size).     *
 * It is derived from NvM_NoOfCrcBytes_u16, however, the factor was arbitrarily chosen.             */
#define NVM_MAX_DATA_COPY_BYTES (NvM_NoOfCrcBytes_u16 << 2)


/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/
#ifndef NVM_LOCAL /* COV_NVM_COMPATIBILITY */
# define NVM_LOCAL static
#endif

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/
#define NVM_START_SEC_VAR_NO_INIT_8
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Test buffer of size 1 byte for readability of a block (e.g. redundant block). */
NVM_LOCAL VAR(uint8, NVM_PRIVATE_DATA) NvM_TestBuffer_u8; /* PRQA S 3218 */ /* MD_NvM_8.9_TestBuffer */

#define NVM_STOP_SEC_VAR_NO_INIT_8
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES: PUBLISHED VIA NvM_ActionTable_ap
 *********************************************************************************************************************/
#define NVM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  ACTION HANDLER FUNCTIONS
 *  They are PRIVATE, i.e. they will be called only
 *  inside the NVM. Normally this means "from same segment".
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * NvM_ActSetInitialAttr
 *********************************************************************************************************************/
/*! \brief Set block to write protected if the block is configured with write once true.
 *  \details -
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActSetInitialAttr(void);

/**********************************************************************************************************************
 * NvM_ActInitMainFsm
 *********************************************************************************************************************/
/*! \brief Initialize the main state machine.
 *  \details -
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitMainFsm(void);

/**********************************************************************************************************************
 * NvM_ActInitBlock
 *********************************************************************************************************************/
/*! \brief Initialize the next block to be processed.
 *  \details -
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitBlock(void);

/**********************************************************************************************************************
 * NvM_ActInitReadAll
 *********************************************************************************************************************/
/*! \brief Initialize the ReadAll job.
 *  \details -
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitReadAll(void);

/**********************************************************************************************************************
 * NvM_ActInitReadBlockSubFsm
 *********************************************************************************************************************/
/*! \brief Initialize the ReadBlock state machine.
 *  \details -
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitReadBlockSubFsm(void);

/**********************************************************************************************************************
 * NvM_ActInitRestoreBlockDefaultsSubFsm
 *********************************************************************************************************************/
/*!
 * \brief Initializes the RestoreRomDefaults state machine.
 * \details -
 * \context TASK
 * \reentrant FALSE
 * \synchronous TRUE
 * \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitRestoreBlockDefaultsSubFsm(void);

/**********************************************************************************************************************
 * NvM_ActInitWriteAll
 *********************************************************************************************************************/
/*! \brief Initialize the WriteAll job.
 *  \details -
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitWriteAll(void);

/**********************************************************************************************************************
 * NvM_ActInitWriteBlock
 *********************************************************************************************************************/
/*! \brief Initialize the current pending block for a WriteBlock job.
 *  \details -
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitWriteBlock(void);

/**********************************************************************************************************************
 * NvM_ActInitWriteBlockFsm
 *********************************************************************************************************************/
/*! \brief Initialize the WriteBlock FSM as Sub-State Machine
 *  \details -
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitWriteBlockFsm(void);

/**********************************************************************************************************************
 * NvM_ActInitRestoreBlockDefaults
 *********************************************************************************************************************/
/*! \brief Initialize current pending block for a RestoreBlockDefaults job.
 *  \details -
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitRestoreBlockDefaults(void);

/**********************************************************************************************************************
 * NvM_ActFinishMainJob
 *********************************************************************************************************************/
/*! \brief Finish current pending job - multi block or single block.
 *  \details -
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActFinishMainJob(void);

#if (NVM_KILL_WRITEALL_API == STD_ON)
/**********************************************************************************************************************
 * NvM_ActKillWriteAll
 *********************************************************************************************************************/
/*! \brief Kill current pending WriteAll-job
 *  \details Finalizes sub FSMs, cleans up internal variables, doesn't set any job result (was set in NvM_KillWritAll API)
 *           Precondition: only called, if QryWriteAllKilled was true - we don't need to check again.
 *           Must be called from Main FSM => because it terminates all SubFsms.
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \config KillWriteAll API is enabled
 *  \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActKillWriteAll(void);
#endif /* (NVM_KILL_WRITEALL_API == STD_ON) */

/**********************************************************************************************************************
 * NvM_ActFinishBlock
 *********************************************************************************************************************/
/*! \brief Finish current pending job.
 *  \details -
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActFinishBlock(void);

/**********************************************************************************************************************
 * NvM_ActInitNextBlockReadAll
 *********************************************************************************************************************/
/*! \brief Initialize next block to be read during ReadAll job.
 *  \details -
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitNextBlockReadAll(void);

/**********************************************************************************************************************
 * NvM_ActInitNextBlockWriteAll
 *********************************************************************************************************************/
/*! \brief Initialize next block to be written during WriteAll job.
 *  \details -
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitNextBlockWriteAll(void);

/**********************************************************************************************************************
 * NvM_ActFinishCfgIdCheck
 *********************************************************************************************************************/
/*! \brief Finalize Block 1 and Configuration Id check during ReadAll processing.
 *  \details -
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 *  \trace CREQ-754
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActFinishCfgIdCheck(void);

/**********************************************************************************************************************
 * NvM_ActFinishReadBlock
 *********************************************************************************************************************/
/*! \brief Finish current ReadBlock job.
 *  \details -
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActFinishReadBlock(void);

/**********************************************************************************************************************
 * NvM_ActFinishWriteBlock
 *********************************************************************************************************************/
/*! \brief Finish current WriteBlock job.
 *  \details -
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActFinishWriteBlock(void);

#if (NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3)
/**********************************************************************************************************************
 * NvM_ActFinishEraseBlock
 *********************************************************************************************************************/
/*! \brief Finish current Erase or Invalidate job.
 *  \details Finishes block processing, evaluates result and reports error to DEM, if processing failed.
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \config NvM Configuration Class is set to 3
 *  \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActFinishEraseBlock(void);

/**********************************************************************************************************************
 * NvM_ActEraseNvBlock
 *********************************************************************************************************************/
/*! \brief Process Erase job.
 *  \details -
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \config NvM Configuration Class is set to 3
 *  \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActEraseNvBlock(void);

/**********************************************************************************************************************
 * NvM_ActInvalidateNvBlock
 *********************************************************************************************************************/
/*! \brief Process Invalidate job.
 *  \details -
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \config NvM Configuration Class is set to 3
 *  \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActInvalidateNvBlock(void);
#endif /* (NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3) */

/**********************************************************************************************************************
 * NvM_ActProcessCrc
 *********************************************************************************************************************/
/*! \brief Process Crc calculation.
 *  \details -
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActProcessCrc(void);

/**********************************************************************************************************************
 * NvM_ActWriteNvBlock
 *********************************************************************************************************************/
/*! \brief Process WriteBlock job.
 *  \details -
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActWriteNvBlock(void);

/**********************************************************************************************************************
 * NvM_ActReadNvBlock
 *********************************************************************************************************************/
/*! \brief Process ReadBlock job.
 *  \details -
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActReadNvBlock(void);

/**********************************************************************************************************************
 * NvM_ActReadNvBlockCrcOnly
 *********************************************************************************************************************/
/*!
 * \brief       Set up MemIf read job for CRC data of the current block.
 * \details     Currently only used for the detection of loss-of-redundancy.
 * \pre         -
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 * \note        Targets extra buffer NvM_RedundantBlockCrcData.
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActReadNvBlockCrcOnly(void);

/**********************************************************************************************************************
 * NvM_ActProcessCrcRead
 *********************************************************************************************************************/
/*! \brief Trigger Crc calculation.
 *  \details -
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActProcessCrcRead(void);

/**********************************************************************************************************************
 * NvM_ActReadCopyData
 *********************************************************************************************************************/
/*!
 * \brief       Copy the read data to target.
 * \details     Copy from internal buffer to the user buffer, invoke explicit synchronization - what ever necessary.
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 * \pre         -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActReadCopyData(void);

/**********************************************************************************************************************
 * NvM_ActRestoreRomDefaults
 *********************************************************************************************************************/
/*! \brief Process RestoreBlockDefaults job.
 *  \details -
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActRestoreRomDefaults(void);

/**********************************************************************************************************************
 * NvM_ActFinishRestoreRomDefaults
 *********************************************************************************************************************/
/*! \brief Finish RestoreBlockDefaults job.
 *  \details -
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActFinishRestoreRomDefaults(void);

/**********************************************************************************************************************
 * NvM_ActTestBlockBlank
 *********************************************************************************************************************/
/*! \brief Check whether the current pending block can be read or not.
 *  \details -
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActTestBlockBlank(void);

/**********************************************************************************************************************
 * NvM_ActValidateRam
 *********************************************************************************************************************/
/*! \brief If current RAM Block is permanent, mark it valid and unchanged.
 *  \details -
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActValidateRam(void);

/**********************************************************************************************************************
 * NvM_ActSetupRedundant
 *********************************************************************************************************************/
/*! \brief Setup Redundant NV Block and reset write retries.
 *  \details -
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActSetupRedundant(void);

/**********************************************************************************************************************
 * NvM_ActSetupOther
 *********************************************************************************************************************/
/*! \brief Setup the other NV Block at redundant blocks and reset write retries
 *  \details -
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActSetupOther(void);

/**********************************************************************************************************************
 * NvM_ActUpdateNvState
 *********************************************************************************************************************/
/*! \brief Updates NvState dependent on last result and marks the other NvBlock as active, if it is a redundant block.
 *  \details -
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActUpdateNvState(void);

/**********************************************************************************************************************
 * NvM_ActSetReqIntegrityFailed
 *********************************************************************************************************************/
/*! \brief Set current pending block's result to integrity failed.
 *  \details -
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActSetReqIntegrityFailed(void);

/**********************************************************************************************************************
 * NvM_ActSetReqSkipped
 *********************************************************************************************************************/
/*! \brief Set current pending block's result to skipped.
 *  \details -
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActSetReqSkipped(void);

/**********************************************************************************************************************
 * NvM_ActSetReqNotOk
 *********************************************************************************************************************/
/*! \brief Set current pending block's result to NOT_OK.
 *  \details -
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActSetReqNotOk(void);

/**********************************************************************************************************************
 * NvM_SetBlockPendingWriteAll
 *********************************************************************************************************************/
/*! \brief Set current block to pending and invoke notifications.
 *  \details -
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_SetBlockPendingWriteAll(void);

/**********************************************************************************************************************
 * NvM_ActWait
 *********************************************************************************************************************/
/*! \brief Set wait flag.
 *  \details -
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActWait(void);

/**********************************************************************************************************************
 * NvM_ActNop
 *********************************************************************************************************************/
/*! \brief Do nothing, just return.
 *  \details -
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActNop(void);

/**********************************************************************************************************************
 * NvM_ActGetMultiBlockJob
 *********************************************************************************************************************/
/*! \brief Setup a multi block job - ReadAll or WriteAll - depending on requests.
 *  \details -
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActGetMultiBlockJob(void);

/**********************************************************************************************************************
 * NvM_ActCopyNvDataToBuf
 *********************************************************************************************************************/
/*! \brief Prepares data for CRC calculation and writing.
 *  \details Takes care about data creation (explicit synchronization, copy to internal buffer) and about the pre write
 *           data transformation handling.
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActCopyNvDataToBuf(void);

/**********************************************************************************************************************
 * NvM_ActKillSubFsm
 *********************************************************************************************************************/
/*!
 * \brief Resets the sub state machine to NVM_STATE_FSM_FINISHED (kills the state machine immediately).
 * \details -
 * \context TASK
 * \reentrant FALSE
 * \synchronous TRUE
 * \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActKillSubFsm(void);

/**********************************************************************************************************************
 *  NvM_ActNotifyLossOfRedundancy
 *********************************************************************************************************************/
/*!
 * \brief           Invoke callback for detected loss of redundancy (if configured)
 * \details         -
 * \pre             -
 * \context         TASK
 * \reentrant       FALSE
 * \synchronous     TRUE
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActNotifyLossOfRedundancy(void);

#if (NVM_REPAIR_REDUNDANT_BLOCKS_API == STD_ON)
/**********************************************************************************************************************
 * NvM_ActRepairRedBlocksInit
 *********************************************************************************************************************/
/*!
 * \brief Initialize the Repair Redundant Blocks job.
 * \details -
 * \config RepairRedundantBlocks API is enabled
 * \context TASK
 * \reentrant FALSE
 * \synchronous TRUE
 * \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActRepairRedBlocksInit(void);

/**********************************************************************************************************************
 * NvM_ActRepairRedBlocksInitNext
 *********************************************************************************************************************/
/*!
 * \brief Initialize next redundant block to check whether it has to be repaired.
 * \details Search for the next redundant block within current configuration and sets the next block Id to check.
 *          In case there is no redundant block any more the repair job will terminate.
 * \config RepairRedundantBlocks API is enabled
 * \context TASK
 * \reentrant FALSE
 * \synchronous TRUE
 * \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActRepairRedBlocksInitNext(void);

/**********************************************************************************************************************
 * NVM_ActRepairRedBlocksInitBlock
 *********************************************************************************************************************/
 /*!
 * \brief Initialize the repair job for current block Id.
 * \details -
 * \config RepairRedundantBlocks API is enabled
 * \context TASK
 * \reentrant FALSE
 * \synchronous TRUE
 * \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NVM_ActRepairRedBlocksInitBlock(void);

/**********************************************************************************************************************
 * NvM_ActRepairRedBlockReadCheck
 *********************************************************************************************************************/
/*!
 * \brief Setups the read request to underlying modules for currently processing block.
 * \details -
 * \config RepairRedundantBlocks API is enabled
 * \context TASK
 * \reentrant FALSE
 * \synchronous TRUE
 * \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActRepairRedBlockReadCheck(void);

/**********************************************************************************************************************
 * NvM_ActRepairRedBlockFinishReadCheck
 *********************************************************************************************************************/
/*!
 * \brief Setup a read request to underlying modules for a sub-block to check its validity.
 * \details The NvM differs between two possible validity checks: for blocks with and without Crc. For blocks with Crc
 *          the Crc has to be checked to ensure block validity, for blocks without Crc a readable block is a valid block.
 * \config RepairRedundantBlocks API is enabled
 * \context TASK
 * \reentrant FALSE
 * \synchronous TRUE
 * \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActRepairRedBlockFinishReadCheck(void);

/**********************************************************************************************************************
 * NvM_ActRepairRedBlocksReadValid
 *********************************************************************************************************************/
/*!
 * \brief Read the sub-block which is marked as valid.
 * \details -
 * \config RepairRedundantBlocks API is enabled
 * \context TASK
 * \reentrant FALSE
 * \synchronous TRUE
 * \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActRepairRedBlocksReadValid(void);

/**********************************************************************************************************************
 * NvM_ActRepairRedBlockWriteInvalid
 *********************************************************************************************************************/
/*!
 * \brief Writes the previously read data to the sub-block which is marked as invalid.
 * \details -
 * \config RepairRedundantBlocks API is enabled
 * \context TASK
 * \reentrant FALSE
 * \synchronous TRUE
 * \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActRepairRedBlockWriteInvalid(void);

/**********************************************************************************************************************
 * NvM_ActRepairRedBlocksFinishBlock
 *********************************************************************************************************************/
/*!
 * \brief Finish the repair job for current NvM block.
 * \details The function decides whether a DEM error shall be reported or not, depending on successful or failed restoring.
 * \config RepairRedundantBlocks API is enabled
 * \context TASK
 * \reentrant FALSE
 * \synchronous TRUE
 * \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActRepairRedBlocksFinishBlock(void);

/**********************************************************************************************************************
 * NvM_ActRepairRedBlocksFinish
 *********************************************************************************************************************/
/*!
 * \brief Reset used internal variable and finish the repair redundant block job.
 * \details -
 * \config RepairRedundantBlocks API is enabled
 * \context TASK
 * \reentrant FALSE
 * \synchronous TRUE
 * \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActRepairRedBlocksFinish(void);
#endif /* (NVM_REPAIR_REDUNDANT_BLOCKS_API == STD_ON) */


/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES: PRIVATE HELPER FUNCTIONS
 *********************************************************************************************************************/

#if (NVM_DYNAMIC_CONFIGURATION == STD_ON)
/**********************************************************************************************************************
 * NvM_UpdateConfigIdBlock
 *********************************************************************************************************************/
/*! \brief Updates ConfigId (in RAM block), marks Block as VALID and CHANGED (to be written during NvM_WriteAll) and
 *         triggers RAM Crc-Recalculation.
 *  \details -
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_UpdateConfigIdBlock(void);
#endif /* (NVM_DYNAMIC_CONFIGURATION == STD_ON) */

/**********************************************************************************************************************
 * NvM_InternalCopyData
 *********************************************************************************************************************/
/*! \brief Copy specific number of data bytes from source to destination.
 *  \details -
 *  \param[in] info_pt
 *  \param[in,out] destPtr
 *  \param[in] srcPtr
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_InternalCopyData
    (NvM_BlockInfoPtrType info_pt, NvM_RamAddressType destPtr, NvM_ConstRamAddressType srcPtr);

/**********************************************************************************************************************
 * NvM_InternalCopyBufferedData
 *********************************************************************************************************************/
/*! \brief If configured, the function will the explicit synchronization mechanism, if not configured the data will be
 *         copied from internal buffer to Ram (permanent or non-permanent).
 *  \details -
 *  \param[in] info_pt
 *  \param[in] srcPtr
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_InternalCopyBufferedData
    (NvM_BlockInfoPtrType info_pt, NvM_ConstRamAddressType srcPtr);

/**********************************************************************************************************************
 * NvM_IntCreateNvState
 *********************************************************************************************************************/
/*! \brief Create current NvState and marks the other one active.
 *  \details -
 *  \param[in] NvState
 *  \param[in,out] NewState
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_IntCreateNvState(P2VAR(uint8, AUTOMATIC, NVM_PRIVATE_DATA) NvState, uint8 NewState);

#if(NVM_KILL_WRITEALL_API == STD_ON)
/**********************************************************************************************************************
 * NvM_IsWriteAllAndKilled
 *********************************************************************************************************************/
/*! \brief Check whether a WriteAll and KillWriteAll requests were setup.
 *  \details -
 *  \param[in] currServiceId
 *  \param[in] currApiFlag
 *  \return TRUE in case the given service Id references WriteAll job and KillWriteAll flag is set in given API flag
 *  \return FALSE otherwise
 *  \config KillWriteAll is enabled
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_IsWriteAllAndKilled(const NvM_InternalServiceIdType currServiceId, const uint8 currApiFlag);
#endif /* (NVM_KILL_WRITEALL_API == STD_ON) */

/**********************************************************************************************************************
 * NvM_IntUpdateCurrentBlockCRCCompareData
 *********************************************************************************************************************/
/*!
 * \brief       Updates or invalidates the current CRCCompareMechanism CRC buffer depending on the given job result.
 * \details     -
 * \param[in]   result - OK=store calculated CRC; NOT_OK=invalidate CRC
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 * \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_IntUpdateCurrentBlockCRCCompareData(const NvM_RequestResultType result);

#define NVM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
#define NVM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

CONST(NvM_ActFctPtrType, NVM_PRIVATE_CONST) NvM_ActionTable_ap[(uint32)NVM_ACT_ID_Nop + 1u] =
{
    NvM_ActSetInitialAttr,
    NvM_ActInitMainFsm,
    NvM_ActInitBlock,
    NvM_ActInitReadAll,
    NvM_ActInitReadBlockSubFsm,
    NvM_ActInitRestoreBlockDefaultsSubFsm,
    NvM_ActInitWriteAll,
    NvM_ActInitWriteBlock,
    NvM_ActInitWriteBlockFsm,
    NvM_ActInitRestoreBlockDefaults,
    NvM_ActFinishMainJob,
#if (NVM_KILL_WRITEALL_API == STD_ON)
    NvM_ActKillWriteAll,
#endif
    NvM_ActFinishBlock,
    NvM_ActInitNextBlockReadAll,
    NvM_ActInitNextBlockWriteAll,
    NvM_ActFinishCfgIdCheck,
    NvM_ActFinishReadBlock,
    NvM_ActFinishWriteBlock,

#if (NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3)
    NvM_ActFinishEraseBlock,
    NvM_ActEraseNvBlock,
    NvM_ActInvalidateNvBlock,
#endif
    NvM_ActProcessCrc,
    NvM_ActWriteNvBlock,
    NvM_ActReadNvBlock,
    NvM_ActReadNvBlockCrcOnly,
    NvM_ActProcessCrcRead,
    NvM_ActReadCopyData,
    NvM_ActRestoreRomDefaults,
    NvM_ActFinishRestoreRomDefaults,
    NvM_ActTestBlockBlank,
    NvM_ActValidateRam,
    NvM_ActSetupRedundant,
    NvM_ActSetupOther,
    NvM_ActUpdateNvState,
    NvM_ActSetReqIntegrityFailed,
    NvM_ActSetReqSkipped,
    NvM_ActSetReqNotOk,
    NvM_ActSetReqOk,
    NvM_SetBlockPendingWriteAll,
    NvM_ActCopyNvDataToBuf,
    NvM_ActGetMultiBlockJob,
    NvM_ActCancelNV,
    NvM_ActKillSubFsm,
    NvM_ActNotifyLossOfRedundancy,
    NvM_ActFinishReadBlockAndSetSkipped,
#if (NVM_REPAIR_REDUNDANT_BLOCKS_API == STD_ON)
    NvM_ActRepairRedBlocksInit,
    NvM_ActRepairRedBlocksInitNext,
    NvM_ActRepairRedBlockReadCheck,
    NvM_ActRepairRedBlockFinishReadCheck,
    NvM_ActRepairRedBlocksReadValid,
    NvM_ActRepairRedBlockWriteInvalid,
    NvM_ActRepairRedBlocksFinishBlock,
    NvM_ActRepairRedBlocksFinish,
#endif
#if (NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1)
    NvM_ActGetNormalPrioJob,
# if (NVM_JOB_PRIORISATION == STD_ON)
        NvM_ActGetHighPrioJob,
        NvM_ActQueueFreeLastJob,
# endif
#endif
    NvM_ActWait,
    NvM_ActNop
}; /* function pointer table storing all actions called from NvM's state machine
 * (state machine accesses the actions via indexes) */

#define NVM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
#define NVM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if (NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3)
/**********************************************************************************************************************
*  NvM_ActEraseNvBlock
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActEraseNvBlock(void)
{
    if (E_OK != MemIf_EraseImmediateBlock((uint8)NvM_CurrentBlockInfo_t.Descriptor_pt->DeviceId_u8,
                                          NvM_CurrentBlockInfo_t.NvIdentifier_u16))
    {
        NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_NOT_OK;
    }
    else
    {
        NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_PENDING;
    }
}
#endif /* (NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3) */

/**********************************************************************************************************************
*  NvM_ActFinishBlock
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActFinishBlock(void)
{
#if(NVM_KILL_WRITEALL_API == STD_ON)
    /* set result only, if KillWriteAll was not called; otherwise it was set by KillWriteAll */
    if(!NvM_IsWriteAllAndKilled(NvM_CurrentJob_t.JobServiceId_t, NvM_ApiFlags_u8)) /* COV_NVM_KILLWRITEALL */
    {
        NvM_CurrentBlockInfo_t.Mngmt_pt->NvRamErrorStatus_u8 = NvM_CurrentBlockInfo_t.LastResult_t; /* SBSW_NvM_Access_CurrBlockInfo */
    }

#else
    NvM_CurrentBlockInfo_t.Mngmt_pt->NvRamErrorStatus_u8 = NvM_CurrentBlockInfo_t.LastResult_t; /* SBSW_NvM_Access_CurrBlockInfo */
#endif

    /* call block notification(s), except the block was skipped during WriteAll (see SREQ SREQ00024689) */
    if((NvM_CurrentJob_t.JobServiceId_t != NVM_INT_FID_WRITE_ALL) || (NvM_CurrentBlockInfo_t.LastResult_t != NVM_REQ_BLOCK_SKIPPED))
    {
        NvM_BlockNotification(NvM_CurrentJob_t.JobBlockId_t, 
                              NvM_IntServiceDescrTable_at[NvM_CurrentJob_t.JobServiceId_t].PublicFid_t,
                              NvM_CurrentBlockInfo_t.LastResult_t);
    }

    /* #30 reset current job's RamBlock, which is important for ReadAll and WriteAll */
    NvM_CurrentJob_t.RamAddr_t = NULL_PTR;
}

/**********************************************************************************************************************
*  NvM_ActInitNextBlockReadAll
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
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitNextBlockReadAll(void)
{
  NvM_ActFinishBlock();

  NvM_CurrentJob_t.JobBlockId_t++;

  if(NvM_CurrentJob_t.JobBlockId_t < NvM_NoOfBlockIds_t)
  {
    NvM_RamAddressType crcCalculationDataPtr;

    NvM_ActInitBlock();

#if(NVM_CRC_INT_BUFFER == STD_ON)
    if(NvM_QryCalcRamBlockCrcEnabledAndRamValid()
        && (NvM_CurrentBlockInfo_t.Descriptor_pt->CbkSetMirrorFunc_pt != NULL_PTR))                                     /* COV_NVM_COVEREDINOTHERCFG */
    {
      /* Attempt to get data via explicit synchronization if configured */
      if(NvM_CurrentBlockInfo_t.Descriptor_pt->CbkSetMirrorFunc_pt(NvM_InternalBuffer_au8) == E_OK)                     /* SBSW_NvM_FuncPtrCall_UserCallbacks */ /* PRQA S 0315 */ /* MD_NvM_Dir1.1_CastToVoidPtr */ /* COV_NVM_COVEREDINOTHERCFG */
      {
        crcCalculationDataPtr = NvM_InternalBuffer_au8;
      }
      else
      {
        /* Explicit synchronization rejected. Assign NULL to skip CRC calculation. */
        crcCalculationDataPtr = NULL_PTR;

        /* Invalidate block to enter processing of extended or normal runtime preparation depending on configuration */
        NvM_CurrentBlockInfo_t.Mngmt_pt->NvRamAttributes_u8 &= NVM_STATE_VALID_CL;                                      /* SBSW_NvM_Access_CurrBlockInfo */
      }
    }
    else
#endif
    {
      crcCalculationDataPtr = NvM_CurrentBlockInfo_t.Descriptor_pt->RamBlockDataAddr_t;
    }

    NvM_CrcJob_Create(
        &NvM_CurrentBlockInfo_t.BlockCrcJob_t,                                                                          /* SBSW_NvM_FuncCall_PtrParam_CurrBlockInfo */
        NvM_CurrentJob_t.JobBlockId_t,
        crcCalculationDataPtr,
        NvM_CurrentBlockInfo_t.Descriptor_pt->NvBlockNVRAMDataLength);

#if(NVM_CRC_INT_BUFFER == STD_ON)
    /* Re-assign CRC buffer to Block's configured CRC buffer. It works, even if CRC buffer is NULL_PTR
     * (i.e. no CRC configured), because in this case the CRC job is designed to prevent from using
     * (dereferencing) this pointer. */
    NvM_CrcJob_ReassignBuffer(                                                                                          /* SBSW_NvM_AccessPtr_CrcReassignBuffer */
        &NvM_CurrentBlockInfo_t.BlockCrcJob_t,
        NvM_CurrentBlockInfo_t.Descriptor_pt->RamBlockCrcAddr_t);
#endif
  }
}

/**********************************************************************************************************************
*  NvM_ActInitNextBlockWriteAll
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitNextBlockWriteAll(void)
{
    NvM_ActFinishBlock();

    --NvM_CurrentJob_t.JobBlockId_t; /* Check whether decrement is valid has already been done */

    NvM_ActInitBlock(); /* Initialize internal data; it simplifies access to Block information below */
}

/**********************************************************************************************************************
*  NvM_ActFinishMainJob
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
 *
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActFinishMainJob(void)
{
    const NvM_InternalServiceIdType currSrvId = NvM_CurrentJob_t.JobServiceId_t;

#if (NVM_REPAIR_REDUNDANT_BLOCKS_API == STD_ON) /* ECO_IGNORE_LINE */
    if(currSrvId < NVM_INT_FID_REPAIR_REDUNDANT_BLOCKS)
#endif /* ECO_IGNORE_LINE */
    {
        if((currSrvId == NVM_INT_FID_READ_ALL) || (currSrvId == NVM_INT_FID_WRITE_ALL)) /* COV_NVM_APICFGCLASS */
        {
            NvM_RequestResultType JobResult;

            if((currSrvId == NVM_INT_FID_WRITE_ALL) && ((NvM_ApiFlags_u8 & NVM_APIFLAG_CANCEL_WR_ALL_SET) != 0u))
            {
                JobResult = NVM_REQ_CANCELED;
            }
            /* PRQA S 3415 1 */ /* MD_NvM_13.5_ReadAllAndKillReadAll */
            else if((currSrvId == NVM_INT_FID_READ_ALL) && (NvM_QryReadAllKilled() == TRUE))
            {
                JobResult = NVM_REQ_CANCELED;
            }
            else if((NvM_CurrentBlockInfo_t.InternalFlags_u8 & NVM_INTFLAG_ERROR_SET) != 0u)
            {
                JobResult = NVM_REQ_NOT_OK;
            }
            else
            {
                JobResult = NVM_REQ_OK;
            }

            NvM_BlockMngmtArea_at[0].NvRamErrorStatus_u8 = JobResult; /* SBSW_NvM_AccessBlockManagementArea */

            /* Internal Callback encapsulation - it is not a function pointer */
            NvM_MultiBlockCbk(NvM_IntServiceDescrTable_at[currSrvId].PublicFid_t, JobResult);

            NvM_EnterCriticalSection();

            NvM_ApiFlags_u8 &= (NVM_APIFLAG_READ_ALL_CL & NVM_APIFLAG_WRITE_ALL_CL);

            NvM_ExitCriticalSection();


    #if(NVM_DRV_MODE_SWITCH == STD_ON)
            MemIf_SetMode(MEMIF_MODE_SLOW);
    #endif
        }
        else
        {
            NvM_ActFinishBlock();
        }
    }

    NvM_CurrentJob_t.JobServiceId_t = NVM_INT_FID_NO_JOB_PENDING;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

#if (NVM_KILL_WRITEALL_API == STD_ON)
/**********************************************************************************************************************
*  NvM_ActKillWriteAll
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActKillWriteAll(void)
{
#if(NVM_DRV_MODE_SWITCH == STD_ON)
    MemIf_SetMode(MEMIF_MODE_SLOW);
#endif
    NvM_ActCancelNV();

    NvM_CurrentJob_t.JobServiceId_t = NVM_INT_FID_NO_JOB_PENDING;

    /* Kill sub-FSMs */
    NvM_JobMainState_t = NVM_STATE_FSM_FINISHED;
    NvM_JobSubState_t = NVM_STATE_FSM_FINISHED;

    NvM_EnterCriticalSection();
    /* Note that (theoretically) ReadAll as well as WriteAll might already have been requested.
     * => NvM_GetStatus(0, ...) delivers "CANCELLED", since the calling NvM_KillWriteAll */
    NvM_ApiFlags_u8 &= (NVM_APIFLAG_CANCEL_WR_ALL_CL & NVM_APIFLAG_KILL_WR_ALL_CL);

    NvM_ExitCriticalSection();
}
#endif /* (NVM_KILL_WRITEALL_API == STD_ON) */

/**********************************************************************************************************************
*  NvM_ActFinishReadBlock
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
 *
 *
 *
 *
 *
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActFinishReadBlock(void)
{
    const NvM_RamMngmtPtrType MngmtPtr = NvM_CurrentBlockInfo_t.Mngmt_pt;
    const NvM_BlockDescrPtrType descr_pt = NvM_CurrentBlockInfo_t.Descriptor_pt;
    /* updates NvState for current block and changes active block */
    NvM_ActUpdateNvState();

    if(((descr_pt->MngmtType_t & NVM_BLOCK_REDUNDANT) != 0u)    &&
       (NVM_EXTRACT_NVSTATE_PRIMARY(NvM_CurrentBlockInfo_t.NvState_u8) != NVM_NVBLOCK_STATE_OUTDATED) &&
       (NVM_EXTRACT_NVSTATE_SECONDARY(NvM_CurrentBlockInfo_t.NvState_u8) == NVM_NVBLOCK_STATE_OUTDATED))
    {
        NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_NOT_OK;
    }

    if(NvM_IsBooleanBitfieldTrue(descr_pt->Flags.BlockWriteBlockOnceEnabled))
    {
        if(NvM_CurrentBlockInfo_t.LastResult_t == NVM_REQ_OK)
        {
            MngmtPtr->NvRamAttributes_u8 |= NVM_WR_PROT_SET; /* SBSW_NvM_Access_CurrBlockInfo */
        }
        else
        {
            MngmtPtr->NvRamAttributes_u8 &= NVM_WR_PROT_CL; /* SBSW_NvM_Access_CurrBlockInfo */
        }
    }

    NvM_IntUpdateCurrentBlockCRCCompareData(NvM_CurrentBlockInfo_t.LastResult_t);

    if(NvM_CurrentBlockInfo_t.LastResult_t != NVM_REQ_OK)
    {
        NvM_CurrentBlockInfo_t.InternalFlags_u8 |= NVM_INTFLAG_ERROR_SET;

        if(NvM_CurrentBlockInfo_t.LastResult_t == NVM_REQ_NOT_OK)
        {
            NvM_DemReportErrorReqFailed();
        }
        else if(NvM_CurrentBlockInfo_t.LastResult_t == NVM_REQ_INTEGRITY_FAILED)
        {
            NvM_DemReportErrorIntegrityFailed();
        }
        else
        {
            /* Nothing to do */
        }

        if((NvM_CurrentBlockInfo_t.InternalFlags_u8 & NVM_INTFLAG_ROM_RESTORED_SET) == NVM_INTFLAG_ROM_RESTORED_SET)
        {
            NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_RESTORED_FROM_ROM;
        }
    }

#if(NVM_CRC_INT_BUFFER == STD_ON)
    /* Save new CRC (RAM CRC), if requested RAM block is permanent (configured) RAM block */
    if((NvM_CurrentBlockInfo_t.LastResult_t == NVM_REQ_OK) &&
       (NvM_CurrentJob_t.RamAddr_t == NULL_PTR)) /* COV_NVM_APICFGCLASS */
    { /* Export function checks whether block has CRC AND CRC buffer (no "RAM CRC") */
        NvM_CrcJob_ExportBufferedValue(&NvM_CurrentBlockInfo_t.BlockCrcJob_t, descr_pt->RamBlockCrcAddr_t); /* SBSW_NvM_FuncCall_PtrParam_CurrBlockInfo */
    }
#endif
} /* PRQA S 6010 */ /* MD_MSR_STPTH */

/**********************************************************************************************************************
*  NvM_ActFinishWriteBlock
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
 *
 *
 *
 *
 *
 *
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActFinishWriteBlock(void)
{
    const NvM_RamMngmtPtrType MngmtPtr = NvM_CurrentBlockInfo_t.Mngmt_pt;

    NvM_ActUpdateNvState();

    if((NvM_CurrentBlockInfo_t.Descriptor_pt->MngmtType_t & NVM_BLOCK_REDUNDANT) != 0u)
    {
        boolean firstBlockDefect = (boolean)(NVM_EXTRACT_NVSTATE_PRIMARY(NvM_CurrentBlockInfo_t.NvState_u8) != NVM_NVBLOCK_STATE_UPTODATE);
        boolean secondBlockDefect = (boolean)(NVM_EXTRACT_NVSTATE_SECONDARY(NvM_CurrentBlockInfo_t.NvState_u8) != NVM_NVBLOCK_STATE_UPTODATE);

        /* both blocks are defect, request failed, DEM error will be reported later */
        if(firstBlockDefect && secondBlockDefect)
        {
            NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_NOT_OK;
        }
        /* at least one block is OK */
        else
        {
            NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_OK;
            /* one block is OK, other isn't -> block isn't redundantly stored within NV RAM */
            if(firstBlockDefect != secondBlockDefect)
            {
                NvM_DemReportErrorLossOfRedundancy();
            }
        }
        /* one or both blocks defect -> use negative result to invalidate CRCCompareMechanism data, otherwise update */
        NvM_IntUpdateCurrentBlockCRCCompareData((firstBlockDefect || secondBlockDefect) ? NVM_REQ_NOT_OK : NVM_REQ_OK);
    }
    else
    {
        NvM_IntUpdateCurrentBlockCRCCompareData(NvM_CurrentBlockInfo_t.LastResult_t);
    }

    if(NvM_CurrentBlockInfo_t.LastResult_t == NVM_REQ_OK)
    {
        /* mark permanent(!) Block as UNCHANGED */
        if(NvM_CurrentJob_t.RamAddr_t == NULL_PTR) /* COV_NVM_APICFGCLASS */
        {
            MngmtPtr->NvRamAttributes_u8 &= NVM_STATE_CHANGED_CL; /* SBSW_NvM_Access_CurrBlockInfo */
        }

        if(NvM_IsBooleanBitfieldTrue(NvM_CurrentBlockInfo_t.Descriptor_pt->Flags.BlockWriteBlockOnceEnabled))
        {
            MngmtPtr->NvRamAttributes_u8 |= NVM_WR_PROT_SET; /* SBSW_NvM_Access_CurrBlockInfo */
        }
    }
    else
    {   /* remember error condition to deliver the correct result for ReadAll/WriteAll */
        NvM_CurrentBlockInfo_t.InternalFlags_u8 |= NVM_INTFLAG_ERROR_SET;
        NvM_DemReportErrorReqFailed();
    }
}

/**********************************************************************************************************************
*  NvM_ActInitBlock
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
 *
 *
 *
 *
 *
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitBlock(void)
{
    /* Just to get a shorter notation ... */
    const NvM_BlockIdType orgBlockId = NVM_BLOCK_FROM_DCM_ID(NvM_CurrentJob_t.JobBlockId_t);
    const NvM_BlockDescrPtrType DescrPtr = &NvM_BlockDescriptorTable_at[orgBlockId];

    NvM_CurrentBlockInfo_t.Mngmt_pt =
        ((NvM_CurrentJob_t.JobBlockId_t == orgBlockId) ? (&NvM_BlockMngmtArea_at[orgBlockId]) : (&NvM_DcmBlockMngmt_t)); /* COV_NVM_APICFGCLASS */
    NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_OK;
    NvM_CurrentBlockInfo_t.Descriptor_pt = DescrPtr;
    NvM_CurrentBlockInfo_t.NvIdentifier_u16 = DescrPtr->NvIdentifier_u16;
    /* For blocks of MngmtType DATASET or DATASET_ROM the DataIndex has to be added to NvIdentifier. */
    if((DescrPtr->MngmtType_t & NVM_BLOCK_DATASET) != 0u)
    {
        NvM_CurrentBlockInfo_t.NvIdentifier_u16 |= NvM_CurrentBlockInfo_t.Mngmt_pt->NvDataIndex_t;
    }
    NvM_CurrentBlockInfo_t.ByteCount_u16 = 0u;

#if(NVM_CRC_INT_BUFFER == STD_ON)
    /* Initially, we assume the internal buffer to be used. */
    NvM_CurrentBlockInfo_t.RamAddr_t = NvM_InternalBuffer_au8;
    /* Only without CRC we have to decide whether to directly read to or write from RAM Block. */
    if(DescrPtr->CrcSettings == NVM_BLOCK_USE_CRC_OFF)
    {
        if(NvM_CurrentJob_t.RamAddr_t != NULL_PTR) /* COV_NVM_APICFGCLASS */
        {
            NvM_CurrentBlockInfo_t.RamAddr_t = NvM_CurrentJob_t.RamAddr_t;
        }
        /* Do not have to check both callbacks - it is only allowed to configure one or even both. */
        else if(DescrPtr->CbkGetMirrorFunc_pt == NULL_PTR)
        {
            NvM_CurrentBlockInfo_t.RamAddr_t = DescrPtr->RamBlockDataAddr_t;
        }
        else /* Explicit synch mechanism (not overriden by passing a pointer along with the request): */
        {
            /* => use internal buffer -> already assigned. */
        }
    }
#else
    NvM_CurrentBlockInfo_t.RamAddr_t =
        (NvM_CurrentJob_t.RamAddr_t != NULL_PTR) ? NvM_CurrentJob_t.RamAddr_t : DescrPtr->RamBlockDataAddr_t;
#endif

#if(NVM_USE_CSM == STD_ON)
    if(NvM_QryIsCipherBlock(NvM_CurrentBlockInfo_t.Descriptor_pt) == TRUE) /* SBSW_NvM_FuncCall_PtrParam_CurrBlockInfo */
    {
        NvM_CurrentBlockInfo_t.NvRamAddr_t = NvM_CipheredDataBuffer;
    }
    else
#endif
    {
        NvM_CurrentBlockInfo_t.NvRamAddr_t = NvM_CurrentBlockInfo_t.RamAddr_t;
    }

    if((DescrPtr->MngmtType_t & NVM_BLOCK_REDUNDANT) != 0u)
    {    
        NvM_CurrentBlockInfo_t.NvState_u8 = NVM_NVBLOCK_STATE_PRI_ACTIVE;
        NvM_IntCreateNvState(&NvM_CurrentBlockInfo_t.NvState_u8, NVM_NVBLOCK_STATE_UNKNOWN); /* SBSW_NvM_FuncCall_PtrParam_CurrBlockInfo */
    }
}

/**********************************************************************************************************************
*  NvM_ActInitMainFsm
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitMainFsm(void)
{
    NvM_ActInitBlock();
    NvM_JobMainState_t = NvM_IntServiceDescrTable_at[NvM_CurrentJob_t.JobServiceId_t].InitialState_t;
    /* NvM uses only the JobMainState at this point, the JobSubState remains unused -> FSM_FINISHED.
     * Normally the JobSubState is already set correctly, but e.g. in case of a WriteAll cancel via an immediate
     * priority block, the JobSubState remains in a real state and processes the states - increases runtime and may
     * lead to problems - ensure the JobSubState does nothing! */
    NvM_JobSubState_t = NVM_STATE_FSM_FINISHED;
    NvM_ActionTable_ap[NvM_IntServiceDescrTable_at[NvM_CurrentJob_t.JobServiceId_t].InitialActionId](); /* SBSW_NvM_FuncPtrCall_QueryAction */
}

/**********************************************************************************************************************
*  NvM_ActInitReadAll
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitReadAll(void)
{
    NvM_BlockIdType currBlockId = NvM_NoOfBlockIds_t;

    /* clear Error and Dynamic Mismatch flags */
    NvM_CurrentBlockInfo_t.InternalFlags_u8 &= NVM_INTFLAG_ERROR_CL & NVM_INTFLAG_DYN_MISMATCH_CL;

    do
    {
        currBlockId--;
        NvM_BlockMngmtArea_at[currBlockId].NvRamErrorStatus_u8 = NVM_REQ_PENDING; /* SBSW_NvM_AccessBlockManagementArea */
        NvM_BlockNotification(currBlockId, NVM_READ_ALL, NVM_REQ_PENDING);
        
    } while(currBlockId > 0u); /* blockId 0 does not need to be set to PENDING, already done */

    NvM_ActSetInitialAttr();

#if(NVM_DRV_MODE_SWITCH == STD_ON)
    MemIf_SetMode(MEMIF_MODE_FAST);
#endif
    /* #50 start reading the configuration block */
    NvM_ActInitReadBlockSubFsm();
}

/**********************************************************************************************************************
*  NvM_ActFinishCfgIdCheck
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
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActFinishCfgIdCheck(void)
{
    /* clear Config ID Mismatch Flag */
    NvM_CurrentBlockInfo_t.InternalFlags_u8 &= NVM_INTFLAG_DYN_MISMATCH_CL;

#if (NVM_DYNAMIC_CONFIGURATION == STD_ON)
    if(NvM_CurrentBlockInfo_t.LastResult_t == NVM_REQ_OK)
    {
        if((NvM_CompiledConfigId_t.Bytes_au8[0] != NvM_CurrentBlockInfo_t.RamAddr_t[0]) ||
           (NvM_CompiledConfigId_t.Bytes_au8[1] != NvM_CurrentBlockInfo_t.RamAddr_t[1]))
        {
            NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_NOT_OK;
            NvM_CurrentBlockInfo_t.InternalFlags_u8 |= NVM_INTFLAG_DYN_MISMATCH_SET;
            NvM_UpdateConfigIdBlock();
        }
    }
    else /* any other negative result */
    {
        if(NvM_CurrentBlockInfo_t.LastResult_t != NVM_REQ_NV_INVALIDATED)
        {
            NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_INTEGRITY_FAILED;
        }
        NvM_CurrentBlockInfo_t.InternalFlags_u8 |= NVM_INTFLAG_DYN_MISMATCH_SET;
        NvM_UpdateConfigIdBlock();
    }

#else

    /* AUTOSAR states that in case NVM_DYNAMIC_CONFIGURATION is STD_OFF the behavior of the config block
    shall be "normal", therefore it doesn't matter if the config ID doesn't match.
    We shall always return NVM_REQ_OK. SWS_NvM_00248 */
    NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_OK; 

#endif
}

/**********************************************************************************************************************
*  NvM_ActInitWriteAll
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitWriteAll(void)
{
    /* clear Error flag */
    NvM_CurrentBlockInfo_t.InternalFlags_u8 &= NVM_INTFLAG_ERROR_CL;

#if(NVM_DRV_MODE_SWITCH == STD_ON)
    MemIf_SetMode(MEMIF_MODE_FAST);
#endif
}

/**********************************************************************************************************************
*  NvM_ActInitWriteBlock
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitWriteBlock(void)
{
    NvM_CurrentBlockInfo_t.WriteRetryCounter_u8 = 0u;
#if (NVM_USE_CSM == STD_ON)
    NvM_CurrentBlockInfo_t.CsmJobRetryCounter_u8 = 0u;
#endif

    if((NvM_CurrentBlockInfo_t.Descriptor_pt->MngmtType_t & NVM_BLOCK_REDUNDANT) != 0u)
    {
        NvM_ActTestBlockBlank();
    }

#if(NVM_CRC_INT_BUFFER == STD_ON)
    NvM_CurrentBlockInfo_t.ByteCount_u16 = NvM_CurrentBlockInfo_t.Descriptor_pt->NvBlockLength_u16;
#endif
    /* Byte Count may remain zero; and this is okay, since no copying will be necessary.
     * In fact NvM_ActCopyNvDataToBuf won't even use it... */
    NvM_CrcJob_Create(&NvM_CurrentBlockInfo_t.BlockCrcJob_t,
                      NvM_CurrentJob_t.JobBlockId_t,
                      NvM_CurrentBlockInfo_t.NvRamAddr_t,
                      NvM_CurrentBlockInfo_t.Descriptor_pt->NvBlockNVRAMDataLength); /* SBSW_NvM_FuncCall_PtrParam_CurrBlockInfo */

    NvM_ActCopyNvDataToBuf();
}

#if (NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3)
/**********************************************************************************************************************
*  NvM_ActFinishEraseBlock
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActFinishEraseBlock(void)
{
    if(NvM_CurrentBlockInfo_t.LastResult_t != NVM_REQ_OK)
    {
        NvM_DemReportErrorReqFailed();
        NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_NOT_OK;
    }

    NvM_IntUpdateCurrentBlockCRCCompareData(NVM_REQ_NOT_OK);
}
#endif /* (NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3) */

/**********************************************************************************************************************
*  NvM_ActInitReadBlockSubFsm
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitReadBlockSubFsm(void)
{
    NvM_JobSubState_t = NvM_IntServiceDescrTable_at[NVM_INT_FID_READ_BLOCK].InitialState_t;
    NvM_ActionTable_ap[NvM_IntServiceDescrTable_at[NVM_INT_FID_READ_BLOCK].InitialActionId](); /* SBSW_NvM_FuncPtrCall_QueryAction */
}

/**********************************************************************************************************************
*  NvM_ActInitRestoreBlockDefaultsSubFsm
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitRestoreBlockDefaultsSubFsm(void)
{
    NvM_JobSubState_t = NvM_IntServiceDescrTable_at[NVM_INT_FID_RESTORE_DEFAULTS].InitialState_t;
    NvM_ActionTable_ap[NvM_IntServiceDescrTable_at[NVM_INT_FID_RESTORE_DEFAULTS].InitialActionId](); /* SBSW_NvM_FuncPtrCall_QueryAction */
}

/**********************************************************************************************************************
*  NvM_ActInitWriteBlockFsm
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitWriteBlockFsm(void)
{
    const NvM_StateActionIdType InitialActId = NvM_IntServiceDescrTable_at[NVM_INT_FID_WRITE_BLOCK].InitialActionId;

    NvM_JobSubState_t = NvM_IntServiceDescrTable_at[NVM_INT_FID_WRITE_BLOCK].InitialState_t;
    NvM_ActionTable_ap[InitialActId](); /* SBSW_NvM_FuncPtrCall_QueryAction */
}

/**********************************************************************************************************************
*  NvM_ActInitRestoreBlockDefaults
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitRestoreBlockDefaults(void)
{
    NvM_CurrentBlockInfo_t.ByteCount_u16 = NvM_CurrentBlockInfo_t.Descriptor_pt->NvBlockLength_u16;
    NvM_CurrentBlockInfo_t.InternalFlags_u8 &= NVM_INTFLAG_ROM_RESTORED_CL;
}

#if (NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3)
/**********************************************************************************************************************
*  NvM_ActInvalidateNvBlock
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActInvalidateNvBlock(void)
{
    if (E_OK != MemIf_InvalidateBlock((uint8)NvM_CurrentBlockInfo_t.Descriptor_pt->DeviceId_u8,
                                      NvM_CurrentBlockInfo_t.NvIdentifier_u16))
    {
        NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_NOT_OK;
    }
    else
    {
        NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_PENDING;
    }
}
#endif /* (NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3) */

/**********************************************************************************************************************
*  NvM_ActNop
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActNop(void)
{
    return;
}

/**********************************************************************************************************************
*  NvM_ActWriteNvBlock
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
 *
 *
 *
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActWriteNvBlock(void)
{
    const NvM_RamAddressType src_pt = NvM_CurrentBlockInfo_t.NvRamAddr_t;
    Std_ReturnType retValMemIf;

    NvM_CurrentBlockInfo_t.WriteRetryCounter_u8++;
    /* Invalidate CRCCompareMechanism data to avoid following situation:
     * block is up to date with NV RAM, but CRC does not fit -> copy the CRC to internal CRC buffer -> reset -> startup ->
     * block is up to date AND the CRC matches the data -> NvM won't write -> RAM does not match NV RAM */
    NvM_IntUpdateCurrentBlockCRCCompareData(NVM_REQ_NOT_OK);
    /* we have to append CRC value to data buffer (for redundant blocks it is okay to do it twice. * 
     * Additionally these operations are allowed, even if no CRC was actually configured            */
    NvM_CrcJob_CopyToBuffer(&NvM_CurrentBlockInfo_t.BlockCrcJob_t); /* SBSW_NvM_FuncCall_PtrParam_CurrBlockInfo */

#if(NVM_CRC_INT_BUFFER == STD_ON)
    /* If we're processing the configured permanent RAM block, we have to copy the CRC into block's Calc Ram Block CRC buffer.
     * The most recent call to NvM_CrcJob_CopyToBuffer copied the CRC value into the internal buffer */
    if(NvM_CurrentJob_t.RamAddr_t == NULL_PTR) /* COV_NVM_APICFGCLASS */
    {
        NvM_CrcJob_ExportBufferedValue(&NvM_CurrentBlockInfo_t.BlockCrcJob_t, /* SBSW_NvM_FuncCall_PtrParam_CurrBlockInfo */
                                        NvM_CurrentBlockInfo_t.Descriptor_pt->RamBlockCrcAddr_t);
    }
#endif

#if(NVM_KILL_WRITEALL_API == STD_ON) /* ECO_IGNORE_LINE */
    /* Prevent from issuing a write job to lower layer, if KillWriteAll was requested.
     *  Critical section, because EcuM (caller of NvM_KilWriteAll)
     *                    might run in a task which preempted our MainFunction!! */
    NvM_EnterCriticalSection();

    if(NvM_IsWriteAllAndKilled(NvM_CurrentJob_t.JobServiceId_t, NvM_ApiFlags_u8)) /* COV_NVM_KILLWRITEALL */
    {
        /* Result is quite irrelevant, but PENDING prevents from write retry handling */
        NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_PENDING;
    }
    else
#endif /* ECO_IGNORE_LINE */
    {
        retValMemIf = MemIf_Write((uint8)NvM_CurrentBlockInfo_t.Descriptor_pt->DeviceId_u8, /* SBSW_NvM_FuncCall_PtrParam_MemIf */
                                                        NvM_CurrentBlockInfo_t.NvIdentifier_u16, src_pt);
        if(E_OK == retValMemIf)
        {
          NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_PENDING;
        }
        else
        {
          NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_NOT_OK;
        }
    }

#if(NVM_KILL_WRITEALL_API == STD_ON)
    NvM_ExitCriticalSection();
#endif
}

/**********************************************************************************************************************
*  NvM_ActReadNvBlock
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
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActReadNvBlock(void)
{
    const NvM_BlockDescrPtrType descr_pt = NvM_CurrentBlockInfo_t.Descriptor_pt;

#if (NVM_USE_CSM == STD_ON)
    NvM_CurrentBlockInfo_t.CsmJobRetryCounter_u8 = 0u;
#endif

    /* Re-init CRC calc job, for two purposes:
     * - if we are processing the secondary NV block of a redundant NVRAM Block, CRC calculation must be restarted
     * - if we are actually processing a CRC block - the internal buffer will be the CRC source.
     * (if we're processing a non-CRC block, it does not matter - it won't be used)
     * First purpose is the reason to re-init CRC job also in case internal buffering was disabled. */
    NvM_CrcJob_Create(&NvM_CurrentBlockInfo_t.BlockCrcJob_t, NvM_CurrentJob_t.JobBlockId_t,
        NvM_CurrentBlockInfo_t.NvRamAddr_t, descr_pt->NvBlockNVRAMDataLength); /* SBSW_NvM_FuncCall_PtrParam_CurrBlockInfo */
    /* Byte Count for Data Copy (after CRC calculation). 
     * We'll go through copy, even if NVM_CRC_INT_BUFFER == STD_OFF (CRC mismatch -> restore ROM defaults */
    NvM_CurrentBlockInfo_t.ByteCount_u16 = descr_pt->NvBlockLength_u16;
    
    if (E_OK == MemIf_Read((uint8)descr_pt->DeviceId_u8, /* SBSW_NvM_FuncCall_PtrParam_MemIf */
        NvM_CurrentBlockInfo_t.NvIdentifier_u16, 0u, NvM_CurrentBlockInfo_t.NvRamAddr_t,
        (uint16)(descr_pt->NvBlockNVRAMDataLength + NvM_CrcJob_GetCrcLength(&NvM_CurrentBlockInfo_t.BlockCrcJob_t))))
    {
        NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_PENDING;
    }
    else
    {
        NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_NOT_OK;
    }
}

/**********************************************************************************************************************
 *  NvM_ActReadNvBlockCrcOnly
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActReadNvBlockCrcOnly(void)
{
  /* CRC job automatically gives the correct length to read */
  const uint8 crcDataLength = NvM_CrcJob_GetCrcLength(&NvM_CurrentBlockInfo_t.BlockCrcJob_t);

  /* CRC is always appended to data */
  const uint16 dataOffsetToCrc = NvM_CurrentBlockInfo_t.Descriptor_pt->NvBlockLength_u16;

  if (E_OK == MemIf_Read((uint8)NvM_CurrentBlockInfo_t.Descriptor_pt->DeviceId_u8,                                      /* SBSW_NvM_FuncCall_PtrParam_MemIf */
      NvM_CurrentBlockInfo_t.NvIdentifier_u16,
      dataOffsetToCrc,
      NvM_SecondaryRedundantBlockCrcData,
      crcDataLength))
  {
    NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_PENDING;
  }
  else
  {
    NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_NOT_OK;
  }
}

/**********************************************************************************************************************
*  NvM_ActProcessCrcRead
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActProcessCrcRead(void)
{
    NvM_CrcJob_Process(&(NvM_CurrentBlockInfo_t.BlockCrcJob_t), NvM_NoOfCrcBytes_u16); /* SBSW_NvM_FuncCall_PtrParam_CurrBlockInfo */
}

/**********************************************************************************************************************
*  NvM_ActReadCopyData
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActReadCopyData(void)
{
    /* #10 Copy data, if internal CRC buffers are enabled, nothing to do otherwise. */
#if(NVM_CRC_INT_BUFFER == STD_ON)
    NvM_InternalCopyBufferedData(&NvM_CurrentBlockInfo_t, NvM_CurrentBlockInfo_t.RamAddr_t); /* SBSW_NvM_FuncCall_PtrParam_CurrBlockInfo */
#else
    NvM_CurrentBlockInfo_t.ByteCount_u16 = 0u;
#endif
}

/**********************************************************************************************************************
*  NvM_InternalCopyBufferedData
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_InternalCopyBufferedData(NvM_BlockInfoPtrType info_pt, NvM_ConstRamAddressType srcPtr)
{
#if(NVM_CRC_INT_BUFFER == STD_ON)
    const NvM_BlockDescrPtrType descr_pt = NvM_CurrentBlockInfo_t.Descriptor_pt;

    /* Mirror Cbk Function shall only be used, if no temporary RAM block was assigned with request */
    if((descr_pt->CbkGetMirrorFunc_pt != NULL_PTR) && (NvM_CurrentJob_t.RamAddr_t == NULL_PTR)) /* COV_NVM_APICFGCLASS */
    { /* client copies on its own -> call callback NvMReadRamBlockFromNvM */
        /* PRQA S 0315 1 */ /* MD_NvM_Dir1.1_CastToVoidPtr */
        if(descr_pt->CbkGetMirrorFunc_pt(srcPtr) == E_OK) /* SBSW_NvM_FuncPtrCall_UserCallbacks */
        {
            info_pt->ByteCount_u16 = 0u; /* SBSW_NvM_Access_CurrBlockInfo */
        }
    }
    else
    {
        const NvM_RamAddressType destPtr = (NvM_CurrentJob_t.RamAddr_t != NULL_PTR) ?
            NvM_CurrentJob_t.RamAddr_t : descr_pt->RamBlockDataAddr_t; /* COV_NVM_APICFGCLASS */
        if(srcPtr != destPtr)
        { /* we copy */
            NvM_InternalCopyData(info_pt, destPtr, srcPtr); /* SBSW_NvM_FuncCall_PtrParam_InternalCopyData */
        }
        else
        { /* don't copy, at all */
            info_pt->ByteCount_u16 = 0u; /* SBSW_NvM_Access_CurrBlockInfo */
        }
    }
#else
    NvM_InternalCopyData(info_pt, info_pt->RamAddr_t, srcPtr); /* SBSW_NvM_FuncCall_PtrParam_InternalCopyData */
#endif
}

/**********************************************************************************************************************
*  NvM_ActRestoreRomDefaults
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
 *
 *
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActRestoreRomDefaults(void)
{
  NvM_CrcJob_Create(&NvM_CurrentBlockInfo_t.BlockCrcJob_t, NvM_CurrentJob_t.JobBlockId_t,
      NULL_PTR, NvM_CurrentBlockInfo_t.Descriptor_pt->NvBlockLength_u16); /* SBSW_NvM_FuncCall_PtrParam_CurrBlockInfo */

  if(NvM_CurrentBlockInfo_t.Descriptor_pt->RomBlockDataAddr_pt != NULL_PTR)
  {
    NvM_InternalCopyBufferedData(&NvM_CurrentBlockInfo_t, /* SBSW_NvM_FuncCall_PtrParam_CurrBlockInfo */
        NvM_CurrentBlockInfo_t.Descriptor_pt->RomBlockDataAddr_pt);

    NvM_CurrentBlockInfo_t.InternalFlags_u8 |= NVM_INTFLAG_ROM_RESTORED_SET;
  }
  else
  {
    if (NvM_QryIsInitCallbackConfigured(NvM_CurrentBlockInfo_t.Descriptor_pt) == TRUE) /* SBSW_NvM_FuncCall_PtrParam_CurrBlockInfo */
    {
      const boolean allowReadAllInvocation =
          NvM_IsBooleanBitfieldTrue(NvM_CurrentBlockInfo_t.Descriptor_pt->Flags.InvokeCallbacksForReadAllEnabled);

      /* Any job allowed for callback; Extra flag check for ReadAll */
      if ((NvM_CurrentJob_t.JobServiceId_t != NVM_INT_FID_READ_ALL) || allowReadAllInvocation) /* COV_NVM_APICFGCLASS */
      {
        if (NvM_CurrentBlockInfo_t.Descriptor_pt->InitCbkExtFunc_pt != NULL_PTR)
        {
          /* Direct invocation of extended callback.
           * RamAddr_t is ensured to be valid while initialization (NvM_ActInitBlock).
           *
           * Note: This code does not consider the configuration possibility of the explicit synchronization feature
           *       "NvMBlockUseSyncMechanism". See TechRef for further information.
           */
          (void)NvM_CurrentBlockInfo_t.Descriptor_pt->InitCbkExtFunc_pt( /* SBSW_NvM_FuncPtrCall_UserCallbacks */
              NvM_CurrentJob_t.JobBlockId_t,
              NvM_CurrentBlockInfo_t.RamAddr_t, /* PRQA S 0315 */ /* MD_NvM_Dir1.1_CastToVoidPtr */
              NvM_CurrentBlockInfo_t.Descriptor_pt->NvBlockLength_u16);
        }
        else
        {
          (void)NvM_CurrentBlockInfo_t.Descriptor_pt->InitCbkFunc_pt(); /* SBSW_NvM_FuncPtrCall_UserCallbacks */
        }

        NvM_CurrentBlockInfo_t.InternalFlags_u8 |= NVM_INTFLAG_ROM_RESTORED_SET;
      }
    }

    NvM_CurrentBlockInfo_t.ByteCount_u16 = 0u;
  }

  NvM_ActWait();
}

/**********************************************************************************************************************
*  NvM_ActFinishRestoreRomDefaults
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActFinishRestoreRomDefaults(void)
{
  /* #10 in case current pending block has a permanent RAM and default data has been restored */
  if((NvM_CurrentJob_t.RamAddr_t == NULL_PTR) &&
      ((NvM_CurrentBlockInfo_t.InternalFlags_u8 & NVM_INTFLAG_ROM_RESTORED_SET) == NVM_INTFLAG_ROM_RESTORED_SET)) /* COV_NVM_APICFGCLASS */
  {
    NvM_CurrentBlockInfo_t.Mngmt_pt->NvRamAttributes_u8 |= (NVM_STATE_VALID_SET | NVM_STATE_CHANGED_SET); /* SBSW_NvM_Access_CurrBlockInfo */

#if((NVM_SET_RAM_BLOCK_STATUS_API == STD_ON) && (NVM_CALC_RAM_CRC_USED == STD_ON))
    /* New data available. Recalculate CRC. */
    NvM_CrcQueueJob(NvM_CurrentJob_t.JobBlockId_t);
#endif
  }

  /* NvM_RestoreBlockDefaults never results in NVM_REQ_RESTORED_FROM_ROM, but always results in in NVM_REQ_OK (cannot fail).
   * NVM_REQ_RESTORED_FROM_ROM is only relevant for reading and will be set within the read block state machine.
   * INTFLAG_ROM_RESTORED can be used to differ between restored/ not restored data, but must not modify the
   * job result! Within RestoreBlockDefaults the default data will always be loaded. */
  NvM_IntUpdateCurrentBlockCRCCompareData(NVM_REQ_NOT_OK);
}

/**********************************************************************************************************************
*  NvM_ActSetInitialAttr
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActSetInitialAttr(void)
{
    uint8 attribs_u8loc;

    /* set the write protection attribute if NVM_BLOCK_WRITE_PROT is TRUE */
    if (NvM_IsBooleanBitfieldTrue(NvM_CurrentBlockInfo_t.Descriptor_pt->Flags.BlockWriteProtEnabled))
    {
        /* set the write protection (we don't need to set one bit, since it is
         * the only value that shall be set, all other bits are zero)
         */
         attribs_u8loc = NVM_WR_PROT_SET;
    }
    else
    {
        /* clear all bits */
          attribs_u8loc = 0u;
    }

    /* Overwrite all attribute flags with configured write protection setting. */
    NvM_CurrentBlockInfo_t.Mngmt_pt->NvRamAttributes_u8 = attribs_u8loc; /* SBSW_NvM_Access_CurrBlockInfo */
}

/**********************************************************************************************************************
*  NvM_ActSetReqIntegrityFailed
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActSetReqIntegrityFailed(void)
{
    NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_INTEGRITY_FAILED;
}

/**********************************************************************************************************************
*  NvM_ActSetReqSkipped
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActSetReqSkipped(void)
{
    NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_BLOCK_SKIPPED;
}

/**********************************************************************************************************************
*  NvM_ActSetReqNotOk
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActSetReqNotOk(void)
{
  NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_NOT_OK;
}

/**********************************************************************************************************************
*  NvM_SetBlockPendingWriteAll
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_SetBlockPendingWriteAll(void)
{
    NvM_CurrentBlockInfo_t.Mngmt_pt->NvRamErrorStatus_u8 = NVM_REQ_PENDING; /* SBSW_NvM_Access_CurrBlockInfo */
    NvM_BlockNotification(NvM_CurrentJob_t.JobBlockId_t, NVM_WRITE_ALL, NVM_REQ_PENDING);
}

/**********************************************************************************************************************
*  NvM_ActSetupRedundant
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActSetupRedundant(void)
{
    /* updates NvState for current block and changes active block */
    NvM_ActUpdateNvState();

    NvM_CurrentBlockInfo_t.NvIdentifier_u16 |= 0x01u;

    NvM_CurrentBlockInfo_t.WriteRetryCounter_u8 = 0u;
}

/**********************************************************************************************************************
*  NvM_ActSetupOther
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActSetupOther(void)
{
     /* reset retry counter */
    NvM_CurrentBlockInfo_t.WriteRetryCounter_u8 = 0u;

    /* activate the inactive NvBlock */
    NvM_CurrentBlockInfo_t.NvIdentifier_u16 ^= 0x0001u;
    
    NvM_ActUpdateNvState();
}

/**********************************************************************************************************************
*  NvM_ActUpdateNvState
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActUpdateNvState(void)
{
    uint8 NvBlockState_u8;
    
    switch (NvM_CurrentBlockInfo_t.LastResult_t)
    {
        case (NVM_REQ_OK):
            /* set NvBlock state uptodate */
            NvBlockState_u8 = NVM_NVBLOCK_STATE_UPTODATE;
            break;

        case (NVM_REQ_NV_INVALIDATED):
            /* set NvBlock state outdated */
            NvBlockState_u8 = NVM_NVBLOCK_STATE_OUTDATED;
            break;

        default:
            /* set NvBlock state defect */
            NvBlockState_u8 = NVM_NVBLOCK_STATE_DEFECT;
            break;
    }

    /* save NvBlock state */
    NvM_IntCreateNvState(&NvM_CurrentBlockInfo_t.NvState_u8, NvBlockState_u8); /* SBSW_NvM_FuncCall_PtrParam_CurrBlockInfo */

    /* mark the other NvBlock active */
    NvM_CurrentBlockInfo_t.NvState_u8 ^= NVM_NVBLOCK_STATE_SEC_ACTIVE;
}

/**********************************************************************************************************************
*  NvM_IntCreateNvState
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_IntCreateNvState(P2VAR(uint8, AUTOMATIC, NVM_PRIVATE_DATA) NvState, uint8 NewState)
{
    uint8 shift;

    /* determine shift factor */
    if((*NvState & NVM_NVBLOCK_STATE_SEC_ACTIVE) != 0u)
    {
        shift = NVM_SEC_NVBLOCK_STATE_SHIFT;        
    }
    else
    {
        shift = NVM_PRI_NVBLOCK_STATE_SHIFT;        
    }

    /* #10 set state of current NvBlock to 0x00 */
    *NvState &= (NVM_NVBLOCK_STATE_UNKNOWN << shift) ^ 0xFFu; /* SBSW_NvM_Access_CurrBlockInfo */

    /* #20 set new state */
    *NvState |= (uint8)(NewState << shift); /* SBSW_NvM_Access_CurrBlockInfo */
}

/**********************************************************************************************************************
*  NvM_ActGetMultiBlockJob
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
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActGetMultiBlockJob(void)
 {
    const uint8 multiJobFlags = NvM_ApiFlags_u8;

    NvM_CurrentJob_t.JobBlockId_t   = 0x00u;
    NvM_CurrentJob_t.RamAddr_t      = NULL_PTR; /* this is essential for further processing! */

    if ((multiJobFlags & NVM_APIFLAG_WRITE_ALL_SET) != 0u)
    {
        NvM_CurrentJob_t.JobServiceId_t = NVM_INT_FID_WRITE_ALL;
        /* WriteAll: begin with last block and end with configuration block */
        NvM_CurrentJob_t.JobBlockId_t = (NvM_NoOfBlockIds_t - 1u);
    }
    else if ((multiJobFlags & NVM_APIFLAG_READ_ALL_SET) != 0u) /* COV_NVM_MISRA */
    {
        NvM_CurrentJob_t.JobServiceId_t = NVM_INT_FID_READ_ALL;
        /* ReadAll: begin with configuration block and end with last block */
        NvM_CurrentJob_t.JobBlockId_t = 1u;
    }
#if (NVM_REPAIR_REDUNDANT_BLOCKS_API == STD_ON) /* ECO_IGNORE_LINE */
    else if ((multiJobFlags & NVM_APIFLAG_REPAIR_REDUNDANT_BLOCKS_SET) != 0u) /* COV_NVM_MISRA */
    {
        NvM_CurrentJob_t.JobServiceId_t = NVM_INT_FID_REPAIR_REDUNDANT_BLOCKS;
    }
#endif /* ECO_IGNORE_LINE */
    else
    {
        /* Nothing to do, should not happen, since this function will be called, if
         * NvM_QryHighMultiJob returned true --> one flag must be set */
    }
 }

/**********************************************************************************************************************
*  NvM_ActTestBlockBlank
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActTestBlockBlank(void)
{
    /* read one byte of the block to a temp buffer to see if the nv
     * is still empty. 
     */
    if(E_OK == MemIf_Read((uint8)NvM_CurrentBlockInfo_t.Descriptor_pt->DeviceId_u8, /* SBSW_NvM_FuncCall_PtrParam_MemIf */
        NvM_CurrentBlockInfo_t.NvIdentifier_u16, 0u, &NvM_TestBuffer_u8, 1u))
    {
        NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_PENDING;
    }
    else
    {
        NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_NOT_OK;
    }
}

/**********************************************************************************************************************
*  NvM_ActValidateRam
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActValidateRam(void)
{
    /* Are we operating on the permanent RAM block? (NULL_PTR implies permanent RAM block or Mirror Cbk!) */
    if(NvM_CurrentJob_t.RamAddr_t == NULL_PTR) /* COV_NVM_APICFGCLASS */
    {
#if (NVM_SET_RAM_BLOCK_STATUS_API == STD_ON)
        /* only make valid, do not change the CHANGED flag) */
        NvM_CurrentBlockInfo_t.Mngmt_pt->NvRamAttributes_u8 |= NVM_STATE_VALID_SET; /* SBSW_NvM_Access_CurrBlockInfo */
        NvM_CurrentBlockInfo_t.Mngmt_pt->NvRamAttributes_u8 &= NVM_STATE_CHANGED_CL; /* SBSW_NvM_Access_CurrBlockInfo */
#else
        /* make valid AND changed, because the application cannot do it. */
        NvM_CurrentBlockInfo_t.Mngmt_pt->NvRamAttributes_u8 |= (NVM_STATE_VALID_SET | NVM_STATE_CHANGED_SET); /* SBSW_NvM_Access_CurrBlockInfo */
#endif
    }
}

/**********************************************************************************************************************
*  NvM_ActWait
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActWait(void)
{
    NvM_CurrentBlockInfo_t.InternalFlags_u8 |= NVM_INTFLAG_WAIT_SET;
}

/**********************************************************************************************************************
*  NvM_ActCopyNvDataToBuf
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActCopyNvDataToBuf(void)
{
#if(NVM_CRC_INT_BUFFER == STD_ON) /* ECO_IGNORE_LINE */
    /* Pointer in BlockCrcJob_t points to internal buffer so that Crc is calculated later about data in internal buffer. */
    const NvM_BlockDescrPtrType descr_pt = NvM_CurrentBlockInfo_t.Descriptor_pt;  

    /* #10 Explicit synchronization enabled -> get data to write from user. */
    if((descr_pt->CbkSetMirrorFunc_pt != NULL_PTR) && (NvM_CurrentJob_t.RamAddr_t == NULL_PTR)) /* COV_NVM_APICFGCLASS */
    {
        /* PRQA S 0315 1 */ /* MD_NvM_Dir1.1_CastToVoidPtr */
        if(descr_pt->CbkSetMirrorFunc_pt(NvM_InternalBuffer_au8) == E_OK) /* SBSW_NvM_FuncPtrCall_UserCallbacks */
        {
            NvM_CurrentBlockInfo_t.ByteCount_u16 = 0u;
        }
    }
    /* #20 No explicit synchronization but CRC enabled -> copy the RAM data to the internal buffer. */
    else if(descr_pt->CrcSettings > NVM_BLOCK_USE_CRC_OFF)
    {
        NvM_ConstRamAddressType ramAddr = (NvM_CurrentJob_t.RamAddr_t != NULL_PTR) ?
            NvM_CurrentJob_t.RamAddr_t : NvM_CurrentBlockInfo_t.Descriptor_pt->RamBlockDataAddr_t; /* COV_NVM_APICFGCLASS */

        NvM_InternalCopyData(&NvM_CurrentBlockInfo_t,  NvM_CurrentBlockInfo_t.RamAddr_t, ramAddr); /* SBSW_NvM_FuncCall_PtrParam_CurrBlockInfo */
    }
    /* #30 No explicit synchronization and no CRC, nothing to do. */
    else
    {
        NvM_CurrentBlockInfo_t.ByteCount_u16 = 0u;
    }
#endif /* ECO_IGNORE_LINE */
    /* #40 Data preparation done and pre write transformation enabled -> pass the data to the transformation callback. */
    if(
#if(NVM_CRC_INT_BUFFER == STD_ON)
        /* ByteCount not relevant in case the internal buffers are disabled -> no copy */
        (NvM_CurrentBlockInfo_t.ByteCount_u16 == 0u) &&
#endif
            (NvM_CurrentBlockInfo_t.Descriptor_pt->CbkPreWriteTransform != NULL_PTR))
    {
        NvM_CurrentBlockInfo_t.Descriptor_pt->CbkPreWriteTransform(NvM_CurrentJob_t.JobBlockId_t, /* SBSW_NvM_FuncPtrCall_UserCallbacks */
            /* PRQA S 0315 1 */ /* MD_NvM_Dir1.1_CastToVoidPtr */
            NvM_CurrentBlockInfo_t.RamAddr_t, NvM_CurrentBlockInfo_t.Descriptor_pt->NvBlockLength_u16);
    }
}

/**********************************************************************************************************************
 * NvM_ActKillSubFsm
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActKillSubFsm(void)
{
    NvM_JobSubState_t = NVM_STATE_FSM_FINISHED;
}

/**********************************************************************************************************************
 *  NvM_ActNotifyLossOfRedundancy
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActNotifyLossOfRedundancy(void)
{
  NvM_NotifyLossOfRedundancy(NvM_CurrentJob_t.JobBlockId_t);
}

#if (NVM_REPAIR_REDUNDANT_BLOCKS_API == STD_ON)
/**********************************************************************************************************************
 * NvM_ActRepairRedBlocksInit
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActRepairRedBlocksInit(void)
{
    /* use the latest suspended block id or the configuration block to begin repairing with */
    NvM_CurrentJob_t.JobBlockId_t = (NvM_RepairRedBlockState.CurrentBlockId == 0u) ? 1u : NvM_RepairRedBlockState.CurrentBlockId;

    NVM_ActRepairRedBlocksInitBlock();
}

/**********************************************************************************************************************
 * NvM_ActRepairRedBlocksInitNext
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActRepairRedBlocksInitNext(void)
{
    /* search to last block for the next redundant block */
    do
    {
        NvM_CurrentJob_t.JobBlockId_t++;
    }while((NvM_CurrentJob_t.JobBlockId_t < NvM_NoOfBlockIds_t) &&
        (NvM_BlockDescriptorTable_at[NvM_CurrentJob_t.JobBlockId_t].MngmtType_t != NVM_BLOCK_REDUNDANT));

    /* only initialize the block in case it exists */
    if(NvM_CurrentJob_t.JobBlockId_t < NvM_NoOfBlockIds_t)
    {
        NVM_ActRepairRedBlocksInitBlock();
    }
}

/**********************************************************************************************************************
 * NVM_ActRepairRedBlocksInitBlock
 *********************************************************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NVM_ActRepairRedBlocksInitBlock(void)
{
    const NvM_BlockIdType orgBlockId = NVM_BLOCK_FROM_DCM_ID(NvM_CurrentJob_t.JobBlockId_t);
    const NvM_BlockDescrPtrType DescrPtr = &NvM_BlockDescriptorTable_at[orgBlockId];
    /* #10 Store current block's information. */
    NvM_CurrentBlockInfo_t.Mngmt_pt = &NvM_BlockMngmtArea_at[orgBlockId];
    NvM_CurrentBlockInfo_t.Descriptor_pt = DescrPtr;
    NvM_CurrentBlockInfo_t.NvIdentifier_u16 = DescrPtr->NvIdentifier_u16;
    NvM_CurrentBlockInfo_t.ByteCount_u16 = 0u;
    /* Use:
     * CipheredDataBuffer: if data ciphering is enabled and the block stores ciphered data,
     * InternalBuffer: if data ciphering is disabled or the block stores plain data.
     * This ensures the used buffer is large enough to store the current block (ciphered data
     * may be > or < internal buffer length!).
     * The RamAddr will never be used! */
#if(NVM_USE_CSM == STD_ON)
    if(NvM_QryIsCipherBlock(NvM_CurrentBlockInfo_t.Descriptor_pt) == TRUE) /* SBSW_NvM_FuncCall_PtrParam_CurrBlockInfo */
    {
        NvM_CurrentBlockInfo_t.NvRamAddr_t = NvM_CipheredDataBuffer;
        NvM_CurrentBlockInfo_t.RamAddr_t = NvM_CipheredDataBuffer;
    }
    else
#endif
    {
        NvM_CurrentBlockInfo_t.NvRamAddr_t = NvM_InternalBuffer_au8;
        NvM_CurrentBlockInfo_t.RamAddr_t = NvM_InternalBuffer_au8;
    }
    /* #30 Setup repair redundant block job. */
    NvM_RepairRedBlockState.CurrentBlockId = NvM_CurrentJob_t.JobBlockId_t;
    NvM_RepairRedBlockState.NvBlockState = NVM_NVBLOCK_STATE_UPTODATE;
    NvM_RepairRedBlockState.CrcBuffer = 0u;
}

/**********************************************************************************************************************
 * NvM_ActRepairRedBlockReadCheck
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
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActRepairRedBlockReadCheck(void)
{
    const NvM_BlockDescrPtrType descr_pt = NvM_CurrentBlockInfo_t.Descriptor_pt;
    uint16 blockLength;
    NvM_RamAddressType readDest_pt;

    /* #10 for blocks without Crc */
    if(descr_pt->CrcSettings == NVM_BLOCK_USE_CRC_OFF)
    {
        blockLength = 1;
        readDest_pt = &NvM_TestBuffer_u8;
    }
    /* #20 for blocks with Crc */
    else
    {
        /* #21 use internal buffer */
        readDest_pt = NvM_CurrentBlockInfo_t.NvRamAddr_t;
        /* #22 create Crc job */
        NvM_CrcJob_Create(&NvM_CurrentBlockInfo_t.BlockCrcJob_t, NvM_CurrentJob_t.JobBlockId_t,
            readDest_pt, NvM_CurrentBlockInfo_t.Descriptor_pt->NvBlockNVRAMDataLength); /* SBSW_NvM_FuncCall_PtrParam_CurrBlockInfo */
        /* NvM_CurrentBlockInfo_t.ByteCount_u16 = descr_pt->NvBlockLength_u16; */
        /* #23 adjust local block length to read the whole data */
        blockLength = descr_pt->NvBlockNVRAMDataLength + NvM_CrcJob_GetCrcLength(&NvM_CurrentBlockInfo_t.BlockCrcJob_t);
    }

    /* #30 setup read job */
    if (MemIf_Read((uint8)descr_pt->DeviceId_u8, NvM_CurrentBlockInfo_t.NvIdentifier_u16, 0u, readDest_pt, /* SBSW_NvM_FuncCall_PtrParam_MemIf */
        (uint16)blockLength) == E_OK)
    {
        NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_PENDING;
    }
    else
    {
        NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_NOT_OK;
    }
}

/**********************************************************************************************************************
 * NvM_ActRepairRedBlockFinishReadCheck
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActRepairRedBlockFinishReadCheck(void)
{
    uint8 stateShift =
        (NvM_CurrentBlockInfo_t.Descriptor_pt->NvIdentifier_u16 == NvM_CurrentBlockInfo_t.NvIdentifier_u16) ? 0u : 4u;

    boolean blockValid = FALSE;

    if(NvM_CurrentBlockInfo_t.LastResult_t == NVM_REQ_OK)
    {
        if(NvM_CurrentBlockInfo_t.Descriptor_pt->CrcSettings != NVM_BLOCK_USE_CRC_OFF)
        {
            /* block has Crc we have to check it to validate the block */
            blockValid = NvM_CrcJob_Compare(&NvM_CurrentBlockInfo_t.BlockCrcJob_t); /* SBSW_NvM_FuncCall_PtrParam_CurrBlockInfo */

            /* store Crc only for the first block */
            if(stateShift == 0u)
            {
                /* copy Crc to job internal buffer to be used to compare with second block's Crc later */
                NvM_RepairRedBlockState.CrcBuffer = NvM_CurrentBlockInfo_t.BlockCrcJob_t.CurrentCrcValue;
            }
        }
        else
        {
            /* no Crc to check, block readable == valid */
            blockValid = TRUE;
        }
    }

    /* #20 set block to defect or valid depending on previous check result */
    NvM_RepairRedBlockState.NvBlockState |= blockValid ?
        (NVM_NVBLOCK_STATE_UPTODATE << stateShift) : (NVM_NVBLOCK_STATE_DEFECT << stateShift);

    /* #30 prepare job for next sub-block (important only for first sub-block to read the second one) */
    NvM_CurrentBlockInfo_t.NvIdentifier_u16 |= 1u;
}

/**********************************************************************************************************************
 * NvM_ActRepairRedBlocksReadValid
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActRepairRedBlocksReadValid(void)
{
    /* we do not have to check whether only one block is defect - this is done previously - this function
     * shall not be invoked in case BOTH blocks are defect or valid!  */

    uint8 crcNrOfBytes = 0u;

    /* first block is defect, read second block */
    if((NvM_RepairRedBlockState.NvBlockState & 0x0Fu) == NVM_NVBLOCK_STATE_DEFECT)
    {
        NvM_CurrentBlockInfo_t.NvIdentifier_u16 = NvM_CurrentBlockInfo_t.Descriptor_pt->NvIdentifier_u16 + 1u;
    }
    /* second block is defect, read first block */
    else
    {
        NvM_CurrentBlockInfo_t.NvIdentifier_u16 = NvM_CurrentBlockInfo_t.Descriptor_pt->NvIdentifier_u16;
    }

    if(NvM_CurrentBlockInfo_t.Descriptor_pt->CrcSettings != NVM_BLOCK_USE_CRC_OFF)
    {
        crcNrOfBytes = NvM_CrcJob_GetCrcLength(&NvM_CurrentBlockInfo_t.BlockCrcJob_t);
    }

    /* read valid block */
    if (MemIf_Read((uint8)NvM_CurrentBlockInfo_t.Descriptor_pt->DeviceId_u8, NvM_CurrentBlockInfo_t.NvIdentifier_u16, /* SBSW_NvM_FuncCall_PtrParam_MemIf */
        0u, NvM_CurrentBlockInfo_t.NvRamAddr_t, (uint16)(NvM_CurrentBlockInfo_t.Descriptor_pt->NvBlockNVRAMDataLength + crcNrOfBytes))
        == E_OK)
    {
        NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_PENDING;
    }
    else
    {
        NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_NOT_OK;
    }
}

/**********************************************************************************************************************
 * NvM_ActRepairRedBlockWriteInvalid
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActRepairRedBlockWriteInvalid(void)
{
    /* we do not have to check whether only one block is defect - this is done previously - this function
     * shall not be invoked in case both blocks are defect or valid!  */

    /* first block is defect, write the first block */
    if((NvM_RepairRedBlockState.NvBlockState & 0x0Fu) == NVM_NVBLOCK_STATE_DEFECT)
    {
        NvM_CurrentBlockInfo_t.NvIdentifier_u16 = NvM_CurrentBlockInfo_t.Descriptor_pt->NvIdentifier_u16;
    }
    /* second block is defect, write the second block */
    else
    {
        NvM_CurrentBlockInfo_t.NvIdentifier_u16 = NvM_CurrentBlockInfo_t.Descriptor_pt->NvIdentifier_u16 + 1u;
    }

    /* write defect block */
    if(MemIf_Write((uint8)NvM_CurrentBlockInfo_t.Descriptor_pt->DeviceId_u8, /* SBSW_NvM_FuncCall_PtrParam_MemIf */
        NvM_CurrentBlockInfo_t.NvIdentifier_u16, NvM_CurrentBlockInfo_t.NvRamAddr_t) == E_OK)
    {
        NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_PENDING;
    }
    else
    {
        NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_NOT_OK;
    }
}

/**********************************************************************************************************************
 * NvM_ActRepairRedBlocksFinishBlock
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActRepairRedBlocksFinishBlock(void)
{
    /* NvM tried to repair a redundant block via overwriting the defect one with valid one */
    /* in case the overwriting wasn't successful, the redundancy is lost and we report the corresponding DEM error */
    if(NvM_CurrentBlockInfo_t.LastResult_t != NVM_REQ_OK)
    {
        NvM_DemReportErrorLossOfRedundancy();
    }

    /* do not change any internal states or results here! redundant block repair is an background job without results! */
}

/**********************************************************************************************************************
 * NvM_ActRepairRedBlocksFinish
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActRepairRedBlocksFinish(void)
{
    NvM_RepairRedBlockState.CurrentBlockId = 0u;
    NvM_RepairRedBlockState.CrcBuffer = 0u;
    NvM_RepairRedBlockState.NvBlockState = NVM_NVBLOCK_STATE_UPTODATE;

    /* clear job flag */
    NvM_ApiFlags_u8 &= NVM_APIFLAG_REPAIR_REDUNDANT_BLOCKS_CL;
}
#endif /* (NVM_REPAIR_REDUNDANT_BLOCKS_API == STD_ON) */

/**********************************************************************************************************************
*  NvM_ActProcessCrc
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActProcessCrc(void)
{
    NvM_CrcJob_Process(&NvM_CurrentBlockInfo_t.BlockCrcJob_t, NvM_NoOfCrcBytes_u16); /* SBSW_NvM_FuncCall_PtrParam_CurrBlockInfo */
}

#if (NVM_DYNAMIC_CONFIGURATION == STD_ON)
/**********************************************************************************************************************
*  NvM_UpdateConfigIdBlock
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_UpdateConfigIdBlock(void) /* PRQA S 3219 */ /* MD_MSR_Unreachable */
{
    NvM_CurrentBlockInfo_t.ByteCount_u16 = NvM_CurrentBlockInfo_t.Descriptor_pt->NvBlockLength_u16;

    NvM_InternalCopyBufferedData(&NvM_CurrentBlockInfo_t, NvM_CompiledConfigId_t.Bytes_au8); /* SBSW_NvM_FuncCall_PtrParam_CurrBlockInfo */

    NvM_CurrentBlockInfo_t.Mngmt_pt->NvRamAttributes_u8 |= (NVM_STATE_CHANGED_SET | NVM_STATE_VALID_SET); /* SBSW_NvM_Access_CurrBlockInfo */
}
#endif /* (NVM_DYNAMIC_CONFIGURATION == STD_ON) */

/**********************************************************************************************************************
*  NvM_InternalCopyData
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_InternalCopyData(
    NvM_BlockInfoPtrType info_pt, NvM_RamAddressType destPtr, NvM_ConstRamAddressType srcPtr)
{
    /* #10 Calculate the length to copy: one step or the remaining bytes (< one step). */
    uint16 length = (info_pt->ByteCount_u16 < NVM_MAX_DATA_COPY_BYTES) ?    
                     info_pt->ByteCount_u16 : NVM_MAX_DATA_COPY_BYTES;
    /* #20 Decrease the remaining length count by the length to copy. */
    info_pt->ByteCount_u16 -= length; /* SBSW_NvM_Access_CurrBlockInfo */
    /* #30 Copy the data from source to destination starting with the next byte to copy and the calculated length. */
    {
        /* Just a short "hack" to avoid calculation of the actual position within the loop. */
        NvM_RamAddressType currDestPtr = &destPtr[info_pt->ByteCount_u16];
        NvM_ConstRamAddressType currSrcPtr = &srcPtr[info_pt->ByteCount_u16];

        while(length > 0u)
        {
            --length;
            currDestPtr[length] = currSrcPtr[length]; /* SBSW_NvM_AccessArray_InternalCopyData */
        }
    }
}

#if (NVM_KILL_WRITEALL_API == STD_ON)
/**********************************************************************************************************************
*  NvM_IsWriteAllAndKilled
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_IsWriteAllAndKilled(const NvM_InternalServiceIdType currServiceId, const uint8 currApiFlag)
{
    return (boolean)((currServiceId == NVM_INT_FID_WRITE_ALL) && ((currApiFlag & NVM_APIFLAG_KILL_WR_ALL_SET) != 0u)); /* COV_NVM_KILLWRITEALL */
}
#endif /* (NVM_KILL_WRITEALL_API == STD_ON) */

/**********************************************************************************************************************
 * NvM_IntUpdateCurrentBlockCRCCompareData
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_IntUpdateCurrentBlockCRCCompareData(const NvM_RequestResultType result)
{
  if (NvM_CurrentBlockInfo_t.Descriptor_pt->CRCCompMechanismCrcAddr_t != NULL_PTR)
  {
    if (result == NVM_REQ_OK)
    {
      /* Update CRCCompareMechanism data */
      NvM_CrcJob_ExportBufferedValue(
          &NvM_CurrentBlockInfo_t.BlockCrcJob_t,
          NvM_CurrentBlockInfo_t.Descriptor_pt->CRCCompMechanismCrcAddr_t); /* SBSW_NvM_FuncCall_PtrParam_CurrBlockInfo */
    }
    else
    {
      /* Invalidate CRCCompareMechanism data */
      uint8 i;
      for (i = 0u; i < NvM_CrcJob_GetCrcLength(&NvM_CurrentBlockInfo_t.BlockCrcJob_t); i++)
      {
        NvM_CurrentBlockInfo_t.Descriptor_pt->CRCCompMechanismCrcAddr_t[i] = 0xFFu; /* SBSW_NvM_AccessArray_CrcBuffers */
      }
    }
  }
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * NvM_ActCancelNV
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, NVM_PRIVATE_CODE) NvM_ActCancelNV(void)
{
    /* Hint: the BUSY check is necessary because canceling in idle state leads to a DET! */
    if(MemIf_GetStatus((uint8)NvM_CurrentBlockInfo_t.Descriptor_pt->DeviceId_u8) == MEMIF_BUSY)
    {
        MemIf_Cancel((uint8)NvM_CurrentBlockInfo_t.Descriptor_pt->DeviceId_u8);
    }
}

/**********************************************************************************************************************
*  NvM_ActFinishReadBlockAndSetSkipped
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, NVM_PRIVATE_CODE) NvM_ActFinishReadBlockAndSetSkipped(void)
{
    NvM_ActFinishReadBlock();
    NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_BLOCK_SKIPPED;
}

/**********************************************************************************************************************
*  NvM_ActSetReqOk
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, NVM_PRIVATE_CODE) NvM_ActSetReqOk(void)
{
    NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_OK;
}

/**********************************************************************************************************************
*  NvM_BlockNotification
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
 *
 *
 */
void NvM_BlockNotification(NvM_BlockIdType BlockId, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult)
{
  /* The complete function body is designed to be optimized away by the compiler, if it is not needed    *
   * If the used macros are empty, the compiler may decide to remove code because it would contain       *
   * empty execution blocks (it does not matter whether conditions were TRUE or FALSE                    */
  const NvM_BlockIdType orgBlockId = NVM_BLOCK_FROM_DCM_ID(BlockId);
  const NvM_BlockDescrPtrType blockDescriptorPtr = &NvM_BlockDescriptorTable_at[orgBlockId];

  if (orgBlockId == BlockId)
  {
    const boolean allowReadAllInvocation =
        NvM_IsBooleanBitfieldTrue(blockDescriptorPtr->Flags.InvokeCallbacksForReadAllEnabled);

    const boolean allowWriteAllInvocation =
        NvM_IsBooleanBitfieldTrue(blockDescriptorPtr->Flags.InvokeCallbacksForWriteAllEnabled);

    if( (JobResult != NVM_REQ_PENDING)
        && ((ServiceId != NVM_WRITE_ALL) || allowWriteAllInvocation)
        && ((ServiceId != NVM_READ_ALL) || allowReadAllInvocation))
    {
      if (blockDescriptorPtr->JobEndCbkFunc_pt != NULL_PTR)
      {
        (void)blockDescriptorPtr->JobEndCbkFunc_pt(ServiceId, JobResult); /* SBSW_NvM_FuncPtrCall_UserCallbacks */
      }

      if (blockDescriptorPtr->JobEndCbkExtFunc_pt != NULL_PTR)
      {
        (void)blockDescriptorPtr->JobEndCbkExtFunc_pt(BlockId, ServiceId, JobResult); /* SBSW_NvM_FuncPtrCall_UserCallbacks */
      }
    }

    if(blockDescriptorPtr->Flags.NotifyBswM == NVM_BLOCK_NOTIFY_BSWM_ON)
    {
      NvM_invokeCurrentBlockMode(BlockId, JobResult);
    }
  }
}

#define NVM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  END OF FILE: NvM_Act.c
 *********************************************************************************************************************/
