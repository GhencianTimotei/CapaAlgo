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
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  IpduM.h
 *      Project:  MICROSAR IpduM
 *       Module:  Implementation
 *    Generator:  CFG5
 *
 *  Description:  Microsar IPDU Multiplexer header file
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date          Author    Change Id         Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2011-11-25    visms     -                 initial CFG5 version derived from Il_AsrIpduM Version 1.05.00
 *  01.00.01  2012-04-02    visms     ESCAN00058067     Compiler error: Undefined symbol TxMuxPduCnt in IpduM_Init
 *  02.00.00  2012-05-24    visms     ESCAN00058315     AR4-160: Support AUTOSAR 4.0.3
 *  02.00.00  2012-06-18    visbms    ESCAN00059468     Extend Comments and Improve Comment Coverage
 *  02.00.01  2012-09-17    visbms    ESCAN00061444     Feature not functional
 *  02.00.01  2012-09-24    visbms    ESCAN00061650     Det is called in IpduM_Init()
 *  02.00.01  2012-09-24    visbms    ESCAN00061652     Linker error: could not find symbol
 *  02.00.01  2012-10-05    visbms    ESCAN00061971     Possible access of out-of-bounds pointer
 *  02.01.00  2012-11-06    visms     ESCAN00062696     Tx Confirmation Callback is always called with the Initial Dynamic Part Handle
 *  02.01.00  2012-11-06    visms     ESCAN00062763     IpduM_GetVersionInfo returns incorrect SW-VERSION
 *  02.01.00  2012-11-26    visbms    ESCAN00061785     AR4-197: Support BIG_ENDIAN Copy Segments in IpduM
 *  02.01.00  2013-01-31    visbms    ESCAN00064703     Compiler error: undeclared identifier: IpduM_TxPathwayRefOfTxPartType
 *  02.02.00  2013-02-14    visms     ESCAN00064366     AR4-325: Implement Post-Build Loadable
 *  02.02.00  2013-03-19    visms     ESCAN00064646     AR4-282: Export BSW DBG Data
 *  02.02.00  2013-03-27    visbms    ESCAN00065331     Memory overwritten, unpredictable ECU behavior
 *  02.02.00  2013-04-19    visbms    ESCAN00061116     Compiler warning: variable (...) was set but never used
 *  02.02.00  2013-04-22    visbms    ESCAN00065881     IpduM does not work with DirectComInvocation
 *  02.02.00  2013-05-13    visbms    ESCAN00067297     Access Violation: array read index out of bounds with PDUs with no static part
 *  02.02.00  2013-05-13    visbms    ESCAN00067309     Wrong TxConfirmations forwarded for static parts
 *  02.03.00  2013-08-16    visms     ESCAN00069872     The prefix of VAR data shall be <Msn> followed by '_'
 *  02.03.00  2013-08-23    visms     ESCAN00069148     Include "SchM_IpduM.h" only in source files
 *  02.03.00  2013-10-08    visms     ESCAN00070960     AR4-89: Support Optional Confirmation
 *  02.03.01  2014-02-07    visbms    ESCAN00073555     HIS metrics violation
 *  02.03.02  2014-05-07    visbms    ESCAN00074501     IpduM_Transmit() returning E_OK on failed transmission
 *  03.00.00  2014-05-14    visms     ESCAN00074121     AR4-642: Deleting container at post-build time
 *  04.00.00  2014-06-30    visbms    ESCAN00076406     MISRA deviation: MISRA-C:2004 Rule 4:3746 Implicit conversion: unsigned short to unsigned char.
 *  05.00.00  2014-11-17    visbms    ESCAN00079611     Corrupt data is forwarded to Com
 *  05.00.00  2014-11-17    visbms    ESCAN00079622     Code Rework
 *  05.00.00  2014-11-28    visbms    ESCAN00079874     FEAT-229: Support 16bit selector in IpduM [AR4-927]
 *  05.00.00  2015-01-09    visbms    ESCAN00080477     Just-in-time update for multiplex I-PDUs not working correctly
 *  05.01.00  2015-04-29    visbms    ESCAN00079850     FEAT-1315: IPDUM for CAN-FD supporting nPdu2Frame-Mapping
 *  05.01.01  2015-04-29    visbms    ESCAN00082757     Compiler error: undeclared identifiers if standard multiplexed PDUs are not configured
 *  05.01.02  2015-04-29    visbms    ESCAN00082763     IpduM does not initialize without multiplex I-PDUs
 *  05.01.03  2015-05-04    visbms    ESCAN00082896     Reception of Container PDUs is not functional
 *  05.01.04  2015-05-28    visbms    ESCAN00083164     Symbol IpduM_IsImmediateProcessingOfRxContainerPdu not found
 *  05.01.05  2015-06-24    visbms    ESCAN00083546     Compiler error: Linkage Error:Undefined symbol 'EcuM_BswErrorHook' in file 'obj\IpduM.o'
 *  05.01.05  2015-06-29    visbms    ESCAN00083693     Compiler error: IpduM.obj : error LNK2019: unresolved external symbol _IpduM_GetSizeOfRxInfo referenced in function _IpduM_RxIndication
 *  05.01.06  2015-09-01    visbms    ESCAN00084929     Compiler warning/error: function IpduM_GetAddrContainerTxBuffer not declared
 *  05.01.06  2015-09-02    visbms    ESCAN00084620     Wrong data copied on Container PDU reception
 *  06.00.00  2015-11-05    visbms    ESCAN00086291     Support Initialization without TriggerTransmit
 *  06.00.00  2015-11-21    visbms    ESCAN00084944     Additional (wrong) Contained-PDUs are received
 *  06.01.00  2016-02-17    visms     ESCAN00087830     FEAT-1631: Trigger Transmit API with SduLength In/Out according to ASR4.2.2
 *  06.01.00  2016-02-24    visbms    ESCAN00088515     Wrong TxConfirmations for configurations including multiplex PDUs and container PDUs at the same time
 *  06.01.00  2016-03-14    visbms    ESCAN00088285     Compiler warning: IpduM_JitUpdate declared static but never defined
 *  06.01.01  2016-03-31    visbms    ESCAN00089162     MISRA deviation: MISRA-C:2004 multiple Rules
 *  06.01.02  2016-04-15    visbms    ESCAN00089535     Container PDUs are transmitted immediately after the first Contained PDU is added
 *  06.01.02  2016-04-15    visbms    ESCAN00089431     Compiler error: IpduM_TxPathwayIdxOfTxLoInfoType undefined
 *  06.01.02  2016-04-18    visbms    ESCAN00089347     Update Bits not showing on Flexray
 *  06.01.03  2016-05-09    visbms    ESCAN00089814     Linker error: unresolved external symbol _IpduM_GetTxPartStaticPartIdxOfTxPathway referenced in function _IpduM_JitUpdate
 *  06.01.04  2016-06-14    visbms    ESCAN00090476     Unexpected ECU behavior on transmission of a multiplexed PDU without configured TxConfirmationPduId
 *  06.02.00  2016-06-21    visbms    ESCAN00090576     FEAT-1896: Missing part of FEAT-1503
 *  06.03.00  2016-10-13    visfrm    FEATC-276         FEAT-1920: SafeBSW Step 6
 *            2016-10-20    visbms    ESCAN00092160     Unexpected ECU behavior on transmission of container PDU in non-safeBSW stack
 *            2016-10-20    visbms    ESCAN00092429     Changed return value to E_OK for accepting the non-triggering multiplex TX part
 *            2016-10-21    visfrm    ESCAN00092431     Unexpected ECU behavior for too large (misconfigured) Contained PDUs
 *            2016-11-03    visbms    ESCAN00092631     Container PDUs stop being transmitted after 255 transmissions
 *            2016-11-03    visbms    ESCAN00089392     MISRA deviation: MISRA-C:2004 Rule 14.1
 *            2016-11-03    visfrm    ESCAN00092299     Compiler error: C4013: 'IpduM_IsSendTimeoutDefinedOfTxContainedPdu' undefined
 *  06.04.00  2016-11-04    visbms    ESCAN00092676     Container PDU Tx Confirmation not working
 *            2016-11-11    visfrm    ESCAN00092765     Endless loop for Container PDU transmission
 *            2016-11-17    visbms    ESCAN00092828     Out of bounds array write access for Container PDUs without TxConfirmation
 *  06.04.01  2016-12-02    visbms    ESCAN00093020     Container Tx Confirmation does not work for immediate transmitted PDUs
 *  06.05.00  2017-01-12    visbms    FEATC-955         FEAT-2072: Introduce separate main functions for reception and transmission for IPDUM
 *            2017-01-27    visbms    ESCAN00093682     Contained PDU is completely not received or routed if it is the last one in a container which is completely filled
 *            2017-01-27    visbms    ESCAN00093762     Large delay between first and second Container PDU transmissions using send timeouts
 *            2017-03-30    visbms    ESCAN00094014     Container PDUs fetched with TriggerTransmit do not appear on the bus
 *  06.05.01  2017-05-17    visbms    ESCAN00094970     Possible out of bounds write access with Tx Container PDUs
 *            2017-05-17    visbms    ESCAN00089599     DET error in Postbuild-Selectable Rx-only variant
 *  06.06.00  2017-07-07    visbms    STORYC-1913       Add Request Queue for TriggerTransmit of Container PDUs according to 4.2.2 Spec
 *  06.06.01  2017-08-28    visbms    ESCAN00096424     Unexpected behavior during Container PDU reception
 *            2017-08-28    visbms    ESCAN00096344     Endless loop during reception of different size Container PDUs with the same PDU ID
 *            2017-08-31    visbms    ESCAN00096366     Wrong data received during Container PDU reception
 *            2017-09-20    visbms    ESCAN00096743     TriggerTransmit Container PDU not appearing on the bus
 *  06.06.02  2017-09-18    visbms    STORYC-2530       Remove unused code if Container TriggerTransmit is not active
 *            2017-09-20    visbms    ESCAN00096618     Container PDUs lost on transmission
 *            2017-09-20    visbms    ESCAN00096611     Wrong container PDU transmission on queue overflow
 *  06.06.03  2017-09-22    visbms    ESCAN00096804     Linker error: Undefined Symbol IpduM_GetTxConfirmationTimeoutOfTxContainerPdu
 *  06.06.04  2017-12-04    visbms    ESCAN00097478     Container TriggerTransmit: some Contained PDUs missing or DET for invalid handle ID or invalid DLC value
 *            2017-12-06    visbms    ESCAN00096610     Container PDU with IpduMContainerTxFirstContainedPduTrigger always contains one PDU
 *  06.06.05  2017-12-08    visbms    ESCAN00097659     Contained PDUs with sendTimeout = 0 not transmitted
 *  06.07.00  2017-12-13    visbms    ESCAN00097673     Rx Container PDUs with invalid content are forwarded to PduR
 *  06.07.00  2017-12-19    visbms    STORYC-3561       Rx Container length calculation and Padding remove
 *  06.07.01  2018-01-08    visbms    ESCAN00097891     Compiler warnings: type conversion and unreferenced parameters
 *  06.07.01  2018-01-24    visbms    ESCAN00098037     Some contained Tx Pdus with last-is-best semantic not appearing on the bus
 *  06.08.00  2018-01-30    visbms    STORYC-2828       FEAT-3072 Support Static PDU Layout for Contained PDU (AR4.3.1 - RfC76543)
 *  06.08.01  2018-02-21    visbms    ESCAN00098231     Some contained Rx Pdus not being indicated to upper layer when non-unique header IDs are used
 *            2018-02-23    visbms    ESCAN00098274     Container PDU with defective data is transmitted on Queue Overflow
 *            2018-02-26    visbms    ESCAN00098506     Empty container PDU is transmitted to the bus
 *            2018-02-27    visbms    ESCAN00098349     Container PDUs transmitted when size threshold is reached and not when it is exceeded
 *            2018-03-02    visbms    ESCAN00097725     Wrong Rx Contained PDU is reported or Rx Contained PDU is not received
 *            2018-03-05    visbms    ESCAN00097724     Container PDU with invalid data or no data at all is transmitted
 *  07.00.00  2018-02-14    visms     ESCAN00098736     Compiler warning: unused parameter 'isTriggerTransmit' in  function 'IpduM_JitUpdate'
 *            2018-02-14    visms     ESCAN00098737     Compiler warning: unused parameter 'rxContainerId' in  function 'IpduM_searchRxHeaderId'
 *            2018-03-21    visssg    STORYC-4401       MISRA-C:2012 IpduM
 *            2018-04-09    visbms    ESCAN00098685     Empty Container PDU transmitted on Trigger Transmit bus with FirstContainedPduTrigger == true
 *            2018-04-09    visbms    ESCAN00098686     Empty Container PDU transmitted on Trigger Transmit bus
 *            2018-04-10    visbms    ESCAN00098676     Reception of larger than configured Container PDU leads to unexpected behavior.
 *            2018-04-10    visbms    ESCAN00098940     Endless loop during static-layout container PDU transmission with collection semantics "last is best".
 *            2018-04-13    visbms    ESCAN00099118     Compiler warning: C++ comment found
 *            2018-04-26    visssg    TASK-71522        CalculateSizeOfContainer needs API Pattern and test
 *  07.00.01  2018-06-11    visbms    ESCAN00099297     Container PDUs are transmitted in the wrong order
 *            2018-06-13    visbms    ESCAN00099671     DET error raised on last is best container PDU
 *  07.00.02  2018-10-24    visbms    ESCAN00101051     Static Layout Container Rx PDUs with no Update Bits are not being received.
 *            2018-10-25    visbms    ESCAN00101026     Static Layout Container PDUs with Last-is-Best and no Update Bits are being transmitted as empty Containers with no data.
 *            2018-10-25    visbms    ESCAN00101048     Compiler error: unknown function/macro IpduM_GetTxPathwayIdxOfTxLoInfo
 *            2018-10-30    visbms    ESCAN00092790     Unused parts of a multiplexed PDU contain old data for non-aligned dynamic parts
 *            2018-10-30    visbms    ESCAN00101025     Container PDUs with unknown Contained PDUs are transmitted after Queue Overflow
 *  07.00.03  2018-11-21    visbms    ESCAN00101414     MISRA deviation: MISRA-C:2004 Rule 10.4
 *  07.01.00  2018-12-18    visbms    ESCAN00101618     Defective Container PDUs transmitted for HeaderSize=NONE and UpdateBit not being configured
 *            2018-12-18    visssg    STORYC-6873       Support shortened Static Layout Rx Container PDUs
 *  07.01.01  2019-01-08    visbms    ESCAN00101716     Container Rx PDUs with headersize==NONE are not received for shortened DLC or completely filled container
 *  07.02.00  2019-03-14    visbms    STORYC-6468       Rework SBSW Justifications
 *            2019-03-27    visbms    ESCAN00101740     Additional unnecessary transmit requests for FlexRay FirstContainedPduTrigger PDUs
 *  07.03.00  2019-04-01    visbms    STORYC-7540       Remove MD_MSR_AutosarBoolean
 *            2019-04-01    visbms    STORYC-8080       Code Rework IpduM
 *  07.03.01  2019-04-05    visbms    ESCAN00102770     TxConfirmations for TriggerTransmit PDUs are not forwarded to the upper layer
 *            2019-04-10    visbms    ESCAN00102814     Compiler warning: warning C4100: 'TxPduId' : unreferenced formal parameter
 *  07.03.02  2019-04-17    vismij    ESCAN00102910     Reception of multiplexed PDU - dynamic part not forwarded
 *            2019-04-18    visbms    ESCAN00102886     Undefined behaviour due to memory access violation, only for TxContainer PDUs with TxConfirmation
 *  08.00.00  2019-05-24    visbms    STORYC-6550       Introduce priority for Tx ContainedIPdus with LastIsBest collection semantics part 1
 *  08.00.01  2019-11-21    visbms    ESCAN00104976     Compiler error: C4013: 'IpduM_CalculateSizeOfContainer' undefined; assuming extern returning int in configurations with SecOC only
 *  09.00.00  2020-01-21    visssg    COM-1314          Update ComStacklib and Minimmize the Number of SizeRelations
 *            2020-02-17    visssg    COM-1024          Replace RH by VCA Step 1
 *            2020-04-22    visbms    ESCAN00105140     Transmitted Container PDUs are delayed, and TxConfirmations not forwarded to upper layer
 *            2020-04-22    visbms    ESCAN00105568     Container Tx PDUs using "last is best" handling contain more PDUs than expected
 *  09.01.00  2020-06-18    vismij    COM-1431          Replace IpduM container mutex with exclusive area
 *            2020-06-22    visfrm    COM-1431          Replace IpduM container mutex with exclusive area
 *            2020-06-22    vismij    ESCAN00106648     TriggerTransmit Container PDU triggers are delayed
 *            2020-07-17    vismij    ESCAN00106550     TxConfirmations not forwarded to upper layer for Queued PDUs with only one Container in entire configuration
 *            2020-07-17    visfrm    ESCAN00106700     TxConfirmations for Container PDUs are called for the wrong PDUs or not at all
 *            2020-07-17    visfrm    ESCAN00106701     Container with None-Header fetched via TriggerTransmit API contains invalid data.
 *            2020-07-17    visfrm    ESCAN00106702     Container with None-Header and send timeout: additional transmit calls to lower layer
 *            2020-07-17    visfrm    ESCAN00106789     TxConfirmations not working for "last is best" Containers with headersize "short" or "long"
 *            2020-07-17    visfrm    ESCAN00106882     Last-is-best container PDUs can lead to unexpected behavior
 *            2020-07-17    visfrm    ESCAN00106338     dynamic container pdus are sent with incorrect pdus
 *            2020-07-20    visfrm    ESCAN00106886     Container PDUs using SendTimeout triggers are transmitted with wrong timings
 *            2020-07-20    visfrm    ESCAN00106828     First contained Pdu Trigger does not work for Container PDUs with "last is best" and headersize "short" or "large"
 *            2020-07-20    visfrm    ESCAN00106905     Tx Container PDUs using SendTimeout are transmitted at the wrong time
 *            2020-07-23    visfrm    ESCAN00106428     RxContained PDUs are received empty if PduLengthType is set too small
 *            2020-07-24    vismij    ESCAN00106945     After Container Tx Queue Overflow, TxConfirmations are forwarded for incorrect PDUs until the queue is emptied
 *            2020-07-28    visfrm    ESCAN00106619     Container PDUs with wrong data transmitted for static layouts without update bits
 *            2020-07-28    visfrm    ESCAN00106944     Rx Container PDUs with deferred processing and headerSize=none are received only partially
 *            2020-07-28    visfrm    ESCAN00106703     Last is best Container PDU transmitted with invalid data
 *            2020-07-28    visfrm    ESCAN00106781     IpduM Container PDU is transmitted with invalid data
 *  09.01.01  2020-11-13    visbms    ESCAN00107176     Compiler error: "errorId" is undefined
 *            2020-11-16    visbms    ESCAN00106885     Container TxConfirmations from within context of Transmit call are not forwarded to upper layer
 *            2020-11-16    visbms    ESCAN00107207     Container Rx PDUs with dynamic layout and additional, unnecessary Bytes at the end are processed incorrectly
 *            2020-11-16    visbms    ESCAN00107437     Container Rx PDUs with immediate processing are delayed
 *            2020-11-18    visbms    ESCAN00107686     Additional TxConfirmations are created by IpduM for Container PDUs with "last is best" collection semantics
 *            2020-11-18    visbms    COM-2006          Remove the AUTHOR IDENTIY
 *            2020-11-19    visbms    COM-2042          Remove VariantCoverage_OldStyleReports
 *  10.00.00  2020-11-24    visbms    COM-1883          Implement Container Rx Mainfunction Read Limit
 *            2020-12-01    visbms    COM-1886          Container Rx processing shall consider smaller received container
 *            2020-12-15    visfrm    ESCAN00108155     Reception of multiplexed PDU  - dynamic part not forwarded
 *  10.00.01  2021-02-02    visbms    ESCAN00108140     Container PDUs triggering too early, not filling the Container PDUs properly
 *  10.00.02  2021-02-16    visfrm    ESCAN00108183     Container Tx PDUs with last is best collection semantics are triggering unnecessary TriggerTransmit calls
 *********************************************************************************************************************/
#ifndef IPDUM_H
# define IPDUM_H

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
# include "IpduM_Cfg.h"
# include "IpduM_Lcfg.h"
# include "IpduM_PBcfg.h"
# include "ComStack_Types.h"

/**********************************************************************************************************************
  GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/*!
  \defgroup  IpduMIdentification IpduM Identification
  \brief  Vendor and module identification of this implementation.
  \{
*/
# define IPDUM_VENDOR_ID              30u              /**< the vendor ID of this implementation. */
# define IPDUM_MODULE_ID              52u              /**< the module ID of this implementation. */
/*!
  \}
*/

/*!
  \defgroup  IpduMSWVersion IpduM version number
  \brief  Version number of this implementation.
  \{
*/
# define IPDUM_SW_MAJOR_VERSION       10u
# define IPDUM_SW_MINOR_VERSION       0u
# define IPDUM_SW_PATCH_VERSION       2u
/*!
  \}
*/

/*!
  \defgroup  IpduMARReleaseVersion IpduM AUTOSAR release version number
  \brief  Version number of AUTOSAR release on which the appropriate implementation is based on.
  \{
*/
# define IPDUM_AR_RELEASE_MAJOR_VERSION       4u
# define IPDUM_AR_RELEASE_MINOR_VERSION       0u
# define IPDUM_AR_RELEASE_REVISION_VERSION    3u
/*!
  \}
*/

/*!
  \defgroup  IpduMDetErrorCodes IpduM Det Error Codes
  \brief  IpduM development error IDs.
  \{
*/
/* Always neccessary as init value! */
# define IPDUM_E_NO_ERROR                      0U   /**< this code is used to detect that no error occurred. Det_ReportError() is not called.  */

# if (IPDUM_DEV_ERROR_DETECT == STD_ON)

#  define IPDUM_E_PARAM                         16u /**< the API service has been with a wrong parameter. */
#  define IPDUM_E_PARAM_POINTER                 17u /**< the API service has been called with a not expected NULL pointer */
#  define IPDUM_E_UNINIT                        32u /**< the API service has been called before IPDUM was initialized with IpduM_Init() */
#  define IPDUM_E_INIT_FAILED                   33u /**< the API service has been called with a not expected NULL pointer */
#  define IPDUM_E_TRIGGERTRANSMITFAILED         34u /**< the call of PduR_IpduMTriggerTransmit has been returned with != E_OK */
#  define IPDUM_E_HEADER                        48u /**< erroneous container header detected */
#  define IPDUM_E_QUEUEOVFL                     49u /**< container queue overflow occurred */
/*!
  \}
*/

/*!
  \defgroup  IpduMApiIds IpduM Module Service Identifiers
  \brief  Unique identifier of a IPDUM module service.
  \{
*/
#  define IPDUM_APIID_INIT                      0x00
#  define IPDUM_APIID_VERSIONINFO               0x01
#  define IPDUM_APIID_RXINDICATION              0x42
#  define IPDUM_APIID_TRANSMIT                  0x49
#  define IPDUM_APIID_TXCONFIRMATION            0x40
#  define IPDUM_APIID_TRIGGERTRANSMIT           0x41
#  define IPDUM_APIID_MAINFUNCTIONTX            0x12
#  define IPDUM_APIID_MAINFUNCTIONRX            0x11
#  define IPDUM_APIID_CALCULATECONTAINERSIZE    0x26
/*!
  \}
*/
# endif

/**********************************************************************************************************************
  GLOBAL FUNCTION MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/
#define IPDUM_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h"    /* PRQA S 5087 */        /*  MD_MSR_MemMap */

#if(IPDUM_USE_INIT_POINTER == STD_ON)
extern P2CONST(IpduM_ConfigType, IPDUM_VAR_ZERO_INIT, IPDUM_INIT_DATA) IpduM_ConfigDataPtr;
#endif

#define IPDUM_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h"    /* PRQA S 5087 */        /*  MD_MSR_MemMap */

/**********************************************************************************************************************
  GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/
# define IPDUM_START_SEC_CODE
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_MemMap */

/*******************************************************************************************
*  IpduM_Init()
*******************************************************************************************/
/*! \brief        Initializes component
 *  \details      Initializes all component variables and sets the component state to initialized
 *  \param[in]    config    Component configuration structure
 *  \pre          Interrupts are disabled
 *  \pre          Module is uninitialized
 *  \pre          IpduM_InitMemory has been called unless IpduM_ModuleInitialized is initialized by start-up code
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \trace        CREQ-102610
 *  \trace        SPEC-2914519, SPEC-2914520, SPEC-2914521, SPEC-2068173
*******************************************************************************************/
FUNC(void, IPDUM_CODE) IpduM_Init(P2CONST(IpduM_ConfigType, AUTOMATIC, IPDUM_INIT_DATA) config);

/*******************************************************************************************
*  IpduM_InitMemory()
*******************************************************************************************/
/*! \brief        Power-up memory initialization
 *  \details      Initializes component variables in *_INIT_* sections at power up.
 *  \pre          Module is uninitialized
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \note         Use this function in case these variables are not initialized by the startup code
*******************************************************************************************/
FUNC(void, IPDUM_CODE) IpduM_InitMemory(void);

# if (IPDUM_VERSION_INFO_API == STD_ON)
/*******************************************************************************************
*  IpduM_GetVersionInfo()
*******************************************************************************************/
/*! \brief        Returns the version information
 *  \details      Returns version information, vendor ID and AUTOSAR module ID of the component
 *  \param[out]   versioninfo    Pointer to where to store the version information. Parameter must not be NULL
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *  \trace        CREQ-102612
 *  \trace        SPEC-2068177
*******************************************************************************************/
FUNC(void, IPDUM_CODE) IpduM_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, IPDUM_APPL_DATA) versioninfo);
# endif

/*******************************************************************************************
*  IpduM_Transmit()
*******************************************************************************************/
/*! \brief        Requests the transmission of a static or dynamic part or a contained PDU.
 *  \details      -
 *  \param[in]    PdumTxPduId
 *  \param[in]    PduInfoPtr    Pointer to payload buffer
 *  \return       E_OK          Transmit request was accepted by IpduM and destination layer
 *  \return       E_NOT_OK      Transmit request was not accepted
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE for different handle IDs
 *  \synchronous  TRUE
 *  \note         Called by PduR module
 *  \trace        CREQ-102653
 *  \trace        SPEC-2068157, SPEC-2068181
*******************************************************************************************/
FUNC(Std_ReturnType, IPDUM_CODE) IpduM_Transmit(PduIdType PdumTxPduId, P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr);

# if (IPDUM_TXCONTAINEDPDU == STD_ON)
/*******************************************************************************************
 *  IpduM_CalculateSizeOfContainer()
*******************************************************************************************/
/*! \brief        Calculates and returns the size of the container PDU in the passed buffer.
 *  \details      -
 *  \param[in]    PduInfoPtr        Pointer to the buffer where the container is stored and its max length.
 *  \param[in]    headerSize
 *  \return       containerSize     Size of the container in bytes, including the closing zero-header.
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *  \trace        SPEC-2068547
*******************************************************************************************/
FUNC(uint32, IPDUM_CODE) IpduM_CalculateSizeOfContainer(PduLengthType headerSize, P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr);
# endif

# define IPDUM_STOP_SEC_CODE
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_MemMap */

/*!
* \exclusivearea IPDUM_EXCLUSIVE_AREA_0
* Ensures consistency of global RAM variables.
* \protects All affected global RAM variables.
* \usedin IpduM_Init, IpduM_MainFunctionTx, IpduM_MainFunctionRx, IpduM_Transmit, IpduM_TriggerTransmit, IpduM_TxConfirmation, IpduM_RxIndication
* \exclude All functions provided by IpduM.
* \length SHORT depending on the API and the call graph.
* \endexclusivearea
*/

#endif /* IPDUM_H */

/**********************************************************************************************************************
 *  END OF FILE: IpduM.h
 *********************************************************************************************************************/
