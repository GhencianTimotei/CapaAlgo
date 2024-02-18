/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *
 *                 This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                 Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                 All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  LICENSE
 *  -------------------------------------------------------------------------------------------------------------------
 *            Module: Dcm
 *           Program: VAG AR4 (MSR_Vag_SLP5)
 *          Customer: Huf H_lsbeck & F_rst GmbH & Co. KG
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: S32K144
 *    License Scope : The usage is restricted to CBD2100188_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: Dcm_Lcfg.c
 *   Generation Time: 2024-02-18 21:43:12
 *           Project: DaVinciConfigurationS32K144 - Version 1.0
 *          Delivery: CBD2100188_D01
 *      Tool Version: DaVinci Configurator  5.23.45 SP4
 *
 *
 *********************************************************************************************************************/



#define DCM_LCFG_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
                                                                                                                                                     /* PRQA S 1533 EOF */ /* MD_Dcm_ObjectOnlyAccessedOnce */
#include "Dcm.h"
#include "Rte_Dcm.h"
#include "Dcm_Int.h"
#include "PduR_Dcm.h"
#include "ComM_Dcm.h"

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#if (DCM_DIDMGR_NVM_READ_ENABLED == STD_ON) || \
    (DCM_DIDMGR_NVM_WRITE_ENABLED == STD_ON)
# if defined(NVM_VENDOR_ID)
#  if (NVM_VENDOR_ID == 30u)
/* Only Vector NvM supports this feature up to now */
#   define Dcm_GetDcmNvMBlockId(blockId)                             (uint16)(NvM_GetDcmBlockId(blockId))                                            /* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro */ /* Macro is more efficient! */
#  endif
# endif

/* Default NvM handle offset */
# if !defined(Dcm_GetDcmNvMBlockId)
#  define Dcm_GetDcmNvMBlockId(blockId)                              (uint16)(blockId)                                                               /* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro */ /* Macro is more efficient! */
# endif
#endif

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DCM_START_SEC_CALLOUT_CODE
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */
/***********************************************************************************************************************
 *  Dcm_SvcWrapper_CanDiagUsr_CommControl0x28()
 ***********************************************************************************************************************/
/*! \brief         Wraps a specific externally implemented service-processor.
 *  \details       Encapsulates the internally used pContext parameter.
 *  \param[in]     pContext              Pointer to the context
 *  \param[in]     opStatus              The operation status
 *  \param[in,out] pMsgContext           Message-related information for one diagnostic protocol identifier
 *                                       The pointers in pMsgContext points behind the SID.
 *  \param[out]    ErrorCode             Negative response code in case return value is DCM_E_NOT_OK
 *  \return        DCM_E_OK              Job processing finished, send positive response
 *  \return        DCM_E_PENDING         Job processing is not yet finished
 *  \return        DCM_E_FORCE_RCRRP     (Vendor extension) Forces a RCR-RP response.
 *                                       The call out will called again once the response is sent. The OpStatus
 *                                       parameter will contain the transmission result
 *  \return        DCM_E_PROCESSINGDONE  (Vendor extension) Can be returned instead of calling Dcm_ProcessingDone() for
 *                                       the current pMsgContext.
 *                                       Saves application code and stack usage.
 *  \return        DCM_E_STOP_REPEATER   Stops the repeater proxy
 *  \return        DCM_E_NOT_OK          Job processing finished, send NRC from the ErrorCode
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
 ***********************************************************************************************************************/
DCM_LOCAL FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_SvcWrapper_CanDiagUsr_CommControl0x28(
  Dcm_ContextPtrType pContext,
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodePtrType ErrorCode
  );
/***********************************************************************************************************************
 *  Dcm_ServiceNoPostProcessor()
 ***********************************************************************************************************************/
/*! \brief         Dummy post-processor
 *  \details       This post-processor is called for diagnostic services which do not require any post processing.
 *  \param[in]     pContext  Pointer to the context
 *  \param[in]     status    The post-processing status
 *  \context       TASK
 *  \reentrant     FALSE
 *  \pre           -
 ***********************************************************************************************************************/
DCM_LOCAL FUNC(void, DCM_CALLOUT_CODE) Dcm_ServiceNoPostProcessor(
  Dcm_ContextPtrType pContext,
  Dcm_ConfirmationStatusType status
  );
#define DCM_STOP_SEC_CALLOUT_CODE
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL DATA DECLARATIONS
 *********************************************************************************************************************/
#define DCM_START_SEC_VAR_NO_INIT_8
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*! DCM protocol descriptor */
DCM_LOCAL VAR(Dcm_MsgItemType, DCM_VAR_NOINIT) Dcm_CfgNetBuffer_000[4096];
#define DCM_STOP_SEC_VAR_NO_INIT_8
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define DCM_START_SEC_CONST_8
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*! TxPduId to DCM connection map */
CONST(Dcm_NetConnRefMemType, DCM_CONST) Dcm_CfgNetTxPduInfo[2]=
{
    0u
  , 1u
};
/*! Map of DCM relevant network handles */
CONST(Dcm_CfgNetNetIdRefMemType, DCM_CONST) Dcm_CfgNetConnComMChannelMap[1]=
{
    0u
};
/*! Look up table of DCM service identifiers */
CONST(uint8, DCM_CONST) Dcm_CfgDiagSvcIdLookUpTable[11]=
{
   10u
  ,0x10u
  ,0x11u
  ,0x14u
  ,0x19u
  ,0x22u
  ,0x28u
  ,0x2Eu
  ,0x31u
  ,0x3Eu
  ,0x85u
};
/*! Service 0x10 look up table  */
CONST(uint8, DCM_CONST) Dcm_CfgSvc10SubFuncLookUpTable[4]=
{
   3u
  ,0x01u
  ,0x02u
  ,0x03u
};
/*! Service 0x11 look up table  */
CONST(uint8, DCM_CONST) Dcm_CfgSvc11SubFuncLookUpTable[3]=
{
   2u
  ,0x01u
  ,0x02u
};
/*! Service 0x19 look up table  */
CONST(uint8, DCM_CONST) Dcm_CfgSvc19SubFuncLookUpTable[6]=
{
   5u
  ,0x01u
  ,0x02u
  ,0x03u
  ,0x04u
  ,0x06u
};
/*! Service 0x3E look up table  */
CONST(uint8, DCM_CONST) Dcm_CfgSvc3ESubFuncLookUpTable[2]=
{
   1u
  ,0x00u
};
/*! Look up table of service 0x85 */
CONST(uint8, DCM_CONST) Dcm_CfgSvc85SubFuncLookUpTable[3]=
{
   2u
  ,0x01u
  ,0x02u
};
#define DCM_STOP_SEC_CONST_8
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define DCM_START_SEC_CONST_16
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*! DID look up table  */
CONST(uint16, DCM_CONST) Dcm_CfgDidMgrDidLookUpTable[46]=
{
   45u
  ,0x0102u
  ,0x0261u
  ,0x0301u
  ,0x0407u
  ,0x040Fu
  ,0x0410u
  ,0x0448u
  ,0x05F0u
  ,0x523Eu
  ,0x7802u
  ,0xF15Bu
  ,0xF17Cu
  ,0xF186u
  ,0xF187u
  ,0xF189u
  ,0xF18Au
  ,0xF18Cu
  ,0xF191u
  ,0xF192u
  ,0xF193u
  ,0xF194u
  ,0xF195u
  ,0xF197u
  ,0xF19Eu
  ,0xF1A0u
  ,0xF1A1u
  ,0xF1A2u
  ,0xF1A3u
  ,0xF1AAu
  ,0xF1ABu
  ,0xF1AFu
  ,0xF1B4u
  ,0xF1B6u
  ,0xF1B8u
  ,0xF1D5u
  ,0xF1DFu
  ,0xFD01u
  ,0xFD02u
  ,0xFD03u
  ,0xFD04u
  ,0xFD05u
  ,0xFD06u
  ,0xFD07u
  ,0xFD13u
  ,0xFD42u
};
/*! RID look up table  */
CONST(uint16, DCM_CONST) Dcm_CfgRidMgrRidLookUpTable[2]=
{
   1u
  ,0x0203u
};
#define DCM_STOP_SEC_CONST_16
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*! DCM buffer descriptor */
CONST(Dcm_CfgNetBufferInfoType, DCM_CONST) Dcm_CfgNetBufferInfo[1]=
{
   { Dcm_CfgNetBuffer_000,4096u}
};
/*! DCM protocol switch notifications */
CONST(Dcm_CfgNetProtocolNotificationInfoType, DCM_CONST) Dcm_CfgNetProtocolNotificationInfo[1]=
{
   { NULL_PTR}
};
/*! RxPduId map */
CONST(Dcm_CfgNetRxPduInfoType, DCM_CONST) Dcm_CfgNetRxPduInfo[4]=
{
   { TRUE, 0u}
  ,{ FALSE, 0u}
  ,{ TRUE, 1u}
  ,{ FALSE, 1u}
};
/*! DCM connection descriptor */
CONST(Dcm_CfgNetConnectionInfoType, DCM_CONST) Dcm_CfgNetConnectionInfo[2]=
{
   { 0x0017u,PduRConf_PduRSrcPdu_PduRSrcPdu_bbe61e78, 0u,0u,0x00u,0x00u, 0u}
  ,{ 0x0217u,PduRConf_PduRSrcPdu_PduRSrcPdu_a9d87b23, 0u,0u,0x00u,0x00u, 0u}
};
/*! DCM protocol descriptor */
CONST(Dcm_CfgNetProtocolInfoType, DCM_CONST) Dcm_CfgNetProtocolInfo[1]=
{
   { {        0u,       0u},4095u, 3u, 0u,TRUE,0u,DemConf_DemClient_DemClient, 0u}
};
/*! Map of all relevant for DCM network handles */
CONST(NetworkHandleType, DCM_CONST) Dcm_CfgNetAllComMChannelMap[1]=
{
   ComMConf_ComMChannel_CN_HCP4_CANFD01_152fd6c6
};
/*! Look up table of DCM relevant network handles */
CONST(NetworkHandleType, DCM_CONST) Dcm_CfgNetNetworkHandleLookUpTable[2]=
{
   1u
  ,ComMConf_ComMChannel_CN_HCP4_CANFD01_152fd6c6
};
/*! Diagnostic service execution conditions */
CONST(Dcm_CfgStatePreconditionInfoType, DCM_CONST) Dcm_CfgStatePreconditions[4]=
{
   { { 0x07u}}
  ,{ { 0x04u}}
  ,{ { 0x05u}}
  ,{ { 0x02u}}
};
/*! Session state properties */
CONST(Dcm_CfgStateSessionInfoType, DCM_CONST) Dcm_CfgStateSessionInfo[3]=
{
   { {        5u,     500u},RTE_MODE_DcmDiagnosticSessionControl_DEFAULT_SESSION,0x01u}
  ,{ {        5u,     500u},RTE_MODE_DcmDiagnosticSessionControl_PROGRAMMING_SESSION,0x02u}
  ,{ {        5u,     500u},RTE_MODE_DcmDiagnosticSessionControl_EXTENDED_SESSION,0x03u}
};
/*! Session state change notification(s) */
CONST(Dcm_CfgStateNotificationInfoType, DCM_CONST) Dcm_CfgStateSessionNotificationInfo[2]=
{
   { Diagnostic_Session_Change_Callback}
  ,{ NULL_PTR}
};
/*! DID ranges look up */
CONST(Dcm_CfgDidMgrDidRangeType, DCM_CONST) Dcm_CfgDidMgrDidRanges[1]=
{
   {    0u,   0u}
};
/*! DID ranges to DID info map */
CONST(Dcm_CfgDidMgrDidInfoRefType, DCM_CONST) Dcm_CfgDidMgrRangeDidInfoRefs[1]=
{
   0u /* dummy initializer */
};
/*! DID properties */
CONST(Dcm_CfgDidMgrDidInfoType, DCM_CONST) Dcm_CfgDidMgrDidInfo[45]=
{
   {    1u,   1u,   1u,   0u,   0u,0x01u} /* DID: 0x0102 */
  ,{    1u,   1u,   1u,   1u,   0u,0x01u} /* DID: 0x0261 */
  ,{    2u,   2u,   2u,   2u,   0u,0x01u} /* DID: 0x0301 */
  ,{    4u,   4u,   4u,   3u,   0u,0x01u} /* DID: 0x0407 */
  ,{    4u,   4u,   4u,   4u,   0u,0x01u} /* DID: 0x040F */
  ,{    1u,   1u,   1u,   5u,   0u,0x03u} /* DID: 0x0410 */
  ,{    5u,   5u,   5u,   7u,   0u,0x01u} /* DID: 0x0448 */
  ,{    1u,   1u,   1u,   8u,   0u,0x03u} /* DID: 0x05F0 */
  ,{    3u,   3u,   3u,  10u,   0u,0x01u} /* DID: 0x523E */
  ,{    1u,   1u,   1u,  11u,   0u,0x01u} /* DID: 0x7802 */
  ,{   20u,  20u,  20u,  12u,   0u,0x01u} /* DID: 0xF15B */
  ,{   23u,  23u,  23u,  13u,   0u,0x01u} /* DID: 0xF17C */
  ,{    1u,   1u,   1u,  14u,   0u,0x01u} /* DID: 0xF186 */
  ,{   11u,  11u,  11u,  15u,   0u,0x01u} /* DID: 0xF187 */
  ,{    4u,   4u,   4u,  16u,   0u,0x01u} /* DID: 0xF189 */
  ,{  100u, 100u, 100u,  17u,   0u,0x01u} /* DID: 0xF18A */
  ,{   20u,  20u,  20u,  18u,   0u,0x01u} /* DID: 0xF18C */
  ,{   11u,  11u,  11u,  19u,   0u,0x01u} /* DID: 0xF191 */
  ,{   11u,  11u,  11u,  20u,   0u,0x01u} /* DID: 0xF192 */
  ,{    3u,   3u,   3u,  21u,   0u,0x01u} /* DID: 0xF193 */
  ,{   11u,  11u,  11u,  22u,   0u,0x01u} /* DID: 0xF194 */
  ,{    4u,   4u,   4u,  23u,   0u,0x01u} /* DID: 0xF195 */
  ,{   13u,  13u,  13u,  24u,   0u,0x01u} /* DID: 0xF197 */
  ,{    0u,  26u,  26u,  25u,   0u,0x01u} /* DID: 0xF19E */
  ,{   11u,  11u,  11u,  26u,   0u,0x03u} /* DID: 0xF1A0 */
  ,{    4u,   4u,   4u,  28u,   0u,0x03u} /* DID: 0xF1A1 */
  ,{    6u,   6u,   6u,  30u,   0u,0x01u} /* DID: 0xF1A2 */
  ,{    3u,   3u,   3u,  31u,   0u,0x01u} /* DID: 0xF1A3 */
  ,{    5u,   5u,   5u,  32u,   0u,0x01u} /* DID: 0xF1AA */
  ,{    8u,   8u,   8u,  33u,   0u,0x01u} /* DID: 0xF1AB */
  ,{   21u,  21u,  21u,  34u,   0u,0x01u} /* DID: 0xF1AF */
  ,{   26u,  26u,  26u,  35u,   0u,0x01u} /* DID: 0xF1B4 */
  ,{    4u,   4u,   4u,  36u,   0u,0x01u} /* DID: 0xF1B6 */
  ,{    5u,   5u,   5u,  37u,   0u,0x01u} /* DID: 0xF1B8 */
  ,{    7u,   7u,   7u,  38u,   0u,0x01u} /* DID: 0xF1D5 */
  ,{    1u,   1u,   1u,  39u,   0u,0x01u} /* DID: 0xF1DF */
  ,{    2u,   2u,   2u,  40u,   0u,0x03u} /* DID: 0xFD01 */
  ,{  168u, 168u, 168u,  42u,   0u,0x03u} /* DID: 0xFD02 */
  ,{    1u,   1u,   1u,  44u,   0u,0x03u} /* DID: 0xFD03 */
  ,{    1u,   1u,   1u,  46u,   0u,0x03u} /* DID: 0xFD04 */
  ,{   10u,  10u,  10u,  48u,   0u,0x01u} /* DID: 0xFD05 */
  ,{   45u,  45u,  45u,  49u,   0u,0x03u} /* DID: 0xFD06 */
  ,{   15u,  15u,  15u,  51u,   0u,0x03u} /* DID: 0xFD07 */
  ,{    2u,   2u,   2u,  53u,   0u,0x01u} /* DID: 0xFD13 */
  ,{    1u,   1u,   1u,  54u,   0u,0x03u} /* DID: 0xFD42 */
};
/*! DID operation properties */
CONST(Dcm_CfgDidMgrDidOpInfoType, DCM_CONST) Dcm_CfgDidMgrDidOpInfo[56]=
{
   {    0u,   0u,0x01u} /* DID: 0x0102 */
  ,{    0u,   1u,0x01u} /* DID: 0x0261 */
  ,{    0u,   2u,0x01u} /* DID: 0x0301 */
  ,{    0u,   3u,0x01u} /* DID: 0x0407 */
  ,{    0u,   4u,0x01u} /* DID: 0x040F */
  ,{    0u,   5u,0x01u} /* DID: 0x0410 */
  ,{    1u,   6u,0x01u} /* DID: 0x0410 */
  ,{    0u,   7u,0x01u} /* DID: 0x0448 */
  ,{    2u,   8u,0x01u} /* DID: 0x05F0 */
  ,{    1u,   9u,0x01u} /* DID: 0x05F0 */
  ,{    0u,  10u,0x01u} /* DID: 0x523E */
  ,{    2u,  11u,0x01u} /* DID: 0x7802 */
  ,{    0u,  12u,0x01u} /* DID: 0xF15B */
  ,{    0u,  13u,0x01u} /* DID: 0xF17C */
  ,{    0u,  14u,0x01u} /* DID: 0xF186 */
  ,{    0u,  15u,0x01u} /* DID: 0xF187 */
  ,{    0u,  16u,0x01u} /* DID: 0xF189 */
  ,{    0u,  17u,0x01u} /* DID: 0xF18A */
  ,{    0u,  18u,0x01u} /* DID: 0xF18C */
  ,{    0u,  19u,0x01u} /* DID: 0xF191 */
  ,{    0u,  20u,0x01u} /* DID: 0xF192 */
  ,{    0u,  21u,0x01u} /* DID: 0xF193 */
  ,{    0u,  22u,0x01u} /* DID: 0xF194 */
  ,{    0u,  23u,0x01u} /* DID: 0xF195 */
  ,{    0u,  24u,0x01u} /* DID: 0xF197 */
  ,{    0u,  25u,0x03u} /* DID: 0xF19E */
  ,{    0u,  27u,0x01u} /* DID: 0xF1A0 */
  ,{    1u,  28u,0x01u} /* DID: 0xF1A0 */
  ,{    0u,  29u,0x01u} /* DID: 0xF1A1 */
  ,{    1u,  30u,0x01u} /* DID: 0xF1A1 */
  ,{    0u,  31u,0x01u} /* DID: 0xF1A2 */
  ,{    0u,  32u,0x01u} /* DID: 0xF1A3 */
  ,{    0u,  33u,0x01u} /* DID: 0xF1AA */
  ,{    0u,  34u,0x01u} /* DID: 0xF1AB */
  ,{    0u,  35u,0x01u} /* DID: 0xF1AF */
  ,{    0u,  36u,0x01u} /* DID: 0xF1B4 */
  ,{    0u,  37u,0x01u} /* DID: 0xF1B6 */
  ,{    0u,  38u,0x01u} /* DID: 0xF1B8 */
  ,{    0u,  39u,0x01u} /* DID: 0xF1D5 */
  ,{    0u,  40u,0x01u} /* DID: 0xF1DF */
  ,{    2u,  41u,0x01u} /* DID: 0xFD01 */
  ,{    1u,  42u,0x01u} /* DID: 0xFD01 */
  ,{    2u,  43u,0x01u} /* DID: 0xFD02 */
  ,{    1u,  44u,0x01u} /* DID: 0xFD02 */
  ,{    2u,  45u,0x01u} /* DID: 0xFD03 */
  ,{    1u,  46u,0x01u} /* DID: 0xFD03 */
  ,{    2u,  47u,0x01u} /* DID: 0xFD04 */
  ,{    1u,  48u,0x01u} /* DID: 0xFD04 */
  ,{    2u,  49u,0x01u} /* DID: 0xFD05 */
  ,{    2u,  50u,0x01u} /* DID: 0xFD06 */
  ,{    1u,  51u,0x01u} /* DID: 0xFD06 */
  ,{    2u,  52u,0x01u} /* DID: 0xFD07 */
  ,{    1u,  53u,0x01u} /* DID: 0xFD07 */
  ,{    2u,  54u,0x01u} /* DID: 0xFD13 */
  ,{    2u,  55u,0x01u} /* DID: 0xFD42 */
  ,{    1u,  56u,0x01u} /* DID: 0xFD42 */
};
/*! DID operation classes */
CONST(Dcm_CfgDidMgrDidOpClassInfoType, DCM_CONST) Dcm_CfgDidMgrDidOpClassInfo[58]=
{
   {  0u}
  ,{  1u}
  ,{  2u}
  ,{  3u}
  ,{  4u}
  ,{  5u}
  ,{  6u}
  ,{  7u}
  ,{  8u}
  ,{  9u}
  ,{ 10u}
  ,{ 11u}
  ,{ 12u}
  ,{ 13u}
  ,{ 14u}
  ,{ 15u}
  ,{ 16u}
  ,{ 17u}
  ,{ 18u}
  ,{ 19u}
  ,{ 20u}
  ,{ 21u}
  ,{ 22u}
  ,{ 23u}
  ,{ 24u}
  ,{ 25u}
  ,{ 26u}
  ,{ 27u}
  ,{ 28u}
  ,{ 29u}
  ,{ 30u}
  ,{ 31u}
  ,{ 32u}
  ,{ 33u}
  ,{ 34u}
  ,{ 35u}
  ,{ 36u}
  ,{ 37u}
  ,{ 38u}
  ,{ 39u}
  ,{ 40u}
  ,{ 41u}
  ,{ 42u}
  ,{ 43u}
  ,{ 44u}
  ,{ 45u}
  ,{ 46u}
  ,{ 47u}
  ,{ 48u}
  ,{ 49u}
  ,{ 50u}
  ,{ 51u}
  ,{ 52u}
  ,{ 53u}
  ,{ 54u}
  ,{ 55u}
  ,{ 56u}
  ,{ 57u}
};
/*! DID signal operation classes */
CONST(Dcm_CfgDidMgrSignalOpClassInfoType, DCM_CONST) Dcm_CfgDidMgrSignalOpClassInfo[57]=
{
   { ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0x0102_Read_Function)),   1u,   1u,0x0001u} /* DID: 0x0102 */                                                /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0x0261_Read_Function)),   1u,   1u,0x0002u} /* DID: 0x0261 */                                                /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0x0301_Read_Function)),   2u,   2u,0x0001u} /* DID: 0x0301 */                                                /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0x0407_Read_Function)),   4u,   4u,0x0001u} /* DID: 0x0407 */                                                /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0x040F_Read_Function)),   4u,   4u,0x0001u} /* DID: 0x040F */                                                /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0x0410_Read_Function)),   1u,   1u,0x0001u} /* DID: 0x0410 */                                                /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0x0410_Write_Function)),   1u,   1u,0x1001u} /* DID: 0x0410 */                                               /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0x0448_Read_Function)),   5u,   5u,0x0001u} /* DID: 0x0448 */                                                /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0x05F0_Read_Function)),   1u,   1u,0x0002u} /* DID: 0x05F0 */                                                /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0x05F0_Write_Function)),   1u,   1u,0x1002u} /* DID: 0x05F0 */                                               /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0x523E_Read_Function)),   3u,   3u,0x0001u} /* DID: 0x523E */                                                /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0x7802_Read_Function)),   1u,   1u,0x0002u} /* DID: 0x7802 */                                                /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0xF15B_Read_Function)),  20u,  20u,0x0001u} /* DID: 0xF15B */                                                /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0xF17C_Read_Function)),  23u,  23u,0x0001u} /* DID: 0xF17C */                                                /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0xF186_Read_Function)),   1u,   1u,0x0001u} /* DID: 0xF186 */                                                /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0xF187_Read_Function)),  11u,  11u,0x0001u} /* DID: 0xF187 */                                                /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0xF189_Read_Function)),   4u,   4u,0x0001u} /* DID: 0xF189 */                                                /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0xF18A_Read_Function)), 100u, 100u,0x0001u} /* DID: 0xF18A */                                                /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0xF18C_Read_Function)),  20u,  20u,0x0001u} /* DID: 0xF18C */                                                /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0xF191_Read_Function)),  11u,  11u,0x0001u} /* DID: 0xF191 */                                                /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0xF192_Read_Function)),  11u,  11u,0x0001u} /* DID: 0xF192 */                                                /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0xF193_Read_Function)),   3u,   3u,0x0001u} /* DID: 0xF193 */                                                /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0xF194_Read_Function)),  11u,  11u,0x0001u} /* DID: 0xF194 */                                                /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0xF195_Read_Function)),   4u,   4u,0x0001u} /* DID: 0xF195 */                                                /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0xF197_Read_Function)),  13u,  13u,0x0001u} /* DID: 0xF197 */                                                /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0xF19E_Read_Function)),   0u,  26u,0x0001u} /* DID: 0xF19E */                                                /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0xF19E_GetDataLength_Function)),   0u,   0u,0x0101u} /* DID: 0xF19E */                                       /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0xF1A0_Read_Function)),  11u,  11u,0x0002u} /* DID: 0xF1A0 */                                                /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0xF1A0_Write_Function)),  11u,  11u,0x1002u} /* DID: 0xF1A0 */                                               /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0xF1A1_Read_Function)),   4u,   4u,0x0002u} /* DID: 0xF1A1 */                                                /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0xF1A1_Write_Function)),   4u,   4u,0x1002u} /* DID: 0xF1A1 */                                               /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0xF1A2_Read_Function)),   6u,   6u,0x0001u} /* DID: 0xF1A2 */                                                /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0xF1A3_Read_Function)),   3u,   3u,0x0001u} /* DID: 0xF1A3 */                                                /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0xF1AA_Read_Function)),   5u,   5u,0x0001u} /* DID: 0xF1AA */                                                /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0xF1AB_Read_Function)),   8u,   8u,0x0001u} /* DID: 0xF1AB */                                                /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0xF1AF_Read_Function)),  21u,  21u,0x0001u} /* DID: 0xF1AF */                                                /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0xF1B4_Read_Function)),  26u,  26u,0x0001u} /* DID: 0xF1B4 */                                                /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0xF1B6_Read_Function)),   4u,   4u,0x0001u} /* DID: 0xF1B6 */                                                /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0xF1B8_Read_Function)),   5u,   5u,0x0001u} /* DID: 0xF1B8 */                                                /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0xF1D5_Read_Function)),   7u,   7u,0x0001u} /* DID: 0xF1D5 */                                                /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0xF1DF_Read_Function)),   1u,   1u,0x0001u} /* DID: 0xF1DF */                                                /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0xFD01_Read_Function)),   2u,   2u,0x0002u} /* DID: 0xFD01 */                                                /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0xFD01_Write_Function)),   2u,   2u,0x1002u} /* DID: 0xFD01 */                                               /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0xFD02_Read_Function)), 168u, 168u,0x0002u} /* DID: 0xFD02 */                                                /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0xFD02_Write_Function)), 168u, 168u,0x1002u} /* DID: 0xFD02 */                                               /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0xFD03_Read_Function)),   1u,   1u,0x0002u} /* DID: 0xFD03 */                                                /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0xFD03_Write_Function)),   1u,   1u,0x1002u} /* DID: 0xFD03 */                                               /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0xFD04_Read_Function)),   1u,   1u,0x0002u} /* DID: 0xFD04 */                                                /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0xFD04_Write_Function)),   1u,   1u,0x1002u} /* DID: 0xFD04 */                                               /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0xFD05_Read_Function)),  10u,  10u,0x0002u} /* DID: 0xFD05 */                                                /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0xFD06_Read_Function)),  45u,  45u,0x0002u} /* DID: 0xFD06 */                                                /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0xFD06_Write_Function)),  45u,  45u,0x1002u} /* DID: 0xFD06 */                                               /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0xFD07_Read_Function)),  15u,  15u,0x0002u} /* DID: 0xFD07 */                                                /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0xFD07_Write_Function)),  15u,  15u,0x1002u} /* DID: 0xFD07 */                                               /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0xFD13_Read_Function)),   2u,   2u,0x0001u} /* DID: 0xFD13 */                                                /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0xFD42_Read_Function)),   1u,   1u,0x0002u} /* DID: 0xFD42 */                                                /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(CanDiagUsr_0xFD42_Write_Function)),   1u,   1u,0x1002u} /* DID: 0xFD42 */                                               /* PRQA S 0313 */ /* MD_Dcm_0313 */
};
/*! RID properties */
CONST(Dcm_CfgRidMgrRidInfoType, DCM_CONST) Dcm_CfgRidMgrRidInfo[1]=
{
   {    0u,   0u,0x01u, 0u} /* RID: 0x0203 */
};
/*! RID operation properties */
CONST(Dcm_CfgRidMgrOpInfoType, DCM_CONST) Dcm_CfgRidMgrOpInfo[1]=
{
   { ((Dcm_RidMgrOpFuncType)(CheckProgrammingPreconditions)),   0u,   0u,   0u,   4u, 6u, 0u} /* RID: 0x0203 */                                      /* PRQA S 0313 */ /* MD_Dcm_0313 */
};
/*! DCM service initializers */
CONST(Dcm_DiagSvcInitFuncType, DCM_CONST) Dcm_CfgDiagSvcInitializers[1]=
{
   NULL_PTR /* end marker */
};
/*! DCM service properties */
CONST(Dcm_CfgDiagServiceInfoType, DCM_CONST) Dcm_CfgDiagServiceInfo[11]=
{
   { Dcm_Service10Processor,0x01u, 1u,   1u,   2u} /* SID: 0x10 */
  ,{ Dcm_Service11Processor,0x01u, 1u,   3u,   4u} /* SID: 0x11 */
  ,{ Dcm_Service14Processor,0x00u, 3u,   0u,   0u} /* SID: 0x14 */
  ,{ Dcm_Service19Processor,0x01u, 1u,   5u,   0u} /* SID: 0x19 */
  ,{ Dcm_Service22Processor,0x00u, 2u,   0u,   0u} /* SID: 0x22 */
  ,{ Dcm_SvcWrapper_CanDiagUsr_CommControl0x28,0x01u, 1u,   0u,   0u} /* SID: 0x28 */
  ,{ Dcm_Service2EProcessor,0x00u, 3u,   0u,   0u} /* SID: 0x2E */
  ,{ Dcm_Service31Processor,0x01u, 3u,   0u,   0u} /* SID: 0x31 */
  ,{ Dcm_Service3EProcessor,0x01u, 1u,   0u,   0u} /* SID: 0x3E */
  ,{ Dcm_Service85Processor,0x01u, 1u,   6u,   0u} /* SID: 0x85 */
  ,{ Dcm_RepeaterDeadEnd,0x00u, 0u,   0u,   0u} /* Dcm_RepeaterDeadEnd */
};
/*! Indirection from diag service info to execution pre conditions */
CONST(Dcm_CfgStateRefMemType, DCM_CONST) Dcm_CfgDiagSvcIdExecPrecondTable[10]=
{
      0u /* SID: 0x10 */
  ,   2u /* SID: 0x11 */
  ,   2u /* SID: 0x14 */
  ,   2u /* SID: 0x19 */
  ,   0u /* SID: 0x22 */
  ,   1u /* SID: 0x28 */
  ,   0u /* SID: 0x2E */
  ,   2u /* SID: 0x31 */
  ,   2u /* SID: 0x3E */
  ,   1u /* SID: 0x85 */
};
/*! DCM service post processors */
CONST(Dcm_DiagSvcConfirmationFuncType, DCM_CONST) Dcm_CfgDiagSvcPostProcessors[7]=
{
   Dcm_ServiceNoPostProcessor
  ,Dcm_Service10PostProcessor
  ,Dcm_Service10FastPostProcessor
  ,Dcm_Service11PostProcessor
  ,Dcm_Service11FastPostProcessor
  ,Dcm_Service19PostProcessor
  ,Dcm_Service85PostProcessor
};
/*! OEM notification functions */
CONST(Dcm_CfgDiagNotificationInfoType, DCM_CONST) Dcm_CfgDiagOemNotificationInfo[1]=
{
   { NULL_PTR,NULL_PTR}
};
/*! System supplier notification functions */
CONST(Dcm_CfgDiagNotificationInfoType, DCM_CONST) Dcm_CfgDiagSysNotificationInfo[2]=
{
   { CAN_DiagUsr_SupplierIndication,CAN_DiagUsr_SupplierConfirmation}
  ,{ NULL_PTR,NULL_PTR}
};
/*! DCM service to protocol map */
CONST(Dcm_CfgDiagSvc2ProtMapMemType, DCM_CONST) Dcm_CfgDiagSvcId2ProtMap[10]=
{
   0x01u
  ,0x01u
  ,0x01u
  ,0x01u
  ,0x01u
  ,0x01u
  ,0x01u
  ,0x01u
  ,0x01u
  ,0x01u
};
/*! Service 0x10 sub-service properties table  */
CONST(Dcm_CfgSvc10SubFuncInfoType, DCM_CONST) Dcm_CfgSvc10SubFuncInfo[3]=
{
   { { 50u, 500u}, 0u} /* Session ID: 0x01 */
  ,{ { 50u, 500u}, 2u} /* Session ID: 0x02 */
  ,{ { 50u, 500u}, 0u} /* Session ID: 0x03 */
};
/*! Indirection from service 0x10 sub functions to execution pre conditions */
CONST(Dcm_CfgStateRefMemType, DCM_CONST) Dcm_CfgSvc10SubFuncExecPrecondTable[3]=
{
      0u /* Session ID: 0x01 */
  ,   1u /* Session ID: 0x02 */
  ,   0u /* Session ID: 0x03 */
};
/*! Service 0x11 sub-service properties table  */
CONST(Dcm_CfgSvc11SubFuncInfoType, DCM_CONST) Dcm_CfgSvc11SubFuncInfo[2]=
{
   { Dcm_Service11_01Processor} /* SF: 0x01 */
  ,{ Dcm_Service11_02Processor} /* SF: 0x02 */
};
/*! Indirection from service 0x11 sub functions to execution pre conditions */
CONST(Dcm_CfgStateRefMemType, DCM_CONST) Dcm_CfgSvc11SubFuncExecPrecondTable[2]=
{
      3u /* SF: 0x01 */
  ,   2u /* SF: 0x02 */
};
/*! Service 0x19 sub-service properties table  */
CONST(Dcm_CfgSvc19SubFuncInfoType, DCM_CONST) Dcm_CfgSvc19SubFuncInfo[5]=
{
   { Dcm_Service19_01Processor, 2u} /* SF: 0x01 */
  ,{ Dcm_Service19_02Processor, 2u} /* SF: 0x02 */
  ,{ Dcm_Service19_03Processor, 1u} /* SF: 0x03 */
  ,{ Dcm_Service19_04Processor, 5u} /* SF: 0x04 */
  ,{ Dcm_Service19_06Processor, 5u} /* SF: 0x06 */
};
/*! Indirection from service 0x19 sub functions to execution pre conditions */
CONST(Dcm_CfgStateRefMemType, DCM_CONST) Dcm_CfgSvc19SubFuncExecPrecondTable[5]=
{
      0u /* SF: 0x01 */
  ,   0u /* SF: 0x02 */
  ,   0u /* SF: 0x03 */
  ,   0u /* SF: 0x04 */
  ,   0u /* SF: 0x06 */
};
/*! Indirection from service 0x3E sub functions to execution pre conditions */
CONST(Dcm_CfgStateRefMemType, DCM_CONST) Dcm_CfgSvc3ESubFuncExecPrecondTable[1]=
{
      0u /* SF: 0x00 */
};
/*! Indirection from service 0x85 sub functions to execution pre conditions */
CONST(Dcm_CfgStateRefMemType, DCM_CONST) Dcm_CfgSvc85SubFuncExecPrecondTable[2]=
{
      0u /* SF: 0x01 */
  ,   0u /* SF: 0x02 */
};
/*! DCM service 0x85 properties */
CONST(Dcm_CfgSvc85SubFuncInfoType, DCM_CONST) Dcm_CfgSvc85SubFuncInfo[2]=
{
   { Dem_EnableDTCSetting,RTE_MODE_DcmControlDtcSetting_ENABLEDTCSETTING} /* SF: 0x01 */
  ,{ Dem_DisableDTCSetting,RTE_MODE_DcmControlDtcSetting_DISABLEDTCSETTING} /* SF: 0x02 */
};
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
#define DCM_START_SEC_CALLOUT_CODE
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */
/***********************************************************************************************************************
 *  Dcm_SvcWrapper_CanDiagUsr_CommControl0x28()
 ***********************************************************************************************************************/
/* Implements CDD Dcm_SvcWrapper_<XXX>() */
DCM_LOCAL FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_SvcWrapper_CanDiagUsr_CommControl0x28(
  Dcm_ContextPtrType pContext,  /* PRQA S 3673 */ /* MD_Dcm_APIStd_3673 */
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodePtrType ErrorCode
  )
{
  DCM_IGNORE_UNREF_PARAM(pContext);  /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
  return CanDiagUsr_CommControl0x28(opStatus, pMsgContext, ErrorCode);  /* SBSW_DCM_GEN_PARAM_PTR_FORWARD */
}
/***********************************************************************************************************************
 *  Dcm_ServiceNoPostProcessor()
 ***********************************************************************************************************************/
/* Implements CDD Dcm_ServiceNoPostProcessor() */
DCM_LOCAL FUNC(void, DCM_CALLOUT_CODE) Dcm_ServiceNoPostProcessor(
  Dcm_ContextPtrType pContext,  /* PRQA S 3673 */ /* MD_Dcm_APIStd_3673 */
  Dcm_ConfirmationStatusType status
  )
{
  DCM_IGNORE_UNREF_PARAM(pContext);  /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
  DCM_IGNORE_UNREF_PARAM(status);  /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}
#define DCM_STOP_SEC_CALLOUT_CODE
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  END OF FILE: Dcm_Lcfg.c
 *********************************************************************************************************************/

