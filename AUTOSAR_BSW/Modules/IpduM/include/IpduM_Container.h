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
 *         File:  IpduM_Container.h
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
#ifndef IPDUM_CONTAINER_H
# define IPDUM_CONTAINER_H

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
# define IPDUM_START_SEC_CODE
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_MemMap */

#if ((IPDUM_CONTAINERRXBUFFER == STD_ON) || (IPDUM_CONTAINERTXBUFFER == STD_ON))
/*******************************************************************************************
*  IpduM_Container_Init()
*******************************************************************************************/
/*! \brief        Initializes container PDU related structures
 *  \details      Initializes all component variables related to container PDUs
 *  \pre          Interrupts are disabled
 *  \pre          Module is uninitialized
 *  \pre          IpduM_InitMemory has been called unless IpduM_ModuleInitialized is initialized by start-up code
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \trace        CREQ-102610
 *  \trace        SPEC-2914519, SPEC-2914520, SPEC-2914521, SPEC-2068173
*******************************************************************************************/
FUNC(void, IPDUM_CODE) IpduM_Container_Init(void);
#endif

#if (IPDUM_TXCONTAINEDPDU == STD_ON)
/*******************************************************************************************
*  IpduM_ContainerTransmit()
*******************************************************************************************/
/*! \brief        Requests the transmission of a contained PDU
 *  \details      -
 *  \param[in]    txContainedId
 *  \param[in]    PduInfoPtr    Pointer to payload buffer
 *  \return       E_OK          Transmit request was accepted by IpduM
 *  \return       E_NOT_OK      Transmit request was not accepted
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE for different handle IDs
 *  \synchronous  TRUE
 *  \trace        CREQ-102653, CREQ-102672, CREQ-102673
 *  \trace        SPEC-2068537, SPEC-2068538, SPEC-2068539, SPEC-2068543, SPEC-2068545, SPEC-2068549, SPEC-2068551, SPEC-2068552
*******************************************************************************************/
FUNC(Std_ReturnType, IPDUM_CODE) IpduM_ContainerTransmit(IpduM_TxUpIndIdxOfTxUpInfoType txContainedId, P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr);
#endif

#if(IPDUM_TRIGGER_TRANSMIT_API == STD_ON && IPDUM_EXISTS_CONTAINER_PATHWAYTYPEOFCTXLOINFO == STD_ON)
/*******************************************************************************************
*  IpduM_ContainerTriggerTransmit()
*******************************************************************************************/
/*! \brief          Requests the PDU data before transmission
 *  \details        -
 *  \param[in]      txContainerId
 *  \param[in,out]  PduInfoPtr    Pointer to lower layer buffer
 *  \return         E_OK          Data was copied correctly
 *  \return         E_NOT_OK      Data could not be copied correctly, PduInfoPtr does not contain valid data
 *  \pre            -
 *  \context        TASK|ISR
 *  \reentrant      TRUE for different handle IDs
 *  \synchronous    TRUE
 *  \trace          CREQ-102654
*******************************************************************************************/
FUNC(Std_ReturnType, IPDUM_CODE) IpduM_ContainerTriggerTransmit(IpduM_TxContainerPduIdxOfCTxLoInfoType txContainerId, P2VAR(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr);
#endif

#if ((IPDUM_TX_CONFIRMATION_API == STD_ON && IPDUM_EXISTS_CONTAINER_PATHWAYTYPEOFCTXLOINFO == STD_ON))
/*******************************************************************************************
*  IpduM_ContainerTxConfirmation()
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
FUNC(void, IPDUM_CODE) IpduM_ContainerTxConfirmation(PduIdType TxPduId);
#endif

#if (IPDUM_RXCONTAINERPDU == STD_ON)
/*******************************************************************************************
*  IpduM_ContainerRxIndication()
*******************************************************************************************/
/*! \brief        Indicates complete reception of a PDU
 *  \details      -
 *  \param[in]    rxContainerId
 *  \param[out]   PduInfoPtr         Pointer to buffer containing PDU
 *  \return       IPDUM_E_NO_ERROR   Data was copied correctly
 *  \return       IPDUM_E_QUEUEOVFL  Data was copied correctly,
 *                                   but the oldest item in the queue has been removed.
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE for different handle IDs
 *  \synchronous  TRUE
 *  \trace        CREQ-102656, CREQ-102674
 *  \trace        SPEC-2068566, SPEC-2068569, SPEC-2068570, SPEC-2068572, SPEC-2068576
*******************************************************************************************/
FUNC(uint8, IPDUM_CODE) IpduM_ContainerRxIndication(IpduM_RxPathwayIndIdxOfRxInfoType rxContainerId, P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr);
#endif

#if (IPDUM_TXCONTAINEDPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerTx_MainFunction()
*******************************************************************************************/
/*! \brief        Performs actions not directly initiated by calls from the PduR.
 *  \details      -
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE
 *  \synchronous  TRUE
*******************************************************************************************/
FUNC(void, IPDUM_CODE) IpduM_ContainerTx_MainFunction(void);
#endif

#if (IPDUM_RXCONTAINERPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_ContainerRx_MainFunction()
*******************************************************************************************/
/*! \brief        Performs actions not directly initiated by calls from the PduR.
 *  \details      -
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE
 *  \synchronous  TRUE
*******************************************************************************************/
FUNC(void, IPDUM_CODE) IpduM_ContainerRx_MainFunction(void);
#endif

# define IPDUM_STOP_SEC_CODE
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_MemMap */

#endif /* IPDUM_CONTAINER_H */

/**********************************************************************************************************************
 *  END OF FILE: IpduM_Container.h
 *********************************************************************************************************************/
