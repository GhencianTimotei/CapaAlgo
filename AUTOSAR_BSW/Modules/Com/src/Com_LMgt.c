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
/*!        \file  Com_LMgt.c
 *        \brief  MICROSAR Communication source file
 *
 *      \details  This is the implementation of the MICROSAR Communication module.
 *                The basic software module is based on the AUTOSAR Communication specification.
 *
 *********************************************************************************************************************/

#define COM_LMGT_SOURCE

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
#include "Com_LMgt.h"
#include "Com_LLIf.h"
#include "Com_Timer.h"
#include "Com_Buffers.h"
#include "Com_Gateway.h"
#include "Com_TxModeHdlr.h"
#include "Com_RxProcessing.h"
#include "Com_IPduGroupHdlr.h"
#include "Com_Notifications.h"
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

#if (COM_TXSIGGRPINFOINDENDIDXOFTXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_SignalGroup_InitTxIpdu
**********************************************************************************************************************/
/*! \brief        This function initializes a tx I-PDU in Com_Signal.
    \details      -
    \pre          -
    \param[in]    ComPduId Handle of the I-PDU.
    \context      TASK
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_SignalGroup_InitTxIpdu(Com_TxPduInfoIterType ComPduId);
#endif

#if (COM_RXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_LMgt_DeactivateRxPdu
**********************************************************************************************************************/
/*! \brief        This function deactivates the given Rx I-PDU.
    \details      -
    \pre          -
    \param[in]    ComPduId Handle of the I-PDU.
    \context      TASK
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_LMgt_DeactivateRxPdu(PduIdType ComPduId);
#endif


/**********************************************************************************************************************
  LOCAL FUNCTIONS
**********************************************************************************************************************/

#if (COM_TXSIGGRPINFOINDENDIDXOFTXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_SignalGroup_InitTxIpdu
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_SignalGroup_InitTxIpdu(Com_TxPduInfoIterType ComPduId)
{
  /* COM484: initialize Tx shadow buffer */
  /* #10 Initialize all related Tx ComSignalGroup shadow buffer of the passed ComIPdu */
  Com_TxSigGrpInfoIndEndIdxOfTxPduInfoType idxTxSigGrpInfoInd = Com_GetTxSigGrpInfoIndStartIdxOfTxPduInfo(ComPduId);
  for(; idxTxSigGrpInfoInd < Com_GetTxSigGrpInfoIndEndIdxOfTxPduInfo(ComPduId); idxTxSigGrpInfoInd++)
  {
    Com_TxSigGrpInfoIndType sigGrpHnd = Com_GetTxSigGrpInfoInd(idxTxSigGrpInfoInd);

# if (COM_TXBUFFERUSEDOFTXSIGGRPINFO == STD_ON)
    if(Com_IsTxBufferUsedOfTxSigGrpInfo(sigGrpHnd))     /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
    {
      /* Com_TxBuffer_IpduInitValue contains the initial values for all I-PDUs. It is only required to copy the initial values that are relevant for the signal group buffer. */
      VStdMemCpyRomToRam(Com_GetAddrTxBuffer(Com_GetTxBufferStartIdxOfTxSigGrpInfo(sigGrpHnd)), Com_GetAddrTxPduInitValue(Com_GetTxPduInitValueStartIdxOfTxPduInfo(ComPduId) + Com_GetPduOffsetOfTxSigGrpInfo(sigGrpHnd)), (uint16_least) Com_GetTxBufferLengthOfTxSigGrpInfo(sigGrpHnd));      /* PRQA S 0315, 2985 */ /* MD_MSR_VStdLibCopy, MD_Com_2985_2986 */ /* SBSW_COM_MEM_CPY_2RAM */
    }
# endif

    /* #20 Clear the ComSignalGroup event flag */
    Com_SetSigGrpEventFlag(sigGrpHnd, 0u);      /* SBSW_COM_CSL03 */
  }
}
#endif

#if (COM_RXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_LMgt_DeactivateRxPdu
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_LMgt_DeactivateRxPdu(PduIdType ComPduId)
{
# if (COM_RXTOUTINFOINDENDIDXOFRXPDUINFO == STD_ON)
  {
    /* #10 Iterate over all related timeout handling state machines and deactivate timeout handling */
    Com_RxTOutInfoIndStartIdxOfRxPduInfoType idxRxTOutInfoInd = Com_GetRxTOutInfoIndStartIdxOfRxPduInfo(ComPduId);
    for(; idxRxTOutInfoInd < Com_GetRxTOutInfoIndEndIdxOfRxPduInfo(ComPduId); idxRxTOutInfoInd++)
    {
      Com_LMgt_DeactivateRxIpduDm(Com_GetRxTOutInfoInd(idxRxTOutInfoInd));      /* SBSW_COM_CSL02_CSL03 */
    }
  }
# endif

  /* #20 Deactivate the Pdu Group state of the passed ComIPdu */
  Com_SetRxPduGrpActive(ComPduId, FALSE);       /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
}
#endif


/**********************************************************************************************************************
  GLOBAL FUNCTIONS
**********************************************************************************************************************/

#if (COM_RXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_LMgt_InitRxIpdu
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_LMgt_InitRxIpdu(PduIdType ComPduId)
{
  /* #10 Initialize the signal buffers */
  Com_RxProcessing_InitRxIpdu(ComPduId);
# if (COM_RXTOUTINFOINDENDIDXOFRXPDUINFO == STD_ON)
  /* #20 Initialize the Rx Timeout handling parameters */
  Com_RxDlMon_InitRxIpdu(ComPduId);
# endif
# if (COM_GWINFOENDIDXOFRXPDUINFO == STD_ON)
  /* #30 Initialize the Signal Gateway parameters */
  Com_SignalGw_InitRxIpdu(ComPduId);
# endif

# if (COM_DEFERREDGWMAPPINGINFOUSEDOFRXPDUINFO == STD_ON)       /* COV_COM_VAR_ELISA_STD_OFF_XF */
  /* #50 If generated description routing code is used and the ComIPdu is a deferred gateway description source ComIPdu, reset the gwMappingEvent flag */
  if(Com_IsDeferredGwMappingInfoUsedOfRxPduInfo(ComPduId))
  {
    Com_SetDeferredGwMappingEvent(Com_GetDeferredGwMappingInfoIdxOfRxPduInfo(ComPduId), 0);     /* SBSW_COM_CSL02_CSL03 */
  }
# endif

}
#endif


#if (COM_TXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_LMgt_InitTxIpdu
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_LMgt_InitTxIpdu(Com_TxPduInfoIterType ComPduId)
{
# if (COM_TXSIGGRPINFOINDENDIDXOFTXPDUINFO == STD_ON)
  /* #10 Initialize SignalGroup parameters */
  Com_SignalGroup_InitTxIpdu(ComPduId);
# endif

  /* #20 Initialize ComIPdu length */
  Com_TxLLIf_InitTxIpdu(ComPduId);

# if (COM_TXBUFFERUSEDOFTXPDUINFO == STD_ON)
  /* #30 Initialize the ComIPdu TxBuffer */
  Com_TxBuffer_InitTxIpdu(ComPduId);
# endif

  /* #40 Initialize filter states and Tx mode parameter */
  Com_TxModeHdlr_InitTxIpdu((PduIdType) ComPduId);

# if ((COM_CBKTXACKDEFFUNCPTRINDUSEDOFTXPDUINFO == STD_ON)||(COM_CBKTXERRFUNCPTRINDUSEDOFTXPDUINFO == STD_ON))
  /* #50 Initialize HandleDeferred and WaitForConfirmation flags */
  Com_TxNHdlr_InitTxIpdu(ComPduId);
# endif
}
#endif

#if (COM_RXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_InitRx
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_InitRx(void)
{
  Com_RxPduInfoIterType ComRxPduId = 0u;
  /* #10 Iterate over all Rx ComIPdus and initialize all related parameters */
  for(; ComRxPduId < Com_GetSizeOfRxPduInfo(); ComRxPduId++)
  {
# if (COM_INVALIDHNDOFRXPDUINFO == STD_ON)
    if(!Com_IsInvalidHndOfRxPduInfo(ComRxPduId))
# endif
    {
      Com_LMgt_InitRxIpdu((PduIdType) ComRxPduId);

      /* The IPdu must be deactivated after all initialization tasks of this IPdu! */
      Com_LMgt_DeactivateRxPdu((PduIdType) ComRxPduId);
    }
  }
}
#endif

#if (COM_TXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_InitTx
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *    -
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_InitTx(void)
{
  Com_TxPduInfoIterType ComTxPduId = 0u;
  /* #10 Iterate over all Tx ComIPdus and initialize all related parameters */
  for(; ComTxPduId < Com_GetSizeOfTxPduInfo(); ComTxPduId++)
  {
# if (COM_INVALIDHNDOFTXPDUINFO == STD_ON)
    if(!Com_IsInvalidHndOfTxPduInfo(ComTxPduId))
# endif
    {
# if ((COM_REPCNTOFTXMODETRUE == STD_ON) || (COM_REPCNTOFTXMODEFALSE == STD_ON))
      Com_SetRepCnt(ComTxPduId, 0u);    /* SBSW_COM_CSL02 */
      Com_SetRepCycleCnt(ComTxPduId, 0u);       /* SBSW_COM_CSL02 */
# endif
      Com_LMgt_InitTxIpdu(ComTxPduId);
      /* The Ipdu must be activated after all initialization tasks of this Ipdu! */
# if (COM_MIXEDMODEPERIODICSUPPRESSION == STD_ON)
      Com_SetInitialTransmit(ComTxPduId, FALSE);        /* SBSW_COM_CSL02 */
# endif
# if (COM_TXTPINFOUSEDOFTXPDUINFO == STD_ON)
      if(Com_IsTxTpInfoUsedOfTxPduInfo(ComTxPduId))     /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
      {
        Com_ResetTxTpConnection((PduIdType) ComTxPduId);
      }
# endif

      Com_SetTxPduGrpActive(ComTxPduId, FALSE); /* SBSW_COM_CSL02 */
    }
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
 *  END OF FILE: Com_LMgt.c
 *********************************************************************************************************************/
