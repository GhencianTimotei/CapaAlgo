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
/*!        \file  NvM_Crc.c
 *        \brief  NvM CRC submodule source file
 *      \details  This sub-module implements the CRC calculation.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#define NVM_CRC_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
/* NvM_JobProc.h includes all needed headers, e.g. configuration, action, query... */
#include "NvM_JobProc.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#ifndef NVM_CRC32_COMPATIBILITY_MODE
# define NVM_CRC32_COMPATIBILITY_MODE STD_OFF
#endif

/* Dummy handler constants */
#define NVM_NOCRC_INIT_VALUE        0u
#define NVM_NOCRC_BYTE_LENGTH       0u

/* CRC16 handler constants */
#define NVM_CRC16_INIT_VALUE        0xFFFFFFFFu
#define NVM_CRC16_BYTE_LENGTH       2u

/* CRC32 handler constants */
#if (NVM_CRC32_COMPATIBILITY_MODE == STD_ON)
# define NVM_CRC32_XOR_VALUE         0xFFFFFFFFu
# define NVM_CRC32_INIT_VALUE        (0xFFFFFFFFu ^ NVM_CRC32_XOR_VALUE)
#else
# define NVM_CRC32_INIT_VALUE        0xFFFFFFFFu
#endif
#define NVM_CRC32_BYTE_LENGTH       4u

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/
#ifndef NVM_LOCAL                                                                                                       /* COV_NVM_COMPATIBILITY */
# define NVM_LOCAL static
#endif

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define NVM_START_SEC_CODE
#include "MemMap.h"                                                                                                     /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*********************************************************************************************************************
 * NvM_CrcCalculateBuffer
 *********************************************************************************************************************/
/*!\brief       Process CRC calculation for given buffer.
 * \details     Uses given data pointer and length for CRC processing. Takes care of correct CRC API usage.
 * \param[in]   Self      Pointer to CRC job to process.
 * \param[in]   DataPtr   Data to be processed.
 * \param[in]   Length    Length of data to be processed.
 * \pre         CRC job must be created via NvM_CrcJob_Create() first.
 * \context     TASK
 * \reentrant   TRUE
 * \synchronous TRUE
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_CrcCalculateBuffer(
    NvM_CrcJobPtrType Self,
    NvM_ConstRamAddressType DataPtr,
    const uint16 Length);

/**********************************************************************************************************************
 * NvM_Crc_NoCrc_Calculate
 *********************************************************************************************************************/
/*! \brief Do nothing, function is a dummy (blocks without Crc).
 *  \details Do nothing, function is a dummy (blocks without Crc).
 *  \param[in] DataPtr, value not relevant, because dummy function.
 *  \param[in] Length, value not relevant, because dummy function.
 *  \param[in] CurrentValue, value not relevant, because dummy function.
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_Crc_NoCrc_Calculate(
    NvM_ConstRamAddressType DataPtr,
    uint16 Length,
    NvM_CrcValuePtrType CurrentValue,
    boolean IsFirstCall);

/**********************************************************************************************************************
 * NvM_Crc_NoCrc_Compare
 *********************************************************************************************************************/
/*! \brief Do nothing, function is a dummy (blocks without Crc).
 *  \details Do nothing, function is a dummy (blocks without Crc).
 *  \param[in] CrcBuff, value not relevant, because dummy function.
 *  \param[in] CurrentValue, value not relevant, because dummy function.
 *  \return TRUE always
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_Crc_NoCrc_Compare(
    NvM_CrcBufferConstPtrType CrcBuff,
    NvM_CrcValueRefType CurrentValue);

/**********************************************************************************************************************
 * NvM_Crc_NoCrc_CopyToBuffer
 *********************************************************************************************************************/
/*! \brief Do nothing, function is a dummy (blocks without Crc).
 *  \details Do nothing, function is a dummy (blocks without Crc).
 *  \param[in] Dest, value not relevant, because dummy function.
 *  \param[in] Src, value not relevant, because dummy function.
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_Crc_NoCrc_CopyToBuffer(
    NvM_CrcBufferPtrType Dest,
    NvM_CrcValueRefType Src);

#if (NVM_USE_CRC16 == STD_ON)
/**********************************************************************************************************************
 * NvM_Crc_Crc16_Calculate
 *********************************************************************************************************************/
/*! \brief Calculates Crc 16.
 *  \details Invokes the Crc16 calculation function exactly once.
 *  \param[in] DataPtr to calculate the CRC over. Must not be NULL_PTR. Caller has to ensure correctness - has to
 *             match the Length.
 *  \param[in] Length as number of bytes to calculate the CRC. Has to match the DataPtr target length.
 *  \param[in,out] CurrCrc the current CRC value, will be used as CRC start value and overwritten by the new CRC.
 *                 Caller has to ensure correctness, that means length. Must not be NULL_PTR.
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \config at least one block with Crc 16
 *  \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_Crc_Crc16_Calculate(
    NvM_ConstRamAddressType DataPtr,
    uint16 Length,
    NvM_CrcValuePtrType CurrCrc,
    boolean IsFirstCall);

/**********************************************************************************************************************
 * NvM_Crc_Crc16_Compare
 *********************************************************************************************************************/
/*! \brief Compares given (two) Crc16 values.
 *  \details The given Crc values have to be Crc16 - first two bytes will be compared.
 *  \param[in] Crc1 as the first value to be compared. Length must fit at least the CRC length. Must not be NULL_PTR.
 *  \param[in] Crc2 as the second value to be compared. Length must fit at least the CRC length. Must not be NULL_PTR.
 *  \return given Crc values fits: TRUE, otherwise: FALSE
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \config at least one block with Crc 16
 *  \pre -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_Crc_Crc16_Compare(
    NvM_CrcBufferConstPtrType Crc1,
    NvM_CrcValueRefType Crc2);

/**********************************************************************************************************************
 * NvM_Crc_Crc16_CopyToBuffer
 *********************************************************************************************************************/
/*! \brief Copies source Crc16 buffer to the destination Crc16 buffer.
 *  \details The given Crc buffer have to be for Crc16 - that means at least two byte long. The API will copy only
 *           the first two bytes from source to destination
 *  \param[in] Dest to copy to source to. Must not be NULL_PTR. Caller has to ensure correctness.
 *  \param[in] Src to copy to the destination. Must not be NULL_PTR. Caller has to ensure correctness.
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \config at least one block with Crc 16
 *  \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_Crc_Crc16_CopyToBuffer(
    NvM_CrcBufferPtrType Dest,
    NvM_CrcValueRefType Src);
#endif /* (NVM_USE_CRC16 == STD_ON) */

#if (NVM_USE_CRC32 == STD_ON)
/**********************************************************************************************************************
 * NvM_Crc_Crc32_Calculate
 *********************************************************************************************************************/
/*! \brief Calculates Crc 32.
 *  \details Invokes the Crc32 calculation function exactly once.
 *  \param[in] DataPtr to calculate the CRC over. Must not be NULL_PTR. Caller has to ensure correctness - has to
 *             match the Length.
 *  \param[in] Length as number of bytes to calculate the CRC. Has to match the DataPtr target length.
 *  \param[in,out] CurrCrc the current CRC value, will be used as CRC start value and overwritten by the new CRC.
 *                 Caller has to ensure correctness, that means length. Must not be NULL_PTR.
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \config at least one block with Crc 32
 *  \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_Crc_Crc32_Calculate(
    NvM_ConstRamAddressType DataPtr,
    uint16 Length,
    NvM_CrcValuePtrType CurrCrc,
    boolean IsFirstCall);

/**********************************************************************************************************************
 * NvM_Crc_Crc32_Compare
 *********************************************************************************************************************/
/*! \brief Compares given (two) Crc16 values.
 *  \details The given Crc values have to be Crc32 - first four bytes will be compared.
 *  \param[in] Crc1 as the first value to be compared. Length must fit at least the CRC length. Must not be NULL_PTR.
 *  \param[in] Crc2 as the second value to be compared. Length must fit at least the CRC length. Must not be NULL_PTR.
 *  \return given Crc values fits: TRUE, otherwise: FALSE
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \config at least one block with Crc 32
 *  \pre -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_Crc_Crc32_Compare(
    NvM_CrcBufferConstPtrType Crc1,
    NvM_CrcValueRefType Crc2);

/**********************************************************************************************************************
 * NvM_Crc_Crc32_CopyToBuffer
 *********************************************************************************************************************/
/*! \brief Copies source Crc32 buffer to the destination Crc32 buffer.
 *  \details The given Crc buffer have to be for Crc32 - that means at least four byte long. The API will copy only
 *           the first four bytes from source to destination
 *  \param[in] Dest to copy to source to. Must not be NULL_PTR. Caller has to ensure correctness.
 *  \param[in] Src to copy to the destination. Must not be NULL_PTR. Caller has to ensure correctness.
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \config at least one block with Crc 32
 *  \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_Crc_Crc32_CopyToBuffer(
    NvM_CrcBufferPtrType Dest,
    NvM_CrcValueRefType Src);
#endif /* (NVM_USE_CRC32 == STD_ON) */

#if ((NVM_SET_RAM_BLOCK_STATUS_API == STD_ON) && (NVM_CALC_RAM_CRC_USED == STD_ON))
/**********************************************************************************************************************
 * NvM_CrcQueueCountTrailingZeros
 *********************************************************************************************************************/
/*! \brief Removes all lower bits with value 0 from given parameter.
 *  \details Removes all lower bits with value 0 from given parameter.
 *  \param[in] Word the value to count the trailing zero for.
 *  \return given parameter without any lower bits with 0
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(uint8, NVM_PRIVATE_CODE) NvM_CrcQueueCountTrailingZeros(NvM_CrcQueueEntryType Word);
#endif /* ((NVM_SET_RAM_BLOCK_STATUS_API == STD_ON) && (NVM_CALC_RAM_CRC_USED == STD_ON)) */

#define NVM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                     /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/
#define NVM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"                                                                                                     /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* "Dummy" Handler for Disabled CRC -> exists always */
NVM_LOCAL CONST(struct NvM_CrcHandlerClass, NVM_PRIVATE_CONST) NvM_Crc_NoCrcHandler_t =
{
    NvM_Crc_NoCrc_Calculate,
    NvM_Crc_NoCrc_Compare,
    NvM_Crc_NoCrc_CopyToBuffer,
    NVM_NOCRC_INIT_VALUE,
    NVM_NOCRC_BYTE_LENGTH
};

#if (NVM_USE_CRC16 == STD_ON)
/* CRC16 handler, only available if there is at least one NvM block configured with CRC16 */
NVM_LOCAL CONST(struct NvM_CrcHandlerClass, NVM_PRIVATE_CONST) NvM_Crc_Crc16Handler_t =
{
    NvM_Crc_Crc16_Calculate,
    NvM_Crc_Crc16_Compare,
    NvM_Crc_Crc16_CopyToBuffer,
    NVM_CRC16_INIT_VALUE,
    NVM_CRC16_BYTE_LENGTH
};
#else
# define NvM_Crc_Crc16Handler_t NvM_Crc_NoCrcHandler_t
#endif /* (NVM_USE_CRC16 == STD_ON) */

#if (NVM_USE_CRC32 == STD_ON)
/* CRC32 handler, only available if there is at least one NvM block configured with CRC32 */
NVM_LOCAL CONST(struct NvM_CrcHandlerClass, NVM_PRIVATE_CONST) NvM_Crc_Crc32Handler_t =
{
    NvM_Crc_Crc32_Calculate,
    NvM_Crc_Crc32_Compare,
    NvM_Crc_Crc32_CopyToBuffer,
    NVM_CRC32_INIT_VALUE,
    NVM_CRC32_BYTE_LENGTH
};
#else
# define NvM_Crc_Crc32Handler_t NvM_Crc_NoCrcHandler_t
#endif /* (NVM_USE_CRC32 == STD_ON) */

/* CRC handler table including all currently supported and enabled/used CRC type handlers */
NVM_LOCAL CONST(NvM_CrcHandlerClassConstPtr, NVM_PRIVATE_CONST) NvM_CrcHandlerTable_at[4] =                             /* PRQA S 3218 */ /* MD_NvM_8.9_CrcHandlerTable */
{
    &NvM_Crc_NoCrcHandler_t,
    &NvM_Crc_NoCrcHandler_t, /* reserved for CRC8 */
    &NvM_Crc_Crc16Handler_t,
    &NvM_Crc_Crc32Handler_t
};

#define NVM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"                                                                                                     /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* CRC queue will only be available if the SetRamBlockStatus API and NvMCalcRamCrc are enabled. */
#if((NVM_SET_RAM_BLOCK_STATUS_API == STD_ON) && (NVM_CALC_RAM_CRC_USED == STD_ON))

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
/* the size of the CRC job queue in 32bitWords. It is a bit-string, one bit for each block */
# define NVM_SIZE_CRC_JOB_QUEUE ((NVM_TOTAL_NUM_OF_NVRAM_BLOCKS + NVM_CRC_QUEUE_BITINDEX_MASK) >> NVM_CRC_QUEUE_ENTRY_SHIFT)

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/
# define NVM_START_SEC_VAR_NO_INIT_UNSPECIFIED
# include "MemMap.h"                                                                                                     /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Crc job queue (It's just a bit string) */
NVM_LOCAL VAR(NvM_CrcQueueEntryType, NVM_PRIVATE_DATA) NvM_CrcQueue_at[NVM_SIZE_CRC_JOB_QUEUE];
/* current CRC queue position to start scanning at */
NVM_LOCAL VAR(NvM_BlockIdType, NVM_PRIVATE_DATA) NvM_CrcQueueScanStart_u16;

# define NVM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
# include "MemMap.h"                                                                                                     /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
# define NVM_START_SEC_CODE
# include "MemMap.h"                                                                                                     /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
*  NvM_CrcQueueInit
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, NVM_PRIVATE_CODE) NvM_CrcQueueInit(void)
{
    uint16 counter = (NvM_CrcQueueSize_u16 + NVM_CRC_QUEUE_BITINDEX_MASK) >> NVM_CRC_QUEUE_ENTRY_SHIFT;

    do
    {
        --counter;
        NvM_CrcQueue_at[counter] = 0u;                                                                                  /* SBSW_NvM_AccessCrcQueue */
    } while (counter > 0u);

    /* start queue scan with block 1, since block ID 0 is a reserved block, never requesting CRC re-calculation */
    NvM_CrcQueueScanStart_u16 = 1u;
}

/**********************************************************************************************************************
*  NvM_CrcQueueJob
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, NVM_PRIVATE_CODE) NvM_CrcQueueJob(NvM_BlockIdType BlockId)
{
    /* perform calculations outside of Critical section, in order to make it as short as possible */
    const NvM_CrcQueueEntryType bitMask = (((NvM_CrcQueueEntryType)1u) << (BlockId & NVM_CRC_QUEUE_BITINDEX_MASK));
    const NvM_CrcQueueEntryPtr queueEntry = &NvM_CrcQueue_at[BlockId >> NVM_CRC_QUEUE_ENTRY_SHIFT];

    NvM_EnterCriticalSection();

    /* #21 process the actual queuing (set corresponding bit) */
    *queueEntry |= bitMask;                                                                                             /* SBSW_NvM_AccessCrcQueue */

    NvM_ExitCriticalSection();
}

/**********************************************************************************************************************
*  NvM_CrcGetQueuedBlockId
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
FUNC(NvM_BlockIdType, NVM_PRIVATE_CODE) NvM_CrcGetQueuedBlockId(void)
{
    /* #10 Setup required values */

    /* set the block Id whether to begin searching - set in previous search correctly or begin from block Id 1 */
    uint16 newBlockId = (NvM_CrcQueueScanStart_u16 < NvM_CrcQueueSize_u16) ? NvM_CrcQueueScanStart_u16 : 1u;
    /* calculate number of queue elements (each with 32 bits) */
    const uint16 queueSizeWords = (NvM_CrcQueueSize_u16 + NVM_CRC_QUEUE_BITINDEX_MASK) >> NVM_CRC_QUEUE_ENTRY_SHIFT;

    uint8 bitPos = (uint8)(newBlockId & NVM_CRC_QUEUE_BITINDEX_MASK);
    const NvM_CrcQueueEntryType entryMask = ~((((NvM_CrcQueueEntryType)1u) << bitPos) - 1u);

    /* shift out lowest 5 bits to get the queue element with current newBlockId */
    newBlockId >>= NVM_CRC_QUEUE_ENTRY_SHIFT;

    bitPos = NvM_CrcQueueCountTrailingZeros(entryMask & NvM_CrcQueue_at[newBlockId]);

    /* #20 search for queue element which includes at least one set bit (queued block) */

    /* search for queue element with at least one bit != 0 */
    while (bitPos >= NVM_CRC_QUEUE_ENTRY_BITS)
    {
        /* we already checked the first queue element, now check the next one */
        newBlockId++;

        /* Crc queue end reached, abort */
        if (newBlockId >= queueSizeWords)
        {
            NvM_CrcQueueScanStart_u16 = NvM_CrcQueueSize_u16;
            break;
        }

        /* check current queue element for set bits */
        bitPos = NvM_CrcQueueCountTrailingZeros(NvM_CrcQueue_at[newBlockId]);
    }

    /* #30 if an queue element with queued block Id was found */
    if(newBlockId < queueSizeWords)
    {
        NvM_EnterCriticalSection();

        /* clear the Block's corresponding bit, since it was set (and cannot be cleared elsewhere, we can use XOR) */
        NvM_CrcQueue_at[newBlockId] ^= (((NvM_CrcQueueEntryType)1u) << bitPos);                                         /* SBSW_NvM_AccessCrcQueue */

        NvM_ExitCriticalSection();

        /* set newBlockId to first block within queue element */
        newBlockId <<= NVM_CRC_QUEUE_ENTRY_SHIFT;
        /* calculate the real set block Id from newBlockId and the set bit within queue element */
        newBlockId |= bitPos;

        /* update Block Id where to start the next queue scan, wrap around will be handled when starting the next scan */
        NvM_CrcQueueScanStart_u16 = (NvM_BlockIdType)(newBlockId + 1u);
    }
    /* #40 if no queue element with queued block Id was found */
    else
    {
        newBlockId = 0u;
    }

    /* #50 return next block Id to calculate Crc for */
    return (NvM_BlockIdType)newBlockId;
}

/* Count the number of cleared bits after the least significant bit that is set *
 * It works either 32bit or 16bit words (depending on platform)                 */
/**********************************************************************************************************************
*  NvM_CrcQueueCountTrailingZeros
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
NVM_LOCAL FUNC(uint8, NVM_PRIVATE_CODE) NvM_CrcQueueCountTrailingZeros(NvM_CrcQueueEntryType Word)
{
    uint8 trailingZeroes = 0u;

    if(Word == 0u)
    {   /* special condition -> avoid going through the divide and conquer algorithm below.  *
         * => it would require additional handling at the remaining two bits.               */
        trailingZeroes = NVM_CRC_QUEUE_ENTRY_BITS;
    }
    else
    {
        NvM_CrcQueueEntryType currWord = Word;
        /* is none of the lower 16 bits set? */
        if((currWord & 0xFFFFu) == 0u)
        {
            trailingZeroes |= 0x10u;
            currWord >>= 16u;
        }

        /* is none of the lower 8bits set? */
        if((currWord & 0xFFu) == 0u)
        {
            trailingZeroes |= 0x08u;
            currWord >>= 8u;
        }

        /* is none of the lower 4 bits set?*/
        if((currWord & 0x0Fu) == 0u)
        {
            trailingZeroes |= 0x04u;
            currWord >>= 4u;
        }

        /* is none of the lower 2 bits set? */
        if((currWord & 0x03u) == 0u)
        {
            trailingZeroes |= 2u;
            currWord >>= 2u;
        }

        /* Process least significant bit.
        * If the least significant bit is zero, add 1, because the second one cannot be cleared
        * Initially, we checked for word == 0, therefore one of both bits must be set here
        * If LSB is set, add nothing.
        * The cast appears to be unnecessary. However, some Compilers might issue a warning,
        * if uint16_least is 16bit, while QueueBitMask is 32bit width */
        trailingZeroes |= (uint8)((currWord & 1u) ^ 1u);
    }

    return trailingZeroes;
}

# define NVM_STOP_SEC_CODE
# include "MemMap.h"                                                                                                    /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* ((NVM_SET_RAM_BLOCK_STATUS_API == STD_ON) && (NVM_CALC_RAM_CRC_USED == STD_ON)) */

#define NVM_START_SEC_CODE
#include "MemMap.h"                                                                                                     /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
*  NvM_CrcJob_Create
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, NVM_PRIVATE_CODE) NvM_CrcJob_Create(
    NvM_CrcJobPtrType Self,
    NvM_BlockIdType BlockId,
    NvM_RamAddressType RamDataPtr,
    uint16 DataLength)
{
  const NvM_BlockDescrPtrType descr_pt = &(NvM_BlockDescriptorTable_at[NVM_BLOCK_FROM_DCM_ID(BlockId)]);

  Self->HandlerInstance_pt = NvM_CrcHandlerTable_at[descr_pt->CrcSettings];                                             /* SBSW_NvM_AccessCrcJobPtr */
  Self->CurrentCrcValue = Self->HandlerInstance_pt->initialCrcValue;                                                    /* SBSW_NvM_AccessCrcJobPtr */
  Self->RamData_pt = RamDataPtr;                                                                                        /* SBSW_NvM_AccessCrcJobPtr */
  Self->CrcBuffer = (RamDataPtr == NULL_PTR) ? ((NvM_RamAddressType)NULL_PTR) : (&RamDataPtr[DataLength]);              /* SBSW_NvM_AccessCrcJobPtr */
  /* Let an CRC job complete immediately, if there's actually no CRC, or if there are no RAM data. */
  Self->RemainingLength_u16 =                                                                                           /* SBSW_NvM_AccessCrcJobPtr */
      ((Self->HandlerInstance_pt->crcLength > 0u) && (RamDataPtr != NULL_PTR)) ? DataLength : 0u;
  Self->IsFirstCall = TRUE;                                                                                             /* SBSW_NvM_AccessCrcJobPtr */

#if(NVM_USE_BLOCK_ID_CHECK == STD_ON)
  if(descr_pt->CrcSettings != NVM_BLOCK_USE_CRC_OFF)
  {
    /* Always use the origin block Id - otherwise the next origin block read will deliver data for the DCM block Id and the
     * Crc comparison fails. */
    NvM_BlockIdType originBlockId = NVM_BLOCK_FROM_DCM_ID(BlockId);
    NvM_RamMngmtConstPtrToConstType ramMngmtPtr =
        (originBlockId != BlockId) ? (&NvM_DcmBlockMngmt_t) : (&NvM_BlockMngmtArea_at[BlockId]);                        /* COV_NVM_APICFGCLASS */

    uint8 ramData[3];
    ramData[0] = (uint8)(originBlockId >> 8);                                                                           /* SBSW_NvM_AccessArray_BlockIdInCrc */
    ramData[1] = (uint8)originBlockId;                                                                                  /* SBSW_NvM_AccessArray_BlockIdInCrc */
    ramData[2] = (uint8)ramMngmtPtr->NvDataIndex_t;                                                                     /* SBSW_NvM_AccessArray_BlockIdInCrc */

    NvM_CrcCalculateBuffer(Self, ramData, 3);                                                                           /* SBSW_NvM_FuncCall_CrcModule */
  }
#endif
}

/**********************************************************************************************************************
*  NvM_CrcJob_Process
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, NVM_PRIVATE_CODE) NvM_CrcJob_Process(
    NvM_CrcJobPtrType Self,
    uint16 ProcessLength)
{
  if(Self->RemainingLength_u16 > 0u)                                                                                    /* COV_NVM_COVEREDINOTHERCFG */
  {
    const NvM_ConstRamAddressType currRamPtr = Self->RamData_pt;
    uint16 currLength = Self->RemainingLength_u16;

    /* if both value are equal, we would not need to adapt currentLength, but finishJob needs to be set. */
    if(currLength > ProcessLength)
    {
      currLength = ProcessLength;
    }

    Self->RemainingLength_u16 -= currLength;                                                                            /* SBSW_NvM_AccessCrcJobPtr */

    /* set RamAddress for next calculation cycle */
    Self->RamData_pt = &currRamPtr[currLength];                                                                         /* SBSW_NvM_AccessCrcJobPtr */

    NvM_CrcCalculateBuffer(Self, currRamPtr, currLength);                                                               /* SBSW_NvM_FuncCall_CrcModule */
  }
}

/**********************************************************************************************************************
*  NvM_CrcJob_Compare
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(boolean, NVM_PRIVATE_CODE) NvM_CrcJob_Compare(NvM_CrcJobConstPtrType Self)
{
  boolean result = FALSE;

  if(Self->CrcBuffer != NULL_PTR)
  {
    result = (Self->HandlerInstance_pt->compare(Self->CrcBuffer, (NvM_CrcValueRefType)&Self->CurrentCrcValue));         /* SBSW_NvM_FuncPtrCall_CrcHandler */
  }

  return result;
}

/**********************************************************************************************************************
 *  NvM_CrcJob_CompareToExternal
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(boolean, NVM_PRIVATE_CODE) NvM_CrcJob_CompareToExternal(
    NvM_CrcJobConstPtrType Self,
    NvM_CrcBufferConstPtrType ExtBuffer)
{
  return Self->HandlerInstance_pt->compare(ExtBuffer, (NvM_CrcValueRefType)&Self->CurrentCrcValue);                     /* SBSW_NvM_FuncPtrCall_CrcHandler */
}

/**********************************************************************************************************************
*  NvM_CrcJob_CopyToBuffer
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, NVM_PRIVATE_CODE) NvM_CrcJob_CopyToBuffer(NvM_CrcJobConstPtrType Self)
{
  if(Self->CrcBuffer != NULL_PTR)
  {
    Self->HandlerInstance_pt->copyToBuffer(Self->CrcBuffer, (NvM_CrcValueRefType)&Self->CurrentCrcValue);               /* SBSW_NvM_FuncPtrCall_CrcHandler */
  }
}

/**********************************************************************************************************************
*  NvM_CrcJob_ExportBufferedValue
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, NVM_PRIVATE_CODE) NvM_CrcJob_ExportBufferedValue(
    NvM_CrcJobConstPtrType Self,
    NvM_CrcBufferPtrType DestPtr)
{
  if((DestPtr != NULL_PTR) && (Self->CrcBuffer != NULL_PTR))
  {
    Self->HandlerInstance_pt->copyToBuffer(DestPtr, Self->CrcBuffer);                                                   /* SBSW_NvM_FuncPtrCall_CrcHandler */
  }
}

/**********************************************************************************************************************
*  NvM_CrcJob_ImportBufferedValue
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, NVM_PRIVATE_CODE) NvM_CrcJob_ImportBufferedValue(
    NvM_CrcJobConstPtrType Self,
    NvM_CrcBufferConstPtrType SrcPtr)
{
  if((Self->CrcBuffer != NULL_PTR) && (SrcPtr != NULL_PTR))
  {
    Self->HandlerInstance_pt->copyToBuffer(Self->CrcBuffer, SrcPtr);                                                    /* SBSW_NvM_FuncPtrCall_CrcHandler */
  }
}

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
*  NvM_CrcCalculateBuffer
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_CrcCalculateBuffer(
    NvM_CrcJobPtrType Self,
    NvM_ConstRamAddressType DataPtr,
    const uint16 Length)
{
  Self->HandlerInstance_pt->calc(DataPtr, Length, &Self->CurrentCrcValue, Self->IsFirstCall);                           /* SBSW_NvM_FuncPtrCall_CrcHandler */
  Self->IsFirstCall = FALSE;                                                                                            /* SBSW_NvM_AccessCrcJobPtr */
}


/**********************************************************************************************************************
*  NvM_Crc_NoCrc_Calculate
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE)  NvM_Crc_NoCrc_Calculate(                                                        /* COV_NVM_NOCRCDUMMYHANDLER */
    NvM_ConstRamAddressType DataPtr,
    uint16 Length,
    NvM_CrcValuePtrType CurrentValue,                                                                                   /* PRQA S 3673 */ /* MD_NvM_8.13_NoCrcHandler */
    boolean IsFirstCall)
{
  NVM_DUMMY_STATEMENT_CONST(DataPtr);
  NVM_DUMMY_STATEMENT(Length);
  NVM_DUMMY_STATEMENT(CurrentValue);
  NVM_DUMMY_STATEMENT(IsFirstCall);
}

/**********************************************************************************************************************
*  NvM_Crc_NoCrc_Compare
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_Crc_NoCrc_Compare(                                                        /* COV_NVM_NOCRCDUMMYHANDLER */
    NvM_CrcBufferConstPtrType CrcBuff,
    NvM_CrcValueRefType CurrentValue)
{
  NVM_DUMMY_STATEMENT_CONST(CrcBuff);
  NVM_DUMMY_STATEMENT_CONST(CurrentValue);

  return TRUE;
}

/**********************************************************************************************************************
*  NvM_Crc_NoCrc_CopyToBuffer
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_Crc_NoCrc_CopyToBuffer(
    NvM_CrcBufferPtrType Dest,                                                                                          /* PRQA S 3673 */ /* MD_NvM_8.13_NoCrcHandler */
    NvM_CrcValueRefType Src)
{
  NVM_DUMMY_STATEMENT(Dest);
  NVM_DUMMY_STATEMENT_CONST(Src);
}

#if (NVM_USE_CRC16 == STD_ON) /* CRC16 handler, only available if there is at least one NvM block configured with CRC16 */
/**********************************************************************************************************************
*  NvM_Crc_Crc16_Calculate
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE)  NvM_Crc_Crc16_Calculate(
    NvM_ConstRamAddressType DataPtr,
    uint16 Length,
    NvM_CrcValuePtrType CurrCrc,
    boolean IsFirstCall)
{
  /* Cast to uint16 pointer is necessary because of RAM endiannes!
   * Rough example: 0x0A0B0C0D as CurrCrc
   * Little endian: forward 0x0C0D to the CRC library
   * Big endian: forward 0x0A0B to the CRC library.
   * Here we need to ensure the endiannes twice! Get the low significant bytes via a pointer cast
   * - when forwarding the pointed uint16 value to the library (CRC start value),
   * - when assigning the returned uint16 CRC value to the pointed uint16 value (storage of the new CRC value).
   *
   * NvM later on accesses the CRC value via indexes, which works fine. */
  typedef P2VAR(uint16, AUTOMATIC, NVM_CRC_BUFFER_PTR_CLASS) NvM_Crc16PtrType;
  *((NvM_Crc16PtrType)CurrCrc) = Crc_CalculateCRC16(DataPtr, Length, *((NvM_Crc16PtrType)CurrCrc), IsFirstCall);        /* PRQA S 0310 */ /* MD_NvM_8.11_Crc16PtrCast */ /* SBSW_NvM_FuncCall_CrcModule */ /* SBSW_NvM_AccessPtr_CrcValue */
}

/**********************************************************************************************************************
*  NvM_Crc_Crc16_Compare
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_Crc_Crc16_Compare(
    NvM_CrcBufferConstPtrType Crc1,
    NvM_CrcValueRefType Crc2)
{
  return (boolean)((Crc1[0] == Crc2[0]) && (Crc1[1] == Crc2[1]));
}

/**********************************************************************************************************************
*  NvM_Crc_Crc16_CopyToBuffer
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_Crc_Crc16_CopyToBuffer(
    NvM_CrcBufferPtrType Dest,
    NvM_CrcValueRefType Src)
{
  Dest[0] = Src[0];                                                                                                     /* SBSW_NvM_AccessArray_CrcBuffers */
  Dest[1] = Src[1];                                                                                                     /* SBSW_NvM_AccessArray_CrcBuffers */
}
#endif /* (NVM_USE_CRC16 == STD_ON) */

#if (NVM_USE_CRC32 == STD_ON) /* CRC32 handler, only available if there is at least one NvM block configured with CRC32 */
/**********************************************************************************************************************
*  NvM_Crc_Crc32_Calculate
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_Crc_Crc32_Calculate(
    NvM_ConstRamAddressType DataPtr,
    uint16 Length,
    NvM_CrcValuePtrType CurrCrc,
    boolean IsFirstCall)
{
# if (NVM_CRC32_COMPATIBILITY_MODE == STD_ON)
  /* The compatibility mode ensures readability of data written with older NvM versions. It shall be used only in case
     * the NvM data cannot be migrated to the new CRC32 calculation.
     * This implementation does not match the AUTOSAR standard CRC calculation and therefore was fixed (see the
     * preprocessor else statement).
     * Please note: the compatibility mode is only available for a limited time period! */
  NVM_DUMMY_STATEMENT(IsFirstCall);
  *CurrCrc = Crc_CalculateCRC32(DataPtr, Length, (*CurrCrc) ^ NVM_CRC32_XOR_VALUE, FALSE);                              /* SBSW_NvM_FuncCall_CrcModule */ /* SBSW_NvM_AccessPtr_CrcValue */
# else
  *CurrCrc = Crc_CalculateCRC32(DataPtr, Length, (*CurrCrc), IsFirstCall);                                              /* SBSW_NvM_FuncCall_CrcModule */ /* SBSW_NvM_AccessPtr_CrcValue */
# endif
}

/**********************************************************************************************************************
*  NvM_Crc_Crc32_Compare
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_Crc_Crc32_Compare(
    NvM_CrcBufferConstPtrType Crc1,
    NvM_CrcValueRefType Crc2)
{
    return (boolean)((Crc1[0] == Crc2[0]) && (Crc1[1] == Crc2[1]) && (Crc1[2] == Crc2[2]) && (Crc1[3] == Crc2[3]));
}

/**********************************************************************************************************************
*  NvM_Crc_Crc32_CopyToBuffer
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_Crc_Crc32_CopyToBuffer(
    NvM_CrcBufferPtrType Dest,
    NvM_CrcValueRefType Src)
{
    Dest[0] = Src[0];                                                                                                   /* SBSW_NvM_AccessArray_CrcBuffers */
    Dest[1] = Src[1];                                                                                                   /* SBSW_NvM_AccessArray_CrcBuffers */
    Dest[2] = Src[2];                                                                                                   /* SBSW_NvM_AccessArray_CrcBuffers */
    Dest[3] = Src[3];                                                                                                   /* SBSW_NvM_AccessArray_CrcBuffers */
}
#endif /* (NVM_USE_CRC32 == STD_ON) */

#define NVM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                     /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  END OF FILE: NvM_Crc.c
 *********************************************************************************************************************/
