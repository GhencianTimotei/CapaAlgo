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
/*!        \file  NvM.c
 *        \brief  NvM source file
 *      \details  The NVRAM Manager ensure the data storage and maintenance of NV data.
 *                The NVRAM Manager shall be able to administrate the NV data of an EEPROM
 *                and/or a FLASH EEPROM emulation device.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the VERSION CHECK below.
 *********************************************************************************************************************/

#define NVM_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
/* Standardized includes */
#include "NvM.h"
#include "NvM_Cbk.h"

/* Submodule includes */
#include "NvM_JobProc.h"
#include "NvM_Queue.h"

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
#if ((NVM_SW_MAJOR_VERSION != (8u)) \
        || (NVM_SW_MINOR_VERSION != (1u)))
# error "Version numbers of NvM.c and NvM.h are inconsistent!"
#endif

#if ((NVM_CFG_MAJOR_VERSION != (8u)) \
        || (NVM_CFG_MINOR_VERSION != (0u)))
# error "Version numbers of NvM.c and NvM_Cfg.h are inconsistent!"
#endif

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/
#ifndef NVM_LOCAL /* COV_NVM_COMPATIBILITY */
# define NVM_LOCAL static
#endif

#ifndef NVM_LOCAL_INLINE /* COV_NVM_COMPATIBILITY */
# define NVM_LOCAL_INLINE LOCAL_INLINE
#endif

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
#if (NVM_API_CONFIG_CLASS > NVM_API_CONFIG_CLASS_1)
typedef P2CONST(NvM_RamMngmtAreaType, AUTOMATIC, NVM_CONFIG_DATA) NvM_RamMngmtConstPtrType;
#endif /* (NVM_API_CONFIG_CLASS > NVM_API_CONFIG_CLASS_1) */

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/
#define NVM_START_SEC_VAR_FAST_NO_INIT_8
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

VAR(uint8, NVM_FAST_DATA) NvM_ApiFlags_u8; /*!< API flags - which are accessible from API. */

#define NVM_STOP_SEC_VAR_FAST_NO_INIT_8
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define NVM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if((NVM_SET_RAM_BLOCK_STATUS_API == STD_ON) && (NVM_CALC_RAM_CRC_USED == STD_ON))
/*! Holds the current asynchronous CRC job, processed by the MainFunction. */
NVM_LOCAL VAR(struct NvM_CrcJobStruct, NVM_PRIVATE_DATA) NvM_AsyncCrcJob_t;
#endif

#define NVM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define NVM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if (NVM_API_CONFIG_CLASS > NVM_API_CONFIG_CLASS_1)
/**********************************************************************************************************************
 * NvM_WriteProtectionChecks
 *********************************************************************************************************************/
/*! \brief Checks whether the block referenced via parameter is write protected or not.
 *  \details Checks whether the block referenced via parameter is write protected or not.
 *  \param[in] MngmtPtr as a pointer to the management information structure of a NvM block. Must not be NULL_PTR.
 *             Validity has to be ensured by called (used NvM internally).
 *  \return FALSE block is write protected
 *  \return TRUE otherwise
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \config API configuration class > 1
 *  \pre -
 */
NVM_LOCAL_INLINE FUNC(boolean, NVM_PRIVATE_CODE) NvM_WriteProtectionChecks(const NvM_RamMngmtConstPtrType MngmtPtr);
#endif

/**********************************************************************************************************************
 * NvM_CheckBlockType
 *********************************************************************************************************************/
/*! \brief Checks whether the Block Id references a Dataset NvM block.
 *  \details Checks whether the Block Id references a Dataset NvM block.
 *  \param[in] BlockId in range [1, (number of blocks - 1)].
 *  \return TRUE Block Id references a Dataset block
 *  \return FALSE otherwise
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL_INLINE FUNC(boolean, NVM_PRIVATE_CODE) NvM_CheckBlockType(const NvM_BlockIdType BlockId);

#if ((NVM_API_CONFIG_CLASS > NVM_API_CONFIG_CLASS_1) && (NVM_DEV_ERROR_DETECT == STD_ON))
/**********************************************************************************************************************
 * NvM_CheckAddress
 *********************************************************************************************************************/
/*! \brief Checks whether the given pointer is valid for given NvM Block Id.
 *  \details Checks whether the given pointer is valid for given NvM Block Id.
 *  \param[in] BlockId in range [1, (number of blocks - 1)].
 *  \param[in] RamPtr to be checked whether valid for the passed BlockId. May be NULL_PTR, depends on passed BlockId.
 *  \return TRUE pointer is valid for NvM block references via BlockId
 *  \return FALSE otherwise
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \config DET error detection and Param Pointer check are enabled
 *  \pre -
 */
NVM_LOCAL_INLINE FUNC(boolean, NVM_PRIVATE_CODE) NvM_CheckAddress(const NvM_BlockIdType BlockId, const void * RamPtr);
#endif /* ((NVM_API_CONFIG_CLASS > NVM_API_CONFIG_CLASS_1) && (NVM_DEV_ERROR_DETECT == STD_ON)) */

# if ((NVM_DEV_ERROR_DETECT == STD_ON) || (NVM_KILL_WRITEALL_API == STD_ON))
/**********************************************************************************************************************
 * NvM_CheckBlockId
 *********************************************************************************************************************/
/*! \brief Checks whether the Block Id is a valid NvM Block Id.
 *  \details Checks whether the Block Id is a valid NvM Block Id.
 *  \param[in] BlockId to be checked for validity. May exceed the number of configured blocks.
 *  \return TRUE Block Id is valid
 *  \return FALSE otherwise
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \config DET error detection and Param Block Id check are enabled
 *  \pre -
 */
NVM_LOCAL_INLINE FUNC(boolean, NVM_PRIVATE_CODE) NvM_CheckBlockId(const NvM_BlockIdType BlockId);
# endif /* ((NVM_DEV_ERROR_DETECT == STD_ON) || (NVM_KILL_WRITEALL_API == STD_ON)) */

#if(NVM_DEV_ERROR_DETECT == STD_ON)
/**********************************************************************************************************************
 * NvM_CheckCurrDataIndex
 *********************************************************************************************************************/
/*! \brief Checks the current Dataindex for given Block Id to be valid for the block.
 *  \details Checks the current Dataindex for given Block Id to be valid for the block.
 *  \param[in] BlockId in range [1, (number of blocks - 1)].
 *  \return TRUE current Dataindex is valid
 *  \return FALSE otherwise
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \config DET error detection and Param Dataindex check are enabled
 *  \pre -
 */
NVM_LOCAL_INLINE FUNC(boolean, NVM_PRIVATE_CODE) NvM_CheckCurrDataIndex(const NvM_BlockIdType BlockId);

/**********************************************************************************************************************
 * NvM_CheckDataIndex
 *********************************************************************************************************************/
/*! \brief Checks the given Dataindex to be valid for given Block Id.
 *  \details Checks the given Dataindex to be valid for given Block Id.
 *  \param[in] BlockId in range [1, (number of blocks - 1)].
 *  \param[in] DataIndex to be checked for validity. May exceed the number of configured dataset.
 *  \return TRUE Dataindex is valid
 *  \return FALSE otherwise
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \config DET error detection and Param Dataindex check are enabled
 *  \pre -
 */
NVM_LOCAL_INLINE FUNC(boolean, NVM_PRIVATE_CODE) NvM_CheckDataIndex(const NvM_BlockIdType BlockId, const uint8 DataIndex);

/**********************************************************************************************************************
 * NvM_CheckNotNull
 *********************************************************************************************************************/
/*! \brief Checks whether the given pointer is null or not.
 *  \details Checks whether the given pointer is null or not.
 *  \param[in] Ptr to be checked != NULL_PTR. May be NULL_PTR.
 *  \return TRUE pointer is not null
 *  \return FALSE otherwise
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \config DET error detection and Param Pointer check are enabled
 *  \pre -
 */
NVM_LOCAL_INLINE FUNC(boolean, NVM_PRIVATE_CODE) NvM_CheckNotNull(const uint8 * Ptr);

/**********************************************************************************************************************
 * NvM_CheckInitialized
 *********************************************************************************************************************/
/*! \brief Checks whether the NvM is initialized or not.
 *  \details Checks whether the NvM is initialized or not.
 *  \return TRUE NvM is initialized
 *  \return FALSE otherwise
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \config DET error detection and Status uninitialized check are enabled
 *  \pre -
 */
NVM_LOCAL_INLINE FUNC(boolean, NVM_PRIVATE_CODE) NvM_CheckInitialized(void);

/**********************************************************************************************************************
 * NvM_CheckMultiBlockPending
 *********************************************************************************************************************/
/*! \brief Checks whether the NvM Multi Block is pending.
 *  \details Checks whether the NvM Multi Block is pending.
 *  \return TRUE NvM Multi Block is pending
 *  \return FALSE otherwise
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \config DET error detection and Block Pending check are enabled
 *  \pre -
 */
NVM_LOCAL_INLINE FUNC(boolean, NVM_PRIVATE_CODE) NvM_CheckMultiBlockPending(void);
#endif /* (NVM_DEV_ERROR_DETECT == STD_ON) */

/**********************************************************************************************************************
 * NvM_CheckBlockPending
 *********************************************************************************************************************/
/*! \brief Checks whether the NvM Block is pending.
 *  \details Checks whether the NvM Block is pending.
 *  \param[in] BlockId in range [1, (number of blocks - 1)].
 *  \return TRUE referenced NvM Block is pending
 *  \return FALSE otherwise
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \config DET error detection and Block Pending check are enabled
 *  \pre -
 */
NVM_LOCAL_INLINE FUNC(boolean, NVM_PRIVATE_CODE) NvM_CheckBlockPending(const NvM_BlockIdType BlockId);

/**********************************************************************************************************************
 * NvM_GetMngmtAreaPtr
 *********************************************************************************************************************/
/*! \brief Returns the pointer to management area.
 *  \details The returned management area pointer depends on given Block Id - is it a DCM or normal NvM Block Id?
 *           The given Block Id has to be valid - the function does not check the given parameter!
 *  \param[in] BlockId in range [1, (number of blocks - 1)].
 *  \return pointer to NvM Block's management area, if given Block Id is a NvM Block Id
 *  \return pointer to the DCM Block management area, if the given Block Id is a DCM Block Id
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL_INLINE FUNC(NvM_RamMngmtPtrType, NVM_PRIVATE_CODE) NvM_GetMngmtAreaPtr(const NvM_BlockIdType BlockId);

#if ((NVM_SET_RAM_BLOCK_STATUS_API == STD_ON) && (NVM_CALC_RAM_CRC_USED == STD_ON))
/**********************************************************************************************************************
 *  NvM_ProcessBackgroundCrcJobs
 *********************************************************************************************************************/
/*!
 * \brief           Process asynchronous background CRC calculations
 * \details         API invocation of NvM_SetRamBlockStatus(blockID, TRUE) leads to the need of a background CRC
 *                  recalculation in background.
 *                  This function processes the queue.
 *                  If queue is empty a dummy job is set up that omits processing to not waste main function processing
 *                  time.
 * \pre             -
 * \context         TASK
 * \reentrant       FALSE
 * \synchronous     TRUE
 * \config          NVM_SET_RAM_BLOCK_STATUS_API == STD_ON && NVM_CALC_RAM_CRC_USED == STD_ON
 *
 */
NVM_LOCAL_INLINE FUNC(void, NVM_PRIVATE_CODE) NvM_ProcessBackgroundCrcJobs(void);
#endif

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
*  NvM_Init
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, NVM_PUBLIC_CODE) NvM_Init(void)
{
    uint16_least NvM_BlockCount_u16loc;
    /* #10 Initialize queue (only if API class > 1). */
#if (NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS)
    NvM_QueueInit();
#endif
    /* #20 Initialize Crc queue (only if SetRamBlockStatusApi and CalcRamBlockCrc enabled). */
#if((NVM_SET_RAM_BLOCK_STATUS_API == STD_ON) && (NVM_CALC_RAM_CRC_USED == STD_ON))
    NvM_CrcQueueInit();
    /* Initialize crc Job with "dummy job" -> CRC for Block 0. It will never be executed, due to its Block Descriptor values. */
    NvM_CrcJob_Create(&NvM_AsyncCrcJob_t, (NvM_BlockIdType)0, NULL_PTR, (uint16)0); /* SBSW_NvM_FuncCall_PtrParam_CrcAsyncJob */
#endif
    /* #30 Reset internal variables. */
    /* No mutli block requested and the multi block result is OK. */
    NvM_ApiFlags_u8 = 0u;
    NvM_BlockMngmtArea_at[0u].NvRamErrorStatus_u8 = NVM_REQ_OK; /* SBSW_NvM_AccessBlockManagementArea */

    /* Set all data indices to zero. */
    NvM_BlockCount_u16loc = NvM_NoOfBlockIds_t;
    do
    {
        --NvM_BlockCount_u16loc;
        NvM_BlockMngmtArea_at[NvM_BlockCount_u16loc].NvDataIndex_t = 0u; /* SBSW_NvM_AccessBlockManagementArea */
    } while(NvM_BlockCount_u16loc > 0u);

    /* Initialize DCM block Mngmt area. */
    NvM_DcmBlockMngmt_t.NvDataIndex_t = 0u;
    NvM_DcmBlockMngmt_t.NvRamAttributes_u8 = 0u;
    NvM_DcmBlockMngmt_t.NvRamErrorStatus_u8 = 0u;

    NvM_JobProcInit();
}

/**********************************************************************************************************************
*  NvM_SetDataIndex
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
FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_SetDataIndex(NvM_BlockIdType BlockId, uint8 DataIndex)
{
    Std_ReturnType returnValue = E_NOT_OK;
    uint8 detErrorId = NVM_E_NO_ERROR;

#if (NVM_DEV_ERROR_DETECT == STD_ON) /* ECO_IGNORE_LINE */
    if (NvM_CheckInitialized() == FALSE)
    {
        detErrorId = NVM_E_NOT_INITIALIZED;
    }
    else if(NvM_CheckBlockId(BlockId) == FALSE)
    {
        detErrorId = NVM_E_PARAM_BLOCK_ID;
    }
    else if(NvM_CheckBlockPending(BlockId) == TRUE)
    {
        detErrorId = NVM_E_BLOCK_PENDING;
    }
    else if (NvM_CheckDataIndex(BlockId, DataIndex) == FALSE)
    {
        detErrorId = NVM_E_PARAM_BLOCK_DATA_IDX;
    }
    else
#endif /* ECO_IGNORE_LINE */
    {
        if(NvM_CheckBlockType(BlockId) == TRUE)
        {
            const NvM_RamMngmtPtrType NvM_RamMngt_ptloc = NvM_GetMngmtAreaPtr(BlockId);

            /* #21 set data index to given one */
            NvM_RamMngt_ptloc->NvDataIndex_t = DataIndex; /* SBSW_NvM_AccessBlockManagementArea */
            /* #22 set return value to successful */
            returnValue = E_OK;
        }
        else
        {
#if (NVM_DEV_ERROR_REPORT == STD_ON) /* ECO_IGNORE_LINE */
            detErrorId = NVM_E_PARAM_BLOCK_TYPE;
#endif /* ECO_IGNORE_LINE */
        }
    }

#if (NVM_DEV_ERROR_REPORT == STD_ON)
    if(detErrorId != NVM_E_NO_ERROR)
    {
        NvM_Errorhook(NVM_SET_DATA_INDEX, detErrorId);
    }
#else
    NVM_DUMMY_STATEMENT(detErrorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
#endif

    return returnValue;
} /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL */

/**********************************************************************************************************************
*  NvM_GetDataIndex
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
FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_GetDataIndex(NvM_BlockIdType BlockId, P2VAR(uint8, AUTOMATIC, NVM_APPL_DATA) DataIndexPtr)
{
    Std_ReturnType returnValue = E_NOT_OK;
    uint8 detErrorId = NVM_E_NO_ERROR;

#if (NVM_DEV_ERROR_DETECT == STD_ON) /* ECO_IGNORE_LINE */
    /* check pointer first - for all other errors the pointed value shall be set to 0 */
    if(NvM_CheckNotNull(DataIndexPtr) == FALSE) /* SBSW_NvM_FuncCall_PtrParam_ParamChecker */
    {
        detErrorId = NVM_E_PARAM_DATA;
    }
    else if(NvM_CheckInitialized() == FALSE)
    {
        *DataIndexPtr = 0u; /* SBSW_NvM_PtrAccess_PublicAPI */

        detErrorId = NVM_E_NOT_INITIALIZED;
    }
    else if(NvM_CheckBlockId(BlockId) == FALSE)
    {
        *DataIndexPtr = 0u; /* SBSW_NvM_PtrAccess_PublicAPI */

        detErrorId = NVM_E_PARAM_BLOCK_ID;
    }
    else
#endif /* ECO_IGNORE_LINE */
    {
        if(NvM_CheckBlockType(BlockId) == TRUE)
        {
            NvM_RamMngmtConstPtrToConstType ramMngmtPtr = NvM_GetMngmtAreaPtr(BlockId);

            *DataIndexPtr = ramMngmtPtr->NvDataIndex_t; /* SBSW_NvM_PtrAccess_PublicAPI */

            returnValue = E_OK;
        }
        else
        {
            *DataIndexPtr = 0u; /* SBSW_NvM_PtrAccess_PublicAPI */

#if (NVM_DEV_ERROR_REPORT == STD_ON) /* ECO_IGNORE_LINE */
            detErrorId = NVM_E_PARAM_BLOCK_TYPE;
#endif /* ECO_IGNORE_LINE */
        }
    }

#if (NVM_DEV_ERROR_REPORT == STD_ON)
    if(detErrorId != NVM_E_NO_ERROR)
    {
        NvM_Errorhook(NVM_GET_DATA_INDEX, detErrorId);
    }
#else
    NVM_DUMMY_STATEMENT(detErrorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
#endif

    return returnValue;
}

#if (NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3)
/**********************************************************************************************************************
*  NvM_SetBlockProtection
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
FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_SetBlockProtection(NvM_BlockIdType BlockId, boolean ProtectionEnabled)
{
  Std_ReturnType returnValue = E_NOT_OK;
  uint8 detErrorId = NVM_E_NO_ERROR;

# if (NVM_DEV_ERROR_DETECT == STD_ON) /* ECO_IGNORE_LINE */
  if(NvM_CheckInitialized() == FALSE)
  {
    detErrorId = NVM_E_NOT_INITIALIZED;
  }
  else if (NvM_CheckBlockId(BlockId) == FALSE)
  {
    detErrorId = NVM_E_PARAM_BLOCK_ID;
  }
  else if (NvM_CheckCurrDataIndex(BlockId) == FALSE)
  {
    detErrorId = NVM_E_PARAM_BLOCK_DATA_IDX;
  }
  else if(NvM_CheckBlockPending(BlockId) == TRUE)
  {
    detErrorId = NVM_E_BLOCK_PENDING;
  }
  else
# endif /* ECO_IGNORE_LINE */
{
    const NvM_RamMngmtPtrType NvM_RamMngmt_ptloc = NvM_GetMngmtAreaPtr(BlockId);

    /* always check block not to be write once!
     * In case the Development error detecting or reporting is disabled, no error will be reported but the write protection wont be set */
    if (NvM_IsBooleanBitfieldTrue(
        NvM_BlockDescriptorTable_at[NVM_BLOCK_FROM_DCM_ID(BlockId)].Flags.BlockWriteBlockOnceEnabled) == FALSE)
    {
      NvM_EnterCriticalSection();

      if (ProtectionEnabled)
      {
        NvM_RamMngmt_ptloc->NvRamAttributes_u8 |= NVM_WR_PROT_SET; /* SBSW_NvM_AccessBlockManagementArea */
      }
      else
      {
        NvM_RamMngmt_ptloc->NvRamAttributes_u8 &= NVM_WR_PROT_CL; /* SBSW_NvM_AccessBlockManagementArea */
      }

      NvM_ExitCriticalSection();

      returnValue = E_OK;
    }
    else
    {
# if (NVM_DEV_ERROR_REPORT == STD_ON) /* ECO_IGNORE_LINE */
      detErrorId = NVM_E_BLOCK_CONFIG;
# endif /* ECO_IGNORE_LINE */
    }
}

# if (NVM_DEV_ERROR_REPORT == STD_ON)
  if(detErrorId != NVM_E_NO_ERROR)
  {
    NvM_Errorhook(NVM_SET_BLOCK_PROTECTION, detErrorId);
  }
# else
  NVM_DUMMY_STATEMENT(detErrorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
# endif

  return returnValue;
} /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif /* (NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3) */

/**********************************************************************************************************************
*  NvM_GetErrorStatus
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
FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_GetErrorStatus(NvM_BlockIdType BlockId,
    P2VAR(NvM_RequestResultType, AUTOMATIC, NVM_APPL_DATA) RequestResultPtr)
{
    Std_ReturnType returnValue = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
    uint8 detErrorId = NVM_E_NO_ERROR;

#if(NVM_DEV_ERROR_DETECT == STD_ON) /* ECO_IGNORE_LINE */
    if (NvM_CheckInitialized() == FALSE)
    {
        detErrorId = NVM_E_NOT_INITIALIZED;
    }
    /* we do not use the Det-function! GetErrorStatus is allowed for the multi block Id (0x0) */
    else if (NVM_BLOCK_FROM_DCM_ID(BlockId) >= NvM_NoOfBlockIds_t)
    {
        detErrorId = NVM_E_PARAM_BLOCK_ID;
    }
    else if (NvM_CheckNotNull(RequestResultPtr) == FALSE) /* SBSW_NvM_FuncCall_PtrParam_ParamChecker */
    {
        detErrorId = NVM_E_PARAM_DATA;
    }
    else
#endif /* ECO_IGNORE_LINE */
    {
        if(NvM_CheckBlockPending(BlockId) == TRUE)
        {
            *RequestResultPtr = NVM_REQ_PENDING; /* SBSW_NvM_PtrAccess_PublicAPI */
        }
        else
        {
            NvM_RamMngmtConstPtrToConstType ramMngmtPtr = NvM_GetMngmtAreaPtr(BlockId);

            /* get the ErrorStatus */
            *RequestResultPtr = ramMngmtPtr->NvRamErrorStatus_u8; /* SBSW_NvM_PtrAccess_PublicAPI */
        }

        returnValue = E_OK;
    }

#if (NVM_DEV_ERROR_REPORT == STD_ON)
    if(detErrorId != NVM_E_NO_ERROR)
    {
        NvM_Errorhook(NVM_GET_ERROR_STATUS, detErrorId);
    }
#else
    NVM_DUMMY_STATEMENT(detErrorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
#endif

    return returnValue;
}

#if (NVM_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
*  NvM_GetVersionInfo
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
FUNC(void, NVM_PUBLIC_CODE) NvM_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, NVM_APPL_DATA) Versioninfo)
{
    uint8 detErrorId = NVM_E_NO_ERROR;

# if (NVM_DEV_ERROR_DETECT == STD_ON) /* ECO_IGNORE_LINE */
    if (Versioninfo == NULL_PTR)
    {
        detErrorId = NVM_E_PARAM_DATA;
    }
    else
# endif /* ECO_IGNORE_LINE */
    {
        Versioninfo->vendorID         = NVM_VENDOR_ID; /* SBSW_NvM_PtrAccess_PublicAPI */
        Versioninfo->moduleID         = NVM_MODULE_ID; /* SBSW_NvM_PtrAccess_PublicAPI */
        Versioninfo->sw_major_version = NVM_SW_MAJOR_VERSION; /* SBSW_NvM_PtrAccess_PublicAPI */
        Versioninfo->sw_minor_version = NVM_SW_MINOR_VERSION; /* SBSW_NvM_PtrAccess_PublicAPI */
        Versioninfo->sw_patch_version = NVM_SW_PATCH_VERSION; /* SBSW_NvM_PtrAccess_PublicAPI */
    }

# if(NVM_DEV_ERROR_REPORT == STD_ON)
    if(detErrorId != NVM_E_NO_ERROR)
    {
        NvM_Errorhook(NVM_GET_VERSION_INFO, detErrorId);
    }
# else
    NVM_DUMMY_STATEMENT(detErrorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
# endif
}
#endif /* (NVM_VERSION_INFO_API == STD_ON) */

#if (NVM_SET_RAM_BLOCK_STATUS_API == STD_ON)
/**********************************************************************************************************************
*  NvM_SetRamBlockStatus
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
FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_SetRamBlockStatus(NvM_BlockIdType BlockId, boolean BlockChanged)
{
  Std_ReturnType returnValue = E_NOT_OK;
  uint8 detErrorId = NVM_E_NO_ERROR;

# if (NVM_DEV_ERROR_DETECT == STD_ON) /* ECO_IGNORE_LINE */
  /* #100 Precondition checks. */
  if(NvM_CheckInitialized() == FALSE)
  {
    detErrorId = NVM_E_NOT_INITIALIZED;
  }
  else if (NvM_CheckBlockId(BlockId) == FALSE)
  {
    detErrorId = NVM_E_PARAM_BLOCK_ID;
  }
  else if (NvM_CheckCurrDataIndex(BlockId) == FALSE)
  {
    detErrorId = NVM_E_PARAM_BLOCK_DATA_IDX;
  }
  else if(NvM_CheckBlockPending(BlockId) == TRUE)
  {
    detErrorId = NVM_E_BLOCK_PENDING;
  }
  else
# endif /* ECO_IGNORE_LINE */
  {
    const NvM_BlockDescriptorFlagsType* blockDescriptorFlags =
        &(NvM_BlockDescriptorTable_at[NVM_BLOCK_FROM_DCM_ID(BlockId)].Flags);

    if (NvM_IsBooleanBitfieldTrue(blockDescriptorFlags->BlockUseSetRamBlockStatusEnabled))
    {
      /* #200 All preconditions passed (set the RAM block status and return successfully). */

      const NvM_RamMngmtPtrType blockMngmtPtr = NvM_GetMngmtAreaPtr(BlockId);

      NvM_EnterCriticalSection();
      if (BlockChanged)
      {
        blockMngmtPtr->NvRamAttributes_u8 |= (NVM_STATE_CHANGED_SET | NVM_STATE_VALID_SET); /* SBSW_NvM_AccessBlockManagementArea */
      }
      else
      {
        blockMngmtPtr->NvRamAttributes_u8 &= (NVM_STATE_CHANGED_CL & NVM_STATE_VALID_CL); /* SBSW_NvM_AccessBlockManagementArea */
      }
      NvM_ExitCriticalSection();

# if (NVM_CALC_RAM_CRC_USED == STD_ON)
        if (NvM_IsBooleanBitfieldTrue(blockDescriptorFlags->CalcRamBlockCrcEnabled) && BlockChanged)
        {
          NvM_CrcQueueJob(NVM_BLOCK_FROM_DCM_ID(BlockId));
        }
# endif

      returnValue = E_OK;
    }
    else
    {
# if (NVM_DEV_ERROR_REPORT == STD_ON)
      /* #150 Precondition: block is allowed to use SetRamBlockStatus   (or error PARAM_BLOCK_TYPE). */
      /* Note: nested in here because the check itself is not really a DET case and MUST be available even if DET checks
       *       are disabled. It simply shall be reported via DET to ease finding problems regarding SetRamBlockStatus
       *       for the customer.
       */
      detErrorId = NVM_E_PARAM_BLOCK_TYPE;
#  endif
    }
  }

# if (NVM_DEV_ERROR_REPORT == STD_ON)
  if(detErrorId != NVM_E_NO_ERROR)
  {
    NvM_Errorhook(NVM_SET_RAM_BLOCK_STATUS, detErrorId);
  }
# else
  NVM_DUMMY_STATEMENT(detErrorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
# endif

  return returnValue;
} /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif /* (NVM_SET_RAM_BLOCK_STATUS_API == STD_ON) */

#if (NVM_API_CONFIG_CLASS > NVM_API_CONFIG_CLASS_1)
/**********************************************************************************************************************
*  NvM_ReadBlock
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
FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_ReadBlock(NvM_BlockIdType BlockId, P2VAR(void, AUTOMATIC, NVM_APPL_DATA) NvM_DstPtr)
{
    Std_ReturnType returnValue = E_NOT_OK;
    uint8 detErrorId = NVM_E_NO_ERROR;

# if (NVM_DEV_ERROR_DETECT == STD_ON) /* ECO_IGNORE_LINE */
    if(NvM_CheckInitialized() == FALSE)
    {
        detErrorId = NVM_E_NOT_INITIALIZED;
    }
    else if (NvM_CheckBlockId(BlockId) == FALSE)
    {
        detErrorId = NVM_E_PARAM_BLOCK_ID;
    }
    else if (NvM_CheckCurrDataIndex(BlockId) == FALSE)
    {
        detErrorId = NVM_E_PARAM_BLOCK_DATA_IDX;
    }
    else if (NvM_CheckAddress(BlockId, NvM_DstPtr) == FALSE) /* SBSW_NvM_FuncCall_PtrParam_ParamChecker */
    {
        detErrorId = NVM_E_PARAM_ADDRESS;
    }
    else if(NvM_CheckBlockPending(BlockId) == TRUE)
    {
        detErrorId = NVM_E_BLOCK_PENDING;
    }
    else
# endif /* ECO_IGNORE_LINE */
    {
        /* PRQA S 0316 1 */ /* MD_NvM_11.5_CastVoidPtrToObjPtr */
        if (NvM_QueueJob(BlockId, NVM_INT_FID_READ_BLOCK, (NvM_RamAddressType)NvM_DstPtr)) /* SBSW_NvM_FuncCall_PtrParam_QueueJob */
        {
            if(NvM_DstPtr == NULL_PTR)
            {
                const NvM_RamMngmtPtrType NvM_RamMngmt_ptloc = NvM_GetMngmtAreaPtr(BlockId);

                NvM_EnterCriticalSection();

                NvM_RamMngmt_ptloc->NvRamAttributes_u8 &= (NVM_STATE_VALID_CL & NVM_STATE_CHANGED_CL); /* SBSW_NvM_AccessBlockManagementArea */

                NvM_ExitCriticalSection();
            }

            returnValue = E_OK;
        }
    }

# if (NVM_DEV_ERROR_REPORT == STD_ON)
    if(detErrorId != NVM_E_NO_ERROR)
    {
        NvM_Errorhook(NVM_READ_BLOCK, detErrorId);
    }
# else
    NVM_DUMMY_STATEMENT(detErrorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
# endif

    return returnValue;
} /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */

/**********************************************************************************************************************
*  NvM_WriteBlock
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
FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_WriteBlock(NvM_BlockIdType BlockId, P2CONST(void, AUTOMATIC, NVM_APPL_DATA) NvM_SrcPtr)
{
    Std_ReturnType returnValue = E_NOT_OK;
    uint8 detErrorId = NVM_E_NO_ERROR;

# if(NVM_DEV_ERROR_DETECT == STD_ON) /* ECO_IGNORE_LINE */
    if(NvM_CheckInitialized() == FALSE)
    {
        detErrorId = NVM_E_NOT_INITIALIZED;
    }
    else if (NvM_CheckBlockId(BlockId) == FALSE)
    {
        detErrorId = NVM_E_PARAM_BLOCK_ID;
    }
    else if (NvM_CheckCurrDataIndex(BlockId) == FALSE)
    {
        detErrorId = NVM_E_PARAM_BLOCK_DATA_IDX;
    }
    else if (NvM_CheckAddress(BlockId, NvM_SrcPtr) == FALSE) /* SBSW_NvM_FuncCall_PtrParam_ParamChecker */
    {
        detErrorId = NVM_E_PARAM_ADDRESS;
    }
    else if(NvM_CheckBlockPending(BlockId) == TRUE)
    {
        detErrorId = NVM_E_BLOCK_PENDING;
    }
    else
# endif /* ECO_IGNORE_LINE */
    {
        const NvM_RamMngmtPtrType NvM_RamMngmt_ptloc = NvM_GetMngmtAreaPtr(BlockId);

        if(NvM_WriteProtectionChecks(NvM_RamMngmt_ptloc) == TRUE) /* SBSW_NvM_FuncCall_PtrParam_BlockMngmtArea */
        {
            /* PRQA S 0311, 0316 1 */ /* MD_NvM_11.5_CastLossOfConst, MD_NvM_11.5_CastVoidPtrToObjPtr */
            if (NvM_QueueJob(BlockId, NVM_INT_FID_WRITE_BLOCK, (NvM_RamAddressType)NvM_SrcPtr)) /* SBSW_NvM_FuncCall_PtrParam_QueueJob */
            {
                if(NvM_SrcPtr == NULL_PTR)
                {
                    NvM_EnterCriticalSection();

                    NvM_RamMngmt_ptloc->NvRamAttributes_u8 |= (NVM_STATE_VALID_SET | NVM_STATE_CHANGED_SET); /* SBSW_NvM_AccessBlockManagementArea */

                    NvM_ExitCriticalSection();
                }

                returnValue = E_OK;
            }
        }
    }

# if (NVM_DEV_ERROR_REPORT == STD_ON)
    if(detErrorId != NVM_E_NO_ERROR)
    {
        NvM_Errorhook(NVM_WRITE_BLOCK, detErrorId);
    }
# else
    NVM_DUMMY_STATEMENT(detErrorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
# endif

    return returnValue;
} /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */

/**********************************************************************************************************************
*  NvM_RestoreBlockDefaults
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
FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_RestoreBlockDefaults(NvM_BlockIdType BlockId, P2VAR(void, AUTOMATIC, NVM_APPL_DATA) NvM_DstPtr)
{
    Std_ReturnType returnValue = E_NOT_OK;
    uint8 detErrorId = NVM_E_NO_ERROR;

# if(NVM_DEV_ERROR_DETECT == STD_ON) /* ECO_IGNORE_LINE */
    if(NvM_CheckInitialized() == FALSE)
    {
        detErrorId = NVM_E_NOT_INITIALIZED;
    }
    else if (NvM_CheckBlockId(BlockId) == FALSE)
    {
        detErrorId = NVM_E_PARAM_BLOCK_ID;
    }
    else if (NvM_CheckCurrDataIndex(BlockId) == FALSE)
    {
        detErrorId = NVM_E_PARAM_BLOCK_DATA_IDX;
    }
    else if (NvM_CheckAddress(BlockId, NvM_DstPtr) == FALSE) /* SBSW_NvM_FuncCall_PtrParam_ParamChecker */
    {
        detErrorId = NVM_E_PARAM_ADDRESS;
    }
    else if ((NvM_BlockDescriptorTable_at[NVM_BLOCK_FROM_DCM_ID(BlockId)].RomBlockDataAddr_pt == NULL_PTR) &&
        (NvM_QryIsInitCallbackConfigured(&NvM_BlockDescriptorTable_at[NVM_BLOCK_FROM_DCM_ID(BlockId)]) == FALSE)) /* PRQA S 3415 */ /* MD_NvM_13.5 */ /* SBSW_NvM_FuncCall_PtrParam_ParamChecker */
    {
        detErrorId = NVM_E_BLOCK_CONFIG;
    }
    else if(NvM_CheckBlockPending(BlockId) == TRUE)
    {
        detErrorId = NVM_E_BLOCK_PENDING;
    }
    else
# endif /* ECO_IGNORE_LINE */
    {
        /* PRQA S 0316 1 */ /* MD_NvM_11.5_CastVoidPtrToObjPtr */
        if (NvM_QueueJob(BlockId, NVM_INT_FID_RESTORE_DEFAULTS, (NvM_RamAddressType)NvM_DstPtr)) /* SBSW_NvM_FuncCall_PtrParam_QueueJob */
        {
            if(NvM_DstPtr == NULL_PTR)
            {
                const NvM_RamMngmtPtrType NvM_RamMngmt_ptloc = NvM_GetMngmtAreaPtr(BlockId);

                NvM_EnterCriticalSection();

                NvM_RamMngmt_ptloc->NvRamAttributes_u8 &= (NVM_STATE_VALID_CL & NVM_STATE_CHANGED_CL);  /* SBSW_NvM_AccessBlockManagementArea */

                NvM_ExitCriticalSection();
            }

            returnValue = E_OK;
        }
    }

# if (NVM_DEV_ERROR_REPORT == STD_ON)
    if(detErrorId != NVM_E_NO_ERROR)
    {
        NvM_Errorhook(NVM_RESTORE_BLOCK_DEFAULTS, detErrorId);
    }
# else
    NVM_DUMMY_STATEMENT(detErrorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
# endif

    return returnValue;
} /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif /* (NVM_API_CONFIG_CLASS > NVM_API_CONFIG_CLASS_1) */

#if (NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3)
/**********************************************************************************************************************
*  NvM_EraseNvBlock
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
FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_EraseNvBlock(NvM_BlockIdType BlockId)
{
    Std_ReturnType returnValue = E_NOT_OK;
    uint8 detErrorId = NVM_E_NO_ERROR;

# if(NVM_DEV_ERROR_DETECT == STD_ON) /* ECO_IGNORE_LINE */
    if(NvM_CheckInitialized() == FALSE)
    {
        detErrorId = NVM_E_NOT_INITIALIZED;
    }
    else if (NvM_CheckBlockId(BlockId) == FALSE)
    {
        detErrorId = NVM_E_PARAM_BLOCK_ID;
    }
    else if (NvM_CheckCurrDataIndex(BlockId) == FALSE)
    {
        detErrorId = NVM_E_PARAM_BLOCK_DATA_IDX;
    }
    else if (NvM_BlockDescriptorTable_at[NVM_BLOCK_FROM_DCM_ID(BlockId)].BlockPrio_u8 != 0u)
    {
        detErrorId = NVM_E_BLOCK_CONFIG;
    }
    else if(NvM_CheckBlockPending(BlockId) == TRUE)
    {
        detErrorId = NVM_E_BLOCK_PENDING;
    }
    else
# endif /* ECO_IGNORE_LINE */
    {
        NvM_RamMngmtConstPtrToConstType ramMngmtPtr = NvM_GetMngmtAreaPtr(BlockId);

        if(NvM_WriteProtectionChecks(ramMngmtPtr) == TRUE) /* SBSW_NvM_FuncCall_PtrParam_BlockMngmtArea */
        {
            returnValue = NvM_QueueJob(BlockId, NVM_INT_FID_ERASE_BLOCK, NULL_PTR) ? E_OK : E_NOT_OK; /* SBSW_NvM_FuncCall_PtrParam_QueueJob */
        }
    }

# if (NVM_DEV_ERROR_REPORT == STD_ON)
    if(detErrorId != NVM_E_NO_ERROR)
    {
        NvM_Errorhook(NVM_ERASE_BLOCK, detErrorId);
    }
# else
    NVM_DUMMY_STATEMENT(detErrorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
# endif

    return returnValue;
} /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */

/**********************************************************************************************************************
*  NvM_InvalidateNvBlock
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
FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_InvalidateNvBlock(NvM_BlockIdType BlockId)
{
    Std_ReturnType returnValue = E_NOT_OK;
    uint8 detErrorId = NVM_E_NO_ERROR;

# if(NVM_DEV_ERROR_DETECT == STD_ON) /* ECO_IGNORE_LINE */
    if(NvM_CheckInitialized() == FALSE)
    {
        detErrorId = NVM_E_NOT_INITIALIZED;
    }
    else if (NvM_CheckBlockId(BlockId) == FALSE)
    {
        detErrorId = NVM_E_PARAM_BLOCK_ID;
    }
    else if (NvM_CheckCurrDataIndex(BlockId) == FALSE)
    {
        detErrorId = NVM_E_PARAM_BLOCK_DATA_IDX;
    }
    else if(NvM_CheckBlockPending(BlockId) == TRUE)
    {
        detErrorId = NVM_E_BLOCK_PENDING;
    }
    else
# endif /* ECO_IGNORE_LINE */
    {
        NvM_RamMngmtConstPtrToConstType ramMngmtPtr = NvM_GetMngmtAreaPtr(BlockId);

        if(NvM_WriteProtectionChecks(ramMngmtPtr) == TRUE) /* SBSW_NvM_FuncCall_PtrParam_BlockMngmtArea */
        {
            returnValue = NvM_QueueJob(BlockId, NVM_INT_FID_INVALIDATE_NV_BLOCK, NULL_PTR) ? E_OK : E_NOT_OK; /* SBSW_NvM_FuncCall_PtrParam_QueueJob */
        }
    }

# if (NVM_DEV_ERROR_REPORT == STD_ON)
    if(detErrorId != NVM_E_NO_ERROR)
    {
        NvM_Errorhook(NVM_INVALIDATE_NV_BLOCK, detErrorId);
    }
# else
    NVM_DUMMY_STATEMENT(detErrorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
# endif

    return returnValue;
} /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif /* (NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3) */

#if (NVM_API_CONFIG_CLASS > NVM_API_CONFIG_CLASS_1)
/**********************************************************************************************************************
*  NvM_CancelJobs
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
FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_CancelJobs(NvM_BlockIdType BlockId)
{
    Std_ReturnType returnValue = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
    uint8 detErrorId = NVM_E_NO_ERROR;

# if (NVM_DEV_ERROR_DETECT == STD_ON) /* ECO_IGNORE_LINE */
    if(NvM_CheckInitialized() == FALSE)
    {
        detErrorId = NVM_E_NOT_INITIALIZED;
    }
    else if (NvM_CheckBlockId(BlockId) == FALSE)
    {
        detErrorId = NVM_E_PARAM_BLOCK_ID;
    }
    else
# endif /* ECO_IGNORE_LINE */
    {
        returnValue = NvM_UnQueueJob(BlockId) ? E_OK : E_NOT_OK;
    }

# if (NVM_DEV_ERROR_REPORT == STD_ON)
    if(detErrorId != NVM_E_NO_ERROR)
    {
        NvM_Errorhook(NVM_CANCEL_JOBS, detErrorId);
    }
# else
    NVM_DUMMY_STATEMENT(detErrorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
# endif

    return returnValue;
}
#endif /* (NVM_API_CONFIG_CLASS > NVM_API_CONFIG_CLASS_1) */

/**********************************************************************************************************************
*  NvM_ReadAll
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
 */
FUNC(void, NVM_PUBLIC_CODE) NvM_ReadAll(void)
{
    uint8 detErrorId = NVM_E_NO_ERROR;

#if (NVM_DEV_ERROR_DETECT == STD_ON) /* ECO_IGNORE_LINE */
    if(NvM_CheckInitialized() == FALSE)
    {
        detErrorId = NVM_E_NOT_INITIALIZED;
    }
    else if (NvM_CheckMultiBlockPending() == TRUE)
    {
        detErrorId = NVM_E_BLOCK_PENDING;
    }
    else
#endif /* ECO_IGNORE_LINE */
    {
        NvM_EnterCriticalSection();

        NvM_BlockMngmtArea_at[0].NvRamErrorStatus_u8 = NVM_REQ_PENDING; /* SBSW_NvM_AccessBlockManagementArea */
        NvM_ApiFlags_u8 &= NVM_APIFLAG_KILL_READ_ALL_CL;
        NvM_ApiFlags_u8 |= NVM_APIFLAG_READ_ALL_SET;

        NvM_ExitCriticalSection();

        NvM_MultiBlockCbk(NVM_READ_ALL, NVM_REQ_PENDING);
    }

#if (NVM_DEV_ERROR_REPORT == STD_ON)
    if(detErrorId != NVM_E_NO_ERROR)
    {
        NvM_Errorhook(NVM_READ_ALL, detErrorId);
    }
#else
    NVM_DUMMY_STATEMENT(detErrorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
#endif
}

/**********************************************************************************************************************
*  NvM_KillReadAll
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
FUNC(void, NVM_PUBLIC_CODE) NvM_KillReadAll(void)
{
    uint8 detErrorId = NVM_E_NO_ERROR;

#if (NVM_DEV_ERROR_DETECT == STD_ON) /* ECO_IGNORE_LINE */
    if(NvM_CheckInitialized() == FALSE)
    {
        detErrorId = NVM_E_NOT_INITIALIZED;
    }
    else
#endif /* ECO_IGNORE_LINE */
    {
        if((NvM_ApiFlags_u8 & NVM_APIFLAG_READ_ALL_SET) == NVM_APIFLAG_READ_ALL_SET)
        {
            NvM_EnterCriticalSection();
            NvM_ApiFlags_u8 |= NVM_APIFLAG_KILL_READ_ALL_SET;
            NvM_ExitCriticalSection();
        }
    }

#if (NVM_DEV_ERROR_REPORT == STD_ON)
    if(detErrorId != NVM_E_NO_ERROR)
    {
        NvM_Errorhook(NVM_KILL_READ_ALL, detErrorId);
    }
#else
    NVM_DUMMY_STATEMENT(detErrorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
#endif
}

/**********************************************************************************************************************
*  NvM_WriteAll
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
FUNC(void, NVM_PUBLIC_CODE) NvM_WriteAll(void)
{
    uint8 detErrorId = NVM_E_NO_ERROR;

#if (NVM_DEV_ERROR_DETECT == STD_ON) /* ECO_IGNORE_LINE */
    if(NvM_CheckInitialized() == FALSE)
    {
        detErrorId = NVM_E_NOT_INITIALIZED;
    }
    else if (NvM_CheckMultiBlockPending() == TRUE)
    {
        detErrorId = NVM_E_BLOCK_PENDING;
    }
    else
#endif /* ECO_IGNORE_LINE */
    {
        NvM_EnterCriticalSection();

        NvM_BlockMngmtArea_at[0u].NvRamErrorStatus_u8 = NVM_REQ_PENDING; /* SBSW_NvM_AccessBlockManagementArea */

        NvM_ApiFlags_u8 &= (NVM_APIFLAG_KILL_WR_ALL_CL & NVM_APIFLAG_CANCEL_WR_ALL_CL);
        NvM_ApiFlags_u8 |= NVM_APIFLAG_WRITE_ALL_SET;

        NvM_ExitCriticalSection();

        NvM_MultiBlockCbk(NVM_WRITE_ALL, NVM_REQ_PENDING);
    }

#if (NVM_DEV_ERROR_REPORT == STD_ON)
    if(detErrorId != NVM_E_NO_ERROR)
    {
        NvM_Errorhook(NVM_WRITE_ALL, detErrorId);
    }
#else
    NVM_DUMMY_STATEMENT(detErrorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
#endif
}

/**********************************************************************************************************************
*  NvM_CancelWriteAll
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
FUNC(void, NVM_PUBLIC_CODE) NvM_CancelWriteAll(void)
{
    uint8 detErrorId = NVM_E_NO_ERROR;

#if (NVM_DEV_ERROR_DETECT == STD_ON) /* ECO_IGNORE_LINE */
    if(NvM_CheckInitialized() == FALSE)
    {
        detErrorId = NVM_E_NOT_INITIALIZED;
    }
    else
#endif /* ECO_IGNORE_LINE */
    {
        NvM_EnterCriticalSection();

        NvM_ApiFlags_u8 |= NVM_APIFLAG_CANCEL_WR_ALL_SET;

        NvM_ExitCriticalSection();
    }

#if (NVM_DEV_ERROR_REPORT == STD_ON)
    if(detErrorId != NVM_E_NO_ERROR)
    {
        NvM_Errorhook(NVM_CANCEL_WRITE_ALL, detErrorId);
    }
#else
    NVM_DUMMY_STATEMENT(detErrorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
#endif
}

#if (NVM_KILL_WRITEALL_API == STD_ON)
/**********************************************************************************************************************
*  NvM_KillWriteAll
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
FUNC(void, NVM_PUBLIC_CODE) NvM_KillWriteAll(void)
{
    uint8 detErrorId = NVM_E_NO_ERROR;

# if (NVM_DEV_ERROR_DETECT == STD_ON) /* ECO_IGNORE_LINE */
    if(NvM_CheckInitialized() == FALSE)
    {
        detErrorId = NVM_E_NOT_INITIALIZED;
    }
    else
# endif /* ECO_IGNORE_LINE */
    {
        /* Flags indicating, whether deferred function calls shall be done at the end.
           We don't want them being called from inside a critical section, on the other hand we'd like to keep number
           of paths (where the critical section must be explicitly left) at a minimum (see ESCAN00072502) */
        
        if((NvM_ApiFlags_u8 & NVM_APIFLAG_WRITE_ALL_SET) == NVM_APIFLAG_WRITE_ALL_SET)
        {
            NvM_BlockIdType blockEndNotificationId = 0u; /* 0 (multiblock ID -> invalid in this context) -> no notification  */
            const NvM_RamMngmtPtrType mngmt_pt = NvM_CurrentBlockInfo_t.Mngmt_pt;
            /* since a NvM_KillWriteAll might be called from a task which preempted NvM_MainFunction,
            this is a critical section. */
            NvM_EnterCriticalSection();
            /*  Clear WriteAll Flag -> if WriteAll was just queued, but not started yet, it will be simply discarded.
             *                      -> WriteAll may be requested immediately after we return.
             *  set both flags, "Cancel WriteAll" and "Kill WriteAll". The former one, makes sure, that
             *  No Block processing will be started, if WriteAll was not started until now               */
            NvM_ApiFlags_u8 &= NVM_APIFLAG_WRITE_ALL_CL;
            NvM_ApiFlags_u8 |= NVM_APIFLAG_KILL_WR_ALL_SET | NVM_APIFLAG_CANCEL_WR_ALL_SET;

            /* Check whether current job is actually a writeAll job, and if it actually processes an NVRAM Block */
            /* PRQA S 3415 2 */ /* MD_NvM_13.5 */
            if((NvM_CurrentJob_t.JobServiceId_t == NVM_INT_FID_WRITE_ALL)
                && (NvM_CheckBlockId(NvM_CurrentJob_t.JobBlockId_t))) /* COV_NVM_KILLWRITEALL */
            {
                blockEndNotificationId = NvM_CurrentJob_t.JobBlockId_t;

                /* immediately set it to NVM_REQ_OK, if it is VALID, otherwise set it to skipped */
                mngmt_pt->NvRamErrorStatus_u8 = 
                    ((mngmt_pt->NvRamAttributes_u8 & NVM_STATE_VALID_SET) == NVM_STATE_VALID_SET) ? NVM_REQ_OK : NVM_REQ_BLOCK_SKIPPED; /* SBSW_NvM_Access_CurrBlockInfo */
            }

            /* Mark WriteAll as CANCELLED for the world (EcuM), however the internal handling does not finish immediately */
            NvM_BlockMngmtArea_at[0].NvRamErrorStatus_u8 = NVM_REQ_CANCELED; /* SBSW_NvM_AccessBlockManagementArea */

            NvM_ExitCriticalSection();

            if(blockEndNotificationId > 0u)
            {
                NvM_BlockNotification(blockEndNotificationId, NVM_WRITE_ALL, mngmt_pt->NvRamErrorStatus_u8);
            }

            NvM_MultiBlockCbk(NVM_WRITE_ALL, NVM_REQ_CANCELED);
        }
    }

# if (NVM_DEV_ERROR_REPORT == STD_ON)
    if(detErrorId != NVM_E_NO_ERROR)
    {
        NvM_Errorhook(NVM_KILL_WRITE_ALL, detErrorId);
    }
# else
    NVM_DUMMY_STATEMENT(detErrorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
# endif
}
#endif /* (NVM_KILL_WRITEALL_API == STD_ON) */

#if (NVM_REPAIR_REDUNDANT_BLOCKS_API == STD_ON)
/**********************************************************************************************************************
*  NvM_RepairRedundantBlocks
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
FUNC(void, NVM_PUBLIC_CODE) NvM_RepairRedundantBlocks(void)
{
    uint8 detErrorId = NVM_E_NO_ERROR;

# if (NVM_DEV_ERROR_DETECT == STD_ON) /* ECO_IGNORE_LINE */
    if (NvM_CheckInitialized() == FALSE)
    {
        detErrorId = NVM_E_NOT_INITIALIZED;
    }
    else
# endif /* ECO_IGNORE_LINE */
    {
        NvM_EnterCriticalSection();

        NvM_ApiFlags_u8 |= NVM_APIFLAG_REPAIR_REDUNDANT_BLOCKS_SET;

        NvM_ExitCriticalSection();
    }

# if (NVM_DEV_ERROR_REPORT == STD_ON)
    if(detErrorId != NVM_E_NO_ERROR)
    {
        NvM_Errorhook(NVM_REPAIR_REDUNDANT_BLOCKS, detErrorId);
    }
# else
    NVM_DUMMY_STATEMENT(detErrorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
# endif
}
#endif /* (NVM_REPAIR_REDUNDANT_BLOCKS_API == STD_ON) */


/**********************************************************************************************************************
*  NvM_MainFunction
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
FUNC(void, NVM_PUBLIC_CODE) NvM_MainFunction(void)
{
    uint8 detErrorId = NVM_E_NO_ERROR;

#if (NVM_DEV_ERROR_DETECT == STD_ON) /* ECO_IGNORE_LINE */
    if (NvM_CheckInitialized() == FALSE)
    {
        detErrorId = NVM_E_NOT_INITIALIZED;
    }
    else
#endif /* ECO_IGNORE_LINE */
    {
        /* reset the wait flag */
        NvM_CurrentBlockInfo_t.InternalFlags_u8 &= NVM_INTFLAG_WAIT_CL;

#if ((NVM_SET_RAM_BLOCK_STATUS_API == STD_ON) && (NVM_CALC_RAM_CRC_USED == STD_ON))
        /* #210 Process asynchronous background CRC job queue */
        NvM_ProcessBackgroundCrcJobs();
#endif

        /* #220 Loop: process state machine as long as the NvM does not have to wait (wait flag). */
        do
        {
            NvM_TaskState_t = NvM_Fsm(NvM_TaskState_t);

            NvM_JobMainState_t = NvM_Fsm(NvM_JobMainState_t);

            NvM_JobSubState_t = NvM_Fsm(NvM_JobSubState_t);
        }
        while ((NvM_CurrentBlockInfo_t.InternalFlags_u8 & NVM_INTFLAG_WAIT_SET) == 0u);
    }

#if (NVM_DEV_ERROR_REPORT == STD_ON)
    if(detErrorId != NVM_E_NO_ERROR)
    {
        NvM_Errorhook(NVM_MAINFUNCTION, detErrorId);
    }
#else
    NVM_DUMMY_STATEMENT(detErrorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
#endif
}

#if (NVM_POLLING_MODE == STD_OFF)
/**********************************************************************************************************************
*  NvM_JobEndNotification
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, NVM_PUBLIC_CODE) NvM_JobEndNotification(void)
{
     NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_OK;
}

/**********************************************************************************************************************
*  NvM_JobErrorNotification
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, NVM_PUBLIC_CODE) NvM_JobErrorNotification(void)
{
    /* sets LastResult depending on JobResult of lower layer */
    switch(MemIf_GetJobResult((uint8)NvM_CurrentBlockInfo_t.Descriptor_pt->DeviceId_u8))
    {       

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
#endif /* (NVM_POLLING_MODE == STD_OFF) */

/**********************************************************************************************************************
*  NvM_SetBlockLockStatus
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
FUNC(void, NVM_PUBLIC_CODE) NvM_SetBlockLockStatus(NvM_BlockIdType BlockId, boolean BlockLocked)
{
    uint8 detErrorId = NVM_E_NO_ERROR;

#if (NVM_DEV_ERROR_DETECT == STD_ON) /* ECO_IGNORE_LINE */
    if(NvM_CheckInitialized() == FALSE)
    {
        detErrorId = NVM_E_NOT_INITIALIZED;
    }
    else if (NvM_CheckBlockId(BlockId) == FALSE)
    {
        detErrorId = NVM_E_PARAM_BLOCK_ID;
    }
    else if (NvM_CheckCurrDataIndex(BlockId) == FALSE)
    {
        detErrorId = NVM_E_PARAM_BLOCK_DATA_IDX;
    }
    else
#endif /* ECO_IGNORE_LINE */
    {
        NvM_EnterCriticalSection();

        if (BlockLocked)
        {
            NvM_BlockMngmtArea_at[NVM_BLOCK_FROM_DCM_ID(BlockId)].NvRamAttributes_u8 |= NVM_LOCK_STAT_SET; /* SBSW_NvM_AccessBlockManagementArea */
        }
        else
        {
            NvM_BlockMngmtArea_at[NVM_BLOCK_FROM_DCM_ID(BlockId)].NvRamAttributes_u8 &= NVM_LOCK_STAT_CL; /* SBSW_NvM_AccessBlockManagementArea */
        }

        NvM_ExitCriticalSection();
    }

#if (NVM_DEV_ERROR_REPORT == STD_ON)
    if(detErrorId != NVM_E_NO_ERROR)
    {
        NvM_Errorhook(NVM_SET_BLOCK_LOCK_STATUS, detErrorId);
    }
#else
    NVM_DUMMY_STATEMENT(detErrorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
#endif
}

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

#if (NVM_API_CONFIG_CLASS > NVM_API_CONFIG_CLASS_1)
/**********************************************************************************************************************
*  NvM_WriteProtectionChecks
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
NVM_LOCAL_INLINE FUNC(boolean, NVM_PRIVATE_CODE) NvM_WriteProtectionChecks(const NvM_RamMngmtConstPtrType MngmtPtr)
{
    boolean returnValue = FALSE;

    /* #10 check whether the block is write protected */
    if ((MngmtPtr->NvRamAttributes_u8 & NVM_WR_PROT_SET) != 0u)
    {
        NvM_DemReportErrorWriteProtected();
    }
    /*  #20 block is not write protected and is an origin block (not a DCM block) */
    else if (MngmtPtr != &NvM_DcmBlockMngmt_t)
    {
        returnValue = (boolean)((MngmtPtr->NvRamAttributes_u8 & NVM_LOCK_STAT_SET) == 0u);
    }
    /* #30 all block is not write protected, check is ok */
    else
    {
        returnValue = TRUE;
    }

    return returnValue;
}
#endif /* (NVM_API_CONFIG_CLASS > NVM_API_CONFIG_CLASS_1) */

/**********************************************************************************************************************
*  NvM_CheckBlockType
**********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
*/
NVM_LOCAL_INLINE FUNC(boolean, NVM_PRIVATE_CODE) NvM_CheckBlockType(const NvM_BlockIdType BlockId)
{
  return (boolean)((NvM_BlockDescriptorTable_at[NVM_BLOCK_FROM_DCM_ID(BlockId)].MngmtType_t & NVM_BLOCK_DATASET) != 0u);
}

#if ((NVM_API_CONFIG_CLASS > NVM_API_CONFIG_CLASS_1) && (NVM_DEV_ERROR_DETECT == STD_ON))
/**********************************************************************************************************************
*  NvM_CheckAddress
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL_INLINE FUNC(boolean, NVM_PRIVATE_CODE) NvM_CheckAddress(const NvM_BlockIdType BlockId, const void * RamPtr)
{
    NvM_BlockDescrPtrType descPtr = &NvM_BlockDescriptorTable_at[NVM_BLOCK_FROM_DCM_ID(BlockId)];
    boolean returnValue = TRUE;

    /* for a request setup with RamPtr != NULL_PTR:
     * - BlockId must be NvM Block Id AND
     * - permanent RAM OR explicit synchronization has to be configured */
    if(RamPtr == NULL_PTR) /* COV_NVM_COVEREDINOTHERCFG */
    {
        returnValue = (boolean)((NVM_BLOCK_FROM_DCM_ID(BlockId) == BlockId) &&
            ((descPtr->RamBlockDataAddr_t != NULL_PTR) || (descPtr->CbkGetMirrorFunc_pt != NULL_PTR))); /* COV_NVM_COVEREDINOTHERCFG */
    }

    return returnValue;
}
#endif /* ((NVM_API_CONFIG_CLASS > NVM_API_CONFIG_CLASS_1) && (NVM_DEV_ERROR_DETECT == STD_ON)) */

# if (NVM_DEV_ERROR_DETECT == STD_ON) || (NVM_KILL_WRITEALL_API == STD_ON)
/**********************************************************************************************************************
*  NvM_CheckBlockId
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL_INLINE FUNC(boolean, NVM_PRIVATE_CODE) NvM_CheckBlockId(const NvM_BlockIdType BlockId)
{
    return (boolean)((NVM_BLOCK_FROM_DCM_ID(BlockId) > 0u) && (NVM_BLOCK_FROM_DCM_ID(BlockId) < NvM_NoOfBlockIds_t)); /* COV_NVM_COVEREDINOTHERCFG */
}
# endif

#if (NVM_DEV_ERROR_DETECT == STD_ON)
/**********************************************************************************************************************
*  NvM_CheckCurrDataIndex
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL_INLINE FUNC(boolean, NVM_PRIVATE_CODE) NvM_CheckCurrDataIndex(const NvM_BlockIdType BlockId)
{
    return (boolean)(NvM_BlockMngmtArea_at[NVM_BLOCK_FROM_DCM_ID(BlockId)].NvDataIndex_t <
        NvM_BlockDescriptorTable_at[NVM_BLOCK_FROM_DCM_ID(BlockId)].NvBlockCount_u8);
}

/**********************************************************************************************************************
*  NvM_CheckDataIndex
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL_INLINE FUNC(boolean, NVM_PRIVATE_CODE) NvM_CheckDataIndex(const NvM_BlockIdType BlockId, const uint8 DataIndex)
{
    return (boolean)(DataIndex < NvM_BlockDescriptorTable_at[NVM_BLOCK_FROM_DCM_ID(BlockId)].NvBlockCount_u8);
}

/**********************************************************************************************************************
*  NvM_CheckNotNull
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL_INLINE FUNC(boolean, NVM_PRIVATE_CODE) NvM_CheckNotNull(const uint8 * Ptr)
{
    return (boolean)(Ptr != NULL_PTR);
}

/**********************************************************************************************************************
*  NvM_CheckInitialized
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL_INLINE FUNC(boolean, NVM_PRIVATE_CODE) NvM_CheckInitialized(void)
{
    return (boolean)(NvM_TaskState_t != NVM_STATE_UNINIT);
}

/**********************************************************************************************************************
*  NvM_CheckMultiBlockPending
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL_INLINE FUNC(boolean, NVM_PRIVATE_CODE) NvM_CheckMultiBlockPending(void)
{
    return (boolean)(NvM_BlockMngmtArea_at[0].NvRamErrorStatus_u8 == NVM_REQ_PENDING);
}
#endif /* (NVM_DEV_ERROR_DETECT == STD_ON) */

/**********************************************************************************************************************
*  NvM_CheckBlockPending
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
NVM_LOCAL_INLINE FUNC(boolean, NVM_PRIVATE_CODE) NvM_CheckBlockPending(const NvM_BlockIdType BlockId)
{
    boolean blockPending;

    /* #100 required block Id is not the multi block itself and multi block request is pending */
    if((BlockId > 0u) && ((NvM_CurrentJob_t.JobServiceId_t == NVM_INT_FID_WRITE_ALL) || (NvM_CurrentJob_t.JobServiceId_t == NVM_INT_FID_READ_ALL)))
    {
        /* #110 NvM_WriteAll is pending */
        if((NvM_ApiFlags_u8 & NVM_APIFLAG_WRITE_ALL_SET) == NVM_APIFLAG_WRITE_ALL_SET)
        {
            /* WriteAll begins with last block and ends with configuration block -> higher block Id than current is done */
            blockPending = (boolean)(BlockId < NvM_CurrentJob_t.JobBlockId_t);
        }
        /* #120 NvM_ReadAll is pending */
        else
        {
            /* ReadAll begins with configuration block and ends with last block -> lower block Id than current is done */
            blockPending = (boolean)(BlockId > NvM_CurrentJob_t.JobBlockId_t);
        }
    }
    /* #200 required block Id is the multi block or multi block request is not pending */
    else
    {
        /* #210 checks whether the given RAM management area describes a pending Block */
        blockPending = (boolean)(NvM_GetMngmtAreaPtr(BlockId)->NvRamErrorStatus_u8 == NVM_REQ_PENDING);
    }

    return blockPending;
}

/**********************************************************************************************************************
*  NvM_GetMngmtAreaPtr
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
NVM_LOCAL_INLINE FUNC(NvM_RamMngmtPtrType, NVM_PRIVATE_CODE) NvM_GetMngmtAreaPtr(const NvM_BlockIdType BlockId)
{
    return (BlockId == NVM_BLOCK_FROM_DCM_ID(BlockId)) ? (&NvM_BlockMngmtArea_at[BlockId]) : (&NvM_DcmBlockMngmt_t);
}

#if ((NVM_SET_RAM_BLOCK_STATUS_API == STD_ON) && (NVM_CALC_RAM_CRC_USED == STD_ON))
/**********************************************************************************************************************
 *  NvM_ProcessBackgroundCrcJobs
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
 *
 *
 *
 */
NVM_LOCAL_INLINE FUNC(void, NVM_PRIVATE_CODE) NvM_ProcessBackgroundCrcJobs(void)
{
  if(!NvM_CrcJob_isBusy(&NvM_AsyncCrcJob_t))
  {
    NvM_BlockIdType newCrcBlockId = NvM_CrcGetQueuedBlockId();
    const NvM_BlockDescrPtrType descr_pt = &NvM_BlockDescriptorTable_at[newCrcBlockId];
    NvM_RamAddressType crcRecalculationPtr = descr_pt->RamBlockDataAddr_t;

    /* Copy CRC from previous CRC job to target CRC buffer, before creating a new job */
    NvM_CrcJob_CopyToBuffer(&NvM_AsyncCrcJob_t);                                                                        /* SBSW_NvM_FuncCall_PtrParam_CrcAsyncJob */

#if (NVM_CRC_USE_INTERNAL_EXPLICIT_SYNC_BUFFER == STD_ON)
    /*
     * Special case:
     * When generator detects blocks with enabled explicit synchronization AND enabled NvMCalcRamBlockCrc an extra
     * internal buffer is generated. This is necessary in order to allow normal job processing via NvM APIs and keep
     * this CRC calculations in the background.
     */
    if (descr_pt->CbkSetMirrorFunc_pt != NULL_PTR)
    {
      /* If block is using explicit synchronization, the data must be synchronized before starting CRC recalculation */
      if(descr_pt->CbkSetMirrorFunc_pt(NvM_CrcInternalExplicitSyncBuffer) == E_OK)                                      /* SBSW_NvM_FuncPtrCall_UserCallbacks */ /* PRQA S 0315 */ /* MD_NvM_Dir1.1_CastToVoidPtr */
      {
        crcRecalculationPtr = NvM_CrcInternalExplicitSyncBuffer;
      }
      else
      {
        /* Mirror function error. Do not create a new CRC job. => blockID '0' targets to 'empty' target */
        newCrcBlockId = 0u;
      }
    }
#endif

    /*
     * Create new Crc Job with next BlockId from CRC queue
     * Note: If the queue is empty we get 0.
     *       Due to block 0's Descriptor, it will result in an "empty" CRC job.
     *       By using it as a dummy an additional and unnecessary check can be omitted. */
    NvM_CrcJob_Create(&NvM_AsyncCrcJob_t, newCrcBlockId, crcRecalculationPtr, descr_pt->NvBlockLength_u16);    /* SBSW_NvM_FuncCall_PtrParam_CrcAsyncJob */

# if (NVM_CRC_INT_BUFFER == STD_ON)
    /* As default the target CRC buffer is placed at the end of the RAM block data buffer */
    NvM_CrcJob_ReassignBuffer(&NvM_AsyncCrcJob_t, descr_pt->RamBlockCrcAddr_t);                                         /* SBSW_NvM_AccessPtr_CrcReassignBuffer */
# endif
  }

  /* Process CRC chunk */
  NvM_CrcJob_Process(&NvM_AsyncCrcJob_t, NvM_NoOfCrcBytes_u16);                                                         /* SBSW_NvM_FuncCall_PtrParam_CrcAsyncJob */
}
#endif

#define NVM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/***********************************************************************************************************************
 *  MISRA JUSTIFICATIONS
 **********************************************************************************************************************/
/* Justification for module-specific MISRA deviations:

MD_NvM_8.9:
  Reason: Query function table logically belongs to the NvM_Qry. Due to architectural decisions this table shall stay
          here for now.
  Risk: Components including the NvM_Qry.h file could directly call queries which then interfere with the intrinsic
        behavior of the component.
  Prevention: A code review should ensure that usage of this table is done correctly.

MD_NvM_8.9_CrcHandlerTable
  Reason: The array NvM_CrcHandlerTable_at stores all possible CRC handlers, the implementation simply uses the configured
          CRC type as an index into the table to use the correct CRC handler.
          Instead of the table the CRC handler could be set within a if else if statements or similar, but the table avoids
          decisions within the code, but costs a bit memory.
  Risk: No risk.
  Prevention: No prevention, component tests and reviews ensure functionality.

MD_NvM_8.9_TestBuffer
  Reason: To check the readability of a (redundant) NvM block, NvM uses a single byte NvM_TestBuffer_u8 - during a read and
          RepairRedundantBlocks. In case the RepairRedundantBlocks feature is disabled, the buffer will only be accessed once.
  Risk: No risk.
  Prevention: No prevention, component tests and reviews ensure functionality.

MD_NvM_8.9_StateTable
  Reason: The state descriptor table holds the complete NvM state machine - all states. NvM_Fsm is the only function
          accessing the state table since the function is the one moving the NvM from one state to the next and so on.
          NvM is not allowed to access the table from another sub modules and/ or functions.
  Risk: No risk.
  Prevention: No prevention, component tests and reviews ensure functionality.

MD_NvM_8.11_Crc16PtrCast
  Reason: The cast from uint32 to uint16 pointer is necessary to be independent from RAM endiannes: the NvM always needs
          to access the 16 bit CRC value in the first two bytes of the passed uint32 pointer value.
  Risk: No risk.
  Prevention: No prevention.

MD_NvM_8.13_NoCrcHandler
  Reason: No Crc handler, used as dummies to avoid differing between CRC and no CRC, has to match the same signature like "real"
        Crc handlers. Because the No Crc handler does nothing, empty functions, the function parameters remain unused and could
        be const -> because of the signature the parameter remains non constant.
  Risk: No risk, the functions are empty, they do not use the parameters.
  Prevention: No prevention.

MD_NvM_11.5_CastLossOfConst:
  Reason: Cast removing const qualifier is necessary.
  Risk: The component is able to modify the pointer content which could result in undefined behavior.
  Prevention: A code review should ensure that the parameters are used correctly.

MD_NvM_11.5_CastVoidPtrToObjPtr:
  Reason: Cast is necessary to call the job-queue API that is processing the request.
  Risk: Cast into an inappropriate type can lead to unexpected behavior.
  Prevention: A code review should ensure that the parameters are used correctly.

MD_NvM_13.5:
  Reason: Operands of '&&' or '||' is a helper function that is extracting information and has no side effect.
          Usage helps the structure and readability of the code a lot.
  Risk: None.
  Prevention: None.

MD_NvM_13.5_ReadAllAndKillReadAll:
  Reason: Finishing the ReadAll request depends on KillReadAll request - if requested the job result shall be
          set to canceled, otherwise the result reflects the result of the finished ReadAll.
  Risk: No risk.
  Prevention: No prevention, reviews and component test ensure functionality.

MD_NvM_Dir1.1_CastToVoidPtr:
  Reason: The used callback is defined with a void-pointer to a buffer. As the used buffer type is uint8 there is no
          chance to avoid this cast.
  Risk: None. A pointer-to-object can always be converted safely to a pointer-to-void.
  Prevention: None.

*/

/***********************************************************************************************************************
 *  SILENTBSW JUSTIFICATIONS
 **********************************************************************************************************************/
/* SBSW_JUSTIFICATION_BEGIN

\ID SBSW_NvM_AccessBlockManagementArea
 \DESCRIPTION Write access to the array storing the NvM block management information about each configured block.
              The required array element is accessed via block Id passed to NvM - each block Id is an array index,
              or via internal block Id 0. NvM expects the given block Id to be valid.
 \COUNTERMEASURE \R Correctness of given parameter is checked by NvM only in case development mode is enabled.

\ID SBSW_NvM_Access_CurrBlockInfo
 \DESCRIPTION NvM Write access to NvM internal variable storing information about current block and job. The variable has to be
              initialized correctly by NvM itself.
 \COUNTERMEASURE \N The NvM itself is responsible to initialize and access its internal structures correctly. Correct usage is
                 ensured by tests and code reviews.

\ID SBSW_NvM_PtrAccess_PublicAPI
 \DESCRIPTION Write access to a pointer, which is given to NvM function as parameter. NvM expects the pointer to be valid.
 \COUNTERMEASURE \R NvM checks the given pointer not to be NULL before using it, but only in case Development Error Detection is enabled.

\ID SBSW_NvM_FuncCall_PtrParam_CurrBlockInfo
 \DESCRIPTION NvM passes its current job parameter to internal functions as pointer. There is no explicit check whether the current job is valid,
              the internal function is invoked only during job processing.
 \COUNTERMEASURE \N Actions and queries which use the internal job parameter does not check whether the parameter are valid or not. They shall
                 only be invoked in case a valid job is currently running. Correct usage is ensured by tests and code reviews.

\ID SBSW_NvM_FuncPtrCall_QueryAction
 \DESCRIPTION All accesses to internal queries and actions are done via function pointer calls. There are no explicit checks whether the
              passed function pointer is valid or not, this is ensured via correct implementation.
 \COUNTERMEASURE \N The NvM itself is responsible to initialize and access its internal structures correctly. Correct usage is ensured by tests and code reviews.

\ID SBSW_NvM_FuncCall_PtrParam_ParamChecker
 \DESCRIPTION NvM uses helper functions to check pointer parameter to be valid (development error mode checks). Those functions only check the
              given pointer to be or not to be NULL and return, they do not use the pointer. Functions expects all other parameter to be valid (checked before invoking)
 \COUNTERMEASURE \N Functions are only used to check parameter, not to use them. Their correctness is ensured via component tests and code reviews.

\ID SBSW_NvM_FuncCall_PtrParam_FsmQuery
 \DESCRIPTION Within the NvM state machine the next actions to execute are determined via queries. Invoked function gets two function pointers to queries
              stored in an array, checks their results and return accordingly. The function expects a valid parameter to be able to call both queries.
 \COUNTERMEASURE \N The code correctness is ensured via NvM state machine structure and is not tested explicitly. Current tests and
                 code reviews shall confirm the structure correctness.

\ID SBSW_NvM_FuncCall_PtrParam_FsmAction
 \DESCRIPTION To execute actions corresponding function is invoked with an pointer parameter, pointing to an array storing both action pointers (function pointers).
              The function expects the given pointer and included function pointers to be valid and does not check them explicitly.
 \COUNTERMEASURE \N The code correctness is ensured via NvM state machine structure and is not tested explicitly. Current tests and
                 state machine reviews shall confirm the structure correctness.

\ID SBSW_NvM_FuncCall_PtrParam_QueueJob
 \DESCRIPTION NvM uses a queue to store jobs to be processed later. The corresponding function is called from NvM's public APIs with parameter
              passed to the public function. The queue function expects the parameter are valid - the caller has to check them, which is done
              in development error mode.
 \COUNTERMEASURE \R NvM checks the parameter given to a public API to be valid, in case development error mode is enabled.

\ID SBSW_NvM_FuncCall_PtrParam_BlockMngmtArea
 \DESCRIPTION NvM uses helper functions with pointer to according block management data as parameter. The function does not check the pointer correctness,
              it expects the pointer is valid and uses it. NvM functions which uses the helper function are responsible for invoking with valid parameter.
 \COUNTERMEASURE \R NvM check the parameter given to a public API to be valid, in case development error mode is enabled and invokes the helper function
                 only with valid parameter.

\ID SBSW_NvM_FuncCall_PtrParam_CrcAsyncJob
 \DESCRIPTION To process queued CRC jobs with MainFunction calls NvM uses a local CRC job parameter. This parameter is passed to functions as pointer and
              will be initialized in one and used in another functions. NvM is responsible for invoking the function in correct order.
 \COUNTERMEASURE \N Functions do not check their parameter before using them, they expect the parameter are valid. Correct functionality shall be
                 checked within reviews and/or component tests.

\ID SBSW_NvM_FuncCall_PtrParam_MemIf
 \DESCRIPTION NvM uses MemIf functions to read/ write data from/ to NV RAM. NvM is responsible to provide valid parameter as identifier or buffers.
 \COUNTERMEASURE \T Correct NvM behavior is checked during component tests. Also code reviews shall ensure correct invoking of the MemIf module.

\ID SBSW_NvM_FuncCall_PtrParam_Csm
 \DESCRIPTION NvM invokes the CSM encrypt and decrypt APIs, of which the signature requires pointers. NvM is responsible to provide valid parameters/ buffers
              and pass them to the CSM.
 \COUNTERMEASURE \T The following test cases ensure the correct pointers: TCASE-1162566, TCASE-1162565, TCASE-1162561, TCASE-1162562, TCASE-1164959,
                 TCASE-1164960, TCASE-1164957, TCASE-1164958. Other test cases verify correct behavior too (implicitly or explicitly).

\ID SBSW_NvM_AccessCrcQueue
 \DESCRIPTION NvM uses a CRC queue to store CRC calculation jobs to be processed later. The queue is only available if SetRamBlockStatus API is enabled
              and at least one block is configured with Calc RAM CRC. To access the queue NvM calculates element indexes.
 \COUNTERMEASURE \T Correct NvM CRC queue behavior is checked during component tests. Code reviews shall ensure correct behavior, too.

\ID SBSW_NvM_AccessCrcJobPtr
 \DESCRIPTION To setup and process a CRC job NvM uses a job structure storing all required parameter. This structure is passed to different functions
              as pointer parameter - all functions assume the pointer is valid and uses it.
 \COUNTERMEASURE \T Correct NvM CRC job usage is checked during component tests and code reviews.

\ID SBSW_NvM_FuncPtrCall_CrcHandler
 \DESCRIPTION To calculate, compare or copy CRC values NvM uses CRC helper functions - for each CRC type there are exactly 3 functions.
              These 3 functions are stored in one CRC specific handler, which is passed to different functions as pointer. Functions which get a CRC handler
              as pointer parameter assumes it is valid and work with it.
 \COUNTERMEASURE \T Correct NvM CRC job usage is checked during component tests and code reviews.

\ID SBSW_NvM_AccessArray_BlockIdInCrc
 \DESCRIPTION There is a special feature NvM uses to ensure the data delivered by underlying modules fits to requested NvM block - it calculate the NvM block Id
              and current data index into the CRC. To do this the block Id and the data index are stored in an extra array and the NvM invokes the CRC module
              with this array to calculate CRC for the data. The array is exactly 3 bytes long and specific function local.
 \COUNTERMEASURE \T Correct buffer usage is checked during component tests and code reviews.

\ID SBSW_NvM_AccessPtr_CrcReassignBuffer
 \DESCRIPTION In case the internal CRC buffer is enabled, NvM uses internal buffer to store the block CRC. During CRC job setup pointer to this buffer
              will be stored in CRC job to be able to fill it directly.
 \COUNTERMEASURE \T Correct buffer usage is checked during component tests and code reviews.

\ID SBSW_NvM_AccessJobQueue
 \DESCRIPTION To store NvM jobs to be processed later asynchronously NvM uses a queue with configured length. The queue is an array storing all queued jobs. NvM accesses
              the queue via calculated indexes. The index calculations has to be correct to ensure correct array accesses.
 \COUNTERMEASURE \T Correct job queue behavior is checked during component tests and code review.

\ID SBSW_NvM_FuncCall_PtrParam_Queue
 \DESCRIPTION NvM job queue invokes its internal helper functions with pointer parameter. These are always valid when passing as parameter,
              invoked functions does not check them.
 \COUNTERMEASURE \T Correct job queue behavior is checked during component tests and code reviews.

\ID SBSW_NvM_AccessPtr_QueueIndex
 \DESCRIPTION Because the NvM job queue actually is an array NvM uses indexes to access the required queue element. Some functions
              require pointers to those indexes as parameter - in this case the caller is responsible for providing valid pointers
              storing valid indexes, functions does not check the given parameter.
 \COUNTERMEASURE \T Correct job queue behavior is checked during component tests and code reviews.

\ID SBSW_NvM_AccessPtr_UsedQueue
 \DESCRIPTION In case job prioritization is enabled NvM uses two different queues: normal and high priority queue. In some situations we have to check
              both queues - this is done via queue pointer. Pointer is initialized with one queue, then the second queue is checked, whether it shall be used
              and the pointer will be reassigned or not. No matter how the pointer always points to a queue and can be used.
 \COUNTERMEASURE \T Correct job queue behavior is checked during component tests and code reviews.

\ID SBSW_NvM_FuncPtrCall_UserCallbacks
 \DESCRIPTION NvM stores all user callbacks in function pointers and invokes them depending on callback type. NvM does not check whether the callback
              functions are valid, it assumes the configuration is correct.
 \COUNTERMEASURE \N User is responsible to provide valid functions to be called as callbacks. To avoid NULL function pointer there are checks within
                 configuration tool. NvM does not invoke disabled callbacks (function pointers are NULL and corresponding flags are disabled)

\ID SBSW_NvM_FuncCall_CrcModule
 \DESCRIPTION To calculate a NvM block CRC NvM uses CRC module functions. They are always invoked with valid parameters from NvM CRC job.
 \COUNTERMEASURE \T Correct NvM behavior is checked during component tests and code reviews.

\ID SBSW_NvM_AccessArray_CrcBuffers
 \DESCRIPTION NvM uses Crc buffers to store current Crc values to be able to compare against Crcs from NV RAM and/or to add the Crc to data.
              Since this is NvM internal handling, NvM is responsible for correct pointer and array usage.
 \COUNTERMEASURE \N The NvM itself is responsible to initialize and access its internal structures correctly. Correctness is ensured by
                 component tests and code reviews.

\ID SBSW_NvM_AccessPtr_CrcValue
 \DESCRIPTION NvM internal CRC job includes a buffer to store the calculated CRC in. This buffer is always valid after the job was setup successfully
              and the calculated CRC can be store in it.
 \COUNTERMEASURE \T Correct NvM behavior is checked during component tests and code reviews.

\ID SBSW_NvM_AccessArray_InternalCopyData
 \DESCRIPTION In some situations NvM has to copy data from one to another buffer. This is done internally using internal or job specific buffers
              and values as buffer length. Corresponding copy function assumes all parameter are valid and uses them. The caller is responsible
              for providing valid values.
 \COUNTERMEASURE \T Correct NvM behavior is checked during component tests and code reviews.

\ID SBSW_NvM_FuncCall_PtrParam_InternalCopyData
 \DESCRIPTION To copy data NvM invokes the internal copy function with corresponding buffers and values. Before invoking the function it is checked whether
              copy is possible or not. Invoked copy function does not check parameter validity.
 \COUNTERMEASURE \T Correct NvM behavior is checked during component tests and code reviews.

SBSW_JUSTIFICATION_END */

/***********************************************************************************************************************
 *  COVERAGE JUSTIFICATIONS
 **********************************************************************************************************************/
/* COV_JUSTIFICATION_BEGIN

CODE COVERAGE JUSTIFICATIONS

\ID COV_NVM_MISRA
 \ACCEPT TX
 \REASON COV_MSR_MISRA

\ID COV_NVM_COVEREDINOTHERCFG
 \ACCEPT TX
 \ACCEPT TX tx tx
 \ACCEPT TF tf tf xf
 \ACCEPT XF xf xx
 \ACCEPT XX
 \REASON Some configurations do not provide all functionalities required to go through all code branches. But the correctness of the affected code
         is ensured via tests in other configurations, which covers the code completely.

\ID COV_NVM_NOCRCDUMMYHANDLER
 \ACCEPT X
 \REASON All NvM CRC handlers have the same structure: they provide a function to calculate, compare and copy data. For blocks
         without CRC the NvM uses a dummy CRC handler, which simply does nothing, but exists to simplify CRC handling: NvM does not have to
         check whether the block has a CRC each time, the assigned CRC handler does it. The uncovered function...

\ID COV_NVM_KILLWRITEALL
 \ACCEPT TF tf tx
 \ACCEPT TX
 \ACCEPT XF
 \ACCEPT XF tf xf
 \REASON All affected code parts belong to NvM_KillWriteAll handling and are currently not testable (NvM processing is not interruptible on required
         points). There are two not covered situations:
         1. NvM isn't processing any block yet or any more (not started or nearly done NvM_WriteAll)
         2. NvM is processing a block and shall abort directly before or after passing the block to underlying modules

\ID COV_NVM_APICFGCLASS
 \ACCEPT TX tf tx
 \ACCEPT TF tf tx
 \ACCEPT TF tx tf
 \ACCEPT TF xf tf
 \ACCEPT TF tx tf tf
 \ACCEPT XF
 \REASON NvM supports three API configuration classes: 3 includes all functionality, 2 removes some functionality and 1 is the smallest
         NvM functionality with only multi block requests. Because of the missing functionalities it is not possible to cover all
         branches. Also some NvM block configuration does not make sense here - e.g. block without permanent RAM will not be processed
         and are responsible for uncovered code.

\ID COV_NVM_CSM_RETRY_ZERO
 \ACCEPT XF tf xf xf
 \REASON NvM supports a configurable amount of retry mechanisms. It is possible to configure zero retries to have a
         'no-retry' behavior. It is necessary to test the implementation to work with this configuration.
         The actual configuration does not support ReadBlock() and WriteBlock() which would enable to cover the complete
         boolean expression.
         The justified code is ensured to have full coverage in CFG1.

\ID COV_NVM_NO_BLOCK_WITH_CALCRAMBLOCKCRC_CONFIGURED
 \ACCEPT XF xf xx
 \REASON If user configures the combination of API NvM_SetRamBlockStatus is enabled AND no block has the parameter
         NvMCalcRamBlockCrc enabled the query NvM_QryCalcRamBlockCrcEnabledAndRamValid will always give the result FALSE.
         The justified code is fully covered in all test configurations but CFG5. It is designed to have exactly
         the described combination to reach coverage for other code parts. See configuration derivation.

VARIANT COVERAGE JUSTIFICATIONS

\ID COV_NVM_COMPATIBILITY
 \ACCEPT TX
 \REASON COV_MSR_COMPATIBILITY

COV_JUSTIFICATION_END */

/**********************************************************************************************************************
 *  END OF FILE: NvM.c
 *********************************************************************************************************************/
