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
 *            Module: CanIf
 *           Program: VAG AR4 (MSR_Vag_SLP5)
 *          Customer: Huf H_lsbeck & F_rst GmbH & Co. KG
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: S32K144
 *    License Scope : The usage is restricted to CBD2100188_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: CanIf_Lcfg.c
 *   Generation Time: 2024-01-27 22:50:08
 *           Project: DaVinciConfigurationS32K144 - Version 1.0
 *          Delivery: CBD2100188_D01
 *      Tool Version: DaVinci Configurator  5.23.45 SP4
 *
 *
 *********************************************************************************************************************/

#define CANIF_LCFG_SOURCE

/**********************************************************************************************************************
  \file  Includes
**********************************************************************************************************************/
/** 
  \brief  Required external files.
*/ 

#include "CanIf_Cfg.h"

 /*  CanTp Header Files  */ 
#include "CanTp_Cfg.h"
#include "CanTp_Cbk.h"
 /*  PduR Header Files  */ 
#include "PduR_Cfg.h"
#include "PduR_CanIf.h"
 /*  CanSM Header Files  */ 
#include "CanSM_Cbk.h"

#define CANIF_START_SEC_APPL_CODE

#include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

/**********************************************************************************************************************
  \var  Prototypes of callback functions
**********************************************************************************************************************/

/** 
  \brief  Tx confirmation functions.
*/



/** 
  \brief  Rx indication functions.
*/




 /** 
  \brief  Wake-up validation function.
*/

FUNC(void, CANIF_APPL_CODE) EcuM_ValidateWakeupEvent(EcuM_WakeupSourceType CanWakeupEvents);

#define CANIF_STOP_SEC_APPL_CODE

#include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

/**********************************************************************************************************************
  ComStackLib
**********************************************************************************************************************/
/**********************************************************************************************************************
  LOCAL DATA PROTOTYPES
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: LOCAL DATA PROTOTYPES
**********************************************************************************************************************/

/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: LOCAL DATA PROTOTYPES
**********************************************************************************************************************/


/**********************************************************************************************************************
  LOCAL DATA
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: LOCAL DATA
**********************************************************************************************************************/

/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: LOCAL DATA
**********************************************************************************************************************/


/**********************************************************************************************************************
  GLOBAL DATA
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA
**********************************************************************************************************************/
/**********************************************************************************************************************
  CanIf_BusOffNotificationFctPtr
**********************************************************************************************************************/
#define CANIF_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(CanIf_BusOffNotificationFctType, CANIF_CONST) CanIf_BusOffNotificationFctPtr = CanSM_ControllerBusOff;  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  CanIf_CanIfCtrlId2MappedTxBuffersConfig
**********************************************************************************************************************/
/** 
  \var    CanIf_CanIfCtrlId2MappedTxBuffersConfig
  \brief  CAN controller configuration - mapped Tx-buffer(s).
  \details
  Element                          Description
  MappedTxBuffersConfigEndIdx      the end index of the 1:n relation pointing to CanIf_MappedTxBuffersConfig
  MappedTxBuffersConfigStartIdx    the start index of the 1:n relation pointing to CanIf_MappedTxBuffersConfig
*/ 
#define CANIF_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(CanIf_CanIfCtrlId2MappedTxBuffersConfigType, CANIF_CONST) CanIf_CanIfCtrlId2MappedTxBuffersConfig[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    MappedTxBuffersConfigEndIdx                                                                             MappedTxBuffersConfigStartIdx                                                                                   Referable Keys */
  { /*     0 */                          1u  /* /ActiveEcuC/CanIf/CanIfCtrlDrvCfg_7d254554/CT_HCP4_CANFD01_a1aa3031 */,                            0u  /* /ActiveEcuC/CanIf/CanIfCtrlDrvCfg_7d254554/CT_HCP4_CANFD01_a1aa3031 */ }   /* [/ActiveEcuC/CanIf/CanIfCtrlDrvCfg_7d254554/CT_HCP4_CANFD01_a1aa3031] */
};
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  CanIf_CtrlModeIndicationFctPtr
**********************************************************************************************************************/
#define CANIF_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(CanIf_CtrlModeIndicationFctType, CANIF_CONST) CanIf_CtrlModeIndicationFctPtr = CanSM_ControllerModeIndication;  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  CanIf_MailBoxConfig
**********************************************************************************************************************/
/** 
  \var    CanIf_MailBoxConfig
  \brief  Mailbox table.
  \details
  Element                 Description
  CtrlStatesIdx           the index of the 1:1 relation pointing to CanIf_CtrlStates
  PduIdFirst              "First" PDU mapped to mailbox.
  PduIdLast               "Last" PDU mapped to mailbox.
  TxBufferCfgIdx          the index of the 0:1 relation pointing to CanIf_TxBufferPrioByCanIdByteQueueConfig
  TxBufferHandlingType
  MailBoxType             Type of mailbox: Rx-/Tx- BasicCAN/FullCAN/unused.
*/ 
#define CANIF_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(CanIf_MailBoxConfigType, CANIF_CONST) CanIf_MailBoxConfig[3] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    CtrlStatesIdx                                                                             PduIdFirst                           PduIdLast                           TxBufferCfgIdx                                                                              TxBufferHandlingType                     MailBoxType                    Referable Keys */
  { /*     0 */            0u  /* /ActiveEcuC/CanIf/CanIfCtrlDrvCfg_7d254554/CT_HCP4_CANFD01_a1aa3031 */,         0u  /* Unused, TxPduId 0 */,        0u  /* Unused, TxPduId 3 */,                                     0u  /* /ActiveEcuC/CanIf/CanIfInitCfg/CHNL_2a45b2d1 */, CANIF_TXBUFFER_HANDLINGTYPE_PRIOBYCANID, CANIF_TxBasicCANMailbox },  /* [/ActiveEcuC/Can/CanConfigSet/CN_HCP4_CANFD01_152fd6c6_Tx] */
  { /*     1 */            0u  /* /ActiveEcuC/CanIf/CanIfCtrlDrvCfg_7d254554/CT_HCP4_CANFD01_a1aa3031 */,         0u  /* Unused object */    ,        0u  /* Unused object */    , CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG  /* unusedIndex1 */                                , CANIF_TXBUFFER_HANDLINGTYPE_NONE       , CANIF_UnusedCANMailbox  },  /* [/ActiveEcuC/Can/CanConfigSet/CN_HCP4_CANFD01_9945d1af_Rx] */
  { /*     2 */            0u  /* /ActiveEcuC/CanIf/CanIfCtrlDrvCfg_7d254554/CT_HCP4_CANFD01_a1aa3031 */,         0u  /* RxPduId */          ,        4u  /* RxPduId  */         , CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG  /* unusedIndex2 */                                , CANIF_TXBUFFER_HANDLINGTYPE_NONE       , CANIF_RxBasicCANMailbox }   /* [/ActiveEcuC/Can/CanConfigSet/CN_HCP4_CANFD01_ac0f8757_Rx] */
};
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  CanIf_MappedTxBuffersConfig
**********************************************************************************************************************/
/** 
  \var    CanIf_MappedTxBuffersConfig
  \brief  Mapped Tx-buffer(s)
  \details
  Element             Description
  MailBoxConfigIdx    the index of the 1:1 relation pointing to CanIf_MailBoxConfig
*/ 
#define CANIF_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(CanIf_MappedTxBuffersConfigType, CANIF_CONST) CanIf_MappedTxBuffersConfig[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    MailBoxConfigIdx                                                                        Referable Keys */
  { /*     0 */               0u  /* /ActiveEcuC/Can/CanConfigSet/CN_HCP4_CANFD01_152fd6c6_Tx */ }   /* [/ActiveEcuC/CanIf/CanIfCtrlDrvCfg_7d254554/CT_HCP4_CANFD01_a1aa3031] */
};
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  CanIf_RxIndicationFctList
**********************************************************************************************************************/
/** 
  \var    CanIf_RxIndicationFctList
  \brief  Rx indication functions table.
  \details
  Element               Description
  RxIndicationFct       Rx indication function.
  RxIndicationLayout    Layout of Rx indication function.
*/ 
#define CANIF_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(CanIf_RxIndicationFctListType, CANIF_CONST) CanIf_RxIndicationFctList[3] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    RxIndicationFct                                               RxIndicationLayout                                                                 Referable Keys */
  { /*     0 */  { (CanIf_SimpleRxIndicationFctType)NULL_PTR }              , CanIf_SimpleRxIndicationLayout    /* PRQA S 0313 */ /* MD_CanIf_Rule11.1 */ },  /* [NULL_PTR] */
  { /*     1 */  { (CanIf_SimpleRxIndicationFctType)CanTp_RxIndication }    , CanIf_AdvancedRxIndicationLayout  /* PRQA S 0313 */ /* MD_CanIf_Rule11.1 */ },  /* [CanTp_RxIndication] */
  { /*     2 */  { (CanIf_SimpleRxIndicationFctType)PduR_CanIfRxIndication }, CanIf_AdvancedRxIndicationLayout  /* PRQA S 0313 */ /* MD_CanIf_Rule11.1 */ }   /* [PduR_CanIfRxIndication] */
};
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  CanIf_RxPduConfig
**********************************************************************************************************************/
/** 
  \var    CanIf_RxPduConfig
  \brief  Rx-PDU configuration table.
  \details
  Element                   Description
  RxPduCanId                Rx-PDU: CAN identifier.
  RxPduMask                 Rx-PDU: CAN identifier mask.
  UpperPduId                PDU ID defined by upper layer.
  RxIndicationFctListIdx    the index of the 1:1 relation pointing to CanIf_RxIndicationFctList
  RxPduDlc                  Rx-PDU length (DLC).
  MsgType                   Type of CAN message: *CAN (both 2.0 or FD), *FD_CAN (only FD), *NO_FD_CAN (only 2.0).
*/ 
#define CANIF_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(CanIf_RxPduConfigType, CANIF_CONST) CanIf_RxPduConfig[5] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    RxPduCanId                                                                                 RxPduMask                                                                     UpperPduId                                  RxIndicationFctListIdx                                RxPduDlc                               MsgType                      Comment                                                                                         Referable Keys */
  { /*     0 */ 0x9C440217u  /* OBDC_NFC_FS_Req_FD_XIX_HCP4_CANFD01_35d280a9_Rx, only FD-PDU */          , 0xDFFFFFFFu  /* OBDC_NFC_FS_Req_FD_XIX_HCP4_CANFD01_35d280a9_Rx */          , CanTpConf_CanTpRxNPdu_CanTpRxNPdu_ca69bed7,                     1u  /* CanTp_RxIndication */    ,       0u  /* DLC-Check is disabled */, CANIF_MSG_TYPE_FD_CAN },  /* [PDU: OBDC_NFC_FS_Req_FD_XIX_HCP4_CANFD01_35d280a9_Rx, CanId: 0x1c440217]           */  /* [CanIfConf_CanIfRxPduCfg_OBDC_NFC_FS_Req_FD_XIX_HCP4_CANFD01_35d280a9_Rx] */
  { /*     1 */ 0x9C440017u  /* ISOx_NFC_FS_Req_FD_XIX_HCP4_CANFD01_2917078e_Rx, only FD-PDU */          , 0x9FFFFFFFu  /* ISOx_NFC_FS_Req_FD_XIX_HCP4_CANFD01_2917078e_Rx */          , CanTpConf_CanTpRxNPdu_CanTpRxNPdu_f8c795a3,                     1u  /* CanTp_RxIndication */    ,       0u  /* DLC-Check is disabled */, CANIF_MSG_TYPE_FD_CAN },  /* [PDU: ISOx_NFC_FS_Req_FD_XIX_HCP4_CANFD01_2917078e_Rx, CanId: 0x1c440017]           */  /* [CanIfConf_CanIfRxPduCfg_ISOx_NFC_FS_Req_FD_XIX_HCP4_CANFD01_2917078e_Rx] */
  { /*     2 */ 0x9C410200u  /* OBDC_Funktionaler_Req_All_FD_XIX_HCP4_CANFD01_922192d8_Rx, only FD-PDU */, 0x9FFFFFFFu  /* OBDC_Funktionaler_Req_All_FD_XIX_HCP4_CANFD01_922192d8_Rx */, CanTpConf_CanTpRxNPdu_CanTpRxNPdu_ab765b2a,                     1u  /* CanTp_RxIndication */    ,       0u  /* DLC-Check is disabled */, CANIF_MSG_TYPE_FD_CAN },  /* [PDU: OBDC_Funktionaler_Req_All_FD_XIX_HCP4_CANFD01_922192d8_Rx, CanId: 0x1c410200] */  /* [CanIfConf_CanIfRxPduCfg_OBDC_Funktionaler_Req_All_FD_XIX_HCP4_CANFD01_922192d8_Rx] */
  { /*     3 */ 0x9C410000u  /* ISOx_Funkt_Req_All_FD_XIX_HCP4_CANFD01_327ee3e6_Rx, only FD-PDU */       , 0x9FFFFFFFu  /* ISOx_Funkt_Req_All_FD_XIX_HCP4_CANFD01_327ee3e6_Rx */       , CanTpConf_CanTpRxNPdu_CanTpRxNPdu_82c3d3ab,                     1u  /* CanTp_RxIndication */    ,       0u  /* DLC-Check is disabled */, CANIF_MSG_TYPE_FD_CAN },  /* [PDU: ISOx_Funkt_Req_All_FD_XIX_HCP4_CANFD01_327ee3e6_Rx, CanId: 0x1c410000]        */  /* [CanIfConf_CanIfRxPduCfg_ISOx_Funkt_Req_All_FD_XIX_HCP4_CANFD01_327ee3e6_Rx] */
  { /*     4 */ 0x92DD54DAu  /* DoorFunctions_FS_01_XIX_HCP4_CANFD01_0b06b15d_Rx, only FD-PDU */         , 0x9FFFFFFFu  /* DoorFunctions_FS_01_XIX_HCP4_CANFD01_0b06b15d_Rx */         , PduRConf_PduRSrcPdu_PduRSrcPdu_660745f7   ,                     2u  /* PduR_CanIfRxIndication */,      60u  /* DLC-Check is enabled */ , CANIF_MSG_TYPE_FD_CAN }   /* [PDU: DoorFunctions_FS_01_XIX_HCP4_CANFD01_0b06b15d_Rx, CanId: 0x12dd54da]          */  /* [CanIfConf_CanIfRxPduCfg_DoorFunctions_FS_01_XIX_HCP4_CANFD01_0b06b15d_Rx] */
};
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  CanIf_TxBufferPrioByCanIdByteQueueConfig
**********************************************************************************************************************/
/** 
  \var    CanIf_TxBufferPrioByCanIdByteQueueConfig
  \brief  Tx-buffer: PRIO_BY_CANID as BYTE_QUEUE
  \details
  Element                                             Description
  TxBufferPrioByCanIdBaseIdx                          the index of the 1:1 relation pointing to CanIf_TxBufferPrioByCanIdBase
  TxBufferPrioByCanIdByteQueueMappedTxPdusEndIdx      the end index of the 1:n relation pointing to CanIf_TxBufferPrioByCanIdByteQueueMappedTxPdus
  TxBufferPrioByCanIdByteQueueMappedTxPdusLength      the number of relations pointing to CanIf_TxBufferPrioByCanIdByteQueueMappedTxPdus
  TxBufferPrioByCanIdByteQueueMappedTxPdusStartIdx    the start index of the 1:n relation pointing to CanIf_TxBufferPrioByCanIdByteQueueMappedTxPdus
*/ 
#define CANIF_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(CanIf_TxBufferPrioByCanIdByteQueueConfigType, CANIF_CONST) CanIf_TxBufferPrioByCanIdByteQueueConfig[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    TxBufferPrioByCanIdBaseIdx                                                      TxBufferPrioByCanIdByteQueueMappedTxPdusEndIdx                                                      TxBufferPrioByCanIdByteQueueMappedTxPdusLength                                                      TxBufferPrioByCanIdByteQueueMappedTxPdusStartIdx                                                            Referable Keys */
  { /*     0 */                         0u  /* /ActiveEcuC/CanIf/CanIfInitCfg/CHNL_2a45b2d1 */,                                             4u  /* /ActiveEcuC/CanIf/CanIfInitCfg/CHNL_2a45b2d1 */,                                             4u  /* /ActiveEcuC/CanIf/CanIfInitCfg/CHNL_2a45b2d1 */,                                               0u  /* /ActiveEcuC/CanIf/CanIfInitCfg/CHNL_2a45b2d1 */ }   /* [/ActiveEcuC/CanIf/CanIfInitCfg/CHNL_2a45b2d1] */
};
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  CanIf_TxBufferPrioByCanIdByteQueueMappedTxPdus
**********************************************************************************************************************/
/** 
  \var    CanIf_TxBufferPrioByCanIdByteQueueMappedTxPdus
  \brief  Tx-buffer: PRIO_BY_CANID as BYTE_QUEUE: Mapped Tx-PDUs
  \details
  Element           Description
  TxPduConfigIdx    the index of the 1:1 relation pointing to CanIf_TxPduConfig
*/ 
#define CANIF_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(CanIf_TxBufferPrioByCanIdByteQueueMappedTxPdusType, CANIF_CONST) CanIf_TxBufferPrioByCanIdByteQueueMappedTxPdus[4] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    TxPduConfigIdx                                                                                               Referable Keys */
  { /*     0 */             0u  /* /ActiveEcuC/CanIf/CanIfInitCfg/OBDC_NFC_FS_Resp_FD_XIX_HCP4_CANFD01_7bcf65c3_Tx */ },  /* [/ActiveEcuC/CanIf/CanIfInitCfg/CHNL_2a45b2d1] */
  { /*     1 */             1u  /* /ActiveEcuC/CanIf/CanIfInitCfg/ISOx_NFC_FS_Resp_FD_XIX_HCP4_CANFD01_a19eac3a_Tx */ },  /* [/ActiveEcuC/CanIf/CanIfInitCfg/CHNL_2a45b2d1] */
  { /*     2 */             2u  /* /ActiveEcuC/CanIf/CanIfInitCfg/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_cddcb18d_Tx */  },  /* [/ActiveEcuC/CanIf/CanIfInitCfg/CHNL_2a45b2d1] */
  { /*     3 */             3u  /* /ActiveEcuC/CanIf/CanIfInitCfg/NFC_TGS_01_XIX_HCP4_CANFD01_6844ad20_Tx */          }   /* [/ActiveEcuC/CanIf/CanIfInitCfg/CHNL_2a45b2d1] */
};
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  CanIf_TxConfirmationFctList
**********************************************************************************************************************/
/** 
  \var    CanIf_TxConfirmationFctList
  \brief  Tx confirmation functions table.
*/ 
#define CANIF_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(CanIf_TxConfirmationFctType, CANIF_CONST) CanIf_TxConfirmationFctList[3] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     TxConfirmationFctList                      Referable Keys */
  /*     0 */ (CanIf_TxConfirmationFctType)NULL_PTR ,  /* [NULL_PTR] */
  /*     1 */ CanTp_TxConfirmation                  ,  /* [CanTp_TxConfirmation] */
  /*     2 */ PduR_CanIfTxConfirmation                 /* [PduR_CanIfTxConfirmation] */
};
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  CanIf_TxPduConfig
**********************************************************************************************************************/
/** 
  \var    CanIf_TxPduConfig
  \brief  Tx-PDUs - configuration.
  \details
  Element                     Description
  CanId                       CAN identifier (16bit / 32bit).
  UpperLayerTxPduId           Upper layer handle-Id (8bit / 16bit).
  IsTxPduTruncation           TRUE: Truncation of Tx-PDU is enabled, FALSE: Truncation of Tx-PDU is disabled
  CtrlStatesIdx               the index of the 1:1 relation pointing to CanIf_CtrlStates
  MailBoxConfigIdx            the index of the 1:1 relation pointing to CanIf_MailBoxConfig
  TxConfirmationFctListIdx    the index of the 1:1 relation pointing to CanIf_TxConfirmationFctList
  TxPduLength                 Tx-PDU length.
*/ 
#define CANIF_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(CanIf_TxPduConfigType, CANIF_CONST) CanIf_TxPduConfig[4] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    CanId        UpperLayerTxPduId                                                     IsTxPduTruncation  CtrlStatesIdx                                                                             MailBoxConfigIdx                                                                  TxConfirmationFctListIdx                                  TxPduLength        Comment                                                             Referable Keys */
  { /*     0 */ 0xDC460217u, CanTpConf_CanTpTxFcNPdu_CanTpTxFcNPdu_ca69bed7                      , TRUE             ,            0u  /* /ActiveEcuC/CanIf/CanIfCtrlDrvCfg_7d254554/CT_HCP4_CANFD01_a1aa3031 */,               0u  /* /ActiveEcuC/Can/CanConfigSet/CN_HCP4_CANFD01_152fd6c6_Tx */,                       1u  /* CanTp_TxConfirmation */    ,         64u },  /* [PDU: OBDC_NFC_FS_Resp_FD_XIX_HCP4_CANFD01_7bcf65c3_Tx] */  /* [/ActiveEcuC/CanIf/CanIfInitCfg/OBDC_NFC_FS_Resp_FD_XIX_HCP4_CANFD01_7bcf65c3_Tx] */
  { /*     1 */ 0xDC460017u, CanTpConf_CanTpTxFcNPdu_CanTpTxFcNPdu_f8c795a3                      , TRUE             ,            0u  /* /ActiveEcuC/CanIf/CanIfCtrlDrvCfg_7d254554/CT_HCP4_CANFD01_a1aa3031 */,               0u  /* /ActiveEcuC/Can/CanConfigSet/CN_HCP4_CANFD01_152fd6c6_Tx */,                       1u  /* CanTp_TxConfirmation */    ,         64u },  /* [PDU: ISOx_NFC_FS_Resp_FD_XIX_HCP4_CANFD01_a19eac3a_Tx] */  /* [/ActiveEcuC/CanIf/CanIfInitCfg/ISOx_NFC_FS_Resp_FD_XIX_HCP4_CANFD01_a19eac3a_Tx] */
  { /*     2 */ 0xDA7C45FFu, PduRConf_PduRDestPdu_DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f070f75_Tx, TRUE             ,            0u  /* /ActiveEcuC/CanIf/CanIfCtrlDrvCfg_7d254554/CT_HCP4_CANFD01_a1aa3031 */,               0u  /* /ActiveEcuC/Can/CanConfigSet/CN_HCP4_CANFD01_152fd6c6_Tx */,                       2u  /* PduR_CanIfTxConfirmation */,         64u },  /* [PDU: DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_cddcb18d_Tx]  */  /* [/ActiveEcuC/CanIf/CanIfInitCfg/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_cddcb18d_Tx] */
  { /*     3 */ 0xD6A9549Eu, PduRConf_PduRDestPdu_NFC_TGS_01_XIX_HCP4_CANFD01_a49c5cba_Tx        , TRUE             ,            0u  /* /ActiveEcuC/CanIf/CanIfCtrlDrvCfg_7d254554/CT_HCP4_CANFD01_a1aa3031 */,               0u  /* /ActiveEcuC/Can/CanConfigSet/CN_HCP4_CANFD01_152fd6c6_Tx */,                       2u  /* PduR_CanIfTxConfirmation */,          8u }   /* [PDU: NFC_TGS_01_XIX_HCP4_CANFD01_6844ad20_Tx]          */  /* [/ActiveEcuC/CanIf/CanIfInitCfg/NFC_TGS_01_XIX_HCP4_CANFD01_6844ad20_Tx] */
};
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  CanIf_TxPduQueueIndex
**********************************************************************************************************************/
/** 
  \var    CanIf_TxPduQueueIndex
  \brief  Indirection table: Tx-PDU handle-Id to corresponding Tx buffer handle-Id. NOTE: Only BasicCAN Tx-PDUs have a valid indirection into the Tx buffer.
  \details
  Element                          Description
  TxQueueIdx                       the index of the 0:1 relation pointing to CanIf_TxQueue
  TxQueueIndex2DataStartStopIdx    the index of the 0:1 relation pointing to CanIf_TxQueueIndex2DataStartStop
*/ 
#define CANIF_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(CanIf_TxPduQueueIndexType, CANIF_CONST) CanIf_TxPduQueueIndex[4] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    TxQueueIdx                                                                                         TxQueueIndex2DataStartStopIdx                                                                                               Comment                                                                                       Referable Keys */
  { /*     0 */         0u  /* /ActiveEcuC/CanIf/CanIfInitCfg/OBDC_NFC_FS_Resp_FD_XIX_HCP4_CANFD01_7bcf65c3_Tx */,                            0u  /* /ActiveEcuC/CanIf/CanIfInitCfg/OBDC_NFC_FS_Resp_FD_XIX_HCP4_CANFD01_7bcf65c3_Tx */ },  /* [OBDC_NFC_FS_Resp_FD_XIX_HCP4_CANFD01_7bcf65c3_Tx, BasicCAN TxPdu with Tx-buffer] */  /* [/ActiveEcuC/CanIf/CanIfInitCfg/OBDC_NFC_FS_Resp_FD_XIX_HCP4_CANFD01_7bcf65c3_Tx, /ActiveEcuC/CanIf/CanIfCtrlDrvCfg_7d254554/CT_HCP4_CANFD01_a1aa3031] */
  { /*     1 */         1u  /* /ActiveEcuC/CanIf/CanIfInitCfg/ISOx_NFC_FS_Resp_FD_XIX_HCP4_CANFD01_a19eac3a_Tx */,                            1u  /* /ActiveEcuC/CanIf/CanIfInitCfg/ISOx_NFC_FS_Resp_FD_XIX_HCP4_CANFD01_a19eac3a_Tx */ },  /* [ISOx_NFC_FS_Resp_FD_XIX_HCP4_CANFD01_a19eac3a_Tx, BasicCAN TxPdu with Tx-buffer] */  /* [/ActiveEcuC/CanIf/CanIfInitCfg/ISOx_NFC_FS_Resp_FD_XIX_HCP4_CANFD01_a19eac3a_Tx, /ActiveEcuC/CanIf/CanIfCtrlDrvCfg_7d254554/CT_HCP4_CANFD01_a1aa3031] */
  { /*     2 */         2u  /* /ActiveEcuC/CanIf/CanIfInitCfg/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_cddcb18d_Tx */ ,                            2u  /* /ActiveEcuC/CanIf/CanIfInitCfg/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_cddcb18d_Tx */  },  /* [DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_cddcb18d_Tx, BasicCAN TxPdu with Tx-buffer]  */  /* [/ActiveEcuC/CanIf/CanIfInitCfg/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_cddcb18d_Tx, /ActiveEcuC/CanIf/CanIfCtrlDrvCfg_7d254554/CT_HCP4_CANFD01_a1aa3031] */
  { /*     3 */         3u  /* /ActiveEcuC/CanIf/CanIfInitCfg/NFC_TGS_01_XIX_HCP4_CANFD01_6844ad20_Tx */         ,                            3u  /* /ActiveEcuC/CanIf/CanIfInitCfg/NFC_TGS_01_XIX_HCP4_CANFD01_6844ad20_Tx */          }   /* [NFC_TGS_01_XIX_HCP4_CANFD01_6844ad20_Tx, BasicCAN TxPdu with Tx-buffer]          */  /* [/ActiveEcuC/CanIf/CanIfInitCfg/NFC_TGS_01_XIX_HCP4_CANFD01_6844ad20_Tx, /ActiveEcuC/CanIf/CanIfCtrlDrvCfg_7d254554/CT_HCP4_CANFD01_a1aa3031] */
};
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  CanIf_TxQueueIndex2DataStartStop
**********************************************************************************************************************/
/** 
  \var    CanIf_TxQueueIndex2DataStartStop
  \details
  Element                Description
  TxQueueDataEndIdx      the end index of the 0:n relation pointing to CanIf_TxQueueData
  TxQueueDataLength      the number of relations pointing to CanIf_TxQueueData
  TxQueueDataStartIdx    the start index of the 0:n relation pointing to CanIf_TxQueueData
*/ 
#define CANIF_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(CanIf_TxQueueIndex2DataStartStopType, CANIF_CONST) CanIf_TxQueueIndex2DataStartStop[4] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    TxQueueDataEndIdx                                                                                         TxQueueDataLength                                                                                         TxQueueDataStartIdx                                                                                               Comment                                                                Referable Keys */
  { /*     0 */               64u  /* /ActiveEcuC/CanIf/CanIfInitCfg/OBDC_NFC_FS_Resp_FD_XIX_HCP4_CANFD01_7bcf65c3_Tx */,               64u  /* /ActiveEcuC/CanIf/CanIfInitCfg/OBDC_NFC_FS_Resp_FD_XIX_HCP4_CANFD01_7bcf65c3_Tx */,                  0u  /* /ActiveEcuC/CanIf/CanIfInitCfg/OBDC_NFC_FS_Resp_FD_XIX_HCP4_CANFD01_7bcf65c3_Tx */ },  /* [Tx-PDU: OBDC_NFC_FS_Resp_FD_XIX_HCP4_CANFD01_7bcf65c3_Tx] */  /* [/ActiveEcuC/CanIf/CanIfInitCfg/OBDC_NFC_FS_Resp_FD_XIX_HCP4_CANFD01_7bcf65c3_Tx] */
  { /*     1 */              128u  /* /ActiveEcuC/CanIf/CanIfInitCfg/ISOx_NFC_FS_Resp_FD_XIX_HCP4_CANFD01_a19eac3a_Tx */,               64u  /* /ActiveEcuC/CanIf/CanIfInitCfg/ISOx_NFC_FS_Resp_FD_XIX_HCP4_CANFD01_a19eac3a_Tx */,                 64u  /* /ActiveEcuC/CanIf/CanIfInitCfg/ISOx_NFC_FS_Resp_FD_XIX_HCP4_CANFD01_a19eac3a_Tx */ },  /* [Tx-PDU: ISOx_NFC_FS_Resp_FD_XIX_HCP4_CANFD01_a19eac3a_Tx] */  /* [/ActiveEcuC/CanIf/CanIfInitCfg/ISOx_NFC_FS_Resp_FD_XIX_HCP4_CANFD01_a19eac3a_Tx] */
  { /*     2 */              192u  /* /ActiveEcuC/CanIf/CanIfInitCfg/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_cddcb18d_Tx */ ,               64u  /* /ActiveEcuC/CanIf/CanIfInitCfg/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_cddcb18d_Tx */ ,                128u  /* /ActiveEcuC/CanIf/CanIfInitCfg/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_cddcb18d_Tx */  },  /* [Tx-PDU: DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_cddcb18d_Tx]  */  /* [/ActiveEcuC/CanIf/CanIfInitCfg/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_cddcb18d_Tx] */
  { /*     3 */              200u  /* /ActiveEcuC/CanIf/CanIfInitCfg/NFC_TGS_01_XIX_HCP4_CANFD01_6844ad20_Tx */         ,                8u  /* /ActiveEcuC/CanIf/CanIfInitCfg/NFC_TGS_01_XIX_HCP4_CANFD01_6844ad20_Tx */         ,                192u  /* /ActiveEcuC/CanIf/CanIfInitCfg/NFC_TGS_01_XIX_HCP4_CANFD01_6844ad20_Tx */          }   /* [Tx-PDU: NFC_TGS_01_XIX_HCP4_CANFD01_6844ad20_Tx]          */  /* [/ActiveEcuC/CanIf/CanIfInitCfg/NFC_TGS_01_XIX_HCP4_CANFD01_6844ad20_Tx] */
};
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  CanIf_WakeUpConfig
**********************************************************************************************************************/
/** 
  \var    CanIf_WakeUpConfig
  \brief  Wake-up source configuration
  \details
  Element                Description
  ControllerId           ControllerId of this wake-up source configuration
  WakeUpSource           Wake-up source identifier
  WakeUpTargetAddress    Target address of wake up source (driver independent handle Id): CAN controller (ControllerId)/CAN transceiver (TransceiverId)
  WakeUpTargetModule     Target module of wake-up source: CAN driver/CAN transceiver driver
*/ 
#define CANIF_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(CanIf_WakeUpConfigType, CANIF_CONST) CanIf_WakeUpConfig[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    ControllerId  WakeUpSource  WakeUpTargetAddress  WakeUpTargetModule             Comment */
  { /*     0 */           0u,          32u,                  0u, CANIF_WAKEUPREQUEST_CAN } 
};
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  CanIf_WakeUpValidationFctPtr
**********************************************************************************************************************/
#define CANIF_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(CanIf_WakeUpValidationFctType, CANIF_CONST) CanIf_WakeUpValidationFctPtr = EcuM_ValidateWakeupEvent;  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  CanIf_CtrlStates
**********************************************************************************************************************/
/** 
  \var    CanIf_CtrlStates
  \details
  Element                  Description
  CtrlMode                 Controller mode.
  PduMode                  PDU mode state.
  WakeUpValidationState    Wake-up validation state.
*/ 
#define CANIF_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(CanIf_CtrlStatesUType, CANIF_VAR_NOINIT) CanIf_CtrlStates;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/CanIf/CanIfCtrlDrvCfg_7d254554/CT_HCP4_CANFD01_a1aa3031] */

#define CANIF_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  CanIf_TxBufferPrioByCanIdBase
**********************************************************************************************************************/
/** 
  \var    CanIf_TxBufferPrioByCanIdBase
  \brief  Variable declaration - Tx-buffer: PRIO_BY_CANID as byte/bit-queue. Stores at least the QueueCounter.
*/ 
#define CANIF_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(CanIf_TxBufferPrioByCanIdBaseUType, CANIF_VAR_NOINIT) CanIf_TxBufferPrioByCanIdBase;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/CanIf/CanIfInitCfg/CHNL_2a45b2d1] */

#define CANIF_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  CanIf_TxQueue
**********************************************************************************************************************/
/** 
  \var    CanIf_TxQueue
  \brief  Variable declaration - Tx byte queue.
*/ 
#define CANIF_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(CanIf_TxQueueUType, CANIF_VAR_NOINIT) CanIf_TxQueue;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/CanIf/CanIfInitCfg/OBDC_NFC_FS_Resp_FD_XIX_HCP4_CANFD01_7bcf65c3_Tx] */
  /*     1 */  /* [/ActiveEcuC/CanIf/CanIfInitCfg/ISOx_NFC_FS_Resp_FD_XIX_HCP4_CANFD01_a19eac3a_Tx] */
  /*     2 */  /* [/ActiveEcuC/CanIf/CanIfInitCfg/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_cddcb18d_Tx] */
  /*     3 */  /* [/ActiveEcuC/CanIf/CanIfInitCfg/NFC_TGS_01_XIX_HCP4_CANFD01_6844ad20_Tx] */

#define CANIF_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  CanIf_TxQueueData
**********************************************************************************************************************/
/** 
  \var    CanIf_TxQueueData
  \brief  Variable declaration - Tx queue data.
*/ 
#define CANIF_START_SEC_VAR_FAST_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(CanIf_TxQueueDataUType, CANIF_VAR_NOINIT_FAST) CanIf_TxQueueData;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/CanIf/CanIfInitCfg/OBDC_NFC_FS_Resp_FD_XIX_HCP4_CANFD01_7bcf65c3_Tx] */
  /*   ... */  /* [/ActiveEcuC/CanIf/CanIfInitCfg/OBDC_NFC_FS_Resp_FD_XIX_HCP4_CANFD01_7bcf65c3_Tx] */
  /*    63 */  /* [/ActiveEcuC/CanIf/CanIfInitCfg/OBDC_NFC_FS_Resp_FD_XIX_HCP4_CANFD01_7bcf65c3_Tx] */
  /*    64 */  /* [/ActiveEcuC/CanIf/CanIfInitCfg/ISOx_NFC_FS_Resp_FD_XIX_HCP4_CANFD01_a19eac3a_Tx] */
  /*   ... */  /* [/ActiveEcuC/CanIf/CanIfInitCfg/ISOx_NFC_FS_Resp_FD_XIX_HCP4_CANFD01_a19eac3a_Tx] */
  /*   127 */  /* [/ActiveEcuC/CanIf/CanIfInitCfg/ISOx_NFC_FS_Resp_FD_XIX_HCP4_CANFD01_a19eac3a_Tx] */
  /*   128 */  /* [/ActiveEcuC/CanIf/CanIfInitCfg/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_cddcb18d_Tx] */
  /*   ... */  /* [/ActiveEcuC/CanIf/CanIfInitCfg/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_cddcb18d_Tx] */
  /*   191 */  /* [/ActiveEcuC/CanIf/CanIfInitCfg/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_cddcb18d_Tx] */
  /*   192 */  /* [/ActiveEcuC/CanIf/CanIfInitCfg/NFC_TGS_01_XIX_HCP4_CANFD01_6844ad20_Tx] */
  /*   ... */  /* [/ActiveEcuC/CanIf/CanIfInitCfg/NFC_TGS_01_XIX_HCP4_CANFD01_6844ad20_Tx] */
  /*   199 */  /* [/ActiveEcuC/CanIf/CanIfInitCfg/NFC_TGS_01_XIX_HCP4_CANFD01_6844ad20_Tx] */

#define CANIF_STOP_SEC_VAR_FAST_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */


/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL DATA
**********************************************************************************************************************/



