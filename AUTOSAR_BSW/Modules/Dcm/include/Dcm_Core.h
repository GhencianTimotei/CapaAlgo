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
/**        \file  Dcm_Core.h
 *        \brief  Public interface of DCM for other components
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
#if !defined(DCM_CORE_H)
# define DCM_CORE_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* Error codes */
# define DCM_E_NO_ERROR                                              (0x00u) /*!< Used to check if no error occurred */
# define DCM_E_INTERFACE_TIMEOUT                                     (0x01u) /*!< Error code: Timeout occurred during interaction with another module*/
# define DCM_E_INTERFACE_RETURN_VALUE                                (0x02u) /*!< Error code: Interface returned an invalid return value */
# define DCM_E_INTERFACE_BUFFER_OVERFLOW                             (0x03u) /*!< Error code: Interface returned to many data */
# define DCM_E_UNINIT                                                (0x05u) /*!< Error code: API service used without module initialization */
# define DCM_E_PARAM                                                 (0x06u) /*!< Error code: API service used with invalid parameter */
# define DCM_E_PARAM_POINTER                                         (0x07u) /*!< Error code: API service used with invalid pointer parameter (NULL) */
# define DCM_E_ILLEGAL_STATE                                         (0x40u) /*!< Error code: API service used in invalid state */
# define DCM_E_INVALID_CONFIG                                        (0x41u) /*!< Error code: Configuration is invalid */
# define DCM_E_CRITICAL_ERROR                                        (0x42u) /*!< Error code: Internal critical error detected */

/* API service IDs */
# define DCM_SID_STARTOFRECEPTION                                    (0x00u) /*!< Service ID: Dcm_StartOfReception() */
# define DCM_SID_INIT                                                (0x01u) /*!< Service ID: Dcm_Init() */
# define DCM_SID_COPYRXDATA                                          (0x02u) /*!< Service ID: Dcm_CopyRxData() */
# define DCM_SID_TPRXINDICATION                                      (0x03u) /*!< Service ID: Dcm_TpRxIndication() */
# define DCM_SID_COPYTXDATA                                          (0x04u) /*!< Service ID: Dcm_CopyTxData() */
# define DCM_SID_TPTXCONFIRMATION                                    (0x05u) /*!< Service ID: Dcm_TpTxConfirmation() */
# define DCM_SID_GETSESCTRLTYPE                                      (0x06u) /*!< Service ID: Dcm_GetSesCtrlType() */
# define DCM_SID_GETSECLEVEL                                         (0x0Du) /*!< Service ID: Dcm_GetSecurityLevel() */
# define DCM_SID_GETACTIVEPROTOCOL                                   (0x0Fu) /*!< Service ID: Dcm_GetActiveProtocol() */
# define DCM_SID_COMMENTERNOCOMMODE                                  (0x21u) /*!< Service ID: Dcm_ComM_NoComModeEntered() */
# define DCM_SID_COMMENTERSILENTCOMMODE                              (0x22u) /*!< Service ID: Dcm_ComM_SilentComModeEntered() */
# define DCM_SID_COMMENTERFULLCOMMODE                                (0x23u) /*!< Service ID: Dcm_ComM_FullComModeEntered() */
# define DCM_SID_GETVERSIONINFO                                      (0x24u) /*!< Service ID: Dcm_GetVersionInfo() */
# define DCM_SID_MAINFUNCTION                                        (0x25u) /*!< Service ID: Dcm_MainFunction() */
# define DCM_SID_READMEMORY                                          (0x26u) /*!< Service ID: Dcm_ReadMemory() */
# define DCM_SID_PROCESSTRANSFERDATAREAD                             (0x26u) /*!< Service ID: Dcm_ProcessTransferDataRead() */
# define DCM_SID_WRITEMEMORY                                         (0x27u) /*!< Service ID: Dcm_WriteMemory() */
# define DCM_SID_PROCESSTRANSFERDATAWRITE                            (0x27u) /*!< Service ID: Dcm_ProcessTransferDataWrite() */
# define DCM_SID_RESET2DEFAULTSESSION                                (0x2Au) /*!< Service ID: Dcm_ResetToDefaultSession() */
# define DCM_SID_DEMTRIGGERONDTCSTATUS                               (0x2Bu) /*!< Service ID: Dcm_DemTriggerOnDTCStatus() */
# define DCM_SID_TRIGGERONEVENT                                      (0x2Du) /*!< Service ID: Dcm_TriggerOnEvent() */
# define DCM_SID_PROCESSREQUESTDOWNLOAD                              (0x30u) /*!< Service ID: Dcm_ProcessRequestDownload() */
# define DCM_SID_EXT_PROCESSINGDONE                                  (0x31u) /*!< Service ID: Dcm_ExternalProcessingDone() */
# define DCM_SID_PROCESSREQUESTUPLOAD                                (0x31u) /*!< Service ID: Dcm_ProcessRequestUpload() */
# define DCM_SID_PROCESSREQUESTTRANSFEREXIT                          (0x32u) /*!< Service ID: Dcm_ProcessRequestTransferExit() */
# define DCM_SID_SVCPORT_DATASVCS_OP_READDATA_SYNC                   (0x34u) /*!< Service ID: Xxx_ReadData() (synchronous) */
# define DCM_SID_SVCPORT_DATASVCS_OP_READDATA_ASYNC                  (0x3Bu) /*!< Service ID: Xxx_ReadData() (asynchronous) */
# define DCM_SID_SVCPORT_DATASVCS_OP_READDIDRANGE                    (0x40u) /*!< Service ID: Xxx_ReadDidData() */
# define DCM_SID_SVCPORT_DATASVCS_OP_WRITEDIDRANGE                   (0x41u) /*!< Service ID: Xxx_WriteDidData() */
# define DCM_SID_GETSEED                                             (0x44u) /*!< Service ID: Xxx_GetSeed() */
# define DCM_SID_COMPAREKEY                                          (0x47u) /*!< Service ID: Xxx_CompareKey() */
# define DCM_SID_EXT_SETNEGRESPONSE                                  (0x48u) /*!< Service ID: Dcm_ExternalSetNegResponse() */
# define DCM_SID_SETACTIVEDIAGNOSTIC                                 (0x56u) /*!< Service ID: Dcm_SetActiveDiagnostic() */
# define DCM_SID_GETSECURITYATTEMPTCOUNTER                           (0x59u) /*!< Service ID: Xxx_GetSecurityAttemptCounter() */
# define DCM_SID_SETSECURITYATTEMPTCOUNTER                           (0x5Au) /*!< Service ID: Xxx_SetSecurityAttemptCounter() */
# define DCM_SID_SVCPORT_DATASVCS_OP_READVID                         (0x60u) /*!< Service ID: Xxx_GetInfotypeValueData() */
# define DCM_SID_DCMSETDEAUTHENTICATEDROLE                           (0x79u) /*!< Service ID: Dcm_SetDeauthenticatedRole() */
# define DCM_SID_TXCONFIRMATION                                      (0xA1u) /*!< Service ID: Dcm_TxConfirmation() */
# define DCM_SID_TRIGGERTRANSMIT                                     (0xA2u) /*!< Service ID: Dcm_TriggerTransmit() */
# define DCM_SID_PROVIDERECOVERYSTATES                               (0xA3u) /*!< Service ID: Dcm_ProvideRecoveryStates() */
# define DCM_SID_ONREQUESTDETECTION                                  (0xA4u) /*!< Service ID: Dcm_OnRequestDetection() */
# define DCM_SID_GETRECOVERYSTATES                                   (0xA5u) /*!< Service ID: Dcm_GetRecoveryStates() */
# define DCM_SID_GETTESTERSOURCEADDRESS                              (0xA6u) /*!< Service ID: Dcm_GetTesterSourceAddress() */
# define DCM_SID_GETSECLEVELFIXEDBYTES                               (0xA7u) /*!< Service ID: Dcm_GetSecurityLevelFixedBytes() */
# define DCM_SID_PROCESSVIRTUALREQUEST                               (0xA8u) /*!< Service ID: Dcm_ProcessVirtualRequest() */
# define DCM_SID_SETSECLEVEL                                         (0xA9u) /*!< Service ID: Dcm_SetSecurityLevel() */
# define DCM_SID_SVCPORT_DATASVCS_OP_READPAGEDDID                    (0xAAu) /*!< Service ID: Xxx_ReadData() (paged-data-reading) */
# define DCM_SID_GETREQUESTKIND                                      (0xABu) /*!< Service ID: Dcm_GetRequestKind() */
# define DCM_SID_VSGSETSINGLE                                        (0xACu) /*!< Service ID: Dcm_VsgSetSingle() */
# define DCM_SID_VSGISACTIVE                                         (0xADu) /*!< Service ID: Dcm_VsgIsActiveAnyOf() */
# define DCM_SID_VSGSETMULTIPLE                                      (0xAEu) /*!< Service ID: Dcm_VsgSetMultiple() */
# define DCM_SID_VSGISACTIVEANY                                      (0xAFu) /*!< Service ID: Dcm_VsgIsActiveAnyOf() */
# define DCM_SID_SVCDISPATCHER                                       (0xB0u) /*!< Service ID: Dcm_HandleServiceExtern() */
# define DCM_SID_KEYMASYNCCERTIFICATEVERIFYFINISHED                  (0xB1u) /*!< Service ID: Dcm_KeyMAsyncCertificateVerifyFinished() */
# define DCM_SID_CSMASYNCJOBFINISHED                                 (0xB2u) /*!< Service ID: Dcm_CsmAsyncJobFinished() */
# define DCM_SID_SETSECURITYBYPASS                                   (0xB3u) /*!< Service ID: Dcm_SetSecurityBypass() */
# define DCM_SID_SETSPECIFICCAUSECODE                                (0xB4u) /*!< Service ID: Dcm_SetSpecificCauseCode() */
# define DCM_SID_INTERNAL                                            (0xF0u) /*!< Service ID: Internal functions */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION DECLARATIONS
 *********************************************************************************************************************/
# define DCM_START_SEC_CODE
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */
# if (DCM_FBLMGR_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_ProcessRequestDownload()
 *********************************************************************************************************************/
/*! \brief         Starts a software download sequence.
 *  \details        This call-out is used during software download processing, if RequestDownload is configured.
 *  \param[in]      OpStatus                Operation status
 *  \param[in]      DataFormatIdentifier    Identifier of the Data Format
 *  \param[in]      MemoryIdentifier        Identifier of the Memory Block
 *  \param[in]      MemoryAddress           Starting address of server memory from which data is to be retrieved
 *  \param[in]      MemorySize              Number of bytes in the MemoryData
 *  \param[in,out]  BlockLength             Maximum number of bytes for one Dcm_ProcessTransferDataWrite
 *  \param[out]     ErrorCode               Negative response code in case return value is DCM_E_NOT_OK
 *  \return         DCM_E_OK                Request was successful
 *  \return         DCM_E_NOT_OK            Request was not successful
 *  \return         DCM_E_PENDING           Request is not yet finished
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    FALSE
 *  \config         This function is only available if DCM_FBLMGR_SUPPORT_ENABLED = STD_ON.
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_ProcessRequestDownload(
  Dcm_OpStatusType OpStatus,
  uint8  DataFormatIdentifier,
  uint8  MemoryIdentifier,
  uint32 MemoryAddress,
  uint32 MemorySize,
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) BlockLength,
  Dcm_NegativeResponseCodePtrType ErrorCode
  );

/**********************************************************************************************************************
 *  Dcm_ProcessTransferDataWrite()
 *********************************************************************************************************************/
/*! \brief         Transfers data during a download sequence.
 *  \details        This call-out is used during software download processing, if TransferData is configured.
 *  \param[in]      OpStatus                Operation status
 *  \param[in]      MemoryIdentifier        Identifier of the Memory Block
 *  \param[in]      MemoryAddress           Starting address of server memory from which data is to be retrieved
 *  \param[in]      MemorySize              Number of bytes in the MemoryData
 *  \param[in]      MemoryData              Data to write (Points to the diagnostic buffer in DCM)
 *  \param[out]     ErrorCode               Negative response code in case return value is DCM_E_NOT_OK
 *  \return         DCM_WRITE_OK            Write was successful
 *  \return         DCM_WRITE_FAILED        Write was not successful
 *  \return         DCM_WRITE_PENDING       Write is not yet finished
 *  \return         DCM_WRITE_FORCE_RCRRP   Enforce RCR-RP transmission (vendor extension)
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    FALSE
 *  \config         This function is only available if DCM_FBLMGR_SUPPORT_ENABLED = STD_ON.
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Dcm_ReturnWriteMemoryType, DCM_CALLOUT_CODE) Dcm_ProcessTransferDataWrite(
  Dcm_OpStatusType OpStatus,
  uint8  MemoryIdentifier,
  uint32 MemoryAddress,
  uint32 MemorySize,
  P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) MemoryData,
  Dcm_NegativeResponseCodePtrType ErrorCode
  );

/**********************************************************************************************************************
 *  Dcm_ProcessRequestTransferExit()
 *********************************************************************************************************************/
/*! \brief         Finalizes a software download sequence.
 *  \details        This call-out is used during software download processing, if RequestTransferExit is configured.
 *  \param[in]      OpStatus                             Operation status
 *  \param[in]      transferRequestParameterRecord       Request data
 *  \param[in]      transferRequestParameterRecordSize   Number of request data bytes
 *  \param[out]     transferResponseParameterRecord      Response data from the application
 *  \param[in,out]  transferResponseParameterRecordSize  Available buffer size, Number of written response data bytes
 *  \param[out]     ErrorCode                            Negative response code in case return value is DCM_E_NOT_OK
 *  \return         DCM_E_OK                             Request was successful
 *  \return         DCM_E_NOT_OK                         Request was not successful
 *  \return         DCM_E_PENDING                        Request is not yet finished
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    FALSE
 *  \config         This function is only available if DCM_FBLMGR_SUPPORT_ENABLED = STD_ON.
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_ProcessRequestTransferExit(
  Dcm_OpStatusType OpStatus,
  P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) transferRequestParameterRecord,
  uint32 transferRequestParameterRecordSize,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) transferResponseParameterRecord,
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) transferResponseParameterRecordSize,
  Dcm_NegativeResponseCodePtrType ErrorCode
  );
# endif /* (DCM_FBLMGR_SUPPORT_ENABLED == STD_ON) */
# if (DCM_AUTHMGR_SUPPORT_ENABLED == STD_ON)
#  if (DCM_AUTHMGR_SET_DEAUTH_ROLE_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_SetDeauthenticatedRole()
 *********************************************************************************************************************/
/*! \brief          Overwrites the configured deauthentication role of a connection of the given index.
 *  \details        The time between the function call and the update of the deauthenticated role depends on the
 *                  current DCM state. The minimum time to be expected is one DCM task cycle. If this service is called
 *                  while the DCM is processing a diagnostic request, the update will be postponed till the end of
 *                  this service processing, to avoid unpredictable behavior.
 *  \param[in]      connectionId           The connection identifier (not the connection handle)
 *  \param[in]      deauthenticatedRole    New deauthenticated role
 *  \return         E_OK is always returned
 *  \context        ISR1|ISR2|TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_SetDeauthenticatedRole(                                                                                           /* PRQA S 3449, 3451 */ /* MD_Dcm_8.5_Rte */
  uint16 connectionId,
  P2CONST(uint8, AUTOMATIC, RTE_DCM_APPL_DATA) deauthenticatedRole
  );
#  endif
# endif /* (DCM_AUTHMGR_SUPPORT_ENABLED == STD_ON) */
# if (DCM_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 *  Dcm_GetVersionInfo()
 *********************************************************************************************************************/
/*! \brief          Reports component's version information.
 *  \details        Returns the version information of the used DCM implementation.
 *  \param[out]     versioninfo    pointer to the application structure
 *  \context        ISR1|ISR2|TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         This function is only available if DCM_VERSION_INFO_API = STD_ON.
 *  \pre            -
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_GetVersionInfo(
  P2VAR(Std_VersionInfoType, AUTOMATIC, DCM_APPL_DATA) versioninfo
  );
# endif
/**********************************************************************************************************************
 *  Dcm_GetActiveProtocol()
 *********************************************************************************************************************/
/*! \brief          Returns the currently active protocol.
 *  \details        This function returns the active protocol Id.
 *  \param[out]     ActiveProtocol    Will contain the currently active protocol ID
 *  \return         DCM_E_OK          This value is always returned (also in error case)
 *  \context        ISR1|ISR2|TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_GetActiveProtocol(                                                                                                /* PRQA S 3449, 3451 */ /* MD_Dcm_8.5_Rte */
  P2VAR(Dcm_ProtocolType, AUTOMATIC, DCM_APPL_DATA) ActiveProtocol
  );

/**********************************************************************************************************************
 *  Dcm_GetTesterSourceAddress()
 *********************************************************************************************************************/
/*! \brief          Returns a DCM tester's SourceAddress.
 *  \details        Returns a DCM tester's SourceAddress for a given RxPduId.
 *  \param[in]      DcmRxPduId             The DCM RxPduId of the tester connection which SourceAddress will be read
 *  \param[out]     TesterSourceAddress    Will contain the corresponding tester's SourceAddress
 *  \return         DCM_E_OK               The TesterSourceAddress out parameter contains a valid value
 *  \return         DCM_E_NOT_OK           The TesterSourceAddress out parameter does not have a valid return value
 *  \context        ISR1|ISR2|TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_GetTesterSourceAddress(
  PduIdType DcmRxPduId,
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) TesterSourceAddress
  );

# if (DCM_DIAG_VIRTUAL_REQUEST_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_ProcessVirtualRequest()
 *********************************************************************************************************************/
/*! \brief          Provides a means for internal (ROE) requests triggered by the application.
 *  \details        -
 *  \param[in]      RxPduId            The RxPDUID of the request
 *  \param[in]      Data               The data of the request. In case of generic connections, tester source address
 *                                     stored in the last byte.
 *  \param[in]      Length             The length of the request
 *  \return         DCM_E_OK           Reception was successful
 *  \return         DCM_E_NOT_OK       Reception was not successful
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            DCM_DIAG_VIRTUAL_REQUEST_ENABLED == STD_ON
 *  \trace          CREQ-113929
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_ProcessVirtualRequest(
  PduIdType RxPduId,
  Dcm_MsgType Data,
  PduLengthType Length
  );
# endif

/**********************************************************************************************************************
 *  Dcm_SetActiveDiagnostic()
 *********************************************************************************************************************/
/*! \brief          Notifies DCM to (not) keep ComM channels awake.
 *  \details        -
 *  \param[in]      active             The new DCM ComM interaction mode
 *  \return         DCM_E_OK           This value is always returned (also in error case)
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_SetActiveDiagnostic(                                                                                              /* PRQA S 3449, 3451 */ /* MD_Dcm_8.5_Rte */
  boolean active
  );

/**********************************************************************************************************************
 *  Dcm_GetRequestKind()
 *********************************************************************************************************************/
/*! \brief          Returns the request kind of a DCM tester SourceAddress.
 *  \details        Returns the request kind for a given diagnostic client.
 *  \param[in]      TesterSourceAddress    Will contain the corresponding tester's SourceAddress
 *  \param[out]     RequestKind            The request kind ([DCM_REQ_KIND]_NONE, _EXTERNAL and _ROE)
 *  \return         DCM_E_OK               The RequestKind out parameter contains a valid value
 *  \return         DCM_E_NOT_OK           The RequestKind out parameter does not have a valid return value
 *  \context        ISR1|ISR2|TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_GetRequestKind(                                                                                                   /* PRQA S 3449, 3451 */ /* MD_Dcm_8.5_Rte */
  uint16 TesterSourceAddress,
  P2VAR(Dcm_RequestKindType, AUTOMATIC, DCM_APPL_DATA) RequestKind
  );
/**********************************************************************************************************************
 *  Dcm_ResetToDefaultSession()
 *********************************************************************************************************************/
/*! \brief          Provides a means for enforced resetting to the default session.
 *  \details        The call to this function allows the application to reset the current session to Default session.
 *                  Example: Automatic termination of an extended diagnostic session upon exceeding of a speed limit.
 *                  Note: The time between the function call and the termination of the session depends on the current
 *                        DCM state. The minimum time to be expected is one DCM task cycle. If this service is called
 *                        while the DCM is processing a diagnostic request, the session termination will be postponed
 *                        till the end of this service processing, to avoid unpredictable behavior.
 *  \return         E_OK    This value is always returned (also in error case)
 *  \context        ISR1|ISR2|TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_ResetToDefaultSession(                                                                                            /* PRQA S 3449, 3451 */ /* MD_Dcm_8.5_Rte */
  void
  );

/**********************************************************************************************************************
 *  Dcm_GetSesCtrlType()
 *********************************************************************************************************************/
/*! \brief          Provides read access to the DCM's diagnostic session register.
 *  \details        This function provides the active session control type value.
 *  \param[out]     SesCtrlType    Pointer to a RAM address where DCM will store the current session
 *  \return         E_OK           This value is always returned (also in error case)
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *  \trace          CREQ-113936
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_GetSesCtrlType(                                                                                                   /* PRQA S 3449, 3451 */ /* MD_Dcm_8.5_Rte */
  P2VAR(Dcm_SesCtrlType, AUTOMATIC, DCM_APPL_DATA) SesCtrlType
  );

# if (DCM_STATE_SECURITY_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_GetSecurityLevel()
 *********************************************************************************************************************/
/*! \brief          Provides read access to the DCM's security access register.
 *  \details        This function provides the active security level value.
 *  \param[out]     SecLevel    Pointer to a RAM address where DCM will store the current security level
 *  \return         E_OK        This value is always returned (also in error case)
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         This function is only available if DCM_STATE_SECURITY_ENABLED = STD_ON.
 *  \pre            -
 *  \trace          CREQ-113940
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_GetSecurityLevel(                                                                                                 /* PRQA S 3449, 3451 */ /* MD_Dcm_8.5_Rte */
  P2VAR(Dcm_SecLevelType, AUTOMATIC, DCM_APPL_DATA) SecLevel
  );
# endif

# if (DCM_STATE_SECURITY_EXT_SETTER_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_SetSecurityLevel()
 *********************************************************************************************************************/
/*! \brief          Provides write access to the DCM's security access register.
 *  \details        This function performs security level transition.
 *  \param[in]      SecLevel    The new security level to switch into
 *  \return         E_OK        State change has been performed.
 *  \return         E_NOT_OK    State change failed. Possible reasons:
 *                              - wrong/invalid security level;
 *                              - called while DCM is busy with a diagnostic request;
 *                              - called from wrong task context (not from Dcm_MainFunctionWorker);
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         This function is only available if DCM_STATE_SECURITY_EXT_SETTER_ENABLED = STD_ON.
 *  \pre            -
 *  \trace          CREQ-129518
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_SetSecurityLevel(
  Dcm_SecLevelType SecLevel
  );
# endif

# if (DCM_STATE_SECURITY_FIXED_BYTES_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_GetSecurityLevelFixedBytes()
 *********************************************************************************************************************/
/*! \brief          Provides fixed bytes set up for a specific security level.
 *  \details        This function provides the fixed bytes for the requested security level.
 *                  A security level without configured fixed bytes will return E_OK and no bytes (bufferSize = 0)
 *  \param[in]      SecLevel              The requested security level
 *  \param[out]     FixedBytes            Buffer to receive the fixed byte values
 *  \param[in,out]  BufferSize
 *                  IN                    The provided buffer size
 *                  OUT                   The number of fixed bytes for the requested level
 *  \return         E_OK                  The security bytes were copied to the provided buffer
 *  \return         DCM_E_NOT_OK          The security level is not configured
 *  \return         DCM_E_BUFFERTOOLOW    The buffer was too small, BufferSize will contain the number of bytes needed
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         This function is only available if DCM_STATE_SECURITY_FIXED_BYTES_ENABLED = STD_ON
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_GetSecurityLevelFixedBytes(                                                                                       /* PRQA S 3449, 3451 */ /* MD_Dcm_8.5_Rte */
  Dcm_SecLevelType SecLevel,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) FixedBytes,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) BufferSize
  );
# endif

# if (DCM_STATE_SECURITY_BYPASS_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_SetSecurityBypass()
 *********************************************************************************************************************/
/*! \brief          Enables a bypass to security states of Dcm.
 *  \details        The call to this function allows the application to bypass the internal DCM security states.
 *  \param[in]      SecBypass       The new bypass mode.
 *  \return         DCM_E_OK        Security bypass mode has been performed.
 *  \return         DCM_E_NOT_OK    Some error has occurred. Possible reasons:
 *                                  - DCM is not yet initialized;
 *                                  - Wrong/invalid SecBypass parameter;
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         This function is only available if DCM_STATE_SECURITY_BYPASS_ENABLED = STD_ON.
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_SetSecurityBypass(                                                                                                /* PRQA S 3449, 3451 */ /* MD_Dcm_8.5_Rte */
  boolean SecBypass
  );
# endif
# if (DCM_DIDMGR_SUPPORT_ENABLED == STD_ON)
#  if (DCM_DIDMGR_EXTENDED_LOOKUP_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_FilterDidLookUpResult()
 *********************************************************************************************************************/
/*! \brief          Provides a means to get supported DID suppressed by the application.
 *  \details        -
 *  \param[in]      OpStatus                Current operation status.
 *  \param[in]      Did                     The requested DID the filtering shall be done.
 *  \param[in]      DidOperation            The requested DID operation the filtering shall be done.
 *  \return         DCM_E_OK                The DID is (still) active.
 *  \return         DCM_E_PENDING           The DID validation needs more time. Call me again.
 *  \return         DCM_E_NOT_OK            The DID is not active.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    FALSE
 *  \config         This function is only available if DCM_DIDMGR_EXTENDED_LOOKUP_ENABLED = STD_ON.
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_FilterDidLookUpResult(
  Dcm_OpStatusType OpStatus,
  uint16 Did,
  Dcm_DidOpType DidOperation
  );
#  endif
# endif /* (DCM_DIDMGR_SUPPORT_ENABLED == STD_ON) */
# if (DCM_RIDMGR_SUPPORT_ENABLED == STD_ON)
#  if (DCM_RIDMGR_EXTENDED_LOOKUP_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_FilterRidLookUpResult()
 *********************************************************************************************************************/
/*! \brief          Provides a means to get supported RID suppressed by the application.
 *  \details        -
 *  \param[in]      OpStatus                Current operation status.
 *  \param[in]      Rid                     The requested RID the filtering shall be done.
 *  \return         DCM_E_OK                The RID is (still) active.
 *  \return         DCM_E_PENDING           The RID validation needs more time. Call me again.
 *  \return         DCM_E_NOT_OK            The RID is not active.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    FALSE
 *  \config         This function is only available if DCM_RIDMGR_EXTENDED_LOOKUP_ENABLED = STD_ON.
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_FilterRidLookUpResult(
  Dcm_OpStatusType OpStatus,
  uint16 Rid
  );
#  endif
# endif /* (DCM_RIDMGR_SUPPORT_ENABLED == STD_ON) */
/**********************************************************************************************************************
 *  Dcm_Init()
 *********************************************************************************************************************/
/*! \brief          Modules initialization.
 *  \details        Service for basic initialization of DCM module.
 *                  In all cases where this API does expect a non-null pointer argument, a validation of the passed
 *                  argument is performed.
 *  \param[in]      configPtr    Pointer to a concrete configuration root - not used for now
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            Global interrupts shall be disabled.
 *  \trace          CREQ-113863
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_Init(
  Dcm_ConfigPtrType configPtr
  );

/**********************************************************************************************************************
 *  Dcm_InitMemory()
 *********************************************************************************************************************/
/*! \brief          Initialization function.
 *  \details        Module's memory initialization.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            Global interrupts shall be disabled. If used, then always prior calling Dcm_Init.
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_InitMemory(
  void
  );

# if (DCM_SPLIT_TASKS_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_MainFunctionTimer()
 *********************************************************************************************************************/
/*! \brief          Modules main timing scheduling.
 *  \details        This service is used for time critical tasks (high priority task).
 *                  Function will be called at high level task only for better timing accuracy.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         This function is only available if DCM_SPLIT_TASKS_ENABLED = STD_ON.
 *  \pre            -
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_MainFunctionTimer(                                                                                                          /* PRQA S 3449, 3451 */ /* MD_Dcm_8.5_Rte */
  void
  );
# endif

# if (DCM_SPLIT_TASKS_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_MainFunctionWorker()
 *********************************************************************************************************************/
/*! \brief          Modules main processing task.
 *  \details        This service is used for diagnostic service processing (low priority task).
 *                  Function will be called at low level task only, to allow long service execution times.
 *                  Note: All application call outs the DCM executes are performed only from within this task.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         This function is only available if DCM_SPLIT_TASKS_ENABLED = STD_ON.
 *  \pre            -
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_MainFunctionWorker(                                                                                                         /* PRQA S 3449, 3451 */ /* MD_Dcm_8.5_Rte */
  void
  );
# endif

# if (DCM_SPLIT_TASKS_ENABLED == STD_OFF)
/**********************************************************************************************************************
 *  Dcm_MainFunction()
 *********************************************************************************************************************/
/*! \brief          Modules main run-time scheduling.
 *  \details        This service is used for processing the tasks of the main loop.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         This function is only available if DCM_SPLIT_TASKS_ENABLED = STD_OFF.
 *  \pre            -
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_MainFunction(                                                                                                               /* PRQA S 3449, 3451 */ /* MD_Dcm_8.5_Rte */
  void
  );
# endif
/* --- Diagnostic service processing management -------------------------------------------------------------------- */
/**********************************************************************************************************************
 *  Dcm_ExternalProcessingDone()
 *********************************************************************************************************************/
/*! \brief          Finalizes the service processing task.
 *  \details        -
 *  \param[in,out]  pMsgContext  Current request context
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_ExternalProcessingDone(
  Dcm_MsgContextPtrType pMsgContext
  );

/**********************************************************************************************************************
 *  Dcm_ExternalSetNegResponse()
 *********************************************************************************************************************/
/*! \brief          Registers a NRC to the request in progress.
 *  \details        Only the very first registered NRC will be stored. Any further call of this API within the same
 *                  diagnostic request will have no effect.
 *  \param[in,out]  pMsgContext  Current request context
 *  \param[in]      errorCode    The error code to be registered
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_ExternalSetNegResponse(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodeType errorCode
  );

# if (DCM_DIAG_STATE_RECOVERY_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_ProvideRecoveryStates()
 *********************************************************************************************************************/
/*! \brief          Returns the internal Dcm state.
 *  \details        This function can be used to gather the internal DCM states to be able to recover them after reset.
 *                  It shall be called by DCM application just before performing the reset operation.
 *  \param[out]     RecoveryInfo    Parameter to be written by the DCM with all the information to be recovered.
 *  \return         DCM_E_OK        Result is valid and shall be processed
 *  \return         DCM_E_NOT_OK    Some error has occurred e.g. DCM is not yet initialized
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         This function is only available if DCM_DIAG_STATE_RECOVERY_ENABLED = STD_ON
 *  \pre            Once this API is called, the states may change due to external events (e.g. session timeout).
 *                  Therefore always perform this call right before executing the reset.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_ProvideRecoveryStates(
  P2VAR(Dcm_RecoveryInfoType, AUTOMATIC, DCM_APPL_DATA) RecoveryInfo
  );
# endif

# if (DCM_DIAG_SPECIFIC_CAUSE_CODE_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_SetSpecificCauseCode()
 *********************************************************************************************************************/
/*! \brief          Registers a specific cause code to the request in progress.
 *  \details        Only the very first registered specific cause code will be stored. Any further call of this API
 *                  within the same diagnostic request will have no effect.
 *  \param[in]      specificCauseCode    The specific cause code to be registered
 *  \return         DCM_E_OK             Operation succeded. In case of first call, specific cause code is registered.
 *  \return         DCM_E_NOT_OK         Some error has occurred e.g. DCM is not yet initialized
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         This function is only available if DCM_DIAG_SPECIFIC_CAUSE_CODE_ENABLED = STD_ON
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_SetSpecificCauseCode(                                                                                             /* PRQA S 3449, 3451 */ /* MD_Dcm_8.5_Rte */
  Dcm_SpecificCauseCodeType specificCauseCode
  );
# endif
# if (DCM_VARMGR_MULTI_SVC_INCLUSIVE_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_VsgSetSingle()
 *********************************************************************************************************************/
/*! \brief          Sets the status of a single VSG.
 *  \details        -
 *  \param[in]      VsgId         Unique handle of the VSG.
 *  \param[in]      State         DCM_VSG_ENABLED:  Set VSG to active
 *                                DCM_VSG_DISABLED: Set VSG to inactive
 *  \return         DCM_E_OK      New status is set succesfully
 *  \return         DCM_E_NOT_OK  Operation failed
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         This function is only available if DCM_VARMGR_MULTI_SVC_INCLUSIVE_ENABLED = STD_ON.
*********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_VsgSetSingle(                                                                                                     /* PRQA S 3449, 3451 */ /* MD_Dcm_8.5_Rte */
  Dcm_VsgIdentifierType VsgId,
  Dcm_VsgStateType State
  );
# endif

# if (DCM_VARMGR_MULTI_SVC_INCLUSIVE_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_VsgIsActive()
 *********************************************************************************************************************/
/*! \brief          Returns status of a single VSG.
 *  \details        -
 *  \param[in]      VsgId         Unique handle of the VSG.
 *  \param[out]     State         DCM_VSG_ENABLED:  VSG is active
 *                                DCM_VSG_DISABLED: VSG is inactive
 *  \return         DCM_E_OK      Operation succeeded, parameter isActive contains status of VSG
 *  \return         DCM_E_NOT_OK  Operation failed
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         This function is only available if DCM_VARMGR_MULTI_SVC_INCLUSIVE_ENABLED = STD_ON.
*********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_VsgIsActive(                                                                                                      /* PRQA S 3449, 3451 */ /* MD_Dcm_8.5_Rte */
  Dcm_VsgIdentifierType VsgId,
  P2VAR(Dcm_VsgStateType, AUTOMATIC, DCM_APPL_DATA) State
  );
# endif

# if (DCM_VARMGR_MULTI_SVC_INCLUSIVE_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_VsgSetMultiple()
 *********************************************************************************************************************/
/*! \brief          Sets the status of a set of VSGs.
 *  \details        -
 *  \param[in]      VsgIdList     List of VsgIds to be set
 *  \param[in]      VsgListSize   Number of VSGs
 *  \param[in]      State         DCM_VSG_ENABLED:  Set VSGs to active
 *                                DCM_VSG_DISABLED: Set VSGs to inactive
 *  \return         DCM_E_OK      New status is set succesfully
 *  \return         DCM_E_NOT_OK  Operation failed
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         This function is only available if DCM_VARMGR_MULTI_SVC_INCLUSIVE_ENABLED = STD_ON.
*********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_VsgSetMultiple(                                                                                                   /* PRQA S 3449, 3451 */ /* MD_Dcm_8.5_Rte */
  P2CONST(Dcm_VsgIdentifierType, AUTOMATIC, DCM_APPL_DATA) VsgIdList,
  uint16 VsgListSize,
  Dcm_VsgStateType State
  );
# endif

# if (DCM_VARMGR_MULTI_SVC_INCLUSIVE_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_VsgIsActiveAnyOf()
 *********************************************************************************************************************/
/*! \brief          Checks if at least one of the passed VSGs is active.
 *  \details        -
 *  \param[in]      VsgIdList     List of VsgIds to be set
 *  \param[in]      VsgListSize   Number of VSGs
 *  \param[out]     State         DCM_VSG_ENABLED:  At least one VSG is active
 *                                DCM_VSG_DISABLED: All VSGs are inactive
 *  \return         DCM_E_OK      Operation is executed successfully
 *  \return         DCM_E_NOT_OK  Operation failed
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         This function is only available if DCM_VARMGR_MULTI_SVC_INCLUSIVE_ENABLED = STD_ON.
*********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_VsgIsActiveAnyOf(                                                                                                 /* PRQA S 3449, 3451 */ /* MD_Dcm_8.5_Rte */
  P2CONST(Dcm_VsgIdentifierType, AUTOMATIC, DCM_APPL_DATA) VsgIdList,
  uint16 VsgListSize,
  P2VAR(Dcm_VsgStateType, AUTOMATIC, DCM_APPL_DATA) State
  );
# endif
# define DCM_STOP_SEC_CODE
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */

# define DCM_START_SEC_CALLOUT_CODE
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */
# if (DCM_MEMMGR_SUPPORT_ENABLED == STD_ON)
#  if (DCM_MEMMGR_MEMOP_WRITE_ENABLED == STD_ON)
#   if (DCM_DCM_AR_VERSION >= DCM_DCM_AR_VERSION_422)
/**********************************************************************************************************************
  Dcm_WriteMemory()
 *********************************************************************************************************************/
/*! \brief          Call-out to write to memory.
 *  \details        The Dcm_WriteMemory call-out is used to write memory data identified by the parameter memoryAddress
 *                  and memorySize.
 *                  This service is needed for the implementation of UDS services:
 *                      - WriteMemoryByAdress
 *                      - RequestDownload
 *  \param[in]      OpStatus                Operation status
 *  \param[in]      MemoryIdentifier        Identifier of the Memory Block
 *  \param[in]      MemoryAddress           Starting address of server memory from which data is to be written.
 *  \param[in]      MemorySize              Number of bytes in the MemoryData
 *  \param[in]      MemoryData              Data to be written (points to the diagnostic buffer in DCM).
 *  \param[out]     ErrorCode               If the operation Dcm_WriteMemory returns value
 *                                          DCM_WRITE_FAILED, the Dcm module shall
 *                                          send a negative response with NRC code equal to
 *                                          the parameter ErrorCode parameter value
 *  \return         DCM_WRITE_OK            Write was successful
 *  \return         DCM_WRITE_FAILED        Write was not successful
 *  \return         DCM_WRITE_PENDING       Write is not yet finished
 *  \return         DCM_WRITE_FORCE_RCRRP   Enforce RCR-RP transmission (vendor extension)
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    FALSE
 *  \config         This function is only available if DCM_MEMMGR_MEMOP_WRITE_ENABLED = STD_ON.
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Dcm_ReturnWriteMemoryType, DCM_CALLOUT_CODE) Dcm_WriteMemory(
  Dcm_OpStatusType OpStatus,
  uint8 MemoryIdentifier,
  uint32 MemoryAddress,
  uint32 MemorySize,
  Dcm_MsgType MemoryData,
  Dcm_NegativeResponseCodePtrType ErrorCode
  );
#   else
/**********************************************************************************************************************
  Dcm_WriteMemory()
 *********************************************************************************************************************/
/*! \brief          Call-out to write to memory.
 *  \details        The Dcm_WriteMemory call-out is used to write memory data identified by the parameter memoryAddress
 *                  and memorySize.
 *                  This service is needed for the implementation of UDS services:
 *                      - WriteMemoryByAdress
 *                      - RequestDownload
 *  \param[in]      OpStatus                Operation status
 *  \param[in]      MemoryIdentifier        Identifier of the Memory Block
 *  \param[in]      MemoryAddress           Starting address of server memory from which data is to be written.
 *  \param[in]      MemorySize              Number of bytes in the MemoryData
 *  \param[in]      MemoryData              Data to be written (points to the diagnostic buffer in DCM).
 *  \return         DCM_WRITE_OK            Write was successful
 *  \return         DCM_WRITE_FAILED        Write was not successful
 *  \return         DCM_WRITE_PENDING       Write is not yet finished
 *  \return         DCM_WRITE_FORCE_RCRRP   Enforce RCR-RP transmission (vendor extension)
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    FALSE
 *  \config         This function is only available if DCM_MEMMGR_MEMOP_WRITE_ENABLED = STD_ON.
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Dcm_ReturnWriteMemoryType, DCM_CALLOUT_CODE) Dcm_WriteMemory(
  Dcm_OpStatusType OpStatus,
  uint8 MemoryIdentifier,
  uint32 MemoryAddress,
  uint32 MemorySize,
  Dcm_MsgType MemoryData
  );
#   endif
#  endif

#  if (DCM_MEMMGR_MEMOP_READ_ENABLED == STD_ON)
#   if (DCM_DCM_AR_VERSION >= DCM_DCM_AR_VERSION_422)
/**********************************************************************************************************************
 *  Dcm_ReadMemory()
 *********************************************************************************************************************/
/*! \brief          Call-out to read from memory.
 *  \details        The Dcm_ReadMemory call-out is used to request memory data identified by the parameter
 *                  memoryAddress and memorySize from the UDS request message. This service is needed for the
 *                  implementation of UDS services:
 *                      - ReadMemoryByAdress
 *                      - RequestUpload
 *                      - ReadDataByIdentifier (in case of Dynamical DID defined by memory address)
 *  \param[in]      OpStatus                Operation status
 *  \param[in]      MemoryIdentifier        Identifier of the Memory Block
 *  \param[in]      MemoryAddress           Starting address of server memory from which data is to be retrieved
 *  \param[in]      MemorySize              Number of bytes in the MemoryData
 *  \param[out]     MemoryData              Data read (points to the diagnostic buffer in DCM)
 *  \param[out]     ErrorCode               If the operation Dcm_ReadMemory returns value
 *                                          DCM_READ_FAILED, the Dcm module shall send
 *                                          a negative response with NRC code equal to the
 *                                          parameter ErrorCode parameter value
 *  \return         DCM_READ_OK             Read was successful
 *  \return         DCM_READ_FAILED         Read was not successful
 *  \return         DCM_READ_PENDING        Read is not yet finished
 *  \return         DCM_READ_FORCE_RCRRP    Enforce RCR-RP transmission (vendor extension)
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    FALSE
 *  \config         This function is only available if DCM_MEMMGR_MEMOP_READ_ENABLED = STD_ON.
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Dcm_ReturnReadMemoryType, DCM_CALLOUT_CODE) Dcm_ReadMemory(
  Dcm_OpStatusType OpStatus,
  uint8 MemoryIdentifier,
  uint32 MemoryAddress,
  uint32 MemorySize,
  Dcm_MsgType MemoryData,
  Dcm_NegativeResponseCodePtrType ErrorCode
  );
#   else
/**********************************************************************************************************************
 *  Dcm_ReadMemory()
 *********************************************************************************************************************/
/*! \brief          Call-out to read from memory.
 *  \details        The Dcm_ReadMemory call-out is used to request memory data identified by the parameter
 *                  memoryAddress and memorySize from the UDS request message. This service is needed for the
 *                  implementation of UDS services:
 *                      - ReadMemoryByAdress
 *                      - RequestUpload
 *                      - ReadDataByIdentifier (in case of Dynamical DID defined by memory address)
 *  \param[in]      OpStatus                Operation status
 *  \param[in]      MemoryIdentifier        Identifier of the Memory Block
 *  \param[in]      MemoryAddress           Starting address of server memory from which data is to be retrieved
 *  \param[in]      MemorySize              Number of bytes in the MemoryData
 *  \param[out]     MemoryData              Data read (points to the diagnostic buffer in DCM)
 *  \return         DCM_READ_OK             Read was successful
 *  \return         DCM_READ_FAILED         Read was not successful
 *  \return         DCM_READ_PENDING        Read is not yet finished
 *  \return         DCM_READ_FORCE_RCRRP    Enforce RCR-RP transmission (vendor extension)
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    FALSE
 *  \config         This function is only available if DCM_MEMMGR_MEMOP_READ_ENABLED = STD_ON.
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Dcm_ReturnReadMemoryType, DCM_CALLOUT_CODE) Dcm_ReadMemory(
  Dcm_OpStatusType OpStatus,
  uint8 MemoryIdentifier,
  uint32 MemoryAddress,
  uint32 MemorySize,
  Dcm_MsgType MemoryData
  );
#   endif
#  endif
# endif /* (DCM_MEMMGR_SUPPORT_ENABLED == STD_ON) */
/**********************************************************************************************************************
 *  Dcm_Confirmation()
 *********************************************************************************************************************/
/*! \brief          Confirms the diagnostic job finalization.
 *  \details        This function confirms the successful transmission or a transmission error of a diagnostic
 *                  service. The idContext and the dcmRxPduId are required to identify the message which was processed.
 *                  If there was no response for this request, this call out is invoked at service processing finish.
 *                  Note: This call out is invoked only then when a DCM internal or external
 *                        <Module>_<DiagnosticService> service handler has been executed.
 *  \param[in]      idContext     Current context identifier which can be used to retrieve the relation between
 *                                request and confirmation. Within the confirmation, the Dcm_MsgContext is no more
 *                                available, so the idContext can be used to represent this relation.
 *                                The idContext is also part of the Dcm_MsgContext
 *  \param[in]      dcmRxPduId    DcmRxPduId on which the request was received. The source of the request
 *                                can have consequences for message processing.
 *  \param[in]      status        Status indication about confirmation
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(void, DCM_CALLOUT_CODE) Dcm_Confirmation(
  Dcm_IdContextType idContext,
  PduIdType dcmRxPduId,
  Dcm_ConfirmationStatusType status
  );

# if (DCM_DIAG_JUMPTOFBL_ENABLED   == STD_ON) || \
     (DCM_DIAG_JUMPFROMFBL_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_SetProgConditions()
 *********************************************************************************************************************/
/*! \brief          Sets the programming conditions.
 *  \details        The Dcm_SetProgConditions call-out allows the integrator to store relevant information prior
 *                  jumping to boot loader. The context parameters are defined in Dcm_ProgConditionsType.
 *  \param[in]      progConditions    Conditions on which the jump to boot loader has been requested.
 *  \return         E_OK              Conditions have correctly been set
 *  \return         E_NOT_OK          Conditions cannot be set
 *  \return         DCM_E_PENDING     Conditions set is in progress, a further call to this API is needed to end the
                                      setting
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         This function is only available if (DCM_DIAG_JUMPTOFBL_ENABLED = STD_ON) ||
 *                  (DCM_DIAG_JUMPFROMFBL_ENABLED = STD_ON).
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_SetProgConditions(
  Dcm_ProgConditionsPtrType progConditions
  );
# endif

# if (DCM_DIAG_JUMPFROMFBL_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_GetProgConditions()
 *********************************************************************************************************************/
/*! \brief          Returns the programming conditions.
 *  \details        The Dcm_GetProgConditions call-out is called upon DCM initialization and allows determining if a
 *                  response (0x50 or 0x51) has to be sent depending on request within the boot-loader.
 *                  The context parameters are defined in Dcm_ProgConditionsType.
 *  \param[in]      progConditions    Conditions on which the jump from the boot-loader has been requested.
 *  \return         DCM_COLD_START    The ECU starts normally
 *  \return         DCM_WARM_START    The ECU starts from a boot-loader jump
 *                                    The function parameter values will be evaluated for further processing.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         This function is only available if DCM_DIAG_JUMPFROMFBL_ENABLED = STD_ON.
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Dcm_EcuStartModeType, DCM_CALLOUT_CODE) Dcm_GetProgConditions(
  Dcm_ProgConditionsPtrType progConditions
  );
# endif

# if (DCM_DIAG_STATE_RECOVERY_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_GetRecoveryStates()
 *********************************************************************************************************************/
/*! \brief          Collects the external stored internal Dcm state.
 *  \details        The Dcm_GetRecoveryStates() call-out is called upon DCM initialization and allows to restore the
 *                  previously via Dcm_ProvideRecoveryStates() stored internal Dcm state.
 *  \param[out]     RecoveryInfo     Parameter to be written by the DCM with all the information to be recovered.
 *  \return         DCM_E_OK         Result is valid and shall be processed
 *  \return         DCM_E_PENDING    Result is pending (e.g. NvM not yet ready)
 *  \return         DCM_E_NOT_OK     No information to be recovered or result reading failed
 *                                   DCM shall continue with the default initialized states.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    FALSE
 *  \config         This function is only available if DCM_DIAG_STATE_RECOVERY_ENABLED = STD_ON
 *  \pre            Once this API is called, DCM will lock any external connection until the result is processed.
 *                  This is required in order to be able to switch into a consistent state without any influence from
 *                  outside.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_GetRecoveryStates(
  P2VAR(Dcm_RecoveryInfoType, AUTOMATIC, DCM_VAR_NOINIT) RecoveryInfo
  );
# endif

# if (DCM_DIAG_SERVICE_DISPATCHER_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_HandleServiceExtern()
 *********************************************************************************************************************/
/*! \brief         Returns the service implementation type for dispatching.
 *  \details        This call-out is used during service request processing, if the service is configured to be
 *                  dispatchable.
 *                  Note: This call-out is only invoked, if a DCM service handler has been configured accordingly.
 *  \param[in]      SID                   The service identifier of the request
 *  \param[in]      RequestData           The request data (behind SID byte)
 *  \param[in]      DataSize              The request data length
 *  \param[in]      ReqType               The request type (0 - physical, 1- functional)
 *  \param[in]      SourceAddress         The tester source address
 *  \return         TRUE              The service processing is done by the application
 *  \return         FALSE             The service processing is done by DCM
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         This function is only available if DCM_DIAG_SERVICE_DISPATCHER_ENABLED = STD_ON.
 *  \pre            -
 *********************************************************************************************************************/
FUNC(boolean, DCM_CALLOUT_CODE) Dcm_HandleServiceExtern(
  uint8 SID,
  Dcm_ReadOnlyMsgType RequestData,
  uint16 DataSize,
  uint8 ReqType,
  uint16 SourceAddress
  );
# endif
# define DCM_STOP_SEC_CALLOUT_CODE
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL DATA DECLARATIONS
 *********************************************************************************************************************/
# define DCM_START_SEC_VAR_NO_INIT_UNSPECIFIED
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */
# if (DCM_AUTHMGR_SUPPORT_ENABLED == STD_ON)
/*! Authentication manager data that can be read from and written to NvM (if NvM is configured) */
extern VAR(Dcm_AuthMgrNvMDataType, DCM_VAR_NOINIT) Dcm_AuthMgrNvMData[DCM_CFGAUTHMGRNETCONNINFO_SIZE];
# endif /* (DCM_AUTHMGR_SUPPORT_ENABLED == STD_ON) */
# if (DCM_SVC_2C_SUPPORT_ENABLED == STD_ON)
/*! Service 0x2C Data that can be read from and written to NvM (if NvM is configured) */
extern VAR(Dcm_Svc2CDynDidNvMDataType, DCM_VAR_NOINIT) Dcm_Svc2CNvMData;
# endif /* (DCM_SVC_2C_SUPPORT_ENABLED == STD_ON) */
# define DCM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  SILENTBSW JUSTIFICATIONS
 *********************************************************************************************************************/
/*!
 * \exclusivearea DCM_EXCLUSIVE_AREA_0
 *                Ensures consistency of the Dcm global state variables.
 *
 * \protects      Dcm_PbRamNetConnHdl2TObjMap,
 *                Dcm_PbRamNetTransportObject,
 *                Dcm_PbRamNetBufferContext,
 *                Dcm_PbRamNetComMContext,
 *                Dcm_PbRamNetPeriodicTxObject[].Timer,
 *                Dcm_PbRamNetPeriodicTxObject[].State,
 *                Dcm_ThreadContext[].Diag.QueuedSet,
 *                Dcm_ThreadContext[].PagedBuffer.ReadIndex,
 *                Dcm_ThreadContext[].PagedBuffer.WriteIndex,
 *                Dcm_ThreadContext[].PagedBuffer.RemainingLen,
 *                Dcm_ThreadContext[].Diag.TObjHdl,
 *                Dcm_ThreadContext[].Diag.MsgContext.msgAddInfo.suppressPosResponse,
 *                Dcm_SingletonContext.Network.NumActiveConnections,
 *                Dcm_SingletonContext.TaskMgr.TaskContext,
 *                Dcm_SingletonContext.TimerMgr.Timer,
 *                Dcm_SingletonContext.Network.ActiveDiagnostic,
 *                Dcm_SingletonContext.TaskMgr.CurrentTaskPrioStack,
 *                Dcm_SingletonContext.TaskMgr.TaskScheduler[].SchdIsActive,
 *                Dcm_SingletonContext.StateMgr.Preconditions.Session,
 *                Dcm_SingletonContext.Diag.Services.Svc27.DelayTime[],
 *                Dcm_SingletonContext.Diag.Services.Svc27.SetAttCntrEventMask,
 *                Dcm_SingletonContext.Diag.Services.Svc2A.Scheduler.Table[].Rate,
 *                Dcm_SingletonContext.Diag.Services.Svc2A.Scheduler.Table[].Timer,
 *                Dcm_SingletonContext.Diag.Services.Svc2A.Scheduler.NumActiveEntries
 *                Dcm_SingletonContext.Diag.Services.Svc29.CbkProcessingState
 *                Dcm_SingletonContext.AuthMgr.PendingData
 *                Dcm_SingletonContext.AuthMgr.DelayTime[]
 *                Dcm_SingletonContext.AuthMgr.TimerExpiredMask
 *                Dcm_Svc86CurrentSession.EventRecord.DtcRecord
 *
 * \usedin        Dcm_ComM_FullComModeEntered,
 *                Dcm_ComM_NoComModeEntered,
 *                Dcm_ComM_SilentComModeEntered,
 *                Dcm_DiagFblResDoProcessTxConfirmation,
 *                Dcm_DiagHandleSuppressBit,
 *                Dcm_DiagRxIndication,
 *                Dcm_DiagSetP2Timings,
 *                Dcm_DiagSwitchProcessingContext,
 *                Dcm_DiagTaskGarbageCollector,
 *                Dcm_DiagTxFinalization,
 *                Dcm_DiagWorkerDoCancelProcessing_CancelOpen,
 *                Dcm_DiagWorkerDoCancelProcessing_ReviveKilledTasks,
 *                Dcm_DiagWorkerDoRepeat,
 *                Dcm_GetRequestKind,
 *                Dcm_NetLockConnection,
 *                Dcm_NetOnRequestDetection,
 *                Dcm_NetProvideRxBuffer,
 *                Dcm_NetRegisterActiveConnection,
 *                Dcm_NetRegisterComMActivity,
 *                Dcm_NetRxIndInternal,
 *                Dcm_NetSetComModeEntered,
 *                Dcm_NetStartOfReception,
 *                Dcm_NetTaskTaMonitor,
 *                Dcm_NetUnRegisterActiveConnection,
 *                Dcm_NetUnRegisterAllComMActivity,
 *                Dcm_NetUnRegisterComMActivity,
 *                Dcm_OnTimeoutPeriodicTx,
 *                Dcm_PagedBufferDefragmentPage,
 *                Dcm_PagedBufferTask,
 *                Dcm_PagedBufferUpdatePage,
 *                Dcm_Service10PostProcessor,
 *                Dcm_SetActiveDiagnostic,
 *                Dcm_SetSecurityLevel,
 *                Dcm_StateSetSession,
 *                Dcm_Svc10_WaitForResetAck,
 *                Dcm_Svc27TimerSet,
 *                Dcm_Svc27UtiSetAttemptCntr,
 *                Dcm_Svc2ASchdCommit,
 *                Dcm_TmrSetTimerByThread,
 *                Dcm_TmrStartTimerByThread,
 *                Dcm_TmrStopTimerByThread,
 *                Dcm_TmrResumeTimerByThread,
 *                Dcm_TmrTaskTimer,
 *                Dcm_TskClrEvent,
 *                Dcm_TskKillAllTasks,
 *                Dcm_TskRegisterActiveTask,
 *                Dcm_TskSetEvent,
 *                Dcm_TskUnRegisterActiveTask,
 *                Dcm_NetPTxObjTimerSet,
 *                Dcm_Svc10CheckAccess,
 *                Dcm_KeyMAsyncCertificateVerifyFinished,
 *                Dcm_CsmAsyncJobFinished,
 *                Dcm_Svc29CancelOperation,
 *                Dcm_SetDeauthenticatedRole,
 *                Dcm_AuthMgrSetDeauthenticatedRole
 *                Dcm_OnTimeoutAuthentication
 *                Dcm_AuthMgrDeauthenticateIdleConn
 *                Dcm_DemTriggerOnDTCStatus
 *                Dcm_MainFunctionWorker
 *
 * \exclude       Dcm_NetStartOfReception, Dcm_MainFunction, Dcm_MainFunctionTimer, Dcm_MainFunctionWorker, Dcm_DemTriggerOnDTCStatus
 * \length        MEDIUM Typically the exclusive area is short, but there are cases, where function calls are performed.
 * \endexclusivearea
 */
#endif /* !defined(DCM_CORE_H) */

/**********************************************************************************************************************
 *  END OF FILE: Dcm_Core.h
 *********************************************************************************************************************/
