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
 *         File:  PduR_Bm.c
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


#define PDUR_BM_SOURCE
/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "PduR.h"
#include "PduR_Bm.h"
#include "PduR_Lock.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/
#define PduR_Core_MemCpyRamToRam(d, s, l)    VStdMemCpyRamToRam((d), (s), (l))
#define PduR_Core_MemCpyRomToRam(d, s, l)    VStdMemCpyRomToRam((d), (s), (l))

# if(PDUR_BMTXBUFFERRAM == STD_ON)
#  define PduR_Bm_GetLengthOfBmTxBuffer(Index, memIdx)                       (PduR_GetBmTxBufferArrayRamLengthOfBmTxBufferRom(Index, memIdx) - (PduR_BmTxBufferArrayRamIterType) 1u)
#  define PduR_Bm_GetInboundBmTxBufferArrayEndIdxOfBmTxBuffer(Index, memIdx) (PduR_GetBmTxBufferArrayRamEndIdxOfBmTxBufferRom(Index, memIdx) - (PduR_BmTxBufferArrayRamIterType) 1u)
# endif

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

#if(PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_Init_TxBuffer
 *********************************************************************************************************************/
/*! \brief      This function initializes the BufferManager TxBuffer
 *  \details     -
 *  \param[in]  memIdx  memory section index
 *  \pre        PduR_InitMemory() has been executed, if the start up code does not initialize variables.
 *  \note       The function must be called on task level and has not to be interrupted.
 *              by other administrative function calls.
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_Init_TxBuffer(PduR_MemIdxType memIdx);
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_Init_TxBufferInstance
 *********************************************************************************************************************/
/*! \brief      This function initializes the BufferManager TxBuffer Instance
 *  \details     -
 *  \param[in]  memIdx  memory section index
 *  \pre        PduR_InitMemory() has been executed, if the start up code does not initialize variables.
 *  \note       The function must be called on task level and has not to be interrupted.
 *              by other administrative function calls.
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_Init_TxBufferInstance(PduR_MemIdxType memIdx);
#endif

#if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_Put_Between_WriteIdx_EndIdx
 *********************************************************************************************************************/
/*! \brief      The WriteId leading. Add data up to the buffer end.
 *  \details    -
 *  \param[in]  bmTxBufferRomIdx  read index in the transport protocol Tx buffer
 *  \param[in]  pduLength                length to copy
 *  \param[in]  sduDataPtr               data pointer
 *  \param[in]  memIdx                   memory section index
 *  \pre        -
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_Put_Between_WriteIdx_EndIdx(PduR_BmTxBufferRomIterType bmTxBufferRomIdx, PduLengthType pduLength,
                                                                       CONST(SduDataPtrType, AUTOMATIC) sduDataPtr, PduR_MemIdxType memIdx);
#endif

#if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_Put_Between_WriteIdx_ReadIdx
 *********************************************************************************************************************/
/*! \brief      The WriteId lagging the ReadIdx. Add data to the buffer in this range.
 *  \details    -
 *  \param[in]  bmTxBufferRomIdx  read index in the transport protocol Tx buffer
 *  \param[in]  pduLength                length to copy
 *  \param[in]  sduDataPtr               data pointer
 *  \param[in]  memIdx                   memory section index
 *  \pre        -
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_Put_Between_WriteIdx_ReadIdx(PduR_BmTxBufferRomIterType bmTxBufferRomIdx, PduLengthType pduLength,
                                                                        CONST(SduDataPtrType, AUTOMATIC) sduDataPtr, PduR_MemIdxType memIdx);
#endif

#if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_PutData_StateHandler_BUFFER_READ4WRITE
 *********************************************************************************************************************/
/*! \brief      Helper function which handles the BUFFER_READ4WRITE state.
 *  \details    -
 *  \param[in]  bmTxBufferRomIdx         read index in the transport protocol Tx buffer
 *  \param[in]  pduLength                length to copy
 *  \param[in]  sduDataPtr               data pointer
 *  \param[in]  memIdx                   memory section index
 *  \return     BUFREQ_OK                State change action was successful.
 *              BUFREQ_E_NOT_OK          State change action was not successful.
 *  \pre        -
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_Bm_PutData_StateHandler_BUFFER_READ4WRITE(PduR_BmTxBufferRomIterType bmTxBufferRomIdx, PduLengthType pduLength,
                                                                                               CONST(SduDataPtrType, AUTOMATIC) sduDataPtr, PduR_MemIdxType memIdx);
#endif

#if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_PutData_StateHandler_BUFFER_EMPTY_OR_WRITE4READ
 *********************************************************************************************************************/
/*! \brief      Helper function which handles the EMPTY or WRITE4READ state.
 *  \details    -
 *  \param[in]  bmTxBufferRomIdx         buffer index
 *  \param[in]  pduLength                length to copy
 *  \param[in]  sduDataPtr               data pointer
 *  \param[in]  memIdx                   memory section index
 *  \return     BUFREQ_OK                State change action was successful.
 *              BUFREQ_E_NOT_OK          State change action was not successful.
 *  \pre        -
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_Bm_PutData_StateHandler_BUFFER_EMPTY_OR_WRITE4READ(PduR_BmTxBufferRomIterType bmTxBufferRomIdx,
                                                                                                        PduLengthType pduLength,
                                                                                                        CONST(SduDataPtrType, AUTOMATIC) sduDataPtr,
                                                                                                        PduR_MemIdxType memIdx);
#endif

#if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_Get_Between_ReadIdx_WriteIdx
 *********************************************************************************************************************/
/*! \brief      The ReadIdx lagging the WriteIdx. Get data in this range.
 *  \details    -
 *  \param[in]  bmTxBufferInstanceRomIdx instance Idx.
 *  \param[in]  pduLength                length to copy.
 *  \param[in]  sduDataPtr               data pointer.
 *  \param[in]  memIdx                   memory section index
 *  \pre        -
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_Get_Between_ReadIdx_WriteIdx(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx,
                                                                        PduLengthType pduLength,
                                                                        CONST(SduDataPtrType, AUTOMATIC) sduDataPtr,
                                                                        PduR_MemIdxType memIdx);
#endif

#if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_Get_Between_ReadIdx_EndIdx
 *********************************************************************************************************************/
/*! \brief      The ReadIdx is leading. Get data up to the buffer end.
 *  \details    -
 *  \param[in]  bmTxBufferInstanceRomIdx instance Idx.
 *  \param[in]  pduLength                length to copy.
 *  \param[in]  sduDataPtr               data pointer.
 *  \param[in]  memIdx                   memory section index
 *  \pre        -
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_Get_Between_ReadIdx_EndIdx(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx, PduLengthType pduLength,
                                                                      CONST(SduDataPtrType, AUTOMATIC) sduDataPtr, PduR_MemIdxType memIdx);
#endif

#if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_GetData_StateHandler_BUFFER_WRITE4READ
 *********************************************************************************************************************/
/*! \brief      Helper function which handles the BUFFER_WRITE4READ state.
 *  \details    -
 *  \param[in]  bmTxBufferInstanceRomIdx instance Idx.
 *  \param[in]  pduLength              length to copy.
 *  \param[in]  sduDataPtr             data pointer.
 *  \param[in]  memIdx                 memory section index
 *  \return     BUFREQ_OK              State change action was successful.
 *              BUFREQ_E_NOT_OK        State change action was not successful.
 *  \pre        -
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_Bm_GetData_StateHandler_BUFFER_WRITE4READ(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx, PduLengthType pduLength,
                                                                                               CONST(SduDataPtrType, AUTOMATIC) sduDataPtr, PduR_MemIdxType memIdx);
#endif

#if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_GetData_StateHandler_BUFFER_FULL_OR_READ4WRITE
 *********************************************************************************************************************/
/*! \brief      Helper function which handles the BUFFER_FULL and READ4WRITE state.
 *  \details    -
 *  \param[in]  bmTxBufferInstanceRomIdx instance Idx
 *  \param[in]  pduLength              length to copy
 *  \param[in]  sduDataPtr             data pointer
 *  \param[in]  memIdx                 memory section index
 *  \return     BUFREQ_OK              State change action was successful.
 *              BUFREQ_E_NOT_OK        State change action was not successful.
 *  \pre        -
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_Bm_GetData_StateHandler_BUFFER_FULL_OR_READ4WRITE(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx,
                                                                                                       PduLengthType pduLength,
                                                                                                       CONST(SduDataPtrType, AUTOMATIC) sduDataPtr,
                                                                                                       PduR_MemIdxType memIdx);
#endif

#if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_Switch_WriteIdx
 *********************************************************************************************************************/
/*! \brief      Set WriteIdx to buffer start Idx.
 *  \details    -
 *  \param[in]  bmTxBufferRomIdx   read index in the transport protocol Tx buffer.
 *  \param[in]  memIdx             memory section index
 *  \pre        -
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_Switch_WriteIdx(PduR_BmTxBufferRomIterType bmTxBufferRomIdx, PduR_MemIdxType memIdx);
#endif

#if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_GetLinearBufferSize
 *********************************************************************************************************************/
/*! \brief      Get the free buffer size which is available without doing a wrap around.
 *  \details    -
 *  \param[in]  bmTxBufferRomIdx  index to the BmTxBuffer element
 *  \param[in]  memIdx            memory section index
 *  \return     the calculated free buffer size
 *  \pre        -
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(PduR_BmTxBufferArrayRamIterType, PDUR_CODE) PduR_Bm_GetLinearBufferSize(PduR_BmTxBufferRomIterType bmTxBufferRomIdx, PduR_MemIdxType memIdx);
#endif

#if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_Switch_InstanceReadIdx
 *********************************************************************************************************************/
/*! \brief     Helper function to perform a wrap around for the instance specific read idx.
 *  \details    -
 *  \param[in] bmTxBufferInstanceRomIdx instance Idx.
 *  \param[in] memIdx                   memory section index
 *  \pre        -
 *  \note      get data from buffer.
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_Switch_InstanceReadIdx(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx, PduR_MemIdxType memIdx);
#endif

#if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_PutData_WithWrapAround
 *********************************************************************************************************************/
/*! \brief      Perform wrap around handling for WriteIdx.
 *  \details    -
 *  \param[in]  bmTxBufferRomIdx  read index in the transport protocol Tx buffer.
 *  \param[in]  pduLength              length to copy.
 *  \param[in]  sduDataPtr              data pointer.
 *  \param[in]  memIdx                  memory section index
 *  \pre        -
**********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_PutData_WithWrapAround(PduR_BmTxBufferRomIterType bmTxBufferRomIdx, PduLengthType pduLength, SduDataPtrType sduDataPtr, PduR_MemIdxType memIdx);
#endif

#if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_GetData_WithWrapAround
 **********************************************************************************************************************/
/*! \brief      Perform a wrap around handling for instance ReadIdx.
 *  \details    -
 *  \param[in]  bmTxBufferInstanceRomIdx  instance Idx.
 *  \param[in]  pduLength              length to copy.
 *  \param[in]  sduDataPtr             data pointer.
 *  \param[in]  memIdx                 memory section index
 *  \pre        -
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_GetData_WithWrapAround(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx, PduLengthType pduLength,
                                                                      SduDataPtrType sduDataPtr, PduR_MemIdxType memIdx);
#endif

#if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_GetBmTxBufferArrayRamReadIdxOfBmTxBufferRam
 **********************************************************************************************************************/
/*! \brief      Get BmTxBufferArrayRamRead Idx Of BmTxBufferRam
 *  \details    -
 *  \param[in]  bmTxBufferRomIdx Buffer Idx.
 *  \return     Buffer read index
 *  \pre        -
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(PduR_BmTxBufferArrayRamReadIdxOfBmTxBufferRamType, PDUR_CODE) PduR_Bm_GetBmTxBufferArrayRamReadIdxOfBmTxBufferRam (PduR_BmTxBufferRomIterType bmTxBufferRomIdx, PduR_MemIdxType memIdx);
#endif

#if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_GetBmTxBufferArrayRamReadIdxOfBmTxBufferInstanceRamSafe
 **********************************************************************************************************************/
/*! \brief      Get BmTxBufferArrayRamRead Idx Of BmTxBufferInstanceRam with safe check
 *  \details    -
 *  \param[in]  bmTxBufferInstanceRomIdx Buffer instance Idx.
 *  \param[in]  memIdx  memory section index
 *  \return     Buffer instance read index
 *  \pre        -
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(PduR_BmTxBufferArrayRamReadIdxOfBmTxBufferInstanceRamType, PDUR_CODE) PduR_Bm_GetBmTxBufferArrayRamReadIdxOfBmTxBufferInstanceRamSafe(PduR_BmTxBufferInstanceRamIterType bmTxBufferInstanceRomIdx,
                                                                                                                                                        PduR_MemIdxType memIdx);
#endif

#if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_GetBmTxBufferArrayRamWriteIdxOfBmTxBufferRamSafe
 **********************************************************************************************************************/
/*! \brief      Get BmTxBufferArrayRamWrite Idx Of BmTxBufferRam with safe check
 *  \details    -
 *  \param[in]  bmTxBufferRomIdx Buffer Idx.
 *  \param[in]  memIdx  memory section index
 *  \return     Buffer write index
 *  \pre        -
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(PduR_BmTxBufferArrayRamWriteIdxOfBmTxBufferRamType, PDUR_CODE) PduR_Bm_GetBmTxBufferArrayRamWriteIdxOfBmTxBufferRamSafe(PduR_BmTxBufferRomIterType bmTxBufferRomIdx, PduR_MemIdxType memIdx);
#endif

#if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_GetBmTxBufferArrayRamReadIdxByBmTxBufferInstanceRomIdxChecked
 *********************************************************************************************************************/
/*! \brief       This function returns the currently read BmTxBufferArrayRamReadIdx
 *  \details     -
 *  \param[in]   bmTxBufferInstanceRomIdx   instance Idx.
 *  \param[out]  bmTxBufferArrayRamReadIdx  The BmTxBufferArrayRam read index
 *  \param[in]   memIdx                     memory section index
 *  \return      E_OK                       the read BmTxBufferArrayRamReadIdx is valid and can be used
 *               E_NOT_OK                   the read BmTxBufferArrayRamReadIdx is invalid and can not be used
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_Bm_GetBmTxBufferArrayRamReadIdxByBmTxBufferInstanceRomIdxChecked(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx,
                                                                                                                   PduR_BmTxBufferArrayRamReadIdxOfBmTxBufferInstanceRamType* bmTxBufferArrayRamReadIdx,
                                                                                                                   PduR_MemIdxType memIdx);
#endif

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

#if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_Init_TxBuffer
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_Init_TxBuffer(PduR_MemIdxType memIdx)
{
  PduR_BmTxBufferRomIterType bmTxBufferRomIdx;
  for(bmTxBufferRomIdx = 0u; bmTxBufferRomIdx < PduR_GetSizeOfBmTxBufferRam(memIdx); bmTxBufferRomIdx++)
  {
    PduR_Bm_ResetTxBuffer(bmTxBufferRomIdx, memIdx);
  }
}
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_Init_TxBufferInstance
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_Init_TxBufferInstance(PduR_MemIdxType memIdx)
{
  PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx;
  for(bmTxBufferInstanceRomIdx = 0u; bmTxBufferInstanceRomIdx < PduR_GetSizeOfBmTxBufferInstanceRam(memIdx); bmTxBufferInstanceRomIdx++)
  {
    PduR_Bm_ResetTxBufferInstance(bmTxBufferInstanceRomIdx, memIdx);
  }
}
#endif

#if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_PutData_StateHandler_BUFFER_EMPTY_OR_WRITE4READ
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
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_Bm_PutData_StateHandler_BUFFER_EMPTY_OR_WRITE4READ(PduR_BmTxBufferRomIterType bmTxBufferRomIdx,
                                                                                                        PduLengthType pduLength,
                                                                                                        CONST(SduDataPtrType, AUTOMATIC) sduDataPtr,
                                                                                                        PduR_MemIdxType memIdx)
{
  BufReq_ReturnType retVal = BUFREQ_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  PduR_BmTxBufferArrayRamIterType bmLinearBufferSize = PduR_Bm_GetLinearBufferSize(bmTxBufferRomIdx, memIdx);

  if(bmLinearBufferSize > pduLength)
  {
    PduR_Bm_Put_Between_WriteIdx_EndIdx(bmTxBufferRomIdx, pduLength, sduDataPtr, memIdx); /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
  }
  else if(bmLinearBufferSize == pduLength)
  {
    PduR_Bm_Put_Between_WriteIdx_EndIdx(bmTxBufferRomIdx, pduLength, sduDataPtr, memIdx); /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
    if (PduR_Bm_GetBmTxBufferArrayRamReadIdxOfBmTxBufferRam(bmTxBufferRomIdx, memIdx) != PduR_GetBmTxBufferArrayRamStartIdxOfBmTxBufferRom(bmTxBufferRomIdx, memIdx)) /* COV_PDUR_IF_ONLY */
    {
      PduR_Bm_Switch_WriteIdx(bmTxBufferRomIdx, memIdx);
    }
  }
  else if(PduR_Bm_GetTotalBufferSize(bmTxBufferRomIdx, memIdx) >= pduLength)
  {
    PduR_Bm_PutData_WithWrapAround(bmTxBufferRomIdx, pduLength, sduDataPtr, memIdx); /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
  }
  else
  {
    /* Tp will never request more buffer than the PDUR has provided */
    retVal = BUFREQ_E_NOT_OK;
  }
  return retVal;
}
#endif

#if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_EnableBmTxBufferInstance
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Bm_EnableBmTxBufferInstance(PduR_BmTxBufferRomIterType bmTxBufferRomIdx, PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx, PduR_MemIdxType memIdx)
{
  if(bmTxBufferInstanceRomIdx > PduR_GetBmTxBufferInstanceRomEndIdxOfBmTxBufferRom(bmTxBufferRomIdx, memIdx))   /* COV_PDUR_FATAL_ERROR */
  {
    PduR_Det_ReportError(PDUR_RMTP_ASSIGNASSOCIATEDBUFFER2DESTINATION, PDUR_E_FATAL);
  }
  else
  {
    PduR_SetBmTxBufferArrayRamReadIdxOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx, PduR_GetBmTxBufferArrayRamStartIdxOfBmTxBufferRom(bmTxBufferRomIdx, memIdx), memIdx);       /* SBSW_PDUR_IDX_PARAM_INTERNAL_FUNCTION */
  }
}
#endif

#if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_GetLinearBufferSize
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(PduR_BmTxBufferArrayRamIterType, PDUR_CODE) PduR_Bm_GetLinearBufferSize(PduR_BmTxBufferRomIterType bmTxBufferRomIdx, PduR_MemIdxType memIdx)
{
  PduR_BmTxBufferArrayRamIterType retVal = 0u;  /* PRQA S 2981 */ /* MD_MSR_RetVal */
  PduR_BmTxBufferArrayRamReadIdxOfBmTxBufferRamType bmTxBufferArrayRamReadIdxOfBmTxBufferRam = PduR_Bm_GetBmTxBufferArrayRamReadIdxOfBmTxBufferRam(bmTxBufferRomIdx, memIdx);
  PduR_BmTxBufferArrayRamWriteIdxOfBmTxBufferRamType bmTxBufferArrayRamWriteIdxOfBmTxBufferRam = PduR_Bm_GetBmTxBufferArrayRamWriteIdxOfBmTxBufferRamSafe(bmTxBufferRomIdx, memIdx);

  switch (PduR_Bm_GetPduRBufferStateOfBmTxBufferRam(bmTxBufferRomIdx, memIdx))
  {
    case PDUR_BUFFER_WRITE4READ_PDURBUFFERSTATEOFBMTXBUFFERRAM:
    {
      if (PduR_GetBmTxBufferArrayRamStartIdxOfBmTxBufferRom(bmTxBufferRomIdx, memIdx) == bmTxBufferArrayRamReadIdxOfBmTxBufferRam)
      {
        retVal = PduR_Bm_GetInboundBmTxBufferArrayEndIdxOfBmTxBuffer(bmTxBufferRomIdx, memIdx) - bmTxBufferArrayRamWriteIdxOfBmTxBufferRam;
      }
      else
      {
        retVal = ((PduR_BmTxBufferArrayRamIterType) PduR_GetBmTxBufferArrayRamEndIdxOfBmTxBufferRom(bmTxBufferRomIdx, memIdx)) - bmTxBufferArrayRamWriteIdxOfBmTxBufferRam;
      }
      break;
    }
    case PDUR_BUFFER_READ4WRITE_PDURBUFFERSTATEOFBMTXBUFFERRAM:
    {
      retVal = ((PduR_BmTxBufferArrayRamIterType) bmTxBufferArrayRamReadIdxOfBmTxBufferRam - (PduR_BmTxBufferArrayRamIterType) 1u) - bmTxBufferArrayRamWriteIdxOfBmTxBufferRam;
      break;
    }
    case PDUR_BUFFER_FULL_PDURBUFFERSTATEOFBMTXBUFFERRAM:      /* COV_PDUR_BUFFER_CALCULATION */
    {
      retVal = 0u;
      break;
    }
    case PDUR_BUFFER_EMPTY_PDURBUFFERSTATEOFBMTXBUFFERRAM:
    {
      if (PduR_GetBmTxBufferArrayRamStartIdxOfBmTxBufferRom(bmTxBufferRomIdx, memIdx) == bmTxBufferArrayRamReadIdxOfBmTxBufferRam)
      {
        retVal = PduR_Bm_GetInboundBmTxBufferArrayEndIdxOfBmTxBuffer(bmTxBufferRomIdx, memIdx) - bmTxBufferArrayRamWriteIdxOfBmTxBufferRam;
      }
      else
      {
        retVal = ((PduR_BmTxBufferArrayRamIterType) PduR_GetBmTxBufferArrayRamEndIdxOfBmTxBufferRom(bmTxBufferRomIdx, memIdx)) - bmTxBufferArrayRamWriteIdxOfBmTxBufferRam;
      }
      break;
    }
    default:   /* COV_PDUR_MISRA */
      break;
  }
  return retVal;
}
#endif

#if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_GetBmTxBufferArrayRamReadIdxOfBmTxBufferInstanceRamSafe
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(PduR_BmTxBufferArrayRamReadIdxOfBmTxBufferInstanceRamType, PDUR_CODE) PduR_Bm_GetBmTxBufferArrayRamReadIdxOfBmTxBufferInstanceRamSafe(PduR_BmTxBufferInstanceRamIterType bmTxBufferInstanceRomIdx,
                                                                                                                                                        PduR_MemIdxType memIdx)
{
  PduR_BmTxBufferArrayRamReadIdxOfBmTxBufferInstanceRamType bmTxBufferArrayRamReadIdx = PduR_GetBmTxBufferArrayRamReadIdxOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx, memIdx);

# if (PDUR_EXTENDED_ERROR_CHECKS == STD_ON)
  PduR_BmTxBufferRomIdxOfBmTxBufferInstanceRomType bmTxBufferRomIdx = PduR_GetBmTxBufferRomIdxOfBmTxBufferInstanceRom(bmTxBufferInstanceRomIdx, memIdx);
  PduR_BmTxBufferArrayRamStartIdxOfBmTxBufferRomType startIdxOfBuffer = PduR_GetBmTxBufferArrayRamStartIdxOfBmTxBufferRom(bmTxBufferRomIdx, memIdx);
  PduR_BmTxBufferArrayRamEndIdxOfBmTxBufferRomType endIdxOfBuffer = PduR_GetBmTxBufferArrayRamEndIdxOfBmTxBufferRom(bmTxBufferRomIdx, memIdx);

  if((bmTxBufferArrayRamReadIdx >= endIdxOfBuffer) && (bmTxBufferArrayRamReadIdx != PDUR_NO_BMTXBUFFERARRAYRAMREADIDXOFBMTXBUFFERINSTANCERAM)) /* COV_PDUR_EXTENDED_ERROR_CHECKS */
  {
    bmTxBufferArrayRamReadIdx = ((PduR_BmTxBufferArrayRamReadIdxOfBmTxBufferInstanceRamType) endIdxOfBuffer) - 1u;
    PduR_ReportRuntimeDetError(PDUR_FCT_GW_BUFMGR_GET_READIDX, PDUR_E_IDXOUTOFBOUNDS);
  }
  if((bmTxBufferArrayRamReadIdx < startIdxOfBuffer) && (bmTxBufferArrayRamReadIdx != PDUR_NO_BMTXBUFFERARRAYRAMREADIDXOFBMTXBUFFERINSTANCERAM)) /* PRQA S 2995 */ /* MD_PduR_2995_2996 */ /* COV_PDUR_EXTENDED_ERROR_CHECKS */
  {
    bmTxBufferArrayRamReadIdx = startIdxOfBuffer;
    PduR_ReportRuntimeDetError(PDUR_FCT_GW_BUFMGR_GET_READIDX, PDUR_E_IDXOUTOFBOUNDS);
  }
# endif

  return bmTxBufferArrayRamReadIdx;
}
# endif

#if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_GetData
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_Bm_GetData(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx, PduLengthType pduLength, CONST(SduDataPtrType, AUTOMATIC) sduDataPtr, PduR_MemIdxType memIdx) /* PRQA S 1505 */ /* MD_PduR_1505 */
{
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  PduR_BmTxBufferArrayRamReadIdxOfBmTxBufferInstanceRamType bmTxBufferArrayRamReadIdx;

  if(PduR_Bm_GetBmTxBufferArrayRamReadIdxByBmTxBufferInstanceRomIdxChecked(bmTxBufferInstanceRomIdx, &bmTxBufferArrayRamReadIdx, memIdx) == E_OK) /* SBSW_PDUR_STACK_VARIABLE */ /* COV_PDUR_ROBUSTNESS */
  {
    switch (PduR_Bm_GetPduRBufferStateOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx, bmTxBufferArrayRamReadIdx, memIdx))
    {
      case PDUR_BUFFER_WRITE4READ_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM:
      {
        retVal = PduR_Bm_GetData_StateHandler_BUFFER_WRITE4READ(bmTxBufferInstanceRomIdx, pduLength, sduDataPtr, memIdx); /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
        break;
      }
      case PDUR_BUFFER_FULL_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM:
      case PDUR_BUFFER_READ4WRITE_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM:
      {
        retVal = PduR_Bm_GetData_StateHandler_BUFFER_FULL_OR_READ4WRITE(bmTxBufferInstanceRomIdx, pduLength, sduDataPtr, memIdx); /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
        break;
      }
      case PDUR_BUFFER_EMPTY_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM:     /* COV_PDUR_ONLY_TT_SINGLE_BUFFER */
      {
        if(pduLength == 0u)
        {
          retVal = BUFREQ_OK;
        }
        else
        {
          /* nothing to do no data available */
          retVal = BUFREQ_E_BUSY;
        }
        break;
      }
      default:   /* COV_PDUR_MISRA */
        break;
    }
  }

  return retVal;
}
#endif

#if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_GetBmTxBufferArrayRamWriteIdxOfBmTxBufferRamSafe
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(PduR_BmTxBufferArrayRamWriteIdxOfBmTxBufferRamType, PDUR_CODE) PduR_Bm_GetBmTxBufferArrayRamWriteIdxOfBmTxBufferRamSafe(PduR_BmTxBufferRomIterType bmTxBufferRomIdx, PduR_MemIdxType memIdx)
{
  PduR_BmTxBufferArrayRamWriteIdxOfBmTxBufferRamType bmTxBufferArrayRamWriteIdxOfBmTxBufferRam = PduR_GetBmTxBufferArrayRamWriteIdxOfBmTxBufferRam(bmTxBufferRomIdx, memIdx);

# if (PDUR_EXTENDED_ERROR_CHECKS == STD_ON)
  PduR_BmTxBufferArrayRamStartIdxOfBmTxBufferRomType startIdxOfBuffer = PduR_GetBmTxBufferArrayRamStartIdxOfBmTxBufferRom(bmTxBufferRomIdx, memIdx);
  PduR_BmTxBufferArrayRamEndIdxOfBmTxBufferRomType endIdxOfBuffer = PduR_GetBmTxBufferArrayRamEndIdxOfBmTxBufferRom(bmTxBufferRomIdx, memIdx);

  if(bmTxBufferArrayRamWriteIdxOfBmTxBufferRam > endIdxOfBuffer) /* COV_PDUR_EXTENDED_ERROR_CHECKS */
  {
    bmTxBufferArrayRamWriteIdxOfBmTxBufferRam = ((PduR_BmTxBufferArrayRamWriteIdxOfBmTxBufferRamType) endIdxOfBuffer) - 1u;
    PduR_ReportRuntimeDetError(PDUR_FCT_GW_BUFMGR_GET_WRITEIDX, PDUR_E_IDXOUTOFBOUNDS);
  }
  if(bmTxBufferArrayRamWriteIdxOfBmTxBufferRam < startIdxOfBuffer) /* COV_PDUR_EXTENDED_ERROR_CHECKS */
  {
    bmTxBufferArrayRamWriteIdxOfBmTxBufferRam = startIdxOfBuffer;
    PduR_ReportRuntimeDetError(PDUR_FCT_GW_BUFMGR_GET_WRITEIDX, PDUR_E_IDXOUTOFBOUNDS);
  }
# endif

  return bmTxBufferArrayRamWriteIdxOfBmTxBufferRam;
}
#endif

#if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_Get_Between_ReadIdx_WriteIdx
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
 *
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_Get_Between_ReadIdx_WriteIdx(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx,
                                                                        PduLengthType pduLength,
                                                                        CONST(SduDataPtrType, AUTOMATIC) sduDataPtr,
                                                                        PduR_MemIdxType memIdx)
{
  uint8 errorId = PDUR_E_NO_ERROR;      /* PRQA S 2981 */ /* MD_MSR_RetVal */
  PduR_BmTxBufferArrayRamReadIdxOfBmTxBufferInstanceRamType bmTxBufferArrayRamReadIdx;

  if(PduR_Bm_GetBmTxBufferArrayRamReadIdxByBmTxBufferInstanceRomIdxChecked(bmTxBufferInstanceRomIdx, &bmTxBufferArrayRamReadIdx, memIdx) == E_OK) /* SBSW_PDUR_STACK_VARIABLE */ /* COV_PDUR_ROBUSTNESS */
  {
    /* ----- Development Error Checks ------------------------------------- */
    if((bmTxBufferArrayRamReadIdx + pduLength) > PduR_Bm_GetBmTxBufferArrayRamWriteIdxOfBmTxBufferRamSafe(PduR_GetBmTxBufferRomIdxOfBmTxBufferInstanceRom(bmTxBufferInstanceRomIdx, memIdx), memIdx))   /* COV_PDUR_FATAL_ERROR */
    {
      errorId = PDUR_E_FATAL;
    }
    else
    {
      /* Dequeue Data */
      PduR_Core_MemCpyRamToRam(sduDataPtr, PduR_GetAddrBmTxBufferArrayRam(bmTxBufferArrayRamReadIdx, memIdx), pduLength);        /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_PDUR_MEM_CPY_RAM2RAM */
      PduR_SetBmTxBufferArrayRamReadIdxOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx, bmTxBufferArrayRamReadIdx + pduLength, memIdx); /* SBSW_PDUR_IDX_PARAM_INTERNAL_FUNCTION */
    }
  }
  /* ----- Development Error Report --------------------------------------- */
  # if (PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR)        /* COV_PDUR_FATAL_ERROR */
  {
    PduR_Det_ReportError(PDUR_FCT_GW_BUFMGR_GET_BETWEEN_READIDX_WRITEIDX, errorId);
  }
  # endif
  PDUR_DUMMY_STATEMENT(errorId);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}
#endif

#if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_GetData_StateHandler_BUFFER_FULL_OR_READ4WRITE
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
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_Bm_GetData_StateHandler_BUFFER_FULL_OR_READ4WRITE(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx,
                                                                                                       PduLengthType pduLength,
                                                                                                       CONST(SduDataPtrType, AUTOMATIC) sduDataPtr,
                                                                                                       PduR_MemIdxType memIdx)
{
  BufReq_ReturnType retVal = BUFREQ_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  PduR_BmTxBufferArrayRamIterType bmLinearDataSizeInstance =  PduR_Bm_GetLinearDataSizeInstance(bmTxBufferInstanceRomIdx, memIdx);
  PduR_BmTxBufferArrayRamIterType bmTotalDataSizeInstance = PduR_Bm_GetTotalDataSizeInstance(bmTxBufferInstanceRomIdx, memIdx);
  
  /* main Tx buffer element */
  if (bmLinearDataSizeInstance == pduLength)
  {
    if(bmLinearDataSizeInstance == bmTotalDataSizeInstance) /* COV_PDUR_IF_ONLY */
    {
      PduR_Bm_Get_Between_ReadIdx_EndIdx(bmTxBufferInstanceRomIdx, pduLength, sduDataPtr, memIdx);      /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
    }
    else
    {
      PduR_Bm_Get_Between_ReadIdx_EndIdx(bmTxBufferInstanceRomIdx, pduLength, sduDataPtr, memIdx);      /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
      PduR_Bm_Switch_InstanceReadIdx(bmTxBufferInstanceRomIdx, memIdx);
    }
  }
  else if(bmLinearDataSizeInstance > pduLength)
  {
    PduR_Bm_Get_Between_ReadIdx_EndIdx(bmTxBufferInstanceRomIdx, pduLength, sduDataPtr, memIdx);        /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
  }
  else if(bmTotalDataSizeInstance >= pduLength)
  {
    PduR_Bm_GetData_WithWrapAround(bmTxBufferInstanceRomIdx, pduLength, sduDataPtr, memIdx);        /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
  }
  else
  {
    retVal = BUFREQ_E_BUSY;
  }
  return retVal;
}
#endif

#if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_Get_Between_ReadIdx_EndIdx
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
 *
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_Get_Between_ReadIdx_EndIdx(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx, PduLengthType pduLength,
                                                                      CONST(SduDataPtrType, AUTOMATIC) sduDataPtr, PduR_MemIdxType memIdx)
{
  uint8 errorId = PDUR_E_NO_ERROR;      /* PRQA S 2981 */ /* MD_MSR_RetVal */
  PduR_BmTxBufferRomIdxOfBmTxBufferInstanceRomType bmTxBufferRomIdx;
  PduR_BmTxBufferArrayRamReadIdxOfBmTxBufferInstanceRamType bmTxBufferArrayRamReadIdx;

  if(PduR_Bm_GetBmTxBufferArrayRamReadIdxByBmTxBufferInstanceRomIdxChecked(bmTxBufferInstanceRomIdx, &bmTxBufferArrayRamReadIdx, memIdx) == E_OK) /* SBSW_PDUR_STACK_VARIABLE */ /* COV_PDUR_ROBUSTNESS */
  {
    /* ----- Development Error Checks ------------------------------------- */
    if((bmTxBufferArrayRamReadIdx + pduLength) > (PduR_GetBmTxBufferArrayRamEndIdxOfBmTxBufferRom(PduR_GetBmTxBufferRomIdxOfBmTxBufferInstanceRom(bmTxBufferInstanceRomIdx, memIdx), memIdx)))   /* COV_PDUR_FATAL_ERROR */
    {
      errorId = PDUR_E_FATAL;
    }
    else
    {
      /* Dequeue Data */
      PduR_Core_MemCpyRamToRam(sduDataPtr, PduR_GetAddrBmTxBufferArrayRam(bmTxBufferArrayRamReadIdx, memIdx), pduLength);        /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_PDUR_MEM_CPY_RAM2RAM */
      bmTxBufferRomIdx = PduR_GetBmTxBufferRomIdxOfBmTxBufferInstanceRom(bmTxBufferInstanceRomIdx, memIdx);

      if ((bmTxBufferArrayRamReadIdx + pduLength) == PduR_GetBmTxBufferArrayRamEndIdxOfBmTxBufferRom(bmTxBufferRomIdx, memIdx))
      {
        PduR_SetBmTxBufferArrayRamReadIdxOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx, PduR_GetBmTxBufferArrayRamStartIdxOfBmTxBufferRom(bmTxBufferRomIdx, memIdx), memIdx);       /* SBSW_PDUR_IDX_PARAM_INTERNAL_FUNCTION */
      }
      else
      {
        PduR_SetBmTxBufferArrayRamReadIdxOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx, (bmTxBufferArrayRamReadIdx + pduLength), memIdx);       /* SBSW_PDUR_IDX_PARAM_INTERNAL_FUNCTION */
      }
    }
  }
  /* ----- Development Error Report --------------------------------------- */
# if (PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR)        /* COV_PDUR_FATAL_ERROR */
  {
    PduR_Det_ReportError(PDUR_FCT_GW_BUFMGR_GET_BETWEEN_READIDX_ENDIDX, errorId);
  }
# endif
  PDUR_DUMMY_STATEMENT(errorId);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}
#endif

#if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_GetData_StateHandler_BUFFER_WRITE4READ
 *********************************************************************************************************************/
/*!
 *Internal comment removed.
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
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_Bm_GetData_StateHandler_BUFFER_WRITE4READ(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx, PduLengthType pduLength,
                                                                                               CONST(SduDataPtrType, AUTOMATIC) sduDataPtr, PduR_MemIdxType memIdx)
{
  BufReq_ReturnType retVal = BUFREQ_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  PduR_BmTxBufferArrayRamIterType bmLinearDataSizeInstance =  PduR_Bm_GetLinearDataSizeInstance(bmTxBufferInstanceRomIdx, memIdx);

  if(bmLinearDataSizeInstance >= pduLength)
  {
    PduR_Bm_Get_Between_ReadIdx_WriteIdx(bmTxBufferInstanceRomIdx, pduLength, sduDataPtr, memIdx);      /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
  }
  else
  {
    /* not enough data available */
    retVal = BUFREQ_E_BUSY;
  }
  return retVal;
}
#endif

#if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_Put_Between_WriteIdx_ReadIdx
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
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_Put_Between_WriteIdx_ReadIdx(PduR_BmTxBufferRomIterType bmTxBufferRomIdx, PduLengthType pduLength, CONST(SduDataPtrType, AUTOMATIC) sduDataPtr, PduR_MemIdxType memIdx)     /* PRQA S 3673 */ /* MD_MSR_Rule8.13 */
{
  uint8 errorId = PDUR_E_NO_ERROR;      /* PRQA S 2981 */ /* MD_MSR_RetVal */
  PduR_BmTxBufferArrayRamWriteIdxOfBmTxBufferRamType bmTxBufferArrayRamWriteIdxOfBmTxBufferRam = PduR_Bm_GetBmTxBufferArrayRamWriteIdxOfBmTxBufferRamSafe(bmTxBufferRomIdx, memIdx);

  /* ----- Development Error Checks ------------------------------------- */
  if((bmTxBufferArrayRamWriteIdxOfBmTxBufferRam + pduLength) > PduR_Bm_GetBmTxBufferArrayRamReadIdxOfBmTxBufferRam(bmTxBufferRomIdx, memIdx))      /* COV_PDUR_FATAL_ERROR */
  {
    errorId = PDUR_E_FATAL;
  }
  else
  {
    /* Enqueue Data */
    PduR_Core_MemCpyRamToRam(PduR_GetAddrBmTxBufferArrayRam(bmTxBufferArrayRamWriteIdxOfBmTxBufferRam, memIdx), sduDataPtr, pduLength);        /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_PDUR_MEM_CPY_RAM2RAM */
    PduR_SetBmTxBufferArrayRamWriteIdxOfBmTxBufferRam(bmTxBufferRomIdx, (bmTxBufferArrayRamWriteIdxOfBmTxBufferRam + pduLength), memIdx);       /* SBSW_PDUR_IDX_PARAM_INTERNAL_FUNCTION */
  }
  /* ----- Development Error Report --------------------------------------- */
# if (PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR)        /* COV_PDUR_FATAL_ERROR */
  {
    PduR_Det_ReportError(PDUR_FCT_GW_BUFMGR_PUT_BETWEEN_WRITEIDX_READIDX, errorId);
  }
# endif
  PDUR_DUMMY_STATEMENT(errorId);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}
#endif

#if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_PutData_StateHandler_BUFFER_READ4WRITE
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
 *
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_Bm_PutData_StateHandler_BUFFER_READ4WRITE(PduR_BmTxBufferRomIterType bmTxBufferRomIdx, PduLengthType pduLength,
                                                                                               CONST(SduDataPtrType, AUTOMATIC) sduDataPtr, PduR_MemIdxType memIdx)
{
  BufReq_ReturnType retVal = BUFREQ_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  PduR_BmTxBufferArrayRamIterType bmLinearBufferSize = PduR_Bm_GetLinearBufferSize(bmTxBufferRomIdx, memIdx);

  if(bmLinearBufferSize >= pduLength)
  {
    PduR_Bm_Put_Between_WriteIdx_ReadIdx(bmTxBufferRomIdx, pduLength, sduDataPtr, memIdx);       /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
  }
  else
  {
    /* Not enough free buffer space available. Tp will never request more buffer than the PDUR has provided */
    retVal = BUFREQ_E_NOT_OK;
  }
  return retVal;
}
#endif

#if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_Put_Between_WriteIdx_EndIdx
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
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_Put_Between_WriteIdx_EndIdx(PduR_BmTxBufferRomIterType bmTxBufferRomIdx, PduLengthType pduLength, CONST(SduDataPtrType, AUTOMATIC) sduDataPtr, PduR_MemIdxType memIdx)      /* PRQA S 3673 */ /* MD_MSR_Rule8.13 */
{
  uint8 errorId = PDUR_E_NO_ERROR;      /* PRQA S 2981 */ /* MD_MSR_RetVal */
  PduR_BmTxBufferArrayRamWriteIdxOfBmTxBufferRamType bmTxBufferArrayRamWriteIdxOfBmTxBufferRam = PduR_Bm_GetBmTxBufferArrayRamWriteIdxOfBmTxBufferRamSafe(bmTxBufferRomIdx, memIdx);

  /* ----- Development Error Checks ------------------------------------- */
  if((bmTxBufferArrayRamWriteIdxOfBmTxBufferRam + pduLength) > (PduR_GetBmTxBufferArrayRamEndIdxOfBmTxBufferRom(bmTxBufferRomIdx, memIdx)))     /* COV_PDUR_FATAL_ERROR */
  {
    errorId = PDUR_E_FATAL;
  }
  else
  {
    /* Enqueue Data */
    PduR_Core_MemCpyRamToRam(PduR_GetAddrBmTxBufferArrayRam(bmTxBufferArrayRamWriteIdxOfBmTxBufferRam, memIdx), sduDataPtr, pduLength);        /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_PDUR_MEM_CPY_RAM2RAM */
    PduR_SetBmTxBufferArrayRamWriteIdxOfBmTxBufferRam(bmTxBufferRomIdx, (bmTxBufferArrayRamWriteIdxOfBmTxBufferRam + pduLength), memIdx);       /* SBSW_PDUR_IDX_PARAM_INTERNAL_FUNCTION */
  }
  /* ----- Development Error Report --------------------------------------- */
# if (PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR)        /* COV_PDUR_FATAL_ERROR */
  {
    PduR_Det_ReportError(PDUR_FCT_GW_BUFMGR_PUT_BETWEEN_WRITEIDX_ENDIDX, errorId);
  }
# endif
  PDUR_DUMMY_STATEMENT(errorId);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}
#endif

#if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_Switch_WriteIdx
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
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_Switch_WriteIdx(PduR_BmTxBufferRomIterType bmTxBufferRomIdx, PduR_MemIdxType memIdx)
{
  PduR_SetBmTxBufferArrayRamWriteIdxOfBmTxBufferRam(bmTxBufferRomIdx, PduR_GetBmTxBufferArrayRamStartIdxOfBmTxBufferRom(bmTxBufferRomIdx, memIdx), memIdx);       /* SBSW_PDUR_IDX_PARAM_INTERNAL_FUNCTION */
}
#endif

#if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_Switch_InstanceReadIdx
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_Switch_InstanceReadIdx(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx, PduR_MemIdxType memIdx)
{
  /* main Tx buffer element */
  PduR_BmTxBufferRomIdxOfBmTxBufferInstanceRomType bmTxBufferRomIdx = PduR_GetBmTxBufferRomIdxOfBmTxBufferInstanceRom(bmTxBufferInstanceRomIdx, memIdx);
  PduR_SetBmTxBufferArrayRamReadIdxOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx, PduR_GetBmTxBufferArrayRamStartIdxOfBmTxBufferRom(bmTxBufferRomIdx, memIdx), memIdx);       /* SBSW_PDUR_IDX_PARAM_INTERNAL_FUNCTION */

  PDUR_DUMMY_STATEMENT(bmTxBufferRomIdx);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}
#endif

#if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_PutData_WithWrapAround
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
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_PutData_WithWrapAround(PduR_BmTxBufferRomIterType bmTxBufferRomIdx, PduLengthType pduLength, SduDataPtrType sduDataPtr, PduR_MemIdxType memIdx)
{
  PduLengthType pduLengthHead, pduLengthTail;
  /* The caller guarantees that the return value of GetLinearBufferSize is smaller than PduLengthType, otherwise a wraparound is not needed. */
  pduLengthTail = (PduLengthType) PduR_Bm_GetLinearBufferSize(bmTxBufferRomIdx, memIdx);
  pduLengthHead = pduLength - pduLengthTail;
  PduR_Bm_Put_Between_WriteIdx_EndIdx(bmTxBufferRomIdx, pduLengthTail, sduDataPtr, memIdx);      /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
  PduR_Bm_Switch_WriteIdx(bmTxBufferRomIdx, memIdx);
  PduR_Bm_Put_Between_WriteIdx_ReadIdx(bmTxBufferRomIdx, pduLengthHead, &sduDataPtr[pduLengthTail], memIdx);     /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
}
#endif

#if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_GetData_WithWrapAround
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
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_GetData_WithWrapAround(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx, PduLengthType pduLength, SduDataPtrType sduDataPtr, PduR_MemIdxType memIdx)
{
  PduLengthType pduLengthHead, pduLengthTail;
  /* The caller guarantees that the return value of GetLinearDataSizeInstance is smaller than PduLengthType, otherwise a wraparound is not needed. */
  pduLengthTail = (PduLengthType) PduR_Bm_GetLinearDataSizeInstance(bmTxBufferInstanceRomIdx, memIdx);
  pduLengthHead = pduLength - pduLengthTail;
  PduR_Bm_Get_Between_ReadIdx_EndIdx(bmTxBufferInstanceRomIdx, pduLengthTail, sduDataPtr, memIdx);        /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
  PduR_Bm_Switch_InstanceReadIdx(bmTxBufferInstanceRomIdx, memIdx);
  PduR_Bm_Get_Between_ReadIdx_WriteIdx(bmTxBufferInstanceRomIdx, pduLengthHead, &sduDataPtr[pduLengthTail], memIdx);    /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
}
#endif

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

#if(PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Bm_Init(PduR_MemIdxType memIdx)
{
  /* Init Buffer manager */
  PduR_Bm_Init_TxBuffer(memIdx);
  PduR_Bm_Init_TxBufferInstance(memIdx);
}
#endif

#if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_GetBmTxBufferArrayRamReadIdxOfBmTxBufferRam
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
PDUR_LOCAL_INLINE FUNC(PduR_BmTxBufferArrayRamReadIdxOfBmTxBufferRamType, PDUR_CODE) PduR_Bm_GetBmTxBufferArrayRamReadIdxOfBmTxBufferRam(PduR_BmTxBufferRomIterType bmTxBufferRomIdx, PduR_MemIdxType memIdx)
{
  PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx;
  PduR_BmTxBufferArrayRamReadIdxOfBmTxBufferInstanceRamType slowestInstanceReadIndex = PduR_GetBmTxBufferArrayRamStartIdxOfBmTxBufferRom(bmTxBufferRomIdx, memIdx);
  PduR_BmTxBufferArrayRamIterType maxTotalDataSizeInstance = 0;

  for(bmTxBufferInstanceRomIdx = PduR_GetBmTxBufferInstanceRomStartIdxOfBmTxBufferRom(bmTxBufferRomIdx, memIdx);
      bmTxBufferInstanceRomIdx < PduR_GetBmTxBufferInstanceRomEndIdxOfBmTxBufferRom(bmTxBufferRomIdx, memIdx); bmTxBufferInstanceRomIdx++)
  {
    PduR_BmTxBufferArrayRamReadIdxOfBmTxBufferInstanceRamType bmTxBufferArrayRamReadIdx = 0;

    if(PduR_Bm_GetBmTxBufferArrayRamReadIdxByBmTxBufferInstanceRomIdxChecked(bmTxBufferInstanceRomIdx, &bmTxBufferArrayRamReadIdx, memIdx) == E_OK) /* PRQA S 2991 */ /* MD_PduR_2991 */ /* COV_PDUR_IF_ONLY */ /* SBSW_PDUR_STACK_VARIABLE */
    {
      PduR_BmTxBufferArrayRamIterType bmTotalDataSizeInstance = PduR_Bm_GetTotalDataSizeInstance(bmTxBufferInstanceRomIdx, memIdx);

      if(bmTotalDataSizeInstance >= maxTotalDataSizeInstance) /* COV_PDUR_IF_ONLY */
      {
        maxTotalDataSizeInstance = bmTotalDataSizeInstance;   /* PRQA S 2983 */ /* MD_PduR_2983 */
        slowestInstanceReadIndex = bmTxBufferArrayRamReadIdx; /* maximum amount of data -> slowest read instance */
      }
    }
  }
  return slowestInstanceReadIndex;
}
#endif

#if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_GetPduRBufferStateOfBmTxBufferInstanceRam
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
FUNC(PduR_PduRBufferStateOfBmTxBufferInstanceRamType, PDUR_CODE) PduR_Bm_GetPduRBufferStateOfBmTxBufferInstanceRam(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx,
                                                                                                                   PduR_BmTxBufferArrayRamReadIdxOfBmTxBufferInstanceRamType bmTxBufferArrayRamReadIdx,
                                                                                                                   PduR_MemIdxType memIdx)
{
  PduR_PduRBufferStateOfBmTxBufferInstanceRamType retVal;

  PduR_BmTxBufferRomIdxOfBmTxBufferInstanceRomType bmTxBufferRomIdx = PduR_GetBmTxBufferRomIdxOfBmTxBufferInstanceRom(bmTxBufferInstanceRomIdx, memIdx);
  PduR_BmTxBufferArrayRamWriteIdxOfBmTxBufferRamType bmTxBufferArrayRamWriteIdx = PduR_Bm_GetBmTxBufferArrayRamWriteIdxOfBmTxBufferRamSafe(bmTxBufferRomIdx, memIdx);
  PduR_BmTxBufferArrayRamStartIdxOfBmTxBufferRomType bmTxBufferArrayRamStartIdx = PduR_GetBmTxBufferArrayRamStartIdxOfBmTxBufferRom(bmTxBufferRomIdx, memIdx);

  if(bmTxBufferArrayRamReadIdx == bmTxBufferArrayRamWriteIdx)
  {
    retVal = PDUR_BUFFER_EMPTY_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM;
  }
  else if (bmTxBufferArrayRamReadIdx == (bmTxBufferArrayRamWriteIdx + 1u))
  {
    retVal = PDUR_BUFFER_FULL_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM;
  }
  else if ((bmTxBufferArrayRamStartIdx == bmTxBufferArrayRamReadIdx) && (PduR_Bm_GetInboundBmTxBufferArrayEndIdxOfBmTxBuffer(bmTxBufferRomIdx, memIdx) == bmTxBufferArrayRamWriteIdx))
  {
    retVal = PDUR_BUFFER_FULL_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM;
  }
  else if (bmTxBufferArrayRamReadIdx > bmTxBufferArrayRamWriteIdx)
  {
    retVal = PDUR_BUFFER_READ4WRITE_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM;
  }
  else /* (bmTxBufferArrayRamReadIdx < bmTxBufferArrayRamWriteIdx) */
  {
    retVal = PDUR_BUFFER_WRITE4READ_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM;
  }

  return retVal;
}
# endif

#if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_GetPduRBufferStateOfBmTxBufferRam
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
FUNC(PduR_PduRBufferStateOfBmTxBufferRamType, PDUR_CODE) PduR_Bm_GetPduRBufferStateOfBmTxBufferRam (PduR_BmTxBufferRomIterType bmTxBufferRomIdx, PduR_MemIdxType memIdx)
    {
      PduR_PduRBufferStateOfBmTxBufferRamType retVal;

      PduR_BmTxBufferArrayRamWriteIdxOfBmTxBufferRamType bmTxBufferArrayRamWriteIdx = PduR_Bm_GetBmTxBufferArrayRamWriteIdxOfBmTxBufferRamSafe(bmTxBufferRomIdx, memIdx);
      PduR_BmTxBufferArrayRamReadIdxOfBmTxBufferInstanceRamType bmTxBufferArrayRamReadIdx = PduR_Bm_GetBmTxBufferArrayRamReadIdxOfBmTxBufferRam(bmTxBufferRomIdx, memIdx);
      PduR_BmTxBufferArrayRamStartIdxOfBmTxBufferRomType bmTxBufferArrayRamStartIdx = PduR_GetBmTxBufferArrayRamStartIdxOfBmTxBufferRom(bmTxBufferRomIdx, memIdx);

      if(bmTxBufferArrayRamReadIdx == bmTxBufferArrayRamWriteIdx)
      {
        retVal = PDUR_BUFFER_EMPTY_PDURBUFFERSTATEOFBMTXBUFFERRAM;
      }
      else if (bmTxBufferArrayRamReadIdx == (bmTxBufferArrayRamWriteIdx + 1u))
      {
        retVal = PDUR_BUFFER_FULL_PDURBUFFERSTATEOFBMTXBUFFERRAM;
      }
      else if ((bmTxBufferArrayRamStartIdx == bmTxBufferArrayRamReadIdx) && (PduR_Bm_GetInboundBmTxBufferArrayEndIdxOfBmTxBuffer(bmTxBufferRomIdx, memIdx) == bmTxBufferArrayRamWriteIdx))
      {
        retVal = PDUR_BUFFER_FULL_PDURBUFFERSTATEOFBMTXBUFFERRAM;
      }
      else if (bmTxBufferArrayRamReadIdx > bmTxBufferArrayRamWriteIdx)
      {
        retVal = PDUR_BUFFER_READ4WRITE_PDURBUFFERSTATEOFBMTXBUFFERRAM;
      }
      else /* (bmTxBufferArrayRamReadIdx < bmTxBufferArrayRamWriteIdx) */
      {
        retVal = PDUR_BUFFER_WRITE4READ_PDURBUFFERSTATEOFBMTXBUFFERRAM;
      }

      return retVal;
    }
# endif

#if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_PutData
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_Bm_PutData(PduR_BmTxBufferRomIterType bmTxBufferRomIdx, PduLengthType pduLength, CONST(SduDataPtrType, AUTOMATIC) sduDataPtr, PduR_MemIdxType memIdx)
{
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  switch (PduR_Bm_GetPduRBufferStateOfBmTxBufferRam(bmTxBufferRomIdx, memIdx))
  {
    case PDUR_BUFFER_EMPTY_PDURBUFFERSTATEOFBMTXBUFFERRAM:
    case PDUR_BUFFER_WRITE4READ_PDURBUFFERSTATEOFBMTXBUFFERRAM:
    {
      retVal = PduR_Bm_PutData_StateHandler_BUFFER_EMPTY_OR_WRITE4READ(bmTxBufferRomIdx, pduLength, sduDataPtr, memIdx);      /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
      break;
    }
    case PDUR_BUFFER_READ4WRITE_PDURBUFFERSTATEOFBMTXBUFFERRAM:
    {
      retVal = PduR_Bm_PutData_StateHandler_BUFFER_READ4WRITE(bmTxBufferRomIdx, pduLength, sduDataPtr, memIdx);       /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
      break;
    }
    case PDUR_BUFFER_FULL_PDURBUFFERSTATEOFBMTXBUFFERRAM:
    {
      if(pduLength == 0u)
      {
        retVal = BUFREQ_OK;
      }
      break;
    }
    default:   /* COV_PDUR_MISRA */
      break;
  }

  return retVal;
}
#endif

#if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_PutDataAsPtr
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_Bm_PutDataAsPtr(PduR_BmTxBufferRomIterType bmTxBufferRomIdx, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, PduR_MemIdxType memIdx)      /* COV_PDUR_IF_ONLY */
{
  info->SduDataPtr = PduR_GetAddrBmTxBufferArrayRam(PduR_Bm_GetBmTxBufferArrayRamWriteIdxOfBmTxBufferRamSafe(bmTxBufferRomIdx, memIdx), memIdx);      /* SBSW_PDUR_STACK_VARIABLE */
  info->SduLength = (PduLengthType) PduR_Bm_GetLinearBufferSize(bmTxBufferRomIdx, memIdx);    /* SBSW_PDUR_STACK_VARIABLE */
  return PduR_Bm_PutData(bmTxBufferRomIdx, info->SduLength, info->SduDataPtr, memIdx);        /* SBSW_PDUR_STACK_VARIABLE */
}
#endif

#if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_ResetTxBuffer
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
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Bm_ResetTxBuffer(PduR_BmTxBufferRomIterType bmTxBufferRomIdx, PduR_MemIdxType memIdx)
{
  PduR_SetRxLengthOfBmTxBufferRam(bmTxBufferRomIdx, 0u, memIdx);   /* SBSW_PDUR_CSL01 */
  PduR_SetAllocatedOfBmTxBufferRam(bmTxBufferRomIdx, FALSE, memIdx); /* SBSW_PDUR_CSL01 */
  PduR_SetBmTxBufferArrayRamWriteIdxOfBmTxBufferRam(bmTxBufferRomIdx, (PduR_GetBmTxBufferArrayRamStartIdxOfBmTxBufferRom(bmTxBufferRomIdx, memIdx)), memIdx);     /* SBSW_PDUR_IDX_PARAM_INTERNAL_FUNCTION */
}
#endif

#if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
  PduR_Bm_ResetTxBufferInstance
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
  *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Bm_ResetTxBufferInstance(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx, PduR_MemIdxType memIdx)
{
  PduR_SetBmTxBufferArrayRamReadIdxOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx, PDUR_NO_BMTXBUFFERARRAYRAMREADIDXOFBMTXBUFFERINSTANCERAM, memIdx); /* SBSW_PDUR_IDX_PARAM_INTERNAL_FUNCTION */ /* PRQA S 2841 */ /* MD_PduR_2841 */
}
#endif

#if ((PDUR_BMTXBUFFERRAM == STD_ON) && (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON))
/**********************************************************************************************************************
 * PduR_Bm_GetTotalDataSize
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(PduR_BmTxBufferArrayRamIterType, PDUR_CODE) PduR_Bm_GetTotalDataSize(PduR_BmTxBufferRomIterType bmTxBufferRomIdx, PduR_MemIdxType memIdx) /* PRQA S 1505 */ /* MD_PduR_1505 */
{
  PduR_BmTxBufferArrayRamIterType retVal = 0u;  /* PRQA S 2981 */ /* MD_MSR_RetVal */
  PduR_BmTxBufferArrayRamReadIdxOfBmTxBufferRamType bmTxBufferArrayRamReadIdxOfBmTxBufferRam = PduR_Bm_GetBmTxBufferArrayRamReadIdxOfBmTxBufferRam(bmTxBufferRomIdx, memIdx);

  switch (PduR_Bm_GetPduRBufferStateOfBmTxBufferRam(bmTxBufferRomIdx, memIdx))
  {
    case PDUR_BUFFER_WRITE4READ_PDURBUFFERSTATEOFBMTXBUFFERRAM:        /* COV_PDUR_BUFFER_CALCULATION */
    {
      retVal = ((PduR_BmTxBufferArrayRamIterType) PduR_Bm_GetBmTxBufferArrayRamWriteIdxOfBmTxBufferRamSafe(bmTxBufferRomIdx, memIdx)) - bmTxBufferArrayRamReadIdxOfBmTxBufferRam;
      break;
    }
    case PDUR_BUFFER_READ4WRITE_PDURBUFFERSTATEOFBMTXBUFFERRAM: /* COV_PDUR_BUFFER_CALCULATION */
    {
      retVal = ((PduR_BmTxBufferArrayRamIterType) PduR_GetBmTxBufferArrayRamLengthOfBmTxBufferRom(bmTxBufferRomIdx, memIdx)) - 
               ((PduR_BmTxBufferArrayRamIterType) bmTxBufferArrayRamReadIdxOfBmTxBufferRam - PduR_Bm_GetBmTxBufferArrayRamWriteIdxOfBmTxBufferRamSafe(bmTxBufferRomIdx, memIdx));
      break;
    }
    case PDUR_BUFFER_FULL_PDURBUFFERSTATEOFBMTXBUFFERRAM:
    {
      retVal = PduR_Bm_GetLengthOfBmTxBuffer(bmTxBufferRomIdx, memIdx);
      break;
    }
    case PDUR_BUFFER_EMPTY_PDURBUFFERSTATEOFBMTXBUFFERRAM:
    {
      retVal = 0u;
      break;
    }
    default:   /* COV_PDUR_MISRA */
      break;
  }
  return retVal;
}
#endif

#if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_GetLinearDataSizeInstance
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(PduR_BmTxBufferArrayRamIterType, PDUR_CODE) PduR_Bm_GetLinearDataSizeInstance(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx, PduR_MemIdxType memIdx) /* PRQA S 1505 */ /* MD_PduR_1505 */
{
  PduR_BmTxBufferArrayRamIterType retVal = 0u;  /* PRQA S 2981 */ /* MD_MSR_RetVal */
  PduR_BmTxBufferRomIterType bmTxBufferRomIdx = PduR_GetBmTxBufferRomIdxOfBmTxBufferInstanceRom(bmTxBufferInstanceRomIdx, memIdx);
  PduR_BmTxBufferArrayRamReadIdxOfBmTxBufferInstanceRamType bmTxBufferArrayRamReadIdx;

  if(PduR_Bm_GetBmTxBufferArrayRamReadIdxByBmTxBufferInstanceRomIdxChecked(bmTxBufferInstanceRomIdx, &bmTxBufferArrayRamReadIdx, memIdx) == E_OK) /* SBSW_PDUR_STACK_VARIABLE */ /* COV_PDUR_ROBUSTNESS */
  {
    switch (PduR_Bm_GetPduRBufferStateOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx, bmTxBufferArrayRamReadIdx, memIdx))
    {
      case PDUR_BUFFER_WRITE4READ_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM:
      {
        retVal = ((PduR_BmTxBufferArrayRamIterType) PduR_Bm_GetBmTxBufferArrayRamWriteIdxOfBmTxBufferRamSafe(bmTxBufferRomIdx, memIdx)) - bmTxBufferArrayRamReadIdx;
        break;
      }
      case PDUR_BUFFER_READ4WRITE_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM:
      {
        retVal = ((PduR_BmTxBufferArrayRamIterType) PduR_GetBmTxBufferArrayRamEndIdxOfBmTxBufferRom(bmTxBufferRomIdx, memIdx)) - bmTxBufferArrayRamReadIdx;
        break;
      }
      case PDUR_BUFFER_FULL_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM:
      {
        if ((PduR_Bm_GetBmTxBufferArrayRamWriteIdxOfBmTxBufferRamSafe(bmTxBufferRomIdx, memIdx) + 1u) == bmTxBufferArrayRamReadIdx)
        {/* first full condition */
          retVal = ((PduR_BmTxBufferArrayRamIterType) PduR_GetBmTxBufferArrayRamEndIdxOfBmTxBufferRom(bmTxBufferRomIdx, memIdx)) - bmTxBufferArrayRamReadIdx;
        }
        else
        {/* second full condition */
          retVal = PduR_Bm_GetLengthOfBmTxBuffer(bmTxBufferRomIdx, memIdx);
        }
        break;
      }
      case PDUR_BUFFER_EMPTY_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM:     /* COV_PDUR_BUFFER_CALCULATION */
      {
        retVal = 0u;
        break;
      }
      default:   /* COV_PDUR_MISRA */
        break;
    }
  }
  return retVal;
}
#endif

#if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_GetBmTxBufferArrayRamReadIdxByBmTxBufferInstanceRomIdxChecked
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_Bm_GetBmTxBufferArrayRamReadIdxByBmTxBufferInstanceRomIdxChecked(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx,
                                                                                                                   PduR_BmTxBufferArrayRamReadIdxOfBmTxBufferInstanceRamType* bmTxBufferArrayRamReadIdx,
                                                                                                                   PduR_MemIdxType memIdx)
{
  Std_ReturnType retVal;
  PduR_BmTxBufferArrayRamReadIdxOfBmTxBufferInstanceRamType readBmTxBufferArrayRamReadIdx = PduR_Bm_GetBmTxBufferArrayRamReadIdxOfBmTxBufferInstanceRamSafe(bmTxBufferInstanceRomIdx, memIdx);

  if (readBmTxBufferArrayRamReadIdx == PDUR_NO_BMTXBUFFERARRAYRAMREADIDXOFBMTXBUFFERINSTANCERAM)
  {
    retVal = E_NOT_OK;
  }
  else
  {
    *bmTxBufferArrayRamReadIdx = readBmTxBufferArrayRamReadIdx; /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
    retVal = E_OK;
  }

  return retVal;
}
#endif

#if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_GetTotalBufferSize
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(PduR_BmTxBufferArrayRamIterType, PDUR_CODE) PduR_Bm_GetTotalBufferSize(PduR_BmTxBufferRomIterType bmTxBufferRomIdx, PduR_MemIdxType memIdx)        /* PRQA S 1505 */ /* MD_PduR_1505 */
{
  PduR_BmTxBufferArrayRamIterType retVal = 0u;  /* PRQA S 2981 */ /* MD_MSR_RetVal */

  switch (PduR_Bm_GetPduRBufferStateOfBmTxBufferRam(bmTxBufferRomIdx, memIdx))
  {
    case PDUR_BUFFER_WRITE4READ_PDURBUFFERSTATEOFBMTXBUFFERRAM:
    {
      retVal = ((PduR_BmTxBufferArrayRamIterType) PduR_Bm_GetLengthOfBmTxBuffer(bmTxBufferRomIdx, memIdx)) - (((PduR_BmTxBufferArrayRamIterType) PduR_Bm_GetBmTxBufferArrayRamWriteIdxOfBmTxBufferRamSafe(bmTxBufferRomIdx, memIdx)) - PduR_Bm_GetBmTxBufferArrayRamReadIdxOfBmTxBufferRam(bmTxBufferRomIdx, memIdx));
      break;
    }
    case PDUR_BUFFER_READ4WRITE_PDURBUFFERSTATEOFBMTXBUFFERRAM:        /* COV_PDUR_BUFFER_CALCULATION */
    {
      retVal = ((PduR_BmTxBufferArrayRamIterType) PduR_Bm_GetBmTxBufferArrayRamReadIdxOfBmTxBufferRam(bmTxBufferRomIdx, memIdx)) - (PduR_Bm_GetBmTxBufferArrayRamWriteIdxOfBmTxBufferRamSafe(bmTxBufferRomIdx, memIdx) - ((PduR_BmTxBufferArrayRamIterType) 1u));
      break;
    }
    case PDUR_BUFFER_FULL_PDURBUFFERSTATEOFBMTXBUFFERRAM:      /* COV_PDUR_BUFFER_CALCULATION */
    {
      retVal = 0u;
      break;
    }
    case PDUR_BUFFER_EMPTY_PDURBUFFERSTATEOFBMTXBUFFERRAM:
    {
      retVal = PduR_Bm_GetLengthOfBmTxBuffer(bmTxBufferRomIdx, memIdx);
      break;
    }
    default:   /* COV_PDUR_MISRA */
      break;
  }
  return retVal;
}
#endif

#if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_GetTotalDataSizeInstance
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(PduR_BmTxBufferArrayRamIterType, PDUR_CODE) PduR_Bm_GetTotalDataSizeInstance(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx, PduR_MemIdxType memIdx)  /* PRQA S 1505 */ /* MD_PduR_1505 */
{
  PduR_BmTxBufferArrayRamIterType retVal = 0u;  /* PRQA S 2981 */ /* MD_MSR_RetVal */
  PduR_BmTxBufferRomIterType bmTxBufferRomIdx = PduR_GetBmTxBufferRomIdxOfBmTxBufferInstanceRom(bmTxBufferInstanceRomIdx, memIdx);
  PduR_BmTxBufferArrayRamReadIdxOfBmTxBufferInstanceRamType bmTxBufferArrayRamReadIdx = PduR_Bm_GetBmTxBufferArrayRamReadIdxOfBmTxBufferInstanceRamSafe(bmTxBufferInstanceRomIdx, memIdx);

  if(PduR_Bm_GetBmTxBufferArrayRamReadIdxByBmTxBufferInstanceRomIdxChecked(bmTxBufferInstanceRomIdx, &bmTxBufferArrayRamReadIdx, memIdx) == E_OK) /* COV_PDUR_ROBUSTNESS */ /* SBSW_PDUR_STACK_VARIABLE */
  {
    switch (PduR_Bm_GetPduRBufferStateOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx, bmTxBufferArrayRamReadIdx, memIdx))
    {
      case PDUR_BUFFER_WRITE4READ_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM:        /* COV_PDUR_BUFFER_CALCULATION */
      {
        retVal = ((PduR_BmTxBufferArrayRamIterType) PduR_Bm_GetBmTxBufferArrayRamWriteIdxOfBmTxBufferRamSafe(bmTxBufferRomIdx, memIdx)) - bmTxBufferArrayRamReadIdx;
        break;
      }
      case PDUR_BUFFER_READ4WRITE_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM:
      {
          retVal =
            ((PduR_BmTxBufferArrayRamIterType) PduR_GetBmTxBufferArrayRamLengthOfBmTxBufferRom(PduR_GetBmTxBufferRomIdxOfBmTxBufferInstanceRom(bmTxBufferInstanceRomIdx, memIdx), memIdx)) -
            (((PduR_BmTxBufferArrayRamIterType) bmTxBufferArrayRamReadIdx) - PduR_Bm_GetBmTxBufferArrayRamWriteIdxOfBmTxBufferRamSafe(bmTxBufferRomIdx, memIdx));
        break;
      }
      case PDUR_BUFFER_FULL_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM:
      {
        retVal = PduR_Bm_GetLengthOfBmTxBuffer(PduR_GetBmTxBufferRomIdxOfBmTxBufferInstanceRom(bmTxBufferInstanceRomIdx, memIdx), memIdx);
        break;
      }
      case PDUR_BUFFER_EMPTY_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM:     /* COV_PDUR_BUFFER_CALCULATION */
      {
        retVal = 0u;
        break;
      }
      default:   /* COV_PDUR_MISRA */
        break;
    }
  }
  return retVal;
}
#endif

#if (PDUR_BMTXBUFFERRAM == STD_ON )
/**********************************************************************************************************************
 * PduR_Bm_AllocateTxBuffer
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
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_Bm_AllocateTxBuffer(PduR_FmFifoRomIterType fmFifoRomIdx,
                                                            PduLengthType pduLength,
                                                            PduLengthType optimalBufferSize,
                                                            PduLengthType minimumBufferSize,
                                                            P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr,
                                                            P2VAR(PduR_BmTxBufferRomIdxOfBmTxBufferIndRomType, AUTOMATIC, PDUR_APPL_DATA) allocatedTxBufferIdxPtr,
                                                            PduR_MemIdxType memIdx)
{
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  /* Get the assigned FifoElement */
  PduR_BmTxBufferRomIdxOfBmTxBufferIndRomType lastSuitableBmTxBufferRomIdx = 0u; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  boolean lastSuitableBmTxBufferRomIdxFound = FALSE;
  PduR_BmTxBufferIndRomIterType bmTxBufferRomIndIdx;

  {
    PduR_BmTxBufferIndRomIterType bmTxBufferRomIndStartId = PduR_GetBmTxBufferIndRomStartIdxOfFmFifoRom(fmFifoRomIdx, memIdx);
    PduR_BmTxBufferIndRomIterType bmTxBufferRomIndEndIdx = PduR_GetBmTxBufferIndRomEndIdxOfFmFifoRom(fmFifoRomIdx, memIdx);

# if (PDUR_LOCKROMUSEDOFFMFIFOROM == STD_ON)
    PduR_Lock_LockBuffersByFmFifo(fmFifoRomIdx, memIdx);
# endif
    {
      for(bmTxBufferRomIndIdx = bmTxBufferRomIndStartId; bmTxBufferRomIndIdx < bmTxBufferRomIndEndIdx; bmTxBufferRomIndIdx++) /* COV_PDUR_ONLY_SHARED_OR_DEDICATED_BUFFER */
      {
        PduR_BmTxBufferRomIdxOfBmTxBufferIndRomType bmTxBufferRomIdx = PduR_GetBmTxBufferRomIdxOfBmTxBufferIndRom(bmTxBufferRomIndIdx, memIdx);
        /* Buffer available? */
        if(!PduR_IsAllocatedOfBmTxBufferRam(bmTxBufferRomIdx, memIdx)) /* COV_PDUR_ONLY_SHARED_OR_DEDICATED_BUFFER */
        {
          if(PduR_Bm_GetLengthOfBmTxBuffer(bmTxBufferRomIdx, memIdx) >= (PduR_BmTxBufferArrayRamIterType) optimalBufferSize) /* COV_PDUR_IF_SDU_LENGTH_HANDLING */
          {
            /* Initialize buffer and assign to FifoElement */
            PduR_SetAllocatedOfBmTxBufferRam(bmTxBufferRomIdx, TRUE, memIdx);     /* SBSW_PDUR_CSL03 */
            PduR_SetRxLengthOfBmTxBufferRam(bmTxBufferRomIdx, pduLength, memIdx); /* SBSW_PDUR_CSL03 */
            *allocatedTxBufferIdxPtr = bmTxBufferRomIdx; /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
            /* Assign amount of available buffer */
            *bufferSizePtr = (PduLengthType) PduR_Bm_GetLengthOfBmTxBuffer(bmTxBufferRomIdx, memIdx); /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
            retVal = BUFREQ_OK;
            break;
          }
          else if(PduR_Bm_GetLengthOfBmTxBuffer(bmTxBufferRomIdx, memIdx) >= (PduR_BmTxBufferArrayRamIterType) minimumBufferSize) /* COV_PDUR_MISRA */
          {
            /* This buffer is not large enough to hold the complete message but the buffer is available and could be used in case no other buffer is available. Reason: the buffer is large enough to hold at least one tpChunk. */
            lastSuitableBmTxBufferRomIdx = bmTxBufferRomIdx; /* PRQA S 2983 */ /* MD_PduR_2983 */
            lastSuitableBmTxBufferRomIdxFound = TRUE;        /* PRQA S 2983 */ /* MD_PduR_2983 */
          }
          else
          {
            /* nothing to be done */
          }
        }
      }
      /* No suitable buffer found which is large enough to store the full TP PDU. Use ring buffer mechanism (routing-on-the-fly) instead. */
      if(retVal != BUFREQ_OK) /* COV_PDUR_IF_SDU_LENGTH_HANDLING */
      {
        /* The received TP PDU is larger than the largest available TP buffer element. The routing is executed using a ring buffer mechanism (routing on the fly) that allows a smaller receive buffer. */
        if(lastSuitableBmTxBufferRomIdxFound == TRUE) /* COV_PDUR_IF_SDU_LENGTH_HANDLING */
        {
          /* Routing is possible, but the gateway will use the ring-buffer mechanism to perform routing. Routing must not be 1:N routing. */
          /* Initialize buffer and assign to FifoElement */
          PduR_SetAllocatedOfBmTxBufferRam(lastSuitableBmTxBufferRomIdx, TRUE, memIdx);     /* SBSW_PDUR_CSL03 */
          PduR_SetRxLengthOfBmTxBufferRam(lastSuitableBmTxBufferRomIdx, pduLength, memIdx); /* SBSW_PDUR_CSL03 */
          *allocatedTxBufferIdxPtr = lastSuitableBmTxBufferRomIdx; /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
          /* Assign amount of available buffer */
          *bufferSizePtr = (PduLengthType) PduR_Bm_GetTotalBufferSize(lastSuitableBmTxBufferRomIdx, memIdx); /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
          retVal = BUFREQ_OK;
        }
        else
        {
          /* Currently no buffer is available that would allow routing of a routing relation with the configured chunk size. 1:N routing relations can only be routed if a buffer of the I-PDU size is available. 1:1 routing relation can be routed principally but not at the current time. Prevented by validation! */
          retVal = BUFREQ_E_NOT_OK;
        }
      }
    }
# if (PDUR_LOCKROMUSEDOFFMFIFOROM == STD_ON)
    PduR_Lock_UnlockBuffersByFmFifo(fmFifoRomIdx, memIdx);
# endif
  }
  return retVal;
}       /* PRQA S 6060, 6080 */ /* MD_MSR_STPAR, MD_MSR_STMIF */
#endif

#if (PDUR_BMTXBUFFERRAM == STD_ON )
/**********************************************************************************************************************
 * PduR_Bm_CopyDataAsPtr
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Bm_CopyDataAsPtr(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, PduR_BmTxBufferArrayRamIterType length, PduR_MemIdxType memIdx)    /* COV_PDUR_ONLY_TT_SINGLE_BUFFER */
{
  PduR_BmTxBufferArrayRamIterType bmLinearDataSizeInstance;
  PduR_BmTxBufferArrayRamReadIdxOfBmTxBufferInstanceRamType bmTxBufferArrayRamReadIdx;

  if(PduR_Bm_GetBmTxBufferArrayRamReadIdxByBmTxBufferInstanceRomIdxChecked(bmTxBufferInstanceRomIdx, &bmTxBufferArrayRamReadIdx, memIdx) == E_OK) /* SBSW_PDUR_STACK_VARIABLE */ /* COV_PDUR_ROBUSTNESS */
  {
    info->SduDataPtr = PduR_GetAddrBmTxBufferArrayRam(bmTxBufferArrayRamReadIdx, memIdx);        /* SBSW_PDUR_STACK_VARIABLE */
    bmLinearDataSizeInstance = PduR_Bm_GetLinearDataSizeInstance(bmTxBufferInstanceRomIdx, memIdx);

    if(length > bmLinearDataSizeInstance)      /* COV_PDUR_ROBUSTNESS */
    {
      info->SduLength = (PduLengthType) bmLinearDataSizeInstance;      /* SBSW_PDUR_STACK_VARIABLE */
    }
    else
    {
      info->SduLength = (PduLengthType) length;   /* SBSW_PDUR_STACK_VARIABLE */
    }
  }
}
#endif

#if (PDUR_BMTXBUFFERRAM == STD_ON )
/**********************************************************************************************************************
 * PduR_Bm_GetActualPduLengthToBeRouted
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(PduLengthType, PDUR_CODE) PduR_Bm_GetActualPduLengthToBeRouted(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx, PduR_MemIdxType memIdx)     /* COV_PDUR_IF_ONLY */
{
  return PduR_GetRxLengthOfBmTxBufferRam(PduR_GetBmTxBufferRomIdxOfBmTxBufferInstanceRom(bmTxBufferInstanceRomIdx, memIdx), memIdx);
}

#endif

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h" /* PRQA S 5087 */   /* MD_MSR_MemMap */

/**********************************************************************************************************************
 * GLOBAL MISRA / PCLINT JUSTIFICATION
 *********************************************************************************************************************/
/* *INDENT-OFF* */

/* module specific MISRA deviations:
     MD_PduR_2841: Dereference of an invalid pointer value.
     Reason:       QAC cannot determine whether the pointer value is correct. The callers of this function guarantee, that the index is always in bound.
     Risk:         No risk.
     Prevention:   No prevention necessary.
*/

/* *INDENT-ON* */
/**********************************************************************************************************************
 *  END OF FILE: PduR_Bm.c
 *********************************************************************************************************************/
