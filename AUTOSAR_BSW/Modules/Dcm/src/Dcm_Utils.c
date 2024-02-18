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
/**        \file  Dcm_Utils.c
 *        \brief  Contains the implementation of Utils unit.
 *
 *      \details  MICROSAR DCM based on AR 4.0.3
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/
#define DCM_UTILS_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Dcm_Utils.h"
#if ((DCM_UTI_NVM_READ_ENABLED == STD_ON) || \
    (DCM_UTI_NVM_WRITE_ENABLED == STD_ON) || \
    (DCM_UTI_NVM_SET_RAM_BLOCK_STATUS_ENABLED == STD_ON))
# include "NvM.h"
#endif

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/
#define Dcm_UtiRuntimeLimiterEnabled()                               (Dcm_UtiGetRuntimeUsageIterations() > 0u)

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/*! Definition of the singleton context type */
struct DCM_UTISINGLETONCONTEXTTYPE_TAG
{
  uint8  RtLmtrCounter;  /*!< Counter of the runtime limiter */
};
typedef struct DCM_UTISINGLETONCONTEXTTYPE_TAG Dcm_UtiSingletonContextType;

/**********************************************************************************************************************
 *  LOCAL FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */
#if (DCM_UTI_NVM_READ_ENABLED  == STD_ON) || \
    (DCM_UTI_NVM_WRITE_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_UtiNvMGetErrorStatus()
 *********************************************************************************************************************/
/*! \brief          Poll the error status from the NvM.
 *  \details        -
 *  \param[in]      blockId    Id of the NvRam block
 *  \return         DCM_E_OK       Operation finished with success.
 *  \return         DCM_E_NOT_OK   Operation finished with failure.
 *  \return         DCM_E_PENDING  Operation needs more time to be accomplished.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \pre            Shall be called only after any NvM read/write operation of the given block is triggered.
 *********************************************************************************************************************/
DCM_LOCAL FUNC(Std_ReturnType, DCM_CODE) Dcm_UtiNvMGetErrorStatus(
  uint16 blockId
  );
#endif
#define DCM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL DATA DECLARATIONS
 *********************************************************************************************************************/
#define DCM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*! Singleton context of Utils unit */
DCM_LOCAL VAR(Dcm_UtiSingletonContextType, DCM_VAR_NOINIT) Dcm_UtiSingletonContext;
#define DCM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */
#if (DCM_UTI_NVM_READ_ENABLED  == STD_ON) || \
    (DCM_UTI_NVM_WRITE_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_UtiNvMGetErrorStatus()
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
 */
DCM_LOCAL FUNC(Std_ReturnType, DCM_CODE) Dcm_UtiNvMGetErrorStatus(
  uint16 blockId
  )
{
  Std_ReturnType lStdResult;
  NvM_RequestResultType nvmStatus;

  /* Get current NvM job status */
  lStdResult = NvM_GetErrorStatus(blockId, &nvmStatus);                                                                                              /* SBSW_DCM_POINTER_FORWARD_STACK */

  if(lStdResult == E_OK)                                                                                                                             /* PRQA S 2991, 2995 */ /* MD_Dcm_ConstExpr, MD_Dcm_ConstExpr */
  {
    /* If NvM operation succeeded: */
    if ((nvmStatus == NVM_REQ_OK) || (nvmStatus == NVM_REQ_RESTORED_FROM_ROM))
    {
      /* Return the result to the callee */
      /* result is already E_OK */
    }
    /* If the NvM needs more time: */
    else if (nvmStatus == NVM_REQ_PENDING)
    {
      /* Notify callee to retry later */
      lStdResult = DCM_E_PENDING;
    }
    else
    {
      lStdResult = E_NOT_OK;
    }
  }
  else
  {
    lStdResult = E_NOT_OK;                                                                                                                           /* PRQA S 2880 */ /* MD_MSR_Unreachable */
  }

  return lStdResult;
}
#endif
#define DCM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */
/**********************************************************************************************************************
 *  Dcm_UtiLookUpUint16()
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
 */
FUNC(sint16_least, DCM_CODE) Dcm_UtiLookUpUint16(
  P2CONST(uint16, AUTOMATIC, DCM_CONST) lookUpTable,
  uint16 value
  )
{
  sint16_least  lResult;
  uint16_least  loIdx;
  uint16_least  hiIdx;
  uint16_least  lPosition;

  /* Initialize look-up: assume nothing will be found */
  lResult = -1;
  loIdx= 1u;
  hiIdx= lookUpTable[0];

  /* If any sub-array exists: */
  while (loIdx <= hiIdx)
  {
    /* Calculate entry position for comparison */
    lPosition = (uint16_least)(loIdx + ((uint16_least)(hiIdx - loIdx) / 2u)); /* avoids overflows on value addition */

    /* If item found: */
    if(lookUpTable[lPosition] == value)
    {
      /* Return valid entry position (compensate offset) */
      lResult = (sint16_least)((sint32_least)lPosition - 1);
      break;
    }
    /* Otherwise - continue searching */

    /* Determine which sub-array shall be taken as a next */
    if (value < lookUpTable[lPosition])
    {
      /* not needed lPosition zero value check, since loIdx >=1 */
      hiIdx = (uint16_least)(lPosition - 1u);
    }
    else
    {
      /* Use upper half of interval */
      loIdx = (uint16_least)(lPosition + 1u);
    }
  }
  /* Otherwise - report nothing found */

  return lResult;
}

/**********************************************************************************************************************
 *  Dcm_UtiGetBitPosition()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(uint8, DCM_CODE) Dcm_UtiGetBitPosition(
  uint32 bitSet
  )
{
  uint8 bitCtr;
  uint32 lBitSet = bitSet;

  /* This API shall be called with a single bit set in the bit-mask */
  Dcm_DebugAssert(Dcm_UtiIsPowerOfTwo(uint32, lBitSet), DCM_SID_INTERNAL, DCM_E_PARAM);                                                              /* COV_DCM_RTM_DEV_DEBUG XF */

  bitCtr = 0u;

  /* The result is zero based -> skip the first bit in the bit-set */
  lBitSet >>= 1u;

  /* Count zero bits in the set until the set bit is reached */
  while (lBitSet != 0u)
  {
    lBitSet >>= 1u;
    ++bitCtr;
  }

  return bitCtr;
}

#if (DCM_UTI_NVM_READ_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_UtiNvMRead()
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
 *
 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_UtiNvMRead(
  Dcm_OpStatusType opStatus,
  Dcm_GenericDcmRamNoInitPtrType data,
  uint16 blockId
  )
{
  Std_ReturnType lStdResult;

  lStdResult = E_OK;

  if (opStatus == DCM_INITIAL)
  {
    /* Initiate NvM read operation */
    lStdResult = NvM_ReadBlock(blockId, data);                                                                                                       /* SBSW_DCM_PARAM_PTR_FORWARD */

    /* If NvM operation accepted: */
    if (lStdResult == E_OK)
    {
      /* Try immediate get status */
    }
    else
    {
      /* Otherwise: NvM request failed; close job */
      lStdResult = E_NOT_OK;
    }
  }
  else
    if (opStatus == DCM_CANCEL)
    {

      /* Try to cancel NvM read; this is all we can do. Operation result is not from importance */
      (void)NvM_CancelJobs(blockId);

      lStdResult = E_NOT_OK;
    }
    else
    {
      /* Shall not be any other then DCM_PENDING (i.e. DCM_FORCE_RCRRP_OK or DCM_FORCE_RCRRP_NOT_OK) */
      Dcm_DebugAssert((opStatus == DCM_PENDING), DCM_SID_INTERNAL, DCM_E_ILLEGAL_STATE);                                                             /* COV_DCM_RTM_DEV_DEBUG XF */
    }

  /* If no error found during NvM request or just next call of this function: */
  if (lStdResult == E_OK)
  {
    /* Gather and return the NvM operation state */
    lStdResult = Dcm_UtiNvMGetErrorStatus(blockId);
  }/* else - result is already E_NOT_OK */

  return lStdResult;
}
#endif

#if (DCM_UTI_NVM_WRITE_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_UtiNvMWrite()
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
 *
 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_UtiNvMWrite(
  Dcm_OpStatusType opStatus,
  Dcm_GenericDcmConstRamNoInitPtrType data,
  uint16 blockId
  )
{
  Std_ReturnType lStdResult;

  lStdResult = E_OK;

  if(opStatus == DCM_INITIAL)
  {
    /* Initiate NvM write operation */
    lStdResult = NvM_WriteBlock(blockId, data);                                                                                                      /* SBSW_DCM_PARAM_PTR_FORWARD */
    /* If NvM operation accepted: */
    if (lStdResult == E_OK)
    {
      /* Try immediate get status */
    }
    else
    {
      /* Otherwise: NvM request failed; close job */
      lStdResult = E_NOT_OK;
    }
  }
  else  if (opStatus == DCM_CANCEL) /* If service is canceled: */
  {
    /* Try to cancel NvM write; this is all we can do. Operation result is not from importance */
    /* Note: It is not a problem to cancel a job which is not ongoing at all */
    (void)NvM_CancelJobs(blockId);

    lStdResult = E_NOT_OK;
  }
  else
  {
    /* Shall not be any other then DCM_PENDING (i.e. DCM_FORCE_RCRRP_OK or DCM_FORCE_RCRRP_NOT_OK) */
    Dcm_DebugAssert((opStatus == DCM_PENDING), DCM_SID_INTERNAL, DCM_E_ILLEGAL_STATE);                                                               /* COV_DCM_RTM_DEV_DEBUG XF */
  }

  /* If no error found during NvM request or just next call of this function: */
  if(lStdResult == E_OK)
  {
    /* Gather and return the NvM operation state */
    lStdResult = Dcm_UtiNvMGetErrorStatus(blockId);
  }/* else - result is already E_NOT_OK */

  return lStdResult;
}
#endif

#if (DCM_UTI_NVM_WRITE_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_UtiNvMSwcDataWrite()
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
 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_UtiNvMSwcDataWrite(
  Dcm_OpStatusType opStatus,
  Dcm_GenericDcmConstRamNoInitPtrType data,
  uint16 blockId
  )
{
  Std_ReturnType lStdResult;

  if(opStatus == DCM_INITIAL)
  {
    /* Lock the access to the blockId for any other NvM client */
    NvM_SetBlockLockStatus(blockId, TRUE);
  }

  /* Perform normal NvM write operation */
  lStdResult = Dcm_UtiNvMWrite(opStatus, data, blockId);                                                                                             /* SBSW_DCM_PARAM_PTR_FORWARD */

  /* If NvM operation failed for any reason */
  if(lStdResult == DCM_E_NOT_OK)
  {
    /* Unlock the access to the current blockId for other clients */
    NvM_SetBlockLockStatus(blockId, FALSE);
  }/* else - DCM_E_PENDING, DCM_E_OK */

  return lStdResult;
}
#endif

#if (DCM_UTI_NVM_SET_RAM_BLOCK_STATUS_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_UtiNvMSetRamBlockStatus()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, DCM_CODE) Dcm_UtiNvMSetRamBlockStatus(                                                                                                    /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  uint16 blockId
  )
{
  (void)NvM_SetRamBlockStatus(blockId, TRUE);                                                                                                        /* PRQA S 4404 */ /* MD_MSR_AutosarBoolean */
}
#endif

/**********************************************************************************************************************
 *  Dcm_UtiLookUpUint8()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(sint16_least, DCM_CODE) Dcm_UtiLookUpUint8(
  Dcm_Uint8ConstDataPtrType lookUpTable,
  uint8 value
  )
{
  sint16_least iter;
  sint16_least lResult = -1;

  for(iter = (sint16_least)lookUpTable[0]; iter>0; --iter)
  {
    if(lookUpTable[iter] == value)
    {
      lResult = (sint16_least)(iter-1);
      break;
    }
  }
  return lResult;
}

/**********************************************************************************************************************
 *  Dcm_UtiConvertToUint16Array()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, DCM_CODE) Dcm_UtiConvertToUint16Array(
  Dcm_ConstReadOnlyMsgType sourcePtr,
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) targetPtr,
  Dcm_MsgLenType targetSize,
  Dcm_EndiannessType targetEndiannes
  )
{
  Dcm_MsgLenType lIndex;

  for(lIndex = 0; lIndex < targetSize; ++lIndex)
  {
    Dcm_ConstReadOnlyMsgType lOffsetPtr = &sourcePtr[lIndex * 2u];

    if(targetEndiannes == DCM_BIG_ENDIAN)
    {
      targetPtr[lIndex] = Dcm_UtiMake16Bit(lOffsetPtr[0], lOffsetPtr[1]);                                                                            /* SBSW_DCM_POINTER_CONVERTTOARRAY */
    }
    else
    {
      targetPtr[lIndex] = Dcm_UtiMake16Bit(lOffsetPtr[1], lOffsetPtr[0]);                                                                            /* SBSW_DCM_POINTER_CONVERTTOARRAY */
    }
  }
}

/**********************************************************************************************************************
 *  Dcm_UtiConvertToUint32Array()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, DCM_CODE) Dcm_UtiConvertToUint32Array(
  Dcm_ConstReadOnlyMsgType sourcePtr,
  P2VAR(uint32, AUTOMATIC, AUTOMATIC) targetPtr,
  Dcm_MsgLenType targetSize,
  Dcm_EndiannessType targetEndiannes
  )
{
  Dcm_MsgLenType lIndex;

  for(lIndex = 0; lIndex < targetSize; ++lIndex)
  {
    Dcm_ConstReadOnlyMsgType lOffsetPtr = &sourcePtr[lIndex * 4u];

    if(targetEndiannes == DCM_BIG_ENDIAN)
    {
      targetPtr[lIndex] = Dcm_UtiMake32Bit(lOffsetPtr[0], lOffsetPtr[1], lOffsetPtr[2], lOffsetPtr[3]);                                              /* SBSW_DCM_POINTER_CONVERTTOARRAY */
    }
    else
    {
      targetPtr[lIndex] = Dcm_UtiMake32Bit(lOffsetPtr[3], lOffsetPtr[2], lOffsetPtr[1], lOffsetPtr[0]);                                              /* SBSW_DCM_POINTER_CONVERTTOARRAY */
    }
  }
}

/**********************************************************************************************************************
 *  Dcm_UtiConvertToFloat32Array()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, DCM_CODE) Dcm_UtiConvertToFloat32Array(
  Dcm_ConstReadOnlyMsgType sourcePtr,
  P2VAR(float32, AUTOMATIC, AUTOMATIC) targetPtr,
  Dcm_MsgLenType targetSize,
  Dcm_EndiannessType targetEndiannes
  )
{
  Dcm_MsgLenType lIndex;

  for(lIndex = 0; lIndex < targetSize; ++lIndex)
  {
    Dcm_UtiFloatConverterType lData;                                                                                                                 /* PRQA S 0759 */ /* MD_Dcm_Rule19.2 */
    Dcm_ConstReadOnlyMsgType  lOffsetPtr = &sourcePtr[lIndex * 4u];

    if(targetEndiannes == DCM_BIG_ENDIAN)
    {
      lData.AsUint32 = Dcm_UtiMake32Bit(lOffsetPtr[0], lOffsetPtr[1], lOffsetPtr[2], lOffsetPtr[3]);
    }
    else
    {
      lData.AsUint32 = Dcm_UtiMake32Bit(lOffsetPtr[3], lOffsetPtr[2], lOffsetPtr[1], lOffsetPtr[0]);
    }

    targetPtr[lIndex] = lData.AsFloat32;                                                                                                             /* SBSW_DCM_POINTER_CONVERTTOARRAY */
  }
}

/**********************************************************************************************************************
 *  Dcm_UtiResetRuntimeLimiter()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, DCM_CODE) Dcm_UtiResetRuntimeLimiter(                                                                                                     /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  void
  )
{
  Dcm_UtiSingletonContext.RtLmtrCounter = Dcm_UtiGetRuntimeUsageIterations();
}

/**********************************************************************************************************************
 *  Dcm_UtiRuntimeLimitReached()
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
 */
FUNC(boolean, DCM_CODE) Dcm_UtiRuntimeLimitReached(
  void
  )
{
  boolean lResult = FALSE;

  if (Dcm_UtiRuntimeLimiterEnabled())                                                                                                                /* PRQA S 2991, 2992, 2995, 2996 */ /* MD_Dcm_ConstExpr */
  {
    --Dcm_UtiSingletonContext.RtLmtrCounter;

    if (Dcm_UtiSingletonContext.RtLmtrCounter == 0u)
    {
      Dcm_UtiResetRuntimeLimiter();
      lResult = TRUE;
    }
  }

  return lResult;
}

/**********************************************************************************************************************
 *  Dcm_UtiLookUpRangeUint16()
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
 */
FUNC(sint16_least, DCM_CODE) Dcm_UtiLookUpRangeUint16(                                                                                               /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  P2CONST(Dcm_UtiU16RangeType, AUTOMATIC, DCM_CONST) lookUpTable,
  uint16 value
  )
{
  sint16_least  lResult;
  uint16_least  loIdx;
  uint16_least  hiIdx;
  uint16_least  lPosition;

  /* Initialize look-up: assume nothing will be found */
  lResult = -1;
  loIdx= 1u;
  hiIdx= lookUpTable[0].First;/* Take one of the borders since both have the same value */

  /* If any sub-array exists: */
  while (loIdx <= hiIdx)
  {
    /* Calculate entry position for comparison */
    lPosition = (uint16_least)(loIdx + ((uint16_least)(hiIdx - loIdx) / 2u)); /* avoids overflows on value addition */

    /* If valid range found:  */
    if( (lookUpTable[lPosition].First <= value)                                                                                                      /* PRQA S 2841 */ /* MD_Dcm_DerefInvalidPointer */
      &&(lookUpTable[lPosition].Second >= value) )                                                                                                   /* PRQA S 2841 */ /* MD_Dcm_DerefInvalidPointer */
    {
      /* Return valid entry position (compensate offset) */
      lResult = (sint16_least)((sint32_least)lPosition - 1);
      break;
    }
    /* Otherwise - continue searching */

    /* Determine which sub-array shall be taken as a next */
    if (value < lookUpTable[lPosition].First)                                                                                                        /* PRQA S 2841 */ /* MD_Dcm_DerefInvalidPointer */
    {
      /* not needed lPosition zero value check, since loIdx >=1 */
      hiIdx = (uint16_least)(lPosition - 1u);
    }
    else
    {
      /* Use upper half of interval */
      loIdx = (uint16_least)(lPosition + 1u);
    }
  }
  /* Otherwise - report nothing found */

  return lResult;
}

/**********************************************************************************************************************
 *  Dcm_UtiMemCopySafe()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, DCM_CODE) Dcm_UtiMemCopySafe(
  Dcm_ConstReadOnlyMsgType sourcePtr,
  Dcm_ConstMsgType targetPtr,
  Dcm_MsgLenType targetPos,
  Dcm_MsgLenType targetSize,
  Dcm_MsgLenType length
  )
{
  DCM_IGNORE_UNREF_PARAM(targetSize);                                                                                                                /* PRQA S 3112 */ /* MD_MSR_DummyStmt */

  /*
   * targetSize and targetPos are in not trusted relation (passed separately) so must be verified for correct relation,
   * so the subtraction can be assumed valid
   */
  if (Dcm_DebugDetectRuntimeError((targetSize < targetPos)                                                                                           /* PRQA S 2992 */ /* MD_Dcm_ConstExpr */
    || ((targetSize - targetPos) < length)))
  {
    Dcm_DebugReportError(DCM_SID_INTERNAL, DCM_E_CRITICAL_ERROR);
  }
  else
  {
    Dcm_UtiMemCopy(sourcePtr, &(targetPtr[targetPos]), length);                                                                                      /* SBSW_DCM_POINTER_MEMCPY_BUFFER */
  }
}

/**********************************************************************************************************************
 *  Dcm_UtiCommitData()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, DCM_CODE) Dcm_UtiCommitData(                                                                                                              /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  Dcm_DiagDataContextPtrType pDataContext,
  Dcm_MsgLenType length
  )
{
  /* All DataContext values must be trusted values since modified only via the dedicated APIs, keeping them consistent. So the comparison is always valid.
   * Otherwise, nothing can help preventing buffer overflows
   * The only not trusted parameter is "length".
   */
  if(Dcm_DebugDetectRuntimeError(pDataContext->AvailLen < length))                                                                                   /* PRQA S 2992 */ /* MD_Dcm_ConstExpr */
  {
    Dcm_DebugReportError(DCM_SID_INTERNAL, DCM_E_CRITICAL_ERROR);
  }
  else
  {
    pDataContext->Usage    += length;                                                                                                                /* SBSW_DCM_POINTER_WRITE_DATA_CONTEXT */
    pDataContext->AvailLen -= length;                                                                                                                /* SBSW_DCM_POINTER_WRITE_DATA_CONTEXT */
  }
}

/**********************************************************************************************************************
 *  Dcm_UtiGetResDataAt()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Dcm_MsgType, DCM_CODE) Dcm_UtiGetResDataAt(                                                                                                     /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  Dcm_ReadOnlyMsgContextPtrType pMsgContext,
  Dcm_DiagBufferIndexType index
  )
{
  Dcm_MsgType pResData;
  if (Dcm_DebugDetectRuntimeError(index >= pMsgContext->resBufSize))                                                                                 /* PRQA S 2992 */ /* MD_Dcm_ConstExpr */
  {
    Dcm_DebugReportError(DCM_SID_INTERNAL, DCM_E_CRITICAL_ERROR);
    pResData = (Dcm_MsgType)&pMsgContext->resData[0];
  }
  else
  {
    pResData = (Dcm_MsgType)&pMsgContext->resData[index];
  }

  return pResData;
}

#if (DCM_MEMMGR_SUPPORT_ENABLED == STD_ON) || \
    (DCM_FBLMGR_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_UtiConvMemoryOpResult()
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
FUNC(Std_ReturnType, DCM_CODE) Dcm_UtiConvMemoryOpResult(                                                                                            /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  Dcm_ReturnReadWriteMemoryType memOpResult,
  Dcm_OpStatusType opStatus,
  P2VAR(boolean, AUTOMATIC, DCM_VAR_NOINIT) unknown,
  Dcm_NegativeResponseCodePtrType ErrorCode
  )
{
  Std_ReturnType lStdResult;

  DCM_IGNORE_UNREF_PARAM(opStatus);                                                                                                                  /* PRQA S 3112 */ /* MD_MSR_DummyStmt */

  *unknown = FALSE;                                                                                                                                  /* SBSW_DCM_PARAM_PTR_WRITE */

  if (opStatus == DCM_CANCEL)
  {
    lStdResult = DCM_E_NOT_OK;
    *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;                                                                                                         /* SBSW_DCM_PARAM_PTR_WRITE */
  }
  else
  {

    switch (memOpResult)
    {
    case DCM_READ_WRITE_RSLT_OK:
      lStdResult = DCM_E_OK;
      break;
    case DCM_READ_WRITE_RSLT_PENDING:
      lStdResult = DCM_E_PENDING;
      break;
    case DCM_READ_WRITE_RSLT_FAILED:
      lStdResult = DCM_E_NOT_OK;
      break;
    case DCM_READ_WRITE_RSLT_FORCE_RCRRP:
      lStdResult = DCM_E_FORCE_RCRRP;
      break;
    default:
      lStdResult = DCM_E_NOT_OK;
      *unknown = TRUE;                                                                                                                               /* SBSW_DCM_PARAM_PTR_WRITE */
      break;
    }
  }

  return lStdResult;
}
#endif

#if (DCM_MEMMGR_SUPPORT_ENABLED == STD_ON) || \
    (DCM_FBLMGR_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_UtiDwordExtract()
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
FUNC(uint32, DCM_CODE) Dcm_UtiDwordExtract(                                                                                                          /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  Dcm_MsgContextPtrType pMsgContext,
  uint8_least numBytes
  )
{
  uint8  lByteValue;
  uint32 lResult = 0;
  uint8_least lNumBytes = numBytes;

  while (lNumBytes != 0u)
  {
    --lNumBytes;
    lResult <<= 8u;
    Dcm_UtiConsumeReqDataAsU8(pMsgContext, &lByteValue);                                                                                             /* SBSW_DCM_COMB_PTR_FORWARD */
    lResult |= lByteValue;
  }

  return lResult;
}

/**********************************************************************************************************************
 *  Dcm_UtiValidateAndGetAlfid()
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
FUNC(Std_ReturnType, DCM_CODE) Dcm_UtiValidateAndGetAlfid(                                                                                           /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_Uint8ConstDataPtrType lookUpTable,
  Dcm_Uint8VarDataPtrType pAlfid,
  Dcm_Uint8VarDataPtrType pBlockLength,
  Dcm_NegativeResponseCodePtrType ErrorCode
  )
{
  Std_ReturnType lStdResult;

  uint8 addrSize;
  uint8 lenSize;

  /* at least one byte for ALFID is available */
  Dcm_UtiConsumeReqDataAsU8(pMsgContext, pAlfid);                                                                                                    /* SBSW_DCM_PARAM_PTR_FORWARD */
  addrSize = Dcm_UtiGetMemBlockAddrSize(*pAlfid);
  lenSize = Dcm_UtiGetMemBlockLenSize(*pAlfid);
  *pBlockLength = (uint8)(addrSize + lenSize); /* (memory address + memory size) */                                                                  /* SBSW_DCM_PARAM_PTR_WRITE */

  if (Dcm_UtiLookUpUint8(lookUpTable, *pAlfid) < 0)                                                                                                  /* SBSW_DCM_POINTER_FORWARD_GLOBAL */
  {
    *ErrorCode = DCM_E_REQUESTOUTOFRANGE;                                                                                                            /* SBSW_DCM_PARAM_PTR_WRITE */
    lStdResult = DCM_E_NOT_OK;
  }
  else
  {
    lStdResult = DCM_E_OK;
  }

  return lStdResult;
}
#endif
#define DCM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  END OF FILE: Dcm_Utils.c
 *********************************************************************************************************************/
