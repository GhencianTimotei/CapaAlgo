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
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  PduR_RmTp_TxInst.c
 *      Project:  Gw_AsrPduRCfg5
 *       Module:  MICROSAR PDU Router
 *    Generator:  Configurator 5
 *
 *  Description:  Vector implementation of AUTOSAR PDU Router
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

/**********************************************************************************************************************
 * LOCAL MISRA / PCLINT JUSTIFICATION
 *********************************************************************************************************************/
/* PRQA  S 3673 EOF */ /* MD_MSR_Rule8.13 */

#define PDUR_RMTP_TXINST_SOURCE
/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "PduR.h"
#include "PduR_Bm.h"
#include "PduR_Fm.h"
#include "PduR_RmTp.h"
#include "PduR_RmTp_TxInst.h"
#include "PduR_Lock.h"
#if (PDUR_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/
#if !defined (PDUR_LOCAL_INLINE)
# define PDUR_LOCAL_INLINE LOCAL_INLINE
#endif

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h" /* PRQA S 5087 */   /* MD_MSR_MemMap */

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_TxInst_LoAndUpTransmit
 *********************************************************************************************************************/
/*! \brief      This function triggers the transmission on the destination bus(es). In case of a
 *              1:N routing including a upper layer module StartOfReception/ CopyRxData/
 *              and the Indication API of the upper layer is called.
 *  \details    -
 *  \param[in]  rmGDestRomIdx    Routing Manager GDest Idx.
 *  \return     E_OK             successful transmission.
 *              E_NOT_OK         transmission failing
 *  \pre        -
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_TxInst_LoAndUpTransmit(PduR_RmGDestRomIterType rmGDestRomIdx);
#endif

#if ((PDUR_UPTPOFMMROM == STD_ON) && (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON))
/**********************************************************************************************************************
 * PduR_RmTp_TxInst_UpTransmit
 *********************************************************************************************************************/
/*! \brief      This function triggers the reception in an upper layer module in case of an
 *              1:N routing including an upper layer module StartOfReception/ CopyRxData/
 *              an the Indication API of the upper layer is called.
 *  \details    -
 *  \param[in]  rmGDestRomIdx           Routing Manager GDest Idx.
 *  \trace      SPEC-2020176
 *  \return     BUFREQ_OK               Buffer request was successful.
 *              BUFREQ_E_NOT_OK         Currently no buffer available.
 *  \pre        -
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_TxInst_UpTransmit(PduR_RmGDestRomIterType rmGDestRomIdx);
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_TxInst_LoTransmit
 *********************************************************************************************************************/
/*! \brief      This function triggers the transmission in an lower layer module.
 *  \details    -
 *  \param[in]  rmGDestRomIdx Routing Manager GDest Idx.
 *  \return     E_OK          Transmission successful.
 *              E_NOT_OK      Transmission not successful.
 *  \pre        -
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_TxInst_LoTransmit(PduR_RmGDestRomIterType rmGDestRomIdx);
#endif

# if ((PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON) && (PDUR_EXISTS_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM == STD_ON))
/**********************************************************************************************************************
 * PduR_RmTp_TxInst_TriggerTransmit_Immediate
 *********************************************************************************************************************/
/*! \brief       The function is called to start the transmission and perform TxSm state handling
 *  \details     TxSm is in the state "Idle"
 *  \param[in]   rmDestRomIdx   Id of destination PDU reference.
 *  \param[in]   rmGDestRomIdx  Id of global PDU reference.
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 ***********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_TxInst_TriggerTransmit_Immediate(PduR_RmDestRomIterType rmDestRomIdx, PduR_RmGDestRomIterType rmGDestRomIdx);
# endif

# if ((PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON) && (PDUR_EXISTS_DEFERRED_PDURDESTPDUPROCESSINGOFRMGDESTROM == STD_ON))
/**********************************************************************************************************************
 * PduR_RmTp_TxInst_TriggerTransmit_Deferred
 *********************************************************************************************************************/
/*! \brief       This function moves the tigger transmit call to the main task
 *  \details     TxSm is in the state "Idle"
 *  \param[in]   rmDestRomIdx   Id of destination PDU reference.
 *  \param[in]   rmGDestRomIdx  Id of global PDU reference.
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 ***********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_TxInst_TriggerTransmit_Deferred(PduR_RmDestRomIterType rmDestRomIdx, PduR_RmGDestRomIterType rmGDestRomIdx);
# endif

# if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_TxInst_TriggerTransmit_FatalError
 *********************************************************************************************************************/
/*! \brief       If this function is called something went totally wrong
 *  \details     -
 *  \param[in]   rmDestRomIdx   Id of destination PDU reference.
 *  \param[in]   rmGDestRomIdx  Id of global PDU reference.
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 ***********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_TxInst_TriggerTransmit_FatalError(PduR_RmDestRomIterType rmDestRomIdx, PduR_RmGDestRomIterType rmGDestRomIdx);
# endif

# if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_TxInst_CopyTxData_RmTxInstActive
 *********************************************************************************************************************/
/*! \brief       This function is called by the PduR GwTp to query the transmit data of an I-PDU segment.
 *  \details     TxSm is in the state "Active"
 *  \param[in]   rmGDestRomIdx     Routing Manager GDest Idx.
 *  \param[in]   pduLength         length to copy.
 *  \param[out]  sduDataPtr        data pointer.
 *                                 A copy size of 0 can be used to get the available data size.
 *  \param[in]   retry             not supported
 *  \param[out]  availableDataPtr  Indicates the remaining number of bytes that are available in the PduR Tx buffer.
 *                                 AvailableTxDataCntPtr can be used by TP modules that support dynamic payload lengths
 *                                 (e.g. Iso FrTp) to determine the size of the following CFs.
 *  \return      BufReq_ReturnType
 *               BUFREQ_OK         The data has been copied successfully.
 *               BUFREQ_E_NOT_OK   Get data fails.
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 ***********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_TxInst_CopyTxData_RmTxInstActive(PduR_RmGDestRomIterType rmGDestRomIdx, PduLengthType pduLength,
                                                                              SduDataPtrType sduDataPtr,
                                                                              P2CONST(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA) retry, P2VAR(PduLengthType, AUTOMATIC,
                                                                                                                                             PDUR_APPL_DATA) availableDataPtr);
# endif

# if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_TxInst_CopyTxData_UnexpectedCall
 *********************************************************************************************************************/
/*! \brief       This function is called by the PduR GwTp to query the transmit data of an I-PDU segment. But the
 *               routing is already aborted.
 *  \details     TxSm is in the state "Aborted"
 *  \param[in]   rmGDestRomIdx    Routing Manager GDest Idx.
 *  \param[in]   pduLength         length to copy.
 *  \param[out]  sduDataPtr        data pointer.
 *                                 A copy size of 0 can be used to get the available data size.
 *  \param[in]   retry             not supported
 *  \param[out]  availableDataPtr  Indicates the remaining number of bytes that are available in the PduR Tx buffer.
 *                                 AvailableTxDataCntPtr can be used by TP modules that support dynamic payload lengths
 *                                 (e.g. Iso FrTp) to determine the size of the following CFs.
 *  \return      BufReq_ReturnType
 *               BUFREQ_OK         The data has been copied successfully.
 *               BUFREQ_E_NOT_OK   Get data fails.
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 ***********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_TxInst_CopyTxData_UnexpectedCall(PduR_RmGDestRomIterType rmGDestRomIdx, PduLengthType pduLength,
                                                                              SduDataPtrType sduDataPtr,
                                                                              P2CONST(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA) retry, P2VAR(PduLengthType, AUTOMATIC,
                                                                                                                                             PDUR_APPL_DATA) availableDataPtr);
# endif

# if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_TxInst_CopyTxData_RmTxInstAborted
 *********************************************************************************************************************/
/*! \brief       This function is called by the PduR GwTp to query the transmit data of an I-PDU segment. But the
 *               routing is already aborted.
 *  \details     TxSm is in the state "Aborted"
 *  \param[in]   rmGDestRomIdx     Routing Manager GDest Idx.
 *  \param[in]   pduLength         length to copy.
 *  \param[out]  sduDataPtr        data pointer.
 *                                 A copy size of 0 can be used to get the available data size.
 *  \param[in]   retry             not supported
 *  \param[out]  availableDataPtr  Indicates the remaining number of bytes that are available in the PduR Tx buffer.
 *                                 AvailableTxDataCntPtr can be used by TP modules that support dynamic payload lengths
 *                                 (e.g. Iso FrTp) to determine the size of the following CFs.
 *  \return      BufReq_ReturnType
 *               BUFREQ_E_NOT_OK   Routing is aborted
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 ***********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_TxInst_CopyTxData_RmTxInstAborted(PduR_RmGDestRomIterType rmGDestRomIdx, PduLengthType pduLength,
                                                                               SduDataPtrType sduDataPtr,
                                                                               P2CONST(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA) retry, P2VAR(PduLengthType, AUTOMATIC,
                                                                                                                                              PDUR_APPL_DATA) availableDataPtr);
# endif

# if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_TxInst_TxConfirmation_RmTxInstActiveOrRmTxInstAborted
 *********************************************************************************************************************/
/*! \brief       The function confirms a successful transmission of a GwTp TX SDU or to report an error that
 *               occurred during transmission.
 *  \details     TxSm is in the state Active Or Aborted. In case of 1:N result E_NOT_OK is acceptable, decrement Confirmation count.
 *  \param[in]   rmGDestRomIdx Routing Manager GDest Idx.
 *  \param[out]  result     result of the transmission.
 *               E_OK       The TP transmission has been completed successfully.\n
 *               E_NOT_OK   The transmission fails.
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
***********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmTp_TxInst_TxConfirmation_RmTxInstActiveOrRmTxInstAborted(PduR_RmGDestRomIterType rmGDestRomIdx, Std_ReturnType result);
# endif

# if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_TxInst_TxConfirmation_UnexpectedCall
 *********************************************************************************************************************/
/*! \brief       The function is called unexpectedly because the TxSm is in state "Idle"
 *  \details     -
 *  \param[in]   rmGDestRomIdx Routing Manager GDest Idx.
 *  \param[out]  result     result of the transmission.
 *               E_OK       The TP transmission has been completed successfully.\n
 *               E_NOT_OK   The transmission fails.
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
***********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmTp_TxInst_TxConfirmation_UnexpectedCall(PduR_RmGDestRomIterType rmGDestRomIdx, Std_ReturnType result);
# endif

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

#if ((PDUR_UPTPOFMMROM == STD_ON) && (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON))
/**********************************************************************************************************************
 * PduR_RmTp_TxInst_UpTransmit
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
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_TxInst_UpTransmit(PduR_RmGDestRomIterType rmGDestRomIdx)
{
  Std_ReturnType retVal = E_NOT_OK;     /* PRQA S 2981 */ /* MD_MSR_RetVal */
  BufReq_ReturnType retValBufReq;
  PduLengthType bufferSizePtr = 0u;
  PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx;

  if(PduR_Fm_GetCurrentlyUsedBmTxBufferInstanceIdxByRmGDestIdx(rmGDestRomIdx, &bmTxBufferInstanceRomIdx) == E_OK) /* SBSW_PDUR_STACK_VARIABLE */ /* COV_PDUR_ROBUSTNESS */
  {
    PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfRmGDestRom(rmGDestRomIdx);
    PduLengthType actualPduLengthToBeRouted = PduR_Bm_GetActualPduLengthToBeRouted(bmTxBufferInstanceRomIdx, memIdx);

    /* If MetaData are available the pUpperLayerInfo points to MetaData */
    {
# if (PDUR_METADATA_SUPPORT == STD_ON)
      PduR_RmSrcRomIterType rmSrcIdx = PduR_GetRmSrcRomIdxOfRmDestRom(PduR_GetRmDestRomIdxOfFmFifoElementRam(PduR_Fm_GetFmFifoElementRamReadIdxOfFmFifoRamSafe(PduR_GetFmFifoRomIdxOfFmFifoInstanceRom(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx), memIdx), memIdx), memIdx));

      if(PduR_IsRmBufferedTpPropertiesRomUsedOfRmSrcRom(rmSrcIdx) && PduR_IsMetaDataLengthUsedOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx), memIdx)) /* COV_PDUR_ROBUSTNESS */
      {
        PduInfoType metaInfo;
        PduR_Bm_CopyDataAsPtr(bmTxBufferInstanceRomIdx, &metaInfo, PduR_GetMetaDataLengthOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx), memIdx), memIdx); /* SBSW_PDUR_STACK_VARIABLE */
        (void) PduR_Bm_GetData(bmTxBufferInstanceRomIdx, metaInfo.SduLength, metaInfo.SduDataPtr, memIdx); /* SBSW_PDUR_STACK_VARIABLE */

        retValBufReq = PduR_GetUpTpStartOfReceptionFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx), &metaInfo, actualPduLengthToBeRouted, &bufferSizePtr);    /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
      }
      else
# endif
      {
        retValBufReq = PduR_GetUpTpStartOfReceptionFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx), (P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA)) NULL_PTR, actualPduLengthToBeRouted, &bufferSizePtr);     /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
      }
    }
    if(retValBufReq == BUFREQ_OK)
    {
      /* RfC 52242 - Transport Protocol Gateway Reception to upper layer modules is not functional */
      /* \trace SPEC-2020098 */
      if(bufferSizePtr < actualPduLengthToBeRouted)
      {
        PduR_GetUpTpTpRxIndicationFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx), E_NOT_OK);      /* SBSW_PDUR_API_CALL_FORWARDING_ID_ONLY */
      }
      else
      {
        PduInfoType info;
        PduR_Bm_CopyDataAsPtr(bmTxBufferInstanceRomIdx, &info, PduR_Bm_GetLinearDataSizeInstance(bmTxBufferInstanceRomIdx, memIdx), memIdx); /* SBSW_PDUR_STACK_VARIABLE */
        (void) PduR_Bm_GetData(bmTxBufferInstanceRomIdx, info.SduLength, info.SduDataPtr, memIdx); /* SBSW_PDUR_STACK_VARIABLE */

        if(BUFREQ_OK == PduR_GetUpTpCopyRxDataFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx), &info, &bufferSizePtr))     /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
        {
          PduR_GetUpTpTpRxIndicationFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx), E_OK);        /* SBSW_PDUR_API_CALL_FORWARDING_ID_ONLY */
          retVal = E_OK;
        }
        else      /* \trace SPEC-2020102 */
        {
          PduR_GetUpTpTpRxIndicationFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx), E_NOT_OK);    /* SBSW_PDUR_API_CALL_FORWARDING_ID_ONLY */
        }
      }
    }
    if(E_OK == retVal)
    {
      PduR_RmTp_TxInst_TxConfirmation(rmGDestRomIdx, E_OK);
    }
    else
    {
      PduR_RmTp_TxInst_TxConfirmation(rmGDestRomIdx, E_NOT_OK);
    }
  }
  return retVal;
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
  PduR_RmTp_TxInst_LoTransmit
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_TxInst_LoTransmit(PduR_RmGDestRomIterType rmGDestRomIdx)
{
  Std_ReturnType retVal = E_NOT_OK;     /* PRQA S 2981 */ /* MD_MSR_RetVal */

  PduInfoType info;
  PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx;

  if(PduR_Fm_GetCurrentlyUsedBmTxBufferInstanceIdxByRmGDestIdx(rmGDestRomIdx, &bmTxBufferInstanceRomIdx) == E_OK) /* SBSW_PDUR_STACK_VARIABLE */ /* COV_PDUR_ROBUSTNESS */
  {
    PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfRmGDestRom(rmGDestRomIdx);
    PduLengthType actualPduLengthToBeRouted = PduR_Bm_GetActualPduLengthToBeRouted(bmTxBufferInstanceRomIdx, memIdx);

    /* Get Data Pointer for Transmit */
    PduR_Bm_CopyDataAsPtr(bmTxBufferInstanceRomIdx, &info, actualPduLengthToBeRouted, memIdx);       /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */

# if (PDUR_METADATA_SUPPORT == STD_ON)
    {
      PduR_RmSrcRomIterType rmSrcIdx = PduR_GetRmSrcRomIdxOfRmDestRom(PduR_GetRmDestRomIdxOfFmFifoElementRam(PduR_Fm_GetFmFifoElementRamReadIdxOfFmFifoRamSafe(PduR_GetFmFifoRomIdxOfFmFifoInstanceRom(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx), memIdx), memIdx), memIdx));

      if(PduR_IsRmBufferedTpPropertiesRomUsedOfRmSrcRom(rmSrcIdx) && PduR_IsMetaDataLengthUsedOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx), memIdx)) /* COV_PDUR_ROBUSTNESS */
      {
        /* Get Meta Data Pointer for Transmit */
        PduR_Bm_CopyDataAsPtr(bmTxBufferInstanceRomIdx, &info, (PduR_BmTxBufferArrayRamIterType) PduR_GetMetaDataLengthOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx), memIdx), memIdx); /* SBSW_PDUR_STACK_VARIABLE */
        (void) PduR_Bm_GetData(bmTxBufferInstanceRomIdx, info.SduLength, info.SduDataPtr, memIdx); /* SBSW_PDUR_STACK_VARIABLE */
      }
    }
# endif

    /* Correction of the length according to AUTOSAR */
    info.SduLength = actualPduLengthToBeRouted;

    if(E_OK == PduR_GetLoTpTransmitFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx), &info))        /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
    {
      retVal &= E_OK;
    }
    else
    {
      PduR_RmTp_TxInst_TxConfirmation(rmGDestRomIdx, E_NOT_OK);
    }
  }

  return retVal;
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
  PduR_RmTp_TxInst_LoAndUpTransmit
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *********************************************************************************************************************/

PDUR_LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_TxInst_LoAndUpTransmit(PduR_RmGDestRomIterType rmGDestRomIdx)
{
  Std_ReturnType retVal = E_NOT_OK;     /* PRQA S 2981 */ /* MD_MSR_RetVal */
  /* Confirmations are decremented in the Context of LoAndUpTransmit and CopyTxData */
  {
    /* Iterate over all routing destinations (1:N) */
    if(PduR_GetDirectionOfRmGDestRom(rmGDestRomIdx) == PDUR_TX_DIRECTIONOFRMGDESTROM)   /* COV_PDUR_FEATURE_ALWAYS_TRUE */
    {
      retVal = PduR_RmTp_TxInst_LoTransmit(rmGDestRomIdx);
    }
# if (PDUR_UPTPOFMMROM == STD_ON)
    else
    {
      retVal = PduR_RmTp_TxInst_UpTransmit(rmGDestRomIdx);
    }
# endif
  }
  return retVal;
}
#endif

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_TxInst_TriggerTransmit
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_TxInst_TriggerTransmit(PduR_RmDestRomIterType rmDestRomIdx, PduR_RmGDestRomIterType rmGDestRomIdx)
{
  Std_ReturnType retVal = E_NOT_OK;
  PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfRmGDestRom(rmGDestRomIdx);

  switch (PduR_GetTpTxInstSmStateOfRmGDestTpTxStateRam(PduR_GetRmGDestTpTxStateRamIdxOfRmGDestRom(rmGDestRomIdx), memIdx))
  {
    case PDUR_RM_TXINST_IDLE_TPTXINSTSMSTATEOFRMGDESTTPTXSTATERAM:
      switch (PduR_GetPduRDestPduProcessingOfRmGDestRom(rmGDestRomIdx))
      {
# if (PDUR_EXISTS_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM == STD_ON)
        case PDUR_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM:
          retVal = PduR_RmTp_TxInst_TriggerTransmit_Immediate(rmDestRomIdx, rmGDestRomIdx);
          break;
# endif
# if (PDUR_EXISTS_DEFERRED_PDURDESTPDUPROCESSINGOFRMGDESTROM == STD_ON)
        case PDUR_DEFERRED_PDURDESTPDUPROCESSINGOFRMGDESTROM:
          retVal = PduR_RmTp_TxInst_TriggerTransmit_Deferred(rmDestRomIdx, rmGDestRomIdx);
          break;
# endif
        default:     /* COV_PDUR_MISRA */
          /* Nothing to do: This should never be reached */
          break;
      }
      break;

    case PDUR_RM_TXINST_ACTIVE_TPTXINSTSMSTATEOFRMGDESTTPTXSTATERAM: /* COV_PDUR_FATAL_ERROR */
# if (PDUR_EXISTS_DEFERRED_PDURDESTPDUPROCESSINGOFRMGDESTROM == STD_ON)
    case PDUR_RM_TXINST_WAITING_TPTXINSTSMSTATEOFRMGDESTTPTXSTATERAM: /* COV_PDUR_FATAL_ERROR */
# endif
    case PDUR_RM_TXINST_ABORTED_TPTXINSTSMSTATEOFRMGDESTTPTXSTATERAM: /* COV_PDUR_FATAL_ERROR */
      retVal = PduR_RmTp_TxInst_TriggerTransmit_FatalError(rmDestRomIdx, rmGDestRomIdx);
      break;

    default: /* COV_PDUR_MISRA */
      /* If state is out-of-bounds: do nothing and return negative result. */
      retVal = E_NOT_OK;
      break;
  }


  return retVal;
}
#endif

#if ((PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON) && (PDUR_EXISTS_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM == STD_ON))
/**********************************************************************************************************************
 * PduR_RmTp_TxInst_TriggerTransmit_Immediate
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_TxInst_TriggerTransmit_Immediate(PduR_RmDestRomIterType rmDestRomIdx, PduR_RmGDestRomIterType rmGDestRomIdx)       /* COV_PDUR_CROSSCORE_ROUTINGS_ONLY */
{
  PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfRmGDestRom(rmGDestRomIdx);

  PduR_SetTpTxInstSmStateOfRmGDestTpTxStateRam(PduR_GetRmGDestTpTxStateRamIdxOfRmGDestRom(rmGDestRomIdx), PDUR_RM_TXINST_ACTIVE_TPTXINSTSMSTATEOFRMGDESTTPTXSTATERAM, memIdx);  /* SBSW_PDUR_CSL03 */
  PDUR_DUMMY_STATEMENT(rmDestRomIdx);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  return PduR_RmTp_TxInst_LoAndUpTransmit(rmGDestRomIdx);
}
#endif

#if ((PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON) && (PDUR_EXISTS_DEFERRED_PDURDESTPDUPROCESSINGOFRMGDESTROM == STD_ON))
/**********************************************************************************************************************
 * PduR_RmTp_TxInst_TriggerTransmit_Deferred
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_TxInst_TriggerTransmit_Deferred(PduR_RmDestRomIterType rmDestRomIdx, PduR_RmGDestRomIterType rmGDestRomIdx)    /* COV_PDUR_NO_DEFERRED_TP_ROUTING */
{
  Std_ReturnType retVal = E_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfRmGDestRom(rmGDestRomIdx);

  PduR_SetTpTxInstSmStateOfRmGDestTpTxStateRam(PduR_GetRmGDestTpTxStateRamIdxOfRmGDestRom(rmGDestRomIdx), PDUR_RM_TXINST_WAITING_TPTXINSTSMSTATEOFRMGDESTTPTXSTATERAM, memIdx); /* SBSW_PDUR_CSL03 */

# if (PDUR_DEFERREDEVENTCACHEROM == STD_ON)
  PduR_EvC_WriteDeferredEventCache(rmDestRomIdx, (PduR_RmGDestRomIdxOfRmDestRomType) rmGDestRomIdx);
# endif
  PDUR_DUMMY_STATEMENT(rmDestRomIdx);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return retVal;
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_TxInst_TriggerTransmit_FatalError
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_TxInst_TriggerTransmit_FatalError(PduR_RmDestRomIterType rmDestRomIdx, PduR_RmGDestRomIterType rmGDestRomIdx) /* COV_PDUR_FATAL_ERROR */
{
  PduR_Det_ReportError(PDUR_RM_TPTRIGGERTRANSMIT_FATALERROR, PDUR_E_FATAL);
  PDUR_DUMMY_STATEMENT(rmDestRomIdx);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(rmGDestRomIdx);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  return E_NOT_OK;
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_TxInst_CopyTxData
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_TxInst_CopyTxData(PduR_RmGDestRomIterType rmGDestRomIdx, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, P2VAR(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA) retry, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) availableDataPtr)      /* PRQA S 3673 */ /* MD_MSR_Rule8.13 */
{
  BufReq_ReturnType retVal;
  PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfRmGDestRom(rmGDestRomIdx);

  switch (PduR_GetTpTxInstSmStateOfRmGDestTpTxStateRam(PduR_GetRmGDestTpTxStateRamIdxOfRmGDestRom(rmGDestRomIdx), memIdx))
  {
    case PDUR_RM_TXINST_IDLE_TPTXINSTSMSTATEOFRMGDESTTPTXSTATERAM:
      retVal = PduR_RmTp_TxInst_CopyTxData_UnexpectedCall(rmGDestRomIdx, info->SduLength, info->SduDataPtr, retry, availableDataPtr);  /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
      break;

    case PDUR_RM_TXINST_ACTIVE_TPTXINSTSMSTATEOFRMGDESTTPTXSTATERAM:
      retVal = PduR_RmTp_TxInst_CopyTxData_RmTxInstActive(rmGDestRomIdx, info->SduLength, info->SduDataPtr, retry, availableDataPtr);  /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
      break;

# if (PDUR_EXISTS_DEFERRED_PDURDESTPDUPROCESSINGOFRMGDESTROM == STD_ON)
    case PDUR_RM_TXINST_WAITING_TPTXINSTSMSTATEOFRMGDESTTPTXSTATERAM:
      retVal = PduR_RmTp_TxInst_CopyTxData_UnexpectedCall(rmGDestRomIdx, info->SduLength, info->SduDataPtr, retry, availableDataPtr);  /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
      break;
# endif

    case PDUR_RM_TXINST_ABORTED_TPTXINSTSMSTATEOFRMGDESTTPTXSTATERAM:
      retVal = PduR_RmTp_TxInst_CopyTxData_RmTxInstAborted(rmGDestRomIdx, info->SduLength, info->SduDataPtr, retry, availableDataPtr);  /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
      break;

    default: /* COV_PDUR_MISRA */
      /* If state is out-of-bounds: do nothing and return negative result. */
      retVal = BUFREQ_E_NOT_OK;
      break;
  }

  return retVal;
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_TxInst_CopyTxData_RmTxInstActive
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_TxInst_CopyTxData_RmTxInstActive(PduR_RmGDestRomIterType rmGDestRomIdx,
                                                                              PduLengthType pduLength,
                                                                              SduDataPtrType sduDataPtr,
                                                                              P2CONST(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA) retry, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) availableDataPtr)
{
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;     /* PRQA S 2981 */ /* MD_MSR_RetVal */
  PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfRmGDestRom(rmGDestRomIdx);
  PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx;

  if(PduR_Fm_GetCurrentlyUsedBmTxBufferInstanceIdxByRmGDestIdx(rmGDestRomIdx, &bmTxBufferInstanceRomIdx) == E_OK) /* SBSW_PDUR_STACK_VARIABLE */ /* COV_PDUR_ROBUSTNESS */
  {
    retVal = PduR_Bm_GetData(bmTxBufferInstanceRomIdx, pduLength, sduDataPtr, memIdx);  /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
    *availableDataPtr = (PduLengthType) PduR_Bm_GetTotalDataSizeInstance(bmTxBufferInstanceRomIdx, memIdx);       /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
  }

  PDUR_DUMMY_STATEMENT(retry);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  return retVal;
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
 /**********************************************************************************************************************
 * PduR_RmTp_TxInst_CopyTxData_RmTxInstAborted
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_TxInst_CopyTxData_RmTxInstAborted(PduR_RmGDestRomIterType rmGDestRomIdx, PduLengthType pduLength,
                                                                               SduDataPtrType sduDataPtr,
                                                                               P2CONST(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA) retry, P2VAR(PduLengthType, AUTOMATIC,
                                                                                                                                              PDUR_APPL_DATA) availableDataPtr)
{
  PDUR_DUMMY_STATEMENT(rmGDestRomIdx);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(pduLength);      /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(sduDataPtr);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(retry);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(availableDataPtr);       /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  return BUFREQ_E_NOT_OK;
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_TxInst_CopyTxData_UnexpectedCall
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_TxInst_CopyTxData_UnexpectedCall(PduR_RmGDestRomIterType rmGDestRomIdx, PduLengthType pduLength,
                                                                              SduDataPtrType sduDataPtr,
                                                                              P2CONST(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA) retry, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) availableDataPtr)
{
  PduR_Det_ReportError(PDUR_RMTP_TXINSTSM_COPYTXDATA_UNEXPECTEDCALL, PDUR_E_UNEXPECTED_CALL);
  PDUR_DUMMY_STATEMENT(rmGDestRomIdx);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(pduLength);      /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(sduDataPtr);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(retry);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(availableDataPtr);       /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  return BUFREQ_E_NOT_OK;
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_TxInst_TxConfirmation
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_RmTp_TxInst_TxConfirmation(PduR_RmGDestRomIterType rmGDestRomIdx, Std_ReturnType result)
{
  PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfRmGDestRom(rmGDestRomIdx);

  switch (PduR_GetTpTxInstSmStateOfRmGDestTpTxStateRam(PduR_GetRmGDestTpTxStateRamIdxOfRmGDestRom(rmGDestRomIdx), memIdx))
  {
    case PDUR_RM_TXINST_IDLE_TPTXINSTSMSTATEOFRMGDESTTPTXSTATERAM:
      PduR_RmTp_TxInst_TxConfirmation_UnexpectedCall(rmGDestRomIdx, result);
      break;

    case PDUR_RM_TXINST_ACTIVE_TPTXINSTSMSTATEOFRMGDESTTPTXSTATERAM:
      PduR_RmTp_TxInst_TxConfirmation_RmTxInstActiveOrRmTxInstAborted(rmGDestRomIdx, result);
      break;

# if (PDUR_EXISTS_DEFERRED_PDURDESTPDUPROCESSINGOFRMGDESTROM == STD_ON)
    case PDUR_RM_TXINST_WAITING_TPTXINSTSMSTATEOFRMGDESTTPTXSTATERAM:
      PduR_RmTp_TxInst_TxConfirmation_UnexpectedCall(rmGDestRomIdx, result);
      break;
# endif

    case PDUR_RM_TXINST_ABORTED_TPTXINSTSMSTATEOFRMGDESTTPTXSTATERAM:
      PduR_RmTp_TxInst_TxConfirmation_RmTxInstActiveOrRmTxInstAborted(rmGDestRomIdx, result);
      break;

    default: /* COV_PDUR_MISRA */
      /* If state is out-of-bounds: do nothing. */
      break;
  }
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_TxInst_TxConfirmation_RmTxInstActiveOrRmTxInstAborted
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmTp_TxInst_TxConfirmation_RmTxInstActiveOrRmTxInstAborted(PduR_RmGDestRomIterType rmGDestRomIdx, Std_ReturnType result)
{
  PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfRmGDestRom(rmGDestRomIdx);
  PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx;

  PduR_SetTpTxInstSmStateOfRmGDestTpTxStateRam(PduR_GetRmGDestTpTxStateRamIdxOfRmGDestRom(rmGDestRomIdx), PDUR_RM_TXINST_IDLE_TPTXINSTSMSTATEOFRMGDESTTPTXSTATERAM, memIdx);        /* SBSW_PDUR_CSL03 */

  if(PduR_Fm_GetCurrentlyUsedBmTxBufferInstanceIdxByRmGDestIdx(rmGDestRomIdx, &bmTxBufferInstanceRomIdx) == E_OK) /* SBSW_PDUR_STACK_VARIABLE */ /* COV_PDUR_ROBUSTNESS */
  {
    PduR_Bm_ResetTxBufferInstance(bmTxBufferInstanceRomIdx, memIdx);
  }
  PduR_RmTp_FinishTransmission_TpTxSmStateHandler(PduR_GetFmFifoRomIdxOfFmFifoInstanceRom(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx), memIdx), result, memIdx);
  PDUR_DUMMY_STATEMENT(result); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_TxInst_TxConfirmation_UnexpectedCall
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmTp_TxInst_TxConfirmation_UnexpectedCall(PduR_RmGDestRomIterType rmGDestRomIdx, Std_ReturnType result)
{
  PduR_Det_ReportError(PDUR_RMTP_TXINSTSM_TPTXCONFIRMATION_UNEXPECTEDCALL, PDUR_E_UNEXPECTED_CALL);
  PDUR_DUMMY_STATEMENT(rmGDestRomIdx);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(result); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_TxInst_CancelTransmit
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_RmTp_TxInst_CancelTransmit(PduR_RmDestRomIterType rmGDestRomIdx)
{
  PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfRmGDestRom(rmGDestRomIdx);
  PduR_RmGDestTpTxStateRamIdxOfRmGDestRomType rmGDestTpTxStateRamIdx = PduR_GetRmGDestTpTxStateRamIdxOfRmGDestRom(rmGDestRomIdx);

  switch (PduR_GetTpTxInstSmStateOfRmGDestTpTxStateRam(rmGDestTpTxStateRamIdx, memIdx))
  {
    case PDUR_RM_TXINST_IDLE_TPTXINSTSMSTATEOFRMGDESTTPTXSTATERAM:
      /* Nothing to abort. */
      break;

    case PDUR_RM_TXINST_ACTIVE_TPTXINSTSMSTATEOFRMGDESTTPTXSTATERAM:
      PduR_SetTpTxInstSmStateOfRmGDestTpTxStateRam(rmGDestTpTxStateRamIdx, PDUR_RM_TXINST_ABORTED_TPTXINSTSMSTATEOFRMGDESTTPTXSTATERAM, memIdx); /* SBSW_PDUR_CSL01 */
      break;

# if (PDUR_EXISTS_DEFERRED_PDURDESTPDUPROCESSINGOFRMGDESTROM == STD_ON)
    case PDUR_RM_TXINST_WAITING_TPTXINSTSMSTATEOFRMGDESTTPTXSTATERAM:
    {
      PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx;

      PduR_SetTpTxInstSmStateOfRmGDestTpTxStateRam(rmGDestTpTxStateRamIdx, PDUR_RM_TXINST_IDLE_TPTXINSTSMSTATEOFRMGDESTTPTXSTATERAM, memIdx);        /* SBSW_PDUR_CSL03 */

      if(PduR_Fm_GetCurrentlyUsedBmTxBufferInstanceIdxByRmGDestIdx(rmGDestRomIdx, &bmTxBufferInstanceRomIdx) == E_OK) /* SBSW_PDUR_STACK_VARIABLE */ /* COV_PDUR_ROBUSTNESS */
      {
        PduR_Bm_ResetTxBufferInstance(bmTxBufferInstanceRomIdx, memIdx);
      }
      PduR_RmTp_FinishTransmission_TpTxSmStateHandler(PduR_GetFmFifoRomIdxOfFmFifoInstanceRom(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx), memIdx), E_NOT_OK, memIdx);
    }
      break;
# endif

    case PDUR_RM_TXINST_ABORTED_TPTXINSTSMSTATEOFRMGDESTTPTXSTATERAM: /* COV_PDUR_CANCELTRANSMIT_WITHOUT_RPG */
      /* Already aborted. Nothing to do. */
      break;

    default: /* COV_PDUR_MISRA */
      /* If state is out-of-bounds: do nothing. */
      break;
  }
}
#endif

#if((PDUR_MAIN_FUNCTION == STD_ON) && (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON))
/**********************************************************************************************************************
 * PduR_RmTp_TxInst_MainFunction
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_RmTp_TxInst_MainFunction(PduR_RmGDestRomIterType rmGDestRomIdx, PduR_MemIdxType memIdx)
{
  PduR_Lock_LockRoutingPathByGDestPdu(rmGDestRomIdx);
  {
    if((PduR_GetPduRDestPduProcessingOfRmGDestRom(rmGDestRomIdx) == PDUR_DEFERRED_PDURDESTPDUPROCESSINGOFRMGDESTROM) && (PDUR_RM_TXINST_WAITING_TPTXINSTSMSTATEOFRMGDESTTPTXSTATERAM == PduR_GetTpTxInstSmStateOfRmGDestTpTxStateRam(PduR_GetRmGDestTpTxStateRamIdxOfRmGDestRom(rmGDestRomIdx), memIdx))) /* COV_PDUR_CROSSCORE_ROUTINGS_ONLY */
    {
      PduR_SetTpTxInstSmStateOfRmGDestTpTxStateRam(PduR_GetRmGDestTpTxStateRamIdxOfRmGDestRom(rmGDestRomIdx), PDUR_RM_TXINST_ACTIVE_TPTXINSTSMSTATEOFRMGDESTTPTXSTATERAM, memIdx);      /* SBSW_PDUR_CSL03 */
      (void) PduR_RmTp_TxInst_LoAndUpTransmit(rmGDestRomIdx);
    }
  }
  PduR_Lock_UnlockRoutingPathByGDestPdu(rmGDestRomIdx);
}       /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h" /* PRQA S 5087 */   /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  END OF FILE: PduR_RmTp_TxInst.c
 *********************************************************************************************************************/
