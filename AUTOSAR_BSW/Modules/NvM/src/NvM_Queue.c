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
/*!        \file  NvM_Queue.c
 *        \brief  NvM queue submodule source file
 *      \details  This sub-module contains the queue-handling of the (optionally) prioritized job queue.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#define NVM_QUEUE_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
/* NvM_JobProc.h includes all needed headers, e.g. configuration, action, query... */
#include "NvM_JobProc.h"
#include "NvM_Queue.h"

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/
#ifndef NVM_LOCAL /* COV_NVM_COMPATIBILITY */
# define NVM_LOCAL static
#endif

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/
#define NVM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

VAR(NvM_JobType, NVM_PRIVATE_DATA) NvM_CurrentJob_t;

#define NVM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Queueing is only needed in configuration classes 2 and 3. */
#if (NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1)

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#define NVM_IMMEDIATE_JOB_PRIO  (0x00u)
#define NVM_LOWEST_JOB_PRIO     (0xFFu)
#define NVM_LIST_END            (0xFFu)

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/*! Queue list pointer type. */
typedef P2VAR(NvM_QueueEntryRefType, AUTOMATIC, NVM_PRIVATE_DATA) NvM_QueueListHeadRefType;
typedef CONSTP2CONST(NvM_QueueEntryType, AUTOMATIC, NVM_PRIVATE_DATA) NvM_QueueEntryConstPtrToConstType;

typedef struct
{
    NvM_QueueEntryRefType SrvList; /*!< Points to next queue element to process. */
    NvM_QueueEntryRefType EmptyList; /*!< Points to next empty queue element to use. */
} NvM_JobQueueType; /*!< Structure storing the next queue indexes - empty and full element. */

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/
#define NVM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if (NVM_JOB_PRIORISATION == STD_ON)
NVM_LOCAL VAR(NvM_JobQueueType, NVM_PRIVATE_DATA) NvM_HighPrioQueue;

NVM_LOCAL VAR(NvM_QueueEntryRefType, NVM_PRIVATE_DATA) NvM_LastJobEntry;
#endif /* (NVM_JOB_PRIORISATION == STD_ON) */

NVM_LOCAL VAR(NvM_JobQueueType, NVM_PRIVATE_DATA) NvM_NormalPrioQueue;

#define NVM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define NVM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 * NvM_QueuePush
 *********************************************************************************************************************/
/*! \brief Add job to queue.
 *  \details Pushes the given element onto the given list, i.e. the element is inserted at list head.
 *  \param[in] Queue as an index to the next queue element. Caller has to ensure validity.
 *  \param[in] Elem as an index to the queue, shall be enqueued at the end of the linked list.
 *             Caller has to ensure validity.
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \config Configuration class is > 1
 *  \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_QueuePush(NvM_QueueListHeadRefType Queue, NvM_QueueEntryRefType Elem);

/**********************************************************************************************************************
 * NvM_QueuePop
 *********************************************************************************************************************/
/*! \brief Removes first element from queue.
 *  \details Pops the first element from the given list, i.e. the element is removed from the list and will be returned.
 *           The given list shall not be empty!
 *  \param[in,out] Queue as an index to the queue to pop out of the queue. Caller has to ensure validity.
 *  \return given element's index
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \config Configuration class is > 1
 *  \pre -
 */
NVM_LOCAL FUNC(NvM_QueueEntryRefType, NVM_PRIVATE_CODE) NvM_QueuePop(NvM_QueueListHeadRefType Queue);

/**********************************************************************************************************************
 * NvM_QueueFindBlock
 *********************************************************************************************************************/
/*! \brief Searches for requested block within the queue.
 *  \details Searches a specific block in the queue and returns a reference to the queue element containing the blockId
             The queue is not modified here!
             Must be called within a critical section (because preemption might result in queue modification, corrupting
             the search.
 *  \param[in] QueueHead as an index to the queue to start and end the search with (ring list).
 *             Caller has to ensure validity.
 *  \param[in] BlockId in range [1, (number of blocks - 1)].
 *  \return queue element which stores the blockId if blockId was found within queue
 *  \return queue end if blockId wasn't found within queue
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \config Configuration class is > 1
 *  \pre -
 */
NVM_LOCAL FUNC(NvM_QueueEntryRefType, NVM_PRIVATE_CODE) NvM_QueueFindBlock(NvM_QueueEntryRefType QueueHead, NvM_BlockIdType BlockId);

#if (NVM_JOB_PRIORISATION == STD_ON)
/**********************************************************************************************************************
 * NvM_QueueRequeueLastJob
 *********************************************************************************************************************/
/*! \brief Requeus the last job.
 *  \details Puts the last found job back into the Normal Prio Queue. It will be inserted at the list end.
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \config Configuration class is > 1 and priority handling is enabled
 *  \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_QueueRequeueLastJob(void);
#endif

#define NVM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
#define NVM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
*  NvM_QueueInit
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, NVM_PRIVATE_CODE) NvM_QueueInit(void)
{
    uint8 maxQueueIndex = (NVM_SIZE_STANDARD_JOB_QUEUE + NVM_SIZE_IMMEDIATE_JOB_QUEUE - 1u);
    uint8 index = maxQueueIndex;

    /* link all list elements */
    while(index > 0u)
    {
        /* element at <index> is linked to its predecessor */
        NvM_JobQueue_at[index].PrevEntry = index - 1u; /* SBSW_NvM_AccessJobQueue */
        /* now we are at the predecessor, link it with it successor */
        NvM_JobQueue_at[(index - 1u)].NextEntry = index; /* SBSW_NvM_AccessJobQueue */
        /* Initializing the SeviceId member of each list element is not necessary, because initially
           they are in the "empty" list --> the member will not be used.
           Once an element gets into the job queue, the Service Id will be initialized */
        --index;
    }

    /* split the lists into two separate ring lists */
    index = NVM_SIZE_STANDARD_JOB_QUEUE;

#if (NVM_JOB_PRIORISATION == STD_ON)
        NvM_LastJobEntry = NVM_LIST_END;

        NvM_HighPrioQueue.SrvList = NVM_LIST_END;
        NvM_HighPrioQueue.EmptyList = index;

        NvM_JobQueue_at[maxQueueIndex].NextEntry = index; /* SBSW_NvM_AccessJobQueue */
        NvM_JobQueue_at[index].PrevEntry = maxQueueIndex; /* SBSW_NvM_AccessJobQueue */
#endif

    /* Normal priority queue. */
    index--;
    NvM_JobQueue_at[index].NextEntry = 0u; /* SBSW_NvM_AccessJobQueue */
    NvM_JobQueue_at[0].PrevEntry = index; /* SBSW_NvM_AccessJobQueue */

    NvM_NormalPrioQueue.EmptyList = 0u;
    NvM_NormalPrioQueue.SrvList = NVM_LIST_END;
}

/**********************************************************************************************************************
*  NvM_QueueJob
**********************************************************************************************************************/
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
FUNC(boolean, NVM_PRIVATE_CODE) NvM_QueueJob(NvM_BlockIdType BlockId,
                                   NvM_InternalServiceIdType ServiceId,
                                          NvM_RamAddressType RamAddress
    )
{
    boolean retVal = FALSE;
    boolean queueFull;
    boolean blockAlreadyPending;
    /* get block management area */
    const NvM_RamMngmtPtrType ramMngmtPtr =
        ((BlockId & NVM_DCM_BLOCK_OFFSET) != 0u) ? (&NvM_DcmBlockMngmt_t) : (&NvM_BlockMngmtArea_at[BlockId]);

#if(NVM_JOB_PRIORISATION == STD_ON)
    const uint8 priority = (uint8)NvM_BlockDescriptorTable_at[NVM_BLOCK_FROM_DCM_ID(BlockId)].BlockPrio_u8;
    /* NvM_HighPrioQueue is only the right queue if block has an immediate priority, current job is a
      write-job and requested block is not a DCM-Block. Otherwise NvM_NormalPrioQueue is right queue. */
    P2VAR(NvM_JobQueueType, AUTOMATIC, NVM_PRIVATE_DATA) usedQueue =
        ((priority == 0u) && (ServiceId == NVM_INT_FID_WRITE_BLOCK) && ((BlockId & NVM_DCM_BLOCK_OFFSET) == 0u)) ?
        (&NvM_HighPrioQueue) : (&NvM_NormalPrioQueue);
#else
    P2VAR(NvM_JobQueueType, AUTOMATIC, NVM_PRIVATE_DATA) usedQueue = &NvM_NormalPrioQueue;
#endif
    /* #200 critical section (Reason: During accessing the job queue, it shall not be possible to access it from another task) */
    NvM_EnterCriticalSection();
    /* check queue fill status before queuing the block! */
    queueFull = (usedQueue->EmptyList == NVM_LIST_END);
    blockAlreadyPending = (ramMngmtPtr->NvRamErrorStatus_u8 == NVM_REQ_PENDING);
    /* #210 queue is not full and the requested block isn't already pending */
    if((queueFull == FALSE) && (blockAlreadyPending == FALSE))
    {
        /* #211 find next free element in queue */
        const NvM_QueueEntryRefType elem = NvM_QueuePop(&usedQueue->EmptyList); /* SBSW_NvM_FuncCall_PtrParam_Queue */
        CONSTP2VAR(NvM_QueueEntryType, AUTOMATIC, NVM_PRIVATE_DATA) elemPtr = &NvM_JobQueue_at[elem];
        /* #212 setup and queue NvM job */
        elemPtr->BlockId   = BlockId; /* SBSW_NvM_AccessJobQueue */
        elemPtr->RamAddr_t = RamAddress; /* SBSW_NvM_AccessJobQueue */
        elemPtr->ServiceId = ServiceId; /* SBSW_NvM_AccessJobQueue */
#if(NVM_JOB_PRIORISATION == STD_ON)
        elemPtr->JobPrio = priority; /* SBSW_NvM_AccessJobQueue */
#endif
        NvM_QueuePush(&usedQueue->SrvList, elem); /* SBSW_NvM_FuncCall_PtrParam_Queue */
        /* #213 set the block status to NVM_REQ_PENDING */
        ramMngmtPtr->NvRamErrorStatus_u8 = NVM_REQ_PENDING; /* SBSW_NvM_AccessBlockManagementArea */
        /* block queued and pending, return successfully */
        retVal = TRUE;
    }
    /* exit critical section */
    NvM_ExitCriticalSection();
    /* #300 queue was full, request to queue the next block leads to queue overflow */
    if(queueFull == TRUE)
    {
        /* #310 report queue overflow to DEM */
        NvM_DemReportErrorQueueOverflow();
    }
    /* #400 queue wasn't full, block wasn't pending, queuing was successful */
    else if (blockAlreadyPending == FALSE)
    {
        /* #410 invoke notifications */
        /* invoke the notification out of the critical section! */
        NvM_BlockNotification(BlockId, NvM_IntServiceDescrTable_at[ServiceId].PublicFid_t, NVM_REQ_PENDING);
    }
    else
    {
        /* nothing to do here */
    }

    return retVal;
}

/**********************************************************************************************************************
*  NvM_UnQueueJob
**********************************************************************************************************************/
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
FUNC(boolean, NVM_PRIVATE_CODE) NvM_UnQueueJob(NvM_BlockIdType BlockId)
{ 
   const NvM_RamMngmtPtrType NvM_RamMngmt_ptloc =
    ((BlockId & NVM_DCM_BLOCK_OFFSET) != 0u) ? (&NvM_DcmBlockMngmt_t) : (&NvM_BlockMngmtArea_at[BlockId]);
    boolean retVal = FALSE;
    NvM_QueueEntryRefType elem; 
    P2VAR(NvM_JobQueueType, AUTOMATIC, NVM_PRIVATE_DATA) UsedQueue = &NvM_NormalPrioQueue;

    /* Entire Search is a critical section, since pre-emption might change the queue (esp. list head),
       which might cause the loop to never finish (especially when NvM_MainFunction empties the queue */
    NvM_EnterCriticalSection();

    /* If NVM_JOB_PRIORISATION is ON we might have two queues to scan:                     *
     *   - For a HighPrio job (prio == 0) both queues (Reads are not high prio!)           *
     *   - For a Low Prio job (prio != 0) only the normal prio queue                       *
     * ==> Always start searching in NormalPrioQueue                                       *
     * ==> conditionally search HighPrioQueue.                                             *
     * After that UsedQueue points to the Queue where the Block was found                  */

    elem = NvM_QueueFindBlock(UsedQueue->SrvList, BlockId);

#if(NVM_JOB_PRIORISATION == STD_ON)
    /* If nothing was found in normal prio queue, look into high prio queue, if it is a high prio block *
     * (and not its DCM-alias)                                                                          */
    if((elem == NVM_LIST_END) &&
        (NvM_BlockDescriptorTable_at[NVM_BLOCK_FROM_DCM_ID(BlockId)].BlockPrio_u8 == 0u) &&
        ((BlockId & NVM_DCM_BLOCK_OFFSET) == 0u))
    {
        UsedQueue = &NvM_HighPrioQueue;
        elem = NvM_QueueFindBlock(UsedQueue->SrvList, BlockId);
    }
#endif

    /* If block was found, remove it from the queue <UsedQueue>,    *
     *  free the queue Item and set block's error/status to CANCELED */
    if(elem != NVM_LIST_END)
    {
        const NvM_InternalServiceIdType srvId = NvM_JobQueue_at[elem].ServiceId;
        const NvM_ServiceIdType   PublicServiceId =  NvM_IntServiceDescrTable_at[srvId].PublicFid_t;
        NvM_QueueEntryRefType tmpElem;

        retVal = TRUE;


        /* pop "elem" of queue -> pretend "elem" being the head of the job queue. 
         * After that "elem" point to its successor (if any); tmpElem points to original entry */
        tmpElem = NvM_QueuePop(&elem); /* SBSW_NvM_FuncCall_PtrParam_Queue */

        /* if we removed the first element from the queue, we need to adjust the real queue head.  *
         * Otherwise it was not changed by removing the "elem"                                     */    
        if(UsedQueue->SrvList == tmpElem)
        {
            UsedQueue->SrvList = elem; /* SBSW_NvM_AccessPtr_UsedQueue */
        }
      
        /* free the element --> add it to free-list; normally "elem" does not point to the correct entry anymore */
        NvM_QueuePush(&UsedQueue->EmptyList, tmpElem); /* SBSW_NvM_FuncCall_PtrParam_Queue */

        NvM_RamMngmt_ptloc->NvRamErrorStatus_u8 = NVM_REQ_CANCELED; /* SBSW_NvM_AccessBlockManagementArea */
        NvM_BlockNotification(BlockId, PublicServiceId, NVM_REQ_CANCELED);
    }

    NvM_ExitCriticalSection();

    return retVal;
} 

/**********************************************************************************************************************
*  NvM_QryNormalPrioJob
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryNormalPrioJob(void)
{
    return (boolean)(NvM_NormalPrioQueue.SrvList != NVM_LIST_END);
}

/**********************************************************************************************************************
*  NvM_ActGetNormalPrioJOb
**********************************************************************************************************************/
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
 */
FUNC(void, NVM_PRIVATE_CODE) NvM_ActGetNormalPrioJob(void)
{
#if (NVM_JOB_PRIORISATION == STD_ON)
    /* search for the highest prioritized entry */
    NvM_QueueEntryRefType maxPrioElem;
    NvM_QueueEntryRefType currentElem;
    uint8 maxPrio;

    NvM_EnterCriticalSection();
    /* We have to guarantee, that we really get the last element.
     * We only get it, as long as our head element remains the head element.
     * Otherwise it would just point to its predecessor. */
    currentElem = NvM_JobQueue_at[NvM_NormalPrioQueue.SrvList].PrevEntry;
    maxPrioElem = NvM_JobQueue_at[NvM_NormalPrioQueue.SrvList].PrevEntry;

    maxPrio = NvM_JobQueue_at[maxPrioElem].JobPrio;

    NvM_ExitCriticalSection();

    /* the actual iteration over the queue is not a critical section,
       because the consistency of the list (prev and next pointers) is guaranteed by
       NvM_QueueJob()
       If the queue contains only one element, it will be checked twice
       (one iteration - it will be compared with itself -> that's no problem */
    do
    {
        currentElem = NvM_JobQueue_at[currentElem].PrevEntry;

        if(NvM_JobQueue_at[currentElem].JobPrio < maxPrio)
        {
            maxPrioElem = currentElem;
            maxPrio = NvM_JobQueue_at[currentElem].JobPrio;
        }
    }
    while(currentElem != NvM_NormalPrioQueue.SrvList);


    /* now, we have the entry of interest. */
    NvM_LastJobEntry = maxPrioElem;

    NvM_CurrentJob_t.JobBlockId_t = NvM_JobQueue_at[maxPrioElem].BlockId;
    NvM_CurrentJob_t.JobServiceId_t = NvM_JobQueue_at[maxPrioElem].ServiceId;
    NvM_CurrentJob_t.RamAddr_t = NvM_JobQueue_at[maxPrioElem].RamAddr_t;


    /* remove entry from the queue, discard the return value */
    NvM_EnterCriticalSection();

    (void)NvM_QueuePop(&maxPrioElem); /* SBSW_NvM_FuncCall_PtrParam_Queue */

    /* if it was the first element of the queue, we need to adjust the real queue head.
     * Otherwise it would not have been changed be removing the entry. */
    if(NvM_NormalPrioQueue.SrvList == NvM_LastJobEntry)
    {
        NvM_NormalPrioQueue.SrvList = maxPrioElem;
    }

    NvM_ExitCriticalSection();
#else

    NvM_QueueEntryRefType elem;

    NvM_EnterCriticalSection();
    /* just take the last queue element, don't store it in NvM_LastJobEntry (it does not exist),
     * but remove it from the queue.
     * Just update the queue head to point to its prev element (which is the tail), then pop.
       After that, the head points to the head again.
     */
    NvM_NormalPrioQueue.SrvList = NvM_JobQueue_at[NvM_NormalPrioQueue.SrvList].PrevEntry;
    elem = NvM_QueuePop(&NvM_NormalPrioQueue.SrvList); /* SBSW_NvM_FuncCall_PtrParam_Queue */

    /* free the element --> add it to free-list */
    NvM_QueuePush(&NvM_NormalPrioQueue.EmptyList, elem); /* SBSW_NvM_FuncCall_PtrParam_Queue */

    NvM_CurrentJob_t.JobBlockId_t = NvM_JobQueue_at[elem].BlockId;
    NvM_CurrentJob_t.JobServiceId_t = NvM_JobQueue_at[elem].ServiceId;
    NvM_CurrentJob_t.RamAddr_t = NvM_JobQueue_at[elem].RamAddr_t;


    NvM_ExitCriticalSection();
#endif /* (NVM_JOB_PRIORISATION == STD_ON) */
}

#if (NVM_JOB_PRIORISATION == STD_ON)
/**********************************************************************************************************************
*  NvM_QryHighPrioJob
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryHighPrioJob(void)
{
    return (boolean)(NvM_HighPrioQueue.SrvList != NVM_LIST_END);
}

/**********************************************************************************************************************
*  NvM_ActGetHighPrioJob
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, NVM_PRIVATE_CODE) NvM_ActGetHighPrioJob(void)
{
    NvM_QueueEntryRefType elem;

    /* #10 Cancel the underlying module and re-queue the canceled job. This shall only be done
     * in case currently there is a NORMAL PRIO or MULTI BLOCK (only if KilWriteAll enabled) job */
# if (NVM_KILL_WRITEALL_API == STD_ON)
    if((NvM_TaskState_t == NVM_STATE_NORMAL_PRIO_JOB) || (NvM_TaskState_t == NVM_STATE_MULTI_BLOCK_JOB))
# else
    if(NVM_STATE_NORMAL_PRIO_JOB == NvM_TaskState_t)
#endif
    {
        NvM_ActCancelNV();

        NvM_QueueRequeueLastJob();
    }

    NvM_EnterCriticalSection();

    /* make the last entry (predecessor of list head) the current entry */
    NvM_HighPrioQueue.SrvList = NvM_JobQueue_at[NvM_HighPrioQueue.SrvList].PrevEntry;

    /* get the head element (it's actually the last one) from list, the new head is its successor,
     * which is the original head */
    elem = NvM_QueuePop(&NvM_HighPrioQueue.SrvList); /* SBSW_NvM_FuncCall_PtrParam_Queue */

    /* an immediate write job cannot be interrupted, therefore we can free the list element */
    NvM_QueuePush(&NvM_HighPrioQueue.EmptyList, elem); /* SBSW_NvM_FuncCall_PtrParam_Queue */

    NvM_CurrentJob_t.JobBlockId_t   = NvM_JobQueue_at[elem].BlockId;
    NvM_CurrentJob_t.JobServiceId_t = NvM_JobQueue_at[elem].ServiceId;
    NvM_CurrentJob_t.RamAddr_t      = NvM_JobQueue_at[elem].RamAddr_t;

    /* make sure that the last job entry is empty --> no re-queuing will be performed */
    NvM_LastJobEntry = NVM_LIST_END;

    NvM_ExitCriticalSection();
}

/**********************************************************************************************************************
*  NvM_ActQueueFreeLastJob
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, NVM_PRIVATE_CODE) NvM_ActQueueFreeLastJob(void)
{
    if(NvM_LastJobEntry != NVM_LIST_END)
    {
        NvM_EnterCriticalSection();
        /* add element at list start */
        NvM_QueuePush(&NvM_NormalPrioQueue.EmptyList, NvM_LastJobEntry); /* SBSW_NvM_FuncCall_PtrParam_Queue */

        NvM_LastJobEntry = NVM_LIST_END;
        NvM_ExitCriticalSection();
    }
}
#endif /* (NVM_JOB_PRIORISATION == STD_ON) */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
*  NvM_QueuePush
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_QueuePush(NvM_QueueListHeadRefType Queue, NvM_QueueEntryRefType Elem)
{
    CONSTP2VAR(NvM_QueueEntryType, AUTOMATIC, NVM_PRIVATE_DATA) elemPtr = &NvM_JobQueue_at[Elem];

    if(*Queue == NVM_LIST_END)
    {
        /* queue is currently empty. put new element in, link it with itself */
        *Queue = Elem; /* SBSW_NvM_AccessPtr_QueueIndex */
        elemPtr->NextEntry = Elem; /* SBSW_NvM_AccessJobQueue */
        elemPtr->PrevEntry = Elem; /* SBSW_NvM_AccessJobQueue */
    }
    else
    {
        CONSTP2VAR(NvM_QueueEntryType, AUTOMATIC, NVM_PRIVATE_DATA) NextPtr = &NvM_JobQueue_at[*Queue];

        elemPtr->NextEntry = *Queue; /* SBSW_NvM_AccessJobQueue */
        elemPtr->PrevEntry = NextPtr->PrevEntry;  /* SBSW_NvM_AccessJobQueue */

        NvM_JobQueue_at[NextPtr->PrevEntry].NextEntry = Elem; /* SBSW_NvM_AccessJobQueue */
        NextPtr->PrevEntry = Elem; /* SBSW_NvM_AccessJobQueue */
        *Queue = Elem; /* SBSW_NvM_AccessPtr_QueueIndex */
    }
}

/**********************************************************************************************************************
*  NvM_QueuePop
**********************************************************************************************************************/
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
NVM_LOCAL FUNC(NvM_QueueEntryRefType, NVM_PRIVATE_CODE) NvM_QueuePop(NvM_QueueListHeadRefType Queue)
{
    const uint8 retVal = *Queue;
    NvM_QueueEntryConstPtrToConstType elemPtr = &NvM_JobQueue_at[retVal];

    if(elemPtr->NextEntry == retVal)
    {
        /* element is linked with itself, therefore the list is empty, now */
        *Queue = NVM_LIST_END; /* SBSW_NvM_AccessPtr_QueueIndex */
    }
    else
    {
        *Queue = elemPtr->NextEntry; /* SBSW_NvM_AccessPtr_QueueIndex */

        NvM_JobQueue_at[elemPtr->NextEntry].PrevEntry = elemPtr->PrevEntry; /* SBSW_NvM_AccessJobQueue */
        NvM_JobQueue_at[elemPtr->PrevEntry].NextEntry = elemPtr->NextEntry; /* SBSW_NvM_AccessJobQueue */
    }

    return retVal;
}

/**********************************************************************************************************************
*  NvM_QueueFindBlock
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
NVM_LOCAL FUNC(NvM_QueueEntryRefType, NVM_PRIVATE_CODE) NvM_QueueFindBlock(NvM_QueueEntryRefType QueueHead, NvM_BlockIdType BlockId)
{
    NvM_QueueEntryRefType entryRef = NVM_LIST_END;

    if(QueueHead != NVM_LIST_END)
    {
        NvM_QueueEntryRefType elem = QueueHead;
        /* search for the block in the queue and prevent from scanning an empty queue */
        do
        {
            elem = NvM_JobQueue_at[elem].NextEntry;

            if(NvM_JobQueue_at[elem].BlockId == BlockId)
            {
                /* found the entry */
                entryRef = elem;
                break;
            }
        }
        while(elem != QueueHead);
    }

    return entryRef;
}

#if (NVM_JOB_PRIORISATION == STD_ON)
/**********************************************************************************************************************
*  NvM_QueueRequeueLastJob
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_QueueRequeueLastJob(void)
{
    if(NvM_LastJobEntry != NVM_LIST_END)
    {
        NvM_EnterCriticalSection();
        /* add element at list start */
        NvM_QueuePush(&NvM_NormalPrioQueue.SrvList, NvM_LastJobEntry); /* SBSW_NvM_FuncCall_PtrParam_Queue */

        /*  set the highest possible priority */
        NvM_JobQueue_at[NvM_LastJobEntry].JobPrio = NVM_IMMEDIATE_JOB_PRIO; /* SBSW_NvM_AccessJobQueue */

        /* shift Queue Start to next element, remember: it is a ring list ... */
        NvM_NormalPrioQueue.SrvList = NvM_JobQueue_at[NvM_LastJobEntry].NextEntry;

        NvM_LastJobEntry = NVM_LIST_END;
        NvM_ExitCriticalSection();
    }
}
#endif /* (NVM_JOB_PRIORISATION == STD_ON) */

#define NVM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* (NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1) */

/**********************************************************************************************************************
 *  END OF FILE: NvM_Queue.c
 *********************************************************************************************************************/
