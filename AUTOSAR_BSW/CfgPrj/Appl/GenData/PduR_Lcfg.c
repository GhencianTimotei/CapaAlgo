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
 *            Module: PduR
 *           Program: VAG AR4 (MSR_Vag_SLP5)
 *          Customer: Huf H_lsbeck & F_rst GmbH & Co. KG
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: S32K144
 *    License Scope : The usage is restricted to CBD2100188_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: PduR_Lcfg.c
 *   Generation Time: 2024-01-27 22:50:07
 *           Project: DaVinciConfigurationS32K144 - Version 1.0
 *          Delivery: CBD2100188_D01
 *      Tool Version: DaVinci Configurator  5.23.45 SP4
 *
 *
 *********************************************************************************************************************/

#define PDUR_LCFG_SOURCE

/**********************************************************************************************************************
 * MISRA / PCLINT JUSTIFICATION
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "PduR.h"
#include "PduR_Fm.h"
#include "PduR_IFQ.h"
#include "PduR_Sm.h"
#include "PduR_RmIf.h"
#include "PduR_RmTp.h"
#include "PduR_RmTp_TxInst.h"
#include "SchM_PduR.h"
#if(PDUR_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif
# include "PduR_Lcfg.h"



/* Include headers with callbacks */
#include "PduR_CanIf.h"
#include "PduR_CanTp.h"
#include "PduR_Com.h"
#include "PduR_Dcm.h"


/**********************************************************************************************************************
 * LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/* Exclusive Area Wrapper functions */
static FUNC(void, PDUR_CODE) PduR_SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_0(void);
static FUNC(void, PDUR_CODE) PduR_SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_0(void);
  
/**********************************************************************************************************************
 * LOCAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * GLOBAL DATA
 *********************************************************************************************************************/
/* \trace SPEC-663, SPEC-661 */

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA
**********************************************************************************************************************/
/**********************************************************************************************************************
  PduR_ExclusiveAreaRom
**********************************************************************************************************************/
/** 
  \var    PduR_ExclusiveAreaRom
  \brief  PduR Exclusive Area Locks
  \details
  Element    Description
  Lock       Lock function
  Unlock     Unlock function
*/ 
#define PDUR_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(PduR_ExclusiveAreaRomType, PDUR_CONST) PduR_ExclusiveAreaRom[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    Lock                                        Unlock                                           Referable Keys */
  { /*     0 */ PduR_SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_0, PduR_SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_0 }   /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRLock_PduRExclusiveArea] */
};
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  PduR_GeneralPropertiesRom
**********************************************************************************************************************/
/** 
  \var    PduR_GeneralPropertiesRom
  \brief  General Properties Switches of the PduR.
  \details
  Element         Description
  hasIfRouting
*/ 
#define PDUR_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(PduR_GeneralPropertiesRomType, PDUR_CONST) PduR_GeneralPropertiesRom[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    hasIfRouting        Referable Keys */
  { /*     0 */         TRUE }   /* [/ActiveEcuC/PduR] */
};
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  PduR_MmRom
**********************************************************************************************************************/
/** 
  \var    PduR_MmRom
  \brief  Module manager: Contains all function pointers of the bordering modules.
  \details
  Element                       Description
  MaskedBits                    contains bitcoded the boolean data of PduR_LoIfOfMmRom, PduR_LoTpOfMmRom, PduR_TpCancelTransmitSupportedOfMmRom, PduR_UpIfOfMmRom, PduR_UpTpOfMmRom
  LoTpCancelTransmitFctPtr      Lower layer cancel transmit function pointers.
  UpTpCopyRxDataFctPtr          Transport protocol CopyRxData function pointers
  UpTpCopyTxDataFctPtr          Transport protocol CopyTxData function pointers
  UpIfRxIndicationFctPtr        Upper layer communication interface Rx indication function pointers.
  UpIfTxConfirmationFctPtr      Upper layer communication interface Tx confimation function pointers
  UpTpStartOfReceptionFctPtr    Transport protocol StartOfReception function pointers
  UpTpTpRxIndicationFctPtr      Transport protocol TpRxIndication function pointers
  UpTpTpTxConfirmationFctPtr    Transport protocol TpTxConfimation function pointers
  LoIfTransmitFctPtr            Lower layer If transmit function pointers
  LoTpTransmitFctPtr            Lower layer Tp transmit function pointers
*/ 
#define PDUR_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(PduR_MmRomType, PDUR_CONST) PduR_MmRom[4] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    MaskedBits  LoTpCancelTransmitFctPtr  UpTpCopyRxDataFctPtr  UpTpCopyTxDataFctPtr  UpIfRxIndicationFctPtr  UpIfTxConfirmationFctPtr  UpTpStartOfReceptionFctPtr  UpTpTpRxIndicationFctPtr  UpTpTpTxConfirmationFctPtr  LoIfTransmitFctPtr  LoTpTransmitFctPtr        Referable Keys */
  { /*     0 */      0x10u, NULL_PTR                , NULL_PTR            , NULL_PTR            , NULL_PTR              , NULL_PTR                , NULL_PTR                  , NULL_PTR                , NULL_PTR                  , CanIf_Transmit    , NULL_PTR           },  /* [/ActiveEcuC/PduR/CanIf] */
  { /*     1 */      0x0Cu, CanTp_CancelTransmit    , NULL_PTR            , NULL_PTR            , NULL_PTR              , NULL_PTR                , NULL_PTR                  , NULL_PTR                , NULL_PTR                  , NULL_PTR          , CanTp_Transmit     },  /* [/ActiveEcuC/PduR/CanTp] */
  { /*     2 */      0x02u, NULL_PTR                , NULL_PTR            , NULL_PTR            , Com_RxIndication      , Com_TxConfirmation      , NULL_PTR                  , NULL_PTR                , NULL_PTR                  , NULL_PTR          , NULL_PTR           },  /* [/ActiveEcuC/PduR/Com] */
  { /*     3 */      0x01u, NULL_PTR                , Dcm_CopyRxData      , Dcm_CopyTxData      , NULL_PTR              , NULL_PTR                , Dcm_StartOfReception      , Dcm_TpRxIndication      , Dcm_TpTxConfirmation      , NULL_PTR          , NULL_PTR           }   /* [/ActiveEcuC/PduR/Dcm] */
};
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  PduR_PartitionIdentifiers
**********************************************************************************************************************/
/** 
  \var    PduR_PartitionIdentifiers
  \brief  the partition context in Config
  \details
  Element         Description
  PartitionSNV
*/ 
#define PDUR_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(PduR_PartitionIdentifiersType, PDUR_CONST) PduR_PartitionIdentifiers[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    PartitionSNV       */
  { /*     0 */ CommonSharedMemory }
};
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  PduR_RmDestRom
**********************************************************************************************************************/
/** 
  \var    PduR_RmDestRom
  \brief  PduR RoutiongPathManager destPdu Table
  \details
  Element                      Description
  PartitionIndexOfCsl      
  PduLengthHandlingStrategy    The strategy how larger than configured If Pdus are handled.
  RmGDestRomIdx                the index of the 1:1 relation pointing to PduR_RmGDestRom
  RmSrcRomIdx                  the index of the 1:1 relation pointing to PduR_RmSrcRom
  RoutingType                  Type of the Routing (API Forwarding, Gateway).
*/ 
#define PDUR_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(PduR_RmDestRomType, PDUR_CONST) PduR_RmDestRom[9] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    PartitionIndexOfCsl                            PduLengthHandlingStrategy                         RmGDestRomIdx  RmSrcRomIdx  RoutingType                                                 Comment                                                                                                                                         Referable Keys */
  { /*     0 */                  0u  /* CommonSharedMemory */, PDUR_IGNORE_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM,            8u,          8u, PDUR_IF_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM },  /* [PduRDestPdu: NFC_TGS_01_XIX_HCP4_CANFD01_a49c5cba_Tx]                                                                              */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/NFC_TGS_01_XIX_HCP4_CANFD01_6816bdec_Tx/PduRSrcPdu_2470bef4, /ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/NFC_TGS_01_XIX_HCP4_CANFD01_6816bdec_Tx/NFC_TGS_01_XIX_HCP4_CANFD01_a49c5cba_Tx] */
  { /*     1 */                  0u  /* CommonSharedMemory */, PDUR_UNUSED_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM,            1u,          2u, PDUR_TP_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM },  /* [PduRDestPdu: DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_ISO_Diagnose_XIX_0x1C440017_XIX_0x1C460017_XIX_Physical_985372e6_Rx_502ae7e6_Rx]  */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_ISO_Diagnose_XIX_0x1C440017_XIX_0x1C460017_XIX_Physical_985372e6_Rx/PduRSrcPdu_502ae7e6, /ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_ISO_Diagnose_XIX_0x1C440017_XIX_0x1C460017_XIX_Physical_985372e6_Rx/DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_ISO_Diagnose_XIX_0x1C440017_XIX_0x1C460017_XIX_Physical_985372e6_Rx_502ae7e6_Rx] */
  { /*     2 */                  0u  /* CommonSharedMemory */, PDUR_IGNORE_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM,            7u,          0u, PDUR_IF_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM },  /* [PduRDestPdu: DoorFunctions_FS_01_XIX_HCP4_CANFD01_ea42fd8e_Rx_660745f7_Rx]                                                         */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/DoorFunctions_FS_01_XIX_HCP4_CANFD01_ea42fd8e_Rx/PduRSrcPdu_660745f7, /ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/DoorFunctions_FS_01_XIX_HCP4_CANFD01_ea42fd8e_Rx/DoorFunctions_FS_01_XIX_HCP4_CANFD01_ea42fd8e_Rx_660745f7_Rx] */
  { /*     3 */                  0u  /* CommonSharedMemory */, PDUR_UNUSED_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM,            3u,          3u, PDUR_TP_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM },  /* [PduRDestPdu: DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_OBDC_Diagnose_XIX_0x1C410200_XIX_Functional_bb5cab1c_Rx_7bfad7e5_Rx]              */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_OBDC_Diagnose_XIX_0x1C410200_XIX_Functional_bb5cab1c_Rx/PduRSrcPdu_7bfad7e5, /ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_OBDC_Diagnose_XIX_0x1C410200_XIX_Functional_bb5cab1c_Rx/DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_OBDC_Diagnose_XIX_0x1C410200_XIX_Functional_bb5cab1c_Rx_7bfad7e5_Rx] */
  { /*     4 */                  0u  /* CommonSharedMemory */, PDUR_UNUSED_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM,            0u,          1u, PDUR_TP_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM },  /* [PduRDestPdu: DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_ISO_Diagnose_XIX_0x1C410000_XIX_Functional_d6ea4aab_Rx_a386612b_Rx]               */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_ISO_Diagnose_XIX_0x1C410000_XIX_Functional_d6ea4aab_Rx/PduRSrcPdu_a386612b, /ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_ISO_Diagnose_XIX_0x1C410000_XIX_Functional_d6ea4aab_Rx/DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_ISO_Diagnose_XIX_0x1C410000_XIX_Functional_d6ea4aab_Rx_a386612b_Rx] */
  { /*     5 */                  0u  /* CommonSharedMemory */, PDUR_UNUSED_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM,            5u,          6u, PDUR_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM },  /* [PduRDestPdu: DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_OBDC_Diagnose_XIX_0x1C460217_XIX_0x1C440217_XIX_Physical_03bb716b_Tx]             */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_OBDC_Diagnose_XIX_0x1C460217_XIX_0x1C440217_XIX_Physical_c4e0b3c7_Tx/PduRSrcPdu_a9d87b23, /ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_OBDC_Diagnose_XIX_0x1C460217_XIX_0x1C440217_XIX_Physical_c4e0b3c7_Tx/DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_OBDC_Diagnose_XIX_0x1C460217_XIX_0x1C440217_XIX_Physical_03bb716b_Tx] */
  { /*     6 */                  0u  /* CommonSharedMemory */, PDUR_UNUSED_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM,            2u,          5u, PDUR_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM },  /* [PduRDestPdu: DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_ISO_Diagnose_XIX_0x1C460017_XIX_0x1C440017_XIX_Physical_59ac3609_Tx]              */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_ISO_Diagnose_XIX_0x1C460017_XIX_0x1C440017_XIX_Physical_16591cf2_Tx/PduRSrcPdu_bbe61e78, /ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_ISO_Diagnose_XIX_0x1C460017_XIX_0x1C440017_XIX_Physical_16591cf2_Tx/DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_ISO_Diagnose_XIX_0x1C460017_XIX_0x1C440017_XIX_Physical_59ac3609_Tx] */
  { /*     7 */                  0u  /* CommonSharedMemory */, PDUR_IGNORE_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM,            6u,          7u, PDUR_IF_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM },  /* [PduRDestPdu: DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f070f75_Tx]                                                                      */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx/PduRSrcPdu_f6736a3d, /ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f070f75_Tx] */
  { /*     8 */                  0u  /* CommonSharedMemory */, PDUR_UNUSED_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM,            4u,          4u, PDUR_TP_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM }   /* [PduRDestPdu: DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_OBDC_Diagnose_XIX_0x1C440217_XIX_0x1C460217_XIX_Physical_c2443584_Rx_f9ee37ce_Rx] */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_OBDC_Diagnose_XIX_0x1C440217_XIX_0x1C460217_XIX_Physical_c2443584_Rx/PduRSrcPdu_f9ee37ce, /ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_OBDC_Diagnose_XIX_0x1C440217_XIX_0x1C460217_XIX_Physical_c2443584_Rx/DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_OBDC_Diagnose_XIX_0x1C440217_XIX_0x1C460217_XIX_Physical_c2443584_Rx_f9ee37ce_Rx] */
};
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  PduR_RmGDestRom
**********************************************************************************************************************/
/** 
  \var    PduR_RmGDestRom
  \brief  PduR RoutingPathManager global destPdu Table
  \details
  Element         Description
  MaxPduLength    Configured PduLength + metadata length.
  DestHnd         handle to be used as parameter for the StartOfReception, CopyRxData, Transmit or RxIndication function call.
  Direction       Direction of this Pdu: Rx or Tx
  LockRomIdx      the index of the 1:1 relation pointing to PduR_LockRom
  MmRomIdx        the index of the 1:1 relation pointing to PduR_MmRom
  RmDestRomIdx    the index of the 1:1 relation pointing to PduR_RmDestRom
*/ 
#define PDUR_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(PduR_RmGDestRomType, PDUR_CONST) PduR_RmGDestRom[9] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    MaxPduLength  DestHnd                                                                                                                                     Direction                      LockRomIdx  MmRomIdx  RmDestRomIdx        Comment                                                                                                                                    Referable Keys */
  { /*     0 */          62u,               DcmConf_DcmDslProtocolRx_DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_ISO_Diagnose_XIX_0x1C410000_XIX_Functional_db157806_Rx_bbe8a62f, PDUR_RX_DIRECTIONOFRMGDESTROM,         0u,       3u,           4u },  /* [Global PduRDestPdu: DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_ISO_Diagnose_XIX_0x1C410000_XIX_Functional_db157806_Rx]               */  /* [/ActiveEcuC/EcuC/EcucPduCollection/DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_ISO_Diagnose_XIX_0x1C410000_XIX_Functional_db157806_Rx, /ActiveEcuC/PduR/Dcm, PduRSinglePartitionDummy] */
  { /*     1 */         512u,  DcmConf_DcmDslProtocolRx_DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_ISO_Diagnose_XIX_0x1C440017_XIX_0x1C460017_XIX_Physical_7e685697_Rx_4a9d0915, PDUR_RX_DIRECTIONOFRMGDESTROM,         0u,       3u,           1u },  /* [Global PduRDestPdu: DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_ISO_Diagnose_XIX_0x1C440017_XIX_0x1C460017_XIX_Physical_7e685697_Rx]  */  /* [/ActiveEcuC/EcuC/EcucPduCollection/DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_ISO_Diagnose_XIX_0x1C440017_XIX_0x1C460017_XIX_Physical_7e685697_Rx, /ActiveEcuC/PduR/Dcm, PduRSinglePartitionDummy] */
  { /*     2 */         512u,                                                                                                 CanTpConf_CanTpTxNSdu_CanTpTxNSdu_93bc2a6a, PDUR_TX_DIRECTIONOFRMGDESTROM,         0u,       1u,           6u },  /* [Global PduRDestPdu: DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_ISO_Diagnose_XIX_0x1C460017_XIX_0x1C440017_XIX_Physical_59ac3609_Tx]  */  /* [/ActiveEcuC/EcuC/EcucPduCollection/DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_ISO_Diagnose_XIX_0x1C460017_XIX_0x1C440017_XIX_Physical_59ac3609_Tx, /ActiveEcuC/PduR/CanTp, PduRSinglePartitionDummy] */
  { /*     3 */          62u,              DcmConf_DcmDslProtocolRx_DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_OBDC_Diagnose_XIX_0x1C410200_XIX_Functional_3877eb8c_Rx_08e97bb6, PDUR_RX_DIRECTIONOFRMGDESTROM,         0u,       3u,           3u },  /* [Global PduRDestPdu: DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_OBDC_Diagnose_XIX_0x1C410200_XIX_Functional_3877eb8c_Rx]              */  /* [/ActiveEcuC/EcuC/EcucPduCollection/DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_OBDC_Diagnose_XIX_0x1C410200_XIX_Functional_3877eb8c_Rx, /ActiveEcuC/PduR/Dcm, PduRSinglePartitionDummy] */
  { /*     4 */         512u, DcmConf_DcmDslProtocolRx_DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_OBDC_Diagnose_XIX_0x1C440217_XIX_0x1C460217_XIX_Physical_acd1f9a2_Rx_3c30689f, PDUR_RX_DIRECTIONOFRMGDESTROM,         0u,       3u,           8u },  /* [Global PduRDestPdu: DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_OBDC_Diagnose_XIX_0x1C440217_XIX_0x1C460217_XIX_Physical_acd1f9a2_Rx] */  /* [/ActiveEcuC/EcuC/EcucPduCollection/DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_OBDC_Diagnose_XIX_0x1C440217_XIX_0x1C460217_XIX_Physical_acd1f9a2_Rx, /ActiveEcuC/PduR/Dcm, PduRSinglePartitionDummy] */
  { /*     5 */         512u,                                                                                                 CanTpConf_CanTpTxNSdu_CanTpTxNSdu_eb2a73c9, PDUR_TX_DIRECTIONOFRMGDESTROM,         0u,       1u,           5u },  /* [Global PduRDestPdu: DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_OBDC_Diagnose_XIX_0x1C460217_XIX_0x1C440217_XIX_Physical_03bb716b_Tx] */  /* [/ActiveEcuC/EcuC/EcucPduCollection/DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_OBDC_Diagnose_XIX_0x1C460217_XIX_0x1C440217_XIX_Physical_03bb716b_Tx, /ActiveEcuC/PduR/CanTp, PduRSinglePartitionDummy] */
  { /*     6 */          64u,                                                                    CanIfConf_CanIfTxPduCfg_DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_cddcb18d_Tx, PDUR_TX_DIRECTIONOFRMGDESTROM,         0u,       0u,           7u },  /* [Global PduRDestPdu: DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f070f75_Tx]                                                          */  /* [/ActiveEcuC/EcuC/EcucPduCollection/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f070f75_Tx, /ActiveEcuC/PduR/CanIf, PduRSinglePartitionDummy] */
  { /*     7 */          60u,                                                                           ComConf_ComIPdu_DoorFunctions_FS_01_XIX_HCP4_CANFD01_92a39409_Rx, PDUR_RX_DIRECTIONOFRMGDESTROM,         0u,       2u,           2u },  /* [Global PduRDestPdu: DoorFunctions_FS_01_XIX_HCP4_CANFD01_92a39409_Rx]                                                         */  /* [/ActiveEcuC/EcuC/EcucPduCollection/DoorFunctions_FS_01_XIX_HCP4_CANFD01_92a39409_Rx, /ActiveEcuC/PduR/Com, PduRSinglePartitionDummy] */
  { /*     8 */           8u,                                                                            CanIfConf_CanIfTxPduCfg_NFC_TGS_01_XIX_HCP4_CANFD01_6844ad20_Tx, PDUR_TX_DIRECTIONOFRMGDESTROM,         0u,       0u,           0u }   /* [Global PduRDestPdu: NFC_TGS_01_XIX_HCP4_CANFD01_a49c5cba_Tx]                                                                  */  /* [/ActiveEcuC/EcuC/EcucPduCollection/NFC_TGS_01_XIX_HCP4_CANFD01_a49c5cba_Tx, /ActiveEcuC/PduR/CanIf, PduRSinglePartitionDummy] */
};
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  PduR_RmSrcRom
**********************************************************************************************************************/
/** 
  \var    PduR_RmSrcRom
  \brief  PduR RoutiongManager SrcPdu Table
  \details
  Element              Description
  LockRomIdx           the index of the 1:1 relation pointing to PduR_LockRom
  MmRomIdx             the index of the 1:1 relation pointing to PduR_MmRom
  RmDestRomStartIdx    the start index of the 1:n relation pointing to PduR_RmDestRom
  SrcHnd               handle to be used as parameter for the TxConfirmation or TriggerTransmit function call.
*/ 
#define PDUR_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(PduR_RmSrcRomType, PDUR_CONST) PduR_RmSrcRom[9] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    LockRomIdx  MmRomIdx  RmDestRomStartIdx  SrcHnd                                                                                                                                            Comment                                       Referable Keys */
  { /*     0 */         0u,       0u,                2u,                                                                                                                   PDUR_NO_SRCHNDOFRMSRCROM },  /* [PduRSrcPdu: PduRSrcPdu_660745f7] */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/DoorFunctions_FS_01_XIX_HCP4_CANFD01_ea42fd8e_Rx/PduRSrcPdu_660745f7] */
  { /*     1 */         0u,       1u,                4u,                                                                                                                   PDUR_NO_SRCHNDOFRMSRCROM },  /* [PduRSrcPdu: PduRSrcPdu_a386612b] */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_ISO_Diagnose_XIX_0x1C410000_XIX_Functional_d6ea4aab_Rx/PduRSrcPdu_a386612b] */
  { /*     2 */         0u,       1u,                1u,                                                                                                                   PDUR_NO_SRCHNDOFRMSRCROM },  /* [PduRSrcPdu: PduRSrcPdu_502ae7e6] */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_ISO_Diagnose_XIX_0x1C440017_XIX_0x1C460017_XIX_Physical_985372e6_Rx/PduRSrcPdu_502ae7e6] */
  { /*     3 */         0u,       1u,                3u,                                                                                                                   PDUR_NO_SRCHNDOFRMSRCROM },  /* [PduRSrcPdu: PduRSrcPdu_7bfad7e5] */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_OBDC_Diagnose_XIX_0x1C410200_XIX_Functional_bb5cab1c_Rx/PduRSrcPdu_7bfad7e5] */
  { /*     4 */         0u,       1u,                8u,                                                                                                                   PDUR_NO_SRCHNDOFRMSRCROM },  /* [PduRSrcPdu: PduRSrcPdu_f9ee37ce] */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_OBDC_Diagnose_XIX_0x1C440217_XIX_0x1C460217_XIX_Physical_c2443584_Rx/PduRSrcPdu_f9ee37ce] */
  { /*     5 */         0u,       3u,                6u,  DcmConf_DcmDslProtocolTx_DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_ISO_Diagnose_XIX_0x1C460017_XIX_0x1C440017_XIX_Physical_16591cf2_Tx_927be076 },  /* [PduRSrcPdu: PduRSrcPdu_bbe61e78] */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_ISO_Diagnose_XIX_0x1C460017_XIX_0x1C440017_XIX_Physical_16591cf2_Tx/PduRSrcPdu_bbe61e78] */
  { /*     6 */         0u,       3u,                5u, DcmConf_DcmDslProtocolTx_DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_OBDC_Diagnose_XIX_0x1C460217_XIX_0x1C440217_XIX_Physical_c4e0b3c7_Tx_4e49cbda },  /* [PduRSrcPdu: PduRSrcPdu_a9d87b23] */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_OBDC_Diagnose_XIX_0x1C460217_XIX_0x1C440217_XIX_Physical_c4e0b3c7_Tx/PduRSrcPdu_a9d87b23] */
  { /*     7 */         0u,       2u,                7u,                                                                            ComConf_ComIPdu_DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx },  /* [PduRSrcPdu: PduRSrcPdu_f6736a3d] */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx/PduRSrcPdu_f6736a3d] */
  { /*     8 */         0u,       2u,                0u,                                                                                    ComConf_ComIPdu_NFC_TGS_01_XIX_HCP4_CANFD01_6816bdec_Tx }   /* [PduRSrcPdu: PduRSrcPdu_2470bef4] */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/NFC_TGS_01_XIX_HCP4_CANFD01_6816bdec_Tx/PduRSrcPdu_2470bef4] */
};
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  PduR_RmTransmitFctPtr
**********************************************************************************************************************/
/** 
  \var    PduR_RmTransmitFctPtr
  \brief  Internal routing manager Transmit functions.
*/ 
#define PDUR_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(PduR_RmTransmitFctPtrType, PDUR_CONST) PduR_RmTransmitFctPtr[2] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     RmTransmitFctPtr                  Referable Keys */
  /*     0 */ PduR_RmIf_RoutePdu           ,  /* [PduR_RmIf_RoutePdu] */
  /*     1 */ PduR_RmTp_Transmit_MultiDest    /* [PduR_RmTp_Transmit_MultiDest] */
};
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  PduR_RxTp2Dest
**********************************************************************************************************************/
/** 
  \var    PduR_RxTp2Dest
  \brief  This table contains all routing information to perform the Rx handling of a Tp Routing. Used in the PduR_&lt;LLTp&gt;_StartOfReception, PduR_&lt;LLTp&gt;_CopyRxData and PduR_&lt;LLTp&gt;_RxIndication.
  \details
  Element                Description
  PartitionIndexOfCsl
*/ 
#define PDUR_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(PduR_RxTp2DestType, PDUR_CONST) PduR_RxTp2Dest[4] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    PartitionIndexOfCsl                                  Referable Keys */
  { /*     0 */                  0u  /* CommonSharedMemory */ },  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_ISO_Diagnose_XIX_0x1C410000_XIX_Functional_d6ea4aab_Rx/PduRSrcPdu_a386612b] */
  { /*     1 */                  0u  /* CommonSharedMemory */ },  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_ISO_Diagnose_XIX_0x1C440017_XIX_0x1C460017_XIX_Physical_985372e6_Rx/PduRSrcPdu_502ae7e6] */
  { /*     2 */                  0u  /* CommonSharedMemory */ },  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_OBDC_Diagnose_XIX_0x1C410200_XIX_Functional_bb5cab1c_Rx/PduRSrcPdu_7bfad7e5] */
  { /*     3 */                  0u  /* CommonSharedMemory */ }   /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_OBDC_Diagnose_XIX_0x1C440217_XIX_0x1C460217_XIX_Physical_c2443584_Rx/PduRSrcPdu_f9ee37ce] */
};
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  PduR_Tx2Lo
**********************************************************************************************************************/
/** 
  \var    PduR_Tx2Lo
  \brief  Contains all information to route a Pdu from a upper layer to a lower layer module, or to cancel a transmission
  \details
  Element                Description
  MaskedBits             contains bitcoded the boolean data of PduR_CancelTransmitUsedOfTx2Lo, PduR_RmSrcRomUsedOfTx2Lo
  PartitionIndexOfCsl
  RmTransmitFctPtrIdx    the index of the 1:1 relation pointing to PduR_RmTransmitFctPtr
*/ 
#define PDUR_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(PduR_Tx2LoType, PDUR_CONST) PduR_Tx2Lo[4] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    MaskedBits  PartitionIndexOfCsl                            RmTransmitFctPtrIdx        Referable Keys */
  { /*     0 */      0x03u,                  0u  /* CommonSharedMemory */,                  1u },  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_ISO_Diagnose_XIX_0x1C460017_XIX_0x1C440017_XIX_Physical_16591cf2_Tx/PduRSrcPdu_bbe61e78] */
  { /*     1 */      0x03u,                  0u  /* CommonSharedMemory */,                  1u },  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_OBDC_Diagnose_XIX_0x1C460217_XIX_0x1C440217_XIX_Physical_c4e0b3c7_Tx/PduRSrcPdu_a9d87b23] */
  { /*     2 */      0x01u,                  0u  /* CommonSharedMemory */,                  0u },  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx/PduRSrcPdu_f6736a3d] */
  { /*     3 */      0x01u,                  0u  /* CommonSharedMemory */,                  0u }   /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/NFC_TGS_01_XIX_HCP4_CANFD01_6816bdec_Tx/PduRSrcPdu_2470bef4] */
};
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  PduR_TxIf2Up
**********************************************************************************************************************/
/** 
  \var    PduR_TxIf2Up
  \brief  This table contains all routing information to perform the Tx handling of an interface routing. Used in the &lt;LLIf&gt;_TriggerTransmit and &lt;LLIf&gt;_TxConfirmation
  \details
  Element                Description
  TxConfirmationUsed     True, if any of the source PduRDestPdus uses a TxConfirmation.
  PartitionIndexOfCsl
  RmGDestRomIdx          the index of the 1:1 relation pointing to PduR_RmGDestRom
*/ 
#define PDUR_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(PduR_TxIf2UpType, PDUR_CONST) PduR_TxIf2Up[2] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    TxConfirmationUsed  PartitionIndexOfCsl                            RmGDestRomIdx        Referable Keys */
  { /*     0 */               TRUE,                  0u  /* CommonSharedMemory */,            6u },  /* [/ActiveEcuC/EcuC/EcucPduCollection/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f070f75_Tx] */
  { /*     1 */               TRUE,                  0u  /* CommonSharedMemory */,            8u }   /* [/ActiveEcuC/EcuC/EcucPduCollection/NFC_TGS_01_XIX_HCP4_CANFD01_a49c5cba_Tx] */
};
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  PduR_TxTp2Src
**********************************************************************************************************************/
/** 
  \var    PduR_TxTp2Src
  \brief  This table contains all routing information to perform the Tx handling of a transport protocol routing, Used in the &lt;LoTp&gt;_CopyTxData and &lt;LoTp&gt;_TxConfirmation
  \details
  Element                Description
  PartitionIndexOfCsl
  RmGDestRomIdx          the index of the 1:1 relation pointing to PduR_RmGDestRom
*/ 
#define PDUR_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(PduR_TxTp2SrcType, PDUR_CONST) PduR_TxTp2Src[2] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    PartitionIndexOfCsl                            RmGDestRomIdx        Referable Keys */
  { /*     0 */                  0u  /* CommonSharedMemory */,            2u },  /* [/ActiveEcuC/EcuC/EcucPduCollection/DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_ISO_Diagnose_XIX_0x1C460017_XIX_0x1C440017_XIX_Physical_59ac3609_Tx] */
  { /*     1 */                  0u  /* CommonSharedMemory */,            5u }   /* [/ActiveEcuC/EcuC/EcucPduCollection/DCM_HCP4_CANFD01_XIX_TPCHType_CANFD_OBDC_Diagnose_XIX_0x1C460217_XIX_0x1C440217_XIX_Physical_03bb716b_Tx] */
};
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  PduR_Initialized
**********************************************************************************************************************/
/** 
  \var    PduR_Initialized
  \brief  Initialization state of PduR. TRUE, if PduR_Init() has been called, else FALSE
*/ 
#define PDUR_START_SEC_VAR_ZERO_INIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(PduR_InitializedType, PDUR_VAR_ZERO_INIT) PduR_Initialized = FALSE;  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define PDUR_STOP_SEC_VAR_ZERO_INIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  PduR_PCPartitionConfig
**********************************************************************************************************************/
/** 
  \var    PduR_PCPartitionConfig
  \details
  Element        Description
  Initialized    the pointer to PduR_Initialized
*/ 
#define PDUR_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(PduR_PCPartitionConfigType, PDUR_CONST) PduR_PCPartitionConfig[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  { /* Index: 0 Keys: [] */
      (&(PduR_Initialized))  /**< the pointer to PduR_Initialized */
  }
};
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */


/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL DATA
**********************************************************************************************************************/


#define PDUR_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "PduR_MemMap.h"    /* PRQA S 5087 */        /* MD_MSR_MemMap */

#if(PDUR_USE_INIT_POINTER == STD_ON)
P2CONST(PduR_PBConfigType, PDUR_VAR_ZERO_INIT, PDUR_PBCFG) PduR_ConfigDataPtr = (const PduR_PBConfigType *) NULL_PTR;
#endif

#define PDUR_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "PduR_MemMap.h"    /* PRQA S 5087 */        /* MD_MSR_MemMap */

#define PDUR_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "PduR_MemMap.h"    /* PRQA S 5087 */        /* MD_MSR_MemMap */

VAR(boolean, PDUR_VAR_NOINIT) PduR_PreInitialized;

#define PDUR_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "PduR_MemMap.h"    /* PRQA S 5087 */        /* MD_MSR_MemMap */
  
/**********************************************************************************************************************
 * LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL FUNCTIONS
**********************************************************************************************************************/
#define PDUR_START_SEC_CODE
/* PRQA S 5087 1 */ /* MD_MSR_MemMap */
#include "PduR_MemMap.h"

/* Exclusive Area Wrapper functions */

/**********************************************************************************************************************
 * PduR_SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_0
 *********************************************************************************************************************/
/*!
 * \internal
 * -  enter the EA  
 * \endinternal
 *********************************************************************************************************************/
static FUNC(void, PDUR_CODE) PduR_SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_0(void)
{
  SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_0();
}


/**********************************************************************************************************************
 * PduR_SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_0
 *********************************************************************************************************************/
/*!
 * \internal
 * -  exit the EA  
 * \endinternal
 *********************************************************************************************************************/
static FUNC(void, PDUR_CODE) PduR_SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_0(void)
{
  SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_0();
}


/* Upper Layer Interface APIs */

/**********************************************************************************************************************
 * PduR_ComTransmit
 *********************************************************************************************************************/
/*!
 * \internal
 * - call upper layer Transmit function. 
 * \endinternal
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_ComTransmit(PduIdType id, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info) /* COV_PDUR_WRAPPER_FUNC */
{
  Std_ReturnType retVal = E_NOT_OK;        /* PRQA S 2981 */ /* MD_MSR_RetVal */
  
#if (PDUR_TX2LO == STD_ON) /* COV_PDUR_RX_OR_TX_ONLY_CONFIG */
  retVal = PduR_UpTransmit(id, info); /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ONLY */
#else
  PduR_Det_ReportError(PDUR_FCT_TX, PDUR_E_PDU_ID_INVALID);
#endif

  PDUR_DUMMY_STATEMENT(id);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(info);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return retVal;
}


/**********************************************************************************************************************
 * PduR_DcmTransmit
 *********************************************************************************************************************/
/*!
 * \internal
 * - call upper layer Transmit function. 
 * \endinternal
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_DcmTransmit(PduIdType id, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info) /* COV_PDUR_WRAPPER_FUNC */
{
  Std_ReturnType retVal = E_NOT_OK;        /* PRQA S 2981 */ /* MD_MSR_RetVal */
  
#if (PDUR_TX2LO == STD_ON) /* COV_PDUR_RX_OR_TX_ONLY_CONFIG */
  retVal = PduR_UpTransmit(id, info); /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ONLY */
#else
  PduR_Det_ReportError(PDUR_FCT_TX, PDUR_E_PDU_ID_INVALID);
#endif

  PDUR_DUMMY_STATEMENT(id);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(info);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return retVal;
}


/* Communication Interface APIs */

/**********************************************************************************************************************
 * PduR_CanIfRxIndication
 *********************************************************************************************************************/
/*!
 * \internal
 * -  call internal general IfRxIndication function.  
 * \endinternal
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_CanIfRxIndication(PduIdType RxPduId, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info) /* COV_PDUR_WRAPPER_FUNC */
{
#if (PDUR_RXIF2DEST == STD_ON) /* COV_PDUR_RX_OR_TX_ONLY_CONFIG */
  PduR_LoIfRxIndication(RxPduId, info);  /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ONLY */
#else
  PduR_Det_ReportError(PDUR_FCT_IFRXIND, PDUR_E_PDU_ID_INVALID);
#endif
  PDUR_DUMMY_STATEMENT(RxPduId);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(info);   		/* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}


/**********************************************************************************************************************
 * PduR_CanIfTxConfirmation
 *********************************************************************************************************************/
/*!
 * \internal
 * - call internal general communication interface TxConfirmation function.
 * \endinternal
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_CanIfTxConfirmation(PduIdType TxPduId) /* COV_PDUR_WRAPPER_FUNC */
{
#if (PDUR_TXCONFIRMATIONUSEDOFTXIF2UP == STD_ON)
  PduR_LoIfTxConfirmation(TxPduId);
#endif
  PDUR_DUMMY_STATEMENT(TxPduId);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}




/* Transport Protocol APIs */

/**********************************************************************************************************************
 * PduR_CanTpStartOfReception
 *********************************************************************************************************************/
 /*!
 * \internal
 * - call transport protocoll StartOfReception function.  
 * \endinternal
 *********************************************************************************************************************/
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_CanTpStartOfReception(PduIdType id, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, PduLengthType TpSduLength, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr) /* COV_PDUR_WRAPPER_FUNC */
{
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;        /* PRQA S 2981 */ /* MD_MSR_RetVal */

#if (PDUR_RXTP2DEST == STD_ON) /* COV_PDUR_RX_OR_TX_ONLY_CONFIG */
  retVal = PduR_LoTpStartOfReception(id, info, TpSduLength, bufferSizePtr); /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ONLY */
#else
  PduR_Det_ReportError(PDUR_FCT_SOR, PDUR_E_PDU_ID_INVALID);
#endif

  PDUR_DUMMY_STATEMENT(id);     		/* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(info);   		/* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(TpSduLength);    /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(bufferSizePtr);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return retVal;
}


/**********************************************************************************************************************
 * PduR_CanTpCopyRxData
 *********************************************************************************************************************/
/*!
 * \internal
 * - call internal general CopyRxData.
 * \endinternal
 *********************************************************************************************************************/
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_CanTpCopyRxData(PduIdType id, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr) /* COV_PDUR_WRAPPER_FUNC */
{
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;        /* PRQA S 2981 */ /* MD_MSR_RetVal */
  
#if (PDUR_RXTP2DEST == STD_ON) /* COV_PDUR_RX_OR_TX_ONLY_CONFIG */
  retVal = PduR_LoTpCopyRxData(id, info, bufferSizePtr); /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ONLY */
#else
  PduR_Det_ReportError(PDUR_FCT_CPYRX, PDUR_E_PDU_ID_INVALID);
#endif

  PDUR_DUMMY_STATEMENT(id);     		/* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(info);  			/* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(bufferSizePtr);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  
  return retVal;
}


/**********************************************************************************************************************
 * PduR_CanTpCopyTxData
 *********************************************************************************************************************/
/*!
 * \internal
 * - call internal general CopyTxData.
 * \endinternal
 *********************************************************************************************************************/
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_CanTpCopyTxData(PduIdType id, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, P2VAR(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA) retry, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) availableDataPtr) /* COV_PDUR_WRAPPER_FUNC */
{
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;        /* PRQA S 2981 */ /* MD_MSR_RetVal */
  
#if(PDUR_TXTP2SRC == STD_ON) /* COV_PDUR_RX_OR_TX_ONLY_CONFIG */
  retVal = PduR_LoTpCopyTxData(id, info, retry, availableDataPtr); /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ONLY */
#else
  PduR_Det_ReportError(PDUR_FCT_CPYTX, PDUR_E_PDU_ID_INVALID);
#endif

  PDUR_DUMMY_STATEMENT(id);     				/* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(info);  					/* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(retry);  				/* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(availableDataPtr);       /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  
  return retVal;
}


/**********************************************************************************************************************
 * PduR_CanTpRxIndication
 *********************************************************************************************************************/
/*!
 * \internal
 * - call Tp RxIndication function.
 * \endinternal
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_CanTpRxIndication(PduIdType id, Std_ReturnType result) /* COV_PDUR_WRAPPER_FUNC */
{
#if (PDUR_RXTP2DEST == STD_ON) /* COV_PDUR_RX_OR_TX_ONLY_CONFIG */
  PduR_LoTpRxIndication(id, result);
#else
  PduR_Det_ReportError(PDUR_FCT_TPRXIND, PDUR_E_PDU_ID_INVALID);
#endif

  PDUR_DUMMY_STATEMENT(id);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(result); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}


/**********************************************************************************************************************
 * PduR_CanTpTxConfirmation
 *********************************************************************************************************************/
/*!
 * \internal
 * - call Tp TxConfirmation function 
 * \endinternal
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_CanTpTxConfirmation(PduIdType id, Std_ReturnType result) /* COV_PDUR_WRAPPER_FUNC */
{
#if (PDUR_TXTP2SRC == STD_ON) /* COV_PDUR_RX_OR_TX_ONLY_CONFIG */
  PduR_LoTpTxConfirmation(id, result);
#else
  PduR_Det_ReportError(PDUR_FCT_TPTXCFM, PDUR_E_PDU_ID_INVALID);
#endif

  PDUR_DUMMY_STATEMENT(id);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(result); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}


/* CancelReceive global without UseTag API */

/* ChangeParameter global without UseTag  API */

/* Communication Interface / Transport Protocol APIs */

/* Communication Interface / Transport Protocol APIs */

/**********************************************************************************************************************
 * PduR_DcmCancelTransmit
 *********************************************************************************************************************/
/*!
 * \internal
 * - call internal general CancelTransmit function.
 * \endinternal
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_DcmCancelTransmit(PduIdType id)
{
  return PduR_CancelTransmit(id); /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ONLY */
}


/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL FUNCTIONS
**********************************************************************************************************************/


#define PDUR_STOP_SEC_CODE
/* PRQA S 5087 1 */ /* MD_MSR_MemMap */
#include "PduR_MemMap.h"

/* SBSW_JUSTIFICATION_BEGIN

  \ID SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ID_AND_PTR
    \DESCRIPTION    The API is called with an Id and a pointer.
                    The API call is forwarded using a function pointer which is read using ComStackLib macros.
                    
    \COUNTERMEASURE \N The function pointer is read using the passed Id (and ComStackLib macros). 
                       The Id is a SNV provided by the lower layer. 
                       It is checked at runtime if it is in the valid range.
                       The pointer is provided by the lower layer and is assumed to be valid. It is passed as is to the corresponding function. 

  \ID SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ID_ONLY
    \DESCRIPTION    The API is called with an Id.
                    The API call is forwarded using a function pointer which is read using ComStackLib macros.
                    
    \COUNTERMEASURE \R The function pointer is read using the passed Id (and ComStackLib macros). 
                       The Id is a SNV provided by the lower layer. 
                       It is checked at runtime if it is in the valid range.
                       
  \ID SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ONLY
    \DESCRIPTION    The API call is forwarded to an internal function.
    \COUNTERMEASURE \N The parameter are checked in the called function.

 SBSW_JUSTIFICATION_END */
 
 /* COV_JUSTIFICATION_BEGIN
 
  \ID COV_PDUR_WRAPPER_FUNC
    \ACCEPT X
    \REASON Each neighbouring module call the same internal function. The call is covered by an other module. 
    
  \ID COV_PDUR_RX_OR_TX_ONLY_CONFIG
    \ACCEPT TX
    \REASON The API is mandatory if this Bsw module exists. In case of Rx or Tx only configs the API call is not forwarded to the internal function. 
 
 COV_JUSTIFICATION_END */
 

/**********************************************************************************************************************
 * END OF FILE: PduR_Lcfg.c
 *********************************************************************************************************************/

