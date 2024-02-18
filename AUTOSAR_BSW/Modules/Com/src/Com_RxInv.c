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
/*!        \file  Com_RxInv.c
 *        \brief  MICROSAR Communication source file
 *
 *      \details  This is the implementation of the MICROSAR Communication module.
 *                The basic software module is based on the AUTOSAR Communication specification.
 *
 *********************************************************************************************************************/

#define COM_RXINV_SOURCE

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
#include "Com_RxInv.h"
#include "Com_Buffers.h"
#include "Com_Notifications.h"
#include "Com_SignalFilterHdlr.h"

/**********************************************************************************************************************
  LOCAL CONSTANT MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
  LOCAL FUNCTION MACROS
**********************************************************************************************************************/
#if !defined (COM_LOCAL_INLINE)
# define COM_LOCAL_INLINE LOCAL_INLINE
#endif

/**********************************************************************************************************************
  LOCAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/

/**********************************************************************************************************************
  LOCAL DATA PROTOTYPES
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/

/**********************************************************************************************************************
  LOCAL FUNCTION PROTOTYPES
**********************************************************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"    /* PRQA S 5087 */        /* MD_MSR_MemMap */

#if (COM_INVEVENTOFRXSIGGRPINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxInv_GrpSigHasInvalidValue
**********************************************************************************************************************/
/*! \brief        This function checks if an invalid value has been assigned to the group signal
    \details      -
    \pre          -
    \param[in]    idxRxAccessInfo Index of group signal
    \param[in]    sduLength  Length of the received Sdu
    \return       Com_RxSigProcessState
    \context      TASK|ISR2
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(Com_RxSigProcessState, COM_CODE) Com_RxInv_GrpSigHasInvalidValue(Com_RxAccessInfoIterType idxRxAccessInfo, PduLengthType sduLength);
#endif

#if (COM_INVEVENTOFRXSIGGRPINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxInv_SigGrpPerfomInvalidAction
**********************************************************************************************************************/
/*! \brief             This function performs the configured invalid action (replace/notify)
    \details           -
    \pre               -
    \param[in]         idxRxSigGrpInfo - Index of RxSigGrpInfo
    \param[in,out]     fctPtrCacheStrctPtr -  Pointer containing all information of function pointer cache (size, location, index)
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_RxInv_SigGrpPerfomInvalidAction(Com_RxSigGrpInfoIterType idxRxSigGrpInfo, P2VAR(FctPtrCacheStrct, AUTOMATIC, COM_APPL_DATA) fctPtrCacheStrctPtr);
#endif

/**********************************************************************************************************************
  LOCAL FUNCTIONS
**********************************************************************************************************************/

#if (COM_INVEVENTOFRXSIGGRPINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxInv_GrpSigHasInvalidValue
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(Com_RxSigProcessState, COM_CODE) Com_RxInv_GrpSigHasInvalidValue(Com_RxAccessInfoIterType idxRxAccessInfo, PduLengthType sduLength)
{
  Com_RxSigProcessState processState = VALID;   /* PRQA S 2981 */ /* MD_MSR_RetVal */

  switch (Com_GetApplTypeOfRxAccessInfo(idxRxAccessInfo))
  {
# if(COM_TMPBUFFERUSEDOFRXACCESSINFO == STD_ON)
#  if (COM_TMPRXSHDBUFFERUINT8 == STD_ON)
    case COM_UINT8_APPLTYPEOFRXACCESSINFO:
    {
      processState = Com_RxInv_Sig_UInt8_EvaluateInvalidValue(idxRxAccessInfo, Com_GetTmpRxShdBufferUInt8(Com_GetTmpBufferIdxOfRxAccessInfo(idxRxAccessInfo)));
      break;
    }
#  endif
#  if (COM_TMPRXSHDBUFFERSINT8 == STD_ON)
    case COM_SINT8_APPLTYPEOFRXACCESSINFO:
    {
      processState = Com_RxInv_Sig_SInt8_EvaluateInvalidValue(idxRxAccessInfo, Com_GetTmpRxShdBufferSInt8(Com_GetTmpBufferIdxOfRxAccessInfo(idxRxAccessInfo)));
      break;
    }
#  endif
#  if (COM_TMPRXSHDBUFFERUINT16 == STD_ON)
    case COM_UINT16_APPLTYPEOFRXACCESSINFO:
    {
      processState = Com_RxInv_Sig_UInt16_EvaluateInvalidValue(idxRxAccessInfo, Com_GetTmpRxShdBufferUInt16(Com_GetTmpBufferIdxOfRxAccessInfo(idxRxAccessInfo)));
      break;
    }
#  endif
#  if (COM_TMPRXSHDBUFFERSINT16 == STD_ON)
    case COM_SINT16_APPLTYPEOFRXACCESSINFO:
    {
      processState = Com_RxInv_Sig_SInt16_EvaluateInvalidValue(idxRxAccessInfo, Com_GetTmpRxShdBufferSInt16(Com_GetTmpBufferIdxOfRxAccessInfo(idxRxAccessInfo)));
      break;
    }
#  endif
#  if (COM_TMPRXSHDBUFFERUINT32 == STD_ON)
    case COM_UINT32_APPLTYPEOFRXACCESSINFO:
    {
      processState = Com_RxInv_Sig_UInt32_EvaluateInvalidValue(idxRxAccessInfo, Com_GetTmpRxShdBufferUInt32(Com_GetTmpBufferIdxOfRxAccessInfo(idxRxAccessInfo)));
      break;
    }
#  endif
#  if (COM_TMPRXSHDBUFFERSINT32 == STD_ON)
    case COM_SINT32_APPLTYPEOFRXACCESSINFO:
    {
      processState = Com_RxInv_Sig_SInt32_EvaluateInvalidValue(idxRxAccessInfo, Com_GetTmpRxShdBufferSInt32(Com_GetTmpBufferIdxOfRxAccessInfo(idxRxAccessInfo)));
      break;
    }
#  endif
#  if (COM_TMPRXSHDBUFFERUINT64 == STD_ON)
    case COM_UINT64_APPLTYPEOFRXACCESSINFO:
    {
      processState = Com_RxInv_Sig_UInt64_EvaluateInvalidValue(idxRxAccessInfo, Com_GetTmpRxShdBufferUInt64(Com_GetTmpBufferIdxOfRxAccessInfo(idxRxAccessInfo)));
      break;
    }
#  endif
#  if (COM_TMPRXSHDBUFFERSINT64 == STD_ON)
    case COM_SINT64_APPLTYPEOFRXACCESSINFO:
    {
      processState = Com_RxInv_Sig_SInt64_EvaluateInvalidValue(idxRxAccessInfo, Com_GetTmpRxShdBufferSInt64(Com_GetTmpBufferIdxOfRxAccessInfo(idxRxAccessInfo)));
      break;
    }
#  endif
#  if (COM_TMPRXSHDBUFFERFLOAT32 == STD_ON)
    case COM_FLOAT32_APPLTYPEOFRXACCESSINFO:
    {
      processState = Com_RxInv_Sig_Float32_EvaluateInvalidValue(idxRxAccessInfo, Com_GetTmpRxShdBufferFloat32(Com_GetTmpBufferIdxOfRxAccessInfo(idxRxAccessInfo)));
      break;
    }
#  endif
#  if (COM_TMPRXSHDBUFFERFLOAT64 == STD_ON)
    case COM_FLOAT64_APPLTYPEOFRXACCESSINFO:
    {
      processState = Com_RxInv_Sig_Float64_EvaluateInvalidValue(idxRxAccessInfo, Com_GetTmpRxShdBufferFloat64(Com_GetTmpBufferIdxOfRxAccessInfo(idxRxAccessInfo)));
      break;
    }
#  endif
# endif
# if ((COM_TMPRXSHDBUFFERARRAYBASEDTMPBUFFERUSEDOFRXACCESSINFO == STD_ON) && (COM_EXISTS_UINT8_N_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_CONSTVALUEARRAYBASEDINVVALUEUSEDOFRXACCESSINFO == STD_ON))
    case COM_UINT8_N_APPLTYPEOFRXACCESSINFO:
    {
      processState = Com_RxInv_Sig_UInt8_N_EvaluateInvalidValue(idxRxAccessInfo, Com_GetAddrTmpRxShdBufferArrayBased(Com_GetTmpRxShdBufferArrayBasedTmpBufferStartIdxOfRxAccessInfo(idxRxAccessInfo))); /* SBSW_COM_VALID_PTR_BY_COMSTACK_01 */
      break;
    }
# endif
# if ((COM_TMPRXSHDBUFFERARRAYBASEDTMPBUFFERUSEDOFRXACCESSINFO == STD_ON) && (COM_RXTPINFOUSEDOFRXPDUINFO == STD_ON) && (COM_EXISTS_UINT8_DYN_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_CONSTVALUEARRAYBASEDINVVALUEUSEDOFRXACCESSINFO == STD_ON))
    case COM_UINT8_DYN_APPLTYPEOFRXACCESSINFO:
    {
      processState = Com_RxInv_Sig_UInt8_Dyn_EvaluateInvalidValue(idxRxAccessInfo, Com_GetAddrTmpRxShdBufferArrayBased(Com_GetTmpRxShdBufferArrayBasedTmpBufferStartIdxOfRxAccessInfo(idxRxAccessInfo)), sduLength);    /* SBSW_COM_VALID_PTR_BY_COMSTACK_01 */
      break;
    }
# endif
    default:   /* COV_COM_MISRA */
      break;
  }

  COM_DUMMY_STATEMENT(idxRxAccessInfo); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(sduLength);       /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  return processState;
}       /* PRQA S 6030, 6050 */ /* MD_MSR_STCYC, MD_MSR_STCAL */
#endif

#if (COM_INVEVENTOFRXSIGGRPINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxInv_SigGrpPerfomInvalidAction
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_RxInv_SigGrpPerfomInvalidAction(Com_RxSigGrpInfoIterType idxRxSigGrpInfo, P2VAR(FctPtrCacheStrct, AUTOMATIC, COM_APPL_DATA) fctPtrCacheStrctPtr)      /* PRQA S 3673 */ /* MD_MSR_Rule8.13 */
{
  /* #10 If the invalid action is notify, cache or call the invalid notification */
# if (COM_RXCBKFUNCPTRINVACKUSEDOFRXSIGGRPINFO == STD_ON)
  if(Com_IsRxCbkFuncPtrInvAckUsedOfRxSigGrpInfo(idxRxSigGrpInfo))       /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    Com_CacheOrCallRxCbkFctPtr((Com_RxCbkFuncPtrIterType) Com_GetRxCbkFuncPtrInvAckIdxOfRxSigGrpInfo(idxRxSigGrpInfo), (PduIdType) Com_GetRxPduInfoIdxOfRxSigGrpInfo(idxRxSigGrpInfo), fctPtrCacheStrctPtr);    /* SBSW_COM_FCTPTR_CACHE_PTR */
  }
  /* #20 Otherwise, iterate over all related ComGroupSignals and perform replace action. */
  else
# endif
  {
    Com_RxAccessInfoIterType rxAccessInfoIndidx = Com_GetRxAccessInfoGrpSigIndStartIdxOfRxSigGrpInfo(idxRxSigGrpInfo);
    for(; rxAccessInfoIndidx < Com_GetRxAccessInfoGrpSigIndEndIdxOfRxSigGrpInfo(idxRxSigGrpInfo); rxAccessInfoIndidx++)
    {
      Com_RxAccessInfoIterType idxRxAccessInfo = Com_GetRxAccessInfoGrpSigInd(rxAccessInfoIndidx);
# if ((COM_INITVALUEUSEDOFRXACCESSINFO == STD_ON) && (COM_SHDBUFFERUSEDOFRXACCESSINFO == STD_ON))
      if(Com_IsInitValueUsedOfRxAccessInfo(idxRxAccessInfo) && Com_IsShdBufferUsedOfRxAccessInfo(idxRxAccessInfo))      /* COV_COM_PERFORMINVALIDACTION_GROUPSIGNAL */
      {
        Com_Signal_SetRxSigBufferValue(idxRxAccessInfo, Com_GetShdBufferIdxOfRxAccessInfo(idxRxAccessInfo), Com_GetInitValueIdxOfRxAccessInfo(idxRxAccessInfo));
      }
# endif
# if ((COM_CONSTVALUEARRAYBASEDINITVALUEUSEDOFRXACCESSINFO == STD_ON) && (COM_RXSIGBUFFERARRAYBASEDSHDBUFFERUSEDOFRXACCESSINFO == STD_ON))
      if(Com_IsConstValueArrayBasedInitValueUsedOfRxAccessInfo(idxRxAccessInfo) && Com_IsRxSigBufferArrayBasedShdBufferUsedOfRxAccessInfo(idxRxAccessInfo))     /* COV_COM_PERFORMINVALIDACTION_ARRAYBASED_GROUPSIGNAL */
      {
        Com_Signal_SetRxSigBufferArrayBasedValue(idxRxAccessInfo, Com_GetRxSigBufferArrayBasedShdBufferStartIdxOfRxAccessInfo(idxRxAccessInfo),
                                                 Com_GetConstValueArrayBasedInitValueStartIdxOfRxAccessInfo(idxRxAccessInfo),
                                                 (PduLengthType) Com_GetConstValueArrayBasedInitValueLengthOfRxAccessInfo(idxRxAccessInfo));
      }
# endif


    }
    COM_DUMMY_STATEMENT(fctPtrCacheStrctPtr);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  }
}
#endif


/**********************************************************************************************************************
  GLOBAL FUNCTIONS
**********************************************************************************************************************/

#if ((COM_INVVALUEUSEDOFRXACCESSINFO == STD_ON) && (COM_EXISTS_UINT8_APPLTYPEOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
  Com_RxInv_Sig_UInt8_EvaluateInvalidValue
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(Com_RxSigProcessState, COM_CODE) Com_RxInv_Sig_UInt8_EvaluateInvalidValue(Com_RxAccessInfoIterType idxRxAccessInfo, uint8 tmpNewValue)
{
  Com_RxSigProcessState processState = VALID;   /* PRQA S 2981 */ /* MD_MSR_RetVal */

  if(Com_IsInvValueUsedOfRxAccessInfo(idxRxAccessInfo)) /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    if(tmpNewValue == Com_GetConstValueUInt8(Com_GetInvValueIdxOfRxAccessInfo(idxRxAccessInfo)))
    {
      processState = INVALID;
    }
  }
  return processState;
}
#endif

#if ((COM_INVVALUEUSEDOFRXACCESSINFO == STD_ON) && (COM_EXISTS_SINT8_APPLTYPEOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
  Com_RxInv_Sig_SInt8_EvaluateInvalidValue
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(Com_RxSigProcessState, COM_CODE) Com_RxInv_Sig_SInt8_EvaluateInvalidValue(Com_RxAccessInfoIterType idxRxAccessInfo, sint8 tmpNewValue)
{
  Com_RxSigProcessState processState = VALID;   /* PRQA S 2981 */ /* MD_MSR_RetVal */

  if(Com_IsInvValueUsedOfRxAccessInfo(idxRxAccessInfo)) /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    if(tmpNewValue == Com_GetConstValueSInt8(Com_GetInvValueIdxOfRxAccessInfo(idxRxAccessInfo)))
    {
      processState = INVALID;
    }
  }
  return processState;
}
#endif

#if ((COM_INVVALUEUSEDOFRXACCESSINFO == STD_ON) && (COM_EXISTS_UINT16_APPLTYPEOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
  Com_RxInv_Sig_UInt16_EvaluateInvalidValue
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(Com_RxSigProcessState, COM_CODE) Com_RxInv_Sig_UInt16_EvaluateInvalidValue(Com_RxAccessInfoIterType idxRxAccessInfo, uint16 tmpNewValue)
{
  Com_RxSigProcessState processState = VALID;   /* PRQA S 2981 */ /* MD_MSR_RetVal */

  if(Com_IsInvValueUsedOfRxAccessInfo(idxRxAccessInfo)) /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    if(tmpNewValue == Com_GetConstValueUInt16(Com_GetInvValueIdxOfRxAccessInfo(idxRxAccessInfo)))
    {
      processState = INVALID;
    }
  }
  return processState;
}
#endif

#if ((COM_INVVALUEUSEDOFRXACCESSINFO == STD_ON) && (COM_EXISTS_SINT16_APPLTYPEOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
  Com_RxInv_Sig_SInt16_EvaluateInvalidValue
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(Com_RxSigProcessState, COM_CODE) Com_RxInv_Sig_SInt16_EvaluateInvalidValue(Com_RxAccessInfoIterType idxRxAccessInfo, sint16 tmpNewValue)
{
  Com_RxSigProcessState processState = VALID;   /* PRQA S 2981 */ /* MD_MSR_RetVal */

  if(Com_IsInvValueUsedOfRxAccessInfo(idxRxAccessInfo)) /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    if(tmpNewValue == Com_GetConstValueSInt16(Com_GetInvValueIdxOfRxAccessInfo(idxRxAccessInfo)))
    {
      processState = INVALID;
    }
  }
  return processState;
}
#endif

#if ((COM_INVVALUEUSEDOFRXACCESSINFO == STD_ON) && (COM_EXISTS_UINT32_APPLTYPEOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
  Com_RxInv_Sig_UInt32_EvaluateInvalidValue
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(Com_RxSigProcessState, COM_CODE) Com_RxInv_Sig_UInt32_EvaluateInvalidValue(Com_RxAccessInfoIterType idxRxAccessInfo, uint32 tmpNewValue)
{
  Com_RxSigProcessState processState = VALID;   /* PRQA S 2981 */ /* MD_MSR_RetVal */

  if(Com_IsInvValueUsedOfRxAccessInfo(idxRxAccessInfo)) /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    if(tmpNewValue == Com_GetConstValueUInt32(Com_GetInvValueIdxOfRxAccessInfo(idxRxAccessInfo)))
    {
      processState = INVALID;
    }
  }
  return processState;
}
#endif

#if ((COM_INVVALUEUSEDOFRXACCESSINFO == STD_ON) && (COM_EXISTS_SINT32_APPLTYPEOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
  Com_RxInv_Sig_SInt32_EvaluateInvalidValue
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(Com_RxSigProcessState, COM_CODE) Com_RxInv_Sig_SInt32_EvaluateInvalidValue(Com_RxAccessInfoIterType idxRxAccessInfo, sint32 tmpNewValue)
{
  Com_RxSigProcessState processState = VALID;   /* PRQA S 2981 */ /* MD_MSR_RetVal */

  if(Com_IsInvValueUsedOfRxAccessInfo(idxRxAccessInfo)) /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    if(tmpNewValue == Com_GetConstValueSInt32(Com_GetInvValueIdxOfRxAccessInfo(idxRxAccessInfo)))
    {
      processState = INVALID;
    }
  }
  return processState;
}
#endif

#if ((COM_INVVALUEUSEDOFRXACCESSINFO == STD_ON) && (COM_EXISTS_UINT64_APPLTYPEOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
  Com_RxInv_Sig_UInt64_EvaluateInvalidValue
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(Com_RxSigProcessState, COM_CODE) Com_RxInv_Sig_UInt64_EvaluateInvalidValue(Com_RxAccessInfoIterType idxRxAccessInfo, uint64 tmpNewValue)
{
  Com_RxSigProcessState processState = VALID;   /* PRQA S 2981 */ /* MD_MSR_RetVal */

  if(Com_IsInvValueUsedOfRxAccessInfo(idxRxAccessInfo)) /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    if(tmpNewValue == Com_GetConstValueUInt64(Com_GetInvValueIdxOfRxAccessInfo(idxRxAccessInfo)))
    {
      processState = INVALID;
    }
  }
  return processState;
}
#endif

#if ((COM_INVVALUEUSEDOFRXACCESSINFO == STD_ON) && (COM_EXISTS_SINT64_APPLTYPEOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
  Com_RxInv_Sig_SInt64_EvaluateInvalidValue
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(Com_RxSigProcessState, COM_CODE) Com_RxInv_Sig_SInt64_EvaluateInvalidValue(Com_RxAccessInfoIterType idxRxAccessInfo, sint64 tmpNewValue)
{
  Com_RxSigProcessState processState = VALID;   /* PRQA S 2981 */ /* MD_MSR_RetVal */

  if(Com_IsInvValueUsedOfRxAccessInfo(idxRxAccessInfo)) /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    if(tmpNewValue == Com_GetConstValueSInt64(Com_GetInvValueIdxOfRxAccessInfo(idxRxAccessInfo)))
    {
      processState = INVALID;
    }
  }
  return processState;
}
#endif

#if ((COM_INVVALUEUSEDOFRXACCESSINFO == STD_ON) && (COM_EXISTS_FLOAT32_APPLTYPEOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
  Com_RxInv_Sig_Float32_EvaluateInvalidValue
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(Com_RxSigProcessState, COM_CODE) Com_RxInv_Sig_Float32_EvaluateInvalidValue(Com_RxAccessInfoIterType idxRxAccessInfo, float32 tmpNewValue)
{
  Com_RxSigProcessState processState = VALID;   /* PRQA S 2981 */ /* MD_MSR_RetVal */

  if(Com_IsInvValueUsedOfRxAccessInfo(idxRxAccessInfo)) /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    if(Com_CompareFloat32Values(tmpNewValue, Com_GetConstValueFloat32(Com_GetInvValueIdxOfRxAccessInfo(idxRxAccessInfo))) == TRUE)
    {
      processState = INVALID;
    }
  }
  return processState;
}
#endif

#if ((COM_INVVALUEUSEDOFRXACCESSINFO == STD_ON) && (COM_EXISTS_FLOAT64_APPLTYPEOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
  Com_RxInv_Sig_Float64_EvaluateInvalidValue
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(Com_RxSigProcessState, COM_CODE) Com_RxInv_Sig_Float64_EvaluateInvalidValue(Com_RxAccessInfoIterType idxRxAccessInfo, float64 tmpNewValue)
{
  Com_RxSigProcessState processState = VALID;   /* PRQA S 2981 */ /* MD_MSR_RetVal */

  if(Com_IsInvValueUsedOfRxAccessInfo(idxRxAccessInfo)) /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    if(Com_CompareFloat64Values(tmpNewValue, Com_GetConstValueFloat64(Com_GetInvValueIdxOfRxAccessInfo(idxRxAccessInfo))) == TRUE)
    {
      processState = INVALID;
    }
  }
  return processState;
}
#endif

#if ((COM_CONSTVALUEARRAYBASEDINVVALUEUSEDOFRXACCESSINFO == STD_ON) && (COM_EXISTS_UINT8_N_APPLTYPEOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
  Com_RxInv_Sig_UInt8_N_EvaluateInvalidValue
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(Com_RxSigProcessState, COM_CODE) Com_RxInv_Sig_UInt8_N_EvaluateInvalidValue(Com_RxAccessInfoIterType idxRxAccessInfo, P2CONST(uint8, AUTOMATIC, AUTOMATIC) newValue)
{
  Com_ConstValueArrayBasedIterType bufferIdx = 0;
  Com_RxSigProcessState processState = VALID;   /* PRQA S 2981 */ /* MD_MSR_RetVal */
  /* #10 Iterate over all buffer parts and evaluate if they are all invalid */
  if(Com_IsConstValueArrayBasedInvValueUsedOfRxAccessInfo(idxRxAccessInfo))     /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    processState = INVALID;
    for(; bufferIdx < Com_GetConstValueArrayBasedInvValueLengthOfRxAccessInfo(idxRxAccessInfo); bufferIdx++)
    {
      if(newValue[bufferIdx] != Com_GetConstValueArrayBased(bufferIdx + Com_GetConstValueArrayBasedInvValueStartIdxOfRxAccessInfo(idxRxAccessInfo)))
      {
        processState = VALID;
        break;
      }
    }
  }
  return processState;
}
#endif

#if ((COM_RXTPINFOUSEDOFRXPDUINFO == STD_ON) && (COM_CONSTVALUEARRAYBASEDINVVALUEUSEDOFRXACCESSINFO == STD_ON) && (COM_EXISTS_UINT8_DYN_APPLTYPEOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
  Com_RxInv_Sig_UInt8_Dyn_EvaluateInvalidValue
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(Com_RxSigProcessState, COM_CODE) Com_RxInv_Sig_UInt8_Dyn_EvaluateInvalidValue(Com_RxAccessInfoIterType idxRxAccessInfo, P2CONST(uint8, AUTOMATIC, AUTOMATIC) newValue, PduLengthType sduLength)
{
  Com_ConstValueArrayBasedIterType bufferIdx = 0;
  Com_RxSigProcessState processState = VALID;   /* PRQA S 2981 */ /* MD_MSR_RetVal */

  if(Com_IsConstValueArrayBasedInvValueUsedOfRxAccessInfo(idxRxAccessInfo))     /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    if(Com_GetRxDynamicLength(sduLength, idxRxAccessInfo) == Com_GetConstValueArrayBasedInvValueLengthOfRxAccessInfo(idxRxAccessInfo))
    {
      processState = INVALID;
      for(; bufferIdx < Com_GetConstValueArrayBasedInvValueLengthOfRxAccessInfo(idxRxAccessInfo); bufferIdx++)
      {
        if(newValue[bufferIdx] != Com_GetConstValueArrayBased(bufferIdx + Com_GetConstValueArrayBasedInvValueStartIdxOfRxAccessInfo(idxRxAccessInfo)))
        {
          processState = VALID;
          break;
        }
      }
    }
  }

  return processState;
}
#endif

#if (COM_INVEVENTOFRXSIGGRPINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxInv_SigGrp
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(Com_RxSigProcessState, COM_CODE) Com_RxInv_SigGrp(Com_RxSigGrpInfoIterType idxRxSigGrpInfo, P2VAR(FctPtrCacheStrct, AUTOMATIC, COM_APPL_DATA) fctPtrCacheStrctPtr, PduLengthType sduLength)
{
  Com_RxSigProcessState processState = VALID;   /* PRQA S 2981 */ /* MD_MSR_RetVal */
  /* #10 If the passed ComSignalGroup has any invalid action configured */
  if(Com_IsInvEventOfRxSigGrpInfo(idxRxSigGrpInfo))
  {
    {
      /* #20 Iterate over all related ComGroupSignals and evaluate whether the current shadow buffer value contains an invalid value */
      Com_RxAccessInfoIterType rxAccessInfoIndidx = Com_GetRxAccessInfoGrpSigIndStartIdxOfRxSigGrpInfo(idxRxSigGrpInfo);
      for(; rxAccessInfoIndidx < Com_GetRxAccessInfoGrpSigIndEndIdxOfRxSigGrpInfo(idxRxSigGrpInfo); rxAccessInfoIndidx++)
      {
        processState = Com_RxInv_GrpSigHasInvalidValue(Com_GetRxAccessInfoGrpSigInd(rxAccessInfoIndidx), sduLength);
        if(processState == INVALID)
        {
          /* #30 If any ComGroupSignal has an invalid value in its shadow buffer, perform the invalid action */
          Com_RxInv_SigGrpPerfomInvalidAction(idxRxSigGrpInfo, fctPtrCacheStrctPtr);    /* SBSW_COM_FCTPTR_CACHE_PTR */
          break;
        }
      }
    }
  }

  return processState;
}
#endif

#if (((COM_INVVALUEUSEDOFRXACCESSINFO == STD_ON) || (COM_CONSTVALUEARRAYBASEDINVVALUEUSEDOFRXACCESSINFO == STD_ON)) && (COM_RXSIGINFO == STD_ON))
/**********************************************************************************************************************
  Com_RxInv_Sig_PerformInvalidAction
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_RxInv_Sig_PerformInvalidAction(Com_RxSigInfoIterType idxRxSigInfo      /* COV_COM_PERFORMINVALIDACTION_X */
                                                        , P2VAR(FctPtrCacheStrct, AUTOMATIC, COM_APPL_DATA) fctPtrCacheStrctPtr)        /* PRQA S 3673 */ /* MD_MSR_Rule8.13 */
{
  /* #10 If an invalid notification is configured cache or call it, otherwise replace the current value with the initial value */
  Com_RxAccessInfoIdxOfRxSigInfoType idxRxAccessInfo = Com_GetRxAccessInfoIdxOfRxSigInfo(idxRxSigInfo);
# if (COM_RXCBKFUNCPTRINVACKUSEDOFRXSIGINFO == STD_ON)
  if(Com_IsRxCbkFuncPtrInvAckUsedOfRxSigInfo(idxRxSigInfo))     /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    Com_CacheOrCallRxCbkFctPtr((Com_RxCbkFuncPtrIterType) Com_GetRxCbkFuncPtrInvAckIdxOfRxSigInfo(idxRxSigInfo), (PduIdType) Com_GetRxPduInfoIdxOfRxAccessInfo(idxRxAccessInfo), fctPtrCacheStrctPtr);  /* SBSW_COM_FCTPTR_CACHE_PTR */
  }
  else
# endif
  {
# if ((COM_INITVALUEUSEDOFRXACCESSINFO == STD_ON) && (COM_BUFFERUSEDOFRXACCESSINFO == STD_ON))
    if(Com_IsInitValueUsedOfRxAccessInfo(idxRxAccessInfo) && Com_IsBufferUsedOfRxAccessInfo(idxRxAccessInfo))   /* COV_COM_PERFORMINVALIDACTION */
    {
      Com_Signal_SetRxSigBufferValue(idxRxAccessInfo, Com_GetBufferIdxOfRxAccessInfo(idxRxAccessInfo), Com_GetInitValueIdxOfRxAccessInfo(idxRxAccessInfo));
    }
# endif
# if ((COM_CONSTVALUEARRAYBASEDINITVALUEUSEDOFRXACCESSINFO == STD_ON) && (COM_RXSIGBUFFERARRAYBASEDBUFFERUSEDOFRXACCESSINFO == STD_ON))
    if(Com_IsConstValueArrayBasedInitValueUsedOfRxAccessInfo(idxRxAccessInfo) && Com_IsRxSigBufferArrayBasedBufferUsedOfRxAccessInfo(idxRxAccessInfo))  /* COV_COM_PERFORMINVALIDACTION_ARRAYBASED */
    {
      Com_Signal_SetRxSigBufferArrayBasedValue(idxRxAccessInfo, Com_GetRxSigBufferArrayBasedBufferStartIdxOfRxAccessInfo(idxRxAccessInfo),
                                               Com_GetConstValueArrayBasedInitValueStartIdxOfRxAccessInfo(idxRxAccessInfo),
                                               (PduLengthType) Com_GetConstValueArrayBasedInitValueLengthOfRxAccessInfo(idxRxAccessInfo));
    }
# endif


    COM_DUMMY_STATEMENT(fctPtrCacheStrctPtr);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  }
}
#endif

#define COM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */   /* MD_MSR_MemMap */

/***********************************************************************************************************************
 *  MISRA JUSTIFICATIONS
 **********************************************************************************************************************/
/* *INDENT-OFF* */
/* Justifications for module-specific MISRA deviations:

*/

/***********************************************************************************************************************
 *  SILENTBSW JUSTIFICATIONS
 **********************************************************************************************************************/
/* SBSW_JUSTIFICATION_BEGIN

SBSW_JUSTIFICATION_END */

/***********************************************************************************************************************
 *  COVERAGE JUSTIFICATIONS
 **********************************************************************************************************************/
/* START_COVERAGE_JUSTIFICATION

END_COVERAGE_JUSTIFICATION */
/* *INDENT-ON* */

/**********************************************************************************************************************
 *  END OF FILE: Com_RxInv.c
 *********************************************************************************************************************/
