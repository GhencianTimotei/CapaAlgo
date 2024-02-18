/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  NvM_Act.h
 *        \brief  NvM action submodule header file
 *      \details  This submodule implements actions to be performed upon state transitions.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#if (!defined NVM_ACT_H_)
#define NVM_ACT_H_

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef enum
{
    NVM_ACT_ID_SetInitialAttr,
    NVM_ACT_ID_InitMainFsm,
    NVM_ACT_ID_InitBlock,
    NVM_ACT_ID_InitReadAll,
    NVM_ACT_ID_InitReadBlockSubFsm,
    NVM_ACT_ID_InitRestoreBlockDefaultsSubFsm,
    NVM_ACT_ID_InitWriteAll,
    NVM_ACT_ID_InitWriteBlock,
    NVM_ACT_ID_InitWriteBlockFsm,
    NVM_ACT_ID_InitRestoreBlockDefaults,
    NVM_ACT_ID_FinishMainJob,
#if (NVM_KILL_WRITEALL_API == STD_ON)
    NVM_ACT_ID_KillWritAll,
#endif
    NVM_ACT_ID_FinishBlock,
    NVM_ACT_ID_InitNextBlockReadAll,
    NVM_ACT_ID_InitNextBlockWriteAll,
    NVM_ACT_ID_FinishCfgIdCheck,
    NVM_ACT_ID_FinishReadBlock,
    NVM_ACT_ID_FinishWriteBlock,
#if (NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3)
    NVM_ACT_ID_FinishEraseBlock,
    NVM_ACT_ID_EraseNvBlock,
    NVM_ACT_ID_InvalidateNvBlock,
#endif
    NVM_ACT_ID_ProcessCrc,
    NVM_ACT_ID_WriteNvBlock,
    NVM_ACT_ID_ReadNvBlock,
    NVM_ACT_ID_ReadNvBlockCrcOnly,
    NVM_ACT_ID_ProcessCrcRead,
    NVM_ACT_ID_ReadCopyData,
    NVM_ACT_ID_RestoreRomDefaults,
    NVM_ACT_ID_FinishRestoreRomDefaults,
    NVM_ACT_ID_TestBlockBlank,
    NVM_ACT_ID_ValidateRam,
    NVM_ACT_ID_SetupRedundant,
    NVM_ACT_ID_SetupOther,
    NVM_ACT_ID_UpdateNvState,
    NVM_ACT_ID_SetReqIntegrityFailed,
    NVM_ACT_ID_SetReqSkipped,
    NVM_ACT_ID_SetReqNotOk,
    NVM_ACT_ID_SetReqOk,
    NVM_ACT_ID_SetBlockPendingWriteAll,
    NVM_ACT_ID_CopyNvDataToBuf,
    NVM_ACT_ID_GetMultiBlockJob,
    NVM_ACT_ID_CancelNV,
    NVM_ACT_ID_KillSubFsm,
    NVM_ACT_ID_NotifyLossOfRedundancy,
    NVM_ACT_ID_FinishReadBlockAndSetSkipped,
#if (NVM_REPAIR_REDUNDANT_BLOCKS_API == STD_ON)
    NVM_ACT_ID_RepairRedBlocksInit,
    NVM_ACT_ID_RepairRedBlocksInitNext,
    NVM_ACT_ID_RepairRedBlockReadCheck,
    NVM_ACT_ID_RepairRedBlockFinishReadCheck,
    NVM_ACT_ID_RepairRedBlocksReadValid,
    NVM_ACT_ID_RepairRedBlockWriteInvalid,
    NVM_ACT_ID_RepairRedBlocksFinishBlock,
    NVM_ACT_ID_RepairRedBlocksFinish,
#endif
#if (NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1)
    NVM_ACT_ID_GetNormalPrioJob,
# if (NVM_JOB_PRIORISATION == STD_ON)
        NVM_ACT_ID_GetHighPrioJob,
        NVM_ACT_ID_QueueFreeLastJob,
# endif
#endif
    NVM_ACT_ID_Wait,
    NVM_ACT_ID_Nop
} NvM_StateActionIdType; /*!< Enumeration of action handler IDs. */

typedef P2FUNC(void, NVM_PRIVATE_CODE, NvM_ActFctPtrType) (void); /*!< Action function pointer type. */

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
/* because of platform independence we cannot say anything about a pointer's
 * size. So we use the "UNSPECIFIED" section
 */
#define NVM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! The Action function table, indexed by NvM_StateActionIdType. */
extern CONST(NvM_ActFctPtrType, NVM_PRIVATE_CONST) NvM_ActionTable_ap[(uint32)NVM_ACT_ID_Nop + 1u];

#define NVM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define NVM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 * NvM_ActCancelNV
 *********************************************************************************************************************/
/*!
 * \brief If the underlying module is BUSY, it will be canceled (via MemIf_Cancel).
 * \details -
 * \context TASK
 * \reentrant FALSE
 * \synchronous TRUE
 * \pre -
 */
FUNC(void, NVM_PRIVATE_CODE) NvM_ActCancelNV(void);

/**********************************************************************************************************************
 * NvM_ActFinishReadBlockAndSetSkipped
 *********************************************************************************************************************/
/*!
 * \brief Combines call of NvM_ActFinishReadBlock and setting of the current internal result to NVM_REQ_SKIPPED.
 * \details This function shall be used wherever the combination of the ActFinishReadBlock and setting of the
 *          result to SKIPPED is needed - the state machine cannot be extended where needed now, this is a workround!
 * \context TASK
 * \reentrant FALSE
 * \synchronous TRUE
 * \pre -
 */
FUNC(void, NVM_PRIVATE_CODE) NvM_ActFinishReadBlockAndSetSkipped(void);

/**********************************************************************************************************************
 * NvM_ActSetReqOk
 *********************************************************************************************************************/
/*!
 * \brief Set current pending block's result to OK.
 * \details -
 * \context TASK
 * \reentrant FALSE
 * \synchronous TRUE
 * \pre -
 */
FUNC(void, NVM_PRIVATE_CODE) NvM_ActSetReqOk(void);

/**********************************************************************************************************************
 * NvM_BlockNotification
 *********************************************************************************************************************/
/*! \brief Invokes single block job end and BSWM notifications, if there are any.
 *  \details Invokes single block job end and BSWM notifications, if there are any.
 *  \param[in] BlockId in range [1, (number of blocks - 1)].
 *  \param[in] ServiceId as a request type. Caller has to ensure validity.
 *  \param[in] JobResult as the current job result of the block with BlockId. Must be in range [0,8]. Caller has to ensure validity.
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
extern FUNC(void, NVM_PRIVATE_CODE) NvM_BlockNotification(NvM_BlockIdType BlockId, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult);

#define NVM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* NVM_ACT_H_ */

/**********************************************************************************************************************
 *  END OF FILE: NvM_Act.h
 *********************************************************************************************************************/
