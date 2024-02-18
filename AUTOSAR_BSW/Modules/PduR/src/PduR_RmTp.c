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
 *         File:  PduR_RmTp.c
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
/* PRQA  S 0789 EOF */ /* MD_PduR_DistinctIdentifiers */

#define PDUR_RMTP_SOURCE
/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "PduR.h"
#include "PduR_Bm.h"
#include "PduR_Fm.h"
#include "PduR_Lock.h"
#include "PduR_RmTp.h"
#include "PduR_RmTp_TxInst.h"
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

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_GetFmFifoElementRamIdxOfRmBufferedTpPropertiesSafe
 *********************************************************************************************************************/
/*! \brief      Gets the current idx for the FIFO element.
 *  \details    -
 *  \param[in]  bufferedTpPropertiesRomIdx    id of the buffered TP property
 *  \param[in]  memIdx                        memory section index
 *  \return     the index
 *  \pre        -
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(PduR_FmFifoElementRamIdxOfRmBufferedTpPropertiesRamType, PDUR_CODE) PduR_RmTp_GetFmFifoElementRamIdxOfRmBufferedTpPropertiesSafe(PduR_RmBufferedTpPropertiesRomIdxOfRmSrcRomType bufferedTpPropertiesRomIdx, PduR_MemIdxType memIdx);
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_ThresholdReached
 *********************************************************************************************************************/
/*! \brief      This function calculates the fill level and returns true if the configured threshold is reached.
 *  \details    -
 *  \param[in]  rmSrcIdx   Routing Manager Src Index
 *  \return                E_OK:     If threshold is reached.
 *                         E_NOT_OK: If threshold is not reached.
 *  \pre        -
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_ThresholdReached(PduR_RmSrcRomIterType rmSrcIdx);
#endif

#if(PDUR_EXISTS_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
   PduR_RmTp_MultipleSourceHandler_Transmit
**********************************************************************************************************************/
/*! \brief       The function is called by the PduR to trigger the transmission on the destination buses in case of a
 *                FanIn Transport Protocol Routing.
 *   \details     The PDU Router evaluates the Gw I-PDU handle and performs appropriate handle and port conversion.
 *                The call is routed to multiple TP module using the appropriate I-PDU handle of the destination layer.
 *   \param[in]   rmDestRomIdx             ID of the transmitted GwTp I-PDU.
 *   \param[in]   info                     the pointer to the data
 *   \pre         -
 *   \context     TASK|ISR1|ISR2
 *   \reentrant   TRUE
 *   \synchronous TRUE
**********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_MultipleSourceHandler_Transmit(PduR_RmDestRomIterType rmDestRomIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
  PduR_RmTp_CopyTxData
**********************************************************************************************************************/
/*! \brief      This function is called by the PduR GwTp to query the transmit data of an I-PDU segment.
 *  \details    Each call to this function copies the next part of the transmit.
 *  \param[in]      rmGDestRomIdx       ID of the GwTp I-PDU that will be transmitted.
 *  \param[in]      info              Pointer to the destination buffer and the number of bytes to copy.
 *                                In case of gateway the PDU Router module will copy otherwise the source upper layer
 *                                module will copy the data. If not enough transmit data is available, no data is copied.
 *
 *                                A copy size of 0 can be used to indicate state changes in the retry parameter.
 *  \param[in]  retry             not supported
 *  \param[out] availableDataPtr  Indicates the remaining number of bytes that are available in the PduR Tx buffer.
 *                                AvailableTxDataCntPtr can be used by TP modules that support dynamic payload lengths
 *                                (e.g. Iso FrTp) to determine the size of the following CFs.
 *  \return     BufReq_ReturnType
 *              BUFREQ_OK         The data has been copied to the transmit buffer successful.
 *              BUFREQ_E_NOT_OK   PduR_Init() has not been called
 *                                or the GwTpTxPduId is not valid
 *                                or the GwTpTxPduId is not forwarded in this identity
 *                                or the info is not valid
 *                                or the request was not accepted by the upper layer and no data has been copied.
 *              BUFREQ_E_BUSY     The request cannot be processed because the TX data is not available
 *                                and no data has been copied. The TP layer might retry later the copy process.
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       SPEC-1096, SPEC-2020151
**********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_CopyTxData(PduR_RmGDestRomIdxOfTxTp2SrcType rmGDestRomIdx,
                                                                     P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info,
                                                                     P2VAR(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA) retry, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) availableDataPtr);
#endif

#if (PDUR_METADATA_SUPPORT == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_StartOfReceptionQueueMetaData
 *********************************************************************************************************************/
/*! \brief         This function writes meta data to the Tp buffer and adjusts the info->SduLength
 *                 if meta data is used.
 *  \details       -
 *  \param[in]     rmSrcIdx         Routing Manager Src Index
 *  \param[in]     pduLength        meta data length. (Meta data length are constant ROM)
 *  \param[in,out] sduDataPtr       Meta Data pointer .
 *  \param[out]    bufferSizePtr    pointer to data structure which will be used to return the size of the Pdu which
                                    can be copied to the buffer.
 *  \return        BUFREQ_OK        Buffer request was successful.
 *                 BUFREQ_E_NOT_OK  Currently no buffer available
 *  \pre           -
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_StartOfReceptionQueueMetaData(PduR_RmSrcRomIterType rmSrcIdx,
                                                                                        PduLengthType pduLength,
                                                                                        SduDataPtrType sduDataPtr, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr);
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_AssignAssociatedBuffer2Destination
 *********************************************************************************************************************/
/*! \brief       Assign the associated buffer to the destinations before the Transmit function is called.
 *  \details     -
 *  \param[in]   bmTxBufferRomIdx      Index of the Tx buffer
 *  \param[in]   rmSrcIdx              Routing Manager Src Index
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmTp_AssignAssociatedBuffer2Destination(PduR_BmTxBufferRomIterType bmTxBufferRomIdx, PduR_RmSrcRomIterType rmSrcIdx);
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_TriggerTransmissionOfDestinations
 *********************************************************************************************************************/
/*! \brief       Trigger the transmission on all destinations if they are enabled, except for those which are unbuffered
 *  \details     -
 *  \param[in]   rmSrcIdx       Routing Manager Src Index
 *  \return      E_OK           Transmission was successful on at least one destination
 *               E_NOT_OK       Transmission was not successful on any destination
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_TriggerTransmissionOfDestinations(PduR_RmSrcRomIterType rmSrcIdx);
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_GetCurrentlyWrittenFmFifoElementRamIdxByRmSrcIdx
 *********************************************************************************************************************/
/*! \brief       This function returns the currently written FmFifoElement index of this source Pdu.
 *  \details     -
 *  \param[in]   rmSrcIdx            Routing Manager Src Index
 *  \param[out]  fmFifoElementRamIdx fifo element index
 *  \return      E_OK                the read fmFifoElementRamIdx is valid and can be used
 *               E_NOT_OK            the read fmFifoElementRamIdx is invalid and can not be used
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_GetCurrentlyWrittenFmFifoElementRamIdxByRmSrcIdx(PduR_RmSrcRomIterType rmSrcIdx, P2VAR(PduR_FmFifoElementRamIterType, AUTOMATIC, PDUR_APPL_DATA) fmFifoElementRamIdx);
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_GetCurrentlyUsedBmTxBufferRamIdxByRmSrcIdx
 *********************************************************************************************************************/
/*! \brief       This function returns the currently written bmTxBuffer index of this source Pdu.
 *  \details     -
 *  \param[in]   rmSrcIdx            Routing Manager Src Index
 *  \param[out]  bmTxBufferRomIdx    tx buffer index
 *  \return      E_OK                the read bmTxBufferRomIdx is valid and can be used
 *               E_NOT_OK            the read bmTxBufferRomIdx is invalid and can not be used
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_GetCurrentlyUsedBmTxBufferRamIdxByRmSrcIdx(PduR_RmSrcRomIterType rmSrcIdx, P2VAR(PduR_BmTxBufferRomIterType, AUTOMATIC, PDUR_APPL_DATA) bmTxBufferRomIdx);
#endif

# if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_FinishTransmission_TpTxSmStateHandler_RM_TX_RECEPTION_FINISHED_TRANSMISSION_ACTIVE
 *********************************************************************************************************************/
/*! \brief This function is called if the transmission is finished o set the suitable state a and
 *         trigger the next pending routing
 *  \details -
 *  \param[in]   fmFifoRomIdx fifo id
 *  \param[out]  result   result of the transmission.
 *               E_OK     successful
 *               E_NO_OK not successful.
 *  \param[in]   memIdx  memory section index
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmTp_FinishTransmission_TpTxSmStateHandler_RM_TX_RECEPTION_FINISHED_TRANSMISSION_ACTIVE(PduR_FmFifoRomIterType fmFifoRomIdx, Std_ReturnType result, PduR_MemIdxType memIdx);
# endif

# if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_FinishTransmission_TpTxSmStateHandler_RM_TX_RECEPTION_TRANSMISSION_ACTIVE
 *********************************************************************************************************************/
/*! \brief This function is called if the transmission is finished o set the suitable state a and
 *         trigger the next pending routing
 *  \details -
 *  \param[in]   fmFifoRomIdx fifo id
 *  \param[out]  result   result of the transmission.
 *               E_OK     successful
 *               E_NO_OK not successful.
 *  \param[in]   memIdx  memory section index
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmTp_FinishTransmission_TpTxSmStateHandler_RM_TX_RECEPTION_TRANSMISSION_ACTIVE(PduR_FmFifoRomIterType fmFifoRomIdx, Std_ReturnType result, PduR_MemIdxType memIdx);
# endif

# if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_FinishTransmission_TpTxSmStateHandler_FatalError
 *********************************************************************************************************************/
/*! \brief This function is called if the transmission is finished o set the suitable state a and
 *         trigger the next pending routing
 *  \details -
 *  \param[in]   fmFifoRomIdx fifo id
 *  \param[out]  result   result of the transmission.
 *               E_OK     successful
 *               E_NO_OK not successful.
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmTp_FinishTransmission_TpTxSmStateHandler_FatalError(PduR_FmFifoRomIterType fmFifoRomIdx, Std_ReturnType result);
# endif

# if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_CheckReady2Transmit_TpTxSmStateHandler
 *********************************************************************************************************************/
/*! \brief       Helper function which checks if the Pdu from this rmSrc is ready to transmit depending on the TpTxSm state.
 *  \details     -
 *  \param[in]   memIdx memory section index
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE)PduR_RmTp_CheckReady2Transmit_TpTxSmStateHandler(PduR_FmFifoRamIterType fmFifoRomIdx, PduR_RmSrcRomIterType rmSrcIdx, PduR_MemIdxType memIdx);
# endif

# if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_CheckReady2Transmit_TpTxSmStateHandler_RM_TX_IDLE_OR_RM_TX_RECEPTION_ACTIVE
 *********************************************************************************************************************/
/*! \brief This function is called to check if the threshold is reached and the transmission could be triggered
 *  \details -
 *  \param[in]     rmSrcIdx Routing Manager source Id
 *  \pre           -
 *  \context       TASK|ISR1|ISR2
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_CheckReady2Transmit_TpTxSmStateHandler_RM_TX_IDLE_OR_RM_TX_RECEPTION_ACTIVE(PduR_RmSrcRomIterType rmSrcIdx);
# endif

# if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_CheckReady2Transmit_TpTxSmStateHandler_NoAction
 *********************************************************************************************************************/
/*! \brief        This function is called if nothing shall be done.
 *  \details      -
 *  \param[in]    rmSrcIdx Routing Manager source Id
 *  \pre          -
 *  \context      TASK|ISR1|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_CheckReady2Transmit_TpTxSmStateHandler_NoAction(PduR_RmSrcRomIterType rmSrcIdx);
# endif

# if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_CheckReady2Transmit_TpTxSmStateHandler_FatalError
 *********************************************************************************************************************/
/*! \brief        This function is called if the TpTx state is in an invalid state. This shall not happen during normal operation
 *  \details      -
 *  \param[in]    rmSrcIdx Routing Manager source Id
 *  \pre          -
 *  \context      TASK|ISR1|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_CheckReady2Transmit_TpTxSmStateHandler_FatalError(PduR_RmSrcRomIterType rmSrcIdx);
# endif

# if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_CopyRxData_TpRxSmStateHandler
 *********************************************************************************************************************/
/*! \brief       Helper function which copies the rx data from this rmSrc depending on the TpRxSm state.
 *  \details     -
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CONST) PduR_RmTp_CopyRxData_TpRxSmStateHandler(PduR_RmSrcRomIdxOfRxTp2DestType rmSrcIdx, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr);
# endif

# if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
  PduR_RmTp_CopyRxData_TpRxSmStateHandler_RM_RX_ACTIVE
**********************************************************************************************************************/
/*! \brief     This function is called by the PduR if data has to be copied to the tx buffer
 *  \details   Several calls may be made during one transportation of an I-PDU.
 *             Rx State machine in state "Active"
 *  \param[in]  rmSrcIdx          Routing Manager source Id
  * \param[in] pduLength         length to copy.
 *  \param[in] sduDataPtr        data pointer (containing the data to be copied by PDU Router module in case of gateway
 *                               or upper layer module in case of reception).
 *  \param[out] bufferSizePtr     Available receive buffer after data has been copied.
 *  \return    BufReq_ReturnType
 *             BUFREQ_OK         Copy data were successful.
 *             BUFREQ_E_NOT_OK   Copy data fails.
 *             BUFREQ_E_BUSY     Currently no buffer of the requested size is available.
 *                               It's up the requester to retry request for a certain time.
 *                               The request was not accepted by the upper layer.
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       SPEC-1096, SPEC-2020151
**********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_CopyRxData_TpRxSmStateHandler_RM_RX_ACTIVE(PduR_RmSrcRomIterType rmSrcIdx, PduLengthType pduLength,
                                                                                        SduDataPtrType sduDataPtr, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr);
# endif

# if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
  PduR_RmTp_CopyRxData_TpRxSmStateHandler_RM_RX_ABORTED
**********************************************************************************************************************/
/*! \brief     This function is called if data has to be copied to the tx buffer but the routing is
 *             already aborted.
 *  \details   Rx State machine in state "Aborted"
 *  \param[in]  rmSrcIdx           Routing Manager source Id
 *  \param[in] pduLength         length to copy.
 *  \param[in] sduDataPtr        data pointer (containing the data to be copied by PDU Router module in case of gateway
 *                               or upper layer module in case of reception).
 *  \param[out] bufferSizePtr     Available receive buffer after data has been copied.
 *  \return    BufReq_ReturnType
 *             BUFREQ_E_NOT_OK   Copy data fails because routing is already aborted.
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       SPEC-1096, SPEC-2020151
**********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_CopyRxData_TpRxSmStateHandler_RM_RX_ABORTED(PduR_RmSrcRomIterType rmSrcIdx, PduLengthType pduLength,
                                                                                         SduDataPtrType sduDataPtr, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr);
# endif

# if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
  PduR_RmTp_CopyRxData_TpRxSmStateHandler_UnexpectedCall
**********************************************************************************************************************/
/*! \brief       This function is called by the PduR if data has to be to copied to the tx buffer unexpectedly.
 *  \details     Rx State machine in state "Idle"
 *  \param[in]   rmSrcIdx          Routing Manager source Id
  * \param[in]   pduLength         length to copy.
 *  \param[in]   sduDataPtr        data pointer (containing the data to be copied by PDU Router module in case of gateway
 *                                 or upper layer module in case of reception).
 *  \param[out]  bufferSizePtr     Available receive buffer after data has been copied.
 *  \return      BufReq_ReturnType
 *               BUFREQ_E_NOT_OK   Copy data fails because the RxSM is still idle. A StartOfReception is expected.
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       SPEC-1096, SPEC-2020151
**********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_CopyRxData_TpRxSmStateHandler_UnexpectedCall(PduR_RmSrcRomIterType rmSrcIdx, PduLengthType pduLength,
                                                                                          SduDataPtrType sduDataPtr, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr);
# endif

# if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_FinishReception_TpTxSmStateHandler
 *********************************************************************************************************************/
/*! \brief       Helper function which finishes the reception in the corresponding queue depending on the TpTxSm state.
 *  \details     -
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmTp_FinishReception_TpTxSmStateHandler(PduR_RmSrcRomIterType rmSrcIdx, Std_ReturnType result);
# endif

# if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_FinishReception_TpTxSmStateHandler_FatalError
 *********************************************************************************************************************/
/*! \brief This function is called if the reception is finished to set the suitable state a and
 *         to trigger the transmission
 *  \details -
 *  \param[in]   rmSrcIdx Routing Manager source Id.
 *  \param[out]  result  result of the reception.
 *               E_OK    successful.
 *               E_NO_OK not successful.
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmTp_FinishReception_TpTxSmStateHandler_FatalError(PduR_RmSrcRomIterType rmSrcIdx, Std_ReturnType result);
# endif

# if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_FinishReception_TpTxSmStateHandler_RM_TX_TRANSMISSION_FINISHED
 *********************************************************************************************************************/
/*! \brief This function is called if the reception is finished to set the suitable state a and
 *         to trigger the transmission
 *  \details -
 *  \param[in]   rmSrcIdx Routing Manager source Id.
 *  \param[out]  result   result of the reception.
 *               E_OK     successful
 *               E_NO_OK not successful.
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmTp_FinishReception_TpTxSmStateHandler_RM_TX_TRANSMISSION_FINISHED(PduR_RmSrcRomIterType rmSrcIdx, Std_ReturnType result);
# endif

# if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_FinishReception_TpTxSmStateHandler_RM_TX_RECEPTION_ACTIVE
 *********************************************************************************************************************/
/*! \brief This function is called if the reception is finished to set the suitable state a and
 *         to trigger the transmissiong
 *  \details -
 *  \param[in]   rmSrcIdx Routing Manager source Id.
 *  \param[out]  result   result of the reception.
 *               E_OK     successful.
 *               E_NO_OK  not successful.
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmTp_FinishReception_TpTxSmStateHandler_RM_TX_RECEPTION_ACTIVE(PduR_RmSrcRomIterType rmSrcIdx, Std_ReturnType result);
# endif

# if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_FinishReception_TpTxSmStateHandler_RM_TX_RECEPTION_TRANSMISSION_ACTIVE
 *********************************************************************************************************************/
/*! \brief This function is called if the reception is finished to set the suitable state a and
 *         to trigger the transmission
 *  \details -
 *  \param[in]   rmSrcIdx Routing Manager source Id.
 *  \param[out]  result  result of the reception.
 *               E_OK    successful
 *               E_NO_OK not successful.
 *  \pre         -
 *  \context     TASK|ISR1|ISR2.
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmTp_FinishReception_TpTxSmStateHandler_RM_TX_RECEPTION_TRANSMISSION_ACTIVE(PduR_RmSrcRomIterType rmSrcIdx, Std_ReturnType result);
# endif

# if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_CancelReceive_TpRxSmStateHandler
 *********************************************************************************************************************/
/*! \brief       Helper function which cancels the reception in the corresponding queue depending on the TpRxSm state.
 *  \details     -
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmTp_CancelReceive_TpRxSmStateHandler(PduR_RmSrcRomIterType rmSrcIdx);
# endif

# if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_CancelReceive_TpRxSmStateHandler_RM_RX_ACTIVE
 *********************************************************************************************************************/
/*! \brief      The function is called to cancel a reception if a routing is disabled.
 *  \details    -
 *  \param[in]   rmSrcIdx    Routing Manager source Id
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
***********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmTp_CancelReceive_TpRxSmStateHandler_RM_RX_ACTIVE(PduR_RmSrcRomIterType rmSrcIdx);
# endif

# if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_CancelReceive_TpRxSmStateHandler_FatalError
 *********************************************************************************************************************/
/*! \brief       If this function is called something went totally wrong.
 *  \details     -
 *  \param[in]   rmSrcIdx   Routing Manager source Id
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
***********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmTp_CancelReceive_TpRxSmStateHandler_FatalError(PduR_RmSrcRomIterType rmSrcIdx);
# endif

# if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_TpRxIndication_TpRxSmStateHandler
 *********************************************************************************************************************/
/*! \brief       Helper function which handels the TpRxIndication for the corresponding queue depending on the TpRxSm state.
 *  \details     -
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmTp_TpRxIndication_TpRxSmStateHandler(PduR_RmSrcRomIterType rmSrcIdx, Std_ReturnType result);
# endif

# if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_TpRxIndication_TpRxSmStateHandler_UnexpectedCall
 *********************************************************************************************************************/
/*! \brief       The function is called by the PduR GwTp to indicate the complete reception of a GwTp SDU
 *               or to finish the reception if an error occurs.
 *  \details     Rx State machine in state "Active or Aborted"
 *  \param[in]   rmSrcIdx             Routing Manager source Id
 *  \param[out]  result                          Result of the TP reception.\n
 *               E_OK                            The TP reception has been completed successfully.\n
 *               E_NOT_OK                        The TP reception was failing.
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       SPEC-1096, SPEC-2020151
***********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmTp_TpRxIndication_TpRxSmStateHandler_UnexpectedCall(PduR_RmSrcRomIterType rmSrcIdx, Std_ReturnType result);
# endif

# if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_TpRxIndication_TpRxSmStateHandler_RM_RX_ACTIVE_OR_RM_RX_ABORTED
 *********************************************************************************************************************/
/*! \brief       The function is called by the PduR GwTp if an indication is called unexpectedly
 *  \details     Rx State machine in state "Idle"
 *  \param[in]   rmSrcIdx              Routing Manager source Id
 *  \param[out]  result                Result of the TP reception.\n
 *               E_OK    successful
 *               E_NO_OK not successful.
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       SPEC-1096, SPEC-2020151
***********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmTp_TpRxIndication_TpRxSmStateHandler_RM_RX_ACTIVE_OR_RM_RX_ABORTED(PduR_RmSrcRomIterType rmSrcIdx, Std_ReturnType result);
# endif

# if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_StartOfReception_TpRxSmStateHandler
 *********************************************************************************************************************/
/*! \brief       Helper function which handels the StartOfReception for the corresponding queue depending on the TpRxSm state.
 *  \details     -
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_StartOfReception_TpRxSmStateHandler(PduR_RmSrcRomIterType rmSrcIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, PduLengthType TpSduLength, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr);
# endif

# if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM  == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_StartOfReception_TpRxSmStateHandler_RM_RX_IDLE
 *********************************************************************************************************************/
/*! \brief      The function is called by the PduR GwTp to start a reception of a GwTp SDU
 *  \details    Rx State machine in state "IDLE" The call is routed to RxSm
 *  \param[in]     rmSrcIdx                      Routing Manager source Id
 *  \param[in]     info                            Pointer to the buffer (SduDataPtr) and its length (SduLength)
 *  \param[in]     TpSduLength       Length of the entire GwTp TP SDU which will be received
 *  \param[out]    bufferSizePtr                   Pointer to the receive buffer in the receiving module.
 *  \return      BufReq_ReturnType
 *               BUFREQ_OK         routing accepted and buffer allocated.
 *               BUFREQ_E_NOT_OK   routing not accepted (FIFO full) no Tp buffer available.
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       SPEC-1096, SPEC-2020151
***********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_StartOfReception_TpRxSmStateHandler_RM_RX_IDLE(PduR_RmSrcRomIterType rmSrcIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info,
                                                                                            PduLengthType TpSduLength, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr);
# endif

# if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM  == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_StartOfReception_TpRxSmStateHandler_UnexpectedCall
 *********************************************************************************************************************/
/*! \brief      The function is called if the start of reception is called unexpectedly.
 *  \details    Rx State machine in state "Active or Aborted"
 *  \param[in]  rmSrcIdx            Routing Manager source Id
 *  \param[in]  info                Pointer to the buffer (SduDataPtr) and its length (SduLength)
 *  \param[in]  TpSduLength         Length of the entire GwTp TP SDU which will be received
 *  \param[out] bufferSizePtr       Pointer to the receive buffer in the receiving module.
 *  \return      BufReq_ReturnType
 *               BUFREQ_E_NOT_OK   unexpected call
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       SPEC-1096, SPEC-2020151
***********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_StartOfReception_TpRxSmStateHandler_UnexpectedCall(PduR_RmSrcRomIterType rmSrcIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info,
                                                                                                PduLengthType TpSduLength, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr);
# endif

# if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_ActivateNext
 *********************************************************************************************************************/
/*! \brief       This function is called to activated the next pending element in the FiFo.
 *  \details     -
 *  \param[in]   fmFifoRamIdx        Index of the destination FIFO.
 *  \param[in]   memIdx              memory section index
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmTp_ActivateNext(PduR_FmFifoRamIterType fmFifoRamIdx, PduR_MemIdxType memIdx);
# endif

# if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
 /**********************************************************************************************************************
 * PduR_RmTp_CancelTransmitOnDestinations
 *********************************************************************************************************************/
/*! \brief       This function is called to cancel all destination transmit calls of a source.
 *  \details     -
 *  \param[in]   rmSrcIdx     rmSrc index
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmTp_CancelTransmitOnDestinations(PduR_RmSrcRomIterType rmSrcIdx);
# endif

# if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
 /**********************************************************************************************************************
 * PduR_RmTp_GetRmSrcRomIdxOfOldestFmFifoElementSafe
 *********************************************************************************************************************/
/*! \brief       Gets the rmSrc index of the oldest fifo element with optional error detection.
 *  \details     -
 *  \param[in]   fmFifoRomIdx fmFifo index
 *  \param[out]  rmSrcIdx     rmSrc index
 *  \param[in]   memIdx       memory section index
 *  \return      E_OK         The read was successful.
 *               E_NOT_OK     The read was not successful.
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_GetRmSrcRomIdxOfOldestFmFifoElementSafe(PduR_FmFifoRomIterType fmFifoRomIdx, P2VAR(PduR_RmSrcRomIterType, AUTOMATIC, PDUR_APPL_DATA) rmSrcRomIdx, PduR_MemIdxType memIdx);
# endif

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_Init
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_RmTp_Init(PduR_MemIdxType memIdx)
{
  {
    PduR_RmGDestTpTxStateRamIterType rmGDestTpTxStateRamTpIdx;
    for(rmGDestTpTxStateRamTpIdx = 0u; rmGDestTpTxStateRamTpIdx < PduR_GetSizeOfRmGDestTpTxStateRam(memIdx); rmGDestTpTxStateRamTpIdx++)
    {
      PduR_SetTpTxInstSmStateOfRmGDestTpTxStateRam(rmGDestTpTxStateRamTpIdx, PDUR_RM_TXINST_IDLE_TPTXINSTSMSTATEOFRMGDESTTPTXSTATERAM, memIdx); /* SBSW_PDUR_CSL01 */
    }
  }
  {
    PduR_RmBufferedTpPropertiesRomIterType rmBufferedTpPropertiesRamIdx;
    for(rmBufferedTpPropertiesRamIdx = 0u; rmBufferedTpPropertiesRamIdx < PduR_GetSizeOfRmBufferedTpPropertiesRam(memIdx); rmBufferedTpPropertiesRamIdx++)
    {
      PduR_SetTpRxSmStateOfRmBufferedTpPropertiesRam(rmBufferedTpPropertiesRamIdx, PDUR_RM_RX_IDLE_TPRXSMSTATEOFRMBUFFEREDTPPROPERTIESRAM, memIdx);     /* SBSW_PDUR_CSL01 */
      PduR_SetFmFifoElementRamIdxOfRmBufferedTpPropertiesRam(rmBufferedTpPropertiesRamIdx, PDUR_NO_FMFIFOELEMENTRAMIDXOFRMBUFFEREDTPPROPERTIESRAM, memIdx);     /* SBSW_PDUR_CSL01 */
    }
  }
}
#endif

#if(PDUR_EXISTS_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_MultipleSourceHandler_Transmit
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
PDUR_LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_MultipleSourceHandler_Transmit(PduR_RmDestRomIterType rmDestRomIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info)        /* COV_PDUR_CROSSCORE_ROUTINGS_ONLY */
{
  Std_ReturnType retVal = E_NOT_OK;     /* PRQA S 2981 */ /* MD_MSR_RetVal */
  PduR_Lock_LockRoutingPathByDestPdu(rmDestRomIdx);
  {
    PduR_RmGDestRomIdxOfRmDestRomType rmGDestRomIdx = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestRomIdx);

# if(PDUR_RMGDESTNTO1INFORAMIDXOFRMGDESTROM == STD_ON)
    if(PduR_IsRmGDestNto1InfoRamUsedOfRmGDestRom(rmGDestRomIdx))
    {
      PduR_RmGDestNto1InfoRamIdxOfRmGDestRomType rmGDestNto1InfoIdx = PduR_GetRmGDestNto1InfoRamIdxOfRmGDestRom(rmGDestRomIdx);
      PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfRmGDestRom(rmGDestRomIdx);

      if(!PduR_IsTransmissionActiveOfRmGDestNto1InfoRam(rmGDestNto1InfoIdx, memIdx))
      {
        PduR_SetRmDestRomIdxOfRmGDestNto1InfoRam(rmGDestNto1InfoIdx, (PduR_RmDestRomIdxOfRmGDestNto1InfoRamType) rmDestRomIdx, memIdx); /* SBSW_PDUR_CSL03 */
        PduR_SetTransmissionActiveOfRmGDestNto1InfoRam(rmGDestNto1InfoIdx, TRUE, memIdx);       /* SBSW_PDUR_CSL03 */

        retVal = PduR_GetLoTpTransmitFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx), info);     /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
        if(retVal != E_OK)
        {
          PduR_Rm_MultipleSourceHandler_Reset(rmGDestRomIdx);
        }
      }
    }
    else
# endif
    {
      retVal = PduR_GetLoTpTransmitFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx), info);       /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
    }
  }
  PduR_Lock_UnlockRoutingPathByDestPdu(rmDestRomIdx);

  return retVal;
}
#endif

#if((PDUR_EXISTS_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON))
/**********************************************************************************************************************
 * PduR_RmTp_MultipleSourceHandler_TpTxConfirmation
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_RmTp_MultipleSourceHandler_TpTxConfirmation(PduR_RmGDestRomIdxOfTxTp2SrcType rmGDestRomIdx, Std_ReturnType result)
{
  PduR_Lock_LockRoutingPathByGDestPdu(rmGDestRomIdx);
  {
    PduR_RmDestRomIterType rmDestRomIdx;

    if(PduR_Rm_GetSrcDestPdu(rmGDestRomIdx, &rmDestRomIdx) == E_OK)     /* SBSW_PDUR_STACK_VARIABLE */ /* COV_PDUR_NO_NTO1_ROUTINGPATHS */
    {
# if(PDUR_RMGDESTNTO1INFORAMIDXOFRMGDESTROM == STD_ON)
      PduR_Rm_MultipleSourceHandler_Reset(rmGDestRomIdx);
# endif

      switch (PduR_GetRoutingTypeOfRmDestRom(rmDestRomIdx))
      {
# if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
        case PDUR_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM:
          PduR_RmTp_TxInst_TxConfirmation(rmGDestRomIdx, result);
          break;
# endif
# if (PDUR_EXISTS_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON)
        case PDUR_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM:     /* COV_PDUR_CROSSCORE_ROUTINGS_ONLY */
        {
          PduR_RmSrcRomIdxOfRmDestRomType rmSrcRomIdx = PduR_GetRmSrcRomIdxOfRmDestRom(rmDestRomIdx);
          PduR_GetUpTpTpTxConfirmationFctPtrOfMmRom(PduR_GetMmRomIdxOfRmSrcRom(rmSrcRomIdx)) (PduR_GetSrcHndOfRmSrcRom(rmSrcRomIdx), result);   /* SBSW_PDUR_API_CALL_FORWARDING_ID_ONLY */
        }
          break;
# endif
        default:       /* COV_PDUR_MISRA */
          break;
      }
    }
    else
    {
      PduR_Det_ReportError(PDUR_RMTP_MULTIPLESOURCEHANDLER_TPTXCONFIRMATION, PDUR_E_UNEXPECTED_CALL);
    }
  }
  PduR_Lock_UnlockRoutingPathByGDestPdu(rmGDestRomIdx);
}
#endif

#if((PDUR_EXISTS_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON))
/**********************************************************************************************************************
 * PduR_RmTp_MultipleSourceHandler_CopyTxData
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_MultipleSourceHandler_CopyTxData(PduR_RmGDestRomIdxOfTxTp2SrcType rmGDestRomIdx, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info,
                                                                              P2VAR(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA) retry, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) availableDataPtr)
{
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;   /* PRQA S 2981 */ /* MD_MSR_RetVal */
  PduR_Lock_LockRoutingPathByGDestPdu(rmGDestRomIdx);
  {
    PduR_RmDestRomIterType rmDestRomIdx;

    if(PduR_Rm_GetSrcDestPdu(rmGDestRomIdx, &rmDestRomIdx) == E_OK)     /* SBSW_PDUR_STACK_VARIABLE */ /* COV_PDUR_NO_NTO1_ROUTINGPATHS */
    {
# if (PDUR_RPGROM == STD_ON)
      if(PduR_IsDestPduEnabled(rmDestRomIdx) == TRUE)
# endif
      {
        switch (PduR_GetRoutingTypeOfRmDestRom(rmDestRomIdx))
        {
# if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
          case PDUR_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM:
            if((retry == NULL_PTR) || (retry->TpDataState != TP_DATARETRY))
            {
              retVal = PduR_RmTp_CopyTxData(rmGDestRomIdx, info, retry, availableDataPtr);        /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
            }
            break;
# endif
# if (PDUR_EXISTS_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON)
          case PDUR_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM:   /* COV_PDUR_CROSSCORE_ROUTINGS_ONLY */
          {
            PduR_RmSrcRomIdxOfRmDestRomType rmSrcRomIdx = PduR_GetRmSrcRomIdxOfRmDestRom(rmDestRomIdx);
            retVal = PduR_GetUpTpCopyTxDataFctPtrOfMmRom(PduR_GetMmRomIdxOfRmSrcRom(rmSrcRomIdx)) (PduR_GetSrcHndOfRmSrcRom(rmSrcRomIdx), info, retry, availableDataPtr);       /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
          }
            break;
# endif
          default:     /* COV_PDUR_MISRA */
            break;
        }
      }
    }
    else
    {
      PduR_Det_ReportError(PDUR_RMTP_MULTIPLESOURCEHANDLER_COPYTXDATA, PDUR_E_UNEXPECTED_CALL);
    }
  }
  PduR_Lock_UnlockRoutingPathByGDestPdu(rmGDestRomIdx);
  return retVal;
}
#endif

#if((PDUR_TPCANCELTRANSMITSUPPORTEDOFMMROM == STD_ON) && (PDUR_EXISTS_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON))
/**********************************************************************************************************************
 * PduR_RmTp_MultipleSourceHandler_CancelTransmit
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
FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_MultipleSourceHandler_CancelTransmit(PduR_RmDestRomIterType rmDestRomIdx)
{
  Std_ReturnType retVal = E_NOT_OK;     /* PRQA S 2981 */ /* MD_MSR_RetVal */
  PduR_Lock_LockRoutingPathByDestPdu(rmDestRomIdx);
  {
    PduR_RmGDestRomIdxOfRmDestRomType rmGDestRomIdx = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestRomIdx);

# if(PDUR_RMGDESTNTO1INFORAMIDXOFRMGDESTROM == STD_ON)
    if(PduR_IsRmGDestNto1InfoRamUsedOfRmGDestRom(rmGDestRomIdx))
    {
      PduR_RmGDestNto1InfoRamIdxOfRmGDestRomType rmGDestNto1InfoIdx = PduR_GetRmGDestNto1InfoRamIdxOfRmGDestRom(rmGDestRomIdx);
      PduR_RmDestRomIterType lastTxdRmDestRomIdx;
      Std_ReturnType foundSrcPdu = PduR_Rm_GetSrcDestPdu(rmGDestRomIdx, &lastTxdRmDestRomIdx);  /* SBSW_PDUR_STACK_VARIABLE */
      PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfRmGDestRom(rmGDestRomIdx);

      if(PduR_IsTransmissionActiveOfRmGDestNto1InfoRam(rmGDestNto1InfoIdx, memIdx) && (foundSrcPdu == E_OK) && (rmDestRomIdx == lastTxdRmDestRomIdx))   /* COV_PDUR_ROBUSTNESS */
      {
        retVal = PduR_GetLoTpCancelTransmitFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx));     /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
      }
      else
      {
        PduR_Det_ReportError(PDUR_RMTP_MULTIPLESOURCEHANDLER_CANCELTRANSMIT, PDUR_E_UNEXPECTED_CALL);
      }
    }
    else
# endif
    {
      retVal = PduR_GetLoTpCancelTransmitFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx));       /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
    }
  }
  PduR_Lock_UnlockRoutingPathByDestPdu(rmDestRomIdx);
  return retVal;
}
#endif

#if(PDUR_EXISTS_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_Transmit_MultiDest
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_Transmit_MultiDest(PduR_RmSrcRomIterType rmSrcIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info)      /* COV_PDUR_CROSSCORE_ROUTINGS_ONLY */
{
  Std_ReturnType retVal = E_NOT_OK;     /* PRQA S 2981 */ /* MD_MSR_RetVal */
  PduR_RmDestRomIterType rmDestIdx;

  for(rmDestIdx = PduR_GetRmDestRomStartIdxOfRmSrcRom(rmSrcIdx); rmDestIdx < PduR_GetRmDestRomEndIdxOfRmSrcRom(rmSrcIdx); rmDestIdx++)
  {
    PduR_RmGDestRomIterType rmGDestRomIdx = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestIdx);
    if(PduR_GetDirectionOfRmGDestRom(rmGDestRomIdx) == PDUR_TX_DIRECTIONOFRMGDESTROM)   /* COV_PDUR_FEATURE_ALWAYS_TRUE */
    {
# if (PDUR_RPGROM == STD_ON)
      if(PduR_IsDestPduEnabled(rmDestIdx) == TRUE)
# endif
      {
        retVal &= PduR_RmTp_MultipleSourceHandler_Transmit(rmDestIdx, info);    /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
      }
    }
  }

  PDUR_DUMMY_STATEMENT(rmSrcIdx);       /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(info);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  return retVal;
}
#endif

#if (PDUR_HASTPBUFFERULSOURCEOFGENERALPROPERTIESROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_UpStartOfReception
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_UpStartOfReception(PduR_RmSrcRomIterType rmSrcIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info)
{
  Std_ReturnType retval = E_NOT_OK;     /* PRQA S 2981 */ /* MD_MSR_RetVal */
  PduLengthType bufferSizePtr = 0u;
  PduLengthType availableDataPtr = 0u;
  PduR_Lock_LockRoutingPathBySrcPdu(rmSrcIdx);
  {
    PduInfoType tempInfo;
    tempInfo.SduLength = info->SduLength;
    tempInfo.SduDataPtr = info->SduDataPtr;
    /* Handle src instance routing state */
    if(BUFREQ_OK == PduR_RmTp_StartOfReception(rmSrcIdx, &tempInfo, tempInfo.SduLength, &bufferSizePtr))        /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ID_AND_PTR */
    {
      if(tempInfo.SduLength <= bufferSizePtr)
      {
        PduInfoType copyInfo;
        PduR_BmTxBufferRomIterType bmTxBufferRomIdx;
        if(PduR_RmTp_GetCurrentlyUsedBmTxBufferRamIdxByRmSrcIdx(rmSrcIdx, &bmTxBufferRomIdx) == E_OK) /* SBSW_PDUR_STACK_VARIABLE */ /* COV_PDUR_ROBUSTNESS */
        {
          PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfRmSrcRom(rmSrcIdx);
          if(BUFREQ_OK == PduR_Bm_PutDataAsPtr(bmTxBufferRomIdx, &copyInfo, memIdx))    /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */ /* COV_PDUR_FATAL_ERROR */
          {
            copyInfo.SduLength = info->SduLength; /* pointer shall request the transmitted length, not the available length in the buffer */
            if(BUFREQ_OK == PduR_GetUpTpCopyTxDataFctPtrOfMmRom(PduR_GetMmRomIdxOfRmSrcRom(rmSrcIdx)) (PduR_GetSrcHndOfRmSrcRom(rmSrcIdx), &copyInfo, (P2VAR(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA)) NULL_PTR, &availableDataPtr))     /* SBSW_PDUR_API_CALL_FORWARDING_ID_ONLY */
            {
              if(availableDataPtr == 0u)
              {
                PduR_RmTp_TpRxIndication((PduR_RmSrcRomIdxOfRxTp2DestType) rmSrcIdx, E_OK);
                PduR_GetUpTpTpTxConfirmationFctPtrOfMmRom(PduR_GetMmRomIdxOfRmSrcRom(rmSrcIdx)) (PduR_GetSrcHndOfRmSrcRom(rmSrcIdx), E_OK);       /* SBSW_PDUR_API_CALL_FORWARDING_ID_ONLY */
                retval = E_OK;
              }
              else
              {
                PduR_RmTp_TpRxIndication((PduR_RmSrcRomIdxOfRxTp2DestType) rmSrcIdx, E_NOT_OK);
                PduR_GetUpTpTpTxConfirmationFctPtrOfMmRom(PduR_GetMmRomIdxOfRmSrcRom(rmSrcIdx)) (PduR_GetSrcHndOfRmSrcRom(rmSrcIdx), E_NOT_OK);   /* SBSW_PDUR_API_CALL_FORWARDING_ID_ONLY */
              }
            }
            else
            {
              PduR_RmTp_TpRxIndication((PduR_RmSrcRomIdxOfRxTp2DestType) rmSrcIdx, E_NOT_OK);
              PduR_GetUpTpTpTxConfirmationFctPtrOfMmRom(PduR_GetMmRomIdxOfRmSrcRom(rmSrcIdx)) (PduR_GetSrcHndOfRmSrcRom(rmSrcIdx), E_NOT_OK);     /* SBSW_PDUR_API_CALL_FORWARDING_ID_ONLY */
            }
          }
          else
          {
            PduR_RmTp_TpRxIndication((PduR_RmSrcRomIdxOfRxTp2DestType) rmSrcIdx, E_NOT_OK);
            PduR_GetUpTpTpTxConfirmationFctPtrOfMmRom(PduR_GetMmRomIdxOfRmSrcRom(rmSrcIdx)) (PduR_GetSrcHndOfRmSrcRom(rmSrcIdx), E_NOT_OK);       /* SBSW_PDUR_API_CALL_FORWARDING_ID_ONLY */
          }
        }
      }
      else
      {
        PduR_GetUpTpTpTxConfirmationFctPtrOfMmRom(PduR_GetMmRomIdxOfRmSrcRom(rmSrcIdx)) (PduR_GetSrcHndOfRmSrcRom(rmSrcIdx), E_NOT_OK); /* SBSW_PDUR_API_CALL_FORWARDING_ID_ONLY */
      }
    }
    else
    {
      PduR_GetUpTpTpTxConfirmationFctPtrOfMmRom(PduR_GetMmRomIdxOfRmSrcRom(rmSrcIdx)) (PduR_GetSrcHndOfRmSrcRom(rmSrcIdx), E_NOT_OK);   /* SBSW_PDUR_API_CALL_FORWARDING_ID_ONLY */
    }
  }
  PduR_Lock_UnlockRoutingPathBySrcPdu(rmSrcIdx);
  PDUR_DUMMY_STATEMENT(availableDataPtr);       /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  return retval;
}       /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_StartOfReception
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_StartOfReception(PduR_RmSrcRomIterType rmSrcIdx, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info,       /* PRQA S 3673 */ /* MD_MSR_Rule8.13 */
                                                              PduLengthType TpSduLength, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;   /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = PDUR_E_NO_ERROR;      /* PRQA S 2981 */ /* MD_MSR_RetVal */
  PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfRmSrcRom(rmSrcIdx);

# if (PDUR_DEV_ERROR_DETECT == STD_ON)  /* COV_PDUR_VAR_DEV_ERROR_DETECT */
  /* Check parameter bufferSizePtr */
  if(bufferSizePtr == NULL_PTR)
  {
    errorId = PDUR_E_PARAM_POINTER;
  }
#  if (PDUR_METADATA_SUPPORT == STD_ON)
  else if((PduR_IsMetaDataLengthUsedOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx), memIdx)) && ((info == NULL_PTR) || (info->SduDataPtr == NULL_PTR) || (info->SduLength < (PduLengthType) PduR_GetMetaDataLengthOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx), memIdx))))        /* COV_PDUR_FEATURE_ALWAYS_TRUE */
  {
    errorId = PDUR_E_PARAM_POINTER;
  }
#  endif
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    PduR_Lock_LockRoutingPathBySrcPdu(rmSrcIdx);
    {
      /* Handle src instance routing state */
      retVal = PduR_RmTp_StartOfReception_TpRxSmStateHandler(rmSrcIdx, info, TpSduLength, bufferSizePtr); /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
    }
    PduR_Lock_UnlockRoutingPathBySrcPdu(rmSrcIdx);
  }
# if (PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR)
  {
    PduR_Det_ReportError(PDUR_FCT_RMTP_SORX, errorId);
  }
# else
  PDUR_DUMMY_STATEMENT(errorId);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
# endif
  PDUR_DUMMY_STATEMENT(memIdx);         /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  return retVal;
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_StartOfReception_TpRxSmStateHandler
 *********************************************************************************************************************/
  /*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_StartOfReception_TpRxSmStateHandler(PduR_RmSrcRomIterType rmSrcIdx,
                                                                                 P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info,
                                                                                 PduLengthType TpSduLength,
                                                                                 P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr)
{
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  switch (PduR_GetTpRxSmStateOfRmBufferedTpPropertiesRam(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx), PduR_GetPartitionIndexOfCslOfRmSrcRom(rmSrcIdx)))
  {
    case PDUR_RM_RX_IDLE_TPRXSMSTATEOFRMBUFFEREDTPPROPERTIESRAM:
      retVal = PduR_RmTp_StartOfReception_TpRxSmStateHandler_RM_RX_IDLE(rmSrcIdx, info, TpSduLength, bufferSizePtr); /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
      break;

    case PDUR_RM_RX_ACTIVE_TPRXSMSTATEOFRMBUFFEREDTPPROPERTIESRAM:
      retVal = PduR_RmTp_StartOfReception_TpRxSmStateHandler_UnexpectedCall(rmSrcIdx, info, TpSduLength, bufferSizePtr); /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
      break;

    case PDUR_RM_RX_ABORTED_TPRXSMSTATEOFRMBUFFEREDTPPROPERTIESRAM:
      retVal = PduR_RmTp_StartOfReception_TpRxSmStateHandler_UnexpectedCall(rmSrcIdx, info, TpSduLength, bufferSizePtr); /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
      break;

    default: /* COV_PDUR_MISRA */
      /* If state is out-of-bounds: do nothing and return negative result. */
      retVal = BUFREQ_E_NOT_OK;
      break;
  }

  return retVal;
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM  == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_StartOfReception_TpRxSmStateHandler_RM_RX_IDLE
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
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_StartOfReception_TpRxSmStateHandler_RM_RX_IDLE(PduR_RmSrcRomIterType rmSrcIdx,
                                                                                            P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, PduLengthType TpSduLength, P2VAR(PduLengthType,
                                                                                                                                                                                   AUTOMATIC,
                                                                                                                                                                                   PDUR_APPL_DATA)
                                                                                            bufferSizePtr)
{
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  /* Allocate FiFo element */
  PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfRmSrcRom(rmSrcIdx);
  PduR_RmBufferedTpPropertiesRomIdxOfRmSrcRomType rmBufferedTpPropertiesRomIdx = PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx);
  PduR_FmFifoRomIterType fmFifoRomIdx = PduR_GetFmFifoRomIdxOfRmBufferedTpPropertiesRom(rmBufferedTpPropertiesRomIdx, memIdx);
  PduR_FmFifoElementRamWriteIdxOfFmFifoRamType fmFifoElementRamWriteIdx = PduR_Fm_GetFmFifoElementRamWriteIdxSafe(fmFifoRomIdx, memIdx);

  if(PduR_Fm_IsFifoElementAllocated(fmFifoElementRamWriteIdx, memIdx) != E_OK)
  {
    PduR_BmTxBufferRomIdxOfBmTxBufferIndRomType allocatedTxBufferIdxPtr = 0u;
    PduLengthType tpThreshold = PduR_GetTpThresholdOfRmBufferedTpPropertiesRom(rmBufferedTpPropertiesRomIdx, memIdx);
    PduLengthType metaDataLength = 0u;

# if  (PDUR_METADATA_SUPPORT == STD_ON )
    if(PduR_IsMetaDataLengthUsedOfRmBufferedTpPropertiesRom(rmBufferedTpPropertiesRomIdx, memIdx))
    {
      metaDataLength = PduR_GetMetaDataLengthOfRmBufferedTpPropertiesRom(rmBufferedTpPropertiesRomIdx, memIdx);
    }
# endif

    if(PduR_Bm_AllocateTxBuffer(fmFifoRomIdx, TpSduLength, TpSduLength + metaDataLength, tpThreshold + metaDataLength, bufferSizePtr, &allocatedTxBufferIdxPtr, memIdx) == BUFREQ_OK)  /* PRQA S 2985 */ /* MD_PduR_2985 */ /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
    {
      PduR_IncFillLevelOfFmFifoRam(fmFifoRomIdx, memIdx); /* SBSW_PDUR_CSL03 */
      PduR_Fm_IncrementWriteIndex(fmFifoRomIdx, memIdx);

      PduR_Fm_AssignTxBuffer2FifoElement(fmFifoElementRamWriteIdx, allocatedTxBufferIdxPtr, memIdx);
      PduR_SetRmDestRomIdxOfFmFifoElementRam(fmFifoElementRamWriteIdx, (PduR_RmDestRomIdxOfFmFifoElementRamType) PduR_GetRmDestRomStartIdxOfRmSrcRom(rmSrcIdx), memIdx);       /* SBSW_PDUR_CSL03 */

      /* Mapping Src Handle and current Fifo element */
      PduR_SetFmFifoElementRamIdxOfRmBufferedTpPropertiesRam(rmBufferedTpPropertiesRomIdx, fmFifoElementRamWriteIdx, memIdx);      /* SBSW_PDUR_CSL03 */

# if  (PDUR_METADATA_SUPPORT == STD_ON )
      if(PduR_IsMetaDataLengthUsedOfRmBufferedTpPropertiesRom(rmBufferedTpPropertiesRomIdx, memIdx)
          && (PduR_RmTp_StartOfReceptionQueueMetaData(rmSrcIdx, info->SduLength, info->SduDataPtr, bufferSizePtr) != BUFREQ_OK)) /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */ /* COV_PDUR_FATAL_ERROR */ /* PRQA S 3415 */ /* MD_PduR_3415 */
      {
        PduR_Det_ReportError(PDUR_RXSM_STARTOFRECEPTION, PDUR_E_FATAL);
        retVal = BUFREQ_E_NOT_OK;
      }
      else
# endif
      {
        PduR_SetTpRxSmStateOfRmBufferedTpPropertiesRam(rmBufferedTpPropertiesRomIdx, PDUR_RM_RX_ACTIVE_TPRXSMSTATEOFRMBUFFEREDTPPROPERTIESRAM, memIdx);     /* SBSW_PDUR_IDX_PARAM_INTERNAL_FUNCTION */

        if(PduR_RmTp_CheckReady2Transmit_TpTxSmStateHandler(fmFifoRomIdx, rmSrcIdx, memIdx) == E_OK)
        {
          retVal = BUFREQ_OK;
        }
        else
        {
          PduR_RmTp_TpRxIndication_TpRxSmStateHandler(rmSrcIdx, E_NOT_OK);
          retVal = BUFREQ_E_NOT_OK;
        }
      }
    }
  }
  PDUR_DUMMY_STATEMENT(rmSrcIdx);       /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(info);           /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(TpSduLength);    /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(bufferSizePtr);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  return retVal;
} /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM  == STD_ON)
 /**********************************************************************************************************************
 * PduR_RmTp_StartOfReception_TpRxSmStateHandler_UnexpectedCall
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_StartOfReception_TpRxSmStateHandler_UnexpectedCall(PduR_RmSrcRomIterType rmSrcIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info,
                                                                                                PduLengthType TpSduLength, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr)
{
  PduR_Det_ReportError(PDUR_FCT_SOR, PDUR_E_UNEXPECTED_CALL);
  PDUR_DUMMY_STATEMENT(rmSrcIdx);       /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(info);           /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(TpSduLength);    /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(bufferSizePtr);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  return BUFREQ_E_NOT_OK;
}
#endif

#if (PDUR_METADATA_SUPPORT == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_StartOfReceptionQueueMetaData
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_StartOfReceptionQueueMetaData(PduR_RmSrcRomIterType rmSrcIdx,
                                                                                        PduLengthType pduLength,
                                                                                        SduDataPtrType sduDataPtr, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr)
{
  PduLengthType pduLengthIntern = pduLength;
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;
  PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfRmSrcRom(rmSrcIdx);

  PduR_BmTxBufferArrayRamIterType metadataStartPosition =
    pduLengthIntern - (PduR_BmTxBufferArrayRamIterType) PduR_GetMetaDataLengthOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx), memIdx);

  PduR_BmTxBufferRomIterType bmTxBufferRomIdx;
  if(PduR_RmTp_GetCurrentlyUsedBmTxBufferRamIdxByRmSrcIdx(rmSrcIdx, &bmTxBufferRomIdx) == E_OK) /* SBSW_PDUR_STACK_VARIABLE */ /* COV_PDUR_ROBUSTNESS */
  {
    /* Metadata is appended after the payload data */
    /* Length information is used to enqueue the MetaData */
    pduLengthIntern = PduR_GetMetaDataLengthOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx), memIdx);
    /* enqueue data will never fail in this context because the buffer is always empty */
    retVal = PduR_Bm_PutData(bmTxBufferRomIdx, pduLengthIntern, &sduDataPtr[metadataStartPosition], memIdx); /* SBSW_PDUR_STACK_VARIABLE */
    *bufferSizePtr = (PduLengthType) PduR_Bm_GetTotalBufferSize(bmTxBufferRomIdx, memIdx);        /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
  }
  return retVal;
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_CopyRxData
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_CopyRxData(PduR_RmSrcRomIdxOfRxTp2DestType rmSrcIdx, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info,
                                                        P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr)
{
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;   /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = PDUR_E_NO_ERROR;      /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
# if (PDUR_DEV_ERROR_DETECT == STD_ON)  /* COV_PDUR_VAR_DEV_ERROR_DETECT */

  /* Check parameter 'info' */
  if(info == NULL_PTR)
  {
    errorId = PDUR_E_PARAM_POINTER;
  }
  else if((info->SduLength > 0u) && (info->SduDataPtr == NULL_PTR))
  {
    errorId = PDUR_E_PARAM_POINTER;
  }
  else if(bufferSizePtr == NULL_PTR)
  {
    errorId = PDUR_E_PARAM_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    PduR_Lock_LockRoutingPathBySrcPdu(rmSrcIdx);
    {
      /* Handle src instance routing state */
      retVal = PduR_RmTp_CopyRxData_TpRxSmStateHandler(rmSrcIdx, info, bufferSizePtr); /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
    }
    PduR_Lock_UnlockRoutingPathBySrcPdu(rmSrcIdx);
  }
  /* ----- Development Error Report --------------------------------------- */
# if (PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR)
  {
    PduR_Det_ReportError(PDUR_FCT_RMTP_CPYRX, errorId);
  }
# else
  PDUR_DUMMY_STATEMENT(errorId);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
# endif
  return retVal;
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_CopyRxData_TpRxSmStateHandler
 *********************************************************************************************************************/
  /*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CONST) PduR_RmTp_CopyRxData_TpRxSmStateHandler(PduR_RmSrcRomIdxOfRxTp2DestType rmSrcIdx,
                                                                            P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info,
                                                                            P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr)
{
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfRmSrcRom(rmSrcIdx);

  switch (PduR_GetTpRxSmStateOfRmBufferedTpPropertiesRam(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx), memIdx))
  {
    case PDUR_RM_RX_IDLE_TPRXSMSTATEOFRMBUFFEREDTPPROPERTIESRAM:
      retVal = PduR_RmTp_CopyRxData_TpRxSmStateHandler_UnexpectedCall((PduR_RmSrcRomIterType) rmSrcIdx, info->SduLength, info->SduDataPtr, bufferSizePtr); /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
      break;

    case PDUR_RM_RX_ACTIVE_TPRXSMSTATEOFRMBUFFEREDTPPROPERTIESRAM:
      retVal = PduR_RmTp_CopyRxData_TpRxSmStateHandler_RM_RX_ACTIVE((PduR_RmSrcRomIterType) rmSrcIdx, info->SduLength, info->SduDataPtr, bufferSizePtr); /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
      break;

    case PDUR_RM_RX_ABORTED_TPRXSMSTATEOFRMBUFFEREDTPPROPERTIESRAM:
      retVal = PduR_RmTp_CopyRxData_TpRxSmStateHandler_RM_RX_ABORTED((PduR_RmSrcRomIterType) rmSrcIdx, info->SduLength, info->SduDataPtr, bufferSizePtr); /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
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
 * PduR_RmTp_CopyRxData_TpRxSmStateHandler_RM_RX_ACTIVE
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_CopyRxData_TpRxSmStateHandler_RM_RX_ACTIVE(PduR_RmSrcRomIterType rmSrcIdx, PduLengthType pduLength,
                                                                                        SduDataPtrType sduDataPtr, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr)
{
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;
  PduR_BmTxBufferRomIterType bmTxBufferRomIdx;

  if(PduR_RmTp_GetCurrentlyUsedBmTxBufferRamIdxByRmSrcIdx(rmSrcIdx, &bmTxBufferRomIdx) == E_OK) /* SBSW_PDUR_STACK_VARIABLE */ /* COV_PDUR_ROBUSTNESS */
  {
    PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfRmSrcRom(rmSrcIdx);

    retVal = PduR_Bm_PutData(bmTxBufferRomIdx, pduLength, sduDataPtr, memIdx);        /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */

    if(retVal == BUFREQ_OK)
    {
      PduR_FmFifoRamIterType fmFifoRomIdx = PduR_GetFmFifoRomIdxOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx), memIdx);

      if(PduR_RmTp_CheckReady2Transmit_TpTxSmStateHandler(fmFifoRomIdx, rmSrcIdx, memIdx) != E_OK)
      {
        retVal = BUFREQ_E_NOT_OK;
      }
    }
    *bufferSizePtr = (PduLengthType) PduR_Bm_GetTotalBufferSize(bmTxBufferRomIdx, memIdx);      /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
  }

  return retVal;
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_CopyRxData_TpRxSmStateHandler_RM_RX_ABORTED
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_CopyRxData_TpRxSmStateHandler_RM_RX_ABORTED(PduR_RmSrcRomIterType rmSrcIdx, PduLengthType pduLength,
                                                                                         SduDataPtrType sduDataPtr, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr)
{
  PDUR_DUMMY_STATEMENT(rmSrcIdx);       /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(pduLength);      /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(sduDataPtr);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(bufferSizePtr);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  return BUFREQ_E_NOT_OK;
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_CopyRxData_TpRxSmStateHandler_UnexpectedCall
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_CopyRxData_TpRxSmStateHandler_UnexpectedCall(PduR_RmSrcRomIterType rmSrcIdx, PduLengthType pduLength,
                                                                                          SduDataPtrType sduDataPtr, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr)
{
  PduR_Det_ReportError(PDUR_RXSM_COPYRXDATA_UNEXPECTEDCALL, PDUR_E_UNEXPECTED_CALL);
  PDUR_DUMMY_STATEMENT(rmSrcIdx);       /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(pduLength);      /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(sduDataPtr);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(bufferSizePtr);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  return BUFREQ_E_NOT_OK;
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_AssignAssociatedBuffer2Destination
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmTp_AssignAssociatedBuffer2Destination(PduR_BmTxBufferRomIterType bmTxBufferRomIdx, PduR_RmSrcRomIterType rmSrcIdx)
{
  PduR_RmDestRomStartIdxOfRmSrcRomType rmDestRomIdx;
  PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfRmSrcRom(rmSrcIdx);
  PduR_BmTxBufferInstanceRomStartIdxOfBmTxBufferRomType bmTxBufferInstanceRomIdx = PduR_GetBmTxBufferInstanceRomStartIdxOfBmTxBufferRom(bmTxBufferRomIdx, memIdx);

  for(rmDestRomIdx = PduR_GetRmDestRomStartIdxOfRmSrcRom(rmSrcIdx); (rmDestRomIdx < PduR_GetRmDestRomEndIdxOfRmSrcRom(rmSrcIdx)) && (bmTxBufferInstanceRomIdx < PduR_GetBmTxBufferInstanceRomEndIdxOfBmTxBufferRom(bmTxBufferRomIdx, memIdx)); rmDestRomIdx++) /* COV_PDUR_ROBUSTNESS */
  {
    if(PduR_GetRoutingTypeOfRmDestRom(rmDestRomIdx) == PDUR_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM) /* COV_PDUR_ONLY_TP_QUEUED_ROUTINGS */
    {
      PduR_RmGDestRomIdxOfRmDestRomType rmGDestRomIdx = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestRomIdx);
      PduR_Bm_EnableBmTxBufferInstance(bmTxBufferRomIdx, bmTxBufferInstanceRomIdx, memIdx);
      PduR_SetBmTxBufferInstanceRomIdxOfFmFifoInstanceRam(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx), bmTxBufferInstanceRomIdx, memIdx);     /* SBSW_PDUR_CSL03 */
      bmTxBufferInstanceRomIdx++;
    }
  }
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_TpRxIndication
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_RmTp_TpRxIndication(PduR_RmSrcRomIdxOfRxTp2DestType rmSrcIdx, Std_ReturnType result)
{
  /* ----- Implementation ----------------------------------------------- */
  PduR_Lock_LockRoutingPathBySrcPdu(rmSrcIdx);
  {
    /* Handle src instance routing state */
    PduR_RmTp_TpRxIndication_TpRxSmStateHandler(rmSrcIdx, result);
  }
  PduR_Lock_UnlockRoutingPathBySrcPdu(rmSrcIdx);
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM  == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_TpRxIndication_TpRxSmStateHandler
 *********************************************************************************************************************/
  /*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmTp_TpRxIndication_TpRxSmStateHandler(PduR_RmSrcRomIterType rmSrcIdx, Std_ReturnType result)
{
  switch (PduR_GetTpRxSmStateOfRmBufferedTpPropertiesRam(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx), PduR_GetPartitionIndexOfCslOfRmSrcRom(rmSrcIdx)))
  {
    case PDUR_RM_RX_IDLE_TPRXSMSTATEOFRMBUFFEREDTPPROPERTIESRAM:
      PduR_RmTp_TpRxIndication_TpRxSmStateHandler_UnexpectedCall((PduR_RmSrcRomIterType) rmSrcIdx, result);
      break;

    case PDUR_RM_RX_ACTIVE_TPRXSMSTATEOFRMBUFFEREDTPPROPERTIESRAM:
      PduR_RmTp_TpRxIndication_TpRxSmStateHandler_RM_RX_ACTIVE_OR_RM_RX_ABORTED((PduR_RmSrcRomIterType) rmSrcIdx, result);
      break;

    case PDUR_RM_RX_ABORTED_TPRXSMSTATEOFRMBUFFEREDTPPROPERTIESRAM:
      PduR_RmTp_TpRxIndication_TpRxSmStateHandler_RM_RX_ACTIVE_OR_RM_RX_ABORTED((PduR_RmSrcRomIterType) rmSrcIdx, result);
      break;

    default: /* COV_PDUR_MISRA */
      /* If state is out-of-bounds: do nothing. */
      break;
  }
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_TpRxIndication_TpRxSmStateHandler_RM_RX_ACTIVE_OR_RM_RX_ABORTED
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
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmTp_TpRxIndication_TpRxSmStateHandler_RM_RX_ACTIVE_OR_RM_RX_ABORTED(PduR_RmSrcRomIterType rmSrcIdx, Std_ReturnType result)
{
  PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfRmSrcRom(rmSrcIdx);
  PduR_FmFifoRamIterType fmFifoRomIdx = PduR_GetFmFifoRomIdxOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx), memIdx);
  PduR_FmFifoElementRamIterType fmFifoElementRamReadIdx = PduR_Fm_GetFmFifoElementRamReadIdxOfFmFifoRamSafe(fmFifoRomIdx, memIdx);
  PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx;

  if(PduR_RmTp_GetCurrentlyWrittenFmFifoElementRamIdxByRmSrcIdx(rmSrcIdx, &fmFifoElementRamWriteIdx) == E_OK) /* SBSW_PDUR_STACK_VARIABLE */ /* COV_PDUR_ROBUSTNESS */
  {
    /* Is this rmSrcIdx Pdu instance the oldest Pdu in the queue? */
    if(fmFifoElementRamWriteIdx == fmFifoElementRamReadIdx)
    {
      PduR_RmTp_FinishReception_TpTxSmStateHandler(rmSrcIdx, result);
    }
    else
    {
      if(result != E_OK)
      {
        PduR_Fm_ReleaseFifoElement(fmFifoElementRamWriteIdx, memIdx);
      }
    }
  }

  PduR_SetFmFifoElementRamIdxOfRmBufferedTpPropertiesRam(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx), PDUR_NO_FMFIFOELEMENTRAMIDXOFRMBUFFEREDTPPROPERTIESRAM, memIdx);     /* SBSW_PDUR_CSL03 */
  PduR_SetTpRxSmStateOfRmBufferedTpPropertiesRam(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx), PDUR_RM_RX_IDLE_TPRXSMSTATEOFRMBUFFEREDTPPROPERTIESRAM, memIdx);     /* SBSW_PDUR_CSL03 */
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_TpRxIndication_TpRxSmStateHandler_UnexpectedCall
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmTp_TpRxIndication_TpRxSmStateHandler_UnexpectedCall(PduR_RmSrcRomIterType rmSrcIdx, Std_ReturnType result)
{
  PduR_Det_ReportError(PDUR_RMTP_RXSM_TPRXINDICATION_UNEXPECTEDCALL, PDUR_E_UNEXPECTED_CALL);
  PDUR_DUMMY_STATEMENT(rmSrcIdx);       /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(result); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_CopyTxData
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_CopyTxData(PduR_RmGDestRomIdxOfTxTp2SrcType rmGDestRomIdx,
                                                                     P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info,
                                                                     P2VAR(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA) retry, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) availableDataPtr)
{
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;   /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = PDUR_E_NO_ERROR;      /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
# if (PDUR_DEV_ERROR_DETECT == STD_ON)  /* COV_PDUR_VAR_DEV_ERROR_DETECT */
  /* parameter 'Handle Id' already checked by the caller API */
  /* Check parameter 'info' */
  if(info == NULL_PTR)
  {
    errorId = PDUR_E_PARAM_POINTER;
  }
  else if((info->SduLength > 0u) && (info->SduDataPtr == NULL_PTR))
  {
    errorId = PDUR_E_PARAM_POINTER;
  }
  else if(availableDataPtr == NULL_PTR)
  {
    errorId = PDUR_E_PARAM_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    PduR_Lock_LockRoutingPathByGDestPdu(rmGDestRomIdx);
    {
      /* Handle global routing state */
      retVal = PduR_RmTp_TxInst_CopyTxData(rmGDestRomIdx, info, retry, availableDataPtr);       /* SBSW_PDUR_CSL03 */
    }
    PduR_Lock_UnlockRoutingPathByGDestPdu(rmGDestRomIdx);
    PDUR_DUMMY_STATEMENT(retry);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  }
  /* ----- Development Error Report --------------------------------------- */
# if (PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR)
  {
    PduR_Det_ReportError(PDUR_FCT_RMTP_CPYTX, errorId);
  }
# else
  PDUR_DUMMY_STATEMENT(errorId);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
# endif
  return retVal;
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_ThresholdReached
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_ThresholdReached(PduR_RmSrcRomIterType rmSrcIdx)
{
  /* Trigger transmission if required */
  Std_ReturnType retVal = E_NOT_OK;     /* PRQA S 2981 */ /* MD_MSR_RetVal */
  PduR_BmTxBufferRomIterType bmTxBufferRomIdx;

  if(PduR_RmTp_GetCurrentlyUsedBmTxBufferRamIdxByRmSrcIdx(rmSrcIdx, &bmTxBufferRomIdx) == E_OK) /* SBSW_PDUR_STACK_VARIABLE */ /* COV_PDUR_ROBUSTNESS */
  {
    PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfRmSrcRom(rmSrcIdx);
    PduR_BmTxBufferArrayRamIterType availableTotalDataSize = PduR_Bm_GetTotalDataSize(bmTxBufferRomIdx, memIdx);

    /* MetaData length is not taken into account to calculate the Threshold */
  # if (PDUR_METADATA_SUPPORT == STD_ON )
    if(PduR_IsMetaDataLengthUsedOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx), memIdx))    /* COV_PDUR_FEATURE_ALWAYS_TRUE */
    {
      availableTotalDataSize -= (PduR_BmTxBufferArrayRamIterType) PduR_GetMetaDataLengthOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx), memIdx);
    }
  # endif

    /* Threshold reached or reception finished (sub state machine is in IDLE) */
    if(availableTotalDataSize >= PduR_GetTpThresholdOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx), memIdx))
    {
      retVal = E_OK;
    }
  }

  return retVal;
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_TriggerTransmissionOfDestinations
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
PDUR_LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_TriggerTransmissionOfDestinations(PduR_RmSrcRomIterType rmSrcIdx)
{
  Std_ReturnType retVal = E_NOT_OK;     /* PRQA S 2981 */ /* MD_MSR_RetVal */
  PduR_RmDestRomIterType rmDestRomIdx;
  PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfRmSrcRom(rmSrcIdx);
  PduR_FmFifoRamIterType fmFifoRomIdx = PduR_GetFmFifoRomIdxOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx), memIdx);
  PduR_FmFifoElementRamIterType fmFifoElementRamReadIdx = PduR_Fm_GetFmFifoElementRamReadIdxOfFmFifoRamSafe(fmFifoRomIdx, memIdx);
  PduR_BmTxBufferRomIterType bmTxBufferRomIdx;

  if(PduR_Fm_GetCurrentlyUsedBmTxBufferRomIdxByFmFifoElementIdx(fmFifoElementRamReadIdx, &bmTxBufferRomIdx, memIdx) == E_OK) /* SBSW_PDUR_STACK_VARIABLE */ /* COV_PDUR_ROBUSTNESS */
  {
    PduR_SetPendingConfirmationsOfFmFifoRam(fmFifoRomIdx, PduR_GetQueuedDestCntOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx), memIdx), memIdx); /* SBSW_PDUR_CSL03 */
    /* Assign Tx Buffer */
    PduR_RmTp_AssignAssociatedBuffer2Destination(bmTxBufferRomIdx, rmSrcIdx);

    for(rmDestRomIdx = PduR_GetRmDestRomStartIdxOfRmSrcRom(rmSrcIdx); rmDestRomIdx < PduR_GetRmDestRomEndIdxOfRmSrcRom(rmSrcIdx); rmDestRomIdx++)
    {
      PduR_RmGDestRomIterType rmGDestRomIdx = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestRomIdx);

      if(PduR_GetRoutingTypeOfRmDestRom(rmDestRomIdx) == PDUR_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM) /* COV_PDUR_ONLY_TP_QUEUED_ROUTINGS */
      {
# if (PDUR_RPGROM == STD_ON)
        if(PduR_IsDestPduEnabled(rmDestRomIdx) == FALSE)
        {
          PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx;

          if(PduR_Fm_GetCurrentlyUsedBmTxBufferInstanceIdxByRmGDestIdx(rmGDestRomIdx, &bmTxBufferInstanceRomIdx) == E_OK) /* SBSW_PDUR_STACK_VARIABLE */ /* COV_PDUR_ROBUSTNESS */
          {
            PduR_Bm_ResetTxBufferInstance(bmTxBufferInstanceRomIdx, memIdx);
          }
          PduR_RmTp_FinishTransmission_TpTxSmStateHandler(fmFifoRomIdx, E_NOT_OK, memIdx);
          retVal &= E_NOT_OK;
        }
        else
# endif
        {
# if(PDUR_RMGDESTNTO1INFORAMIDXOFRMGDESTROM == STD_ON)
          if(PduR_IsRmGDestNto1InfoRamUsedOfRmGDestRom(rmGDestRomIdx))
          {
            PduR_RmGDestNto1InfoRamIdxOfRmGDestRomType rmGDestNto1InfoIdx = PduR_GetRmGDestNto1InfoRamIdxOfRmGDestRom(rmGDestRomIdx);

            if(!PduR_IsTransmissionActiveOfRmGDestNto1InfoRam(rmGDestNto1InfoIdx, memIdx))  /* COV_PDUR_CROSSCORE_ROUTINGS_ONLY */
            {
              PduR_SetRmDestRomIdxOfRmGDestNto1InfoRam(rmGDestNto1InfoIdx, (PduR_RmDestRomIdxOfRmGDestNto1InfoRamType) rmDestRomIdx, memIdx);       /* SBSW_PDUR_CSL03 */
              PduR_SetTransmissionActiveOfRmGDestNto1InfoRam(rmGDestNto1InfoIdx, TRUE, memIdx);     /* SBSW_PDUR_CSL03 */

              retVal &= PduR_RmTp_TxInst_TriggerTransmit(rmDestRomIdx, rmGDestRomIdx);
              if(E_OK != retVal)    /* COV_PDUR_CROSSCORE_ROUTINGS_ONLY */
              {
                PduR_Rm_MultipleSourceHandler_Reset(rmGDestRomIdx);
              }
            }
          }
          else
# endif
          {
            retVal &= PduR_RmTp_TxInst_TriggerTransmit(rmDestRomIdx, rmGDestRomIdx);
          }
        }
      }
    }
  }
  return retVal;
}       /* PRQA S 6080, 6050 */ /* MD_MSR_STMIF, MD_MSR_STCAL */
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_CheckReady2Transmit_TpTxSmStateHandler
 *********************************************************************************************************************/
  /*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_CheckReady2Transmit_TpTxSmStateHandler(PduR_FmFifoRamIterType fmFifoRomIdx, PduR_RmSrcRomIterType rmSrcIdx, PduR_MemIdxType memIdx)
{
  Std_ReturnType retVal = E_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  PduR_FmFifoElementRamIterType fmFifoElementRamReadIdx = PduR_Fm_GetFmFifoElementRamReadIdxOfFmFifoRamSafe(fmFifoRomIdx, memIdx);
  PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx;

  if(PduR_RmTp_GetCurrentlyWrittenFmFifoElementRamIdxByRmSrcIdx(rmSrcIdx, &fmFifoElementRamWriteIdx) == E_OK) /* SBSW_PDUR_STACK_VARIABLE */ /* COV_PDUR_ROBUSTNESS */
  {
    /* Is this rmSrcIdx Pdu instance the oldest Pdu in the queue? */
    if(fmFifoElementRamWriteIdx == fmFifoElementRamReadIdx)
    {
      switch (PduR_GetTpTxSmStateOfFmFifoRam(fmFifoRomIdx, PduR_GetPartitionIndexOfCslOfRmSrcRom(rmSrcIdx)))
      {
        case PDUR_RM_TX_IDLE_TPTXSMSTATEOFFMFIFORAM:
        case PDUR_RM_TX_RECEPTION_ACTIVE_TPTXSMSTATEOFFMFIFORAM:
          retVal = PduR_RmTp_CheckReady2Transmit_TpTxSmStateHandler_RM_TX_IDLE_OR_RM_TX_RECEPTION_ACTIVE(rmSrcIdx);
          break;

        case PDUR_RM_TX_TRANSMISSION_FINISHED_TPTXSMSTATEOFFMFIFORAM: /* COV_PDUR_FATAL_ERROR */
          retVal = PduR_RmTp_CheckReady2Transmit_TpTxSmStateHandler_FatalError(rmSrcIdx);
          break;

        case PDUR_RM_TX_RECEPTION_TRANSMISSION_ACTIVE_TPTXSMSTATEOFFMFIFORAM:
          retVal = PduR_RmTp_CheckReady2Transmit_TpTxSmStateHandler_NoAction(rmSrcIdx);
          break;

        case PDUR_RM_TX_RECEPTION_FINISHED_TRANSMISSION_ACTIVE_TPTXSMSTATEOFFMFIFORAM: /* COV_PDUR_FATAL_ERROR */
          retVal = PduR_RmTp_CheckReady2Transmit_TpTxSmStateHandler_FatalError(rmSrcIdx);
          break;

        default: /* COV_PDUR_MISRA */
          /* If state is out-of-bounds: do nothing and return with negative result. */
          retVal = E_NOT_OK;
          break;
      }
    }
  }

  return retVal;
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_CheckReady2Transmit_TpTxSmStateHandler_RM_TX_IDLE_OR_RM_TX_RECEPTION_ACTIVE
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
PDUR_LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_CheckReady2Transmit_TpTxSmStateHandler_RM_TX_IDLE_OR_RM_TX_RECEPTION_ACTIVE(PduR_RmSrcRomIterType rmSrcIdx)
{
  Std_ReturnType retVal = E_NOT_OK;     /* PRQA S 2981 */ /* MD_MSR_RetVal */
  PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfRmSrcRom(rmSrcIdx);
  PduR_FmFifoRamIterType fmFifoRamIdx = PduR_GetFmFifoRomIdxOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx), memIdx);
  if(PduR_RmTp_ThresholdReached(rmSrcIdx) == E_OK)
  {
    PduR_SetTpTxSmStateOfFmFifoRam(fmFifoRamIdx, PDUR_RM_TX_RECEPTION_TRANSMISSION_ACTIVE_TPTXSMSTATEOFFMFIFORAM, memIdx);    /* SBSW_PDUR_CSL03 */

    retVal = PduR_RmTp_TriggerTransmissionOfDestinations(rmSrcIdx);
    if(retVal != E_OK)
    {
      PduR_SetTpTxSmStateOfFmFifoRam(fmFifoRamIdx, PDUR_RM_TX_RECEPTION_ACTIVE_TPTXSMSTATEOFFMFIFORAM, memIdx);       /* SBSW_PDUR_CSL03 */
    }
  }
  else
  {
    retVal = E_OK;
    PduR_SetTpTxSmStateOfFmFifoRam(fmFifoRamIdx, PDUR_RM_TX_RECEPTION_ACTIVE_TPTXSMSTATEOFFMFIFORAM, memIdx);   /* SBSW_PDUR_CSL03 */
  }
  return retVal;
}       /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_CheckReady2Transmit_TpTxSmStateHandler_NoAction
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_CheckReady2Transmit_TpTxSmStateHandler_NoAction(PduR_RmSrcRomIterType rmSrcIdx)
{
  PDUR_DUMMY_STATEMENT(rmSrcIdx);       /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  return E_OK;
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_CheckReady2Transmit_TpTxSmStateHandler_FatalError
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_CheckReady2Transmit_TpTxSmStateHandler_FatalError(PduR_RmSrcRomIterType rmSrcIdx) /* COV_PDUR_FATAL_ERROR */
{
  PduR_Det_ReportError(PDUR_RMTP_TXSM_CHECKREADY2TRANSMIT_FATALERROR, PDUR_E_FATAL);
  PDUR_DUMMY_STATEMENT(rmSrcIdx);       /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  return E_NOT_OK;
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
 /**********************************************************************************************************************
 * PduR_RmTp_CancelTransmitOnDestinations
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmTp_CancelTransmitOnDestinations(PduR_RmSrcRomIterType rmSrcIdx)
{
  PduR_RmDestRomIterType rmDestRomIdx;
  for(rmDestRomIdx = PduR_GetRmDestRomStartIdxOfRmSrcRom(rmSrcIdx); rmDestRomIdx < PduR_GetRmDestRomEndIdxOfRmSrcRom(rmSrcIdx); rmDestRomIdx++)
  {
    if(PduR_GetRoutingTypeOfRmDestRom(rmDestRomIdx) == PDUR_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM) /* COV_PDUR_ONLY_TP_QUEUED_ROUTINGS */
    {
      PduR_RmTp_TxInst_CancelTransmit(PduR_GetRmGDestRomIdxOfRmDestRom(rmDestRomIdx));
    }
  }
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_FinishTransmission_TpTxSmStateHandler
 *********************************************************************************************************************/
  /*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_RmTp_FinishTransmission_TpTxSmStateHandler(PduR_FmFifoRomIterType fmFifoRomIdx, Std_ReturnType result, PduR_MemIdxType memIdx)
{
  PduR_DecPendingConfirmationsOfFmFifoRam(fmFifoRomIdx, memIdx);    /* SBSW_PDUR_CSL03 */

  switch (PduR_GetTpTxSmStateOfFmFifoRam(fmFifoRomIdx, memIdx))
  {
    case PDUR_RM_TX_IDLE_TPTXSMSTATEOFFMFIFORAM: /* COV_PDUR_FATAL_ERROR */
    case PDUR_RM_TX_RECEPTION_ACTIVE_TPTXSMSTATEOFFMFIFORAM: /* COV_PDUR_FATAL_ERROR */
    case PDUR_RM_TX_TRANSMISSION_FINISHED_TPTXSMSTATEOFFMFIFORAM: /* COV_PDUR_FATAL_ERROR */
      PduR_RmTp_FinishTransmission_TpTxSmStateHandler_FatalError(fmFifoRomIdx, result);
      break;

    case PDUR_RM_TX_RECEPTION_TRANSMISSION_ACTIVE_TPTXSMSTATEOFFMFIFORAM:
      PduR_RmTp_FinishTransmission_TpTxSmStateHandler_RM_TX_RECEPTION_TRANSMISSION_ACTIVE(fmFifoRomIdx, result, memIdx);
      break;

    case PDUR_RM_TX_RECEPTION_FINISHED_TRANSMISSION_ACTIVE_TPTXSMSTATEOFFMFIFORAM:
      PduR_RmTp_FinishTransmission_TpTxSmStateHandler_RM_TX_RECEPTION_FINISHED_TRANSMISSION_ACTIVE(fmFifoRomIdx, result, memIdx);
      break;

    default: /* COV_PDUR_MISRA */
      /* If state is out-of-bounds: do nothing. */
      break;
  }
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_FinishTransmission_TpTxSmStateHandler_RM_TX_RECEPTION_FINISHED_TRANSMISSION_ACTIVE
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmTp_FinishTransmission_TpTxSmStateHandler_RM_TX_RECEPTION_FINISHED_TRANSMISSION_ACTIVE(PduR_FmFifoRomIterType fmFifoRomIdx, Std_ReturnType result, PduR_MemIdxType memIdx)
{
  if(PduR_GetPendingConfirmationsOfFmFifoRam(fmFifoRomIdx, memIdx) == 0u)
  {
    PduR_FmFifoElementRamIterType fmFifoElementRamReadIdx = PduR_Fm_GetFmFifoElementRamReadIdxOfFmFifoRamSafe(fmFifoRomIdx, memIdx);

    PduR_Fm_ReleaseFifoElement(fmFifoElementRamReadIdx, memIdx);

    PduR_SetTpTxSmStateOfFmFifoRam(fmFifoRomIdx, PDUR_RM_TX_IDLE_TPTXSMSTATEOFFMFIFORAM, memIdx);       /* SBSW_PDUR_CSL03 */
    PduR_RmTp_ActivateNext(fmFifoRomIdx, memIdx);
  }
  PDUR_DUMMY_STATEMENT(result); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_FinishTransmission_TpTxSmStateHandler_RM_TX_RECEPTION_TRANSMISSION_ACTIVE
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmTp_FinishTransmission_TpTxSmStateHandler_RM_TX_RECEPTION_TRANSMISSION_ACTIVE(PduR_FmFifoRomIterType fmFifoRomIdx, Std_ReturnType result, PduR_MemIdxType memIdx)
{
  if(PduR_GetPendingConfirmationsOfFmFifoRam(fmFifoRomIdx, memIdx) == 0u)
  {
    PduR_SetTpTxSmStateOfFmFifoRam(fmFifoRomIdx, PDUR_RM_TX_TRANSMISSION_FINISHED_TPTXSMSTATEOFFMFIFORAM, memIdx);      /* SBSW_PDUR_CSL01 */
    if(result != E_OK)
    {
      PduR_RmSrcRomIterType rmSrcRomIdx;

      if(PduR_RmTp_GetRmSrcRomIdxOfOldestFmFifoElementSafe(fmFifoRomIdx, &rmSrcRomIdx, memIdx) == E_OK) /* SBSW_PDUR_STACK_VARIABLE */ /* COV_PDUR_ROBUSTNESS */
      {
        PduR_RmTp_CancelReceive_TpRxSmStateHandler(rmSrcRomIdx);
      }
    }
  }
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_FinishTransmission_TpTxSmStateHandler_FatalError
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmTp_FinishTransmission_TpTxSmStateHandler_FatalError(PduR_FmFifoRomIterType fmFifoRomIdx, Std_ReturnType result)   /* COV_PDUR_FATAL_ERROR */
{
  PduR_Det_ReportError(PDUR_RMTP_TXSM_FINISHTX_FATALERROR, PDUR_E_FATAL);
  PDUR_DUMMY_STATEMENT(fmFifoRomIdx);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(result); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_FinishReception_TpTxSmStateHandler
 *********************************************************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmTp_FinishReception_TpTxSmStateHandler(PduR_RmSrcRomIterType rmSrcIdx, Std_ReturnType result)
{
  PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfRmSrcRom(rmSrcIdx);
  PduR_FmFifoRomIterType fmFifoRomIdx = PduR_GetFmFifoRomIdxOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx), memIdx);

  switch (PduR_GetTpTxSmStateOfFmFifoRam(fmFifoRomIdx, memIdx))
  {
    case PDUR_RM_TX_IDLE_TPTXSMSTATEOFFMFIFORAM: /* COV_PDUR_FATAL_ERROR */
      PduR_RmTp_FinishReception_TpTxSmStateHandler_FatalError(rmSrcIdx, result);
      break;

    case PDUR_RM_TX_RECEPTION_ACTIVE_TPTXSMSTATEOFFMFIFORAM:
      PduR_RmTp_FinishReception_TpTxSmStateHandler_RM_TX_RECEPTION_ACTIVE(rmSrcIdx, result);
      break;

    case PDUR_RM_TX_TRANSMISSION_FINISHED_TPTXSMSTATEOFFMFIFORAM:
      PduR_RmTp_FinishReception_TpTxSmStateHandler_RM_TX_TRANSMISSION_FINISHED(rmSrcIdx, result);
      break;

    case PDUR_RM_TX_RECEPTION_TRANSMISSION_ACTIVE_TPTXSMSTATEOFFMFIFORAM:
      PduR_RmTp_FinishReception_TpTxSmStateHandler_RM_TX_RECEPTION_TRANSMISSION_ACTIVE(rmSrcIdx, result);
      break;

    case PDUR_RM_TX_RECEPTION_FINISHED_TRANSMISSION_ACTIVE_TPTXSMSTATEOFFMFIFORAM: /* COV_PDUR_FATAL_ERROR */
      PduR_RmTp_FinishReception_TpTxSmStateHandler_FatalError(rmSrcIdx, result);
      break;

    default: /* COV_PDUR_MISRA */
      /* If state is out-of-bounds: do nothing. */
      break;
  }
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_FinishReception_TpTxSmStateHandler_FatalError
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmTp_FinishReception_TpTxSmStateHandler_FatalError(PduR_RmSrcRomIterType rmSrcIdx, Std_ReturnType result) /* COV_PDUR_FATAL_ERROR */
{
  PduR_Det_ReportError(PDUR_FINISHRECEPTION, PDUR_E_FATAL);
  PDUR_DUMMY_STATEMENT(rmSrcIdx);       /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(result); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}       /* PRQA S 6080 */ /* MD_MSR_STMIF */

#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM  == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_FinishReception_TpTxSmStateHandler_RM_TX_RECEPTION_ACTIVE
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
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmTp_FinishReception_TpTxSmStateHandler_RM_TX_RECEPTION_ACTIVE(PduR_RmSrcRomIterType rmSrcIdx, Std_ReturnType result)
{
  PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfRmSrcRom(rmSrcIdx);
  PduR_FmFifoRamIterType fmFifoRomIdx = PduR_GetFmFifoRomIdxOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx), memIdx);

  if(result == E_OK)
  {
    PduR_SetTpTxSmStateOfFmFifoRam(fmFifoRomIdx, PDUR_RM_TX_RECEPTION_FINISHED_TRANSMISSION_ACTIVE_TPTXSMSTATEOFFMFIFORAM, memIdx);   /* SBSW_PDUR_CSL01 */

    if(PduR_RmTp_TriggerTransmissionOfDestinations(rmSrcIdx) != E_OK)
    {
      PduR_SetTpTxSmStateOfFmFifoRam(fmFifoRomIdx, PDUR_RM_TX_IDLE_TPTXSMSTATEOFFMFIFORAM, memIdx);     /* SBSW_PDUR_CSL01 */
      PduR_RmTp_ActivateNext(fmFifoRomIdx, memIdx);
    }
  }
  else
  {
    PduR_Fm_ReleaseFifoElement(PduR_Fm_GetFmFifoElementRamReadIdxOfFmFifoRamSafe(fmFifoRomIdx, memIdx), memIdx);
    PduR_SetTpTxSmStateOfFmFifoRam(fmFifoRomIdx, PDUR_RM_TX_IDLE_TPTXSMSTATEOFFMFIFORAM, memIdx);     /* SBSW_PDUR_CSL01 */
    PduR_RmTp_ActivateNext(fmFifoRomIdx, memIdx);
  }
}       /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_FinishReception_TpTxSmStateHandler_RM_TX_RECEPTION_TRANSMISSION_ACTIVE
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmTp_FinishReception_TpTxSmStateHandler_RM_TX_RECEPTION_TRANSMISSION_ACTIVE(PduR_RmSrcRomIterType rmSrcIdx, Std_ReturnType result)
{
  PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfRmSrcRom(rmSrcIdx);
  PduR_FmFifoRamIterType fmFifoRamIdx = PduR_GetFmFifoRomIdxOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx), memIdx);

  PduR_SetTpTxSmStateOfFmFifoRam(fmFifoRamIdx, PDUR_RM_TX_RECEPTION_FINISHED_TRANSMISSION_ACTIVE_TPTXSMSTATEOFFMFIFORAM, memIdx);       /* SBSW_PDUR_CSL01 */

  if(result != E_OK)
  {
    PduR_RmTp_CancelTransmitOnDestinations(rmSrcIdx);
  }
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_FinishReception_TpTxSmStateHandler_RM_TX_TRANSMISSION_FINISHED
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmTp_FinishReception_TpTxSmStateHandler_RM_TX_TRANSMISSION_FINISHED(PduR_RmSrcRomIterType rmSrcIdx, Std_ReturnType result)
{
  PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfRmSrcRom(rmSrcIdx);
  PduR_FmFifoRamIterType fmFifoRomIdx = PduR_GetFmFifoRomIdxOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx), memIdx);

  PduR_Fm_ReleaseFifoElement(PduR_Fm_GetFmFifoElementRamReadIdxOfFmFifoRamSafe(fmFifoRomIdx, memIdx), memIdx);
  PduR_SetTpTxSmStateOfFmFifoRam(fmFifoRomIdx, PDUR_RM_TX_IDLE_TPTXSMSTATEOFFMFIFORAM, memIdx); /* SBSW_PDUR_CSL01 */
  PduR_RmTp_ActivateNext(fmFifoRomIdx, memIdx);

  PDUR_DUMMY_STATEMENT(result); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}
#endif

#if ((PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON) && (PDUR_RPGROM == STD_ON))
/**********************************************************************************************************************
 * PduR_RmTp_TpDisableRouting_TpTxSmStateHandler
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_RmTp_TpDisableRouting_TpTxSmStateHandler(PduR_RmDestRomIterType rmDestRomIdx)
{
  PduR_RmTp_TxInst_CancelTransmit(PduR_GetRmGDestRomIdxOfRmDestRom(rmDestRomIdx));
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_CancelReceive_TpRxSmStateHandler
 *********************************************************************************************************************/
  /*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmTp_CancelReceive_TpRxSmStateHandler(PduR_RmSrcRomIterType rmSrcIdx)
{
  switch (PduR_GetTpRxSmStateOfRmBufferedTpPropertiesRam(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx), PduR_GetPartitionIndexOfCslOfRmSrcRom(rmSrcIdx)))
  {
    case PDUR_RM_RX_IDLE_TPRXSMSTATEOFRMBUFFEREDTPPROPERTIESRAM: /* COV_PDUR_FATAL_ERROR */
      PduR_RmTp_CancelReceive_TpRxSmStateHandler_FatalError(rmSrcIdx);
      break;

    case PDUR_RM_RX_ACTIVE_TPRXSMSTATEOFRMBUFFEREDTPPROPERTIESRAM:
      PduR_RmTp_CancelReceive_TpRxSmStateHandler_RM_RX_ACTIVE(rmSrcIdx);
      break;

    case PDUR_RM_RX_ABORTED_TPRXSMSTATEOFRMBUFFEREDTPPROPERTIESRAM: /* COV_PDUR_FATAL_ERROR */
      PduR_RmTp_CancelReceive_TpRxSmStateHandler_FatalError(rmSrcIdx);
      break;

    default: /* COV_PDUR_MISRA */
      /* If state is out-of-bounds: do nothing. */
      break;
  }
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_CancelReceive_TpRxSmStateHandler_RM_RX_ACTIVE
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmTp_CancelReceive_TpRxSmStateHandler_RM_RX_ACTIVE(PduR_RmSrcRomIterType rmSrcIdx)
{
  PduR_SetTpRxSmStateOfRmBufferedTpPropertiesRam(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx), PDUR_RM_RX_ABORTED_TPRXSMSTATEOFRMBUFFEREDTPPROPERTIESRAM, PduR_GetPartitionIndexOfCslOfRmSrcRom(rmSrcIdx));  /* SBSW_PDUR_CSL03 */
  PDUR_DUMMY_STATEMENT(rmSrcIdx);       /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_CancelReceive_TpRxSmStateHandler_FatalError
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmTp_CancelReceive_TpRxSmStateHandler_FatalError(PduR_RmSrcRomIterType rmSrcIdx)     /* COV_PDUR_FATAL_ERROR */
{
  PduR_Det_ReportError(PDUR_RXSM_TPCANCELRECEIVE_FATALERROR, PDUR_E_FATAL);
  PDUR_DUMMY_STATEMENT(rmSrcIdx);       /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_ActivateNext
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmTp_ActivateNext(PduR_FmFifoRamIterType fmFifoRamIdx, PduR_MemIdxType memIdx)
{
  PduR_FmFifoElementRamIterType fmFifoElementRamReadIdx;
  while(PduR_Fm_Peek(fmFifoRamIdx, &fmFifoElementRamReadIdx, memIdx) == E_OK)      /* SBSW_PDUR_STACK_VARIABLE */
  {
    PduR_RmSrcRomIterType rmSrcIdx;
    PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx;

    if(PduR_RmTp_GetRmSrcRomIdxOfOldestFmFifoElementSafe(fmFifoRamIdx, &rmSrcIdx, memIdx) == E_NOT_OK) /* SBSW_PDUR_STACK_VARIABLE */ /* COV_PDUR_ROBUSTNESS */
    {
      /* If the read handle id is erroneous and does not belong to this queue: free this element and look for next  */
      PduR_Fm_ReleaseFifoElement(fmFifoElementRamReadIdx, memIdx);
      continue;
    }

    /* Is Rx already finished? */
    if((PduR_RmTp_GetCurrentlyWrittenFmFifoElementRamIdxByRmSrcIdx(rmSrcIdx, &fmFifoElementRamWriteIdx) != E_OK) || (fmFifoElementRamReadIdx != fmFifoElementRamWriteIdx)) /* SBSW_PDUR_STACK_VARIABLE */
    {
      PduR_SetTpTxSmStateOfFmFifoRam(fmFifoRamIdx, PDUR_RM_TX_RECEPTION_FINISHED_TRANSMISSION_ACTIVE_TPTXSMSTATEOFFMFIFORAM, memIdx); /* SBSW_PDUR_CSL03 */

      if(PduR_RmTp_TriggerTransmissionOfDestinations(rmSrcIdx) != E_OK) /* COV_PDUR_ONLY_DEFERRED_TP_QUEUED_ROUTINGS */
      {
        PduR_SetTpTxSmStateOfFmFifoRam(fmFifoRamIdx, PDUR_RM_TX_IDLE_TPTXSMSTATEOFFMFIFORAM, memIdx); /* SBSW_PDUR_CSL03 */
      }

    }
    else
    {
      (void) PduR_RmTp_CheckReady2Transmit_TpTxSmStateHandler_RM_TX_IDLE_OR_RM_TX_RECEPTION_ACTIVE(rmSrcIdx);
    }

    break;
  }
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_GetCurrentlyWrittenFmFifoElementRamIdxByRmSrcIdx
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_GetCurrentlyWrittenFmFifoElementRamIdxByRmSrcIdx(PduR_RmSrcRomIterType rmSrcIdx, P2VAR(PduR_FmFifoElementRamIterType, AUTOMATIC, PDUR_APPL_DATA) fmFifoElementRamIdx)
{
  Std_ReturnType retVal;
  PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfRmSrcRom(rmSrcIdx);
  PduR_FmFifoElementRamIterType readFmFifoElementRamIdx = PduR_RmTp_GetFmFifoElementRamIdxOfRmBufferedTpPropertiesSafe(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx), memIdx);

  if(readFmFifoElementRamIdx == PDUR_NO_FMFIFOELEMENTRAMIDXOFRMBUFFEREDTPPROPERTIESRAM)
  {
    retVal = E_NOT_OK;
  }
  else
  {
    *fmFifoElementRamIdx = readFmFifoElementRamIdx; /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
    retVal = E_OK;
  }

  return retVal;
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_GetCurrentlyUsedBmTxBufferRamIdxByRmSrcIdx
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_GetCurrentlyUsedBmTxBufferRamIdxByRmSrcIdx(PduR_RmSrcRomIterType rmSrcIdx, P2VAR(PduR_BmTxBufferRomIterType, AUTOMATIC, PDUR_APPL_DATA) bmTxBufferRomIdx)
{
  Std_ReturnType retVal;
  PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx;

  if(PduR_RmTp_GetCurrentlyWrittenFmFifoElementRamIdxByRmSrcIdx(rmSrcIdx, &fmFifoElementRamWriteIdx) == E_OK) /* SBSW_PDUR_STACK_VARIABLE */ /* COV_PDUR_ROBUSTNESS */
  {
    retVal = PduR_Fm_GetCurrentlyUsedBmTxBufferRomIdxByFmFifoElementIdx(fmFifoElementRamWriteIdx, bmTxBufferRomIdx, PduR_GetPartitionIndexOfCslOfRmSrcRom(rmSrcIdx)); /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
  }
  else
  {
    retVal = E_NOT_OK;
  }

  return retVal;
}
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_GetFmFifoElementRamIdxOfRmBufferedTpPropertiesSafe
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *   -
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(PduR_FmFifoElementRamIdxOfRmBufferedTpPropertiesRamType, PDUR_CODE) PduR_RmTp_GetFmFifoElementRamIdxOfRmBufferedTpPropertiesSafe(PduR_RmBufferedTpPropertiesRomIdxOfRmSrcRomType bufferedTpPropertiesRomIdx, PduR_MemIdxType memIdx)
{
  PduR_FmFifoElementRamIdxOfRmBufferedTpPropertiesRamType fmFifoElementRamIdx = PduR_GetFmFifoElementRamIdxOfRmBufferedTpPropertiesRam(bufferedTpPropertiesRomIdx, memIdx);

# if (PDUR_EXTENDED_ERROR_CHECKS == STD_ON)
  PduR_FmFifoRamIterType fmFifoRomIdx = PduR_GetFmFifoRomIdxOfRmBufferedTpPropertiesRom(bufferedTpPropertiesRomIdx, memIdx);
  PduR_FmFifoElementRamStartIdxOfFmFifoRomType startIdx = PduR_GetFmFifoElementRamStartIdxOfFmFifoRom(fmFifoRomIdx, memIdx);
  PduR_FmFifoElementRamEndIdxOfFmFifoRomType   endIdx   = PduR_GetFmFifoElementRamEndIdxOfFmFifoRom(fmFifoRomIdx, memIdx);

  if((fmFifoElementRamIdx >= endIdx) && (fmFifoElementRamIdx != PDUR_NO_FMFIFOELEMENTRAMIDXOFRMBUFFEREDTPPROPERTIESRAM)) /* COV_PDUR_EXTENDED_ERROR_CHECKS */
  {
    fmFifoElementRamIdx = endIdx - 1u;
    PduR_ReportRuntimeDetError(PDUR_FCT_GETCURRENTLYWRITTENFIFOELEMENT, PDUR_E_IDXOUTOFBOUNDS);
  }
  if((fmFifoElementRamIdx < startIdx) && (fmFifoElementRamIdx != PDUR_NO_FMFIFOELEMENTRAMIDXOFRMBUFFEREDTPPROPERTIESRAM))  /* COV_PDUR_EXTENDED_ERROR_CHECKS */ /* PRQA S 2995, 2996 */ /* MD_PduR_2995_2996 */
  {
    fmFifoElementRamIdx = startIdx;
    PduR_ReportRuntimeDetError(PDUR_FCT_GETCURRENTLYWRITTENFIFOELEMENT, PDUR_E_IDXOUTOFBOUNDS);
  }
# endif

  return fmFifoElementRamIdx;
}
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_GetRmSrcRomIdxOfOldestFmFifoElementSafe
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *   -
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_GetRmSrcRomIdxOfOldestFmFifoElementSafe(PduR_FmFifoRomIterType fmFifoRomIdx, P2VAR(PduR_RmSrcRomIterType, AUTOMATIC, PDUR_APPL_DATA) rmSrcRomIdx, PduR_MemIdxType memIdx)
{
  Std_ReturnType retVal = E_NOT_OK;
  PduR_RmDestRomIterType rmDestRomIdx;

  if(PduR_Fm_GetRmDestRomIdxOfFmFifoElementRamSafe(PduR_Fm_GetFmFifoElementRamReadIdxOfFmFifoRamSafe(fmFifoRomIdx, memIdx), &rmDestRomIdx, memIdx) == E_OK) /* SBSW_PDUR_STACK_VARIABLE */ /* COV_PDUR_ROBUSTNESS */
  {
    PduR_RmSrcRomIterType readRmSrcRomIdx = PduR_GetRmSrcRomIdxOfRmDestRom(rmDestRomIdx);

# if (PDUR_EXTENDED_ERROR_CHECKS == STD_ON)
    if(PduR_IsRmBufferedTpPropertiesRomUsedOfRmSrcRom(readRmSrcRomIdx)) /* COV_PDUR_EXTENDED_ERROR_CHECKS */
    {

      PduR_FmFifoRomIterType supposedfmFifoRomIdx = PduR_GetFmFifoRomIdxOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(readRmSrcRomIdx), PduR_GetPartitionIndexOfCslOfRmSrcRom(readRmSrcRomIdx));

      if(supposedfmFifoRomIdx == fmFifoRomIdx) /* COV_PDUR_EXTENDED_ERROR_CHECKS */
      {
        *rmSrcRomIdx = readRmSrcRomIdx; /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
        retVal = E_OK;
      }
    }
# else
    *rmSrcRomIdx = readRmSrcRomIdx; /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
    retVal = E_OK;
# endif
  }

  return retVal;
}
#endif

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h" /* PRQA S 5087 */   /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  END OF FILE: PduR_RmTp.c
 *********************************************************************************************************************/
