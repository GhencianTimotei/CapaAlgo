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
/*!        \file  Com_RxProcessing.h
 *        \brief  MICROSAR Communication source file
 *
 *      \details  This is the implementation of the MICROSAR Communication module.
 *                The basic software module is based on the AUTOSAR Communication specification.
 *
 *********************************************************************************************************************/

#if !defined (COM_RXPROCESSING_H)
# define COM_RXPROCESSING_H

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
# include "Com.h"
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

/*! Type to indicate the process state. */
typedef enum
{
  VALID,                        /* PRQA S 3205 */ /* MD_Com_3205 */
  INVALID,                      /* PRQA S 3205 */ /* MD_Com_3205 */
  FILTERED                      /* PRQA S 3205 */ /* MD_Com_3205 */
} Com_RxSigProcessState;        /* PRQA S 3205 */ /* MD_Com_3205 */

/**********************************************************************************************************************
  GLOBAL DATA PROTOTYPES (Com)
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/
# define COM_START_SEC_CODE
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_MemMap */

# if (COM_RXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxProcessing_InitRxIpdu
**********************************************************************************************************************/
/*! \brief        This function initializes a rx I-PDU in Com_RxProcessing.
    \details      -
    \pre          -
    \param[in]    ComRxPduId Handle of the I-PDU.
    \context      TASK
    \trace        SPEC-2736775
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_RxProcessing_InitRxIpdu(PduIdType ComRxPduId);
# endif

# if (COM_RXCBKFUNCPTR == STD_ON)
/**********************************************************************************************************************
  Com_ProcessRxFctPtrCache
**********************************************************************************************************************/
/*! \brief             This function calles all Rx cached function pointer.
    \details           -
    \pre               -
    \param[in,out]     fctPtrCacheStrctPtr    Pointert to Struct that contains informations (cache location, cache size, cache index)
                                              about cache which should be processed.
    \context           TASK|ISR2
    \synchronous       TRUE
    \reentrant         TRUE, for different handles
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_ProcessRxFctPtrCache(P2VAR(FctPtrCacheStrct, AUTOMATIC, COM_APPL_DATA) fctPtrCacheStrctPtr);
# endif

# if (COM_RXSIGINFOENDIDXOFRXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxProcessing_RxPduSigEvent
**********************************************************************************************************************/
/*! \brief              This function processes all related Rx ComSignals of the received ComIPdu.
    \details            -
    \pre                -
    \param[in]          comRxPduInfoIdx index of the received ComIPdu
    \param[in]          PduInfoPtr   contains the SDU buffer and the SDU length
    \param[in,out]      fctPtrCacheStrctPtr contains function ptr cache informations (cache location, size, index)
    \trace              SPEC-2736871
    \context            TASK|ISR2
    \synchronous        TRUE
    \reentrant          TRUE, for different handles
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_RxProcessing_RxPduSigEvent(PduIdType comRxPduInfoIdx, P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr,
                                                    P2VAR(FctPtrCacheStrct, AUTOMATIC, COM_APPL_DATA) fctPtrCacheStrctPtr);
# endif

# if (COM_RXSIGGRPINFOINDENDIDXOFRXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxProcessing_RxPduSigGrpEvent
**********************************************************************************************************************/
/*! \brief              This function processes all related Rx ComSignalGroups of the received ComIPdu.
    \details            -
    \pre                -
    \param[in]          comRxPduInfoIdx index of the received ComIPdu
    \param[in]          PduInfoPtr   contains the SDU buffer and the SDU length
    \param[in,out]      fctPtrCacheStrctPtr contains function ptr cache informations (cache location, size, index)
    \trace              SPEC-2736871, SPEC-2736854
    \context            TASK|ISR2
    \synchronous        TRUE
    \reentrant          TRUE, for different handles
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_RxProcessing_RxPduSigGrpEvent(PduIdType comRxPduInfoIdx, P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr,
                                                       P2VAR(FctPtrCacheStrct, AUTOMATIC, COM_APPL_DATA) fctPtrCacheStrctPtr);
# endif

# if (COM_EXISTS_DEFERRED_SIGNALPROCESSINGOFRXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxDeferredPduProcessing
**********************************************************************************************************************/
/*! \brief              This function shall perform the processing of the AUTOSAR COM receive processing that are not directly
                        initiated by the calls from the RTE and PduR.
    \details            -
    \pre                -
    \context            TASK
    \synchronous        TRUE
    \reentrant          TRUE, for different handles
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_RxDeferredPduProcessing(void);
# endif

# if(COM_RXSIGBUFFERARRAYBASEDBUFFERUSEDOFRXACCESSINFO == STD_ON)
/**********************************************************************************************************************
  Com_Signal_SetRxSigBufferArrayBasedValue
**********************************************************************************************************************/
/*! \brief        This function copies the ArrayBased ApplType dependent constant source value to the destination buffer
                  RxSigBufferArrayBased.
    \details      -
    \pre          -
    \param[in]    idxRxAccessInfo   Index of RxAccessInfo
    \param[in]    idxDestValue      Destination index of the buffer RxSigBufferBuffer
    \param[in]    idxSrcValue       Source index of constant source value
    \param[in]    length            Valid amount of bytes to be copied.
    \context      TASK|ISR2
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_Signal_SetRxSigBufferArrayBasedValue(Com_RxAccessInfoIterType idxRxAccessInfo, Com_RxSigBufferArrayBasedIterType idxDestValue,
                                                              Com_ConstValueArrayBasedIterType idxSrcValue, PduLengthType length);
# endif

# if ((COM_RXTPINFOUSEDOFRXPDUINFO == STD_ON) && (COM_EXISTS_UINT8_DYN_APPLTYPEOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
  Com_GetRxDynamicLength
**********************************************************************************************************************/
/*! \brief        This function returns the current dynamic signal length, dependent on the passed SDU length.
    \details      -
    \pre          -
    \param[in]    sduLength                   SDU length
    \param[in]    rxAccessInfoIdx             RxAccessInfo index
    \return       PduLengthType               current dynamic signal length.
    \trace        SPEC-2736904
    \context      TASK
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
**********************************************************************************************************************/
FUNC(PduLengthType, COM_CODE) Com_GetRxDynamicLength(PduLengthType sduLength, Com_RxAccessInfoIterType rxAccessInfoIdx);
# endif

# if(COM_EXISTS_DEFERRED_SIGNALPROCESSINGOFRXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxProcessing_EnterExclusiveArea_Deferred
**********************************************************************************************************************/
/*! \brief        This function enters the rx deferred exclusive area.
    \details      -
    \pre          -
    \trace        DSGN-COM_ISRTHRESHOLD_CONCEPT
    \context      TASK
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_RxProcessing_EnterExclusiveArea_Deferred(void);

/**********************************************************************************************************************
  Com_RxProcessing_ExitExclusiveArea_Deferred
**********************************************************************************************************************/
/*! \brief        This function exits the rx deferred exclusive area.
    \details      -
    \pre          -
    \trace        DSGN-COM_ISRTHRESHOLD_CONCEPT
    \context      TASK
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_RxProcessing_ExitExclusiveArea_Deferred(void);
# endif

# define COM_STOP_SEC_CODE
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_MemMap */

#endif /* COM_RXPROCESSING_H */
/**********************************************************************************************************************
  END OF FILE: Com_RxProcessing.h
**********************************************************************************************************************/
