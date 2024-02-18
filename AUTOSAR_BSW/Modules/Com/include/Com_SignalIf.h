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
/*!        \file  Com_SignalIf.h
 *        \brief  MICROSAR Communication header file
 *
 *      \details  This is the implementation of the MICROSAR Communication module.
 *                The basic software module is based on the AUTOSAR Communication specification.
 *
 *********************************************************************************************************************/
#if !defined (COM_SIGNALIF_H)
# define COM_SIGNALIF_H

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

# if ((COM_RXACCESSINFO == STD_ON) && ((COM_BUFFERUSEDOFRXACCESSINFO == STD_ON) || (COM_RXSIGBUFFERARRAYBASEDBUFFERUSEDOFRXACCESSINFO == STD_ON)))
/**********************************************************************************************************************
  Com_ReceiveSignal_GetRxSigBuffer
**********************************************************************************************************************/
/*! \brief        The function Com_ReceiveSignal_GetRxSigBuffer updates the signal data referenced by SignalDataPtr
                  with the data in the signal object identified by SignalId.
    \details      -
    \pre          -
    \param[in]    idxRxAccessInfo             Id of signal or group signal to be received.
    \param[out]   SignalDataPtr               Reference to the signal data in which to store the received data.
    \context      TASK|ISR2
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_ReceiveSignal_GetRxSigBuffer(Com_SignalIdType idxRxAccessInfo, P2VAR(void, AUTOMATIC, COM_APPL_VAR) SignalDataPtr);
# endif

# if (COM_SHDBUFFERREQUIREDOFRXSIGGRPINFO == STD_ON)
/**********************************************************************************************************************
  Com_ReadSignalGroupData
**********************************************************************************************************************/
/*! \brief        The function Com_ReadSignalGroupData copies the received signal group to the shadow buffer.
    \details      -
    \pre          -
    \param[in]    SignalGroupId               Id of signal group to be received.
    \context      TASK|ISR2
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_ReadSignalGroupData(Com_SignalGroupIdType SignalGroupId);
# endif

# if (COM_TXSIGGRPINFO == STD_ON)
/**********************************************************************************************************************
  Com_SendSignalGroup_Processing
**********************************************************************************************************************/
/*! \brief        The service Com_SendSignalGroup_Processing copies the content of the associated shadow buffer to
                  the associated I-PDU buffer.
                  Prior to this call, all group signals should be updated in the shadow buffer
                  by the call of Com_SendSignal.
    \details      -
    \pre          -
    \param[in]    idxTxSigGrpInfo    ID of signal group to be send.
    \param[in]    ShadowBufferPtr    Pointer to Shadow Buffer
    \return       uint8
                    E_OK                        service has been accepted
                    COM_SERVICE_NOT_AVAILABLE   corresponding I-PDU group was stopped
                                                (or service failed due to development error)
    \context      TASK|ISR2
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
**********************************************************************************************************************/
FUNC(uint8, COM_CODE) Com_SendSignalGroup_Processing(Com_SignalIdType idxTxSigGrpInfo, P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) ShadowBufferPtr);
# endif

# if (COM_TXSIGINFO == STD_ON)
/**********************************************************************************************************************
  Com_SendSignal_Processing
**********************************************************************************************************************/
/*! \brief        The function Com_SendSignal_Processing updates the signal or group signal object
                  with the signal data referenced by the SignalDataPtr parameter. The Length parameter is evaluated for
                  dynamic length signals.
    \details      -
    \pre          -
    \param[in]    SignalDataPtr Reference to the signal data to be transmitted.
    \param[in]    Length        Length of the dynamic length signal.
    \param[in]    idxTxSigInfo  Index of signal or group signal to be sent.
    \return       uint8
                    E_OK                        service has been accepted
                    COM_SERVICE_NOT_AVAILABLE   corresponding I-PDU group was stopped
                                                (or service failed due to development error)
                    COM_BUSY                    in case the TP-Buffer is locked for large data types handling
    \context      TASK|ISR2
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
    \trace        SPEC-2736898, SPEC-2736899
    \warning      If the method is used on a microcontroller like the Tms320 DSP and the datatype uint8 is unsigned short
                  the 8 MSB bits of the variable shall never be set.
                  If the method is used on a microcontroller like the S12X and the datatype is uint16, sint16, uint32
                  or sint32 the SignalDataPtr must be word aligned.
**********************************************************************************************************************/
FUNC(uint8, COM_CODE) Com_SendSignal_Processing(Com_TxSigInfoIterType idxTxSigInfo, P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr, uint16 Length);
# endif

# if (COM_ARRAYACCESSUSEDOFTXSIGGRPINFO == STD_ON)
/**********************************************************************************************************************
  Com_SendSignalGroupArray_Processing
**********************************************************************************************************************/
/*! \brief        The service Com_SendSignalGroupArray copies the content of the provided SignalGroupArrayPtr to the
 *                associated I-PDU. The provided data shall correspond to the array representation of the signal group.
    \details      -
    \param[in]    SignalGroupId               Id of signal group to be sent.
    \param[in]    SignalGroupArrayPtr         Reference to the signal group array.
    \return       uint8
                    E_OK                        service has been accepted
                    COM_SERVICE_NOT_AVAILABLE   corresponding I-PDU group was stopped (or service failed due to development
                                                error)
                    COM_BUSY                    in case the TP-Buffer is locked for large data types handling
    \context      TASK|ISR2
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
    \pre          The configuration switch ComEnableSignalGroupArrayApi has to be enabled.
**********************************************************************************************************************/
FUNC(uint8, COM_CODE) Com_SendSignalGroupArray_Processing(Com_SignalGroupIdType SignalGroupId, P2CONST(uint8, AUTOMATIC, COM_APPL_VAR) SignalGroupArrayPtr);
# endif

# if ((COM_INVVALUEUSEDOFTXSIGINFO == STD_ON) || (COM_CONSTVALUEARRAYBASEDINVVALUEUSEDOFTXSIGINFO == STD_ON))
/**********************************************************************************************************************
  Com_InvalidateSignal_SendSignal
**********************************************************************************************************************/
/*! \brief        This function calls Com_SendSignal according to the configured ApplType.
    \details      -
    \pre          -
    \param[in]    idxTxSigInfo ID of signal or group signal to be invalidated.
    \return       uint8
                    E_OK                        service has been accepted
                    COM_SERVICE_NOT_AVAILABLE   corresponding I-PDU group was stopped
                                                (or service failed due to development error)
    \context      TASK|ISR2
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
**********************************************************************************************************************/
FUNC(uint8, COM_CODE) Com_InvalidateSignal_SendSignal(Com_TxSigInfoIterType idxTxSigInfo);
# endif

# define COM_STOP_SEC_CODE
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_MemMap */

#endif /* COM_SIGNALIF_H */

/**********************************************************************************************************************
  END OF FILE: Com_SignalIf.h
**********************************************************************************************************************/
