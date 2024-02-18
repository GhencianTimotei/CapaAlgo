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
/*!        \file  NvM_Cbk.h
 *        \brief  NvM callback header file
 *      \details  This file declares callback functions NvM_JobEndNotification and NvM_JobErrorNotification.
 *                Callbacks are public, i.e. they will be called from outside of the NvM - usually Fee or Ea.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#if (!defined NVM_CBK_H)
#define NVM_CBK_H

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define NVM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 * NvM_JobEndNotification
 *********************************************************************************************************************/
/*! \brief If invoked, it will set the current pending job's result to NVM_REQ_OK.
 *  \details The function does nothing in case the NvM is running in polling mode! (empty function)
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
extern FUNC(void, NVM_PUBLIC_CODE) NvM_JobEndNotification(void);

/**********************************************************************************************************************
 * NvM_JobErrorNotification
 *********************************************************************************************************************/
/*! \brief If invoked, it will check the underlying module's job result and set current NvM pending job's result accordingly.
 *  \details The function does nothing in case the NvM is running in polling mode! (empty function)
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
extern FUNC(void, NVM_PUBLIC_CODE) NvM_JobErrorNotification(void);

#define NVM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* NVM_CBK_H */

/**********************************************************************************************************************
 *  END OF FILE: NvM_Cbk.h
 *********************************************************************************************************************/


