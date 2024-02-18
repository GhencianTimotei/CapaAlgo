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
/**        \file  Dcm_Ext.c
 *        \brief  Implementation of DCM extensions
 *
 *      \details  MICROSAR DCM based on AR 4.0.3
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
#define DCM_EXT_SOURCE

#ifdef __PRQA__                                                                                                                                      /* COV_DCM_UNSUPPORTED XF */
# pragma PRQA_MACRO_MESSAGES_OFF "Dcm_UtiGetReqData" 2985 /* MD_Dcm_Redundant_2985 */
                                                                                                                                                     /* PRQA S 2991 EOF */ /* MD_Dcm_ConstExpr */
                                                                                                                                                     /* PRQA S 2992 EOF */ /* MD_Dcm_ConstExpr */
                                                                                                                                                     /* PRQA S 2995 EOF */ /* MD_Dcm_ConstExpr */
                                                                                                                                                     /* PRQA S 2996 EOF */ /* MD_Dcm_ConstExpr */
#endif
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Dcm.h"
#include "Rte_Dcm.h"
#if (DCM_SVC_86_NVM_SUPPORT_ENABLED == STD_ON)
# include "NvM.h"
#endif /* (DCM_SVC_86_NVM_SUPPORT_ENABLED == STD_ON) */
#include "Dcm_Int.h"

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
#if (DCM_EXTENSION_ID != 0x96ACD543UL)
# error "Mismatching OEMs between static and generated code"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#if (DCM_SVC_86_SUPPORT_ENABLED == STD_ON)
# define DCM_EXT_SVC_86_READ_TIMEOUT                                 ((Dcm_ExtSvc86RoeTimeoutType)10u)

/* states of the Roe service handler */
# define DCM_EXT_SVC_86_STATE_ACTIVE                                 ((Dcm_ExtSvc86RoeStateType)DCM_ROE_AR_STATE_ACTIVE)
# define DCM_EXT_SVC_86_STATE_INACTIVE                               ((Dcm_ExtSvc86RoeStateType)DCM_ROE_AR_STATE_INACTIVE)
# define DCM_EXT_SVC_86_STATE_CLEARED                                ((Dcm_ExtSvc86RoeStateType)DCM_ROE_AR_STATE_CLEARED)

# define DCM_EXT_SVC_86_STATE_ACTIVE_SETUP_STORED                    ((Dcm_ExtSvc86RoeStateType)0x11u)
# define DCM_EXT_SVC_86_STATE_ACTIVE_SETUP_NOT_STORED                ((Dcm_ExtSvc86RoeStateType)0x12u)
# define DCM_EXT_SVC_86_STATE_INACTIVE_SETUP_NOT_STORED              ((Dcm_ExtSvc86RoeStateType)0x13u)
# define DCM_EXT_SVC_86_STATE_INACTIVE_STOP_NOT_STORED               ((Dcm_ExtSvc86RoeStateType)0x14u)
# define DCM_EXT_SVC_86_STATE_WRITE_NVM_DATA                         ((Dcm_ExtSvc86RoeStateType)0x15u)

/* STRT sending states */
# define DCM_EXT_SVC_86_STRT_STATE_IDLE                              ((Dcm_ExtSvc86STRTStateType)0x00u)
# define DCM_EXT_SVC_86_STRT_STATE_SENDING                           ((Dcm_ExtSvc86STRTStateType)0x01u)
# define DCM_EXT_SVC_86_STRT_STATE_WAIT_FOR_TIMEOUT                  ((Dcm_ExtSvc86STRTStateType)0x02u)

/* access to Roe context data */
# define Dcm_ExtSvc86HandlerState                                    (Dcm_ExtInstanceContext.Svc86.CurrentSession.HandlerState)
# define Dcm_ExtSvc86OldHandlerState                                 (Dcm_ExtInstanceContext.Svc86.CurrentSession.OldHandlerState)
# define Dcm_ExtSvc86RoEState                                        (Dcm_ExtInstanceContext.Svc86.CurrentSession.NvmData.RoEState)
# define Dcm_ExtSvc86ReadTimeout                                     (Dcm_ExtInstanceContext.Svc86.CurrentSession.NvmReadTimeout)
# define Dcm_ExtSvc86NvMData                                         (Dcm_ExtInstanceContext.Svc86.CurrentSession.NvmData)
# define Dcm_ExtSvc86NvMReadOpStatus                                 (Dcm_ExtInstanceContext.Svc86.CurrentSession.NvmReadOpStatus)
# define Dcm_ExtSvc86DTCStatusMask                                   (Dcm_ExtInstanceContext.Svc86.CurrentSession.NvmData.EventTypeRecord.DTCStatusMask)
# define Dcm_ExtSvc86RoEDid                                          (Dcm_ExtInstanceContext.Svc86.CurrentSession.NvmData.EventTypeRecord.Did)
# define Dcm_ExtSvc86ActiveEvent                                     (Dcm_ExtInstanceContext.Svc86.CurrentSession.NvmData.EventId)
# define Dcm_ExtSvc86EventType                                       (Dcm_ExtInstanceContext.Svc86.CurrentSession.NvmData.EventType)

# define Dcm_ExtSvc86CurrentSessionContext                           (Dcm_ExtInstanceContext.Svc86.CurrentSession)
# define Dcm_ExtSvc86DefaultSessionContext                           (Dcm_ExtInstanceContext.Svc86.DefaultSession)
# define Dcm_ExtSvc86STRTSendingState                                (Dcm_ExtInstanceContext.Svc86.STRTSendingState)

# define DCM_EXTSVC86_STOPROE_SID                                    0x00u
# define DCM_EXTSVC86_ONDTCSTATUSCHANGE_SID                          0x01u
# define DCM_EXTSVC86_ONCHANGEOFDATAIDENTIFIER_SID                   0x03u
# define DCM_EXTSVC86_STARTROE_SID                                   0x05u
# define DCM_EXTSVC86_CLEARROE_SID                                   0x06u

# define DCM_CFG_EWT_INFINITE_OCY                                    0x02u
# define DCM_CFG_EWT_CURRENT_OCY                                     0x03u
#endif /* (DCM_SVC_86_SUPPORT_ENABLED == STD_ON) */

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
#if (DCM_SVC_86_SUPPORT_ENABLED == STD_ON)
typedef uint8 Dcm_ExtSvc86RoeTimeoutType;

/*! Context for processing service 0x86 in a non-default session */
struct DCM_EXTSVC86SESSIONCONTEXTTYPE_TAG
{
  Dcm_ExtSvc86NvMDataType    NvmData;                  /*!< Data to be read from or written to NvM RoE storage */
  Dcm_ExtSvc86RoeStateType   HandlerState;             /*!< state of the internal RoE state machine */
  Dcm_ExtSvc86RoeStateType   OldHandlerState;          /*!< previous state of the internal RoE state machine */
  Dcm_ExtSvc86RoeTimeoutType NvmReadTimeout;           /*!< timeout counter to handle failed calls to NvM_ReadBlock block */
  Dcm_OpStatusType           NvmReadOpStatus;          /*!< current operation status during initialization for NvM reading */
};
typedef struct DCM_EXTSVC86SESSIONCONTEXTTYPE_TAG Dcm_ExtSvc86SessionContextType;

# if (DCM_SVC_86_RST_ON_DSC_ENABLED == STD_ON)
/*! Context for processing service 0x86 in the default session */
struct DCM_EXTSVC86DEFAULTSESSIONCONTEXTTYPE_TAG
{
  Dcm_ExtSvc86RoeStateType   RoEState;       /*!< RoE state */
  Dcm_ExtSvc86RoeStateType   HandlerState;   /*!< state of the internal RoE state machine */
  PduIdType                  RxPduId;        /*!< Id of connection requesting RoE */
  Dcm_ExtSvc86STRTType       EventType;      /*!< Type of event which is one of service 0x86 internally handled sub-functions */
  uint8                      EventId;        /*!< Id of an event to be processed */
};
typedef struct DCM_EXTSVC86DEFAULTSESSIONCONTEXTTYPE_TAG Dcm_ExtSvc86DefaultSessionContextType;
# endif

/*! Service 0x86 temporary processing context */
struct DCM_EXTSVC86CONTEXTTYPE_TAG
{
  Dcm_ExtSvc86SessionContextType CurrentSession;        /*!< RoE context in a non-default session */
# if (DCM_SVC_86_RST_ON_DSC_ENABLED == STD_ON)
  Dcm_ExtSvc86DefaultSessionContextType DefaultSession; /*!< RoE context in the default session */
# endif
  Dcm_ExtSvc86STRTStateType STRTSendingState;           /*!< Sending state of a response to STRT */
};
typedef struct DCM_EXTSVC86CONTEXTTYPE_TAG Dcm_ExtSvc86ContextType;

/*! Temporary processing context for OEM-specific services */
struct DCM_EXTINSTANCECONTEXTTYPE_TAG
{
# if (DCM_SVC_86_SUPPORT_ENABLED == STD_ON)                                                                                                          /* COV_DCM_SUPPORT_RESTRICTED TX */
  Dcm_ExtSvc86ContextType   Svc86;         /*!< state of the internal RoE state machine */
# endif
};
typedef struct DCM_EXTINSTANCECONTEXTTYPE_TAG Dcm_ExtInstanceContextType;
#endif /* (DCM_SVC_86_SUPPORT_ENABLED == STD_ON) */

/**********************************************************************************************************************
 *  LOCAL FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */
#if (DCM_SVC_86_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_ExtService86_CheckEWT_CtrlRequest_DefaultSession()
 *********************************************************************************************************************/
/*! \brief          Checks EventWindowTime and storeEvent combination for control request.
 *  \details        -
 *  \param[in]      eventWindowTime         EventWindowTime from request
 *  \param[in]      storeEvent              TRUE RoE state shall be stored.
 *                                          FALSE RoE state shall not be stored.
 *  \param[out]     errorCode               Negative response code in case return value is DCM_E_NOT_OK
 *  \return         DCM_E_OK                Combination is valid.
 *  \return         DCM_E_NOT_OK            Combination is not valid.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            ECU is in default session and storage Stage is supported for passed eventWindowTime
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_ExtService86_CheckEWT_CtrlRequest_DefaultSession(
  uint8 eventWindowTime,
  boolean storeEvent,
  Dcm_NegativeResponseCodePtrType errorCode
  );

/**********************************************************************************************************************
 *  Dcm_ExtService86_CheckEWT_SetupRequest_DefaultSession()
 *********************************************************************************************************************/
/*! \brief          Checks EventWindowTime and storeEvent combination for setup request.
 *  \details        -
 *  \param[in]      eventWindowTime         EventWindowTime from request
 *  \param[in]      storeEvent              TRUE RoE state shall be stored.
 *                                          FALSE RoE state shall not be stored.
 *  \param[out]     errorCode               Negative response code in case return value is DCM_E_NOT_OK
 *  \return         DCM_E_OK                Combination is valid.
 *  \return         DCM_E_NOT_OK            Combination is not valid.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            ECU is in default session and storage Stage is supported for passed eventWindowTime
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_ExtService86_CheckEWT_SetupRequest_DefaultSession(
  uint8 eventWindowTime,
  boolean storeEvent,
  Dcm_NegativeResponseCodePtrType errorCode
  );

/**********************************************************************************************************************
 *  Dcm_ExtService86_CheckEWT_NonDefaultSession()
 *********************************************************************************************************************/
/*! \brief          Checks EventWindowTime and storeEvent combination in non-default session.
 *  \details        -
 *  \param[in]      storeEvent              TRUE RoE state shall be stored.
 *                                          FALSE RoE state shall not be stored.
 *  \param[out]     errorCode               Negative response code in case return value is DCM_E_NOT_OK
 *  \return         DCM_E_OK                Combination is valid.
 *  \return         DCM_E_NOT_OK            Combination is not valid.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            Ecu is in non-default session
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_ExtService86_CheckEWT_NonDefaultSession(
  boolean storeEvent,
  Dcm_NegativeResponseCodePtrType errorCode
  );

# if (DCM_SVC_86_EVTYPE_ONCHGDTC_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_ExtService86_SendSTRT_OnDTCStatusChange()
 *********************************************************************************************************************/
/*! \brief          Tries to send ServiceToRespondTo for OnChangeDtc.
 *  \details        -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            ComM state shall still be in FullCommunicationMode.
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_ExtService86_SendSTRT_OnDTCStatusChange(
  void
  );
# endif

# if (DCM_SVC_86_EVTYPE_ONCHGDID_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_ExtService86_SendSTRT_OnChangeOfDid()
 *********************************************************************************************************************/
/*! \brief          Tries to send ServiceToRespondTo for OnChangeDid.
 *  \details        -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            ComM state shall still be in FullCommunicationMode.
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_ExtService86_SendSTRT_OnChangeOfDid(
  void
  );
# endif

/**********************************************************************************************************************
 *  Dcm_ExtService86_Send_STRT()
 *********************************************************************************************************************/
/*! \brief          Trying to send ServiceToRespondTo.
 *  \details        -
 *  \param[in,out]  pEventContext  Pointer to the event context
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            ComM state shall still be in FullCommunicationMode.
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_ExtService86_Send_STRT(
  Dcm_TskEventContextPtrType pEventContext
  );

/**********************************************************************************************************************
 *  Dcm_ExtService86_ClearTaskEvents()
 *********************************************************************************************************************/
/*! \brief          Clearing task events.
 *  \details        -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_ExtService86_ClearTaskEvents(
  void
  );

/**********************************************************************************************************************
 *  Dcm_ExtService86_CheckEWT_Internal()
 *********************************************************************************************************************/
/*! \brief          Checks EventWindowTime and storeEvent combination.
 *  \details        Checks combination for the sub-Functions stopResponseToEvent, startResponseToEvent and
 *                  onDtcStatusChange.
 *  \param[in]      session                 Current diagnostic session
 *  \param[in]      eventType               Type of RoE sub-function
 *  \param[in]      eventWindowTime         EventWindowTime from request
 *  \param[in]      storeEvent              If RoE information shall be stored.
 *  \param[out]     errorCode               Negative response code in case return value is DCM_E_NOT_OK
 *  \return         DCM_E_OK                Combination is valid.
 *  \return         DCM_E_NOT_OK            Combination is not valid.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            Ecu is in default session and storage Stage is supported for passed eventWindowTime
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_ExtService86_CheckEWT_Internal(
  Dcm_SesCtrlType session,
  uint8 eventType,
  uint8 eventWindowTime,
  boolean storeEvent,
  Dcm_NegativeResponseCodePtrType errorCode
  );

# if (DCM_SVC_86_NVM_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_ExtSvc86ReadNvM()
 *********************************************************************************************************************/
/*! \brief          Reads RoE information from NvM.
 *  \details        -
 *  \param[in,out]  pEventContext  Pointer to the event context
 *  \return         DCM_E_OK              Read operation finished successfully.
 *  \return         DCM_E_NOT_OK          Read operation finished with error or got canceled.
 *  \return         DCM_E_PENDING         Read operation needs more time to be accomplished.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    FALSE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_ExtSvc86ReadNvM(
  Dcm_TskEventContextPtrType pEventContext
  );
# endif

# if (DCM_SVC_86_EVTYPE_ONCHGDTC_ENABLED == STD_ON) && \
     (DCM_SVC_86_NVM_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_ExtService86_DTCStatusChange_StoreEvent()
 *********************************************************************************************************************/
/*! \brief          Initializes RoE setup.
 *  \details        -
 *  \param[in]      pContext                Pointer to the context
 *  \param[in]      pMsgContext             The current request context
 *  \param[in]      opStatus                The operation status
 *  \param[in]      dtcStatusMask           DTCStatusMask in request
 *  \param[out]     errorCode               Negative response code in case return value is DCM_E_NOT_OK
 *  \return         DCM_E_OK                Service processing done.
 *  \return         DCM_E_NOT_OK            Service processing failed.
 *  \return         DCM_E_PENDING           Service operation needs more time to be accomplished.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    FALSE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_ExtService86_DTCStatusChange_StoreEvent(
  Dcm_ContextPtrType pContext,
  Dcm_ReadOnlyMsgContextPtrType pMsgContext,
  Dcm_OpStatusType opStatus,
  uint8 dtcStatusMask,
  Dcm_NegativeResponseCodePtrType errorCode
  );
# endif
#endif /* (DCM_SVC_86_SUPPORT_ENABLED == STD_ON) */
#define DCM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define DCM_START_SEC_CODE
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */
#if (DCM_SVC_86_SUPPORT_ENABLED == STD_ON)
# if (DCM_SVC_86_EVTYPE_ONCHGDID_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_ExtService86_CheckDID()
 *********************************************************************************************************************/
/*! \brief          Check if the Did supports RoE.
 *  \details        -
 *  \param[in]      pContext                Pointer to the context
 *  \param[in]      opStatus                The operation status
 *  \param[in]      Did                     Requested Did
 *  \param[out]     errorCode               Negative response code in case return value is DCM_E_NOT_OK
 *  \return         DCM_E_OK                Service processing done.
 *  \return         DCM_E_NOT_OK            Service processing failed.
 *  \return         DCM_E_PENDING           Service operation needs more time to be accomplished.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    FALSE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL FUNC(Std_ReturnType, DCM_CODE) Dcm_ExtService86_CheckDID(
  Dcm_ContextPtrType pContext,
  Dcm_OpStatusType opStatus,
  uint16 Did,
  Dcm_NegativeResponseCodePtrType errorCode
  );
# endif

/**********************************************************************************************************************
 *  Dcm_ExtService86_StartRoE()
 *********************************************************************************************************************/
/*! \brief          Changes RoE state to active.
 *  \details        -
 *  \param[in]      pContext                Pointer to the context
 *  \param[in]      opStatus                The operation status
 *  \param[in,out]  pMsgContext             The current request context
 *  \param[in]      storeEvent              TRUE if RoE state shall be stored.
 *                                          FALSE if RoE state shall not be stored.
 *  \param[out]     errorCode               Negative response code in case return value is DCM_E_NOT_OK
 *  \return         DCM_E_OK                Service processing done.
 *  \return         DCM_E_NOT_OK            Service processing was not successful.
 *  \return         DCM_E_PENDING           Service operation needs more time to be accomplished.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    FALSE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL FUNC(Std_ReturnType, DCM_CODE) Dcm_ExtService86_StartRoE(
  Dcm_ContextPtrType pContext,
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,
  boolean storeEvent,
  Dcm_NegativeResponseCodePtrType errorCode
  );

# if (DCM_SVC_86_NVM_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_ExtService86_StartRoE_StoreEvent()
 *********************************************************************************************************************/
/*! \brief          Changes RoE state to inactive and stores event state.
 *  \details        -
 *  \param[in]      pContext                Pointer to the context
 *  \param[in]      opStatus                The operation status
 *  \param[in]      pMsgContext             The current request context
 *  \param[out]     errorCode               Negative response code in case return value is DCM_E_NOT_OK
 *  \return         DCM_E_OK                Service processing was successful.
 *  \return         DCM_E_PENDING           Service operation needs more time to be accomplished.
 *  \return         DCM_E_NOT_OK            Service processing was not successful.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    FALSE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL FUNC(Std_ReturnType, DCM_CODE) Dcm_ExtService86_StartRoE_StoreEvent(
  Dcm_ContextPtrType pContext,
  Dcm_OpStatusType opStatus,
  Dcm_ReadOnlyMsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodePtrType errorCode
  );
# endif
/**********************************************************************************************************************
 *  Dcm_ExtService86_StartRoE_Internal()
 *********************************************************************************************************************/
/*! \brief          Changes RoE state to inactive.
 *  \details        -
 *  \param[in]      pMsgContext             The current request context
 *  \param[out]     errorCode               Negative response code in case return value is DCM_E_NOT_OK
 *  \return         DCM_E_OK                Service processing was successful.
 *  \return         DCM_E_NOT_OK            Service processing was not successful.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL FUNC(Std_ReturnType, DCM_CODE) Dcm_ExtService86_StartRoE_Internal(
  Dcm_ContextPtrType pContext,                                                                                                                       /* PRQA S 3673 */ /* MD_Dcm_Design_3673 */
  Dcm_ReadOnlyMsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodePtrType errorCode
  );

/**********************************************************************************************************************
 *  Dcm_ExtService86_StopRoE()
 *********************************************************************************************************************/
/*! \brief          Changes RoE state to inactive.
 *  \details        -
 *  \param[in]      pContext                Pointer to the context
 *  \param[in]      opStatus                The operation status
 *  \param[in,out]  pMsgContext             The current request context
 *  \param[in]      storeEvent              TRUE if RoE state shall be stored.
 *                                          FALSE if RoE state shall not be stored.
 *  \param[out]     errorCode               Negative response code in case return value is DCM_E_NOT_OK
 *  \return         DCM_E_OK                Service processing done.
 *  \return         DCM_E_NOT_OK            Service processing was not successful.
 *  \return         DCM_E_PENDING           Service operation needs more time to be accomplished.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    FALSE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL FUNC(Std_ReturnType, DCM_CODE) Dcm_ExtService86_StopRoE(
  Dcm_ContextPtrType pContext,
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,
  boolean storeEvent,
  Dcm_NegativeResponseCodePtrType errorCode
  );

# if (DCM_SVC_86_NVM_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_ExtService86_StopRoE_StoreEvent()
 *********************************************************************************************************************/
/*! \brief          Changes RoE state to inactive and stores event.
 *  \details        -
 *  \param[in]      pContext                Pointer to the context
 *  \param[in]      pMsgContext             The current request context
 *  \param[in]      opStatus                The operation status
 *  \param[out]     errorCode               Negative response code in case return value is DCM_E_NOT_OK
 *  \return         DCM_E_OK                Service processing was successful.
 *  \return         DCM_E_PENDING           Service operation needs more time to be accomplished.
 *  \return         DCM_E_NOT_OK            Service processing was not successful.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    FALSE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL FUNC(Std_ReturnType, DCM_CODE) Dcm_ExtService86_StopRoE_StoreEvent(
  Dcm_ContextPtrType pContext,
  Dcm_ReadOnlyMsgContextPtrType pMsgContext,
  Dcm_OpStatusType opStatus,
  Dcm_NegativeResponseCodePtrType errorCode
  );
# endif

/**********************************************************************************************************************
 *  Dcm_ExtService86_StopRoE_Internal()
 *********************************************************************************************************************/
/*! \brief          Changes RoE state to inactive.
 *  \details        -
 *  \param[in,out]  errorCode               Negative response code in case return value is DCM_E_NOT_OK
 *  \return         DCM_E_OK                Service processing was successful.
 *  \return         DCM_E_NOT_OK            Service processing was not successful.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL FUNC(Std_ReturnType, DCM_CODE) Dcm_ExtService86_StopRoE_Internal(
  Dcm_NegativeResponseCodePtrType errorCode
  );

# if (DCM_SVC_86_EVTYPE_ONCHGDTC_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_ExtService86_OnDTCStatusChange()
 *********************************************************************************************************************/
/*! \brief          Initializes RoE sub function 0x01 setup.
 *  \details        -
 *  \param[in]      pContext                Pointer to the context
 *  \param[in]      opStatus                The operation status
 *  \param[in,out]  pMsgContext             The current request context
 *  \param[in]      storeEvent              TRUE if setup shall be stored.
 *                                          FALSE if setup shall not be stored.
 *  \param[out]     errorCode               Negative response code in case return value is DCM_E_NOT_OK
 *  \return         DCM_E_OK                Service processing done.
 *  \return         DCM_E_NOT_OK            Service processing was not successful.
 *  \return         DCM_E_PENDING           Service operation needs more time to be accomplished.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    FALSE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL FUNC(Std_ReturnType, DCM_CODE) Dcm_ExtService86_OnDTCStatusChange(
  Dcm_ContextPtrType pContext,
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,
  boolean storeEvent,
  Dcm_NegativeResponseCodePtrType errorCode
  );
# endif

# if (DCM_SVC_86_EVTYPE_ONCHGDID_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_ExtService86_OnChangeOfDataIdentifier()
 *********************************************************************************************************************/
/*! \brief          Initializes RoE sub function 0x03 setup.
 *  \details        -
 *  \param[in]      pContext                Pointer to the context
 *  \param[in]      opStatus                The operation status
 *  \param[in,out]  pMsgContext             The current request context
 *  \param[in]      storeEvent              TRUE if setup shall be stored.
 *                                          FALSE if setup shall not be stored.
 *  \param[out]     errorCode               Negative response code in case return value is DCM_E_NOT_OK
 *  \return         DCM_E_OK                Service processing done.
 *  \return         DCM_E_NOT_OK            Service processing was not successful.
 *  \return         DCM_E_PENDING           Service operation needs more time to be accomplished.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    FALSE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL FUNC(Std_ReturnType, DCM_CODE) Dcm_ExtService86_OnChangeOfDataIdentifier(
  Dcm_ContextPtrType pContext,
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,
  boolean storeEvent,
  Dcm_NegativeResponseCodePtrType errorCode
  );
# endif

/**********************************************************************************************************************
 *  Dcm_ExtService86_CheckEWT()
 *********************************************************************************************************************/
/*! \brief          Checks EventWindowTime and storeEvent combination.
 *  \details        -
 *  \param[in]      eventType               Type of RoE sub-function
 *  \param[in]      eventWindowTime         EventWindowTime from request
 *  \param[in]      storeEvent              If RoE information shall be stored.
 *  \param[out]     errorCode               Negative response code in case return value is DCM_E_NOT_OK
 *  \return         DCM_E_OK                Combination is valid.
 *  \return         DCM_E_NOT_OK            Combination is not valid.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            Ecu is in default session and storage Stage is supported for passed eventWindowTime
 *********************************************************************************************************************/
DCM_LOCAL FUNC(Std_ReturnType, DCM_CODE) Dcm_ExtService86_CheckEWT(
  uint8 eventType,
  uint8 eventWindowTime,
  boolean storeEvent,
  Dcm_NegativeResponseCodePtrType errorCode
  );

# if (DCM_SVC_86_NVM_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_ExtSvc86UpdateNvM()
 *********************************************************************************************************************/
/*! \brief          Updates the NvM with the RoE information.
 *  \details        -
 *  \param[in]      opStatus       Operation status
 *  \param[in]      pRepContext    The RoE context
 *  \param[out]     errorCode      Negative response code in case return value is DCM_E_NOT_OK
 *  \return         DCM_E_OK       Update operation finished successfully.
 *  \return         DCM_E_NOT_OK   Update operation finished with error or got canceled.
 *  \return         DCM_E_PENDING  Update operation needs more time to be accomplished.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    FALSE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL FUNC(Std_ReturnType, DCM_CODE) Dcm_ExtSvc86UpdateNvM(
  Dcm_OpStatusType opStatus,
  Dcm_Svc86RepeaterProxyContextConstPtrType pRepContext,
  Dcm_NegativeResponseCodePtrType errorCode
  );
# endif

/**********************************************************************************************************************
 *  Dcm_ExtSvc86_ClearRoE()
 *********************************************************************************************************************/
/*! \brief          Clear RoE logic.
 *  \details        RoE state is set to cleared and new state is stored.
 *  \param[in]      pContext                Pointer to the context
 *  \param[in]      opStatus                Operation status
 *  \param[in,out]  pMsgContext             The current request context
 *  \return         DCM_E_OK                Clear processing done.
 *  \return         DCM_E_NOT_OK            Clearing was not successful.
 *  \return         DCM_E_PENDING           Clear operation needs more time to be accomplished.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    FALSE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL FUNC(Std_ReturnType, DCM_CODE) Dcm_ExtSvc86_ClearRoE(
  Dcm_ContextPtrType pContext,
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodePtrType errorCode
  );

/**********************************************************************************************************************
 *  Dcm_ExtService86_CheckRoEClient()
 *********************************************************************************************************************/
/*! \brief          Checks if client is the same client that that started RoE.
 *  \details        -
 *  \param[in]      pContext                Pointer to the context
 *  \param[in]      pMsgContext             The current request context
 *  \param[out]     errorCode               Negative response code in case return value is DCM_E_NOT_OK
 *  \return         DCM_E_OK                Client is same.
 *  \return         DCM_E_NOT_OK            Client is not same.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL FUNC(Std_ReturnType, DCM_CODE) Dcm_ExtService86_CheckRoEClient(
  Dcm_ContextPtrType pContext,
  Dcm_ReadOnlyMsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodePtrType errorCode
  );
#endif /* (DCM_SVC_86_SUPPORT_ENABLED == STD_ON) */
#define DCM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL DATA DECLARATIONS
 *********************************************************************************************************************/
#define DCM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */
#if (DCM_SVC_86_SUPPORT_ENABLED == STD_ON)
DCM_LOCAL VAR(Dcm_ExtInstanceContextType, DCM_VAR_NOINIT)  Dcm_ExtInstanceContext;
#endif /* (DCM_SVC_86_SUPPORT_ENABLED == STD_ON) */
#define DCM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */
#if (DCM_SVC_86_SUPPORT_ENABLED == STD_ON)
CONST(Dcm_ExtSvc86NvMDataType, DCM_CONST) DcmExtSvc86DefaultNvMData =                                                                                /* PRQA S 1514 */ /* MD_Dcm_ObjectOnlyAccessedOnce */
{
  0
 ,0
 ,{ 0 }
 ,DCM_EXT_SVC_86_STATE_CLEARED /* per default - clear RoE */
 ,0
 ,0
};
#endif /* (DCM_SVC_86_SUPPORT_ENABLED == STD_ON) */
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */
#if (DCM_SVC_86_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_ExtService86_CheckEWT_NonDefaultSession()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DCM_LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_ExtService86_CheckEWT_NonDefaultSession(
  boolean storeEvent,
  Dcm_NegativeResponseCodePtrType errorCode
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType lStdResult = DCM_E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* storeEvent is considered */
  if(storeEvent == TRUE)
  {
    /* Storing in Non-Default Session is not allowed */
    *errorCode = DCM_E_REQUESTOUTOFRANGE;                                                                                                            /* SBSW_DCM_PARAM_PTR_WRITE */
    lStdResult = DCM_E_NOT_OK;
  }

  return lStdResult;
}

/**********************************************************************************************************************
 *  Dcm_ExtService86_CheckEWT_CtrlRequest_DefaultSession()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DCM_LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_ExtService86_CheckEWT_CtrlRequest_DefaultSession(
  uint8 eventWindowTime,
  boolean storeEvent,
  Dcm_NegativeResponseCodePtrType errorCode
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType lStdResult = DCM_E_OK;

  /* ----- Implementation ----------------------------------------------- */
  if((storeEvent == TRUE) && (eventWindowTime == DCM_CFG_EWT_CURRENT_OCY))
  {
    /* storeEvent not allowed with DCM_CFG_EWT_CURRENT_OCY */
    *errorCode = DCM_E_REQUESTOUTOFRANGE;                                                                                                            /* SBSW_DCM_PARAM_PTR_WRITE */
    lStdResult = DCM_E_NOT_OK;
  }

  return lStdResult;
}

/**********************************************************************************************************************
 *  Dcm_ExtService86_CheckEWT_SetupRequest_DefaultSession()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DCM_LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_ExtService86_CheckEWT_SetupRequest_DefaultSession(
  uint8 eventWindowTime,
  boolean storeEvent,
  Dcm_NegativeResponseCodePtrType errorCode
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType lStdResult = DCM_E_OK;

  /* ----- Implementation ----------------------------------------------- */
  if( ((storeEvent == TRUE)  && (eventWindowTime == DCM_CFG_EWT_CURRENT_OCY))
    ||((storeEvent == FALSE) && (eventWindowTime == DCM_CFG_EWT_INFINITE_OCY))
    )
  {
    /* storeEvent and eventWindowTime combination not allowed */
    *errorCode = DCM_E_REQUESTOUTOFRANGE;                                                                                                            /* SBSW_DCM_PARAM_PTR_WRITE */
    lStdResult = DCM_E_NOT_OK;
  }

  return lStdResult;
}

# if (DCM_SVC_86_EVTYPE_ONCHGDTC_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_ExtService86_SendSTRT_OnDTCStatusChange()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DCM_LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_ExtService86_SendSTRT_OnDTCStatusChange(
  void
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  Dcm_MsgItemType lReqDtc[2] = { 0x19, 0x0E };
  uint8 numOfBytes = Dcm_UtiGetNumElementsOfTable(lReqDtc, Dcm_MsgItemType);

  /* ----- Implementation ----------------------------------------------- */
  return Dcm_NetRxIndInternal(Dcm_ExtSvc86NvMData.RxPduId, Dcm_ExtSvc86NvMData.ClientSrcAddr, lReqDtc, numOfBytes);                                  /* SBSW_DCM_LOCAL_ARRAY_WRITE */
}
# endif

# if (DCM_SVC_86_EVTYPE_ONCHGDID_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_ExtService86_SendSTRT_OnChangeOfDid()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DCM_LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_ExtService86_SendSTRT_OnChangeOfDid(
  void
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  Dcm_MsgItemType lReqDid[3];
  uint8 numOfBytes = Dcm_UtiGetNumElementsOfTable(lReqDid, Dcm_MsgItemType);

  lReqDid[0] = 0x22;                                                                                                                                 /* SBSW_DCM_LOCAL_ARRAY_WRITE */
  lReqDid[1] = Dcm_UtiGetHiByte(Dcm_ExtSvc86RoEDid);                                                                                                 /* SBSW_DCM_LOCAL_ARRAY_WRITE */
  lReqDid[2] = Dcm_UtiGetLoByte(Dcm_ExtSvc86RoEDid);                                                                                                 /* SBSW_DCM_LOCAL_ARRAY_WRITE */

  /* ----- Implementation ----------------------------------------------- */
  return Dcm_NetRxIndInternal(Dcm_ExtSvc86NvMData.RxPduId, Dcm_ExtSvc86NvMData.ClientSrcAddr, lReqDid, numOfBytes);                                  /* SBSW_DCM_LOCAL_ARRAY_WRITE */
}
# endif

/**********************************************************************************************************************
 *  Dcm_ExtService86_Send_STRT()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_ExtService86_Send_STRT(
  Dcm_TskEventContextPtrType pEventContext
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType  rxIndicationResult;

  /* ----- Implementation ----------------------------------------------- */
  switch (Dcm_ExtSvc86EventType)
  {
# if (DCM_SVC_86_EVTYPE_ONCHGDTC_ENABLED == STD_ON)
    case DCM_EXTSVC86_ONDTCSTATUSCHANGE_SID:
      rxIndicationResult = Dcm_ExtService86_SendSTRT_OnDTCStatusChange();
    break;
# endif
# if (DCM_SVC_86_EVTYPE_ONCHGDID_ENABLED == STD_ON)
    case DCM_EXTSVC86_ONCHANGEOFDATAIDENTIFIER_SID:
      rxIndicationResult = Dcm_ExtService86_SendSTRT_OnChangeOfDid();
    break;
# endif
    default:
      /* Nothing to trigger */
      rxIndicationResult = DCM_E_NOT_OK;
      Dcm_DebugReportError(DCM_SID_INTERNAL, DCM_E_INVALID_CONFIG);
    break;
  }

  if (rxIndicationResult != DCM_E_OK)
  {
    /* Set STRT state to IDLE and retry sending next task cycle */
    Dcm_TskSetLocalEvent(pEventContext->PostEv, DCM_EXT_TSK_EV_ROE_SEND);                                                                            /* SBSW_DCM_PARAM_PTR_WRITE */
    Dcm_ExtSvc86STRTSendingState = DCM_EXT_SVC_86_STRT_STATE_IDLE;
  }
}

/**********************************************************************************************************************
 *  Dcm_ExtService86_ClearTaskEvents()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_ExtService86_ClearTaskEvents(
  void
  )
{
  Dcm_TskClrEvent(DCM_TSK_ID_ROE, (DCM_EXT_TSK_EV_ROE_SEND | DCM_EXT_TSK_EV_ROE_TX_END));

# if (DCM_SVC_86_TIMER_ENABLED != STD_ON)
  /* intermessage time is 0; next STRT can be sent with next task event */
  Dcm_ExtSvc86STRTSendingState = DCM_EXT_SVC_86_STRT_STATE_IDLE;
# endif
}

/**********************************************************************************************************************
 *  Dcm_ExtService86_CheckEWT_Internal()
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
 */
DCM_LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_ExtService86_CheckEWT_Internal(
  Dcm_SesCtrlType session,
  uint8 eventType,
  uint8 eventWindowTime,
  boolean storeEvent,
  Dcm_NegativeResponseCodePtrType errorCode
  )
{
  Std_ReturnType lStdResult;

  if(session == DCM_DEFAULT_SESSION)
  {
    /* default session */
    if((eventType == DCM_EXTSVC86_STOPROE_SID) || (eventType == DCM_EXTSVC86_STARTROE_SID) )
    {
      /* conditions for startResponseOnEvent and stopResponseOnEvent are equal in default session */
      lStdResult = Dcm_ExtService86_CheckEWT_CtrlRequest_DefaultSession(eventWindowTime, storeEvent, errorCode);                                     /* SBSW_DCM_COMB_PTR_FORWARD */
    }
    else
    {
      /* Setup RoE */
      lStdResult = Dcm_ExtService86_CheckEWT_SetupRequest_DefaultSession(eventWindowTime, storeEvent, errorCode);                                    /* SBSW_DCM_COMB_PTR_FORWARD */
    }
  }
  else
  {
    /* non-default session */
    if(eventType == DCM_EXTSVC86_STOPROE_SID)
    {
      /* conditions for stopResponseOnEvent is in non-default session same as in default session */
      lStdResult = Dcm_ExtService86_CheckEWT_CtrlRequest_DefaultSession(eventWindowTime, storeEvent, errorCode);                                     /* SBSW_DCM_COMB_PTR_FORWARD */
    }
    else
    {
      if((eventType == DCM_EXTSVC86_ONDTCSTATUSCHANGE_SID) && (eventWindowTime == DCM_CFG_EWT_INFINITE_OCY))
      {
        /* EventWindowTime Infinite not allowed for onDTCDtatusChange */
        *errorCode = DCM_E_REQUESTOUTOFRANGE;                                                                                                        /* SBSW_DCM_PARAM_PTR_WRITE */
        lStdResult = DCM_E_NOT_OK;
      }
      else
      {
        /* conditions for startResponseOnEvent and onDTCDtatusChange are mostly equal in non-default session */
        lStdResult = Dcm_ExtService86_CheckEWT_NonDefaultSession(storeEvent, errorCode);                                                             /* SBSW_DCM_COMB_PTR_FORWARD */
      }
    }
  }

  return lStdResult;
}                                                                                                                                                    /* PRQA S 6060 */ /* MD_MSR_STPAR */

# if (DCM_SVC_86_NVM_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_ExtSvc86ReadNvM()
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
 *
 *
 *
 *
 *
 *
 */
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_ExtSvc86ReadNvM(
  Dcm_TskEventContextPtrType pEventContext
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType lStdResult;

  /* ----- Implementation ----------------------------------------------- */
  /* get persistent data from NvM */
  lStdResult = Dcm_UtiNvMRead(Dcm_ExtSvc86NvMReadOpStatus, &Dcm_ExtSvc86NvMData, DCM_EXT_SVC_86_NVRAM_BLOCKID);                                      /* SBSW_DCM_ROE_NV_ACCESS */ /* PRQA S 0315 */ /* MD_MSR_Dir1.1 */

  if(lStdResult == DCM_E_OK)
  {
#  if (DCM_VARMGR_MULTI_COM_ENABLED == STD_ON)
    if(Dcm_ExtSvc86NvMData.RoEState == DCM_EXT_SVC_86_STATE_ACTIVE)
    {
      Dcm_CfgVarMgrComVariantType pComVariant = Dcm_VarMgrGetActiveComVariant();

      if( (Dcm_ExtSvc86NvMData.RxPduId >= Dcm_NetCfgGetNumRxPduIds(pComVariant))
        ||(Dcm_NetCfgGetRxPduInfo(pComVariant)[Dcm_ExtSvc86NvMData.RxPduId].ConnRef >= Dcm_NetCfgGetNumConnections(pComVariant)) /* keep evaluation order to guard the connRef indirection */
        ||(
#   if (DCM_NET_GENERIC_CONNECTION_ENABLED == STD_ON)
            (!Dcm_NetCfgIsGenericConnection(pComVariant, Dcm_NetCfgGetConnHdlOfRxPduId(pComVariant, Dcm_ExtSvc86NvMData.RxPduId))) &&
#   endif
            (Dcm_ExtSvc86NvMData.ClientSrcAddr != Dcm_NetCfgGetTesterAddressOfRxPduId(pComVariant, Dcm_ExtSvc86NvMData.RxPduId)) ) )
      {
        /* Restore default values */
        Dcm_ExtSvc86NvMData = DcmExtSvc86DefaultNvMData;
      }
    }
#  endif
    /* reading data from NvM finished; change state according to stored RoE state */
    Dcm_ExtSvc86HandlerState = Dcm_ExtSvc86NvMData.RoEState;
    Dcm_RoEOnEventStateChange(Dcm_ExtSvc86ActiveEvent, Dcm_ExtSvc86NvMData.RoEState);

    /* If RoE state is active */
    if (Dcm_ExtSvc86NvMData.RoEState == DCM_EXT_SVC_86_STATE_ACTIVE)
    {
      /* notify Dem to start triggering DTC status changes */
      Dcm_DemAPI_ControlDTCStatusChangedNotification(TRUE);
    }
  }
  else if(lStdResult == DCM_E_PENDING)
  {
    /* retry later */
    Dcm_TskSetLocalEvent(pEventContext->PostEv, DCM_EXT_TSK_EV_ROE_ACTIVATE);                                                                        /* SBSW_DCM_PARAM_PTR_WRITE */
    Dcm_ExtSvc86NvMReadOpStatus = DCM_PENDING;
  }
  else  /* DCM_E_NOT_OK */
  {
    /* If NvM request was not accepted -> retry later until timeout. Once accepted (OpStatus == DCM_PENDING) would mean that the read access has failed -> close the job */
    if( (Dcm_ExtSvc86NvMReadOpStatus == DCM_INITIAL)
      &&(Dcm_ExtSvc86ReadTimeout > 0u) )
    {
      /* timeout not yet reached; try again in next cycle */
      Dcm_ExtSvc86ReadTimeout--;
      Dcm_TskSetLocalEvent(pEventContext->PostEv, DCM_EXT_TSK_EV_ROE_ACTIVATE);                                                                      /* SBSW_DCM_PARAM_PTR_WRITE */
     /* Start new cycle - leave opStatus = DCM_INITIAL
      * Dcm_ExtSvc86NvMReadOpStatus = DCM_INITIAL;
      */
    }
    else
    {
      /* read data from NvM failed; set to default */
      Dcm_ExtSvc86NvMData = DcmExtSvc86DefaultNvMData;

      Dcm_ExtSvc86HandlerState = Dcm_ExtSvc86NvMData.RoEState;
      Dcm_RoEOnEventStateChange(Dcm_ExtSvc86ActiveEvent, Dcm_ExtSvc86NvMData.RoEState);
    }
  }
}
# endif

# if (DCM_SVC_86_EVTYPE_ONCHGDTC_ENABLED == STD_ON) && \
     (DCM_SVC_86_NVM_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_ExtService86_DTCStatusChange_StoreEvent()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DCM_LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_ExtService86_DTCStatusChange_StoreEvent(
  Dcm_ContextPtrType pContext,                                                                                                                       /* PRQA S 3673 */ /* MD_Dcm_Design_3673 */
  Dcm_ReadOnlyMsgContextPtrType pMsgContext,
  Dcm_OpStatusType opStatus,
  uint8 dtcStatusMask,
  Dcm_NegativeResponseCodePtrType errorCode
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType lStdResult;

  /* ----- Implementation ----------------------------------------------- */
  Dcm_Svc86RepeaterProxyContextPtrType pRepContext;
  pRepContext = &pContext->Thread->Repeater.Contexts.Context.Svc86;

  if (Dcm_ExtSvc86HandlerState == DCM_EXT_SVC_86_STATE_WRITE_NVM_DATA)
  {
    /* updating NvM is pending */
    lStdResult = Dcm_ExtSvc86UpdateNvM(opStatus, pRepContext, errorCode);                                                                            /* SBSW_DCM_COMB_PTR_FORWARD */
  }
  else
  {
    /* update NvM */
    Dcm_NetTransportObjectConstPtrType pTranspObj = Dcm_NetGetTransportObject(pContext->Thread->Diag.TObjHdl);
    Dcm_ExtSvc86OldHandlerState = Dcm_ExtSvc86HandlerState;
    Dcm_ExtSvc86HandlerState = DCM_EXT_SVC_86_STATE_WRITE_NVM_DATA;
    pRepContext->NewNvmData.RoEState = DCM_EXT_SVC_86_STATE_INACTIVE;                                                                                /* SBSW_DCM_GLOBAL_PTR_WRITE */
    pRepContext->NewNvmData.EventTypeRecord.DTCStatusMask = dtcStatusMask;                                                                           /* SBSW_DCM_GLOBAL_PTR_WRITE */
    pRepContext->NewNvmData.EventType = DCM_EXTSVC86_ONDTCSTATUSCHANGE_SID;                                                                          /* SBSW_DCM_GLOBAL_PTR_WRITE */
    pRepContext->NewNvmData.EventId = DCM_EXT_SVC_86_ROE_DTC_EVENTID;                                                                                /* SBSW_DCM_GLOBAL_PTR_WRITE */
    pRepContext->NewNvmData.RxPduId = pMsgContext->rxPduId;                                                                                          /* SBSW_DCM_GLOBAL_PTR_WRITE */
    pRepContext->NewNvmData.ClientSrcAddr = pTranspObj->ClientSrcAddr;                                                                               /* SBSW_DCM_GLOBAL_PTR_WRITE */
    lStdResult = Dcm_ExtSvc86UpdateNvM(opStatus, pRepContext, errorCode);                                                                            /* SBSW_DCM_COMB_PTR_FORWARD */
  }

  return lStdResult;
}
# endif
#endif /* (DCM_SVC_86_SUPPORT_ENABLED == STD_ON) */
#define DCM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define DCM_START_SEC_CODE
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */
#if (DCM_SVC_86_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_ExtService86_CheckRoEClient()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DCM_LOCAL FUNC(Std_ReturnType, DCM_CODE) Dcm_ExtService86_CheckRoEClient(
  Dcm_ContextPtrType pContext,                                                                                                                       /* PRQA S 3673 */ /* MD_Dcm_Design_3673 */
  Dcm_ReadOnlyMsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodePtrType errorCode
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType lStdResult = DCM_E_OK;

  /* ----- Implementation ----------------------------------------------- */
# if (DCM_VARMGR_MULTI_COM_ENABLED == STD_ON)
  Dcm_CfgVarMgrComVariantType pComVariant = Dcm_VarMgrGetActiveComVariant();
# endif
  if( (Dcm_NetCfgGetRxPduInfo(pComVariant)[Dcm_ExtSvc86NvMData.RxPduId].ConnRef != Dcm_NetCfgGetRxPduInfo(pComVariant)[pMsgContext->rxPduId].ConnRef)
    ||(Dcm_ExtSvc86NvMData.ClientSrcAddr != Dcm_NetGetTransportObject(pContext->Thread->Diag.TObjHdl)->ClientSrcAddr) )                              /* PRQA S 3415 */ /* MD_Dcm_Rule13.5 */
  {
    /* Request comes from a different tester */
    *errorCode = DCM_E_CONDITIONSNOTCORRECT;                                                                                                         /* SBSW_DCM_PARAM_PTR_WRITE */
    lStdResult = DCM_E_NOT_OK;
  }

  return lStdResult;
}

/**********************************************************************************************************************
 *  Dcm_ExtService86_StartRoE()
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
 *
 *
 *
 *
 *
 *
 *
 */
DCM_LOCAL FUNC(Std_ReturnType, DCM_CODE) Dcm_ExtService86_StartRoE(
  Dcm_ContextPtrType pContext,                                                                                                                       /* PRQA S 3673 */ /* MD_Dcm_Design_3673 */
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,
  boolean storeEvent,
  Dcm_NegativeResponseCodePtrType errorCode
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType lStdResult = DCM_E_OK;
  uint8          lEventWindowTime;
  *errorCode = DCM_E_POSITIVERESPONSE;                                                                                                               /* SBSW_DCM_PARAM_PTR_WRITE */

  DCM_IGNORE_UNREF_PARAM(pContext);                                                                                                                  /* PRQA S 3112 */ /* MD_MSR_DummyStmt */

  /* ----- Implementation ----------------------------------------------- */
  lEventWindowTime = Dcm_UtiGetReqDataAsU8(pMsgContext);                                                                                             /* PRQA S 2985 */ /* MD_Dcm_Redundant_2985 */
  if(opStatus == DCM_INITIAL)
  {
    lStdResult = Dcm_ExtService86_CheckEWT(DCM_EXTSVC86_STARTROE_SID, lEventWindowTime, storeEvent, errorCode);                                      /* SBSW_DCM_COMB_PTR_FORWARD */

    /* check if request comes from tester that started RoE */
    if((lStdResult == DCM_E_OK) && (Dcm_ExtSvc86RoEState == DCM_EXT_SVC_86_STATE_ACTIVE))
    {
      lStdResult = Dcm_ExtService86_CheckRoEClient(pContext, pMsgContext, errorCode);                                                                /* SBSW_DCM_COMB_PTR_FORWARD */
    }
  }

  if(lStdResult == DCM_E_OK)
  {
# if (DCM_SVC_86_NVM_SUPPORT_ENABLED == STD_ON)
    if(storeEvent == TRUE)
    {
      lStdResult = Dcm_ExtService86_StartRoE_StoreEvent(pContext, opStatus, pMsgContext, errorCode);                                                 /* SBSW_DCM_COMB_PTR_FORWARD */
    }
    else
# endif
    {
      lStdResult = Dcm_ExtService86_StartRoE_Internal(pContext, pMsgContext, errorCode);                                                             /* SBSW_DCM_COMB_PTR_FORWARD */
    }

    if (lStdResult == DCM_E_OK)
    {
# if (DCM_SVC_86_EVTYPE_ONCHGDTC_ENABLED == STD_ON)
      if(Dcm_ExtSvc86EventType == DCM_EXTSVC86_ONDTCSTATUSCHANGE_SID)
      {
        /* notify Dem to start triggering DTC status changes */
        Dcm_DemAPI_ControlDTCStatusChangedNotification(TRUE);
      }
# endif
      /* report response data */
      Dcm_UtiProvideResDataAsU8(pMsgContext, 0x00u);                                                                                                 /* SBSW_DCM_PARAM_PTR_FORWARD */
      Dcm_UtiProvideResDataAsU8(pMsgContext, lEventWindowTime);                                                                                      /* SBSW_DCM_PARAM_PTR_FORWARD */
    } /* else storing RoE state is pending or DCM_E_NOT_OK (errorCode already set) */
  } /* else DCM_E_NOT_OK (errrorCode already set) */

  return lStdResult;
}

/**********************************************************************************************************************
 *  Dcm_ExtService86_StopRoE()
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
 *
 *
 *
 *
 *
 *
 */
DCM_LOCAL FUNC(Std_ReturnType, DCM_CODE) Dcm_ExtService86_StopRoE(
  Dcm_ContextPtrType pContext,                                                                                                                       /* PRQA S 3673 */ /* MD_Dcm_Design_3673 */
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,
  boolean storeEvent,
  Dcm_NegativeResponseCodePtrType errorCode
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType        lStdResult = DCM_E_OK;
  uint8 lEventWindowTime;
  *errorCode = DCM_E_POSITIVERESPONSE;                                                                                                               /* SBSW_DCM_PARAM_PTR_WRITE */

  DCM_IGNORE_UNREF_PARAM(pContext);                                                                                                                  /* PRQA S 3112 */ /* MD_MSR_DummyStmt */

  /* ----- Implementation ----------------------------------------------- */
  lEventWindowTime = Dcm_UtiGetReqDataAsU8(pMsgContext);                                                                                             /* PRQA S 2985 */ /* MD_Dcm_Redundant_2985 */
  if(opStatus == DCM_INITIAL)
  {
    lStdResult = Dcm_ExtService86_CheckEWT(DCM_EXTSVC86_STOPROE_SID, lEventWindowTime, storeEvent, errorCode);                                       /* SBSW_DCM_COMB_PTR_FORWARD */
  }

  if(lStdResult == DCM_E_OK)
  {
# if (DCM_SVC_86_EVTYPE_ONCHGDTC_ENABLED == STD_ON)
    Dcm_ExtSvc86RoeStateType lOldRoEState = Dcm_ExtSvc86RoEState;
# endif

# if (DCM_SVC_86_NVM_SUPPORT_ENABLED == STD_ON)
    if(storeEvent == TRUE)
    {
      lStdResult = Dcm_ExtService86_StopRoE_StoreEvent(pContext, pMsgContext, opStatus, errorCode);                                                  /* SBSW_DCM_PARAM_PTR_FORWARD */
    }
    else
# endif
    {
      lStdResult = Dcm_ExtService86_StopRoE_Internal(errorCode);                                                                                     /* SBSW_DCM_PARAM_PTR_FORWARD */
    }

    if (lStdResult == DCM_E_OK)
    {
# if (DCM_SVC_86_EVTYPE_ONCHGDTC_ENABLED == STD_ON)
      if((lOldRoEState == DCM_EXT_SVC_86_STATE_ACTIVE) && (Dcm_ExtSvc86EventType == DCM_EXTSVC86_ONDTCSTATUSCHANGE_SID))
      {
        /* notify Dem to stop triggering DTC status change */
        Dcm_DemAPI_ControlDTCStatusChangedNotification(FALSE);
      }
# endif
      /* report response data */
      Dcm_UtiProvideResDataAsU8(pMsgContext, 0x00u);                                                                                                 /* SBSW_DCM_PARAM_PTR_FORWARD */
      Dcm_UtiProvideResDataAsU8(pMsgContext, lEventWindowTime);                                                                                      /* SBSW_DCM_PARAM_PTR_FORWARD */

      /* clear task event */
      Dcm_ExtService86_ClearTaskEvents();
    } /* else storing RoE state is pending or DCM_E_NOT_OK (errorCode already set) */
  } /* else DCM_E_NOT_OK (errorCode already set) */

  return lStdResult;
}

/**********************************************************************************************************************
 *  Dcm_ExtService86_StopRoE_Internal()
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
 */
DCM_LOCAL FUNC(Std_ReturnType, DCM_CODE) Dcm_ExtService86_StopRoE_Internal(
  Dcm_NegativeResponseCodePtrType errorCode
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType lStdResult = DCM_E_OK;

  /* ----- Implementation ----------------------------------------------- */
  switch (Dcm_ExtSvc86HandlerState)
  {
    case DCM_EXT_SVC_86_STATE_ACTIVE:
      /* RoE state is active and stored */
      Dcm_ExtSvc86HandlerState = DCM_EXT_SVC_86_STATE_INACTIVE_STOP_NOT_STORED;
      Dcm_ExtSvc86RoEState = DCM_EXT_SVC_86_STATE_INACTIVE;
      Dcm_RoEOnEventStateChange(Dcm_ExtSvc86ActiveEvent, Dcm_ExtSvc86RoEState);
      break;
    case DCM_EXT_SVC_86_STATE_ACTIVE_SETUP_NOT_STORED:
      /* RoE state is active and setup not stored */
      Dcm_ExtSvc86HandlerState = DCM_EXT_SVC_86_STATE_INACTIVE_SETUP_NOT_STORED;
      Dcm_ExtSvc86RoEState = DCM_EXT_SVC_86_STATE_INACTIVE;
      Dcm_RoEOnEventStateChange(Dcm_ExtSvc86ActiveEvent, Dcm_ExtSvc86RoEState);
      break;
    case DCM_EXT_SVC_86_STATE_ACTIVE_SETUP_STORED:
      /* RoE state is active and setup stored */
      Dcm_ExtSvc86HandlerState = DCM_EXT_SVC_86_STATE_INACTIVE;
      Dcm_ExtSvc86RoEState = DCM_EXT_SVC_86_STATE_INACTIVE;
      Dcm_RoEOnEventStateChange(Dcm_ExtSvc86ActiveEvent, Dcm_ExtSvc86RoEState);
      break;
    case DCM_EXT_SVC_86_STATE_INACTIVE_SETUP_NOT_STORED:
    case DCM_EXT_SVC_86_STATE_INACTIVE_STOP_NOT_STORED:
      /* RoE state is already stopped and not stored */
      break;
    case DCM_EXT_SVC_86_STATE_CLEARED:
      /* Roe is cleared and can not processed in this state */
      lStdResult = DCM_E_NOT_OK;
      *errorCode = DCM_E_REQUESTSEQUENCEERROR;                                                                                                       /* SBSW_DCM_PARAM_PTR_WRITE */
      break;
    default:
      /* Sub-service can not be processed in the current state;current state is X_SETUP_NOT_STORED */
      lStdResult = DCM_E_NOT_OK;
      *errorCode = DCM_E_CONDITIONSNOTCORRECT;                                                                                                       /* SBSW_DCM_PARAM_PTR_WRITE */
      break;
  }

  return lStdResult;
}

# if (DCM_SVC_86_NVM_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_ExtService86_StopRoE_StoreEvent()
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
 *
 */
DCM_LOCAL FUNC(Std_ReturnType, DCM_CODE) Dcm_ExtService86_StopRoE_StoreEvent(
  Dcm_ContextPtrType pContext,                                                                                                                       /* PRQA S 3673 */ /* MD_Dcm_Design_3673 */
  Dcm_ReadOnlyMsgContextPtrType pMsgContext,
  Dcm_OpStatusType opStatus,
  Dcm_NegativeResponseCodePtrType errorCode
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType                       lStdResult = DCM_E_OK;
  Dcm_Svc86RepeaterProxyContextPtrType pRepContext;
  Dcm_NetTransportObjectConstPtrType   pTranspObj;

  /* ----- Implementation ----------------------------------------------- */
  pRepContext = &pContext->Thread->Repeater.Contexts.Context.Svc86;
  pTranspObj = Dcm_NetGetTransportObject(pContext->Thread->Diag.TObjHdl);

  switch (Dcm_ExtSvc86HandlerState)
  {
    case DCM_EXT_SVC_86_STATE_ACTIVE:
    case DCM_EXT_SVC_86_STATE_INACTIVE_STOP_NOT_STORED:
      Dcm_ExtSvc86OldHandlerState = Dcm_ExtSvc86HandlerState;
      Dcm_ExtSvc86HandlerState = DCM_EXT_SVC_86_STATE_WRITE_NVM_DATA;
      pRepContext->NewNvmData.RoEState = DCM_EXT_SVC_86_STATE_INACTIVE;                                                                              /* SBSW_DCM_GLOBAL_PTR_WRITE */
      pRepContext->NewNvmData.EventId = Dcm_ExtSvc86ActiveEvent;                                                                                     /* SBSW_DCM_GLOBAL_PTR_WRITE */
      pRepContext->NewNvmData.EventType = Dcm_ExtSvc86EventType;                                                                                     /* SBSW_DCM_GLOBAL_PTR_WRITE */
      pRepContext->NewNvmData.EventTypeRecord.DTCStatusMask = Dcm_ExtSvc86DTCStatusMask;                                                             /* SBSW_DCM_GLOBAL_PTR_WRITE */
      pRepContext->NewNvmData.RxPduId = pMsgContext->rxPduId;                                                                                        /* SBSW_DCM_GLOBAL_PTR_WRITE */
      pRepContext->NewNvmData.ClientSrcAddr = pTranspObj->ClientSrcAddr;                                                                             /* SBSW_DCM_GLOBAL_PTR_WRITE */
      /* fall through */
    case DCM_EXT_SVC_86_STATE_WRITE_NVM_DATA:                                                                                                        /* PRQA S 2003 */ /* MD_Dcm_Optimize_2003 */
      lStdResult = Dcm_ExtSvc86UpdateNvM(opStatus, pRepContext, errorCode);                                                                          /* SBSW_DCM_COMB_PTR_FORWARD */
      break;

    case DCM_EXT_SVC_86_STATE_ACTIVE_SETUP_STORED:
      /* Roe state was previously DCM_EXT_SVC_86_STATE_INACTIVE; NvM state must be still DCM_EXT_SVC_86_STATE_INACTIVE, so not necessary to update NvM */
      Dcm_ExtSvc86HandlerState = DCM_EXT_SVC_86_STATE_INACTIVE;
      Dcm_ExtSvc86RoEState = DCM_EXT_SVC_86_STATE_INACTIVE;
      Dcm_RoEOnEventStateChange(Dcm_ExtSvc86ActiveEvent, Dcm_ExtSvc86RoEState);
      break;
    case DCM_EXT_SVC_86_STATE_INACTIVE:
      /* Roe is already stopped and stored */
      break;
    case DCM_EXT_SVC_86_STATE_CLEARED:
      /* Roe is cleared and can not processed in this state */
      *errorCode = DCM_E_REQUESTSEQUENCEERROR;                                                                                                       /* SBSW_DCM_PARAM_PTR_WRITE */
      lStdResult = DCM_E_NOT_OK;
      break;
    default:
      /* Sub-service can not be processed in the current state;current state is X_SETUP_NOT_STORED */
      *errorCode = DCM_E_CONDITIONSNOTCORRECT;                                                                                                       /* SBSW_DCM_PARAM_PTR_WRITE */
      lStdResult = DCM_E_NOT_OK;
      break;
  }

  return lStdResult;
}
# endif

# if (DCM_SVC_86_NVM_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_ExtService86_StartRoE_StoreEvent()
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
 *
 */
DCM_LOCAL FUNC(Std_ReturnType, DCM_CODE) Dcm_ExtService86_StartRoE_StoreEvent(
  Dcm_ContextPtrType pContext,                                                                                                                       /* PRQA S 3673 */ /* MD_Dcm_Design_3673 */
  Dcm_OpStatusType opStatus,
  Dcm_ReadOnlyMsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodePtrType errorCode
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType lStdResult = DCM_E_OK;
  Dcm_Svc86RepeaterProxyContextPtrType pRepContext;
  Dcm_NetTransportObjectConstPtrType pTranspObj;

  /* ----- Implementation ----------------------------------------------- */
  pRepContext = &pContext->Thread->Repeater.Contexts.Context.Svc86;
  pTranspObj = Dcm_NetGetTransportObject(pContext->Thread->Diag.TObjHdl);

  switch (Dcm_ExtSvc86HandlerState)
  {
    case DCM_EXT_SVC_86_STATE_INACTIVE:
    case DCM_EXT_SVC_86_STATE_INACTIVE_STOP_NOT_STORED:
      {
        Dcm_ExtSvc86OldHandlerState = Dcm_ExtSvc86HandlerState;
        Dcm_ExtSvc86HandlerState = DCM_EXT_SVC_86_STATE_WRITE_NVM_DATA;
        pRepContext->NewNvmData.RoEState      = DCM_EXT_SVC_86_STATE_ACTIVE;                                                                         /* SBSW_DCM_GLOBAL_PTR_WRITE */
        pRepContext->NewNvmData.EventId = Dcm_ExtSvc86ActiveEvent;                                                                                   /* SBSW_DCM_GLOBAL_PTR_WRITE */
        pRepContext->NewNvmData.EventType = Dcm_ExtSvc86EventType;                                                                                   /* SBSW_DCM_GLOBAL_PTR_WRITE */
        pRepContext->NewNvmData.EventTypeRecord.DTCStatusMask = Dcm_ExtSvc86DTCStatusMask;                                                           /* SBSW_DCM_GLOBAL_PTR_WRITE */
        pRepContext->NewNvmData.RxPduId       = pMsgContext->rxPduId;                                                                                /* SBSW_DCM_GLOBAL_PTR_WRITE */
        pRepContext->NewNvmData.ClientSrcAddr = pTranspObj->ClientSrcAddr;                                                                           /* SBSW_DCM_GLOBAL_PTR_WRITE */
      }
      /* fall through */
    case DCM_EXT_SVC_86_STATE_WRITE_NVM_DATA:                                                                                                        /* PRQA S 2003 */ /* MD_Dcm_Optimize_2003 */
      lStdResult = Dcm_ExtSvc86UpdateNvM(opStatus, pRepContext, errorCode);                                                                          /* SBSW_DCM_COMB_PTR_FORWARD */
      break;

    case DCM_EXT_SVC_86_STATE_ACTIVE:
      /* Roe is already started and stored */
      break;
    case DCM_EXT_SVC_86_STATE_CLEARED:
      /* RoE is cleared and can not processed in this state */
      lStdResult = DCM_E_NOT_OK;
      *errorCode = DCM_E_REQUESTSEQUENCEERROR;                                                                                                       /* SBSW_DCM_PARAM_PTR_WRITE */
      break;
    default:
      /* Sub-service can not be processed in the current state;current state is X_SETUP_NOT_STORED or DCM_EXT_SVC_86_STATE_ACTIVE_SETUP_STORED */
      *errorCode = DCM_E_CONDITIONSNOTCORRECT;                                                                                                       /* SBSW_DCM_PARAM_PTR_WRITE */
      lStdResult = DCM_E_NOT_OK;
      break;
  }

  return lStdResult;
}
# endif
/**********************************************************************************************************************
 *  Dcm_ExtService86_StartRoE_Internal()
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
 */
DCM_LOCAL FUNC(Std_ReturnType, DCM_CODE) Dcm_ExtService86_StartRoE_Internal(
  Dcm_ContextPtrType pContext,                                                                                                                       /* PRQA S 3673 */ /* MD_Dcm_Design_3673 */
  Dcm_ReadOnlyMsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodePtrType errorCode
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType lStdResult = DCM_E_OK;
  Dcm_NetTransportObjectConstPtrType pTranspObj = Dcm_NetGetTransportObject(pContext->Thread->Diag.TObjHdl);

  /* ----- Implementation ----------------------------------------------- */
  switch (Dcm_ExtSvc86HandlerState)
  {
    case DCM_EXT_SVC_86_STATE_INACTIVE:
      /* RoE state is stopped and stored */
      Dcm_ExtSvc86HandlerState = DCM_EXT_SVC_86_STATE_ACTIVE_SETUP_STORED;
      Dcm_ExtSvc86RoEState = DCM_EXT_SVC_86_STATE_ACTIVE;
      Dcm_ExtSvc86NvMData.RxPduId = pMsgContext->rxPduId;
      Dcm_ExtSvc86NvMData.ClientSrcAddr = pTranspObj->ClientSrcAddr;
      Dcm_RoEOnEventStateChange(Dcm_ExtSvc86ActiveEvent, Dcm_ExtSvc86RoEState);
      break;
    case DCM_EXT_SVC_86_STATE_INACTIVE_SETUP_NOT_STORED:
      /* RoE state is stopped and not stored */
      Dcm_ExtSvc86HandlerState = DCM_EXT_SVC_86_STATE_ACTIVE_SETUP_NOT_STORED;
      Dcm_ExtSvc86RoEState = DCM_EXT_SVC_86_STATE_ACTIVE;
      Dcm_ExtSvc86NvMData.RxPduId = pMsgContext->rxPduId;
      Dcm_ExtSvc86NvMData.ClientSrcAddr = pTranspObj->ClientSrcAddr;
      Dcm_RoEOnEventStateChange(Dcm_ExtSvc86ActiveEvent, Dcm_ExtSvc86RoEState);
      break;
    case DCM_EXT_SVC_86_STATE_CLEARED:
      /* RoE is cleared and can not processed in this state */
      lStdResult = DCM_E_NOT_OK;
      *errorCode = DCM_E_REQUESTSEQUENCEERROR;                                                                                                       /* SBSW_DCM_PARAM_PTR_WRITE */
      break;
    case DCM_EXT_SVC_86_STATE_ACTIVE_SETUP_STORED:
    case DCM_EXT_SVC_86_STATE_ACTIVE_SETUP_NOT_STORED:
      /* RoE already started and not stored */
      break;
    default:
      /* Sub-service can not be processed in the current state */
      lStdResult = DCM_E_NOT_OK;
      *errorCode = DCM_E_CONDITIONSNOTCORRECT;                                                                                                       /* SBSW_DCM_PARAM_PTR_WRITE */
      break;
  }

  return lStdResult;
}

/**********************************************************************************************************************
 *  Dcm_ExtService86_CheckEWT()
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
 */
DCM_LOCAL FUNC(Std_ReturnType, DCM_CODE) Dcm_ExtService86_CheckEWT(
  uint8 eventType,
  uint8 eventWindowTime,
  boolean storeEvent,
  Dcm_NegativeResponseCodePtrType errorCode
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  sint16_least          lLookUpResult;
  Std_ReturnType        lStdResult = DCM_E_OK;

  /* ----- Implementation ----------------------------------------------- */
  lLookUpResult = Dcm_UtiLookUpUint8(Dcm_CfgEventWindowTimeLookUpTable, eventWindowTime);                                                            /* SBSW_DCM_POINTER_FORWARD_GLOBAL */

  if(lLookUpResult < 0)
  {
    /* EWT not supported */
    *errorCode = DCM_E_REQUESTOUTOFRANGE;                                                                                                            /* SBSW_DCM_PARAM_PTR_WRITE */
    lStdResult = DCM_E_NOT_OK;
  }
  else if(eventType != DCM_EXTSVC86_CLEARROE_SID)
  {
    Dcm_SesCtrlType lSession;
    (void)Dcm_GetSesCtrlType(&lSession); /* This API always returns E_OK */                                                                          /* SBSW_DCM_POINTER_FORWARD_STACK */

    lStdResult = Dcm_ExtService86_CheckEWT_Internal(lSession,
                                                    eventType,
                                                    eventWindowTime,
                                                    storeEvent,
                                                    errorCode);                                                                                      /* SBSW_DCM_COMB_PTR_FORWARD */
  }
  else
  {
      /* for SF clearResponseOnEvent only EWT existence is verified; no additional checks needed */
  }

  return lStdResult;
}

# if (DCM_SVC_86_NVM_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_ExtSvc86UpdateNvM()
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
 */
DCM_LOCAL FUNC(Std_ReturnType, DCM_CODE) Dcm_ExtSvc86UpdateNvM(
  Dcm_OpStatusType opStatus,
  Dcm_Svc86RepeaterProxyContextConstPtrType pRepContext,
  Dcm_NegativeResponseCodePtrType errorCode
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType lStdResult;

  /* ----- Implementation ----------------------------------------------- */
  lStdResult = Dcm_UtiNvMWrite(opStatus, &(pRepContext->NewNvmData), DCM_EXT_SVC_86_NVRAM_BLOCKID);                                                  /* SBSW_DCM_ROE_NV_ACCESS */ /* PRQA S 0315 */ /* MD_MSR_Dir1.1 */

  if (lStdResult == E_OK)
  {
    /* NvM storage complete; RoE is now inactive/active/clear - update working mirror data */
    Dcm_ExtSvc86HandlerState = pRepContext->NewNvmData.RoEState;

    if(Dcm_ExtSvc86RoEState != Dcm_ExtSvc86HandlerState)
    {
      /* RoE state changed -> notify event handler */
      Dcm_RoEOnEventStateChange(pRepContext->NewNvmData.EventId, Dcm_ExtSvc86HandlerState);
    }

    Dcm_ExtSvc86NvMData = pRepContext->NewNvmData;

#  if (DCM_SVC_86_RST_ON_DSC_ENABLED == STD_ON)
    Dcm_ExtSvc86DefaultSessionContext.RoEState = Dcm_ExtSvc86RoEState;
    Dcm_ExtSvc86DefaultSessionContext.HandlerState = Dcm_ExtSvc86RoEState;
#  endif

    lStdResult = DCM_E_OK;
  }
  else if (lStdResult == DCM_E_PENDING)
  {
    /* just try later */
  }
  else /* E_NOT_OK */
  {
    /* NvM storage failed; Roe remains active/inactive */
    Dcm_ExtSvc86HandlerState = Dcm_ExtSvc86OldHandlerState;
    *errorCode = DCM_E_CONDITIONSNOTCORRECT;                                                                                                         /* SBSW_DCM_PARAM_PTR_WRITE */
    lStdResult = DCM_E_NOT_OK;
  }

  return lStdResult;
}
# endif

# if (DCM_SVC_86_EVTYPE_ONCHGDTC_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_ExtService86_OnDTCStatusChange()
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
DCM_LOCAL FUNC(Std_ReturnType, DCM_CODE) Dcm_ExtService86_OnDTCStatusChange(
  Dcm_ContextPtrType pContext,                                                                                                                       /* PRQA S 3673 */ /* MD_Dcm_Design_3673 */
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,
  boolean storeEvent,
  Dcm_NegativeResponseCodePtrType errorCode
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType lStdResult = DCM_E_OK;
  uint8 lEventWindowTime;
  uint8 lDtcStatusMask;
  uint16 lSTRT; /* serviceToRespondTo */
  *errorCode = DCM_E_POSITIVERESPONSE;                                                                                                               /* SBSW_DCM_PARAM_PTR_WRITE */

  DCM_IGNORE_UNREF_PARAM(pContext);                                                                                                                  /* PRQA S 3112 */ /* MD_MSR_DummyStmt */

  /* ----- Implementation ----------------------------------------------- */
  lEventWindowTime = Dcm_UtiGetReqDataAsU8Rel(pMsgContext, 0u);                                                                                      /* PRQA S 2985 */ /* MD_Dcm_Redundant_2985 */
  lDtcStatusMask = Dcm_UtiGetReqDataAsU8Rel(pMsgContext, 1u);
  lSTRT = Dcm_UtiGetReqDataAsU16Rel(pMsgContext, 2u);                                                                                                /* PRQA S 2985 */ /* MD_Dcm_Redundant_2985 */

  if(opStatus == DCM_INITIAL)
  {
    lStdResult = Dcm_ExtService86_CheckEWT(DCM_EXTSVC86_ONDTCSTATUSCHANGE_SID, lEventWindowTime, storeEvent, errorCode);                             /* SBSW_DCM_COMB_PTR_FORWARD */

    /* only Service 0x19 0E is accepted as serviceToRespondTo */
    if((lStdResult == DCM_E_OK)
      && (lSTRT != 0x190Eu))
    {
      lStdResult = DCM_E_NOT_OK;
      *errorCode = DCM_E_REQUESTOUTOFRANGE;                                                                                                          /* SBSW_DCM_PARAM_PTR_WRITE */
    }

    /* check if request comes from tester that started RoE */
    if((lStdResult == DCM_E_OK) && (Dcm_ExtSvc86RoEState == DCM_EXT_SVC_86_STATE_ACTIVE))
    {
      lStdResult = Dcm_ExtService86_CheckRoEClient(pContext, pMsgContext, errorCode);                                                                /* SBSW_DCM_COMB_PTR_FORWARD */
    }
  }

  if(lStdResult == DCM_E_OK)
  {
     Dcm_ExtSvc86RoeStateType lOldRoEState = Dcm_ExtSvc86RoEState;
#  if (DCM_SVC_86_NVM_SUPPORT_ENABLED == STD_ON)
    if(storeEvent == TRUE)
    {
      lStdResult = Dcm_ExtService86_DTCStatusChange_StoreEvent(pContext, pMsgContext, opStatus, lDtcStatusMask, errorCode);                          /* SBSW_DCM_PARAM_PTR_FORWARD */
    }
    else
#  endif
    {
      if(Dcm_ExtSvc86RoEState != DCM_EXT_SVC_86_STATE_INACTIVE)
      {
        /* If RoE was started or cleared RoE is stopped */
        Dcm_ExtSvc86RoEState = DCM_EXT_SVC_86_STATE_INACTIVE;
        Dcm_RoEOnEventStateChange(DCM_EXT_SVC_86_ROE_DTC_EVENTID, Dcm_ExtSvc86RoEState);
      }

      Dcm_ExtSvc86HandlerState = DCM_EXT_SVC_86_STATE_INACTIVE_SETUP_NOT_STORED;
      Dcm_ExtSvc86DTCStatusMask = lDtcStatusMask;
    }

#  if (DCM_SVC_86_NVM_SUPPORT_ENABLED == STD_ON)
    if (lStdResult == DCM_E_OK)
#  endif
    {
      /* ServiceToRespondTo is correct */
      Dcm_ExtSvc86ActiveEvent = DCM_EXT_SVC_86_ROE_DTC_EVENTID;

      if(lOldRoEState == DCM_EXT_SVC_86_STATE_ACTIVE)
      {
        /* notify Dem to stop triggering DTC status change */
        Dcm_DemAPI_ControlDTCStatusChangedNotification(FALSE);
      }

      /* Set Event Type */
      Dcm_ExtSvc86EventType =  DCM_EXTSVC86_ONDTCSTATUSCHANGE_SID;

      /* report response data */
      Dcm_UtiProvideResDataAsU8(pMsgContext, 0x00u);                                                                                                 /* SBSW_DCM_PARAM_PTR_FORWARD */
      Dcm_UtiProvideResDataAsU8(pMsgContext, lEventWindowTime);                                                                                      /* SBSW_DCM_PARAM_PTR_FORWARD */
      Dcm_UtiProvideResDataAsU8(pMsgContext, lDtcStatusMask);                                                                                        /* SBSW_DCM_PARAM_PTR_FORWARD */
      Dcm_UtiProvideResDataAsU16(pMsgContext, lSTRT);                                                                                                /* SBSW_DCM_PARAM_PTR_FORWARD */

      Dcm_ExtService86_ClearTaskEvents();
    }/* else storing RoE state is pending or DCM_E_NOT_OK (errorCode already set) */
  } /* else DCM_E_NOT_OK (errorCode already set) */

  return lStdResult;
}                                                                                                                                                    /* PRQA S 6050 */ /* MD_MSR_STCAL */
# endif

# if (DCM_SVC_86_EVTYPE_ONCHGDID_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_ExtService86_CheckDID()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
DCM_LOCAL FUNC(Std_ReturnType, DCM_CODE) Dcm_ExtService86_CheckDID(
  Dcm_ContextPtrType pContext,                                                                                                                       /* PRQA S 3673 */ /* MD_Dcm_Design_3673 */
  Dcm_OpStatusType opStatus,
  uint16 Did,
  Dcm_NegativeResponseCodePtrType errorCode
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType        lStdResult;
  Dcm_Svc86RepeaterProxyContextPtrType pRepContext;

  /* ----- Implementation ----------------------------------------------- */
  pRepContext = &pContext->Thread->Repeater.Contexts.Context.Svc86;

  pRepContext->DidInfoContext.Did = Did;                                                                                                             /* SBSW_DCM_GLOBAL_PTR_WRITE */

  lStdResult = Dcm_DidMgrGetDidInfo(opStatus
                                   ,&pRepContext->DidInfoContext
                                   ,&pRepContext->DidOpTypeContext
                                   ,DCM_DIDMGR_OP_ROE);                                                                                              /* SBSW_DCM_PARAM_PTR_FORWARD */

  if(lStdResult == DCM_E_NOT_OK)
  {
    *errorCode = DCM_E_REQUESTOUTOFRANGE;                                                                                                            /* SBSW_DCM_PARAM_PTR_WRITE */
    lStdResult = DCM_E_NOT_OK;
  }

  return lStdResult;
}
# endif

# if (DCM_SVC_86_EVTYPE_ONCHGDID_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_ExtService86_OnChangeOfDataIdentifier()
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
 *
 *
 *
 *
 *
 *
 *
 *
 */
DCM_LOCAL FUNC(Std_ReturnType, DCM_CODE) Dcm_ExtService86_OnChangeOfDataIdentifier(
  Dcm_ContextPtrType pContext,
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,
  boolean storeEvent,
  Dcm_NegativeResponseCodePtrType errorCode
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType lStdResult = DCM_E_OK;
  uint8  lEventWindowTime;
  uint16 lEventTypeRecord; /* eventTypeRecord Did */
  uint8  lSTRT_Sid; /* serviceToRespondTo service 0x22 */
  uint16 lSTRT_Did; /* serviceToRespondTo DID */
  Dcm_Svc86RepeaterProxyContextConstPtrType pRepContext;
  *errorCode = DCM_E_POSITIVERESPONSE;                                                                                                               /* SBSW_DCM_PARAM_PTR_WRITE */

  /* ----- Implementation ----------------------------------------------- */
  pRepContext = &pContext->Thread->Repeater.Contexts.Context.Svc86;

  lEventWindowTime = Dcm_UtiGetReqDataAsU8Rel(pMsgContext, 0u);                                                                                      /* PRQA S 2985 */ /* MD_Dcm_Redundant_2985 */
  lEventTypeRecord = Dcm_UtiGetReqDataAsU16Rel(pMsgContext, 1u);                                                                                     /* PRQA S 2985 */ /* MD_Dcm_Redundant_2985 */
  lSTRT_Sid = Dcm_UtiGetReqDataAsU8Rel(pMsgContext, 3u);
  lSTRT_Did = Dcm_UtiGetReqDataAsU16Rel(pMsgContext, 4u);                                                                                            /* PRQA S 2985 */ /* MD_Dcm_Redundant_2985 */

  if(opStatus == DCM_INITIAL)
  {
    lStdResult = Dcm_ExtService86_CheckEWT(DCM_EXTSVC86_ONCHANGEOFDATAIDENTIFIER_SID, lEventWindowTime, storeEvent, errorCode);                      /* SBSW_DCM_COMB_PTR_FORWARD */

    /* Only Service 0x22 and same DID in eventTypeRecord and serviceToRespondTo are accepted */
    if(lStdResult == DCM_E_OK)
    {
      if((lSTRT_Sid != 0x22u) || (lEventTypeRecord != lSTRT_Did))
      {
        lStdResult = DCM_E_NOT_OK;
        *errorCode = DCM_E_REQUESTOUTOFRANGE;                                                                                                        /* SBSW_DCM_PARAM_PTR_WRITE */
      }
    }
  }

  if(lStdResult == DCM_E_OK)
  {
    /* Check if Did supports RoE */
    lStdResult = Dcm_ExtService86_CheckDID(pContext, opStatus, lSTRT_Did, errorCode);                                                                /* SBSW_DCM_PARAM_PTR_FORWARD */

    /* Check if request comes from tester that started RoE */
    if((lStdResult == DCM_E_OK) && (Dcm_ExtSvc86RoEState == DCM_EXT_SVC_86_STATE_ACTIVE))
    {
      lStdResult = Dcm_ExtService86_CheckRoEClient(pContext, pMsgContext, errorCode);                                                                /* SBSW_DCM_COMB_PTR_FORWARD */
    }
  }

  if(lStdResult == DCM_E_OK)
  {
    /* Set active event */
    Dcm_ExtSvc86ActiveEvent = Dcm_DidMgrGetRoeEventId(Dcm_CfgDidMgrGetDidInfo(&(pRepContext->DidInfoContext)));

    if(Dcm_ExtSvc86RoEState != DCM_EXT_SVC_86_STATE_INACTIVE)
    {
      /* If RoE was started or cleared RoE is stopped */
      Dcm_ExtSvc86RoEState = DCM_EXT_SVC_86_STATE_INACTIVE;
      Dcm_RoEOnEventStateChange(Dcm_ExtSvc86ActiveEvent, Dcm_ExtSvc86RoEState);
    }

    Dcm_ExtSvc86HandlerState = DCM_EXT_SVC_86_STATE_INACTIVE_SETUP_NOT_STORED;

    /* Set Event Type sid and record */
    Dcm_ExtSvc86EventType =  DCM_EXTSVC86_ONCHANGEOFDATAIDENTIFIER_SID;
    Dcm_ExtSvc86RoEDid = lSTRT_Did;

    /* Report response data */
    Dcm_UtiProvideResDataAsU8(pMsgContext, 0x00u); /* Number of activated elements is always zero */                                                 /* SBSW_DCM_PARAM_PTR_FORWARD */
    Dcm_UtiProvideResDataAsU8(pMsgContext, lEventWindowTime);                                                                                        /* SBSW_DCM_PARAM_PTR_FORWARD */
    Dcm_UtiProvideResDataAsU16(pMsgContext, lEventTypeRecord);                                                                                       /* SBSW_DCM_PARAM_PTR_FORWARD */
    Dcm_UtiProvideResDataAsU8(pMsgContext, lSTRT_Sid);                                                                                               /* SBSW_DCM_PARAM_PTR_FORWARD */
    Dcm_UtiProvideResDataAsU16(pMsgContext, lSTRT_Did);                                                                                              /* SBSW_DCM_PARAM_PTR_FORWARD */

    Dcm_ExtService86_ClearTaskEvents();
  } /* else DCM_E_NOT_OK (errorCode already set) */

  return lStdResult;
}                                                                                                                                                    /* PRQA S 6050 */ /* MD_MSR_STCAL */
# endif
/**********************************************************************************************************************
 *  Dcm_ExtSvc86_ClearRoE()
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
DCM_LOCAL FUNC(Std_ReturnType, DCM_CODE) Dcm_ExtSvc86_ClearRoE(
  Dcm_ContextPtrType pContext,                                                                                                                       /* PRQA S 3673 */ /* MD_Dcm_Design_3673 */
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodePtrType errorCode
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType lStdResult = DCM_E_OK;
  uint8 lEventWindowTime;
  *errorCode = DCM_E_POSITIVERESPONSE;                                                                                                               /* SBSW_DCM_PARAM_PTR_WRITE */

  DCM_IGNORE_UNREF_PARAM(pContext);                                                                                                                  /* PRQA S 3112 */ /* MD_MSR_DummyStmt */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Prepare clear */
  lEventWindowTime = Dcm_UtiGetReqDataAsU8(pMsgContext);                                                                                             /* PRQA S 2985 */ /* MD_Dcm_Redundant_2985 */
  if(opStatus == DCM_INITIAL)
  {
    lStdResult = Dcm_ExtService86_CheckEWT(DCM_EXTSVC86_CLEARROE_SID, lEventWindowTime, TRUE, errorCode);                                            /* SBSW_DCM_COMB_PTR_FORWARD */
  }

  /* #20 Execute clear */
  if(lStdResult == DCM_E_OK)
  {
# if (DCM_SVC_86_EVTYPE_ONCHGDTC_ENABLED == STD_ON)
    Dcm_ExtSvc86RoeStateType lOldRoEState = Dcm_ExtSvc86RoEState;
# endif

    /* If current RoE state is not stopped, started or setup: */
    if(Dcm_ExtSvc86RoEState != DCM_EXT_SVC_86_STATE_CLEARED)
    {
# if (DCM_SVC_86_NVM_SUPPORT_ENABLED == STD_ON)
      Dcm_Svc86RepeaterProxyContextPtrType pRepContext;

      pRepContext = &pContext->Thread->Repeater.Contexts.Context.Svc86;

      if(Dcm_ExtSvc86HandlerState == DCM_EXT_SVC_86_STATE_WRITE_NVM_DATA)
      {
        /* NvMUpdate is pending */
        lStdResult = Dcm_ExtSvc86UpdateNvM(opStatus, pRepContext, errorCode);                                                                        /* SBSW_DCM_COMB_PTR_FORWARD */
      }
      else
      {
        Dcm_NetTransportObjectConstPtrType pTranspObj = Dcm_NetGetTransportObject(pContext->Thread->Diag.TObjHdl);
        /* Update in NvM */
        Dcm_ExtSvc86OldHandlerState = Dcm_ExtSvc86HandlerState;
        Dcm_ExtSvc86HandlerState = DCM_EXT_SVC_86_STATE_WRITE_NVM_DATA;
        pRepContext->NewNvmData.RoEState = DCM_EXT_SVC_86_STATE_CLEARED;                                                                             /* SBSW_DCM_GLOBAL_PTR_WRITE */
        pRepContext->NewNvmData.EventTypeRecord.DTCStatusMask = Dcm_ExtSvc86DTCStatusMask;                                                           /* SBSW_DCM_GLOBAL_PTR_WRITE */
        pRepContext->NewNvmData.EventType = Dcm_ExtSvc86EventType;                                                                                   /* SBSW_DCM_GLOBAL_PTR_WRITE */
        pRepContext->NewNvmData.EventId = Dcm_ExtSvc86ActiveEvent;                                                                                   /* SBSW_DCM_GLOBAL_PTR_WRITE */
        pRepContext->NewNvmData.RxPduId = pMsgContext->rxPduId;                                                                                      /* SBSW_DCM_GLOBAL_PTR_WRITE */
        pRepContext->NewNvmData.ClientSrcAddr = pTranspObj->ClientSrcAddr;                                                                           /* SBSW_DCM_GLOBAL_PTR_WRITE */
        lStdResult = Dcm_ExtSvc86UpdateNvM(opStatus, pRepContext, errorCode);                                                                        /* SBSW_DCM_COMB_PTR_FORWARD */
      }
# else
      Dcm_ExtSvc86HandlerState = DCM_EXT_SVC_86_STATE_CLEARED;
      Dcm_ExtSvc86RoEState = DCM_EXT_SVC_86_STATE_CLEARED;
      Dcm_RoEOnEventStateChange(Dcm_ExtSvc86ActiveEvent, Dcm_ExtSvc86RoEState);
# endif

# if (DCM_SVC_86_NVM_SUPPORT_ENABLED == STD_ON)
      if (lStdResult == DCM_E_OK)
# endif
      {
# if (DCM_SVC_86_EVTYPE_ONCHGDTC_ENABLED == STD_ON)
        if ((lOldRoEState == DCM_EXT_SVC_86_STATE_ACTIVE) && (Dcm_ExtSvc86EventType == DCM_EXTSVC86_ONDTCSTATUSCHANGE_SID))
        {
          /* Notify Dem to stop triggering DTC status change */
          Dcm_DemAPI_ControlDTCStatusChangedNotification(FALSE);
        }
# endif
        /* Clear task event */
        Dcm_ExtService86_ClearTaskEvents();
      }/* else storing RoE state is pending or DCM_E_NOT_OK (errorCode already set) */
    }
  } /* else DCM_E_NOT_OK (errorCode already set) */

  /* #30 Finalize clear */
  /* If operation finished successfully: */
  if (lStdResult == DCM_E_OK)
  {
    /* Provide clear positive response data */
    Dcm_UtiProvideResDataAsU8(pMsgContext, 0x00u);                                                                                                   /* SBSW_DCM_PARAM_PTR_FORWARD */
    Dcm_UtiProvideResDataAsU8(pMsgContext, lEventWindowTime);                                                                                        /* SBSW_DCM_PARAM_PTR_FORWARD */
  }

  return lStdResult;
}                                                                                                                                                    /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif /* (DCM_SVC_86_SUPPORT_ENABLED == STD_ON) */
#define DCM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */
#if (DCM_SVC_86_SUPPORT_ENABLED == STD_ON)
# if (DCM_SVC_86_EVTYPE_ONCHGDTC_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_DemTriggerOnDTCStatus()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_DemTriggerOnDTCStatus(
  uint32 DTC,
  uint8 DTCStatusOld,
  uint8 DTCStatusNew
  )
{
  uint8 lErrorId = DCM_E_NO_ERROR;

  /* ----- Development Error Checks ---------------------------------------- */
  if(Dcm_DebugDetectError(Dcm_DebugIsModuleInitialized() == FALSE))
  {
    lErrorId = DCM_E_UNINIT;
  }
  else
  {
    /* ----- Implementation ------------------------------------------------ */
    if( (Dcm_ExtSvc86RoEState == DCM_EXT_SVC_86_STATE_ACTIVE)
      &&(Dcm_ExtSvc86EventType == DCM_EXTSVC86_ONDTCSTATUSCHANGE_SID)
      &&(((DTCStatusOld ^ DTCStatusNew) & Dcm_ExtSvc86DTCStatusMask) != 0u) )
    {
      /* bit changes 0->1 or 1->0 */

      /* Check ComM state */
      if(Dcm_NetGetComState(Dcm_ExtSvc86NvMData.RxPduId) == DCM_NET_COMM_STATE_RX_EN_TX_EN)
      {
        /* trigger RoE */
        Dcm_TskSetEvent(DCM_TSK_ID_ROE, DCM_EXT_TSK_EV_ROE_SEND);
      }
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
  Dcm_DebugReportError(DCM_SID_DEMTRIGGERONDTCSTATUS, lErrorId);

  DCM_IGNORE_UNREF_PARAM(DTC);                                                                                                                       /* PRQA S 3112 */ /* MD_MSR_DummyStmt */

  return DCM_E_OK;
}
# endif

# if (DCM_SVC_86_EVTYPE_ONCHGDID_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_TriggerOnEvent()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_TriggerOnEvent(
  uint8 RoeEventId                                                                                                                                   /* PRQA S 1330 */ /* MD_Dcm_RteSpecific_1330 */
  )
{
  Std_ReturnType lStdResult = DCM_E_NOT_OK;
  uint8          lErrorId   = DCM_E_NO_ERROR;

  /* ----- Development Error Checks ---------------------------------------- */
  if(Dcm_DebugDetectError(Dcm_DebugIsModuleInitialized() == FALSE))
  {
    lErrorId = DCM_E_UNINIT;
  }
  else if(Dcm_DebugDetectError(RoeEventId >= DCM_CFGMODEROEEVENTMODESWITCHINFOTABLE_SIZE))
  {
    lErrorId = DCM_E_PARAM;
  }
  else
  {
    /* ----- Implementation ------------------------------------------------ */
    /* check if DCM is able to process the request */
    if((Dcm_ExtSvc86RoEState == DCM_EXT_SVC_86_STATE_ACTIVE)
      && (Dcm_ExtSvc86EventType == DCM_EXTSVC86_ONCHANGEOFDATAIDENTIFIER_SID)
      && (RoeEventId == Dcm_ExtSvc86ActiveEvent))
    {
        /* RoEEventId is valid */
        lStdResult = DCM_E_OK;

        /* Check ComM state */
        if(Dcm_NetGetComState(Dcm_ExtSvc86NvMData.RxPduId) == DCM_NET_COMM_STATE_RX_EN_TX_EN)
        {
          /* trigger RoE */
          Dcm_TskSetEvent(DCM_TSK_ID_ROE, DCM_EXT_TSK_EV_ROE_SEND);
        }
    }/* else - event triggered under invalid conditions */
  }
  /* ----- Development Error Report ---------------------------------------- */
  Dcm_DebugReportError(DCM_SID_TRIGGERONEVENT, lErrorId);

  return lStdResult;
}
# endif /* (DCM_SVC_86_EVTYPE_ONCHGDID_ENABLED == STD_ON) */
#endif /* (DCM_SVC_86_SUPPORT_ENABLED == STD_ON) */
#define DCM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define DCM_START_SEC_CODE
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */
#if (DCM_SVC_86_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_ExtService86Init()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, DCM_CODE) Dcm_ExtService86Init(
  void
  )
{
  /* set state to cleared; reading NvM in first task cycle */
  Dcm_ExtSvc86HandlerState = DCM_EXT_SVC_86_STATE_CLEARED;
  Dcm_ExtSvc86ReadTimeout  = DCM_EXT_SVC_86_READ_TIMEOUT;
  Dcm_ExtSvc86NvMReadOpStatus = DCM_INITIAL;
  Dcm_ExtSvc86STRTSendingState = DCM_EXT_SVC_86_STRT_STATE_IDLE;

  /* set default values for NvM data */
  Dcm_ExtSvc86NvMData.RoEState   = DCM_EXT_SVC_86_STATE_CLEARED;
  Dcm_ExtSvc86NvMData.RxPduId = 0;
  Dcm_ExtSvc86NvMData.EventId = 0;
  Dcm_ExtSvc86NvMData.EventType = 0;
  Dcm_ExtSvc86NvMData.ClientSrcAddr = 0;
# if (DCM_SVC_86_EVTYPE_ONCHGDID_ENABLED == STD_ON)
  Dcm_ExtSvc86NvMData.EventTypeRecord.Did = 0x00;                                                                                                    /* PRQA S 2982 */ /* MD_Dcm_Redundant_2982 */
# endif
# if (DCM_SVC_86_EVTYPE_ONCHGDID_ENABLED == STD_ON)
  Dcm_ExtSvc86NvMData.EventTypeRecord.DTCStatusMask = 0x00;                                                                                          /* PRQA S 2982 */ /* MD_Dcm_Redundant_2982 */
# endif

  Dcm_TskSetEvent(DCM_TSK_ID_ROE, DCM_EXT_TSK_EV_ROE_ACTIVATE);
}

/**********************************************************************************************************************
 *  Dcm_ExtSvc86Task()
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
 *
 *
 *
 *
 *
 *
 */
FUNC(void, DCM_CODE) Dcm_ExtSvc86Task(
  Dcm_ContextPtrType pContext,                                                                                                                       /* PRQA S 3673 */ /* MD_Dcm_Design_3673 */
  Dcm_TskEventContextPtrType pEventContext
  )
{
  DCM_IGNORE_UNREF_PARAM(pContext);                                                                                                                  /* PRQA S 3112 */ /* MD_MSR_DummyStmt */

# if (DCM_SVC_86_NVM_SUPPORT_ENABLED == STD_ON)
  /* check if configured event occurred */
  if (Dcm_TskIsLocalEventSet(pEventContext->Ev, DCM_EXT_TSK_EV_ROE_ACTIVATE))
  {
    Dcm_ExtSvc86ReadNvM(pEventContext);                                                                                                              /* SBSW_DCM_PARAM_PTR_FORWARD */
  }
# endif

  if (Dcm_TskIsLocalEventSet(pEventContext->Ev, DCM_EXT_TSK_EV_ROE_TX_END))
  {
# if (DCM_SVC_86_TIMER_ENABLED == STD_ON)
    /* response transmission triggered; restart timer */
    Dcm_TmrStartTimer(DCM_TMR_ID_SVC86_SCHEDULER, DCM_EXT_SVC_86_INTERMESSAGETIME);
    Dcm_ExtSvc86STRTSendingState = DCM_EXT_SVC_86_STRT_STATE_WAIT_FOR_TIMEOUT;
# else
    /* response transmission triggered; next ServicToResponseTo can be sent */
    Dcm_ExtSvc86STRTSendingState = DCM_EXT_SVC_86_STRT_STATE_IDLE;
# endif
  }

  if(Dcm_TskIsLocalEventSet(pEventContext->Ev, DCM_EXT_TSK_EV_ROE_SEND))
  {
    /* RoE event was triggered by Dem */
    if(Dcm_ExtSvc86RoEState == DCM_EXT_SVC_86_STATE_ACTIVE)
    {
      /* RoE is Active */

      /* Check ComM state */
      if(Dcm_NetGetComState(Dcm_ExtSvc86NvMData.RxPduId) == DCM_NET_COMM_STATE_RX_EN_TX_EN)
      {
        /* STRT state is IDLE */
        if (Dcm_ExtSvc86STRTSendingState == DCM_EXT_SVC_86_STRT_STATE_IDLE)
        {
          /* STRT state is set to SENDING -> next event will be queued */
          Dcm_ExtSvc86STRTSendingState = DCM_EXT_SVC_86_STRT_STATE_SENDING;
          Dcm_ExtService86_Send_STRT(pEventContext);                                                                                                 /* SBSW_DCM_PARAM_PTR_FORWARD */
        }
        else
        {
          /* Try next task cycle */
          Dcm_TskSetLocalEvent(pEventContext->PostEv, DCM_EXT_TSK_EV_ROE_SEND);                                                                      /* SBSW_DCM_PARAM_PTR_WRITE */
        }
      }
    }
  }
}

# if (DCM_SVC_86_TIMER_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_ExtOnTimeoutSvc86Scheduler()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Dcm_TmrTimerCntrMemType, DCM_CODE) Dcm_ExtOnTimeoutSvc86Scheduler(
  Dcm_ThreadIdMemType threadId
  )
{
  DCM_IGNORE_UNREF_PARAM(threadId);                                                                                                                  /* PRQA S 3112 */ /* MD_MSR_DummyStmt */

  Dcm_ExtSvc86STRTSendingState = DCM_EXT_SVC_86_STRT_STATE_IDLE;
  return 0u;/* no reload */
}
# endif

# if (DCM_SVC_86_RST_ON_DSC_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_ExtSvc86OnChangeSession()
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
 */
FUNC(void, DCM_CODE) Dcm_ExtSvc86OnChangeSession(
  Dcm_CfgStateGroupOptType oldSession,
  Dcm_CfgStateGroupOptType newSession
  )
{
  if ( (DCM_STATE_VALUE_SESSION_INIT & (oldSession & newSession)) == 0u)
  {
    /* at least one session is non-default */
    Dcm_NegativeResponseCodeType errorCode = DCM_E_POSITIVERESPONSE;

    if ((DCM_STATE_VALUE_SESSION_INIT & oldSession) != 0u)
    {
      /* default session is left; save context */
      Dcm_ExtSvc86DefaultSessionContext.RoEState = Dcm_ExtSvc86RoEState;
      Dcm_ExtSvc86DefaultSessionContext.HandlerState = Dcm_ExtSvc86HandlerState;
      Dcm_ExtSvc86DefaultSessionContext.RxPduId = Dcm_ExtSvc86NvMData.RxPduId;
    }

    if (((DCM_STATE_VALUE_SESSION_INIT & newSession) != 0u) && (Dcm_ExtSvc86DefaultSessionContext.RoEState == DCM_EXT_SVC_86_STATE_ACTIVE))
    {
      /* RoE was started when leaving default session -> restart RoE */
      if(Dcm_ExtSvc86RoEState != Dcm_ExtSvc86DefaultSessionContext.RoEState)
      {
        Dcm_RoEOnEventStateChange(Dcm_ExtSvc86ActiveEvent, Dcm_ExtSvc86DefaultSessionContext.RoEState);
      }

      /* restore default session context */
      Dcm_ExtSvc86RoEState = Dcm_ExtSvc86DefaultSessionContext.RoEState;
      Dcm_ExtSvc86HandlerState = Dcm_ExtSvc86DefaultSessionContext.HandlerState;
      Dcm_ExtSvc86NvMData.RxPduId = Dcm_ExtSvc86DefaultSessionContext.RxPduId;
    }
    else if(Dcm_ExtSvc86RoEState == DCM_EXT_SVC_86_STATE_ACTIVE)
    {
      /* stop RoE on session change if it was started before; Dcm_ExtService86_StopRoE_Internal() returns DCM_E_OK if RoE state is active */
      (void)Dcm_ExtService86_StopRoE_Internal(&errorCode);                                                                                           /* SBSW_DCM_POINTER_FORWARD_STACK */
    }
    else
    {
      /* nothing to do */
    }
  }
}
# endif

/**********************************************************************************************************************
 *  Dcm_Svc86IsStorageStateBitPartOfSubFunc()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(boolean, DCM_CODE) Dcm_Svc86IsStorageStateBitPartOfSubFunc(
  void
  )
{
  return TRUE;
}
#endif /* (DCM_SVC_86_SUPPORT_ENABLED == STD_ON) */
#define DCM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define DCM_START_SEC_CALLOUT_CODE
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */
#if (DCM_SVC_86_SUPPORT_ENABLED == STD_ON)
# if (DCM_SVC_86_00_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_ExtService86_00Processor()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_ExtService86_00Processor(
  Dcm_ContextPtrType pContext,                                                                                                                       /* PRQA S 3673 */ /* MD_Dcm_Design_3673 */
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodePtrType ErrorCode
  )
{
  Std_ReturnType lStdResult;

  lStdResult = Dcm_ExtService86_StopRoE(pContext, opStatus, pMsgContext, FALSE, ErrorCode);                                                          /* SBSW_DCM_PARAM_PTR_FORWARD */

  return lStdResult;
}
# endif

# if (DCM_SVC_86_40_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_ExtService86_40Processor()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_ExtService86_40Processor(
  Dcm_ContextPtrType pContext,                                                                                                                       /* PRQA S 3673 */ /* MD_Dcm_Design_3673 */
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodePtrType ErrorCode
  )
{
  Std_ReturnType lStdResult;

  lStdResult = Dcm_ExtService86_StopRoE(pContext, opStatus, pMsgContext, TRUE, ErrorCode);                                                           /* SBSW_DCM_PARAM_PTR_FORWARD */

  return lStdResult;
}
# endif

# if (DCM_SVC_86_01_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_ExtService86_01Processor()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_ExtService86_01Processor(
  Dcm_ContextPtrType pContext,                                                                                                                       /* PRQA S 3673 */ /* MD_Dcm_Design_3673 */
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodePtrType ErrorCode
  )
{
  Std_ReturnType lStdResult;

  lStdResult = Dcm_ExtService86_OnDTCStatusChange(pContext, opStatus, pMsgContext, FALSE, ErrorCode);                                                /* SBSW_DCM_PARAM_PTR_FORWARD */

  return lStdResult;
}
# endif

# if (DCM_SVC_86_41_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_ExtService86_41Processor()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_ExtService86_41Processor(
  Dcm_ContextPtrType pContext,
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodePtrType ErrorCode
  )
{
  Std_ReturnType lStdResult;

  lStdResult = Dcm_ExtService86_OnDTCStatusChange(pContext, opStatus, pMsgContext, TRUE, ErrorCode);                                                 /* SBSW_DCM_PARAM_PTR_FORWARD */

  return lStdResult;
}
# endif

# if (DCM_SVC_86_03_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_ExtService86_03Processor()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_ExtService86_03Processor(
  Dcm_ContextPtrType pContext,
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodePtrType ErrorCode
  )
{
  Std_ReturnType lStdResult;

  lStdResult = Dcm_ExtService86_OnChangeOfDataIdentifier(pContext, opStatus, pMsgContext, FALSE, ErrorCode);                                         /* SBSW_DCM_PARAM_PTR_FORWARD */

  return lStdResult;
}
# endif

# if (DCM_SVC_86_05_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_ExtService86_05Processor()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_ExtService86_05Processor(
  Dcm_ContextPtrType pContext,
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodePtrType ErrorCode
  )
{
  Std_ReturnType lStdResult;

  lStdResult = Dcm_ExtService86_StartRoE(pContext, opStatus, pMsgContext, FALSE, ErrorCode);                                                         /* SBSW_DCM_PARAM_PTR_FORWARD */

  return lStdResult;
}
# endif

# if (DCM_SVC_86_45_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_ExtService86_45Processor()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_ExtService86_45Processor(
  Dcm_ContextPtrType pContext,                                                                                                                       /* PRQA S 3673 */ /* MD_Dcm_Design_3673 */
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodePtrType ErrorCode
  )
{
  Std_ReturnType lStdResult;

  lStdResult = Dcm_ExtService86_StartRoE(pContext, opStatus, pMsgContext, TRUE, ErrorCode);                                                          /* SBSW_DCM_PARAM_PTR_FORWARD */

  return lStdResult;
}
# endif

# if (DCM_SVC_86_06_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_ExtService86_06Processor()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_ExtService86_06Processor(
  Dcm_ContextPtrType pContext,
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodePtrType ErrorCode
  )
{
  Std_ReturnType lStdResult;

  lStdResult = Dcm_ExtSvc86_ClearRoE(pContext, opStatus, pMsgContext, ErrorCode);                                                                    /* SBSW_DCM_PARAM_PTR_FORWARD */

  return lStdResult;
}
# endif

# if (DCM_SVC_86_46_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_ExtService86_46Processor()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_ExtService86_46Processor(
  Dcm_ContextPtrType pContext,
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodePtrType ErrorCode
  )
{
  Std_ReturnType lStdResult;

  lStdResult = Dcm_ExtSvc86_ClearRoE(pContext, opStatus, pMsgContext, ErrorCode);                                                                    /* SBSW_DCM_PARAM_PTR_FORWARD */

  return lStdResult;
}
# endif
#endif /* (DCM_SVC_86_SUPPORT_ENABLED == STD_ON) */
#define DCM_STOP_SEC_CALLOUT_CODE
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  END OF FILE: Dcm_Ext.c
 *********************************************************************************************************************/
