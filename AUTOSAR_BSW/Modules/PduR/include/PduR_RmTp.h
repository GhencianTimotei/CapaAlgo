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
 *         File:  PduR_RmTp.h
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
#if !defined (PDUR_RMTP_H)
# define PDUR_RMTP_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "PduR_Types.h"
# include "PduR_Cfg.h"
# include "PduR_Lcfg.h"

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
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define PDUR_START_SEC_CODE
# include "PduR_MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

# if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_Init
 *********************************************************************************************************************/
/*! \brief       This function initializes the PDUR transport protocol routings.
 *  \details     -
 *  \param[in]   memIdx  memory section index
 *  \pre         PduR_InitMemory() has been executed, if the startup code does not initialise variables.
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \note        The function must be called on task level and has not to be interrupted
 *               by other administrative function calls.
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_RmTp_Init(PduR_MemIdxType memIdx);
# endif

# if((PDUR_EXISTS_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON))
/**********************************************************************************************************************
  PduR_RmTp_MultipleSourceHandler_CopyTxData
**********************************************************************************************************************/
/*! \brief       This function is called by the PduR GwTp multiple times to query the transmit data of an I-PDU segment.
 *  \details     Each call to this function copies the next part of the transmit.
 *  \param[in]   rmGDestRomIdx            ID of the transmitted GwIf I-PDU
 *  \param[in]   info                        Pointer to the destination buffer and the number of bytes to copy.
 *                                          In case of gateway the PDU Router module will copy otherwise the source upper layer
 *                                          module will copy the data. If not enough transmit data is available, no data is copied.
 *
 *                                          A copy size of 0 can be used to indicate state changes in the retry parameter.
 *  \param[in]   retry                       not supported
 *  \param[out]  availableDataPtr           Indicates the remaining number of bytes that are available in the PduR Tx buffer.
 *                                          AvailableTxDataCntPtr can be used by TP modules that support dynamic payload lengths
 *                                          (e.g. Iso FrTp) to determine the size of the following CFs.
 *  \return      BufReq_ReturnType
 *               BUFREQ_OK                   The data has been copied to the transmit buffer successfully.
 *               BUFREQ_E_NOT_OK             PduR_Init() has not been called
 *                                          or the GwTpTxPduId is not valid
 *                                          or the GwTpTxPduId is not forwarded in this identity
 *                                          or the info is not valid
 *                                          or the request was not accepted by the upper layer and no data has been copied.
 *               BUFREQ_E_BUSY               The request cannot be processed because the TX data is not available
 *                                           and no data has been copied. The TP layer might retry later the copy process.
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
**********************************************************************************************************************/
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_MultipleSourceHandler_CopyTxData(PduR_RmGDestRomIdxOfTxTp2SrcType rmGDestRomIdx, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info,
                                                                              P2VAR(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA) retry, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) availableDataPtr);
# endif

# if((PDUR_EXISTS_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON))
/**********************************************************************************************************************
  PduR_RmTp_MultipleSourceHandler_TpTxConfirmation
**********************************************************************************************************************/
/*! \brief        The function is called to confirm or abort a transport protocol I-PDU routing.
 *  \details      The PDU Router evaluates the Gw I-PDU handle and performs appropriate handle and port conversion.
 *                The call is routed to an upper Tp module or to the gateway depending on the pending Confirmation.
 *   \param[in]   rmGDestRomIdx          ID of the transmitted GwIf I-PDU
 *   \param[out]  result    not used, but expected due to function pointer table type
 *   \pre         -
 *   \context     TASK|ISR1|ISR2
 *   \reentrant   TRUE
 *   \synchronous TRUE
 **********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_RmTp_MultipleSourceHandler_TpTxConfirmation(PduR_RmGDestRomIdxOfTxTp2SrcType rmGDestRomIdx, Std_ReturnType result);
# endif

# if((PDUR_TPCANCELTRANSMITSUPPORTEDOFMMROM == STD_ON) && (PDUR_EXISTS_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON))
/**********************************************************************************************************************
   PduR_RmTp_MultipleSourceHandler_CancelTransmit
**********************************************************************************************************************/
/*! \brief        The function is called by the PduR to cancel the transmission on the destination buses in case of a
 *                FanIn Transport Protocol Routing.
 *   \details     The PDU Router evaluates the Gw I-PDU handle and performs appropriate handle and port conversion.
 *                The call is routed to multiple TP module using the appropriate I-PDU handle of the destination layer.
 *   \param[in]   rmDestRomIdx             ID of the transmitted GwTp I-PDU.
 *   \pre         -
 *   \context     TASK|ISR1|ISR2
 *   \reentrant   TRUE
 *   \synchronous TRUE
**********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_MultipleSourceHandler_CancelTransmit(PduR_RmDestRomIterType rmDestRomIdx);
# endif

# if (PDUR_HASTPBUFFERULSOURCEOFGENERALPROPERTIESROM == STD_ON)
/**********************************************************************************************************************
  PduR_RmTp_UpStartOfReception
**********************************************************************************************************************/
/*! \brief       Wrapper function for buffered transmit.
 *  \details     -
 *  \param[in]   rmSrcIdx          Routing Manager source Id
 *  \param[in]   info              Pointer to the buffer (SduDataPtr) contains MetaData if this feature is enabled
 *  \return      Std_ReturnType
 *                E_OK              Connection has been accepted. RxBufferSizePtr indicates the available receive buffer.
 *                E_NOT_OK          PduR_Init() has not been called
 *                                  or the GwTpRxPduId is not valid
 *                                  or the GwTpRxPduId is not forwarded in this identity
 *                                  or the info is not valid
 *                                  or the request was not accepted by the upper layer.
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       SPEC-1096, SPEC-2020151
***********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_UpStartOfReception(PduR_RmSrcRomIterType rmSrcIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
# endif

# if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
  PduR_RmTp_StartOfReception
**********************************************************************************************************************/
/*! \brief       This function will be called by the GwTp at the start of receiving an I-PDU.
 *  \details     The I-PDU might be fragmented into multiple N-PDUs
 *               (FF with one or more following CFs) or might consist of a single N-PDU (SF).
 *  \param[in]   rmSrcIdx          Routing Manager source Id
 *  \param[in]   info              Pointer to the buffer (SduDataPtr) contains MetaData if this feature is enabled
 *  \param[in]   TpSduLength       Length of the entire GwTp TP SDU which will be received
 *  \param[out]  bufferSizePtr     Pointer to the receive buffer in the receiving module.
 *                                   This parameter will be used to compute Block Size (BS) in the transport protocol module.
 *  \return      BufReq_ReturnType
 *               BUFREQ_OK         Connection has been accepted. RxBufferSizePtr indicates the available receive buffer.
 *               BUFREQ_E_NOT_OK   PduR_Init() has not been called
 *                                  or the GwTpRxPduId is not valid
 *                                  or the GwTpRxPduId is not forwarded in this identity
 *                                  or the info is not valid
 *                                  or the request was not accepted by the upper layer.
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       SPEC-1096, SPEC-2020151
***********************************************************************************************************************/
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_StartOfReception(PduR_RmSrcRomIterType rmSrcIdx,
                                                              P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info,
                                                              PduLengthType TpSduLength, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr);
# endif

# if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
  PduR_RmTp_CopyRxData
**********************************************************************************************************************/
/*! \brief     This function is called by the PduR if data has to be to copied to the receiving module.
 *  \details   Several calls may be made during one transportation of an I-PDU.
 *  \param[in]   rmSrcIdx         Routing Manager source Id
 *  \param[in]   info               Pointer to the buffer (SduDataPtr) and its length (SduLength)
 *                                containing the data to be copied by PDU Router module in case of gateway
 *                                or upper layer module in case of reception.
 *  \param[out]  bufferSizePtr     Available receive buffer after data has been copied.
 *  \return    BufReq_ReturnType
 *             BUFREQ_OK         Buffer request accomplished successful.
 *             BUFREQ_E_NOT_OK   PduR_Init() has not been called
 *                                  or the GwTpRxPduId is not valid
 *                                  or the GwTpRxPduId is not forwarded in this identity
 *                                  or the info is not valid
 *                                  or the request was not accepted by the upper layer.
 *             BUFREQ_E_BUSY     Currently no buffer of the requested size is available.
 *                               It's up the requester to retry request for a certain time.
 *                               The request was not accepted by the upper layer.
 *             BUFREQ_E_OVFL     The upper TP module is not able to receive the number of bytes.
 *                               The request was not accepted by the upper layer.
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       SPEC-1096, SPEC-2020151
**********************************************************************************************************************/
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_CopyRxData(PduR_RmSrcRomIdxOfRxTp2DestType rmSrcIdx, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info,
                                                        P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr);
# endif

# if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
  PduR_RmTp_TpRxIndication
**********************************************************************************************************************/
/*! \brief      The function is called by the PduR GwTp to indicate the complete reception of a GwTp SDU
 *              or to report an error that occurred during reception.
 *  \details    -
 *              The PDU Router evaluates the Gw I-PDU handle and performs appropriate handle and port conversion.
 *              The call is routed to an upper TP module using the appropriate I-PDU handle of the destination layer.
 *  \param[in]      rmSrcIdx                    Routing Manager source Id
 *  \param[out] result                          Result of the TP reception.\n
 *              E_OK                            The TP reception has been completed successfully.\n
 *              E_NOT_OK                        The PDU Router is in the PDUR_UNINIT state\n
 *                                              or the id is not valid\n
 *                                              or the id is not forwarded in this identity\n
 *                                              or the request was not accepted by the destination upper layer.\n
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       SPEC-1096, SPEC-2020151
***********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_RmTp_TpRxIndication(PduR_RmSrcRomIdxOfRxTp2DestType rmSrcIdx, Std_ReturnType result);
# endif

# if(PDUR_EXISTS_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_Transmit_MultiDest
 *********************************************************************************************************************/
/*!
 * \brief    The function calls the Transmit function for every destination
 * \details     -
 * \param[in]   rmSrcIdx            internal RmSrcRom index
 * \param[in]   info                Pointer to the data to be transmitted
 * \return      Std_ReturnType
 *               E_OK              Transmit was executed successfully by all the destination modules.
 *               E_NOT_OK          Transmit was rejected by the destination module.
 * \pre         -
 * \context     TASK|ISR1|ISR2
 * \reentrant   TRUE
 * \synchronous TRUE
**********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_Transmit_MultiDest(PduR_RmSrcRomIterType rmSrcIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
# endif

# if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_TpDisableRouting_TpTxSmStateHandler
 *********************************************************************************************************************/
/*! \brief       Disables the currently active Pdu in the FIFO. Cancels transmit and receive if necessary.
 *  \details     -
 *  \param[in]   rmDestRomIdx    Id of the global destination Pdu
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_RmTp_TpDisableRouting_TpTxSmStateHandler(PduR_RmDestRomIterType rmDestRomIdx);
# endif

# if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_FinishTransmission_TpTxSmStateHandler
 *********************************************************************************************************************/
/*! \brief       Helper function which finishes the transmission in the corresponding queue depending on the TpTxSm state.
 *  \details     -
 *  \param[in]   memIdx  memory section index
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_RmTp_FinishTransmission_TpTxSmStateHandler(PduR_FmFifoRomIterType fmFifoRomIdx, Std_ReturnType result, PduR_MemIdxType memIdx);
# endif

# define PDUR_STOP_SEC_CODE
# include "PduR_MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */
#endif /* PDUR_RMTP_H */
/**********************************************************************************************************************
 *  END OF FILE: PduR_RmTp.h
 *********************************************************************************************************************/
