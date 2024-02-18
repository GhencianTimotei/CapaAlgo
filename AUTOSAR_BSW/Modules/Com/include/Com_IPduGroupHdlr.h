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
/*!        \file  Com_IPduGroupHdlr.h
 *        \brief  MICROSAR Communication source file
 *
 *      \details  This is the implementation of the MICROSAR Communication module.
 *                The basic software module is based on the AUTOSAR Communication specification.
 *
 *********************************************************************************************************************/
#if !defined (COM_IPDUGROUPHDLR_H)
# define COM_IPDUGROUPHDLR_H

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
# include "Com_Lcfg.h"

/**********************************************************************************************************************
  GLOBAL CONSTANT MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL CONSTANT MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL FUNCTION MACROS
**********************************************************************************************************************/
# if (COM_RXTOUTINFO == STD_ON)

/**********************************************************************************************************************
  Com_LMgt_DeactivateRxIpduDm
**********************************************************************************************************************/
/*! \brief        This function disables the Deadline Monitoring for the Rx I-Pdu.
                  To avoid data inconsistency ensure the Deadline Monitoring is
                  enabled for the Rx I-Pdu by calling Com_LMgt_RxIpduDmActive().
    \details      -
    \pre          -
    \param[in]    ComRxToutObjtId  ID of Rx Timeout object.
    \context      TASK
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
**********************************************************************************************************************/
#  define Com_LMgt_DeactivateRxIpduDm(ComRxToutObjtId)  Com_SetRxPduDmState((ComRxToutObjtId), COM_INACTIVE_RXPDUDMSTATE)

# endif

/**********************************************************************************************************************
  GLOBAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL DATA PROTOTYPES (Com)
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/

# define COM_START_SEC_CODE
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_MemMap */

# if (COM_ALWAYSACTIVERXCOMIPDUS == STD_ON)
/**********************************************************************************************************************
  Com_ActivateAlwaysOnRxComIPdus
**********************************************************************************************************************/
/*! \brief        This function activates Rx ComIPdu's without an assigned ComIPduGroup
    \details      -
    \pre          -
    \context      TASK
    \synchronous  TRUE
    \reentrant    FALSE
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_ActivateAlwaysOnRxComIPdus(void);
# endif

# if (COM_ALWAYSACTIVETXCOMIPDUS == STD_ON)
/**********************************************************************************************************************
  Com_ActivateAlwaysOnTxComIPdus
**********************************************************************************************************************/
/*! \brief        This function activates Tx ComIPdu's without an assigned ComIPduGroup
    \details      -
    \pre          -
    \context      TASK
    \synchronous  TRUE
    \reentrant    FALSE
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_ActivateAlwaysOnTxComIPdus(void);
# endif

# if (COM_RXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_DeactivateRxComIPdu
**********************************************************************************************************************/
/*! \brief        This function deactivates the given Rx ComIPdu
    \details      -
    \pre          -
    \param[in]    ComRxPduId  ComIPdu  handle id
    \context      TASK
    \synchronous  TRUE
    \reentrant    FALSE
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_DeactivateRxComIPdu(Com_RxPduInfoIterType ComRxPduId);
# endif

# if (COM_TXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_DeactivateTxComIPdu
**********************************************************************************************************************/
/*! \brief        This function deactivates the given Tx ComIPdu
    \details      -
    \param[in]    txPduId  ComIPdu  handle id
    \pre          Com_TxIPduGroup_EnterExclusiveArea has been called before
    \context      TASK
    \synchronous  TRUE
    \reentrant    FALSE
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_DeactivateTxComIPdu(Com_TxPduInfoIterType txPduId);
# endif

# if (COM_RXPDUINFOINDUSEDOFIPDUGROUPINFO == STD_ON)
/**********************************************************************************************************************
  Com_IpduGroupStartRx
**********************************************************************************************************************/
/*! \brief        Starts a preconfigured I-PDU Rx-subgroup.
    \details      -
    \pre          -
    \param[in]    subIpduGroupId ID of I-PDU subgroup to be started
    \param[in]    Initialize  Flag to request initialization of the data in the I-PDUs of this I-PDU group
    \context      TASK
    \synchronous  TRUE
    \reentrant    FALSE
    \warning      A call to Com_IpduGroupStartRx shall not be interrupted by another call to Com_IpduGroupStart, Com_EnableReceptionDM,
                  Com_DisableReceptionDM or a call to Com_IpduGroupStop.
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_IpduGroupStartRx(Com_IpduGroupIdType subIpduGroupId, boolean Initialize);
# endif

# if (COM_TXPDUINFOINDUSEDOFIPDUGROUPINFO == STD_ON)
/**********************************************************************************************************************
  Com_IpduGroupStartTx
**********************************************************************************************************************/
/*! \brief        Starts a preconfigured I-PDU Tx-subgroup.
    \details      -
    \pre          -
    \param[in]    subIpduGroupId ID of I-PDU subgroup to be started
    \param[in]    Initialize  Flag to request initialization of the data in the I-PDUs of this I-PDU group
    \context      TASK
    \synchronous  TRUE
    \reentrant    FALSE
    \warning      A call to Com_IpduGroupStartTx shall not be interrupted by another call to Com_IpduGroupStart, Com_EnableReceptionDM,
                  Com_DisableReceptionDM or a call to Com_IpduGroupStop.
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_IpduGroupStartTx(Com_IpduGroupIdType subIpduGroupId, boolean Initialize);
# endif

# if (COM_IPDUGROUPINFO == STD_ON)
/**********************************************************************************************************************
  Com_IpduGroupStopSubGroup
**********************************************************************************************************************/
/*! \brief        Stops a preconfigured I-PDU subgroup.
                  For example, cyclic I-PDUs will be stopped after the call of Com_IpduGroupStop().
    \details      -
    \pre          -
    \param[in]    subIpduGroupId ID of I-PDU subgroup to be stopped
    \context      TASK
    \synchronous  TRUE
    \reentrant    FALSE
    \warning      A call to Com_IpduGroupStopSubGroup shall not be interrupted by another call to Com_IpduGroupStop, Com_EnableReceptionDM,
                  Com_DisableReceptionDM or a call to Com_IpduGroupStart.
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_IpduGroupStopSubGroup(Com_IpduGroupIdType subIpduGroupId);
# endif

# if ((COM_PDUGRPVECTOR == STD_ON) && (COM_TXPDUINFO == STD_ON) && (COM_ACTIVATABLETXCOMIPDUS == STD_ON))
/**********************************************************************************************************************
 Com_IpduGroupControl_SetRequestedActiveState
**********************************************************************************************************************/
/*! \brief        This function sets the requested active state if needed.
    \details      -
    \pre          -
    \param[in]    ComTxPduId              ID of the I-PDU
    \param[in]    initialize              flag to request initialization of the I-PDUs which are newly started
    \param[in]    bRequestedActiveState   Active state of the I-PDU
    \trace        SPEC-2736840
    \context      TASK
    \synchronous  TRUE
    \reentrant    FALSE
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_IpduGroupControl_SetRequestedActiveState(Com_TxPduInfoIterType ComTxPduId, boolean initialize, boolean bRequestedActiveState);

/**********************************************************************************************************************
  Com_IpduGroupControl_EvaluateActiveState
**********************************************************************************************************************/
/*! \brief        This function evaluates requested active state of the I-PDU
    \details      -
    \pre          -
    \param[in]    ComTxPduId          ID of the I-PDU
    \param[in]    ipduGroupVector     I-PDU group vector containing the activation state (stopped = 0/ started = 1)
                                      for all I-PDU groups.
    \return       bRequestedActiveState   Active state of the I-PDU. An I-PDU is active if and only if at least one I-PDU group is active it belongs to.
    \context      TASK
    \synchronous  TRUE
    \reentrant    FALSE
**********************************************************************************************************************/
FUNC(boolean, COM_CODE) Com_IpduGroupControl_EvaluateActiveState(Com_IpduGroupVector ipduGroupVector, Com_TxPduInfoIterType ComTxPduId);
# endif

# if (COM_ACTIVATABLERXCOMIPDUS == STD_ON)
/**********************************************************************************************************************
  Com_IpduGroupControl_UpdateRxComIPduState
**********************************************************************************************************************/
/*! \brief        This function evaluates requested active state of the I-PDU
    \details      -
    \pre          -
    \param[in]    ipduGroupVector I-PDU group vector containing the activation state (stopped = 0/ started = 1)
                              for all I-PDU groups.
    \param[in]    initialize      flag to request initialization of the I-PDUs which are newly started
    \trace        SPEC-2736840, SPEC-2736847
    \context      TASK
    \synchronous  TRUE
    \reentrant    FALSE
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_IpduGroupControl_UpdateRxComIPduState(Com_IpduGroupVector ipduGroupVector, boolean initialize);
# endif

# if ((COM_RXTOUTINFOINDENDIDXOFRXPDUINFO == STD_ON) && (COM_PDUGRPVECTOR == STD_ON))
/**********************************************************************************************************************
  Com_ReceptionDMControl_SetDmState
**********************************************************************************************************************/
/*! \brief        This service enables or disables I-PDU group Deadline Monitoring. The group Deadline Monitoring is started
 *                on activation. All I-PDUs, that have not changed their deadline monitoring state, are not processed.
    \details      -
    \pre          -
    \param[in]    ComRxPduId -  ID of the RX-PDU
    \param[in]    bRequestedActiveState - true if at least one of the IPDU-Groups of ComRxPduId is active
    \trace        SPEC-2736873, SPEC-2736875, SPEC-2736872
    \context      TASK
    \synchronous  TRUE
    \reentrant    FALSE
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_ReceptionDMControl_SetDmState(Com_RxPduInfoIterType ComRxPduId, Com_RxPduDmStateType bRequestedActiveState);
# endif

# if ((COM_RXTOUTINFO == STD_ON) && (COM_PDUGRPVECTOR == STD_ON) && (COM_ACTIVATABLERXCOMIPDUS == STD_ON))
/**********************************************************************************************************************
  Com_ReceptionDMControl_EvaluateActiveState
**********************************************************************************************************************/
/*! \brief        This function evaluates requested active state of the I-PDU
    \details      -
    \pre          -
    \param[in]    ComRxPduId          ID of the I-PDU
    \param[in]    ipduGroupVector     ipduGroupVector I-PDU group vector containing the requested deadline monitoring state
                                  (disabled = 0/ enabled = 1) for all I-PDU groups.
    \return       bRequestedActiveState   Active state of the I-PDU. An I-PDU is active if and only if at least one I-PDU group is active it belongs to.
    \context      TASK
    \synchronous  TRUE
    \reentrant    FALSE
**********************************************************************************************************************/
FUNC(Com_RxPduDmStateType, COM_CODE) Com_ReceptionDMControl_EvaluateActiveState(Com_IpduGroupVector ipduGroupVector, Com_RxPduInfoIterType ComRxPduId);
# endif

# if ((COM_RXPDUINFOINDUSEDOFIPDUGROUPINFO == STD_ON) && (COM_RXTOUTINFOINDENDIDXOFRXPDUINFO == STD_ON))
/**********************************************************************************************************************
  Com_EnableReceptionDMsubGroup
**********************************************************************************************************************/
/*! \brief        Enables the reception deadline monitoring for the I-PDUs within the given I-PDU subgroup.
    \details      -
    \pre          -
    \param[in]    subIpduGroupId ID of I-PDU subgroup where reception DM shall be enabled.
    \context      TASK
    \synchronous  TRUE
    \reentrant    FALSE
    \warning      A call to Com_EnableReceptionDMsubGroup shall not be interrupted by another call to Com_EnableReceptionDM,
                  Com_IpduGroupStop, Com_DisableReceptionDM or a call to Com_IpduGroupStart.
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_EnableReceptionDMsubGroup(Com_IpduGroupIdType subIpduGroupId);

/**********************************************************************************************************************
  Com_DisableReceptionDMsubGroup
**********************************************************************************************************************/
/*! \brief        Disables the reception deadline monitoring for the I-PDUs within the given I-PDU subgroup.
    \details      -
    \pre          -
    \param[in]    subIpduGroupId ID of I-PDU subgroup where reception DM shall be disabled.
    \context      TASK
    \synchronous  TRUE
    \reentrant    FALSE
    \warning      A call to Com_DisableReceptionDMsubGroup shall not be interrupted by another call to Com_DisableReceptionDM, Com_IpduGroupStop,
                  Com_EnableReceptionDM or a call to Com_IpduGroupStart.
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_DisableReceptionDMsubGroup(Com_IpduGroupIdType subIpduGroupId);
# endif

# if (COM_RXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxIPduGroup_EnterExclusiveArea
**********************************************************************************************************************/
/*! \brief        This function enters the rx IPduGroups exclusive area.
    \details      -
    \pre          -
    \trace        DSGN-COM_ISRTHRESHOLD_CONCEPT
    \context      TASK
    \synchronous  TRUE
    \reentrant    FALSE
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_RxIPduGroup_EnterExclusiveArea(void);

/**********************************************************************************************************************
  Com_RxIPduGroup_ExitExclusiveArea
**********************************************************************************************************************/
/*! \brief        This function exits the rx IPduGroups exclusive area.
    \details      -
    \pre          -
    \trace        DSGN-COM_ISRTHRESHOLD_CONCEPT
    \context      TASK
    \synchronous  TRUE
    \reentrant    FALSE
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_RxIPduGroup_ExitExclusiveArea(void);

/**********************************************************************************************************************
  Com_RxIPduGroup_ThresholdCheck
**********************************************************************************************************************/
/*! \brief        This function checks if the ISR Lock must be opened
    \details      -
    \pre          -
    \trace        DSGN-COM_ISRTHRESHOLD_CONCEPT
    \context      TASK
    \synchronous  TRUE
    \reentrant    FALSE
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_RxIPduGroup_ThresholdCheck(void);
# endif

# if (COM_TXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_TxIPduGroup_EnterExclusiveArea
**********************************************************************************************************************/
/*! \brief        This function enters the tx IPduGroups exclusive area.
    \details      -
    \pre          -
    \trace        DSGN-COM_ISRTHRESHOLD_CONCEPT
    \context      TASK
    \synchronous  TRUE
    \reentrant    FALSE
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxIPduGroup_EnterExclusiveArea(void);

/**********************************************************************************************************************
  Com_TxIPduGroup_ExitExclusiveArea
**********************************************************************************************************************/
/*! \brief        This function exits the tx IPduGroups exclusive area.
    \details      -
    \pre          -
    \trace        DSGN-COM_ISRTHRESHOLD_CONCEPT
    \context      TASK
    \synchronous  TRUE
    \reentrant    FALSE
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxIPduGroup_ExitExclusiveArea(void);

/**********************************************************************************************************************
  Com_TxIPduGroup_ThresholdCheck
**********************************************************************************************************************/
/*! \brief        This function checks if the ISR Lock must be opened
    \details      -
    \pre          -
    \trace        DSGN-COM_ISRTHRESHOLD_CONCEPT
    \context      TASK
    \synchronous  TRUE
    \reentrant    FALSE
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxIPduGroup_ThresholdCheck(void);
# endif

# define COM_STOP_SEC_CODE
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_MemMap */

#endif /* COM_IPDUGROUPHDLR_H */
/**********************************************************************************************************************
  END OF FILE: Com_IPduGroupHdlr.h
**********************************************************************************************************************/
