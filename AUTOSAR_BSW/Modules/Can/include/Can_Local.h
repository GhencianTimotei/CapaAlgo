/* Kernbauer Version: 1.14 Konfiguration: DrvCan_Arm32Flexcan3Asr Erzeugungsgangnummer: 398 */

/* STARTSINGLE_OF_MULTIPLE */

/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*  \file     Can.c / Can_Irq.c / Can_Local.h
 *  \brief    Implementation of the CAN driver
 *  \details  see functional description below
 *
 *********************************************************************************************************************/
/* ***************************************************************************
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| Ht           Heike Honert              Vector Informatik GmbH
| Pl           Georg Pfluegel            Vector Informatik GmbH
| Bir          Holger Birke              Vector Informatik GmbH
| Rse          Robert Schelkle           Vector Informatik GmbH
| Rli          Roman Linder              Vector Informatik GmbH
| Yoe          Yacine Ould Boukhitine    Vector Informatik GmbH
| Bns          Benjamin Schuetterle      Vector Informatik GmbH
| Gaz          Carsten Gauglitz          Vector Informatik GmbH
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver   Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 2012-01-09  1.00.00  Rse    - ESCAN00056163: Initial version: Hll - Flexcan3 - Imx6 - QCC - High-End - QNX
| 2012-09-20  1.01.00  Rse    - ESCAN00062414: Support workaround for erratum ERR005829
| 2013-01-30  1.02.00  Rse    - ESCAN00065347: Support platform MPC5700
|                             - ESCAN00064665: CANbedded only: CAN messages will not be sent any more
|                             - ESCAN00066667: Support workaround for erratum e5769
|                             - ESCAN00067035: Inconsistent combination of receive handle and receive information (id, dlc, data) is indicated to upper layer
| 2013-05-21  1.03.00  Rse    - ESCAN00067478: Support FlexCAN2 derivatives for RxFifo usage
|                             - ESCAN00067660: Support the feature Mirror Mode
| 2013-07-22  1.04.00  Rse    - ESCAN00069229: Support CAN message retransmit feature for FBL driver
|                             - ESCAN00070121: Support Vybrid with FlexCAN3
| 2013-11-21  1.05.00  Rse    - ESCAN00072129: ASR4 only: change BusOff behavior to ensure recovery time of 128x11 recessive bits
|                             - ESCAN00072322: AR4-328: Predefined Runtime Measurement Points
| 2013-12-09  1.06.00  Rse    - ESCAN00072515: AutoSar only: Can_SetControllerMode(controller, CAN_T_STOP) returns CAN_OK instead of CAN_NOT_OK
|                             - ESCAN00072597: CANbedded only: Retransmit does not work if more than 22 RxFullCAN objects are used
| 2014-01-08  1.07.00  Rse    - ESCAN00072828: CANbedded only: Compiler error: identifier "canCanInterruptCounter" is undefined
|                             - ESCAN00072863: Support Cancel in Hardware with Transmission Abort feature
|                             - ESCAN00072869: Support new interface for Bus Mirroring
| 2014-01-30  1.07.01  Rse    - ESCAN00073299: Parity check only available for Vybrid and MPC5700 derivatives
| 2014-02-06  1.07.02  Rse    - Some minor MISRA improvements
|                      Rse    - ESCAN00073889: CANbedded only: Compiler error: struct has unknown field
| 2014-03-24  1.07.03  Rse    - ESCAN00074424: Indication function is called twice for the reception of one BasicCAN message
| 2014-04-16  1.08.00  Rse    - ESCAN00075110: BusOff notification is called twice for one single BusOff event (FlexCAN2)
|                             - ESCAN00075955: Remove obsolete workaround implementation for e5769
|                             - ESCAN00075964: Delete unnecessary interrupt locks
|                             - ESCAN00075507: IAR Compiler warning: the order of volatile accesses is undefined
| 2014-06-24  1.09.00  Rse    - ESCAN00076588: CAN clock settings are invalid after reinitialization, error frames occur continuously on the bus
|                             - ESCAN00076653: Implement proper mode switch to init (FREEZE) mode in CAN controller initialization process
|                             - ESCAN00076657: MAXMB value is obsolete
|                             - ESCAN00077049: CANbedded only: Support Tx FullCAN Send Delay (External PIA)
|                             - ESCAN00077083: CANbedded only: LowLevel Message is not transmitted
|                             - ESCAN00077485: OS Exception when CAN driver is handled in User Mode
| 2014-08-13  1.10.00  Rse    - ESCAN00077825: Support derivative MPC5748G CUT2
| 2014-11-10  1.10.01  Rse    - ESCAN00079385: Compiler warning: argument of type "volatile uint32 *" is incompatible with parameter of type "volatile uint16 *"
| 2014-11-27  2.00.00  Rse    - ESCAN00078072: Support full functionality for CAN-FD (Mode 2)
|                             - ESCAN00079900: CANbedded only: Extended ID message with dominant SRR-Bit does not receive
|                             - ESCAN00079901: Support ComStackLib tables for ASR403 R11
|                             - ESCAN00079494: Add loop checks for mode switching in CAN Controller initialization process
| 2015-01-21  2.00.01  Rse    - ESCAN00080716: Standard CAN message is sent as CAN-FD message with baudrate switch
| 2015-04-09  2.00.02  Was    - ESCAN00082335: Update to Core 5.00.02, R11 (Vybrid)
| 2015-05-02  2.01.00  Rse    - ESCAN00082800: Support CANbedded compatibility
| 2015-09-02  2.02.00  Zam    - ESCAN00084930: Support Extended CAN RAM Check feature
| 2015-10-14  2.03.00  Pl     - ESCAN00085860: Support S32K with FlexCAN3
| 2015-12-03  3.00.00  Rse    - ESCAN00086974: Support R14 and process 3.0
| 2016-03-17  3.01.00  Rse    - ESCAN00088969: Support Extended RAM check for MSR403
| 2016-05-30  3.01.01  Rse    - ESCAN00090210: Compiler error: parse error near ';'
| 2016-06-20  3.01.02  Rse    - Update HL-ASR 5.04.01 for issue 89754
| 2016-08-03  3.01.03  Rse    - ESCAN00091088: Callback that indicates corrupt CAN Controller is called erroneously
| 2016-08-25  3.02.00  Rse    - ESCAN00091626: Support R14 for Arm32 platforms
|                             - ESCAN00092139: Support ISO CAN-FD
|                             - ESCAN00092218: Support possibility to use a non-CAN-FD baudrate on a CAN-FD channel
|                             - ESCAN00092333: Support asymmetric mailboxes
| 2016-10-26  3.02.01  Rse    - ESCAN00092531: Linker Error: undefined symbol found 'Can_GetCanNumberOfMaxMailboxes'
| 2016-12-12  3.02.02  Rli    - ESCAN00093255: CAN FD FULL support for Little Endian Architectures
| 2017-03-30  3.02.03  Rli    - ESCAN00094552: Compiler error: identifier Controller not declared
| 2017-04-11  4.00.00  Rse    - ESCAN00094734: Beta support of RI2.0
| 2017-11-30  4.00.01  yoe    - ESCAN00097612: Beta support of RI2.0 for Arm32Flexcan3
| 2018-02-26  4.01.00  Rli    - ESCAN00098508: Final support of RI2.0 for Arm32Flexcan3
| 2018-03-07  4.01.01  Rli    - ESCAN00098514: add MISRA relevant changes
| 2018-04-27  4.02.00  Rli    - ESCAN00099193: Final support of RI2.0 for Mpc5700Flexcan3
| 2017-10-31  5.00.00  Rli    - ESCAN00097302 Support of SafeBSW for FlexCAN3
| 2018-03-08  5.00.01  Bns    - Update HL-ASR 5.07.02 for issue 96367
|                             - ESCAN00098678 Support Extended RAM Check for S32
| 2018-03-12  5.01.00  Gaz    - ESCAN00098459 Update to Core 6.00.00
| 2018-06-19  5.02.00  Rli    - ESCAN00099727 Support of Virtual Addressing with CAN FD Mode 2
| 2018-08-02  5.03.00  Rli    - STORYC-6186: Support Silent Mode
|                             - ESCAN00100316 IMX8: Messages not received with CAN FD configuration
| 2018-10-19  5.04.00  Yoe    - STORYC-6683: Support SafeBsw for Asymmetric Mailboxes
| 2018-10-31  5.04.01  Yoe    - STORYC-6877: Support SafeBsw for S32k1xx derivatives
| 2018-11-22  5.04.02  Rli    - STORYC-7138: Update code due to Cfg5 bugfix
| 2019-01-16  5.04.03  Rli    - ESCAN00101634: FlexCAN3 e10368: Transition of the CAN FD operation enable bit may lead FlexCAN logic to an inconsistent state
| 2019-02-02  6.00.00  Rli    - ESCAN00101108: RxFifo support for FlexCAN2 removed
|                             - STORYC-6864: Support AR4-R21 and update to new HighLevel interface
|                             - STORYC-6865: Mirror Mode support with FD  inclusively
|                             - STORYC-6866: Virtual Addressing support with FD mode 2 inclusively
|                             - STORYC-6867: Silent Mode support for baudrate detection
|                             - STORYC-7901: Support AR4-R22
| 2019-05-20  6.00.01  Rli    - STORYC-8800: Support IMX ASIL and Extended Ramcheck
| 2019-07-17  6.01.00  Bns    - STORYC-8855: Support Extended Ramcheck for canbedded
| 2019-07-17  6.01.01  Bns    - STORYC-8860: Core Update & Extended RAM Check fix
| 2019-09-25  6.01.02  Rli    - ESCAN00104425: Unlock RX FullCAN and RX BasicCAN mailbox may not work correctly (AUTOSAR only)
| 2020-04-21  6.02.00  Rli    - CAN1421: [FLEXCAN3] S32K2/3 support
|                             - ESCAN00106152: FlexCAN3: CAN memmap error
| 2020-10-06  6.02.01  Rli    - ESCAN00107557: Call to CanResetBusSleep() stays in STOPPED mode (Freeze mode) (CBD only)
| 2021-03-08  6.02.02  Dzi    - CAN-2167 Vybrid Support
|************************************************************************** */

#if !defined(CAN_LOCAL_H)
#define  CAN_LOCAL_H

/***************************************************************************/
/* Include                                                                 */
/***************************************************************************/
/* \trace SPEC-1583 */
#include "SchM_Can.h"
#include "Can.h"         /* include also all needed types */

/***************************************************************************/
/* Version Check                                                           */
/***************************************************************************/
/* \trace SPEC-20329 */
/* not the SW version but all file versions that represent the SW version are checked */
#if (CAN_COREVERSION           != 0x0900u) /* \trace SPEC-1699 */
# error "Header file are inconsistent!"
#endif
#if (CAN_RELEASE_COREVERSION   != 0x01u)
# error "Header file are inconsistent!"
#endif
#if( DRVCAN_IMXFLEXCAN3ASR_VERSION != 0x0602u)
# error "Source and Header file are inconsistent!"
#endif
#if( DRVCAN_IMXFLEXCAN3ASR_RELEASE_VERSION != 0x02u)
# error "Source and Header file are inconsistent!"
#endif

# if( CAN_GEN_ImxFlexcan3Asr_VERSION != 0x0101u)
#  error "Generated Data are inconsistent!"
# endif

/* PRQA S 3453 EOF */ /* MD_MSR_FctLikeMacro */

/***************************************************************************/
/* compatibility defines                                                   */
/***************************************************************************/
#if defined(C_ENABLE_MIXED_ID) || defined(C_ENABLE_EXTENDED_ID)
# define CAN_ID_IDE_MASK            0x80000000UL
# define CAN_ID_FD_MASK             0x40000000UL /* \trace SPEC-50553 */
# define CAN_ID_MASK                0x1FFFFFFFUL
# define CAN_ID_MASK_STD            0x000007FFUL
# define CAN_ID_UNUSED_MASK         0x20000000UL
#else
# define CAN_ID_IDE_MASK            0x0000U
# define CAN_ID_FD_MASK             0x4000U /* \trace SPEC-50553 */
# define CAN_ID_MASK                0x07FFU
# define CAN_ID_MASK_STD            0x07FFU
# define CAN_ID_UNUSED_MASK         0x3800U
#endif
#define kCanAllChannels  ((CanChannelHandle)0xFFU)

#if !defined(C_DRV_INTERNAL) /* COV_CAN_INTERNAL */
# error "Can_Local.h should only be included by Can.c"
#endif
/* real amount of controllers in this system (LT and PB) */
#define kCanNumberOfChannels  Can_GetControllerMax()
/* if kCanNumberOfChannels used to declare a table/dimension this table has to be generated to be also Link-Time-capable */
/*  -> see ESCAN00028069 controller-amount has to be Link-Time-capable */
/* real amount of controllers in this system (LT and PB) */
#define kCanNumberOfHwChannels  kCanNumberOfChannels

#if defined( C_SINGLE_RECEIVE_CHANNEL )
/* have to be done here to avoid declaration of "channel" in Can.h */
# define channel                                ((CanChannelHandle)0)
# define canHwChannel                           ((CanChannelHandle)0)
# define CAN_HL_HW_CHANNEL_STARTINDEX(ch)       ((CanChannelHandle)0)
# define CAN_HL_HW_CHANNEL_STOPINDEX(ch)        ((CanChannelHandle)0)
#else
# define channel                                Controller
# define canHwChannel                           Controller
# define CAN_HL_HW_CHANNEL_STARTINDEX(ch)       (ch)
# define CAN_HL_HW_CHANNEL_STOPINDEX(ch)        (ch)
#endif
#if !defined(CAN_TRANSITION_CHECK) /* COV_CAN_COMPATIBILITY */
# define CAN_TRANSITION_CHECK STD_ON /* default may be deactivated by user configuration */
#endif
#if !defined(CAN_REINIT_START) /* COV_CAN_COMPATIBILITY */
# define CAN_REINIT_START STD_OFF
#endif

#if !defined(CAN_OS_TICK2MS) /* COV_CAN_COMPATIBILITY */
# error "CAN_OS_TICK2MS() should be defined to OS_TICKS2MS_<counterShortName>() macro from OS"
#endif
#if !defined(CAN_OS_COUNTER_ID) /* COV_CAN_COMPATIBILITY */
# error "CAN_OS_COUNTER_ID should be defined to 'counterShortName' from OS"
#endif

#if !defined(CAN_ID_MASK_IN_GENERIC_CALLOUT) /* COV_CAN_COMPATIBILITY */
# define CAN_ID_MASK_IN_GENERIC_CALLOUT (CAN_ID_IDE_MASK | CAN_ID_FD_MASK | CAN_ID_MASK)
/* May be changed to mask out FD-bit: (CAN_ID_IDE_MASK | CAN_ID_MASK) */
#endif

#if !defined( C_ENABLE_BUSOFF_RECOVERY_COMPLIANT ) && !defined( C_DISABLE_BUSOFF_RECOVERY_COMPLIANT )
# define C_ENABLE_BUSOFF_RECOVERY_COMPLIANT
#endif

# if ( CAN_PROTECTED_MODE == STD_ON )
#  define C_ENABLE_USER_MODE_OS
# endif

/***************************************************************************/
/* Defines                                                                 */
/***************************************************************************/
/* for variable Can_ActiveSendState */
#define kCanBufferFree              (uint8)0xFF     /* mark objects as free */
#define kCanBufferCancel            (uint8)0xFE     /* mark object as currently cancelling */
#define kCanBufferCancelSw          (uint8)0xFD
#define kCanBufferSend              (uint8)0x01     /* occupied send object */

/* HL return values */
#define kCanFailed                  (uint8)0x00     /* similar to CAN_NOT_OK but value may differ --> converted in HL (LL only use kCan...) */
#define kCanOk                      (uint8)0x01     /* similar to CAN_OK */
#define kCanRequested               (uint8)0x03

#define kCanFalse                   kCanFailed
#define kCanTrue                    kCanOk

#define Can_GetControllerMax()                        Can_GetSizeOfControllerData()
#define Can_GetCanToCanIfChannelMapping(Index)        Can_GetCanIfChannelId((Index))

/* ControllerConfig */
#define Can_GetCanControllerDefaultBaudrate(logCh)    Can_GetCanControllerDefaultBaudrateOfControllerConfig(logCh)
#define Can_GetCanControllerDefaultBaudrateIdx(logCh) Can_GetCanControllerDefaultBaudrateIdxOfControllerConfig(logCh)
#if !defined(Can_GetMailboxRxBasicLengthOfControllerConfig) /* If no Object is available ComStackLib do not generate start-stop index */
# define Can_GetMailboxRxBasicLengthOfControllerConfig(logCh) 0u
# define Can_GetMailboxRxBasicStartIdxOfControllerConfig(logCh) 0u
# define Can_GetMailboxRxBasicEndIdxOfControllerConfig(logCh) 0u
#endif
#define Can_GetRxBasicHandleMax(logCh)                Can_GetMailboxRxBasicLengthOfControllerConfig(logCh)
#define Can_GetRxBasicHandleStart(logCh)              (Can_HwHandleType)Can_GetMailboxRxBasicStartIdxOfControllerConfig(logCh)
#define Can_GetRxBasicHandleStop(logCh)               (Can_HwHandleType)Can_GetMailboxRxBasicEndIdxOfControllerConfig(logCh)
#define Can_GetRxBasicHwStart(logCh)                  Can_GetRxBasicHwStartOfControllerConfig(logCh)
#define Can_GetRxBasicHwStop(logCh)                   Can_GetRxBasicHwStopOfControllerConfig(logCh)
#if !defined(Can_GetMailboxRxFullLengthOfControllerConfig)
# define Can_GetMailboxRxFullLengthOfControllerConfig(logCh) 0u
# define Can_GetMailboxRxFullStartIdxOfControllerConfig(logCh) 0u
# define Can_GetMailboxRxFullEndIdxOfControllerConfig(logCh) 0u
#endif
#define Can_GetRxFullHandleMax(logCh)                 Can_GetMailboxRxFullLengthOfControllerConfig(logCh)
#define Can_GetRxFullHandleStart(logCh)               (Can_HwHandleType)Can_GetMailboxRxFullStartIdxOfControllerConfig(logCh)
#define Can_GetRxFullHandleStop(logCh)                (Can_HwHandleType)Can_GetMailboxRxFullEndIdxOfControllerConfig(logCh)
#define Can_GetRxFullHwStart(logCh)                   Can_GetRxFullHwStartOfControllerConfig(logCh)
#define Can_GetRxFullHwStop(logCh)                    Can_GetRxFullHwStopOfControllerConfig(logCh)
#if !defined(Can_GetMailboxTxBasicLengthOfControllerConfig) /* COV_CAN_GENDATA_FAILURE */
# define Can_GetMailboxTxBasicLengthOfControllerConfig(logCh) 0u
# define Can_GetMailboxTxBasicStartIdxOfControllerConfig(logCh) 0u
# define Can_GetMailboxTxBasicEndIdxOfControllerConfig(logCh) 0u
#endif
#define Can_GetTxBasicHandleMax(logCh)                Can_GetMailboxTxBasicLengthOfControllerConfig(logCh)
#define Can_GetTxBasicHandleStart(logCh)              (Can_HwHandleType)Can_GetMailboxTxBasicStartIdxOfControllerConfig(logCh)
#define Can_GetTxBasicHandleStop(logCh)               (Can_HwHandleType)Can_GetMailboxTxBasicEndIdxOfControllerConfig(logCh)
#define Can_GetTxBasicHwStart(logCh)                  Can_GetTxBasicHwStartOfControllerConfig(logCh)
#define Can_GetTxBasicHwStop(logCh)                   Can_GetTxBasicHwStopOfControllerConfig(logCh)
#if !defined(Can_GetMailboxTxFullLengthOfControllerConfig)
# define Can_GetMailboxTxFullLengthOfControllerConfig(logCh) 0u
# define Can_GetMailboxTxFullStartIdxOfControllerConfig(logCh) 0u
# define Can_GetMailboxTxFullEndIdxOfControllerConfig(logCh) 0u
#endif
#define Can_GetTxFullHandleMax(logCh)                 Can_GetMailboxTxFullLengthOfControllerConfig(logCh)
#define Can_GetTxFullHandleStart(logCh)               (Can_HwHandleType)Can_GetMailboxTxFullStartIdxOfControllerConfig(logCh)
#define Can_GetTxFullHandleStop(logCh)                (Can_HwHandleType)Can_GetMailboxTxFullEndIdxOfControllerConfig(logCh)
#define Can_GetTxFullHwStart(logCh)                   Can_GetTxFullHwStartOfControllerConfig(logCh)
#define Can_GetTxFullHwStop(logCh)                    Can_GetTxFullHwStopOfControllerConfig(logCh)
#if !defined(Can_GetMailboxUnusedLengthOfControllerConfig)  /* COV_CAN_GENDATA_FAILURE */
# define Can_GetMailboxUnusedLengthOfControllerConfig(logCh) 0u
# define Can_GetMailboxUnusedStartIdxOfControllerConfig(logCh) 0u
# define Can_GetMailboxUnusedEndIdxOfControllerConfig(logCh) 0u
#endif
#define Can_GetUnusedHandleMax(logCh)                 Can_GetMailboxUnusedLengthOfControllerConfig(logCh)
#define Can_GetUnusedHandleStart(logCh)               (Can_HwHandleType)Can_GetMailboxUnusedStartIdxOfControllerConfig(logCh)
#define Can_GetUnusedHandleStop(logCh)                (Can_HwHandleType)Can_GetMailboxUnusedEndIdxOfControllerConfig(logCh)
#define Can_GetUnusedHwStart(logCh)                   Can_GetUnusedHwStartOfControllerConfig(logCh)
#define Can_GetUnusedHwStop(logCh)                    Can_GetUnusedHwStopOfControllerConfig(logCh)

/* Mailbox */
/* GetMailboxSize: logical size of mailbox - use LL specific generated data to get hardware object size if needed */
#define Can_GetMailboxSize(htrh)                      Can_GetMailboxSizeOfMailbox(htrh)
#define Can_GetMailboxHwHandle(htrh)                  Can_GetHwHandleOfMailbox(htrh)
#define Can_GetMailboxIDValue(htrh)                   Can_GetIDValueOfMailbox(htrh)
#define Can_GetMailboxType(htrh)                      Can_GetMailboxTypeOfMailbox(htrh)
#define Can_GetMailboxDataLen(htrh)                   Can_GetMaxDataLenOfMailbox(htrh)
#define Can_GetMailboxFdPadding(htrh)                 Can_GetFdPaddingOfMailbox(htrh)
#define Can_GetMailboxController(htrh)                (CanChannelHandle)Can_GetControllerConfigIdxOfMailbox(htrh)
#define Can_GetMailboxActiveSendObject(htrh)          Can_GetActiveSendObjectOfMailbox(htrh)
#define Can_GetMailboxActiveSendData(htrh)            Can_GetActiveSendDataOfMailbox(htrh)
#define Can_GetMailboxMemSecObjIndex(htrh)            Can_GetMemorySectionsIndexOfMailbox(htrh)
#define Can_IsMailboxIndivPolling(htrh)               Can_IsIsIndivPollingOfMailbox(htrh)
#define Can_GetMailboxTxHwFifo(htrh)                  Can_GetTxHwFifoOfMailbox(htrh)

/* MemorySectionInfo */
#define Can_GetMemSecAddress(memSec)                  Can_GetMemoryStartAddressOfMemorySectionInfo(memSec)
#define Can_GetMemSecStartIndex(memSec)               Can_GetMemorySectionStartOfMemorySectionInfo(memSec)

/* MemorySectionObjects */
#define Can_GetMemSecObjHwHandle(memSecObj)           Can_GetHwHandleOfMemorySectionObjects(memSecObj)
#define Can_GetMemSecObjMailboxElement(memSecObj)     Can_GetMailboxElementOfMemorySectionObjects(memSecObj)
#define Can_GetMemSecObjMailboxHandle(memSecObj)      Can_GetMailboxHandleOfMemorySectionObjects(memSecObj)
#define Can_IsMemSecObjIndivPolling(memSecObj)        Can_IsIsIndivPollingOfMemorySectionObjects(memSecObj)

/* VAR */
#define Can_GetLastInitObject(Index)                   Can_GetLastInitObjectOfControllerData(Index)
#define Can_SetLastInitObject(Index, Value)            Can_SetLastInitObjectOfControllerData(Index, Value)
#define Can_GetCanInterruptOldStatus(Index)            Can_GetCanInterruptOldStatusOfControllerData(Index)
#define Can_SetCanInterruptOldStatus(Index, Value)     Can_SetCanInterruptOldStatusOfControllerData(Index, Value)
#define Can_GetCanInterruptCounter(Index)              Can_GetCanInterruptCounterOfControllerData(Index)
#define Can_SetCanInterruptCounter(Index, Value)       Can_SetCanInterruptCounterOfControllerData(Index, Value)
#define Can_IncCanInterruptCounter(Index)              Can_IncCanInterruptCounterOfControllerData(Index)
#define Can_DecCanInterruptCounter(Index)              Can_DecCanInterruptCounterOfControllerData(Index)
#define Can_IsIsWakeup(Index)                          Can_IsIsWakeupOfControllerData(Index)
#define Can_SetIsWakeup(Index, Value)                  Can_SetIsWakeupOfControllerData(Index, Value)
#define Can_IsIsBusOff(Index)                          Can_IsIsBusOffOfControllerData(Index)
#define Can_SetIsBusOff(Index, Value)                  Can_SetIsBusOffOfControllerData(Index, Value)
#define Can_GetBusOffCounter(Index)                    Can_GetBusOffCounterOfControllerData(Index)
#define Can_SetBusOffCounter(Index, Value)             Can_SetBusOffCounterOfControllerData(Index, Value)
#define Can_DecBusOffCounter(Index)                    Can_DecBusOffCounterOfControllerData(Index)
#define Can_GetModeTransitionRequest(Index)            Can_GetModeTransitionRequestOfControllerData(Index)
#define Can_SetModeTransitionRequest(Index, Value)     Can_SetModeTransitionRequestOfControllerData(Index, Value)
#define Can_GetBusOffTransitionRequest(Index)          Can_GetBusOffTransitionRequestOfControllerData(Index)
#define Can_SetBusOffTransitionRequest(Index, Value)   Can_SetBusOffTransitionRequestOfControllerData(Index, Value)
#define Can_GetRamCheckTransitionRequest(Index)        Can_GetRamCheckTransitionRequestOfControllerData(Index)
#define Can_SetRamCheckTransitionRequest(Index, Value) Can_SetRamCheckTransitionRequestOfControllerData(Index, Value)
/* controller states */
#define Can_GetLogStatus(Index)                        Can_GetLogStatusOfControllerData(Index)
#define Can_SetLogStatus(Index, Value)                 Can_SetLogStatusOfControllerData(Index, Value)
#define Can_GetCanLoopTimeout(ch, Index)               (Can_GetLoopTimeoutOfControllerData(ch))[(Index)]
#define Can_GetMirrorModeState(Index)                  Can_GetMirrorModeStateOfControllerData(Index)
#define Can_SetMirrorModeState(Index, Value)           Can_SetMirrorModeStateOfControllerData(Index, Value)
#define Can_GetSilentModeState(Index)                  Can_GetSilentModeStateOfControllerData(Index)
#define Can_SetSilentModeState(Index, Value)           Can_SetSilentModeStateOfControllerData(Index, Value)
/* ActiveSend */
#define Can_GetActiveSendPdu(Index)                    Can_GetPduOfActiveSendObject(Index)
#define Can_SetActiveSendPdu(Index, Value)             Can_SetPduOfActiveSendObject(Index, Value)
#define Can_GetActiveSendState(Index)                  Can_GetStateOfActiveSendObject(Index)
#define Can_SetActiveSendState(Index, Value)           Can_SetStateOfActiveSendObject(Index, Value)
#define Can_GetActiveSendPduInfo(Index)                Can_GetPduInfoOfActiveSendObject(Index)
#define Can_GetActiveSendId(Index)                     (Can_GetPduInfoOfActiveSendObject(Index)).id
#define Can_SetActiveSendId(Index, Value)              (Can_GetPduInfoOfActiveSendObject(Index)).id = (Value)
#define Can_GetActiveSendLength(Index)                 (Can_GetPduInfoOfActiveSendObject(Index)).length
#define Can_SetActiveSendLength(Index, Value)          (Can_GetPduInfoOfActiveSendObject(Index)).length = (Value)
#define Can_GetActiveSendSdu(Index)                    (Can_GetPduInfoOfActiveSendObject(Index)).sdu
#define Can_SetActiveSendSdu(Index, Value)             (Can_GetPduInfoOfActiveSendObject(Index)).sdu = (Value)
#define Can_GetActiveSendSwPduHandle(Index)            (Can_GetPduInfoOfActiveSendObject(Index)).swPduHandle
#define Can_SetActiveSendSwPduHandle(Index, Value)     (Can_GetPduInfoOfActiveSendObject(Index)).swPduHandle = (Value)
/* Use already ComStackLib name #define Can_GetActiveSendData(Index)                   Can_GetActiveSendData(Index) */
/* TxHwFifo */
#define Can_GetTxHwFifoWriteIndex(fifo)                Can_GetWriteIndexOfTxHwFifo(fifo)
#define Can_SetTxHwFifoWriteIndex(fifo, Value)         Can_SetWriteIndexOfTxHwFifo(fifo, Value)
#define Can_IncTxHwFifoWriteIndex(fifo)                Can_IncWriteIndexOfTxHwFifo(fifo)
#define Can_GetTxHwFifoReadIndex(fifo)                 Can_GetReadIndexOfTxHwFifo(fifo)
#define Can_SetTxHwFifoReadIndex(fifo, Value)          Can_SetReadIndexOfTxHwFifo(fifo, Value)
#define Can_IncTxHwFifoReadIndex(fifo)                 Can_IncReadIndexOfTxHwFifo(fifo)
#define Can_GetTxHwFifoFillCount(fifo)                 Can_GetFillCountOfTxHwFifo(fifo)
#define Can_SetTxHwFifoFillCount(fifo, Value)          Can_SetFillCountOfTxHwFifo(fifo, Value)
#define Can_IncTxHwFifoFillCount(fifo)                 Can_IncFillCountOfTxHwFifo(fifo)
#define Can_DecTxHwFifoFillCount(fifo)                 Can_DecFillCountOfTxHwFifo(fifo)

# define Can_GetFDHwChannelIndirection(Index)                              Can_GetFDHwChannelIndirectionOfControllerConfig(Index)
# define Can_GetHwToMbHandle(logCh, Index)                                 Can_GetMemSecObjMailboxHandle(Can_GetMemSecStartIndex(logCh) + (Index))
# define CAN_HL_MB_TX_NORMAL_INDEX                                         CAN_HL_MB_TX_BASIC_STARTINDEX


/***************************************************************************/
/* Default switches                                                        */
/* Automatic define settings, depending on user configuration in can_cfg.h */
/***************************************************************************/
/***************************************************************************/
/*  Safe Check for FlexCAN3                                                */
/***************************************************************************/
# if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
#  if defined (C_ENABLE_WAKEUP_INTERRUPT) || \
      defined (C_ENABLE_GLITCH_FILTER) /* COV_CAN_SAFE_BSW_EXCLUSION_FLEXCAN3 */
#    error "Unsupported Feature activated for SafeBSW"
#  endif
# endif

#define C_HL_DISABLE_OVERRUN_IN_STATUS

#define C_HL_DISABLE_HW_RANGES_FILTER

#define C_HL_ENABLE_IDTYPE_IN_DLC




#define C_HL_DISABLE_DUMMY_FCT_CALL


#define C_HL_DISABLE_TX_MSG_DESTROYED


#define C_HL_DISABLE_CANCEL_IN_HW_TASK

#define C_HL_DISABLE_HW_EXIT_TRANSMIT

#define C_HL_DISABLE_ADJUST_RXHANDLE


#define C_HL_DISABLE_REJECT_UNWANTED_IDTYPE

#define C_HL_DISABLE_REJECT_REMOTE_FRAME

#define C_HL_DISABLE_REJECT_REMOTE_FRAME_FULLCAN

#define C_HL_ENABLE_REJECT_ILLEGAL_DLC

#define C_HL_DISABLE_COPROCESSOR_SUPPORT



#define C_HL_DISABLE_AVOID_REENTRANT_APPLCANCANCELNOTIFICATION

/* Possibility to disable the prototypes of interrupt service routines in the driver header file */

#define C_DISABLE_TX_ACTUAL_MACROS

#define CAN_HL_HW_LAYOUT_TXBASIC_FIRST




#if defined ( C_ENABLE_CAN_FD_USED )
#  define C_ENABLE_CLASSIC_MAILBOX_LAYOUT
#endif

#if !defined( C_ENABLE_CLKSRC_SELECTION ) && !defined( C_DISABLE_CLKSRC_SELECTION ) /* COV_CAN_RAMCHECK_EXTENDED_CLKSRC_COMPATABILITY */
# define C_ENABLE_CLKSRC_SELECTION
#endif

/***************************************************************************/
/* macros                                                                  */
/***************************************************************************/
#define txErrCMask      (vuint32)0x000000FFu
#define rxErrCMask      (vuint32)0x0000FF00u
#define txErrCFastMask  (vuint32)0x00FF0000u
#define rxErrCFastMask  (vuint32)0xFF000000u



/* macros to set DLC and ID in RX-,TX-structures -------------------------- */
/* MK... macros are used by the generation tool to fill the RX and TX structures */
/* In case the IDE bit is located in the ID registers, this bit has to be handled as must match.
   In general, this is done by setting the IDE bit to 0 in the .._MASK_.. macros.
*/

#define MK_RX_RANGE_MASK_IDSTD0(id)   ( MK_STDID0(id) )
#define MK_RX_RANGE_MASK_IDSTD1(id)   ( MK_STDID1(id) )
#define MK_RX_RANGE_MASK_IDSTD2(id)   ( MK_STDID2(id) )
#define MK_RX_RANGE_MASK_IDSTD3(id)   ( MK_STDID3(id) )
#define MK_RX_RANGE_MASK_IDSTD4(id)   ( MK_STDID4(id) )

#define MK_RX_RANGE_CODE_IDSTD0(id)   ( MK_STDID0(id) )
#define MK_RX_RANGE_CODE_IDSTD1(id)   ( MK_STDID1(id) )
#define MK_RX_RANGE_CODE_IDSTD2(id)   ( MK_STDID2(id) )
#define MK_RX_RANGE_CODE_IDSTD3(id)   ( MK_STDID3(id) )
#define MK_RX_RANGE_CODE_IDSTD4(id)   ( MK_STDID4(id) )

#define MK_RX_RANGE_MASK_IDEXT0(id)   ( MK_EXTID0(id))
#define MK_RX_RANGE_MASK_IDEXT1(id)   ( MK_EXTID1(id) )
#define MK_RX_RANGE_MASK_IDEXT2(id)   ( MK_EXTID2(id) )
#define MK_RX_RANGE_MASK_IDEXT3(id)   ( MK_EXTID3(id) )
#define MK_RX_RANGE_MASK_IDEXT4(id)   ( MK_EXTID4(id) )

#define MK_RX_RANGE_CODE_IDEXT0(id)   ( MK_EXTID0(id))
#define MK_RX_RANGE_CODE_IDEXT1(id)   ( MK_EXTID1(id) )
#define MK_RX_RANGE_CODE_IDEXT2(id)   ( MK_EXTID2(id) )
#define MK_RX_RANGE_CODE_IDEXT3(id)   ( MK_EXTID3(id) )
#define MK_RX_RANGE_CODE_IDEXT4(id)   ( MK_EXTID4(id) )


#if defined( C_ENABLE_EXTENDED_ID ) 
# define MK_STDID0(id)           (((id) & 0x07FFUL) << 18)
#else
# define MK_STDID0(id)           (((id) & 0x07FFu) << 2)
#endif
#define MK_STDID1(id)            (id)
#define MK_STDID2(id)            (id)
#define MK_STDID3(id)            (id)
#define MK_STDID4(id)            (id)



#define MK_EXTID0(id)            (((vuint32)(id)) & 0x1FFFFFFFUL)
#define MK_EXTID1(id)            ((id))
#define MK_EXTID2(id)            ((id))
#define MK_EXTID3(id)            ((id))
#define MK_EXTID4(id)            ((id))




# if defined(C_ENABLE_EXTENDED_ID)
#  if defined(C_ENABLE_MIXED_ID)
#   define MK_TX_DLC(dlc)     ((tCanDlc)((vuint8)(dlc) & (vuint8)0x0Fu))
#  else
#   define  MK_TX_DLC(dlc)    ((tCanDlc)(((vuint8)(dlc) & (vuint8)0x0Fu) | (vuint8)kCanIdTypeExt | (vuint8)kCanIdTypeSRR))
#  endif
# else
#  define MK_TX_DLC(dlc)      ((tCanDlc)((vuint8)(dlc) & (vuint8)0x0Fu))
# endif

/* extract  DLC from register format to logical format */
#define XT_TX_DLC(dlc)       ((vuint8)((vuint8)(dlc) & (vuint8)0x0Fu))


/* The macros CanRxActualIdRawx() have to provide the register context of the ID registers.
   It is not necessary to mask any bits. These macros are for internal use only and masking
   will be done in can_hls.c
*/
#if defined( C_ENABLE_EXTENDED_ID )
# define CanRxActualIdRaw0(rxStruct)      ((vuint32)(((tCanRxMsgBufferPtr)((rxStruct)->pChipMsgObj))->msgID))
# define CanRxActualIdRaw1(rxStruct)   0
# define CanRxActualIdRaw2(rxStruct)   0
# define CanRxActualIdRaw3(rxStruct)   0
# define CanRxActualIdRaw4(rxStruct)   0
#else
# define CanRxActualIdRaw0(rxStruct)      ((vuint16)((((tCanRxMsgBufferPtr)((rxStruct)->pChipMsgObj))->msgID) >> 16) & (vuint16)0x1FFFu)
# define CanRxActualIdRaw1(rxStruct)    0
# define CanRxActualIdRaw2(rxStruct)    0
# define CanRxActualIdRaw3(rxStruct)    0
# define CanRxActualIdRaw4(rxStruct)    0
#endif


/* Macros for CAN message access within ApplCanMsgReceived() or PreCopy() function */
#if defined( C_ENABLE_EXTENDED_ID )
# define CanRxActualIdExtHi(rxStruct)        ((vuint8)((((tCanRxMsgBufferPtr)((rxStruct)->pChipMsgObj))->msgID) >> 24) & (vuint8)0x1Fu)
# define CanRxActualIdExtMidHi(rxStruct)     ((vuint8)((((tCanRxMsgBufferPtr)((rxStruct)->pChipMsgObj))->msgID) >> 16) & (vuint8)0xFFu)
# define CanRxActualIdExtMidLo(rxStruct)     ((vuint8)((((tCanRxMsgBufferPtr)((rxStruct)->pChipMsgObj))->msgID) >> 8) & (vuint8)0xFFu)
# define CanRxActualIdExtLo(rxStruct)        ((vuint8)(((tCanRxMsgBufferPtr)((rxStruct)->pChipMsgObj))->msgID) & (vuint8)0xFFu)
#endif

#if defined( C_ENABLE_EXTENDED_ID ) 
# define XT_ID(id)         ((vuint16)(((vuint32)(id) & (vuint32)0x1FFC0000u) >> 18))
#else
# define XT_ID(id)         ((vuint16)(((vuint16)(id) & 0x1FFCu) >> 2))
#endif
#define XT_EXTID(id)       ((vuint32)((vuint32)(id) & (vuint32)0x1FFFFFFFu))

#define CanRxActualExtId(rxStruct)        (XT_EXTID(CanRxActualIdRaw0(rxStruct)))
#define CanRxActualStdId(rxStruct)        (XT_ID(CanRxActualIdRaw0(rxStruct)))

#define CanRxActualData(rxStruct, i)       ((vuint8)((rxStruct)->pChipData[(i)]))
#define CanRxActualDLC(rxStruct)          CAN_DLC2LEN((vuint8)(((tCanRxMsgBufferPtr)((rxStruct)->pChipMsgObj))->control) & (vuint8)0x0F)
#define CanRxActualIdType(rxStruct)       ((vuint8)(((tCanRxMsgBufferPtr)((rxStruct)->pChipMsgObj))->control) & (vuint8)kCanIdTypeExt)
#define CanRxActualFdType(rxStruct)       (((tCanRxMsgBufferPtr)((rxStruct)->pChipMsgObj))->control & kCanFdTypeFd)

/* support reading the error counters */
#if defined( C_SINGLE_RECEIVE_CHANNEL )
# if defined( C_ENABLE_UPDATE_BASE_ADDRESS )
#  define CanRxActualErrorCounter()   ((vuint8)(((((tFlexCANPtr)canLL_VirtualPtrField[0])->ecr) & rxErrCMask) >> 8))
#  define CanTxActualErrorCounter()   ((vuint8)((((tFlexCANPtr)canLL_VirtualPtrField[0])->ecr) & txErrCMask))
# else
#  define CanRxActualErrorCounter()   ((vuint8)(((pFlexCAN(0)->ecr) & rxErrCMask) >> 8))
#  define CanTxActualErrorCounter()   ((vuint8)((pFlexCAN(0)->ecr) & txErrCMask))
# endif
#else
# if defined( C_ENABLE_UPDATE_BASE_ADDRESS )
#  define CanRxActualErrorCounter(x)  ((vuint8)(((((tFlexCANPtr)canLL_VirtualPtrField[(x)])->ecr) & rxErrCMask) >> 8))
#  define CanTxActualErrorCounter(x)  ((vuint8)((((tFlexCANPtr)canLL_VirtualPtrField[(x)])->ecr) & txErrCMask))
# else
#  define CanRxActualErrorCounter(x)  ((vuint8)(((pFlexCAN(x)->ecr) & rxErrCMask) >> 8))
#  define CanTxActualErrorCounter(x)  ((vuint8)((pFlexCAN(x)->ecr) & txErrCMask))
# endif
#endif

/* Macros for CAN message access within GenericConfirmation() function */
#if defined( C_ENABLE_EXTENDED_ID )
# define CanTxActualIdRaw0(txStruct)      ((vuint32)(((tCanMsgObjPtr)((txStruct)->pChipMsgObj))->msgID))
#else
# define CanTxActualIdRaw0(txStruct)      ((vuint16)((((tCanMsgObjPtr)((txStruct)->pChipMsgObj))->msgID) >> 16) & (vuint16)0x1FFFu)
#endif /* C_ENABLE_EXTENDED_ID */

#define CanTxActualStdId(txStruct)        (XT_ID(CanTxActualIdRaw0(txStruct)))
#define CanTxActualExtId(txStruct)        (XT_EXTID(CanTxActualIdRaw0(txStruct)))
#define CanTxActualDLC(txStruct)          CAN_DLC2LEN((vuint8)(((tCanMsgObjPtr)((txStruct)->pChipMsgObj))->control) & (vuint8)0x0Fu)
#define CanTxActualIdType(txStruct)       ((vuint8)(((tCanMsgObjPtr)((txStruct)->pChipMsgObj))->control) & (vuint8)kCanIdTypeExt)
#define CanTxActualData(rxStruct, i)       ((vuint8)((txStruct)->pChipData[(i)]))
#define CanTxActualFdType(txStruct)       (((tCanMsgObjPtr)((txStruct)->pChipMsgObj))->control & kCanFdTypeFd)

/* Macros for CAN message access within PreTransmit() function */

#if defined( C_ENABLE_EXTENDED_ID )
# define CanTxWriteActId(txStruct, id)       (((tCanMsgObjPtr)((txStruct).pChipMsgObj))->msgID) = MK_STDID0(id); \
                                            (((tCanMsgObjPtr)((txStruct).pChipMsgObj))->control) &= (vuint16)0xFF0Fu

# define CanTxWriteActFdId(txStruct, id)     (((tCanMsgObjPtr)((txStruct).pChipMsgObj))->msgID) = MK_STDID0(id); \
                                            (((tCanMsgObjPtr)((txStruct).pChipMsgObj))->control)  |= (vuint16)kCanFdTypeFd | (vuint16)kCanFdBrsTypeTrue; \
                                            (((tCanMsgObjPtr)((txStruct).pChipMsgObj))->control) &= (vuint16)0xFF0Fu

# define CanTxWriteActExtId(txStruct, id)    (((tCanMsgObjPtr)((txStruct).pChipMsgObj))->msgID) = MK_EXTID0(id); \
                                            (((tCanMsgObjPtr)((txStruct).pChipMsgObj))->control) |= (vuint16)kCanIdTypeExt

# define CanTxWriteActFdExtId(txStruct, id)  (((tCanMsgObjPtr)((txStruct).pChipMsgObj))->msgID) = MK_STDID0(id); \
                                            (((tCanMsgObjPtr)((txStruct).pChipMsgObj))->control)  |= (vuint16)kCanIdTypeExt | (vuint16)kCanFdTypeFd | (vuint16)kCanFdBrsTypeTrue;
#else
# define CanTxWriteActId(txStruct, id)       (((tCanMsgObjPtr)((txStruct).pChipMsgObj))->msgID) = ((((tCanMsgObjPtr)((txStruct).pChipMsgObj))->msgID) & 0x0000FFFFu) | ((vuint32)MK_STDID0(id) << 16); \
                                            (((tCanMsgObjPtr)((txStruct).pChipMsgObj))->control) &= (vuint16)0xFF0Fu

#  define CanTxWriteActFdId(txStruct, id)    (((tCanMsgObjPtr)((txStruct).pChipMsgObj))->msgID) = ((((tCanMsgObjPtr)((txStruct).pChipMsgObj))->msgID) & 0x0000FFFFu) | ((vuint32)MK_STDID0(id) << 16); \
                                            (((tCanMsgObjPtr)((txStruct).pChipMsgObj))->control)  |= (vuint16)kCanFdTypeFd | (vuint16)kCanFdBrsTypeTrue; \
                                            (((tCanMsgObjPtr)((txStruct).pChipMsgObj))->control) &= (vuint16)0xFF0Fu
#endif
#define CanTxWriteActDLC(txStruct, dlc)     (((tCanMsgObjPtr)((txStruct).pChipMsgObj))->control) &= (vuint8)kCanIdTypeExt; \
                                            (((tCanMsgObjPtr)((txStruct).pChipMsgObj))->control) |= ((vuint8)(dlc) & (vuint8)0x0Fu)


/* Macros to fill variables of the type tCanMsgTransmitStruct */

/* macros for buffer access */
#define StartRxReadSync()          (VStdSuspendAllInterrupts())
#define EndRxReadSync()            (VStdResumeAllInterrupts())

#define StartRxWriteSync()         (VStdSuspendAllInterrupts())
#define EndRxWriteSync()           (VStdResumeAllInterrupts())

#define StartTxReadSync()
#define EndTxReadSync()

#define StartTxWriteSync()         (VStdSuspendAllInterrupts())
#define EndTxWriteSync()           (VStdResumeAllInterrupts())

#define StartRxWriteCANSync()
#define EndRxWriteCANSync()

#define StartRxReadCANSync()
#define EndRxReadCANSync()

#define StartRxFullCANReadSync(Obj)  (VStdSuspendAllInterrupts())
#define EndRxFullCANReadSync(Obj)    (VStdResumeAllInterrupts())

#define StartRxFullCANWriteSync(obj) (VStdSuspendAllInterrupts())
#define EndRxFullCANWriteSync(obj)   (VStdResumeAllInterrupts())

/* macros for flag access */
#define CanStartFlagWriteSync()    (VStdSuspendAllInterrupts())
#define CanEndFlagWriteSync()      (VStdResumeAllInterrupts())

/* macros to copy data bytes to unint32 */
#define CanCopyDataBytes2Uint32(dst, src) \
            (dst)[0] = (((vuint32)((src)[0])) << 24) | \
                       (((vuint32)((src)[1])) << 16) | \
                       (((vuint32)((src)[2])) << 8) | \
                       ((vuint32)((src)[3])); \
            (dst)[1] = (((vuint32)((src)[4])) << 24) | \
                       (((vuint32)((src)[5])) << 16) | \
                       (((vuint32)((src)[6])) << 8) | \
                       ((vuint32)((src)[7]));

#define CanCopyFDDataBytes2Uint32(dst, src) \
            (dst) = (((vuint32)((src)[0])) << 24) | \
                    (((vuint32)((src)[1])) << 16) | \
                    (((vuint32)((src)[2])) << 8) | \
                    ((vuint32)((src)[3]));

#define CanAdd1FDByte2Uint32(dst, src) \
            (dst) =  (((dst) << 8)); \
            (dst) |= ((vuint32)((src)));

#define CanCopyFDPadding2Uint32(dst, src) \
            (dst) = (((vuint32)((src))) << 24) | \
                    (((vuint32)((src))) << 16) | \
                    (((vuint32)((src))) << 8) | \
                    ((vuint32)((src)));


#define CAN_HL_MIN(x, y) (((x)>(y)) ? (y) : (x)) /* COV_CAN_GENDATA_FAILURE */
#define CAN_HL_MAX(x, y) (((x)<(y)) ? (y) : (x)) /* COV_CAN_GENDATA_FAILURE */

/***************************************************************************************************/
/* Macros for dummy statements */
#if !defined(CAN_DUMMY_STATEMENT) /* COV_CAN_COMPATIBILITY */
# if defined(V_ENABLE_USE_DUMMY_STATEMENT) /* COV_CAN_COMPATIBILITY */
#  define CAN_DUMMY_STATEMENT(x) (x) = (x) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# else
#  define CAN_DUMMY_STATEMENT(x)
# endif
#endif
#if !defined(CAN_DUMMY_STATEMENT_CONST) /* COV_CAN_COMPATIBILITY */
# if defined(V_ENABLE_USE_DUMMY_STATEMENT) /* COV_CAN_COMPATIBILITY */
#  define CAN_DUMMY_STATEMENT_CONST(x) (void)(x)
# else
#  define CAN_DUMMY_STATEMENT_CONST(x)
# endif
#endif

/***************************************************************************************************/
/* Macros for DET and assertions */
#if (CAN_DEV_ERROR_REPORT == STD_ON) /* \trace SPEC-1404, SPEC-1696 */
/* \trace SPEC-1725, SPEC-1403, SPEC-1568 */
# define Can_CallDetReportError(api, err) ((void) Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, (api), (err)))
# define assertHardware(a, b, c)  if (!(a)) {Can_CallDetReportError(CAN_HW_ACCESS_ID, (c));}
# define assertInternal(a, b, c)  if (!(a)) {Can_CallDetReportError(CAN_HW_ACCESS_ID, (c));}
# define assertUser(a, b, c)      if (!(a)) {Can_CallDetReportError(CAN_HW_ACCESS_ID, (c));}
# define assertGen(a, b, c)       if (!(a)) {Can_CallDetReportError(CAN_HW_ACCESS_ID, (c));}
# define C_ENABLE_HARDWARE_CHECK
# define C_ENABLE_INTERNAL_CHECK
# define C_ENABLE_USER_CHECK
# define C_ENABLE_GEN_CHECK
#else
# define Can_CallDetReportError(api, err)
# define assertHardware(a, b, c)
# define assertInternal(a, b, c)
# define assertUser(a, b, c)
# define assertGen(a, b, c)
#endif

/***************************************************************************************************/
/* Macros for Critical Area 0 abstraction */

#define CanDeclareGlobalInterruptOldStatus
/* CAN_EXCLUSIVE_AREA_0 called only by LL code */
#define CanSingleGlobalInterruptDisable()     SchM_Enter_Can_CAN_EXCLUSIVE_AREA_0()
#define CanSingleGlobalInterruptRestore()     SchM_Exit_Can_CAN_EXCLUSIVE_AREA_0()
#define CanGlobalInterruptDisable()           SchM_Enter_Can_CAN_EXCLUSIVE_AREA_0()
#define CanGlobalInterruptRestore()           SchM_Exit_Can_CAN_EXCLUSIVE_AREA_0()
#define CanNestedGlobalInterruptDisable()     SchM_Enter_Can_CAN_EXCLUSIVE_AREA_0()
#define CanNestedGlobalInterruptRestore()     SchM_Exit_Can_CAN_EXCLUSIVE_AREA_0()

/***************************************************************************************************/
/* Macros for LL-HLL compatibility */

/***************************************************************************************************/
/* Macros for ProtectedMode / PeripheralAccess */
# if defined ( C_ENABLE_USER_MODE_OS )
#  define CAN_WRITE_PROTECTED_REG8(area, regAdr, val)         osWritePeripheral8((area), (uint32)(regAdr), (val))
#  define CAN_WRITE_PROTECTED_REG16(area, regAdr, val)        osWritePeripheral16((area), (uint32)(regAdr), (val))
#  define CAN_WRITE_PROTECTED_REG32(area, regAdr, val)        osWritePeripheral32((area), (uint32)(regAdr), (val))
#  define CAN_WRITE_PROTECTED_REG8_RESET(area, regAdr, bits)  osModifyPeripheral8((area), (uint32)(regAdr), (uint8)~(bits), (uint8)0x00u)
#  define CAN_WRITE_PROTECTED_REG16_RESET(area, regAdr, bits) osModifyPeripheral16((area), (uint32)(regAdr), (uint16)~(bits), (uint16)0x0000u)
#  define CAN_WRITE_PROTECTED_REG32_RESET(area, regAdr, bits) osModifyPeripheral32((area), (uint32)(regAdr), (uint32)~(bits), (uint32)0x00000000UL)
#  define CAN_WRITE_PROTECTED_REG8_SET(area, regAdr, bits)    osModifyPeripheral8((area), (uint32)(regAdr), (uint8)0xFFu, (bits))
#  define CAN_WRITE_PROTECTED_REG16_SET(area, regAdr, bits)   osModifyPeripheral16((area), (uint32)(regAdr), (uint16)0xFFFFu, (bits))
#  define CAN_WRITE_PROTECTED_REG32_SET(area, regAdr, bits)   osModifyPeripheral32((area), (uint32)(regAdr), (uint32)0xFFFFFFFFUL, (bits))
#  define CAN_READ_PROTECTED_REG8(area, regAdr)               osReadPeripheral8((area), (uint32)(regAdr))
#  define CAN_READ_PROTECTED_REG16(area, regAdr)              osReadPeripheral16((area), (uint32)(regAdr))
#  define CAN_READ_PROTECTED_REG32(area, regAdr)              osReadPeripheral32((area), (uint32)(regAdr))
# endif
# if defined ( C_ENABLE_USER_MODE_APPL )
#  define CAN_WRITE_PROTECTED_REG8(area, regAdr, val)         ApplCanWriteProtectedRegister8((regAdr), (uint8)0xFFu, (val))
#  define CAN_WRITE_PROTECTED_REG16(area, regAdr, val)        ApplCanWriteProtectedRegister16((regAdr), (uint16)0xFFFFu, (val))
#  define CAN_WRITE_PROTECTED_REG32(area, regAdr, val)        ApplCanWriteProtectedRegister32((regAdr), (uint32)0xFFFFFFFFUL, (val))
#  define CAN_WRITE_PROTECTED_REG8_RESET(area, regAdr, bits)  ApplCanWriteProtectedRegister8((regAdr), (bits), (uint8)0x00u)
#  define CAN_WRITE_PROTECTED_REG16_RESET(area, regAdr, bits) ApplCanWriteProtectedRegister16((regAdr), (bits), (uint16)0x0000u)
#  define CAN_WRITE_PROTECTED_REG32_RESET(area, regAdr, bits) ApplCanWriteProtectedRegister32((regAdr), (bits), (uint32)0x00000000UL)
#  define CAN_WRITE_PROTECTED_REG8_SET(area, regAdr, bits)    ApplCanWriteProtectedRegister8((regAdr), (bits), (bits))
#  define CAN_WRITE_PROTECTED_REG16_SET(area, regAdr, bits)   ApplCanWriteProtectedRegister16((regAdr), (bits), (bits))
#  define CAN_WRITE_PROTECTED_REG32_SET(area, regAdr, bits)   ApplCanWriteProtectedRegister32((regAdr), (bits), (bits))
#  define CAN_READ_PROTECTED_REG8(area, regAdr)               ApplCanReadProtectedRegister8((regAdr))
#  define CAN_READ_PROTECTED_REG16(area, regAdr)              ApplCanReadProtectedRegister16((regAdr))
#  define CAN_READ_PROTECTED_REG32(area, regAdr)              ApplCanReadProtectedRegister32((regAdr))
# endif
# if !defined(C_ENABLE_USER_MODE_OS) && !defined(C_ENABLE_USER_MODE_APPL)
#  define CAN_WRITE_PROTECTED_REG8(area, regAdr, val)         *(regAdr) = (val)
#  define CAN_WRITE_PROTECTED_REG16(area, regAdr, val)        *(regAdr) = (val)
#  define CAN_WRITE_PROTECTED_REG32(area, regAdr, val)        *(regAdr) = (val)
#  define CAN_WRITE_PROTECTED_REG8_RESET(area, regAdr, bits)  *(regAdr) &= (uint8)~(bits)
#  define CAN_WRITE_PROTECTED_REG16_RESET(area, regAdr, bits) *(regAdr) &= (uint16)~(bits)
#  define CAN_WRITE_PROTECTED_REG32_RESET(area, regAdr, bits) *(regAdr) &= (uint32)~(bits)
#  define CAN_WRITE_PROTECTED_REG8_SET(area, regAdr, bits)    *(regAdr) |= (bits)
#  define CAN_WRITE_PROTECTED_REG16_SET(area, regAdr, bits)   *(regAdr) |= (bits)
#  define CAN_WRITE_PROTECTED_REG32_SET(area, regAdr, bits)   *(regAdr) |= (bits)
#  define CAN_READ_PROTECTED_REG8(area, regAdr)               *(regAdr)
#  define CAN_READ_PROTECTED_REG16(area, regAdr)              *(regAdr)
#  define CAN_READ_PROTECTED_REG32(area, regAdr)              *(regAdr)
# endif

/***************************************************************************/
/* CAN-Hardware Data Definitions                                           */
/***************************************************************************/

/***************************************************************************/
/* Special switches need by CAN driver                                     */
/***************************************************************************/

/***************************************************************************/
/* Defines / data types / structures / unions                              */
/***************************************************************************/
# define kCanNumberOfUsedCanRxIdTables 1
# define kCanNumberOfUsedCanTxIdTables 1
/* Define CAN Chip hardware; segment must be located in locator file    */
/* register layout of the can chip                                      */
/* Structure describing CAN receive buffer. */

#if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
# if( kCanNumberOfUsedCanRxIdTables > 4 ) /* COV_CAN_COMPATIBILITY */
#  define SET_PARASTRUCT_IDRAW_RX_STD(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_STDID0(id); \
                                   (paraStruct)->idRaw1 = MK_STDID1(id); \
                                   (paraStruct)->idRaw2 = MK_STDID2(id); \
                                   (paraStruct)->idRaw3 = MK_STDID3(id); \
                                   (paraStruct)->idRaw4 = MK_STDID4(id)
#  define SET_PARASTRUCT_IDRAW_RX_EXT(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_EXTID0(id); \
                                   (paraStruct)->idRaw1 = MK_EXTID1(id); \
                                   (paraStruct)->idRaw2 = MK_EXTID2(id); \
                                   (paraStruct)->idRaw3 = MK_EXTID3(id); \
                                   (paraStruct)->idRaw4 = MK_EXTID4(id)
# elif ( kCanNumberOfUsedCanRxIdTables > 3 ) /* COV_CAN_COMPATIBILITY */
#  define SET_PARASTRUCT_IDRAW_RX_STD(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_STDID0(id); \
                                   (paraStruct)->idRaw1 = MK_STDID1(id); \
                                   (paraStruct)->idRaw2 = MK_STDID2(id); \
                                   (paraStruct)->idRaw3 = MK_STDID3(id)
#  define SET_PARASTRUCT_IDRAW_RX_EXT(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_EXTID0(id); \
                                   (paraStruct)->idRaw1 = MK_EXTID1(id); \
                                   (paraStruct)->idRaw2 = MK_EXTID2(id); \
                                   (paraStruct)->idRaw3 = MK_EXTID3(id)
# elif ( kCanNumberOfUsedCanRxIdTables > 2 ) /* COV_CAN_COMPATIBILITY */
#  define SET_PARASTRUCT_IDRAW_RX_STD(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_STDID0(id); \
                                   (paraStruct)->idRaw1 = MK_STDID1(id); \
                                   (paraStruct)->idRaw2 = MK_STDID2(id)
#  define SET_PARASTRUCT_IDRAW_RX_EXT(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_EXTID0(id); \
                                   (paraStruct)->idRaw1 = MK_EXTID1(id); \
                                   (paraStruct)->idRaw2 = MK_EXTID2(id)
# elif ( kCanNumberOfUsedCanRxIdTables > 1 ) /* COV_CAN_COMPATIBILITY */
#  define SET_PARASTRUCT_IDRAW_RX_STD(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_STDID0(id); \
                                   (paraStruct)->idRaw1 = MK_STDID1(id)
#  define SET_PARASTRUCT_IDRAW_RX_EXT(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_EXTID0(id); \
                                   (paraStruct)->idRaw1 = MK_EXTID1(id)
# else
#  define SET_PARASTRUCT_IDRAW_RX_STD(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_STDID0(id)
#  define SET_PARASTRUCT_IDRAW_RX_EXT(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_EXTID0(id)
# endif
#endif

#if( kCanNumberOfUsedCanTxIdTables > 4 ) /* COV_CAN_COMPATIBILITY */
# define SET_PARASTRUCT_IDRAW_TX_STD(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_STDID0(id); \
                                   (paraStruct)->idRaw1 = MK_STDID1(id); \
                                   (paraStruct)->idRaw2 = MK_STDID2(id); \
                                   (paraStruct)->idRaw3 = MK_STDID3(id); \
                                   (paraStruct)->idRaw4 = MK_STDID4(id)
# define SET_PARASTRUCT_IDRAW_TX_EXT(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_EXTID0(id); \
                                   (paraStruct)->idRaw1 = MK_EXTID1(id); \
                                   (paraStruct)->idRaw2 = MK_EXTID2(id); \
                                   (paraStruct)->idRaw3 = MK_EXTID3(id); \
                                   (paraStruct)->idRaw4 = MK_EXTID4(id)
#elif ( kCanNumberOfUsedCanTxIdTables > 3 ) /* COV_CAN_COMPATIBILITY */
# define SET_PARASTRUCT_IDRAW_TX_STD(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_STDID0(id); \
                                   (paraStruct)->idRaw1 = MK_STDID1(id); \
                                   (paraStruct)->idRaw2 = MK_STDID2(id); \
                                   (paraStruct)->idRaw3 = MK_STDID3(id)
# define SET_PARASTRUCT_IDRAW_TX_EXT(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_EXTID0(id); \
                                   (paraStruct)->idRaw1 = MK_EXTID1(id); \
                                   (paraStruct)->idRaw2 = MK_EXTID2(id); \
                                   (paraStruct)->idRaw3 = MK_EXTID3(id)
#elif ( kCanNumberOfUsedCanTxIdTables > 2 ) /* COV_CAN_COMPATIBILITY */
# define SET_PARASTRUCT_IDRAW_TX_STD(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_STDID0(id); \
                                   (paraStruct)->idRaw1 = MK_STDID1(id); \
                                   (paraStruct)->idRaw2 = MK_STDID2(id)
# define SET_PARASTRUCT_IDRAW_TX_EXT(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_EXTID0(id); \
                                   (paraStruct)->idRaw1 = MK_EXTID1(id); \
                                   (paraStruct)->idRaw2 = MK_EXTID2(id)
#elif ( kCanNumberOfUsedCanTxIdTables > 1 ) /* COV_CAN_COMPATIBILITY */
# define SET_PARASTRUCT_IDRAW_TX_STD(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_STDID0(id); \
                                   (paraStruct)->idRaw1 = MK_STDID1(id)
# define SET_PARASTRUCT_IDRAW_TX_EXT(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_EXTID0(id); \
                                   (paraStruct)->idRaw1 = MK_EXTID1(id)
#else
# define SET_PARASTRUCT_IDRAW_TX_STD(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_STDID0(id)
# define SET_PARASTRUCT_IDRAW_TX_EXT(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_EXTID0(id)
#endif

/***************************************************************************/
/* Core - LowLevel API                                                     */
/***************************************************************************/
typedef struct sCanRxInfoStruct
{
  CanChipMsgPtr     pChipMsgObj;
  CanChipDataPtr    pChipData;
  CanObjectHandle   localMailboxHandle; 
  Can_IdType               localId; 
  uint8                    localDlc;
  /* LL specific part */
} tCanRxInfoStruct;
V_DEF_P2VAR_TYPE(V_NONE, tCanRxInfoStruct, VAR_NOINIT) CanRxInfoStructPtr;

typedef struct sCanTxConfInfoStruct
{
  CanChipMsgPtr     pChipMsgObj;
  CanChipDataPtr    pChipData;
  /* LL specific part */
} tCanTxConfInfoStruct;
V_DEF_P2VAR_TYPE(V_NONE, tCanTxConfInfoStruct, VAR_NOINIT) CanTxConfInfoStructPtr;

typedef struct sCanInitParaStruct
{
  CanInitHandle     initObject;
  CanObjectHandle   mailboxHandle;
  CanObjectHandle   hwObjHandle;
#if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
  tCanRxId0                idRaw0;
# if( kCanNumberOfUsedCanRxIdTables > 1 ) /* COV_CAN_COMPATIBILITY */
  tCanRxId1                idRaw1;
# endif
# if( kCanNumberOfUsedCanRxIdTables > 2 ) /* COV_CAN_COMPATIBILITY */
  tCanRxId2                idRaw2;
# endif
# if( kCanNumberOfUsedCanRxIdTables > 3 ) /* COV_CAN_COMPATIBILITY */
  tCanRxId3                idRaw3;
# endif
# if( kCanNumberOfUsedCanRxIdTables > 4 ) /* COV_CAN_COMPATIBILITY */
  tCanRxId4                idRaw4;
# endif
  tCanIdType               idType;
#endif
#if defined(C_ENABLE_CAN_RAM_CHECK)
  uint8                    doRamCheck;
# if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
  uint8                    isChRamCheckFail;
# endif
#endif
  uint8                    isInitOk;
  /* LL specific part */
} tCanInitParaStruct;
V_DEF_P2VAR_TYPE(V_NONE, tCanInitParaStruct, VAR_NOINIT) CanInitParaStructPtr;

#define TxDataPtr Can_SduPtrType /* CBD compatibility */
typedef struct sCanTxTransmissionParaStruct
{
  /* logical formats */
  CanObjectHandle   mailboxHandle;
  CanObjectHandle   mailboxElement; /* logical index within the mailbox for muxTx or FIFO element */
  CanObjectHandle   hwObjHandle;    /* set to the initial hwHandle by core but has to be modified by LL in case of muxTx or FIFO */
  CanObjectHandle   activeSendObject; /* index of the logical Tx mailbox (Tx * Element) */
  tCanTxId0                idRaw0;
#if( kCanNumberOfUsedCanTxIdTables > 1 ) /* COV_CAN_COMPATIBILITY */
  tCanTxId1                idRaw1;
#endif
#if( kCanNumberOfUsedCanTxIdTables > 2 ) /* COV_CAN_COMPATIBILITY */
  tCanTxId2                idRaw2;
#endif
#if( kCanNumberOfUsedCanTxIdTables > 3 ) /* COV_CAN_COMPATIBILITY */
  tCanTxId3                idRaw3;
#endif
#if( kCanNumberOfUsedCanTxIdTables > 4 ) /* COV_CAN_COMPATIBILITY */
  tCanTxId4                idRaw4;
#endif
#if defined( C_ENABLE_MIXED_ID ) 
  tCanIdType               idType;
#endif
  tCanDlc                  dlcRaw;
  TxDataPtr                CanMemCopySrcPtr;
#if defined( C_ENABLE_CAN_FD_USED )
  tCanFdType               fdType;
  tCanFdBrsType            fdBrsType;
  uint8                    messageLen;
  uint8                    frameLen;
  uint8                    paddingVal;
#endif
  Can_PduType              pdu;
  /* LL specific part */
} tCanTxTransmissionParaStruct;
V_DEF_P2VAR_TYPE(V_NONE, tCanTxTransmissionParaStruct, VAR_NOINIT) CanTxTransmissionParaStructPtr;

typedef struct sCanRxBasicParaStruct
{
  CanObjectHandle   mailboxHandle;
  CanObjectHandle   hwObjHandle;
#if defined( C_ENABLE_OVERRUN )
  uint8                    isOverrun;
#endif
  tCanRxInfoStruct         rxStruct;
  /* LL specific part */
} tCanRxBasicParaStruct;
V_DEF_P2VAR_TYPE(V_NONE, tCanRxBasicParaStruct, VAR_NOINIT) CanRxBasicParaStructPtr;

typedef struct sCanRxFullParaStruct
{
  CanObjectHandle   mailboxHandle;
  CanObjectHandle   hwObjHandle;
#if defined( C_ENABLE_FULLCAN_OVERRUN )
  uint8                    isOverrun;
#endif
  tCanRxInfoStruct         rxStruct;
  /* LL specific part */
} tCanRxFullParaStruct;
V_DEF_P2VAR_TYPE(V_NONE, tCanRxFullParaStruct, VAR_NOINIT) CanRxFullParaStructPtr;

#if defined( C_ENABLE_CANCEL_IN_HW ) || defined( C_ENABLE_CANCEL_SUPPORT_API )
typedef struct
{
  CanObjectHandle   mailboxHandle;
  CanObjectHandle   mailboxElement; /* logical index within the mailbox for muxTx or FIFO element */
  CanObjectHandle   hwObjHandle;    /* set to the initial hwHandle by core but has to be modified by LL in case of muxTx or FIFO */
  CanObjectHandle   activeSendObject; /* index of the logical mailbox + muxTx or FIFO element 0..n */
  CanTransmitHandle   canHandleCurTxObj;
} tCanTxCancellationParaStruct;
V_DEF_P2VAR_TYPE(V_NONE, tCanTxCancellationParaStruct, VAR_NOINIT) CanTxCancellationParaStructPtr;
#endif

typedef struct
{
  CanObjectHandle   mailboxHandle;
  CanObjectHandle   mailboxElement; /* logical index within the mailbox for muxTx or FIFO element */
  CanObjectHandle   hwObjHandle;    /* set to the initial hwHandle by core but has to be modified by LL in case of muxTx or FIFO */
  CanObjectHandle   activeSendObject; /* index of the logical mailbox + muxTx or FIFO element 0..n */
#if defined(CAN_ENABLE_GENERIC_CONFIRMATION_API2)
  CanTxConfInfoStructPtr   txStructConf;
#endif
  #if defined( C_CPUTYPE_LITTLEENDIAN ) /* COV_CAN_FLEXCAN3_DERIVATIVE_LITTLE_ENDIAN */
  # if defined(CAN_ENABLE_GENERIC_CONFIRMATION_API2)
  #  if defined ( C_ENABLE_CAN_FD_FULL )
  vuint32 canDataBuffer[16];
  #  else
  vuint32 canDataBuffer[2];
  #  endif
  # endif
  #endif
} tCanTxConfirmationParaStruct;
V_DEF_P2VAR_TYPE(V_NONE, tCanTxConfirmationParaStruct, VAR_NOINIT) CanTxConfirmationParaStructPtr;

typedef struct sCanTaskParaStruct
{
  CanObjectHandle mailboxHandle;
  CanObjectHandle hwObjHandle;
  /* LL specific part */
} tCanTaskParaStruct;
V_DEF_P2VAR_TYPE(V_NONE, tCanTaskParaStruct, VAR_NOINIT) CanTaskParaStructPtr;
    
/***************************************************************************/
/* module global variable declaration                                      */
/***************************************************************************/

/***************************************************************************/
/* External Declarations                                                   */
/***************************************************************************/
#define CAN_START_SEC_VAR_NOINIT_UNSPECIFIED  /*---------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define CAN_STOP_SEC_VAR_NOINIT_UNSPECIFIED  /*----------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/***************************************************************************/
/* local function prototypes (only internal usage)                         */
/***************************************************************************/
#define CAN_START_SEC_STATIC_CODE  /*--------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */



/************************************************************************************************************
 *  CanLL_InitMailboxWriteReg16()
 ***********************************************************************************************************/
/*! \brief         Write value and do RamCheck inside InitMailbox functions
 *  \details       Write the value of the hardware mailbox or controller register and read back for RamCheck.
 *                 set initPara->isChRamCheckFail or initPara->isMbRamCheckFail in case of an HW issue to deactivate hardware.
 *  \param[in]     Controller       CAN controller.
 *                                  (only if not using "Optimize for one controller")
 *  \param[in]     regPtr           valid pointer to Register to be written.
 *  \param[in]     value            value to be written.
 *  \param[in]     readMask         mask to check the read back value.
 *  \return        kCanTrue         RamCheck failed.
 *  \return        kCanFalse        RamCheck passed.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitMailboxWriteReg16(CAN_CHANNEL_CANTYPE_FIRST CanChipMsgPtr16 regPtr, vuint16 value, vuint16 readMask, CanInitParaStructPtr initPara);
/* CODE CATEGORY 4 END */

/************************************************************************************************************
 *  CanLL_WriteReg32()
 ***********************************************************************************************************/
/*! \brief         Write value and do RamCheck
 *  \details       Write the value of the hardware mailbox or controller register and read back for RamCheck.
 *                 set initPara->isChRamCheckFail or initPara->isMbRamCheckFail in case of an HW issue to deactivate hardware.
 *  \param[in]     Controller       CAN controller.
 *                                  (only if not using "Optimize for one controller")
 *  \param[in]     regPtr           valid pointer to Register to be written.
 *  \param[in]     value            value to be written.
 *  \param[in]     readMask         mask to check the read back value.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_WriteReg32(CAN_CHANNEL_CANTYPE_FIRST CanChipMsgPtr32 regPtr, vuint32 value, vuint32 readMask, CanInitParaStructPtr initPara);
/* CODE CATEGORY 4 END */

# if defined( C_ENABLE_RX_FULLCAN_OBJECTS ) || defined( C_ENABLE_RX_BASICCAN_OBJECTS )
/************************************************************************************************************
 *  CanLL_InitMailboxWriteReg32()
 ***********************************************************************************************************/
/*! \brief         Write value and do RamCheck inside InitMailbox functions
 *  \details       Write the value of the hardware mailbox or controller register and read back for RamCheck.
 *                 set initPara->isChRamCheckFail or initPara->isMbRamCheckFail in case of an HW issue to deactivate hardware.
 *  \param[in]     Controller       CAN controller.
 *                                  (only if not using "Optimize for one controller")
 *  \param[in]     regPtr           valid pointer to Register to be written.
 *  \param[in]     value            value to be written.
 *  \param[in]     readMask         mask to check the read back value.
 *  \return        kCanTrue         RamCheck failed.
 *  \return        kCanFalse        RamCheck passed.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitMailboxWriteReg32(CAN_CHANNEL_CANTYPE_FIRST CanChipMsgPtr32 regPtr, vuint32 value, vuint32 readMask, CanInitParaStructPtr initPara);
/* CODE CATEGORY 4 END */
# endif


/************************************************************************************************************
 *  CanLL_WriteProtectedReg16()
 ***********************************************************************************************************/
/*! \brief         Write value via OS and do RamCheck
 *  \details       Write the value of the hardware mailbox or controller register and read back for RamCheck.
 *                 set initPara->isChRamCheckFail or initPara->isMbRamCheckFail in case of an HW issue to deactivate hardware.
 *  \param[in]     Controller       CAN controller.
 *                                  (only if not using "Optimize for one controller")
 *  \param[in]     area             Memory area to be written.
 *  \param[in]     regPtr           valid pointer to Register to be written.
 *  \param[in]     value            Value to be written.
 *  \param[in]     readMask         Mask to check the read back value.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_WriteProtectedReg16(CAN_CHANNEL_CANTYPE_FIRST vuint16 area, CanChipMsgPtr16 regPtr, vuint16 value, vuint16 readMask, CanInitParaStructPtr initPara);
/* CODE CATEGORY 4 END */


/**********************************************************************************************************************
 *  CanLL_InitBegin()
 *********************************************************************************************************************/
/*! \brief         Starts the channel initialization
 *  \details       Called by CanInit()
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] initPara            Pointer to local variables of CanInit()
 *  \return        kCanOk              Successfully completed
 *                 kCanFailed          Failure occured
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitBegin( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara );
/* CODE CATEGORY 4 END */

#if defined( C_ENABLE_CAN_RAM_CHECK_EXTENDED )
/**********************************************************************************************************************
 *  CanLL_InitBeginIsRegisterCorrupt()
 *********************************************************************************************************************/
/*! \brief         Performs the channel register RAM check
 *  \details       Called by CanInit()
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] initPara            Pointer to local variables of CanInit()
 *  \return        kCanFalse           No corrupt register RAM found
 *                 kCanTrue            Register RAM is considered corrupt or failure occured
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitBeginIsRegisterCorrupt( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara );
/* CODE CATEGORY 4 END */
#endif

/**********************************************************************************************************************
 *  CanLL_InitBeginSetRegisters()
 *********************************************************************************************************************/
/*! \brief         Performs the channel register initialization
 *  \details       Called by CanInit()
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] initPara            Pointer to local variables of CanInit()
 *  \return        kCanOk              Successfully completed
 *                 kCanFailed          Failure occured
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitBeginSetRegisters( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara );
/* CODE CATEGORY 4 END */

/**********************************************************************************************************************
 *  CanLL_InitMailboxTx()
 *********************************************************************************************************************/
/*! \brief         Initializes a transmit mailbox
 *  \details       Called by CanInit()
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] initPara            Pointer to local variables of CanInit()
 *  \return        kCanOk              Successfully completed
 *                 kCanFailed          Failure occured
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitMailboxTx( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara );
/* CODE CATEGORY 4 END */

# if (defined( C_ENABLE_CAN_RAM_CHECK ))

/**********************************************************************************************************************
 *  CanLL_InitMailboxTxDeactivate()
 *********************************************************************************************************************/
/*! \brief         Deactivates a transmit mailbox if it is considered corrupt by the RAM check
 *  \details       Called by CanInit()
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] initPara            Pointer to local variables of CanInit()
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_InitMailboxTxDeactivate( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara );
/* CODE CATEGORY 4 END */
# endif


#if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
/**********************************************************************************************************************
 *  CanLL_InitMailboxRxFullCan()
 *********************************************************************************************************************/
/*! \brief         Initializes a receive FullCAN mailbox
 *  \details       Called by CanInit()
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] initPara            Pointer to local variables of CanInit()
 *  \return        kCanOk              Successfully completed
 *                 kCanFailed          Failure occured
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitMailboxRxFullCan( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara );
/* CODE CATEGORY 4 END */

# if ((defined( C_ENABLE_CAN_RAM_CHECK )))
/**********************************************************************************************************************
 *  CanLL_InitMailboxRxFullCanDeactivate()
 *********************************************************************************************************************/
/*! \brief         Deactivates a receive FullCAN mailbox if it is considered corrupt by the RAM check
 *  \details       Called by CanInit()
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] initPara            Pointer to local variables of CanInit()
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_InitMailboxRxFullCanDeactivate( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara );
/* CODE CATEGORY 4 END */
# endif

#endif /* C_ENABLE_RX_FULLCAN_OBJECTS */

#if defined( C_ENABLE_RX_BASICCAN_OBJECTS )
/**********************************************************************************************************************
 *  CanLL_InitMailboxRxBasicCan()
 *********************************************************************************************************************/
/*! \brief         Initializes a receive BasicCAN mailbox
 *  \details       Called by CanInit()
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] initPara            Pointer to local variables of CanInit()
 *  \return        kCanOk              Successfully completed
 *                 kCanFailed          Failure occured
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitMailboxRxBasicCan( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara );
/* CODE CATEGORY 4 END */

# if ((defined( C_ENABLE_CAN_RAM_CHECK )))
/**********************************************************************************************************************
 *  CanLL_InitMailboxRxBasicCanDeactivate()
 *********************************************************************************************************************/
/*! \brief         Deactivates a receive BasicCAN mailbox if it is considered corrupt by the RAM check
 *  \details       Called by CanInit()
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] initPara            Pointer to local variables of CanInit()
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_InitMailboxRxBasicCanDeactivate( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara );
/* CODE CATEGORY 4 END */
# endif
#endif /* C_ENABLE_RX_BASICCAN_OBJECTS */


/**********************************************************************************************************************
 *  CanLL_InitEndSetRegisters()
 *********************************************************************************************************************/
/*! \brief         Finishes the channel register initialization
 *  \details       Called by CanInit()
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] initPara            Pointer to local variables of CanInit()
 *  \return        kCanOk              Successfully completed
 *                 kCanFailed          Failure occured
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitEndSetRegisters( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara );
/* CODE CATEGORY 4 END */

/**********************************************************************************************************************
 *  CanLL_InitEnd()
 *********************************************************************************************************************/
/*! \brief         Finishes the channel initialization
 *  \details       Called by CanInit()
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] initPara            Pointer to local variables of CanInit()
 *  \return        kCanOk              Successfully completed
 *                 kCanFailed          Failure occured
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitEnd( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara );
/* CODE CATEGORY 4 END */

#if defined( C_ENABLE_CAN_RAM_CHECK )
/**********************************************************************************************************************
 *  CanLL_InitIsMailboxCorrupt()
 *********************************************************************************************************************/
/*! \brief         Performs the RAM check for a mailbox
 *  \details       Called by CanInit()
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] initPara            Pointer to local variables of CanInit()
 *  \return        kCanFalse           Mailbox is not corrupt
 *                 kCanTrue            Mailbox is considered corrupt or failure occured
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_STATIC, vuint8, STATIC_CODE) CanLL_InitIsMailboxCorrupt( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara );
/* CODE CATEGORY 4 END */
#endif


/**********************************************************************************************************************
 *  CanLL_InitPowerOn()
 *********************************************************************************************************************/
/*! \brief         Performs the hardware specific global module initialization
 *  \details       Called by CanInitPowerOn()
 *  \return        kCanOk              Successfully completed
 *                 kCanFailed          Failure occured
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitPowerOn( void );
/* CODE CATEGORY 4 END */

/**********************************************************************************************************************
 *  CanLL_InitMemoryPowerOn()
 *********************************************************************************************************************/
/*! \brief         Internal function, called by Can_InitMemory().
 *  \details       Performs the platform specific memory initialization.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_InitMemoryPowerOn( void );
/* CODE CATEGORY 4 END */

/**********************************************************************************************************************
 *  CanLL_InitPowerOnChannelSpecific()
 *********************************************************************************************************************/
/*! \brief         Performs the channel dependent hardware specific global module initialization
 *  \details       Called by CanInitPowerOn()
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \return        kCanOk              Successfully completed
 *                 kCanFailed          Failure occured
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitPowerOnChannelSpecific( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 4 END */

#if defined( C_ENABLE_CANCEL_IN_HW )
/**********************************************************************************************************************
 *  CanLL_TxCancelInHw()
 *********************************************************************************************************************/
/*! \brief         Performs cancellation of the transmission in hardware
 *  \details       Called by cancellation
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] txCancellationPara  Pointer to local variables of cancellation
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 3 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_TxCancelInHw(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxCancellationParaStructPtr txCancellationPara);
/* CODE CATEGORY 3 END */
#endif
/**********************************************************************************************************************
 *  CanLL_TxBegin()
 *********************************************************************************************************************/
/*! \brief         Perform start of transmission
 *  \details       Called by transmission to prepare send object
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] txPara              Pointer to local variables of transmission
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_TxBegin(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxTransmissionParaStructPtr txPara);
/* CODE CATEGORY 1 END */
/**********************************************************************************************************************
 *  CanLL_TxSetMailbox()
 *********************************************************************************************************************/
/*! \brief         Set mailbox data for transmission
 *  \details       Called by transmission to set ID, DLC
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] txPara              Pointer to local variables of transmission
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_TxSetMailbox(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxTransmissionParaStructPtr txPara);
/* CODE CATEGORY 1 END */
/**********************************************************************************************************************
 *  CanLL_TxCopyToCan()
 *********************************************************************************************************************/
/*! \brief         Set mailbox data for transmission
 *  \details       Called by transmission to set data part in mailbox
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] txPara              Pointer to local variables of transmission
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_TxCopyToCan(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxTransmissionParaStructPtr txPara);
/* CODE CATEGORY 1 END */
/**********************************************************************************************************************
 *  CanLL_TxStart()
 *********************************************************************************************************************/
/*! \brief         Trigger mailbox to start the transmission
 *  \details       Called by transmission to start transmission
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] txPara              Pointer to local variables of transmission
 *  \return        kCanOk              No issue
 *                 kCanFailed          Issue occur
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_TxStart(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxTransmissionParaStructPtr txPara);
/* CODE CATEGORY 1 END */
/**********************************************************************************************************************
 *  CanLL_TxEnd()
 *********************************************************************************************************************/
/*! \brief         Perform end handling of the transmission
 *  \details       Called by transmission to finish transmission
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] txPara              Pointer to local variables of transmission
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_TxEnd(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxTransmissionParaStructPtr txPara);
/* CODE CATEGORY 1 END */
#if defined( C_ENABLE_TX_POLLING )
/**********************************************************************************************************************
 *  CanLL_TxIsGlobalConfPending()
 *********************************************************************************************************************/
/*! \brief         Check global pending of transmission
 *  \details       Called by transmission to get global pending flag
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \return        kCanTrue            pending confirmation
 *                 kCanFailed          no pending confirmation
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_TxIsGlobalConfPending(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 2 END */
/**********************************************************************************************************************
 *  CanLL_TxProcessPendings()
 *********************************************************************************************************************/
/*! \brief         Check pending of transmission object
 *  \details       Called by transmission to get pending flag of mailbox
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] txPara              Pointer to local variables of confirmation task
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_TxProcessPendings(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTaskParaStructPtr taskPara);
/* CODE CATEGORY 2 END */
#endif
/**********************************************************************************************************************
 *  CanLL_TxConfBegin()
 *********************************************************************************************************************/
/*! \brief         Perform start of confirmation
 *  \details       Called by confirmation
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] txConfPara          Pointer to local variables of confirmation
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_TxConfBegin(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxConfirmationParaStructPtr txConfPara);
/* CODE CATEGORY 1 END */
#if defined( C_ENABLE_CANCEL_IN_HW )
/**********************************************************************************************************************
 *  CanLL_TxConfIsMsgTransmitted()
 *********************************************************************************************************************/
/*! \brief         Check message is transmitted
 *  \details       Called by confirmation
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] txConfPara          Pointer to local variables of confirmation
 *  \return        kCanTrue            message is transmitted
 *                 kCanFailed          message is not transmitted
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_TxConfIsMsgTransmitted(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxConfirmationParaStructPtr txConfPara);
/* CODE CATEGORY 1 END */
#endif
#if defined(CAN_ENABLE_GENERIC_CONFIRMATION_API2)
/**********************************************************************************************************************
 *  CanLL_TxConfSetTxConfStruct()
 *********************************************************************************************************************/
/*! \brief         Set confirmation struct
 *  \details       Called by confirmation to set confirmation data struct
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] txConfPara          Pointer to local variables of confirmation
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_TxConfSetTxConfStruct(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxConfirmationParaStructPtr txConfPara);
/* CODE CATEGORY 1 END */
#endif
/**********************************************************************************************************************
 *  CanLL_TxConfEnd()
 *********************************************************************************************************************/
/*! \brief         Perform confirmation end handling
 *  \details       Called by confirmation
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] txConfPara          Pointer to local variables of confirmation
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_TxConfEnd(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxConfirmationParaStructPtr txConfPara);
/* CODE CATEGORY 1 END */

#if defined( C_ENABLE_RX_BASICCAN_OBJECTS )
/**********************************************************************************************************************
 *  CanLL_RxBasicMsgReceivedBegin()
 *********************************************************************************************************************/
/*! \brief         Perform BasicCAN receive begin
 *  \details       Called by reception to begin handling
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] rxBasicPara         Pointer to local variables of reception
 *  \return        kCanOk              No Issue occur
 *                 kCanFailed          Issue occur
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_RxBasicMsgReceivedBegin(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanRxBasicParaStructPtr rxBasicPara);
/* CODE CATEGORY 1 END */
/**********************************************************************************************************************
 *  CanLL_RxBasicReleaseObj()
 *********************************************************************************************************************/
/*! \brief         Release BasicCAN mailbox
 *  \details       Called by reception to release object
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] rxBasicPara         Pointer to local variables of reception
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_RxBasicReleaseObj(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanRxBasicParaStructPtr rxBasicPara);
/* CODE CATEGORY 1 END */
/**********************************************************************************************************************
 *  CanLL_RxBasicMsgReceivedEnd()
 *********************************************************************************************************************/
/*! \brief         Release BasicCAN receive end
 *  \details       Called by reception to finish handling
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] rxBasicPara         Pointer to local variables of reception
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_RxBasicMsgReceivedEnd(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanRxBasicParaStructPtr rxBasicPara);
/* CODE CATEGORY 1 END */
# if defined( C_ENABLE_RX_BASICCAN_POLLING )
/**********************************************************************************************************************
 *  CanLL_RxBasicIsGlobalIndPending()
 *********************************************************************************************************************/
/*! \brief         Check BasicCAN receive global pending
 *  \details       Called by reception to get pending state
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \return        kCanTrue            global pending
 *                 kCanFailed          no pending
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_RxBasicIsGlobalIndPending(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 2 END */
/**********************************************************************************************************************
 *  CanLL_RxBasicProcessPendings()
 *********************************************************************************************************************/
/*! \brief         Check BasicCAN receive pending
 *  \details       Called by reception to get mailbox pending state
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] taskPara            Pointer to local variables of reception task
 *  \return        kCanTrue            mailbox pending
 *                 kCanFailed          no pending
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_RxBasicProcessPendings(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTaskParaStructPtr taskPara);
/* CODE CATEGORY 2 END */
# endif /* C_ENABLE_RX_BASICCAN_POLLING */
#endif /* C_ENABLE_RX_BASICCAN_OBJECTS */
#if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
/**********************************************************************************************************************
 *  CanLL_RxFullMsgReceivedBegin()
 *********************************************************************************************************************/
/*! \brief         Perform FullCAN receive begin
 *  \details       Called by reception to begin handling
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] rxBasicPara         Pointer to local variables of reception
 *  \return        kCanOk              No Issue occur
 *                 kCanFailed          Issue occur
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_RxFullMsgReceivedBegin(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanRxFullParaStructPtr rxFullPara);
/* CODE CATEGORY 1 END */
/**********************************************************************************************************************
 *  CanLL_RxFullReleaseObj()
 *********************************************************************************************************************/
/*! \brief         Release FullCAN mailbox
 *  \details       Called by reception to release object
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] rxBasicPara         Pointer to local variables of reception
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_RxFullReleaseObj(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanRxFullParaStructPtr rxFullPara);
/* CODE CATEGORY 1 END */
/**********************************************************************************************************************
 *  CanLL_RxFullMsgReceivedEnd()
 *********************************************************************************************************************/
/*! \brief         Release FullCAN receive end
 *  \details       Called by reception to finish handling
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] rxBasicPara         Pointer to local variables of reception
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_RxFullMsgReceivedEnd(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanRxFullParaStructPtr rxFullPara);
/* CODE CATEGORY 1 END */
# if defined( C_ENABLE_RX_FULLCAN_POLLING )
/**********************************************************************************************************************
 *  CanLL_RxFullIsGlobalIndPending()
 *********************************************************************************************************************/
/*! \brief         Check FullCAN receive global pending
 *  \details       Called by reception to get pending state
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \return        kCanTrue            global pending
 *                 kCanFailed          no pending
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_RxFullIsGlobalIndPending(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 2 END */
/**********************************************************************************************************************
 *  CanLL_RxFullProcessPendings()
 *********************************************************************************************************************/
/*! \brief         Check FullCAN receive pending
 *  \details       Called by reception to get mailbox pending state
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] taskPara            Pointer to local variables of reception task
 *  \return        kCanTrue            mailbox pending
 *                 kCanFailed          no pending
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_RxFullProcessPendings(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTaskParaStructPtr taskPara);
/* CODE CATEGORY 2 END */
# endif /* C_ENABLE_RX_FULLCAN_POLLING */
#endif /* C_ENABLE_RX_FULLCAN_OBJECTS */

/**********************************************************************************************************************
 *  CanLL_ErrorHandlingBegin()
 *********************************************************************************************************************/
/*! \brief         Perform error handling begin
 *  \details       Called by error handler
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_ErrorHandlingBegin(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 2 END */
/**********************************************************************************************************************
 *  CanLL_BusOffOccured()
 *********************************************************************************************************************/
/*! \brief         Check BusOff occur
 *  \details       Called by error handler
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \return        kCanTrue            BusOff occur
 *                 kCanFailed          no BusOff occur
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_BusOffOccured(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 2 END */
/**********************************************************************************************************************
 *  CanLL_ErrorHandlingEnd()
 *********************************************************************************************************************/
/*! \brief         Perform error handling end
 *  \details       Called by error handler
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_ErrorHandlingEnd(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 2 END */
#if defined( C_ENABLE_EXTENDED_STATUS )
/**********************************************************************************************************************
 *  CanLL_GetStatusBegin()
 *********************************************************************************************************************/
/*! \brief         Perform read out of status information
 *  \details       Called by GetStatus API
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 3 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_GetStatusBegin(CAN_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 3 END */
#endif
/**********************************************************************************************************************
 *  CanLL_ModeTransition()
 *********************************************************************************************************************/
/*! \brief         Perform mode change
 *  \details       Called by mode handler
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in]     mode                mode to be set
 *  \param[in]     busOffRecovery      BusOff recovery should be done or not
 *  \param[in]     ramCheck            RamCheck should be done or not
 *  \return        kCanOk              Successfully completed
 *                 kCanRequested       Mode not yet reached
 *                 kCanFailed          Failure occured
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_STATIC, vuint8, STATIC_CODE) CanLL_ModeTransition(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST vuint8 mode, vuint8 busOffRecovery, vuint8 ramCheck);
/* CODE CATEGORY 4 END */
/**********************************************************************************************************************
 *  CanLL_StopReinit()
 *********************************************************************************************************************/
/*! \brief         Perform reinitialization for mode change
 *  \details       Called by mode handler
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_StopReinit(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */

/************************************************************************************************************
 *  CanLL_CanInterruptDisable()
 ***********************************************************************************************************/
/*! \brief         Disables CAN interrupts
 *  \details       Saves the current state (enable or disable) of all 
 *                 CAN interrupt sources to localInterruptOldFlagPtr
 *                 and disables all CAN interrupt sources (RX, TX, error, wakeup).
 *  \param[in]     canHwChannel              CAN channel
 *  \param[out]    localInterruptOldFlagPtr  Pointer to global variable that holds the interrupt state
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_CanInterruptDisable(CAN_HW_CHANNEL_CANTYPE_FIRST tCanLLCanIntOldPtr localInterruptOldFlagPtr);
/* CODE CATEGORY 1 END */

/************************************************************************************************************
 *  CanLL_CanInterruptRestore()
 **********************************************************************************************************/
/*! \brief         Restores CAN interrupts.
 *  \details       Restores the previous state of all CAN interrupt sources (RX, TX, error, wakeup).
 *  \param[in]     canHwChannel             CAN channel
 *  \param[in]     localInterruptOldFlag    Global variable that holds the interrupt state
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_CanInterruptRestore(CAN_HW_CHANNEL_CANTYPE_FIRST tCanLLCanIntOld localInterruptOldFlag);
/* CODE CATEGORY 1 END */



/* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  CanLL_SetFlexCANToInitMode()
 ***********************************************************************************************************/
/*! \brief         Set FlexCAN Controller to INIT mode.
 *  \details       Sets the FlexCAN Controller from any mode to INIT mode.
 *  \param[in]     Controller     CAN controller (Controller must be in valid range).
 *                                (only if not using "Optimize for one controller")
 *  \param[in]     CanInitHandle  handle to INIT-structure
 *  \return        kCanRequested: FlexCAN successfully set to init mode
 *  \return        kCanFailed:    FlexCAN failure
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_SetFlexCANToInitMode(CAN_HW_CHANNEL_CANTYPE_FIRST CanInitHandle initObject);
/* CODE CATEGORY 4 END */
/* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  CanLL_ExecuteSoftReset()
 ***********************************************************************************************************/
/*! \brief         Perform FlexCAN soft-reset
 *  \details       Triggers the FlexCAN Controller to perform internal soft-reset.
 *  \param[in]     Controller     CAN controller (Controller must be in valid range).
 *                                (only if not using "Optimize for one controller")
 *  \return        kCanRequested: SoftReset ongoing
 *  \return        kCanOk:        SoftReset successfully finished
 *  \return        kCanFailed:    transition failure
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_ExecuteSoftReset(CAN_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */

/* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  CanLL_ReInit()
 ***********************************************************************************************************/
/*! \brief         Perform Reintialisation of FlexCAN controller.
 *  \details       Use CanHL_ReInit() for reinitalization of FlexCAN Controller.
 *  \param[in]     channel        current application CAN channel (must be in valid range).
 *                                (only if not using "Optimize for one controller")
 *  \return        kCanOk:        Transition to START successfully finished
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_ReInit(CAN_CHANNEL_CANTYPE_FIRST vuint8 ramCheck);
/* CODE CATEGORY 4 END */

/* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  CanLL_StopTransition()
 ***********************************************************************************************************/
/*! \brief         Perform FlexCAN for stop mode and control the transition.
 *  \details       Request stop mode to FlexCAN Controller and control the transition.
 *  \param[in]     channel          current application CAN channel
 *  \param[in]     canHwChannel     current HW CAN channel
 *  \param[in]     busOffRecovery   flag whether BusOff recovery shall be terminated (if relevant and possible)
 *  \param[in]     ramCheck         flag whether RamCheck shall be executed (if relevant and possible)
 *  \return        kCanRequested:   Transition to STOP ongoing
 *  \return        kCanOk           Transition to STOP successfully finished
 *  \return        kCanFailed       Transition to STOP not possible
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_StopTransition(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST vuint8 busOffRecovery, vuint8 ramCheck);
/* CODE CATEGORY 4 END */

/* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  CanLL_StartTransition()
 ***********************************************************************************************************/
/*! \brief         Perform FlexCAN start mode and control the transition
 *  \details       Request start mode to FlexCAN Controller and control the transition.
 *  \param[in]     channel          current application CAN channel
 *  \param[in]     canHwChannel     current HW CAN channel
 *  \param[in]     mode             target mode for the transition
 *  \param[in]     ramCheck       flag whether RamCheck shall be executed (if relevant and possible)
 *  \return        kCanRequested:   Transition to START ongoing
 *  \return        kCanOk:          Transition to START successfully finished
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_StartTransition(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST vuint8 mode, vuint8 ramCheck);
/* CODE CATEGORY 4 END */

#if defined ( C_ENABLE_BUSOFF_RECOVERY_COMPLIANT )
/* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  CanLL_BusOffEndTransition()
 ***********************************************************************************************************/
/*! \brief         Perform FlexCAN BusOffEnd transition and control the transition
 *  \details       Request BusOff Auto Recovery Mode to FlexCAN Controller. When busoff end is detected
 *                 request start mode and control the transition.
 *  \param[in]     channel          current application CAN channel
 *  \param[in]     canHwChannel     current HW CAN channel
 *  \param[in]     ramCheck       flag whether RamCheck shall be executed (if relevant and possible)
 *  \return        kCanRequested:   Transition to START ongoing
 *  \return        kCanOk:          Transition to START successfully finished
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_BusOffEndTransition(CAN_HW_CHANNEL_CANTYPE_FIRST vuint8 ramCheck);
/* CODE CATEGORY 4 END */
#endif


#if defined( C_ENABLE_CAN_RAM_CHECK_EXTENDED ) && defined( C_ENABLE_CLKSRC_SELECTION ) /* COV_CAN_RAMCHECK_EXTENDED_CLKSRC_AVAILABILITY */
/* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  CanLL_CheckClockSource()
 ***********************************************************************************************************/
/*! \brief         Check the CAN[CTRL1].CLKSRC bit
 *  \details       check the CAN[CTRL1].CLKSRC bit by write and read back patterns.
 *  \param[in]     Controller   CAN controller
 *  \return        kCanTrue:    CAN[CTRL1].CLKSRC bit is corrupt
 *  \return        kCanFalse:   CAN[CTRL1].CLKSRC bit is not corrupt  
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
************************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_CheckClockSource(CAN_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */
#endif

#if defined( C_ENABLE_CAN_RXTX_INTERRUPT )
/* CODE CATEGORY 1 START */
/************************************************************************************************************
 *  CanLL_ComputeMailboxInterrupt()
 ***********************************************************************************************************/
/*! \brief         Computes Mailbox interrupt.
 *  \details       Determines the index of the Mailbox that notified an interrupt and call
 *                 CanLL_ComputeInterruptType.
 *  \param[in]     Controller    CAN controller (Controller must be in valid range).
 *                               (only if not using "Optimize for one controller")
 *  \param[in]     iFlags        Interrupt Flags that should be used for computation.
 *  \param[in]     iMask         Interrupt Mask that determines which iFlags are considered in interrupt context.
 *  \param[in]     startIndex    Index of first Mailbox that is part of the corresponding iFlags/iMask values.
 *  \pre           -
 *  \context       ISR1|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        C_ENABLE_CAN_RXTX_INTERRUPT
***********************************************************************************************************/
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanLL_ComputeMailboxInterrupt(CAN_HW_CHANNEL_CANTYPE_FIRST vuint32 iFlags, vuint32 iMask, CanObjectHandle startIndex);
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
/************************************************************************************************************
 *  CanLL_ComputeInterruptType()
 ***********************************************************************************************************/
/*! \brief         Computes the communication type of the notified Mailbox interrupt (Tx/Rx FullCAN/BasicCAN).
 *  \details       Determines which communication event occurred and calls internal notification function.
 *  \param[in]     Controller    CAN controller (Controller must be in valid range)
 *                               (only if not using "Optimize for one controller")
 *  \param[in]     index         Index of the Mailbox that notified an interrupt.
 *  \pre           -
 *  \context       ISR1|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        C_ENABLE_CAN_RXTX_INTERRUPT
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_ComputeInterruptType(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle index);
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
/************************************************************************************************************
 *  CanLL_ComputeInterruptType()
 ***********************************************************************************************************/
/*! \brief         Checks all mailbox interrupt flags (Tx/Rx FullCAN/BasicCAN).
 *  \details       Determines which mailbox interrupt flags are set and processes it accordingly.
 *  \param[in]     Controller    CAN controller (Controller must be in valid range).
 *                               (only if not using "Optimize for one controller")
 *  \pre           -
 *  \context       ISR1|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        C_ENABLE_CAN_RXTX_INTERRUPT
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_CanMailboxInterrupt( CAN_HW_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 1 END */
#endif

/* CODE CATEGORY 1 START */
/************************************************************************************************************
 *  CanLL_ClearPendingInterrupt()
 ***********************************************************************************************************/
/*! \brief         Clears the interrupt flag related to the hwObjectHandle.
 *  \details       Determines which which interrupt flags needs to be cleared and clears the bit related to
 *                 the hwObjectHandle.
 *  \param[in]     pFlexCANLocal    base address of the CAN controller
 *  \param[in]     hwObjHandle      current hardware object to handle
 *  \pre           -
 *  \context       ISR1|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        -
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_ClearPendingInterrupt( tFlexCANPtr pFlexCANLocal, CanObjectHandle hwObjHandle );
/* CODE CATEGORY 1 END */

#if defined (C_ENABLE_TX_POLLING) || ( defined (C_ENABLE_RX_FULLCAN_POLLING) && defined (C_ENABLE_RX_FULLCAN_OBJECTS) ) || ( (defined (C_ENABLE_RX_BASICCAN_POLLING) && defined (C_ENABLE_RX_BASICCAN_OBJECTS)) && defined (C_ENABLE_CLASSIC_MAILBOX_LAYOUT) )
/* CODE CATEGORY 1 START */
/************************************************************************************************************
 *  CanLL_GetInterruptFlag()
 ***********************************************************************************************************/
/*! \brief         Gets the corresponding interrupt flag related to a hwObjectHandle.
 *  \details       Determines which which interrupt flags needs to be returned related to the hwObjectHandle.
 *  \param[in]     pFlexCANLocal    base address of the CAN controller
 *  \param[in]     hwObjHandle      current hardware object to handle
 *  \return        iFlags           returns the content of the iFlag related to hwObjHandle
 *  \pre           -
 *  \context       ISR1|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        -
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint32, STATIC_CODE) CanLL_GetInterruptFlag( tFlexCANPtr pFlexCANLocal, CanObjectHandle hwObjHandle );
/* CODE CATEGORY 1 END */
#endif

#if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
  /* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  CanLL_CheckMaxHwMailboxHandle()
 ***********************************************************************************************************/
/*! \brief         Check for maximum value of HW mailbox handle
 *  \details       If canHwChannel is greater or equal to number of available mailboxes throw a DET
 *  \param[in]     hwChannel           hardware channel of the corresponding CAN Controller
 *  \param[in]     hwObjHandle         Handle to hardware object
 *  \return        retVal     kCanOk: no error, kCanFalse: error
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        CAN_SAFE_BSW == STD_ON
************************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_CheckMaxHwMailboxHandle(CanChannelHandle hwChannel, Can_HwHandleType hwObjHandle);
/* CODE CATEGORY 4 END */

# if defined( C_ENABLE_CAN_RXTX_INTERRUPT )   || \
      defined( C_ENABLE_CAN_BUSOFF_INTERRUPT ) /* COV_CAN_INTERRUPT_SUPPORT */ 
  /* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  CanLL_CheckSizeOfHwChannelData()
 ***********************************************************************************************************/
/*! \brief         Check size of HwChannelData
 *  \details       If canHwChannel is greater or equal to the size of HwChannelData throw a DET
 *  \param[in]     hwChannel   hardware channel of the corresponding CAN Controller
 *  \return        retVal     kCanOk: no error, kCanFalse: error
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        C_ENABLE_CAN_RXTX_INTERRUPT || C_ENABLE_CAN_BUSOFF_INTERRUPT || C_ENABLE_CAN_WAKEUP_INTERRUPT
************************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_CheckSizeOfHwChannelData(CanChannelHandle hwChannel);
/* CODE CATEGORY 4 END */
# endif
#endif

/************************************************************************************************************
 *  CanHL_CleanUpSendState()
 ***********************************************************************************************************/
/*! \brief         Clean up send state
 *  \details       Reset active send state (semaphore blocking TX while send).
 *                 Called by Can_SetControllerMode(), Can_MainFunction_Mode() (CanHL_ReInit() do same but without this call).
 *  \param[in]     Controller    CAN controller \n
 *                               (only if not using "Optimize for one controller")
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_CleanUpSendState(CAN_CHANNEL_CANTYPE_ONLY);

# if (CAN_HW_LOOP_SUPPORT_API == STD_OFF)
/************************************************************************************************************
 *  ApplCanTimerLoop()
 ***********************************************************************************************************/
/*! \brief         Time out monitoring
 *  \details       Service function to check (against generated maximum loop value) whether a hardware loop shall be continued or broken.
 *  \param[in]     Controller  CAN controller on which the hardware observation takes place. \n
 *                             (only if not using "Optimize for one controller")
 *  \param[in]     source      Source for the hardware observation.
 *  \return        CAN_NOT_OK  when loop shall be broken (observation stops) \n
 *                             CAN_NOT_OK should only be used in case of a time out occurs due to a hardware issue. \n
 *                             After this an appropriate error handling is needed (see chapter Hardware Loop Check / Time out Monitoring).
 *  \return        CAN_OK      when loop shall be continued (observation continues)
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \notes         Please refer to chapter "Hardware Loop Check".
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) ApplCanTimerLoop(CAN_CHANNEL_CANTYPE_FIRST uint8 source);
# endif

/************************************************************************************************************
 *  CanHL_ModeTransition()
 ***********************************************************************************************************/
/*! \brief         Request mode transition
 *  \details       Handle/Request transition and wait asynchronous-short time.
 *                 Called by Can_SetControllerMode().
 *  \param[in]     Controller         CAN controller (Controller must be in valid range). \n
 *                                    (only if not using "Optimize for one controller") \n
 *  \param[in]     transitionRequest  transition request used to switch mode (kCanModeInit, kCanModeSleep, kCanModeWakeupStopReinit, \n
 *                                    kCanModeStopReinit, kCanModeStopReinitFast, kCanModeStart, kCanModeStartReinit, kCanModeSilent, \n
 *                                    kCanModeResetBusOffStart, kCanModeResetBusOffEnd). \n
 *  \param[in]     busOffRecovery     handling of the busoff behaviour (kCanFinishBusOffRecovery, kCanContinueBusOffRecovery). \n
 *  \param[in]     doRamCheck         do a RAM check while reinit or not (kCanExecuteRamCheck, kCanSuppressRamCheck). \n
 *  \return        kCanFailed         transition rejected
 *  \return        kCanRequested      transition requested but is ongoing asynchronous
 *  \return        kCanOk             transition finished successful
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_ModeTransition(CAN_CHANNEL_CANTYPE_FIRST uint8 transitionRequest, uint8 busOffRecovery, uint8 doRamCheck);

/************************************************************************************************************
 *  CanHL_NotifyTransition()
 ***********************************************************************************************************/
/*! \brief         notify about sucessful mode transition
 *  \details       notify to upper layer.
 *                 Called by Can_SetControllerMode().
 *  \param[in]     Controller         CAN controller (Controller must be in valid range). \n
 *                                    (only if not using "Optimize for one controller") \n
 *  \param[in]     canState           CAN controller mode to be switched to (CAN_STATUS_STOP, CAN_STATUS_START, CAN_STATUS_SLEEP). \n
 *  \param[in]     canIfState         CAN controller mode to be switched to (CANIF_CS_STOPPED, CANIF_CS_STARTED, CANIF_CS_SLEEP). \n
 *  \param[in]     transitionState    transition request state (kCanFailed, kCanRequested, kCanOk). \n
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_NotifyTransition(CAN_CHANNEL_CANTYPE_FIRST uint8 canState, CanIf_ControllerModeType canIfState, uint8 transitionState);

#if defined(C_ENABLE_CANCEL_IN_HW)
/************************************************************************************************************
 *  CanHL_IsHigherCanIdPrio()
 ***********************************************************************************************************/
/*! \brief         check CAN ID priority
 *  \details       compare two CAN IDs and check if first one is of higher priority.
 *  \param[in]     CanId1        first CAN ID for compare
 *  \param[in]     CanId2        second CAN ID for compare
 *  \return        CAN_OK        first CAN ID has higher priority
 *  \return        CAN_NOT_OK    first CAN ID has no higher priority
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) CanHL_IsHigherCanIdPrio(Can_IdType CanId1, Can_IdType CanId2);
#endif

/************************************************************************************************************
 *  CanHL_WritePrepare()
 ***********************************************************************************************************/
/*! \brief         TX preparation
 *  \details       Search for BasicCAN object handle to transmit (Multiplexed TX) and backup data for cancel TX object if necessary.
 *                 calculate txPara member activeSendObject, and mailboxElement
 *                 Called by Can_Write().
 *  \param[in]     Controller       CAN controller. \n
 *                                  (only if not using "Optimize for one controller")
 *  \param[in,out] txPara           mailbox information
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_WritePrepare(CAN_CHANNEL_CANTYPE_FIRST CanTxTransmissionParaStructPtr txPara);

#if defined(C_ENABLE_CANCEL_IN_HW) 
/************************************************************************************************************
 *  CanHL_WriteSavePduInfo()
 ***********************************************************************************************************/
/*! \brief         Save PduInfo before send
 *  \details       Cancellation or TxHwFifo need to save send data to get this information in confirmation context.
 *  \param[in,out] txPara                    mailbox information
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_WriteSavePduInfo(CanTxTransmissionParaStructPtr txPara);
#endif

#if defined(C_ENABLE_CANCEL_IN_HW)
/************************************************************************************************************
 *  CanHL_WritePrepareCancelTx()
 ***********************************************************************************************************/
/*! \brief         TX cancellation
 *  \details       Cancel the BasicCAN TX object or store message data for later cancelation
 *                 Called by CanHL_WritePrepare().
 *  \param[in]     Controller                CAN controller. \n
 *                                           (only if not using "Optimize for one controller")
 *  \param[in,out] txPara                    mailbox information
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_WritePrepareCancelTx(CAN_CHANNEL_CANTYPE_FIRST CanTxTransmissionParaStructPtr txPara);
#endif

/************************************************************************************************************
 *  CanHL_WriteStart()
 ***********************************************************************************************************/
/*! \brief         TX start
 *  \details       Write ID, DLC and Data to FullCAN or BasicCAN object and set transmit request
 *                 Called by Can_Write().
 *  \param[in]     Controller      CAN controller. \n
 *                                 (only if not using "Optimize for one controller")
 *  \param[in,out] txPara          mailbox information
 *  \return        CAN_NOT_OK      transmission failed.
 *  \return        CAN_OK          transmission successful.
 *  \return        CAN_BUSY        transition object busy - repeat it.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) CanHL_WriteStart(CAN_CHANNEL_CANTYPE_FIRST CanTxTransmissionParaStructPtr txPara);

/************************************************************************************************************
 *  CanHL_GetActiveSendObject()
 ***********************************************************************************************************/
/*! \brief         Convert Handle
 *  \details       Hardware to logical Handle conversion.
 *  \param[in]     mailboxHandle   Handle to mailbox object
 *  \param[in]     mailboxElement  mailbox element
 *  \return        logical handle for the given hardware mailbox
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, CanObjectHandle, STATIC_CODE) CanHL_GetActiveSendObject(Can_HwHandleType mailboxHandle, Can_HwHandleType mailboxElement);

#if defined(C_ENABLE_CANCEL_IN_HW) 
/************************************************************************************************************
 *  CanHL_GetActiveSendData()
 ***********************************************************************************************************/
/*! \brief         Convert Handle
 *  \details       Hardware to logical Handle conversion.
 *  \param[in]     mailboxHandle   Handle to mailbox object
 *  \param[in]     mailboxElement  mailbox element
 *  \return        start index in the data buffer for the given mailbox
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint16, STATIC_CODE) CanHL_GetActiveSendData(Can_HwHandleType mailboxHandle, uint8 mailboxElement);
#endif

#if defined(C_ENABLE_CAN_RAM_CHECK)
/************************************************************************************************************
 *  CanHL_RamCheckMailboxNotification()
 ***********************************************************************************************************/
/*! \brief         RAM check
 *  \details       Notify upper layer in case of an HW issue and deactivate controller.
 *                 Called by CanHL_ReInit().
 *  \param[in]     Controller       CAN controller. \n
 *                                  (only if not using "Optimize for one controller")
 *  \param[in]     initPara         include controller and all LL specific settings.
 *  \param[in]     htrh             Hrh or Hth of the hardware object
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_RamCheckMailboxNotification(CAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara);
#endif

/************************************************************************************************************
 *  CanHL_InitBegin()
 ***********************************************************************************************************/
/*! \brief         Start Initialization
 *  \details       LL implementation see token CanLL_InitBegin description.
 *                 Called by CanHL_ReInit().
 *  \param[in]     Controller       CAN controller. \n
 *                                  (only if not using "Optimize for one controller")
 *  \param[in]     initPara          include controller and all LL specific settings.
 *  \return        errorId
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_InitBegin(CAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara);

#if defined(C_ENABLE_TX_FULLCAN_OBJECTS)
/************************************************************************************************************
 *  CanHL_InitTxFullCAN()
 ***********************************************************************************************************/
/*! \brief         Initialize TX FullCAN
 *  \details       LL implementation see token CanLL_InitTxObj description.
 *                 Called by CanHL_ReInit().
 *  \param[in]     Controller       CAN controller. \n
 *                                  (only if not using "Optimize for one controller")
 *  \param[in]     initPara          include controller and all LL specific settings.
 *  \return        errorId
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_InitTxFullCAN(CAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara);
#endif

/************************************************************************************************************
 *  CanHL_InitTxBasicCAN()
 ***********************************************************************************************************/
/*! \brief         Initialize TX BasicCAN
 *  \details       LL implementation see token CanLL_InitTxObj description.
 *                 Called by CanHL_ReInit().
 *  \param[in]     Controller       CAN controller. \n
 *                                  (only if not using "Optimize for one controller")
 *  \param[in]     initPara         include controller and all LL specific settings.
 *  \return        errorId
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_InitTxBasicCAN(CAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara);


#if defined(C_ENABLE_RX_FULLCAN_OBJECTS)
/************************************************************************************************************
 *  CanHL_InitRxFullCAN()
 ***********************************************************************************************************/
/*! \brief         Initialize RX FullCAN
 *  \details       LL implementation see token CanLL_InitFullCANObj description.
 *                 Called by CanHL_ReInit().
 *  \param[in]     Controller       CAN controller. \n
 *                                  (only if not using "Optimize for one controller")
 *  \param[in]     initPara         include controller and all LL specific settings.
 *  \return        errorId
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_InitRxFullCAN(CAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara);
#endif

#if defined(C_ENABLE_RX_BASICCAN_OBJECTS) /* COV_CAN_MULTIPLE_BASICCAN */
/************************************************************************************************************
 *  CanHL_InitRxBasicCAN()
 ***********************************************************************************************************/
/*! \brief         Initialize RX BasicCAN
 *  \details       LL implementation see token CanLL_InitBasicCANObj description.
 *                 Called by CanHL_ReInit().
 *  \param[in]     Controller       CAN controller. \n
 *                                  (only if not using "Optimize for one controller")
 *  \param[in]     initPara         include controller and all LL specific settings.
 *  \return        errorId
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_InitRxBasicCAN(CAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara);
#endif

/************************************************************************************************************
 *  CanHL_InitEnd_InitMode()
 ***********************************************************************************************************/
/*! \brief         End Initialization
 *  \details       LL implementation see token CanLL_InitEnd_InitMode description.
 *                 Called by CanHL_ReInit().
 *  \param[in]     Controller       CAN controller. \n
 *                                  (only if not using "Optimize for one controller")
 *  \param[in]     initPara         include controller and all LL specific settings.
 *  \return        errorId
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_InitEnd_InitMode(CAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara);

#if defined(C_ENABLE_RX_BASICCAN_OBJECTS) /* COV_CAN_MULTIPLE_BASICCAN */
# if defined(C_ENABLE_RX_BASICCAN_POLLING) /* COV_CAN_RX_BASICCAN_POLLING */
/************************************************************************************************************
 *  CanHL_RxBasicCanPolling()
 ***********************************************************************************************************/
/*! \brief         RX BasicCAN polling
 *  \details       RX BasicCAN polling handling.
 *                 Called by Can_MainFunctionRead().
 *  \param[in]     Controller    CAN controller.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_RxBasicCanPolling(CAN_HW_CHANNEL_CANTYPE_ONLY);
# endif
#endif /* C_ENABLE_RX_BASICCAN_OBJECTS */

#if defined(C_ENABLE_RX_FULLCAN_OBJECTS)
# if defined(C_ENABLE_RX_FULLCAN_POLLING) /* COV_CAN_RX_FULLCAN_POLLING */
/************************************************************************************************************
 *  CanHL_RxFullCanPolling()
 ***********************************************************************************************************/
/*! \brief         RX FullCAN polling
 *  \details       RX FullCAN polling handling.
 *                 Called by Can_MainFunctionRead().
 *  \param[in]     Controller    CAN controller.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_RxFullCanPolling(CAN_HW_CHANNEL_CANTYPE_ONLY);
# endif
#endif /* C_ENABLE_RX_FULLCAN_OBJECTS */

#if defined(C_ENABLE_RX_FULLCAN_OBJECTS) || defined(C_ENABLE_RX_BASICCAN_OBJECTS) /* COV_CAN_MULTIPLE_BASICCAN */
/************************************************************************************************************
 *  CanHL_RxMsgReceivedNotification()
 ***********************************************************************************************************/
/*! \brief         RX notification
 *  \details       RX queue and notification handling for BasicCAN and FullCAN reception.
 *                 Called by CanHL_BasicCanMsgReceived(),CanHL_FullCanMsgReceived().
 *  \param[in]     Controller      CAN controller. \n
 *                                 (only if not using "Optimize for one controller")
 *  \param[in]     rxStructPtr     include general rx info and all LL specific data.
 *  \return        errorId         error identifier reporting to DET
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_RxMsgReceivedNotification(CAN_CHANNEL_CANTYPE_FIRST CanRxInfoStructPtr rxStructPtr);
#endif

#if defined(C_ENABLE_RX_QUEUE)
/************************************************************************************************************
 *  CanHL_RxQueueExecution()
 ***********************************************************************************************************/
/*! \brief         RX queue
 *  \details       RX queue execution and notification.
 *                 Called by Can_MainFunction_Read().
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_RxQueueExecution(void);
#endif

#if defined(C_ENABLE_TX_POLLING) /* COV_CAN_TX_POLLING TX */
/************************************************************************************************************
 *  CanHL_TxConfirmationPolling()
 ***********************************************************************************************************/
/*! \brief         TX Confirmation intermediate call
 *  \details       intermediate call to do interrupt locks between polling call from LL and HL handling.
 *  \param[in]     Controller      CAN controller. \n
 *                                 (only if not using "Optimize for one controller")
 *  \param[in]     mailboxHandle   mailbox handle
 *  \param[in]     mailboxElement  index of the mailboxElement (muxTx, FIFO)
 *  \param[in]     hwObjHandle     hardware handle
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_TxConfirmationPolling(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle mailboxHandle, CanObjectHandle mailboxElement, CanObjectHandle hwObjHandle);
#endif

/************************************************************************************************************
 *  CanHL_TxConfirmation()
 ***********************************************************************************************************/
/*! \brief         TX Confirmation handling
 *  \details       Called for a transmit or cancel event. Finish transmission by free send mailbox and call confirmation. \n
 *                 Called for FullCAN and BasicCAN handling.
 *  \param[in]     Controller      CAN controller. \n
 *                                 (only if not using "Optimize for one controller")
 *  \param[in]     mailboxHandle   mailbox handle
 *  \param[in]     mailboxElement  index of the mailboxElement (muxTx, FIFO)
 *  \param[in]     hwObjHandle     transmitted hardware handle
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanHL_TxConfirmation(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle mailboxHandle, CanObjectHandle mailboxElement, CanObjectHandle hwObjHandle);


#if defined(CAN_ENABLE_GENERIC_CONFIRMATION_API2)
/************************************************************************************************************
 *  CanHL_SetCanPduInfo()
 ***********************************************************************************************************/
/*! \brief         copy the confirmation parameter info to the PduInfo struct
 *  \details       Called while confirmation handling to set data struct need for confirmation API2. \n
 *  \param[in,out] PduInfo             Pointer to local PduInfo struct
 *  \param[in]     txConfPara          Pointer to local variables of confirmation
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanHL_SetCanPduInfo(Can_PduInfoPtrType_var PduInfo, CanTxConfirmationParaStructPtr txConfPara);
#endif

#if defined(C_ENABLE_RX_BASICCAN_OBJECTS) /* COV_CAN_MULTIPLE_BASICCAN */
# if defined(C_ENABLE_RX_BASICCAN_POLLING) /* COV_CAN_RX_BASICCAN_POLLING */
/************************************************************************************************************
 *  CanHL_BasicCanMsgReceivedPolling()
 ***********************************************************************************************************/
/*! \brief         RX Indication intermediate call
 *  \details       intermediate call to do interrupt locks between polling call from LL and HL handling.
 *  \param[in]     Controller      CAN controller. \n
 *                                 (only if not using "Optimize for one controller")
 *  \param[in]     rxMailboxHandle mailbox handle
 *  \param[in]     hwObjHandle     received hardware handle
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_BasicCanMsgReceivedPolling(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxMailboxHandle, CanObjectHandle hwObjHandle);
# endif

/************************************************************************************************************
 *  CanHL_BasicCanMsgReceived()
 ***********************************************************************************************************/
/*! \brief         Handle reception
 *  \details       Receive BasicCAN data and call indication function.
 *  \param[in]     Controller      CAN controller. \n
 *                                 (only if not using "Optimize for one controller")
 *  \param[in]     rxMailboxHandle mailbox handle
 *  \param[in]     hwObjHandle     received hardware handle
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanHL_BasicCanMsgReceived(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxMailboxHandle, CanObjectHandle hwObjHandle);
#endif

#if defined(C_ENABLE_RX_FULLCAN_OBJECTS)
# if defined(C_ENABLE_RX_FULLCAN_POLLING) /* COV_CAN_RX_FULLCAN_POLLING */
/************************************************************************************************************
 *  CanHL_FullCanMsgReceivedPolling()
 ***********************************************************************************************************/
/*! \brief         RX Indication intermediate call
 *  \details       intermediate call to do interrupt locks between polling call from LL and HL handling.
 *  \param[in]     Controller      CAN controller. \n
 *                                 (only if not using "Optimize for one controller")
 *  \param[in]     rxMailboxHandle mailbox handle
 *  \param[in]     hwObjHandle     received hardware handle
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_FullCanMsgReceivedPolling(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxMailboxHandle, CanObjectHandle hwObjHandle);
#endif

/************************************************************************************************************
 *  CanHL_FullCanMsgReceived()
 ***********************************************************************************************************/
/*! \brief         Handle reception
 *  \details       Receive FullCAN data and call indication function.
 *  \param[in]     Controller      CAN controller. \n
 *                                 (only if not using "Optimize for one controller")
 *  \param[in]     rxMailboxHandle mailbox handle
 *  \param[in]     hwObjHandle     received hardware handle
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanHL_FullCanMsgReceived(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxMailboxHandle, CanObjectHandle hwObjHandle);
#endif

/************************************************************************************************************
 *  CanHL_ErrorHandling()
 ***********************************************************************************************************/
/*! \brief         BUSOFF handling
 *  \details       Handler for bus off situation.
 *  \param[in]     Controller    CAN controller. \n
 *                               (only if not using "Optimize for one controller")
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanHL_ErrorHandling(CAN_HW_CHANNEL_CANTYPE_ONLY);


#if defined(C_ENABLE_CANCEL_TX_IN_HW) 
#endif

/************************************************************************************************************
 *  CanHL_ReInit()
 ***********************************************************************************************************/
/*! \brief         Initialization of controller specific CAN hardware.
 *  \details       Initialization of the CAN controller hardware registers and CAN driver variables. \n
 *                 after that the controller is fully initialized and can be swtiched to "STOP Mode".
 *  \param[in]     Controller            CAN controller. \n
 *                                       (only if not using "Optimize for one controller")
 *  \param[in]     doRamCheck            RAM check exectuion (kCanExecuteRamCheck, kCanSuppressRamCheck).
 *  \return        error                 return kCanFailed in case of issue or kCanOk if initialization pass.
 *  \pre           controller is ready to be configured (INIT mode).
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \notes         no mode change must be done inside. No CAN bus depended hardware loops allowed.
***********************************************************************************************************/
V_DEF_FUNC(CAN_STATIC, uint8, STATIC_CODE) CanHL_ReInit(CAN_HW_CHANNEL_CANTYPE_FIRST uint8 doRamCheck);

#define CAN_STOP_SEC_STATIC_CODE  /*----------------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#endif /* CAN_LOCAL_H */

/* End of channel */



/* Kernbauer Version: 1.14 Konfiguration: DrvCan_Arm32Flexcan3Asr Erzeugungsgangnummer: 398 */

/* Kernbauer Version: 1.14 Konfiguration: DrvCan_Arm32Flexcan3Asr Erzeugungsgangnummer: 398 */

/* Kernbauer Version: 1.14 Konfiguration: DrvCan_Arm32Flexcan3Asr Erzeugungsgangnummer: 398 */

/* Kernbauer Version: 1.14 Konfiguration: DrvCan_Arm32Flexcan3Asr Erzeugungsgangnummer: 398 */

/* Kernbauer Version: 1.14 Konfiguration: DrvCan_Arm32Flexcan3Asr Erzeugungsgangnummer: 398 */

/* Kernbauer Version: 1.14 Konfiguration: DrvCan_Arm32Flexcan3Asr Erzeugungsgangnummer: 398 */

/* Kernbauer Version: 1.14 Konfiguration: DrvCan_Arm32Flexcan3Asr Erzeugungsgangnummer: 398 */

/************   Organi, Version 3.9.2 Vector-Informatik GmbH  ************/
