/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2020 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**         \file  ComM_BusSM.h
 *         \brief  Communication Manager ASR4
 *
 *       \details  Callback API of the communication manager for the Bus state manager
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

#ifndef COMM_BUSSM_H
# define COMM_BUSSM_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "ComM_Cfg.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
# define COMM_BUSSM_MAJOR_VERSION    (0x13u)
# define COMM_BUSSM_MINOR_VERSION    (0x00u)
# define COMM_BUSSM_PATCH_VERSION    (0x01u)

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
 *  CALLBACK FUNCTIONS PROTOTYPES (called by appropriate bus state manager)
 *********************************************************************************************************************/

# define COMM_START_SEC_CODE
/* PRQA S 5087 1 */ /* MD_MSR_MemMap */
# include "MemMap.h"

/*********************************************************************************************************************
 * ComM_BusSM_ModeIndication()
 *********************************************************************************************************************/
/*! \brief       Indication of the actual bus mode by the corresponding Bus State Manager.
 *  \details     -
 *  \param[in]   Channel                 Valid channel identifier (network handle)
 *  \param[in]   ComMode                 Valid pointer where the BusSM mode is stored
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       CREQ-102897
*********************************************************************************************************************/
FUNC(void, COMM_CODE) ComM_BusSM_ModeIndication(NetworkHandleType Channel, P2VAR(ComM_ModeType, AUTOMATIC, COMM_APPL_VAR) ComMode);

#if ( COMM_EXISTS_LINSLAVE_NMTYPEOFCHANNEL == STD_ON )
/**********************************************************************************************************************
 *  ComM_BusSM_BusSleepMode()
 *********************************************************************************************************************/
/*! \brief       Indication of the corresponding Bus State Manager that the actual bus mode is Bus-Sleep.
 *  \details     Only applicable for LIN slave nodes.
 *  \param[in]   Channel               Valid channel identifier (network handle)
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous FALSE
 *  \trace       CREQ-102519
 *********************************************************************************************************************/
FUNC(void, COMM_CODE) ComM_BusSM_BusSleepMode( NetworkHandleType  Channel );
#endif

# define COMM_STOP_SEC_CODE
/* PRQA S 5087 1 */ /* MD_MSR_MemMap */
# include "MemMap.h"

#endif  /* COMM_BUSSM_H */

/**********************************************************************************************************************
  END OF FILE: ComM_BusSM.h
**********************************************************************************************************************/

