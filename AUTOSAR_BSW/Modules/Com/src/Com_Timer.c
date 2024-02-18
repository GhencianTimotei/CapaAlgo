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
/*!        \file  Com_Timer.c
 *        \brief  MICROSAR Communication source file
 *
 *      \details  This is the implementation of the MICROSAR Communication module.
 *                The basic software module is based on the AUTOSAR Communication specification.
 *
 *********************************************************************************************************************/
#define COM_TIMER_SOURCE

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
#include "Com.h"
#include "Com_LLIf.h"
#include "Com_Timer.h"
#include "Com_Buffers.h"
#include "Com_TxModeHdlr.h"
#include "Com_RxProcessing.h"
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

#if (COM_GWTIMEOUTINFO == STD_ON)
/**********************************************************************************************************************
  Com_GwTout_TimeoutHasOccurred
**********************************************************************************************************************/
/*! \brief        This function checks if a gateway timeout has occurred
    \details      -
    \pre          -
    \param[in]    gwToutId - Index of GwTimeoutInfo
    \return       boolean
                    true if timeout counter is zero
                    false otherwise
**********************************************************************************************************************/
# define Com_GwTout_TimeoutHasOccurred(gwToutId)  (Com_GetGwRoutingTimeoutCounter(gwToutId) == 0u)

/**********************************************************************************************************************
  Com_GwTout_TimeoutIsActive
**********************************************************************************************************************/
/*! \brief        This function checks if a gateway timer is still active
    \details      -
    \pre          -
    \param[in]    gwToutId - Index of GwTimeoutInfo
    \return       boolean
                    true if timeout counter is greater than zero
                    false otherwise
**********************************************************************************************************************/
# define Com_GwTout_TimeoutIsActive(gwToutId)     (Com_GetGwRoutingTimeoutCounter(gwToutId) > 0u)
#endif

#if (COM_RXTOUTINFO == STD_ON)
/**********************************************************************************************************************
  Com_LMgt_RxIpduDmActive
**********************************************************************************************************************/
/*! \brief        This function evaluates the Deadline Monitoring state of the Rx I-Pdu.
    \details      -
    \pre          -
    \param[in]    ComRxToutObjtId  ID of Rx Timeout object.
    \return       boolean
                  true:   The Deadline Monitoring is enabled for at least one mapped I-Pdu Group
                  false:  The Deadline Monitoring is disabled for all mapped I-Pdu Groups
**********************************************************************************************************************/
# define Com_LMgt_RxIpduDmActive(ComRxToutObjtId)       ((Com_GetRxPduDmState(ComRxToutObjtId) & COM_ACTIVE_RXPDUDMSTATE) == COM_ACTIVE_RXPDUDMSTATE)

/**********************************************************************************************************************
  Com_LMgt_TimeoutOccurred
**********************************************************************************************************************/
/*! \brief        This function sets the Rx Deadline Monitoring State to Occurred.
    \details      -
    \pre          -
    \param[in]    ComRxToutObjtId  ID of Rx Timeout object.
**********************************************************************************************************************/
# define Com_LMgt_TimeoutOccurred(ComRxToutObjtId)  Com_SetRxPduDmState((ComRxToutObjtId), COM_OCCURRED_RXPDUDMSTATE)
#endif

/**********************************************************************************************************************
  LOCAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/

/**********************************************************************************************************************
  LOCAL DATA PROTOTYPES
**********************************************************************************************************************/

/**********************************************************************************************************************
  LOCAL FUNCTION PROTOTYPES
**********************************************************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"    /* PRQA S 5087 */        /* MD_MSR_MemMap */

#if(COM_TXTOUTINFO == STD_ON)
/**********************************************************************************************************************
  Com_TxDlMon_EnterExclusiveArea
**********************************************************************************************************************/
/*! \brief    This function enters the tx deadline monitoring exclusive area.
    \details  -
    \pre      -
    \trace    DSGN-COM_ISRTHRESHOLD_CONCEPT
    \context  TASK
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_TxDlMon_EnterExclusiveArea(void);

/**********************************************************************************************************************
  Com_TxDlMon_ExitExclusiveArea
**********************************************************************************************************************/
/*! \brief    This function exits the tx deadline monitoring exclusive area.
    \details  -
    \pre      -
    \trace    DSGN-COM_ISRTHRESHOLD_CONCEPT
    \context  TASK
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_TxDlMon_ExitExclusiveArea(void);

/**********************************************************************************************************************
  Com_TxDlMon_ThresholdCheck
**********************************************************************************************************************/
/*! \brief    This function checks if the ISR Lock must be opened
    \details  -
    \pre      -
    \trace    DSGN-COM_ISRTHRESHOLD_CONCEPT
    \context  TASK
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_TxDlMon_ThresholdCheck(void);
#endif

#if (COM_RXTOUTINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxDlMon_EnterExclusiveArea
**********************************************************************************************************************/
/*! \brief    This function enters the rx deadline monitoring exclusive area.
    \details  -
    \pre      -
    \trace    DSGN-COM_ISRTHRESHOLD_CONCEPT
    \context  TASK
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_RxDlMon_EnterExclusiveArea(void);

/**********************************************************************************************************************
  Com_RxDlMon_ExitExclusiveArea
**********************************************************************************************************************/
/*! \brief    This function exits the rx deadline monitoring exclusive area.
    \details  -
    \pre      -
    \trace    DSGN-COM_ISRTHRESHOLD_CONCEPT
    \context  TASK
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_RxDlMon_ExitExclusiveArea(void);

/**********************************************************************************************************************
  Com_RxDlMon_ThresholdCheck
**********************************************************************************************************************/
/*! \brief    This function checks if the ISR Lock must be opened
    \details  -
    \pre      -
    \trace    DSGN-COM_ISRTHRESHOLD_CONCEPT
    \context  TASK
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_RxDlMon_ThresholdCheck(void);
#endif

#if (COM_CBKTXTOUTFUNCPTRINDUSEDOFTXTOUTINFO == STD_ON)
/**********************************************************************************************************************
  Com_TxDlMon_TxCallCbkTout
**********************************************************************************************************************/
/*! \brief        This function calls the TxTout callback functions.
 *  \details      -
    \pre          -
    \param[in]    idxTxTOutInfo  Index of TxTOutInfo
    \context      TASK
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_TxDlMon_TxCallCbkTout(Com_SizeOfTxTOutInfoType idxTxTOutInfo);
#endif

#if (COM_RXACCESSINFOREPLACESIGINDENDIDXOFRXTOUTINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxDlMon_SignalTimeoutAction
**********************************************************************************************************************/
/*! \brief        This function sets all related ComSignal replace values of passed timeout pdu.
    \details      -
    \pre          -
    \param[in]    idxRxTOutInfo RxToutInfo handle id
    \context      TASK
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_RxDlMon_SignalTimeoutAction(Com_SizeOfRxTOutInfoType idxRxTOutInfo);
#endif

#if (COM_RXACCESSINFOREPLACEGRPSIGINDENDIDXOFRXTOUTINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxDlMon_GroupSignalTimeoutAction
**********************************************************************************************************************/
/*! \brief        This function sets all related ComGroupSignal replace values of passed timeout pdu.
    \details      -
    \pre          -
    \param[in]    idxRxTOutInfo RxToutInfo handle id
    \context      TASK
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_RxDlMon_GroupSignalTimeoutAction(Com_SizeOfRxTOutInfoType idxRxTOutInfo);
#endif

#if (COM_CBKRXTOUTFUNCPTRINDUSEDOFRXTOUTINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxDlMon_CallTimeOutNotifications
**********************************************************************************************************************/
/*! \brief        This function calls the related timeout notification functions.
    \details      -
    \pre          -
    \param[in]    idxRxTOutInfo RxToutInfo handle id
    \context      TASK
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_RxDlMon_CallTimeOutNotifications(Com_SizeOfRxTOutInfoType idxRxTOutInfo);
#endif


/**********************************************************************************************************************
  LOCAL FUNCTIONS
**********************************************************************************************************************/

#if(COM_TXTOUTINFO == STD_ON)
/**********************************************************************************************************************
  Com_TxDlMon_EnterExclusiveArea
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_TxDlMon_EnterExclusiveArea(void)
{
  /* #10 Enter the tx deadline monitoring exclusive area */
  SchM_Enter_Com_COM_EXCLUSIVE_AREA_TX();
}

/**********************************************************************************************************************
  Com_TxDlMon_ExitExclusiveArea
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_TxDlMon_ExitExclusiveArea(void)
{
  /* #05 Reload the counter with the threshold value */
  Com_SetTxDeadlineMonitoringISRLockCounter(Com_GetTxDeadlineMonitoringISRLockThreshold());     /* SBSW_COM_CSL_VAR_ACCESS */
  /* #10 Exit the tx deadline monitoring exclusive area */
  SchM_Exit_Com_COM_EXCLUSIVE_AREA_TX();
}

/**********************************************************************************************************************
  Com_TxDlMon_ThresholdCheck
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_TxDlMon_ThresholdCheck(void)
{
  if(Com_GetTxDeadlineMonitoringISRLockCounter() > 0u)  /* COV_COM_THRESHOLD_TX */
  {
    Com_DecTxDeadlineMonitoringISRLockCounter();        /* SBSW_COM_CSL_VAR_ACCESS */
  }
  else
  {
    Com_TxDlMon_ExitExclusiveArea();
    Com_TxDlMon_EnterExclusiveArea();
  }
}
#endif

#if(COM_RXTOUTINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxDlMon_EnterExclusiveArea
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_RxDlMon_EnterExclusiveArea(void)
{
  /* #10 Enter the rx deadline monitoring exclusive area */
  SchM_Enter_Com_COM_EXCLUSIVE_AREA_RX();
}

/**********************************************************************************************************************
  Com_RxDlMon_ExitExclusiveArea
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_RxDlMon_ExitExclusiveArea(void)
{
  /* #05 Reload the counter with the threshold value */
  Com_SetRxDeadlineMonitoringISRLockCounter(Com_GetRxDeadlineMonitoringISRLockThreshold());     /* SBSW_COM_CSL_VAR_ACCESS */
  /* #10 Exit the rx deadline monitoring exclusive area */
  SchM_Exit_Com_COM_EXCLUSIVE_AREA_RX();
}

/**********************************************************************************************************************
  Com_RxDlMon_ThresholdCheck
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_RxDlMon_ThresholdCheck(void)
{
  if(Com_GetRxDeadlineMonitoringISRLockCounter() > 0u)
  {
    Com_DecRxDeadlineMonitoringISRLockCounter();        /* SBSW_COM_CSL_VAR_ACCESS */
  }
  else
  {
    Com_RxDlMon_ExitExclusiveArea();
    Com_RxDlMon_EnterExclusiveArea();
  }
}
#endif

#if (COM_CBKTXTOUTFUNCPTRINDUSEDOFTXTOUTINFO == STD_ON)
/**********************************************************************************************************************
  Com_TxDlMon_TxCallCbkTout
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_TxDlMon_TxCallCbkTout(Com_SizeOfTxTOutInfoType idxTxTOutInfo)
{
  /* #10 Call all related tx timeout notification functions */
  Com_CbkTxTOutFuncPtrIndEndIdxOfTxTOutInfoType idxIndTxTOutFuncPtr = Com_GetCbkTxTOutFuncPtrIndStartIdxOfTxTOutInfo(idxTxTOutInfo);
  for(; idxIndTxTOutFuncPtr < Com_GetCbkTxTOutFuncPtrIndEndIdxOfTxTOutInfo(idxTxTOutInfo); idxIndTxTOutFuncPtr++)
  {
    Com_GetCbkTxTOutFuncPtr(Com_GetCbkTxTOutFuncPtrInd(idxIndTxTOutFuncPtr)) ();        /* SBSW_COM_FCT_PTR_CALL_CSL03 */
  }
}
#endif

#if (COM_RXACCESSINFOREPLACESIGINDENDIDXOFRXTOUTINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxDlMon_SignalTimeoutAction
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_RxDlMon_SignalTimeoutAction(Com_SizeOfRxTOutInfoType idxRxTOutInfo)
{
  /* #10 Iterate over all related ComSignals with timeout replace value */
  Com_RxAccessInfoReplaceSigIndEndIdxOfRxTOutInfoType idxRxAccessInfoReplaceSigInd = Com_GetRxAccessInfoReplaceSigIndStartIdxOfRxTOutInfo(idxRxTOutInfo);
  for(; idxRxAccessInfoReplaceSigInd < Com_GetRxAccessInfoReplaceSigIndEndIdxOfRxTOutInfo(idxRxTOutInfo); idxRxAccessInfoReplaceSigInd++)
  {
    /* #20 Set the ComSignal buffer to the timeout replace value */
    Com_RxAccessInfoIterType idxRxAccessInfo = Com_GetRxAccessInfoReplaceSigInd(idxRxAccessInfoReplaceSigInd);
# if ((COM_RXDATATIMEOUTSUBSTITUTIONVALUEUSEDOFRXACCESSINFO == STD_ON) && (COM_BUFFERUSEDOFRXACCESSINFO == STD_ON))
    if(Com_IsRxDataTimeoutSubstitutionValueUsedOfRxAccessInfo(idxRxAccessInfo) && Com_IsBufferUsedOfRxAccessInfo(idxRxAccessInfo))      /* COV_COM_DLMON_SIGNALTIMEOUTACTION_TX */
    {
      Com_Signal_SetRxSigBufferValue(idxRxAccessInfo, Com_GetBufferIdxOfRxAccessInfo(idxRxAccessInfo), Com_GetRxDataTimeoutSubstitutionValueIdxOfRxAccessInfo(idxRxAccessInfo));
    }
# endif
# if ((COM_CONSTVALUEARRAYBASEDRXDATATIMEOUTSUBSTITUTIONVALUEUSEDOFRXACCESSINFO == STD_ON) && (COM_RXSIGBUFFERARRAYBASEDBUFFERUSEDOFRXACCESSINFO == STD_ON))
    if(Com_IsConstValueArrayBasedRxDataTimeoutSubstitutionValueUsedOfRxAccessInfo(idxRxAccessInfo) && Com_IsRxSigBufferArrayBasedBufferUsedOfRxAccessInfo(idxRxAccessInfo))     /* COV_COM_DLMON_SIGNALTIMEOUTACTION_DYN_TX */
    {
      Com_Signal_SetRxSigBufferArrayBasedValue(idxRxAccessInfo, Com_GetRxSigBufferArrayBasedBufferStartIdxOfRxAccessInfo(idxRxAccessInfo),
                                               Com_GetConstValueArrayBasedRxDataTimeoutSubstitutionValueStartIdxOfRxAccessInfo(idxRxAccessInfo),
                                               (PduLengthType) Com_GetConstValueArrayBasedRxDataTimeoutSubstitutionValueLengthOfRxAccessInfo(idxRxAccessInfo));
    }
# endif


# if (COM_GWINFOUSEDOFRXACCESSINFO  == STD_ON)
    /* #30 If the ComSignal is routed, set the related Gateway Event flag to forward the Rx timeout value to Tx side */
    if(Com_IsGwInfoUsedOfRxAccessInfo(idxRxAccessInfo)) /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
    {
      Com_SetGwEvent(Com_GetGwInfoIdxOfRxAccessInfo(idxRxAccessInfo), TRUE);    /* SBSW_COM_CSL02_CSL03 */
    }
# endif
  }
}
#endif


#if (COM_RXACCESSINFOREPLACEGRPSIGINDENDIDXOFRXTOUTINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxDlMon_GroupSignalTimeoutAction
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_RxDlMon_GroupSignalTimeoutAction(Com_SizeOfRxTOutInfoType idxRxTOutInfo)
{
  /* #10 Iterate over all related ComGroupSignals with timeout replace value */
  Com_RxAccessInfoReplaceGrpSigIndEndIdxOfRxTOutInfoType idxRxAccessInfoReplaceGrpSigInd = Com_GetRxAccessInfoReplaceGrpSigIndStartIdxOfRxTOutInfo(idxRxTOutInfo);
  for(; idxRxAccessInfoReplaceGrpSigInd < Com_GetRxAccessInfoReplaceGrpSigIndEndIdxOfRxTOutInfo(idxRxTOutInfo); idxRxAccessInfoReplaceGrpSigInd++)
  {
    /* #20 Set the ComGroupSignal shadow buffer to the timeout replace value */
    Com_RxAccessInfoIterType idxRxAccessInfo = Com_GetRxAccessInfoReplaceGrpSigInd(idxRxAccessInfoReplaceGrpSigInd);
# if ((COM_RXDATATIMEOUTSUBSTITUTIONVALUEUSEDOFRXACCESSINFO == STD_ON) && (COM_SHDBUFFERUSEDOFRXACCESSINFO == STD_ON))
    if(Com_IsRxDataTimeoutSubstitutionValueUsedOfRxAccessInfo(idxRxAccessInfo) && Com_IsShdBufferUsedOfRxAccessInfo(idxRxAccessInfo))   /* COV_COM_DLMON_SIGNALTIMEOUTACTION_TX */
    {
      Com_Signal_SetRxSigBufferValue(idxRxAccessInfo, Com_GetShdBufferIdxOfRxAccessInfo(idxRxAccessInfo), Com_GetRxDataTimeoutSubstitutionValueIdxOfRxAccessInfo(idxRxAccessInfo));
    }
# endif
# if ((COM_CONSTVALUEARRAYBASEDRXDATATIMEOUTSUBSTITUTIONVALUEUSEDOFRXACCESSINFO == STD_ON) && (COM_RXSIGBUFFERARRAYBASEDSHDBUFFERUSEDOFRXACCESSINFO == STD_ON))
    if(Com_IsConstValueArrayBasedRxDataTimeoutSubstitutionValueUsedOfRxAccessInfo(idxRxAccessInfo) && Com_IsRxSigBufferArrayBasedShdBufferUsedOfRxAccessInfo(idxRxAccessInfo))  /* COV_COM_DLMON_SIGNALTIMEOUTACTION_DYN_TX */
    {
      Com_Signal_SetRxSigBufferArrayBasedValue(idxRxAccessInfo, Com_GetRxSigBufferArrayBasedShdBufferStartIdxOfRxAccessInfo(idxRxAccessInfo),
                                               Com_GetConstValueArrayBasedRxDataTimeoutSubstitutionValueStartIdxOfRxAccessInfo(idxRxAccessInfo),
                                               (PduLengthType) Com_GetConstValueArrayBasedRxDataTimeoutSubstitutionValueLengthOfRxAccessInfo(idxRxAccessInfo));
    }
# endif


# if (COM_GWINFOUSEDOFRXACCESSINFO  == STD_ON)
    /* #30 If the ComGroupSignal is routed, set the related Gateway Event flag to forward the Rx timeout value to Tx side */
    if(Com_IsGwInfoUsedOfRxAccessInfo(idxRxAccessInfo)) /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
    {
      Com_SetGwEvent(Com_GetGwInfoIdxOfRxAccessInfo(idxRxAccessInfo), TRUE);    /* SBSW_COM_CSL02_CSL03 */
    }
# endif
  }
}
#endif

#if (COM_CBKRXTOUTFUNCPTRINDUSEDOFRXTOUTINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxDlMon_CallTimeOutNotifications
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_RxDlMon_CallTimeOutNotifications(Com_SizeOfRxTOutInfoType idxRxTOutInfo)
{
  /* #10 Iterate over all related timeout notification functions and call them */
  Com_CbkRxTOutFuncPtrIndEndIdxOfRxTOutInfoType idxIndRxTOutFuncPtr = Com_GetCbkRxTOutFuncPtrIndStartIdxOfRxTOutInfo(idxRxTOutInfo);

  Com_RxDlMon_ExitExclusiveArea();
  for(; idxIndRxTOutFuncPtr < Com_GetCbkRxTOutFuncPtrIndEndIdxOfRxTOutInfo(idxRxTOutInfo); idxIndRxTOutFuncPtr++)
  {
    Com_GetCbkRxTOutFuncPtr(Com_GetCbkRxTOutFuncPtrInd(idxIndRxTOutFuncPtr)) ();        /* SBSW_COM_FCT_PTR_CALL_CSL03 */
  }
  Com_RxDlMon_EnterExclusiveArea();
}
#endif


/**********************************************************************************************************************
  GLOBAL FUNCTIONS
**********************************************************************************************************************/

#if (COM_TXTOUTCNT == STD_ON)
/**********************************************************************************************************************
  Com_TxDlMon_Init
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxDlMon_Init(void)
{
  /* #10 Initialize all tx timeout counter with 0 */
  Com_TxTOutCntIterType ComTxToutIdx;
  for(ComTxToutIdx = 0; ComTxToutIdx < Com_GetSizeOfTxTOutCnt(); ComTxToutIdx++)
  {
    Com_SetTxTOutCnt(ComTxToutIdx, 0);  /* SBSW_COM_CSL01 */
  }
}
#endif

#if (COM_TXTOUTINFO == STD_ON)
/**********************************************************************************************************************
  Com_TxDlMon_MainFunctionTx
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
FUNC(void, COM_CODE) Com_TxDlMon_MainFunctionTx(void)
{
  Com_SizeOfTxTOutInfoType idxTxTOutInfo;

  Com_TxDlMon_EnterExclusiveArea();

  /* #10 Iterate over all tx timeout infos */
  for(idxTxTOutInfo = 0; idxTxTOutInfo < Com_GetSizeOfTxTOutInfo(); idxTxTOutInfo++)
  {
    Com_TxPduInfoIdxOfTxTOutInfoType idxTxPduInfo = Com_GetTxPduInfoIdxOfTxTOutInfo(idxTxTOutInfo);

    /* #20 If the Tx ComIPdu is active and the current timeout counter value is greater 0 */
    if(Com_IsTxPduGrpActive(idxTxPduInfo))
    {
      if(0u < Com_GetTxTOutCnt(idxTxTOutInfo))  /* COV_COM_TX_PROCESSING_NONE_MODE */
      {
        /* #30 Decrement the timeout counter value */
        Com_DecTxTOutCnt(idxTxTOutInfo);        /* SBSW_COM_CSL02 */
        /* #40 If the timeout counter value is equal 0 */
        if(Com_GetTxTOutCnt(idxTxTOutInfo) == 0u)
        {
          /* #50 Set the repetition counter and the MDT counter to 0 */
# if ((COM_REPCNTOFTXMODETRUE == STD_ON) || (COM_REPCNTOFTXMODEFALSE == STD_ON))
          Com_SetRepCnt(idxTxPduInfo, 0);       /* SBSW_COM_CSL02 */ /* \trace SPEC-2736820 */
# endif
# if (COM_MINIMUMDELAYOFTXMODEINFO == STD_ON)
          Com_SetDelayTimeCnt(idxTxPduInfo, 0); /* SBSW_COM_CSL02 */
# endif

# if ((COM_TXTPINFOUSEDOFTXPDUINFO == STD_ON) && (COM_CANCELLATIONSUPPORTOFTXPDUINFO == STD_ON))
          /* #60 Do transmit cancellation */
          Com_TxLLIf_CancelTransmit((PduIdType) idxTxPduInfo);
# endif

# if (COM_CBKTXTOUTFUNCPTRINDUSEDOFTXTOUTINFO == STD_ON)
          Com_TxDlMon_ExitExclusiveArea();
          /* #70 Call the configured timeout notifications */
          Com_TxDlMon_TxCallCbkTout(idxTxTOutInfo);
          Com_TxDlMon_EnterExclusiveArea();
# endif

# if (COM_RETRY_FAILED_TRANSMIT_REQUESTS == STD_ON)
          /* #80 Reset the transmit request, if RETRY_FAILED_TRANSMIT_REQUESTS is enabled */
          Com_SetTransmitRequest(idxTxPduInfo, FALSE);  /* SBSW_COM_CSL02 */
# endif
        }
      } /* Timer active check */
    }   /* I-PDU active check */
    Com_TxDlMon_ThresholdCheck();
  }     /* Tx Timeout object loop */

  Com_TxDlMon_ExitExclusiveArea();
}
#endif

#if (COM_TXTOUTINFOUSEDOFTXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_TxDlMon_TxConfirmation
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxDlMon_TxConfirmation(PduIdType TxPduId)
{
  /* #10 If the passed Tx ComIPdu has a related tx timeout */
  if(Com_IsTxTOutInfoUsedOfTxPduInfo(TxPduId))
  {
    Com_TxTOutInfoIdxOfTxPduInfoType idxTxTOutInfo = Com_GetTxTOutInfoIdxOfTxPduInfo(TxPduId);
# if (COM_EXISTS_NONE_MODEOFTXTOUTINFO == STD_ON)
    /* #20 If the tx timeout is in None mode and the current timeout counter value is greater 0, set the tx timeout counter to the configured tx timeout factor */
    if(Com_GetModeOfTxTOutInfo(idxTxTOutInfo) == COM_NONE_MODEOFTXTOUTINFO)     /* COV_COM_TX_PROCESSING_NONE_MODE */
    {
      if(Com_GetTxTOutCnt(idxTxTOutInfo) > 0u)
      {
        Com_SetTxTOutCnt(idxTxTOutInfo, Com_GetFactorOfTxTOutInfo(idxTxTOutInfo));      /* SBSW_COM_CSL02 */
      }
    }
    /* #30 Otherwise the tx timeout is in Normal mode, in this case set the tx timeout counter to 0 */
    else
# endif
    {
      Com_SetTxTOutCnt(idxTxTOutInfo, 0);       /* SBSW_COM_CSL02 */
    }
  }
}
#endif


#if (COM_TXTOUTINFOUSEDOFTXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_TxDlMon_IPduGroupStart
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxDlMon_IPduGroupStart(Com_TxPduInfoIterType TxPduId)
{
  /* #10 If the passed Tx ComIPdu has a related tx timeout */
  if(Com_IsTxTOutInfoUsedOfTxPduInfo(TxPduId))  /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    Com_TxTOutInfoIdxOfTxPduInfoType idxTxTOutInfo = Com_GetTxTOutInfoIdxOfTxPduInfo(TxPduId);
# if (COM_EXISTS_NONE_MODEOFTXTOUTINFO == STD_ON)
    /* #20 If the tx timeout is in None mode, set the tx timeout counter to the configured tx timeout factor */
    if(Com_GetModeOfTxTOutInfo(idxTxTOutInfo) == COM_NONE_MODEOFTXTOUTINFO)     /* COV_COM_TX_PROCESSING_NONE_MODE */
    {
      Com_SetTxTOutCnt(idxTxTOutInfo, Com_GetFactorOfTxTOutInfo(idxTxTOutInfo));        /* SBSW_COM_CSL02 */
    }
    /* #30 Otherwise the tx timeout is in Normal mode, in this case set the tx timeout counter to 0 */
    else
# endif
    {
      Com_SetTxTOutCnt(idxTxTOutInfo, 0);       /* SBSW_COM_CSL02 */
    }
  }
}
#endif

#if (COM_EXISTS_NORMAL_MODEOFTXTOUTINFO == STD_ON)
/**********************************************************************************************************************
  Com_TxDlMon_SwitchIpduTxMode
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxDlMon_SwitchIpduTxMode(PduIdType TxPduId)
{
  /* #10 If the passed Tx ComIPdu has a related tx timeout and the tx timeout is in Normal mode */
  if(Com_IsTxTOutInfoUsedOfTxPduInfo(TxPduId))
  {
    Com_TxTOutInfoIdxOfTxPduInfoType idxTxTOutInfo = Com_GetTxTOutInfoIdxOfTxPduInfo(TxPduId);

    if(Com_GetModeOfTxTOutInfo(idxTxTOutInfo) == COM_NORMAL_MODEOFTXTOUTINFO)   /* COV_COM_TX_PROCESSING_NONE_MODE */
    {
      boolean hasCyclicOrDirectTxModePart = FALSE;      /* PRQA S 2981 */ /* MD_MSR_RetVal */
# if ((COM_PERIODICOFTXMODETRUE == STD_ON) || (COM_PERIODICOFTXMODEFALSE == STD_ON))
      hasCyclicOrDirectTxModePart = (boolean) Com_TxModeHdlr_IsPeriodicTxMode(TxPduId); /* PRQA S 2986 */ /* MD_Com_2985_2986 */
# endif
# if ((COM_DIRECTOFTXMODETRUE == STD_ON) || (COM_DIRECTOFTXMODEFALSE == STD_ON))
      {
        boolean isDirectTxMode = (boolean) Com_TxModeHdlr_IsDirectTxMode(TxPduId);
#  if ((COM_PERIODICOFTXMODETRUE == STD_ON) || (COM_PERIODICOFTXMODEFALSE == STD_ON))
        hasCyclicOrDirectTxModePart = hasCyclicOrDirectTxModePart || isDirectTxMode;    /* PRQA S 2986 */ /* MD_Com_2985_2986 */
#  else
        hasCyclicOrDirectTxModePart = isDirectTxMode;   /* PRQA S 2986 */ /* MD_Com_2985_2986 */
#  endif
      }
# endif

      /* #20 If the passed Tx ComIPdu is in NONE transmission mode, set the tx timeout counter to 0 */
      if(hasCyclicOrDirectTxModePart == FALSE)
      {
        /* \trace SPEC-2736879 */
        Com_SetTxTOutCnt(idxTxTOutInfo, 0);     /* SBSW_COM_CSL02 */
      }
    }
  }
}
#endif

#if (COM_GWTIMEOUTINFO == STD_ON)
/**********************************************************************************************************************
  Com_GwTout_HandleCounter
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_GwTout_HandleCounter(void)
{
  Com_SizeOfGwTimeoutInfoType gwToutHndl;
  SchM_Enter_Com_COM_EXCLUSIVE_AREA_TX();
  /* #10 Iterate over all gateway timeout infos */
  for(gwToutHndl = 0u; gwToutHndl < Com_GetSizeOfGwTimeoutInfo(); gwToutHndl++)
  {
    /* #20 If the tx pdu is active and the timeout is active, decrement the gateway timeout counter */
    if(Com_IsTxPduGrpActive((Com_GetTxPduInfoIdxOfGwTimeoutInfo(gwToutHndl))))
    {
      if(Com_GwTout_TimeoutIsActive(gwToutHndl))
      {
        Com_DecGwRoutingTimeoutCounter(gwToutHndl);     /* SBSW_COM_CSL02 */
        /* #30 If a gateway timeout occurred, stop the cyclic transmission */
        if(Com_GwTout_TimeoutHasOccurred(gwToutHndl))
        {
          Com_TxModeHdlr_StopCyclicTransmission(Com_GetTxPduInfoIdxOfGwTimeoutInfo(gwToutHndl));
        }
      }
    }
  }
  SchM_Exit_Com_COM_EXCLUSIVE_AREA_TX();
}

/**********************************************************************************************************************
  Com_GwTout_InitCounter
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_GwTout_InitCounter(PduIdType ComPduId)
{
  /* #10 If the passed ComIPdu has a configured gateway timeout */
  if(Com_IsGwTimeoutInfoUsedOfTxPduInfo(ComPduId))      /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    /* #20 Initialize the timeout counter with 1 */
    Com_SetGwRoutingTimeoutCounter(Com_GetGwTimeoutInfoIdxOfTxPduInfo(ComPduId), 1);    /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */

    /* #30 Stop cyclic transmission */
    Com_TxModeHdlr_StopCyclicTransmission(ComPduId);
  }
}
#endif

#if (COM_GWTIMEOUTINFO == STD_ON)
/**********************************************************************************************************************
  Com_GwTout_Event
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_GwTout_Event(PduIdType ComTxPduId)     /* PRQA S 1505 */ /* MD_MSR_Rule8.7 */
{
  /* #10 If the passed ComIPdu has a configured gateway timeout and the Tx ComIPdu is active */
  if(Com_IsTxPduGrpActive((PduIdType) ComTxPduId))
  {
    if(Com_IsGwTimeoutInfoUsedOfTxPduInfo(ComTxPduId))  /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
    {
      /* #20 If the current tx mode is periodic */
      Com_GwTimeoutInfoIdxOfTxPduInfoType gwToutId = Com_GetGwTimeoutInfoIdxOfTxPduInfo(ComTxPduId);
      if(Com_TxModeHdlr_IsPeriodicTxMode(ComTxPduId) == TRUE)   /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
      {
        /* #30 Start the cyclic transmission of the passed Tx ComIPdu */
        Com_TxModeHdlr_StartCyclicTransmission(ComTxPduId);
        /* #40 Reload the gateway timeout counter with the gateway timeout factor */
        Com_SetGwRoutingTimeoutCounter(gwToutId, Com_GetGwRoutingTimeoutFactorOfGwTimeoutInfo(gwToutId));       /* SBSW_COM_CSL02 */
      }
      /* #50 Otherwise set the gateway routing timeout to 0 */
      else
      {
        Com_SetGwRoutingTimeoutCounter(gwToutId, 0);    /* SBSW_COM_CSL02 */
      }
    }
  }
}
#endif

#if (COM_RXTOUTINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxDlMon_MainFunctionRx
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
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_RxDlMon_MainFunctionRx(void)
{
  /* Reception Deadline Monitoring.  */
  Com_SizeOfRxTOutInfoType idxRxTOutInfo;

  Com_RxDlMon_EnterExclusiveArea();
  /* #10 Iterate over all Rx deadline monitorings */
  for(idxRxTOutInfo = 0; idxRxTOutInfo < Com_GetSizeOfRxTOutInfo(); idxRxTOutInfo++)
  {
    /* #20 If the Rx deadline monitoring state machine is active and the timeout counter is greater zero, decrement the timeout counter */
    if(Com_LMgt_RxIpduDmActive(idxRxTOutInfo))
    {
      if(0u < Com_GetRxTOutCnt(idxRxTOutInfo))  /* COV_COM_RX_TOUT_CNT */
      {
        Com_DecRxTOutCnt(idxRxTOutInfo);        /* SBSW_COM_CSL02 */

        /* #30 If a timeout expired, reload the timeout counter */
        if(Com_GetRxTOutCnt(idxRxTOutInfo) == 0u)
        {
          Com_SetRxTOutCnt(idxRxTOutInfo, Com_GetFactorOfRxTOutInfo(idxRxTOutInfo) - 1u);       /* SBSW_COM_CSL02 */

          /* #40 Set the rx timeout state to timeout occurred */
          Com_LMgt_TimeoutOccurred(idxRxTOutInfo);      /* SBSW_COM_CSL02 */
# if (COM_RXACCESSINFOREPLACESIGINDENDIDXOFRXTOUTINFO == STD_ON)
          /* #50 Do the timeout action for related ComSignals */
          Com_RxDlMon_SignalTimeoutAction(idxRxTOutInfo);
# endif
# if (COM_RXACCESSINFOREPLACEGRPSIGINDENDIDXOFRXTOUTINFO == STD_ON)
          /* #60 Do the timeout action for related ComSignalGroups */
          Com_RxDlMon_GroupSignalTimeoutAction(idxRxTOutInfo);
# endif

# if (COM_CBKRXTOUTFUNCPTRINDUSEDOFRXTOUTINFO == STD_ON)
          /* #70 Call related timeout notification functions */
          Com_RxDlMon_CallTimeOutNotifications(idxRxTOutInfo);
# endif

        }
      }
    }
    Com_RxDlMon_ThresholdCheck();
  }
  Com_RxDlMon_ExitExclusiveArea();
}
#endif


#if (COM_RXTOUTINFOINDENDIDXOFRXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxDlMon_InitRxIpdu
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_RxDlMon_InitRxIpdu(PduIdType ComPduId)
{
  /* #10 Iterate over all related timeout data sets */
  Com_RxTOutInfoIndStartIdxOfRxPduInfoType idxRxTOutInfoInd = Com_GetRxTOutInfoIndStartIdxOfRxPduInfo(ComPduId);
  for(; idxRxTOutInfoInd < Com_GetRxTOutInfoIndEndIdxOfRxPduInfo(ComPduId); idxRxTOutInfoInd++)
  {
    /* #20 Set the Rx timeout counter value to the first timeout and set the deadline monitoring state machine to ACTIVE */
    Com_SetRxTOutCnt(Com_GetRxTOutInfoInd(idxRxTOutInfoInd), Com_GetFirstFactorOfRxTOutInfo(Com_GetRxTOutInfoInd(idxRxTOutInfoInd)));   /* SBSW_COM_CSL02_CSL03 */
    Com_SetRxPduDmState(Com_GetRxTOutInfoInd(idxRxTOutInfoInd), COM_ACTIVE_RXPDUDMSTATE);       /* SBSW_COM_CSL02_CSL03 */
  }
}
#endif

#if (COM_RXTOUTINFOUSEDOFRXSIGINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxDlMon_SigEvent
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_RxDlMon_SigEvent(Com_RxSigInfoIterType idxRxSigInfo)
{
  /* #10 If the passed Rx ComSignal has a timeout, reload the timeout value */
  if(Com_IsRxTOutInfoUsedOfRxSigInfo(idxRxSigInfo))     /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    Com_RxTOutInfoIdxOfRxSigInfoType idxRxTOutInfo = Com_GetRxTOutInfoIdxOfRxSigInfo(idxRxSigInfo);
    Com_SetRxTOutCnt(idxRxTOutInfo, Com_GetFactorOfRxTOutInfo(idxRxTOutInfo));  /* SBSW_COM_CSL02 */
  }
}
#endif

#if (COM_RXTOUTINFOUSEDOFRXSIGGRPINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxDlMon_SigGrpEvent
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_RxDlMon_SigGrpEvent(Com_RxSigGrpInfoIterType idxRxSigGrpInfo)
{
  /* #10 If the passed Rx ComSignalGroup has a timeout, reload the timeout value */
  if(Com_IsRxTOutInfoUsedOfRxSigGrpInfo(idxRxSigGrpInfo))       /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    Com_RxTOutInfoIdxOfRxSigGrpInfoType idxRxTOutInfo = Com_GetRxTOutInfoIdxOfRxSigGrpInfo(idxRxSigGrpInfo);
    Com_SetRxTOutCnt(idxRxTOutInfo, Com_GetFactorOfRxTOutInfo(idxRxTOutInfo));  /* SBSW_COM_CSL02 */
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
 *  END OF FILE: Com_Timer.c
 *********************************************************************************************************************/
