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
/*!        \file  Com_LLIf.h
 *        \brief  MICROSAR Communication header file
 *
 *      \details  This is the implementation of the MICROSAR Communication module.
 *                The basic software module is based on the AUTOSAR Communication specification.
 *
 *********************************************************************************************************************/
#if !defined (COM_LLIF_H)
# define COM_LLIF_H

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
# include "Com_Lcfg.h"

/**********************************************************************************************************************
  GLOBAL CONSTANT MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL FUNCTION MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL DATA PROTOTYPES (Com)
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/
# define COM_START_SEC_CODE
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_MemMap */

# if (COM_TRIGGER_TRANSMIT_API == STD_ON)
/**********************************************************************************************************************
  Com_TriggerTransmit_Process
**********************************************************************************************************************/
/*! \brief            Within this function, the upper layer module
                      (called module) shall copy its data into the buffer provided by PduInfoPtr->SduDataPtr and
                      update the length of the actual copied data in PduInfoPtr->SduLength.
    \details          -
    \pre              -
    \param[in]        TxPduId      ID of the SDU that is requested to be transmitted.
    \param[in,out]    PduInfoPtr   Contains a pointer to a buffer (SduDataPtr) to where the SDU
                                 data shall be copied, and the available buffer size in SduLengh.
                                 On return, the service will indicate the length of the copied SDU
                                 data in SduLength.
    \return           E_OK       SDU has been copied and SduLength indicates the number of copied bytes.
    \return           E_NOT_OK   No data has been copied, because
                                 Com is not initialized
                                 or TxPduId is not valid
                                 or PduInfoPtr is NULL_PTR
                                 or SduDataPtr is NULL_PTR
                                 or SduLength is to small.
    \trace            CREQ-103166
    \trace            SPEC-2737060
    \context          TASK|ISR2
    \synchronous      TRUE
    \reentrant        TRUE, for different handles
**********************************************************************************************************************/
FUNC(Std_ReturnType, COM_CODE) Com_TriggerTransmit_Process(PduIdType TxPduId, P2VAR(PduInfoType, AUTOMATIC, COM_APPL_VAR) PduInfoPtr);
# endif

# if((COM_TXTPINFOUSEDOFTXPDUINFO == STD_ON) || (COM_TX_CONFIRMATION_API == STD_ON))
/**********************************************************************************************************************
  Com_TxConfirmation_Process
**********************************************************************************************************************/
/*! \brief        The lower layer communication interface module confirms the transmission of an I-PDU.
    \details      -
    \pre          -
    \param[in]    TxPduId       ID of the I-PDU that has been transmitted.
    \trace        SPEC-2736844
    \context      TASK|ISR2
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxConfirmation_Process(PduIdType TxPduId);
# endif

# if (COM_TXTPINFOUSEDOFTXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_ResetTxTpConnection
**********************************************************************************************************************/
/*! \brief        This function resets the TxTP state machine
    \details      -
    \pre          -
    \param[in]    PduId    ID of I-PDU whose TP connection shall be reset.
    \context      TASK|ISR2
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_ResetTxTpConnection(PduIdType PduId);
# endif

# if (COM_TXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_TxLLIf_Transmit
**********************************************************************************************************************/
/*! \brief        This function wraps the function PduR_ComTransmit. The I-PDU is transmitted immediate.
    \details      -
    \pre          -
    \param[in]    ComTxPduId    ID of I-PDU to be transmitted.
    \return       Std_ReturnType
                    E_OK          Transmit request has been accepted
                    E_NOT_OK      E_NOT_OK Transmit request has not been accepted
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
    \trace        SPEC-2736903, SPEC-2736898, SPEC-2736899, SPEC-2737062
    \context      TASK
    \warning      This function is for internal purpose only.
**********************************************************************************************************************/
FUNC(Std_ReturnType, COM_CODE) Com_TxLLIf_Transmit(PduIdType ComTxPduId);
# endif

# if ((COM_TXTPINFOUSEDOFTXPDUINFO == STD_ON) && (COM_CANCELLATIONSUPPORTOFTXPDUINFO == STD_ON))
/**********************************************************************************************************************
  Com_TxLLIf_CancelTransmit
**********************************************************************************************************************/
/*! \brief        This function wraps the call of PduR_ComCancelTransmit(), if configured, for the given Tx I-PDU.
                  If required, the ID is converted to the PduR handle space.
    \details      -
    \pre          -
    \param[in]    ComTxPduId    ID of I-PDU to be transmitted.
    \context      TASK
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxLLIf_CancelTransmit(PduIdType ComTxPduId);
# endif

# if (COM_TXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_TxLLIf_InitTxIpdu
**********************************************************************************************************************/
/*! \brief        This function initializes a tx I-PDU in Com_TxLLIf.
    \details      -
    \pre          -
    \param[in]    ComPduId Handle of the I-PDU.
    \context      TASK|ISR2
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxLLIf_InitTxIpdu(Com_TxPduInfoIterType ComPduId);
# endif

# if (COM_RXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxIndication_Processing
**********************************************************************************************************************/
/*! \brief        This function is called by Com_RxIndication_Processing after an I-PDU has been received.
    \details      -
    \pre          -
    \param[in]    RxPduId      ID of I-PDU that has been received. Identifies the data that has been received.
                               Range: 0..(maximum number of I-PDU IDs received by AUTOSAR COM) - 1
    \param[in]    PduInfoPtr   Payload information of the received I-PDU (pointer to data and data length).
    \return       TRUE         If Pdu was processed
                  FALSE        otherwise
    \trace        SPEC-2736845, SPEC-2736846
    \trace        CREQ-103160
    \context      TASK|ISR2
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
**********************************************************************************************************************/
FUNC(boolean, COM_CODE) Com_RxIndication_Processing(PduIdType RxPduId, P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr);
# endif

# if (COM_RXTPINFOUSEDOFRXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_TpRxIndication_Processing
**********************************************************************************************************************/
/*! \brief    This function is called by Com_TpRxIndication after a TP I-PDU has been received.
    \details  -
    \pre      -
    \param[in]    PduId      ID of I-PDU that has been received. Identifies the data that has been received.
                             Range: 0..(maximum number of I-PDU IDs received by AUTOSAR COM) - 1
    \param[in]    Result     Indicates whether the message was received successfully.
    \context  TASK|ISR2
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TpRxIndication_Processing(PduIdType PduId, Std_ReturnType Result);
# endif

# if (COM_RXTPINFOUSEDOFRXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_ResetRxTpConnection
**********************************************************************************************************************/
/*! \brief        This function is called to reset the Rx TP connection.
    \details      -
    \pre          -
    \param[in]    PduId      ID of I-PDU whose TP connection shall be reset.
    \context      TASK|ISR2
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_ResetRxTpConnection(PduIdType PduId);
# endif

# if (COM_RXTPINFOUSEDOFRXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_CopyRxData_Processing
**********************************************************************************************************************/
/*! \brief        This function is called by the lower layer to hand a received TP segment to Com.
                  The Com copies the received segment in his internal tp buffer.
    \details      -
    \pre          -
    \param[in]    PduId              ID of AUTOSAR COM I-PDU that has been received. Identifies the data that has been received.
    \param[in]    PduInfoPointer     Payload information of the received TP segment (pointer to data and data length).
    \param[out]   RxBufferSizePtr    The Com returns in this value the remaining TP buffer size to the lower layer.
    \return       BufReq_ReturnType  BUFREQ_OK:       Connection has been accepted.
                                                      RxBufferSizePtr indicates the available receive buffer.
                                     BUFREQ_E_NOT_OK: Connection has been rejected.
                                                      RxBufferSizePtr remains unchanged.
    \context      TASK|ISR2
    \synchronous  TRUE
    \reentrant    TRUE, for different Handles
**********************************************************************************************************************/
FUNC(BufReq_ReturnType, COM_CODE) Com_CopyRxData_Processing(PduIdType PduId, CONSTP2VAR(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPointer,
                                                            P2VAR(PduLengthType, AUTOMATIC, COM_APPL_VAR) RxBufferSizePtr);
# endif

# define COM_STOP_SEC_CODE
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_MemMap */

#endif /* COM_LLIF_H */

/**********************************************************************************************************************
  END OF FILE: Com_LLIf.h
**********************************************************************************************************************/
