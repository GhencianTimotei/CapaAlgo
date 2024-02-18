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
 *            Module: ComM
 *           Program: VAG AR4 (MSR_Vag_SLP5)
 *          Customer: Huf H_lsbeck & F_rst GmbH & Co. KG
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: S32K144
 *    License Scope : The usage is restricted to CBD2100188_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: ComM_Cfg.h
 *   Generation Time: 2024-02-05 15:58:29
 *           Project: DaVinciConfigurationS32K144 - Version 1.0
 *          Delivery: CBD2100188_D01
 *      Tool Version: DaVinci Configurator  5.23.45 SP4
 *
 *
 *********************************************************************************************************************/


#if !defined(COMM_CFG_H)
#define COMM_CFG_H

/* -----------------------------------------------------------------------------
    &&&~ INCLUDES
 ----------------------------------------------------------------------------- */

#include "ComM_Types.h"

/* -----------------------------------------------------------------------------
    &&&~ CONFIGURATION DEFINES
 ----------------------------------------------------------------------------- */

#ifndef COMM_USE_DUMMY_STATEMENT
#define COMM_USE_DUMMY_STATEMENT STD_ON /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef COMM_DUMMY_STATEMENT
#define COMM_DUMMY_STATEMENT(v) (v)=(v) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef COMM_DUMMY_STATEMENT_CONST
#define COMM_DUMMY_STATEMENT_CONST(v) (void)(v) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef COMM_ATOMIC_BIT_ACCESS_IN_BITFIELD
#define COMM_ATOMIC_BIT_ACCESS_IN_BITFIELD STD_OFF /* /MICROSAR/EcuC/EcucGeneral/AtomicBitAccessInBitfield */
#endif
#ifndef COMM_ATOMIC_VARIABLE_ACCESS
#define COMM_ATOMIC_VARIABLE_ACCESS 32u /* /MICROSAR/EcuC/EcucGeneral/AtomicVariableAccess */
#endif
#ifndef COMM_PROCESSOR_S32K144
#define COMM_PROCESSOR_S32K144
#endif
#ifndef COMM_COMP_IAR
#define COMM_COMP_IAR
#endif
#ifndef COMM_GEN_GENERATOR_MSR
#define COMM_GEN_GENERATOR_MSR
#endif
#ifndef COMM_CPUTYPE_BITORDER_LSB2MSB
#define COMM_CPUTYPE_BITORDER_LSB2MSB /* /MICROSAR/vSet/vSetPlatform/vSetBitOrder */
#endif
#ifndef COMM_CONFIGURATION_VARIANT_PRECOMPILE
#define COMM_CONFIGURATION_VARIANT_PRECOMPILE 1
#endif
#ifndef COMM_CONFIGURATION_VARIANT_LINKTIME
#define COMM_CONFIGURATION_VARIANT_LINKTIME 2
#endif
#ifndef COMM_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE
#define COMM_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE 3
#endif
#ifndef COMM_CONFIGURATION_VARIANT
#define COMM_CONFIGURATION_VARIANT COMM_CONFIGURATION_VARIANT_PRECOMPILE
#endif
#ifndef COMM_POSTBUILD_VARIANT_SUPPORT
#define COMM_POSTBUILD_VARIANT_SUPPORT STD_OFF
#endif

#ifndef COMM_DEV_ERROR_DETECT
#define COMM_DEV_ERROR_DETECT STD_OFF
#endif
#ifndef COMM_DEV_ERROR_REPORT
#define COMM_DEV_ERROR_REPORT STD_OFF
#endif

#define COMM_INIT_POINTER_ENABLED                       STD_OFF
#define COMM_VERSION_INFO_API                           STD_ON

#define COMM_MODE_LIMITATION                            STD_OFF
#define COMM_WAKEUP_INHIBITION                          STD_OFF

#define COMM_PNC_SUPPORT                                STD_OFF
#define COMM_PNC_ACTIVE_COORD                           STD_OFF
#define COMM_PNC_PS_TIMER                               0u
#define COMM_ACTIVE_PNC                                 0u
#define COMM_PNC_EXTENDED_FUNCTIONALITY_ENABLED         STD_OFF
#define COMM_PNC_TO_CHANNEL_ROUTING_LIMITATION_ENABLED  STD_OFF
#define COMM_PNC_PASSIVE_GW_SUPPORT                     STD_OFF
#define COMM_PNC_EXISTS_GATEWAY_TYPE_ACTIVE             STD_OFF
#define COMM_PNC_EXISTS_GATEWAY_TYPE_NONE               STD_OFF
#define COMM_PNC_SIGNAL_LENGTH                          0u
#define COMM_PNC_MAX_NUMBER_OF_EIRA_RX                  0u
#define COMM_PNC_CHECK_ENABLED_AT_RUNTIME               STD_OFF
#define COMM_PNC_0_VECTOR_AVOIDANCE                     STD_OFF

#define COMM_NM_GW_EXT_ENABLED                          STD_OFF
#define COMM_KEEP_AWAKE_CHANNELS_SUPPORT                STD_ON
#define COMM_BUS_TYPE_INTERNAL_PRESENT                  STD_OFF
#define COMM_BUS_TYPE_FR_PRESENT                        STD_OFF
#define COMM_BUS_TYPE_LIN_PRESENT                       STD_OFF
#define COMM_EXISTS_ONLY_NONE_NMTYPEOFCHANNEL           STD_OFF

#define COMM_FULL_COMM_REQUEST_NOTIF                    STD_OFF
#define COMM_MAX_NUMBER_OF_USERS                        3u
#define COMM_DCM_INDICATION                             STD_ON
#define COMM_USERMODENOTIFUNC_PNC_USER_ONLY             STD_OFF

#define COMM_SYNCHRONOUS_WAKE_UP                        STD_ON
#define COMM_EXTENDED_RAM_CHECK                         STD_OFF

#define COMM_ACTIVE_CHANNEL                             1u
#define COMM_NVM_SUPPORT                                STD_OFF



/* -----------------------------------------------------------------------------
    &&&~ USER HANDLES
 ----------------------------------------------------------------------------- */

#define ComMConf_ComMUser_BusOff                   1u 
#define ComMConf_ComMUser_CN_HCP4_CANFD01_e8a39a18 0u 
#define ComMConf_ComMUser_ComMUser_NFC_User        2u 


/* -----------------------------------------------------------------------------
    &&&~ CHANNEL HANDLES
 ----------------------------------------------------------------------------- */
 
#define ComMConf_ComMChannel_CN_HCP4_CANFD01_152fd6c6 0u 


/* -----------------------------------------------------------------------------
    &&&~ PNC HANDLES
 ----------------------------------------------------------------------------- */



/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/** 
  \defgroup  ComMPCDataSwitches  ComM Data Switches  (PRE_COMPILE)
  \brief  These defines are used to deactivate data and their processing.
  \{
*/ 
#define COMM_ACTIVEPNCCOMMODE                                         STD_OFF  /**< Deactivateable: 'ComM_ActivePncComMode' Reason: 'PNC Support is disabled' */
#define COMM_BUSPNCCOMMODEREQ                                         STD_OFF  /**< Deactivateable: 'ComM_BusPncComModeReq' Reason: 'the array is deactivated because the size is 0 in all variants and the piece of data is in the configuration class: PRE_COMPILE' */
#define COMM_BUSSLEEPMODEINDICATED                                    STD_OFF  /**< Deactivateable: 'ComM_BusSleepModeIndicated' Reason: 'NM variant LINSLAVE is not present' */
#define COMM_CHANNEL                                                  STD_ON
#define COMM_BUSTYPEOFCHANNEL                                         STD_ON
#define COMM_ENABLEDOFCHANNEL                                         STD_OFF  /**< Deactivateable: 'ComM_Channel.Enabled' Reason: 'the value of ComM_EnabledOfChannel is always 'true' due to this, the array is deactivated.' */
#define COMM_GWTYPEOFCHANNEL                                          STD_ON
#define COMM_INHIBITIONINITVALUEOFCHANNEL                             STD_ON
#define COMM_J1939SUPPORTOFCHANNEL                                    STD_OFF  /**< Deactivateable: 'ComM_Channel.J1939Support' Reason: 'the value of ComM_J1939SupportOfChannel is always 'false' due to this, the array is deactivated.' */
#define COMM_MANAGINGCHANNELIDOFCHANNEL                               STD_OFF  /**< Deactivateable: 'ComM_Channel.ManagingChannelId' Reason: 'the value of ComM_ManagingChannelIdOfChannel is always 'COMM_NO_MANAGINGCHANNELIDOFCHANNEL' due to this, the array is deactivated.' */
#define COMM_MANAGINGCHANNELOFCHANNEL                                 STD_OFF  /**< Deactivateable: 'ComM_Channel.ManagingChannel' Reason: 'the value of ComM_ManagingChannelOfChannel is always 'false' due to this, the array is deactivated.' */
#define COMM_MANAGINGUSEROFCHANNEL                                    STD_OFF  /**< Deactivateable: 'ComM_Channel.ManagingUser' Reason: 'the value of ComM_ManagingUserOfChannel is always 'COMM_NO_MANAGINGUSEROFCHANNEL' due to this, the array is deactivated.' */
#define COMM_MINFULLCOMTIMEOFCHANNEL                                  STD_ON
#define COMM_NMLIGHTDURATIONOFCHANNEL                                 STD_OFF  /**< Deactivateable: 'ComM_Channel.NmLightDuration' Reason: 'the value of ComM_NmLightDurationOfChannel is always '0' due to this, the array is deactivated.' */
#define COMM_NMLIGHTSILENTDURATIONOFCHANNEL                           STD_OFF  /**< Deactivateable: 'ComM_Channel.NmLightSilentDuration' Reason: 'the value of ComM_NmLightSilentDurationOfChannel is always '0' due to this, the array is deactivated.' */
#define COMM_NMSUPPORTOFCHANNEL                                       STD_OFF  /**< Deactivateable: 'ComM_Channel.NmSupport' Reason: 'the value of ComM_NmSupportOfChannel is always 'false' due to this, the array is deactivated.' */
#define COMM_NMTYPEOFCHANNEL                                          STD_ON
#define COMM_PASSIVEORLINSLAVEOFCHANNEL                               STD_OFF  /**< Deactivateable: 'ComM_Channel.PassiveOrLinSlave' Reason: 'the value of ComM_PassiveOrLinSlaveOfChannel is always 'false' due to this, the array is deactivated.' */
#define COMM_PNCNMREQUESTOFCHANNEL                                    STD_OFF  /**< Deactivateable: 'ComM_Channel.PncNmRequest' Reason: 'PNC Support is disabled' */
#define COMM_RESETAFTERFORCINGNOCOMMOFCHANNEL                         STD_OFF  /**< Deactivateable: 'ComM_Channel.ResetAfterForcingNoComm' Reason: 'the value of ComM_ResetAfterForcingNoCommOfChannel is always 'false' due to this, the array is deactivated.' */
#define COMM_SILENTSUPPORTOFCHANNEL                                   STD_OFF  /**< Deactivateable: 'ComM_Channel.SilentSupport' Reason: 'the value of ComM_SilentSupportOfChannel is always 'false' due to this, the array is deactivated.' */
#define COMM_WAKEUPSTATEOFCHANNEL                                     STD_ON
#define COMM_CHANNELPB                                                STD_ON
#define COMM_PNCPBINDENDIDXOFCHANNELPB                                STD_OFF  /**< Deactivateable: 'ComM_ChannelPb.PncPbIndEndIdx' Reason: 'the optional indirection is deactivated because PncPbIndUsedOfChannelPb is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define COMM_PNCPBINDSTARTIDXOFCHANNELPB                              STD_OFF  /**< Deactivateable: 'ComM_ChannelPb.PncPbIndStartIdx' Reason: 'the optional indirection is deactivated because PncPbIndUsedOfChannelPb is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define COMM_PNCPBINDUSEDOFCHANNELPB                                  STD_OFF  /**< Deactivateable: 'ComM_ChannelPb.PncPbIndUsed' Reason: 'the optional indirection is deactivated because PncPbIndUsedOfChannelPb is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define COMM_USERREQFULLCOMENDIDXOFCHANNELPB                          STD_ON
#define COMM_USERREQFULLCOMSTARTIDXOFCHANNELPB                        STD_ON
#define COMM_USERREQFULLCOMUSEDOFCHANNELPB                            STD_ON
#define COMM_DCMREQUESTACTIVE                                         STD_ON
#define COMM_FINALMAGICNUMBER                                         STD_OFF  /**< Deactivateable: 'ComM_FinalMagicNumber' Reason: 'the module configuration does not support flashing of data.' */
#define COMM_FULLCOMREQUESTERS                                        STD_OFF  /**< Deactivateable: 'ComM_FullComRequesters' Reason: 'Deactivated because no channel had ComMFullCommRequestNoficiation enabled' */
#define COMM_INITDATAHASHCODE                                         STD_OFF  /**< Deactivateable: 'ComM_InitDataHashCode' Reason: 'the module configuration does not support flashing of data.' */
#define COMM_LASTSTATECHANGE                                          STD_ON
#define COMM_MINFULLCOMMODETIMER                                      STD_ON
#define COMM_NMLIGHTTIMER                                             STD_OFF  /**< Deactivateable: 'ComM_NmLightTimer' Reason: 'Nm Light and Nm Light Silent Timers are disabled' */
#define COMM_PNC                                                      STD_OFF  /**< Deactivateable: 'ComM_Pnc' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define COMM_CLEARMASKOFPNC                                           STD_OFF  /**< Deactivateable: 'ComM_Pnc.ClearMask' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define COMM_COORDINATEDOFPNC                                         STD_OFF  /**< Deactivateable: 'ComM_Pnc.Coordinated' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define COMM_PNCIDOFPNC                                               STD_OFF  /**< Deactivateable: 'ComM_Pnc.PncId' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define COMM_SETMASKOFPNC                                             STD_OFF  /**< Deactivateable: 'ComM_Pnc.SetMask' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define COMM_SYSTEMUSEROFPNC                                          STD_OFF  /**< Deactivateable: 'ComM_Pnc.SystemUser' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define COMM_WAKEUPENABLEDOFPNC                                       STD_OFF  /**< Deactivateable: 'ComM_Pnc.WakeupEnabled' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define COMM_PNCCHANNELMAPPING                                        STD_OFF  /**< Deactivateable: 'ComM_PncChannelMapping' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define COMM_PNCPSLEEPTIMER                                           STD_OFF  /**< Deactivateable: 'ComM_PncPSleepTimer' Reason: 'PNC Support is disabled' */
#define COMM_PNCPB                                                    STD_OFF  /**< Deactivateable: 'ComM_PncPb' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define COMM_PNCCHANNELMAPPINGENDIDXOFPNCPB                           STD_OFF  /**< Deactivateable: 'ComM_PncPb.PncChannelMappingEndIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define COMM_PNCCHANNELMAPPINGSTARTIDXOFPNCPB                         STD_OFF  /**< Deactivateable: 'ComM_PncPb.PncChannelMappingStartIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define COMM_PNCCHANNELMAPPINGUSEDOFPNCPB                             STD_OFF  /**< Deactivateable: 'ComM_PncPb.PncChannelMappingUsed' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define COMM_PNCSIGNALINDENDIDXOFPNCPB                                STD_OFF  /**< Deactivateable: 'ComM_PncPb.PncSignalIndEndIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define COMM_PNCSIGNALINDSTARTIDXOFPNCPB                              STD_OFF  /**< Deactivateable: 'ComM_PncPb.PncSignalIndStartIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define COMM_PNCSIGNALINDUSEDOFPNCPB                                  STD_OFF  /**< Deactivateable: 'ComM_PncPb.PncSignalIndUsed' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define COMM_SIGNALBYTEINDEXOFPNCPB                                   STD_OFF  /**< Deactivateable: 'ComM_PncPb.SignalByteIndex' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define COMM_USERREQPNCFULLCOMENDIDXOFPNCPB                           STD_OFF  /**< Deactivateable: 'ComM_PncPb.UserReqPncFullComEndIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define COMM_USERREQPNCFULLCOMSTARTIDXOFPNCPB                         STD_OFF  /**< Deactivateable: 'ComM_PncPb.UserReqPncFullComStartIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define COMM_PNCPBIND                                                 STD_OFF  /**< Deactivateable: 'ComM_PncPbInd' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define COMM_PNCSIGNAL                                                STD_OFF  /**< Deactivateable: 'ComM_PncSignal' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define COMM_BUSTYPEIDOFPNCSIGNAL                                     STD_OFF  /**< Deactivateable: 'ComM_PncSignal.BusTypeId' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define COMM_CHANNELIDXOFPNCSIGNAL                                    STD_OFF  /**< Deactivateable: 'ComM_PncSignal.ChannelIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define COMM_CHANNELUSEDOFPNCSIGNAL                                   STD_OFF  /**< Deactivateable: 'ComM_PncSignal.ChannelUsed' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define COMM_PNCSIGNALVALUESENDIDXOFPNCSIGNAL                         STD_OFF  /**< Deactivateable: 'ComM_PncSignal.PncSignalValuesEndIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define COMM_PNCSIGNALVALUESSTARTIDXOFPNCSIGNAL                       STD_OFF  /**< Deactivateable: 'ComM_PncSignal.PncSignalValuesStartIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define COMM_PNCSIGNALVALUESUSEDOFPNCSIGNAL                           STD_OFF  /**< Deactivateable: 'ComM_PncSignal.PncSignalValuesUsed' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define COMM_TYPEOFPNCSIGNAL                                          STD_OFF  /**< Deactivateable: 'ComM_PncSignal.Type' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define COMM_PNCSIGNALIND                                             STD_OFF  /**< Deactivateable: 'ComM_PncSignalInd' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define COMM_PNCSIGNALVALUES                                          STD_OFF  /**< Deactivateable: 'ComM_PncSignalValues' Reason: 'the array is deactivated because the size is 0 in all variants and the piece of data is in the configuration class: PRE_COMPILE' */
#define COMM_SIZEOFCHANNEL                                            STD_ON
#define COMM_SIZEOFCHANNELPB                                          STD_ON
#define COMM_SIZEOFDCMREQUESTACTIVE                                   STD_ON
#define COMM_SIZEOFLASTSTATECHANGE                                    STD_ON
#define COMM_SIZEOFMINFULLCOMMODETIMER                                STD_ON
#define COMM_SIZEOFUSER                                               STD_ON
#define COMM_SIZEOFUSERBYTEMASK                                       STD_ON
#define COMM_SIZEOFUSERMODENOTIFUNC                                   STD_ON
#define COMM_SIZEOFUSERREQFULLCOM                                     STD_ON
#define COMM_USER                                                     STD_ON
#define COMM_PNCUSEROFUSER                                            STD_ON
#define COMM_USERBYTEMASKENDIDXOFUSER                                 STD_ON
#define COMM_USERBYTEMASKSTARTIDXOFUSER                               STD_ON
#define COMM_USERBYTEMASKUSEDOFUSER                                   STD_ON
#define COMM_USERPNCBYTEMASKENDIDXOFUSER                              STD_OFF  /**< Deactivateable: 'ComM_User.UserPncByteMaskEndIdx' Reason: 'the optional indirection is deactivated because UserPncByteMaskUsedOfUser is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define COMM_USERPNCBYTEMASKSTARTIDXOFUSER                            STD_OFF  /**< Deactivateable: 'ComM_User.UserPncByteMaskStartIdx' Reason: 'the optional indirection is deactivated because UserPncByteMaskUsedOfUser is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define COMM_USERPNCBYTEMASKUSEDOFUSER                                STD_OFF  /**< Deactivateable: 'ComM_User.UserPncByteMaskUsed' Reason: 'the optional indirection is deactivated because UserPncByteMaskUsedOfUser is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define COMM_USERBYTEMASK                                             STD_ON
#define COMM_CHANNELOFUSERBYTEMASK                                    STD_ON
#define COMM_CLEARMASKOFUSERBYTEMASK                                  STD_ON
#define COMM_SETMASKOFUSERBYTEMASK                                    STD_ON
#define COMM_USERREQFULLCOMIDXOFUSERBYTEMASK                          STD_ON
#define COMM_USERMODENOTIFUNC                                         STD_ON
#define COMM_USERPNCBYTEMASK                                          STD_OFF  /**< Deactivateable: 'ComM_UserPncByteMask' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define COMM_CLEARMASKOFUSERPNCBYTEMASK                               STD_OFF  /**< Deactivateable: 'ComM_UserPncByteMask.ClearMask' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define COMM_PNCIDOFUSERPNCBYTEMASK                                   STD_OFF  /**< Deactivateable: 'ComM_UserPncByteMask.PncID' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define COMM_SETMASKOFUSERPNCBYTEMASK                                 STD_OFF  /**< Deactivateable: 'ComM_UserPncByteMask.SetMask' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define COMM_USERREQPNCFULLCOMIDXOFUSERPNCBYTEMASK                    STD_OFF  /**< Deactivateable: 'ComM_UserPncByteMask.UserReqPncFullComIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define COMM_USERREQFULLCOM                                           STD_ON
#define COMM_USERREQPNCFULLCOM                                        STD_OFF  /**< Deactivateable: 'ComM_UserReqPncFullCom' Reason: 'the array is deactivated because the size is 0 in all variants and the piece of data is in the configuration class: PRE_COMPILE' */
#define COMM_PCCONFIG                                                 STD_ON
#define COMM_CHANNELOFPCCONFIG                                        STD_ON
#define COMM_CHANNELPBOFPCCONFIG                                      STD_ON
#define COMM_DCMREQUESTACTIVEOFPCCONFIG                               STD_ON
#define COMM_FINALMAGICNUMBEROFPCCONFIG                               STD_OFF  /**< Deactivateable: 'ComM_PCConfig.FinalMagicNumber' Reason: 'the module configuration does not support flashing of data.' */
#define COMM_INITDATAHASHCODEOFPCCONFIG                               STD_OFF  /**< Deactivateable: 'ComM_PCConfig.InitDataHashCode' Reason: 'the module configuration does not support flashing of data.' */
#define COMM_LASTSTATECHANGEOFPCCONFIG                                STD_ON
#define COMM_MINFULLCOMMODETIMEROFPCCONFIG                            STD_ON
#define COMM_SIZEOFCHANNELOFPCCONFIG                                  STD_ON
#define COMM_SIZEOFCHANNELPBOFPCCONFIG                                STD_ON
#define COMM_SIZEOFDCMREQUESTACTIVEOFPCCONFIG                         STD_ON
#define COMM_SIZEOFLASTSTATECHANGEOFPCCONFIG                          STD_ON
#define COMM_SIZEOFMINFULLCOMMODETIMEROFPCCONFIG                      STD_ON
#define COMM_SIZEOFUSERBYTEMASKOFPCCONFIG                             STD_ON
#define COMM_SIZEOFUSERMODENOTIFUNCOFPCCONFIG                         STD_ON
#define COMM_SIZEOFUSEROFPCCONFIG                                     STD_ON
#define COMM_SIZEOFUSERREQFULLCOMOFPCCONFIG                           STD_ON
#define COMM_USERBYTEMASKOFPCCONFIG                                   STD_ON
#define COMM_USERMODENOTIFUNCOFPCCONFIG                               STD_ON
#define COMM_USEROFPCCONFIG                                           STD_ON
#define COMM_USERREQFULLCOMOFPCCONFIG                                 STD_ON
/** 
  \}
*/ 

/** 
  \defgroup  ComMPCMinNumericValueDefines  ComM Min Numeric Value Defines (PRE_COMPILE)
  \brief  These defines are used to implement against the minimum value in numerical based data.
  \{
*/ 
#define COMM_MIN_MINFULLCOMMODETIMER                                  0u
#define COMM_MIN_USERREQFULLCOM                                       0u
/** 
  \}
*/ 

/** 
  \defgroup  ComMPCMaxNumericValueDefines  ComM Max Numeric Value Defines (PRE_COMPILE)
  \brief  These defines are used to implement against the maximum value in numerical based data.
  \{
*/ 
#define COMM_MAX_MINFULLCOMMODETIMER                                  65535u
#define COMM_MAX_USERREQFULLCOM                                       255u
/** 
  \}
*/ 

/** 
  \defgroup  ComMPCNoReferenceDefines  ComM No Reference Defines (PRE_COMPILE)
  \brief  These defines are used to indicate unused indexes in data relations.
  \{
*/ 
#define COMM_NO_USERREQFULLCOMENDIDXOFCHANNELPB                       255u
#define COMM_NO_USERREQFULLCOMSTARTIDXOFCHANNELPB                     255u
#define COMM_NO_USERBYTEMASKENDIDXOFUSER                              255u
#define COMM_NO_USERBYTEMASKSTARTIDXOFUSER                            255u
/** 
  \}
*/ 

/** 
  \defgroup  ComMPCEnumExistsDefines  ComM Enum Exists Defines (PRE_COMPILE)
  \brief  These defines can be used to deactivate enumeration based code sequences if the enumeration value does not exist in the configuration data.
  \{
*/ 
#define COMM_EXISTS_NOT_USED_IN_THIS_VARIANT_NMTYPEOFCHANNEL          STD_OFF
#define COMM_EXISTS_FULL_NMTYPEOFCHANNEL                              STD_OFF
#define COMM_EXISTS_PASSIVE_NMTYPEOFCHANNEL                           STD_OFF
#define COMM_EXISTS_LIGHT_NMTYPEOFCHANNEL                             STD_ON
#define COMM_EXISTS_NONE_NMTYPEOFCHANNEL                              STD_OFF
#define COMM_EXISTS_LINSLAVE_NMTYPEOFCHANNEL                          STD_OFF
#define COMM_EXISTS_EIRA_RX_TYPEOFPNCSIGNAL                           STD_OFF  /**< Deactivateable: 'ComM_PncSignal.Type' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define COMM_EXISTS_EIRA_TX_TYPEOFPNCSIGNAL                           STD_OFF  /**< Deactivateable: 'ComM_PncSignal.Type' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define COMM_EXISTS_ERA_RX_TYPEOFPNCSIGNAL                            STD_OFF  /**< Deactivateable: 'ComM_PncSignal.Type' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define COMM_EXISTS_NOT_USED_IN_THIS_VARIANT_TYPEOFPNCSIGNAL          STD_OFF  /**< Deactivateable: 'ComM_PncSignal.Type' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
/** 
  \}
*/ 

/** 
  \defgroup  ComMPCEnumDefines  ComM Enum Defines (PRE_COMPILE)
  \brief  These defines are the enumeration values of enumeration based CONST and VAR data.
  \{
*/ 
#define COMM_LIGHT_NMTYPEOFCHANNEL                                    0x03u
/** 
  \}
*/ 

/** 
  \defgroup  ComMPCIsReducedToDefineDefines  ComM Is Reduced To Define Defines (PRE_COMPILE)
  \brief  If all values in a CONST array or an element in a CONST array of structs are equal, the define is STD_ON else STD_OFF.
  \{
*/ 
#define COMM_ISDEF_BUSTYPEOFCHANNEL                                   STD_ON
#define COMM_ISDEF_GWTYPEOFCHANNEL                                    STD_ON
#define COMM_ISDEF_INHIBITIONINITVALUEOFCHANNEL                       STD_ON
#define COMM_ISDEF_MINFULLCOMTIMEOFCHANNEL                            STD_ON
#define COMM_ISDEF_NMTYPEOFCHANNEL                                    STD_ON
#define COMM_ISDEF_WAKEUPSTATEOFCHANNEL                               STD_ON
#define COMM_ISDEF_USERREQFULLCOMENDIDXOFCHANNELPB                    STD_ON
#define COMM_ISDEF_USERREQFULLCOMSTARTIDXOFCHANNELPB                  STD_ON
#define COMM_ISDEF_USERREQFULLCOMUSEDOFCHANNELPB                      STD_ON
#define COMM_ISDEF_PNCUSEROFUSER                                      STD_OFF
#define COMM_ISDEF_USERBYTEMASKENDIDXOFUSER                           STD_OFF
#define COMM_ISDEF_USERBYTEMASKSTARTIDXOFUSER                         STD_OFF
#define COMM_ISDEF_USERBYTEMASKUSEDOFUSER                             STD_ON
#define COMM_ISDEF_CHANNELOFUSERBYTEMASK                              STD_ON
#define COMM_ISDEF_CLEARMASKOFUSERBYTEMASK                            STD_OFF
#define COMM_ISDEF_SETMASKOFUSERBYTEMASK                              STD_OFF
#define COMM_ISDEF_USERREQFULLCOMIDXOFUSERBYTEMASK                    STD_ON
#define COMM_ISDEF_USERMODENOTIFUNC                                   STD_OFF
#define COMM_ISDEF_CHANNELOFPCCONFIG                                  STD_ON
#define COMM_ISDEF_CHANNELPBOFPCCONFIG                                STD_ON
#define COMM_ISDEF_DCMREQUESTACTIVEOFPCCONFIG                         STD_ON
#define COMM_ISDEF_LASTSTATECHANGEOFPCCONFIG                          STD_ON
#define COMM_ISDEF_MINFULLCOMMODETIMEROFPCCONFIG                      STD_ON
#define COMM_ISDEF_USERBYTEMASKOFPCCONFIG                             STD_ON
#define COMM_ISDEF_USERMODENOTIFUNCOFPCCONFIG                         STD_ON
#define COMM_ISDEF_USEROFPCCONFIG                                     STD_ON
#define COMM_ISDEF_USERREQFULLCOMOFPCCONFIG                           STD_ON
/** 
  \}
*/ 

/** 
  \defgroup  ComMPCEqualsAlwaysToDefines  ComM Equals Always To Defines (PRE_COMPILE)
  \brief  If all values in a CONST array or an element in a CONST array of structs are equal, the define contains the always equals value.
  \{
*/ 
#define COMM_EQ2_BUSTYPEOFCHANNEL                                     COMM_BUS_TYPE_CAN
#define COMM_EQ2_GWTYPEOFCHANNEL                                      COMM_GATEWAY_TYPE_NONE
#define COMM_EQ2_INHIBITIONINITVALUEOFCHANNEL                         0x00u
#define COMM_EQ2_MINFULLCOMTIMEOFCHANNEL                              250u
#define COMM_EQ2_NMTYPEOFCHANNEL                                      COMM_LIGHT_NMTYPEOFCHANNEL
#define COMM_EQ2_WAKEUPSTATEOFCHANNEL                                 COMM_FULL_COM_NETWORK_REQUESTED
#define COMM_EQ2_USERREQFULLCOMENDIDXOFCHANNELPB                      1u
#define COMM_EQ2_USERREQFULLCOMSTARTIDXOFCHANNELPB                    0u
#define COMM_EQ2_USERREQFULLCOMUSEDOFCHANNELPB                        TRUE
#define COMM_EQ2_PNCUSEROFUSER                                        
#define COMM_EQ2_USERBYTEMASKENDIDXOFUSER                             
#define COMM_EQ2_USERBYTEMASKSTARTIDXOFUSER                           
#define COMM_EQ2_USERBYTEMASKUSEDOFUSER                               TRUE
#define COMM_EQ2_CHANNELOFUSERBYTEMASK                                0u
#define COMM_EQ2_CLEARMASKOFUSERBYTEMASK                              
#define COMM_EQ2_SETMASKOFUSERBYTEMASK                                
#define COMM_EQ2_USERREQFULLCOMIDXOFUSERBYTEMASK                      0u
#define COMM_EQ2_USERMODENOTIFUNC                                     
#define COMM_EQ2_CHANNELOFPCCONFIG                                    ComM_Channel
#define COMM_EQ2_CHANNELPBOFPCCONFIG                                  ComM_ChannelPb
#define COMM_EQ2_DCMREQUESTACTIVEOFPCCONFIG                           ComM_DcmRequestActive.raw
#define COMM_EQ2_LASTSTATECHANGEOFPCCONFIG                            ComM_LastStateChange
#define COMM_EQ2_MINFULLCOMMODETIMEROFPCCONFIG                        ComM_MinFullComModeTimer.raw
#define COMM_EQ2_USERBYTEMASKOFPCCONFIG                               ComM_UserByteMask
#define COMM_EQ2_USERMODENOTIFUNCOFPCCONFIG                           ComM_UserModeNotiFunc
#define COMM_EQ2_USEROFPCCONFIG                                       ComM_User
#define COMM_EQ2_USERREQFULLCOMOFPCCONFIG                             ComM_UserReqFullCom
/** 
  \}
*/ 

/** 
  \defgroup  ComMPCSymbolicInitializationPointers  ComM Symbolic Initialization Pointers (PRE_COMPILE)
  \brief  Symbolic initialization pointers to be used in the call of a preinit or init function.
  \{
*/ 
#define ComM_Config_Ptr                                               NULL_PTR  /**< symbolic identifier which shall be used to initialize 'ComM' */
/** 
  \}
*/ 

/** 
  \defgroup  ComMPCInitializationSymbols  ComM Initialization Symbols (PRE_COMPILE)
  \brief  Symbolic initialization pointers which may be used in the call of a preinit or init function. Please note, that the defined value can be a 'NULL_PTR' and the address operator is not usable.
  \{
*/ 
#define ComM_Config                                                   NULL_PTR  /**< symbolic identifier which could be used to initialize 'ComM */
/** 
  \}
*/ 

/** 
  \defgroup  ComMPCGeneral  ComM General (PRE_COMPILE)
  \brief  General constant defines not associated with a group of defines.
  \{
*/ 
#define COMM_CHECK_INIT_POINTER                                       STD_OFF  /**< STD_ON if the init pointer shall not be used as NULL_PTR and a check shall validate this. */
#define COMM_FINAL_MAGIC_NUMBER                                       0x0C1Eu  /**< the precompile constant to validate the size of the initialization structure at initialization time of ComM */
#define COMM_INDIVIDUAL_POSTBUILD                                     STD_OFF  /**< the precompile constant to check, that the module is individual postbuildable. The module 'ComM' is not configured to be postbuild capable. */
#define COMM_INIT_DATA                                                COMM_CONST  /**< CompilerMemClassDefine for the initialization data. */
#define COMM_INIT_DATA_HASH_CODE                                      -215872543  /**< the precompile constant to validate the initialization structure at initialization time of ComM with a hashcode. The seed value is '0x0C1Eu' */
#define COMM_USE_ECUM_BSW_ERROR_HOOK                                  STD_OFF  /**< STD_ON if the EcuM_BswErrorHook shall be called in the ConfigPtr check. */
#define COMM_USE_INIT_POINTER                                         STD_OFF  /**< STD_ON if the init pointer ComM shall be used. */
/** 
  \}
*/ 



/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
typedef P2FUNC(Std_ReturnType, COMM_CODE, ComM_StateNotiFuncPtrType) (Rte_ModeType_ComMMode  nextMode);

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL SIMPLE DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/** 
  \defgroup  ComMPCIterableTypes  ComM Iterable Types (PRE_COMPILE)
  \brief  These type definitions are used to iterate over an array with least processor cycles for variable access as possible.
  \{
*/ 
/**   \brief  type used to iterate ComM_Channel */
typedef uint8_least ComM_ChannelIterType;

/**   \brief  type used to iterate ComM_ChannelPb */
typedef uint8_least ComM_ChannelPbIterType;

/**   \brief  type used to iterate ComM_User */
typedef uint8_least ComM_UserIterType;

/**   \brief  type used to iterate ComM_UserByteMask */
typedef uint8_least ComM_UserByteMaskIterType;

/**   \brief  type used to iterate ComM_UserModeNotiFunc */
typedef uint8_least ComM_UserModeNotiFuncIterType;

/**   \brief  type used to iterate ComM_UserReqFullCom */
typedef uint8_least ComM_UserReqFullComIterType;

/** 
  \}
*/ 

/** 
  \defgroup  ComMPCIterableTypesWithSizeRelations  ComM Iterable Types With Size Relations (PRE_COMPILE)
  \brief  These type definitions are used to iterate over a VAR based array with the same iterator as the related CONST array.
  \{
*/ 
/**   \brief  type used to iterate ComM_DcmRequestActive */
typedef ComM_ChannelIterType ComM_DcmRequestActiveIterType;

/**   \brief  type used to iterate ComM_LastStateChange */
typedef ComM_UserIterType ComM_LastStateChangeIterType;

/**   \brief  type used to iterate ComM_MinFullComModeTimer */
typedef ComM_ChannelIterType ComM_MinFullComModeTimerIterType;

/** 
  \}
*/ 

/** 
  \defgroup  ComMPCValueTypes  ComM Value Types (PRE_COMPILE)
  \brief  These type definitions are used for value based data representations.
  \{
*/ 
/**   \brief  value based type definition for ComM_GwTypeOfChannel */
typedef uint8 ComM_GwTypeOfChannelType;

/**   \brief  value based type definition for ComM_InhibitionInitValueOfChannel */
typedef uint8 ComM_InhibitionInitValueOfChannelType;

/**   \brief  value based type definition for ComM_MinFullComTimeOfChannel */
typedef uint8 ComM_MinFullComTimeOfChannelType;

/**   \brief  value based type definition for ComM_NmTypeOfChannel */
typedef uint8 ComM_NmTypeOfChannelType;

/**   \brief  value based type definition for ComM_WakeupStateOfChannel */
typedef uint8 ComM_WakeupStateOfChannelType;

/**   \brief  value based type definition for ComM_UserReqFullComEndIdxOfChannelPb */
typedef uint8 ComM_UserReqFullComEndIdxOfChannelPbType;

/**   \brief  value based type definition for ComM_UserReqFullComStartIdxOfChannelPb */
typedef uint8 ComM_UserReqFullComStartIdxOfChannelPbType;

/**   \brief  value based type definition for ComM_UserReqFullComUsedOfChannelPb */
typedef boolean ComM_UserReqFullComUsedOfChannelPbType;

/**   \brief  value based type definition for ComM_DcmRequestActive */
typedef boolean ComM_DcmRequestActiveType;

/**   \brief  value based type definition for ComM_MinFullComModeTimer */
typedef uint16 ComM_MinFullComModeTimerType;

/**   \brief  value based type definition for ComM_SizeOfChannel */
typedef uint8 ComM_SizeOfChannelType;

/**   \brief  value based type definition for ComM_SizeOfChannelPb */
typedef uint8 ComM_SizeOfChannelPbType;

/**   \brief  value based type definition for ComM_SizeOfDcmRequestActive */
typedef uint8 ComM_SizeOfDcmRequestActiveType;

/**   \brief  value based type definition for ComM_SizeOfLastStateChange */
typedef uint8 ComM_SizeOfLastStateChangeType;

/**   \brief  value based type definition for ComM_SizeOfMinFullComModeTimer */
typedef uint8 ComM_SizeOfMinFullComModeTimerType;

/**   \brief  value based type definition for ComM_SizeOfUser */
typedef uint8 ComM_SizeOfUserType;

/**   \brief  value based type definition for ComM_SizeOfUserByteMask */
typedef uint8 ComM_SizeOfUserByteMaskType;

/**   \brief  value based type definition for ComM_SizeOfUserModeNotiFunc */
typedef uint8 ComM_SizeOfUserModeNotiFuncType;

/**   \brief  value based type definition for ComM_SizeOfUserReqFullCom */
typedef uint8 ComM_SizeOfUserReqFullComType;

/**   \brief  value based type definition for ComM_PncUserOfUser */
typedef boolean ComM_PncUserOfUserType;

/**   \brief  value based type definition for ComM_UserByteMaskEndIdxOfUser */
typedef uint8 ComM_UserByteMaskEndIdxOfUserType;

/**   \brief  value based type definition for ComM_UserByteMaskStartIdxOfUser */
typedef uint8 ComM_UserByteMaskStartIdxOfUserType;

/**   \brief  value based type definition for ComM_UserByteMaskUsedOfUser */
typedef boolean ComM_UserByteMaskUsedOfUserType;

/**   \brief  value based type definition for ComM_ChannelOfUserByteMask */
typedef uint8 ComM_ChannelOfUserByteMaskType;

/**   \brief  value based type definition for ComM_ClearMaskOfUserByteMask */
typedef uint8 ComM_ClearMaskOfUserByteMaskType;

/**   \brief  value based type definition for ComM_SetMaskOfUserByteMask */
typedef uint8 ComM_SetMaskOfUserByteMaskType;

/**   \brief  value based type definition for ComM_UserReqFullComIdxOfUserByteMask */
typedef uint8 ComM_UserReqFullComIdxOfUserByteMaskType;

/**   \brief  value based type definition for ComM_UserReqFullCom */
typedef uint8 ComM_UserReqFullComType;

/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL COMPLEX DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/** 
  \defgroup  ComMPCStructTypes  ComM Struct Types (PRE_COMPILE)
  \brief  These type definitions are used for structured data representations.
  \{
*/ 
/**   \brief  type used in ComM_Channel */
typedef struct sComM_ChannelType
{
  uint8 ComM_ChannelNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} ComM_ChannelType;

/**   \brief  type used in ComM_ChannelPb */
typedef struct sComM_ChannelPbType
{
  uint8 ComM_ChannelPbNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} ComM_ChannelPbType;

/**   \brief  type used in ComM_User */
typedef struct sComM_UserType
{
  ComM_PncUserOfUserType PncUserOfUser;  /**< decides if a user is a partial network user or a direct channel user */
  ComM_UserByteMaskEndIdxOfUserType UserByteMaskEndIdxOfUser;  /**< the end index of the 0:n relation pointing to ComM_UserByteMask */
  ComM_UserByteMaskStartIdxOfUserType UserByteMaskStartIdxOfUser;  /**< the start index of the 0:n relation pointing to ComM_UserByteMask */
} ComM_UserType;

/**   \brief  type used in ComM_UserByteMask */
typedef struct sComM_UserByteMaskType
{
  ComM_ClearMaskOfUserByteMaskType ClearMaskOfUserByteMask;  /**< Clear-mask for clearing the bit which corresponds to this user */
  ComM_SetMaskOfUserByteMaskType SetMaskOfUserByteMask;  /**< Set-mask for setting the bit which corresponds to this user */
} ComM_UserByteMaskType;

/** 
  \}
*/ 

/** 
  \defgroup  ComMPCSymbolicStructTypes  ComM Symbolic Struct Types (PRE_COMPILE)
  \brief  These structs are used in unions to have a symbol based data representation style.
  \{
*/ 
/**   \brief  type to be used as symbolic data element access to ComM_DcmRequestActive */
typedef struct ComM_DcmRequestActiveStructSTag
{
  ComM_DcmRequestActiveType ComMChannel_0;
} ComM_DcmRequestActiveStructSType;

/**   \brief  type to be used as symbolic data element access to ComM_MinFullComModeTimer */
typedef struct ComM_MinFullComModeTimerStructSTag
{
  ComM_MinFullComModeTimerType ComMChannel_0;
} ComM_MinFullComModeTimerStructSType;

/** 
  \}
*/ 

/** 
  \defgroup  ComMPCUnionIndexAndSymbolTypes  ComM Union Index And Symbol Types (PRE_COMPILE)
  \brief  These unions are used to access arrays in an index and symbol based style.
  \{
*/ 
/**   \brief  type to access ComM_DcmRequestActive in an index and symbol based style. */
typedef union ComM_DcmRequestActiveUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  ComM_DcmRequestActiveType raw[1];
  ComM_DcmRequestActiveStructSType str;
} ComM_DcmRequestActiveUType;

/**   \brief  type to access ComM_MinFullComModeTimer in an index and symbol based style. */
typedef union ComM_MinFullComModeTimerUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  ComM_MinFullComModeTimerType raw[1];
  ComM_MinFullComModeTimerStructSType str;
} ComM_MinFullComModeTimerUType;

/** 
  \}
*/ 

/** 
  \defgroup  ComMPCRootPointerTypes  ComM Root Pointer Types (PRE_COMPILE)
  \brief  These type definitions are used to point from the config root to symbol instances.
  \{
*/ 
/**   \brief  type used to point to ComM_Channel */
typedef P2CONST(ComM_ChannelType, TYPEDEF, COMM_CONST) ComM_ChannelPtrType;

/**   \brief  type used to point to ComM_ChannelPb */
typedef P2CONST(ComM_ChannelPbType, TYPEDEF, COMM_CONST) ComM_ChannelPbPtrType;

/**   \brief  type used to point to ComM_DcmRequestActive */
typedef P2VAR(ComM_DcmRequestActiveType, TYPEDEF, COMM_VAR_NOINIT) ComM_DcmRequestActivePtrType;

/**   \brief  type used to point to ComM_LastStateChange */
typedef P2VAR(ComM_ModeType, TYPEDEF, COMM_VAR_NOINIT) ComM_LastStateChangePtrType;

/**   \brief  type used to point to ComM_MinFullComModeTimer */
typedef P2VAR(ComM_MinFullComModeTimerType, TYPEDEF, COMM_VAR_NOINIT) ComM_MinFullComModeTimerPtrType;

/**   \brief  type used to point to ComM_User */
typedef P2CONST(ComM_UserType, TYPEDEF, COMM_CONST) ComM_UserPtrType;

/**   \brief  type used to point to ComM_UserByteMask */
typedef P2CONST(ComM_UserByteMaskType, TYPEDEF, COMM_CONST) ComM_UserByteMaskPtrType;

/**   \brief  type used to point to ComM_UserModeNotiFunc */
typedef P2CONST(ComM_StateNotiFuncPtrType, TYPEDEF, COMM_CONST) ComM_UserModeNotiFuncPtrType;

/**   \brief  type used to point to ComM_UserReqFullCom */
typedef P2VAR(ComM_UserReqFullComType, TYPEDEF, COMM_VAR_NOINIT) ComM_UserReqFullComPtrType;

/** 
  \}
*/ 

/** 
  \defgroup  ComMPCRootValueTypes  ComM Root Value Types (PRE_COMPILE)
  \brief  These type definitions are used for value representations in root arrays.
  \{
*/ 
/**   \brief  type used in ComM_PCConfig */
typedef struct sComM_PCConfigType
{
  uint8 ComM_PCConfigNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} ComM_PCConfigType;

typedef ComM_PCConfigType ComM_ConfigType;  /**< A structure type is present for data in each configuration class. This typedef redefines the probably different name to the specified one. */

/** 
  \}
*/ 




#endif /* COMM_CFG_H */

