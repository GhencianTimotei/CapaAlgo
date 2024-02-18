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
/*!        \file  NvM_JobProc.h
 *        \brief  NvM job processing submodule header file
 *      \details  This submodule implements the FSM for the NVM, including the state description table.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#if (!defined NVM_JOBPROC_H_)
#define NVM_JOBPROC_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "NvM_Cfg.h"
#include "NvM_PrivateCfg.h"
#include "NvM_IntTypes.h"

#include "NvM_Act.h"
#include "NvM_Crc.h"
#include "NvM_Qry.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* The maximum number of conditional exits a stat can have, the final ("else") exit is implicit. */
#define NVM_MAX_NUM_OF_STATE_CONDITIONS (3u)

/* The maximum number of Query functions that can be ANDed together to form a state exit condition. */
#define NVM_MAX_NUM_OF_QRY_AND (2u)

/* Maximum number of bytes that is required to hold all CRC data.
 * As NvM only supports up to CRC32.
 *
 * Note: This is only a constant to avoid magic numbers. Changing this constant will not lead to any changes regarding
 *       CRC handling but increases buffer reservation for some(!) cases.
 */
#define NVM_MAX_NUM_BYTES_CRC (4u)

/*
 * Constants for NV block state handling
 *
 * Note: The state information contains primary, secondary and current block's state.
 *       The current state information is placed in the least significant position (i.e. shift=0).
 */

/* Bit mask representing NV block state for redundant blocks */
#define NVM_NVBLOCK_STATE_BIT_MASK (0x3u)

/* Shift factor to address primary redundant block NV state */
#define NVM_PRI_NVBLOCK_STATE_SHIFT (0x5u)

/* Shift factor to address secondary redundant block NV state */
#define NVM_SEC_NVBLOCK_STATE_SHIFT (0x3u)

/* Flag to set/check the primary redundant block active flag */
#define NVM_NVBLOCK_STATE_PRI_ACTIVE   (0x7Fu)

/* Flag to set/check the secondary redundant block active flag */
#define NVM_NVBLOCK_STATE_SEC_ACTIVE   (0x80u)

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/* Extracts primary NvBlock state from NvState. */
/* PRQA S 3453 1 */ /* MD_MSR_FctLikeMacro */
#define NVM_EXTRACT_NVSTATE_PRIMARY(NvState) (((NvState) >> NVM_PRI_NVBLOCK_STATE_SHIFT) & NVM_NVBLOCK_STATE_BIT_MASK)

/* Extracts secondary NvBlock state from NvState. */
/* PRQA S 3453 1 */ /* MD_MSR_FctLikeMacro */
#define NVM_EXTRACT_NVSTATE_SECONDARY(NvState) (((NvState) >> NVM_SEC_NVBLOCK_STATE_SHIFT) & NVM_NVBLOCK_STATE_BIT_MASK)


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef struct
{
    NvM_BlockIdType             JobBlockId_t; /*!< NvM block ID. */
    NvM_InternalServiceIdType   JobServiceId_t; /*!< Requested job. */
    NvM_RamAddressType          RamAddr_t; /*!< Data pointer. */
} NvM_JobType; /*!< Type of a job that is to be queued. */

typedef P2VAR(NvM_JobType, AUTOMATIC, NVM_PRIVATE_DATA) NvM_JobPtrType;

typedef struct
{
    NvM_BlockDescrPtrType       Descriptor_pt; /*!< Pointer to the block descriptor. */
    NvM_RamMngmtPtrType         Mngmt_pt; /*!< Pointer to the RAM management. */
    NvM_RamAddressType          RamAddr_t; /*!< Pointer to data. */
    NvM_RamAddressType          NvRamAddr_t; /*!< Pointer to be forwarded to the NV RAM. */
    NvM_CrcJobType              BlockCrcJob_t; /*!< Pointer to CRC job. */
    uint16                      NvIdentifier_u16; /*!< Nv ID, which will be passed to underlying modules. */
    uint16                      ByteCount_u16; /*!< Used for block-wise copy - also if internal buffer is OFF! */
    NvM_RequestResultType       LastResult_t; /*!< Job result. */
    uint8                       WriteRetryCounter_u8; /*!< Write retry counter. */
    uint8                       InternalFlags_u8; /*!< Job flags. */
    uint8                       NvState_u8; /*!< Current state of the block. */
#if (NVM_USE_CSM == STD_ON)
    uint8                       CsmJobReturnValue_u8; /*!< Stores return value of a CSM job */
    uint8                       CsmJobRetryCounter_u8; /*!< CSM retry counter */
#endif /* (NVM_USE_CSM == STD_ON) */
} NvM_BlockInfoType; /*!< Job processing structure: contains all information related to the processing of one certain job. */

typedef P2VAR(NvM_BlockInfoType, AUTOMATIC, NVM_FAST_DATA) NvM_BlockInfoPtrType;

#if (NVM_REPAIR_REDUNDANT_BLOCKS_API == STD_ON)
typedef struct
{
    NvM_BlockIdType CurrentBlockId; /*!< Current block ID. */
    uint8 NvBlockState; /*!< Current job state. */
    uint32 CrcBuffer; /*!< CRC buffer to be able to compare two CRCs. */
} NvM_RepairBlockStateType; /*!< Structure used to store a RepairRedundantBlocks job. */
#endif

typedef enum
{
    /* Possible states of the task state machine */

    /* \trace DSGN-NvM22853 */
    NVM_STATE_UNINIT = 0u,
    /* \trace DSGN-NvM22979 */
    NVM_STATE_IDLE,
#if ((NVM_JOB_PRIORISATION == STD_ON) && (NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1))
    /* \trace DSGN-NvM22983 */
    NVM_STATE_HIGH_PRIO_JOB,
#endif
    /* \trace DSGN-NvM22981 */
    NVM_STATE_NORMAL_PRIO_JOB,
#if (NVM_KILL_WRITEALL_API == STD_ON)
    /* \trace DSGN-NvM22980 */
    NVM_STATE_MULTI_BLOCK_JOB,
#endif
    /* Possible states of the jobmain- and jobsub state machine */

    /* Read Block */

    /* \trace DSGN-NvM22815 */
    NVM_STATE_READ_READ_DATA,
    /* \trace DSGN-NvM24164 */
    NVM_STATE_READ_DATA_VALIDATION,
    /* \trace DSGN-NvM22816 */
    NVM_STATE_READ_CMP_CRC,
    NVM_STATE_READ_PRE_CHECK_LOSS_OF_REDUNDANCY,
    NVM_STATE_READ_CHECK_LOSS_OF_REDUNDANCY,
    /* \trace DSGN-NvM22818 */
    NVM_STATE_READ_IMPL_RECOV,
    /* \trace DSGN-NvM22819 */
    NVM_STATE_READ_LOAD_ROM,
    /* \trace DSGN-NvM24163 */
    NVM_STATE_READ_FINALIZE,

    /* Write Block */

    /* \trace DSGN-NvM24148 */
    NVM_STATE_WRITE_INITIAL,
    /* \trace DSGN-NvM24306 */
    NVM_STATE_WRITE_CRCCALC,
    /* \trace DSGN-NvM22806 */
    NVM_STATE_WRITE_CRCCOMPMECHANISM,
    /* \trace DSGN-NvM22807 */
    NVM_STATE_WRITE_TEST_PRI_READ,
    /* \trace DSGN-NvM22808 */
    NVM_STATE_WRITE_TEST_SEC_READ,
    /* \trace DSGN-NvM22809 */
    NVM_STATE_WRITE_WR_DATA_CRC_1,
    /* \trace DSGN-NvM22810 */
    NVM_STATE_WRITE_WR_DATA_CRC_2,

    /* RestoreBlockDefaults */

    /* \trace DSGN-NvM22825 */
    NVM_STATE_RESTORE_LOAD_ROM,

#if (NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3)
    /* Invalidate Nv Block */

    /* \trace DSGN-NvM22829 */
    NVM_STATE_INVALIDATING_BLOCK,

    /* Erase Nv Block */

    /* \trace DSGN-NvM22833 */
    NVM_STATE_ERASE_ERASE_BLOCK,
#endif

    /* Read All */

    /* \trace DSGN-NvM22840 */
    NVM_STATE_READALL_PROC_CONFIG_ID,
    /* \trace DSGN-NvM22841 */
    NVM_STATE_READALL_PROC_RAM_BLOCK,
    /* \trace DSGN-NvM22843 */
    NVM_STATE_READALL_CHK_SKIP,
    /* \trace DSGN-NvM24170 */
    NVM_STATE_READALL_KILLED,
    /* \trace DSGN-NvM22845 */
    NVM_STATE_READALL_WR_ONCE_PROT,
#if (NVM_SET_RAM_BLOCK_STATUS_API == STD_ON)
    /* \trace DSGN-NvM22842 */
    NVM_STATE_READALL_CHK_RAM_VALIDITY,
#endif
    /* \trace DSGN-NvM22846 */
    NVM_STATE_READALL_READ_NV,
    /* \trace DSGN-NvM24171 */
    NVM_STATE_READALL_LOAD_DEFAULTS,
    /* \trace DSGN-NvM24172 */
    NVM_STATE_READALL_READABILITY_CHECK,

    /* Write All */

    /* \trace DSGN-NvM22847 */
    NVM_STATE_WRITEALL_PROC_BLOCK,
    /* \trace DSGN-NvM22850 */
    NVM_STATE_WRITEALL_WRITE_FSM,
    /* \trace DSGN-NvM22848 */
    NVM_STATE_WRITEALL_WAIT_MEMHWA,

#if (NVM_REPAIR_REDUNDANT_BLOCKS_API == STD_ON)
    /* RepairRedundantBlocks */

    /* \trace DSGN-NvM23540 */
    NVM_STATE_REPAIRREDUNDANT_MAIN,
    /* \trace DSGN-NvM23542 */
    NVM_STATE_REPAIRREDUNDANT_CHECK_FIRST,
    /* \trace DSGN-NvM23543 */
    NVM_STATE_REPAIRREDUNDANT_CHECK_SECOND,
    /* \trace DSGN-NvM23544 */
    NVM_STATE_REPAIRREDUNDANT_VALIDATE_BLOCK,
    /* \trace DSGN-NvM23545 */
    NVM_STATE_REPAIRREDUNDANT_READ_VALID_BLOCK,
    /* \trace DSGN-NvM23546 */
    NVM_STATE_REPAIRREDUNDANT_WRITE_INVALID_BLOCK,
#endif
    /* \trace DSGN-NvM22817 */
    NVM_STATE_FSM_FINISHED
} NvM_StateIdType; /*!< All available/ possible states of all NvM state machines (task, job main, and the job sub state machine). */

typedef struct
{
    NvM_StateActionIdType    InitialActionId;
    NvM_StateIdType        InitialState_t;
    NvM_ServiceIdType      PublicFid_t;
} NvM_IntServiceDescrType; /*!< Descriptor, describing an internal service (asynchronous  NVM job). */

typedef struct
{
    NvM_StateActionIdType ExitHandler_t; /*!< Action ID. */
    NvM_StateActionIdType EntryHandler_t; /*!< Action ID. */
} NvM_StateChangeActionsType; /*!< Holds two action Ids (part of a state). */

typedef P2CONST(NvM_StateChangeActionsType, AUTOMATIC, NVM_PRIVATE_CONST) NvM_StateChangeActionsPtrType;

typedef struct
{
    NvM_StateQueryIdType         Queries_at[NVM_MAX_NUM_OF_QRY_AND]; /*!< Queries, which decide whether the actions shall be executed. */
    NvM_StateChangeActionsType Actions_t; /*!< Action IDs to execute. */
    NvM_StateIdType              NextState_t; /*!< Next state to execute. */
} NvM_StateChangeIfDescrType; /*!< Describe one State exit with its condition, its Actions and its following state. */

typedef struct
{
    NvM_StateChangeActionsType Actions_t; /*!< Action IDs to execute. */
    NvM_StateIdType              NextState_t; /*!< Next state to execute. */
} NvM_StateChangeElseDescrType; /*!< Describe the final state exit ("else") to be taken if no condition matched. */

typedef struct
{
    NvM_StateChangeIfDescrType   ChangeConditions_at[NVM_MAX_NUM_OF_STATE_CONDITIONS]; /*!<All conditions with queries. */
    NvM_StateChangeElseDescrType FinalCondition_t; /*!< Fallback condition without queries. */
} NvM_StateDescrType; /*!< Describe a state with it's possible change conditions. */

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
#define NVM_START_SEC_VAR_FAST_NO_INIT_8
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Note: At least for development mode (where the following two state types are enums)
 * the compiler is expected to ensure correct alignment, regardless of any given section alignment.
 * The state variables are used quite frequently (but never via pointers)
 */

/*! Holds current main state machine status */
extern VAR(NvM_StateIdType, NVM_FAST_DATA) NvM_JobMainState_t;

/*! Holds current sub state machine status */
extern VAR(NvM_StateIdType, NVM_FAST_DATA) NvM_JobSubState_t;

/*! External definition of variables that area used in the NvM submodules - they are defined in NvM.c. */
extern VAR(uint8, NVM_FAST_DATA) NvM_ApiFlags_u8;

#define NVM_STOP_SEC_VAR_FAST_NO_INIT_8
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define NVM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! State of the task state machine. */
extern VAR(NvM_StateIdType, NVM_PRIVATE_DATA) NvM_TaskState_t;

#define NVM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define NVM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Currently processed NvM job type */
extern VAR(NvM_JobType, NVM_PRIVATE_DATA) NvM_CurrentJob_t;

/*! Information to currently processed block */
extern VAR(NvM_BlockInfoType, NVM_PRIVATE_DATA) NvM_CurrentBlockInfo_t;

/*! Holds CRC information of a redundant block only. */
extern VAR(uint8, NVM_PRIVATE_DATA) NvM_SecondaryRedundantBlockCrcData[NVM_MAX_NUM_BYTES_CRC];

#if (NVM_REPAIR_REDUNDANT_BLOCKS_API == STD_ON)
/*! Information required for NvM_RepairRedundant block handling */
extern VAR(NvM_RepairBlockStateType, NVM_PRIVATE_DATA) NvM_RepairRedBlockState;
#endif

#define NVM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define NVM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Internal job descriptor table. */
extern CONST(NvM_IntServiceDescrType, NVM_PRIVATE_CONST) NvM_IntServiceDescrTable_at[(uint32)NVM_INT_FID_NO_JOB_PENDING + 1u];

#define NVM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define NVM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*! Array of RAM Block Management areas, defined to be usable in block descriptor table */
extern VAR(NvM_RamMngmtAreaType, NVM_CONFIG_DATA) NvM_BlockMngmtArea_at[NVM_TOTAL_NUM_OF_NVRAM_BLOCKS];

/*! Management area for DCM blocks */
extern VAR(NvM_RamMngmtAreaType, NVM_CONFIG_DATA) NvM_DcmBlockMngmt_t;

#define NVM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define NVM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 * NvM_JobProcInit
 *********************************************************************************************************************/
/*! \brief Initialize the module variables
 *  \details Initialize the module variables
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
extern FUNC(void, NVM_PRIVATE_CODE) NvM_JobProcInit(void);

/**********************************************************************************************************************
 * NvM_Fsm
 *********************************************************************************************************************/
/*! \brief Sets next state machine state to process depending on query results.
 *  \details This function executes exactly one State of a state machine: e.g. the initial state of the State Machine
 *           for ReadBlock. This initial state contains four exits. Which exit is taken depends on the queries
 *           which in turn lead to the actions. At last the next state is stored. The next time the function is called,
 *           it executes this next state. This function is called from NvM_Mainfunction() which is called cyclically
 *           by an Application (or event-driven when NVM is an ECC Task).
 *  \param[in] NvM_CurrentState_t as an index to the state table array. Must be in range
 *             [NVM_STATE_UNINIT, NVM_STATE_FSM_FINISHED]. Caller has to ensure validity.
 *  \return next state
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
extern FUNC(NvM_StateIdType, NVM_PRIVATE_CODE) NvM_Fsm(NvM_StateIdType NvM_CurrentState_t);

/**********************************************************************************************************************
 *  NvM_IsBooleanBitfieldTrue
 *********************************************************************************************************************/
/*!
 * \brief           Translates a given "boolean bitfield" into a native boolean type.
 * \details         Bit fields with length 1 are intrinsic booleans.
 *                  The MISRA QAC tool does not accept this and shows warnings. To solve the problem, this inline
 *                  function is used to check boolean expressions for such types.
 *
 *                  Note: This function is only allowed to be used for NvM_BitfieldType with length 1!
 * \param[in]       BooleanBitfield A bitfield with length "1" that is used for boolean expression.
 * \return          TRUE if bitfield is not equal to zero, FALSE otherwise.
 * \pre             -
 * \context         TASK
 * \reentrant       FALSE
 * \synchronous     TRUE
 */
extern FUNC(boolean, NVM_PRIVATE_CODE) NvM_IsBooleanBitfieldTrue(const NvM_BitFieldType BooleanBitfield);

#define NVM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* NVM_JOBPROC_H_ */

/**********************************************************************************************************************
 *  END OF FILE: NvM_JobProc.h
 *********************************************************************************************************************/
