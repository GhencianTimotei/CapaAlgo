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
 *              File: Can_Cfg.h
 *   Generation Time: 2022-05-18 14:23:33
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
/* -----------------------------------------------------------------------------
    Generator Info
 ----------------------------------------------------------------------------- 
  Name:     MICROSAR Can Flexcan3 driver Generator
  Version:  3.13.00
  MSN:      Can
  Origin:   CAN
  Descrip:  MICROSAR Can driver generator
  JavaPack: com.vector.cfg.gen.DrvCan_ImxFlexcan3Asr
 ----------------------------------------------------------------------------- */

#if !defined(CAN_CFG_H)
#define CAN_CFG_H

/* CAN222, CAN389, CAN365, CAN366, CAN367 */
/* CAN022, CAN047, CAN388, CAN397, CAN390, CAN392  */

/* PRQA S 0779 EOF */ /* MD_MSR_Rule5.2 */

/* -----------------------------------------------------------------------------
    Includes
 ----------------------------------------------------------------------------- */

#include "ComStack_Types.h"

#include "Can_GeneralTypes.h" /* CAN435 */

#if defined (CAN_LCFG_SOURCE) || defined (C_DRV_INTERNAL) /* ESCAN00070085 */
# include "Os.h"
#endif

/* -----------------------------------------------------------------------------
    General Switches for CAN module
 ----------------------------------------------------------------------------- */

#ifndef CAN_USE_DUMMY_STATEMENT
#define CAN_USE_DUMMY_STATEMENT STD_ON /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef CAN_DUMMY_STATEMENT
#define CAN_DUMMY_STATEMENT(v) (v)=(v) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef CAN_DUMMY_STATEMENT_CONST
#define CAN_DUMMY_STATEMENT_CONST(v) (void)(v) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef CAN_ATOMIC_BIT_ACCESS_IN_BITFIELD
#define CAN_ATOMIC_BIT_ACCESS_IN_BITFIELD STD_OFF /* /MICROSAR/EcuC/EcucGeneral/AtomicBitAccessInBitfield */
#endif
#ifndef CAN_ATOMIC_VARIABLE_ACCESS
#define CAN_ATOMIC_VARIABLE_ACCESS 32u /* /MICROSAR/EcuC/EcucGeneral/AtomicVariableAccess */
#endif
#ifndef CAN_PROCESSOR_S32K144
#define CAN_PROCESSOR_S32K144
#endif
#ifndef CAN_COMP_IAR
#define CAN_COMP_IAR
#endif
#ifndef CAN_GEN_GENERATOR_MSR
#define CAN_GEN_GENERATOR_MSR
#endif
#ifndef CAN_CPUTYPE_BITORDER_LSB2MSB
#define CAN_CPUTYPE_BITORDER_LSB2MSB /* /MICROSAR/vSet/vSetPlatform/vSetBitOrder */
#endif
#ifndef CAN_CONFIGURATION_VARIANT_PRECOMPILE
#define CAN_CONFIGURATION_VARIANT_PRECOMPILE 1
#endif
#ifndef CAN_CONFIGURATION_VARIANT_LINKTIME
#define CAN_CONFIGURATION_VARIANT_LINKTIME 2
#endif
#ifndef CAN_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE
#define CAN_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE 3
#endif
#ifndef CAN_CONFIGURATION_VARIANT
#define CAN_CONFIGURATION_VARIANT CAN_CONFIGURATION_VARIANT_PRECOMPILE
#endif
#ifndef CAN_POSTBUILD_VARIANT_SUPPORT
#define CAN_POSTBUILD_VARIANT_SUPPORT STD_OFF
#endif


/* -----------------------------------------------------------------------------
    General Switches from old v_cfg.h
 ----------------------------------------------------------------------------- */
#if !defined(V_GEN_GENERATOR5)
# define V_GEN_GENERATOR5 /* need by LL */
#endif
#if !defined(V_ENABLE_CAN_ASR_ABSTRACTION)
# define V_ENABLE_CAN_ASR_ABSTRACTION /* ATK */
#endif
#define CAN_GEN_COM_STACK_LIB

#if !defined( V_OSTYPE_AUTOSAR )
# define V_OSTYPE_AUTOSAR
#endif

#if (CPU_TYPE == CPU_TYPE_32)
# if !defined( C_CPUTYPE_32BIT )
#  define C_CPUTYPE_32BIT
# endif
#endif
#if (CPU_TYPE == CPU_TYPE_16)
# if !defined( C_CPUTYPE_16BIT )
#  define C_CPUTYPE_16BIT
# endif
#endif
#if (CPU_TYPE == CPU_TYPE_8)
# if !defined( C_CPUTYPE_8BIT )
#  define C_CPUTYPE_8BIT
# endif
#endif
#if (CPU_BIT_ORDER == LSB_FIRST)
# if !defined( C_CPUTYPE_BITORDER_LSB2MSB )
#  define C_CPUTYPE_BITORDER_LSB2MSB
# endif
#endif
#if (CPU_BIT_ORDER == MSB_FIRST)
# if !defined( C_CPUTYPE_BITORDER_MSB2LSB )
#  define C_CPUTYPE_BITORDER_MSB2LSB
# endif
#endif
#if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
# if !defined( C_CPUTYPE_LITTLEENDIAN )
#  define C_CPUTYPE_LITTLEENDIAN
# endif
#endif
#if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
# if !defined( C_CPUTYPE_BIGENDIAN )
#  define C_CPUTYPE_BIGENDIAN
# endif
#endif

#if !defined( V_DISABLE_USE_DUMMY_FUNCTIONS )
# define V_DISABLE_USE_DUMMY_FUNCTIONS
#endif
#if !defined( V_ENABLE_USE_DUMMY_STATEMENT )
# define V_ENABLE_USE_DUMMY_STATEMENT
#endif

#if !defined( V_CPU_S32 )
# define V_CPU_S32
#endif

#if !defined( C_PROCESSOR_S32K144 )
# define C_PROCESSOR_S32K144
#endif
#if !defined( V_PROCESSOR_S32K144 )
# define V_PROCESSOR_S32K144
#endif

#if !defined( C_COMP_IAR_S32_FLEXCAN3 )
#define C_COMP_IAR_S32_FLEXCAN3
#endif
#if !defined( V_COMP_IAR )
# define V_COMP_IAR
#endif
#if !defined( V_COMP_IAR_S32 )
# define V_COMP_IAR_S32
#endif

#if !defined( V_SUPPRESS_EXTENDED_VERSION_CHECK )
# define V_SUPPRESS_EXTENDED_VERSION_CHECK
#endif

/* -----------------------------------------------------------------------------
    Version defines
 ----------------------------------------------------------------------------- */

/* CAN024, CAN023 */
#define CAN_ASR_VERSION              0x0400u
#define CAN_GEN_BASE_CFG5_VERSION    0x0103u
#define CAN_GEN_BASESASR_VERSION     0x0407u
#define CAN_GEN_ImxFlexcan3Asr_VERSION              0x0101u
#define CAN_MICROSAR_VERSION         CAN_MSR403

/* -----------------------------------------------------------------------------
    Hardcoded defines
 ----------------------------------------------------------------------------- */

#define CAN_INSTANCE_ID           0

#define CAN_RX_BASICCAN_TYPE                 0u
#define CAN_RX_FULLCAN_TYPE                  1u
#define CAN_TX_BASICCAN_TYPE                 2u
#define CAN_TX_FULLCAN_TYPE                  3u
#define CAN_UNUSED_CAN_TYPE                  4u
#define CAN_TX_BASICCAN_MUX_TYPE             5u
#define CAN_TX_BASICCAN_FIFO_TYPE            6u

#define CAN_INTERRUPT                        0u
#define CAN_POLLING                          1u

#define kCanChannelNotUsed                     CAN_NO_CANIFCHANNELID 

#define CAN_NONE                             0u
/* RAM check (also  none) */
#define CAN_NOTIFY_ISSUE                     1u
#define CAN_NOTIFY_MAILBOX                   2u
#define CAN_EXTENDED                         3u
/* Interrupt lock (also  none) */
#define CAN_DRIVER                           1u
#define CAN_APPL                             2u
#define CAN_BOTH                             3u
/* Overrun Notification (als none,appl) */
#define CAN_DET                              1u
/* CAN FD Support */
#define CAN_BRS                              1u
#define CAN_FULL                             2u
/* CAN FD Configuration */
#define CAN_FD_RXONLY                        2u /* FD Baudrate exist (RX) */
#define CAN_FD_RXTX                          1u /* FD Baudrate also used for TX */
/* Generic Confirmation */
#define CAN_API1                             1u
#define CAN_API2                             2u

#define CAN_OS_TICK2MS(tick)     OS_TICKS2MS_SystemTimer((tick))     /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CAN_OS_COUNTER_ID        SystemTimer

/* -----------------------------------------------------------------------------
    Defines / Switches
 ----------------------------------------------------------------------------- */

/* Version and Issue detection */
#define CAN_VERSION_INFO_API                 STD_OFF   /* CAN106_Conf */
#define CAN_DEV_ERROR_DETECT                 STD_ON   /* CAN064_Conf */
#define CAN_DEV_ERROR_REPORT                 STD_ON
#define CAN_SAFE_BSW                         STD_OFF

/* Interrupt / Polling */
#define CAN_TX_PROCESSING                    CAN_INTERRUPT   /* CAN318_Conf */
#define CAN_RX_PROCESSING                    CAN_INTERRUPT   /* CAN317_Conf */
#define CAN_BUSOFF_PROCESSING                CAN_INTERRUPT   /* CAN314_Conf */
#define CAN_WAKEUP_PROCESSING                CAN_INTERRUPT   /* CAN319_Conf */
#define CAN_INDIVIDUAL_PROCESSING            STD_OFF
#define CAN_INTERRUPT_USED                   STD_ON
#define CAN_NESTED_INTERRUPTS                STD_OFF
#define C_DISABLE_OSEK_OS_INTCAT2
#define C_DISABLE_ISRVOID
#define CAN_INTLOCK                          CAN_DRIVER

/* Tx Handling */
#define CAN_MULTIPLEXED_TX_MAX               1u
#define CAN_CANCEL_SUPPORT_API               STD_OFF
#define CAN_TRANSMIT_BUFFER                  STD_ON
#define CAN_MULTIPLEXED_TRANSMISSION         STD_OFF   /* CAN095_Conf */
#define CAN_TX_HW_FIFO                       STD_OFF
#define CAN_HW_TRANSMIT_CANCELLATION         STD_OFF   /* CAN069_Conf */
#define CAN_IDENTICAL_ID_CANCELLATION        STD_OFF   /* CAN378_Conf */
#define CAN_MULTIPLE_BASICCAN_TX             STD_OFF

/* Rx Handling */
#define CAN_MULTIPLE_BASICCAN                STD_OFF
#define CAN_RX_QUEUE                         STD_OFF
#define CAN_OVERRUN_NOTIFICATION             CAN_DET

/* Sleep Wakeup */
#define CAN_SLEEP_SUPPORT                    STD_OFF
#define CAN_WAKEUP_SUPPORT                   STD_OFF   /* CAN330_Conf */

/* Hardware loop check */
#define CAN_HARDWARE_CANCELLATION            STD_ON
#define CAN_TIMEOUT_DURATION                 10uL   /* CAN113_Conf */
#define CAN_LOOP_MAX                         5u

/* Appl calls */
#define CAN_HW_LOOP_SUPPORT_API              STD_OFF
#define CAN_GENERIC_PRECOPY                  STD_OFF
#define CAN_GENERIC_CONFIRMATION             STD_OFF
#define CAN_GENERIC_PRETRANSMIT              STD_OFF
#define CAN_USE_OS_INTERRUPT_CONTROL         STD_OFF

/* Optimization */
#define CAN_RX_FULLCAN_OBJECTS               STD_OFF
#define CAN_TX_FULLCAN_OBJECTS               STD_OFF
#define CAN_RX_BASICCAN_OBJECTS              STD_ON
#define CAN_EXTENDED_ID                      STD_ON
#define CAN_MIXED_ID                         STD_ON
#define CAN_ONE_CONTROLLER_OPTIMIZATION      STD_ON
#define CAN_CHANGE_BAUDRATE_API              STD_OFF   /* CAN460_Conf */
#define CAN_FD_HW_BUFFER_OPTIMIZATION        STD_OFF

/* CAN FD */
#define CAN_SET_BAUDRATE_API                 STD_OFF   /* CAN482_Conf */
#define CAN_FD_SUPPORT                       CAN_FULL

/* Other */
#define CAN_COMMON_CAN                       STD_OFF
#define CAN_RAM_CHECK                        CAN_NONE
#define CAN_REINIT_START                     STD_OFF
#define CAN_GET_STATUS                       STD_OFF
#define CAN_RUNTIME_MEASUREMENT_SUPPORT      STD_OFF
#define CAN_PROTECTED_MODE                   STD_OFF
#define CAN_MIRROR_MODE                      STD_OFF
#define CAN_SILENT_MODE                      STD_OFF
#define CAN_CHECK_WAKEUP_CAN_RET_TYPE        STD_OFF
/* -----------------------------------------------------------------------------
    Channel And Mailbox
 ----------------------------------------------------------------------------- */
#ifndef C_DRV_INTERNAL
# ifndef kCanNumberOfChannels
#  define kCanNumberOfChannels               1u
# endif
# ifndef kCanNumberOfHwChannels
#  define kCanNumberOfHwChannels             1u
# endif
#endif
#ifndef kCanNumberOfUsedChannels /* ATK only */
# define kCanNumberOfUsedChannels            1u
#endif

#define kCanPhysToLogChannelIndex_0 

#define kCanNumberOfPhysChannels             1u

/* -----------------------------------------------------------------------------
    Symbolic Name Values for Controller, HardwareObject and Baudrates
 ----------------------------------------------------------------------------- */
/* These definitions can change at Link-time and Post-build configuration time. Use them wisely. */



/**
 * \defgroup CanHandleIdsactivated Handle IDs of handle space activated.
 * \brief controllers by CanControllerActivation
 * \{
 */

/* Handle IDs active in all predefined variants (the application has not to take the active variant into account) */
/*      Symbolic Name                                                 Value   Active in predefined variant(s) */
#define CanConf_CanController_CT_HCP4_CANFD01_a1aa3031                0u
/**\} */
#define CanConf_CN_HCP4_CANFD01_152fd6c6_Tx 0u
#define CanConf_CN_HCP4_CANFD01_9945d1af_Rx 1u
#define CanConf_CN_HCP4_CANFD01_ac0f8757_Rx 2u

#define CanConf_ControllerBaudrateConfig_CT_HCP4_CANFD01_a1aa3031_CanControllerBaudrateConfig 0u

#define CanConf_MemorySection_Memory_0 0u



/* -----------------------------------------------------------------------------
    Types
 ----------------------------------------------------------------------------- */
/* HW specific BEGIN */
/* Hw specific defines */
#define C_DISABLE_TASD
#define C_DISABLE_GLITCH_FILTER
#define C_DISABLE_FLEXCAN_STOP_MODE
#define C_DISABLE_FLEXCAN_PARITY_CHECK_AVAILABLE
#define C_DISABLE_MB32TO63
#define C_DISABLE_MB64TO95
#define C_DISABLE_MB96TO127
#define C_ENABLE_ASYM_MAILBOXES
#define C_DISABLE_INTERRUPT_SOURCE_SINGLE
#define C_ENABLE_INTERRUPT_SOURCE_MULTIPLE
#define C_ENABLE_CLKSRC_SELECTION

#if !defined( C_ENABLE_EXTENDED_BITTIMING ) && !defined( C_DISABLE_EXTENDED_BITTIMING )
# define C_ENABLE_EXTENDED_BITTIMING
#endif

#define C_DISABLE_WORKAROUND_ERR005829

#define C_DISABLE_WORKAROUND_ERR010368

#define C_ENABLE_ISO_CANFD

typedef struct tCanLLCanIntOldTag
{
  uint32 flags1;
  uint32 canctrl1;
  uint16 canmcr;
} tCanLLCanIntOld;

typedef struct tCanRxMsgBufferTag
{
  uint16 control;
  uint16 timestamp;
  uint32 msgID;
  uint32 data[16];
} tCanRxMsgBuffer;
 
/* HW specific END */ 

typedef VAR(uint16, TYPEDEF) CanChannelHandle;

#if defined (CAN_LCFG_SOURCE) || defined (C_DRV_INTERNAL)
typedef TickType Can_ExternalTickType;
#else
typedef uint32 Can_ExternalTickType;
#endif

typedef VAR(Can_ExternalTickType, TYPEDEF) Can_LoopTimeout_dim_type[CAN_LOOP_MAX+1u];




/* -----------------------------------------------------------------------------
    CONST Declarations
 ----------------------------------------------------------------------------- */

/* -----------------------------------------------------------------------------
    VAR Declarations
 ----------------------------------------------------------------------------- */

/* -----------------------------------------------------------------------------
    Hw specific
 ----------------------------------------------------------------------------- */
/* HW specific BEGIN */

/* HW specific END */


/**********************************************************************************************************************
  ComStackLib
**********************************************************************************************************************/
/* Can_GlobalConfig: CAN354_Conf */
/* Can_ConfigType: CAN413 */

/**********************************************************************************************************************
  GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/** 
  \defgroup  CanPCDataSwitches  Can Data Switches  (PRE_COMPILE)
  \brief  These defines are used to deactivate data and their processing.
  \{
*/ 
#define CAN_ACTIVESENDOBJECT                                          STD_ON
#define CAN_PDUOFACTIVESENDOBJECT                                     STD_ON
#define CAN_STATEOFACTIVESENDOBJECT                                   STD_ON
#define CAN_BASEDLL_GENERATORVERSION                                  STD_ON
#define CAN_CANIFCHANNELID                                            STD_ON
#define CAN_CONTROLLERCONFIG                                          STD_ON
#define CAN_BASEADDRESSOFCONTROLLERCONFIG                             STD_ON
#define CAN_CANCONTROLLERDEFAULTBAUDRATEIDXOFCONTROLLERCONFIG         STD_ON
#define CAN_CANCONTROLLERDEFAULTBAUDRATEOFCONTROLLERCONFIG            STD_ON
#define CAN_FDHWCHANNELINDIRECTIONOFCONTROLLERCONFIG                  STD_ON
#define CAN_FDMAILBOXMAXWORDLENGTHOFCONTROLLERCONFIG                  STD_ON
#define CAN_HASCANFDBAUDRATEOFCONTROLLERCONFIG                        STD_ON
#define CAN_INTERRUPTMASK1OFCONTROLLERCONFIG                          STD_ON
#define CAN_MAILBOXRXBASICENDIDXOFCONTROLLERCONFIG                    STD_ON
#define CAN_MAILBOXRXBASICLENGTHOFCONTROLLERCONFIG                    STD_ON
#define CAN_MAILBOXRXBASICSTARTIDXOFCONTROLLERCONFIG                  STD_ON
#define CAN_MAILBOXRXBASICUSEDOFCONTROLLERCONFIG                      STD_ON
#define CAN_MAILBOXRXFULLENDIDXOFCONTROLLERCONFIG                     STD_OFF  /**< Deactivateable: 'Can_ControllerConfig.MailboxRxFullEndIdx' Reason: 'the optional indirection is deactivated because MailboxRxFullUsedOfControllerConfig is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define CAN_MAILBOXRXFULLLENGTHOFCONTROLLERCONFIG                     STD_OFF  /**< Deactivateable: 'Can_ControllerConfig.MailboxRxFullLength' Reason: 'the optional indirection is deactivated because MailboxRxFullUsedOfControllerConfig is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define CAN_MAILBOXRXFULLSTARTIDXOFCONTROLLERCONFIG                   STD_OFF  /**< Deactivateable: 'Can_ControllerConfig.MailboxRxFullStartIdx' Reason: 'the optional indirection is deactivated because MailboxRxFullUsedOfControllerConfig is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define CAN_MAILBOXRXFULLUSEDOFCONTROLLERCONFIG                       STD_OFF  /**< Deactivateable: 'Can_ControllerConfig.MailboxRxFullUsed' Reason: 'the optional indirection is deactivated because MailboxRxFullUsedOfControllerConfig is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define CAN_MAILBOXTXBASICENDIDXOFCONTROLLERCONFIG                    STD_ON
#define CAN_MAILBOXTXBASICLENGTHOFCONTROLLERCONFIG                    STD_ON
#define CAN_MAILBOXTXBASICSTARTIDXOFCONTROLLERCONFIG                  STD_ON
#define CAN_MAILBOXTXBASICUSEDOFCONTROLLERCONFIG                      STD_ON
#define CAN_MAILBOXTXFULLENDIDXOFCONTROLLERCONFIG                     STD_OFF  /**< Deactivateable: 'Can_ControllerConfig.MailboxTxFullEndIdx' Reason: 'the optional indirection is deactivated because MailboxTxFullUsedOfControllerConfig is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define CAN_MAILBOXTXFULLLENGTHOFCONTROLLERCONFIG                     STD_OFF  /**< Deactivateable: 'Can_ControllerConfig.MailboxTxFullLength' Reason: 'the optional indirection is deactivated because MailboxTxFullUsedOfControllerConfig is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define CAN_MAILBOXTXFULLSTARTIDXOFCONTROLLERCONFIG                   STD_OFF  /**< Deactivateable: 'Can_ControllerConfig.MailboxTxFullStartIdx' Reason: 'the optional indirection is deactivated because MailboxTxFullUsedOfControllerConfig is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define CAN_MAILBOXTXFULLUSEDOFCONTROLLERCONFIG                       STD_OFF  /**< Deactivateable: 'Can_ControllerConfig.MailboxTxFullUsed' Reason: 'the optional indirection is deactivated because MailboxTxFullUsedOfControllerConfig is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define CAN_MAILBOXUNUSEDENDIDXOFCONTROLLERCONFIG                     STD_ON
#define CAN_MAILBOXUNUSEDLENGTHOFCONTROLLERCONFIG                     STD_ON
#define CAN_MAILBOXUNUSEDSTARTIDXOFCONTROLLERCONFIG                   STD_ON
#define CAN_MAILBOXUNUSEDUSEDOFCONTROLLERCONFIG                       STD_ON
#define CAN_NUMBEROFFILTERSOFCONTROLLERCONFIG                         STD_ON
#define CAN_NUMBEROFFULLCONFIGURABLEFILTERSOFCONTROLLERCONFIG         STD_ON
#define CAN_NUMBEROFMAXMAILBOXESOFCONTROLLERCONFIG                    STD_ON
#define CAN_RFFNOFCONTROLLERCONFIG                                    STD_ON
#define CAN_RXBASICHWSTARTOFCONTROLLERCONFIG                          STD_ON
#define CAN_RXBASICHWSTOPOFCONTROLLERCONFIG                           STD_ON
#define CAN_RXFULLHWSTARTOFCONTROLLERCONFIG                           STD_ON
#define CAN_RXFULLHWSTOPOFCONTROLLERCONFIG                            STD_ON
#define CAN_TXBASICHWSTARTOFCONTROLLERCONFIG                          STD_ON
#define CAN_TXBASICHWSTOPOFCONTROLLERCONFIG                           STD_ON
#define CAN_TXFULLHWSTARTOFCONTROLLERCONFIG                           STD_ON
#define CAN_TXFULLHWSTOPOFCONTROLLERCONFIG                            STD_ON
#define CAN_UNUSEDHWSTARTOFCONTROLLERCONFIG                           STD_ON
#define CAN_UNUSEDHWSTOPOFCONTROLLERCONFIG                            STD_ON
#define CAN_CONTROLLERDATA                                            STD_ON
#define CAN_BUSOFFCOUNTEROFCONTROLLERDATA                             STD_ON
#define CAN_BUSOFFTRANSITIONREQUESTOFCONTROLLERDATA                   STD_ON
#define CAN_CANINTERRUPTCOUNTEROFCONTROLLERDATA                       STD_ON
#define CAN_CANINTERRUPTOLDSTATUSOFCONTROLLERDATA                     STD_ON
#define CAN_ISBUSOFFOFCONTROLLERDATA                                  STD_ON
#define CAN_LASTINITOBJECTOFCONTROLLERDATA                            STD_ON
#define CAN_LOGSTATUSOFCONTROLLERDATA                                 STD_ON
#define CAN_LOOPTIMEOUTOFCONTROLLERDATA                               STD_ON
#define CAN_MODETRANSITIONREQUESTOFCONTROLLERDATA                     STD_ON
#define CAN_RAMCHECKTRANSITIONREQUESTOFCONTROLLERDATA                 STD_ON
#define CAN_RXMSGBUFFEROFCONTROLLERDATA                               STD_ON
#define CAN_STARTMODEREQUESTEDOFCONTROLLERDATA                        STD_ON
#define CAN_FDMAILBOXMAPPING                                          STD_ON
#define CAN_FINALMAGICNUMBER                                          STD_OFF  /**< Deactivateable: 'Can_FinalMagicNumber' Reason: 'the module configuration does not support flashing of data.' */
#define CAN_INITBASICCAN                                              STD_ON
#define CAN_INITCODEOFINITBASICCAN                                    STD_ON
#define CAN_INITMASKOFINITBASICCAN                                    STD_ON
#define CAN_INITBASICCANINDEX                                         STD_ON
#define CAN_INITDATAHASHCODE                                          STD_OFF  /**< Deactivateable: 'Can_InitDataHashCode' Reason: 'the module configuration does not support flashing of data.' */
#define CAN_INITOBJECT                                                STD_ON
#define CAN_CBTOFINITOBJECT                                           STD_ON
#define CAN_CONTROL1OFINITOBJECT                                      STD_ON
#define CAN_INITOBJECTBAUDRATE                                        STD_ON
#define CAN_INITOBJECTFD                                              STD_ON
#define CAN_FDCBTOFINITOBJECTFD                                       STD_ON
#define CAN_FDCTRLOFINITOBJECTFD                                      STD_ON
#define CAN_INITOBJECTFDBRSCONFIG                                     STD_ON
#define CAN_INITOBJECTSTARTINDEX                                      STD_ON
#define CAN_MAILBOX                                                   STD_ON
#define CAN_ACTIVESENDOBJECTOFMAILBOX                                 STD_ON
#define CAN_CONTROLLERCONFIGIDXOFMAILBOX                              STD_ON
#define CAN_FDPADDINGOFMAILBOX                                        STD_ON
#define CAN_HWHANDLEOFMAILBOX                                         STD_ON
#define CAN_IDVALUEOFMAILBOX                                          STD_ON
#define CAN_MAILBOXSIZEOFMAILBOX                                      STD_ON
#define CAN_MAILBOXTYPEOFMAILBOX                                      STD_ON
#define CAN_MAXDATALENOFMAILBOX                                       STD_ON
#define CAN_MEMORYSECTIONSINDEXOFMAILBOX                              STD_ON
#define CAN_MEMORYSECTIONINFO                                         STD_ON
#define CAN_MEMORYSECTIONSTARTOFMEMORYSECTIONINFO                     STD_ON
#define CAN_MEMORYSTARTADDRESSOFMEMORYSECTIONINFO                     STD_ON
#define CAN_MEMORYSECTIONOBJECTS                                      STD_ON
#define CAN_HWHANDLEOFMEMORYSECTIONOBJECTS                            STD_ON
#define CAN_MAILBOXELEMENTOFMEMORYSECTIONOBJECTS                      STD_ON
#define CAN_MAILBOXHANDLEOFMEMORYSECTIONOBJECTS                       STD_ON
#define CAN_PLATFORMDLL_GENERATORVERSION                              STD_ON
#define CAN_SIZEOFACTIVESENDOBJECT                                    STD_ON
#define CAN_SIZEOFCANIFCHANNELID                                      STD_ON
#define CAN_SIZEOFCONTROLLERCONFIG                                    STD_ON
#define CAN_SIZEOFCONTROLLERDATA                                      STD_ON
#define CAN_SIZEOFFDMAILBOXMAPPING                                    STD_ON
#define CAN_SIZEOFINITBASICCAN                                        STD_ON
#define CAN_SIZEOFINITBASICCANINDEX                                   STD_ON
#define CAN_SIZEOFINITOBJECT                                          STD_ON
#define CAN_SIZEOFINITOBJECTBAUDRATE                                  STD_ON
#define CAN_SIZEOFINITOBJECTFD                                        STD_ON
#define CAN_SIZEOFINITOBJECTFDBRSCONFIG                               STD_ON
#define CAN_SIZEOFINITOBJECTSTARTINDEX                                STD_ON
#define CAN_SIZEOFMAILBOX                                             STD_ON
#define CAN_SIZEOFMEMORYSECTIONINFO                                   STD_ON
#define CAN_SIZEOFMEMORYSECTIONOBJECTS                                STD_ON
#define CAN_PCCONFIG                                                  STD_ON
#define CAN_ACTIVESENDOBJECTOFPCCONFIG                                STD_ON
#define CAN_BASEDLL_GENERATORVERSIONOFPCCONFIG                        STD_ON
#define CAN_CANIFCHANNELIDOFPCCONFIG                                  STD_ON
#define CAN_CONTROLLERCONFIGOFPCCONFIG                                STD_ON
#define CAN_CONTROLLERDATAOFPCCONFIG                                  STD_ON
#define CAN_FDMAILBOXMAPPINGOFPCCONFIG                                STD_ON
#define CAN_FINALMAGICNUMBEROFPCCONFIG                                STD_OFF  /**< Deactivateable: 'Can_PCConfig.FinalMagicNumber' Reason: 'the module configuration does not support flashing of data.' */
#define CAN_INITBASICCANINDEXOFPCCONFIG                               STD_ON
#define CAN_INITBASICCANOFPCCONFIG                                    STD_ON
#define CAN_INITDATAHASHCODEOFPCCONFIG                                STD_OFF  /**< Deactivateable: 'Can_PCConfig.InitDataHashCode' Reason: 'the module configuration does not support flashing of data.' */
#define CAN_INITOBJECTBAUDRATEOFPCCONFIG                              STD_ON
#define CAN_INITOBJECTFDOFPCCONFIG                                    STD_ON
#define CAN_INITOBJECTFDBRSCONFIGOFPCCONFIG                           STD_ON
#define CAN_INITOBJECTOFPCCONFIG                                      STD_ON
#define CAN_INITOBJECTSTARTINDEXOFPCCONFIG                            STD_ON
#define CAN_MAILBOXOFPCCONFIG                                         STD_ON
#define CAN_MEMORYSECTIONINFOOFPCCONFIG                               STD_ON
#define CAN_MEMORYSECTIONOBJECTSOFPCCONFIG                            STD_ON
#define CAN_PLATFORMDLL_GENERATORVERSIONOFPCCONFIG                    STD_ON
#define CAN_SIZEOFACTIVESENDOBJECTOFPCCONFIG                          STD_ON
#define CAN_SIZEOFCANIFCHANNELIDOFPCCONFIG                            STD_ON
#define CAN_SIZEOFCONTROLLERCONFIGOFPCCONFIG                          STD_ON
#define CAN_SIZEOFCONTROLLERDATAOFPCCONFIG                            STD_ON
#define CAN_SIZEOFFDMAILBOXMAPPINGOFPCCONFIG                          STD_ON
#define CAN_SIZEOFINITBASICCANINDEXOFPCCONFIG                         STD_ON
#define CAN_SIZEOFINITBASICCANOFPCCONFIG                              STD_ON
#define CAN_SIZEOFINITOBJECTBAUDRATEOFPCCONFIG                        STD_ON
#define CAN_SIZEOFINITOBJECTFDOFPCCONFIG                              STD_ON
#define CAN_SIZEOFINITOBJECTFDBRSCONFIGOFPCCONFIG                     STD_ON
#define CAN_SIZEOFINITOBJECTOFPCCONFIG                                STD_ON
#define CAN_SIZEOFINITOBJECTSTARTINDEXOFPCCONFIG                      STD_ON
#define CAN_SIZEOFMAILBOXOFPCCONFIG                                   STD_ON
#define CAN_SIZEOFMEMORYSECTIONINFOOFPCCONFIG                         STD_ON
#define CAN_SIZEOFMEMORYSECTIONOBJECTSOFPCCONFIG                      STD_ON
/** 
  \}
*/ 

/** 
  \defgroup  CanPCMinNumericValueDefines  Can Min Numeric Value Defines (PRE_COMPILE)
  \brief  These defines are used to implement against the minimum value in numerical based data.
  \{
*/ 
#define CAN_MIN_PDUOFACTIVESENDOBJECT                                 0u
#define CAN_MIN_STATEOFACTIVESENDOBJECT                               0u
#define CAN_MIN_BUSOFFCOUNTEROFCONTROLLERDATA                         0u
#define CAN_MIN_BUSOFFTRANSITIONREQUESTOFCONTROLLERDATA               0u
#define CAN_MIN_CANINTERRUPTCOUNTEROFCONTROLLERDATA                   0u
#define CAN_MIN_LASTINITOBJECTOFCONTROLLERDATA                        0u
#define CAN_MIN_LOGSTATUSOFCONTROLLERDATA                             0u
#define CAN_MIN_MODETRANSITIONREQUESTOFCONTROLLERDATA                 0u
#define CAN_MIN_RAMCHECKTRANSITIONREQUESTOFCONTROLLERDATA             0u
/** 
  \}
*/ 

/** 
  \defgroup  CanPCMaxNumericValueDefines  Can Max Numeric Value Defines (PRE_COMPILE)
  \brief  These defines are used to implement against the maximum value in numerical based data.
  \{
*/ 
#define CAN_MAX_PDUOFACTIVESENDOBJECT                                 255u
#define CAN_MAX_STATEOFACTIVESENDOBJECT                               65535u
#define CAN_MAX_BUSOFFCOUNTEROFCONTROLLERDATA                         255u
#define CAN_MAX_BUSOFFTRANSITIONREQUESTOFCONTROLLERDATA               255u
#define CAN_MAX_CANINTERRUPTCOUNTEROFCONTROLLERDATA                   255u
#define CAN_MAX_LASTINITOBJECTOFCONTROLLERDATA                        255u
#define CAN_MAX_LOGSTATUSOFCONTROLLERDATA                             255u
#define CAN_MAX_MODETRANSITIONREQUESTOFCONTROLLERDATA                 255u
#define CAN_MAX_RAMCHECKTRANSITIONREQUESTOFCONTROLLERDATA             255u
/** 
  \}
*/ 

/** 
  \defgroup  CanPCNoReferenceDefines  Can No Reference Defines (PRE_COMPILE)
  \brief  These defines are used to indicate unused indexes in data relations.
  \{
*/ 
#define CAN_NO_CANIFCHANNELID                                         255u
#define CAN_NO_CANCONTROLLERDEFAULTBAUDRATEIDXOFCONTROLLERCONFIG      255u
#define CAN_NO_CANCONTROLLERDEFAULTBAUDRATEOFCONTROLLERCONFIG         65535u
#define CAN_NO_MAILBOXRXBASICENDIDXOFCONTROLLERCONFIG                 255u
#define CAN_NO_MAILBOXRXBASICSTARTIDXOFCONTROLLERCONFIG               255u
#define CAN_NO_MAILBOXTXBASICENDIDXOFCONTROLLERCONFIG                 255u
#define CAN_NO_MAILBOXTXBASICSTARTIDXOFCONTROLLERCONFIG               255u
#define CAN_NO_MAILBOXUNUSEDENDIDXOFCONTROLLERCONFIG                  255u
#define CAN_NO_MAILBOXUNUSEDSTARTIDXOFCONTROLLERCONFIG                255u
#define CAN_NO_RXBASICHWSTARTOFCONTROLLERCONFIG                       255u
#define CAN_NO_RXBASICHWSTOPOFCONTROLLERCONFIG                        255u
#define CAN_NO_RXFULLHWSTARTOFCONTROLLERCONFIG                        255u
#define CAN_NO_RXFULLHWSTOPOFCONTROLLERCONFIG                         255u
#define CAN_NO_TXBASICHWSTARTOFCONTROLLERCONFIG                       255u
#define CAN_NO_TXBASICHWSTOPOFCONTROLLERCONFIG                        255u
#define CAN_NO_TXFULLHWSTARTOFCONTROLLERCONFIG                        255u
#define CAN_NO_TXFULLHWSTOPOFCONTROLLERCONFIG                         255u
#define CAN_NO_UNUSEDHWSTARTOFCONTROLLERCONFIG                        255u
#define CAN_NO_UNUSEDHWSTOPOFCONTROLLERCONFIG                         255u
/** 
  \}
*/ 

/** 
  \defgroup  CanPCEnumExistsDefines  Can Enum Exists Defines (PRE_COMPILE)
  \brief  These defines can be used to deactivate enumeration based code sequences if the enumeration value does not exist in the configuration data.
  \{
*/ 
#define CAN_EXISTS_NONE_INITOBJECTFDBRSCONFIG                         STD_OFF
#define CAN_EXISTS_FD_RXTX_INITOBJECTFDBRSCONFIG                      STD_ON
#define CAN_EXISTS_FD_RXONLY_INITOBJECTFDBRSCONFIG                    STD_OFF
#define CAN_EXISTS_RX_BASICCAN_TYPE_MAILBOXTYPEOFMAILBOX              STD_ON
#define CAN_EXISTS_RX_FULLCAN_TYPE_MAILBOXTYPEOFMAILBOX               STD_OFF
#define CAN_EXISTS_TX_BASICCAN_TYPE_MAILBOXTYPEOFMAILBOX              STD_ON
#define CAN_EXISTS_TX_FULLCAN_TYPE_MAILBOXTYPEOFMAILBOX               STD_OFF
#define CAN_EXISTS_UNUSED_CAN_TYPE_MAILBOXTYPEOFMAILBOX               STD_ON
#define CAN_EXISTS_TX_BASICCAN_MUX_TYPE_MAILBOXTYPEOFMAILBOX          STD_OFF
#define CAN_EXISTS_TX_BASICCAN_FIFO_TYPE_MAILBOXTYPEOFMAILBOX         STD_OFF
/** 
  \}
*/ 

/** 
  \defgroup  CanPCEnumDefines  Can Enum Defines (PRE_COMPILE)
  \brief  These defines are the enumeration values of enumeration based CONST and VAR data.
  \{
*/ 
#define CAN_FD_RXTX_INITOBJECTFDBRSCONFIG                             0x01u
#define CAN_RX_BASICCAN_TYPE_MAILBOXTYPEOFMAILBOX                     0x00u
#define CAN_TX_BASICCAN_TYPE_MAILBOXTYPEOFMAILBOX                     0x02u
#define CAN_UNUSED_CAN_TYPE_MAILBOXTYPEOFMAILBOX                      0x04u
/** 
  \}
*/ 

/** 
  \defgroup  CanPCIsReducedToDefineDefines  Can Is Reduced To Define Defines (PRE_COMPILE)
  \brief  If all values in a CONST array or an element in a CONST array of structs are equal, the define is STD_ON else STD_OFF.
  \{
*/ 
#define CAN_ISDEF_CANIFCHANNELID                                      STD_OFF
#define CAN_ISDEF_BASEADDRESSOFCONTROLLERCONFIG                       STD_OFF
#define CAN_ISDEF_CANCONTROLLERDEFAULTBAUDRATEIDXOFCONTROLLERCONFIG   STD_OFF
#define CAN_ISDEF_CANCONTROLLERDEFAULTBAUDRATEOFCONTROLLERCONFIG      STD_OFF
#define CAN_ISDEF_FDHWCHANNELINDIRECTIONOFCONTROLLERCONFIG            STD_OFF
#define CAN_ISDEF_FDMAILBOXMAXWORDLENGTHOFCONTROLLERCONFIG            STD_OFF
#define CAN_ISDEF_HASCANFDBAUDRATEOFCONTROLLERCONFIG                  STD_OFF
#define CAN_ISDEF_INTERRUPTMASK1OFCONTROLLERCONFIG                    STD_OFF
#define CAN_ISDEF_MAILBOXRXBASICENDIDXOFCONTROLLERCONFIG              STD_OFF
#define CAN_ISDEF_MAILBOXRXBASICLENGTHOFCONTROLLERCONFIG              STD_OFF
#define CAN_ISDEF_MAILBOXRXBASICSTARTIDXOFCONTROLLERCONFIG            STD_OFF
#define CAN_ISDEF_MAILBOXRXBASICUSEDOFCONTROLLERCONFIG                STD_OFF
#define CAN_ISDEF_MAILBOXTXBASICENDIDXOFCONTROLLERCONFIG              STD_OFF
#define CAN_ISDEF_MAILBOXTXBASICLENGTHOFCONTROLLERCONFIG              STD_OFF
#define CAN_ISDEF_MAILBOXTXBASICSTARTIDXOFCONTROLLERCONFIG            STD_OFF
#define CAN_ISDEF_MAILBOXTXBASICUSEDOFCONTROLLERCONFIG                STD_OFF
#define CAN_ISDEF_MAILBOXUNUSEDENDIDXOFCONTROLLERCONFIG               STD_OFF
#define CAN_ISDEF_MAILBOXUNUSEDLENGTHOFCONTROLLERCONFIG               STD_OFF
#define CAN_ISDEF_MAILBOXUNUSEDSTARTIDXOFCONTROLLERCONFIG             STD_OFF
#define CAN_ISDEF_MAILBOXUNUSEDUSEDOFCONTROLLERCONFIG                 STD_OFF
#define CAN_ISDEF_NUMBEROFFILTERSOFCONTROLLERCONFIG                   STD_OFF
#define CAN_ISDEF_NUMBEROFFULLCONFIGURABLEFILTERSOFCONTROLLERCONFIG   STD_OFF
#define CAN_ISDEF_NUMBEROFMAXMAILBOXESOFCONTROLLERCONFIG              STD_OFF
#define CAN_ISDEF_RFFNOFCONTROLLERCONFIG                              STD_OFF
#define CAN_ISDEF_RXBASICHWSTARTOFCONTROLLERCONFIG                    STD_OFF
#define CAN_ISDEF_RXBASICHWSTOPOFCONTROLLERCONFIG                     STD_OFF
#define CAN_ISDEF_RXFULLHWSTARTOFCONTROLLERCONFIG                     STD_OFF
#define CAN_ISDEF_RXFULLHWSTOPOFCONTROLLERCONFIG                      STD_OFF
#define CAN_ISDEF_TXBASICHWSTARTOFCONTROLLERCONFIG                    STD_OFF
#define CAN_ISDEF_TXBASICHWSTOPOFCONTROLLERCONFIG                     STD_OFF
#define CAN_ISDEF_TXFULLHWSTARTOFCONTROLLERCONFIG                     STD_OFF
#define CAN_ISDEF_TXFULLHWSTOPOFCONTROLLERCONFIG                      STD_OFF
#define CAN_ISDEF_UNUSEDHWSTARTOFCONTROLLERCONFIG                     STD_OFF
#define CAN_ISDEF_UNUSEDHWSTOPOFCONTROLLERCONFIG                      STD_OFF
#define CAN_ISDEF_FDMAILBOXMAPPING                                    STD_OFF
#define CAN_ISDEF_INITCODEOFINITBASICCAN                              STD_OFF
#define CAN_ISDEF_INITMASKOFINITBASICCAN                              STD_OFF
#define CAN_ISDEF_INITBASICCANINDEX                                   STD_OFF
#define CAN_ISDEF_CBTOFINITOBJECT                                     STD_OFF
#define CAN_ISDEF_CONTROL1OFINITOBJECT                                STD_OFF
#define CAN_ISDEF_INITOBJECTBAUDRATE                                  STD_OFF
#define CAN_ISDEF_FDCBTOFINITOBJECTFD                                 STD_OFF
#define CAN_ISDEF_FDCTRLOFINITOBJECTFD                                STD_OFF
#define CAN_ISDEF_INITOBJECTFDBRSCONFIG                               STD_OFF
#define CAN_ISDEF_INITOBJECTSTARTINDEX                                STD_OFF
#define CAN_ISDEF_ACTIVESENDOBJECTOFMAILBOX                           STD_OFF
#define CAN_ISDEF_CONTROLLERCONFIGIDXOFMAILBOX                        STD_OFF
#define CAN_ISDEF_FDPADDINGOFMAILBOX                                  STD_OFF
#define CAN_ISDEF_HWHANDLEOFMAILBOX                                   STD_OFF
#define CAN_ISDEF_IDVALUEOFMAILBOX                                    STD_OFF
#define CAN_ISDEF_MAILBOXSIZEOFMAILBOX                                STD_OFF
#define CAN_ISDEF_MAILBOXTYPEOFMAILBOX                                STD_OFF
#define CAN_ISDEF_MAXDATALENOFMAILBOX                                 STD_OFF
#define CAN_ISDEF_MEMORYSECTIONSINDEXOFMAILBOX                        STD_OFF
#define CAN_ISDEF_MEMORYSECTIONSTARTOFMEMORYSECTIONINFO               STD_OFF
#define CAN_ISDEF_MEMORYSTARTADDRESSOFMEMORYSECTIONINFO               STD_OFF
#define CAN_ISDEF_HWHANDLEOFMEMORYSECTIONOBJECTS                      STD_OFF
#define CAN_ISDEF_MAILBOXELEMENTOFMEMORYSECTIONOBJECTS                STD_OFF
#define CAN_ISDEF_MAILBOXHANDLEOFMEMORYSECTIONOBJECTS                 STD_OFF
#define CAN_ISDEF_ACTIVESENDOBJECTOFPCCONFIG                          STD_ON
#define CAN_ISDEF_CANIFCHANNELIDOFPCCONFIG                            STD_ON
#define CAN_ISDEF_CONTROLLERCONFIGOFPCCONFIG                          STD_ON
#define CAN_ISDEF_CONTROLLERDATAOFPCCONFIG                            STD_ON
#define CAN_ISDEF_FDMAILBOXMAPPINGOFPCCONFIG                          STD_ON
#define CAN_ISDEF_INITBASICCANINDEXOFPCCONFIG                         STD_ON
#define CAN_ISDEF_INITBASICCANOFPCCONFIG                              STD_ON
#define CAN_ISDEF_INITOBJECTBAUDRATEOFPCCONFIG                        STD_ON
#define CAN_ISDEF_INITOBJECTFDOFPCCONFIG                              STD_ON
#define CAN_ISDEF_INITOBJECTFDBRSCONFIGOFPCCONFIG                     STD_ON
#define CAN_ISDEF_INITOBJECTOFPCCONFIG                                STD_ON
#define CAN_ISDEF_INITOBJECTSTARTINDEXOFPCCONFIG                      STD_ON
#define CAN_ISDEF_MAILBOXOFPCCONFIG                                   STD_ON
#define CAN_ISDEF_MEMORYSECTIONINFOOFPCCONFIG                         STD_ON
#define CAN_ISDEF_MEMORYSECTIONOBJECTSOFPCCONFIG                      STD_ON
/** 
  \}
*/ 

/** 
  \defgroup  CanPCEqualsAlwaysToDefines  Can Equals Always To Defines (PRE_COMPILE)
  \brief  If all values in a CONST array or an element in a CONST array of structs are equal, the define contains the always equals value.
  \{
*/ 
#define CAN_EQ2_CANIFCHANNELID                                        
#define CAN_EQ2_BASEADDRESSOFCONTROLLERCONFIG                         
#define CAN_EQ2_CANCONTROLLERDEFAULTBAUDRATEIDXOFCONTROLLERCONFIG     
#define CAN_EQ2_CANCONTROLLERDEFAULTBAUDRATEOFCONTROLLERCONFIG        
#define CAN_EQ2_FDHWCHANNELINDIRECTIONOFCONTROLLERCONFIG              
#define CAN_EQ2_FDMAILBOXMAXWORDLENGTHOFCONTROLLERCONFIG              
#define CAN_EQ2_HASCANFDBAUDRATEOFCONTROLLERCONFIG                    
#define CAN_EQ2_INTERRUPTMASK1OFCONTROLLERCONFIG                      
#define CAN_EQ2_MAILBOXRXBASICENDIDXOFCONTROLLERCONFIG                
#define CAN_EQ2_MAILBOXRXBASICLENGTHOFCONTROLLERCONFIG                
#define CAN_EQ2_MAILBOXRXBASICSTARTIDXOFCONTROLLERCONFIG              
#define CAN_EQ2_MAILBOXRXBASICUSEDOFCONTROLLERCONFIG                  
#define CAN_EQ2_MAILBOXTXBASICENDIDXOFCONTROLLERCONFIG                
#define CAN_EQ2_MAILBOXTXBASICLENGTHOFCONTROLLERCONFIG                
#define CAN_EQ2_MAILBOXTXBASICSTARTIDXOFCONTROLLERCONFIG              
#define CAN_EQ2_MAILBOXTXBASICUSEDOFCONTROLLERCONFIG                  
#define CAN_EQ2_MAILBOXUNUSEDENDIDXOFCONTROLLERCONFIG                 
#define CAN_EQ2_MAILBOXUNUSEDLENGTHOFCONTROLLERCONFIG                 
#define CAN_EQ2_MAILBOXUNUSEDSTARTIDXOFCONTROLLERCONFIG               
#define CAN_EQ2_MAILBOXUNUSEDUSEDOFCONTROLLERCONFIG                   
#define CAN_EQ2_NUMBEROFFILTERSOFCONTROLLERCONFIG                     
#define CAN_EQ2_NUMBEROFFULLCONFIGURABLEFILTERSOFCONTROLLERCONFIG     
#define CAN_EQ2_NUMBEROFMAXMAILBOXESOFCONTROLLERCONFIG                
#define CAN_EQ2_RFFNOFCONTROLLERCONFIG                                
#define CAN_EQ2_RXBASICHWSTARTOFCONTROLLERCONFIG                      
#define CAN_EQ2_RXBASICHWSTOPOFCONTROLLERCONFIG                       
#define CAN_EQ2_RXFULLHWSTARTOFCONTROLLERCONFIG                       
#define CAN_EQ2_RXFULLHWSTOPOFCONTROLLERCONFIG                        
#define CAN_EQ2_TXBASICHWSTARTOFCONTROLLERCONFIG                      
#define CAN_EQ2_TXBASICHWSTOPOFCONTROLLERCONFIG                       
#define CAN_EQ2_TXFULLHWSTARTOFCONTROLLERCONFIG                       
#define CAN_EQ2_TXFULLHWSTOPOFCONTROLLERCONFIG                        
#define CAN_EQ2_UNUSEDHWSTARTOFCONTROLLERCONFIG                       
#define CAN_EQ2_UNUSEDHWSTOPOFCONTROLLERCONFIG                        
#define CAN_EQ2_FDMAILBOXMAPPING                                      
#define CAN_EQ2_INITCODEOFINITBASICCAN                                
#define CAN_EQ2_INITMASKOFINITBASICCAN                                
#define CAN_EQ2_INITBASICCANINDEX                                     
#define CAN_EQ2_CBTOFINITOBJECT                                       
#define CAN_EQ2_CONTROL1OFINITOBJECT                                  
#define CAN_EQ2_INITOBJECTBAUDRATE                                    
#define CAN_EQ2_FDCBTOFINITOBJECTFD                                   
#define CAN_EQ2_FDCTRLOFINITOBJECTFD                                  
#define CAN_EQ2_INITOBJECTFDBRSCONFIG                                 
#define CAN_EQ2_INITOBJECTSTARTINDEX                                  
#define CAN_EQ2_ACTIVESENDOBJECTOFMAILBOX                             
#define CAN_EQ2_CONTROLLERCONFIGIDXOFMAILBOX                          
#define CAN_EQ2_FDPADDINGOFMAILBOX                                    
#define CAN_EQ2_HWHANDLEOFMAILBOX                                     
#define CAN_EQ2_IDVALUEOFMAILBOX                                      
#define CAN_EQ2_MAILBOXSIZEOFMAILBOX                                  
#define CAN_EQ2_MAILBOXTYPEOFMAILBOX                                  
#define CAN_EQ2_MAXDATALENOFMAILBOX                                   
#define CAN_EQ2_MEMORYSECTIONSINDEXOFMAILBOX                          
#define CAN_EQ2_MEMORYSECTIONSTARTOFMEMORYSECTIONINFO                 
#define CAN_EQ2_MEMORYSTARTADDRESSOFMEMORYSECTIONINFO                 
#define CAN_EQ2_HWHANDLEOFMEMORYSECTIONOBJECTS                        
#define CAN_EQ2_MAILBOXELEMENTOFMEMORYSECTIONOBJECTS                  
#define CAN_EQ2_MAILBOXHANDLEOFMEMORYSECTIONOBJECTS                   
#define CAN_EQ2_ACTIVESENDOBJECTOFPCCONFIG                            Can_ActiveSendObject
#define CAN_EQ2_CANIFCHANNELIDOFPCCONFIG                              Can_CanIfChannelId
#define CAN_EQ2_CONTROLLERCONFIGOFPCCONFIG                            Can_ControllerConfig
#define CAN_EQ2_CONTROLLERDATAOFPCCONFIG                              Can_ControllerData
#define CAN_EQ2_FDMAILBOXMAPPINGOFPCCONFIG                            Can_FDMailboxMapping
#define CAN_EQ2_INITBASICCANINDEXOFPCCONFIG                           Can_InitBasicCanIndex
#define CAN_EQ2_INITBASICCANOFPCCONFIG                                Can_InitBasicCan
#define CAN_EQ2_INITOBJECTBAUDRATEOFPCCONFIG                          Can_InitObjectBaudrate
#define CAN_EQ2_INITOBJECTFDOFPCCONFIG                                Can_InitObjectFD
#define CAN_EQ2_INITOBJECTFDBRSCONFIGOFPCCONFIG                       Can_InitObjectFdBrsConfig
#define CAN_EQ2_INITOBJECTOFPCCONFIG                                  Can_InitObject
#define CAN_EQ2_INITOBJECTSTARTINDEXOFPCCONFIG                        Can_InitObjectStartIndex
#define CAN_EQ2_MAILBOXOFPCCONFIG                                     Can_Mailbox
#define CAN_EQ2_MEMORYSECTIONINFOOFPCCONFIG                           Can_MemorySectionInfo
#define CAN_EQ2_MEMORYSECTIONOBJECTSOFPCCONFIG                        Can_MemorySectionObjects
/** 
  \}
*/ 

/** 
  \defgroup  CanPCSymbolicInitializationPointers  Can Symbolic Initialization Pointers (PRE_COMPILE)
  \brief  Symbolic initialization pointers to be used in the call of a preinit or init function.
  \{
*/ 
#define Can_Config_Ptr                                                NULL_PTR  /**< symbolic identifier which shall be used to initialize 'Can' */
/** 
  \}
*/ 

/** 
  \defgroup  CanPCInitializationSymbols  Can Initialization Symbols (PRE_COMPILE)
  \brief  Symbolic initialization pointers which may be used in the call of a preinit or init function. Please note, that the defined value can be a 'NULL_PTR' and the address operator is not usable.
  \{
*/ 
#define Can_Config                                                    NULL_PTR  /**< symbolic identifier which could be used to initialize 'Can */
/** 
  \}
*/ 

/** 
  \defgroup  CanPCGeneral  Can General (PRE_COMPILE)
  \brief  General constant defines not associated with a group of defines.
  \{
*/ 
#define CAN_CHECK_INIT_POINTER                                        STD_OFF  /**< STD_ON if the init pointer shall not be used as NULL_PTR and a check shall validate this. */
#define CAN_FINAL_MAGIC_NUMBER                                        0x501Eu  /**< the precompile constant to validate the size of the initialization structure at initialization time of Can */
#define CAN_INDIVIDUAL_POSTBUILD                                      STD_OFF  /**< the precompile constant to check, that the module is individual postbuildable. The module 'Can' is not configured to be postbuild capable. */
#define CAN_INIT_DATA                                                 CAN_CONST  /**< CompilerMemClassDefine for the initialization data. */
#define CAN_INIT_DATA_HASH_CODE                                       -1893185136  /**< the precompile constant to validate the initialization structure at initialization time of Can with a hashcode. The seed value is '0x501Eu' */
#define CAN_USE_ECUM_BSW_ERROR_HOOK                                   STD_OFF  /**< STD_ON if the EcuM_BswErrorHook shall be called in the ConfigPtr check. */
#define CAN_USE_INIT_POINTER                                          STD_OFF  /**< STD_ON if the init pointer Can shall be used. */
/** 
  \}
*/ 


/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/** 
  \defgroup  CanLTDataSwitches  Can Data Switches  (LINK)
  \brief  These defines are used to deactivate data and their processing.
  \{
*/ 
#define CAN_LTCONFIG                                                  STD_OFF  /**< Deactivateable: 'Can_LTConfig' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
/** 
  \}
*/ 


/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/** 
  \defgroup  CanPBDataSwitches  Can Data Switches  (POST_BUILD)
  \brief  These defines are used to deactivate data and their processing.
  \{
*/ 
#define CAN_PBCONFIG                                                  STD_OFF  /**< Deactivateable: 'Can_PBConfig' Reason: 'the module configuration is VARIANT_PRE_COMPILE.' */
#define CAN_LTCONFIGIDXOFPBCONFIG                                     STD_OFF  /**< Deactivateable: 'Can_PBConfig.LTConfigIdx' Reason: 'the module configuration is VARIANT_PRE_COMPILE.' */
#define CAN_PCCONFIGIDXOFPBCONFIG                                     STD_OFF  /**< Deactivateable: 'Can_PBConfig.PCConfigIdx' Reason: 'the module configuration is VARIANT_PRE_COMPILE.' */
/** 
  \}
*/ 



/**********************************************************************************************************************
  GLOBAL FUNCTION MACROS
**********************************************************************************************************************/
/** 
  \defgroup  DataAccessMacros  Data Access Macros
  \brief  generated data access macros to abstract the generated data from the code to read and write CONST or VAR data.
  \{
*/ 
  /* PRQA S 3453 Macros_3453 */  /* MD_MSR_FctLikeMacro */
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL FUNCTION MACROS
**********************************************************************************************************************/
/** 
  \defgroup  CanPCGetConstantDuplicatedRootDataMacros  Can Get Constant Duplicated Root Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated by constance root data elements.
  \{
*/ 
#define Can_GetActiveSendObjectOfPCConfig()                           Can_ActiveSendObject  /**< the pointer to Can_ActiveSendObject */
#define Can_GetBaseDll_GeneratorVersionOfPCConfig()                   0x0103u
#define Can_GetCanIfChannelIdOfPCConfig()                             Can_CanIfChannelId  /**< the pointer to Can_CanIfChannelId */
#define Can_GetControllerConfigOfPCConfig()                           Can_ControllerConfig  /**< the pointer to Can_ControllerConfig */
#define Can_GetControllerDataOfPCConfig()                             Can_ControllerData  /**< the pointer to Can_ControllerData */
#define Can_GetFDMailboxMappingOfPCConfig()                           Can_FDMailboxMapping  /**< the pointer to Can_FDMailboxMapping */
#define Can_GetInitBasicCanIndexOfPCConfig()                          Can_InitBasicCanIndex  /**< the pointer to Can_InitBasicCanIndex */
#define Can_GetInitBasicCanOfPCConfig()                               Can_InitBasicCan  /**< the pointer to Can_InitBasicCan */
#define Can_GetInitObjectBaudrateOfPCConfig()                         Can_InitObjectBaudrate  /**< the pointer to Can_InitObjectBaudrate */
#define Can_GetInitObjectFDOfPCConfig()                               Can_InitObjectFD  /**< the pointer to Can_InitObjectFD */
#define Can_GetInitObjectFdBrsConfigOfPCConfig()                      Can_InitObjectFdBrsConfig  /**< the pointer to Can_InitObjectFdBrsConfig */
#define Can_GetInitObjectOfPCConfig()                                 Can_InitObject  /**< the pointer to Can_InitObject */
#define Can_GetInitObjectStartIndexOfPCConfig()                       Can_InitObjectStartIndex  /**< the pointer to Can_InitObjectStartIndex */
#define Can_GetMailboxOfPCConfig()                                    Can_Mailbox  /**< the pointer to Can_Mailbox */
#define Can_GetMemorySectionInfoOfPCConfig()                          Can_MemorySectionInfo  /**< the pointer to Can_MemorySectionInfo */
#define Can_GetMemorySectionObjectsOfPCConfig()                       Can_MemorySectionObjects  /**< the pointer to Can_MemorySectionObjects */
#define Can_GetPlatformDll_GeneratorVersionOfPCConfig()               0x0101u
#define Can_GetSizeOfActiveSendObjectOfPCConfig()                     1u  /**< the number of accomplishable value elements in Can_ActiveSendObject */
#define Can_GetSizeOfCanIfChannelIdOfPCConfig()                       1u  /**< the number of accomplishable value elements in Can_CanIfChannelId */
#define Can_GetSizeOfControllerConfigOfPCConfig()                     1u  /**< the number of accomplishable value elements in Can_ControllerConfig */
#define Can_GetSizeOfFDMailboxMappingOfPCConfig()                     5u  /**< the number of accomplishable value elements in Can_FDMailboxMapping */
#define Can_GetSizeOfInitBasicCanIndexOfPCConfig()                    1u  /**< the number of accomplishable value elements in Can_InitBasicCanIndex */
#define Can_GetSizeOfInitBasicCanOfPCConfig()                         4u  /**< the number of accomplishable value elements in Can_InitBasicCan */
#define Can_GetSizeOfInitObjectBaudrateOfPCConfig()                   1u  /**< the number of accomplishable value elements in Can_InitObjectBaudrate */
#define Can_GetSizeOfInitObjectFDOfPCConfig()                         1u  /**< the number of accomplishable value elements in Can_InitObjectFD */
#define Can_GetSizeOfInitObjectFdBrsConfigOfPCConfig()                1u  /**< the number of accomplishable value elements in Can_InitObjectFdBrsConfig */
#define Can_GetSizeOfInitObjectOfPCConfig()                           1u  /**< the number of accomplishable value elements in Can_InitObject */
#define Can_GetSizeOfInitObjectStartIndexOfPCConfig()                 2u  /**< the number of accomplishable value elements in Can_InitObjectStartIndex */
#define Can_GetSizeOfMailboxOfPCConfig()                              4u  /**< the number of accomplishable value elements in Can_Mailbox */
#define Can_GetSizeOfMemorySectionInfoOfPCConfig()                    1u  /**< the number of accomplishable value elements in Can_MemorySectionInfo */
#define Can_GetSizeOfMemorySectionObjectsOfPCConfig()                 7u  /**< the number of accomplishable value elements in Can_MemorySectionObjects */
/** 
  \}
*/ 

/** 
  \defgroup  CanPCGetDuplicatedRootDataMacros  Can Get Duplicated Root Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated root data elements.
  \{
*/ 
#define Can_GetSizeOfControllerDataOfPCConfig()                       Can_GetSizeOfControllerConfigOfPCConfig()  /**< the number of accomplishable value elements in Can_ControllerData */
/** 
  \}
*/ 

/** 
  \defgroup  CanPCGetDataMacros  Can Get Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read CONST and VAR data.
  \{
*/ 
#define Can_GetPduOfActiveSendObject(Index)                           (Can_GetActiveSendObjectOfPCConfig()[(Index)].PduOfActiveSendObject)
#define Can_GetStateOfActiveSendObject(Index)                         (Can_GetActiveSendObjectOfPCConfig()[(Index)].StateOfActiveSendObject)
#define Can_GetCanIfChannelId(Index)                                  (Can_GetCanIfChannelIdOfPCConfig()[(Index)])
#define Can_GetBaseAddressOfControllerConfig(Index)                   (Can_GetControllerConfigOfPCConfig()[(Index)].BaseAddressOfControllerConfig)
#define Can_GetCanControllerDefaultBaudrateIdxOfControllerConfig(Index) (Can_GetControllerConfigOfPCConfig()[(Index)].CanControllerDefaultBaudrateIdxOfControllerConfig)
#define Can_GetCanControllerDefaultBaudrateOfControllerConfig(Index)  (Can_GetControllerConfigOfPCConfig()[(Index)].CanControllerDefaultBaudrateOfControllerConfig)
#define Can_GetFDHwChannelIndirectionOfControllerConfig(Index)        (Can_GetControllerConfigOfPCConfig()[(Index)].FDHwChannelIndirectionOfControllerConfig)
#define Can_GetFDMailboxMaxWordLengthOfControllerConfig(Index)        (Can_GetControllerConfigOfPCConfig()[(Index)].FDMailboxMaxWordLengthOfControllerConfig)
#define Can_IsHasCANFDBaudrateOfControllerConfig(Index)               ((Can_GetControllerConfigOfPCConfig()[(Index)].HasCANFDBaudrateOfControllerConfig) != FALSE)
#define Can_GetInterruptMask1OfControllerConfig(Index)                (Can_GetControllerConfigOfPCConfig()[(Index)].InterruptMask1OfControllerConfig)
#define Can_GetMailboxRxBasicEndIdxOfControllerConfig(Index)          (Can_GetControllerConfigOfPCConfig()[(Index)].MailboxRxBasicEndIdxOfControllerConfig)
#define Can_GetMailboxRxBasicLengthOfControllerConfig(Index)          (Can_GetControllerConfigOfPCConfig()[(Index)].MailboxRxBasicLengthOfControllerConfig)
#define Can_GetMailboxRxBasicStartIdxOfControllerConfig(Index)        (Can_GetControllerConfigOfPCConfig()[(Index)].MailboxRxBasicStartIdxOfControllerConfig)
#define Can_GetMailboxTxBasicEndIdxOfControllerConfig(Index)          (Can_GetControllerConfigOfPCConfig()[(Index)].MailboxTxBasicEndIdxOfControllerConfig)
#define Can_GetMailboxTxBasicLengthOfControllerConfig(Index)          (Can_GetControllerConfigOfPCConfig()[(Index)].MailboxTxBasicLengthOfControllerConfig)
#define Can_GetMailboxTxBasicStartIdxOfControllerConfig(Index)        (Can_GetControllerConfigOfPCConfig()[(Index)].MailboxTxBasicStartIdxOfControllerConfig)
#define Can_GetMailboxUnusedEndIdxOfControllerConfig(Index)           (Can_GetControllerConfigOfPCConfig()[(Index)].MailboxUnusedEndIdxOfControllerConfig)
#define Can_GetMailboxUnusedLengthOfControllerConfig(Index)           (Can_GetControllerConfigOfPCConfig()[(Index)].MailboxUnusedLengthOfControllerConfig)
#define Can_GetMailboxUnusedStartIdxOfControllerConfig(Index)         (Can_GetControllerConfigOfPCConfig()[(Index)].MailboxUnusedStartIdxOfControllerConfig)
#define Can_GetNumberOfFiltersOfControllerConfig(Index)               (Can_GetControllerConfigOfPCConfig()[(Index)].NumberOfFiltersOfControllerConfig)
#define Can_GetNumberOfFullConfigurableFiltersOfControllerConfig(Index) (Can_GetControllerConfigOfPCConfig()[(Index)].NumberOfFullConfigurableFiltersOfControllerConfig)
#define Can_GetNumberOfMaxMailboxesOfControllerConfig(Index)          (Can_GetControllerConfigOfPCConfig()[(Index)].NumberOfMaxMailboxesOfControllerConfig)
#define Can_GetRFFNOfControllerConfig(Index)                          (Can_GetControllerConfigOfPCConfig()[(Index)].RFFNOfControllerConfig)
#define Can_GetRxBasicHwStartOfControllerConfig(Index)                (Can_GetControllerConfigOfPCConfig()[(Index)].RxBasicHwStartOfControllerConfig)
#define Can_GetRxBasicHwStopOfControllerConfig(Index)                 (Can_GetControllerConfigOfPCConfig()[(Index)].RxBasicHwStopOfControllerConfig)
#define Can_GetRxFullHwStartOfControllerConfig(Index)                 (Can_GetControllerConfigOfPCConfig()[(Index)].RxFullHwStartOfControllerConfig)
#define Can_GetRxFullHwStopOfControllerConfig(Index)                  (Can_GetControllerConfigOfPCConfig()[(Index)].RxFullHwStopOfControllerConfig)
#define Can_GetTxBasicHwStartOfControllerConfig(Index)                (Can_GetControllerConfigOfPCConfig()[(Index)].TxBasicHwStartOfControllerConfig)
#define Can_GetTxBasicHwStopOfControllerConfig(Index)                 (Can_GetControllerConfigOfPCConfig()[(Index)].TxBasicHwStopOfControllerConfig)
#define Can_GetTxFullHwStartOfControllerConfig(Index)                 (Can_GetControllerConfigOfPCConfig()[(Index)].TxFullHwStartOfControllerConfig)
#define Can_GetTxFullHwStopOfControllerConfig(Index)                  (Can_GetControllerConfigOfPCConfig()[(Index)].TxFullHwStopOfControllerConfig)
#define Can_GetUnusedHwStartOfControllerConfig(Index)                 (Can_GetControllerConfigOfPCConfig()[(Index)].UnusedHwStartOfControllerConfig)
#define Can_GetUnusedHwStopOfControllerConfig(Index)                  (Can_GetControllerConfigOfPCConfig()[(Index)].UnusedHwStopOfControllerConfig)
#define Can_GetBusOffCounterOfControllerData(Index)                   (Can_GetControllerDataOfPCConfig()[(Index)].BusOffCounterOfControllerData)
#define Can_GetBusOffTransitionRequestOfControllerData(Index)         (Can_GetControllerDataOfPCConfig()[(Index)].BusOffTransitionRequestOfControllerData)
#define Can_GetCanInterruptCounterOfControllerData(Index)             (Can_GetControllerDataOfPCConfig()[(Index)].CanInterruptCounterOfControllerData)
#define Can_GetCanInterruptOldStatusOfControllerData(Index)           (Can_GetControllerDataOfPCConfig()[(Index)].CanInterruptOldStatusOfControllerData)
#define Can_IsIsBusOffOfControllerData(Index)                         ((Can_GetControllerDataOfPCConfig()[(Index)].IsBusOffOfControllerData) != FALSE)
#define Can_GetLastInitObjectOfControllerData(Index)                  (Can_GetControllerDataOfPCConfig()[(Index)].LastInitObjectOfControllerData)
#define Can_GetLogStatusOfControllerData(Index)                       (Can_GetControllerDataOfPCConfig()[(Index)].LogStatusOfControllerData)
#define Can_GetLoopTimeoutOfControllerData(Index)                     (Can_GetControllerDataOfPCConfig()[(Index)].LoopTimeoutOfControllerData)
#define Can_GetModeTransitionRequestOfControllerData(Index)           (Can_GetControllerDataOfPCConfig()[(Index)].ModeTransitionRequestOfControllerData)
#define Can_GetRamCheckTransitionRequestOfControllerData(Index)       (Can_GetControllerDataOfPCConfig()[(Index)].RamCheckTransitionRequestOfControllerData)
#define Can_GetRxMsgBufferOfControllerData(Index)                     (Can_GetControllerDataOfPCConfig()[(Index)].RxMsgBufferOfControllerData)
#define Can_IsStartModeRequestedOfControllerData(Index)               ((Can_GetControllerDataOfPCConfig()[(Index)].StartModeRequestedOfControllerData) != FALSE)
#define Can_GetFDMailboxMapping(Index)                                (Can_GetFDMailboxMappingOfPCConfig()[(Index)])
#define Can_GetInitCodeOfInitBasicCan(Index)                          (Can_GetInitBasicCanOfPCConfig()[(Index)].InitCodeOfInitBasicCan)
#define Can_GetInitMaskOfInitBasicCan(Index)                          (Can_GetInitBasicCanOfPCConfig()[(Index)].InitMaskOfInitBasicCan)
#define Can_GetInitBasicCanIndex(Index)                               (Can_GetInitBasicCanIndexOfPCConfig()[(Index)])
#define Can_GetCBTOfInitObject(Index)                                 (Can_GetInitObjectOfPCConfig()[(Index)].CBTOfInitObject)
#define Can_GetControl1OfInitObject(Index)                            (Can_GetInitObjectOfPCConfig()[(Index)].Control1OfInitObject)
#define Can_GetInitObjectBaudrate(Index)                              (Can_GetInitObjectBaudrateOfPCConfig()[(Index)])
#define Can_GetFDCBTOfInitObjectFD(Index)                             (Can_GetInitObjectFDOfPCConfig()[(Index)].FDCBTOfInitObjectFD)
#define Can_GetFDCTRLOfInitObjectFD(Index)                            (Can_GetInitObjectFDOfPCConfig()[(Index)].FDCTRLOfInitObjectFD)
#define Can_GetInitObjectFdBrsConfig(Index)                           (Can_GetInitObjectFdBrsConfigOfPCConfig()[(Index)])
#define Can_GetInitObjectStartIndex(Index)                            (Can_GetInitObjectStartIndexOfPCConfig()[(Index)])
#define Can_GetActiveSendObjectOfMailbox(Index)                       (Can_GetMailboxOfPCConfig()[(Index)].ActiveSendObjectOfMailbox)
#define Can_GetControllerConfigIdxOfMailbox(Index)                    (Can_GetMailboxOfPCConfig()[(Index)].ControllerConfigIdxOfMailbox)
#define Can_GetFdPaddingOfMailbox(Index)                              (Can_GetMailboxOfPCConfig()[(Index)].FdPaddingOfMailbox)
#define Can_GetHwHandleOfMailbox(Index)                               (Can_GetMailboxOfPCConfig()[(Index)].HwHandleOfMailbox)
#define Can_GetIDValueOfMailbox(Index)                                (Can_GetMailboxOfPCConfig()[(Index)].IDValueOfMailbox)
#define Can_GetMailboxSizeOfMailbox(Index)                            (Can_GetMailboxOfPCConfig()[(Index)].MailboxSizeOfMailbox)
#define Can_GetMailboxTypeOfMailbox(Index)                            (Can_GetMailboxOfPCConfig()[(Index)].MailboxTypeOfMailbox)
#define Can_GetMaxDataLenOfMailbox(Index)                             (Can_GetMailboxOfPCConfig()[(Index)].MaxDataLenOfMailbox)
#define Can_GetMemorySectionsIndexOfMailbox(Index)                    (Can_GetMailboxOfPCConfig()[(Index)].MemorySectionsIndexOfMailbox)
#define Can_GetMemorySectionStartOfMemorySectionInfo(Index)           (Can_GetMemorySectionInfoOfPCConfig()[(Index)].MemorySectionStartOfMemorySectionInfo)
#define Can_GetMemoryStartAddressOfMemorySectionInfo(Index)           (Can_GetMemorySectionInfoOfPCConfig()[(Index)].MemoryStartAddressOfMemorySectionInfo)
#define Can_GetHwHandleOfMemorySectionObjects(Index)                  (Can_GetMemorySectionObjectsOfPCConfig()[(Index)].HwHandleOfMemorySectionObjects)
#define Can_GetMailboxElementOfMemorySectionObjects(Index)            (Can_GetMemorySectionObjectsOfPCConfig()[(Index)].MailboxElementOfMemorySectionObjects)
#define Can_GetMailboxHandleOfMemorySectionObjects(Index)             (Can_GetMemorySectionObjectsOfPCConfig()[(Index)].MailboxHandleOfMemorySectionObjects)
/** 
  \}
*/ 

/** 
  \defgroup  CanPCGetDeduplicatedDataMacros  Can Get Deduplicated Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated data elements.
  \{
*/ 
#define Can_GetBaseDll_GeneratorVersion()                             Can_GetBaseDll_GeneratorVersionOfPCConfig()
#define Can_IsMailboxRxBasicUsedOfControllerConfig(Index)             (((boolean)(Can_GetMailboxRxBasicLengthOfControllerConfig(Index) != 0u)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to Can_Mailbox */
#define Can_IsMailboxTxBasicUsedOfControllerConfig(Index)             (((boolean)(Can_GetMailboxTxBasicLengthOfControllerConfig(Index) != 0u)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to Can_Mailbox */
#define Can_IsMailboxUnusedUsedOfControllerConfig(Index)              (((boolean)(Can_GetMailboxUnusedLengthOfControllerConfig(Index) != 0u)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to Can_Mailbox */
#define Can_GetPlatformDll_GeneratorVersion()                         Can_GetPlatformDll_GeneratorVersionOfPCConfig()
#define Can_GetSizeOfActiveSendObject()                               Can_GetSizeOfActiveSendObjectOfPCConfig()
#define Can_GetSizeOfCanIfChannelId()                                 Can_GetSizeOfCanIfChannelIdOfPCConfig()
#define Can_GetSizeOfControllerConfig()                               Can_GetSizeOfControllerConfigOfPCConfig()
#define Can_GetSizeOfControllerData()                                 Can_GetSizeOfControllerDataOfPCConfig()
#define Can_GetSizeOfFDMailboxMapping()                               Can_GetSizeOfFDMailboxMappingOfPCConfig()
#define Can_GetSizeOfInitBasicCan()                                   Can_GetSizeOfInitBasicCanOfPCConfig()
#define Can_GetSizeOfInitBasicCanIndex()                              Can_GetSizeOfInitBasicCanIndexOfPCConfig()
#define Can_GetSizeOfInitObject()                                     Can_GetSizeOfInitObjectOfPCConfig()
#define Can_GetSizeOfInitObjectBaudrate()                             Can_GetSizeOfInitObjectBaudrateOfPCConfig()
#define Can_GetSizeOfInitObjectFD()                                   Can_GetSizeOfInitObjectFDOfPCConfig()
#define Can_GetSizeOfInitObjectFdBrsConfig()                          Can_GetSizeOfInitObjectFdBrsConfigOfPCConfig()
#define Can_GetSizeOfInitObjectStartIndex()                           Can_GetSizeOfInitObjectStartIndexOfPCConfig()
#define Can_GetSizeOfMailbox()                                        Can_GetSizeOfMailboxOfPCConfig()
#define Can_GetSizeOfMemorySectionInfo()                              Can_GetSizeOfMemorySectionInfoOfPCConfig()
#define Can_GetSizeOfMemorySectionObjects()                           Can_GetSizeOfMemorySectionObjectsOfPCConfig()
/** 
  \}
*/ 

/** 
  \defgroup  CanPCSetDataMacros  Can Set Data Macros (PRE_COMPILE)
  \brief  These macros can be used to write data.
  \{
*/ 
#define Can_SetPduOfActiveSendObject(Index, Value)                    Can_GetActiveSendObjectOfPCConfig()[(Index)].PduOfActiveSendObject = (Value)
#define Can_SetStateOfActiveSendObject(Index, Value)                  Can_GetActiveSendObjectOfPCConfig()[(Index)].StateOfActiveSendObject = (Value)
#define Can_SetBusOffCounterOfControllerData(Index, Value)            Can_GetControllerDataOfPCConfig()[(Index)].BusOffCounterOfControllerData = (Value)
#define Can_SetBusOffTransitionRequestOfControllerData(Index, Value)  Can_GetControllerDataOfPCConfig()[(Index)].BusOffTransitionRequestOfControllerData = (Value)
#define Can_SetCanInterruptCounterOfControllerData(Index, Value)      Can_GetControllerDataOfPCConfig()[(Index)].CanInterruptCounterOfControllerData = (Value)
#define Can_SetCanInterruptOldStatusOfControllerData(Index, Value)    Can_GetControllerDataOfPCConfig()[(Index)].CanInterruptOldStatusOfControllerData = (Value)
#define Can_SetIsBusOffOfControllerData(Index, Value)                 Can_GetControllerDataOfPCConfig()[(Index)].IsBusOffOfControllerData = (Value)
#define Can_SetLastInitObjectOfControllerData(Index, Value)           Can_GetControllerDataOfPCConfig()[(Index)].LastInitObjectOfControllerData = (Value)
#define Can_SetLogStatusOfControllerData(Index, Value)                Can_GetControllerDataOfPCConfig()[(Index)].LogStatusOfControllerData = (Value)
#define Can_SetLoopTimeoutOfControllerData(Index, Value)              Can_GetControllerDataOfPCConfig()[(Index)].LoopTimeoutOfControllerData = (Value)
#define Can_SetModeTransitionRequestOfControllerData(Index, Value)    Can_GetControllerDataOfPCConfig()[(Index)].ModeTransitionRequestOfControllerData = (Value)
#define Can_SetRamCheckTransitionRequestOfControllerData(Index, Value) Can_GetControllerDataOfPCConfig()[(Index)].RamCheckTransitionRequestOfControllerData = (Value)
#define Can_SetRxMsgBufferOfControllerData(Index, Value)              Can_GetControllerDataOfPCConfig()[(Index)].RxMsgBufferOfControllerData = (Value)
#define Can_SetStartModeRequestedOfControllerData(Index, Value)       Can_GetControllerDataOfPCConfig()[(Index)].StartModeRequestedOfControllerData = (Value)
/** 
  \}
*/ 

/** 
  \defgroup  CanPCHasMacros  Can Has Macros (PRE_COMPILE)
  \brief  These macros can be used to detect at runtime a deactivated piece of information. TRUE in the CONFIGURATION_VARIANT PRE-COMPILE, TRUE or FALSE in the CONFIGURATION_VARIANT POST-BUILD.
  \{
*/ 
#define Can_HasActiveSendObject()                                     (TRUE != FALSE)
#define Can_HasPduOfActiveSendObject()                                (TRUE != FALSE)
#define Can_HasStateOfActiveSendObject()                              (TRUE != FALSE)
#define Can_HasBaseDll_GeneratorVersion()                             (TRUE != FALSE)
#define Can_HasCanIfChannelId()                                       (TRUE != FALSE)
#define Can_HasControllerConfig()                                     (TRUE != FALSE)
#define Can_HasBaseAddressOfControllerConfig()                        (TRUE != FALSE)
#define Can_HasCanControllerDefaultBaudrateIdxOfControllerConfig()    (TRUE != FALSE)
#define Can_HasCanControllerDefaultBaudrateOfControllerConfig()       (TRUE != FALSE)
#define Can_HasFDHwChannelIndirectionOfControllerConfig()             (TRUE != FALSE)
#define Can_HasFDMailboxMaxWordLengthOfControllerConfig()             (TRUE != FALSE)
#define Can_HasHasCANFDBaudrateOfControllerConfig()                   (TRUE != FALSE)
#define Can_HasInterruptMask1OfControllerConfig()                     (TRUE != FALSE)
#define Can_HasMailboxRxBasicEndIdxOfControllerConfig()               (TRUE != FALSE)
#define Can_HasMailboxRxBasicLengthOfControllerConfig()               (TRUE != FALSE)
#define Can_HasMailboxRxBasicStartIdxOfControllerConfig()             (TRUE != FALSE)
#define Can_HasMailboxRxBasicUsedOfControllerConfig()                 (TRUE != FALSE)
#define Can_HasMailboxTxBasicEndIdxOfControllerConfig()               (TRUE != FALSE)
#define Can_HasMailboxTxBasicLengthOfControllerConfig()               (TRUE != FALSE)
#define Can_HasMailboxTxBasicStartIdxOfControllerConfig()             (TRUE != FALSE)
#define Can_HasMailboxTxBasicUsedOfControllerConfig()                 (TRUE != FALSE)
#define Can_HasMailboxUnusedEndIdxOfControllerConfig()                (TRUE != FALSE)
#define Can_HasMailboxUnusedLengthOfControllerConfig()                (TRUE != FALSE)
#define Can_HasMailboxUnusedStartIdxOfControllerConfig()              (TRUE != FALSE)
#define Can_HasMailboxUnusedUsedOfControllerConfig()                  (TRUE != FALSE)
#define Can_HasNumberOfFiltersOfControllerConfig()                    (TRUE != FALSE)
#define Can_HasNumberOfFullConfigurableFiltersOfControllerConfig()    (TRUE != FALSE)
#define Can_HasNumberOfMaxMailboxesOfControllerConfig()               (TRUE != FALSE)
#define Can_HasRFFNOfControllerConfig()                               (TRUE != FALSE)
#define Can_HasRxBasicHwStartOfControllerConfig()                     (TRUE != FALSE)
#define Can_HasRxBasicHwStopOfControllerConfig()                      (TRUE != FALSE)
#define Can_HasRxFullHwStartOfControllerConfig()                      (TRUE != FALSE)
#define Can_HasRxFullHwStopOfControllerConfig()                       (TRUE != FALSE)
#define Can_HasTxBasicHwStartOfControllerConfig()                     (TRUE != FALSE)
#define Can_HasTxBasicHwStopOfControllerConfig()                      (TRUE != FALSE)
#define Can_HasTxFullHwStartOfControllerConfig()                      (TRUE != FALSE)
#define Can_HasTxFullHwStopOfControllerConfig()                       (TRUE != FALSE)
#define Can_HasUnusedHwStartOfControllerConfig()                      (TRUE != FALSE)
#define Can_HasUnusedHwStopOfControllerConfig()                       (TRUE != FALSE)
#define Can_HasControllerData()                                       (TRUE != FALSE)
#define Can_HasBusOffCounterOfControllerData()                        (TRUE != FALSE)
#define Can_HasBusOffTransitionRequestOfControllerData()              (TRUE != FALSE)
#define Can_HasCanInterruptCounterOfControllerData()                  (TRUE != FALSE)
#define Can_HasCanInterruptOldStatusOfControllerData()                (TRUE != FALSE)
#define Can_HasIsBusOffOfControllerData()                             (TRUE != FALSE)
#define Can_HasLastInitObjectOfControllerData()                       (TRUE != FALSE)
#define Can_HasLogStatusOfControllerData()                            (TRUE != FALSE)
#define Can_HasLoopTimeoutOfControllerData()                          (TRUE != FALSE)
#define Can_HasModeTransitionRequestOfControllerData()                (TRUE != FALSE)
#define Can_HasRamCheckTransitionRequestOfControllerData()            (TRUE != FALSE)
#define Can_HasRxMsgBufferOfControllerData()                          (TRUE != FALSE)
#define Can_HasStartModeRequestedOfControllerData()                   (TRUE != FALSE)
#define Can_HasFDMailboxMapping()                                     (TRUE != FALSE)
#define Can_HasInitBasicCan()                                         (TRUE != FALSE)
#define Can_HasInitCodeOfInitBasicCan()                               (TRUE != FALSE)
#define Can_HasInitMaskOfInitBasicCan()                               (TRUE != FALSE)
#define Can_HasInitBasicCanIndex()                                    (TRUE != FALSE)
#define Can_HasInitObject()                                           (TRUE != FALSE)
#define Can_HasCBTOfInitObject()                                      (TRUE != FALSE)
#define Can_HasControl1OfInitObject()                                 (TRUE != FALSE)
#define Can_HasInitObjectBaudrate()                                   (TRUE != FALSE)
#define Can_HasInitObjectFD()                                         (TRUE != FALSE)
#define Can_HasFDCBTOfInitObjectFD()                                  (TRUE != FALSE)
#define Can_HasFDCTRLOfInitObjectFD()                                 (TRUE != FALSE)
#define Can_HasInitObjectFdBrsConfig()                                (TRUE != FALSE)
#define Can_HasInitObjectStartIndex()                                 (TRUE != FALSE)
#define Can_HasMailbox()                                              (TRUE != FALSE)
#define Can_HasActiveSendObjectOfMailbox()                            (TRUE != FALSE)
#define Can_HasControllerConfigIdxOfMailbox()                         (TRUE != FALSE)
#define Can_HasFdPaddingOfMailbox()                                   (TRUE != FALSE)
#define Can_HasHwHandleOfMailbox()                                    (TRUE != FALSE)
#define Can_HasIDValueOfMailbox()                                     (TRUE != FALSE)
#define Can_HasMailboxSizeOfMailbox()                                 (TRUE != FALSE)
#define Can_HasMailboxTypeOfMailbox()                                 (TRUE != FALSE)
#define Can_HasMaxDataLenOfMailbox()                                  (TRUE != FALSE)
#define Can_HasMemorySectionsIndexOfMailbox()                         (TRUE != FALSE)
#define Can_HasMemorySectionInfo()                                    (TRUE != FALSE)
#define Can_HasMemorySectionStartOfMemorySectionInfo()                (TRUE != FALSE)
#define Can_HasMemoryStartAddressOfMemorySectionInfo()                (TRUE != FALSE)
#define Can_HasMemorySectionObjects()                                 (TRUE != FALSE)
#define Can_HasHwHandleOfMemorySectionObjects()                       (TRUE != FALSE)
#define Can_HasMailboxElementOfMemorySectionObjects()                 (TRUE != FALSE)
#define Can_HasMailboxHandleOfMemorySectionObjects()                  (TRUE != FALSE)
#define Can_HasPlatformDll_GeneratorVersion()                         (TRUE != FALSE)
#define Can_HasSizeOfActiveSendObject()                               (TRUE != FALSE)
#define Can_HasSizeOfCanIfChannelId()                                 (TRUE != FALSE)
#define Can_HasSizeOfControllerConfig()                               (TRUE != FALSE)
#define Can_HasSizeOfControllerData()                                 (TRUE != FALSE)
#define Can_HasSizeOfFDMailboxMapping()                               (TRUE != FALSE)
#define Can_HasSizeOfInitBasicCan()                                   (TRUE != FALSE)
#define Can_HasSizeOfInitBasicCanIndex()                              (TRUE != FALSE)
#define Can_HasSizeOfInitObject()                                     (TRUE != FALSE)
#define Can_HasSizeOfInitObjectBaudrate()                             (TRUE != FALSE)
#define Can_HasSizeOfInitObjectFD()                                   (TRUE != FALSE)
#define Can_HasSizeOfInitObjectFdBrsConfig()                          (TRUE != FALSE)
#define Can_HasSizeOfInitObjectStartIndex()                           (TRUE != FALSE)
#define Can_HasSizeOfMailbox()                                        (TRUE != FALSE)
#define Can_HasSizeOfMemorySectionInfo()                              (TRUE != FALSE)
#define Can_HasSizeOfMemorySectionObjects()                           (TRUE != FALSE)
#define Can_HasPCConfig()                                             (TRUE != FALSE)
#define Can_HasActiveSendObjectOfPCConfig()                           (TRUE != FALSE)
#define Can_HasBaseDll_GeneratorVersionOfPCConfig()                   (TRUE != FALSE)
#define Can_HasCanIfChannelIdOfPCConfig()                             (TRUE != FALSE)
#define Can_HasControllerConfigOfPCConfig()                           (TRUE != FALSE)
#define Can_HasControllerDataOfPCConfig()                             (TRUE != FALSE)
#define Can_HasFDMailboxMappingOfPCConfig()                           (TRUE != FALSE)
#define Can_HasInitBasicCanIndexOfPCConfig()                          (TRUE != FALSE)
#define Can_HasInitBasicCanOfPCConfig()                               (TRUE != FALSE)
#define Can_HasInitObjectBaudrateOfPCConfig()                         (TRUE != FALSE)
#define Can_HasInitObjectFDOfPCConfig()                               (TRUE != FALSE)
#define Can_HasInitObjectFdBrsConfigOfPCConfig()                      (TRUE != FALSE)
#define Can_HasInitObjectOfPCConfig()                                 (TRUE != FALSE)
#define Can_HasInitObjectStartIndexOfPCConfig()                       (TRUE != FALSE)
#define Can_HasMailboxOfPCConfig()                                    (TRUE != FALSE)
#define Can_HasMemorySectionInfoOfPCConfig()                          (TRUE != FALSE)
#define Can_HasMemorySectionObjectsOfPCConfig()                       (TRUE != FALSE)
#define Can_HasPlatformDll_GeneratorVersionOfPCConfig()               (TRUE != FALSE)
#define Can_HasSizeOfActiveSendObjectOfPCConfig()                     (TRUE != FALSE)
#define Can_HasSizeOfCanIfChannelIdOfPCConfig()                       (TRUE != FALSE)
#define Can_HasSizeOfControllerConfigOfPCConfig()                     (TRUE != FALSE)
#define Can_HasSizeOfControllerDataOfPCConfig()                       (TRUE != FALSE)
#define Can_HasSizeOfFDMailboxMappingOfPCConfig()                     (TRUE != FALSE)
#define Can_HasSizeOfInitBasicCanIndexOfPCConfig()                    (TRUE != FALSE)
#define Can_HasSizeOfInitBasicCanOfPCConfig()                         (TRUE != FALSE)
#define Can_HasSizeOfInitObjectBaudrateOfPCConfig()                   (TRUE != FALSE)
#define Can_HasSizeOfInitObjectFDOfPCConfig()                         (TRUE != FALSE)
#define Can_HasSizeOfInitObjectFdBrsConfigOfPCConfig()                (TRUE != FALSE)
#define Can_HasSizeOfInitObjectOfPCConfig()                           (TRUE != FALSE)
#define Can_HasSizeOfInitObjectStartIndexOfPCConfig()                 (TRUE != FALSE)
#define Can_HasSizeOfMailboxOfPCConfig()                              (TRUE != FALSE)
#define Can_HasSizeOfMemorySectionInfoOfPCConfig()                    (TRUE != FALSE)
#define Can_HasSizeOfMemorySectionObjectsOfPCConfig()                 (TRUE != FALSE)
/** 
  \}
*/ 

/** 
  \defgroup  CanPCIncrementDataMacros  Can Increment Data Macros (PRE_COMPILE)
  \brief  These macros can be used to increment VAR data with numerical nature.
  \{
*/ 
#define Can_IncPduOfActiveSendObject(Index)                           Can_GetPduOfActiveSendObject(Index)++
#define Can_IncStateOfActiveSendObject(Index)                         Can_GetStateOfActiveSendObject(Index)++
#define Can_IncBusOffCounterOfControllerData(Index)                   Can_GetBusOffCounterOfControllerData(Index)++
#define Can_IncBusOffTransitionRequestOfControllerData(Index)         Can_GetBusOffTransitionRequestOfControllerData(Index)++
#define Can_IncCanInterruptCounterOfControllerData(Index)             Can_GetCanInterruptCounterOfControllerData(Index)++
#define Can_IncCanInterruptOldStatusOfControllerData(Index)           Can_GetCanInterruptOldStatusOfControllerData(Index)++
#define Can_IncLastInitObjectOfControllerData(Index)                  Can_GetLastInitObjectOfControllerData(Index)++
#define Can_IncLogStatusOfControllerData(Index)                       Can_GetLogStatusOfControllerData(Index)++
#define Can_IncLoopTimeoutOfControllerData(Index)                     Can_GetLoopTimeoutOfControllerData(Index)++
#define Can_IncModeTransitionRequestOfControllerData(Index)           Can_GetModeTransitionRequestOfControllerData(Index)++
#define Can_IncRamCheckTransitionRequestOfControllerData(Index)       Can_GetRamCheckTransitionRequestOfControllerData(Index)++
#define Can_IncRxMsgBufferOfControllerData(Index)                     Can_GetRxMsgBufferOfControllerData(Index)++
/** 
  \}
*/ 

/** 
  \defgroup  CanPCDecrementDataMacros  Can Decrement Data Macros (PRE_COMPILE)
  \brief  These macros can be used to decrement VAR data with numerical nature.
  \{
*/ 
#define Can_DecPduOfActiveSendObject(Index)                           Can_GetPduOfActiveSendObject(Index)--
#define Can_DecStateOfActiveSendObject(Index)                         Can_GetStateOfActiveSendObject(Index)--
#define Can_DecBusOffCounterOfControllerData(Index)                   Can_GetBusOffCounterOfControllerData(Index)--
#define Can_DecBusOffTransitionRequestOfControllerData(Index)         Can_GetBusOffTransitionRequestOfControllerData(Index)--
#define Can_DecCanInterruptCounterOfControllerData(Index)             Can_GetCanInterruptCounterOfControllerData(Index)--
#define Can_DecCanInterruptOldStatusOfControllerData(Index)           Can_GetCanInterruptOldStatusOfControllerData(Index)--
#define Can_DecLastInitObjectOfControllerData(Index)                  Can_GetLastInitObjectOfControllerData(Index)--
#define Can_DecLogStatusOfControllerData(Index)                       Can_GetLogStatusOfControllerData(Index)--
#define Can_DecLoopTimeoutOfControllerData(Index)                     Can_GetLoopTimeoutOfControllerData(Index)--
#define Can_DecModeTransitionRequestOfControllerData(Index)           Can_GetModeTransitionRequestOfControllerData(Index)--
#define Can_DecRamCheckTransitionRequestOfControllerData(Index)       Can_GetRamCheckTransitionRequestOfControllerData(Index)--
#define Can_DecRxMsgBufferOfControllerData(Index)                     Can_GetRxMsgBufferOfControllerData(Index)--
/** 
  \}
*/ 

  /* PRQA L:Macros_3453 */
/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL ACCESS FUNCTION MACROS
**********************************************************************************************************************/

/** 
  \defgroup  DataAccessMacros  Data Access Macros
  \brief  generated data access macros to abstract the generated data from the code to read and write CONST or VAR data.
  \{
*/ 
  /* PRQA S 3453 Macros_3453 */  /* MD_MSR_FctLikeMacro */
/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL FUNCTION MACROS
**********************************************************************************************************************/
  /* PRQA L:Macros_3453 */
/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL ACCESS FUNCTION MACROS
**********************************************************************************************************************/

/** 
  \defgroup  DataAccessMacros  Data Access Macros
  \brief  generated data access macros to abstract the generated data from the code to read and write CONST or VAR data.
  \{
*/ 
  /* PRQA S 3453 Macros_3453 */  /* MD_MSR_FctLikeMacro */
/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL FUNCTION MACROS
**********************************************************************************************************************/
  /* PRQA L:Macros_3453 */
/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL ACCESS FUNCTION MACROS
**********************************************************************************************************************/


/**********************************************************************************************************************
  GLOBAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL SIMPLE DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/** 
  \defgroup  CanPCIterableTypes  Can Iterable Types (PRE_COMPILE)
  \brief  These type definitions are used to iterate over an array with least processor cycles for variable access as possible.
  \{
*/ 
/**   \brief  type used to iterate Can_ActiveSendObject */
typedef uint8_least Can_ActiveSendObjectIterType;

/**   \brief  type used to iterate Can_CanIfChannelId */
typedef uint8_least Can_CanIfChannelIdIterType;

/**   \brief  type used to iterate Can_ControllerConfig */
typedef uint8_least Can_ControllerConfigIterType;

/**   \brief  type used to iterate Can_FDMailboxMapping */
typedef uint8_least Can_FDMailboxMappingIterType;

/**   \brief  type used to iterate Can_InitBasicCan */
typedef uint8_least Can_InitBasicCanIterType;

/**   \brief  type used to iterate Can_InitBasicCanIndex */
typedef uint8_least Can_InitBasicCanIndexIterType;

/**   \brief  type used to iterate Can_InitObject */
typedef uint8_least Can_InitObjectIterType;

/**   \brief  type used to iterate Can_InitObjectBaudrate */
typedef uint8_least Can_InitObjectBaudrateIterType;

/**   \brief  type used to iterate Can_InitObjectFD */
typedef uint8_least Can_InitObjectFDIterType;

/**   \brief  type used to iterate Can_InitObjectFdBrsConfig */
typedef uint8_least Can_InitObjectFdBrsConfigIterType;

/**   \brief  type used to iterate Can_InitObjectStartIndex */
typedef uint8_least Can_InitObjectStartIndexIterType;

/**   \brief  type used to iterate Can_Mailbox */
typedef uint8_least Can_MailboxIterType;

/**   \brief  type used to iterate Can_MemorySectionInfo */
typedef uint8_least Can_MemorySectionInfoIterType;

/**   \brief  type used to iterate Can_MemorySectionObjects */
typedef uint8_least Can_MemorySectionObjectsIterType;

/** 
  \}
*/ 

/** 
  \defgroup  CanPCIterableTypesWithSizeRelations  Can Iterable Types With Size Relations (PRE_COMPILE)
  \brief  These type definitions are used to iterate over a VAR based array with the same iterator as the related CONST array.
  \{
*/ 
/**   \brief  type used to iterate Can_ControllerData */
typedef Can_ControllerConfigIterType Can_ControllerDataIterType;

/** 
  \}
*/ 

/** 
  \defgroup  CanPCValueTypes  Can Value Types (PRE_COMPILE)
  \brief  These type definitions are used for value based data representations.
  \{
*/ 
/**   \brief  value based type definition for Can_PduOfActiveSendObject */
typedef PduIdType Can_PduOfActiveSendObjectType;

/**   \brief  value based type definition for Can_StateOfActiveSendObject */
typedef uint16 Can_StateOfActiveSendObjectType;

/**   \brief  value based type definition for Can_BaseDll_GeneratorVersion */
typedef uint16 Can_BaseDll_GeneratorVersionType;

/**   \brief  value based type definition for Can_CanIfChannelId */
typedef uint8 Can_CanIfChannelIdType;

/**   \brief  value based type definition for Can_BaseAddressOfControllerConfig */
typedef uint32 Can_BaseAddressOfControllerConfigType;

/**   \brief  value based type definition for Can_CanControllerDefaultBaudrateIdxOfControllerConfig */
typedef uint8 Can_CanControllerDefaultBaudrateIdxOfControllerConfigType;

/**   \brief  value based type definition for Can_CanControllerDefaultBaudrateOfControllerConfig */
typedef uint16 Can_CanControllerDefaultBaudrateOfControllerConfigType;

/**   \brief  value based type definition for Can_FDHwChannelIndirectionOfControllerConfig */
typedef uint8 Can_FDHwChannelIndirectionOfControllerConfigType;

/**   \brief  value based type definition for Can_FDMailboxMaxWordLengthOfControllerConfig */
typedef uint8 Can_FDMailboxMaxWordLengthOfControllerConfigType;

/**   \brief  value based type definition for Can_HasCANFDBaudrateOfControllerConfig */
typedef boolean Can_HasCANFDBaudrateOfControllerConfigType;

/**   \brief  value based type definition for Can_InterruptMask1OfControllerConfig */
typedef uint8 Can_InterruptMask1OfControllerConfigType;

/**   \brief  value based type definition for Can_MailboxRxBasicEndIdxOfControllerConfig */
typedef uint8 Can_MailboxRxBasicEndIdxOfControllerConfigType;

/**   \brief  value based type definition for Can_MailboxRxBasicLengthOfControllerConfig */
typedef uint8 Can_MailboxRxBasicLengthOfControllerConfigType;

/**   \brief  value based type definition for Can_MailboxRxBasicStartIdxOfControllerConfig */
typedef uint8 Can_MailboxRxBasicStartIdxOfControllerConfigType;

/**   \brief  value based type definition for Can_MailboxRxBasicUsedOfControllerConfig */
typedef boolean Can_MailboxRxBasicUsedOfControllerConfigType;

/**   \brief  value based type definition for Can_MailboxTxBasicEndIdxOfControllerConfig */
typedef uint8 Can_MailboxTxBasicEndIdxOfControllerConfigType;

/**   \brief  value based type definition for Can_MailboxTxBasicLengthOfControllerConfig */
typedef uint8 Can_MailboxTxBasicLengthOfControllerConfigType;

/**   \brief  value based type definition for Can_MailboxTxBasicStartIdxOfControllerConfig */
typedef uint8 Can_MailboxTxBasicStartIdxOfControllerConfigType;

/**   \brief  value based type definition for Can_MailboxTxBasicUsedOfControllerConfig */
typedef boolean Can_MailboxTxBasicUsedOfControllerConfigType;

/**   \brief  value based type definition for Can_MailboxUnusedEndIdxOfControllerConfig */
typedef uint8 Can_MailboxUnusedEndIdxOfControllerConfigType;

/**   \brief  value based type definition for Can_MailboxUnusedLengthOfControllerConfig */
typedef uint8 Can_MailboxUnusedLengthOfControllerConfigType;

/**   \brief  value based type definition for Can_MailboxUnusedStartIdxOfControllerConfig */
typedef uint8 Can_MailboxUnusedStartIdxOfControllerConfigType;

/**   \brief  value based type definition for Can_MailboxUnusedUsedOfControllerConfig */
typedef boolean Can_MailboxUnusedUsedOfControllerConfigType;

/**   \brief  value based type definition for Can_NumberOfFiltersOfControllerConfig */
typedef uint8 Can_NumberOfFiltersOfControllerConfigType;

/**   \brief  value based type definition for Can_NumberOfFullConfigurableFiltersOfControllerConfig */
typedef uint8 Can_NumberOfFullConfigurableFiltersOfControllerConfigType;

/**   \brief  value based type definition for Can_NumberOfMaxMailboxesOfControllerConfig */
typedef uint8 Can_NumberOfMaxMailboxesOfControllerConfigType;

/**   \brief  value based type definition for Can_RFFNOfControllerConfig */
typedef uint8 Can_RFFNOfControllerConfigType;

/**   \brief  value based type definition for Can_RxBasicHwStartOfControllerConfig */
typedef uint8 Can_RxBasicHwStartOfControllerConfigType;

/**   \brief  value based type definition for Can_RxBasicHwStopOfControllerConfig */
typedef uint8 Can_RxBasicHwStopOfControllerConfigType;

/**   \brief  value based type definition for Can_RxFullHwStartOfControllerConfig */
typedef uint8 Can_RxFullHwStartOfControllerConfigType;

/**   \brief  value based type definition for Can_RxFullHwStopOfControllerConfig */
typedef uint8 Can_RxFullHwStopOfControllerConfigType;

/**   \brief  value based type definition for Can_TxBasicHwStartOfControllerConfig */
typedef uint8 Can_TxBasicHwStartOfControllerConfigType;

/**   \brief  value based type definition for Can_TxBasicHwStopOfControllerConfig */
typedef uint8 Can_TxBasicHwStopOfControllerConfigType;

/**   \brief  value based type definition for Can_TxFullHwStartOfControllerConfig */
typedef uint8 Can_TxFullHwStartOfControllerConfigType;

/**   \brief  value based type definition for Can_TxFullHwStopOfControllerConfig */
typedef uint8 Can_TxFullHwStopOfControllerConfigType;

/**   \brief  value based type definition for Can_UnusedHwStartOfControllerConfig */
typedef uint8 Can_UnusedHwStartOfControllerConfigType;

/**   \brief  value based type definition for Can_UnusedHwStopOfControllerConfig */
typedef uint8 Can_UnusedHwStopOfControllerConfigType;

/**   \brief  value based type definition for Can_BusOffCounterOfControllerData */
typedef uint8 Can_BusOffCounterOfControllerDataType;

/**   \brief  value based type definition for Can_BusOffTransitionRequestOfControllerData */
typedef uint8 Can_BusOffTransitionRequestOfControllerDataType;

/**   \brief  value based type definition for Can_CanInterruptCounterOfControllerData */
typedef uint8 Can_CanInterruptCounterOfControllerDataType;

/**   \brief  value based type definition for Can_IsBusOffOfControllerData */
typedef boolean Can_IsBusOffOfControllerDataType;

/**   \brief  value based type definition for Can_LastInitObjectOfControllerData */
typedef uint8 Can_LastInitObjectOfControllerDataType;

/**   \brief  value based type definition for Can_LogStatusOfControllerData */
typedef uint8 Can_LogStatusOfControllerDataType;

/**   \brief  value based type definition for Can_ModeTransitionRequestOfControllerData */
typedef uint8 Can_ModeTransitionRequestOfControllerDataType;

/**   \brief  value based type definition for Can_RamCheckTransitionRequestOfControllerData */
typedef uint8 Can_RamCheckTransitionRequestOfControllerDataType;

/**   \brief  value based type definition for Can_StartModeRequestedOfControllerData */
typedef boolean Can_StartModeRequestedOfControllerDataType;

/**   \brief  value based type definition for Can_FDMailboxMapping */
typedef uint32 Can_FDMailboxMappingType;

/**   \brief  value based type definition for Can_InitCodeOfInitBasicCan */
typedef uint32 Can_InitCodeOfInitBasicCanType;

/**   \brief  value based type definition for Can_InitMaskOfInitBasicCan */
typedef uint32 Can_InitMaskOfInitBasicCanType;

/**   \brief  value based type definition for Can_InitBasicCanIndex */
typedef uint8 Can_InitBasicCanIndexType;

/**   \brief  value based type definition for Can_CBTOfInitObject */
typedef uint32 Can_CBTOfInitObjectType;

/**   \brief  value based type definition for Can_Control1OfInitObject */
typedef uint32 Can_Control1OfInitObjectType;

/**   \brief  value based type definition for Can_InitObjectBaudrate */
typedef uint16 Can_InitObjectBaudrateType;

/**   \brief  value based type definition for Can_FDCBTOfInitObjectFD */
typedef uint32 Can_FDCBTOfInitObjectFDType;

/**   \brief  value based type definition for Can_FDCTRLOfInitObjectFD */
typedef uint32 Can_FDCTRLOfInitObjectFDType;

/**   \brief  value based type definition for Can_InitObjectFdBrsConfig */
typedef uint8 Can_InitObjectFdBrsConfigType;

/**   \brief  value based type definition for Can_InitObjectStartIndex */
typedef uint8 Can_InitObjectStartIndexType;

/**   \brief  value based type definition for Can_ActiveSendObjectOfMailbox */
typedef uint8 Can_ActiveSendObjectOfMailboxType;

/**   \brief  value based type definition for Can_ControllerConfigIdxOfMailbox */
typedef uint8 Can_ControllerConfigIdxOfMailboxType;

/**   \brief  value based type definition for Can_FdPaddingOfMailbox */
typedef uint8 Can_FdPaddingOfMailboxType;

/**   \brief  value based type definition for Can_HwHandleOfMailbox */
typedef uint8 Can_HwHandleOfMailboxType;

/**   \brief  value based type definition for Can_IDValueOfMailbox */
typedef uint8 Can_IDValueOfMailboxType;

/**   \brief  value based type definition for Can_MailboxSizeOfMailbox */
typedef uint8 Can_MailboxSizeOfMailboxType;

/**   \brief  value based type definition for Can_MailboxTypeOfMailbox */
typedef uint8 Can_MailboxTypeOfMailboxType;

/**   \brief  value based type definition for Can_MaxDataLenOfMailbox */
typedef uint8 Can_MaxDataLenOfMailboxType;

/**   \brief  value based type definition for Can_MemorySectionsIndexOfMailbox */
typedef uint8 Can_MemorySectionsIndexOfMailboxType;

/**   \brief  value based type definition for Can_MemorySectionStartOfMemorySectionInfo */
typedef uint8 Can_MemorySectionStartOfMemorySectionInfoType;

/**   \brief  value based type definition for Can_MemoryStartAddressOfMemorySectionInfo */
typedef uint32 Can_MemoryStartAddressOfMemorySectionInfoType;

/**   \brief  value based type definition for Can_HwHandleOfMemorySectionObjects */
typedef uint8 Can_HwHandleOfMemorySectionObjectsType;

/**   \brief  value based type definition for Can_MailboxElementOfMemorySectionObjects */
typedef uint8 Can_MailboxElementOfMemorySectionObjectsType;

/**   \brief  value based type definition for Can_MailboxHandleOfMemorySectionObjects */
typedef uint8 Can_MailboxHandleOfMemorySectionObjectsType;

/**   \brief  value based type definition for Can_PlatformDll_GeneratorVersion */
typedef uint16 Can_PlatformDll_GeneratorVersionType;

/**   \brief  value based type definition for Can_SizeOfActiveSendObject */
typedef uint8 Can_SizeOfActiveSendObjectType;

/**   \brief  value based type definition for Can_SizeOfCanIfChannelId */
typedef uint8 Can_SizeOfCanIfChannelIdType;

/**   \brief  value based type definition for Can_SizeOfControllerConfig */
typedef uint8 Can_SizeOfControllerConfigType;

/**   \brief  value based type definition for Can_SizeOfControllerData */
typedef uint8 Can_SizeOfControllerDataType;

/**   \brief  value based type definition for Can_SizeOfFDMailboxMapping */
typedef uint8 Can_SizeOfFDMailboxMappingType;

/**   \brief  value based type definition for Can_SizeOfInitBasicCan */
typedef uint8 Can_SizeOfInitBasicCanType;

/**   \brief  value based type definition for Can_SizeOfInitBasicCanIndex */
typedef uint8 Can_SizeOfInitBasicCanIndexType;

/**   \brief  value based type definition for Can_SizeOfInitObject */
typedef uint8 Can_SizeOfInitObjectType;

/**   \brief  value based type definition for Can_SizeOfInitObjectBaudrate */
typedef uint8 Can_SizeOfInitObjectBaudrateType;

/**   \brief  value based type definition for Can_SizeOfInitObjectFD */
typedef uint8 Can_SizeOfInitObjectFDType;

/**   \brief  value based type definition for Can_SizeOfInitObjectFdBrsConfig */
typedef uint8 Can_SizeOfInitObjectFdBrsConfigType;

/**   \brief  value based type definition for Can_SizeOfInitObjectStartIndex */
typedef uint8 Can_SizeOfInitObjectStartIndexType;

/**   \brief  value based type definition for Can_SizeOfMailbox */
typedef uint8 Can_SizeOfMailboxType;

/**   \brief  value based type definition for Can_SizeOfMemorySectionInfo */
typedef uint8 Can_SizeOfMemorySectionInfoType;

/**   \brief  value based type definition for Can_SizeOfMemorySectionObjects */
typedef uint8 Can_SizeOfMemorySectionObjectsType;

/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL COMPLEX DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/** 
  \defgroup  CanPCStructTypes  Can Struct Types (PRE_COMPILE)
  \brief  These type definitions are used for structured data representations.
  \{
*/ 
/**   \brief  type used in Can_ActiveSendObject */
typedef struct sCan_ActiveSendObjectType
{
  Can_StateOfActiveSendObjectType StateOfActiveSendObject;  /**< send state like cancelled or send activ */
  Can_PduOfActiveSendObjectType PduOfActiveSendObject;  /**< buffered PduId for confirmation or cancellation */
} Can_ActiveSendObjectType;

/**   \brief  type used in Can_ControllerConfig */
typedef struct sCan_ControllerConfigType
{
  Can_BaseAddressOfControllerConfigType BaseAddressOfControllerConfig;
  Can_CanControllerDefaultBaudrateOfControllerConfigType CanControllerDefaultBaudrateOfControllerConfig;
  Can_HasCANFDBaudrateOfControllerConfigType HasCANFDBaudrateOfControllerConfig;
  Can_CanControllerDefaultBaudrateIdxOfControllerConfigType CanControllerDefaultBaudrateIdxOfControllerConfig;
  Can_FDHwChannelIndirectionOfControllerConfigType FDHwChannelIndirectionOfControllerConfig;  /**< This table contains indirection values for the Hw Channel for CANFD configurations. */
  Can_FDMailboxMaxWordLengthOfControllerConfigType FDMailboxMaxWordLengthOfControllerConfig;
  Can_InterruptMask1OfControllerConfigType InterruptMask1OfControllerConfig;
  Can_MailboxRxBasicEndIdxOfControllerConfigType MailboxRxBasicEndIdxOfControllerConfig;  /**< the end index of the 0:n relation pointing to Can_Mailbox */
  Can_MailboxRxBasicLengthOfControllerConfigType MailboxRxBasicLengthOfControllerConfig;  /**< the number of relations pointing to Can_Mailbox */
  Can_MailboxRxBasicStartIdxOfControllerConfigType MailboxRxBasicStartIdxOfControllerConfig;  /**< the start index of the 0:n relation pointing to Can_Mailbox */
  Can_MailboxTxBasicEndIdxOfControllerConfigType MailboxTxBasicEndIdxOfControllerConfig;  /**< the end index of the 0:n relation pointing to Can_Mailbox */
  Can_MailboxTxBasicLengthOfControllerConfigType MailboxTxBasicLengthOfControllerConfig;  /**< the number of relations pointing to Can_Mailbox */
  Can_MailboxTxBasicStartIdxOfControllerConfigType MailboxTxBasicStartIdxOfControllerConfig;  /**< the start index of the 0:n relation pointing to Can_Mailbox */
  Can_MailboxUnusedEndIdxOfControllerConfigType MailboxUnusedEndIdxOfControllerConfig;  /**< the end index of the 0:n relation pointing to Can_Mailbox */
  Can_MailboxUnusedLengthOfControllerConfigType MailboxUnusedLengthOfControllerConfig;  /**< the number of relations pointing to Can_Mailbox */
  Can_MailboxUnusedStartIdxOfControllerConfigType MailboxUnusedStartIdxOfControllerConfig;  /**< the start index of the 0:n relation pointing to Can_Mailbox */
  Can_NumberOfFiltersOfControllerConfigType NumberOfFiltersOfControllerConfig;
  Can_NumberOfFullConfigurableFiltersOfControllerConfigType NumberOfFullConfigurableFiltersOfControllerConfig;
  Can_NumberOfMaxMailboxesOfControllerConfigType NumberOfMaxMailboxesOfControllerConfig;
  Can_RFFNOfControllerConfigType RFFNOfControllerConfig;
  Can_RxBasicHwStartOfControllerConfigType RxBasicHwStartOfControllerConfig;
  Can_RxBasicHwStopOfControllerConfigType RxBasicHwStopOfControllerConfig;
  Can_RxFullHwStartOfControllerConfigType RxFullHwStartOfControllerConfig;
  Can_RxFullHwStopOfControllerConfigType RxFullHwStopOfControllerConfig;
  Can_TxBasicHwStartOfControllerConfigType TxBasicHwStartOfControllerConfig;
  Can_TxBasicHwStopOfControllerConfigType TxBasicHwStopOfControllerConfig;
  Can_TxFullHwStartOfControllerConfigType TxFullHwStartOfControllerConfig;
  Can_TxFullHwStopOfControllerConfigType TxFullHwStopOfControllerConfig;
  Can_UnusedHwStartOfControllerConfigType UnusedHwStartOfControllerConfig;
  Can_UnusedHwStopOfControllerConfigType UnusedHwStopOfControllerConfig;
} Can_ControllerConfigType;

/**   \brief  type used in Can_ControllerData */
typedef struct sCan_ControllerDataType
{
  Can_BusOffCounterOfControllerDataType BusOffCounterOfControllerData;  /**< This variable stores the busoff recovery timeout counter. */
  Can_BusOffTransitionRequestOfControllerDataType BusOffTransitionRequestOfControllerData;  /**< CAN state request for each controller: ContinueBusOffRecovery=0x00, FinishBusOffRecovery=0x01 */
  Can_CanInterruptCounterOfControllerDataType CanInterruptCounterOfControllerData;  /**< CAN interrupt disable counter for each controller */
  Can_IsBusOffOfControllerDataType IsBusOffOfControllerData;  /**< CAN state for each controller: busoff occur */
  Can_LastInitObjectOfControllerDataType LastInitObjectOfControllerData;  /**< last set baudrate for reinit */
  Can_LogStatusOfControllerDataType LogStatusOfControllerData;  /**< CAN state for each controller: UNINIT=0x00, START=0x01, STOP=0x02, INIT=0x04, INCONSISTENT=0x08, WARNING =0x10, PASSIVE=0x20, BUSOFF=0x40, SLEEP=0x80 */
  Can_ModeTransitionRequestOfControllerDataType ModeTransitionRequestOfControllerData;  /**< CAN state request for each controller: INIT=0x00, SLEEP=0x01, WAKEUP=0x02, STOP+INIT=0x03, START=0x04, START+INIT=0x05, NONE=0x06 */
  Can_RamCheckTransitionRequestOfControllerDataType RamCheckTransitionRequestOfControllerData;  /**< CAN state request for each controller: kCanSuppressRamCheck=0x01, kCanExecuteRamCheck=0x00 */
  Can_StartModeRequestedOfControllerDataType StartModeRequestedOfControllerData;  /**< This variable stores if the start mode is of a special CAN Controller is already requested in the busoff recovery process. */
  tCanLLCanIntOld CanInterruptOldStatusOfControllerData;  /**< last CAN interrupt status for restore interrupt for each controller */
  Can_LoopTimeout_dim_type LoopTimeoutOfControllerData;  /**< hw loop timeout for each controller */
  tCanRxMsgBuffer RxMsgBufferOfControllerData;  /**< This variable stores received values (ID, DLC, DATA) in the reception process. */
} Can_ControllerDataType;

/**   \brief  type used in Can_InitBasicCan */
typedef struct sCan_InitBasicCanType
{
  Can_InitCodeOfInitBasicCanType InitCodeOfInitBasicCan;
  Can_InitMaskOfInitBasicCanType InitMaskOfInitBasicCan;
} Can_InitBasicCanType;

/**   \brief  type used in Can_InitObject */
typedef struct sCan_InitObjectType
{
  Can_CBTOfInitObjectType CBTOfInitObject;
  Can_Control1OfInitObjectType Control1OfInitObject;
} Can_InitObjectType;

/**   \brief  type used in Can_InitObjectFD */
typedef struct sCan_InitObjectFDType
{
  Can_FDCBTOfInitObjectFDType FDCBTOfInitObjectFD;
  Can_FDCTRLOfInitObjectFDType FDCTRLOfInitObjectFD;
} Can_InitObjectFDType;

/**   \brief  type used in Can_Mailbox */
typedef struct sCan_MailboxType
{
  Can_ActiveSendObjectOfMailboxType ActiveSendObjectOfMailbox;
  Can_ControllerConfigIdxOfMailboxType ControllerConfigIdxOfMailbox;  /**< the index of the 1:1 relation pointing to Can_ControllerConfig */
  Can_FdPaddingOfMailboxType FdPaddingOfMailbox;
  Can_HwHandleOfMailboxType HwHandleOfMailbox;
  Can_IDValueOfMailboxType IDValueOfMailbox;
  Can_MailboxSizeOfMailboxType MailboxSizeOfMailbox;
  Can_MailboxTypeOfMailboxType MailboxTypeOfMailbox;
  Can_MaxDataLenOfMailboxType MaxDataLenOfMailbox;
  Can_MemorySectionsIndexOfMailboxType MemorySectionsIndexOfMailbox;
} Can_MailboxType;

/**   \brief  type used in Can_MemorySectionInfo */
typedef struct sCan_MemorySectionInfoType
{
  Can_MemoryStartAddressOfMemorySectionInfoType MemoryStartAddressOfMemorySectionInfo;
  Can_MemorySectionStartOfMemorySectionInfoType MemorySectionStartOfMemorySectionInfo;
} Can_MemorySectionInfoType;

/**   \brief  type used in Can_MemorySectionObjects */
typedef struct sCan_MemorySectionObjectsType
{
  Can_HwHandleOfMemorySectionObjectsType HwHandleOfMemorySectionObjects;
  Can_MailboxElementOfMemorySectionObjectsType MailboxElementOfMemorySectionObjects;
  Can_MailboxHandleOfMemorySectionObjectsType MailboxHandleOfMemorySectionObjects;
} Can_MemorySectionObjectsType;

/** 
  \}
*/ 

/** 
  \defgroup  CanPCRootPointerTypes  Can Root Pointer Types (PRE_COMPILE)
  \brief  These type definitions are used to point from the config root to symbol instances.
  \{
*/ 
/**   \brief  type used to point to Can_ActiveSendObject */
typedef P2VAR(Can_ActiveSendObjectType, TYPEDEF, CAN_VAR_NOINIT) Can_ActiveSendObjectPtrType;

/**   \brief  type used to point to Can_CanIfChannelId */
typedef P2CONST(Can_CanIfChannelIdType, TYPEDEF, CAN_CONST) Can_CanIfChannelIdPtrType;

/**   \brief  type used to point to Can_ControllerConfig */
typedef P2CONST(Can_ControllerConfigType, TYPEDEF, CAN_CONST) Can_ControllerConfigPtrType;

/**   \brief  type used to point to Can_ControllerData */
typedef P2VAR(Can_ControllerDataType, TYPEDEF, CAN_VAR_NOINIT) Can_ControllerDataPtrType;

/**   \brief  type used to point to Can_FDMailboxMapping */
typedef P2CONST(Can_FDMailboxMappingType, TYPEDEF, CAN_CONST) Can_FDMailboxMappingPtrType;

/**   \brief  type used to point to Can_InitBasicCan */
typedef P2CONST(Can_InitBasicCanType, TYPEDEF, CAN_CONST) Can_InitBasicCanPtrType;

/**   \brief  type used to point to Can_InitBasicCanIndex */
typedef P2CONST(Can_InitBasicCanIndexType, TYPEDEF, CAN_CONST) Can_InitBasicCanIndexPtrType;

/**   \brief  type used to point to Can_InitObject */
typedef P2CONST(Can_InitObjectType, TYPEDEF, CAN_CONST) Can_InitObjectPtrType;

/**   \brief  type used to point to Can_InitObjectBaudrate */
typedef P2CONST(Can_InitObjectBaudrateType, TYPEDEF, CAN_CONST) Can_InitObjectBaudratePtrType;

/**   \brief  type used to point to Can_InitObjectFD */
typedef P2CONST(Can_InitObjectFDType, TYPEDEF, CAN_CONST) Can_InitObjectFDPtrType;

/**   \brief  type used to point to Can_InitObjectFdBrsConfig */
typedef P2CONST(Can_InitObjectFdBrsConfigType, TYPEDEF, CAN_CONST) Can_InitObjectFdBrsConfigPtrType;

/**   \brief  type used to point to Can_InitObjectStartIndex */
typedef P2CONST(Can_InitObjectStartIndexType, TYPEDEF, CAN_CONST) Can_InitObjectStartIndexPtrType;

/**   \brief  type used to point to Can_Mailbox */
typedef P2CONST(Can_MailboxType, TYPEDEF, CAN_CONST) Can_MailboxPtrType;

/**   \brief  type used to point to Can_MemorySectionInfo */
typedef P2CONST(Can_MemorySectionInfoType, TYPEDEF, CAN_CONST) Can_MemorySectionInfoPtrType;

/**   \brief  type used to point to Can_MemorySectionObjects */
typedef P2CONST(Can_MemorySectionObjectsType, TYPEDEF, CAN_CONST) Can_MemorySectionObjectsPtrType;

/** 
  \}
*/ 

/** 
  \defgroup  CanPCRootValueTypes  Can Root Value Types (PRE_COMPILE)
  \brief  These type definitions are used for value representations in root arrays.
  \{
*/ 
/**   \brief  type used in Can_PCConfig */
typedef struct sCan_PCConfigType
{
  uint8 Can_PCConfigNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} Can_PCConfigType;

typedef Can_PCConfigType Can_ConfigType;  /**< A structure type is present for data in each configuration class. This typedef redefines the probably different name to the specified one. */

/** 
  \}
*/ 


/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL SIMPLE DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL COMPLEX DATA TYPES AND STRUCTURES
**********************************************************************************************************************/

/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL SIMPLE DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL COMPLEX DATA TYPES AND STRUCTURES
**********************************************************************************************************************/


/**********************************************************************************************************************
  GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA PROTOTYPES
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
extern CONST(Can_CanIfChannelIdType, CAN_CONST) Can_CanIfChannelId[1];
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
extern CONST(Can_ControllerConfigType, CAN_CONST) Can_ControllerConfig[1];
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
extern CONST(Can_FDMailboxMappingType, CAN_CONST) Can_FDMailboxMapping[5];
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
extern CONST(Can_InitBasicCanType, CAN_CONST) Can_InitBasicCan[4];
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
extern CONST(Can_InitBasicCanIndexType, CAN_CONST) Can_InitBasicCanIndex[1];
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
extern CONST(Can_InitObjectType, CAN_CONST) Can_InitObject[1];
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
extern CONST(Can_InitObjectBaudrateType, CAN_CONST) Can_InitObjectBaudrate[1];
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
extern CONST(Can_InitObjectFDType, CAN_CONST) Can_InitObjectFD[1];
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
extern CONST(Can_InitObjectFdBrsConfigType, CAN_CONST) Can_InitObjectFdBrsConfig[1];
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
extern CONST(Can_InitObjectStartIndexType, CAN_CONST) Can_InitObjectStartIndex[2];
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
extern CONST(Can_MailboxType, CAN_CONST) Can_Mailbox[4];
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
extern CONST(Can_MemorySectionInfoType, CAN_CONST) Can_MemorySectionInfo[1];
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
extern CONST(Can_MemorySectionObjectsType, CAN_CONST) Can_MemorySectionObjects[7];
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
extern VAR(Can_ActiveSendObjectType, CAN_VAR_NOINIT) Can_ActiveSendObject[1];
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
extern VAR(Can_ControllerDataType, CAN_VAR_NOINIT) Can_ControllerData[1];
#define CAN_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */


/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/

/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/


/**********************************************************************************************************************
  GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/

/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/

/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/


/* -----------------------------------------------------------------------------
    UserConfigFile
 ----------------------------------------------------------------------------- */
/* User Config File Start */

/* User Config File End */



#endif  /* CAN_CFG_H */
/**********************************************************************************************************************
  END OF FILE: Can_Cfg.h
**********************************************************************************************************************/
 

