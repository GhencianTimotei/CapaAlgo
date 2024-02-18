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
 *         File:  PduR_Fm.c
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


#define PDUR_FM_SOURCE
/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "PduR.h"
#include "PduR_Bm.h"
#include "PduR_Fm.h"
#include "PduR_RmTp.h"
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

#if (PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_GetBmTxBufferRomIdxOfFmFifoElementRamSafe
 *********************************************************************************************************************/
 /*! \brief       Get the bmTxBuffer index of the fmFifoElement
 *   \details     -
 *   \param[in]   fmFifoElementRamIdx   Index of the FIFO element in Ram.
 *   \param[in]   memIdx                memory section index
 *   \return                            bmTxBuffer index
 *   \pre         -
 *   \context     TASK|ISR1|ISR2
 *   \reentrant   TRUE
 *   \synchronous TRUE
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(PduR_BmTxBufferRomIdxOfFmFifoElementRamType, PDUR_CODE) PduR_Fm_GetBmTxBufferRomIdxOfFmFifoElementRamSafe(PduR_FmFifoElementRamIterType fmFifoElementRamIdx, PduR_MemIdxType memIdx);
#endif

#if (PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_GetBmTxBufferInstanceRomIdxOfFmFifoInstanceRamSafe
 *********************************************************************************************************************/
/*! \brief       Gets the bmTxBufferInstance index of the fmFifoInstance with error checking
 *  \details     -
 *  \param[in]   fmFifoInstanceRomIdx   fmFifoInstance index
 *  \param[in]   memIdx                 memory section index
 *  \return                             bmTxBufferInstance index
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(PduR_BmTxBufferInstanceRomIterType, PDUR_CODE) PduR_Fm_GetBmTxBufferInstanceRomIdxOfFmFifoInstanceRamSafe(PduR_FmFifoInstanceRomIterType fmFifoInstanceRomIdx, PduR_MemIdxType memIdx);
#endif

#if (PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_GetFillLevelSafe
 *********************************************************************************************************************/
/*! \brief       Gets the fill level with error detection.
 *  \details     -
 *  \param[in]   fmFifoRamIdx    Id of the Fifo
 *  \param[in]   memIdx          memory section index
 *  \return                      the fill level
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(uint16, PDUR_CODE) PduR_Fm_GetFillLevelSafe(PduR_FmFifoRamIterType fmFifoRamIdx, PduR_MemIdxType memIdx);
#endif

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
#if(PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Fm_Init(PduR_MemIdxType memIdx)
{
  {
    PduR_FmFifoRamIterType fmFifoRamIdx;
    for(fmFifoRamIdx = 0u; fmFifoRamIdx < PduR_GetSizeOfFmFifoRam(memIdx); fmFifoRamIdx++)
    {
# if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
      PduR_SetTpTxSmStateOfFmFifoRam(fmFifoRamIdx, PDUR_RM_TX_IDLE_TPTXSMSTATEOFFMFIFORAM, memIdx);     /* SBSW_PDUR_CSL01 */
# endif
      PduR_SetPendingConfirmationsOfFmFifoRam(fmFifoRamIdx, 0u, memIdx);        /* SBSW_PDUR_CSL01 */
      PduR_SetFmFifoElementRamReadIdxOfFmFifoRam(fmFifoRamIdx, PduR_GetFmFifoElementRamStartIdxOfFmFifoRom(fmFifoRamIdx, memIdx), memIdx);      /* SBSW_PDUR_CSL01 */
      PduR_SetFmFifoElementRamWriteIdxOfFmFifoRam(fmFifoRamIdx, PduR_GetFmFifoElementRamStartIdxOfFmFifoRom(fmFifoRamIdx, memIdx), memIdx);     /* SBSW_PDUR_CSL01 */
      PduR_SetFillLevelOfFmFifoRam(fmFifoRamIdx, 0u, memIdx);   /* SBSW_PDUR_CSL01 */
    }
  }
  {
    PduR_FmFifoElementRamIterType fmFifoElementRamIdx;
    for(fmFifoElementRamIdx = 0u; fmFifoElementRamIdx < PduR_GetSizeOfFmFifoElementRam(memIdx); fmFifoElementRamIdx++)
    {
      PduR_SetBmTxBufferRomIdxOfFmFifoElementRam(fmFifoElementRamIdx, PDUR_NO_BMTXBUFFERROMIDXOFFMFIFOELEMENTRAM, memIdx);      /* SBSW_PDUR_CSL01 */
      PduR_SetRmDestRomIdxOfFmFifoElementRam(fmFifoElementRamIdx, 0, memIdx);      /* SBSW_PDUR_CSL01 */
    }
  }
  {
    PduR_FmFifoInstanceRamIterType fmFifoInstanceRamIdx;
    for(fmFifoInstanceRamIdx = 0u; fmFifoInstanceRamIdx < PduR_GetSizeOfFmFifoInstanceRam(memIdx); fmFifoInstanceRamIdx++)
    {
      PduR_SetBmTxBufferInstanceRomIdxOfFmFifoInstanceRam(fmFifoInstanceRamIdx, PDUR_NO_BMTXBUFFERINSTANCEROMIDXOFFMFIFOINSTANCERAM, memIdx);   /* SBSW_PDUR_CSL01 */
    }
  }
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_Peek
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
FUNC(Std_ReturnType, PDUR_CODE) PduR_Fm_Peek(PduR_FmFifoRamIterType fmFifoRamIdx, P2VAR(PduR_FmFifoElementRamIterType, AUTOMATIC, PDUR_APPL_DATA) fmFifoElementRamIdx, PduR_MemIdxType memIdx)
{
  Std_ReturnType retVal = E_NOT_OK;     /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* FifoElements in the queue? */
  while(PduR_Fm_GetFillLevelSafe(fmFifoRamIdx, memIdx) > 0u)
  {
    PduR_FmFifoElementRamIterType fmFifoElementRamReadIdx = PduR_Fm_IncrementReadIndex(fmFifoRamIdx, memIdx);

    if(PduR_Fm_IsFifoElementAllocated(fmFifoElementRamReadIdx, memIdx) == E_OK)
    {
      *fmFifoElementRamIdx = fmFifoElementRamReadIdx;   /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
      retVal = E_OK;
      break;
    }
  }
  return retVal;
}
#endif

#if (PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_IsFifoElementAllocated
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
*********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_Fm_IsFifoElementAllocated(PduR_FmFifoElementRamIterType fmFifoElementRamIdx, PduR_MemIdxType memIdx)
{
  PduR_BmTxBufferRomIterType bmTxBufferRomIdx;

  /* Is a TxBuffer assigned to the FifoElement? */
  return PduR_Fm_GetCurrentlyUsedBmTxBufferRomIdxByFmFifoElementIdx(fmFifoElementRamIdx, &bmTxBufferRomIdx, memIdx); /* SBSW_PDUR_STACK_VARIABLE */
}
#endif

#if (PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_AssignTxBuffer2FifoElement
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
  *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Fm_AssignTxBuffer2FifoElement(PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx, PduR_BmTxBufferRomIdxOfFmFifoElementRamType bmTxBufferRomIdx, PduR_MemIdxType memIdx)
{
  PduR_SetBmTxBufferRomIdxOfFmFifoElementRam(fmFifoElementRamWriteIdx, bmTxBufferRomIdx, memIdx);       /* SBSW_PDUR_CSL03 */
}
#endif

#if (PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_ReleaseFifoElement
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
  *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Fm_ReleaseFifoElement(PduR_FmFifoElementRamIterType fmFifoElementRamIdx, PduR_MemIdxType memIdx)
{
  PduR_BmTxBufferRomIterType bmTxBufferRomIdx;

  /* Reset (optional) referenced TxBuffer */
  if(PduR_Fm_GetCurrentlyUsedBmTxBufferRomIdxByFmFifoElementIdx(fmFifoElementRamIdx, &bmTxBufferRomIdx, memIdx) == E_OK) /* SBSW_PDUR_STACK_VARIABLE */ /* COV_PDUR_ROBUSTNESS */
  {
    PduR_Bm_ResetTxBuffer(bmTxBufferRomIdx, memIdx);
  }

  PduR_SetRmDestRomIdxOfFmFifoElementRam(fmFifoElementRamIdx, 0, memIdx);  /* SBSW_PDUR_CSL03 */
  /* Release Tx buffer Fifo Element connection */
  PduR_SetBmTxBufferRomIdxOfFmFifoElementRam(fmFifoElementRamIdx, PDUR_NO_BMTXBUFFERROMIDXOFFMFIFOELEMENTRAM, memIdx);  /* SBSW_PDUR_IDX_PARAM_INTERNAL_FUNCTION */
}
#endif

#if (PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_GetCurrentlyUsedBmTxBufferRomIdxByFmFifoElementIdx
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
  *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_Fm_GetCurrentlyUsedBmTxBufferRomIdxByFmFifoElementIdx(PduR_FmFifoElementRamIterType fmFifoElementRamIdx, P2VAR(PduR_BmTxBufferRomIterType, AUTOMATIC, PDUR_APPL_DATA) bmTxBufferRomIdx, PduR_MemIdxType memIdx)
{
  Std_ReturnType retVal;
  PduR_BmTxBufferRomIterType readBmTxBufferRomIdx = PduR_Fm_GetBmTxBufferRomIdxOfFmFifoElementRamSafe(fmFifoElementRamIdx, memIdx);

  if(readBmTxBufferRomIdx == PDUR_NO_BMTXBUFFERROMIDXOFFMFIFOELEMENTRAM)
  {
    retVal = E_NOT_OK;
  }
  else
  {
    *bmTxBufferRomIdx = readBmTxBufferRomIdx; /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
    retVal = E_OK;
  }

  return retVal;
}
#endif

#if (PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_GetBmTxBufferRomIdxOfFmFifoElementRamSafe
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(PduR_BmTxBufferRomIdxOfFmFifoElementRamType, PDUR_CODE) PduR_Fm_GetBmTxBufferRomIdxOfFmFifoElementRamSafe(PduR_FmFifoElementRamIterType fmFifoElementRamIdx, PduR_MemIdxType memIdx)
{
  PduR_BmTxBufferRomIdxOfFmFifoElementRamType bmTxBufferRomIdx = PduR_GetBmTxBufferRomIdxOfFmFifoElementRam(fmFifoElementRamIdx, memIdx);

# if (PDUR_EXTENDED_ERROR_CHECKS == STD_ON)
  PduR_SizeOfBmTxBufferInstanceRomType sizeOfBmTxBufferRom = PduR_GetSizeOfBmTxBufferRom(memIdx);

  if((bmTxBufferRomIdx >= sizeOfBmTxBufferRom) && (bmTxBufferRomIdx != PDUR_NO_BMTXBUFFERROMIDXOFFMFIFOELEMENTRAM)) /* COV_PDUR_EXTENDED_ERROR_CHECKS */
  {
    bmTxBufferRomIdx = 0;
    PduR_ReportRuntimeDetError(PDUR_FCT_GETTXBUFFEROFFIFOELEMENT, PDUR_E_IDXOUTOFBOUNDS);
  }
# endif

  return bmTxBufferRomIdx;
}
#endif

#if (PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_GetBmTxBufferInstanceRomIdxOfFmFifoInstanceRamSafe
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(PduR_BmTxBufferInstanceRomIterType, PDUR_CODE) PduR_Fm_GetBmTxBufferInstanceRomIdxOfFmFifoInstanceRamSafe(PduR_FmFifoInstanceRomIterType fmFifoInstanceRomIdx, PduR_MemIdxType memIdx)
{
  PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx = PduR_GetBmTxBufferInstanceRomIdxOfFmFifoInstanceRam(fmFifoInstanceRomIdx, memIdx);

# if (PDUR_EXTENDED_ERROR_CHECKS == STD_ON)
  PduR_SizeOfBmTxBufferInstanceRomType sizeOfBmTxBufferInstanceRom = PduR_GetSizeOfBmTxBufferInstanceRom(memIdx);

  if((bmTxBufferInstanceRomIdx >= sizeOfBmTxBufferInstanceRom) && (bmTxBufferInstanceRomIdx != PDUR_NO_BMTXBUFFERINSTANCEROMIDXOFFMFIFOINSTANCERAM)) /* COV_PDUR_EXTENDED_ERROR_CHECKS */
  {
    bmTxBufferInstanceRomIdx = 0;
    PduR_ReportRuntimeDetError(PDUR_FCT_GETTXBUFFERINSTANCEOFFIFOINSTANCE, PDUR_E_IDXOUTOFBOUNDS);
  }
# endif

  return bmTxBufferInstanceRomIdx;
}
#endif

#if (PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_GetCurrentlyUsedBmTxBufferInstanceIdxByRmGDestIdx
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
  *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_Fm_GetCurrentlyUsedBmTxBufferInstanceIdxByRmGDestIdx(PduR_RmGDestRomIterType rmGDestRomIdx, P2VAR(PduR_BmTxBufferInstanceRomIterType, AUTOMATIC, PDUR_APPL_DATA) bmTxBufferInstanceRomIdx)
{
  Std_ReturnType retVal;     /* PRQA S 2981 */ /* MD_MSR_RetVal */
  PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfRmGDestRom(rmGDestRomIdx);
  PduR_BmTxBufferInstanceRomIterType readBmTxBufferInstanceRomIdxOfFmFifoInstance = PduR_Fm_GetBmTxBufferInstanceRomIdxOfFmFifoInstanceRamSafe(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx), memIdx);

  if(readBmTxBufferInstanceRomIdxOfFmFifoInstance == PDUR_NO_BMTXBUFFERINSTANCEROMIDXOFFMFIFOINSTANCERAM) /* COV_PDUR_ROBUSTNESS */
  {
    retVal = E_NOT_OK;
  }
  else
  {
    *bmTxBufferInstanceRomIdx = readBmTxBufferInstanceRomIdxOfFmFifoInstance; /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
    retVal = E_OK;
  }

  return retVal;
}
#endif

# if (PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_IncrementReadIndex
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
  *********************************************************************************************************************/
FUNC(PduR_FmFifoElementRamIterType, PDUR_CODE) PduR_Fm_IncrementReadIndex(PduR_FmFifoRamIterType fmFifoRamIdx, PduR_MemIdxType memIdx)
{
  PduR_FmFifoElementRamReadIdxOfFmFifoRamType fmFifoElementRamReadIdx = PduR_Fm_GetFmFifoElementRamReadIdxOfFmFifoRamSafe(fmFifoRamIdx, memIdx);

  /* Get next element */
  if(fmFifoElementRamReadIdx >= ((PduR_GetFmFifoElementRamEndIdxOfFmFifoRom(fmFifoRamIdx, memIdx) - 1u)))
  {
    /* Wrap-around */
    fmFifoElementRamReadIdx = PduR_GetFmFifoElementRamStartIdxOfFmFifoRom(fmFifoRamIdx, memIdx);
  }
  else
  {
    fmFifoElementRamReadIdx++;
  }
  PduR_DecFillLevelOfFmFifoRam(fmFifoRamIdx, memIdx);       /* SBSW_PDUR_IDX_PARAM_INTERNAL_FUNCTION */
  PduR_SetFmFifoElementRamReadIdxOfFmFifoRam(fmFifoRamIdx, fmFifoElementRamReadIdx, memIdx);      /* SBSW_PDUR_IDX_PARAM_INTERNAL_FUNCTION */

  return fmFifoElementRamReadIdx;
}
#endif

# if (PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_IncrementWriteIndex
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
  *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Fm_IncrementWriteIndex(PduR_FmFifoRamIterType fmFifoRamIdx, PduR_MemIdxType memIdx)
{
  PduR_FmFifoElementRamWriteIdxOfFmFifoRamType fmFifoElementRamWriteIdx = PduR_Fm_GetFmFifoElementRamWriteIdxSafe(fmFifoRamIdx, memIdx); /* PRQA S 2842 */ /* MD_PduR_2842 */

  /* Get next fifo element */ /* Check if the write Idx is at the end (EndIdx -1) */
  if(fmFifoElementRamWriteIdx >= (PduR_GetFmFifoElementRamEndIdxOfFmFifoRom(fmFifoRamIdx, memIdx) - 1u))      /* COV_PDUR_ONLY_SHARED_OR_DEDICATED_BUFFER */
  {
    /* Wrap-around */
    fmFifoElementRamWriteIdx = PduR_GetFmFifoElementRamStartIdxOfFmFifoRom(fmFifoRamIdx, memIdx);
  }
  else
  {
    fmFifoElementRamWriteIdx++;
  }
  /* Update global FifoElement write pointer. This pointer points to the next available Fifo element. */
  PduR_SetFmFifoElementRamWriteIdxOfFmFifoRam(fmFifoRamIdx, fmFifoElementRamWriteIdx, memIdx);        /* PRQA S 2842 */ /* MD_PduR_2842 */ /* SBSW_PDUR_CSL03 */
}
#endif

/**********************************************************************************************************************
 * PduR_Fm_PutFifo
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
#if (PDUR_EXISTS_SHARED_FIFO_QUEUE_IMPLEMENTATIONTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
FUNC(Std_ReturnType, PDUR_CODE) PduR_Fm_PutFifo(PduR_RmGDestRomIterType rmGDest, PduR_RmDestRomIterType rmDest, PduLengthType pduLength, SduDataPtrType sduDataPtr)
{
  Std_ReturnType retVal = E_NOT_OK;     /* PRQA S 2981 */ /* MD_MSR_RetVal */
  PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfRmGDestRom(rmGDest);
  PduR_FmFifoRomIterType fmFifoRomIdx = PduR_GetFmFifoRomIdxOfFmFifoInstanceRom(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDest), memIdx);
  PduR_FmFifoElementRamWriteIdxOfFmFifoRamType fmFifoElementRamWriteIdx = PduR_Fm_GetFmFifoElementRamWriteIdxSafe(fmFifoRomIdx, memIdx);

  if(PduR_Fm_IsFifoElementAllocated(fmFifoElementRamWriteIdx, memIdx) != E_OK)
  {
    PduR_BmTxBufferRomIdxOfBmTxBufferIndRomType allocatedTxBufferIdxPtr = 0u;
    PduLengthType bufferSizePtr = 0u;

    /* The pduLength already includes optional metadata -> it's the optimal and minimum buffer length. */
    if(PduR_Bm_AllocateTxBuffer(fmFifoRomIdx, pduLength, pduLength, pduLength, &bufferSizePtr, &allocatedTxBufferIdxPtr, memIdx) == BUFREQ_OK)     /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
    {
      PduR_IncFillLevelOfFmFifoRam(fmFifoRomIdx, memIdx); /* SBSW_PDUR_CSL03 */
      PduR_Fm_IncrementWriteIndex(fmFifoRomIdx, memIdx);

      PduR_Fm_AssignTxBuffer2FifoElement(fmFifoElementRamWriteIdx, allocatedTxBufferIdxPtr, memIdx);
      PduR_SetRmDestRomIdxOfFmFifoElementRam(fmFifoElementRamWriteIdx, (PduR_RmDestRomIdxOfFmFifoElementRamType) rmDest, memIdx);   /* SBSW_PDUR_CSL01 */

      {
        PduR_BmTxBufferRomIterType bmTxBufferRomIdx;

        if(PduR_Fm_GetCurrentlyUsedBmTxBufferRomIdxByFmFifoElementIdx(fmFifoElementRamWriteIdx, &bmTxBufferRomIdx, memIdx) == E_OK) /* SBSW_PDUR_STACK_VARIABLE */ /* COV_PDUR_ROBUSTNESS */
        {
          (void) PduR_Bm_PutData(bmTxBufferRomIdx, pduLength, sduDataPtr, memIdx);      /* SBSW_PDUR_STACK_VARIABLE */
          retVal = E_OK;
        }
      }
    }
  }
  return retVal;
}
#endif

#if (PDUR_EXISTS_SHARED_FIFO_QUEUE_IMPLEMENTATIONTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_RemoveElement
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Fm_RemoveElement(PduR_RmGDestRomIterType rmGDestRomIdx)
{
  PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfRmGDestRom(rmGDestRomIdx);
  PduR_FmFifoRamIterType fmFifoRomIdx = PduR_GetFmFifoRomIdxOfFmFifoInstanceRom(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx), memIdx);
  PduR_FmFifoElementRamIterType fmFifoElementRamReadIdx = PduR_Fm_GetFmFifoElementRamReadIdxOfFmFifoRamSafe(fmFifoRomIdx, memIdx);
  PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx;

  PduR_Fm_ReleaseFifoElement(fmFifoElementRamReadIdx, memIdx);
  if(PduR_Fm_GetCurrentlyUsedBmTxBufferInstanceIdxByRmGDestIdx(rmGDestRomIdx, &bmTxBufferInstanceRomIdx) == E_OK) /* SBSW_PDUR_STACK_VARIABLE */ /* COV_PDUR_ROBUSTNESS */
  {
    PduR_Bm_ResetTxBufferInstance(bmTxBufferInstanceRomIdx, memIdx);
  }
  (void) PduR_Fm_IncrementReadIndex(fmFifoRomIdx, memIdx);
}
#endif

#if (PDUR_EXISTS_SHARED_FIFO_QUEUE_IMPLEMENTATIONTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_GetNextElement
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_Fm_GetNextElement(PduR_RmGDestRomIterType rmGDestRomIdx, P2VAR(PduR_RmDestRomIterType, AUTOMATIC, PDUR_APPL_DATA) rmDestRomIdx, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info)
{
  Std_ReturnType retVal = E_NOT_OK;     /* PRQA S 2981 */ /* MD_MSR_RetVal */
  PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfRmGDestRom(rmGDestRomIdx);
  PduR_FmFifoElementRamIterType fmFifoElementRamReadIdx = PduR_Fm_GetFmFifoElementRamReadIdxOfFmFifoRamSafe(PduR_GetFmFifoRomIdxOfFmFifoInstanceRom(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx), memIdx), memIdx);

  if(PduR_Fm_IsFifoElementAllocated(fmFifoElementRamReadIdx, memIdx) == E_OK)
  {
    PduR_BmTxBufferRomIterType bmTxBufferRomIdx;

    if(PduR_Fm_GetCurrentlyUsedBmTxBufferRomIdxByFmFifoElementIdx(fmFifoElementRamReadIdx, &bmTxBufferRomIdx, memIdx) == E_OK) /* SBSW_PDUR_STACK_VARIABLE */ /* COV_PDUR_ROBUSTNESS */
    {
      PduR_BmTxBufferInstanceRomStartIdxOfBmTxBufferRomType bmTxBufferInstanceRomIdx = PduR_GetBmTxBufferInstanceRomStartIdxOfBmTxBufferRom(bmTxBufferRomIdx, memIdx);

      PduR_Bm_EnableBmTxBufferInstance(bmTxBufferRomIdx, bmTxBufferInstanceRomIdx, memIdx);
      PduR_SetBmTxBufferInstanceRomIdxOfFmFifoInstanceRam(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx), bmTxBufferInstanceRomIdx, memIdx);       /* SBSW_PDUR_CSL03 */

      if(PduR_Fm_GetRmDestRomIdxOfFmFifoElementRamSafe(fmFifoElementRamReadIdx, rmDestRomIdx, memIdx) == E_OK) /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */ /* COV_PDUR_ROBUSTNESS */ /* PRQA S 2995, 2991 */ /* MD_PduR_2995_2996, MD_PduR_2991 */
      {
        PduR_Bm_CopyDataAsPtr(bmTxBufferInstanceRomIdx, info, PduR_Bm_GetLinearDataSizeInstance(bmTxBufferInstanceRomIdx, memIdx), memIdx);       /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
        retVal = E_OK;
      }
    }
  }

  return retVal;
}
#endif

#if (PDUR_EXISTS_SHARED_FIFO_QUEUE_IMPLEMENTATIONTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_GetFillLevel
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(uint16, PDUR_CODE) PduR_Fm_GetFillLevel(PduR_RmGDestRomIterType rmGDestRomIdx) /* COV_PDUR_NO_DEFERRED_IF_ROUTING */
{
  PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfRmGDestRom(rmGDestRomIdx);

  return PduR_Fm_GetFillLevelSafe(PduR_GetFmFifoRomIdxOfFmFifoInstanceRom(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx), memIdx), memIdx);
}
#endif

#if (PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_GetFillLevelSafe
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(uint16, PDUR_CODE) PduR_Fm_GetFillLevelSafe(PduR_FmFifoRamIterType fmFifoRamIdx, PduR_MemIdxType memIdx) /* COV_PDUR_NO_DEFERRED_IF_ROUTING */
{
  uint16 fillLevel = PduR_GetFillLevelOfFmFifoRam(fmFifoRamIdx, memIdx);

# if (PDUR_EXTENDED_ERROR_CHECKS == STD_ON)
  PduR_FmFifoElementRamLengthOfFmFifoRomType fifoDepth = PduR_GetFmFifoElementRamLengthOfFmFifoRom(fmFifoRamIdx, memIdx);

  if(fillLevel > fifoDepth) /* COV_PDUR_EXTENDED_ERROR_CHECKS */
  {
    fillLevel = fifoDepth;
    PduR_ReportRuntimeDetError(PDUR_FCT_GETFILLLEVEL, PDUR_E_IDXOUTOFBOUNDS);
  }
# endif

  return fillLevel;
}
#endif

#if (PDUR_EXISTS_SHARED_FIFO_QUEUE_IMPLEMENTATIONTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_FlushFiFo
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Fm_FlushFiFo(PduR_RmGDestRomIterType rmGDestRomIdx)
{
  PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfRmGDestRom(rmGDestRomIdx);
  PduR_FmFifoRomIterType fmFifoRomIdx = PduR_GetFmFifoRomIdxOfFmFifoInstanceRom(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx), memIdx);
  PduR_FmFifoElementRamIterType fmFifoElementRamIdx;

  for(fmFifoElementRamIdx = PduR_GetFmFifoElementRamStartIdxOfFmFifoRom(fmFifoRomIdx, memIdx); fmFifoElementRamIdx < PduR_GetFmFifoElementRamEndIdxOfFmFifoRom(fmFifoRomIdx, memIdx); fmFifoElementRamIdx++)
  {
    PduR_BmTxBufferRomIterType bmTxBufferRomIdx;

    /* Reset (optional) referenced TxBuffer */
    if(PduR_Fm_GetCurrentlyUsedBmTxBufferRomIdxByFmFifoElementIdx(fmFifoElementRamIdx, &bmTxBufferRomIdx, memIdx) == E_OK) /* SBSW_PDUR_STACK_VARIABLE */ /* COV_PDUR_ROBUSTNESS */
    {
      PduR_Bm_ResetTxBuffer(bmTxBufferRomIdx, memIdx);
      PduR_Bm_ResetTxBufferInstance(PduR_GetBmTxBufferInstanceRomStartIdxOfBmTxBufferRom(bmTxBufferRomIdx, memIdx), memIdx);
    }
    PduR_Fm_ReleaseFifoElement(fmFifoElementRamIdx, memIdx);
  }
  PduR_SetFillLevelOfFmFifoRam(fmFifoRomIdx, 0u, memIdx);       /* PRQA S 2842 */ /* MD_PduR_2842 */ /* SBSW_PDUR_CSL02 */
  PduR_SetFmFifoElementRamReadIdxOfFmFifoRam(fmFifoRomIdx, PduR_GetFmFifoElementRamStartIdxOfFmFifoRom(fmFifoRomIdx, memIdx), memIdx);  /* PRQA S 2842 */ /* MD_PduR_2842 */ /* SBSW_PDUR_CSL02 */
  PduR_SetFmFifoElementRamWriteIdxOfFmFifoRam(fmFifoRomIdx, PduR_GetFmFifoElementRamStartIdxOfFmFifoRom(fmFifoRomIdx, memIdx), memIdx); /* PRQA S 2842 */ /* MD_PduR_2842 */ /* SBSW_PDUR_CSL02 */
}
#endif

#if (PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_GetFmFifoElementRamReadIdxOfFmFifoRamSafe
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(PduR_FmFifoElementRamReadIdxOfFmFifoRamType, PDUR_CODE) PduR_Fm_GetFmFifoElementRamReadIdxOfFmFifoRamSafe(PduR_FmFifoRamIterType fmFifoRamIdx, PduR_MemIdxType memIdx)
{
  PduR_FmFifoElementRamReadIdxOfFmFifoRamType readIdx = PduR_GetFmFifoElementRamReadIdxOfFmFifoRam(fmFifoRamIdx, memIdx);

# if (PDUR_EXTENDED_ERROR_CHECKS == STD_ON)
  PduR_FmFifoElementRamStartIdxOfFmFifoRomType startIdxOfBuffer = PduR_GetFmFifoElementRamStartIdxOfFmFifoRom(fmFifoRamIdx, memIdx);
  PduR_FmFifoElementRamEndIdxOfFmFifoRomType endIdxOfBuffer = PduR_GetFmFifoElementRamEndIdxOfFmFifoRom(fmFifoRamIdx, memIdx);

  if(readIdx >= endIdxOfBuffer) /* COV_PDUR_EXTENDED_ERROR_CHECKS */
  {
    readIdx = endIdxOfBuffer - 1u;
    PduR_ReportRuntimeDetError(PDUR_FCT_GETFMREADIDX, PDUR_E_IDXOUTOFBOUNDS);
  }
  if(readIdx < startIdxOfBuffer) /* COV_PDUR_EXTENDED_ERROR_CHECKS */
  {
    readIdx = startIdxOfBuffer;
    PduR_ReportRuntimeDetError(PDUR_FCT_GETFMREADIDX, PDUR_E_IDXOUTOFBOUNDS);
  }
# endif

  return readIdx;
}
#endif

#if (PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_GetFmFifoElementRamWriteIdxSafe
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(PduR_FmFifoElementRamWriteIdxOfFmFifoRamType, PDUR_CODE) PduR_Fm_GetFmFifoElementRamWriteIdxSafe(PduR_FmFifoRamIterType fmFifoRamIdx, PduR_MemIdxType memIdx)
{
  PduR_FmFifoElementRamWriteIdxOfFmFifoRamType writeIdx = PduR_GetFmFifoElementRamWriteIdxOfFmFifoRam(fmFifoRamIdx, memIdx);

# if (PDUR_EXTENDED_ERROR_CHECKS == STD_ON)
  PduR_FmFifoElementRamStartIdxOfFmFifoRomType startIdxOfBuffer = PduR_GetFmFifoElementRamStartIdxOfFmFifoRom(fmFifoRamIdx, memIdx);
  PduR_FmFifoElementRamEndIdxOfFmFifoRomType endIdxOfBuffer = PduR_GetFmFifoElementRamEndIdxOfFmFifoRom(fmFifoRamIdx, memIdx);

  if(writeIdx >= endIdxOfBuffer) /* COV_PDUR_EXTENDED_ERROR_CHECKS */
  {
    writeIdx = endIdxOfBuffer - 1u;
    PduR_ReportRuntimeDetError(PDUR_FCT_GETFMWRITEIDX, PDUR_E_IDXOUTOFBOUNDS);
  }
  if(writeIdx < startIdxOfBuffer) /* COV_PDUR_EXTENDED_ERROR_CHECKS */
  {
    writeIdx = startIdxOfBuffer;
    PduR_ReportRuntimeDetError(PDUR_FCT_GETFMWRITEIDX, PDUR_E_IDXOUTOFBOUNDS);
  }
# endif

  return writeIdx;
}
#endif

#if (PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_GetRmDestRomIdxOfFmFifoElementRamSafe
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_Fm_GetRmDestRomIdxOfFmFifoElementRamSafe(PduR_FmFifoElementRamIterType fmFifoElementRamIdx, P2VAR(PduR_RmDestRomIterType, AUTOMATIC, PDUR_APPL_DATA) rmDestRomIdx, PduR_MemIdxType memIdx)
{
  Std_ReturnType retVal = E_NOT_OK;     /* PRQA S 2981 */ /* MD_MSR_RetVal */
  PduR_RmDestRomIdxOfFmFifoElementRamType readRmDestRomIdx = PduR_GetRmDestRomIdxOfFmFifoElementRam(fmFifoElementRamIdx, memIdx);

# if (PDUR_EXTENDED_ERROR_CHECKS == STD_ON)
  if(readRmDestRomIdx >= PduR_GetSizeOfRmDestRom()) /* COV_PDUR_EXTENDED_ERROR_CHECKS */
  {
    PduR_ReportRuntimeDetError(PDUR_FCT_GETDESTHNDOFFIFOELEMENT, PDUR_E_IDXOUTOFBOUNDS);
    retVal = E_NOT_OK;
  }
  else
# endif
  {
    *rmDestRomIdx = readRmDestRomIdx; /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
    retVal = E_OK;
  }

  return retVal;
}
#endif

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h" /* PRQA S 5087 */   /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  END OF FILE: PduR_Fm.c
 *********************************************************************************************************************/
