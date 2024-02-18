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
/*!        \file  Com_Buffers.h
 *        \brief  MICROSAR Communication source file
 *
 *      \details  This is the implementation of the MICROSAR Communication module.
 *                The basic software module is based on the AUTOSAR Communication specification.
 *
 *********************************************************************************************************************/
#if !defined (COM_BUFFERS_H)
# define COM_BUFFERS_H

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
# include "Com_Lcfg.h"

/**********************************************************************************************************************
  GLOBAL CONSTANT MACROS
**********************************************************************************************************************/

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

# if (COM_TXBUFFERUSEDOFTXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_TxBuffer_InitTxIpdu
**********************************************************************************************************************/
/*! \brief        This function initializes a tx I-PDU in Com_TxBuffer.
    \details      -
    \pre          -
    \param[in]    ComPduId Handle of the I-PDU.
    \context      TASK
    \synchronous  TRUE
    \reentrant    FALSE
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxBuffer_InitTxIpdu(Com_TxPduInfoIterType ComPduId);
# endif

# if (COM_CONSTVALUEUINT8UBCLEARMASKENDIDXOFTXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_TxBuffer_ClearUpdateBits
**********************************************************************************************************************/
/*! \brief        This method sets the update bits to 0.
    \details      -
    \pre          -
    \param[in]    ComTxPduId    ID of Tx I-PDU.
    \context      TASK|ISR2
    \synchronous  TRUE
    \reentrant    FALSE
***********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxBuffer_ClearUpdateBits(PduIdType ComTxPduId);
# endif

# if (COM_TXSIGGRPMASK == STD_ON)
/**********************************************************************************************************************
  Com_TxBuffer_WriteSignalGroup
**********************************************************************************************************************/
/*! \brief        This method reads from the signal group buffer and writes the data to the Idpu buffer.
    \details      -
    \pre          -
    \param[in]    SignalGroupId  ID of Tx signal group.
    \param[in]    ShadowBufferPtr Reference to the signal group buffer.
    \context      TASK|ISR2
    \synchronous  TRUE
    \reentrant    FALSE
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxBuffer_WriteSignalGroup(Com_SignalGroupIdType SignalGroupId, P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) ShadowBufferPtr);
# endif

# if (COM_SHDBUFFERREQUIREDOFRXSIGGRPINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxProcessing_ExtractToShdwBffr
**********************************************************************************************************************/
/*! \brief        This function copies the temp shadow buffer of the passed ComSignalGroup to the shadow buffer.
    \details      -
    \pre          -
    \param[in]    idxRxSigGrpInfo   Handle Id of ComSignalGroup
    \param[in]    PduInfoPtr        contains the SDU buffer and the SDU length.
    \context      TASK|ISR2
    \synchronous  TRUE
    \reentrant    FALSE
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_RxProcessing_ExtractToShdwBffr(Com_RxSigGrpInfoIterType idxRxSigGrpInfo, P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr);
# endif

# if(COM_BUFFERUSEDOFRXACCESSINFO == STD_ON)
/**********************************************************************************************************************
  Com_Signal_SetRxSigBufferValue
**********************************************************************************************************************/
/*! \brief        This function copies the Simple ApplType dependent constant source value to the destination buffer RxSigBufferBuffer.
    \details      -
    \pre          -
    \param[in]    idxRxAccessInfo   Index of RxAccessInfo
    \param[in]    idxDestValue      Destination index of the buffer RxSigBufferBuffer
    \param[in]    idxSrcValue       Source index of constant source value
    \context      TASK|ISR2
    \synchronous  TRUE
    \reentrant    FALSE
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_Signal_SetRxSigBufferValue(Com_RxAccessInfoIterType idxRxAccessInfo, uint32_least idxDestValue, uint32_least idxSrcValue);
# endif

# if(COM_MINPROCGWBUFFERUSEDOFRXACCESSINFO == STD_ON)
/**********************************************************************************************************************
  Com_Signal_SetMinProcGwBufferValue
**********************************************************************************************************************/
/*! \brief        This function copies the Simple ApplType dependent constant source value to the destination buffer MinProcGwBuffer.
    \details      -
    \pre          -
    \param[in]    idxRxAccessInfo   Index of RxAccessInfo
    \param[in]    idxDestValue      Destination index of the buffer MinProcGwBuffer
    \param[in]    idxSrcValue       Source index of constant source value
    \context      TASK|ISR2
    \synchronous  TRUE
    \reentrant    FALSE
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_Signal_SetMinProcGwBufferValue(Com_RxAccessInfoIterType idxRxAccessInfo, uint32_least idxDestValue, uint32_least idxSrcValue);
# endif

# if (((COM_MINPROCGWBUFFERUSEDOFRXACCESSINFO == STD_ON) || (COM_MINPROCGWBUFFERARRAYBASEDBUFFERUSEDOFRXACCESSINFO == STD_ON)) && (COM_GWSIGGRPMAPPINGENDIDXOFGWINFO == STD_ON))
/**********************************************************************************************************************
  Com_RxProcessing_ExtractToMinProcGwBuffer
**********************************************************************************************************************/
/*! \brief        This function copies the temp shadow buffer of the passed ComSignalGroup to the MinProcGwBuffer.
    \details      -
    \pre          -
    \param[in]    idxRxSigGrpInfo   Handle Id of ComSignalGroup
    \param[in]    PduInfoPtr        contains the SDU buffer and the SDU length.
    \context      TASK|ISR2
    \synchronous  TRUE
    \reentrant    FALSE
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_RxProcessing_ExtractToMinProcGwBuffer(Com_RxSigGrpInfoIterType idxRxSigGrpInfo, P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr);
# endif

# define COM_STOP_SEC_CODE
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_MemMap */

#endif /* COM_BUFFERS_H */
/**********************************************************************************************************************
  END OF FILE: Com_Buffers.h
**********************************************************************************************************************/
