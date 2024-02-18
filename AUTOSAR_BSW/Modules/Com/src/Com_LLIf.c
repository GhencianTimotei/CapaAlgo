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
/*!        \file  Com_LLIf.c
 *        \brief  MICROSAR Communication source file
 *
 *      \details  This is the implementation of the MICROSAR Communication module.
 *                The basic software module is based on the AUTOSAR Communication specification.
 *
 *********************************************************************************************************************/
#define COM_LLIF_SOURCE

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
#include "Com_LLIf.h"
#include "Com_Timer.h"
#include "Com_Buffers.h"
#include "Com_Gateway.h"
#include "Com_TxModeHdlr.h"
#include "Com_RxProcessing.h"
#include "Com_Notifications.h"
#include "vstdlib.h"
#include "SchM_Com.h"

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

#if ((COM_MIXEDMODEPERIODICSUPPRESSION == STD_ON) || (COM_STRICT_REPETITION_PERIOD == STD_ON) || (COM_TXTPINFOUSEDOFTXPDUINFO == STD_ON) || (COM_MINIMUMDELAYOFTXMODEINFO == STD_ON) || (COM_EXISTS_TRANSMIT_CLRUBOFTXPDUINFO == STD_ON) || (COM_CBKTXERRFUNCPTRINDUSEDOFTXPDUINFO == STD_ON))
/**********************************************************************************************************************
Com_TxLLIf_SetTxAttributes
**********************************************************************************************************************/
/*! \brief        This function adjusts Tx-Parameter like Update-Bit, Delay Time Counter, Tp Connection State and
 *                Com_WaitingForConfirmation Parameter if the status of transmit request has been accepted.
    \details      -
    \pre          -
    \param[in]    status        Status if transmit request has been accepted or not
    \param[in]    ComTxPduId    Valid ID of Tx I-PDU to be transmitted.
    \trace        SPEC-2736857, SPEC-2736858, SPEC-2736898
    \context      TASK|ISR2
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_TxLLIf_SetTxAttributes(PduIdType ComTxPduId, Std_ReturnType status);
#endif

#if (COM_TXPDUCALLOUTFUNCPTRUSEDOFTXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_TxLLIf_GetTxPduCalloutFuncPtr
**********************************************************************************************************************/
/*! \brief            This function returns the result of Tx Pdu Callout.
    \details          -
    \pre              -
    \param[in]        ComTxPduId    ID of I-PDU to be transmitted.
    \param[in,out]    PduInfo       Pointer to the SDU buffer and the SDU length.
    \return           boolean       callout result
    \context          TASK|ISR2
    \trace            CREQ-103167
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(boolean, COM_CODE) Com_TxLLIf_GetTxPduCalloutFuncPtr(PduIdType ComTxPduId, P2VAR(PduInfoType, AUTOMATIC, AUTOMATIC) PduInfo);
#endif

#if (COM_TXBUFFERMETADATAUSEDOFTXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_TxLLIf_CpyInitMetaDataToBffr
**********************************************************************************************************************/
/*! \brief        This function copies the initial meta data to TxBuffer.
    \details      -
    \pre          -
    \param[in]    ComTxPduId    ID of I-PDU to be transmitted.
    \context      TASK|ISR2
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_TxLLIf_CpyInitMetaDataToBffr(PduIdType ComTxPduId);
#endif

#if (COM_RXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxIndication_ProcessPdu
**********************************************************************************************************************/
/*! \brief        This function processes the PDU immediate or copies the received PDU in the deferred buffer, depending
 *                on the IPdu Signal Processing parameter.
    \details      -
    \pre          -
    \param[in]    ComPduId Handle of the I-PDU.
    \param[in]    PduInfoPtr   contains the SDU buffer and the SDU length
    \context      TASK|ISR2
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_RxIndication_ProcessPdu(PduIdType ComPduId, P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr);
#endif

#if (COM_RXDEFERREDEVENTCACHE == STD_ON)
/**********************************************************************************************************************
  Com_RxIndication_CacheDeferredEvent
**********************************************************************************************************************/
/*! \brief        This function caches the ID of the received Rx deferred PDU to avoid the iteration through all
 *                RxPdus while processing deferred IPdus
    \details      -
    \pre          -
    \param[in]    ComPduId            Rx ComIPdu handle Id
    \context      TASK|ISR2
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_RxIndication_CacheDeferredEvent(Com_RxDeferredEventCacheType ComPduId);
#endif

#if (COM_GWEVENTCACHE == STD_ON)
/**********************************************************************************************************************
  Com_RxIndication_CacheDeferredDescriptionGwEvent
**********************************************************************************************************************/
/*! \brief        This function caches a deferred gateway description event.
    \details      -
    \pre          -
    \param[in]    ComPduId            Handle of the I-PDU.
    \context      TASK|ISR2
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_RxIndication_CacheDeferredDescriptionGwEvent(PduIdType ComPduId);
#endif


/**********************************************************************************************************************
  LOCAL FUNCTIONS
**********************************************************************************************************************/

#if ((COM_MIXEDMODEPERIODICSUPPRESSION == STD_ON) || (COM_STRICT_REPETITION_PERIOD == STD_ON) || (COM_TXTPINFOUSEDOFTXPDUINFO == STD_ON) || (COM_MINIMUMDELAYOFTXMODEINFO == STD_ON) || (COM_EXISTS_TRANSMIT_CLRUBOFTXPDUINFO == STD_ON) || (COM_CBKTXERRFUNCPTRINDUSEDOFTXPDUINFO == STD_ON))
/**********************************************************************************************************************
Com_TxLLIf_SetTxAttributes
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *

**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_TxLLIf_SetTxAttributes(PduIdType ComTxPduId, Std_ReturnType status)
{
  /* #10 If the value of status is positive */
  if(status == E_OK)
  {
# if (COM_EXISTS_TRANSMIT_CLRUBOFTXPDUINFO == STD_ON)
    /* #20 If the Update Bit clear context is TRANSMIT, clear the Update Bits */
    if(COM_TRANSMIT_CLRUBOFTXPDUINFO == Com_GetClrUbOfTxPduInfo(ComTxPduId))
    {
      Com_TxBuffer_ClearUpdateBits(ComTxPduId);
    }
# endif
# if (COM_MINIMUMDELAYOFTXMODEINFO == STD_ON)
#  if (COM_DIRECTTRIGGER == STD_ON)
    if(Com_IsDirectTrigger(ComTxPduId)) /* COV_COM_DIRECTTRIGGER */
#  endif
    {
      /* \trace SPEC-2736857 */ /* \trace SPEC-2736858 */
      /* #30 Reload the Minimum Delay timer */
      Com_SetDelayTimeCnt(ComTxPduId, Com_GetMinimumDelayOfTxModeInfo(ComTxPduId));     /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
    }
# endif
# if (COM_MIXEDMODEPERIODICSUPPRESSION == STD_ON)
    Com_SetInitialTransmit(ComTxPduId, FALSE);  /* SBSW_COM_CSL02 */
# endif
  }
# if ((COM_TXTPINFOUSEDOFTXPDUINFO == STD_ON) || (COM_CBKTXERRFUNCPTRINDUSEDOFTXPDUINFO == STD_ON))
  /* #40 Otherwise */
  else
  {
#  if (COM_TXTPINFOUSEDOFTXPDUINFO == STD_ON)
    /* #50 If the ComIPdu is a TP PDU, set the state to READY */
    if(Com_IsTxTpInfoUsedOfTxPduInfo(ComTxPduId))       /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
    {
      /* \trace SPEC-2736898 */
      Com_ResetTxTpConnection(ComTxPduId);
    }
#  endif
#  if (COM_CBKTXERRFUNCPTRINDUSEDOFTXPDUINFO == STD_ON)
    /* #60 Clear the WaitingForConfirmation flag */
    Com_SetWaitingForConfirmation(ComTxPduId, FALSE);   /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
#  endif
  }
# endif

# if (COM_STRICT_REPETITION_PERIOD == STD_ON)
  /* #70 Reset the RepCycleCnt to avoid a potential shift (the time between repetitions beeing less than the configured value ComTxModeRepetitionPeriod) of the repetition period caused by the MDT. */
  Com_SetRepCycleCnt(ComTxPduId, Com_TxModeHdlr_GetCurrentRepetitionPeriod(ComTxPduId));        /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
# endif

}
#endif

#if (COM_TXPDUCALLOUTFUNCPTRUSEDOFTXPDUINFO == STD_ON)
/**********************************************************************************************************************
Com_TxLLIf_GetTxPduCalloutFuncPtr
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *

**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(boolean, COM_CODE) Com_TxLLIf_GetTxPduCalloutFuncPtr(PduIdType ComTxPduId, P2VAR(PduInfoType, AUTOMATIC, AUTOMATIC) PduInfo)      /* PRQA S 3673 */ /* MD_MSR_Rule8.13 */
{
  boolean CalloutResult = TRUE; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  /* #10 If the ComIPdu has a configured callout */
  if(Com_IsTxPduCalloutFuncPtrUsedOfTxPduInfo(ComTxPduId))      /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    /* #20 Call the callout with the PduInfo (if ASR 4.1.x callouts are enabled) or with the SduDataPtr */
    Com_TxPduCalloutFuncPtrIdxOfTxPduInfoType idx = Com_GetTxPduCalloutFuncPtrIdxOfTxPduInfo(ComTxPduId);
# if (COM_IPDUCALLOUT_USEPDUINFOPTR == STD_ON)
    CalloutResult = Com_GetTxPduCalloutFuncPtr(idx) (ComTxPduId, PduInfo);      /* SBSW_COM_FCT_PTR_CALL_CSL03 */
# else
    CalloutResult = Com_GetTxPduCalloutFuncPtr(idx) (ComTxPduId, (P2VAR(uint8, AUTOMATIC, AUTOMATIC)) PduInfo->SduDataPtr);     /* SBSW_COM_FCT_PTR_CALL_CSL03 */
# endif
  }
  return CalloutResult;
}
#endif

#if (COM_TXBUFFERMETADATAUSEDOFTXPDUINFO == STD_ON)
/**********************************************************************************************************************
Com_TxLLIf_CpyInitMetaDataToBffr
**********************************************************************************************************************/
/*! Internal comment removed.
 *

**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_TxLLIf_CpyInitMetaDataToBffr(PduIdType ComTxPduId)
{
  if(Com_IsTxBufferMetaDataUsedOfTxPduInfo(ComTxPduId))
  {
    /* #10 Copy the meta data initial value to the Tx PDU buffer */
    P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) pTxPduBuffer = Com_GetAddrTxBuffer(Com_GetTxBufferMetaDataStartIdxOfTxPduInfo(ComTxPduId));
    P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) pInitValues = Com_GetAddrTxPduInitValue(Com_GetTxPduInitValueMetaDataStartIdxOfTxPduInfo(ComTxPduId));
    uint8_least metaDataLength = Com_GetMetaDataLengthOfTxPduInfo(ComTxPduId);
    uint8_least idxMetaData;
    for(idxMetaData = 0; idxMetaData < metaDataLength; idxMetaData++)
    {
      pTxPduBuffer[idxMetaData] = pInitValues[idxMetaData];     /* SBSW_COM_CSL01 */
    }
  }
}
#endif

#if (COM_RXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxIndication_ProcessPdu
**********************************************************************************************************************/
/*! Internal comment removed.
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
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_RxIndication_ProcessPdu(PduIdType ComPduId, P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr)
{
  PduIdType comRxPduInfoIdx = ComPduId;
# if (COM_EXISTS_DEFERRED_SIGNALPROCESSINGOFRXPDUINFO == STD_ON)
  /* #10 If the passed Rx ComIPdu is handled deferred */
  if(Com_IsHandleRxPduDeferredUsedOfRxPduInfo(comRxPduInfoIdx)) /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    SchM_Enter_Com_COM_EXCLUSIVE_AREA_RX();
#  if (COM_RXDEFPDUBUFFERUSEDOFRXPDUINFO == STD_ON)
    switch (Com_GetTypeOfRxPduInfo(comRxPduInfoIdx))
    {
#   if(COM_EXISTS_NORMAL_TYPEOFRXPDUINFO == STD_ON)
      case COM_NORMAL_TYPEOFRXPDUINFO:
        /* #20 If the passed Rx ComIPdu is not a TP Pdu and no NULL_PTR, copy the passed Sdu data to the deferred Pdu buffer */
        if(PduInfoPtr->SduDataPtr != NULL_PTR)
        {
          Com_RxDefPduBufferLengthOfRxPduInfoType numberOfBytes =
            ((Com_GetRxDefPduBufferLengthOfRxPduInfo(comRxPduInfoIdx)) >
             PduInfoPtr->SduLength) ? (Com_RxDefPduBufferLengthOfRxPduInfoType) (PduInfoPtr->SduLength) : Com_GetRxDefPduBufferLengthOfRxPduInfo(comRxPduInfoIdx);
          VStdMemCpyRamToRam(Com_GetAddrRxDefPduBuffer(Com_GetRxDefPduBufferStartIdxOfRxPduInfo(comRxPduInfoIdx)), (P2CONST(uint8, AUTOMATIC, COM_APPL_DATA)) PduInfoPtr->SduDataPtr, numberOfBytes);   /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_COM_MEM_CPY_2RAM */
        }
        break;
#   endif
#   if(COM_RXTPINFOUSEDOFRXPDUINFO == STD_ON)
      case COM_TP_TYPEOFRXPDUINFO:
        break;
#   endif
      default: /* COV_COM_MISRA */
        break;
    }
#  endif
#  if (COM_RXDEFERREDEVENTCACHE == STD_ON)
    /* #30 If the passed ComIPdu is not cached yet, add the Rx ComIPdu to the deferred event cache */
    if(Com_GetHandleRxPduDeferred(Com_GetHandleRxPduDeferredIdxOfRxPduInfo(comRxPduInfoIdx)) == 0u)     /* COV_COM_RXDEFERRED_PROCESSING */
    {
      Com_RxIndication_CacheDeferredEvent((Com_RxDeferredEventCacheType) comRxPduInfoIdx);
    }
#  endif
    /* #40 Store the passed Sdu length in the handle deferred buffer */
    Com_SetHandleRxPduDeferred(Com_GetHandleRxPduDeferredIdxOfRxPduInfo(comRxPduInfoIdx), (PduInfoPtr->SduLength + 1u));        /* SBSW_COM_CSL03 */
#  if(COM_GWEVENTCACHE == STD_ON)
    Com_RxIndication_CacheDeferredDescriptionGwEvent(comRxPduInfoIdx);
#  endif
    SchM_Exit_Com_COM_EXCLUSIVE_AREA_RX();
  }
# endif
# if ((COM_EXISTS_DEFERRED_SIGNALPROCESSINGOFRXPDUINFO == STD_ON) && (COM_EXISTS_IMMEDIATE_SIGNALPROCESSINGOFRXPDUINFO == STD_ON))
  else
# endif
# if (COM_EXISTS_IMMEDIATE_SIGNALPROCESSINGOFRXPDUINFO == STD_ON)
    /* #50 Otherwise process the Rx ComIPdu immediate */
  {
    FctPtrCacheStrct immediateFctPtrCacheStrct;

#  if (COM_RXIMMEDIATEFCTPTRCACHE == STD_ON)
    uint32 fctPtrCache[COM_RXIMMEDIATEFCTPTRCACHESIZE];
    immediateFctPtrCacheStrct.ptrToCache = fctPtrCache;
    immediateFctPtrCacheStrct.cacheSize = COM_RXIMMEDIATEFCTPTRCACHESIZE;
#  else
    immediateFctPtrCacheStrct.ptrToCache = NULL_PTR;
    immediateFctPtrCacheStrct.cacheSize = 0;
#  endif
    immediateFctPtrCacheStrct.cacheIndex = 0;

    SchM_Enter_Com_COM_EXCLUSIVE_AREA_RX();
#  if (COM_RXSIGINFOENDIDXOFRXPDUINFO == STD_ON)
    /* #60 Do Rx ComSignal processing */
    Com_RxProcessing_RxPduSigEvent(comRxPduInfoIdx, PduInfoPtr, &immediateFctPtrCacheStrct);    /* SBSW_COM_FCTCALL_WITH_P2CONST_AND_FCTPTR_CACHE_PTR_1 */
#  endif
#  if (COM_RXSIGGRPINFOINDENDIDXOFRXPDUINFO == STD_ON)
    /* #70 Do Rx ComSignalGroup processing */
    Com_RxProcessing_RxPduSigGrpEvent(comRxPduInfoIdx, PduInfoPtr, &immediateFctPtrCacheStrct); /* SBSW_COM_FCTCALL_WITH_P2CONST_AND_FCTPTR_CACHE_PTR_1 */
#  endif
#  if (COM_GWTXPDUDESCRIPTIONINFOUSEDOFRXPDUINFO == STD_ON)
    /* #75 If rxPdu has any configured GwDescriptions, do gateway description processing */
    if(Com_IsGwTxPduDescriptionInfoUsedOfRxPduInfo(comRxPduInfoIdx))    /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
    {
      SchM_Enter_Com_COM_EXCLUSIVE_AREA_TX();

      Com_RxProcessing_GwDescriptionEvent(comRxPduInfoIdx,      /* SBSW_COM_FCTCALL_WITH_P2CONST */
                                          PduInfoPtr);

      SchM_Exit_Com_COM_EXCLUSIVE_AREA_TX();
    }
#  endif

#  if (COM_RXTOUTINFOUSEDOFRXPDUINFO == STD_ON)
    /* #80 If the passed Rx ComIPdu has a timeout, remove the timeout occurred flag */
    if(Com_IsRxTOutInfoUsedOfRxPduInfo(comRxPduInfoIdx))        /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
    {
      Com_LMgt_RemoveOccurredFlag(Com_GetRxTOutInfoIdxOfRxPduInfo(comRxPduInfoIdx));    /* SBSW_COM_CSL02_CSL03 */
    }
#  endif
    SchM_Exit_Com_COM_EXCLUSIVE_AREA_RX();

#  if (COM_RXIMMEDIATEFCTPTRCACHE == STD_ON)
    /* #90 Call all cached notification or invalid notifications and clear the immediate function pointer cache */
    Com_ProcessRxFctPtrCache(&immediateFctPtrCacheStrct);       /* SBSW_COM_FCTPTR_CACHE_PTR_1 */
#  endif

    COM_DUMMY_STATEMENT(immediateFctPtrCacheStrct);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  }     /* Immediate signal processing */
# endif
}       /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (COM_RXDEFERREDEVENTCACHE == STD_ON)
/**********************************************************************************************************************
  Com_RxIndication_CacheDeferredEvent
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_RxIndication_CacheDeferredEvent(Com_RxDeferredEventCacheType ComPduId)
{
  /* #10 If an entry is free in the deferred event cache, store the passed ComIPdu in the next free cache entry */
  if(Com_GetRxNextEventCacheEnty() < Com_GetSizeOfRxDeferredEventCache())
  {
    Com_SetRxDeferredEventCache(Com_GetRxNextEventCacheEnty(), ComPduId);       /* SBSW_COM_ARRAY_WRITEACCESS */
    Com_IncRxNextEventCacheEnty();      /* SBSW_COM_CSL_VAR_ACCESS */
  }
  /* #20 Otherwise mark the cache as overflowed */
  else
  {
    Com_SetRxNextEventCacheEnty(COM_NO_HANDLERXPDUDEFERREDIDXOFRXPDUINFO);      /* SBSW_COM_CSL_VAR_ACCESS */
  }
}
#endif

#if (COM_GWEVENTCACHE == STD_ON)
/**********************************************************************************************************************
  Com_RxIndication_CacheDeferredDescriptionGwEvent
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_RxIndication_CacheDeferredDescriptionGwEvent(PduIdType ComPduId)
{
  /* #10 If a gateway description exists for this PDU */
  if(Com_IsGwTxPduDescriptionInfoUsedOfRxPduInfo(ComPduId))     /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    /* #20 If PDU Id is not already cached */
    if(Com_GetHandleRxDeferredGwDescription(Com_GetHandleRxDeferredGwDescriptionIdxOfRxPduInfo(ComPduId)) == 0u)
    {
      /* #30 If cache is not full */
      if(Com_GetGwEventCacheIndex() < Com_GetSizeOfGwEventCache())
      {
        /* #40 Store PDU Id in cache, increase gateway cache index */
        Com_SetGwEventCache(Com_GetGwEventCacheIndex(), ComPduId);      /* SBSW_COM_GWCACHING */
        Com_IncGwEventCacheIndex();     /* SBSW_COM_CSL_VAR_ACCESS */
      }
    }

    /* #50 Mark pdu a cached by storing current length + 1 */
    Com_SetHandleRxDeferredGwDescription(Com_GetHandleRxDeferredGwDescriptionIdxOfRxPduInfo(ComPduId), Com_GetHandleRxPduDeferred(Com_GetHandleRxPduDeferredIdxOfRxPduInfo(ComPduId))); /* SBSW_COM_CSL03 */
  }
}
#endif


/**********************************************************************************************************************
  GLOBAL FUNCTIONS
**********************************************************************************************************************/

#if (COM_TRIGGER_TRANSMIT_API == STD_ON)
/**********************************************************************************************************************
  Com_TriggerTransmit_Process
**********************************************************************************************************************/
/*! Internal comment removed.
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
**********************************************************************************************************************/
FUNC(Std_ReturnType, COM_CODE) Com_TriggerTransmit_Process(PduIdType TxPduId, P2VAR(PduInfoType, AUTOMATIC, COM_APPL_VAR) PduInfoPtr)
{
  uint8 retVal = E_NOT_OK;      /* PRQA S 2981 */ /* MD_MSR_RetVal */
  PduInfoType PduInfo;
# if (COM_TXPDUINFO == STD_ON)  /* COV_COM_VAR_DEPENDENT_SWITCH */
  /* #05 If the PDU length fits into the passed buffer */
  if(PduInfoPtr->SduLength >= Com_GetTxSduLength(TxPduId))
  {
    PduInfo.SduDataPtr = NULL_PTR;      /* PRQA S 2982 */ /* MD_Com_2982 */
    /* #10 If the ComIPdu is not a Zero Byte PDU, set the SduDataPtr to PDU buffer address otherwise set the SduDataPtr to NULL_PTR */
    if(Com_IsTxBufferUsedOfTxPduInfo(TxPduId))  /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
    {
      PduInfo.SduDataPtr = Com_GetAddrTxBuffer(Com_GetTxBufferStartIdxOfTxPduInfo(TxPduId));
    }

    /* #20 Set the SduLength to the current TxSduLength */
    PduInfo.SduLength = (PduLengthType) Com_GetTxSduLength(TxPduId);

    SchM_Enter_Com_COM_EXCLUSIVE_AREA_TX();

    /* \trace CREQ-103166 */
#  if  (COM_TXPDUTTCALLOUTFUNCPTRUSEDOFTXPDUINFO == STD_ON)
    /* #30 If a IPdu trigger transmit callout is configured */
    if(Com_IsTxPduTTCalloutFuncPtrUsedOfTxPduInfo(TxPduId))     /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
    {
      /* #40 Call the trigger transmit callout with the PduInfo (if ASR 4.1.x callouts are enabled) or with the SduDataPtr */
      Com_TxPduTTCalloutFuncPtrIdxOfTxPduInfoType idx = Com_GetTxPduTTCalloutFuncPtrIdxOfTxPduInfo(TxPduId);
#   if (COM_IPDUCALLOUT_USEPDUINFOPTR == STD_ON)
      (void) Com_GetTxPduTTCalloutFuncPtr(idx) (TxPduId, (P2VAR(PduInfoType, AUTOMATIC, AUTOMATIC)) & PduInfo); /* SBSW_COM_FCT_PTR_CALL_CSL03 */
#   else
      (void) Com_GetTxPduTTCalloutFuncPtr(idx) (TxPduId, (P2VAR(uint8, AUTOMATIC, AUTOMATIC)) PduInfo.SduDataPtr);      /* SBSW_COM_FCT_PTR_CALL_CSL03 */
#   endif
    }
#  endif

    /* #50 Copy the PDU buffer data to the provided pointer */
    VStdLib_MemCpy_s(PduInfoPtr->SduDataPtr, Com_GetTxBufferLengthOfTxPduInfo(TxPduId), PduInfo.SduDataPtr, PduInfo.SduLength); /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_COM_VSTDLIB_SAFE */

#  if (COM_EXISTS_TRIGGER_TRANSMIT_CLRUBOFTXPDUINFO == STD_ON)
    /* #60 If the Update Bit clear context is TRIGGER_TRANSMIT, clear the Update Bits */
    if(COM_TRIGGER_TRANSMIT_CLRUBOFTXPDUINFO == Com_GetClrUbOfTxPduInfo(TxPduId))
    {
      Com_TxBuffer_ClearUpdateBits(TxPduId);
    }
#  endif
    SchM_Exit_Com_COM_EXCLUSIVE_AREA_TX();
    /* #70 Set the provided SduLength pointer to the value of the current SduLength */
    PduInfoPtr->SduLength = PduInfo.SduLength;  /* SBSW_COM_PTR_API */
    /* #80 Return E_OK If the ComIPduGroup is active */
    if(Com_IsTxPduGrpActive(TxPduId))
    {
      retVal = E_OK;
    }
  }
# endif

  COM_DUMMY_STATEMENT(TxPduId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(PduInfoPtr);      /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  return retVal;
}
#endif

#if((COM_TXTPINFOUSEDOFTXPDUINFO == STD_ON) || (COM_TX_CONFIRMATION_API == STD_ON))
/**********************************************************************************************************************
  Com_TxConfirmation_Process
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxConfirmation_Process(PduIdType TxPduId)
{
  boolean doNotificationProcessing = FALSE;     /* PRQA S 2981 */ /* MD_MSR_RetVal */

  SchM_Enter_Com_COM_EXCLUSIVE_AREA_TX();

# if ((COM_TXTPINFOUSEDOFTXPDUINFO == STD_ON) && (COM_EXISTS_CONFIRMATION_CLRUBOFTXPDUINFO == STD_ON))
  if(COM_CONFIRMATION_CLRUBOFTXPDUINFO == Com_GetClrUbOfTxPduInfo(TxPduId))
  {
    Com_TxBuffer_ClearUpdateBits(TxPduId);
  }
# endif

  /* \trace SPEC-2736844 */
  if(Com_IsTxPduGrpActive(TxPduId))     /* COV_COM_TP_ONLY */
  {
# if ((COM_MINIMUMDELAYOFTXMODEINFO == STD_ON) || (COM_REPCNTOFTXMODETRUE == STD_ON) || (COM_REPCNTOFTXMODEFALSE == STD_ON))
    if(Com_TxModeHdlr_Confirmation(TxPduId) == TRUE)    /* PRQA S 2991, 2995 */ /* MD_Com_2991, MD_Com_2995 */ /* COV_COM_REPETITIVE_TRANSMISSION */
# endif
    {
      doNotificationProcessing = TRUE;
# if (COM_TXTOUTINFOUSEDOFTXPDUINFO == STD_ON)

      Com_TxDlMon_TxConfirmation(TxPduId);
# endif
    }
  }

  SchM_Exit_Com_COM_EXCLUSIVE_AREA_TX();

# if ((COM_CBKTXERRFUNCPTRINDUSEDOFTXPDUINFO == STD_ON)||(COM_CBKTXACKIMFUNCPTRINDUSEDOFTXPDUINFO == STD_ON)||(COM_CBKTXACKDEFFUNCPTRINDUSEDOFTXPDUINFO == STD_ON))
  if(doNotificationProcessing == TRUE)
  {
    Com_TxNHdlr_Confirmation(TxPduId);
  }
# else
  COM_DUMMY_STATEMENT(doNotificationProcessing);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
# endif

  COM_DUMMY_STATEMENT(TxPduId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}
#endif

#if (COM_TXTPINFOUSEDOFTXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_ResetTxTpConnection
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_ResetTxTpConnection(PduIdType PduId)
{
  Com_TxTpInfoIdxOfTxPduInfoType txTpPduInfoIdx = Com_GetTxTpInfoIdxOfTxPduInfo(PduId);
  Com_SetTxTpConnectionState(txTpPduInfoIdx, COM_READY_TXTPCONNECTIONSTATE);    /* SBSW_COM_CSL02 */
  Com_SetTxTpWrittenBytesCounter(txTpPduInfoIdx, 0u);   /* SBSW_COM_CSL02 */
}
#endif

#if (COM_TXPDUINFO == STD_ON)
/**********************************************************************************************************************
Com_TxLLIf_Transmit
**********************************************************************************************************************/
/*! Internal comment removed.
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
 *

**********************************************************************************************************************/
FUNC(Std_ReturnType, COM_CODE) Com_TxLLIf_Transmit(PduIdType ComTxPduId)        /* PRQA S 1505 */ /* MD_MSR_Rule8.7 */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  PduInfoType PduInfo;

# if (COM_TXPDUCALLOUTFUNCPTRUSEDOFTXPDUINFO == STD_ON)
  boolean CalloutResult;
# endif

  PduInfo.SduDataPtr = NULL_PTR;        /* PRQA S 2982 */ /* MD_Com_2982 */

# if (COM_TXBUFFERUSEDOFTXPDUINFO == STD_ON)
  /* #10 If the ComIPdu is no zero byte PDU */
  if(Com_IsTxBufferUsedOfTxPduInfo(ComTxPduId)) /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
#  if (COM_TXTPINFOUSEDOFTXPDUINFO == STD_ON && COM_TXBUFFERMETADATAUSEDOFTXPDUINFO == STD_ON)
    /* For TP transmission with meta data, point to meta data */
    /* #20 If the ComIPdu is a TP PDU AND has configured meta data */
    if(Com_IsTxTpInfoUsedOfTxPduInfo(ComTxPduId) && Com_IsTxBufferMetaDataUsedOfTxPduInfo(ComTxPduId))  /* COV_COM_TP_ONLY */
    {
      /* #30 Set the SduDataPtr to the meta data */
      PduInfo.SduDataPtr = Com_GetAddrTxBuffer(Com_GetTxBufferMetaDataStartIdxOfTxPduInfo(ComTxPduId));
    }
    else
#  endif
    {
      /* #40 otherwise, set the SduDataPtr to the PDU data buffer */
      PduInfo.SduDataPtr = Com_GetAddrTxBuffer(Com_GetTxBufferStartIdxOfTxPduInfo(ComTxPduId));
    }
  }
  /* #60 otherwise set the SduDataPtr to NULL_PTR */
# endif

# if (COM_TXTPINFOUSEDOFTXPDUINFO == STD_ON)
  /* #80 If the ComIPdu is a TP PDU */
  if(Com_IsTxTpInfoUsedOfTxPduInfo(ComTxPduId)) /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    /* #90 Set the SduLength, if the ComIPdu is in READY state. Otherwise skip transmission */
    Com_TxTpInfoIdxOfTxPduInfoType txTpPduInfoIdx = Com_GetTxTpInfoIdxOfTxPduInfo(ComTxPduId);
    if(Com_GetTxTpConnectionState(txTpPduInfoIdx) == COM_READY_TXTPCONNECTIONSTATE)     /* COV_COM_PERIODIC_PDU_REQUIRED */
    {
      /* \trace SPEC-2736903 */
      PduInfo.SduLength = (PduLengthType) Com_GetTxSduLength(ComTxPduId);
    }
    else
    {
      /* \trace SPEC-2736899 */
      retVal = E_NOT_OK;
    }
  }
  /* #100 otherwise, set the SduLength to the current TxSduLength or to the PDU length with meta data length (if configured) */
  else
# endif
  {
# if (COM_TXBUFFERMETADATAUSEDOFTXPDUINFO == STD_ON)
    /* meta data exists and it is not TP, use length with meta data */
    PduInfo.SduLength = Com_GetPduWithMetaDataLengthOfTxPduInfo(ComTxPduId);
# else
    /* no meta data exists or it is TP, use IPduLength */
    PduInfo.SduLength = (PduLengthType) Com_GetTxSduLength(ComTxPduId);
# endif
  }
# if (COM_TXTPINFOUSEDOFTXPDUINFO == STD_ON)
  /* #120 If the ComIPdu is not a TP PDU or was initially already in READY state */
  if(retVal == E_OK)    /* COV_COM_PERIODIC_PDU_REQUIRED */
# endif
  {
# if (COM_TXPDUCALLOUTFUNCPTRUSEDOFTXPDUINFO == STD_ON)
    /* #130 Call the configured callout function */
    CalloutResult = Com_TxLLIf_GetTxPduCalloutFuncPtr(ComTxPduId, &PduInfo);    /* SBSW_COM_FCTCALL_STACKPTR */

    /* #140 If the callout return value is positive */
    if(CalloutResult == TRUE)
# endif
    {
# if (COM_TXTPINFOUSEDOFTXPDUINFO == STD_ON)
      /* #150 If the ComIPdu is a TP PDU, set the state variable to TRANSMISSION_STARTED or to WAITING_FOR_CONFIRMATION for zero-sized Pdu */
      if(Com_IsTxTpInfoUsedOfTxPduInfo(ComTxPduId))     /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
      {
#  if (COM_EXISTS_UINT8_DYN_APPLTYPEOFTXSIGINFO == STD_ON)
        if(Com_GetTxSduLength(ComTxPduId) == 0u)
        {
          Com_SetTxTpConnectionState(Com_GetTxTpInfoIdxOfTxPduInfo(ComTxPduId), COM_WAITING_FOR_CONFIRMATION_TXTPCONNECTIONSTATE);      /* SBSW_COM_CSL02_CSL03 */
        }
        else
#  endif
        {
          Com_SetTxTpConnectionState(Com_GetTxTpInfoIdxOfTxPduInfo(ComTxPduId), COM_TRANSMISSION_STARTED_TXTPCONNECTIONSTATE);  /* SBSW_COM_CSL02_CSL03 */
        }
      }
# endif
# if (COM_CBKTXERRFUNCPTRINDUSEDOFTXPDUINFO == STD_ON)
      /* #160 Set the WaitingForConfirmation flag */
      Com_SetWaitingForConfirmation(ComTxPduId, TRUE);  /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
# endif
      /* #170 Initiate the transmit of a ComIPdu by a call of PduR_ComTransmit */
      retVal = PduR_ComTransmit(Com_GetExternalIdOfTxPduInfo(ComTxPduId), &PduInfo);    /* SBSW_COM_FCTCALL_STACKPTR */

# if ((COM_MIXEDMODEPERIODICSUPPRESSION == STD_ON) || (COM_STRICT_REPETITION_PERIOD == STD_ON) || (COM_TXTPINFOUSEDOFTXPDUINFO == STD_ON) || (COM_MINIMUMDELAYOFTXMODEINFO == STD_ON) || (COM_EXISTS_TRANSMIT_CLRUBOFTXPDUINFO == STD_ON) || (COM_CBKTXERRFUNCPTRINDUSEDOFTXPDUINFO == STD_ON))
      /* #180 Set ComIPdu Attributes depending on the value of retVal */
      Com_TxLLIf_SetTxAttributes(ComTxPduId, retVal);
# endif
    }

# if (COM_TXBUFFERMETADATAUSEDOFTXPDUINFO == STD_ON)
    /* write default meta data to buffer, ignoring the result of the transmission */
    /* #190 Set the meta data buffer back to the meta data initial value (If meta data feature is enabled) */
    Com_TxLLIf_CpyInitMetaDataToBffr(ComTxPduId);
# endif
  }
  return retVal;
}
#endif

#if ((COM_TXTPINFOUSEDOFTXPDUINFO == STD_ON) && (COM_CANCELLATIONSUPPORTOFTXPDUINFO == STD_ON))
/**********************************************************************************************************************
  Com_TxLLIf_CancelTransmit
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxLLIf_CancelTransmit(PduIdType ComTxPduId)
{
  /* #10 If cancellation support is configured for the ComIPdu */
  if(Com_IsCancellationSupportOfTxPduInfo(ComTxPduId))
  {
    /* #20 Cancel the transmission by a call of PduR_ComCancelTransmit */
    (void) PduR_ComCancelTransmit(Com_GetExternalIdOfTxPduInfo(ComTxPduId));
  }
}
#endif

#if (COM_TXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_TxLLIf_InitTxIpdu
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxLLIf_InitTxIpdu(Com_TxPduInfoIterType ComPduId)
{
# if(COM_TXTPINFOUSEDOFTXPDUINFO == STD_ON)
  /* #10 If I-Pdu is TP Pdu */
  if(Com_IsTxTpInfoUsedOfTxPduInfo(ComPduId))   /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    /* #20 Initialize TP variables of one ComIPdu */
    Com_TxTpInfoIdxOfTxPduInfoType txTpPduInfoIdx = Com_GetTxTpInfoIdxOfTxPduInfo(ComPduId);

#  if (COM_TXSIGINFODYNSIGUSEDOFTXTPINFO == STD_ON)
    /* #30 If ComIPdu contains a dynamic length signal */
    if(Com_IsTxSigInfoDynSigUsedOfTxTpInfo(txTpPduInfoIdx))     /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
    {

      /* #40 Initialize the ComIpdu length with the initial dynamic length */
      Com_SetTxSduLength(ComPduId, (Com_TxSduLengthType) (Com_GetStartByteInPduPositionOfTxSigInfo(Com_GetTxSigInfoDynSigIdxOfTxTpInfo(txTpPduInfoIdx)) + ((Com_TxSduLengthType) Com_GetDynamicInitialLengthOfTxTpInfo(txTpPduInfoIdx))));      /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
      Com_SetTxTmpTpPduLength(txTpPduInfoIdx, (Com_TxSduLengthType) (Com_GetStartByteInPduPositionOfTxSigInfo(Com_GetTxSigInfoDynSigIdxOfTxTpInfo(txTpPduInfoIdx)) + ((Com_TxSduLengthType) Com_GetDynamicInitialLengthOfTxTpInfo(txTpPduInfoIdx))));   /* SBSW_COM_CSL02 */
      Com_SetTxDynSignalLength(txTpPduInfoIdx, Com_GetDynamicInitialLengthOfTxTpInfo(txTpPduInfoIdx));  /* SBSW_COM_CSL02 */
    }
    /* #50 otherwise */
    else
#  endif
    {
      /* #60 Initialize the ComIpdu length with the initial fixed length */
#  if (COM_TXSIGINFODYNSIGUSEDOFTXTPINFO == STD_ON)
      Com_SetTxTmpTpPduLength(txTpPduInfoIdx, Com_GetBufferSizeOfTxTpInfo(txTpPduInfoIdx));     /* SBSW_COM_CSL02 */
#  endif
      Com_SetTxSduLength(ComPduId, (Com_TxSduLengthType) Com_GetBufferSizeOfTxTpInfo(txTpPduInfoIdx));  /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
    }
  }
  /* #70 otherwise */
  else
# endif
  {
    /* #80 Initialize the ComIpdu length with the initial fixed length */
# if (COM_TXBUFFERUSEDOFTXPDUINFO == STD_ON)
    Com_SetTxSduLength(ComPduId, (Com_TxSduLengthType) Com_GetTxBufferLengthOfTxPduInfo(ComPduId));     /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
# else
    Com_SetTxSduLength(ComPduId, 0);    /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
# endif
  }
}
#endif

#if (COM_RXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxIndication_Processing
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(boolean, COM_CODE) Com_RxIndication_Processing(PduIdType RxPduId, P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr)
{
  boolean retVal = FALSE;

  /* #10 If the ComIPdu is active */
  if(Com_IsRxPduGrpActive(RxPduId))     /* COV_COM_NO_IPDUGROUPS */ /* PRQA S 2842 */ /* MD_Com_2842 */ /* \trace SPEC-2736845 */ /* \trace SPEC-2736846 */
  {
    retVal = TRUE;
    /* \trace CREQ-103160 */
# if (COM_RXPDUCALLOUTFUNCPTRUSEDOFRXPDUINFO == STD_ON)
    /* Rx I-PDU callout.  */
    /* #20 Call callout function if configured */
    if(Com_IsRxPduCalloutFuncPtrUsedOfRxPduInfo(RxPduId))       /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
    {
      Com_RxPduCalloutFuncPtrIdxOfRxPduInfoType idx = Com_GetRxPduCalloutFuncPtrIdxOfRxPduInfo(RxPduId);
      /* Call the callout with the PduInfo (if ASR 4.1.x callouts are enabled) or with the SduDataPtr */
#  if (COM_IPDUCALLOUT_USEPDUINFOPTR == STD_ON)
      retVal = Com_GetRxPduCalloutFuncPtr(idx) (RxPduId, (P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA)) PduInfoPtr);  /* SBSW_COM_FCT_PTR_CALL_CSL03 */
#  else
      retVal = Com_GetRxPduCalloutFuncPtr(idx) (RxPduId, (P2CONST(uint8, AUTOMATIC, COM_APPL_DATA)) PduInfoPtr->SduDataPtr);    /* SBSW_COM_FCT_PTR_CALL_CSL03 */
#  endif
    }

    /* #40 If the callout result is positive or not configured */
    if(retVal == TRUE)
# endif
    {
      PduInfoType PduInfoLocal;
      PduInfoLocal.SduDataPtr = PduInfoPtr->SduDataPtr;
      PduInfoLocal.SduLength = PduInfoPtr->SduLength;

# if(COM_METADATALENGTHOFRXPDUINFO == STD_ON)
      PduInfoLocal.SduLength -= Com_GetMetaDataLengthOfRxPduInfo(RxPduId);
# endif

# if (COM_GENERATED_DESCRIPTION_ROUTING == STD_ON)      /* COV_COM_VAR_ELISA_STD_OFF_XF */
      /* #50 Call the Com_RxGwIndication to process the ComDescription routings */
      Com_RxGwIndication(RxPduId, &PduInfoLocal);       /* SBSW_COM_FCTCALL_WITH_P2CONST */
# endif
      /* #60 Call Com_RxIndication_ProcessPdu to process the passed Rx ComIPdu */
      Com_RxIndication_ProcessPdu(RxPduId, &PduInfoLocal);      /* SBSW_COM_FCTCALL_WITH_P2CONST */
    }   /* Rx I-PDU callout */
  }     /* Active check */

  return retVal;
}
#endif

#if (COM_RXTPINFOUSEDOFRXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_TpRxIndication_Processing
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TpRxIndication_Processing(PduIdType PduId, Std_ReturnType Result)
{
  boolean resetRequired = FALSE;
  Com_RxTpInfoIdxOfRxPduInfoType rxTpPduInfoIdx = Com_GetRxTpInfoIdxOfRxPduInfo(PduId);

  switch (Com_GetRxTpConnectionState(rxTpPduInfoIdx))
  {
      /* #10 If RXTPCONNECTIONSTATE is COPYING or RECEPTION_STARTED, reset Tp connection. */
    case COM_RECEPTION_STARTED_RXTPCONNECTIONSTATE:
    case COM_COPYING_RXTPCONNECTIONSTATE:
    {
      resetRequired = TRUE;
      break;
    }
      /* #20 If RXTPCONNECTIONSTATE is WAITING_FOR_INDICATION */
    case COM_WAITING_FOR_INDICATION_RXTPCONNECTIONSTATE:
    {
      /* #30 If the passed Result is negative, reset TP connection. */
      if(Result != E_OK)
      {
        resetRequired = TRUE;
      }
      /* #40 Otherwise the Rx TP ComIPdu reception was successful */
      else
      {
        PduInfoType rxPduInfo;
        rxPduInfo.SduDataPtr = Com_GetAddrRxTpBuffer(Com_GetRxTpBufferStartIdxOfRxTpInfo(rxTpPduInfoIdx));
        rxPduInfo.SduLength = Com_GetRxTpSduLength(rxTpPduInfoIdx);

# if (COM_RXTPBUFFERMETADATAUSEDOFRXTPINFO == STD_ON)
        /* #45 If meta data is configured, add meta data length */
        rxPduInfo.SduLength += Com_GetMetaDataLengthOfRxPduInfo(PduId);
# endif

        /* #50 If deferred processing is required, set RxTpConnectionState to BUFFER_LOCKED. */
# if (COM_EXISTS_DEFERRED_SIGNALPROCESSINGOFRXPDUINFO == STD_ON)
        if(Com_IsHandleRxPduDeferredUsedOfRxPduInfo(PduId))     /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
        {
          Com_SetRxTpConnectionState(rxTpPduInfoIdx, COM_BUFFER_LOCKED_RXTPCONNECTIONSTATE);    /* SBSW_COM_CSL02 */
          resetRequired = !Com_RxIndication_Processing(PduId, &rxPduInfo);      /* SBSW_COM_FCTCALL_WITH_P2CONST */
        }
        else
# endif
          /* #60 Otherwise initiate processing and reset TP machine afterwards. */
        {
          (void) Com_RxIndication_Processing(PduId, &rxPduInfo);        /* SBSW_COM_FCTCALL_WITH_P2CONST */
          resetRequired = TRUE;
        }
      }
      break;
    }
      /* #70 Do nothing if RxTpConnectionState is BUFFER_LOCKED or READY */
    default:
    {
      /* Do nothing. */
      break;
    }
  }

  /* Reset TP state machine if required. */
  if(resetRequired == TRUE)
  {
    SchM_Enter_Com_COM_EXCLUSIVE_AREA_RX();
    Com_ResetRxTpConnection(PduId);
    SchM_Exit_Com_COM_EXCLUSIVE_AREA_RX();
  }
}
#endif

#if (COM_RXTPINFOUSEDOFRXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_ResetRxTpConnection
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_ResetRxTpConnection(PduIdType PduId)
{
  Com_RxTpInfoIdxOfRxPduInfoType rxTpPduInfoIdx = Com_GetRxTpInfoIdxOfRxPduInfo(PduId);

# if (COM_EXISTS_DEFERRED_SIGNALPROCESSINGOFRXPDUINFO == STD_ON)
  if(Com_IsHandleRxPduDeferredUsedOfRxPduInfo(PduId))   /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    /* #10 Reset the "Handle Deferred" flag */
    Com_SetHandleRxPduDeferred(Com_GetHandleRxPduDeferredIdxOfRxPduInfo(PduId), 0);     /* SBSW_COM_CSL03 */
  }
# endif

  /* #20 Reset WrittenBytesCounter, TpSduLength and TP Connection state */
  Com_SetRxTpWrittenBytesCounter(rxTpPduInfoIdx, 0);    /* SBSW_COM_CSL02 */
  Com_SetRxTpSduLength(rxTpPduInfoIdx, 0);      /* SBSW_COM_CSL02 */
  Com_SetRxTpConnectionState(rxTpPduInfoIdx, COM_READY_RXTPCONNECTIONSTATE);    /* SBSW_COM_CSL02 */
}
#endif

#if (COM_RXTPINFOUSEDOFRXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_CopyRxData_Processing
**********************************************************************************************************************/
/*!  Internal comment removed.
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
**********************************************************************************************************************/
FUNC(BufReq_ReturnType, COM_CODE) Com_CopyRxData_Processing(PduIdType PduId, CONSTP2VAR(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPointer, P2VAR(PduLengthType, AUTOMATIC, COM_APPL_VAR) RxBufferSizePtr)   /* PRQA S 3673 */ /* MD_MSR_Rule8.13 */
{
  /* ----- Local Variables ---------------------------------------------- */
  BufReq_ReturnType bufReq_status = BUFREQ_E_NOT_OK;    /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If I-PDU is active */
  if(Com_IsRxPduGrpActive(PduId))       /* \trace SPEC-2736846 */
  {
    Com_RxTpInfoIdxOfRxPduInfoType rxTpPduInfoIdx = Com_GetRxTpInfoIdxOfRxPduInfo(PduId);

    /* #20 If RxTpConnectionState is RECEPTION_STARTED, set RxTpConnectionState to COPYING */
    if(Com_GetRxTpConnectionState(rxTpPduInfoIdx) == COM_RECEPTION_STARTED_RXTPCONNECTIONSTATE)
    {
      Com_SetRxTpConnectionState(rxTpPduInfoIdx, COM_COPYING_RXTPCONNECTIONSTATE);      /* SBSW_COM_CSL02 */
    }

    switch (Com_GetRxTpConnectionState(rxTpPduInfoIdx))
    {
        /* #30 If RxTpConnectionState is COPYING */
      case COM_COPYING_RXTPCONNECTIONSTATE:
      {
        /* #40 If segment fits into buffer */
        if(PduInfoPointer->SduLength <= (Com_GetRxTpSduLength(rxTpPduInfoIdx) - Com_GetRxTpWrittenBytesCounter(rxTpPduInfoIdx)))
        {
          /* #50 Copy the passed bytes to the buffer, update the written bytes counter and set the passed RxBufferSizePtr value to the remaining receive buffer size */
          VStdMemCpyRamToRam(Com_GetAddrRxTpBuffer(Com_GetRxTpBufferStartIdxOfRxTpInfo(rxTpPduInfoIdx) + Com_GetRxTpWrittenBytesCounter(rxTpPduInfoIdx)), PduInfoPointer->SduDataPtr, PduInfoPointer->SduLength);       /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_COM_WRITEACCESS_STACKPTR_CONFIG_LENGTH */
          Com_SetRxTpWrittenBytesCounter(rxTpPduInfoIdx, (Com_GetRxTpWrittenBytesCounter(rxTpPduInfoIdx) + PduInfoPointer->SduLength)); /* SBSW_COM_CSL02 */
          *RxBufferSizePtr = (Com_GetBufferSizeOfRxTpInfo(rxTpPduInfoIdx) - Com_GetRxTpWrittenBytesCounter(rxTpPduInfoIdx));    /* SBSW_COM_PTR_API */
# if (COM_RXTPBUFFERMETADATAUSEDOFRXTPINFO == STD_ON)
          /* #60 If meta data is configured adapt the RxBufferSizePtr */
          *RxBufferSizePtr -= Com_GetMetaDataLengthOfRxPduInfo(PduId);  /* SBSW_COM_PTR_API */
# endif
          /* #70 If the expected amount of bytes is received, set Rx Tp ComIPdu state to WAITING_FOR_INDICATION */
          if(Com_GetRxTpSduLength(rxTpPduInfoIdx) == Com_GetRxTpWrittenBytesCounter(rxTpPduInfoIdx))
          {
            Com_SetRxTpConnectionState(rxTpPduInfoIdx, COM_WAITING_FOR_INDICATION_RXTPCONNECTIONSTATE); /* SBSW_COM_CSL02 */
          }
          bufReq_status = BUFREQ_OK;
        }
        break;
      }
        /* #80 Else-If RxTpConnectionState is WAITING_FOR_INDICATION */
      case COM_WAITING_FOR_INDICATION_RXTPCONNECTIONSTATE:
      {
        /* #90 If zero-sized segment is provided, do nothing, otherwise reset state machine */
        if(PduInfoPointer->SduLength == 0u)
        {
          *RxBufferSizePtr = 0u;        /* SBSW_COM_PTR_API */
          bufReq_status = BUFREQ_OK;
        }
        else
        {
          SchM_Enter_Com_COM_EXCLUSIVE_AREA_RX();
          Com_ResetRxTpConnection(PduId);
          SchM_Exit_Com_COM_EXCLUSIVE_AREA_RX();
        }
        break;
      }
        /* #100 Else do nothing */
      default:
      {
        /* READY or BUFFER_LOCKED - Do nothing */
        break;
      }
    }
  }

  return bufReq_status;
}       /* PRQA S 6030, 6080 */ /* MD_MSR_STCYC, MD_MSR_STMIF */
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

/**********************************************************************************************************************
 *  END OF FILE: Com_LLIf.c
 *********************************************************************************************************************/
