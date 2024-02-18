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
/*!        \file  Com_RxProcessing.c
 *        \brief  MICROSAR Communication source file
 *
 *      \details  This is the implementation of the MICROSAR Communication module.
 *                The basic software module is based on the AUTOSAR Communication specification.
 *
 *********************************************************************************************************************/

#define COM_RXPROCESSING_SOURCE

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
#include "Com_RxProcessing.h"
#include "Com_LLIf.h"
#include "Com_RxInv.h"
#include "Com_Timer.h"
#include "Com_Buffers.h"
#include "Com_Gateway.h"
#include "Com_Deserializer.h"
#include "Com_Notifications.h"
#include "Com_SignalFilterHdlr.h"
#include "SchM_Com.h"
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

#if (COM_SHDBUFFERREQUIREDOFRXSIGGRPINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxProcessing_ReadGrpSignal
**********************************************************************************************************************/
/*! \brief        This function extracts the ComGroupSignal data of the passed Sdu data and copies it to the related temp shadow buffer
    \details      -
    \pre          -
    \param[in]    PduInfoPtr contains the SDU buffer and the SDU length
    \param[in]    idxRxAccessInfo   Rx Group Signal handle
    \context      TASK|ISR2
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_RxProcessing_ReadGrpSignal(P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr, Com_RxAccessInfoIterType idxRxAccessInfo);
#endif

#if ((COM_RXSIGGRPINFOINDENDIDXOFRXPDUINFO == STD_ON) && (COM_FILTEREVENTOFRXSIGGRPINFO == STD_ON))
/**********************************************************************************************************************
  Com_RxProcessing_RxSignalGroupFilterCheck
**********************************************************************************************************************/
/*! \brief        This function evaluates the filter of the passed ComSignalGroup
    \details      -
    \pre          -
    \param[in]    idxRxSigGrpInfo   Handle Id of ComSignalGroup
    \return       boolean TRUE if the filter is passed, otherwise FALSE.
    \context      TASK|ISR2
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(Com_RxSigProcessState, COM_CODE) Com_RxProcessing_RxSignalGroupFilterCheck(Com_RxSigGrpInfoIterType idxRxSigGrpInfo);
#endif

#if ((COM_RXSIGGRPINFOINDENDIDXOFRXPDUINFO == STD_ON) && (COM_UBMASKUSEDOFRXSIGGRPINFO == STD_ON))
/**********************************************************************************************************************
  Com_RxProcessing_CheckSigGrpUB
**********************************************************************************************************************/
/*! \brief        This function evaluates if the ComSignalGroup was updated.
    \details      -
    \pre          -
    \param[in]    PduInfoPtr        contains the SDU buffer and the SDU length.
    \param[in]    idxRxSigGrpInfo   Handle Id of ComSignalGroup
    \return       boolean TRUE if the ComSignalGroup was updated, otherwise FALSE.
    \context      TASK|ISR2
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(boolean, COM_CODE) Com_RxProcessing_CheckSigGrpUB(P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr, Com_RxSigGrpInfoIterType idxRxSigGrpInfo);
#endif

#if ((COM_RXSIGINFOENDIDXOFRXPDUINFO == STD_ON) && (COM_UBMASKUSEDOFRXSIGINFO == STD_ON))
/**********************************************************************************************************************
  Com_RxProcessing_CheckSigUB
**********************************************************************************************************************/
/*! \brief        This function evaluates if the ComSignal was updated.
    \details      -
    \pre          -
    \param[in]    idxRxSigInfo       Index of RxSigInfo
    \param[in]    PduInfoPtr         contains the SDU buffer and the SDU length.
    \return       boolean TRUE if the ComSignalGroup was updated, otherwise FALSE.
    \context      TASK|ISR2
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(boolean, COM_CODE) Com_RxProcessing_CheckSigUB(Com_RxSigInfoIterType idxRxSigInfo, P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr);
#endif

#if (COM_RXSIGGRPINFOINDENDIDXOFRXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxProcessing_ProcessSigGrpEvent
**********************************************************************************************************************/
/*! \brief              This function processes the passed ComSignalGroup.
    \details            -
    \pre                -
    \param[in]          comRxPduInfoIdx     Index of RxPduInfo
    \param[in]          PduInfoPtr          contains the SDU buffer and the SDU length.
    \param[in]          idxRxSigGrpInfo     Index of RxSigGrpInfo.
    \param[in,out]      fctPtrCacheStrctPtr Pointer to function ptr cache containing all informations (location, size, index)
    \trace              SPEC-2736832, SPEC-2736777, SPEC-2736778
    \context            TASK|ISR2
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_RxProcessing_ProcessSigGrpEvent(PduIdType comRxPduInfoIdx, P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr,
                                                                          Com_RxSigGrpInfoIterType idxRxSigGrpInfo, P2VAR(FctPtrCacheStrct, AUTOMATIC, COM_APPL_DATA) fctPtrCacheStrctPtr);
#endif

#if ((COM_SHDBUFFERREQUIREDOFRXSIGGRPINFO == STD_ON) || (COM_ARRAYACCESSUSEDOFRXSIGGRPINFO == STD_ON))
/**********************************************************************************************************************
  Com_RxProcessing_ReadSignalGroup
**********************************************************************************************************************/
/*! \brief        This function reads the signal group data for a given Signal Group Index from given PDU.
    \details      -
    \pre          -
    \param[in]    PduInfoPtr          contains the SDU buffer and the SDU length.
    \param[in]    idxRxSigGrpInfo     Index of RxSigGrpInfo.
    \context      TASK|ISR2
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_RxProcessing_ReadSignalGroup(P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr, Com_RxSigGrpInfoIterType idxRxSigGrpInfo);
#endif

#if(COM_EXISTS_DEFERRED_SIGNALPROCESSINGOFRXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxProcessing_ThresholdCheck_Deferred
**********************************************************************************************************************/
/*! \brief            This function checks if the ISR Lock must be opened
    \details          -
    \pre              -
    \param[in,out]    fctPtrCacheStrctPtr Deferred function pointer cache which should be processed if ISR Lock will be opened.
    \trace            DSGN-COM_ISRTHRESHOLD_CONCEPT
    \context          TASK
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_RxProcessing_ThresholdCheck_Deferred(P2VAR(FctPtrCacheStrct, AUTOMATIC, COM_APPL_DATA) fctPtrCacheStrctPtr);
#endif

#if (COM_EXISTS_DEFERRED_SIGNALPROCESSINGOFRXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxProcessing_IsDeferredProcessingRequested
**********************************************************************************************************************/
/*! \brief        This function checks if the PduGroup that belongs to the PduId is active and if the Pdu with given Id has
 *                been received.
    \details      -
    \pre          -
    \param[in]    idxRxPduInfo            Rx ComIPdu handle Id
    \return       boolean
                    FALSE if sanity check fails, otherwise TRUE.
    \context      TASK
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(boolean, COM_CODE) Com_RxProcessing_IsDeferredProcessingRequested(Com_SizeOfRxPduInfoType idxRxPduInfo);
#endif

#if (COM_EXISTS_DEFERRED_SIGNALPROCESSINGOFRXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxProcessDeferredPDU
**********************************************************************************************************************/
/*! \brief              This function processes a deferred PDU.
    \details            -
    \pre                -
    \param[in]          idxRxPduInfo                  Index of the PDU that should be processed.
    \param[in,out]      deferredfctPtrCacheStrctPtr   Pointer to struct,
                                                      which contains all informations for deferred function pointer caching.
    \context            TASK
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_RxProcessDeferredPDU(PduIdType idxRxPduInfo, P2VAR(FctPtrCacheStrct, AUTOMATIC, COM_APPL_DATA) deferredfctPtrCacheStrctPtr);
#endif

#if (COM_EXISTS_DEFERRED_SIGNALPROCESSINGOFRXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxDeferredPduProcessing_IterateOverAllRxPdus
**********************************************************************************************************************/
/*! \brief             This function shall perform the processing of the AUTOSAR COM receive processing that are not directly
                       initiated by the calls from the RTE and PduR. All Rx Pdus are checked, whether a deferred processing is required.
    \details           -
    \pre               -
    \param[in,out]     deferredFctPtrCacheStrct - Deferred function pointer cache which should be processed if ISR Lock will be opened
    \context           TASK
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_RxDeferredPduProcessing_IterateOverAllRxPdus(P2VAR(FctPtrCacheStrct, AUTOMATIC, COM_APPL_DATA) deferredFctPtrCacheStrct);
#endif

#if (COM_RXSIGINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxSignalProcessing
**********************************************************************************************************************/
/*! \brief        This function processes the reception of one specific Rx Access Info event.
    \details      -
    \pre          -
    \param[in]    PduInfoPtr              received PDU.
    \param[in]    idxRxAccessInfo         Rx Access Info index.
    \return       Com_RxSigProcessState
                          VALID       the signal value is valid
                          INVALID     the signal value is invalid
                          FILTERED    the signal value is does not pass the filter
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(Com_RxSigProcessState, COM_CODE) Com_RxSignalProcessing(P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr, Com_RxAccessInfoIdxOfRxSigInfoType idxRxAccessInfo);
#endif

#if ((COM_EXISTS_UINT8_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_RXSIGINFO == STD_ON))
/**********************************************************************************************************************
*  Com_RxSignalProcessing_UINT8
*********************************************************************************************************************/
/*!
 * \brief         This method reads the signal value from the PDU buffer performs the invalid check and evaluates the filter state
 *                and updates the internal signal buffer if value is valid.
 * \details       -
 * \pre           -
 * \param[in]     PduInfoPtr              received PDU.
 * \param[in]     idxRxAccessInfo         Rx Access Info index.
 * \return        Com_RxSigProcessState
 *                        VALID       the signal value is valid
 *                        INVALID     the signal value is invalid
 *                        FILTERED    the signal value does not pass the filter
 * \trace         SPEC-2736777
 * \trace         SPEC-2736778
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(Com_RxSigProcessState, COM_CODE) Com_RxSignalProcessing_UINT8(P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr, Com_RxAccessInfoIterType idxRxAccessInfo);
#endif

#if ((COM_EXISTS_SINT8_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_RXSIGINFO == STD_ON))
/**********************************************************************************************************************
*  Com_RxSignalProcessing_SINT8
*********************************************************************************************************************/
/*!
 * \brief         This method reads the signal value from the PDU buffer performs the invalid check and evaluates the filter state
 *                and updates the internal signal buffer if value is valid.
 * \details       -
 * \pre           -
 * \param[in]     PduInfoPtr              received PDU.
 * \param[in]     idxRxAccessInfo         Rx Access Info index.
 * \return        Com_RxSigProcessState
 *                        VALID       the signal value is valid
 *                        INVALID     the signal value is invalid
 *                        FILTERED    the signal value does not pass the filter
 * \trace         SPEC-2736777
 * \trace         SPEC-2736778
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(Com_RxSigProcessState, COM_CODE) Com_RxSignalProcessing_SINT8(P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr, Com_RxAccessInfoIterType idxRxAccessInfo);
#endif

#if ((COM_EXISTS_UINT16_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_RXSIGINFO == STD_ON))
/**********************************************************************************************************************
*  Com_RxSignalProcessing_UINT16
*********************************************************************************************************************/
/*!
 * \brief         This method reads the signal value from the PDU buffer performs the invalid check and evaluates the filter state
 *                and updates the internal signal buffer if value is valid.
 * \details       -
 * \pre           -
 * \param[in]     PduInfoPtr              received PDU.
 * \param[in]     idxRxAccessInfo         Rx Access Info index.
 * \return        Com_RxSigProcessState
 *                        VALID       the signal value is valid
 *                        INVALID     the signal value is invalid
 *                        FILTERED    the signal value does not pass the filter
 * \trace         SPEC-2736777
 * \trace         SPEC-2736778
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(Com_RxSigProcessState, COM_CODE) Com_RxSignalProcessing_UINT16(P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr, Com_RxAccessInfoIterType idxRxAccessInfo);
#endif

#if ((COM_EXISTS_SINT16_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_RXSIGINFO == STD_ON))
/**********************************************************************************************************************
*  Com_RxSignalProcessing_SINT16
*********************************************************************************************************************/
/*!
 * \brief         This method reads the signal value from the PDU buffer performs the invalid check and evaluates the filter state
 *                and updates the internal signal buffer if value is valid.
 * \details       -
 * \pre           -
 * \param[in]     PduInfoPtr              received PDU.
 * \param[in]     idxRxAccessInfo         Rx Access Info index.
 * \return        Com_RxSigProcessState
 *                        VALID       the signal value is valid
 *                        INVALID     the signal value is invalid
 *                        FILTERED    the signal value does not pass the filter
 * \trace         SPEC-2736777
 * \trace         SPEC-2736778
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(Com_RxSigProcessState, COM_CODE) Com_RxSignalProcessing_SINT16(P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr, Com_RxAccessInfoIterType idxRxAccessInfo);
#endif

#if ((COM_EXISTS_UINT32_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_RXSIGINFO == STD_ON))
/**********************************************************************************************************************
*  Com_RxSignalProcessing_UINT32
*********************************************************************************************************************/
/*!
 * \brief         This method reads the signal value from the PDU buffer performs the invalid check and evaluates the filter state
 *                and updates the internal signal buffer if value is valid.
 * \details       -
 * \pre           -
 * \param[in]     PduInfoPtr              received PDU.
 * \param[in]     idxRxAccessInfo         Rx Access Info index.
 * \return        Com_RxSigProcessState
 *                        VALID       the signal value is valid
 *                        INVALID     the signal value is invalid
 *                        FILTERED    the signal value does not pass the filter
 * \trace         SPEC-2736777
 * \trace         SPEC-2736778
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(Com_RxSigProcessState, COM_CODE) Com_RxSignalProcessing_UINT32(P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr, Com_RxAccessInfoIterType idxRxAccessInfo);
#endif

#if ((COM_EXISTS_SINT32_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_RXSIGINFO == STD_ON))
/**********************************************************************************************************************
*  Com_RxSignalProcessing_SINT32
*********************************************************************************************************************/
/*!
 * \brief         This method reads the signal value from the PDU buffer performs the invalid check and evaluates the filter state
 *                and updates the internal signal buffer if value is valid.
 * \details       -
 * \pre           -
 * \param[in]     PduInfoPtr              received PDU.
 * \param[in]     idxRxAccessInfo         Rx Access Info index.
 * \return        Com_RxSigProcessState
 *                        VALID       the signal value is valid
 *                        INVALID     the signal value is invalid
 *                        FILTERED    the signal value does not pass the filter
 * \trace         SPEC-2736777
 * \trace         SPEC-2736778
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(Com_RxSigProcessState, COM_CODE) Com_RxSignalProcessing_SINT32(P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr, Com_RxAccessInfoIterType idxRxAccessInfo);
#endif

#if ((COM_EXISTS_UINT64_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_RXSIGINFO == STD_ON))
/**********************************************************************************************************************
*  Com_RxSignalProcessing_UINT64
*********************************************************************************************************************/
/*!
 * \brief         This method reads the signal value from the PDU buffer performs the invalid check and evaluates the filter state
 *                and updates the internal signal buffer if value is valid.
 * \details       -
 * \pre           -
 * \param[in]     PduInfoPtr              received PDU.
 * \param[in]     idxRxAccessInfo         Rx Access Info index.
 * \return        Com_RxSigProcessState
 *                        VALID       the signal value is valid
 *                        INVALID     the signal value is invalid
 *                        FILTERED    the signal value does not pass the filter
 * \trace         SPEC-2736777
 * \trace         SPEC-2736778
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(Com_RxSigProcessState, COM_CODE) Com_RxSignalProcessing_UINT64(P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr, Com_RxAccessInfoIterType idxRxAccessInfo);
#endif

#if ((COM_EXISTS_SINT64_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_RXSIGINFO == STD_ON))
/**********************************************************************************************************************
*  Com_RxSignalProcessing_SINT64
*********************************************************************************************************************/
/*!
 * \brief         This method reads the signal value from the PDU buffer performs the invalid check and evaluates the filter state
 *                and updates the internal signal buffer if value is valid.
 * \details       -
 * \pre           -
 * \param[in]     PduInfoPtr              received PDU.
 * \param[in]     idxRxAccessInfo         Rx Access Info index.
 * \return        Com_RxSigProcessState
 *                        VALID       the signal value is valid
 *                        INVALID     the signal value is invalid
 *                        FILTERED    the signal value does not pass the filter
 * \trace         SPEC-2736777
 * \trace         SPEC-2736778
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(Com_RxSigProcessState, COM_CODE) Com_RxSignalProcessing_SINT64(P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr, Com_RxAccessInfoIterType idxRxAccessInfo);
#endif

#if ((COM_EXISTS_FLOAT32_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_RXSIGINFO == STD_ON))
/**********************************************************************************************************************
*  Com_RxSignalProcessing_FLOAT32
*********************************************************************************************************************/
/*!
 * \brief         This method reads the signal value from the PDU buffer performs the invalid check and evaluates the filter state
 *                and updates the internal signal buffer if value is valid.
 * \details       -
 * \pre           -
 * \param[in]     PduInfoPtr              received PDU.
 * \param[in]     idxRxAccessInfo         Rx Access Info index.
 * \return        Com_RxSigProcessState
 *                        VALID       the signal value is valid
 *                        INVALID     the signal value is invalid
 *                        FILTERED    the signal value does not pass the filter
 * \trace         SPEC-2736777
 * \trace         SPEC-2736778
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(Com_RxSigProcessState, COM_CODE) Com_RxSignalProcessing_FLOAT32(P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr, Com_RxAccessInfoIterType idxRxAccessInfo);
#endif

#if ((COM_EXISTS_FLOAT64_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_RXSIGINFO == STD_ON))
/**********************************************************************************************************************
*  Com_RxSignalProcessing_FLOAT64
*********************************************************************************************************************/
/*!
 * \brief         This method reads the signal value from the PDU buffer performs the invalid check and evaluates the filter state
 *                and updates the internal signal buffer if value is valid.
 * \details       -
 * \pre           -
 * \param[in]     PduInfoPtr              received PDU.
 * \param[in]     idxRxAccessInfo         Rx Access Info index.
 * \return        Com_RxSigProcessState
 *                        VALID       the signal value is valid
 *                        INVALID     the signal value is invalid
 *                        FILTERED    the signal value does not pass the filter
 * \trace         SPEC-2736777
 * \trace         SPEC-2736778
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(Com_RxSigProcessState, COM_CODE) Com_RxSignalProcessing_FLOAT64(P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr, Com_RxAccessInfoIterType idxRxAccessInfo);
#endif

#if((COM_EXISTS_UINT8_N_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_RXSIGINFO == STD_ON))
/**********************************************************************************************************************
*  Com_RxSignalProcessing_UINT8_N
*********************************************************************************************************************/
/*!
 * \brief         This method reads the signal value from the PDU buffer performs the invalid check and evaluates the filter state
 *                and updates the internal signal buffer if value is valid.
 * \details       -
 * \pre           -
 * \param[in]     PduInfoPtr              received PDU.
 * \param[in]     idxRxAccessInfo         Rx Access Info index.
 * \return        Com_RxSigProcessState
 *                        VALID       the signal value is valid
 *                        INVALID     the signal value is invalid
 *                        FILTERED    the signal value is does not pass the filter
 * \trace         SPEC-2736777
 * \trace         SPEC-2736778
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(Com_RxSigProcessState, COM_CODE) Com_RxSignalProcessing_UINT8_N(P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr, Com_RxAccessInfoIterType idxRxAccessInfo);
#endif

#if ((COM_RXTPINFOUSEDOFRXPDUINFO == STD_ON) && (COM_EXISTS_UINT8_DYN_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_RXSIGINFO == STD_ON))
/**********************************************************************************************************************
*  Com_RxSignalProcessing_UINT8_DYN
*********************************************************************************************************************/
/*!
 * \brief         This method reads the signal value from the PDU buffer performs the invalid check and evaluates the filter state
 *                and updates the internal signal buffer if value is valid.
 * \details       -
 * \pre           -
 * \param[in]     PduInfoPtr              received PDU.
 * \param[in]     idxRxAccessInfo         Rx Access Info index.
 * \return        Com_RxSigProcessState
 *                        VALID       the signal value is valid
 *                        INVALID     the signal value is invalid
 *                        FILTERED    the signal value is does not pass the filter
 * \trace         SPEC-2736777
 * \trace         SPEC-2736778
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(Com_RxSigProcessState, COM_CODE) Com_RxSignalProcessing_UINT8_DYN(P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr, Com_RxAccessInfoIterType idxRxAccessInfo);
#endif


/**********************************************************************************************************************
  LOCAL FUNCTIONS
**********************************************************************************************************************/

#if (COM_SHDBUFFERREQUIREDOFRXSIGGRPINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxProcessing_ReadGrpSignal
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_RxProcessing_ReadGrpSignal(P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr, Com_RxAccessInfoIterType idxRxAccessInfo)
{
  if(NULL_PTR != PduInfoPtr->SduDataPtr)        /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    switch (Com_GetApplTypeOfRxAccessInfo(idxRxAccessInfo))
    {
# if (COM_TMPRXSHDBUFFERUINT8 == STD_ON)
      case COM_UINT8_APPLTYPEOFRXACCESSINFO:
      {
        uint8 signalValue = Com_Signal_ReadSignal_UInt8(idxRxAccessInfo, &(PduInfoPtr->SduDataPtr[Com_GetBytePositionOfRxAccessInfo(idxRxAccessInfo)]));        /* SBSW_COM_FCTCALL_WITH_P2CONST */
        Com_SetTmpRxShdBufferUInt8(Com_GetTmpBufferIdxOfRxAccessInfo(idxRxAccessInfo), signalValue);    /* SBSW_COM_CSL03 */
        break;
      }
# endif
# if (COM_TMPRXSHDBUFFERSINT8 == STD_ON)
      case COM_SINT8_APPLTYPEOFRXACCESSINFO:
      {
        sint8 signalValue = Com_Signal_ReadSignal_SInt8(idxRxAccessInfo, &(PduInfoPtr->SduDataPtr[Com_GetBytePositionOfRxAccessInfo(idxRxAccessInfo)]));        /* SBSW_COM_FCTCALL_WITH_P2CONST */
        Com_SetTmpRxShdBufferSInt8(Com_GetTmpBufferIdxOfRxAccessInfo(idxRxAccessInfo), signalValue);    /* SBSW_COM_CSL03 */
        break;
      }
# endif
# if (COM_TMPRXSHDBUFFERUINT16 == STD_ON)
      case COM_UINT16_APPLTYPEOFRXACCESSINFO:
      {
        uint16 signalValue = Com_Signal_ReadSignal_UInt16(idxRxAccessInfo, &(PduInfoPtr->SduDataPtr[Com_GetBytePositionOfRxAccessInfo(idxRxAccessInfo)]));      /* SBSW_COM_FCTCALL_WITH_P2CONST */
        Com_SetTmpRxShdBufferUInt16(Com_GetTmpBufferIdxOfRxAccessInfo(idxRxAccessInfo), signalValue);   /* SBSW_COM_CSL03 */
        break;
      }
# endif
# if (COM_TMPRXSHDBUFFERSINT16 == STD_ON)
      case COM_SINT16_APPLTYPEOFRXACCESSINFO:
      {
        sint16 signalValue = Com_Signal_ReadSignal_SInt16(idxRxAccessInfo, &(PduInfoPtr->SduDataPtr[Com_GetBytePositionOfRxAccessInfo(idxRxAccessInfo)]));      /* SBSW_COM_FCTCALL_WITH_P2CONST */
        Com_SetTmpRxShdBufferSInt16(Com_GetTmpBufferIdxOfRxAccessInfo(idxRxAccessInfo), signalValue);   /* SBSW_COM_CSL03 */
        break;
      }
# endif
# if (COM_TMPRXSHDBUFFERUINT32 == STD_ON)
      case COM_UINT32_APPLTYPEOFRXACCESSINFO:
      {
        uint32 signalValue = Com_Signal_ReadSignal_UInt32(idxRxAccessInfo, &(PduInfoPtr->SduDataPtr[Com_GetBytePositionOfRxAccessInfo(idxRxAccessInfo)]));      /* SBSW_COM_FCTCALL_WITH_P2CONST */
        Com_SetTmpRxShdBufferUInt32(Com_GetTmpBufferIdxOfRxAccessInfo(idxRxAccessInfo), signalValue);   /* SBSW_COM_CSL03 */
        break;
      }
# endif
# if (COM_TMPRXSHDBUFFERSINT32 == STD_ON)
      case COM_SINT32_APPLTYPEOFRXACCESSINFO:
      {
        sint32 signalValue = Com_Signal_ReadSignal_SInt32(idxRxAccessInfo, &(PduInfoPtr->SduDataPtr[Com_GetBytePositionOfRxAccessInfo(idxRxAccessInfo)]));      /* SBSW_COM_FCTCALL_WITH_P2CONST */
        Com_SetTmpRxShdBufferSInt32(Com_GetTmpBufferIdxOfRxAccessInfo(idxRxAccessInfo), signalValue);   /* SBSW_COM_CSL03 */
        break;
      }
# endif
# if (COM_TMPRXSHDBUFFERUINT64 == STD_ON)
      case COM_UINT64_APPLTYPEOFRXACCESSINFO:
      {
        uint64 signalValue = Com_Signal_ReadSignal_UInt64(idxRxAccessInfo, &(PduInfoPtr->SduDataPtr[Com_GetBytePositionOfRxAccessInfo(idxRxAccessInfo)]));      /* SBSW_COM_FCTCALL_WITH_P2CONST */
        Com_SetTmpRxShdBufferUInt64(Com_GetTmpBufferIdxOfRxAccessInfo(idxRxAccessInfo), signalValue);   /* SBSW_COM_CSL03 */
        break;
      }
# endif
# if (COM_TMPRXSHDBUFFERSINT64 == STD_ON)
      case COM_SINT64_APPLTYPEOFRXACCESSINFO:
      {
        sint64 signalValue = Com_Signal_ReadSignal_SInt64(idxRxAccessInfo, &(PduInfoPtr->SduDataPtr[Com_GetBytePositionOfRxAccessInfo(idxRxAccessInfo)]));      /* SBSW_COM_FCTCALL_WITH_P2CONST */
        Com_SetTmpRxShdBufferSInt64(Com_GetTmpBufferIdxOfRxAccessInfo(idxRxAccessInfo), signalValue);   /* SBSW_COM_CSL03 */
        break;
      }
# endif
# if (COM_TMPRXSHDBUFFERFLOAT32 == STD_ON)
      case COM_FLOAT32_APPLTYPEOFRXACCESSINFO:
      {
        float32 signalValue = Com_Signal_ReadSignal_Float32(idxRxAccessInfo, &(PduInfoPtr->SduDataPtr[Com_GetBytePositionOfRxAccessInfo(idxRxAccessInfo)]));    /* SBSW_COM_FCTCALL_WITH_P2CONST */
        Com_SetTmpRxShdBufferFloat32(Com_GetTmpBufferIdxOfRxAccessInfo(idxRxAccessInfo), signalValue);  /* SBSW_COM_CSL03 */
        break;
      }
# endif
# if (COM_TMPRXSHDBUFFERFLOAT64 == STD_ON)
      case COM_FLOAT64_APPLTYPEOFRXACCESSINFO:
      {
        float64 signalValue = Com_Signal_ReadSignal_Float64(idxRxAccessInfo, &(PduInfoPtr->SduDataPtr[Com_GetBytePositionOfRxAccessInfo(idxRxAccessInfo)]));    /* SBSW_COM_FCTCALL_WITH_P2CONST */
        Com_SetTmpRxShdBufferFloat64(Com_GetTmpBufferIdxOfRxAccessInfo(idxRxAccessInfo), signalValue);  /* SBSW_COM_CSL03 */
        break;
      }
# endif
# if (COM_TMPRXSHDBUFFERARRAYBASED == STD_ON)
#  if (COM_EXISTS_UINT8_N_APPLTYPEOFRXACCESSINFO == STD_ON)
      case COM_UINT8_N_APPLTYPEOFRXACCESSINFO:
      {
        P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) SignalBusSourcePtr;
        SignalBusSourcePtr = &(PduInfoPtr->SduDataPtr[Com_GetStartByteInPduPositionOfRxAccessInfo(idxRxAccessInfo)]);
        VStdMemCpyRamToRam(Com_GetAddrTmpRxShdBufferArrayBased(Com_GetTmpRxShdBufferArrayBasedTmpBufferStartIdxOfRxAccessInfo(idxRxAccessInfo)), SignalBusSourcePtr, Com_GetTmpRxShdBufferArrayBasedTmpBufferLengthOfRxAccessInfo(idxRxAccessInfo));    /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_COM_CSL02 */
        break;
      }
#  endif
#  if ((COM_RXTPINFOUSEDOFRXPDUINFO == STD_ON) && (COM_EXISTS_UINT8_DYN_APPLTYPEOFRXACCESSINFO == STD_ON))
      case COM_UINT8_DYN_APPLTYPEOFRXACCESSINFO:
      {
        P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) SignalBusSourcePtr;
        PduLengthType dynLength;
        SignalBusSourcePtr = &(PduInfoPtr->SduDataPtr[Com_GetStartByteInPduPositionOfRxAccessInfo(idxRxAccessInfo)]);
        dynLength = Com_GetRxDynamicLength(PduInfoPtr->SduLength, idxRxAccessInfo);
        if(dynLength <= Com_GetTmpRxShdBufferArrayBasedTmpBufferLengthOfRxAccessInfo(idxRxAccessInfo))  /* COV_COM_SILENT_TX */
        {
          VStdLib_MemCpy_s(Com_GetAddrTmpRxShdBufferArrayBased(Com_GetTmpRxShdBufferArrayBasedTmpBufferStartIdxOfRxAccessInfo(idxRxAccessInfo)), (VStdLib_CntType) Com_GetTmpRxShdBufferArrayBasedTmpBufferLengthOfRxAccessInfo(idxRxAccessInfo), SignalBusSourcePtr, (VStdLib_CntType) dynLength);     /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_COM_VSTDLIB_SAFE */
        }
        break;
      }
#  endif
# endif
      default: /* COV_COM_MISRA */
        break;
    }
  }
}       /* PRQA S 6030, 6050 */ /* MD_MSR_STCYC, MD_MSR_STCAL */
#endif

#if ((COM_RXSIGGRPINFOINDENDIDXOFRXPDUINFO == STD_ON) && (COM_FILTEREVENTOFRXSIGGRPINFO == STD_ON))
/**********************************************************************************************************************
  Com_RxProcessing_RxSignalGroupFilterCheck
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(Com_RxSigProcessState, COM_CODE) Com_RxProcessing_RxSignalGroupFilterCheck(Com_RxSigGrpInfoIterType idxRxSigGrpInfo)
{
  Com_RxSigProcessState retVal = VALID; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  boolean hasToutOccurred = FALSE;
# if (COM_RXTOUTINFOUSEDOFRXSIGGRPINFO == STD_ON)
  /* #10 If the ComSignalGroup has a Timeout, check if that timeout has occurred */
  if(Com_IsRxTOutInfoUsedOfRxSigGrpInfo(idxRxSigGrpInfo))
  {
    hasToutOccurred = Com_LMgt_HasTimeoutOccurred(Com_GetRxTOutInfoIdxOfRxSigGrpInfo(idxRxSigGrpInfo));
  }
# endif
  {
    Com_RxAccessInfoIndIterType RxAccessInfoIndidx = Com_GetRxAccessInfoGrpSigIndStartIdxOfRxSigGrpInfo(idxRxSigGrpInfo);
    boolean filterState = FALSE;
# if ((COM_SHDBUFFERUSEDOFRXACCESSINFO == STD_ON)||((COM_RXSIGBUFFERARRAYBASEDSHDBUFFERUSEDOFRXACCESSINFO == STD_ON) && (COM_EXISTS_UINT8_N_APPLTYPEOFRXACCESSINFO == STD_ON)))
    /* #20 Iterate over all ComGroupSignals of the passed ComSignalGroup */
    for(; RxAccessInfoIndidx < Com_GetRxAccessInfoGrpSigIndEndIdxOfRxSigGrpInfo(idxRxSigGrpInfo); RxAccessInfoIndidx++)
    {
      Com_RxAccessInfoIterType idxRxAccessInfo = Com_GetRxAccessInfoGrpSigInd(RxAccessInfoIndidx);
      /* #30 Check filter state according to configured filter algorithm and the configured signal ApplType */
      switch (Com_GetApplTypeOfRxAccessInfo(idxRxAccessInfo))
      {
#  if ((COM_TMPRXSHDBUFFERUINT8 == STD_ON) && (COM_FILTERINFO_UINT8 == STD_ON))
        case COM_UINT8_APPLTYPEOFRXACCESSINFO:
        {
          filterState =
            Com_Signal_UInt8_EvaluateFilter((Com_FilterInfo_UInt8IterType) Com_GetFilterInfoIdxOfRxAccessInfo(idxRxAccessInfo),
                                            Com_GetTmpRxShdBufferUInt8(Com_GetTmpBufferIdxOfRxAccessInfo(idxRxAccessInfo)),
                                            Com_GetRxSigBufferUInt8(Com_GetShdBufferIdxOfRxAccessInfo(idxRxAccessInfo)), hasToutOccurred);
          break;
        }
#  endif
#  if ((COM_TMPRXSHDBUFFERSINT8 == STD_ON) && (COM_FILTERINFO_SINT8 == STD_ON))
        case COM_SINT8_APPLTYPEOFRXACCESSINFO:
        {
          filterState =
            Com_Signal_SInt8_EvaluateFilter((Com_FilterInfo_SInt8IterType) Com_GetFilterInfoIdxOfRxAccessInfo(idxRxAccessInfo),
                                            Com_GetTmpRxShdBufferSInt8(Com_GetTmpBufferIdxOfRxAccessInfo(idxRxAccessInfo)),
                                            Com_GetRxSigBufferSInt8(Com_GetShdBufferIdxOfRxAccessInfo(idxRxAccessInfo)), hasToutOccurred);
          break;
        }
#  endif
#  if ((COM_TMPRXSHDBUFFERUINT16 == STD_ON) && (COM_FILTERINFO_UINT16 == STD_ON))
        case COM_UINT16_APPLTYPEOFRXACCESSINFO:
        {
          filterState =
            Com_Signal_UInt16_EvaluateFilter((Com_FilterInfo_UInt16IterType) Com_GetFilterInfoIdxOfRxAccessInfo(idxRxAccessInfo),
                                             Com_GetTmpRxShdBufferUInt16(Com_GetTmpBufferIdxOfRxAccessInfo(idxRxAccessInfo)),
                                             Com_GetRxSigBufferUInt16(Com_GetShdBufferIdxOfRxAccessInfo(idxRxAccessInfo)), hasToutOccurred);
          break;
        }
#  endif
#  if ((COM_TMPRXSHDBUFFERSINT16 == STD_ON) && (COM_FILTERINFO_SINT16 == STD_ON))
        case COM_SINT16_APPLTYPEOFRXACCESSINFO:
        {
          filterState =
            Com_Signal_SInt16_EvaluateFilter((Com_FilterInfo_SInt16IterType) Com_GetFilterInfoIdxOfRxAccessInfo(idxRxAccessInfo),
                                             Com_GetTmpRxShdBufferSInt16(Com_GetTmpBufferIdxOfRxAccessInfo(idxRxAccessInfo)),
                                             Com_GetRxSigBufferSInt16(Com_GetShdBufferIdxOfRxAccessInfo(idxRxAccessInfo)), hasToutOccurred);
          break;
        }
#  endif
#  if ((COM_TMPRXSHDBUFFERUINT32 == STD_ON) && (COM_FILTERINFO_UINT32 == STD_ON))
        case COM_UINT32_APPLTYPEOFRXACCESSINFO:
        {
          filterState =
            Com_Signal_UInt32_EvaluateFilter((Com_FilterInfo_UInt32IterType) Com_GetFilterInfoIdxOfRxAccessInfo(idxRxAccessInfo),
                                             Com_GetTmpRxShdBufferUInt32(Com_GetTmpBufferIdxOfRxAccessInfo(idxRxAccessInfo)),
                                             Com_GetRxSigBufferUInt32(Com_GetShdBufferIdxOfRxAccessInfo(idxRxAccessInfo)), hasToutOccurred);
          break;
        }
#  endif
#  if ((COM_TMPRXSHDBUFFERSINT32 == STD_ON) && (COM_FILTERINFO_SINT32 == STD_ON))
        case COM_SINT32_APPLTYPEOFRXACCESSINFO:
        {
          filterState =
            Com_Signal_SInt32_EvaluateFilter((Com_FilterInfo_SInt32IterType) Com_GetFilterInfoIdxOfRxAccessInfo(idxRxAccessInfo),
                                             Com_GetTmpRxShdBufferSInt32(Com_GetTmpBufferIdxOfRxAccessInfo(idxRxAccessInfo)),
                                             Com_GetRxSigBufferSInt32(Com_GetShdBufferIdxOfRxAccessInfo(idxRxAccessInfo)), hasToutOccurred);
          break;
        }
#  endif
#  if ((COM_TMPRXSHDBUFFERUINT64 == STD_ON) && (COM_FILTERINFO_UINT64 == STD_ON))
        case COM_UINT64_APPLTYPEOFRXACCESSINFO:
        {
          filterState =
            Com_Signal_UInt64_EvaluateFilter((Com_FilterInfo_UInt64IterType) Com_GetFilterInfoIdxOfRxAccessInfo(idxRxAccessInfo),
                                             Com_GetTmpRxShdBufferUInt64(Com_GetTmpBufferIdxOfRxAccessInfo(idxRxAccessInfo)),
                                             Com_GetRxSigBufferUInt64(Com_GetShdBufferIdxOfRxAccessInfo(idxRxAccessInfo)), hasToutOccurred);
          break;
        }
#  endif
#  if ((COM_TMPRXSHDBUFFERSINT64 == STD_ON) && (COM_FILTERINFO_SINT64 == STD_ON))
        case COM_SINT64_APPLTYPEOFRXACCESSINFO:
        {
          filterState =
            Com_Signal_SInt64_EvaluateFilter((Com_FilterInfo_SInt64IterType) Com_GetFilterInfoIdxOfRxAccessInfo(idxRxAccessInfo),
                                             Com_GetTmpRxShdBufferSInt64(Com_GetTmpBufferIdxOfRxAccessInfo(idxRxAccessInfo)),
                                             Com_GetRxSigBufferSInt64(Com_GetShdBufferIdxOfRxAccessInfo(idxRxAccessInfo)), hasToutOccurred);
          break;
        }
#  endif
#  if((COM_TMPRXSHDBUFFERARRAYBASED == STD_ON) && (COM_FILTERINFO_UINT8_N == STD_ON))
        case COM_UINT8_N_APPLTYPEOFRXACCESSINFO:
        {
          /* *INDENT-OFF* */
           filterState = Com_Signal_UInt8_N_EvaluateFilter((Com_FilterInfo_UInt8_NIterType) Com_GetFilterInfoIdxOfRxAccessInfo(idxRxAccessInfo),
           Com_GetAddrTmpRxShdBufferArrayBased(Com_GetTmpRxShdBufferArrayBasedTmpBufferStartIdxOfRxAccessInfo(idxRxAccessInfo)),
           Com_GetAddrRxSigBufferArrayBased(Com_GetRxSigBufferArrayBasedShdBufferStartIdxOfRxAccessInfo(idxRxAccessInfo)),
           (PduLengthType) Com_GetRxSigBufferArrayBasedShdBufferLengthOfRxAccessInfo(idxRxAccessInfo), hasToutOccurred); /* SBSW_COM_FCTCALL_WITH_P2CONST */
         /* *INDENT-ON* */
          break;
        }
#  endif
/* filterState will be always FALSE for floating-point signals, no filter evaluation is needed */
#  if ((COM_TMPRXSHDBUFFERFLOAT32 == STD_ON) && (COM_FILTERINFO_FLOAT32 == STD_ON))
        case COM_FLOAT32_APPLTYPEOFRXACCESSINFO:
#  endif
#  if ((COM_TMPRXSHDBUFFERFLOAT64 == STD_ON) && (COM_FILTERINFO_FLOAT64 == STD_ON))
        case COM_FLOAT64_APPLTYPEOFRXACCESSINFO:
#  endif
        default:       /* COV_COM_MISRA */
          break;
      }
      /* #40 If Filter evaluates to TRUE, stop evaluating remaining group signals. */
      if(filterState == TRUE)
      {
        break;
      }
    }
    /* #50 If any of the group signal filters evaluates to TRUE, return VALID */
    /* #60 Otherwise return FILTERED */
    if(filterState == FALSE)
# endif
    {
      retVal = FILTERED;
    }

    COM_DUMMY_STATEMENT(hasToutOccurred);       /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
    COM_DUMMY_STATEMENT(RxAccessInfoIndidx);    /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
    COM_DUMMY_STATEMENT(filterState);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  }
  return retVal;
}       /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */
#endif

#if ((COM_RXSIGGRPINFOINDENDIDXOFRXPDUINFO == STD_ON) && (COM_UBMASKUSEDOFRXSIGGRPINFO == STD_ON))
/**********************************************************************************************************************
  Com_RxProcessing_CheckSigGrpUB
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(boolean, COM_CODE) Com_RxProcessing_CheckSigGrpUB(P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr, Com_RxSigGrpInfoIterType idxRxSigGrpInfo)
{
  boolean retVal = TRUE;        /* PRQA S 2981 */ /* MD_MSR_RetVal */
  /* #10 If the ComSignalGroup has an UpdateBit */
  if(NULL_PTR != PduInfoPtr->SduDataPtr)        /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    if(Com_IsUbMaskUsedOfRxSigGrpInfo(idxRxSigGrpInfo)) /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
    {
      /* #20 If the configured UpdateBit was not received mark the ComSignalGroup as updated */
      if(PduInfoPtr->SduLength <= Com_GetUbIdxOfRxSigGrpInfo(idxRxSigGrpInfo))
      {
        /* Update-bit not received */
        retVal = TRUE;
      }
      /* #30 If the UpdateBit is not set, mark the ComSignalGroup as not updated */
      else if(0u == (PduInfoPtr->SduDataPtr[Com_GetUbIdxOfRxSigGrpInfo(idxRxSigGrpInfo)] & Com_GetConstValueUInt8(Com_GetUbMaskIdxOfRxSigGrpInfo(idxRxSigGrpInfo))))    /* PRQA S 2822 */ /* MD_Com_2822 */
      {
        /* Update-bit not set */
        retVal = FALSE;
      }
      /* #40 Otherwise mark the ComSignalGroup as updated */
      else
      {
        /* Update-bit set */
        retVal = TRUE;
      }
    }
  }
  return retVal;
}
#endif

#if ((COM_RXSIGINFOENDIDXOFRXPDUINFO == STD_ON) && (COM_UBMASKUSEDOFRXSIGINFO == STD_ON))
/**********************************************************************************************************************
  Com_RxProcessing_CheckSigUB
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(boolean, COM_CODE) Com_RxProcessing_CheckSigUB(Com_RxSigInfoIterType idxRxSigInfo, P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr)
{
  boolean retVal = TRUE;        /* PRQA S 2981 */ /* MD_MSR_RetVal */
  /* #10 If the ComSignal has an UpdateBit */
  if(NULL_PTR != PduInfoPtr->SduDataPtr)        /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    if(Com_IsUbMaskUsedOfRxSigInfo(idxRxSigInfo))       /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
    {
      /* #20 If the configured UpdateBit was not received mark the ComSignal as updated */
      /* <= because a length is compared with an index */
      if(PduInfoPtr->SduLength <= Com_GetUbIdxOfRxSigInfo(idxRxSigInfo))
      {
        /* Update-bit not received */
        retVal = TRUE;
      }
      /* #30 If the UpdateBit is not set, mark the ComSignal as not updated */
      else if(0u == (PduInfoPtr->SduDataPtr[Com_GetUbIdxOfRxSigInfo(idxRxSigInfo)] & Com_GetConstValueUInt8(Com_GetUbMaskIdxOfRxSigInfo(idxRxSigInfo))))        /* PRQA S 2822 */ /* MD_Com_2822 */
      {
        /* Update-bit not set */
        retVal = FALSE;
      }
      /* #40 Otherwise mark the ComSignal as updated */
      else
      {
        /* Update-bit set */
        retVal = TRUE;
      }
    }
  }
  return retVal;
}
#endif

#if (COM_RXSIGGRPINFOINDENDIDXOFRXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxProcessing_ProcessSigGrpEvent
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
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_RxProcessing_ProcessSigGrpEvent(PduIdType comRxPduInfoIdx, P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr, Com_RxSigGrpInfoIterType idxRxSigGrpInfo, P2VAR(FctPtrCacheStrct, AUTOMATIC, COM_APPL_DATA) fctPtrCacheStrctPtr)        /* PRQA S 3673 */ /* MD_MSR_Rule8.13 */
{
# if ((COM_INVEVENTOFRXSIGGRPINFO == STD_ON) || (COM_FILTEREVENTOFRXSIGGRPINFO == STD_ON))
  Com_RxSigProcessState process = VALID;        /* PRQA S 2981 */ /* MD_MSR_RetVal */
# endif
# if ((COM_SHDBUFFERREQUIREDOFRXSIGGRPINFO == STD_ON) || (COM_ARRAYACCESSUSEDOFRXSIGGRPINFO == STD_ON))
  /* #10 Read the passed ComSignalGroup values form the passed ComIPdu */
  Com_RxProcessing_ReadSignalGroup(PduInfoPtr, idxRxSigGrpInfo);        /* SBSW_COM_FCTCALL_WITH_P2CONST */
# endif
# if (((COM_MINPROCGWBUFFERUSEDOFRXACCESSINFO == STD_ON) || (COM_MINPROCGWBUFFERARRAYBASEDBUFFERUSEDOFRXACCESSINFO == STD_ON)) && (COM_GWSIGGRPMAPPINGENDIDXOFGWINFO == STD_ON))
  Com_RxProcessing_ExtractToMinProcGwBuffer(idxRxSigGrpInfo, PduInfoPtr);       /* SBSW_COM_FCTCALL_WITH_P2CONST */
# endif
# if (COM_INVEVENTOFRXSIGGRPINFO == STD_ON)
  /* \trace SPEC-2736832 */
  /* #20 Evaluate whether any new value of the related ComGroupSignals is an invalid value */
  process = Com_RxInv_SigGrp(idxRxSigGrpInfo, fctPtrCacheStrctPtr, PduInfoPtr->SduLength);      /* SBSW_COM_FCTPTR_CACHE_PTR */
  /* #30 If the new value of all related ComGroupSignal is valid */
  if(process == VALID)
# endif
  {
# if (COM_FILTEREVENTOFRXSIGGRPINFO == STD_ON)
    /* #40 Evaluate the current filter state */
    if(Com_IsFilterEventOfRxSigGrpInfo(idxRxSigGrpInfo))        /* COV_COM_FILTER_ALWAYS_PRESENT */
    {
      process = Com_RxProcessing_RxSignalGroupFilterCheck(idxRxSigGrpInfo);
    }
    if(process == VALID)        /* \trace SPEC-2736777 */ /* \trace SPEC-2736778 */
# endif
    {
# if (COM_SHDBUFFERREQUIREDOFRXSIGGRPINFO == STD_ON)
      /* #60 If no ComSignalGroup Array Access is used or array based gateway routing is configured, extract group signal data to the shadow buffer */
      if(Com_IsShdBufferRequiredOfRxSigGrpInfo(idxRxSigGrpInfo))        /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
      {
        Com_RxProcessing_ExtractToShdwBffr(idxRxSigGrpInfo, PduInfoPtr);        /* SBSW_COM_FCTCALL_WITH_P2CONST */
      }
# endif
# if ((COM_RXTOUTINFOUSEDOFRXSIGGRPINFO == STD_ON) && (COM_UBMASKIDXOFRXSIGGRPINFO == STD_ON))
      /* #70 If the ComSiganlGroup has a timeout and an UpdateBit, remove the timeout occurred flag */
      if(Com_IsRxTOutInfoUsedOfRxSigGrpInfo(idxRxSigGrpInfo) && Com_IsUbMaskUsedOfRxSigGrpInfo(idxRxSigGrpInfo))        /* COV_COM_FEATURE_RX_TOUT_WITH_UB */
      {
        Com_LMgt_RemoveOccurredFlag(Com_GetRxTOutInfoIdxOfRxSigGrpInfo(idxRxSigGrpInfo));       /* SBSW_COM_CSL02_CSL03 */
      }
# endif
# if (COM_RXCBKFUNCPTRACKIDXOFRXSIGGRPINFO == STD_ON)
      /* #80 Cache or Call the related Rx notification functions */
      if(Com_IsRxCbkFuncPtrAckUsedOfRxSigGrpInfo(idxRxSigGrpInfo))      /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
      {
        Com_CacheOrCallRxCbkFctPtr((Com_RxCbkFuncPtrIterType) Com_GetRxCbkFuncPtrAckIdxOfRxSigGrpInfo(idxRxSigGrpInfo), comRxPduInfoIdx, fctPtrCacheStrctPtr);  /* SBSW_COM_FCTPTR_CACHE_PTR */
      }
# endif
    }
  }

  COM_DUMMY_STATEMENT(comRxPduInfoIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT_CONST(PduInfoPtr);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(idxRxSigGrpInfo); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(fctPtrCacheStrctPtr);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}
#endif

#if ((COM_SHDBUFFERREQUIREDOFRXSIGGRPINFO == STD_ON) || (COM_ARRAYACCESSUSEDOFRXSIGGRPINFO == STD_ON))
/**********************************************************************************************************************
  Com_RxProcessing_ReadSignalGroup
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_RxProcessing_ReadSignalGroup(P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr, Com_RxSigGrpInfoIterType idxRxSigGrpInfo)
{
# if (COM_ARRAYACCESSUSEDOFRXSIGGRPINFO == STD_ON)
  /* #10 If ComSignalGroup Array Access is used, copy the passed ComSignalGroup data to the shadow buffer */
  if(Com_IsArrayAccessUsedOfRxSigGrpInfo(idxRxSigGrpInfo))      /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    Com_RxSigArrayAccessSigGrpBufferIterType ShdBufferStartIndex = Com_GetRxSigArrayAccessSigGrpBufferStartIdxOfRxSigGrpInfo(idxRxSigGrpInfo);
    P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) SignalSourcePtr = &(PduInfoPtr->SduDataPtr[Com_GetStartBytePositionOfRxSigGrpInfo(idxRxSigGrpInfo)]);     /* PRQA S 2822 */ /* MD_Com_2822 */
    VStdMemCpyRamToRam(Com_GetAddrRxSigArrayAccessSigGrpBuffer(ShdBufferStartIndex), SignalSourcePtr, Com_GetRxSigArrayAccessSigGrpBufferLengthOfRxSigGrpInfo(idxRxSigGrpInfo));        /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_COM_CSL02 */
  }

# endif

# if (COM_SHDBUFFERREQUIREDOFRXSIGGRPINFO == STD_ON)
  /* #20 If shadow buffers are required (normal signal group or gateway array access routing), extract all group signals to their shadow buffers */
  if(Com_IsShdBufferRequiredOfRxSigGrpInfo(idxRxSigGrpInfo))    /* COV_COM_SHDBUFFER_REQUIRED */
  {
    Com_RxAccessInfoIndIterType RxAccessInfoIndidx = Com_GetRxAccessInfoGrpSigIndStartIdxOfRxSigGrpInfo(idxRxSigGrpInfo);
    for(; RxAccessInfoIndidx < Com_GetRxAccessInfoGrpSigIndEndIdxOfRxSigGrpInfo(idxRxSigGrpInfo); RxAccessInfoIndidx++)
    {
      Com_RxProcessing_ReadGrpSignal(PduInfoPtr, Com_GetRxAccessInfoGrpSigInd(RxAccessInfoIndidx));     /* SBSW_COM_FCTCALL_WITH_P2CONST */
    }
  }
# endif

  COM_DUMMY_STATEMENT(idxRxSigGrpInfo); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}
#endif

#if(COM_EXISTS_DEFERRED_SIGNALPROCESSINGOFRXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxProcessing_EnterExclusiveArea_Deferred
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_RxProcessing_EnterExclusiveArea_Deferred(void)
{
  /* #10 Enter the rx deferred exclusive area */
  SchM_Enter_Com_COM_EXCLUSIVE_AREA_RX();
}

/**********************************************************************************************************************
  Com_RxProcessing_ExitExclusiveArea_Deferred
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_RxProcessing_ExitExclusiveArea_Deferred(void)
{
  /* #05 Reload the counter with the threshold value */
  Com_SetRxDeferredProcessingISRLockCounter(Com_GetRxDeferredProcessingISRLockThreshold());     /* SBSW_COM_CSL_VAR_ACCESS */
  /* #10 Exit the rx deferred exclusive area */
  SchM_Exit_Com_COM_EXCLUSIVE_AREA_RX();
}

/**********************************************************************************************************************
  Com_RxProcessing_ThresholdCheck_Deferred
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_RxProcessing_ThresholdCheck_Deferred(P2VAR(FctPtrCacheStrct, AUTOMATIC, COM_APPL_DATA) fctPtrCacheStrctPtr)   /* PRQA S 3673 */ /* MD_MSR_Rule8.13 */
{
  if(Com_GetRxDeferredProcessingISRLockCounter() > 0u)
  {
    Com_DecRxDeferredProcessingISRLockCounter();        /* SBSW_COM_CSL_VAR_ACCESS */
  }
  else
  {
    Com_RxProcessing_ExitExclusiveArea_Deferred();
# if (COM_RXDEFERREDFCTPTRCACHE == STD_ON)
    Com_ProcessRxFctPtrCache(fctPtrCacheStrctPtr);      /* SBSW_COM_FCTPTR_CACHE_PTR */
# endif
    Com_RxProcessing_EnterExclusiveArea_Deferred();
  }

  COM_DUMMY_STATEMENT(fctPtrCacheStrctPtr);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}
#endif

#if (COM_EXISTS_DEFERRED_SIGNALPROCESSINGOFRXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxProcessing_IsDeferredProcessingRequested
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(boolean, COM_CODE) Com_RxProcessing_IsDeferredProcessingRequested(Com_SizeOfRxPduInfoType idxRxPduInfo)
{
  /* #10 Evaluate if deferred processing needs to be performed for the passed Rx ComIPdu */
  boolean retVal = FALSE;       /* PRQA S 2981 */ /* MD_MSR_RetVal */
  if(Com_IsHandleRxPduDeferredUsedOfRxPduInfo(idxRxPduInfo))    /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    if(Com_IsRxPduGrpActive(idxRxPduInfo))
    {
      if(0u < Com_GetHandleRxPduDeferred(Com_GetHandleRxPduDeferredIdxOfRxPduInfo(idxRxPduInfo)))       /* COV_COM_RX_PROCESSING_SINGLEPDU */
      {
        retVal = TRUE;
      }
    }
  }

  return retVal;
}
#endif

#if (COM_EXISTS_DEFERRED_SIGNALPROCESSINGOFRXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxProcessDeferredPDU
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
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_RxProcessDeferredPDU(PduIdType idxRxPduInfo, P2VAR(FctPtrCacheStrct, AUTOMATIC, COM_APPL_DATA) deferredfctPtrCacheStrctPtr)   /* PRQA S 3206, 3673 */ /* MD_Com_3206, MD_MSR_Rule8.13 */
{
  PduInfoType PduInfo;

  /* #10 Create a PduInfoType with the stored SduLength and the stored deferred Pdu data buffer */
  PduInfo.SduLength = Com_GetHandleRxPduDeferred(Com_GetHandleRxPduDeferredIdxOfRxPduInfo(idxRxPduInfo)) - 1u;
  PduInfo.SduDataPtr = NULL_PTR;

  switch (Com_GetTypeOfRxPduInfo(idxRxPduInfo))
  {
# if (COM_RXTPINFOUSEDOFRXPDUINFO == STD_ON)
    case COM_TP_TYPEOFRXPDUINFO:
    {
      /* #20 If the Rx ComIPdu is a Tp Pdu use the Tp buffer as SduDataPtr */
      Com_RxTpInfoIdxOfRxPduInfoType rxTpPduInfoIdx = Com_GetRxTpInfoIdxOfRxPduInfo(idxRxPduInfo);
      PduInfo.SduDataPtr = Com_GetAddrRxTpBuffer(Com_GetRxTpBufferStartIdxOfRxTpInfo(rxTpPduInfoIdx));
      break;
    }
# endif
# if (COM_EXISTS_NORMAL_TYPEOFRXPDUINFO == STD_ON)
    case COM_NORMAL_TYPEOFRXPDUINFO:
    {
      /* #35 Use the normal deferred Pdu buffer if present, else use NULL_PTR */
#  if (COM_RXDEFPDUBUFFERUSEDOFRXPDUINFO == STD_ON)
      if(Com_IsRxDefPduBufferUsedOfRxPduInfo(idxRxPduInfo))     /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
      {
        PduInfo.SduDataPtr = Com_GetAddrRxDefPduBuffer(Com_GetRxDefPduBufferStartIdxOfRxPduInfo(idxRxPduInfo));
      }
#  endif
      break;
    }
# endif
    default:   /* COV_COM_MISRA */
      break;
  }

  /* #40 Reset the "Handle Deferred" flag */
  Com_SetHandleRxPduDeferred(Com_GetHandleRxPduDeferredIdxOfRxPduInfo(idxRxPduInfo), 0);        /* SBSW_COM_CSL03 */

# if (COM_RXSIGINFOENDIDXOFRXPDUINFO == STD_ON)
  /* #50 Do Rx ComSignal processing for the passed Rx ComIPdu */
  Com_RxProcessing_RxPduSigEvent(idxRxPduInfo, &PduInfo, deferredfctPtrCacheStrctPtr);  /* SBSW_COM_FCTCALL_STACKPTR */
# endif
# if (COM_RXSIGGRPINFOINDENDIDXOFRXPDUINFO == STD_ON)
  /* #60 Do Rx ComSignalGroup processing for the passed Rx ComIPdu */
  Com_RxProcessing_RxPduSigGrpEvent(idxRxPduInfo, &PduInfo, deferredfctPtrCacheStrctPtr);       /* SBSW_COM_FCTCALL_STACKPTR */
# endif

# if (COM_RXTOUTINFOUSEDOFRXPDUINFO == STD_ON)
  /* #70 If the passed Rx ComIPdu has a timeout, remove the timeout occurred flag */
  if(Com_IsRxTOutInfoUsedOfRxPduInfo(idxRxPduInfo))     /* COV_COM_RXDEFERRED_TIMEOUT */
  {
    Com_LMgt_RemoveOccurredFlag(Com_GetRxTOutInfoIdxOfRxPduInfo(idxRxPduInfo)); /* SBSW_COM_CSL02_CSL03 */
  }
# endif

# if (COM_RXTPINFOUSEDOFRXPDUINFO == STD_ON)
  /* #80 If the Rx ComIPdu is a Tp pdu, reset the tp parameter */
  if(Com_GetTypeOfRxPduInfo(idxRxPduInfo) == COM_TP_TYPEOFRXPDUINFO)    /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    Com_ResetRxTpConnection(idxRxPduInfo);
  }
# endif
  COM_DUMMY_STATEMENT(PduInfo); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(deferredfctPtrCacheStrctPtr);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}
#endif

#if (COM_EXISTS_DEFERRED_SIGNALPROCESSINGOFRXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxDeferredPduProcessing_IterateOverAllRxPdus
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_RxDeferredPduProcessing_IterateOverAllRxPdus(P2VAR(FctPtrCacheStrct, AUTOMATIC, COM_APPL_DATA) deferredFctPtrCacheStrct)
{
  Com_SizeOfRxPduInfoType idxRxPduInfo;

# if (COM_RXDEFERREDEVENTCACHE == STD_ON)
  /* #10 Reset deferred event caching index */
  Com_SetRxNextEventCacheEnty(0);       /* SBSW_COM_CSL_VAR_ACCESS */
# endif
  /* #20 Iterate over all Rx ComIPdus and If a "process deferred" flag is set, process that Rx ComIPdu */
  for(idxRxPduInfo = 0; idxRxPduInfo < Com_GetSizeOfRxPduInfo(); idxRxPduInfo++)
  {
    if(Com_RxProcessing_IsDeferredProcessingRequested(idxRxPduInfo) == TRUE)
    {
      Com_RxProcessDeferredPDU((PduIdType) idxRxPduInfo, deferredFctPtrCacheStrct);     /* SBSW_COM_FCTPTR_CACHE_PTR_1 */
    }   /* Is HandleRxPduDeferred Used */
    Com_RxProcessing_ThresholdCheck_Deferred(deferredFctPtrCacheStrct); /* SBSW_COM_FCTPTR_CACHE_PTR_1 */
  }
}
#endif

#if (COM_RXSIGINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxSignalProcessing
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(Com_RxSigProcessState, COM_CODE) Com_RxSignalProcessing(P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr, Com_RxAccessInfoIdxOfRxSigInfoType idxRxAccessInfo)    /* PRQA S 3206 */ /* MD_Com_3206 */
{
  Com_RxSigProcessState processState = VALID;   /* PRQA S 2981 */ /* MD_MSR_RetVal */

  if(NULL_PTR != PduInfoPtr->SduDataPtr)        /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    /* #10 process the passed signal signal type dependent */
    switch (Com_GetApplTypeOfRxAccessInfo(idxRxAccessInfo))
    {
# if (COM_EXISTS_UINT8_APPLTYPEOFRXACCESSINFO == STD_ON)
      case COM_UINT8_APPLTYPEOFRXACCESSINFO:
      {
        processState = Com_RxSignalProcessing_UINT8(PduInfoPtr, idxRxAccessInfo);       /* SBSW_COM_VALID_PTR_ENSURED_BY_CALLING_FUNC */
        break;
      }
# endif
# if (COM_EXISTS_SINT8_APPLTYPEOFRXACCESSINFO == STD_ON)
      case COM_SINT8_APPLTYPEOFRXACCESSINFO:
      {
        processState = Com_RxSignalProcessing_SINT8(PduInfoPtr, idxRxAccessInfo);       /* SBSW_COM_VALID_PTR_ENSURED_BY_CALLING_FUNC */
        break;
      }
# endif
# if (COM_EXISTS_UINT16_APPLTYPEOFRXACCESSINFO == STD_ON)
      case COM_UINT16_APPLTYPEOFRXACCESSINFO:
      {
        processState = Com_RxSignalProcessing_UINT16(PduInfoPtr, idxRxAccessInfo);      /* SBSW_COM_VALID_PTR_ENSURED_BY_CALLING_FUNC */
        break;
      }
# endif
# if (COM_EXISTS_SINT16_APPLTYPEOFRXACCESSINFO == STD_ON)
      case COM_SINT16_APPLTYPEOFRXACCESSINFO:
      {
        processState = Com_RxSignalProcessing_SINT16(PduInfoPtr, idxRxAccessInfo);      /* SBSW_COM_VALID_PTR_ENSURED_BY_CALLING_FUNC */
        break;
      }
# endif
# if (COM_EXISTS_UINT32_APPLTYPEOFRXACCESSINFO == STD_ON)
      case COM_UINT32_APPLTYPEOFRXACCESSINFO:
      {
        processState = Com_RxSignalProcessing_UINT32(PduInfoPtr, idxRxAccessInfo);      /* SBSW_COM_VALID_PTR_ENSURED_BY_CALLING_FUNC */
        break;
      }
# endif
# if (COM_EXISTS_SINT32_APPLTYPEOFRXACCESSINFO == STD_ON)
      case COM_SINT32_APPLTYPEOFRXACCESSINFO:
      {
        processState = Com_RxSignalProcessing_SINT32(PduInfoPtr, idxRxAccessInfo);      /* SBSW_COM_VALID_PTR_ENSURED_BY_CALLING_FUNC */
        break;
      }
# endif
# if (COM_EXISTS_UINT64_APPLTYPEOFRXACCESSINFO == STD_ON)
      case COM_UINT64_APPLTYPEOFRXACCESSINFO:
      {
        processState = Com_RxSignalProcessing_UINT64(PduInfoPtr, idxRxAccessInfo);      /* SBSW_COM_VALID_PTR_ENSURED_BY_CALLING_FUNC */
        break;
      }
# endif
# if (COM_EXISTS_SINT64_APPLTYPEOFRXACCESSINFO == STD_ON)
      case COM_SINT64_APPLTYPEOFRXACCESSINFO:
      {
        processState = Com_RxSignalProcessing_SINT64(PduInfoPtr, idxRxAccessInfo);      /* SBSW_COM_VALID_PTR_ENSURED_BY_CALLING_FUNC */
        break;
      }
# endif
# if (COM_EXISTS_FLOAT32_APPLTYPEOFRXACCESSINFO == STD_ON)
      case COM_FLOAT32_APPLTYPEOFRXACCESSINFO:
      {
        processState = Com_RxSignalProcessing_FLOAT32(PduInfoPtr, idxRxAccessInfo);     /* SBSW_COM_VALID_PTR_ENSURED_BY_CALLING_FUNC */
        break;
      }
# endif
# if (COM_EXISTS_FLOAT64_APPLTYPEOFRXACCESSINFO == STD_ON)
      case COM_FLOAT64_APPLTYPEOFRXACCESSINFO:
      {
        processState = Com_RxSignalProcessing_FLOAT64(PduInfoPtr, idxRxAccessInfo);     /* SBSW_COM_VALID_PTR_ENSURED_BY_CALLING_FUNC */
        break;
      }
# endif
# if(COM_EXISTS_UINT8_N_APPLTYPEOFRXACCESSINFO == STD_ON)
      case COM_UINT8_N_APPLTYPEOFRXACCESSINFO: /* COV_COM_APPLTYPEOFRXACCESSINFO */
      {
        processState = Com_RxSignalProcessing_UINT8_N(PduInfoPtr, idxRxAccessInfo);     /* SBSW_COM_VALID_PTR_ENSURED_BY_CALLING_FUNC */
        break;
      }
# endif
# if ((COM_RXTPINFOUSEDOFRXPDUINFO == STD_ON) && (COM_EXISTS_UINT8_DYN_APPLTYPEOFRXACCESSINFO == STD_ON))
      case COM_UINT8_DYN_APPLTYPEOFRXACCESSINFO:
      {
        processState = Com_RxSignalProcessing_UINT8_DYN(PduInfoPtr, idxRxAccessInfo);   /* SBSW_COM_VALID_PTR_ENSURED_BY_CALLING_FUNC */
        break;
      }
# endif
# if(COM_EXISTS_ZEROBIT_APPLTYPEOFRXACCESSINFO == STD_ON)
      case COM_ZEROBIT_APPLTYPEOFRXACCESSINFO: /* COV_COM_APPLTYPEOFRXACCESSINFO */
      {
        break;  /* place holder for zeroBit Appl.Types. No signalProcessing shall be done */
      }
# endif
      default: /* COV_COM_MISRA */
        break;
    }
  }

  COM_DUMMY_STATEMENT_CONST(PduInfoPtr);
  return processState;
}       /* PRQA S 6030, 6050 */ /* MD_MSR_STCYC, MD_MSR_STCAL */
#endif

#if ((COM_EXISTS_UINT8_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_RXSIGINFO == STD_ON))
/**********************************************************************************************************************
  Com_RxSignalProcessing_UINT8
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(Com_RxSigProcessState, COM_CODE) Com_RxSignalProcessing_UINT8(P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr, Com_RxAccessInfoIterType idxRxAccessInfo)
{
  Com_RxSigProcessState processState = VALID;   /* PRQA S 2981 */ /* MD_MSR_RetVal */
  /* Check for buffer is not required as there is always a buffer configured. Removed check Com_IsBufferUsedOfRxAccessInfo */
  uint8 tmpNewValue = Com_Signal_ReadSignal_UInt8(idxRxAccessInfo, &(PduInfoPtr->SduDataPtr[Com_GetBytePositionOfRxAccessInfo(idxRxAccessInfo)]));      /* SBSW_COM_FCTCALL_WITH_P2CONST */

# if (COM_INVVALUEUSEDOFRXACCESSINFO == STD_ON)
  processState = Com_RxInv_Sig_UInt8_EvaluateInvalidValue(idxRxAccessInfo, tmpNewValue);
  if(processState == VALID)     /* COV_COM_INVALIDATION_TX */
# endif
# if ((COM_FILTERINFOUSEDOFRXACCESSINFO == STD_ON) && (COM_FILTERINFO_UINT8 == STD_ON))
  {
    if(Com_IsFilterInfoUsedOfRxAccessInfo(idxRxAccessInfo))     /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
    {
      boolean filterState;
      boolean hasToutOccurred = FALSE;
#  if (COM_RXTOUTINFOUSEDOFRXACCESSINFO == STD_ON)
      if(Com_IsRxTOutInfoUsedOfRxAccessInfo(idxRxAccessInfo))   /* COV_COM_FEATURE_RX_TOUT_INFO_USED_XX */
      {
        hasToutOccurred = Com_LMgt_HasTimeoutOccurred(Com_GetRxTOutInfoIdxOfRxAccessInfo(idxRxAccessInfo));
      }
#  endif
      filterState =
        Com_Signal_UInt8_EvaluateFilter((Com_FilterInfo_UInt8IterType) Com_GetFilterInfoIdxOfRxAccessInfo(idxRxAccessInfo), tmpNewValue,
                                        Com_GetRxSigBufferUInt8(Com_GetBufferIdxOfRxAccessInfo(idxRxAccessInfo)), hasToutOccurred);
      if(filterState == FALSE)
      {
        processState = FILTERED;
      }
    }
  }
  if(processState == VALID)
# endif
  {
    Com_BufferIdxOfRxAccessInfoType idxBuffer = Com_GetBufferIdxOfRxAccessInfo(idxRxAccessInfo);
    Com_SetRxSigBufferUInt8(idxBuffer, tmpNewValue);    /* SBSW_COM_CSL03 */
  }

# if (COM_MINPROCGWBUFFERUSEDOFRXACCESSINFO == STD_ON)
  if(Com_IsMinProcGwBufferUsedOfRxAccessInfo(idxRxAccessInfo))
  {
    Com_SetMinProcGwBufferUInt8(Com_GetMinProcGwBufferIdxOfRxAccessInfo(idxRxAccessInfo), tmpNewValue); /* SBSW_COM_CSL03 */
  }
# endif

  COM_DUMMY_STATEMENT_CONST(PduInfoPtr);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(idxRxAccessInfo); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return processState;
}
#endif

#if ((COM_EXISTS_SINT8_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_RXSIGINFO == STD_ON))
/**********************************************************************************************************************
  Com_RxSignalProcessing_SINT8
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(Com_RxSigProcessState, COM_CODE) Com_RxSignalProcessing_SINT8(P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr, Com_RxAccessInfoIterType idxRxAccessInfo)
{
  Com_RxSigProcessState processState = VALID;   /* PRQA S 2981 */ /* MD_MSR_RetVal */
  /* Check for buffer is not required as there is always a buffer configured. Removed check Com_IsBufferUsedOfRxAccessInfo */
  sint8 tmpNewValue = Com_Signal_ReadSignal_SInt8(idxRxAccessInfo, &(PduInfoPtr->SduDataPtr[Com_GetBytePositionOfRxAccessInfo(idxRxAccessInfo)]));      /* SBSW_COM_FCTCALL_WITH_P2CONST */

# if (COM_INVVALUEUSEDOFRXACCESSINFO == STD_ON)
  processState = Com_RxInv_Sig_SInt8_EvaluateInvalidValue(idxRxAccessInfo, tmpNewValue);
  if(processState == VALID)     /* COV_COM_INVALIDATION_TX */
# endif
# if ((COM_FILTERINFOUSEDOFRXACCESSINFO == STD_ON) && (COM_FILTERINFO_SINT8 == STD_ON))
  {
    if(Com_IsFilterInfoUsedOfRxAccessInfo(idxRxAccessInfo))     /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
    {
      boolean filterState;
      boolean hasToutOccurred = FALSE;
#  if (COM_RXTOUTINFOUSEDOFRXACCESSINFO == STD_ON)
      if(Com_IsRxTOutInfoUsedOfRxAccessInfo(idxRxAccessInfo))   /* COV_COM_FEATURE_RX_TOUT_INFO_USED_XX */
      {
        hasToutOccurred = Com_LMgt_HasTimeoutOccurred(Com_GetRxTOutInfoIdxOfRxAccessInfo(idxRxAccessInfo));
      }
#  endif
      filterState =
        Com_Signal_SInt8_EvaluateFilter((Com_FilterInfo_SInt8IterType) Com_GetFilterInfoIdxOfRxAccessInfo(idxRxAccessInfo), tmpNewValue,
                                        Com_GetRxSigBufferSInt8(Com_GetBufferIdxOfRxAccessInfo(idxRxAccessInfo)), hasToutOccurred);
      if(filterState == FALSE)
      {
        processState = FILTERED;
      }
    }
  }
  if(processState == VALID)
# endif
  {
    Com_BufferIdxOfRxAccessInfoType idxBuffer = Com_GetBufferIdxOfRxAccessInfo(idxRxAccessInfo);
    Com_SetRxSigBufferSInt8(idxBuffer, tmpNewValue);    /* SBSW_COM_CSL03 */
  }

# if (COM_MINPROCGWBUFFERUSEDOFRXACCESSINFO == STD_ON)
  if(Com_IsMinProcGwBufferUsedOfRxAccessInfo(idxRxAccessInfo))
  {
    Com_SetMinProcGwBufferSInt8(Com_GetMinProcGwBufferIdxOfRxAccessInfo(idxRxAccessInfo), tmpNewValue); /* SBSW_COM_CSL03 */
  }
# endif

  COM_DUMMY_STATEMENT_CONST(PduInfoPtr);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(idxRxAccessInfo); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return processState;
}
#endif

#if ((COM_EXISTS_UINT16_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_RXSIGINFO == STD_ON))
/**********************************************************************************************************************
  Com_RxSignalProcessing_UINT16
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(Com_RxSigProcessState, COM_CODE) Com_RxSignalProcessing_UINT16(P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr, Com_RxAccessInfoIterType idxRxAccessInfo)
{
  Com_RxSigProcessState processState = VALID;   /* PRQA S 2981 */ /* MD_MSR_RetVal */
  /* Check for buffer is not required as there is always a buffer configured. Removed check Com_IsBufferUsedOfRxAccessInfo */
  uint16 tmpNewValue = Com_Signal_ReadSignal_UInt16(idxRxAccessInfo, &(PduInfoPtr->SduDataPtr[Com_GetBytePositionOfRxAccessInfo(idxRxAccessInfo)]));    /* SBSW_COM_FCTCALL_WITH_P2CONST */

# if (COM_INVVALUEUSEDOFRXACCESSINFO == STD_ON)
  processState = Com_RxInv_Sig_UInt16_EvaluateInvalidValue(idxRxAccessInfo, tmpNewValue);
  if(processState == VALID)     /* COV_COM_INVALIDATION_TX */
# endif
# if ((COM_FILTERINFOUSEDOFRXACCESSINFO == STD_ON) && (COM_FILTERINFO_UINT16 == STD_ON))
  {
    if(Com_IsFilterInfoUsedOfRxAccessInfo(idxRxAccessInfo))     /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
    {
      boolean filterState;
      boolean hasToutOccurred = FALSE;
#  if (COM_RXTOUTINFOUSEDOFRXACCESSINFO == STD_ON)
      if(Com_IsRxTOutInfoUsedOfRxAccessInfo(idxRxAccessInfo))   /* COV_COM_FEATURE_RX_TOUT_INFO_USED_XX */
      {
        hasToutOccurred = Com_LMgt_HasTimeoutOccurred(Com_GetRxTOutInfoIdxOfRxAccessInfo(idxRxAccessInfo));
      }
#  endif
      filterState =
        Com_Signal_UInt16_EvaluateFilter((Com_FilterInfo_UInt16IterType) Com_GetFilterInfoIdxOfRxAccessInfo(idxRxAccessInfo), tmpNewValue,
                                         Com_GetRxSigBufferUInt16(Com_GetBufferIdxOfRxAccessInfo(idxRxAccessInfo)), hasToutOccurred);
      if(filterState == FALSE)
      {
        processState = FILTERED;
      }
    }
  }
  if(processState == VALID)
# endif
  {
    Com_BufferIdxOfRxAccessInfoType idxBuffer = Com_GetBufferIdxOfRxAccessInfo(idxRxAccessInfo);
    Com_SetRxSigBufferUInt16(idxBuffer, tmpNewValue);   /* SBSW_COM_CSL03 */
  }

# if (COM_MINPROCGWBUFFERUSEDOFRXACCESSINFO == STD_ON)
  if(Com_IsMinProcGwBufferUsedOfRxAccessInfo(idxRxAccessInfo))
  {
    Com_SetMinProcGwBufferUInt16(Com_GetMinProcGwBufferIdxOfRxAccessInfo(idxRxAccessInfo), tmpNewValue);        /* SBSW_COM_CSL03 */
  }
# endif

  COM_DUMMY_STATEMENT_CONST(PduInfoPtr);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(idxRxAccessInfo); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return processState;
}
#endif

#if ((COM_EXISTS_SINT16_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_RXSIGINFO == STD_ON))
/**********************************************************************************************************************
  Com_RxSignalProcessing_SINT16
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(Com_RxSigProcessState, COM_CODE) Com_RxSignalProcessing_SINT16(P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr, Com_RxAccessInfoIterType idxRxAccessInfo)
{
  Com_RxSigProcessState processState = VALID;   /* PRQA S 2981 */ /* MD_MSR_RetVal */
  /* Check for buffer is not required as there is always a buffer configured. Removed check Com_IsBufferUsedOfRxAccessInfo */
  sint16 tmpNewValue = Com_Signal_ReadSignal_SInt16(idxRxAccessInfo, &(PduInfoPtr->SduDataPtr[Com_GetBytePositionOfRxAccessInfo(idxRxAccessInfo)]));    /* SBSW_COM_FCTCALL_WITH_P2CONST */

# if (COM_INVVALUEUSEDOFRXACCESSINFO == STD_ON)
  processState = Com_RxInv_Sig_SInt16_EvaluateInvalidValue(idxRxAccessInfo, tmpNewValue);
  if(processState == VALID)     /* COV_COM_INVALIDATION_TX */
# endif
# if ((COM_FILTERINFOUSEDOFRXACCESSINFO == STD_ON) && (COM_FILTERINFO_SINT16 == STD_ON))
  {
    if(Com_IsFilterInfoUsedOfRxAccessInfo(idxRxAccessInfo))     /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
    {
      boolean filterState;
      boolean hasToutOccurred = FALSE;
#  if (COM_RXTOUTINFOUSEDOFRXACCESSINFO == STD_ON)
      if(Com_IsRxTOutInfoUsedOfRxAccessInfo(idxRxAccessInfo))   /* COV_COM_FEATURE_RX_TOUT_INFO_USED_XX */
      {
        hasToutOccurred = Com_LMgt_HasTimeoutOccurred(Com_GetRxTOutInfoIdxOfRxAccessInfo(idxRxAccessInfo));
      }
#  endif
      filterState =
        Com_Signal_SInt16_EvaluateFilter((Com_FilterInfo_SInt16IterType) Com_GetFilterInfoIdxOfRxAccessInfo(idxRxAccessInfo), tmpNewValue,
                                         Com_GetRxSigBufferSInt16(Com_GetBufferIdxOfRxAccessInfo(idxRxAccessInfo)), hasToutOccurred);
      if(filterState == FALSE)
      {
        processState = FILTERED;
      }
    }
  }
  if(processState == VALID)
# endif
  {
    Com_BufferIdxOfRxAccessInfoType idxBuffer = Com_GetBufferIdxOfRxAccessInfo(idxRxAccessInfo);
    Com_SetRxSigBufferSInt16(idxBuffer, tmpNewValue);   /* SBSW_COM_CSL03 */
  }

# if (COM_MINPROCGWBUFFERUSEDOFRXACCESSINFO == STD_ON)
  if(Com_IsMinProcGwBufferUsedOfRxAccessInfo(idxRxAccessInfo))
  {
    Com_SetMinProcGwBufferSInt16(Com_GetMinProcGwBufferIdxOfRxAccessInfo(idxRxAccessInfo), tmpNewValue);        /* SBSW_COM_CSL03 */
  }
# endif

  COM_DUMMY_STATEMENT_CONST(PduInfoPtr);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(idxRxAccessInfo); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return processState;
}
#endif

#if ((COM_EXISTS_UINT32_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_RXSIGINFO == STD_ON))
/**********************************************************************************************************************
  Com_RxSignalProcessing_UINT32
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(Com_RxSigProcessState, COM_CODE) Com_RxSignalProcessing_UINT32(P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr, Com_RxAccessInfoIterType idxRxAccessInfo)
{
  Com_RxSigProcessState processState = VALID;   /* PRQA S 2981 */ /* MD_MSR_RetVal */
  /* Check for buffer is not required as there is always a buffer configured. Removed check Com_IsBufferUsedOfRxAccessInfo */
  uint32 tmpNewValue = Com_Signal_ReadSignal_UInt32(idxRxAccessInfo, &(PduInfoPtr->SduDataPtr[Com_GetBytePositionOfRxAccessInfo(idxRxAccessInfo)]));    /* SBSW_COM_FCTCALL_WITH_P2CONST */

# if (COM_INVVALUEUSEDOFRXACCESSINFO == STD_ON)
  processState = Com_RxInv_Sig_UInt32_EvaluateInvalidValue(idxRxAccessInfo, tmpNewValue);
  if(processState == VALID)     /* COV_COM_INVALIDATION_TX */
# endif
# if ((COM_FILTERINFOUSEDOFRXACCESSINFO == STD_ON) && (COM_FILTERINFO_UINT32 == STD_ON))
  {
    if(Com_IsFilterInfoUsedOfRxAccessInfo(idxRxAccessInfo))     /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
    {
      boolean filterState;
      boolean hasToutOccurred = FALSE;
#  if (COM_RXTOUTINFOUSEDOFRXACCESSINFO == STD_ON)
      if(Com_IsRxTOutInfoUsedOfRxAccessInfo(idxRxAccessInfo))   /* COV_COM_FEATURE_RX_TOUT_INFO_USED_XX */
      {
        hasToutOccurred = Com_LMgt_HasTimeoutOccurred(Com_GetRxTOutInfoIdxOfRxAccessInfo(idxRxAccessInfo));
      }
#  endif
      filterState =
        Com_Signal_UInt32_EvaluateFilter((Com_FilterInfo_UInt32IterType) Com_GetFilterInfoIdxOfRxAccessInfo(idxRxAccessInfo), tmpNewValue,
                                         Com_GetRxSigBufferUInt32(Com_GetBufferIdxOfRxAccessInfo(idxRxAccessInfo)), hasToutOccurred);
      if(filterState == FALSE)
      {
        processState = FILTERED;
      }
    }
  }
  if(processState == VALID)
# endif
  {
    Com_BufferIdxOfRxAccessInfoType idxBuffer = Com_GetBufferIdxOfRxAccessInfo(idxRxAccessInfo);
    Com_SetRxSigBufferUInt32(idxBuffer, tmpNewValue);   /* SBSW_COM_CSL03 */
  }

# if (COM_MINPROCGWBUFFERUSEDOFRXACCESSINFO == STD_ON)
  if(Com_IsMinProcGwBufferUsedOfRxAccessInfo(idxRxAccessInfo))
  {
    Com_SetMinProcGwBufferUInt32(Com_GetMinProcGwBufferIdxOfRxAccessInfo(idxRxAccessInfo), tmpNewValue);        /* SBSW_COM_CSL03 */
  }
# endif

  COM_DUMMY_STATEMENT_CONST(PduInfoPtr);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(idxRxAccessInfo); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return processState;
}
#endif

#if ((COM_EXISTS_SINT32_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_RXSIGINFO == STD_ON))
/**********************************************************************************************************************
  Com_RxSignalProcessing_SINT32
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(Com_RxSigProcessState, COM_CODE) Com_RxSignalProcessing_SINT32(P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr, Com_RxAccessInfoIterType idxRxAccessInfo)
{
  Com_RxSigProcessState processState = VALID;   /* PRQA S 2981 */ /* MD_MSR_RetVal */
  /* Check for buffer is not required as there is always a buffer configured. Removed check Com_IsBufferUsedOfRxAccessInfo */
  sint32 tmpNewValue = Com_Signal_ReadSignal_SInt32(idxRxAccessInfo, &(PduInfoPtr->SduDataPtr[Com_GetBytePositionOfRxAccessInfo(idxRxAccessInfo)]));    /* SBSW_COM_FCTCALL_WITH_P2CONST */

# if (COM_INVVALUEUSEDOFRXACCESSINFO == STD_ON)
  processState = Com_RxInv_Sig_SInt32_EvaluateInvalidValue(idxRxAccessInfo, tmpNewValue);
  if(processState == VALID)     /* COV_COM_INVALIDATION_TX */
# endif
# if ((COM_FILTERINFOUSEDOFRXACCESSINFO == STD_ON) && (COM_FILTERINFO_SINT32 == STD_ON))
  {
    if(Com_IsFilterInfoUsedOfRxAccessInfo(idxRxAccessInfo))     /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
    {
      boolean filterState;
      boolean hasToutOccurred = FALSE;
#  if (COM_RXTOUTINFOUSEDOFRXACCESSINFO == STD_ON)
      if(Com_IsRxTOutInfoUsedOfRxAccessInfo(idxRxAccessInfo))   /* COV_COM_FEATURE_RX_TOUT_INFO_USED_XX */
      {
        hasToutOccurred = Com_LMgt_HasTimeoutOccurred(Com_GetRxTOutInfoIdxOfRxAccessInfo(idxRxAccessInfo));
      }
#  endif
      filterState =
        Com_Signal_SInt32_EvaluateFilter((Com_FilterInfo_SInt32IterType) Com_GetFilterInfoIdxOfRxAccessInfo(idxRxAccessInfo), tmpNewValue,
                                         Com_GetRxSigBufferSInt32(Com_GetBufferIdxOfRxAccessInfo(idxRxAccessInfo)), hasToutOccurred);
      if(filterState == FALSE)
      {
        processState = FILTERED;
      }
    }
  }
  if(processState == VALID)
# endif
  {
    Com_BufferIdxOfRxAccessInfoType idxBuffer = Com_GetBufferIdxOfRxAccessInfo(idxRxAccessInfo);
    Com_SetRxSigBufferSInt32(idxBuffer, tmpNewValue);   /* SBSW_COM_CSL03 */
  }

# if (COM_MINPROCGWBUFFERUSEDOFRXACCESSINFO == STD_ON)
  if(Com_IsMinProcGwBufferUsedOfRxAccessInfo(idxRxAccessInfo))
  {
    Com_SetMinProcGwBufferSInt32(Com_GetMinProcGwBufferIdxOfRxAccessInfo(idxRxAccessInfo), tmpNewValue);        /* SBSW_COM_CSL03 */
  }
# endif

  COM_DUMMY_STATEMENT_CONST(PduInfoPtr);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(idxRxAccessInfo); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return processState;
}
#endif

#if ((COM_EXISTS_UINT64_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_RXSIGINFO == STD_ON))
/**********************************************************************************************************************
  Com_RxSignalProcessing_UINT64
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(Com_RxSigProcessState, COM_CODE) Com_RxSignalProcessing_UINT64(P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr, Com_RxAccessInfoIterType idxRxAccessInfo)
{
  Com_RxSigProcessState processState = VALID;   /* PRQA S 2981 */ /* MD_MSR_RetVal */
  /* Check for buffer is not required as there is always a buffer configured. Removed check Com_IsBufferUsedOfRxAccessInfo */
  uint64 tmpNewValue = Com_Signal_ReadSignal_UInt64(idxRxAccessInfo, &(PduInfoPtr->SduDataPtr[Com_GetBytePositionOfRxAccessInfo(idxRxAccessInfo)]));    /* SBSW_COM_FCTCALL_WITH_P2CONST */

# if (COM_INVVALUEUSEDOFRXACCESSINFO == STD_ON)
  processState = Com_RxInv_Sig_UInt64_EvaluateInvalidValue(idxRxAccessInfo, tmpNewValue);
  if(processState == VALID)     /* COV_COM_INVALIDATION_TX */
# endif
# if ((COM_FILTERINFOUSEDOFRXACCESSINFO == STD_ON) && (COM_FILTERINFO_UINT64 == STD_ON))
  {
    if(Com_IsFilterInfoUsedOfRxAccessInfo(idxRxAccessInfo))     /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
    {
      boolean filterState;
      boolean hasToutOccurred = FALSE;
#  if (COM_RXTOUTINFOUSEDOFRXACCESSINFO == STD_ON)
      if(Com_IsRxTOutInfoUsedOfRxAccessInfo(idxRxAccessInfo))   /* COV_COM_FEATURE_RX_TOUT_INFO_USED_XX */
      {
        hasToutOccurred = Com_LMgt_HasTimeoutOccurred(Com_GetRxTOutInfoIdxOfRxAccessInfo(idxRxAccessInfo));
      }
#  endif
      filterState =
        Com_Signal_UInt64_EvaluateFilter((Com_FilterInfo_UInt64IterType) Com_GetFilterInfoIdxOfRxAccessInfo(idxRxAccessInfo), tmpNewValue,
                                         Com_GetRxSigBufferUInt64(Com_GetBufferIdxOfRxAccessInfo(idxRxAccessInfo)), hasToutOccurred);
      if(filterState == FALSE)
      {
        processState = FILTERED;
      }
    }
  }
  if(processState == VALID)
# endif
  {
    Com_BufferIdxOfRxAccessInfoType idxBuffer = Com_GetBufferIdxOfRxAccessInfo(idxRxAccessInfo);
    Com_SetRxSigBufferUInt64(idxBuffer, tmpNewValue);   /* SBSW_COM_CSL03 */
  }

# if (COM_MINPROCGWBUFFERUSEDOFRXACCESSINFO == STD_ON)
  if(Com_IsMinProcGwBufferUsedOfRxAccessInfo(idxRxAccessInfo))
  {
    Com_SetMinProcGwBufferUInt64(Com_GetMinProcGwBufferIdxOfRxAccessInfo(idxRxAccessInfo), tmpNewValue);        /* SBSW_COM_CSL03 */
  }
# endif

  COM_DUMMY_STATEMENT_CONST(PduInfoPtr);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(idxRxAccessInfo); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return processState;
}
#endif

#if ((COM_EXISTS_SINT64_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_RXSIGINFO == STD_ON))
/**********************************************************************************************************************
  Com_RxSignalProcessing_SINT64
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(Com_RxSigProcessState, COM_CODE) Com_RxSignalProcessing_SINT64(P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr, Com_RxAccessInfoIterType idxRxAccessInfo)
{
  Com_RxSigProcessState processState = VALID;   /* PRQA S 2981 */ /* MD_MSR_RetVal */
  /* Check for buffer is not required as there is always a buffer configured. Removed check Com_IsBufferUsedOfRxAccessInfo */
  sint64 tmpNewValue = Com_Signal_ReadSignal_SInt64(idxRxAccessInfo, &(PduInfoPtr->SduDataPtr[Com_GetBytePositionOfRxAccessInfo(idxRxAccessInfo)]));    /* SBSW_COM_FCTCALL_WITH_P2CONST */

# if (COM_INVVALUEUSEDOFRXACCESSINFO == STD_ON)
  processState = Com_RxInv_Sig_SInt64_EvaluateInvalidValue(idxRxAccessInfo, tmpNewValue);
  if(processState == VALID)     /* COV_COM_INVALIDATION_TX */
# endif
# if ((COM_FILTERINFOUSEDOFRXACCESSINFO == STD_ON) && (COM_FILTERINFO_SINT64 == STD_ON))
  {
    if(Com_IsFilterInfoUsedOfRxAccessInfo(idxRxAccessInfo))     /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
    {
      boolean filterState;
      boolean hasToutOccurred = FALSE;
#  if (COM_RXTOUTINFOUSEDOFRXACCESSINFO == STD_ON)
      if(Com_IsRxTOutInfoUsedOfRxAccessInfo(idxRxAccessInfo))   /* COV_COM_FEATURE_RX_TOUT_INFO_USED_XX */
      {
        hasToutOccurred = Com_LMgt_HasTimeoutOccurred(Com_GetRxTOutInfoIdxOfRxAccessInfo(idxRxAccessInfo));
      }
#  endif
      filterState =
        Com_Signal_SInt64_EvaluateFilter((Com_FilterInfo_SInt64IterType) Com_GetFilterInfoIdxOfRxAccessInfo(idxRxAccessInfo), tmpNewValue,
                                         Com_GetRxSigBufferSInt64(Com_GetBufferIdxOfRxAccessInfo(idxRxAccessInfo)), hasToutOccurred);
      if(filterState == FALSE)
      {
        processState = FILTERED;
      }
    }
  }
  if(processState == VALID)
# endif
  {
    Com_BufferIdxOfRxAccessInfoType idxBuffer = Com_GetBufferIdxOfRxAccessInfo(idxRxAccessInfo);
    Com_SetRxSigBufferSInt64(idxBuffer, tmpNewValue);   /* SBSW_COM_CSL03 */
  }

# if (COM_MINPROCGWBUFFERUSEDOFRXACCESSINFO == STD_ON)
  if(Com_IsMinProcGwBufferUsedOfRxAccessInfo(idxRxAccessInfo))
  {
    Com_SetMinProcGwBufferSInt64(Com_GetMinProcGwBufferIdxOfRxAccessInfo(idxRxAccessInfo), tmpNewValue);        /* SBSW_COM_CSL03 */
  }
# endif

  COM_DUMMY_STATEMENT_CONST(PduInfoPtr);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(idxRxAccessInfo); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return processState;
}
#endif

#if ((COM_EXISTS_FLOAT32_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_RXSIGINFO == STD_ON))
/**********************************************************************************************************************
  Com_RxSignalProcessing_FLOAT32
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(Com_RxSigProcessState, COM_CODE) Com_RxSignalProcessing_FLOAT32(P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr, Com_RxAccessInfoIterType idxRxAccessInfo)
{
  Com_RxSigProcessState processState = VALID;   /* PRQA S 2981 */ /* MD_MSR_RetVal */
  /* Check for buffer is not required as there is always a buffer configured. Removed check Com_IsBufferUsedOfRxAccessInfo */
  float32 tmpNewValue = Com_Signal_ReadSignal_Float32(idxRxAccessInfo, &(PduInfoPtr->SduDataPtr[Com_GetBytePositionOfRxAccessInfo(idxRxAccessInfo)]));  /* SBSW_COM_FCTCALL_WITH_P2CONST */

# if (COM_INVVALUEUSEDOFRXACCESSINFO == STD_ON)
  processState = Com_RxInv_Sig_Float32_EvaluateInvalidValue(idxRxAccessInfo, tmpNewValue);
  if(processState == VALID)     /* COV_COM_INVALIDATION_TX */
# endif
# if ((COM_FILTERINFOUSEDOFRXACCESSINFO == STD_ON) && (COM_FILTERINFO_FLOAT32 == STD_ON))
  {
    if(Com_IsFilterInfoUsedOfRxAccessInfo(idxRxAccessInfo))     /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
    {
      boolean filterState;
      boolean hasToutOccurred = FALSE;
#  if (COM_RXTOUTINFOUSEDOFRXACCESSINFO == STD_ON)
      if(Com_IsRxTOutInfoUsedOfRxAccessInfo(idxRxAccessInfo))   /* COV_COM_FEATURE_RX_TOUT_INFO_USED_XX */
      {
        hasToutOccurred = Com_LMgt_HasTimeoutOccurred(Com_GetRxTOutInfoIdxOfRxAccessInfo(idxRxAccessInfo));
      }
#  endif
      filterState =
        Com_Signal_Float32_EvaluateFilter((Com_FilterInfo_Float32IterType) Com_GetFilterInfoIdxOfRxAccessInfo(idxRxAccessInfo), tmpNewValue,
                                          Com_GetRxSigBufferFloat32(Com_GetBufferIdxOfRxAccessInfo(idxRxAccessInfo)), hasToutOccurred);
      if(filterState == FALSE)  /* PRQA S 2991, 2995 */ /* MD_Com_2991, MD_Com_2995 */ /* COV_COM_FLOAT_TYPE_FILTER */
      {
        processState = FILTERED;
      }
    }
  }
  if(processState == VALID)
# endif
  {
    Com_BufferIdxOfRxAccessInfoType idxBuffer = Com_GetBufferIdxOfRxAccessInfo(idxRxAccessInfo);
    Com_SetRxSigBufferFloat32(idxBuffer, tmpNewValue);  /* SBSW_COM_CSL03 */
  }

# if (COM_MINPROCGWBUFFERUSEDOFRXACCESSINFO == STD_ON)
  if(Com_IsMinProcGwBufferUsedOfRxAccessInfo(idxRxAccessInfo))
  {
    Com_SetMinProcGwBufferFloat32(Com_GetMinProcGwBufferIdxOfRxAccessInfo(idxRxAccessInfo), tmpNewValue);       /* SBSW_COM_CSL03 */
  }
# endif

  COM_DUMMY_STATEMENT_CONST(PduInfoPtr);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(idxRxAccessInfo); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return processState;
}
#endif

#if ((COM_EXISTS_FLOAT64_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_RXSIGINFO == STD_ON))
/**********************************************************************************************************************
  Com_RxSignalProcessing_FLOAT64
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(Com_RxSigProcessState, COM_CODE) Com_RxSignalProcessing_FLOAT64(P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr, Com_RxAccessInfoIterType idxRxAccessInfo)
{
  Com_RxSigProcessState processState = VALID;   /* PRQA S 2981 */ /* MD_MSR_RetVal */
  /* Check for buffer is not required as there is always a buffer configured. Removed check Com_IsBufferUsedOfRxAccessInfo */
  float64 tmpNewValue = Com_Signal_ReadSignal_Float64(idxRxAccessInfo, &(PduInfoPtr->SduDataPtr[Com_GetBytePositionOfRxAccessInfo(idxRxAccessInfo)]));  /* SBSW_COM_FCTCALL_WITH_P2CONST */

# if (COM_INVVALUEUSEDOFRXACCESSINFO == STD_ON)
  processState = Com_RxInv_Sig_Float64_EvaluateInvalidValue(idxRxAccessInfo, tmpNewValue);
  if(processState == VALID)     /* COV_COM_INVALIDATION_TX */
# endif
# if ((COM_FILTERINFOUSEDOFRXACCESSINFO == STD_ON) && (COM_FILTERINFO_FLOAT64 == STD_ON))
  {
    if(Com_IsFilterInfoUsedOfRxAccessInfo(idxRxAccessInfo))     /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
    {
      boolean filterState;
      boolean hasToutOccurred = FALSE;
#  if (COM_RXTOUTINFOUSEDOFRXACCESSINFO == STD_ON)
      if(Com_IsRxTOutInfoUsedOfRxAccessInfo(idxRxAccessInfo))   /* COV_COM_FEATURE_RX_TOUT_INFO_USED_XX */
      {
        hasToutOccurred = Com_LMgt_HasTimeoutOccurred(Com_GetRxTOutInfoIdxOfRxAccessInfo(idxRxAccessInfo));
      }
#  endif
      filterState =
        Com_Signal_Float64_EvaluateFilter((Com_FilterInfo_Float64IterType) Com_GetFilterInfoIdxOfRxAccessInfo(idxRxAccessInfo), tmpNewValue,
                                          Com_GetRxSigBufferFloat64(Com_GetBufferIdxOfRxAccessInfo(idxRxAccessInfo)), hasToutOccurred);
      if(filterState == FALSE)  /* PRQA S 2991, 2995 */ /* MD_Com_2991, MD_Com_2995 */ /* COV_COM_FLOAT_TYPE_FILTER */
      {
        processState = FILTERED;
      }
    }
  }
  if(processState == VALID)
# endif
  {
    Com_BufferIdxOfRxAccessInfoType idxBuffer = Com_GetBufferIdxOfRxAccessInfo(idxRxAccessInfo);
    Com_SetRxSigBufferFloat64(idxBuffer, tmpNewValue);  /* SBSW_COM_CSL03 */
  }

# if (COM_MINPROCGWBUFFERUSEDOFRXACCESSINFO == STD_ON)
  if(Com_IsMinProcGwBufferUsedOfRxAccessInfo(idxRxAccessInfo))
  {
    Com_SetMinProcGwBufferFloat64(Com_GetMinProcGwBufferIdxOfRxAccessInfo(idxRxAccessInfo), tmpNewValue);       /* SBSW_COM_CSL03 */
  }
# endif

  COM_DUMMY_STATEMENT_CONST(PduInfoPtr);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(idxRxAccessInfo); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return processState;
}
#endif

#if((COM_EXISTS_UINT8_N_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_RXSIGINFO == STD_ON))
/**********************************************************************************************************************
  Com_RxSignalProcessing_UINT8_N
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(Com_RxSigProcessState, COM_CODE) Com_RxSignalProcessing_UINT8_N(P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr, Com_RxAccessInfoIterType idxRxAccessInfo)      /* COV_COM_APPLTYPEOFRXACCESSINFO */
{
  Com_RxSigProcessState processState = VALID;   /* PRQA S 2981 */ /* MD_MSR_RetVal */

  P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) newValuePtr = &(PduInfoPtr->SduDataPtr[Com_GetStartByteInPduPositionOfRxAccessInfo(idxRxAccessInfo)]);
# if (COM_CONSTVALUEARRAYBASEDINVVALUEUSEDOFRXACCESSINFO == STD_ON)
  processState = Com_RxInv_Sig_UInt8_N_EvaluateInvalidValue(idxRxAccessInfo, newValuePtr);      /* SBSW_COM_FCTCALL_WITH_P2CONST */
  if(processState == VALID)
# endif
# if ((COM_FILTERINFOUSEDOFRXACCESSINFO == STD_ON) && (COM_FILTERINFO_UINT8_N == STD_ON))
  {
    if(Com_IsFilterInfoUsedOfRxAccessInfo(idxRxAccessInfo))     /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
    {
      boolean filterState;
      boolean hasToutOccurred = FALSE;
#  if (COM_RXTOUTINFOUSEDOFRXACCESSINFO == STD_ON)
      if(Com_IsRxTOutInfoUsedOfRxAccessInfo(idxRxAccessInfo))   /* COV_COM_FEATURE_RX_TOUT_INFO_USED_XX */
      {
        hasToutOccurred = Com_LMgt_HasTimeoutOccurred(Com_GetRxTOutInfoIdxOfRxAccessInfo(idxRxAccessInfo));
      }
#  endif
      filterState = Com_Signal_UInt8_N_EvaluateFilter((Com_FilterInfo_UInt8_NIterType) Com_GetFilterInfoIdxOfRxAccessInfo(idxRxAccessInfo), newValuePtr, Com_GetAddrRxSigBufferArrayBased(Com_GetRxSigBufferArrayBasedBufferStartIdxOfRxAccessInfo(idxRxAccessInfo)), (PduLengthType) Com_GetRxSigBufferArrayBasedBufferLengthOfRxAccessInfo(idxRxAccessInfo), hasToutOccurred);        /* SBSW_COM_FCTCALL_WITH_P2CONST */
      if(filterState == FALSE)
      {
        processState = FILTERED;
      }
    }
  }
  if(processState == VALID)
# endif
  {
    Com_RxSigBufferArrayBasedIterType idxBuffer = Com_GetRxSigBufferArrayBasedBufferStartIdxOfRxAccessInfo(idxRxAccessInfo);
    VStdMemCpyRamToRam(Com_GetAddrRxSigBufferArrayBased(idxBuffer), newValuePtr, Com_GetRxSigBufferArrayBasedBufferLengthOfRxAccessInfo(idxRxAccessInfo));      /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_COM_MEM_CPY_2RAM */
  }

# if (COM_MINPROCGWBUFFERARRAYBASEDBUFFERUSEDOFRXACCESSINFO == STD_ON)
  if(Com_IsMinProcGwBufferArrayBasedBufferUsedOfRxAccessInfo(idxRxAccessInfo))
  {
    Com_RxSigBufferArrayBasedIterType idxBuffer = Com_GetMinProcGwBufferArrayBasedBufferStartIdxOfRxAccessInfo(idxRxAccessInfo);
    VStdMemCpyRamToRam(Com_GetAddrMinProcGwBufferArrayBased(idxBuffer), newValuePtr, Com_GetMinProcGwBufferArrayBasedBufferLengthOfRxAccessInfo(idxRxAccessInfo));      /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_COM_MEM_CPY_2RAM */
  }
# endif

  COM_DUMMY_STATEMENT_CONST(PduInfoPtr);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(idxRxAccessInfo); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return processState;
}       /* PRQA S 6030 */ /* MD_MSR_STCYC */
#endif

#if ((COM_RXTPINFOUSEDOFRXPDUINFO == STD_ON) && (COM_EXISTS_UINT8_DYN_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_RXSIGINFO == STD_ON))
/**********************************************************************************************************************
  Com_RxSignalProcessing_UINT8_DYN
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(Com_RxSigProcessState, COM_CODE) Com_RxSignalProcessing_UINT8_DYN(P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr, Com_RxAccessInfoIterType idxRxAccessInfo)
{
  Com_RxSigProcessState processState = VALID;   /* PRQA S 2981 */ /* MD_MSR_RetVal */

  P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) newValuePtr;
  newValuePtr = &(PduInfoPtr->SduDataPtr[Com_GetStartByteInPduPositionOfRxAccessInfo(idxRxAccessInfo)]);

# if (COM_CONSTVALUEARRAYBASEDINVVALUEUSEDOFRXACCESSINFO == STD_ON)
  processState = Com_RxInv_Sig_UInt8_Dyn_EvaluateInvalidValue(idxRxAccessInfo, newValuePtr, PduInfoPtr->SduLength);     /* SBSW_COM_FCTCALL_STACKPTR */
  if(processState == VALID)
# endif
  {
    Com_RxSigBufferArrayBasedIterType idxBuffer = Com_GetRxSigBufferArrayBasedBufferStartIdxOfRxAccessInfo(idxRxAccessInfo);
    Com_RxTpInfoIdxOfRxPduInfoType rxTpPduInfoIdx = Com_GetRxTpInfoIdxOfRxPduInfo(Com_GetRxPduInfoIdxOfRxAccessInfo(idxRxAccessInfo));
    Com_SetRxDynSignalLength(rxTpPduInfoIdx, Com_GetRxDynamicLength(PduInfoPtr->SduLength, idxRxAccessInfo));   /* SBSW_COM_CSL02 */

    VStdMemCpyRamToRam(Com_GetAddrRxSigBufferArrayBased(idxBuffer), newValuePtr, Com_GetRxDynSignalLength(rxTpPduInfoIdx));     /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_COM_CSL01_STACKPTR */
  }

  COM_DUMMY_STATEMENT_CONST(PduInfoPtr);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(idxRxAccessInfo); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return processState;
}
#endif


/**********************************************************************************************************************
  GLOBAL FUNCTIONS
**********************************************************************************************************************/

#if (COM_RXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxProcessing_InitRxIpdu
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_RxProcessing_InitRxIpdu(PduIdType ComRxPduId)
{
  /* Initialize signal buffer */
# if (COM_RXACCESSINFOINDENDIDXOFRXPDUINFO == STD_ON)
  {
    /* #10 Iterate over all ComSignals and ComGroupSignals and initialize the corresponding buffers and shadow buffers */
    Com_RxAccessInfoIndEndIdxOfRxPduInfoType com_RxAccessInfoIndIdx = Com_GetRxAccessInfoIndStartIdxOfRxPduInfo(ComRxPduId);
    for(; com_RxAccessInfoIndIdx < Com_GetRxAccessInfoIndEndIdxOfRxPduInfo(ComRxPduId); com_RxAccessInfoIndIdx++)
    {
      Com_RxAccessInfoIterType com_RxAccessInfoIdx = Com_GetRxAccessInfoInd(com_RxAccessInfoIndIdx);
#  if ((COM_INITVALUEUSEDOFRXACCESSINFO == STD_ON) && (COM_BUFFERUSEDOFRXACCESSINFO == STD_ON))
      if(Com_IsInitValueUsedOfRxAccessInfo(com_RxAccessInfoIdx) && Com_IsBufferUsedOfRxAccessInfo(com_RxAccessInfoIdx)) /* COV_COM_RXPROCESSING_TX */
      {
        Com_Signal_SetRxSigBufferValue(com_RxAccessInfoIdx, Com_GetBufferIdxOfRxAccessInfo(com_RxAccessInfoIdx), Com_GetInitValueIdxOfRxAccessInfo(com_RxAccessInfoIdx));
      }
#  endif
#  if ((COM_INITVALUEUSEDOFRXACCESSINFO == STD_ON) && (COM_MINPROCGWBUFFERUSEDOFRXACCESSINFO == STD_ON))
      if(Com_IsInitValueUsedOfRxAccessInfo(com_RxAccessInfoIdx) && Com_IsMinProcGwBufferUsedOfRxAccessInfo(com_RxAccessInfoIdx))        /* COV_COM_ONLY_INIT_VALUE */
      {
        Com_Signal_SetMinProcGwBufferValue(com_RxAccessInfoIdx, Com_GetMinProcGwBufferIdxOfRxAccessInfo(com_RxAccessInfoIdx), Com_GetInitValueIdxOfRxAccessInfo(com_RxAccessInfoIdx));
      }
#  endif
#  if ((COM_CONSTVALUEARRAYBASEDINITVALUEUSEDOFRXACCESSINFO == STD_ON) && (COM_RXSIGBUFFERARRAYBASEDBUFFERUSEDOFRXACCESSINFO == STD_ON))
      if(Com_IsConstValueArrayBasedInitValueUsedOfRxAccessInfo(com_RxAccessInfoIdx) && Com_IsRxSigBufferArrayBasedBufferUsedOfRxAccessInfo(com_RxAccessInfoIdx))        /* COV_COM_RXPROCESSING_TX */
      {
        Com_Signal_SetRxSigBufferArrayBasedValue(com_RxAccessInfoIdx, Com_GetRxSigBufferArrayBasedBufferStartIdxOfRxAccessInfo(com_RxAccessInfoIdx),
                                                 Com_GetConstValueArrayBasedInitValueStartIdxOfRxAccessInfo(com_RxAccessInfoIdx),
                                                 (PduLengthType) Com_GetConstValueArrayBasedInitValueLengthOfRxAccessInfo(com_RxAccessInfoIdx));
      }
#  endif
#  if ((COM_CONSTVALUEARRAYBASEDINITVALUEUSEDOFRXACCESSINFO == STD_ON) && (COM_MINPROCGWBUFFERARRAYBASEDBUFFERUSEDOFRXACCESSINFO == STD_ON))
      if(Com_IsConstValueArrayBasedInitValueUsedOfRxAccessInfo(com_RxAccessInfoIdx) && Com_IsMinProcGwBufferArrayBasedBufferUsedOfRxAccessInfo(com_RxAccessInfoIdx)) /* COV_COM_MIN_SIGGW_UINT8_ONLY */
      {
        VStdMemCpyRomToRam(Com_GetAddrMinProcGwBufferArrayBased(Com_GetMinProcGwBufferArrayBasedBufferStartIdxOfRxAccessInfo(com_RxAccessInfoIdx)),     /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_COM_CSL01 */
                           Com_GetAddrConstValueArrayBased(Com_GetConstValueArrayBasedInitValueStartIdxOfRxAccessInfo(com_RxAccessInfoIdx)),
                           (PduLengthType) Com_GetMinProcGwBufferArrayBasedBufferLengthOfRxAccessInfo(com_RxAccessInfoIdx));
      }
#  endif
#  if (COM_ISGROUPSIGNALOFRXACCESSINFO == STD_ON)
      if(Com_IsIsGroupSignalOfRxAccessInfo(com_RxAccessInfoIdx))        /* COV_COM_RXPROCESSING */
      {
#   if ((COM_INITVALUEUSEDOFRXACCESSINFO == STD_ON) && (COM_SHDBUFFERUSEDOFRXACCESSINFO == STD_ON))
        if(Com_IsInitValueUsedOfRxAccessInfo(com_RxAccessInfoIdx) && Com_IsShdBufferUsedOfRxAccessInfo(com_RxAccessInfoIdx))    /* COV_COM_RXPROCESSING_SHADOWSIGNAL */
        {
          Com_Signal_SetRxSigBufferValue(com_RxAccessInfoIdx, Com_GetShdBufferIdxOfRxAccessInfo(com_RxAccessInfoIdx), Com_GetInitValueIdxOfRxAccessInfo(com_RxAccessInfoIdx));
        }
#   endif
#   if ((COM_CONSTVALUEARRAYBASEDINITVALUEUSEDOFRXACCESSINFO == STD_ON) && (COM_RXSIGBUFFERARRAYBASEDSHDBUFFERUSEDOFRXACCESSINFO == STD_ON))
        if(Com_IsConstValueArrayBasedInitValueUsedOfRxAccessInfo(com_RxAccessInfoIdx) && Com_IsRxSigBufferArrayBasedShdBufferUsedOfRxAccessInfo(com_RxAccessInfoIdx))   /* COV_COM_RXPROCESSING_SHADOWSIGNAL */
        {
          Com_Signal_SetRxSigBufferArrayBasedValue(com_RxAccessInfoIdx, Com_GetRxSigBufferArrayBasedShdBufferStartIdxOfRxAccessInfo(com_RxAccessInfoIdx),
                                                   Com_GetConstValueArrayBasedInitValueStartIdxOfRxAccessInfo(com_RxAccessInfoIdx),
                                                   (PduLengthType) Com_GetConstValueArrayBasedInitValueLengthOfRxAccessInfo(com_RxAccessInfoIdx));
        }
#   endif
      }
#  endif
    }
  }
# endif
# if(COM_ARRAYACCESSUSEDOFRXSIGGRPINFO == STD_ON)
  {
    /* #20 Iterate over all ComSignalGroups and if ArrayAccess is used initialize the corresponding shadow buffer */
    Com_RxSigGrpInfoIndIterType com_SignalGroupIndId = Com_GetRxSigGrpInfoIndStartIdxOfRxPduInfo(ComRxPduId);   /* PRQA S 2842 */ /* MD_Com_2842 */
    for(; com_SignalGroupIndId < Com_GetRxSigGrpInfoIndEndIdxOfRxPduInfo(ComRxPduId); com_SignalGroupIndId++)   /* PRQA S 2842 */ /* MD_Com_2842 */
    {
      Com_RxSigGrpInfoIterType com_SignalGroupId = Com_GetRxSigGrpInfoInd(com_SignalGroupIndId);
      if(Com_IsArrayAccessUsedOfRxSigGrpInfo(com_SignalGroupId))        /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
      {
        Com_RxSigArrayAccessSigGrpBufferIterType idxShdBufferIdx = Com_GetRxSigArrayAccessSigGrpBufferStartIdxOfRxSigGrpInfo(com_SignalGroupId);
        Com_ConstValueSigGrpArrayAccessIterType intialValueStartIdx = Com_GetConstValueSigGrpArrayAccessStartIdxOfRxSigGrpInfo(com_SignalGroupId);

        VStdMemCpyRamToRam(Com_GetAddrRxSigArrayAccessSigGrpBuffer(idxShdBufferIdx), Com_GetAddrConstValueSigGrpArrayAccess(intialValueStartIdx), Com_GetRxSigArrayAccessSigGrpBufferLengthOfRxSigGrpInfo(com_SignalGroupId));  /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_COM_CSL01 */
      }
    }
  }
# endif
# if (COM_EXISTS_DEFERRED_SIGNALPROCESSINGOFRXPDUINFO == STD_ON)
  /* #30 If the Rx ComIPdu is handled deferred, reset the "Handle Deferred" flag */
  if(Com_IsHandleRxPduDeferredUsedOfRxPduInfo(ComRxPduId))      /* PRQA S 2842 */ /* MD_Com_2842 */ /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    Com_SetHandleRxPduDeferred(Com_GetHandleRxPduDeferredIdxOfRxPduInfo(ComRxPduId), 0);        /* PRQA S 2842 */ /* MD_Com_2842 */ /* SBSW_COM_CSL03 */

#  if (COM_GWEVENTCACHE == STD_ON)
    /* #40 If a gateway description exists, reset the gateway description handle */
    if(Com_IsGwTxPduDescriptionInfoUsedOfRxPduInfo(ComRxPduId)) /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
    {
      Com_SetHandleRxDeferredGwDescription(Com_GetHandleRxDeferredGwDescriptionIdxOfRxPduInfo(ComRxPduId), 0);  /* SBSW_COM_CSL03 */
    }
#  endif
  }
# endif
}       /* PRQA S 6010, 6030 */ /* MD_MSR_STPTH, MD_MSR_STCYC */
#endif

#if (COM_RXCBKFUNCPTR == STD_ON)
/**********************************************************************************************************************
  Com_ProcessRxFctPtrCache
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_ProcessRxFctPtrCache(P2VAR(FctPtrCacheStrct, AUTOMATIC, COM_APPL_DATA) fctPtrCacheStrctPtr)
{
  while(fctPtrCacheStrctPtr->cacheIndex > 0u)
  {
    Com_RxCbkFuncPtrIterType cbkFctPtrIdx;

    fctPtrCacheStrctPtr->cacheIndex = fctPtrCacheStrctPtr->cacheIndex - 1u;     /* SBSW_COM_FCTPTR_CACHE_PTR_2 */
    cbkFctPtrIdx = (Com_RxCbkFuncPtrIterType) fctPtrCacheStrctPtr->ptrToCache[fctPtrCacheStrctPtr->cacheIndex]; /* PRQA S 2842 */ /* MD_Com_ProcessRxFctPtrCache */

    Com_GetRxCbkFuncPtr(cbkFctPtrIdx) ();       /* SBSW_COM_FCT_PTR_CALL_CSL03 */
  }
}
#endif

#if (COM_RXSIGINFOENDIDXOFRXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxProcessing_RxPduSigEvent
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
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_RxProcessing_RxPduSigEvent(PduIdType comRxPduInfoIdx, P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr, P2VAR(FctPtrCacheStrct, AUTOMATIC, COM_APPL_DATA) fctPtrCacheStrctPtr)        /* PRQA S 3673 */ /* MD_MSR_Rule8.13 */
{
  /* #10 Iterate over all Rx ComSignals of the passed Rx ComIPdu and do Rx ComSignal based processing */
  Com_RxSigInfoIterType idxRxSigInfo = Com_GetRxSigInfoStartIdxOfRxPduInfo(comRxPduInfoIdx);
  for(; idxRxSigInfo < Com_GetRxSigInfoEndIdxOfRxPduInfo(comRxPduInfoIdx); idxRxSigInfo++)
  {
    /* #20 If the Rx ComSignal is completely contained in the passed Sdu data length */
    if(PduInfoPtr->SduLength >= Com_GetValidDlcOfRxSigInfo(idxRxSigInfo))
    {
# if (COM_UBMASKUSEDOFRXSIGINFO == STD_ON)
      /* #30 Check if the ComSignal was updated */
      boolean process = Com_RxProcessing_CheckSigUB(idxRxSigInfo, PduInfoPtr);  /* SBSW_COM_FCTCALL_WITH_P2CONST */
      if(process == TRUE)
# endif
      {
# if (COM_RXTOUTINFOUSEDOFRXSIGINFO == STD_ON)
        /* #40 Set configured timeout event */
        Com_RxDlMon_SigEvent(idxRxSigInfo);
# endif

# if (COM_GWINFOUSEDOFRXSIGINFO == STD_ON)
        /* #50 Set configured routing event */
        Com_SignalGw_SigEvent(idxRxSigInfo);
# endif
        /* #60 Do Rx Signal Processing */
        {
          Com_RxSigProcessState rxSigProcessingState = Com_RxSignalProcessing(PduInfoPtr, Com_GetRxAccessInfoIdxOfRxSigInfo(idxRxSigInfo));     /* SBSW_COM_VALID_PTR_ENSURED_BY_CALLING_FUNC */
          switch (rxSigProcessingState)
          {
            case VALID:
            {
# if ((COM_RXTOUTINFOUSEDOFRXSIGINFO == STD_ON) && (COM_UBMASKUSEDOFRXSIGINFO == STD_ON))
              /* #70 If the ComSignal has a timeout and an UpdateBit, remove the timeout occurred flag */
              if(Com_IsRxTOutInfoUsedOfRxSigInfo(idxRxSigInfo) && Com_IsUbMaskUsedOfRxSigInfo(idxRxSigInfo))    /* COV_COM_TIMEOUT_AND_UB */
              {
                Com_LMgt_RemoveOccurredFlag(Com_GetRxTOutInfoIdxOfRxSigInfo(idxRxSigInfo));     /* SBSW_COM_CSL02_CSL03 */
              }
# endif
# if (COM_RXCBKFUNCPTRACKIDXOFRXSIGINFO == STD_ON)
              /* #80 If the passed Rx ComSignal uses a notification function, cache or call that function */
              if(Com_IsRxCbkFuncPtrAckUsedOfRxSigInfo(idxRxSigInfo))    /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
              {
                Com_CacheOrCallRxCbkFctPtr((Com_RxCbkFuncPtrIterType) Com_GetRxCbkFuncPtrAckIdxOfRxSigInfo(idxRxSigInfo), comRxPduInfoIdx, fctPtrCacheStrctPtr);        /* SBSW_COM_FCTPTR_CACHE_PTR */
              }
# endif
            }
              break;
# if ((COM_INVVALUEUSEDOFRXACCESSINFO == STD_ON) || (COM_CONSTVALUEARRAYBASEDINVVALUEUSEDOFRXACCESSINFO == STD_ON))
              /* #90 If the signal value is the invalid value, perform the invalid action */
            case INVALID:      /* COV_COM_SIGNALINVALIDATION */
            {
              Com_RxInv_Sig_PerformInvalidAction(idxRxSigInfo, fctPtrCacheStrctPtr);    /* SBSW_COM_FCTPTR_CACHE_PTR */
            }
              break;
# endif
            default:   /* COV_COM_MISRA */
              /* do nothing */
              break;
          }
        }
      } /* Update-bit check */
    }   /* DLC check */
  }     /* Signal loop */
  COM_DUMMY_STATEMENT(fctPtrCacheStrctPtr);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}       /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if (COM_RXSIGGRPINFOINDENDIDXOFRXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxProcessing_RxPduSigGrpEvent
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_RxProcessing_RxPduSigGrpEvent(PduIdType comRxPduInfoIdx, P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr,
                                                       P2VAR(FctPtrCacheStrct, AUTOMATIC, COM_APPL_DATA) fctPtrCacheStrctPtr)
{
  /* #10 Iterate over all ComSignalGroups related to the passed ComIPdu and do ComSignalGroup based processing */
  Com_RxSigGrpInfoIterType idxRxSigGrpInfoInd = Com_GetRxSigGrpInfoIndStartIdxOfRxPduInfo(comRxPduInfoIdx);
  for(; idxRxSigGrpInfoInd < Com_GetRxSigGrpInfoIndEndIdxOfRxPduInfo(comRxPduInfoIdx); idxRxSigGrpInfoInd++)
  {
    Com_RxSigGrpInfoIterType idxRxSigGrpInfo = Com_GetRxSigGrpInfoInd(idxRxSigGrpInfoInd);

    /* #20 If ComSignalGroup is completely contained in received data length */
    /* \trace SPEC-2736854 */
    if(PduInfoPtr->SduLength >= Com_GetValidDlcOfRxSigGrpInfo(idxRxSigGrpInfo))
    {
# if (COM_UBMASKUSEDOFRXSIGGRPINFO == STD_ON)
      /* #30 Check if the ComSignal was updated */
      boolean process = Com_RxProcessing_CheckSigGrpUB(PduInfoPtr, idxRxSigGrpInfo);    /* SBSW_COM_FCTCALL_WITH_P2CONST */
      if(process == TRUE)
# endif
      {
# if (COM_RXTOUTINFOUSEDOFRXSIGGRPINFO == STD_ON)
        /* #40 Set configured timeout event */
        Com_RxDlMon_SigGrpEvent(idxRxSigGrpInfo);
# endif

# if (COM_GWINFOUSEDOFRXSIGGRPINFO == STD_ON)
        /* #50 Set configured routing event */
        Com_SignalGw_SigGrpEvent(idxRxSigGrpInfo);
# endif
        /* #60 Do Rx ComSignalGroup processing */
        Com_RxProcessing_ProcessSigGrpEvent(comRxPduInfoIdx, PduInfoPtr, idxRxSigGrpInfo, fctPtrCacheStrctPtr); /* SBSW_COM_FCTCALL_WITH_P2CONST */
      } /* Update-bit check */
    }   /* DLC check */
  }     /* Signal Group loop */
}       /* Signal group processing */
#endif

#if (COM_EXISTS_DEFERRED_SIGNALPROCESSINGOFRXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxDeferredPduProcessing
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_RxDeferredPduProcessing(void)
{
# if (COM_RXDEFERREDEVENTCACHE == STD_ON)
  boolean fallbackRequired = TRUE;      /* Initially assume deferred event cache is full. */
# endif
  /* Deferred Signal Processing.  */
  FctPtrCacheStrct deferredFctPtrCacheStrct;

# if (COM_RXDEFERREDFCTPTRCACHE == STD_ON)
  deferredFctPtrCacheStrct.ptrToCache = Com_GetAddrRxDeferredFctPtrCache(0);
  deferredFctPtrCacheStrct.cacheSize = Com_GetSizeOfRxDeferredFctPtrCache();
# else
  deferredFctPtrCacheStrct.ptrToCache = NULL_PTR;
  deferredFctPtrCacheStrct.cacheSize = 0;
# endif
  deferredFctPtrCacheStrct.cacheIndex = 0;

# if (COM_RXDEFERREDEVENTCACHE == STD_ON)
  Com_RxProcessing_EnterExclusiveArea_Deferred();

  /* #10 If all received deferred processed events fitted into the deferred event cache */
  if(Com_GetRxNextEventCacheEnty() != COM_NO_HANDLERXPDUDEFERREDIDXOFRXPDUINFO)
  {
    Com_SizeOfRxPduInfoType idxRxPduInfo;
    fallbackRequired = FALSE;   /* Cache is not full. */

    /* #20 Iterate over all stored deferred events, and process them */
    while(Com_GetRxNextEventCacheEnty() > 0u)
    {
      Com_DecRxNextEventCacheEnty();    /* SBSW_COM_CSL_VAR_ACCESS */
      idxRxPduInfo = Com_GetRxDeferredEventCache(Com_GetRxNextEventCacheEnty());
      if(Com_IsRxPduGrpActive(idxRxPduInfo))
      {
        if(0u < Com_GetHandleRxPduDeferred(Com_GetHandleRxPduDeferredIdxOfRxPduInfo(idxRxPduInfo)))
        {
          Com_RxProcessDeferredPDU((PduIdType) idxRxPduInfo, &deferredFctPtrCacheStrct);        /* SBSW_COM_FCTPTR_CACHE_PTR */
        }
      }
      Com_RxProcessing_ThresholdCheck_Deferred(&deferredFctPtrCacheStrct);      /* SBSW_COM_FCTPTR_CACHE_PTR_1 */

      /* #25 If meanwhile new Pdus have been received and cache is full, stop processing cache and set fallback strategy flag */
      if(Com_GetRxNextEventCacheEnty() == COM_NO_HANDLERXPDUDEFERREDIDXOFRXPDUINFO)     /* COV_COM_DEFERRED_EVENTCACHE_FALLBACK */
      {
        fallbackRequired = TRUE;
        break;
      }
    }
  }

  /* #26 If fallback strategy flag is set or cache is not configured, iterate over all Rx Pdus */
  if(fallbackRequired == TRUE)  /* COV_COM_DEFERRED_EVENTCACHE_FALLBACK */
  {
    Com_RxDeferredPduProcessing_IterateOverAllRxPdus(&deferredFctPtrCacheStrct);        /* SBSW_COM_FCTPTR_CACHE_PTR_1 */
  }
  Com_RxProcessing_ExitExclusiveArea_Deferred();
# else
  {
    Com_RxProcessing_EnterExclusiveArea_Deferred();
    Com_RxDeferredPduProcessing_IterateOverAllRxPdus(&deferredFctPtrCacheStrct);        /* SBSW_COM_FCTPTR_CACHE_PTR_1 */
    Com_RxProcessing_ExitExclusiveArea_Deferred();
  }
# endif

# if (COM_RXDEFERREDFCTPTRCACHE == STD_ON)
  /* #40 Call all cached notification and invalid notification functions. */
  Com_ProcessRxFctPtrCache(&deferredFctPtrCacheStrct);  /* SBSW_COM_FCTPTR_CACHE_PTR_1 */
# endif
}
#endif

#if(COM_RXSIGBUFFERARRAYBASEDBUFFERUSEDOFRXACCESSINFO == STD_ON)
/**********************************************************************************************************************
  Com_Signal_SetRxSigBufferArrayBasedValue
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_Signal_SetRxSigBufferArrayBasedValue(Com_RxAccessInfoIterType idxRxAccessInfo, Com_RxSigBufferArrayBasedIterType idxDestValue,
                                                              Com_ConstValueArrayBasedIterType idxSrcValue, PduLengthType length)
{
  /* #10 Copy the constant value at the position of the passed source index to the passed destination index, the source and destination buffer depends on the ApplType of the passed signal */
  switch (Com_GetApplTypeOfRxAccessInfo(idxRxAccessInfo))
  {
# if ((COM_RXTPINFOUSEDOFRXPDUINFO == STD_ON) && (COM_EXISTS_UINT8_DYN_APPLTYPEOFRXACCESSINFO == STD_ON))
    case COM_UINT8_DYN_APPLTYPEOFRXACCESSINFO:
    {
      Com_RxTpInfoIdxOfRxPduInfoType rxTpPduInfoIdx = Com_GetRxTpInfoIdxOfRxPduInfo(Com_GetRxPduInfoIdxOfRxAccessInfo(idxRxAccessInfo));
      Com_SetRxDynSignalLength(rxTpPduInfoIdx, length); /* SBSW_COM_CSL02 */
#  if (COM_RXDYNSIGNALTMPLENGTHFORSIGNALGROUPS == STD_ON)
      Com_SetRxDynSignalTmpLengthForSignalGroups(rxTpPduInfoIdx, length);       /* SBSW_COM_CSL02 */
#  endif

      VStdMemCpyRomToRam(Com_GetAddrRxSigBufferArrayBased(idxDestValue), Com_GetAddrConstValueArrayBased(idxSrcValue), length); /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_COM_WRITEACCESS_LENGTH */
      break;
    }
# endif
# if ((COM_EXISTS_UINT8_N_APPLTYPEOFRXACCESSINFO == STD_ON))
    case COM_UINT8_N_APPLTYPEOFRXACCESSINFO:
    {
      VStdMemCpyRomToRam(Com_GetAddrRxSigBufferArrayBased(idxDestValue), Com_GetAddrConstValueArrayBased(idxSrcValue), length); /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_COM_WRITEACCESS_LENGTH */
      break;
    }
# endif
    default:   /* COV_COM_MISRA */
      break;
  }
  COM_DUMMY_STATEMENT(idxDestValue);    /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}
#endif


#if ((COM_RXTPINFOUSEDOFRXPDUINFO == STD_ON) && (COM_EXISTS_UINT8_DYN_APPLTYPEOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
  Com_GetRxDynamicLength
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(PduLengthType, COM_CODE) Com_GetRxDynamicLength(PduLengthType sduLength, Com_RxAccessInfoIterType rxAccessInfoIdx)
{
  return sduLength - Com_GetStartByteInPduPositionOfRxAccessInfo(rxAccessInfoIdx);
}
#endif

#define COM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */   /* MD_MSR_MemMap */

/***********************************************************************************************************************
 *  MISRA JUSTIFICATIONS
 **********************************************************************************************************************/
/* *INDENT-OFF* */
/* Justifications for module-specific MISRA deviations:
  MD_Com_2822: Misra Dir 4.1
     Reason:     In case of Deferred Processing, the SduDataPtr can never be a NULL_PTR because of the Control Flow. If the RxProcessDeferredPDU function is called a DeferredPduBuffer is always present and a PDU is always a TP_PDU or a NORMAL_PDU and thus the SduDataPtr is initialized. If it is Immediate Processing the SduDataPtr is always initialized with a valid value, or the SduDataPtr is checked.
     Risk:       No risk.
     Prevention: No prevention necessary

  MD_Com_ProcessRxFctPtrCache: Misra Rule 18.1, Misra Rule 21.18, Misra Dir 4.1
     Reason:     All calls of the Com_ProcessRxFctPtrCacheFunction are directly or indirectly wraped by preprocessor switches checking if a FctPtrCache is available and the setting of the fctPtrCacheStrctPtr is wrapped by the same preprocessor switches, so the fctPtrCacheStrctPtr is always valid, when accessed.
     Risk:       No risk.
     Prevention: No prevention necessary
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
 *  END OF FILE: Com_RxProcessing.c
 *********************************************************************************************************************/
