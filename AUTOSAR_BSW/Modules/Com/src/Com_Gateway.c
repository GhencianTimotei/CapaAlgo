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
/*!        \file  Com_Gateway.c
 *        \brief  MICROSAR Communication source file
 *
 *      \details  This is the implementation of the MICROSAR Communication module.
 *                The basic software module is based on the AUTOSAR Communication specification.
 *
 *********************************************************************************************************************/
#define COM_GATEWAY_SOURCE

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
#include "Com.h"
#include "Com_LLIf.h"
#include "Com_Timer.h"
#include "Com_Gateway.h"
#include "Com_SignalIf.h"
#include "Com_TxModeHdlr.h"
#include "Com_Serializer.h"
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

#if (COM_GWTXPDUDESCRIPTIONINFOUSEDOFRXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_IsGwDestinationDescriptionTypeImmediate
**********************************************************************************************************************/
/*! \brief        This function checks if the type of the gateway description is immediate.
    \details      -
    \pre          -
    \param[in]    DescriptionType - Type of description
    \return       boolean
                    TRUE if type of description is immediate.
                    FALSE otherwise
**********************************************************************************************************************/
# define Com_IsGwDestinationDescriptionTypeImmediate(DescriptionType)       (boolean) ((((DescriptionType) & COM_IMMEDIATE_MASK_TYPEOFGWDESCRIPTIONACCESSINFO) == COM_IMMEDIATE_MASK_TYPEOFGWDESCRIPTIONACCESSINFO) ? TRUE : FALSE)

/**********************************************************************************************************************
  Com_IsGwDestinationDescriptionTypeTriggered
**********************************************************************************************************************/
/*! \brief        This function checks if the description has a TRIGGERED* transferProperty
    \details      -
    \pre          -
    \param[in]    DescriptionType - Type of description
    \return       boolean
                    TRUE if a TRIGGERED* transferProperty is configured
                    FALSE otherwise
**********************************************************************************************************************/
# define Com_IsGwDestinationDescriptionTypeTriggered(DescriptionType)       (((DescriptionType) & COM_TRIGGERED_MASK_TYPEOFGWDESCRIPTIONACCESSINFO) == COM_TRIGGERED_MASK_TYPEOFGWDESCRIPTIONACCESSINFO)

/**********************************************************************************************************************
  Com_IsGwDestinationDescriptionTypeOnChange
**********************************************************************************************************************/
/*! \brief        This function checks if the description has an ONCHANGE* transferProperty
    \details      -
    \pre          -
    \param[in]    DescriptionType - Type of description
    \return       boolean
                    TRUE if an ONCHANGE* transferProperty is configured
                    FALSE otherwise
**********************************************************************************************************************/
# define Com_IsGwDestinationDescriptionTypeOnChange(DescriptionType)        (((DescriptionType) & COM_ONCHANGE_MASK_TYPEOFGWDESCRIPTIONACCESSINFO) == COM_ONCHANGE_MASK_TYPEOFGWDESCRIPTIONACCESSINFO)

/**********************************************************************************************************************
  Com_IsGwDestinationDescriptionTypeWithoutRepetion
**********************************************************************************************************************/
/*! \brief        This function checks if the description has an WITHOUTREPETITION* transferProperty
    \details      -
    \pre          -
    \param[in]    DescriptionType - Type of description
    \return       boolean
                    TRUE if a WITHOUTREPETITION* transferProperty is configured
                    FALSE otherwise
**********************************************************************************************************************/
# define Com_IsGwDestinationDescriptionTypeWithoutRepetion(DescriptionType)  (((DescriptionType) & COM_WITHOUTREP_MASK_TYPEOFGWDESCRIPTIONACCESSINFO) == COM_WITHOUTREP_MASK_TYPEOFGWDESCRIPTIONACCESSINFO)
#endif

/**********************************************************************************************************************
  LOCAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
#if (COM_GWTXPDUDESCRIPTIONINFOUSEDOFRXPDUINFO == STD_ON)
typedef enum
{
  COM_TRANSMIT_TRIGGER_NOTFULFILLED,
  COM_TRANSMIT_TRIGGER,
  COM_TRANSMIT_TRIGGERWITHOUTREP
} Com_GwDescriptionTriggerType;
#endif

#if (COM_GWTXPDUDESCRIPTIONINFOUSEDOFRXPDUINFO == STD_ON)
/*!
  \defgroup  Com_IsGwDestinationDescriptionTypeX Bit Flags
  \brief  These bit masks are used to retrieve the desired property out of GwDestinationDescriptionType
  \details  -
    \pre      -
    \{
*/
# define COM_IMMEDIATE_MASK_TYPEOFGWDESCRIPTIONACCESSINFO      8u    /**< bit mask to retrieve the immediate flag */
# define COM_TRIGGERED_MASK_TYPEOFGWDESCRIPTIONACCESSINFO      4u    /**< bit mask to retrieve the triggered flag */
# define COM_ONCHANGE_MASK_TYPEOFGWDESCRIPTIONACCESSINFO       2u    /**< bit mask to retrieve the onchange flag */
# define COM_WITHOUTREP_MASK_TYPEOFGWDESCRIPTIONACCESSINFO     1u    /**< bit mask to retrieve the without repetition flag */
/*!
  \}
*/
#endif

/**********************************************************************************************************************
  LOCAL DATA PROTOTYPES
**********************************************************************************************************************/

/**********************************************************************************************************************
  LOCAL FUNCTION PROTOTYPES
**********************************************************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"    /* PRQA S 5087 */        /* MD_MSR_MemMap */

#if (COM_GWTXPDUDESCRIPTIONINFOUSEDOFRXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxProcessing_ProcessDestinationDescription
**********************************************************************************************************************/
/*! \brief        This function processes a gateway destination description. More precisely, it copies the configured bits
 *                from the source to destination buffer if the transfer property conditions are satisfied.
    \details      -
    \pre          -
    \param[in]    rxPduBuffer          Buffer of rxPdu that is received on gateway description event.
    \param[in]    gwDescrAccessIdx     Index of Com_GwDescriptionAccessInfo, which contains all informations of the description
    \return       Com_GwDescriptionTriggerType
                      COM_TRANSMIT_TRIGGER_NOTFULFILLED  transfer property conditions are not fulfilled
                      COM_TRANSMIT_TRIGGER               transfer property conditions are fulfilled and repetitions
                                                         are required
                      COM_TRANSMIT_TRIGGERWITHOUTREP     transfer property conditions are fulfilled and repetitions
                                                         are not required
    \context      TASK|ISR2
    \trace        CREQ-115135
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(Com_GwDescriptionTriggerType, COM_CODE) Com_RxProcessing_ProcessDestinationDescription(P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) rxPduBuffer,
                                                                                                             Com_GwDescriptionAccessInfoEndIdxOfGwTxPduDescriptionInfoType gwDescrAccessIdx);

/**********************************************************************************************************************
  Com_GwDescriptionCopyBuffer
**********************************************************************************************************************/
/*! \brief        This function copies the received content from source to destination buffer.
    \details      -
    \pre          -
    \param[in]    rxPduBuffer          Buffer of rxPdu that is received on gateway description event.
    \param[in]    gwDescrAccessIdx     Index of Com_GwDescriptionAccessInfo, which contains all informations of the description
    \return       boolean
                    TRUE                 if content of destination buffer has changed.
                    FALSE                otherwise
    \context      TASK|ISR2
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(boolean, COM_CODE) Com_GwDescriptionCopyBuffer(P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) rxPduBuffer,
                                                                     Com_GwDescriptionAccessInfoEndIdxOfGwTxPduDescriptionInfoType gwDescrAccessIdx);

# if ((COM_DIRECTOFTXMODETRUE == STD_ON) || (COM_DIRECTOFTXMODEFALSE == STD_ON))
/**********************************************************************************************************************
  Com_RxProcessing_GwDescriptionTransmit
**********************************************************************************************************************/
/*! \brief        This function initiates the transmission of txPdu on gateway description event
    \details      -
    \pre          -
    \param[in]    txPduID                 Valid ID of TxPdu that should be sent
    \param[in]    isImmediate             true, if TxPdu should be sent immediately, otherwise transmission will be triggered
                                          in next main function cycle
    \param[in]    withoutRepetitionFlag   true, if no repetitions are required
    \context      TASK|ISR2
 *********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_RxProcessing_GwDescriptionTransmit(PduIdType txPduID, boolean isImmediate, boolean withoutRepetitionFlag);
# endif
#endif

#if (COM_EXISTS_DIRECT_COPYTYPEOFGWDESCRIPTIONACCESSINFO == STD_ON)
/**********************************************************************************************************************
  Com_GwDescription_DirectCopy
**********************************************************************************************************************/
/*! \brief            This function directly copies the content from source to destination buffer.
    \details          -
    \param[in]        gwDescrAccessIdx          Gateway description access idx.
    \param[in]        sourceBuffer              Received source buffer referenced by source description.
    \param[in,out]    destinationBuffer         Tx Buffer where the received content is copied to.
    \param[in]        txBufferLength            Length of destinationBuffer
    \return           boolean
                        TRUE   if any bytes of destination have changed
                        FALSE  otherwise
    \pre              Caller has to ensure that sourceBuffer and destinationBuffer point to start byte of source and destination description.
    \context          TASK|ISR2
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(boolean, COM_CODE) Com_GwDescription_DirectCopy(Com_GwDescriptionAccessInfoEndIdxOfGwTxPduDescriptionInfoType gwDescrAccessIdx,
                                                                      P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) sourceBuffer,
                                                                      P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) destinationBuffer, Com_TxBufferLengthOfGwDescriptionAccessInfoType txBufferLength);
#endif

#if (COM_EXISTS_RIGHTSHIFT_COPYTYPEOFGWDESCRIPTIONACCESSINFO == STD_ON)
/**********************************************************************************************************************
  Com_GwDescription_RightShiftCopy
**********************************************************************************************************************/
/*! \brief              This function shifts the content of source buffer to the right and copies it to the destination buffer.
    \details            -
    \param[in]          sourceBuffer              Source buffer.
    \param[in,out]      destinationBuffer         Destination buffer.
    \param[in]          destinationBufferSize     Size of Destination Buffer.
    \param[in]          sourceStartBitIndex       Bit index within byte zero of source, where the content starts.
    \param[in]          bitOffset                 Offset to be shifted right.
    \param[in]          bitLength                 Number of bits to be copied.
    \param[in]          isBigEndian               true, if GwDescription is type of BIG_ENDIAN
    \return             boolean
                          TRUE                    if any bytes of destination have changed
                          FALSE                   otherwise
    \pre                For BigEndian description routing, caller has to ensure that sourceBuffer and destinationBuffer
                        point to end byte of source and destination description. For LittleEndian description routing,
                        caller has to ensure that sourceBuffer and destinationBuffer point to start byte of source
                        and destination description.
    \context            TASK|ISR2
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(boolean, COM_CODE) Com_GwDescription_RightShiftCopy(P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) sourceBuffer,
                                                                          P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) destinationBuffer,
                                                                          uint16 destinationBufferSize, uint8 sourceStartBitIndex, uint8 bitOffset, uint16 bitLength, boolean isBigEndian);
#endif

#if (COM_EXISTS_LEFTSHIFT_COPYTYPEOFGWDESCRIPTIONACCESSINFO == STD_ON)
/**********************************************************************************************************************
  Com_GwDescription_LeftShiftCopy
**********************************************************************************************************************/
/*! \brief            This function shifts the content of source buffer to the left and copies it to the destination buffer.
    \details          -
    \param[in]        sourceBuffer              Source buffer.
    \param[in,out]    destinationBuffer         Destination buffer.
    \param[in]        destinationBufferSize     Size of Destination Buffer.
    \param[in]        sourceStartBitIndex       Bit index within byte zero of source, where the content starts.
    \param[in]        bitOffset                 Offset to be shifted left.
    \param[in]        bitLength                 Number of bits to be copied.
    \param[in]        isBigEndian               true, if GwDescription is type of BIG_ENDIAN
    \return           boolean
                        TRUE                    if any bytes of destination have changed
                        FALSE                   otherwise
    \pre              For BigEndian description routing, caller has to ensure that sourceBuffer and destinationBuffer
                      point to end byte of source and destination description. For LittleEndian description routing,
                      caller has to ensure that sourceBuffer and destinationBuffer point to start byte of source and
                      destination description.
    \context          TASK|ISR2
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(boolean, COM_CODE) Com_GwDescription_LeftShiftCopy(P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) sourceBuffer,
                                                                         P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) destinationBuffer,
                                                                         uint16 destinationBufferSize, uint8 sourceStartBitIndex, uint8 bitOffset, uint16 bitLength, boolean isBigEndian);
#endif

#if (COM_RXUBMASKUSEDOFGWDESCRIPTIONACCESSINFO  == STD_ON)
/**********************************************************************************************************************
  Com_RxProcessing_CheckGwDescriptionUB
**********************************************************************************************************************/
/*! \brief        This function evaluates if the source description was updated.
    \details      -
    \pre          -
    \param[in]    gwDescrAccessIdx        Index of RxSigInfo
    \param[in]    PduInfoPtr              contains the SDU buffer and the SDU length.
    \return       boolean
                    TRUE                  if the source description was updated
                    FALSE                 otherwise
    \context      TASK|ISR2
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(boolean, COM_CODE) Com_RxProcessing_CheckGwDescriptionUB(Com_GwDescriptionAccessInfoEndIdxOfGwTxPduDescriptionInfoType gwDescrAccessIdx,
                                                                               P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr);
#endif

#if (COM_GWEVENTCACHE == STD_ON)
/**********************************************************************************************************************
  Com_GwDescription_EnterExclusiveArea
**********************************************************************************************************************/
/*! \brief    This function enters the gw description routing exclusive area.
    \details  -
    \pre      -
    \trace    DSGN-COM_ISRTHRESHOLD_CONCEPT
    \context  TASK
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_GwDescription_EnterExclusiveArea(void);

/**********************************************************************************************************************
  Com_GwDescription_ExitExclusiveArea
**********************************************************************************************************************/
/*! \brief    This function exits the gw description routing exclusive area.
    \details  -
    \pre      -
    \trace    DSGN-COM_ISRTHRESHOLD_CONCEPT
    \context  TASK
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_GwDescription_ExitExclusiveArea(void);

/**********************************************************************************************************************
  Com_GwDescription_ThresholdCheck
**********************************************************************************************************************/
/*! \brief    This function checks if the ISR Lock must be opened
    \details  -
    \pre      -
    \trace    DSGN-COM_ISRTHRESHOLD_CONCEPT
    \context  TASK
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_GwDescription_ThresholdCheck(void);
#endif


#if (((COM_GWSIGMAPPINGENDIDXOFGWINFO == STD_ON) || (COM_GWSIGGRPMAPPINGENDIDXOFGWINFO == STD_ON)) && (COM_MINPROCGWBUFFERUSEDOFRXACCESSINFO == STD_OFF && COM_MINPROCGWBUFFERARRAYBASEDBUFFERUSEDOFRXACCESSINFO == STD_OFF))
/**********************************************************************************************************************
  Com_MainFunction_SignalRoutings_SendSignal
**********************************************************************************************************************/
/*! \brief    This function routes the received signal after complete signal processing to its destination
    \details  -
    \param[in]    idxRxAccessInfo      Index of RxAccessInfo.
    \param[in]    txSigId              Tx signal Id.
    \pre      -
    \context  TASK
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_MainFunction_SignalRoutings_SendSignal(Com_SignalIdType idxRxAccessInfo, Com_TxSigInfoIterType txSigId);
#endif

#if ((COM_MINPROCGWBUFFERUSEDOFRXACCESSINFO == STD_ON) || (COM_MINPROCGWBUFFERARRAYBASEDBUFFERUSEDOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
  Com_MainFunction_SignalRoutings_SendSignalWithMinimalProcessing
**********************************************************************************************************************/
/*! \brief    This function routes the received signal after minimal signal processing to its destination
    \details  -
    \param[in]    idxRxAccessInfo      Index of RxAccessInfo.
    \param[in]    txSigId              Tx signal Id.
    \pre      -
    \context  TASK
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_MainFunction_SignalRoutings_SendSignalWithMinimalProcessing(Com_SignalIdType idxRxAccessInfo, Com_TxSigInfoIterType txSigId);
#endif



/**********************************************************************************************************************
  LOCAL FUNCTIONS
**********************************************************************************************************************/
#if (COM_GWTXPDUDESCRIPTIONINFOUSEDOFRXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxProcessing_ProcessDestinationDescription
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 ********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(Com_GwDescriptionTriggerType, COM_CODE) Com_RxProcessing_ProcessDestinationDescription(P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) rxPduBuffer,
                                                                                                             Com_GwDescriptionAccessInfoEndIdxOfGwTxPduDescriptionInfoType gwDescrAccessIdx)
{
  Com_GwDescriptionTriggerType retVal = COM_TRANSMIT_TRIGGER_NOTFULFILLED;      /* PRQA S 2981 */ /* MD_MSR_RetVal */

  Com_TypeOfGwDescriptionAccessInfoType descriptionType = Com_GetTypeOfGwDescriptionAccessInfo(gwDescrAccessIdx);

  boolean triggerCondition = TRUE;

  /* #10 Copy configured bytes into destination txPduBuffers */
  boolean hasContentChanged = Com_GwDescriptionCopyBuffer(rxPduBuffer, gwDescrAccessIdx);       /* SBSW_COM_FCTCALL_WITH_P2CONST */

  if(Com_IsGwDestinationDescriptionTypeOnChange(descriptionType))       /* TRIGGERED ON CHANGE */
  {
    triggerCondition = hasContentChanged;
  }

  /* #20 If transferProperty is not type of ON-CHANGE or content of description has changed */
  if(triggerCondition == TRUE)
  {
    /* #30 Set TRIGGERED and WITHOUTREPETITION FLAG if transfer property is TriggeredWithoutRepetition or TriggeredOnChangeWithoutRepetition */
    if(Com_IsGwDestinationDescriptionTypeWithoutRepetion(descriptionType))
    {
      retVal = COM_TRANSMIT_TRIGGERWITHOUTREP;
    }
    /* #40 otherwise set TRIGGERED FLAG if transfer property is Triggered */
    else if(Com_IsGwDestinationDescriptionTypeTriggered(descriptionType))
    {
      retVal = COM_TRANSMIT_TRIGGER;
    }
    else
    {
      /* #50 otherwise transfer property is assumed to be PENDING */
      retVal = COM_TRANSMIT_TRIGGER_NOTFULFILLED;
    }
  }

# if (COM_TXUBMASKUSEDOFGWDESCRIPTIONACCESSINFO == STD_ON)
  /* #60 If the destination description has a configured UB, set UB in the Tx ComIPdu Buffer. */
  if(Com_IsTxUbMaskUsedOfGwDescriptionAccessInfo(gwDescrAccessIdx))
  {
    Com_TxBufferEndIdxOfTxPduInfoType ubIdx = Com_GetTxBufferUbIdxOfGwDescriptionAccessInfo(gwDescrAccessIdx);
    Com_SetTxBuffer(ubIdx, (Com_GetTxBuffer(ubIdx) | Com_GetConstValueUInt8(Com_GetTxUbMaskIdxOfGwDescriptionAccessInfo(gwDescrAccessIdx))));   /* SBSW_COM_CSL03 */
  }
# endif

  return retVal;
}

 /**********************************************************************************************************************
  Com_GwDescriptionCopyBuffer
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 ********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(boolean, COM_CODE) Com_GwDescriptionCopyBuffer(P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) rxPduBuffer,
                                                                     Com_GwDescriptionAccessInfoEndIdxOfGwTxPduDescriptionInfoType gwDescrAccessIdx)
{
  boolean hasContentChanged = FALSE;    /* PRQA S 2981 */ /* MD_MSR_RetVal */

  P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) destinationBuffer;
  boolean isBigEndian;

  P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) sourceBuffer = &(rxPduBuffer[Com_GetSourceStartBytePositionOfGwDescriptionAccessInfo(gwDescrAccessIdx)]);
  uint8 sourceStartBitIndex = Com_GetGwSourceStartBitIndexOfGwDescriptionAccessInfo(gwDescrAccessIdx);
  uint8 bitOffset = Com_GetBitOffsetOfGwDescriptionAccessInfo(gwDescrAccessIdx);

  Com_TxBufferLengthOfGwDescriptionAccessInfoType destinationBufferSize = Com_GetTxBufferLengthOfGwDescriptionAccessInfo(gwDescrAccessIdx);

# if (COM_EXISTS_BIG_ENDIAN_ENDIANNESSOFGWDESCRIPTIONACCESSINFO == STD_ON)
  if(Com_GetEndiannessOfGwDescriptionAccessInfo(gwDescrAccessIdx) == COM_BIG_ENDIAN_ENDIANNESSOFGWDESCRIPTIONACCESSINFO)
  {
    destinationBuffer = Com_GetAddrTxBuffer(Com_GetTxBufferEndIdxOfGwDescriptionAccessInfo(gwDescrAccessIdx) - 1u);
    isBigEndian = TRUE;
  }
  else
# endif
  {
    destinationBuffer = Com_GetAddrTxBuffer(Com_GetTxBufferStartIdxOfGwDescriptionAccessInfo(gwDescrAccessIdx));
    isBigEndian = FALSE;
  }

  switch (Com_GetCopyTypeOfGwDescriptionAccessInfo(gwDescrAccessIdx))
  {     /* #10 If source and destination description are bit aligned respective to their relative start bit position, copy directly the desired bytes. */
# if (COM_EXISTS_DIRECT_COPYTYPEOFGWDESCRIPTIONACCESSINFO == STD_ON)
    case COM_DIRECT_COPYTYPEOFGWDESCRIPTIONACCESSINFO:
    {
      /* Assume direct copy is always little endian. */
      hasContentChanged = Com_GwDescription_DirectCopy(gwDescrAccessIdx, sourceBuffer, destinationBuffer, destinationBufferSize);       /* SBSW_COM_GW_DESCRIPTION_COPYBUFFER */
      break;
    }
# endif
# if (COM_EXISTS_RIGHTSHIFT_COPYTYPEOFGWDESCRIPTIONACCESSINFO == STD_ON)
      /* #20 Otherwise if relative start bit index of source is bigger than destination, perform right shift copy operation. */
    case COM_RIGHTSHIFT_COPYTYPEOFGWDESCRIPTIONACCESSINFO:
    {
      hasContentChanged = Com_GwDescription_RightShiftCopy(sourceBuffer, destinationBuffer, (uint16) destinationBufferSize, sourceStartBitIndex, bitOffset, Com_GetBitSizeOfGwDescriptionAccessInfo(gwDescrAccessIdx), isBigEndian);    /* SBSW_COM_GW_DESCRIPTION_COPYBUFFER */
      break;
    }
# endif
# if (COM_EXISTS_LEFTSHIFT_COPYTYPEOFGWDESCRIPTIONACCESSINFO == STD_ON)
      /* #30 Otherwise perform left shift copy operation. */
    case COM_LEFTSHIFT_COPYTYPEOFGWDESCRIPTIONACCESSINFO:
    {
      hasContentChanged = Com_GwDescription_LeftShiftCopy(sourceBuffer, destinationBuffer, (uint16) destinationBufferSize, sourceStartBitIndex, bitOffset, Com_GetBitSizeOfGwDescriptionAccessInfo(gwDescrAccessIdx), isBigEndian);     /* SBSW_COM_GW_DESCRIPTION_COPYBUFFER */
      break;
    }
# endif
    default:   /* COV_COM_MISRA */
      break;
  }

  COM_DUMMY_STATEMENT(sourceStartBitIndex);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(bitOffset);       /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(isBigEndian);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return hasContentChanged;
}

# if ((COM_DIRECTOFTXMODETRUE == STD_ON) || (COM_DIRECTOFTXMODEFALSE == STD_ON))
/**********************************************************************************************************************
  Com_RxProcessing_GwDescriptionTransmit
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
 *
 *
 ***********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_RxProcessing_GwDescriptionTransmit(PduIdType txPduID, boolean isImmediate, boolean withoutRepetitionFlag)
{

  /* #10 If txPdu should be processed immediately and minimum delay time has elapsed */
  if((isImmediate == TRUE)
#  if (COM_MINIMUMDELAYOFTXMODEINFO == STD_ON)
     && (Com_GetDelayTimeCnt(txPduID) == 0u)
#  endif
    )   /* COV_COM_IMMEDIATE_DESTINATION_DESCRIPTION */
  {
    /* #20 If TxPdu is active */
    if(Com_IsTxPduGrpActive(txPduID))
    {
      /* #30 If Tx Pdu is in DIRECT or MIXED TxModeMode */
      if(Com_TxModeHdlr_IsDirectTxMode(txPduID) == TRUE)
      {
#  if ((COM_REPCNTOFTXMODETRUE == STD_ON) || (COM_REPCNTOFTXMODEFALSE == STD_ON))
        /* #40 Reload repetition counter and repetition cycle counter, if repetitions are required */
        if(withoutRepetitionFlag == FALSE)
        {
          Com_SetRepCnt(txPduID, Com_TxModeHdlr_GetCurRepCnt(txPduID)); /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
          Com_SetRepCycleCnt(txPduID, Com_TxModeHdlr_GetCurrentRepetitionPeriod(txPduID));      /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */

#   if (COM_EXISTS_NORMAL_MODEOFTXTOUTINFO == STD_ON)
          /* #42 Reload Tx Deadline Monitoring timer if configured */
          if(0u < Com_GetRepCnt(txPduID))
          {
            /* SPEC-2736884 */
            if(Com_IsTxTOutInfoUsedOfTxPduInfo(txPduID))        /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
            {
              Com_TxTOutInfoIdxOfTxPduInfoType idxTxTOutInfo = Com_GetTxTOutInfoIdxOfTxPduInfo(txPduID);
              Com_SetTxTOutCnt(idxTxTOutInfo, Com_GetFactorOfTxTOutInfo(idxTxTOutInfo));        /* SBSW_COM_CSL02 */
            }
          }
          else
          {
            Com_TxModeHdlr_ReloadTxDlMonCounter(txPduID);
          }
#   endif
        }
        else
#  endif
        {
#  if (COM_EXISTS_NORMAL_MODEOFTXTOUTINFO == STD_ON)
          Com_TxModeHdlr_ReloadTxDlMonCounter(txPduID);
#  endif
        }
        /* #45 Set eventbased trigger Flag if configured */
#  if (COM_DIRECTTRIGGER == STD_ON)
        Com_SetDirectTrigger(txPduID, TRUE);    /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
#  endif

        /* #50 Trigger transmit */
#  if (COM_RETRY_FAILED_TRANSMIT_REQUESTS == STD_ON)
        /* #60 If transmission was not successful and retry failed transmit feature is configured */
        if(Com_TxLLIf_Transmit(txPduID) != E_OK)
        {
          /* #70 Schedule deferred transmission in next main function cycle */
          Com_TxModeHdlr_TriggerDeferredTransmitAndSetTimer(txPduID, withoutRepetitionFlag);
        }
#  else
        (void) Com_TxLLIf_Transmit(txPduID);
#  endif
      }
    }
  }
  /* #80 otherwise trigger deferred transmission in next main function cycle */
  else
  {
    Com_TxModeHdlr_TriggerDeferredTransmitAndSetTimer(txPduID, withoutRepetitionFlag);
  }
}       /* PRQA S 6080 */ /* MD_MSR_STMIF */
# endif
#endif

#if (COM_RXUBMASKUSEDOFGWDESCRIPTIONACCESSINFO  == STD_ON)
/**********************************************************************************************************************
  Com_RxProcessing_CheckGwDescriptionUB
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(boolean, COM_CODE) Com_RxProcessing_CheckGwDescriptionUB(Com_GwDescriptionAccessInfoEndIdxOfGwTxPduDescriptionInfoType gwDescrAccessIdx,
                                                                               P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr)
{
  boolean retVal = TRUE;        /* PRQA S 2981 */ /* MD_MSR_RetVal */
  /* #10 If the source description has an UpdateBit */
  if(Com_IsRxUbMaskUsedOfGwDescriptionAccessInfo(gwDescrAccessIdx))
  {
    /* #20 If the configured UpdateBit was not received mark the source description as updated */
    /* <= because a length is compared with an index */
    if(PduInfoPtr->SduLength <= Com_GetRxUbIdxOfGwDescriptionAccessInfo(gwDescrAccessIdx))
    {
      /* Update-bit not received */
      retVal = TRUE;
    }
    /* #30 If the UpdateBit is not set, mark the source description as not updated */
    else if(0u == (PduInfoPtr->SduDataPtr[Com_GetRxUbIdxOfGwDescriptionAccessInfo(gwDescrAccessIdx)] & Com_GetConstValueUInt8(Com_GetRxUbMaskIdxOfGwDescriptionAccessInfo(gwDescrAccessIdx))))
    {
      /* Update-bit not set */
      retVal = FALSE;
    }
    /* #40 Otherwise mark the source description as updated */
    else
    {
      /* Update-bit set */
      retVal = TRUE;
    }
  }
  return retVal;
}
#endif

#if (COM_EXISTS_DIRECT_COPYTYPEOFGWDESCRIPTIONACCESSINFO == STD_ON)
/**********************************************************************************************************************
   Com_GwDescription_DirectCopy
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 ********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(boolean, COM_CODE) Com_GwDescription_DirectCopy(Com_GwDescriptionAccessInfoEndIdxOfGwTxPduDescriptionInfoType gwDescrAccessIdx,
                                                                      P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) sourceBuffer,
                                                                      P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) destinationBuffer, Com_TxBufferLengthOfGwDescriptionAccessInfoType txBufferLength)
{
  boolean destinationHasChanged = FALSE;        /* PRQA S 2981 */ /* MD_MSR_RetVal */

  uint8 byteToBeCopied;

  Com_SourceDescriptionMaskType mask = Com_GetSourceDescriptionMask(Com_GetSourceDescriptionMaskIdxOfGwDescriptionAccessInfo(gwDescrAccessIdx));

  /* #10 Copy configured bytes into destination txPduBuffers and return true if any of the destination bytes has changed it's content. */

  byteToBeCopied = (destinationBuffer[0] & COM_CAST2UINT8(~mask)) | (sourceBuffer[0] & mask);

  if(destinationBuffer[0] != byteToBeCopied)
  {
    destinationBuffer[0] = byteToBeCopied;      /* SBSW_COM_CSL03 */
    destinationHasChanged = TRUE;
  }

# if (COM_SOURCEDESCRIPTIONMASKENDMASKUSEDOFGWDESCRIPTIONACCESSINFO == STD_ON)
  if(txBufferLength > 1u)
  {
    Com_TxBufferLengthOfGwDescriptionAccessInfoType byteIdx;
    Com_SourceDescriptionMaskType endMask = Com_GetSourceDescriptionMask(Com_GetSourceDescriptionMaskEndMaskIdxOfGwDescriptionAccessInfo(gwDescrAccessIdx));
    /* Intermediate bytes can be copied directly. */
    for(byteIdx = 1u; byteIdx < (txBufferLength - 1u); byteIdx++)
    {
      if(destinationBuffer[byteIdx] != sourceBuffer[byteIdx])
      {
        destinationBuffer[byteIdx] = sourceBuffer[byteIdx];     /* SBSW_COM_CSL03 */
        destinationHasChanged = TRUE;
      }
    }

    /* Last byte has to be masked to avoid overwriting bits that do not belong to gateway description. */
    byteToBeCopied = (destinationBuffer[byteIdx] & COM_CAST2UINT8(~endMask)) | (sourceBuffer[byteIdx] & endMask);

    if(destinationBuffer[byteIdx] != sourceBuffer[byteIdx])
    {
      destinationBuffer[byteIdx] = byteToBeCopied;      /* SBSW_COM_CSL03 */
      destinationHasChanged = TRUE;
    }
  }
# else
  COM_DUMMY_STATEMENT(txBufferLength);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
# endif

  return destinationHasChanged;
}
#endif

#if (COM_EXISTS_RIGHTSHIFT_COPYTYPEOFGWDESCRIPTIONACCESSINFO == STD_ON)
/*********************************************************************************************************************
   Com_GwDescription_RightShiftCopy
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 ********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(boolean, COM_CODE) Com_GwDescription_RightShiftCopy(P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) sourceBuffer,
                                                                          P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) destinationBuffer,
                                                                          uint16 destinationBufferSize, uint8 sourceStartBitIndex, uint8 bitOffset, uint16 bitLength, boolean isBigEndian)
{

  sint32 i = 1;

  uint16 remainingBits;
  uint8 destinationStartBitIndex = COM_CAST2UINT8(sourceStartBitIndex - bitOffset);

  uint8 sourceEndBitIndex = COM_CAST2UINT8((sourceStartBitIndex + bitLength) - 1u) % 8u;
  uint8 destinationEndBitIndex = COM_CAST2UINT8((destinationStartBitIndex + bitLength) - 1u) % 8u;

  uint8 destinationMask = COM_CAST2UINT8(255u << destinationStartBitIndex);
  uint8 sourceMask_i = COM_CAST2UINT8(255u << sourceStartBitIndex);
  uint8 sourceMask_iP1 = COM_CAST2UINT8(~sourceMask_i);

  uint8 byteToCopy = 0u;        /* PRQA S 2981 */ /* MD_MSR_RetVal */

  boolean destinationHasChanged = FALSE;        /* PRQA S 2981 */ /* MD_MSR_RetVal */

  if((destinationStartBitIndex + bitLength) <= 8u)
  {
    /* Destination description covers single byte. Truncate leading bits of destination mask. */
    destinationMask &= COM_CAST2UINT8(255u >> COM_CAST2UINT8(8u - (destinationStartBitIndex + bitLength)));
    remainingBits = 0u;
  }
  else
  {
    /* Description covers multiple bytes. No truncation of mask is required. */
    uint8 bitToBeCopiedToFirstByte = COM_CAST2UINT8(8u - destinationStartBitIndex);
    remainingBits = (uint16) (bitLength - bitToBeCopiedToFirstByte);
  }

  if((sourceStartBitIndex + bitLength) <= 8u)
  {
    /* Source description covers single byte.  Truncate leading bits of source mask */
    sourceMask_i &= COM_CAST2UINT8(255u >> COM_CAST2UINT8(7u - sourceEndBitIndex));
    byteToCopy = COM_CAST2UINT8((sourceBuffer[0] & sourceMask_i) >> bitOffset);
  }
  else
  {
    /* Source description covers multiple bytes. */
    uint8 bitsOf_i = COM_CAST2UINT8(8u - sourceStartBitIndex);
    uint8 posOf_iP1 = destinationStartBitIndex + bitsOf_i;

    if(bitLength < bitOffset)
    {
      sourceMask_iP1 = COM_CAST2UINT8(~COM_CAST2UINT8(255u << (sourceEndBitIndex + 1u)));
    }

    byteToCopy = COM_CAST2UINT8((sourceBuffer[0] & sourceMask_i) >> bitOffset);
    byteToCopy |= COM_CAST2UINT8((sourceBuffer[Com_NBITNBYTE_GetEndiannesIndex(i, isBigEndian)] & sourceMask_iP1) << posOf_iP1);
  }

  byteToCopy = (destinationBuffer[0] & COM_CAST2UINT8(~destinationMask)) | (byteToCopy & destinationMask);

  if(destinationBuffer[0] != byteToCopy)
  {
    destinationHasChanged = TRUE;
    destinationBuffer[0] = byteToCopy;  /* SBSW_COM_CSL03 */
  }

  sourceMask_i = COM_CAST2UINT8(255u << bitOffset);
  sourceMask_iP1 = COM_CAST2UINT8(~sourceMask_i);

  while((remainingBits > 7u) && (i < (sint32) destinationBufferSize))   /* COV_COM_GWDESCRIPTION_RTCHECK */
  {
    /* Copy full bytes without truncation. */
    byteToCopy = COM_CAST2UINT8((sourceBuffer[Com_NBITNBYTE_GetEndiannesIndex(i, isBigEndian)] & sourceMask_i) >> bitOffset);
    byteToCopy |= COM_CAST2UINT8((sourceBuffer[Com_NBITNBYTE_GetEndiannesIndex(i + 1, isBigEndian)] & sourceMask_iP1) << COM_CAST2UINT8(8u - bitOffset));

    if(destinationBuffer[Com_NBITNBYTE_GetEndiannesIndex(i, isBigEndian)] != byteToCopy)
    {
      destinationHasChanged = TRUE;
      destinationBuffer[Com_NBITNBYTE_GetEndiannesIndex(i, isBigEndian)] = byteToCopy;  /* SBSW_COM_GWDESCRIPTION_RTCHECK */
    }

    i++;
    remainingBits = (uint16) (remainingBits - 8u);
  }

  if((remainingBits > 0u) && (i < (sint32) destinationBufferSize))      /* COV_COM_GWDESCRIPTION_RTCHECK */
  {     /* if source covers multiple bytes */
    destinationMask = COM_CAST2UINT8(255u >> COM_CAST2UINT8(7u - destinationEndBitIndex));
    if(destinationEndBitIndex > sourceEndBitIndex)
    {
      /* Copy i and i+1 */
      sourceMask_iP1 = COM_CAST2UINT8(~(255u << (sourceEndBitIndex + 1u)));
      byteToCopy = COM_CAST2UINT8((sourceBuffer[Com_NBITNBYTE_GetEndiannesIndex(i, isBigEndian)] & sourceMask_i) >> bitOffset);
      byteToCopy |= COM_CAST2UINT8((sourceBuffer[Com_NBITNBYTE_GetEndiannesIndex(i + 1, isBigEndian)] & sourceMask_iP1) << COM_CAST2UINT8(8u - bitOffset));
    }
    else
    {
      /* Copy only i */
      byteToCopy = COM_CAST2UINT8((sourceBuffer[Com_NBITNBYTE_GetEndiannesIndex(i, isBigEndian)] & sourceMask_i) >> bitOffset);
    }

    byteToCopy = (destinationBuffer[Com_NBITNBYTE_GetEndiannesIndex(i, isBigEndian)] & COM_CAST2UINT8(~destinationMask)) | (byteToCopy & destinationMask);
    if(destinationBuffer[Com_NBITNBYTE_GetEndiannesIndex(i, isBigEndian)] != byteToCopy)
    {
      destinationHasChanged = TRUE;
      destinationBuffer[Com_NBITNBYTE_GetEndiannesIndex(i, isBigEndian)] = byteToCopy;  /* SBSW_COM_GWDESCRIPTION_RTCHECK */
    }
  }

  return destinationHasChanged;
}       /* PRQA S 6010, 6060 */ /* MD_MSR_STPTH, MD_MSR_STPAR */
#endif

#if (COM_EXISTS_LEFTSHIFT_COPYTYPEOFGWDESCRIPTIONACCESSINFO == STD_ON)
/*********************************************************************************************************************
   Com_GwDescription_LeftShiftCopy
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 ********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(boolean, COM_CODE) Com_GwDescription_LeftShiftCopy(P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) sourceBuffer,
                                                                         P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) destinationBuffer,
                                                                         uint16 destinationBufferSize, uint8 sourceStartBitIndex, uint8 bitOffset, uint16 bitLength, boolean isBigEndian)
{
  boolean destinationHasChanged = FALSE;        /* PRQA S 2981 */ /* MD_MSR_RetVal */

  uint8 byteToBeCopied;

  sint32 i = 1;

  uint8 destinationStartBitIndex = sourceStartBitIndex + bitOffset;

  uint8 sourceEndBitIndex = COM_CAST2UINT8((sourceStartBitIndex + bitLength) - 1u) % 8u;
  uint8 destinationEndBitIndex = COM_CAST2UINT8((destinationStartBitIndex + bitLength) - 1u) % 8u;

  uint16 remainingBits = bitLength;

  uint8 snippetMask = COM_CAST2UINT8(255u >> bitOffset);

  uint8 destinationMask = COM_CAST2UINT8(255u << destinationStartBitIndex);

  uint8 sourceMask = COM_CAST2UINT8(255u << sourceStartBitIndex) & COM_CAST2UINT8(255u >> bitOffset);

  if((destinationStartBitIndex + bitLength) <= 8u)
  {
    /* Destination description covers single byte. Destinations mask needs to be truncated. */
    destinationMask &= COM_CAST2UINT8(255u >> COM_CAST2UINT8(7u - destinationEndBitIndex));
    sourceMask = COM_CAST2UINT8(destinationMask >> bitOffset);

    remainingBits = 0u;
  }
  else
  {
    /* Destination description covers multiple bytes. */
    remainingBits = COM_CAST2UINT8(remainingBits - COM_CAST2UINT8(8u - destinationStartBitIndex));
  }

  byteToBeCopied = (destinationBuffer[0] & COM_CAST2UINT8(~destinationMask)) | COM_CAST2UINT8((sourceBuffer[0] & sourceMask) << bitOffset);

  if(*destinationBuffer != byteToBeCopied)
  {
    destinationHasChanged = TRUE;
    *destinationBuffer = byteToBeCopied;        /* SBSW_COM_CSL03 */
  }

  while((remainingBits > 7u) && (i < (sint32) destinationBufferSize))   /* COV_COM_GWDESCRIPTION_RTCHECK */
  {
    /* Copy full bytes to destination description. Fill leading part of destination with trailing bits of i-th source byte and copy trailing part of destination with leading bits of (i-1)-th source byte. */
    byteToBeCopied = COM_CAST2UINT8((sourceBuffer[Com_NBITNBYTE_GetEndiannesIndex(i - 1, isBigEndian)] & COM_CAST2UINT8(~snippetMask)) >> COM_CAST2UINT8(8u - bitOffset));
    byteToBeCopied |= COM_CAST2UINT8((sourceBuffer[Com_NBITNBYTE_GetEndiannesIndex(i, isBigEndian)] & snippetMask) << bitOffset);

    if(destinationBuffer[Com_NBITNBYTE_GetEndiannesIndex(i, isBigEndian)] != byteToBeCopied)
    {
      destinationHasChanged = TRUE;
      destinationBuffer[Com_NBITNBYTE_GetEndiannesIndex(i, isBigEndian)] = byteToBeCopied;      /* SBSW_COM_GWDESCRIPTION_RTCHECK */
    }

    i++;
    remainingBits = COM_CAST2UINT8(remainingBits - 8u);
  }

  if((remainingBits > 0u) && (i < (sint32) destinationBufferSize))      /* COV_COM_GWDESCRIPTION_RTCHECK */
  {     /* if source covers multiple bytes */
    uint8 finalByteMask;
    destinationMask = COM_CAST2UINT8(255u << (destinationEndBitIndex + 1u));

    byteToBeCopied = destinationBuffer[Com_NBITNBYTE_GetEndiannesIndex(i, isBigEndian)];
    if(destinationEndBitIndex < sourceEndBitIndex)
    {
      /* Next Byte */
      finalByteMask = COM_CAST2UINT8(COM_CAST2UINT8(255u >> COM_CAST2UINT8(8u - (uint8) remainingBits)) << COM_CAST2UINT8((1u + sourceEndBitIndex) - (uint8) remainingBits));
    }
    else
    {
      /* Same byte */
      uint8 sourceMaske = COM_CAST2UINT8(255u >> COM_CAST2UINT8(7u - sourceEndBitIndex));
      finalByteMask = COM_CAST2UINT8(~snippetMask);
      byteToBeCopied = (byteToBeCopied & destinationMask) | COM_CAST2UINT8((sourceBuffer[Com_NBITNBYTE_GetEndiannesIndex(i, isBigEndian)] & sourceMaske) << bitOffset);

      destinationMask = COM_CAST2UINT8(255u << bitOffset);
    }
    byteToBeCopied = (byteToBeCopied & destinationMask) | COM_CAST2UINT8((sourceBuffer[Com_NBITNBYTE_GetEndiannesIndex(i - 1, isBigEndian)] & finalByteMask) >> COM_CAST2UINT8(8u - bitOffset));

    if(destinationBuffer[Com_NBITNBYTE_GetEndiannesIndex(i, isBigEndian)] != byteToBeCopied)
    {
      destinationHasChanged = TRUE;
      destinationBuffer[Com_NBITNBYTE_GetEndiannesIndex(i, isBigEndian)] = byteToBeCopied;      /* SBSW_COM_GWDESCRIPTION_RTCHECK */
    }
  }

  return destinationHasChanged;
}       /* PRQA S 6060 */ /* MD_MSR_STPAR */
#endif

#if (COM_GWEVENTCACHE == STD_ON)
/**********************************************************************************************************************
  Com_GwDescription_EnterExclusiveArea
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_GwDescription_EnterExclusiveArea(void)
{
  /* #10 Enter the gw description routing exclusive area */
  SchM_Enter_Com_COM_EXCLUSIVE_AREA_BOTH();
}

/**********************************************************************************************************************
  Com_GwDescription_ExitExclusiveArea
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_GwDescription_ExitExclusiveArea(void)
{
  /* #05 Reload the counter with the threshold value */
  Com_SetGatewayDescriptionProcessingISRLockCounter(Com_GetGatewayDescriptionProcessingISRLockThreshold());     /* SBSW_COM_CSL_VAR_ACCESS */
  /* #10 Exit the gw description routing exclusive area */
  SchM_Exit_Com_COM_EXCLUSIVE_AREA_BOTH();
}

/**********************************************************************************************************************
  Com_GwDescription_ThresholdCheck
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_GwDescription_ThresholdCheck(void)
{
  if(Com_GetGatewayDescriptionProcessingISRLockCounter() > 0u)
  {
    Com_DecGatewayDescriptionProcessingISRLockCounter();        /* SBSW_COM_CSL_VAR_ACCESS */
  }
  else
  {
    Com_GwDescription_ExitExclusiveArea();
    Com_GwDescription_EnterExclusiveArea();
  }
}
#endif


/**********************************************************************************************************************
  GLOBAL FUNCTIONS
**********************************************************************************************************************/

#if (COM_GWTXPDUDESCRIPTIONINFOUSEDOFRXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxProcessing_GwDescriptionEvent
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
 *
 *
 **********************************************************************************************************************/
FUNC(void, COM_CODE) Com_RxProcessing_GwDescriptionEvent(PduIdType rxComPduId, P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr)
{
  Com_GwTxPduDescriptionInfoEndIdxOfRxPduInfoType gwTxPduIdx = Com_GetGwTxPduDescriptionInfoStartIdxOfRxPduInfo(rxComPduId);
  /* #20 Iterate over all corresponding destination TxPDUs */
  for(; gwTxPduIdx < Com_GetGwTxPduDescriptionInfoEndIdxOfRxPduInfo(rxComPduId); gwTxPduIdx++)
  {
    Com_GwDescriptionAccessInfoEndIdxOfGwTxPduDescriptionInfoType gwDescrAccessIdx = Com_GetGwDescriptionAccessInfoStartIdxOfGwTxPduDescriptionInfo(gwTxPduIdx);

    Com_TxPduInfoIdxOfGwDescriptionAccessInfoType txPduID = Com_GetTxPduInfoIdxOfGwDescriptionAccessInfo(gwDescrAccessIdx);

    boolean gwDescriptionUpdated = FALSE;       /* PRQA S 2981 */ /* MD_MSR_RetVal */
    boolean sendTrigger = FALSE;        /* PRQA S 2981 */ /* MD_MSR_RetVal */
    boolean withoutRepetitionFlag = TRUE;       /* PRQA S 2981 */ /* MD_MSR_RetVal */

    /* #30 Process all descriptions that correspond to the same destination txPdu */
    for(; gwDescrAccessIdx < Com_GetGwDescriptionAccessInfoEndIdxOfGwTxPduDescriptionInfo(gwTxPduIdx); gwDescrAccessIdx++)
    {
      /* #31 Check if the source description is fully contained in received buffer */
      if(PduInfoPtr->SduLength >= Com_GetValidDlcOfGwDescriptionAccessInfo(gwDescrAccessIdx))
      {
# if (COM_RXUBMASKUSEDOFGWDESCRIPTIONACCESSINFO == STD_ON)
        /* #35 Check if the source description was updated */
        if(Com_RxProcessing_CheckGwDescriptionUB(gwDescrAccessIdx, PduInfoPtr) == TRUE) /* SBSW_COM_FCTCALL_WITH_P2CONST */
# endif
        {
          switch (Com_RxProcessing_ProcessDestinationDescription(PduInfoPtr->SduDataPtr, gwDescrAccessIdx))     /* SBSW_COM_FCTCALL_WITH_P2CONST */
          {
            case COM_TRANSMIT_TRIGGERWITHOUTREP:
              sendTrigger = TRUE;       /* #40 Set transmit flag if at least one description fulfills the transmit condition */
              break;
            case COM_TRANSMIT_TRIGGER:
              sendTrigger = TRUE;
              withoutRepetitionFlag = FALSE;    /* #50 Set repetition flag if at least one description requires repetitve transmit */
              break;
            default:   /* COV_COM_MISRA */
              break;
          }

          gwDescriptionUpdated = TRUE;
        }
      }
    }

# if (COM_GWTIMEOUTINFO == STD_ON)
    /* #55 If any gateway description belonging to same source and destination Pdu was updated */
    if(gwDescriptionUpdated == TRUE)
    {
      /* #60 Handle Gw Timeout if configured */
      Com_GwTout_Event((PduIdType) txPduID);
    }
# endif
# if ((COM_DIRECTOFTXMODETRUE == STD_ON) || (COM_DIRECTOFTXMODEFALSE == STD_ON))
    /* #70 If transmit condition is fulfilled (transmit flag is set) */
    if(sendTrigger == TRUE)
    {
      Com_TypeOfGwDescriptionAccessInfoType typeOfDescription = Com_GetTypeOfGwDescriptionAccessInfo(Com_GetGwDescriptionAccessInfoStartIdxOfGwTxPduDescriptionInfo(gwTxPduIdx));
      /* #80 Trigger the transmission of the PDU */
      Com_RxProcessing_GwDescriptionTransmit((PduIdType) txPduID, Com_IsGwDestinationDescriptionTypeImmediate(typeOfDescription), withoutRepetitionFlag);       /* COV_COM_IMMEDIATE_DESTINATION_DESCRIPTION */
    }
# endif
    COM_DUMMY_STATEMENT(withoutRepetitionFlag); /* PRQA S 1338, 2983, 3112, 2982 */ /* MD_MSR_DummyStmt, MD_MSR_DummyStmt, MD_MSR_DummyStmt, MD_Com_2982 */ /* lint -e{438} */
    COM_DUMMY_STATEMENT(sendTrigger);   /* PRQA S 1338, 2983, 3112, 2982 */ /* MD_MSR_DummyStmt, MD_MSR_DummyStmt, MD_MSR_DummyStmt, MD_Com_2982 */ /* lint -e{438} */
    COM_DUMMY_STATEMENT(gwDescriptionUpdated);  /* PRQA S 1338, 2983, 3112, 2982 */ /* MD_MSR_DummyStmt, MD_MSR_DummyStmt, MD_MSR_DummyStmt, MD_Com_2982 */ /* lint -e{438} */
  }
}       /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if (COM_GWINFOENDIDXOFRXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_SignalGw_InitRxIpdu
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_SignalGw_InitRxIpdu(PduIdType ComPduId)
{
  /* #10 Reset all gateway event flags of the passed ComIPdu */
  Com_GwInfoEndIdxOfRxPduInfoType idxGwInfo = Com_GetGwInfoStartIdxOfRxPduInfo(ComPduId);
  for(; idxGwInfo < Com_GetGwInfoEndIdxOfRxPduInfo(ComPduId); idxGwInfo++)
  {
    Com_SetGwEvent(idxGwInfo, FALSE);   /* SBSW_COM_CSL02 */
  }
}
#endif

#if (COM_GWINFOUSEDOFRXSIGINFO == STD_ON)
/**********************************************************************************************************************
  Com_SignalGw_SigEvent
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_SignalGw_SigEvent(Com_RxSigInfoIterType idxRxSigInfo)
{
  /* #10 If the passed signal is routed, set the related gateway event flag */
  if(Com_IsGwInfoUsedOfRxSigInfo(idxRxSigInfo)) /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    Com_SetGwEvent(Com_GetGwInfoIdxOfRxSigInfo(idxRxSigInfo), TRUE);    /* SBSW_COM_CSL02_CSL03 */
  }
}
#endif

#if (COM_GWINFOUSEDOFRXSIGGRPINFO == STD_ON)
/**********************************************************************************************************************
  Com_SignalGw_SigGrpEvent
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_SignalGw_SigGrpEvent(Com_RxSigGrpInfoIterType idxRxSigGrpInfo)
{
  /* #10 If the passed signal group is routed, set the related gateway event flag */
  if(Com_IsGwInfoUsedOfRxSigGrpInfo(idxRxSigGrpInfo))   /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    Com_SetGwEvent(Com_GetGwInfoIdxOfRxSigGrpInfo(idxRxSigGrpInfo), TRUE);      /* SBSW_COM_CSL02_CSL03 */
  }
}
#endif

#if (COM_GWSIGMAPPINGENDIDXOFGWINFO == STD_ON)
/**********************************************************************************************************************
  Com_MainFunction_SignalRoutings
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_MainFunction_SignalRoutings(Com_GwInfoIterType idxGwInfo)
{
  /* #10 Iterate over all signal depending gateway mappings of the passed gateway info */
  Com_GwSigMappingEndIdxOfGwInfoType idxGwSigMapping = Com_GetGwSigMappingStartIdxOfGwInfo(idxGwInfo);
  for(; idxGwSigMapping < Com_GetGwSigMappingEndIdxOfGwInfo(idxGwInfo); idxGwSigMapping++)
  {
    Com_SignalIdType idxRxAccessInfo = (Com_SignalIdType) Com_GetRxAccessInfoIdxOfGwSigMapping(idxGwSigMapping);

    Com_TxSigInfoIterType txSigId = (Com_TxSigInfoIterType) Com_GetTxSigIdOfGwSigMapping(idxGwSigMapping);

    if(txSigId < Com_GetSizeOfTxSigInfo())      /* COV_COM_MISRA */
    {
# if (COM_INVALIDHNDOFTXSIGINFO == STD_ON)
      if(!Com_IsInvalidHndOfTxSigInfo(txSigId)) /* COV_COM_DEFENSIVE_PROGRAMMING */
# endif
      {
# if (COM_GWTIMEOUTINFO == STD_ON)
        /* #20 Start cyclic transmission for periodic I-PDUs with a configured GW Timeout and reload gw Timeout counter */
        Com_GwTout_Event((PduIdType) Com_GetTxPduInfoIdxOfTxSigInfo(txSigId));
# endif
# if ((COM_MINPROCGWBUFFERUSEDOFRXACCESSINFO == STD_ON) || (COM_MINPROCGWBUFFERARRAYBASEDBUFFERUSEDOFRXACCESSINFO == STD_ON))
        Com_MainFunction_SignalRoutings_SendSignalWithMinimalProcessing(idxRxAccessInfo, txSigId);
# else
        Com_MainFunction_SignalRoutings_SendSignal(idxRxAccessInfo, txSigId);
# endif
      }
    }
    COM_DUMMY_STATEMENT(idxRxAccessInfo);       /* PRQA S 1338, 2983, 3112, 2982 */ /* MD_MSR_DummyStmt, MD_MSR_DummyStmt, MD_MSR_DummyStmt, MD_Com_2982 */ /* lint -e{438} */
  }
}
#endif


#if (((COM_GWSIGMAPPINGENDIDXOFGWINFO == STD_ON) || (COM_GWSIGGRPMAPPINGENDIDXOFGWINFO == STD_ON)) && (COM_MINPROCGWBUFFERUSEDOFRXACCESSINFO == STD_OFF && COM_MINPROCGWBUFFERARRAYBASEDBUFFERUSEDOFRXACCESSINFO == STD_OFF))
/**********************************************************************************************************************
  Com_MainFunction_SignalRoutings_SendSignal
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_MainFunction_SignalRoutings_SendSignal(Com_SignalIdType idxRxAccessInfo, Com_TxSigInfoIterType txSigId)
{
  /* Check for buffer is not required as there is always a buffer configured. Removed check Com_IsBufferUsedOfRxAccessInfo */

  /* #10 Send signal with the received value, the source buffer of the value depends on the signal ApplType */
  switch (Com_GetApplTypeOfRxAccessInfo(idxRxAccessInfo))
  {
# if (COM_ROUTINGBUFFERUSEDOFRXACCESSINFO == STD_ON)
#  if (COM_RXSIGBUFFERUINT8 == STD_ON)
    case COM_UINT8_APPLTYPEOFRXACCESSINFO:     /* COV_COM_APPLTYPEOFRXACCESSINFO_GW_ROUTING */
    {
      (void) Com_SendSignal_Processing(txSigId, Com_GetAddrRxSigBufferUInt8(Com_GetRoutingBufferIdxOfRxAccessInfo(idxRxAccessInfo)), 0);        /* PRQA S 0315 */ /* MD_Com_0314_0315 */ /* SBSW_COM_FCTCALL_WITH_P2CONST */
      break;
    }
#  endif
#  if (COM_RXSIGBUFFERSINT8 == STD_ON)
    case COM_SINT8_APPLTYPEOFRXACCESSINFO:     /* COV_COM_APPLTYPEOFRXACCESSINFO_GW_ROUTING */
    {
      (void) Com_SendSignal_Processing(txSigId, Com_GetAddrRxSigBufferSInt8(Com_GetRoutingBufferIdxOfRxAccessInfo(idxRxAccessInfo)), 0);        /* PRQA S 0315 */ /* MD_Com_0314_0315 */ /* SBSW_COM_FCTCALL_WITH_P2CONST */
      break;
    }
#  endif
#  if (COM_RXSIGBUFFERUINT16 == STD_ON)
    case COM_UINT16_APPLTYPEOFRXACCESSINFO:    /* COV_COM_APPLTYPEOFRXACCESSINFO_GW_ROUTING */
    {
      (void) Com_SendSignal_Processing(txSigId, Com_GetAddrRxSigBufferUInt16(Com_GetRoutingBufferIdxOfRxAccessInfo(idxRxAccessInfo)), 0);       /* PRQA S 0315 */ /* MD_Com_0314_0315 */ /* SBSW_COM_FCTCALL_WITH_P2CONST */
      break;
    }
#  endif
#  if (COM_RXSIGBUFFERSINT16 == STD_ON)
    case COM_SINT16_APPLTYPEOFRXACCESSINFO:    /* COV_COM_APPLTYPEOFRXACCESSINFO_GW_ROUTING */
    {
      (void) Com_SendSignal_Processing(txSigId, Com_GetAddrRxSigBufferSInt16(Com_GetRoutingBufferIdxOfRxAccessInfo(idxRxAccessInfo)), 0);       /* PRQA S 0315 */ /* MD_Com_0314_0315 */ /* SBSW_COM_FCTCALL_WITH_P2CONST */
      break;
    }
#  endif
#  if (COM_RXSIGBUFFERUINT32 == STD_ON)
    case COM_UINT32_APPLTYPEOFRXACCESSINFO:    /* COV_COM_APPLTYPEOFRXACCESSINFO_GW_ROUTING */
    {
      (void) Com_SendSignal_Processing(txSigId, Com_GetAddrRxSigBufferUInt32(Com_GetRoutingBufferIdxOfRxAccessInfo(idxRxAccessInfo)), 0);       /* PRQA S 0315 */ /* MD_Com_0314_0315 */ /* SBSW_COM_FCTCALL_WITH_P2CONST */
      break;
    }
#  endif
#  if (COM_RXSIGBUFFERSINT32 == STD_ON)
    case COM_SINT32_APPLTYPEOFRXACCESSINFO:    /* COV_COM_APPLTYPEOFRXACCESSINFO_GW_ROUTING */
    {
      (void) Com_SendSignal_Processing(txSigId, Com_GetAddrRxSigBufferSInt32(Com_GetRoutingBufferIdxOfRxAccessInfo(idxRxAccessInfo)), 0);       /* PRQA S 0315 */ /* MD_Com_0314_0315 */ /* SBSW_COM_FCTCALL_WITH_P2CONST */
      break;
    }
#  endif
#  if (COM_RXSIGBUFFERUINT64 == STD_ON)
    case COM_UINT64_APPLTYPEOFRXACCESSINFO:    /* COV_COM_APPLTYPEOFRXACCESSINFO_GW_ROUTING */
    {
      (void) Com_SendSignal_Processing(txSigId, Com_GetAddrRxSigBufferUInt64(Com_GetRoutingBufferIdxOfRxAccessInfo(idxRxAccessInfo)), 0);       /* PRQA S 0315 */ /* MD_Com_0314_0315 */ /* SBSW_COM_FCTCALL_WITH_P2CONST */
      break;
    }
#  endif
#  if (COM_RXSIGBUFFERSINT64 == STD_ON)
    case COM_SINT64_APPLTYPEOFRXACCESSINFO:    /* COV_COM_APPLTYPEOFRXACCESSINFO_GW_ROUTING */
    {
      (void) Com_SendSignal_Processing(txSigId, Com_GetAddrRxSigBufferSInt64(Com_GetRoutingBufferIdxOfRxAccessInfo(idxRxAccessInfo)), 0);       /* PRQA S 0315 */ /* MD_Com_0314_0315 */ /* SBSW_COM_FCTCALL_WITH_P2CONST */
      break;
    }
#  endif
#  if (COM_RXSIGBUFFERFLOAT32 == STD_ON)
    case COM_FLOAT32_APPLTYPEOFRXACCESSINFO:   /* COV_COM_APPLTYPEOFRXACCESSINFO_GW_ROUTING */
    {
      (void) Com_SendSignal_Processing(txSigId, Com_GetAddrRxSigBufferFloat32(Com_GetRoutingBufferIdxOfRxAccessInfo(idxRxAccessInfo)), 0);      /* PRQA S 0315 */ /* MD_Com_0314_0315 */ /* SBSW_COM_FCTCALL_WITH_P2CONST */
      break;
    }
#  endif
#  if (COM_RXSIGBUFFERFLOAT64 == STD_ON)
    case COM_FLOAT64_APPLTYPEOFRXACCESSINFO:   /* COV_COM_APPLTYPEOFRXACCESSINFO_GW_ROUTING */
    {
      (void) Com_SendSignal_Processing(txSigId, Com_GetAddrRxSigBufferFloat64(Com_GetRoutingBufferIdxOfRxAccessInfo(idxRxAccessInfo)), 0);      /* PRQA S 0315 */ /* MD_Com_0314_0315 */ /* SBSW_COM_FCTCALL_WITH_P2CONST */
      break;
    }
#  endif
# endif
# if (COM_RXSIGBUFFERARRAYBASEDROUTINGBUFFERUSEDOFRXACCESSINFO == STD_ON)
    case COM_UINT8_N_APPLTYPEOFRXACCESSINFO:   /* COV_COM_APPLTYPEOFRXACCESSINFO_GW_ROUTING */
    {
      (void) Com_SendSignal_Processing(txSigId, Com_GetAddrRxSigBufferArrayBased(Com_GetRxSigBufferArrayBasedRoutingBufferStartIdxOfRxAccessInfo(idxRxAccessInfo)), 0); /* PRQA S 0315 */ /* MD_Com_0314_0315 */ /* SBSW_COM_FCTCALL_WITH_P2CONST */
      break;
    }
# endif
# if (COM_EXISTS_ZEROBIT_APPLTYPEOFRXACCESSINFO == STD_ON)
    case COM_ZEROBIT_APPLTYPEOFRXACCESSINFO:   /* COV_COM_APPLTYPEOFRXACCESSINFO_GW_ROUTING */
    {
      (void) Com_SendSignal_Processing(txSigId, NULL_PTR, 0);   /* SBSW_COM_FCTCALL_WITH_P2CONST */
      break;
    }
# endif
    default:   /* COV_COM_MISRA */
      break;
  }
}       /* PRQA S 6030 */ /* MD_MSR_STCYC */
#endif


#if ((COM_MINPROCGWBUFFERUSEDOFRXACCESSINFO == STD_ON) || (COM_MINPROCGWBUFFERARRAYBASEDBUFFERUSEDOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
  Com_MainFunction_SignalRoutings_SendSignalWithMinimalProcessing
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_MainFunction_SignalRoutings_SendSignalWithMinimalProcessing(Com_SignalIdType idxRxAccessInfo, Com_TxSigInfoIterType txSigId)
{
  /* #10 Send signal with the received value, the source buffer of the value depends on the signal ApplType */
  switch (Com_GetApplTypeOfRxAccessInfo(idxRxAccessInfo))
  {
# if (COM_MINPROCGWBUFFERUINT8 == STD_ON)
    case COM_UINT8_APPLTYPEOFRXACCESSINFO:
    {
      (void) Com_SendSignal_Processing(txSigId, Com_GetAddrMinProcGwBufferUInt8(Com_GetMinProcGwBufferIdxOfRxAccessInfo(idxRxAccessInfo)), 0);  /* PRQA S 0315 */ /* MD_Com_0314_0315 */ /* SBSW_COM_FCTCALL_WITH_P2CONST */
      break;
    }
# endif
# if (COM_MINPROCGWBUFFERSINT8 == STD_ON)
    case COM_SINT8_APPLTYPEOFRXACCESSINFO:
    {
      (void) Com_SendSignal_Processing(txSigId, Com_GetAddrMinProcGwBufferSInt8(Com_GetMinProcGwBufferIdxOfRxAccessInfo(idxRxAccessInfo)), 0);  /* PRQA S 0315 */ /* MD_Com_0314_0315 */ /* SBSW_COM_FCTCALL_WITH_P2CONST */
      break;
    }
# endif
# if (COM_MINPROCGWBUFFERUINT16 == STD_ON)
    case COM_UINT16_APPLTYPEOFRXACCESSINFO:
    {
      (void) Com_SendSignal_Processing(txSigId, Com_GetAddrMinProcGwBufferUInt16(Com_GetMinProcGwBufferIdxOfRxAccessInfo(idxRxAccessInfo)), 0); /* PRQA S 0315 */ /* MD_Com_0314_0315 */ /* SBSW_COM_FCTCALL_WITH_P2CONST */
      break;
    }
# endif
# if (COM_MINPROCGWBUFFERSINT16 == STD_ON)
    case COM_SINT16_APPLTYPEOFRXACCESSINFO:
    {
      (void) Com_SendSignal_Processing(txSigId, Com_GetAddrMinProcGwBufferSInt16(Com_GetMinProcGwBufferIdxOfRxAccessInfo(idxRxAccessInfo)), 0); /* PRQA S 0315 */ /* MD_Com_0314_0315 */ /* SBSW_COM_FCTCALL_WITH_P2CONST */
      break;
    }
# endif
# if (COM_MINPROCGWBUFFERUINT32 == STD_ON)
    case COM_UINT32_APPLTYPEOFRXACCESSINFO:
    {
      (void) Com_SendSignal_Processing(txSigId, Com_GetAddrMinProcGwBufferUInt32(Com_GetMinProcGwBufferIdxOfRxAccessInfo(idxRxAccessInfo)), 0); /* PRQA S 0315 */ /* MD_Com_0314_0315 */ /* SBSW_COM_FCTCALL_WITH_P2CONST */
      break;
    }
# endif
# if (COM_MINPROCGWBUFFERSINT32 == STD_ON)
    case COM_SINT32_APPLTYPEOFRXACCESSINFO:
    {
      (void) Com_SendSignal_Processing(txSigId, Com_GetAddrMinProcGwBufferSInt32(Com_GetMinProcGwBufferIdxOfRxAccessInfo(idxRxAccessInfo)), 0); /* PRQA S 0315 */ /* MD_Com_0314_0315 */ /* SBSW_COM_FCTCALL_WITH_P2CONST */
      break;
    }
# endif
# if (COM_MINPROCGWBUFFERUINT64 == STD_ON)
    case COM_UINT64_APPLTYPEOFRXACCESSINFO:
    {
      (void) Com_SendSignal_Processing(txSigId, Com_GetAddrMinProcGwBufferUInt64(Com_GetMinProcGwBufferIdxOfRxAccessInfo(idxRxAccessInfo)), 0); /* PRQA S 0315 */ /* MD_Com_0314_0315 */ /* SBSW_COM_FCTCALL_WITH_P2CONST */
      break;
    }
# endif
# if (COM_MINPROCGWBUFFERSINT64 == STD_ON)
    case COM_SINT64_APPLTYPEOFRXACCESSINFO:
    {
      (void) Com_SendSignal_Processing(txSigId, Com_GetAddrMinProcGwBufferSInt64(Com_GetMinProcGwBufferIdxOfRxAccessInfo(idxRxAccessInfo)), 0); /* PRQA S 0315 */ /* MD_Com_0314_0315 */ /* SBSW_COM_FCTCALL_WITH_P2CONST */
      break;
    }
# endif
# if (COM_MINPROCGWBUFFERFLOAT32 == STD_ON)
    case COM_FLOAT32_APPLTYPEOFRXACCESSINFO:
    {
      (void) Com_SendSignal_Processing(txSigId, Com_GetAddrMinProcGwBufferFloat32(Com_GetMinProcGwBufferIdxOfRxAccessInfo(idxRxAccessInfo)), 0);        /* PRQA S 0315 */ /* MD_Com_0314_0315 */ /* SBSW_COM_FCTCALL_WITH_P2CONST */
      break;
    }
# endif
# if (COM_MINPROCGWBUFFERFLOAT64 == STD_ON)
    case COM_FLOAT64_APPLTYPEOFRXACCESSINFO:
    {
      (void) Com_SendSignal_Processing(txSigId, Com_GetAddrMinProcGwBufferFloat64(Com_GetMinProcGwBufferIdxOfRxAccessInfo(idxRxAccessInfo)), 0);        /* PRQA S 0315 */ /* MD_Com_0314_0315 */ /* SBSW_COM_FCTCALL_WITH_P2CONST */
      break;
    }
# endif
# if (COM_MINPROCGWBUFFERARRAYBASED == STD_ON)
    case COM_UINT8_N_APPLTYPEOFRXACCESSINFO:
    {
      (void) Com_SendSignal_Processing(txSigId, Com_GetAddrMinProcGwBufferArrayBased(Com_GetMinProcGwBufferArrayBasedBufferStartIdxOfRxAccessInfo(idxRxAccessInfo)), 0);        /* PRQA S 0315 */ /* MD_Com_0314_0315 */ /* SBSW_COM_FCTCALL_WITH_P2CONST */
      break;
    }
# endif
# if (COM_EXISTS_ZEROBIT_APPLTYPEOFRXACCESSINFO == STD_ON)
    case COM_ZEROBIT_APPLTYPEOFRXACCESSINFO:
    {
      (void) Com_SendSignal_Processing(txSigId, NULL_PTR, 0);   /* SBSW_COM_FCTCALL_WITH_P2CONST */
      break;
    }
# endif
    default:   /* COV_COM_MISRA */
      break;
  }
}       /* PRQA S 6030 */ /* MD_MSR_STCYC */
#endif




#if (COM_GWSIGGRPMAPPINGENDIDXOFGWINFO == STD_ON)
/**********************************************************************************************************************
  Com_MainFunction_SignalGroupRoutings
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_MainFunction_SignalGroupRoutings(Com_GwInfoIterType idxGwInfo)
{
  P2CONST(uint8, AUTOMATIC, COM_APPL_VAR) shdBuffer = NULL_PTR;
  /* #10 Iterate over all signal group depending gateway mappings of the passed gateway info */
  Com_GwSigGrpMappingEndIdxOfGwInfoType idxGwSigGrpMapping = Com_GetGwSigGrpMappingStartIdxOfGwInfo(idxGwInfo);
  for(; idxGwSigGrpMapping < Com_GetGwSigGrpMappingEndIdxOfGwInfo(idxGwInfo); idxGwSigGrpMapping++)
  {
    Com_SignalGroupIdType txSigGrpId = Com_GetTxSigGrpIdOfGwSigGrpMapping(idxGwSigGrpMapping);
    Com_GwGrpSigMappingEndIdxOfGwSigGrpMappingType idxGwGrpSigMapping = Com_GetGwGrpSigMappingStartIdxOfGwSigGrpMapping(idxGwSigGrpMapping);

# if (COM_GWTIMEOUTINFO == STD_ON)
    /* #20 Start cyclic transmission for periodic I-PDUs with a configured GW Timeout and reload gw Timeout counter */
    Com_GwTout_Event((PduIdType) Com_GetTxPduInfoIdxOfTxSigGrpInfo(txSigGrpId));
# endif

    /* #30 Iterate over all related group signal mappings */
    for(; idxGwGrpSigMapping < Com_GetGwGrpSigMappingEndIdxOfGwSigGrpMapping(idxGwSigGrpMapping); idxGwGrpSigMapping++)
    {
      Com_SignalIdType idxRxAccessInfo = (Com_SignalIdType) Com_GetRxAccessInfoIdxOfGwGrpSigMapping(idxGwGrpSigMapping);
      Com_TxSigInfoIterType txSigId = (Com_TxSigInfoIterType) Com_GetTxSigIdOfGwGrpSigMapping(idxGwGrpSigMapping);

      if(txSigId < Com_GetSizeOfTxSigInfo())    /* COV_COM_MISRA */
      {
# if (COM_INVALIDHNDOFTXSIGINFO == STD_ON)
        if(!Com_IsInvalidHndOfTxSigInfo(txSigId)) /* COV_COM_DEFENSIVE_PROGRAMMING */
# endif
        {
          /* Check for buffer is not required as there is always a buffer configured. Removed check Com_IsBufferUsedOfRxAccessInfo */
          /* #40 Send signal with the value of the related shadow buffer, the buffer depends on the ApplType of the ComGroupSignal */
# if ((COM_MINPROCGWBUFFERUSEDOFRXACCESSINFO == STD_ON) || (COM_MINPROCGWBUFFERARRAYBASEDBUFFERUSEDOFRXACCESSINFO == STD_ON))
          Com_MainFunction_SignalRoutings_SendSignalWithMinimalProcessing(idxRxAccessInfo, txSigId);
# else
          Com_MainFunction_SignalRoutings_SendSignal(idxRxAccessInfo, txSigId); /* SBSW_COM_FCT_PTR_CALL_CSL03 */
# endif
        }
      }
      COM_DUMMY_STATEMENT(idxRxAccessInfo);     /* PRQA S 1338, 2983, 3112, 2982 */ /* MD_MSR_DummyStmt, MD_MSR_DummyStmt, MD_MSR_DummyStmt, MD_Com_2982 */ /* lint -e{438} */
    }
    /* #50 Call Com_SendSignalGroup for the related signal group with the respective shadowBuffer */
# if (COM_TXBUFFERUSEDOFTXSIGGRPINFO == STD_ON)
    if(Com_IsTxBufferUsedOfTxSigGrpInfo(txSigGrpId))    /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
    {
      shdBuffer = Com_GetAddrTxBuffer(Com_GetTxBufferStartIdxOfTxSigGrpInfo(txSigGrpId));
    }
# endif
    (void) Com_SendSignalGroup_Processing(txSigGrpId, shdBuffer);       /* SBSW_COM_FCTCALL_WITH_P2CONST */
  }
}       /* PRQA S 6030 */ /* MD_MSR_STCYC */
#endif

#if (COM_GWEVENTCACHE == STD_ON)
/**********************************************************************************************************************
  Com_MainFunction_GwDescription
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_MainFunction_GwDescription(void)
{
  /* #10 Iterate over all ComIPdus inside the cache */
  Com_GwDescription_EnterExclusiveArea();

  while(Com_GetGwEventCacheIndex() > 0u)
  {
    PduIdType rxPdu;

    Com_HandleRxDeferredGwDescriptionType gwDeferredHandleSize;

    Com_DecGwEventCacheIndex(); /* SBSW_COM_CSL_VAR_ACCESS */

    rxPdu = Com_GetGwEventCache(Com_GetGwEventCacheIndex());

    gwDeferredHandleSize = Com_GetHandleRxDeferredGwDescription(Com_GetHandleRxDeferredGwDescriptionIdxOfRxPduInfo(rxPdu));

    /* #20 If gw flag has not been reset */
    if(gwDeferredHandleSize > 0u)
    {
      PduInfoType PduInfo;

      PduInfo.SduLength = (PduLengthType) (gwDeferredHandleSize - 1u);
      PduInfo.SduDataPtr = Com_GetAddrRxDefPduBuffer(Com_GetRxDefPduBufferStartIdxOfRxPduInfo(rxPdu));

      /* #30 Process gateway description */
      Com_RxProcessing_GwDescriptionEvent(rxPdu, &PduInfo);     /* SBSW_COM_FCTCALL_STACKPTR */
    }

    /* #40 Reset deferred gw description flag */
    Com_SetHandleRxDeferredGwDescription(Com_GetHandleRxDeferredGwDescriptionIdxOfRxPduInfo(rxPdu), 0); /* SBSW_COM_CSL03 */

    Com_GwDescription_ThresholdCheck();
  }

  Com_GwDescription_ExitExclusiveArea();
}
#endif

#define COM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */   /* MD_MSR_MemMap */

/***********************************************************************************************************************
 *  MISRA JUSTIFICATIONS
 **********************************************************************************************************************/
/* *INDENT-OFF* */
/* Justifications for module-specific MISRA deviations:
   MD_Com_0314_0315: Misra Dir 1.1
     Reason:     A void pointer is used because it depends on the configuration of which type the pointer is. It is easier to use a void pointer insead of different functions for different pointer types.
     Risk:       No risk, because the underlying pointer type is known via the configuration.
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
/* *INDENT-ON* */

/**********************************************************************************************************************
 *  END OF FILE: Com_Gateway.c
 *********************************************************************************************************************/
