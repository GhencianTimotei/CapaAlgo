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
 *         File:  IpduM_Mux.c
 *      Project:  MICROSAR IpduM
 *       Module:  Implementation
 *    Generator:  CFG5
 *
 *  Description:  Microsar IPDU Multiplexer source file
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the VERSION CHECK below.
 *********************************************************************************************************************/

#define IPDUM_MUX_SOURCE
/**********************************************************************************************************************
 * MISRA JUSTIFICATION
 *********************************************************************************************************************/

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
#include "IpduM.h"
#include "IpduM_Mux.h"
#include "SchM_IpduM.h"
#include "vstdlib.h"

#if (IPDUM_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif
#if ((IPDUM_TXBUFFERSTARTIDXOFTXPATHWAY == STD_ON) || (IPDUM_RXMUXPDU == STD_ON) || (IPDUM_CONTAINERRXBUFFER == STD_ON) || (IPDUM_CONTAINERTXBUFFER == STD_ON))      /* COV_IPDUM_EMPTY_CONFIG */
# include "PduR_IpduM.h"
#endif
#if(IPDUM_DIRECT_COM_INVOCATION == STD_ON)
# include "Com_Cbk.h"
#endif

/**********************************************************************************************************************
  LOCAL CONSTANT MACROS
**********************************************************************************************************************/
#define IPDUM_RESET                             0u

#if(IPDUM_DIRECT_COM_INVOCATION == STD_ON)
# if(IPDUM_UL_TRIGGER_TRANSMIT_API == STD_ON)
#  define PduR_IpduMTriggerTransmit   Com_TriggerTransmit    
# endif
# if(IPDUM_UL_TX_CONFIRMATION_API == STD_ON)
#  define PduR_IpduMTxConfirmation    Com_TxConfirmation    
# endif
# define PduR_IpduMRxIndication      Com_RxIndication       
#endif

/**********************************************************************************************************************
  LOCAL FUNCTION MACROS
**********************************************************************************************************************/
#if (IPDUM_DEV_ERROR_REPORT == STD_ON)                                     
# define IpduM_Det_ReportError(ApiId, ErrorCode)    (void)Det_ReportError(IPDUM_MODULE_ID, 0, (ApiId), (ErrorCode))   /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#endif

/**********************************************************************************************************************
  LOCAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/

/**********************************************************************************************************************
  LOCAL DATA PROTOTYPES
**********************************************************************************************************************/

/**********************************************************************************************************************
  LOCAL DATA
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL DATA
**********************************************************************************************************************/

/**********************************************************************************************************************
  LOCAL FUNCTION PROTOTYPES
**********************************************************************************************************************/
#define IPDUM_START_SEC_CODE
#include "MemMap.h"    /* PRQA S 5087 */        /*  MD_MSR_MemMap */

#if (IPDUM_RESTSEGMENT == STD_ON)
/*******************************************************************************************
*  IpduM_WriteMuxFillerSegments()
*******************************************************************************************/
/*! \brief        Writes filler segments for imperfectly overlapping dynamic parts in PDUs
 *  \details      -
 *  \param[in]    segmentStartIdx
 *  \param[in]    segmentEndIdx
 *  \param[in]    txPathwayIdx
 *  \param[out]   destPduInfoPtr    PduInfoPtr to target buffer
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE for different segments
 *  \synchronous  TRUE
*******************************************************************************************/
LOCAL_INLINE FUNC(void,
                  IPDUM_CODE) IpduM_WriteMuxFillerSegments(IpduM_RestSegmentIterType segmentStartIdx,
                                                 IpduM_RestSegmentIterType segmentEndIdx, IpduM_CTxPathwayIterType txPathwayIdx, P2VAR(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) destPduInfoPtr);
#endif

#if (IPDUM_TXBUFFERSTARTIDXOFTXPATHWAY == STD_ON || IPDUM_RXMUXPDU == STD_ON)
/*******************************************************************************************
*  IpduM_CopySegments()
*******************************************************************************************/
/*! \brief        Copies segments in PDUs
 *  \details      -
 *  \param[in]    segmentStartIdx
 *  \param[in]    segmentEndIdx
 *  \param[out]   destPduInfoPtr    PduInfoPtr to target buffer
 *  \param[in]    srcPtr            Pointer to source buffer
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE for different segments
 *  \synchronous  TRUE
*******************************************************************************************/
LOCAL_INLINE FUNC(void,
                  IPDUM_CODE) IpduM_CopySegments(IpduM_SegmentIterType segmentStartIdx,
                                                 IpduM_SegmentIterType segmentEndIdx, P2VAR(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) destPduInfoPtr, P2CONST(uint8, AUTOMATIC, IPDUM_APPL_DATA) srcPtr);
#endif

#if((IPDUM_JITUPDATEOFTXPART == STD_ON) && (IPDUM_UL_TRIGGER_TRANSMIT_API == STD_ON))
/*******************************************************************************************
 *  IpduM_JitUpdate()
*******************************************************************************************/
/*! \brief          Updates static and dynamic parts via Trigger Transmit, if configured.
 *  \details        -
 *  \param[in]      txPathwayId       tx pathway handle
 *  \param[in,out]  pduInfoPtr        pointer and length of the provided buffer and length of the copied data on return
 *  \param[in]      isTriggerTransmit true for triggertransmit, false for direct transmission
 *  \param[in]      txPartId          id of triggered part for direct transmission, ignored for triggertransmit
 *  \return         E_OK              the trigger transmit call has been successful and data has been updated.
 *  \return         E_NOT_OK          the trigger transmit call has been rejected by the upper layer.
 *  \pre            -
 *  \context        TASK|ISR
 *  \reentrant      TRUE for different tx Pathway IDs
 *  \synchronous    TRUE
*******************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, IPDUM_CODE) IpduM_JitUpdate(IpduM_CTxPathwayIterType txPathwayId, P2VAR(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) pduInfoPtr, boolean isTriggerTransmit,
                                                              IpduM_TxUpIndIdxOfTxUpInfoType txPartId);

/*******************************************************************************************
 *  IpduM_JitTriggerTransmit()
*******************************************************************************************/
/*! \brief          Updates parts via Trigger Transmit.
 *  \details        -
 *  \param[in]      PdumTxPduId     upper layer trigger transmit handle
 *  \param[in]      txPathwayId     tx pathway handle
 *  \param[in]      txPartId        tx part handle
 *  \param[in,out]  pduInfoPtr      pointer and length of the provided buffer and length of the copied data on return
 *  \return         E_OK            the trigger transmit call has been successful and data has been updated.
 *  \return         E_NOT_OK        the trigger transmit call has been rejected by the upper layer.
 *  \pre            -
 *  \context        TASK|ISR
 *  \reentrant      TRUE for different tx Pathway IDs
 *  \synchronous    TRUE
*******************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, IPDUM_CODE) IpduM_JitTriggerTransmit(PduIdType PdumTxPduId, IpduM_CTxPathwayIterType txPathwayId, IpduM_TxPartIterType txPartId,
                                                                       P2VAR(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) pduInfoPtr);
#endif

#define IPDUM_STOP_SEC_CODE
#include "MemMap.h"    /* PRQA S 5087 */        /*  MD_MSR_MemMap */

/**********************************************************************************************************************
  LOCAL FUNCTIONS
**********************************************************************************************************************/
#define IPDUM_START_SEC_CODE
#include "MemMap.h"    /* PRQA S 5087 */        /*  MD_MSR_MemMap */

/*******************************************************************************************
*  IpduM_WriteMuxFillerSegments()
*******************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
#if (IPDUM_RESTSEGMENT == STD_ON)
LOCAL_INLINE FUNC(void,
                  IPDUM_CODE) IpduM_WriteMuxFillerSegments(IpduM_RestSegmentIterType segmentStartIdx,
                                                 IpduM_RestSegmentIterType segmentEndIdx, IpduM_CTxPathwayIterType txPathwayIdx, P2VAR(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) destPduInfoPtr)
{
  IpduM_UnusedAreasDefaultOfTxPathwayType unusedPattern = IpduM_GetUnusedAreasDefaultOfTxPathway(txPathwayIdx);
  IpduM_RestSegmentIterType segmentIterParameter = segmentStartIdx;
# if ((IPDUM_PARTIALENDBYTEOFRESTSEGMENT == STD_ON) || (IPDUM_PARTIALSTARTBYTEOFRESTSEGMENT == STD_ON))
  /* Only partial byte writing needs exclusive area for read-modify-write protection */
  SchM_Enter_IpduM_IPDUM_EXCLUSIVE_AREA_0();
# endif
  for(; segmentIterParameter < segmentEndIdx; segmentIterParameter++)
  {
    /* Set copy destination pointer to the start position of the provided dest buffer */
    P2VAR(uint8, AUTOMATIC, IPDUM_APPL_DATA) pDest = destPduInfoPtr->SduDataPtr;

# if ((IPDUM_PARTIALENDBYTEOFRESTSEGMENT == STD_ON) && ((IPDUM_FULLBYTESPRESENTOFRESTSEGMENT == STD_ON) || (IPDUM_PARTIALSTARTBYTEOFRESTSEGMENT == STD_ON)))
    if(IpduM_IsPartialEndByteOfRestSegment(segmentIterParameter))  
# endif
# if (IPDUM_PARTIALENDBYTEOFRESTSEGMENT == STD_ON)
    {
      if(IpduM_GetLastBytePosOfRestSegment(segmentIterParameter) < destPduInfoPtr->SduLength) /* COV_IPDUM_DEFENSIVE_PROGRAMMING */
      {
        /* copy the last (partial) byte from source to destination */
        pDest[IpduM_GetLastBytePosOfRestSegment(segmentIterParameter)] &= IpduM_GetEndByteMaskClearOfRestSegment(segmentIterParameter);     /* SBSW_IPDUM_COPYSEGMENTS */
        pDest[IpduM_GetLastBytePosOfRestSegment(segmentIterParameter)] |= (unusedPattern & IpduM_GetEndByteMaskWriteOfRestSegment(segmentIterParameter));    /* SBSW_IPDUM_COPYSEGMENTS */
      }
    }
# endif

# if((IPDUM_FULLBYTESPRESENTOFRESTSEGMENT == STD_ON) && (IPDUM_PARTIALSTARTBYTEOFRESTSEGMENT == STD_ON))
    if(IpduM_IsFullBytesPresentOfRestSegment(segmentIterParameter))  
# endif
# if(IPDUM_FULLBYTESPRESENTOFRESTSEGMENT == STD_ON)
    {
      IpduM_LastFullBytePosOfRestSegmentType pos;
      for(pos = IpduM_GetFirstFullBytePosOfRestSegment(segmentIterParameter); pos <= IpduM_GetLastFullBytePosOfRestSegment(segmentIterParameter); pos++)
      {
        if(pos < destPduInfoPtr->SduLength) /* COV_IPDUM_DEFENSIVE_PROGRAMMING */
        {
          pDest[pos] = unusedPattern; /* SBSW_IPDUM_COPYSEGMENTS */
        }
      }
    }
# endif

# if((IPDUM_PARTIALSTARTBYTEOFRESTSEGMENT == STD_ON) && ((IPDUM_PARTIALENDBYTEOFRESTSEGMENT == STD_ON) || (IPDUM_FULLBYTESPRESENTOFRESTSEGMENT == STD_ON)))
    if(IpduM_IsPartialStartByteOfRestSegment(segmentIterParameter))  
# endif
# if(IPDUM_PARTIALSTARTBYTEOFRESTSEGMENT == STD_ON)
    {
      if(IpduM_GetFirstBytePosOfRestSegment(segmentIterParameter) < destPduInfoPtr->SduLength) /* COV_IPDUM_DEFENSIVE_PROGRAMMING */
      {
        /* copy the first (partial) byte from source to destination */
        pDest[IpduM_GetFirstBytePosOfRestSegment(segmentIterParameter)] &= IpduM_GetStartByteMaskClearOfRestSegment(segmentIterParameter);  /* SBSW_IPDUM_COPYSEGMENTS */
        pDest[IpduM_GetFirstBytePosOfRestSegment(segmentIterParameter)] |= (unusedPattern & IpduM_GetStartByteMaskWriteOfRestSegment(segmentIterParameter));        /* SBSW_IPDUM_COPYSEGMENTS */
      }
    }
# endif
  }
# if ((IPDUM_PARTIALENDBYTEOFRESTSEGMENT == STD_ON) || (IPDUM_PARTIALSTARTBYTEOFRESTSEGMENT == STD_ON))
  SchM_Exit_IpduM_IPDUM_EXCLUSIVE_AREA_0();
# endif
}
#endif

/*******************************************************************************************
 *  IpduM_CopySegments()
*******************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
#if (IPDUM_TXBUFFERSTARTIDXOFTXPATHWAY == STD_ON || IPDUM_RXMUXPDU == STD_ON)
LOCAL_INLINE FUNC(void,
                  IPDUM_CODE) IpduM_CopySegments(IpduM_SegmentIterType segmentStartIdx,
                                                 IpduM_SegmentIterType segmentEndIdx, P2VAR(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) destPduInfoPtr, P2CONST(uint8, AUTOMATIC, IPDUM_APPL_DATA) srcPtr)
{
  IpduM_SegmentIterType segmentIterParameter = segmentStartIdx;
# if ((IPDUM_PARTIALENDBYTEOFSEGMENT == STD_ON) || (IPDUM_PARTIALSTARTBYTEOFSEGMENT == STD_ON))
  /* Only partial byte copy needs exclusive area for read-modify-write protection */
  SchM_Enter_IpduM_IPDUM_EXCLUSIVE_AREA_0();
# endif
  for(; segmentIterParameter < segmentEndIdx; segmentIterParameter++)
  {
    /* Set copy destination pointer to the start position of the provided dest buffer */
    P2VAR(uint8, AUTOMATIC, IPDUM_APPL_DATA) pDest = destPduInfoPtr->SduDataPtr;
    /* Set copy source pointer to the start position of the provided source buffer */
    P2CONST(uint8, AUTOMATIC, IPDUM_APPL_DATA) pSrc = &srcPtr[0];

# if ((IPDUM_PARTIALENDBYTEOFSEGMENT == STD_ON) && ((IPDUM_FULLBYTESPRESENTOFSEGMENT == STD_ON) || (IPDUM_PARTIALSTARTBYTEOFSEGMENT == STD_ON)))
    if(IpduM_IsPartialEndByteOfSegment(segmentIterParameter))  
# endif
# if (IPDUM_PARTIALENDBYTEOFSEGMENT == STD_ON)
    {
      if(IpduM_GetLastBytePosOfSegment(segmentIterParameter) < destPduInfoPtr->SduLength) /* COV_IPDUM_DEFENSIVE_PROGRAMMING */
      {
        /* copy the last (partial) byte from source to destination */
        pDest[IpduM_GetLastBytePosOfSegment(segmentIterParameter)] &= IpduM_GetEndByteMaskClearOfSegment(segmentIterParameter);     /* SBSW_IPDUM_COPYSEGMENTS */
        pDest[IpduM_GetLastBytePosOfSegment(segmentIterParameter)] |= (pSrc[IpduM_GetLastBytePosOfSegment(segmentIterParameter)] & IpduM_GetEndByteMaskWriteOfSegment(segmentIterParameter));    /* SBSW_IPDUM_COPYSEGMENTS */
      }
    }
# endif

# if((IPDUM_FULLBYTESPRESENTOFSEGMENT == STD_ON) && (IPDUM_PARTIALSTARTBYTEOFSEGMENT == STD_ON))
    if(IpduM_IsFullBytesPresentOfSegment(segmentIterParameter))  
# endif
# if(IPDUM_FULLBYTESPRESENTOFSEGMENT == STD_ON)
    {
      IpduM_LastFullBytePosOfSegmentType pos;
      for(pos = IpduM_GetFirstFullBytePosOfSegment(segmentIterParameter); pos <= IpduM_GetLastFullBytePosOfSegment(segmentIterParameter); pos++)
      {
        if(pos < destPduInfoPtr->SduLength) /* COV_IPDUM_DEFENSIVE_PROGRAMMING */
        {
          pDest[pos] = pSrc[pos]; /* SBSW_IPDUM_COPYSEGMENTS */
        }
      }
    }
# endif

# if((IPDUM_PARTIALSTARTBYTEOFSEGMENT == STD_ON) && ((IPDUM_PARTIALENDBYTEOFSEGMENT == STD_ON) || (IPDUM_FULLBYTESPRESENTOFSEGMENT == STD_ON)))
    if(IpduM_IsPartialStartByteOfSegment(segmentIterParameter))  
# endif
# if(IPDUM_PARTIALSTARTBYTEOFSEGMENT == STD_ON)
    {
      if(IpduM_GetFirstBytePosOfSegment(segmentIterParameter) < destPduInfoPtr->SduLength) /* COV_IPDUM_DEFENSIVE_PROGRAMMING */
      {
        /* copy the first (partial) byte from source to destination */
        pDest[IpduM_GetFirstBytePosOfSegment(segmentIterParameter)] &= IpduM_GetStartByteMaskClearOfSegment(segmentIterParameter);  /* SBSW_IPDUM_COPYSEGMENTS */
        pDest[IpduM_GetFirstBytePosOfSegment(segmentIterParameter)] |= (pSrc[IpduM_GetFirstBytePosOfSegment(segmentIterParameter)] & IpduM_GetStartByteMaskWriteOfSegment(segmentIterParameter));        /* SBSW_IPDUM_COPYSEGMENTS */
      }
    }
# endif
  }
# if ((IPDUM_PARTIALENDBYTEOFSEGMENT == STD_ON) || (IPDUM_PARTIALSTARTBYTEOFSEGMENT == STD_ON))
  SchM_Exit_IpduM_IPDUM_EXCLUSIVE_AREA_0();
# endif
}
#endif

#if(IPDUM_JITUPDATEOFTXPART == STD_ON && IPDUM_UL_TRIGGER_TRANSMIT_API == STD_ON)
/*******************************************************************************************
 *  IpduM_JitUpdate()
*******************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
LOCAL_INLINE FUNC(Std_ReturnType, IPDUM_CODE) IpduM_JitUpdate(IpduM_CTxPathwayIterType txPathwayId, P2VAR(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) pduInfoPtr, boolean isTriggerTransmit,
                                                              IpduM_TxUpIndIdxOfTxUpInfoType txPartId)
{
  Std_ReturnType retVal = E_OK;
# if(IPDUM_TXSTATICPDUREFOFTXPATHWAY == STD_ON)
  if((IpduM_IsTxPartStaticPartUsedOfTxPathway(txPathwayId)) && (IpduM_IsJitUpdateOfTxPart(IpduM_GetTxPartStaticPartIdxOfTxPathway(txPathwayId)))) 
  {
    if(((txPartId == IpduM_GetDynamicPduIdxOfTxPathway(txPathwayId)) && (!isTriggerTransmit)) || isTriggerTransmit) /* COV_IPDUM_INVALID_CONFIG */
    {
      retVal = IpduM_JitTriggerTransmit(IpduM_GetUlPduRefOfTxPart(IpduM_GetTxPartStaticPartIdxOfTxPathway(txPathwayId)), txPathwayId, IpduM_GetTxPartStaticPartIdxOfTxPathway(txPathwayId), pduInfoPtr);        /* SBSW_IPDUM_FUNCTIONCALL_PDUINFOPTR_CHECKED_BY_CALLER */
    }
  }
# endif
  {
    IpduM_TxPartIterType txDynamicPartId;
    SchM_Enter_IpduM_IPDUM_EXCLUSIVE_AREA_0();
    txDynamicPartId = (IpduM_TxPartIterType) IpduM_GetDynamicPduIdxOfTxPathway(txPathwayId);
    SchM_Exit_IpduM_IPDUM_EXCLUSIVE_AREA_0();

    if(IpduM_IsJitUpdateOfTxPart(txDynamicPartId)) 
    {
# if ((IPDUM_TRIGGEREVENTOFTXPART == STD_ON) && (IPDUM_TXSTATICPDUREFOFTXPATHWAY == STD_ON))
      if(((txPartId == IpduM_GetTxPartStaticPartIdxOfTxPathway(txPathwayId)) && (!isTriggerTransmit)) || isTriggerTransmit) /* COV_IPDUM_INVALID_CONFIG */
# endif
      {
        retVal = IpduM_JitTriggerTransmit(IpduM_GetUlPduRefOfTxPart(txDynamicPartId), txPathwayId, txDynamicPartId, pduInfoPtr);        /* SBSW_IPDUM_FUNCTIONCALL_PDUINFOPTR_CHECKED_BY_CALLER */
      }
    }
  }
  IPDUM_DUMMY_STATEMENT(txPartId);      /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  IPDUM_DUMMY_STATEMENT(isTriggerTransmit);      /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  return retVal;
}

/*******************************************************************************************
 *  IpduM_JitTriggerTransmit()
*******************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
LOCAL_INLINE FUNC(Std_ReturnType, IPDUM_CODE) IpduM_JitTriggerTransmit(PduIdType PdumTxPduId, IpduM_CTxPathwayIterType txPathwayId, IpduM_TxPartIterType txPartId,
                                                                       P2VAR(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) pduInfoPtr)
{
  Std_ReturnType retVal = E_OK;
  if(PduR_IpduMTriggerTransmit(PdumTxPduId, pduInfoPtr) == E_OK)        /* SBSW_IPDUM_FUNCTIONCALL_PDUINFOPTR_CHECKED_BY_CALLER */ /* VCA_IPDUM_FUNCTIONCALL_PDUINFOPTR_SELF_CONSTRUCTED */
  {
    PduInfoType segmentDestPduInfo;
    segmentDestPduInfo.SduDataPtr = IpduM_GetAddrTxBuffer(IpduM_GetTxBufferStartIdxOfTxPathway(txPathwayId));
    segmentDestPduInfo.SduLength = (PduLengthType) ((PduLengthType)IpduM_GetSizeOfTxBuffer() - IpduM_GetTxBufferStartIdxOfTxPathway(txPathwayId)); /* maximum size of buffer, used for ensuring freedom from interference */
    IpduM_CopySegments(IpduM_GetSegmentStartIdxOfTxPart(txPartId), IpduM_GetSegmentEndIdxOfTxPart(txPartId), &segmentDestPduInfo, pduInfoPtr->SduDataPtr);      /* SBSW_IPDUM_JITTRIGGERTRANSMIT_CALL_COPYSEGMENTS */
  }
  else
  {
    retVal = E_NOT_OK;
  }
  return retVal;
}
#endif

#if (IPDUM_TXBUFFERSTARTIDXOFTXPATHWAY == STD_ON)
/*******************************************************************************************
*  IpduM_InitComponentMux()
*******************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, IPDUM_CODE) IpduM_InitComponentMux(void)
{
  /* Initialize multiplex PDU handle / index for "for" loop */
  IpduM_CTxPathwayIterType muxTxPduHnd;

  /* initialize all the Tx multiplex PDUs, reset the timeout counters and set the IpduM state to initialized */
  for(muxTxPduHnd = 0u; muxTxPduHnd < IpduM_GetSizeOfCTxPathway(); muxTxPduHnd++)  
  {
# if(IPDUM_DYNAMICPDUIDXOFTXPATHWAY == STD_ON)    /* COV_IPDUM_VAR_DEPENDENT_SWITCH */
    /* record the dynamic PDU id */
    IpduM_SetDynamicPduIdxOfTxPathway(muxTxPduHnd, IpduM_GetTxPartInitialDynPartIdxOfTxPathway(muxTxPduHnd)); /* SBSW_IPDUM_CSL02 */
#  endif
  }
# if(IPDUM_TXINITVALUES == STD_ON)     /* COV_IPDUM_VAR_DEPENDENT_SWITCH */
  /* This check avoids copying from an empty buffer in Post-Build RxOnly configurations */
  if(IpduM_GetSizeOfTxInitValues() > 0u)    /* PRQA S 2741 */ /* MD_IpduM_2741 */ /* COV_IPDUM_INIT_MEMCPY */
  {
    VStdLib_MemCpy_s(IpduM_GetAddrTxBuffer(0), IpduM_GetSizeOfTxBuffer(), IpduM_GetAddrTxInitValues(0), IpduM_GetSizeOfTxInitValues()); /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_IPDUM_VSTDLIB_SAFE */  /* VCA_IPDUM_VSTDLIB_MEMCPY_SAFE */
  }
# endif
}
#endif

#if (IPDUM_TXPART == STD_ON)
/*******************************************************************************************
 *  IpduM_MuxTransmit()
*******************************************************************************************/
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
 * \spec
 *   requires txPartId < IpduM_GetSizeOfTxPart();
 * \endspec
 */
FUNC(Std_ReturnType, IPDUM_CODE) IpduM_MuxTransmit(IpduM_TxUpIndIdxOfTxUpInfoType txPartId, P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr)
{
  Std_ReturnType retVal = E_NOT_OK;  /* PRQA S 2981*/ /* MD_MSR_RetVal*/
  /* Initialize multiplex PDU handle for copying to */
  IpduM_CTxPathwayIterType txPathway = IpduM_GetTxPathwayIdxOfTxPart(txPartId);

# if((IPDUM_TXCONFTIMEOUTCNTOFVTXLOINFO == STD_ON) && (IPDUM_TXCONFIRMATIONTIMEOUTOFTXPATHWAY == STD_ON))
  /* TxLoInfo exists if a txConfirmation is configured. If not, 0 is a safe default for txConfTimeoutCntIdx. */
  IpduM_TxLoInfoWithInvalidIndexesIterType txConfTimeoutCntIdx = 0;
  if(IpduM_IsTxLoInfoUsedOfTxPathway(txPathway))
  {
    IpduM_TxLoInfoIdxOfTxPathwayType txLoInfoIdx = IpduM_GetTxLoInfoIdxOfTxPathway(txPathway);
    txConfTimeoutCntIdx = txLoInfoIdx;
  }

  if((IpduM_GetTxConfirmationTimeoutOfTxPathway(txPathway) == 0u) || (IpduM_GetTxConfTimeoutCntOfVTxLoInfoOfTxLoInfoWithInvalidIndexes(txConfTimeoutCntIdx) == 0u))
# endif
  {
    /* multiplex PDU buffer not engaged and accept transmission */
    /* jit update not required, assign associated multiplex buffer, multiplex data */
    /* as an optimization copying a source part requiring jit update can be avoided in this context */
    
    PduInfoType segmentDestPduInfo;
    segmentDestPduInfo.SduDataPtr = IpduM_GetAddrTxBuffer(IpduM_GetTxBufferStartIdxOfTxPathway(txPathway));
    segmentDestPduInfo.SduLength = (PduLengthType) ((PduLengthType)IpduM_GetSizeOfTxBuffer() - IpduM_GetTxBufferStartIdxOfTxPathway(txPathway)); /* PRQA S 2897 */ /* MD_IpduM_2897 */ /* maximum size of buffer, used for ensuring freedom from interference */

    /* Write unused areas default value if necessary */
# if (IPDUM_RESTSEGMENT == STD_ON)
    IpduM_WriteMuxFillerSegments(IpduM_GetRestSegmentStartIdxOfTxPart(txPartId), IpduM_GetRestSegmentEndIdxOfTxPart(txPartId), txPathway, &segmentDestPduInfo); /* SBSW_IPDUM_MUXTRANSMIT_CALL_MUXFILLERSEGMENTS */
# endif
    /* Copy data from the given buffer (function argument) to the TX buffer */
    IpduM_CopySegments(IpduM_GetSegmentStartIdxOfTxPart(txPartId), IpduM_GetSegmentEndIdxOfTxPart(txPartId), &segmentDestPduInfo, PduInfoPtr->SduDataPtr); /* SBSW_IPDUM_MUXTRANSMIT_CALL_COPYSEGMENTS */
    /* set retVal to "OK" for successfully storing the non-triggering part for later transmission */
    retVal = E_OK; /* PRQA S 2981*/ /* MD_MSR_RetVal*/

# if((IPDUM_TXSTATICPDUREFOFTXPATHWAY == STD_ON) && (IPDUM_DYNAMICPDUIDXOFTXPATHWAY == STD_ON))    /* COV_IPDUM_VAR_DEPENDENT_SWITCH */
    if((!IpduM_IsTxPartStaticPartUsedOfTxPathway(txPathway)) || (IpduM_GetTxPartStaticPartIdxOfTxPathway(txPathway) != txPartId))  
# endif
    {
      SchM_Enter_IpduM_IPDUM_EXCLUSIVE_AREA_0();
      IpduM_SetDynamicPduIdxOfTxPathway(txPathway, (IpduM_DynamicPduIdxOfTxPathwayType) txPartId); /* PRQA S 2842 */ /* MD_IpduM_2842 */ /* SBSW_IPDUM_CSL02 */
      SchM_Exit_IpduM_IPDUM_EXCLUSIVE_AREA_0();
    }

# if (IPDUM_TRIGGEREVENTOFTXPART == STD_ON)
    if(IpduM_IsTriggerEventOfTxPart(txPartId)) 
    {
      /* do transmit, a trigger triggered */
      if(IpduM_GetSizeOfJitUpdateBuffer() >= (IpduM_GetLengthOfTxPathway(txPathway) + IpduM_GetJitUpdateBufferStartIdxOfTxPathway(txPathway))) /* COV_IPDUM_DEFENSIVE_PROGRAMMING */
      {
#  if ((IPDUM_JITUPDATEOFTXPART == STD_ON) && (IPDUM_UL_TRIGGER_TRANSMIT_API == STD_ON) && (IPDUM_TXSTATICPDUREFOFTXPATHWAY == STD_ON))
        PduInfoType jitUpdatePduInfo;
        jitUpdatePduInfo.SduDataPtr = IpduM_GetAddrJitUpdateBuffer(IpduM_GetJitUpdateBufferStartIdxOfTxPathway(txPathway));
        jitUpdatePduInfo.SduLength = IpduM_GetLengthOfTxPathway(txPathway);
        if(IpduM_JitUpdate(txPathway, &jitUpdatePduInfo, FALSE, txPartId) == E_OK) /* SBSW_IPDUM_MUXTRANSMIT_CALL_JITUPDATE */
#  endif
        {
          /* Interrupt disabling is required to avoid the timeout timer being reset by a tx confirmation of a previous transmission. The tx confirmation timeout is loaded before triggering transmission, because the If can confirm a previous transmission of the multiplex Pdu in the current tranmission trigger context, before the timer for the current transmission is loaded.  */
          SchM_Enter_IpduM_IPDUM_EXCLUSIVE_AREA_0();
#  if((IPDUM_TXCONFTIMEOUTCNTOFVTXLOINFO == STD_ON) && (IPDUM_TXCONFIRMATIONTIMEOUTOFTXPATHWAY == STD_ON))
          /* Load timeout counter - encapsulation necessary to secure write access using optional variable txConfTimeoutCntIdx. */
          if(IpduM_IsTxLoInfoUsedOfTxPathway(txPathway))
          {
            IpduM_SetTxConfTimeoutCntOfVTxLoInfoOfTxLoInfoWithInvalidIndexes(txConfTimeoutCntIdx, IpduM_GetTxConfirmationTimeoutOfTxPathway(txPathway)); /* SBSW_IPDUM_INDIRECT_ACCESS_FROM_EXTERNAL_PARAMETER */
          }
#  endif
          {
            PduInfoType pduInfo;
            pduInfo.SduDataPtr = IpduM_GetAddrTxBuffer(IpduM_GetTxBufferStartIdxOfTxPathway(txPathway));
            pduInfo.SduLength = IpduM_GetLengthOfTxPathway(txPathway);
            if(IpduM_GetSizeOfTxBuffer() >= (IpduM_GetLengthOfTxPathway(txPathway) + IpduM_GetTxBufferStartIdxOfTxPathway(txPathway))) /* COV_IPDUM_DEFENSIVE_PROGRAMMING */
            {
              retVal = PduR_IpduMTransmit(IpduM_GetLlPduRefOfTxPathway(txPathway), &pduInfo); /* SBSW_IPDUM_MUXTRANSMIT_CALL_PDURTRANSMIT */ /* VCA_IPDUM_FUNCTIONCALL_PDUINFOPTR_SELF_CONSTRUCTED */
            }
          }
#  if((IPDUM_TXCONFTIMEOUTCNTOFVTXLOINFO == STD_ON) && (IPDUM_TXCONFIRMATIONTIMEOUTOFTXPATHWAY == STD_ON))
          if((retVal != E_OK) && IpduM_IsTxLoInfoUsedOfTxPathway(txPathway))
          {
            /* transmission failed. Reset the confirmation timeout time - encapsulation necessary to secure write access using optional variable txConfTimeoutCntIdx. */
            IpduM_SetTxConfTimeoutCntOfVTxLoInfoOfTxLoInfoWithInvalidIndexes(txConfTimeoutCntIdx, IPDUM_RESET);  /* SBSW_IPDUM_INDIRECT_ACCESS_FROM_EXTERNAL_PARAMETER */
          }
#  endif
          SchM_Exit_IpduM_IPDUM_EXCLUSIVE_AREA_0();
        }
#  if ((IPDUM_JITUPDATEOFTXPART == STD_ON) && (IPDUM_UL_TRIGGER_TRANSMIT_API == STD_ON) && (IPDUM_TXSTATICPDUREFOFTXPATHWAY == STD_ON))
        else
        {
          /* jit update failed */
          retVal = E_NOT_OK;
        }
#  endif
      }
    }
# endif
  }
  return retVal;
}  /* PRQA S 6010, 6030, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STMIF */
#endif

#if(IPDUM_TRIGGER_TRANSMIT_API == STD_ON && IPDUM_EXISTS_MUX_PATHWAYTYPEOFCTXLOINFO == STD_ON)
/*******************************************************************************************
 *  IpduM_MuxTriggerTransmit()
*******************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, IPDUM_CODE) IpduM_MuxTriggerTransmit(IpduM_TxPathwayIdxOfCTxLoInfoType txPathwayHnd, P2VAR(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr)
{
  /* Initialize return value with "ok" */
  Std_ReturnType retVal = E_NOT_OK;
# if (IPDUM_TXBUFFERSTARTIDXOFTXPATHWAY == STD_ON)   /* COV_IPDUM_VAR_DEPENDENT_SWITCH */
  /* Initialize copy destination pointer */
  IpduM_TxBufferPtrType pMuxPduBuf = IpduM_GetAddrTxBuffer(IpduM_GetTxBufferStartIdxOfTxPathway(txPathwayHnd));
#  if(IPDUM_JITUPDATEOFTXPART == STD_ON && IPDUM_UL_TRIGGER_TRANSMIT_API == STD_ON)     /* COV_IPDUM_VAR_DEPENDENT_SWITCH */
  PduInfoType jitUpdatePduInfo;
  jitUpdatePduInfo.SduDataPtr = IpduM_GetAddrTriggerTransmitBuffer(IpduM_GetTriggerTransmitBufferStartIdxOfTxPathway(txPathwayHnd));
  jitUpdatePduInfo.SduLength = PduInfoPtr->SduLength;
#  endif
  if(PduInfoPtr->SduLength >= IpduM_GetLengthOfTxPathway(txPathwayHnd))
  {
#  if(IPDUM_JITUPDATEOFTXPART == STD_ON && IPDUM_UL_TRIGGER_TRANSMIT_API == STD_ON) /* COV_IPDUM_VAR_DEPENDENT_SWITCH */
    if(IpduM_GetSizeOfTriggerTransmitBuffer() >= (PduInfoPtr->SduLength + IpduM_GetTriggerTransmitBufferStartIdxOfTxPathway(txPathwayHnd))) /* COV_IPDUM_DEFENSIVE_PROGRAMMING */
    {
      if(IpduM_JitUpdate(txPathwayHnd, &jitUpdatePduInfo, TRUE, 0u) == E_OK) /* SBSW_IPDUM_MUXTRIGGERTRANSMIT_CALL_JITUPDATE */
      {
#  endif
        SchM_Enter_IpduM_IPDUM_EXCLUSIVE_AREA_0();
        {
          /* Copy PDU from mux buffer to provided destination buffer */
          VStdLib_MemCpy_s(PduInfoPtr->SduDataPtr, PduInfoPtr->SduLength, pMuxPduBuf, IpduM_GetLengthOfTxPathway(txPathwayHnd)); /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_IPDUM_VSTDLIB_SAFE */  /* VCA_IPDUM_VSTDLIB_MEMCPY_SAFE */
          PduInfoPtr->SduLength = IpduM_GetLengthOfTxPathway(txPathwayHnd); /* SBSW_IPDUM_MUXTRIGGERTRANSMIT_MEMORY_WRITE */
        }
#  if((IPDUM_TXCONFTIMEOUTCNTOFVTXLOINFO == STD_ON) && (IPDUM_TXCONFIRMATIONTIMEOUTOFTXPATHWAY == STD_ON) && (IPDUM_TXCONFIRMATIONOFTXPART == STD_ON)) /* COV_IPDUM_VAR_DEPENDENT_SWITCH */
        /* Load timeout counter - encapsulation necessary to secure write access using optional variable txConfTimeoutCntIdx. */
        if(IpduM_IsTxLoInfoUsedOfTxPathway(txPathwayHnd))
        {
          IpduM_TxLoInfoIdxOfTxPathwayType txLoInfoIdx = IpduM_GetTxLoInfoIdxOfTxPathway(txPathwayHnd);
          IpduM_SetTxConfTimeoutCntOfVTxLoInfoOfTxLoInfoWithInvalidIndexes(txLoInfoIdx, IpduM_GetTxConfirmationTimeoutOfTxPathway(txPathwayHnd)); /* SBSW_IPDUM_INDIRECT_ACCESS_FROM_EXTERNAL_PARAMETER */
        }
#  endif
        SchM_Exit_IpduM_IPDUM_EXCLUSIVE_AREA_0();
        retVal = E_OK;
#  if(IPDUM_JITUPDATEOFTXPART == STD_ON && IPDUM_UL_TRIGGER_TRANSMIT_API == STD_ON)     /* COV_IPDUM_VAR_DEPENDENT_SWITCH */
      }
    }
#  endif
  }
# endif
  IPDUM_DUMMY_STATEMENT(txPathwayHnd);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  IPDUM_DUMMY_STATEMENT(PduInfoPtr);    /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  return retVal;
}
#endif

#if ((IPDUM_TXCONFIRMATIONTIMEOUTOFTXPATHWAY == STD_ON) || (IPDUM_TXCONFIRMATIONOFTXPART == STD_ON))
/*******************************************************************************************
 *  IpduM_MuxTxConfirmation()
*******************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(void, IPDUM_CODE) IpduM_MuxTxConfirmation(PduIdType TxPduId)
{
  {
# if (IPDUM_TXBUFFERSTARTIDXOFTXPATHWAY == STD_ON)   /* COV_IPDUM_VAR_DEPENDENT_SWITCH */
    /* get handle of multiplex PDU */
#  if ((IPDUM_TXCONFIRMATIONTIMEOUTOFTXPATHWAY == STD_ON) || (IPDUM_TXCONFIRMATIONOFTXPART == STD_ON && IPDUM_UL_TX_CONFIRMATION_API == STD_ON))        /* COV_IPDUM_VAR_DEPENDENT_SWITCH */
    IpduM_CTxPathwayIterType txPathwayHnd = IpduM_GetTxPathwayIdxOfCTxLoInfoOfTxLoInfoWithInvalidIndexes(TxPduId);
#  endif
#  if (IPDUM_TXCONFIRMATIONTIMEOUTOFTXPATHWAY == STD_ON)        /* COV_IPDUM_VAR_DEPENDENT_SWITCH */
    /* Initialize the "we have a confirmation to forwards" flag with "nothing to forward" */
    boolean txConf = FALSE;

    if(0u != IpduM_GetTxConfirmationTimeoutOfTxPathway(txPathwayHnd))
    {
      /* IPDUM019: transmission confirmation timeout time configured for the multiplex PDU */
      if(0u != IpduM_GetTxConfTimeoutCntOfVTxLoInfoOfTxLoInfoWithInvalidIndexes(TxPduId))
      {
        /* transmission confirmation timer not elapsed yet, transmission confirmation is expected */
        txConf = TRUE;  /* We have a confirmation to forward */
        IpduM_SetTxConfTimeoutCntOfVTxLoInfoOfTxLoInfoWithInvalidIndexes(TxPduId, IPDUM_RESET);    /* Clear counter */ /* SBSW_IPDUM_INDIRECT_ACCESS_FROM_EXTERNAL_PARAMETER */
      }
    }
    else
    {
      /* no transmission confirmation time configured */
      txConf = TRUE;    /* We have a confirmation to forward */
    }

    if(txConf == TRUE)
#  endif
    {
#  if(IPDUM_TXCONFIRMATIONOFTXPART == STD_ON && IPDUM_UL_TX_CONFIRMATION_API == STD_ON)
      IpduM_TxPartIterType txDynamicPartId;
      SchM_Enter_IpduM_IPDUM_EXCLUSIVE_AREA_0();
      txDynamicPartId = (IpduM_TxPartIterType) IpduM_GetDynamicPduIdxOfTxPathway(txPathwayHnd);
      SchM_Exit_IpduM_IPDUM_EXCLUSIVE_AREA_0();
      if(IpduM_IsTxConfirmationOfTxPart(txDynamicPartId)) /* VCA_IPDUM_READING_OF_BEFORE_WRITTEN_ID */
      {
        /* Forward confirmation to PduR */
        PduR_IpduMTxConfirmation(IpduM_GetUlPduRefOfTxPart(txDynamicPartId)); /* VCA_IPDUM_FUNCTIONCALL_WITH_ONLY_ID */
      }
#   if(IPDUM_TXSTATICPDUREFOFTXPATHWAY == STD_ON)
      if(IpduM_IsTxPartStaticPartUsedOfTxPathway(txPathwayHnd)) 
      {
        if(IpduM_IsTxConfirmationOfTxPart(IpduM_GetTxPartStaticPartIdxOfTxPathway(txPathwayHnd)))  
        {
          /* Forward confirmation to PduR */
          PduR_IpduMTxConfirmation(IpduM_GetUlPduRefOfTxPart(IpduM_GetTxPartStaticPartIdxOfTxPathway(txPathwayHnd))); /* VCA_IPDUM_FUNCTIONCALL_WITH_ONLY_ID */
        }
      }
#   endif
#  endif
    }
# endif
  }
  IPDUM_DUMMY_STATEMENT(TxPduId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}
#endif

#if (IPDUM_RXMUXPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_MuxRxIndication()
*******************************************************************************************/
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
 * \spec
 *   requires rxMuxPduId < IpduM_GetSizeOfRxMuxPdu();
 * \endspec
 */
FUNC(void, IPDUM_CODE) IpduM_MuxRxIndication(IpduM_RxPathwayIndIdxOfRxInfoType rxMuxPduId, P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr)
{
  PduInfoType pduInfo;
  /* Point to copy target buffer */
  pduInfo.SduDataPtr = IpduM_GetAddrRxBuffer(IpduM_GetRxBufferStartIdxOfRxMuxPdu(rxMuxPduId));
  pduInfo.SduLength = PduInfoPtr->SduLength;    /* Set length of pdu */

  /* Ensure consistency of pduInfo pointer. */
  if((PduLengthType)(IpduM_GetSizeOfRxBuffer() - (PduLengthType)IpduM_GetRxBufferStartIdxOfRxMuxPdu(rxMuxPduId)) < pduInfo.SduLength) /* COV_IPDUM_DEFENSIVE_PROGRAMMING */
  {
    pduInfo.SduLength = (PduLengthType)((PduLengthType)IpduM_GetSizeOfRxBuffer() - IpduM_GetRxBufferStartIdxOfRxMuxPdu(rxMuxPduId));
  }

  {     /* block for encapsulation */
    IpduM_RxDynPduIterType ipduMDynPduIdx = IpduM_GetRxDynPduStartIdxOfRxMuxPdu(rxMuxPduId);
    IpduM_RxSelectorPatternStartIdxOfRxDynPduType patternLength =
        IpduM_GetRxSelectorPatternEndIdxOfRxDynPdu(ipduMDynPduIdx) - IpduM_GetRxSelectorPatternStartIdxOfRxDynPdu(ipduMDynPduIdx);

    if(((PduLengthType)IpduM_GetSelectorFieldBytePositionOfRxMuxPdu(rxMuxPduId) + (PduLengthType)(patternLength)) <= pduInfo.SduLength)
    {
      /* loop over dynamic parts */
      for(; ipduMDynPduIdx < IpduM_GetRxDynPduEndIdxOfRxMuxPdu(rxMuxPduId); ipduMDynPduIdx++)
      {
        IpduM_RxSelectorPatternIterType ipduMSubPatternIdx;
        boolean patternMatch = TRUE;      /* Initialize with true, turn false on any sub-pattern mismatch. */
        uint8 inputOffset = 0;    /* Offset of initial pointer to current pattern position (valid values: 0, 1, 2). */
        /* loop over subpatterns */
        for(ipduMSubPatternIdx = IpduM_GetRxSelectorPatternStartIdxOfRxDynPdu(ipduMDynPduIdx); ipduMSubPatternIdx < IpduM_GetRxSelectorPatternEndIdxOfRxDynPdu(ipduMDynPduIdx); ipduMSubPatternIdx++)
        {
          /* mask input data and compare with pattern */
          uint8 selectorSubPattern = PduInfoPtr->SduDataPtr[(IpduM_GetSelectorFieldBytePositionOfRxMuxPdu(rxMuxPduId) + inputOffset)] & IpduM_GetSelectorFieldSubMaskOfRxSelectorPattern(ipduMSubPatternIdx);  /* PRQA S 2985 */ /* MD_IpduM_2985 */
          if(selectorSubPattern != IpduM_GetSelectorFieldSubPatternOfRxSelectorPattern(ipduMSubPatternIdx))
          {
            patternMatch = FALSE;
          }
          inputOffset++;  /* PRQA S 2982 */ /* MD_IpduM_2982 */
        }
        if((patternMatch == TRUE) && (pduInfo.SduLength >= IpduM_GetMinDLCOfRxDynPdu(ipduMDynPduIdx)))
        {
          /* on match: copy data */
          /* copy dynamic part to target buffer */
          IpduM_CopySegments(IpduM_GetSegmentStartIdxOfRxDynPdu(ipduMDynPduIdx), IpduM_GetSegmentEndIdxOfRxDynPdu(ipduMDynPduIdx), &pduInfo, PduInfoPtr->SduDataPtr); /* SBSW_IPDUM_MUXRXINDICATION_CALL_COPYSEGMENTS */
          /* Indicate reception of dynamic part to PduR, hand over the buffer containing received data */
          PduR_IpduMRxIndication(IpduM_GetUlPduRefOfRxDynPdu(ipduMDynPduIdx), &pduInfo);  /* SBSW_IPDUM_MUXRXINDICATION_CALL_PDURRXINDICATION */ /* VCA_IPDUM_FUNCTIONCALL_PDUINFOPTR_SELF_CONSTRUCTED */
        }
      }
    }
  }

# if(IPDUM_RXSTATICPDUIDXOFRXMUXPDU == STD_ON)
  if(IpduM_IsRxStaticPduUsedOfRxMuxPdu(rxMuxPduId))  
  {
    /* get index of static PDU */
    IpduM_RxStaticPduIterType ipduMStaticPduIdx = IpduM_GetRxStaticPduIdxOfRxMuxPdu(rxMuxPduId);
    if(pduInfo.SduLength >= IpduM_GetMinDLCOfRxStaticPdu(ipduMStaticPduIdx))
    {
      /* a static part is configured, its id assigned its sub parts/bit fields indicies extracted */
      /* Copy received data to receive buffer */
      IpduM_CopySegments(IpduM_GetSegmentStartIdxOfRxStaticPdu(ipduMStaticPduIdx), IpduM_GetSegmentEndIdxOfRxStaticPdu(ipduMStaticPduIdx), &pduInfo, PduInfoPtr->SduDataPtr); /* SBSW_IPDUM_MUXRXINDICATION_CALL_COPYSEGMENTS */
      /* Indicate reception of static part to PduR, hand over the buffer containing received data */
      PduR_IpduMRxIndication(IpduM_GetUlPduRefOfRxStaticPdu(ipduMStaticPduIdx), &pduInfo); /* SBSW_IPDUM_MUXRXINDICATION_CALL_PDURRXINDICATION */ /* VCA_IPDUM_FUNCTIONCALL_PDUINFOPTR_SELF_CONSTRUCTED */
    }
  }
# endif
}
#endif /* (IPDUM_RXMUXPDU == STD_ON) */

#define IPDUM_STOP_SEC_CODE
#include "MemMap.h"    /* PRQA S 5087 */        /*  MD_MSR_MemMap */

/**********************************************************************************************************************
  GLOBAL FUNCTIONS
**********************************************************************************************************************/

/**********************************************************************************************************************
 * GLOBAL MISRA / PCLINT JUSTIFICATION
 *********************************************************************************************************************/
/* *INDENT-OFF* */
/* module specific MISRA deviations:
   MD_IpduM_2741: Misra Rule 14.3
     Reason:      This "if" statement was added to avoid illegal calls to Memcpy with a NULL ptr as the source
                  address. The behavior without this "if" is always correct because the length is always zero
                  in these cases, but a DET is thrown because of the NULL ptr. This "if" statement avoids the
                  DET call but doesn't change any functionality.
     Risk:        No risk, because the functionality doesn't change without the if-statement.
     Prevention:  No prevention necessary.
     
   MD_IpduM_2842: Index Access to pointer array
     Reason:      QAC cannot determine whether the pointer value is correct. However, the ComStackLib generates
                  those values and if the indices used are correct, the pointers are, too. The indices are either
                  calculated using ComStackLib indirections, ComStackLib SizeOf() macros or passed on by a caller
                  of this function, hence being checked by the caller. So all indices used in these macros are
                  correct.
     Risk:        No risk.
     Prevention:  No prevention necessary.
   
   MD_IpduM_2897: Apparent: Negative value cast to an unsigned type.
     Reason:      Subtraction could possibly return negative result. However, the first value is a ComStackLib generated
                  buffer and the second value is a ComStackLib generated index within this buffer, using a ComStackLib
                  indirection. The second value will always be smaller than the first, the result will always be positive.
     Risk:        No risk.
     Prevention:  No prevention necessary.
   
   MD_IpduM_2982: Misra Rule 2.2  
     Reason:      The number of loop iterations depends on the configuration. When there is only one iteration this value is optimized.
     Risk:        No risk, because only warning that assignment is redundant.
     Prevention:  No prevention necessary.
     
   MD_IpduM_2985: Misra Rule 2.2
     Reason:      The bit shift of 0 bits is because of maintainability and comprehensibility. Or the result depends on the configuration.
     Risk:        No risk, because only warning that the operation is redundant.
     Prevention:  No prevention necessary.

*/

/* COV_JUSTIFICATION_BEGIN

  \ID COV_IPDUM_DEFENSIVE_PROGRAMMING
    \ACCEPT TX
    \ACCEPT XF
    \ACCEPT TF tf tx
    \ACCEPT TX tx tx
    \REASON This condition is used because of safe programming, should never be false in production code.

  \ID COV_IPDUM_INVALID_CONFIG
    \ACCEPT TF tf tx tf
    \ACCEPT TF tf tf tx
    \REASON Coverage of this code section would require an invalid configuration.

  \ID COV_IPDUM_VAR_DEPENDENT_SWITCH
    \ACCEPT TX
    \ACCEPT TF tf tx
    \ACCEPT TF tx tf
    \ACCEPT TX tx tx
    \ACCEPT TX tf tf tf
    \ACCEPT TX tx tf tf
    \ACCEPT TF tx tf tf
    \REASON The nested switch depends on a previous switch.

  \ID COV_IPDUM_INIT_MEMCPY
    \ACCEPT TX
    \REASON This "if" statement was added to avoid illegal calls to Memcpy with a NULL ptr as the source
            address. The behavior without this "if" is always correct because the length is always zero
            in these cases, but a DET is thrown because of the NULL ptr. This "if" statement avoids the
            DET call but doesn't change any functionality.

COV_JUSTIFICATION_END */

/* *INDENT-ON* */

/**********************************************************************************************************************
  END OF FILE: IpduM_Mux.c
**********************************************************************************************************************/
