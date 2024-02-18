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
/*!        \file  Com_TxModeHdlr.h
 *        \brief  MICROSAR Communication source file
 *
 *      \details  This is the implementation of the MICROSAR Communication module.
 *                The basic software module is based on the AUTOSAR Communication specification.
 *
 *********************************************************************************************************************/

#if !defined (COM_TXMODEHDLR_H)
# define COM_TXMODEHDLR_H

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

/**********************************************************************************************************************
Com_TxModeHdlr_IsDirectTxMode
**********************************************************************************************************************/
/*! \brief        This function checks if the current tx mode of the passed Tx ComIPdu is DIRECT.
    \details      -
    \pre          -
    \param[in]    TxPduId               Id of Tx ComIPdu.
    \context      TASK|ISR2
    \return       boolean
                    TRUE if current tx mode is DIRECT
                    FALSE otherwise
    \synchronous  TRUE
    \reentrant    TRUE
**********************************************************************************************************************/
# if ((COM_DIRECTOFTXMODETRUE == STD_ON) && (COM_DIRECTOFTXMODEFALSE == STD_ON))
#  define Com_TxModeHdlr_IsDirectTxMode(TxPduId)           ((Com_IsCurrentTxMode(TxPduId)) ? (Com_IsDirectOfTxModeTrue(Com_GetTxModeTrueIdxOfTxModeInfo(TxPduId))) : (Com_IsDirectOfTxModeFalse(Com_GetTxModeFalseIdxOfTxModeInfo(TxPduId))))
# endif
# if ((COM_DIRECTOFTXMODETRUE == STD_ON) && (COM_DIRECTOFTXMODEFALSE == STD_OFF))
#  define Com_TxModeHdlr_IsDirectTxMode(TxPduId)           ((Com_IsCurrentTxMode(TxPduId)) ? (Com_IsDirectOfTxModeTrue(Com_GetTxModeTrueIdxOfTxModeInfo(TxPduId))) : FALSE)
# endif
# if ((COM_DIRECTOFTXMODETRUE == STD_OFF) && (COM_DIRECTOFTXMODEFALSE == STD_ON))
#  define Com_TxModeHdlr_IsDirectTxMode(TxPduId)           ((Com_IsCurrentTxMode(TxPduId)) ? FALSE : (Com_IsDirectOfTxModeFalse(Com_GetTxModeFalseIdxOfTxModeInfo(TxPduId))))
# endif

/**********************************************************************************************************************
  Com_TxModeHdlr_IsPeriodicTxMode
**********************************************************************************************************************/
/*! \brief    This function checks if the current tx mode of the passed Tx ComIPdu is periodic
    \details  -
    \pre      -
    \return   boolean
                TRUE if current tx mode is periodic
                FALSE otherwise
    \context      TASK
    \synchronous  TRUE
    \reentrant    TRUE
**********************************************************************************************************************/
# if ((COM_PERIODICOFTXMODETRUE == STD_ON) && (COM_PERIODICOFTXMODEFALSE == STD_ON))
#  define Com_TxModeHdlr_IsPeriodicTxMode(TxPduId)           ((Com_IsCurrentTxMode(TxPduId)) ? (Com_IsPeriodicOfTxModeTrue(Com_GetTxModeTrueIdxOfTxModeInfo(TxPduId))) : (Com_IsPeriodicOfTxModeFalse(Com_GetTxModeFalseIdxOfTxModeInfo(TxPduId))))
# elif (COM_PERIODICOFTXMODETRUE == STD_ON)
#  define Com_TxModeHdlr_IsPeriodicTxMode(TxPduId)           ((Com_IsCurrentTxMode(TxPduId)) ? (Com_IsPeriodicOfTxModeTrue(Com_GetTxModeTrueIdxOfTxModeInfo(TxPduId))) : FALSE)
# elif (COM_PERIODICOFTXMODEFALSE == STD_ON)
#  define Com_TxModeHdlr_IsPeriodicTxMode(TxPduId)           ((Com_IsCurrentTxMode(TxPduId)) ? FALSE : (Com_IsPeriodicOfTxModeFalse(Com_GetTxModeFalseIdxOfTxModeInfo(TxPduId))))
# endif

/**********************************************************************************************************************
  Com_TxModeHdlr_GetCurrentTimePeriod
**********************************************************************************************************************/
/*! \brief    This function returns the configured time period of the current tx mode.
    \details  -
    \pre      -
    \return   uint8
                configured time period of the current tx mode.
    \context      TASK
    \synchronous  TRUE
    \reentrant    TRUE
**********************************************************************************************************************/
# if ((COM_PERIODICOFTXMODETRUE == STD_ON) && (COM_PERIODICOFTXMODEFALSE == STD_ON))
#  define Com_TxModeHdlr_GetCurrentTimePeriod(TxPduId)           ((Com_IsCurrentTxMode(TxPduId)) ? (Com_GetTimePeriodOfTxModeTrue(Com_GetTxModeTrueIdxOfTxModeInfo(TxPduId))) : (Com_GetTimePeriodOfTxModeFalse(Com_GetTxModeFalseIdxOfTxModeInfo(TxPduId))))
# elif (COM_PERIODICOFTXMODETRUE == STD_ON)
#  define Com_TxModeHdlr_GetCurrentTimePeriod(TxPduId)           ((Com_IsCurrentTxMode(TxPduId)) ? (Com_GetTimePeriodOfTxModeTrue(Com_GetTxModeTrueIdxOfTxModeInfo(TxPduId))) : 0u)
# elif (COM_PERIODICOFTXMODEFALSE == STD_ON)
#  define Com_TxModeHdlr_GetCurrentTimePeriod(TxPduId)           ((Com_IsCurrentTxMode(TxPduId)) ? 0u : (Com_GetTimePeriodOfTxModeFalse(Com_GetTxModeFalseIdxOfTxModeInfo(TxPduId))))
# endif

/**********************************************************************************************************************
  Com_TxModeHdlr_GetCurrentTimeOffset
**********************************************************************************************************************/
/*! \brief    This function returns the configured time offset (time between the start of the I-PDU by
 *            Com_IpduGroupControl and the first transmission request) of the current tx mode.
    \details  -
    \pre      -
    \return   uint8
                configured time offset of the current tx mode.
    \context      TASK
    \synchronous  TRUE
    \reentrant    TRUE
**********************************************************************************************************************/
# if ((COM_TIMEOFFSETOFTXMODETRUE == STD_ON) && (COM_TIMEOFFSETOFTXMODEFALSE == STD_ON))
#  define Com_TxModeHdlr_GetCurrentTimeOffset(TxPduId)           ((Com_IsCurrentTxMode(TxPduId)) ? (Com_GetTimeOffsetOfTxModeTrue(Com_GetTxModeTrueIdxOfTxModeInfo(TxPduId))) : (Com_GetTimeOffsetOfTxModeFalse(Com_GetTxModeFalseIdxOfTxModeInfo(TxPduId))))
# elif (COM_TIMEOFFSETOFTXMODETRUE == STD_ON)
#  define Com_TxModeHdlr_GetCurrentTimeOffset(TxPduId)           ((Com_IsCurrentTxMode(TxPduId)) ? (Com_GetTimeOffsetOfTxModeTrue(Com_GetTxModeTrueIdxOfTxModeInfo(TxPduId))) : 1u)
# elif (COM_TIMEOFFSETOFTXMODEFALSE == STD_ON)
#  define Com_TxModeHdlr_GetCurrentTimeOffset(TxPduId)           ((Com_IsCurrentTxMode(TxPduId)) ? 1u : (Com_GetTimeOffsetOfTxModeFalse(Com_GetTxModeFalseIdxOfTxModeInfo(TxPduId))))
# else
#  define Com_TxModeHdlr_GetCurrentTimeOffset(TxPduId)           1u
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

# if (COM_TXMODEINFO == STD_ON)
/**********************************************************************************************************************
  Com_TxModeHdlr_InitTxIpdu
**********************************************************************************************************************/
/*! \brief        This function initializes a Tx I-PDU in Com_TxModeHdlr.
    \details      -
    \pre          -
    \param[in]    ComPduId Handle of the Tx I-PDU.
    \trace        SPEC-2736775
    \context      TASK
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxModeHdlr_InitTxIpdu(PduIdType ComPduId);

#  if ((COM_PERIODICOFTXMODETRUE == STD_ON) || (COM_PERIODICOFTXMODEFALSE == STD_ON) || (COM_REPCNTOFTXMODETRUE == STD_ON) || (COM_REPCNTOFTXMODEFALSE == STD_ON) || (COM_MINIMUMDELAYOFTXMODEINFO == STD_ON))
/**********************************************************************************************************************
  Com_TxModeHdlr_MainFunctionTx_CycleCounter
**********************************************************************************************************************/
/*! \brief    This function iterates over all Tx ComIPdus and processes the cyclic transmission.
    \details  -
    \pre      -
    \context  TASK
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxModeHdlr_MainFunctionTx_CycleCounter(void);
#  endif

/**********************************************************************************************************************
  Com_TxModeHdlr_MainFunctionTx_Transmit
**********************************************************************************************************************/
/*! \brief    This function iterates over all Tx ComIPdus and process the related transmit requests.
    \details  -
    \pre      -
    \context      TASK
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxModeHdlr_MainFunctionTx_Transmit(void);

#  if ((COM_MINIMUMDELAYOFTXMODEINFO == STD_ON) || (COM_REPCNTOFTXMODETRUE == STD_ON) || (COM_REPCNTOFTXMODEFALSE == STD_ON))
/**********************************************************************************************************************
  Com_TxModeHdlr_Confirmation
**********************************************************************************************************************/
/*! \brief        This method serves to start the delay time counter of the dependent I-PDU.
    \details      -
    \pre          -
    \param[in]    ComTxPduId    ID of Tx I-PDU.
    \return       TRUE:   report the confirmation to the upper layer
                  FALSE:  don't report the confirmation (used in Direct N-Times transmissions)
    \trace        SPEC-2736859
    \context      TASK|ISR2
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
**********************************************************************************************************************/
FUNC(boolean, COM_CODE) Com_TxModeHdlr_Confirmation(CONST(PduIdType, AUTOMATIC) ComTxPduId);
#  endif

/**********************************************************************************************************************
  Com_TxModeHdlr_InitTxMode
**********************************************************************************************************************/
/*! \brief        This method initializes the transmission mode parameters (e.g. cycle counter). It is called each time
                  the active tx mode changes.
    \details      -
    \pre          -
    \param[in]    ComTxPduId    ID of Tx I-PDU.
    \context      TASK|ISR2
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxModeHdlr_InitTxMode(CONST(PduIdType, AUTOMATIC) ComTxPduId);

#  if (COM_TXFILTERINITSTATEUSEDOFTXMODEINFO == STD_ON)
/**********************************************************************************************************************
  Com_TxModeHdlr_UpdateTMS
**********************************************************************************************************************/
/*! \brief        This method manages the I-PDU transmission mode selection.
    \details      -
    \pre          -
    \param[in]    idxTxModeInfo    ID of Tx I-PDU.
    \context      TASK|ISR2
    \trace        SPEC-2736812
    \trace        SPEC-2736813
    \trace        SPEC-2736814
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxModeHdlr_UpdateTMS(CONST(PduIdType, AUTOMATIC) idxTxModeInfo);
#  endif

/**********************************************************************************************************************
  Com_TxModeHdlr_StopTxIpdus
**********************************************************************************************************************/
/*! \brief        This method cancels outstanding transmission requests of an I-PDU and reloads the time offset counter.
    \details      -
    \pre          -
    \param[in]    ComTxPduId  ID of Tx I-PDU.
    \trace        SPEC-2736842
    \context      TASK|ISR2
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxModeHdlr_StopTxIpdus(CONST(PduIdType, AUTOMATIC) ComTxPduId);
# endif

# if (COM_TXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_TxModeHdlr_TriggerIpduSendOnceDeferred
**********************************************************************************************************************/
/*! \brief        This method sets the internal transmit request flag and the I-PDU is transmitted once.
                  The I-PDU Transmit request is performed with the next call of Com_TxModeHdlr_MainFunction.
    \details      -
    \pre          -
    \param[in]    ComTxPduId  ID of Tx I-PDU.
    \context      TASK|ISR2
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxModeHdlr_TriggerIpduSendOnceDeferred(CONST(PduIdType, AUTOMATIC) ComTxPduId);
# endif

# if (COM_GWTIMEOUTINFO == STD_ON)
/**********************************************************************************************************************
Com_TxModeHdlr_StartCyclicTransmission
**********************************************************************************************************************/
/*! \brief        This method starts the cyclic transmission of an I-PDU.
    \details      -
    \pre          -
    \param[in]    ComTxPduId    ID of Tx I-PDU.
    \context      TASK|ISR
    \synchronous  TRUE
    \reentrant    TRUE, for different Handles
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxModeHdlr_StartCyclicTransmission(CONST(PduIdType, AUTOMATIC) ComTxPduId);

/**********************************************************************************************************************
Com_TxModeHdlr_StopCyclicTransmission
**********************************************************************************************************************/
/*! \brief        This method stops the cyclic transmission of an I-PDU and cancels outstanding transmission requests of
                  an I-PDU and reloads the time offset counter, if the I-PDU is restarted later.
    \details      -
    \pre          -
    \param[in]    ComTxPduId    ID of Tx I-PDU.
    \context      TASK|ISR2
    \synchronous  TRUE
    \reentrant    TRUE, for different Handles
    \warning      This function is a private function and is only called by the Com module and must not interface with Com_TxModeHdlr_MainFunction.
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxModeHdlr_StopCyclicTransmission(CONST(PduIdType, AUTOMATIC) ComTxPduId);
# endif

# if ((((COM_DIRECTOFTXMODETRUE == STD_ON) || (COM_DIRECTOFTXMODEFALSE == STD_ON)) && ((COM_FILTERINFOUSEDOFTXSIGINFO == STD_ON) || (COM_GWTXPDUDESCRIPTIONINFOUSEDOFRXPDUINFO == STD_ON) || (COM_GENERATED_DESCRIPTION_ROUTING == STD_ON)))|| (COM_ONCHANGEUSEDOFTXSIGINFO == STD_ON)||(COM_TRIGGEREDOFTXSIGINFO == STD_ON))   /* COV_COM_VAR_ELISA_STD_OFF_TF_tf_tf_tf_tf_xf_tf_tf */
/**********************************************************************************************************************
  Com_TxModeHdlr_TriggerDeferredTransmitAndSetTimer
**********************************************************************************************************************/
/*! \brief        This method sets the internal transmit request flag and the I-PDU is transmitted once or multiple.
                  Further, the timer for normal Tx Deadline Monitoring is reloaded.
                  The I-PDU Transmit request is performed with the next call of Com_TxModeHdlr_MainFunction.
    \details      -
    \pre          -
    \param[in]    ComTxPduId                ID of Tx I-PDU.
    \param[in]    TriggerWithoutRepetition  Decide whether configured repetitions are taken into account.
                                        TRUE:  I-PDU is triggered just once without a repetition.
                                        FALSE: Configured repetitions are taken into account.
    \context      TASK|ISR2
    \synchronous  TRUE
    \reentrant    TRUE, for different Handles
    \warning      This function is for internal purpose only.
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxModeHdlr_TriggerDeferredTransmitAndSetTimer(CONST(PduIdType, AUTOMATIC) ComTxPduId, boolean TriggerWithoutRepetition);
# endif

# if (COM_TXTOUTINFO == STD_ON)
/**********************************************************************************************************************
  Com_TxModeHdlr_ReloadTxDlMonCounter
**********************************************************************************************************************/
/*! \brief        This method reloads the timer for normal Tx Deadline Monitoring if the timer is not already running.
    \details      -
    \param[in]    ComTxPduId                ID of Tx I-PDU.
    \context      TASK|ISR2
    \synchronous  TRUE
    \reentrant    TRUE, for different Handles
    \pre          Function shall only be called in Normal Mode of Tx Deadline monitoring.
    \trace        SPEC-5131191
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxModeHdlr_ReloadTxDlMonCounter(CONST(PduIdType, AUTOMATIC) ComTxPduId);
# endif

# if ((COM_REPPERIODOFTXMODETRUE == STD_ON) || (COM_REPPERIODOFTXMODEFALSE == STD_ON))
/**********************************************************************************************************************
  Com_TxModeHdlr_GetCurrentRepetitionPeriod
**********************************************************************************************************************/
/*! \brief        This function returns the current repetition period. The repetition period depends on the current tx mode.
    \details      -
    \pre          -
    \param[in]    TxPduId     Tx ComIPdu handle id
    \return       Com_RepCycleCntType   current repetition period
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
    \context      TASK|ISR2
**********************************************************************************************************************/
FUNC(Com_RepCycleCntType, COM_CODE) Com_TxModeHdlr_GetCurrentRepetitionPeriod(PduIdType TxPduId);
# endif

# if ((COM_REPCNTOFTXMODETRUE == STD_ON) || (COM_REPCNTOFTXMODEFALSE == STD_ON))
/**********************************************************************************************************************
  Com_TxModeHdlr_GetCurRepCnt
**********************************************************************************************************************/
/*! \brief        This function returns the current repetition count configuration constant.
                  The repetition count configuration constant depends on the current tx mode.
    \details      -
    \pre          -
    \param[in]    TxPduId     Tx ComIPdu handle id
    \return       Com_RepCntType
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
    \context      TASK|ISR2
**********************************************************************************************************************/
FUNC(Com_RepCntType, COM_CODE) Com_TxModeHdlr_GetCurRepCnt(PduIdType TxPduId);
# endif

# define COM_STOP_SEC_CODE
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_MemMap */

#endif /* COM_TXMODEHDLR_H */
/**********************************************************************************************************************
  END OF FILE: Com_TxModeHdlr.h
**********************************************************************************************************************/
