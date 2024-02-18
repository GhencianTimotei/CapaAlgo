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
/*!        \file  Com_Timer.h
 *        \brief  MICROSAR Communication header file
 *
 *      \details  This is the implementation of the MICROSAR Communication module.
 *                The basic software module is based on the AUTOSAR Communication specification.
 *
 *********************************************************************************************************************/
#if !defined (COM_TIMER_H)
# define COM_TIMER_H

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
# include "Com_Lcfg.h"

/**********************************************************************************************************************
  GLOBAL CONSTANT MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL FUNCTION MACROS
**********************************************************************************************************************/

# if (COM_RXTOUTINFO == STD_ON)
/**********************************************************************************************************************
  Com_LMgt_HasTimeoutOccurred
**********************************************************************************************************************/
/*! \brief        This function evaluates if a Timeout has occurred.
    \details      -
    \pre          -
    \param[in]    ComRxToutObjtId  ID of Rx Timeout object.
    \return       boolean
                  true:   A timeout has occurred.
                  false:  No timeout has occurred.
    \context      TASK
    \synchronous  TRUE
    \reentrant    TRUE
**********************************************************************************************************************/
#  define Com_LMgt_HasTimeoutOccurred(ComRxToutObjtId)  (boolean) ((COM_OCCURRED_RXPDUDMSTATE == Com_GetRxPduDmState(ComRxToutObjtId)) ? TRUE : FALSE)

/**********************************************************************************************************************
  Com_LMgt_RemoveOccurredFlag
**********************************************************************************************************************/
/*! \brief        This function removes the OCCURRED flag form the Rx Deadline Monitoring State.
    \details      -
    \pre          -
    \param[in]    ComRxToutObjtId  ID of Rx Timeout object.
    \context      TASK
    \synchronous  TRUE
    \reentrant    TRUE
**********************************************************************************************************************/
#  define Com_LMgt_RemoveOccurredFlag(ComRxToutObjtId)  Com_SetRxPduDmState((ComRxToutObjtId), (Com_GetRxPduDmState(ComRxToutObjtId) & COM_CLEAR_OCCURRED_FLAG_RXPDUDMSTATE))

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

# if (COM_TXTOUTCNT == STD_ON)
/**********************************************************************************************************************
  Com_TxDlMon_Init
**********************************************************************************************************************/
/*! \brief    This function initializes the Com_TxDlMon.
    \details  -
    \pre      -
    \context      TASK
    \synchronous  TRUE
    \reentrant    FALSE
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxDlMon_Init(void);
# endif

# if (COM_TXTOUTINFO == STD_ON)
/**********************************************************************************************************************
  Com_TxDlMon_MainFunctionTx
**********************************************************************************************************************/
/*! \brief    This function performs the Tx Deadline Monitoring.
    \details  -
    \pre      -
    \trace    SPEC-2736820
    \context      TASK
    \synchronous  TRUE
    \reentrant    FALSE
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxDlMon_MainFunctionTx(void);
# endif

# if (COM_TXTOUTINFOUSEDOFTXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_TxDlMon_TxConfirmation
**********************************************************************************************************************/
/*! \brief        This function stops the tx deadline monitoring after a succesful transmission.
    \details      -
    \pre          -
    \param[in]    TxPduId Handle of the I-PDU.
    \context      TASK|ISR2
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxDlMon_TxConfirmation(PduIdType TxPduId);
# endif

# if (COM_TXTOUTINFOUSEDOFTXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_TxDlMon_IPduGroupStart
**********************************************************************************************************************/
/*! \brief        This function initializes the tx timeout values of the passed tx I-PDU
    \details      -
    \pre          -
    \param[in]    TxPduId Handle of the I-PDU.
    \context      TASK
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxDlMon_IPduGroupStart(Com_TxPduInfoIterType TxPduId);
# endif

# if (COM_EXISTS_NORMAL_MODEOFTXTOUTINFO == STD_ON)
/**********************************************************************************************************************
  Com_TxDlMon_SwitchIpduTxMode
**********************************************************************************************************************/
/*! \brief        This function reset the tx timeout counter of the passed tx I-PDU
    \details      -
    \pre          -
    \param[in]    TxPduId Handle of the I-PDU.
    \trace        SPEC-2736879
    \context      TASK|ISR2
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxDlMon_SwitchIpduTxMode(PduIdType TxPduId);
# endif

# if (COM_GWTIMEOUTINFO == STD_ON)
/**********************************************************************************************************************
  Com_GwTout_HandleCounter
**********************************************************************************************************************/
/*! \brief    This function handles the GW timeout counter. On a timeout event the cyclic transmission is stopped.
    \details  -
    \pre      -
    \context  TASK
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_GwTout_HandleCounter(void);

/**********************************************************************************************************************
  Com_GwTout_InitCounter
**********************************************************************************************************************/
/*! \brief        This function initializes the GW timeout counter for a given Pdu. On a timeout event
                  the cyclic transmission is stopped.
 *  \details      -
    \pre          -
    \param[in]    ComPduId    ComIPdu handle id
    \context      TASK
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_GwTout_InitCounter(PduIdType ComPduId);
# endif

# if (COM_GWTIMEOUTINFO == STD_ON)
/**********************************************************************************************************************
  Com_GwTout_Event
**********************************************************************************************************************/
/*! \brief          This function handles the GW timeout counter. On a timeout event the cyclic transmission is stopped.
 *  \details        -
    \pre            -
    \param[in]      ComTxPduId
    \synchronous    TRUE
    \reentrant      TRUE, for different handles
    \context        TASK
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_GwTout_Event(PduIdType ComTxPduId);
# endif

# if (COM_RXTOUTINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxDlMon_MainFunctionRx
**********************************************************************************************************************/
/*! \brief        This function initiates the Rx Deadline Monitoring processing.
    \details      -
    \pre          -
    \trace        SPEC-2736949
    \context      TASK
    \synchronous  TRUE
    \reentrant    FALSE
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_RxDlMon_MainFunctionRx(void);
# endif

# if (COM_RXTOUTINFOINDENDIDXOFRXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxDlMon_InitRxIpdu
**********************************************************************************************************************/
/*! \brief        This function initializes the Rx deadline monitoring parameters of the passed Rx ComIPdu
    \details      -
    \pre          -
    \param[in]    ComPduId Handle of the I-PDU.
    \context      TASK
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_RxDlMon_InitRxIpdu(PduIdType ComPduId);
# endif

# if (COM_RXTOUTINFOUSEDOFRXSIGINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxDlMon_SigEvent
**********************************************************************************************************************/
/*! \brief        This function reloads the timeout counter value of the passed Rx ComSignal
    \details      -
    \pre          -
    \param[in]    idxRxSigInfo Handle Id of Rx ComSignal
    \trace        SPEC-2736869
    \context      TASK|ISR2
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_RxDlMon_SigEvent(Com_RxSigInfoIterType idxRxSigInfo);
# endif

# if (COM_RXTOUTINFOUSEDOFRXSIGGRPINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxDlMon_SigGrpEvent
**********************************************************************************************************************/
/*! \brief        This function reloads the timeout counter value of the passed Rx ComSignalGroup
    \details      -
    \pre          -
    \param[in]    idxRxSigGrpInfo Handle Id of Rx ComSignalGroup
    \trace        SPEC-2736869
    \context      TASK|ISR2
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_RxDlMon_SigGrpEvent(Com_RxSigGrpInfoIterType idxRxSigGrpInfo);
# endif

# define COM_STOP_SEC_CODE
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_MemMap */

#endif /* COM_TIMER_H */

/**********************************************************************************************************************
  END OF FILE: Com_Timer.h
**********************************************************************************************************************/
