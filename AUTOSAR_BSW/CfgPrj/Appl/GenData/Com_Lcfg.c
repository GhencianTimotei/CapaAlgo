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
 *            Module: Com
 *           Program: VAG AR4 (MSR_Vag_SLP5)
 *          Customer: Huf H_lsbeck & F_rst GmbH & Co. KG
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: S32K144
 *    License Scope : The usage is restricted to CBD2100188_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: Com_Lcfg.c
 *   Generation Time: 2024-02-18 20:52:58
 *           Project: DaVinciConfigurationS32K144 - Version 1.0
 *          Delivery: CBD2100188_D01
 *      Tool Version: DaVinci Configurator  5.23.45 SP4
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * WARNING: This code has been generated with reduced-severity errors. 
 * The created output files contain errors that have been ignored. Usage of the created files can lead to unpredictable behavior of the embedded code.
 * Usage of the created files happens at own risk!
 * 
 * [Warning] COM01007 - Inconsistent textual value. 
 * - [Reduced Severity due to User-Defined Parameter] Interpreted array value 0 of string value "0000000000000000000000000000000000000000000000000000000000000000" is too short for array signal with signal length 64.
 * Erroneous configuration elements:
 * /ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_Data_XIX_DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_56a7f80a_Tx[0:ComSignalInitValue](value=0000000000000000000000000000000000000000000000000000000000000000) (DefRef: /MICROSAR/Com/ComConfig/ComSignal/ComSignalInitValue)
 *********************************************************************************************************************/

/**********************************************************************************************************************
  MISRA / PClint JUSTIFICATIONS
**********************************************************************************************************************/

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
#define V_IL_ASRCOMCFG5_LCFG_SOURCE

#include "Com.h"
#include "Com_Timer.h"
#include "Com_TxModeHdlr.h"
#include "Com_LLIf.h"


#include "SchM_Com.h"

/**********************************************************************************************************************
  LOCAL CONSTANT MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
  LOCAL FUNCTION MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
  LOCAL DATA TYPES AND STRUCTURES
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
  Com_ConstValueUInt8
**********************************************************************************************************************/
/** 
  \var    Com_ConstValueUInt8
  \brief  Optimized array of commonly used values like initial or invalid values. (BOOLEAN, UINT8)
*/ 
#define COM_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Com_ConstValueUInt8Type, COM_CONST) Com_ConstValueUInt8[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     ConstValueUInt8      Referable Keys */
  /*     0 */            0x00u   /* [/ActiveEcuC/Com/ComConfig/B_ActiveModeInitValue, /ActiveEcuC/Com/ComConfig/B_ActuatorControlInitValue, /ActiveEcuC/Com/ComConfig/B_InductiveEnabledInitValue, /ActiveEcuC/Com/ComConfig/B_LockEnabledInitValue, /ActiveEcuC/Com/ComConfig/B_UnlockEnabledInitValue, /ActiveEcuC/Com/ComConfig/E_LedModeInitValue] */
};
#define COM_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_IPduGroupInfo
**********************************************************************************************************************/
/** 
  \var    Com_IPduGroupInfo
  \brief  Contains all I-Pdu Group relevant information
  \details
  Element                 Description
  RxPduInfoIndEndIdx      the end index of the 0:n relation pointing to Com_RxPduInfoInd
  RxPduInfoIndStartIdx    the start index of the 0:n relation pointing to Com_RxPduInfoInd
  TxPduInfoIndEndIdx      the end index of the 0:n relation pointing to Com_TxPduInfoInd
  TxPduInfoIndStartIdx    the start index of the 0:n relation pointing to Com_TxPduInfoInd
*/ 
#define COM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Com_IPduGroupInfoType, COM_CONST) Com_IPduGroupInfo[4] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    RxPduInfoIndEndIdx                        RxPduInfoIndStartIdx                        TxPduInfoIndEndIdx                        TxPduInfoIndStartIdx                              Referable Keys */
  { /*     0 */ COM_NO_RXPDUINFOINDENDIDXOFIPDUGROUPINFO, COM_NO_RXPDUINFOINDSTARTIDXOFIPDUGROUPINFO, COM_NO_TXPDUINFOINDENDIDXOFIPDUGROUPINFO, COM_NO_TXPDUINFOINDSTARTIDXOFIPDUGROUPINFO },  /* [/ActiveEcuC/Com/ComConfig/AlwaysOnRx] */
  { /*     1 */ COM_NO_RXPDUINFOINDENDIDXOFIPDUGROUPINFO, COM_NO_RXPDUINFOINDSTARTIDXOFIPDUGROUPINFO, COM_NO_TXPDUINFOINDENDIDXOFIPDUGROUPINFO, COM_NO_TXPDUINFOINDSTARTIDXOFIPDUGROUPINFO },  /* [/ActiveEcuC/Com/ComConfig/AlwaysOnTx] */
  { /*     2 */                                       1u,                                         0u, COM_NO_TXPDUINFOINDENDIDXOFIPDUGROUPINFO, COM_NO_TXPDUINFOINDSTARTIDXOFIPDUGROUPINFO },  /* [/ActiveEcuC/Com/ComConfig/CommunicationControlRx, /ActiveEcuC/Com/ComConfig/DoorFunctions_FS_01_XIX_HCP4_CANFD01_92a39409_Rx] */
  { /*     3 */ COM_NO_RXPDUINFOINDENDIDXOFIPDUGROUPINFO, COM_NO_RXPDUINFOINDSTARTIDXOFIPDUGROUPINFO,                                       2u,                                         0u }   /* [/ActiveEcuC/Com/ComConfig/CommunicationControlTx, /ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx, /ActiveEcuC/Com/ComConfig/NFC_TGS_01_XIX_HCP4_CANFD01_6816bdec_Tx] */
};
#define COM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_IPduGroupInfoOfTxPduInfoInd
**********************************************************************************************************************/
/** 
  \var    Com_IPduGroupInfoOfTxPduInfoInd
  \brief  the indexes of the 1:1 sorted relation pointing to Com_IPduGroupInfo
*/ 
#define COM_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Com_IPduGroupInfoOfTxPduInfoIndType, COM_CONST) Com_IPduGroupInfoOfTxPduInfoInd[2] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     IPduGroupInfoOfTxPduInfoInd      Referable Keys */
  /*     0 */                           3u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*     1 */                           3u   /* [/ActiveEcuC/Com/ComConfig/NFC_TGS_01_XIX_HCP4_CANFD01_6816bdec_Tx] */
};
#define COM_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_RxAccessInfo
**********************************************************************************************************************/
/** 
  \var    Com_RxAccessInfo
  \brief  Contains all signal layout information necessary for signal access within an I-PDU.
  \details
  Element                   Description
  InitValueUsed             TRUE, if the 0:1 relation has minimum 1 relation pointing to Com_ConstValueUInt8,Com_ConstValueUInt16,Com_ConstValueUInt32,Com_ConstValueUInt64,Com_ConstValueSInt8,Com_ConstValueSInt16,Com_ConstValueSInt32,Com_ConstValueSInt64,Com_ConstValueFloat32,Com_ConstValueFloat64
  BitLength                 Bit length of the signal or group signal.
  BitPosition               Little endian bit position of the signal or group signal within the I-PDU.
  BusAcc                    BUS access algorithm for signal or group signal packing / un-packing.
  ByteLength                Byte length of the signal or group signal.
  InitValueIdx              the index of the 0:1 relation pointing to Com_ConstValueUInt8,Com_ConstValueUInt16,Com_ConstValueUInt32,Com_ConstValueUInt64,Com_ConstValueSInt8,Com_ConstValueSInt16,Com_ConstValueSInt32,Com_ConstValueSInt64,Com_ConstValueFloat32,Com_ConstValueFloat64
  StartByteInPduPosition    Start Byte position of the signal or group signal within the I-PDU.
*/ 
#define COM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Com_RxAccessInfoType, COM_CONST) Com_RxAccessInfo[6] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    InitValueUsed  BitLength  BitPosition  BusAcc                              ByteLength  InitValueIdx  StartByteInPduPosition        Referable Keys */
  { /*     0 */          TRUE,        1u,         12u,      COM_NBIT_BUSACCOFRXACCESSINFO,         0u,           0u,                     1u },  /* [/ActiveEcuC/Com/ComConfig/B_ActiveMode, /ActiveEcuC/Com/ComConfig/DoorFunctions_FS_01_XIX_HCP4_CANFD01_92a39409_Rx] */
  { /*     1 */          TRUE,        1u,         11u,      COM_NBIT_BUSACCOFRXACCESSINFO,         0u,           0u,                     1u },  /* [/ActiveEcuC/Com/ComConfig/B_ActuatorControl, /ActiveEcuC/Com/ComConfig/DoorFunctions_FS_01_XIX_HCP4_CANFD01_92a39409_Rx] */
  { /*     2 */          TRUE,        1u,          2u,      COM_NBIT_BUSACCOFRXACCESSINFO,         0u,           0u,                     0u },  /* [/ActiveEcuC/Com/ComConfig/B_InductiveEnabled, /ActiveEcuC/Com/ComConfig/DoorFunctions_FS_01_XIX_HCP4_CANFD01_92a39409_Rx] */
  { /*     3 */          TRUE,        1u,          0u,      COM_NBIT_BUSACCOFRXACCESSINFO,         0u,           0u,                     0u },  /* [/ActiveEcuC/Com/ComConfig/B_LockEnabled, /ActiveEcuC/Com/ComConfig/DoorFunctions_FS_01_XIX_HCP4_CANFD01_92a39409_Rx] */
  { /*     4 */          TRUE,        1u,          1u,      COM_NBIT_BUSACCOFRXACCESSINFO,         0u,           0u,                     0u },  /* [/ActiveEcuC/Com/ComConfig/B_UnlockEnabled, /ActiveEcuC/Com/ComConfig/DoorFunctions_FS_01_XIX_HCP4_CANFD01_92a39409_Rx] */
  { /*     5 */          TRUE,        8u,          3u, COM_NBITNBYTE_BUSACCOFRXACCESSINFO,         1u,           0u,                     0u }   /* [/ActiveEcuC/Com/ComConfig/E_LedMode, /ActiveEcuC/Com/ComConfig/DoorFunctions_FS_01_XIX_HCP4_CANFD01_92a39409_Rx] */
};
#define COM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_RxPduCalloutFuncPtr
**********************************************************************************************************************/
/** 
  \var    Com_RxPduCalloutFuncPtr
  \brief  Rx I-PDU callout function pointer table.
*/ 
#define COM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(ComRxPduCalloutType, COM_CONST) Com_RxPduCalloutFuncPtr[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     RxPduCalloutFuncPtr                Referable Keys */
  /*     0 */ TEST_Ipdu_DoorFunctions_FS_01    /* [/ActiveEcuC/Com/ComConfig/DoorFunctions_FS_01_XIX_HCP4_CANFD01_92a39409_Rx] */
};
#define COM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_RxPduInfo
**********************************************************************************************************************/
/** 
  \var    Com_RxPduInfo
  \brief  Contains all relevant common information for Rx I-PDUs.
  \details
  Element                            Description
  IPduGroupInfoOfRxPduInfoIndUsed    TRUE, if the 0:n relation has 1 relation pointing to Com_IPduGroupInfoOfRxPduInfoInd
*/ 
#define COM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Com_RxPduInfoType, COM_CONST) Com_RxPduInfo[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    IPduGroupInfoOfRxPduInfoIndUsed        Referable Keys */
  { /*     0 */                            TRUE }   /* [/ActiveEcuC/Com/ComConfig/DoorFunctions_FS_01_XIX_HCP4_CANFD01_92a39409_Rx, /ActiveEcuC/Com/ComConfig/CommunicationControlRx] */
};
#define COM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_RxSigInfo
**********************************************************************************************************************/
/** 
  \var    Com_RxSigInfo
  \brief  Contains all relevant information for Rx signals.
  \details
  Element             Description
  SignalProcessing
  ValidDlc            Minimum length of PDU required to completely receive the signal or signal group.
*/ 
#define COM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Com_RxSigInfoType, COM_CONST) Com_RxSigInfo[6] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    SignalProcessing                          ValidDlc        Referable Keys */
  { /*     0 */ COM_DEFERRED_SIGNALPROCESSINGOFRXSIGINFO,       2u },  /* [/ActiveEcuC/Com/ComConfig/DoorFunctions_FS_01_XIX_HCP4_CANFD01_92a39409_Rx] */
  { /*     1 */ COM_DEFERRED_SIGNALPROCESSINGOFRXSIGINFO,       2u },  /* [/ActiveEcuC/Com/ComConfig/DoorFunctions_FS_01_XIX_HCP4_CANFD01_92a39409_Rx] */
  { /*     2 */ COM_DEFERRED_SIGNALPROCESSINGOFRXSIGINFO,       1u },  /* [/ActiveEcuC/Com/ComConfig/DoorFunctions_FS_01_XIX_HCP4_CANFD01_92a39409_Rx] */
  { /*     3 */ COM_DEFERRED_SIGNALPROCESSINGOFRXSIGINFO,       1u },  /* [/ActiveEcuC/Com/ComConfig/DoorFunctions_FS_01_XIX_HCP4_CANFD01_92a39409_Rx] */
  { /*     4 */ COM_DEFERRED_SIGNALPROCESSINGOFRXSIGINFO,       1u },  /* [/ActiveEcuC/Com/ComConfig/DoorFunctions_FS_01_XIX_HCP4_CANFD01_92a39409_Rx] */
  { /*     5 */ COM_DEFERRED_SIGNALPROCESSINGOFRXSIGINFO,       2u }   /* [/ActiveEcuC/Com/ComConfig/DoorFunctions_FS_01_XIX_HCP4_CANFD01_92a39409_Rx] */
};
#define COM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_TxModeInfo
**********************************************************************************************************************/
/** 
  \var    Com_TxModeInfo
  \brief  Contains all relevant information for transmission mode handling.
  \details
  Element         Description
  InitMode        Initial transmission mode selector of the Tx I-PDU.
  MinimumDelay    Minimum delay factor of the Tx I-PDU.
*/ 
#define COM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Com_TxModeInfoType, COM_CONST) Com_TxModeInfo[2] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    InitMode  MinimumDelay        Referable Keys */
  { /*     0 */     TRUE,           0u },  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  { /*     1 */     TRUE,           2u }   /* [/ActiveEcuC/Com/ComConfig/NFC_TGS_01_XIX_HCP4_CANFD01_6816bdec_Tx] */
};
#define COM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_TxModeTrue
**********************************************************************************************************************/
/** 
  \var    Com_TxModeTrue
  \brief  Contains all relevant information for transmission mode true.
  \details
  Element       Description
  Periodic      TRUE if transmission mode contains a cyclic part.
  RepCnt        Repetition count for replication of transmission requests plus one initial transmit.
  RepPeriod     Repetition period factor for replication of transmission requests.
  TimePeriod    Cycle time factor.
*/ 
#define COM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Com_TxModeTrueType, COM_CONST) Com_TxModeTrue[2] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    Periodic  RepCnt  RepPeriod  TimePeriod        Referable Keys */
  { /*     0 */     TRUE,     0u,        0u,         1u },  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  { /*     1 */     TRUE,     9u,        2u,        20u }   /* [/ActiveEcuC/Com/ComConfig/NFC_TGS_01_XIX_HCP4_CANFD01_6816bdec_Tx] */
};
#define COM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_TxPduCalloutFuncPtr
**********************************************************************************************************************/
/** 
  \var    Com_TxPduCalloutFuncPtr
  \brief  Tx I-PDU callout function pointer table.
*/ 
#define COM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(ComTxPduCalloutType, COM_CONST) Com_TxPduCalloutFuncPtr[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     TxPduCalloutFuncPtr                  Referable Keys */
  /*     0 */ NFC_FS_Resp_development_message    /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
};
#define COM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_TxPduInfo
**********************************************************************************************************************/
/** 
  \var    Com_TxPduInfo
  \brief  Contains all relevant information for Tx I-PDUs.
  \details
  Element                   Description
  TxBufferUsed              TRUE, if the 0:n relation has 1 relation pointing to Com_TxBuffer
  MetaDataLength            Length of MetaData.
  TxBufferLength            the number of relations pointing to Com_TxBuffer
  TxPduCalloutFuncPtrIdx    the index of the 0:1 relation pointing to Com_TxPduCalloutFuncPtr
  TxPduInitValueEndIdx      the end index of the 0:n relation pointing to Com_TxPduInitValue
  TxPduInitValueStartIdx    the start index of the 0:n relation pointing to Com_TxPduInitValue
*/ 
#define COM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Com_TxPduInfoType, COM_CONST) Com_TxPduInfo[2] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    TxBufferUsed  MetaDataLength  TxBufferLength  TxPduCalloutFuncPtrIdx                    TxPduInitValueEndIdx  TxPduInitValueStartIdx        Referable Keys */
  { /*     0 */         TRUE,             0u,            64u,                                       0u,                  64u,                     0u },  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx, /ActiveEcuC/Com/ComConfig/CommunicationControlTx] */
  { /*     1 */         TRUE,             0u,             8u, COM_NO_TXPDUCALLOUTFUNCPTRIDXOFTXPDUINFO,                  72u,                    64u }   /* [/ActiveEcuC/Com/ComConfig/NFC_TGS_01_XIX_HCP4_CANFD01_6816bdec_Tx, /ActiveEcuC/Com/ComConfig/CommunicationControlTx] */
};
#define COM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_TxPduInitValue
**********************************************************************************************************************/
/** 
  \var    Com_TxPduInitValue
  \brief  Initial values used for Tx I-PDU buffer initialization.
*/ 
#define COM_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Com_TxPduInitValueType, COM_CONST) Com_TxPduInitValue[72] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     TxPduInitValue      Referable Keys */
  /*     0 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*     1 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*     2 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*     3 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*     4 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*     5 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*     6 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*     7 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*     8 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*     9 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    10 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    11 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    12 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    13 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    14 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    15 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    16 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    17 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    18 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    19 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    20 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    21 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    22 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    23 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    24 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    25 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    26 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    27 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    28 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    29 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    30 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    31 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    32 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    33 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    34 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    35 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    36 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    37 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    38 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    39 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    40 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    41 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    42 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    43 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    44 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    45 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    46 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    47 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    48 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    49 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /* Index     TxPduInitValue      Referable Keys */
  /*    50 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    51 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    52 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    53 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    54 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    55 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    56 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    57 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    58 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    59 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    60 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    61 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    62 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    63 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
  /*    64 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/NFC_TGS_01_XIX_HCP4_CANFD01_6816bdec_Tx] */
  /*    65 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/NFC_TGS_01_XIX_HCP4_CANFD01_6816bdec_Tx] */
  /*    66 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/NFC_TGS_01_XIX_HCP4_CANFD01_6816bdec_Tx] */
  /*    67 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/NFC_TGS_01_XIX_HCP4_CANFD01_6816bdec_Tx] */
  /*    68 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/NFC_TGS_01_XIX_HCP4_CANFD01_6816bdec_Tx] */
  /*    69 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/NFC_TGS_01_XIX_HCP4_CANFD01_6816bdec_Tx] */
  /*    70 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/NFC_TGS_01_XIX_HCP4_CANFD01_6816bdec_Tx] */
  /*    71 */           0x00u   /* [/ActiveEcuC/Com/ComConfig/NFC_TGS_01_XIX_HCP4_CANFD01_6816bdec_Tx] */
};
#define COM_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_TxSigInfo
**********************************************************************************************************************/
/** 
  \var    Com_TxSigInfo
  \brief  Contains all relevant information for Tx signals and group signals.
  \details
  Element                   Description
  BitLength                 Bit length of the signal or group signal.
  ApplType                  Application data type.
  BitPosition               Little endian bit position of the signal or group signal within the I-PDU.
  BusAcc                    BUS access algorithm for signal or group signal packing / un-packing.
  ByteLength                Byte length of the signal or group signal.
  StartByteInPduPosition    Start Byte position of the signal or group signal within the I-PDU.
  TxBufferLength            the number of relations pointing to Com_TxBuffer
  TxBufferStartIdx          the start index of the 0:n relation pointing to Com_TxBuffer
  TxPduInfoIdx              the index of the 1:1 relation pointing to Com_TxPduInfo
*/ 
#define COM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Com_TxSigInfoType, COM_CONST) Com_TxSigInfo[6] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    BitLength  ApplType                         BitPosition  BusAcc                             ByteLength  StartByteInPduPosition  TxBufferLength  TxBufferStartIdx  TxPduInfoIdx        Referable Keys */
  { /*     0 */        1u,   COM_UINT8_APPLTYPEOFTXSIGINFO,          3u,        COM_NBIT_BUSACCOFTXSIGINFO,         0u,                     0u,             1u,              64u,           1u },  /* [/ActiveEcuC/Com/ComConfig/B_Inductive, /ActiveEcuC/Com/ComConfig/NFC_TGS_01_XIX_HCP4_CANFD01_6816bdec_Tx] */
  { /*     1 */        1u,   COM_UINT8_APPLTYPEOFTXSIGINFO,          4u,        COM_NBIT_BUSACCOFTXSIGINFO,         0u,                     0u,             1u,              64u,           1u },  /* [/ActiveEcuC/Com/ComConfig/B_LedActive, /ActiveEcuC/Com/ComConfig/NFC_TGS_01_XIX_HCP4_CANFD01_6816bdec_Tx] */
  { /*     2 */        1u,   COM_UINT8_APPLTYPEOFTXSIGINFO,          0u,        COM_NBIT_BUSACCOFTXSIGINFO,         0u,                     0u,             1u,              64u,           1u },  /* [/ActiveEcuC/Com/ComConfig/B_LockApproach, /ActiveEcuC/Com/ComConfig/NFC_TGS_01_XIX_HCP4_CANFD01_6816bdec_Tx] */
  { /*     3 */        1u,   COM_UINT8_APPLTYPEOFTXSIGINFO,          1u,        COM_NBIT_BUSACCOFTXSIGINFO,         0u,                     0u,             1u,              64u,           1u },  /* [/ActiveEcuC/Com/ComConfig/B_LockTouch, /ActiveEcuC/Com/ComConfig/NFC_TGS_01_XIX_HCP4_CANFD01_6816bdec_Tx] */
  { /*     4 */        1u,   COM_UINT8_APPLTYPEOFTXSIGINFO,          2u,        COM_NBIT_BUSACCOFTXSIGINFO,         0u,                     0u,             1u,              64u,           1u },  /* [/ActiveEcuC/Com/ComConfig/B_UnlockApproach, /ActiveEcuC/Com/ComConfig/NFC_TGS_01_XIX_HCP4_CANFD01_6816bdec_Tx] */
  { /*     5 */      512u, COM_UINT8_N_APPLTYPEOFTXSIGINFO,          0u, COM_ARRAY_BASED_BUSACCOFTXSIGINFO,        64u,                     0u,            64u,               0u,           0u }   /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_Data_XIX_DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_56a7f80a_Tx, /ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx] */
};
#define COM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_CurrentTxMode
**********************************************************************************************************************/
/** 
  \var    Com_CurrentTxMode
  \brief  Current transmission mode state of all Tx I-PDUs.
*/ 
#define COM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_CurrentTxModeType, COM_VAR_NOINIT) Com_CurrentTxMode[2];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx, /ActiveEcuC/Com/ComConfig/CommunicationControlTx] */
  /*     1 */  /* [/ActiveEcuC/Com/ComConfig/NFC_TGS_01_XIX_HCP4_CANFD01_6816bdec_Tx, /ActiveEcuC/Com/ComConfig/CommunicationControlTx] */

#define COM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_CycleTimeCnt
**********************************************************************************************************************/
/** 
  \var    Com_CycleTimeCnt
  \brief  Current counter value of cyclic transmission.
*/ 
#define COM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_CycleTimeCntType, COM_VAR_NOINIT) Com_CycleTimeCnt[2];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx, /ActiveEcuC/Com/ComConfig/CommunicationControlTx] */
  /*     1 */  /* [/ActiveEcuC/Com/ComConfig/NFC_TGS_01_XIX_HCP4_CANFD01_6816bdec_Tx, /ActiveEcuC/Com/ComConfig/CommunicationControlTx] */

#define COM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_CyclicSendRequest
**********************************************************************************************************************/
/** 
  \var    Com_CyclicSendRequest
  \brief  Cyclic send request flag used to indicate cyclic transmission mode for all Tx I-PDU.
*/ 
#define COM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_CyclicSendRequestType, COM_VAR_NOINIT) Com_CyclicSendRequest[2];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx, /ActiveEcuC/Com/ComConfig/CommunicationControlTx] */
  /*     1 */  /* [/ActiveEcuC/Com/ComConfig/NFC_TGS_01_XIX_HCP4_CANFD01_6816bdec_Tx, /ActiveEcuC/Com/ComConfig/CommunicationControlTx] */

#define COM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_DelayTimeCnt
**********************************************************************************************************************/
/** 
  \var    Com_DelayTimeCnt
  \brief  Current counter value of minimum delay counter.
*/ 
#define COM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_DelayTimeCntType, COM_VAR_NOINIT) Com_DelayTimeCnt[2];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx, /ActiveEcuC/Com/ComConfig/CommunicationControlTx] */
  /*     1 */  /* [/ActiveEcuC/Com/ComConfig/NFC_TGS_01_XIX_HCP4_CANFD01_6816bdec_Tx, /ActiveEcuC/Com/ComConfig/CommunicationControlTx] */

#define COM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_HandleRxPduDeferred
**********************************************************************************************************************/
/** 
  \var    Com_HandleRxPduDeferred
  \brief  Array indicating received Rx I-PDUs to be processed deferred within the next call of Com_MainfunctionRx().
*/ 
#define COM_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_HandleRxPduDeferredUType, COM_VAR_NOINIT) Com_HandleRxPduDeferred;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Com/ComConfig/DoorFunctions_FS_01_XIX_HCP4_CANFD01_92a39409_Rx] */

#define COM_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_IPduGroupState
**********************************************************************************************************************/
#define COM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_IPduGroupStateType, COM_VAR_NOINIT) Com_IPduGroupState[4];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Com/ComConfig/AlwaysOnRx] */
  /*     1 */  /* [/ActiveEcuC/Com/ComConfig/AlwaysOnTx] */
  /*     2 */  /* [/ActiveEcuC/Com/ComConfig/CommunicationControlRx, /ActiveEcuC/Com/ComConfig/DoorFunctions_FS_01_XIX_HCP4_CANFD01_92a39409_Rx] */
  /*     3 */  /* [/ActiveEcuC/Com/ComConfig/CommunicationControlTx, /ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx, /ActiveEcuC/Com/ComConfig/NFC_TGS_01_XIX_HCP4_CANFD01_6816bdec_Tx] */

#define COM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_Initialized
**********************************************************************************************************************/
/** 
  \var    Com_Initialized
  \brief  Initialization state of Com. TRUE, if Com_Init() has been called, else FALSE.
*/ 
#define COM_START_SEC_VAR_ZERO_INIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_InitializedType, COM_VAR_ZERO_INIT) Com_Initialized = FALSE;  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define COM_STOP_SEC_VAR_ZERO_INIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_RepCnt
**********************************************************************************************************************/
/** 
  \var    Com_RepCnt
  \brief  Current repetition counter value for replication of transmission requests plus one initial transmit.
*/ 
#define COM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_RepCntType, COM_VAR_NOINIT) Com_RepCnt[2];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx, /ActiveEcuC/Com/ComConfig/CommunicationControlTx] */
  /*     1 */  /* [/ActiveEcuC/Com/ComConfig/NFC_TGS_01_XIX_HCP4_CANFD01_6816bdec_Tx, /ActiveEcuC/Com/ComConfig/CommunicationControlTx] */

#define COM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_RepCycleCnt
**********************************************************************************************************************/
/** 
  \var    Com_RepCycleCnt
  \brief  Current counter value of repetition period for replication of transmission requests.
*/ 
#define COM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_RepCycleCntType, COM_VAR_NOINIT) Com_RepCycleCnt[2];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx, /ActiveEcuC/Com/ComConfig/CommunicationControlTx] */
  /*     1 */  /* [/ActiveEcuC/Com/ComConfig/NFC_TGS_01_XIX_HCP4_CANFD01_6816bdec_Tx, /ActiveEcuC/Com/ComConfig/CommunicationControlTx] */

#define COM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_RxDefPduBuffer
**********************************************************************************************************************/
/** 
  \var    Com_RxDefPduBuffer
  \brief  Rx I-PDU buffer for deferred signal processing.
*/ 
#define COM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_RxDefPduBufferUType, COM_VAR_NOINIT) Com_RxDefPduBuffer;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Com/ComConfig/DoorFunctions_FS_01_XIX_HCP4_CANFD01_92a39409_Rx] */
  /*   ... */  /* [/ActiveEcuC/Com/ComConfig/DoorFunctions_FS_01_XIX_HCP4_CANFD01_92a39409_Rx] */
  /*    59 */  /* [/ActiveEcuC/Com/ComConfig/DoorFunctions_FS_01_XIX_HCP4_CANFD01_92a39409_Rx] */

#define COM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_RxDeferredProcessingISRLockCounter
**********************************************************************************************************************/
#define COM_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_RxDeferredProcessingISRLockCounterType, COM_VAR_NOINIT) Com_RxDeferredProcessingISRLockCounter;  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define COM_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_RxIPduGroupISRLockCounter
**********************************************************************************************************************/
#define COM_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_RxIPduGroupISRLockCounterType, COM_VAR_NOINIT) Com_RxIPduGroupISRLockCounter;  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define COM_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_RxPduGrpActive
**********************************************************************************************************************/
/** 
  \var    Com_RxPduGrpActive
  \brief  Rx I-PDU based state (started/stopped) of the corresponding I-PDU-Group.
*/ 
#define COM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_RxPduGrpActiveType, COM_VAR_NOINIT) Com_RxPduGrpActive[1];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Com/ComConfig/DoorFunctions_FS_01_XIX_HCP4_CANFD01_92a39409_Rx, /ActiveEcuC/Com/ComConfig/CommunicationControlRx] */

#define COM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_RxSigBufferUInt8
**********************************************************************************************************************/
/** 
  \var    Com_RxSigBufferUInt8
  \brief  Rx Signal and Group Signal Buffer. (BOOLEAN, UINT8)
*/ 
#define COM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_RxSigBufferUInt8Type, COM_VAR_NOINIT) Com_RxSigBufferUInt8[6];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Com/ComConfig/B_ActiveMode, /ActiveEcuC/Com/ComConfig/B_ActiveMode_RxSignalBufferRouting] */
  /*     1 */  /* [/ActiveEcuC/Com/ComConfig/B_ActuatorControl, /ActiveEcuC/Com/ComConfig/B_ActuatorControl_RxSignalBufferRouting] */
  /*     2 */  /* [/ActiveEcuC/Com/ComConfig/B_InductiveEnabled, /ActiveEcuC/Com/ComConfig/B_InductiveEnabled_RxSignalBufferRouting] */
  /*     3 */  /* [/ActiveEcuC/Com/ComConfig/B_LockEnabled, /ActiveEcuC/Com/ComConfig/B_LockEnabled_RxSignalBufferRouting] */
  /*     4 */  /* [/ActiveEcuC/Com/ComConfig/B_UnlockEnabled, /ActiveEcuC/Com/ComConfig/B_UnlockEnabled_RxSignalBufferRouting] */
  /*     5 */  /* [/ActiveEcuC/Com/ComConfig/E_LedMode, /ActiveEcuC/Com/ComConfig/E_LedMode_RxSignalBufferRouting] */

#define COM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_TransmitRequest
**********************************************************************************************************************/
/** 
  \var    Com_TransmitRequest
  \brief  Transmit request flag used for decoupled Tx I-PDU tranmission.
*/ 
#define COM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_TransmitRequestType, COM_VAR_NOINIT) Com_TransmitRequest[2];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx, /ActiveEcuC/Com/ComConfig/CommunicationControlTx] */
  /*     1 */  /* [/ActiveEcuC/Com/ComConfig/NFC_TGS_01_XIX_HCP4_CANFD01_6816bdec_Tx, /ActiveEcuC/Com/ComConfig/CommunicationControlTx] */

#define COM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_TxBuffer
**********************************************************************************************************************/
/** 
  \var    Com_TxBuffer
  \brief  Shared uint8 buffer for Tx I-PDUs and ComSignalGroup shadow buffer.
*/ 
#define COM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_TxBufferType, COM_VAR_NOINIT) Com_TxBuffer[72];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx, /ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_Data_XIX_DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_56a7f80a_Tx] */
  /*   ... */  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx, /ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_Data_XIX_DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_56a7f80a_Tx] */
  /*    63 */  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx, /ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_Data_XIX_DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_56a7f80a_Tx] */
  /*    64 */  /* [/ActiveEcuC/Com/ComConfig/NFC_TGS_01_XIX_HCP4_CANFD01_6816bdec_Tx, /ActiveEcuC/Com/ComConfig/B_Inductive, /ActiveEcuC/Com/ComConfig/B_LedActive, /ActiveEcuC/Com/ComConfig/B_LockApproach, /ActiveEcuC/Com/ComConfig/B_LockTouch, /ActiveEcuC/Com/ComConfig/B_UnlockApproach] */
  /*    65 */  /* [/ActiveEcuC/Com/ComConfig/NFC_TGS_01_XIX_HCP4_CANFD01_6816bdec_Tx] */
  /*   ... */  /* [/ActiveEcuC/Com/ComConfig/NFC_TGS_01_XIX_HCP4_CANFD01_6816bdec_Tx] */
  /*    71 */  /* [/ActiveEcuC/Com/ComConfig/NFC_TGS_01_XIX_HCP4_CANFD01_6816bdec_Tx] */

#define COM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_TxCyclicProcessingISRLockCounter
**********************************************************************************************************************/
#define COM_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_TxCyclicProcessingISRLockCounterType, COM_VAR_NOINIT) Com_TxCyclicProcessingISRLockCounter;  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define COM_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_TxIPduGroupISRLockCounter
**********************************************************************************************************************/
#define COM_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_TxIPduGroupISRLockCounterType, COM_VAR_NOINIT) Com_TxIPduGroupISRLockCounter;  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define COM_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_TxPduGrpActive
**********************************************************************************************************************/
/** 
  \var    Com_TxPduGrpActive
  \brief  Tx I-PDU based state (started/stopped) of the corresponding I-PDU-Group.
*/ 
#define COM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_TxPduGrpActiveType, COM_VAR_NOINIT) Com_TxPduGrpActive[2];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx, /ActiveEcuC/Com/ComConfig/CommunicationControlTx] */
  /*     1 */  /* [/ActiveEcuC/Com/ComConfig/NFC_TGS_01_XIX_HCP4_CANFD01_6816bdec_Tx, /ActiveEcuC/Com/ComConfig/CommunicationControlTx] */

#define COM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_TxProcessingISRLockCounter
**********************************************************************************************************************/
#define COM_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_TxProcessingISRLockCounterType, COM_VAR_NOINIT) Com_TxProcessingISRLockCounter;  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define COM_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_TxSduLength
**********************************************************************************************************************/
/** 
  \var    Com_TxSduLength
  \brief  This var Array contains the Com Ipdu Length.
*/ 
#define COM_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_TxSduLengthType, COM_VAR_NOINIT) Com_TxSduLength[2];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Com/ComConfig/DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_7f57edc0_Tx, /ActiveEcuC/Com/ComConfig/CommunicationControlTx] */
  /*     1 */  /* [/ActiveEcuC/Com/ComConfig/NFC_TGS_01_XIX_HCP4_CANFD01_6816bdec_Tx, /ActiveEcuC/Com/ComConfig/CommunicationControlTx] */

#define COM_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */


/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL DATA
**********************************************************************************************************************/


/**********************************************************************************************************************
  LOCAL FUNCTION PROTOTYPES
**********************************************************************************************************************/



/**********************************************************************************************************************
  LOCAL FUNCTIONS
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL FUNCTIONS
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL FUNCTIONS
**********************************************************************************************************************/

/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL FUNCTIONS
**********************************************************************************************************************/






/**********************************************************************************************************************
  END OF FILE: Com_Lcfg.c
**********************************************************************************************************************/

