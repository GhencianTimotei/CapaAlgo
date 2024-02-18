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
 *         File:  PduR_Fm.h
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
# if !defined (PDUR_FM_H)
# define PDUR_FM_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "PduR_Types.h"
# include "PduR_Cfg.h"
# include "PduR_Lcfg.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define PDUR_START_SEC_CODE
# include "PduR_MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

# if(PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_Init
 *********************************************************************************************************************/
/*! \brief      This function initializes the FifoManager Ram Variables
 *  \details    -
 *   \param[in]  memIdx  memory section index
 *  \pre         PduR_InitMemory() has been executed, if the start up code does not initialize variables.
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \note       The function must be called on task level and has not to be interrupted.
 *              by other administrative function calls.
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Fm_Init(PduR_MemIdxType memIdx);
# endif

# if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_Peek
 *********************************************************************************************************************/
/*!  \brief       Helper function which checks if any routing is ready to transmit in the FIFO
 *   \details     no dequeuing.
 *   \param[in]   fmFifoRamIdx        Index of the destination FIFO.
 *   \param[in]   fmFifoElementRamIdx Index of the current element which is used by the routing.
 *   \param[in]   memIdx              memory section index
 *   \return      E_OK     if a routing is waiting for transmission.
 *                E_NOT_OK FIFO is empty
 *   \pre         -
 *   \context     TASK|ISR1|ISR2
 *   \reentrant   TRUE
 *   \synchronous TRUE
***********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_Fm_Peek(PduR_FmFifoRamIterType fmFifoRamIdx, P2VAR(PduR_FmFifoElementRamIterType, AUTOMATIC, PDUR_APPL_DATA) fmFifoElementRamIdx, PduR_MemIdxType memIdx);
# endif

# if (PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_AssignTxBuffer2FifoElement
 *********************************************************************************************************************/
/*! \brief       Assign the element from the buffer pool.
 *  \details     -
 *  \param[in]   fmFifoElementRamWriteIdx  Current write FIFO Idx.
 *  \param[in]   bmTxBufferRomIdx Tx Buffer Idx.
 *  \param[in]   memIdx  memory section index
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Fm_AssignTxBuffer2FifoElement(PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx, PduR_BmTxBufferRomIdxOfFmFifoElementRamType bmTxBufferRomIdx, PduR_MemIdxType memIdx);
# endif

# if (PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_IncrementReadIndex
 *********************************************************************************************************************/
/*! \brief       This function is called to increment the read index of the FIFO.
 *  \details     It also handles the wrap-around and the fill level.
 *  \param[in]   fmFifoRamIdx        Index of the destination FIFO.
 *  \param[in]   memIdx              memory section index
 *  \return                          the new read index
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(PduR_FmFifoElementRamIterType, PDUR_CODE) PduR_Fm_IncrementReadIndex(PduR_FmFifoRamIterType fmFifoRamIdx, PduR_MemIdxType memIdx);
# endif

# if (PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_IncrementWriteIndex
 *********************************************************************************************************************/
/*! \brief       This function is called to increment the write index of the FIFO.
 *  \details     It also handles the wrap-around.
 *  \param[in]   fmFifoRamIdx        Index of the destination FIFO.
 *  \param[in]   memIdx              memory section index
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Fm_IncrementWriteIndex(PduR_FmFifoRamIterType fmFifoRamIdx, PduR_MemIdxType memIdx);
# endif

# if (PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_GetFmFifoElementRamReadIdxOfFmFifoRamSafe
 *********************************************************************************************************************/
/*! \brief       This gets the read Idx of the fifo
 *  \details     -
 *  \param[in]   fmFifoRamIdx        Index of the destination FIFO.
 *  \param[in]   memIdx              memory section index
 *  \return                          the read index
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(PduR_FmFifoElementRamReadIdxOfFmFifoRamType, PDUR_CODE) PduR_Fm_GetFmFifoElementRamReadIdxOfFmFifoRamSafe(PduR_FmFifoRamIterType fmFifoRamIdx, PduR_MemIdxType memIdx);
# endif

# if (PDUR_EXISTS_SHARED_FIFO_QUEUE_IMPLEMENTATIONTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_PutFifo
 *********************************************************************************************************************/
/*! \brief      This function writes the Pdu to the Fifo
 *  \details    -
 *  \param[in]  rmDest               routing manager indirection Idx.
 *  \param[in]  rmGDest              routing manager indirection Idx to global destination Pdu table.
 *  \param[in]  pduLength            length to copy.
 *  \param[in]  sduDataPtr           data pointer.
 *  \pre        -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_Fm_PutFifo(PduR_RmGDestRomIterType rmGDest, PduR_RmDestRomIterType rmDest, PduLengthType pduLength, SduDataPtrType sduDataPtr);
#endif

# if (PDUR_EXISTS_SHARED_FIFO_QUEUE_IMPLEMENTATIONTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_RemoveElement
 *********************************************************************************************************************/
/*! \brief       Remove the oldest element from the queue
 *  \details     -
 *  \param[in]   rmGDestRomIdx         global destination Pdu Idx.
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Fm_RemoveElement(PduR_RmGDestRomIterType rmGDestRomIdx);
#endif

# if (PDUR_EXISTS_SHARED_FIFO_QUEUE_IMPLEMENTATIONTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_GetNextElement
 *********************************************************************************************************************/
/*! \brief       Get the next element from the queue if available
 *  \details     -
 *  \param[in]   rmGDestRomIdx       global destination Pdu Idx.
 *  \param[out]  rmDestRomIdx        read destination Pdu Idx from the queue
 *  \param[out]  info                read data from the queue
 *  \return      E_OK                A Pdu could be read and will be returned via the pointers
 *               E_NOT_OK            No Pdu could be read.
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_Fm_GetNextElement(PduR_RmGDestRomIterType rmGDestRomIdx, P2VAR(PduR_RmDestRomIterType, AUTOMATIC, PDUR_APPL_DATA) rmDestRomIdx, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
#endif

# if (PDUR_EXISTS_SHARED_FIFO_QUEUE_IMPLEMENTATIONTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_GetFillLevel
 *********************************************************************************************************************/
/*! \brief       Get the fill level of the queue.
 *  \details     -
 *  \param[in]   rmGDestRomIdx       global destination Pdu Idx.
 *  \return                          Fill level of the queue
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(uint16, PDUR_CODE) PduR_Fm_GetFillLevel(PduR_RmGDestRomIterType rmGDestRomIdx);
#endif

# if (PDUR_EXISTS_SHARED_FIFO_QUEUE_IMPLEMENTATIONTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_FlushFiFo
 *********************************************************************************************************************/
/*! \brief       This function flushes the FIFO queue.
 *  \details     -
 *  \param[in]   rmGDestRomIdx  routing manager indirection Idx.
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Fm_FlushFiFo(PduR_RmGDestRomIterType rmGDestRomIdx);
# endif

#if (PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_ReleaseFifoElement
 *********************************************************************************************************************/
/*! \brief       Reset Fifo Element.
 *  \details     -
 *  \param[in]   fmFifoElementRamIdx    Fifo State Id used for state handling.
 *  \param[in]   memIdx                 memory section index
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Fm_ReleaseFifoElement(PduR_FmFifoElementRamIterType fmFifoElementRamIdx, PduR_MemIdxType memIdx);
#endif

#if (PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_GetCurrentlyUsedBmTxBufferRomIdxByFmFifoElementIdx
 *********************************************************************************************************************/
/*! \brief       Return the currently used BmTxBufferRomIdx of this fmFifoElement.
 *  \details     -
 *  \param[in]   fmFifoElementRamIdx Fifo State Id used for state handling.
 *  \param[out]  bmTxBufferRomIdx    tx buffer index
 *  \param[in]   memIdx              memory section index
 *  \return      E_OK                the read bmTxBufferRomIdx is valid and can be used
 *               E_NOT_OK            the read bmTxBufferRomIdx is invalid and can not be used
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_Fm_GetCurrentlyUsedBmTxBufferRomIdxByFmFifoElementIdx(PduR_FmFifoElementRamIterType fmFifoElementRamIdx, P2VAR(PduR_BmTxBufferRomIterType, AUTOMATIC, PDUR_APPL_DATA) bmTxBufferRomIdx, PduR_MemIdxType memIdx);
#endif

#if (PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_GetCurrentlyUsedBmTxBufferInstanceIdxByRmGDestIdx
 *********************************************************************************************************************/
/*! \brief       Return the currently used BmTxBufferInstanceRomIdx for this global destination.
 *  \details     -
 *  \param[in]   rmGDestRomIdx             global destination Pdu index
 *  \param[out]  bmTxBufferInstanceRomIdx  tx Buffer Instance index
 *  \return      E_OK                      the read bmTxBufferInstanceRomIdx is valid and can be used
 *               E_NOT_OK                  the read bmTxBufferInstanceRomIdx is invalid and can not be used
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_Fm_GetCurrentlyUsedBmTxBufferInstanceIdxByRmGDestIdx(PduR_RmGDestRomIterType rmGDestRomIdx, P2VAR(PduR_BmTxBufferInstanceRomIterType, AUTOMATIC, PDUR_APPL_DATA) bmTxBufferInstanceRomIdx);
#endif

#if (PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_GetRmDestRomIdxOfFmFifoElementRamSafe
 *********************************************************************************************************************/
/*! \brief       Gets the rmDestRomIdx of fmFifoElement with error detection.
 *  \details     -
 *  \param[in]   fmFifoElementRamIdx  Id of the Fifo element
 *  \param[out]  rmDestRomIdx         The read rmDestRomIdx
 *  \param[in]   memIdx               memory section index
 *  \return      E_OK                 The read was successful.
 *               E_NOT_OK             The read was not successful.
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_Fm_GetRmDestRomIdxOfFmFifoElementRamSafe(PduR_FmFifoElementRamIterType fmFifoElementRamIdx, P2VAR(PduR_RmDestRomIterType, AUTOMATIC, PDUR_APPL_DATA) rmDestRomIdx, PduR_MemIdxType memIdx);
#endif

#if (PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_GetFmFifoElementRamWriteIdxSafe
 *********************************************************************************************************************/
/*! \brief       Gets the current write idx for the FIFO element.
 *  \details     -
 *  \param[in]   fmFifoRamIdx    Id of the Fifo
 *  \param[in]   memIdx          memory section index
 *  \return                      the write index
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(PduR_FmFifoElementRamWriteIdxOfFmFifoRamType, PDUR_CODE) PduR_Fm_GetFmFifoElementRamWriteIdxSafe(PduR_FmFifoRamIterType fmFifoRamIdx, PduR_MemIdxType memIdx);
#endif

# if (PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_IsFifoElementAllocated
 *********************************************************************************************************************/
/*! \brief       Helper function to check if the queue element is in use.
 *  \details     -
 *  \param[in]   fmFifoElementRamIdx    Fifo State Id used for state handling.
 *  \param[in]   memIdx                 memory section index
 *  \return      E_OK                   if the queue is in use.
 *               E_NOT_OK               if the queue is not in use.
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_Fm_IsFifoElementAllocated(PduR_FmFifoElementRamIterType fmFifoElementRamIdx, PduR_MemIdxType memIdx);
# endif

# define PDUR_STOP_SEC_CODE
# include "PduR_MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */
#endif /* PDUR_FM_H */
/**********************************************************************************************************************
 *  END OF FILE: PduR_Fm.h
 *********************************************************************************************************************/
