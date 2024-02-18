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
/*!        \file  Com_TxModeHdlr.c
 *        \brief  MICROSAR Communication source file
 *
 *      \details  This is the implementation of the MICROSAR Communication module.
 *                The basic software module is based on the AUTOSAR Communication specification.
 *
 *********************************************************************************************************************/

#define COM_TXMODEHDLR_SOURCE

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
#include "Com.h"
#include "Com_LLIf.h"
#include "Com_Timer.h"
#include "Com_TxModeHdlr.h"
#include "SchM_Com.h"
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

#if (COM_TXMODEINFO == STD_ON)
# if ((COM_PERIODICOFTXMODETRUE == STD_ON) || (COM_PERIODICOFTXMODEFALSE == STD_ON) || (COM_REPCNTOFTXMODETRUE == STD_ON) || (COM_REPCNTOFTXMODEFALSE == STD_ON) || (COM_MINIMUMDELAYOFTXMODEINFO == STD_ON))
/**********************************************************************************************************************
  Com_TxModeHdlr_EnterExclusiveArea_CycleCounter
**********************************************************************************************************************/
/*! \brief    This function enters the tx cyclic processing exclusive area.
    \details  -
    \pre      -
    \trace    DSGN-COM_ISRTHRESHOLD_CONCEPT
    \context  TASK
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_TxModeHdlr_EnterExclusiveArea_CycleCounter(void);

/**********************************************************************************************************************
  Com_TxModeHdlr_ExitExclusiveArea_CycleCounter
**********************************************************************************************************************/
/*! \brief    This function exits the tx cyclic processing exclusive area.
    \details  -
    \pre      -
    \trace    DSGN-COM_ISRTHRESHOLD_CONCEPT
    \context  TASK
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_TxModeHdlr_ExitExclusiveArea_CycleCounter(void);

/**********************************************************************************************************************
  Com_TxModeHdlr_ThresholdCheck_CycleCounter
**********************************************************************************************************************/
/*! \brief    This function checks if the ISR Lock must be opened
    \details  -
    \pre      -
    \trace    DSGN-COM_ISRTHRESHOLD_CONCEPT
    \context  TASK
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_TxModeHdlr_ThresholdCheck_CycleCounter(void);
# endif

/**********************************************************************************************************************
  Com_TxModeHdlr_EnterExclusiveArea
**********************************************************************************************************************/
/*! \brief    This function enters the tx processing exclusive area.
    \details  -
    \pre      -
    \trace    DSGN-COM_ISRTHRESHOLD_CONCEPT
    \context  TASK
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_TxModeHdlr_EnterExclusiveArea(void);

/**********************************************************************************************************************
  Com_TxModeHdlr_ExitExclusiveArea
**********************************************************************************************************************/
/*! \brief    This function exits the tx processing exclusive area.
    \details  -
    \pre      -
    \trace    DSGN-COM_ISRTHRESHOLD_CONCEPT
    \context  TASK
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_TxModeHdlr_ExitExclusiveArea(void);

/**********************************************************************************************************************
  Com_TxModeHdlr_ThresholdCheck
**********************************************************************************************************************/
/*! \brief    This function checks if the ISR Lock must be opened
    \details  -
    \pre      -
    \trace    DSGN-COM_ISRTHRESHOLD_CONCEPT
    \context  TASK
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_TxModeHdlr_ThresholdCheck(void);

/**********************************************************************************************************************
  Com_TxModeHdlr_MainFunctionTx_ProcessTransmit
**********************************************************************************************************************/
/*! \brief        This function process the transmit requests of provided ComTxPduId.
    \details      -
    \pre          -
    \param[in]    ComTxPduId    ID of Tx I-PDU.
    \context      TASK
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_TxModeHdlr_MainFunctionTx_ProcessTransmit(PduIdType ComTxPduId);
#endif

#if ((COM_PERIODICOFTXMODETRUE == STD_ON) || (COM_PERIODICOFTXMODEFALSE == STD_ON) || (COM_REPCNTOFTXMODETRUE == STD_ON) || (COM_REPCNTOFTXMODEFALSE == STD_ON) || (COM_MINIMUMDELAYOFTXMODEINFO == STD_ON))
/**********************************************************************************************************************
  Com_TxModeHdlr_SetTransmitRequestAndCycleCnt
**********************************************************************************************************************/
/*! \brief        This function processes the cyclic transmission for the passed ComTxPdu.
    \details      -
    \pre          -
    \param[in]    ComTxPduId ID of Tx I-PDU.
    \context      TASK
    \trace        SPEC-2736819
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_TxModeHdlr_SetTransmitRequestAndCycleCnt(PduIdType ComTxPduId);
#endif

#if ((COM_PERIODICOFTXMODETRUE == STD_ON) || (COM_PERIODICOFTXMODEFALSE == STD_ON))
/**********************************************************************************************************************
  Com_TxModeHdlr_ProcessCyclicPdu
**********************************************************************************************************************/
/*! \brief        This function processes the cyclic transmission for the passed ComTxPdu.
    \details      -
    \pre          -
    \param[in]    ComTxPduId ID of Tx I-PDU.
    \param[out]   transmitRequest  Pointer to transmit request boolean flag.
    \context      TASK
    \trace        SPEC-2736819
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_TxModeHdlr_ProcessCyclicPdu(PduIdType ComTxPduId, P2VAR(Com_TransmitRequestType, AUTOMATIC, COM_APPL_VAR) transmitRequest);
#endif

#if ((COM_REPCNTOFTXMODETRUE == STD_ON) || (COM_REPCNTOFTXMODEFALSE == STD_ON))
/**********************************************************************************************************************
  Com_TxModeHdlr_ProcessRepetitions
**********************************************************************************************************************/
/*! \brief        This function processes the repetitions for the passed ComTxPdu.
    \details      -
    \pre          -
    \param[in]    ComTxPduId ID of Tx I-PDU.
    \param[out]   transmitRequest  Pointer to transmit request boolean flag.
    \context      TASK
    \trace        SPEC-2736819
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_TxModeHdlr_ProcessRepetitions(PduIdType ComTxPduId, P2VAR(Com_TransmitRequestType, AUTOMATIC, COM_APPL_VAR) transmitRequest);
#endif


/**********************************************************************************************************************
  LOCAL FUNCTIONS
**********************************************************************************************************************/

#if (COM_TXMODEINFO == STD_ON)
# if ((COM_PERIODICOFTXMODETRUE == STD_ON) || (COM_PERIODICOFTXMODEFALSE == STD_ON) || (COM_REPCNTOFTXMODETRUE == STD_ON) || (COM_REPCNTOFTXMODEFALSE == STD_ON) || (COM_MINIMUMDELAYOFTXMODEINFO == STD_ON))
/**********************************************************************************************************************
  Com_TxModeHdlr_EnterExclusiveArea_CycleCounter
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_TxModeHdlr_EnterExclusiveArea_CycleCounter(void)
{
  /* #10 Enter the tx cyclic processing exclusive area */
  SchM_Enter_Com_COM_EXCLUSIVE_AREA_TX();
}

/**********************************************************************************************************************
  Com_TxModeHdlr_ExitExclusiveArea_CycleCounter
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_TxModeHdlr_ExitExclusiveArea_CycleCounter(void)
{
  /* #05 Reload the counter with the threshold value */
  Com_SetTxCyclicProcessingISRLockCounter(Com_GetTxCyclicProcessingISRLockThreshold()); /* SBSW_COM_CSL_VAR_ACCESS */
  /* #10 Exit the tx cyclic processing exclusive area */
  SchM_Exit_Com_COM_EXCLUSIVE_AREA_TX();
}

/**********************************************************************************************************************
  Com_TxModeHdlr_ThresholdCheck_CycleCounter
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_TxModeHdlr_ThresholdCheck_CycleCounter(void)
{
  if(Com_GetTxCyclicProcessingISRLockCounter() > 0u)
  {
    Com_DecTxCyclicProcessingISRLockCounter();  /* SBSW_COM_CSL_VAR_ACCESS */
  }
  else
  {
    Com_TxModeHdlr_ExitExclusiveArea_CycleCounter();
    Com_TxModeHdlr_EnterExclusiveArea_CycleCounter();
  }
}
# endif

/**********************************************************************************************************************
  Com_TxModeHdlr_EnterExclusiveArea
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_TxModeHdlr_EnterExclusiveArea(void)
{
  /* #10 Enter the tx processing exclusive area */
  SchM_Enter_Com_COM_EXCLUSIVE_AREA_TX();
}

/**********************************************************************************************************************
  Com_TxModeHdlr_ExitExclusiveArea
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_TxModeHdlr_ExitExclusiveArea(void)
{
  /* #05 Reload the counter with the threshold value */
  Com_SetTxProcessingISRLockCounter(Com_GetTxProcessingISRLockThreshold());     /* SBSW_COM_CSL_VAR_ACCESS */
  /* #10 Exit the tx processing exclusive area */
  SchM_Exit_Com_COM_EXCLUSIVE_AREA_TX();
}

/**********************************************************************************************************************
  Com_TxModeHdlr_ThresholdCheck
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_TxModeHdlr_ThresholdCheck(void)
{
  if(Com_GetTxProcessingISRLockCounter() > 0u)  /* COV_COM_THRESHOLD_TX */
  {
    Com_DecTxProcessingISRLockCounter();        /* SBSW_COM_CSL_VAR_ACCESS */
  }
  else
  {
    Com_TxModeHdlr_ExitExclusiveArea();
    Com_TxModeHdlr_EnterExclusiveArea();
  }
}

/**********************************************************************************************************************
  Com_TxModeHdlr_MainFunctionTx_ProcessTransmit
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_TxModeHdlr_MainFunctionTx_ProcessTransmit(PduIdType ComTxPduId)
{
  /* #10 If the passed Tx ComIPdu is active, the MDT has expired and a transmit request is set */
  if(Com_IsTxPduGrpActive(ComTxPduId))  /* COV_COM_NO_IPDUGROUPS */
  {

# if (COM_MINIMUMDELAYOFTXMODEINFO == STD_ON)
    /* Delay Time and Transmission Handling */
    if(Com_GetDelayTimeCnt(ComTxPduId) == 0u)
# endif
    {
      if(Com_IsTransmitRequest(ComTxPduId))
      {
        /* #20 Trigger the transmission by a call of Com_TxLLIf_Transmit check if the return of Com_TxLLIf_Transmit is positive, if ComRetryFailedTransmitRequest is enabled */
# if (COM_RETRY_FAILED_TRANSMIT_REQUESTS == STD_ON)
        if(Com_TxLLIf_Transmit(ComTxPduId) == E_OK)
# else
        (void) Com_TxLLIf_Transmit(ComTxPduId);
# endif
        {
          /* #30 Reset the transmit request */
          Com_SetTransmitRequest(ComTxPduId, FALSE);    /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
        }
      }
    }
  }
}
#endif

#if ((COM_PERIODICOFTXMODETRUE == STD_ON) || (COM_PERIODICOFTXMODEFALSE == STD_ON) || (COM_REPCNTOFTXMODETRUE == STD_ON) || (COM_REPCNTOFTXMODEFALSE == STD_ON) || (COM_MINIMUMDELAYOFTXMODEINFO == STD_ON))
/**********************************************************************************************************************
  Com_TxModeHdlr_SetTransmitRequestAndCycleCnt
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_TxModeHdlr_SetTransmitRequestAndCycleCnt(PduIdType ComTxPduId)
{
  Com_TransmitRequestType transmitRequest = Com_IsTransmitRequest(ComTxPduId);

# if ((COM_PERIODICOFTXMODETRUE == STD_ON) || (COM_PERIODICOFTXMODEFALSE == STD_ON))
  Com_TxModeHdlr_ProcessCyclicPdu(ComTxPduId, &transmitRequest);        /* SBSW_COM_FCTCALL_STACKPTR */
# endif

# if ((COM_REPCNTOFTXMODETRUE == STD_ON) || (COM_REPCNTOFTXMODEFALSE == STD_ON))
  Com_TxModeHdlr_ProcessRepetitions(ComTxPduId, &transmitRequest);      /* SBSW_COM_FCTCALL_STACKPTR */
# endif

  Com_SetTransmitRequest(ComTxPduId, transmitRequest);  /* SBSW_COM_CSL01 */

# if (COM_MINIMUMDELAYOFTXMODEINFO == STD_ON)
  if(Com_GetDelayTimeCnt(ComTxPduId) != 0u)
  {
    Com_DecDelayTimeCnt(ComTxPduId);    /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
  }
# endif
}
#endif

#if ((COM_PERIODICOFTXMODETRUE == STD_ON) || (COM_PERIODICOFTXMODEFALSE == STD_ON))
/**********************************************************************************************************************
  Com_TxModeHdlr_ProcessCyclicPdu
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_TxModeHdlr_ProcessCyclicPdu(PduIdType ComTxPduId, P2VAR(Com_TransmitRequestType, AUTOMATIC, COM_APPL_VAR) transmitRequest)
{
  /* #10 If the passed Tx ComIPdu is in a cyclic Pdu, decrement the cycle counter */
  if(Com_IsCyclicSendRequest(ComTxPduId))       /* COV_COM_ONLY_CYCLIC_PDU */
  {
    Com_DecCycleTimeCnt(ComTxPduId);    /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
    /* #20 If the cycle counter is 0, set the transmit flag and reload the cycle counter */
    if(Com_GetCycleTimeCnt(ComTxPduId) == 0u)
    {
      *transmitRequest = TRUE;  /* SBSW_COM_WRITEACCESS_STACKPTR_01 */

      Com_SetCycleTimeCnt(ComTxPduId, (Com_CycleTimeCntType) Com_TxModeHdlr_GetCurrentTimePeriod(ComTxPduId));  /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */ /* COV_COM_SETCYCLETIMECOUNT */

# if (COM_EXISTS_NORMAL_MODEOFTXTOUTINFO == STD_ON)
      /* #30 Reload Tx Deadline monitoring timer if configured */
      Com_TxModeHdlr_ReloadTxDlMonCounter(ComTxPduId);
# endif
    }
  }
}
#endif

#if ((COM_REPCNTOFTXMODETRUE == STD_ON) || (COM_REPCNTOFTXMODEFALSE == STD_ON))
/**********************************************************************************************************************
  Com_TxModeHdlr_ProcessRepetitions
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_TxModeHdlr_ProcessRepetitions(PduIdType ComTxPduId, P2VAR(Com_TransmitRequestType, AUTOMATIC, COM_APPL_VAR) transmitRequest)
{
  /* #10 If the repetition count is greater 0, decrement the repetition cycle counter */
  if(Com_GetRepCnt(ComTxPduId) > 0u)    /* COV_COM_NONTRIGGERED_REPETITION */
  {
# if (COM_MIXEDMODEPERIODICSUPPRESSION == STD_ON)
    if(!Com_IsInitialTransmit(ComTxPduId))
    {
      *transmitRequest = FALSE; /* SBSW_COM_WRITEACCESS_STACKPTR_01 */
    }
# endif

    Com_DecRepCycleCnt(ComTxPduId);     /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
    /* #20 If the repetition cycle counter is equal 0, set a transmit request and reload the repetition cycle counter */
    if(Com_GetRepCycleCnt(ComTxPduId) == 0u)
    {
      *transmitRequest = TRUE;  /* SBSW_COM_WRITEACCESS_STACKPTR_01 */
      /* reload the repetition cycle time counter */
      Com_SetRepCycleCnt(ComTxPduId, Com_TxModeHdlr_GetCurrentRepetitionPeriod(ComTxPduId));    /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
    }
  }
}
#endif


/**********************************************************************************************************************
  GLOBAL FUNCTIONS
**********************************************************************************************************************/

#if (COM_TXMODEINFO == STD_ON)
/**********************************************************************************************************************
  Com_TxModeHdlr_InitTxIpdu
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
FUNC(void, COM_CODE) Com_TxModeHdlr_InitTxIpdu(PduIdType ComPduId)
{
# if (COM_TXSIGINFOFILTERINITVALUEINDENDIDXOFTXMODEINFO == STD_ON)
  {
    /* \trace SPEC-2736775 */
    /* #10 Iterate overall related tx filter infos and set the old filter value to the initial value, the buffer is ApplType specific */
    Com_TxSigInfoFilterInitValueIndEndIdxOfTxModeInfoType idxTxSigInfoFilterInitValueInd = Com_GetTxSigInfoFilterInitValueIndStartIdxOfTxModeInfo(ComPduId);
    for(; idxTxSigInfoFilterInitValueInd < Com_GetTxSigInfoFilterInitValueIndEndIdxOfTxModeInfo(ComPduId); idxTxSigInfoFilterInitValueInd++)
    {
      Com_SignalIdType idxTxSigInfo = (Com_SignalIdType) Com_GetTxSigInfoFilterInitValueInd(idxTxSigInfoFilterInitValueInd);
#  if(COM_FILTERINITVALUEUSEDOFTXSIGINFO == STD_ON)
      if(Com_IsFilterInitValueUsedOfTxSigInfo(idxTxSigInfo))    /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
      {
        Com_FilterInitValueIdxOfTxSigInfoType idxTxFilterOldValue = Com_GetFilterInitValueIdxOfTxSigInfo(idxTxSigInfo);
        switch (Com_GetApplTypeOfTxSigInfo(idxTxSigInfo))
        {
#   if (COM_TXFILTERINITVALUEUINT8 == STD_ON)
          case COM_UINT8_APPLTYPEOFTXSIGINFO:
          {
            Com_SetTxFilterOldValueUInt8(idxTxFilterOldValue, Com_GetTxFilterInitValueUInt8(idxTxFilterOldValue));      /* SBSW_COM_CSL02 */
            break;
          }
#   endif
#   if (COM_TXFILTERINITVALUESINT8 == STD_ON)
          case COM_SINT8_APPLTYPEOFTXSIGINFO:
          {
            Com_SetTxFilterOldValueSInt8(idxTxFilterOldValue, Com_GetTxFilterInitValueSInt8(idxTxFilterOldValue));      /* SBSW_COM_CSL02 */
            break;
          }
#   endif
#   if (COM_TXFILTERINITVALUEUINT16 == STD_ON)
          case COM_UINT16_APPLTYPEOFTXSIGINFO:
          {
            Com_SetTxFilterOldValueUInt16(idxTxFilterOldValue, Com_GetTxFilterInitValueUInt16(idxTxFilterOldValue));    /* SBSW_COM_CSL02 */
            break;
          }
#   endif
#   if (COM_TXFILTERINITVALUESINT16 == STD_ON)
          case COM_SINT16_APPLTYPEOFTXSIGINFO:
          {
            Com_SetTxFilterOldValueSInt16(idxTxFilterOldValue, Com_GetTxFilterInitValueSInt16(idxTxFilterOldValue));    /* SBSW_COM_CSL02 */
            break;
          }
#   endif
#   if (COM_TXFILTERINITVALUEUINT32 == STD_ON)
          case COM_UINT32_APPLTYPEOFTXSIGINFO:
          {
            Com_SetTxFilterOldValueUInt32(idxTxFilterOldValue, Com_GetTxFilterInitValueUInt32(idxTxFilterOldValue));    /* SBSW_COM_CSL02 */
            break;
          }
#   endif
#   if (COM_TXFILTERINITVALUESINT32 == STD_ON)
          case COM_SINT32_APPLTYPEOFTXSIGINFO:
          {
            Com_SetTxFilterOldValueSInt32(idxTxFilterOldValue, Com_GetTxFilterInitValueSInt32(idxTxFilterOldValue));    /* SBSW_COM_CSL02 */
            break;
          }
#   endif
#   if (COM_TXFILTERINITVALUEUINT64 == STD_ON)
          case COM_UINT64_APPLTYPEOFTXSIGINFO:
          {
            Com_SetTxFilterOldValueUInt64(idxTxFilterOldValue, Com_GetTxFilterInitValueUInt64(idxTxFilterOldValue));    /* SBSW_COM_CSL02 */
            break;
          }
#   endif
#   if (COM_TXFILTERINITVALUESINT64 == STD_ON)
          case COM_SINT64_APPLTYPEOFTXSIGINFO:
          {
            Com_SetTxFilterOldValueSInt64(idxTxFilterOldValue, Com_GetTxFilterInitValueSInt64(idxTxFilterOldValue));    /* SBSW_COM_CSL02 */
            break;
          }
#   endif
#   if (COM_TXFILTERINITVALUEFLOAT32 == STD_ON)
          case COM_FLOAT32_APPLTYPEOFTXSIGINFO:
          {
            Com_SetTxFilterOldValueFloat32(idxTxFilterOldValue, Com_GetTxFilterInitValueFloat32(idxTxFilterOldValue));  /* SBSW_COM_CSL02 */
            break;
          }
#   endif
#   if (COM_TXFILTERINITVALUEFLOAT64 == STD_ON)
          case COM_FLOAT64_APPLTYPEOFTXSIGINFO:
          {
            Com_SetTxFilterOldValueFloat64(idxTxFilterOldValue, Com_GetTxFilterInitValueFloat64(idxTxFilterOldValue));  /* SBSW_COM_CSL02 */
            break;
          }
#   endif
          default:     /* COV_COM_MISRA */
            break;
        }
      }
#  endif
#  if ((COM_TXFILTERINITVALUEARRAYBASEDFILTERINITVALUEUSEDOFTXSIGINFO == STD_ON) && (COM_EXISTS_UINT8_N_APPLTYPEOFTXSIGINFO == STD_ON))
      if(Com_IsTxFilterInitValueArrayBasedFilterInitValueUsedOfTxSigInfo(idxTxSigInfo)) /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
      {
        switch (Com_GetApplTypeOfTxSigInfo(idxTxSigInfo))
        {
          case COM_UINT8_N_APPLTYPEOFTXSIGINFO:
          {
            Com_TxFilterInitValueArrayBasedIterType bufferIdx = Com_GetTxFilterInitValueArrayBasedFilterInitValueStartIdxOfTxSigInfo(idxTxSigInfo);
            VStdMemCpyRamToRam(Com_GetAddrTxFilterOldValueArrayBased(bufferIdx), Com_GetAddrTxFilterInitValueArrayBased(bufferIdx), Com_GetTxFilterInitValueArrayBasedFilterInitValueLengthOfTxSigInfo(idxTxSigInfo));  /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_COM_CSL03 */
            break;
          }
          default:     /* COV_COM_MISRA */
            break;
        }
      }
#  endif
    }
  }
# endif
# if (COM_FILTERINFOIDXOFTXSIGINFO == STD_ON)
  {
    /* #20 Iterate overall related tx filter states and set them to their initial state */
    Com_TxFilterInitStateEndIdxOfTxModeInfoType idxTxFilterInitState = Com_GetTxFilterInitStateStartIdxOfTxModeInfo(ComPduId);
    for(; idxTxFilterInitState < Com_GetTxFilterInitStateEndIdxOfTxModeInfo(ComPduId); idxTxFilterInitState++)
    {
      Com_SetTxFilterState(idxTxFilterInitState, Com_IsTxFilterInitState(idxTxFilterInitState));        /* SBSW_COM_CSL02 */
    }
  }
# endif
  /* #30 Set the initial Tx Mode of the passed Tx ComIPdu, initialize that mode and remove the transmit request */
  Com_SetCurrentTxMode(ComPduId, Com_IsInitModeOfTxModeInfo(ComPduId)); /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
  Com_TxModeHdlr_InitTxMode(ComPduId);
  Com_SetTransmitRequest(ComPduId, FALSE);      /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */

# if ((COM_PERIODICOFTXMODETRUE == STD_ON) || (COM_PERIODICOFTXMODEFALSE == STD_ON))
  /* #40 If the current tx mode is a cyclic tx mode, set the cycle counter to the start delay time */
  if(Com_IsCyclicSendRequest(ComPduId)) /* COV_COM_CYCLIC_SEND_REQUEST */
  {
    Com_SetCycleTimeCnt(ComPduId, (Com_CycleTimeCntType) Com_TxModeHdlr_GetCurrentTimeOffset(ComPduId));        /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */ /* COV_COM_SETCYCLETIMECOUNT */
  }
# endif
# if (COM_MINIMUMDELAYOFTXMODEINFO == STD_ON)
  /* #50 Set the minimum delay counter to 0 */
  Com_SetDelayTimeCnt(ComPduId, 0u);    /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
# endif
  /* #60 Clear eventbased trigger Flag if configured */
# if (COM_DIRECTTRIGGER == STD_ON)
  Com_SetDirectTrigger(ComPduId, FALSE);        /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
# endif
}       /* PRQA S 6010, 6030 */ /* MD_MSR_STPTH , MD_MSR_STCYC */
#endif

#if ((COM_PERIODICOFTXMODETRUE == STD_ON) || (COM_PERIODICOFTXMODEFALSE == STD_ON) || (COM_REPCNTOFTXMODETRUE == STD_ON) || (COM_REPCNTOFTXMODEFALSE == STD_ON) || (COM_MINIMUMDELAYOFTXMODEINFO == STD_ON))
/**********************************************************************************************************************
  Com_TxModeHdlr_MainFunctionTx_CycleCounter
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxModeHdlr_MainFunctionTx_CycleCounter(void)
{
  Com_TxCyclicPduIterType ComTxCyclicPduIterator = 0u;
  Com_TxPduInfoIdxOfTxCyclicPduType ComTxPduId;

  Com_TxModeHdlr_EnterExclusiveArea_CycleCounter();
  /* #10 Iterate over all Tx Pdu Infos */
  for(; ComTxCyclicPduIterator < Com_GetSizeOfTxCyclicPdu(); ComTxCyclicPduIterator++)
  {
    ComTxPduId = Com_GetTxPduInfoIdxOfTxCyclicPdu(ComTxCyclicPduIterator);
    {
      /* #20 If the Tx ComIPdu is active, process the cyclic transmission mode, the repetition counter and the MDT counter */
      if(Com_IsTxPduGrpActive(ComTxPduId))
      {
        Com_TxModeHdlr_SetTransmitRequestAndCycleCnt((PduIdType) ComTxPduId);
      }
    }
    Com_TxModeHdlr_ThresholdCheck_CycleCounter();
  }
  Com_TxModeHdlr_ExitExclusiveArea_CycleCounter();
}
#endif

#if (COM_TXMODEINFO == STD_ON)
/**********************************************************************************************************************
  Com_TxModeHdlr_MainFunctionTx_Transmit
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxModeHdlr_MainFunctionTx_Transmit(void)
{
  PduIdType ComTxPduId;
  Com_TxModeHdlr_EnterExclusiveArea();

  /* #10 Iterate over all Tx ComIPdus and process the related transmit requests */
  for(ComTxPduId = 0u; ComTxPduId < Com_GetSizeOfTxPduInfo(); ComTxPduId++)
  {
# if (COM_INVALIDHNDOFTXPDUINFO == STD_ON)
    if(!Com_IsInvalidHndOfTxPduInfo(ComTxPduId))
# endif
    {
      Com_TxModeHdlr_MainFunctionTx_ProcessTransmit(ComTxPduId);
    }
    Com_TxModeHdlr_ThresholdCheck();
  }
  Com_TxModeHdlr_ExitExclusiveArea();
}
#endif

#if (COM_TXMODEINFO == STD_ON)
/**********************************************************************************************************************
  Com_TxModeHdlr_InitTxMode
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
FUNC(void, COM_CODE) Com_TxModeHdlr_InitTxMode(CONST(PduIdType, AUTOMATIC) ComTxPduId)
{
# if ((COM_PERIODICOFTXMODETRUE == STD_ON) || (COM_PERIODICOFTXMODEFALSE == STD_ON))
  /* #10 If the current tx mode of the passed Tx ComIPdu is periodic */
  if(Com_TxModeHdlr_IsPeriodicTxMode(ComTxPduId) == TRUE)
  {
    Com_SetCyclicSendRequest(ComTxPduId, TRUE); /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
    /* #20 Enable the cyclic send request and trigger the first transmission within the next Com_MainfunctionTx call */
#  if (COM_MINIMUMDELAYOFTXMODEINFO == STD_ON)
    Com_SetTransmitRequest(ComTxPduId, TRUE);   /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
    Com_SetCycleTimeCnt(ComTxPduId, (Com_CycleTimeCntType) (Com_TxModeHdlr_GetCurrentTimePeriod(ComTxPduId) + Com_GetDelayTimeCnt(ComTxPduId) + 1u));   /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */ /* COV_COM_SETCYCLETIMECOUNT */

#   if (COM_EXISTS_NORMAL_MODEOFTXTOUTINFO == STD_ON)
    /* #30 Reload Tx Deadline monitoring timer if configured */
    Com_TxModeHdlr_ReloadTxDlMonCounter(ComTxPduId);
#   endif
#  else
    Com_SetCycleTimeCnt(ComTxPduId, (Com_CycleTimeCntType) 1u); /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
#  endif
  }
  /* #40 Otherwise disable the cyclic send request and remove the transmit request flag */
  else
  {
    Com_SetCyclicSendRequest(ComTxPduId, FALSE);        /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
    Com_SetTransmitRequest(ComTxPduId, FALSE);  /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
  }
# else
  Com_SetTransmitRequest(ComTxPduId, FALSE);    /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
# endif

# if ((COM_REPCNTOFTXMODETRUE == STD_ON) || (COM_REPCNTOFTXMODEFALSE == STD_ON))
  /* #50 Set the repetition counter to 0 */
  Com_SetRepCnt(ComTxPduId, 0u);        /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
# endif

# if (COM_EXISTS_NORMAL_MODEOFTXTOUTINFO == STD_ON)
  /* #60 Reset the tx timeout counter */
  Com_TxDlMon_SwitchIpduTxMode(ComTxPduId);
# endif
}

# if (COM_TXFILTERINITSTATEUSEDOFTXMODEINFO == STD_ON)
/**********************************************************************************************************************
  Com_TxModeHdlr_UpdateTMS
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxModeHdlr_UpdateTMS(CONST(PduIdType, AUTOMATIC) idxTxModeInfo)
{
  boolean newTxMode = FALSE;    /* PRQA S 2981 */ /* MD_MSR_RetVal */
  Com_TxFilterInitStateEndIdxOfTxModeInfoType filterIndex = Com_GetTxFilterInitStateStartIdxOfTxModeInfo(idxTxModeInfo);

  /* #10 Iterate over all related filter states, if at least one filter state is true, the Tx Mode true is active. Otherwise the Tx Mode false is active */
  for(; filterIndex < Com_GetTxFilterInitStateEndIdxOfTxModeInfo(idxTxModeInfo); filterIndex++)
  {
    if(Com_IsTxFilterState(filterIndex))
    {
      newTxMode = TRUE;
      break;
    }
  }

  /* #20 If the Tx Mode has changed */
  if(Com_IsCurrentTxMode(idxTxModeInfo) != newTxMode)   /* COV_COM_TX_FILTER */
  {
    /* #30 Update the current Tx Mode with the new Tx Mode, initialize the new Tx Mode and trigger a deferred transmission without repetitions */
    Com_SetCurrentTxMode(idxTxModeInfo, newTxMode);     /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */

    Com_TxModeHdlr_InitTxMode(idxTxModeInfo);
#  if ((COM_DIRECTOFTXMODETRUE == STD_ON) || (COM_DIRECTOFTXMODEFALSE == STD_ON))
    /* COM582: If a change of the TMS causes a change of the transmission mode to the transmission mode DIRECT an immediate, respecting the MDT, direct/ n-times transmission to the underlying layer shall be initiated. */
    Com_TxModeHdlr_TriggerDeferredTransmitAndSetTimer(idxTxModeInfo, FALSE);
#  endif
  }
}
# endif

# if ((COM_MINIMUMDELAYOFTXMODEINFO == STD_ON) || (COM_REPCNTOFTXMODETRUE == STD_ON) || (COM_REPCNTOFTXMODEFALSE == STD_ON))
/**********************************************************************************************************************
  Com_TxModeHdlr_Confirmation
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
**********************************************************************************************************************/
FUNC(boolean, COM_CODE) Com_TxModeHdlr_Confirmation(CONST(PduIdType, AUTOMATIC) ComTxPduId)
{
  boolean retVal = TRUE;        /* PRQA S 2981 */ /* MD_MSR_RetVal */

#  if (COM_MINIMUMDELAYOFTXMODEINFO == STD_ON)
  /* #10 Reload the minimum delay time counter of the passed Tx ComIPdu */

#   if (COM_DIRECTTRIGGER == STD_ON)
  if(Com_IsDirectTrigger(ComTxPduId))
#   endif
  {     /* \trace SPEC-2736859 */
    Com_SetDelayTimeCnt(ComTxPduId, Com_GetMinimumDelayOfTxModeInfo(ComTxPduId));       /* SBSW_COM_IDXPARAM_INTERNALFCT_DET_CSL02 */
#   if (COM_DIRECTTRIGGER == STD_ON)
    Com_SetDirectTrigger(ComTxPduId, FALSE);    /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
#   endif
  }
#  endif
#  if ((COM_REPCNTOFTXMODETRUE == STD_ON) || (COM_REPCNTOFTXMODEFALSE == STD_ON))

  /* #20 Check if the all requested transmits have been performed and this is the final Tx Confirmation */
  if(0u < Com_GetRepCnt(ComTxPduId))    /* COV_COM_REPETITIONS */
  {
    Com_DecRepCnt(ComTxPduId);  /* SBSW_COM_IDXPARAM_INTERNALFCT_DET_CSL02 */
    if(0u < Com_GetRepCnt(ComTxPduId))
    {
      /* this is the first or an intermediate confirmation for an N-Times transmission return false to avoid notification of the upper layer */
      retVal = FALSE;
    }
  }
#  endif
  return retVal;
}
# endif

/**********************************************************************************************************************
  Com_TxModeHdlr_StopTxIpdus
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxModeHdlr_StopTxIpdus(CONST(PduIdType, AUTOMATIC) ComTxPduId)
{
  /* #10 Reset transmit request, set repetition counter and repetition cycle counter to 0 */
  Com_SetTransmitRequest(ComTxPduId, FALSE);    /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
# if ((COM_REPCNTOFTXMODETRUE == STD_ON) || (COM_REPCNTOFTXMODEFALSE == STD_ON))
  Com_SetRepCnt(ComTxPduId, 0u);        /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
  Com_SetRepCycleCnt(ComTxPduId, 0u);   /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
# endif
# if ((COM_PERIODICOFTXMODETRUE == STD_ON) || (COM_PERIODICOFTXMODEFALSE == STD_ON))
  /* #20 reload the time offset counter and set minimum delay time to 0. If the I-PDU is started again, the time offset is already set */
  Com_SetCycleTimeCnt(ComTxPduId, (Com_CycleTimeCntType) Com_TxModeHdlr_GetCurrentTimeOffset(ComTxPduId));      /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */ /* COV_COM_TIMEOFFSET */
# endif

# if (COM_MINIMUMDELAYOFTXMODEINFO == STD_ON)
  Com_SetDelayTimeCnt(ComTxPduId, 0u);  /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
# endif
}
#endif

#if (COM_TXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_TxModeHdlr_TriggerIpduSendOnceDeferred
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxModeHdlr_TriggerIpduSendOnceDeferred(CONST(PduIdType, AUTOMATIC) ComTxPduId)
{
  /* #10 If the passed Tx ComIPdu is active */
  if(Com_IsTxPduGrpActive(ComTxPduId))  /* COV_COM_NO_IPDUGROUPS */
  {
    /* #20 Set eventbased trigger Flag if configured */
# if (COM_DIRECTTRIGGER == STD_ON)
    Com_SetDirectTrigger(ComTxPduId, TRUE);     /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
# endif
    /* #30 Set the related transmit request */
    Com_SetTransmitRequest(ComTxPduId, TRUE);   /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */

# if(COM_MIXEDMODEPERIODICSUPPRESSION == STD_ON)
    Com_SetInitialTransmit(ComTxPduId, TRUE);   /* SBSW_COM_CSL02 */
# endif
# if (COM_TXTOUTINFO == STD_ON)
    /* #40 Reload Tx Deadline monitoring timer if configured */
    Com_TxModeHdlr_ReloadTxDlMonCounter(ComTxPduId);
# endif
  }
}
#endif

#if (COM_GWTIMEOUTINFO == STD_ON)
/**********************************************************************************************************************
  Com_TxModeHdlr_StopCyclicTransmission
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxModeHdlr_StopCyclicTransmission(CONST(PduIdType, AUTOMATIC) ComTxPduId)      /* PRQA S 1505 */ /* MD_MSR_Rule8.7 */
{
  /* #10 Stop the cyclic transmission */
  Com_TxModeHdlr_StopTxIpdus(ComTxPduId);
  Com_SetCyclicSendRequest(ComTxPduId, FALSE);  /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
}

/**********************************************************************************************************************
  Com_TxModeHdlr_StartCyclicTransmission
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxModeHdlr_StartCyclicTransmission(CONST(PduIdType, AUTOMATIC) ComTxPduId)     /* PRQA S 1505 */ /* MD_MSR_Rule8.7 */
{
  /* #10 Enable the cyclic send transmission */
  if(!Com_IsCyclicSendRequest(ComTxPduId))
  {
    Com_SetCyclicSendRequest(ComTxPduId, TRUE); /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
    Com_SetCycleTimeCnt(ComTxPduId, 1u);        /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
  }
}
#endif

#if ((((COM_DIRECTOFTXMODETRUE == STD_ON) || (COM_DIRECTOFTXMODEFALSE == STD_ON)) && ((COM_FILTERINFOUSEDOFTXSIGINFO == STD_ON) || (COM_GWTXPDUDESCRIPTIONINFOUSEDOFRXPDUINFO == STD_ON) || (COM_GENERATED_DESCRIPTION_ROUTING == STD_ON)))|| (COM_ONCHANGEUSEDOFTXSIGINFO == STD_ON)||(COM_TRIGGEREDOFTXSIGINFO == STD_ON))    /* COV_COM_VAR_ELISA_STD_OFF_TF_tf_tf_tf_tf_xf_tf_tf */
/**********************************************************************************************************************
  Com_TxModeHdlr_TriggerDeferredTransmitAndSetTimer
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
FUNC(void, COM_CODE) Com_TxModeHdlr_TriggerDeferredTransmitAndSetTimer(CONST(PduIdType, AUTOMATIC) ComTxPduId, boolean TriggerWithoutRepetition)        /* PRQA S 1505 */ /* MD_MSR_Rule8.7 */
{
  /* If the passed Tx ComIPdu is active and the current tx mode is direct */
  if(Com_IsTxPduGrpActive(ComTxPduId))  /* COV_COM_TXIPDUGROUP_ACTIVE */
  {
    if(Com_TxModeHdlr_IsDirectTxMode(ComTxPduId) == TRUE)       /* COV_COM_ISDIRECT_TXMODE */
    {
      /* Set eventbased trigger Flag if configured */
# if (COM_DIRECTTRIGGER == STD_ON)
      Com_SetDirectTrigger(ComTxPduId, TRUE);   /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
# endif
# if ((COM_REPCNTOFTXMODETRUE == STD_ON) || (COM_REPCNTOFTXMODEFALSE == STD_ON))
      /* If the passed Tx ComIPdu is triggered without repetitions, set the transmit request and reload the Tx Deadline Monitoring timer if not already running */
      if(TriggerWithoutRepetition == TRUE)      /* COV_COM_DEFERREDIPDUSEND */
      {
#  if (COM_EXISTS_NORMAL_MODEOFTXTOUTINFO == STD_ON)
        Com_TxModeHdlr_ReloadTxDlMonCounter(ComTxPduId);
#  endif
        Com_SetTransmitRequest(ComTxPduId, TRUE);       /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
      }
      /* Otherwise, set the repetition count to the tx mode dependent repetition count value */
      else
      {
        Com_SetRepCnt(ComTxPduId, Com_TxModeHdlr_GetCurRepCnt(ComTxPduId));     /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
        /* If the repetition count is greater 0, set the repetition cycle counter to 1. Otherwise set the transmit request */
        if(0u < Com_GetRepCnt(ComTxPduId))      /* COV_COM_ZERO_REPETITION */
        {
#  if (COM_EXISTS_NORMAL_MODEOFTXTOUTINFO == STD_ON)
          /* SPEC-2736884 */
          if(Com_IsTxTOutInfoUsedOfTxPduInfo(ComTxPduId))       /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
          {
            /* Reload Tx Deadline Monitoring counter if configured */
            Com_TxTOutInfoIdxOfTxPduInfoType idxTxTOutInfo = Com_GetTxTOutInfoIdxOfTxPduInfo(ComTxPduId);
            Com_SetTxTOutCnt(idxTxTOutInfo, Com_GetFactorOfTxTOutInfo(idxTxTOutInfo));  /* SBSW_COM_CSL02 */
          }
#  endif
          /* trigger first transmission of n repetitive transmissions */
          Com_SetRepCycleCnt(ComTxPduId, 1u);   /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
#  if (COM_MIXEDMODEPERIODICSUPPRESSION == STD_ON)
          Com_SetInitialTransmit(ComTxPduId, TRUE);     /* SBSW_COM_CSL02 */
#  endif
        }
        else
# endif
        {
# if (COM_EXISTS_NORMAL_MODEOFTXTOUTINFO == STD_ON)
          Com_TxModeHdlr_ReloadTxDlMonCounter(ComTxPduId);
# endif
          Com_SetTransmitRequest(ComTxPduId, TRUE);     /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
        }
# if ((COM_REPCNTOFTXMODETRUE == STD_ON) || (COM_REPCNTOFTXMODEFALSE == STD_ON))
      }
# endif
    }
  }
  COM_DUMMY_STATEMENT(TriggerWithoutRepetition);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}       /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if (COM_TXTOUTINFO == STD_ON)
/**********************************************************************************************************************
  Com_TxModeHdlr_ReloadTxDlMonCounter
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxModeHdlr_ReloadTxDlMonCounter(CONST(PduIdType, AUTOMATIC) ComTxPduId)        /* PRQA S 1505 */ /* MD_MSR_Rule8.7 */
{
  /* #10 If Tx Deadline Monitoring is configured */
  if(Com_IsTxTOutInfoUsedOfTxPduInfo(ComTxPduId))       /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    Com_TxTOutInfoIdxOfTxPduInfoType idxTxTOutInfo = Com_GetTxTOutInfoIdxOfTxPduInfo(ComTxPduId);
    if(Com_GetTxTOutCnt(idxTxTOutInfo) == 0u)
    {
      /* #20 Reload Tx Deadline Monitoring timer if not already running */
      Com_SetTxTOutCnt(idxTxTOutInfo, Com_GetFactorOfTxTOutInfo(idxTxTOutInfo));        /* SBSW_COM_CSL02 */
    }
  }
}
#endif

#if ((COM_REPCNTOFTXMODETRUE == STD_ON) || (COM_REPCNTOFTXMODEFALSE == STD_ON))
/**********************************************************************************************************************
  Com_TxModeHdlr_GetCurRepCnt
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(Com_RepCntType, COM_CODE) Com_TxModeHdlr_GetCurRepCnt(PduIdType TxPduId)   /* PRQA S 1505 */ /* MD_MSR_Rule8.7 */
{
  /* #10 Return the current repetition count depending on the current active tx mode */
# if ((COM_REPCNTOFTXMODETRUE == STD_ON) && (COM_REPCNTOFTXMODEFALSE == STD_ON))
  Com_RepCntType retVal =
    Com_IsCurrentTxMode(TxPduId) ? (Com_RepCntType) Com_GetRepCntOfTxModeTrue(Com_GetTxModeTrueIdxOfTxModeInfo(TxPduId)) : (Com_RepCntType)
    Com_GetRepCntOfTxModeFalse(Com_GetTxModeFalseIdxOfTxModeInfo(TxPduId));
# elif (COM_REPCNTOFTXMODETRUE == STD_ON)
  Com_RepCntType retVal = Com_IsCurrentTxMode(TxPduId) ? (Com_RepCntType) Com_GetRepCntOfTxModeTrue(Com_GetTxModeTrueIdxOfTxModeInfo(TxPduId)) : 0u;
# else
  Com_RepCntType retVal = Com_IsCurrentTxMode(TxPduId) ? 0u : (Com_RepCntType) Com_GetRepCntOfTxModeFalse(Com_GetTxModeFalseIdxOfTxModeInfo(TxPduId));
# endif
  return retVal;
}
#endif

#if ((COM_REPPERIODOFTXMODETRUE == STD_ON) || (COM_REPPERIODOFTXMODEFALSE == STD_ON))
/**********************************************************************************************************************
  Com_TxModeHdlr_GetCurrentRepetitionPeriod
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(Com_RepCycleCntType, COM_CODE) Com_TxModeHdlr_GetCurrentRepetitionPeriod(PduIdType TxPduId)        /* PRQA S 1505 */ /* MD_MSR_Rule8.7 */
{
  /* #10 Return the current repetition period factor depending on the current active tx mode */
# if ((COM_REPPERIODOFTXMODETRUE == STD_ON) && (COM_REPPERIODOFTXMODEFALSE == STD_ON))
  Com_RepCycleCntType retVal =
    Com_IsCurrentTxMode(TxPduId) ? (Com_RepCycleCntType) Com_GetRepPeriodOfTxModeTrue(Com_GetTxModeTrueIdxOfTxModeInfo(TxPduId)) : (Com_RepCycleCntType)
    Com_GetRepPeriodOfTxModeFalse(Com_GetTxModeFalseIdxOfTxModeInfo(TxPduId));
# elif (COM_REPPERIODOFTXMODETRUE == STD_ON)
  Com_RepCycleCntType retVal = Com_IsCurrentTxMode(TxPduId) ? (Com_RepCycleCntType) Com_GetRepPeriodOfTxModeTrue(Com_GetTxModeTrueIdxOfTxModeInfo(TxPduId)) : 0u;
# else
  Com_RepCycleCntType retVal = Com_IsCurrentTxMode(TxPduId) ? 0u : (Com_RepCycleCntType) Com_GetRepPeriodOfTxModeFalse(Com_GetTxModeFalseIdxOfTxModeInfo(TxPduId));
# endif
  return retVal;
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
 *  END OF FILE: Com_TxModeHdlr.c
 *********************************************************************************************************************/
