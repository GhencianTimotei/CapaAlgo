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
 *            Module: Can
 *           Program: VAG AR4 (MSR_Vag_SLP5)
 *          Customer: Huf H_lsbeck & F_rst GmbH & Co. KG
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: S32K144
 *    License Scope : The usage is restricted to CBD2100188_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: Can_Lcfg.c
 *   Generation Time: 2022-07-06 20:10:19
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
 * [Warning] CAN02002 - An invalid value is configured 
 * - [Reduced Severity due to User-Defined Parameter] The feature ( /ActiveEcuC/Can/CanConfigSet/CT_HCP4_CANFD01_a1aa3031[0:CanWakeupSupport](value=true)) is not supported but there is at least one CanWakeupSource configured.
 * Erroneous configuration elements:
 * /ActiveEcuC/Can/CanConfigSet/CT_HCP4_CANFD01_a1aa3031[0:CanWakeupSupport](value=true) (DefRef: /MICROSAR/Can_ImxFlexcan3/Can/CanConfigSet/CanController/CanWakeupSupport)
 *********************************************************************************************************************/

#define CAN_LCFG_SOURCE

/* PRQA S 0779 EOF */ /* MD_MSR_Rule5.2 */

/* -----------------------------------------------------------------------------
    Includes
 ----------------------------------------------------------------------------- */

#include "Can_Cfg.h"

/* -----------------------------------------------------------------------------
    Hw specific
 ----------------------------------------------------------------------------- */


/**********************************************************************************************************************
  ComStackLib
**********************************************************************************************************************/
/**********************************************************************************************************************
  LOCAL DATA PROTOTYPES
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: LOCAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/

/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: LOCAL DATA TYPES AND STRUCTURES
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
  Can_CanIfChannelId
**********************************************************************************************************************/
/** 
  \var    Can_CanIfChannelId
  \brief  indirection table Can to CanIf controller ID
*/ 
#define CAN_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Can_CanIfChannelIdType, CAN_CONST) Can_CanIfChannelId[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     CanIfChannelId      Comment */
  /*     0 */              0u   /* [CT_HCP4_CANFD01_a1aa3031] */
};
#define CAN_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Can_ControllerConfig
**********************************************************************************************************************/
/** 
  \var    Can_ControllerConfig
  \brief  Global configuration for all controllers
  \details
  Element                            Description
  BaseAddress                    
  CanControllerDefaultBaudrate   
  HasCANFDBaudrate               
  CanControllerDefaultBaudrateIdx
  FDHwChannelIndirection             This table contains indirection values for the Hw Channel for CANFD configurations.
  FDMailboxMaxWordLength         
  InterruptMask1                 
  MailboxRxBasicEndIdx               the end index of the 0:n relation pointing to Can_Mailbox
  MailboxRxBasicLength               the number of relations pointing to Can_Mailbox
  MailboxRxBasicStartIdx             the start index of the 0:n relation pointing to Can_Mailbox
  MailboxTxBasicEndIdx               the end index of the 0:n relation pointing to Can_Mailbox
  MailboxTxBasicLength               the number of relations pointing to Can_Mailbox
  MailboxTxBasicStartIdx             the start index of the 0:n relation pointing to Can_Mailbox
  MailboxUnusedEndIdx                the end index of the 0:n relation pointing to Can_Mailbox
  MailboxUnusedLength                the number of relations pointing to Can_Mailbox
  MailboxUnusedStartIdx              the start index of the 0:n relation pointing to Can_Mailbox
  NumberOfFilters                
  NumberOfFullConfigurableFilters
  NumberOfMaxMailboxes           
  RFFN                           
  RxBasicHwStart                 
  RxBasicHwStop                  
  RxFullHwStart                  
  RxFullHwStop                   
  TxBasicHwStart                 
  TxBasicHwStop                  
  TxFullHwStart                  
  TxFullHwStop                   
  UnusedHwStart                  
  UnusedHwStop                   
*/ 
#define CAN_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Can_ControllerConfigType, CAN_CONST) Can_ControllerConfig[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    BaseAddress  CanControllerDefaultBaudrate  HasCANFDBaudrate  CanControllerDefaultBaudrateIdx  FDHwChannelIndirection  FDMailboxMaxWordLength  InterruptMask1  MailboxRxBasicEndIdx                                                                                                                                                  MailboxRxBasicLength                                                                                                                                                  MailboxRxBasicStartIdx                                                                                                                                                  MailboxTxBasicEndIdx                                                                                                                                                  MailboxTxBasicLength                                                                                                                                                  MailboxTxBasicStartIdx                                                                                                                                                  MailboxUnusedEndIdx                                                                                                                                                 MailboxUnusedLength                                                                                                                                                 MailboxUnusedStartIdx                                                                                                                                                 NumberOfFilters  NumberOfFullConfigurableFilters  NumberOfMaxMailboxes  RFFN   RxBasicHwStart  RxBasicHwStop  RxFullHwStart  RxFullHwStop  TxBasicHwStart  TxBasicHwStop  TxFullHwStart  TxFullHwStop  UnusedHwStart  UnusedHwStop        Comment                                Referable Keys */
  { /*     0 */ 0x40024000u,                         500u,             TRUE,                              0u,                  0x00u,                  0x10u,          0x1Fu,                   3u  /* RX_BASICCAN_TYPE/ActiveEcuC/Can/CanConfigSet/CT_HCP4_CANFD01_a1aa3031 (DefRef: /MICROSAR/Can_ImxFlexcan3/Can/CanConfigSet/CanController) */,                   2u  /* RX_BASICCAN_TYPE/ActiveEcuC/Can/CanConfigSet/CT_HCP4_CANFD01_a1aa3031 (DefRef: /MICROSAR/Can_ImxFlexcan3/Can/CanConfigSet/CanController) */,                     1u  /* RX_BASICCAN_TYPE/ActiveEcuC/Can/CanConfigSet/CT_HCP4_CANFD01_a1aa3031 (DefRef: /MICROSAR/Can_ImxFlexcan3/Can/CanConfigSet/CanController) */,                   1u  /* TX_BASICCAN_TYPE/ActiveEcuC/Can/CanConfigSet/CT_HCP4_CANFD01_a1aa3031 (DefRef: /MICROSAR/Can_ImxFlexcan3/Can/CanConfigSet/CanController) */,                   1u  /* TX_BASICCAN_TYPE/ActiveEcuC/Can/CanConfigSet/CT_HCP4_CANFD01_a1aa3031 (DefRef: /MICROSAR/Can_ImxFlexcan3/Can/CanConfigSet/CanController) */,                     0u  /* TX_BASICCAN_TYPE/ActiveEcuC/Can/CanConfigSet/CT_HCP4_CANFD01_a1aa3031 (DefRef: /MICROSAR/Can_ImxFlexcan3/Can/CanConfigSet/CanController) */,                  4u  /* UNUSED_CAN_TYPE/ActiveEcuC/Can/CanConfigSet/CT_HCP4_CANFD01_a1aa3031 (DefRef: /MICROSAR/Can_ImxFlexcan3/Can/CanConfigSet/CanController) */,                  1u  /* UNUSED_CAN_TYPE/ActiveEcuC/Can/CanConfigSet/CT_HCP4_CANFD01_a1aa3031 (DefRef: /MICROSAR/Can_ImxFlexcan3/Can/CanConfigSet/CanController) */,                    3u  /* UNUSED_CAN_TYPE/ActiveEcuC/Can/CanConfigSet/CT_HCP4_CANFD01_a1aa3031 (DefRef: /MICROSAR/Can_ImxFlexcan3/Can/CanConfigSet/CanController) */,           0x00u,                           0x00u,                0x20u, 0x00u,             0u,            4u,            0u,           0u,             4u,            5u,            5u,           5u,            5u,           7u }   /* [CT_HCP4_CANFD01_a1aa3031] */  /* [/ActiveEcuC/Can/CanConfigSet/CT_HCP4_CANFD01_a1aa3031] */
};
#define CAN_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Can_FDMailboxMapping
**********************************************************************************************************************/
/** 
  \var    Can_FDMailboxMapping
  \brief  This table contains mapping from HwHandles to mailbox index of CAN Controller for CANFD configurations.
*/ 
#define CAN_START_SEC_CONST_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Can_FDMailboxMappingType, CAN_CONST) Can_FDMailboxMapping[5] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     FDMailboxMapping      Comment */
  /*     0 */       0x40024080u,  /* [Channel: "CT_HCP4_CANFD01_a1aa3031", channel index: 0, Mailbox Index: 0] */
  /*     1 */       0x400240C8u,  /* [Channel: "CT_HCP4_CANFD01_a1aa3031", channel index: 0, Mailbox Index: 1] */
  /*     2 */       0x40024110u,  /* [Channel: "CT_HCP4_CANFD01_a1aa3031", channel index: 0, Mailbox Index: 2] */
  /*     3 */       0x40024158u,  /* [Channel: "CT_HCP4_CANFD01_a1aa3031", channel index: 0, Mailbox Index: 3] */
  /*     4 */       0x400241A0u   /* [Channel: "CT_HCP4_CANFD01_a1aa3031", channel index: 0, Mailbox Index: 4] */
};
#define CAN_STOP_SEC_CONST_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Can_InitBasicCan
**********************************************************************************************************************/
/** 
  \var    Can_InitBasicCan
  \brief  This table contains acceptance filter configuration values.
  \details
  Element     Description
  InitCode
  InitMask
*/ 
#define CAN_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Can_InitBasicCanType, CAN_CONST) Can_InitBasicCan[4] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    InitCode     InitMask           Comment */
  { /*     0 */ 0x00000000u, 0x0003FFFFu },  /* [Channel: CT_HCP4_CANFD01_a1aa3031, Init object: 0, Filter: CanFilterMask] */
  { /*     1 */ 0x00000000u, 0x0003FFFFu },  /* [Channel: CT_HCP4_CANFD01_a1aa3031, Init object: 0, Filter: CanFilterMask] */
  { /*     2 */ 0x80000000u, 0x00000000u },  /* [Channel: CT_HCP4_CANFD01_a1aa3031, Init object: 0, Filter: CanFilterMask_001] */
  { /*     3 */ 0x80000000u, 0x00000000u }   /* [Channel: CT_HCP4_CANFD01_a1aa3031, Init object: 0, Filter: CanFilterMask_001] */
};
#define CAN_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Can_InitBasicCanIndex
**********************************************************************************************************************/
/** 
  \var    Can_InitBasicCanIndex
  \brief  This table contains start/stop indices for the Can_InitBasicCan table.
*/ 
#define CAN_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Can_InitBasicCanIndexType, CAN_CONST) Can_InitBasicCanIndex[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     InitBasicCanIndex                                                                               */
  /*     0 */              0x00u  /* Filter Start Index: Channel: CT_HCP4_CANFD01_a1aa3031, Init object: 0 */
};
#define CAN_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Can_InitObject
**********************************************************************************************************************/
/** 
  \var    Can_InitObject
  \brief  This table contains information about the init object: e.g. bustiming register contents.
  \details
  Element     Description
  CBT     
  Control1
*/ 
#define CAN_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Can_InitObjectType, CAN_CONST) Can_InitObject[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    CBT          Control1           Comment */
  { /*     0 */ 0x80E318E3u, 0x07FB2006u }   /* ["CT_HCP4_CANFD01_a1aa3031 - CanControllerBaudrateConfig", init object index: 0] */
};
#define CAN_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Can_InitObjectBaudrate
**********************************************************************************************************************/
/** 
  \var    Can_InitObjectBaudrate
  \brief  baudrates ('InitStruct' as index)
*/ 
#define CAN_START_SEC_CONST_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Can_InitObjectBaudrateType, CAN_CONST) Can_InitObjectBaudrate[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     InitObjectBaudrate      Comment */
  /*     0 */                500u   /* [CT_HCP4_CANFD01_a1aa3031 - CanControllerBaudrateConfig] */
};
#define CAN_STOP_SEC_CONST_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Can_InitObjectFD
**********************************************************************************************************************/
/** 
  \var    Can_InitObjectFD
  \brief  This table contains bittiming register values for the CAN-FD baudrate.
  \details
  Element    Description
  FDCBT  
  FDCTRL 
*/ 
#define CAN_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Can_InitObjectFDType, CAN_CONST) Can_InitObjectFD[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    FDCBT        FDCTRL             Comment */
  { /*     0 */ 0x00731CE3u, 0x80030000u }   /* ["CT_HCP4_CANFD01_a1aa3031 - CanControllerBaudrateConfig", init object index: 0] */
};
#define CAN_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Can_InitObjectFdBrsConfig
**********************************************************************************************************************/
/** 
  \var    Can_InitObjectFdBrsConfig
  \brief  FD config ('BaudrateObject' as index)
*/ 
#define CAN_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Can_InitObjectFdBrsConfigType, CAN_CONST) Can_InitObjectFdBrsConfig[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     InitObjectFdBrsConfig              */
  /*     0 */  CAN_FD_RXTX_INITOBJECTFDBRSCONFIG
};
#define CAN_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Can_InitObjectStartIndex
**********************************************************************************************************************/
/** 
  \var    Can_InitObjectStartIndex
  \brief  Start index of 'InitStruct' / baudratesets (controllers as index)
*/ 
#define CAN_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Can_InitObjectStartIndexType, CAN_CONST) Can_InitObjectStartIndex[2] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     InitObjectStartIndex      Comment */
  /*     0 */                    0u,  /* [CT_HCP4_CANFD01_a1aa3031] */
  /*     1 */                    1u   /* [stop index] */
};
#define CAN_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Can_Mailbox
**********************************************************************************************************************/
/** 
  \var    Can_Mailbox
  \brief  mailbox configuration (over all controllers)
  \details
  Element                Description
  ActiveSendObject   
  ControllerConfigIdx    the index of the 1:1 relation pointing to Can_ControllerConfig
  FdPadding          
  HwHandle           
  IDValue            
  MailboxSize        
  MailboxType        
  MaxDataLen         
  MemorySectionsIndex
*/ 
#define CAN_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Can_MailboxType, CAN_CONST) Can_Mailbox[4] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    ActiveSendObject  ControllerConfigIdx                                                               FdPadding  HwHandle  IDValue  MailboxSize  MailboxType                                MaxDataLen  MemorySectionsIndex        Comment                                   Referable Keys */
  { /*     0 */               0u,                  0u  /* /ActiveEcuC/Can/CanConfigSet/CT_HCP4_CANFD01_a1aa3031 */,        0u,       4u,   0x00u,          1u, CAN_TX_BASICCAN_TYPE_MAILBOXTYPEOFMAILBOX,        64u,                  4u },  /* [CN_HCP4_CANFD01_152fd6c6_Tx] */  /* [/ActiveEcuC/Can/CanConfigSet/CN_HCP4_CANFD01_152fd6c6_Tx (DefRef: /MICROSAR/Can_ImxFlexcan3/Can/CanConfigSet/CanHardwareObject), /ActiveEcuC/Can/CanConfigSet/CT_HCP4_CANFD01_a1aa3031, TX_BASICCAN_TYPE/ActiveEcuC/Can/CanConfigSet/CT_HCP4_CANFD01_a1aa3031 (DefRef: /MICROSAR/Can_ImxFlexcan3/Can/CanConfigSet/CanController)] */
  { /*     1 */               0u,                  0u  /* /ActiveEcuC/Can/CanConfigSet/CT_HCP4_CANFD01_a1aa3031 */,        0u,       0u,   0x00u,          2u, CAN_RX_BASICCAN_TYPE_MAILBOXTYPEOFMAILBOX,        64u,                  0u },  /* [CN_HCP4_CANFD01_9945d1af_Rx] */  /* [/ActiveEcuC/Can/CanConfigSet/CN_HCP4_CANFD01_9945d1af_Rx (DefRef: /MICROSAR/Can_ImxFlexcan3/Can/CanConfigSet/CanHardwareObject), /ActiveEcuC/Can/CanConfigSet/CT_HCP4_CANFD01_a1aa3031, RX_BASICCAN_TYPE/ActiveEcuC/Can/CanConfigSet/CT_HCP4_CANFD01_a1aa3031 (DefRef: /MICROSAR/Can_ImxFlexcan3/Can/CanConfigSet/CanController)] */
  { /*     2 */               0u,                  0u  /* /ActiveEcuC/Can/CanConfigSet/CT_HCP4_CANFD01_a1aa3031 */,        0u,       2u,   0x00u,          2u, CAN_RX_BASICCAN_TYPE_MAILBOXTYPEOFMAILBOX,        64u,                  2u },  /* [CN_HCP4_CANFD01_ac0f8757_Rx] */  /* [/ActiveEcuC/Can/CanConfigSet/CN_HCP4_CANFD01_ac0f8757_Rx (DefRef: /MICROSAR/Can_ImxFlexcan3/Can/CanConfigSet/CanHardwareObject), /ActiveEcuC/Can/CanConfigSet/CT_HCP4_CANFD01_a1aa3031, RX_BASICCAN_TYPE/ActiveEcuC/Can/CanConfigSet/CT_HCP4_CANFD01_a1aa3031 (DefRef: /MICROSAR/Can_ImxFlexcan3/Can/CanConfigSet/CanController)] */
  { /*     3 */               0u,                  0u  /* /ActiveEcuC/Can/CanConfigSet/CT_HCP4_CANFD01_a1aa3031 */,        0u,       5u,   0x00u,          2u,  CAN_UNUSED_CAN_TYPE_MAILBOXTYPEOFMAILBOX,         0u,                  5u }   /* []                            */  /* [undefined, /ActiveEcuC/Can/CanConfigSet/CT_HCP4_CANFD01_a1aa3031, UNUSED_CAN_TYPE/ActiveEcuC/Can/CanConfigSet/CT_HCP4_CANFD01_a1aa3031 (DefRef: /MICROSAR/Can_ImxFlexcan3/Can/CanConfigSet/CanController)] */
};
#define CAN_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Can_MemorySectionInfo
**********************************************************************************************************************/
/** 
  \var    Can_MemorySectionInfo
  \brief  Memory section description
  \details
  Element               Description
  MemoryStartAddress
  MemorySectionStart
*/ 
#define CAN_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Can_MemorySectionInfoType, CAN_CONST) Can_MemorySectionInfo[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    MemoryStartAddress  MemorySectionStart        Comment */
  { /*     0 */        0x40024000u,                 0u }   /* [MemorySection: Memory_0] */
};
#define CAN_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Can_MemorySectionObjects
**********************************************************************************************************************/
/** 
  \var    Can_MemorySectionObjects
  \brief  Memory section objects description
  \details
  Element           Description
  HwHandle      
  MailboxElement
  MailboxHandle 
*/ 
#define CAN_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Can_MemorySectionObjectsType, CAN_CONST) Can_MemorySectionObjects[7] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    HwHandle  MailboxElement  MailboxHandle        Comment */
  { /*     0 */       0u,             0u,            1u },  /* [Memory_0 - CN_HCP4_CANFD01_9945d1af_Rx] */
  { /*     1 */       1u,             1u,            1u },  /* [Memory_0 - CN_HCP4_CANFD01_9945d1af_Rx] */
  { /*     2 */       2u,             0u,            2u },  /* [Memory_0 - CN_HCP4_CANFD01_ac0f8757_Rx] */
  { /*     3 */       3u,             1u,            2u },  /* [Memory_0 - CN_HCP4_CANFD01_ac0f8757_Rx] */
  { /*     4 */       4u,             0u,            0u },  /* [Memory_0 - CN_HCP4_CANFD01_152fd6c6_Tx] */
  { /*     5 */       5u,             0u,            0u },  /* [Memory_0 - Unused] */
  { /*     6 */       6u,             0u,            0u }   /* [Memory_0 - Unused] */
};
#define CAN_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Can_ActiveSendObject
**********************************************************************************************************************/
/** 
  \var    Can_ActiveSendObject
  \brief  temporary data for TX object
  \details
  Element    Description
  State      send state like cancelled or send activ
  Pdu        buffered PduId for confirmation or cancellation
*/ 
#define CAN_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Can_ActiveSendObjectType, CAN_VAR_NOINIT) Can_ActiveSendObject[1];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define CAN_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Can_ControllerData
**********************************************************************************************************************/
/** 
  \var    Can_ControllerData
  \brief  struct for all controller related variable data
  \details
  Element                      Description
  BusOffCounter                This variable stores the busoff recovery timeout counter.
  BusOffTransitionRequest      CAN state request for each controller: ContinueBusOffRecovery=0x00, FinishBusOffRecovery=0x01
  CanInterruptCounter          CAN interrupt disable counter for each controller
  IsBusOff                     CAN state for each controller: busoff occur
  LastInitObject               last set baudrate for reinit
  LogStatus                    CAN state for each controller: UNINIT=0x00, START=0x01, STOP=0x02, INIT=0x04, INCONSISTENT=0x08, WARNING =0x10, PASSIVE=0x20, BUSOFF=0x40, SLEEP=0x80
  ModeTransitionRequest        CAN state request for each controller: INIT=0x00, SLEEP=0x01, WAKEUP=0x02, STOP+INIT=0x03, START=0x04, START+INIT=0x05, NONE=0x06
  RamCheckTransitionRequest    CAN state request for each controller: kCanSuppressRamCheck=0x01, kCanExecuteRamCheck=0x00
  StartModeRequested           This variable stores if the start mode is of a special CAN Controller is already requested in the busoff recovery process.
  CanInterruptOldStatus        last CAN interrupt status for restore interrupt for each controller
  LoopTimeout                  hw loop timeout for each controller
  RxMsgBuffer                  This variable stores received values (ID, DLC, DATA) in the reception process.
*/ 
#define CAN_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Can_ControllerDataType, CAN_VAR_NOINIT) Can_ControllerData[1];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define CAN_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */


/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL DATA
**********************************************************************************************************************/




