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
 *         File:  PduR_IFQ.c
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


#define PDUR_IFQ_SOURCE
/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "PduR.h"
#include "PduR_IFQ.h"
#include "SchM_PduR.h"
#if (PDUR_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/
#define PduR_Core_MemCpyRamToRam(d, s, l)    VStdMemCpyRamToRam((d), (s), (l))

#if !defined (PDUR_LOCAL_INLINE)
# define PDUR_LOCAL_INLINE LOCAL_INLINE
#endif

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/
#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h" /* PRQA S 5087 */   /* MD_MSR_MemMap */

#if (PDUR_INTERFACEFIFOQUEUEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_IFQ_GetActualLengthOfInterfaceFifoQueueElementRamSafe
 *********************************************************************************************************************/
/*! \brief       Get the actual length of interface Fifo queue without worrying the length exceeds the maximum pdu length
 *  \details     -
 *  \param[in]   interfaceFifoQueueElementRamIdx    id of the interface FIFO queue element
 *  \param[in]   interfaceFifoQueueRomIdx           id of the interface FIFO queue
 *  \param[in]   memIdx                             memory section index
 *  \return      the read index
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(PduR_ActualLengthOfInterfaceFifoQueueElementRamType, PDUR_CODE) PduR_IFQ_GetActualLengthOfInterfaceFifoQueueElementRamSafe(PduR_InterfaceFifoQueueElementRamIterType interfaceFifoQueueElementRamIdx,
                                                                                                                                             PduR_InterfaceFifoQueueRomIterType interfaceFifoQueueRomIdx,
                                                                                                                                             PduR_MemIdxType memIdx);
#endif

#if (PDUR_INTERFACEFIFOQUEUEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_IFQ_GetInterfaceFifoQueueElementRamReadIdxSafe
 *********************************************************************************************************************/
/*! \brief       Gets the current read idx for the FIFO queue.
 *  \details     -
 *  \param[in]   interfaceFifoQueueRomIdx    id of the interface FIFO queue
 *  \param[in]   memIdx                      memory section index
 *  \return      the read index
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(PduR_InterfaceFifoQueueElementRamReadIdxOfInterfaceFifoQueueRamType, PDUR_CODE) PduR_IFQ_GetInterfaceFifoQueueElementRamReadIdxSafe(PduR_InterfaceFifoQueueRomIterType interfaceFifoQueueRomIdx, PduR_MemIdxType memIdx);
#endif

#if (PDUR_INTERFACEFIFOQUEUEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_IFQ_GetInterfaceFifoQueueElementRamWriteIdxSafe
 *********************************************************************************************************************/
/*! \brief       Set the current write idx for the FIFO queue.
 *  \details     -
 *  \param[in]   interfaceFifoQueueRomIdx    id of the interface FIFO queue
 *  \param[in]   memIdx                      memory section index
 *  \return      the write index
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(PduR_InterfaceFifoQueueElementRamWriteIdxOfInterfaceFifoQueueRamType, PDUR_CODE) PduR_IFQ_GetInterfaceFifoQueueElementRamWriteIdxSafe(PduR_InterfaceFifoQueueRomIterType interfaceFifoQueueRomIdx, PduR_MemIdxType memIdx);
#endif

#if(PDUR_INTERFACEFIFOQUEUEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_IFQ_IsQueueFull
 *********************************************************************************************************************/
/*! \brief      Returns if the queue is full.
 *  \details    -
 *  \param[in]  interfaceFifoQueueRomIdx  id of the interface fifo queue
 *  \param[in]  memIdx                    memory section index
 *  \return     true                      queue is full
 *              false                     queue is not full
 *  \pre        -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_IFQ_IsQueueFull(PduR_InterfaceFifoQueueRomIterType interfaceFifoQueueRomIdx, PduR_MemIdxType memIdx);
#endif

#if(PDUR_INTERFACEFIFOQUEUEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_IFQ_IsQueueEmpty
 *********************************************************************************************************************/
/*! \brief      Returns if the queue is empty.
 *  \details    -
 *  \param[in]  interfaceFifoQueueRomIdx  id of the interface fifo queue
 *  \param[in]  memIdx                    memory section index
 *  \return     true                      queue is empty
 *              false                     queue is not empty
 *  \pre        -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_IFQ_IsQueueEmpty(PduR_InterfaceFifoQueueRomIterType interfaceFifoQueueRomIdx, PduR_MemIdxType memIdx);
#endif

#if(PDUR_INTERFACEFIFOQUEUEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_IFQ_IncrementReadIdx
 *********************************************************************************************************************/
/*! \brief      Increments the read Idx with wrap around.
 *  \details    -
 *  \param[in]  interfaceFifoQueueRomIdx  id of the interface fifo queue
 *  \param[in]  memIdx                    memory section index
 *  \pre        -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_IFQ_IncrementReadIdx(PduR_InterfaceFifoQueueRomIterType interfaceFifoQueueRomIdx, PduR_MemIdxType memIdx);
#endif

#if(PDUR_INTERFACEFIFOQUEUEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_IFQ_IncrementWriteIdx
 *********************************************************************************************************************/
/*! \brief      Increments the write Idx with wrap around.
 *  \details    -
 *  \param[in]  interfaceFifoQueueRomIdx  id of the interface fifo queue
 *  \param[in]  memIdx                    memory section index
 *  \pre        -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_IFQ_IncrementWriteIdx(PduR_InterfaceFifoQueueRomIterType interfaceFifoQueueRomIdx, PduR_MemIdxType memIdx);
#endif

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
#if (PDUR_INTERFACEFIFOQUEUEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_IFQ_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_IFQ_Init(PduR_MemIdxType memIdx)
{
  PduR_InterfaceFifoQueueRomIterType interfaceFifoQueueRomIdx;
  for(interfaceFifoQueueRomIdx = 0u; interfaceFifoQueueRomIdx < PduR_GetSizeOfInterfaceFifoQueueRom(memIdx); interfaceFifoQueueRomIdx++)
  {
    PduR_InterfaceFifoQueueElementRamStartIdxOfInterfaceFifoQueueRomType startIdxOfQueue = PduR_GetInterfaceFifoQueueElementRamStartIdxOfInterfaceFifoQueueRom(interfaceFifoQueueRomIdx, memIdx);

    PduR_SetInterfaceFifoQueueElementRamReadIdxOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx, startIdxOfQueue, memIdx);  /* SBSW_PDUR_CSL02 */
    PduR_SetInterfaceFifoQueueElementRamWriteIdxOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx, startIdxOfQueue, memIdx); /* SBSW_PDUR_CSL02 */
    PduR_SetFifoFullOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx, FALSE, memIdx);                                        /* SBSW_PDUR_CSL02 */
  }
}
#endif

/**********************************************************************************************************************
 * PduR_IFQ_PutFifo
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
#if (PDUR_INTERFACEFIFOQUEUEROM == STD_ON)
FUNC(Std_ReturnType, PDUR_CODE) PduR_IFQ_PutFifo(PduR_RmGDestRomIterType rmGDestRomIdx, PduR_RmDestRomIterType rmDestRomIdx, PduLengthType pduLength, SduDataPtrType sduDataPtr)  /* PRQA S 3673 */ /* MD_MSR_Rule8.13 */
{
  Std_ReturnType retVal = E_NOT_OK;     /* PRQA S 2981 */ /* MD_MSR_RetVal */
  PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfRmGDestRom(rmGDestRomIdx);
  PduR_InterfaceFifoQueueRomIdxOfRmBufferedIfPropertiesRomType interfaceFifoQueueRomIdx = PduR_GetInterfaceFifoQueueRomIdxOfRmBufferedIfPropertiesRom(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx), memIdx);

  if(PduR_IFQ_IsQueueFull(interfaceFifoQueueRomIdx, memIdx))
  {
    retVal = E_NOT_OK;
  }
  else
  {
    PduR_InterfaceFifoQueueElementRamStartIdxOfInterfaceFifoQueueRomType startIdxOfQueue = PduR_GetInterfaceFifoQueueElementRamStartIdxOfInterfaceFifoQueueRom(interfaceFifoQueueRomIdx, memIdx);
    PduR_InterfaceFifoQueueElementRamWriteIdxOfInterfaceFifoQueueRamType interfaceFifoQueueElementRamWriteIdx = PduR_IFQ_GetInterfaceFifoQueueElementRamWriteIdxSafe(interfaceFifoQueueRomIdx, memIdx);
    PduLengthType maxPduLengthOfInterfaceFifoQueueRom = PduR_GetMaxPduLengthOfInterfaceFifoQueueRom(interfaceFifoQueueRomIdx, memIdx);

    PduR_InterfaceFifoQueueArrayRamEndIdxOfInterfaceFifoQueueRomType writeOffset = ((PduR_InterfaceFifoQueueArrayRamEndIdxOfInterfaceFifoQueueRomType) interfaceFifoQueueElementRamWriteIdx - startIdxOfQueue) * maxPduLengthOfInterfaceFifoQueueRom;
    PduR_InterfaceFifoQueueArrayRamEndIdxOfInterfaceFifoQueueRomType interfaceFifoQueueArrayRamWriteIdx = PduR_GetInterfaceFifoQueueArrayRamStartIdxOfInterfaceFifoQueueRom(interfaceFifoQueueRomIdx, memIdx) + writeOffset;

    if((interfaceFifoQueueArrayRamWriteIdx + maxPduLengthOfInterfaceFifoQueueRom) <= PduR_GetInterfaceFifoQueueArrayRamEndIdxOfInterfaceFifoQueueRom(interfaceFifoQueueRomIdx, memIdx))  /* COV_PDUR_FATAL_ERROR */
    {
      PduR_SetActualLengthOfInterfaceFifoQueueElementRam(interfaceFifoQueueElementRamWriteIdx, pduLength, memIdx); /* SBSW_PDUR_CSL03 */
      VStdLib_MemCpy_s(PduR_GetAddrInterfaceFifoQueueArrayRam(interfaceFifoQueueArrayRamWriteIdx, memIdx), maxPduLengthOfInterfaceFifoQueueRom, sduDataPtr, pduLength);   /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_PDUR_MEM_CPY_FIFOMGR */
      PduR_IFQ_IncrementWriteIdx(interfaceFifoQueueRomIdx, memIdx);
      retVal = E_OK;
    }
# if (PDUR_DEV_ERROR_REPORT == STD_ON)
    else
    {
      retVal = E_NOT_OK;
      PduR_Det_ReportError(PDUR_IFQ_PUT, PDUR_E_FATAL);
    }
# endif
  }

  PDUR_DUMMY_STATEMENT(rmDestRomIdx);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  return retVal;
}
#endif

/**********************************************************************************************************************
 * PduR_IFQ_IsQueueFull
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
#if (PDUR_INTERFACEFIFOQUEUEROM == STD_ON)
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_IFQ_IsQueueFull(PduR_InterfaceFifoQueueRomIterType interfaceFifoQueueRomIdx, PduR_MemIdxType memIdx)
{
  return PduR_IsFifoFullOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx, memIdx);
}
#endif

/**********************************************************************************************************************
 * PduR_IFQ_IsQueueEmpty
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
#if (PDUR_INTERFACEFIFOQUEUEROM == STD_ON)
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_IFQ_IsQueueEmpty(PduR_InterfaceFifoQueueRomIterType interfaceFifoQueueRomIdx, PduR_MemIdxType memIdx)
{
  return (PduR_IFQ_GetInterfaceFifoQueueElementRamReadIdxSafe(interfaceFifoQueueRomIdx, memIdx) == PduR_IFQ_GetInterfaceFifoQueueElementRamWriteIdxSafe(interfaceFifoQueueRomIdx, memIdx))
          && !PduR_IFQ_IsQueueFull(interfaceFifoQueueRomIdx, memIdx);
}
#endif

/**********************************************************************************************************************
 * PduR_IFQ_IncrementReadIdx
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
#if (PDUR_INTERFACEFIFOQUEUEROM == STD_ON)
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_IFQ_IncrementReadIdx(PduR_InterfaceFifoQueueRomIterType interfaceFifoQueueRomIdx, PduR_MemIdxType memIdx)
{
  PduR_InterfaceFifoQueueElementRamReadIdxOfInterfaceFifoQueueRamType localReadIdx = PduR_IFQ_GetInterfaceFifoQueueElementRamReadIdxSafe(interfaceFifoQueueRomIdx, memIdx);
  localReadIdx++;

  if(localReadIdx >= PduR_GetInterfaceFifoQueueElementRamEndIdxOfInterfaceFifoQueueRom(interfaceFifoQueueRomIdx, memIdx))
  {
    PduR_SetInterfaceFifoQueueElementRamReadIdxOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx, PduR_GetInterfaceFifoQueueElementRamStartIdxOfInterfaceFifoQueueRom(interfaceFifoQueueRomIdx, memIdx), memIdx); /* SBSW_PDUR_CSL03 */
  }
  else
  {
    PduR_SetInterfaceFifoQueueElementRamReadIdxOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx, localReadIdx, memIdx); /* SBSW_PDUR_CSL03 */
  }

  PduR_SetFifoFullOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx, FALSE, memIdx); /* SBSW_PDUR_CSL03 */
}
#endif

/**********************************************************************************************************************
 * PduR_IFQ_IncrementWriteIdx
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
#if (PDUR_INTERFACEFIFOQUEUEROM == STD_ON)
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_IFQ_IncrementWriteIdx(PduR_InterfaceFifoQueueRomIterType interfaceFifoQueueRomIdx, PduR_MemIdxType memIdx)
{
  PduR_InterfaceFifoQueueElementRamWriteIdxOfInterfaceFifoQueueRamType localWriteIdx = PduR_IFQ_GetInterfaceFifoQueueElementRamWriteIdxSafe(interfaceFifoQueueRomIdx, memIdx);
  localWriteIdx++;

  if(localWriteIdx >= PduR_GetInterfaceFifoQueueElementRamEndIdxOfInterfaceFifoQueueRom(interfaceFifoQueueRomIdx, memIdx))
  {
    PduR_SetInterfaceFifoQueueElementRamWriteIdxOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx, PduR_GetInterfaceFifoQueueElementRamStartIdxOfInterfaceFifoQueueRom(interfaceFifoQueueRomIdx, memIdx), memIdx); /* SBSW_PDUR_CSL03 */
  }
  else
  {
    PduR_SetInterfaceFifoQueueElementRamWriteIdxOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx, localWriteIdx, memIdx); /* SBSW_PDUR_CSL03 */
  }

  if(PduR_IFQ_GetInterfaceFifoQueueElementRamReadIdxSafe(interfaceFifoQueueRomIdx, memIdx) == PduR_IFQ_GetInterfaceFifoQueueElementRamWriteIdxSafe(interfaceFifoQueueRomIdx, memIdx))
  {
    PduR_SetFifoFullOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx, TRUE, memIdx); /* SBSW_PDUR_CSL03 */
  }
}
#endif

#if (PDUR_INTERFACEFIFOQUEUEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_IFQ_GetNextElement
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
FUNC(Std_ReturnType, PDUR_CODE) PduR_IFQ_GetNextElement(PduR_RmGDestRomIterType rmGDestRomIdx, P2VAR(PduR_RmDestRomIterType, AUTOMATIC, PDUR_APPL_DATA) rmDestRomIdx, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info)
{
  Std_ReturnType retVal = E_NOT_OK;     /* PRQA S 2981 */ /* MD_MSR_RetVal */
  PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfRmGDestRom(rmGDestRomIdx);
  PduR_InterfaceFifoQueueRomIdxOfRmBufferedIfPropertiesRomType interfaceFifoQueueRomIdx = PduR_GetInterfaceFifoQueueRomIdxOfRmBufferedIfPropertiesRom(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx), memIdx);

  if(PduR_IFQ_IsQueueEmpty(interfaceFifoQueueRomIdx, memIdx))
  {
    retVal = E_NOT_OK;
  }
  else
  {
    PduR_InterfaceFifoQueueElementRamStartIdxOfInterfaceFifoQueueRomType startIdxOfQueue = PduR_GetInterfaceFifoQueueElementRamStartIdxOfInterfaceFifoQueueRom(interfaceFifoQueueRomIdx, memIdx);
    PduR_InterfaceFifoQueueElementRamReadIdxOfInterfaceFifoQueueRamType interfaceFifoQueueElementRamReadIdx = PduR_IFQ_GetInterfaceFifoQueueElementRamReadIdxSafe(interfaceFifoQueueRomIdx, memIdx);

    PduR_InterfaceFifoQueueArrayRamEndIdxOfInterfaceFifoQueueRomType offset = ((PduR_InterfaceFifoQueueArrayRamEndIdxOfInterfaceFifoQueueRomType) interfaceFifoQueueElementRamReadIdx - startIdxOfQueue) * PduR_GetMaxPduLengthOfInterfaceFifoQueueRom(interfaceFifoQueueRomIdx, memIdx);

    info->SduDataPtr = PduR_GetAddrInterfaceFifoQueueArrayRam(PduR_GetInterfaceFifoQueueArrayRamStartIdxOfInterfaceFifoQueueRom(interfaceFifoQueueRomIdx, memIdx)  + offset, memIdx); /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
    info->SduLength  = PduR_IFQ_GetActualLengthOfInterfaceFifoQueueElementRamSafe(interfaceFifoQueueElementRamReadIdx, interfaceFifoQueueRomIdx, memIdx); /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
    *rmDestRomIdx = PduR_GetRmDestRomIdxOfInterfaceFifoQueueRom(interfaceFifoQueueRomIdx, memIdx); /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
    retVal = E_OK;
  }

  return retVal;
}
#endif

#if (PDUR_INTERFACEFIFOQUEUEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_IFQ_GetActualLengthOfInterfaceFifoQueueElementRamSafe
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(PduR_ActualLengthOfInterfaceFifoQueueElementRamType, PDUR_CODE) PduR_IFQ_GetActualLengthOfInterfaceFifoQueueElementRamSafe(PduR_InterfaceFifoQueueElementRamIterType interfaceFifoQueueElementRamIdx,
                                                                                                                                             PduR_InterfaceFifoQueueRomIterType interfaceFifoQueueRomIdx,
                                                                                                                                             PduR_MemIdxType memIdx)
{
  PduR_ActualLengthOfInterfaceFifoQueueElementRamType actualLengthOfInterfaceFifoQueueElement = PduR_GetActualLengthOfInterfaceFifoQueueElementRam(interfaceFifoQueueElementRamIdx, memIdx);

# if (PDUR_EXTENDED_ERROR_CHECKS == STD_ON)
  PduLengthType maxPduLength = PduR_GetMaxPduLengthOfInterfaceFifoQueueRom(interfaceFifoQueueRomIdx, memIdx);

  if(actualLengthOfInterfaceFifoQueueElement > maxPduLength) /* COV_PDUR_EXTENDED_ERROR_CHECKS */
  {
    actualLengthOfInterfaceFifoQueueElement = maxPduLength;
    PduR_ReportRuntimeDetError(PDUR_FCT_GETACTUALLENGTHOFIFQ, PDUR_E_IDXOUTOFBOUNDS);
  }
# endif

  PDUR_DUMMY_STATEMENT(interfaceFifoQueueRomIdx);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  return actualLengthOfInterfaceFifoQueueElement;
}
#endif

#if (PDUR_INTERFACEFIFOQUEUEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_IFQ_RemoveElement
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_IFQ_RemoveElement(PduR_RmGDestRomIterType rmGDestRomIdx)
{
  PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfRmGDestRom(rmGDestRomIdx);
  PduR_InterfaceFifoQueueRomIdxOfRmBufferedIfPropertiesRomType interfaceFifoQueueRomIdx = PduR_GetInterfaceFifoQueueRomIdxOfRmBufferedIfPropertiesRom(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx), memIdx);

  if(!PduR_IFQ_IsQueueEmpty(interfaceFifoQueueRomIdx, memIdx)) /* COV_PDUR_FATAL_ERROR */
  {
    PduR_IFQ_IncrementReadIdx(interfaceFifoQueueRomIdx, memIdx);
  }
}
#endif

#if (PDUR_INTERFACEFIFOQUEUEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_IFQ_FlushQueue
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_IFQ_FlushQueue(PduR_RmGDestRomIterType rmGDestRomIdx)
{
  PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfRmGDestRom(rmGDestRomIdx);
  PduR_InterfaceFifoQueueRomIdxOfRmBufferedIfPropertiesRomType interfaceFifoQueueRomIdx = PduR_GetInterfaceFifoQueueRomIdxOfRmBufferedIfPropertiesRom(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx), memIdx);
  PduR_InterfaceFifoQueueElementRamStartIdxOfInterfaceFifoQueueRomType startIdxOfQueue = PduR_GetInterfaceFifoQueueElementRamStartIdxOfInterfaceFifoQueueRom(interfaceFifoQueueRomIdx, memIdx);

  PduR_SetInterfaceFifoQueueElementRamReadIdxOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx, startIdxOfQueue, memIdx);  /* SBSW_PDUR_CSL03 */
  PduR_SetInterfaceFifoQueueElementRamWriteIdxOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx, startIdxOfQueue, memIdx); /* SBSW_PDUR_CSL03 */
  PduR_SetFifoFullOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx, FALSE, memIdx);                                        /* SBSW_PDUR_CSL03 */
}
#endif

#if (PDUR_INTERFACEFIFOQUEUEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_IFQ_GetFillLevel
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(uint16, PDUR_CODE) PduR_IFQ_GetFillLevel(PduR_RmGDestRomIterType rmGDestRomIdx) /* COV_PDUR_NO_DEFERRED_IF_ROUTING */
{
  uint32 fillLevel;
  PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfRmGDestRom(rmGDestRomIdx);
  PduR_InterfaceFifoQueueRomIdxOfRmBufferedIfPropertiesRomType interfaceFifoQueueRomIdx = PduR_GetInterfaceFifoQueueRomIdxOfRmBufferedIfPropertiesRom(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx), memIdx);

  PduR_InterfaceFifoQueueElementRamReadIdxOfInterfaceFifoQueueRamType  readIdx         = PduR_IFQ_GetInterfaceFifoQueueElementRamReadIdxSafe(interfaceFifoQueueRomIdx, memIdx);
  PduR_InterfaceFifoQueueElementRamWriteIdxOfInterfaceFifoQueueRamType writeIdx        = PduR_IFQ_GetInterfaceFifoQueueElementRamWriteIdxSafe(interfaceFifoQueueRomIdx, memIdx);
  PduR_InterfaceFifoQueueElementRamStartIdxOfInterfaceFifoQueueRomType startIdxOfQueue = PduR_GetInterfaceFifoQueueElementRamStartIdxOfInterfaceFifoQueueRom(interfaceFifoQueueRomIdx, memIdx);
  PduR_InterfaceFifoQueueElementRamEndIdxOfInterfaceFifoQueueRomType   endIdxOfQueue   = PduR_GetInterfaceFifoQueueElementRamEndIdxOfInterfaceFifoQueueRom(interfaceFifoQueueRomIdx, memIdx);

  if(readIdx < writeIdx)
  {
    fillLevel = (uint32) writeIdx - readIdx;
  }
  else if(writeIdx < readIdx)
  {
    fillLevel = ((uint32) endIdxOfQueue - readIdx) + ((uint32) writeIdx - startIdxOfQueue);
  }
  else /* (readIdx == writeIdx) */
  {
    if(PduR_IFQ_IsQueueFull(interfaceFifoQueueRomIdx, memIdx)) /* COV_PDUR_NON_EMPTY_QUEUE */
    {
      fillLevel = (uint32) endIdxOfQueue - startIdxOfQueue;
    }
    else
    {
      fillLevel = 0u;
    }
  }

  return (uint16) fillLevel;
}
#endif

#if (PDUR_INTERFACEFIFOQUEUEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_IFQ_GetInterfaceFifoQueueElementRamReadIdxSafe
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(PduR_InterfaceFifoQueueElementRamReadIdxOfInterfaceFifoQueueRamType, PDUR_CODE) PduR_IFQ_GetInterfaceFifoQueueElementRamReadIdxSafe(PduR_InterfaceFifoQueueRomIterType interfaceFifoQueueRomIdx, PduR_MemIdxType memIdx)
{
  PduR_InterfaceFifoQueueElementRamReadIdxOfInterfaceFifoQueueRamType readIdx = PduR_GetInterfaceFifoQueueElementRamReadIdxOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx, memIdx);

# if (PDUR_EXTENDED_ERROR_CHECKS == STD_ON)
  PduR_InterfaceFifoQueueElementRamStartIdxOfInterfaceFifoQueueRomType startIdxOfQueue = PduR_GetInterfaceFifoQueueElementRamStartIdxOfInterfaceFifoQueueRom(interfaceFifoQueueRomIdx, memIdx);
  PduR_InterfaceFifoQueueElementRamEndIdxOfInterfaceFifoQueueRomType   endIdxOfQueue   = PduR_GetInterfaceFifoQueueElementRamEndIdxOfInterfaceFifoQueueRom(interfaceFifoQueueRomIdx, memIdx);

  if(readIdx >= endIdxOfQueue) /* COV_PDUR_EXTENDED_ERROR_CHECKS */
  {
    readIdx = endIdxOfQueue - 1u;
    PduR_ReportRuntimeDetError(PDUR_FCT_GETIFQREADIDX, PDUR_E_IDXOUTOFBOUNDS);
  }
  if(readIdx < startIdxOfQueue) /* COV_PDUR_EXTENDED_ERROR_CHECKS */
  {
    readIdx = startIdxOfQueue;
    PduR_ReportRuntimeDetError(PDUR_FCT_GETIFQREADIDX, PDUR_E_IDXOUTOFBOUNDS);
  }
# endif

  return readIdx;
}
#endif


#if (PDUR_INTERFACEFIFOQUEUEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_IFQ_GetInterfaceFifoQueueElementRamWriteIdxSafe
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(PduR_InterfaceFifoQueueElementRamWriteIdxOfInterfaceFifoQueueRamType, PDUR_CODE) PduR_IFQ_GetInterfaceFifoQueueElementRamWriteIdxSafe(PduR_InterfaceFifoQueueRomIterType interfaceFifoQueueRomIdx, PduR_MemIdxType memIdx)
{
  PduR_InterfaceFifoQueueElementRamWriteIdxOfInterfaceFifoQueueRamType writeIdx = PduR_GetInterfaceFifoQueueElementRamWriteIdxOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx, memIdx);

# if (PDUR_EXTENDED_ERROR_CHECKS == STD_ON)
  PduR_InterfaceFifoQueueElementRamStartIdxOfInterfaceFifoQueueRomType startIdxOfQueue = PduR_GetInterfaceFifoQueueElementRamStartIdxOfInterfaceFifoQueueRom(interfaceFifoQueueRomIdx, memIdx);
  PduR_InterfaceFifoQueueElementRamEndIdxOfInterfaceFifoQueueRomType   endIdxOfQueue   = PduR_GetInterfaceFifoQueueElementRamEndIdxOfInterfaceFifoQueueRom(interfaceFifoQueueRomIdx, memIdx);

  if(writeIdx >= endIdxOfQueue) /* COV_PDUR_EXTENDED_ERROR_CHECKS */
  {
    writeIdx = endIdxOfQueue - 1u;
    PduR_ReportRuntimeDetError(PDUR_FCT_GETIFQWRITEIDX, PDUR_E_IDXOUTOFBOUNDS);
  }
  if(writeIdx < startIdxOfQueue) /* COV_PDUR_EXTENDED_ERROR_CHECKS */
  {
    writeIdx = startIdxOfQueue;
    PduR_ReportRuntimeDetError(PDUR_FCT_GETIFQWRITEIDX, PDUR_E_IDXOUTOFBOUNDS);
  }
# endif

  return writeIdx;
}
#endif

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h" /* PRQA S 5087 */   /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  END OF FILE: PduR_IFQ.c
 *********************************************************************************************************************/
