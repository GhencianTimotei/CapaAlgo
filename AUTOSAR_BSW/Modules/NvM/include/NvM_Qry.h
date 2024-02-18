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
/*!        \file  NvM_Qry.h
 *        \brief  NvM query submodule header file
 *      \details  This submodule implements the queries to be executed to evaluate the conditions
 *                for a state transition.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#if (!defined NVM_QRY_H_)
#define NVM_QRY_H_

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

typedef enum
{
  NVM_QRY_ID_BLK_RELEVANT_FOR_WRITE_ALL = 0u,
  NVM_QRY_ID_CANCEL_WRITE_ALL,
#if(NVM_KILL_WRITEALL_API == STD_ON)
  NVM_QR_ID_WRITEALL_KILLED,
#endif
  NVM_QRY_ID_CRC_BUSY,
  NVM_QRY_ID_DATA_COPY_BUSY,
  NVM_QRY_ID_CRC_MATCH,

  NVM_QRY_ID_LAST_BLOCK_DONE_READALL,
  NVM_QRY_ID_LAST_BLOCK_DONE_WRITEALL,
  NVM_QRY_ID_LAST_RESULT_OK,
  NVM_QRY_ID_MAIN_FSM_RUNNING,
  NVM_QRY_ID_MULTI_BLK_JOB,
#if (NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1)
  NVM_QRY_ID_NORMAL_PRIO_JOB,
# if(NVM_JOB_PRIORISATION == STD_ON)
  NVM_QRY_ID_HI_PRIO_JOB,
# endif
#endif
  NVM_QRY_ID_NV_BUSY,
  NVM_QRY_ID_MEMHWA_BUSY,
#if(NVM_SET_RAM_BLOCK_STATUS_API == STD_ON)
  NVM_QRY_ID_CALC_RAM_BLOCK_CRC_ENABLED_AND_RAM_VALID,
#endif
  NVM_QRY_ID_PRIMARY_REDUNDANT_BLOCK,
  NVM_QRY_ID_SECONDARY_REDUNDANT_BLOCK,
  NVM_QRY_ID_SKIP_BLOCK,
  NVM_QRY_ID_SUB_FSM_RUNNING,
  NVM_QRY_ID_WRITE_BLOCK_ONCE,
  NVM_QRY_ID_WRITE_RETRIES_EXCEEDED,
  NVM_QRY_ID_HAS_ROM,
  NVM_QRY_ID_EXT_RUNTIME,
#if (NVM_REPAIR_REDUNDANT_BLOCKS_API == STD_ON)
  NVM_QRY_ID_SUSPEND_REPAIR_REDUNDANT_BLOCKS,
  NVM_QRY_ID_REPAIR_RED_BLOCK_DEFECT,
#endif
  NvM_QRY_CRC_COMP_MECHANISM_SKIPWRITE,
  NVM_QRY_POST_READ_TRANSFORM,
  NVM_QRY_READALL_KILLED,
  NVM_QRY_SYNCDECRYPT,
  NVM_QRY_SYNCENCRYPT,
  NVM_QRY_CSM_RETRIES_NECESSARY,
  NVM_QRY_ID_BLOCK_CHECK_LOSS_OF_REDUNDANCY,
  NVM_QRY_ID_FIRST_REDUNDANT_BLOCK_FAILED,
  NVM_QRY_ID_REDUNDANT_CRC_MATCHES,
  NVM_QRY_ID_TRUE
} NvM_StateQueryIdType; /*!< Enumeration of Query IDs. */

/*! Query table pointer type. */
typedef P2CONST(NvM_StateQueryIdType, AUTOMATIC, NVM_PRIVATE_CONST) NvM_StateQueryPtrType;
/*! Query function pointer type. */
typedef P2FUNC(boolean, NVM_PRIVATE_CODE, NvM_QryFctPtrType) (void);

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
#define NVM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! The query function table, indexed by NvM_StateQueryIdType. */
extern CONST(NvM_QryFctPtrType, NVM_PRIVATE_CONST) NvM_QueryTable_ap[(uint32)NVM_QRY_ID_TRUE + 1u];

#define NVM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define NVM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  NvM_QryReadAllKilled
 *********************************************************************************************************************/
/*!
 * \brief       Returns whether the KillReadAll is requested.
 * \details     -
 * \return      TRUE: KillReadAll requested; FALSE: KillReadAll not requested
 * \pre         -
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryReadAllKilled(void);

/**********************************************************************************************************************
 * NvM_QryIsInitCallbackConfigured
 *********************************************************************************************************************/
/*! \brief Check if any init callback is configured for the given block
 *  \details -
 *  \param[in] BlockDescriptor as a valid pointer to a block descriptor. Caller has to ensure validity of pointer.
 *  \return TRUE: There is an init callback configured; FALSE: No init callback configured.
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
extern FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryIsInitCallbackConfigured(NvM_BlockDescrPtrType BlockDescriptor);

#if (NVM_USE_CSM == STD_ON)
/**********************************************************************************************************************
 * NvM_QryIsCipherBlock
 *********************************************************************************************************************/
/*! \brief Returns whether the passed block descriptor references a CSM job or not.
 *  \details Reference to a CSM job means that the block must be encrypted and the result data provided to the user.
 *  \param[in] BlockDescriptor as a valid pointer to a block descriptor. Caller has to ensure validity of pointer.
 *  \return TRUE Block has a reference to a CSM job, FALSE otherwise
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre NVM_USE_CSM == STD_ON (at least one NvM block has a reference to the CSM module job.
 */
FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryIsCipherBlock(NvM_BlockDescrPtrType BlockDescriptor);
#endif

/**********************************************************************************************************************
 * NvM_QrySyncDecrypt
 *********************************************************************************************************************/
/*! \brief Decrypts data and returns the result of the decryption, or returns TRUE in case no decryption is
 *         required, data is ok.
 *  \details Decryption is only successful, in case the CSM returns E_OK and the result length matches
 *           configured user data length. NvM will then provide the decrypted data to the user.
 *  \return TRUE Data decrypted successfully or no decryption needed, FALSE decryption failed.
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
FUNC(boolean, NVM_PRIVATE_CODE) NvM_QrySyncDecrypt(void);

/**********************************************************************************************************************
 * NvM_QrySyncEncrypt
 *********************************************************************************************************************/
/*! \brief Encrypts data and returns the result of the encryption, or returns TRUE in case no encryption is
 *         required, data is ok and shall be forwarded to the NV RAM as it is.
 *  \details Encryption is only successful, in case the CSM returns E_OK and the result length matches
 *           configured NV RAM data length. NvM will then forward the encrypted data to NV RAM (underlying module).
 *  \return TRUE Data encrypted successfully or no encryption needed, FALSE encryption failed.
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
FUNC(boolean, NVM_PRIVATE_CODE) NvM_QrySyncEncrypt(void);

#if ((NVM_SET_RAM_BLOCK_STATUS_API == STD_ON) || (NVM_CRC_INT_BUFFER == STD_ON))
/**********************************************************************************************************************
 * NvM_QryCalcRamBlockCrcEnabledAndRamValid
 *********************************************************************************************************************/
/*! \brief Returns whether the current block has CalcRamBlockCrc enabled and its RAM is valid.
 *  \details -
 *  \return TRUE CalcRamBlockCrc is enabled and the RAM is valid, FALSE otherwise
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \config SetRamBlockStatus API or internal CRC buffers are enabled
 *  \pre -
 */
FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryCalcRamBlockCrcEnabledAndRamValid(void);
#endif /* ((NVM_SET_RAM_BLOCK_STATUS_API == STD_ON) || (NVM_CRC_INT_BUFFER == STD_ON)) */

#define NVM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* NVM_QRY_H_ */

/**********************************************************************************************************************
 *  END OF FILE: NvM_Qry.h
 *********************************************************************************************************************/
