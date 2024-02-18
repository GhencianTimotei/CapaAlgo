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
 *         File:  IpduM.c
 *      Project:  MICROSAR IpduM
 *       Module:  Implementation
 *    Generator:  CFG5
 *
 *  Description:  Microsar IPDU Multiplexer source file
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

#define IPDUM_SOURCE
/**********************************************************************************************************************
 * MISRA JUSTIFICATION
 *********************************************************************************************************************/

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
#include "IpduM.h"
#include "IpduM_Mux.h"
#include "IpduM_Container.h"
#include "IpduM_Cbk.h"
#include "SchM_IpduM.h"
#include "vstdlib.h"

#if (IPDUM_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif
#if(IPDUM_USE_INIT_POINTER == STD_ON)
# include "EcuM_Error.h"
#endif

/**********************************************************************************************************************
  VERSION CHECK
**********************************************************************************************************************/
/* vendor specific version information is BCD coded */
#if ((IPDUM_SW_MAJOR_VERSION != 10u) || (IPDUM_SW_MINOR_VERSION != 0u) || (IPDUM_SW_PATCH_VERSION != 2u))
# error "IpduM.c: IpduM.c and IpduM.h versions are inconsistent!"
#endif

/**********************************************************************************************************************
  LOCAL CONSTANT MACROS
**********************************************************************************************************************/
#define IPDUM_RESET                             0u

/**********************************************************************************************************************
  LOCAL FUNCTION MACROS
**********************************************************************************************************************/
#if (IPDUM_DEV_ERROR_REPORT == STD_ON)                                     
# define IpduM_Det_ReportError(ApiId, ErrorCode)    (void)Det_ReportError(IPDUM_MODULE_ID, 0, (ApiId), (ErrorCode))   /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#endif

/**********************************************************************************************************************
  LOCAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/

/**********************************************************************************************************************
  LOCAL DATA PROTOTYPES
**********************************************************************************************************************/

/**********************************************************************************************************************
  LOCAL DATA
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL DATA
**********************************************************************************************************************/
#define IPDUM_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h"    /* PRQA S 5087 */        /*  MD_MSR_MemMap */

#if(IPDUM_USE_INIT_POINTER == STD_ON)
P2CONST(IpduM_ConfigType, IPDUM_VAR_ZERO_INIT, IPDUM_INIT_DATA) IpduM_ConfigDataPtr = NULL_PTR;
#endif

#define IPDUM_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h"    /* PRQA S 5087 */        /*  MD_MSR_MemMap */

/**********************************************************************************************************************
  LOCAL FUNCTION PROTOTYPES
**********************************************************************************************************************/

/**********************************************************************************************************************
  LOCAL FUNCTIONS
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL FUNCTIONS
**********************************************************************************************************************/
#define IPDUM_START_SEC_CODE
#include "MemMap.h"    /* PRQA S 5087 */        /*  MD_MSR_MemMap */

/*******************************************************************************************
 *  IpduM_Init()
*******************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(void, IPDUM_CODE) IpduM_Init(P2CONST(IpduM_ConfigType, AUTOMATIC, IPDUM_INIT_DATA) config)
{
  uint8 errorId = IPDUM_E_NO_ERROR;
#if(IPDUM_USE_INIT_POINTER == STD_ON)
  IpduM_ConfigDataPtr = config;
  if(IpduM_ConfigDataPtr == NULL_PTR)
  {
# if(IPDUM_USE_ECUM_BSW_ERROR_HOOK == STD_ON)   /* COV_IPDUM_VAR_DEPENDENT_SWITCH */
    EcuM_BswErrorHook(IPDUM_MODULE_ID, ECUM_BSWERROR_NULLPTR);
# endif
# if (IPDUM_DEV_ERROR_DETECT == STD_ON)
    errorId = IPDUM_E_PARAM_POINTER;
# endif
  }
# if (IPDUM_FINALMAGICNUMBER == STD_ON) /* COV_IPDUM_VAR_DEPENDENT_SWITCH */
  else if(IpduM_GetFinalMagicNumber() != IPDUM_FINAL_MAGIC_NUMBER)
  {
    IpduM_ConfigDataPtr = NULL_PTR;
#  if(IPDUM_USE_ECUM_BSW_ERROR_HOOK == STD_ON)  /* COV_IPDUM_VAR_DEPENDENT_SWITCH */
    EcuM_BswErrorHook(IPDUM_MODULE_ID, ECUM_BSWERROR_MAGICNUMBER);
#  endif
#  if (IPDUM_DEV_ERROR_DETECT == STD_ON)
    errorId = IPDUM_E_PARAM_POINTER;
#  endif
  }
# endif
#else
  if(config != NULL_PTR)        /* COV_IPDUM_PRECOMPILE_CONFIG */
  {
# if (IPDUM_DEV_ERROR_DETECT == STD_ON)
    errorId = IPDUM_E_PARAM_POINTER;
# endif
  }
#endif
#if((IPDUM_TXBUFFERSTARTIDXOFTXPATHWAY == STD_ON) || (IPDUM_RXMUXPDU == STD_ON) || (IPDUM_CONTAINERRXBUFFER == STD_ON) || (IPDUM_CONTAINERTXBUFFER == STD_ON))       /* COV_IPDUM_EMPTY_CONFIG */
  else
  {

# if(IPDUM_TXCONFTIMEOUTCNTOFVTXLOINFO == STD_ON)
    {
      IpduM_CTxLoInfoIterType txConfTimeoutCntIdx;
      for(txConfTimeoutCntIdx = 0u; txConfTimeoutCntIdx < IpduM_GetSizeOfVTxLoInfo(); txConfTimeoutCntIdx++)
      {
        /* Reset timeout counter for given multiplex handle in this loop iteration */
        IpduM_SetTxConfTimeoutCntOfVTxLoInfo(txConfTimeoutCntIdx, IPDUM_RESET);    /* SBSW_IPDUM_CSL01 */
      }
    }
# endif

# if (IPDUM_TXBUFFERSTARTIDXOFTXPATHWAY == STD_ON)
    IpduM_InitComponentMux();
# endif

# if ((IPDUM_CONTAINERRXBUFFER == STD_ON) || (IPDUM_CONTAINERTXBUFFER == STD_ON))
    IpduM_Container_Init();
# endif

    IpduM_SetInitialized(TRUE); /* SBSW_IPDUM_CSL_VAR_ACCESS */
  }
#endif
#if (IPDUM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != IPDUM_E_NO_ERROR)       /* COV_IPDUM_NO_DEV_ERROR */
  {
    IpduM_Det_ReportError(IPDUM_APIID_INIT, (errorId));
  }
#else
  IPDUM_DUMMY_STATEMENT(errorId);      /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */  /* lint -e{438} */
#endif
} /* PRQA S 6010, 6030 */ /* MD_MSR_STPTH, MD_MSR_STCYC */

/*******************************************************************************************
 *  IpduM_InitMemory()
*******************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, IPDUM_CODE) IpduM_InitMemory(void)
{
  /* Set the IpduM to "uninitialized" */
  IpduM_SetInitialized(FALSE);  /* SBSW_IPDUM_CSL_VAR_ACCESS */
#if(IPDUM_USE_INIT_POINTER == STD_ON)
  IpduM_ConfigDataPtr = NULL_PTR;
#endif
}

/*******************************************************************************************
*  IpduM_MainFunctionTx()
*******************************************************************************************/
/*! \brief        Performs actions not directly initiated by calls from the PduR.
 *  \details      -
 *  \pre          -
 *  \context      TASK
 *  \reentrant    TRUE
 *  \synchronous  TRUE
*******************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(void, IPDUM_CODE) IpduM_MainFunctionTx(void)
{
#if ((IPDUM_TXCONFTIMEOUTCNTOFVTXLOINFO == STD_ON)||(IPDUM_TXCONTAINEDPDU == STD_ON))
  if(IpduM_IsInitialized())
  {
# if ((IPDUM_TXCONFTIMEOUTCNTOFVTXLOINFO == STD_ON) && (IPDUM_TXLOINFOWITHINVALIDINDEXES == STD_ON)) /* COV_IPDUM_VAR_DEPENDENT_SWITCH */
    {
      IpduM_CTxLoInfoIterType txLoInfoIdx;
      for(txLoInfoIdx = 0; txLoInfoIdx < IpduM_GetSizeOfCTxLoInfo(); txLoInfoIdx++)
      {
#  if ((IPDUM_TXCONTAINEDPDU == STD_ON) && (IPDUM_EXISTS_CONTAINER_PATHWAYTYPEOFCTXLOINFO == STD_ON))
        if((IpduM_GetTxConfTimeoutCntOfVTxLoInfo(txLoInfoIdx) == 1u)
#   if (IPDUM_EXISTS_MUX_PATHWAYTYPEOFCTXLOINFO == STD_ON)
           && (IpduM_GetPathwayTypeOfCTxLoInfo(txLoInfoIdx) == IPDUM_CONTAINER_PATHWAYTYPEOFCTXLOINFO)
#   endif
          )   /* COV_IPDUM_TXCONF_ALWAYS_ZERO */
        {
          /* it is a container PDU about to time-out */
          IpduM_TxContainerPduIdxOfCTxLoInfoType containerPduId = IpduM_GetTxContainerPduIdxOfCTxLoInfo(txLoInfoIdx);

          /* reset write index */
          SchM_Enter_IpduM_IPDUM_EXCLUSIVE_AREA_0();
          IpduM_SetContainerTxConfLaIdOfTxContainerPdu(containerPduId, 0u);  /* SBSW_IPDUM_CSL03 */
          SchM_Exit_IpduM_IPDUM_EXCLUSIVE_AREA_0();
        }
#  endif
        SchM_Enter_IpduM_IPDUM_EXCLUSIVE_AREA_0();
        if(0u != IpduM_GetTxConfTimeoutCntOfVTxLoInfo(txLoInfoIdx))      /* COV_IPDUM_TXCONF_ALWAYS_ZERO */
        {
          IpduM_DecTxConfTimeoutCntOfVTxLoInfo(txLoInfoIdx);     /* SBSW_IPDUM_CSL03 */
        }
        SchM_Exit_IpduM_IPDUM_EXCLUSIVE_AREA_0();
      }
    }
# endif

# if (IPDUM_TXCONTAINEDPDU == STD_ON)
    IpduM_ContainerTx_MainFunction();
# endif
  }
#endif
}  /* PRQA S 6010, 6030 */ /* MD_MSR_STPTH, MD_MSR_STCYC */

/*******************************************************************************************
*  IpduM_MainFunctionRx()
*******************************************************************************************/
/*! \brief        Performs actions not directly initiated by calls from the PduR.
 *  \details      -
 *  \pre          -
 *  \context      TASK
 *  \reentrant    TRUE
 *  \synchronous  TRUE
*******************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, IPDUM_CODE) IpduM_MainFunctionRx(void)
{
#if (IPDUM_RXCONTAINERPDU == STD_ON)
  if(IpduM_IsInitialized()) 
  {
    IpduM_ContainerRx_MainFunction();
  }
#endif
}

/*******************************************************************************************
 *  IpduM_Transmit()
*******************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, IPDUM_CODE) IpduM_Transmit(PduIdType PdumTxPduId, P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr)
{
  Std_ReturnType retVal = E_NOT_OK;

#if (IPDUM_TXUPINFO == STD_ON)
  uint8 errorId = IPDUM_E_NO_ERROR;
# if (IPDUM_DEV_ERROR_DETECT == STD_ON)
  if(!IpduM_IsInitialized())
  {
    errorId = IPDUM_E_UNINIT;
  }
  else if((PdumTxPduId >= IpduM_GetSizeOfTxUpInfo())
#  if (IPDUM_INVALIDHNDOFTXUPINFO == STD_ON)
          || (IpduM_IsInvalidHndOfTxUpInfo(PdumTxPduId))
#  endif
    )
  {
    errorId = IPDUM_E_PARAM;
  }
  else if((PduInfoPtr == NULL_PTR) || (PduInfoPtr->SduDataPtr == NULL_PTR))
  {
    errorId = IPDUM_E_PARAM_POINTER;
  }
  else
# endif
  {
    IpduM_TxUpIndIdxOfTxUpInfoType txUpIndIdx = IpduM_GetTxUpIndIdxOfTxUpInfo(PdumTxPduId);
    switch (IpduM_GetPathwayTypeOfTxUpInfo(PdumTxPduId))
    {
# if (IPDUM_EXISTS_MUX_PATHWAYTYPEOFTXUPINFO == STD_ON)
      case IPDUM_MUX_PATHWAYTYPEOFTXUPINFO:
      {
        retVal = IpduM_MuxTransmit(txUpIndIdx, PduInfoPtr); /* SBSW_IPDUM_FUNCTIONCALL_PDUINFOPTR_CHECKED_BY_CALLER */
        break;
      }
# endif
# if (IPDUM_EXISTS_CONTAINER_PATHWAYTYPEOFTXUPINFO == STD_ON)
      case IPDUM_CONTAINER_PATHWAYTYPEOFTXUPINFO:
      {
        retVal = IpduM_ContainerTransmit(txUpIndIdx, PduInfoPtr); /* SBSW_IPDUM_FUNCTIONCALL_PDUINFOPTR_CHECKED_BY_CALLER */
        break;
      }
# endif
      default: /* COV_IPDUM_MISRA */
      {
        break; /* PRQA S 2880 */ /* MD_IpduM_2880 */
      }
    }
  }
# if (IPDUM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != IPDUM_E_NO_ERROR)
  {
    IpduM_Det_ReportError(IPDUM_APIID_TRANSMIT, (errorId));
  }
# else
  IPDUM_DUMMY_STATEMENT(errorId);       /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
# endif

#else
  IPDUM_DUMMY_STATEMENT(PdumTxPduId);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  IPDUM_DUMMY_STATEMENT(PduInfoPtr);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif
  return retVal;
}

#if (IPDUM_TRIGGER_TRANSMIT_API == STD_ON)
/*******************************************************************************************
 *  IpduM_TriggerTransmit()
*******************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, IPDUM_CODE) IpduM_TriggerTransmit(PduIdType TxPduId, P2VAR(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr)
{
  Std_ReturnType retVal = E_NOT_OK;

# if (IPDUM_TXLOINFOWITHINVALIDINDEXES == STD_ON) /* COV_IPDUM_VAR_DEPENDENT_SWITCH */
  uint8 errorId = IPDUM_E_NO_ERROR;
#  if (IPDUM_DEV_ERROR_DETECT == STD_ON)
  if(!IpduM_IsInitialized())
  {
    errorId = IPDUM_E_UNINIT;
  }
  else if((TxPduId >= IpduM_GetSizeOfTxLoInfoWithInvalidIndexes())
#   if (IPDUM_INVALIDHNDOFTXLOINFOWITHINVALIDINDEXES == STD_ON)
          || (IpduM_IsInvalidHndOfTxLoInfoWithInvalidIndexes(TxPduId))
#   endif
    )
  {
    errorId = IPDUM_E_PARAM;
  }
  else if((PduInfoPtr == NULL_PTR) || (PduInfoPtr->SduDataPtr == NULL_PTR))
  {
    errorId = IPDUM_E_PARAM_POINTER;
  }
  else
#  endif
  {
    switch (IpduM_GetPathwayTypeOfCTxLoInfoOfTxLoInfoWithInvalidIndexes(TxPduId))
    {
#  if (IPDUM_EXISTS_MUX_PATHWAYTYPEOFCTXLOINFO == STD_ON)
      case IPDUM_MUX_PATHWAYTYPEOFCTXLOINFO:
      {
        retVal = IpduM_MuxTriggerTransmit(IpduM_GetTxPathwayIdxOfCTxLoInfoOfTxLoInfoWithInvalidIndexes(TxPduId), PduInfoPtr); /* SBSW_IPDUM_FUNCTIONCALL_PDUINFOPTR_CHECKED_BY_CALLER */
        break;
      }
#  endif
#  if (IPDUM_EXISTS_CONTAINER_PATHWAYTYPEOFCTXLOINFO == STD_ON)
      case IPDUM_CONTAINER_PATHWAYTYPEOFCTXLOINFO:
      {
        retVal = IpduM_ContainerTriggerTransmit(IpduM_GetTxContainerPduIdxOfCTxLoInfoOfTxLoInfoWithInvalidIndexes(TxPduId), PduInfoPtr); /* SBSW_IPDUM_FUNCTIONCALL_PDUINFOPTR_CHECKED_BY_CALLER */
        break;
      }
#  endif
      default: /* COV_IPDUM_MISRA */
      {
        break; /* PRQA S 2880 */ /* MD_IpduM_2880 */
      }
    }
  }
#  if (IPDUM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != IPDUM_E_NO_ERROR)
  {
    IpduM_Det_ReportError(IPDUM_APIID_TRIGGERTRANSMIT, (errorId));
  }
#  else
  IPDUM_DUMMY_STATEMENT(errorId);      /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#  endif
# endif
  IPDUM_DUMMY_STATEMENT(TxPduId);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  IPDUM_DUMMY_STATEMENT(PduInfoPtr);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  return retVal;
}
#endif

#if(IPDUM_TX_CONFIRMATION_API == STD_ON)
/*******************************************************************************************
 *  IpduM_TxConfirmation()
*******************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, IPDUM_CODE) IpduM_TxConfirmation(PduIdType TxPduId)
{
  uint8 errorId = IPDUM_E_NO_ERROR;
# if (IPDUM_TXLOINFOWITHINVALIDINDEXES == STD_ON) /* COV_IPDUM_VAR_DEPENDENT_SWITCH */
#  if (IPDUM_DEV_ERROR_DETECT == STD_ON)
  if(!IpduM_IsInitialized())
  {
    errorId = IPDUM_E_UNINIT;
  }
  else if(TxPduId >= IpduM_GetSizeOfTxLoInfoWithInvalidIndexes())
  {
    errorId = IPDUM_E_PARAM;
  }
#   if (IPDUM_INVALIDHNDOFTXLOINFOWITHINVALIDINDEXES == STD_ON)
  else if(IpduM_IsInvalidHndOfTxLoInfoWithInvalidIndexes(TxPduId))
  {
    errorId = IPDUM_E_PARAM;
  }
#   endif
  else
#  endif
  {
    switch (IpduM_GetPathwayTypeOfCTxLoInfoOfTxLoInfoWithInvalidIndexes(TxPduId))
    {
#  if ((IPDUM_TXCONFIRMATIONTIMEOUTOFTXPATHWAY == STD_ON) || (IPDUM_TXCONFIRMATIONOFTXPART == STD_ON))
      case IPDUM_MUX_PATHWAYTYPEOFCTXLOINFO:
      {
        IpduM_MuxTxConfirmation(TxPduId);
        break;
      }
#  endif
#  if (IPDUM_EXISTS_CONTAINER_PATHWAYTYPEOFCTXLOINFO == STD_ON)
      case IPDUM_CONTAINER_PATHWAYTYPEOFCTXLOINFO:
      {
        IpduM_ContainerTxConfirmation(TxPduId);
        break;
      }
#  endif
      default: /* COV_IPDUM_MISRA */
      {
        break; /* PRQA S 2880 */ /* MD_IpduM_2880 */
      }
    }
  }
#  if (IPDUM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != IPDUM_E_NO_ERROR)
  {
    IpduM_Det_ReportError(IPDUM_APIID_TXCONFIRMATION, (errorId));
  }
#  endif
# endif
  IPDUM_DUMMY_STATEMENT(errorId);       /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  IPDUM_DUMMY_STATEMENT(TxPduId);       /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}
#endif

/*******************************************************************************************
 *  IpduM_RxIndication()
*******************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, IPDUM_CODE) IpduM_RxIndication(PduIdType RxPduId, P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr)
{
#if (IPDUM_RXINFO == STD_ON)
  uint8 errorId = IPDUM_E_NO_ERROR;
# if (IPDUM_DEV_ERROR_DETECT == STD_ON)
  if(!IpduM_IsInitialized())
  {
    errorId = IPDUM_E_UNINIT;
  }
  else if((RxPduId >= IpduM_GetSizeOfRxInfo())
#  if (IPDUM_INVALIDHNDOFRXINFO == STD_ON)
          || (IpduM_IsInvalidHndOfRxInfo(RxPduId))
#  endif
    )
  {
    errorId = IPDUM_E_PARAM;
  }
  else if((PduInfoPtr == NULL_PTR) || (PduInfoPtr->SduDataPtr == NULL_PTR))
  {
    errorId = IPDUM_E_PARAM_POINTER;
  }
  else
# endif
  {
    IpduM_RxPathwayIndIdxOfRxInfoType rxPathwayIndIdx = IpduM_GetRxPathwayIndIdxOfRxInfo(RxPduId);
    switch (IpduM_GetPathwayTypeOfRxInfo(RxPduId))
    {
# if (IPDUM_EXISTS_MUX_PATHWAYTYPEOFRXINFO == STD_ON)
      case IPDUM_MUX_PATHWAYTYPEOFRXINFO:
      {
        IpduM_MuxRxIndication(rxPathwayIndIdx, PduInfoPtr); /* SBSW_IPDUM_FUNCTIONCALL_PDUINFOPTR_CHECKED_BY_CALLER */
        break;
      }
# endif
# if (IPDUM_EXISTS_CONTAINER_PATHWAYTYPEOFRXINFO == STD_ON)
      case IPDUM_CONTAINER_PATHWAYTYPEOFRXINFO:
      {
        errorId = IpduM_ContainerRxIndication(rxPathwayIndIdx, PduInfoPtr); /* SBSW_IPDUM_FUNCTIONCALL_PDUINFOPTR_CHECKED_BY_CALLER */
        break;
      }
# endif
      default: /* COV_IPDUM_MISRA */
      {
        break; /* PRQA S 2880 */ /* MD_IpduM_2880 */
      }
    }
  }

# if (IPDUM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != IPDUM_E_NO_ERROR)
  {
    IpduM_Det_ReportError(IPDUM_APIID_RXINDICATION, (errorId));
  }
# else
  IPDUM_DUMMY_STATEMENT(errorId);      /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */  /* lint -e{438} */
# endif

#else
  IPDUM_DUMMY_STATEMENT(RxPduId);       /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  IPDUM_DUMMY_STATEMENT(PduInfoPtr);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif
}

#if (IPDUM_VERSION_INFO_API == STD_ON)
/*******************************************************************************************
 *  IpduM_GetVersionInfo()
*******************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, IPDUM_CODE) IpduM_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, IPDUM_APPL_DATA) versioninfo)
{
  uint8 errorId = IPDUM_E_NO_ERROR;
# if (IPDUM_DEV_ERROR_DETECT == STD_ON)
  if(versioninfo == NULL_PTR)
  {
    errorId = IPDUM_E_PARAM_POINTER;
  }
  else
# endif
  {
    /* Set version info / fill struct */
    versioninfo->vendorID = (uint16) IPDUM_VENDOR_ID;   /* SBSW_IPDUM_GETVERSION_PARAM */
    versioninfo->moduleID = (uint8) IPDUM_MODULE_ID;    /* SBSW_IPDUM_GETVERSION_PARAM */
    versioninfo->sw_major_version = (uint8) IPDUM_SW_MAJOR_VERSION;     /* SBSW_IPDUM_GETVERSION_PARAM */
    versioninfo->sw_minor_version = (uint8) IPDUM_SW_MINOR_VERSION;     /* SBSW_IPDUM_GETVERSION_PARAM */
    versioninfo->sw_patch_version = (uint8) IPDUM_SW_PATCH_VERSION;     /* SBSW_IPDUM_GETVERSION_PARAM */
  }
# if (IPDUM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != IPDUM_E_NO_ERROR)
  {
    IpduM_Det_ReportError(IPDUM_APIID_VERSIONINFO, (errorId));
  }
# else
  IPDUM_DUMMY_STATEMENT(errorId);       /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
# endif
}
#endif

#define IPDUM_STOP_SEC_CODE
#include "MemMap.h"    /* PRQA S 5087 */        /*  MD_MSR_MemMap */

/**********************************************************************************************************************
 * GLOBAL MISRA / PCLINT JUSTIFICATION
 *********************************************************************************************************************/
/* *INDENT-OFF* */
/* module specific MISRA deviations:
   MD_IpduM_2880: Misra Rule 2.1
     Reason:      Default statement needed because of Misra, but the default statement is never reached.
     Risk:        No risk.
     Prevention:  No prevention necessary.
*/

/* SBSW_JUSTIFICATION_BEGIN
  \ID SBSW_IPDUM_FUNCTIONCALL_PDUINFOPTR_CHECKED_BY_CALLER
    \DESCRIPTION Function is called with an ID and a pointer.
    \COUNTERMEASURE \N Both the ID and the pointer are checked by the caller of this function.

  \ID SBSW_IPDUM_FUNCTIONCALL_PDUINFOPTR_SELF_CONSTRUCTED
    \DESCRIPTION Function is called with an ID and a pointer.
    \COUNTERMEASURE \N The pointer is constructed in the calling function and always valid.
                       The ID is checked by the caller of this function.

  \ID SBSW_IPDUM_FUNCTIONCALL_PDUINFOPTR_EMPTY
    \DESCRIPTION Function is called with an ID and a pointer.
    \COUNTERMEASURE \N The pointer is always valid and because of zero length will never be actually read.
                       The ID is checked by the caller of this function.

  \ID SBSW_IPDUM_VSTDLIB_SAFE
    \DESCRIPTION       Pointer is passed as function argument.
    \COUNTERMEASURE \N The VStdLib_MemCpy_s guarantees that the destination pointer is not overwritten.

  \ID SBSW_IPDUM_MAINFUNCTIONRX_CALL_UNPACKRXCONTAINERPDU
    \DESCRIPTION IpduM_ContainerRx_UnpackContainerPdu is called with an ID and a pointer.
    \COUNTERMEASURE \N The ID is verified by ComStackLib, the pointer is calculated using generated
                       ComStackLib structures and the ID.

  \ID SBSW_IPDUM_FILLLASTISBEST_CALL_CONTAINERWRITEHEADER
    \DESCRIPTION IpduM_ContainerTx_WriteHeader is called with two pointers, and two lengths. The header
                 pointer is local/static and always correct and the headersize always matches.
    \COUNTERMEASURE \N The parameter lastIsBestBuffer is generated large enough to fit any configured PDU
                       and the last parameter, freeBytes, is calculated using the size of the buffer passed
                       to this function. The caller verifies the size matches.

  \ID SBSW_IPDUM_FILLLASTISBEST_MEMORY_WRITE
    \DESCRIPTION An array is written using a calculated index.
    \COUNTERMEASURE \N The index is the iterator in a for-loop that always starts at or after the start
                       position of the buffer and always ends at its end at the latest.

  \ID SBSW_IPDUM_CSL01
    \DESCRIPTION Index Access is using ComStackLib, using boundary check with getSizeOf macro.
    \COUNTERMEASURE  \N Qualified use-case CSL01 of ComStackLib.

  \ID SBSW_IPDUM_CSL02
    \DESCRIPTION  Access of Table1,  with the same index as Table2 using ComStackLib. (arrays of same size)
    \COUNTERMEASURE \N Qualified use-case CSL02 of ComStackLib

  \ID SBSW_IPDUM_CSL03
    \DESCRIPTION Access to Table1 via indirection over Table2. (modelled indirections)
    \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

  \ID SBSW_IPDUM_CSL_VAR_ACCESS
    \DESCRIPTION A ComStackLib generated variable is accessed.
    \COUNTERMEASURE \N The variable is written using a generated macro of the CSL. It immediately dereferences the variables address without pointer arithmetic.

  \ID SBSW_IPDUM_GETVERSION_PARAM
    \DESCRIPTION    The IpduM_GetVersionInfo writes to the 'versioninfo' pointer parameter. It is checked against NULL,
                    but this does not guarantee that the referenced memory is valid.
    \COUNTERMEASURE \N  Pointers passed to public IpduM APIs point to a valid memory range. A general countermeasure is included in the safety manual.

  \ID SBSW_IPDUM_DIRECT_ACCESS_FROM_EXTERNAL_PARAMETER
    \DESCRIPTION Structure is accessed using an index.
    \COUNTERMEASURE \N Index is an external parameter. The caller verifies the external parameter.
                       This caller can either be an external module or another IpduM function.

  \ID SBSW_IPDUM_INDIRECT_ACCESS_FROM_EXTERNAL_PARAMETER
    \DESCRIPTION Structure is accessed using an index.
    \COUNTERMEASURE \N Index is derived through ComStackLib indirections from an external parameter. The original caller
                       verifies the external parameter. This original caller can either be an external module or another
                       IpduM function.
                       Qualified use-case CSL03.

  \ID SBSW_IPDUM_COPYSEGMENTS
    \DESCRIPTION The memory location is used for an array write access using the IDs.
    \COUNTERMEASURE \N The destPtr and srcPtr are not checked against NULL_PTR. The caller of this local function checks them.
                       The segmentStartIdx and segmentEndIdx are checked by the caller of this local function.

  \ID SBSW_IPDUM_JITTRIGGERTRANSMIT_CALL_COPYSEGMENTS
    \DESCRIPTION IpduM_CopySegments is called with two indices and two pointers.
    \COUNTERMEASURE \N The indices and the first pointer are calculated using ComStackLib indirections
                       based on the function parameters txPartId and txPathwayId. These parameters and
                       the second pointer are checked by the caller of this local function.

  \ID SBSW_IPDUM_MUXTRANSMIT_CALL_JITUPDATE
    \DESCRIPTION IpduM_JitUpdate is called with two indices, a pointer and a boolean value.
    \COUNTERMEASURE \N One index is a function parameter, the other one derived from it using
                       ComStackLib indirections, the pointer is also created using ComStackLib
                       indirections based on the parameter txPartId and the boolean value is
                       always right. The caller checks the parameter txPartId.

  \ID SBSW_IPDUM_MUXTRIGGERTRANSMIT_CALL_JITUPDATE
    \DESCRIPTION IpduM_JitUpdate is called with two indices, a pointer and a boolean value.
    \COUNTERMEASURE \N One index is a function parameter, the other one is static, the pointer
                       is created using ComStackLib indirections based on the parameter txPathwayHnd
                       and the boolean value is always right. The caller checks the parameter txPathwayHnd.

  \ID SBSW_IPDUM_MUXTRANSMIT_CALL_COPYSEGMENTS
    \DESCRIPTION IpduM_CopySegments is called with two IDs and two pointers.
    \COUNTERMEASURE \N The IDs and the first pointer are generated structures using the ComStackLib based on
                       the same objects, they always match. The PduInfoPtr is checked against NULL_PTR
                       by the caller.

  \ID SBSW_IPDUM_MUXTRANSMIT_CALL_MUXFILLERSEGMENTS
    \DESCRIPTION IpduM_CopySegments is called with three IDs and one pointer.
    \COUNTERMEASURE \N The IDs and the pointer are generated structures using the ComStackLib based on
                       the same objects, they always match.

  \ID SBSW_IPDUM_MUXTRANSMIT_CALL_PDURTRANSMIT
    \DESCRIPTION PduR_IpduMTransmit is called with an ID and a pointer. The pointer is built using
                 ComStackLib-generated data structures and is always valid.
    \COUNTERMEASURE \N The ID is a SNV provided by PduR. The PduR ensures that the SNV is valid.

  \ID SBSW_IPDUM_MUXTRIGGERTRANSMIT_MEMORY_WRITE
    \DESCRIPTION An array is written using an index.
    \COUNTERMEASURE \N The pointer and index are validated by the caller and are always correct.

  \ID SBSW_IPDUM_MUXRXINDICATION_CALL_COPYSEGMENTS
    \DESCRIPTION IpduM_CopySegments is called with two IDs and two pointers.
    \COUNTERMEASURE \N The IDs and the first pointer are generated structures using the ComStackLib based on
                       the same objects, they always match. The PduInfoPtr is not checked against NULL_PTR
                       and must be checked by the caller. The consistency of pduInfo pointer is ensured by this local function.

  \ID SBSW_IPDUM_MUXRXINDICATION_CALL_PDURRXINDICATION
    \DESCRIPTION PduR_IpduMRxIndication is called with an ID and a pointer.
    \COUNTERMEASURE \N The ID is a SNV provided by PduR. The PduR ensures that the SNV is valid.
                       The PduInfoPtr is built using ComStackLib-generated data structures and is
                       always valid. The length however is taken from the parameter PduInfoPtr and
                       is checked by the caller of this local function. The consistency of this pointer is ensured by this local function.

  \ID SBSW_IPDUM_ARRAY_WRITE_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER
    \DESCRIPTION Array is written with index access.
    \COUNTERMEASURE \R Additional variable passed along with the array is checked by caller to reflect the remaining
                       space in the array. This variable is used for run-time checks.

  \ID SBSW_IPDUM_TRANSMITCURRCONTAINERPDU_CALL_CONTAINERWRITEHEADER
    \DESCRIPTION IpduM_ContainerTx_WriteHeader is called with two pointers, and two lengths. The header
                 pointer is local/static and always correct and the headersize always matches.
    \COUNTERMEASURE \N The parameters pContainerTxBuf and freeBytes are calculated using ComStackLib
                       indirections based on the function parameter txContainerId. The parameters are
                       checked prior to calling this local function.

  \ID SBSW_IPDUM_TRANSMITCURRCONTAINERPDU_CALL_CALCULATESIZEOFCONTAINER
    \DESCRIPTION IpduM_CalculateSizeOfContainer is called with an ID and a pointer.
    \COUNTERMEASURE \N The pointer is built using ComStackLib indirections based on the function parameter
                       txContainerId, which also is the ID used here. This parameter is checked prior to
                       calling this local function.

  \ID SBSW_IPDUM_TRANSMITCURRCONTAINERPDU_CALL_PDURTRANSMIT
    \DESCRIPTION PduR_IpduMTransmit is called with an ID and a pointer. The pointer is built using
                 ComStackLib-generated data structures based on the function parameter txContainerId.
                 This parameter is checked prior to calling this local function.
    \COUNTERMEASURE \N The ID is a SNV provided by PduR. The PduR ensures that the SNV is valid.

  \ID SBSW_IPDUM_GETTRANSMITTEDPDULENGTH
    \DESCRIPTION IpduM_ContainerTx_GetTransmittedPduLength is called with an ID and a pointer. The pointer is built using
                 ComStackLib-generated data structures based on the function parameter txContainerId.
    \COUNTERMEASURE \N The ID is a SNV provided by PduR. The PduR ensures that the SNV is valid.

  \ID SBSW_IPDUM_TRANSMIT_CURR_CONTAINER_PDU_MEMCPY
    \DESCRIPTION MemCpy is called with two pointers and a length.
    \COUNTERMEASURE \N The first pointer is generated large enough for the largest possible number of items, ensured during
                       generation. The second pointer and length always match as they are generated using the ComStackLib.

  \ID SBSW_IPDUM_TRANSMITQUEUEDCONTAINERPDU_CALL_CALCULATESIZEOFCONTAINER
    \DESCRIPTION IpduM_CalculateSizeOfContainer is called with an ID and a pointer.
    \COUNTERMEASURE \N The pointer is built using ComStackLib indirections based on the function parameter
                       txContainerId, which also is the ID used here. This parameter is checked prior to
                       calling this local function. The pointer offset
                       is verified using CSL01 use case of ComStackLib.

  \ID SBSW_IPDUM_TRANSMITQUEUEDCONTAINERPDU_CALL_PDURTRANSMIT
    \DESCRIPTION PduR_IpduMTransmit is called with an ID and a pointer. The pointer is built using
                 ComStackLib-generated data structures based on the function parameter txContainerId.
                 This parameter is checked prior to calling this local function.
    \COUNTERMEASURE \N The ID is a SNV provided by PduR. The PduR ensures that the SNV is valid.
                       the pointer offset is verified using CSL01 use case of ComStackLib.

  \ID SBSW_IPDUM_ARRAY_WRITE_WITH_INDEX_CHECK
    \DESCRIPTION Array is accessed with index access.
    \COUNTERMEASURE \R The index is checked with a runtime-check to be within the buffer.

  \ID SBSW_IPDUM_CONTAINER_TRANSMIT_INDIRECT_ACCESS
    \DESCRIPTION The parameter txContainedId is used as an ID to access generated structures.
    \COUNTERMEASURE \N The caller ensures the txContainedId parameter contains the correct value.

  \ID SBSW_IPDUM_CONTAINER_TRANSMIT_CALL_CALCULATESIZEOFCONTAINER
    \DESCRIPTION IpduM_CalculateSizeOfContainer is called with an ID and a pointer.
    \COUNTERMEASURE \N The pointer is built using ComStackLib indirections based on the function parameter
                       txContainerId, which also is the ID used here. This parameter is checked prior to
                       calling this local function. The pointer is only
                       read by the called function, never written. There cannot be any out of bounds write access.

  \ID SBSW_IPDUM_CONTAINER_TRANSMIT_CALL_PDURTRANSMIT
    \DESCRIPTION PduR_IpduMTransmit is called with an ID and a pointer. The pointer is built using
                 ComStackLib-generated data structures based on the function parameter txContainerId.
                 This parameter is checked prior to calling this local function.
    \COUNTERMEASURE \N The ID is a SNV provided by PduR. The PduR ensures that the SNV is valid. The pointer is only
                       read by the called function, never written. There cannot be any out of bounds write access.

  \ID SBSW_IPDUM_CONTAINER_TRANSMIT_INCREMENT_CALCULATED_POSITION
    \DESCRIPTION A value in an array is incremented, the position in the array is calculated.
    \COUNTERMEASURE \N The position is calculated using the start position and an offset (currentInstance). The
                       start position is retrieved using ComStackLib functions and a parameter (verified by caller),
                       the offset is a write index within a cyclic buffer, the code parts setting this index were
                       reviewed and tested, and the maximum value matches the array size, ensured during generation.

  \ID SBSW_IPDUM_CONTAINERTRIGGERTRANSMIT_PTR_WRITE
    \DESCRIPTION Data is written to a pointer.
    \COUNTERMEASURE \N The caller of this local function ensures this is a valid pointer.

  \ID SBSW_IPDUM_QUEUECURRCONTAINERPDU_CALL_CONTAINERWRITEHEADER
    \DESCRIPTION IpduM_ContainerTx_WriteHeader is called with two pointers, and two lengths. The header
                 pointer is local/static and always correct and the headersize always matches.
    \COUNTERMEASURE \N The parameters pContainerTxBuf and freeBytes are calculated using ComStackLib
                       indirections based on the function parameter txContainerId. The parameters are
                       checked prior to calling this local function (IpduM_ContainerTx_DataQueue_QueueCurrContainerPdu).

  \ID SBSW_IPDUM_ADDTXPDUTOCURRCONTAINER_CALL_CONTAINERWRITEHEADER
    \DESCRIPTION IpduM_ContainerTx_WriteHeader is called with two pointers, and two lengths.
    \COUNTERMEASURE \N The parameters pContainerTxBuf, header and freeBytes are calculated using
                       ComStackLib indirections based on the function parameter txContainedId. The
                       parameter headerSize is calculated using the local function IpduM_ContainerTx_GetHeaderSize()
                       using ComStackLib indirections based on the function parameter txContainedId. The
                       calculated headerSize is one of two possible, pre-defined values and both are safe
                       because of the freeBytes parameter verifying there is sufficient space. The input
                       parameters are checked prior to calling this local function
                       (IpduM_ContainerTx_DataQueue_AddTxPduToCurrContainer).

  \ID SBSW_IPDUM_UNPACKRXCONTAINERPDU_CALL_PDURRXINDICATION
    \DESCRIPTION PduR_IpduMRxIndication is called with an ID and a pointer. The pointer is given by
                 the calling function that ensures it is correct.
    \COUNTERMEASURE \N The ID is a SNV provided by PduR. The PduR ensures that the SNV is valid.

  \ID SBSW_IPDUM_CONTAINERRXINDICATION_MEMORY_WRITE
    \DESCRIPTION An array is written using a calculated index.
    \COUNTERMEASURE \N The index is the iterator in a for-loop that always starts at or after the start
                       position of the buffer and always ends at its end at the latest.

  \ID SBSW_IPDUM_CONTAINERRXINDICATION_CALL_ENQUEUERXCONTAINER
    \DESCRIPTION IpduM_ContainerRx_EnqueueContainer is called with an ID and a pointer.
    \COUNTERMEASURE \N The ID is verified by the caller, the pointer is built using ComStackLib indirections
                       and a passed pointer from the caller. The caller verifies the pointer.

  \ID SBSW_IPDUM_CONTAINERRXINDICATION_CALL_UNPACKRXCONTAINERPDU
    \DESCRIPTION IpduM_ContainerRx_UnpackContainerPdu is called with an ID and a pointer.
    \COUNTERMEASURE \N The ID is verified by the caller, the pointer is built using ComStackLib indirections
                       and a passed pointer from the caller. The caller verifies the pointer.

  \ID SBSW_IPDUM_REQUESTQUEUE_WRITEIDX
    \DESCRIPTION The WriteIdxOfTxRequestQueueInfo is used to write at GetAddrTxRequestQueue(requestQueueStartIdx). 
    \COUNTERMEASURE \N The WriteIdx is initialized with 0 and checked to be within allowed range directly
                       after every increment. All values for offsets and sizes are generated by ComStackLib using
                       size relations, so those values always match.

   SBSW_JUSTIFICATION_END */
   
/* VCA Justifications

  \ID VCA_IPDUM_VSTDLIB_MEMCPY_SAFE
    \DESCRIPTION       Pointer is passed as function argument.
    \COUNTERMEASURE \N The VStdLib_MemCpy_s guarantees that the destination pointer is not overwritten.

  \ID VCA_IPDUM_VSTDLIB_MEMCPY
    \DESCRIPTION       MemCpy is called with two pointers and a length.
    \COUNTERMEASURE \N The first pointer is generated large enough for the largest possible number of items, ensured during
                       generation. The second pointer and length always match as they are generated using the ComStackLib.

  \ID VCA_IPDUM_FUNCTIONCALL_PDUINFOPTR_CHECKED_BY_CALLER
    \DESCRIPTION       Function is called with an ID and a pointer.
    \COUNTERMEASURE \N Both the ID and the pointer are checked by the caller of this function.

  \ID VCA_IPDUM_FUNCTIONCALL_PDUINFOPTR_SELF_CONSTRUCTED
    \DESCRIPTION       Function is called with an ID and a pointer.
    \COUNTERMEASURE \N The pointer is constructed in the calling function and always valid.
                       The ID is checked by the caller of this function or derived via Indirections and GetSizeOfMacros of the Comstacklib from an external ID.

  \ID VCA_PDUINFOPTR_SELF_CONSTRUCTED
    \DESCRIPTION       Written to PduInfoPtr.
    \COUNTERMEASURE \N The pointer is constructed in the calling function and always valid.

  \ID VCA_IPDUM_FUNCTIONCALL_WITH_ONLY_ID
    \DESCRIPTION Function is called with an ID.
    \COUNTERMEASURE \N The ID is checked by the caller of this function or derived  via Indirections or GetSizeOfMacros of the Comstacklib from an external ID.

  \ID VCA_IPDUM_READING_OF_BEFORE_WRITTEN_ID
    \DESCRIPTION       Structure is accessed using an index.
    \COUNTERMEASURE \N The index is read from an array using Comstacklib Macros. The Index written to this array is derived through ComStackLib indirections from
                       an external parameter or using the GetSizeOfMacro of the Comstacklib. The original caller verifies the external parameter.

  \ID VCA_IPDUM_ARRAY_WRITE_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER
    \DESCRIPTION       Array is written with index access.
    \COUNTERMEASURE \R Additional variable passed along with the array is checked by caller to reflect the remaining
                       space in the array. This variable is used for run-time checks.

  \ID VCA_IPDUM_ARRAY_READ_WITH_SIZE_VARIABLE_CHECKED_BY_CALLER
    \DESCRIPTION       Array is read with index access.
    \COUNTERMEASURE \R The size of the array is checked by the caller.
*/

/* COV_JUSTIFICATION_BEGIN

  \ID COV_IPDUM_EMPTY_CONFIG
    \ACCEPT TX tf tf tf tf
    \REASON Empty configurations are excluded.

  \ID COV_IPDUM_VAR_DEPENDENT_SWITCH
    \ACCEPT TX
    \ACCEPT TF tf tx
    \ACCEPT TF tx tf
    \ACCEPT TX tx tx
    \ACCEPT TX tf tf tf
    \ACCEPT TX tx tf tf
    \ACCEPT TF tx tf tf
    \REASON The nested switch depends on a previous switch.

  \ID COV_IPDUM_COMPLEMENTARY_CHECK
    \ACCEPT TF tf tx tf
    \REASON This condition (a || (!a && b)) cannot be fully covered for a==true because the first condition (before the "||") will always match, so the second (!a) is not evaluated.

  \ID COV_IPDUM_PRECOMPILE_CONFIG
    \ACCEPT XF
    \REASON Precompile configurations are always initialized with a NULL config pointer.

  \ID COV_IPDUM_NO_DEV_ERROR
    \ACCEPT XF
    \REASON Only tests with erroneous configurations would cover this.

  \ID COV_IPDUM_TXCONF_ALWAYS_ZERO
    \ACCEPT XF
    \ACCEPT TX tx xx xx
    \ACCEPT TF tf tx tf
    \REASON A TxConfirmation Timeout of zero is a special value which is used for unused TxConfirmation Timeouts.

  \ID COV_IPDUM_DEFENSIVE_PROGRAMMING
    \ACCEPT TX
    \ACCEPT XF
    \ACCEPT TF tf tx
    \ACCEPT TX tx tx
    \REASON This condition is used because of safe programming, should never be false in production code.

  \ID COV_IPDUM_MISRA
    \ACCEPT X
    \ACCEPT TX
    \REASON [MSR_COV_MISRA]

COV_JUSTIFICATION_END */

/* *INDENT-ON* */

/**********************************************************************************************************************
  END OF FILE: IpduM.c
**********************************************************************************************************************/
