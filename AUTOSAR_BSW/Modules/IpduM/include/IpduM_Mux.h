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
 *         File:  IpduM_Mux.h
 *      Project:  MICROSAR IpduM
 *       Module:  Implementation
 *    Generator:  CFG5
 *
 *  Description:  Microsar IPDU Multiplexer header file
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
#ifndef IPDUM_MUX_H
# define IPDUM_MUX_H

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
# include "IpduM_Cfg.h"
# include "IpduM_Lcfg.h"
# include "IpduM_PBcfg.h"
# include "ComStack_Types.h"

/**********************************************************************************************************************
  GLOBAL CONSTANT MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL FUNCTION MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/
#define IPDUM_START_SEC_CODE
#include "MemMap.h"    /* PRQA S 5087 */        /*  MD_MSR_MemMap */

#if (IPDUM_TXBUFFERSTARTIDXOFTXPATHWAY == STD_ON)
/*******************************************************************************************
*  IpduM_InitComponentMux()
*******************************************************************************************/
/*! \brief        Initializes mutiplex PDU related structures
 *  \details      Initializes all component variables related to multiplexing
 *  \pre          Interrupts are disabled
 *  \pre          Module is uninitialized
 *  \pre          IpduM_InitMemory has been called unless IpduM_ModuleInitialized is initialized by start-up code
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \trace        CREQ-102610
 *  \trace        SPEC-2914519, SPEC-2914520, SPEC-2914521, SPEC-2068173
*******************************************************************************************/
FUNC(void, IPDUM_CODE) IpduM_InitComponentMux(void);
#endif

#if (IPDUM_TXPART == STD_ON)
/*******************************************************************************************
*  IpduM_MuxTransmit()
*******************************************************************************************/
/*! \brief        Requests the transmission of a static or dynamic part
 *  \details      -
 *  \param[in]    txPartId
 *  \param[in]    PduInfoPtr    Pointer to payload buffer
 *  \return       E_OK          Transmit request was accepted by IpduM and destination layer
 *  \return       E_NOT_OK      Transmit request was not accepted
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE for different handle IDs
 *  \synchronous  TRUE
 *  \trace        CREQ-102653, CREQ-102659, CREQ-102661
*******************************************************************************************/
FUNC(Std_ReturnType, IPDUM_CODE) IpduM_MuxTransmit(IpduM_TxUpIndIdxOfTxUpInfoType txPartId, P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr);
#endif

#if(IPDUM_TRIGGER_TRANSMIT_API == STD_ON && IPDUM_EXISTS_MUX_PATHWAYTYPEOFCTXLOINFO == STD_ON)
/*******************************************************************************************
*  IpduM_MuxTriggerTransmit()
*******************************************************************************************/
/*! \brief          Requests the PDU data before transmission
 *  \details      -
 *  \param[in]      txPathwayHnd
 *  \param[in,out]  PduInfoPtr    pointer and length of the provided buffer and length of the copied data on return
 *  \return         E_OK          Data was copied correctly
 *  \return         E_NOT_OK      Data could not be copied correctly, PduInfoPtr does not contain valid data
 *  \pre            -
 *  \context        TASK|ISR
 *  \reentrant      TRUE for different handle IDs
 *  \synchronous    TRUE
 *  \trace          CREQ-102654, CREQ-102659, CREQ-102661
*******************************************************************************************/
FUNC(Std_ReturnType, IPDUM_CODE) IpduM_MuxTriggerTransmit(IpduM_TxPathwayIdxOfCTxLoInfoType txPathwayHnd, P2VAR(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr);
#endif

#if ((IPDUM_TXCONFIRMATIONTIMEOUTOFTXPATHWAY == STD_ON) || (IPDUM_TXCONFIRMATIONOFTXPART == STD_ON))
/*******************************************************************************************
*  IpduM_MuxTxConfirmation()
*******************************************************************************************/
/*! \brief        Indicates complete transmission of a PDU
 *  \details      -
 *  \param[in]    TxPduId
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE for different handle IDs
 *  \synchronous  TRUE
 *  \trace        CREQ-102655
*******************************************************************************************/
FUNC(void, IPDUM_CODE) IpduM_MuxTxConfirmation(PduIdType TxPduId);
#endif

#if (IPDUM_RXMUXPDU == STD_ON)
/*******************************************************************************************
*  IpduM_MuxRxIndication()
*******************************************************************************************/
/*! \brief        Indicates complete reception of a PDU
 *  \details      -
 *  \param[in]    rxMuxPduId
 *  \param[out]   PduInfoPtr    Pointer to buffer containing PDU
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE for different handle IDs
 *  \synchronous  TRUE
 *  \trace        CREQ-102656, CREQ-102660
*******************************************************************************************/
FUNC(void, IPDUM_CODE) IpduM_MuxRxIndication(IpduM_RxPathwayIndIdxOfRxInfoType rxMuxPduId, P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr);
#endif

#define IPDUM_STOP_SEC_CODE
#include "MemMap.h"    /* PRQA S 5087 */        /*  MD_MSR_MemMap */

#endif /* IPDUM_MUX_H */

/**********************************************************************************************************************
 *  END OF FILE: IpduM_Mux.h
 *********************************************************************************************************************/
