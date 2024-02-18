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
/*!        \file  Com_Buffers.c
 *        \brief  MICROSAR Communication source file
 *
 *      \details  This is the implementation of the MICROSAR Communication module.
 *                The basic software module is based on the AUTOSAR Communication specification.
 *
 *********************************************************************************************************************/

#define COM_BUFFERS_SOURCE

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
#include "Com_Buffers.h"
#include "Com_RxProcessing.h"
#include "vstdlib.h"

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

/**********************************************************************************************************************
  LOCAL FUNCTIONS
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL FUNCTIONS
**********************************************************************************************************************/

#if (COM_TXBUFFERUSEDOFTXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_TxBuffer_InitTxIpdu
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxBuffer_InitTxIpdu(Com_TxPduInfoIterType ComPduId)
{
  /* #10 Copy the initial values to the Tx ComIPdu buffer */
  if(Com_IsTxBufferUsedOfTxPduInfo(ComPduId))   /* COV_COM_TX_BUFFER_ALWAYS_USED */
  {
    VStdMemCpyRomToRam(Com_GetAddrTxBuffer(Com_GetTxBufferStartIdxOfTxPduInfo(ComPduId)), Com_GetAddrTxPduInitValue(Com_GetTxPduInitValueStartIdxOfTxPduInfo(ComPduId)), Com_GetTxBufferLengthOfTxPduInfo(ComPduId));   /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_COM_MEM_CPY_2RAM */
  }
# if  (COM_TXBUFFERMETADATAUSEDOFTXPDUINFO == STD_ON)
  if(Com_IsTxBufferMetaDataUsedOfTxPduInfo(ComPduId))
  {
    /* #20 Copy the meta data init values to the Tx ComIPdu buffer */
    VStdMemCpyRomToRam(Com_GetAddrTxBuffer(Com_GetTxBufferMetaDataStartIdxOfTxPduInfo(ComPduId)), Com_GetAddrTxPduInitValue(Com_GetTxPduInitValueMetaDataStartIdxOfTxPduInfo(ComPduId)), Com_GetTxBufferMetaDataLengthOfTxPduInfo(ComPduId));   /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_COM_MEM_CPY_2RAM */
  }
# endif
}
#endif

#if (COM_CONSTVALUEUINT8UBCLEARMASKENDIDXOFTXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_TxBuffer_ClearUpdateBits
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxBuffer_ClearUpdateBits(PduIdType ComTxPduId)
{
  Com_TxBufferIterType txBufferIdx = Com_GetTxBufferStartIdxOfTxPduInfo(ComTxPduId);

  /* #10 If the passed Tx ComIPdu has a pdu buffer, clear all related UpdateBits in that buffer */
  Com_ConstValueUInt8UbClearMaskEndIdxOfTxPduInfoType idxConstValueUInt8 = Com_GetConstValueUInt8UbClearMaskStartIdxOfTxPduInfo(ComTxPduId);
  for(; idxConstValueUInt8 < Com_GetConstValueUInt8UbClearMaskEndIdxOfTxPduInfo(ComTxPduId); idxConstValueUInt8++)
  {
    Com_SetTxBuffer(txBufferIdx, Com_GetTxBuffer(txBufferIdx) & Com_GetConstValueUInt8(idxConstValueUInt8));    /* SBSW_COM_CSL03 */
    txBufferIdx++;
  }
}
#endif

#if (COM_TXSIGGRPMASK == STD_ON)
/**********************************************************************************************************************
  Com_TxBuffer_WriteSignalGroup
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxBuffer_WriteSignalGroup(Com_SignalGroupIdType SignalGroupId, P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) ShadowBufferPtr)
{
  if(ShadowBufferPtr != NULL_PTR)       /* COV_COM_SILENT_TX */
  {
    Com_TxBufferSigGrpInTxIPDUEndIdxOfTxSigGrpInfoType i;
    P2CONST(uint8, AUTOMATIC, COM_PBCFG) maskPtr = Com_GetAddrTxSigGrpMask(Com_GetTxSigGrpMaskStartIdxOfTxSigGrpInfo(SignalGroupId));
    P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) pIpduBuf = Com_GetAddrTxBuffer(Com_GetTxBufferSigGrpInTxIPDUStartIdxOfTxSigGrpInfo(SignalGroupId));
    /* #10 Copy the shadow buffer to the Tx ComIPdu buffer, mask out the required bits */
    for(i = 0; i < Com_GetTxBufferSigGrpInTxIPDULengthOfTxSigGrpInfo(SignalGroupId); i++)
    {
      pIpduBuf[i] = (pIpduBuf[i] & COM_CAST2UINT8(~maskPtr[i])) | (ShadowBufferPtr[i] & maskPtr[i]);    /* SBSW_COM_CSL03 */
    }
  }

  COM_DUMMY_STATEMENT(SignalGroupId);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}
#endif

#if (COM_SHDBUFFERREQUIREDOFRXSIGGRPINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxProcessing_ExtractToShdwBffr
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_RxProcessing_ExtractToShdwBffr(Com_RxSigGrpInfoIterType idxRxSigGrpInfo, P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr)
{
  /* #10 Iterate over all ComGroupSignals of the passed ComSignalGroup */
  Com_RxAccessInfoIndIterType RxAccessInfoIndidx = Com_GetRxAccessInfoGrpSigIndStartIdxOfRxSigGrpInfo(idxRxSigGrpInfo);
  for(; RxAccessInfoIndidx < Com_GetRxAccessInfoGrpSigIndEndIdxOfRxSigGrpInfo(idxRxSigGrpInfo); RxAccessInfoIndidx++)
  {
    Com_RxAccessInfoIterType idxRxAccessInfo = Com_GetRxAccessInfoGrpSigInd(RxAccessInfoIndidx);
    /* #20 Copy the value of the temp shadow buffer to the shadow buffer */
    switch (Com_GetApplTypeOfRxAccessInfo(idxRxAccessInfo))
    {
# if (COM_TMPRXSHDBUFFERUINT8 == STD_ON)
      case COM_UINT8_APPLTYPEOFRXACCESSINFO:
      {
        Com_SetRxSigBufferUInt8(Com_GetShdBufferIdxOfRxAccessInfo(idxRxAccessInfo), Com_GetTmpRxShdBufferUInt8(Com_GetTmpBufferIdxOfRxAccessInfo(idxRxAccessInfo)));    /* SBSW_COM_CSL03 */
        break;
      }
# endif
# if (COM_TMPRXSHDBUFFERSINT8 == STD_ON)
      case COM_SINT8_APPLTYPEOFRXACCESSINFO:
      {
        Com_SetRxSigBufferSInt8(Com_GetShdBufferIdxOfRxAccessInfo(idxRxAccessInfo), Com_GetTmpRxShdBufferSInt8(Com_GetTmpBufferIdxOfRxAccessInfo(idxRxAccessInfo)));    /* SBSW_COM_CSL03 */
        break;
      }
# endif
# if (COM_TMPRXSHDBUFFERUINT16 == STD_ON)
      case COM_UINT16_APPLTYPEOFRXACCESSINFO:
      {
        Com_SetRxSigBufferUInt16(Com_GetShdBufferIdxOfRxAccessInfo(idxRxAccessInfo), Com_GetTmpRxShdBufferUInt16(Com_GetTmpBufferIdxOfRxAccessInfo(idxRxAccessInfo)));  /* SBSW_COM_CSL03 */
        break;
      }
# endif
# if (COM_TMPRXSHDBUFFERSINT16 == STD_ON)
      case COM_SINT16_APPLTYPEOFRXACCESSINFO:
      {
        Com_SetRxSigBufferSInt16(Com_GetShdBufferIdxOfRxAccessInfo(idxRxAccessInfo), Com_GetTmpRxShdBufferSInt16(Com_GetTmpBufferIdxOfRxAccessInfo(idxRxAccessInfo)));  /* SBSW_COM_CSL03 */
        break;
      }
# endif
# if (COM_TMPRXSHDBUFFERUINT32 == STD_ON)
      case COM_UINT32_APPLTYPEOFRXACCESSINFO:
      {
        Com_SetRxSigBufferUInt32(Com_GetShdBufferIdxOfRxAccessInfo(idxRxAccessInfo), Com_GetTmpRxShdBufferUInt32(Com_GetTmpBufferIdxOfRxAccessInfo(idxRxAccessInfo)));  /* SBSW_COM_CSL03 */
        break;
      }
# endif
# if (COM_TMPRXSHDBUFFERSINT32 == STD_ON)
      case COM_SINT32_APPLTYPEOFRXACCESSINFO:
      {
        Com_SetRxSigBufferSInt32(Com_GetShdBufferIdxOfRxAccessInfo(idxRxAccessInfo), Com_GetTmpRxShdBufferSInt32(Com_GetTmpBufferIdxOfRxAccessInfo(idxRxAccessInfo)));  /* SBSW_COM_CSL03 */
        break;
      }
# endif
# if (COM_TMPRXSHDBUFFERUINT64 == STD_ON)
      case COM_UINT64_APPLTYPEOFRXACCESSINFO:
      {
        Com_SetRxSigBufferUInt64(Com_GetShdBufferIdxOfRxAccessInfo(idxRxAccessInfo), Com_GetTmpRxShdBufferUInt64(Com_GetTmpBufferIdxOfRxAccessInfo(idxRxAccessInfo)));  /* SBSW_COM_CSL03 */
        break;
      }
# endif
# if (COM_TMPRXSHDBUFFERSINT64 == STD_ON)
      case COM_SINT64_APPLTYPEOFRXACCESSINFO:
      {
        Com_SetRxSigBufferSInt64(Com_GetShdBufferIdxOfRxAccessInfo(idxRxAccessInfo), Com_GetTmpRxShdBufferSInt64(Com_GetTmpBufferIdxOfRxAccessInfo(idxRxAccessInfo)));  /* SBSW_COM_CSL03 */
        break;
      }
# endif
# if (COM_TMPRXSHDBUFFERFLOAT32 == STD_ON)
      case COM_FLOAT32_APPLTYPEOFRXACCESSINFO:
      {
        Com_SetRxSigBufferFloat32(Com_GetShdBufferIdxOfRxAccessInfo(idxRxAccessInfo), Com_GetTmpRxShdBufferFloat32(Com_GetTmpBufferIdxOfRxAccessInfo(idxRxAccessInfo)));        /* SBSW_COM_CSL03 */
        break;
      }
# endif
# if (COM_TMPRXSHDBUFFERFLOAT64 == STD_ON)
      case COM_FLOAT64_APPLTYPEOFRXACCESSINFO:
      {
        Com_SetRxSigBufferFloat64(Com_GetShdBufferIdxOfRxAccessInfo(idxRxAccessInfo), Com_GetTmpRxShdBufferFloat64(Com_GetTmpBufferIdxOfRxAccessInfo(idxRxAccessInfo)));        /* SBSW_COM_CSL03 */
        break;
      }
# endif
# if (COM_TMPRXSHDBUFFERARRAYBASED == STD_ON)
#  if (COM_EXISTS_UINT8_N_APPLTYPEOFRXACCESSINFO == STD_ON)
      case COM_UINT8_N_APPLTYPEOFRXACCESSINFO:
      {
        VStdMemCpyRamToRam(Com_GetAddrRxSigBufferArrayBased(Com_GetRxSigBufferArrayBasedShdBufferStartIdxOfRxAccessInfo(idxRxAccessInfo)), Com_GetAddrTmpRxShdBufferArrayBased(Com_GetTmpRxShdBufferArrayBasedTmpBufferStartIdxOfRxAccessInfo(idxRxAccessInfo)), (PduLengthType) Com_GetRxSigBufferArrayBasedShdBufferLengthOfRxAccessInfo(idxRxAccessInfo));   /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_COM_MEM_CPY_2RAM */
        break;
      }
#  endif
#  if (COM_RXDYNSIGNALTMPLENGTHFORSIGNALGROUPS == STD_ON)
      case COM_UINT8_DYN_APPLTYPEOFRXACCESSINFO:
      {
        Com_RxTpInfoIdxOfRxPduInfoType rxTpPduInfoIdx = Com_GetRxTpInfoIdxOfRxPduInfo(Com_GetRxPduInfoIdxOfRxAccessInfo(idxRxAccessInfo));
        Com_SetRxDynSignalTmpLengthForSignalGroups(rxTpPduInfoIdx, Com_GetRxDynamicLength(PduInfoPtr->SduLength, idxRxAccessInfo));     /* SBSW_COM_CSL02 */
        VStdMemCpyRamToRam(Com_GetAddrRxSigBufferArrayBased(Com_GetRxSigBufferArrayBasedShdBufferStartIdxOfRxAccessInfo(idxRxAccessInfo)), Com_GetAddrTmpRxShdBufferArrayBased(Com_GetTmpRxShdBufferArrayBasedTmpBufferStartIdxOfRxAccessInfo(idxRxAccessInfo)), Com_GetRxDynSignalTmpLengthForSignalGroups(rxTpPduInfoIdx));   /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_COM_CSL01 */
        break;
      }
#  endif
# endif
      default: /* COV_COM_MISRA */
        break;
    }
  }
  COM_DUMMY_STATEMENT(idxRxSigGrpInfo); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT_CONST(PduInfoPtr);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}       /* PRQA S 6030 */ /* MD_MSR_STCYC */
#endif


#if (((COM_MINPROCGWBUFFERUSEDOFRXACCESSINFO == STD_ON) || (COM_MINPROCGWBUFFERARRAYBASEDBUFFERUSEDOFRXACCESSINFO == STD_ON)) && (COM_GWSIGGRPMAPPINGENDIDXOFGWINFO == STD_ON))
/**********************************************************************************************************************
  Com_RxProcessing_ExtractToMinProcGwBuffer
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_RxProcessing_ExtractToMinProcGwBuffer(Com_RxSigGrpInfoIterType idxRxSigGrpInfo, P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr)
{
  /* #10 Iterate over all ComGroupSignals of the passed ComSignalGroup */
  Com_RxAccessInfoIndIterType RxAccessInfoIndidx = Com_GetRxAccessInfoGrpSigIndStartIdxOfRxSigGrpInfo(idxRxSigGrpInfo);
  for(; RxAccessInfoIndidx < Com_GetRxAccessInfoGrpSigIndEndIdxOfRxSigGrpInfo(idxRxSigGrpInfo); RxAccessInfoIndidx++)
  {
    Com_RxAccessInfoIterType idxRxAccessInfo = Com_GetRxAccessInfoGrpSigInd(RxAccessInfoIndidx);
    /* #20 Copy the value of the temp shadow buffer to the MinProcGwBuffer */

# if(COM_MINPROCGWBUFFERUSEDOFRXACCESSINFO == STD_ON)
    if(Com_IsMinProcGwBufferUsedOfRxAccessInfo(idxRxAccessInfo))
    {
      switch (Com_GetApplTypeOfRxAccessInfo(idxRxAccessInfo))
      {
# if (COM_TMPRXSHDBUFFERUINT8 == STD_ON)
        case COM_UINT8_APPLTYPEOFRXACCESSINFO:
        {
          Com_SetMinProcGwBufferUInt8(Com_GetMinProcGwBufferIdxOfRxAccessInfo(idxRxAccessInfo), Com_GetTmpRxShdBufferUInt8(Com_GetTmpBufferIdxOfRxAccessInfo(idxRxAccessInfo)));        /* SBSW_COM_CSL03 */
          break;
        }
# endif
# if (COM_TMPRXSHDBUFFERSINT8 == STD_ON)
        case COM_SINT8_APPLTYPEOFRXACCESSINFO:
        {
          Com_SetMinProcGwBufferSInt8(Com_GetMinProcGwBufferIdxOfRxAccessInfo(idxRxAccessInfo), Com_GetTmpRxShdBufferSInt8(Com_GetTmpBufferIdxOfRxAccessInfo(idxRxAccessInfo)));        /* SBSW_COM_CSL03 */
          break;
        }
# endif
# if (COM_TMPRXSHDBUFFERUINT16 == STD_ON)
        case COM_UINT16_APPLTYPEOFRXACCESSINFO:
        {
          Com_SetMinProcGwBufferUInt16(Com_GetMinProcGwBufferIdxOfRxAccessInfo(idxRxAccessInfo), Com_GetTmpRxShdBufferUInt16(Com_GetTmpBufferIdxOfRxAccessInfo(idxRxAccessInfo)));      /* SBSW_COM_CSL03 */
          break;
        }
# endif
# if (COM_TMPRXSHDBUFFERSINT16 == STD_ON)
        case COM_SINT16_APPLTYPEOFRXACCESSINFO:
        {
          Com_SetMinProcGwBufferSInt16(Com_GetMinProcGwBufferIdxOfRxAccessInfo(idxRxAccessInfo), Com_GetTmpRxShdBufferSInt16(Com_GetTmpBufferIdxOfRxAccessInfo(idxRxAccessInfo)));      /* SBSW_COM_CSL03 */
          break;
        }
# endif
# if (COM_TMPRXSHDBUFFERUINT32 == STD_ON)
        case COM_UINT32_APPLTYPEOFRXACCESSINFO:
        {
          Com_SetMinProcGwBufferUInt32(Com_GetMinProcGwBufferIdxOfRxAccessInfo(idxRxAccessInfo), Com_GetTmpRxShdBufferUInt32(Com_GetTmpBufferIdxOfRxAccessInfo(idxRxAccessInfo)));      /* SBSW_COM_CSL03 */
          break;
        }
# endif
# if (COM_TMPRXSHDBUFFERSINT32 == STD_ON)
        case COM_SINT32_APPLTYPEOFRXACCESSINFO:
        {
          Com_SetMinProcGwBufferSInt32(Com_GetMinProcGwBufferIdxOfRxAccessInfo(idxRxAccessInfo), Com_GetTmpRxShdBufferSInt32(Com_GetTmpBufferIdxOfRxAccessInfo(idxRxAccessInfo)));      /* SBSW_COM_CSL03 */
          break;
        }
# endif
# if (COM_TMPRXSHDBUFFERUINT64 == STD_ON)
        case COM_UINT64_APPLTYPEOFRXACCESSINFO:
        {
          Com_SetMinProcGwBufferUInt64(Com_GetMinProcGwBufferIdxOfRxAccessInfo(idxRxAccessInfo), Com_GetTmpRxShdBufferUInt64(Com_GetTmpBufferIdxOfRxAccessInfo(idxRxAccessInfo)));      /* SBSW_COM_CSL03 */
          break;
        }
# endif
# if (COM_TMPRXSHDBUFFERSINT64 == STD_ON)
        case COM_SINT64_APPLTYPEOFRXACCESSINFO:
        {
          Com_SetMinProcGwBufferSInt64(Com_GetMinProcGwBufferIdxOfRxAccessInfo(idxRxAccessInfo), Com_GetTmpRxShdBufferSInt64(Com_GetTmpBufferIdxOfRxAccessInfo(idxRxAccessInfo)));      /* SBSW_COM_CSL03 */
          break;
        }
# endif
# if (COM_TMPRXSHDBUFFERFLOAT32 == STD_ON)
        case COM_FLOAT32_APPLTYPEOFRXACCESSINFO:
        {
          Com_SetMinProcGwBufferFloat32(Com_GetMinProcGwBufferIdxOfRxAccessInfo(idxRxAccessInfo), Com_GetTmpRxShdBufferFloat32(Com_GetTmpBufferIdxOfRxAccessInfo(idxRxAccessInfo)));    /* SBSW_COM_CSL03 */
          break;
        }
# endif
# if (COM_TMPRXSHDBUFFERFLOAT64 == STD_ON)
        case COM_FLOAT64_APPLTYPEOFRXACCESSINFO:
        {
          Com_SetMinProcGwBufferFloat64(Com_GetMinProcGwBufferIdxOfRxAccessInfo(idxRxAccessInfo), Com_GetTmpRxShdBufferFloat64(Com_GetTmpBufferIdxOfRxAccessInfo(idxRxAccessInfo)));    /* SBSW_COM_CSL03 */
          break;
        }
# endif
        default:       /* COV_COM_MISRA */
          break;
      }
    }
# endif

# if ((COM_MINPROCGWBUFFERARRAYBASEDBUFFERUSEDOFRXACCESSINFO == STD_ON))
  if(Com_IsMinProcGwBufferArrayBasedBufferUsedOfRxAccessInfo(idxRxAccessInfo)) /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    VStdMemCpyRamToRam(Com_GetAddrMinProcGwBufferArrayBased(Com_GetMinProcGwBufferArrayBasedBufferStartIdxOfRxAccessInfo(idxRxAccessInfo)), Com_GetAddrTmpRxShdBufferArrayBased(Com_GetTmpRxShdBufferArrayBasedTmpBufferStartIdxOfRxAccessInfo(idxRxAccessInfo)), (PduLengthType) Com_GetMinProcGwBufferArrayBasedBufferLengthOfRxAccessInfo(idxRxAccessInfo));    /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_COM_MEM_CPY_2RAM */ 
  }
# endif
  }
  COM_DUMMY_STATEMENT(idxRxSigGrpInfo); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT_CONST(PduInfoPtr);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}       /* PRQA S 6030 */ /* MD_MSR_STCYC */
#endif


#if (COM_BUFFERUSEDOFRXACCESSINFO == STD_ON)
/**********************************************************************************************************************
  Com_Signal_SetRxSigBufferValue
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_Signal_SetRxSigBufferValue(Com_RxAccessInfoIterType idxRxAccessInfo, uint32_least idxDestValue, uint32_least idxSrcValue)
{
  /* #10 Copy the constant value at the position of the passed source index to the passed destination index, the source and destination buffer depends on the ApplType of the passed signal */
  switch (Com_GetApplTypeOfRxAccessInfo(idxRxAccessInfo))
  {
# if ((COM_RXSIGBUFFERUINT8 == STD_ON) && (COM_EXISTS_UINT8_APPLTYPEOFRXACCESSINFO == STD_ON))
    case COM_UINT8_APPLTYPEOFRXACCESSINFO:
    {
      Com_SetRxSigBufferUInt8(idxDestValue, Com_GetConstValueUInt8(idxSrcValue));       /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
      break;
    }
# endif
# if (COM_RXSIGBUFFERSINT8 == STD_ON)
    case COM_SINT8_APPLTYPEOFRXACCESSINFO:
    {
      Com_SetRxSigBufferSInt8(idxDestValue, Com_GetConstValueSInt8(idxSrcValue));       /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
      break;
    }
# endif
# if (COM_RXSIGBUFFERUINT16 == STD_ON)
    case COM_UINT16_APPLTYPEOFRXACCESSINFO:
    {
      Com_SetRxSigBufferUInt16(idxDestValue, Com_GetConstValueUInt16(idxSrcValue));     /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
      break;
    }
# endif
# if (COM_RXSIGBUFFERSINT16 == STD_ON)
    case COM_SINT16_APPLTYPEOFRXACCESSINFO:
    {
      Com_SetRxSigBufferSInt16(idxDestValue, Com_GetConstValueSInt16(idxSrcValue));     /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
      break;
    }
# endif
# if (COM_RXSIGBUFFERUINT32 == STD_ON)
    case COM_UINT32_APPLTYPEOFRXACCESSINFO:
    {
      Com_SetRxSigBufferUInt32(idxDestValue, Com_GetConstValueUInt32(idxSrcValue));     /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
      break;
    }
# endif
# if (COM_RXSIGBUFFERSINT32 == STD_ON)
    case COM_SINT32_APPLTYPEOFRXACCESSINFO:
    {
      Com_SetRxSigBufferSInt32(idxDestValue, Com_GetConstValueSInt32(idxSrcValue));     /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
      break;
    }
# endif
# if (COM_RXSIGBUFFERUINT64 == STD_ON)
    case COM_UINT64_APPLTYPEOFRXACCESSINFO:
    {
      Com_SetRxSigBufferUInt64(idxDestValue, Com_GetConstValueUInt64(idxSrcValue));     /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
      break;
    }
# endif
# if (COM_RXSIGBUFFERSINT64 == STD_ON)
    case COM_SINT64_APPLTYPEOFRXACCESSINFO:
    {
      Com_SetRxSigBufferSInt64(idxDestValue, Com_GetConstValueSInt64(idxSrcValue));     /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
      break;
    }
# endif
# if (COM_RXSIGBUFFERFLOAT32 == STD_ON)
    case COM_FLOAT32_APPLTYPEOFRXACCESSINFO:
    {
      Com_SetRxSigBufferFloat32(idxDestValue, Com_GetConstValueFloat32(idxSrcValue));   /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
      break;
    }
# endif
# if (COM_RXSIGBUFFERFLOAT64 == STD_ON)
    case COM_FLOAT64_APPLTYPEOFRXACCESSINFO:
    {
      Com_SetRxSigBufferFloat64(idxDestValue, Com_GetConstValueFloat64(idxSrcValue));   /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
      break;
    }
# endif
    default:   /* COV_COM_MISRA */
      break;
  }
  COM_DUMMY_STATEMENT(idxDestValue);    /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(idxRxAccessInfo); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}       /* PRQA S 6030 */ /* MD_MSR_STCYC */
#endif


#if (COM_MINPROCGWBUFFERUSEDOFRXACCESSINFO == STD_ON)
/**********************************************************************************************************************
  Com_Signal_SetMinProcGwBufferValue
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_Signal_SetMinProcGwBufferValue(Com_RxAccessInfoIterType idxRxAccessInfo, uint32_least idxDestValue, uint32_least idxSrcValue)
{
  /* #10 Copy the constant value at the position of the passed source index to the passed destination index, the source and destination buffer depends on the ApplType of the passed signal */
  switch (Com_GetApplTypeOfRxAccessInfo(idxRxAccessInfo))
  {
# if ((COM_MINPROCGWBUFFERUINT8 == STD_ON) && (COM_EXISTS_UINT8_APPLTYPEOFRXACCESSINFO == STD_ON))
    case COM_UINT8_APPLTYPEOFRXACCESSINFO:
    {
      Com_SetMinProcGwBufferUInt8(idxDestValue, Com_GetConstValueUInt8(idxSrcValue));   /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
      break;
    }
# endif
# if (COM_MINPROCGWBUFFERSINT8 == STD_ON)
    case COM_SINT8_APPLTYPEOFRXACCESSINFO:
    {
      Com_SetMinProcGwBufferSInt8(idxDestValue, Com_GetConstValueSInt8(idxSrcValue));   /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
      break;
    }
# endif
# if (COM_MINPROCGWBUFFERUINT16 == STD_ON)
    case COM_UINT16_APPLTYPEOFRXACCESSINFO:
    {
      Com_SetMinProcGwBufferUInt16(idxDestValue, Com_GetConstValueUInt16(idxSrcValue)); /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
      break;
    }
# endif
# if (COM_MINPROCGWBUFFERSINT16 == STD_ON)
    case COM_SINT16_APPLTYPEOFRXACCESSINFO:
    {
      Com_SetMinProcGwBufferSInt16(idxDestValue, Com_GetConstValueSInt16(idxSrcValue)); /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
      break;
    }
# endif
# if (COM_MINPROCGWBUFFERUINT32 == STD_ON)
    case COM_UINT32_APPLTYPEOFRXACCESSINFO:
    {
      Com_SetMinProcGwBufferUInt32(idxDestValue, Com_GetConstValueUInt32(idxSrcValue)); /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
      break;
    }
# endif
# if (COM_MINPROCGWBUFFERSINT32 == STD_ON)
    case COM_SINT32_APPLTYPEOFRXACCESSINFO:
    {
      Com_SetMinProcGwBufferSInt32(idxDestValue, Com_GetConstValueSInt32(idxSrcValue)); /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
      break;
    }
# endif
# if (COM_MINPROCGWBUFFERUINT64 == STD_ON)
    case COM_UINT64_APPLTYPEOFRXACCESSINFO:
    {
      Com_SetMinProcGwBufferUInt64(idxDestValue, Com_GetConstValueUInt64(idxSrcValue)); /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
      break;
    }
# endif
# if (COM_MINPROCGWBUFFERSINT64 == STD_ON)
    case COM_SINT64_APPLTYPEOFRXACCESSINFO:
    {
      Com_SetMinProcGwBufferSInt64(idxDestValue, Com_GetConstValueSInt64(idxSrcValue)); /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
      break;
    }
# endif
# if (COM_MINPROCGWBUFFERFLOAT32 == STD_ON)
    case COM_FLOAT32_APPLTYPEOFRXACCESSINFO:
    {
      Com_SetMinProcGwBufferFloat32(idxDestValue, Com_GetConstValueFloat32(idxSrcValue));       /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
      break;
    }
# endif
# if (COM_MINPROCGWBUFFERFLOAT64 == STD_ON)
    case COM_FLOAT64_APPLTYPEOFRXACCESSINFO:
    {
      Com_SetMinProcGwBufferFloat64(idxDestValue, Com_GetConstValueFloat64(idxSrcValue));       /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
      break;
    }
# endif
    default:   /* COV_COM_MISRA */
      break;
  }
  COM_DUMMY_STATEMENT(idxDestValue);    /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(idxRxAccessInfo); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}       /* PRQA S 6030 */ /* MD_MSR_STCYC */
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
 *  END OF FILE: Com_Buffers.c
 *********************************************************************************************************************/
