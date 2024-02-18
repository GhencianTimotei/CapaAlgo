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

/* \trace SPEC-1570 */
/***************************************************************************/
/* Include files                                                           */
/***************************************************************************/
/* ECO_IGNORE_BLOCK_BEGIN */
#define C_DRV_INTERNAL /* compatibility */
#define CAN_SOURCE     /* testability */
#define __CAN_SRC__       /* compatibility RTM not aware of multi driver instance */ /* PRQA S 0602,0603 */ /* MD_Can_ModuleDefine */
#if !defined(__CAN_SRC__) /* driver use ORGANI without infix */ /* COV_CAN_INTERNAL */
# define __CAN_SRC__      /* for all MSR module (used by RTM) */ /* PRQA S 0602,0603 */ /* MD_Can_ModuleDefine */
#endif

/* \trace SPEC-1408, SPEC-1590, SPEC-1588 */

/* \trace SPEC-1392 */
#include "CanIf_Cbk.h"   /* for callback declaration */
/* \trace SPEC-1707 */
#include "CanIf.h"       /* for version check */
#include "Can_Local.h"    /* have to be last include due to channel define will lead to problems */


#if (CAN_DEV_ERROR_REPORT == STD_ON)
/* \trace SPEC-1596 */
# include "Det.h"
#endif

#if !defined(CAN_AMD_RUNTIME_MEASUREMENT) /* COV_CAN_COMPATIBILITY */
# define CAN_AMD_RUNTIME_MEASUREMENT STD_OFF
#endif
#if (CAN_AMD_RUNTIME_MEASUREMENT == STD_ON) /* COV_CAN_AMD_RUNTIME_MEASUREMENT */
# include "AmdRtm.h"
#endif

#if !defined(CAN_RUNTIME_MEASUREMENT_SUPPORT) /* COV_CAN_COMPATIBILITY */
# define CAN_RUNTIME_MEASUREMENT_SUPPORT STD_OFF
#endif
#if (CAN_RUNTIME_MEASUREMENT_SUPPORT == STD_ON)
/* AR4-328 */
# define C_ENABLE_RUNTIME_MEASUREMENT_SUPPORT
# include "Rtm.h"
#endif

#include "vstdlib.h"

/* ECO_IGNORE_BLOCK_END */

/***************************************************************************/
/* Version Check                                                           */
/***************************************************************************/
/* \trace SPEC-20329 */
/* not the SW version but all file versions that represent the SW version are checked */
#if (CAN_COREVERSION           != 0x0900u) /* \trace SPEC-1699 */
# error "Source and Header file are inconsistent!"
#endif
#if (CAN_RELEASE_COREVERSION   != 0x01u)
# error "Source and Header file are inconsistent!"
#endif
#if defined(CAN_GEN_BASE_CFG5_VERSION) /* COV_CAN_COMPATIBILITY */
# if (CAN_GEN_BASE_CFG5_VERSION         != 0x0103u)
#  error "Source and Generated Header file are inconsistent!"
# endif
#else
# error "No CAN_GEN_BASE_CFG5_VERSION is defined"
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

/***************************************************************************/
/* Defines                                                                 */
/***************************************************************************/
#if defined(CAN_USE_NO_VECTOR_IF) /* for testability */
# define CAN_USE_CRITICALSECTION_OVER_CONFIRMATION
#else
# if defined(CANIF_VENDOR_ID) /* COV_CAN_COMPATIBILITY */
#  if (CANIF_VENDOR_ID == 0x001E) /* COV_CAN_COMPATIBILITY */
#   define CAN_USE_VECTOR_IF
#   if defined(IF_ASRIFCAN_VERSION) /* COV_CAN_COMPATIBILITY */
#    if (IF_ASRIFCAN_VERSION < 0x0410) /* COV_CAN_COMPATIBILITY */
#     define CAN_USE_CRITICALSECTION_OVER_CONFIRMATION
#    endif
#   endif
#  else
#   define CAN_USE_CRITICALSECTION_OVER_CONFIRMATION
#  endif
# else
#  define CAN_USE_CRITICALSECTION_OVER_CONFIRMATION
# endif
#endif
/* Compatibility to CBD */
/* instead of direct canCanInterruptCounter[] use Can_GetCanInterruptCounter(Index) abstraction for ComStackLib */

#if (CAN_RUNTIME_MEASUREMENT_SUPPORT == STD_ON)
# define CanHookBegin_Can_Init()                              Rtm_Start(RtmConf_RtmMeasurementPoint_Can_Init)
# define CanHookEnd_Can_Init()                                Rtm_Stop(RtmConf_RtmMeasurementPoint_Can_Init)
# define CanHookBegin_Can_SetControllerMode()                 Rtm_Start(RtmConf_RtmMeasurementPoint_Can_SetControllerMode)
# define CanHookEnd_Can_SetControllerMode()                   Rtm_Stop(RtmConf_RtmMeasurementPoint_Can_SetControllerMode)
# define CanHookBegin_Can_Write()                             Rtm_Start(RtmConf_RtmMeasurementPoint_Can_Write)
# define CanHookEnd_Can_Write()                               Rtm_Stop(RtmConf_RtmMeasurementPoint_Can_Write)

#else /* BRS runtime measurement */
# define CanHookBegin_Can_Init()
# define CanHookEnd_Can_Init()
# define CanHookBegin_Can_SetControllerMode() \

# define CanHookEnd_Can_SetControllerMode() \

# define CanHookBegin_Can_Write() \

# define CanHookEnd_Can_Write() \

#endif

# define CanHookBegin_CanHL_ReInit() \

# define CanHookEnd_CanHL_ReInit() \

#define CanHookBegin_CanHL_TxConfirmation() \

#define CanHookEnd_CanHL_TxConfirmation() \

#define CanHookBegin_CanHL_BasicCanMsgReceived() \

#define CanHookEnd_CanHL_BasicCanMsgReceived() \

#define CanHookBegin_CanHL_FullCanMsgReceived() \

#define CanHookEnd_CanHL_FullCanMsgReceived() \

#define CanHookBegin_Can_MainFunction_Write() \

#define CanHookEnd_Can_MainFunction_Write() \

#define CanHookBegin_Can_MainFunction_Read() \

#define CanHookEnd_Can_MainFunction_Read() \

#if defined (MISRA_CHECK)  /* COV_CAN_MISRA */
# pragma PRQA_MACRO_MESSAGES_OFF "CanRxActualIdRaw0",                   0310,3305          /* MD_Can_PointerCast, MD_Can_3305_LL_MsgObjectAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanRxActualDLC",                      0310,3305          /* MD_Can_PointerCast, MD_Can_3305_LL_MsgObjectAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanRxActualStdId",                    0310,3305          /* MD_Can_PointerCast, MD_Can_3305_LL_MsgObjectAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanRxActualExtId",                    0310,3305          /* MD_Can_PointerCast, MD_Can_3305_LL_MsgObjectAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanRxActualFdType",                   0310,3305          /* MD_Can_PointerCast, MD_Can_3305_LL_MsgObjectAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanRxActualIdType",                   0310,3305          /* MD_Can_PointerCast, MD_Can_3305_LL_MsgObjectAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanTxActualDLC",                      0310,3305          /* MD_Can_PointerCast, MD_Can_3305_LL_MsgObjectAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanTxActualStdId",                    0310,3305          /* MD_Can_PointerCast, MD_Can_3305_LL_MsgObjectAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanTxActualExtId",                    0310,3305          /* MD_Can_PointerCast, MD_Can_3305_LL_MsgObjectAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanTxActualFdType",                   0310,3305          /* MD_Can_PointerCast, MD_Can_3305_LL_MsgObjectAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanTxActualIdType",                   0310,3305          /* MD_Can_PointerCast, MD_Can_3305_LL_MsgObjectAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "GLOBAL_MAILBOX_ACCESS",               0303,0306          /* MD_Can_HwAccess, MD_Can_LL_HwAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "LOCAL_MAILBOX_ACCESS",                0303,0306          /* MD_Can_HwAccess, MD_Can_LL_HwAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanLL_TxIsObjFree",                   0303,0306          /* MD_Can_HwAccess, MD_Can_LL_HwAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanLL_HwIsSleep",                     0303,0306          /* MD_Can_HwAccess, MD_Can_LL_HwAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanLL_HwIsStop",                      0303,0306          /* MD_Can_HwAccess, MD_Can_LL_HwAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanLL_HwIsStopRequested",             0303,0306          /* MD_Can_HwAccess, MD_Can_LL_HwAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanLL_HwIsStart",                     0303,0306          /* MD_Can_HwAccess, MD_Can_LL_HwAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanLL_HwIsStartRequested",            0303,0306          /* MD_Can_HwAccess, MD_Can_LL_HwAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanLL_HwIsBusOff",                    0303,0306          /* MD_Can_HwAccess, MD_Can_LL_HwAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanLL_HwIsAutoRecoveryActive",        0303,0306          /* MD_Can_HwAccess, MD_Can_LL_HwAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanLL_HwIsListenOnlyMode",            0303,0306          /* MD_Can_HwAccess, MD_Can_LL_HwAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanLL_HwIsPassive",                   0303,0306          /* MD_Can_HwAccess, MD_Can_LL_HwAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanLL_HwIsWarning",                   0303,0306          /* MD_Can_HwAccess, MD_Can_LL_HwAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanRxActualErrorCounter",             0303,0310          /* MD_Can_HwAccess, MD_Can_PointerCast */
# pragma PRQA_MACRO_MESSAGES_OFF "CanTxActualErrorCounter",             0303,0310          /* MD_Can_HwAccess, MD_Can_PointerCast */
# pragma PRQA_MACRO_MESSAGES_OFF "pFlexCAN",                            0303,0306          /* MD_Can_HwAccess, MD_Can_LL_HwAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "pRXFIFO",                             0303,0306          /* MD_Can_HwAccess, MD_Can_LL_HwAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "pCanRxMask",                          0303,0306          /* MD_Can_HwAccess, MD_Can_LL_HwAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "pCanGlitchFilter",                    0303,0306          /* MD_Can_HwAccess, MD_Can_LL_HwAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "pCanParityCheck",                     0303,0306          /* MD_Can_HwAccess, MD_Can_LL_HwAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "pCanFDRegister",                      0303,0306          /* MD_Can_HwAccess, MD_Can_LL_HwAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CAN_WRITE_PROTECTED_REG",             0303,0306          /* MD_Can_HwAccess, MD_Can_LL_HwAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CAN_WRITE_PROTECTED_REG_RESET",       0303,0306          /* MD_Can_HwAccess, MD_Can_LL_HwAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CAN_WRITE_PROTECTED_REG_SET",         0303,0306          /* MD_Can_HwAccess, MD_Can_LL_HwAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CAN_READ_PROTECTED_REG",              0303,0306          /* MD_Can_HwAccess, MD_Can_LL_HwAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CAN_WRITE_PROTECTED_REG_32BIT",       0303,0306          /* MD_Can_HwAccess, MD_Can_LL_HwAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CAN_WRITE_PROTECTED_REG_RESET_32BIT", 0303,0306          /* MD_Can_HwAccess, MD_Can_LL_HwAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CAN_WRITE_PROTECTED_REG_SET_32BIT",   0303,0306          /* MD_Can_HwAccess, MD_Can_LL_HwAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CAN_READ_PROTECTED_REG_32BIT",        0303,0306          /* MD_Can_HwAccess, MD_Can_LL_HwAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CAN_WRITE_PROTECTED_REG8",            0303,0306          /* MD_Can_HwAccess, MD_Can_LL_HwAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CAN_WRITE_PROTECTED_REG16",           0303,0306          /* MD_Can_HwAccess, MD_Can_LL_HwAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CAN_WRITE_PROTECTED_REG32",           0303,0306          /* MD_Can_HwAccess, MD_Can_LL_HwAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CAN_WRITE_PROTECTED_REG8_RESET",      0303,0306          /* MD_Can_HwAccess, MD_Can_LL_HwAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CAN_WRITE_PROTECTED_REG16_RESET",     0303,0306          /* MD_Can_HwAccess, MD_Can_LL_HwAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CAN_WRITE_PROTECTED_REG32_RESET",     0303,0306          /* MD_Can_HwAccess, MD_Can_LL_HwAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CAN_WRITE_PROTECTED_REG8_SET",        0303,0306          /* MD_Can_HwAccess, MD_Can_LL_HwAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CAN_WRITE_PROTECTED_REG16_SET",       0303,0306          /* MD_Can_HwAccess, MD_Can_LL_HwAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CAN_WRITE_PROTECTED_REG32_SET",       0303,0306          /* MD_Can_HwAccess, MD_Can_LL_HwAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CAN_READ_PROTECTED_REG8",             0303,0306          /* MD_Can_HwAccess, MD_Can_LL_HwAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CAN_READ_PROTECTED_REG16",            0303,0306          /* MD_Can_HwAccess, MD_Can_LL_HwAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CAN_READ_PROTECTED_REG32",            0303,0306          /* MD_Can_HwAccess, MD_Can_LL_HwAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "assertUser",                          0303,0306          /* MD_Can_HwAccess, MD_Can_LL_HwAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "assertHardware",                      0303,0306          /* MD_Can_HwAccess, MD_Can_LL_HwAccess */
#endif

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
/* Define chiphardware                     */
/* Constants concerning can chip registers */
/* Bitmasks of FlexCAN module configuration register CANx_MCR */
#define kFlexCAN_MDIS      ((vuint16)0x8000u)       /*!< Module Disable: shut down FlexCAN clocks */
#define kFlexCAN_FRZ       ((vuint16)0x4000u)       /*!< Freeze Enable: allow entering the freeze mode */
#define kFlexCAN_FEN       ((vuint16)0x2000u)       /*!< FIFO enable */
#define kFlexCAN_HALT      ((vuint16)0x1000u)       /*!< Halt FlexCAN: request entering the freeze mode */
#define kFlexCAN_NOT_RDY   ((vuint16)0x0800u)       /*!< Not Ready: FlexCAN is in DISABLE, DOZE or STOP mode */
#define kFlexCAN_WAK_MSK   ((vuint16)0x0400u)       /*!< Wakeup Interrupt Mask: enable wakeup interrupt generation */
#define kFlexCAN_SOFT_RST  ((vuint16)0x0200u)       /*!< Soft Reset: reset FlexCAN internal state and some memory mapped registers */
#define kFlexCAN_FRZ_ACK   ((vuint16)0x0100u)       /*!< Freeze Mode Acknowledge */
#define kFlexCAN_SUPV      ((vuint16)0x0080u)       /*!< Supervisor Mode */
#define kFlexCAN_SLF_WAK   ((vuint16)0x0040u)       /*!< FlexCAN Self Wakeup by CAN bus activity */
#define kFlexCAN_WRN_EN    ((vuint16)0x0020u)       /*!< Warning Interrupt Enable */
#define kFlexCAN_LPM_ACK   ((vuint16)0x0010u)       /*!< Low Power Mode Acknowledge */
#define kFlexCAN_WAK_SRC   ((vuint16)0x0008u)       /*!< Wakeup Source: enable filtered Rx input signal */
#define kFlexCAN_DOZE      ((vuint16)0x0004u)       /*!< Doze Mode Enable: allow MCU to switch FlexCAN into DOZE low power mode */
#define kFlexCAN_NOT_DOZE  ((vuint16)0xFFFBu)       /*!< Doze Mode Disable: do not allow MCU to switch FlexCAN into DOZE low power mode */
#define kFlexCAN_SRX_DIS   ((vuint16)0x0002u)       /*!< Self Reception Disable */
#define kFlexCAN_IRMQ      ((vuint16)0x0001u)       /*!< Backwards Compatibility Configuration: enable Individual Rx Masks and queue feature */

#define kFlexCAN_LPPRIO_EN ((vuint16)0x2000u)       /*!< Local Priority Enable */
#define kFlexCAN_AEN       ((vuint16)0x1000u)       /*!< Abort Enable: enables transmit abort feature */
#define kFlexCAN_FDEN      ((vuint16)0x0800u)       /*!< CAN FD operation enable */
#define kFlexCAN_IDAM      ((vuint16)0x0300u)       /*!< ID Acceptance Mode */
#define kFlexCAN_MAXMB     ((vuint16)0x003Fu)       /*!< Maximum Number of Message Buffers: maximum number of used message buffers = MAXMB+1 */

/* Bitmasks of FlexCAN module configuration register CANx_CTRL1 */
#define kFlexCAN_BOFF_MSK  ((vuint32)0x00008000u)   /*!< FlexCAN BusOff interrupt mask */
#define kFlexCAN_LOM       ((vuint32)0x00000008u)   /*!< FlexCAN Listen Only Mode */
#define kFlexCAN_CLK_SRC   ((vuint32)0x00002000u)   /*!< FlexCAN clock source mask */
#define kFlexCAN_BOFF_REC  ((vuint32)0x00000040u)   /*!< FlexCAN auto BusOff recovery */
#define kFlexCAN_SMP       ((vuint32)0x00000080u)   /*!< FlexCAN sampling mode */

/* Bitmasks of FlexCAN module configuration register CANx_ESR */
#define kFlexCAN_WAKE_INT   (vuint32)0x00000001u    /*!< Wake Up interrupt flag */
#define kFlexCAN_ERR_INT    (vuint32)0x00000002u    /*!< Error interrupt flag */
#define kFlexCAN_BOFF_INT   (vuint32)0x00000004u    /*!< Bus Off interrupt flag */
#define kFlexCAN_FCS_BOFF   (vuint32)0x00000020u    /*!< Fault Confinement State value for BusOff */
#define kFlexCAN_FCS_EP     (vuint32)0x00000010u    /*!< Fault Confinement State value for ErrorPassive */
#define kFlexCAN_FCS        (vuint32)0x00000030u    /*!< Fault Confinement State */
#define kFlexCAN_RXTX_WARN  (vuint32)0x00000300u
#define kFlexCAN_STATUS_INT (kFlexCAN_BOFF_INT | kFlexCAN_ERR_INT | kFlexCAN_WAKE_INT)

#define kFlexCAN_MCR_REQ_ONLY_BITS (kFlexCAN_MDIS | kFlexCAN_FRZ | kFlexCAN_HALT)
#define kFlexCAN_MCR               (kFlexCAN_MDIS | kFlexCAN_FRZ | kFlexCAN_HALT | kFlexCAN_NOT_RDY | kFlexCAN_FRZ_ACK | kFlexCAN_LPM_ACK)
#define kFlexCAN_FREEZE_MODE       (kFlexCAN_FRZ | kFlexCAN_HALT | kFlexCAN_NOT_RDY | kFlexCAN_FRZ_ACK) /* FlexCAN in FREEZE mode: FRZ, HALT, NOT_RDY and FRZ_ACK bit are set */
#define kFlexCAN_FREEZE_MODE_REQ   (kFlexCAN_FRZ | kFlexCAN_HALT)
#define kFlexCAN_STOP_MODE         (kFlexCAN_NOT_RDY | kFlexCAN_LPM_ACK) /* FlexCAN in STOP powerdown mode: NOT_RDY and LPM_ACK bits set */
#define kFlexCAN_DISABLE_MODE      (kFlexCAN_MDIS | kFlexCAN_NOT_RDY | kFlexCAN_LPM_ACK) /* FlexCAN in DISABLE powerdown mode: MDIS, NOT_RDY and LPM_ACK bit are set */
#define kFlexCAN_NORMAL_MODE       ((vuint16)0x0000u) /* relevant bits for mode states must all be negated for NORMAL mode */
#define kFlexCAN_NORMAL_MODE_REQ   ((vuint16)0x0000u)
/* FlexCAN is DISABLED, independent from FREEZE mode:
  -> MDIS and LPM_ACK bit are necessary to identify DISABLE mode
  -> NOT_RDY must not be checked because it also influenced by FREEZE mode 
*/
#define kFlexCAN_DISABLE_ONLY_BITS (kFlexCAN_MDIS | kFlexCAN_LPM_ACK)
#define kNotFlexCAN_MCR_CFG_BTIS   (kFlexCAN_MCR | kFlexCAN_SOFT_RST | kFlexCAN_SUPV) /* user configurable bits are '0', not changeable bits are '1' */


#define kNotFlexCANErrBoff ((vuint32)0xFFFF3FFFu)

#define CANSFR_CLEAR      ((vuint32)0x00000000u)
#define CANSFR_SET        ((vuint32)0xFFFFFFFFu)

/* Macros to access the CODE-bits in the control/status word ------------------*/
#define kCodeMask         ((vuint16)0x0F00u)     /*!< Mask to access the CODE in the control/status word */
#define kNotDlcMask       ((vuint16)0xFF00u)
#define kNotCodeMask      ((vuint16)0xF0FFu)

/* Code definitions for receive objects */
#define kRxCodeEmpty      ((vuint16)0x0400u)    /*!< Message buffer is active and empty */
#define kRxCodeClear      ((vuint16)0x00F0u)    /*!< Mask to clear control register but leave the ID type */
#define kRxCodeOverrun    ((vuint16)0x0600u)    /*!< Second frame was received into a full buffer */
#define kRxCodeBusy       ((vuint16)0x0100u)    /*!< Receive buffer locked */

/* Code definitions for transmit objects */
#define kTxCodeTransmit     ((vuint16)0x0C40u)     /*!< transmit request in nominal bit rate  */
#define kTxCodeTransmitFD   ((vuint16)0xCC40u)     /*!< transmit request for CAN-FD: EDL (extended data length) and BRS (bit rate switch) bit must be set */
#define kNotIDEMask         ((vuint16)0xFF0Fu)
#define kTxDlcMask          ((vuint16)0x006Fu)     /*!< Mask to access the DLC in the control/status word */
#define kTxCodeFree         ((vuint16)0x0800u)     /*!< Transmit object free */
#define kTxCodeAbort        ((vuint16)0x0900u)     /*!< Abort message transmission */

#if defined( C_ENABLE_EXTENDED_ID )
# define kTxCodeInactive  ((vuint16)0x0820u)       /*!< Transmit object inactive for extended or mixed IDs */
#else
# define kTxCodeInactive  ((vuint16)0x0800u)       /*!< Transmit object inactive for standard IDs */
#endif

/* Code definitions for Rx FiFo ---------------------------- */
#define kRxFIFO_OVERRUN     (vuint32)0x00000080u  /*!< RxFIFO overrun (iflag1) */
#define kRxFIFO_WARN        (vuint32)0x00000040u  /*!< RxFIFO warning (iflag1) */
#define kRxFIFO_NEWMSG      (vuint32)0x00000020u  /*!< RxFIFO new message available (iflag1) */
#define kRxFIFO_EXT         (vuint32)0x40000000u  /*!< RxFIFO extended ID (ID tab element) */
#define kRxFIFO_REM         (vuint32)0x80000000u  /*!< RxFIFO remote frame (ID tab element) */
#define kRxFIFO_MASK        (vuint32)0xC0000000u  /*!< RxFIFO mask for ID tab element */

# define C_FLEXCAN_RXFIFO_MAXLOOP  6u  /*!< 6 RX Fifo elements available */

/* Code definitions for ctrl2 register ------------------- */
#define kFlexCAN_ECRWRE         (vuint32)0x20000000u  /*!< Enables write access to MECR register */
#define kFlexCAN_MRP            (vuint32)0x00040000u  /*!< Matching process starts from mailboxes and continues on Rx FIFO */
#define kFlexCAN_RRS            (vuint32)0x00020000u  /*!< Remote request frame is stored */
#define kFlexCAN_EACEN          (vuint32)0x00010000u  /*!< Enables the comparison of IDE and RTR bit */
#define kFlexCAN_TASD_DEFAULT   (vuint32)0x00800000u  /*!< TASD default value */
#define kFlexCAN_STFCNTEN       (vuint32)0x00001000u  /*!< Enables ISO CAN FD */

/* Code definitions for mecr  register ------------------- */
#define kFlexCAN_ECRWRDIS       (vuint32)0x80000000u  /*!< Disable MECR write */
#define kFlexCAN_RERRDIS        (vuint32)0x00000200u  /*!< Disable Error Report */
#define kFlexCAN_ECCDIS         (vuint32)0x00000100u  /*!< Disable Error Correction */
#define kFlexCAN_Disable_ParityCheck (kFlexCAN_RERRDIS | kFlexCAN_ECCDIS) /* Disable Parity Check */
#define kFlexCAN_Clear_Parity_Status (vuint32)0x000D000Du /* Clear Status register */

#define kExtIDBit               (vuint32)0x80000000u


#define kCanRxMaskStd     ((vuint32)0xDFFC0000u)
#if defined( C_ENABLE_EXTENDED_ID )
#  define kCanRxMaskExt   ((vuint32)0xDFFFFFFFu)
#endif

#if defined( C_ENABLE_EXTENDED_ID )
# define CAN_MSGID(x) (vuint32)(x) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#else
# define CAN_MSGID(x) ((vuint32)(x) << 16) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#endif

#define kCanRxFifoIntUnmask   ((vuint32)0xFFFFFF00u)

#define kCanMaskAll32 0xFFFFFFFFu
#define kCanMaskAll16 0xFFFFu

/* all bits of CAN[MCR].MCR except mode and reserved bits */  
#define kCanRamCheckMaskMCR         0x24EBu

#if defined ( C_ENABLE_MB96TO127 ) || defined ( C_ENABLE_MB64TO95 ) /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
# define maxmbMask                  0x007Fu
#else
# define maxmbMask                  0x003Fu
#endif

/* all bits of CAN[MCR].MAXMB except unused/reserved bits */  
#if defined( C_ENABLE_CAN_FD_USED )
# define kCanRamCheckMaskMAXMB      (0x3300u | kFlexCAN_FDEN | maxmbMask)
#else
# define kCanRamCheckMaskMAXMB      (0x3300u | maxmbMask)
#endif

#define kCanRamCheckMailboxControl  0x0F7Fu

#if defined( C_ENABLE_CAN_RAM_CHECK_EXTENDED )

# if defined( C_ENABLE_EXTENDED_BITTIMING ) /* COV_CAN_FLEXCAN3_DERIVATIVE_EXTENDED_BITTIMING */
/* mask for CAN_CTRL1 register check */
#  define kCanRamCheckMaskCONTROL1               0x0000DCF8u
# else
/* mask for CAN_CTRL1 register check */
#  define kCanRamCheckMaskCONTROL1               0xFFFFDCFFu
# endif

/* mask for CAN_ECR register check */
# define kCanRamCheckMaskECR                    0x0000FFFFu

/* mask for CAN_CBT register check */
# define kCanRamCheckMaskCBT                    0xFFEFFFFFu

# if defined( C_ENABLE_GLITCH_FILTER )
/* mask for CAN_GFWR register check */
#  define kCanRamCheckMaskGFWR                  0x000000FFu
# endif

# if defined ( C_ENABLE_FLEXCAN_PARITY_CHECK_AVAILABLE )
/* mask for CAN_CTRL2 register check */
#  define kCanRamCheckMaskCTRL2                0x3FFF0000u
/* mask for CAN_MECR register check */
#  define kCanRamCheckMaskMECR                 0x0001E380u
# else
/* mask for CAN_CTRL2 register check */
#  define kCanRamCheckMaskCTRL2                 0x0FFF0000u
# endif

/* configuration check */
# if !defined( C_ENABLE_CAN_RAM_CHECK )
#  error "C_ENABLE_CAN_RAM_CHECK has to be defined if C_ENABLE_CAN_RAM_CHECK_EXTENDED is set."
# endif

#endif /* C_ENABLE_CAN_RAM_CHECK_EXTENDED */

#define CanBswap32(x)                   (vuint32)  (( ((vuint32)((x) & 0xFF000000u)) >> 24) | /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */ \
                                                    ( ((vuint32)((x) & 0x00FF0000u)) >>  8) | \
                                                    ( ((vuint32)((x) & 0x0000FF00u)) <<  8) | \
                                                    ( ((vuint32)((x) & 0x000000FFu)) << 24))      /* swap b4-b3-b2-b1 to b1-b2-b3-b4 */

/* FlexCAN LL Transition States */
#define kCanLLStateStart                        0u
#define kCanLLStateRequested                    1u

/***************************************************************************/
/* macros                                                                  */
/***************************************************************************/
/* PRQA S 3453 FctLikeMacroLabel */ /* MD_MSR_FctLikeMacro */

/* for LL compatibility */
/* hw handles */
#define CAN_HL_HW_TX_NORMAL_INDEX(hwch)     (Can_GetTxBasicHwStart(hwch)) 
#if defined(CAN_HL_HW_LAYOUT_TXBASIC_FIRST) /* COV_CAN_HW_LAYOUT_TXBASIC_FIRST */
# define CAN_HL_HW_TX_STARTINDEX(hwch)      (Can_GetTxBasicHwStart(hwch))
#else
# define CAN_HL_HW_TX_STARTINDEX(hwch)      (Can_GetTxFullHwStart(hwch))
#endif
#define CAN_HL_HW_TX_FULL_STARTINDEX(hwch)  (Can_GetTxFullHwStart(hwch))
#define CAN_HL_HW_UNUSED_STARTINDEX(hwch)   (Can_GetUnusedHwStart(hwch))
#define CAN_HL_HW_RX_FULL_STARTINDEX(hwch)  (Can_GetRxFullHwStart(hwch))
#define CAN_HL_HW_RX_BASIC_STARTINDEX(hwch) (Can_GetRxBasicHwStart(hwch))
#if defined(CAN_HL_HW_LAYOUT_TXBASIC_FIRST) /* COV_CAN_HW_LAYOUT_TXBASIC_FIRST */
# define CAN_HL_HW_TX_STOPINDEX(hwch)       (Can_GetTxFullHwStop(hwch))
#else
# define CAN_HL_HW_TX_STOPINDEX(hwch)       (Can_GetTxBasicHwStop(hwch))
#endif
#define CAN_HL_HW_TX_FULL_STOPINDEX(hwch)   (Can_GetTxFullHwStop(hwch))
#define CAN_HL_HW_UNUSED_STOPINDEX(hwch)    (Can_GetUnusedHwStop(hwch))
#define CAN_HL_HW_RX_FULL_STOPINDEX(hwch)   (Can_GetRxFullHwStop(hwch))
#define CAN_HL_HW_RX_BASIC_STOPINDEX(hwch)  (Can_GetRxBasicHwStop(hwch))
/* mailbox handles */
#define CAN_HL_MB_RX_FULL_STARTINDEX(hwch)  (Can_GetRxFullHandleStart(hwch))
#define CAN_HL_MB_RX_BASIC_STARTINDEX(hwch) (Can_GetRxBasicHandleStart(hwch))
#define CAN_HL_MB_TX_FULL_STARTINDEX(hwch)  (Can_GetTxFullHandleStart(hwch))
#define CAN_HL_MB_TX_BASIC_STARTINDEX(hwch) (Can_GetTxBasicHandleStart(hwch))
#define CAN_HL_MB_RX_FULL_STOPINDEX(hwch)   (Can_GetRxFullHandleStop(hwch))
#define CAN_HL_MB_RX_BASIC_STOPINDEX(hwch)  (Can_GetRxBasicHandleStop(hwch))
#define CAN_HL_MB_TX_FULL_STOPINDEX(hwch)   (Can_GetTxFullHandleStop(hwch))
#define CAN_HL_MB_TX_BASIC_STOPINDEX(hwch)  (Can_GetTxBasicHandleStop(hwch))

#if defined(C_ENABLE_CAN_RAM_CHECK)
# if !defined(CAN_RAM_CHECK_MAILBOX_RESULT) /* May be defined by test suite to stimulate RAM_CHECK failure */
#  if defined( C_SINGLE_RECEIVE_CHANNEL )
#   define CAN_RAM_CHECK_MAILBOX_RESULT(ch, initParaPtr) CanLL_InitIsMailboxCorrupt((initParaPtr))
#  else
#   define CAN_RAM_CHECK_MAILBOX_RESULT(ch, initParaPtr) CanLL_InitIsMailboxCorrupt((ch), (initParaPtr))
#  endif
# endif
# if !defined(CAN_RAM_CHECK_FINISHED_CTP) /* May be defined by test suite to check RAM_CHECK finished / executed */
#  define CAN_RAM_CHECK_FINISHED_CTP(ch)
# endif
#endif
#if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
# if !defined(CAN_RAM_CHECK_BEGIN_REG_RESULT) /* May be defined by test suite to stimulate RAM_CHECK_EXTENDED failure */
#  if defined( C_SINGLE_RECEIVE_CHANNEL )
#   define CAN_RAM_CHECK_BEGIN_REG_RESULT(ch, initParaPtr) CanLL_InitBeginIsRegisterCorrupt((initParaPtr))
#  else
#   define CAN_RAM_CHECK_BEGIN_REG_RESULT(ch, initParaPtr) CanLL_InitBeginIsRegisterCorrupt((ch), (initParaPtr))
#  endif
# endif
# if !defined(CAN_RAM_CHECK_END_REG_RESULT) /* May be defined by test suite to stimulate RAM_CHECK_EXTENDED failure */
#  if defined( C_SINGLE_RECEIVE_CHANNEL )
#   define CAN_RAM_CHECK_END_REG_RESULT(ch, initParaPtr) CanLL_InitEndIsRegisterCorrupt((initParaPtr))
#  else
#   define CAN_RAM_CHECK_END_REG_RESULT(ch, initParaPtr) CanLL_InitEndIsRegisterCorrupt((ch), (initParaPtr))
#  endif
# endif
# if !defined(CAN_RAM_CHECK_READ_BACK_RESULT) /* May be defined by test suite to stimulate RAM_CHECK_EXTENDED failure */
#  define CAN_RAM_CHECK_READ_BACK_RESULT(ch)
# endif
#endif

#define CanHL_IsStart(ch) ((Can_GetLogStatus(ch) & CAN_STATUS_START) == CAN_STATUS_START)
#define CanHL_IsSleep(ch) ((Can_GetLogStatus(ch) & CAN_STATUS_SLEEP) == CAN_STATUS_SLEEP)
#define CanHL_IsStop(ch) ((Can_GetLogStatus(ch) & CAN_STATUS_STOP) == CAN_STATUS_STOP)
#define CanHL_IsBusOff(ch) (Can_IsIsBusOff(ch))
#define CanHL_IsControllerInit(ch) ((Can_GetLogStatus(ch) & CAN_STATUS_INIT) == CAN_STATUS_INIT)

#if defined(C_ENABLE_CAN_FD_USED) /* also for BRS because DLC may be bigger than 8 and will be checked by CanIf */
# define CAN_DLC2LEN(dlc) (Can_DlcToFrameLenght[((uint8)(dlc)) & ((uint8)0xFu)])
# define CAN_LEN2DLC(length) ((uint8)Can_MessageLengthToDlc[(length)])
#else
# define CAN_DLC2LEN(dlc) (dlc)
# define CAN_LEN2DLC(length) (length)
#endif
#if defined(C_ENABLE_CAN_FD_FULL)
# define CAN_MAX_DATALEN_OBJ(Index) Can_GetMailboxDataLen(Index)
#else
# define CAN_MAX_DATALEN_OBJ(Index) 8u
#endif
#define CanHL_IsFdMessage(id) (((id) & (Can_IdType)CAN_ID_FD_MASK) == (Can_IdType)CAN_ID_FD_MASK) /* \trace SPEC-60432, SPEC-50586 */
#define CanHL_IsFdTxBrs(ch)   (Can_GetInitObjectFdBrsConfig(Can_GetLastInitObject(ch)) == CAN_FD_RXTX) /* \trace SPEC-60432, SPEC-50586 */

/* PRQA L:FctLikeMacroLabel */

/* PRQA S 3453 FctLikeMacroLabel */ /* MD_MSR_FctLikeMacro */

# define CANDRV_SET_CODE_TEST_POINT(x)

#if defined( C_ENABLE_HW_LOOP_TIMER )
# if defined( C_SINGLE_RECEIVE_CHANNEL )
#  define   CanLL_ApplCanTimerStart(loop)   ApplCanTimerStart(loop)
#  define   CanLL_ApplCanTimerLoop(loop)    ApplCanTimerLoop(loop)
#  define   CanLL_ApplCanTimerEnd(loop)     ApplCanTimerEnd(loop)
# else
#  define   CanLL_ApplCanTimerStart(loop)   ApplCanTimerStart(channel, (loop))
#  define   CanLL_ApplCanTimerLoop(loop)    ApplCanTimerLoop(channel, (loop))
#  define   CanLL_ApplCanTimerEnd(loop)     ApplCanTimerEnd(channel, (loop))
# endif
#else
# define   CanLL_ApplCanTimerStart(loop)
# define   CanLL_ApplCanTimerLoop(loop)     CAN_OK
# define   CanLL_ApplCanTimerEnd(loop)
#endif

#if defined ( C_ENABLE_USER_MODE_OS )
# define CAN_AREA(ch) Can_GetProtectedAreaId(ch)
#else
  /* dummy area */
# define CAN_AREA(ch) 0
#endif

#if defined ( C_ENABLE_USER_MODE_OS )
# define CAN_WRITE_PROTECTED_REG(reg, val)              osWritePeripheral16(CAN_AREA(canHwChannel), (vuint32)&(reg), (val))
# define CAN_WRITE_PROTECTED_REG_RESET(reg, bits)       osModifyPeripheral16(CAN_AREA(canHwChannel), (vuint32)&(reg), (vuint16)(~(bits)), (vuint16)0x0000u)
# define CAN_WRITE_PROTECTED_REG_SET(reg, bits)         osModifyPeripheral16(CAN_AREA(canHwChannel), (vuint32)&(reg), (vuint16)0xFFFFu, (bits))
# define CAN_READ_PROTECTED_REG(reg)                    osReadPeripheral16(CAN_AREA(canHwChannel), (vuint32)&(reg))
# define CAN_WRITE_PROTECTED_REG_32BIT(reg, val)        osWritePeripheral32(CAN_AREA(canHwChannel), (vuint32)&(reg), (val))
# define CAN_WRITE_PROTECTED_REG_RESET_32BIT(reg, bits) osModifyPeripheral32(CAN_AREA(canHwChannel), (vuint32)&(reg), (vuint32)(~(bits)), (vuint32)0x00000000u)
# define CAN_WRITE_PROTECTED_REG_SET_32BIT(reg, bits)   osModifyPeripheral32(CAN_AREA(canHwChannel), (vuint32)&(reg), (vuint32)0xFFFFFFFFu, (bits))
# define CAN_READ_PROTECTED_REG_32BIT(reg)              osReadPeripheral32(CAN_AREA(canHwChannel), (vuint32)&(reg))
#elif defined ( C_ENABLE_USER_MODE_APPL )
# define CAN_WRITE_PROTECTED_REG(reg, val)              ApplCanWriteProtectedRegister16(&(reg), (vuint16)0xFFFFu, (val))
# define CAN_WRITE_PROTECTED_REG_RESET(reg, bits)       ApplCanWriteProtectedRegister16(&(reg), (bits), (vuint16)0x0000u)
# define CAN_WRITE_PROTECTED_REG_SET(reg, bits)         ApplCanWriteProtectedRegister16(&(reg), (bits), (bits))
# define CAN_READ_PROTECTED_REG(reg)                    ApplCanReadProtectedRegister16(&(reg))
# define CAN_WRITE_PROTECTED_REG_RESET_32BIT(reg, bits) ApplCanWriteProtectedRegister32(&(reg), (bits), (vuint32)0x00000000u)
# define CAN_WRITE_PROTECTED_REG_SET_32BIT(reg, bits)   ApplCanWriteProtectedRegister32(&(reg), (bits), (bits))
# define CAN_READ_PROTECTED_REG_32BIT(reg)              ApplCanReadProtectedRegister32(&(reg))
#else
# define CAN_WRITE_PROTECTED_REG(reg, val)              (reg) = (val)
# define CAN_WRITE_PROTECTED_REG_RESET(reg, bits)       (reg) &= (vuint16)(~(bits))
# define CAN_WRITE_PROTECTED_REG_SET(reg, bits)         (reg) |= (bits)
# define CAN_READ_PROTECTED_REG(reg)                    (reg)
# define CAN_WRITE_PROTECTED_REG_RESET_32BIT(reg, bits) (reg) &= (vuint32)(~(bits))
# define CAN_WRITE_PROTECTED_REG_SET_32BIT(reg, bits)   (reg) |= (bits)
# define CAN_READ_PROTECTED_REG_32BIT(reg)              (reg)
#endif

#if defined( C_ENABLE_CAN_RXTX_INTERRUPT )
# define   CAN_DISABLE_RXTX_INTERRUPT_0TO31(canFlagPtr) (canFlagPtr)->flags1 = pFlexcan->imask1; pFlexcan->imask1 = 0u
# define   CAN_RESTORE_RXTX_INTERRUPT_0TO31(canFlag)    pFlexcan->imask1 = (canFlag).flags1
# if defined ( C_ENABLE_MB32TO63 ) /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
#  define   CAN_DISABLE_RXTX_INTERRUPT_32TO63(canFlagPtr) (canFlagPtr)->flags2 = pFlexcan->imask2; pFlexcan->imask2 = 0u
#  define   CAN_RESTORE_RXTX_INTERRUPT_32TO63(canFlag)    pFlexcan->imask2 = (canFlag).flags2
# else
#  define   CAN_DISABLE_RXTX_INTERRUPT_32TO63(canFlagPtr)
#  define   CAN_RESTORE_RXTX_INTERRUPT_32TO63(canFlag)
# endif
# if defined ( C_ENABLE_MB64TO95 ) /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
#  define   CAN_DISABLE_RXTX_INTERRUPT_64TO95(canFlagPtr) (canFlagPtr)->flags3 = pFlexcan->imask3; pFlexcan->imask3 = 0u
#  define   CAN_RESTORE_RXTX_INTERRUPT_64TO95(canFlag)    pFlexcan->imask3 = (canFlag).flags3
# else
#  define   CAN_DISABLE_RXTX_INTERRUPT_64TO95(canFlagPtr)
#  define   CAN_RESTORE_RXTX_INTERRUPT_64TO95(canFlag)
# endif
# if defined ( C_ENABLE_MB96TO127 ) /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
#  define   CAN_DISABLE_RXTX_INTERRUPT_96TO127(canFlagPtr) (canFlagPtr)->flags4 = pFlexcan->imask4; pFlexcan->imask4 = 0u
#  define   CAN_RESTORE_RXTX_INTERRUPT_96TO127(canFlag)    pFlexcan->imask4 = (canFlag).flags4
# else
#  define   CAN_DISABLE_RXTX_INTERRUPT_96TO127(canFlagPtr)
#  define   CAN_RESTORE_RXTX_INTERRUPT_96TO127(canFlag)
# endif
#else
# define   CAN_DISABLE_RXTX_INTERRUPT_0TO31(canFlagPtr)
# define   CAN_RESTORE_RXTX_INTERRUPT_0TO31(canFlag)
# define   CAN_DISABLE_RXTX_INTERRUPT_32TO63(canFlagPtr)
# define   CAN_RESTORE_RXTX_INTERRUPT_32TO63(canFlag)
# define   CAN_DISABLE_RXTX_INTERRUPT_64TO95(canFlagPtr)
# define   CAN_RESTORE_RXTX_INTERRUPT_64TO95(canFlag)
# define   CAN_DISABLE_RXTX_INTERRUPT_96TO127(canFlagPtr)
# define   CAN_RESTORE_RXTX_INTERRUPT_96TO127(canFlag)
#endif

#if defined( C_ENABLE_CAN_BUSOFF_INTERRUPT )
# define CAN_DISABLE_BUSOFF_INTERRUPT(canFlagPtr)  (canFlagPtr)->canctrl1 = pFlexcan->control1; pFlexcan->control1 &= kNotFlexCANErrBoff
# define CAN_RESTORE_BUSOFF_INTERRUPT(canFlag)     pFlexcan->control1 |= (vuint32)((canFlag).canctrl1 & (vuint32)(~kNotFlexCANErrBoff))
#else
# define CAN_DISABLE_BUSOFF_INTERRUPT(canFlagPtr)
# define CAN_RESTORE_BUSOFF_INTERRUPT(canFlag)
#endif

# define CAN_DISABLE_WAKEUP_INTERRUPT(canFlagPtr)
# define CAN_RESTORE_WAKEUP_INTERRUPT(canFlag)

/*
|<DataModelStart>| CanLL_TxIsObjFree
Relation_Context:
Relation:
ChannelAmount, TxBasicAmount
ChannelAmount, TxFullAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
#define CanLL_TxIsObjFree(hwCh, txObjHandle) ((GLOBAL_MAILBOX_ACCESS((hwCh), (txObjHandle), control) & kCodeMask) == kTxCodeFree)

/*
|<DataModelStart>| CanLL_HwIsSleep
Relation_Context:
Relation:
Wakeup, OneChOpt, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
# define CanLL_HwIsSleep(hwCh)  (kCanFalse != kCanFalse)

/*
|<DataModelStart>| CanLL_HwIsStop
Relation_Context:
Relation:
OneChOpt, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
#define CanLL_HwIsStop(hwCh) ((CAN_READ_PROTECTED_REG((pFlexCAN(hwCh))->canmcr) & kFlexCAN_MCR) == kFlexCAN_FREEZE_MODE)

/*
|<DataModelStart>| CanLL_HwIsStopRequested
Relation_Context:
Relation:
OneChOpt, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
#define CanLL_HwIsStopRequested(hwCh) ((CAN_READ_PROTECTED_REG((pFlexCAN(hwCh))->canmcr) & kFlexCAN_MCR_REQ_ONLY_BITS) == kFlexCAN_FREEZE_MODE_REQ)

/*
|<DataModelStart>| CanLL_HwIsStart
Relation_Context:
Relation:
OneChOpt, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
#define CanLL_HwIsStart(hwCh) ((CAN_READ_PROTECTED_REG((pFlexCAN(hwCh))->canmcr) & kFlexCAN_MCR) == kFlexCAN_NORMAL_MODE)

/*
|<DataModelStart>| CanLL_HwIsStartRequested
Relation_Context:
Relation:
OneChOpt, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
#define CanLL_HwIsStartRequested(hwCh) ((CAN_READ_PROTECTED_REG((pFlexCAN(hwCh))->canmcr) & kFlexCAN_MCR_REQ_ONLY_BITS) == kFlexCAN_NORMAL_MODE_REQ)

/*
|<DataModelStart>| CanLL_HwIsBusOff
Relation_Context:
Relation:
OneChOpt, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
#define CanLL_HwIsBusOff(hwCh) (((pFlexCAN(hwCh))->estat & kFlexCAN_FCS_BOFF) != 0u)

/*
|<DataModelStart>| CanLL_HwIsListenOnlyMode
Relation_Context:
Relation:
OneChOpt, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
#define CanLL_HwIsAutoRecoveryActive(hwCh) (((pFlexCAN(hwCh))->control1 &  kFlexCAN_BOFF_REC) == 0u)

/*
|<DataModelStart>| CanLL_HwIsListenOnlyMode
Relation_Context:
Relation:
OneChOpt, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
#define CanLL_HwIsListenOnlyMode(hwCh) (((pFlexCAN(hwCh))->control1 & kFlexCAN_LOM) != 0u)

#if defined( C_ENABLE_EXTENDED_STATUS )
/*
|<DataModelStart>| CanLL_HwIsPassive
Relation_Context:
Relation:
CanGetStatus, OneChOpt, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
#  define CanLL_HwIsPassive(hwCh) (((pFlexCAN(hwCh))->estat & kFlexCAN_FCS) == kFlexCAN_FCS_EP)

/*
|<DataModelStart>| CanLL_HwIsWarning
Relation_Context:
Relation:
CanGetStatus, OneChOpt, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
#  define CanLL_HwIsWarning(hwCh) (((pFlexCAN(hwCh))->estat & kFlexCAN_RXTX_WARN) != 0u)
#endif /* C_ENABLE_EXTENDED_STATUS */



#define CanBitMask(x)      ((vuint32)((vuint32)0x01u << ((x) & (0x1Fu))))
#define CanInvBitMask(x)   ((vuint32)~((vuint32)0x01u << ((x) & (0x1Fu))))

/* PRQA L:FctLikeMacroLabel */

/***************************************************************************/
/* Constants                                                               */
/***************************************************************************/
#define CAN_START_SEC_CONST_UNSPECIFIED  /*--------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/* BR:012 */
V_DEF_CONST(V_NONE, uint8, CONST) Can_MainVersion         = (uint8)CAN_SW_MAJOR_VERSION; /* PRQA S 3408 */ /* MD_Can_ExternalScope */
V_DEF_CONST(V_NONE, uint8, CONST) Can_SubVersion          = (uint8)CAN_SW_MINOR_VERSION; /* PRQA S 3408 */ /* MD_Can_ExternalScope */
V_DEF_CONST(V_NONE, uint8, CONST) Can_ReleaseVersion      = (uint8)CAN_SW_PATCH_VERSION; /* PRQA S 3408 */ /* MD_Can_ExternalScope */


#if defined(C_ENABLE_CAN_FD_USED)
V_DEF_CONST(CAN_STATIC, uint8, CONST) Can_DlcToFrameLenght[16] = /* PRQA S 3218,3408 */ /* MD_Can_GlobalScope */
{
  0u,  1u,  2u,  3u,
  4u,  5u,  6u,  7u,
  8u, 12u, 16u, 20u,
 24u, 32u, 48u, 64u
};
V_DEF_CONST(CAN_STATIC, uint8, CONST) Can_MessageLengthToDlc[65] = /* PRQA S 3218,3408 */ /* MD_Can_GlobalScope */
{
/* 00..07 */  0u,  1u,  2u,  3u,  4u,  5u,  6u,  7u,
/* 08..15 */  8u,  9u,  9u,  9u,  9u, 10u, 10u, 10u,
/* 16..23 */ 10u, 11u, 11u, 11u, 11u, 12u, 12u, 12u,
/* 24..31 */ 12u, 13u, 13u, 13u, 13u, 13u, 13u, 13u,
/* 32..39 */ 13u, 14u, 14u, 14u, 14u, 14u, 14u, 14u,
/* 40..47 */ 14u, 14u, 14u, 14u, 14u, 14u, 14u, 14u,
/* 48..55 */ 14u, 15u, 15u, 15u, 15u, 15u, 15u, 15u,
/* 56..63 */ 15u, 15u, 15u, 15u, 15u, 15u, 15u, 15u,
/* 64     */ 15u
};
#endif

/* Global constants with CAN driver main and subversion */

#if defined( C_ENABLE_CAN_RAM_CHECK )
/* ROM CATEGORY 4 START */
/* test bit patterns for (Extended) RAM check */
V_DEF_CONST(CAN_STATIC, vuint32, CONST) ramCheckPattern32[3] = /* PRQA S 3218 */ /* MD_Can_GlobalScope */
{
  0xAAAAAAAAu, 0x55555555u, 0x00000000u
};
/* ROM CATEGORY 4 END */
#endif

#if defined( C_ENABLE_CAN_RAM_CHECK_EXTENDED )
/* ROM CATEGORY 4 START */
/* additional test bit patterns for Extended RAM check */
V_DEF_CONST(CAN_STATIC, vuint16, CONST) ramCheckPattern16[3] = /* PRQA S 3218 */ /* MD_Can_GlobalScope */
{
  0xAAAAu, 0x5555u, 0x0000u
};
/* ROM CATEGORY 4 END */
#endif


#define CAN_STOP_SEC_CONST_UNSPECIFIED  /*---------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/***************************************************************************/
/* global data definitions                                                 */
/***************************************************************************/
#define CAN_START_SEC_VAR_NOINIT_UNSPECIFIED  /*---------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/***************************************************************************************/
/* local data definitions   (need also INFIX because STATIC may be defined to nothing) */
/***************************************************************************************/
/* \trace SPEC-1585 */
/*! Semaphore to block reentrancy for Can_MainFunction_Read() */
V_DEF_VAR(CAN_STATIC, uint8, VAR_NOINIT) canIsRxTaskLocked; /* PRQA S 3408 */ /* MD_Can_GlobalScope */

/* Can LL Init State variable */


#if ( CAN_REINIT_START == STD_ON )
/* RAM CATEGORY 1 START */
V_DEF_VAR(CAN_STATIC volatile, vuint8, VAR_NOINIT) canLL_canStartReinitState[kCanNumberOfChannels]; /* SBSW_CAN_LL14 */
/* RAM CATEGORY 1 END */
#endif

#if defined( C_ENABLE_UPDATE_BASE_ADDRESS )
/* RAM CATEGORY 1 START */
V_DEF_P2VAR(V_NONE, vuint32, VAR_NOINIT, REG_CANCELL) canLL_VirtualPtrField[kCanNumberOfHwChannels]; /* PRQA S 3408 */ /* MD_Can_ExternalScope */
/* RAM CATEGORY 1 END */
#endif
#if defined (C_ENABLE_HW_LOOP_TIMER)
/* RAM CATEGORY 1 START */
V_DEF_VAR(CAN_STATIC volatile, vuint8, VAR_NOINIT) canLL_FlexCANInitResultNeeded[kCanNumberOfHwChannels];
/* RAM CATEGORY 1 END */
#endif

#define CAN_STOP_SEC_VAR_NOINIT_UNSPECIFIED  /*----------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

# define CAN_START_SEC_VAR_INIT_UNSPECIFIED  /*-----------------------------*/
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/* ! Mark module to be initialized (used to check double/none initialization) */
V_DEF_VAR(CAN_STATIC, uint8, VAR_INIT) canConfigInitFlag = CAN_STATUS_UNINIT; /* PRQA S 3408 */ /* MD_Can_ExternalScope */
# define CAN_STOP_SEC_VAR_INIT_UNSPECIFIED  /*------------------------------*/
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/* not static because of debug/test usage */
#if defined(CAN_ENABLE_USE_INIT_ROOT_POINTER)
# define CAN_START_SEC_VAR_INIT_UNSPECIFIED  /*-----------------------------*/
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*! Pointer to the current configuration */
V_DEF_P2CONST (V_NONE, Can_ConfigType, VAR_INIT, CONST_PBCFG) Can_ConfigDataPtr = NULL_PTR; /* UREQ00035484 */ /* PRQA S 3408 */ /* MD_Can_ExternalScope */
# define CAN_STOP_SEC_VAR_INIT_UNSPECIFIED  /*------------------------------*/
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
#else
# define CAN_START_SEC_CONST_UNSPECIFIED  /*--------------------------------*/
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*! Pointer to the current configuration */
V_DEF_CONSTP2CONST(V_NONE, Can_ConfigType, CONST, CONST_PBCFG) Can_ConfigDataPtr = NULL_PTR; /* PRQA S 3408,1514 */ /* MD_Can_ExternalScope */
# define CAN_STOP_SEC_CONST_UNSPECIFIED  /*---------------------------------*/
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
#endif

/***************************************************************************/
/*  Safe Check                                                             */
/***************************************************************************/
#if !defined(CAN_SAFE_BSW) /* COV_CAN_COMPATIBILITY */
# define CAN_SAFE_BSW   STD_OFF
#else
# if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
#  if (CAN_DEV_ERROR_DETECT == STD_OFF) || (CAN_AMD_RUNTIME_MEASUREMENT == STD_ON) /* COV_CAN_SAFE_BSW_EXCLUSION */
#   error "Unsupported Feature activated for SafeBSW"
#  endif
# endif
#endif

/***************************************************************************/
/*  Error Check                                                            */
/***************************************************************************/
#if (CAN_TRANSMIT_BUFFER == STD_OFF) && defined(C_ENABLE_CANCEL_IN_HW)
# error "C_ENABLE_CANCEL_IN_HW need CAN_TRANSMIT_BUFFER == STD_ON (no FIFO buffering but PRIO_BY_CANID in CanIf) -> check Generated data"
#endif
# if (CAN_SLEEP_SUPPORT == STD_ON) && (CAN_WAKEUP_SUPPORT == STD_ON)
#  error "C_ENABLE_SLEEP_WAKEUP organified but generated like supported"
# endif
#if (CAN_WAKEUP_SUPPORT == STD_ON) && (CAN_SLEEP_SUPPORT == STD_OFF)
# error "activated CAN_WAKEUP_SUPPORT need activated CAN_SLEEP_SUPPORT"
#endif
#if defined(C_ENABLE_HW_LOOP_TIMER)
# if (CAN_LOOP_MAX == 0)
#  error "CAN_LOOP_MAX should not be generated as 0"
# endif
#else
# if (CAN_HARDWARE_CANCELLATION == STD_ON)
#  error "C_ENABLE_HW_LOOP_TIMER organified but generated like supported"
# endif
#endif
#if defined(C_ENABLE_CANCEL_IN_HW)
#else
# if (CAN_HW_TRANSMIT_CANCELLATION == STD_ON)
#  error "C_ENABLE_CANCEL_IN_HW organified but generated like supported"
# endif
#endif
#if (CAN_MIRROR_MODE == STD_ON) && (!defined(CAN_ENABLE_GENERIC_CONFIRMATION_API2) || (CAN_GENERIC_PRECOPY == STD_OFF))
# error "CAN_MIRROR_MODE need CAN_GENERIC_CONFIRMATION with CAN_API2 and CAN_GENERIC_PRECOPY as STD_ON"
#endif
#if (CAN_MULTIPLE_BASICCAN_TX == STD_ON)
# if (CAN_HW_TRANSMIT_CANCELLATION == STD_ON)
/* cancellation does not work in CanHL_WritePrepareCancelTx for multiple BasicCAN messages, and is not useful for FIFO queue in CanIf (normally combined with multiple BCAN)*/
# error "CAN_MULTIPLE_BASICCAN_TX and CAN_HW_TRANSMIT_CANCELLATION are STD_ON but this combination is not supported"
# endif
#endif


/***************************************************************************/
/*  Functions                                                              */
/***************************************************************************/
#define CAN_START_SEC_STATIC_CODE  /*--------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# if defined( C_SINGLE_RECEIVE_CHANNEL )
#  define CanHL_ApplCanTimerStart( timerIdx )  ApplCanTimerStart( timerIdx );
#  define CanHL_ApplCanTimerEnd( timerIdx )    ApplCanTimerEnd( timerIdx );
# else
#  define CanHL_ApplCanTimerStart( timerIdx )  ApplCanTimerStart( channel, (timerIdx) );
#  define CanHL_ApplCanTimerEnd( timerIdx )    ApplCanTimerEnd( channel, (timerIdx) );
# endif
# define CanHL_ApplCanTimerLoop( timerIdx )   if (ApplCanTimerLoop(CAN_CHANNEL_CANPARA_FIRST (timerIdx)) != CAN_OK) \
                                              { \
                                                break; \
                                              }

# if (CAN_HW_LOOP_SUPPORT_API == STD_OFF)
/* Internal handling of HW loops (like AutoSar) - otherwise ApplCanTimer... is defined an implemented by Application */
/****************************************************************************
| NAME:             ApplCanTimerStart
****************************************************************************/
/* Used as macro to save runtime and code */
#  if defined( C_SINGLE_RECEIVE_CHANNEL )
/* \trace SPEC-1640 */
#    define ApplCanTimerStart(source)     ((void)GetCounterValue( CAN_OS_COUNTER_ID, &Can_GetCanLoopTimeout(0, (source)))) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  else
#    define ApplCanTimerStart(ch, source) ((void)GetCounterValue( CAN_OS_COUNTER_ID, &Can_GetCanLoopTimeout((ch), (source)))) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  endif
/****************************************************************************
| NAME:             ApplCanTimerLoop
****************************************************************************/
/*
|<DataModelStart>| ApplCanTimerLoop
Relation_Context:
# from mode transition + any LL #
HardwareLoopCheck, HardwareCancelByAppl
Relation:
DevErrorDetect, OneChOpt
HardwareLoopCheck
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) ApplCanTimerLoop( CAN_CHANNEL_CANTYPE_FIRST uint8 source )
{
  /* ----- Local Variables ---------------------------------------------- */
  Can_ReturnType retval;
  uint8 errorId;
  uint8 apiId;
  errorId = CAN_E_NO_ERROR;
  apiId = CAN_HW_ACCESS_ID;
  retval = CAN_NOT_OK;

  /* ----- Development Error Checks ------------------------------------- */
#  if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller and source is valid (no INIT check because may be used inside power on INIT) */
  if (source > CAN_LOOP_MAX) /* CM_CAN_HL22 */
  {
    errorId = CAN_E_PARAM_HANDLE;
  }
  else
#   if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#   endif
#  endif
  {
    /* ----- Implementation ----------------------------------------------- */
    TickType elapsedTime;
    TickType startTime;
    /* #110 Calculate the elapsed since time the start of this hardware loop (identified by parameter source). */
    /* Get start time (set by ApplCanTimerStart - temporary variable because GetElapsedValue modify original data */
    startTime = Can_GetCanLoopTimeout(channel, source);
    /* Get elapsed time - from start time to now */
    /* #120 Throw DET error when GetElapsedValue() failed */
    if ( GetElapsedValue( CAN_OS_COUNTER_ID, &startTime, &elapsedTime ) != (StatusType)E_OK ) /* SBSW_CAN_HL37 */ /* COV_CAN_GENDATA_FAILURE */
    {
      errorId = CAN_E_TIMEOUT_DET;
    }
    else
    {
      /* #130 Check if time out occurs for HW loop checks (none mode transition) \trace SPEC-1594 */
      if ( (TickType)CAN_OS_TICK2MS( elapsedTime ) < (TickType)CAN_TIMEOUT_DURATION ) /* COV_CAN_HARDWARE_FAILURE */
      { /* no time out occur return OK */
        retval = CAN_OK;
      }
      else /* only used in case C_ENABLE_HW_LOOP_TIMER but removed because of coverage TX for some organiy cases */
      { /* Mode Change synchronous & HW loop check */
        /* #140 Throw DET error and set hardware cancellation flag */
        if (source < CAN_LOOP_MAX) /* COV_CAN_HARDWARE_FAILURE */
        { 
          errorId = CAN_E_TIMEOUT_DET;
        }
      }
    }
    CAN_DUMMY_STATEMENT(startTime); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CAN_DEV_ERROR_REPORT == STD_ON)  
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(apiId, errorId);
  }
#  else
  CAN_DUMMY_STATEMENT(apiId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#  endif
  return retval;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
/****************************************************************************
| NAME:             ApplCanTimerEnd
****************************************************************************/
/* Used as macro to save runtime and code */
/* because of possible nested timers .. timer has to be reset */
#  define ApplCanTimerEnd ApplCanTimerStart
# endif /* (CAN_HW_LOOP_SUPPORT_API == STD_OFF) */


/****************************************************************************
| NAME:             CanHL_CleanUpSendState
****************************************************************************/
/*
|<DataModelStart>| CanHL_CleanUpSendState
Relation_Context:
# from CanLL_ModeTransition() #
Relation:
OneChOpt, ChannelAmount
MultiplexedTx
TxFullCANSupport
TxBasicAmount
TxFullAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_CleanUpSendState( CAN_CHANNEL_CANTYPE_ONLY )
{
  /* ----- Local Variables ---------------------------------------------- */
  CanObjectHandle activeSendObject;
  CanObjectHandle mailboxHandle;
  Can_HwHandleType mailboxElement;
  /* ----- Implementation ----------------------------------------------- */
  /* parameter channel is already checked by caller */
  /* #10 set all BasicCAN TX Objects to state FREE to allow a new transmission */
  mailboxHandle = Can_GetTxBasicHandleStart(canHwChannel);
# if defined(C_ENABLE_MULTIPLE_BASICCAN_TX)
  for (; mailboxHandle < Can_GetTxBasicHandleStop(canHwChannel); mailboxHandle++) /* PRQA S 2994,2996 */ /* MD_Can_ConstValue */
# endif
  {
# if defined(C_ENABLE_MULTIPLEXED_TRANSMISSION) 
    for (mailboxElement = 0u; mailboxElement < Can_GetMailboxSize(mailboxHandle); mailboxElement++) /* PRQA S 2880 */ /*  MD_MSR_Unreachable */
# else
    mailboxElement = 0u; /* PRQA S 2880 */ /*  MD_MSR_Unreachable */
# endif
    {
      activeSendObject = CanHL_GetActiveSendObject(mailboxHandle, mailboxElement);
      Can_SetActiveSendState(activeSendObject, kCanBufferFree); /* SBSW_CAN_HL04 */
    }
  }
# if defined(C_ENABLE_TX_FULLCAN_OBJECTS)
  /* #30 set all FullCAN TX Objects to state FREE to allow a new transmission */
  for (mailboxHandle = Can_GetTxFullHandleStart(canHwChannel); mailboxHandle < Can_GetTxFullHandleStop(canHwChannel); mailboxHandle++) /* PRQA S 2994,2996 */ /* MD_Can_ConstValue */
  {
    activeSendObject = CanHL_GetActiveSendObject(mailboxHandle, 0u); /* PRQA S 2880 */ /*  MD_MSR_Unreachable */
    Can_SetActiveSendState(activeSendObject, kCanBufferFree); /* SBSW_CAN_HL04 */ 
  }
# endif
  CAN_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}

/****************************************************************************
| NAME:             CanHL_ReInit
****************************************************************************/
/*
|<DataModelStart>| CanHL_ReInit
Relation_Context:
# from CanHL_ModeTransition() #
Wakeup, OneChOpt, ChannelAmount
Relation:
DevErrorDetect, OneChOpt, ChannelAmount
DevErrorDetect, Variant, ChannelAmount
RamCheck
TxFullCANSupport
RxFullCANSupport
RxBasicCANSupport
Wakeup, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
 */
V_DEF_FUNC(CAN_STATIC, uint8, STATIC_CODE) CanHL_ReInit( CAN_HW_CHANNEL_CANTYPE_FIRST uint8 doRamCheck )
{ /* \trace SPEC-1719, SPEC-1589, SPEC-1346, SPEC-1565 */
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  tCanInitParaStruct initPara;
  CanHookBegin_CanHL_ReInit();
  errorId = CAN_E_NO_ERROR;
  initPara.isInitOk = kCanFailed; /* PRQA S 2982 */ /* MD_MSR_RetVal */
  /* ----- Development Error Checks ------------------------------------- */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller and Config pointer is valid and state is INIT */
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* \trace SPEC-1718 */
    errorId = CAN_E_UNINIT;
  }
  else
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  { /* \trace SPEC-1713 */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
# endif
# if (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
  if (Can_GetCanIfChannelId(channel) == kCanChannelNotUsed) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  { /* \trace SPEC-1713 */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
# endif
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #100 initialization controller states and initialization objects --- */
    initPara.initObject = Can_GetLastInitObject(channel);
#if defined(C_ENABLE_CAN_RAM_CHECK)
    initPara.doRamCheck = doRamCheck;
#endif
#if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
    initPara.isChRamCheckFail = kCanFalse;
#endif
    /* #110 clean up status (do not activate communication and let SLEEP and initialization to detect ram-check request) */
#if defined(C_ENABLE_CAN_RAM_CHECK) && !defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
    if (doRamCheck == kCanExecuteRamCheck)
    { /* #112 standard RAM check will be performed so delete old status CAN_DEACTIVATE_CONTROLLER but leave CAN_STATUS_INIT (info about PowerOn) */
      Can_SetLogStatus(channel, Can_GetLogStatus(channel) & (uint8)CAN_STATUS_INIT);  /* SBSW_CAN_HL02 */
    }
    else
#endif
    { /* #114 extended RAM check may be performed so delete old status except CAN_DEACTIVATE_CONTROLLER and CAN_STATUS_INIT */
      Can_SetLogStatus(channel, Can_GetLogStatus(channel) & ((uint8)(CAN_DEACTIVATE_CONTROLLER) | (uint8)((uint8)CAN_STATUS_INIT)));  /* SBSW_CAN_HL02 */
    }
    /* #125 begin initialization CanHL_InitBegin() */
    initPara.isInitOk = CanHL_InitBegin(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &initPara); /* SBSW_CAN_HL31 */
    /* #130 block invalid hardware access (silent check) */
    if (initPara.isInitOk == kCanOk) /* PRQA S 2991,2995 */ /* MD_Can_ConstValue */ /* COV_CAN_LL_HARDWARE_BEHAVIOUR */
    {
#if defined(C_ENABLE_TX_FULLCAN_OBJECTS)
      /* #140 do TX FullCAN initialization CanHL_InitTxFullCAN()*/
      initPara.isInitOk &= CanHL_InitTxFullCAN(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &initPara); /* SBSW_CAN_HL31 */
#endif
      /* #150 do TX BasicCAN initialization CanHL_InitTxBasicCAN() */
      initPara.isInitOk &= CanHL_InitTxBasicCAN(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &initPara); /* SBSW_CAN_HL31 */
#if defined(C_ENABLE_RX_FULLCAN_OBJECTS)
      /* #170 do RX FullCAN initialization CanHL_InitRxFullCAN() */
      initPara.isInitOk &= CanHL_InitRxFullCAN(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &initPara); /* SBSW_CAN_HL31 */
#endif
#if defined(C_ENABLE_RX_BASICCAN_OBJECTS) /* COV_CAN_MULTIPLE_BASICCAN */
      /* #180 do RX BasicCAN initialization CanHL_InitRxBasicCAN() */
      initPara.isInitOk &= CanHL_InitRxBasicCAN(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &initPara); /* SBSW_CAN_HL31 */
#endif
      /* #190 end initialization CanHL_InitEnd_InitMode() */
      initPara.isInitOk &= CanHL_InitEnd_InitMode(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &initPara); /* SBSW_CAN_HL31 */ /* PRQA S 2986 */ /* MD_Can_ConstValue */
#if defined(C_ENABLE_CAN_RAM_CHECK)
      if (doRamCheck == kCanExecuteRamCheck)
      { 
# if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
        /* #200 extended RamChecks new issue occur - notify corrupt register / deactivate controller */
        if (initPara.isChRamCheckFail == kCanTrue) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
        {
          CanIf_RamCheckCorruptController((uint8)Can_GetCanToCanIfChannelMapping(channel));
          Can_SetLogStatus(channel, Can_GetLogStatus(channel) | CAN_DEACTIVATE_CONTROLLER); /* SBSW_CAN_HL02 */
        }
# else
        if( (Can_GetLogStatus(channel) & CAN_DEACTIVATE_CONTROLLER) == CAN_DEACTIVATE_CONTROLLER ) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
        { /* #210 standard RAM check issue occur - call Appl_CanRamCheckFailed() (any mailbox fail) */
          if (Appl_CanRamCheckFailed((uint8)channel) != CAN_DEACTIVATE_CONTROLLER)
          { /* #220 let the application decide if communication stay disabled as set by RAM check or not */
            Can_SetLogStatus(channel, Can_GetLogStatus(channel) & (uint8)(~(CAN_DEACTIVATE_CONTROLLER))); /* Application decide to activate communication in case RAM_CHECK failed */  /* SBSW_CAN_HL02 */
          }
        }
# endif
        CAN_RAM_CHECK_FINISHED_CTP(channel)
      }
#endif
    }
    if (initPara.isInitOk == kCanOk) /* PRQA S 2991,2995 */ /* MD_Can_ConstValue */ /* COV_CAN_LL_HARDWARE_BEHAVIOUR */
    { /* #280 set controller init flag when no issue occure before */
      Can_SetLogStatus(channel, Can_GetLogStatus(channel) | (CAN_STATUS_INIT)); /* SBSW_CAN_HL02 */
    }
    else
    { /* #275 set error when issue occure before */
      Can_SetLogStatus(channel, /* CAN_STATUS_UNINIT | */ (Can_GetLogStatus(channel) & (uint8)(CAN_DEACTIVATE_CONTROLLER))); /* SBSW_CAN_HL02 */
      errorId = CAN_E_UNINIT;
    }
  } /* controller active in multiple ECU configuration */

  /* ----- Development Error Report --------------------------------------- */
#if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_INITCTR_ID, errorId);
  }
#else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
#if !defined(C_ENABLE_CAN_RAM_CHECK)
  CAN_DUMMY_STATEMENT(doRamCheck); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
  CanHookEnd_CanHL_ReInit();
  return initPara.isInitOk;
} /* PRQA S 6010,6030,6050,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STCAL,MD_MSR_STMIF */

/****************************************************************************
| NAME:             CanHL_ModeTransition
****************************************************************************/
/*
|<DataModelStart>| CanHL_ModeTransition
Relation_Context:
# from Can_Init #
ChannelAmount
# from Can_MainFunction_BusOff, CanHL_ErrorHandling #
StatusPolling, ChannelAmount
# from Can_ChangeBaudrate #
ChannelAmount
# from Can_SetBaudrate #
ChannelAmount
# from Can_SetControllerMode #
Wakeup
RamCheck
# from Can_RamCheckExecute #
RamCheck
# from Can_RamCheckEnableController #
RamCheck
Relation:
OneChOpt, HardwareLoopCheck, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_ModeTransition( CAN_CHANNEL_CANTYPE_FIRST uint8 transitionRequest, uint8 busOffRecovery, uint8 doRamCheck )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 transitionState;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 request transition in LL */
  transitionState = CanLL_ModeTransition(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST transitionRequest, busOffRecovery, doRamCheck);
  if(transitionState != kCanOk) /* COV_CAN_TRANSITION_REQUEST */
  { /* #20 first request fail so start Loop that wait short time for transition \trace SPEC-1642, SPEC-1635, SPEC-1630 */
    CanHL_ApplCanTimerStart((uint8)CAN_LOOP_MAX); /* SBSW_CAN_HL38 */
    do
    { /* #30 HW check mode reached (LL) */
      transitionState = CanLL_ModeTransition(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST transitionRequest, busOffRecovery, doRamCheck);
      CanHL_ApplCanTimerLoop((uint8)CAN_LOOP_MAX); /* COV_CAN_TRANSITION_REQUEST */
    } while ( transitionState != kCanOk ); /* COV_CAN_TRANSITION_REQUEST */
    CanHL_ApplCanTimerEnd ((uint8)CAN_LOOP_MAX); /* SBSW_CAN_HL38 */
  }
  if ( transitionState == kCanRequested ) /* PRQA S 2991,2995 */ /* MD_Can_ConstValue */ /* COV_CAN_TRANSITION_REQUEST */
  {
    /* #50 transition requested so remember request to repeat it asynchronous */
    Can_SetModeTransitionRequest(channel, transitionRequest); /* SBSW_CAN_HL01 */
    Can_SetBusOffTransitionRequest(channel, busOffRecovery); /* SBSW_CAN_HL01 */
    Can_SetRamCheckTransitionRequest(channel, doRamCheck); /* SBSW_CAN_HL01 */
  }
  return transitionState;
}

/****************************************************************************
| NAME:             CanHL_NotifyTransition
****************************************************************************/
/*
|<DataModelStart>| CanHL_NotifyTransition
Relation_Context:
# from Can_SetControllerMode() #
Wakeup
RamCheck
Relation:
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_NotifyTransition( CAN_CHANNEL_CANTYPE_FIRST uint8 canState, CanIf_ControllerModeType canIfState, uint8 transitionState )
{
  /* #10 if mode changed successful */
  if ( transitionState == kCanOk ) /* COV_CAN_TRANSITION_REQUEST */
  {
    /* #20 transition finished change internal state */
    Can_SetLogStatus(channel, (uint8)((Can_GetLogStatus(channel) & CAN_STATUS_MASK_NOMODE) | canState)); /* SBSW_CAN_HL02 */
    /* #30 remove transition request */
    Can_SetModeTransitionRequest(channel, kCanModeNone); /* SBSW_CAN_HL01 */
    /* #40 call notification CanIf_ControllerModeIndication() \trace SPEC-1726, SPEC-1644, SPEC-60446 */
    CanIf_ControllerModeIndication( (uint8)Can_GetCanToCanIfChannelMapping(channel), canIfState );
  }
  CAN_DUMMY_STATEMENT(transitionState); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}

#if defined(C_ENABLE_CANCEL_IN_HW)
/****************************************************************************
| NAME:             CanHL_IsHigherCanIdPrio
****************************************************************************/
/*
|<DataModelStart>| CanHL_IsHigherCanIdPrio
Relation_Context:
# from CanHL_WritePrepare #
HwCancelTx, MultiplexedTx, IdenticalIdCancel
Relation:
IDType
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) CanHL_IsHigherCanIdPrio( Can_IdType CanId1, Can_IdType CanId2 )
{
  /* ----- Local Variables ---------------------------------------------- */
  Can_ReturnType retval = CAN_NOT_OK;
  Can_IdType tmpCanId1, tmpCanId2;
  tmpCanId1 = CanId1;
  tmpCanId2 = CanId2;
  /* ----- Implementation ----------------------------------------------- */
# if defined(C_ENABLE_MIXED_ID)
  /* #10 take care about mixed Extended and Standard ID format (shift Standard ID to match Extended format) */
  if (((tmpCanId1) & CAN_ID_IDE_MASK) == CAN_ID_IDE_MASK) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  {
    tmpCanId1 = tmpCanId1 & (Can_IdType)(CAN_ID_MASK);
  } else {
    tmpCanId1 = (Can_IdType)(((tmpCanId1) & CAN_ID_MASK_STD) << 18);
  }
  if (((tmpCanId2) & CAN_ID_IDE_MASK) == CAN_ID_IDE_MASK) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  {
    tmpCanId2 = tmpCanId2 & (Can_IdType)(CAN_ID_MASK);
  } else {
    tmpCanId2 = (Can_IdType)(((tmpCanId2) & CAN_ID_MASK_STD) << 18);
  }
# else
  /* #20 mask out unused bits */
  tmpCanId1 = tmpCanId1 & (Can_IdType)CAN_ID_MASK;
  tmpCanId2 = tmpCanId2 & (Can_IdType)CAN_ID_MASK;
# endif
  /* #30 compare CAN ID priority */
  if(tmpCanId1 < tmpCanId2)
  {
    retval = CAN_OK;
  }
  return retval;
}
#endif

/****************************************************************************
| NAME:             CanHL_WritePrepare
****************************************************************************/
/*
|<DataModelStart>| CanHL_WritePrepare
Relation_Context:
# from Can_Write() #
Relation:
TxFullCANSupport
MultiplexedTx, TxHwFifo
MultiplexedTx, HwCancelTx, IdenticalIdCancel
ChannelAmount
OneChOpt
TxBasicAmount
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_WritePrepare( CAN_CHANNEL_CANTYPE_FIRST CanTxTransmissionParaStructPtr txPara )
{
  /* ----- Local Variables ---------------------------------------------- */
  /* ----- Implementation ----------------------------------------------- */
  /* #10 calculate logical TX mailbox handle for FullCAN or for BasicCAN (Multiplexed TX) as start value */
  txPara->mailboxElement = 0u; /* PRQA S 2982 */ /* MD_MSR_RetVal */ /* SBSW_CAN_HL42 */
  txPara->activeSendObject = CanHL_GetActiveSendObject(txPara->mailboxHandle, 0u); /* SBSW_CAN_HL42 */
#if defined(C_ENABLE_TX_FULLCAN_OBJECTS)
  if ( Can_GetMailboxType(txPara->mailboxHandle) != CAN_TX_FULLCAN_TYPE ) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
#endif
  { /* #20 BasicCAN preparation - search for hardware and logical transmit handle and do cancellation */
#if defined(C_ENABLE_MULTIPLEXED_TRANSMISSION) || defined(C_ENABLE_CANCEL_IN_HW)
    CanObjectHandle mailboxElement_max;
    mailboxElement_max = Can_GetMailboxSize(txPara->mailboxHandle); /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    /* \trace SPEC-1677, SPEC-1672, SPEC-1679, SPEC-1673, SPEC-1671 */
    { /* #27 if normal or Mux Tx search from first to last element 0..1 or 0..3 for free object or one to be cancelled */
      CanObjectHandle mailboxElementFound;
      CanObjectHandle activeSendObjectFound;
      mailboxElementFound = mailboxElement_max;
      activeSendObjectFound = mailboxElement_max;
      for (txPara->mailboxElement = 0u; txPara->mailboxElement < mailboxElement_max; txPara->mailboxElement++) /* SBSW_CAN_HL42 */ /* SBSW_CAN_HL42 */
      { /* #30 over all multiplexed TX objects: find free mailbox or mailbox with identical ID */
# if (CAN_IDENTICAL_ID_CANCELLATION == STD_ON) && defined(C_ENABLE_CANCEL_IN_HW)
        if ( ((txPara->pdu.id) == Can_GetActiveSendId(txPara->activeSendObject) ) && (Can_GetActiveSendState(txPara->activeSendObject) != kCanBufferFree) )
        { /* #40 Identical ID: priority 1 - cancel identical (also when free is available) */
          mailboxElementFound = txPara->mailboxElement;
          activeSendObjectFound = txPara->activeSendObject;
          break;
        }
        if (Can_GetActiveSendState(txPara->activeSendObject) == kCanBufferFree)
        { /* #50 Identical ID: priority 2 - find free mailbox (no cancellation) */
          mailboxElementFound = txPara->mailboxElement; /* do not break ... next may be identical ID */
          activeSendObjectFound = txPara->activeSendObject;
        }
# else
        if (Can_GetActiveSendState(txPara->activeSendObject) == kCanBufferFree)
        { /* #60 None Identical ID: else priority 1 - find free mailbox (no cancellation) */
          mailboxElementFound = txPara->mailboxElement;
          activeSendObjectFound = txPara->activeSendObject;
          break;
        }
# endif
        txPara->activeSendObject++; /* SBSW_CAN_HL42 */
      }
# if defined(C_ENABLE_CANCEL_IN_HW)
      if (mailboxElementFound == mailboxElement_max)
      { /* #70 No free nor identical ID found but hardware cancellation is on - search for lowest prio message to cancel */
        Can_IdType lowestPrioId = txPara->pdu.id;
        txPara->activeSendObject = CanHL_GetActiveSendObject(txPara->mailboxHandle, 0u); /* SBSW_CAN_HL42 */
        for (txPara->mailboxElement = 0u; txPara->mailboxElement < mailboxElement_max; txPara->mailboxElement++) /* SBSW_CAN_HL42 */ /* SBSW_CAN_HL42 */
        {
          if (Can_GetActiveSendState(txPara->activeSendObject) == kCanBufferSend)
          { /* #80 mailbox with send request found: check for priority and remember the lowest that could be cancelled */
            if (CanHL_IsHigherCanIdPrio(lowestPrioId, Can_GetActiveSendId(txPara->activeSendObject)) == CAN_OK)
            {
              lowestPrioId = Can_GetActiveSendId(txPara->activeSendObject);
              mailboxElementFound = txPara->mailboxElement;
              activeSendObjectFound = txPara->activeSendObject;
            }
          }
          txPara->activeSendObject++; /* SBSW_CAN_HL42 */
        }
      }
# endif
      if (mailboxElementFound == mailboxElement_max)
      { /* #90 no free or cancel mailbox found: return values set to valid element or to found element and cancel */
        txPara->mailboxElement = 0u; /* SBSW_CAN_HL42 */
        txPara->activeSendObject = CanHL_GetActiveSendObject(txPara->mailboxHandle, 0u); /* SBSW_CAN_HL42 */
      }
      else
      {
        txPara->mailboxElement = mailboxElementFound; /* SBSW_CAN_HL42 */
        txPara->activeSendObject = activeSendObjectFound; /* SBSW_CAN_HL42 */
# if defined(C_ENABLE_CANCEL_IN_HW) /* \trace SPEC-1674 */
        CanHL_WritePrepareCancelTx(CAN_CHANNEL_CANPARA_FIRST txPara); /* SBSW_CAN_HL49 */
# endif
      }
    } /* normal or mux tx */
#endif
  } /* end BasicCAN handling */
  CAN_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  /* #200 no special FullCAN handling needed */
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

#if defined(C_ENABLE_CANCEL_IN_HW) 
/****************************************************************************
| NAME:             CanHL_WriteSavePduInfo
****************************************************************************/
/*
|<DataModelStart>| CanHL_WriteSavePduInfo
Relation_Context:
# from CanHL_WritePrepareCancelTx #
HwCancelTx
# from CanHL_WriteStart #
TxHwFifo, GenericConfirmation
Relation:
DevErrorDetect
TxBasicAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_WriteSavePduInfo( CanTxTransmissionParaStructPtr txPara ) /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */
{
    /* #10 Get buffer to store data */
    uint16 activeSendData;
    activeSendData = CanHL_GetActiveSendData(txPara->mailboxHandle, txPara->mailboxElement);
    /* #20 SDU pointer may be a null pointer in case the DLC is 0 - so do not copy data in this case */
    if(txPara->pdu.sdu != NULL_PTR)
    {
# if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
      if(Can_GetSizeOfActiveSendData() >= (activeSendData + txPara->pdu.length)) /* CM_CAN_HL20 */ /* COV_CAN_GENDATA_FAILURE */
# endif
      {
        /* #25 copy data with VStdLib optimized copy routine */
        VStdMemCpy((void*)&Can_GetActiveSendData(activeSendData), (void*)txPara->pdu.sdu, txPara->pdu.length); /* SBSW_CAN_HL22 */ /* PRQA S 0314,0316 */ /* MD_Can_PointerVoidCast */
      }
    }
    /* #30 copy ID, DLC and pointer to data (also pdu as part of PduInfo struct) */
    Can_SetActiveSendId(txPara->activeSendObject, txPara->pdu.id); /* SBSW_CAN_HL23 */
    Can_SetActiveSendLength(txPara->activeSendObject, txPara->pdu.length); /* SBSW_CAN_HL23 */
    Can_SetActiveSendSdu(txPara->activeSendObject, &Can_GetActiveSendData(activeSendData)); /* SBSW_CAN_HL23 */
    Can_SetActiveSendSwPduHandle(txPara->activeSendObject, txPara->pdu.swPduHandle); /* SBSW_CAN_HL23 */
}
#endif

#if defined(C_ENABLE_CANCEL_IN_HW)
/****************************************************************************
| NAME:             CanHL_WritePrepareCancelTx
****************************************************************************/
/*
|<DataModelStart>| CanHL_WritePrepareCancelTx
Relation_Context:
# from CanHL_WritePrepare #
HwCancelTx
Relation:
DevErrorDetect
CanFdSupport
MultiplexedTx, IdenticalIdCancel
OneChOpt
ChannelAmount
TxBasicAmount
TxFullAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_WritePrepareCancelTx( CAN_CHANNEL_CANTYPE_FIRST CanTxTransmissionParaStructPtr txPara )
{
  /* ----- Local Variables ---------------------------------------------- */
  /* ----- Implementation ----------------------------------------------- */
  if (Can_GetActiveSendState(txPara->activeSendObject) == kCanBufferFree)
  { /* #10 free buffer found: backup ID, DLC, data, PDU for possible cancellation - as parameter to IF */
    CanHL_WriteSavePduInfo(txPara); /* SBSW_CAN_HL49 */
  }
  else if (Can_GetActiveSendState(txPara->activeSendObject) == kCanBufferSend) /* COV_IMPLICITE_TXCANCEL */
  { /* #20 occupied buffer found (lower ID or Identical - found before): cancel it */
    /* \trace SPEC-1747, SPEC-15133, SPEC-1685, SPEC-1690, SPEC-1692, SPEC-1676, SPEC-1683, SPEC-15126 */
    tCanTxCancellationParaStruct txCancellationPara;
    txCancellationPara.mailboxHandle = txPara->mailboxHandle;
    txCancellationPara.hwObjHandle = txPara->hwObjHandle; 
    txCancellationPara.mailboxElement = txPara->mailboxElement;
    txCancellationPara.activeSendObject = txPara->activeSendObject;
    txCancellationPara.canHandleCurTxObj = kCanBufferCancel;
    /* #30 HW cancel mailbox (LL) */
    CanLL_TxCancelInHw(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &txCancellationPara); /* SBSW_CAN_HL47 */
    Can_SetActiveSendState(txPara->activeSendObject, kCanBufferCancel); /* SBSW_CAN_HL41 */
    /* #40 do not notify IF about successful cancellation because of recursion will not work! Hardware support not possible in this case */
  }
  else
  { /* avoid MISRA warning (if else if without ending else) */
    /* \trace SPEC-1754 */
  }
}
#endif

/****************************************************************************
| NAME:             CanHL_WriteStart
****************************************************************************/
/*
|<DataModelStart>| Can_WriteStart
Relation_Context:
# from Can_Write #
Relation:
GenericPreTransmit
TxHwFifo, GenericConfirmation
IDType
OneChOpt
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) CanHL_WriteStart( CAN_CHANNEL_CANTYPE_FIRST CanTxTransmissionParaStructPtr txPara )
{
  /* ----- Local Variables ---------------------------------------------- */
  Can_ReturnType retval = CAN_OK;
  /* ----- Implementation ----------------------------------------------- */
  /* #10 free TX mailbox found so start transmission \trace SPEC-1744 */
  if (Can_GetActiveSendState(txPara->activeSendObject) == kCanBufferFree)
  {
    uint8 llretval;
    /* #20 remember PDU and send state to use it in Confirmation function \trace SPEC-1675 */
    Can_SetActiveSendPdu(txPara->activeSendObject, txPara->pdu.swPduHandle); /* SBSW_CAN_HL05 */
    Can_SetActiveSendState(txPara->activeSendObject, kCanBufferSend); /* SBSW_CAN_HL04 */
#if defined(C_ENABLE_PRETRANSMIT_FCT)
    /* call pretransmit function ----------------------------------------------- */
    Appl_GenericPreTransmit( (uint8)channel, &(txPara->pdu) );  /* PRQA S 0312 */ /* MD_Can_NoneVolatilePointerCast */ /* SBSW_CAN_HL24 */
#endif
    /* #50 HW prepare transmission */
    CanLL_TxBegin(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST txPara); /* SBSW_CAN_HL49 */
    /* #60 Set ID, ID type and DLC in HW register depend on ID type */
    txPara->dlcRaw = MK_TX_DLC(CAN_LEN2DLC(txPara->pdu.length)); /* SBSW_CAN_HL42 */
#if defined(C_ENABLE_EXTENDED_ID)
# if defined(C_ENABLE_MIXED_ID)
    if ( ((txPara->pdu.id) & CAN_ID_IDE_MASK) != CAN_ID_IDE_MASK) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    {
      txPara->idType = kCanIdTypeStd; /* SBSW_CAN_HL42 */
      SET_PARASTRUCT_IDRAW_TX_STD(txPara, txPara->pdu.id); /* SBSW_CAN_HL42 */ /* SBSW_CAN_HL42 */ /* SBSW_CAN_HL42 */ /* SBSW_CAN_HL42 */
    }
    else
# endif
    {
# if defined( C_ENABLE_MIXED_ID ) 
      txPara->idType = kCanIdTypeExt; /* SBSW_CAN_HL42 */
# endif
      SET_PARASTRUCT_IDRAW_TX_EXT(txPara, txPara->pdu.id); /* SBSW_CAN_HL42 */ /* SBSW_CAN_HL42 */ /* SBSW_CAN_HL42 */ /* SBSW_CAN_HL42 */
    }
#else
    {
      SET_PARASTRUCT_IDRAW_TX_STD(txPara, txPara->pdu.id); /* SBSW_CAN_HL42 */ /* SBSW_CAN_HL42 */ /* SBSW_CAN_HL42 */ /* SBSW_CAN_HL42 */ /* PRQA S 4491 */ /* MD_Can_IntegerCast */
    }
#endif
    /* set id, dlc in hardware */
    CanLL_TxSetMailbox(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST txPara); /* SBSW_CAN_HL49 */
    if(txPara->pdu.sdu != NULL_PTR)
    { /* #70 Set CAN data in HW register (LL) - only when data pointer is not null \trace SPEC-1680, SPEC-1572, SPEC-1678, SPEC-60421 */
      txPara->CanMemCopySrcPtr = txPara->pdu.sdu; /* SBSW_CAN_HL42 */
      CanLL_TxCopyToCan(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST txPara); /* SBSW_CAN_HL49 */
    }
    /* #80 HW start transmission (LL) */
    llretval = CanLL_TxStart(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST txPara); /* SBSW_CAN_HL49 */
    /* HW finish transmission (LL) */
    CanLL_TxEnd(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST txPara); /* SBSW_CAN_HL49 */
    CAN_DUMMY_STATEMENT(llretval); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  }
  else
  { /* #200 no free TX mailbox found so return busy - also in case cancellation (BasicCAN) was possible \trace SPEC-1754, SPEC-1764, SPEC-1747 */
    retval = CAN_BUSY;
  }
  return retval;
} /* PRQA S 6050 */ /* MD_MSR_STCAL */

/****************************************************************************
| NAME:             CanHL_GetActiveSendObject
****************************************************************************/
/*
|<DataModelStart>| CanHL_GetActiveSendObject
Relation_Context:
# from CanHL_InitXXX() #
Wakeup, OneChOpt, ChannelAmount
# from CanHL_WritePrepare #
# from CanHL_TxTaskCancelationHandling #
HwCancelTx
# from CanHL_CleanUpSendState #
# from Can_CancelTx #
TransmitCancellationAPI
# from CanHL_TxConfirmation #
Relation:
DevErrorDetect
TxFullAmount
TxBasicAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, CanObjectHandle, STATIC_CODE) CanHL_GetActiveSendObject( Can_HwHandleType mailboxHandle, Can_HwHandleType mailboxElement )
{
  /* ----- Local Variables ---------------------------------------------- */
  CanObjectHandle activeSendObject;
  /* ----- Implementation ----------------------------------------------- */
  /* #10 get logical handle from generated indirection table */
  activeSendObject = (CanObjectHandle) Can_GetMailboxActiveSendObject(mailboxHandle) + mailboxElement;
#if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
  if (activeSendObject >= (Can_HwHandleType)Can_GetSizeOfActiveSendObject()) /* CM_CAN_HL03 */ /* COV_CAN_GENDATA_FAILURE */
  { /* #20 secure SilentBSW */
    activeSendObject = ((Can_HwHandleType)Can_GetSizeOfActiveSendObject() - (Can_HwHandleType)1u);
# if (CAN_DEV_ERROR_REPORT == STD_ON)  
    Can_CallDetReportError(CAN_WRITE_ID, CAN_E_PARAM_HANDLE);
# endif
  }
#endif
  return activeSendObject;
}

#if defined(C_ENABLE_CANCEL_IN_HW) 
/****************************************************************************
| NAME:             CanHL_GetActiveSendData
****************************************************************************/
/*
|<DataModelStart>| CanHL_GetActiveSendData
Relation_Context:
HwCancelTx, TxHwFifo
# from CanHL_WritePrepare #
# from CanHL_TxTaskCancelationHandling #
HwCancelTx
# from Can_CancelTx #
TransmitCancellationAPI
# from CanHL_TxConfirmation #
Relation:
DevErrorDetect
TxBasicAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, uint16, STATIC_CODE) CanHL_GetActiveSendData( Can_HwHandleType mailboxHandle, uint8 mailboxElement )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint16 activeSendData;
  /* ----- Implementation ----------------------------------------------- */
  /* #10 get logical handle from generated indirection table */
  activeSendData = (uint16) (Can_GetMailboxActiveSendData(mailboxHandle) + ((uint16)mailboxElement * (uint16)Can_GetMailboxDataLen(mailboxHandle)));
#if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
  if ((activeSendData + Can_GetMailboxDataLen(mailboxHandle)) > Can_GetSizeOfActiveSendData()) /* CM_CAN_HL20 */ /* COV_CAN_GENDATA_FAILURE */
  { /* #20 secure SilentBSW */
    activeSendData = 0u;
# if (CAN_DEV_ERROR_REPORT == STD_ON)  
    Can_CallDetReportError(CAN_WRITE_ID, CAN_E_PARAM_HANDLE);
# endif
  }
#endif
  return activeSendData;
}
#endif

#if defined(C_ENABLE_CAN_RAM_CHECK)
/****************************************************************************
| NAME:             CanHL_RamCheckMailboxNotification
****************************************************************************/
/*
|<DataModelStart>| CanHL_RamCheckMailboxNotification
Relation_Context:
# CanHL_InitXXX() #
Wakeup, OneChOpt, ChannelAmount, RamCheck
Relation:
TxFullCANSupport
RxFullCANSupport
RxBasicCANSupport
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_RamCheckMailboxNotification( CAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara ) /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */ /* COV_CAN_RAM_CHECK_NO_STIMULATION */
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 deactivate mailbox */
  Can_SetMailboxState(initPara->mailboxHandle, kCanFailed); /* SBSW_CAN_HL34 */
  /* #20 deactivate controller */
  Can_SetLogStatus(channel, Can_GetLogStatus(channel) | CAN_DEACTIVATE_CONTROLLER); /* SBSW_CAN_HL02 */
  /* #30 notify application about corrupt mailbox */
# if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
  CanIf_RamCheckCorruptMailbox((uint8)Can_GetCanToCanIfChannelMapping(channel), initPara->mailboxHandle);
# else
#  if defined(C_ENABLE_NOTIFY_CORRUPT_MAILBOX) /* with Mailbox Notification */
  Appl_CanCorruptMailbox((uint8)channel, (initPara->hwObjHandle));
#  endif
# endif
}
#endif

/****************************************************************************
| NAME:             CanHL_InitBegin
****************************************************************************/
/*
|<DataModelStart>| CanHL_InitBegin
Relation_Context:
# CanHL_ReInit() #
Wakeup, OneChOpt, ChannelAmount
Relation:
RamCheck
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_InitBegin( CAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 initOk;
  /* ----- Implementation ----------------------------------------------- */
  initOk = kCanFailed; /* PRQA S 2982 */ /* MD_MSR_RetVal */
  if (CanLL_InitBegin(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST initPara) == kCanOk) /* PRQA S 2991,2995 */ /* MD_Can_ConstValue */ /* SBSW_CAN_HL31 */ /* COV_CAN_LL_HARDWARE_BEHAVIOUR */
  {
#if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
    /* #20 Execute pattern RamCheck */
    if (initPara->doRamCheck == kCanExecuteRamCheck)
    {
      initPara->isChRamCheckFail |= CAN_RAM_CHECK_BEGIN_REG_RESULT(channel, initPara); /* SBSW_CAN_HL36 */ /* SBSW_CAN_HL31 */ /* COV_CAN_HARDWARE_FAILURE */ /* PRQA S 2985 */ /* MD_Can_ConstValue */
    } 
#endif
    /* #30 Initialize controller registers (Begin section) */
    initOk = CanLL_InitBeginSetRegisters(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST initPara); /* SBSW_CAN_HL31 */
  }
  return initOk;
}

#if defined(C_ENABLE_TX_FULLCAN_OBJECTS)
/****************************************************************************
| NAME:             CanHL_InitTxFullCAN
****************************************************************************/
/*
|<DataModelStart>| CanHL_InitTxFullCAN
Relation_Context:
# CanHL_ReInit() #
Wakeup, OneChOpt, ChannelAmount, TxFullCANSupport
Relation:
RamCheck
TxFullAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_InitTxFullCAN( CAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 initOk;
  uint8 mailboxState;
  CanObjectHandle activeSendObject;
# if defined(C_ENABLE_CAN_RAM_CHECK)
  uint8 isMbRamCheckFail;
# endif
  /* ----- Implementation ----------------------------------------------- */
  initOk = kCanOk;
  /* #10 iterate over all FullCAN TX */
  for (initPara->mailboxHandle = Can_GetTxFullHandleStart(canHwChannel); initPara->mailboxHandle < Can_GetTxFullHandleStop(canHwChannel); initPara->mailboxHandle++) /* PRQA S 2994,2996 */ /* MD_Can_ConstValue */ /* SBSW_CAN_HL36 */ /* SBSW_CAN_HL36 */
  { /* #20 initialize FullCAN TX mailboxes */
    initPara->hwObjHandle = Can_GetMailboxHwHandle(initPara->mailboxHandle); /* PRQA S 2880 */ /*  MD_MSR_Unreachable */ /* SBSW_CAN_HL36 */
    activeSendObject = CanHL_GetActiveSendObject(initPara->mailboxHandle, 0u);
    Can_SetActiveSendState(activeSendObject, kCanBufferFree); /* SBSW_CAN_HL04 */
# if defined(C_ENABLE_CAN_RAM_CHECK)
    /* #30 RAM check for FullCAN TX mailboxes */
    isMbRamCheckFail = kCanFalse;
    if (initPara->doRamCheck == kCanExecuteRamCheck)
    {
      isMbRamCheckFail = CAN_RAM_CHECK_MAILBOX_RESULT(channel, initPara); /* SBSW_CAN_HL31 */ /* COV_CAN_HARDWARE_FAILURE */
    } 
# endif
    /* TX initialization */
    mailboxState = CanLL_InitMailboxTx(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST initPara); /* SBSW_CAN_HL31 */
    initOk &= mailboxState; /* all mailboxes OK - otherwise return fail */ /* PRQA S 2985 */ /* MD_Can_ConstValue */
# if defined(C_ENABLE_CAN_RAM_CHECK)
    if(mailboxState == kCanFailed) { /* PRQA S 2992,2996 */ /* MD_Can_ConstValue */ /* COV_CAN_HARDWARE_FAILURE */
      isMbRamCheckFail = kCanTrue; /* PRQA S 2880 */ /* MD_MSR_Unreachable */
    }
    if( (Can_GetLogStatus(channel) & CAN_STATUS_INIT) != CAN_STATUS_INIT )
    { /* PowerOn */
      Can_SetMailboxState(initPara->mailboxHandle, mailboxState); /* SBSW_CAN_HL34 */
    }
    if( (isMbRamCheckFail == kCanTrue) || (Can_GetMailboxState(initPara->mailboxHandle) == kCanFailed) ) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
    { /* #45 deactivate corrupt mailbox */
      CanLL_InitMailboxTxDeactivate(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST initPara); /* SBSW_CAN_HL31 */
      if (isMbRamCheckFail == kCanTrue)
      {  /* #50 notify application about corrupt mailbox and deactivate controller */
        CanHL_RamCheckMailboxNotification(CAN_CHANNEL_CANPARA_FIRST initPara); /* SBSW_CAN_HL31 */
      }
    }
# endif
  }
  return initOk;
}
#endif

/****************************************************************************
| NAME:             CanHL_InitTxBasicCAN
****************************************************************************/
/*
|<DataModelStart>| CanHL_InitTxBasicCAN
Relation_Context:
# CanHL_ReInit() #
Wakeup, OneChOpt, ChannelAmount
Relation:
MultiplexedTx, TxHwFifo
TxHwFifo, GenericConfirmation, IfTxBuffer
TxBasicAmount
RamCheck
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_InitTxBasicCAN( CAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 initOk;
  uint8 mailboxState;
  CanObjectHandle activeSendObject;
#if defined(C_ENABLE_CAN_RAM_CHECK)
  uint8 isMbRamCheckFail;
#endif

  /* ----- Implementation ----------------------------------------------- */
  initOk = kCanOk;
  initPara->mailboxHandle = Can_GetTxBasicHandleStart(canHwChannel); /* SBSW_CAN_HL36 */
#if defined(C_ENABLE_MULTIPLE_BASICCAN_TX)
  for (; initPara->mailboxHandle < Can_GetTxBasicHandleStop(canHwChannel); initPara->mailboxHandle++) /* PRQA S 2994,2996 */ /* MD_Can_ConstValue */ /* SBSW_CAN_HL36 */
#endif
  { /* #10 iterate over all logical BasicCAN TX */
#if defined(C_ENABLE_MULTIPLEXED_TRANSMISSION) 
    CanObjectHandle activeSendObjectStop;
#endif
    initPara->hwObjHandle = Can_GetMailboxHwHandle(initPara->mailboxHandle); /* PRQA S 2880 */ /*  MD_MSR_Unreachable */ /* SBSW_CAN_HL36 */
    activeSendObject = CanHL_GetActiveSendObject(initPara->mailboxHandle, 0u);
#if defined(C_ENABLE_MULTIPLEXED_TRANSMISSION) 
    activeSendObjectStop = activeSendObject + Can_GetMailboxSize(initPara->mailboxHandle);
    for (; activeSendObject < activeSendObjectStop; activeSendObject++)
#endif
    { /* #20 initialize BasicCAN TX mailboxes */
      Can_SetActiveSendState(activeSendObject, kCanBufferFree); /* SBSW_CAN_HL04 */
    }
#if defined(C_ENABLE_CAN_RAM_CHECK)
    /* #30 RAM check for BasicCAN TX mailboxes */
    isMbRamCheckFail = kCanFalse;
    if (initPara->doRamCheck == kCanExecuteRamCheck)
    {
      isMbRamCheckFail = CAN_RAM_CHECK_MAILBOX_RESULT(channel, initPara); /* COV_CAN_HARDWARE_FAILURE */ /* SBSW_CAN_HL31 */
    } 
#endif
    /* TX initialization */
    mailboxState = CanLL_InitMailboxTx(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST initPara); /* SBSW_CAN_HL31 */
    initOk &= mailboxState; /* all mailboxes OK - otherwise return fail */ /* PRQA S 2985,2986 */ /* MD_Can_ConstValue */
#if defined(C_ENABLE_CAN_RAM_CHECK)
    if(mailboxState == kCanFailed) { /* PRQA S 2992,2996 */ /* MD_Can_ConstValue */ /* COV_CAN_HARDWARE_FAILURE */
      isMbRamCheckFail = kCanTrue; /* PRQA S 2880 */ /* MD_MSR_Unreachable */
    }
    if( (Can_GetLogStatus(channel) & CAN_STATUS_INIT) != CAN_STATUS_INIT )
    { /* PowerOn */
      Can_SetMailboxState(initPara->mailboxHandle, mailboxState); /* SBSW_CAN_HL34 */
    }
    if( (isMbRamCheckFail == kCanTrue) || (Can_GetMailboxState(initPara->mailboxHandle) == kCanFailed) ) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
    { /* #45 deactivate corrupt mailbox */
      CanLL_InitMailboxTxDeactivate(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST initPara); /* SBSW_CAN_HL31 */
      if (isMbRamCheckFail == kCanTrue)
      {  /* #50 notify application about corrupt mailbox and deactivate controller */
        CanHL_RamCheckMailboxNotification(CAN_CHANNEL_CANPARA_FIRST initPara); /* SBSW_CAN_HL31 */
      }
    }
#endif
  }
  return initOk;
} /* PRQA S 6010 */ /* MD_MSR_STPTH */


#if defined(C_ENABLE_RX_FULLCAN_OBJECTS)
/****************************************************************************
| NAME:             CanHL_InitRxFullCAN
****************************************************************************/
/*
|<DataModelStart>| CanHL_InitRxFullCAN
Relation_Context:
# CanHL_ReInit() #
Wakeup, OneChOpt, ChannelAmount, RxFullCANSupport
Relation:
RamCheck
IDType
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_InitRxFullCAN( CAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 initOk;
  uint8 mailboxState;
# if defined(C_ENABLE_CAN_RAM_CHECK)
  uint8 isMbRamCheckFail;
# endif

  /* ----- Implementation ----------------------------------------------- */
  initOk = kCanOk;
  for (initPara->mailboxHandle = Can_GetRxFullHandleStart(canHwChannel); initPara->mailboxHandle < Can_GetRxFullHandleStop(canHwChannel); initPara->mailboxHandle++) /* PRQA S 2994,2996 */ /* MD_Can_ConstValue */ /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */ /* SBSW_CAN_HL36 */ /* SBSW_CAN_HL36 */
  { /* #10 iterate over all FullCAN RX mailboxes */
    initPara->hwObjHandle=Can_GetMailboxHwHandle(initPara->mailboxHandle); /* PRQA S 2880 */ /*  MD_MSR_Unreachable */ /* SBSW_CAN_HL36 */
# if defined(C_ENABLE_CAN_RAM_CHECK)
    /* #20 RAM check for FullCAN RX mailboxes */
    isMbRamCheckFail = kCanFalse;
    if (initPara->doRamCheck == kCanExecuteRamCheck)
    {
      isMbRamCheckFail = CAN_RAM_CHECK_MAILBOX_RESULT(channel, initPara); /* COV_CAN_HARDWARE_FAILURE */ /* SBSW_CAN_HL31 */
    } 
# endif
    /* #30 set ID for FullCAN RX mailboxes (LL) */
# if defined(C_ENABLE_EXTENDED_ID)
#  if defined(C_ENABLE_MIXED_ID)
    if ( ((Can_IdType)Can_GetMailboxIDValue(initPara->mailboxHandle) & CAN_ID_IDE_MASK) != CAN_ID_IDE_MASK) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */ /* PRQA S 2991,2995 */ /* MD_Can_ConstValue */
    {
      initPara->idType = kCanIdTypeStd; /* SBSW_CAN_HL36 */
      SET_PARASTRUCT_IDRAW_RX_STD(initPara, Can_GetMailboxIDValue(initPara->mailboxHandle)); /* SBSW_CAN_HL36 */ /* SBSW_CAN_HL36 */ /* SBSW_CAN_HL36 */ /* SBSW_CAN_HL36 */ /* PRQA S 4491 */ /* MD_Can_IntegerCast */
    }
    else
#  endif
    {
      initPara->idType = kCanIdTypeExt; /* SBSW_CAN_HL36 */ /* PRQA S 2880 */ /* MD_MSR_Unreachable */
      SET_PARASTRUCT_IDRAW_RX_EXT(initPara, Can_GetMailboxIDValue(initPara->mailboxHandle)); /* SBSW_CAN_HL36 */ /* SBSW_CAN_HL36 */ /* SBSW_CAN_HL36 */ /* SBSW_CAN_HL36 */
    }
# else
    initPara->idType = kCanIdTypeStd; /* SBSW_CAN_HL36 */
    SET_PARASTRUCT_IDRAW_RX_STD(initPara, Can_GetMailboxIDValue(initPara->mailboxHandle)); /* SBSW_CAN_HL36 */ /* SBSW_CAN_HL36 */ /* SBSW_CAN_HL36 */ /* SBSW_CAN_HL36 */ /* PRQA S 4491,2985 */ /* MD_Can_IntegerCast */
# endif
    /* #40 initialize FullCAN RX mailboxes */
    mailboxState = CanLL_InitMailboxRxFullCan(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST initPara); /* SBSW_CAN_HL31 */
    initOk &= mailboxState; /* all mailboxes OK - otherwise return fail */ /* PRQA S 2985 */ /* MD_Can_ConstValue */
# if defined(C_ENABLE_CAN_RAM_CHECK)
    if(mailboxState == kCanFailed) { /* PRQA S 2992,2996 */ /* MD_Can_ConstValue */ /* COV_CAN_HARDWARE_FAILURE */
      isMbRamCheckFail = kCanTrue; /* PRQA S 2880 */ /* MD_MSR_Unreachable */
    }
    if( (Can_GetLogStatus(channel) & CAN_STATUS_INIT) != CAN_STATUS_INIT )
    { /* PowerOn */
      Can_SetMailboxState(initPara->mailboxHandle, mailboxState); /* SBSW_CAN_HL34 */
    }
    if( (isMbRamCheckFail == kCanTrue) || (Can_GetMailboxState(initPara->mailboxHandle) == kCanFailed) ) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
    { /* #45 deactivate corrupt mailbox */
      CanLL_InitMailboxRxFullCanDeactivate(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST initPara); /* SBSW_CAN_HL31 */
      if (isMbRamCheckFail == kCanTrue)
      {  /* #50 notify application about corrupt mailbox and deactivate controller */
        CanHL_RamCheckMailboxNotification(CAN_CHANNEL_CANPARA_FIRST initPara); /* SBSW_CAN_HL31 */
      }
    }
# endif
  }
  return initOk;
}
#endif

#if defined(C_ENABLE_RX_BASICCAN_OBJECTS) /* COV_CAN_MULTIPLE_BASICCAN */
/****************************************************************************
| NAME:             CanHL_InitRxBasicCAN
****************************************************************************/
/*
|<DataModelStart>| CanHL_InitRxBasicCAN
Relation_Context:
# CanHL_ReInit() #
Wakeup, OneChOpt, ChannelAmount, RxBasicCANSupport
Relation:
RamCheck
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_InitRxBasicCAN( CAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 initOk;
  uint8 mailboxState;
# if defined(C_ENABLE_CAN_RAM_CHECK)
  uint8 isMbRamCheckFail;
# endif

  /* ----- Implementation ----------------------------------------------- */
  initOk = kCanOk;
  for (initPara->mailboxHandle = Can_GetRxBasicHandleStart(canHwChannel); initPara->mailboxHandle < Can_GetRxBasicHandleStop(canHwChannel); initPara->mailboxHandle++) /* PRQA S 2994,2996 */ /* MD_Can_ConstValue */ /* SBSW_CAN_HL36 */ /* SBSW_CAN_HL36 */
  { /* #10 iterate over all BasicCAN RX mailboxes */
    initPara->hwObjHandle = Can_GetMailboxHwHandle(initPara->mailboxHandle); /* PRQA S 2880 */ /*  MD_MSR_Unreachable */ /* SBSW_CAN_HL36 */
# if defined(C_ENABLE_CAN_RAM_CHECK)
    /* #20 RAM check for BasicCAN RX mailboxes */
    isMbRamCheckFail = kCanFalse;
    if (initPara->doRamCheck == kCanExecuteRamCheck)
    {
      isMbRamCheckFail = CAN_RAM_CHECK_MAILBOX_RESULT(channel, initPara); /* COV_CAN_HARDWARE_FAILURE */ /* SBSW_CAN_HL31 */
    } 
# endif
    /* #30 initialize BasicCAN RX mailboxes */
    mailboxState = CanLL_InitMailboxRxBasicCan(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST initPara); /* SBSW_CAN_HL31 */
    initOk &= mailboxState; /* all mailboxes OK - otherwise return fail */ /* PRQA S 2985 */ /* MD_Can_ConstValue */
# if defined(C_ENABLE_CAN_RAM_CHECK)
    if(mailboxState == kCanFailed) { /* PRQA S 2992,2996 */ /* MD_Can_ConstValue */ /* COV_CAN_HARDWARE_FAILURE */
      isMbRamCheckFail = kCanTrue; /* PRQA S 2880 */ /* MD_MSR_Unreachable */
    }
    if( (Can_GetLogStatus(channel) & CAN_STATUS_INIT) != CAN_STATUS_INIT )
    { /* PowerOn */
      Can_SetMailboxState(initPara->mailboxHandle, mailboxState); /* SBSW_CAN_HL34 */
    }
    if( (isMbRamCheckFail == kCanTrue) || (Can_GetMailboxState(initPara->mailboxHandle) == kCanFailed) ) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
    { /* #45 deactivate corrupt mailbox */
      CanLL_InitMailboxRxBasicCanDeactivate(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST initPara); /* SBSW_CAN_HL31 */
      if (isMbRamCheckFail == kCanTrue)
      {  /* #50 notify application about corrupt mailbox and deactivate controller */
        CanHL_RamCheckMailboxNotification(CAN_CHANNEL_CANPARA_FIRST initPara); /* SBSW_CAN_HL31 */
      }
    }
# endif
  }
  return initOk;
}
#endif

/****************************************************************************
| NAME:             CanHL_InitEnd_InitMode
****************************************************************************/
/*
|<DataModelStart>| CanHL_InitEnd_InitMode
Relation_Context:
# CanHL_ReInit() #
Wakeup, OneChOpt, ChannelAmount
Relation:
RamCheck
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_InitEnd_InitMode( CAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 initOk;

  /* ----- Implementation ----------------------------------------------- */
  initOk = kCanOk;

  /* #20 HW specific initialization end */
  initOk &= CanLL_InitEndSetRegisters(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST initPara); /* SBSW_CAN_HL31 */ /* PRQA S 2985 */ /* MD_Can_ConstValue */
  initOk &= CanLL_InitEnd( CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST initPara ); /* SBSW_CAN_HL31 */ /* PRQA S 2985 */ /* MD_Can_ConstValue */
  return initOk;
}

#if defined(C_ENABLE_RX_BASICCAN_OBJECTS) /* COV_CAN_MULTIPLE_BASICCAN */
# if defined(C_ENABLE_RX_BASICCAN_POLLING) /* COV_CAN_RX_BASICCAN_POLLING */
/****************************************************************************
| NAME:             CanHL_RxBasicCanPolling
****************************************************************************/
/*
|<DataModelStart>| CanHL_RxBasicCanPolling
Relation_Context:
# from Can_MainFunction_Read #
RxBasicCANSupport, RxPolling
Relation:
IndividualPolling
OneChOpt
ChannelAmount
RxBasicAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_RxBasicCanPolling( CAN_HW_CHANNEL_CANTYPE_ONLY )
{
  /* ----- Local Variables ---------------------------------------------- */
  tCanTaskParaStruct taskPara;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 check global pending flag (over all mailboxes - if available) */
  if(CanLL_RxBasicIsGlobalIndPending(CAN_HW_CHANNEL_CANPARA_ONLY) == kCanTrue) /* PRQA S 2991,2995 */ /* MD_Can_ConstValue */ /* COV_CAN_LL_HARDWARE_BEHAVIOUR */
  {
    /* #20 loop over all BasicCAN mailboxes */
    for (taskPara.mailboxHandle = Can_GetRxBasicHandleStart(canHwChannel); taskPara.mailboxHandle < Can_GetRxBasicHandleStop(canHwChannel); taskPara.mailboxHandle++) /* PRQA S 2994,2996 */ /* MD_Can_ConstValue */
    { /* loop over all BasicCAN mailboxes with gap */
      taskPara.hwObjHandle = Can_GetMailboxHwHandle(taskPara.mailboxHandle); /* PRQA S 2880 */ /*  MD_MSR_Unreachable */
#  if defined(C_ENABLE_INDIVIDUAL_POLLING) /* COV_CAN_HWOBJINDIVPOLLING */
      /* #30 check individual polling flag */
      if ( Can_IsMailboxIndivPolling(taskPara.mailboxHandle)) /* COV_CAN_HWOBJINDIVPOLLING */
#  endif
      {
        /* #40 call LL handling */
        CanLL_RxBasicProcessPendings(CAN_HW_CHANNEL_CANPARA_FIRST &taskPara); /* SBSW_CAN_HL44 */
      }
    }
  }
}
# endif /* C_ENABLE_RX_BASICCAN_POLLING */
#endif /* C_ENABLE_RX_BASICCAN_OBJECTS */

#if defined(C_ENABLE_RX_FULLCAN_OBJECTS)
# if defined(C_ENABLE_RX_FULLCAN_POLLING) /* COV_CAN_RX_FULLCAN_POLLING */
/****************************************************************************
| NAME:             CanHL_RxFullCanPolling
****************************************************************************/
/*
|<DataModelStart>| CanHL_RxFullCanPolling
Relation_Context:
# from Can_MainFunction_Read #
RxFullCANSupport, RxPolling
Relation:
IndividualPolling
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_RxFullCanPolling( CAN_HW_CHANNEL_CANTYPE_ONLY )
{
  /* ----- Local Variables ---------------------------------------------- */
  tCanTaskParaStruct taskPara;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 check global pending flag (over all mailboxes - if available) */
  if(CanLL_RxFullIsGlobalIndPending(CAN_HW_CHANNEL_CANPARA_ONLY) == kCanTrue) /* PRQA S 2991,2995 */ /* MD_Can_ConstValue */ /* COV_CAN_LL_HARDWARE_BEHAVIOUR */
  {
    /* #20 loop over all FullCAN mailboxes */
    for (taskPara.mailboxHandle = Can_GetRxFullHandleStart(canHwChannel); taskPara.mailboxHandle < Can_GetRxFullHandleStop(canHwChannel); taskPara.mailboxHandle++ ) /* PRQA S 2994,2996 */ /* MD_Can_ConstValue */
    {
      taskPara.hwObjHandle = Can_GetMailboxHwHandle(taskPara.mailboxHandle); /* PRQA S 2880 */ /*  MD_MSR_Unreachable */
#  if defined(C_ENABLE_INDIVIDUAL_POLLING) /* COV_CAN_HWOBJINDIVPOLLING */
      /* #30 check individual polling flag */
      if ( Can_IsMailboxIndivPolling(taskPara.mailboxHandle)) /* COV_CAN_HWOBJINDIVPOLLING */
#  endif
      {
        /* #40 call LL handling */
        CanLL_RxFullProcessPendings(CAN_HW_CHANNEL_CANPARA_FIRST &taskPara); /* SBSW_CAN_HL44 */
      }
    }
  }
}
# endif /* C_ENABLE_RX_FULLCAN_POLLING */
#endif /* C_ENABLE_RX_FULLCAN_OBJECTS */

#if defined(C_ENABLE_RX_FULLCAN_OBJECTS) || defined(C_ENABLE_RX_BASICCAN_OBJECTS) /* COV_CAN_MULTIPLE_BASICCAN */
/****************************************************************************
| NAME:             CanHL_RxMsgReceivedNotification
****************************************************************************/
/*
|<DataModelStart>| CanHL_RxMsgReceivedNotification
Relation_Context:
# from CanHL_FullCanMsgReceived #
RxFullCANSupport
# from CanHL_BasicCanMsgReceived #
RxBasicCANSupport
Relation:
RxQueue, GenericPreCopy, MirrorMode
RxQueue, DevErrorDetect
RxQueue, CanFdSupport
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_RxMsgReceivedNotification( CAN_CHANNEL_CANTYPE_FIRST CanRxInfoStructPtr rxStructPtr ) /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */
{
  /* ----- Local Variables ---------------------------------------------- */
# if !defined(C_ENABLE_RX_QUEUE) && (CAN_GENERIC_PRECOPY == STD_ON)
  Can_ReturnType generic_retval;
# endif
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  /* ----- Implementation ----------------------------------------------- */
  /* #10 RX queue */
# if defined(C_ENABLE_RX_QUEUE)
  /**************************** RxQueue handling **********************************/
    /* #20 EXCLUSIVE_AREA_4 secure RxQueue data handling */
  SchM_Enter_Can_CAN_EXCLUSIVE_AREA_4();
  if (Can_GetRxQueueInfo().Count < Can_GetSizeOfRxQueueBuffer()) /* COV_CAN_GENDATA_FAILURE */
  { /* #30 Queue not full: */
    /* #45 copy HRH, ID, DLC and data to RX queue */
    Can_GetRxQueueBuffer(Can_GetRxQueueInfo().WriteIndex).Hrh = rxStructPtr->localMailboxHandle; /* SBSW_CAN_HL18 */
    Can_GetRxQueueBuffer(Can_GetRxQueueInfo().WriteIndex).id  = rxStructPtr->localId; /* SBSW_CAN_HL18 */
    Can_GetRxQueueBuffer(Can_GetRxQueueInfo().WriteIndex).dlc = rxStructPtr->localDlc; /* SBSW_CAN_HL18 */

#  if (CAN_DEV_ERROR_DETECT == STD_ON)
    if (((uint8) (sizeof(Can_GetRxQueueBuffer(0).data) / sizeof(Can_GetRxQueueBuffer(0).data[0]))) < rxStructPtr->localDlc) /* CM_CAN_HL17 */ /* COV_CAN_GENDATA_FAILURE */
    {
      errorId = CAN_E_PARAM_DLC;
    }
    else
#  endif
    {
      /* #46 copy data with VStdLib optimized copy routine */
      VStdMemCpy((void*)Can_GetRxQueueBuffer(Can_GetRxQueueInfo().WriteIndex).data, (void*)rxStructPtr->pChipData, rxStructPtr->localDlc); /* SBSW_CAN_HL19 */ /* PRQA S 0312,0314,0316 */ /* MD_Can_NoneVolatilePointerCast,MD_Can_PointerVoidCast,MD_Can_PointerVoidCast */
    }
      /* #47 increase pointer to next queue element */
    Can_GetRxQueueInfo().Count++; /* SBSW_CAN_HL55 */
    if (Can_GetRxQueueInfo().WriteIndex < ((uint16)Can_GetSizeOfRxQueueBuffer() - (uint16)1u) )
    {
      Can_GetRxQueueInfo().WriteIndex++; /* SBSW_CAN_HL55 */
    }
    else
    {
      Can_GetRxQueueInfo().WriteIndex = 0u; /* CM_CAN_HL24 */ /* SBSW_CAN_HL55 */
    }
  }
#  if (CAN_DEV_ERROR_REPORT == STD_ON)
  else 
  { /* #50 Queue full: last message will be lost -> overrun in queue do not change ReadIndex to override latest message because inconsistency problem (currently reading queue) */
    errorId = CAN_E_RXQUEUE;
  }
#  endif
  SchM_Exit_Can_CAN_EXCLUSIVE_AREA_4();
# else /* C_ENABLE_RX_QUEUE */
  /* #100 no RX queue */
  /* -------------------------- Interface + APPL Notifications --- */
    /* #110 call Appl_GenericPrecopy() depend on configuration and if mirror mode is active */
#  if (CAN_GENERIC_PRECOPY == STD_ON)
#   if defined(C_ENABLE_MIRROR_MODE)
  if (Can_GetMirrorModeState(channel) == CDDMIRROR_INACTIVE)
  { /* do not call Appl_GenericPrecopy() in case mirror mode was disabled */
    generic_retval = CAN_OK;
  }
  else
#   endif
  {
    generic_retval = Appl_GenericPrecopy((uint8)channel, (rxStructPtr->localId & CAN_ID_MASK_IN_GENERIC_CALLOUT), rxStructPtr->localDlc, (Can_DataPtrType)rxStructPtr->pChipData);  /* PRQA S 0312 */ /* MD_Can_NoneVolatilePointerCast */ /* SBSW_CAN_HL07 */
  }
  if (generic_retval == CAN_OK) /* \trace SPEC-15119 */
#  endif
  { /* #120 call CanIf_RxIndication() if mirror mode is no active or Appl_GenericPrecopy() return OK \trace SPEC-1726, SPEC-1688, SPEC-1687, SPEC-1687 */
    CanIf_RxIndication(rxStructPtr->localMailboxHandle, rxStructPtr->localId, rxStructPtr->localDlc, (Can_DataPtrType)rxStructPtr->pChipData); /* PRQA S 0312 */ /* MD_Can_NoneVolatilePointerCast */ /* SBSW_CAN_HL07 */
  }
# endif
  CAN_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return errorId;
}
#endif

#if defined(C_ENABLE_RX_QUEUE)
/****************************************************************************
| NAME:             CanHL_RxQueueExecution
****************************************************************************/
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
 */
/*
|<DataModelStart>| CanHL_RxQueueExecution
Relation_Context:
# from Can_MainFunction_Read #
RxQueue
Relation:
GenericPreCopy, OneChOpt, DevErrorDetect
GenericPreCopy, MirrorMode
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_RxQueueExecution( void )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Execute RxQueue (over all channels) */
  while ( Can_GetRxQueueInfo().Count != (uint16)0 )
  { /* #20 over all filled RxQueue elements */
# if (CAN_GENERIC_PRECOPY == STD_ON)
    Can_ReturnType generic_retval;
    CAN_CHANNEL_CANTYPE_LOCAL
    generic_retval = CAN_NOT_OK; /* PRQA S 2982 */ /* MD_MSR_RetVal */
#  if !defined( C_SINGLE_RECEIVE_CHANNEL ) /* otherwise 'channel' is a define */
    channel = Can_GetMailboxController(Can_GetRxQueueBuffer(Can_GetRxQueueInfo().ReadIndex).Hrh);
#   if (CAN_DEV_ERROR_DETECT == STD_ON)
    if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */ /* COV_CAN_GENDATA_FAILURE */
    { /* #30 Check controller is valid */
      errorId = CAN_E_PARAM_CONTROLLER;
    }
    else
#   endif
#  endif
#  if defined(C_ENABLE_MIRROR_MODE)
    if (Can_GetMirrorModeState(channel) == CDDMIRROR_INACTIVE)
    { /* #40 MirrorMode: only when mirror is activated for this controller */
      generic_retval = CAN_OK;
    }
    else
#  endif
    { /* #50 call Appl_GenericPrecopy() */
      generic_retval = Appl_GenericPrecopy( (uint8)channel,
                (Can_GetRxQueueBuffer(Can_GetRxQueueInfo().ReadIndex).id & CAN_ID_MASK_IN_GENERIC_CALLOUT),
                Can_GetRxQueueBuffer(Can_GetRxQueueInfo().ReadIndex).dlc,
                (Can_DataPtrType)Can_GetRxQueueBuffer(Can_GetRxQueueInfo().ReadIndex).data ); /* PRQA S 0312 */ /* MD_Can_NoneVolatilePointerCast */ /* SBSW_CAN_HL06 */
    }
    if (generic_retval == CAN_OK)
# endif
    { /* #60 call CanIf_RxIndication() if Appl_GenericPrecopy() return OK or no generic precopy is used \trace SPEC-1726, SPEC-1688, SPEC-1687, SPEC-1687 */
      CanIf_RxIndication( Can_GetRxQueueBuffer(Can_GetRxQueueInfo().ReadIndex).Hrh, /* SBSW_CAN_HL06 */
              Can_GetRxQueueBuffer(Can_GetRxQueueInfo().ReadIndex).id,
              Can_GetRxQueueBuffer(Can_GetRxQueueInfo().ReadIndex).dlc,
              (Can_DataPtrType)Can_GetRxQueueBuffer(Can_GetRxQueueInfo().ReadIndex).data ); /* PRQA S 0312 */ /* MD_Can_NoneVolatilePointerCast */
    }
    /* #70 EXCLUSIVE_AREA_4 secure RxQueue handling */
    SchM_Enter_Can_CAN_EXCLUSIVE_AREA_4();
    /* #80 get next RxQueue element pointer */
    if (Can_GetRxQueueInfo().ReadIndex >= ((uint16)Can_GetSizeOfRxQueueBuffer() - (uint16)1u) ) /* CM_CAN_HL25 */
    {
      Can_GetRxQueueInfo().ReadIndex = 0u; /* CM_CAN_HL25 */ /* SBSW_CAN_HL55 */
    }
    else
    {
      Can_GetRxQueueInfo().ReadIndex++; /* SBSW_CAN_HL55 */
    }
    Can_GetRxQueueInfo().Count--; /* SBSW_CAN_HL55 */
    SchM_Exit_Can_CAN_EXCLUSIVE_AREA_4();
  }
#if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR) /* PRQA S 2992,2996 */ /* MD_Can_ConstValue */ /* COV_CAN_GENDATA_FAILURE */
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_MAINFCT_READ_ID, errorId); /* PRQA S 2880 */ /*  MD_MSR_Unreachable */
  }
#else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
}
#endif

#if defined(C_ENABLE_CANCEL_TX_IN_HW) 
#endif


/****************************************************************************
| NAME:             CanLL_InitMailboxWriteReg16
****************************************************************************/
/*
|<DataModelStart>| CanLL_InitMailboxWriteReg16
Relation_Context:
# CanHL_InitXXX() #
RamCheck
Relation:
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitMailboxWriteReg16( CAN_CHANNEL_CANTYPE_FIRST CanChipMsgPtr16 regPtr, vuint16 value, vuint16 readMask, CanInitParaStructPtr initPara ) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
{
  vuint8 result = kCanFalse;
  /* #10 write register value */
  *regPtr = value; /* SBSW_CAN_LL03 */
# if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED) 
  if (initPara->doRamCheck == kCanExecuteRamCheck)
  {
    volatile vuint16 readBack = *regPtr;
    /* #20 read back value for RamCheck */
    if ((readBack & readMask) != (value & readMask)) /* COV_CAN_HARDWARE_FAILURE */
    {
      /* #30 return issue when read back value differs */
      result = kCanTrue; /* PRQA S 2981,2982 */ /* MD_MSR_RetVal */
    }
    CAN_RAM_CHECK_READ_BACK_RESULT(channel)
    initPara->isChRamCheckFail |= result; /* SBSW_CAN_LL04 */
  }
# else
  CAN_DUMMY_STATEMENT(readMask); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CAN_DUMMY_STATEMENT(initPara); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  return result;
}
/* CODE CATEGORY 4 END */

/****************************************************************************
| NAME:             CanLL_WriteReg32
****************************************************************************/
/*
|<DataModelStart>| CanLL_WriteReg32
Relation_Context:
# CanHL_InitXXX() #
RamCheck
Relation:
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_WriteReg32( CAN_CHANNEL_CANTYPE_FIRST CanChipMsgPtr32 regPtr, vuint32 value, vuint32 readMask, CanInitParaStructPtr initPara ) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
{
  /* #10 write register value */
  *regPtr = value; /* SBSW_CAN_LL03 */
# if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED) 
  if (initPara->doRamCheck == kCanExecuteRamCheck)
  {
    vuint8 result = kCanFalse; /* PRQA S 2981,2982 */ /* MD_MSR_RetVal */
    volatile vuint32 readBack = *regPtr;
    /* #20 read back value for RamCheck */
    if ((readBack & readMask) != (value & readMask)) /* COV_CAN_HARDWARE_FAILURE */
    {
      /* #30 return issue when read back value differs */
      result = kCanTrue; /* PRQA S 2981,2982 */ /* MD_MSR_RetVal */
    }
    CAN_RAM_CHECK_READ_BACK_RESULT(channel)
    initPara->isChRamCheckFail |= result; /* SBSW_CAN_LL04 */
  }
# else
  CAN_DUMMY_STATEMENT(readMask); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CAN_DUMMY_STATEMENT(initPara); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
}
/* CODE CATEGORY 4 END */

# if defined( C_ENABLE_RX_FULLCAN_OBJECTS ) || defined( C_ENABLE_RX_BASICCAN_OBJECTS )
/****************************************************************************
| NAME:             CanLL_InitMailboxWriteReg32
****************************************************************************/
/*
|<DataModelStart>| CanLL_InitMailboxWriteReg32
Relation_Context:
# CanHL_InitXXX() #
RamCheck
Relation:
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitMailboxWriteReg32( CAN_CHANNEL_CANTYPE_FIRST CanChipMsgPtr32 regPtr, vuint32 value, vuint32 readMask, CanInitParaStructPtr initPara ) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
{
  vuint8 result = kCanFalse;
  /* #10 write register value */
  *regPtr = value; /* SBSW_CAN_LL03 */
#  if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED) 
  if (initPara->doRamCheck == kCanExecuteRamCheck)
  {
    volatile vuint32 readBack = *regPtr;
    /* #20 read back value for RamCheck */
    if ((readBack & readMask) != (value & readMask)) /* COV_CAN_HARDWARE_FAILURE */
    {
      /* #30 return issue when read back value differs */
      result = kCanTrue; /* PRQA S 2981,2982 */ /* MD_MSR_RetVal */
    }
    CAN_RAM_CHECK_READ_BACK_RESULT(channel)
    initPara->isChRamCheckFail |= result; /* SBSW_CAN_LL04 */
  }
#  else
  CAN_DUMMY_STATEMENT(readMask); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CAN_DUMMY_STATEMENT(initPara); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#  endif
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#  endif
  return result;
}
/* CODE CATEGORY 4 END */
# endif


/****************************************************************************
| NAME:             CanLL_WriteProtectedReg16
****************************************************************************/
/*
|<DataModelStart>| CanLL_WriteProtectedReg16
Relation_Context:
# CanHL_InitXXX() #
RamCheck
Relation:
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_WriteProtectedReg16( CAN_CHANNEL_CANTYPE_FIRST vuint16 area, CanChipMsgPtr16 regPtr, vuint16 value, vuint16 readMask, CanInitParaStructPtr initPara ) /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */
{
  /* #10 write register value */
  CAN_WRITE_PROTECTED_REG16(area, regPtr, value); /* SBSW_CAN_LL01 */
# if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED) 
  if (initPara->doRamCheck == kCanExecuteRamCheck)
  {
    vuint8 result = kCanFalse; /* PRQA S 2981,2982 */ /* MD_MSR_RetVal */
    volatile vuint16 readBack = CAN_READ_PROTECTED_REG16(area, regPtr); /* SBSW_CAN_LL01 */
    /* #20 read back value for RamCheck */
    if ((readBack & readMask) != (value & readMask)) /* COV_CAN_HARDWARE_FAILURE */
    {
      /* #30 return issue when read back value differs */
      result = kCanTrue; /* PRQA S 2981,2982 */ /* MD_MSR_RetVal */
    }
    CAN_RAM_CHECK_READ_BACK_RESULT(channel)
    initPara->isChRamCheckFail |= result; /* SBSW_CAN_LL04 */
  }
# else
  CAN_DUMMY_STATEMENT(readMask); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CAN_DUMMY_STATEMENT(initPara); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  CAN_DUMMY_STATEMENT(area); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
} /* PRQA S 6060 */ /* MD_MSR_STPAR */
/* CODE CATEGORY 4 END */


/**********************************************************************************************************************
 *  CanLL_InitBegin
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_InitBegin
Relation_Context:
# CanHL_InitBegin() #
OneChOpt, ChannelAmount
Relation:
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
 *
*/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitBegin( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara ) /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */
{
  vuint8 returnValue;


  /* #10 Set FlexCAN to Init Mode */
  returnValue = CanLL_SetFlexCANToInitMode(CAN_HW_CHANNEL_CANPARA_FIRST initPara->initObject);
  if (returnValue == kCanOk) /* COV_CAN_LL_HARDWARE_BEHAVIOUR */
  {
    /* #20 Perform a soft reset */
    returnValue = CanLL_ExecuteSoftReset(CAN_HW_CHANNEL_CANPARA_ONLY);
  }

  return(returnValue);
}
/* CODE CATEGORY 4 END */

#if defined( C_ENABLE_CAN_RAM_CHECK_EXTENDED )
/**********************************************************************************************************************
 *  CanLL_InitBeginIsRegisterCorrupt
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_InitBeginIsRegisterCorrupt
Relation_Context:
# CanHL_InitBegin() #
OneChOpt, ChannelAmount, RamCheck
Relation:
CanFdSupport
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
*/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitBeginIsRegisterCorrupt( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara )

{
    /* ----- Local Variables ---------------------------------------------- */
  vuint16 tmpCANmaxmb;
  vuint8 loopRamCheckCounter;
  vuint8 result;
  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);
  vuint32 tmpRamCheckPattern;
# if defined ( C_ENABLE_FLEXCAN_PARITY_CHECK_AVAILABLE )
  tParityCheckPtr pParityCheckLocal = pCanParityCheck(canHwChannel);
# endif
# if defined( C_ENABLE_GLITCH_FILTER )
  tGlitchFilterPtr pGlitchFilterLocal = pCanGlitchFilter(canHwChannel);
# endif
  
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Load MAXMB Pattern and remove FD enable bit if FD is not supported on this channel */
  tmpCANmaxmb = kCanRamCheckMaskMAXMB;
# if defined( C_ENABLE_CAN_FD_USED )
  if (!Can_IsHasCANFDBaudrateOfControllerConfig(canHwChannel)) /* COV_CAN_FD_BAUDRATE_AVAILABILITY */
  {
    /* Remove FD Flag in case of HwChannel does not support CANFD */
    tmpCANmaxmb &= ((vuint16) ~kFlexCAN_FDEN);
  }
# endif
  /* #20 Check CLKSRC bit in control1 register */
# if defined( C_ENABLE_CLKSRC_SELECTION ) /* COV_CAN_RAMCHECK_EXTENDED_CLKSRC_AVAILABILITY */
  result = CanLL_CheckClockSource(CAN_HW_CHANNEL_CANPARA_ONLY);
# else
  result = kCanFalse;
# endif

  /* #30 Iterate test patterns */
  for (loopRamCheckCounter = 0u; loopRamCheckCounter < 3u; loopRamCheckCounter++)
  {
    /* #40 Write MCR and MAXMB register */
    CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kCanRamCheckMaskMCR); /* SBSW_CAN_LL01 */
    CAN_WRITE_PROTECTED_REG_SET(pFlexCANLocal->canmcr, (ramCheckPattern16[loopRamCheckCounter] & kCanRamCheckMaskMCR)); /* SBSW_CAN_LL01 */
    
    CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmaxmb, tmpCANmaxmb); /* SBSW_CAN_LL01 */
    CAN_WRITE_PROTECTED_REG_SET(pFlexCANLocal->canmaxmb, (ramCheckPattern16[loopRamCheckCounter] & tmpCANmaxmb)); /* SBSW_CAN_LL01 */
    
    /* #50 Check the register contents */
    if(  ((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kCanRamCheckMaskMCR) != (ramCheckPattern16[loopRamCheckCounter] & kCanRamCheckMaskMCR))
      || ((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmaxmb) & tmpCANmaxmb) != (ramCheckPattern16[loopRamCheckCounter] & tmpCANmaxmb))) /* COV_CAN_HARDWARE_FAILURE */ /* SBSW_CAN_LL01 */ /* SBSW_CAN_LL01 */
    {
      result = kCanTrue;
      break; /* no need to carry on if check already failed */
    }
  }

  /* #60 Set all CAN register except the MCR register in unrestricted memory space */
  CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_SUPV); /* SBSW_CAN_LL01 */

  /* #70 Set WRNEN flag in CAN_MCR register to check TWRNMSK and RWRNMASK in CTRL1 register */
  CAN_WRITE_PROTECTED_REG_SET(pFlexCANLocal->canmcr, kFlexCAN_WRN_EN); /* SBSW_CAN_LL01 */

  /* #80 Iterate test patterns */
  for (loopRamCheckCounter = 0u; loopRamCheckCounter < 3u; loopRamCheckCounter++)
  {
    /* #90 Write CTRL1 register */
    pFlexCANLocal->control1 &= ~kCanRamCheckMaskCONTROL1; /* SBSW_CAN_LL01 */
    pFlexCANLocal->control1 |= ramCheckPattern32[loopRamCheckCounter] & kCanRamCheckMaskCONTROL1; /* SBSW_CAN_LL01 */
    
# if defined ( C_ENABLE_FLEXCAN_PARITY_CHECK_AVAILABLE )
    /* enable ECRWRE flag in CTRL2 register to get write access for MECR register */
    pFlexCANLocal->ctrl2 |= kFlexCAN_ECRWRE; /* SBSW_CAN_LL01 */
    /* #100 Write MECR register if available */
    pParityCheckLocal->mecr &= (vuint32)(~kFlexCAN_ECRWRDIS); /* SBSW_CAN_LL09 */
    pParityCheckLocal->mecr = ramCheckPattern32[loopRamCheckCounter] & kCanRamCheckMaskMECR; /* SBSW_CAN_LL09 */
# endif

    /* #110 Write CTRL2 register */
    pFlexCANLocal->ctrl2 = ramCheckPattern32[loopRamCheckCounter] & kCanRamCheckMaskCTRL2; /* SBSW_CAN_LL01 */
    
    /* #120 Write ECR register */
    pFlexCANLocal->ecr = ramCheckPattern32[loopRamCheckCounter] & kCanRamCheckMaskECR; /* SBSW_CAN_LL01 */
    
    /* #130 Write IMASK1 register */
    tmpRamCheckPattern = ramCheckPattern32[loopRamCheckCounter];

# if defined (C_ENABLE_ASYM_MAILBOXES) /* COV_CAN_FLEXCAN3_DERIVATIVE_ASYM_MAILBOXES */
    if (NUMBER_OF_MAX_MAILBOXES(canHwChannel) < 32u) /* PRQA S 2741,2742 */ /* MD_Can_ConstValue */ /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
    {
      tmpRamCheckPattern = (vuint32) ramCheckPattern16[loopRamCheckCounter]; /* PRQA S 2880 */ /*  MD_MSR_Unreachable */
    }
# endif
    pFlexCANLocal->imask1 = tmpRamCheckPattern; /* SBSW_CAN_LL01 */
    
# if defined ( C_ENABLE_MB32TO63 ) /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
    /* #140 Write IMASK2 register */
#  if defined (C_ENABLE_ASYM_MAILBOXES) /* COV_CAN_FLEXCAN3_DERIVATIVE_ASYM_MAILBOXES */
    if (NUMBER_OF_MAX_MAILBOXES(canHwChannel) > 32u) /* PRQA S 2741,2742 */ /* MD_Can_ConstValue */ /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
#  endif
    {
      pFlexCANLocal->imask2 = ramCheckPattern32[loopRamCheckCounter]; /* SBSW_CAN_LL01 */
    }
# endif
  
# if defined ( C_ENABLE_MB64TO95 ) /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
    /* #150 Write IMASK3 register */
#  if defined (C_ENABLE_ASYM_MAILBOXES) /* COV_CAN_FLEXCAN3_DERIVATIVE_ASYM_MAILBOXES */
    if (NUMBER_OF_MAX_MAILBOXES(canHwChannel) > 64u) /* PRQA S 2741,2742 */ /* MD_Can_ConstValue */ /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
#  endif
    {
      pFlexCANLocal->imask3 = ramCheckPattern32[loopRamCheckCounter]; /* SBSW_CAN_LL01 */
    }
# endif
    
# if defined ( C_ENABLE_MB96TO127 ) /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
    /* #160 Write IMASK4 register */
    pFlexCANLocal->imask4 = ramCheckPattern32[loopRamCheckCounter]; /* SBSW_CAN_LL01 */
# endif
    
# if defined( C_ENABLE_EXTENDED_BITTIMING )
    /* #170 Write CBT register */
    pFlexCANLocal->cbt = ramCheckPattern32[loopRamCheckCounter] & kCanRamCheckMaskCBT; /* SBSW_CAN_LL01 */
# endif
    
# if defined( C_ENABLE_GLITCH_FILTER )
    /* #180 Write GFWR register */
    pGlitchFilterLocal->gfwR = ramCheckPattern32[loopRamCheckCounter] & kCanRamCheckMaskGFWR; /* SBSW_CAN_LL09 */
# endif

    /* #190 Write RXGMASK register */
    pFlexCANLocal->rxfgmask = ramCheckPattern32[loopRamCheckCounter]; /* SBSW_CAN_LL01 */
    
    /* #200 Check the register contents  */
    if( ((pFlexCANLocal->control1 & kCanRamCheckMaskCONTROL1) != (ramCheckPattern32[loopRamCheckCounter] & kCanRamCheckMaskCONTROL1))      ||
        ((pFlexCANLocal->ecr & kCanRamCheckMaskECR) != (ramCheckPattern32[loopRamCheckCounter] & kCanRamCheckMaskECR))                     ||
        ((pFlexCANLocal->ctrl2 & kCanRamCheckMaskCTRL2) != (ramCheckPattern32[loopRamCheckCounter] & kCanRamCheckMaskCTRL2))               ||
         (pFlexCANLocal->imask1 != tmpRamCheckPattern)                                                                                     ||
# if defined ( C_ENABLE_MB96TO127 ) /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
         (pFlexCANLocal->imask4 != ramCheckPattern32[loopRamCheckCounter])                                                                 ||
# endif
# if defined( C_ENABLE_EXTENDED_BITTIMING )
        ((pFlexCANLocal->cbt & kCanRamCheckMaskCBT) != (ramCheckPattern32[loopRamCheckCounter] & kCanRamCheckMaskCBT))                     ||
# endif
# if defined( C_ENABLE_GLITCH_FILTER )
        ((pGlitchFilterLocal->gfwR & kCanRamCheckMaskGFWR) != (ramCheckPattern32[loopRamCheckCounter] & kCanRamCheckMaskGFWR)) ||
# endif
# if defined ( C_ENABLE_FLEXCAN_PARITY_CHECK_AVAILABLE )
        ((pParityCheckLocal->mecr & kCanRamCheckMaskMECR) != (ramCheckPattern32[loopRamCheckCounter] & kCanRamCheckMaskMECR))  /* SBSW_CAN_LL09 */ ||
# endif
        (pFlexCANLocal->rxfgmask != ramCheckPattern32[loopRamCheckCounter])
      ) /* COV_CAN_HARDWARE_FAILURE */
    {
      result = kCanTrue;
    }
    else
    {
# if defined ( C_ENABLE_MB32TO63 ) /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
#  if defined ( C_ENABLE_ASYM_MAILBOXES ) /* COV_CAN_FLEXCAN3_DERIVATIVE_ASYM_MAILBOXES */
      if (NUMBER_OF_MAX_MAILBOXES(canHwChannel) > 32u) /* PRQA S 2741,2742 */ /* MD_Can_ConstValue */ /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
#  endif
      {
        if (pFlexCANLocal->imask2 != ramCheckPattern32[loopRamCheckCounter]) /* COV_CAN_HARDWARE_FAILURE */
        {
          result = kCanTrue;
        }
      }
# endif
# if defined ( C_ENABLE_MB64TO95 ) /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
#  if defined ( C_ENABLE_ASYM_MAILBOXES ) /* COV_CAN_FLEXCAN3_DERIVATIVE_ASYM_MAILBOXES */
      if (NUMBER_OF_MAX_MAILBOXES(canHwChannel) > 64u) /* PRQA S 2741,2742 */ /* MD_Can_ConstValue */ /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
#  endif
      {
        if (pFlexCANLocal->imask3 != ramCheckPattern32[loopRamCheckCounter]) /* COV_CAN_HARDWARE_FAILURE */
        {
          result = kCanTrue;
        }
      }
# endif
    }

    if (result == kCanTrue) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
    {
       break; /* no need to carry on if check already failed */
    }
  }
  CAN_RAM_CHECK_READ_BACK_RESULT(channel);
  CAN_DUMMY_STATEMENT(initPara); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return result;
} /* PRQA S 6010,6030 */ /* MD_MSR_STPTH,MD_MSR_STCYC */
/* CODE CATEGORY 4 END */
#endif /* C_ENABLE_CAN_RAM_CHECK_EXTENDED */

/**********************************************************************************************************************
 *  CanLL_InitBeginSetRegisters
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_InitBeginSetRegisters
Relation_Context:
# CanHL_InitBegin() #
OneChOpt, ChannelAmount
Relation:
HwCancelTx
CanFdSupport
StatusPolling
Tasd
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitBeginSetRegisters( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara )
{
  vuint16 tmpCANmaxmb, tmpCANmcr;
  vuint32 tmpCANctrl2, tmpCANcontrol1;
  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);
#if defined ( C_ENABLE_FLEXCAN_PARITY_CHECK_AVAILABLE )
  tParityCheckPtr pParityCheckLocal = pCanParityCheck(canHwChannel);
#endif
#if defined( C_ENABLE_GLITCH_FILTER )
  tGlitchFilterPtr pGlitchFilterLocal = pCanGlitchFilter(canHwChannel);
#endif

  /* #10 Configure CAN[MCR].MAXMB register value */
  tmpCANmaxmb = ((vuint16)CAN_HL_HW_TX_STOPINDEX(canHwChannel) - (vuint16)1u)
#if defined( C_ENABLE_CANCEL_IN_HW )
  /* #11 Set AEN bit to enable Abort feature (Cancel in Hardware) */
  | kFlexCAN_AEN
#endif
  ;
#if defined( C_ENABLE_CAN_FD_USED )
  if (Can_IsHasCANFDBaudrateOfControllerConfig(channel)) /* COV_CAN_FD_BAUDRATE_AVAILABILITY */
  {
    /* #12 Set FDEN bit to enable CAN FD */
    tmpCANmaxmb |= kFlexCAN_FDEN;
  }
#endif 
  /* #15 Write configured value to register */
  CanLL_WriteProtectedReg16(CAN_CHANNEL_CANPARA_FIRST CAN_AREA(canHwChannel), &pFlexCANLocal->canmaxmb, tmpCANmaxmb, kCanRamCheckMaskMAXMB, initPara); /* SBSW_CAN_LL01 */
  
  /* #20 Configure CAN[MCR].MCR register value */
  tmpCANmcr = CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kNotFlexCAN_MCR_CFG_BTIS; /* SBSW_CAN_LL01 */
  /* #21 Set IRMQ bit to allow individual buffer masking configuration */
  tmpCANmcr |= kFlexCAN_IRMQ
  /* #22 Set SRXDIS bit to disable self-reception feature */
  | kFlexCAN_SRX_DIS
#if defined( C_ENABLE_GLITCH_FILTER )
  /* #23 Set WAK_SRC bit to integrate low-pass filter to protect the FLEXCAN_RX input from spurious wake up */
  | kFlexCAN_WAK_SRC
#endif
#if !defined( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
  /* #24 Set FEN bit to enable RX FIFO */
  | kFlexCAN_FEN
#endif
  ;
  /* #29 Write configured value to register */
  CanLL_WriteProtectedReg16(CAN_CHANNEL_CANPARA_FIRST CAN_AREA(canHwChannel), &pFlexCANLocal->canmcr, tmpCANmcr, kCanRamCheckMaskMCR, initPara); /* SBSW_CAN_LL01 */
 
  /* #30 Configure CAN[CTRL1] register value */
# if defined( C_ENABLE_EXTENDED_BITTIMING )
  tmpCANcontrol1 = Can_GetControl1OfInitObject(initPara->initObject) & (kFlexCAN_CLK_SRC | kFlexCAN_SMP);
# else
  tmpCANcontrol1 = Can_GetControl1OfInitObject(initPara->initObject);
# endif
  /* #32 Disable BusOff Auto Recovery */
  tmpCANcontrol1 |= kFlexCAN_BOFF_REC;
# if defined( C_ENABLE_CAN_BUSOFF_INTERRUPT )  
  /* #33 Enable BusOff interrupt */
  if(Can_GetCanInterruptCounter(channel) == 0u)
  {
    tmpCANcontrol1 |= kFlexCAN_BOFF_MSK;
  }
# endif
  /* #39 Write configured value to register */
  CanLL_WriteReg32(CAN_CHANNEL_CANPARA_FIRST &pFlexCANLocal->control1, tmpCANcontrol1, kCanMaskAll32, initPara); /* SBSW_CAN_LL01 */

#if defined( C_ENABLE_EXTENDED_BITTIMING )
  /* #40 Write CAN[CBT] register value (extended bit timing) */
  CanLL_WriteReg32(CAN_CHANNEL_CANPARA_FIRST &pFlexCANLocal->cbt, Can_GetCBTOfInitObject(initPara->initObject), kCanMaskAll32, initPara); /* SBSW_CAN_LL01 */
#endif

#if defined( C_ENABLE_CAN_FD_USED )
  if (Can_IsHasCANFDBaudrateOfControllerConfig(canHwChannel)) /* COV_CAN_FD_BAUDRATE_AVAILABILITY */
  {
    tCanFDRegisterPtr pCanFDRegisterLocal = pCanFDRegister(canHwChannel);
    /* #50 Write CAN[FDCTRL] register value (CAN FD control) */
    CanLL_WriteReg32(CAN_CHANNEL_CANPARA_FIRST &pCanFDRegisterLocal->fdctrl, Can_GetFDCTRLOfInitObjectFD(initPara->initObject), kCanMaskAll32, initPara); /* SBSW_CAN_LL09 */
    /* #60 Write CAN[FDCBT] register value (CAN FD bit timing) */
    CanLL_WriteReg32(CAN_CHANNEL_CANPARA_FIRST &pCanFDRegisterLocal->fdcbt, Can_GetFDCBTOfInitObjectFD(initPara->initObject), kCanMaskAll32, initPara); /* SBSW_CAN_LL09 */
  }
#endif

  /* #70 Configure CAN[CTRL2] register value */
  /* #71 Set RFFN value */
  tmpCANctrl2 = RFFN_VALUE(canHwChannel) | kFlexCAN_MRP | kFlexCAN_RRS | kFlexCAN_EACEN

  /* #72 Set ECR Write Enable */
#if defined ( C_ENABLE_FLEXCAN_PARITY_CHECK_AVAILABLE )
  | kFlexCAN_ECRWRE
#endif
  /* #73 Set TASD Value */
#if defined( C_ENABLE_TASD )
  | Can_GetTASDOfInitObject(initPara->initObject)
#else
  | kFlexCAN_TASD_DEFAULT
#endif
  ;
#if defined( C_ENABLE_CAN_FD_USED )
# if defined (C_ENABLE_ISO_CANFD)
  /* #74 Set CAN ISO FD */
  if (Can_IsHasCANFDBaudrateOfControllerConfig(channel)) /* COV_CAN_FD_BAUDRATE_AVAILABILITY */
  {
    tmpCANctrl2 |= kFlexCAN_STFCNTEN;
  }
# endif
#endif
  /* #79 Write configured value to register */
  CanLL_WriteReg32(CAN_CHANNEL_CANPARA_FIRST &pFlexCANLocal->ctrl2, tmpCANctrl2, kCanMaskAll32, initPara); /* SBSW_CAN_LL01 */

#if defined ( C_ENABLE_FLEXCAN_PARITY_CHECK_AVAILABLE )
  /* #80 Enable write on MECR register */
  pParityCheckLocal->mecr &= (vuint32)(~kFlexCAN_ECRWRDIS); /* SBSW_CAN_LL09 */
  /* #81 Configuration of MECR register */
# if !defined ( C_ENABLE_FLEXCAN_PARITY_CHECK )
  /* #82 Disable parity check functionality (not supported but enabled by default) */
  CanLL_WriteReg32(CAN_CHANNEL_CANPARA_FIRST &pParityCheckLocal->mecr, (vuint32)(kFlexCAN_Disable_ParityCheck), kCanMaskAll32, initPara); /* SBSW_CAN_LL09 */
# endif
  /* #83 Disable write on MECR register */
  pParityCheckLocal->mecr |= kFlexCAN_ECRWRDIS; /* SBSW_CAN_LL09 */
  /* #84 Clear Error Status register */
  pParityCheckLocal->errStatusR = kFlexCAN_Clear_Parity_Status; /* SBSW_CAN_LL09 */
#endif

#if defined( C_ENABLE_GLITCH_FILTER )
  /* # 90 Configure glitch filter register value */
  CanLL_WriteReg32(CAN_CHANNEL_CANPARA_FIRST &pGlitchFilterLocal->gfwR, GLITCH_FILTER_WIDTH(canHwChannel), kCanMaskAll32, initPara); /* SBSW_CAN_LL09 */
#endif

  return(kCanOk);
}
/* CODE CATEGORY 4 END */

/**********************************************************************************************************************
 *  CanLL_InitMailboxTx
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_InitMailboxTx
Relation_Context:
# CanHL_InitTxFullCAN() #
OneChOpt, ChannelAmount
# CanHL_InitTxBasicCAN() #
OneChOpt, ChannelAmount
Relation:
TxFullCANSupport
MultiplexedTx,DevErrorDetect
CanFdSupport
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
 *
 *
*/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitMailboxTx( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara )
{
  vuint8 retVal = kCanFailed; /* PRQA S 2981,2982 */ /* MD_MSR_RetVal */
#if !defined ( C_ENABLE_CAN_FD_FULL )
  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);
#endif


  /* #10 Configure TX mailbox to INACTIVE */
# if defined(C_ENABLE_MULTIPLEXED_TRANSMISSION)
  if ( (initPara->mailboxHandle >= CAN_HL_MB_TX_BASIC_STARTINDEX(canHwChannel)) && (initPara->mailboxHandle < CAN_HL_MB_TX_BASIC_STOPINDEX(canHwChannel)) ) /* COV_CAN_MAILBOX_ORDER */
  {
    CanObjectHandle mailboxElement;
#  if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
    /* #20 Check for valid hwObject handle (multiplexed transmission) */
    if (CanLL_CheckMaxHwMailboxHandle(canHwChannel, (initPara->hwObjHandle + Can_GetMailboxSize(initPara->mailboxHandle)) - 1u) == kCanOk) /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL04 */
#  endif
    {
      retVal = kCanOk;
      for (mailboxElement = 0u; mailboxElement < Can_GetMailboxSize(initPara->mailboxHandle); mailboxElement++)
      {
        retVal &= ~CanLL_InitMailboxWriteReg16( CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &LOCAL_MAILBOX_ACCESS(canHwChannel, (vuint16)(initPara->hwObjHandle) + (vuint16)mailboxElement, control), kTxCodeInactive, kCanRamCheckMailboxControl, initPara ); /* SBSW_CAN_LL02 */ /* PRQA S 2985 */ /* MD_Can_ConstValue */
      }
    }
  }
  else
# endif
  {
# if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
    /* #30 Check for valid hwObject handle */
    if (CanLL_CheckMaxHwMailboxHandle(canHwChannel, initPara->hwObjHandle) == kCanOk) /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL04 */
# endif
    {
      retVal = kCanOk;
      retVal &= ~CanLL_InitMailboxWriteReg16( CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &LOCAL_MAILBOX_ACCESS(canHwChannel, initPara->hwObjHandle, control), kTxCodeInactive, kCanRamCheckMailboxControl, initPara ); /* SBSW_CAN_LL02 */ /* PRQA S 2985 */ /* MD_Can_ConstValue */
    }
  }
  return(retVal);
}
/* CODE CATEGORY 4 END */

# if (defined( C_ENABLE_CAN_RAM_CHECK ))
/**********************************************************************************************************************
 *  CanLL_InitMailboxTxDeactivate
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_InitMailboxTxDeactivate
Relation_Context:
# CanHL_InitTxFullCAN() #
OneChOpt, ChannelAmount
# CanHL_InitTxBasicCAN() #
OneChOpt, ChannelAmount
Relation:
TxFullCANSupport, RamCheck
MultiplexedTx, RamCheck
CanFdSupport
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
*/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_InitMailboxTxDeactivate( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara ) /* COV_CAN_RAM_CHECK_NO_STIMULATION */ /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */
{
#  if !defined ( C_ENABLE_CAN_FD_FULL )
  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);
#  endif

  /* #10 Deactivate transmit mailbox */
#  if defined(C_ENABLE_MULTIPLEXED_TRANSMISSION)
  if ( (initPara->mailboxHandle >= CAN_HL_MB_TX_BASIC_STARTINDEX(canHwChannel)) && (initPara->mailboxHandle < CAN_HL_MB_TX_BASIC_STOPINDEX(canHwChannel)) ) /* COV_CAN_MAILBOX_ORDER */
  {
    CanObjectHandle mailboxElement;
    for (mailboxElement = 0u; mailboxElement < Can_GetMailboxSize(initPara->mailboxHandle); mailboxElement++)
    {
      LOCAL_MAILBOX_ACCESS(canHwChannel, (vuint16)initPara->hwObjHandle + (vuint16)mailboxElement, control) = 0u; /* set all mailboxes inactive */ /* SBSW_CAN_LL02 */
    }
  }
  else
#  endif
  {
    LOCAL_MAILBOX_ACCESS(canHwChannel, initPara->hwObjHandle, control) = 0u; /* SBSW_CAN_LL02 */
  }
}
/* CODE CATEGORY 4 END */
# endif


#if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
/**********************************************************************************************************************
 *  CanLL_InitMailboxRxFullCan
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_InitMailboxRxFullCan
Relation_Context:
# CanHL_InitRxFullCAN() #
OneChOpt, ChannelAmount, RxFullCANSupport
Relation:
CanFdSupport
DevErrorDetect
IDType
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
 *
 *
 *
*/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitMailboxRxFullCan( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara )
{
  vuint8 retVal = kCanFailed; /* PRQA S 2981,2982 */ /* MD_MSR_RetVal */
# if !defined ( C_ENABLE_CAN_FD_FULL )
  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);
# endif
  
# if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
  /* #10 Check for valid hwObject handle */
  if (CanLL_CheckMaxHwMailboxHandle(canHwChannel, initPara->hwObjHandle) == kCanOk) /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL04 */
# endif
  {
    tCanRxMaskPtr pIndivRxMask = pCanRxMask(canHwChannel); /* pointer to FlexCAN individual receive mask registers */
    retVal = kCanOk;

    /* #20 Set message ID */
    retVal &= ~CanLL_InitMailboxWriteReg32( CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &LOCAL_MAILBOX_ACCESS(canHwChannel, initPara->hwObjHandle, msgID), CAN_MSGID(initPara->idRaw0), kCanMaskAll32, initPara ); /* SBSW_CAN_LL02 */ /* PRQA S 2985 */ /* MD_Can_ConstValue */
    /* #30 set ID type and set mailbox ready for receive */
    retVal &= ~CanLL_InitMailboxWriteReg16( CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &LOCAL_MAILBOX_ACCESS(canHwChannel, initPara->hwObjHandle, control), kRxCodeEmpty | (vuint16)(initPara->idType), kCanRamCheckMailboxControl, initPara ); /* SBSW_CAN_LL02 */ /* PRQA S 2985 */ /* MD_Can_ConstValue */

    /* #40 Initialize individual mask values for each FullCAN mailbox */
# if defined( C_ENABLE_EXTENDED_ID )
#  if defined( C_ENABLE_MIXED_ID )
    if((LOCAL_MAILBOX_ACCESS(canHwChannel, initPara->hwObjHandle, control) & (vuint16)kCanIdTypeExt) == 0u) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */ /* SBSW_CAN_LL02 */
    {
      retVal &= ~CanLL_InitMailboxWriteReg32( CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &pIndivRxMask->indivRxMask[initPara->hwObjHandle], kCanRxMaskStd, kCanMaskAll32, initPara ); /* SBSW_CAN_LL09 */ /* PRQA S 2985 */ /* MD_Can_ConstValue */
    }
    else
#  endif
    {
      retVal &= ~CanLL_InitMailboxWriteReg32( CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &pIndivRxMask->indivRxMask[initPara->hwObjHandle], kCanRxMaskExt, kCanMaskAll32, initPara ); /* SBSW_CAN_LL09 */ /* PRQA S 2985 */ /* MD_Can_ConstValue */
    }
# else
    retVal &= ~CanLL_InitMailboxWriteReg32( CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &pIndivRxMask->indivRxMask[initPara->hwObjHandle], kCanRxMaskStd, kCanMaskAll32, initPara ); /* SBSW_CAN_LL09 */ /* PRQA S 2985 */ /* MD_Can_ConstValue */
# endif
  }
  return(retVal);
}
/* CODE CATEGORY 4 END */

# if ((defined( C_ENABLE_CAN_RAM_CHECK )))
/**********************************************************************************************************************
 *  CanLL_InitMailboxRxFullCanDeactivate
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_InitMailboxRxFullCanDeactivate
Relation_Context:
# CanHL_InitRxFullCAN() #
OneChOpt, ChannelAmount, RxFullCANSupport, RamCheck
Relation:
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
*/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_InitMailboxRxFullCanDeactivate( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara ) /* COV_CAN_RAM_CHECK_NO_STIMULATION */ /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */
{
  /* #10 Deactivate receive mailbox */
  GLOBAL_MAILBOX_ACCESS(canHwChannel, initPara->hwObjHandle, control) = 0u; /* deactivate receive mailbox */ /* SBSW_CAN_LL02 */
}
/* CODE CATEGORY 4 END */
# endif

#endif /* C_ENABLE_RX_FULLCAN_OBJECTS */

#if defined( C_ENABLE_RX_BASICCAN_OBJECTS )
/**********************************************************************************************************************
 *  CanLL_InitMailboxRxBasicCan
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_InitMailboxRxBasicCan
Relation_Context:
# CanHL_InitRxBasicCAN() #
Wakeup, OneChOpt, ChannelAmount, RxBasicCANSupport
Relation:
CanFdSupport,DevErrorDetect,IDType
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
*/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitMailboxRxBasicCan( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara )
{
  vuint8 retVal = kCanFailed; /* PRQA S 2981,2982 */ /* MD_MSR_RetVal */
# if !defined ( C_ENABLE_CAN_FD_FULL )
  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);
# endif
  vuint8 filterHandle;
# if defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
  CanObjectHandle hwObjCount;
  CanObjectHandle hwObjHandle;
# else
  vuint32 locMsgIDMask;
  tRXFIFOPtr pRxFIFO = pRXFIFO(canHwChannel);
# endif
  tCanRxMaskPtr pIndivRxMask = pCanRxMask(canHwChannel); /* pointer to FlexCAN individual receive mask registers */

# if defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
#  if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
  /* #10 Check for valid hwObject handle (Classic Layout) */
  if (CanLL_CheckMaxHwMailboxHandle(canHwChannel, (initPara->hwObjHandle + Can_GetMailboxSize(initPara->mailboxHandle)) - 1u) == kCanOk) /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL04 */
#  endif
  {
    retVal = kCanOk;
    /* #20 No Rx-Fifo: configure RX BASICCAN hardware objects */
    for (hwObjCount = 0u; hwObjCount < Can_GetMailboxSize(initPara->mailboxHandle); hwObjCount++)
    {
      hwObjHandle = initPara->hwObjHandle + hwObjCount;
      filterHandle = (vuint8)((vuint16)Can_GetInitBasicCanIndex(initPara->initObject) + ((vuint16)hwObjHandle - (vuint16)(Can_GetMailboxHwHandle(CAN_HL_MB_RX_BASIC_STARTINDEX(canHwChannel))))); /* calculate BasicCan offset */
      /* #30 Configure message ID */
      retVal &= ~CanLL_InitMailboxWriteReg32( CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, msgID), Can_GetInitCodeOfInitBasicCan(filterHandle) & (vuint32)0x1FFFFFFFu, kCanMaskAll32, initPara ); /* SBSW_CAN_LL02 */ /* PRQA S 2985 */ /* MD_Can_ConstValue */
      /* #40 Configure mask */
      retVal &= ~CanLL_InitMailboxWriteReg32( CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &pIndivRxMask->indivRxMask[hwObjHandle], (Can_GetInitMaskOfInitBasicCan(filterHandle) & (vuint32)0x1FFFFFFFu) | 0xC0000000u, kCanMaskAll32, initPara ); /* SBSW_CAN_LL09 */ /* PRQA S 2985 */ /* MD_Can_ConstValue */
      /* #50 Configure mailbox as empty and consider CAN ID type */
#  if defined(C_ENABLE_EXTENDED_ID)
#   if defined(C_ENABLE_MIXED_ID)   
      if((Can_GetInitCodeOfInitBasicCan(filterHandle) & kExtIDBit) == 0u) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
      {
        retVal &= ~CanLL_InitMailboxWriteReg16( CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control), kRxCodeEmpty, kCanRamCheckMailboxControl, initPara ); /* SBSW_CAN_LL02 */ /* PRQA S 2985 */ /* MD_Can_ConstValue */
      }
      else
#   endif
      {
        retVal &= ~CanLL_InitMailboxWriteReg16( CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control), kRxCodeEmpty | (vuint16)kCanIdTypeExt, kCanRamCheckMailboxControl, initPara ); /* SBSW_CAN_LL02 */ /* PRQA S 2985 */ /* MD_Can_ConstValue */
      }
  #  else
      retVal &= ~CanLL_InitMailboxWriteReg16( CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control), kRxCodeEmpty, kCanRamCheckMailboxControl, initPara ); /* SBSW_CAN_LL02 */ /* PRQA S 2985 */ /* MD_Can_ConstValue */
#  endif
    }
  }

# else /* C_ENABLE_CLASSIC_MAILBOX_LAYOUT */
  {
#  if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
    /* #60 Check for valid hwObject handle (Rx-Fifo Layout) */
    vuint8 numOfHandles = NUMBER_OF_FULL_CONFIGURABLE_FILTERS(canHwChannel);
    if (numOfHandles > 0u) /* COV_CAN_MUMOFHANDLES_CORRECTON */
    {
      numOfHandles--;
    }
    if ( (CanLL_CheckMaxHwMailboxHandle(canHwChannel, numOfHandles) == kCanOk) && (NUMBER_OF_FILTERS(canHwChannel) <= (sizeof(pRxFIFO->rxIDTAB) / sizeof(vuint32))) ) /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL04 */
#  endif
    {
      retVal = kCanOk;
      /* #70 Configure Rx-Fifo */
      for(filterHandle = 0u; filterHandle < NUMBER_OF_FILTERS(canHwChannel); filterHandle++)
      {
        if (filterHandle < NUMBER_OF_FULL_CONFIGURABLE_FILTERS(canHwChannel)) /* PRQA S 2991, 2995 */ /* MD_Can_ConstValue */ /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
        {
          /* #80 Initialize individual masks for Rx Fifo */
          locMsgIDMask = Can_GetInitMaskOfInitBasicCan(Can_GetInitBasicCanIndex(initPara->initObject) + filterHandle) & (vuint32)0x1FFFFFFFu; /* PRQA S 2985 */ /* MD_Can_ConstValue */
          retVal &= ~CanLL_InitMailboxWriteReg32( CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &pIndivRxMask->indivRxMask[filterHandle], (vuint32)((locMsgIDMask << 1) | kRxFIFO_MASK), kCanMaskAll32, initPara ); /* SBSW_CAN_LL09 */ /* PRQA S 2985 */ /* MD_Can_ConstValue */
        }

        /* #90 Initialize Id table for Rx Fifo */
        locMsgIDMask = Can_GetInitCodeOfInitBasicCan(Can_GetInitBasicCanIndex(initPara->initObject) + filterHandle) & (vuint32)0x1FFFFFFFu; /* PRQA S 2985 */ /* MD_Can_ConstValue */

        /* #100 Consider CAN ID type */
        if((Can_GetInitCodeOfInitBasicCan(Can_GetInitBasicCanIndex(initPara->initObject) + filterHandle) & kExtIDBit) != 0u) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */ /* PRQA S 2991,2992,2995,2996 */ /* MD_Can_ConstValue */ /* COV_CAN_GENDATA_FAILURE */
        {
          retVal &= ~CanLL_InitMailboxWriteReg32( CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &pRxFIFO->rxIDTAB[filterHandle], (vuint32)((locMsgIDMask << 1) | kRxFIFO_EXT), kCanMaskAll32, initPara ); /* SBSW_CAN_LL09 */ /* PRQA S 2880,2985 */ /*  MD_MSR_Unreachable */ /* MD_Can_ConstValue */
        }
        else
        {
          retVal &= ~CanLL_InitMailboxWriteReg32( CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &pRxFIFO->rxIDTAB[filterHandle], (vuint32)(locMsgIDMask << 1), kCanMaskAll32, initPara ); /* SBSW_CAN_LL09 */ /* PRQA S 2985 */ /* MD_Can_ConstValue */
        }
      }
    }
  }
# endif /* C_ENABLE_CLASSIC_MAILBOX_LAYOUT */

# if !defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
  /* #110 Set global mask register for Rx Fifo to 'must match' (bits REM and EXT must always match) */
  retVal &= ~CanLL_InitMailboxWriteReg32( CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &pFlexCANLocal->rxfgmask, kRxFIFO_MASK | (vuint32)0x3FFFFFFEu, kCanMaskAll32, initPara ); /* SBSW_CAN_LL01 */ /* PRQA S 2985 */ /* MD_Can_ConstValue */
# endif

  return(retVal);
}
/* CODE CATEGORY 4 END */

# if ((defined( C_ENABLE_CAN_RAM_CHECK )))
/**********************************************************************************************************************
 *  CanLL_InitMailboxRxBasicCanDeactivate
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_InitMailboxRxBasicCanDeactivate
Relation_Context:
# CanHL_InitRxBasicCAN() #
Wakeup, OneChOpt, ChannelAmount, RxBasicCANSupport, RamCheck
Relation:
CanFdSupport, RxFullCANSupport
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
 *
 *
*/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_InitMailboxRxBasicCanDeactivate( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara ) /* COV_CAN_RAM_CHECK_NO_STIMULATION */ /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */
{
#  if defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
  CanObjectHandle hwObjCount;
  CanObjectHandle hwObjHandle;

  for (hwObjCount = 0u; hwObjCount < Can_GetMailboxSize(initPara->mailboxHandle); hwObjCount++)
  {
    /* #10 Deactivate Rx BasicCAN mailboxes */
    hwObjHandle = initPara->hwObjHandle + hwObjCount;
    GLOBAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control) = 0u; /* SBSW_CAN_LL02 */
  }
#  else
  {
    CanObjectHandle hwObjHandle;
    tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);
    /* #20 Deactivate RxFifo */
    CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_FEN); /* SBSW_CAN_LL01 */

    /* #30 Deactivate all mailboxes that are overlaid by RxFifo engine */
#    if defined ( C_ENABLE_RX_FULLCAN_OBJECTS )
    for(hwObjHandle = 0u; hwObjHandle < CAN_HL_HW_RX_FULL_STARTINDEX(canHwChannel); hwObjHandle++)
#    else
    for(hwObjHandle = 0u; hwObjHandle < CAN_HL_HW_TX_STARTINDEX(canHwChannel); hwObjHandle++)
#    endif
    {
      LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control) = 0u; /* deactivate receive mailbox */ /* SBSW_CAN_LL02 */
    }
  }
#  endif

#  if !defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
  CAN_DUMMY_STATEMENT(initPara); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#  endif
}
/* CODE CATEGORY 4 END */
# endif
#endif /* C_ENABLE_RX_BASICCAN_OBJECTS */


/**********************************************************************************************************************
 *  CanLL_InitEndSetRegisters
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_InitEndSetRegisters
Relation_Context:
# CanHL_InitEnd_InitMode() #
OneChOpt, ChannelAmount
Relation:
CanFdSupport,RxPolling,IndividualPolling
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
 *
 *
 *
*/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitEndSetRegisters( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara )
{
  vuint32 tmpCANimask1;
  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);

  if (Can_GetCanInterruptCounter(channel) == 0u)
  {
    /* #10 Configure CAN[IMASK1] register value, take RxFifo into account if used */
    tmpCANimask1 =  CAN_INT_MASK1(canHwChannel)
# if !defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
    & kCanRxFifoIntUnmask
# endif
    ;
# if !defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
#  if !defined( C_ENABLE_RX_BASICCAN_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING )
#   if defined( C_ENABLE_INDIVIDUAL_POLLING )
    if ((CAN_INT_MASK1(canHwChannel) & (vuint32)0x01u) == (vuint32)0x01u) /* PRQA S 2742 */ /* MD_Can_ConstValue */ /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
#   endif
    {
      tmpCANimask1 |= kRxFIFO_NEWMSG; /* PRQA S 2880 */ /*  MD_MSR_Unreachable */ /* enable Rx FIFO interrupt */
    }
#  endif
# endif
    CanLL_WriteReg32(CAN_CHANNEL_CANPARA_FIRST &pFlexCANLocal->imask1, tmpCANimask1, kCanMaskAll32, initPara); /* SBSW_CAN_LL01 */

# if defined ( C_ENABLE_MB32TO63 ) /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
#  if defined ( C_ENABLE_ASYM_MAILBOXES ) /* COV_CAN_FLEXCAN3_DERIVATIVE_ASYM_MAILBOXES */
    if (NUMBER_OF_MAX_MAILBOXES(canHwChannel) > 32u) /* PRQA S 2741,2742 */ /* MD_Can_ConstValue */ /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
#  endif
    {
      /* #20 Configure CAN[IMASK2] register value */
      CanLL_WriteReg32(CAN_CHANNEL_CANPARA_FIRST &pFlexCANLocal->imask2, CAN_INT_MASK2(canHwChannel), kCanMaskAll32, initPara); /* SBSW_CAN_LL01 */
    }
# endif  
# if defined ( C_ENABLE_MB64TO95 ) /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
#  if defined ( C_ENABLE_ASYM_MAILBOXES ) /* COV_CAN_FLEXCAN3_DERIVATIVE_ASYM_MAILBOXES */
    if (NUMBER_OF_MAX_MAILBOXES(canHwChannel) > 64u) /* PRQA S 2741,2742 */ /* MD_Can_ConstValue */ /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
#  endif
    {
      /* #30 Configure CAN[IMASK3] register value */
      CanLL_WriteReg32(CAN_CHANNEL_CANPARA_FIRST &pFlexCANLocal->imask3, CAN_INT_MASK3(canHwChannel), kCanMaskAll32, initPara); /* SBSW_CAN_LL01 */
    }
# endif
# if defined ( C_ENABLE_MB96TO127 ) /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
    /* #40 Configure CAN[IMASK4] register value */
    CanLL_WriteReg32(CAN_CHANNEL_CANPARA_FIRST &pFlexCANLocal->imask4, CAN_INT_MASK4(canHwChannel), kCanMaskAll32, initPara); /* SBSW_CAN_LL01 */
# endif
  }

  CAN_DUMMY_STATEMENT(initPara); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  return(kCanOk);
}
/* CODE CATEGORY 4 END */
/**********************************************************************************************************************
 *  CanLL_InitEnd
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_InitEnd
Relation_Context:
# CanHL_InitEnd_InitMode() #
OneChOpt, ChannelAmount
Relation:
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
*/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitEnd( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara )
{
  /* #10 Nothing to do */
  CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CAN_DUMMY_STATEMENT(initPara); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return(kCanOk);
}
/* CODE CATEGORY 4 END */

#if defined( C_ENABLE_CAN_RAM_CHECK )
/**********************************************************************************************************************
 *  CanLL_InitIsMailboxCorrupt
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_InitIsMailboxCorrupt
Relation_Context:
# CanHL_InitXXX() #
Wakeup, OneChOpt, ChannelAmount
Relation:
RamCheck
DevErrorDetect
CanFdSupport
RxBasicCANSupport
RxFullCANSupport
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
*/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_STATIC, vuint8, STATIC_CODE) CanLL_InitIsMailboxCorrupt( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara ) /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */
{
   /* ----- Local Variables ---------------------------------------------- */
  vuint8    result, idx, wordLength, i;

  CanObjectHandle hwObjHandle;
  CanObjectHandle hwObjCount;

# if defined( C_ENABLE_CAN_RAM_CHECK_EXTENDED )
#  if !defined( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
  vuint8 filterHandle;
#  endif
#  if defined (C_ENABLE_RX_BASICCAN_OBJECTS) || defined (C_ENABLE_RX_FULLCAN_OBJECTS)
  tCanRxMaskPtr pIndivRxMask = pCanRxMask(canHwChannel);
#  endif
# endif

# if defined ( C_ENABLE_CAN_FD_FULL )
# else
  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);
# endif

   /* ----- Implementation ----------------------------------------------- */
  result = kCanFalse;

# if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
  /* #10 Check for valid hwObject handle */
  if (CanLL_CheckMaxHwMailboxHandle(canHwChannel, (initPara->hwObjHandle + Can_GetMailboxSize(initPara->mailboxHandle)) - 1u) == kCanOk) /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL04 */
# endif
  {
    hwObjHandle = initPara->hwObjHandle;

    for (hwObjCount = 0u; hwObjCount < Can_GetMailboxSize(initPara->mailboxHandle); hwObjCount++)
    {
      /* #20 DLC and IDE register check */
      LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control) = (vuint16)0x0055u; /* SBSW_CAN_LL02 */
      if((LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control) & (vuint16)0x007Fu) != (vuint16)0x0055u) /* COV_CAN_HARDWARE_FAILURE */ /* SBSW_CAN_LL02 */
      {
        result = kCanTrue;
      }
      LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control) = (vuint16)0x002Au; /* SBSW_CAN_LL02 */
      if((LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control) & (vuint16)0x007Fu) != (vuint16)0x002Au) /* COV_CAN_HARDWARE_FAILURE */ /* SBSW_CAN_LL02 */
      {
        result = kCanTrue;
      }
      LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control) = (vuint16)0x0000u; /* SBSW_CAN_LL02 */
      if((LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control) & (vuint16)0x007Fu) != (vuint16)0x0000u) /* COV_CAN_HARDWARE_FAILURE */ /* SBSW_CAN_LL02 */
      {
        result = kCanTrue; /* PRQA S 2981,2982 */ /* MD_MSR_RetVal */
      }

     /* #30 Iterate test patterns */
      for(i = 0u; i < 3u; i++)
      {
        /* #40 ID register check */
        LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, msgID) = ramCheckPattern32[i]; /* SBSW_CAN_LL02 */
        if((LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, msgID) != ramCheckPattern32[i])) /* COV_CAN_HARDWARE_FAILURE */ /* SBSW_CAN_LL02 */
        {
          result = kCanTrue; /* PRQA S 2981,2982 */ /* MD_MSR_RetVal */
        }
        /* #50 Data register check */
# if defined ( C_ENABLE_CAN_FD_FULL )
        wordLength = CANFD_MAILBOX_MAX_WORD_LENGTH(canHwChannel);
# else
        wordLength = 2u; /* check 8 data bytes */
# endif
        for (idx = 0; idx < wordLength; idx++)
        {
          LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, data[idx]) = ramCheckPattern32[i]; /* SBSW_CAN_LL02 */
          if(LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, data[idx]) != ramCheckPattern32[i]) /* COV_CAN_HARDWARE_FAILURE */ /* SBSW_CAN_LL02 */
          {
            result = kCanTrue; /* PRQA S 2981,2982 */ /* MD_MSR_RetVal */
          }
        }
      }
      hwObjHandle++;
    }

# if defined( C_ENABLE_CAN_RAM_CHECK_EXTENDED )
    if (result == kCanFalse) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
    {
      /* #60 Check RxFifo */
#  if !defined( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
      if (initPara->hwObjHandle == 0u)
      {
        for(filterHandle = 0u; filterHandle < NUMBER_OF_FILTERS(canHwChannel); filterHandle++)
        {
          if (filterHandle < NUMBER_OF_FULL_CONFIGURABLE_FILTERS(canHwChannel)) /* PRQA S 2991, 2995 */ /* MD_Can_ConstValue */ /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
          {
            for(i = 0u; i < 3u; i++)
            {
              pIndivRxMask->indivRxMask[filterHandle] = ramCheckPattern32[i];  /* SBSW_CAN_LL09 */
              if(pIndivRxMask->indivRxMask[filterHandle] != ramCheckPattern32[i]) /* COV_CAN_HARDWARE_FAILURE */
              {
                result = kCanTrue; /* PRQA S 2981,2982 */ /* MD_MSR_RetVal */
              }
            }
          }
        }
      }
#  else /* C_ENABLE_CLASSIC_MAILBOX_LAYOUT */
#   if defined( C_ENABLE_RX_BASICCAN_OBJECTS )
      /* #70 Check RX BasicCAN objects */
      hwObjHandle = initPara->hwObjHandle;
      if ( (initPara->mailboxHandle >= CAN_HL_MB_RX_BASIC_STARTINDEX(canHwChannel)) && (initPara->mailboxHandle < CAN_HL_MB_RX_BASIC_STOPINDEX(canHwChannel)) ) /* COV_CAN_HARDWARE_FAILURE */
      {
        for (hwObjCount = 0u; hwObjCount < Can_GetMailboxSize(initPara->mailboxHandle); hwObjCount++)
        {
          for(i = 0u; i < 3u; i++)
          {
            pIndivRxMask->indivRxMask[hwObjHandle] = ramCheckPattern32[i]; /* SBSW_CAN_LL09 */
            if(pIndivRxMask->indivRxMask[hwObjHandle] != ramCheckPattern32[i]) /* COV_CAN_HARDWARE_FAILURE */
            {
              result = kCanTrue; /* PRQA S 2981,2982 */ /* MD_MSR_RetVal */
            }
          }
          hwObjHandle++;
        }
      }
#   endif /* C_ENABLE_RX_BASICCAN_OBJECTS */
#  endif /* C_ENABLE_CLASSIC_MAILBOX_LAYOUT */
#  if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
      /* #80 Check RX FullCAN objects */
      if ( (initPara->mailboxHandle >= CAN_HL_MB_RX_FULL_STARTINDEX(canHwChannel)) && (initPara->mailboxHandle < CAN_HL_MB_RX_FULL_STOPINDEX(canHwChannel)) ) /* COV_CAN_MAILBOX_ORDER */
      {
        for(i = 0u; i < 3u; i++)
        {
          pIndivRxMask->indivRxMask[initPara->hwObjHandle] = ramCheckPattern32[i]; /* SBSW_CAN_LL09 */
          if(pIndivRxMask->indivRxMask[initPara->hwObjHandle] != ramCheckPattern32[i]) /* COV_CAN_HARDWARE_FAILURE */
          {
            result = kCanTrue; /* PRQA S 2981,2982 */ /* MD_MSR_RetVal */
          }
        }
      }
#  endif /* C_ENABLE_RX_FULLCAN_OBJECTS */
    }
# endif
  }

  return result;
} /* PRQA S 6010,6030,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STMIF */
/* CODE CATEGORY 4 END */
#endif /* C_ENABLE_CAN_RAM_CHECK */


/**********************************************************************************************************************
 *  CanLL_InitPowerOn
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_InitPowerOn
Relation_Context:
# from Can_Init #
Relation:
DevErrorDetect,CanFdSupport
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
 *
*/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitPowerOn(void)
{
  vuint8 retVal = kCanOk; /* PRQA S 2981,2982 */ /* MD_MSR_RetVal */
#if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
  CanChannelHandle chan;

  /* #10 SafeBSW check for maximum number of loops */
  if (kCanLoopResetInit >= (vuint8)CAN_LOOP_MAX)/* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL02 */ /* PRQA S 2742 */ /* MD_Can_ConstValue */
  {
    retVal = kCanFalse; /* PRQA S 2880 */ /*  MD_MSR_Unreachable */
  }

  for (chan = 0u; chan < kCanNumberOfChannels; chan++)
  {
# if defined ( C_ENABLE_CAN_FD_FULL )
    if ( CANFD_MAILBOX_MAX_WORD_LENGTH(chan) > 16u ) /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL10 */
    {
      retVal = kCanFalse;
    }
    if ( sizeof( Can_GetRxMsgBufferOfControllerData(chan).data ) < 64u ) /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL01 */ /* PRQA S 2742 */ /* MD_Can_ConstValue */
    {
      retVal = kCanFalse; /* PRQA S 2880 */ /*  MD_MSR_Unreachable */
    }
# else
    if ( sizeof( Can_GetRxMsgBufferOfControllerData(chan).data ) < 8u ) /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL01 */ /* PRQA S 2742 */ /* MD_Can_ConstValue */
    {
      retVal = kCanFalse; /* PRQA S 2880 */ /*  MD_MSR_Unreachable */
    }
# endif
  }
#endif

  return (retVal);
}
/* CODE CATEGORY 4 END */

/**********************************************************************************************************************
 *  CanLL_InitPowerOnChannelSpecific
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_InitPowerOnChannelSpecific
Relation_Context:
# from Can_Init #
Relation:
ChannelAmount, OneChOpt
VirtualAdressing
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
 *
 *
*/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitPowerOnChannelSpecific(CAN_CHANNEL_CANTYPE_ONLY)
{
#if defined( C_ENABLE_UPDATE_BASE_ADDRESS )
  /* #20 Get virtual base address of FlexCAN controller */
# if defined (C_MULTIPLE_RECEIVE_CHANNEL)
  canLL_VirtualPtrField[channel] = (vuint32 *)(ApplCanPowerOnGetBaseAddress((vuint32)(Can_GetBaseAddressOfControllerConfig(channel)), (vuint16)((vuint16)0xC00u + (vuint16)sizeof(tCanFDRegister)))); /* SBSW_CAN_LL06 */ /* PRQA S 0316 */ /* MD_Can_PointerVoidCast */
# else
  canLL_VirtualPtrField[0] = (vuint32 *)(ApplCanPowerOnGetBaseAddress((vuint32)(Can_GetBaseAddressOfControllerConfig(0)), (vuint16)((vuint16)0xC00u + (vuint16)sizeof(tCanFDRegister)))); /* SBSW_CAN_LL06 */ /* PRQA S 0316 */ /* MD_Can_PointerVoidCast */
# endif
#endif /* QWRAP / MDWRAP */


#if ( CAN_REINIT_START == STD_ON )
  canLL_canStartReinitState[channel] = kCanLLStateStart; /* SBSW_CAN_LL14 */
#endif

# if defined (C_ENABLE_HW_LOOP_TIMER)
  /* #30 initialize init control flag */
  canLL_FlexCANInitResultNeeded[channel] = kCanTrue; /* SBSW_CAN_LL14 */
# endif

  CAN_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  return (kCanOk);
}
/* CODE CATEGORY 4 END */

/**********************************************************************************************************************
 *  CanLL_InitMemoryPowerOn
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_InitMemoryPowerOn
Relation_Context:
Relation:
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
*/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_InitMemoryPowerOn(void)
{
  /* #10 CanLL_InitMemoryPowerOn: nothing to do here */
}
/* CODE CATEGORY 4 END */


#if defined( C_ENABLE_CANCEL_IN_HW )
/**********************************************************************************************************************
 *  CanLL_TxCancelInHw
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_TxCancelInHw
Relation_Context:
# from Can_CancelTx #
TransmitCancellationAPI, TxFullCANSupport, HwCancelTx
# from CanHL_WritePrepareCancelTx #
Relation:
MultiplexedTx
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
*/
/* CODE CATEGORY 3 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_TxCancelInHw(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxCancellationParaStructPtr txCancellationPara) /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */
{
  /* #10 calculate mailbox to abort and issue ABORT to it */
#  if defined(C_ENABLE_MULTIPLEXED_TRANSMISSION)
  txCancellationPara->hwObjHandle += txCancellationPara->mailboxElement; /* SBSW_CAN_LL04 */
#  endif
  GLOBAL_MAILBOX_ACCESS(canHwChannel, txCancellationPara->hwObjHandle, control) = kTxCodeAbort; /* SBSW_CAN_LL02 */
}
/* CODE CATEGORY 3 END */
#endif



/**********************************************************************************************************************
 *  CanLL_TxBegin
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_TxBegin
Relation_Context:
# from Can_Write #
Relation:
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
*/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_TxBegin(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxTransmissionParaStructPtr txPara)
{
  /* #10 CanLL_TxBegin: nothing to do here */
  CAN_DUMMY_STATEMENT(txPara); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}
/* CODE CATEGORY 1 END */

/**********************************************************************************************************************
 *  CanLL_TxSetMailbox
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_TxSetMailbox
Relation_Context:
# from Can_Write #
Relation:
CanFdSupport
MultiplexedTx
IDType
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
 *
 *
*/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_TxSetMailbox(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxTransmissionParaStructPtr txPara) /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */
{
# if !defined ( C_ENABLE_CAN_FD_FULL )
  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);
# endif
  vuint16 tmpControlVal;
  CanObjectHandle hwObjHandle;

  /* #10 Determine mailbox to be transmitted */
# if defined(C_ENABLE_MULTIPLEXED_TRANSMISSION)
  hwObjHandle = txPara->hwObjHandle + txPara->mailboxElement;
# else
  hwObjHandle = txPara->hwObjHandle;
# endif
  /* #20 Configure message ID */
# if defined( C_ENABLE_EXTENDED_ID )
  LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, msgID) = (vuint32)(txPara->idRaw0); /* SBSW_CAN_LL02 */
# else
  LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, msgID) = (vuint32)(txPara->idRaw0) << 16; /* SBSW_CAN_LL02 */
# endif
  /* #30 Configure control word */
  tmpControlVal = (vuint16)(((vuint16)txPara->dlcRaw & kTxDlcMask) | kTxCodeFree); /* write IDE,SRR and DLC */

# if defined( C_ENABLE_MIXED_ID ) 
  if (txPara->idType == kCanIdTypeExt) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  {
    tmpControlVal |= (vuint16)(kCanIdTypeExt | kCanIdTypeSRR);
  }
# endif

# if defined(C_ENABLE_CAN_FD_USED)
  tmpControlVal |= (vuint16)(txPara->fdType | txPara->fdBrsType);
# endif
  
  LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control) = tmpControlVal; /* SBSW_CAN_LL02 */
}
/* CODE CATEGORY 1 END */


/**********************************************************************************************************************
 *  CanLL_TxCopyToCan
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_TxCopyToCan
Relation_Context:
# from Can_Write #
Relation:
CanFdSupport,DevErrorDetect
MultiplexedTx
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
*/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_TxCopyToCan(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxTransmissionParaStructPtr txPara) /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */
{
#  if defined ( C_ENABLE_CAN_FD_FULL )
  vuint32     canFDTxBuf[16];
  vuint8 idx, idxByte, idxWord, dataWordLen, sduWordLen, sduResLen;
  vuint32 paddingWordValue;
#  else
  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);
  vuint32     canTxBuf[2];
#  endif
  CanObjectHandle hwObjHandle;

  /* #10 Determine mailbox to be used */
#  if defined(C_ENABLE_MULTIPLEXED_TRANSMISSION)
  hwObjHandle = txPara->hwObjHandle + txPara->mailboxElement;
#  else
  hwObjHandle = txPara->hwObjHandle;
#  endif
#  if defined(C_ENABLE_CAN_FD_FULL)
  /* #20 Preparation for FD data copying */
#   if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
  if ((txPara->messageLen <= 64u) && (txPara->frameLen <= 64u)) /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL11 */
#   endif
  {
    sduWordLen = txPara->messageLen >> 2;
    sduResLen = txPara->messageLen & 0x03u;
    CanCopyFDPadding2Uint32(paddingWordValue, txPara->paddingVal);

    /* #30 Copy FD data into tx message object */
    idxByte = 0u;
    /* #40 Copy four bytes into one word */
    for (idxWord = 0u; idxWord < sduWordLen; idxWord++)
    {
      CanCopyFDDataBytes2Uint32(canFDTxBuf[idxWord], &(txPara->CanMemCopySrcPtr[idxByte])); /* SBSW_CAN_LL11 */
      idxByte += 4u;
    }
    /* #50 Data bytes do not fit into a whole word, mix data bytes and padding value */
    if (sduResLen != 0u)
    {
      canFDTxBuf[idxWord] = 0u; /* SBSW_CAN_LL11 */
      for (idx = idxByte; idx < txPara->messageLen; idx++)
      {
        CanAdd1FDByte2Uint32(canFDTxBuf[idxWord], txPara->CanMemCopySrcPtr[idx]); /* SBSW_CAN_LL11 */ /* SBSW_CAN_LL11 */
      }
      for (idx = txPara->messageLen; idx < (txPara->messageLen + (4u - sduResLen)); idx++)
      {
        CanAdd1FDByte2Uint32(canFDTxBuf[idxWord], txPara->paddingVal); /* SBSW_CAN_LL11 */ /* SBSW_CAN_LL11 */
      }
      idxWord++;
    }
    /* #60 Add padding */
    dataWordLen = (txPara->frameLen + 3u) >> 2;
    for (idx = idxWord; idx < dataWordLen; idx++) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    {
      canFDTxBuf[idx] = paddingWordValue; /* SBSW_CAN_LL11 */
    }
    /* #70 Copy prepared FD message to mailbox */
    for (idx = 0u; idx < dataWordLen; idx++)
    {
      LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, data[idx]) = canFDTxBuf[idx]; /* SBSW_CAN_LL02 */
    }
  }
#  else
  /* #80 Prepare and copy non-FD data into tx message object */
  CanCopyDataBytes2Uint32(canTxBuf, txPara->CanMemCopySrcPtr); /* SBSW_CAN_LL13 */  /* SBSW_CAN_LL13 */
  LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, data[0]) = canTxBuf[0]; /* SBSW_CAN_LL02 */
  LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, data[1]) = canTxBuf[1]; /* SBSW_CAN_LL02 */
#  endif
}
/* CODE CATEGORY 1 END */

/**********************************************************************************************************************
 *  CanLL_TxStart
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_TxStart
Relation_Context:
# from Can_Write #
Relation:
MultiplexedTx
CanFdSupport, IDType
WorkaroundERR00582
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
 *
 *
*/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_TxStart(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxTransmissionParaStructPtr txPara) /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */
{
# if !defined ( C_ENABLE_CAN_FD_FULL )
  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);
# endif
  CanObjectHandle hwObjHandle;

  /* #10 Determine mailbox to be used */
# if defined(C_ENABLE_MULTIPLEXED_TRANSMISSION)
  hwObjHandle = txPara->hwObjHandle + txPara->mailboxElement;
# else
  hwObjHandle = txPara->hwObjHandle;
# endif

  {
    /* #20 Request transmission */
    LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control) |= kTxCodeTransmit; /* start tx of the message */ /* SBSW_CAN_LL02 */
# if defined (C_ENABLE_WORKAROUND_ERR005829)
    /* #30 Workaround ERR005829: set the reserved mailbox twice to CodeInactive. This workaround is recommended by Freescale */
    LOCAL_MAILBOX_ACCESS(canHwChannel, INDEX_RSVD_MB(canHwChannel), control) |= kTxCodeInactive; /* SBSW_CAN_LL02 */
    LOCAL_MAILBOX_ACCESS(canHwChannel, INDEX_RSVD_MB(canHwChannel), control) |= kTxCodeInactive; /* SBSW_CAN_LL02 */
# endif
  }
  
  return(kCanOk);
}
/* CODE CATEGORY 1 END */

/**********************************************************************************************************************
 *  CanLL_TxEnd
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_TxEnd
Relation_Context:
# from Can_Write #
Relation:
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
*/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_TxEnd(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxTransmissionParaStructPtr txPara)
{
  /* #10 CanLL_TxEnd: nothing to do here */
  CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CAN_DUMMY_STATEMENT(txPara); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}
/* CODE CATEGORY 1 END */

#if defined( C_ENABLE_TX_POLLING )
/**********************************************************************************************************************
 *  CanLL_TxIsGlobalConfPending
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_TxIsGlobalConfPending
Relation_Context:
# from Can_MainFunction_Write #
TxPolling, TxFullCANSupport
Relation:
ChannelAmount
OneChOpt
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
 *
 *
 *
 *
*/
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_TxIsGlobalConfPending(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY)
{
  vuint32 iFlags;
  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);
  vuint8 retVal = kCanFalse; /* PRQA S 2981,2982 */ /* MD_MSR_RetVal */

  /* #10 Retrieve IFLAG1 */
  iFlags = pFlexCANLocal->iflag1 & CAN_TX_POLL_MASK1(canHwChannel);
# if defined ( C_ENABLE_MB32TO63 ) /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
#  if defined ( C_ENABLE_ASYM_MAILBOXES ) /* COV_CAN_FLEXCAN3_DERIVATIVE_ASYM_MAILBOXES */
  if (NUMBER_OF_MAX_MAILBOXES(canHwChannel) > 32u) /* PRQA S 2741,2742 */ /* MD_Can_ConstValue */ /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
#  endif
  {
    /* #20 Retrieve IFLAG2 */
    iFlags |= pFlexCANLocal->iflag2 & CAN_TX_POLL_MASK2(canHwChannel);
  }
# endif
# if defined ( C_ENABLE_MB64TO95 ) /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
#  if defined ( C_ENABLE_ASYM_MAILBOXES ) /* COV_CAN_FLEXCAN3_DERIVATIVE_ASYM_MAILBOXES */
  if (NUMBER_OF_MAX_MAILBOXES(canHwChannel) > 64u) /* PRQA S 2741,2742 */ /* MD_Can_ConstValue */ /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
#  endif
  {
    /* #30 Retrieve IFLAG3 */
    iFlags |= pFlexCANLocal->iflag3 & CAN_TX_POLL_MASK3(canHwChannel);
  }
# endif
# if defined ( C_ENABLE_MB96TO127 ) /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
  /* #40 Retrieve IFLAG4 */
  iFlags |= pFlexCANLocal->iflag4 & CAN_TX_POLL_MASK4(canHwChannel);
# endif

  /* #50 Check for pending confirmation */
  if (iFlags != 0u)
  {
    retVal = kCanTrue;
  }
  
  return retVal;
}
/* CODE CATEGORY 2 END */

/**********************************************************************************************************************
 *  CanLL_TxProcessPendings
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_TxProcessPendings
Relation_Context:
# from Can_MainFunction_Write #
TxPolling, TxFullCANSupport
Relation:
MultiplexedTx
TxBasicAmount
TxFullAmount
ChannelAmount
OneChOpt
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
 *
 *
*/
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_TxProcessPendings(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTaskParaStructPtr taskPara) /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */
{
  vuint32 iFlags;
  CanObjectHandle mailboxElement = 0u;
  CanObjectHandle hwObjHandle = taskPara->hwObjHandle;
  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);
  
# if defined(C_ENABLE_MULTIPLEXED_TRANSMISSION)
  for (; mailboxElement < Can_GetMailboxSize(taskPara->mailboxHandle); mailboxElement++)
# endif
  {
  /* #10 Get iflag corresponding to hwObjHandle */
    iFlags = CanLL_GetInterruptFlag(pFlexCANLocal, hwObjHandle); /* SBSW_CAN_LL01 */

    /* #20 Check for confirmation condition */
    if( ((iFlags & CanBitMask(hwObjHandle)) != 0u)) /* PRQA S 2985 */ /* MD_Can_ConstValue */ /* COV_CAN_FULLCAN_LL_TX_POLLING */
    {
      /* #30 Perform TX confirmation */
      CanHL_TxConfirmationPolling(CAN_HW_CHANNEL_CANPARA_FIRST  taskPara->mailboxHandle, mailboxElement, hwObjHandle);
    }
    hwObjHandle++; /* PRQA S 2983 */ /* MD_MSR_DummyStmt */
  }
}
/* CODE CATEGORY 2 END */
#endif /* C_ENABLE_TX_POLLING */

/**********************************************************************************************************************
 *  CanLL_TxConfBegin
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_TxConfBegin
Relation_Context:
# from CanHL_TxConfirmation #
Relation:
TxBasicAmount
TxFullAmount
ChannelAmount
OneChOpt
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
*/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_TxConfBegin(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxConfirmationParaStructPtr txConfPara) /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */
{
  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);

  /* #10 Clear pending interrupt flag */
  CanLL_ClearPendingInterrupt(pFlexCANLocal, txConfPara->hwObjHandle); /* SBSW_CAN_LL01 */
}
/* CODE CATEGORY 1 END */

#if defined( C_ENABLE_CANCEL_IN_HW )
/**********************************************************************************************************************
 *  CanLL_TxConfIsMsgTransmitted
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_TxConfIsMsgTransmitted
Relation_Context:
# from CanHL_TxConfirmation #
HwCancelTx
Relation:
TxBasicAmount
TxFullAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
 *
*/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_TxConfIsMsgTransmitted(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxConfirmationParaStructPtr txConfPara) /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */
{
  vuint8 isMsgTransmitted = kCanTrue;

  /* #10 Check for transmitted message */
  if (!CanLL_TxIsObjFree(canHwChannel, txConfPara->hwObjHandle))
  {
    /* #20 Set mailbox to free if message was cancelled */
    GLOBAL_MAILBOX_ACCESS(canHwChannel, txConfPara->hwObjHandle, control) = kTxCodeFree; /* SBSW_CAN_LL02 */
    isMsgTransmitted = kCanFalse;
  }

  return isMsgTransmitted;
}
/* CODE CATEGORY 1 END */
#endif

#if defined(CAN_ENABLE_GENERIC_CONFIRMATION_API2)
/**********************************************************************************************************************
 *  CanLL_TxConfSetTxConfStruct
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_TxConfSetTxConfStruct
Relation_Context:
# from CanHL_TxConfirmation #
GenericConfirmation
Relation:
TxBasicAmount
TxFullAmount
CanFdSupport
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
*/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_TxConfSetTxConfStruct(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxConfirmationParaStructPtr txConfPara)
{
  /* # 10 Get Confirmation information from mailbox */
#  if defined( C_CPUTYPE_LITTLEENDIAN ) /* COV_CAN_FLEXCAN3_DERIVATIVE_LITTLE_ENDIAN */
  {
    vuint32 tmpData; /* avoid IAR compiler warning */
#   if defined ( C_ENABLE_CAN_FD_FULL )
    vuint8 idx;

    for (idx = 0u; idx < CANFD_MAILBOX_MAX_WORD_LENGTH(canHwChannel); idx++)
    {
      tmpData = GLOBAL_MAILBOX_ACCESS(canHwChannel, txConfPara->hwObjHandle, data[idx]); /* SBSW_CAN_LL02 */
      txConfPara->canDataBuffer[idx] = CanBswap32(tmpData); /* SBSW_CAN_LL12 */
    }
    txConfPara->txStructConf->pChipData = (CanChipDataPtr)&(txConfPara->canDataBuffer[0]); /* SBSW_CAN_LL04 */
#   else
    tmpData = GLOBAL_MAILBOX_ACCESS(canHwChannel, txConfPara->hwObjHandle, data[0]); /* SBSW_CAN_LL02 */
    txConfPara->canDataBuffer[0] = CanBswap32(tmpData); /* SBSW_CAN_LL13 */
    tmpData = GLOBAL_MAILBOX_ACCESS(canHwChannel, txConfPara->hwObjHandle, data[1]); /* SBSW_CAN_LL02 */
    txConfPara->canDataBuffer[1] = CanBswap32(tmpData); /* SBSW_CAN_LL13 */
    txConfPara->txStructConf->pChipData = (CanChipDataPtr)&(txConfPara->canDataBuffer[0]); /* SBSW_CAN_LL04 */
#   endif
    txConfPara->txStructConf->pChipMsgObj = (CanChipMsgPtr)&(GLOBAL_MAILBOX_ACCESS(canHwChannel, txConfPara->hwObjHandle, timestamp)); /* SBSW_CAN_LL04 */
  }
#  endif
}
/* CODE CATEGORY 1 END */
#endif

/**********************************************************************************************************************
 *  CanLL_TxConfEnd
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_TxConfEnd
Relation_Context:
# from CanHL_TxConfirmation #
Relation:
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
*/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_TxConfEnd(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxConfirmationParaStructPtr txConfPara)
{
  /* #10 CanLL_TxConfEnd: nothing to do here */
  CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CAN_DUMMY_STATEMENT(txConfPara); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}
/* CODE CATEGORY 1 END */



#if defined( C_ENABLE_RX_BASICCAN_OBJECTS )
/**********************************************************************************************************************
 *  CanLL_RxBasicMsgReceivedBegin
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_RxBasicMsgReceivedBegin
Relation_Context:
# from CanHL_BasicCanMsgReceived #
RxBasicCANSupport
Relation:
HardwareLoopCheck
CanFdSupport
Overrun
OneChOpt
ChannelAmount
RxFullAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_RxBasicMsgReceivedBegin(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanRxBasicParaStructPtr rxBasicPara)
{
  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);
  vuint8 retVal = kCanTrue; /* PRQA S 2981,2982 */ /* MD_MSR_RetVal */
# if defined ( C_ENABLE_CAN_FD_FULL )
  vuint8 idx;
# endif
# if defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
#  if defined( C_ENABLE_PROTECTED_RX_PROCESS )
  CanDeclareGlobalInterruptOldStatus
#  endif
  Can_ReturnType loopResult = CAN_OK; /* PRQA S 2981,2982 */ /* MD_MSR_RetVal */
# endif

# if defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
#  if defined( C_ENABLE_PROTECTED_RX_PROCESS )
  CanNestedGlobalInterruptDisable();
#  endif
  /* #10 Request access to BasicCAN mailbox and copy control word */
  Can_GetRxMsgBufferOfControllerData(canHwChannel).control = LOCAL_MAILBOX_ACCESS(canHwChannel, rxBasicPara->hwObjHandle, control); /* SBSW_CAN_LL06 */
  if ((Can_GetRxMsgBufferOfControllerData(canHwChannel).control & kRxCodeBusy) == kRxCodeBusy) /* COV_CAN_HARDWARE_PROCESSING_TIME */
  {
    CanLL_ApplCanTimerStart(kCanLoopMsgReception); /* start hw loop timer */ /* SBSW_CAN_LL08 */
    do
    { /* Check busy state of receive object */
      Can_GetRxMsgBufferOfControllerData(canHwChannel).control = LOCAL_MAILBOX_ACCESS(canHwChannel, rxBasicPara->hwObjHandle, control); /* SBSW_CAN_LL06 */
      loopResult = CanLL_ApplCanTimerLoop(kCanLoopMsgReception);
    } while(((Can_GetRxMsgBufferOfControllerData(canHwChannel).control & kRxCodeBusy) == kRxCodeBusy) && (loopResult == CAN_OK)); /* COV_CAN_TIMEOUT_DURATION */ /* PRQA S 2995 */ /* MD_Can_ConstValue */
    CanLL_ApplCanTimerEnd(kCanLoopMsgReception); /* stop hw loop timer */ /* SBSW_CAN_LL08 */
  }
# else /* C_ENABLE_CLASSIC_MAILBOX_LAYOUT */
  /* #20 Copy control word from RxFifo */
  Can_GetRxMsgBufferOfControllerData(canHwChannel).control = LOCAL_MAILBOX_ACCESS(canHwChannel, rxBasicPara->hwObjHandle, control); /* SBSW_CAN_LL06 */
# endif /* C_ENABLE_CLASSIC_MAILBOX_LAYOUT */
      
  /* #30 Copy id to RAM buffer */
  Can_GetRxMsgBufferOfControllerData(canHwChannel).msgID = LOCAL_MAILBOX_ACCESS(canHwChannel, rxBasicPara->hwObjHandle, msgID); /* SBSW_CAN_LL06 */
  /* #40 Copy data to RAM buffer */
# if defined( C_CPUTYPE_LITTLEENDIAN ) /* COV_CAN_FLEXCAN3_DERIVATIVE_LITTLE_ENDIAN */
  {
    vuint32 tmpData; /* avoid IAR compiler warning */
#  if defined ( C_ENABLE_CAN_FD_FULL )
    for (idx = 0u; idx < CANFD_MAILBOX_MAX_WORD_LENGTH(canHwChannel); idx++)
    {
      tmpData = LOCAL_MAILBOX_ACCESS(canHwChannel, rxBasicPara->hwObjHandle, data[idx]); /* SBSW_CAN_LL02 */
      Can_GetRxMsgBufferOfControllerData(canHwChannel).data[idx] = CanBswap32(tmpData); /* SBSW_CAN_LL06 */
    }
#  else
    tmpData = LOCAL_MAILBOX_ACCESS(canHwChannel, rxBasicPara->hwObjHandle, data[0]); /* SBSW_CAN_LL02 */
    Can_GetRxMsgBufferOfControllerData(canHwChannel).data[0] = CanBswap32(tmpData); /* SBSW_CAN_LL06 */
    tmpData = LOCAL_MAILBOX_ACCESS(canHwChannel, rxBasicPara->hwObjHandle, data[1]); /* SBSW_CAN_LL02 */
    Can_GetRxMsgBufferOfControllerData(canHwChannel).data[1] = CanBswap32(tmpData); /* SBSW_CAN_LL06 */
#  endif
  }
# endif

# if defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
  /* #50 Clear pending interrupt flag for BaisCAN */
  CanLL_ClearPendingInterrupt(pFlexCANLocal, rxBasicPara->hwObjHandle); /* SBSW_CAN_LL01 */

  /* #60 Unlock BasicCAN mailbox */
  Can_GetRxMsgBufferOfControllerData(canHwChannel).timestamp = (vuint16)pFlexCANLocal->timer; /* unlock current receive buffer */ /* SBSW_CAN_LL01 */

#  if defined( C_ENABLE_PROTECTED_RX_PROCESS )
  CanNestedGlobalInterruptRestore();
#  endif

#  if defined( C_ENABLE_HW_LOOP_TIMER )
  if (loopResult != CAN_OK) /* COV_CAN_TIMEOUT_DURATION */
  {    
    retVal = kCanFailed;
  }
#  endif
# else /* C_ENABLE_CLASSIC_MAILBOX_LAYOUT */
  /* #70 Clear RxFIFO pending interrupt flag after message is stored */
  pFlexCANLocal->iflag1 = (vuint32)kRxFIFO_NEWMSG; /* SBSW_CAN_LL01 */
# endif /* C_ENABLE_CLASSIC_MAILBOX_LAYOUT */

  /* #80 Save pointer of control word and data */
  rxBasicPara->rxStruct.pChipMsgObj = (CanChipMsgPtr) &(Can_GetRxMsgBufferOfControllerData(canHwChannel).control); /* SBSW_CAN_LL04 */
  rxBasicPara->rxStruct.pChipData = (CanChipDataPtr) &(Can_GetRxMsgBufferOfControllerData(canHwChannel).data[0]); /* SBSW_CAN_LL04 */

# if defined( C_ENABLE_OVERRUN )
  /* #90 Save overrun status */
#  if defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
  if((Can_GetRxMsgBufferOfControllerData(canHwChannel).control & kCodeMask) == kRxCodeOverrun)
  {
#  else
  if((pFlexCANLocal->iflag1 & kRxFIFO_OVERRUN) != 0u)
  {
    pFlexCANLocal->iflag1 = kRxFIFO_OVERRUN | kRxFIFO_WARN; /* clear warning and overflow flag */ /* SBSW_CAN_LL01 */
#  endif
    rxBasicPara->isOverrun = (vuint8)kCanTrue; /* SBSW_CAN_LL04 */
  }
  else
  {
    rxBasicPara->isOverrun = (vuint8)kCanFalse; /* SBSW_CAN_LL04 */
  }
# endif

  return (retVal);
}
/* CODE CATEGORY 1 END */

/**********************************************************************************************************************
 *  CanLL_RxBasicReleaseObj
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_RxBasicReleaseObj
Relation_Context:
# from CanHL_BasicCanMsgReceived #
RxBasicCANSupport
Relation:
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
*/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_RxBasicReleaseObj(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanRxBasicParaStructPtr rxBasicPara)
{
  /* #10 CanLL_RxBasicReleaseObj(): nothing to do here */
  CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CAN_DUMMY_STATEMENT(rxBasicPara); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}
/* CODE CATEGORY 1 END */

/**********************************************************************************************************************
 *  CanLL_RxBasicMsgReceivedEnd
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_RxBasicMsgReceivedEnd
Relation_Context:
# from CanHL_BasicCanMsgReceived #
RxBasicCANSupport
Relation:
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
*/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_RxBasicMsgReceivedEnd(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanRxBasicParaStructPtr rxBasicPara)
{
  /* #10 CanLL_RxBasicMsgReceivedEnd(): nothing to do here */
  CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CAN_DUMMY_STATEMENT(rxBasicPara); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}
/* CODE CATEGORY 1 END */

# if defined( C_ENABLE_RX_BASICCAN_POLLING )
/**********************************************************************************************************************
 *  CanLL_RxBasicIsGlobalIndPending
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_RxBasicIsGlobalIndPending
Relation_Context:
# from CanHL_RxBasicCanPolling #
RxBasicCANSupport, RxPolling
Relation:
CanFdSupport
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
*/
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_RxBasicIsGlobalIndPending(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY)
{
  vuint8 retVal = kCanFalse; /* PRQA S 2981,2982 */ /* MD_MSR_RetVal */
  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);
#  if defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
  vuint32 iFlags;
  
  /* #10 Retrieve IFLAG1 */
  iFlags = pFlexCANLocal->iflag1 & CAN_RXBASIC_POLL_MASK1(canHwChannel);
#   if defined ( C_ENABLE_MB32TO63 ) /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
  /* #20 Retrieve IFLAG2 */
#    if defined ( C_ENABLE_ASYM_MAILBOXES ) /* COV_CAN_FLEXCAN3_DERIVATIVE_ASYM_MAILBOXES */
  if (NUMBER_OF_MAX_MAILBOXES(canHwChannel) > 32u) /* PRQA S 2741,2742 */ /* MD_Can_ConstValue */ /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
#    endif
  {
    iFlags |= pFlexCANLocal->iflag2 & CAN_RXBASIC_POLL_MASK2(canHwChannel);
  }
#   endif
#   if defined ( C_ENABLE_MB64TO95 ) /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
  /* #30 Retrieve IFLAG3 */
#    if defined ( C_ENABLE_ASYM_MAILBOXES ) /* COV_CAN_FLEXCAN3_DERIVATIVE_ASYM_MAILBOXES */
  if (NUMBER_OF_MAX_MAILBOXES(canHwChannel) > 64u) /* PRQA S 2741,2742 */ /* MD_Can_ConstValue */ /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
#    endif
  {
    iFlags |= pFlexCANLocal->iflag3 & CAN_RXBASIC_POLL_MASK3(canHwChannel);
  }
#   endif
#   if defined ( C_ENABLE_MB96TO127 ) /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
  /* #40 Retrieve IFLAG4 */
  iFlags |= pFlexCANLocal->iflag4 & CAN_RXBASIC_POLL_MASK4(canHwChannel);
#   endif
  /* #50 Check for pending RX BesicCAN message */
  if (iFlags != 0u)
  {
#  else /* C_ENABLE_CLASSIC_MAILBOX_LAYOUT */
  /* #60 Check for pending RxFifo message */
  if ((pFlexCANLocal->iflag1 & kRxFIFO_NEWMSG) != 0u)
  {
#  endif /* C_ENABLE_CLASSIC_MAILBOX_LAYOUT */
    retVal = kCanTrue;
  }
  
  return retVal;
}
/* CODE CATEGORY 2 END */

/**********************************************************************************************************************
 *  CanLL_RxBasicProcessPendings
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_RxBasicProcessPendings
Relation_Context:
# from CanHL_RxBasicCanPolling #
RxBasicCANSupport, RxPolling
Relation:
CanFdSupport
IndividualPolling
OneChOpt
ChannelAmount
RxBasicAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
 *
 *
 *
*/
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_RxBasicProcessPendings(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTaskParaStructPtr taskPara) /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */
{

  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);
#  if defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
  vuint32 iFlags = 0u; /* PRQA S 2981,2982 */ /* MD_MSR_RetVal */
  CanObjectHandle hwObjCount;
  CanObjectHandle hwObjHandle;
#  else
  vuint8 fifoLoopCnt=0u;
#  endif

#  if defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
  /* #10 BasicCAN receive process */
  for (hwObjCount = 0u; hwObjCount < Can_GetMailboxSize(taskPara->mailboxHandle); hwObjCount++)
  {
    hwObjHandle = taskPara->hwObjHandle + hwObjCount;
    /* 20 Get corresponding iflag */
    iFlags = CanLL_GetInterruptFlag(pFlexCANLocal, hwObjHandle); /* SBSW_CAN_LL01 */
    /* #30 Check for received BasicCAN message */
    if((iFlags & CanBitMask(hwObjHandle)) != 0u) /* PRQA S 2985 */ /* MD_Can_ConstValue */
    {
      taskPara->hwObjHandle = hwObjHandle; /* SBSW_CAN_LL04 */
      CanHL_BasicCanMsgReceivedPolling(CAN_HW_CHANNEL_CANPARA_FIRST taskPara->mailboxHandle, hwObjHandle);
    }
  }
#  else /* C_ENABLE_CLASSIC_MAILBOX_LAYOUT */
  /* #40 Check for RxFifo message */
  while(((pFlexCANLocal->iflag1 & kRxFIFO_NEWMSG) != 0u) && (fifoLoopCnt < C_FLEXCAN_RXFIFO_MAXLOOP)) /* COV_CAN_RXFIFO_HANDLING */
  {
    fifoLoopCnt++;
    CanHL_BasicCanMsgReceivedPolling(CAN_HW_CHANNEL_CANPARA_FIRST taskPara->mailboxHandle, taskPara->hwObjHandle);
  }
#  endif /* C_ENABLE_CLASSIC_MAILBOX_LAYOUT */
}
/* CODE CATEGORY 2 END */
# endif /* C_ENABLE_RX_BASICCAN_POLLING */
#endif /* C_ENABLE_RX_BASICCAN_OBJECTS */

#if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
/**********************************************************************************************************************
*  CanLL_RxFullMsgReceivedBegin
*********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_RxFullMsgReceivedBegin
Relation_Context:
# from CanHL_FullCanMsgReceived #
RxFullCANSupport
Relation:
HardwareLoopCheck
CanFdSupport
Overrun
OneChOpt
ChannelAmount
RxFullAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_RxFullMsgReceivedBegin(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanRxFullParaStructPtr rxFullPara)
{
# if defined( C_ENABLE_PROTECTED_RX_PROCESS )
  CanDeclareGlobalInterruptOldStatus
# endif
# if defined ( C_ENABLE_CAN_FD_FULL )
  vuint8 idx;
# endif
  vuint8 retVal = kCanOk; /* PRQA S 2981,2982 */ /* MD_MSR_RetVal */
  Can_ReturnType loopResult = CAN_OK; /* PRQA S 2981,2982 */ /* MD_MSR_RetVal */
  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);

# if defined( C_ENABLE_PROTECTED_RX_PROCESS )
  CanNestedGlobalInterruptDisable();
# endif
  /* #10 Request access to FullCAN mailbox and copy control word */
  Can_GetRxMsgBufferOfControllerData(canHwChannel).control = LOCAL_MAILBOX_ACCESS(canHwChannel, rxFullPara->hwObjHandle, control); /* SBSW_CAN_LL06 */
  if ((Can_GetRxMsgBufferOfControllerData(canHwChannel).control & kRxCodeBusy) == kRxCodeBusy) /* COV_CAN_HARDWARE_PROCESSING_TIME */
  {
    CanLL_ApplCanTimerStart(kCanLoopMsgReception); /* start hw loop timer */ /* SBSW_CAN_LL08 */
    do
    { /* Check busy state of receive object */
      Can_GetRxMsgBufferOfControllerData(canHwChannel).control = LOCAL_MAILBOX_ACCESS(canHwChannel, rxFullPara->hwObjHandle, control); /* SBSW_CAN_LL06 */
      loopResult = CanLL_ApplCanTimerLoop(kCanLoopMsgReception);
    } while(((Can_GetRxMsgBufferOfControllerData(canHwChannel).control & kRxCodeBusy) == kRxCodeBusy) && (loopResult == CAN_OK)); /* COV_CAN_TIMEOUT_DURATION */ /* PRQA S 2995 */ /* MD_Can_ConstValue */
    CanLL_ApplCanTimerEnd(kCanLoopMsgReception); /* stop hw loop timer */ /* SBSW_CAN_LL08 */
  }

  /* #20 Copy id to RAM buffer */
  Can_GetRxMsgBufferOfControllerData(canHwChannel).msgID = LOCAL_MAILBOX_ACCESS(canHwChannel, rxFullPara->hwObjHandle, msgID); /* SBSW_CAN_LL06 */
  /* #30 Copy data to RAM buffer */
# if defined( C_CPUTYPE_LITTLEENDIAN ) /* COV_CAN_FLEXCAN3_DERIVATIVE_LITTLE_ENDIAN */
  {
    vuint32 tmpData; /* avoid IAR compiler warning */
#  if defined ( C_ENABLE_CAN_FD_FULL )
    for (idx = 0u; idx < CANFD_MAILBOX_MAX_WORD_LENGTH(canHwChannel); idx++)
    {
      tmpData = LOCAL_MAILBOX_ACCESS(canHwChannel, rxFullPara->hwObjHandle, data[idx]); /* SBSW_CAN_LL02 */
      Can_GetRxMsgBufferOfControllerData(canHwChannel).data[idx] = CanBswap32(tmpData); /* SBSW_CAN_LL06 */
    }
#  else
    tmpData = LOCAL_MAILBOX_ACCESS(canHwChannel, rxFullPara->hwObjHandle, data[0]); /* SBSW_CAN_LL02 */
    Can_GetRxMsgBufferOfControllerData(canHwChannel).data[0] = CanBswap32(tmpData); /* SBSW_CAN_LL06 */
    tmpData = LOCAL_MAILBOX_ACCESS(canHwChannel, rxFullPara->hwObjHandle, data[1]); /* SBSW_CAN_LL02 */
    Can_GetRxMsgBufferOfControllerData(canHwChannel).data[1] = CanBswap32(tmpData); /* SBSW_CAN_LL06 */
#  endif
  }
# endif

  /* #40 Clear pending interrupt flag for FullCAN */
  CanLL_ClearPendingInterrupt(pFlexCANLocal, rxFullPara->hwObjHandle); /* SBSW_CAN_LL01 */

  /* #50 Unlock FullCAN mailbox */
  Can_GetRxMsgBufferOfControllerData(canHwChannel).timestamp = (vuint16)pFlexCANLocal->timer; /* unlock current receive buffer */ /* SBSW_CAN_LL01 */

# if defined( C_ENABLE_PROTECTED_RX_PROCESS )
  CanNestedGlobalInterruptRestore();
# endif

# if defined( C_ENABLE_HW_LOOP_TIMER )
  if (loopResult != CAN_OK) /* COV_CAN_TIMEOUT_DURATION */
  {    
    retVal = kCanFailed;
  }
# endif

  /* #60 Save pointer of control word and data */
  rxFullPara->rxStruct.pChipMsgObj = (CanChipMsgPtr) &(Can_GetRxMsgBufferOfControllerData(canHwChannel).control); /* SBSW_CAN_LL04 */
  rxFullPara->rxStruct.pChipData = (CanChipDataPtr) &(Can_GetRxMsgBufferOfControllerData(canHwChannel).data[0]); /* SBSW_CAN_LL04 */

# if defined( C_ENABLE_FULLCAN_OVERRUN )
  /* #70 Save overrun status */
  if ((Can_GetRxMsgBufferOfControllerData(canHwChannel).control & kCodeMask) == kRxCodeOverrun) /* COV_CAN_FULL_OVERRUN_HANDLING */
  {
    rxFullPara->isOverrun = kCanTrue; /* SBSW_CAN_LL04 */
  }
  else
  {
    rxFullPara->isOverrun = kCanFalse; /* SBSW_CAN_LL04 */
  }
# endif

  return (retVal);
}
/* CODE CATEGORY 1 END */


/**********************************************************************************************************************
 *  CanLL_RxFullReleaseObj
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_RxFullReleaseObj
Relation_Context:
# from CanHL_FullCanMsgReceived #
RxFullCANSupport
Relation:
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
*/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_RxFullReleaseObj(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanRxFullParaStructPtr rxFullPara)
{
  /* #10 CanLL_RxFullReleaseObj(): nothing to do here */
  CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CAN_DUMMY_STATEMENT(rxFullPara); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}
/* CODE CATEGORY 1 END */

/**********************************************************************************************************************
 *  CanLL_RxFullMsgReceivedEnd
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_RxFullMsgReceivedEnd
Relation_Context:
# from CanHL_FullCanMsgReceived #
RxFullCANSupport
Relation:
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
*/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_RxFullMsgReceivedEnd(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanRxFullParaStructPtr rxFullPara)
{
  /* #10 CanLL_RxFullMsgReceivedEnd(): nothing to do here */
  CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CAN_DUMMY_STATEMENT(rxFullPara); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}
/* CODE CATEGORY 1 END */


# if defined( C_ENABLE_RX_FULLCAN_POLLING )
/**********************************************************************************************************************
 *  CanLL_RxFullIsGlobalIndPending
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_RxFullIsGlobalIndPending
Relation_Context:
# from CanHL_RxFullCanPolling #
RxFullCANSupport, RxPolling
Relation:
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
 *
 *
 *
 *
*/
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_RxFullIsGlobalIndPending(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY)
{
  vuint32 iFlags;
  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);
  vuint8 retVal = kCanFalse; /* PRQA S 2981,2982 */ /* MD_MSR_RetVal */

  /* #10 Retrieve IFLAG1 of Rx FullCAN */
  iFlags = pFlexCANLocal->iflag1 & CAN_RXFULL_POLL_MASK1(canHwChannel);
#if defined ( C_ENABLE_MB32TO63 ) /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
  /* #20 Retrieve IFLAG2 of Rx FullCAN */
# if defined ( C_ENABLE_ASYM_MAILBOXES ) /* COV_CAN_FLEXCAN3_DERIVATIVE_ASYM_MAILBOXES */
  if (NUMBER_OF_MAX_MAILBOXES(canHwChannel) > 32u) /* PRQA S 2741,2742 */ /* MD_Can_ConstValue */ /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
# endif
  {
    iFlags |= pFlexCANLocal->iflag2 & CAN_RXFULL_POLL_MASK2(canHwChannel);
  }
#endif
#if defined ( C_ENABLE_MB64TO95 ) /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
  /* #30 Retrieve IFLAG3 of Rx FullCAN */
# if defined ( C_ENABLE_ASYM_MAILBOXES ) /* COV_CAN_FLEXCAN3_DERIVATIVE_ASYM_MAILBOXES */
  if (NUMBER_OF_MAX_MAILBOXES(canHwChannel) > 64u) /* PRQA S 2741,2742 */ /* MD_Can_ConstValue */ /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
# endif
  {
    iFlags |= pFlexCANLocal->iflag3 & CAN_RXFULL_POLL_MASK3(canHwChannel);
  }
#endif
#if defined ( C_ENABLE_MB96TO127 ) /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
  /* #40 Retrieve IFLAG of Rx FullCAN */
  iFlags |= pFlexCANLocal->iflag4 & CAN_RXFULL_POLL_MASK4(canHwChannel);
#endif
  /* #50 Check for received FullCAN message */
  if (iFlags != 0u) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  {
    retVal = kCanTrue;
  }
  
  return retVal;
}
/* CODE CATEGORY 2 END */

/**********************************************************************************************************************
 *  CanLL_RxFullProcessPendings
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_RxFullProcessPendings
Relation_Context:
# from CanHL_RxFullCanPolling #
RxFullCANSupport, RxPolling
Relation:
OneChOpt
ChannelAmount
RxFullAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
 *
*/
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_RxFullProcessPendings(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTaskParaStructPtr taskPara) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */ /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */
{
  vuint32 iFlags;
  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);

  /* #10 Get iflag of corresponding hwObject */
  iFlags = CanLL_GetInterruptFlag(pFlexCANLocal, taskPara->hwObjHandle); /* SBSW_CAN_LL01 */
  /* #20 Check for received FullCAN message */
  if((iFlags & CanBitMask(taskPara->hwObjHandle)) != 0u) /* COV_CAN_FULLCAN_LL_RX_POLLING */ /* PRQA S 2985 */ /* MD_Can_ConstValue */
  {
    CanHL_FullCanMsgReceivedPolling(CAN_HW_CHANNEL_CANPARA_FIRST Can_GetHwToMbHandle(canHwChannel, taskPara->hwObjHandle), taskPara->hwObjHandle); /* PRQA S 2986 */ /* MD_Can_ConstValue */
  }
}
/* CODE CATEGORY 2 END */
# endif /* C_ENABLE_RX_FULLCAN_POLLING */
#endif /* C_ENABLE_RX_FULLCAN_OBJECTS */




/**********************************************************************************************************************
 *  CanLL_ErrorHandlingBegin
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_ErrorHandlingBegin
Relation_Context:
# from CanHL_ErrorHandling() #
StatusPolling
Relation:
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
*/
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_ErrorHandlingBegin(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY)
{
  /* #10 CanLL_ErrorHandlingBegin(): nothing to do here */
  CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}
/* CODE CATEGORY 2 END */

/**********************************************************************************************************************
 *  CanLL_BusOffOccured
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_BusOffOccured
Relation_Context:
# from CanHL_ErrorHandling() #
StatusPolling
Relation:
OneChOpt
ChannelAmount
BusOffRecoveryDefine
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
 *
 *
*/
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_BusOffOccured(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY)
{
  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);
  vuint8 retVal = kCanFalse; /* PRQA S 2981,2982 */ /* MD_MSR_RetVal */
  
  /* #10 Check for BusOff */
  if((pFlexCANLocal->estat & kFlexCAN_BOFF_INT) != 0u) /* COV_CAN_BUSOFF_HANDLING */
  {
    /* #20 clear busoff and error interrupt flags */
    pFlexCANLocal->estat = (CANSFR_TYPE)(kFlexCAN_BOFF_INT | kFlexCAN_ERR_INT); /* clear busoff and error interrupt flags */ /* SBSW_CAN_LL01 */

#if defined ( C_ENABLE_BUSOFF_RECOVERY_COMPLIANT )
    /* #30 Delete pending transmit requests */
    {
      CanObjectHandle hwObjHandle;
      for (hwObjHandle = CAN_HL_HW_TX_STARTINDEX(canHwChannel); hwObjHandle < CAN_HL_HW_TX_STOPINDEX(canHwChannel); hwObjHandle++)
      {
        LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control) = kTxCodeInactive; /* set all mailboxes inactive */ /* SBSW_CAN_LL02 */
      }
    }
#endif
    retVal = kCanTrue;
  }
  
  return retVal;
}
/* CODE CATEGORY 2 END */


/**********************************************************************************************************************
 *  CanLL_ErrorHandlingEnd
 *********************************************************************************************************************/
 /*
 |<DataModelStart>| CanLL_ErrorHandlingEnd
 Relation_Context:
 # from CanHL_ErrorHandling() #
 StatusPolling
 Relation:
 Parameter_PreCompile:
 Parameter_Data:
 Constrain:
 |<DataModelEnd>|
 */
/*!
* Internal comment removed.
 *
 *
*/
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_ErrorHandlingEnd(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY)
{
  /* #10 CanLL_ErrorHandlingEnd(): nothing to do here */
  CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}
/* CODE CATEGORY 2 END */

#if defined( C_ENABLE_EXTENDED_STATUS )
/**********************************************************************************************************************
 *  CanLL_GetStatusBegin
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_GetStatusBegin
Relation_Context:
# from Can_GetStatus
CanGetStatus
Relation:
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
*/
/* CODE CATEGORY 3 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_GetStatusBegin(CAN_CHANNEL_CANTYPE_ONLY)
{
  /* #10 CanLL_GetStatusBegin(): nothing to do here */
  CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}
/* CODE CATEGORY 3 END */
#endif



/**********************************************************************************************************************
 *  CanLL_ModeTransition
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_ModeTransition
Relation_Context:
# from CanHL_ModeTransition() #
Wakeup, OneChOpt, HardwareLoopCheck, ChannelAmount
RamCheck, OneChOpt, HardwareLoopCheck, ChannelAmount
# from Can_Mainfunction_Mode() #
ChannelAmount
Relation:
Wakeup
SilentMode
ReInitStart
BusOffRecoveryDefine
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
 */
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_STATIC, vuint8, STATIC_CODE) CanLL_ModeTransition(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST vuint8 mode, vuint8 busOffRecovery, vuint8 ramCheck)
{
  vuint8 retVal = kCanFailed; /* PRQA S 2981,2982 */ /* MD_MSR_RetVal */
#if ( (CAN_REINIT_START == STD_ON) )
  if ( (mode != kCanModeStartReinit)
  )
  {
    canLL_canStartReinitState[channel] = kCanLLStateStart; /* SBSW_CAN_LL14 */
  }
#endif
  switch(mode)
  {

    /* #400 STOP reinit request */
    case kCanModeStopReinit:
      retVal = CanHL_ReInit(CAN_CHANNEL_CANPARA_FIRST ramCheck);
      break;

    /* #500 STOP reinit fast request */
    case kCanModeStopReinitFast:
      retVal = CanLL_StopTransition(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST busOffRecovery, ramCheck);
      break;

    /* #600 START request */
#if ( (CAN_REINIT_START == STD_OFF) )
    case kCanModeStart:
#endif
#if ( (CAN_REINIT_START == STD_ON) )
    /* #700 START reinit request */
    case kCanModeStartReinit:
#endif
#if defined ( C_ENABLE_SILENT_MODE )
    /* #800 SILENT mode request */
    case kCanModeSilent:
#endif
      retVal = CanLL_StartTransition(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST mode, ramCheck);
      break;

    /* #1000 BUSOFF start request */
    case kCanModeResetBusOffStart:
#if defined ( C_ENABLE_BUSOFF_RECOVERY_COMPLIANT )
      retVal = kCanOk;
#else
      retVal = CanLL_ReInit(CAN_CHANNEL_CANPARA_FIRST ramCheck);
#endif
      break;

    /* #1100 BUSOFF end request */
    case kCanModeResetBusOffEnd:
#if defined ( C_ENABLE_BUSOFF_RECOVERY_COMPLIANT )
      retVal = CanLL_BusOffEndTransition(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST ramCheck);
#else
      retVal = CanLL_StartTransition(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST mode, ramCheck);
#endif
      break;

    default:
      /* retVal is kCanFailed */
      break;
  }

  return retVal;
}
/* CODE CATEGORY 4 END */

/**********************************************************************************************************************
 *  CanLL_StopReinit
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_StopReinit
Relation_Context:
# from CanLL_StopTransition #
OneChOpt,ChannelAmount
Relation:
TxFullCANSupport
RxFullCANSupport
RxBasicCANSupport,CanFdSupport
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_StopReinit(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY)
{
  CanObjectHandle hwObjHandle;
  CanObjectHandle mailboxHandle = 0u; /* PRQA S 2981,2982 */ /* MD_MSR_RetVal */
  tFlexCANPtr     pFlexCANLocal;
# if defined ( C_ENABLE_RX_BASICCAN_OBJECTS )
#  if defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
  CanObjectHandle hwObjCount;
#  else
  vuint8 fifoLoopCnt = 0u;
#  endif
# endif

  /* #10 Clear all pending Rx/Tx interrupts */
  pFlexCANLocal = pFlexCAN(canHwChannel);
  pFlexCANLocal->iflag1 = CANSFR_SET; /* clear pending Rx/Tx interrupts */ /* SBSW_CAN_LL01 */
# if defined ( C_ENABLE_MB32TO63 ) /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
#  if defined ( C_ENABLE_ASYM_MAILBOXES ) /* COV_CAN_FLEXCAN3_DERIVATIVE_ASYM_MAILBOXES */
  if (NUMBER_OF_MAX_MAILBOXES(canHwChannel) > 32u) /* PRQA S 2741,2742 */ /* MD_Can_ConstValue */ /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
#  endif
  {
    pFlexCANLocal->iflag2 = CANSFR_SET; /* clear pending Rx/Tx interrupts */ /* SBSW_CAN_LL01 */
  }
# endif
# if defined ( C_ENABLE_MB64TO95 ) /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
#  if defined ( C_ENABLE_ASYM_MAILBOXES ) /* COV_CAN_FLEXCAN3_DERIVATIVE_ASYM_MAILBOXES */
  if (NUMBER_OF_MAX_MAILBOXES(canHwChannel) > 64u) /* PRQA S 2741,2742 */ /* MD_Can_ConstValue */ /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
#  endif
  {
    pFlexCANLocal->iflag3 = CANSFR_SET; /* clear pending Rx/Tx interrupts */ /* SBSW_CAN_LL01 */
  }
# endif
# if defined ( C_ENABLE_MB96TO127 ) /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
  pFlexCANLocal->iflag4 = CANSFR_SET; /* clear pending Rx/Tx interrupts */ /* SBSW_CAN_LL01 */
# endif

  /* #20 Clear pending BusOff and error interrupts */
  pFlexCANLocal->estat = (vuint32)kFlexCAN_STATUS_INT; /* SBSW_CAN_LL01 */

  /* #30 Activate BusOff auto recovery */
  pFlexCANLocal->control1 &= (vuint32)(~kFlexCAN_BOFF_REC); /* SBSW_CAN_LL01 */

  /* #40 Inactivate all Tx mailboxes */

  for (hwObjHandle = CAN_HL_HW_TX_STARTINDEX(canHwChannel); hwObjHandle < CAN_HL_HW_TX_STOPINDEX(canHwChannel); hwObjHandle++)
  {
    LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control) = kTxCodeInactive; /* set all mailboxes inactive */ /* SBSW_CAN_LL02 */
  }

# if defined ( C_ENABLE_RX_FULLCAN_OBJECTS )
  /* #50 Disable all Rx FullCAN mailboxes */
  for (mailboxHandle = CAN_HL_MB_RX_FULL_STARTINDEX(canHwChannel); mailboxHandle < CAN_HL_MB_RX_FULL_STOPINDEX(canHwChannel); mailboxHandle++)
  {
    hwObjHandle = Can_GetMailboxHwHandle(mailboxHandle);
    LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control) &= kRxCodeClear; /* clear control register and do not change the ID type */ /* SBSW_CAN_LL02 */
    LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control) |= kRxCodeEmpty; /* set mailbox ready for receive */ /* SBSW_CAN_LL02 */
  }
# endif

# if defined ( C_ENABLE_RX_BASICCAN_OBJECTS )
#  if defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
  /* #60 Disable all Rx BasicCAN mailboxes */
  for (mailboxHandle = CAN_HL_MB_RX_BASIC_STARTINDEX(canHwChannel); mailboxHandle < CAN_HL_MB_RX_BASIC_STOPINDEX(canHwChannel); mailboxHandle++)
  {
    for (hwObjCount = 0u; hwObjCount < Can_GetMailboxSize(mailboxHandle); hwObjCount++)
    {
      hwObjHandle = Can_GetMailboxHwHandle(mailboxHandle) + hwObjCount;
      LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control) &= kRxCodeClear; /* clear control register and do not change the ID type */ /* SBSW_CAN_LL02 */
      LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control) |= kRxCodeEmpty; /* set mailbox ready for receive */ /* SBSW_CAN_LL02 */
    }
  }
#  else
  /* #70 Clear pending RxFIFO interrupts */
  while(((pFlexCANLocal->iflag1 & kRxFIFO_NEWMSG) != 0u) && (fifoLoopCnt < C_FLEXCAN_RXFIFO_MAXLOOP)) /* COV_CAN_RXFIFO_HANDLING */
  {
    pFlexCANLocal->iflag1 = (vuint32)kRxFIFO_NEWMSG; /* clear RxFIFO pending interrupts */ /* SBSW_CAN_LL01 */
    fifoLoopCnt++;
  }
#  endif
# endif
  CAN_DUMMY_STATEMENT(mailboxHandle); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}
/* CODE CATEGORY 4 END */


/**********************************************************************************************************************
 *  CanLL_CanInterruptDisable
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_CanInterruptDisable
Relation_Context:
# from Can_DisableControllerInterrupts #
IndividualPolling
TxPolling
RxPolling
StatusPolling
Relation:
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
 *
 *
*/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_CanInterruptDisable(CAN_HW_CHANNEL_CANTYPE_FIRST tCanLLCanIntOldPtr localInterruptOldFlagPtr)
{
#if defined( C_ENABLE_CAN_RXTX_INTERRUPT )   || \
    defined( C_ENABLE_CAN_BUSOFF_INTERRUPT ) /* COV_CAN_INTERRUPT_SUPPORT */ 
  {
    /* ----- Local Variables ---------------------------------------------- */
    tFlexCANPtr pFlexcan = pFlexCAN(canHwChannel);

    /* ----- Implementation ----------------------------------------------- */
    /* #10 Disable RxTx interrupts */
    CAN_DISABLE_RXTX_INTERRUPT_0TO31(localInterruptOldFlagPtr); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL01 */
# if defined (C_ENABLE_ASYM_MAILBOXES) /* COV_CAN_FLEXCAN3_DERIVATIVE_ASYM_MAILBOXES */
    if (NUMBER_OF_MAX_MAILBOXES(canHwChannel) > 32u) /* PRQA S 2741,2742 */ /* MD_Can_ConstValue */ /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
# endif
    {
      CAN_DISABLE_RXTX_INTERRUPT_32TO63(localInterruptOldFlagPtr); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL01 */
    }
# if defined (C_ENABLE_ASYM_MAILBOXES) /* COV_CAN_FLEXCAN3_DERIVATIVE_ASYM_MAILBOXES */
    if (NUMBER_OF_MAX_MAILBOXES(canHwChannel) > 64u) /* PRQA S 2741,2742 */ /* MD_Can_ConstValue */ /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
# endif
    {
      CAN_DISABLE_RXTX_INTERRUPT_64TO95(localInterruptOldFlagPtr); /* PRQA S 2880 */ /* MD_Can_ConstValue */ /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL01 */
    }
    CAN_DISABLE_RXTX_INTERRUPT_96TO127(localInterruptOldFlagPtr); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL01 */

    /* #20 Disable BusOff interrupts */
    CAN_DISABLE_BUSOFF_INTERRUPT(localInterruptOldFlagPtr); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL01 */

    /* #30 Disable WakeUp interrupts */
    CAN_DISABLE_WAKEUP_INTERRUPT(localInterruptOldFlagPtr); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL01 */
  }
#else
  CAN_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CAN_DUMMY_STATEMENT(localInterruptOldFlagPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
}
/* CODE CATEGORY 1 END */

/**********************************************************************************************************************
 *  CanLL_CanInterruptRestore
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_CanInterruptRestore
Relation_Context:
# from Can_EnableControllerInterrupts #
IndividualPolling
TxPolling
RxPolling
StatusPolling
Relation:
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
 *
 *
*/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_CanInterruptRestore(CAN_HW_CHANNEL_CANTYPE_FIRST tCanLLCanIntOld localInterruptOldFlag)
{
#if defined( C_ENABLE_CAN_RXTX_INTERRUPT )   || \
    defined( C_ENABLE_CAN_BUSOFF_INTERRUPT ) /* COV_CAN_INTERRUPT_SUPPORT */ 
  {
    /* ----- Local Variables ---------------------------------------------- */
    tFlexCANPtr pFlexcan = pFlexCAN(canHwChannel);

    /* ----- Implementation ----------------------------------------------- */
    /* #10 Restore RxTx interrupts */
    CAN_RESTORE_RXTX_INTERRUPT_0TO31(localInterruptOldFlag); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL01 */
# if defined (C_ENABLE_ASYM_MAILBOXES) /* COV_CAN_FLEXCAN3_DERIVATIVE_ASYM_MAILBOXES */
    if (NUMBER_OF_MAX_MAILBOXES(canHwChannel) > 32u) /* PRQA S 2741,2742 */ /* MD_Can_ConstValue */ /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
# endif
    {
      CAN_RESTORE_RXTX_INTERRUPT_32TO63(localInterruptOldFlag); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL01 */
    }
# if defined (C_ENABLE_ASYM_MAILBOXES) /* COV_CAN_FLEXCAN3_DERIVATIVE_ASYM_MAILBOXES */
    if (NUMBER_OF_MAX_MAILBOXES(canHwChannel) > 64u) /* PRQA S 2741,2742 */ /* MD_Can_ConstValue */ /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
# endif
    {
      CAN_RESTORE_RXTX_INTERRUPT_64TO95(localInterruptOldFlag); /* PRQA S 2880 */ /*  MD_MSR_Unreachable */ /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL01 */
    }
    CAN_RESTORE_RXTX_INTERRUPT_96TO127(localInterruptOldFlag); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL01 */

    /* #20 Restore BusOff interrupts */
    CAN_RESTORE_BUSOFF_INTERRUPT(localInterruptOldFlag); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL01 */

    /* #30 Restore WakeUp interrupts */
    CAN_RESTORE_WAKEUP_INTERRUPT(localInterruptOldFlag); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL01 */
  }
#else
  CAN_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CAN_DUMMY_STATEMENT(localInterruptOldFlag); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
}
/* CODE CATEGORY 1 END */


/* CODE CATEGORY 4 START */
/****************************************************************************
| NAME:             CanLL_SetFlexCANToInitMode
****************************************************************************/
/*
|<DataModelStart>| CanLL_SetFlexCANToInitMode
Relation_Context:
# from CanLL_InitBegin #
OneChOpt, ChannelAmount
Relation:
HardwareLoopCheck
SilentMode
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_SetFlexCANToInitMode(CAN_HW_CHANNEL_CANTYPE_FIRST CanInitHandle initObject)
{
  /* ----- Local Variables ---------------------------------------------- */
  Can_ReturnType loopResult = CAN_OK; /* PRQA S 2981,2982 */ /* MD_MSR_RetVal */
  vuint8 returnCode = kCanOk; /* PRQA S 2981,2982 */ /* MD_MSR_RetVal */
  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);
  
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if FlexCAN is DISABLED or in a NON_BUSOFF state (and in NON_LOM mode) */
  if (((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_DISABLE_MODE) == kFlexCAN_DISABLE_MODE)
    || (((CAN_READ_PROTECTED_REG_32BIT(pFlexCANLocal->estat) & kFlexCAN_FCS_BOFF) == 0u)
#if defined(C_ENABLE_SILENT_MODE)
    && ((CAN_READ_PROTECTED_REG_32BIT(pFlexCANLocal->control1) & kFlexCAN_LOM) == 0u)
#endif
  )) /* COV_CAN_INIT_STIMULATION */ /* SBSW_CAN_LL01 */ /* SBSW_CAN_LL01 */ /* SBSW_CAN_LL01 */
  {
    /* #20 Check if FlexCAN is ENABLED */
    if ((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_DISABLE_ONLY_BITS) == 0u) /* COV_CAN_INIT_STIMULATION */ /* SBSW_CAN_LL01 */
    {
      /* #30 Enter FREEZE mode (INIT mode) of FlexCAN */
      CAN_WRITE_PROTECTED_REG_SET(pFlexCANLocal->canmcr, kFlexCAN_FRZ); /* SBSW_CAN_LL01 */
      CAN_WRITE_PROTECTED_REG_SET(pFlexCANLocal->canmcr, kFlexCAN_HALT); /* SBSW_CAN_LL01 */
      if ((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_MCR) != kFlexCAN_FREEZE_MODE) /* COV_CAN_HARDWARE_PROCESSING_TIME */ /* SBSW_CAN_LL01 */
      {
        CanLL_ApplCanTimerStart(kCanLoopEnterFreezeModeInit); /* start hw loop timer */ /* SBSW_CAN_LL08 */
        do  
        { /* wait for FRZACK */  
          loopResult = CanLL_ApplCanTimerLoop(kCanLoopEnterFreezeModeInit);
        } while(((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_MCR) != kFlexCAN_FREEZE_MODE) && (loopResult == CAN_OK)); /* COV_CAN_TIMEOUT_DURATION */ /* SBSW_CAN_LL01 */ /* PRQA S 2995,0303 */ /* MD_Can_ConstValue */ /* MD_Can_HwAccess */
        CanLL_ApplCanTimerEnd(kCanLoopEnterFreezeModeInit); /* stop hw loop timer */ /* SBSW_CAN_LL08 */
#if defined( C_ENABLE_HW_LOOP_TIMER )
        if ((loopResult != CAN_OK) && (canLL_FlexCANInitResultNeeded[canHwChannel] == kCanTrue)) /* COV_CAN_TIMEOUT_DURATION */
        {
          returnCode = kCanFailed;
        }
#endif
      }
      
      /* #40 Enter DISABLE mode of FlexCAN for clock selection */
      CAN_WRITE_PROTECTED_REG_SET(pFlexCANLocal->canmcr, kFlexCAN_MDIS); /* disable FlexCAN module before clock selection */ /* SBSW_CAN_LL01 */
      if ((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_LPM_ACK) != kFlexCAN_LPM_ACK) /* COV_CAN_HARDWARE_PROCESSING_TIME */ /* SBSW_CAN_LL01 */
      {
        CanLL_ApplCanTimerStart(kCanLoopEnterDisableModeInit); /* start hw loop timer */ /* SBSW_CAN_LL08 */
        do
        { /* wait for FlexCAN is disabled */
          loopResult = CanLL_ApplCanTimerLoop(kCanLoopEnterDisableModeInit);
        } while(((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_LPM_ACK) != kFlexCAN_LPM_ACK) && (loopResult == CAN_OK)); /* COV_CAN_TIMEOUT_DURATION */ /* SBSW_CAN_LL01 */ /* PRQA S 2995,0303 */ /* MD_Can_ConstValue */ /* MD_Can_HwAccess */
        CanLL_ApplCanTimerEnd(kCanLoopEnterDisableModeInit);  /* stop hw loop timer */ /* SBSW_CAN_LL08 */
#if defined( C_ENABLE_HW_LOOP_TIMER )
        if ((loopResult != CAN_OK)  && (canLL_FlexCANInitResultNeeded[canHwChannel] == kCanTrue)) /* COV_CAN_TIMEOUT_DURATION */
        {
          returnCode = kCanFailed;
        }
#endif
      }
    }
    
    /* #50 Set FlexCAN clock source */
    if((Can_GetControl1OfInitObject(initObject) & kFlexCAN_CLK_SRC) != 0u) /* COV_CAN_CLK_SRC_GENERATION */
    {
      CAN_WRITE_PROTECTED_REG_SET_32BIT(pFlexCANLocal->control1, kFlexCAN_CLK_SRC); /* SBSW_CAN_LL01 */
    }
    else
    {
      CAN_WRITE_PROTECTED_REG_RESET_32BIT(pFlexCANLocal->control1, kFlexCAN_CLK_SRC); /* SBSW_CAN_LL01 */
    }

    /* #60 Leave DISABLE mode of FlexCAN */
    CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_MDIS); /* clear MDIS bit */ /* SBSW_CAN_LL01 */
    if ((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_LPM_ACK) == kFlexCAN_LPM_ACK) /* COV_CAN_HARDWARE_PROCESSING_TIME */ /* SBSW_CAN_LL01 */
    {
      CanLL_ApplCanTimerStart(kCanLoopLeaveDisableModeInit); /* start hw loop timer */ /* SBSW_CAN_LL08 */
      do
      { /* wait for FlexCAN is enabled */
        loopResult = CanLL_ApplCanTimerLoop(kCanLoopLeaveDisableModeInit);
      } while(((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_LPM_ACK) == kFlexCAN_LPM_ACK) && (loopResult == CAN_OK)); /* COV_CAN_TIMEOUT_DURATION */ /* SBSW_CAN_LL01 */ /* PRQA S 2995,0303 */ /* MD_Can_ConstValue */ /* MD_Can_HwAccess */
      CanLL_ApplCanTimerEnd(kCanLoopLeaveDisableModeInit);  /* stop hw loop timer */ /* SBSW_CAN_LL08 */
#if defined( C_ENABLE_HW_LOOP_TIMER )
      if ((loopResult != CAN_OK)  && (canLL_FlexCANInitResultNeeded[canHwChannel] == kCanTrue)) /* COV_CAN_TIMEOUT_DURATION */
      {
        returnCode = kCanFailed;
      }
#endif
    }
  }

  return (returnCode);
} /* PRQA S 6010,6030 */ /* MD_MSR_STPTH,MD_MSR_STCYC */
/* CODE CATEGORY 4 END */

/* CODE CATEGORY 4 START */
/****************************************************************************
| NAME:             CanLL_ExecuteSoftReset
****************************************************************************/
/*
|<DataModelStart>| CanLL_ExecuteSoftReset
Relation_Context:
# from CanLL_InitBegin #
OneChOpt, ChannelAmount
Relation:
CanFdSupport,WorkaroundErrata010368
HardwareLoopCheck,CanFdSupport,WorkaroundErrata010368
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
 *
 *
 *
 *
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_ExecuteSoftReset(CAN_HW_CHANNEL_CANTYPE_ONLY)
{
  Can_ReturnType loopResult1 = CAN_OK; /* PRQA S 2981,2982 */ /* MD_MSR_RetVal */
#if defined( C_ENABLE_CAN_FD_USED ) && defined( C_ENABLE_WORKAROUND_ERR010368 )
  Can_ReturnType loopResult2 = CAN_OK; /* PRQA S 2981,2982 */ /* MD_MSR_RetVal */
#endif
  vuint8 returnCode = kCanOk; /* PRQA S 2981,2982 */ /* MD_MSR_RetVal */
  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);
  
  /* ----- Implementation ----------------------------------------------- */     
  /* *********************************************************************** */
  /* Perform FlexCAN soft reset.                                             */
  /* Please note: the soft reset cannot be applied while clocks are          */
  /* shut down: low power mode or clocks are not enabled.                    */
  /* Please check clock settings if soft reset cannot be finalized.          */
  /* Errata e10368: Perform a second soft reset in case of FD enabled        */
  /* *********************************************************************** */
  /* #10 Execute SoftReset of FlexCAN */
  CAN_WRITE_PROTECTED_REG(pFlexCANLocal->canmcr, kFlexCAN_SOFT_RST); /* SBSW_CAN_LL01 */
  if ((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_SOFT_RST) == kFlexCAN_SOFT_RST) /* COV_CAN_HARDWARE_PROCESSING_TIME */ /* SBSW_CAN_LL01 */
  {
    /* #20 Wait for soft reset confirmation from hardware */
    CanLL_ApplCanTimerStart(kCanLoopResetInit); /* start hw loop timer */ /* SBSW_CAN_LL08 */
    do
    { /* wait for SOFT_RST */
      loopResult1 = CanLL_ApplCanTimerLoop(kCanLoopResetInit);
    } while(((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_SOFT_RST) == kFlexCAN_SOFT_RST) && (loopResult1 == CAN_OK)); /* SBSW_CAN_LL01 */ /* COV_CAN_TIMEOUT_DURATION */ /* PRQA S 2995,0303 */ /* MD_Can_ConstValue */ /* MD_Can_HwAccess */
    CanLL_ApplCanTimerEnd(kCanLoopResetInit);  /* stop hw loop timer */ /* SBSW_CAN_LL08 */
  }
#if defined( C_ENABLE_CAN_FD_USED ) && defined( C_ENABLE_WORKAROUND_ERR010368 )
  /* #30 Execute SoftReset of FlexCAN second time (errata e10368) if CAN FD is enabled */
  if (Can_IsHasCANFDBaudrateOfControllerConfig(canHwChannel)) /* COV_CAN_FD_BAUDRATE_AVAILABILITY */
  {
    CAN_WRITE_PROTECTED_REG(pFlexCANLocal->canmcr, kFlexCAN_SOFT_RST); /* SBSW_CAN_LL01 */
    if ((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_SOFT_RST) == kFlexCAN_SOFT_RST) /* COV_CAN_HARDWARE_PROCESSING_TIME */ /* SBSW_CAN_LL01 */
    {
      /* #40 Wait for soft reset confirmation from hardware second time (errata e10368) if CAN FD is enabled */
      CanLL_ApplCanTimerStart(kCanLoopResetInit); /* start hw loop timer */ /* SBSW_CAN_LL08 */
      do
      { /* wait for SOFT_RST */
        loopResult2 = CanLL_ApplCanTimerLoop(kCanLoopResetInit);
      } while(((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_SOFT_RST) == kFlexCAN_SOFT_RST) && (loopResult2 == CAN_OK)); /* SBSW_CAN_LL01 */ /* COV_CAN_TIMEOUT_DURATION */ /* PRQA S 2995,0303 */ /* MD_Can_ConstValue */ /* MD_Can_HwAccess */
      CanLL_ApplCanTimerEnd(kCanLoopResetInit);  /* stop hw loop timer */ /* SBSW_CAN_LL08 */
    }
  }
#endif

#if defined(C_ENABLE_HW_LOOP_TIMER)
  if (((loopResult1 != CAN_OK)
# if defined( C_ENABLE_CAN_FD_USED ) && defined( C_ENABLE_WORKAROUND_ERR010368 )
      || (loopResult2 != CAN_OK)
# endif
      ) && (canLL_FlexCANInitResultNeeded[canHwChannel] == kCanTrue)) /* COV_CAN_TIMEOUT_DURATION */
  {
    returnCode = kCanFailed;
  }
#endif

  /* #50 Reset SUPV bit to grant access to CAN register (except MCR register) in User Mode */
  /* set all CAN register except the MCR register in unrestricted memory space directly after soft reset */
  CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_SUPV); /* SBSW_CAN_LL01 */

  return (returnCode);
}
/* CODE CATEGORY 4 END */

/* CODE CATEGORY 4 START */
/****************************************************************************
| NAME:             CanLL_ReInit
****************************************************************************/
/*
|<DataModelStart>| CanLL_ReInit
Relation_Context:
# from CanLL_ModeTransition #
BusOffRecoveryDefine
# from CanLL_StopTransition #
SilentMode
# from CanLL_StartTransition #
ReInitStart
Relation:
OneChOpt
ChannelAmount
HardwareLoopCheck
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_ReInit(CAN_CHANNEL_CANTYPE_FIRST vuint8 ramCheck)
{
  vuint8 retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* *********************************************************************** */
  /* Reinitialisation of FlexCAN                                             */
  /* *********************************************************************** */
  /* #10 Request CanHL_ReInit() */
#if defined (C_ENABLE_HW_LOOP_TIMER)
        canLL_FlexCANInitResultNeeded[channel] = kCanFalse; /* SBSW_CAN_LL14 */
#endif
        retVal = CanHL_ReInit(CAN_CHANNEL_CANPARA_FIRST ramCheck);
#if defined (C_ENABLE_HW_LOOP_TIMER)
        canLL_FlexCANInitResultNeeded[channel] = kCanTrue; /* SBSW_CAN_LL14 */
#endif
  return (retVal);
}
/* CODE CATEGORY 4 END */

/* CODE CATEGORY 4 START */
/****************************************************************************
| NAME:             CanLL_StopTransition
****************************************************************************/
/*
|<DataModelStart>| CanLL_StopTransition
Relation_Context:
# from CanLL_ModeTransition #
OneChOpt,ChannelAmount
Relation:
SilentMode
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_StopTransition(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST vuint8 busOffRecovery, vuint8 ramCheck)
{
  vuint8 retVal;
  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);

  /* ----- Implementation ----------------------------------------------- */
  /* *********************************************************************** */
  /* Handle stop transition of FlexCAN                                       */
  /* *********************************************************************** */
  if (CanLL_HwIsBusOff(canHwChannel)) /* COV_CAN_STOP_BOFF_STIMULATION */ /* SBSW_CAN_LL01 */
  { /* #10 Check for BusOff state */
    if (busOffRecovery == kCanContinueBusOffRecovery) /* COV_CAN_STOP_BOFF_STIMULATION */
    { /* #20 Stop Transition in case of kCanContinueBusOffRecovery */
      retVal = kCanFailed;
    }
    else
    { /* #30 Stop Transition in case of kCanFinishBusOffRecovery */
      retVal = CanLL_ReInit(CAN_CHANNEL_CANPARA_FIRST ramCheck);
    }
  }
# if defined (C_ENABLE_SILENT_MODE)
  else if (CanLL_HwIsListenOnlyMode(canHwChannel)) /* SBSW_CAN_LL01 */
  { /* #40 Stop Transition in case of silent mode active */
      retVal = CanLL_ReInit(CAN_CHANNEL_CANPARA_FIRST ramCheck);
  }
# endif
  else
  { /* #50 Fast Re-Init Stop Transition */
    if (CanLL_HwIsStop(canHwChannel)) /* SBSW_CAN_LL01 */
    { /* #60 Check for stop transition finished */
      CanLL_StopReinit(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_ONLY);
      CanHL_CleanUpSendState(CAN_CHANNEL_CANPARA_ONLY);
      retVal = kCanOk;
    }
    else if (CanLL_HwIsStopRequested(canHwChannel)) /* SBSW_CAN_LL01 */ /* COV_CAN_HARDWARE_PROCESSING_TIME */
    { /* #70 Check for stop mode requested */
      retVal = kCanRequested;
    }
    else
    { /* #80 Request stop mode for all other cases */
      CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_MDIS); /* clear MDIS bit */ /* SBSW_CAN_LL01 */
      CAN_WRITE_PROTECTED_REG_SET(pFlexCANLocal->canmcr, kFlexCAN_FRZ);  /* set FRZ bit */ /* SBSW_CAN_LL01 */
      CAN_WRITE_PROTECTED_REG_SET(pFlexCANLocal->canmcr, kFlexCAN_HALT); /* set HALT bit */ /* SBSW_CAN_LL01 */
      retVal = kCanRequested;
    }
  }

  return (retVal);
}
/* CODE CATEGORY 4 END */

/* CODE CATEGORY 4 START */
/****************************************************************************
| NAME:             CanLL_StartTransition
****************************************************************************/
/*
|<DataModelStart>| CanLL_StartTransition
Relation_Context:
# from CanLL_ModeTransition #
OneChOpt,ChannelAmount
Relation:
SilentMode
ReInitStart
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_StartTransition(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST vuint8 mode, vuint8 ramCheck)
{
  vuint8 retVal;
  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);
  /* ----- Implementation ----------------------------------------------- */
  /* *********************************************************************** */
  /* Handle start transition of FlexCAN                                      */
  /* *********************************************************************** */
#if (CAN_REINIT_START == STD_ON)
  retVal = kCanOk;
  if ( (mode == kCanModeStartReinit) 
     ) /* COV_CAN_REINITSTART_STIMULATION */
  { /* #10 Check for kCanModeStartReinit */
    if (canLL_canStartReinitState[canHwChannel] == kCanLLStateStart) /* SBSW_CAN_LL14 */
    { /* #20 Check for reinitialization execution */
      retVal = CanLL_ReInit(CAN_CHANNEL_CANPARA_FIRST ramCheck);
      canLL_canStartReinitState[canHwChannel] = kCanLLStateRequested; /* SBSW_CAN_LL14 */
    }
  }
  if (retVal == kCanOk) /* COV_CAN_HARDWARE_FAILURE */
#endif
  {
    if (CanLL_HwIsStart(canHwChannel)) /* SBSW_CAN_LL01 */
    { /* #30 Check for start transition finished */
#if (CAN_REINIT_START == STD_ON)
      canLL_canStartReinitState[canHwChannel] = kCanLLStateStart; /* SBSW_CAN_LL14 */
#endif
      retVal = kCanOk;
    }
    else if (CanLL_HwIsStartRequested(canHwChannel)) /* SBSW_CAN_LL01 */ /* COV_CAN_START_STIMULATION */
    { /* #40 Check for start mode requested */
      retVal = kCanRequested;
    }
    else
    { /* #50 Process start mode */
      {
#if defined ( C_ENABLE_SILENT_MODE )
        if (mode == kCanModeSilent)
        { /* #60 Check for kCanModeSilent */
          pFlexCANLocal->control1 |= kFlexCAN_LOM; /* SBSW_CAN_LL01 */
        }
        else
        {
          pFlexCANLocal->control1 &= (vuint32)(~kFlexCAN_LOM); /* SBSW_CAN_LL01 */
        }
#endif
        /* #70 Request start mode */
        /* request NORMAL mode - considered as CanStart mode */
        CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_MDIS); /* clear MDIS bit */ /* SBSW_CAN_LL01 */
        CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_HALT); /* clear HALT bit */ /* SBSW_CAN_LL01 */
        CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_FRZ);  /* clear FRZ bit  */ /* SBSW_CAN_LL01 */

        /* #80 Deactivate BusOff auto recovery mode */
        /* the transition CanStop - CanStart does also leave a potential BusOff state */
        pFlexCANLocal->control1 |= kFlexCAN_BOFF_REC; /* SBSW_CAN_LL01 */

        retVal = kCanRequested;
      }
    }
  }
  CAN_DUMMY_STATEMENT(ramCheck); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CAN_DUMMY_STATEMENT(mode); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  return (retVal);
}
/* CODE CATEGORY 4 END */

#if defined ( C_ENABLE_BUSOFF_RECOVERY_COMPLIANT )
/* CODE CATEGORY 4 START */
/****************************************************************************
| NAME:             CanLL_BusOffEndTransition
****************************************************************************/
/*
|<DataModelStart>| CanLL_BusOffEndTransition
Relation_Context:
# from CanLL_ModeTransition #
BusOffRecoveryDefine
Relation:
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_BusOffEndTransition(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST vuint8 ramCheck)
{
  vuint8 retVal;
  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);

  /* ----- Implementation ----------------------------------------------- */
  /* *********************************************************************** */
  /* Handle busoff end transition of FlexCAN                                      */
  /* *********************************************************************** */
  if (CanLL_HwIsBusOff(canHwChannel)) /* SBSW_CAN_LL01 */
  { /* #10 Check for busoff state */
    if (!CanLL_HwIsAutoRecoveryActive(canHwChannel)) /* SBSW_CAN_LL01 */ /* COV_CAN_BUSOFFEND_STIMULATION */
    { /* #20 Activate busoff auto recovery */
      pFlexCANLocal->control1 &= (vuint32)(~kFlexCAN_BOFF_REC); /* SBSW_CAN_LL01 */
    }
    if (!CanLL_HwIsStartRequested(canHwChannel)) /* COV_CAN_BUSOFFEND_STIMULATION */ /* SBSW_CAN_LL01 */
    { /* #30 Start auto recovery process in case of CAN controler is not started */
      CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_MDIS); /* clear MDIS bit */ /* SBSW_CAN_LL01 */
      CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_HALT); /* clear HALT bit */ /* SBSW_CAN_LL01 */
      CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_FRZ);  /* clear FRZ bit  */ /* SBSW_CAN_LL01 */
    }
    retVal = kCanRequested;
  }
  else
  { /* #40 Check for busoff state left */
    if (CanLL_HwIsStart(canHwChannel)) /* COV_CAN_BUSOFFEND_STIMULATION */ /* SBSW_CAN_LL01 */
    { /* #50 Check for start transition finished */
      if (CanLL_HwIsAutoRecoveryActive(canHwChannel)) /* SBSW_CAN_LL01 */
      { /* #60 In case of autorecovery finished: Controller re-initialization */
        retVal = CanLL_ReInit(CAN_CHANNEL_CANPARA_FIRST ramCheck);
        if (retVal == kCanOk) /* COV_CAN_BUSOFFEND_STIMULATION */
        {
          CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_MDIS); /* clear MDIS bit */ /* SBSW_CAN_LL01 */
          CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_HALT); /* clear HALT bit */ /* SBSW_CAN_LL01 */
          CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_FRZ);  /* clear FRZ bit  */ /* SBSW_CAN_LL01 */

          pFlexCANLocal->control1 |= kFlexCAN_BOFF_REC; /* SBSW_CAN_LL01 */
          retVal = kCanRequested;
        }
      }
      else
      { /* #70 Start transition finished */
        retVal = kCanOk;
      }
    }
    else if (CanLL_HwIsStartRequested(canHwChannel)) /* COV_CAN_BUSOFFEND_STIMULATION */ /* SBSW_CAN_LL01 */
    { /* #80 Check for start mode requested */
       retVal = kCanRequested;
    }
    else
    { /* #90 Request start mode in case of busoff end due to a controller re-initialization */
      /* request NORMAL mode - considered as CanStart mode */
      CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_MDIS); /* clear MDIS bit */ /* SBSW_CAN_LL01 */
      CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_HALT); /* clear HALT bit */ /* SBSW_CAN_LL01 */
      CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_FRZ);  /* clear FRZ bit  */ /* SBSW_CAN_LL01 */

      /* the transition CanStop - CanStart does also leave a potential BusOff state */
      pFlexCANLocal->control1 |= kFlexCAN_BOFF_REC; /* SBSW_CAN_LL01 */

      retVal = kCanRequested;
    }
  }

  return (retVal);
}
/* CODE CATEGORY 4 END */
#endif


#if defined( C_ENABLE_CAN_RAM_CHECK_EXTENDED ) && defined( C_ENABLE_CLKSRC_SELECTION ) /* COV_CAN_RAMCHECK_EXTENDED_CLKSRC_AVAILABILITY */
/* CODE CATEGORY 4 START */
/****************************************************************************
| NAME:             CanLL_CheckClockSource
****************************************************************************/
/*
|<DataModelStart>| CanLL_CheckClockSource
Relation_Context:
# from CanLL_InitBeginIsRegisterCorrupt #
RamCheck
Relation:
HardwareLoopCheck
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
 *
 *
 *
 *
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_CheckClockSource(CAN_HW_CHANNEL_CANTYPE_ONLY)
{
  vuint32 control1OldVal;
  Can_ReturnType loopResult = CAN_OK; /* PRQA S 2981,2982 */ /* MD_MSR_RetVal */
  vuint8 clkSrcCheckFailed = kCanFalse;
  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);
  
  /* #10 Enter DISABLE mode of FlexCAN */
  CAN_WRITE_PROTECTED_REG_SET(pFlexCANLocal->canmcr, kFlexCAN_MDIS); /* disable FlexCAN module before clock selection */ /* SBSW_CAN_LL01 */
  if ((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_LPM_ACK) != kFlexCAN_LPM_ACK) /* COV_CAN_HARDWARE_PROCESSING_TIME */ /* SBSW_CAN_LL01 */
  {
    CanLL_ApplCanTimerStart(kCanLoopEnterDisableModeInit); /* start hw loop timer */ /* SBSW_CAN_LL08 */
    do
    { /* wait for FlexCAN is disabled */
      loopResult = CanLL_ApplCanTimerLoop(kCanLoopEnterDisableModeInit);
    } while(((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_LPM_ACK) != kFlexCAN_LPM_ACK) && (loopResult == CAN_OK)); /* COV_CAN_TIMEOUT_DURATION */ /* SBSW_CAN_LL01 */ /* PRQA S 2995,0303 */ /* MD_Can_ConstValue */ /* MD_Can_HwAccess */
    CanLL_ApplCanTimerEnd(kCanLoopEnterDisableModeInit);  /* stop hw loop timer */ /* SBSW_CAN_LL08 */
  }
      
  /* #20 Save configured value of control1 register */
  control1OldVal = CAN_READ_PROTECTED_REG_32BIT(pFlexCANLocal->control1); /* SBSW_CAN_LL01 */
      
  /* #30 Perform check of Clock Source */
  CAN_WRITE_PROTECTED_REG_SET_32BIT(pFlexCANLocal->control1, kFlexCAN_CLK_SRC);  /* SBSW_CAN_LL01 */
  if((CAN_READ_PROTECTED_REG_32BIT(pFlexCANLocal->control1) & kFlexCAN_CLK_SRC) != kFlexCAN_CLK_SRC) /* COV_CAN_RAM_CHECK_NO_STIMULATION */ /* SBSW_CAN_LL01 */
  {
    clkSrcCheckFailed = kCanTrue;
  }

  CAN_WRITE_PROTECTED_REG_RESET_32BIT(pFlexCANLocal->control1, kFlexCAN_CLK_SRC); /* SBSW_CAN_LL01 */
  if((CAN_READ_PROTECTED_REG_32BIT(pFlexCANLocal->control1) & (kFlexCAN_CLK_SRC)) != 0x00u) /* COV_CAN_RAM_CHECK_NO_STIMULATION */ /* SBSW_CAN_LL01 */
  {
    clkSrcCheckFailed = kCanTrue;
  }
  
  /* #40 Reset FlexCAN clock source to configured value */
  if((control1OldVal & kFlexCAN_CLK_SRC) != 0u) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  {
    CAN_WRITE_PROTECTED_REG_SET_32BIT(pFlexCANLocal->control1, kFlexCAN_CLK_SRC); /* SBSW_CAN_LL01 */ /* SBSW_CAN_LL01 */
  }
  else
  {
    CAN_WRITE_PROTECTED_REG_RESET_32BIT(pFlexCANLocal->control1, kFlexCAN_CLK_SRC); /* SBSW_CAN_LL01 */
  }
  
  /* #50 Leave DISABLE mode of FlexCAN */
  CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_MDIS); /* clear MDIS bit */ /* SBSW_CAN_LL01 */
  if ((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_LPM_ACK) == kFlexCAN_LPM_ACK) /* COV_CAN_HARDWARE_PROCESSING_TIME */ /* SBSW_CAN_LL01 */
  {
    CanLL_ApplCanTimerStart(kCanLoopLeaveDisableModeInit); /* start hw loop timer */ /* SBSW_CAN_LL08 */
    do
    { /* wait for FlexCAN is enabled */
      loopResult = CanLL_ApplCanTimerLoop(kCanLoopLeaveDisableModeInit);
    } while(((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_LPM_ACK) == kFlexCAN_LPM_ACK) && (loopResult == CAN_OK)); /* COV_CAN_TIMEOUT_DURATION */ /* SBSW_CAN_LL01 */ /* PRQA S 2995,0303 */ /* MD_Can_ConstValue */ /* MD_Can_HwAccess */
    CanLL_ApplCanTimerEnd(kCanLoopLeaveDisableModeInit);  /* stop hw loop timer */ /* SBSW_CAN_LL08 */
  }
  
  return clkSrcCheckFailed;
}
/* CODE CATEGORY 4 END */
#endif

#if defined( C_ENABLE_CAN_RXTX_INTERRUPT )
/* CODE CATEGORY 1 START */
/****************************************************************************
| NAME:             CanLL_ComputeMailboxInterrupt
****************************************************************************/
/*
|<DataModelStart>| CanLL_ComputeMailboxInterrupt
Relation_Context:
# from CanLL_CanMailboxInterrupt #
TxPolling,RxPolling,IndividualPolling,UseNestedCANInterrupts,
Relation:
OneChOpt
DevErrorDetect,CanFdSupport
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
 *
 *
*/
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanLL_ComputeMailboxInterrupt(CAN_HW_CHANNEL_CANTYPE_FIRST vuint32 iFlags, vuint32 iMask, CanObjectHandle startIndex) /* COV_CAN_MAILBOX_INT_INDIVPOLLING */
{
  vuint32 activeInterrupts;
  CanObjectHandle index;
  
  activeInterrupts = iFlags & iMask;
  index = startIndex;
  /* #10 For all active pending interrupts */
  while(activeInterrupts != 0u) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  {
    /* #20 Compute index of active interrupt */
    while((activeInterrupts & (vuint32)0xFFu) == 0u) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    {
      activeInterrupts >>= 8;
      index += (CanObjectHandle)8u;
    }    
    if((activeInterrupts & (vuint32)0x0Fu) == 0u) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    {
      activeInterrupts >>= 4;
      index += (CanObjectHandle)4u;
    }        
    while((activeInterrupts & (vuint32)0x01u) == 0u) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    {
      activeInterrupts >>= 1;
      index++;
    }

    /* #30 Call computation of interrupt type */
# if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
#  if defined ( C_ENABLE_CAN_FD_FULL )
    if ( Can_GetSizeOfFDMailboxMapping() > (Can_GetFDHwChannelIndirectionOfControllerConfig((canHwChannel)) + index) ) /* COV_CAN_GENDATA_FAILURE */
#  endif
# endif
    {
      CanLL_ComputeInterruptType(CAN_HW_CHANNEL_CANPARA_FIRST index);
    }

    index++;
    activeInterrupts = (iFlags & iMask) >> (index-startIndex);
  }
}
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
/****************************************************************************
| NAME:             CanLL_ComputeInterruptType
****************************************************************************/
/*
|<DataModelStart>| CanLL_ComputeMailboxInterrupt
Relation_Context:
# from CanLL_ComputeMailboxInterrupt #
TxPolling,RxPolling,IndividualPolling,UseNestedCANInterrupts,
Relation:
OneChOpt
RxFullCANSupport,RxPolling,IndividualPolling,DevErrorDetect
CanFdSupport,RxBasicCANSupport,RxPolling,IndividualPolling,DevErrorDetect
TxPolling,IndividualPolling,TxFullCANSupport,DevErrorDetect,MultiplexedTx
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
 *
 *
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_ComputeInterruptType(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle index) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
{

  {
    CanObjectHandle mailboxHandle = Can_GetHwToMbHandle(canHwChannel, index); /* PRQA S 2981,2982 */ /* MD_MSR_RetVal */

#  if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
#   if !defined( C_ENABLE_RX_FULLCAN_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING )
    /* #10 Check if pending interrupt is caused due to a FullCAN reception */
    if((index >= CAN_HL_HW_RX_FULL_STARTINDEX(canHwChannel)) && (index < CAN_HL_HW_RX_FULL_STOPINDEX(canHwChannel))) /* COV_CAN_MAILBOX_ORDER */
    {
#    if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
      if ((mailboxHandle >= CAN_HL_MB_RX_FULL_STARTINDEX(canHwChannel)) && (mailboxHandle < CAN_HL_MB_RX_FULL_STOPINDEX(canHwChannel))) /* COV_CAN_GENDATA_FAILURE */
#    endif
      {
        CanHL_FullCanMsgReceived(CAN_HW_CHANNEL_CANPARA_FIRST mailboxHandle, index);
      }
    }
#   endif
#  endif

#  if defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
#   if defined( C_ENABLE_RX_BASICCAN_OBJECTS )
#    if !defined( C_ENABLE_RX_BASICCAN_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING )
    /* #20 Check if pending interrupt is caused due to a BasicCAN reception */
    if((index >= CAN_HL_HW_RX_BASIC_STARTINDEX(canHwChannel)) && (index < CAN_HL_HW_RX_BASIC_STOPINDEX(canHwChannel))) /* COV_CAN_MAILBOX_ORDER */
    {
#     if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
      if((mailboxHandle >= CAN_HL_MB_RX_BASIC_STARTINDEX(canHwChannel)) && (mailboxHandle < CAN_HL_MB_RX_BASIC_STOPINDEX(canHwChannel))) /* COV_CAN_GENDATA_FAILURE */
#     endif
      {
        CanHL_BasicCanMsgReceived(CAN_HW_CHANNEL_CANPARA_FIRST mailboxHandle, index);
      }
    }
#    endif
#   endif
#  endif

#  if !defined( C_ENABLE_TX_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING )
    /* #30 Check if pending interrupt is caused due to a successful transmission */
    if((index >= CAN_HL_HW_TX_STARTINDEX(canHwChannel)) && (index < CAN_HL_HW_TX_STOPINDEX(canHwChannel))) /* COV_CAN_MAILBOX_ORDER */
    {
#   if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
      if (
#    if defined ( C_ENABLE_TX_FULLCAN_OBJECTS )
          ((mailboxHandle >= CAN_HL_MB_TX_FULL_STARTINDEX(canHwChannel)) && (mailboxHandle < CAN_HL_MB_TX_FULL_STOPINDEX(canHwChannel))) ||
#    endif
          ((mailboxHandle >= CAN_HL_MB_TX_BASIC_STARTINDEX(canHwChannel)) && (mailboxHandle < CAN_HL_MB_TX_BASIC_STOPINDEX(canHwChannel)))
      ) /* COV_CAN_GENDATA_FAILURE */
#   endif
      {
        CanObjectHandle mailboxElement = 0u;
#   if defined(C_ENABLE_MULTIPLEXED_TRANSMISSION)
        if ((mailboxHandle >= CAN_HL_MB_TX_BASIC_STARTINDEX(canHwChannel)) && (mailboxHandle < CAN_HL_MB_TX_BASIC_STOPINDEX(canHwChannel))) /* COV_CAN_MAILBOX_ORDER */
        {
          mailboxElement = index - Can_GetMailboxHwHandle(mailboxHandle);
        }
#    if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
        if (mailboxElement < Can_GetMailboxSize(mailboxHandle)) /* COV_CAN_GENDATA_FAILURE */
#    endif
#   endif
        {
          CanHL_TxConfirmation(CAN_HW_CHANNEL_CANPARA_FIRST mailboxHandle, mailboxElement, index);
        }
      }
    }
#  endif
  }
}
/* CODE CATEGORY 1 END */

/****************************************************************************
| NAME:             CanLL_CanMailboxInterrupt
****************************************************************************/
/*
|<DataModelStart>| CanLL_CanMailboxInterrupt
Relation_Context:
# from CanMailboxInterrupt, CanInterrupt #
TxPolling,RxPolling,IndividualPolling,UseNestedCANInterrupts
Relation:
OneChOpt
CanFdSupport,RxPolling,IndividualPolling
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
*/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_CanMailboxInterrupt( CAN_HW_CHANNEL_CANTYPE_ONLY ) /* COV_CAN_MAILBOX_INT_INDIVPOLLING */
{
  vuint32 iflag; /* avoid IAR compiler warning */
  vuint32 imask; /* avoid IAR compiler warning */

  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);
#if defined( C_ENABLE_RX_BASICCAN_OBJECTS ) 
# if !defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
#  if !defined( C_ENABLE_RX_BASICCAN_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING ) /* COV_CAN_CDK_DETECTION */
  /* #10 Check if pending interrupt is caused due to a BasicCAN reception (RxFifo) */

#   if defined(C_ENABLE_INDIVIDUAL_POLLING)
  /* additional check is necessary to ensure only objects configured for interrupt are processed here */
  if (!Can_IsMailboxIndivPolling(Can_GetHwToMbHandle(canHwChannel, 0u))) /* COV_CAN_HWOBJINDIVPOLLING */ /* PRQA S 2985 */ /* MD_Can_ConstValue */
#   endif
  {
    vuint8 fifoLoopCnt;
    fifoLoopCnt = 0u;
    while(((pFlexCANLocal->iflag1 & kRxFIFO_NEWMSG) != 0u) && (fifoLoopCnt < C_FLEXCAN_RXFIFO_MAXLOOP)) /* COV_CAN_RXFIFO_HANDLING */
    {
      fifoLoopCnt++;
      CanHL_BasicCanMsgReceived(CAN_HW_CHANNEL_CANPARA_FIRST Can_GetHwToMbHandle(canHwChannel, 0u), 0u); /* PRQA S 2985 */ /* MD_Can_ConstValue */
    }
  }
#  endif
# endif
#endif

  /* #20 Call mailbox interrupt computation function for Mailboxes 0 to 31 */
  iflag = pFlexCANLocal->iflag1;
  imask = pFlexCANLocal->imask1;
  CanLL_ComputeMailboxInterrupt(CAN_HW_CHANNEL_CANPARA_FIRST iflag, imask, 0u);
# if defined ( C_ENABLE_MB32TO63 ) /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
#  if defined ( C_ENABLE_ASYM_MAILBOXES ) /* COV_CAN_FLEXCAN3_DERIVATIVE_ASYM_MAILBOXES */
  if (NUMBER_OF_MAX_MAILBOXES(canHwChannel) > 32u) /* PRQA S 2741,2742 */ /* MD_Can_ConstValue */ /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
#  endif
  {
    /* #30 Call mailbox interrupt computation function for Mailboxes 32 to 63 */
    iflag = pFlexCANLocal->iflag2;
    imask = pFlexCANLocal->imask2;
    CanLL_ComputeMailboxInterrupt(CAN_HW_CHANNEL_CANPARA_FIRST iflag, imask, 32u);
  }
# endif
# if defined ( C_ENABLE_MB64TO95 ) /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
#  if defined ( C_ENABLE_ASYM_MAILBOXES ) /* COV_CAN_FLEXCAN3_DERIVATIVE_ASYM_MAILBOXES */
  if (NUMBER_OF_MAX_MAILBOXES(canHwChannel) > 64u) /* PRQA S 2741,2742 */ /* MD_Can_ConstValue */ /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
#  endif
  {
    /* #40 Call mailbox interrupt computation function for Mailboxes 64 to 95 */
    iflag = pFlexCANLocal->iflag3;
    imask = pFlexCANLocal->imask3;
    CanLL_ComputeMailboxInterrupt(CAN_HW_CHANNEL_CANPARA_FIRST iflag, imask, 64u);
  }
# endif
# if defined ( C_ENABLE_MB96TO127 ) /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
  /* #50 Call mailbox interrupt computation function for Mailboxes 96 to 127 */
  iflag = pFlexCANLocal->iflag4;
  imask = pFlexCANLocal->imask4;
  CanLL_ComputeMailboxInterrupt(CAN_HW_CHANNEL_CANPARA_FIRST iflag, imask, 96u);
# endif
}
/* CODE CATEGORY 1 END */
#endif /* C_ENABLE_CAN_RXTX_INTERRUPT */

/**********************************************************************************************************************
*  CanLL_ClearPendingInterrupt
*********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_ClearPendingInterrupt
Relation_Context:
# from CanLL_TxConfBegin #
Relation:
TxBasicAmount
TxFullAmount
RxFullAmount
RxBasicAmount
ChannelAmount
OneChOpt
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
 *
 *
 *
*/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_ClearPendingInterrupt( tFlexCANPtr pFlexCANLocal, CanObjectHandle hwObjHandle )
{
  if (hwObjHandle < 32u) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  { /* #10 Clear pending interrupt for mailbox 0 to 31 */
    pFlexCANLocal->iflag1 = CanBitMask(hwObjHandle); /* clear pending interrupt flag  */ /* SBSW_CAN_LL01 */ /* PRQA S 2985 */ /* MD_Can_ConstValue */
  }
#if defined ( C_ENABLE_MB32TO63 ) /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
  else
  { /* #20 Clear pending interrupt for mailbox 32 to 63 */
    if (hwObjHandle < 64u) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    {
      pFlexCANLocal->iflag2 = CanBitMask(hwObjHandle); /* clear pending interrupt flag  */ /* SBSW_CAN_LL01 */ /* PRQA S 2985 */ /* MD_Can_ConstValue */
    }
# if defined ( C_ENABLE_MB64TO95 ) /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
    else
    { /* #30 Clear pending interrupt for mailbox 64 to 95 */
      if (hwObjHandle < 96u) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
      {
        pFlexCANLocal->iflag3 = CanBitMask(hwObjHandle); /* clear pending interrupt flag  */ /* SBSW_CAN_LL01 */ /* PRQA S 2985 */ /* MD_Can_ConstValue */
      }
#  if defined ( C_ENABLE_MB96TO127 ) /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
      else
      { /* #40 Clear pending interrupt for mailbox 96 to 128 */
        pFlexCANLocal->iflag4 = CanBitMask(hwObjHandle); /* clear pending interrupt flag  */ /* SBSW_CAN_LL01 */ /* PRQA S 2985 */ /* MD_Can_ConstValue */
      }
#  endif
    }
# endif
  }
#endif
}
/* CODE CATEGORY 1 END */

#if defined (C_ENABLE_TX_POLLING) || ( defined (C_ENABLE_RX_FULLCAN_POLLING) && defined (C_ENABLE_RX_FULLCAN_OBJECTS) ) || ( (defined (C_ENABLE_RX_BASICCAN_POLLING) && defined (C_ENABLE_RX_BASICCAN_OBJECTS)) && defined (C_ENABLE_CLASSIC_MAILBOX_LAYOUT) )
/**********************************************************************************************************************
*  CanLL_GetInterruptFlag
*********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_GetInterruptFlag
Relation_Context:
# from CanLL_RxFullProcessPendings #
RxFullCANSupport, RxPolling
# from CanLL_RxBasicProcessPendings #
RxBasicCANSupport, RxPolling
# from CanLL_TxProcessPendings #
TxFullCANSupport, TxPolling
Relation:
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
 *
 *
 *
*/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint32, STATIC_CODE) CanLL_GetInterruptFlag( tFlexCANPtr pFlexCANLocal, CanObjectHandle hwObjHandle ) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */ /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */
{
  vuint32 iFlags = 0u;

  if (hwObjHandle < 32u) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  { /* #10 Get iflag for mailboxes 0 to 31 */
    iFlags = pFlexCANLocal->iflag1;
  }
#if defined ( C_ENABLE_MB32TO63 ) /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
  else
  {
    if (hwObjHandle < 64u) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    { /* #20 Get iflag for mailboxes 32 to 63 */
      iFlags = pFlexCANLocal->iflag2;
    }
# if defined ( C_ENABLE_MB64TO95 ) /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
    else
    {
      if (hwObjHandle < 96u) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
      { /* #30 Get iflag for mailboxes 64 to 95 */
        iFlags = pFlexCANLocal->iflag3;
      }
#  if defined ( C_ENABLE_MB96TO127 ) /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
      else
      { /* #40 Get iflag for mailboxes 96 to 128 */
        iFlags = pFlexCANLocal->iflag4;
      }
#  endif
    }
# endif
  }
#endif

  return (iFlags);
}
/* CODE CATEGORY 1 END */
#endif

#if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
/****************************************************************************
| NAME:             CanLL_CheckMaxHwMailboxHandle
****************************************************************************/
/*
|<DataModelStart>| CanLL_CheckMaxHwMailboxHandle
Relation_Context:
# from CanLL_InitMailboxTx #
TxFullCANSupport,DevErrorDetect
# from CanLL_InitMailboxRxFullCan #
RxFullCANSupport,DevErrorDetect
# from CanLL_InitMailboxRxBasicCan #
RxBasicCANSupport,DevErrorDetect
Relation:
CanFdSupport
ChannelAmount
TxBasicAmount
TxFullAmount
RxFullAmount
RxBasicAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
*/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_CheckMaxHwMailboxHandle(CanChannelHandle hwChannel, Can_HwHandleType hwObjHandle)
{
  vuint8 retVal = kCanOk;

  /* #10 Check for maximum value of HW mailbox handle */
# if defined ( C_ENABLE_CAN_FD_FULL )
  if ( Can_GetSizeOfFDMailboxMapping() <= (Can_GetFDHwChannelIndirectionOfControllerConfig((hwChannel)) + hwObjHandle) ) /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL04 */
  {
    retVal = kCanFalse;
  }
  CAN_DUMMY_STATEMENT(hwChannel); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# else
#  if defined ( C_ENABLE_MB96TO127 ) /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
  if ( hwObjHandle >= 128u ) /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL04 */
#  elif defined ( C_ENABLE_MB64TO95 ) /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
#   if defined ( C_ENABLE_ASYM_MAILBOXES ) /* COV_CAN_FLEXCAN3_DERIVATIVE_ASYM_MAILBOXES */
  if (hwObjHandle >= NUMBER_OF_MAX_MAILBOXES(hwChannel)) /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL04 */
#   else
  if ( hwObjHandle >= 96u ) /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL04 */
#   endif
#  elif defined ( C_ENABLE_MB32TO63 ) /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
#   if defined ( C_ENABLE_ASYM_MAILBOXES ) /* COV_CAN_FLEXCAN3_DERIVATIVE_ASYM_MAILBOXES */
  if (hwObjHandle >= NUMBER_OF_MAX_MAILBOXES(hwChannel)) /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL04 */
#   else
  if ( hwObjHandle >= 64u ) /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL04 */
#   endif
#  else
#   if defined ( C_ENABLE_ASYM_MAILBOXES ) /* COV_CAN_FLEXCAN3_DERIVATIVE_ASYM_MAILBOXES */
  if (hwObjHandle >= NUMBER_OF_MAX_MAILBOXES(hwChannel)) /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL04 */
#   else
  if ( hwObjHandle >= 32u ) /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL04 */
#   endif
#  endif
  {
    retVal = kCanFalse;
  }
#  if !defined ( C_ENABLE_ASYM_MAILBOXES ) /* COV_CAN_FLEXCAN3_DERIVATIVE_ASYM_MAILBOXES */
  CAN_DUMMY_STATEMENT(hwChannel); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#  endif
# endif

  return ( retVal );
}
/* CODE CATEGORY 4 END */

# if defined( C_ENABLE_CAN_RXTX_INTERRUPT )   || \
     defined( C_ENABLE_CAN_BUSOFF_INTERRUPT ) /* COV_CAN_INTERRUPT_SUPPORT */ 
/****************************************************************************
| NAME:             CanLL_CheckSizeOfHwChannelData
****************************************************************************/
/*
|<DataModelStart>| CanLL_CheckSizeOfHwChannelData
Relation_Context:
# from CanInterrupt #
TxPolling,RxPolling,IndividualPolling,StatusPolling,WakeupPolling,UseNestedCANInterrupts
# from CanMailboxInterrupt #
TxPolling,RxPolling,IndividualPolling,UseNestedCANInterrupts
# from CanBusoffInterrupt #
StatusPolling,UseNestedCANInterrupts
Relation:
OneChOpt
DevErrorDetect,TxPolling,RxPolling,IndividualPolling
DevErrorDetect,StatusPolling,WakeupPolling
DevErrorDetect,StatusPolling
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
 *
*/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_CheckSizeOfHwChannelData(CanChannelHandle hwChannel) /* COV_CAN_MAILBOX_INT_INDIVPOLLING */
{
  vuint8 retVal = kCanOk;

  /* #10 Check size of canHwChannel against size of HwChannelData */
  if ( hwChannel >= kCanNumberOfChannels ) /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL07 */
  {
    retVal = kCanFailed;
  }
  else
  {
    /* #20 Check if controller is initialized */
    if (!(CanHL_IsControllerInit(hwChannel))) /* COV_CAN_CONTROLLER_INIT_STATE  */
    {
      retVal = kCanFailed;
    }
  }

  return ( retVal );
}
/* CODE CATEGORY 4 END */
# endif
#endif

#if defined(C_ENABLE_TX_POLLING) /* COV_CAN_TX_POLLING TX */
/****************************************************************************
| NAME:             CanHL_TxConfirmationPolling
****************************************************************************/
/*
|<DataModelStart>| CanHL_TxConfirmationPolling
Relation_Context:
# from CanLL_TxProcessPendings #
TxPolling
Relation:
OneChOpt
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_TxConfirmationPolling( CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle mailboxHandle, CanObjectHandle mailboxElement, CanObjectHandle hwObjHandle )
{
  /* #10 Lock CAN controller interrupts. (avoid nested call of confirmation (individual polling) and CancelTx interrupt confirmation out of Can interrupt like TP) */
  Can_DisableControllerInterrupts((uint8)channel);
  /* #20 call CanHL_TxConfirmation() for handling */
  CanHL_TxConfirmation(CAN_HW_CHANNEL_CANPARA_FIRST mailboxHandle, mailboxElement, hwObjHandle);
  Can_EnableControllerInterrupts((uint8)channel);
}
#endif

/****************************************************************************
| NAME:             CanHL_TxConfirmation
****************************************************************************/
/*
|<DataModelStart>| CanHL_TxConfirmation
Relation_Context:
# from CanHL_TxConfirmationPolling #
# from Tx Interrupt #
TxPolling, IndividualPolling
Relation:
TxHwFifo, GenericConfirmation
DevErrorDetect, TxPolling, OneChOpt
TransmitCancellationAPI
GenericConfirmation, IfTxBuffer
HwCancelTx
GenericConfirmation, MirrorMode
HwCancelTx, TransmitCancellationAPI, GenericConfirmation
ChannelAmount
TxBasicAmount
TxFullAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
 *
 *
 *
 */
/* explicite not inline (big code + multiple calls) */
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanHL_TxConfirmation( CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle mailboxHandle, CanObjectHandle mailboxElement, CanObjectHandle hwObjHandle )
{
  /* \trace SPEC-1574 */
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  tCanTxConfirmationParaStruct txConfPara;
#if defined(CAN_ENABLE_GENERIC_CONFIRMATION_API2)
  tCanTxConfInfoStruct txConfInfoStruct;
#endif
  CanHookBegin_CanHL_TxConfirmation();
  errorId = CAN_E_NO_ERROR; /* PRQA S 2982 */ /* MD_MSR_RetVal */
  txConfPara.mailboxHandle = mailboxHandle;
  txConfPara.mailboxElement = mailboxElement; /* PRQA S 2983 */ /* MD_MSR_DummyStmt */
  txConfPara.hwObjHandle = hwObjHandle; /* PRQA S 2983 */ /* MD_MSR_DummyStmt */
#if defined(CAN_ENABLE_GENERIC_CONFIRMATION_API2)
  txConfPara.txStructConf = &txConfInfoStruct;
#endif
  /* ----- Development Error Checks ------------------------------------- */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
# if !defined(C_ENABLE_TX_POLLING) /* COV_CAN_TX_POLLING */
  /* #10 Check if parameter controller and hwObjHandle is valid (only for Interrupt system, polling do this by caller) */
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
  if ( 
#  if defined(C_ENABLE_TX_FULLCAN_OBJECTS)
       ((txConfPara.mailboxHandle < Can_GetTxFullHandleStart(canHwChannel)) || (txConfPara.mailboxHandle >= Can_GetTxFullHandleStop(canHwChannel))) &&  /* PRQA S 2995,2996 */ /* MD_Can_ConstValue */ /* COV_CAN_GENDATA_FAILURE */
#  endif
       ((txConfPara.mailboxHandle < Can_GetTxBasicHandleStart(canHwChannel)) || (txConfPara.mailboxHandle >= Can_GetTxBasicHandleStop(canHwChannel))) ) /* PRQA S 2991,2992,2995,2996 */ /* MD_Can_ConstValue */ /* COV_CAN_GENDATA_FAILURE */
  {
    errorId = CAN_E_PARAM_HANDLE;
  }
  else
# endif
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    PduIdType tmp_pdu;
#if defined(C_ENABLE_CANCEL_SUPPORT_API)
    uint8_least tmp_state;
#endif
#if defined(CAN_ENABLE_GENERIC_CONFIRMATION_API2)
    Can_ReturnType generic_retval;
#endif
#if (defined(CAN_USE_CRITICALSECTION_OVER_CONFIRMATION) && (CAN_TRANSMIT_BUFFER == STD_ON)) || defined(CAN_ENABLE_GENERIC_CONFIRMATION_API2)
    /* #100 EXCLUSIVE_AREA_3 needed to avoid another can_write while interface send out of queue (first send out of queue avoid inversion) or call GenericConfirmation2 (data consistency) */
    SchM_Enter_Can_CAN_EXCLUSIVE_AREA_3();
#endif
    txConfPara.activeSendObject = CanHL_GetActiveSendObject(txConfPara.mailboxHandle, txConfPara.mailboxElement); /* PRQA S 2880 */ /*  MD_MSR_Unreachable */
    {
      /* #120 Pre Release HW transmit object (LL) */
      CanLL_TxConfBegin(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &txConfPara); /* SBSW_CAN_HL45 */
      /* #130 Remember PDU for confirmation parameter */
      tmp_pdu   = Can_GetActiveSendPdu(txConfPara.activeSendObject);
#if defined(C_ENABLE_CANCEL_SUPPORT_API)
      /* #140 Remember SEND STATE which may be modified due to new transmit call in indication */
      tmp_state = (uint8_least)Can_GetActiveSendState(txConfPara.activeSendObject);
#endif
#if defined(C_ENABLE_CANCEL_TX_IN_HW) /* cancel interrupt occur */
      /* #150 If the message was successfully transmitted (without cancellation) (LL): */
      if (CanLL_TxConfIsMsgTransmitted(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &txConfPara) == kCanTrue) /* SBSW_CAN_HL45 */ /* COV_CAN_HW_TRANSMIT_CANCELLATION */
#endif
      { /* #200 Set send state to free to allow next TX out of confirmation or direct (reload queue) */
        /* #210 Notify the application by call Appl_GenericConfirmation() and CanIf_TxConfirmation() */
        /*      - Appl_GenericConfirmation() if configured and mirror mode is active
                and afterwards depend of return value
                - CanIf_TxConfirmation() if generic confirmation return OK, or no generic is used, and TX is not cancelled */
#if defined(CAN_ENABLE_GENERIC_CONFIRMATION_API1)
        Can_SetActiveSendState(txConfPara.activeSendObject, kCanBufferFree); /* SBSW_CAN_HL04 */
        if (Appl_GenericConfirmation( tmp_pdu ) == CAN_OK)
#elif defined(CAN_ENABLE_GENERIC_CONFIRMATION_API2)
# if defined(C_ENABLE_MIRROR_MODE)
        if (Can_GetMirrorModeState(channel) == CDDMIRROR_INACTIVE)
        { /* MirrorMode is inactive so call the following CanIf_TxConfirmation() */
          Can_SetActiveSendState(txConfPara.activeSendObject, kCanBufferFree); /* SBSW_CAN_HL04 */
          generic_retval = CAN_OK;
        }
        else
# endif
        { /* #230 For generic confirmation with API2 copy PDU data as parameter for Appl_GenericConfirmation() */
          { /* #250 in case of none FIFO get data out of CAN cell buffer (LL txStructConf) */
            Can_PduType canPdu;
            /* #260 get confirmation data out of hardware */
            CanLL_TxConfSetTxConfStruct(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &txConfPara); /* SBSW_CAN_HL45 */
            CanHL_SetCanPduInfo(&canPdu, &txConfPara); /* SBSW_CAN_HL32 */ /* SBSW_CAN_HL45 */
            canPdu.swPduHandle = tmp_pdu;
            Can_SetActiveSendState(txConfPara.activeSendObject, kCanBufferFree); /* SBSW_CAN_HL04 */ /* release after copy data to avoid data inconsistency */
            /* call Appl_GenericConfirmation() and in case of CAN_OK also the following CanIf_TxConfirmation() */
            generic_retval = Appl_GenericConfirmation( (uint8)channel, &canPdu ); /* PRQA S 0312 */ /* MD_Can_NoneVolatilePointerCast */ /* SBSW_CAN_HL32 */
          }
        }
        /* #300 Appl_GenericConfirmation() decide to call Indication */
        if (generic_retval == CAN_OK)
#else /* no generic confirmation */
        Can_SetActiveSendState(txConfPara.activeSendObject, kCanBufferFree); /* SBSW_CAN_HL04 */
#endif
        {
#if defined(C_ENABLE_CANCEL_SUPPORT_API)
          /* #310 If TX is SW cancelled call CanIf_CancelTxNotification() */
          if (tmp_state == kCanBufferCancelSw) /* COV_CAN_CANCEL_SW_STIMULATION */
          {
            CanIf_CancelTxNotification(tmp_pdu, FALSE);
          }
          else
#endif  /* #320 otherwise call CanIf_TxConfirmation() */
          {
            CanIf_TxConfirmation(tmp_pdu); /* \trace SPEC-1726, SPEC-1571 */
          }
        }
#if (defined(CAN_ENABLE_GENERIC_CONFIRMATION_API1) || defined(CAN_ENABLE_GENERIC_CONFIRMATION_API2)) && (CAN_TRANSMIT_BUFFER == STD_ON)
        /* #350 otherwise no CanIf_TxConfirmation() will be called so call CanIf_CancelTxNotification() just to notify IF to restart sending out of Queue */
        else
        {
# if defined(C_ENABLE_CANCEL_SUPPORT_API)
          CanIf_CancelTxNotification( tmp_pdu, FALSE );
# else
#  error "When using Generic Confirmation and Transmit buffer (If) the Cancel-support-api (if) has to be activated"
# endif
        }
#endif
      }
#if defined(C_ENABLE_CANCEL_TX_IN_HW)
      /* #400 otherwise mailbox is cancelled successful */
      else
      {
#  if defined(C_ENABLE_CANCEL_SUPPORT_API)
        if (tmp_state == kCanBufferCancelSw) /* COV_CAN_CANCEL_SW_STIMULATION */
        { /* #410 free active PDU to allow next TX out of confirmation or direct (reload queue) */
          Can_SetActiveSendState(txConfPara.activeSendObject, kCanBufferFree); /* SBSW_CAN_HL04 */
          /* #420 SW cancellation: just call CanIf_CancelTxNotification() (no interrupt lock used here! - worst case can_write came in between and a unnecessary cancellation appear) */
          CanIf_CancelTxNotification( tmp_pdu, TRUE );
        }
        else
#  endif
        {
#  if defined(C_ENABLE_CANCEL_IN_HW) /* COV_CAN_CANCEL_IN_HW TX */
          /* always CancelSW when only FullCAN TX is cancelled so never called */
#   if (CAN_DEV_ERROR_DETECT == STD_ON)
          /* #440 Check send state is not free now, to secure that ActiveSendPduInfo is already set before used */
          if (Can_GetActiveSendState(txConfPara.activeSendObject) == kCanBufferFree) /* COV_CAN_HARDWARE_FAILURE */
          {
            errorId = CAN_E_PARAM_HANDLE;
          }
          else
#   endif
          { /* #450 EXCLUSIVE_AREA_3 -> no call to upper layer here */
            SchM_Enter_Can_CAN_EXCLUSIVE_AREA_3();
            /* #460 free active PDU to allow next TX out of confirmation or direct (reload queue) */
            Can_SetActiveSendState(txConfPara.activeSendObject, kCanBufferFree);  /* SBSW_CAN_HL04 */          
            /* #470 call CanIf_CancelTxConfirmation() to re trigger queue \trace SPEC-1726, SPEC-1725, SPEC-1684, SPEC-1689 */
            CanIf_CancelTxConfirmation( Can_GetActiveSendSwPduHandle(txConfPara.activeSendObject), &Can_GetActiveSendPduInfo(txConfPara.activeSendObject) ); /* SBSW_CAN_HL25 */
            SchM_Exit_Can_CAN_EXCLUSIVE_AREA_3();
          }
#  endif
        }
      }
#endif
      /* #500 Post release HW transmit object (LL) */
      CanLL_TxConfEnd(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &txConfPara); /* SBSW_CAN_HL45 */
    }

#if (defined(CAN_USE_CRITICALSECTION_OVER_CONFIRMATION) && (CAN_TRANSMIT_BUFFER == STD_ON)) || defined(CAN_ENABLE_GENERIC_CONFIRMATION_API2)
    SchM_Exit_Can_CAN_EXCLUSIVE_AREA_3();
#endif
  }

  /* ----- Development Error Report --------------------------------------- */
#if (CAN_DEV_ERROR_REPORT == STD_ON)
# if !defined(C_ENABLE_TX_POLLING) /* COV_CAN_TX_POLLING */
  if (errorId != CAN_E_NO_ERROR) /* PRQA S 2991,2992,2995,2996 */ /* MD_Can_ConstValue */ /* COV_CAN_HARDWARE_FAILURE */
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_TXCNF_ID, errorId);
  }
# endif
#endif
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CanHookEnd_CanHL_TxConfirmation();
} /* PRQA S 6010,6030,6050,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STCAL,MD_MSR_STMIF */


#if defined(CAN_ENABLE_GENERIC_CONFIRMATION_API2)
/****************************************************************************
| NAME:             CanHL_SetCanPduInfo
****************************************************************************/
/*
|<DataModelStart>| CanHL_SetCanPduInfo
Relation_Context:
# from CanHL_TxConfirmation #
GenericConfirmation
Relation:
IDType
CanFdSupport
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanHL_SetCanPduInfo(Can_PduInfoPtrType_var PduInfo, CanTxConfirmationParaStructPtr txConfPara) /* COV_CAN_GENDATA_TX_NOT_IN_ALL_CONFIG */
{
  /* #10 set data pointer */
  PduInfo->sdu = (Can_SduPtrType) txConfPara->txStructConf->pChipData; /* PRQA S 0312 */ /* MD_Can_NoneVolatilePointerCast */ /* SBSW_CAN_HL46 */
  /* #20 set data length */
  PduInfo->length = CanTxActualDLC(txConfPara->txStructConf); /* SBSW_CAN_HL46 */
  /* #30 set ID */
# if defined(C_ENABLE_EXTENDED_ID)
#  if defined(C_ENABLE_MIXED_ID)
  if ( CanTxActualIdType(txConfPara->txStructConf) == kCanIdTypeStd) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  { /* Mixed ID */
    PduInfo->id = (Can_IdType)CanTxActualStdId(txConfPara->txStructConf); /* PRQA S 4391 */ /* MD_Can_IntegerCast */ /* SBSW_CAN_HL46 */
  }
  else
#  endif  /* pure Extended ID */
  { /* Extended ID */
    PduInfo->id = (Can_IdType)(CanTxActualExtId(txConfPara->txStructConf) | CAN_ID_IDE_MASK); /* SBSW_CAN_HL46 */
  }
# else    /* Standard ID */
  PduInfo->id = CanTxActualStdId(txConfPara->txStructConf); /* SBSW_CAN_HL46 */
# endif
# if defined(C_ENABLE_CAN_FD_USED)
  if ( CanTxActualFdType(txConfPara->txStructConf) == kCanFdTypeFd )
  {
    PduInfo->id |= (Can_IdType)CAN_ID_FD_MASK; /* SBSW_CAN_HL46 */
  }
# endif
  PduInfo->id &= CAN_ID_MASK_IN_GENERIC_CALLOUT; /* SBSW_CAN_HL46 */
}
#endif


#if defined(C_ENABLE_RX_BASICCAN_OBJECTS) /* COV_CAN_MULTIPLE_BASICCAN */
# if defined(C_ENABLE_RX_BASICCAN_POLLING) /* COV_CAN_RX_BASICCAN_POLLING */
/****************************************************************************
| NAME:             CanHL_BasicCanMsgReceivedPolling
****************************************************************************/
/*
|<DataModelStart>| CanHL_BasicCanMsgReceivedPolling
Relation_Context:
# from CanLL_RxBasicProcessPendings #
RxBasicCANSupport
Relation:
OneChOpt
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_BasicCanMsgReceivedPolling( CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxMailboxHandle, CanObjectHandle hwObjHandle )
{
  /* #10 Lock CAN controller interrupts. */
  Can_DisableControllerInterrupts((uint8)channel);
  /* #20 call CanHL_BasicCanMsgReceived() for handling */
  CanHL_BasicCanMsgReceived( CAN_HW_CHANNEL_CANPARA_FIRST rxMailboxHandle, hwObjHandle );
  Can_EnableControllerInterrupts((uint8)channel);
}
#endif

/****************************************************************************
| NAME:             CanHL_BasicCanMsgReceived
****************************************************************************/
/*
|<DataModelStart>| CanHL_BasicCanMsgReceived
Relation_Context:
# from CanHL_BasicCanMsgReceivedPolling #
RxBasicCANSupport
# from Rx Interrupt #
Relation:
DevErrorDetect, RxPolling, OneChOpt
RamCheck
Overrun
IDType
CanFdSupport
DevErrorDetect, RxPolling, IndividualPolling
ChannelAmount
RxBasicAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
 */
/* explicite not inline (big code + multiple calls) */
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanHL_BasicCanMsgReceived( CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxMailboxHandle, CanObjectHandle hwObjHandle )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  tCanRxBasicParaStruct rxBasicPara;
  CanHookBegin_CanHL_BasicCanMsgReceived();
  errorId = CAN_E_NO_ERROR;
  rxBasicPara.mailboxHandle = rxMailboxHandle;
  rxBasicPara.hwObjHandle = hwObjHandle;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON) && !defined(C_ENABLE_RX_BASICCAN_POLLING)
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  /* #10 Check if parameter controller is in expected limit (already checked in polling task - do it only for interrupt) */
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */ /* COV_CAN_GENDATA_FAILURE */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
# endif 
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #25 receive handling begin CanLL_RxBasicMsgReceivedBegin() \trace SPEC-1682, SPEC-1694 */
    if (CanLL_RxBasicMsgReceivedBegin(CAN_CHANNEL_CANPARA_FIRST &rxBasicPara) == kCanOk) /* SBSW_CAN_HL26 */ /* COV_CAN_RxBasicMsgReceivedBegin */
    {
# if defined(C_ENABLE_CAN_RAM_CHECK)
      /* -------------------------- RAM check failed --- */
      if ((Can_GetLogStatus(channel) & CAN_DEACTIVATE_CONTROLLER) != CAN_DEACTIVATE_CONTROLLER) /* COV_CAN_HARDWARE_FAILURE */
# endif
      { /* #30 RAM CHECK pass so continue reception */
# if defined(C_ENABLE_OVERRUN)
        /* -------------------------- Overrun --- */
        if (rxBasicPara.isOverrun == kCanTrue)
        { /* #40 Overrun occur so notify upper layer \trace SPEC-1686 */
#   if (CAN_OVERRUN_NOTIFICATION == CAN_DET)
          Can_CallDetReportError(CAN_RXINDI_ID, CAN_E_DATALOST); /* Call DET direct because Overrun will be notified additional to following DETs */
#   else /* CAN_OVERRUN_NOTIFICATION == CAN_APPL */
          Appl_CanOverrun( (uint8)channel );
#   endif
        }
# endif
        /* \trace SPEC-1346 */
        {
          /* -------------------------- Get DLC and Data Pointer --- */
          /* #60 get ID, DLC and data from HW \trace SPEC-1691, SPEC-1693 */
          rxBasicPara.rxStruct.localDlc = CanRxActualDLC((&(rxBasicPara.rxStruct)));
          /* -------------------------- Get ID  &  reject unwanted ID type --- */
# if defined(C_ENABLE_EXTENDED_ID)
#  if defined(C_ENABLE_MIXED_ID)
          if ( CanRxActualIdType((&(rxBasicPara.rxStruct))) == kCanIdTypeStd) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
          { /* mixed - standard ID */
            rxBasicPara.rxStruct.localId = (Can_IdType)CanRxActualStdId((&(rxBasicPara.rxStruct)));
          }
          else
#  endif 
          { /* mixed or pure - extended ID */
            rxBasicPara.rxStruct.localId = (Can_IdType)(CanRxActualExtId((&(rxBasicPara.rxStruct))) | CAN_ID_IDE_MASK);
          }
          {
# else 
          { /* pure - standard ID */
            rxBasicPara.rxStruct.localId = CanRxActualStdId((&(rxBasicPara.rxStruct)));
# endif
# if defined(C_ENABLE_CAN_FD_USED)
            if ( CanRxActualFdType((&(rxBasicPara.rxStruct))) == kCanFdTypeFd )
            { /* \trace SPEC-60428 */
              rxBasicPara.rxStruct.localId |= (Can_IdType)CAN_ID_FD_MASK;
            }
            /* DLC is not bigger than expected length (8) for CLASSIC CAN msg (additional to HashTag 145) */
            if ((CanRxActualFdType((&(rxBasicPara.rxStruct))) != kCanFdTypeFd) && (rxBasicPara.rxStruct.localDlc > 8u)) /* ESCAN00084263 */ /* COV_CAN_HARDWARE_FAILURE */
            {
              errorId = CAN_E_PARAM_DLC;
            }
            else
# endif
# if (CAN_DEV_ERROR_DETECT == STD_ON)
#  if (!defined(C_ENABLE_RX_BASICCAN_POLLING) || defined(C_ENABLE_INDIVIDUAL_POLLING))
            /* #140 Check HRH is BasicCAN (already checked in polling task - do it only for interrupt) */
            if ( (rxBasicPara.mailboxHandle < Can_GetRxBasicHandleStart(canHwChannel)) ||
                 (rxBasicPara.mailboxHandle >= Can_GetRxBasicHandleStop(canHwChannel)) ) /* PRQA S 2991,2992,2995,2996 */ /* MD_Can_ConstValue */ /* CM_CAN_HL18 */ /* COV_CAN_GENDATA_FAILURE */
            {
              errorId = CAN_E_PARAM_HANDLE;
            } 
            else
#  endif
# endif
            /* #145 DLC is not bigger than expected length from mailbox (MAX over all PDU for this mailbox) */
            if (rxBasicPara.rxStruct.localDlc > CAN_MAX_DATALEN_OBJ(rxBasicPara.mailboxHandle)) /* ESCAN00084263 */ /* COV_CAN_HARDWARE_FAILURE */
            {
              errorId = CAN_E_PARAM_DLC;
            }
            else
            {
              /* -------------------------- Notification --- */
              /* #150 RX queue and notification handling CanHL_RxMsgReceivedNotification() */
              rxBasicPara.rxStruct.localMailboxHandle = rxBasicPara.mailboxHandle;
              errorId = CanHL_RxMsgReceivedNotification(CAN_CHANNEL_CANPARA_FIRST &(rxBasicPara.rxStruct)); /* SBSW_CAN_HL26 */
            }
          }
        }
      }
    }
    /* #160 receive handling end CanHL_RxBasicMsgReceivedEnd() */
    CanLL_RxBasicReleaseObj(CAN_CHANNEL_CANPARA_FIRST &rxBasicPara); /* SBSW_CAN_HL26 */
    CanLL_RxBasicMsgReceivedEnd(CAN_CHANNEL_CANPARA_FIRST &rxBasicPara); /* SBSW_CAN_HL26 */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR) /* PRQA S 2992,2996 */ /* MD_Can_ConstValue */ /* COV_CAN_HARDWARE_FAILURE */
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_RXINDI_ID, errorId); /* PRQA S 2880 */ /*  MD_MSR_Unreachable */
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  CanHookEnd_CanHL_BasicCanMsgReceived();
} /* PRQA S 6010,6030,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STMIF */
#endif /* C_ENABLE_RX_BASICCAN_OBJECTS */

#if defined(C_ENABLE_RX_FULLCAN_OBJECTS)
# if defined(C_ENABLE_RX_FULLCAN_POLLING) /* COV_CAN_RX_FULLCAN_POLLING */
/****************************************************************************
| NAME:             CanHL_FullCanMsgReceivedPolling
****************************************************************************/
/*
|<DataModelStart>| CanHL_FullCanMsgReceivedPolling
Relation_Context:
# from CanLL_RxFullProcessPendings #
RxFullCANSupport, RxPolling
Relation:
OneChOpt
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_FullCanMsgReceivedPolling( CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxMailboxHandle, CanObjectHandle hwObjHandle )
{
  /* #10 Lock CAN controller interrupts. */
  Can_DisableControllerInterrupts((uint8)channel);
  /* #20 call CanHL_FullCanMsgReceived() for handling */
  CanHL_FullCanMsgReceived( CAN_HW_CHANNEL_CANPARA_FIRST rxMailboxHandle, hwObjHandle );
  Can_EnableControllerInterrupts((uint8)channel);
}
# endif

/****************************************************************************
| NAME:             CanHL_FullCanMsgReceived
****************************************************************************/
/*
|<DataModelStart>| CanHL_FullCanMsgReceived
Relation_Context:
# from CanLL_FullCanMsgReceivedPolling #
RxFullCANSupport
# from Rx Interrupt #
Relation:
OneChOpt
DevErrorDetect, RxPolling, OneChOpt
RamCheck
Overrun
IDType
CanFdSupport
DevErrorDetect, RxPolling, IndividualPolling
ChannelAmount
RxFullAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
 */
/* explicite not inline (big code + multiple calls) */
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanHL_FullCanMsgReceived( CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxMailboxHandle, CanObjectHandle hwObjHandle ) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  tCanRxFullParaStruct rxFullPara;
  CanHookBegin_CanHL_FullCanMsgReceived();
  errorId = CAN_E_NO_ERROR;
  rxFullPara.mailboxHandle = rxMailboxHandle;
  rxFullPara.hwObjHandle = hwObjHandle;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
#  if !defined(C_ENABLE_RX_FULLCAN_POLLING) /* COV_CAN_RX_FULLCAN_POLLING */
#   if !defined( C_SINGLE_RECEIVE_CHANNEL )
  /* #10 Check if parameter controller is in expected limit (already checked in polling task - do it only for interrupt) */
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */ /* COV_CAN_GENDATA_FAILURE */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#   endif
#  endif
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #25 receive handling begin CanLL_RxFullMsgReceivedBegin() \trace SPEC-1682, SPEC-1694 */
    if (CanLL_RxFullMsgReceivedBegin(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &rxFullPara) == kCanOk) /* SBSW_CAN_HL27 */ /* COV_CAN_RxFullMsgReceivedBegin */
    {
  /* -------------------------- RAM check failed --- */
# if defined(C_ENABLE_CAN_RAM_CHECK)
      if ((Can_GetLogStatus(channel) & CAN_DEACTIVATE_CONTROLLER) != CAN_DEACTIVATE_CONTROLLER) /* COV_CAN_HARDWARE_FAILURE */
# endif
      { /* #30 RAM CHECK pass so continue reception */
        /* -------------------------- Overrun --- */
# if defined(C_ENABLE_FULLCAN_OVERRUN)
        if (rxFullPara.isOverrun == kCanTrue)
        {
          /* #40 Overrun occur so notify upper layer */
#   if (CAN_OVERRUN_NOTIFICATION == CAN_DET)
          Can_CallDetReportError(CAN_RXINDI_ID, CAN_E_DATALOST); /* \trace SPEC-1686 */ /* Call DET direct because Overrun will be notified additional to following DETs */
#   else /* CAN_OVERRUN_NOTIFICATION == CAN_APPL */
          Appl_CanFullCanOverrun( (uint8)channel );
#   endif
        }
# endif
        {
          /* -------------------------- Get DLC and Data Pointer --- */
          /* #60 get ID, DLC and data from HW \trace SPEC-1691, SPEC-1693 */
          rxFullPara.rxStruct.localDlc = CanRxActualDLC((&(rxFullPara.rxStruct)));
          /* -------------------------- Get ID  &  reject unwanted ID type --- */
# if defined(C_ENABLE_EXTENDED_ID)
#  if defined(C_ENABLE_MIXED_ID)
          if ( CanRxActualIdType((&(rxFullPara.rxStruct))) == kCanIdTypeStd) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
          { /* mixed - standard ID */
            rxFullPara.rxStruct.localId = (Can_IdType)CanRxActualStdId((&(rxFullPara.rxStruct)));
          }
          else
#  endif 
          { /* mixed or pure - extended ID */
            rxFullPara.rxStruct.localId = (Can_IdType)(CanRxActualExtId((&(rxFullPara.rxStruct))) | CAN_ID_IDE_MASK);
          }
# else 
          rxFullPara.rxStruct.localId = CanRxActualStdId((&(rxFullPara.rxStruct)));
# endif
          { /* ID has valid IdType */
# if defined(C_ENABLE_CAN_FD_USED)
            if ( CanRxActualFdType((&(rxFullPara.rxStruct))) == kCanFdTypeFd )
            { /* \trace SPEC-60428 */
              rxFullPara.rxStruct.localId |= (Can_IdType)CAN_ID_FD_MASK;
            }
            /* DLC is not bigger than expected length (8) for CLASSIC CAN msg (additional to HashTag 145) */
            if ((CanRxActualFdType((&(rxFullPara.rxStruct))) != kCanFdTypeFd) && (rxFullPara.rxStruct.localDlc > 8u)) /* ESCAN00084263 */ /* COV_CAN_HARDWARE_FAILURE */
            {
              errorId = CAN_E_PARAM_DLC;
            }
            else
# endif
# if (CAN_DEV_ERROR_DETECT == STD_ON)
#  if (!defined(C_ENABLE_RX_FULLCAN_POLLING) || defined(C_ENABLE_INDIVIDUAL_POLLING)) /* COV_CAN_RX_FULLCAN_POLLING */
            /* #140 Check HRH is FullCAN (already checked in polling task - do it only for interrupt) */
            if ( (rxFullPara.mailboxHandle < Can_GetRxFullHandleStart(canHwChannel)) ||
                 (rxFullPara.mailboxHandle >= Can_GetRxFullHandleStop(canHwChannel)) )  /* PRQA S 2991,2992,2995,2996 */ /* MD_Can_ConstValue */ /* CM_CAN_HL18 */ /* COV_CAN_GENDATA_FAILURE */
            {
              errorId = CAN_E_PARAM_HANDLE;
            }
            else
#  endif
# endif
            /* #145 DLC is not bigger than expected length from mailbox */
            if (rxFullPara.rxStruct.localDlc > CAN_MAX_DATALEN_OBJ(rxFullPara.mailboxHandle)) /* ESCAN00084263 */ /* COV_CAN_HARDWARE_FAILURE */
            {
              errorId = CAN_E_PARAM_DLC;
            }
            else
            {
              /* -------------------------- Notification --- */
              /* #150 RX queue and notification handling CanHL_RxMsgReceivedNotification() */
              rxFullPara.rxStruct.localMailboxHandle = rxFullPara.mailboxHandle;
              errorId = CanHL_RxMsgReceivedNotification(CAN_CHANNEL_CANPARA_FIRST &(rxFullPara.rxStruct)); /* SBSW_CAN_HL27 */
            }
          }
        }
      }
    }
    /* #160 receive handling end CanHL_RxFullMsgReceivedEnd() */
    CanLL_RxFullReleaseObj(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &rxFullPara); /* SBSW_CAN_HL27 */
    CanLL_RxFullMsgReceivedEnd(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &rxFullPara); /* SBSW_CAN_HL27 */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR) /* PRQA S 2992,2996 */ /* MD_Can_ConstValue */ /* COV_CAN_HARDWARE_FAILURE */
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_RXINDI_ID, errorId); /* PRQA S 2880 */ /*  MD_MSR_Unreachable */
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  CanHookEnd_CanHL_FullCanMsgReceived();
} /* PRQA S 6030,6080 */ /* MD_MSR_STCYC,MD_MSR_STMIF */
#endif /* C_ENABLE_RX_FULLCAN_OBJECTS */

/****************************************************************************
| NAME:             CanHL_ErrorHandling
****************************************************************************/
/*
|<DataModelStart>| CanHL_ErrorHandling
Relation_Context:
# from Can_MainFunction_BusOff() #
StatusPolling
# from BusOff Interrupt #
StatusPolling
Relation:
DevErrorDetect, StatusPolling, OneChOpt
Overrun
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
 */
/* explicite not inline (big code + multiple calls) */
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanHL_ErrorHandling( CAN_HW_CHANNEL_CANTYPE_ONLY )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
# if !defined(C_ENABLE_ERROR_POLLING) /* COV_CAN_ERROR_POLLING */
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  /* #10 Check if parameter controller is in expected limit */
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */ /* COV_CAN_GENDATA_FAILURE */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
# endif
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Pre Error handling (LL) */
    CanLL_ErrorHandlingBegin(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_ONLY); /* PRQA S 2987 */ /* MD_Can_EmptyFunction */
    if ( (CanLL_BusOffOccured(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_ONLY) == kCanTrue) && (!Can_IsIsBusOff(channel) /* avoid repeated call */)) /* COV_CAN_BUSOFF_NOT_IN_ALL_CONFIG */
    {
      /* #90 EXCLUSIVE_AREA_6 secure mode changes */
      SchM_Enter_Can_CAN_EXCLUSIVE_AREA_6();
      /* #100 BUSOFF occur -> ECU Manager restart Controller (no ResetBusOffStart/End needed) */
      Can_SetBusOffCounter(channel, 3); /* SBSW_CAN_HL33 */
      Can_SetIsBusOff(channel, TRUE); /* SBSW_CAN_HL08 */
      /* #110 ResetBusOffStart need when BUSOFF handled by Application */
      (void)CanHL_ModeTransition(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST kCanModeResetBusOffStart, kCanContinueBusOffRecovery, kCanSuppressRamCheck);
      /* #115 Controller is in STOP mode after ResetBusOffStart \trace SPEC-1578, SPEC-1664, SPEC-1663 */
      /* #120 Status changed to STOP - no more call of STOP from CAN Interface */
      Can_SetLogStatus(channel, (uint8)((Can_GetLogStatus(channel) & CAN_STATUS_MASK_NOMODE) | CAN_STATUS_STOP)); /* SBSW_CAN_HL02 */
      SchM_Exit_Can_CAN_EXCLUSIVE_AREA_6();
      /* #130 notify higher layer by call CanIf_ControllerBusOff() \trace SPEC-1726, SPEC-1578 */
      CanIf_ControllerBusOff((uint8)Can_GetCanToCanIfChannelMapping(channel));
    }
    /* #200 Post Error handling (LL) */
    CanLL_ErrorHandlingEnd(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_ONLY); /* PRQA S 2987 */ /* MD_Can_EmptyFunction */
  }

  /* ----- Development Error Report --------------------------------------- */
#if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR) /* PRQA S 2992,2996 */ /* MD_Can_ConstValue */ /* COV_CAN_GENDATA_FAILURE */
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_CTRBUSOFF_ID, errorId); /* PRQA S 2880 */ /*  MD_MSR_Unreachable */
  }
#else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
} /* PRQA S 6050 */ /* MD_MSR_STCAL */


#define CAN_STOP_SEC_STATIC_CODE  /*---------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*-------------------------------------------------------------------------*/

#define CAN_START_SEC_CODE  /*---------------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if (CAN_VERSION_INFO_API == STD_ON) /* \trace SPEC-1716 */
/****************************************************************************
| NAME:             Can_GetVersionInfo
****************************************************************************/
/*
|<DataModelStart>| Can_GetVersionInfo
Relation_Context:
VersionInfoApi
Relation:
DevErrorDetect
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 */
V_DEF_FUNC(V_NONE, void, CODE) Can_GetVersionInfo( Can_VersionInfoPtrType VersionInfo )
{ /* \trace SPEC-1723 */
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter versionInfo is an illegal null pointer \trace SPEC-1721 */
  if (VersionInfo == NULL_PTR)
  {
    errorId = CAN_E_PARAM_POINTER;
  }
  else
# endif
  { /* #100 copy version info to given pointer parameter \trace SPEC-1717 */
    /* ----- Implementation ----------------------------------------------- */
    VersionInfo->vendorID   = CAN_VENDOR_ID; /* SBSW_CAN_HL10 */
    VersionInfo->moduleID   = CAN_MODULE_ID; /* SBSW_CAN_HL10 */
    VersionInfo->sw_major_version = (uint8)CAN_SW_MAJOR_VERSION; /* SBSW_CAN_HL10 */
    VersionInfo->sw_minor_version = (uint8)CAN_SW_MINOR_VERSION; /* SBSW_CAN_HL10 */
    VersionInfo->sw_patch_version = (uint8)CAN_SW_PATCH_VERSION; /* SBSW_CAN_HL10 */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_VERSION_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
}
#endif

/****************************************************************************
| NAME:             Can_InitMemory
****************************************************************************/
/*
|<DataModelStart>| Can_InitMemory
Relation_Context:
Relation:
Variant
DevErrorDetect
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
V_DEF_FUNC(V_NONE, void, CODE) Can_InitMemory( void )
{ /* BR:011 */
  /* ----- Local Variables ---------------------------------------------- */
  /* ----- Implementation ----------------------------------------------- */
  /* #10 mark driver as uninitialized \trace SPEC-1650 */
  canConfigInitFlag = CAN_STATUS_UNINIT;
#if defined(CAN_ENABLE_USE_INIT_ROOT_POINTER)
  /* #20 reset global configuration pointer */
  Can_ConfigDataPtr = NULL_PTR;
#endif /* otherwise constant pointer is used */
  /* #30 HW reset memory */
  CanLL_InitMemoryPowerOn(); /* PRQA S 2987 */ /* MD_Can_EmptyFunction */
#if(CAN_DEV_ERROR_DETECT == STD_OFF)
  CAN_DUMMY_STATEMENT(canConfigInitFlag); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
}


#if ((CAN_CHANGE_BAUDRATE_API == STD_ON) || (CAN_SET_BAUDRATE_API == STD_OFF))
/****************************************************************************
| NAME:             Can_ChangeBaudrate
****************************************************************************/
/*
|<DataModelStart>| Can_ChangeBaudrate
Relation_Context:
Relation:
ChangeBaudrate, DevErrorDetect, OneChOpt, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
V_DEF_FUNC(V_NONE, Std_ReturnType, CODE) Can_ChangeBaudrate( uint8 Controller, V_DEF_CONST(V_NONE, uint16, APPL_CONST) Baudrate )
{ /* \trace SPEC-20314 */
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retval;
  uint8 errorId;
  retval = E_NOT_OK;
  errorId = CAN_E_PARAM_BAUDRATE; /* explicit default as Issue - remove when baud rate fit */ /* \trace SPEC-20321 */
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller is valid and state is INIT and STOP \trace SPEC-20338 */
  if ( canConfigInitFlag == CAN_STATUS_UNINIT )
  {
    errorId = CAN_E_UNINIT;
  }
  else
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if ( channel >= kCanNumberOfChannels ) /* CM_CAN_HL01 */
  { /* \trace SPEC-20331 */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
  if ( (Can_GetLogStatus(channel) & CAN_STATUS_STOP) != CAN_STATUS_STOP )
  { /* \trace SPEC-1655, SPEC-20312 */
    errorId = CAN_E_TRANSITION;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    uint8_least baudrateIndex;
    for (baudrateIndex = Can_GetInitObjectStartIndex(channel); baudrateIndex < Can_GetInitObjectStartIndex(channel + 1u); baudrateIndex++)
    { /* #30 search for baud rate configuration */
      if (Can_GetInitObjectBaudrate(baudrateIndex) == Baudrate)
      { /* #40 set baud rate and reinitialize controller to activate baud rate \trace SPEC-1669 */
        uint8 transitionState;
        Can_SetLastInitObject(channel, (uint8)baudrateIndex); /* SBSW_CAN_HL11 */
        transitionState = CanHL_ModeTransition(CAN_CHANNEL_CANPARA_FIRST kCanModeStopReinit, kCanFinishBusOffRecovery, kCanSuppressRamCheck);
        if (transitionState == kCanOk) /* COV_CAN_TRANSITION_REQUEST */
        { /* #50 check transition STOP (Reinit) is successful */
          Can_SetLogStatus(channel, Can_GetLogStatus(channel) | CAN_STATUS_STOP); /* STOP mode reached */ /* SBSW_CAN_HL02 */
        }
        retval = E_OK;
        errorId = CAN_E_NO_ERROR;
        break;
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_CHANGE_BR_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
# if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  return retval;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if (CAN_CHANGE_BAUDRATE_API == STD_ON)
/****************************************************************************
| NAME:             Can_CheckBaudrate
****************************************************************************/
/*
|<DataModelStart>| Can_CheckBaudrate
Relation_Context:
ChangeBaudrate
Relation:
DevErrorDetect, OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
V_DEF_FUNC(V_NONE, Std_ReturnType, CODE) Can_CheckBaudrate( uint8 Controller, V_DEF_CONST(V_NONE, uint16, APPL_CONST) Baudrate )
{ /* \trace SPEC-20311 */
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retval;
  uint8 errorId;
  retval = E_NOT_OK;
  errorId = CAN_E_PARAM_BAUDRATE; /* \trace SPEC-20317 */
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller is valid and state is INIT \trace SPEC-20328, SPEC-20318 */
  if ( canConfigInitFlag == CAN_STATUS_UNINIT )
  {
    errorId = CAN_E_UNINIT;
  }
  else
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if ( channel >= kCanNumberOfChannels )
  { /* \trace SPEC-20335 */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    uint8_least baudrateIndex;
    for (baudrateIndex = Can_GetInitObjectStartIndex(channel); baudrateIndex < Can_GetInitObjectStartIndex(channel + 1u); baudrateIndex++)
    { /* #30 search for baud rate configuration */
      if (Can_GetInitObjectBaudrate(baudrateIndex) == Baudrate)
      { /* #40 requested baud rate is set - return OK */
        retval = E_OK;
        errorId = CAN_E_NO_ERROR;
        break;
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_CHECK_BR_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
# if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  return retval;
}
#endif /* CAN_CHANGE_BAUDRATE_API == STD_ON */

#if (CAN_SET_BAUDRATE_API == STD_ON)
/****************************************************************************
| NAME:             Can_SetBaudrate
****************************************************************************/
/*
|<DataModelStart>| Can_SetBaudrate
Relation_Context:
Relation:
ChangeBaudrate, DevErrorDetect, OneChOpt, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
V_DEF_FUNC(V_NONE, Std_ReturnType, CODE) Can_SetBaudrate( uint8 Controller, uint16 BaudRateConfigID )
{ /* \trace SPEC-50605 */
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retval;
  uint8 errorId;
  /* #5 return E_NOT_OK in case no fitting baudrate is found */
  retval = E_NOT_OK; /* PRQA S 2982 */ /* MD_MSR_RetVal */
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller is valid and state is INIT and STOP \trace SPEC-50595 */
  if ( canConfigInitFlag == CAN_STATUS_UNINIT )
  {
    errorId = CAN_E_UNINIT;
  }
  else
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if ( channel >= kCanNumberOfChannels ) /* CM_CAN_HL01 */
  { /* \trace SPEC-50587 */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
  if ( (Can_GetLogStatus(channel) & CAN_STATUS_STOP) != CAN_STATUS_STOP )
  { /* \trace SPEC-50584 */
    errorId = CAN_E_TRANSITION;
  }
  else
  if ( BaudRateConfigID >= (uint16)(Can_GetInitObjectStartIndex(channel + 1u) - Can_GetInitObjectStartIndex(channel)) ) /* PRQA S 4391 */ /* MD_Can_IntegerCast */
  { /* \trace SPEC-50625, SPEC-50563 */
    errorId = CAN_E_PARAM_BAUDRATE;
  }
  else
# endif
  { /* #50 set baud rate and reinitialize controller to activate baud rate */
    uint8 transitionState;
    /* ----- Implementation ----------------------------------------------- */
    Can_SetLastInitObject(channel, (uint8)(Can_GetInitObjectStartIndex(channel) + BaudRateConfigID)); /* SBSW_CAN_HL11 */
    transitionState = CanHL_ModeTransition(CAN_CHANNEL_CANPARA_FIRST kCanModeStopReinit, kCanFinishBusOffRecovery, kCanSuppressRamCheck);
    /* #60 check if hardware cancellation appear while mode change, so for the baud rate set is not successful \trace SPEC-60434 */
    if (transitionState == kCanOk) /* COV_CAN_TRANSITION_REQUEST */
    {
      retval = E_OK;
      Can_SetLogStatus(channel, Can_GetLogStatus(channel) | CAN_STATUS_STOP); /* STOP mode reached */ /* SBSW_CAN_HL02 */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_SET_BR_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
# if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  return retval;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* CAN_SET_BAUDRATE_API == STD_ON */

/****************************************************************************
| NAME:             Can_Init
****************************************************************************/
/*
|<DataModelStart>| Can_Init
Relation_Context:
Relation:
Variant, DevErrorDetect
RxQueue
OneChOpt
Variant
Wakeup
MirrorMode
SilentMode
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
 */
V_DEF_FUNC(V_NONE, void, CODE) Can_Init( Can_ConfigPtrType ConfigPtr ) /* PRQA S 3206 */ /* MD_MSR_DummyStmt */
{ /* \trace SPEC-1587, SPEC-1708 */
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  CAN_CHANNEL_CANTYPE_LOCAL
  CanHookBegin_Can_Init();
  errorId = CAN_E_NO_ERROR;
#if defined(CAN_ENABLE_USE_INIT_ROOT_POINTER) /* PostBuild (load+sel) */
  Can_ConfigDataPtr = ConfigPtr; /* \trace SPEC-1394, SPEC-1575 */
# if defined(CAN_ENABLE_USE_ECUM_BSW_ERROR_HOOK) /* PostBuildLoadable */
  if (ConfigPtr == NULL_PTR)
  { /* #10 EcuM null pointer configuration check and notification */
    EcuM_BswErrorHook((uint16) CAN_MODULE_ID, (uint8) ECUM_BSWERROR_NULLPTR);
  }
  else
#  if (CAN_FINALMAGICNUMBER == STD_ON) /* COV_CAN_FINALMAGICNUMBER */
  if (Can_GetFinalMagicNumber() != 20510u) /* COV_CAN_GENDATA_FAILURE */
  { /* #20 EcuM wrong magic number check and notification */
    EcuM_BswErrorHook((uint16) CAN_MODULE_ID, (uint8) ECUM_BSWERROR_MAGICNUMBER);
  }
  else
#  endif
# else
  
  /* ----- Development Error Checks ------------------------------------- */
#  if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #30 Check if all parameters are valid \trace SPEC-1724 */
  if (ConfigPtr == NULL_PTR)
  {
    errorId = CAN_E_PARAM_POINTER;
  }
  else
#  endif
# endif
#else
  CAN_DUMMY_STATEMENT(ConfigPtr);  /* PRQA S 1338, 2982, 2983, 3112 */ /* MD_MSR_DummyStmt */
# if defined(V_ENABLE_USE_DUMMY_STATEMENT) /* COV_CAN_COMPATIBILITY */
  ConfigPtr = Can_ConfigDataPtr;  /* PRQA S 2983,1338 */ /* MD_MSR_DummyStmt */
# endif
#endif /* CAN_ENABLE_USE_INIT_ROOT_POINTER */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
  if (canConfigInitFlag != CAN_STATUS_UNINIT)
  {
    /* #60 Check already initialized -> 2nd call is not allowed \trace SPEC-1712, SPEC-1722 */
    errorId = CAN_E_TRANSITION;
  }
  else
#endif
  if (  ( Can_GetBaseDll_GeneratorVersion()     != (uint16)CAN_GEN_BASE_CFG5_VERSION ) ||  /* PRQA S 2742 */ /* MD_Can_ConstValue */
        ( Can_GetPlatformDll_GeneratorVersion() != (uint16)CAN_GEN_ImxFlexcan3Asr_VERSION ) ) /* COV_CAN_GENDATA_FAILURE */
  {
    /* #70 EcuM generator and compatibility version check and notification */
#if defined(CAN_ENABLE_USE_ECUM_BSW_ERROR_HOOK) /* not for PostBuildSelectable */
    EcuM_BswErrorHook((uint16) CAN_MODULE_ID, (uint8) ECUM_BSWERROR_COMPATIBILITYVERSION); /* PRQA S 2880 */ /*  MD_MSR_Unreachable */
#else
    errorId = CAN_E_UNINIT; /* PRQA S 2880 */ /*  MD_MSR_Unreachable */
#endif
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    {
      canIsRxTaskLocked = kCanFalse;
#if defined(C_ENABLE_RX_QUEUE)
      /* #110 delete RxQueue (all channels) */
      Can_GetRxQueueInfo().WriteIndex = 0u;  /* CM_CAN_HL24 */ /* SBSW_CAN_HL55 */
      Can_GetRxQueueInfo().ReadIndex = 0u; /* SBSW_CAN_HL55 */
      Can_GetRxQueueInfo().Count = 0u; /* SBSW_CAN_HL55 */
#endif
      /* #120 Set active Identity */
      /* #130 HW specific power on (LL) */
      if (CanLL_InitPowerOn() == kCanOk) /* PRQA S 2991,2995 */ /* MD_Can_ConstValue */ /* COV_CAN_LL_HARDWARE_BEHAVIOUR */
      {
        canConfigInitFlag = CAN_STATUS_INIT; /* \trace SPEC-1648 */ /* before Controller initialization begin */
#if !defined( C_SINGLE_RECEIVE_CHANNEL )
        for (channel = 0u; channel < kCanNumberOfChannels; channel++) /* CM_CAN_HL01 */
#endif
        { /* #132 for each controller */
#if (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON) /* one controller optimization is always off */
          if ( Can_GetCanIfChannelId(channel) == kCanChannelNotUsed ) /* COV_CAN_GENDATA_FAILURE */
          { /* #134 not for inactive controller */
            continue;
          }
#endif
          /* #140 initialize start up values for each controllers */
          Can_SetLogStatus(channel, CAN_STATUS_UNINIT); /* PowerOn mark */ /* SBSW_CAN_HL02 */
          Can_SetModeTransitionRequest(channel, kCanModeNone); /* SBSW_CAN_HL01 */
          Can_SetBusOffTransitionRequest(channel, kCanFinishBusOffRecovery); /* SBSW_CAN_HL01 */
          Can_SetRamCheckTransitionRequest(channel, kCanSuppressRamCheck); /* SBSW_CAN_HL01 */
          Can_SetBusOffCounter(channel, 0u); /* SBSW_CAN_HL33 */
          Can_SetIsBusOff(channel, FALSE);  /* start up: no BUSOFF */ /* SBSW_CAN_HL08 */
          Can_SetCanInterruptCounter(channel, 0u); /* SBSW_CAN_HL12 */
#if defined(C_ENABLE_MIRROR_MODE)
          Can_SetMirrorModeState(channel, CDDMIRROR_INACTIVE); /* SBSW_CAN_HL20 */
#endif
#if defined(C_ENABLE_SILENT_MODE)
          Can_SetSilentModeState(channel, CAN_SILENT_INACTIVE); /* SBSW_CAN_HL20 */
#endif
          /* #155 HW channel specific power on */
          if (CanLL_InitPowerOnChannelSpecific(CAN_CHANNEL_CANPARA_ONLY) == kCanOk) /* PRQA S 2991,2995 */ /* MD_Can_ConstValue */ /* COV_CAN_HARDWARE_FAILURE */
          {
            uint8 transitionState;
            /* #160 set baud rate and initialize all CAN controllers \trace SPEC-1587, SPEC-1656 */
            Can_SetLastInitObject(channel, (uint8)(Can_GetInitObjectStartIndex(channel) + Can_GetCanControllerDefaultBaudrateIdx(CAN_HL_HW_CHANNEL_STARTINDEX(channel)))); /* SBSW_CAN_HL11 */
            transitionState = CanHL_ModeTransition(CAN_CHANNEL_CANPARA_FIRST kCanModeStopReinit, kCanFinishBusOffRecovery, kCanExecuteRamCheck);
            if (transitionState == kCanOk) /* COV_CAN_TRANSITION_REQUEST */
            { /* #170 check transition STOP (Reinit) is successful */
              Can_SetLogStatus(channel, Can_GetLogStatus(channel) | CAN_STATUS_STOP); /* STOP mode reached or issue */ /* SBSW_CAN_HL02 */
            }
#if (CAN_DEV_ERROR_DETECT == STD_ON)
            else
            {              
              errorId = CAN_E_TRANSITION;
            }
#endif
          }
        }
      } /* CanLL_InitPowerOn */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_INIT_ID, errorId);
  }
#else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
  CanHookEnd_Can_Init();
} /* PRQA S 6030,6050,6080 */ /* MD_MSR_STCYC,MD_MSR_STCAL,MD_MSR_STMIF */

/****************************************************************************
| NAME:             Can_SetControllerMode
****************************************************************************/
/*
|<DataModelStart>| Can_SetControllerMode
Relation_Context:
Relation:
DevErrorDetect, OneChOpt, ChannelAmount
DevErrorDetect, Variant, ChannelAmount
DevErrorDetect, TransitionCheck
RamCheck, ChannelAmount
SilentMode, ChannelAmount
ReInitStart
Wakeup
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
 */
V_DEF_FUNC(V_NONE, Can_ReturnType, CODE) Can_SetControllerMode( uint8 Controller, Can_StateTransitionType Transition )
{ /* \trace SPEC-1715 */
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  Can_ReturnType retval;
  uint8 transitionRequest;
  uint8 busOffRecovery;
  uint8 doRamCheck;
  uint8 transitionState;
  CanHookBegin_Can_SetControllerMode();
  retval = CAN_NOT_OK;  /* \trace SPEC-1407 */ /* For successful transition it is set explicit to CAN_OK */
  transitionState = kCanFailed;
  errorId = CAN_E_NO_ERROR;
  /* ----- Development Error Checks ------------------------------------- */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller and Transition is valid and state is INIT */
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* \trace SPEC-1731 */
    errorId = CAN_E_UNINIT;
  }
  else
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  { /* \trace SPEC-1732 */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
# endif
# if (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
  if (Can_GetCanIfChannelId(channel) == kCanChannelNotUsed) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  { 
    errorId = CAN_E_PARAM_CONTROLLER; /* \trace SPEC3874 */
  }
  else
# endif
#endif
  { /* #50 second level check (modes and transitions) only valid when controller is in active ECU and valid */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
    if (!CanHL_IsControllerInit(channel))
    { /* #60 Check controller is initialized */
      errorId = CAN_E_UNINIT;
    }
    else
    if ((!CanHL_IsStop(channel)) && (Transition == CAN_T_START))
    { /* #70 Check No-STOP -> START-Req is invalid \trace SPEC-1637 */ /* ESCAN00073272 */
      errorId = CAN_E_TRANSITION;
    }
    else
# if (CAN_TRANSITION_CHECK == STD_ON)  /* SREQ00000291 */
    if ( ((!CanHL_IsStop(channel)) && (!CanHL_IsSleep(channel)) && ((Transition == CAN_T_WAKEUP) || (Transition == CAN_T_SLEEP))) ||
         ((CanHL_IsSleep(channel)) && (Transition == CAN_T_STOP)) )
    { /* #80 Check  No STOP Nor SLEEP -> SLEEP-Req   or   No SLEEP Nor STOP --> WAKEUP-Req   is invalid \trace SPEC-1654, SPEC-1649 */
      /* #90 Check  No START Nor STOP -> STOP-Req is invalid \trace SPEC-1652 */
      errorId = CAN_E_TRANSITION;
    }
    else
# endif
#endif
#if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
    /* #95 controller is active (no RAM check issue): */
    if ((Can_GetLogStatus(channel) & CAN_DEACTIVATE_CONTROLLER) != CAN_DEACTIVATE_CONTROLLER) /* PRQA S 2004 */ /* MD_Can_NoElseAfterIf */ /* COV_CAN_RAM_CHECK_NO_STIMULATION */
#endif
    {
      /* ----- Implementation ----------------------------------------------- */
      /* #100 EXCLUSIVE_AREA_6 avoid nesting mode changes (e.g. same API, initialization or BUSOFF) */
      SchM_Enter_Can_CAN_EXCLUSIVE_AREA_6();
      /* #125 HW begin mode transition */
      switch(Transition)
      {
      case CAN_T_START:
        /* #200 Handle --- START --- transition */
        if (Can_IsIsBusOff(channel)) /* COV_CAN_BUSOFF_NOT_IN_ALL_CONFIG */
        { /* #210 BUSOFF occur so finish BUSOFF handling and do START transition inside */
          transitionRequest = kCanModeResetBusOffEnd;
        } 
        else
        {
#if defined(C_ENABLE_SILENT_MODE)
          if (Can_GetSilentModeState(channel) == CAN_SILENT_ACTIVE)
          {
            transitionRequest = kCanModeSilent;
          }
          else
#endif
          {
#if (CAN_REINIT_START == STD_ON)
            transitionRequest = kCanModeStartReinit;
#else
            transitionRequest = kCanModeStart;
#endif
          }
        }
        busOffRecovery = kCanContinueBusOffRecovery;
        doRamCheck = kCanSuppressRamCheck;
        transitionState = CanHL_ModeTransition(CAN_CHANNEL_CANPARA_FIRST transitionRequest, busOffRecovery, doRamCheck);
        if ( transitionState == kCanOk ) /* COV_CAN_TRANSITION_REQUEST */
        {
          Can_SetIsBusOff(channel, FALSE); /* SBSW_CAN_HL08 */
        }
        CanHL_NotifyTransition(CAN_CHANNEL_CANPARA_FIRST CAN_STATUS_START, CANIF_CS_STARTED, transitionState);
        break;

      case CAN_T_STOP:
        /* #300 Handle --- STOP --- transition */
        transitionRequest = kCanModeStopReinitFast;
        if (Can_GetBusOffCounter(channel) == 0u)  /* COV_CAN_BUSOFF_NOT_IN_ALL_CONFIG */
        {
          busOffRecovery = kCanFinishBusOffRecovery;
        }
        else
        {
          Can_DecBusOffCounter(channel); /* SBSW_CAN_HL33 */
          busOffRecovery = kCanContinueBusOffRecovery;
        }
        doRamCheck = kCanSuppressRamCheck;
        transitionState = CanHL_ModeTransition(CAN_CHANNEL_CANPARA_FIRST transitionRequest, busOffRecovery, doRamCheck);
        CanHL_NotifyTransition(CAN_CHANNEL_CANPARA_FIRST CAN_STATUS_STOP, CANIF_CS_STOPPED, transitionState);
        break;

      case CAN_T_WAKEUP:
        /* #400 Handle --- WAKEUP --- transition */
#if defined(C_ENABLE_CAN_RAM_CHECK) && !defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
        if (!CanHL_IsStop(channel)) { /* do not call RAM_CHECK again in case CanIf call wakeup a second time (buswakeup + stop transition afterwards) */
          /* #415 do standard RAM check CanHL_DoRamCheck() if controller is not in STOP mode */
          transitionRequest = kCanModeStopReinit;
          doRamCheck = kCanExecuteRamCheck;
        }
        else
#endif
        {
          transitionRequest = kCanModeStopReinitFast;
          doRamCheck = kCanSuppressRamCheck;
        }
        {
          busOffRecovery = kCanFinishBusOffRecovery;
        }
        transitionState = CanHL_ModeTransition(CAN_CHANNEL_CANPARA_FIRST transitionRequest, busOffRecovery, doRamCheck);
        CanHL_NotifyTransition(CAN_CHANNEL_CANPARA_FIRST CAN_STATUS_STOP, CANIF_CS_STOPPED, transitionState);
        break;

      case CAN_T_SLEEP: /* \trace SPEC-1639 */
        /* #500 Handle --- SLEEP --- transition */
        { /* #520 no WAKEUP-source-ref: do emulated SLEEP mode \trace SPEC-1629, SPEC-1641, SPEC-1645 */
          transitionState = kCanOk;
        }
        CanHL_NotifyTransition(CAN_CHANNEL_CANPARA_FIRST CAN_STATUS_SLEEP, CANIF_CS_SLEEP, transitionState);
        break;

      default:
        /* #600 check unknown transition, return NOT_OK \trace SPEC-1573, SPEC-1402, SPEC-1403 */
        errorId = CAN_E_TRANSITION; /* \trace SPEC-1733, SPEC-1407 */
        break;
      } /* switch */
      SchM_Exit_Can_CAN_EXCLUSIVE_AREA_6();
    }
  }
  if ( transitionState != kCanFailed ) /* COV_CAN_TRANSITION_REQUEST */
  {
    retval = CAN_OK;
  }
  /* ----- Development Error Report --------------------------------------- */
#if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_SETCTR_ID, errorId);
  }
#else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
#if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
  CanHookEnd_Can_SetControllerMode();
  return retval;
} /* PRQA S 6010,6030,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STMIF */

/****************************************************************************
| NAME:             Can_DisableControllerInterrupts
****************************************************************************/
/*
|<DataModelStart>| Can_DisableControllerInterrupts
Relation_Context:
# from Can_MainFunction_BusOff #
StatusPolling, ChannelAmount
# from CanHL_TxTaskCancelationHandling #
HwCancelTx, IndividualPolling
# from CanHL_TxConfirmationPolling #
TxPolling
# from Rx BasicCan FullCan #
RxPolling
RxBasicCANSupport
RxFullCANSupport
# from Error handling #
StatusPolling
Relation:
DevErrorDetect, OneChOpt
DevErrorDetect, Variant
IntLock
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
V_DEF_FUNC(V_NONE, void, CODE) Can_DisableControllerInterrupts( uint8 Controller )
{ /* \trace SPEC-1746 */
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller is valid and state is INIT */
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* \trace SPEC-1750 */
    errorId = CAN_E_UNINIT;
  }
  else
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  { /* \trace SPEC-1742 */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
# endif
# if (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
  if (Can_GetCanIfChannelId(channel) == kCanChannelNotUsed) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
# endif
  if (!CanHL_IsControllerInit(channel))
  { /* #40 Check controller is initialized \trace SPEC-1750 */
    errorId = CAN_E_UNINIT;
  }
  else
#endif
  { /* ----- Implementation ----------------------------------------------- */
    /* #100 EXCLUSIVE_AREA_1 secure interrupt lock handling */
    SchM_Enter_Can_CAN_EXCLUSIVE_AREA_1();
    if (Can_GetCanInterruptCounter(channel) == 0u)
    { /* #110 Disable only when not disabled before (count nesting) \trace SPEC-1735, SPEC-1745 */
#if (CAN_INTLOCK == CAN_DRIVER) || (CAN_INTLOCK == CAN_BOTH) /* COV_CAN_LOCK_ISR_BY_APPL */
      { /* #120 Disable CAN interrupt for each HW channel */
        CanLL_CanInterruptDisable(CAN_CHANNEL_CANPARA_FIRST  &Can_GetCanInterruptOldStatus(canHwChannel)); /* SBSW_CAN_HL16 */
      }
#endif
#if (CAN_INTLOCK == CAN_APPL) || (CAN_INTLOCK == CAN_BOTH) /* COV_CAN_LOCK_ISR_BY_APPL */
      /* #130 Let application Disable CAN interrupt ApplCanInterruptDisable() */
      ApplCanInterruptDisable((uint8)channel);
#endif
    }
    Can_IncCanInterruptCounter(channel); /* \trace SPEC-1748 */ /* SBSW_CAN_HL12 */
    SchM_Exit_Can_CAN_EXCLUSIVE_AREA_1();
  }

  /* ----- Development Error Report --------------------------------------- */
#if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_DIINT_ID, errorId);
  }
#else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
#if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/****************************************************************************
| NAME:             Can_EnableControllerInterrupts
****************************************************************************/
/*
|<DataModelStart>| Can_EnableControllerInterrupts
Relation_Context:
# from Can_MainFunction_BusOff #
StatusPolling, ChannelAmount
# from CanHL_TxTaskCancelationHandling #
HwCancelTx, IndividualPolling
# from CanHL_TxConfirmationPolling #
TxPolling
# from Rx BasicCan FullCan #
RxPolling
RxBasicCANSupport
RxFullCANSupport
# from Error handling #
StatusPolling
Relation:
DevErrorDetect, OneChOpt 
DevErrorDetect, Variant
IntLock
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
V_DEF_FUNC(V_NONE, void, CODE) Can_EnableControllerInterrupts( uint8 Controller )
{ /* \trace SPEC-1741 */
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller is valid and state is INIT */
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* \trace SPEC-1739 */
    errorId = CAN_E_UNINIT;
  }
  else
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  { /* \trace SPEC-1752 */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
# endif
# if (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
  if (Can_GetCanIfChannelId(channel) == kCanChannelNotUsed) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
# endif
  if (!CanHL_IsControllerInit(channel))
  { /* #40 Check controller is initialized \trace SPEC-1739 */
    errorId = CAN_E_UNINIT;
  }
  else
#endif
  { /* ----- Implementation ----------------------------------------------- */
    /* #100 EXCLUSIVE_AREA_1 secure interrupt lock handling */
    SchM_Enter_Can_CAN_EXCLUSIVE_AREA_1();
    if (Can_GetCanInterruptCounter(channel) != 0u)
    { /* #110 Enable only when disabled before (count nesting) \trace SPEC-1749, SPEC-1748 */
      Can_DecCanInterruptCounter(channel); /* SBSW_CAN_HL12 */
      if (Can_GetCanInterruptCounter(channel) == 0u) /* \trace SPEC-1736, SPEC-1756 */
      {
#if (CAN_INTLOCK == CAN_DRIVER) || (CAN_INTLOCK == CAN_BOTH) /* COV_CAN_LOCK_ISR_BY_APPL */
        { /* #120 Disable CAN interrupt for each HW channel */
          CanLL_CanInterruptRestore(CAN_CHANNEL_CANPARA_FIRST Can_GetCanInterruptOldStatus(canHwChannel));
        }
#endif
#if (CAN_INTLOCK == CAN_APPL) || (CAN_INTLOCK == CAN_BOTH) /* COV_CAN_LOCK_ISR_BY_APPL */
        /* #130 Let application Enable CAN interrupt ApplCanInterruptRestore() */
        ApplCanInterruptRestore((uint8)channel);
#endif
      }
    }
    SchM_Exit_Can_CAN_EXCLUSIVE_AREA_1();
  }

  /* ----- Development Error Report --------------------------------------- */
#if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_ENINT_ID, errorId);
  }
#else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
#if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/****************************************************************************
| NAME:             Can_Write
****************************************************************************/
/*
|<DataModelStart>| Can_Write
Relation_Context:
Relation:
DevErrorDetect
OneChOpt
DevErrorDetect, OneChOpt
DevErrorDetect, Variant
DevErrorDetect, TxFullCANSupport
DevErrorDetect, CanFdSupport
DevErrorDetect, MixedId
RamCheck
UseVectorCanIf
CanFdSupport
ChannelAmount
TxBasicAmount
TxFullAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
 */
V_DEF_FUNC(V_NONE, Can_ReturnType, CODE) Can_Write( Can_HwHandleType Hth, Can_PduInfoPtrType PduInfo )
{ /* \trace SPEC-1751, SPEC-1760, SPEC-1406 */
  /* ----- Local Variables ---------------------------------------------- */
  Can_ReturnType retval;
  CAN_CHANNEL_CANTYPE_LOCAL
  uint8 errorId;
  CanHookBegin_Can_Write();
  errorId = CAN_E_NO_ERROR;
  retval = CAN_NOT_OK; /* PRQA S 2982 */ /* MD_MSR_RetVal */
  
  /* ----- Development Error Checks ------------------------------------- */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller is valid and state is INIT */
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* \trace SPEC-1759 */
    errorId = CAN_E_UNINIT;
  }
  else
  if (Hth >= Can_GetSizeOfMailbox()) {
    errorId = CAN_E_PARAM_HANDLE;
  }
  else
#endif
  {
#if !defined( C_SINGLE_RECEIVE_CHANNEL ) /* otherwise 'channel' is a define */
    channel = Can_GetMailboxController(Hth);
#endif
#if (CAN_DEV_ERROR_DETECT == STD_ON)
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
    if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */ /* COV_CAN_GENDATA_FAILURE */
    {
      errorId = CAN_E_PARAM_HANDLE;
    }
    else
# endif
# if (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
    if (Can_GetCanIfChannelId(channel) == kCanChannelNotUsed) /* COV_CAN_GENDATA_FAILURE */
    {
      errorId = CAN_E_PARAM_HANDLE;
    }
    else
# endif
    if (!CanHL_IsControllerInit(channel))
    { /* #40 Check controller is initialized \trace SPEC-1407 */
      errorId = CAN_E_UNINIT;
    }
    else
# if defined(C_ENABLE_TX_FULLCAN_OBJECTS)
    if ((Can_GetMailboxType(Hth) != CAN_TX_BASICCAN_TYPE) && (Can_GetMailboxType(Hth) != CAN_TX_BASICCAN_MUX_TYPE) && (Can_GetMailboxType(Hth) != CAN_TX_BASICCAN_FIFO_TYPE) && (Can_GetMailboxType(Hth) != CAN_TX_FULLCAN_TYPE)) /* COV_CAN_GENDATA_TX_NOT_IN_ALL_CONFIG */
# else
    if ((Can_GetMailboxType(Hth) != CAN_TX_BASICCAN_TYPE) && (Can_GetMailboxType(Hth) != CAN_TX_BASICCAN_MUX_TYPE) && (Can_GetMailboxType(Hth) != CAN_TX_BASICCAN_FIFO_TYPE)) /* COV_CAN_GENDATA_TX_NOT_IN_ALL_CONFIG */
# endif
    { /* \trace SPEC-1763 */
      errorId = CAN_E_PARAM_HANDLE;
    }
    else
    if ((PduInfo == NULL_PTR) || ((PduInfo->sdu == NULL_PTR) && (PduInfo->length != 0u)))
    { /* \trace SPEC-1761 */
      errorId = CAN_E_PARAM_POINTER;
    }
    else
# if !defined(C_ENABLE_CAN_FD_USED)
    if ( CanHL_IsFdMessage(PduInfo->id) )
    { /* no CAN_FD: Check parameter PduInfo->id should not have FD bit in ID */
      errorId = CAN_E_PARAM_POINTER;
    }
    else
# endif
# if defined(C_ENABLE_CAN_FD_FULL)
    if ( ((PduInfo->length > 8u) && (Can_GetInitObjectFdBrsConfig(Can_GetLastInitObject(channel)) == CAN_NONE)) ||
         (PduInfo->length > CAN_MAX_DATALEN_OBJ(Hth)) ) /* COV_CAN_GENDATA_FAILURE */
         { /* \trace SPEC-1758 */
      /* \trace SPEC-60433 */ /* CAN_FD: Check parameter PduInfo->length is smaller than 9 for none FD configuration
         If development error detection for the CAN module is enabled and the CAN Controller is not in CAN FD mode (no CanControllerFdBaudrateConfig):
         The function Can_Write shall raise the error CAN_E_PARAM_DLC and shall return CAN_NOT_OK if the length is more than 8 byte.() */
      /* CAN_FD: Check parameter PduInfo->length against PDU maximum size */
      errorId = CAN_E_PARAM_DLC;
    }
    else
# else
    if ( PduInfo->length > CAN_MAX_DATALEN_OBJ(Hth) ) /* CM_CAN_HL20 */
    { /* \trace SPEC-1758 */ /* Check parameter PduInfo->length against maximum buffer size */
      errorId = CAN_E_PARAM_DLC;
    }
    else
# endif
# if defined(C_ENABLE_MIXED_ID)
    if ( ((PduInfo->id & (Can_IdType)CAN_ID_IDE_MASK) != (Can_IdType)CAN_ID_IDE_MASK ) && ( (PduInfo->id & (Can_IdType)CAN_ID_MASK) > (Can_IdType)CAN_ID_MASK_STD ) ) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    { /* Check parameter PduInfo->id for STD ID is in STD range (EXT is always in range) */
      errorId = CAN_E_PARAM_POINTER;
    }
    else
# endif
    if ( (PduInfo->id & (Can_IdType)CAN_ID_UNUSED_MASK) != (Can_IdType)0UL )
    { /* Check parameter PduInfo->id contains illegal bits (e.g. bigger ID value than MAX for given type) */
      errorId = CAN_E_PARAM_POINTER;
    }
    else
#endif
    /* ----- Implementation ----------------------------------------------- */
#if defined(C_ENABLE_CAN_RAM_CHECK)
    /* #150 reject deactivated mailbox (by RamCheck) */
    if (Can_GetMailboxState(Hth) == kCanFailed) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
    {
      retval = CAN_NOT_OK;
    }
    else
#endif
    /* #180 check Hardware is in BUSOFF recovery state and is not able to handle a request: return BUSY \trace SPEC-1764 */
    if (Can_IsIsBusOff(channel)) /* COV_CAN_BUSOFF_NOT_IN_ALL_CONFIG */
    {
      retval = CAN_NOT_OK; /* ESCAN00096369 */
    }
    else
#if defined(C_ENABLE_CAN_RAM_CHECK)
    /* #200 controller is active (no RAM check issue): */
    if ((Can_GetLogStatus(channel) & CAN_DEACTIVATE_CONTROLLER) != CAN_DEACTIVATE_CONTROLLER) /* PRQA S 2004 */ /* MD_Can_NoElseAfterIf */ /* COV_CAN_HARDWARE_FAILURE */
#endif
    {
      /* #205 temporary pdu buffer to avoid data modification on constant data (modification in generic pretransmit) */
      tCanTxTransmissionParaStruct txPara;
      /* #210 EXCLUSIVE_AREA_2: Interrupts may not be locked and re-entrant call may occur. */
      /*                        Time in between ID search and lock of mailbox is critical 
                                (only when no Vector Interface used otherwise CanIf EXCLUSIVE_AREA is used instead) 
                                Can_Write() could be called re-entrant, there for also for polling systems the interrupts have to be locked  
                                this is essential while check for mailbox is free (in between if (free) and set to not free) and save PDU handle */
#if !defined(CAN_USE_VECTOR_IF)
      SchM_Enter_Can_CAN_EXCLUSIVE_AREA_2();
#endif
      txPara.mailboxHandle = Hth;
      txPara.hwObjHandle = Can_GetMailboxHwHandle(Hth); 
      txPara.pdu.id = PduInfo->id;
      txPara.pdu.length = PduInfo->length;
      txPara.pdu.sdu = PduInfo->sdu;
      txPara.pdu.swPduHandle = PduInfo->swPduHandle;
#if defined(C_ENABLE_CAN_FD_USED)
      if (txPara.pdu.length <= 8u) /* PRQA S 2991,2995 */ /* MD_Can_ConstValue */ /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
      {
        if (Can_GetInitObjectFdBrsConfig(Can_GetLastInitObject(channel)) == CAN_NONE)
        { /* #220 remove FD flag when no FD support is activated in this initialization structure and DLC not greater than 8 */
          /* CAN FD also support an extended payload which allows the transmission of up to 64 bytes.
          This feature also depends on the CAN FD configuration (see CanControllerFdBaudrateConfig).
          Therefore, if the CAN FD feature is enabled and the CAN FD flag is set in CanId passed to
           Can_Write(), CanDrv supports the transmission of PDUs with a length up to 64 bytes.
          If there is a request to transmit a CAN FD frame without the CAN FD feature enabled the
          frame is sent as conventional CAN frame as long as the PDU length <= 8 bytes. */
          txPara.pdu.id = txPara.pdu.id & ((Can_IdType)(CAN_ID_IDE_MASK | CAN_ID_MASK)); /* CAN_FD_   mask out the FD bit */
        }
      }
      txPara.fdBrsType = kCanFdBrsTypeFalse;
      if (CanHL_IsFdMessage(txPara.pdu.id))
      {
        txPara.fdType = kCanFdTypeFd;
        if (CanHL_IsFdTxBrs(channel))
        {
          txPara.fdBrsType = kCanFdBrsTypeTrue;
        }
      } else {
        txPara.fdType = kCanFdTypeClassic;
      }
      txPara.messageLen = txPara.pdu.length;
      txPara.frameLen = CAN_DLC2LEN(CAN_LEN2DLC(txPara.messageLen));
# if defined(C_ENABLE_CAN_FD_FULL)
      txPara.paddingVal = Can_GetMailboxFdPadding(txPara.mailboxHandle);
# endif
#endif
      /* #230 search for BasicCAN object handle to transmit (Multiplexed TX) and backup data for cancel TX object if necessary */
      CanHL_WritePrepare(CAN_CHANNEL_CANPARA_FIRST &txPara); /* SBSW_CAN_HL49 */
      /* #240 start transmission for given handle (if free) and return state */
      retval = CanHL_WriteStart(CAN_CHANNEL_CANPARA_FIRST &txPara); /* SBSW_CAN_HL49 */

#if !defined(CAN_USE_VECTOR_IF) /* No Vector Interface used, Interrupts may not be locked */
      /* avoid change of PDU information due to TX interrupt while changing */
      SchM_Exit_Can_CAN_EXCLUSIVE_AREA_2();
#endif
    }
  }
  /* ----- Development Error Report --------------------------------------- */
#if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_WRITE_ID, errorId);
  }
#else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
  CanHookEnd_Can_Write();
  return retval;
} /* PRQA S 6010,6030,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STMIF */

/****************************************************************************
| NAME:             ASR4.x - Can_CheckWakeup
****************************************************************************/
/*
|<DataModelStart>| Can_CheckWakeup
Relation_Context:
Relation:
Wakeup, DevErrorDetect, OneChOpt
Wakeup, DevErrorDetect, Variant
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
#if defined(C_ENABLE_CHECK_WAKEUP_CAN_RET_TYPE) /* COV_CAN_COMPATIBILITY */
# define CAN_CHECKWAKEUP_RETTYPE Can_ReturnType
# define CAN_CHECKWAKEUP_RETVAL_OK     CAN_OK
# define CAN_CHECKWAKEUP_RETVAL_NOT_OK CAN_NOT_OK
V_DEF_FUNC(V_NONE, Can_ReturnType, CODE) Can_CheckWakeup( uint8 Controller )
#else
# define CAN_CHECKWAKEUP_RETTYPE Std_ReturnType
# define CAN_CHECKWAKEUP_RETVAL_OK     E_OK
# define CAN_CHECKWAKEUP_RETVAL_NOT_OK E_NOT_OK
V_DEF_FUNC(V_NONE, Std_ReturnType, CODE) Can_CheckWakeup( uint8 Controller )
#endif
{ /* \trace SPEC-1740 */
  /* ----- Local Variables ---------------------------------------------- */
  CAN_CHECKWAKEUP_RETTYPE retval;
  retval = CAN_CHECKWAKEUP_RETVAL_NOT_OK; /* \trace SPEC-1407 */
  CAN_DUMMY_STATEMENT(Controller); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return retval;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/****************************************************************************
| NAME:             Can_MainFunction_Write
****************************************************************************/
/*
|<DataModelStart>| Can_MainFunction_Write
Relation_Context:
Relation:
TxPolling, HwCancelTx, DevErrorDetect
TxPolling, HwCancelTx, OneChOpt
TxPolling, HwCancelTx, Variant
TxPolling, HwCancelTx, Wakeup
TxPolling, IndividualPolling
TxPolling, TxFullCANSupport, IndividualPolling
TxFullCANSupport, HwCancelTx
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
V_DEF_FUNC(V_NONE, void, CODE) Can_MainFunction_Write( void )
{ /* \trace SPEC-1766 */
  /* ----- Local Variables ---------------------------------------------- */
#if defined(C_ENABLE_TX_POLLING) 
  CAN_CHANNEL_CANTYPE_LOCAL
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  CanHookBegin_Can_MainFunction_Write();
  /* canSendSemaphor no more needed because of ControllerInterrupts disabled while Can_Write() */
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* #10 Check Driver is initialized \trace SPEC-1767 */
    errorId = CAN_E_UNINIT;
  }
  else
# endif
  {  
    /* ----- Implementation ----------------------------------------------- */
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
    for (channel = 0u; channel < kCanNumberOfChannels; channel++)
# endif
    { /* #20 over all active controller */
# if (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON) /* one controller optimization is always off */
      if ( Can_GetCanIfChannelId(channel) == kCanChannelNotUsed ) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
      { /* not for inactive controller */
        continue;
      }
# endif
# if (CAN_DEV_ERROR_DETECT == STD_ON) /* \trace SPEC-1573, SPEC-1402, SPEC-1403 */
      if (!CanHL_IsControllerInit(channel))
      { /* #50 Check controller is initialized */
        errorId = CAN_E_UNINIT;
      }
      else
# endif
      {
        if ( !CanHL_IsSleep(channel) )
        { /* #60 do not access CAN hardware in SLEEP */
          tCanTaskParaStruct taskPara;
# if defined(C_ENABLE_TX_POLLING) /* COV_CAN_TX_POLLING TX */ /* always true when no hw-cancel is supported */
          /* #100 do confirmation handling for pending mailboxes */
          if ( CanLL_TxIsGlobalConfPending(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_ONLY) == kCanTrue ) /* PRQA S 2991,2995 */ /* MD_Can_ConstValue */ /* COV_CAN_LL_HARDWARE_BEHAVIOUR */
          { /* #110 is at least one mailbox pending */
            for ( taskPara.mailboxHandle = Can_GetTxBasicHandleStart(canHwChannel); taskPara.mailboxHandle < Can_GetTxBasicHandleStop(canHwChannel); taskPara.mailboxHandle++ ) /* PRQA S 2994,2996 */ /* MD_Can_ConstValue */
            { /* #120 iterate over all TxBasicCAN */
              taskPara.hwObjHandle = Can_GetMailboxHwHandle(taskPara.mailboxHandle); /* PRQA S 2880 */ /*  MD_MSR_Unreachable */
#  if defined(C_ENABLE_INDIVIDUAL_POLLING) /* COV_CAN_HWOBJINDIVPOLLING */
              if ( Can_IsMailboxIndivPolling(taskPara.mailboxHandle)) /* COV_CAN_HWOBJINDIVPOLLING */
#  endif
              { /* #130 is mailbox handled by polling (individual) */
                /* #140 call LL confirmation handling */
                CanLL_TxProcessPendings(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &taskPara); /* SBSW_CAN_HL44 */
              }
            }
          }
# endif
# if defined(C_ENABLE_CANCEL_TX_IN_HW) 
# endif
# if defined(C_ENABLE_TX_FULLCAN_OBJECTS)
#  if defined(C_ENABLE_TX_POLLING) /* COV_CAN_TX_POLLING TX */ /* always true when no hw-cancel is supported */
          /* #200 do confirmation handling for pending mailboxes */
          if ( CanLL_TxIsGlobalConfPending(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_ONLY) == kCanTrue ) /* PRQA S 2991,2995 */ /* MD_Can_ConstValue */ /* COV_CAN_LL_HARDWARE_BEHAVIOUR */
          { /* #210 is at least one mailbox pending */
            for ( taskPara.mailboxHandle = Can_GetTxFullHandleStart(canHwChannel); taskPara.mailboxHandle < Can_GetTxFullHandleStop(canHwChannel); taskPara.mailboxHandle++ ) /* PRQA S 2994,2996 */ /* MD_Can_ConstValue */
            { /* #220 iterate over all TxFullCAN */
              taskPara.hwObjHandle = Can_GetMailboxHwHandle(taskPara.mailboxHandle); /* PRQA S 2880 */ /*  MD_MSR_Unreachable */
#   if defined(C_ENABLE_INDIVIDUAL_POLLING) /* COV_CAN_HWOBJINDIVPOLLING */
              if ( Can_IsMailboxIndivPolling(taskPara.mailboxHandle)) /* COV_CAN_HWOBJINDIVPOLLING */
#   endif
              { /* #230 is mailbox handled by polling (individual) */
                /* #240 call LL confirmation handling */
                CanLL_TxProcessPendings(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &taskPara); /* SBSW_CAN_HL44 */
              }
            }
          }
#  endif
#  if defined(C_ENABLE_CANCEL_TX_IN_HW) 
#  endif
# endif
        } /* !IsSleep */
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_MAINFCT_WRITE_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif

#else
  CanHookBegin_Can_MainFunction_Write();
#endif /* C_ENABLE_TX_POLLING */
  CanHookEnd_Can_MainFunction_Write();
} /* PRQA S 6030,6080 */ /* MD_MSR_STCYC,MD_MSR_STMIF */

/****************************************************************************
| NAME:             Can_MainFunction_Read
****************************************************************************/
/*
|<DataModelStart>| Can_MainFunction_Read
Relation_Context:
Relation:
DevErrorDetect
RxPolling, OneChOpt
RxPolling, Variant
RxPolling, DevErrorDetect
RxPolling, Wakeup
RxPolling, RxFullCANSupport
RxPolling, RxBasicCANSupport
RxQueue
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
V_DEF_FUNC(V_NONE, void, CODE) Can_MainFunction_Read( void )
{ /* \trace SPEC-1776 */
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  CanHookBegin_Can_MainFunction_Read();
  errorId = CAN_E_NO_ERROR; /* PRQA S 2982 */ /* MD_MSR_RetVal */
  
  /* ----- Development Error Checks ------------------------------------- */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check Driver is initialized \trace SPEC-1784 */
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  {
    errorId = CAN_E_UNINIT;
  }
  else
#endif
  /* ----- Implementation ----------------------------------------------- */
  /* #20 semaphore to secure parallel access to RX buffers interrupt or polling \trace SPEC-1569 */
  if ( canIsRxTaskLocked == kCanFalse )  /* PRQA S 2004 */ /* MD_Can_NoElseAfterIf */
  {
#if defined(C_ENABLE_RX_POLLING) /* COV_CAN_RX_POLLING */
    CAN_CHANNEL_CANTYPE_LOCAL
#endif
    canIsRxTaskLocked = kCanTrue; /* PRQA S 2982 */ /* MD_MSR_RetVal */
#if defined(C_ENABLE_RX_POLLING) /* \trace SPEC-1782 */ /* COV_CAN_RX_POLLING */
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
    for (channel = 0u; channel < kCanNumberOfChannels; channel++)
# endif
    { /* #30 iterate over all active controller */
# if (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON) /* one controller optimization is always off */
      if ( Can_GetCanIfChannelId(channel) == kCanChannelNotUsed ) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
      { /* not for inactive controller */
        continue;
      }
# endif
# if (CAN_DEV_ERROR_DETECT == STD_ON)
      if (!CanHL_IsControllerInit(channel))
      { /* #60 Check controller is initialized */
        errorId = CAN_E_UNINIT;
      }
      else
# endif
      {
        if ( !CanHL_IsSleep(channel) )
        { /* #70 do not access CAN hardware in SLEEP */
          /* #80 over all HW channel \trace SPEC-1774 */
# if defined(C_ENABLE_RX_FULLCAN_OBJECTS)
          /* #90 search for all pending FullCAN mailbox objects and call notification */
          CanHL_RxFullCanPolling(CAN_HW_CHANNEL_CANPARA_ONLY);
# endif
# if defined(C_ENABLE_RX_BASICCAN_OBJECTS) /* COV_CAN_MULTIPLE_BASICCAN */
          /* #100 search for all pending BasicCAN mailbox objects and call notification */
          CanHL_RxBasicCanPolling(CAN_HW_CHANNEL_CANPARA_ONLY);
# endif
        }
      }
    }
#endif /* C_ENABLE_RX_POLLING */
#if defined(C_ENABLE_RX_QUEUE)
    /* #200 execute RxQueue CanHL_RxQueueExecution() */
    CanHL_RxQueueExecution(); 
#endif
    canIsRxTaskLocked = kCanFalse;
  }

  /* ----- Development Error Report --------------------------------------- */
#if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR) /* PRQA S 2992,2996 */ /* MD_Can_ConstValue */
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_MAINFCT_READ_ID, errorId); /* PRQA S 2880 */ /*  MD_MSR_Unreachable */
  }
#else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
  CanHookEnd_Can_MainFunction_Read();
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/****************************************************************************
| NAME:             Can_MainFunction_BusOff
****************************************************************************/
/*
|<DataModelStart>| Can_MainFunction_BusOff
Relation_Context:
Relation:
StatusPolling, DevErrorDetect, ChannelAmount
StatusPolling, OneChOpt
StatusPolling, Variant, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
V_DEF_FUNC(V_NONE, void, CODE) Can_MainFunction_BusOff( void )
{ /* \trace SPEC-1783 */
  /* ----- Local Variables ---------------------------------------------- */
#if defined(C_ENABLE_ERROR_POLLING) /* \trace SPEC-1778 */ /* COV_CAN_ERROR_POLLING */
  CAN_CHANNEL_CANTYPE_LOCAL
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* #10 Check Driver is initialized \trace SPEC-1780 */
    errorId = CAN_E_UNINIT;
  }
  else
# endif
  {  
    /* ----- Implementation ----------------------------------------------- */
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
    for (channel = 0u; channel < kCanNumberOfChannels; channel++)
# endif
    { /* #20 over all active controller */
# if (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON) /* one controller optimization is always off */
      if ( Can_GetCanIfChannelId(channel) == kCanChannelNotUsed ) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
      { /* not for inactive controller */
        continue;
      }
# endif
# if (CAN_DEV_ERROR_DETECT == STD_ON)
      if (!CanHL_IsControllerInit(channel))
      { /* #50 Check controller is initialized */
        errorId = CAN_E_UNINIT;
      }
      else
# endif
      {
        if ( !CanHL_IsSleep(channel) )
        { /* #60 do not access CAN hardware in SLEEP */
          /* #80 disable CAN interrupts */
          Can_DisableControllerInterrupts((uint8)channel);
          /* #90 call CanHL_ErrorHandling */
          CanHL_ErrorHandling( CAN_HW_CHANNEL_CANPARA_ONLY );
          Can_EnableControllerInterrupts((uint8)channel);
        }
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_MAINFCT_BO_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
#endif /* C_ENABLE_ERROR_POLLING */
}


/****************************************************************************
| NAME:             Can_MainFunction_Wakeup
****************************************************************************/
/*
|<DataModelStart>| Can_MainFunction_Wakeup
Relation_Context:
Relation:
WakeupPolling, Wakeup, DevErrorDetect
WakeupPolling, Wakeup, OneChOpt
WakeupPolling, Wakeup, Variant
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
V_DEF_FUNC(V_NONE, void, CODE) Can_MainFunction_Wakeup( void )
{ /* \trace SPEC-1770 */
  /* ----- Local Variables ---------------------------------------------- */
}

/****************************************************************************
| NAME:             Can_MainFunction_Mode
****************************************************************************/
/*
|<DataModelStart>| Can_MainFunction_Mode
Relation_Context:
Relation:
DevErrorDetect
OneChOpt, ChannelAmount
Variant, ChannelAmount
DevErrorDetect, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
V_DEF_FUNC(V_NONE, void, CODE) Can_MainFunction_Mode( void )
{ /* \trace SPEC-1775 */
  /* ----- Local Variables ---------------------------------------------- */
  CAN_CHANNEL_CANTYPE_LOCAL
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* #10 Check Driver is initialized \trace SPEC-1779 */
    errorId = CAN_E_UNINIT;
  }
  else
# endif
  { /* #15 EXCLUSIVE_AREA_6 avoid nesting mode changes (e.g. same API, initialization or BUSOFF) */
    /* ----- Implementation ----------------------------------------------- */
    SchM_Enter_Can_CAN_EXCLUSIVE_AREA_6();
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
    for (channel = 0u; channel < kCanNumberOfChannels; channel++) /* CM_CAN_HL01 */
# endif
    { /* #20 over all active controller */
# if (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON) /* one controller optimization is always off */
      if ( Can_GetCanIfChannelId(channel) == kCanChannelNotUsed ) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
      { /* not for inactive controller */
        continue;
      }
# endif
# if (CAN_DEV_ERROR_DETECT == STD_ON)
      if (!CanHL_IsControllerInit(channel))
      { /* #50 Check controller is initialized */ /* \trace SPEC-1779 */
        errorId = CAN_E_UNINIT;
      }
      else
# endif
      {
        uint8 transitionRequest;
        uint8 busOffRecovery;
        uint8 doRamCheck;
        uint8 transitionState;
        transitionRequest = Can_GetModeTransitionRequest(channel);
        busOffRecovery = Can_GetBusOffTransitionRequest(channel);
        doRamCheck = Can_GetRamCheckTransitionRequest(channel);
        /* #55 only one transition request at one time is possible - execute it \trace SPEC-1771 */
        if(transitionRequest != kCanModeNone)
        {
          transitionState = CanLL_ModeTransition(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST transitionRequest, busOffRecovery, doRamCheck);
          switch(transitionRequest)
          {
            case kCanModeStopReinitFast: /* COV_CAN_TRANSITION_REQUEST */
            case kCanModeStopReinit: /* COV_CAN_TRANSITION_REQUEST */
              CanHL_NotifyTransition(CAN_CHANNEL_CANPARA_FIRST CAN_STATUS_STOP, CANIF_CS_STOPPED, transitionState);
              break;
# if (CAN_REINIT_START == STD_ON)
            case kCanModeStartReinit: /* COV_CAN_TRANSITION_REQUEST */
# else
            case kCanModeStart: /* COV_CAN_TRANSITION_REQUEST */
# endif
            case kCanModeResetBusOffEnd: /* COV_CAN_TRANSITION_REQUEST */
# if defined(C_ENABLE_SILENT_MODE)
            case kCanModeSilent: /* COV_CAN_TRANSITION_REQUEST */
# endif
              CanHL_NotifyTransition(CAN_CHANNEL_CANPARA_FIRST CAN_STATUS_START, CANIF_CS_STARTED, transitionState);
              if ( transitionState == kCanOk ) /* COV_CAN_TRANSITION_REQUEST */
              {
                Can_SetIsBusOff(channel, FALSE); /* SBSW_CAN_HL08 */
              }
              break;
            case kCanModeResetBusOffStart: /* COV_CAN_TRANSITION_REQUEST */ /* not expected, no repetition request */
            default: /* COV_CAN_TRANSITION_REQUEST */
              break;
          }
        }
      }
    } /* over all channels */
    SchM_Exit_Can_CAN_EXCLUSIVE_AREA_6();
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_MAINFCT_MODE_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
} /* PRQA S 6030,6080 */ /* MD_MSR_STCYC,MD_MSR_STMIF */


/****************************************************************************
| NAME:             Can_CancelTx
****************************************************************************/
/*
|<DataModelStart>| Can_CancelTx
Relation_Context:
TransmitCancellationAPI
Relation:
DevErrorDetect, TxFullCANSupport
OneChOpt
DevErrorDetect, OneChOpt
DevErrorDetect, Variant
TxFullCANSupport, HwCancelTx
ChannelAmount
TxFullAmount
TxBasicAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
V_DEF_FUNC(V_NONE, void, CODE) Can_CancelTx( Can_HwHandleType Hth, PduIdType PduId )
{
  /* ----- Local Variables ---------------------------------------------- */
#if defined(C_ENABLE_CANCEL_SUPPORT_API)
  CAN_CHANNEL_CANTYPE_LOCAL
  tCanTxCancellationParaStruct txCancellationPara;
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* #10 Check Driver is initialized */
    errorId = CAN_E_UNINIT;
  }
  else
  if (Hth >= Can_GetSizeOfMailbox())
  { /* #20 Check Hth is in range */
    errorId = CAN_E_PARAM_HANDLE;
  }
  else
#  if defined(C_ENABLE_TX_FULLCAN_OBJECTS)
  if ((Can_GetMailboxType(Hth) != CAN_TX_BASICCAN_TYPE) && (Can_GetMailboxType(Hth) != CAN_TX_BASICCAN_MUX_TYPE) && (Can_GetMailboxType(Hth) != CAN_TX_BASICCAN_FIFO_TYPE) && (Can_GetMailboxType(Hth) != CAN_TX_FULLCAN_TYPE)) /* COV_CAN_GENDATA_TX_NOT_IN_ALL_CONFIG */
#  else
  if ((Can_GetMailboxType(Hth) != CAN_TX_BASICCAN_TYPE) && (Can_GetMailboxType(Hth) != CAN_TX_BASICCAN_MUX_TYPE) && (Can_GetMailboxType(Hth) != CAN_TX_BASICCAN_FIFO_TYPE)) /* COV_CAN_GENDATA_TX_NOT_IN_ALL_CONFIG */
#  endif
  { /* #30 Check Hth is FullCAN or BasicCAN */
    errorId = CAN_E_PARAM_HANDLE;
  }
  else
# endif
  {
# if !defined( C_SINGLE_RECEIVE_CHANNEL ) /* otherwise 'channel' is a define */
    channel = Can_GetMailboxController(Hth);
# endif
# if (CAN_DEV_ERROR_DETECT == STD_ON)
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
    if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */ /* COV_CAN_GENDATA_FAILURE */
    { /* #40 Check parameter controller is in range */
      errorId = CAN_E_PARAM_CONTROLLER;
    }
    else
#  endif
#  if (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
    if (Can_GetCanIfChannelId(channel) == kCanChannelNotUsed) /* COV_CAN_GENDATA_FAILURE */
    { /* #60 Check parameter controller is valid */
      errorId = CAN_E_PARAM_CONTROLLER;
    }
    else
#  endif
    if (!CanHL_IsControllerInit(channel))
    { /* #70 Check controller is initialized */
      errorId = CAN_E_UNINIT;
    }
    else
# endif
    {
      /* ----- Implementation ----------------------------------------------- */
      txCancellationPara.mailboxHandle = Hth;
# if defined(C_ENABLE_CANCEL_TX_IN_HW)
      txCancellationPara.hwObjHandle = Can_GetMailboxHwHandle(Hth);
# endif
      txCancellationPara.mailboxElement = 0u;
      txCancellationPara.activeSendObject = CanHL_GetActiveSendObject(txCancellationPara.mailboxHandle, txCancellationPara.mailboxElement);

# if defined (C_ENABLE_TX_FULLCAN_OBJECTS)
      if ( Can_GetMailboxType(Hth) != CAN_TX_FULLCAN_TYPE ) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
# endif
      { /* #100 is BasicCAN */
# if defined(C_ENABLE_MULTIPLEXED_TRANSMISSION) 
        for (; txCancellationPara.mailboxElement < Can_GetMailboxSize(Hth); txCancellationPara.mailboxElement++, txCancellationPara.activeSendObject++) /* PRQA S 3418 */ /* MD_Can_IncompleteForLoop */
# endif
        { /* #110 over all Multiplexed TX objects - search for handle */
          if (Can_GetActiveSendPdu(txCancellationPara.activeSendObject) == PduId)
          {
            if ((Can_GetActiveSendState(txCancellationPara.activeSendObject) == kCanBufferSend)
# if defined(C_ENABLE_CANCEL_TX_IN_HW)
                || (Can_GetActiveSendState(txCancellationPara.activeSendObject) == kCanBufferCancel)
# endif
                )  /* COV_CAN_CANCEL_SW_STIMULATION */
            { /* #120 PDU found in active send list - handle found */
              /* #130 CANCEL_IN_HW is active - just suppress TX confirmation */
# if defined(C_ENABLE_CANCEL_IN_HW)
              { /* #140 LL TX cancel in HW */ /* \trace SPEC-1690 */
                /* #150 mark as to be cancelled by hardware */
                txCancellationPara.canHandleCurTxObj = kCanBufferCancelSw;
                CanLL_TxCancelInHw(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &txCancellationPara); /* SBSW_CAN_HL47 */
                Can_SetActiveSendState(txCancellationPara.activeSendObject, kCanBufferCancelSw); /* SBSW_CAN_HL04 */
              }
# else
              Can_SetActiveSendState(txCancellationPara.activeSendObject, kCanBufferCancelSw); /* mark as cancelled by SW */ /* SBSW_CAN_HL04 */
# endif
# if defined(C_ENABLE_MULTIPLEXED_TRANSMISSION) 
              break;
# endif
            }
          }
        }
      }
# if defined (C_ENABLE_TX_FULLCAN_OBJECTS)
      else
      { /* #200 is FullCAN */
        if (Can_GetActiveSendPdu(txCancellationPara.activeSendObject) == PduId)
        {
          if ((Can_GetActiveSendState(txCancellationPara.activeSendObject) == kCanBufferSend)
#  if defined(C_ENABLE_CANCEL_TX_IN_HW)
              || (Can_GetActiveSendState(txCancellationPara.activeSendObject) == kCanBufferCancel)
#  endif
             )  /* COV_CAN_CANCEL_SW_STIMULATION */
          { /* #210 mailbox to cancel is valid (PDU, handle, send state OK) */
            /* #220 CANCEL_FULLCAN_IN_HW is active - just suppress TX confirmation */
#  if defined(C_ENABLE_CANCEL_TX_IN_HW)
            { /* #230 LL TX cancel in HW */ /* \trace SPEC-1690 */
              /* #150 mark as to be cancelled by hardware */
              txCancellationPara.canHandleCurTxObj = kCanBufferCancelSw;
              CanLL_TxCancelInHw(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &txCancellationPara); /* SBSW_CAN_HL47 */
              Can_SetActiveSendState(txCancellationPara.activeSendObject, kCanBufferCancelSw); /* mark as cancelled by SW */ /* SBSW_CAN_HL04 */
            }
#  endif
            Can_SetActiveSendState(txCancellationPara.activeSendObject, kCanBufferCancelSw); /* mark as cancelled by SW */ /* SBSW_CAN_HL04 */
          }
        }
      }
# endif
    }
    CAN_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  }
  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_WRITE_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
#else /* CAN_ENABLE_CANCEL_SUPPORT_API */
  CAN_DUMMY_STATEMENT(Hth); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CAN_DUMMY_STATEMENT(PduId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif /* CAN_ENABLE_CANCEL_SUPPORT_API */
} /* PRQA S 6030,6080 */ /* MD_MSR_STCYC,MD_MSR_STMIF */

#if (CAN_GET_STATUS == STD_ON)
/****************************************************************************
| NAME:             Can_GetStatus
****************************************************************************/
/*
|<DataModelStart>| Can_GetStatus
Relation_Context:
CanGetStatus
Relation:
DevErrorDetect, OneChOpt
DevErrorDetect, Variant
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
V_DEF_FUNC(V_NONE, uint8, CODE) Can_GetStatus( uint8 Controller )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 canReturnCode;
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  canReturnCode = CAN_STATUS_INCONSISTENT; /* PRQA S 2982 */ /* MD_MSR_RetVal */
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller is valid and state is INIT */
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* #20 Check Driver is initialized */
    errorId = CAN_E_UNINIT;
  }
  else
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
#  if (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
  if (Can_GetCanIfChannelId(channel) == kCanChannelNotUsed) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
  if (!CanHL_IsControllerInit(channel))
  { /* #50 Check controller is initialized */
    errorId = CAN_E_UNINIT;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    CanLL_GetStatusBegin(CAN_CHANNEL_CANPARA_ONLY); /* PRQA S 2987 */ /* MD_Can_EmptyFunction */
    /* #100 set logical state as return value */
    canReturnCode = (uint8)Can_GetLogStatus(channel);
    if ( CanLL_HwIsBusOff(channel) ) /* COV_CAN_HARDWARE_FAILURE */
    { /* #150 set BUSOFF - BUSOFF can only happen on first HW channel (with TX objects) */
      canReturnCode |= CAN_STATUS_BUSOFF;
    }
# if defined(C_ENABLE_EXTENDED_STATUS) /* COV_CAN_EXTENDED_STATUS */
    {    
      if ( CanLL_HwIsPassive(channel) ) /* COV_CAN_HARDWARE_FAILURE */
      { /* #160 set Error Passive */
        canReturnCode |= CAN_STATUS_PASSIVE;
      }    
      if ( CanLL_HwIsWarning(channel) ) /* COV_CAN_HARDWARE_FAILURE */
      { /* #170 set Error Warning */
        canReturnCode |= CAN_STATUS_WARNING;
      }
    }
# endif /* C_ENABLE_EXTENDED_STATUS */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_HW_ACCESS_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
# if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  return (uint8)canReturnCode;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/****************************************************************************
| NAME:             Can_GetControllerMode
****************************************************************************/
/*
|<DataModelStart>| Can_GetControllerMode
Relation_Context:
CanGetStatus
Relation:
DevErrorDetect, OneChOpt
DevErrorDetect, Variant
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
V_DEF_FUNC(V_NONE, Std_ReturnType, CODE) Can_GetControllerMode( uint8 Controller, Can_ControllerStatePtrType ControllerModePtr )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType canReturnCode;
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  canReturnCode = E_NOT_OK; /* PRQA S 2982 */ /* MD_MSR_RetVal */
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameters are valid */
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* #20 Check Driver is initialized */
    errorId = CAN_E_UNINIT;
  }
  else
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
#  if (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
  if (Can_GetCanIfChannelId(channel) == kCanChannelNotUsed) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
  if (ControllerModePtr == NULL_PTR)
  {
    errorId = CAN_E_PARAM_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 get logical controller mode from state machine variable */
    if (!CanHL_IsControllerInit(channel))
    {
      *ControllerModePtr = CAN_CS_UNINIT; /* SBSW_CAN_HL51 */
    }
    else if (CanHL_IsStart(channel))
    {
      *ControllerModePtr = CAN_CS_STARTED; /* SBSW_CAN_HL51 */
    } 
    else if (CanHL_IsSleep(channel))
    {
      *ControllerModePtr = CAN_CS_SLEEP; /* SBSW_CAN_HL51 */
    }
    else /* default is:   if (CanHL_IsStop(channel)) */
    {
      *ControllerModePtr = CAN_CS_STOPPED; /* SBSW_CAN_HL51 */
    }
    canReturnCode = E_OK;
  }
  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_GETCTR_MODE_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
# if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  return canReturnCode;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/****************************************************************************
| NAME:             Can_GetControllerErrorState
****************************************************************************/
/*
|<DataModelStart>| Can_GetControllerErrorState
Relation_Context:
CanGetStatus
Relation:
DevErrorDetect, OneChOpt
DevErrorDetect, Variant
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
V_DEF_FUNC(V_NONE, Std_ReturnType, CODE) Can_GetControllerErrorState( uint8 Controller, Can_ErrorStatePtrType ErrorStatePtr )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType canReturnCode;
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  canReturnCode = E_NOT_OK; /* PRQA S 2982 */ /* MD_MSR_RetVal */
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller is valid and state is INIT */
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* Check Driver is initialized */
    errorId = CAN_E_UNINIT;
  }
  else
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
#  if (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
  if (Can_GetCanIfChannelId(channel) == kCanChannelNotUsed) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
  if (!CanHL_IsControllerInit(channel))
  { /* Check controller is initialized */
    errorId = CAN_E_UNINIT;
  }
  else
  if (ErrorStatePtr == NULL_PTR)
  {
    errorId = CAN_E_PARAM_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    CanLL_GetStatusBegin(CAN_CHANNEL_CANPARA_ONLY); /* PRQA S 2987 */ /* MD_Can_EmptyFunction */
    if ( CanLL_HwIsBusOff(channel) ) /* COV_CAN_HARDWARE_FAILURE */
    { /* #40 set BUSOFF */
      *ErrorStatePtr = CAN_ERRORSTATE_BUSOFF; /* SBSW_CAN_HL52 */
    } 
# if defined(C_ENABLE_EXTENDED_STATUS) /* COV_CAN_EXTENDED_STATUS */
    else if ( CanLL_HwIsPassive(channel) ) /* COV_CAN_HARDWARE_FAILURE */
    { /* #50 set Error Passive */
      *ErrorStatePtr = CAN_ERRORSTATE_PASSIVE; /* SBSW_CAN_HL52 */
    }
# endif /* C_ENABLE_EXTENDED_STATUS */
    else
    { /* #60 default return is ACTIVE */
      *ErrorStatePtr = CAN_ERRORSTATE_ACTIVE; /* SBSW_CAN_HL52 */
    }
    canReturnCode = E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_GETCTR_STATE_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
# if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  return canReturnCode;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/****************************************************************************
| NAME:             Can_GetControllerTxErrorCounter
****************************************************************************/
/*
|<DataModelStart>| Can_GetControllerTxErrorCounter
Relation_Context:
CanGetStatus
Relation:
DevErrorDetect, OneChOpt
DevErrorDetect, Variant
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 */
V_DEF_FUNC(V_NONE, Std_ReturnType, CODE) Can_GetControllerTxErrorCounter( uint8 Controller, Can_ErrorCounterPtrType TxErrorCounterPtr )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType canReturnCode;
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  canReturnCode = E_NOT_OK; /* PRQA S 2982 */ /* MD_MSR_RetVal */
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller is valid and state is INIT */
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* Check Driver is initialized */
    errorId = CAN_E_UNINIT;
  }
  else
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
#  if (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
  if (Can_GetCanIfChannelId(channel) == kCanChannelNotUsed) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
  if (!CanHL_IsControllerInit(channel))
  { /* Check controller is initialized */
    errorId = CAN_E_UNINIT;
  }
  else
  if (TxErrorCounterPtr == NULL_PTR)
  {
    errorId = CAN_E_PARAM_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #40 get error counter from hardware */
# if defined( C_SINGLE_RECEIVE_CHANNEL )
    *TxErrorCounterPtr = CanTxActualErrorCounter(); /* SBSW_CAN_HL53 */
# else
    *TxErrorCounterPtr = CanTxActualErrorCounter(channel); /* SBSW_CAN_HL53 */
# endif
    canReturnCode = E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_GETCTR_TXCNT_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
# if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  return canReturnCode;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/****************************************************************************
| NAME:             Can_GetControllerRxErrorCounter
****************************************************************************/
/*
|<DataModelStart>| Can_GetControllerRxErrorCounter
Relation_Context:
CanGetStatus
Relation:
DevErrorDetect, OneChOpt
DevErrorDetect, Variant
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 */
V_DEF_FUNC(V_NONE, Std_ReturnType, CODE) Can_GetControllerRxErrorCounter( uint8 Controller, Can_ErrorCounterPtrType RxErrorCounterPtr )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType canReturnCode;
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  canReturnCode = E_NOT_OK; /* PRQA S 2982 */ /* MD_MSR_RetVal */
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller is valid and state is INIT */
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* Check Driver is initialized */
    errorId = CAN_E_UNINIT;
  }
  else
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
#  if (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
  if (Can_GetCanIfChannelId(channel) == kCanChannelNotUsed) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
  if (!CanHL_IsControllerInit(channel))
  { /* Check controller is initialized */
    errorId = CAN_E_UNINIT;
  }
  else
  if (RxErrorCounterPtr == NULL_PTR)
  {
    errorId = CAN_E_PARAM_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #40 get error counter from hardware */
# if defined( C_SINGLE_RECEIVE_CHANNEL )
    *RxErrorCounterPtr = CanRxActualErrorCounter(); /* SBSW_CAN_HL54 */
# else
    *RxErrorCounterPtr = CanRxActualErrorCounter(channel); /* SBSW_CAN_HL54 */
# endif
    canReturnCode = E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_GETCTR_RXCNT_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
# if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  return canReturnCode;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

#endif

#if defined(C_ENABLE_MIRROR_MODE)
/****************************************************************************
| NAME:             Can_SetMirrorMode
****************************************************************************/
/*
|<DataModelStart>| Can_SetMirrorMode
Relation_Context:
MirrorMode
Relation:
DevErrorDetect, OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
V_DEF_FUNC(V_NONE, void, CODE) Can_SetMirrorMode( uint8 Controller, CddMirror_MirrorModeType mirrorMode )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* #10 Check Driver is initialized */
    errorId = CAN_E_UNINIT;
  }
  else
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  { /* #20 Check parameter controller is in range */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
# endif
  { /* #30 set mirror mode for given controller */
    /* ----- Implementation ----------------------------------------------- */
    Can_SetMirrorModeState(channel, mirrorMode); /* SBSW_CAN_HL20 */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_HW_ACCESS_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
# if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
}
#endif

#if defined(C_ENABLE_SILENT_MODE)
/****************************************************************************
| NAME:             Can_SetSilentMode
****************************************************************************/
/*
|<DataModelStart>| Can_SetSilentMode
Relation_Context:
SilentMode
Relation:
DevErrorDetect, OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
V_DEF_FUNC(V_NONE, Std_ReturnType, CODE) Can_SetSilentMode( uint8 Controller, Can_SilentModeType silentMode )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  Std_ReturnType retval;
  errorId = CAN_E_NO_ERROR;
  retval = E_NOT_OK; /* PRQA S 2982 */ /* MD_MSR_RetVal */
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* #10 Check Driver is initialized */
    errorId = CAN_E_UNINIT;
  }
  else
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  { /* #20 Check parameter controller is in range */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
# endif
  { /* #30 set silent mode for given controller */
    /* ----- Implementation ----------------------------------------------- */
    Can_SetSilentModeState(channel, silentMode); /* SBSW_CAN_HL20 */
    retval = E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_HW_ACCESS_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
# if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  return retval;
}
#endif

#if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
/****************************************************************************
| NAME:             Can_RamCheckExecute
****************************************************************************/
/*
|<DataModelStart>| Can_RamCheckExecute
Relation_Context:
Relation:
RamCheck, DevErrorDetect, OneChOpt, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
V_DEF_FUNC(V_NONE, void, CODE) Can_RamCheckExecute( uint8 Controller )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* #10 Check Driver is initialized */
    errorId = CAN_E_UNINIT;
  }
  else
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  { /* #20 Check parameter controller is in range */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
# endif
  { /* #30 Do RamCheck by execute reinitialization with activated check */
    uint8 transitionState;
    /* ----- Implementation ----------------------------------------------- */
    transitionState = CanHL_ModeTransition(CAN_CHANNEL_CANPARA_FIRST kCanModeStopReinit, kCanFinishBusOffRecovery, kCanExecuteRamCheck);
    if (transitionState == kCanOk) /* COV_CAN_TRANSITION_REQUEST */
    { /* #40 check transition STOP (Reinit) is successful */
      Can_SetLogStatus(channel, Can_GetLogStatus(channel) | CAN_STATUS_STOP); /* STOP mode reached */ /* SBSW_CAN_HL02 */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_HW_ACCESS_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
# if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
}

/****************************************************************************
| NAME:             Can_RamCheckEnableMailbox
****************************************************************************/
/*
|<DataModelStart>| Can_RamCheckEnableMailbox
Relation_Context:
Relation:
RamCheck, DevErrorDetect
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
V_DEF_FUNC(V_NONE, void, CODE) Can_RamCheckEnableMailbox( Can_HwHandleType htrh )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* #10 Check Driver is initialized */
    errorId = CAN_E_UNINIT;
  }
  else
  if (htrh >= Can_GetSizeOfMailbox()) { /* CM_CAN_HL28 */
    errorId = CAN_E_PARAM_HANDLE;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #15 disable controller to force reinitialization afterwards in Can_RamCheckEnableController() */
    Can_SetLogStatus(Can_GetMailboxController(htrh), CAN_DEACTIVATE_CONTROLLER); /* SBSW_CAN_HL40 */
    /* #20 reactivate mailbox */
    Can_SetMailboxState(htrh, kCanOk); /* SBSW_CAN_HL34 */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_HW_ACCESS_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
}

/****************************************************************************
| NAME:             Can_RamCheckEnableController
****************************************************************************/
/*
|<DataModelStart>| Can_RamCheckEnableController
Relation_Context:
RamCheck
Relation:
DevErrorDetect, OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
V_DEF_FUNC(V_NONE, void, CODE) Can_RamCheckEnableController( uint8 Controller )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* #10 Check Driver is initialized */
    errorId = CAN_E_UNINIT;
  }
  else
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  { /* #20 Check parameter controller is in range */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 activate controller only when currently disabled */
    if ( (Can_GetLogStatus(channel) & CAN_DEACTIVATE_CONTROLLER) == CAN_DEACTIVATE_CONTROLLER ) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
    {
      uint8 transitionState;
      /* #40 re-initialize to activate mailboxes and controller after RAM check issue */
      Can_SetLogStatus(channel, Can_GetLogStatus(channel) & (uint8)(~(CAN_DEACTIVATE_CONTROLLER))); /* SBSW_CAN_HL02 */
      transitionState = CanHL_ModeTransition(CAN_CHANNEL_CANPARA_FIRST kCanModeStopReinit, kCanFinishBusOffRecovery, kCanSuppressRamCheck);
      if (transitionState == kCanOk) /* COV_CAN_TRANSITION_REQUEST */
      { /* #40 check transition STOP (Reinit) is successful */
        Can_SetLogStatus(channel, Can_GetLogStatus(channel) | CAN_STATUS_STOP); /* STOP mode reached */ /* SBSW_CAN_HL02 */
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_HW_ACCESS_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
# if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
}
#endif


#if defined( C_ENABLE_INTERRUPT_SOURCE_SINGLE ) /* COV_CAN_FLEXCAN3_DERIVATIVE_INTERRUPT_SOURCE_SINGLE */
# if defined( C_ENABLE_CAN_RXTX_INTERRUPT )   || \
     defined( C_ENABLE_CAN_BUSOFF_INTERRUPT ) 
/* **************************************************************************
| NAME:             CanInterrupt<Name>
| CALLED BY:        CanIsr<Name>_<physicalChannelIndex>()
| PRECONDITIONS:
| INPUT PARAMETERS: canHwChannel
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service functions according to the CAN controller
|                   interrupt structure
|                   - check for the interrupt reason ( interrupt source )
|                   - work appropriate interrupt:
|                     + status/error interrupt (BUSOFF, wakeup, error warning)
|                     + basic can receive
|                     + full can receive
|                     + can transmit
|
|                   If an RX-Interrupt occurs while the CAN controller is in Sleep mode, 
|                   a wakeup has to be generated. 
|
|                   If an TX-Interrupt occurs while the CAN controller is in Sleep mode, 
|                   an assertion has to be called and the interrupt has to be ignored.
|
|                   The name of BrsTimeStrt...() and BrsTimeStop...() can be adapted to 
|                   really used name of the interrupt functions.
|
************************************************************************** */
/*
|<DataModelStart>| CanInterrupt
Relation_Context:
# from CanIsr_0 #
TxPolling,RxPolling,IndividualPolling,StatusPolling,WakeupPolling,UseNestedCANInterrupts
# from CanIsr_1 #
TxPolling,RxPolling,IndividualPolling,StatusPolling,WakeupPolling,UseNestedCANInterrupts
# from CanIsr_2 #
TxPolling,RxPolling,IndividualPolling,StatusPolling,WakeupPolling,UseNestedCANInterrupts
# from CanIsr_3 #
TxPolling,RxPolling,IndividualPolling,StatusPolling,WakeupPolling,UseNestedCANInterrupts
Relation:
OneChOpt
DevErrorDetect
StatusPolling,WakeupPolling
TxPolling,RxPolling,IndividualPolling
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
 *
 *
*/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(V_NONE, void, CODE) CanInterrupt( CAN_HW_CHANNEL_CANTYPE_ONLY )
{
# if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
  if (CanLL_CheckSizeOfHwChannelData( canHwChannel ) == kCanOk) /* COV_CAN_GENDATA_FAILURE */  /* CM_CAN_LL07 */
# endif
  {
#  if defined( C_ENABLE_CAN_BUSOFF_INTERRUPT )
    tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);
#  endif
  
#   if (CAN_RUNTIME_MEASUREMENT_SUPPORT == STD_ON)
    Rtm_Start(RtmConf_RtmMeasurementPoint_CanInterrupt);
#   endif


#  if defined( C_ENABLE_CAN_BUSOFF_INTERRUPT )
    {
      if((pFlexCANLocal->estat & kFlexCAN_BOFF_INT) != 0u) /* COV_CAN_BUSOFF_INTERRUPT_ONLY */
      {
        CanHL_ErrorHandling( CAN_HW_CHANNEL_CANPARA_ONLY );
      }
    }
#  endif

#  if defined( C_ENABLE_CAN_RXTX_INTERRUPT )
    /*  #30 Process mailbox interrupt */
    CanLL_CanMailboxInterrupt(CAN_HW_CHANNEL_CANPARA_ONLY);
#  endif /* C_ENABLE_CAN_RXTX_INTERRUPT */

#   if (CAN_RUNTIME_MEASUREMENT_SUPPORT == STD_ON)
    Rtm_Stop(RtmConf_RtmMeasurementPoint_CanInterrupt);
#   endif
  }
} /* end of CanInterrupt */
/* CODE CATEGORY 1 END */
# endif
#endif /* C_ENABLE_INTERRUPT_SOURCE_SINGLE */

#if defined ( C_ENABLE_INTERRUPT_SOURCE_MULTIPLE ) /* COV_CAN_FLEXCAN3_DERIVATIVE_INTERRUPT_SOURCE_MULTIPLE */
# if defined( C_ENABLE_CAN_BUSOFF_INTERRUPT )
/****************************************************************************
| NAME:             CanBusOffInterrupt
****************************************************************************/
/*
|<DataModelStart>| CanBusOffInterrupt
Relation_Context:
# from CanBusOffIsr_0 #
StatusPolling,UseNestedCANInterrupts
# from CanBusOffIsr_1 #
StatusPolling,UseNestedCANInterrupts
# from CanBusOffIsr_2 #
StatusPolling,UseNestedCANInterrupts
# from CanBusOffIsr_3 #
StatusPolling,UseNestedCANInterrupts
# from CanBusOffIsr_4 #
StatusPolling,UseNestedCANInterrupts
# from CanBusOffIsr_5 #
StatusPolling,UseNestedCANInterrupts
# from CanBusOffIsr_6 #
StatusPolling,UseNestedCANInterrupts
# from CanBusOffIsr_7 #
StatusPolling,UseNestedCANInterrupts
Relation:
OneChOpt
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
*/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(V_NONE, void, CODE) CanBusOffInterrupt( CAN_HW_CHANNEL_CANTYPE_ONLY )
{
#   if (CAN_RUNTIME_MEASUREMENT_SUPPORT == STD_ON)
  Rtm_Start(RtmConf_RtmMeasurementPoint_CanBusOffInterrupt);
#   endif

  /* #10 Call internal indication function if BUSOFF occurred */
# if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
  if (CanLL_CheckSizeOfHwChannelData( canHwChannel ) == kCanOk) /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL07 */
# endif
  {
    CanHL_ErrorHandling( CAN_HW_CHANNEL_CANPARA_ONLY );
  }

#   if (CAN_RUNTIME_MEASUREMENT_SUPPORT == STD_ON)
  Rtm_Stop(RtmConf_RtmMeasurementPoint_CanBusOffInterrupt);
#   endif
}
/* CODE CATEGORY 1 END */
# endif
# if defined( C_ENABLE_CAN_RXTX_INTERRUPT )
/****************************************************************************
| NAME:             CanMailboxInterrupt
****************************************************************************/
/*
|<DataModelStart>| CanMailboxInterrupt
Relation_Context:
# from CanMailboxIsr_0 #
TxPolling,RxPolling,IndividualPolling,UseNestedCANInterrupts
# from CanMailboxIsr_1 #
TxPolling,RxPolling,IndividualPolling,UseNestedCANInterrupts
# from CanMailboxIsr_2 #
TxPolling,RxPolling,IndividualPolling,UseNestedCANInterrupts
# from CanMailboxIsr_3 #
TxPolling,RxPolling,IndividualPolling,UseNestedCANInterrupts
# from CanMailboxIsr_4 #
TxPolling,RxPolling,IndividualPolling,UseNestedCANInterrupts
# from CanMailboxIsr_5 #
TxPolling,RxPolling,IndividualPolling,UseNestedCANInterrupts
# from CanMailboxIsr_6 #
TxPolling,RxPolling,IndividualPolling,UseNestedCANInterrupts
# from CanMailboxIsr_7 #
TxPolling,RxPolling,IndividualPolling,UseNestedCANInterrupts
Relation:
OneChOpt
DevErrorDetect
TxPolling,RxPolling,IndividualPolling
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
*/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(V_NONE, void, CODE) CanMailboxInterrupt( CAN_HW_CHANNEL_CANTYPE_ONLY ) /* COV_CAN_MAILBOX_INT_INDIVPOLLING */
{
#   if (CAN_RUNTIME_MEASUREMENT_SUPPORT == STD_ON)
  Rtm_Start(RtmConf_RtmMeasurementPoint_CanMailboxInterrupt);
#   endif

  /* #10 Process mailbox interrupt */
# if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
  if (CanLL_CheckSizeOfHwChannelData( canHwChannel ) == kCanOk) /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL07 */
# endif
  {
    CanLL_CanMailboxInterrupt(CAN_HW_CHANNEL_CANPARA_ONLY);
  }

#   if (CAN_RUNTIME_MEASUREMENT_SUPPORT == STD_ON)
  Rtm_Stop(RtmConf_RtmMeasurementPoint_CanMailboxInterrupt);
#   endif
}
# endif
#endif /* C_ENABLE_INTERRUPT_SOURCE_MULTIPLE */

#define CAN_STOP_SEC_CODE  /*----------------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/****************************************************************************/

/****************************************************************************/
/*  excluded Requirements                                                   */
/****************************************************************************/
/* part of other component: SPEC-1597 */
/* Currently no use-case / not supported: SPEC-1601, SPEC-1592, SPEC-1582 */

/****************************************************************************/
/*  MISRA deviations                                                        */
/****************************************************************************/
/* Justification for module-specific MISRA deviations:

MD_Can_Goto:
PRQA message 2001
  Reason: 'goto' statements are used to reduce code complexity.
  Risk: Incorrect jump.
  Prevention: Code inspection and runtime tests.

MD_Can_MultipleReturn:
PRQA message 2889
  Reason: Multiple return paths are used to reduce code complexity.
  Risk: Return a function too soon.
  Prevention: Code inspection and runtime tests.

MD_Can_ParameterName:
PRQA message 0784, 0788
  Reason: A parameter that is also used as a macro name is accepted for compatibility reasons.
  Risk: The macro can change the declaration unintentionally and readability is reduced.
  Prevention: Code inspection and test of the different variants in the component test.

MD_Can_ConstValue:
PRQA message 2741, 2742, 2880, 2985, 2986, 2990, 2991, 2992, 2993, 2994, 2995, 2996
  Reason: Value is constant depending on configuration aspects or platform specific implementation. This leads to constant control expressions, unreachable code or redundant operations.
  Risk: Wrong or missing functionality.
  Prevention: Code inspection and test of the different variants in the component test.

MD_Can_EmptyFunction:
PRQA message 2987
  Reason: Function is empty depending on configuration aspects and platform specific implementation.
  Risk: Function implementation missing.
  Prevention: Code inspection and test of the different variants in the component test.

MD_Can_NoneConstParameterPointer:
PRQA message 3673
  Reason: Non-const pointer parameter is required by the internal interface or compatibility reasons but depending on the configuration or specific platform implementation the target may not always be modified.
  Risk: Read only data could be modified without intention.
  Prevention: Code inspection and test of the different variants in the component test.

MD_Can_ModuleDefine:
PRQA message 0602, 0603
  Reason: Usage of reserved identifiers with leading underscores is accepted for compatibility reasons.
  Risk: Name conflicts.
  Prevention: Compile and link of the different variants in the component and integration test.

MD_Can_RedundantInit:
PRQA message 2981
  Reason: Reduce code complexity by using an explicit variable initializer that may be always modified before being used in some configurations.
  Risk: Unintended change of value.
  Prevention: Code inspection and test of the different variants in the component test.

MD_Can_GlobalScope:
PRQA message 3218
  Reason: The usage of variables depends on configuration aspects and they may be used only once or defined globally to improve overview.
  Risk: None.
  Prevention: None.

MD_Can_ExternalScope:
PRQA message 1514, 3408, 3447, 3451, 3210
  Reason: The variable is used by other modules and can't be declared static.
  Risk: Name conflicts.
  Prevention: Compile and link of the different variants in the component and integration test.

MD_Can_GenData:
PRQA message 1533, 3408
  Reason: These constants are defined in a generated file and cannot be moved to the static source file. Visibility might be reduced by stricter switches for the declaration (kept for compatibility reasons).
  Risk: Compile or link errors.
  Prevention: Code inspection and compile-link of the different variants in the component and integration test.

MD_Can_Union:
PRQA message 0750, 0759
  Reason: Using union type to handle different data accesses.
  Risk: Misinterpreted data.
  Prevention: Code inspection and test of the different variants in the component test.

MD_Can_Assertion:
PRQA message 2842, 2897
  Reason: Assertion leads to apparent out of bounds indexing or casting an apparent negative value to an unsigned type.
  Risk: Undefined behaviour.
  Prevention: Code inspection. The assertion itself prevents the apparent anomaly.

MD_Can_PointerVoidCast:
PRQA message 0314, 0316
  Reason: API is defined with pointer to void parameter, so pointer has to be casted to or from void.
  Risk: Wrong data access or undefiend behavior for platforms where the byte alignment is not arbitrary.
  Prevention: Code inspection and test with the target compiler/platform in the component test.

MD_Can_PointerCast:
PRQA message 0310
  Reason: Different pointer type is used to access data.
  Risk: Wrong memory is accessed or alignment is incorrect.
  Prevention: Code inspection and test of different variants in the component test.

MD_Can_NoneVolatilePointerCast:
PRQA message 0312
  Reason: Cast to none volatile pointer.
  Risk: Incorrect multiple context access.
  Prevention: Code inspection checks that the value is not multiple accessed.

MD_Can_HwAccess:
PRQA message 0303
  Reason: Hardware access needs cast between a pointer to volatile object and an integral type.
  Risk: Access of unknown memory.
  Prevention: Runtime tests.

MD_Can_MixedSigns:
PRQA message 4393, 4394
  Reason: Casting from signed to unsigned types and vice versa is needed as different types are intentionally used.
  Risk: Value is changed during cast.
  Prevention: Code inspection and test of different variants in the component test.

MD_Can_IntegerCast:
PRQA message 4391, 4398, 4399, 4491
  Reason: Explicit cast to a different integer type.
  Risk: Value is changed during cast.
  Prevention: Code inspection and test of different variants in the component test.

MD_Can_CompilerAbstraction:
PRQA message 0342
  Reason: Glue operator used for compiler abstraction.
  Risk: Only K&R compiler support glue operator.
  Prevention: Compile test show whether compiler accept glue operator.

MD_Can_NoElseAfterIf:
PRQA message 2004
  Reason: No default handling needed for if-else-if here.
  Risk: Missing default handling.
  Prevention: Code inspection and test of different variants in the component test.

MD_Can_IncompleteForLoop:
PRQA message 3418
  Reason: Comma operator in for-loop header is used to get a compact code.
  Risk: Uninitialized variable.
  Prevention: Code inspection and test of different variants in the component test.


MD_Can_HL_UndefTypes:
ID 0841
  Reason: CBD types defined for CAN driver usage but should be not seen in other modules to avoid MSR-CBD mixture problems.
  Risk: None
  Prevention: None

MD_Can_3305_LL_MsgObjectAccess
PRQA message 3305
  Reason: Pointer keeps either a RX message buffer object or a HW message buffer object. Both are stored as a uint8 pointer. For access the appropriate structure is used.
  Risk: Wrong object structure might be accessed
  Prevention: Code review and runtime tests

MD_Can_LL_HwAccess:
PRQA message 0306
  Reason: Hardware access needs cast between a pointer object and an integral type in case of Virtual Addressing.
  Risk: Access of unknown memory.
  Prevention: Runtime tests.
  
MD_Can_ArraySizeUnknown:
PRQA message 3684
  Reason: Arrays declared without size, because size depends on configuration and is unknown here, especially for linktime tables.
  Risk: Data access outside table.
  Prevention: Code inspection and test of the different variants in the component test.
  
MD_Can_FlexibleStructMember:
PRQA message 	1039
  Reason: Array struct member is of size one and at the end of the struct.
  Risk: None.
  Prevention: None.
*/

/****************************************************************************/
/*  Silent deviations                                                       */
/****************************************************************************/
/* SBSW_JUSTIFICATION_BEGIN

\ID SBSW_CAN_HL01
 \DESCRIPTION Write access to CanModeTransitionRequest with controller as index. Controller index is checked against sizeof CanModeTransitionRequest in Can_SetControllerMode(), Can_RamCheckExecute(), Can_MainFunction_Mode(), Can_Init() and CanHL_ReInit().
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_HL02
 \DESCRIPTION Write access to CanLogStatus with controller as index. Controller index is checked against sizeof CanLogStatus in Can_SetControllerMode(), CanHL_ErrorHandling(), Can_RamCheckEnableController(), Can_MainFunction_Mode(), Can_Init() and CanHL_ReInit().
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_HL04
 \DESCRIPTION Write access to CanActiveSendState with activeSendObject as index. activeSendObject is checked against size of ActiveSendObject in Can_CleanUpSendState(), CanHL_WritePrepare(), CanHL_InitTxFullCAN(), CanHL_InitTxBasicCAN(), CanHL_TxTaskCancelationHandling(), CanHL_TxConfirmation() and Can_CancelTx().
 \COUNTERMEASURE \R [CM_CAN_HL03]

\ID SBSW_CAN_HL05
 \DESCRIPTION Write access to CanActiveSendPdu with activeSendObject as index. activeSendObject is checked against size of ActiveSendObject.
 \COUNTERMEASURE \R [CM_CAN_HL03]

\ID SBSW_CAN_HL06
 \DESCRIPTION Call Can_GenericPrecopy() and CanIf_RxIndication() with parameter RX Queue data pointer. The data pointer is only used for read access and it is always a valid pointer (module local defined).
 \COUNTERMEASURE \R [CM_CAN_HL25]

\ID SBSW_CAN_HL07
 \DESCRIPTION Call Can_GenericPrecopy() and CanIf_RxIndication() with parameter Rx Struct data pointer. The data pointer is only used for read access. Parameter is of type P2CONST in API.
 \COUNTERMEASURE \N [CM_CAN_HL31]

\ID SBSW_CAN_HL08
 \DESCRIPTION Write access to CanIsBusOff with controller as index. Controller index is checked against sizeof CanIsBusOff in Can_SetControllerMode(), CanHL_ErrorHandling() and Can_Init().
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_HL09
 \DESCRIPTION Write access to CanIsWakeup with controller as index. Controller index is checked against sizeof CanIsWakeup in CanHL_WakeUpHandling(), Can_CheckWakeup(), reinitialization and Can_Init().
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_HL10
 \DESCRIPTION Write access to VersionInfo pointer within function Can_GetVersionInfo()
 \COUNTERMEASURE \N caller of Can_GetVersionInfo() has to ensure that VersionInfo pointer is valid. (global description available)

\ID SBSW_CAN_HL11
 \DESCRIPTION Write access to CanLastInitObject with controller as index. Controller index is checked against sizeof CanLastInitObject in CanHL_ReInit(), Can_ChangeBaudrate(), Can_SetBaudrate() and Can_Init().
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_HL12
 \DESCRIPTION Write access to CanInterruptCounter with controller as index. Controller index is checked against sizeof CanInterruptCounter in Can_Init(), Can_EnableControllerInterrupts() and Can_DisableControllerInterrupts()
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_HL16
 \DESCRIPTION Call CanLL_CanInterruptDisable() with parameter CanInterruptOldStatus as pointer (compiler secures used type in function declaration fitting to given pointer parameter type).
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_HL18
 \DESCRIPTION Write access to CanRxQueueBuffer with queue write index. Write index is checked against size of CanRxQueueBuffer.
 \COUNTERMEASURE \R [CM_CAN_HL24]

\ID SBSW_CAN_HL19
 \DESCRIPTION Write access to CanRxQueueBuffer.data with queue write index and data index. Write index is checked against size of CanRxQueueBuffer. (see also generator CM_CAN_HL04 qualified use case CSL02)
 \COUNTERMEASURE \R [CM_CAN_HL24]
                 \R [CM_CAN_HL17]

\ID SBSW_CAN_HL20
 \DESCRIPTION Write access to CanMirrorModeState with controller as index. Controller is checked against size of CanMirrorModeState.
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_HL22
 \DESCRIPTION Write access to ActiveSendData with activeSendData + length as index. Index is checked against size of table.
 \COUNTERMEASURE \R [CM_CAN_HL20]

\ID SBSW_CAN_HL23
 \DESCRIPTION Write access to ActiveSendObject stuct with activeSendObject as index. activeSendObject is checked against size of CanActiveSendObject.
 \COUNTERMEASURE \R [CM_CAN_HL03]

\ID SBSW_CAN_HL24
 \DESCRIPTION Call Appl_GenericPreTransmit() with parameter PduInfoPtr_var pointer (module local defined).
 \COUNTERMEASURE \N The pointer is static and always valid.

\ID SBSW_CAN_HL25
 \DESCRIPTION Call CanIf_CancelTxConfirmation() with parameter CanActiveSendObject.PduInfo[activeSendObject] as pointer with activeSendObject as index. activeSendObject is checked against size of CanActiveSendObject.
 \COUNTERMEASURE \R [CM_CAN_HL03]

\ID SBSW_CAN_HL26
 \DESCRIPTION Call CanHL_RxBasicMsgReceivedBegin(), CanHL_RxMsgReceivedNotification() and CanHL_RxBasicMsgReceivedEnd() with parameter rxBasicPara pointer (module local defined).
 \COUNTERMEASURE \N The pointer is static and always valid.

\ID SBSW_CAN_HL27
 \DESCRIPTION Call CanHL_RxFullMsgReceivedBegin(), CanHL_RxFullReceivedNotification() and CanHL_RxFullMsgReceivedEnd() with parameter rxFullPara pointer (module local defined).
 \COUNTERMEASURE \N The pointer is static and always valid.

\ID SBSW_CAN_HL29
 \DESCRIPTION Write access to rxBasicPara (module local defined).
 \COUNTERMEASURE \N The structure is static and always valid.

\ID SBSW_CAN_HL30
 \DESCRIPTION Write access to rxFullPara (module local defined).
 \COUNTERMEASURE \N The structure is static and always valid.

\ID SBSW_CAN_HL31
 \DESCRIPTION Call Initialization subroutines with initPara pointer as parameter (local defined).
 \COUNTERMEASURE \N The structure is static and always valid (pointer to a local stack variable)

\ID SBSW_CAN_HL32
 \DESCRIPTION Call Appl_GenericConfirmation and CanHL_SetCanPduInfo with canPdu pointer as parameter (local defined).
 \COUNTERMEASURE \N The structure is static and always valid.

\ID SBSW_CAN_HL33
 \DESCRIPTION Write access to CanBusOffCounter with controller as index. Controller index is checked against sizeof CanBusOffCounter in Can_SetControllerMode(), CanHL_ErrorHandling() and Can_Init().
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_HL34
 \DESCRIPTION Write access to CanMailboxState with mailbox handle as index. Index secured by ComStackLib [CM_CAN_HL29] and [CM_CAN_HL30] and checked against size of CanMailboxState.
 \COUNTERMEASURE \R [CM_CAN_HL28]

\ID SBSW_CAN_HL35
 \DESCRIPTION Call with pointer to CAN cell register for write and read access.
 \COUNTERMEASURE \N Caller ensures validity of pointer parameter.

\ID SBSW_CAN_HL36
 \DESCRIPTION Write access to initPara structure as pointer (local defined).
 \COUNTERMEASURE \N The structure is static and always valid.

\ID SBSW_CAN_HL37
 \DESCRIPTION Call GetElapsedValue with timer value pointers as parameter (module local defined).
 \COUNTERMEASURE \N The timer values are static and always valid.

\ID SBSW_CAN_HL38
 \DESCRIPTION Call GetCounterValue with timer value (LoopTimeout) pointers as parameter. Controller index is checked against size of ControllerData, kCanLoopXXX as index in LoopTimeout table is always smaller than the dimension of the table given as static user type in ComStackLib and checked against this value.
 \COUNTERMEASURE \R [CM_CAN_HL01]
                 \R [CM_CAN_HL22]

\ID SBSW_CAN_HL39
 \DESCRIPTION Undefine preprocessor switch to stimulate user defined feature (only test purpose).
 \COUNTERMEASURE \N Redefinement activates a none documented feature.

\ID SBSW_CAN_HL40
 \DESCRIPTION Write access to CanLogStatus with controller as index. Controller is secured by qualified use-case CSL03 of ComStackLib.
 \COUNTERMEASURE \N [CM_CAN_HL02]

\ID SBSW_CAN_HL41
 \DESCRIPTION Write access to CanActiveSendState with activeSendObject as index. activeSendObject is temporary stored in a list of [1,3] elements where each element is initialized to a valid value and always written with size check before.
 \COUNTERMEASURE \R [CM_CAN_HL03]

\ID SBSW_CAN_HL42
 \DESCRIPTION Write access to txPara (module local defined).
 \COUNTERMEASURE \N The structure is static and always valid.

\ID SBSW_CAN_HL43
 \DESCRIPTION Write access to taskPara (module local defined).
 \COUNTERMEASURE \N The structure is static and always valid.

\ID SBSW_CAN_HL44
 \DESCRIPTION Call task subroutines with taskPara pointer as parameter (local defined).
 \COUNTERMEASURE \N The structure is static and always valid (pointer to a local stack variable)

\ID SBSW_CAN_HL45
 \DESCRIPTION Call confirmation subroutines with txConfPara pointer as parameter (local defined).
 \COUNTERMEASURE \N The structure is static and always valid (pointer to a local stack variable)

\ID SBSW_CAN_HL46
 \DESCRIPTION Write access to txConfPara (module local defined).
 \COUNTERMEASURE \N The structure is static and always valid.

\ID SBSW_CAN_HL47
 \DESCRIPTION Call cancellation subroutines with txCancellationPara pointer as parameter (local defined).
 \COUNTERMEASURE \N The structure is static and always valid (pointer to a local stack variable)

\ID SBSW_CAN_HL48
 \DESCRIPTION Write access to txCancellationPara (module local defined).
 \COUNTERMEASURE \N The structure is static and always valid.

\ID SBSW_CAN_HL49
 \DESCRIPTION Call transmit subroutines with txPara pointer as parameter (local defined).
 \COUNTERMEASURE \N The structure is static and always valid (pointer to a local stack variable)

\ID SBSW_CAN_HL50
 \DESCRIPTION Write access to TxHwFifo member FillCount, WriteIndex and ReadIndex with Mailbox member TxHwFifo as Index. Index is checked against size of TxHwFifo array.
 \COUNTERMEASURE \R [CM_CAN_HL32]

\ID SBSW_CAN_HL51
 \DESCRIPTION Write access to ControllerModePtr pointer within function Can_GetControllerMode()
 \COUNTERMEASURE \N caller of Can_GetControllerMode() has to ensure that ControllerModePtr pointer is valid. (global description available)

\ID SBSW_CAN_HL52
 \DESCRIPTION Write access to ErrorStatePtr pointer within function Can_GetControllerErrorState()
 \COUNTERMEASURE \N caller of Can_GetControllerErrorState() has to ensure that ErrorStatePtr pointer is valid. (global description available)

\ID SBSW_CAN_HL53
 \DESCRIPTION Write access to TxErrorCounterPtr pointer within function Can_GetControllerTxErrorCounter()
 \COUNTERMEASURE \N caller of Can_GetControllerTxErrorCounter() has to ensure that TxErrorCounterPtr pointer is valid. (global description available)

\ID SBSW_CAN_HL54
 \DESCRIPTION Write access to RxErrorCounterPtr pointer within function Can_GetControllerRxErrorCounter()
 \COUNTERMEASURE \N caller of Can_GetControllerRxErrorCounter() has to ensure that RxErrorCounterPtr pointer is valid. (global description available)

\ID SBSW_CAN_HL55
 \DESCRIPTION A ComStackLib generated variable is accessed.
 \COUNTERMEASURE \N The variable is written using a generated macro of the CSL. It immediately dereferences the variables address without pointer arithmetic.


\ID SBSW_CAN_LL01
 \DESCRIPTION Access to a hardware register (Global section) of the FlexCAN module using a pointer access. Pointer is derived using channel as index. Channel is checked by caller. (see also generator CM_CAN_LL08 qualified use case CSL02)
 \COUNTERMEASURE \R [CM_CAN_LL03]
                 \R [CM_CAN_LL05]
                 \S [CM_CAN_LL06]
                 \R [CM_CAN_LL07]

\ID SBSW_CAN_LL02
 \DESCRIPTION Access to a hardware register (mailbox section) of the FlexCAN module using a structure access. In addition it is referenced by the global FlexCAN module pointer that refernces the channel.
 \COUNTERMEASURE \R [CM_CAN_LL03]
                 \R [CM_CAN_LL04]
                 \R [CM_CAN_LL05]
                 \S [CM_CAN_LL06]
                 \R [CM_CAN_LL07]
                 \S [CM_CAN_LL09]

\ID SBSW_CAN_LL03
 \DESCRIPTION Call with pointer to CAN cell register (either global section or mailbox section) for write and read access.
 \COUNTERMEASURE \R [CM_CAN_LL03]
                 \R [CM_CAN_LL04]
                 \R [CM_CAN_LL05]
                 \S [CM_CAN_LL06]
                 \R [CM_CAN_LL07]
                 \S [CM_CAN_LL09]

\ID SBSW_CAN_LL04
 \DESCRIPTION Write access with pointer to initPara, txConfPara, rxBasicPara, rxFullPara, txCancellationPara, taskPara structure (local defined).
 \COUNTERMEASURE \N The structure is static and always valid (pointer to a local stack variable).

\ID SBSW_CAN_LL05
 \DESCRIPTION Write access to canTxBuf with dedicated integers as index.
 \COUNTERMEASURE \N Type of static CanTxBuf structure.

 \ID SBSW_CAN_LL06
 \DESCRIPTION Write access to generated CanRxMsgBuffer with channel as index.
 \COUNTERMEASURE \R [CM_CAN_LL01]
                 \R [CM_CAN_LL03]

\ID SBSW_CAN_LL07
 \DESCRIPTION Write access to localInterruptOldFlagPtr.
 \COUNTERMEASURE \N Caller ensures validity of pointer parameter. See SBSW_CAN_HL16.

\ID SBSW_CAN_LL08
 \DESCRIPTION Call GetCounterValue with timer index as parameter.
 \COUNTERMEASURE \R [CM_CAN_LL02]

\ID SBSW_CAN_LL09
 \DESCRIPTION Write access to section of the FlexCAN using a pointer derived from the FlexCAN module's base address (RXFIFO, CanRxMask, CanGlitchFilter, CanParityCheck, DebugRegister, CanFDRegister, IndivRxMask).
 \COUNTERMEASURE \R [CM_CAN_LL03]
                 \R [CM_CAN_LL04]
                 \R [CM_CAN_LL05]
                 \S [CM_CAN_LL06]

\ID SBSW_CAN_LL10
 \DESCRIPTION Write access to canFDTxBuf with index.
 \COUNTERMEASURE \N pduInfo_var_dli never exceeds maximum value of 64 bytes (this is secured by core: Can_DliToBytesMap, Can_BytesToDliMap). Thus it is ensured that sduWordLen and dataWordLen never exceeds size of canFDTxBuf.

\ID SBSW_CAN_LL11
 \DESCRIPTION Write access to canFDTxBuf with unsecured maximum value from caller.
 \COUNTERMEASURE \R [CM_CAN_LL11]

\ID SBSW_CAN_LL12
 \DESCRIPTION Write access to canFDTxBuf with index .
 \COUNTERMEASURE \R [CM_CAN_LL10]

\ID SBSW_CAN_LL13
 \DESCRIPTION Write access to canTxBuf with static index.
 \COUNTERMEASURE \N the memory access is warranty by the static index used (0,1).

\ID SBSW_CAN_LL14
 \DESCRIPTION Write access to canLL_canStartReinitState and canLL_FlexCANInitResultNeeded with channel as index.
 \COUNTERMEASURE \R [CM_CAN_LL03].

SBSW_JUSTIFICATION_END */

/* Counter measurement description

\CM CM_CAN_HL01 A runtime check ensures controller index is always smaller than number of elements in arrays with controller amount as dimension (Qualified use-case CSL01 of ComStackLib size of ControllerData).
\CM CM_CAN_HL02 Qualified use-case CSL03 of ComStackLib (CanMailbox.ControllerConfigIdx is always in range of controller ControllerData)
\CM CM_CAN_HL03 A runtime check ensures activeSendObject index is in valid range for Can_ActiveSendObject table (Qualified use-case CSL01 of ComStackLib - Can_ActiveSendObject size is extended by CAN_MULTIPLEXED_TX_MAX within generator to allow an access to logObjHandle+CAN_MULTIPLEXED_TX_MAX).
\CM CM_CAN_HL17 A runtime check ensures DLC index is always smaller than the dimension of CanRxQueueBuffer.data.
\CM CM_CAN_HL18 A runtime check ensures HRH values is always in range of start stop index of the given mailbox type. (Qualified use-case CSL03 of ComStackLib - start-stop index fit to mailbox entrys)
\CM CM_CAN_HL20 A runtime check ensures size of ActiveSendData (dataByte). For CAN-FD it is checked against the size of the table. For none CAN-FD size is checked against 8 as defined.
\CM CM_CAN_HL22 A runtime check ensures source index for LoopTimeout array is always smaller than the dimension of LoopTimeout.
\CM CM_CAN_HL24 A runtime check ensures RxQueue write index is always smaller than the dimension of RxQueue (Qualified use-case CSL01 of ComStackLib).
\CM CM_CAN_HL25 A runtime check ensures RxQueue read index is always smaller than the dimension of RxQueue (Qualified use-case CSL01 of ComStackLib).
\CM CM_CAN_HL28 A runtime check ensures htrh index is always smaller than the dimension of CanMailboxState (Qualified use-case CSL01 of ComStackLib).
\CM CM_CAN_HL29 Qualified use-case CSL02 of ComStackLib (size of CanMailboxState == size of CanMailbox) 
\CM CM_CAN_HL30 Qualified use-case CSL03 of ComStackLib (CanMailbox - CanController Start/Stop HtrhIndex).
\CM CM_CAN_HL31 valid mailbox data area is assigned to rxStruct.pChipData pointer (Has to be given by LL implementation part).
\CM CM_CAN_HL32 A runtime check ensures TxHwFifo index is always smaller than the dimension of TxHwFifo (Qualified use-case CSL01 of ComStackLib).

\CM CM_CAN_LL01 CanRxMsgBuffer size is checked during PowerOnInit against static defined size; canConfigInitFlag remains CAN_STATUS_UNINIT in case of failure.
\CM CM_CAN_LL02 Loop timeout is checked during PowerOnInit against maximum value CAN_MAX_LOOP); canConfigInitFlag remains CAN_STATUS_UNINIT in case of failure.
\CM CM_CAN_LL03 Is covered by CM_CAN_HL01: A runtime check ensures controller index is always smaller than number of elements in arrays with controller amount as dimension (Qualified use-case CSL01 of ComStackLib size of ControllerData).
\CM CM_CAN_LL04 HwObjHandle for mailbox and individual receive masks index is secured by a runtime check and in addition it is secured by a DET.
\CM CM_CAN_LL05 TCASE-429: Code inspection ensures that the defined access structures match the memory structure of the FlexCAN module.
\CM CM_CAN_LL06 User must verify that the generated base address(es) for the FlexCAN controller matches to the used derivative (see SMI-301577).
\CM CM_CAN_LL07 channel number is checked in interrupt (runtime check).
\CM CM_CAN_LL08 Qualified use-case CSL02 of ComStackLib (size of Can_GetBaseAddressOfControllerConfig == size of CanControllerData).
\CM CM_CAN_LL09 User must verify that the generated mailbox addresses in case of FD mode 2 matches the address range of the used derivative (see SMI-301577).
\CM CM_CAN_LL10 CANFD_MAILBOX_MAX_WORD_LENGTH() is checked during PowerOnInit against static defined size; canConfigInitFlag remains CAN_STATUS_UNINIT in case of failure.
\CM CM_CAN_LL11 sduWordLen is restricted to maximum buffer size.

*/

/****************************************************************************/
/*  Coverage Justification                                                  */
/****************************************************************************/
/* START_COVERAGE_JUSTIFICATION

\ID COV_CAN_COMPATIBILITY
  \ACCEPT TX
  \ACCEPT XF
  \ACCEPT TX xf xf
  \ACCEPT XF tf tf
  \REASON The condition checks whether a switch is defined and conditionally assigns a default value. This is used to ensure compatibility to older AUTOSAR/Component versions. 

\ID COV_CAN_INTERNAL
  \ACCEPT XF
  \ACCEPT TX
  \REASON This switch is always active within CAN driver context. Secure visibility of internal interface and cannot be stimulated to off while test. The code is verified by code inspection.

\ID COV_CAN_CANCEL_SW_STIMULATION
  \ACCEPT TF
  \ACCEPT XF
  \ACCEPT TX
  \ACCEPT XX
  \ACCEPT TF tf xf
  \REASON It is not possible to stimulate a sw cancellation while the message is already start to send when hw cancellation is active. The code is verified by code inspection.

\ID COV_CAN_AMD_RUNTIME_MEASUREMENT
  \ACCEPT XF
  \REASON The feature AMD Runtime Measurement is not supported for SafeBSW. A MSSV plugin enforces this configuration for SafeBSW.

\ID COV_CAN_FINALMAGICNUMBER
  \ACCEPT TX
  \REASON Switch is always true is OK here no side effect will occur when switch is false verified by review.

\ID COV_CAN_SAFE_BSW_EXCLUSION
  \ACCEPT XF xf xf
  \REASON SafeBsw restricted feature will not be enforced to be deactivated or activated.

\ID COV_CAN_BUSOFF_NOT_IN_ALL_CONFIG
  \ACCEPT X
  \ACCEPT XF
  \ACCEPT TX
  \ACCEPT TF tf tx
  \ACCEPT TX tx tx
  \REASON BUSOFF not stimulated in each configruation. The behavior does not depend on each configuration variant but TCASE-274 takes long runtime and will not be executed for each configuration.   

\ID COV_CAN_WAKEUP_CHANNEL_NOT_IN_ALL_CONFIG
  \ACCEPT XF
  \ACCEPT TX
  \REASON Wakeup may be always activated or deactivated depend on configuration. Not all configurations contain activated or deactivated wakeup for at least one controller, but is sufficiantly tested in some configuations with both settings.

\ID COV_IMPLICITE_TXCANCEL
  \ACCEPT TX
  \REASON In some configurations there will be no recancellation but for this case there is no active code (empty else), so this is not really a test case.

---------------- LL ------------------


\ID COV_CAN_MULTIPLE_BASICCAN_TX
  \ACCEPT TF
  \ACCEPT TF tf tf
  \REASON The feature is platform specific - fully supported.

\ID COV_CAN_SLEEP_SUPPORT
  \ACCEPT XF
  \REASON This feature is not supported - always deactivated.

\ID COV_CAN_WAKEUP_SUPPORT
  \ACCEPT XF
  \REASON This feature is not supported - always deactivated.

\ID COV_CAN_TX_POLLING
  \ACCEPT TF
  \REASON The feature is platform specific - fully supported.

\ID COV_CAN_RX_POLLING
  \ACCEPT TF
  \REASON The feature is platform specific - fully supported.

\ID COV_CAN_RX_BASICCAN_POLLING
  \ACCEPT TF
  \REASON The feature is platform specific - fully supported.

\ID COV_CAN_RX_FULLCAN_POLLING
  \ACCEPT TF
  \REASON The feature configuration specific - fully supported.

\ID COV_CAN_ERROR_POLLING
  \ACCEPT TF
  \REASON The feature is platform specific - fully supported.

\ID COV_CAN_WAKEUP_POLLING
  \ACCEPT XF
  \REASON This feature is not supported - always deactivated.

\ID COV_CAN_INDIVIDUAL_POLLING
  \ACCEPT TF
  \REASON The feature is platform and Project specific.

\ID COV_CAN_TX_POLLING_OR_CANCEL_IN_HW_TASK
  \ACCEPT TF tf tf tx
  \ACCEPT TF tf tf xf
  \REASON The feature is platform specific - C_HL_ENABLE_CANCEL_IN_HW_TASK is always true or false.

\ID COV_CAN_GENERIC_CONFIRMATION_API2
  \ACCEPT TF
  \REASON The feature is platform and Project specific - fully supported.

\ID COV_CAN_FD_SUPPORT
  \ACCEPT TF
  \REASON The feature is platform and Project specific - fully supported.

\ID COV_CAN_MULTIPLE_BASICCAN
  \ACCEPT TF
  \REASON The feature is platform and Project specific - fully supported.

\ID COV_CAN_TX_FULLCAN_OBJECTS
  \ACCEPT TF
  \REASON The feature is platform specific - fully supported.

\ID COV_CAN_RX_FULLCAN_OBJECTS
  \ACCEPT TF
  \REASON The feature is platform specific - fully supported.

\ID COV_CAN_HW_TRANSMIT_CANCELLATION
  \ACCEPT TF
  \REASON The feature is platform specific - fully supported.

\ID COV_CAN_CANCEL_IN_HW
  \ACCEPT TF
  \REASON The feature is platform specific - fully supported.

\ID COV_CAN_HARDWARE_CANCELLATION
  \ACCEPT TF
  \REASON The feature is platform specific - fully supported.

\ID COV_CAN_EXTENDED_ID
  \ACCEPT TF
  \REASON The feature is platform specific - fully supported.

\ID COV_CAN_MIXED_ID
  \ACCEPT TF
  \REASON The feature is platform specific - fully supported.

\ID COV_CAN_SECURE_TEMP_BUFFER
  \ACCEPT XF
  \REASON This feature is not supported - always deactivated.

\ID COV_CAN_OVERRUN_NOTIFICATION
  \ACCEPT TF
  \REASON The feature is platform specific - fully supported.

\ID COV_CAN_MULTIPLEXED_TRANSMISSION
  \ACCEPT TF
  \REASON The feature is platform specific - fully supported.

\ID COV_CAN_TX_HW_FIFO
  \ACCEPT XF
  \REASON This feature is not supported - always deactivated.

\ID COV_CAN_RX_QUEUE
  \ACCEPT TF
  \REASON The feature is platform specific - fully supported.

\ID COV_CAN_HW_LAYOUT_TXBASIC_FIRST
  \ACCEPT TX
  \REASON For FlexCAN3 the mailbox ordering is TX Basic first - always activated.

\ID COV_CAN_TX_FULLCAN_HWHANDLE_REVERSE
  \ACCEPT XF
  \REASON The feature is platform specific - always deactivated.

\ID COV_CAN_RX_FULLCAN_HWHANDLE_REVERSE
  \ACCEPT XF
  \REASON The feature is platform specific - always deactivated.

\ID COV_CAN_BASICCAN_HWHANDLE_REVERSE
  \ACCEPT XF
  \REASON The feature is platform specific - always deactivated.

\ID COV_CAN_EXTENDED_STATUS
  \ACCEPT TX
  \REASON The feature is platform specific - always active.

\ID COV_CAN_OVERRUN_IN_STATUS
  \ACCEPT XF
  \REASON The feature is platform specific - always deactivated.

\ID COV_CAN_RxBasicMsgReceivedBegin
  \ACCEPT TX
  \REASON The feature is platform specific - always active.

\ID COV_CAN_RxFullMsgReceivedBegin
  \ACCEPT TX
  \REASON The feature is platform specific - always active.

\ID COV_CAN_HW_EXIT_TRANSMIT
  \ACCEPT TX
  \REASON The feature is platform specific - always active.

\ID COV_CAN_HARDWARE_FAILURE
  \ACCEPT TX
  \ACCEPT XF
  \ACCEPT XF xf xf
  \ACCEPT XF tf xf
  \ACCEPT TF tf xf
  \ACCEPT TF tf tx
  \ACCEPT XF xf xf xf xf
  \ACCEPT XF xf xf xf xf xf
  \ACCEPT XF xf xf xf xf xf xf
  \ACCEPT XF xf xf xf xf xf xf xf
  \ACCEPT XF xf xf xf xf xf xf xf xf
  \ACCEPT XF xf xf xf xf xf xf xf xf xf
  \ACCEPT XF xf xf xf xf xf xf xf xf xf xf
  \ACCEPT XF xf xf xf xf xf xf xf xf xf xf xf
  \REASON The condition checks for hardware failures that cannot be stimulated. The code is verified by code inspection.

\ID COV_CAN_LL_HARDWARE_BEHAVIOUR
  \ACCEPT TX
  \ACCEPT XF
  \REASON The condition checks for hardware depended return value. The return value is always true because hardware never fail here. The code is verified by code inspection.

\ID COV_CAN_GENDATA_FAILURE
  \ACCEPT TX
  \ACCEPT XF
  \ACCEPT XF xf xf
  \ACCEPT TF tf xf
  \ACCEPT TX tx tx
  \ACCEPT TF xf tf
  \ACCEPT TF tf xf tf
  \ACCEPT TF xf tf xf tf
  \ACCEPT TX tx xf tx tx
  \ACCEPT TX tx tf tx tx
  \ACCEPT TX tx tx xx xx
  \REASON The condition checks for generated data failures that cannot be simulated. The code is verified by code inspection.

\ID COV_CAN_GENDATA_NOT_IN_ALL_CONFIG
  \ACCEPT TX
  \ACCEPT XF
  \ACCEPT X
  \REASON Generated data does not contain all data sets but checked in code. Not encapsulated with preprocessor switch to simplify code.  

\ID COV_CAN_OS_USAGE
  \ACCEPT TX
  \ACCEPT XF
  \ACCEPT TX xf tx
  \ACCEPT TX tx xf
  \ACCEPT TF tx tf
  \ACCEPT XF xf tx
  \ACCEPT TF xf xf
  \ACCEPT TF xf tf
  \REASON Os may be used in component test or not. The code is verified by code inspection.

\ID COV_CAN_INTERRUPT_SUPPORT
  \ACCEPT TF tf tx
  \REASON Busoff Interrupt is in some configurations always true

\ID COV_CAN_CDK_DETECTION
  \ACCEPT TX tf tf
  \ACCEPT TF tf tf tx tx tx tx
  \REASON Variant Coverage tool does not detect full coverage though preprocessing shows it is fully covered covered with TF

\ID COV_CAN_LOCK_ISR_BY_APPL
  \ACCEPT TX tf tf
  \ACCEPT TF xf tf 
  \REASON CAN interrupts never locked by application only within tests. It is not part of the component test to check application code. The code is verified by code inspection.

\ID COV_CAN_RAM_CHECK
  \ACCEPT TF
  \REASON The feature is platform specific - fully supported.

\ID COV_CAN_RAM_CHECK_EXTENDED
  \ACCEPT TF
  \REASON The feature is platform specific - fully supported.

\ID COV_CAN_TIMEOUT_DURATION
  \ACCEPT XF
  \ACCEPT TX
  \ACCEPT XF xf xx
  \ACCEPT TF tf tx
  \ACCEPT XF xf xf xx
  \REASON Hardware loop time out is not covered in all configurations.

\ID COV_CAN_TRANSITION_REQUEST
  \ACCEPT X
  \ACCEPT TX
  \ACCEPT XF
  \REASON Mode transition is platform specific always true or false.

\ID COV_CAN_BASICCAN_SEARCH_LINEAR
  \ACCEPT TX
  \ACCEPT TF tx tf
  \ACCEPT TX tx tx
  \REASON Received BasicCAN mailbox is always a valid object and found while search.

\ID COV_CAN_FULLCAN_SEARCH_LINEAR
  \ACCEPT TX
  \ACCEPT TF tx tf
  \REASON Received FullCAN mailbox is always a valid object and found while search.

\ID COV_CAN_RAM_CHECK_NO_STIMULATION
  \ACCEPT X
  \ACCEPT XF
  \ACCEPT TX
  \ACCEPT XF xf xf
  \ACCEPT TF tf xf
  \ACCEPT XF xf xf xf xf
  \ACCEPT XF xf xf xf xf xf
  \ACCEPT XF xf xf xf xf xf xf
  \ACCEPT XF xf xf xf xf xf xf xf
  \ACCEPT XF xf xf xf xf xf xf xf xf
  \ACCEPT XF xf xf xf xf xf xf xf xf xf
  \ACCEPT XF xf xf xf xf xf xf xf xf xf xf
  \ACCEPT XF xf xf xf xf xf xf xf xf xf xf xf
  \REASON some configurations do not stimulate RamCheck by test suite, to check the standard CAN driver behaviour.

\ID COV_CAN_SAFE_BSW
  \ACCEPT TF
  \REASON The feature is platform specific - fully supported.

\ID COV_CAN_HWOBJINDIVPOLLING
  \ACCEPT TF tf xf
  \ACCEPT TX
  \ACCEPT XF
  \REASON usage of individual hardware object polling is platform specific always true or false.

\ID COV_CAN_FLEXCAN3_DERIVATIVE_ASYM_MAILBOXES
  \ACCEPT TX
  \ACCEPT XF
  \REASON Feature only available with FlexCAN3 derivatives having different number of hardware Mailboxes on the channels.

\ID COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB
  \ACCEPT TX
  \ACCEPT TX tx tx
  \ACCEPT TX xf tx
  \ACCEPT XF
  \ACCEPT XF xf xf
  \REASON Depending on the FLexCAN3 derivatives different maximum number of Hardware Mailboxes are supported.

\ID COV_CAN_FLEXCAN3_DERIVATIVE_LITTLE_ENDIAN
  \ACCEPT TX
  \REASON Always true for ARM32 FlexCAN3 derivatives.

\ID COV_CAN_FLEXCAN3_DERIVATIVE_BIG_ENDIAN
  \ACCEPT TX
  \REASON Always true for MPC FlexCAN3 derivatives.

\ID COV_CAN_FLEXCAN3_DERIVATIVE_INTERRUPT_SOURCE_SINGLE
  \ACCEPT TX
  \ACCEPT XF
  \REASON Depending on the FlexCAN3 derivative a single interrupt source is available.

\ID COV_CAN_FLEXCAN3_DERIVATIVE_INTERRUPT_SOURCE_MULTIPLE
  \ACCEPT TX
  \ACCEPT XF
  \REASON Depending on the FlexCAN3 derivative a multiple interrupt sources are available.

\ID COV_CAN_EQUAL_CHANNEL_LAYOUT
  \ACCEPT TX
  \ACCEPT XF
  \ACCEPT TF
  \REASON The test is executed on defined channels. The channel layout is equal for each channel.

\ID COV_CAN_LL_OSCAT_CONFIG_CHECK
  \REASON The define 'osdIsr' is only available with OSEK OS. It is only used to verify the configuration and does not influence the runtime code.

\ID COV_CAN_LL_ISR_PROTOTYPE
  \REASON Is not fully covered with tf tf but with all other combinations. Tool does not recognize it.

\ID COV_CAN_MAILBOX_ORDER
  \ACCEPT TF tx tf
  \ACCEPT TF tx tf
  \ACCEPT TF tf tx
  \ACCEPT TX tx tx
  \ACCEPT XF tf xf
  \ACCEPT XF tx xf
  \ACCEPT XF xf xx
  \ACCEPT TX
  \REASON Depends on order of generated RX, TX Basic CAN or Full CAN objects.

\ID COV_CAN_HARDWARE_PROCESSING_TIME
  \ACCEPT TX
  \ACCEPT XF
  \ACCEPT XF xf xx
  \REASON Hardware processing time cannot be influenced. Is either true or false.

\ID COV_CAN_TESTSTIMULATION
  \ACCEPT XF
  \ACCEPT TX
  \ACCEPT TX tf tx
  \ACCEPT TF tf tx tf
  \REASON Not in all configurations fully covered.

\ID COV_CAN_INIT_STIMULATION
  \ACCEPT TX
  \ACCEPT TF xf tf
  \ACCEPT TX xf tx
  \ACCEPT TX tf tx
  \ACCEPT TF xf tf tf
  \ACCEPT TF xf tx tf
  \ACCEPT TF tf tx tf
  \REASON Test Automation does not cover disable mode during power on (manually tested). Busoff state only covered here if busoff recovery is chosen to be "not compliant (not waiting 128x11 recessive bits)".

\ID COV_CAN_CLK_SRC_GENERATION
  \ACCEPT TX
  \ACCEPT XF
  \REASON Depending on hardware Usage of Oscillator Clock or System Clock is used.

\ID COV_CAN_STOP_BOFF_STIMULATION
  \ACCEPT TF
  \ACCEPT TX
  \ACCEPT XF
  \REASON Busoff condition during stop transition is not covered by all configurations.

\ID COV_CAN_REINITSTART_STIMULATION
  \ACCEPT TX
  \REASON If Reinit Start Feature is active condition is always true.

\ID COV_CAN_START_STIMULATION
  \ACCEPT TF
  \ACCEPT XF
  \REASON Depending on derivative or configuration Start Request State is hit or Started State is reached very fast.

\ID COV_CAN_BUSOFFEND_STIMULATION
  \ACCEPT TF
  \ACCEPT TX
  \ACCEPT XF
  \REASON Not all possible states covered (unlikely states). Manually tested.

\ID COV_CAN_CONTROLLER_INIT_STATE
  \ACCEPT XF
  \REASON SAFE_BSW check expected to be false.

\ID COV_CAN_GENDATA_TX_NOT_IN_ALL_CONFIG
  \ACCEPT TF tx tf tx tf
  \ACCEPT TF tf tx tx tf
  \ACCEPT TF tf tf tx tf
  \ACCEPT TF tx tf tf
  \ACCEPT TF tf tx tf
  \ACCEPT TF tf tf tx
  \ACCEPT TF tf tx tx
  \ACCEPT TF tx tf tx
  \ACCEPT TF tx tf
  \ACCEPT TF tf tx
  \REASON Generated data does not contain all data sets but checked in code. Not encapsulated with preprocessor switch to simplify code.

\ID COV_CAN_FULL_OVERRUN_HANDLING
  \ACCEPT XF
  \ACCEPT TF
  \REASON FullCAN overrun is only detected if BasicCAN filter is configured in such a way that FullCAN messages cannot be received in a BasicCAN mailbox.

\ID COV_CAN_BUSOFF_HANDLING
  \ACCEPT TX
  \ACCEPT TF
  \REASON Is always true in CanHL_ErrorHandling() when it is only called due to busoff.

\ID COV_CAN_RXFIFO_HANDLING
  \ACCEPT XF xf xx
  \ACCEPT TF tf tx
  \ACCEPT TF tf tf
  \REASON Depends on whether messages in RX-FIFO are available and on the number of queued messages.

\ID COV_CAN_FULLCAN_LL_RX_POLLING
  \ACCEPT TX
  \ACCEPT TF
  \REASON Is always true when during a polling period a FullCAN is received.

\ID COV_CAN_FULLCAN_LL_TX_POLLING
  \ACCEPT TX
  \ACCEPT TF
  \REASON Is always true when during a polling period a message is transmitted.

\ID COV_CAN_MUMOFHANDLES_CORRECTON
  \ACCEPT TX
  \ACCEPT XF
  \REASON Correction needed if nofOfHandles is greater 0 (always true or false depending on generated data)

\ID COV_CAN_FD_BAUDRATE_AVAILABILITY
  \ACCEPT TX
  \ACCEPT XF
  \ACCEPT TF
  \REASON Generated data does not contain all data sets but checked in code. Not encapsulated with preprocessor switch to simplify code.

\ID COV_CAN_SAFE_BSW_EXCLUSION_FLEXCAN3
  \ACCEPT XF xf xf
  \ACCEPT XF xf xf xf
  \REASON SafeBsw restricted feature will not be enforced to be deactivated or activated.

\ID COV_CAN_MAILBOX_INT_INDIVPOLLING
  \ACCEPT TF
  \ACCEPT XF
  \ACCEPT TX
  \ACCEPT XX
  \ACCEPT X
  \REASON In case of Individual Polling activated, mailbox interrupts are enabled. But if there are only polling objects interrupt is never called.

\ID COV_CAN_MISRA
  \ACCEPT XF
  \ACCEPT TX
  \REASON Only used for MISRA analysis not active in production code.

\ID COV_CAN_RAMCHECK_EXTENDED_CLKSRC_COMPATABILITY
  \ACCEPT XF tx xf
  \ACCEPT XF xf tx
  \ACCEPT TF xf xf
  \REASON Set to a default value if not generated. C_ENABLE_CLKSRC_SELECTION shall be defined if clock source can be selected, C_DISABLE_CLKSRC_SELECTION otherwise.
  
\ID COV_CAN_RAMCHECK_EXTENDED_CLKSRC_AVAILABILITY
  \ACCEPT TX
  \ACCEPT XF
  \ACCEPT TF tf tx
  \ACCEPT XF tf xf
  \REASON Extended RAM check can only be excecuted on devices that support clock source selection.
  
\ID COV_CAN_BUSOFF_INTERRUPT_ONLY
  \ACCEPT TX
  \REASON Result is always true if Busoff Interrupt and RX/TX polling is configured.

END_COVERAGE_JUSTIFICATION */ 


/* Kernbauer Version: 1.14 Konfiguration: DrvCan_Arm32Flexcan3Asr Erzeugungsgangnummer: 398 */

/* Kernbauer Version: 1.14 Konfiguration: DrvCan_Arm32Flexcan3Asr Erzeugungsgangnummer: 398 */

/* Kernbauer Version: 1.14 Konfiguration: DrvCan_Arm32Flexcan3Asr Erzeugungsgangnummer: 398 */

/* Kernbauer Version: 1.14 Konfiguration: DrvCan_Arm32Flexcan3Asr Erzeugungsgangnummer: 398 */

/* Kernbauer Version: 1.14 Konfiguration: DrvCan_Arm32Flexcan3Asr Erzeugungsgangnummer: 398 */

/* Kernbauer Version: 1.14 Konfiguration: DrvCan_Arm32Flexcan3Asr Erzeugungsgangnummer: 398 */

/* Kernbauer Version: 1.14 Konfiguration: DrvCan_Arm32Flexcan3Asr Erzeugungsgangnummer: 398 */

/************   Organi, Version 3.9.2 Vector-Informatik GmbH  ************/
