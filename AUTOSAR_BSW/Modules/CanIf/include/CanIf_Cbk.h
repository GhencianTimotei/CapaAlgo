/* \trace SPEC-1878 */

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
/**        \file  CanIf_Cbk.h
 *        \brief  CAN Interface callback functions header file.
 *
 *      \details  This file contains the declaration of the callback function prototypes of the AUTOSAR 
 *                CAN Interface module.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  05.00.00  2012-07-02  visrna  ESCAN00060132 Support ASR 4.0 Rev 3
 *  05.01.00  2015-03-26  visseu  ESCAN00080296 FEAT-427: SafeBSW Step I
 *  05.02.00  2015-11-30  visrna  ESCAN00086059 FEAT-1429: Gateway Optimization
 *  05.02.01  2016-10-10  visrna  ESCAN00092243 Rework of  Doxygen comments
 *  05.03.00  2017-08-04  visseu  ESCAN00096180 FEAT-2946 - Supporting 3rd party communication MCAL CAN driver according to AR 4.2
 *  05.04.00  2018-10-31  visgaz  STORYC-6847   MISRA-C:2012: If_AsrIfCan
 *                                STORYC-7095   Adapt to new template
 *  05.05.00  2018-11-29  visgaz  STORYC-7176   Remove Parameter CanIfMultipleBasicCANTxObjects
 *  05.06.00  2020-01-23  visgaz  CAN-578       [CAN-IF] Synchronize API description between CanIf.h/CanIf_Cbk.h and TechRef
 *  05.07.00  2020-08-04  visgaz  CAN-1570      [CAN-IF] IdsM: Support reporting of security events by CAN stack modules
 *  05.08.00  2020-11-23  visgaz  CAN-1989      [CAN-IF] Support reporting of security events according to AR20-11
 *  06.00.00  2021-01-04  visgaz  ESCAN00100613 Compiler error: Declaration of CanIf_ControllerModeIndication() is missing
 *                                CAN-1768      [CAN-IF] Usage of <Ma>_MemMap.h in CanIf
 *********************************************************************************************************************/

#if !defined (CANIF_CBK_H)
# define CANIF_CBK_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
 
# include "CanIf_Cfg.h"
/* CanIf_Types.h  is included by CanIf_Cfg.h */

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

# define CANIF_CBK_MAJOR_VERSION   0x06u
# define CANIF_CBK_MINOR_VERSION   0x00u
# define CANIF_CBK_PATCH_VERSION   0x00u

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
 
# define CANIF_START_SEC_CODE
# include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* \trace SPEC-3696 */

/************************************************************************************************************
 *  CanIf_ControllerModeIndication()
 ***********************************************************************************************************/
/*! \brief         Called by the CAN Driver to notify CAN Interface about a successful controller mode
 *                 transition at the specified CAN controller.
 *  \details       -
 *  \param[in]     ControllerId: Abstracted CanIf ControllerId which is assigned to a CAN controller,
 *                               which controller mode has been transitioned.
 *  \param[in]     ControllerMode: Controller mode to which the CAN controller transitioned.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     TRUE only for different ControllerId
 *  \synchronous   TRUE
 *  \config        -
***********************************************************************************************************/
FUNC(void, CANIF_CODE) CanIf_ControllerModeIndication(uint8 ControllerId, CanIf_ControllerModeType ControllerMode);

/***********************************************************************************************************************
 *  CanIf_TxConfirmation()
 **********************************************************************************************************************/
/*! \brief       Called by the CAN Driver to notify the CAN Interface about the successful transmission of
 *               the specified Tx-PDU.
 *  \details     -
 *  \param[in]   CanTxPduId: Handle of the Tx-PDU which is successfully transmitted.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      -
 **********************************************************************************************************************/
FUNC(void, CANIF_CODE) CanIf_TxConfirmation(PduIdType CanTxPduId);

/***********************************************************************************************************************
 *  CanIf_RxIndicationAsr403()
 **********************************************************************************************************************/
/*! \brief       Called by the CAN Driver to notify the CAN Interface about the reception of the specified Rx-PDU.
 *  \details     This function searches whether the received PDU matches one of the configured ones. If yes, then the
 *               configured upper layer is notified.
 *               The signature of the CanIf_RxIndication() API is according to AUTOSAR Standard 4.0.3. A suitable
 *               wrapper is generated to CanIf_Cfg.h, if you are using a CAN-Driver which is implemented to 
 *               AUTOSAR Standard 4.2.2.
 *  \param[in]   Hrh: Hardware handle where the Rx-PDU was received in.
 *  \param[in]   CanId: CAN identifier of the received Rx-PDU.
 *  \param[in]   CanDlc: Data length of the received Rx-PDU.
 *  \param[in]   CanSduPtr: Pointer to the data of the received Rx-PDU.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      -
 **********************************************************************************************************************/
FUNC(void, CANIF_CODE) CanIf_RxIndicationAsr403(CanIf_HwHandleType Hrh, Can_IdType CanId, uint8 CanDlc, P2CONST(uint8, AUTOMATIC, CANIF_CBK_DRV_VAR)CanSduPtr);

/* void CanIf_CancelTxConfirmation(const Can_PduType *PduInfoPtr); */
# if (CANIF_TRANSMIT_BUFFER_PRIO_BY_CANID == STD_ON)
#  if (CANIF_TRANSMIT_BUFFER_FIFO == STD_OFF)
#   if (CANIF_TRANSMIT_CANCELLATION == STD_ON)
/***********************************************************************************************************************
 *  CanIf_CancelTxConfirmation()
 **********************************************************************************************************************/
/*! \brief       Called by the CAN Driver to notify the CAN Interface about the transmission cancellation of the
 *               specifed Tx-PDU.
 *  \details     The specified Tx-PDU is re-queued in a transmit-buffer.
 *  \param[in]   CanTxPduId: Handle of the Tx-PDU which was cancelled.
 *  \param[in]   PduInfoPtr: Pointer to parameters of the canceled Tx-PDU.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      CANIF_TRANSMIT_BUFFER == STD_ON and CANIF_TRANSMIT_CANCELLATION == STD_ON
 **********************************************************************************************************************/
FUNC(void, CANIF_CODE) CanIf_CancelTxConfirmation(PduIdType CanTxPduId, P2CONST(Can_PduType, AUTOMATIC, CANIF_CBK_DRV_VAR) PduInfoPtr);
#   endif
#  endif
# endif

/***********************************************************************************************************************
 *  CanIf_ControllerBusOff()
 **********************************************************************************************************************/
/*! \brief       Called by the CAN Driver to notify the CAN Interface about an occurred BusOff-event at the 
 *               specified CAN controller.
 *  \details     -
 *  \param[in]   ControllerId: Abstracted CanIf ControllerId which is assigned to a CAN controller,
 *                             at which the BusOff-event occurred.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      -
 **********************************************************************************************************************/
FUNC(void, CANIF_CODE) CanIf_ControllerBusOff(uint8 ControllerId);

# if (CANIF_ENABLE_SECURITY_EVENT_REPORTING == STD_ON)
/***********************************************************************************************************************
 *  CanIf_ControllerErrorStatePassive()
 **********************************************************************************************************************/
/*! \brief       Called by the CAN Driver to notify the CAN Interface about an occurred transistion to error state passive
 *               at the specified CAN controller
 *  \details     -
 *  \param[in]   ControllerId: Abstracted CanIf ControllerId which is assigned to a CAN controller,
 *                             at which the transistion to error state passive occurred.
 *  \param[in]   RxErrorCounter: Value of the rx error counter from the specified CAN controller.
 *  \param[in]   TxErrorCounter: Value of the tx error counter from the specified CAN controller.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      CANIF_ENABLE_SECURITY_EVENT_REPORTING  == STD_ON
 **********************************************************************************************************************/
FUNC(void, CANIF_CODE) CanIf_ControllerErrorStatePassive(uint8 ControllerId, uint16 RxErrorCounter, uint16 TxErrorCounter);

/***********************************************************************************************************************
 *  CanIf_ErrorNotification()
 **********************************************************************************************************************/
/*! \brief       Called by the CAN Driver to notify the CAN Interface about an occurred bus error at the specified
 *               CAN controller
 *  \details     -
 *  \param[in]   ControllerId: Abstracted CanIf ControllerId which is assigned to a CAN controller,
 *                             at which the bus error occurred.
 *  \param[in]   CanError: Occured bus error.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      CANIF_ENABLE_SECURITY_EVENT_REPORTING  == STD_ON
 **********************************************************************************************************************/
FUNC(void, CANIF_CODE) CanIf_ErrorNotification(uint8 ControllerId, Can_ErrorType CanError);
# endif

/* NON AUTOSAR callback functions */

# if (CANIF_CANCEL_SUPPORT_API == STD_ON)
/***********************************************************************************************************************
 *  CanIf_CancelTxNotification()
 **********************************************************************************************************************/
/*! \brief       Called by the CAN Driver to notify the CAN Interface about the transmission cancelation of the
 *               specified Tx-PDU.
 *  \details     The specified Tx-PDU is not confirmed to the configured upper layer. The next Tx-PDU from the
 *               transmit-buffer is transmitted.
 *               Used for trigger-purpose to fill the free HW-object, after calling of CanIf_CancelTransmit().
 *  \param[in]   PduId: Handle of the Tx-PDU which was cancelled.
 *  \param[in]   IsCancelled: Parameter currently not evaluated.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      CANIF_CANCEL_SUPPORT_API == STD_ON
 **********************************************************************************************************************/
FUNC(void, CANIF_CODE) CanIf_CancelTxNotification(PduIdType PduId, CanIf_CancelResultType IsCancelled);
# endif

# define CANIF_STOP_SEC_CODE
# include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* CANIF_CBK_H */

/**********************************************************************************************************************
 *  END OF FILE: CanIf_Cbk.h
 *********************************************************************************************************************/
