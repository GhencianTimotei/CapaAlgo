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
/**        \file  BswM_Dcm.h
 *        \brief  MICROSAR Basic Software Mode Manager
 *
 *      \details  Callback header for Dcm.
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
#if !defined BSWM_DCM_H
# define BSWM_DCM_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
# include "Dcm.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT VERSIONS
 *********************************************************************************************************************/

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
# define BSWM_START_SEC_CODE
/* PRQA S 5087 1 */ /* MD_MSR_MemMap */
# include "BswM_vMemMap.h" 

/**********************************************************************************************************************
 *  BswM_Dcm_CommunicationMode_CurrentState()
 *********************************************************************************************************************/
/*! \brief      Function called by DCM to inform the BswM about the current state of the communication mode.
 * \details     Passed RequestedMode is stored and depending rules are arbitrated.
 * \param[in]   Network         The communication channel that the diagnostic mode corresponds to.
 * \param[in]   RequestedMode   The requested diagnostic communication mode.
 * \pre         -
 * \context     TASK|ISR1|ISR2
 * \reentrant   TRUE for different networks
 * \synchronous TRUE
 * \config      BSWM_ENABLE_DCM
 * \trace       SPEC-16646, SPEC-7844, SPEC-7923, SPEC-7946
 */
extern FUNC(void, BSWM_CODE) BswM_Dcm_CommunicationMode_CurrentState(NetworkHandleType Network, Dcm_CommunicationModeType RequestedMode);

/**********************************************************************************************************************
 *  BswM_Dcm_ApplicationUpdated()
 *********************************************************************************************************************/
/*! \brief      Function called by DCM to inform the BswM that the application has being updated.
 * \details     Application update is stored and depending rules are arbitrated.
 * \pre         -
 * \context     TASK|ISR1|ISR2
 * \reentrant   TRUE
 * \synchronous TRUE
 * \config      BSWM_ENABLE_DCM
 */
extern FUNC(void, BSWM_CODE) BswM_Dcm_ApplicationUpdated(void);

# define BSWM_STOP_SEC_CODE
/* PRQA S 5087 1 */ /* MD_MSR_MemMap */
# include "BswM_vMemMap.h" 

#endif /* BSWM_DCM_H */

/**********************************************************************************************************************
 *  END OF FILE: BswM_Dcm.h
 *********************************************************************************************************************/
