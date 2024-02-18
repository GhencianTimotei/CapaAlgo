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
/*!        \file  Com.c
 *        \brief  MICROSAR Communication source file
 *
 *      \details  This is the implementation of the MICROSAR Communication module.
 *                The basic software module is based on the AUTOSAR Communication specification.
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

#define COM_SOURCE
/*! compatibility define for COM_SOURCE. */
#define V_IL_ASRCOMCFG5_COMPONENT_SOURCE

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
#include "Com.h"
#include "Com_LMgt.h"
#include "Com_LLIf.h"
#include "Com_Timer.h"
#include "Com_Gateway.h"
#include "Com_SignalIf.h"
#include "Com_TxModeHdlr.h"
#include "Com_RxProcessing.h"
#include "Com_IPduGroupHdlr.h"
#include "Com_Notifications.h"
#if(COM_USE_INIT_POINTER == STD_ON)
# include "EcuM_Error.h"
#endif
#include "SchM_Com.h"
#include "vstdlib.h"

/**********************************************************************************************************************
  VERSION CHECK
**********************************************************************************************************************/
#if ((COM_SW_MAJOR_VERSION != 21u) || (COM_SW_MINOR_VERSION != 2u) || (COM_SW_PATCH_VERSION != 0u))
# error "Vendor specific version numbers of Com.c and Com.h are inconsistent"
#endif

/**********************************************************************************************************************
  LOCAL CONSTANT MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
  LOCAL FUNCTION MACROS
**********************************************************************************************************************/
#if !defined (COM_LOCAL_INLINE)
# define COM_LOCAL_INLINE LOCAL_INLINE
#endif

/**********************************************************************************************************************
  LOCAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/

/**********************************************************************************************************************
  LOCAL DATA PROTOTYPES
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/

#if(COM_USE_INIT_POINTER == STD_ON)
# define COM_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_MemMap */

P2CONST(Com_ConfigType, COM_VAR_ZERO_INIT, COM_PBCFG) Com_ConfigDataPtr = NULL_PTR;     /* PRQA S 1504 */ /* MD_MSR_Rule8.7 */

# define COM_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_MemMap */
#endif

/**********************************************************************************************************************
  LOCAL FUNCTION PROTOTYPES
**********************************************************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"    /* PRQA S 5087 */        /* MD_MSR_MemMap */

#if (COM_GWINFO == STD_ON)

/**********************************************************************************************************************
  Com_SignalGw_EnterExclusiveArea
**********************************************************************************************************************/
/*! \brief    This function enters the gw signal routing exclusive area.
    \details  -
    \pre      -
    \trace    DSGN-COM_ISRTHRESHOLD_CONCEPT
    \context  TASK
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_SignalGw_EnterExclusiveArea(void);

/**********************************************************************************************************************
  Com_SignalGw_ExitExclusiveArea
**********************************************************************************************************************/
/*! \brief    This function exits the gw signal routing exclusive area.
    \details  -
    \pre      -
    \trace    DSGN-COM_ISRTHRESHOLD_CONCEPT
    \context  TASK
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_SignalGw_ExitExclusiveArea(void);

/**********************************************************************************************************************
  Com_SignalGw_ThresholdCheck
**********************************************************************************************************************/
/*! \brief    This function checks if the ISR Lock must be opened
    \details  -
    \pre      -
    \trace    DSGN-COM_ISRTHRESHOLD_CONCEPT
    \context  TASK
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_SignalGw_ThresholdCheck(void);

#endif

/**********************************************************************************************************************
  LOCAL FUNCTIONS
**********************************************************************************************************************/
#if (COM_GWINFO == STD_ON)
/**********************************************************************************************************************
  Com_SignalGw_EnterExclusiveArea
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_SignalGw_EnterExclusiveArea(void)
{
  /* #10 Enter the gw signal routing exclusive area */
  SchM_Enter_Com_COM_EXCLUSIVE_AREA_BOTH();
}

/**********************************************************************************************************************
  Com_SignalGw_ExitExclusiveArea
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_SignalGw_ExitExclusiveArea(void)
{
  /* #05 Reload the counter with the threshold value */
  Com_SetGatewayProcessingISRLockCounter(Com_GetGatewayProcessingISRLockThreshold());   /* SBSW_COM_CSL_VAR_ACCESS */
  /* #10 Exit the gw signal routing exclusive area */
  SchM_Exit_Com_COM_EXCLUSIVE_AREA_BOTH();
}

/**********************************************************************************************************************
  Com_SignalGw_ThresholdCheck
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_SignalGw_ThresholdCheck(void)
{
  if(Com_GetGatewayProcessingISRLockCounter() > 0u)     /* COV_COM_THRESHOLD_TX */
  {
    Com_DecGatewayProcessingISRLockCounter();   /* SBSW_COM_CSL_VAR_ACCESS */
  }
  else
  {
    Com_SignalGw_ExitExclusiveArea();
    Com_SignalGw_EnterExclusiveArea();
  }
}
#endif

/**********************************************************************************************************************
  GLOBAL FUNCTIONS
**********************************************************************************************************************/

#if (COM_MAIN_FUNCTION_ROUTE_SIGNALS_API == STD_ON)
/**********************************************************************************************************************
  Com_MainFunctionRouteSignals
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_MainFunctionRouteSignals(void)
{
  if(Com_IsInitialized())
  {
    /* #10 Do description routing, if GENERATED_DESCRIPTION_ROUTING is on use the generated description routing function, otherwise use the static function */
# if (COM_GENERATED_DESCRIPTION_ROUTING == STD_ON)      /* COV_COM_VAR_ELISA_STD_OFF_XF */
    Com_RxGwMainFunctionRoute();
# elif (COM_GWEVENTCACHE == STD_ON)
    Com_MainFunction_GwDescription();
# endif

# if (COM_GWINFO == STD_ON)
    {
      Com_GwInfoIterType idxGwInfo;

      Com_SignalGw_EnterExclusiveArea();
      /* #20 Iterate over all gateway event flags */
      for(idxGwInfo = 0; idxGwInfo < Com_GetSizeOfGwInfo(); idxGwInfo++)
      {
        /* #30 If a gateway event flag is set */
        if(Com_IsGwEvent(idxGwInfo))
        {
          Com_SetGwEvent(idxGwInfo, FALSE);     /* SBSW_COM_CSL02 */

#  if (COM_GWSIGMAPPINGENDIDXOFGWINFO == STD_ON)
          /* #40 Do normal signal routings */
          Com_MainFunction_SignalRoutings(idxGwInfo);
#  endif

#  if (COM_GWSIGGRPMAPPINGENDIDXOFGWINFO == STD_ON)
          /* #50 Do normal signal group routings */
          Com_MainFunction_SignalGroupRoutings(idxGwInfo);
#  endif
        }
        Com_SignalGw_ThresholdCheck();
      }
      Com_SignalGw_ExitExclusiveArea();
    }
# endif
  }
}
#endif

/**********************************************************************************************************************
Com_IpduGroupStart
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_IpduGroupStart(Com_IpduGroupIdType IpduGroupId, boolean Initialize)
{
/* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = COM_E_NO_ERROR;       /* PRQA S 2981 */ /* MD_MSR_RetVal */

/* ----- Development Error Checks ------------------------------------- */
/* #10 Check if component is initialized */
  if(!Com_IsInitialized())
  {
    errorId = COM_E_UNINIT;
  }
#if (COM_DEV_ERROR_DETECT == STD_ON )   /* COV_COM_VAR_ELISA_STD_ON_TX */
# if (COM_IPDUGROUPINFO == STD_ON)
/* #20 Check plausibility of input parameters */
  else if(IpduGroupId >= Com_GetSizeOfIPduGroupInfo())
  {
    errorId = COM_E_PARAM;
  }
#  if(COM_INVALIDHNDOFIPDUGROUPINFO == STD_ON)
  else if(Com_IsInvalidHndOfIPduGroupInfo(IpduGroupId))
  {
    errorId = COM_E_PARAM;
  }
#  endif
# endif
#endif
  else
  {
#if (COM_IPDUGROUPINFO == STD_ON)
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Iterate over all related SubIPduGroups */
    Com_IPduGroupInfoToSubIPduGroupsIndEndIdxOfIPduGroupInfoType subIpduGroupInd = Com_GetIPduGroupInfoToSubIPduGroupsIndStartIdxOfIPduGroupInfo(IpduGroupId);
    for(; subIpduGroupInd < Com_GetIPduGroupInfoToSubIPduGroupsIndEndIdxOfIPduGroupInfo(IpduGroupId); subIpduGroupInd++)
    {
      Com_IpduGroupIdType subIpduGroupId = (Com_IpduGroupIdType) Com_GetIPduGroupInfoToSubIPduGroupsInd(subIpduGroupInd);
      /* #40 If SubIPduGroup is INACTIVE, activate the SubIPduGroup and start the related Rx and Tx ComIPdus */
      if(Com_GetIPduGroupState(subIpduGroupId) == COM_INACTIVE_IPDUGROUPSTATE)
      {
        Com_SetIPduGroupState(subIpduGroupId, COM_ACTIVE_DMACTIVE_IPDUGROUPSTATE);      /* SBSW_COM_CSL03 */
# if (COM_RXPDUINFOINDUSEDOFIPDUGROUPINFO == STD_ON)
        Com_IpduGroupStartRx(subIpduGroupId, Initialize);
# endif
# if (COM_TXPDUINFOINDUSEDOFIPDUGROUPINFO == STD_ON)
        Com_IpduGroupStartTx(subIpduGroupId, Initialize);
# endif
      }
    }
#else
    errorId = COM_E_PARAM;
#endif
  }

/* ----- Development Error Report --------------------------------------- */
#if (COM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != COM_E_NO_ERROR) /* PRQA S 2991, 2995 */ /* MD_Com_2991, MD_Com_2995 */ /* COV_COM_ONLY_DET_FUNCTIONALITY_PRESENT */
  {
    Com_LMgt_CallDetErrorContinue(COMServiceId_IpduGroupControl, errorId);
  }
#endif

  COM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(IpduGroupId);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(Initialize);      /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

}       /* PRQA S 6080 */ /* MD_MSR_STMIF */


/**********************************************************************************************************************
  Com_IpduGroupStop
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_IpduGroupStop(Com_IpduGroupIdType IpduGroupId) /* PRQA S 1505 */ /* MD_MSR_Rule8.7 */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = COM_E_NO_ERROR;       /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check if component is initialized */
  if(!Com_IsInitialized())
  {
    errorId = COM_E_UNINIT;
  }
#if (COM_DEV_ERROR_DETECT == STD_ON )   /* COV_COM_VAR_ELISA_STD_ON_TX */
# if (COM_IPDUGROUPINFO == STD_ON)      /* COV_COM_VAR_DEPENDENT_SWITCH */
  /* #20 Check plausibility of input parameters */
  else if(IpduGroupId >= Com_GetSizeOfIPduGroupInfo())
  {
    errorId = COM_E_PARAM;
  }
#  if(COM_INVALIDHNDOFIPDUGROUPINFO == STD_ON)
  else if(Com_IsInvalidHndOfIPduGroupInfo(IpduGroupId))
  {
    errorId = COM_E_PARAM;
  }
#  endif
# endif
#endif
  else
  {
#if (COM_IPDUGROUPINFO == STD_ON)
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Iterate over all related SubIPduGroups and stop them */
    Com_IPduGroupInfoToSubIPduGroupsIndEndIdxOfIPduGroupInfoType subIpduGroupInd = Com_GetIPduGroupInfoToSubIPduGroupsIndStartIdxOfIPduGroupInfo(IpduGroupId);
    for(; subIpduGroupInd < Com_GetIPduGroupInfoToSubIPduGroupsIndEndIdxOfIPduGroupInfo(IpduGroupId); subIpduGroupInd++)
    {
      Com_IpduGroupIdType subIpduGroupId = (Com_IpduGroupIdType) Com_GetIPduGroupInfoToSubIPduGroupsInd(subIpduGroupInd);
      Com_IpduGroupStopSubGroup(subIpduGroupId);
    }
#else
    errorId = COM_E_PARAM;
#endif
  }

  /* ----- Development Error Report --------------------------------------- */
#if (COM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != COM_E_NO_ERROR) /* PRQA S 2991, 2995 */ /* MD_Com_2991, MD_Com_2995 */ /* COV_COM_ONLY_DET_FUNCTIONALITY_PRESENT */
  {
    Com_LMgt_CallDetErrorContinue(COMServiceId_IpduGroupControl, errorId);
  }
#endif

  COM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(IpduGroupId);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}

#if (COM_PDUGRPVECTOR == STD_ON)
/**********************************************************************************************************************
  Com_ClearIpduGroupVector
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_ClearIpduGroupVector(Com_IpduGroupVector ipduGroupVector)      /* PRQA S 1505 */ /* MD_MSR_Rule8.7 */
{
  VStdMemSet(&ipduGroupVector[0], 0u, COM_LMGT_MAXIPDUGROUPVECTORBYTECNT);      /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_COM_PTR_API_VALID_PTR */
}
#endif

/**********************************************************************************************************************
Com_IpduGroupControl
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_IpduGroupControl(Com_IpduGroupVector ipduGroupVector, boolean initialize)      /* PRQA S 1505, 3206, 3677 */ /* MD_MSR_Rule8.7, MD_Com_3206, MD_Com_3677 */
{
/* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = COM_E_NO_ERROR;       /* PRQA S 2981 */ /* MD_MSR_RetVal */

/* ----- Development Error Checks ------------------------------------- */
/* #10 Check if component is initialized */
  if(!Com_IsInitialized())
  {
    errorId = COM_E_UNINIT;
  }
  else
  {

#if (COM_PDUGRPVECTOR == STD_ON)
    /* ----- Implementation ----------------------------------------------- */
# if (COM_ACTIVATABLERXCOMIPDUS == STD_ON)
    {
      /* #30 Update the states of all related Rx ComIPdus */
      Com_IpduGroupControl_UpdateRxComIPduState(ipduGroupVector, initialize);   /* SBSW_COM_PTR_API_VALID_PTR */
    }
# endif
# if (COM_ACTIVATABLETXCOMIPDUS == STD_ON)
    {
      /* #40 Iterate over all Tx ComIPdus and set the requested state */
      Com_ActivatableTxComIPdusIterType idx;

      Com_TxIPduGroup_EnterExclusiveArea();

      for(idx = 0; idx < Com_GetSizeOfActivatableTxComIPdus(); idx++)
      {
        Com_TxPduInfoIterType ComTxPduId = Com_GetTxPduInfoIdxOfActivatableTxComIPdus(idx);

        /* Evaluate requested active state of the I-PDU */
        boolean bRequestedActiveState = Com_IpduGroupControl_EvaluateActiveState(ipduGroupVector, ComTxPduId);  /* SBSW_COM_PTR_API_VALID_PTR */

        /* COM615 For all I-PDUs that do not change their activation state, the function Com_IpduGroupControl shall do nothing. */
        Com_IpduGroupControl_SetRequestedActiveState(ComTxPduId, initialize, bRequestedActiveState);

        Com_TxIPduGroup_ThresholdCheck();
      }

      Com_TxIPduGroup_ExitExclusiveArea();
    }
# endif
#else
    errorId = COM_E_PARAM;
#endif
  }

/* ----- Development Error Report --------------------------------------- */
#if (COM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != COM_E_NO_ERROR) /* PRQA S 2991, 2995 */ /* MD_Com_2991, MD_Com_2995 */ /* COV_COM_ONLY_DET_FUNCTIONALITY_PRESENT */
  {
    Com_LMgt_CallDetErrorContinue(COMServiceId_IpduGroupControl, errorId);
  }
#endif
  COM_DUMMY_STATEMENT(ipduGroupVector); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(initialize);      /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}

#if (COM_PDUGRPVECTOR == STD_ON)
/**********************************************************************************************************************
  Com_SetIpduGroup
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_SetIpduGroup(Com_IpduGroupVector ipduGroupVector, Com_IpduGroupIdType ipduGroupId, boolean bitval)
{
  /* ----- Local Variables ---------------------------------------------- */

  uint8 errorId = COM_E_NO_ERROR;       /* PRQA S 2981 */ /* MD_MSR_RetVal */


  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check if component is initialized */
  if(!Com_IsInitialized())
  {
    errorId = COM_E_UNINIT;
  }
# if (COM_DEV_ERROR_DETECT == STD_ON )  /* COV_COM_VAR_ELISA_STD_ON_TX */
  /* #20 Check plausibility of input parameters */
  else if(ipduGroupId > COM_SUPPORTED_IPDU_GROUPS)
  {
    errorId = COM_E_PARAM;
  }
# endif
  else
  {
    /* #30 If the passed ComIPduGroup shall be disabled, disable the ComIPduGroup within the passed ComIPduGroup vector */
    if((bitval) == FALSE)
    {
      (ipduGroupVector)[(ipduGroupId) >> 3u] &= /* SBSW_COM_PTR_API_VALID_PTR */
        COM_CAST2UINT8(~(COM_CAST2UINT8(1u << ((ipduGroupId) & (Com_IpduGroupIdType) 7u))));    /* PRQA S 2985 */ /* MD_Com_2985_2986 */
    }
    /* #40 Otherwise enable the ComIPduGroup within the passed ComIPduGroup vector */
    else
    {
      (ipduGroupVector)[(ipduGroupId) >> 3u] |= /* SBSW_COM_PTR_API_VALID_PTR */
        COM_CAST2UINT8(1u << ((ipduGroupId) & (Com_IpduGroupIdType) 7u));       /* PRQA S 2985 */ /* MD_Com_2985_2986 */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (COM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != COM_E_NO_ERROR) /* PRQA S 2991, 2995 */ /* MD_Com_2991, MD_Com_2995 */
  {
    Com_LMgt_CallDetErrorContinue(COMServiceId_SetIpduGroup, errorId);
  }
# endif

  COM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}
#endif

/**********************************************************************************************************************
Com_SwitchIpduTxMode
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_SwitchIpduTxMode(PduIdType PduId, boolean Mode)
{
/* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = COM_E_NO_ERROR;       /* PRQA S 2981 */ /* MD_MSR_RetVal */

/* ----- Development Error Checks ------------------------------------- */
/* #10 Check if component is initialized */
  if(!Com_IsInitialized())
  {
    errorId = COM_E_UNINIT;
  }
#if (COM_DEV_ERROR_DETECT == STD_ON )   /* COV_COM_VAR_ELISA_STD_ON_TX */
/* #20 Check plausibility of input parameters */
# if (COM_TXMODEINFO == STD_ON)
  else if(PduId >= Com_GetSizeOfTxModeInfo())
  {
    errorId = COM_E_PARAM;
  }
#  if (COM_INVALIDHNDOFTXMODEINFO == STD_ON)
  else if(Com_IsInvalidHndOfTxModeInfo(PduId))
  {
    errorId = COM_E_PARAM;
  }
#  endif
# endif
#endif
  else
  {
    /* ----- Implementation ----------------------------------------------- */
#if (COM_TXMODEINFO == STD_ON)
    /* #30 If the passed tx mode differs form the current tx mode, update the current tx mode value and initialize the new tx mode */
    if(Com_IsCurrentTxMode(PduId) != Mode)
    {
      Com_SetCurrentTxMode(PduId, Mode);        /* SBSW_COM_CSL02 */
      Com_TxModeHdlr_InitTxMode(PduId);

# if ((COM_TIMEOFFSETOFTXMODETRUE == STD_ON) || (COM_TIMEOFFSETOFTXMODEFALSE == STD_ON))
      /* #40 If new mode is cyclic (MIXED or DIRECT) */
      if(Com_IsCyclicSendRequest(PduId) == TRUE)        /* COV_COM_ONLY_MIXED_PDUS */
      {
        Com_CycleTimeCntType currentTimeOffset = Com_TxModeHdlr_GetCurrentTimeOffset(PduId);    /* COV_COM_SETCYCLETIMECOUNT */
        /* #50 If TimeOffset is configured, set periodic counter to FirstTimeOffset */
        if(currentTimeOffset > 1U)
        {
#  if (COM_MINIMUMDELAYOFTXMODEINFO == STD_ON)
          /* If MDT remaining time is smaller than FirstTimeOffset */
          if(Com_GetDelayTimeCnt(PduId) < currentTimeOffset)
          {
            /* Clear TransmitRequest, as elapsing MDT shall not trigger transmission */
            Com_SetTransmitRequest(PduId, FALSE);       /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
            /* Set period to FirstTimeOffset */
            Com_SetCycleTimeCnt(PduId, currentTimeOffset);      /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
          }
#  else
          /* Set period to FirstTimeOffset */
          Com_SetCycleTimeCnt(PduId, currentTimeOffset);        /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
#  endif
#  if (COM_TXTOUTINFO == STD_ON)
          /* If deadline monitoring is configured for the PDU, reset counter */
          if(Com_IsTxTOutInfoUsedOfTxPduInfo(PduId))    /* COV_COM_NO_TIMEOUT_AND_OFFSET */
          {
            Com_TxTOutInfoIdxOfTxPduInfoType idxTxTOutInfo = Com_GetTxTOutInfoIdxOfTxPduInfo(PduId);
            Com_SetTxTOutCnt(idxTxTOutInfo, 0u);        /* SBSW_COM_CSL02 */
          }
#  endif
        }
      }
# endif
    }
#else
    errorId = COM_E_PARAM;
#endif
  }

/* ----- Development Error Report --------------------------------------- */
#if (COM_DEV_ERROR_REPORT == STD_ON)

  if(errorId != COM_E_NO_ERROR) /* PRQA S 2991, 2995 */ /* MD_Com_2991, MD_Com_2995 */ /* COV_COM_ONLY_DET_FUNCTIONALITY_PRESENT */
  {
    Com_LMgt_CallDetErrorContinue(COMServiceId_SwitchIpduTxMode, errorId);
  }
#endif

  COM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(PduId);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(Mode);    /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}       /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
Com_ReceptionDMControl
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_ReceptionDMControl(Com_IpduGroupVector ipduGroupVector)        /* PRQA S 3677 */ /* MD_Com_3677 */
{
/* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = COM_E_NO_ERROR;       /* PRQA S 2981 */ /* MD_MSR_RetVal */

/* ----- Development Error Checks ------------------------------------- */
/* #10 Check if component is initialized */
  if(!Com_IsInitialized())      /* COV_COM_ONLY_DET_FUNCTIONALITY_PRESENT */
  {
    errorId = COM_E_UNINIT;
  }
  else
  {
#if (COM_ACTIVATABLERXCOMIPDUS == STD_ON)
    /* ----- Implementation ----------------------------------------------- */
# if (COM_RXTOUTINFOINDENDIDXOFRXPDUINFO == STD_ON)
    {
      {
        Com_ActivatableRxComIPdusIterType idx;
        /* \trace SPEC-2736874 */
        /* #20 Iterate over all activatable Rx ComIpdus and set the requested deadline monitoring state */
        for(idx = 0; idx < Com_GetSizeOfActivatableRxComIPdus(); idx++)
        {
          Com_RxPduInfoIterType ComRxPduId = Com_GetRxPduInfoIdxOfActivatableRxComIPdus(idx);
          /* Evaluate requested active state of the I-PDU */
          Com_RxPduDmStateType bRequestedActiveState = Com_ReceptionDMControl_EvaluateActiveState(ipduGroupVector, ComRxPduId); /* SBSW_COM_PTR_API_VALID_PTR */
          Com_ReceptionDMControl_SetDmState(ComRxPduId, bRequestedActiveState);
        }
      }
    }
# endif
#else
    errorId = COM_E_PARAM;
#endif
  }

/* ----- Development Error Report --------------------------------------- */
#if (COM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != COM_E_NO_ERROR) /* PRQA S 2991, 2995 */ /* MD_Com_2991, MD_Com_2995 */ /* COV_COM_ONLY_DET_FUNCTIONALITY_PRESENT */
  {
    Com_LMgt_CallDetErrorContinue(COMServiceId_ReceptionDMControl, errorId);
  }
#endif

  COM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(ipduGroupVector); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}

/**********************************************************************************************************************
Com_EnableReceptionDM
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_EnableReceptionDM(Com_IpduGroupIdType IpduGroupId)
{
/* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = COM_E_NO_ERROR;       /* PRQA S 2981 */ /* MD_MSR_RetVal */

/* ----- Development Error Checks ------------------------------------- */
/* #10 Check if component is initialized */
  if(!Com_IsInitialized())
  {
    errorId = COM_E_UNINIT;
  }
#if (COM_DEV_ERROR_DETECT == STD_ON )   /* COV_COM_VAR_ELISA_STD_ON_TX */
# if (COM_IPDUGROUPINFO == STD_ON)      /* COV_COM_VAR_DEPENDENT_SWITCH */
/* #20 Check plausibility of input parameters */
  else if(IpduGroupId >= Com_GetSizeOfIPduGroupInfo())
  {
    errorId = COM_E_PARAM;
  }
#  if(COM_INVALIDHNDOFIPDUGROUPINFO == STD_ON)
  else if(Com_IsInvalidHndOfIPduGroupInfo(IpduGroupId))
  {
    errorId = COM_E_PARAM;
  }
#  endif
# endif
#endif
  else
  {
    /* ----- Implementation ----------------------------------------------- */
#if (COM_RXPDUINFOINDUSEDOFIPDUGROUPINFO == STD_ON)     /* COV_COM_VAR_DEPENDENT_SWITCH */
# if (COM_RXTOUTINFOINDENDIDXOFRXPDUINFO == STD_ON)
    /* #30 Iterate over all related SubIpduGroups and enable the Rx deadline monitoring */
    Com_IPduGroupInfoToSubIPduGroupsIndEndIdxOfIPduGroupInfoType subIpduGroupInd = Com_GetIPduGroupInfoToSubIPduGroupsIndStartIdxOfIPduGroupInfo(IpduGroupId);
    for(; subIpduGroupInd < Com_GetIPduGroupInfoToSubIPduGroupsIndEndIdxOfIPduGroupInfo(IpduGroupId); subIpduGroupInd++)
    {
      Com_IpduGroupIdType subIpduGroupId = (Com_IpduGroupIdType) Com_GetIPduGroupInfoToSubIPduGroupsInd(subIpduGroupInd);
      Com_EnableReceptionDMsubGroup(subIpduGroupId);
    }
# endif
#else
    errorId = COM_E_PARAM;
#endif
  }

/* ----- Development Error Report --------------------------------------- */
#if (COM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != COM_E_NO_ERROR) /* PRQA S 2991, 2995 */ /* MD_Com_2991, MD_Com_2995 */ /* COV_COM_ONLY_DET_FUNCTIONALITY_PRESENT */
  {
    Com_LMgt_CallDetErrorContinue(COMServiceId_ReceptionDMControl, errorId);
  }
#endif

  COM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(IpduGroupId);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}

/**********************************************************************************************************************
Com_DisableReceptionDM
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_DisableReceptionDM(Com_IpduGroupIdType IpduGroupId)
{
/* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = COM_E_NO_ERROR;       /* PRQA S 2981 */ /* MD_MSR_RetVal */

/* ----- Development Error Checks ------------------------------------- */
/* #10 Check if component is initialized */
  if(!Com_IsInitialized())
  {
    errorId = COM_E_UNINIT;
  }
#if (COM_DEV_ERROR_DETECT == STD_ON )   /* COV_COM_VAR_ELISA_STD_ON_TX */
# if (COM_IPDUGROUPINFO == STD_ON)      /* COV_COM_VAR_DEPENDENT_SWITCH */
/* #20 Check plausibility of input parameters */
  else if(IpduGroupId >= Com_GetSizeOfIPduGroupInfo())
  {
    errorId = COM_E_PARAM;
  }
#  if(COM_INVALIDHNDOFIPDUGROUPINFO == STD_ON)
  else if(Com_IsInvalidHndOfIPduGroupInfo(IpduGroupId))
  {
    errorId = COM_E_PARAM;
  }
#  endif
# endif
#endif
  else
  {
#if (COM_RXPDUINFOINDUSEDOFIPDUGROUPINFO == STD_ON)     /* COV_COM_VAR_DEPENDENT_SWITCH */
# if (COM_RXTOUTINFOINDENDIDXOFRXPDUINFO == STD_ON)
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Iterate over all related SubIPduGroups and disable the Rx deadline monitoring */
    Com_IPduGroupInfoToSubIPduGroupsIndEndIdxOfIPduGroupInfoType subIpduGroupInd = Com_GetIPduGroupInfoToSubIPduGroupsIndStartIdxOfIPduGroupInfo(IpduGroupId);
    for(; subIpduGroupInd < Com_GetIPduGroupInfoToSubIPduGroupsIndEndIdxOfIPduGroupInfo(IpduGroupId); subIpduGroupInd++)
    {
      Com_IpduGroupIdType subIpduGroupId = (Com_IpduGroupIdType) Com_GetIPduGroupInfoToSubIPduGroupsInd(subIpduGroupInd);
      Com_DisableReceptionDMsubGroup(subIpduGroupId);
    }
# endif
#else
    errorId = COM_E_PARAM;
#endif
  }

/* ----- Development Error Report --------------------------------------- */
#if (COM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != COM_E_NO_ERROR) /* PRQA S 2991, 2995 */ /* MD_Com_2991, MD_Com_2995 */ /* COV_COM_ONLY_DET_FUNCTIONALITY_PRESENT */
  {
    Com_LMgt_CallDetErrorContinue(COMServiceId_ReceptionDMControl, errorId);
  }
#endif

  COM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(IpduGroupId);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}

/**********************************************************************************************************************
Com_MainFunctionTx
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
***********************************************************************************************************************/
FUNC(void, COM_CODE) Com_MainFunctionTx(void)
{
#if (COM_TXMODEINFO == STD_ON)
/* #10 Check if COM is initialized */
  if(Com_IsInitialized())
  {
    /* Tx Counter Handling */
# if (COM_TXCYCLECOUNTERDIVISOR == STD_ON)
    /* #20 Use Tx Mode timing domain */
    Com_DecTxCycleCounterDivisorCounter();      /* SBSW_COM_CSL_VAR_ACCESS */
    if(Com_GetTxCycleCounterDivisorCounter() == 0u)
# endif
    {
# if (COM_TXCYCLECOUNTERDIVISOR == STD_ON)
      Com_SetTxCycleCounterDivisorCounter(Com_GetTxCycleCounterDivisor());      /* SBSW_COM_CSL_VAR_ACCESS */
# endif
# if ((COM_PERIODICOFTXMODETRUE == STD_ON) || (COM_PERIODICOFTXMODEFALSE == STD_ON) || (COM_REPCNTOFTXMODETRUE == STD_ON) || (COM_REPCNTOFTXMODEFALSE == STD_ON) || (COM_MINIMUMDELAYOFTXMODEINFO == STD_ON))
      /* #30 Do TxMode processing */
      Com_TxModeHdlr_MainFunctionTx_CycleCounter();
# endif
    }

    /* Tx deadline monitoring */
# if ((COM_GWTIMEOUTINFO == STD_ON) || (COM_TXTOUTINFO == STD_ON))
#  if (COM_TXDLMONDIVISOR == STD_ON)
    /* #40 Use Tx deadline monitoring timing domain */
    Com_DecTxDlMonDivisorCounter();     /* SBSW_COM_CSL_VAR_ACCESS */
    if(Com_GetTxDlMonDivisorCounter() == 0u)
#  endif
    {
#  if (COM_TXDLMONDIVISOR == STD_ON)
      Com_SetTxDlMonDivisorCounter(Com_GetTxDlMonDivisor());    /* SBSW_COM_CSL_VAR_ACCESS */
#  endif
#  if (COM_TXTOUTINFO == STD_ON)
      /* #50 Do Tx deadline monitoring */
      Com_TxDlMon_MainFunctionTx();
#  endif
#  if (COM_GWTIMEOUTINFO == STD_ON)
      /* #60 Handle GwTimeout, if configured. */
      Com_GwTout_HandleCounter();
#  endif
    }
# endif

    /* #70 Process transmit request and initiate transition */
    Com_TxModeHdlr_MainFunctionTx_Transmit();

# if (COM_CBKTXACKDEFFUNCPTRINDUSEDOFTXPDUINFO == STD_ON)
    /* #80 Process deferred Tx Confirmations */
    Com_TxNHdlr_MainFunctionTx();
# endif
  }
#endif
}

/**********************************************************************************************************************
Com_MainFunctionRx
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_MainFunctionRx(void)
{
#if ((COM_EXISTS_DEFERRED_SIGNALPROCESSINGOFRXPDUINFO == STD_ON)||(COM_RXTOUTINFO == STD_ON))
/* #10 Check if COM is initialized */
  if(Com_IsInitialized())
  {
# if (COM_EXISTS_DEFERRED_SIGNALPROCESSINGOFRXPDUINFO == STD_ON)
    {
      /* #20 Do deferred processing */
      Com_RxDeferredPduProcessing();
    }
# endif
# if (COM_RXTOUTINFO == STD_ON)
    /* #30 Use Rx deadline monitoring timing domain (if configured) */
#  if(COM_RXDLMONDIVISOR == STD_ON)
    Com_DecRxDlMonDivisorCounter();     /* SBSW_COM_CSL_VAR_ACCESS */
    if(Com_GetRxDlMonDivisorCounter() == 0u)
#  endif
    {
#  if(COM_RXDLMONDIVISOR == STD_ON)
      Com_SetRxDlMonDivisorCounter(Com_GetRxDlMonDivisor());    /* SBSW_COM_CSL_VAR_ACCESS */
#  endif
      /* #40 Do Rx deadline monitoring */
      Com_RxDlMon_MainFunctionRx();
    }
# endif
  }
#endif
}

/**********************************************************************************************************************
Com_Init
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_Init(P2CONST(Com_ConfigType, AUTOMATIC, COM_INIT_DATA) config)
{
/* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = COM_E_NO_ERROR;       /* PRQA S 2981 */ /* MD_MSR_RetVal */

#if(COM_USE_INIT_POINTER == STD_ON)
  Com_ConfigDataPtr = config;
#endif
/* ----- Development Error Checks ------------------------------------- */
/* #10 Check plausibility of all input parameters */
  if(Com_IsInitialized())
  {
    errorId = COM_E_INIT_FAILED;
  }
#if(COM_USE_INIT_POINTER == STD_ON)
/* Check validity of Config pointer */
  else if(Com_ConfigDataPtr == NULL_PTR)
  {
# if(COM_USE_ECUM_BSW_ERROR_HOOK == STD_ON)     /* COV_COM_VAR_DEPENDENT_SWITCH */
    EcuM_BswErrorHook(COM_MODULE_ID, ECUM_BSWERROR_NULLPTR);
# endif
    errorId = COM_E_PARAM_POINTER;
  }
# if (COM_FINALMAGICNUMBER == STD_ON)   /* COV_COM_VAR_DEPENDENT_SWITCH */
  else if(Com_GetFinalMagicNumber() != COM_FINAL_MAGIC_NUMBER)
  {
#  if(COM_USE_ECUM_BSW_ERROR_HOOK == STD_ON)    /* COV_COM_VAR_DEPENDENT_SWITCH */
    EcuM_BswErrorHook(COM_MODULE_ID, ECUM_BSWERROR_MAGICNUMBER);
#  endif
    errorId = COM_E_PARAM_POINTER;
    Com_ConfigDataPtr = NULL_PTR;
  }
# endif
  else
#endif
  {
#if (COM_RXPDUINFO == STD_ON)
    {
      /* #20 Initialize all Rx ComIPdus and related parameters */
      Com_InitRx();
    }
#endif
#if (COM_TXPDUINFO == STD_ON)
    {
      /* #30 Initialize all Tx ComIPdus and related parameters */
      Com_InitTx();
    }
# if (COM_TXTOUTCNT == STD_ON)
    /* #40 Initialize all Tx deadline monitoring parameters */
    Com_TxDlMon_Init(); /* PRQA S 2987 */ /* MD_Com_2987 */
# endif
#endif

#if (COM_IPDUGROUPSTATE == STD_ON)
    {
      /* \trace SPEC-2736784 */ /* \trace SPEC-2736788 */
      /* #50 Iterate all ComIPduGroups and set them to INACTIVE */
      Com_SizeOfIPduGroupStateType comIPduGroupId = 0;
      for(; comIPduGroupId < Com_GetSizeOfIPduGroupState(); comIPduGroupId++)
      {
        Com_SetIPduGroupState(comIPduGroupId, COM_INACTIVE_IPDUGROUPSTATE);     /* SBSW_COM_CSL01 */
      }
    }
#endif

    /* #60 Initialize timing domain divisors (if configured) */
#if (COM_TXCYCLECOUNTERDIVISOR == STD_ON)
    Com_SetTxCycleCounterDivisorCounter(1);     /* SBSW_COM_CSL_VAR_ACCESS */
#endif
#if (COM_TXDLMONDIVISOR == STD_ON)
    Com_SetTxDlMonDivisorCounter(1);    /* SBSW_COM_CSL_VAR_ACCESS */
#endif
#if (COM_RXDLMONDIVISOR == STD_ON)
    Com_SetRxDlMonDivisorCounter(1);    /* SBSW_COM_CSL_VAR_ACCESS */
#endif
#if (COM_RXDEFERREDEVENTCACHE == STD_ON)
    /* #70 Initialize next event cache entry (if configured) */
    Com_SetRxNextEventCacheEnty(0);     /* SBSW_COM_CSL_VAR_ACCESS */
#endif
#if (COM_GWEVENTCACHE == STD_ON)
    /* #80 Initialize gateway event cache index (if configured) */
    Com_SetGwEventCacheIndex(0);        /* SBSW_COM_CSL_VAR_ACCESS */
#endif

    /* #85 Initialize ISR lock counter */
#if (COM_GWEVENTCACHE == STD_ON)
    Com_SetGatewayDescriptionProcessingISRLockCounter(Com_GetGatewayDescriptionProcessingISRLockThreshold());   /* SBSW_COM_CSL_VAR_ACCESS */
#endif
#if (COM_GWINFO == STD_ON)
    Com_SetGatewayProcessingISRLockCounter(Com_GetGatewayProcessingISRLockThreshold()); /* SBSW_COM_CSL_VAR_ACCESS */
#endif
#if (COM_RXPDUINFO == STD_ON)
    Com_SetRxIPduGroupISRLockCounter(Com_GetRxIPduGroupISRLockThreshold());     /* SBSW_COM_CSL_VAR_ACCESS */
#endif
#if (COM_TXPDUINFO == STD_ON)
    Com_SetTxIPduGroupISRLockCounter(Com_GetTxIPduGroupISRLockThreshold());     /* SBSW_COM_CSL_VAR_ACCESS */
#endif
#if(COM_EXISTS_DEFERRED_SIGNALPROCESSINGOFRXPDUINFO == STD_ON)
    Com_SetRxDeferredProcessingISRLockCounter(Com_GetRxDeferredProcessingISRLockThreshold());   /* SBSW_COM_CSL_VAR_ACCESS */
#endif
#if(COM_RXTOUTINFO == STD_ON)
    Com_SetRxDeadlineMonitoringISRLockCounter(Com_GetRxDeadlineMonitoringISRLockThreshold());   /* SBSW_COM_CSL_VAR_ACCESS */
#endif
#if(COM_TXTOUTINFO == STD_ON)
    Com_SetTxDeadlineMonitoringISRLockCounter(Com_GetTxDeadlineMonitoringISRLockThreshold());   /* SBSW_COM_CSL_VAR_ACCESS */
#endif
#if ((COM_PERIODICOFTXMODETRUE == STD_ON) || (COM_PERIODICOFTXMODEFALSE == STD_ON) || (COM_REPCNTOFTXMODETRUE == STD_ON) || (COM_REPCNTOFTXMODEFALSE == STD_ON) || (COM_MINIMUMDELAYOFTXMODEINFO == STD_ON))
    Com_SetTxCyclicProcessingISRLockCounter(Com_GetTxCyclicProcessingISRLockThreshold());       /* SBSW_COM_CSL_VAR_ACCESS */
#endif
#if (COM_TXMODEINFO == STD_ON)
    Com_SetTxProcessingISRLockCounter(Com_GetTxProcessingISRLockThreshold());   /* SBSW_COM_CSL_VAR_ACCESS */
#endif
#if (COM_ALWAYSACTIVERXCOMIPDUS == STD_ON)
    /* #90 Activate Rx ComIPdus without assigned ComIPduGroups */
    Com_ActivateAlwaysOnRxComIPdus();
#endif
#if (COM_ALWAYSACTIVETXCOMIPDUS == STD_ON)
    /* #100 Activate Tx ComIPdus without assigned ComIPduGroups */
    Com_ActivateAlwaysOnTxComIPdus();
#endif
    /* #110 Set the component state to INITIALIZED */
    /* Com must be enabled after all subcomponents are initialized */
    Com_SetInitialized(TRUE);   /* SBSW_COM_CSL_VAR_ACCESS */
  }

/* ----- Development Error Report --------------------------------------- */
#if (COM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != COM_E_NO_ERROR) /* PRQA S 2991, 2995 */ /* MD_Com_2991, MD_Com_2995 */
  {
    Com_LMgt_CallDetErrorContinue(COMServiceId_Init, errorId);
  }
#endif

  COM_DUMMY_STATEMENT(config);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}

/**********************************************************************************************************************
Com_InitMemory
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_InitMemory(void)
{
/* #10 Initialize all component _INIT_ variables. */
  Com_SetInitialized(FALSE);    /* SBSW_COM_CSL_VAR_ACCESS */
#if(COM_USE_INIT_POINTER == STD_ON)
  Com_ConfigDataPtr = NULL_PTR;
#endif
}

/**********************************************************************************************************************
Com_DeInit
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_DeInit(void)
{
/* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = COM_E_NO_ERROR;       /* PRQA S 2981 */ /* MD_MSR_RetVal */

/* ----- Development Error Checks ------------------------------------- */
/* #10 Check if component is initialized */
  if(!Com_IsInitialized())
  {
    errorId = COM_E_UNINIT;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    /* ! \note COM130 only specifies that the inter-ECU communication shall be stopped */
#if (COM_IPDUGROUPINFO == STD_ON)
    {
      /* #20 Iterate over all ComIPduGroups and stop them by a call of Com_IpduGroupStop (if ComOptimizedIPduGroupHandling is enabled) */
      Com_IpduGroupIdType comIPduGroupId = 0;
      for(; comIPduGroupId < Com_GetSizeOfIPduGroupInfo(); comIPduGroupId++)
      {
# if(COM_INVALIDHNDOFIPDUGROUPINFO == STD_ON)
        if(!Com_IsInvalidHndOfIPduGroupInfo(comIPduGroupId))
# endif
        {
          Com_IpduGroupStop(comIPduGroupId);
        }
      }
    }
#endif
#if (COM_PDUGRPVECTOR == STD_ON)
    /* #30 Stop all ComIPduGroups by a call of Com_IpduGroupControl (if ComOptimizedIPduGroupHandling is disabled) */
    {
      Com_IpduGroupVector clearIpduGroupVector;
      Com_ClearIpduGroupVector(clearIpduGroupVector);   /* SBSW_COM_FCTCALL_STACKPTR */
      Com_IpduGroupControl(clearIpduGroupVector, FALSE);        /* SBSW_COM_FCTCALL_STACKPTR */
    }
#endif

#if (COM_ALWAYSACTIVERXCOMIPDUS == STD_ON)
    {
      Com_AlwaysActiveRxComIPdusIterType idx;

      Com_RxIPduGroup_EnterExclusiveArea();
      /* #40 Iterate over all Rx ComIPdus without an assigned ComIPduGroup and deactivate Rx ComIPdu */
      for(idx = 0; idx < Com_GetSizeOfAlwaysActiveRxComIPdus(); idx++)
      {
        Com_DeactivateRxComIPdu(Com_GetRxPduInfoIdxOfAlwaysActiveRxComIPdus(idx));
        Com_RxIPduGroup_ThresholdCheck();
      }

      Com_RxIPduGroup_ExitExclusiveArea();
    }
#endif

#if (COM_ALWAYSACTIVETXCOMIPDUS == STD_ON)
    {
      Com_AlwaysActiveTxComIPdusIterType idx;

      Com_TxIPduGroup_EnterExclusiveArea();

      /* #50 Iterate over all Tx ComIPdus without an assigned ComIPduGroup and deactivate Tx ComIPdu */
      for(idx = 0; idx < Com_GetSizeOfAlwaysActiveTxComIPdus(); idx++)
      {
        Com_DeactivateTxComIPdu(Com_GetTxPduInfoIdxOfAlwaysActiveTxComIPdus(idx));
        Com_TxIPduGroup_ThresholdCheck();
      }

      Com_TxIPduGroup_ExitExclusiveArea();
    }
#endif
    Com_SetInitialized(FALSE);  /* SBSW_COM_CSL_VAR_ACCESS */
  }

/* ----- Development Error Report --------------------------------------- */
#if (COM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != COM_E_NO_ERROR) /* PRQA S 2991, 2995 */ /* MD_Com_2991, MD_Com_2995 */
  {
    Com_LMgt_CallDetErrorContinue(COMServiceId_DeInit, errorId);
  }
#endif

  COM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}       /* PRQA S 6050 */ /* MD_MSR_STCAL */

/**********************************************************************************************************************
Com_GetConfigurationId
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
**********************************************************************************************************************/
FUNC(uint32, COM_CODE) Com_GetConfigurationId(void)
{
/* ----- Local Variables ---------------------------------------------- */
  uint32 retVal;                /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = COM_E_NO_ERROR;       /* PRQA S 2981 */ /* MD_MSR_RetVal */

/* ----- Development Error Checks ------------------------------------- */
/* #10 Check if component is initialized */
  if(!Com_IsInitialized())
  {
    errorId = COM_E_UNINIT;
    retVal = 0u;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Get current configuration Id */
    retVal = Com_GetConfigId();
  }

/* ----- Development Error Report --------------------------------------- */
#if (COM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != COM_E_NO_ERROR) /* PRQA S 2991, 2995 */ /* MD_Com_2991, MD_Com_2995 */
  {
    Com_LMgt_CallDetErrorContinue(COMServiceId_GetConfigurationId, errorId);
  }
#endif

  COM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return retVal;
}

/**********************************************************************************************************************
Com_GetStatus
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(Com_StatusType, COM_CODE) Com_GetStatus(void)
{
/* #10 Return the current COM module status */
  return (Com_IsInitialized()? COM_INIT : COM_UNINIT);
}

#if (COM_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
Com_GetVersionInfo
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, COM_APPL_VAR) versioninfo)
{
/* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = COM_E_NO_ERROR;       /* PRQA S 2981 */ /* MD_MSR_RetVal */
/* ----- Development Error Checks ------------------------------------- */
/* #10 Check plausibility of all input parameters */
# if (COM_DEV_ERROR_DETECT == STD_ON )  /* COV_COM_VAR_ELISA_STD_ON_TX */
  if(versioninfo == NULL_PTR)
  {
    errorId = COM_E_PARAM_POINTER;
  }
  else
# endif
  {
    /* #20 Write component data to versioninfo */
    versioninfo->vendorID = COM_VENDOR_ID;      /* SBSW_COM_PTR_API */
    versioninfo->moduleID = COM_MODULE_ID;      /* SBSW_COM_PTR_API */

    versioninfo->sw_major_version = COM_SW_MAJOR_VERSION;       /* SBSW_COM_PTR_API */
    versioninfo->sw_minor_version = COM_SW_MINOR_VERSION;       /* SBSW_COM_PTR_API */
    versioninfo->sw_patch_version = COM_SW_PATCH_VERSION;       /* SBSW_COM_PTR_API */
  }

/* ----- Development Error Report --------------------------------------- */
# if (COM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != COM_E_NO_ERROR) /* PRQA S 2991, 2995 */ /* MD_Com_2991, MD_Com_2995 */
  {
    Com_LMgt_CallDetErrorContinue(COMServiceId_GetVersionInfo, errorId);
  }
# endif

  COM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}
#endif

/**********************************************************************************************************************
Com_ReceiveSignal
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(uint8, COM_CODE) Com_ReceiveSignal(Com_SignalIdType SignalId, P2VAR(void, AUTOMATIC, COM_APPL_VAR) SignalDataPtr)  /* PRQA S 3673 */ /* MD_MSR_Rule8.13 */
{
/* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = COM_E_NO_ERROR;       /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 retVal = COM_SERVICE_NOT_AVAILABLE;     /* PRQA S 2981 */ /* MD_MSR_RetVal */

/* ----- Development Error Checks ------------------------------------- */
/* #10 Check if component is initialized */
  if(!Com_IsInitialized())
  {
    errorId = COM_E_UNINIT;
  }
#if (COM_DEV_ERROR_DETECT == STD_ON)    /* COV_COM_VAR_ELISA_STD_ON_TX */
/* #20 Check plausibility of input parameters */
# if (COM_RXACCESSINFO == STD_ON)
  else if(SignalId >= Com_GetSizeOfRxAccessInfo())
  {
    errorId = COM_E_PARAM;
  }
#  if (COM_INVALIDHNDOFRXACCESSINFO == STD_ON)
  else if(Com_IsInvalidHndOfRxAccessInfo(SignalId))
  {
    errorId = COM_E_PARAM;
  }
#  endif
# endif
  else if(SignalDataPtr == NULL_PTR)
  {
    errorId = COM_E_PARAM_POINTER;
  }
#endif
  else
  {
#if (COM_RXACCESSINFO == STD_ON)
    /* ----- Implementation ----------------------------------------------- */
# if ((COM_BUFFERUSEDOFRXACCESSINFO == STD_ON) || (COM_RXSIGBUFFERARRAYBASEDBUFFERUSEDOFRXACCESSINFO == STD_ON))
    /* #30 Copy the stored ComSignal value to the passed SignalDataPtr */
    Com_ReceiveSignal_GetRxSigBuffer(SignalId, SignalDataPtr);  /* SBSW_COM_PTR_API */
# endif

    /* #40 If the related ComIPduGroup is active, E_OK will be returned otherwise COM_SERVICE_NOT_AVAILABLE will be returned */
    if(Com_IsRxPduGrpActive(Com_GetRxPduInfoIdxOfRxAccessInfo(SignalId)))       /* COV_COM_NO_IPDUGROUPS */
    {
      retVal = E_OK;
    }
    else
    {
      retVal = COM_SERVICE_NOT_AVAILABLE;
    }
#else
    errorId = COM_E_PARAM;
#endif
  }

/* ----- Development Error Report --------------------------------------- */
#if (COM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != COM_E_NO_ERROR) /* PRQA S 2991, 2995 */ /* MD_Com_2991, MD_Com_2995 */ /* COV_COM_ONLY_DET_FUNCTIONALITY_PRESENT */
  {
    Com_LMgt_CallDetErrorContinue(COMServiceId_ReceiveSignal, errorId);
  }
#endif

  COM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(SignalId);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(SignalDataPtr);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return retVal;
}       /* PRQA S 6080 */ /* MD_MSR_STMIF */


#if (COM_TRANSPORT_PROTOCOL == STD_ON)
/**********************************************************************************************************************
  Com_ReceiveDynSignal
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(uint8, COM_CODE) Com_ReceiveDynSignal(Com_SignalIdType SignalId, P2VAR(void, AUTOMATIC, COM_APPL_VAR) SignalDataPtr, P2VAR(uint16, AUTOMATIC, COM_APPL_VAR) Length)        /* PRQA S 3673 */ /* MD_MSR_Rule8.13 */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = COM_E_NO_ERROR;       /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 retVal = COM_SERVICE_NOT_AVAILABLE;     /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check if component is initialized */
  if(!Com_IsInitialized())
  {
    errorId = COM_E_UNINIT;
  }
  /* #20 Check plausibility of input parameters */
# if (COM_DEV_ERROR_DETECT == STD_ON )
#  if (COM_RXACCESSINFO == STD_ON)
  else if(SignalId >= Com_GetSizeOfRxAccessInfo())
  {
    errorId = COM_E_PARAM;
  }
#   if (COM_INVALIDHNDOFRXACCESSINFO == STD_ON)
  else if(Com_IsInvalidHndOfRxAccessInfo(SignalId))
  {
    errorId = COM_E_PARAM;
  }
#   endif
#   if (COM_EXISTS_NORMAL_TYPEOFRXPDUINFO == STD_ON)
  else if(Com_GetTypeOfRxPduInfo(Com_GetRxPduInfoIdxOfRxAccessInfo(SignalId)) == COM_NORMAL_TYPEOFRXPDUINFO)
  {
    errorId = COM_E_PARAM;
  }
#   endif
#   if (COM_EXISTS_UINT8_DYN_APPLTYPEOFRXACCESSINFO == STD_ON)
  else if(Com_GetApplTypeOfRxAccessInfo(SignalId) != COM_UINT8_DYN_APPLTYPEOFRXACCESSINFO)      /* COV_COM_UINT8_DYN_APPLTYPE */
  {
    errorId = COM_E_PARAM;
  }
#   endif
#  endif
  else if(SignalDataPtr == NULL_PTR)
  {
    errorId = COM_E_PARAM_POINTER;
  }
  else if(Length == NULL_PTR)   /* COV_COM_NO_DYNSIG_CONFIGURED */
  {
    errorId = COM_E_PARAM_POINTER;
  }
# endif
  else
  {
    /* ----- Implementation ----------------------------------------------- */
# if ((COM_RXTPINFOUSEDOFRXPDUINFO == STD_ON) && (COM_EXISTS_UINT8_DYN_APPLTYPEOFRXACCESSINFO == STD_ON))
    Com_RxPduInfoIdxOfRxAccessInfoType ComPduId = Com_GetRxPduInfoIdxOfRxAccessInfo(SignalId);
    /* #30 If the dynamic ComSignal fits into the passed buffer */

    Com_RxTpInfoIdxOfRxPduInfoType rxTpPduInfoIdx = Com_GetRxTpInfoIdxOfRxPduInfo(ComPduId);
    PduLengthType dynSignalLength = Com_GetRxDynSignalLength(rxTpPduInfoIdx);
    if(*Length >= dynSignalLength)
    {
      /* #40 Copy the dynamic ComSignal value to the passed signal data location and set the passed Length pointer to the current dynamic ComSignal length */
      SchM_Enter_Com_COM_EXCLUSIVE_AREA_RX();
      VStdMemCpyRamToRam((P2VAR(uint8, AUTOMATIC, COM_APPL_VAR)) SignalDataPtr, Com_GetAddrRxSigBufferArrayBased(Com_GetRxSigBufferArrayBasedBufferStartIdxOfRxAccessInfo(SignalId)), dynSignalLength); /* PRQA S 0315, 0316 */ /* MD_MSR_VStdLibCopy, MD_Com_0316_0317 */ /* SBSW_COM_WRITEACCESS_STACKPTR_WITH_LENGTH */
      *Length = (uint16) dynSignalLength;       /* SBSW_COM_PTR_API */
      SchM_Exit_Com_COM_EXCLUSIVE_AREA_RX();
      if(Com_IsRxPduGrpActive(ComPduId))
      {
        retVal = E_OK;
      }
    }
    else
    {
      errorId = COM_E_PARAM;
      *Length = (uint16) dynSignalLength;       /* SBSW_COM_PTR_API */
      retVal = E_NOT_OK;
    }
# else
    errorId = COM_E_PARAM;
# endif
  }

  /* ----- Development Error Report --------------------------------------- */
# if (COM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != COM_E_NO_ERROR) /* COV_COM_NO_DYNSIG_CONFIGURED */ /* PRQA S 2991, 2995 */ /* MD_Com_2991, MD_Com_2995 */
  {
    Com_LMgt_CallDetErrorContinue(COMServiceId_ReceiveDynSignal, errorId);
  }
# endif

  COM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(SignalId);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(SignalDataPtr);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(Length);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return retVal;
}       /* PRQA S 6080, 6030 */ /* MD_MSR_STMIF, MD_MSR_STCYC */
#endif

/**********************************************************************************************************************
Com_SendSignalGroup
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(uint8, COM_CODE) Com_SendSignalGroup(Com_SignalGroupIdType SignalGroupId)  /* PRQA S 1505 */ /* MD_MSR_Rule8.7 */
{
/* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = COM_E_NO_ERROR;       /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 retVal = COM_SERVICE_NOT_AVAILABLE;     /* PRQA S 2981 */ /* MD_MSR_RetVal */

/* ----- Development Error Checks ------------------------------------- */
/* #10 Check if component is initialized */
  if(!Com_IsInitialized())
  {
    errorId = COM_E_UNINIT;
  }
#if (COM_DEV_ERROR_DETECT == STD_ON )   /* COV_COM_VAR_ELISA_STD_ON_TX */
/* #20 Check plausibility of input parameters */
# if (COM_TXSIGGRPINFO == STD_ON)
  else if(SignalGroupId >= Com_GetSizeOfTxSigGrpInfo()) /* COV_COM_ONLY_DET_FUNCTIONALITY_PRESENT */
  {
    errorId = COM_E_PARAM;
  }
#  if (COM_INVALIDHNDOFTXSIGGRPINFO == STD_ON)
  else if(Com_IsInvalidHndOfTxSigGrpInfo(SignalGroupId))
  {
    errorId = COM_E_PARAM;
  }
#  endif
#  if (COM_ARRAYACCESSUSEDOFTXSIGGRPINFO == STD_ON)
  else if(Com_IsArrayAccessUsedOfTxSigGrpInfo(SignalGroupId))
  {
    errorId = COM_E_PARAM;
  }
#  endif
# endif
#endif
  else
  {
    /* ----- Implementation ----------------------------------------------- */
#if (COM_TXSIGGRPINFO == STD_ON)
    P2CONST(uint8, AUTOMATIC, COM_APPL_VAR) shdBuffer = NULL_PTR;
# if (COM_TXBUFFERUSEDOFTXSIGGRPINFO == STD_ON)
    /* #30 If the ComSignalGroup has a shadow buffer, get the address of this shadow buffer */
    if(Com_IsTxBufferUsedOfTxSigGrpInfo(SignalGroupId)) /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
    {
      shdBuffer = Com_GetAddrTxBuffer(Com_GetTxBufferStartIdxOfTxSigGrpInfo(SignalGroupId));
    }
# endif
    SchM_Enter_Com_COM_EXCLUSIVE_AREA_TX();
    /* #40 Process the passed ComSignalGroup */
    retVal = Com_SendSignalGroup_Processing(SignalGroupId, shdBuffer);  /* SBSW_COM_FCTCALL_WITH_P2CONST */
    SchM_Exit_Com_COM_EXCLUSIVE_AREA_TX();
#else
    errorId = COM_E_PARAM;
#endif
  }

/* ----- Development Error Report --------------------------------------- */
#if (COM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != COM_E_NO_ERROR) /* PRQA S 2991, 2995 */ /* MD_Com_2991, MD_Com_2995 */ /* COV_COM_ONLY_DET_FUNCTIONALITY_PRESENT */
  {
    Com_LMgt_CallDetErrorContinue(COMServiceId_SendSignalGroup, errorId);
  }
#endif

  COM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(SignalGroupId);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return retVal;
}

#if (COM_ENABLE_SIGNAL_GROUP_ARRAY_API == STD_ON)
/**********************************************************************************************************************
  Com_SendSignalGroupArray
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(uint8, COM_CODE) Com_SendSignalGroupArray(Com_SignalGroupIdType SignalGroupId, P2CONST(uint8, AUTOMATIC, COM_APPL_VAR) SignalGroupArrayPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = COM_E_NO_ERROR;       /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 retVal = COM_SERVICE_NOT_AVAILABLE;     /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check if component is initialized */
  if(!Com_IsInitialized())
  {
    errorId = COM_E_UNINIT;
  }
# if (COM_DEV_ERROR_DETECT == STD_ON )  /* COV_COM_VAR_ELISA_STD_ON_TX */
  /* #20 Check plausibility of input parameters */
#  if (COM_TXSIGGRPINFO == STD_ON)
  else if(SignalGroupId >= Com_GetSizeOfTxSigGrpInfo())
  {
    errorId = COM_E_PARAM;
  }
#   if(COM_INVALIDHNDOFTXSIGGRPINFO == STD_ON)
  else if(Com_IsInvalidHndOfTxSigGrpInfo(SignalGroupId))
  {
    errorId = COM_E_PARAM;
  }
#   endif
#   if (COM_ARRAYACCESSUSEDOFTXSIGGRPINFO == STD_ON)
  else if(!Com_IsArrayAccessUsedOfTxSigGrpInfo(SignalGroupId))  /* COV_COM_ONLY_ARRAYBASED_TX_SIGGRP */
  {
    errorId = COM_E_PARAM;
  }
#   endif
#  endif
  else if(SignalGroupArrayPtr == NULL_PTR)      /* COV_COM_ONLY_DET_FUNCTIONALITY_PRESENT */
  {
    errorId = COM_E_PARAM_POINTER;
  }
# endif
  else
  {
    /* ----- Implementation ----------------------------------------------- */
# if(COM_ARRAYACCESSUSEDOFTXSIGGRPINFO == STD_ON)
    SchM_Enter_Com_COM_EXCLUSIVE_AREA_TX();

    retVal = Com_SendSignalGroupArray_Processing(SignalGroupId, SignalGroupArrayPtr);   /* SBSW_COM_VALID_PTR_ENSURED_BY_CALLING_FUNC */

    SchM_Exit_Com_COM_EXCLUSIVE_AREA_TX();
# else
    errorId = COM_E_PARAM;
# endif
  }

  /* ----- Development Error Report --------------------------------------- */
# if (COM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != COM_E_NO_ERROR) /* PRQA S 2991, 2995 */ /* MD_Com_2991, MD_Com_2995 */ /* COV_COM_ONLY_DET_FUNCTIONALITY_PRESENT */
  {
    Com_LMgt_CallDetErrorContinue(COMServiceId_SendSignalGroupArray, errorId);
  }
# endif

  COM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(SignalGroupId);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(SignalGroupArrayPtr);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return retVal;
}       /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

/**********************************************************************************************************************
Com_InvalidateSignal
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(uint8, COM_CODE) Com_InvalidateSignal(Com_SignalIdType SignalId)
{
/* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = COM_E_NO_ERROR;       /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 retVal = COM_SERVICE_NOT_AVAILABLE;     /* PRQA S 2981 */ /* MD_MSR_RetVal */

/* ----- Development Error Checks ------------------------------------- */
/* #10 Check if component is initialized */
  if(!Com_IsInitialized())
  {
    errorId = COM_E_UNINIT;
  }
#if (COM_DEV_ERROR_DETECT == STD_ON )   /* COV_COM_VAR_ELISA_STD_ON_TX */
/* #20 Check plausibility of input parameters */
# if (COM_TXSIGINFO == STD_ON )
  else if(SignalId >= Com_GetSizeOfTxSigInfo()) /* COV_COM_ONLY_DET_FUNCTIONALITY_PRESENT */
  {
    errorId = COM_E_PARAM;
  }
#  if (COM_INVALIDHNDOFTXSIGINFO == STD_ON)
  else if(Com_IsInvalidHndOfTxSigInfo(SignalId))        /* COV_COM_ONLY_DET_FUNCTIONALITY_PRESENT */
  {
    errorId = COM_E_PARAM;
  }
#  endif
# endif
#endif
  else
  {
#if (COM_INVVALUEUSEDOFTXSIGINFO == STD_ON)
    SchM_Enter_Com_COM_EXCLUSIVE_AREA_TX();
    /* ----- Implementation ----------------------------------------------- */
    /* #30 If the passed ComSignal has an configured invalid value, set the value of the passed ComSignal to the invalid value */
    retVal = Com_InvalidateSignal_SendSignal((Com_TxSigInfoIterType) SignalId);
    SchM_Exit_Com_COM_EXCLUSIVE_AREA_TX();
#else
    errorId = COM_E_PARAM;
#endif
  }

/* ----- Development Error Report --------------------------------------- */
#if (COM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != COM_E_NO_ERROR) /* PRQA S 2991, 2995 */ /* MD_Com_2991, MD_Com_2995 */ /* COV_COM_ONLY_DET_FUNCTIONALITY_PRESENT */
  {
    Com_LMgt_CallDetErrorContinue(COMServiceId_InvalidateSignal, errorId);
  }
#endif

  COM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(SignalId);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return retVal;
}

/**********************************************************************************************************************
Com_InvalidateSignalGroup
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(uint8, COM_CODE) Com_InvalidateSignalGroup(Com_SignalGroupIdType SignalGroupId)
{
/* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = COM_E_NO_ERROR;       /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 retVal = COM_SERVICE_NOT_AVAILABLE;     /* PRQA S 2981 */ /* MD_MSR_RetVal */

/* ----- Development Error Checks ------------------------------------- */
/* #10 Check if component is initialized */
  if(!Com_IsInitialized())
  {
    errorId = COM_E_UNINIT;
  }
#if (COM_DEV_ERROR_DETECT == STD_ON )   /* COV_COM_VAR_ELISA_STD_ON_TX */
/* #20 Check plausibility of input parameters */
# if (COM_TXSIGGRPINFO == STD_ON )
  else if(SignalGroupId >= Com_GetSizeOfTxSigGrpInfo()) /* COV_COM_ONLY_DET_FUNCTIONALITY_PRESENT */
  {
    errorId = COM_E_PARAM;
  }
#  if (COM_INVALIDHNDOFTXSIGGRPINFO == STD_ON)
  else if(Com_IsInvalidHndOfTxSigGrpInfo(SignalGroupId))        /* COV_COM_ONLY_DET_FUNCTIONALITY_PRESENT */
  {
    errorId = COM_E_PARAM;
  }
#  endif
# endif
#endif
  else
  {
#if (COM_TXSIGINFOINVVALUEINDENDIDXOFTXSIGGRPINFO == STD_ON )
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Iterate overall ComGroupSignal of the passed ComSignalGroup and set the ComGroupSignal value to the invalid value */
    Com_TxSigInfoInvValueIndEndIdxOfTxSigGrpInfoType idxTxSigInfoInvValueInd = Com_GetTxSigInfoInvValueIndStartIdxOfTxSigGrpInfo(SignalGroupId);
    for(; idxTxSigInfoInvValueInd < Com_GetTxSigInfoInvValueIndEndIdxOfTxSigGrpInfo(SignalGroupId); idxTxSigInfoInvValueInd++)
    {
      Com_TxSigInfoIterType idxTxSigInfo = (Com_TxSigInfoIterType) Com_GetTxSigInfoInvValueInd(idxTxSigInfoInvValueInd);

      SchM_Enter_Com_COM_EXCLUSIVE_AREA_TX();

      (void) Com_InvalidateSignal_SendSignal(idxTxSigInfo);

      SchM_Exit_Com_COM_EXCLUSIVE_AREA_TX();
    }
    /* #40 Call Com_SendSignalGroup to copy the invalid values form the shadow buffer to the tx pdu buffer */
    retVal = Com_SendSignalGroup(SignalGroupId);
#else
    errorId = COM_E_PARAM;
#endif
  }

/* ----- Development Error Report --------------------------------------- */
#if (COM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != COM_E_NO_ERROR) /* PRQA S 2991, 2995 */ /* MD_Com_2991, MD_Com_2995 */ /* COV_COM_ONLY_DET_FUNCTIONALITY_PRESENT */
  {
    Com_LMgt_CallDetErrorContinue(COMServiceId_InvalidateSignalGroup, errorId);
  }
#endif

  COM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(SignalGroupId);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return retVal;
}

/**********************************************************************************************************************
Com_ReceiveSignalGroup
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(uint8, COM_CODE) Com_ReceiveSignalGroup(Com_SignalGroupIdType SignalGroupId)
{
/* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = COM_E_NO_ERROR;       /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 retVal = COM_SERVICE_NOT_AVAILABLE;     /* PRQA S 2981 */ /* MD_MSR_RetVal */

/* ----- Development Error Checks ------------------------------------- */
/* #10 Check if component is initialized */
  if(!Com_IsInitialized())
  {
    errorId = COM_E_UNINIT;
  }
#if (COM_DEV_ERROR_DETECT == STD_ON )   /* COV_COM_VAR_ELISA_STD_ON_TX */
/* #20 Check plausibility of input parameters */
# if(COM_RXSIGGRPINFO == STD_ON)
  else if(SignalGroupId >= Com_GetSizeOfRxSigGrpInfo()) /* COV_COM_ONLYARRAYACCESS_PRESENT_01 */
  {
    errorId = COM_E_PARAM;
  }
#  if(COM_INVALIDHNDOFRXSIGGRPINFO == STD_ON)
  else if(Com_IsInvalidHndOfRxSigGrpInfo(SignalGroupId))        /* COV_COM_ONLY_ARRAYBASED_TX_SIGGRP */
  {
    errorId = COM_E_PARAM;
  }
#  endif
#  if (COM_ARRAYACCESSUSEDOFRXSIGGRPINFO == STD_ON)
  else if(Com_IsArrayAccessUsedOfRxSigGrpInfo(SignalGroupId))
  {
    errorId = COM_E_PARAM;
  }
#  endif
# endif
#endif
  else
  {
#if(COM_RXSIGGRPINFO == STD_ON)
    /* ----- Implementation ----------------------------------------------- */
    Com_RxPduInfoIdxOfRxSigGrpInfoType ComPduId = Com_GetRxPduInfoIdxOfRxSigGrpInfo(SignalGroupId);
    retVal = E_OK;

    /* #30 If the related ComIPduGroup is stopped, COM_SERVICE_NOT_AVAILABLE will be returned */
    if(!Com_IsRxPduGrpActive(ComPduId)) /* COV_COM_ONLYARRAYACCESS_PRESENT */
    {
      retVal = COM_SERVICE_NOT_AVAILABLE;
    }

# if (COM_SHDBUFFERREQUIREDOFRXSIGGRPINFO == STD_ON)
    SchM_Enter_Com_COM_EXCLUSIVE_AREA_RX();
    /* #40 Read the Rx ComSignalGroup data */
    {
      Com_ReadSignalGroupData(SignalGroupId);
    }
    SchM_Exit_Com_COM_EXCLUSIVE_AREA_RX();
# endif
#else
    errorId = COM_E_PARAM;
#endif
  }
/* ----- Development Error Report --------------------------------------- */
#if (COM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != COM_E_NO_ERROR) /* PRQA S 2991, 2995 */ /* MD_Com_2991, MD_Com_2995 */ /* COV_COM_ONLY_DET_FUNCTIONALITY_PRESENT */
  {
    Com_LMgt_CallDetErrorContinue(COMServiceId_ReceiveSignalGroup, errorId);
  }
#endif

  COM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(SignalGroupId);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return retVal;
}       /* PRQA S 6080 */ /* MD_MSR_STMIF */

#if (COM_ENABLE_SIGNAL_GROUP_ARRAY_API == STD_ON)
/**********************************************************************************************************************
  Com_ReceiveSignalGroupArray
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(uint8, COM_CODE) Com_ReceiveSignalGroupArray(Com_SignalGroupIdType SignalGroupId, P2VAR(uint8, AUTOMATIC, COM_APPL_VAR) SignalGroupArrayPtr)       /* PRQA S 3673 */ /* MD_MSR_Rule8.13 */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = COM_E_NO_ERROR;       /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 retVal = COM_SERVICE_NOT_AVAILABLE;     /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check if component is initialized */
  if(!Com_IsInitialized())
  {
    errorId = COM_E_UNINIT;
  }
# if (COM_DEV_ERROR_DETECT == STD_ON )  /* COV_COM_VAR_ELISA_STD_ON_TX */
  /* #20 Check plausibility of input parameters */
#  if(COM_RXSIGGRPINFO == STD_ON)
  else if(SignalGroupId >= Com_GetSizeOfRxSigGrpInfo())
  {
    errorId = COM_E_PARAM;
  }
#   if(COM_INVALIDHNDOFRXSIGGRPINFO == STD_ON)
  else if(Com_IsInvalidHndOfRxSigGrpInfo(SignalGroupId))
  {
    errorId = COM_E_PARAM;
  }
#   endif
#   if (COM_ARRAYACCESSUSEDOFRXSIGGRPINFO == STD_ON)
  else if(!Com_IsArrayAccessUsedOfRxSigGrpInfo(SignalGroupId))  /* COV_COM_ONLY_ARRAYBASED_RX_SIGGRP */
  {
    errorId = COM_E_PARAM;
  }
#   endif
#  endif
  else if(SignalGroupArrayPtr == NULL_PTR)      /* COV_COM_ONLY_DET_FUNCTIONALITY_PRESENT */
  {
    errorId = COM_E_PARAM_POINTER;
  }
# endif
  else
  {
    /* ----- Implementation ----------------------------------------------- */
# if(COM_ARRAYACCESSUSEDOFRXSIGGRPINFO == STD_ON)
    /* #30 Initiate the reception of the signal group array */
    Com_RxPduInfoIdxOfRxSigGrpInfoType ComPduId = Com_GetRxPduInfoIdxOfRxSigGrpInfo(SignalGroupId);
    Com_RxSigArrayAccessSigGrpBufferIterType idxShdBufferIdx = Com_GetRxSigArrayAccessSigGrpBufferStartIdxOfRxSigGrpInfo(SignalGroupId);

    /* #40 If the belonging RxPduGroup is active, set the return value to E_OK */
    if(Com_IsRxPduGrpActive(ComPduId))
    {
      retVal = E_OK;
    }
    /* #50 Enter exclusive area */
    SchM_Enter_Com_COM_EXCLUSIVE_AREA_RX();
    {
      /* #60 copy data from shadow buffer to the signal group array */
      VStdMemCpyRamToRam(SignalGroupArrayPtr, Com_GetAddrRxSigArrayAccessSigGrpBuffer(idxShdBufferIdx), Com_GetRxSigArrayAccessSigGrpBufferLengthOfRxSigGrpInfo(SignalGroupId));        /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_COM_CSL01 */
    }
    /* #70 Exit exclusive area */
    SchM_Exit_Com_COM_EXCLUSIVE_AREA_RX();
# else
    errorId = COM_E_PARAM;
# endif
  }

  /* ----- Development Error Report --------------------------------------- */
# if (COM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != COM_E_NO_ERROR) /* PRQA S 2991, 2995 */ /* MD_Com_2991, MD_Com_2995 */ /* COV_COM_ONLY_DET_FUNCTIONALITY_PRESENT */
  {
    Com_LMgt_CallDetErrorContinue(COMServiceId_ReceiveSignalGroupArray, errorId);
  }
# endif

  COM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(SignalGroupId);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(SignalGroupArrayPtr);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return retVal;
}       /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if (COM_TRANSPORT_PROTOCOL == STD_ON)
/**********************************************************************************************************************
  Com_SendDynSignal
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 **********************************************************************************************************************/
FUNC(uint8, COM_CODE) Com_SendDynSignal(Com_SignalIdType SignalId, P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr, uint16 Length)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = COM_E_NO_ERROR;       /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 retVal = COM_SERVICE_NOT_AVAILABLE;     /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check if component is initialized */
  if(!Com_IsInitialized())
  {
    errorId = COM_E_UNINIT;
  }
# if (COM_DEV_ERROR_DETECT == STD_ON)
  /* #20 Check plausibility of input parameters */
#  if (COM_TXSIGINFO == STD_ON)
  else if(SignalId >= Com_GetSizeOfTxSigInfo())
  {
    errorId = COM_E_PARAM;
  }
#   if (COM_INVALIDHNDOFTXSIGINFO == STD_ON)
  else if(Com_IsInvalidHndOfTxSigInfo(SignalId))
  {
    errorId = COM_E_PARAM;
  }
#   endif
#   if (COM_TXTPINFOUSEDOFTXPDUINFO == STD_ON)
  else if(!Com_IsTxTpInfoUsedOfTxPduInfo(Com_GetTxPduInfoIdxOfTxSigInfo(SignalId)))     /* COV_COM_TP_ONLY */
  {
    errorId = COM_E_PARAM;
  }
#   endif
#   if (COM_EXISTS_UINT8_DYN_APPLTYPEOFTXSIGINFO == STD_ON)
  else if(Com_GetApplTypeOfTxSigInfo(SignalId) != COM_UINT8_DYN_APPLTYPEOFTXSIGINFO)    /* PRQA S 2992, 2996 */ /* MD_Com_2992, MD_Com_2996 */ /* COV_COM_UINT8_DYN_APPLTYPE */
  {
    errorId = COM_E_PARAM;      /* PRQA S 2880 */ /* MD_MSR_Unreachable */
  }
  else if(Length > Com_GetByteLengthOfTxSigInfo(SignalId))
  {
    errorId = COM_E_PARAM;
  }
#   endif
#  endif
  else if(SignalDataPtr == NULL_PTR)
  {
    errorId = COM_E_PARAM_POINTER;
  }
# endif
  else
  {
    /* ----- Implementation ----------------------------------------------- */
# if (COM_EXISTS_UINT8_DYN_APPLTYPEOFTXSIGINFO == STD_ON)
    SchM_Enter_Com_COM_EXCLUSIVE_AREA_TX();
    /* #30 Process the passed Tx ComSignal */
    retVal = Com_SendSignal_Processing((Com_TxSigInfoIterType) SignalId, SignalDataPtr, Length);        /* SBSW_COM_FCTCALL_WITH_P2CONST */
    SchM_Exit_Com_COM_EXCLUSIVE_AREA_TX();
# else
    errorId = COM_E_PARAM;
# endif
  }

  /* ----- Development Error Report --------------------------------------- */
# if (COM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != COM_E_NO_ERROR) /* PRQA S 2991, 2995 */ /* MD_Com_2991, MD_Com_2995 */ /* COV_COM_ONLY_DET_FUNCTIONALITY_PRESENT */
  {
    Com_LMgt_CallDetErrorContinue(COMServiceId_SendDynSignal, errorId);
  }
# endif

  COM_DUMMY_STATEMENT(Length);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(SignalId);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(SignalDataPtr);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return retVal;
}       /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

/**********************************************************************************************************************
Com_SendSignal
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(uint8, COM_CODE) Com_SendSignal(Com_SignalIdType SignalId, P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr)
{
/* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = COM_E_NO_ERROR;       /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 retVal = COM_SERVICE_NOT_AVAILABLE;     /* PRQA S 2981 */ /* MD_MSR_RetVal */

/* ----- Development Error Checks ------------------------------------- */
/* #10 Check if component is initialized */
  if(!Com_IsInitialized())
  {
    errorId = COM_E_UNINIT;
  }
#if (COM_DEV_ERROR_DETECT == STD_ON)    /* COV_COM_VAR_ELISA_STD_ON_TX */
/* #20 Check plausibility of input parameters */
# if (COM_TXSIGINFO == STD_ON)
  else if(SignalId >= Com_GetSizeOfTxSigInfo())
  {
    errorId = COM_E_PARAM;
  }
#  if (COM_INVALIDHNDOFTXSIGINFO == STD_ON)
  else if(Com_IsInvalidHndOfTxSigInfo(SignalId))
  {
    errorId = COM_E_PARAM;
  }
#  endif
# endif
  else if(SignalDataPtr == NULL_PTR)    /* COV_COM_UINT8_DYN_APPLTYPE */
  {
    errorId = COM_E_PARAM_POINTER;
  }
#endif
  else
  {
    /* ----- Implementation ----------------------------------------------- */
#if (COM_TXSIGINFO == STD_ON)
    SchM_Enter_Com_COM_EXCLUSIVE_AREA_TX();
    /* #30 Process the passed Tx ComSignal */
    retVal = Com_SendSignal_Processing((Com_TxSigInfoIterType) SignalId, SignalDataPtr, 0);     /* SBSW_COM_FCTCALL_WITH_P2CONST */
    SchM_Exit_Com_COM_EXCLUSIVE_AREA_TX();
#else
    errorId = COM_E_PARAM;
#endif
  }

/* ----- Development Error Report --------------------------------------- */
#if (COM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != COM_E_NO_ERROR) /* PRQA S 2991, 2995 */ /* MD_Com_2991, MD_Com_2995 */ /* COV_COM_ONLY_DET_FUNCTIONALITY_PRESENT */
  {
    Com_LMgt_CallDetErrorContinue(COMServiceId_SendSignal, errorId);
  }
#endif

  COM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(SignalId);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(SignalDataPtr);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return retVal;
}       /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
Com_TriggerIPDUSend
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TriggerIPDUSend(PduIdType PduId)
{
/* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = COM_E_NO_ERROR;       /* PRQA S 2981 */ /* MD_MSR_RetVal */

/* ----- Development Error Checks ------------------------------------- */
/* #10 Check if component is initialized */
  if(!Com_IsInitialized())
  {
    errorId = COM_E_UNINIT;
  }
#if (COM_DEV_ERROR_DETECT == STD_ON )   /* COV_COM_VAR_ELISA_STD_ON_TX */
/* #20 Check plausibility of input parameters */
# if (COM_TXPDUINFO == STD_ON)
  else if(PduId >= Com_GetSizeOfTxPduInfo())
  {
    errorId = COM_E_PARAM;
  }
#  if (COM_INVALIDHNDOFTXPDUINFO == STD_ON)
  else if(Com_IsInvalidHndOfTxPduInfo(PduId))
  {
    errorId = COM_E_PARAM;
  }
#  endif
# endif
#endif
  else
  {
    /* ----- Implementation ----------------------------------------------- */
#if (COM_TXPDUINFO == STD_ON)
# if (COM_TXTPINFOUSEDOFTXPDUINFO)
    if((!Com_IsTxTpInfoUsedOfTxPduInfo(PduId)) || (Com_GetTxTpConnectionState(Com_GetTxTpInfoIdxOfTxPduInfo(PduId)) == COM_READY_TXTPCONNECTIONSTATE))  /* COV_COM_TP_ONLY */
# endif
    {
      /* #30 Set the deferred transmit flag to initiate a transmission within the Com_MainFunctionTx */
      Com_TxModeHdlr_TriggerIpduSendOnceDeferred(PduId);
    }
#else
    errorId = COM_E_PARAM;
#endif
  }

/* ----- Development Error Report --------------------------------------- */
#if (COM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != COM_E_NO_ERROR) /* PRQA S 2991, 2995 */ /* MD_Com_2991, MD_Com_2995 */ /* COV_COM_ONLY_DET_FUNCTIONALITY_PRESENT */
  {
    Com_LMgt_CallDetErrorContinue(COMServiceId_TriggerIPDUSend, errorId);
  }
#endif

  COM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(PduId);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}

#if (COM_TRIGGER_IPDU_SEND_WITH_META_DATA_API == STD_ON)
/**********************************************************************************************************************
Com_TriggerIPDUSendWithMetaData
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TriggerIPDUSendWithMetaData(PduIdType PduId, P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) MetaData)
{
/* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = COM_E_NO_ERROR;       /* PRQA S 2981 */ /* MD_MSR_RetVal */

/* ----- Development Error Checks ------------------------------------- */
/* #10 Check if component is initialized */
  if(!Com_IsInitialized())
  {
    errorId = COM_E_UNINIT;
  }
# if (COM_DEV_ERROR_DETECT == STD_ON )
/* #20 Check plausibility of input parameters */
#  if (COM_TXPDUINFO == STD_ON)
  else if(PduId >= Com_GetSizeOfTxPduInfo())
  {
    errorId = COM_E_PARAM;
  }
#   if (COM_INVALIDHNDOFTXPDUINFO == STD_ON)
  else if(Com_IsInvalidHndOfTxPduInfo(PduId))
  {
    errorId = COM_E_PARAM;
  }
#   endif
#   if (COM_TXBUFFERMETADATAUSEDOFTXPDUINFO == STD_ON)
  else if(!Com_IsTxBufferMetaDataUsedOfTxPduInfo(PduId))
  {
    errorId = COM_E_PARAM;
  }
#   endif
#  endif
  else if(MetaData == NULL_PTR)
  {
    errorId = COM_E_PARAM_POINTER;
  }
# endif
  else
  {
    /* ----- Implementation ----------------------------------------------- */
# if (COM_TXBUFFERMETADATAUSEDOFTXPDUINFO == STD_ON)
    SchM_Enter_Com_COM_EXCLUSIVE_AREA_TX();
#  if (COM_TXTPINFOUSEDOFTXPDUINFO)
    if((!Com_IsTxTpInfoUsedOfTxPduInfo(PduId)) || (Com_GetTxTpConnectionState(Com_GetTxTpInfoIdxOfTxPduInfo(PduId)) == COM_READY_TXTPCONNECTIONSTATE))  /* COV_COM_TP_ONLY */
#  endif
    {
      /* #30 Copy the passed meta data to the Tx ComIPdu buffer and trigger a deferred transmission */
      VStdLib_MemCpy(Com_GetAddrTxBuffer(Com_GetTxBufferMetaDataStartIdxOfTxPduInfo(PduId)), MetaData, Com_GetMetaDataLengthOfTxPduInfo(PduId));        /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_COM_CSL03 */
      Com_TxModeHdlr_TriggerIpduSendOnceDeferred(PduId);
    }
    SchM_Exit_Com_COM_EXCLUSIVE_AREA_TX();
# else
    errorId = COM_E_PARAM;
# endif
  }

/* ----- Development Error Report --------------------------------------- */
# if (COM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != COM_E_NO_ERROR) /* COV_COM_NO_METADATA_CONFIGURED */ /* PRQA S 2991, 2995 */ /* MD_Com_2991, MD_Com_2995 */
  {
    Com_LMgt_CallDetErrorContinue(COMServiceId_TriggerIPDUSendWithMetaData, errorId);
  }
# endif

  COM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(PduId);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(MetaData);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}       /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if (COM_COMMUNICATION_INTERFACE == STD_ON)
/**********************************************************************************************************************
  Com_RxIndication
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_RxIndication(PduIdType RxPduId, P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = COM_E_NO_ERROR;       /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */

  /* #10 Check if component is initialized */
  if(!Com_IsInitialized())
  {
    errorId = COM_E_UNINIT;
  }
# if (COM_DEV_ERROR_DETECT == STD_ON )  /* COV_COM_VAR_ELISA_STD_ON_TX */
  /* #20 Check plausibility of input parameters */
#  if (COM_RXPDUINFO == STD_ON)
  else if(RxPduId >= Com_GetSizeOfRxPduInfo())
  {
    errorId = COM_E_PARAM;
  }
#   if(COM_INVALIDHNDOFRXPDUINFO == STD_ON)
  else if(Com_IsInvalidHndOfRxPduInfo(RxPduId))
  {
    errorId = COM_E_PARAM;
  }
#   endif
#  endif
  else if(PduInfoPtr == NULL_PTR)
  {
    errorId = COM_E_PARAM_POINTER;
  }
#  if (COM_METADATALENGTHOFRXPDUINFO == STD_ON)
  else if((Com_GetMetaDataLengthOfRxPduInfo(RxPduId) > 0u) && (PduInfoPtr->SduDataPtr == NULL_PTR))
  {
    errorId = COM_E_PARAM_POINTER;
  }
  else if((Com_GetMetaDataLengthOfRxPduInfo(RxPduId) > 0u) && (PduInfoPtr->SduLength < Com_GetMetaDataLengthOfRxPduInfo(RxPduId)))
  {
    errorId = COM_E_PARAM_POINTER;
  }
  else if(!(Com_GetMetaDataLengthOfRxPduInfo(RxPduId) > 0u) && (PduInfoPtr->SduDataPtr == NULL_PTR) && (PduInfoPtr->SduLength > 0u))
  {
    errorId = COM_E_PARAM_POINTER;
  }
#  else
  else if((PduInfoPtr->SduDataPtr == NULL_PTR) && (PduInfoPtr->SduLength > 0u))
  {
    errorId = COM_E_PARAM_POINTER;
  }
#  endif
# endif
  else
  {
# if (COM_RXPDUINFO == STD_ON)
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Do Rx Indication processing */
    (void) Com_RxIndication_Processing(RxPduId, PduInfoPtr);    /* SBSW_COM_FCTCALL_WITH_P2CONST */
# else
    errorId = COM_E_PARAM;
# endif
  }

  /* ----- Development Error Report --------------------------------------- */
# if (COM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != COM_E_NO_ERROR) /* PRQA S 2991, 2995 */ /* MD_Com_2991, MD_Com_2995 */ /* COV_COM_ONLY_DET_FUNCTIONALITY_PRESENT */
  {
    Com_LMgt_CallDetErrorContinue(COMServiceId_RxIndication, errorId);
  }
# endif

  COM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(RxPduId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT_CONST(PduInfoPtr);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}       /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if (COM_TRANSPORT_PROTOCOL == STD_ON)
/**********************************************************************************************************************
  Com_StartOfReception
**********************************************************************************************************************/
/*!  * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(BufReq_ReturnType, COM_CODE) Com_StartOfReception(PduIdType ComRxPduId, P2VAR(PduInfoType, AUTOMATIC, COM_APPL_VAR) TpSduInfoPtr, PduLengthType TpSduLength, P2VAR(PduLengthType, AUTOMATIC, COM_APPL_VAR) RxBufferSizePtr)        /* PRQA S 3673 */ /* MD_MSR_Rule8.13 */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = COM_E_NO_ERROR;       /* PRQA S 2981 */ /* MD_MSR_RetVal */
  BufReq_ReturnType bufReq_status = BUFREQ_E_NOT_OK;    /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */

  /* #10 Check if component is initialized */
  if(!Com_IsInitialized())
  {
    errorId = COM_E_UNINIT;
  }
# if (COM_DEV_ERROR_DETECT == STD_ON )
  /* #20 Check plausibility of input parameters */
#  if (COM_RXPDUINFO == STD_ON)
  else if(ComRxPduId >= Com_GetSizeOfRxPduInfo())
  {
    errorId = COM_E_PARAM;
  }
#   if (COM_INVALIDHNDOFRXPDUINFO == STD_ON)
  else if(Com_IsInvalidHndOfRxPduInfo(ComRxPduId))
  {
    errorId = COM_E_PARAM;
  }
#   endif
#   if (COM_EXISTS_NORMAL_TYPEOFRXPDUINFO == STD_ON)
  else if(Com_GetTypeOfRxPduInfo(ComRxPduId) == COM_NORMAL_TYPEOFRXPDUINFO)     /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    errorId = COM_E_PARAM;
  }
#   endif
#  endif
#  if (COM_RXTPBUFFERMETADATAUSEDOFRXTPINFO == STD_ON)
  else if(Com_IsRxTpBufferMetaDataUsedOfRxTpInfo(Com_GetRxTpInfoIdxOfRxPduInfo(ComRxPduId)) && (TpSduInfoPtr == NULL_PTR))
  {
    errorId = COM_E_PARAM_POINTER;
  }
  else if(Com_IsRxTpBufferMetaDataUsedOfRxTpInfo(Com_GetRxTpInfoIdxOfRxPduInfo(ComRxPduId)) && (TpSduInfoPtr->SduDataPtr == NULL_PTR))  /* PRQA S 2812 */ /* MD_Com_2812 */
  {
    errorId = COM_E_PARAM_POINTER;
  }
  else if(Com_IsRxTpBufferMetaDataUsedOfRxTpInfo(Com_GetRxTpInfoIdxOfRxPduInfo(ComRxPduId)) && (TpSduInfoPtr->SduLength < Com_GetRxTpBufferMetaDataLengthOfRxTpInfo(Com_GetRxTpInfoIdxOfRxPduInfo(ComRxPduId))))        /* PRQA S 2812 */ /* MD_Com_2812 */
  {
    errorId = COM_E_PARAM_POINTER;
  }
#  endif
  else if(RxBufferSizePtr == NULL_PTR)
  {
    errorId = COM_E_PARAM_POINTER;
  }
# endif
  else
  {
# if (COM_RXTPINFOUSEDOFRXPDUINFO == STD_ON)
    if(Com_IsRxPduGrpActive(ComRxPduId))        /* \trace SPEC-2736846 */
    {
      /* ----- Implementation ----------------------------------------------- */
      Com_RxTpInfoIdxOfRxPduInfoType rxTpPduInfoIdx = Com_GetRxTpInfoIdxOfRxPduInfo(ComRxPduId);

      switch (Com_GetRxTpConnectionState(rxTpPduInfoIdx))
      {
          /* #30 If Com is ready for new TP connection */
        case COM_READY_RXTPCONNECTIONSTATE:
        {
          PduLengthType requiredBytes = TpSduLength;
          /* #40 If the passed TpSduLength + MetaDataLength fits into the current available buffer */
#  if (COM_RXTPBUFFERMETADATAUSEDOFRXTPINFO == STD_ON)
          if(Com_IsRxTpBufferMetaDataUsedOfRxTpInfo(rxTpPduInfoIdx))
          {
            requiredBytes += (Com_MetaDataLengthOfRxPduInfoType) Com_GetRxTpBufferMetaDataLengthOfRxTpInfo(rxTpPduInfoIdx);
          }
#  endif
          if(requiredBytes <= Com_GetBufferSizeOfRxTpInfo(rxTpPduInfoIdx))
          {
            /* #50 Store the passed TpSduLength, set the passed RxBufferSizePtr to the available buffer size and set the Rx Tp ComIPdu state to RECEPTION_STARTED */
            Com_SetRxTpSduLength(rxTpPduInfoIdx, TpSduLength);  /* SBSW_COM_CSL02 */
            *RxBufferSizePtr = Com_GetBufferSizeOfRxTpInfo(rxTpPduInfoIdx);     /* SBSW_COM_PTR_API */

            if(TpSduLength > 0u)
            {
              Com_SetRxTpConnectionState(rxTpPduInfoIdx, COM_RECEPTION_STARTED_RXTPCONNECTIONSTATE);    /* SBSW_COM_CSL02 */
            }
            else
            {
              Com_SetRxTpConnectionState(rxTpPduInfoIdx, COM_WAITING_FOR_INDICATION_RXTPCONNECTIONSTATE);       /* SBSW_COM_CSL02 */
            }

#  if (COM_RXTPBUFFERMETADATAUSEDOFRXTPINFO == STD_ON)
            /* #60 If meta data is configured, copy the passed meta data to the buffer and set the passed RxBufferSizePtr value to the remaining receive buffer size */
            if(Com_IsRxTpBufferMetaDataUsedOfRxTpInfo(rxTpPduInfoIdx))
            {
              P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) metaDataSourcePtr = &(TpSduInfoPtr->SduDataPtr[TpSduInfoPtr->SduLength - Com_GetRxTpBufferMetaDataLengthOfRxTpInfo(rxTpPduInfoIdx)]);
              VStdMemCpyRamToRam(Com_GetAddrRxTpBuffer(Com_GetRxTpBufferMetaDataStartIdxOfRxTpInfo(rxTpPduInfoIdx)), metaDataSourcePtr, Com_GetRxTpBufferMetaDataLengthOfRxTpInfo(rxTpPduInfoIdx));     /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_COM_WRITEACCESS_STACKPTR_CONFIG_LENGTH */

              *RxBufferSizePtr = Com_GetBufferSizeOfRxTpInfo(rxTpPduInfoIdx) - Com_GetMetaDataLengthOfRxPduInfo(ComRxPduId);    /* SBSW_COM_PTR_API */
            }
#  endif
            bufReq_status = BUFREQ_OK;
          }
          /* #70 Otherwise return BUFREQ_E_OVFL. The bufferSizePtr remains unchanged */
          else
          {
            *RxBufferSizePtr = Com_GetBufferSizeOfRxTpInfo(rxTpPduInfoIdx);     /* SBSW_COM_PTR_API */
            bufReq_status = BUFREQ_E_OVFL;
          }
          break;
        }
          /* #80 Else if Com is waiting for deferred processing, reject connection. */
#  if (COM_EXISTS_DEFERRED_SIGNALPROCESSINGOFRXPDUINFO == STD_ON)
        case COM_BUFFER_LOCKED_RXTPCONNECTIONSTATE:
        {
          /* Buffer stays locked */
          bufReq_status = BUFREQ_E_NOT_OK;      /* PRQA S 2981 */ /* MD_MSR_RetVal */
          break;
        }
#  endif
          /* #90 Else reset TP connection. */
        default:
        {
          SchM_Enter_Com_COM_EXCLUSIVE_AREA_RX();
          Com_ResetRxTpConnection(ComRxPduId);
          SchM_Exit_Com_COM_EXCLUSIVE_AREA_RX();
          break;
        }
      }
    }
# else
    errorId = COM_E_PARAM;
# endif
  }

  /* ----- Development Error Report --------------------------------------- */
# if (COM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != COM_E_NO_ERROR) /* PRQA S 2991, 2995 */ /* MD_Com_2991, MD_Com_2995 */ /* COV_COM_ONLY_DET_FUNCTIONALITY_PRESENT */
  {
    Com_LMgt_CallDetErrorContinue(COMServiceId_StartOfReception, errorId);
  }
# endif

  COM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(ComRxPduId);      /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(TpSduInfoPtr);    /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(TpSduLength);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(RxBufferSizePtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return bufReq_status;
}       /* PRQA S 6080, 6030 */ /* MD_MSR_STMIF, MD_MSR_STCYC */
#endif

#if (COM_TRANSPORT_PROTOCOL == STD_ON)
/**********************************************************************************************************************
  Com_TpRxIndication
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TpRxIndication(PduIdType PduId, Std_ReturnType Result)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = COM_E_NO_ERROR;       /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check if component is initialized */
  if(!Com_IsInitialized())
  {
    errorId = COM_E_UNINIT;
  }
# if (COM_DEV_ERROR_DETECT == STD_ON )
  /* #20 Check plausibility of input parameters */
#  if(COM_RXPDUINFO == STD_ON)
  else if(PduId >= Com_GetSizeOfRxPduInfo())
  {
    errorId = COM_E_PARAM;
  }
#   if (COM_INVALIDHNDOFRXPDUINFO == STD_ON)
  else if(Com_IsInvalidHndOfRxPduInfo(PduId))
  {
    errorId = COM_E_PARAM;
  }
#   endif
#   if (COM_EXISTS_NORMAL_TYPEOFRXPDUINFO == STD_ON)
  else if(Com_GetTypeOfRxPduInfo(PduId) == COM_NORMAL_TYPEOFRXPDUINFO)  /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    errorId = COM_E_PARAM;
  }
#   endif
#  endif
# endif
  else
  {
    /* ----- Implementation ----------------------------------------------- */
# if(COM_RXTPINFOUSEDOFRXPDUINFO == STD_ON)
    /* #30 Process the passed Rx Tp ComIPdu */
    Com_TpRxIndication_Processing(PduId, Result);
# else
    errorId = COM_E_PARAM;
# endif
  }

  /* ----- Development Error Report --------------------------------------- */
# if (COM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != COM_E_NO_ERROR) /* PRQA S 2991, 2995 */ /* MD_Com_2991, MD_Com_2995 */ /* COV_COM_ONLY_DET_FUNCTIONALITY_PRESENT */
  {
    Com_LMgt_CallDetErrorContinue(COMServiceId_TpRxIndication, errorId);
  }
# endif

  COM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(PduId);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(Result);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}
#endif

#if(COM_TRANSPORT_PROTOCOL == STD_ON)
/**********************************************************************************************************************
  Com_TpTxConfirmation
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TpTxConfirmation(PduIdType PduId, Std_ReturnType Result)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = COM_E_NO_ERROR;       /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check if component is initialized */
  if(!Com_IsInitialized())
  {
    errorId = COM_E_UNINIT;
  }
# if (COM_DEV_ERROR_DETECT == STD_ON )
  /* #20 Check plausibility of input parameters */
#  if (COM_TXPDUINFO == STD_ON)
  else if(PduId >= Com_GetSizeOfTxPduInfo())
  {
    errorId = COM_E_PARAM;
  }
#   if (COM_INVALIDHNDOFTXPDUINFO == STD_ON)
  else if(Com_IsInvalidHndOfTxPduInfo(PduId))
  {
    errorId = COM_E_PARAM;
  }
#   endif
#   if (COM_TXTPINFOUSEDOFTXPDUINFO == STD_ON)
  else if(!Com_IsTxTpInfoUsedOfTxPduInfo(PduId))        /* COV_COM_TP_ONLY */
  {
    errorId = COM_E_PARAM;
  }
#   endif
#  endif
# endif
  else
  {
# if (COM_TXTPINFOUSEDOFTXPDUINFO == STD_ON)
    /* ----- Implementation ----------------------------------------------- */
    /* #25 If I-PDU is active */
    if(Com_IsTxPduGrpActive(PduId))
    {
      Com_TxTpInfoIdxOfTxPduInfoType txTpPduInfoIdx = Com_GetTxTpInfoIdxOfTxPduInfo(PduId);

      /* #30 If the passed Result is E_OK and the state is WAITING_FOR_CONFIRMATION or TRANSMISSION_STARTED */
      if((Result == E_OK) && (Com_GetTxTpConnectionState(txTpPduInfoIdx) == COM_WAITING_FOR_CONFIRMATION_TXTPCONNECTIONSTATE))
      {
        /* #40 Call the normal Com_TxConfirmation */
        Com_TxConfirmation_Process(PduId);
      }

      /* #50 Prepare the TP parameters for the start of a new transmission */
      Com_ResetTxTpConnection(PduId);
    }
# else
    errorId = COM_E_PARAM;
# endif
  }

  /* ----- Development Error Report --------------------------------------- */
# if (COM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != COM_E_NO_ERROR) /* PRQA S 2991, 2995 */ /* MD_Com_2991, MD_Com_2995 */ /* COV_COM_ONLY_DET_FUNCTIONALITY_PRESENT */
  {
    Com_LMgt_CallDetErrorContinue(COMServiceId_TpTxConfirmation, errorId);
  }
# endif

  COM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(PduId);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(Result);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}       /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if (COM_TRANSPORT_PROTOCOL == STD_ON)
/**********************************************************************************************************************
  Com_CopyTxData
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(BufReq_ReturnType, COM_CODE) Com_CopyTxData(PduIdType PduId, P2VAR(PduInfoType, AUTOMATIC, COM_APPL_VAR) PduInfoPtr, P2VAR(RetryInfoType, AUTOMATIC, COM_APPL_VAR) RetryInfoPtr, P2VAR(PduLengthType, AUTOMATIC, COM_APPL_VAR) TxDataCntPtr)       /* PRQA S 3673 */ /* MD_MSR_Rule8.13 */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = COM_E_NO_ERROR;       /* PRQA S 2981 */ /* MD_MSR_RetVal */
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;   /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check if component is initialized */
  if(!Com_IsInitialized())
  {
    errorId = COM_E_UNINIT;
  }
# if (COM_DEV_ERROR_DETECT == STD_ON )
  /* #20 Check plausibility of input parameters */
#  if (COM_TXPDUINFO == STD_ON)
  else if(PduId >= Com_GetSizeOfTxPduInfo())
  {
    errorId = COM_E_PARAM;
  }
#   if (COM_INVALIDHNDOFTXPDUINFO == STD_ON)
  else if(Com_IsInvalidHndOfTxPduInfo(PduId))
  {
    errorId = COM_E_PARAM;
  }
#   endif
#   if (COM_TXTPINFOUSEDOFTXPDUINFO == STD_ON)
  else if(!Com_IsTxTpInfoUsedOfTxPduInfo(PduId))        /* COV_COM_TP_ONLY */
  {
    errorId = COM_E_PARAM;
  }
#   endif
#  endif
  else if(PduInfoPtr == NULL_PTR)
  {
    errorId = COM_E_PARAM_POINTER;
  }
  else if((PduInfoPtr->SduDataPtr == NULL_PTR) && (PduInfoPtr->SduLength > 0u))
  {
    errorId = COM_E_PARAM_POINTER;
  }
  else if(TxDataCntPtr == NULL_PTR)
  {
    errorId = COM_E_PARAM_POINTER;
  }
# endif
  else
  {
# if (COM_TXTPINFOUSEDOFTXPDUINFO == STD_ON)
    /* ----- Implementation ----------------------------------------------- */
    /* #25 If I-PDU is active and TpDataState of RetryInfoPtr is not TP_DATARETRY */
    if(Com_IsTxPduGrpActive(PduId))     /* \trace SPEC-2736849 */
    {
      if((RetryInfoPtr == NULL_PTR) || (RetryInfoPtr->TpDataState != TP_DATARETRY))
      {
        Com_TxTpInfoIdxOfTxPduInfoType txTpPduInfoIdx = Com_GetTxTpInfoIdxOfTxPduInfo(PduId);
        /* #30 If TxTpConnectionState is... */
        switch (Com_GetTxTpConnectionState(txTpPduInfoIdx))
        {
            /* #40 ...TRANSMISSION_STARTED, switch to COPYING and Copy Tx Data */
          case COM_TRANSMISSION_STARTED_TXTPCONNECTIONSTATE:
          {
            Com_SetTxTpConnectionState(txTpPduInfoIdx, COM_COPYING_TXTPCONNECTIONSTATE);        /* SBSW_COM_CSL02 */
            /* No break required here. Copying operations shall be performed. */
          }     /* @suppress("No break at end of case") */
            /* #50 ...COPYING */
          case COM_COPYING_TXTPCONNECTIONSTATE:        /* PRQA S 2003 */ /* MD_Com_2003 */
          {
            /* #60 If enough data is present */
            if(PduInfoPtr->SduLength <= (Com_GetTxSduLength(PduId) - Com_GetTxTpWrittenBytesCounter(txTpPduInfoIdx)))
            {
              /* #65 Copy the provided data segment to the Tx PDU buffer and increment the WrittenBytesCouter by the passed SduLength */
              VStdMemCpyRamToRam(PduInfoPtr->SduDataPtr, Com_GetAddrTxBuffer(Com_GetTxBufferStartIdxOfTxTpInfo(txTpPduInfoIdx) + Com_GetTxTpWrittenBytesCounter(txTpPduInfoIdx)), PduInfoPtr->SduLength);       /* PRQA S 0315, 2986 */ /* MD_MSR_VStdLibCopy, MD_Com_2985_2986 */ /* SBSW_COM_MEM_CPY */
              Com_SetTxTpWrittenBytesCounter(txTpPduInfoIdx, (Com_GetTxTpWrittenBytesCounter(txTpPduInfoIdx) + PduInfoPtr->SduLength)); /* SBSW_COM_CSL02 */

              /* #70 Set the passed TxDataCntPtr to number of remaining bytes in the Tx PDU buffer */
              *TxDataCntPtr = (Com_GetTxSduLength(PduId) - Com_GetTxTpWrittenBytesCounter(txTpPduInfoIdx));     /* SBSW_COM_PTR_API */

              /* #80 If all bytes are transmitted set the state to WAITING_FOR_CONFIRMATION */
              if(0u == *TxDataCntPtr)
              {
                Com_SetTxTpConnectionState(txTpPduInfoIdx, COM_WAITING_FOR_CONFIRMATION_TXTPCONNECTIONSTATE);   /* SBSW_COM_CSL02 */
              }
              retVal = BUFREQ_OK;
            }
            /* #90 Otherwise set the passed TxDataCntPtr to number of remaining bytes in the Tx PDU buffer */
            else
            {
              *TxDataCntPtr = (Com_GetTxSduLength(PduId) - Com_GetTxTpWrittenBytesCounter(txTpPduInfoIdx));     /* SBSW_COM_PTR_API */
              retVal = BUFREQ_E_BUSY;
            }
            break;
          }
            /* #100 ...WAITING_FOR_CONFIRMATION and zero-sized segment shall be copy, return E_OK, otherwise reset the connection */
          case COM_WAITING_FOR_CONFIRMATION_TXTPCONNECTIONSTATE:
          {
            if(PduInfoPtr->SduLength == 0u)
            {
              *TxDataCntPtr = 0u;       /* SBSW_COM_PTR_API */
              retVal = BUFREQ_OK;
            }
            else
            {
              Com_ResetTxTpConnection(PduId);
            }
            break;
          }
            /* #110 ...READY, do nothing */
          default:
          {
            /* COM_READY_RXTPCONNECTIONSTATE */
            break;
          }
        }
      }
    }
# else
    errorId = COM_E_PARAM;
# endif
  }

  /* ----- Development Error Report --------------------------------------- */
# if (COM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != COM_E_NO_ERROR) /* PRQA S 2991, 2995 */ /* MD_Com_2991, MD_Com_2995 */ /* COV_COM_ONLY_DET_FUNCTIONALITY_PRESENT */
  {
    Com_LMgt_CallDetErrorContinue(COMServiceId_CopyTxData, errorId);
  }
# endif

  COM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(PduId);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(PduInfoPtr);      /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(RetryInfoPtr);    /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(TxDataCntPtr);    /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return retVal;
}       /* PRQA S 6030, 6080 */ /* MD_MSR_STCYC, MD_MSR_STMIF */
#endif

#if (COM_TRANSPORT_PROTOCOL == STD_ON)
/**********************************************************************************************************************
  Com_CopyRxData
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(BufReq_ReturnType, COM_CODE) Com_CopyRxData(PduIdType PduId, CONSTP2VAR(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPointer, P2VAR(PduLengthType, AUTOMATIC, COM_APPL_VAR) RxBufferSizePtr)      /* PRQA S 3673 */ /* MD_MSR_Rule8.13 */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = COM_E_NO_ERROR;       /* PRQA S 2981 */ /* MD_MSR_RetVal */
  BufReq_ReturnType bufReq_status = BUFREQ_E_NOT_OK;    /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check if component is initialized */
  if(!Com_IsInitialized())
  {
    errorId = COM_E_UNINIT;
  }
# if (COM_DEV_ERROR_DETECT == STD_ON )
  /* #20 Check plausibility of input parameters */
#  if (COM_RXPDUINFO == STD_ON)
  else if(PduId >= Com_GetSizeOfRxPduInfo())
  {
    errorId = COM_E_PARAM;
  }
#   if (COM_INVALIDHNDOFRXPDUINFO == STD_ON)
  else if(Com_IsInvalidHndOfRxPduInfo(PduId))
  {
    errorId = COM_E_PARAM;
  }
#   endif
#   if (COM_EXISTS_NORMAL_TYPEOFRXPDUINFO == STD_ON)
  else if(Com_GetTypeOfRxPduInfo(PduId) == COM_NORMAL_TYPEOFRXPDUINFO)  /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    errorId = COM_E_PARAM;
  }
#   endif
#  endif
  else if(PduInfoPointer == NULL_PTR)
  {
    errorId = COM_E_PARAM_POINTER;
  }
  else if((PduInfoPointer->SduDataPtr == NULL_PTR) && (PduInfoPointer->SduLength > 0u))
  {
    errorId = COM_E_PARAM_POINTER;
  }
  else if(RxBufferSizePtr == NULL_PTR)
  {
    errorId = COM_E_PARAM_POINTER;
  }
# endif
  else
  {
# if (COM_RXTPINFOUSEDOFRXPDUINFO == STD_ON)
    /* ----- Implementation ----------------------------------------------- */
    bufReq_status = Com_CopyRxData_Processing(PduId, PduInfoPointer, RxBufferSizePtr);  /* SBSW_COM_VALID_PTR_ENSURED_BY_CALLING_FUNC */
# else
    errorId = COM_E_PARAM;
# endif
  }

  /* ----- Development Error Report --------------------------------------- */
# if (COM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != COM_E_NO_ERROR) /* PRQA S 2991, 2995 */ /* MD_Com_2991, MD_Com_2995 */ /* COV_COM_ONLY_DET_FUNCTIONALITY_PRESENT */
  {
    Com_LMgt_CallDetErrorContinue(COMServiceId_CopyRxData, errorId);
  }
# endif

  COM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(PduId);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(RxBufferSizePtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT_CONST(PduInfoPointer);    /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return bufReq_status;
}       /* PRQA S 6030, 6080 */ /* MD_MSR_STCYC, MD_MSR_STMIF */
#endif

#if (COM_TRIGGER_TRANSMIT_API == STD_ON)
/**********************************************************************************************************************
  Com_TriggerTransmit
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(Std_ReturnType, COM_CODE) Com_TriggerTransmit(PduIdType TxPduId, P2VAR(PduInfoType, AUTOMATIC, COM_APPL_VAR) PduInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = COM_E_NO_ERROR;       /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 retVal = E_NOT_OK;      /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check if component is initialized */
  if(!Com_IsInitialized())
  {
    errorId = COM_E_UNINIT;
  }
# if (COM_DEV_ERROR_DETECT == STD_ON )  /* COV_COM_VAR_ELISA_STD_ON_TX */
  /* #20 Check plausibility of input parameters */
#  if (COM_TXPDUINFO == STD_ON) /* COV_COM_VAR_DEPENDENT_SWITCH */
  else if(TxPduId >= Com_GetSizeOfTxPduInfo())
  {
    errorId = COM_E_PARAM;
  }
#   if (COM_INVALIDHNDOFTXPDUINFO == STD_ON)
  else if(Com_IsInvalidHndOfTxPduInfo(TxPduId))
  {
    errorId = COM_E_PARAM;
  }
#   endif
#  endif
  else if(PduInfoPtr == NULL_PTR)
  {
    errorId = COM_E_PARAM_POINTER;
  }
  else if((PduInfoPtr->SduDataPtr == NULL_PTR) && (PduInfoPtr->SduLength > 0u))
  {
    errorId = COM_E_PARAM_POINTER;
  }
# endif
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Do Trigger Transmit processing */
    retVal = Com_TriggerTransmit_Process(TxPduId, PduInfoPtr);  /* SBSW_COM_VALID_PTR_ENSURED_BY_CALLING_FUNC */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (COM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != COM_E_NO_ERROR) /* PRQA S 2991, 2995 */ /* MD_Com_2991, MD_Com_2995 */
  {
    Com_LMgt_CallDetErrorContinue(COMServiceId_TriggerTransmit, errorId);
  }
# endif

  COM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(TxPduId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(PduInfoPtr);      /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return retVal;
}       /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if (COM_TX_CONFIRMATION_API == STD_ON)
/**********************************************************************************************************************
  Com_TxConfirmation
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxConfirmation(PduIdType TxPduId)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = COM_E_NO_ERROR;       /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check if component is initialized */
  if(!Com_IsInitialized())
  {
    errorId = COM_E_UNINIT;
  }
# if (COM_DEV_ERROR_DETECT == STD_ON )  /* COV_COM_VAR_ELISA_STD_ON_TX */
  /* #20 Check plausibility of input parameters */
#  if (COM_TXPDUINFO == STD_ON) /* COV_COM_VAR_DEPENDENT_SWITCH */
  else if(TxPduId >= Com_GetSizeOfTxPduInfo())
  {
    errorId = COM_E_PARAM;
  }
#   if (COM_INVALIDHNDOFTXPDUINFO == STD_ON)
  else if(Com_IsInvalidHndOfTxPduInfo(TxPduId))
  {
    errorId = COM_E_PARAM;
  }
#   endif
#  endif
# endif
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Do confirmation processing */
    Com_TxConfirmation_Process(TxPduId);
  }

  /* ----- Development Error Report --------------------------------------- */
# if (COM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != COM_E_NO_ERROR) /* PRQA S 2991, 2995 */ /* MD_Com_2991, MD_Com_2995 */
  {
    Com_LMgt_CallDetErrorContinue(COMServiceId_TxConfirmation, errorId);
  }
# endif

  COM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(TxPduId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}
#endif

#define COM_STOP_SEC_CODE
#include "MemMap.h"    /* PRQA S 5087 */        /* MD_MSR_MemMap */

/***********************************************************************************************************************
 *  MISRA JUSTIFICATIONS
 **********************************************************************************************************************/
/* *INDENT-OFF* */
/* Justifications for module-specific MISRA deviations:
    MD_Com_0316_0317: Misra Rule 11.5
     Reason:     A pointer is cast to a void pointer, because it depends on the configuration of which type the pointer is. It is easier to use a void pointer insead of different functions for different pointer types.
     Risk:       No risk, because the underlying pointer type is known via the configuration.
     Prevention: No prevention necessary.

   MD_Com_2842: Misra Rule 18.1, Misra Rule 21.18, Misra Dir 4.1
     Reason:     The ComStackLib validates that the Index doesn't exceed the table.
     Risk:       No risk.
     Prevention: Qualified use-case CSL01 of ComStackLib.

   MD_Com_2982: Misra Rule 2.2
     Reason:     It depends on the configuration if the value is modified.
     Risk:       No risk, because only warning that assignment is redundant.
     Prevention: No prevention necessary.

   MD_Com_2985_2986: Misra Rule 2.2
     Reason:     The value of the operands depends on the configuration.
     Risk:       No risk, because only warning that the operation is redundant.
     Prevention: No prevention necessary.

   MD_Com_2991: Misra Rule 14.3
     Reason:     The value of the if-controlling expression depends on the configuration.
     Risk:       No risk.
     Prevention: No prevention necessary.

   MD_Com_2992: Misra Rule 14.3
     Reason:     The value of the if-controlling expression depends on the configuration.
     Risk:       No risk.
     Prevention: No prevention necessary.

   MD_Com_2995: Misra Rule 2.2
     Reason:     The value of the logical operation depends on the configuration.
     Risk:       No risk.
     Prevention: No prevention necessary.

  MD_Com_2996: Misra Rule 2.2
     Reason:     The value of the logical operation depends on the configuration.
     Risk:       No risk.
     Prevention: No prevention necessary.

   MD_Com_3205: Misra Rule 2.3
     Reason:     It depends on the configuration if the identifier is used or not.
     Risk:       No risk.
     Prevention: No prevention necessary.

   MD_Com_3206: Misra Rule 2.7
     Reason:     It depends on the configuration if the parameter is used or not.
     Risk:       No risk.
     Prevention: No prevention necessary.

   MD_Com_2003:  Misra Rule 16.3
     Reason:     A break-statement is not required, the switch case needs to perform the remaining operations of the succeeding case.
     Risk:       No risk
     Prevention: No prevention necessary

   MD_Com_2812:  Misra Dir 4.1
     Reason:     False-Positive: Dereference of NULL pointer.
     Risk:       No risk, pointer is checked against NULL pointer in preceding if-case.
     Prevention: No prevention necessary

  MD_Com_3677:   Misra Rule 8.13
     Reason:     It depends on the configuration if the parameter is modified or not.
     Risk:       No risk.
     Prevention: No prevention necessary

  MD_Com_2987: Misra Rule 2.2
     Reason:     False-Positive: Function has a side effekt. QAC has a problem with the access over the CfgPtr in Postbuild-Loadable
     Risk:       No risk.
     Prevention: No prevention necessary
*/
/***********************************************************************************************************************
 *  SILENTBSW JUSTIFICATIONS
 **********************************************************************************************************************/
/* SBSW_JUSTIFICATION_BEGIN
  \ID SBSW_COM_CSL01
    \DESCRIPTION    Index Access is using ComStackLib
    \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib.

  \ID SBSW_COM_CSL01_STACKPTR
    \DESCRIPTION    Index Access is using ComStackLib
    \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib and a the passed pointer belongs to a stack variable and is therefore always valid.

  \ID SBSW_COM_CSL02
    \DESCRIPTION    Access of Table1, via index of Table2.
                    Table1 and Table2 have a size relation.
    \COUNTERMEASURE \N Qualified use-case CSL02 of ComStackLib

  \ID SBSW_COM_CSL02_CSL03
    \DESCRIPTION    Access of Table1, via indirection over Table2 and index of Table3.
                    Table1 and Table3 have a size relation.
    \COUNTERMEASURE \N Qualified use-case CSL02 and CSL03 of ComStackLib

  \ID SBSW_COM_CSL03
    \DESCRIPTION    Access to Table1 via indirection over Table2.
    \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

  \ID SBSW_COM_TXBUFFER_CSL03
    \DESCRIPTION    Write access to TxBuffer over pointer.
    \COUNTERMEASURE \N The relation between TxSigInfo and TxBuffer is modeled through sorted by use-case CSL03 of ComStackLib indirection, therefore
                       out of bounds access is not possible. The array access index runs in between the indirection size.
                       For dynamic signals the access index is limited by the dynamic length which itself is checked in Com_SendDynSignal
                       against the actual indirection size.

   \ID SBSW_COM_VSTDLIB_SAFE
    \DESCRIPTION    Pointer is passed as function argument.
    \COUNTERMEASURE \N The VStdLib_MemCpy_s guarantees that the destination pointer is not overwritten.

  \ID SBSW_COM_FCT_PTR_CALL_CSL03
    \DESCRIPTION    Function pointer call from Table1 via indirection over Table2.
    \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

  \ID SBSW_COM_MEM_CPY
    \DESCRIPTION    Function call to copy data to RAM
    \COUNTERMEASURE \R Buffer boundary is checked before copy operation.

  \ID SBSW_COM_MEM_CPY_2RAM
    \DESCRIPTION    Function call to copy data to RAM.
    \COUNTERMEASURE \N The address of the destination and the amount of bytes to be copied are
                       retrieved through use-case CSL03 of ComStackLib indirection access macros.

  \ID SBSW_COM_FCTCALL_WITH_P2CONST
    \DESCRIPTION    Pointer is passed as function argument to read memory location.
    \COUNTERMEASURE \N Called function expects a P2CONST pointer, therefore write-access is not possible.

  \ID SBSW_COM_FCTCALL_STACKPTR
    \DESCRIPTION    Pointer is passed as function argument.
    \COUNTERMEASURE \N The passed pointer belongs to a stack variable and is therefore always valid.

  \ID SBSW_COM_WRITEACCESS_STACKPTR
    \DESCRIPTION    Write access on pointer after appl-type specific cast.
    \COUNTERMEASURE \N Caller ensures by checking the appl-type at runtime that the cast is valid.
                       The passed pointer belongs to a stack variable and is therefore always valid.

   \ID SBSW_COM_VALID_PTR_ENSURED_BY_CALLING_FUNC
    \DESCRIPTION A pointer is written or passed to a function. The pointer can possibly be used to write to the corresponding memory location.
    \COUNTERMEASURE \N The call sequence ensures that the pointer is valid.

   \ID SBSW_COM_VALID_PTR_ENSURED_BY_CALLING_FUNC_AND_STACKPTR
    \DESCRIPTION A pointer is written or passed to a function. The pointer can possibly be used to write to the corresponding memory location.
    \COUNTERMEASURE \N The calling function ensures that the pointer is valid. The second pointer belongs to a stack variable and is derived from the first.

  \ID SBSW_COM_WRITEACCESS_STACKPTR_01
    \DESCRIPTION    Write access on pointer.
    \COUNTERMEASURE \N Pointer points to stack variable and is therefore always valid.

  \ID SBSW_COM_WRITEACCESS_STACKPTR_WITH_LENGTH
    \DESCRIPTION    Write access on pointer.
    \COUNTERMEASURE \R The passed length parameter ensures that no memory is overwritten.

  \ID SBSW_COM_WRITEACCESS_LENGTH
    \DESCRIPTION    Write access on pointer.
    \COUNTERMEASURE \N Boundaries of pointer are ensured by provided length. Caller ensures validity of length and pointer.

  \ID SBSW_COM_WRITEACCESS_STACKPTR_CONFIG_LENGTH
    \DESCRIPTION    Write access on pointer.
    \COUNTERMEASURE \R The bytes to be copied are checked against the buffer size to ensures that no memory is overwritten.

  \ID SBSW_COM_PTR_API
    \DESCRIPTION Function call with pointer as argument.
    \COUNTERMEASURE \N The caller of the COM-API must ensure the validity of the passed pointer.
                       The DET of the COM-API verifies that the pointer is not equal to NULL_PTR.

  \ID SBSW_COM_PTR_API_VALID_PTR
    \DESCRIPTION Function call with pointer as argument.
    \COUNTERMEASURE \N The caller of the COM-API must ensure the validity of the passed pointer.

  \ID SBSW_COM_VALID_PTR_BY_COMSTACK_01
    \DESCRIPTION    Function call with pointer as argument.
    \COUNTERMEASURE \N Caller ensures by use-case CSL01 of ComStackLib access macros the validity of the passed pointer.

  \ID SBSW_COM_VALID_PTR_BY_COMSTACK_02
    \DESCRIPTION    Write access to RAM pointer in for loop.
    \COUNTERMEASURE \N Address of pointer is retrieved by use-case CSL02 of ComStackLib. The start and stop index of ComStackLib indirection ensure validity of pointer boundaries.

  \ID SBSW_COM_IDXPARAM_INTERNALFCT_CSL02
    \DESCRIPTION    The index is passed to an internal function as parameter and is used within the function to write to a memory location.
    \COUNTERMEASURE \N The index is read by the calling function using the use-case CSL02 of ComStackLib macros. The ComStackLib ensures the validity of the index through a size relation.

  \ID SBSW_COM_IDXPARAM_INTERNALFCT_DET_CSL02
    \DESCRIPTION    The index is passed to an internal function as parameter and is used within the function to write to a memory location.
    \COUNTERMEASURE \N The top most COM calling function ensures that the passed index is not out of bounds.
                       The use-case CSL02 of ComStackLib ensures the validity of the index through a size relation.

  \ID SBSW_COM_ARRAY_WRITEACCESS
    \DESCRIPTION    The memory location is used for an array write access.
    \COUNTERMEASURE \R Index is validated at runtime.

  \ID SBSW_COM_GWCACHING
    \DESCRIPTION    Array write access on GwEventCache ram array.
    \COUNTERMEASURE \R Index is checked against size of cache at runtime.

  \ID SBSW_COM_COMST_PTR
    \DESCRIPTION   Pointer is passed to a function.
    \COUNTERMEASURE \N The pointer is a pointer to a constant value and will not be written to.

  \ID SBSW_COM_FCTPTR_CACHE_PTR
    \DESCRIPTION Function call with pointer as argument. Cache struct pointer is passed to a function.
    \COUNTERMEASURE \N The caller of the API must ensure the validity of the passed pointer. Pointer always points to a stack struct.

  \ID SBSW_COM_FCTPTR_CACHE_PTR_1
    \DESCRIPTION Function call with pointer as argument. Cache struct pointer is passed to a function.
    \COUNTERMEASURE \N Pointer always points to a stack struct, which itself contains pointer which point to either stack or heap arrays.
                     Pointed arrays should always accessed by using the pointer access parameters (size and index) contained in the provided struct, which ensures
                     consistency of memory. Access of array is always done in same task or interrupt context.

  \ID SBSW_COM_FCTPTR_CACHE_PTR_2
    \DESCRIPTION Pointer write access. Modification of cache index.
    \COUNTERMEASURE \N The caller of the API must ensure the validity of the passed pointer. Pointer always points to a stack information struct.

  \ID SBSW_COM_FCTPTR_CACHE_PTR_3
    \DESCRIPTION Array write access on function pointer cache (stack or heap).
    \COUNTERMEASURE \R Index is checked against cache size at runtime.

  \ID SBSW_COM_GW_DESCRIPTION_COPYBUFFER
    \DESCRIPTION Function call with const pointer and var pointer.
    \COUNTERMEASURE \N Pointer of source buffer is P2CONST, therefore only a read access is possible. Destination pointer is retrieved to use-case CSL03 of ComStackLib Indirection.

  \ID SBSW_COM_GWDESCRIPTION_RTCHECK
    \DESCRIPTION Array write access on destination buffer.
    \COUNTERMEASURE \R Index is checked against destinationBufferSize at runtime.

  \ID SBSW_COM_CSL_VAR_ACCESS
    \DESCRIPTION A ComStackLib generated variable is accessed.
    \COUNTERMEASURE \N The variable is written using a generated macro of the CSL. It immediately dereferences the variables address without pointer arithmetic.

  \ID SBSW_COM_FCTCALL_WITH_P2CONST_AND_FCTPTR_CACHE_PTR_1
    \DESCRIPTION Function call with pointer as argument. Cache struct pointer is passed to a function. (see SBSW_COM_FCTPTR_CACHE_PTR_1)
                 Pointer is passed as function argument to read memory location. (see SBSW_COM_FCTCALL_WITH_P2CONST)
    \COUNTERMEASURE \N Pointer always points to a stack struct, which itself contains pointer which point to either stack or heap arrays.
                     Pointed arrays should always accessed by using the pointer access parameters (size and index) contained in the provided struct, which ensures
                     consistency of memory. Access of array is always done in same task or interrupt context. (see SBSW_COM_FCTPTR_CACHE_PTR_1)
                     Called function expects a P2CONST pointer, therefore write-access is not possible. (see SBSW_COM_FCTCALL_WITH_P2CONST)

SBSW_JUSTIFICATION_END */

/***********************************************************************************************************************
 *  COVERAGE JUSTIFICATIONS
 **********************************************************************************************************************/
/* START_COVERAGE_JUSTIFICATION

  \ID COV_COM_FEATURE_ALWAYS_TRUE_TX
    \ACCEPT TX
    \REASON Depending on the configuration the feature check can always be true. In this case the compiler removes the check.

   \ID COV_COM_FEATURE_RX_TOUT_INFO_USED_XX
    \ACCEPT XF
    \ACCEPT TX
    \REASON Depending on the configuration the feature check can always be false or always true. The function are ApplType specific the preprocessor switch is ApplType independent.

   \ID COV_COM_FEATURE_RX_TOUT_WITH_UB
    \ACCEPT XF tf xf
    \REASON Depending on the configuration the feature check can always be false or always true. The Rx Timeout and the Rx UpdateBit are two independent features and must not be configured combined.

   \ID COV_COM_SILENT_TX
    \ACCEPT TX
    \REASON This checks ensures that no incorrect memory is overwritten. This should never happen in normal configurations.

   \ID COV_COM_IPDU_GROUP_ASR3_XF
    \ACCEPT XF
    \REASON Statement can only evaluate to true for Rx I-PDUs where referred I-PDU Group has a I-PDU sub-Group.

    \ID COV_COM_IPDU_GROUP_ASR3_TX
    \ACCEPT TX
    \REASON Statement can only evaluate to false for Rx I-PDUs where referred I-PDU Group has a I-PDU sub-Group.

    \ID COV_COM_IPDU_GROUP_DM_ASR3_TX
    \ACCEPT TX
    \REASON Runtime check should never be false.

    \ID COV_COM_MASKED_NEW_DIFFERS_MASKED_OLD_TX
    \ACCEPT TX
    \REASON Condition may never be false if this filter is used on Tx side only.

  \ID COV_COM_THRESHOLD_TX
    \ACCEPT TX
    \REASON May always be true if number of iterated elements is less than or equal the configured threshold.

   \ID COV_COM_RXPROCESSING_TX
    \ACCEPT TF tf tx
    \ACCEPT TX tx tx
    \REASON Second condition never evaluates to false when first condition is true. Second condition only evaluates to false if only zero bit signals/groupSignals are present.

  \ID COV_COM_RXPROCESSING
    \ACCEPT TX
    \REASON May always be true if only groupSignals are present.

  \ID COV_COM_RXPROCESSING_SHADOWSIGNAL
    \ACCEPT TF tf tf
    \ACCEPT TX tx tx
    \ACCEPT TF tx tf
    \ACCEPT TF tf tx
    \REASON The condition targeting the shadow buffer can only evaluate to false for zero bit group signals or signal groups with array based access. An initial value can only be absent for zero bit group signals and dynamic lenght signals.

   \ID COV_COM_PERFORMINVALIDACTION_X
    \ACCEPT X
    \REASON May not be called if only SignalGroups with invalid action are configured.

   \ID COV_COM_INVALIDATION_TX
    \ACCEPT TX
    \REASON May not be called if only groupSignals with invalid values are configured.

   \ID COV_COM_PERFORMINVALIDACTION
    \ACCEPT TF tf tx
    \ACCEPT TX tx tx
    \ACCEPT XX
    \REASON Second condition never evaluates to false as this condition is already checked in the sequence flow. TX_tx_tx occurs if only signals with invalid action are present. May never be called if the enclosing condition evaluates to false.

   \ID COV_COM_PERFORMINVALIDACTION_ARRAYBASED
    \ACCEPT TF tf tx
    \ACCEPT TX tx tx
    \REASON Second condition never evaluates to false as this condition is already checked in the sequence flow. TX_tx_tx occurs if only array based signals with invalid action are present.

   \ID COV_COM_PERFORMINVALIDACTION_GROUPSIGNAL
    \ACCEPT TF tf tx
    \ACCEPT TX tx tx
    \REASON Second condition never evaluates to false as this condition is already checked in the sequence flow. TX_tx_tx occurs if only GroupSignals with invalid action are present. May never be called if the enclosing condition evaluates to false.

   \ID COV_COM_PERFORMINVALIDACTION_ARRAYBASED_GROUPSIGNAL
    \ACCEPT TF tf tx
    \ACCEPT TX tx tx
    \REASON Second condition never evaluates to false as this condition is already checked in the sequence flow. TX_tx_tx occurs if only array based GroupSignals with invalid action are present.

   \ID COV_COM_DLMON_SIGNALTIMEOUTACTION_TX
    \ACCEPT TF tf tx
    \ACCEPT TX tx tx
    \REASON May evaluate to TX if only Signals/GroupSignals with a configured timeout are present. The last condition will never evaluate to false as buffer is always present for signals/GroupSignals other than zero bit signals/GroupSignals.

   \ID COV_COM_RXDEFERRED_TIMEOUT
    \ACCEPT XF
    \REASON May always be false if all ComIPdus which are monitored are immediate PDUs.

   \ID COV_COM_RXDEFERRED_PROCESSING
    \ACCEPT TX
    \REASON May always be true if all ComIPdus are deferred PDUs.

   \ID COV_COM_TIMEOFFSET
    \ACCEPT TX
    \REASON May always be true if time offset is only configured for TxModeTrue.

   \ID COV_COM_UPDATE_IPDU_STATE
    \ACCEPT TX
    \REASON May always be true if only rxSignlals/groupSignals without handleId are configured.

   \ID COV_COM_SIGNALINVALIDATION
    \ACCEPT X
    \REASON May never be true if only groupSignals with invalid values are present.

  \ID COV_COM_SIGNALINVALIDATION_ARRAYACCESS
    \ACCEPT X
    \REASON May never be true if only groupSignals with array access and with invalid values are present.

  \ID COV_COM_ONLYARRAYACCESS_PRESENT
    \ACCEPT XX
    \REASON May not be evaluated if no signal groups without array access are present.

  \ID COV_COM_ONLYARRAYACCESS_PRESENT_01
    \ACCEPT TX
    \REASON May always be TRUE if only signal groups with array access are present.

   \ID COV_COM_SIGNALINVALIDATION_ARRAYACCESS_01
    \ACCEPT XX
    \REASON Will never be evaluated if only groupSignals with array access and with invalid values are present.

   \ID COV_COM_CACHEORCALL_IMMEDIATE
    \ACCEPT TX
    \REASON May always be true if received immediate ComIPdu has less or equal signals and/or signalGroups with configured notification callbacks than configured cache size.

   \ID COV_COM_DLMON_SIGNALTIMEOUTACTION_DYN_TX
    \ACCEPT TF tf tx
    \ACCEPT TX tx tx
    \REASON May evaluate to TX if only Signals/GroupSignals with a configured timeout are present. The last condition can only evaluate to false for dynamic length signals.

   \ID COV_COM_N_BIT_X
    \ACCEPT X
    \REASON Not reachable if only zero bit signals are present with n bit bus access type.

   \ID COV_COM_NBITNBYTE_X
    \ACCEPT X
    \REASON Not reachable if only groupSignals have the bus access type NBITNBYTE, whose enclosing signal group has array access enabled.

   \ID COV_COM_NBITNBYTE_SW_BUSACCOFTXSIGINFO
    \ACCEPT X
    \REASON Not reachable if only groupSignals have the bus access type NBITNBYTE_SW_BUSACCOFTXSIGINFO, whose enclosing signal group has array access enabled.

   \ID COV_COM_NBITNBYTE
    \ACCEPT TX
    \ACCEPT XF
    \REASON Condition only evaluates to false if Rx signal/groupSignal with bit size is < 9, where the byte layout overlaps at least two bytes.

   \ID COV_COM_NBITNBYTE_COPY_REMAININGBITS
    \ACCEPT TX
    \ACCEPT XF
    \REASON Depending on the signal layout this condition may always be FALSE or always TRUE, if the last byte to be copied is always or never a full byte.

   \ID COV_COM_NBITNBYTE_TX_01
    \ACCEPT TX
    \ACCEPT XX
    \REASON This condition shall never evaluate to false, runtime check is only provided on safety purpose. May evaluate to XX if enclosing encapsulation evaluates to false.

   \ID COV_COM_NBITNBYTE_BY_UINT8_ONLY
    \ACCEPT TX
    \REASON This condition may not evaluate to false, if the NBitNByte Algorithm is only present for UInt8 signals.

   \ID COV_COM_DIRECTTRIGGER
    \ACCEPT TX
    \REASON Will always be true if no periodic/mixed I-PDUs are configured.

   \ID COV_COM_REPETITIVE_TRANSMISSION
    \ACCEPT TX
    \REASON May always be true if only MDT is configured and no repetitions.

   \ID COV_COM_NONTRIGGERED_REPETITION
    \ACCEPT XF
    \REASON May always be FALSE if repetitions are configured for non-event based TxModeModes.

   \ID COV_COM_ZERO_REPETITION
    \ACCEPT TX
    \ACCEPT XF
    \REASON For full coverage, ComTxIPdus with and without repetitions need to be configured.

   \ID COV_COM_SETCYCLETIMECOUNT
    \ACCEPT TX
    \ACCEPT XF
    \ACCEPT XX
    \REASON May always be true/false if txModeMode has no cyclic content in both txModes. May never be evaluated, if enclosing condition always evaluates to FALSE.

  \ID COV_COM_NBITNBYTE_ENDIANNESS
    \ACCEPT TX
    \REASON May always be true, if all signals are big endian signals.

   \ID COV_WRITESIGNAL_NBITNBYTE_XX
    \ACCEPT XX
    \ACCEPT X
    \REASON May evaluate to XX if only GroupSignals have an overlapping layout respective to the byte boundaries, whose enclosing SignalGroup has array access enabled.

   \ID COV_COM_NBITNBYTE_XX
    \ACCEPT XX
    \REASON May evaluate to XX if enclosing encapsulation evaluates to false.

   \ID COV_COM_SIGNMSBOFFSET
    \ACCEPT XF
    \ACCEPT TX
    \REASON Only reachable if SINT16 Rx signal/groupSignal is present with bit size < 9.

  \ID COV_COM_IPDU_GROUP_STATE_ACTIVE
    \ACCEPT TF tf tx
    \REASON Depending on the configuration the last sub condition will always be true.

  \ID COV_COM_TX_FILTER
    \ACCEPT TX
    \REASON May not be FALSE if I-PDU has only one signal.

  \ID COV_COM_FILTER_ALWAYS_PRESENT
    \ACCEPT TX
    \REASON May always be true if all signalGroups have at least one groupSignal with configured filter.

  \ID COV_COM_TXIPDUGROUP_ACTIVE
    \ACCEPT TX
    \REASON Can only evaluate to false if filter are configured.

   \ID COV_COM_ISDIRECT_TXMODE
    \ACCEPT TX
    \REASON Can only evaluate to false if mixed or periodic or none I-PDUs are configured.

  \ID COV_COM_APPLTYPEOFRXACCESSINFO
    \ACCEPT X
    \REASON May not be called if only groupSignals with specific appl type are present.

  \ID COV_COM_APPLTYPEOFRXACCESSINFO_GW_ROUTING
    \ACCEPT X
    \REASON May not be called if Gateway Routing is only done for specific appl types.

  \ID COV_COM_RX_PROCESSING_SINGLEPDU
    \ACCEPT TX
    \REASON May not evaluate to false if only one Rx deferred I-PDU is present.

  \ID COV_COM_TX_PROCESSING_NONE_MODE
    \ACCEPT TX
    \ACCEPT XF
    \REASON May not be fully covered if only tx I-PDUs with TxModeMode NONE with a configured timeout are present.

  \ID COV_COM_SHDBUFFER_REQUIRED
    \ACCEPT TX
    \REASON May always be TRUE when no ArrayAccess SignalGroups without Gateway Routing are configured.

  \ID COV_COM_RX_TOUT_CNT
    \ACCEPT TX
    \REASON Depending on the configuration the condition will always be true. Only in configuration with a first timeout equal to 0 the condition can evaluate to false.

  \ID COV_COM_SIGGRP_CHECK
    \ACCEPT XF
    \ACCEPT TX
    \REASON May always evaluate to FALSE, if only signal groups with enabled array access are present. May always evaluate to TRUE in configurations where only signal groups are present.

  \ID COV_COM_TRIGGERED_ONCHG_SIGGRP
    \ACCEPT XF
    \ACCEPT TX
    \REASON Depending on configuration this condition may always be true/false if all/no group signals have transferProperty TRIGGERED_ON_CHANGE(_WITHOUT_REPETITION).

  \ID COV_COM_WRITESIGNAL_TXBUFFER
    \ACCEPT TX
    \ACCEPT XF
    \REASON May always be TRUE, if all ComSignals are ZeroBit Signals. May always be FALSE if there are no zero bit ComSignals present.

  \ID COV_COM_ONLY_TRIGGERED_SIGGRP
    \ACCEPT TX
    \REASON Always evaluates to TRUE if only triggered signal groups are present.

  \ID COV_COM_ONLY_ARRAYBASED_TX_SIGGRP
    \ACCEPT XF
    \REASON May always be FALSE if only array-based Tx SignalGroups are present.

  \ID COV_COM_ONLY_ARRAYBASED_RX_SIGGRP
    \ACCEPT XF
    \REASON May always be FALSE if only array-based Rx SignalGroups are present.

  \ID COV_COM_NO_GRPSIG_FILTER_PRESENT
    \ACCEPT XF
    \REASON May evaluate to FALSE, if no group signals with configured filter are present.

  \ID COV_COM_SIGGRP_FILTER
    \ACCEPT XF
    \ACCEPT TX
    \REASON May always evaluate to FALSE, if only group signals with filters are present but not signals. May always evaluate to TRUE if only signals with filters are present but no group signals.

  \ID COV_COM_FILTERSTATE
    \ACCEPT XX
    \REASON May not get evaluated if first conditions fails (if only group signals with filter are present).

  \ID COV_COM_ONLY_DET_FUNCTIONALITY_PRESENT
    \ACCEPT TX
    \REASON Condition is always true if the actual functionality of this API is not configured.

  \ID COV_COM_CYCLIC_SEND_REQUEST
    \ACCEPT XF
    \ACCEPT TX
    \REASON Condition may always be false if only TxModeFalse has got a cyclic portion and the initial TxMode is always TxModeTrue. May always be true, if the initial TxMode is always in a cyclic TxModeMode.

  \ID COV_COM_TIMEOUT_AND_UB
    \ACCEPT XF tf xf
    \REASON Condition may not be fully covered when no signals/groups with timeout and update bit are configured.

  \ID COV_COM_REPETITIONS
    \ACCEPT XF
    \REASON May never be true if repetitions are configured but no triggered signal is present.

  \ID COV_COM_DEFERREDIPDUSEND
    \ACCEPT XF
    \REASON May always be false, if not WITHOUT_REPETITION TransferProperty is configured.

  \ID COV_COM_FLOAT_TYPE_FILTER
    \ACCEPT TX
    \REASON May never be false for Rx signals or groupSignals as only 'NEVER' filter is supported.

  \ID COV_COM_IMMEDIATE_DESTINATION_DESCRIPTION
    \ACCEPT TX
    \REASON May always be true, if all GwDestinationDescriptions are of type IMMEDIATE.

  \ID COV_COM_GWDESCRIPTION_RTCHECK
   \ACCEPT TF tf tx
   \REASON Last condition shall never evaluate to false. SBSW RT check to avoid overwriting buffer.

  \ID COV_COM_DEFERRED_EVENTCACHE_FALLBACK
   \ACCEPT XF
   \REASON Will always evaluate to FALSE in unit test suite. Check is still required as an interrupt can overflow the cache.

  \ID COV_COM_UINT8_DYN_APPLTYPE
   \ACCEPT XF
   \ACCEPT TX
   \REASON May not be fully covered in configuration with only dynamic length signals.

  \ID COV_COM_PERIODIC_PDU_REQUIRED
   \ACCEPT TX
   \REASON This condition can only fail for periodic ComIPdu.

  \ID COV_COM_TP_ONLY
   \ACCEPT TF xf tf
   \ACCEPT XF
   \ACCEPT TX
   \ACCEPT TF tx tf
   \REASON May not be fully configured in TP only configuration.

  \ID COV_COM_NO_METADATA_CONFIGURED
   \ACCEPT TX
   \REASON May not be fully covered, if Meta Data API is enabled but no Pdu with Meta Data is present.

  \ID COV_COM_NO_DYNSIG_CONFIGURED
   \ACCEPT TX
   \REASON May not be fully covered, if no dynamic length signals are present.

  \ID COV_COM_MISRA
    \ACCEPT X
    \ACCEPT TX
    \REASON [MSR_COV_MISRA]

  \ID COV_COM_VAR_ELISA_STD_ON_TX
    \ACCEPT TX
    \REASON Feature must always be enabled for SafeBsw secured by the Elisa plugin.

  \ID COV_COM_VAR_ELISA_STD_OFF_XF
    \ACCEPT XF
    \REASON Feature must always be disabled for SafeBsw secured by the Elisa plugin.

  \ID COV_COM_VAR_ELISA_STD_OFF_TX
    \ACCEPT TX
    \REASON see COV_COM_VAR_ELISA_STD_OFF_XF

  \ID COV_COM_VAR_ELISA_STD_OFF_TF_tx_tf_tf_tf
    \ACCEPT TF tx tf tf tf
    \REASON see COV_COM_VAR_ELISA_STD_OFF_XF

  \ID COV_COM_VAR_ELISA_STD_OFF_TF_tf_tf_tf_tf_xf_tf_tf
    \ACCEPT TF tf tf tf tf xf tf tf
    \REASON see COV_COM_VAR_ELISA_STD_OFF_XF

  \ID COV_COM_VAR_DEPENDENT_SWITCH
    \ACCEPT TX
    \REASON The nested switch depends on a previous switch.

  \ID COV_COM_TX_BUFFER_ALWAYS_USED
    \ACCEPT TX
    \REASON This statement can only be fully covered, if zero-Bit Pdus are present.

  \ID COV_COM_ONLY_CYCLIC_PDU
    \ACCEPT TX
    \REASON This statement is always true if only cyclic PDUs are configured.

  \ID COV_COM_NO_IPDUGROUPS
    \ACCEPT TX
    \REASON If no ComIPdu Groups are configured, the statement is always true.

  \ID COV_COM_NO_TIMEOUT_AND_OFFSET
    \APPLYOVERRIDE
    \REASON Condition is always FALSE in configurations that have no PDU with timeoffset and timeout.

  \ID COV_COM_ONLY_TRIGGERED_SIG
    \APPLYOVERRIDE
    \REASON Condition is always TRUE if only signals with transfer property TRIGGERED exist.

  \ID COV_COM_ONLY_MIXED_PDUS
    \APPLYOVERRIDE
    \REASON Condition is always TRUE if only PDUs with txMode MIXED or PERIODIC exist.

  \ID COV_COM_ONLY_INIT_VALUE
    \ACCEPT TF tx tf
    \REASON Condition is not fully covered in configurations with init value configured for all signals and groupSignals.
    
  \ID COV_COM_MIN_SIGGW_UINT8_ONLY
    \ACCEPT Tx tx tx
    \REASON Condition is not fully covered in configurations with init value configured for all signals and groupSignals. Config only contains UINT8_N signals and groupSignals.
    
  \ID COV_COM_DEFENSIVE_PROGRAMMING
    \ACCEPT TX
    \REASON Statement will never reach false as the Tx signal id is always valid.

COV_JUSTIFICATION_END */
/* *INDENT-ON* */

/**********************************************************************************************************************
 *  END OF FILE: Com.c
 *********************************************************************************************************************/
