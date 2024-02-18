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
 *         File:  PduR.c
 *      Project:  Gw_AsrPduRCfg5
 *       Module:  MICROSAR PDU Router
 *    Generator:  Configurator 5
 *
 *  Description:  Vector implementation of AUTOSAR PDU Router
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

/**********************************************************************************************************************
 * LOCAL MISRA / PCLINT JUSTIFICATION
 *********************************************************************************************************************/


#define PDUR_SOURCE
/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "PduR.h"
#include "PduR_Bm.h"
#include "PduR_Fm.h"
#include "PduR_IFQ.h"
#include "PduR_Sm.h"
#include "PduR_RmIf.h"
#include "PduR_RmTp.h"
#include "PduR_RmTp_TxInst.h"
#include "PduR_McQ.h"
#include "PduR_Lock.h"
#include "SchM_PduR.h"

#if(PDUR_MULTICORE == STD_ON)
# include "Os.h"
#endif

#if ((PDUR_BSWMPDURRXINDICATIONCALLBACKOFRXIF2DEST == STD_ON) || (PDUR_BSWMPDURTPRXINDICATIONCALLBACKOFRXTP2DEST == STD_ON) || (PDUR_BSWMPDURTPSTARTOFRECEPTIONCALLBACKOFRXTP2DEST == STD_ON) || (PDUR_BSWMPDURTRANSMITCALLBACKOFTX2LO == STD_ON) || (PDUR_BSWMPDURTXCONFIRMATIONCALLBACKOFTXIF2UP == STD_ON) || (PDUR_BSWMPDURTPTXCONFIRMATIONCALLBACKOFTXTP2SRC == STD_ON) || (PDUR_BSWMPDURPRETRANSMITCALLBACKOFRMDESTROM == STD_ON))
# include "BswM_PduR.h"
#endif

#if(PDUR_USE_ECUM_BSW_ERROR_HOOK == STD_ON)
# include "EcuM_Error.h"
#endif

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
/* Check the version of PduR header file */
#if (  (PDUR_SW_MAJOR_VERSION != (16u)) \
    || (PDUR_SW_MINOR_VERSION != (2u)) \
    || (PDUR_SW_PATCH_VERSION != (0u)) )
# error "Vendor specific version numbers of PduR.c and PduR.h are inconsistent"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * LOCAL FUNCTION MACROS
 *********************************************************************************************************************/
#if !defined (PDUR_LOCAL_INLINE)
# define PDUR_LOCAL_INLINE LOCAL_INLINE
#endif

/**********************************************************************************************************************
 * LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"    /* PRQA S 5087 */        /* MD_MSR_MemMap */

/**********************************************************************************************************************
  PduR_InitMemorySection
**********************************************************************************************************************/
/*! \brief       This function initializes the PDUR
 *  \details     Initializes all component variables of a specific memory section and sets the component state to initialized.
 *  \param[in]   memIdx   memory section index
 *  \pre         Interrupts are disabled.
 *  \pre         Module is uninitialized.
 *  \pre         PduR_InitMemory has been called unless PduR_ModuleInitialized is initialized by start-up code.
 *  \pre         PduR_PreInit has been called.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 ********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_InitMemorySection(PduR_MemIdxType memIdx);

#if(PDUR_RPGROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Init_RmDestRpgRom
 *********************************************************************************************************************/
/*! \brief      This function initializes the PDUR routing path groups.
 *  \details    -
 *  \param[in]  memIdx  memory section index
 *  \pre        PduR_InitMemory() has been executed, if the start up code does not initialize variables.
 *  \note       The function must be called on task level and has not to be interrupted.
 *              by other administrative function calls.
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Init_RmDestRpgRom(PduR_MemIdxType memIdx);
#endif

#if(PDUR_RMGDESTNTO1INFORAMIDXOFRMGDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Rm_MultipleSourceHandler_Init
 *********************************************************************************************************************/
/*! \brief      This function initializes the PDUR fan in RAM variables.
 *  \details    -
 *  \param[in]  memIdx  memory section index
 *  \pre        PduR_InitMemory() has been executed, if the start up code does not initialize variables.
 *  \note       The function must be called on task level and has not to be interrupted
 *              by other administrative function calls.
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Rm_MultipleSourceHandler_Init(PduR_MemIdxType memIdx);
#endif

#if ((PDUR_IFCANCELTRANSMITSUPPORTEDOFMMROM == STD_ON) || (PDUR_TPCANCELTRANSMITSUPPORTEDOFMMROM == STD_ON))
/**********************************************************************************************************************
 * PduR_Rm_CancelTransmit_MultiDest
 *********************************************************************************************************************/
/*!
 * \brief    The function calls the CancelTransmit function for every destination
 * \details     -
 * \param[in]   rmSrcIdx            internal RmSrcRom index
 * \return      Std_ReturnType
 *               E_OK              Cancellation was executed successfully by all the destination modules.
 *               E_NOT_OK          Cancellation was rejected by the destination module.
 * \pre         -
 * \context     TASK|ISR1|ISR2
 * \reentrant   TRUE
 * \synchronous TRUE
**********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_Rm_CancelTransmit_MultiDest(PduR_RmSrcRomIterType rmSrcIdx);
#endif

#if ((PDUR_MAIN_FUNCTION == STD_ON) && ((PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)))
/**********************************************************************************************************************
  PduR_DispatchMainfuntion
**********************************************************************************************************************/
/*! \brief      This function calls the corresponding Mainfunction for the rmGDestRomIdx
 *  \details    -
 *  \param[in]  rmGDestRomIdx    internal RmGDestRom index
 *  \pre        -
 ********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_DispatchMainfuntion(PduR_RmGDestRomIterType rmGDestRomIdx);
#endif

#if(PDUR_DEFERREDEVENTCACHEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_EvC_Init
**********************************************************************************************************************/
/*! \brief      This function initializes the deferred event cache.
 *  \details    -
 *  \param[in]  memIdx  memory section index
 *  \pre        -
 ********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_EvC_Init(PduR_MemIdxType memIdx);
#endif

#if (PDUR_DEFERREDEVENTCACHEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_EvC_ReadFlush
 *********************************************************************************************************************/
/*! \brief       Flush the event queue by setting the read pointer equal to the write pointer
 *  \details     -
 *  \param[in]   deferredEventCacheIdx    Id of the correct queue to be used
 *  \param[in]   memIdx                   memory section index
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \note        This function must only be called by the reader core!
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_EvC_ReadFlush(PduR_DeferredEventCacheRomIdxOfSrcApplicationRomType deferredEventCacheIdx, PduR_MemIdxType memIdx);
#endif

#if (PDUR_DEFERREDEVENTCACHEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_EvC_GetDeferredEventCacheArrayRamReadIdxSafe
 *********************************************************************************************************************/
/*! \brief       Gets the current read idx for the queue with optional error checking.
 *  \details     -
 *  \param[in]   deferredEventCacheIdx    Id of the correct queue to be used
 *  \param[in]   memIdx                   memory section index
 *  \return      the read index
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(PduR_DeferredEventCacheArrayRamReadIdxOfDeferredEventCacheRamType, PDUR_CODE) PduR_EvC_GetDeferredEventCacheArrayRamReadIdxSafe(PduR_DeferredEventCacheRomIdxOfSrcApplicationRomType deferredEventCacheIdx, PduR_MemIdxType memIdx);
#endif

#if (PDUR_DEFERREDEVENTCACHEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_EvC_GetDeferredEventCacheArrayRamWriteIdxSafe
 *********************************************************************************************************************/
/*! \brief       Gets the current write idx for the queue with optional error checking.
 *  \details     -
 *  \param[in]   deferredEventCacheIdx    Id of the correct queue to be used
 *  \param[in]   memIdx                   memory section index
 *  \return      the write index
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(PduR_DeferredEventCacheArrayRamWriteIdxOfDeferredEventCacheRamType, PDUR_CODE) PduR_EvC_GetDeferredEventCacheArrayRamWriteIdxSafe(PduR_DeferredEventCacheRomIdxOfSrcApplicationRomType deferredEventCacheIdx, PduR_MemIdxType memIdx);
#endif

#if (PDUR_DEFERREDEVENTCACHEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_EvC_IsFull
 *********************************************************************************************************************/
/*! \brief       Checks if the queue is full.
 *  \details -
 *  \param[in]   deferredEventCacheIdx    Id of the correct queue to be used
 *  \param[in]   memIdx                   memory section index
 *  \return      true                     Queue is full.
 *               false                    Queue is not full.
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_EvC_IsFull(PduR_DeferredEventCacheRomIdxOfSrcApplicationRomType deferredEventCacheIdx, PduR_MemIdxType memIdx);
#endif

#if (PDUR_DEFERREDEVENTCACHEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_EvC_IsAnyEvCOverflowed
 *********************************************************************************************************************/
/*! \brief       Checks if any EvC for the destination application is overflowed.
 *  \details -
 *  \param[in]   destApplicationManagerRomIdx    Id of the destination application
 *  \return      true                     Any EvC is overflowed.
 *               false                    No EvC is overflowed.
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_EvC_IsAnyEvCOverflowed(PduR_DestApplicationManagerRomIterType destApplicationManagerRomIdx);
#endif

#if (PDUR_DEFERREDEVENTCACHEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_EvC_FlushAllEvCOfDestApplication
 *********************************************************************************************************************/
/*! \brief       Flushes all EvCs of the destination application.
 *  \details     -
 *  \param[in]   destApplicationManagerRomIdx    Id of the destination application
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_EvC_FlushAllEvCOfDestApplication(PduR_DestApplicationManagerRomIterType destApplicationManagerRomIdx);
#endif

#if (PDUR_DEFERREDEVENTCACHEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_EvC_ReadAndProcessEvCOfDestApplication
 *********************************************************************************************************************/
/*! \brief       Read and process the event cache of this destination application
 *  \details     -
 *  \param[in]   destApplicationManagerRomIdx    Id of the destination application
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_EvC_ReadAndProcessEvCOfDestApplication(PduR_DestApplicationManagerRomIterType destApplicationManagerRomIdx);
#endif

#if ((PDUR_MAIN_FUNCTION == STD_ON) && ((PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)))
/**********************************************************************************************************************
 * PduR_ProcessAllDestinationsOfDestApplication
 *********************************************************************************************************************/
/*! \brief       Process all destinations on this destination application
 *  \details     -
 *  \param[in]   destApplicationManagerRomIdx    Id of the destination application
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_ProcessAllDestinationsOfDestApplication(PduR_DestApplicationManagerRomIterType destApplicationManagerRomIdx);
#endif

#if (PDUR_DEFERREDEVENTCACHEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_IsRmGDestIdxValidOnApplication
 *********************************************************************************************************************/
/*! \brief       Checks if this global destination handle is assigned to the provided application.
 *  \details -
 *  \param[in]   rmGDestRomIdx    rmGDest handle id
 *  \param[in]   applicationId    application handled id
 *  \return      true             rmGDest is running on applicationId
 *               false            rmGDest is not running on applicationId
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_IsRmGDestIdxValidOnApplication(PduR_RmGDestRomIterType rmGDestRomIdx, PduR_DestApplicationManagerRomIterType applicationId);
#endif

#if(PDUR_MULTICORE == STD_ON)
/**********************************************************************************************************************
 *  PduR_CreatePartitionLookupTable
 **********************************************************************************************************************/
/*! \brief       Create the partition lookup table which maps the OsApplicationId to the internal ComStackLib Id
 *  \details     -
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_CreatePartitionLookupTable(void);
#endif

#if(PDUR_MULTICORE == STD_ON)
/**********************************************************************************************************************
 *  PduR_GetMemorySectionIndexOfOsApplication
 **********************************************************************************************************************/
/*! \brief       Get the current memory section index which is assigned to the OsApplication this function is running in.
 *  \details     -
 *  \param[in]   applicationId  Id of the OsApplication this function is running in.
 *  \return      memory section index
 *  \pre         PduR_PreInit was called before. This function calculated the mapping between OsApplicationId and the internal CSL memory section Id.
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(PduR_MemIdxType, PDUR_CODE) PduR_GetMemorySectionIndexOfOsApplication(ApplicationType applicationId);
#endif

/**********************************************************************************************************************
 *  PduR_GetMemIdx
 **********************************************************************************************************************/
/*! \brief       Get the current memory section index which is assigned to the OsApplication this function is running in.
 *  \details     For single core configuration a default value will be returned.
 *  \return      memory section index
 *  \pre         PduR_PreInit was called before. This function calculated the mapping between OsApplicationId and the internal CSL memory section Id.
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(PduR_MemIdxType, PDUR_CODE) PduR_GetMemIdx(void);

/**********************************************************************************************************************
 * LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * GLOBAL AND LOCAL FUNCTIONS
 *********************************************************************************************************************/
#if(PDUR_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 * PduR_GetVersionInfo
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, PDUR_APPL_DATA) versionInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = PDUR_E_NO_ERROR;      /* PRQA S 2981 */ /* MD_MSR_RetVal */
# if (PDUR_DEV_ERROR_DETECT == STD_ON)  /* COV_PDUR_VAR_DEV_ERROR_DETECT */
  /* Check parameter 'ConfigPtr' */
  if(versionInfo == NULL_PTR)
  {
    errorId = PDUR_E_PARAM_POINTER;
  }
  else
# endif
  {
    versionInfo->vendorID = (uint16) PDUR_VENDOR_ID;    /* SBSW_PDUR_GETVERSION_PARAM */
    versionInfo->moduleID = (uint8) PDUR_MODULE_ID;     /* SBSW_PDUR_GETVERSION_PARAM */
    versionInfo->sw_major_version = (uint8) PDUR_SW_MAJOR_VERSION;      /* SBSW_PDUR_GETVERSION_PARAM */
    versionInfo->sw_minor_version = (uint8) PDUR_SW_MINOR_VERSION;      /* SBSW_PDUR_GETVERSION_PARAM */
    versionInfo->sw_patch_version = (uint8) PDUR_SW_PATCH_VERSION;      /* SBSW_PDUR_GETVERSION_PARAM */
  }
  /* ----- Development Error Report --------------------------------------- */
# if (PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR)
  {
    PduR_Det_ReportError(PDUR_FCT_VERSIONINFO, errorId);
  }
# else
  PDUR_DUMMY_STATEMENT(errorId);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
# endif
}       /* End of PduR_GetVersionInfo() */
#endif

/**********************************************************************************************************************
 * PduR_GetConfigurationId
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
FUNC(PduR_PBConfigIdType, PDUR_CODE) PduR_GetConfigurationId(void)
{
  uint16 configID = 0u;         /* PRQA S 2981 */ /* MD_MSR_RetVal */
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = PDUR_E_NO_ERROR;      /* PRQA S 2981 */ /* MD_MSR_RetVal */

  if(!PduR_IsPreInitialized())
  {
    errorId = PDUR_E_INVALID_REQUEST;
  }
  else if(!PduR_IsInitialized(PduR_GetMemIdx()))
  {
    errorId = PDUR_E_INVALID_REQUEST;
  }
  else
  {
    configID = PduR_GetConfigId(partitionIndexOfCSLForCommonSharedMemory);
  }
  /* ----- Development Error Report --------------------------------------- */
#if (PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR)
  {
    PduR_Det_ReportError(PDUR_FCT_CONFIGURATIONID, errorId);
  }
#else
  PDUR_DUMMY_STATEMENT(errorId);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif
  return configID;
}       /* End of PduR_GetConfigurationId() */

/* Upper Layer Interface APIs */
#if (PDUR_TX2LO == STD_ON)
/**********************************************************************************************************************
 * PduR_UpTransmit
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_UpTransmit(PduIdType id, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = PDUR_E_NO_ERROR;      /* PRQA S 2981 */ /* MD_MSR_RetVal */
  Std_ReturnType retVal = E_NOT_OK;     /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
# if (PDUR_DEV_ERROR_DETECT == STD_ON)  /* COV_PDUR_VAR_DEV_ERROR_DETECT */
  if(!PduR_IsPreInitialized())
  {
    errorId = PDUR_E_INVALID_REQUEST;
  }
  else if((id >= PduR_GetSizeOfTx2Lo())
#  if (PDUR_INVALIDHNDOFTX2LO == STD_ON)
          || (PduR_IsInvalidHndOfTx2Lo(id))
#  endif
    )
  {
    errorId = PDUR_E_PDU_ID_INVALID;
  }
  else if(!PduR_IsInitialized(PduR_GetPartitionIndexOfCslOfTx2Lo(id)))
  {
    errorId = PDUR_E_INVALID_REQUEST;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
# if (PDUR_BSWMPDURTRANSMITCALLBACKOFTX2LO == STD_ON)
    if(PduR_IsBswMPduRTransmitCallbackOfTx2Lo(id))
    {
      BswM_PduR_Transmit(id, info);     /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ID_AND_PTR */
    }
# endif
    {
      { /* 1:N Tx If API Forwarding; 1:1 Tx Tp API Forwarding */
        retVal = PduR_GetRmTransmitFctPtr(PduR_GetRmTransmitFctPtrIdxOfTx2Lo(id)) (PduR_GetRmSrcRomIdxOfTx2Lo(id), info);       /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ID_AND_PTR */
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR)
  {
    PduR_Det_ReportError(PDUR_FCT_TX, errorId);
  }
# else
  PDUR_DUMMY_STATEMENT(errorId);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
# endif

  PDUR_DUMMY_STATEMENT(id);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(info);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return retVal;
}
#endif

/* Communication Interface APIs */
#if (PDUR_RXIF2DEST == STD_ON)
/**********************************************************************************************************************
 * PduR_LoIfRxIndication
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_LoIfRxIndication(PduIdType RxPduId, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = PDUR_E_NO_ERROR;      /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
# if (PDUR_DEV_ERROR_DETECT == STD_ON)  /* COV_PDUR_VAR_DEV_ERROR_DETECT */
  if(!PduR_IsPreInitialized())
  {
    errorId = PDUR_E_INVALID_REQUEST;
  }
  else if((RxPduId >= PduR_GetSizeOfRxIf2Dest())
#  if (PDUR_INVALIDHNDOFRXIF2DEST == STD_ON)
          || (PduR_IsInvalidHndOfRxIf2Dest(RxPduId))
#  endif
    )
  {
    errorId = PDUR_E_PDU_ID_INVALID;
  }
  else if(!PduR_IsInitialized(PduR_GetPartitionIndexOfCslOfRxIf2Dest(RxPduId)))
  {
    errorId = PDUR_E_INVALID_REQUEST;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
# if (PDUR_BSWMPDURRXINDICATIONCALLBACKOFRXIF2DEST == STD_ON)
    if(PduR_IsBswMPduRRxIndicationCallbackOfRxIf2Dest(RxPduId))
    {
      BswM_PduR_RxIndication(RxPduId, info);    /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ID_AND_PTR */
    }
# endif
    {
      (void) PduR_RmIf_RoutePdu(PduR_GetRmSrcRomIdxOfRxIf2Dest(RxPduId), info);     /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ID_AND_PTR */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR)
  {
    PduR_Det_ReportError(PDUR_FCT_IFRXIND, errorId);
  }
# else
  PDUR_DUMMY_STATEMENT(errorId);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
# endif

  PDUR_DUMMY_STATEMENT(RxPduId);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(info);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}
#endif

#if (PDUR_TXCONFIRMATIONUSEDOFTXIF2UP == STD_ON)
/**********************************************************************************************************************
 * PduR_LoIfTxConfirmation
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
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
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_LoIfTxConfirmation(PduIdType TxPduId)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = PDUR_E_NO_ERROR;      /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
# if (PDUR_DEV_ERROR_DETECT == STD_ON)  /* COV_PDUR_VAR_DEV_ERROR_DETECT */
  if(!PduR_IsPreInitialized())
  {
    errorId = PDUR_E_INVALID_REQUEST;
  }
  else if((TxPduId >= PduR_GetSizeOfTxIf2Up())
#  if (PDUR_INVALIDHNDOFTXIF2UP == STD_ON)
          || (PduR_IsInvalidHndOfTxIf2Up(TxPduId))
#  endif
    )
  {
    errorId = PDUR_E_PDU_ID_INVALID;
  }
  else if(!PduR_IsInitialized(PduR_GetPartitionIndexOfCslOfTxIf2Up(TxPduId)))
  {
    errorId = PDUR_E_INVALID_REQUEST;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
# if (PDUR_BSWMPDURTXCONFIRMATIONCALLBACKOFTXIF2UP == STD_ON)
    if(PduR_IsBswMPduRTxConfirmationCallbackOfTxIf2Up(TxPduId))
    {
      BswM_PduR_TxConfirmation(TxPduId);
    }
# endif
# if (PDUR_TXCONFIRMATIONUSEDOFTXIF2UP == STD_ON)       /* COV_PDUR_VAR_LINIF_SPECIAL_CONFIGURATION */
    if(PduR_IsTxConfirmationUsedOfTxIf2Up(TxPduId))     /* COV_PDUR_FEATURE_ALWAYS_TRUE */
    {
      PduR_RmIf_MultipleSourceHandler_TxConfirmation(PduR_GetRmGDestRomIdxOfTxIf2Up(TxPduId));
    }
# endif
  }

  /* ----- Development Error Report --------------------------------------- */
# if (PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR)
  {
    PduR_Det_ReportError(PDUR_FCT_IFTXCFM, errorId);
  }
# else
  PDUR_DUMMY_STATEMENT(errorId);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
# endif

  PDUR_DUMMY_STATEMENT(TxPduId);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}
#endif

#if ((PDUR_TRIGGERTRANSMITSUPPORTEDOFRMSRCROM == STD_ON) || (PDUR_EXISTS_TRIGGER_TRANSMIT_QUEUEDATAPROVISIONTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))
/**********************************************************************************************************************
 * PduR_LoIfTriggerTransmit
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_LoIfTriggerTransmit(PduIdType TxPduId, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = PDUR_E_NO_ERROR;      /* PRQA S 2981 */ /* MD_MSR_RetVal */
  Std_ReturnType retVal = E_NOT_OK;     /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
# if (PDUR_DEV_ERROR_DETECT == STD_ON)  /* COV_PDUR_VAR_DEV_ERROR_DETECT */
  if(!PduR_IsPreInitialized())
  {
    errorId = PDUR_E_INVALID_REQUEST;
  }
  else if((TxPduId >= PduR_GetSizeOfTxIf2Up())
#  if (PDUR_INVALIDHNDOFTXIF2UP == STD_ON)
          || (PduR_IsInvalidHndOfTxIf2Up(TxPduId))
#  endif
    )
  {
    errorId = PDUR_E_PDU_ID_INVALID;
  }
  else if(!PduR_IsInitialized(PduR_GetPartitionIndexOfCslOfTxIf2Up(TxPduId)))
  {
    errorId = PDUR_E_INVALID_REQUEST;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    retVal = PduR_RmIf_MultipleSourceHandler_TriggerTransmit(PduR_GetRmGDestRomIdxOfTxIf2Up(TxPduId), info);    /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ID_AND_PTR */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR)
  {
    PduR_Det_ReportError(PDUR_FCT_TT, errorId);
  }
# else
  PDUR_DUMMY_STATEMENT(errorId);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
# endif

  PDUR_DUMMY_STATEMENT(TxPduId);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(info);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return retVal;
}
#endif
/* Transport Protocol APIs */
#if (PDUR_RXTP2DEST == STD_ON)
/**********************************************************************************************************************
 * PduR_LoTpStartOfReception
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
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
 *********************************************************************************************************************/
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_LoTpStartOfReception(PduIdType id, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, PduLengthType TpSduLength,
                                                             P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = PDUR_E_NO_ERROR;      /* PRQA S 2981 */ /* MD_MSR_RetVal */
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;   /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
# if (PDUR_DEV_ERROR_DETECT == STD_ON)  /* COV_PDUR_VAR_DEV_ERROR_DETECT */
  if(!PduR_IsPreInitialized())
  {
    errorId = PDUR_E_INVALID_REQUEST;
  }
  else if((id >= PduR_GetSizeOfRxTp2Dest())
#  if (PDUR_INVALIDHNDOFRXTP2DEST == STD_ON)
          || (PduR_IsInvalidHndOfRxTp2Dest(id))
#  endif
    )
  {
    errorId = PDUR_E_PDU_ID_INVALID;
  }
  else if(!PduR_IsInitialized(PduR_GetPartitionIndexOfCslOfRxTp2Dest(id)))
  {
    errorId = PDUR_E_INVALID_REQUEST;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    PduR_RmSrcRomIdxOfRxTp2DestType rmSrcRomIdx = PduR_GetRmSrcRomIdxOfRxTp2Dest(id);
    
# if ((PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON) && (PDUR_EXISTS_TP_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON))
    PduR_RmDestRomStartIdxOfRmSrcRomType rmDestRomIdxOfApiFwdDest = PduR_GetRmDestRomStartIdxOfRmSrcRom(rmSrcRomIdx);
    boolean apiFwdDestWasCalled = FALSE;
# endif

# if (PDUR_BSWMPDURTPSTARTOFRECEPTIONCALLBACKOFRXTP2DEST == STD_ON)
    if(PduR_IsBswMPduRTpStartOfReceptionCallbackOfRxTp2Dest(id))
    {
      BswM_PduR_TpStartOfReception(id, info, TpSduLength, bufferSizePtr);       /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ID_AND_PTR */
    }
# endif

# if (PDUR_EXISTS_TP_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON)
    {
      PduR_RmDestRomStartIdxOfRmSrcRomType rmDestRomIdx = PduR_GetRmDestRomStartIdxOfRmSrcRom(rmSrcRomIdx);

#  if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)      
      for(; rmDestRomIdx < PduR_GetRmDestRomEndIdxOfRmSrcRom(rmSrcRomIdx); rmDestRomIdx++)
      {
        if(PduR_GetRoutingTypeOfRmDestRom(rmDestRomIdx) == PDUR_TP_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM)
        {
#  endif
#  if (PDUR_RPGROM == STD_ON)
          if(PduR_IsDestPduEnabled(rmDestRomIdx) == TRUE)
#  endif
          {
            PduR_RmGDestRomIdxOfRmDestRomType rmGDestRomIdx = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestRomIdx);
            retVal = PduR_GetUpTpStartOfReceptionFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx), info, TpSduLength, bufferSizePtr);       /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ID_AND_PTR */
#  if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
            rmDestRomIdxOfApiFwdDest= rmDestRomIdx;
            apiFwdDestWasCalled = TRUE;
            break;
#  endif
          }
#  if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
        }
      }
#  endif
    }
# endif

# if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
    if(PduR_IsRmBufferedTpPropertiesRomUsedOfRmSrcRom(rmSrcRomIdx)) /* COV_PDUR_ONLY_TP_QUEUED_ROUTINGS */
    {
#  if (PDUR_EXISTS_TP_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON)
      if(apiFwdDestWasCalled == TRUE)
      {
          if(retVal == BUFREQ_OK)
          {
            PduLengthType bufferSizeOfQueuedDestinations;

            retVal = PduR_RmTp_StartOfReception(rmSrcRomIdx, info, TpSduLength, &bufferSizeOfQueuedDestinations);     /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ID_AND_PTR */
            if(retVal == BUFREQ_OK)
            {
              if(bufferSizeOfQueuedDestinations < *bufferSizePtr)
              {
                *bufferSizePtr = bufferSizeOfQueuedDestinations;  /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
              }
            }
            else
            {
              PduR_RmGDestRomIdxOfRmDestRomType rmGDestRomIdx = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestRomIdxOfApiFwdDest);
              PduR_GetUpTpTpRxIndicationFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx), E_NOT_OK);       /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ID_AND_PTR */
            }
          }
      }
      else
#  endif
      {
        retVal = PduR_RmTp_StartOfReception(rmSrcRomIdx, info, TpSduLength, bufferSizePtr);     /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ID_AND_PTR */
      }
    }
# endif
  }

  /* ----- Development Error Report --------------------------------------- */
# if (PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR)
  {
    PduR_Det_ReportError(PDUR_FCT_SOR, errorId);
  }
# else
  PDUR_DUMMY_STATEMENT(errorId);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
# endif

  PDUR_DUMMY_STATEMENT(id);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(info);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(TpSduLength);    /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(bufferSizePtr);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return retVal;
}  /* PRQA S 6080, 6010, 6030 */ /* MD_MSR_STMIF, MD_MSR_STPTH, MD_MSR_STCYC */
#endif
#if (PDUR_RXTP2DEST == STD_ON)
/**********************************************************************************************************************
 * PduR_LoTpCopyRxData
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_LoTpCopyRxData(PduIdType id, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = PDUR_E_NO_ERROR;      /* PRQA S 2981 */ /* MD_MSR_RetVal */
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;   /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
# if (PDUR_DEV_ERROR_DETECT == STD_ON)  /* COV_PDUR_VAR_DEV_ERROR_DETECT */
  if(!PduR_IsPreInitialized())
  {
    errorId = PDUR_E_INVALID_REQUEST;
  }
  else if((id >= PduR_GetSizeOfRxTp2Dest())
#  if (PDUR_INVALIDHNDOFRXTP2DEST == STD_ON)
          || (PduR_IsInvalidHndOfRxTp2Dest(id))
#  endif
    )
  {
    errorId = PDUR_E_PDU_ID_INVALID;
  }
  else if(!PduR_IsInitialized(PduR_GetPartitionIndexOfCslOfRxTp2Dest(id)))
  {
    errorId = PDUR_E_INVALID_REQUEST;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    PduR_RmSrcRomIdxOfRxTp2DestType rmSrcRomIdx = PduR_GetRmSrcRomIdxOfRxTp2Dest(id);
# if ((PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON) && (PDUR_EXISTS_TP_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON))
    boolean apiFwdDestWasCalled = FALSE;
# endif

# if (PDUR_EXISTS_TP_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON)
    {
      PduR_RmDestRomStartIdxOfRmSrcRomType rmDestRomIdx = PduR_GetRmDestRomStartIdxOfRmSrcRom(rmSrcRomIdx);

      /*----- Iterate destPdus, find out the only unbuffered destPdu (only one unbuffered destPdu is supported), call the Forwarding Tp module CopyRxData function -----*/
#  if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
      for (; rmDestRomIdx < PduR_GetRmDestRomEndIdxOfRmSrcRom(rmSrcRomIdx); rmDestRomIdx++)
      {
        if(PduR_GetRoutingTypeOfRmDestRom(rmDestRomIdx) == PDUR_TP_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM)
        {
#  endif
#  if (PDUR_RPGROM == STD_ON)
          if(PduR_IsDestPduEnabled(rmDestRomIdx) == TRUE)
#  endif
          {
            PduR_RmGDestRomIdxOfRmDestRomType rmGDestRomIdx = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestRomIdx);
            retVal = PduR_GetUpTpCopyRxDataFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx), info, bufferSizePtr);  /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ID_AND_PTR */
#  if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
            apiFwdDestWasCalled = TRUE;
            break;
#  endif
          }
#  if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
        }
      }
#  endif
    }
# endif


# if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
    /* ----- when Unbuferred destRoms exist, call the gateway or Tp module start of reception function ----- */
    if(PduR_IsRmBufferedTpPropertiesRomUsedOfRmSrcRom(rmSrcRomIdx)) /* COV_PDUR_ONLY_TP_QUEUED_ROUTINGS */
    { /* buffered Tp Routings */
#  if (PDUR_EXISTS_TP_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON)
      if(apiFwdDestWasCalled == TRUE)
      {
        if(retVal == BUFREQ_OK)
        {/* buffered Tp Routings */
          PduLengthType bufferSizeOfQueuedDestinations;

          retVal = PduR_RmTp_CopyRxData(rmSrcRomIdx, info, &bufferSizeOfQueuedDestinations);  /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ID_AND_PTR */
          if(retVal == BUFREQ_OK)
          {
            if(bufferSizeOfQueuedDestinations < *bufferSizePtr)
            {
              *bufferSizePtr = bufferSizeOfQueuedDestinations;  /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
            }
          }
        }
      }
      else
#  endif
      {
        retVal = PduR_RmTp_CopyRxData(rmSrcRomIdx, info, bufferSizePtr);     /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ID_AND_PTR */
      }
    }
# endif
  }


  /* ----- Development Error Report --------------------------------------- */
# if (PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR)
  {
    PduR_Det_ReportError(PDUR_FCT_CPYRX, errorId);
  }
# else
  PDUR_DUMMY_STATEMENT(errorId);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
# endif

  PDUR_DUMMY_STATEMENT(id);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(info);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(bufferSizePtr);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return retVal;
}  /* PRQA S 6080, 6030 */ /* MD_MSR_STMIF, MD_MSR_STCYC */
#endif
#if(PDUR_TXTP2SRC == STD_ON)
/**********************************************************************************************************************
 * PduR_LoTpCopyTxData
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_LoTpCopyTxData(PduIdType id, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, P2VAR(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA) retry,
                                                       P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) availableDataPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = PDUR_E_NO_ERROR;      /* PRQA S 2981 */ /* MD_MSR_RetVal */
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;   /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
# if (PDUR_DEV_ERROR_DETECT == STD_ON)  /* COV_PDUR_VAR_DEV_ERROR_DETECT */
  if(!PduR_IsPreInitialized())
  {
    errorId = PDUR_E_INVALID_REQUEST;
  }
  else if((id >= PduR_GetSizeOfTxTp2Src())
#  if (PDUR_INVALIDHNDOFTXTP2SRC == STD_ON)
          || (PduR_IsInvalidHndOfTxTp2Src(id))
#  endif
    )
  {
    errorId = PDUR_E_PDU_ID_INVALID;
  }
  else if(!PduR_IsInitialized(PduR_GetPartitionIndexOfCslOfTxTp2Src(id)))
  {
    errorId = PDUR_E_INVALID_REQUEST;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    retVal = PduR_RmTp_MultipleSourceHandler_CopyTxData(PduR_GetRmGDestRomIdxOfTxTp2Src(id), info, retry, availableDataPtr);    /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
  }
  
  /* ----- Development Error Report --------------------------------------- */
# if (PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR)
  {
    PduR_Det_ReportError(PDUR_FCT_CPYTX, errorId);
  }
# else
  PDUR_DUMMY_STATEMENT(errorId);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
# endif

  PDUR_DUMMY_STATEMENT(id);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(info);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(retry);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(availableDataPtr);       /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return retVal;
}
#endif
#if (PDUR_RXTP2DEST == STD_ON)
/**********************************************************************************************************************
 * PduR_LoTpRxIndication
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_LoTpRxIndication(PduIdType id, Std_ReturnType result)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = PDUR_E_NO_ERROR;      /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
# if (PDUR_DEV_ERROR_DETECT == STD_ON)  /* COV_PDUR_VAR_DEV_ERROR_DETECT */
  if(!PduR_IsPreInitialized())
  {
    errorId = PDUR_E_INVALID_REQUEST;
  }
  else if((id >= PduR_GetSizeOfRxTp2Dest())
#  if (PDUR_INVALIDHNDOFRXTP2DEST == STD_ON)
          || (PduR_IsInvalidHndOfRxTp2Dest(id))
#  endif
    )
  {
    errorId = PDUR_E_PDU_ID_INVALID;
  }
  else if(!PduR_IsInitialized(PduR_GetPartitionIndexOfCslOfRxTp2Dest(id)))
  {
    errorId = PDUR_E_INVALID_REQUEST;
  }
  else
# endif
  {
# if (PDUR_BSWMPDURTPRXINDICATIONCALLBACKOFRXTP2DEST == STD_ON)
    if(PduR_IsBswMPduRTpRxIndicationCallbackOfRxTp2Dest(id))
    {
      BswM_PduR_TpRxIndication(id, result);
    }
# endif

    {
      /* ----- Implementation ----------------------------------------------- */
      PduR_RmSrcRomIdxOfRxTp2DestType rmSrcRomIdx = PduR_GetRmSrcRomIdxOfRxTp2Dest(id);

# if (PDUR_EXISTS_TP_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON)
      {
        PduR_RmDestRomStartIdxOfRmSrcRomType rmDestRomIdx = PduR_GetRmDestRomStartIdxOfRmSrcRom(rmSrcRomIdx);

        /*----- Iterate destPdus, find out the only unbuffered destPdu (only one unbuffered destPdu is supported), call the Forwarding Tp module RxIndication -----*/
#  if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
        for (; rmDestRomIdx < PduR_GetRmDestRomEndIdxOfRmSrcRom(rmSrcRomIdx); rmDestRomIdx++)
        {
          if(PduR_GetRoutingTypeOfRmDestRom(rmDestRomIdx) == PDUR_TP_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM)
#  endif
          {
            PduR_RmGDestRomIdxOfRmDestRomType rmGDestRomIdx = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestRomIdx);
            PduR_GetUpTpTpRxIndicationFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx), result);      /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ID_AND_PTR */
#  if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
            break;
#  endif
          }
#  if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
        }
#  endif
      }
# endif


# if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
      if(PduR_IsRmBufferedTpPropertiesRomUsedOfRmSrcRom(rmSrcRomIdx)) /* COV_PDUR_ONLY_TP_QUEUED_ROUTINGS */
      {
        /* buffered Tp Routings */
        PduR_RmTp_TpRxIndication(rmSrcRomIdx, result);
      }
# endif
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR)
  {
    PduR_Det_ReportError(PDUR_FCT_TPRXIND, errorId);
  }
# else
  PDUR_DUMMY_STATEMENT(errorId);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
# endif

  PDUR_DUMMY_STATEMENT(id);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(result); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif
#if (PDUR_TXTP2SRC == STD_ON)
/**********************************************************************************************************************
 * PduR_LoTpTxConfirmation
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_LoTpTxConfirmation(PduIdType id, Std_ReturnType result)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = PDUR_E_NO_ERROR;      /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
# if (PDUR_DEV_ERROR_DETECT == STD_ON)  /* COV_PDUR_VAR_DEV_ERROR_DETECT */
  if(!PduR_IsPreInitialized())
  {
    errorId = PDUR_E_INVALID_REQUEST;
  }
  else if((id >= PduR_GetSizeOfTxTp2Src())
#  if (PDUR_INVALIDHNDOFTXTP2SRC == STD_ON)
          || (PduR_IsInvalidHndOfTxTp2Src(id))
#  endif
    )
  {
    errorId = PDUR_E_PDU_ID_INVALID;
  }
  else if(!PduR_IsInitialized(PduR_GetPartitionIndexOfCslOfTxTp2Src(id)))
  {
    errorId = PDUR_E_INVALID_REQUEST;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
# if (PDUR_BSWMPDURTPTXCONFIRMATIONCALLBACKOFTXTP2SRC == STD_ON)
    if(PduR_IsBswMPduRTpTxConfirmationCallbackOfTxTp2Src(id))
    {
      BswM_PduR_TpTxConfirmation(id, result);
    }
# endif
    PduR_RmTp_MultipleSourceHandler_TpTxConfirmation(PduR_GetRmGDestRomIdxOfTxTp2Src(id), result);
  }

  /* ----- Development Error Report --------------------------------------- */
# if (PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR)
  {
    PduR_Det_ReportError(PDUR_FCT_TPTXCFM, errorId);
  }
# else
  PDUR_DUMMY_STATEMENT(errorId);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
# endif

  PDUR_DUMMY_STATEMENT(id);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(result); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}
#endif
/* CancelReceive global without UseTag API */
#if (PDUR_CANCELRECEIVESUPPORTEDOFMMROM == STD_ON)
/**********************************************************************************************************************
 * PduR_CancelReceive
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_CancelReceive(PduIdType id)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = PDUR_E_NO_ERROR;      /* PRQA S 2981 */ /* MD_MSR_RetVal */
  Std_ReturnType retVal = E_NOT_OK;     /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
# if (PDUR_DEV_ERROR_DETECT == STD_ON)  /* COV_PDUR_VAR_DEV_ERROR_DETECT */
  if(!PduR_IsPreInitialized())
  {
    errorId = PDUR_E_INVALID_REQUEST;
  }
  else if((id >= PduR_GetSizeOfRxTp2Src())
#  if (PDUR_INVALIDHNDOFRXTP2SRC == STD_ON)
          || (PduR_IsInvalidHndOfRxTp2Src(id))
#  endif
    )
  {
    errorId = PDUR_E_PDU_ID_INVALID;
  }
  else if(!PduR_IsInitialized(PduR_GetPartitionIndexOfCslOfRxTp2Src(id)))
  {
    errorId = PDUR_E_INVALID_REQUEST;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    PduR_RmDestRomIdxOfRxTp2SrcType rmDestRomIdx = PduR_GetRmDestRomIdxOfRxTp2Src(id);
    PduR_RmSrcRomIdxOfRmDestRomType rmSrcRomIdx = PduR_GetRmSrcRomIdxOfRmDestRom(rmDestRomIdx);
    PduR_MmRomIdxOfRmSrcRomType mmRomIdx = PduR_GetMmRomIdxOfRmSrcRom(rmSrcRomIdx);

    if(PduR_IsCancelReceiveSupportedOfMmRom(mmRomIdx))  /* COV_PDUR_FEATURE_ALWAYS_TRUE */
    {
# if (PDUR_RPGROM == STD_ON)
      if(PduR_IsDestPduEnabled(rmDestRomIdx) == TRUE)
# endif
      {
        PduR_SrcHndOfRmSrcRomType srcHnd = PduR_GetSrcHndOfRmSrcRom(rmSrcRomIdx);
        retVal = PduR_GetLoTpCancelReceiveFctPtrOfMmRom(mmRomIdx) (srcHnd);     /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ID_ONLY */
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR)
  {
    PduR_Det_ReportError(PDUR_FCT_CRX, errorId);
  }
# else
  PDUR_DUMMY_STATEMENT(errorId);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
# endif

  PDUR_DUMMY_STATEMENT(id);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return retVal;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif
#if (PDUR_CHANGEPARAMETERSUPPORTEDOFMMROM == STD_ON)
/* ChangeParameter global without UseTag  API */
/**********************************************************************************************************************
 * PduR_ChangeParameter
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_ChangeParameter(PduIdType id, TPParameterType parameter, uint16 value)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = PDUR_E_NO_ERROR;      /* PRQA S 2981 */ /* MD_MSR_RetVal */
  Std_ReturnType retVal = E_NOT_OK;     /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
# if (PDUR_DEV_ERROR_DETECT == STD_ON)  /* COV_PDUR_VAR_DEV_ERROR_DETECT */
  if(!PduR_IsPreInitialized())
  {
    errorId = PDUR_E_INVALID_REQUEST;
  }
  else if((id >= PduR_GetSizeOfRxTp2Src())
#  if (PDUR_INVALIDHNDOFRXTP2SRC == STD_ON)
          || (PduR_IsInvalidHndOfRxTp2Src(id))
#  endif
    )
  {
    errorId = PDUR_E_PDU_ID_INVALID;
  }
  else if(!PduR_IsInitialized(PduR_GetPartitionIndexOfCslOfRxTp2Src(id)))
  {
    errorId = PDUR_E_INVALID_REQUEST;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    PduR_RmDestRomIdxOfRxTp2SrcType rmDestRomIdx = PduR_GetRmDestRomIdxOfRxTp2Src(id);
    PduR_RmSrcRomIdxOfRmDestRomType rmSrcRomIdx = PduR_GetRmSrcRomIdxOfRmDestRom(rmDestRomIdx);
    PduR_MmRomIdxOfRmSrcRomType mmRomIdx = PduR_GetMmRomIdxOfRmSrcRom(rmSrcRomIdx);

    if(PduR_IsChangeParameterSupportedOfMmRom(mmRomIdx))        /* COV_PDUR_FEATURE_ALWAYS_TRUE */
    {
      PduR_SrcHndOfRmSrcRomType srcHnd = PduR_GetSrcHndOfRmSrcRom(rmSrcRomIdx);
      retVal = PduR_GetLoTpChangeParameterFctPtrOfMmRom(mmRomIdx) (srcHnd, parameter, value);   /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ID_ONLY */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR)
  {
    PduR_Det_ReportError(PDUR_FCT_CHPARA, errorId);
  }
# else
  PDUR_DUMMY_STATEMENT(errorId);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
# endif

  PDUR_DUMMY_STATEMENT(id);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(parameter);      /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(value);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return retVal;
}
#endif
/* Communication Interface / Transport Protocol APIs */
#if ((PDUR_IFCANCELTRANSMITSUPPORTEDOFMMROM == STD_ON) || (PDUR_TPCANCELTRANSMITSUPPORTEDOFMMROM == STD_ON))
/**********************************************************************************************************************
 * PduR_CancelTransmit
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_CancelTransmit(PduIdType id)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = PDUR_E_NO_ERROR;      /* PRQA S 2981 */ /* MD_MSR_RetVal */
  Std_ReturnType retVal = E_NOT_OK;     /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
# if (PDUR_DEV_ERROR_DETECT == STD_ON)  /* COV_PDUR_VAR_DEV_ERROR_DETECT */
  if(!PduR_IsPreInitialized())
  {
    errorId = PDUR_E_INVALID_REQUEST;
  }
#  if (PDUR_TX2LO == STD_ON)    /* COV_PDUR_VAR_DEPENDENT_SWITCH */
  else if((id >= PduR_GetSizeOfTx2Lo())
#   if (PDUR_INVALIDHNDOFTX2LO == STD_ON)
          || (PduR_IsInvalidHndOfTx2Lo(id))
#   endif
    )
  {
    errorId = PDUR_E_PDU_ID_INVALID;
  }
  else if(!PduR_IsInitialized(PduR_GetPartitionIndexOfCslOfTx2Lo(id)))
  {
    errorId = PDUR_E_INVALID_REQUEST;
  }
#  endif
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
# if (PDUR_CANCELTRANSMITUSEDOFTX2LO  == STD_ON)        /* COV_PDUR_VAR_DEPENDENT_SWITCH */
    if(PduR_IsCancelTransmitUsedOfTx2Lo(id))    /* COV_PDUR_FEATURE_ALWAYS_TRUE */
    {
      retVal = PduR_Rm_CancelTransmit_MultiDest(PduR_GetRmSrcRomIdxOfTx2Lo(id));
    }
# endif
  }
  /* ----- Development Error Report --------------------------------------- */
# if (PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR)
  {
    PduR_Det_ReportError(PDUR_FCT_CTX, errorId);
  }
# else
  PDUR_DUMMY_STATEMENT(errorId);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
# endif

  PDUR_DUMMY_STATEMENT(id);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return retVal;
}
#endif

#if ((PDUR_IFCANCELTRANSMITSUPPORTEDOFMMROM == STD_ON) || (PDUR_TPCANCELTRANSMITSUPPORTEDOFMMROM == STD_ON))
/**********************************************************************************************************************
 * PduR_Rm_CancelTransmit_MultiDest
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_Rm_CancelTransmit_MultiDest(PduR_RmSrcRomIterType rmSrcIdx)
{
  Std_ReturnType retVal = E_NOT_OK;     /* PRQA S 2981 */ /* MD_MSR_RetVal */

  PduR_RmDestRomIterType rmDestIdx;

  for(rmDestIdx = PduR_GetRmDestRomStartIdxOfRmSrcRom(rmSrcIdx); rmDestIdx < PduR_GetRmDestRomEndIdxOfRmSrcRom(rmSrcIdx); rmDestIdx++)
  {
# if (PDUR_RPGROM == STD_ON)
    if(PduR_IsDestPduEnabled(rmDestIdx) == TRUE)
# endif
    {
      switch (PduR_GetRoutingTypeOfRmDestRom(rmDestIdx))
      {
# if ((PDUR_EXISTS_IF_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON) && (PDUR_IFCANCELTRANSMITSUPPORTEDOFMMROM == STD_ON))
        case PDUR_IF_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM:
          if(PduR_IsIfCancelTransmitSupportedOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(PduR_GetRmGDestRomIdxOfRmDestRom(rmDestIdx))))        /* COV_PDUR_FEATURE_ALWAYS_TRUE */
          {
            retVal &= PduR_RmIf_MultipleSourceHandler_CancelTransmit(rmDestIdx);
          }
          break;
# endif
# if ((PDUR_EXISTS_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON) && (PDUR_TPCANCELTRANSMITSUPPORTEDOFMMROM == STD_ON))
        case PDUR_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM:
          if(PduR_IsTpCancelTransmitSupportedOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(PduR_GetRmGDestRomIdxOfRmDestRom(rmDestIdx))))        /* COV_PDUR_FEATURE_ALWAYS_TRUE */
          {
            retVal &= PduR_RmTp_MultipleSourceHandler_CancelTransmit(rmDestIdx);
          }
          break;
# endif
        default:       /* COV_PDUR_MISRA */
          /* Nothing to do: This should never be reached */
          break;
      }
    }
  }

  PDUR_DUMMY_STATEMENT(rmSrcIdx);       /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return retVal;
}
#endif

#if(PDUR_MULTICORE == STD_ON)
/**********************************************************************************************************************
*  PduR_GetMemorySectionIndexOfOsApplication
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
PDUR_LOCAL_INLINE FUNC(PduR_MemIdxType, PDUR_CODE) PduR_GetMemorySectionIndexOfOsApplication(ApplicationType applicationId)
{
  PduR_MemIdxType retVal = 0;
  PduR_MemIdxType memIdx = PduR_GetOsApplicationToPduROfPartitionLookupTableRam(applicationId);

  if(memIdx == 0xFFu) /* COV_PDUR_FATAL_ERROR */
  {
    /* This PduR is either not assigned to this osApplication or was not correctly initialized. */
    PduR_Det_ReportError(PDUR_FCT_MEM_SECTION_MAPPING, PDUR_E_OSAPP2MEMMAPPING);
  }
  else
  {
    retVal = memIdx;
  }
  return retVal;
}
#endif

#if(PDUR_MULTICORE == STD_ON)
/**********************************************************************************************************************
 *  PduR_CreatePartitionLookupTable
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_CreatePartitionLookupTable(void)
{
  PduR_MemIdxType memIdx;
  PduR_PartitionLookupTableRamIterType osApplicationId;

  for (osApplicationId = 0u; osApplicationId < PduR_GetSizeOfPartitionLookupTableRam(); osApplicationId++)
  {
    PduR_SetOsApplicationToPduROfPartitionLookupTableRam(osApplicationId, 0xFFu); /* SBSW_PDUR_CSL01 */
    for (memIdx = 0u; memIdx < PduR_GetSizeOfPartitionIdentifiers(); memIdx++)  /* COV_PDUR_RUNS_ON_ALL_APPLICATIONS */
    {
      if (((PduR_PartitionLookupTableRamIterType) PduR_GetPartitionSNVOfPartitionIdentifiers(memIdx)) == osApplicationId)
      {
        PduR_SetOsApplicationToPduROfPartitionLookupTableRam(osApplicationId, memIdx); /* SBSW_PDUR_CSL01 */
        break;
      }
    }
  }
}
#endif

/**********************************************************************************************************************
 *  PduR_GetMemIdx
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
PDUR_LOCAL_INLINE FUNC(PduR_MemIdxType, PDUR_CODE) PduR_GetMemIdx(void)
{
#if(PDUR_MULTICORE == STD_ON)
  return PduR_GetMemorySectionIndexOfOsApplication(GetApplicationID());
#else
  return partitionIndexOfCSLForCommonSharedMemory;
#endif
}

/**********************************************************************************************************************
 *  PduR_PreInit
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
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
 */
FUNC(void, PDUR_CODE) PduR_PreInit(P2CONST(PduR_PBConfigType, AUTOMATIC, PDUR_INIT_DATA) ConfigPtr)
{
  uint8 errorId = PDUR_E_NO_ERROR;      /* PRQA S 2981 */ /* MD_MSR_RetVal */
  PduR_PCPartitionConfigIdxOfPartitionIdentifiersType partitionCounter;

#if(PDUR_USE_INIT_POINTER == STD_ON)
  PduR_ConfigDataPtr = ConfigPtr;
  if(PduR_ConfigDataPtr == NULL_PTR)
  {
# if(PDUR_USE_ECUM_BSW_ERROR_HOOK == STD_ON)    /* COV_PDUR_VAR_DEPENDENT_SWITCH */
    EcuM_BswErrorHook(PDUR_MODULE_ID, ECUM_BSWERROR_NULLPTR);
# endif
    errorId = PDUR_E_PARAM_POINTER;
  }
# if (PDUR_FINALMAGICNUMBER == STD_ON)  /* COV_PDUR_VAR_DEPENDENT_SWITCH */
  else if(PduR_GetFinalMagicNumber() != PDUR_FINAL_MAGIC_NUMBER)
  {
#  if(PDUR_USE_ECUM_BSW_ERROR_HOOK == STD_ON)   /* COV_PDUR_VAR_DEPENDENT_SWITCH */
    EcuM_BswErrorHook(PDUR_MODULE_ID, ECUM_BSWERROR_MAGICNUMBER);
#  endif
    errorId = PDUR_E_INIT_FAILED;
    PduR_ConfigDataPtr = (const PduR_PBConfigType *) NULL_PTR;
  }
  else
# endif
#else
  if(ConfigPtr != NULL_PTR)
  {
    errorId = PDUR_E_INIT_FAILED;
  }
  else
#endif
  {
#if(PDUR_MULTICORE == STD_ON)
    PduR_CreatePartitionLookupTable();
    /* Initialize shared memory section. */
    PduR_InitMemorySection(partitionIndexOfCSLForCommonSharedMemory);
#endif

    for (partitionCounter = 0u; partitionCounter < PduR_GetSizeOfPartitionIdentifiers(); partitionCounter++)
    {
      PduR_SetInitialized(FALSE, partitionCounter); /* SBSW_PDUR_CSL01 */
    }

    PduR_PreInitialized = TRUE;
  }
  /* ----- Development Error Report --------------------------------------- */
#if (PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR)
  {
    PduR_Det_ReportError(PDUR_FCT_PREINIT, errorId);
  }
#else
  PDUR_DUMMY_STATEMENT(errorId);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif
}

/**********************************************************************************************************************
 * PduR_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Init(P2CONST(PduR_PBConfigType, AUTOMATIC, PDUR_INIT_DATA) ConfigPtr)
{
/* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = PDUR_E_NO_ERROR;      /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
  if (!PduR_IsPreInitialized())
  {
    errorId = PDUR_E_NO_PREINIT;
  }
  else if(PduR_IsInitialized(PduR_GetMemIdx()))
  {
    errorId = PDUR_E_ALREADY_INITIALIZED;
  }
  else
  {
    PduR_InitMemorySection(PduR_GetMemIdx());
  }
  /* ----- Development Error Report --------------------------------------- */
#if (PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR)
  {
    PduR_Det_ReportError(PDUR_FCT_INIT, errorId);
  }
#else
  PDUR_DUMMY_STATEMENT(errorId);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif
  PDUR_DUMMY_STATEMENT(ConfigPtr);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}

/**********************************************************************************************************************
 * PduR_InitMemorySection
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_InitMemorySection(PduR_MemIdxType memIdx)
{
#if(PDUR_RPGROM == STD_ON)
  PduR_Init_RmDestRpgRom(memIdx);
#endif

#if(PDUR_RMGDESTNTO1INFORAMIDXOFRMGDESTROM == STD_ON)
  PduR_Rm_MultipleSourceHandler_Init(memIdx);
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)
  PduR_Bm_Init(memIdx);
#endif

#if(PDUR_FMFIFORAM == STD_ON)
  PduR_Fm_Init(memIdx);
#endif

#if (PDUR_SMDATAPLANEROM == STD_ON)
  PduR_Sm_Init(memIdx);
#endif

#if (PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
  PduR_RmIf_InitDestPduState(memIdx);
#endif

#if(PDUR_EXISTS_SINGLE_BUFFER_QUEUE_IMPLEMENTATIONTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
  PduR_RmIf_SingleBuffer_Init(memIdx);
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
  PduR_RmTp_Init(memIdx);
#endif

#if(PDUR_MCQBUFFERROM == STD_ON)
  PduR_McQ_Init(memIdx);
#endif

#if (PDUR_DEFERREDEVENTCACHEROM == STD_ON)
  PduR_EvC_Init(memIdx);
#endif

#if (PDUR_SPINLOCKRAM == STD_ON)
  PduR_Lock_Init(memIdx);
#endif

#if (PDUR_INTERFACEFIFOQUEUEROM == STD_ON)
  PduR_IFQ_Init(memIdx);
#endif

  PduR_SetInitialized(TRUE, memIdx);        /* SBSW_PDUR_CSL_VAR_ACCESS */
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */

#if (PDUR_MAIN_FUNCTION == STD_ON)
/**********************************************************************************************************************
  PduR_MainFunction
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_MainFunction(void)
{
# if(PDUR_MULTICORE == STD_ON)
  uint8 errorId = PDUR_E_NO_ERROR;      /* PRQA S 2981 */ /* MD_MSR_RetVal */
  PduR_ApplicationId2DestApplicationManagerRomIterType applicationId = (PduR_ApplicationId2DestApplicationManagerRomIterType) GetApplicationID();
#  if (PDUR_DEV_ERROR_DETECT == STD_ON) /* COV_PDUR_VAR_DEV_ERROR_DETECT */
  if(applicationId >= PduR_GetSizeOfApplicationId2DestApplicationManagerRom())
  {
    errorId = PDUR_E_INVALID_APPLICATION_ID;
  }
#   if(PDUR_INVALIDHNDOFAPPLICATIONID2DESTAPPLICATIONMANAGERROM == STD_ON)
  else if(PduR_IsInvalidHndOfApplicationId2DestApplicationManagerRom(applicationId))
  {
    errorId = PDUR_E_INVALID_APPLICATION_ID;
  }
#   endif
  else
#  endif
# endif
  {
    if(PduR_IsPreInitialized() && PduR_IsInitialized(PduR_GetMemIdx())) /* PRQA S 3415 */ /* MD_PduR_3415 */
    {
      PduR_DestApplicationManagerRomIterType destApplicationManagerRomIdx = 0; /* PRQA S 2981 */ /* MD_MSR_RetVal */
# if(PDUR_MULTICORE == STD_ON)
      destApplicationManagerRomIdx = PduR_GetDestApplicationManagerRomIdxOfApplicationId2DestApplicationManagerRom(applicationId); /* PRQA S 2842 */ /* MD_PduR_2842 */
# endif

# if ((PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON))
#  if (PDUR_DEFERREDEVENTCACHEROM == STD_ON)
      /* In case of an overflowed event queue, flush all queues and apply fallback strategy to process all destinations */
      if(PduR_EvC_IsAnyEvCOverflowed(destApplicationManagerRomIdx) == TRUE)
      {
        PduR_EvC_FlushAllEvCOfDestApplication(destApplicationManagerRomIdx);
        PduR_ProcessAllDestinationsOfDestApplication(destApplicationManagerRomIdx);
      }
      /* Otherwise, process deferred event cache and call the corresponding Mainfunction */
      else
      {
        PduR_EvC_ReadAndProcessEvCOfDestApplication(destApplicationManagerRomIdx);
      }
#  else
      PduR_ProcessAllDestinationsOfDestApplication(destApplicationManagerRomIdx);
#  endif
# endif

# if (PDUR_MCQBUFFERROM == STD_ON)
      /* Process deferred If Pdus which are handled by the multicore queue in context of cyclic MainFunction */
      PduR_McQ_MainFunction(destApplicationManagerRomIdx);
# endif
    }
  }

# if(PDUR_MULTICORE == STD_ON)
  /* ----- Development Error Report --------------------------------------- */
#  if (PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR)
  {
    PduR_Det_ReportError(PDUR_FCT_MAINFUNCTION_TX, errorId);
  }
#  else
  PDUR_DUMMY_STATEMENT(errorId);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#  endif
# endif
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if(PDUR_RPGROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Init_RmDestRpgRom
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Init_RmDestRpgRom(PduR_MemIdxType memIdx)
{
  {
    PduR_RmDestRpgRomIterType rmDestRpgRomIdx;
    for(rmDestRpgRomIdx = 0u; rmDestRpgRomIdx < PduR_GetSizeOfRmDestRpgRom(memIdx); rmDestRpgRomIdx++)
    {
      PduR_SetEnabledCntOfRmDestRpgRam(rmDestRpgRomIdx, PduR_GetInitialEnabledCntOfRmDestRpgRom(rmDestRpgRomIdx, memIdx), memIdx);      /* SBSW_PDUR_CSL01 */
    }
  }
  {
    PduR_RpgRomIterType rpgRomIdx;
    for(rpgRomIdx = 0u; rpgRomIdx < PduR_GetSizeOfRpgRom(memIdx); rpgRomIdx++)
    {
      PduR_SetEnabledOfRpgRam(rpgRomIdx, PduR_IsEnabledAtInitOfRpgRom(rpgRomIdx, memIdx), memIdx);    /* SBSW_PDUR_CSL01 */ /* PRQA S 2995, 2996 */ /* MD_PduR_2995_2996 */
    }
  }
}
#endif

#if(PDUR_RMGDESTNTO1INFORAMIDXOFRMGDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Rm_MultipleSourceHandler_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Rm_MultipleSourceHandler_Init(PduR_MemIdxType memIdx)
{
  PduR_RmGDestNto1InfoRamIterType rmGDestNto1InfoRamIdx;

  for(rmGDestNto1InfoRamIdx = 0u; rmGDestNto1InfoRamIdx < PduR_GetSizeOfRmGDestNto1InfoRam(memIdx); rmGDestNto1InfoRamIdx++)
  {
    PduR_SetTransmissionActiveOfRmGDestNto1InfoRam(rmGDestNto1InfoRamIdx, FALSE, memIdx);  /* SBSW_PDUR_IDX_PARAM_INTERNAL_FUNCTION */
    PduR_SetRmDestRomIdxOfRmGDestNto1InfoRam(rmGDestNto1InfoRamIdx, PDUR_NO_RMDESTROMIDXOFRMGDESTNTO1INFORAM, memIdx);     /* SBSW_PDUR_IDX_PARAM_INTERNAL_FUNCTION */
  }
}
#endif

/**********************************************************************************************************************
 * PduR_Rm_GetSrcDestPdu
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_Rm_GetSrcDestPdu(PduR_RmGDestRomIterType rmGDestRomIdx, P2VAR(PduR_RmDestRomIterType, AUTOMATIC, PDUR_APPL_DATA) rmDestRomIdx)
{
  Std_ReturnType retVal = E_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */

#if(PDUR_RMGDESTNTO1INFORAMIDXOFRMGDESTROM == STD_ON)
  PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfRmGDestRom(rmGDestRomIdx);

  if(PduR_IsRmGDestNto1InfoRamUsedOfRmGDestRom(rmGDestRomIdx))  /* COV_PDUR_NTO1_NO_BUFFER_GW_ONLY_ROUTINGPATHS */
  {
    PduR_RmDestRomIterType readRmDestRomIdx = PduR_GetRmDestRomIdxOfRmGDestNto1InfoRam(PduR_GetRmGDestNto1InfoRamIdxOfRmGDestRom(rmGDestRomIdx), memIdx);

    if(readRmDestRomIdx == PDUR_NO_RMDESTROMIDXOFRMGDESTNTO1INFORAM)   /* COV_PDUR_NTO1_NO_BUFFER_GW_ONLY_ROUTINGPATHS */
    {
      retVal = E_NOT_OK;
    }
# if (PDUR_EXTENDED_ERROR_CHECKS == STD_ON)
    else if(readRmDestRomIdx >= PduR_GetSizeOfRmDestRom()) /* COV_PDUR_EXTENDED_ERROR_CHECKS */
    {
      /* If rmDestRomIdx is out-of-bounds: use one of the valid source rmDests as fallback. */
      *rmDestRomIdx = PduR_GetRmDestRomIdxOfRmGDestRom(rmGDestRomIdx);    /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
    }
    else if(PduR_GetRmGDestRomIdxOfRmDestRom(readRmDestRomIdx) != rmGDestRomIdx) /* COV_PDUR_EXTENDED_ERROR_CHECKS */
    {
      /* The read source rmDest is valid but does not belong to this rmGDestRom. It is erroneous. Use one of the valid source rmDests as fallback. */
      *rmDestRomIdx = PduR_GetRmDestRomIdxOfRmGDestRom(rmGDestRomIdx);    /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
    }
# endif
    else
    {
      *rmDestRomIdx = readRmDestRomIdx;        /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
    }
  }
  else
#endif
  {
    *rmDestRomIdx = PduR_GetRmDestRomIdxOfRmGDestRom(rmGDestRomIdx);    /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
  }

  return retVal;
}

#if(PDUR_RMGDESTNTO1INFORAMIDXOFRMGDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Rm_MultipleSourceHandler_Reset
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Rm_MultipleSourceHandler_Reset(PduR_RmGDestRomIterType rmGDestRomIdx)
{
  if(PduR_IsRmGDestNto1InfoRamUsedOfRmGDestRom(rmGDestRomIdx))
  {
    PduR_RmGDestNto1InfoRamIdxOfRmGDestRomType rmGDestNto1InfoIdx = PduR_GetRmGDestNto1InfoRamIdxOfRmGDestRom(rmGDestRomIdx);
    PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfRmGDestRom(rmGDestRomIdx);

    PduR_SetTransmissionActiveOfRmGDestNto1InfoRam(rmGDestNto1InfoIdx, FALSE, memIdx);  /* SBSW_PDUR_IDX_PARAM_INTERNAL_FUNCTION */
    PduR_SetRmDestRomIdxOfRmGDestNto1InfoRam(rmGDestNto1InfoIdx, PDUR_NO_RMDESTROMIDXOFRMGDESTNTO1INFORAM, memIdx);     /* SBSW_PDUR_IDX_PARAM_INTERNAL_FUNCTION */
  }
}
#endif

/**********************************************************************************************************************
 * PduR_InitMemory
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_InitMemory(void)
{
  PduR_PreInitialized = FALSE;
#if(PDUR_USE_INIT_POINTER == STD_ON)
  PduR_ConfigDataPtr = NULL_PTR;
#endif
}

#if (PDUR_RPGROM == STD_ON)
/**********************************************************************************************************************
 * PduR_EnableRouting
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_EnableRouting(PduR_RoutingPathGroupIdType id)
{
  uint8 errorId = PDUR_E_NO_ERROR;      /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
# if (PDUR_DEV_ERROR_DETECT == STD_ON)  /* COV_PDUR_VAR_DEV_ERROR_DETECT */
  if(!PduR_IsPreInitialized())
  {
    errorId = PDUR_E_INVALID_REQUEST;
  }
  else if(!PduR_IsInitialized(PduR_GetMemIdx()))
  {
    errorId = PDUR_E_INVALID_REQUEST;
  }
  else if(id >= PduR_GetSizeOfRpgExtIdRom())
  {
    errorId = PDUR_E_ROUTING_PATH_GROUP_ID_INVALID;
  }
#  if(PDUR_INVALIDHNDOFRPGEXTIDROM == STD_ON)
  else if(PduR_IsInvalidHndOfRpgExtIdRom(id))
  {
    errorId = PDUR_E_ROUTING_PATH_GROUP_ID_INVALID;
  }
#  endif
  else
# endif
  {
    PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfRpgExtIdRom(id);
    PduR_RpgRomIdxOfRpgExtIdRomType rpgRomIdx = PduR_GetRpgRomIdxOfRpgExtIdRom(id);

    /* ----- Implementation ----------------------------------------------- */
    if(!PduR_IsEnabledOfRpgRam(rpgRomIdx, memIdx))
    {
      PduR_RmDestRpgRomIndIterType rmDestRpgRomIndIdx;
      for(rmDestRpgRomIndIdx = PduR_GetRmDestRpgRomIndStartIdxOfRpgRom(rpgRomIdx, memIdx); rmDestRpgRomIndIdx < PduR_GetRmDestRpgRomIndEndIdxOfRpgRom(rpgRomIdx, memIdx); rmDestRpgRomIndIdx++)
      {
        PduR_RmDestRpgRomIterType rmDestRpgRomIdx = PduR_GetRmDestRpgRomInd(rmDestRpgRomIndIdx, memIdx);
        PduR_RmDestRomIterType rmDestRomIdx = PduR_GetRmDestRomIdxOfRmDestRpgRom(rmDestRpgRomIdx, memIdx);
        PduR_Lock_LockRoutingPathByDestPdu(rmDestRomIdx);
        {
          PduR_SetEnabledCntOfRmDestRpgRam(rmDestRpgRomIdx, PduR_GetEnabledCntOfRmDestRpgRam(rmDestRpgRomIdx, memIdx) + 1u, memIdx);    /* SBSW_PDUR_CSL03 */
        }
        PduR_Lock_UnlockRoutingPathByDestPdu(rmDestRomIdx);
      }
      PduR_SetEnabledOfRpgRam(rpgRomIdx, TRUE, memIdx);        /* SBSW_PDUR_CSL01 */
    }
  }
  /* ----- Development Error Report --------------------------------------- */
# if (PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR)
  {
    PduR_Det_ReportError(PDUR_FCT_ENABLEROUTING, errorId);
  }
# else
  PDUR_DUMMY_STATEMENT(errorId);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
# endif
}       /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if (PDUR_RPGROM == STD_ON)
/**********************************************************************************************************************
 * PduR_DisableRouting
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_DisableRouting(PduR_RoutingPathGroupIdType id)
{
  uint8 errorId = PDUR_E_NO_ERROR;      /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
# if (PDUR_DEV_ERROR_DETECT == STD_ON)  /* COV_PDUR_VAR_DEV_ERROR_DETECT */
  if(!PduR_IsPreInitialized())
  {
    errorId = PDUR_E_INVALID_REQUEST;
  }
  else if(!PduR_IsInitialized(PduR_GetMemIdx()))
  {
    errorId = PDUR_E_INVALID_REQUEST;
  }
  else if(id >= PduR_GetSizeOfRpgExtIdRom())
  {
    errorId = PDUR_E_ROUTING_PATH_GROUP_ID_INVALID;
  }
#  if(PDUR_INVALIDHNDOFRPGEXTIDROM == STD_ON)
  else if(PduR_IsInvalidHndOfRpgExtIdRom(id))
  {
    errorId = PDUR_E_ROUTING_PATH_GROUP_ID_INVALID;
  }
#  endif
  else
# endif
  {
    PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfRpgExtIdRom(id);
    PduR_RpgRomIdxOfRpgExtIdRomType rpgRomIdx = PduR_GetRpgRomIdxOfRpgExtIdRom(id);

    /* ----- Implementation ----------------------------------------------- */
    if(PduR_IsEnabledOfRpgRam(rpgRomIdx, memIdx))
    {
      PduR_RmDestRpgRomIndIterType rmDestRpgRomIndIdx;
      for(rmDestRpgRomIndIdx = PduR_GetRmDestRpgRomIndStartIdxOfRpgRom(rpgRomIdx, memIdx); rmDestRpgRomIndIdx < PduR_GetRmDestRpgRomIndEndIdxOfRpgRom(rpgRomIdx, memIdx); rmDestRpgRomIndIdx++)
      {
        PduR_RmDestRpgRomIterType rmDestRpgRomIdx = PduR_GetRmDestRpgRomInd(rmDestRpgRomIndIdx, memIdx);
        PduR_RmDestRomIterType rmDestRomIdx = PduR_GetRmDestRomIdxOfRmDestRpgRom(rmDestRpgRomIdx, memIdx);
        PduR_Lock_LockRoutingPathByDestPdu(rmDestRomIdx);
        {
# if (PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
          if(PDUR_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == PduR_GetRoutingTypeOfRmDestRom(rmDestRomIdx))   /* COV_PDUR_FEATURE_ALWAYS_TRUE */
          {
            PduR_RmIf_DisableRoutingAction(rmDestRomIdx);
          }
# endif
# if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
          if(PDUR_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == PduR_GetRoutingTypeOfRmDestRom(rmDestRomIdx))
          {
            PduR_RmTp_TpDisableRouting_TpTxSmStateHandler(rmDestRomIdx);
          }
# endif
          PduR_SetEnabledCntOfRmDestRpgRam(rmDestRpgRomIdx, (PduR_GetEnabledCntOfRmDestRpgRam(rmDestRpgRomIdx, memIdx) - 1u), memIdx);  /* SBSW_PDUR_CSL03 */
        }
        PduR_Lock_UnlockRoutingPathByDestPdu(rmDestRomIdx);
      }
      PduR_SetEnabledOfRpgRam(rpgRomIdx, FALSE, memIdx);       /* SBSW_PDUR_CSL01 */
    }
  }
  /* ----- Development Error Report --------------------------------------- */
# if (PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR)
  {
    PduR_Det_ReportError(PDUR_FCT_DISABLEROUTING, errorId);
  }
# else
  PDUR_DUMMY_STATEMENT(errorId);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
# endif
}       /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if (PDUR_RPGROM == STD_ON)
/**********************************************************************************************************************
 * PduR_IsDestPduEnabled
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
FUNC(boolean, PDUR_CODE) PduR_IsDestPduEnabled(PduR_RmDestRomIterType rmDestRomIdx)
{
  PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfRmDestRom(rmDestRomIdx);

  return (!PduR_IsRmDestRpgRomUsedOfRmDestRom(rmDestRomIdx)) || (0u != PduR_GetEnabledCntOfRmDestRpgRam(PduR_GetRmDestRpgRomIdxOfRmDestRom(rmDestRomIdx), memIdx));
}
#endif

#if ((PDUR_MAIN_FUNCTION == STD_ON) && ((PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)))
/**********************************************************************************************************************
 * PduR_DispatchMainfuntion
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_DispatchMainfuntion(PduR_RmGDestRomIterType rmGDestRomIdx)
{
# if(PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
  if(PduR_IsRmBufferedIfPropertiesRomUsedOfRmGDestRom(rmGDestRomIdx))   /* COV_PDUR_FEATURE_ALWAYS_TRUE */
  {
    PduR_RmIf_MainFunction(rmGDestRomIdx);
  }
# endif
# if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
  if(PduR_IsRmGDestTpTxStateRamUsedOfRmGDestRom(rmGDestRomIdx))
  {
    PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfRmGDestRom(rmGDestRomIdx);

    PduR_RmTp_TxInst_MainFunction(rmGDestRomIdx, memIdx);
  }
# endif
}
#endif

#if (PDUR_BSWMPDURPRETRANSMITCALLBACKOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_CallPreTransmitCallout
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_CallPreTransmitCallout(PduR_RmDestRomIterType rmDestRomIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info)
{
  if(PduR_IsBswMPduRPreTransmitCallbackOfRmDestRom(rmDestRomIdx))
  {
    BswM_PduR_PreTransmit(PduR_GetTxIf2UpIdxOfRmGDestRom(PduR_GetRmGDestRomIdxOfRmDestRom(rmDestRomIdx)), info);  /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ID_AND_PTR */
  }
}
#endif

#if (PDUR_DEFERREDEVENTCACHEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_EvC_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_EvC_Init(PduR_MemIdxType memIdx)
{
  PduR_DeferredEventCacheRomIterType deferredEventCacheRomIdx;
  for(deferredEventCacheRomIdx = 0u; deferredEventCacheRomIdx < PduR_GetSizeOfDeferredEventCacheRom(memIdx); deferredEventCacheRomIdx++)
  {
    PduR_DeferredEventCacheArrayRamStartIdxOfDeferredEventCacheRomType startIdxOfBuffer = PduR_GetDeferredEventCacheArrayRamStartIdxOfDeferredEventCacheRom(deferredEventCacheRomIdx, memIdx);

    PduR_SetDeferredEventCacheArrayRamReadIdxOfDeferredEventCacheRam(deferredEventCacheRomIdx, startIdxOfBuffer, memIdx);       /* SBSW_PDUR_CSL02 */
    PduR_SetDeferredEventCacheArrayRamWriteIdxOfDeferredEventCacheRam(deferredEventCacheRomIdx, startIdxOfBuffer, memIdx);      /* SBSW_PDUR_CSL02 */
  }
}
#endif

#if (PDUR_DEFERREDEVENTCACHEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_EvC_Put
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_EvC_Put(PduR_DeferredEventCacheRomIdxOfSrcApplicationRomType deferredEventCacheIdx, PduR_RmGDestRomIterType rmGDestRomIdx, PduR_MemIdxType memIdx)
{
  Std_ReturnType retVal = E_NOT_OK;

  SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_0();
  {
    PduR_DeferredEventCacheArrayRamReadIdxOfDeferredEventCacheRamType readIdx = PduR_EvC_GetDeferredEventCacheArrayRamReadIdxSafe(deferredEventCacheIdx, memIdx);
    PduR_DeferredEventCacheArrayRamWriteIdxOfDeferredEventCacheRamType writeIdx = PduR_EvC_GetDeferredEventCacheArrayRamWriteIdxSafe(deferredEventCacheIdx, memIdx);

    if(writeIdx < PduR_GetSizeOfDeferredEventCacheArrayRam(memIdx))   /* COV_PDUR_VAR_FATAL_ERROR */
    {
      PduR_DeferredEventCacheArrayRamStartIdxOfDeferredEventCacheRomType startIdxOfBuffer = PduR_GetDeferredEventCacheArrayRamStartIdxOfDeferredEventCacheRom(deferredEventCacheIdx, memIdx);
      PduR_DeferredEventCacheArrayRamEndIdxOfDeferredEventCacheRomType endIdxOfBuffer = PduR_GetDeferredEventCacheArrayRamEndIdxOfDeferredEventCacheRom(deferredEventCacheIdx, memIdx) - 1u;    /* ComStackLibs EndIdx is actually the first out of bounds index */

      /* If event cache is full, return E_NOT_OK */
      if(PduR_EvC_IsFull(deferredEventCacheIdx, memIdx) == TRUE)
      {
        /* Buffer is full */
        retVal = E_NOT_OK;
      }
      /* else if write index < read index, put rmGDestRomIdx into cache and increase write idx */
      else if(writeIdx < readIdx)       /* write is possible until read Idx is reached. Could be too small though */
      {
        PduR_SetRmGDestRomIdxOfDeferredEventCacheArrayRam(writeIdx, (PduR_RmGDestRomIdxOfDeferredEventCacheArrayRamType) rmGDestRomIdx, memIdx);        /* SBSW_PDUR_EVC_PUT_RTCHECK */
        PduR_SetDeferredEventCacheArrayRamWriteIdxOfDeferredEventCacheRam(deferredEventCacheIdx, writeIdx + 1u, memIdx);        /* SBSW_PDUR_IDX_PARAM_INTERNAL_FUNCTION */
        retVal = E_OK;
      }
      /* else */
      else
      { /* readIdx < writeIdx OR readIdx == writeIdx */
        /* put rmGDestRomIdx into cache */
        PduR_SetRmGDestRomIdxOfDeferredEventCacheArrayRam(writeIdx, (PduR_RmGDestRomIdxOfDeferredEventCacheArrayRamType) rmGDestRomIdx, memIdx);        /* SBSW_PDUR_EVC_PUT_RTCHECK */

        /* Wrap around write index if required or increase write index otherwise */
        if(writeIdx == endIdxOfBuffer)
        {
          PduR_SetDeferredEventCacheArrayRamWriteIdxOfDeferredEventCacheRam(deferredEventCacheIdx, startIdxOfBuffer, memIdx);   /* SBSW_PDUR_IDX_PARAM_INTERNAL_FUNCTION */
        }
        else
        {
          PduR_SetDeferredEventCacheArrayRamWriteIdxOfDeferredEventCacheRam(deferredEventCacheIdx, writeIdx + 1u, memIdx);      /* SBSW_PDUR_IDX_PARAM_INTERNAL_FUNCTION */
        }
        retVal = E_OK;
      }
    }
    else
    {
      PduR_Det_ReportError(PDUR_EVC_PUT, PDUR_E_FATAL);
    }
  }
  SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_0();

  return retVal;
}
#endif

#if (PDUR_DEFERREDEVENTCACHEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_EvC_WriteDeferredEventCache
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_EvC_WriteDeferredEventCache(PduR_RmDestRomIterType rmDest, PduR_RmGDestRomIdxOfRmDestRomType rmGDest)
{
  /* Put destination handle into the deferred event queue */
  PduR_DestApplicationManagerRomIterType srcApplicationIdx  = PduR_GetDestApplicationManagerRomIdxOfRmSrcRom(PduR_GetRmSrcRomIdxOfRmDestRom(rmDest));
  PduR_DestApplicationManagerRomIterType destApplicationIdx = PduR_GetDestApplicationManagerRomIdxOfRmGDestRom(rmGDest);
  PduR_SrcApplicationRomIterType dest2srcApplicationRomIdx = PduR_GetSrcApplicationRomStartIdxOfDestApplicationManagerRom(destApplicationIdx) + (PduR_SrcApplicationRomIterType) srcApplicationIdx;

  (void) PduR_EvC_Put(PduR_GetDeferredEventCacheRomIdxOfSrcApplicationRom(dest2srcApplicationRomIdx), rmGDest, PduR_GetPartitionIndexOfCslOfSrcApplicationRom(dest2srcApplicationRomIdx));
}
#endif

#if (PDUR_DEFERREDEVENTCACHEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_EvC_Get
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_EvC_Get(PduR_DeferredEventCacheRomIdxOfSrcApplicationRomType deferredEventCacheIdx, P2VAR(PduR_RmGDestRomIterType, AUTOMATIC, PDUR_APPL_DATA) rmGDestRomIdxPtr, PduR_MemIdxType memIdx)
{
  Std_ReturnType retVal;

  SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_0();
  {
    PduR_DeferredEventCacheArrayRamReadIdxOfDeferredEventCacheRamType readIdx = PduR_EvC_GetDeferredEventCacheArrayRamReadIdxSafe(deferredEventCacheIdx, memIdx);
    PduR_DeferredEventCacheArrayRamWriteIdxOfDeferredEventCacheRamType writeIdx = PduR_EvC_GetDeferredEventCacheArrayRamWriteIdxSafe(deferredEventCacheIdx, memIdx);

    /* If buffer is empty, return E_NOT_OK */
    if(readIdx == writeIdx)
    {
      retVal = E_NOT_OK;
    }
    /* Otherwise */
    else
    {
      PduR_DeferredEventCacheArrayRamStartIdxOfDeferredEventCacheRomType startIdxOfBuffer = PduR_GetDeferredEventCacheArrayRamStartIdxOfDeferredEventCacheRom(deferredEventCacheIdx, memIdx);
      PduR_DeferredEventCacheArrayRamEndIdxOfDeferredEventCacheRomType endIdxOfBuffer = PduR_GetDeferredEventCacheArrayRamEndIdxOfDeferredEventCacheRom(deferredEventCacheIdx, memIdx) - 1u;    /* ComStackLibs EndIdx is actually the first out of bounds index */

      /* Read RmGDestRomIdx from Cache */
      *rmGDestRomIdxPtr = PduR_GetRmGDestRomIdxOfDeferredEventCacheArrayRam(readIdx, memIdx);   /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */

      /* Increase read index to next element. Wrap around if required. */
      if(readIdx == endIdxOfBuffer)
      {
        PduR_SetDeferredEventCacheArrayRamReadIdxOfDeferredEventCacheRam(deferredEventCacheIdx, startIdxOfBuffer, memIdx);      /* SBSW_PDUR_IDX_PARAM_INTERNAL_FUNCTION */
      }
      else
      {
        PduR_SetDeferredEventCacheArrayRamReadIdxOfDeferredEventCacheRam(deferredEventCacheIdx, readIdx + 1u, memIdx);  /* SBSW_PDUR_IDX_PARAM_INTERNAL_FUNCTION */
      }

      /* Return E_OK */
      retVal = E_OK;
    }
  }
  SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_0();

  return retVal;
}
#endif

#if (PDUR_DEFERREDEVENTCACHEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_EvC_ReadFlush
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_EvC_ReadFlush(PduR_DeferredEventCacheRomIdxOfSrcApplicationRomType deferredEventCacheIdx, PduR_MemIdxType memIdx)
{
  PduR_SetDeferredEventCacheArrayRamReadIdxOfDeferredEventCacheRam(deferredEventCacheIdx, PduR_EvC_GetDeferredEventCacheArrayRamWriteIdxSafe(deferredEventCacheIdx, memIdx), memIdx);    /* SBSW_PDUR_IDX_PARAM_INTERNAL_FUNCTION */
}
#endif

#if (PDUR_DEFERREDEVENTCACHEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_EvC_GetDeferredEventCacheArrayRamReadIdxSafe
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(PduR_DeferredEventCacheArrayRamReadIdxOfDeferredEventCacheRamType, PDUR_CODE) PduR_EvC_GetDeferredEventCacheArrayRamReadIdxSafe(PduR_DeferredEventCacheRomIdxOfSrcApplicationRomType deferredEventCacheIdx, PduR_MemIdxType memIdx)
{
  PduR_DeferredEventCacheArrayRamReadIdxOfDeferredEventCacheRamType readIdx = PduR_GetDeferredEventCacheArrayRamReadIdxOfDeferredEventCacheRam(deferredEventCacheIdx, memIdx);

# if (PDUR_EXTENDED_ERROR_CHECKS == STD_ON)
  PduR_DeferredEventCacheArrayRamStartIdxOfDeferredEventCacheRomType startIdxOfBuffer = PduR_GetDeferredEventCacheArrayRamStartIdxOfDeferredEventCacheRom(deferredEventCacheIdx, memIdx);
  PduR_DeferredEventCacheArrayRamEndIdxOfDeferredEventCacheRomType endIdxOfBuffer = PduR_GetDeferredEventCacheArrayRamEndIdxOfDeferredEventCacheRom(deferredEventCacheIdx, memIdx);

  if(readIdx >= endIdxOfBuffer) /* COV_PDUR_EXTENDED_ERROR_CHECKS */
  {
    readIdx = endIdxOfBuffer - 1u;
    PduR_ReportRuntimeDetError(PDUR_FCT_GETEVCREADIDX, PDUR_E_IDXOUTOFBOUNDS);
  }
  if(readIdx < startIdxOfBuffer) /* COV_PDUR_EXTENDED_ERROR_CHECKS */
  {
    readIdx = startIdxOfBuffer;
    PduR_ReportRuntimeDetError(PDUR_FCT_GETEVCREADIDX, PDUR_E_IDXOUTOFBOUNDS);
  }
# endif

  return readIdx;
}
#endif

#if (PDUR_DEFERREDEVENTCACHEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_EvC_GetDeferredEventCacheArrayRamWriteIdxSafe
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(PduR_DeferredEventCacheArrayRamWriteIdxOfDeferredEventCacheRamType, PDUR_CODE) PduR_EvC_GetDeferredEventCacheArrayRamWriteIdxSafe(PduR_DeferredEventCacheRomIdxOfSrcApplicationRomType deferredEventCacheIdx, PduR_MemIdxType memIdx)
{
  PduR_DeferredEventCacheArrayRamWriteIdxOfDeferredEventCacheRamType writeIdx = PduR_GetDeferredEventCacheArrayRamWriteIdxOfDeferredEventCacheRam(deferredEventCacheIdx, memIdx);

# if (PDUR_EXTENDED_ERROR_CHECKS == STD_ON)
  PduR_DeferredEventCacheArrayRamStartIdxOfDeferredEventCacheRomType startIdxOfBuffer = PduR_GetDeferredEventCacheArrayRamStartIdxOfDeferredEventCacheRom(deferredEventCacheIdx, memIdx);
  PduR_DeferredEventCacheArrayRamEndIdxOfDeferredEventCacheRomType endIdxOfBuffer = PduR_GetDeferredEventCacheArrayRamEndIdxOfDeferredEventCacheRom(deferredEventCacheIdx, memIdx);

  if(writeIdx >= endIdxOfBuffer) /* COV_PDUR_EXTENDED_ERROR_CHECKS */
  {
    writeIdx = endIdxOfBuffer - 1u;
    PduR_ReportRuntimeDetError(PDUR_FCT_GETEVCWRITEIDX, PDUR_E_IDXOUTOFBOUNDS);
  }
  if(writeIdx < startIdxOfBuffer) /* COV_PDUR_EXTENDED_ERROR_CHECKS */
  {
    writeIdx = startIdxOfBuffer;
    PduR_ReportRuntimeDetError(PDUR_FCT_GETEVCWRITEIDX, PDUR_E_IDXOUTOFBOUNDS);
  }
# endif

  return writeIdx;
}
#endif

#if (PDUR_DEFERREDEVENTCACHEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_EvC_IsFull
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_EvC_IsFull(PduR_DeferredEventCacheRomIdxOfSrcApplicationRomType deferredEventCacheIdx, PduR_MemIdxType memIdx)
{
  boolean retVal;

  SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_0();
  {
    PduR_DeferredEventCacheArrayRamReadIdxOfDeferredEventCacheRamType readIdx = PduR_EvC_GetDeferredEventCacheArrayRamReadIdxSafe(deferredEventCacheIdx, memIdx);
    PduR_DeferredEventCacheArrayRamWriteIdxOfDeferredEventCacheRamType writeIdx = PduR_EvC_GetDeferredEventCacheArrayRamWriteIdxSafe(deferredEventCacheIdx, memIdx);

    PduR_DeferredEventCacheArrayRamStartIdxOfDeferredEventCacheRomType startIdxOfBuffer = PduR_GetDeferredEventCacheArrayRamStartIdxOfDeferredEventCacheRom(deferredEventCacheIdx, memIdx);
    PduR_DeferredEventCacheArrayRamEndIdxOfDeferredEventCacheRomType endIdxOfBuffer = PduR_GetDeferredEventCacheArrayRamEndIdxOfDeferredEventCacheRom(deferredEventCacheIdx, memIdx) - 1u;      /* ComStackLibs EndIdx is actually the first out of bounds index */

    if(((writeIdx + 1u) == readIdx) || ((readIdx == startIdxOfBuffer) && (writeIdx == endIdxOfBuffer)))
    {
      /* Buffer is full */
      retVal = TRUE;
    }
    else
    {
      retVal = FALSE;
    }
  }
  SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_0();

  return retVal;
}
#endif

#if (PDUR_DEFERREDEVENTCACHEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_EvC_IsAnyEvCOverflowed
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_EvC_IsAnyEvCOverflowed(PduR_DestApplicationManagerRomIterType destApplicationManagerRomIdx)
{
  PduR_SrcApplicationRomEndIdxOfDestApplicationManagerRomType srcApplicationRomIdx;
  boolean anyEventQueueIsOverflowed = FALSE;

  /* Check if any event queue has overflowed */
  for(srcApplicationRomIdx = PduR_GetSrcApplicationRomStartIdxOfDestApplicationManagerRom(destApplicationManagerRomIdx); srcApplicationRomIdx < PduR_GetSrcApplicationRomEndIdxOfDestApplicationManagerRom(destApplicationManagerRomIdx); srcApplicationRomIdx++)
  {
    PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfSrcApplicationRom(srcApplicationRomIdx);
    boolean isEvCFull = PduR_EvC_IsFull(PduR_GetDeferredEventCacheRomIdxOfSrcApplicationRom(srcApplicationRomIdx), memIdx);

    if (isEvCFull)
    {
      anyEventQueueIsOverflowed = TRUE;
      break;
    }
  }

  return anyEventQueueIsOverflowed;
}
#endif

#if (PDUR_DEFERREDEVENTCACHEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_EvC_FlushAllEvCOfDestApplication
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_EvC_FlushAllEvCOfDestApplication(PduR_DestApplicationManagerRomIterType destApplicationManagerRomIdx)
{
  PduR_SrcApplicationRomEndIdxOfDestApplicationManagerRomType srcApplicationRomIdx;

  /* Flush Queues */
  for(srcApplicationRomIdx = PduR_GetSrcApplicationRomStartIdxOfDestApplicationManagerRom(destApplicationManagerRomIdx); srcApplicationRomIdx < PduR_GetSrcApplicationRomEndIdxOfDestApplicationManagerRom(destApplicationManagerRomIdx); srcApplicationRomIdx++)
  {
    PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfSrcApplicationRom(srcApplicationRomIdx);

    PduR_EvC_ReadFlush(PduR_GetDeferredEventCacheRomIdxOfSrcApplicationRom(srcApplicationRomIdx), memIdx);
  }
}
#endif

#if (PDUR_DEFERREDEVENTCACHEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_EvC_ReadAndProcessEvCOfDestApplication
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_EvC_ReadAndProcessEvCOfDestApplication(PduR_DestApplicationManagerRomIterType destApplicationManagerRomIdx)
{
  PduR_SrcApplicationRomEndIdxOfDestApplicationManagerRomType srcApplicationRomIdx;

  for(srcApplicationRomIdx = PduR_GetSrcApplicationRomStartIdxOfDestApplicationManagerRom(destApplicationManagerRomIdx); srcApplicationRomIdx < PduR_GetSrcApplicationRomEndIdxOfDestApplicationManagerRom(destApplicationManagerRomIdx); srcApplicationRomIdx++)
  {
    PduR_RmGDestRomIterType rmGDestRomIdx;
    PduR_DeferredEventCacheRomIdxOfSrcApplicationRomType deferredEventCacheRomIdx = PduR_GetDeferredEventCacheRomIdxOfSrcApplicationRom(srcApplicationRomIdx);
    PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfSrcApplicationRom(srcApplicationRomIdx);
    PduR_DeferredEventCacheArrayRamLengthOfDeferredEventCacheRomType readLimit = PduR_GetDeferredEventCacheArrayRamLengthOfDeferredEventCacheRom(deferredEventCacheRomIdx, memIdx);

    while(PduR_EvC_Get(deferredEventCacheRomIdx, &rmGDestRomIdx, memIdx) == E_OK)       /* SBSW_PDUR_STACK_VARIABLE */
    {
      if(PduR_IsRmGDestIdxValidOnApplication(rmGDestRomIdx, destApplicationManagerRomIdx) == TRUE) /* COV_PDUR_ROBUSTNESS */
      {
        PduR_DispatchMainfuntion(rmGDestRomIdx);
      }
      readLimit--;
      if(readLimit == 0u)       /* COV_PDUR_DEFERRED_EVENT_CACHE_READLIMIT */
      {
        break;
      }
    }
  }
}
#endif

#if ((PDUR_MAIN_FUNCTION == STD_ON) && ((PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)))
/**********************************************************************************************************************
 * PduR_ProcessAllDestinationsOfDestApplication
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_ProcessAllDestinationsOfDestApplication(PduR_DestApplicationManagerRomIterType destApplicationManagerRomIdx)
{
  PduR_RmGDestRomIterType rmGDestRomIdx;

  for(rmGDestRomIdx = PduR_GetRmGDestRomStartIdxOfDestApplicationManagerRom(destApplicationManagerRomIdx); rmGDestRomIdx < PduR_GetRmGDestRomEndIdxOfDestApplicationManagerRom(destApplicationManagerRomIdx); rmGDestRomIdx++)
  {
    PduR_DispatchMainfuntion(rmGDestRomIdx);
  }
}
#endif

#if (PDUR_DEFERREDEVENTCACHEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_IsRmGDestIdxValidOnApplication
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_IsRmGDestIdxValidOnApplication(PduR_RmGDestRomIterType rmGDestRomIdx, PduR_DestApplicationManagerRomIterType applicationId)
{
  boolean retVal;

  PduR_DestApplicationManagerRomIterType supposedApplicationId = PduR_GetDestApplicationManagerRomIdxOfRmGDestRom(rmGDestRomIdx);

  if(applicationId == supposedApplicationId) /* COV_PDUR_ROBUSTNESS */
  {
    retVal = TRUE;
  }
  else
  {
    retVal = FALSE;
  }

  return retVal;
}
#endif

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"    /* PRQA S 5087 */        /* MD_MSR_MemMap */

/**********************************************************************************************************************
 * GLOBAL MISRA / PCLINT JUSTIFICATION
 *********************************************************************************************************************/
/* module specific MISRA deviations:
  MD_PduR_1505:  Misra Rule 8.7
     Reason:      It depends on the configuration if the function is only referenced in the translation unit is is defined or not.
     Risk:        No risk.
     Prevention:  No prevention necessary.

  MD_PduR_1336: Misra Rule 8.2
     Reason:      No identifier name needed in a function pointer typedef.
     Risk:        No risk, because only warning that with a identifier name the readability is better.
     Prevention:  No prevention necessary.

  MD_PduR_2842
     Reason:      Index Access using the ComStackLib.
     Risk:        No risk, because qualified use-case CSL02 of ComStackLib.
     Prevention:  No prevention necessary.

  MD_PduR_2983: Misra Rule 2.2
     Reason:      The value is modified to be used in the next iteration. It depends on the configuration if the loop consists of more than one iteration.
     Risk:        No risk, as the assigned value is only not used subsequently.
     Prevention:  No prevention necessary.

  MD_PduR_2985: Misra Rule 2.2
     Reason:      The value of the result is only that of the left-hand operand for the first iteration. It depends on the configuration it there will be more than one iteration step.
     Risk:        No risk, as the bitwise operation is only redundant.
     Prevention:  No prevention necessary.

  MD_PduR_2995_2996: Misra Rule 2.2
     Reason:      Depending on the configuration the check might always be true or false.
     Risk:        No risk, as the evaluation of the boolean expression depends on the configuration.
     Prevention:  No prevention necessary.

  MD_PduR_2991: Misra Rule 14.3
     Reason:      The value of the if-controlling expression depends on the configuration.
     Risk:        No risk.
     Prevention:  No prevention necessary.

  MD_PduR_2880: Misra Rule 2.1
     Reason:      Code might not be reachable depending on the configuration.
     Risk:        No risk.
     Prevention:  No prevention necessary.

  MD_PduR_3415: Misra Rule 13.5
     Reason:      The right hand operand is known to have no side effects.
     Risk:        No risk.
     Prevention:  No prevention necessary.

  MD_PduR_3451_3449: Misra Rule 8.8
  Reason:         The global identifier has been declared in more than one file. the function declaration has to be in
                  the PduR_<Module>.h. Affected APIs are CancelReceive, CancelTransmit and ChangeParameter.
  Risk:           no risk.
  Prevention:     To avoid a duplicate declaration use the BSW-Module "use-Tag" flag.
  
  MD_PduR_DistinctIdentifiers: Misra Rule 5.5
  Reason:         Generated symbols may exceed the 31 character limitation, because the code 
                  generator concatenates strings based on fixed rules.
  Risk:           The linker or compiler may mismatch symbols.
  Prevention:     Modern compilers for AUTOSAR platforms do not have this limitation anymore. 
*/

/* *INDENT-OFF* */
/* SBSW_JUSTIFICATION_BEGIN

  \ID SBSW_PDUR_IDX_PARAM_INTERNAL_FUNCTION
    \DESCRIPTION The index is passed to an internal function as parameter and is used within the function to write to a memory location.
    \COUNTERMEASURE \N The index is read by the calling function using the ComStackLib macros. The ComStackLib ensures that the index is valid.

  \ID SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION
    \DESCRIPTION A pointer is written or passed to a function. The pointer can possibly be used to write to the corresponding memory location.
    \COUNTERMEASURE \N The calling function ensures that the pointer is valid.

  \ID SBSW_PDUR_STACK_VARIABLE
    \DESCRIPTION A pointer is passed to a function. The pointer can possibly be used to write to the corresponding memory location.
    \COUNTERMEASURE \N The pointer points to a local stack variable, therefore it's always valid.

  \ID SBSW_PDUR_GETVERSION_PARAM
    \DESCRIPTION    The PduR_GetVersionInfo writes to the 'versioninfo' pointer parameter. It is checked against NULL,
                    but this does not guarantee that the referenced memory is valid.
    \COUNTERMEASURE \N  Pointers passed to public PduR APIs point to a valid memory range. A general countermeasure is included in the safety manual.

  \ID SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR
    \DESCRIPTION    The API is called with an Id and a pointer.
                    The API call is forwarded using a function pointer which is read using ComStackLib macros.

    \COUNTERMEASURE \N The function pointer is read using the passed Id and ComStackLib macros.
                       The Id is a SNV provided by the lower layer. It is checked when it was first passed to the PduR module.
                       The pointer is either forwarded and assumed to be valid or it is a local stack variable.

  \ID SBSW_PDUR_API_CALL_FORWARDING_ID_ONLY
    \DESCRIPTION    The API is called with an Id.
                    The API call is forwarded using a function pointer which is read using ComStackLib macros.
    \COUNTERMEASURE \R The function pointer is read using the passed Id and ComStackLib macros.
                       The Id is a SNV provided by the lower layer.
                       It is checked when it was first passed to the PduR module.

  \ID SBSW_PDUR_MEM_CPY_FIFOMGR
    \DESCRIPTION Call to copy RAM data to RAM
    \COUNTERMEASURE \N The passed pointers are either read by ComStackLib macros or are passed through and checked by one of the calling functions.
                       The size of the copy operation is always equal or less than the size of the destination buffer. This is ensured by the calling function.

  \ID SBSW_PDUR_MEM_CPY_RAM2RAM
    \DESCRIPTION Call to copy RAM data to RAM
    \COUNTERMEASURE \R The passed pointers are either read by ComStackLib macros or are passed through and checked by one of the calling functions.
                    \R The size of the copy operation is checked against the remaining free buffer space.

  \ID SBSW_PDUR_WRITE_TRANSMIT_OR_INDICATION_QUEUE
    \DESCRIPTION Data is written into the indication or transmit queue.
    \COUNTERMEASURE \R The passed index will always be within range of the indication or transmit queue as it is caluclated considering the length of the queue.

  \ID SBSW_PDUR_CORE_ID_RTCHECK
    \DESCRIPTION Array write access. Core Id is retrieved over OS API and respective counter is modified.
    \COUNTERMEASURE  \R Runtime check assures, core Id is always within the bounds of counter array.

  \ID SBSW_PDUR_MCQ_RAMARRAY_RTCHECK
    \DESCRIPTION Array write access. Write Idx is calculated from caller.
    \COUNTERMEASURE  \R Runtime check assures, write idx is always within the bound of the RamArray.

  \ID SBSW_PDUR_MCQ_RAMARRAY_RTCHECK_FCTCALL
    \DESCRIPTION The address of the provided destination pointer is retrieved via CSL Macros. Source pointer is only read.
    \COUNTERMEASURE  \R Runtime check assures, that the destination has enough space to store the data.

  \ID SBSW_PDUR_EVC_PUT_RTCHECK
    \DESCRIPTION Array write access. Write Idx is read from Ram.
    \COUNTERMEASURE  \R Runtime check assures, write idx is always within the bounds.

  \ID SBSW_PDUR_FCT_CALL_P2CONST
    \DESCRIPTION Function call with constant P2CONST / CONSTP2CONST.
    \COUNTERMEASURE  \N The function is call with pointer for reading purpose only. Content of pointer is not modified.

  \ID SBSW_PDUR_CSL01
    \DESCRIPTION Index Access is using ComStackLib
    \COUNTERMEASURE  \N Qualified use-case CSL01 of ComStackLib.

  \ID SBSW_PDUR_CSL02
    \DESCRIPTION  Access of Table1, via indirection over Table2
                  with same index using ComStackLib.
    \COUNTERMEASURE \N Qualified use-case CSL02 of ComStackLib

  \ID SBSW_PDUR_CSL03
    \DESCRIPTION Access to Table1 via indirection over Table2.
    \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

  \ID SBSW_PDUR_CSL_VAR_ACCESS
    \DESCRIPTION A ComStackLib generated variable is accessed.
    \COUNTERMEASURE \N The variable is written using a generated macro of the CSL. It immediately dereferences the variables address without pointer arithmetic.

  SBSW_JUSTIFICATION_END */

/*
  SBSW_PDUR_CSL01 Boundary check using generated identifiers:
  Table1 -- Size of the table itself

  SBSW_PDUR_CSL02 Arrays of same size:
  Table1 -- SizeRelation --> Table2

  SBSW_PDUR_CSL03: Usage of modelled indirections:
  Table1 -- Key Size Relation --> Table2
*/

/* COV_JUSTIFICATION_BEGIN
  \ID COV_PDUR_FEATURE_ALWAYS_TRUE
    \ACCEPT TX
    \ACCEPT TF tx tf
    \ACCEPT TF tf xf
    \ACCEPT TF tf tf tf xf
    \ACCEPT TF tf tx
    \ACCEPT XF tf xf
    \ACCEPT TX tx tx
    \REASON Depending on the configuration the feature check can always be true. In this case the compiler removes the check.

  \ID COV_PDUR_ONLY_TP_QUEUED_ROUTINGS
    \ACCEPT TX
    \REASON The condition is always true if there are only queued transport protocol routings and no unqueued routings in the configuration.

  \ID COV_PDUR_ONLY_DEFERRED_TP_QUEUED_ROUTINGS
    \ACCEPT XF
    \REASON The condition is always false as the transmission to the destination is always successful for deferred routings. It can only fail in the MainFunction context.

  \ID COV_PDUR_NO_DEFERRED_IF_ROUTING
    \ACCEPT X
    \REASON Function is never covered in configurations without deferred If routing paths. The function is always referenced by a function pointer.

  \ID COV_PDUR_NO_DEFERRED_TP_ROUTING
    \ACCEPT X
    \REASON Function is never covered in configurations without deferred Tp routing paths. The function is always referenced by a function pointer.

  \ID COV_PDUR_CROSSCORE_ROUTINGS_ONLY
    \ACCEPT TF tx tf
    \ACCEPT TX
    \ACCEPT XF
    \ACCEPT X
    \REASON Condition can't be covered in configurations with only cross-core routing paths.

  \ID COV_PDUR_ONLY_DIRECT_BUFFER
    \ACCEPT TX
    \ACCEPT TF tx tf
    \REASON In configurations with only direct buffers this is always true. Buffer can't run out as there always will be the shadow buffer.

  \ID COV_PDUR_ONLY_TT_SINGLE_BUFFER
    \ACCEPT XX
    \ACCEPT TX
    \ACCEPT X
    \REASON The code can't be covered in configurations where only trigger transmit single buffer are used.

  \ID COV_PDUR_ONLY_SHARED_OR_DEDICATED_BUFFER
    \ACCEPT TX
    \ACCEPT XF
    \ACCEPT XX
    \REASON This configuration has only shared or dedicated buffer.

  \ID COV_PDUR_CANCELTRANSMIT_WITHOUT_RPG
    \ACCEPT X
    \REASON This case can not be covered without routing path groups being configured.
            The function can only be called once in these configuration and hence it will never be called in this TxInst state.

  \ID COV_PDUR_NO_NTO1_ROUTINGPATHS
    \ACCEPT TX
    \REASON This condition is always true if no N:1 routing paths were configured.

  \ID COV_PDUR_NTO1_GW_ONLY_ROUTINGPATHS
    \ACCEPT TX
    \REASON This condition is always true if there are only N:1 gateway only routing paths configured.

  \ID COV_PDUR_RUNS_ON_ALL_APPLICATIONS
    \APPLYOVERRIDE
    \REASON The PduR is executed on all configured Os Applications. Hence this loop always finds a valid Partition SNV and breaks the loop.

  \ID COV_PDUR_NTO1_NO_BUFFER_GW_ONLY_ROUTINGPATHS
    \ACCEPT XF
    \ACCEPT XX
    \REASON This condition is never true if only no buffer gateway only N:1 routing paths exist.

  \ID COV_PDUR_MISRA
    \ACCEPT X
    \ACCEPT TX
    \REASON [MSR_COV_MISRA]

  \ID COV_PDUR_IF_SDU_LENGTH_HANDLING
    \ACCEPT TX
    \ACCEPT XF
    \ACCEPT XX
    \REASON  If the provided length is greater than the maximum buffer size the value is truncated to this value. Therefore the code code not be reached in case of communication interface routing.

  \ID COV_PDUR_NON_EMPTY_QUEUE
    \ACCEPT TX
    \REASON The fill level is only read from one function and in a context where it is never zero.

  \ID COV_PDUR_IF_ONLY
   \ACCEPT X
   \ACCEPT XX
   \ACCEPT XF
   \ACCEPT TX
   \REASON This is only called if buffered transport protocol routing paths exist. This is not the case for communication interface routing path only configurations.

  \ID COV_PDUR_BUFFER_CALCULATION
   \ACCEPT X
   \ACCEPT XF
   \REASON This function is not called in the context of this state. It still exists to have a correct and complete calculation function.

  \ID COV_PDUR_SPINLOCK_TIMEOUT
   \ACCEPT XF xf xx
   \ACCEPT XF
   \REASON The spinlock timeout can not be tested with the component testsuite.

  \ID COV_PDUR_EXTENDED_ERROR_CHECKS
   \ACCEPT XF
   \ACCEPT TX
   \ACCEPT XF tf xf
   \ACCEPT XF xf xx
   \REASON The extended error checks are not tested by the component testsuite.

  \ID COV_PDUR_FATAL_ERROR
    \ACCEPT X
    \ACCEPT XF
    \ACCEPT TX
    \ACCEPT TF tx tf
    \ACCEPT XF tf xf
    \REASON Fatal error check.

  \ID COV_PDUR_ROBUSTNESS
    \ACCEPT TF tx tf
    \ACCEPT TX tx tx
    \ACCEPT TF tf tx
    \ACCEPT XF
    \ACCEPT TX
    \ACCEPT TF tf tx tf
    \ACCEPT TF tx tf tf
    \ACCEPT TF tx tx tf
    \REASON This check increases robustness. Under normal circumstances it is never false/true.

  \ID COV_PDUR_MCQ_MAIN_FUNCTION_THRESHOLD
    \ACCEPT XF
    \REASON Threshold shall never be violated in the Unit TestSuite. However, threshold check is required to avoid an endless loop under high load.

  \ID COV_PDUR_VAR_FATAL_ERROR
    \ACCEPT TX
    \REASON Fatal error check.

  \ID COV_PDUR_VAR_DEV_ERROR_DETECT
    \ACCEPT TX
    \REASON Det error detection must always be enabled for SafeBsw.

  \ID COV_PDUR_ERROR_NOTIFICATION
    \ACCEPT XF
    \REASON Always false. Feature is not part of SafeBsw.

  \ID COV_PDUR_VAR_DEPENDENT_SWITCH
    \ACCEPT TX
    \ACCEPT TX tx tx
    \REASON The nested switch depends on a previous switch.

  \ID COV_PDUR_VAR_NO_RX_ONLY_CONFIG
    \ACCEPT TX
    \REASON Rx only configurations are not possible. Therefore this switch is always true.

  \ID COV_PDUR_VAR_LINIF_SPECIAL_CONFIGURATION
    \ACCEPT TX
    \REASON This can only be false for LinIf BswModule. Otherwise this Code part is always active if the API is active.

  \ID COV_PDUR_DEFERRED_EVENT_CACHE_READLIMIT
    \ACCEPT XF
    \REASON Statement is only true when events are queued again while others are read at the same time

  \ID COV_PDUR_WRAPPER_FUNC
    \ACCEPT X
    \REASON The wrapper function may not be needed in some configurations.

COV_JUSTIFICATION_END */

/* *INDENT-ON* */

/**********************************************************************************************************************
 * END OF FILE: PduR.c
 *********************************************************************************************************************/
