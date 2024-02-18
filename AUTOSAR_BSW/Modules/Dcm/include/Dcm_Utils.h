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
/**        \file  Dcm_Utils.h
 *        \brief  Contains public inline function definitions of Utils unit.
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
#if !defined(DCM_UTILS_H)
# define DCM_UTILS_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Dcm_UtilsInt.h"
# include "Dcm_Debug.h"

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION DECLARATIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA DECLARATIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
# define DCM_START_SEC_CODE
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */
# if !defined(DCM_NOUNIT_SWITCHES)                                                                                                                   /* COV_DCM_NOUNIT TX */
/***********************************************************************************************************************
 *  Dcm_UtiGetRuntimeUsageIterations()
 ***********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(uint8, DCM_CODE) Dcm_UtiGetRuntimeUsageIterations(                                                                            /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  void
  )
{
  return DCM_RUNTIME_USAGE_ITERATIONS;
}
# endif

# if !defined(DCM_NOUNIT_UTILS)                                                                                                                      /* COV_DCM_NOUNIT TX */
/**********************************************************************************************************************
 *  Dcm_UtiBitSetGetRowIdxSafe()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(uint16_least, DCM_CODE) Dcm_UtiBitSetGetRowIdxSafe(                                                                           /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  uint16_least bitsetPosition,
  uint16_least bitsetSize,
  uint8_least bitsetBaseTypeSize
  )
{
  uint16_least rowIndex;

  DCM_IGNORE_UNREF_PARAM(bitsetSize);                                                                                                                /* PRQA S 3112 */ /* MD_MSR_DummyStmt */

  rowIndex = (uint16_least)(bitsetPosition / bitsetBaseTypeSize);
  if (Dcm_DebugDetectRuntimeError(rowIndex >= bitsetSize))                                                                                           /* PRQA S 2992 */ /* MD_Dcm_ConstExpr */
  {
    /* requested bit position is behind bitset */
    Dcm_DebugReportError(DCM_SID_INTERNAL, DCM_E_CRITICAL_ERROR);
    rowIndex = 0;
  }
  return rowIndex;
}

/**********************************************************************************************************************
 *  Dcm_UtiHandleApplNrc()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiHandleApplNrc(                                                                                         /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  Std_ReturnType StdResultAppl,
  Dcm_NegativeResponseCodePtrType ErrorCodeAppl,
  Dcm_NegativeResponseCodeType DefaultNrc
  )
{
  if( ( StdResultAppl == DCM_E_NOT_OK)
    &&(*ErrorCodeAppl == DCM_E_POSITIVERESPONSE) )
  {
    *ErrorCodeAppl = DefaultNrc;                                                                                                                     /* SBSW_DCM_PARAM_PTR_WRITE */
    Dcm_DebugReportError(DCM_SID_INTERNAL, DCM_E_PARAM);
  }
}

/**********************************************************************************************************************
 *  Dcm_UtiSetReqDataAsU8At()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiSetReqDataAsU8At(                                                                                      /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  Dcm_MsgContextPtrType pMsgContext,                                                                                                                 /* PRQA S 3673 */ /* MD_Dcm_Design_3673 */
  Dcm_DiagBufferIndexType index,
  uint8 value
  )
{
  if (Dcm_DebugDetectRuntimeError(index >= pMsgContext->reqBufSize))                                                                                 /* PRQA S 2992 */ /* MD_Dcm_ConstExpr */
  {
    Dcm_DebugReportError(DCM_SID_INTERNAL, DCM_E_CRITICAL_ERROR);
  }
  else
  {
    pMsgContext->reqData[index] = value;                                                                                                             /* SBSW_DCM_POINTER_WRITE_MESSAGE_CONTEXT_REQBUFFER */
  }
}

/**********************************************************************************************************************
 *  Dcm_UtiSetReqDataAsU8()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiSetReqDataAsU8(                                                                                        /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  Dcm_MsgContextPtrType pMsgContext,
  uint8 value
  )
{
  Dcm_UtiSetReqDataAsU8At(pMsgContext, pMsgContext->reqIndex, value);                                                                                /* SBSW_DCM_PARAM_PTR_FORWARD */
}

/**********************************************************************************************************************
 *  Dcm_UtiSetResDataAsU8At()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiSetResDataAsU8At(
  Dcm_MsgContextPtrType pMsgContext,                                                                                                                 /* PRQA S 3673 */ /* MD_Dcm_Design_3673 */
  Dcm_DiagBufferIndexType index,
  uint8 value
  )
{
  if (Dcm_DebugDetectRuntimeError(index >= pMsgContext->resBufSize))                                                                                 /* PRQA S 2992 */ /* MD_Dcm_ConstExpr */
  {
    Dcm_DebugReportError(DCM_SID_INTERNAL, DCM_E_CRITICAL_ERROR);
  }
  else
  {
    pMsgContext->resData[index] = value;                                                                                                             /* SBSW_DCM_POINTER_WRITE_MESSAGE_CONTEXT_RESBUFFER */
  }
}

/**********************************************************************************************************************
 *  Dcm_UtiSetResDataAsU8Rel()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiSetResDataAsU8Rel(                                                                                     /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_DiagBufferIndexType index,
  uint8 value
  )
{
  Dcm_UtiSetResDataAsU8At(pMsgContext, pMsgContext->resIndex + index, value);                                                                        /* SBSW_DCM_PARAM_PTR_FORWARD */
}

/**********************************************************************************************************************
 *  Dcm_UtiSetResDataAsU32()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiSetResDataAsU32(                                                                                       /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  Dcm_MsgContextPtrType pMsgContext,
  uint32 value
  )
{
  Dcm_UtiSetResDataAsU8Rel(pMsgContext, 0u, Dcm_UtiGetHiHiByte(value));                                                                              /* SBSW_DCM_PARAM_PTR_FORWARD */
  Dcm_UtiSetResDataAsU8Rel(pMsgContext, 1u, Dcm_UtiGetHiLoByte(value));                                                                              /* SBSW_DCM_PARAM_PTR_FORWARD */
  Dcm_UtiSetResDataAsU8Rel(pMsgContext, 2u, Dcm_UtiGetLoHiByte(value));                                                                              /* SBSW_DCM_PARAM_PTR_FORWARD */
  Dcm_UtiSetResDataAsU8Rel(pMsgContext, 3u, Dcm_UtiGetLoLoByte(value));                                                                              /* SBSW_DCM_PARAM_PTR_FORWARD */
}

/**********************************************************************************************************************
 *  Dcm_UtiSetResDataAsUN()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiSetResDataAsUN(                                                                                        /* COV_DCM_UNSUPPORTED X */
  Dcm_MsgContextPtrType pMsgContext,                                                                                                                 /* PRQA S 3673 */ /* MD_Dcm_Design_3673 */
  Dcm_ConstReadOnlyMsgType pSource,
  Dcm_MsgLenType size
  )
{
  Dcm_UtiMemCopySafe(pSource, pMsgContext->resData, pMsgContext->resIndex, pMsgContext->resBufSize, size);                                           /* SBSW_DCM_PARAM_PTR_FORWARD */
}

/**********************************************************************************************************************
 *  Dcm_UtiUpdateResLength()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiUpdateResLength(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_MsgLenType numBytes
  )
{
  /* pMsgContext->resMaxDataLen = pDataContext->resBufferSize - pDataContext->resIndex and is a trusted value.
   * All MsgContext values must be trusted values since modified only via the dedicated APIs, keeping them consistent. So the comparison is always valid.
   * Otherwise, nothing can help preventing buffer overflows
   * The only not trusted parameter is "numBytes".
   */
  if(Dcm_DebugDetectRuntimeError(pMsgContext->resMaxDataLen < numBytes))                                                                             /* PRQA S 2992 */ /* MD_Dcm_ConstExpr */
  {
    Dcm_DebugReportError(DCM_SID_INTERNAL, DCM_E_CRITICAL_ERROR);
  }
  else
  {
    pMsgContext->resDataLen += numBytes;                                                                                                             /* SBSW_DCM_PARAM_PTR_WRITE */
    pMsgContext->resMaxDataLen -= numBytes;                                                                                                          /* SBSW_DCM_PARAM_PTR_WRITE */
  }
}

/**********************************************************************************************************************
 *  Dcm_UtiProvideResData()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiProvideResData(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_MsgLenType numBytes
  )
{
  /* pMsgContext->resMaxDataLen = pDataContext->resBufferSize - pDataContext->resIndex and is a trusted value.
   * All MsgContext values must be trusted values since modified only via the dedicated APIs, keeping them consistent. So the comparison is always valid.
   * Otherwise, nothing can help preventing buffer overflows
   * The only not trusted parameter is "numBytes".
   */
  if(Dcm_DebugDetectRuntimeError(pMsgContext->resMaxDataLen < numBytes))                                                                             /* PRQA S 2992 */ /* MD_Dcm_ConstExpr */
  {
    Dcm_DebugReportError(DCM_SID_INTERNAL, DCM_E_CRITICAL_ERROR);
  }
  else
  {
    pMsgContext->resIndex += numBytes;                                                                                                               /* SBSW_DCM_PARAM_PTR_WRITE */
    Dcm_UtiUpdateResLength(pMsgContext, numBytes);                                                                                                   /* SBSW_DCM_PARAM_PTR_FORWARD */
  }
}

/**********************************************************************************************************************
 *  Dcm_UtiProvideResDataAsU8()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiProvideResDataAsU8(                                                                                    /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  Dcm_MsgContextPtrType pMsgContext,
  uint8 value
  )
{
  Dcm_UtiSetResDataAsU8At(pMsgContext, pMsgContext->resIndex, value);                                                                                /* SBSW_DCM_PARAM_PTR_FORWARD */
  Dcm_UtiProvideResData(pMsgContext, 1u);                                                                                                            /* SBSW_DCM_PARAM_PTR_FORWARD */
}

/**********************************************************************************************************************
 *  Dcm_UtiProvideResDataAsU16()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiProvideResDataAsU16(                                                                                   /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  Dcm_MsgContextPtrType pMsgContext,
  uint16 value
  )
{
  Dcm_UtiSetResDataAsU8At(pMsgContext,  pMsgContext->resIndex,       Dcm_UtiGetHiByte(value));                                                       /* SBSW_DCM_PARAM_PTR_FORWARD */
  Dcm_UtiSetResDataAsU8At(pMsgContext, (pMsgContext->resIndex + 1u), Dcm_UtiGetLoByte(value));                                                       /* SBSW_DCM_PARAM_PTR_FORWARD */
  Dcm_UtiProvideResData(pMsgContext, 2u);                                                                                                            /* SBSW_DCM_PARAM_PTR_FORWARD */
}

/**********************************************************************************************************************
 *  Dcm_UtiProvideResDataAsU24()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiProvideResDataAsU24(                                                                                   /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  Dcm_MsgContextPtrType pMsgContext,
  uint32 value
  )
{
  Dcm_UtiSetResDataAsU8At(pMsgContext,  pMsgContext->resIndex,       Dcm_UtiGetHiLoByte(value));                                                     /* SBSW_DCM_PARAM_PTR_FORWARD */
  Dcm_UtiSetResDataAsU8At(pMsgContext, (pMsgContext->resIndex + 1u), Dcm_UtiGetLoHiByte(value));                                                     /* SBSW_DCM_PARAM_PTR_FORWARD */
  Dcm_UtiSetResDataAsU8At(pMsgContext, (pMsgContext->resIndex + 2u), Dcm_UtiGetLoLoByte(value));                                                     /* SBSW_DCM_PARAM_PTR_FORWARD */
  Dcm_UtiProvideResData(pMsgContext, 3u);                                                                                                            /* SBSW_DCM_PARAM_PTR_FORWARD */
}

/**********************************************************************************************************************
 *  Dcm_UtiProvideResDataAsU32()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiProvideResDataAsU32(                                                                                   /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  Dcm_MsgContextPtrType pMsgContext,
  uint32 value
  )
{
  Dcm_UtiSetResDataAsU8At(pMsgContext,  pMsgContext->resIndex,       Dcm_UtiGetHiHiByte(value));                                                     /* SBSW_DCM_PARAM_PTR_FORWARD */
  Dcm_UtiSetResDataAsU8At(pMsgContext, (pMsgContext->resIndex + 1u), Dcm_UtiGetHiLoByte(value));                                                     /* SBSW_DCM_PARAM_PTR_FORWARD */
  Dcm_UtiSetResDataAsU8At(pMsgContext, (pMsgContext->resIndex + 2u), Dcm_UtiGetLoHiByte(value));                                                     /* SBSW_DCM_PARAM_PTR_FORWARD */
  Dcm_UtiSetResDataAsU8At(pMsgContext, (pMsgContext->resIndex + 3u), Dcm_UtiGetLoLoByte(value));                                                     /* SBSW_DCM_PARAM_PTR_FORWARD */
  Dcm_UtiProvideResData(pMsgContext, 4u);                                                                                                            /* SBSW_DCM_PARAM_PTR_FORWARD */
}

/**********************************************************************************************************************
 *  Dcm_UtiProvideResDataAsUN()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiProvideResDataAsUN(                                                                                    /* PRQA S 3219 */ /* MD_MSR_Unreachable */ /* COV_DCM_UNSUPPORTED X */
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_ConstReadOnlyMsgType pSource,
  Dcm_MsgLenType size
  )
{
  Dcm_UtiSetResDataAsUN(pMsgContext, pSource, size);                                                                                                 /* SBSW_DCM_PARAM_PTR_FORWARD */
  Dcm_UtiProvideResData(pMsgContext, size);                                                                                                          /* SBSW_DCM_PARAM_PTR_FORWARD */
}

/**********************************************************************************************************************
 *  Dcm_UtiGetRemainingResLenWithOffset()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(Dcm_MsgLenType, DCM_CODE) Dcm_UtiGetRemainingResLenWithOffset(                                                                /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  Dcm_ReadOnlyMsgContextPtrType pMsgContext,
  Dcm_MsgLenType offset
  )
{
  Dcm_MsgLenType lResMaxLen;

  if (Dcm_DebugDetectRuntimeError(offset > pMsgContext->resMaxDataLen))                                                                              /* PRQA S 2992 */ /* MD_Dcm_ConstExpr */
  {
    Dcm_DebugReportError(DCM_SID_INTERNAL, DCM_E_CRITICAL_ERROR);
    lResMaxLen = 0;
  }
  else
  {
    lResMaxLen = pMsgContext->resMaxDataLen - offset;
  }

  return lResMaxLen;
}

/**********************************************************************************************************************
 *  Dcm_UtiConsumeReqData()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiConsumeReqData(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_MsgLenType numBytes
  )
{
  pMsgContext->reqIndex += (Dcm_DiagBufferIndexType)numBytes;                                                                                        /* SBSW_DCM_PARAM_PTR_WRITE */
  Dcm_UtiUpdateReqLength(pMsgContext, numBytes);                                                                                                     /* SBSW_DCM_PARAM_PTR_WRITE */
}

/**********************************************************************************************************************
 *  Dcm_UtiConsumeReqDataAsU8()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiConsumeReqDataAsU8(                                                                                    /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  Dcm_MsgContextPtrType pMsgContext,
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) pValue
  )
{
  *pValue = Dcm_UtiGetReqDataAsU8(pMsgContext);                                                                                                      /* SBSW_DCM_PARAM_PTR_WRITE */ /* PRQA S 2985 */ /* MD_Dcm_Redundant_2985 */
  Dcm_UtiConsumeReqData(pMsgContext, 1);                                                                                                             /* SBSW_DCM_PARAM_PTR_FORWARD */
}

/**********************************************************************************************************************
 *  Dcm_UtiConsumeReqDataAsU16()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiConsumeReqDataAsU16(                                                                                   /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  Dcm_MsgContextPtrType pMsgContext,
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) pValue
  )
{
  *pValue = Dcm_UtiGetReqDataAsU16(pMsgContext);                                                                                                     /* SBSW_DCM_PARAM_PTR_WRITE */ /* PRQA S 2985 */ /* MD_Dcm_Redundant_2985 */
  Dcm_UtiConsumeReqData(pMsgContext, 2);                                                                                                             /* SBSW_DCM_PARAM_PTR_FORWARD */
}

/**********************************************************************************************************************
 *  Dcm_UtiConsumeReqDataAsU24()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiConsumeReqDataAsU24(                                                                                   /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  Dcm_MsgContextPtrType pMsgContext,
  P2VAR(uint32, AUTOMATIC, AUTOMATIC) pValue
  )
{
  *pValue = Dcm_UtiGetReqDataAsU24(pMsgContext);                                                                                                     /* SBSW_DCM_PARAM_PTR_WRITE */ /* PRQA S 2985, 2986 */ /* MD_Dcm_Redundant_2986, MD_Dcm_Redundant_2986 */
  Dcm_UtiConsumeReqData(pMsgContext, 3);                                                                                                             /* SBSW_DCM_PARAM_PTR_FORWARD */
}

/**********************************************************************************************************************
 *  Dcm_UtiConsumeReqDataAsUN()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiConsumeReqDataAsUN(                                                                                    /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  Dcm_MsgContextPtrType pMsgContext,
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) pTarget,
  Dcm_MsgLenType sizeOfTargetBuffer,
  Dcm_MsgLenType numBytes
  )
{
  Dcm_UtiMemCopySafe(Dcm_UtiGetReqData(pMsgContext), pTarget, 0u, sizeOfTargetBuffer, numBytes);                                                     /* SBSW_DCM_PARAM_PTR_FORWARD */ /* PRQA S 2985 */ /* MD_Dcm_Redundant_2985 */

  Dcm_UtiConsumeReqData(pMsgContext, numBytes);                                                                                                      /* SBSW_DCM_PARAM_PTR_FORWARD */
}

/**********************************************************************************************************************
 *  Dcm_UtiMsgContextVerifySize()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_UtiMsgContextVerifySize(                                                                        /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  Dcm_ReadOnlyMsgContextPtrType pMsgContext,
  Dcm_MsgLenType numBytes,
  Dcm_NegativeResponseCodePtrType ErrorCode
  )
{
  Std_ReturnType lResult;

  if(Dcm_DebugDetectRuntimeError(numBytes > pMsgContext->resMaxDataLen))                                                                             /* PRQA S 2992 */ /* MD_Dcm_ConstExpr */
  {
    Dcm_DebugReportError(DCM_SID_INTERNAL, DCM_E_CRITICAL_ERROR);

    *ErrorCode = DCM_E_PANIC_NRC;                                                                                                                    /* SBSW_DCM_PARAM_PTR_WRITE */
    lResult = DCM_E_NOT_OK;
  }
  else
  {
    lResult = DCM_E_OK;
  }

  return lResult;
}

/**********************************************************************************************************************
 *  Dcm_UtiInitDataContext()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiInitDataContext(                                                                                       /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  Dcm_DiagDataContextPtrType pDataContext,
  Dcm_MsgType Buffer,
  Dcm_MsgLenType BufferSize
  )
{
  pDataContext->Buffer   = Buffer;                                                                                                                   /* SBSW_DCM_POINTER_WRITE_DATA_CONTEXT */
  pDataContext->Size     = BufferSize;                                                                                                               /* SBSW_DCM_POINTER_WRITE_DATA_CONTEXT */
  pDataContext->Usage    = 0;                                                                                                                        /* SBSW_DCM_POINTER_WRITE_DATA_CONTEXT */
  pDataContext->AvailLen = BufferSize;                                                                                                               /* SBSW_DCM_POINTER_WRITE_DATA_CONTEXT */
}

/**********************************************************************************************************************
 *  Dcm_UtiDataContextSetAvailLen()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiDataContextSetAvailLen(                                                                                /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  Dcm_DiagDataContextPtrType pDataContext,
  Dcm_MsgLenType length
  )
{
  /* No overflow check needed since usage will always be smaller than size.
   * The utilities for data context handling enforce this.
   */
  if(Dcm_DebugDetectRuntimeError((Dcm_MsgLenType)(pDataContext->Size - pDataContext->Usage) < length))                                               /* PRQA S 2992 */ /* MD_Dcm_ConstExpr */
  {
    Dcm_DebugReportError(DCM_SID_INTERNAL, DCM_E_CRITICAL_ERROR);
  }
  else
  {
    pDataContext->AvailLen = length;                                                                                                                 /* SBSW_DCM_POINTER_WRITE_DATA_CONTEXT */
  }
}

/**********************************************************************************************************************
 *  Dcm_UtiDataContextCheckSize()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(boolean, DCM_CODE) Dcm_UtiDataContextCheckSize(                                                                               /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  Dcm_DiagDataContextConstPtrType pDataContext,
  Dcm_MsgLenType size
  )
{
  boolean lResult = TRUE;

  if((Dcm_MsgLenType)(pDataContext->Size - pDataContext->Usage) < size)
  {
    lResult = FALSE;
  }

  return lResult;
}

/**********************************************************************************************************************
 *  Dcm_UtiDataContextVerifySize()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_UtiDataContextVerifySize(                                                                       /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  Dcm_DiagDataContextConstPtrType pDataContext,
  Dcm_MsgLenType size,
  Dcm_NegativeResponseCodePtrType ErrorCode
  )
{
  Std_ReturnType lResult;

  if(Dcm_DebugDetectRuntimeError(Dcm_UtiDataContextCheckSize(pDataContext, size) == FALSE))                                                          /* PRQA S 2992 */ /* MD_Dcm_ConstExpr */ /* SBSW_DCM_PARAM_PTR_FORWARD */
  {
    Dcm_DebugReportError(DCM_SID_INTERNAL, DCM_E_CRITICAL_ERROR);

    *ErrorCode = DCM_E_PANIC_NRC;                                                                                                                    /* SBSW_DCM_PARAM_PTR_WRITE */
    lResult = DCM_E_NOT_OK;
  }
  else
  {
    lResult = DCM_E_OK;
  }

  return lResult;
}

/**********************************************************************************************************************
 *  Dcm_UtiRevertData()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiRevertData(                                                                                            /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  Dcm_DiagDataContextPtrType pDataContext,
  Dcm_MsgLenType length
  )
{
  /* All DataContext values must be trusted values since modified only via the dedicated APIs, keeping them consistent. So the comparison is always valid.
   * Otherwise, nothing can help preventing buffer overflows
   * The only not trusted parameter is "length".
   */
  if(Dcm_DebugDetectRuntimeError(pDataContext->Usage < length))                                                                                      /* PRQA S 2992 */ /* MD_Dcm_ConstExpr */
  {
    Dcm_DebugReportError(DCM_SID_INTERNAL, DCM_E_CRITICAL_ERROR);
  }
  else
  {
    pDataContext->Usage    -= length;                                                                                                                /* SBSW_DCM_POINTER_WRITE_DATA_CONTEXT */
    pDataContext->AvailLen += length;                                                                                                                /* SBSW_DCM_POINTER_WRITE_DATA_CONTEXT */
  }
}

/**********************************************************************************************************************
 *  Dcm_UtiGetDataContextBuffer()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(Dcm_MsgType, DCM_CODE) Dcm_UtiGetDataContextBuffer(                                                                           /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  Dcm_DiagDataContextPtrType pDataContext                                                                                                            /* PRQA S 3673 */ /* MD_Dcm_Design_3673 */
  )
{
  return &pDataContext->Buffer[pDataContext->Usage];
}

/**********************************************************************************************************************
 *  Dcm_UtiSetDataAsU8At()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiSetDataAsU8At(
  Dcm_DiagDataContextPtrType pDataContext,                                                                                                           /* PRQA S 3673 */ /* MD_Dcm_Design_3673 */
  Dcm_MsgLenType index,
  uint8 value
  )
{
  if (Dcm_DebugDetectRuntimeError(pDataContext->Size <= index))                                                                                      /* PRQA S 2992 */ /* MD_Dcm_ConstExpr */
  {
    Dcm_DebugReportError(DCM_SID_INTERNAL, DCM_E_CRITICAL_ERROR);
  }
  else
  {
    pDataContext->Buffer[index] = value;                                                                                                             /* SBSW_DCM_POINTER_WRITE_DATA_CONTEXT */
  }
}

/**********************************************************************************************************************
 *  Dcm_UtiSetDataAsU8Rel()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiSetDataAsU8Rel(                                                                                        /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  Dcm_DiagDataContextPtrType pDataContext,
  Dcm_MsgLenType index,
  uint8 value
  )
{
  Dcm_UtiSetDataAsU8At(pDataContext, pDataContext->Usage + index, value);                                                                            /* SBSW_DCM_PARAM_PTR_FORWARD */
}

/**********************************************************************************************************************
 *  Dcm_UtiProvideDataAsU8()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiProvideDataAsU8(                                                                                       /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  Dcm_DiagDataContextPtrType pDataContext,
  uint8 value
  )
{
  if(Dcm_DebugDetectRuntimeError(pDataContext->AvailLen < 1u))                                                                                       /* PRQA S 2992 */ /* MD_Dcm_ConstExpr */
  {
    Dcm_DebugReportError(DCM_SID_INTERNAL, DCM_E_CRITICAL_ERROR);
  }
  else
  {
    pDataContext->Buffer[pDataContext->Usage] = value;                                                                                               /* SBSW_DCM_POINTER_WRITE_DATA_CONTEXT */
    Dcm_UtiCommitData(pDataContext, 1u);                                                                                                             /* SBSW_DCM_PARAM_PTR_FORWARD */
  }
}

/**********************************************************************************************************************
 *  Dcm_UtiProvideDataAsU16()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiProvideDataAsU16(                                                                                      /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  Dcm_DiagDataContextPtrType pDataContext,
  uint16 value
  )
{
  Dcm_UtiProvideDataAsU8(pDataContext, Dcm_UtiGetHiByte(value));                                                                                     /* SBSW_DCM_PARAM_PTR_FORWARD */
  Dcm_UtiProvideDataAsU8(pDataContext, Dcm_UtiGetLoByte(value));                                                                                     /* SBSW_DCM_PARAM_PTR_FORWARD */
}

/**********************************************************************************************************************
 *  Dcm_UtiProvideDataAsU24()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiProvideDataAsU24(                                                                                      /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  Dcm_DiagDataContextPtrType pDataContext,
  uint32 value
  )
{
  Dcm_UtiProvideDataAsU8(pDataContext, Dcm_UtiGetHiLoByte(value));                                                                                   /* SBSW_DCM_PARAM_PTR_FORWARD */
  Dcm_UtiProvideDataAsU8(pDataContext, Dcm_UtiGetLoHiByte(value));                                                                                   /* SBSW_DCM_PARAM_PTR_FORWARD */
  Dcm_UtiProvideDataAsU8(pDataContext, Dcm_UtiGetLoLoByte(value));                                                                                   /* SBSW_DCM_PARAM_PTR_FORWARD */
}

/**********************************************************************************************************************
 *  Dcm_UtiProvideDataAsU32()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiProvideDataAsU32(                                                                                      /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  Dcm_DiagDataContextPtrType pDataContext,
  uint32 value
  )
{
  Dcm_UtiProvideDataAsU16(pDataContext, Dcm_UtiGetHiWord(value));                                                                                    /* SBSW_DCM_PARAM_PTR_FORWARD */
  Dcm_UtiProvideDataAsU16(pDataContext, Dcm_UtiGetLoWord(value));                                                                                    /* SBSW_DCM_PARAM_PTR_FORWARD */
}

/**********************************************************************************************************************
 *  Dcm_UtiProvideDataAsF32()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiProvideDataAsF32(                                                                                      /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  Dcm_DiagDataContextPtrType pDataContext,
  float32 value,
  Dcm_EndiannessType endianness
  )
{
  Dcm_UtiFloatConverterType lData;                                                                                                                   /* PRQA S 0759 */ /* MD_Dcm_Rule19.2 */

  lData.AsFloat32 = value;

  if(endianness == DCM_BIG_ENDIAN)
  {
    Dcm_UtiProvideDataAsU8(pDataContext, Dcm_UtiGetHiHiByte(lData.AsUint32));                                                                        /* SBSW_DCM_PARAM_PTR_FORWARD */
    Dcm_UtiProvideDataAsU8(pDataContext, Dcm_UtiGetHiLoByte(lData.AsUint32));                                                                        /* SBSW_DCM_PARAM_PTR_FORWARD */
    Dcm_UtiProvideDataAsU8(pDataContext, Dcm_UtiGetLoHiByte(lData.AsUint32));                                                                        /* SBSW_DCM_PARAM_PTR_FORWARD */
    Dcm_UtiProvideDataAsU8(pDataContext, Dcm_UtiGetLoLoByte(lData.AsUint32));                                                                        /* SBSW_DCM_PARAM_PTR_FORWARD */
  }
  else
  {
    Dcm_UtiProvideDataAsU8(pDataContext, Dcm_UtiGetLoLoByte(lData.AsUint32));                                                                        /* SBSW_DCM_PARAM_PTR_FORWARD */
    Dcm_UtiProvideDataAsU8(pDataContext, Dcm_UtiGetLoHiByte(lData.AsUint32));                                                                        /* SBSW_DCM_PARAM_PTR_FORWARD */
    Dcm_UtiProvideDataAsU8(pDataContext, Dcm_UtiGetHiLoByte(lData.AsUint32));                                                                        /* SBSW_DCM_PARAM_PTR_FORWARD */
    Dcm_UtiProvideDataAsU8(pDataContext, Dcm_UtiGetHiHiByte(lData.AsUint32));                                                                        /* SBSW_DCM_PARAM_PTR_FORWARD */
  }
}

/**********************************************************************************************************************
 *  Dcm_UtiProvideDataAsUN()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiProvideDataAsUN(                                                                                       /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  Dcm_DiagDataContextPtrType pDataContext,
  Dcm_ConstReadOnlyMsgType pSource,
  Dcm_MsgLenType length
  )
{
  Dcm_UtiMemCopySafe(pSource, pDataContext->Buffer, pDataContext->Usage, pDataContext->Size, length);                                                /* SBSW_DCM_PARAM_PTR_FORWARD */

  Dcm_UtiCommitData(pDataContext, length);                                                                                                           /* SBSW_DCM_PARAM_PTR_FORWARD */
}
# endif /* !defined(DCM_NOUNIT_UTILS) */
# define DCM_STOP_SEC_CODE
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* !defined(DCM_UTILS_H) */

/**********************************************************************************************************************
 *  END OF FILE: Dcm_Utils.h
 *********************************************************************************************************************/
