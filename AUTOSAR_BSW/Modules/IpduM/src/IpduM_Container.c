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
 *         File:  IpduM_Container.c
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

#define IPDUM_CONTAINER_SOURCE
/**********************************************************************************************************************
 * MISRA JUSTIFICATION
 *********************************************************************************************************************/

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
#include "IpduM.h"
#include "IpduM_Container.h"
#include "SchM_IpduM.h"
#include "vstdlib.h"

#if (IPDUM_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif
#if ((IPDUM_TXBUFFERSTARTIDXOFTXPATHWAY == STD_ON) || (IPDUM_RXMUXPDU == STD_ON) || (IPDUM_CONTAINERRXBUFFER == STD_ON) || (IPDUM_CONTAINERTXBUFFER == STD_ON))      /* COV_IPDUM_EMPTY_CONFIG */
# include "PduR_IpduM.h"
#endif

/**********************************************************************************************************************
  LOCAL CONSTANT MACROS
**********************************************************************************************************************/
#define IPDUM_RESET                             0u

#define IPDUM_HEADERSIZE_SMALL                  4u
#define IPDUM_HEADERSIZE_LARGE                  8u

/**********************************************************************************************************************
  LOCAL FUNCTION MACROS
**********************************************************************************************************************/
#if (IPDUM_DEV_ERROR_REPORT == STD_ON)                                     
# define IpduM_Det_ReportError(ApiId, ErrorCode)    (void)Det_ReportError(IPDUM_MODULE_ID, 0, (ApiId), (ErrorCode))   /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#endif

/**********************************************************************************************************************
  LOCAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
#define IPDUM_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h"    /* PRQA S 5087 */        /*  MD_MSR_MemMap */

#if ((IPDUM_TXCONTAINEDPDU == STD_ON) || (IPDUM_EXISTS_SHORT_HEADERSIZEOFRXCONTAINERPDU == STD_ON) || (IPDUM_EXISTS_LONG_HEADERSIZEOFRXCONTAINERPDU == STD_ON))
/* Stores the information about the header of a contained pdu. */
typedef struct
{
  uint32 headerId;
  uint32 dlc;
} IpduM_ContainedPduHeaderType;
#endif

#define IPDUM_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h"    /* PRQA S 5087 */        /*  MD_MSR_MemMap */

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

#if (IPDUM_TXCONTAINEDPDU == STD_ON)
/*******************************************************************************************
*  IpduM_ContainerTx_WriteHeader()
*******************************************************************************************/
/*! \brief        Writes the header to the container PDU buffer
 *  \details      -
 *  \param[out]   pContainerBuf   Pointer to buffer containing container PDU
 *  \param[in]    header          Header information: ID and DLC
 *  \param[in]    headerSize
 *  \param[in]    freeBytes       Number of free bytes in the buffer, used to verify the header fits into the container
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE for different buffers
 *  \synchronous  TRUE
*******************************************************************************************/
LOCAL_INLINE FUNC(void,
                  IPDUM_CODE) IpduM_ContainerTx_WriteHeader(P2VAR(uint8, AUTOMATIC, IPDUM_APPL_DATA) pContainerBuf,
                                                         P2CONST(IpduM_ContainedPduHeaderType, AUTOMATIC, IPDUM_APPL_DATA) header, PduLengthType headerSize, uint32 freeBytes);
#endif

#if ((IPDUM_TXCONTAINEDPDU == STD_ON) || (IPDUM_EXISTS_SHORT_HEADERSIZEOFRXCONTAINERPDU == STD_ON) || (IPDUM_EXISTS_LONG_HEADERSIZEOFRXCONTAINERPDU == STD_ON))
/*******************************************************************************************
*  IpduM_Container_ReadHeader()
*******************************************************************************************/
/*! \brief        Reads the header from the start position of the provided buffer
 *  \details      -
 *  \param[in]    headerSize
 *  \param[in]    pContainerBuf   Pointer to buffer containing container PDU, must be at least headerSize bytes large!
 *  \return       header          Header at the beginning of the provided container PDU buffer
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE for different buffers
 *  \synchronous  TRUE
*******************************************************************************************/
LOCAL_INLINE FUNC(IpduM_ContainedPduHeaderType, IPDUM_CODE) IpduM_Container_ReadHeader(P2CONST(uint8, AUTOMATIC, IPDUM_APPL_DATA) pContainerBuf, uint32 headerSize);
#endif

# if((IPDUM_EXISTS_SHORT_HEADERSIZEOFRXCONTAINERPDU == STD_ON) || (IPDUM_EXISTS_LONG_HEADERSIZEOFRXCONTAINERPDU == STD_ON))
/*******************************************************************************************
 *  IpduM_ContainerRx_GetHeaderSize()
*******************************************************************************************/
/*! \brief        Gets header size for given container.
 *  \details      -
 *  \param[in]    rxContainerId
 *  \return       headerSize
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE
 *  \synchronous  TRUE
*******************************************************************************************/
LOCAL_INLINE FUNC(uint8, IPDUM_CODE) IpduM_ContainerRx_GetHeaderSize(IpduM_RxContainerPduIterType rxContainerId);
#endif

#if (IPDUM_TXCONTAINEDPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTx_GetHeaderSize()
*******************************************************************************************/
/*! \brief        Gets header size for given container.
 *  \details      -
 *  \param[in]    txContainerId
 *  \return       headerSize
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE
 *  \synchronous  TRUE
*******************************************************************************************/
LOCAL_INLINE FUNC(uint8, IPDUM_CODE) IpduM_ContainerTx_GetHeaderSize(IpduM_CTxContainerPduIterType txContainerId);
#endif

#if (IPDUM_TXCONTAINEDPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTx_GetStartAddrOfCurrentlyWrittenContainerPdu()
*******************************************************************************************/
/*! \brief        Returns the address of the beginning of the currently written container instance.
 *  \details      -
 *  \param[in]    txContainerId
 *  \return       the address
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE
 *  \synchronous  TRUE
*******************************************************************************************/
LOCAL_INLINE FUNC(IpduM_ContainerTxBufferPtrType, IPDUM_CODE) IpduM_ContainerTx_GetStartAddrOfCurrentlyWrittenContainerPdu(IpduM_CTxContainerPduIterType txContainerId);
#endif

#if (IPDUM_TXCONTAINEDPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTx_GetStartAddrOfCurrentlyReadContainerPdu()
*******************************************************************************************/
/*! \brief        Returns the address of the beginning of the currently read container instance.
 *  \details      -
 *  \param[in]    txContainerId
 *  \return       the address
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE
 *  \synchronous  TRUE
*******************************************************************************************/
LOCAL_INLINE FUNC(IpduM_ContainerTxBufferPtrType, IPDUM_CODE) IpduM_ContainerTx_GetStartAddrOfCurrentlyReadContainerPdu(IpduM_CTxContainerPduIterType txContainerId);
#endif

#if (IPDUM_REQUESTQUEUEUSEDOFTXCONTAINERPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTx_RequestQueue_IsEmpty()
*******************************************************************************************/
/*! \brief        Checks if the request queue for a given container is empty.
 *  \details      -
 *  \param[in]    txContainerId
 *  \return       TRUE if the queue has no PDUs
 *  \return       FALSE if there are PDUs in the queue
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE
 *  \synchronous  TRUE
*******************************************************************************************/
LOCAL_INLINE FUNC(boolean, IPDUM_CODE) IpduM_ContainerTx_RequestQueue_IsEmpty(IpduM_CTxContainerPduIterType txContainerId);
#endif

#if (IPDUM_REQUESTQUEUEUSEDOFTXCONTAINERPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTx_RequestQueue_ContainsPdu()
*******************************************************************************************/
/*! \brief        Checks if a Pdu is already queued in the request queue.
 *  \details      -
 *  \param[in]    txContainedId
 *  \return       TRUE if the PDU is in the container
 *  \return       FALSE if the PDU is not in the container
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE
 *  \synchronous  TRUE
*******************************************************************************************/
LOCAL_INLINE FUNC(boolean, IPDUM_CODE) IpduM_ContainerTx_RequestQueue_ContainsPdu(IpduM_TxContainedPduIterType txContainedId);
#endif

#if (IPDUM_REQUESTQUEUEUSEDOFTXCONTAINERPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTx_RequestQueue_CalculateSize()
*******************************************************************************************/
/*! \brief        Calculates the size of data stored in the request queue (the DLCs combined)
 *  \details      -
 *  \param[in]    txContainerId
 *  \return       Size of data stored in the request queue
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE
 *  \synchronous  TRUE
*******************************************************************************************/
LOCAL_INLINE FUNC(PduLengthType, IPDUM_CODE) IpduM_ContainerTx_RequestQueue_CalculateSize(IpduM_CTxContainerPduIterType txContainerId);
#endif

#if (IPDUM_REQUESTQUEUEUSEDOFTXCONTAINERPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTx_RequestQueue_AddPdu()
*******************************************************************************************/
/*! \brief        Adds a Pdu to the request queue.
 *  \details      -
 *  \param[in]    txContainedId
 *  \param[in]    sduLength       length of the received PDU for size estimation
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE
 *  \synchronous  TRUE
*******************************************************************************************/
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_ContainerTx_RequestQueue_AddPdu(IpduM_TxContainedPduIterType txContainedId, PduLengthType sduLength);
#endif

#if (IPDUM_FIRSTCONTAINEDPDUTRIGGEROFTXCONTAINERPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTx_TransmitEmptyPdu()
*******************************************************************************************/
/*! \brief        Sends an empty PDU with DLC=0 with the given Container PDU ID.
 *  \details      -
 *  \param[in]    txContainerId
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE
 *  \synchronous  TRUE
*******************************************************************************************/
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_ContainerTx_TransmitEmptyPdu(IpduM_CTxContainerPduIterType txContainerId);
#endif

#if (IPDUM_REQUESTQUEUEUSEDOFTXCONTAINERPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTx_RequestQueue_RemoveLastTransmittedIds
*******************************************************************************************/
/*! \brief        Makes the temporary read indices permanent
 *  \details      -
 *  \param[in]    txContainerId   ID of the container PDU
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *  \synchronous  TRUE
*******************************************************************************************/
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_ContainerTx_RequestQueue_RemoveLastTransmittedIds(IpduM_CTxContainerPduIterType txContainerId);
#endif

#if (IPDUM_REQUESTQUEUEUSEDOFTXCONTAINERPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTx_RequestQueue_FillLastIsBestContainer()
*******************************************************************************************/
/*! \brief        Fills the last-is-best buffer with data via trigger transmit
 *  \details      -
 *  \param[in]    txContainerId   ID of the container PDU
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *  \synchronous  TRUE
*******************************************************************************************/
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_ContainerTx_RequestQueue_FillLastIsBestContainer(IpduM_CTxContainerPduIterType txContainerId);
#endif

#if ((IPDUM_TXCONTAINEDPDU == STD_ON) && (IPDUM_REQUESTQUEUEUSEDOFTXCONTAINERPDU == STD_ON))
/*******************************************************************************************
 *  IpduM_ContainerTx_RequestQueue_TransmitContainer()
*******************************************************************************************/
/*! \brief        Transmits request queue Container PDU.
 *  \details      -
 *  \param[in]    txContainerId
 *  \return       E_OK            Transmission was successful, current instance is marked empty.
 *  \return       E_NOT_OK        Transmission was unsuccessful, current instance is untouched.
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE for different container IDs.
 *  \synchronous  TRUE
*******************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, IPDUM_CODE) IpduM_ContainerTx_RequestQueue_TransmitContainer(IpduM_CTxContainerPduIterType txContainerId);
#endif

#if (IPDUM_TXCONTAINEDPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTx_DataQueue_QueueCurrContainerPdu()
*******************************************************************************************/
/*! \brief        Queues Tx container queue.
 *  \details      If the queue is full: clears oldest item, throws DET, sets it as current.
 *  \param[in]    txContainerId
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE for different container IDs
 *  \synchronous  TRUE
*******************************************************************************************/
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_ContainerTx_DataQueue_QueueCurrContainerPdu(IpduM_CTxContainerPduIterType txContainerId);
#endif

#if (IPDUM_TXCONTAINEDPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTx_GetTransmittedPduLength()
*******************************************************************************************/
/*! \brief        Returns the actual length of the transmitted container Pdu.
 *  \details      -
 *  \param[in]    txContainerId
 *  \param[in]    dataPtr pointer to the data which shall be transmitted
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE for different container IDs
 *  \synchronous  TRUE
*******************************************************************************************/
LOCAL_INLINE FUNC(PduLengthType, IPDUM_CODE) IpduM_ContainerTx_GetTransmittedPduLength(IpduM_CTxContainerPduIterType txContainerId, P2VAR(uint8, AUTOMATIC, IPDUM_APPL_DATA) dataPtr);
#endif

#if (IPDUM_TXCONTAINEDPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTx_DataQueue_AddTxPduToCurrContainer()
*******************************************************************************************/
/*! \brief        Adds contained PDU to current container PDU.
 *  \details      -
 *  \param[in]    txContainedId
 *  \param[in]    PduInfoPtr      Pointer to the PDU data to be transmitted.
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE for different container IDs
 *  \synchronous  TRUE
*******************************************************************************************/
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_ContainerTx_DataQueue_AddTxPduToCurrContainer(IpduM_TxContainedPduIterType txContainedId, P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr);
#endif

#if (IPDUM_EXISTS_NONE_HEADERSIZEOFTXCONTAINERPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTx_DataQueue_ResetNoneHeaderContainerInstance()
*******************************************************************************************/
/*! \brief        Initializes a container PDU with unused area pattern and deactivated update bits.
 *  \details      -
 *  \param[in]    txContainerId
 *  \param[in]    txContainerInstance   Instance number of the container within the queue.
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE for different container IDs
 *  \synchronous  TRUE
*******************************************************************************************/
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_ContainerTx_DataQueue_ResetNoneHeaderContainerInstance(IpduM_CTxContainerPduIterType txContainerId, PduLengthType txContainerInstance);
#endif

#if((IPDUM_EXISTS_SHORT_HEADERSIZEOFRXCONTAINERPDU == STD_ON) || (IPDUM_EXISTS_LONG_HEADERSIZEOFRXCONTAINERPDU == STD_ON))
/*******************************************************************************************
 *  IpduM_ContainerRx_SearchRxHeaderId()
*******************************************************************************************/
/*! \brief        Searches for the received Container PDU header ID in the list of Rx Contained PDUs.
 *  \details      -
 *  \param[in]    headerId          Header ID to be searched for.
 *  \param[in]    rxContainerId     ID of the Container PDU.
 *  \return       rxContainedPduId  ID of the Contained PDU.
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE
 *  \synchronous  TRUE
*******************************************************************************************/
LOCAL_INLINE FUNC(IpduM_HeaderIdOfRxContainedPduType, IPDUM_CODE) IpduM_ContainerRx_SearchRxHeaderId(uint32 headerId, IpduM_RxContainerPduIterType rxContainerId);
#endif

#if(IPDUM_RXCONTAINERPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerRx_EnqueueContainer()
*******************************************************************************************/
/*! \brief        Enqueue the rx Container Pdu
 *  \details      -
 *  \param[in]    rxContainerId     ID of the Container PDU.
 *  \param[in]    PduInfoPtr        data pointer
 *  \param[in]    pduLength         actual length of the data
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE
 *  \synchronous  TRUE
*******************************************************************************************/
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_ContainerRx_EnqueueContainer(IpduM_RxContainerPduIterType rxContainerId, P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr, PduLengthType pduLength);
#endif

#if(IPDUM_RXCONTAINERPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerRx_GetCurrentlyReadContainerRxBufferPtr
*******************************************************************************************/
/*! \brief        Returns the pointer to the buffer which shall currently be read.
 *  \details      -
 *  \param[in]    rxContainerId     ID of the Container PDU.
 *  \return                         Pointer to the buffer
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE
 *  \synchronous  TRUE
*******************************************************************************************/
LOCAL_INLINE FUNC(uint8*, IPDUM_CODE) IpduM_ContainerRx_GetCurrentlyReadContainerRxBufferPtr(IpduM_RxContainerPduIterType rxContainerId);
#endif

#if(IPDUM_RXCONTAINERPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerRx_RemoveOldestElementOfQueue
*******************************************************************************************/
/*! \brief        Remove the oldest element from the Container Rx Queue.
 *  \details      -
 *  \param[in]    rxContainerId     ID of the Container PDU.
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE
 *  \synchronous  TRUE
*******************************************************************************************/
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_ContainerRx_RemoveOldestElementOfQueue(IpduM_RxContainerPduIterType rxContainerId);
#endif

#if (IPDUM_TXCONTAINEDPDU == STD_ON)
/*******************************************************************************************
*  IpduM_ContainerTx_CheckTriggers()
*******************************************************************************************/
/*! \brief        Checks trigger conditions and triggers the PDU if necessary
 *  \details      -
 *  \param[in]    txContainedId
 *  \param[in]    isFirstContainedPdu   is it the first contained Pdu which is added
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE for different handle IDs
 *  \synchronous  TRUE
 *  \trace        CREQ-102653, CREQ-102672, CREQ-102673
 *  \trace        SPEC-2068537, SPEC-2068538, SPEC-2068539, SPEC-2068543, SPEC-2068545, SPEC-2068549, SPEC-2068551, SPEC-2068552
*******************************************************************************************/
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_ContainerTx_CheckTriggers(IpduM_TxUpIndIdxOfTxUpInfoType txContainedId, boolean isFirstContainedPdu);
#endif

#if (IPDUM_TXCONTAINEDPDU == STD_ON)
/*******************************************************************************************
*  IpduM_ContainerTx_StartContainerPduSendTimeout
*******************************************************************************************/
/*! \brief        Start container Pdu send timeout after adding the first PDUs to it
 *  \details      -
 *  \param[in]    txContainerId
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE for different handle IDs
 *  \synchronous  TRUE
 *  \trace        CREQ-102653, CREQ-102672, CREQ-102673
 *  \trace        SPEC-2068537, SPEC-2068538, SPEC-2068539, SPEC-2068543, SPEC-2068545, SPEC-2068549, SPEC-2068551, SPEC-2068552
*******************************************************************************************/
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_ContainerTx_StartContainerPduSendTimeout(IpduM_CTxContainerPduIterType txContainerId);
#endif

#if (IPDUM_TXCONTAINEDPDU == STD_ON)
/*******************************************************************************************
*  IpduM_ContainerTx_StopContainerPduSendTimeout
*******************************************************************************************/
/*! \brief        Stop container Pdu send timeout
 *  \details      -
 *  \param[in]    txContainerId
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE for different handle IDs
 *  \synchronous  TRUE
*******************************************************************************************/
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_ContainerTx_StopContainerPduSendTimeout(IpduM_CTxContainerPduIterType txContainerId);
#endif

#if (IPDUM_TXCONTAINEDPDU == STD_ON)
/*******************************************************************************************
*  IpduM_ContainerTx_StartContainedPduSendTimeout
*******************************************************************************************/
/*! \brief        Start/Update contained Pdu send timeout after adding new PDUs to it
 *  \details      -
 *  \param[in]    txContainedId
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE for different handle IDs
 *  \synchronous  TRUE
 *  \trace        CREQ-102653, CREQ-102672, CREQ-102673
 *  \trace        SPEC-2068537, SPEC-2068538, SPEC-2068539, SPEC-2068543, SPEC-2068545, SPEC-2068549, SPEC-2068551, SPEC-2068552
*******************************************************************************************/
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_ContainerTx_StartContainedPduSendTimeout(IpduM_TxUpIndIdxOfTxUpInfoType txContainedId);
#endif

#if (IPDUM_TXCONTAINEDPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTx_DataQueue_IsFifoQueueEmpty()
*******************************************************************************************/
/*! \brief        Checks if the FIFO for a given container is empty.
 *  \details      -
 *  \param[in]    txContainerId
 *  \return       TRUE if the FIFO is empty
 *  \return       FALSE if the FIFO it not empty
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE
 *  \synchronous  TRUE
*******************************************************************************************/
LOCAL_INLINE FUNC(boolean, IPDUM_CODE) IpduM_ContainerTx_DataQueue_IsFifoQueueEmpty(IpduM_CTxContainerPduIterType txContainerId);
#endif

#if (IPDUM_TXCONTAINEDPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTx_DataQueue_IsFifoQueueFull()
*******************************************************************************************/
/*! \brief        Checks if the FIFO for a given container is full.
 *  \details      -
 *  \param[in]    txContainerId
 *  \return       TRUE if the FIFO is full
 *  \return       FALSE if the FIFO it not full
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE
 *  \synchronous  TRUE
*******************************************************************************************/
LOCAL_INLINE FUNC(boolean, IPDUM_CODE) IpduM_ContainerTx_DataQueue_IsFifoQueueFull(IpduM_CTxContainerPduIterType txContainerId);
#endif

#if (IPDUM_TXCONTAINEDPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTx_DataQueue_FitsPduIntoCurrentOpenInstance()
*******************************************************************************************/
/*! \brief        Checks if the provided Pdu fits into the open container instance
 *  \details      -
 *  \param[in]    txContainerId
 *  \param[in]    pduLength
 *  \return       TRUE if it fits
 *  \return       FALSE if it doesn't fit
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE
 *  \synchronous  TRUE
*******************************************************************************************/
LOCAL_INLINE FUNC(boolean, IPDUM_CODE) IpduM_ContainerTx_DataQueue_FitsPduIntoCurrentOpenInstance(IpduM_CTxContainerPduIterType txContainerId, PduLengthType pduLength);
#endif

#if (IPDUM_TXCONTAINEDPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTx_DataQueue_TransmitQueuedFIFOContainerPdu()
*******************************************************************************************/
/*! \brief        Transmit the next container instance from the queue.
 *  \details      -
 *  \param[in]    txContainerId
 *  \return       E_OK            Transmission was successful, last queue item is removed.
 *  \return       E_NOT_OK        Transmission was unsuccessful or nothing to transmit.
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE for different container IDs.
 *  \synchronous  TRUE
*******************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, IPDUM_CODE) IpduM_ContainerTx_DataQueue_TransmitQueuedFIFOContainerPdu(IpduM_CTxContainerPduIterType txContainerId);
#endif

#if (IPDUM_RXCONTAINERPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerRx_UnpackContainerPdu()
*******************************************************************************************/
/*! \brief        Retrieves all contained PDUs from the container PDU and sends RxIndications where configured.
 *  \details      -
 *  \param[in]    rxContainerId
 *  \param[in]    PduInfoPtr      Pointer to the received PDU data.
 *  \param[in]    pduLength      Length of received rx container
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE for different container IDs
 *  \synchronous  TRUE
*******************************************************************************************/
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_ContainerRx_UnpackContainerPdu(IpduM_RxContainerPduIterType rxContainerId, P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr, PduLengthType pduLength);
#endif

#if (IPDUM_TXCONTAINEDPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTx_DataQueue_TriggerTransmissionOfCurrContainerPdu()
*******************************************************************************************/
/*! \brief        Transmits (if direct transmission configured) or queues current container PDU.
 *  \details      -
 *  \param[in]    txContainerId
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE for different container IDs
 *  \synchronous  TRUE
*******************************************************************************************/
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_ContainerTx_DataQueue_TriggerTransmissionOfCurrContainerPdu(IpduM_CTxContainerPduIterType txContainerId);
#endif


#if ((IPDUM_TXLOINFOUSEDOFTXCONTAINERPDU == STD_ON) && (IPDUM_TXCONFIRMATIONTIMEOUTOFTXCONTAINERPDU == STD_ON))
/*******************************************************************************************
 *  IpduM_ContainerTx_StartTxConfirmationTimeout()
*******************************************************************************************/
/*! \brief        Load TxConfirmation timeout counter
 *  \details      -
 *  \param[in]    txContainerId
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE for different container IDs
 *  \synchronous  TRUE
*******************************************************************************************/
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_ContainerTx_StartTxConfirmationTimeout(IpduM_CTxContainerPduIterType txContainerId);
#endif

#if ((IPDUM_TXLOINFOUSEDOFTXCONTAINERPDU == STD_ON) && (IPDUM_TXCONFIRMATIONTIMEOUTOFTXCONTAINERPDU == STD_ON))
/*******************************************************************************************
 *  IpduM_ContainerTx_StopTxConfirmationTimeout()
*******************************************************************************************/
/*! \brief        Reset TxConfirmation timeout counter
 *  \details      -
 *  \param[in]    txContainerId
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE for different container IDs
 *  \synchronous  TRUE
*******************************************************************************************/
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_ContainerTx_StopTxConfirmationTimeout(IpduM_CTxContainerPduIterType txContainerId);
#endif

#if (IPDUM_TXCONTAINEDPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTx_DataQueue_TerminateContainer()
*******************************************************************************************/
/*! \brief        Writes a header containing only zeros to the end of the currently written container.
 *  \details      -
 *  \param[in]    txContainerId
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE for different container IDs
 *  \synchronous  TRUE
*******************************************************************************************/
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_ContainerTx_DataQueue_TerminateContainer(IpduM_CTxContainerPduIterType txContainerId);
#endif

#if (IPDUM_TXCONTAINEDPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTx_DataQueue_CloseCurrentContainerInstance()
*******************************************************************************************/
/*! \brief        Closes the current container instance.
 *  \details      -
 *  \param[in]    txContainerId
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE for different container IDs
 *  \synchronous  TRUE
*******************************************************************************************/
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_ContainerTx_DataQueue_CloseCurrentContainerInstance(IpduM_CTxContainerPduIterType txContainerId);
#endif

#if (IPDUM_TXCONTAINEDPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTx_CopyTxConfirmationsOfCurrentlyReadContainer2LastBuffer()
*******************************************************************************************/
/*! \brief        Copies the IDs of the to be confirmed contained Pdus of the currently read container to the last buffer.
 *  \details      -
 *  \param[in]    txContainerId
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE for different container IDs
 *  \synchronous  TRUE
*******************************************************************************************/
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_ContainerTx_CopyTxConfirmationsOfCurrentlyReadContainer2LastBuffer(IpduM_CTxContainerPduIterType txContainerId);
#endif

#if (IPDUM_TXCONTAINEDPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTx_DataQueue_RemoveOldestPdu()
*******************************************************************************************/
/*! \brief        Removes the oldest container Pdu from the queue.
 *  \details      -
 *  \param[in]    txContainerId
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE for different container IDs
 *  \synchronous  TRUE
*******************************************************************************************/
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_ContainerTx_DataQueue_RemoveOldestPdu(IpduM_CTxContainerPduIterType txContainerId);
#endif

#if (IPDUM_TXCONTAINEDPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTx_TransmitPduAndHandleTxConfTimeout()
*******************************************************************************************/
/*! \brief        Transmit the handed over Pdu and handle the optional TxConfirmation timeout.
 *  \details      -
 *  \param[in]    txContainerId
 *  \param[in]    PduInfoPtr pointer to the Pdu
 *  \return       E_OK     Transmission successful
 *                E_NOT_OK Transmission not successful
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE for different container IDs
 *  \synchronous  TRUE
*******************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, IPDUM_CODE) IpduM_ContainerTx_TransmitPduAndHandleTxConfTimeout(IpduM_CTxContainerPduIterType txContainerId, P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr);
#endif

#if (IPDUM_TX_CONFIRMATION_API == STD_ON && IPDUM_EXISTS_CONTAINER_PATHWAYTYPEOFCTXLOINFO == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTx_WriteContainedPduIdToTxConfirmationBuffer()
*******************************************************************************************/
/*! \brief        Write contained PduID to TxConfirmation Buffer
 *  \details      -
 *  \param[in]    txContainedId
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE for different contained IDs
 *  \synchronous  TRUE
*******************************************************************************************/
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_ContainerTx_WriteContainedPduIdToTxConfirmationBuffer(IpduM_TxUpIndIdxOfTxUpInfoType txContainedId);
#endif

#define IPDUM_STOP_SEC_CODE
#include "MemMap.h"    /* PRQA S 5087 */        /*  MD_MSR_MemMap */

/**********************************************************************************************************************
  LOCAL FUNCTIONS
**********************************************************************************************************************/
#define IPDUM_START_SEC_CODE
#include "MemMap.h"    /* PRQA S 5087 */        /*  MD_MSR_MemMap */

#if (IPDUM_TXCONTAINEDPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTx_WriteHeader()
*******************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
LOCAL_INLINE FUNC(void,
                  IPDUM_CODE) IpduM_ContainerTx_WriteHeader(P2VAR(uint8, AUTOMATIC, IPDUM_APPL_DATA) pContainerBuf,
                                                         P2CONST(IpduM_ContainedPduHeaderType, AUTOMATIC, IPDUM_APPL_DATA) header, PduLengthType headerSize, uint32 freeBytes)
{
# if (IPDUM_EXISTS_SHORT_HEADERSIZEOFTXCONTAINERPDU == STD_ON)
  if((freeBytes >= IPDUM_HEADERSIZE_SMALL) && (headerSize == IPDUM_HEADERSIZE_SMALL)) /*COV_IPDUM_SINGLE_HEADERSIZE_CONFIG */
  {
#  if (IPDUM_HEADER_BYTE_ORDER == IPDUM_LITTLE_ENDIAN)
    pContainerBuf[0] = ((uint8) (header->headerId >> 0));       /* PRQA S 2985 */ /* MD_IpduM_2985 */ /* SBSW_IPDUM_ARRAY_WRITE_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */ /* VCA_IPDUM_ARRAY_WRITE_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */
    pContainerBuf[1] = ((uint8) (header->headerId >> 8));       /* SBSW_IPDUM_ARRAY_WRITE_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */ /* VCA_IPDUM_ARRAY_WRITE_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */
    pContainerBuf[2] = ((uint8) (header->headerId >> 16));      /* SBSW_IPDUM_ARRAY_WRITE_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */ /* VCA_IPDUM_ARRAY_WRITE_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */
    pContainerBuf[3] = ((uint8) (header->dlc >> 0));    /* PRQA S 2985 */ /* MD_IpduM_2985 */ /* SBSW_IPDUM_ARRAY_WRITE_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */ /* VCA_IPDUM_ARRAY_WRITE_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */
#  else /* (IPDUM_HEADER_BYTE_ORDER == IPDUM_BIG_ENDIAN) */
    pContainerBuf[0] = ((uint8) (header->headerId >> 16));      /* SBSW_IPDUM_ARRAY_WRITE_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */ /* VCA_IPDUM_ARRAY_WRITE_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */
    pContainerBuf[1] = ((uint8) (header->headerId >> 8));       /* SBSW_IPDUM_ARRAY_WRITE_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */ /* VCA_IPDUM_ARRAY_WRITE_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */
    pContainerBuf[2] = ((uint8) (header->headerId >> 0));       /* PRQA S 2985 */ /* MD_IpduM_2985 */ /* SBSW_IPDUM_ARRAY_WRITE_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */ /* VCA_IPDUM_ARRAY_WRITE_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */
    pContainerBuf[3] = ((uint8) (header->dlc >> 0));    /* PRQA S 2985 */ /* MD_IpduM_2985 */ /* SBSW_IPDUM_ARRAY_WRITE_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */ /* VCA_IPDUM_ARRAY_WRITE_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */
#  endif
  }
# endif
# if (IPDUM_EXISTS_LONG_HEADERSIZEOFTXCONTAINERPDU == STD_ON)
  if((headerSize == IPDUM_HEADERSIZE_LARGE) && (freeBytes >= IPDUM_HEADERSIZE_LARGE)) /*COV_IPDUM_SINGLE_HEADERSIZE_CONFIG */
  {
#  if (IPDUM_HEADER_BYTE_ORDER == IPDUM_LITTLE_ENDIAN)
    pContainerBuf[0] = ((uint8) (header->headerId >> 0));       /* PRQA S 2985 */ /* MD_IpduM_2985 */ /* SBSW_IPDUM_ARRAY_WRITE_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */ /* VCA_IPDUM_ARRAY_WRITE_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */
    pContainerBuf[1] = ((uint8) (header->headerId >> 8));       /* SBSW_IPDUM_ARRAY_WRITE_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */ /* VCA_IPDUM_ARRAY_WRITE_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */
    pContainerBuf[2] = ((uint8) (header->headerId >> 16));      /* SBSW_IPDUM_ARRAY_WRITE_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */ /* VCA_IPDUM_ARRAY_WRITE_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */
    pContainerBuf[3] = ((uint8) (header->headerId >> 24));      /* SBSW_IPDUM_ARRAY_WRITE_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */ /* VCA_IPDUM_ARRAY_WRITE_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */
    pContainerBuf[4] = ((uint8) (header->dlc >> 0));    /* PRQA S 2985 */ /* MD_IpduM_2985 */ /* SBSW_IPDUM_ARRAY_WRITE_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */ /* VCA_IPDUM_ARRAY_WRITE_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */
    pContainerBuf[5] = ((uint8) (header->dlc >> 8));    /* SBSW_IPDUM_ARRAY_WRITE_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */ /* VCA_IPDUM_ARRAY_WRITE_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */
    pContainerBuf[6] = ((uint8) (header->dlc >> 16));   /* SBSW_IPDUM_ARRAY_WRITE_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */ /* VCA_IPDUM_ARRAY_WRITE_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */
    pContainerBuf[7] = ((uint8) (header->dlc >> 24));   /* SBSW_IPDUM_ARRAY_WRITE_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */ /* VCA_IPDUM_ARRAY_WRITE_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */
#  else /* (IPDUM_HEADER_BYTE_ORDER == IPDUM_BIG_ENDIAN) */
    pContainerBuf[0] = ((uint8) (header->headerId >> 24));      /* SBSW_IPDUM_ARRAY_WRITE_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */ /* VCA_IPDUM_ARRAY_WRITE_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */
    pContainerBuf[1] = ((uint8) (header->headerId >> 16));      /* SBSW_IPDUM_ARRAY_WRITE_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */ /* VCA_IPDUM_ARRAY_WRITE_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */
    pContainerBuf[2] = ((uint8) (header->headerId >> 8));       /* SBSW_IPDUM_ARRAY_WRITE_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */ /* VCA_IPDUM_ARRAY_WRITE_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */
    pContainerBuf[3] = ((uint8) (header->headerId >> 0));       /* PRQA S 2985 */ /* MD_IpduM_2985 */ /* SBSW_IPDUM_ARRAY_WRITE_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */ /* VCA_IPDUM_ARRAY_WRITE_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */
    pContainerBuf[4] = ((uint8) (header->dlc >> 24));   /* SBSW_IPDUM_ARRAY_WRITE_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */ /* VCA_IPDUM_ARRAY_WRITE_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */
    pContainerBuf[5] = ((uint8) (header->dlc >> 16));   /* SBSW_IPDUM_ARRAY_WRITE_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */ /* VCA_IPDUM_ARRAY_WRITE_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */
    pContainerBuf[6] = ((uint8) (header->dlc >> 8));    /* SBSW_IPDUM_ARRAY_WRITE_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */ /* VCA_IPDUM_ARRAY_WRITE_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */
    pContainerBuf[7] = ((uint8) (header->dlc >> 0));    /* PRQA S 2985 */ /* MD_IpduM_2985 */ /* SBSW_IPDUM_ARRAY_WRITE_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */ /* VCA_IPDUM_ARRAY_WRITE_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */
#  endif
  }
# endif
  IPDUM_DUMMY_STATEMENT(headerSize);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}
#endif

#if ((IPDUM_TXCONTAINEDPDU == STD_ON) || (IPDUM_EXISTS_SHORT_HEADERSIZEOFRXCONTAINERPDU == STD_ON) || (IPDUM_EXISTS_LONG_HEADERSIZEOFRXCONTAINERPDU == STD_ON))
/*******************************************************************************************
*  IpduM_Container_ReadHeader()
*******************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
LOCAL_INLINE FUNC(IpduM_ContainedPduHeaderType, IPDUM_CODE) IpduM_Container_ReadHeader(P2CONST(uint8, AUTOMATIC, IPDUM_APPL_DATA) pContainerBuf, uint32 headerSize)
{
  IpduM_ContainedPduHeaderType header;
  
  header.headerId = 0;
  header.dlc = 0;

# if((IPDUM_EXISTS_SHORT_HEADERSIZEOFRXCONTAINERPDU == STD_ON) || (IPDUM_EXISTS_SHORT_HEADERSIZEOFTXCONTAINERPDU == STD_ON))
  if(headerSize == IPDUM_HEADERSIZE_SMALL) /* COV_IPDUM_SINGLE_HEADERSIZE_CONFIG */
  {
    /* short header */
    SchM_Enter_IpduM_IPDUM_EXCLUSIVE_AREA_0();
#  if (IPDUM_HEADER_BYTE_ORDER == IPDUM_LITTLE_ENDIAN)
    /* *INDENT-OFF* */
    header.headerId =
      (((uint32) pContainerBuf[0]) << 0) |  /* PRQA S 2985 */ /* MD_IpduM_2985 */  /* VCA_IPDUM_ARRAY_READ_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */
      (((uint32) pContainerBuf[1]) << 8) | /* VCA_IPDUM_ARRAY_READ_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */
      (((uint32) pContainerBuf[2]) << 16); /* VCA_IPDUM_ARRAY_READ_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */
    header.dlc = ((uint32) pContainerBuf[3]); /* VCA_IPDUM_ARRAY_READ_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */
    /* *INDENT-ON* */
#  else /* (IPDUM_HEADER_BYTE_ORDER == IPDUM_BIG_ENDIAN) */
    /* *INDENT-OFF* */
    header.headerId =
      (((uint32) pContainerBuf[0]) << 16) | /* VCA_IPDUM_ARRAY_READ_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */
      (((uint32) pContainerBuf[1]) << 8) | /* VCA_IPDUM_ARRAY_READ_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */
      (((uint32) pContainerBuf[2]) << 0);  /* PRQA S 2985 */ /* MD_IpduM_2985 */  /* VCA_IPDUM_ARRAY_READ_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */
    header.dlc = (((uint32) pContainerBuf[3]) << 0);  /* PRQA S 2985 */ /* MD_IpduM_2985 */  /* VCA_IPDUM_ARRAY_READ_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */
    /* *INDENT-ON* */
#  endif
    SchM_Exit_IpduM_IPDUM_EXCLUSIVE_AREA_0();
  }
# endif
# if((IPDUM_EXISTS_LONG_HEADERSIZEOFRXCONTAINERPDU == STD_ON) || (IPDUM_EXISTS_LONG_HEADERSIZEOFTXCONTAINERPDU == STD_ON))
  if(headerSize == IPDUM_HEADERSIZE_LARGE) /* COV_IPDUM_SINGLE_HEADERSIZE_CONFIG */
  {
    /* long header */
    SchM_Enter_IpduM_IPDUM_EXCLUSIVE_AREA_0();
#  if (IPDUM_HEADER_BYTE_ORDER == IPDUM_LITTLE_ENDIAN)
    /* *INDENT-OFF* */
    header.headerId =
      (((uint32) pContainerBuf[0]) << 0) |  /* PRQA S 2985 */ /* MD_IpduM_2985 */  /* VCA_IPDUM_ARRAY_READ_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */
      (((uint32) pContainerBuf[1]) << 8) | /* VCA_IPDUM_ARRAY_READ_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */
      (((uint32) pContainerBuf[2]) << 16) | /* VCA_IPDUM_ARRAY_READ_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */
      (((uint32) pContainerBuf[3]) << 24); /* VCA_IPDUM_ARRAY_READ_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */
    header.dlc =
      (((uint32) pContainerBuf[4]) << 0) |  /* PRQA S 2985 */ /* MD_IpduM_2985 */  /* VCA_IPDUM_ARRAY_READ_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */
      (((uint32) pContainerBuf[5]) << 8) | /* VCA_IPDUM_ARRAY_READ_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */
      (((uint32) pContainerBuf[6]) << 16) | /* VCA_IPDUM_ARRAY_READ_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */
      (((uint32) pContainerBuf[7]) << 24); /* VCA_IPDUM_ARRAY_READ_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */
    /* *INDENT-ON* */
#  else /* (IPDUM_HEADER_BYTE_ORDER == IPDUM_BIG_ENDIAN) */
    /* *INDENT-OFF* */
    header.headerId =
      (((uint32) pContainerBuf[0]) << 24) | /* VCA_IPDUM_ARRAY_READ_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */
      (((uint32) pContainerBuf[1]) << 16) | /* VCA_IPDUM_ARRAY_READ_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */
      (((uint32) pContainerBuf[2]) << 8) | /* VCA_IPDUM_ARRAY_READ_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */
      (((uint32) pContainerBuf[3]) << 0);  /* PRQA S 2985 */ /* MD_IpduM_2985 */  /* VCA_IPDUM_ARRAY_READ_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */
    header.dlc =
      (((uint32) pContainerBuf[4]) << 24) | /* VCA_IPDUM_ARRAY_READ_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */
      (((uint32) pContainerBuf[5]) << 16) | /* VCA_IPDUM_ARRAY_READ_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */
      (((uint32) pContainerBuf[6]) << 8) | /* VCA_IPDUM_ARRAY_READ_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */
      (((uint32) pContainerBuf[7]) << 0);  /* PRQA S 2985 */ /* MD_IpduM_2985 */  /* VCA_IPDUM_ARRAY_READ_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER */
    /* *INDENT-ON* */
#  endif
    SchM_Exit_IpduM_IPDUM_EXCLUSIVE_AREA_0();
  }
# endif
  IPDUM_DUMMY_STATEMENT(headerSize);    /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  IPDUM_DUMMY_STATEMENT(pContainerBuf);    /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  return header;
}
#endif

# if((IPDUM_EXISTS_SHORT_HEADERSIZEOFRXCONTAINERPDU == STD_ON) || (IPDUM_EXISTS_LONG_HEADERSIZEOFRXCONTAINERPDU == STD_ON))
/*******************************************************************************************
 *  IpduM_ContainerRx_GetHeaderSize()
*******************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
LOCAL_INLINE FUNC(uint8, IPDUM_CODE) IpduM_ContainerRx_GetHeaderSize(IpduM_RxContainerPduIterType rxContainerId)
{
  uint8 headerSize = 0;
# if (IPDUM_EXISTS_LONG_HEADERSIZEOFRXCONTAINERPDU == STD_ON)
  if(IpduM_GetHeaderSizeOfRxContainerPdu(rxContainerId) == IPDUM_LONG_HEADERSIZEOFRXCONTAINERPDU) /* COV_IPDUM_SINGLE_HEADERSIZE_CONFIG */
  {
    headerSize = IPDUM_HEADERSIZE_LARGE;
  }
# endif
# if (IPDUM_EXISTS_SHORT_HEADERSIZEOFRXCONTAINERPDU == STD_ON)
  if(IpduM_GetHeaderSizeOfRxContainerPdu(rxContainerId) == IPDUM_SHORT_HEADERSIZEOFRXCONTAINERPDU) /* COV_IPDUM_SINGLE_HEADERSIZE_CONFIG */
  {
    headerSize = IPDUM_HEADERSIZE_SMALL;
  }
# endif
  IPDUM_DUMMY_STATEMENT(rxContainerId);    /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  return headerSize;
}
#endif

#if (IPDUM_TXCONTAINEDPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTx_GetHeaderSize()
*******************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
LOCAL_INLINE FUNC(uint8, IPDUM_CODE) IpduM_ContainerTx_GetHeaderSize(IpduM_CTxContainerPduIterType txContainerId)
{
  uint8 headerSize = 0;
# if (IPDUM_EXISTS_LONG_HEADERSIZEOFTXCONTAINERPDU == STD_ON)
  if(IpduM_GetHeaderSizeOfTxContainerPdu(txContainerId) == IPDUM_LONG_HEADERSIZEOFTXCONTAINERPDU) /* PRQA S 2842 */ /* MD_IpduM_2842 */ /* COV_IPDUM_SINGLE_HEADERSIZE_CONFIG */
  {
    headerSize = IPDUM_HEADERSIZE_LARGE;
  }
# endif
# if (IPDUM_EXISTS_SHORT_HEADERSIZEOFTXCONTAINERPDU == STD_ON)
  if(IpduM_GetHeaderSizeOfTxContainerPdu(txContainerId) == IPDUM_SHORT_HEADERSIZEOFTXCONTAINERPDU) /* PRQA S 2842 */ /* MD_IpduM_2842 */ /* COV_IPDUM_SINGLE_HEADERSIZE_CONFIG */
  {
    headerSize = IPDUM_HEADERSIZE_SMALL;
  }
# endif

  return headerSize;
}
#endif

#if (IPDUM_TXCONTAINEDPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTx_GetStartAddrOfCurrentlyWrittenContainerPdu()
*******************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
LOCAL_INLINE FUNC(IpduM_ContainerTxBufferPtrType, IPDUM_CODE) IpduM_ContainerTx_GetStartAddrOfCurrentlyWrittenContainerPdu(IpduM_CTxContainerPduIterType txContainerId)
{
  IpduM_ContainerTxBufferStartIdxOfTxContainerPduType bufferStartPos = IpduM_GetContainerTxBufferStartIdxOfTxContainerPdu(txContainerId); /* PRQA S 2842 */ /* MD_IpduM_2842 */
  IpduM_ContainerWriteIdxOfTxContainerPduType containerWriteIdx = IpduM_GetContainerWriteIdxOfTxContainerPdu(txContainerId); /* PRQA S 2842 */ /* MD_IpduM_2842 */
  IpduM_LengthOfTxContainerPduType bufferInstanceLength = IpduM_GetLengthOfTxContainerPdu(txContainerId); /* PRQA S 2842 */ /* MD_IpduM_2842 */
  IpduM_ContainerTxBufferIterType containerTxBufferIdx = bufferStartPos + (containerWriteIdx * bufferInstanceLength);
  IpduM_ContainerTxBufferPtrType pContainerTxBuf = IpduM_GetAddrContainerTxBuffer(bufferStartPos);

  if(containerTxBufferIdx < IpduM_GetSizeOfContainerTxBuffer())  /* COV_IPDUM_DEFENSIVE_PROGRAMMING */
  {
    pContainerTxBuf = IpduM_GetAddrContainerTxBuffer(containerTxBufferIdx);
  }

  return pContainerTxBuf;
}
#endif

#if (IPDUM_TXCONTAINEDPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTx_GetStartAddrOfCurrentlyReadContainerPdu()
*******************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
LOCAL_INLINE FUNC(IpduM_ContainerTxBufferPtrType, IPDUM_CODE) IpduM_ContainerTx_GetStartAddrOfCurrentlyReadContainerPdu(IpduM_CTxContainerPduIterType txContainerId)
{
  IpduM_ContainerTxBufferStartIdxOfTxContainerPduType bufferStartPos = IpduM_GetContainerTxBufferStartIdxOfTxContainerPdu(txContainerId); /* PRQA S 2842 */ /* MD_IpduM_2842 */
  IpduM_ContainerWriteIdxOfTxContainerPduType containerReadIdx = IpduM_GetContainerReadIdxOfTxContainerPdu(txContainerId); /* PRQA S 2842 */ /* MD_IpduM_2842 */
  IpduM_LengthOfTxContainerPduType bufferInstanceLength = IpduM_GetLengthOfTxContainerPdu(txContainerId); /* PRQA S 2842 */ /* MD_IpduM_2842 */
  IpduM_ContainerTxBufferIterType containerTxBufferIdx = bufferStartPos + (containerReadIdx * bufferInstanceLength);
  IpduM_ContainerTxBufferPtrType pContainerTxBuf = IpduM_GetAddrContainerTxBuffer(bufferStartPos);

  if(containerTxBufferIdx < IpduM_GetSizeOfContainerTxBuffer())  /* COV_IPDUM_DEFENSIVE_PROGRAMMING */
  {
    pContainerTxBuf = IpduM_GetAddrContainerTxBuffer(containerTxBufferIdx);
  }

  return pContainerTxBuf;
}
#endif

#if (IPDUM_TXCONTAINEDPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTx_GetTransmittedPduLength
*******************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
LOCAL_INLINE FUNC(PduLengthType, IPDUM_CODE) IpduM_ContainerTx_GetTransmittedPduLength(IpduM_CTxContainerPduIterType txContainerId, P2VAR(uint8, AUTOMATIC, IPDUM_APPL_DATA) dataPtr)
{
  PduLengthType pduLength;

# if (IPDUM_EXISTS_NONE_HEADERSIZEOFTXCONTAINERPDU == STD_ON)
  if(IpduM_GetHeaderSizeOfTxContainerPdu(txContainerId) == IPDUM_NONE_HEADERSIZEOFTXCONTAINERPDU) /* PRQA S 2842 */ /* MD_IpduM_2842 */
  {
    pduLength = (PduLengthType) IpduM_GetLengthOfTxContainerPdu(txContainerId);
  }
  else
# endif
  {
    PduInfoType pduInfo;

    pduInfo.SduDataPtr = dataPtr;
    pduInfo.SduLength = (PduLengthType) IpduM_GetLengthOfTxContainerPdu(txContainerId);

    pduLength = (PduLengthType) IpduM_CalculateSizeOfContainer((PduLengthType) IpduM_ContainerTx_GetHeaderSize(txContainerId), &pduInfo); /* SBSW_IPDUM_TRANSMITCURRCONTAINERPDU_CALL_CALCULATESIZEOFCONTAINER */
  }

  return pduLength;
}
#endif

#if (IPDUM_TXCONTAINEDPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTx_DataQueue_TerminateContainer()
*******************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_ContainerTx_DataQueue_TerminateContainer(IpduM_CTxContainerPduIterType txContainerId)
{
  IpduM_ContainerTxBufferIterType containerBufId;
  uint8 headerSize = IpduM_ContainerTx_GetHeaderSize(txContainerId);
  IpduM_LengthOfTxContainerPduType bufferInstanceLength = IpduM_GetLengthOfTxContainerPdu(txContainerId);
  IpduM_ContainerTxBufferStartIdxOfTxContainerPduType bufferStartPos = IpduM_GetContainerTxBufferStartIdxOfTxContainerPdu(txContainerId);
  PduLengthType bufferOffset = (PduLengthType)(bufferStartPos + (IpduM_GetContainerWriteIdxOfTxContainerPdu(txContainerId) * bufferInstanceLength));
  IpduM_ContainerTxBufferPtrType pSrc = IpduM_ContainerTx_GetStartAddrOfCurrentlyWrittenContainerPdu(txContainerId);

  /* add zero header for safe PDU termination */
  for(containerBufId = (IpduM_ContainerTxBufferIterType) IpduM_GetContainedPduWriteIdxOfTxContainerPdu(txContainerId); (containerBufId < bufferInstanceLength) && (containerBufId < (IpduM_GetContainedPduWriteIdxOfTxContainerPdu(txContainerId) + headerSize)); containerBufId++) /* COV_IPDUM_TERMINATION_ZEROES */
  {
    if(IpduM_GetSizeOfContainerTxBuffer() > (containerBufId + bufferOffset)) /* COV_IPDUM_DEFENSIVE_PROGRAMMING */
    {
      pSrc[containerBufId] = 0; /* SBSW_IPDUM_CONTAINERRXINDICATION_MEMORY_WRITE */
    }
  }
}
#endif

#if (IPDUM_TXCONTAINEDPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTx_DataQueue_CloseCurrentContainerInstance()
*******************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_ContainerTx_DataQueue_CloseCurrentContainerInstance(IpduM_CTxContainerPduIterType txContainerId)
{
# if (IPDUM_EXISTS_NONE_HEADERSIZEOFTXCONTAINERPDU == STD_ON)
  if(IpduM_GetHeaderSizeOfTxContainerPdu(txContainerId) != IPDUM_NONE_HEADERSIZEOFTXCONTAINERPDU) /* PRQA S 2842 */ /* MD_IpduM_2842 */
# endif
  {
    IpduM_ContainerTx_DataQueue_TerminateContainer(txContainerId);
  }
}
#endif

#if (IPDUM_TXCONTAINEDPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTx_CopyTxConfirmationsOfCurrentlyReadContainer2LastBuffer()
*******************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_ContainerTx_CopyTxConfirmationsOfCurrentlyReadContainer2LastBuffer(IpduM_CTxContainerPduIterType txContainerId)
{
  IpduM_ContainerTxConfBufStartIdxOfTxContainerPduType bufferStartIdx = IpduM_GetContainerTxConfBufStartIdxOfTxContainerPdu(txContainerId); /* PRQA S 2842 */ /* MD_IpduM_2842 */
  IpduM_ContainerTxConfBuInLenOfTxContainerPduType confirmationBufferInstanceLength = IpduM_GetContainerTxConfBuInLenOfTxContainerPdu(txContainerId); /* PRQA S 2842 */ /* MD_IpduM_2842 */
  IpduM_ContainerWriteIdxOfTxContainerPduType currentInstance = IpduM_GetContainerReadIdxOfTxContainerPdu(txContainerId); /* PRQA S 2842 */ /* MD_IpduM_2842 */
  IpduM_ContainerTxConfLastPtrType lastTxConfirmationIdBuffer = IpduM_GetAddrContainerTxConfLast(IpduM_GetContainerTxConfLastStartIdxOfTxContainerPdu(txContainerId)); /* PRQA S 2842 */ /* MD_IpduM_2842 */
  IpduM_ContainerTxConfBufPtrType txConfirmationIdBuffer = IpduM_GetAddrContainerTxConfBuf(bufferStartIdx + (currentInstance * confirmationBufferInstanceLength));
  IpduM_ContainerTxConfBuIdIterType containerTxConfBuIdx  = IpduM_GetContainerTxConfBuIdStartIdxOfTxContainerPdu(txContainerId) + currentInstance;

  /* copy transmitted PDU IDs to the "last transmitted ID buffer" and reset the source buffer */
  VStdMemCpyRamToRam(lastTxConfirmationIdBuffer, txConfirmationIdBuffer, confirmationBufferInstanceLength); /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_IPDUM_TRANSMIT_CURR_CONTAINER_PDU_MEMCPY */ /* VCA_IPDUM_VSTDLIB_MEMCPY */
  IpduM_SetContainerTxConfLaIdOfTxContainerPdu(txContainerId, IpduM_GetContainerTxConfBuId(containerTxConfBuIdx)); /* PRQA S 2842 */ /* MD_IpduM_2842 */ /* SBSW_IPDUM_INDIRECT_ACCESS_FROM_EXTERNAL_PARAMETER */
}
#endif

#if (IPDUM_TXCONTAINEDPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTx_DataQueue_RemoveOldestPdu()
*******************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_ContainerTx_DataQueue_RemoveOldestPdu(IpduM_CTxContainerPduIterType txContainerId)
{
  IpduM_CountOfTxContainerPduType bufferInstanceCount = IpduM_GetCountOfTxContainerPdu(txContainerId); /* PRQA S 2842 */ /* MD_IpduM_2842 */

# if (IPDUM_EXISTS_NONE_HEADERSIZEOFTXCONTAINERPDU == STD_ON)
  if(IpduM_GetHeaderSizeOfTxContainerPdu(txContainerId) == IPDUM_NONE_HEADERSIZEOFTXCONTAINERPDU) /* PRQA S 2842 */ /* MD_IpduM_2842 */
  {
    /* re-init current instance for later writing */
    IpduM_ContainerTx_DataQueue_ResetNoneHeaderContainerInstance(txContainerId, (PduLengthType) IpduM_GetContainerReadIdxOfTxContainerPdu(txContainerId)); /* PRQA S 2842 */ /* MD_IpduM_2842 */
  }
# endif

  {
    /* Reset the corresponding TxConfirmation buffer write Idx. This basically resets the corresponding TxConfirmation buffer. */
    IpduM_ContainerTxConfBuIdIterType containerTxConfBuIdx = IpduM_GetContainerTxConfBuIdStartIdxOfTxContainerPdu(txContainerId) + IpduM_GetContainerReadIdxOfTxContainerPdu(txContainerId);
    IpduM_SetContainerTxConfBuId(containerTxConfBuIdx, 0); /* SBSW_IPDUM_INDIRECT_ACCESS_FROM_EXTERNAL_PARAMETER */
  }

  /* increment read pointer */
  IpduM_IncContainerReadCountOfTxContainerPdu(txContainerId); /* SBSW_IPDUM_CSL01 */
  IpduM_IncContainerReadIdxOfTxContainerPdu(txContainerId); /* SBSW_IPDUM_CSL01 */
  if(IpduM_GetContainerReadIdxOfTxContainerPdu(txContainerId) >= bufferInstanceCount)
  {
    IpduM_SetContainerReadIdxOfTxContainerPdu(txContainerId, 0u); /* SBSW_IPDUM_CSL01 */

  }
}
#endif

#if (IPDUM_TXCONTAINEDPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTx_DataQueue_IsFifoQueueEmpty
*******************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
LOCAL_INLINE FUNC(boolean, IPDUM_CODE) IpduM_ContainerTx_DataQueue_IsFifoQueueEmpty(IpduM_CTxContainerPduIterType txContainerId)
{
  boolean retVal = FALSE;

  if( (IpduM_ContainerWriteCountOfTxContainerPduType) (IpduM_GetContainerWriteCountOfTxContainerPdu(txContainerId) - IpduM_GetContainerReadCountOfTxContainerPdu(txContainerId)) == 0u)
  {
    retVal = TRUE;
  }

  return retVal;
}
#endif

#if (IPDUM_TXCONTAINEDPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTx_DataQueue_IsFifoQueueFull
*******************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
LOCAL_INLINE FUNC(boolean, IPDUM_CODE) IpduM_ContainerTx_DataQueue_IsFifoQueueFull(IpduM_CTxContainerPduIterType txContainerId)
{
  boolean retVal = FALSE;
  /* Count is the queue depth from the configuration incremented by 1. */
  IpduM_CountOfTxContainerPduType queueDepth = IpduM_GetCountOfTxContainerPdu(txContainerId) - 1u; /* PRQA S 2842 */ /* MD_IpduM_2842 */
  IpduM_ContainerWriteCountOfTxContainerPduType containerWriteCount = IpduM_GetContainerWriteCountOfTxContainerPdu(txContainerId); /* PRQA S 2842 */ /* MD_IpduM_2842 */
  IpduM_ContainerReadCountOfTxContainerPduType containerReadCount = IpduM_GetContainerReadCountOfTxContainerPdu(txContainerId); /* PRQA S 2842 */ /* MD_IpduM_2842 */

  if( (IpduM_ContainerWriteCountOfTxContainerPduType) (containerWriteCount - containerReadCount) >= queueDepth)
  {
    retVal = TRUE;
  }

  return retVal;
}
#endif

#if (IPDUM_TXCONTAINEDPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTx_DataQueue_FitsPduIntoCurrentOpenInstance
*******************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
LOCAL_INLINE FUNC(boolean, IPDUM_CODE) IpduM_ContainerTx_DataQueue_FitsPduIntoCurrentOpenInstance(IpduM_CTxContainerPduIterType txContainerId, PduLengthType pduLength)
{
  return (boolean) ((IpduM_GetContainedPduWriteIdxOfTxContainerPdu(txContainerId) + IpduM_ContainerTx_GetHeaderSize(txContainerId) + pduLength) <= IpduM_GetLengthOfTxContainerPdu(txContainerId));
}
#endif

#if ((IPDUM_TXLOINFOUSEDOFTXCONTAINERPDU == STD_ON) && (IPDUM_TXCONFIRMATIONTIMEOUTOFTXCONTAINERPDU == STD_ON))
/*******************************************************************************************
 *  IpduM_ContainerTx_StartTxConfirmationTimeout()
*******************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_ContainerTx_StartTxConfirmationTimeout(IpduM_CTxContainerPduIterType txContainerId)
{
  if(IpduM_IsTxLoInfoUsedOfTxContainerPdu(txContainerId)) /* PRQA S 2842 */ /* MD_IpduM_2842 */ /* COV_IPDUM_TXCONF_ALWAYS_ZERO */
  {
    /* Load timeout counter */
    IpduM_SetTxConfTimeoutCntOfVTxLoInfoOfTxLoInfoWithInvalidIndexes(IpduM_GetTxLoInfoIdxOfTxContainerPdu(txContainerId), IpduM_GetTxConfirmationTimeoutOfTxContainerPdu(txContainerId)); /* PRQA S 2842 */ /* MD_IpduM_2842 */ /* SBSW_IPDUM_CSL03 */
  }
}
#endif

#if ((IPDUM_TXLOINFOUSEDOFTXCONTAINERPDU == STD_ON) && (IPDUM_TXCONFIRMATIONTIMEOUTOFTXCONTAINERPDU == STD_ON))
/*******************************************************************************************
 *  IpduM_ContainerTx_StopTxConfirmationTimeout()
*******************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_ContainerTx_StopTxConfirmationTimeout(IpduM_CTxContainerPduIterType txContainerId)
{
  if(IpduM_IsTxLoInfoUsedOfTxContainerPdu(txContainerId)) /* PRQA S 2842 */ /* MD_IpduM_2842 */ /* COV_IPDUM_TXCONF_ALWAYS_ZERO */
  {
    /* Reset timeout counter */
    IpduM_SetTxConfTimeoutCntOfVTxLoInfoOfTxLoInfoWithInvalidIndexes(IpduM_GetTxLoInfoIdxOfTxContainerPdu(txContainerId), IPDUM_RESET); /* PRQA S 2842 */ /* MD_IpduM_2842 */ /* SBSW_IPDUM_CSL03 */
  }
}
#endif

#if (IPDUM_TXCONTAINEDPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTx_TransmitPduAndHandleTxConfTimeout
*******************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
LOCAL_INLINE FUNC(Std_ReturnType, IPDUM_CODE) IpduM_ContainerTx_TransmitPduAndHandleTxConfTimeout(IpduM_CTxContainerPduIterType txContainerId, P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr)
{
  Std_ReturnType transmitResult;

# if ((IPDUM_TXLOINFOUSEDOFTXCONTAINERPDU == STD_ON) && (IPDUM_TXCONFIRMATIONTIMEOUTOFTXCONTAINERPDU == STD_ON))
#  if (IPDUM_TRIGGERTRANSMITOFTXCONTAINERPDU == STD_ON)
  if(!IpduM_IsTriggerTransmitOfTxContainerPdu(txContainerId))
#  endif
  {
    IpduM_ContainerTx_StartTxConfirmationTimeout(txContainerId);
  }
# endif

  transmitResult = PduR_IpduMTransmit(IpduM_GetTxContainerPduRefOfTxContainerPdu(txContainerId), PduInfoPtr); /* PRQA S 2842 */ /* MD_IpduM_2842 */ /* SBSW_IPDUM_TRANSMITCURRCONTAINERPDU_CALL_PDURTRANSMIT */ /* VCA_IPDUM_FUNCTIONCALL_PDUINFOPTR_SELF_CONSTRUCTED */

# if ((IPDUM_TXLOINFOUSEDOFTXCONTAINERPDU == STD_ON) && (IPDUM_TXCONFIRMATIONTIMEOUTOFTXCONTAINERPDU == STD_ON))
  if(transmitResult == E_NOT_OK)
  {
    IpduM_ContainerTx_StopTxConfirmationTimeout(txContainerId);
  }
# endif

  return transmitResult;
}
#endif

#if (IPDUM_TX_CONFIRMATION_API == STD_ON && IPDUM_EXISTS_CONTAINER_PATHWAYTYPEOFCTXLOINFO == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTx_WriteContainedPduIdToTxConfirmationBuffer()
*******************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_ContainerTx_WriteContainedPduIdToTxConfirmationBuffer(IpduM_TxUpIndIdxOfTxUpInfoType txContainedId)
{
  IpduM_CTxContainerPduIterType txContainerId = IpduM_GetTxContainerPduIdxOfTxContainedPdu(txContainedId);

  IpduM_ContainerTxConfBufStartIdxOfTxContainerPduType bufferStartIdx = IpduM_GetContainerTxConfBufStartIdxOfTxContainerPdu(txContainerId);
  IpduM_ContainerWriteIdxOfTxContainerPduType currentInstance = IpduM_GetContainerWriteIdxOfTxContainerPdu(txContainerId);

  IpduM_ContainerTxConfBuInLenOfTxContainerPduType confirmationBufferInstanceLength = IpduM_GetContainerTxConfBuInLenOfTxContainerPdu(txContainerId);
  IpduM_ContainerTxConfBuIdIterType containerTxConfBuIdx = IpduM_GetContainerTxConfBuIdStartIdxOfTxContainerPdu(txContainerId) + currentInstance;
  /* Fallback: get instance 0 */
  IpduM_ContainerTxConfBuIdType bufferInstanceWriteOffset = IpduM_GetContainerTxConfBuId(IpduM_GetContainerTxConfBuIdStartIdxOfTxContainerPdu(txContainerId));
  IpduM_ContainerTxConfBufIterType containerTxConfBufIdx;

  /* If the calculated offset with instance offset fits, use this */
  if(containerTxConfBuIdx < IpduM_GetSizeOfContainerTxConfBuId())  /* COV_IPDUM_DEFENSIVE_PROGRAMMING */
  {
    bufferInstanceWriteOffset = IpduM_GetContainerTxConfBuId(containerTxConfBuIdx);
  }

  containerTxConfBufIdx = bufferStartIdx + (currentInstance * confirmationBufferInstanceLength) + bufferInstanceWriteOffset;
  if(IpduM_GetSizeOfContainerTxConfBuf() > containerTxConfBufIdx) /* COV_IPDUM_DEFENSIVE_PROGRAMMING */
  {
    IpduM_SetContainerTxConfBuf(containerTxConfBufIdx, (PduIdType) txContainedId); /* SBSW_IPDUM_CONTAINER_TRANSMIT_INDIRECT_ACCESS */
  }

  if(bufferInstanceWriteOffset < (IpduM_ContainerTxConfBuIdType)confirmationBufferInstanceLength) /* COV_IPDUM_DEFENSIVE_PROGRAMMING */
  {
    /* buffer not yet full: increment to next position */
    if(containerTxConfBuIdx < IpduM_GetSizeOfContainerTxConfBuId())  /* COV_IPDUM_DEFENSIVE_PROGRAMMING */
    {
      IpduM_IncContainerTxConfBuId(containerTxConfBuIdx); /* SBSW_IPDUM_CONTAINER_TRANSMIT_INCREMENT_CALCULATED_POSITION */
    }
  }
}
#endif

#if (IPDUM_REQUESTQUEUEUSEDOFTXCONTAINERPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTx_RequestQueue_IsEmpty()
*******************************************************************************************/
/*! 
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
LOCAL_INLINE FUNC(boolean, IPDUM_CODE) IpduM_ContainerTx_RequestQueue_IsEmpty(IpduM_CTxContainerPduIterType txContainerId)
{
  /* if nothing is found (default), the result is true */
  boolean retVal = TRUE;

  IpduM_TxRequestQueueIndirectionStartIdxOfTxContainerPduType requestQueueIndirectionIterator = IpduM_GetTxRequestQueueIndirectionStartIdxOfTxContainerPdu(txContainerId);
  IpduM_TxRequestQueueIndirectionEndIdxOfTxContainerPduType requestQueueIndirectionEndIdx = IpduM_GetTxRequestQueueIndirectionEndIdxOfTxContainerPdu(txContainerId);
  /* loop over all priorities for this container */
  for(; requestQueueIndirectionIterator < requestQueueIndirectionEndIdx; requestQueueIndirectionIterator++)
  {
    IpduM_ReadIdxOfTxRequestQueueIndirectionType readIdx = IpduM_GetReadIdxOfTxRequestQueueIndirection(requestQueueIndirectionIterator);
    IpduM_ReadIdxOfTxRequestQueueIndirectionType writeIdx = IpduM_GetWriteIdxOfTxRequestQueueIndirection(requestQueueIndirectionIterator);
    
    /* If read and write Idx are the same, this queue is empty */
    if(readIdx != writeIdx)
    {
      /* there is data in the queue */
      retVal = FALSE;
      break;
    }
  }
  return retVal;
}
#endif

#if (IPDUM_REQUESTQUEUEUSEDOFTXCONTAINERPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTx_RequestQueue_ContainsPdu()
*******************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
LOCAL_INLINE FUNC(boolean, IPDUM_CODE) IpduM_ContainerTx_RequestQueue_ContainsPdu(IpduM_TxContainedPduIterType txContainedId)
{
  boolean retVal = FALSE;
  
  IpduM_TxRequestQueueIndirectionIdxOfTxContainedPduType requestQueueIndirectionIdx = IpduM_GetTxRequestQueueIndirectionIdxOfTxContainedPdu(txContainedId);
  IpduM_TxRequestQueueStartIdxOfTxRequestQueueIndirectionType requestQueueStartIdx = IpduM_GetTxRequestQueueStartIdxOfTxRequestQueueIndirection(requestQueueIndirectionIdx);
  IpduM_TxRequestQueueLengthOfTxRequestQueueIndirectionType requestQueueLength = IpduM_GetTxRequestQueueLengthOfTxRequestQueueIndirection(requestQueueIndirectionIdx);
  IpduM_ReadIdxOfTxRequestQueueIndirectionType readIdxIterator = IpduM_GetReadIdxOfTxRequestQueueIndirection(requestQueueIndirectionIdx);
  IpduM_ReadIdxOfTxRequestQueueIndirectionType writeIdx = IpduM_GetWriteIdxOfTxRequestQueueIndirection(requestQueueIndirectionIdx);
  IpduM_TxRequestQueuePtrType queue = IpduM_GetAddrTxRequestQueue(requestQueueStartIdx);
  
  while(readIdxIterator != writeIdx)
  {
    if(queue[readIdxIterator].id == txContainedId)
    {
      retVal = TRUE;
      break;
    }
    readIdxIterator++;
    if(readIdxIterator >= requestQueueLength)
    {
      readIdxIterator = 0u;
    }
  }
  return retVal;
}
#endif

#if (IPDUM_REQUESTQUEUEUSEDOFTXCONTAINERPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTx_RequestQueue_CalculateSize()
*******************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
LOCAL_INLINE FUNC(PduLengthType, IPDUM_CODE) IpduM_ContainerTx_RequestQueue_CalculateSize(IpduM_CTxContainerPduIterType txContainerId)
{
  PduLengthType sizeOfData = 0u;
  IpduM_TxRequestQueueIndirectionStartIdxOfTxContainerPduType indirectionIterator = IpduM_GetTxRequestQueueIndirectionStartIdxOfTxContainerPdu(txContainerId);
  IpduM_TxRequestQueueIndirectionEndIdxOfTxContainerPduType indirectionEnd = IpduM_GetTxRequestQueueIndirectionEndIdxOfTxContainerPdu(txContainerId);
  PduLengthType headerSize = (PduLengthType) IpduM_ContainerTx_GetHeaderSize(txContainerId);
  
  for(; indirectionIterator < indirectionEnd; indirectionIterator++)
  {
    IpduM_TxRequestQueueStartIdxOfTxRequestQueueIndirectionType requestQueueStartIdx = IpduM_GetTxRequestQueueStartIdxOfTxRequestQueueIndirection(indirectionIterator);
    IpduM_TxRequestQueueLengthOfTxRequestQueueIndirectionType requestQueueLength = IpduM_GetTxRequestQueueLengthOfTxRequestQueueIndirection(indirectionIterator);
    IpduM_ReadIdxOfTxRequestQueueIndirectionType readIdxIterator = IpduM_GetReadIdxOfTxRequestQueueIndirection(indirectionIterator);
    IpduM_WriteIdxOfTxRequestQueueIndirectionType writeIdx = IpduM_GetWriteIdxOfTxRequestQueueIndirection(indirectionIterator);
    IpduM_TxRequestQueuePtrType queue = IpduM_GetAddrTxRequestQueue(requestQueueStartIdx);
    
    while(readIdxIterator != writeIdx)
    {
      sizeOfData += queue[readIdxIterator].dlc;
      sizeOfData += headerSize;
      readIdxIterator++;
      if(readIdxIterator >= requestQueueLength)
      {
        readIdxIterator = 0u;
      }
    }
  }
  return sizeOfData;
}
#endif

#if (IPDUM_REQUESTQUEUEUSEDOFTXCONTAINERPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTx_RequestQueue_AddPdu()
*******************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_ContainerTx_RequestQueue_AddPdu(IpduM_TxContainedPduIterType txContainedId, PduLengthType sduLength)
{
  IpduM_TxRequestQueueIndirectionIdxOfTxContainedPduType requestQueueIndirectionIdx = IpduM_GetTxRequestQueueIndirectionIdxOfTxContainedPdu(txContainedId);
  IpduM_TxRequestQueueStartIdxOfTxRequestQueueIndirectionType requestQueueStartIdx = IpduM_GetTxRequestQueueStartIdxOfTxRequestQueueIndirection(requestQueueIndirectionIdx);
  IpduM_TxRequestQueueLengthOfTxRequestQueueIndirectionType requestQueueLength = IpduM_GetTxRequestQueueLengthOfTxRequestQueueIndirection(requestQueueIndirectionIdx);
  IpduM_ReadIdxOfTxRequestQueueIndirectionType writeIdx = IpduM_GetWriteIdxOfTxRequestQueueIndirection(requestQueueIndirectionIdx);
  IpduM_TxRequestQueuePtrType queue = IpduM_GetAddrTxRequestQueue(requestQueueStartIdx);
  
  if(IpduM_ContainerTx_RequestQueue_ContainsPdu(txContainedId) != TRUE)
  {
    /* add PDU to queue */
    queue[writeIdx].id = (PduIdType)txContainedId; /* SBSW_IPDUM_REQUESTQUEUE_WRITEIDX */
    queue[writeIdx].dlc = sduLength; /* SBSW_IPDUM_REQUESTQUEUE_WRITEIDX */
    writeIdx++;
    if(writeIdx >= requestQueueLength)
    {
      writeIdx = 0u;
    }
    IpduM_SetWriteIdxOfTxRequestQueueIndirection(requestQueueIndirectionIdx, writeIdx); /* SBSW_IPDUM_INDIRECT_ACCESS_FROM_EXTERNAL_PARAMETER */
  }
}
#endif

#if (IPDUM_FIRSTCONTAINEDPDUTRIGGEROFTXCONTAINERPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTx_TransmitEmptyPdu()
*******************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_ContainerTx_TransmitEmptyPdu(IpduM_CTxContainerPduIterType txContainerId)
{
  PduInfoType pduInfo;
  uint8 data = 0;
  /* The actual memory this pointer is pointing at doesn't matter, because the SduLength is zero. Must not be a NULL_PTR though. */
  pduInfo.SduDataPtr = &data;
  pduInfo.SduLength = 0u; /* PRQA S 2982 */ /* MD_IpduM_2982_initValue */
  (void) PduR_IpduMTransmit(IpduM_GetTxContainerPduRefOfTxContainerPdu(txContainerId), &pduInfo); /* SBSW_IPDUM_FUNCTIONCALL_PDUINFOPTR_EMPTY */ /* VCA_IPDUM_FUNCTIONCALL_PDUINFOPTR_SELF_CONSTRUCTED */
}
#endif

#if (IPDUM_REQUESTQUEUEUSEDOFTXCONTAINERPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTx_RequestQueue_RemoveLastTransmittedIds
*******************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_ContainerTx_RequestQueue_RemoveLastTransmittedIds(IpduM_CTxContainerPduIterType txContainerId)
{
  IpduM_TxRequestQueueIndirectionStartIdxOfTxContainerPduType indirectionIterator = IpduM_GetTxRequestQueueIndirectionStartIdxOfTxContainerPdu(txContainerId);
  IpduM_TxRequestQueueIndirectionEndIdxOfTxContainerPduType indirectionEnd = IpduM_GetTxRequestQueueIndirectionEndIdxOfTxContainerPdu(txContainerId);
  for(; indirectionIterator < indirectionEnd; indirectionIterator++)
  {
    IpduM_SetReadIdxOfTxRequestQueueIndirection(indirectionIterator, IpduM_GetReadTmpIdxOfTxRequestQueueIndirection(indirectionIterator)); /* SBSW_IPDUM_INDIRECT_ACCESS_FROM_EXTERNAL_PARAMETER */
  }
}
#endif

#if (IPDUM_REQUESTQUEUEUSEDOFTXCONTAINERPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTx_RequestQueue_FillLastIsBestContainer()
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
 *
 */
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_ContainerTx_RequestQueue_FillLastIsBestContainer(IpduM_CTxContainerPduIterType txContainerId)
{
  IpduM_LengthOfTxContainerPduType bufferInstanceLength = IpduM_GetLengthOfTxContainerPdu(txContainerId);
  IpduM_TxRequestQueueIndirectionStartIdxOfTxContainerPduType indirectionIterator = IpduM_GetTxRequestQueueIndirectionStartIdxOfTxContainerPdu(txContainerId);
  IpduM_TxRequestQueueIndirectionEndIdxOfTxContainerPduType indirectionEnd = IpduM_GetTxRequestQueueIndirectionEndIdxOfTxContainerPdu(txContainerId);
  IpduM_ContainerTxConfLastPtrType txConfLast = IpduM_GetAddrContainerTxConfLast(IpduM_GetContainerTxConfLastStartIdxOfTxContainerPdu(txContainerId));
  IpduM_ContainerTxConfLastIterType txConfLastId = 0u;
  PduLengthType lastIsBestWriteIdx = 0u;
  PduLengthType headerSize = (PduLengthType) IpduM_ContainerTx_GetHeaderSize(txContainerId);
  PduLengthType containerBufId;
  
  for(; indirectionIterator < indirectionEnd; indirectionIterator++)
  {
    IpduM_ReadIdxOfTxRequestQueueIndirectionType readIdx = IpduM_GetReadIdxOfTxRequestQueueIndirection(indirectionIterator);
    IpduM_WriteIdxOfTxRequestQueueIndirectionType writeIdx = IpduM_GetWriteIdxOfTxRequestQueueIndirection(indirectionIterator);
    IpduM_TxRequestQueueStartIdxOfTxRequestQueueIndirectionType bufferStart = IpduM_GetTxRequestQueueStartIdxOfTxRequestQueueIndirection(indirectionIterator);
    IpduM_TxRequestQueuePtrType requestQueue = IpduM_GetAddrTxRequestQueue(bufferStart);
    
    while(readIdx != writeIdx)
    {
      /* get data for containedId and add to buffer */
      /* the remaining bytes in the "last is best" buffer */
      PduLengthType freeBytes = (PduLengthType)((uint32)bufferInstanceLength - (uint32)lastIsBestWriteIdx);
      PduLengthType containedPduLength = requestQueue[readIdx].dlc;

      if(freeBytes >= (headerSize + containedPduLength))
      {
        /* the requestQueue contains internal containedPduIds */
        PduIdType containedPduId = requestQueue[readIdx].id;

        if(containedPduId < IpduM_GetSizeOfTxContainedPdu()) /* COV_IPDUM_DEFENSIVE_PROGRAMMING */
        {
          PduInfoType pduInfo;
          pduInfo.SduDataPtr = IpduM_GetAddrContainerTxLIBBuffer(lastIsBestWriteIdx + headerSize);  /* data starts after the header */
          pduInfo.SduLength = freeBytes - headerSize; /* available size left in buffer */

          if(PduR_IpduMTriggerTransmit(IpduM_GetTxContainedPduRefOfTxContainedPdu(containedPduId), &pduInfo) == E_OK) /* SBSW_IPDUM_FUNCTIONCALL_PDUINFOPTR_SELF_CONSTRUCTED */ /* VCA_IPDUM_FUNCTIONCALL_PDUINFOPTR_SELF_CONSTRUCTED */
          {
            /* triggertransmit was successful, write header with correct size and increment write IDX */
            {
              IpduM_ContainedPduHeaderType newHeader;
              newHeader.headerId = IpduM_GetHeaderIdOfTxContainedPdu(containedPduId);
              newHeader.dlc = pduInfo.SduLength;        /* updated value from TriggerTransmit call */
              IpduM_ContainerTx_WriteHeader(IpduM_GetAddrContainerTxLIBBuffer(lastIsBestWriteIdx), &newHeader, headerSize, freeBytes); /* SBSW_IPDUM_FILLLASTISBEST_CALL_CONTAINERWRITEHEADER */
            }

            /* write id to TxConfirmation last ID buffer */
            if(IpduM_GetSizeOfContainerTxConfLast() > (txConfLastId + IpduM_GetContainerTxConfLastStartIdxOfTxContainerPdu(txContainerId))) /* COV_IPDUM_DEFENSIVE_PROGRAMMING */
            {
              txConfLast[txConfLastId] = containedPduId; /* SBSW_IPDUM_CSL01 */
              txConfLastId++;
              IpduM_SetContainerTxConfLaIdOfTxContainerPdu(txContainerId, txConfLastId); /* PRQA S 2842 */ /* MD_IpduM_2842 */ /* SBSW_IPDUM_INDIRECT_ACCESS_FROM_EXTERNAL_PARAMETER */
            }

            /* Increment the write Index by the headerSize and actual written length of data */
            lastIsBestWriteIdx += (PduLengthType) (headerSize + pduInfo.SduLength);
          }
        }

        /* Remove last containedPdu. Is removed in both successful and not successful TriggerTransmit call. */
        readIdx++;
        if(readIdx >= IpduM_GetTxRequestQueueLengthOfTxRequestQueueIndirection(indirectionIterator))
        {
          readIdx = 0u;
        }
      }
      else
      {
        break;
      }
    }

    /* set temporary read index, this will be made permanent once the transmission was confirmed */
    IpduM_SetReadTmpIdxOfTxRequestQueueIndirection(indirectionIterator, readIdx); /* SBSW_IPDUM_INDIRECT_ACCESS_FROM_EXTERNAL_PARAMETER */
  }
  /* add zero header for safe PDU termination */
  for(containerBufId = lastIsBestWriteIdx; (containerBufId < IpduM_GetSizeOfContainerTxLIBBuffer()) && (containerBufId < (lastIsBestWriteIdx + headerSize)); containerBufId++)   /* COV_IPDUM_TERMINATION_ZEROES */
  {
    IpduM_ContainerTxLIBBufferPtrType lastIsBestBuffer = IpduM_GetAddrContainerTxLIBBuffer(containerBufId);
    lastIsBestBuffer[0] = 0; /* SBSW_IPDUM_FILLLASTISBEST_MEMORY_WRITE */
    IPDUM_DUMMY_STATEMENT(lastIsBestBuffer); /* PRQA S 1338, 2982, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  }
} /* PRQA S 6010, 6030, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STMIF */
#endif

#if ((IPDUM_TXCONTAINEDPDU == STD_ON) && (IPDUM_REQUESTQUEUEUSEDOFTXCONTAINERPDU == STD_ON))
/*******************************************************************************************
 *  IpduM_ContainerTx_RequestQueue_TransmitContainer()
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
 */
LOCAL_INLINE FUNC(Std_ReturnType, IPDUM_CODE) IpduM_ContainerTx_RequestQueue_TransmitContainer(IpduM_CTxContainerPduIterType txContainerId)
{
  Std_ReturnType transmitResult = E_NOT_OK;   /* PRQA S 2981 */ /* MD_MSR_RetVal */

# if ((IPDUM_TXLOINFOUSEDOFTXCONTAINERPDU == STD_ON) && (IPDUM_TXCONFIRMATIONTIMEOUTOFTXCONTAINERPDU == STD_ON))
  if((IpduM_GetTxConfirmationTimeoutOfTxContainerPdu(txContainerId) == 0u) || (IpduM_IsTxLoInfoUsedOfTxContainerPdu(txContainerId) && (IpduM_GetTxConfTimeoutCntOfVTxLoInfoOfTxLoInfoWithInvalidIndexes(IpduM_GetTxLoInfoIdxOfTxContainerPdu(txContainerId)) == 0u))) /* PRQA S 2842 */ /* MD_IpduM_2842 */ /* COV_IPDUM_DEPENDENT_VALUES */ /* COV_IPDUM_TXCONF_ALWAYS_ZERO */
# endif
  {
    {
      PduInfoType pduInfo;

#  if (IPDUM_TRIGGERTRANSMITOFTXCONTAINERPDU == STD_ON)
      if(IpduM_IsTriggerTransmitOfTxContainerPdu(txContainerId)) /* PRQA S 2842 */ /* MD_IpduM_2842 */
      {
        pduInfo.SduDataPtr = IpduM_GetAddrContainerTxLIBBuffer(0);
        pduInfo.SduLength  = 0;
      }
      else
#  endif
      {
        /* last-is-best PDU: load data to last-is-best buffer via TriggerTransmit, then use this buffer for transmission */
        IpduM_ContainerTx_RequestQueue_FillLastIsBestContainer(txContainerId); /* SBSW_IPDUM_TRANSMITCURRCONTAINERPDU_CALL_FILLLASTISBESTCONTAINER */
        pduInfo.SduDataPtr = IpduM_GetAddrContainerTxLIBBuffer(0);
        pduInfo.SduLength  = IpduM_ContainerTx_GetTransmittedPduLength(txContainerId, pduInfo.SduDataPtr);  /* SBSW_IPDUM_GETTRANSMITTEDPDULENGTH */
      }

      transmitResult = IpduM_ContainerTx_TransmitPduAndHandleTxConfTimeout(txContainerId, &pduInfo);  /* SBSW_IPDUM_TRANSMITCURRCONTAINERPDU_CALL_PDURTRANSMIT */

      if((transmitResult == E_OK)
# if (IPDUM_TRIGGERTRANSMITOFTXCONTAINERPDU == STD_ON)
         && (!IpduM_IsTriggerTransmitOfTxContainerPdu(txContainerId)) /* PRQA S 2842 */ /* MD_IpduM_2842 */
# endif
        )
      {
        IpduM_ContainerTx_RequestQueue_RemoveLastTransmittedIds(txContainerId);
      }
    }
  }

  return transmitResult;
}
#endif

#if (IPDUM_TXCONTAINEDPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTx_DataQueue_TransmitQueuedFIFOContainerPdu()
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
 */
LOCAL_INLINE FUNC(Std_ReturnType, IPDUM_CODE) IpduM_ContainerTx_DataQueue_TransmitQueuedFIFOContainerPdu(IpduM_CTxContainerPduIterType txContainerId)
{
  Std_ReturnType transmitResult = E_NOT_OK;

# if ((IPDUM_TXLOINFOUSEDOFTXCONTAINERPDU == STD_ON) && (IPDUM_TXCONFIRMATIONTIMEOUTOFTXCONTAINERPDU == STD_ON))
  if((IpduM_GetTxConfirmationTimeoutOfTxContainerPdu(txContainerId) == 0u) || (IpduM_IsTxLoInfoUsedOfTxContainerPdu(txContainerId) && (IpduM_GetTxConfTimeoutCntOfVTxLoInfoOfTxLoInfoWithInvalidIndexes(IpduM_GetTxLoInfoIdxOfTxContainerPdu(txContainerId)) == 0u))) /* PRQA S 2842 */ /* MD_IpduM_2842 */ /* COV_IPDUM_DEPENDENT_VALUES */ /* COV_IPDUM_TXCONF_ALWAYS_ZERO */
# endif
  {
    if(!IpduM_ContainerTx_DataQueue_IsFifoQueueEmpty(txContainerId))
    {
      {
        PduInfoType pduInfo;
        pduInfo.SduDataPtr = IpduM_ContainerTx_GetStartAddrOfCurrentlyReadContainerPdu(txContainerId);
        pduInfo.SduLength = IpduM_ContainerTx_GetTransmittedPduLength(txContainerId, pduInfo.SduDataPtr);  /* SBSW_IPDUM_GETTRANSMITTEDPDULENGTH */

        IpduM_ContainerTx_CopyTxConfirmationsOfCurrentlyReadContainer2LastBuffer(txContainerId);
          
        transmitResult = IpduM_ContainerTx_TransmitPduAndHandleTxConfTimeout(txContainerId, &pduInfo); /* SBSW_IPDUM_TRANSMITCURRCONTAINERPDU_CALL_PDURTRANSMIT */
      
        if((transmitResult == E_OK)
# if (IPDUM_TRIGGERTRANSMITOFTXCONTAINERPDU == STD_ON)
           && (!IpduM_IsTriggerTransmitOfTxContainerPdu(txContainerId)) /* PRQA S 2842 */ /* MD_IpduM_2842 */
# endif
          )
        {
          IpduM_ContainerTx_DataQueue_RemoveOldestPdu(txContainerId);
        }
      }
    }
  }

  return transmitResult;
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (IPDUM_TXCONTAINEDPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTx_DataQueue_QueueCurrContainerPdu()
*******************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_ContainerTx_DataQueue_QueueCurrContainerPdu(IpduM_CTxContainerPduIterType txContainerId)
{
  if(IpduM_ContainerTx_DataQueue_IsFifoQueueFull(txContainerId))
  {
# if (IPDUM_DEV_ERROR_REPORT == STD_ON)
    IpduM_Det_ReportError(IPDUM_APIID_TRANSMIT, IPDUM_E_QUEUEOVFL);
# endif
    IpduM_ContainerTx_DataQueue_RemoveOldestPdu(txContainerId);
  }

  IpduM_ContainerTx_DataQueue_CloseCurrentContainerInstance(txContainerId);

  /* Queue the container PDU (i.e. increment write pointer). */
  {
    IpduM_IncContainerWriteCountOfTxContainerPdu(txContainerId);      /* SBSW_IPDUM_CSL01 */
    IpduM_IncContainerWriteIdxOfTxContainerPdu(txContainerId);        /* SBSW_IPDUM_CSL01 */
    if(IpduM_GetContainerWriteIdxOfTxContainerPdu(txContainerId) >= IpduM_GetCountOfTxContainerPdu(txContainerId))
    {
      IpduM_SetContainerWriteIdxOfTxContainerPdu(txContainerId, 0u);  /* SBSW_IPDUM_CSL01 */
    }
    /* The new instance is empty, clear contained indices */
    IpduM_SetContainedPduWriteIdxOfTxContainerPdu(txContainerId, 0u); /* SBSW_IPDUM_CSL01 */
  }
}
#endif

#if (IPDUM_TXCONTAINEDPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTx_DataQueue_TriggerTransmissionOfCurrContainerPdu()
*******************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_ContainerTx_DataQueue_TriggerTransmissionOfCurrContainerPdu(IpduM_CTxContainerPduIterType txContainerId)
{
  boolean wasQueueEmpty = IpduM_ContainerTx_DataQueue_IsFifoQueueEmpty(txContainerId);

  IpduM_ContainerTx_DataQueue_QueueCurrContainerPdu(txContainerId);

  if(wasQueueEmpty)
  {
    (void) IpduM_ContainerTx_DataQueue_TransmitQueuedFIFOContainerPdu(txContainerId);
  }
}
#endif

#if (IPDUM_TXCONTAINEDPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTx_DataQueue_AddTxPduToCurrContainer()
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
 */
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_ContainerTx_DataQueue_AddTxPduToCurrContainer(IpduM_TxContainedPduIterType txContainedId, P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr)
{
  IpduM_CTxContainerPduIterType txContainerId = IpduM_GetTxContainerPduIdxOfTxContainedPdu(txContainedId);
  IpduM_ContainerTxBufferStartIdxOfTxContainerPduType bufferStartPos = IpduM_GetContainerTxBufferStartIdxOfTxContainerPdu(txContainerId); /* PRQA S 2842 */ /* MD_IpduM_2842 */
  IpduM_LengthOfTxContainerPduType bufferInstanceLength = IpduM_GetLengthOfTxContainerPdu(txContainerId); /* PRQA S 2842 */ /* MD_IpduM_2842 */

  uint8 headerSize = IpduM_ContainerTx_GetHeaderSize(txContainerId);

# if (IPDUM_EXISTS_NONE_HEADERSIZEOFTXCONTAINERPDU == STD_ON)
  if(IpduM_GetHeaderSizeOfTxContainerPdu(txContainerId) != IPDUM_NONE_HEADERSIZEOFTXCONTAINERPDU) /* PRQA S 2842 */ /* MD_IpduM_2842 */
# endif
  {
    /* PDUs with short or long header */
    IpduM_ContainedPduHeaderType header;

    PduLengthType bufferOffset = (PduLengthType) (bufferStartPos +
        (IpduM_GetContainerWriteIdxOfTxContainerPdu(txContainerId) * /* PRQA S 2842 */ /* MD_IpduM_2842 */
         bufferInstanceLength) + IpduM_GetContainedPduWriteIdxOfTxContainerPdu(txContainerId)); /* PRQA S 2842 */ /* MD_IpduM_2842 */

    header.headerId = IpduM_GetHeaderIdOfTxContainedPdu(txContainedId);
    header.dlc = PduInfoPtr->SduLength;

    /* Write the header to the buffer */
    IpduM_ContainerTx_WriteHeader(IpduM_GetAddrContainerTxBuffer(bufferOffset), &header, headerSize, (bufferInstanceLength - IpduM_GetContainedPduWriteIdxOfTxContainerPdu(txContainerId))); /* PRQA S 2842 */ /* MD_IpduM_2842 */ /* SBSW_IPDUM_ADDTXPDUTOCURRCONTAINER_CALL_CONTAINERWRITEHEADER */

    /* Write the sdu to the buffer */
    VStdLib_MemCpy_s(IpduM_GetAddrContainerTxBuffer(bufferOffset+headerSize), (PduLengthType) (IpduM_GetSizeOfContainerTxBuffer() - bufferOffset - headerSize), PduInfoPtr->SduDataPtr, PduInfoPtr->SduLength); /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_IPDUM_VSTDLIB_SAFE */  /* VCA_IPDUM_VSTDLIB_MEMCPY_SAFE */

    IpduM_SetContainedPduWriteIdxOfTxContainerPdu(txContainerId, IpduM_GetContainedPduWriteIdxOfTxContainerPdu(txContainerId) + headerSize + PduInfoPtr->SduLength);        /* SBSW_IPDUM_CSL01 */
  }
# if (IPDUM_EXISTS_NONE_HEADERSIZEOFTXCONTAINERPDU == STD_ON)
  else
  {
    /* PDUs with no headers and static layout */
    PduLengthType bufferOffset = (PduLengthType) (bufferStartPos + (IpduM_GetContainerWriteIdxOfTxContainerPdu(txContainerId) * bufferInstanceLength)); /* PRQA S 2842 */ /* MD_IpduM_2842 */

    /* Write the sdu to the buffer */
    VStdLib_MemCpy_s(IpduM_GetAddrContainerTxBuffer((PduLengthType)(bufferOffset + IpduM_GetOffsetOfTxContainedPdu(txContainedId))), (PduLengthType)(IpduM_GetSizeOfContainerTxBuffer() - bufferOffset - IpduM_GetOffsetOfTxContainedPdu(txContainedId)), PduInfoPtr->SduDataPtr, PduInfoPtr->SduLength); /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_IPDUM_VSTDLIB_SAFE */  /* VCA_IPDUM_VSTDLIB_MEMCPY_SAFE */

#  if (IPDUM_UPDATEBITUSEDOFTXCONTAINEDPDU == STD_ON)
    if(IpduM_IsUpdateBitUsedOfTxContainedPdu(txContainedId))
    {
      PduLengthType updateBitBytePos;
      uint8 updateBitSetPattern;

      /* Set update bit */
      updateBitBytePos = IpduM_GetUpdateIndicationBitPositionOfTxContainedPdu(txContainedId) >> 3u;
      updateBitSetPattern = (uint8) (0x01u << (IpduM_GetUpdateIndicationBitPositionOfTxContainedPdu(txContainedId) % 8u));
      if((updateBitBytePos < bufferInstanceLength) && ((bufferOffset + updateBitBytePos) <= IpduM_GetSizeOfContainerTxBuffer())) /* COV_IPDUM_DEFENSIVE_PROGRAMMING */
      {
        IpduM_ContainerTxBufferPtrType pContainerTxBuf = IpduM_GetAddrContainerTxBuffer(bufferOffset + updateBitBytePos);
        pContainerTxBuf[0] |= updateBitSetPattern; /* SBSW_IPDUM_ARRAY_WRITE_WITH_INDEX_CHECK */
      }
    }
#  endif

    /* Mark Pdu as non-empty */
    IpduM_SetContainedPduWriteIdxOfTxContainerPdu(txContainerId, 1); /* SBSW_IPDUM_CSL01 */  /* PRQA S 2842 */ /* MD_IpduM_2842 */
  }
# endif
}
#endif

#if (IPDUM_EXISTS_NONE_HEADERSIZEOFTXCONTAINERPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTx_DataQueue_ResetNoneHeaderContainerInstance()
*******************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
*******************************************************************************************/
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_ContainerTx_DataQueue_ResetNoneHeaderContainerInstance(IpduM_CTxContainerPduIterType txContainerId, PduLengthType txContainerInstance)
{
  IpduM_ContainerTxBufferStartIdxOfTxContainerPduType bufferStartPos = IpduM_GetContainerTxBufferStartIdxOfTxContainerPdu(txContainerId);
  IpduM_LengthOfTxContainerPduType bufferInstanceLength = IpduM_GetLengthOfTxContainerPdu(txContainerId);
  IpduM_ContainerTxBufferPtrType pContainerTxBuf = IpduM_GetAddrContainerTxBuffer(bufferStartPos);
  PduLengthType containerIterator;
  PduLengthType bufferOffset = (PduLengthType)(bufferStartPos + (txContainerInstance * bufferInstanceLength));

  if(bufferOffset < IpduM_GetSizeOfContainerTxBuffer())  /* COV_IPDUM_DEFENSIVE_PROGRAMMING */
  {
    pContainerTxBuf = IpduM_GetAddrContainerTxBuffer(bufferOffset);
  }

  for(containerIterator = 0u; (containerIterator < bufferInstanceLength) && (IpduM_GetSizeOfContainerTxBuffer() >= (containerIterator + bufferOffset)); containerIterator++) /* COV_IPDUM_DEFENSIVE_PROGRAMMING */
  {
    pContainerTxBuf[containerIterator] = IpduM_GetUnusedBitPatternOfTxContainerPdu(txContainerId); /* SBSW_IPDUM_CSL01 */
  }

# if (IPDUM_UPDATEBITUSEDOFTXCONTAINEDPDU == STD_ON)
  {
    PduLengthType updateBitBytePos;
    uint8 updateBitClearPattern;
    PduIdType containedPduIterator;

    for(containedPduIterator = IpduM_GetTxContainedPduStartIdxOfTxContainerPdu(txContainerId); containedPduIterator < IpduM_GetTxContainedPduEndIdxOfTxContainerPdu(txContainerId);
        containedPduIterator++)
    {
      if(IpduM_IsUpdateBitUsedOfTxContainedPdu(containedPduIterator))
      {
        updateBitBytePos = (PduLengthType) IpduM_GetUpdateIndicationBitPositionOfTxContainedPdu(containedPduIterator) >> (PduLengthType) 3u;
        updateBitClearPattern = (~(uint8) (0x01u << (IpduM_GetUpdateIndicationBitPositionOfTxContainedPdu(containedPduIterator) % 8u)));
        if(updateBitBytePos < (IpduM_GetSizeOfContainerTxBuffer() - bufferOffset)) /* COV_IPDUM_DEFENSIVE_PROGRAMMING */
        {
          pContainerTxBuf[updateBitBytePos] &= updateBitClearPattern; /* SBSW_IPDUM_CSL01 */
        }
      }
    }
  }
# endif
}
#endif

#if (IPDUM_RXCONTAINERPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerRx_UnpackContainerPdu()
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
 */
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_ContainerRx_UnpackContainerPdu(IpduM_RxContainerPduIterType rxContainerId, P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr, PduLengthType pduLength)
{
  PduLengthType containedPduIdx;

# if (IPDUM_EXISTS_NONE_HEADERSIZEOFRXCONTAINERPDU == STD_ON)
#  if((IPDUM_EXISTS_SHORT_HEADERSIZEOFRXCONTAINERPDU == STD_ON) || (IPDUM_EXISTS_LONG_HEADERSIZEOFRXCONTAINERPDU == STD_ON))
  if(IpduM_GetHeaderSizeOfRxContainerPdu(rxContainerId) != IPDUM_NONE_HEADERSIZEOFRXCONTAINERPDU)
#  endif
# endif
# if((IPDUM_EXISTS_SHORT_HEADERSIZEOFRXCONTAINERPDU == STD_ON) || (IPDUM_EXISTS_LONG_HEADERSIZEOFRXCONTAINERPDU == STD_ON))
  {
    uint8 headerSize = IpduM_ContainerRx_GetHeaderSize(rxContainerId);
    containedPduIdx = 0u;
    /* PDUs with long headers and short headers */
    /* loop over all contained-pdus */
    while((containedPduIdx + headerSize) <= pduLength)
    {
      IpduM_ContainedPduHeaderType header;      /* header.headerId; header.dlc */

      /* get header id and dlc of the contained PDU */
      header = IpduM_Container_ReadHeader(&(PduInfoPtr->SduDataPtr[containedPduIdx]), headerSize);       /* SBSW_IPDUM_FUNCTIONCALL_PDUINFOPTR_CHECKED_BY_CALLER */ /* VCA_PDUINFOPTR_SELF_CONSTRUCTED */

      /* Increment read idx to begin of pdu */
      containedPduIdx += headerSize;

      /* if header id == 0: break loop */
      if(header.headerId == 0u)
      {
        break;
      }
      if(((containedPduIdx) + header.dlc) <= pduLength)     /* COV_IPDUM_DEFENSIVE_PROGRAMMING */
      {
        /* look up the header id in IpduM_RxContainedPdu */
        IpduM_HeaderIdOfRxContainedPduType rxContainedPduId = IpduM_ContainerRx_SearchRxHeaderId(header.headerId, rxContainerId);
        if(rxContainedPduId < IpduM_GetSizeOfRxContainedPdu()) /* This check must not be removed, it implicitly checks whether the search found an ID */
        {
        /* check if either "accept all" is configured or PDU is configured for this container */
        if((IpduM_IsRxContainerPduUsedOfRxContainedPdu(rxContainedPduId) && (IpduM_GetRxContainerPduIdxOfRxContainedPdu(rxContainedPduId) == rxContainerId))  
#  if (IPDUM_ACCEPTALLPDUSOFRXCONTAINERPDU == STD_ON)
           || IpduM_IsAcceptAllPdusOfRxContainerPdu(rxContainerId)
#  endif
          ) /* COV_IPDUM_INVALID_CONFIGURATION */
          {
            /* header id exists */
            PduInfoType dynamicPduInfo;
            dynamicPduInfo.SduDataPtr = &(PduInfoPtr->SduDataPtr[containedPduIdx]);
            dynamicPduInfo.SduLength = (PduLengthType) header.dlc;
            /* send RxIndication for the referenced PduR-PDU to PduR module */
            PduR_IpduMRxIndication(IpduM_GetContainedPduRefOfRxContainedPdu(rxContainedPduId), &dynamicPduInfo);       /* SBSW_IPDUM_UNPACKRXCONTAINERPDU_CALL_PDURRXINDICATION */ /* VCA_IPDUM_FUNCTIONCALL_PDUINFOPTR_SELF_CONSTRUCTED */
          }
        }
      }

      /* increment contained pdu read idx by dlc */
      containedPduIdx += (PduLengthType) header.dlc;
    }
  }
# endif
# if (IPDUM_EXISTS_NONE_HEADERSIZEOFRXCONTAINERPDU == STD_ON)
#  if((IPDUM_EXISTS_SHORT_HEADERSIZEOFRXCONTAINERPDU == STD_ON) || (IPDUM_EXISTS_LONG_HEADERSIZEOFRXCONTAINERPDU == STD_ON))
  else
#  endif
  {
    /* PDUs with static layout and no header */
    for(containedPduIdx = IpduM_GetRxContainedPduStartIdxOfRxContainerPdu(rxContainerId); containedPduIdx < IpduM_GetRxContainedPduEndIdxOfRxContainerPdu(rxContainerId); containedPduIdx++)
    {
#  if (IPDUM_UPDATEBITUSEDOFRXCONTAINEDPDU == STD_ON)
      /* Check Update Bit */
      PduLengthType updateBitBytePos;
      uint8 updateBitMask;
      updateBitBytePos = (PduLengthType) ((PduLengthType) IpduM_GetUpdateIndicationBitPositionOfRxContainedPdu(containedPduIdx) >> 3u);
      updateBitMask = (uint8) (0x01u << (IpduM_GetUpdateIndicationBitPositionOfRxContainedPdu(containedPduIdx) % 8u));
      /* if (update bits used AND update bit is set) OR (update bits not used) */
      if((IpduM_IsUpdateBitUsedOfRxContainedPdu(containedPduIdx) && ((PduInfoPtr->SduDataPtr[updateBitBytePos] & updateBitMask) != 0x00u)) || !IpduM_IsUpdateBitUsedOfRxContainedPdu(containedPduIdx))
#  endif
      {
        PduInfoType staticPduInfo;
        staticPduInfo.SduDataPtr = &(PduInfoPtr->SduDataPtr[IpduM_GetOffsetOfRxContainedPdu(containedPduIdx)]);
        staticPduInfo.SduLength = IpduM_GetLengthOfRxContainedPdu(containedPduIdx);
        
        /* if contained pdus completely fits into received container */
        if(IpduM_GetEndBytePositionOfRxContainedPdu(containedPduIdx) <= pduLength)
        {
          /* send RxIndication for the referenced PduR-PDU to PduR module */
          PduR_IpduMRxIndication(IpduM_GetContainedPduRefOfRxContainedPdu(containedPduIdx), &staticPduInfo);    /* SBSW_IPDUM_UNPACKRXCONTAINERPDU_CALL_PDURRXINDICATION */ /* VCA_IPDUM_FUNCTIONCALL_PDUINFOPTR_SELF_CONSTRUCTED */
        }
      }
    }
  }
# endif
  IPDUM_DUMMY_STATEMENT(pduLength);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if((IPDUM_EXISTS_SHORT_HEADERSIZEOFRXCONTAINERPDU == STD_ON) || (IPDUM_EXISTS_LONG_HEADERSIZEOFRXCONTAINERPDU == STD_ON))
/*******************************************************************************************
 *  IpduM_ContainerRx_SearchRxHeaderId()
*******************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
LOCAL_INLINE FUNC(IpduM_HeaderIdOfRxContainedPduType, IPDUM_CODE) IpduM_ContainerRx_SearchRxHeaderId(uint32 headerId, IpduM_RxContainerPduIterType rxContainerId)
{
  IpduM_HeaderIdOfRxContainedPduType rxContainedPduId;
  for(rxContainedPduId = 0u; rxContainedPduId < IpduM_GetSizeOfRxContainedPdu(); rxContainedPduId++)    /* COV_IPDUM_SEARCH_HEADER_ID_LOOP_ABORT */
  {
    if(IpduM_GetHeaderIdOfRxContainedPdu(rxContainedPduId) == (IpduM_HeaderIdOfRxContainedPduType)headerId)
    {
# if (IPDUM_ACCEPTALLPDUSOFRXCONTAINERPDU == STD_ON)
      if((IpduM_IsAcceptAllPdusOfRxContainerPdu(rxContainerId))  
        || ((!IpduM_IsAcceptAllPdusOfRxContainerPdu(rxContainerId)) && (IpduM_GetRxContainerPduIdxOfRxContainedPdu(rxContainedPduId) == rxContainerId)) 
      ) /* COV_IPDUM_COMPLEMENTARY_CHECK */
# endif
      {
        break;
      }
    }
  }
  IPDUM_DUMMY_STATEMENT(rxContainerId);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  return rxContainedPduId;
}
#endif

#if(IPDUM_RXCONTAINERPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerRx_EnqueueContainer()
*******************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_ContainerRx_EnqueueContainer(IpduM_RxContainerPduIterType rxContainerId, P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr, PduLengthType pduLength)
{
  IpduM_ContainerRxBufferStartIdxOfRxContainerPduType bufferStartPos = IpduM_GetContainerRxBufferStartIdxOfRxContainerPdu(rxContainerId);
  PduLengthType bufferInstanceLength = IpduM_GetLengthOfRxContainerBufferInfo(rxContainerId);
  IpduM_QueueDepthOfRxContainerBufferInfoType bufferInstanceCount = IpduM_GetQueueDepthOfRxContainerBufferInfo(rxContainerId);

  IpduM_ContainerRxBufferIterType rxBufferIndex = (IpduM_ContainerRxBufferStartIdxOfRxContainerPduType)(bufferStartPos + (IpduM_GetContainerWriteIdxOfRxContainerBufferInfo(rxContainerId) * bufferInstanceLength));

  /* Make sure that size does not get negative. */
  if (rxBufferIndex < IpduM_GetSizeOfContainerRxBuffer()) /* COV_IPDUM_DEFENSIVE_PROGRAMMING */
  {
    IpduM_ContainerRxBufferPtrType pContainerRxBuf = IpduM_GetAddrContainerRxBuffer(rxBufferIndex);

    /* The buffer is being accessed with an offset, this offset has to be subtracted from the GetSizeOf macro. */
    VStdLib_MemCpy_s(pContainerRxBuf, (IpduM_ContainerRxBufferIterType)(IpduM_GetSizeOfContainerRxBuffer() - rxBufferIndex), PduInfoPtr->SduDataPtr, pduLength); /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_IPDUM_VSTDLIB_SAFE */  /* VCA_IPDUM_VSTDLIB_MEMCPY_SAFE */

# if((IPDUM_EXISTS_SHORT_HEADERSIZEOFRXCONTAINERPDU == STD_ON) || (IPDUM_EXISTS_LONG_HEADERSIZEOFRXCONTAINERPDU == STD_ON))
#  if (IPDUM_EXISTS_NONE_HEADERSIZEOFRXCONTAINERPDU == STD_ON)
    if(IpduM_GetHeaderSizeOfRxContainerPdu(rxContainerId) != IPDUM_NONE_HEADERSIZEOFRXCONTAINERPDU)
#  endif
    {
      IpduM_ContainerRxBufferIterType containerBufId;
      uint8 headerSize = IpduM_ContainerRx_GetHeaderSize(rxContainerId);

      /* add zero header for safe PDU termination */
      for(containerBufId = (IpduM_ContainerRxBufferIterType) pduLength; (containerBufId < bufferInstanceLength) && (containerBufId < ((IpduM_ContainerRxBufferIterType)(pduLength) + headerSize)); containerBufId++)       /* COV_IPDUM_TERMINATION_ZEROES */
      {
        if(IpduM_GetSizeOfContainerRxBuffer() > (containerBufId + rxBufferIndex)) /* COV_IPDUM_DEFENSIVE_PROGRAMMING */
        {
          pContainerRxBuf[containerBufId] = 0; /* SBSW_IPDUM_CONTAINERRXINDICATION_MEMORY_WRITE */
        }
      }
    }
# endif
  }

  /* update write pointers */
  SchM_Enter_IpduM_IPDUM_EXCLUSIVE_AREA_0();
  IpduM_IncContainerWriteCountOfRxContainerBufferInfo(rxContainerId);    /* SBSW_IPDUM_INDIRECT_ACCESS_FROM_EXTERNAL_PARAMETER */
  IpduM_IncContainerWriteIdxOfRxContainerBufferInfo(rxContainerId);      /* SBSW_IPDUM_INDIRECT_ACCESS_FROM_EXTERNAL_PARAMETER */
  if(IpduM_GetContainerWriteIdxOfRxContainerBufferInfo(rxContainerId) >= bufferInstanceCount)
  {
    IpduM_SetContainerWriteIdxOfRxContainerBufferInfo(rxContainerId, 0u);        /* SBSW_IPDUM_INDIRECT_ACCESS_FROM_EXTERNAL_PARAMETER */
  }
  SchM_Exit_IpduM_IPDUM_EXCLUSIVE_AREA_0();
}
#endif

#if(IPDUM_RXCONTAINERPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerRx_GetCurrentlyReadContainerRxBufferPtr
*******************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
LOCAL_INLINE FUNC(uint8*, IPDUM_CODE) IpduM_ContainerRx_GetCurrentlyReadContainerRxBufferPtr(IpduM_RxContainerPduIterType rxContainerId)
{
  IpduM_ContainerRxBufferPtrType rxQueueBuffer = IpduM_GetAddrContainerRxBuffer(IpduM_GetContainerRxBufferStartIdxOfRxContainerPdu(rxContainerId));
  IpduM_LengthOfRxContainerBufferInfoType bufferInstanceLength = IpduM_GetLengthOfRxContainerBufferInfo(rxContainerId);
  IpduM_ContainerRxBufferIterType containerRxBufferInstanceIdx = (IpduM_ContainerRxBufferIterType) (IpduM_GetContainerRxBufferStartIdxOfRxContainerPdu(rxContainerId) + (IpduM_GetContainerReadIdxOfRxContainerBufferInfo(rxContainerId) * (IpduM_ContainerRxBufferIterType) bufferInstanceLength));

  if(containerRxBufferInstanceIdx < IpduM_GetSizeOfContainerRxBuffer())  /* COV_IPDUM_DEFENSIVE_PROGRAMMING */
  {
    rxQueueBuffer = IpduM_GetAddrContainerRxBuffer(containerRxBufferInstanceIdx);
  }

  return rxQueueBuffer;
}
#endif

#if(IPDUM_RXCONTAINERPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerRx_RemoveOldestElementOfQueue
*******************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_ContainerRx_RemoveOldestElementOfQueue(IpduM_RxContainerPduIterType rxContainerId)
{
  /* increment read pointer */
  IpduM_IncContainerReadCountOfRxContainerBufferInfo(rxContainerId); /* SBSW_IPDUM_CSL02 */

  IpduM_IncContainerReadIdxOfRxContainerBufferInfo(rxContainerId); /* SBSW_IPDUM_CSL02 */
  if(IpduM_GetContainerReadIdxOfRxContainerBufferInfo(rxContainerId) >= IpduM_GetQueueDepthOfRxContainerBufferInfo(rxContainerId))
  {
    IpduM_SetContainerReadIdxOfRxContainerBufferInfo(rxContainerId, 0u); /* SBSW_IPDUM_CSL02 */
  }
}
#endif

#if ((IPDUM_CONTAINERRXBUFFER == STD_ON) || (IPDUM_CONTAINERTXBUFFER == STD_ON))
/*******************************************************************************************
*  IpduM_Container_Init()
*******************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, IPDUM_CODE) IpduM_Container_Init(void)
{
# if(IPDUM_TXCONTAINEDPDU == STD_ON)
  {
    IpduM_CTxContainerPduIterType confirmationId;
#  if (IPDUM_EXISTS_NONE_HEADERSIZEOFTXCONTAINERPDU == STD_ON)
    IpduM_CTxContainerPduIterType containerId;
#  endif
    for(confirmationId = 0u; confirmationId < IpduM_GetSizeOfCTxContainerPdu(); confirmationId++)
    {
      /* Reset write offsets for "last transmitted" ID buffer */
      IpduM_SetContainerTxConfLaIdOfTxContainerPdu(confirmationId, 0u);       /* SBSW_IPDUM_CSL01 */
    }

#  if (IPDUM_EXISTS_NONE_HEADERSIZEOFTXCONTAINERPDU == STD_ON)
    for(containerId = 0u; containerId < IpduM_GetSizeOfCTxContainerPdu(); containerId++)
    {
      /* Initialize current containers with header type == none */
      if(IpduM_GetHeaderSizeOfTxContainerPdu(containerId) == IPDUM_NONE_HEADERSIZEOFTXCONTAINERPDU)
      {
        IpduM_ContainerTx_DataQueue_ResetNoneHeaderContainerInstance((IpduM_CTxContainerPduIterType) containerId, 0u);   /* first instance is always instance 0 */
      }
    }
#  endif
  }
# endif
  /* Initialize BufferInfoIdx */
  {
# if(IPDUM_CTXCONTAINERPDU == STD_ON)
    IpduM_CTxContainerPduIterType txContainerId;
# endif
# if(IPDUM_CRXCONTAINERBUFFERINFO == STD_ON)
    IpduM_CRxContainerBufferInfoIterType rxContainerId;
# endif
# if(IPDUM_CTXCONTAINERPDU == STD_ON)
    SchM_Enter_IpduM_IPDUM_EXCLUSIVE_AREA_0();
    for(txContainerId = 0u; txContainerId < IpduM_GetSizeOfCTxContainerPdu(); txContainerId++)
    {
      IpduM_SetContainedPduWriteIdxOfTxContainerPdu(txContainerId, 0u);       /* SBSW_IPDUM_CSL01 */
      IpduM_SetContainerReadIdxOfTxContainerPdu(txContainerId, 0u);   /* SBSW_IPDUM_CSL01 */
      IpduM_SetContainerWriteIdxOfTxContainerPdu(txContainerId, 0u);  /* SBSW_IPDUM_CSL01 */
      IpduM_SetContainerPduSendTimeoutOfTxContainerPdu(txContainerId, 0u);    /* SBSW_IPDUM_CSL01 */
      IpduM_SetContainerReadCountOfTxContainerPdu(txContainerId, 0u); /* SBSW_IPDUM_CSL01 */
      IpduM_SetContainerWriteCountOfTxContainerPdu(txContainerId, 0u);        /* SBSW_IPDUM_CSL01 */
    }
    SchM_Exit_IpduM_IPDUM_EXCLUSIVE_AREA_0();
# endif
# if(IPDUM_CRXCONTAINERBUFFERINFO == STD_ON)
    SchM_Enter_IpduM_IPDUM_EXCLUSIVE_AREA_0();
    for(rxContainerId = 0u; rxContainerId < IpduM_GetSizeOfCRxContainerBufferInfo(); rxContainerId++)
    {
      IpduM_SetContainerReadIdxOfRxContainerBufferInfo(rxContainerId, 0u);   /* SBSW_IPDUM_CSL01 */
      IpduM_SetContainerWriteIdxOfRxContainerBufferInfo(rxContainerId, 0u);  /* SBSW_IPDUM_CSL01 */
      IpduM_SetContainerReadCountOfRxContainerBufferInfo(rxContainerId, 0u); /* SBSW_IPDUM_CSL01 */
      IpduM_SetContainerWriteCountOfRxContainerBufferInfo(rxContainerId, 0u);        /* SBSW_IPDUM_CSL01 */
    }
    SchM_Exit_IpduM_IPDUM_EXCLUSIVE_AREA_0();
# endif
  }

# if (IPDUM_CONTAINERTXBUFFER == STD_ON)
  {
    IpduM_ContainerTxConfBuIdIterType txConfirmationBufferInfoIdx = 0u;
    for(; txConfirmationBufferInfoIdx < IpduM_GetSizeOfContainerTxConfBuId(); txConfirmationBufferInfoIdx++)
    {
      IpduM_SetContainerTxConfBuId(txConfirmationBufferInfoIdx, 0u);  /* SBSW_IPDUM_CSL01 */
    }
  }
# endif
# if (IPDUM_REQUESTQUEUEUSEDOFTXCONTAINERPDU == STD_ON)
  {
    IpduM_CTxRequestQueueIndirectionIterType requestQueueIndirectionIdx = 0;
    
    for(; requestQueueIndirectionIdx < IpduM_GetSizeOfCTxRequestQueueIndirection(); requestQueueIndirectionIdx++)
    {
      IpduM_SetReadIdxOfTxRequestQueueIndirection(requestQueueIndirectionIdx, 0); /* SBSW_IPDUM_CSL01 */
      IpduM_SetReadTmpIdxOfTxRequestQueueIndirection(requestQueueIndirectionIdx, 0); /* SBSW_IPDUM_CSL01 */
      IpduM_SetWriteIdxOfTxRequestQueueIndirection(requestQueueIndirectionIdx, 0); /* SBSW_IPDUM_CSL01 */
    }
  }
# endif
}  /* PRQA S 6010 */ /* MD_MSR_STPTH */
#endif

#if (IPDUM_TXCONTAINEDPDU == STD_ON)
/*******************************************************************************************
*  IpduM_ContainerTx_CheckTriggers()
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
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_ContainerTx_CheckTriggers(IpduM_TxUpIndIdxOfTxUpInfoType txContainedId, boolean isFirstContainedPdu)
{
  IpduM_CTxContainerPduIterType txContainerId = IpduM_GetTxContainerPduIdxOfTxContainedPdu(txContainedId);
# if (IPDUM_REQUESTQUEUEUSEDOFTXCONTAINERPDU == STD_ON)
  PduLengthType sizeOfRequestQueueData = IpduM_ContainerTx_RequestQueue_CalculateSize(txContainerId);
# endif
  
  if((IpduM_GetContainedPduWriteIdxOfTxContainerPdu(txContainerId) > (IpduM_GetTxSizeThresholdOfTxContainerPdu(txContainerId)))
# if (IPDUM_REQUESTQUEUEUSEDOFTXCONTAINERPDU == STD_ON)
     || (IpduM_IsRequestQueueUsedOfTxContainerPdu(txContainerId) && (sizeOfRequestQueueData > IpduM_GetTxSizeThresholdOfTxContainerPdu(txContainerId)))
# endif
# if (IPDUM_TXPDUTRIGGEROFTXCONTAINEDPDU == STD_ON)
     || (IpduM_IsTxPduTriggerOfTxContainedPdu(txContainedId))
# endif
# if (IPDUM_SENDTODEFOFTXCONTAINEDPDU == STD_ON)
     || (IpduM_IsSendToDefOfTxContainedPdu(txContainedId) && (IpduM_GetSendTimeoutOfTxContainedPdu(txContainedId) == 0u))
# endif
    )
  {
# if ((IPDUM_REQUESTQUEUEUSEDOFTXCONTAINERPDU == STD_ON))
    if(IpduM_IsRequestQueueUsedOfTxContainerPdu(txContainerId))
    {
      (void) IpduM_ContainerTx_RequestQueue_TransmitContainer(txContainerId);
    }
    else
# endif
    {
      /* FIFO queue */
      /* If container size threshold reached or trigger always is set: transmit/queue container, choose next container */
      IpduM_ContainerTx_DataQueue_TriggerTransmissionOfCurrContainerPdu(txContainerId);
    }
    IpduM_ContainerTx_StopContainerPduSendTimeout(txContainerId);
  }
# if (IPDUM_FIRSTCONTAINEDPDUTRIGGEROFTXCONTAINERPDU == STD_ON)
  else if(IpduM_IsFirstContainedPduTriggerOfTxContainerPdu(txContainerId)) /* PRQA S 2004 */ /* MD_IpduM_2004 */
  {
    /* only continue if it is the first PDU being added */
    if(isFirstContainedPdu)
    {
      /* If first contained pdu trigger = true, call PduR_IpduMTransmit with empty PDU */
      IpduM_ContainerTx_TransmitEmptyPdu(txContainerId);
    }
  }
# endif

  IPDUM_DUMMY_STATEMENT(isFirstContainedPdu); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */  /* lint -e{438} */
}
#endif

#if (IPDUM_TXCONTAINEDPDU == STD_ON)
/*******************************************************************************************
*  IpduM_ContainerTx_StartContainerPduSendTimeout
*******************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_ContainerTx_StartContainerPduSendTimeout(IpduM_CTxContainerPduIterType txContainerId)
{
# if (IPDUM_SENDTODEFOFTXCONTAINERPDU == STD_ON)
  if(IpduM_IsSendToDefOfTxContainerPdu(txContainerId))
  {
    /* Start timeout */
    IpduM_SetContainerPduSendTimeoutOfTxContainerPdu(txContainerId, IpduM_GetSendTimeoutOfTxContainerPdu(txContainerId)); /* SBSW_IPDUM_INDIRECT_ACCESS_FROM_EXTERNAL_PARAMETER */
  }
# endif

  IPDUM_DUMMY_STATEMENT(txContainerId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */  /* lint -e{438} */
}
#endif

#if (IPDUM_TXCONTAINEDPDU == STD_ON)
/*******************************************************************************************
*  IpduM_ContainerTx_StopContainerPduSendTimeout
*******************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_ContainerTx_StopContainerPduSendTimeout(IpduM_CTxContainerPduIterType txContainerId)
{
  IpduM_SetContainerPduSendTimeoutOfTxContainerPdu(txContainerId, 0); /* SBSW_IPDUM_INDIRECT_ACCESS_FROM_EXTERNAL_PARAMETER */
}
#endif

#if (IPDUM_TXCONTAINEDPDU == STD_ON)
/*******************************************************************************************
*  IpduM_ContainerTx_StartContainedPduSendTimeout
*******************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_ContainerTx_StartContainedPduSendTimeout(IpduM_TxUpIndIdxOfTxUpInfoType txContainedId)
{
# if (IPDUM_SENDTODEFOFTXCONTAINEDPDU == STD_ON)
  IpduM_CTxContainerPduIterType txContainerId = IpduM_GetTxContainerPduIdxOfTxContainedPdu(txContainedId);

  if(IpduM_IsSendToDefOfTxContainedPdu(txContainedId))
  {
    if((IpduM_GetContainerPduSendTimeoutOfTxContainerPdu(txContainerId) > IpduM_GetSendTimeoutOfTxContainedPdu(txContainedId)) /* Update current running timer if contained Pdu timeout is smaller. */
        || (IpduM_GetContainerPduSendTimeoutOfTxContainerPdu(txContainerId) == 0u)) /* OR Update timer to start it initially. */
    {
      IpduM_SetContainerPduSendTimeoutOfTxContainerPdu(txContainerId, IpduM_GetSendTimeoutOfTxContainedPdu(txContainedId)); /* SBSW_IPDUM_INDIRECT_ACCESS_FROM_EXTERNAL_PARAMETER */
    }
  }
# endif

  IPDUM_DUMMY_STATEMENT(txContainedId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */  /* lint -e{438} */
}
#endif

#if (IPDUM_TXCONTAINEDPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTransmit()
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
 *   requires txContainedId < IpduM_GetSizeOfTxContainedPdu();
 * \endspec
 */
FUNC(Std_ReturnType, IPDUM_CODE) IpduM_ContainerTransmit(IpduM_TxUpIndIdxOfTxUpInfoType txContainedId, P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr)
{
  uint8 errorId = IPDUM_E_NO_ERROR;
  Std_ReturnType retVal = E_NOT_OK;
  IpduM_CTxContainerPduIterType txContainerId = IpduM_GetTxContainerPduIdxOfTxContainedPdu(txContainedId);
  IpduM_LengthOfTxContainerPduType bufferInstanceLength = IpduM_GetLengthOfTxContainerPdu(txContainerId);
  PduLengthType pduLength = PduInfoPtr->SduLength;

/* *INDENT-OFF* */
  /* Long headers are 8 bytes, short headers are 4 bytes in size.
     Long headers have 4 bytes ID and 4 bytes DLC.
     Short headers have 3 bytes ID and 1 byte DLC. */
/* *INDENT-ON* */
  uint8 headerSize = IpduM_ContainerTx_GetHeaderSize(txContainerId);

# if (IPDUM_DEV_ERROR_DETECT == STD_ON)
  IpduM_LengthOfTxContainerPduType pduAndHeaderLength = (IpduM_LengthOfTxContainerPduType)pduLength + (IpduM_LengthOfTxContainerPduType)headerSize;
  if(pduAndHeaderLength > bufferInstanceLength)
  {
    errorId = IPDUM_E_PARAM;
  }
#  if (IPDUM_EXISTS_SHORT_HEADERSIZEOFTXCONTAINERPDU == STD_ON)
  else if((pduLength > 255u) && (headerSize == IPDUM_HEADERSIZE_SMALL)) /* COV_IPDUM_SINGLE_HEADERSIZE_CONFIG */
  {
    /* For short headers, only 8 bits are available for DLC. So values >255 are not allowed here. */
    errorId = IPDUM_E_PARAM;
  }
#  endif
  else
# endif
  {
    SchM_Enter_IpduM_IPDUM_EXCLUSIVE_AREA_0();
    {
      boolean isFirstContainedPdu;

# if (IPDUM_REQUESTQUEUEUSEDOFTXCONTAINERPDU == STD_ON)
      if(IpduM_IsRequestQueueUsedOfTxContainerPdu(txContainerId))
      {
        isFirstContainedPdu = IpduM_ContainerTx_RequestQueue_IsEmpty(txContainerId);
        /* PDUs that use the request queue get only their ID added */
        IpduM_ContainerTx_RequestQueue_AddPdu(txContainedId, pduLength);
      }
      else
# endif
      {
# if (IPDUM_EXISTS_NONE_HEADERSIZEOFTXCONTAINERPDU == STD_ON)
        if(IpduM_GetHeaderSizeOfTxContainerPdu(txContainerId) != IPDUM_NONE_HEADERSIZEOFTXCONTAINERPDU)
# endif
        {
          if(!IpduM_ContainerTx_DataQueue_FitsPduIntoCurrentOpenInstance(txContainerId, pduLength))
          {
            IpduM_ContainerTx_DataQueue_TriggerTransmissionOfCurrContainerPdu(txContainerId);

            IpduM_ContainerTx_StopContainerPduSendTimeout(txContainerId);
          }
        }

        isFirstContainedPdu = (IpduM_GetContainedPduWriteIdxOfTxContainerPdu(txContainerId) == 0u);

        /* PDU now does fit into current container instance: add PDU. */
        IpduM_ContainerTx_DataQueue_AddTxPduToCurrContainer(txContainedId, PduInfoPtr); /* SBSW_IPDUM_FUNCTIONCALL_PDUINFOPTR_CHECKED_BY_CALLER */

# if (IPDUM_TX_CONFIRMATION_API == STD_ON && IPDUM_EXISTS_CONTAINER_PATHWAYTYPEOFCTXLOINFO == STD_ON)
        IpduM_ContainerTx_WriteContainedPduIdToTxConfirmationBuffer(txContainedId);
# endif
      }

      /* Handle timeouts. */
      if(isFirstContainedPdu)
      {
        IpduM_ContainerTx_StartContainerPduSendTimeout(txContainerId);
      }
      IpduM_ContainerTx_StartContainedPduSendTimeout(txContainedId);

      /* Check trigger conditions and trigger the PDU if conditions are met. */
      IpduM_ContainerTx_CheckTriggers(txContainedId, isFirstContainedPdu);

      /* PDU is added to the PDU by here */
      retVal = E_OK;
    }
    SchM_Exit_IpduM_IPDUM_EXCLUSIVE_AREA_0();
  }

# if (IPDUM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != IPDUM_E_NO_ERROR)
  {
    IpduM_Det_ReportError(IPDUM_APIID_TRANSMIT, (errorId));
  }
# else
  IPDUM_DUMMY_STATEMENT(errorId);      /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */  /* lint -e{438} */
# endif

  return retVal;
}  /* PRQA S 6050, 6080, 6030 */ /* MD_MSR_STCAL, MD_MSR_STMIF, MD_MSR_STCYC */
#endif

#if(IPDUM_TRIGGER_TRANSMIT_API == STD_ON && IPDUM_EXISTS_CONTAINER_PATHWAYTYPEOFCTXLOINFO == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTriggerTransmit()
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
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, IPDUM_CODE) IpduM_ContainerTriggerTransmit(IpduM_TxContainerPduIdxOfCTxLoInfoType txContainerId, P2VAR(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr)
{
  Std_ReturnType retVal = E_NOT_OK;
  IpduM_LengthOfTxContainerPduType bufferInstanceLength = IpduM_GetLengthOfTxContainerPdu(txContainerId);

  /* If a non-empty instance of this container exists: Calculate payload size, transmit container, delete from queue, E_OK */
  /* Else: E_NOT_OK */
  if(PduInfoPtr->SduLength >= bufferInstanceLength)
  {
# if (IPDUM_REQUESTQUEUEUSEDOFTXCONTAINERPDU == STD_ON)
    if(IpduM_IsRequestQueueUsedOfTxContainerPdu(txContainerId))
    {
      SchM_Enter_IpduM_IPDUM_EXCLUSIVE_AREA_0();
      if(!IpduM_ContainerTx_RequestQueue_IsEmpty(txContainerId))
      {
        /* current instance is closed -> reset its send timeout */
        IpduM_ContainerTx_StopContainerPduSendTimeout(txContainerId);

        /* last-is-best PDU: load data to last-is-best buffer via TriggerTransmit, then use this buffer for transmission */
        IpduM_ContainerTx_RequestQueue_FillLastIsBestContainer(txContainerId); /* SBSW_IPDUM_CONTAINERTRIGGERTRANSMIT_CALL_FILLLASTISBESTCONTAINER */
        /* TriggerTransmit is always considered successful */
        IpduM_ContainerTx_RequestQueue_RemoveLastTransmittedIds(txContainerId);

        /* Copy PDU from container buffer to provided destination buffer */
        VStdLib_MemCpy_s(PduInfoPtr->SduDataPtr, PduInfoPtr->SduLength, IpduM_GetAddrContainerTxLIBBuffer(0), bufferInstanceLength); /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_IPDUM_VSTDLIB_SAFE */  /* VCA_IPDUM_VSTDLIB_MEMCPY_SAFE */

        PduInfoPtr->SduLength = IpduM_ContainerTx_GetTransmittedPduLength(txContainerId, IpduM_GetAddrContainerTxLIBBuffer(0)); /* SBSW_IPDUM_CONTAINERTRIGGERTRANSMIT_PTR_WRITE */ /* SBSW_IPDUM_GETTRANSMITTEDPDULENGTH */

# if ((IPDUM_TXLOINFOUSEDOFTXCONTAINERPDU == STD_ON) && (IPDUM_TXCONFIRMATIONTIMEOUTOFTXCONTAINERPDU == STD_ON))       /* COV_IPDUM_VAR_DEPENDENT_SWITCH */
        IpduM_ContainerTx_StartTxConfirmationTimeout(txContainerId);
# endif
        retVal = E_OK;
      }
      SchM_Exit_IpduM_IPDUM_EXCLUSIVE_AREA_0();
    }
    else
# endif
    {
      boolean pleaseCopyTheData = FALSE;

      SchM_Enter_IpduM_IPDUM_EXCLUSIVE_AREA_0();
      if(IpduM_ContainerTx_DataQueue_IsFifoQueueEmpty(txContainerId))
      {
        if(IpduM_GetContainedPduWriteIdxOfTxContainerPdu(txContainerId) > 0u)
        {/* Queue is empty, but the current open instance has data. Put it in the queue and read it below. */
          IpduM_ContainerTx_DataQueue_QueueCurrContainerPdu(txContainerId);
          IpduM_ContainerTx_StopContainerPduSendTimeout(txContainerId);
          pleaseCopyTheData = TRUE;
        }
      }
      else
      {
        pleaseCopyTheData = TRUE;
      }

      if(pleaseCopyTheData == TRUE)
      {
        /* Copy PDU from container buffer to provided destination buffer */
        VStdLib_MemCpy_s(PduInfoPtr->SduDataPtr, PduInfoPtr->SduLength, IpduM_ContainerTx_GetStartAddrOfCurrentlyReadContainerPdu(txContainerId), bufferInstanceLength); /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_IPDUM_VSTDLIB_SAFE */  /* VCA_IPDUM_VSTDLIB_MEMCPY_SAFE */
        PduInfoPtr->SduLength = IpduM_ContainerTx_GetTransmittedPduLength(txContainerId, IpduM_ContainerTx_GetStartAddrOfCurrentlyReadContainerPdu(txContainerId)); /* SBSW_IPDUM_CONTAINERTRIGGERTRANSMIT_PTR_WRITE */ /* SBSW_IPDUM_GETTRANSMITTEDPDULENGTH */

# if ((IPDUM_TXLOINFOUSEDOFTXCONTAINERPDU == STD_ON) && (IPDUM_TXCONFIRMATIONTIMEOUTOFTXCONTAINERPDU == STD_ON))       /* COV_IPDUM_VAR_DEPENDENT_SWITCH */
        IpduM_ContainerTx_StartTxConfirmationTimeout(txContainerId);
# endif
        IpduM_ContainerTx_CopyTxConfirmationsOfCurrentlyReadContainer2LastBuffer(txContainerId);
        IpduM_ContainerTx_DataQueue_RemoveOldestPdu(txContainerId);
        retVal = E_OK;
      }
      SchM_Exit_IpduM_IPDUM_EXCLUSIVE_AREA_0();
    }
  }
  return retVal;
}  /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */ 
#endif

#if (IPDUM_TX_CONFIRMATION_API == STD_ON && IPDUM_EXISTS_CONTAINER_PATHWAYTYPEOFCTXLOINFO == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTxConfirmation()
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
 */
FUNC(void, IPDUM_CODE) IpduM_ContainerTxConfirmation(PduIdType TxPduId)
{
# if ((IPDUM_TXLOINFOUSEDOFTXCONTAINERPDU == STD_ON) && (IPDUM_TXCONFIRMATIONTIMEOUTOFTXCONTAINERPDU == STD_ON))        /* COV_IPDUM_VAR_DEPENDENT_SWITCH */
  IpduM_CTxContainerPduIterType containerPduId = IpduM_GetTxContainerPduIdxOfCTxLoInfoOfTxLoInfoWithInvalidIndexes(TxPduId);
  if(0u != IpduM_GetTxConfirmationTimeoutOfTxContainerPdu(containerPduId))
  {
    if(0u != IpduM_GetTxConfTimeoutCntOfVTxLoInfoOfTxLoInfoWithInvalidIndexes(TxPduId))
    {
      SchM_Enter_IpduM_IPDUM_EXCLUSIVE_AREA_0();
#  if (IPDUM_TXCONFIRMATIONOFTXCONTAINEDPDU == STD_ON)
      {
        IpduM_ContainerTxConfLastIterType readOffset;
        IpduM_TxContainerPduIdxOfCTxLoInfoType txContainerId = IpduM_GetTxContainerPduIdxOfCTxLoInfoOfTxLoInfoWithInvalidIndexes(TxPduId);
        IpduM_ContainerTxConfLastStartIdxOfTxContainerPduType bufferStartIdx = IpduM_GetContainerTxConfLastStartIdxOfTxContainerPdu(txContainerId);
        for(readOffset = 0u; readOffset < IpduM_GetContainerTxConfLaIdOfTxContainerPdu(txContainerId); readOffset++)
        {
          IpduM_ContainerTxConfLastType currentContainedPdu = IpduM_GetContainerTxConfLast(bufferStartIdx + readOffset);
          if(IpduM_IsTxConfirmationOfTxContainedPdu(currentContainedPdu))
          {
            PduR_IpduMTxConfirmation(IpduM_GetTxContainedPduRefOfTxContainedPdu(currentContainedPdu)); /* VCA_IPDUM_FUNCTIONCALL_WITH_ONLY_ID */
          }
        }
      }
#  endif

      IpduM_SetTxConfTimeoutCntOfVTxLoInfoOfTxLoInfoWithInvalidIndexes(TxPduId, IPDUM_RESET);      /* Clear counter */ /* SBSW_IPDUM_CSL03 */
      SchM_Exit_IpduM_IPDUM_EXCLUSIVE_AREA_0();
    }
  }
# endif

  IPDUM_DUMMY_STATEMENT(TxPduId);      /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}
#endif

#if (IPDUM_RXCONTAINERPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerRxIndication()
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
 *   requires rxContainerId < IpduM_GetSizeOfRxContainerPdu();
 * \endspec
 */
FUNC(uint8, IPDUM_CODE) IpduM_ContainerRxIndication(IpduM_RxPathwayIndIdxOfRxInfoType rxContainerId, P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr)
{
  uint8 errorId = IPDUM_E_NO_ERROR;

  PduLengthType bufferInstanceLength = IpduM_GetLengthOfRxContainerBufferInfo(rxContainerId);

  PduLengthType pduLength = PduInfoPtr->SduLength;

  /* Handle larger than configured PDUs by trimming to configured length */
  if(pduLength > bufferInstanceLength)
  {
    pduLength = bufferInstanceLength;
# if (IPDUM_DEV_ERROR_DETECT == STD_ON)
    errorId = IPDUM_E_HEADER;
# endif
  }
  
  {
    IpduM_RxContainerReceivedSizeType rxContainerReceivedSizeInstanceIdx = ((IpduM_RxContainerReceivedSizeType) IpduM_GetRxContainerReceivedSizeStartIdxOfRxContainerPdu(rxContainerId)) + IpduM_GetContainerWriteIdxOfRxContainerBufferInfo(rxContainerId);

    if(IpduM_GetSizeOfRxContainerReceivedSize() > rxContainerReceivedSizeInstanceIdx) /* COV_IPDUM_DEFENSIVE_PROGRAMMING */
    {
      IpduM_SetRxContainerReceivedSize(rxContainerReceivedSizeInstanceIdx, pduLength); /* SBSW_IPDUM_CSL02 */
    }
  }

# if (IPDUM_IMMEDIATEPROCESSINGOFRXCONTAINERPDU == STD_ON)
  /* If immediate processing is active: loop through all contained-pdus, send rxindications if configured or accept all */
  if(IpduM_IsImmediateProcessingOfRxContainerPdu(rxContainerId))  
  {
    /* Immediate processing. Send RxIndications for all received contained-PDUs. */
    IpduM_ContainerRx_UnpackContainerPdu(rxContainerId, PduInfoPtr, pduLength); /* SBSW_IPDUM_CONTAINERRXINDICATION_CALL_UNPACKRXCONTAINERPDU */
  }
  else
# endif
  {/* Deferred processing. Enqueue PDU for later reception handling. */

    /* If the PDU does not fit into container: DET, oldest entry will be overwritten while enqueueing */
    if((IpduM_ContainerWriteCountOfRxContainerBufferInfoType)
       (IpduM_GetContainerWriteCountOfRxContainerBufferInfo(rxContainerId) - IpduM_GetContainerReadCountOfRxContainerBufferInfo(rxContainerId)) >= IpduM_GetQueueDepthOfRxContainerBufferInfo(rxContainerId))
    {
      /* Queue is full, return an error */
# if (IPDUM_DEV_ERROR_DETECT == STD_ON)
      errorId = IPDUM_E_QUEUEOVFL;
# endif
      SchM_Enter_IpduM_IPDUM_EXCLUSIVE_AREA_0();
      IpduM_ContainerRx_RemoveOldestElementOfQueue(rxContainerId);
      SchM_Exit_IpduM_IPDUM_EXCLUSIVE_AREA_0();
    }

    SchM_Enter_IpduM_IPDUM_EXCLUSIVE_AREA_0();
    IpduM_ContainerRx_EnqueueContainer(rxContainerId, PduInfoPtr, pduLength);  /* SBSW_IPDUM_CONTAINERRXINDICATION_CALL_ENQUEUERXCONTAINER */
    SchM_Exit_IpduM_IPDUM_EXCLUSIVE_AREA_0();
  }
  return errorId;
} /* PRQA S 6010, 6030, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STMIF */
#endif

#define IPDUM_STOP_SEC_CODE
#include "MemMap.h"    /* PRQA S 5087 */        /*  MD_MSR_MemMap */

/**********************************************************************************************************************
  GLOBAL FUNCTIONS
**********************************************************************************************************************/
#define IPDUM_START_SEC_CODE
#include "MemMap.h"    /* PRQA S 5087 */        /*  MD_MSR_MemMap */

#if (IPDUM_TXCONTAINEDPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_CalculateSizeOfContainer()
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
FUNC(uint32, IPDUM_CODE) IpduM_CalculateSizeOfContainer(PduLengthType headerSize, P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr)   /* PRQA S 1505 */ /* MD_MSR_Rule8.7 */
{
  uint8 errorId = IPDUM_E_NO_ERROR;
  PduLengthType containerSize = 0u;
  
# if (IPDUM_DEV_ERROR_DETECT == STD_ON)
  if(!IpduM_IsInitialized())
  {
    errorId = IPDUM_E_UNINIT;
  }
  else if((PduInfoPtr == NULL_PTR) || (PduInfoPtr->SduDataPtr == NULL_PTR))
  {
    errorId = IPDUM_E_PARAM_POINTER;
  } 
#  if ((IPDUM_EXISTS_LONG_HEADERSIZEOFTXCONTAINERPDU == STD_ON) || (IPDUM_EXISTS_SHORT_HEADERSIZEOFTXCONTAINERPDU == STD_ON)) /* COV_IPDUM_HEADERSIZE_IN_SIZE_CALCULATION */
  else if(
#   if (IPDUM_EXISTS_LONG_HEADERSIZEOFTXCONTAINERPDU == STD_ON)
  !(headerSize == IPDUM_HEADERSIZE_LARGE)
#   endif
#   if ((IPDUM_EXISTS_LONG_HEADERSIZEOFTXCONTAINERPDU == STD_ON) && (IPDUM_EXISTS_SHORT_HEADERSIZEOFTXCONTAINERPDU == STD_ON))
  && 
#   endif
#   if (IPDUM_EXISTS_SHORT_HEADERSIZEOFTXCONTAINERPDU == STD_ON)
  !(headerSize == IPDUM_HEADERSIZE_SMALL)
#   endif
  )
  {
    errorId = IPDUM_E_PARAM;
  }
#  endif
  else
# endif
  {
    IpduM_ContainedPduHeaderType currentHeader;

    while(containerSize <= (PduInfoPtr->SduLength - headerSize))  /* stop iterating one headersize before the end to avoid reading a partial header */
    {
      /* read header, add current contained PDU's length (including header) to containerSize */
      currentHeader = IpduM_Container_ReadHeader(&(PduInfoPtr->SduDataPtr[containerSize]), headerSize); /* SBSW_IPDUM_FUNCTIONCALL_PDUINFOPTR_CHECKED_BY_CALLER */ /* VCA_IPDUM_FUNCTIONCALL_PDUINFOPTR_CHECKED_BY_CALLER */

      /* detect end of container */
      if(currentHeader.headerId == 0u)
      {
        break;
      }

      containerSize += headerSize + (PduLengthType) currentHeader.dlc;
    }
  }
  
# if (IPDUM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != IPDUM_E_NO_ERROR)
  {
    IpduM_Det_ReportError(IPDUM_APIID_CALCULATECONTAINERSIZE, (errorId));
  }
# else
  IPDUM_DUMMY_STATEMENT(errorId);       /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
# endif

  return containerSize;
}  /* PRQA S 6080 */ /* MD_MSR_STMIF */ 
#endif

#if (IPDUM_TXCONTAINEDPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTx_MainFunction()
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
 */
FUNC(void, IPDUM_CODE) IpduM_ContainerTx_MainFunction(void)
{
  IpduM_CTxContainerPduIterType txContainerId;

  for(txContainerId = 0u; txContainerId < IpduM_GetSizeOfCTxContainerPdu(); txContainerId++)
  {
    Std_ReturnType transmitResult = E_OK;

    SchM_Enter_IpduM_IPDUM_EXCLUSIVE_AREA_0();
    {
# if (IPDUM_SENDTODEFOFTXCONTAINERPDU == STD_ON)
      IpduM_ContainerPduSendTimeoutOfTxContainerPduType containerPduSendTimeout = IpduM_GetContainerPduSendTimeoutOfTxContainerPdu(txContainerId);
# endif

      {
# if (IPDUM_REQUESTQUEUEUSEDOFTXCONTAINERPDU == STD_ON)
        if(IpduM_IsRequestQueueUsedOfTxContainerPdu(txContainerId))
        {
#  if (IPDUM_SENDTODEFOFTXCONTAINERPDU == STD_ON)
          if(containerPduSendTimeout == 0u)
#  endif
          {
# if (IPDUM_TRIGGERTRANSMITOFTXCONTAINERPDU == STD_ON)
            if(IpduM_IsTriggerTransmitOfTxContainerPdu(txContainerId)) /* PRQA S 2842 */ /* MD_IpduM_2842 */
            {
              if(!IpduM_ContainerTx_RequestQueue_IsEmpty(txContainerId))
              {
                /* For TriggerTransmit Pdus only the oldest Pdu is transmitted. */
                (void) IpduM_ContainerTx_RequestQueue_TransmitContainer(txContainerId);
              }
            }
            else
# endif
            {
              while(!IpduM_ContainerTx_RequestQueue_IsEmpty(txContainerId) && (transmitResult == E_OK))
              {
                /* returns E_NOT_OK for empty queue and transmission failure */
                transmitResult = IpduM_ContainerTx_RequestQueue_TransmitContainer(txContainerId);
              }
            }
          }
        }
        else
# endif
        {
# if (IPDUM_TRIGGERTRANSMITOFTXCONTAINERPDU == STD_ON)
          if(IpduM_IsTriggerTransmitOfTxContainerPdu(txContainerId)) /* PRQA S 2842 */ /* MD_IpduM_2842 */
          {
            /* For TriggerTransmit Pdus only the oldest Pdu is transmitted. */
            (void) IpduM_ContainerTx_DataQueue_TransmitQueuedFIFOContainerPdu(txContainerId);
          }
          else
# endif
          {
            while(transmitResult == E_OK)
            {
              /* returns E_NOT_OK for empty queue and transmission failure */
              transmitResult = IpduM_ContainerTx_DataQueue_TransmitQueuedFIFOContainerPdu(txContainerId);
            }
          }
        }
      }

# if (IPDUM_SENDTODEFOFTXCONTAINERPDU == STD_ON)
      {
        if(containerPduSendTimeout == 1u)
        {
#  if ((IPDUM_REQUESTQUEUEUSEDOFTXCONTAINERPDU == STD_ON))
          if(IpduM_IsRequestQueueUsedOfTxContainerPdu(txContainerId))
          {
            (void) IpduM_ContainerTx_RequestQueue_TransmitContainer(txContainerId);
          }
          else
#  endif
          {
            IpduM_ContainerTx_DataQueue_TriggerTransmissionOfCurrContainerPdu(txContainerId);
          }

          IpduM_ContainerTx_StopContainerPduSendTimeout(txContainerId);
        }
        else if(containerPduSendTimeout > 0u)
        {
          IpduM_DecContainerPduSendTimeoutOfTxContainerPdu(txContainerId); /* SBSW_IPDUM_CSL02 */
        }
        else
        {
          /* Because of Misra. Stays empty. */
        }
      }
# endif
    }
    SchM_Exit_IpduM_IPDUM_EXCLUSIVE_AREA_0();
  }
}  /* PRQA S 6050, 6080, 6030 */ /* MD_MSR_STCAL, MD_MSR_STMIF, MD_MSR_STCYC */
#endif

#if(IPDUM_RXCONTAINERPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerRx_MainFunction()
*******************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, IPDUM_CODE) IpduM_ContainerRx_MainFunction(void)
{
  IpduM_VRxContainerBufferInfoIterType rxContainerId;

  for(rxContainerId = 0u; rxContainerId < IpduM_GetSizeOfCRxContainerBufferInfo(); rxContainerId++)
  {
# if (IPDUM_IMMEDIATEPROCESSINGOFRXCONTAINERPDU == STD_ON)
    if(!IpduM_IsImmediateProcessingOfRxContainerPdu(rxContainerId))
# endif
    {
      IpduM_LengthOfRxContainerBufferInfoType bufferInstanceLength = IpduM_GetLengthOfRxContainerBufferInfo(rxContainerId);
      IpduM_QueueDepthOfRxContainerBufferInfoType queueLengthCounter = IpduM_GetQueueDepthOfRxContainerBufferInfo(rxContainerId);

      /* the while statement checks for empty queue */
      while((IpduM_ContainerWriteCountOfRxContainerBufferInfoType)
            (IpduM_GetContainerWriteCountOfRxContainerBufferInfo(rxContainerId) - IpduM_GetContainerReadCountOfRxContainerBufferInfo(rxContainerId)) > 0u)
      {
        IpduM_RxContainerMainFunctionBufferPtrType rxMfBuffer = IpduM_GetAddrRxContainerMainFunctionBuffer(0);
        PduInfoType pduInfo;
        PduLengthType pduLength = 0u;

        SchM_Enter_IpduM_IPDUM_EXCLUSIVE_AREA_0();

        /* Extra buffer is necessary to avoid interruption by rxIndication. */
        VStdLib_MemCpy_s(rxMfBuffer, IpduM_GetSizeOfRxContainerMainFunctionBuffer(), IpduM_ContainerRx_GetCurrentlyReadContainerRxBufferPtr(rxContainerId), bufferInstanceLength);  /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_IPDUM_VSTDLIB_SAFE */  /* VCA_IPDUM_VSTDLIB_MEMCPY_SAFE */

        pduInfo.SduDataPtr = rxMfBuffer;
        pduInfo.SduLength = bufferInstanceLength;

        {
          IpduM_RxContainerReceivedSizeType rxContainerReceivedSizeInstanceIdx = ((IpduM_RxContainerReceivedSizeType) IpduM_GetRxContainerReceivedSizeStartIdxOfRxContainerPdu(rxContainerId)) + IpduM_GetContainerReadIdxOfRxContainerBufferInfo(rxContainerId);

          if(rxContainerReceivedSizeInstanceIdx < IpduM_GetSizeOfRxContainerReceivedSize())  /* COV_IPDUM_DEFENSIVE_PROGRAMMING */
          {
            pduLength = IpduM_GetRxContainerReceivedSize(rxContainerReceivedSizeInstanceIdx);
          }
        }

        IpduM_ContainerRx_RemoveOldestElementOfQueue(rxContainerId);
        SchM_Exit_IpduM_IPDUM_EXCLUSIVE_AREA_0();

        if(IpduM_GetSizeOfRxContainerMainFunctionBuffer() >= bufferInstanceLength) /* COV_IPDUM_DEFENSIVE_PROGRAMMING */
        {
          IpduM_ContainerRx_UnpackContainerPdu(rxContainerId, &pduInfo, pduLength);    /* SBSW_IPDUM_MAINFUNCTIONRX_CALL_UNPACKRXCONTAINERPDU */
        }
        
        queueLengthCounter--;
        if(queueLengthCounter == 0u)
        {
          break;
        }
      }
    }
  }
}
#endif

#define IPDUM_STOP_SEC_CODE
#include "MemMap.h"    /* PRQA S 5087 */        /*  MD_MSR_MemMap */

/**********************************************************************************************************************
 * GLOBAL MISRA / PCLINT JUSTIFICATION
 *********************************************************************************************************************/
/* *INDENT-OFF* */
/* module specific MISRA deviations:
   MD_IpduM_2004: Misra Rule 15.7
     Reason:      There is no concluding "else" in an "if-elseif" statement.
     Risk:        No risk..
     Prevention:  This is ok because both paths trigger a transmission and there are no extra steps to do if both don't.

   MD_IpduM_2842: Index Access to pointer array
     Reason:      QAC cannot determine whether the pointer value is correct. However, the ComStackLib generates
                  those values and if the indices used are correct, the pointers are, too. The indices are either
                  calculated using ComStackLib indirections, ComStackLib SizeOf() macros or passed on by a caller
                  of this function, hence being checked by the caller. So all indices used in these macros are
                  correct.
     Risk:        No risk.
     Prevention:  No prevention necessary.
   
   MD_IpduM_2982_initValue: Redundant assignment, value always modified.
     Reason:      This init value is used to ensure the pduInfo ptr is always containing a valid size.
     Risk:        No risk.
     Prevention:  No prevention necessary.
     
   MD_IpduM_2985: Misra Rule 2.2
     Reason:      The bit shift of 0 bits is because of maintainability and comprehensibility. Or the result depends on the configuration.
     Risk:        No risk, because only warning that the operation is redundant.
     Prevention:  No prevention necessary.
     
*/

/* COV_JUSTIFICATION_BEGIN

  \ID COV_IPDUM_SINGLE_HEADERSIZE_CONFIG
    \ACCEPT TX
    \ACCEPT TF tf tx
    \ACCEPT TF tx tf
    \ACCEPT Tx tx tx
    \REASON Configurations with only one type of headersize needed to cover this.

  \ID COV_IPDUM_VAR_DEPENDENT_SWITCH
    \ACCEPT TX
    \ACCEPT TF tf tx
    \ACCEPT TF tx tf
    \ACCEPT TX tx tx
    \ACCEPT TX tf tf tf
    \ACCEPT TX tx tf tf
    \ACCEPT TF tx tf tf
    \REASON The nested switch depends on a previous switch.

  \ID COV_IPDUM_DEPENDENT_VALUES
    \ACCEPT TF tf tx tf
    \REASON Generated values depend on each other.

  \ID COV_IPDUM_TXCONF_ALWAYS_ZERO
    \ACCEPT XF
    \ACCEPT TX tx xx xx
    \ACCEPT TF tf tx tf
    \REASON A TxConfirmation Timeout of zero is a special value which is used for unused TxConfirmation Timeouts.

  \ID COV_IPDUM_DEFENSIVE_PROGRAMMING
    \ACCEPT TX
    \ACCEPT XF
    \ACCEPT TF tf tx
    \ACCEPT TX tx tx
    \REASON This condition is used because of safe programming, should never be false in production code.

  \ID COV_IPDUM_INVALID_CONFIGURATION
    \ACCEPT TX tf tf tx
    \ACCEPT TF tx tf
    \REASON This condition (a && b || c) cannot be fully covered for c==false because the first condition (before the  "||") will alwas match false if c== false, so c is not evaluated in this case. Coverage of this code section would require an invalid configuration.
            If c is preprocessed out, the only valid configuration is a==true and b==true/false.

  \ID COV_IPDUM_REQUESTQUEUE_WITH_NONE_HEADER
    \ACCEPT TF tf tx
    \REASON Request queue (last is best) with none-header is not supported. None-headers internally are always using the data queue.

  \ID COV_IPDUM_SEARCH_HEADER_ID_LOOP_ABORT
    \ACCEPT TX
    \REASON This is a search function, normal termination of the loop would only occur if the searched item was not found.

  \ID COV_IPDUM_COMPLEMENTARY_CHECK
    \ACCEPT TF tf tx tf
    \REASON This condition (a || (!a && b)) cannot be fully covered for a==true because the first condition (before the "||") will always match, so the second (!a) is not evaluated.

  \ID COV_IPDUM_TERMINATION_ZEROES
    \ACCEPT TF tx tf
    \REASON Double condition in the loop for safe programming reasons

  \ID COV_IPDUM_HEADERSIZE_IN_SIZE_CALCULATION
    \ACCEPT TX tf tf
    \REASON This function is only used with non-zero headers, so in (a || b) always either a or b is true, so the composite condition can never go false.
    
COV_JUSTIFICATION_END */

/* *INDENT-ON* */

/**********************************************************************************************************************
  END OF FILE: IpduM_Container.c
**********************************************************************************************************************/
