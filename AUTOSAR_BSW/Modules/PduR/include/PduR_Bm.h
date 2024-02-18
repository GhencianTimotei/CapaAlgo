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
 *         File:  PduR_Bm.h
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
#if !defined (PDUR_BM_H)
# define PDUR_BM_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
/* \trace SPEC-2020230, SPEC-38402 */

# include "PduR_Types.h"
# include "PduR_Cfg.h"
# if (PDUR_DEV_ERROR_REPORT == STD_ON)
#  include "Det.h"
# endif
# include "PduR_Lcfg.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
# if(PDUR_BMTXBUFFERRAM == STD_ON)
#define PDUR_BUFFER_EMPTY_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM                                    0x00u
#define PDUR_BUFFER_WRITE4READ_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM                               0x01u
#define PDUR_BUFFER_READ4WRITE_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM                               0x02u
#define PDUR_BUFFER_FULL_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM                                     0x03u
#define PDUR_BUFFER_EMPTY_PDURBUFFERSTATEOFBMTXBUFFERRAM                                            0x00u
#define PDUR_BUFFER_WRITE4READ_PDURBUFFERSTATEOFBMTXBUFFERRAM                                       0x01u
#define PDUR_BUFFER_READ4WRITE_PDURBUFFERSTATEOFBMTXBUFFERRAM                                       0x02u
#define PDUR_BUFFER_FULL_PDURBUFFERSTATEOFBMTXBUFFERRAM                                             0x03u
# endif

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
# if(PDUR_BMTXBUFFERRAM == STD_ON)
/*! Value based type definition for PduR_PduRBufferStateOfBmTxBufferRam */
typedef uint8 PduR_PduRBufferStateOfBmTxBufferRamType;
/*! Value based type definition for PduR_PduRBufferStateOfBmTxBufferInstanceRam */
typedef uint8 PduR_PduRBufferStateOfBmTxBufferInstanceRamType;
/*! Value based type definition for PduR_BmTxBufferArrayRamReadIdxOfBmTxBufferRamType */
typedef PduR_BmTxBufferArrayRamWriteIdxOfBmTxBufferRamType PduR_BmTxBufferArrayRamReadIdxOfBmTxBufferRamType;
# endif

# define PDUR_START_SEC_CODE
# include "PduR_MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

# if(PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
  PduR_Bm_Init
**********************************************************************************************************************/
/*! \brief       This function initializes the BufferManager.
 *  \details     -
 *  \param[in]   memIdx  memory section index
 *  \pre         PduR_InitMemory() has been executed, if the start up code does not initialize variables.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 ********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Bm_Init(PduR_MemIdxType memIdx);
# endif

# if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_PutData
 *********************************************************************************************************************/
/*! \brief      Call to put data into the buffer.
 *  \details -
 *  \param[in]  bmTxBufferRomIdx         read index in the transport protocol Tx buffer
 *  \param[in] pduLength                 length to copy.
 *  \param[in] sduDataPtr                data pointer.
 *  \param[in] memIdx                    memory section index
 *  \pre         PduR_Init() is executed successfully.
 *  \return      BUFREQ_OK                Copy action was successful.
 *               BUFREQ_E_NOT_OK          Copy action was not successful.
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_Bm_PutData(PduR_BmTxBufferRomIterType bmTxBufferRomIdx, PduLengthType pduLength, CONST(SduDataPtrType, AUTOMATIC) sduDataPtr, PduR_MemIdxType memIdx);
# endif

# if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_PutDataAsPtr
 *********************************************************************************************************************/
/*! \brief       Call to put data into the buffer.
 *  \details     -
 *  \param[in]   bmTxBufferRomIdx         read index in the transport protocol Tx buffer
 *  \param[in]   info                     data pointer.
 *  \param[in]   memIdx                   memory section index
 *  \pre         PduR_Init() is executed successfully.
 *  \return      BUFREQ_OK                Copy action was successful.
 *               BUFREQ_E_NOT_OK          Copy action was not successful.
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_Bm_PutDataAsPtr(PduR_BmTxBufferRomIterType bmTxBufferRomIdx, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, PduR_MemIdxType memIdx);     /* COV_PDUR_IF_ONLY */
# endif

# if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_GetData
 *********************************************************************************************************************/
/*!  \brief      Call to get queued data from the buffer.
 *   \details -
 *   \param[in]  bmTxBufferInstanceRomIdx instance Idx
 *   \param[in]  pduLength                length to copy
 *   \param[out] sduDataPtr               data pointer
 *   \param[in]  memIdx                   memory section index
 *   \pre        PduR_Init() is executed successfully.
 *   \return     BUFREQ_OK              Copy action was successful.
 *               BUFREQ_E_NOT_OK        Copy action was not successful.
 *   \context    TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_Bm_GetData(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx, PduLengthType pduLength, CONST(SduDataPtrType, AUTOMATIC) sduDataPtr, PduR_MemIdxType memIdx);
# endif

# if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_ResetTxBuffer
 *********************************************************************************************************************/
/*! \brief      Reset Buffer element: Read, WriteIndex, data and buffer size information, Buffer state.
 *  \details -
 *  \param[in]  bmTxBufferRomIdx  read index in the transport protocol Tx buffer.
 *  \param[in]  memIdx            memory section index
 *  \pre         PduR_Init() is executed successfully.
 *  \context    TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Bm_ResetTxBuffer(PduR_BmTxBufferRomIterType bmTxBufferRomIdx, PduR_MemIdxType memIdx);
# endif

# if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_ResetTxBufferInstance
 *********************************************************************************************************************/
/*! \brief       Reset Instance Buffer element: Read, WriteIdx, data and buffer size information, Buffer state.
 *  \details     -
 *  \param[in]   bmTxBufferInstanceRomIdx  instance Idx.
 *  \param[in]   memIdx  memory section index
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Bm_ResetTxBufferInstance(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx, PduR_MemIdxType memIdx);
# endif

# if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_EnableBmTxBufferInstance
 *********************************************************************************************************************/
/*! \brief       Enable the BmTxBuffer read instance.
 *  \details     -
 *  \param[in]   bmTxBufferRomIdx          Index of the Tx buffer.
 *  \param[in]   bmTxBufferInstanceRomIdx  Instance Index of the Tx buffer.
 *  \param[in]   memIdx                    memory section index
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Bm_EnableBmTxBufferInstance(PduR_BmTxBufferRomIterType bmTxBufferRomIdx, PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx, PduR_MemIdxType memIdx);
# endif

#if ((PDUR_BMTXBUFFERRAM == STD_ON) && (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON))
/**********************************************************************************************************************
 * PduR_Bm_GetTotalDataSize
 *********************************************************************************************************************/
/*! \brief       Get the total data size which is available
 *  \details     -
 *  \param[in]   bmTxBufferRomIdx  index to the BmTxBuffer element
 *  \param[in]   memIdx            memory section index
 *  \return      the calculated total data size
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(PduR_BmTxBufferArrayRamIterType, PDUR_CODE) PduR_Bm_GetTotalDataSize(PduR_BmTxBufferRomIterType bmTxBufferRomIdx, PduR_MemIdxType memIdx);
# endif

# if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_GetLinearDataSizeInstance
 *********************************************************************************************************************/
/*! \brief       Get the data size which is available without doing a wrap around.
 *  \details     -
 *  \param[in]   bmTxBufferInstanceRomIdx  index to the BmTxBuffer element
 *  \param[in]   memIdx  memory section index
 *  \return      the calculated linear data size
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(PduR_BmTxBufferArrayRamIterType, PDUR_CODE) PduR_Bm_GetLinearDataSizeInstance(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx, PduR_MemIdxType memIdx);
# endif

# if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_GetTotalDataSizeInstance
 *********************************************************************************************************************/
/*! \brief       Get the total data size which is available
 *  \details     -
 *  \param[in]   bmTxBufferInstanceRomIdx  index to the BmTxBuffer element
 *  \param[in]   memIdx                    memory section index
 *  \return      the calculated total data size
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(PduR_BmTxBufferArrayRamIterType, PDUR_CODE) PduR_Bm_GetTotalDataSizeInstance(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx, PduR_MemIdxType memIdx);
# endif

# if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_GetTotalBufferSize
 *********************************************************************************************************************/
/*! \brief       Get the total free buffer size which is available
 *  \details     -
 *  \param[in]   bmTxBufferRomIdx  index to the BmTxBuffer element
 *  \param[in]   memIdx            memory section index
 *  \return      the calculated total free buffer size
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(PduR_BmTxBufferArrayRamIterType, PDUR_CODE) PduR_Bm_GetTotalBufferSize(PduR_BmTxBufferRomIterType bmTxBufferRomIdx, PduR_MemIdxType memIdx);
# endif

# if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_AllocateTxBuffer
 *********************************************************************************************************************/
/*! \brief       Search a suitable buffer from the buffer pool.
 *  \details     -
 *  \param[in]   fmFifoRomIdx              Index to the FmFifo object
 *  \param[in]   pduLength                 SDU length which must be routed
 *  \param[in]   optimalBufferSize         The optimal buffer size (which fits the whole Pdu)
 *  \param[in]   minimumBufferSize         The minimum buffer size which still can be used for Tp routings (which only fits the TpThreshold + Metadata)
 *  \param[out]  bufferSizePtr             Available buffer
 *  \param[out]  allocatedTxBufferIdxPtr   Id of the allocated TxBuffer
 *  \param[in]   memIdx                    memory section index
 *  \return      BUFREQ_OK                 Buffer request was successful.
 *               BUFREQ_E_NOT_OK           Currently no buffer is available or a buffer request occurs for a 1:N routing
 *                                         and no buffer is available to store the complete frame to the buffer.
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_Bm_AllocateTxBuffer(PduR_FmFifoRomIterType fmFifoRomIdx,
                                                            PduLengthType pduLength,
                                                            PduLengthType optimalBufferSize,
                                                            PduLengthType minimumBufferSize,
                                                            P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr,
                                                            P2VAR(PduR_BmTxBufferRomIdxOfBmTxBufferIndRomType, AUTOMATIC, PDUR_APPL_DATA) allocatedTxBufferIdxPtr,
                                                            PduR_MemIdxType memIdx);
# endif

# if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_CopyDataAsPtr
 *********************************************************************************************************************/
/*! \brief       Get the Buffer Data as a Pointer to the data.
 *  \details     -
 *  \param[in]   bmTxBufferInstanceRomIdx  TxBuffer ID
 *  \param[out]  info                      PduInfo Pointer to the Data.
 *  \param[in]   length                    Length of the requested Data.
 *  \param[in]   memIdx                    memory section index
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Bm_CopyDataAsPtr(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, PduR_BmTxBufferArrayRamIterType length, PduR_MemIdxType memIdx);
# endif

# if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_GetActualPduLengthToBeRouted
 *********************************************************************************************************************/
/*! \brief       The actual entire Pdu length which shall be routed.
 *  \details     -
 *  \param[in]   bmTxBufferInstanceRomIdx  TxBuffer ID
 *  \param[in]   memIdx                    memory section index
 *  \return      actual entire Length of Pdu to be routed.
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(PduLengthType, PDUR_CODE) PduR_Bm_GetActualPduLengthToBeRouted(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx, PduR_MemIdxType memIdx);
# endif
# if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_GetPduRBufferStateOfBmTxBufferInstanceRam
 *********************************************************************************************************************/
/*! \brief       The state of a buffer instance.
 *  \details     -
 *  \param[in]   bmTxBufferInstanceRomIdx  TxBuffer ID
 *  \param[in]   bmTxBufferArrayRamReadIdx TxBuffer ID
 *  \param[in]   memIdx                    memory section index
 *  \return      State of the particular buffer instance.
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(PduR_PduRBufferStateOfBmTxBufferInstanceRamType, PDUR_CODE) PduR_Bm_GetPduRBufferStateOfBmTxBufferInstanceRam(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx,
                                                                                                                   PduR_BmTxBufferArrayRamReadIdxOfBmTxBufferInstanceRamType bmTxBufferArrayRamReadIdx,
                                                                                                                   PduR_MemIdxType memIdx);
# endif
# if (PDUR_BMTXBUFFERRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Bm_GetPduRBufferStateOfBmTxBufferRam
 *********************************************************************************************************************/
/*! \brief       The state of a buffer.
 *  \details     -
 *  \param[in]   bmTxBufferInstanceRomIdx  TxBuffer ID
 *  \param[in]   memIdx                    memory section index
 *  \return      State of the particular buffer.
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(PduR_PduRBufferStateOfBmTxBufferRamType, PDUR_CODE) PduR_Bm_GetPduRBufferStateOfBmTxBufferRam (PduR_BmTxBufferRomIterType bmTxBufferRomIdx, PduR_MemIdxType memIdx);
# endif
# define PDUR_STOP_SEC_CODE
# include "PduR_MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */
#endif /* PDUR_BM_H */
/**********************************************************************************************************************
 *  END OF FILE: PduR_Bm.h
 *********************************************************************************************************************/
