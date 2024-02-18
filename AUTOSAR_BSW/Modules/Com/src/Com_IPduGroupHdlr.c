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
/*!        \file  Com_IPduGroupHdlr.c
 *        \brief  MICROSAR Communication source file
 *
 *      \details  This is the implementation of the MICROSAR Communication module.
 *                The basic software module is based on the AUTOSAR Communication specification.
 *
 *********************************************************************************************************************/

#define COM_IPDUGROUPHDLR_SOURCE

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
#include "Com_LMgt.h"
#include "Com_LLIf.h"
#include "Com_Timer.h"
#include "Com_Buffers.h"
#include "Com_TxModeHdlr.h"
#include "Com_IPduGroupHdlr.h"
#include "Com_Notifications.h"
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

#if (COM_RXTOUTINFO == STD_ON)
/**********************************************************************************************************************
  Com_LMgt_ActivateRxIpduDm
**********************************************************************************************************************/
/*! \brief        This function enables the Deadline Monitoring for the Rx I-Pdu.
    \details      -
    \pre          -
    \param[in]    ComRxToutObjtId  ID of Rx Timeout object.
**********************************************************************************************************************/
# define Com_LMgt_ActivateRxIpduDm(ComRxToutObjtId)        Com_SetRxPduDmState(ComRxToutObjtId, COM_ACTIVE_RXPDUDMSTATE)
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

#if (COM_RXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_ActivateRxComIPdu
**********************************************************************************************************************/
/*! \brief        This function activates Rx ComIPdu's and optionally initializes the ComIPdu.
    \details      -
    \pre          -
    \param[in]    rxPduIdx   - ID of Rx ComIPdu
    \param[in]    initialize - True, if belonging buffer shall be initialized
    \context      TASK
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_ActivateRxComIPdu(Com_RxPduInfoIterType rxPduIdx, boolean initialize);
#endif

#if (COM_TXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_ActivateTxComIPdu
**********************************************************************************************************************/
/*! \brief        This function activates Tx ComIPdu's and optionally initializes the ComIPdu.
    \details      -
    \pre          -
    \param[in]    ComTxPduId   - ID of Tx ComIPdu
    \param[in]    initialize - True, if belonging buffer shall be initialized
    \context      TASK
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_ActivateTxComIPdu(Com_TxPduInfoIterType ComTxPduId, boolean initialize);
#endif

#if (COM_RXPDUINFOINDUSEDOFIPDUGROUPINFO == STD_ON)
/**********************************************************************************************************************
  Com_SetRxPduGrpStateToStop
**********************************************************************************************************************/
/*! \brief        This function sets the Rx-PDU-Group-State to FALSE, if the state of all referenced IPDU groups is
 *                equal to COM_INACTIVE_IPDUGROUPSTATE
    \details      -
    \pre          -
    \param[in]    subIpduGroupId  ComIPduGroup handle id
    \context      TASK
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_SetRxPduGrpStateToStop(Com_IpduGroupIdType subIpduGroupId);
#endif

#if (COM_TXPDUINFOINDUSEDOFIPDUGROUPINFO == STD_ON)
/**********************************************************************************************************************
  Com_SetTxPduGrpStateToStop
**********************************************************************************************************************/
/*! \brief        This function sets the Tx-PDU-Group-State to FALSE, if the state of all referenced IPDU groups is
 *                equal to COM_INACTIVE_IPDUGROUPSTATE
    \details      -
    \pre          -
    \param[in]    subIpduGroupId  ComIPduGroup handle id
    \context      TASK
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_SetTxPduGrpStateToStop(Com_IpduGroupIdType subIpduGroupId);
#endif

/**********************************************************************************************************************
  LOCAL FUNCTIONS
**********************************************************************************************************************/

#if (COM_RXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_ActivateRxComIPdu
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_ActivateRxComIPdu(Com_RxPduInfoIterType rxPduIdx, boolean initialize)
{
  /* Start Rx I-PDU */
  /* #10 If the ComIPdu should be initialized, initialize the Rx ComIPdu parameters */
  if(initialize == TRUE)        /* COV_COM_UPDATE_IPDU_STATE */
  {
    /* COM614 If a previously stopped I-PDU gets started by the operation specified in COM613 and the parameter initialize is set to true, then the function Com_IpduGroupControl shall (re-)initialize this I-PDU before it is started. */
    Com_LMgt_InitRxIpdu((PduIdType) rxPduIdx);
  }

# if (COM_RXTPINFOUSEDOFRXPDUINFO == STD_ON)
  /* #20 If the ComIPdu is a TP Pdu initialize the TP Pdu parameters */
  if(Com_GetTypeOfRxPduInfo(rxPduIdx) == COM_TP_TYPEOFRXPDUINFO)        /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    Com_ResetRxTpConnection((PduIdType) rxPduIdx);
  }
# endif

# if (COM_EXISTS_DEFERRED_SIGNALPROCESSINGOFRXPDUINFO == STD_ON)
  /* #30 If the Rx ComIPdu is handled deferred, reset the "Handle Deferred" flag */
  if(Com_IsHandleRxPduDeferredUsedOfRxPduInfo(rxPduIdx))        /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    Com_SetHandleRxPduDeferred(Com_GetHandleRxPduDeferredIdxOfRxPduInfo(rxPduIdx), 0);  /* SBSW_COM_CSL03 */
  }
# endif

  /* #40 Set the state of the Rx ComIPdu to active */
  Com_SetRxPduGrpActive(rxPduIdx, TRUE);        /* SBSW_COM_CSL02 */
# if (COM_RXTOUTINFOINDENDIDXOFRXPDUINFO == STD_ON)
  {
    /* #50 Iterate over all related Rx timeout state machines and set them to active */
    /* \trace SPEC-2736840 */
    Com_RxTOutInfoIndStartIdxOfRxPduInfoType idxRxTOutInfoInd = Com_GetRxTOutInfoIndStartIdxOfRxPduInfo(rxPduIdx);
    for(; idxRxTOutInfoInd < Com_GetRxTOutInfoIndEndIdxOfRxPduInfo(rxPduIdx); idxRxTOutInfoInd++)
    {
      Com_LMgt_ActivateRxIpduDm(Com_GetRxTOutInfoInd(idxRxTOutInfoInd));        /* SBSW_COM_CSL02_CSL03 */
    }
  }
# endif
}
#endif

#if (COM_TXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_ActivateTxComIPdu
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
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_ActivateTxComIPdu(Com_TxPduInfoIterType ComTxPduId, boolean initialize)
{
  /* Start Tx I-PDU */
  /* #30 If the ComIPdu should be initialized, initialize the Tx ComIPdu parameters */
  if(initialize == TRUE)        /* COV_COM_NO_IPDUGROUPS */
  {
    /* COM614 If a previously stopped I-PDU gets started by the operation specified in COM613 and the parameter initialize is set to true, then the function Com_IpduGroupControl shall (re-)initialize this I-PDU before it is started. */
    Com_LMgt_InitTxIpdu(ComTxPduId);
  }

# if (COM_TXTPINFOUSEDOFTXPDUINFO == STD_ON)
  if(Com_IsTxTpInfoUsedOfTxPduInfo(ComTxPduId)) /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    Com_ResetTxTpConnection((PduIdType) ComTxPduId);
  }
# endif

# if (COM_TXTOUTINFOUSEDOFTXPDUINFO == STD_ON)
  /* #40 Start the Tx deadline monitoring */
  /* \trace SPEC-2736840 */
  Com_TxDlMon_IPduGroupStart(ComTxPduId);
# endif
  /* #45 Initialize gateway counter */
# if (COM_GWTIMEOUTINFO == STD_ON)
  Com_GwTout_InitCounter((PduIdType) ComTxPduId);
# endif
# if (COM_CONSTVALUEUINT8UBCLEARMASKENDIDXOFTXPDUINFO == STD_ON)
  /* #50 Clear all Update Bits */
  Com_TxBuffer_ClearUpdateBits((PduIdType) ComTxPduId);
# endif
  /* #60 Set the Tx ComIPdu Group state to active */
  Com_SetTxPduGrpActive(ComTxPduId, TRUE);      /* SBSW_COM_CSL02 */
}
#endif

#if (COM_RXPDUINFOINDUSEDOFIPDUGROUPINFO == STD_ON)
/**********************************************************************************************************************
  Com_SetRxPduGrpStateToStop
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_SetRxPduGrpStateToStop(Com_IpduGroupIdType subIpduGroupId)
{
  /* #10 Iterate over all related Rx ComIPdu of the passed ComIPduGroup */
  Com_RxPduInfoIndEndIdxOfIPduGroupInfoType rxPduIndId = Com_GetRxPduInfoIndStartIdxOfIPduGroupInfo(subIpduGroupId);

  Com_RxIPduGroup_EnterExclusiveArea();
  for(; rxPduIndId < Com_GetRxPduInfoIndEndIdxOfIPduGroupInfo(subIpduGroupId); rxPduIndId++)
  {
    boolean canBeStopped = TRUE;
    Com_RxPduInfoIndType rxPduId = Com_GetRxPduInfoInd(rxPduIndId);

    /* #20 Iterate over all related ComIPdu Groups */
    Com_IPduGroupInfoOfRxPduInfoIndEndIdxOfRxPduInfoType referencedIPduGroupInd = Com_GetIPduGroupInfoOfRxPduInfoIndStartIdxOfRxPduInfo(rxPduId);
    for(; referencedIPduGroupInd < Com_GetIPduGroupInfoOfRxPduInfoIndEndIdxOfRxPduInfo(rxPduId); referencedIPduGroupInd++)
    {
      Com_IPduGroupInfoOfRxPduInfoIndType referencedIPduGroup = Com_GetIPduGroupInfoOfRxPduInfoInd(referencedIPduGroupInd);
      /* #30 If at least one related ComIPdu Group is active, the ComIPdu remains active */
      if(Com_GetIPduGroupState(referencedIPduGroup) != COM_INACTIVE_IPDUGROUPSTATE)     /* COV_COM_IPDU_GROUP_ASR3_XF */
      {
        canBeStopped = FALSE;
        break;
      }
    }
    /* #40 If all related ComIPdu Groups are stopped the ComIPdu Group state is set to inactive */
    if(canBeStopped == TRUE)    /* COV_COM_IPDU_GROUP_ASR3_TX */
    {
      Com_DeactivateRxComIPdu(rxPduId);
    }

    Com_RxIPduGroup_ThresholdCheck();
  }
  Com_RxIPduGroup_ExitExclusiveArea();
}
#endif

#if (COM_TXPDUINFOINDUSEDOFIPDUGROUPINFO == STD_ON)
/**********************************************************************************************************************
  Com_SetTxPduGrpStateToStop
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_SetTxPduGrpStateToStop(Com_IpduGroupIdType subIpduGroupId)
{
  Com_TxPduInfoIndEndIdxOfIPduGroupInfoType txPduIndId = Com_GetTxPduInfoIndStartIdxOfIPduGroupInfo(subIpduGroupId);

  Com_TxIPduGroup_EnterExclusiveArea();
  /* #10 Iterate over all related Tx ComIPdu of the passed ComIPduGroup */
  for(; txPduIndId < Com_GetTxPduInfoIndEndIdxOfIPduGroupInfo(subIpduGroupId); txPduIndId++)
  {
    boolean canBeStopped = TRUE;
    Com_TxPduInfoIndType txPduId = Com_GetTxPduInfoInd(txPduIndId);

    /* #20 Iterate over all related ComIPdu Groups */
    Com_IPduGroupInfoOfTxPduInfoIndEndIdxOfTxPduInfoType referencedIPduGroupInd = Com_GetIPduGroupInfoOfTxPduInfoIndStartIdxOfTxPduInfo(txPduId);
    for(; referencedIPduGroupInd < Com_GetIPduGroupInfoOfTxPduInfoIndEndIdxOfTxPduInfo(txPduId); referencedIPduGroupInd++)
    {
      Com_IPduGroupInfoOfTxPduInfoIndType referencedIPduGroup = Com_GetIPduGroupInfoOfTxPduInfoInd(referencedIPduGroupInd);
      /* #30 If at least one related ComIPdu Group is active, the ComIPdu remains active */
      if(Com_GetIPduGroupState(referencedIPduGroup) != COM_INACTIVE_IPDUGROUPSTATE)
      {
        canBeStopped = FALSE;
        break;
      }
    }
    /* #40 If all related ComIPdu Groups are stopped, deactivate TxComIPdu */
    if(canBeStopped == TRUE)
    {
      Com_DeactivateTxComIPdu(txPduId);
    }
    Com_TxIPduGroup_ThresholdCheck();
  }
  Com_TxIPduGroup_ExitExclusiveArea();
}
#endif

/**********************************************************************************************************************
  GLOBAL FUNCTIONS
**********************************************************************************************************************/

#if (COM_ALWAYSACTIVERXCOMIPDUS == STD_ON)
/**********************************************************************************************************************
  Com_ActivateAlwaysOnRxComIPdus
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *-
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_ActivateAlwaysOnRxComIPdus(void)
{
  Com_AlwaysActiveRxComIPdusIterType idx;

  /* #10 Iterate over all Rx ComIPdus and activate Rx ComIPdu */
  for(idx = 0; idx < Com_GetSizeOfAlwaysActiveRxComIPdus(); idx++)
  {
    Com_ActivateRxComIPdu(Com_GetRxPduInfoIdxOfAlwaysActiveRxComIPdus(idx), TRUE);
  }
}
#endif

#if ((COM_RXTOUTINFOINDENDIDXOFRXPDUINFO == STD_ON) && (COM_PDUGRPVECTOR == STD_ON))
/**********************************************************************************************************************
  Com_ReceptionDMControl_SetDmState
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_ReceptionDMControl_SetDmState(Com_RxPduInfoIterType ComRxPduId, Com_RxPduDmStateType bRequestedActiveState)
{

  Com_RxTOutInfoIndStartIdxOfRxPduInfoType idxRxTOutInfoInd = Com_GetRxTOutInfoIndStartIdxOfRxPduInfo(ComRxPduId);
  /* #10 Iterate over all ComIPdu related reception deadline monitoring states */
  for(; idxRxTOutInfoInd < Com_GetRxTOutInfoIndEndIdxOfRxPduInfo(ComRxPduId); idxRxTOutInfoInd++)
  {
    /* COM618 For all I-PDUs that do not change their deadline monitoring state the function, Com_ReceptionDMControl shall do nothing. */
    Com_RxTOutInfoIndType idxRxTOutInfo = Com_GetRxTOutInfoInd(idxRxTOutInfoInd);
    /* #20 If the current state differs the passed state */
    /* \trace SPEC-2736873 */ /* \trace SPEC-2736875 */
    if((Com_GetRxPduDmState(idxRxTOutInfo) & COM_PURE_DM_STATE_MASK_RXPDUDMSTATE) != bRequestedActiveState)
    {
      /* COM617 Second, the function Com_ReceptionDMControl shall start or stop the reception deadline monitoring for all I-PDUs that change their reception deadline monitoring state because of this call of Com_ReceptionDMControl respectively. */

      /* Start Deadline Monitoring */
      /* #30 If the passed state is ACTIVE, set the timeout counter to the first timeout value */
      /* \trace SPEC-2736872 */
      if(bRequestedActiveState == COM_ACTIVE_RXPDUDMSTATE)
      {
        Com_SetRxTOutCnt(idxRxTOutInfo, Com_GetFirstFactorOfRxTOutInfo(idxRxTOutInfo)); /* SBSW_COM_CSL02 */
      }
      /* #40 Set the timeout state to the passed state */
      Com_SetRxPduDmState(idxRxTOutInfo, bRequestedActiveState);        /* SBSW_COM_CSL02 */
    }
  }
}
#endif

#if (COM_ALWAYSACTIVETXCOMIPDUS == STD_ON)
/**********************************************************************************************************************
  Com_ActivateAlwaysOnTxComIPdus
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *-
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_ActivateAlwaysOnTxComIPdus(void)
{
  Com_AlwaysActiveTxComIPdusIterType idx;

  /* #10 Iterate over all Tx ComIPdus and activate Tx ComIPdu */
  for(idx = 0; idx < Com_GetSizeOfAlwaysActiveTxComIPdus(); idx++)
  {
    Com_ActivateTxComIPdu(Com_GetTxPduInfoIdxOfAlwaysActiveTxComIPdus(idx), TRUE);
  }
}
#endif

#if (COM_RXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_DeactivateRxComIPdu
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_DeactivateRxComIPdu(Com_RxPduInfoIterType ComRxPduId)
{
  /* #10 Set RxPduGrpActivate State to FALSE */
  Com_SetRxPduGrpActive(ComRxPduId, FALSE);     /* PRQA S 2842 */ /* MD_Com_2842 */ /* SBSW_COM_CSL02 */
# if (COM_RXTOUTINFOINDENDIDXOFRXPDUINFO == STD_ON)
  {
    /* - #20 Deactivate Rx Deadline Monitoring */
    Com_RxTOutInfoIndStartIdxOfRxPduInfoType idxRxTOutInfoInd = Com_GetRxTOutInfoIndStartIdxOfRxPduInfo(ComRxPduId);
    for(; idxRxTOutInfoInd < Com_GetRxTOutInfoIndEndIdxOfRxPduInfo(ComRxPduId); idxRxTOutInfoInd++)
    {
      Com_LMgt_DeactivateRxIpduDm(Com_GetRxTOutInfoInd(idxRxTOutInfoInd));      /* SBSW_COM_CSL02_CSL03 */
    }
  }
# endif
}
#endif

#if (COM_TXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_DeactivateTxComIPdu
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_DeactivateTxComIPdu(Com_TxPduInfoIterType txPduId)
{
  /* #50 Set the Tx Mode related parameters to the initial value */
  Com_TxModeHdlr_StopTxIpdus((PduIdType) txPduId);
# if (COM_CBKTXERRFUNCPTRINDUSEDOFTXPDUINFO == STD_ON)
  /* #60 If the transmission of a ComIPdu was not confirmed, set WaitForConfirmation flags to the initial value and call any configured error notification */
  if(Com_IsWaitingForConfirmation(txPduId))
  {
    Com_TxIPduGroup_ExitExclusiveArea();

    Com_TxNHdlr_StopTxIpdu(txPduId);

    Com_TxIPduGroup_EnterExclusiveArea();
  }
# endif
# if (COM_CBKTXACKDEFFUNCPTRINDUSEDOFTXPDUINFO == STD_ON)
  /* #65 Clear HandleTxPduDeffered flag */
  Com_SetHandleTxPduDeferred(txPduId, FALSE);   /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
# endif

# if (COM_TXTPINFOUSEDOFTXPDUINFO == STD_ON)
  if(Com_IsTxTpInfoUsedOfTxPduInfo(txPduId))    /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    Com_ResetTxTpConnection((PduIdType) txPduId);
  }
# endif

  /* #70 Set the Tx ComIPdu Group state to inactive */
  Com_SetTxPduGrpActive((PduIdType) txPduId, FALSE);    /* SBSW_COM_CSL02 */
}
#endif

#if (COM_RXPDUINFOINDUSEDOFIPDUGROUPINFO == STD_ON)
/**********************************************************************************************************************
  Com_IpduGroupStartRx
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_IpduGroupStartRx(Com_IpduGroupIdType subIpduGroupId, boolean Initialize)
{
  /* #10 Iterate over all related Rx ComIPdus */
  Com_RxPduInfoIndEndIdxOfIPduGroupInfoType rxPduIndId = Com_GetRxPduInfoIndStartIdxOfIPduGroupInfo(subIpduGroupId);

  Com_RxIPduGroup_EnterExclusiveArea();

  for(; rxPduIndId < Com_GetRxPduInfoIndEndIdxOfIPduGroupInfo(subIpduGroupId); rxPduIndId++)
  {
    Com_RxPduInfoIndType rxPduId = Com_GetRxPduInfoInd(rxPduIndId);
    /* #20 If the Rx ComIPdu is inactive, activate and optionally initialize the Rx ComIPdu */
    if(!Com_IsRxPduGrpActive(rxPduId))  /* COV_COM_IPDU_GROUP_ASR3_TX */
    {
      /* Start Rx I-PDU */
      Com_ActivateRxComIPdu(rxPduId, Initialize);
    }
    Com_RxIPduGroup_ThresholdCheck();
  }
  Com_RxIPduGroup_ExitExclusiveArea();
}
#endif

#if (COM_TXPDUINFOINDUSEDOFIPDUGROUPINFO == STD_ON)
/**********************************************************************************************************************
  Com_IpduGroupStartTx
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_IpduGroupStartTx(Com_IpduGroupIdType subIpduGroupId, boolean Initialize)
{
  /* #10 Iterate over all related Tx ComIPdus */
  Com_TxPduInfoIndEndIdxOfIPduGroupInfoType txPduIndId = Com_GetTxPduInfoIndStartIdxOfIPduGroupInfo(subIpduGroupId);

  Com_TxIPduGroup_EnterExclusiveArea();

  for(; txPduIndId < Com_GetTxPduInfoIndEndIdxOfIPduGroupInfo(subIpduGroupId); txPduIndId++)
  {
    Com_TxPduInfoIndType txPduId = Com_GetTxPduInfoInd(txPduIndId);
    /* #20 If the ComIPdu state is inactive */
    if(!Com_IsTxPduGrpActive(txPduId))
    {
      /* #30 Activate and optionally initialize the Tx ComIPdu */
      Com_ActivateTxComIPdu(txPduId, Initialize);
    }

    Com_TxIPduGroup_ThresholdCheck();
  }

  Com_TxIPduGroup_ExitExclusiveArea();
}
#endif

#if (COM_IPDUGROUPINFO == STD_ON)
/**********************************************************************************************************************
  Com_IpduGroupStopSubGroup
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_IpduGroupStopSubGroup(Com_IpduGroupIdType subIpduGroupId)
{
  /* #10 If the ComIPduGroup is ACTIVE set the ComIPduGroup to INACTIVE and stop its SubIPduGroups */
  if(Com_GetIPduGroupState(subIpduGroupId) != COM_INACTIVE_IPDUGROUPSTATE)
  {
    Com_SetIPduGroupState(subIpduGroupId, COM_INACTIVE_IPDUGROUPSTATE); /* SBSW_COM_CSL02 */
# if (COM_RXPDUINFOINDUSEDOFIPDUGROUPINFO == STD_ON)
    Com_SetRxPduGrpStateToStop(subIpduGroupId);
# endif
# if (COM_TXPDUINFOINDUSEDOFIPDUGROUPINFO == STD_ON)
    Com_SetTxPduGrpStateToStop(subIpduGroupId);
# endif
  }
}
#endif

#if ((COM_PDUGRPVECTOR == STD_ON) && (COM_TXPDUINFO == STD_ON) && (COM_ACTIVATABLETXCOMIPDUS == STD_ON))
/**********************************************************************************************************************
 Com_IpduGroupControl_SetRequestedActiveState
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_IpduGroupControl_SetRequestedActiveState(Com_TxPduInfoIterType ComTxPduId, boolean initialize, boolean bRequestedActiveState)
{
  /* #10 If the requested state is not equal to the current state */
  if((Com_IsTxPduGrpActive(ComTxPduId)) != bRequestedActiveState)
  {
    /* COM613 Second, the function Com_IpduGroupControl shall start or stop all I-PDUs that change theire activation state because of this call of Com_IpduGroupControl respectively. */
    /* #20 If the requested state is activated, activate and optionally initialize Tx ComIPdu */
    if(bRequestedActiveState == TRUE)
    {
      /* Start Tx I-PDU */
      Com_ActivateTxComIPdu(ComTxPduId, initialize);
    }
    /* #30 Otherwise stop the Tx ComIPdu, set the Tx ComIPdu state to inactive and clear HandleTxPduDeffered flag */
    else
    {
      Com_DeactivateTxComIPdu(ComTxPduId);
    }
  }
}

/**********************************************************************************************************************
  Com_IpduGroupControl_EvaluateActiveState
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(boolean, COM_CODE) Com_IpduGroupControl_EvaluateActiveState(Com_IpduGroupVector ipduGroupVector, Com_TxPduInfoIterType ComTxPduId) /* PRQA S 3673, 3677 */ /* MD_MSR_Rule8.13, MD_Com_3677 */
{
  boolean bRequestedActiveState = FALSE;
  Com_PduGrpVectorEndIdxOfTxPduInfoType pduGrpVectorIdx = Com_GetPduGrpVectorStartIdxOfTxPduInfo(ComTxPduId);
  /* #10 Iterate over all ComIPdu related ComIPduGroup states and evaluate the current state of the passed ComIPdu */
  uint8_least iByteIndex = 0;
  for(; ((pduGrpVectorIdx < Com_GetPduGrpVectorEndIdxOfTxPduInfo(ComTxPduId)) && (bRequestedActiveState == FALSE)); pduGrpVectorIdx++)  /* COV_COM_IPDU_GROUP_STATE_ACTIVE */
  {
    if((ipduGroupVector[iByteIndex] & Com_GetPduGrpVector(pduGrpVectorIdx)) != 0u)
    {
      /* An I-PDU is active if and only if at least one I-PDU group is active it belongs to */
      bRequestedActiveState = TRUE;
    }
    iByteIndex++;       /* PRQA S 2983 */ /* MD_Com_2983 */
  }
  return bRequestedActiveState;
}
#endif

#if (COM_ACTIVATABLERXCOMIPDUS == STD_ON)
/**********************************************************************************************************************
  Com_IpduGroupControl_UpdateRxComIPduState
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
FUNC(void, COM_CODE) Com_IpduGroupControl_UpdateRxComIPduState(Com_IpduGroupVector ipduGroupVector, boolean initialize) /* PRQA S 3673, 3677 */ /* MD_MSR_Rule8.13, MD_Com_3677 */
{
  Com_ActivatableRxComIPdusIterType idx;

  Com_RxIPduGroup_EnterExclusiveArea();

  /* #10 Iterate over all Rx ComIPdus and evaluate the current state */
  for(idx = 0; idx < Com_GetSizeOfActivatableRxComIPdus(); idx++)
  {
    Com_RxPduInfoIterType ComRxPduId = Com_GetRxPduInfoIdxOfActivatableRxComIPdus(idx);

    /* Evaluate requested active state of the I-PDU */
    boolean bRequestedActiveState = FALSE;
    Com_PduGrpVectorEndIdxOfRxPduInfoType pduGrpVectorIdx = Com_GetPduGrpVectorStartIdxOfRxPduInfo(ComRxPduId);
    {
      /* #20 Iterate over all related ComIPduGroups of the current ComRxPdu */
      uint8_least iByteIndex = 0;
      for(; (pduGrpVectorIdx < Com_GetPduGrpVectorEndIdxOfRxPduInfo(ComRxPduId)) && (bRequestedActiveState == FALSE); pduGrpVectorIdx++)        /* COV_COM_IPDU_GROUP_STATE_ACTIVE */
      {
        /* #30 If at least one related ComIPduGroup is active the requested state is active */
        if((ipduGroupVector[iByteIndex] & Com_GetPduGrpVector(pduGrpVectorIdx)) != 0u)
        {
          /* An I-PDU is active if and only if at least one I-PDU group is active it belongs to */
          bRequestedActiveState = TRUE;
        }
        iByteIndex++;   /* PRQA S 2982, 2983 */ /* MD_Com_2982_Loop, MD_Com_2983 */
      }
    }
    /* COM615 For all I-PDUs that do not change their activation state, the function Com_IpduGroupControl shall do nothing. */
    /* #40 If the requested state is not equal to the current state */
    if((Com_IsRxPduGrpActive(ComRxPduId)) != bRequestedActiveState)
    {
      /* COM613 Second, the function Com_IpduGroupControl shall start or stop all I-PDUs that change theire activation state because of this call of Com_IpduGroupControl respectively. */
      /* #50 If the requested state is activated, activate Rx ComIPdu and optionally initialze the ComIPdu */
      if(bRequestedActiveState != FALSE)
      {
        /* Start Rx I-PDU */
        Com_ActivateRxComIPdu(ComRxPduId, initialize);
      }
      /* #90 Otherwise set the Rx ComIPdu state to inactive and deactivate all related Rx Timeout state machines */
      else      /* \trace SPEC-2736847 */
      {
        Com_DeactivateRxComIPdu(ComRxPduId);
      }
    }
    Com_RxIPduGroup_ThresholdCheck();
  }
  Com_RxIPduGroup_ExitExclusiveArea();
}
#endif

#if ((COM_RXTOUTINFO == STD_ON) && (COM_PDUGRPVECTOR == STD_ON) && (COM_ACTIVATABLERXCOMIPDUS == STD_ON))
/**********************************************************************************************************************
  Com_ReceptionDMControl_EvaluateActiveState
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(Com_RxPduDmStateType, COM_CODE) Com_ReceptionDMControl_EvaluateActiveState(Com_IpduGroupVector ipduGroupVector, Com_RxPduInfoIterType ComRxPduId)  /* PRQA S 3673, 3677 */ /* MD_MSR_Rule8.13, MD_Com_3677 */
{
  Com_RxPduDmStateType bRequestedActiveState = COM_INACTIVE_RXPDUDMSTATE;
  Com_PduGrpVectorEndIdxOfRxPduInfoType pduGrpVectorIdx = Com_GetPduGrpVectorStartIdxOfRxPduInfo(ComRxPduId);

  /* #10 Iterate over all ComIPdu related ComIPduGroup states and evaluate the current reception deadline monitoring state of the passed ComIPdu */
  uint8_least iByteIndex = 0;
  for(; ((pduGrpVectorIdx < Com_GetPduGrpVectorEndIdxOfRxPduInfo(ComRxPduId)) && (bRequestedActiveState == COM_INACTIVE_RXPDUDMSTATE)); pduGrpVectorIdx++)      /* COV_COM_IPDU_GROUP_STATE_ACTIVE */
  {
    if((ipduGroupVector[iByteIndex] & Com_GetPduGrpVector(pduGrpVectorIdx)) != 0u)
    {
      /* An I-PDU is active if and only if at least one I-PDU group is active it belongs to */
      bRequestedActiveState = COM_ACTIVE_RXPDUDMSTATE;
    }
    iByteIndex++;
  }
  return bRequestedActiveState;
}
#endif

#if ((COM_RXPDUINFOINDUSEDOFIPDUGROUPINFO == STD_ON) && (COM_RXTOUTINFOINDENDIDXOFRXPDUINFO == STD_ON))
/**********************************************************************************************************************
  Com_EnableReceptionDMsubGroup
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_EnableReceptionDMsubGroup(Com_IpduGroupIdType subIpduGroupId)
{
  /* #10 If the current deadline monitoring state is DMINACTIVE set the state to DMACTIVE */
  if(Com_GetIPduGroupState(subIpduGroupId) == COM_ACTIVE_DMINACTIVE_IPDUGROUPSTATE)
  {
    Com_SetIPduGroupState(subIpduGroupId, COM_ACTIVE_DMACTIVE_IPDUGROUPSTATE);  /* SBSW_COM_CSL02 */
    {
      /* #20 Iterate over all related Rx ComIPdus */
      Com_RxPduInfoIndEndIdxOfIPduGroupInfoType rxPduIndId = Com_GetRxPduInfoIndStartIdxOfIPduGroupInfo(subIpduGroupId);
      for(; rxPduIndId < Com_GetRxPduInfoIndEndIdxOfIPduGroupInfo(subIpduGroupId); rxPduIndId++)
      {
        Com_RxPduInfoIndType rxPduId = Com_GetRxPduInfoInd(rxPduIndId);
        /* #30 Iterate over all related Rx deadline monitoring state machines */
        Com_RxTOutInfoIndStartIdxOfRxPduInfoType idxRxTOutInfoInd = Com_GetRxTOutInfoIndStartIdxOfRxPduInfo(rxPduId);
        for(; idxRxTOutInfoInd < Com_GetRxTOutInfoIndEndIdxOfRxPduInfo(rxPduId); idxRxTOutInfoInd++)
        {
          Com_RxTOutInfoIndType idxRxTOutInfo = Com_GetRxTOutInfoInd(idxRxTOutInfoInd);
          /* #40 If the Rx deadline monitoring is INACTIVE, activate the Rx deadline monitoring */
          if((Com_GetRxPduDmState(idxRxTOutInfo) & COM_PURE_DM_STATE_MASK_RXPDUDMSTATE) == COM_INACTIVE_RXPDUDMSTATE)   /* COV_COM_IPDU_GROUP_DM_ASR3_TX */
          {
            Com_SetRxTOutCnt(idxRxTOutInfo, Com_GetFirstFactorOfRxTOutInfo(idxRxTOutInfo));     /* SBSW_COM_CSL02 */
            Com_SetRxPduDmState(idxRxTOutInfo, COM_ACTIVE_RXPDUDMSTATE);        /* SBSW_COM_CSL02 */
          }
        }
      }
    }
  }
}
#endif

#if ((COM_RXPDUINFOINDUSEDOFIPDUGROUPINFO == STD_ON) && (COM_RXTOUTINFOINDENDIDXOFRXPDUINFO == STD_ON))
/**********************************************************************************************************************
  Com_DisableReceptionDMsubGroup
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
FUNC(void, COM_CODE) Com_DisableReceptionDMsubGroup(Com_IpduGroupIdType subIpduGroupId)
{
  /* #10 If the current deadline monitoring state is DMACTIVE set the state to DMINACTIVE */
  if(Com_GetIPduGroupState(subIpduGroupId) == COM_ACTIVE_DMACTIVE_IPDUGROUPSTATE)
  {
    Com_SetIPduGroupState(subIpduGroupId, COM_ACTIVE_DMINACTIVE_IPDUGROUPSTATE);        /* SBSW_COM_CSL02 */
    {
      /* #20 Iterate over all related Rx ComIPdus */
      Com_RxPduInfoIndEndIdxOfIPduGroupInfoType rxPduIndId = Com_GetRxPduInfoIndStartIdxOfIPduGroupInfo(subIpduGroupId);
      for(; rxPduIndId < Com_GetRxPduInfoIndEndIdxOfIPduGroupInfo(subIpduGroupId); rxPduIndId++)
      {
        boolean canBeStopped = TRUE;
        Com_RxPduInfoIndType rxPduId = Com_GetRxPduInfoInd(rxPduIndId);
        /* #30 Iterate over all related ComIPduGroups */
        Com_IPduGroupInfoOfRxPduInfoIndEndIdxOfRxPduInfoType referencedIPduGroupInd = Com_GetIPduGroupInfoOfRxPduInfoIndStartIdxOfRxPduInfo(rxPduId);
        for(; referencedIPduGroupInd < Com_GetIPduGroupInfoOfRxPduInfoIndEndIdxOfRxPduInfo(rxPduId); referencedIPduGroupInd++)
        {
          /* #40 If at least one ComIPduGroup state is DMACTIVE the deadline monitoring states remain active */
          Com_IPduGroupInfoOfRxPduInfoIndType referencedIPduGroup = Com_GetIPduGroupInfoOfRxPduInfoInd(referencedIPduGroupInd);
          if(Com_GetIPduGroupState(referencedIPduGroup) == COM_ACTIVE_DMACTIVE_IPDUGROUPSTATE)
          {
            canBeStopped = FALSE;
            break;
          }
        }
        /* #50 If all ComIPduGroups are in state DMINACTIVE */
        if(canBeStopped == TRUE)
        {
          /* #60 Iterate all Rx deadline monitoring states and deactivate them */
          Com_RxTOutInfoIndStartIdxOfRxPduInfoType idxRxTOutInfoInd = Com_GetRxTOutInfoIndStartIdxOfRxPduInfo(rxPduId);
          for(; idxRxTOutInfoInd < Com_GetRxTOutInfoIndEndIdxOfRxPduInfo(rxPduId); idxRxTOutInfoInd++)
          {
            Com_LMgt_DeactivateRxIpduDm(Com_GetRxTOutInfoInd(idxRxTOutInfoInd));        /* SBSW_COM_CSL02_CSL03 */
          }
        }
      }
    }
  }
}
#endif

#if (COM_RXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxIPduGroup_EnterExclusiveArea
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_RxIPduGroup_EnterExclusiveArea(void)
{
  /* #10 Enter the rx IPduGroups exclusive area */
  SchM_Enter_Com_COM_EXCLUSIVE_AREA_RX();
}

/**********************************************************************************************************************
  Com_RxIPduGroup_ExitExclusiveArea
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_RxIPduGroup_ExitExclusiveArea(void)
{
  /* #05 Reload the counter with the threshold value */
  Com_SetRxIPduGroupISRLockCounter(Com_GetRxIPduGroupISRLockThreshold());       /* SBSW_COM_CSL_VAR_ACCESS */
  /* #10 Exit the rx IPduGroups exclusive area */
  SchM_Exit_Com_COM_EXCLUSIVE_AREA_RX();
}

/**********************************************************************************************************************
  Com_RxIPduGroup_ThresholdCheck
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_RxIPduGroup_ThresholdCheck(void)
{
  if(Com_GetRxIPduGroupISRLockCounter() > 0u)   /* COV_COM_THRESHOLD_TX */
  {
    Com_DecRxIPduGroupISRLockCounter(); /* SBSW_COM_CSL_VAR_ACCESS */
  }
  else
  {
    Com_RxIPduGroup_ExitExclusiveArea();
    Com_RxIPduGroup_EnterExclusiveArea();
  }
}
#endif

#if (COM_TXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_TxIPduGroup_EnterExclusiveArea
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxIPduGroup_EnterExclusiveArea(void)
{
  /* #10 Enter the tx IPduGroups exclusive area */
  SchM_Enter_Com_COM_EXCLUSIVE_AREA_TX();
}

/**********************************************************************************************************************
  Com_TxIPduGroup_ExitExclusiveArea
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxIPduGroup_ExitExclusiveArea(void)
{
  /* #05 Reload the counter with the threshold value */
  Com_SetTxIPduGroupISRLockCounter(Com_GetTxIPduGroupISRLockThreshold());       /* SBSW_COM_CSL_VAR_ACCESS */
  /* #10 Exit the tx IPduGroups exclusive area */
  SchM_Exit_Com_COM_EXCLUSIVE_AREA_TX();
}

/**********************************************************************************************************************
  Com_TxIPduGroup_ThresholdCheck
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxIPduGroup_ThresholdCheck(void)
{
  if(Com_GetTxIPduGroupISRLockCounter() > 0u)   /* COV_COM_THRESHOLD_TX */
  {
    Com_DecTxIPduGroupISRLockCounter(); /* SBSW_COM_CSL_VAR_ACCESS */
  }
  else
  {
    Com_TxIPduGroup_ExitExclusiveArea();
    Com_TxIPduGroup_EnterExclusiveArea();
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
   MD_Com_2982_Loop: Misra Rule 2.2
     Reason:     The number of loop iterations depends on the configuration. When there is only one iteration the value is optimized and isn't used before it is being modified.
     Risk:       No risk, because only warning that assignment is redundant.
     Prevention: No prevention necessary.
   MD_Com_2983: Misra Rule 2.2
     Reason:     The number of loop iterations depends on the configuration. When there is only one iteration the value is optimized and isn't used before it is being modified.
     Risk:       No risk, because only warning that assignment is redundant.
     Prevention: No prevention necessary.
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
 *  END OF FILE: Com_IPduGroupHdlr.c
 *********************************************************************************************************************/
