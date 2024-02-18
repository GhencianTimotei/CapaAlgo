/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  NvM_Queue.h
 *        \brief  NvM queue submodule header file
 *      \details  This submodule contains the queue-handling of the (optionally) prioritized job queue.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#if (!defined NVM_QUEUE_H_)
#define NVM_QUEUE_H_

/* Queueing is only needed in configuration classes 2 and 3. */
#if (NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1)

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define NVM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 * NvM_QueueInit
 *********************************************************************************************************************/
/*! \brief Initializes the NvM submodule NvM_Queue
 *  \details The queue (normal prio and high prio, if enabled) and internal variables will be reset.
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \config Configuration class is > 1
 *  \pre -
 */
extern FUNC(void, NVM_PRIVATE_CODE) NvM_QueueInit(void);

/**********************************************************************************************************************
 * NvM_QueueJob
 *********************************************************************************************************************/
/*! \brief Puts a job into the queue.
 *  \details In case priority handling is enabled, the function decides whether the queue the job in normal or high
 *           priority queue. The job will only be queued, if the block isn't already in pending state!
 *  \param[in] BlockId in range [1, (number of blocks - 1)].
 *  \param[in] ServiceId as a request type. Caller has to ensure validity.
 *  \param[in] RamAddress pointing to the buffer used to for request. May be NULL_PTR for specific BlockIds.
 *  \return TRUE job was queued successfully
 *  \return FALSE otherwise
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \config Configuration class is > 1
 *  \pre -
 *  \trace CREQ-748
 */
extern FUNC(boolean, NVM_PRIVATE_CODE) NvM_QueueJob(NvM_BlockIdType BlockId, NvM_InternalServiceIdType ServiceId, NvM_RamAddressType RamAddress);

/**********************************************************************************************************************
 * NvM_UnQueueJob
 *********************************************************************************************************************/
/*! \brief Removes the job for given BlockId from queue.
 *  \details The function searches for the given Block Id within normal or high priority queue (depending on configured
 *           NvM Block priority) and removes the job from queue, if there is one queued.
 *  \param[in] BlockId in range [1, (number of blocks - 1)].
 *  \return TRUE unqueuing was successful
 *  \return FALSE otherwise
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \config Configuration class is > 1
 *  \pre -
 */
extern FUNC(boolean, NVM_PRIVATE_CODE) NvM_UnQueueJob(NvM_BlockIdType BlockId);

/**********************************************************************************************************************
 * NvM_QryNormalPrioJob
 *********************************************************************************************************************/
/*! \brief Checks the normal priority job queue for a job.
 *  \details Checks the normal priority job queue for a job.
 *  \return TRUE queue is not empty
 *  \return FALSE queue is empty
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \config Configuration class is > 1
 *  \pre -
 */
extern FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryNormalPrioJob(void);

/**********************************************************************************************************************
 * NvM_ActGetNormalPrioJob
 *********************************************************************************************************************/
/*! \brief Setups the NvM internal job variable for next job.
 *  \details Scans the given queue for the entry with highest priority, located nearest to the list end.
 *           The element is removed from the list, but stored in NvM_lastJobEntry. The job parameters will be copied
 *           to the passed job structure. The queue is expected to contain at least one element.
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \config Configuration class is > 1
 *  \pre -
 */
extern FUNC(void, NVM_PRIVATE_CODE) NvM_ActGetNormalPrioJob(void);

#if (NVM_JOB_PRIORISATION == STD_ON)
/**********************************************************************************************************************
 * NvM_QryHighPrioJob
 *********************************************************************************************************************/
/*! \brief Checks the high priority job queue for a job.
 *  \details Checks the high priority job queue for a job.
 *  \return TRUE queue is not empty
 *  \return FALSE queue is empty
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \config Configuration class is > 1 and priority handling is enabled
 *  \pre -
 */
extern FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryHighPrioJob(void);

/**********************************************************************************************************************
 * NvM_ActGetHighPrioJob
 *********************************************************************************************************************/
/*! \brief Setups the NvM internal job variable for next high priority job.
 *  \details Retrieves the next job from the high priority job queue. The next job is the last element in the list.
 *           The Queue is expected to contain at least one element.
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \config Configuration class is > 1 and priority handling is enabled
 *  \pre -
 */
extern FUNC(void, NVM_PRIVATE_CODE) NvM_ActGetHighPrioJob(void);

/**********************************************************************************************************************
 * NvM_ActQueueFreeLastJob
 *********************************************************************************************************************/
/*! \brief Frees the last found job item - it will be added to the normal queue's free list.
 *  \details Frees the last found job item - it will be added to the normal queue's free list.
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \config Configuration class is > 1 and priority handling is enabled
 *  \pre -
 */
extern FUNC(void, NVM_PRIVATE_CODE) NvM_ActQueueFreeLastJob(void);
#endif /* (NVM_JOB_PRIORISATION == STD_ON) */

#define NVM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* (NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1) */

#endif /* NVM_QUEUE_H_ */

/**********************************************************************************************************************
 *  END OF FILE: NvM_Queue.h
 *********************************************************************************************************************/
