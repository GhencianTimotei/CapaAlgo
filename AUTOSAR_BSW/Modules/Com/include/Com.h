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
/*!        \file  Com.h
 *        \brief  MICROSAR Communication header file
 *
 *      \details  This is the implementation of the MICROSAR Communication module.
 *                The basic software module is based on the AUTOSAR Communication specification.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2011-12-07  visms   -             derived initial Cfg5 version from Il_AsrCom 3.21.00
 *            2011-12-21  visdbi  -             first version Il_AsrComCfg5
 *            2012-03-16  visdbi  ESCAN00055751 AR3-2330: Extend the CFG5 Support
 *  01.00.01  2012-03-29  visdbi  ESCAN00057998 Provide AUTOSAR data-type definitions in Com_Cfg.h
 *  02.00.00  2012-06-14  visdbi  ESCAN00058306 AR4-160 AUTOSAR 4.0.3 Support
 *                        visdbi  ESCAN00059339 Transfer property or TMS not evaluated as expected
 *                        visdbi  ESCAN00059340 Compiler warning: undefined functions
 *                        visdbi  ESCAN00059113 Compiler error: parse error near 'Com_FilterAlgoOfSigFilterInfoType'
 *                        visdbi  ESCAN00059109 Compiler error: identifier sigGrpHnd not declared
 *            2012-07-12  visdbi  ESCAN00060077 AR4-67: ASR4 Handle Concept
 *            2012-07-19  visdbi  ESCAN00060210 Linker error: Symbol Com_IsApplTypeUint8NOfSigInfo not found
 *  02.01.00  2012-09-12  visdbi  ESCAN00061351 Several features not functional
 *                        visdbi  ESCAN00061355 ASR4: Replication of Signal Transmission Requests not functional
 *            2012-11-08  visdbi  ESCAN00061792 AR4-199: Support Signal Data Invalidation
 *                        visdbi  ESCAN00061801 AR4-204: Support Update Bits
 *                        visdbi  ESCAN00062866 Support Signal Based Reception
 *            2012-11-29  visdbi  ESCAN00061807 AR4-212: Support Rx Filter
 *                        visdbi  ESCAN00063565 AR4-306: Support TRIGGERED_ON_CHANGE for uint8_N signals
 *            2012-12-05  visdbi  ESCAN00063384 Separate Misra/PcLint comments with blank
 *            2012-12-06  visdbi  ESCAN00063289 Improved Transition Mode Switch behavior
 *                        visdbi  ESCAN00063569 ASR4.0.3  compliance: Minimum Delay Timer
 *                        visdbi  ESCAN00062810 Use upper case 'U' suffix for unsigned variables / numbers
 *                        visdbi  ESCAN00062282 OS error 0x2C01 occurs
 *                        visdbi  ESCAN00063578 Copy Tx Signal Value Routine Optimization
 *            2012-12-13  visdbi  ESCAN00063708 Unexpected transmission mode behavior
 *            2012-12-18  visdbi  ESCAN00063559 Compiler error  in special configuration
 *                        visdbi  ESCAN00063496 Compiler errors occur in Tx only configuration
 *                        visdbi  ESCAN00062703 Compiler errors occur in Rx only configuration
 *                        visdbi  ESCAN00063259 Linker error: Com_IsInitModeOfTxModeInfo undefined
 *            2012-12-20  visdbi  ESCAN00063836 Use address getter macros
 *  02.02.00  2013-02-14  visms vishho visdbi
 *                                ESCAN00064302 AR4-325: Implement Post-Build Loadable
 *            2013-03-01  visdbi  ESCAN00065326 Exclusive Area Optimization
 *            2013-03-14  visdbi  ESCAN00064079 AR4-211: Support Signal Gateway
 *            2013-03-19  visms   ESCAN00064484 AR4-282: Export BSW DBG Data
 *            2013-04-03  visdbi  ESCAN00065565 Delayed Transmission of COM Tx I-PDU
 *            2013-04-10  visswa  ESCAN00066492 MISRA compliance
 *            2013-04-15  visdbi  ESCAN00066651 Incorrect reception of UINT8_N signals
 *                        visdbi  ESCAN00066653 Unexpected behavior after initialization
 *  03.00.00  2013-06-19  visdbi  ESCAN00067819 Cyclic transmission after triggered event with repetitions
 *                        visdbi  ESCAN00067769 ComPdu data can be modified after the call of the IPdu Trigger Transmit Callout function
 *                        visdbi  ESCAN00068097 Support AUTOSAR 4.0.3 I-PDU callout prototypes
 *                        vishho  ESCAN00068673 AR4-307: Support TP SDUs and dynamic length signals
 *            2013-07-23  vishho  ESCAN00069149 Include "SchM_Com.h" only in source files
 *            2013-07-26  vishho  visdbi
 *                                ESCAN00069359 AR4-520: Support Dynamic Rx DLC
 *            2013-08-07  visdbi  ESCAN00069650 AR4-205: Support Tx Timeout
 *            2013-08-08  visdbi  ESCAN00069677 Use generated increment/decrement macros
 *            2013-08-12  visdbi  ESCAN00069727 0-Bit signal support
 *            2013-08-16  vishho  ESCAN00069871 The prefix of VAR data shall be <Msn> followed by '_'
 *            2013-09-04  visdbi  ESCAN00070065 Compiler warning: Unreferenced parameter 'SignalDataPtr' in function Com_SendSignal
 *                        visdbi  ESCAN00069990 Compiler warning: Unreferenced parameter 'SignalId' in function Com_SendSignal
 *                        visdbi  ESCAN00069991 Compiler warning: Unreferenced parameter 'SignalGroupId' in function Com_ReceiveSignalGroup
 *                        visdbi  ESCAN00069996 Compiler warning: Unreferenced parameter 'idxFilterInfo' in function Com_Signal_EvaluateFilter
 *                        visdbi  ESCAN00069994 Compiler warning: Unreferenced parameter 'TxPduId' in function Com_TxBuffer_WriteIpduSignal
 *                        visdbi  ESCAN00069993 Compiler warning: Unreferenced parameter 'ComPduId' in function Com_LMgt_InitRxIpdu
 *                        vishho  ESCAN00069969 Compiler warning: Unreachable code in Com_ReceiveSignalGroup() API
 *                        visdbi  ESCAN00064672 Compiler warning: Unreferenced parameter 'SignalId' in function Com_ReceiveSignal
 *            2013-09-19  vishho  ESCAN00070511 AR4-307: Add Confirmation as ComTxIPduClearUpdateBit context
 *            2013-10-22  vishho  ESCAN00071307 Removed ASR3 support from single source
 *  03.01.00  2013-12-06  vishho  ESCAN00072488 Implement alive timeout behaviour according to Bugzilla 52102
 *            2013-12-11  vishho  ESCAN00071571 Remove Com_LMgt_TxIpduActive check from the API  Com_TxModeHdlr_Confirmation
 *            2013-12-13  vishho  ESCAN00072588 Make it possible to filter with negative values.
 *            2013-12-17  vishho  ESCAN00072687 AR4-569: Reset the minimum delay counter if Tx timeout occurs.
 *            2014-01-07  vishho  ESCAN00072739 Compiler error: Com.c() 'Com_PduGrpVectorEndIdxOfRxPduGrpInfoType' : undeclared identifier
 *            2014-01-14  vishho  ESCAN00072954 ComTxTimeouts initalisation writes out of bounds.
 *            2014-01-20  vishho  ESCAN00073070 Remove "is Initialized" DET check in the function Com_ClearIpduGroupVector
 *            2014-03-04  vishho  ESCAN00074050 A call of Com_TpTxConfirmation with a negative result will block the Com TP state machine
 *            2014-03-04  vishho  ESCAN00074051 Negative callout return value will block the Com TP state machine
 *  04.00.00  2014-03-12  vishho  ESCAN00070541 AR4-345: Implement PF4_PostBuildSelectable
 *            2014-03-25  vishho  ESCAN00071921 AR4-619: Support the StartOfReception API (with the PduInfoType), TxConfirmation and RxIndication according ASR4.1.2
 *            2014-04-17  vishho  ESCAN00074387 AR4-710: Support IPDUGroup relevant API like as ASR3 API
 *            2014-05-08  vishho  ESCAN00074113 AR4-642: Deleting container at post-build time
 *            2014-05-09  visbms  ESCAN00073892 AR4-601: Implement request handling
 *            2014-06-02  vishho  ESCAN00076011 Transmission of Messages is started without trigger
 *  04.00.01  2014-07-02  vishho  ESCAN00076677 ComOptimizedIPduGroupHandling not functional in variant POST-BUILD-LOADABLE
 *  04.00.02  2014-07-15  visbms  ESCAN00077100 Compiler error: Com.c: 'COM_VALIDHNDOFTXPDUINFO' is not defined as a preprocessor macro
 *  05.00.00  2014-08-18  visbms  ESCAN00077910 Missing compiler abstraction in Com_TriggerIPDUSendWithMetaData()
 *  07.00.00  2014-11-13  visms visgut
 *                                ESCAN00081777 FEAT-1275: SafeBSW Step 2
 *            2014-12-09  vishho  ESCAN00079731 Compiler warning: conversion from 'int' to 'Com_CycleTimeCntType', possible loss of data
 *            2015-03-25  visbms  ESCAN00081923 Lower layer is triggered with wrong SduLength if TP and IF PDUs with meta data are configured
 *            2015-05-06  vishho  ESCAN00082638 FEAT-1047: Gateway Rx signal timeout handling without update bits [AR4-894]
 *            2015-05-07  vishho  ESCAN00082891 The invalid action (notify/replace) of a Signal Group is executed although a valid value is received.
 *            2015-05-11  vishho  ESCAN00082928 FEAT-511: Support Ford SDLC: Support TxConfirmation  function calls in context of the Transmit function
 *            2015-06-24  vishho  ESCAN00079638 incorrect data is copied if a UINT8_DYN signal is copied on a BIG_ENDIAN Hardware.
 *            2015-07-15  visgut  ESCAN00084006 FEAT-77: COM Based Transformer for CONC_601_SenderReceiverSerialization incl. E2EXf [AR4-829]
 *  8.01.00   2015-08-11  visgut  Com Optimization
 *            2015-08-11  visgut  ESCAN00085310 FEAT-1436: MainFunction Timing Domains
 *            2015-08-11  visgut  ESCAN00085310 FEAT-1436: Deferred Event Caching
 *            2015-09-11  visgut  ESCAN00085310 FEAT-1436: Description Routing
 *            2015-10-01  vishho  ESCAN00085594 Incorrect reception of UINT8_DYN ComSignals and ComSignalGroups on BIG_ENDIAN hardware
 *            2015-11-04  visms   ESCAN00086287 SignalGroup with Update bit is not marked as updated although the UpdateBit is not contained in the PDU.
 *            2015-11-27  vishho  ESCAN00085931 Compiler warning: conversion from 'typeX' to 'typeY', possible loss of data
 *            2015-12-11  vishho  ESCAN00078850 Missing NULL_PTR check in  Com_ReceiveSignal
 *  09.00.00  2016-01-29  visgut  ESCAN00087943 Missing preprocessor encapsulation in Com_ReceiveSignalGroupArrayAPI
 *            2016-02-22  visgut  ESCAN00088468 Missing preprocessor encapsulation in Com_SendSignalGroupArrayAPI for PENDING only configuration.
 *            2016-02-24  visgut  ESCAN00088514 Missing parameter in Com_Signal_ReadSignalApplTypeSpecific for BigEndian CPU byte order.
 *            2016-02-26  visms   ESCAN00087832 FEAT-1631: Trigger Transmit API with SduLength In/Out according to ASR4.2.2
 *            2016-02-25  visgut  ESCAN00088557 Wrong initialization of shadow buffer if handle ID gaps are present.
 *            2016-02-26  visgut  ESCAN00088580 Wrong behaviour of dynamic length signals on big endian hardware, if a byte offset is present.
 *            2016-05-30  vishho  ESCAN00090216 A Rx Signal Group with Array Access is not initialized
 *            2016-05-30  vishho  ESCAN00090836 Fix through implementation of threshold pattern for opening closing exclusive area for deferred Rx Pdu Processing.
 *            2016-06-05  vishho visgut visms
 *                                ESCAN00087795 FEAT-1688: SafeBSW Step 4
 *  09.00.01  2016-06-14  visgut  ESCAN00090483 Wrong behaviour on reception of byte aligned  16Bit and 32 Bit big endian signals on big endian hardware
 *  10.00.00  2016-06-28  visgut  ESCAN00090733 Compiler warning: Missing cast in Com_TxSignal_EvaluateFilter()
 *            2016-07-07  visgut  ESCAN00090882 FEAT-1640: Implement ISR threshold strategy and notification function pointer caching optimization.
 *            2016-06-28  visbbk  ESCAN00090880 FEAT-1818: Enable minimum delay time for cyclic transmission
 *            2016-07-12  vishho  ESCAN00090949 Com_ReceptionDMControl shall call no DET if the function is call although no Reception Timeout is configured
 *            2016-07-12  visgut  ESCAN00090838 Compiler error due to wrong encapsulation of gateway description source code.
 *  10.00.01  2016-08-09  visgut  ESCAN00091376 Compiler warning due to usage of wrong variable type for rx signals/ group signals.
 *            2016-08-09  visgut  ESCAN00091375 Compiler error due to usage of undeclared variable type for array based tx signals/ group signals.
 *  11.00.00  2016-08-17  visgut  ESCAN00091506 Wrong Sdu length is provided to lower layer when sending non-dynamic length group signals of TP Pdus.
 *            2016-08-24  visgut  ESCAN00091620 Compiler error due to undeclared identifier for configured gateway description.
 *            2016-09-15  visgut  ESCAN00091922 Gateway description deferred event flag not initialized on call of Com_Init.
 *            2016-09-20  visgut  ESCAN00091958 Wrong initialization of Tx Sdu length in TP context.
 *            2016-09-23  visbbk  ESCAN00092007 FEAT-2002: Support 64 Bit Signal Types for COM according to ASR 4.2.2
 *            2016-10-17  visgut  ESCAN00092336 Immediate event based Gw Description Routing on non event based TxModeMode
 *            2016-10-18  visbbk  ESCAN00092352 Read from NULL_PTR for deferred I-PDUs
 *            2016-10-18  visbbk  ESCAN00092487 Compiler error: Undefined variable Com_FilterInfo<ApplType>IterType
 *            2016-10-26  visgut  ESCAN00092532 Compiler error: Undefined reference to Com_RxInv_Sig_UInt8_N_EvaluateInvalidValue
 *            2016-10-26  visgut  ESCAN00092286 FEAT-1890: Extension of gateway description routing with shifted copy and update bit support.
 *            2016-11-10  visgut  ESCAN00092737 Compiler error: Wrong encapsulation of Length Parameter when calling Com_SetTxFilterOldValueX
 *            2016-11-15  visgut  ESCAN00092792 Minimum delay time for cyclic transmission does not comply with Gw Description Routing
 *            2016-11-16  visgut  ESCAN00092835 Missing initialization for deferred source ComIPdu of GwDescriptionRouting triggers the transmission of destination ComIPdu.
 *            2016-11-23  visbbk  ESCAN00092749 Wrong SduLength for deferred Rx I-PDUs.
 *  12.00.00  2016-12-21  visgut  FEATC-510     FEAT-2362: AUTOSAR 4.2.2 SWS Traceability Goals 2&3 for Com (Il_AsrComCfg5) (FEAT-2036 cont.)
 *            2017-01-12  visgut  FEATC-797     FEAT-2333: Support Tx Timeout for cyclic messages
 *            2017-01-13  visbbk  FEATC-792     FEAT-2179: Refactor 0 Bit Signals
 *            2017-01-18  visgut  ESCAN00093087 Remove DET Error for stopped I-PDU Group in TP APIs
 *            2017-01-20  visbbk  FEATC-850     FEAT-2386: WriteOutOfBoundsWriteProtectionStrategy with INDEX_SATURATION and INDEX_CHECKING shall not be used in productive builds
 *            2017-03-23  vishho  ESCAN00094463 Cyclic transmission does not start after a Bus Off occurred.
 *  13.00.00  2017-04-10  visgut  STORYC-18     Support IPDUs without IPDU Group assignment in COM
 *            2017-03-31  visbbk  STORYC-164    Implement MASKED_NEW_EQUALS_X and MASKED_NEW_DIFFERS_X for Signal Group Arrays in Com
 *  13.01.00  2017-04-26  visbbk  STORYC-694    Implement MASKED_NEW_EQUALS_X and MASKED_NEW_DIFFERS_X for Signal Group Arrays in Com
 *            2017-04-26  visbbk  ESCAN00094772 Support filter for ArrayBased SignalGroups
 *            2017-05-05  visbbk  ESCAN00094938 Compiler error: Undefined function Com_TxModeHdlr_UpdateTMS
 *            2017-04-13  vishho  ESCAN00095939 Compiler error:"COM_UINT8_N_APPLTYPEOFRXACCESSINFO" is undefined
 *  13.02.00  2017-05-29  visbbk  STORYC-1205   Rework of COM
 *            2017-06-08  visbbk  ESCAN00095471 Datatype conversion, possible loss of data
 *  13.03.00  2017-06-14  visbbk  STORYC-1029   Routing for Group Signals with Array Access
 *            2017-06-14  visbbk  ESCAN00095528 Undeclared Identifier 'COM_UINT8_APPLTYPEOFRXACCESSINFO'
 *            2017-06-19  visbbk  ESCAN00095488 Datatype conversion for description routing, possible loss of Data
 *            2017-06-28  visgut  STORYC-1675   Clear RetryFailedTransmitRequest on Tx Timeout
 *  13.03.01  2017-08-01  vishho  ESCAN00096126 Com_Init may lead to long interrupt locks
 *            2017-08-01  vishho  ESCAN00095907 Compiler warning: Com.c(4142): warning C4100: 'idxFilterInfo' : unreferenced formal parameter
 *  14.00.00  2017-10-18  visgut  ESCAN00097092 Compiler error: Identifier "sint"<X> is undefined
 *            2017-10-18  visbbk  STORYC-2475   Support Float32 and Float64
 *            2017-10-18  visgut  ESCAN00097086 Compiler error: Undefined reference to Com_GetTxFilterInitValueArrayBasedFilterInitValueLengthOfTxSigInfo
 *  14.00.01  2018-01-15  visgut  ESCAN00097911 Deferred PDUs are not processed using deferred event Cache
 *  15.00.00  2018-04-10  visssg  STORYC-4399   MISRA-C:2012 Com
 *            2018-04-27  visbbk  ESCAN00087948 Update Bits are not cleared if Com_IpduGroupControl is called with initialize = false
 *            2018-05-02  visms   ESCAN00099286 Compiler warning: unused parameter 'ipduGroupVector' and 'initialize' in  function 'Com_IpduGroupControl'
 *            2018-05-02  visms   ESCAN00099287 Compiler warning: unused parameter 'deferredfctPtrCacheStrctPtr' in  function 'Com_RxProcessDeferredPDU'
 *            2018-05-03  visbbk  ESCAN00099291 Compiler warning: unused parameter 'PduInfoPtr' in  function 'Com_RxSignalProcessing'
 *            2018-05-03  visbbk  ESCAN00099292 Compiler warning: unused parameter 'idxTxSigInfo' in  function 'Com_SendSignal_WriteSignal'
 *            2018-05-03  visms   ESCAN00099300 Compiler warning: unused parameter 'newValue' in  function 'Com_Signal_Float32_EvaluateFilter' and 'Com_Signal_Float64_EvaluateFilter'
 *  15.01.00  2018-05-15  visgut  STORYC-3089   Respect ComTxModeTimeOffset in combination with Com_SwitchIpduTxMode
 *  15.01.01  2018-08-16  visgut  ESCAN00098036 Cyclic PDUs with a ComGwRoutingTimeout are triggered when started if ComTxDlMonTimeBase is configured
 *            2018-08-22  visms   ESCAN00100469 MISRA deviation: MISRA-C:2012 Dir 1.1 Implicit conversion from a pointer to object type to a pointer to void
 *            2018-08-22  visms   ESCAN00100470 MISRA deviation: MISRA-C:2012 Rule 11.5 Cast from a pointer to void to a pointer to object type
 *            2018-08-22  visms   ESCAN00100473 MISRA deviation: VectorMetrics Maximum nesting of control structures too high (HIS: STMIF = 0..4)
 *            2018-08-22  visms   ESCAN00100474 MISRA deviation: MISRA-C:2012 Rule 2.2 This assignment is redundant. The value of this object is never used before being modified.
 *            2018-08-22  visms   ESCAN00100476 MISRA deviation: MISRA-C:2012 Rule 2.2 This operation is redundant. The value of the result is always that of the left-hand operand.
 *            2018-08-22  visms   ESCAN00100477 MISRA deviation: MISRA-C:2012 Rule 14.3 This 'if' controlling expression is a constant expression and its value is 'true'.
 *  15.01.02  2018-09-13  visgut  ESCAN00100734 Incorrect errorId in Com_CopyTxData in case the input parameter PduId is out of bounds
 *            2018-09-14  visgut  ESCAN00097901 Rx Deferred Event Cache leads to unexpected ECU behaviour under high load
 *  16.01.00  2018-10-02  visgut  ESCAN00100910 No reception of Rx ComIPdus after re-activation of ComIPduGroup without initialization using deferred event cache
 *            2018-12-11  visgut  STORYC-1789   Rework of TP State Machine
 *  16.02.00  2019-01-08  visgut  STORYC-1791   Finalize Com TP and Meta Data APIs
 *            2019-01-15  visbbk  ESCAN00101788 SignalGroup invalidation does not work for RX UINT8_DYN signals
 *            2019-01-15  visbbk  ESCAN00101789 Signal or SignalGroup invalidation does not work for UINT8_DYN TX signals
 *  16.02.01  2019-01-21  visgut  ESCAN00101827 Compiler error: Undeclared identifier in post-build usecase
 *  16.03.00  2019-03-12  visgut  STORYC-7874   Deny Retry in COM
 *  17.00.00  2019-03-20  visgut  STORYC-7975   Add doxygen parameter direction
 *  17.01.00  2019-06-11  visgut  ESCAN00102934 Out of bounds read access leads to a MPU violation
 *            2019-07-08  visssg  STORYC-8645   Support Rx Meta Data
 *            2019-07-15  visgut  ESCAN00103719 Out of bounds read access on reception of truncated Rx Deferred Pdu.
 *  18.00.00  2019-08-27  visbbk  COM-507       RunTimeOptimizations for TxMainFunction
 *            2019-10-01  visbbk  ESCAN00104274 Compiler error: uint64 undefined
 *  19.00.00  2020-04-27  visssg  COM-1509      Support Helix QAC 2019-2
 *            2020-06-02  visssg  ESCAN00106471 error C2065: 'Com_PduGrpVectorEndIdxOfRxPduInfoType' : undeclared identifier
 *            2020-06-02  visssg  ESCAN00106476 Identifier "Com_PduGrpVectorEndIdxOfTxPduInfoType" is undefined
 *  20.00.00  2020-11-04  viscpe  COM-1639      Support repetition cycle without MDT
 *            2020-11-11  visssg  COM-2074      Remove Supression of Mandatory Rules
 *            2020-11-12  visssg  COM-1997      Remove the AUTHOR IDENTITY
 *  20.01.00  2020-11-26  vismij  COM-1606      Suppress periodic trigger during transmission of mixed mode PDUs with repetitions Step 1
 *            2020-12-04  visbbk  ESCAN00107889 Timeout occurs after switching the TxMode which shall not be the case
 *  21.00.00  2020-12-21  vismij visssg
                                  COM-1848      Introduce Com Units
 *  21.01.00  2021-01-15  visbbk  ESCAN00108014 Com_SendDynSignal during ComIPduCallout does not update the PduInfo.SduLength passed to PduR_ComTransmit
 *  21.01.00  2021-05-18  visbbk  COM-2282      Remove Com_ReceiveSignal macro API
 *  21.02.00  2021-01-25  visbbk viscpe
                                  COM-23        Signal Gateway according ASR 4.3
 *********************************************************************************************************************/
#if !defined (COM_H)
# define COM_H

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
# include "Com_Lcfg.h"
# if (COM_DEV_ERROR_REPORT == STD_ON)
#  include "Det.h"
# endif

# include "PduR_Com.h"

/**********************************************************************************************************************
  GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
# define COM_VENDOR_ID                         30u              /**< the vendor ID of this implementation. */
# define COM_MODULE_ID                         50u              /**< the module ID of this implementation. */

/*!
  \defgroup  ComARReleaseVersion Com AUTOSAR release version number
  \brief  Version number of AUTOSAR release on which the appropriate implementation is based on.
  \details  -
  \pre      -
    \{
*/
# define COM_AR_RELEASE_MAJOR_VERSION          4u    /**< Major version */
# define COM_AR_RELEASE_MINOR_VERSION          0u    /**< Minor version */
# define COM_AR_RELEASE_REVISION_VERSION       3u    /**< Revision version */
/*!
  \}
*/

/*!
  \defgroup  ComSWVersion Com version number
  \brief  Version number of this implementation.
  \details  -
  \pre      -
    \{
*/
# define COM_SW_MAJOR_VERSION                 21u    /**< Major version */
# define COM_SW_MINOR_VERSION                  2u    /**< Minor version */
# define COM_SW_PATCH_VERSION                  0u    /**< Patch level version */
/*!
  \}
*/

/*!
  \defgroup  ComDetErrorCodes Com Det Error Codes
  \brief  COM development error IDs.
  \trace  SPEC-2781487, SPEC-2736943, SPEC-2736944, SPEC-2736945
  \details  -
  \pre      -
    \{
*/
# define COM_E_NO_ERROR                    0u /**< this code is used to detect that no error occurred. Det_ReportError() is not called.  */
# define COM_E_PARAM                       1u /**< the API service has been with a wrong parameter. */
# define COM_E_UNINIT                      2u /**< the API service has been called before COM was initialized with Com_Init() or after a call to Com_DeInit() */
# define COM_E_PARAM_POINTER               3u /**< the API service has been called with a not expected NULL pointer */
# define COM_E_INIT_FAILED                 4u /**< the API service has been when COM was already initialized. */
/*!
  \}
*/

/*!
  \defgroup  ComReturnCodes Com Return Codes
  \brief  The COM module does not define a own COM return type. The API services return errors either by using the Std_ReturnType as defined Std_Types.h or with these values.
  \details  -
  \pre      -
    \{
*/
# define COM_SERVICE_NOT_AVAILABLE         128u /**< the service is currently not available e.g. the corresponding I-PDU group is stopped or a development error has been detected */
# define COM_BUSY                          129u /**< Successful execution of this function is currently not possible, because a resource is currently in use. For example, the buffer of a large I-PDU is locked. */
/*!
  \}
*/

/**********************************************************************************************************************
  CONSISTENCY CHECK
**********************************************************************************************************************/
# if defined (_TEXAS_INSTRUMENTS_C_TMS320_)
#  error "The Target Tms320 is not supported !"
# endif

# if ((CPU_BYTE_ORDER != LOW_BYTE_FIRST) && (CPU_BYTE_ORDER != HIGH_BYTE_FIRST))
#  error "The hardware byte order is either not defined or has a not supported value"
# endif

/**********************************************************************************************************************
  GLOBAL CONSTANT MACROS
**********************************************************************************************************************/

/*!
  \defgroup  Com_GetConstValueXIntXXOffsets Com XInt Value Offsets
  \brief  These defines are used to calculate the filter specific offset to Com_GetConstValueXIntXX.
  \details  -
    \pre      -
    \{
*/
# define COM_SIGNAL_F_PARAM_MASK           0u /**< the offset to get the mask value */
# define COM_SIGNAL_F_PARAM_X              1u /**< the offset to get the x value */
# define COM_SIGNAL_F_PARAM_MIN            0u /**< the offset to get the min value */
# define COM_SIGNAL_F_PARAM_MAX            1u /**< the offset to get the max value */
/*!
  \}
*/


/**********************************************************************************************************************
  GLOBAL FUNCTION MACROS
**********************************************************************************************************************/
# define COM_CAST2UINT8(argument)         ((uint8) (argument))

/**********************************************************************************************************************
Com_LMgt_CallDetErrorContinue
**********************************************************************************************************************/
/*! \brief          This function is called by Com whenever a development error occurs.
  \details        -
  \pre            -
  \param[in]      API_ID              the service ID of the AUTOSAR COM modules API in which the error was detected.
  \param[in]      ERROR_CODE          the error ID
                                      COM_E_PARAM
                                      COM_E_UNINIT
                                      COM_E_PARAM_POINTER
                                      COM_E_INIT_FAILED
  \context        TASK|ISR2
  \synchronous    TRUE
  \reentrant      TRUE
  \trace          SPEC-2736947
**********************************************************************************************************************/
# define Com_LMgt_CallDetErrorContinue(               API_ID, ERROR_CODE )           (void) Det_ReportError( (COM_MODULE_ID), 0u, ((uint8)(API_ID)), ((uint8)(ERROR_CODE)))

/**********************************************************************************************************************
  Com_TxModeHdlr_IsDirectTxMode
**********************************************************************************************************************/
/*! \brief        This function checks if the current tx mode of the passed Tx ComIPdu is DIRECT.
    \details      -
    \pre          -
    \param[in]    TxPduId               Id of Tx ComIPdu.
    \context      TASK|ISR2
    \return       boolean
                    TRUE if current tx mode is DIRECT
                    FALSE otherwise
    \synchronous  TRUE
    \reentrant    TRUE, for different Handles
**********************************************************************************************************************/
# if ((COM_DIRECTOFTXMODETRUE == STD_ON) && (COM_DIRECTOFTXMODEFALSE == STD_ON))
#  define Com_TxModeHdlr_IsDirectTxMode(TxPduId)           ((Com_IsCurrentTxMode(TxPduId)) ? (Com_IsDirectOfTxModeTrue(Com_GetTxModeTrueIdxOfTxModeInfo(TxPduId))) : (Com_IsDirectOfTxModeFalse(Com_GetTxModeFalseIdxOfTxModeInfo(TxPduId))))
# endif
# if ((COM_DIRECTOFTXMODETRUE == STD_ON) && (COM_DIRECTOFTXMODEFALSE == STD_OFF))
#  define Com_TxModeHdlr_IsDirectTxMode(TxPduId)           ((Com_IsCurrentTxMode(TxPduId)) ? (Com_IsDirectOfTxModeTrue(Com_GetTxModeTrueIdxOfTxModeInfo(TxPduId))) : FALSE)
# endif
# if ((COM_DIRECTOFTXMODETRUE == STD_OFF) && (COM_DIRECTOFTXMODEFALSE == STD_ON))
#  define Com_TxModeHdlr_IsDirectTxMode(TxPduId)           ((Com_IsCurrentTxMode(TxPduId)) ? FALSE : (Com_IsDirectOfTxModeFalse(Com_GetTxModeFalseIdxOfTxModeInfo(TxPduId))))
# endif

/**********************************************************************************************************************
  Com_Signal_BitOffsetFromBitPos
**********************************************************************************************************************/
/*! \brief        This function converts an absolute signal position to the corresponding bit offset in byte.
    \details      -
    \pre          -
    \param[in]    pos  absolute bit position
    \return       uint8
                    bit index in the byte, where the signal starts (0..7)
    \context     TASK
    \synchronous TRUE
    \reentrant   TRUE
**********************************************************************************************************************/
# define Com_Signal_BitOffsetFromBitPos(pos)  (COM_CAST2UINT8((pos) & 7u))

/**********************************************************************************************************************
  GLOBAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/

/*!
  \defgroup  Com_StatusType Com Status Type
  \brief  This is a status value returned by the API service Com_GetStatus().
  \details     -
  \pre         -
  \context     -
  \synchronous -
  \reentrant   -
    \{
*/
typedef enum
{
  COM_UNINIT = 0x00,  /**< The COM module is not initialized or not usable. */
  COM_INIT = 0x01     /**< The COM Module is initialized and usable. */
} Com_StatusType;
/*!
  \}
*/

# if (COM_DEV_ERROR_REPORT == STD_ON)
/*!
  \defgroup  Com_ServiceIdType Com Service Id Type
  \brief  Unique identifier of a COM module service.
  \trace  SPEC-2736956
  \details     -
  \pre         -
    \{
*/
typedef enum
{
  COMServiceId_Init = 0x01,
  COMServiceId_DeInit = 0x02,
  COMServiceId_IpduGroupControl = 0x03,
  COMServiceId_ReceptionDMControl = 0x06,
  COMServiceId_GetStatus = 0x07,
  COMServiceId_GetConfigurationId = 0x08,    /**< This service Id is not used in Autosar 4.2.1 */
  COMServiceId_GetVersionInfo = 0x09,
  COMServiceId_SendSignal = 0x0A,
  COMServiceId_ReceiveSignal = 0x0B,
  COMServiceId_SendSignalGroup = 0x0D,
  COMServiceId_ReceiveSignalGroup = 0x0E,
  COMServiceId_InvalidateSignal = 0x10,
  COMServiceId_TriggerIPDUSend = 0x17,
  COMServiceId_MainFunctionRx = 0x18,
  COMServiceId_MainFunctionTx = 0x19,
  COMServiceId_MainFunctionRouteSignals = 0x1A,
  COMServiceId_InvalidateSignalGroup = 0x1B,
  COMServiceId_ClearIpduGroupVector = 0x1C,
  COMServiceId_SetIpduGroup = 0x1D,
  COMServiceId_SendDynSignal = 0x21,
  COMServiceId_ReceiveDynSignal = 0x22,
  COMServiceId_SendSignalGroupArray = 0x23,
  COMServiceId_ReceiveSignalGroupArray = 0x24,
  COMServiceId_SwitchIpduTxMode = 0x27,
  COMServiceId_TriggerIPDUSendWithMetaData = 0x28,
  COMServiceId_TxConfirmation = 0x40,
  COMServiceId_TriggerTransmit = 0x41,
  COMServiceId_RxIndication = 0x42,
  COMServiceId_CopyTxData = 0x43,
  COMServiceId_CopyRxData = 0x44,
  COMServiceId_TpRxIndication = 0x45,
  COMServiceId_StartOfReception = 0x46,
  COMServiceId_TpTxConfirmation = 0x48
} Com_ServiceIdType;
/*!
  \}
*/
# endif

/*! Struct used for caching function ptr callbacks. */
typedef struct
{
  P2VAR(uint32, AUTOMATIC, COM_APPL_VAR) ptrToCache;
  uint32 cacheIndex;
  uint32 cacheSize;
} FctPtrCacheStrct;             /* PRQA S 3205 */ /* MD_Com_3205 */

/**********************************************************************************************************************
  GLOBAL DATA PROTOTYPES (Com)
**********************************************************************************************************************/
# if(COM_USE_INIT_POINTER == STD_ON)
#  define COM_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_MemMap */

extern P2CONST(Com_ConfigType, COM_VAR_ZERO_INIT, COM_PBCFG) Com_ConfigDataPtr;

#  define COM_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_MemMap */
# endif

/**********************************************************************************************************************
  GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/
# define COM_START_SEC_CODE
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_19.1 */

/**********************************************************************************************************************
Com_Init
**********************************************************************************************************************/
/*! \brief          This service initializes internal and external interfaces and variables of the AUTOSAR COM layer
                  for the further processing. After calling this function the inter-ECU communication is still disabled.
  \details        -
  \param[in]      config  NULL_PTR if COM_USE_INIT_POINTER is STD_OFF
                  Pointer to the Com configuration data if COM_USE_INIT_POINTER is STD_ON
  \context        TASK
  \warning        Com_Init shall not pre-empt any COM function.
                  The rest of the system must guarantee that Com_Init is not called in such a way.
  \synchronous    TRUE
  \reentrant      FALSE
  \trace          SPEC-2736960
  \pre            Com_InitMemory() has to be executed previously, if the startup code does not initialize variables.
  \pre            Com is not in initialized state.
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_Init(P2CONST(Com_ConfigType, AUTOMATIC, COM_INIT_DATA) config);

/**********************************************************************************************************************
Com_InitMemory
**********************************************************************************************************************/
/*! \brief    The function initializes variables, which cannot be initialized with the startup code.
  \details  -
  \context  TASK
  \synchronous TRUE
  \reentrant   FALSE
  \trace    SPEC-2736784, SPEC-2736788
  \pre      Com_Init() is not called yet.
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_InitMemory(void);

/**********************************************************************************************************************
Com_DeInit
**********************************************************************************************************************/
/*! \brief    This service stops the inter-ECU communication. All started I-PDU groups are stopped and have
            to be started again, if needed, after Com_Init is called. By a call to ComDeInit COM is put into an
            not initialized state.
  \details  -
  \pre      -
  \context  TASK
  \warning  Com_DeInit shall not pre-empt any COM function.
            The rest of the system must guarantee that Com_DeInit is not called in such a way.
  \synchronous TRUE
  \reentrant   FALSE
  \trace    SPEC-2736961, SPEC-2736962
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_DeInit(void);

/**********************************************************************************************************************
  Com_IpduGroupControl
**********************************************************************************************************************/
/*! \brief          This service starts I-PDU groups.
    \details        -
    \pre            -
    \param[in]      ipduGroupVector     I-PDU group vector containing the activation state (stopped = 0/ started = 1)
                                        for all I-PDU groups.
    \param[in]      initialize          flag to request initialization of the I-PDUs which are newly started
    \context        TASK
    \synchronous    TRUE
    \reentrant      FALSE
    \trace          SPEC-2736963, SPEC-2736964
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_IpduGroupControl(Com_IpduGroupVector ipduGroupVector, boolean initialize);

/**********************************************************************************************************************
Com_ReceptionDMControl
**********************************************************************************************************************/
/*! \brief          This service enables or disables I-PDU group Deadline Monitoring.
  \details        -
  \pre            -
  \param[in]      ipduGroupVector I-PDU group vector containing the requested deadline monitoring state
                                  (disabled = 0/ enabled = 1) for all I-PDU groups.
  \context        TASK
  \synchronous    TRUE
  \reentrant      FALSE
  \trace          SPEC-2736874, SPEC-2736965, SPEC-2736966, SPEC-2736967, SPEC-2736968
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_ReceptionDMControl(Com_IpduGroupVector ipduGroupVector);

/**********************************************************************************************************************
  Com_IpduGroupStart
**********************************************************************************************************************/
/*! \brief          Starts a preconfigured I-PDU group.
                    For example, cyclic I-PDUs will be sent out cyclically after the call of Com_IpduGroupStart().
                    If Initialize is true all I-PDUs of the I-PDU group shall be (re-)initialized before the I-PDU group
                    is started. That means they shall behave like after a start-up of COM, for example the old_value of the
                    filter objects and shadow buffers of signal groups have to be (re-)initialized.
    \details        -
    \pre            -
    \param[in]      IpduGroupId ID of I-PDU group to be started
    \param[in]      Initialize  Flag to request initialization of the data in the I-PDUs of this I-PDU group
    \context        TASK
    \warning        A call to Com_IpduGroupStart shall not be interrupted by another call to Com_IpduGroupStart, Com_EnableReceptionDM,
                    Com_DisableReceptionDM or a call to Com_IpduGroupStop.
    \synchronous    TRUE
    \reentrant      FALSE
    \trace          SPEC-5131280
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_IpduGroupStart(Com_IpduGroupIdType IpduGroupId, boolean Initialize);

/**********************************************************************************************************************
  Com_IpduGroupStop
**********************************************************************************************************************/
/*! \brief          Stops a preconfigured I-PDU group.
                    For example, cyclic I-PDUs will be stopped after the call of Com_IpduGroupStop().
    \details        -
    \pre            -
    \param[in]      IpduGroupId ID of I-PDU group to be stopped
    \context        TASK
    \warning        A call to Com_IpduGroupStop shall not be interrupted by another call to Com_IpduGroupStop, Com_EnableReceptionDM,
                    Com_DisableReceptionDM or a call to Com_IpduGroupStart.
    \synchronous    TRUE
    \reentrant      FALSE
    \trace          SPEC-5131281
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_IpduGroupStop(Com_IpduGroupIdType IpduGroupId);

/**********************************************************************************************************************
Com_EnableReceptionDM
**********************************************************************************************************************/
/*! \brief          Enables the reception deadline monitoring for the I-PDUs within the given I-PDU group.
  \details        -
  \pre            -
  \param[in]      IpduGroupId ID of I-PDU group where reception DM shall be enabled.
  \context        TASK
  \warning        A call to Com_EnableReceptionDM shall not be interrupted by another call to Com_EnableReceptionDM, Com_IpduGroupStop,
                  Com_DisableReceptionDM or a call to Com_IpduGroupStart.
  \synchronous    TRUE
  \reentrant      FALSE
  \trace          SPEC-5131282
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_EnableReceptionDM(Com_IpduGroupIdType IpduGroupId);

/**********************************************************************************************************************
Com_DisableReceptionDM
**********************************************************************************************************************/
/*! \brief          Disables the reception deadline monitoring for the I-PDUs within the given I-PDU group.
  \details        -
  \pre            -
  \param[in]      IpduGroupId ID of I-PDU group where reception DM shall be disabled.
  \context        TASK
  \warning        A call to Com_DisableReceptionDM shall not be interrupted by another call to Com_DisableReceptionDM, Com_IpduGroupStop,
                  Com_EnableReceptionDM or a call to Com_IpduGroupStart.
  \synchronous    TRUE
  \reentrant      FALSE
  \trace          SPEC-5131283
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_DisableReceptionDM(Com_IpduGroupIdType IpduGroupId);

/**********************************************************************************************************************
Com_MainFunctionRx
**********************************************************************************************************************/
/*! \brief    This function shall perform the processing of the AUTOSAR COM receive processing that are not directly
            initiated by the calls from the RTE and PDU-R.
            A call to Com_MainFunctionRx returns simply if COM was not previously initialized with
            a call to Com_Init.
  \details  -
  \pre      -
  \context  TASK
  \synchronous TRUE
  \reentrant   FALSE
  \trace    CREQ-103161
**********************************************************************************************************************/
/* function defined in file 'SchM_Com.h' */

/**********************************************************************************************************************
Com_MainFunctionTx
**********************************************************************************************************************/
/*! \brief    This function shall perform the processing of the transmission activities that are not
            directly initiated by the calls from the RTE and PDU-R.
            A call to Com_MainFunctionTx returns simply if COM was not previously initialized with
            a call to Com_Init.
  \details  -
  \pre      -
  \context  TASK
  \synchronous TRUE
  \reentrant   FALSE
  \trace    CREQ-103168
**********************************************************************************************************************/
/* function defined in file 'SchM_Com.h' */

/**********************************************************************************************************************
Com_GetConfigurationId
**********************************************************************************************************************/
/*! \brief    Provides the unique identifier of the configuration.
  \details  -
  \pre      -
  \return   uint32 Configured ConfigurationID
  \context  TASK|ISR2
  \synchronous TRUE
  \reentrant   FALSE
  \trace    CREQ-107420
**********************************************************************************************************************/
FUNC(uint32, COM_CODE) Com_GetConfigurationId(void);

/**********************************************************************************************************************
Com_GetStatus
**********************************************************************************************************************/
/*! \brief    Returns the status of the AUTOSAR COM module.
  \details  -
  \pre      -
  \return   Com_StatusType
  \context  TASK|ISR2
  \trace    CREQ-107163
  \trace    SPEC-2736969
  \synchronous TRUE
  \reentrant   TRUE
**********************************************************************************************************************/
FUNC(Com_StatusType, COM_CODE) Com_GetStatus(void);

# if (COM_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
  Com_GetVersionInfo
**********************************************************************************************************************/
/*! \brief          Returns the version information of this module.
    \details        -
    \pre            -
    \param[out]     versioninfo Pointer to where to store the version information of this module.
    \context        TASK|ISR2
    \synchronous    TRUE
    \reentrant      TRUE
    \trace          SPEC-2736970
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, COM_APPL_VAR) versioninfo);
# endif

/**********************************************************************************************************************
  Com_TriggerIPDUSend
**********************************************************************************************************************/
/*! \brief          By a call to Com_TriggerIPDUSend the I-PDU with the given ID is triggered for transmission
    \details        -
    \pre            -
    \param[in]      PduId    ID of Tx I-PDU.
    \context        TASK|ISR2
    \synchronous    TRUE
    \reentrant      FALSE
    \trace          SPEC-2737013, SPEC-2737014, SPEC-2737015
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TriggerIPDUSend(PduIdType PduId);

# if (COM_TRIGGER_IPDU_SEND_WITH_META_DATA_API == STD_ON)
/**********************************************************************************************************************
  Com_TriggerIPDUSendWithMetaData
**********************************************************************************************************************/
/*! \brief          By a call to Com_TriggerIPDUSendWithMetaData the given meta data is appended to the I-PDU and the I-PDU
                    with the given ID is triggered for transmission
    \details        -
    \pre            -
    \param[in]      PduId    ID of Tx I-PDU.
    \param[in]      MetaData The Meta data that shall be added to the I-PDU before sending.
    \context        TASK|ISR2
    \synchronous    TRUE
    \reentrant      FALSE
    \trace          SPEC-2737018, SPEC-2737019
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TriggerIPDUSendWithMetaData(PduIdType PduId, P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) MetaData);
# endif

# if (COM_PDUGRPVECTOR == STD_ON)
/**********************************************************************************************************************
  Com_ClearIpduGroupVector
**********************************************************************************************************************/
/*! \brief          This service sets all bits of the given Com_IpduGroupVector to 0.
    \details        -
    \pre            -
    \param[out]     ipduGroupVector I-PDU group vector to be cleared
    \context        TASK
    \synchronous    TRUE
    \reentrant      FALSE
    \trace          SPEC-2736971
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_ClearIpduGroupVector(Com_IpduGroupVector ipduGroupVector);
# endif

# if (COM_PDUGRPVECTOR == STD_ON)
/**********************************************************************************************************************
  Com_SetIpduGroup
**********************************************************************************************************************/
/*! \brief              This service sets the value of a bit in an I-PDU group vector.
    \details            -
    \pre                -
    \param[in,out]      ipduGroupVector I-PDU group vector to be modified
    \param[in]          ipduGroupId     ID used to identify the corresponding bit in the I-PDU group vector
    \param[in]          bitval          New value of the corresponding bit
    \context            TASK
    \synchronous        TRUE
    \reentrant          FALSE
    \trace              SPEC-2736972, SPEC-2736973
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_SetIpduGroup(Com_IpduGroupVector ipduGroupVector, Com_IpduGroupIdType ipduGroupId, boolean bitval);
# endif

# if (COM_TRANSPORT_PROTOCOL == STD_ON)
/**********************************************************************************************************************
  Com_ReceiveDynSignal
**********************************************************************************************************************/
/*! \brief              The service Com_ReceiveDynSignal updates the signal data referenced by SignalDataPtr
                        with the data in the signal object identified by SignalId. The Length parameter indicates as
                        "in parameter" the maximum length that can be received and as "out parameter" the length of the written
                        dynamic length signal or group signal. If the signal processing of the corresponding I-Pdu is
                        configured to DEFERRED the last received signal value is available not until the next call to Com_MainfunctionRx.
                        If a group signal is read, the data in the shadow buffer should be updated before the call
                        by a call of the service Com_ReceiveSignalGroup.
    \details            -
    \pre                -
    \param[in]          SignalId                    Id of signal or group signal to be received.
    \param[out]         SignalDataPtr               Reference to the signal data in which to store the received data.
    \param[in,out]      Length                      in: maximum length that could be received
                                                    out: length of the dynamic length signal
    \return             uint8
                          E_OK                      service has been accepted
                          E_NOT_OK                  in case the Length (as in-parameter) is smaller than
                                                    the received length of the dynamic length signal
                          COM_SERVICE_NOT_AVAILABLE corresponding I-PDU group was stopped
                                                    (or service failed due to development error)
    \context            TASK|ISR2
    \synchronous        TRUE
    \reentrant          TRUE, for different handles
    \trace              SPEC-2736983, SPEC-2736984, SPEC-2736985, SPEC-2736986
**********************************************************************************************************************/
FUNC(uint8, COM_CODE) Com_ReceiveDynSignal(Com_SignalIdType SignalId, P2VAR(void, AUTOMATIC, COM_APPL_VAR) SignalDataPtr, P2VAR(uint16, AUTOMATIC, COM_APPL_VAR) Length);
# endif

/**********************************************************************************************************************
Com_ReceiveSignal
**********************************************************************************************************************/
/*! \brief          The service Com_ReceiveSignal updates the signal data referenced by SignalDataPtr
                  with the data in the signal object identified by SignalId.
                  If the signal processing of the corresponding I-Pdu is configured to DEFERRED
                  the last received signal value is available not until the next call to Com_MainfunctionRx.
                  If a group signal is read, the data in the shadow buffer should be updated before the call
                  by a call of the service Com_ReceiveSignalGroup.
  \details        -
  \pre            -
  \param[in]      SignalId                    Id of signal or group signal to be received.
  \param[out]     SignalDataPtr               Reference to the signal data in which to store the received data.
  \return         uint8
                    E_OK                      service has been accepted
                    COM_SERVICE_NOT_AVAILABLE corresponding I-PDU group was stopped
                                              (or service failed due to development error)
  \context        TASK|ISR2
  \synchronous    TRUE
  \reentrant      TRUE, for different handles
  \trace          SPEC-2736981, SPEC-2736982
**********************************************************************************************************************/
FUNC(uint8, COM_CODE) Com_ReceiveSignal(Com_SignalIdType SignalId, P2VAR(void, AUTOMATIC, COM_APPL_VAR) SignalDataPtr);

/**********************************************************************************************************************
Com_ReceiveShadowSignal
**********************************************************************************************************************/
/*! \brief          The service Com_ReceiveShadowSignal updates the group signal data referenced
                  by SignalDataPtr with the data in the shadow buffer.
                  The data in the shadow buffer should be updated before the call of Com_ReceiveShadowSignal
                  by a call of the service Com_ReceiveSignalGroup.
  \details        -
  \pre            -
  \param[in]      SignalId                    Id of group signal to be received.
  \param[out]     SignalDataPtr               Reference to the group signal data in which to store the received data.
  \context        TASK|ISR2
  \synchronous    TRUE
  \reentrant      TRUE, for different handles
  \trace          SPEC-2736997, SPEC-2736998
  \deprecated     This function is deprecated. Use 'Com_ReceiveSignal' instead to read group signals.
**********************************************************************************************************************/
# define Com_ReceiveShadowSignal(SignalId, SignalDataPtr) (void) Com_ReceiveSignal((SignalId), (SignalDataPtr))

/**********************************************************************************************************************
Com_ReceiveSignalGroup
**********************************************************************************************************************/
/*! \brief          The service Com_ReceiveSignalGroup copies the received signal group to the shadow buffer.
                  After this call, the group signals could be copied from the shadow buffer to the upper layer by
                  a call of Com_ReceiveShadowSignal.
  \details        -
  \pre            -
  \param[in]      SignalGroupId               Id of signal group to be received.
  \return         uint8
                    E_OK                      service has been accepted
                    COM_SERVICE_NOT_AVAILABLE corresponding I-PDU group was stopped
                                              (or service failed due to development error)
  \context        TASK|ISR2
                  To guarantee data consistency of the whole signal group the complete reception of a signal group
                  (consecutive calls of 'Com_ReceiveSignalGroup' and 'Com_ReceiveSignal')
                  must not be interrupted by another reception request for the same signal group.
  \synchronous    TRUE
  \reentrant      TRUE, for different handles
  \trace          SPEC-2736993, SPEC-2736994, SPEC-2736995, SPEC-2736996
**********************************************************************************************************************/
FUNC(uint8, COM_CODE) Com_ReceiveSignalGroup(Com_SignalGroupIdType SignalGroupId);

# if (COM_ENABLE_SIGNAL_GROUP_ARRAY_API == STD_ON)
/**********************************************************************************************************************
  Com_ReceiveSignalGroupArray
**********************************************************************************************************************/
/*! \brief          The service Com_ReceiveSignalGroupArray copies the received signal group
                    array representation from the PDU to the location designated by SignalGroupArrayPtr.
    \details        -
    \param[in]      SignalGroupId               Id of signal group to be received.
    \param[out]     SignalGroupArrayPtr         reference to the location where the received signal group
                                                array shall be stored
    \return         uint8
                      E_OK                      service has been accepted
                      COM_SERVICE_NOT_AVAILABLE corresponding I-PDU group was stopped (or service failed due to development
                                                error)
                      COM_BUSY                  in case the TP-Buffer is locked for large data types handling
    \context        TASK|ISR2
    \synchronous    TRUE
    \reentrant      TRUE, for different handles
    \trace          SPEC-2737002, SPEC-2737003, SPEC-2737005
    \pre            The configuration switch ComEnableSignalGroupArrayApi has to be enabled.
**********************************************************************************************************************/
FUNC(uint8, COM_CODE) Com_ReceiveSignalGroupArray(Com_SignalGroupIdType SignalGroupId, P2VAR(uint8, AUTOMATIC, COM_APPL_VAR) SignalGroupArrayPtr);
# endif

# if (COM_MAIN_FUNCTION_ROUTE_SIGNALS_API == STD_ON)
/**********************************************************************************************************************
  Com_MainFunctionRouteSignals
**********************************************************************************************************************/
/*! \brief    Calls the signal gateway part of COM to forward received signals to be routed.
              The insertion of this call is necessary for decoupling receive interrupts and signal gateway tasks.
              A call to Com_MainFunctionRouteSignals returns simply if COM was not previously initialized with a
              call to Com_Init.
    \details  -
    \pre      -
    \context  TASK
    \synchronous TRUE
    \reentrant   FALSE
    \warning  The time between to consecutive calls (perhaps the related task/thread cycle)
              affects directly the signal gateway latency.
    \trace    CREQ-103192
    \trace    SPEC-2736940, SPEC-2736941
**********************************************************************************************************************/
/* the function prototype is implemented in file 'SchM_Com.h' */
# endif

/**********************************************************************************************************************
Com_InvalidateSignal
**********************************************************************************************************************/
/*! \brief        This function invalidates the signal or group signal by calling Com_SendSignal
                with the configured invalid value.
                If this function is used to invalidate a group signal, a call to Com_SendSignalGroup is needed
                to update the signal group data.

  \details      -
  \pre          -
  \param[in]    SignalId      ID of signal or group signal to be invalidated.
  \return       uint8
                  E_OK                        service has been accepted
                  COM_SERVICE_NOT_AVAILABLE   corresponding I-PDU group was stopped
                                              (or service failed due to development error)
  \context      TASK|ISR2
  \synchronous  FALSE
  \reentrant    TRUE, for different handles
  \trace        SPEC-2737006, SPEC-2737007, SPEC-2737008, SPEC-2737010
**********************************************************************************************************************/
FUNC(uint8, COM_CODE) Com_InvalidateSignal(Com_SignalIdType SignalId);

/**********************************************************************************************************************
Com_InvalidateSignalGroup
**********************************************************************************************************************/
/*! \brief        This function invalidates the whole signal group by calling Com_SendSignal
                with the configured invalid value for all group signals of the signal group.
                After invalidation of the current signal group data Com_SendSignalGroup is performed internally.

  \details      -
  \pre          -
  \param[in]    SignalGroupId      ID of signal group to be invalidated.
  \return       uint8
                 E_OK                        service has been accepted
                 COM_SERVICE_NOT_AVAILABLE   corresponding I-PDU group was stopped
                                             (or service failed due to development error)
  \context      TASK|ISR2
  \synchronous  FALSE
  \reentrant    TRUE, for different handles
  \trace        SPEC-2737011, SPEC-2737012
**********************************************************************************************************************/
FUNC(uint8, COM_CODE) Com_InvalidateSignalGroup(Com_SignalGroupIdType SignalGroupId);

/**********************************************************************************************************************
Com_InvalidateShadowSignal
**********************************************************************************************************************/
/*! \brief        This function invalidates the group signal by calling Com_SendSignal
                with the configured invalid value.
                An additional call to Com_SendSignalGroup is needed to update the signal group data.

  \details      -
  \pre          -
  \param[in]    SignalId      ID of group signal to be invalidated.
  \context      TASK|ISR2
  \deprecated   This function is deprecated. Use 'Com_InvalidateSignal' instead to invalidate a group signals.
  \synchronous  TRUE
  \reentrant    TRUE, for different handles
  \trace        SPEC-2737009
**********************************************************************************************************************/
# define Com_InvalidateShadowSignal(SignalId) (void) Com_InvalidateSignal((SignalId))

/**********************************************************************************************************************
Com_SwitchIpduTxMode
**********************************************************************************************************************/
/*! \brief        This method sets the TX Mode of the I-PDU referenced by PduId to Mode.
                In case the TX Mode changes the new mode is immediately effective.
                In case the requested transmission mode was already active for this I-PDU, the call will have no effect.
  \details      -
  \pre          -
  \param[in]    PduId    ID of Tx I-PDU.
  \param[in]    Mode     TX mode of the I-PDU (TRUE/FALSE)
  \context      TASK|ISR2
  \synchronous  TRUE
  \trace        SPEC-2737021
  \reentrant    TRUE, for different Handles
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_SwitchIpduTxMode(PduIdType PduId, boolean Mode);

# if (COM_TRANSPORT_PROTOCOL == STD_ON)
/**********************************************************************************************************************
  Com_SendDynSignal
**********************************************************************************************************************/
/*! \brief        The service Com_SendDynSignal updates the signal or group signal object identified by SignalId
                  with the signal data referenced by the SignalDataPtr parameter. The Length parameter is evaluated for
                  dynamic length signals.
    \details      -
    \pre          -
    \param[in]    SignalId      ID of signal or group signal to be sent.
    \param[in]    SignalDataPtr Reference to the signal data to be transmitted.
    \param[in]    Length        Length of the dynamic length signal.
    \return       uint8
                    E_OK                        service has been accepted
                    COM_SERVICE_NOT_AVAILABLE   corresponding I-PDU group was stopped
                                          (or service failed due to development error)
                    COM_BUSY                    in case the TP-Buffer is locked for large data types handling
    \context      TASK|ISR2
    \warning      If the method is used on a microcontroller like the Tms320 DSP and the datatype uint8 is unsigned short
                  the 8 MSB bits of the variable shall never be set.
                  If the method is used on a microcontroller like the S12X and the datatype is uint16, sint16, uint32
                  or sint32 the SignalDataPtr must be word aligned.
                  Do not call this function in Tx ComIPduCallout.
    \synchronous  FALSE
    \trace        SPEC-2736977, SPEC-2736978
    \reentrant    TRUE, for different handles
**********************************************************************************************************************/
FUNC(uint8, COM_CODE) Com_SendDynSignal(Com_SignalIdType SignalId, P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr, uint16 Length);
# endif

/**********************************************************************************************************************
Com_SendSignal
**********************************************************************************************************************/
/*! \brief        The service Com_SendSignal updates the signal or group signal object identified by SignalId
                with the signal data referenced by the SignalDataPtr parameter.
  \details      -
  \pre          -
  \param[in]    SignalId      ID of signal or group signal to be sent.
  \param[in]    SignalDataPtr Reference to the signal data to be transmitted.
  \return       uint8
                E_OK                        service has been accepted
                COM_SERVICE_NOT_AVAILABLE   corresponding I-PDU group was stopped
                                            (or service failed due to development error)
                COM_BUSY                    in case the TP-Buffer is locked for large data types handling
  \context      TASK|ISR2
  \warning      If the method is used on a microcontroller like the Tms320 DSP and the datatype uint8 is unsigned short
                the 8 MSB bits of the variable shall never be set.
                If the method is used on a microcontroller like the S12X and the datatype is uint16, sint16, uint32
                or sint32 the SignalDataPtr must be word aligned.
  \synchronous  FALSE
  \reentrant    TRUE, for different handles
  \trace        CREQ-103177
  \trace        SPEC-2736974, SPEC-2736975
**********************************************************************************************************************/
FUNC(uint8, COM_CODE) Com_SendSignal(Com_SignalIdType SignalId, P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr);

/**********************************************************************************************************************
Com_SendSignalGroup
**********************************************************************************************************************/
/*! \brief        The service Com_SendSignalGroup copies the content of the associated shadow buffer to
                the associated I-PDU buffer.
                Prior to this call, all group signals should be updated in the shadow buffer
                by the call of Com_SendSignal.
  \details      -
  \pre          -
  \param[in]    SignalGroupId      ID of signal group to be send.
  \return       uint8
                  E_OK                        service has been accepted
                  COM_SERVICE_NOT_AVAILABLE   corresponding I-PDU group was stopped (or service failed due to development error)
                  COM_BUSY                    in case the TP-Buffer is locked for large data types handling
  \context      TASK|ISR2
  \synchronous  FALSE
  \reentrant    TRUE, for different handles
  \trace        SPEC-2736990, SPEC-2736991, SPEC-2736992
**********************************************************************************************************************/
FUNC(uint8, COM_CODE) Com_SendSignalGroup(Com_SignalGroupIdType SignalGroupId);

/**********************************************************************************************************************
Com_UpdateShadowSignal
**********************************************************************************************************************/
/*! \brief        The service Com_UpdateShadowSignal updates a group signal with the data, referenced by SignalDataPtr.
                The update of the group signal data is done in the shadow buffer, not in the I-PDU.
                To send out the shadow buffer, Com_SendSignalGroup has to be called.
  \details      -
  \pre          -
  \param[in]    SignalId      ID of group signal to be updated.
  \param[in]    SignalDataPtr Reference to the group signal data to be updated.
  \context      TASK|ISR2
  \warning      If the method is used on a microcontroller like the S12X and the datatype is uint16, sint16, uint32
                or sint32 the SignalDataPtr must be word aligned.
  \deprecated   This function is deprecated. Use 'Com_SendSignal' instead to send group signals.
  \synchronous  TRUE
  \reentrant    FALSE
  \trace        SPEC-2736987, SPEC-2736988
**********************************************************************************************************************/
# define Com_UpdateShadowSignal(SignalId, SignalDataPtr) (void) Com_SendSignal((SignalId), (SignalDataPtr))

# if (COM_ENABLE_SIGNAL_GROUP_ARRAY_API == STD_ON)
/**********************************************************************************************************************
  Com_SendSignalGroupArray
**********************************************************************************************************************/
/*! \brief        The service Com_SendSignalGroupArray copies the content of the provided SignalGroupArrayPtr to the
 *                associated I-PDU. The provided data shall correspond to the array representation of the signal group.
    \details      -
    \param[in]    SignalGroupId               Id of signal group to be sent.
    \param[in]    SignalGroupArrayPtr         Reference to the signal group array.
    \return       uint8
                    E_OK                        service has been accepted
                    COM_SERVICE_NOT_AVAILABLE   corresponding I-PDU group was stopped (or service failed due to development
                                                error)
                    COM_BUSY                    in case the TP-Buffer is locked for large data types handling
    \context      TASK|ISR2
    \synchronous  FALSE
    \reentrant    TRUE, for different handles
    \trace        SPEC-2736999, SPEC-2737000
    \pre          The configuration switch ComEnableSignalGroupArrayApi has to be enabled.
**********************************************************************************************************************/
FUNC(uint8, COM_CODE) Com_SendSignalGroupArray(Com_SignalGroupIdType SignalGroupId, P2CONST(uint8, AUTOMATIC, COM_APPL_VAR) SignalGroupArrayPtr);
# endif

# define COM_STOP_SEC_CODE
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_MemMap */

/*!
* \exclusivearea COM_EXCLUSIVE_AREA_RX
* Ensures consistency of global RAM variables.
* \protects Global RAM variables used of Rx path.
* \usedin Com_DeInit, Com_Init, Com_IPduGroupControl, Com_IPduGroupStart, Com_IPduGroupStop, Com_MainFunctionRx, Com_ReceiveDynSignal, Com_ReceiveSignal, Com_ReceiveSignalGroup, Com_ReceiveSignalGroupArray, Com_RxIndication, Com_TpRxindication
* \exclude All functions provided by Com.
* \length SHORT to LONG depending on the API, the call graph and configured thresholds.
* \endexclusivearea
*/

/*!
* \exclusivearea COM_EXCLUSIVE_AREA_TX
* Ensures consistency of global RAM variables.
* \protects Global RAM variables used of Tx path.
* \usedin Com_Deinit, Com_Init, Com_InvalidateSignal, Com_InvalidateSignalGroup, Com_IpduGroupControl, Com_IpduGroupStart, Com_IpduGroupStop, Com_MainFunctionTx, Com_RxIndication, Com_SendDynSignal, Com_SendSignal, Com_SendSignalGroup, Com_SendSignalGroupArray, Com_TpRxIndication, Com_TpTxConfirmation, Com_TriggerTransmit, Com_TxConfirmation, Com_TpTxConfirmation, Com_TriggerIPDUSendWithMetaData
* \exclude All functions provided by Com.
* \length SHORT to LONG depending on the API, the call graph and configured thresholds.
* \endexclusivearea
*/

/*!
* \exclusivearea COM_EXCLUSIVE_AREA_BOTH
* Ensures consistency of global RAM variables.
* \protects Global RAM variables.
* \usedin Com_MainFunctionRouteSignals
* \exclude All functions provided by Com.
* \length SHORT to LONG depending on the API, the call graph and configured thresholds.
* \endexclusivearea
*/

#endif /* COM_H */

/**********************************************************************************************************************
  END OF FILE: Com.h
**********************************************************************************************************************/
