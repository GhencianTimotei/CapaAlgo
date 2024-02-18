
/* ********************************************************************************************************************
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
 */
/*!  Project    MICROSAR Diagnostic Event Manager (Dem)
 *
 *  \defgroup   Dem_Master    Dem Master Functionality
 *  \{
 *  \}
 *  \defgroup   Dem_Shared    Dem Shared Functionality
 *  \{
 *  \}
 *
 *  \ingroup    Dem_Shared
 *  \defgroup   Dem_Main Dem API
 *  \{
 *  \file       Dem.h
 *  \brief      Implementation header file for the MICROSAR Dem
 *  \details
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author       Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  04.00.00  2012-06-29  vismhe       ESCAN00057159 AR4-82: DEM 4.x
 *                        visade       ESCAN00057159 AR4-82: DEM 4.x
 *  04.01.00  2012-09-07  vismhe       ESCAN00061254 VersionInfo API returns wrong version number
 *            2012-09-14  vismhe       ESCAN00061429 Autostart cycle has no effect
 *            2012-09-20  vismhe       ESCAN00061565 Wrong snapshot record number reported for 19 03
 *            2012-10-26  vismhe       ESCAN00062489 Compiler warning: Condition is always true
 *            2012-10-26  vismhe       ESCAN00062490 Compiler warning: Condition is always true
 *            2012-10-26  vismhe       ESCAN00062483 Unexpected ClearAllowed callback
 *  04.02.00  2012-11-05  vismhe       ESCAN00062646 Compiler warning: Function "Dem_Queue_CancelOperation" was declared but never referenced
 *            2012-11-05  vismhe       ESCAN00062647 Compiler warning: Variable "Dem_Mem_PrimaryInfo" was declared but never referenced
 *            2012-11-05  vismhe       ESCAN00062644 Compiler warning: Variable "lResult" was set but never used
 *            2012-11-06  vismhe       ESCAN00062645 Compiler warning: Variable "lOldEventStatus" was set but never used
 *            2012-11-06  visade       ESCAN00062771 Memory corruption after call of Dem_SetDTCFilter()
 *            2012-12-07  vismhe       ESCAN00061769 AR4-207: Support VCC Diagnostic specification and required Diagnostic RFCs
 *  04.03.00  2013-02-04  visdth       ESCAN00061747 OBDII Support: IUMPR handling added
 *            2013-03-05  vismhe       ESCAN00065600 DET error DEM_E_UNINIT in Dem_Mainfunction
 *            2013-03-08  visade       ESCAN00061747 AR4-55: DEM - OBDII Support
 *            2013-03-13  visdth       ESCAN00063590 OBD IUMPR Counting Misbehavior
 *            2013-03-13  visdth       ESCAN00065851 Support User Controlled Warning Indicator Request
 *            2013-03-13  visdth       ESCAN00065853 Support suppression of permanent DTC storage
 *            2013-03-13  visdth       ESCAN00065854 Support MIL Groups
 *            2013-03-13  vismhe       ESCAN00065867 Allow PendingDTC independent from event storage
 *            2013-03-13  vismhe       ESCAN00065868 Support different DTC aging protocols
 *  04.04.00  2013-04-02  visade       ESCAN00066314 Compiler warning: multiple dead assignments within Dem.c
 *            2013-04-03  vismhe       ESCAN00065209 AR4-375: Add Support of "Suppress DTC" in Dem
 *            2013-04-10  visdth       ESCAN00066201 Extension of Interface to read IUMPR data
 *            2013-04-26  vismhe       ESCAN00067007 Secondary Memory DTCs do not report Severity and FunctionalUnit information
 *  04.04.01  2013-05-15  visade       ESCAN00067368 Compiler error: OdometerAtClear is not a member of Dem_Cfg_AdminDataType_s
 *            2013-05-15  visade       ESCAN00067372 Compiler error: Dem_Cfg_ObdGetGlobalDenominator() not a modifiable lvalue
 *            2013-05-15  visade       ESCAN00067155 Missing type definitions if Dem is used without Rte
 *            2013-05-15  visade       ESCAN00067025 Include FiM.h only if IUMPR or FiM notification is enabled
 *            2013-05-22  vismhe       ESCAN00067180 Compiler warning: uninitialized local variable 'lDtcStatusNew' used
 *            2013-05-22  vismhe       ESCAN00067354 Compilation error: Undefined symbol
 *            2013-05-22  vismhe       ESCAN00067345 Compilation error: Undefined symbol
 *            2013-05-22  vismhe       ESCAN00067459 Compiler warning: dead assignment to "lReturnValue" eliminated
 *  04.05.00  2013-06-03  visade       ESCAN00067673 Change Permanent Activation Distance from absolute to relative distance calculation
 *            2013-06-10  visade       ESCAN00067618 Out-parameter not initialized in Dem_GetIUMPRGeneralData
 *            2013-06-19  visdth       ESCAN00068159 MIL Group trip counter not reset on ClearDTC
 *            2013-06-19  vismhe       ESCAN00067715 AR4-418: Support Event Combination Type 1
 *            2013-06-19  vismhe       ESCAN00068164 Immediately persist event status on ClearDTC
 *            2013-06-19  vismhe       ESCAN00068389 Extended use of Dem_GetSeverityOfDTC and Dem_GetFunctionalUnitOfDTC
 *            2013-06-27  vismhe       ESCAN00068390 OperationCycles not stopped during Shutdown
 *            2013-09-18  vismhe       ESCAN00070478 Unexpected value for EventStatusChanged and DTCStatusChanged callbacks
 *  04.05.01  2013-07-03  vismhe       ESCAN00068511 Compiler error: Dem.c: 'Dem_Cbk_InitMonitor' undefined
 *  04.05.02  2013-07-03  vismhe       ESCAN00068562 Mode 0x02 does not return data
 *            2013-07-04  vismhe       ESCAN00068508 IUMPR: Numerator is incremented without qualified test result
 *            2013-07-04  vismhe       ESCAN00068569 Suppression or UserControlled WIR has no effect
 *  04.05.03  2013-07-10  visade       ESCAN00068885 Provide OBD FreezeFrame in 0x1904 although Snapshots Records are disabled
 *            2013-07-18  visade       ESCAN00069154 Missing cast truncates OBD DTC number
 *            2013-07-22  vismhe       ESCAN00069132 Mixed internal and external data records are stored misaligned
 *            2013-07-22  vismhe       ESCAN00069237 Allow to override static / inline specific to Dem module
 *            2013-07-23  vismhe       ESCAN00069270 Too many increments of occurrence counter
 *            2013-07-23  vismhe       ESCAN00069271 DTC starts aging although it is still pending
 *            2013-07-23  visdth       ESCAN00068577 IUMPR Counters may be incremented more than once per DCY
 *  04.06.00  2013-07-24  visade       ESCAN00069311 Missing DID/PID validation check in Dem_GetEventFreezeFrameData()
 *            2013-07-24  visade       ESCAN00068636 AR4-419: Support Multiple OBD Freeze Frames
 *            2013-08-02  visade       ESCAN00069587 The code shall compile if NVM support is disabled and OBD support is enabled
 *            2013-08-06  visade       ESCAN00069626 OBD DTC Status does not qualify
 *            2013-08-07  visade       ESCAN00069423 OBD relevant data is not reset on configuration change
 *            2013-08-08  visade       ESCAN00069683 Erroneous indicator decrement during Mode 0x04
 *            2013-08-14  vismhe       ESCAN00069801 BSW error reporting after PreInit and before Init not possible
 *  05.00.00  2013-09-03  vismhe       ESCAN00068165 Compiler warning: Condition is always constant
 *            2013-09-03  vismhe       ESCAN00068395 AR4-292: Reporting of DET and DEM errors via DLT
 *            2013-09-03  vismhe       ESCAN00068416 AR4-420: Postbuild Loadable Support
 *            2013-09-03  vismhe       ESCAN00068465 AR4-371: Support signal interface
 *            2013-09-03  vismhe       ESCAN00068526 AR4-409: Support of OEM Volvo AB
 *            2013-09-03  vismhe       ESCAN00068530 AR4-542: Support of OEM Ford
 *            2013-09-03  vismhe       ESCAN00069882 Internal event is not cleared
 *            2013-09-03  vismhe       ESCAN00069989 Compiler warning: variable "lEntry" was set but never used
 *            2013-09-03  vismhe       ESCAN00069805 Add verification of EventKind to ReportErrorStatus and SetEventStatus
 *            2013-09-04  visdth       ESCAN00070048 OBD IUMPR: reading the same ratio several times is not possible
 *            2013-09-11  vismhe       ESCAN00070346 AgingCounter is reported with incorrect value
 *            2013-09-16  vismhe       ESCAN00069943 Delay WarmUpCycle until restart of Driving Cycle
 *            2013-09-16  vismhe       ESCAN00070219 Reset PID 0x21 if no OBD DTC requests the MIL for 40 warm-up cycles
 *            2013-09-19  vismhe       ESCAN00070500 Remove DET for consecutive qualified DCY reports
 *            2013-09-26  vismhe       ESCAN00070686 ConfirmedDTC is reset on initialization
 *            2013-10-02  vismhe       ESCAN00070834 Incorrect event displaced on overflow
 *            2013-11-27  vismhe       ESCAN00072203 Memory overwritten during initialization
 *  05.00.01  2013-11-13  vismhe       ESCAN00071873 DTCs do not age
 *            2013-11-14  vismhe       ESCAN00071948 Compiler warning: Definition different from declaration
 *  05.01.00  2013-10-17  visade       ESCAN00071182 Incorrect MIL group behavior after ClearAllDTCs
 *            2013-10-22  visade       ESCAN00071161 Change initialization of PID 0x31
 *            2013-10-22  visade       ESCAN00071162 Support ClearSingleDtc for OBD ECUs
 *            2013-10-25  visade       ESCAN00071244 Provide Dem internal EventId in Environmental Data
 *            2013-10-25  visade       ESCAN00071425 Provide OBD DTC in Environmental Data
 *            2013-10-30  visade       ESCAN00071346 Support application interface providing the permanent DTC activation state
 *            2013-11-20  vismhe       ESCAN00072084 Incorrect value for maximum FDC in current cycle
 *            2013-11-20  vismhe       ESCAN00071550 Incorrect status report handling for BSW errors
 *            2013-11-21  visade       ESCAN00072122 Stored UDS DTC does not have Confirmed and WarningIndicator bit set
 *            2013-11-28  vismhe       ESCAN00072310 Incorrect PID21 handling
 *  06.00.00  2014-02-04  visade       ESCAN00072994 Admin data is not persisted during shutdown if no Operation Cycle was started
 *            2014-02-04  vismhe       ESCAN00073575 Compile/Validation error: Incompatible prototypes
 *            2014-02-04  vismhe       ESCAN00073578 Rework NV MemoryAbstraction
 *            2014-02-04  vismhe       ESCAN00070873 AR4-402: Support of OEM Ford
 *            2014-02-04  visade       ESCAN00071380 AR4-465: Support for J1939 Diagnostics - API to DCM according AR 4.1.2
 *            2014-02-04  visade       ESCAN00071379 AR4-465: Support for J1939 Diagnostics
 *            2014-02-14  visade       ESCAN00073721 Driving cycle remains qualified after automatic end
 *            2014-02-18  vismhe       ESCAN00073792 Diagnostics locked when clearing DTCs
 *            2014-02-18  vismhe       ESCAN00079177 Compiler warning: Name Dem_DTCGroupType has already been declared
 *  06.01.00  2014-03-10  visdth       ESCAN00073613 Numerator is only incremented with fulfilled General Denominator conditions
 *            2014-03-12  vismhe       ESCAN00074193 NRC "conditions not correct" for services 19 04, 19 06
 *            2014-03-12  vismhe       ESCAN00074203 AR4-673: Diag_Asr4J1939Dcm + Diag_Asr4Dem shall work without Diag_Asr4Dcm
 *            2014-03-13  vismhe       ESCAN00074248 Compiler error: Missing type definition Dem_J1939DcmDiagnosticReadinessNType
 *            2014-03-12  visade       ESCAN00073876 Lock Numerator increment during active tester communication
 *            2014-03-13  visade       ESCAN00074253 Compile error if Aging is configured to start at passed
 *            2014-03-21  vismhe       ESCAN00074493 DTC does not re-enable after suppression
 *            2014-03-21  vismhe       ESCAN00074494 DTCs do not respect multiple trips
 *            2014-03-25  vismhe       ESCAN00074541 Hide Dependent OBD DTCs in UDS diagnostic services
 *            2014-03-25  vismhe       ESCAN00074410 Incorrect old DTC status in DtcStatusChangeCbk
 *            2014-03-26  vismhe       ESCAN00074566 Event does not debounce correctly
 *            2014-03-27  vismhe       ESCAN00074598 Significance value reported incorrectly in extended records
 *            2014-03-28  vismhe       ESCAN00074644 Time debounced events report wrong maximum debounce value
 *            2014-03-28  vismhe       ESCAN00074647 Occurrence Counter reported incorrectly
 *            2014-03-28  vismhe       ESCAN00073289 Add Operating Hours to Standardized Environmental Data
 *            2014-04-02  visade       ESCAN00074740 Possible out of bound access for variable Dem_Cfg_ObdIumprData.Status
 *            2014-04-02  vismhe       ESCAN00074743 Wrong result when reporting invalid event status
 *  06.02.00  2014-04-23  vismhe       ESCAN00074202 AR4-670: Support DTC Pre-storage
 *            2014-04-23  vismhe       ESCAN00075221 Support 16 Operation Cycles
 *            2014-04-23  vismhe       ESCAN00075100 Usage of OSEK OS symbol can cause errors during preprocessing
 *            2014-04-24  vismhe       ESCAN00075205 Provide API Dem_SetEventAvailable
 *            2014-04-24  vismhe       ESCAN00075207 Suppressed Events do not confirm
 *            2014-04-28  visade       ESCAN00073569 Do not track the ratio for suppressed DTCs/Events
 *            2014-05-05  vismhe       ESCAN00075368 Incorrect new DTC status reported in DTC status changed callback
 *            2014-05-07  visade       ESCAN00075400 PID 0x21 is not cleared if MIL is not triggered
 *            2014-05-08  visade       ESCAN00074965 Loop underrun in function Dem_EnablePermanentStorage()
 *            2014-06-04  vismhe       ESCAN00075786 Dem does not compile if PID 0x21 is not enabled
 *            2014-05-21  vismhe       ESCAN00075810 OBD Freeze Frame is not cleared correctly
 *            2014-06-04  vismhe       ESCAN00076016 Compile Error: Multiple errors for OBD DEM with feature OBD disabled
 *            2014-06-04  vismhe       ESCAN00076021 Compiler error: Undefined preprocessor identifier in Dem_Dcm.h
 *  07.00.00  2014-06-25  vismhe       ESCAN00076615 AR4-732: Application Trigger for NV Synchronization
 *            2014-06-25  vismhe       ESCAN00076615 AR4-732: Extend aging behavior to not require TFTOC==false
 *            2014-06-30  vismhe       ESCAN00076615 AR4-732: Added support for Clear DTC Limitation
 *            2014-07-02  vismhe       ESCAN00076615 AR4-732: Added support FDC trip / once per cycle
 *            2014-06-25  vismhe       ESCAN00076450 Compiler error: inline function's body is not declared previously
 *            2014-06-30  vismhe       ESCAN00077724 AR4-698: Move InitPointer to Dem_Init
 *            2014-07-02  visade       ESCAN00076529 AR4-607: Option to store the Fault Detection Counter in NVRAM
 *            2014-07-02  vismhe       ESCAN00076664 Improve DTC status recovery after power loss
 *            2014-07-02  visade       ESCAN00076667 Remove support of DEM_DTC_FORMAT_OBD from DTC suppression
 *            2014-07-10  vismhe       ESCAN00076878 Improve robustness against Shutdown
 *            2014-07-11  vismhe       ESCAN00076920 Wrong result when extended record is not stored
 *            2014-07-11  vismhe       ESCAN00076982 Implausible value for extended data records mapped to aging counter
 *            2014-07-23  visade       ESCAN00076612 AR4-741: Support multiple J1939 nodes in DEM and J1939DCM
 *            2014-08-07  vismhe       ESCAN00077685 Improve robustness of disable DTC record update
 *            2014-08-07  visade       ESCAN00077680 Do not report previously OBD relevant DTCs in Mode 0x0A
 *            2014-08-08  vismhe       ESCAN00077722 Compiler warning: 'EventId' : unreferenced formal parameter
 *            2014-08-12  vismhe       ESCAN00074759 Feature J1939 and EventCombination does not work together
 *            2014-08-25  vismhe       ESCAN00074190 Restore ConfirmedBit when StorageTrigger == Confirmed
 *            2014-08-25  vismhe       ESCAN00077999 Service 19 02 does not report all DTCs
 *            2014-09-12  vismhe       ESCAN00078381 Dem_GetIUMPRGeneralData returns an incorrect value for 'NumberOfRatios'
 *            2014-09-30  vismhe       ESCAN00078498 Recover external visible OBD Freeze Frame if event in memory is not OBD relevant by configuration (anymore)
 *            2014-10-01  visade       ESCAN00078639 Add NVRAM Recovery for Permanent Memesry
 *            2014-10-10  vismhe       ESCAN00078806 Wrong event displaced from event memory
 *            2014-10-13  vismhe       ESCAN00078902 Event availability not working with combined events
 *            2014-10-13  vismhe       ESCAN00068635 Compiler warning: expression always constant
 *            2014-10-13  vismhe       ESCAN00070124 Compiler warning: conditional expression is constant
 *            2014-10-13  vismhe       ESCAN00076527 AR4-572: Ford/Mazda Feature Complete - Ford in AR environment
 *            2014-10-13  vismhe       ESCAN00076605 AR4-669: Support for J1939 Diagnostics
 *            2014-10-13  vismhe       ESCAN00080571 Memory corruption when aging DTCs
 *            2015-01-14  vismhe       ESCAN00081016 Out of bound memory read access for Dem_Cfg_ObdIumprData.Status
 *  08.00.00  2014-11-24  vismhe       ESCAN00079766 Remove API Dem_GetNextIUMPRRatioData
 *            2014-11-24  vismhe       ESCAN00079776 Combined events not correctly unavailable in postbuild configuration
 *            2014-11-24  vismhe       ESCAN00079653 Change return value for API Dem_SetOperationCycleState()
 *            2014-11-24  visade       ESCAN00079787 Compiler warning: Dead assignment in function Dem_Data_PermanentEntryFind()
 *            2014-12-04  visade       ESCAN00079994 1-Trip DTC without the need for a qualified driving cycle
 *            2014-12-04  vismhe       ESCAN00079778 A Monitor Report is lost
 *            2014-12-05  vismhe       ESCAN00080187 FEAT-412 Support latching TestFailed of confirmed DTCs
 *            2014-12-11  vismhe       ESCAN00080187 FEAT-412 Support Freezing/Resetting the debouncing state by API
 *            2014-12-11  vismhe       ESCAN00080187 FEAT-412 Support init monitor notification when debouncing is reenabled
 *            2014-12-11  vismhe       ESCAN00080187 FEAT-412 Transport NvM error result to ClearDTC Api
 *            2014-12-17  visade       ESCAN00080224 Support of 3 Byte OBD DTC for DEM internal data element
 *            2015-01-12  vismhe       ESCAN00079539 FEAT-1200: Support of length information in Snapshot
 *            2015-01-12  vismhe       ESCAN00079539 FEAT-1200: Option to rest TF bit on operation cycle start
 *            2015-01-14  vismhe       ESCAN00080283 FEAT-427: Refactoring of large functions, rework function headers
 *            2015-01-21  visade       ESCAN00080705 Permanent DTC without permanent memory activation
 *            2015-01-21  visade       ESCAN00080718 Remove DCY wait state for permanent DTCs after CodeClear
 *            2015-01-21  visade       ESCAN00080178 Add DCY qualification as permanent DTC erase condition
 *            2015-01-28  vismhe       ESCAN00080898 Out of bounds memory read access
 *            2015-02-06  visade       ESCAN00081089 Improve NVRAM recovery for combined events in permanent memory
 *            2015-02-06  visade       ESCAN00081024 IUMPR - erroneous numerator increment
 *            2015-02-12  vismhe       ESCAN00081038 Event reports are not processed correctly before Dem_Init()
 *            2015-02-12  vismhe       ESCAN00081188 Keep auto-start cycles active after shutdown
 *            2015-02-15  vismhe       ESCAN00080245 FEAT-473: Support default initialization for event available state
 *            2015-02-18  vismhe       ESCAN00081328 Critical section is kept in lock state
 *            2015-02-20  vismhe       ESCAN00080555 Compiler warning: 'FreezeFrameIndex' : unreferenced formal parameter
 *            2015-02-23  visade       ESCAN00081400 Make active DTC immediately visible after permanent memory activation
 *            2015-02-25  visade       ESCAN00079859 FEAT-643: Support WWH OBD (Beta)
 *            2015-02-27  vismhe       ESCAN00081529 Blocking of ClearDTC while processing ClearSingleDTC
 *            2015-03-10  vismhe       ESCAN00081708 DTC aging starts too early
 *            2015-03-19  vismhe       ESCAN00079199 Compiler warning: 'FreezeFrameIndex' : unreferenced formal parameter
 *            2015-03-19  vismhe       ESCAN00079200 Compiler warning: 'SRecIndex' : unreferenced formal parameter
 *  09.00.00  2015-03-24  visade       ESCAN00082399 FEAT-1446: Make OBD II Freeze Frame optional in Service 0x1904
 *            2015-03-31  visade       ESCAN00082399 FEAT-1446: Optionally restart DCY on ClearAllDTCs
 *            2015-04-01  vismhe       ESCAN00082199 Compiler warning: Unitialized variable lReturnValue
 *            2015-04-08  visade       ESCAN00082399 FEAT-1446: Add option to displace Pending OBD Freeze Frame
 *            2015-04-09  vismhe       ESCAN00082289 Displacement of wrong DTC
 *            2015-04-09  vismhe       ESCAN00082319 Compiler error: Missing 'else' block
 *            2015-04-20  vismhe       ESCAN00082534 Compiler error or warning:  initializer type incompatible with object type
 *            2015-04-20  vismhe       ESCAN00082346 FEAT-56: Support data callbacks with EventId parameter
 *            2015-04-23  vismhe       ESCAN00082348 FEAT-285: Support healing for events without indicator
 *            2015-04-23  vismhe       ESCAN00082348 FEAT-285: Support debouncing while enable conditions are locked
 *            2015-05-05  visade       ESCAN00082811 Environmental data is missing for confirmed DTC
 *            2015-05-22  vismhe       ESCAN00082348 FEAT-285: Support entry retry
 *            2015-06-03  vismhe       ESCAN00082346 FEAT-56: Support data callbacks without NV storage
 *            2015-06-03  vismhe       ESCAN00082346 FEAT-56: Support JLR specific snapshot trigger
 *            2015-06-09  vismhe       ESCAN00082346 FEAT-56: Support aging at passed trigger for aging target == 0
 *            2015-06-26  vismhe       ESCAN00079889 Status change callback called without change of status
 *            2015-06-29  visade       ESCAN00083654 1-Trip DTC not available in Mode 0x0A
 *            2015-07-02  vismhe       ESCAN00083400 Compiler warning:  narrowing or signed-to-unsigned type conversion found
 *            2015-07-06  vismhe       ESCAN00083803 Combined events age without completed test
 *            2015-07-08  vismhe       ESCAN00082762 Compiler error: E0516: Zero sized structure 'DebounceInfo', E0823: Too long macro expansion 'VStdMemSet'
 *            2015-07-21  vismhe       ESCAN00084110 DID length is not included in snapshot record
 *            2015-07-21  visade       ESCAN00082355 FEAT-397: Support of WWH-OBD in Dcm and Dem [AR4-749] incl. Variant Handling for WWH-OBD use case
 *  10.00.00  2015-08-28  vismhe       ESCAN00084816 Compiler error: struct has no member SnapshotData
 *            2015-08-28  vismhe       ESCAN00084822 Compiler error: struct has no member MaxDebounceValue, missing symbols DEM_ESM_TEST/SET_FDC_MAX
 *            2015-08-28  vismhe       ESCAN00084823 Compiler error: undefined symbol Dem_Mem_SetOdometerMilOn
 *            2015-08-28  vismhe       ESCAN00084837 Compiler error: undefined symbol Dem_Cfg_GlobalIndicatorStates
 *            2015-08-28  vismhe       ESCAN00084839 Compiler error: undefined symbol Dem_Data_CollectDid
 *            2015-08-31  vismhe       ESCAN00084885 Compiler error: undefined symbol lEventId
 *            2015-09-02  vismhe       ESCAN00084948 Compiler error: syntax error in Dem_J1939Dcm_GetNextDTCwithLampStatus
 *            2015-09-03  vismhe       ESCAN00084954 Compiler error: undefined symbol 'Dem_Esm_TestEventHealed'
 *            2015-09-03  vismhe       ESCAN00084615 ClearDTC for secondary memory deletes wrong DTCs
 *            2015-09-10  vismhe       ESCAN00085138 DTCs not stored on FaultDetectionCounter Threshold
 *            2015-09-11  vismhe       ESCAN00085160 Compiler error: undefined symbol 'lNewEventStatus'
 *            2015-09-11  vismhe       ESCAN00085162 Compiler error: undefined symbol 'Dem_Queue_CalculatePid4E'
 *            2015-09-14  vismhe       ESCAN00084044 Indicator is reported active without requesting DTC
 *            2015-09-14  vismhe       ESCAN00085009 Support non-volatile availability setting
 *            2015-11-10  vismhe       ESCAN00085612 Out of bounds memory write access
 *            2015-11-10  vismhe       ESCAN00085604 Statistic values 'Failed Cycles counter', 'Consecutive Failed Cycles Counter' do not update correctly
 *            2015-11-10  vismhe       ESCAN00085552 Missing Data after DTC re-occurrence
 *            2015-11-20  vismhe       ESCAN00086554 Remove initailaziation check from API Dem_NvM_InitObdPermanentData
 *            2015-11-26  vismhe       ESCAN00086756 Code depends on undefined behavior
 *            2015-11-26  vismhe       ESCAN00086757 Dem calls FiM_DemTriggerOnEventStatus before initialization
 *            2015-11-26  vismhe       ESCAN00086808 Cycles since last failed not updated correctly
 *            2015-11-26  vismhe       ESCAN00086603 Compiler warning: variable "lOldStatus/lNewStatus" was set but never used
 *            2015-11-26  vismhe       ESCAN00086539 Compiler warning: variable 'lSRecId'/'lCfgSRecIndex' was set but never used
 *            2015-11-26  vismhe       ESCAN00086537 Compiler warning: variable 'lSRecId' was set but never used
 *            2015-11-26  visanh       ESCAN00085828 FEAT-1334: Support Time-series Snapshot Data Records
 *            2015-11-26  visanh       ESCAN00085143 FEAT-1527: SafeBSW Step 3
 *            2015-11-26  vismhe       ESCAN00085143 FEAT-1527: SafeBSW Step 3
 *            2015-11-30  vismhe       ESCAN00086885 Dcm cannot lock DTCs (unexpected NRC22)
 *            2015-12-14  vismhe       ESCAN00086336 Aging behavior for AgingTarget==0 is incorrect
 *            2015-12-14  vismhe       ESCAN00086887 Allow Dem_SetWIRStatus during ControlDTCSetting
 *  11.00.00  2016-01-14  vismhe       ESCAN00087477 Cannot report event status
 *            2016-01-14  vismhe       ESCAN00087481 Compiler error: Undefined symbol Dem_Esm_TestEventHealed
 *            2016-01-20  visanh       ESCAN00087429 Memory overwritten when using internal data elements in time series snapshot records
 *            2016-01-20  visanh       ESCAN00087534 Time Series Snapshot Records cannot be used without time based debouncing
 *            2016-02-03  vismhe       ESCAN00087637 FEAT-1472: Implement RoE for VAG
 *            2016-02-29  vismhe       ESCAN00088591 Permanent memory initialization pattern is overwritten
 *            2016-02-29  visanh       ESCAN00087794 FEAT-1688: SafeBSW Step 4
 *            2016-02-29  vismhe       ESCAN00087794 FEAT-1688: SafeBSW Step 4
 *            2016-03-07  vismhe       ESCAN00087325 Incorrect behavior for disablement of numerators and denominators after Clear DTC
 *            2016-03-11  vismhe       ESCAN00087868 FEAT-1605: Support DM5/27/53/54/55 in J1939Dcm
 *            2016-03-15  vismhe       ESCAN00088915 Fault data updated too often
 *            2016-03-23  vismhe       ESCAN00089043 Combined DTC incorrectly sets Pending and Confirmed bit
 *            2016-03-23  vismhe       ESCAN00089057 WarmUp cycle not restarted automatically
 *  12.00.00  2016-03-29  visanh       ESCAN00088997 FEAT-1770: Support up to 255 Enable and Storage Conditions
 *            2016-04-07  visanh       ESCAN00089288 Incorrect Maximum FDC Since Last Clear
 *            2016-04-08  visade       ESCAN00089273 FEAT-1723: Support clear PDTC without PFC if event has a ratio attached
 *            2016-04-11  visade       ESCAN00089273 FEAT-1723: Support IUMPR in environmental data
 *            2016-04-11  visade       ESCAN00089273 FEAT-1723: Support OBD DTCs that do not trigger the MIL (Black MIL)
 *            2016-04-11  visanh       ESCAN00089273 FEAT-1723: Change API name Dem_SetPfcCycle
 *            2016-04-11  visanh       ESCAN00089273 FEAT-1723: Provide API Dem_GetDebouncingOfEvent
 *            2016-04-13  visade       ESCAN00089273 FEAT-1723: Support Readiness Group based IUMPR data retrieval
 *            2016-04-20  visanh       ESCAN00089353 FEAT-1724: OBD: Support for DTR (Diag Test Results)
 *            2016-04-29  visade       ESCAN00089767 Reset ratio status before call of init monitor function
 *            2016-05-02  visanh       ESCAN00089273 FEAT-1723: Support similar conditions
 *            2016-05-23  vissat       ESCAN00089273 FEAT-1723: Support Readiness PID01/PID41
 *            2016-06-03  visade       ESCAN00090281 Mode 0x0A DTC which do not trigger the MIL yet after permanent memory activation
 *            2016-06-07  visanh       ESCAN00089775 SI30.5 is not set as expected
 *            2016-06-07  visanh       ESCAN00089619 Compiler warning: last line of file ends without a newline
 *            2016-06-07  visanh       ESCAN00089453 Compiler error: l-value specifies const object
 *            2016-06-07  visanh       ESCAN00089446 Monitor results are not processed
 *            2016-06-07  visanh       ESCAN00087975 OCC7 incorrect after reoccurrence of an aged DTC
 *            2016-06-08  visanh       ESCAN00090369 Add support for DM35
 *            2016-06-13  vismhe       ESCAN00090431 DTC is not stored during memory overflow
 *            2016-06-14  vismhe       ESCAN00090430 Module initialization fails
 *            2016-06-23  vismhe       ESCAN00090622 Aging counter incremented without test result
 *            2016-06-23  vismhe       ESCAN00090629 FEAT-1810: Adapt DCM and DEM to FCA Requirements
 *            2016-07-07  visanh       ESCAN00090874 Compiler warning: DEM_CFG_SUPPORT_NVM_POLLING undefined
 *  13.00.00  2016-10-25  viszfa       ESCAN00091941 OBD DTCs can't be displaced
 *            2017-01-11  viszfa       ESCAN00093510 Memory write access out of range
 *            2017-02-24  vismhe       ESCAN00091967 WIR status bit is reset for aged, but not healed DTC on ECU restart
 *            2017-02-24  visanh       FEAT-2212     SafeBSW for DEM
 *            2017-02-24  visejz       FEAT-2212     SafeBSW for DEM
 *            2017-02-24  vishrs       FEAT-2212     SafeBSW for DEM
 *            2017-02-24  vismhe       FEAT-2212     SafeBSW for DEM
 *            2017-02-24  viszfa       FEAT-2212     SafeBSW for DEM
 *            2017-02-24  visanh       FEAT-2212     Extend API to multiple satellites
 *            2017-02-24  visejz       FEAT-2212     Extend API to multiple satellites
 *            2017-02-24  vishrs       FEAT-2212     Extend API to multiple satellites
 *            2017-02-24  vismhe       FEAT-2212     Extend API to multiple satellites
 *            2017-02-24  viszfa       FEAT-2212     Extend API to multiple satellites
 *            2017-02-24  visanh       FEAT-2160     Rework Dcm interface to support parallel requests
 *            2017-02-24  visejz       FEAT-2160     Rework Dcm interface to support parallel requests
 *            2017-02-24  vishrs       FEAT-2160     Rework Dcm interface to support parallel requests
 *            2017-02-24  vismhe       FEAT-2160     Rework Dcm interface to support parallel requests
 *            2017-02-24  viszfa       FEAT-2160     Rework Dcm interface to support parallel requests
 *            2017-02-24  visavi       ESCAN00102117 Degradation in runtime performance including delayed processing of event reports
 *  13.01.00  2017-03-30  visavi       STORYC-446    Rework Dcm interface to support parallel requests 5 Verification
 *            2017-03-30  visfrs       STORYC-447    Rework Dcm interface to support parallel requests 9 Verification
 *            2017-03-30  visavi       STORYC-456    Rework Dcm interface to support parallel requests 6 Functional
 *            2017-03-30  vishrs       STORYC-459    Rework Dcm interface to support parallel requests 13 Functional
 *            2017-03-30  visavi       STORYC-468    Rework Dcm interface to support parallel requests 11 Verification
 *            2017-03-30  visfrs       STORYC-469    Rework Dcm interface to support parallel requests 12 Functional
 *            2017-03-30  visavi       STORYC-472    Rework Dcm interface to support parallel requests 5 Verification
 *            2017-03-30  visejz       STORYC-473    Rework Dcm interface to support parallel requests 9 Functional
 *            2017-03-30  vishrs       STORYC-474    Rework Dcm interface to support parallel requests 10 Functional
 *            2017-03-30  visanh       STORYC-475    Rework Dcm interface to support parallel requests 11 TechRef
 *            2017-03-30  visavi       STORYC-550    Rework Dcm interface to support parallel requests 6 Verification
 *            2017-04-05  visejz       ESCAN00094637 Suppressed DTCs reported by GetDTCbyOccurrenceTime
 *            2017-04-10  visejz       STORYC-448    Rework Dcm interface to support parallel requests 10 Verification
 *            2017-04-10  visfrs       STORYC-458    Rework Dcm interface to support parallel requests 8 Verification
 *            2017-04-11  visanh       STORYC-507    Extract time based de-bouncing Functional
 *            2017-04-11  vismhe       STORYC-232    Connect Protocol Handler to DEM
 *            2017-04-11  visejz       STORYC-510    Extract subcomponent Debounce Functional
 *            2017-04-11  vishrs       STORYC-512    Extract Subcomponent DTR Functional
 *            2017-04-10  visfrs       STORYC-555    Rework Dcm interface to support parallel requests 9 Verification
 *            2017-04-11  visejz       STORYC-513    Rework Dem_GetWIRStatus Functional
 *            2017-04-11  vishrs       ESCAN00099725 DTR Data might not be reported for some OBD MIDs
 *  13.02.00  2017-04-18  visanh       ESCAN00094549 FIM_E_WRONG_TRIGGER_ON_EVENT DET during initialization
 *            2017-04-20  visanh       ESCAN00094812 Compile error: Definition different from declaration
 *            2017-04-21  vishrs       STORYC-511    Extract subcomponent MonitorStatus Functional
 *            2017-04-24  vismhe       STORYC-514    Extract subcomponent event queue Functional
 *            2017-05-05  vishrs       STORYC-515    Extract subcomponent init state management Functional
 *  13.03.00  2017-05-22  vishrs       STORYC-994    Provide Dem_GetDTCSuppression API
 *            2017-05-22  vishrs       STORYC-752    Rework include of RTE files
 *            2017-06-06  visejz       STORYC-738    Extract subcomponent EventUds Functional
 *  13.04.00  2017-06-13  visanh       STORYC-222    Adapt DEM to FCA Requirements
 *            2017-06-14  visejz       STORYC-360    Add new API Dem_GetOperationCycleState
 *            2017-14-06  vissat       ESCAN00093466 Unexpected DET in Dem_DcmDisableDTCRecordUpdate
 *            2017-06-19  visanh       STORYC-361    Support indicator state CONT_BLINKING for OBD MIL
 *            2017-06-20  vissat       STORYC-721    Change SelectDTC to prohibit event selection during ongoing request Functional
 *            2017-06-28  vishrs       STORYC-1457   Extract subcomponent for SWC APIs for environmental data Functional
 *            2017-07-03  visanh       STORYC-1191   Extract subcomponent MemoryEntry Functional
 *  13.05.00  2017-07-10  vishrs       STORYC-1756   Support a component-specific SafeBSW configuration switch
 *            2017-07-15  vissat       STORYC-654    Extract subcomponent OperationCycle Functional
 *            2017-07-17  visejz       STORYC-651    Extract subcomponent UdsDtcStatus Functional
 *            2017-07-17  vishrs       STORYC-1519   Extract subcomponent Memory (part 1) Functional
 *            2017-07-19  visanh       STORYC-1538   Extract subcomponent NvM management Functional
 *  13.06.00  2017-08-04  vishrs       STORYC-1469   FCA CDDT Import for DEM
 *            2017-08-18  visejz       ESCAN00096295 Debounce data not persisted after manual NV synchronization
 *            2017-08-21  vissat       ESCAN00092216 PID 0x01: Incorrect calculation of bit B.4 and B.5
 *            2017-09-03  visavi       ESCAN00096492 Aging counter is incremented incorrectly
 *  13.06.01  2017-09-11  visavi       ESCAN00096546 Operation Cycle started twice
 *  14.00.00  2017-09-05  visanh       STORYC-1989   Upgrade J1939Dcm Interfaces in DEM
 *            2017-09-07  visavi       STORYC-2339   Reworked the Snapshot retrieval function in EnvDataSwcApi subcomponent
 *            2017-09-12  visanh       ESCAN00096549 DET check for DTCOrigin missing in API Dem_J1939DcmClearDTC
 *            2017-09-21  visanh       ESCAN00096826 Incorrect J1939 lamp status in DM31
 *  14.01.00  2017-10-05  visanh       STORYC-2640   Change DTR processing to fulfill SWS_Dem_01105
 *            2017-10-09  visanh       ESCAN00096945 Debounce data not persisted after manual NV synchronization
 *            2017-10-10  visanh       ESCAN00096960 CycleState is not stored in NvRam
 *            2017-10-10  visejz       STORYC-1318   Rework Similar Condition handlingfor multiple partitions
 *            2017-10-16  vismhe       ESCAN00097026 No response for service 19 06
 *            2017-10-16  visanh       ESCAN00097045 Dem_SetEventAvailable returns E_OK for events unavailable in variant
 *  14.02.00  2017-11-02  visanh       ESCAN00097267 PID 0x41: Incorrect calculation of comprehensive component monitoring, if major monitors are not supported
 *            2017-11-02  visanh       ESCAN00097254 Linker error: Fim_DemInit instead of FiM_DemInit is called
 *            2017-11-17  vissat       ESCAN00097201 DTC storing a Freeze Frame is not reported via OBDII Mode 02
 *            2017-11-20  visejz       STORYC-2340   Extract subcomponent Indicator Functional
 *            2017-11-20  visanh       ESCAN00097458 Compiler error: undefined symbol Dem_Event_GetTripCount
 *            2017-11-20  visanh       ESCAN00097474 Incorrect calculation of 'Cycles Tested Since Last Failed' and 'Healing Counter Inverted'
 *  14.03.00  2017-11-28  visanh       ESCAN00097584 Incorrect values for 'Cycles Tested Since Last Failed' and 'Healing Counter Inverted' returned
 *            2017-11-28  visanh       ESCAN00099810 Event heals to early after displacement (implicitly fixed with ESCAN00097584)
 *            2017-11-29  visanh       ESCAN00097595 Feature J1939 and Postbuild Loadable don't work together
 *            2017-11-30  vismhe       ESCAN00097339 Compiler warning: possible truncation at implicit conversion
 *            2017-11-30  vismhe       ESCAN00097564 Compiler error: Non defined function referenced in DEM Code
 *            2017-11-30  vismhe       ESCAN00097662 Configured ClearDTC finished notification does not occur
 *            2017-12-05  visejz       STORYC-1726   Add multi-partition support for freeze frame pre-storage
 *            2017-12-05  vismhe       ESCAN00097577 FreezeFrame is reported while no DTC is visible in modes 0x03 and 0x07
 *            2017-12-11  vismhe       ESCAN00097707 Unexpected DET during wakeup
 *            2017-12-11  vismhe       ESCAN00097712 Permanent DTC is not persisted into NV Ram
 *  14.04.00  2018-01-02  visanh       ESCAN00097699 Dem_SetWIRStatus is processed and returns E_OK for unavailable events
 *            2018-01-02  visanh       ESCAN00097848 Dem_GetWIRStatus returns E_OK for unavailable events
 *            2018-01-02  visanh       ESCAN00097849 Dem_GetEventEnableCondition returns E_OK for unavailable events
 *            2018-01-02  visanh       ESCAN00097850 Dem_GetEventAvailable returns AvailableStatus 'True' for events unavailable in variant
 *            2018-01-02  visanh       ESCAN00097852 Dem_GetCurrentIUMPRRatioDataAndDTC returns E_OK for unavailable/suppressed events
 *            2018-01-08  visanh       ESCAN00097884 DET check for pre-initialized satellite missing in Dem_SetEventStatus and Dem_ResetEventDebounceStatus
 *            2018-01-11  visanh       ESCAN00097932 Remove unused user defined switch DEM_CFG_AGING_START_CLEARS_OBD_FF
 *            2018-01-25  visanh       ESCAN00098143 WIR status bit of Black MIL DTC is reported, although driving cycle is not qualified
 *            2018-01-25  visanh       ESCAN00098142 Non OBD relevant DTC is not reported as confirmed
 *  14.05.00  2018-02-13  visanh       ESCAN00098374 Memory corruption during module initialization
 *            2018-02-13  visanh       ESCAN00099243 Compiler warning: 'Dem_Data_CopyStandardEnvData_Dag' declared, but never defined
 *            2018-02-14  vissat       ESCAN00098391 Compiler warning: Linker error/warning caused by usage of pointers to inline functions
 *            2018-02-15  visanh       ESCAN00098319 Compiler error: Non defined function(s) referenced in DEM Code
 *            2018-02-15  visanh       ESCAN00098311 Compiler error: Non defined function referenced in DEM Code
 *  14.06.00  2018-03-01  visanh       STORYC-4316   Fix several compile errors in new configurations
 *            2018-03-02  vishrs       ESCAN00098370 Dem calls monitor status change callbacks before Dem_Init
 *            2018-03-08  visanh       ESCAN00098637 Compiler error in configurations using DTRs without any event references
 *            2018-03-12  vissat       STORY-3042    Complete Silent Analysis
 *  15.00.00  2018-03-22  visanh       STORYC-4757   Fix several compile warnings in exotic configurations
 *  15.01.00  2018-04-16  visanh       ESCAN00098748 Similar conditions reported with pre-qualified monitor result not considered for events with time-based de-bouncing
 *            2018-04-17  visanh       ESCAN00098659 Permanent entry of combined event is cleared at initialization of Dem
 *            2018-04-18  visfrs       ESCAN00098660 Cycles since first failed is not latched at 255
 *            2018-04-25  visfrs       ESCAN00098186 Compiler error in configurations with certain aging behavior types
 *            2018-04-30  visanh       ESCAN00098183 DTCStatusOld in DTCStatusChanged callbacks wrong for OBD relevant DTCs
 *            2018-05-03  visanh       ESCAN00099302 Driving cycle qualification is not considered in EventStatusChanged callbacks
 *            2018-05-04  vishrs       ESCAN00099171 Value of 'Cycles Since First Failed' is 0
 *  15.02.00  2018-05-15  visanh       ESCAN00098626 Incorrect calculation of 'Cycles Tested Since Last Failed' for healing target 0
 *            2018-05-16  vishrs       ESCAN00098596 Combined event is not stored, during Storage Retry after Storage Conditions are fulfilled
 *            2018-05-17  vishrs       ESCAN00099241 Compiler warning: 'Dem_Cfg_FindGroupMaskFromUdsDtc' declared but never defined
 *            2018-06-05  visanh       ESCAN00099298 Missing safety manual item for ClearDTC notification function pointers
 *            2018-06-05  visanh       ESCAN00099490 Missing safety manual item for J1939 DTC Status Changed notification function pointers
 *  15.03.00  2018-06-13  visavi       ESCAN00099487 Supported OBD MIDs in response message of Service 06 are reported in the wrong order
 *            2018-06-22  visejz       ESCAN00099227 Healing of event continues despite pre-confirmation
 *            2018-06-27  visavi       ESCAN00099383 Failure to collect data via Client/Server or Sender/Receiver R-Port results in random data
 *            2018-07-02  visfrs       ESCAN00099748 Completeness of PID01 Comprehensive Component Monitoring is reported incomplete.
 *  15.04.00  2018-07-17  visanh       STORYC-5589   Provide OBD Dem Autosar 4.3 IUMPR Groups
 *            2018-07-24  visavi       STORYC-5370   Extract subcomponent Memory Functional
 *            2018-07-30  visejz       STORYC-5849   Adapt DEM Interface for Initialization
 *  15.05.00  2018-08-10  visfrs       ESCAN00099789 Undefined behaviour: Satellite Status not initialized during RAM initialization
 *            2018-08-10  visfrs       ESCAN00100047 Consecutive failed cycle counter not persisted to NvRAM
 *            2018-08-07  visavi       STORYC-5368   Extract subcomponent MemState Functional
 *            2018-08-16  visavi       STORYC-5364   Extract subcomponent MemStorageManager Functional
 *            2018-08-21  visfrs       STORYC-2206   Extract subcomponent Notifications Functional
 *            2018-08-21  visfrs       ESCAN00100432 First clear request after NvM error is responded with CLEAR_MEMORY_ERROR
 *  15.06.00  2018-08-27  visejz       STORYC-5366   Extract subcomponent MemAccess Functional
 *  16.00.00  2018-09-12  visfrs       STORYC-4763   DEM: Support suppressed DTCs in response of service 19x0A
 *            2018-09-20  visejz       ESCAN00100732 Dem_DisableDTCRecordUpdate is not processed
 *            2018-09-21  visejz       ESCAN00100778 Suppressed DTCs are reported in UDS service 0x19 subfunction 0x15
 *            2018-09-24  visejz       STORYC-5932:  Extract subcomponent Memory Functional 2
 *            2018-09-25  visejz       ESCAN00100584 Dem doesn't return DEM_CLEAR_FAILED although all ClearEventAllowed callbacks return FALSE
 *            2018-09-26  visfrs       ESCAN00100537 Not qualified OBD Driving Cycle is restarted
 *  16.01.00  2018-09-26  visavi       STORYC-1548   Extract subcomponent Statistics Functional
 *            2018-10-01  visanh       ESCAN00100903 Compiler warning: last line of Dem_EnableCondition_Interface.h ends without a newline
 *            2018-10-01  visanh       ESCAN00100904 Compiler warning: last line of Dem_Cfg_Definitions.h ends without a newline
 *            2018-10-01  visanh       ESCAN00100905 Compiler warning: last line of Dem_MemState_Implementation.h ends without a newline
 *            2018-10-04  visejz       STORYC-4794   Support "Fault Pending Counter"
 *            2018-10-11  visejz       STORYC-6249   Improve recovery for stored EventIds in NvRAM blocks
 *            2018-10-16  vissat       ESCAN00101027 Stack Usage of Dem functions too high
 *  16.02.00  2018-10-25  visavi       STORYC-4762   Support Storage of Global Snapshot Record
 *            2018-11-14  visejz       STORYC-6782   [OBD] Use oldest Confirmed DTC, after PDTC memory gets freed
 *  16.03.00  2018-12-04  visejz       ESCAN00101111 Dem returns invalid OBD Freeze Frame data when read out through Application API
 *            2018-12-18  visavi       STORYC-6793   Make aging in Dem compliant to 1968.2, Support aging independent of memory entry
 *            2018-12-19  visavi       ESCAN00101179 Dem returns invalid OBD Freeze Frame data during UDS Service 19 05 and OBD Mode 02
 *  16.04.00  2019-01-08  visejz       STORYC-4761   Support "Aged Counter"
 *  16.05.00  2019-01-08  visavi       STORYC-7342   Included improvements in aging performance
 *            2019-01-22  visejz       STORYC-4797   Support Reading of Global Snapshot Record
 *            2019-01-31  visfrs       ESCAN00101934 OBD Freeze Frame of an event without memory entry is not cleared on aging
 *            2019-02-05  visfrs       ESCAN00101407 OBD freeze frame of major monitor events (misfire & fuel system monitors) do not displace existing OBD freeze frames.
 *            2019-02-12  visfrs       STORY-10500   Adapt behavior of service 19 05 to be consistent with Obd mode 02
 *  16.06.00  2019-02-27  visejz       STORYC-7660   Support Reading of Global Snapshot Record (2)
 *            2019-03-04  vissat       ESCAN00101665 Dem returns invalid OBD Freeze Frame data during UDS Service 19 04
 *            2019-03-05  visavi       ESCAN00101894 Fuel System Monitoring Ready (bit B.5) in PID 0x01 is incorrectly reported as complete.
 *            2019-03-06  visejz       ESCAN00101907 Undefined behaviour due to memory access violation
 *            2019-03-12  visavi       ESCAN00102295 Incorrect configuration of DEM Aging Behavior
 *  17.00.00  2019-03-20  visavi       ESCAN00101969 The 500-Mile denominator can only be incremented if the general denominator conditions are reached in the same driving cycle
 *            2019-03-08  visejz       STORYC-7436   Support DEM_TRIGGER_ON_FDC_THRESHOLD
 *            2019-03-29  visfrs       ESCAN00102478 API Dem_SetIUMPRDenCondition() returns E_OK even if IUMPR denominator condition status is not accepted.
 *            2019-04-03  visavi       ESCAN00101792 PID 0x41: Incorrect calculation of bit B.4 and B.5
 *  17.01.00  2019-04-23  visern       ESCAN00102696 Removed float32 type usages for configurations without DTR support.
 *            2019-04-29  visejz       STORYC-8203   Support DEM_TRIGGER_ON_PASSED
 *            2019-05-06  visfrs       STORY-11911   Support of immediate Permanent DTC availability via OBD mode 0A
 *  17.02.00  2019-05-20  visejz       ESCAN00103098 Incorrect status changed notifications and ReponseOnEvents (UDS Service 0x86 0x01)
 *            2019-05-20  visejz       STORY-11909   Support DEM_TRIGGER_ON_CONFIRMED
 *            2019-05-24  vissat       ESCAN00103242 Compiler warning: Dem_MainFunction<Timer|Worker> declared but never defined
 *            2019-05-29  visavi       STORY-9550    Support recoverableInSameOperationCycle Flag
 *  17.03.00  2019-06-13  visavi       ESCAN00102751 Incorrect behavior of API Dem_ResetEventDebounceStatus for events using monitor internal debouncing
 *            2019-06-14  visejz       ESCAN00103065 Event is stored in memory although memory entry storage trigger is not reached
 *            2019-06-14  visejz       ESCAN00103058 Event data stored/updated although storage trigger did not re-occur
 *            2019-06-17  vissat       ESCAN00103296 DTC Status of supressed DTC is wrong in response of Service 19 0A
 *            2019-06-27  visejz       ESCAN00102806 Ignition cycle counter for hybrids is not locked through pending fault code.
 *            2019-06-27  visern       ESCAN00103404 Remove usage of __FILE__ Preprocessor macro from source code
 *            2019-06-28  visern       ESCAN00102833 OBD Freeze Frame erroneously cleared at initialization if associated event not stored
 *            2019-07-02  visfrs       ESCAN00103565 Compiler error: Implicit conversion from 'float' to 'double'
 *  17.04.00  2019-07-08  visern       ESCAN00103179 User defined environmental data is not persisted immediately to NvRam
 *            2019-07-11  visern       ESCAN00103357 OBD Driving Cycle Status incorrectly synchronized to non-volatile memory
 *            2019-07-17  vissat       ESCAN00103543 Memory corruption when clearing or updating prestored Freeze Frame
 *            2019-07-18  visavi       DEM-148       DTC Selection for Event Combination Type 2
 *            2019-07-18  visejz       DEM-22        Suppression for Event Combination Type 2
 *            2019-07-29  visejz       ESCAN00103749 Endless loop during initialization using Freeze Frame Prestorage feature
 *  17.05.00  2019-08-06  visern       DEM-789       ClearDTC for Event Combination Type 2
 *            2019-08-08  vissat       ESCAN00103590 Compiler error and warnings if number of global NvRAM blocks is configured larger than 255
 *            2019-08-12  visavi       DEM-3478      Adapt DEM so that Aging and Displacement works for Event Combination Type 2
 *            2019-08-28  visavi       ESCAN00103957 The API Dem_ClearDTC() returns DEM_PENDING indefinitely
 *  18.00.00  2019-08-30  visern       DEM-558       DTC Filtering for Event Combination Type 2
 *            2019-09-04  vissat       ESCAN00103808 Suppressed DTCs  reported in UDS service 0x19 subfunction 0x05, OBD Mode 02
 *            2019-09-12  visavi       DEM-103       Support reading of snapshot data for event combination type 2
 *            2019-09-17  visavi       ESCAN00104148 Aging counter is incremented twice during DEM restart sequence
 *            2019-09-18  visera       ESCAN00103966 Wrong PID30 counting policy
 *            2019-09-16  visejz       DEM-149       Support Permanent Memory for WWHOBD
 *  18.01.00  2019-10-01  visejz       DEM-3636      Support Permanent Memory for WWHOBD (Feature completed)
 *            2019-10-10  visavi       ESCAN00104568 The API Dem_SelectDTC() returns E_NOT_OK after Dem_ClearDTC() is invoked
 *            2019-10-14  vissat       ESCAN00104508 Compiler error: Function was referenced but not defined
 *            2019-10-15  vissat       ESCAN00104535 Memory corruption due to incorrectly defined function pointer prototype
 *            2019-10-17  visejz       DEM-3709      Support DemDataElementClass Multiplicity 65534
 *  18.02.00  2019-10-23  visera       ESCAN00104559 Inconsistent state when configuration changes and API Dem_NvM_InitAdminData() is called
 *            2019-10-28  vissat       DEM-133       Support Reading Extended Data Records for Event Combination Type 2
 *            2019-10-28  visejz       DEM-63        Support for OBDII Permanent Memory for Event Combination Type 2
 *            2019-10-30  visern       DEM-3758      Support for UDS Service 19 03 (reading stored snapshot record numbers) for Event Combination Type 2
 *            2019-11-06  visfrs       DEM-129       Support for OBDII Major-Monitor PIDs for Event Combination Type 2
 *            2019-11-14  visfrs       DEM-3736      Support Availability for snapshot readout for Event Combination Type 2
 *            2019-11-15  visern       ESCAN00104233 Diagnostic Test Result handling for signed UnitandScalingID does not allow negative values.
 *  18.03.00  2019-11-27  visern       DEM-1611      Support for IUMPR General Individual Denominator Conditions and IUMPR General OBD Denominator Conditions.
 *            2019-11-29  visern       DEM-3832      Support for Additional Denominator Conditions to fulfill before General Denominator Conditions.
 *            2019-12-05  vissko       DEM-3864      Improve internal structure of Dem_Satellite
 *  18.04.00  2019-12-13  visera       ESCAN00104901 Monitor Status Bits of an Event with a latched Test Failed Bit deviate from its respective UDS Status Bits
 *            2020-01-08  visavi       ESCAN00105268 Dem reports Det error and becomes unoperative when an event fulfills aging start condition
 *            2020-01-10  visern       DEM-2795      Extract subcomponent IUMPR
 *  18.05.00  2020-01-20  visejz       DEM-3902      Refactor Satellite - Remove Preprocessor Switches
 *            2020-01-24  visern       DEM-4005      Refactor Iumpr - Remove Preprocessor Switches
 *            2020-01-27  visavi       DEM-3902      Refactor Satellite - Remove Preprocessor Switches
 *            2020-01-31  visera       ESCAN00105211 Aging is not stopped with failed report with unfulfilled storage conditions
 *            2020-02-03  vissat       ESCAN00105527 Compiler Error: last line of Dem_DTCReadoutBuffer_Types.h ends without a newline
 *            2020-02-03  visavi       ESCAN00105311 PID 41: Monitor status is set to completed when monitor is disabled 
 *            2020-02-07  visern       DEM-4005      Redesign of subcomponent IUMPR 
 *  18.06.00  2020-02-21  visxli       ESCAN00105547 Dem calls monitor initialization notification with reason monitor restart at the end of an operation cycle
 *            2020-02-26  visern       DEM-4009      Support for MISRA-C:2012 
 *            2020-03-02  vissko       ESCAN00105661 A previously reported 500 mile denominator is not increased with the general individual denominator conditions reached report
 *            2020-03-03  visejz       ESCAN00105705 Time series snapshot record sampling rate overflow
 *            2020-03-03  visejz       ESCAN00105717 Engine Runtime Polling rate overflow
 *  19.00.00  2020-03-09  visfrs       ESCAN00105373 No OBD FreezeFrame available via Mode 02 after 0-Trip Event is confirmed
 *            2020-03-19  visfrs       ESCAN00105872 Compiler error: error C4668: 'FIM_CFG_USE_RTE' is not defined
 *            2020-03-23  vissat       ESCAN00105919 DEM writes behind a null pointer when the generated dynamic files are inconsistent
 *  19.01.00  2020-04-01  visavi       DEM-79        Make DEM Satellite usable in ASIL partition for partitioning solution
 *            2020-04-06  visejz       DEM-3743      ExtendedDataRecord readable without event storage
 *            2020-04-07  visera       ESCAN00105824 IUMPR numerator is not incremented with qualified test result before full initialization.
 *  19.02.00  2020-04-09  vissko       DEM-4268      IUMPR Denominator without dependency to the general individual denominator
 *  19.02.01  2020-04-21  visern       DEM-4277      Replace SMI with MSSV Plugin
 *            2020-04-22  visern       DEM-4328      Removed unused functions to complete function coverage
 *  19.03.00  2020-04-28  visfrs       DEM-4041      Support J1939Dcm DM01 parallel to Dem with OBD-II Addon
 *            2020-05-04  visern       DEM-4080      IUMPR decoupling of conditions from ratios
 *  19.04.00  2020-05-12  visern       DEM-4455      IUMPR ConditionStatus and OperationCycle interface restructure
 *            2020-05-13  visera       DEM-128       Improve Recovery of Event Status
 *            2020-05-19  visern       DEM-4420      Improve Recovery of AgingCounter
 *            2020-05-25  visfrs       DEM-4432      Support multiple special indicators for one DTC
 *            2020-05-27  visanh       ESCAN00106278 Dem writes Event Entry Block to NVRAM although data did not change
 *  19.05.00  2020-06-05  visera       DEM-4337      Implement runtime limiter for J1939 Diagnostic Messages in DEM
 *            2020-06-09  visxli       ESCAN00105691 DTC or DTC Group not Cleared despite positive response
 *            2020-06-18  visxli       ESCAN00106496 Reporting qualified 'failed' is not processed after warm start
 *  19.06.00  2020-07-03  vissat       DEM-4681      Remove Compiler Validation for OBD2 with J1939
 *            2020-07-06  vsarcsiiv    CARC-411      Add support for number Of WarmUp cycles since last failed
 *            2020-07-14  visern       ESCAN00106656 Dem invokes InitMonitor callbacks before the operation cycle is internally started    
 *            2020-07-17  visanh       DEM-4512      Post-build Selectable for non-OBD/OBD II/WWH-OBD/CN6
 *            2020-07-28  visavi       ESCAN00106975 Missing safety manual item regarding array containing address of Dem memory entries
 *  19.07.00  2020-08-05  visanh       DEM-4748      Remove Global Justifications 3453, 3458 and 3679
 *            2020-08-11  visavi       ESCAN00106939 Lost Diagnostic Data after ECU Shutdown and Initialization
 *            2020-08-11  visern       DEM-130       Implement service 0x19 sub-function 0x16 of ReadDTCInformation as a Dcm internal service
 *  20.00.00  2020-09-02  visejz       ESCAN00107271 Compiler Warning: Conversion from Dem_Cfg_MemoryIndexIterType to Dem_Cfg_MemoryIndexType, possible loss of data
 *            2020-09-08  visern       DEM-4772      Implement service 0x19 sub-function 0x56 of ReadDTCInformation by Readiness Group
 *            2020-09-09  vsarcsiiv    CARC-477      Implement StatusIndicator30 feature
 *            2020-09-18  visern       ESCAN00107268 Extended data updated twice in the same operation cycle although trigger FDC First in Cycle is configured
 *            2020-07-15  visfrs       ESCAN00106517 IUMPR Numerator and Denominator are not incremented correctly
 *  20.01.00  2020-10-21  visern       DEM-4773      Prepare implementation to support OBD on UDS Subfunction 0x1A of Service 0x19 
 *  20.02.00  2020-10-27  visejz       DEM-4128      DEM III: Storage of powertrain Multi Sample Snapshot
 *            2020-11-06  visern       DEM-4410      Extended service 0x19 sub-function 0x03 with readout of powertrain TimeSeries data
 *            2020-11-10  vsarcmiem    CARC-626      Implement service 0x19 sub-function 1A
 *            2020-11-10  vissko       DEM-5220      Support immediate OBD DTC visibility independent of trip target
 *  20.03.00  2020-11-20  visxli       DEM-5157      Virtual Buffer for Multi-sample development snapshot records
 *            2020-11-20  visavi       DEM-4386      DEM V: Readout of powertrain Multi Sample Snapshot through 0x19-04
 *            2020-11-24  haelvero     CARC-693      Add recovery for StatusIndicator30 feature
 *            2020-11-25  visejz       ESCAN00107999 Compiler error: Incompatible type assigned to a function pointer
 *  20.04.00  2020-12-15  visejz       DEM-5307      Remove OEM names from code
 *            2020-12-11  visern       DEM-5310      Renamed OEM compiler switches
 *            2020-12-14  visxli       ESCAN00107528 Time Series Snapshot Record not readable from multiple clients in parallel.
 *            2020-12-18  haelvero     CARC-829      Trigger passed for configured Snapshot Records
 *            2020-12-22  visavi       ESCAN00108208 Compiler error: Parse error  near 'Dem_StatusIndicator_Type'
 *            2020-12-23  visavi       ESCAN00108197 Dem APIs used for Service 0x19-04 respond incorrectly while reading Time Series Snapshot Record
 *            2021-01-07  vireno       ESCAN00108009 Incorrect Aging Counter reported for DTCs that are configured not allowed to age.
 *            2021-01-08  visxli       ESCAN00108154 Incorrect data reported in service 0x19 sub-function 0x04 when reading multi-sample snapshot record 0x30
 *            2021-01-12  visera       Dem-5362      Improve traceability of OEM specific code parts
 *  20.05.00  2021-01-19  visern       DEM-5411      Improved Filter Data handling efficiency.
 *            2021-01-21  visern       ESCAN00100513 Compiler error: Missing Parameter in API Dem_DcmGetDTCOfOBDFreezeFrame
 *            2021-01-27  visern       ESCAN00108379 Compiler error: Wrong Parameter Type in API Dem_DcmReadDataOfOBDFreezeFrame
 *            2021-01-29  visrk        DEM-4275      Reduce complexity and stack usage of Event Record Read
 *            2021-02-01  visern       ESCAN00108244 Displacement fallback strategy does not select an event/time series entry to displace
 *            2021-02-03  visera       ESCAN00108365 Incorrect description of IUMPR APIs in Embedded Code
 *  20.06.00  2021-02-12  visavi       DEM-5356      Apply updated include structure to DEM
 *            2021-02-15  visxli       ESCAN00108502 Compiler warning: Possible loss of data due to incorrect conversion from uint16_least to uint16
 *            2021-02-15  visxli       ESCAN00108503 Compiler warning: Possible loss of data due to incorrect conversion from uint16_least to uint16
 *            2021-02-18  visavi       DEM-5542      Remove implementation from Logical Units
 *            2021-02-22  visejz       ESCAN00108633 Compiler error: parse error near uint32
 *            2021-02-23  visern       ESCAN00108453 Wrong value reported for occurrence counter after successful "retry storage"
 *            2021-02-23  visern       ESCAN00108621 Memory corruption while invoking API Dem_GetEventFreezeFrameDataEx()
 *            2021-02-25  visejz       DEM-5398      Internal reorganization of public service APIs
 *            2021-03-09  visavi       ESCAN00108775 DEM Main Function runs in an endless loop. 
 *********************************************************************************************************************/

#if !defined (DEM_H)                                                                                                             /* COV_MSR_HEADERGUARD TX */
#define DEM_H


/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "SchM_Dem.h" /* Patch, Avoid compiler warninigs */
                                     /* Dem public types, defined statically */
/* ------------------------------------------------------------------------- */
#include "Dem_Types.h"
/* ------------------------------------------------------------------------- */

                                                       /* Configuration data */
/* ------------------------------------------------------------------------- */
#include "Dem_Lcfg.h"
#include "Dem_PBcfg.h"
/* ------------------------------------------------------------------------- */

                                                       /* Subcomponent types */
/* ------------------------------------------------------------------------- */
#include "Dem_Cfg_Types.h"
#include "Dem_Cfg_Macros.h"
/* ------------------------------------------------------------------------- */


                                          /* Static configuration validation */
/* ------------------------------------------------------------------------- */
#include "Dem_Validation.h"
/* ------------------------------------------------------------------------- */



/* ********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

                                                      /* Version information */
/* ------------------------------------------------------------------------- */

/* vendor and module identification - decimal encoding */
#define DEM_VENDOR_ID                            (30U)
#define DEM_MODULE_ID                            (54U)
#define DEM_INSTANCE_ID                          (0U)

/* AUTOSAR Software Specification Version Information - decimal encoding */
#define DEM_AR_RELEASE_MAJOR_VERSION             (4U)
#define DEM_AR_RELEASE_MINOR_VERSION             (3U)
#define DEM_AR_RELEASE_REVISION_VERSION          (0U)

/* Component Version Information - decimal encoding */
#define DEM_SW_MAJOR_VERSION                     (20U)
#define DEM_SW_MINOR_VERSION                     (6U)
#define DEM_SW_PATCH_VERSION                     (0U)


                                                                  /* API Ids */
/* ------------------------------------------------------------------------- */
#define DEM_GETVERSIONINFO_APIID                          (0x00U)              /*< Service ID: Dem_GetVersionInfo() */
#define DEM_PREINIT_APIID                                 (0x01U)              /*< Service ID: Dem_PreInit() */
#define DEM_INIT_APIID                                    (0x02U)              /*< Service ID: Dem_Init() */
#define DEM_SHUTDOWN_APIID                                (0x03U)              /*< Service ID: Dem_Shutdown() */
#define DEM_SETEVENTSTATUS_APIID                          (0x04U)              /*< Service ID: Dem_SetEventStatus() */
#define DEM_RESETEVENTSTATUS_APIID                        (0x05U)              /*< Service ID: Dem_ResetEventStatus() */
#define DEM_PRESTOREFREEZEFRAME_APIID                     (0x06U)              /*< Service ID: Dem_PrestoreFreezeFrame() */
#define DEM_CLEARPRESTOREDFREEZEFRAME_APIID               (0x07U)              /*< Service ID: Dem_ClearPrestoredFreezeFrame() */
#define DEM_SETOPERATIONCYCLESTATE_APIID                  (0x08U)              /*< Service ID: Dem_SetOperationCycleState() */
#define DEM_RESETEVENTDEBOUNCESTATUS_APIID                (0x09U)              /*< Service ID: Dem_ResetEventDebounceStatus() */
#define DEM_GETEVENTUDSSTATUS_APIID                       (0x0aU)              /*< Service ID: Dem_GetEventUdsStatus() */
#define DEM_GETEVENTFAILED_APIID                          (0x0bU)              /*< Service ID: Dem_GetEventFailed() */
#define DEM_GETEVENTTESTED_APIID                          (0x0cU)              /*< Service ID: Dem_GetEventTested() */
#define DEM_GETDTCOFEVENT_APIID                           (0x0dU)              /*< Service ID: Dem_GetDTCOfEvent() */
#define DEM_GETSEVERITYOFDTC_APIID                        (0x0eU)              /*< Service ID: Dem_GetSeverityOfDTC() */
#define DEM_REPORTERRORSTATUS_APIID                       (0x0fU)              /*< Service ID: Dem_ReportErrorStatus() */
#define DEM_SETAGINGCYCLESTATE_APIID                      (0x11U)              /*< Service ID: Dem_SetAgingCycleState() */
#define DEM_SETAGINGCYCLECOUNTERVALUE_APIID               (0x12U)              /*< Service ID: Dem_SetAgingCounterValue() */
#define DEM_SETDTCFILTER_APIID                            (0x13U)              /*< Service ID: Dem_SetDTCFilter() */
#define DEM_GETSTATUSOFDTC_APIID                          (0x15U)              /*< Service ID: Dem_GetStatusOfDTC() */
#define DEM_GETDTCSTATUSAVAILABILITYMASK_APIID            (0x16U)              /*< Service ID: Dem_GetDTCStatusAvailabilityMask() */
#define DEM_GETNUMBEROFFILTEREDDTC_APIID                  (0x17U)              /*< Service ID: Dem_DcmGetNumberOfFilteredDTC() */
#define DEM_GETNEXTFILTEREDDTC_APIID                      (0x18U)              /*< Service ID: Dem_DcmGetNextFilteredDTC() */
#define DEM_GETDTCBYOCCURRENCETIME_APIID                  (0x19U)              /*< Service ID: Dem_GetDTCByOccurrenceTime() */
#define DEM_DISABLEDTCRECORDUPDATE_APIID                  (0x1aU)              /*< Service ID: Dem_DisableDTCRecordUpdate() */
#define DEM_ENABLEDTCRECORDUPDATE_APIID                   (0x1bU)              /*< Service ID: Dem_EnableDTCRecordUpdate() */
#define DEM_DCMGETOBDFREEZEFRAMEDATA_APIID                (0x1cU)              /*< Service ID: Dem_DcmGetOBDFreezeFrameData() */
#define DEM_GETNEXTFREEZEFRAMEDATA_APIID                  (0x1dU)              /*< Service ID: Dem_GetNextFreezeFrameData() */
#define DEM_GETSIZEOFFREEZEFRAMESELECTION_APIID           (0x1fU)              /*< Service ID: Dem_GetSizeOfFreezeFrameSelection() */
#define DEM_GETNEXTEXTENDEDDATARECORD_APIID               (0x20U)              /*< Service ID: Dem_GetNextExtendedDataRecord() */
#define DEM_GETSIZEOFEXTENDEDDATARECORDSELECTION_APIID    (0x21U)              /*< Service ID: Dem_GetSizeOfExtendedDataRecordSelection() */
#define DEM_CLEARDTC_APIID                                (0x23U)              /*< Service ID: Dem_ClearDTC() */
#define DEM_DISABLEDTCSETTING_APIID                       (0x24U)              /*< Service ID: Dem_DisableDTCSetting() */
#define DEM_ENABLEDTCSETTING_APIID                        (0x25U)              /*< Service ID: Dem_EnableDTCSetting() */
#define DEM_GETINDICATORSTATUS_APIID                      (0x29U)              /*< Service ID: Dem_GetIndicatorStatus() */
#define DEM_GETEVENTMEMORYOVERFLOW_APIID                  (0x32U)              /*< Service ID: Dem_GetEventMemoryOverflow() */
#define DEM_SETDTCSUPPRESSION_APIID                       (0x33U)              /*< Service ID: Dem_SetDTCSuppression() */
#define DEM_GETFUNCTIONALUNITOFDTC_APIID                  (0x34U)              /*< Service ID: Dem_GetFunctionalUnitOfDTC() */
#define DEM_GETNUMBEROFEVENTMEMORYENTRIES_APIID           (0x35U)              /*< Service ID: Dem_GetNumberOfEventMemoryEntries() */
#define DEM_SETEVENTAVAILABLE_APIID                       (0x37U)              /*< Service ID: Dem_SetEventAvailable() */
#define DEM_SETSTORAGECONDITION_APIID                     (0x38U)              /*< Service ID: Dem_SetStorageCondition() */
#define DEM_SETENABLECONDITION_APIID                      (0x39U)              /*< Service ID: Dem_SetEnableCondition() */
#define DEM_GETNEXTFILTEREDRECORD_APIID                   (0x3aU)              /*< Service ID: Dem_GetNextFilteredRecord() */
#define DEM_GETNEXTFILTEREDDTCANDFDC_APIID                (0x3bU)              /*< Service ID: Dem_DcmGetNextFilteredDTCAndFDC() */
#define DEM_GETTRANSLATIONTYPE_APIID                      (0x3cU)              /*< Service ID: Dem_GetTranslationType() */
#define DEM_GETNEXTFILTEREDDTCANDSEVERITY_APIID           (0x3dU)              /*< Service ID: Dem_DcmGetNextFilteredDTCAndSeverity() */
#define DEM_GETFAULTDETECTIONCOUNTER_APIID                (0x3eU)              /*< Service ID: Dem_GetFaultDetectionCounter() */
#define DEM_SETFREEZEFRAMERECORDFILTER_APIID              (0x3fU)              /*< Service ID: Dem_SetFreezeFrameRecordFilter() */
#define DEM_SETEVENTDISABLED_APIID                        (0x51U)              /*< Service ID: Dem_SetEventDisabled() */
#define DEM_DCMREADDATAOFOBDFREEZEFRAME_APIID             (0x52U)              /*< Service ID: Dem_DcmReadDataOfOBDFreezeFrame() */
#define DEM_DCMGETDTCOFOBDFREEZEFRAME_APIID               (0x53U)              /*< Service ID: Dem_DcmGetDTCOfOBDFreezeFrame() */
#define DEM_MAINFUNCTION_APIID                            (0x55U)              /*< Service ID: Dem_MainFunction() */
#define DEM_DCMREADDATAOFPID01_APIID                      (0x61U)              /*< Service ID: Dem_DcmReadDataOfPID01() */
#define DEM_DCMREADDATAOFPID1C_APIID                      (0x63U)              /*< Service ID: Dem_DcmReadDataOfPID1C() */
#define DEM_DCMREADDATAOFPID21_APIID                      (0x64U)              /*< Service ID: Dem_DcmReadDataOfPID21() */
#define DEM_DCMREADDATAOFPID30_APIID                      (0x65U)              /*< Service ID: Dem_DcmReadDataOfPID30() */
#define DEM_DCMREADDATAOFPID31_APIID                      (0x66U)              /*< Service ID: Dem_DcmReadDataOfPID31() */
#define DEM_DCMREADDATAOFPID41_APIID                      (0x67U)              /*< Service ID: Dem_DcmReadDataOfPID41() */
#define DEM_DCMREADDATAOFPID4D_APIID                      (0x68U)              /*< Service ID: Dem_DcmReadDataOfPID4D() */
#define DEM_DCMREADDATAOFPID4E_APIID                      (0x69U)              /*< Service ID: Dem_DcmReadDataOfPID4E() */
#define DEM_DCMREADDATAOFPID91_APIID                      (0x6aU)              /*< Service ID: Dem_DcmReadDataOfPID91() */
#define DEM_GETEVENTEXTENDEDDATARECORDEX_APIID            (0x6dU)              /*< Service ID: Dem_GetEventExtendedDataRecordEx() */
#define DEM_GETEVENTFREEZEFRAMEDATAEX_APIID               (0x6eU)              /*< Service ID: Dem_GetEventFreezeFrameDataEx() */
#define DEM_REPIUMPRDENLOCK_APIID                         (0x71U)              /*< Service ID: Dem_RepIUMPRDenLock() */
#define DEM_REPIUMPRDENRELEASE_APIID                      (0x72U)              /*< Service ID: Dem_RepIUMPRDenRelease() */
#define DEM_REPIUMPRFAULTDETECT_APIID                     (0x73U)              /*< Service ID: Dem_RepIUMPRFaultDetect() */
#define DEM_SETWIRSTATUS_APIID                            (0x7aU)              /*< Service ID: Dem_SetWIRStatus() */
#define DEM_J1939DCMSETDTCFILTER_APIID                    (0x90U)              /*< Service ID: Dem_J1939DcmSetDTCFilter() */
#define DEM_J1939DCMGETNUMBEROFFILTEREDDTC_APIID          (0x91U)              /*< Service ID: Dem_J1939DcmGetNumberOfFilteredDTC() */
#define DEM_J1939DCMGETNEXTFILTEREDDTC_APIID              (0x92U)              /*< Service ID: Dem_J1939DcmGetNextFilteredDTC() */
#define DEM_J1939DCMFIRSTDTCWITHLAMPSTATUS_APIID          (0x93U)              /*< Service ID: Dem_J1939DcmFirstDTCWithLampStatus() */
#define DEM_J1939DCMGETNEXTDTCWITHLAMPSTATUS_APIID        (0x94U)              /*< Service ID: Dem_J1939DcmGetNextDTCWithLampStatus() */
#define DEM_J1939DCMCLEARDTC_APIID                        (0x95U)              /*< Service ID: Dem_J1939DcmClearDTC() */
#define DEM_J1939DCMSETFREEZEFRAMEFILTER_APIID            (0x96U)              /*< Service ID: Dem_J1939DcmSetFreezeFrameFilter() */
#define DEM_J1939DCMGETNEXTFREEZEFRAME_APIID              (0x97U)              /*< Service ID: Dem_J1939DcmGetNextFreezeFrame() */
#define DEM_J1939DCMGETNEXTSPNINFREEZEFRAME_APIID         (0x98U)              /*< Service ID: Dem_J1939DcmGetNextSPNInFreezeFrame() */
#define DEM_J1939DCMREADDIAGNOSTICREADINESS1_APIID        (0x9bU)              /*< Service ID: Dem_J1939DcmReadDiagnosticReadiness1() */
#define DEM_GETOPERATIONCYCLESTATE_APIID                  (0x9eU)              /*< Service ID: Dem_GetOperationCycleState() */
#define DEM_GETDEBOUNCINGOFEVENT_APIID                    (0x9fU)              /*< Service ID: Dem_GetDebouncingOfEvent() */
#define DEM_SETDTR_APIID                                  (0xa2U)              /*< Service ID: Dem_SetDTR() */
#define DEM_DCMGETAVAILABLEOBDMIDS                        (0xa3U)              /*< Service ID: Dem_DcmGetAvailableOBDMIDs() */
#define DEM_DCMGETNUMTIDSOFOBDMID                         (0xa4U)              /*< Service ID: Dem_DcmGetNumTIDsOfOBDMID() */
#define DEM_DCMGETDTRDATA                                 (0xa5U)              /*< Service ID: Dem_DcmGetDTRData() */
#define DEM_SETPFCCYCLEQUALIFIED_APIID                    (0xaaU)              /*< Service ID: Dem_SetPfcCycleQualified() */
#define DEM_GETPFCCYCLE_APIID                             (0xabU)              /*< Service ID: Dem_GetPfcCycle() */
#define DEM_SETIUMPRDENCONDITION_APIID                    (0xaeU)              /*< Service ID: Dem_SetIUMPRDenCondition() */
#define DEM_GETDTCSEVERITYAVAILABILITYMASK_APIID          (0xb2U)              /*< Service ID: Dem_GetDTCSeverityAvailabilityMask() */
#define DEM_READDATAOFPID01_APIID                         (0xb3U)              /*< Service ID: Dem_ReadDataOfPID01() */
#define DEM_GETB1COUNTER_APIID                            (0xb4U)              /*< Service ID: Dem_GetB1Counter() */
#define DEM_GETMONITORSTATUS_APIID                        (0xb5U)              /*< Service ID: Dem_GetMonitorStatus() */
#define DEM_SELECTDTC_APIID                               (0xb7U)              /*< Service ID: Dem_SelectDTC() */
#define DEM_SELECTFREEZEFRAMEDATA_APIID                   (0xb9U)              /*< Service ID: Dem_SelectFreezeFrameData() */
#define DEM_SELECTEXTENDEDDATARECORD_APIID                (0xbaU)              /*< Service ID: Dem_SelectExtendedDataRecord() */
#define DEM_GETDTCSELCETIONRESULT_APIID                   (0xb8U)              /*< Service ID: Dem_GetDTCSelectionResult() */

#define DEM_INITMEMORY_APIID                              (0xd0U)              /*< Service ID: Dem_InitMemory() */
#define DEM_POSTRUNREQUESTED_APIID                        (0xd1U)              /*< Service ID: Dem_PostRunRequested() */
#define DEM_GETENABLECONDITION_APIID                      (0xd2U)              /*< Service ID: Dem_GetEventEnableCondition() */
#define DEM_GETWIRSTATUS_APIID                            (0xd3U)              /*< Service ID: Dem_GetWIRStatus() */
#define DEM_ENABLEPERMANENTSTORAGE_APIID                  (0xd4U)              /*< Service ID: Dem_EnablePermanentStorage() */
#define DEM_GETIUMPRGENERALDATA_APIID                     (0xd5U)              /*< Service ID: Dem_GetIUMPRGeneralData() */
#define DEM_GETNEXTIUMPRRATIODATAANDDTC_APIID             (0xd7U)              /*< Service ID: Dem_GetNextIUMPRRatioDataAndDTC() */
#define DEM_GETCURRENTIUMPRRATIODATAANDDTC_APIID          (0xd8U)              /*< Service ID: Dem_GetCurrentIUMPRRatioDataAndDTC() */
#define DEM_GETPERMANENTSTORAGESTATE_APIID                (0xd9U)              /*< Service ID: Dem_GetPermanentStorageState() */
#define DEM_IUMPRLOCKNUMERATORS_APIID                     (0xdaU)              /*< Service ID: Dem_IUMPRLockNumerators() */
#define DEM_REQUESTNVSYNCHRONIZATION_APIID                (0xdbU)              /*< Service ID: Dem_RequestNVSynchronization() */
#define DEM_GETEVENTAVAILABLE_APIID                       (0xdcU)              /*< Service ID: Dem_GetEventAvailable() */
#define DEM_SETIUMPRFILTER_APIID                          (0xddU)              /*< Service ID: Dem_SetIUMPRFilter() */
#define DEM_GETNUMBEROFFILTEREDIUMPR_APIID                (0xdeU)              /*< Service ID: Dem_GetNumberOfFilteredIUMPR() */
#define DEM_UPDATEAVAILABLEOBDMIDS_APIID                  (0xdfU)              /*< Service ID: Dem_UpdateAvailableOBDMIDs() */
#define DEM_SETEXTENDEDDATARECORDFILTER_APIID             (0xe0U)              /*< Service ID: Dem_SetExtendedDataRecordFilter() */
#define DEM_GETNUMBEROFFILTEREDEXTENDEDDATARECORDS_APIID  (0xe1U)              /*< Service ID: Dem_GetNumberOfFilteredExtendedDataRecords() */   
#define DEM_GETNEXTFILTEREDEXTENDEDDATARECORD_APIID       (0xe2U)              /*< Service ID: Dem_GetNextFilteredExtendedDataRecord() */   
#define DEM_SETDTCFILTERBYREADINESSGROUP_APIID            (0xe3U)              /*< Service ID: Dem_SetDTCFilterByReadinessGroup() */   
#define DEM_SETDTCFILTERBYEXTENDEDDATARECORDNUMBER_APIID  (0xe4U)              /*< Service ID: Dem_SetDTCFilterByExtendedDataRecordNumber() */
#define DEM_NVMINIT_APIID                                 (0xf1U)              /*< Service ID: Dem_NvM_InitAdminData(), Dem_NvM_InitStatusData(), Dem_NvM_InitDebounceData(), Dem_NvM_InitEventAvailableData(), Dem_NvM_InitObdFreezeFrameData, Dem_NvM_InitObdIumprData(), Dem_NvM_InitDtrData(), Dem_NvM_InitAgingData(), Dem_NvM_InitCycleCounterData() */
#define DEM_NVMJOBFINISHED_APIID                          (0xf2U)              /*< Service ID: Dem_NvM_JobFinished() */
#define DEM_SETHIDEOBDOCCURRENCES_APIID                   (0xf3U)              /*< Service ID: Dem_SetHideOBDOccurrences() */
#define DEM_GETHIDEOBDOCCURRENCES_APIID                   (0xf4U)              /*< Service ID: Dem_GetHideOBDOccurrences() */
#define DEM_SATELLITEPREINIT_APIID                        (0xf5U)              /*< Service ID: Dem_SatellitePreInit() */
#define DEM_SATELLITEINIT_APIID                           (0xf6U)              /*< Service ID: Dem_SatelliteInit() */
#define DEM_SATELLITEMAINFUNCTION_APIID                   (0xf7U)              /*< Service ID: Dem_SatelliteMainFunction() */
#define DEM_GETEVENTIDOFDTC_APIID                         (0xf8U)              /*< Service ID: Dem_GetEventIdOfDTC() */
#define DEM_GETDTCSUPPRESSION_APIID                       (0xf9U)              /*< Service ID: Dem_GetDTCSuppression() */
#define DEM_SAFEPREINIT_APIID                             (0xfaU)              /*< Service ID: Dem_SafePreInit() */
#define DEM_SAFEINIT_APIID                                (0xfbU)              /*< Service ID: Dem_SafeInit() */
#define DEM_SETSI30SYMPTOM_APIID                          (0xfcU)              /*< Service ID: Dem_SetSI30Symptom() */
#define DEM_GETSI30STATUS_APIID                           (0xfdU)              /*< Service ID: Dem_GetSI30Status() */
#define DEM_INTERNAL_APIID                                (0xffU)              /*< Service ID: Internal Functions */


                                  /* Error Codes for Det and port interfaces */
/* ------------------------------------------------------------------------- */
#define DEM_E_NO_ERROR                           (0x00U)                       /*< This value is never returned as error code */
#define DEM_E_PARAM_CONFIG                       (0x10U)                       /*< API called with a parameter value which is not allowed in this configuration */
#define DEM_E_PARAM_POINTER                      (0x11U)                       /*< API called with a NULL pointer where NULL pointer is not allowed */
#define DEM_E_PARAM_DATA                         (0x12U)                       /*< API called with an invalid parameter value, e.g. outside the valid range */
#define DEM_E_PARAM_LENGTH                       (0x13U)                       /*< API called with an invalid length or size parameter */
#define DEM_E_UNINIT                             (0x20U)                       /*< API called before the Dem module has been initialized */
#define DEM_E_NODATAAVAILABLE                    (0x30U)                       /*< Data collection failed while storing a DTC */
#define DEM_E_WRONG_CONDITION                    (0x40U)                       /*< API called with unsatisfied precondition (other than initialization) */
#define DEM_E_INCONSISTENT_STATE                 (0xf0U)                       /*< Internal state inconsistency - indicates a serious error */


                                                                /* Constants */
/* ------------------------------------------------------------------------- */
#define DEM_EVENT_INVALID                        ((Dem_EventIdType)0x0000U)    /*< EventId which is not used */
#define DEM_EVENT_FIRST                          ((Dem_EventIdType)0x0001U)    /*< First valid EventId */

#define DEM_DTC_GROUP_ALL_DTCS                   ((Dem_DTCGroupType)(0x00ffffffUL))  /*< predefined DTC group encoding 'All DTCs' */
#define DEM_DTC_GROUP_EMISSION_REL_DTCS          ((Dem_DTCGroupType)(0x00000000UL))  /*< predefined DTC group encoding 'Emmission related DTCs' for OBD-II */
#define DEM_DTC_GROUP_WWHOBD_DTCS                ((Dem_DTCGroupType)(0x00ffff33UL))  /*< predefined DTC group encoding 'Emmission related DTCs' for WWH-OBD */


/* ********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

#define DEM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if (DEM_CFG_USE_INIT_POINTER == STD_ON)
/*! Stores the pointer to the active module configuration */
extern P2CONST(Dem_ConfigType, DEM_VAR_NOINIT, DEM_INIT_DATA)  Dem_GlobalConfigPtr;
#endif

#define DEM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */


/* ********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_API_Public Public Methods
 * \{
 */

/* ****************************************************************************
 * Dem_SatellitePreInit
 *****************************************************************************/
/*!
 * \brief         Initializes DemSatellite basic functionality.
 *
 * \details       This function performs the first half of initialization.
 *                After calling this function, the Dem enters a pre-initialized
 *                state in which basic functionality is available.
 *                From now on Dem_SetEventStatus is supported to allow reporting
 *                results by BSW modules for events assigned to this satellite
 *                during the initialization phase.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite
 *
 * \pre           The DemMaster must have been pre-initialized.
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(void, DEM_CODE)
Dem_SatellitePreInit(
  Dem_SatelliteInfoType SatelliteId
  );

/* ****************************************************************************
 * Dem_SafePreInit
 *****************************************************************************/
/*!
 * \brief         Initializes preliminary global config pointer.
 *
 * \details       Initializes preliminary global config pointer.
 *
 *                In multiple configuration use-cases (Post-Build Selectable),
 *                initialization has to provide a preliminary configuration.
 *                This preliminary configuration may be replaced during the
 *                final configuration during Dem_Init() or Dem_SafeInit()
 *
 * \param[in]     ConfigPtr
 *                A pointer to the preliminary configuration data.
 *
 *                In multiple configuration use cases, a valid configuration
 *                must be provided here.
 *
 * \pre           The Dem is not (pre)initialized yet. 
 *                all this API from a trusted (ASIL) partition if the Dem 
 *                Master runs in an untrusted partition (QM) and Satellite runs 
 *                in a trusted partition (QM).
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(void, DEM_CODE)
Dem_SafePreInit(
  P2CONST(Dem_ConfigType, AUTOMATIC, DEM_INIT_DATA)  ConfigPtr
  );

/* ****************************************************************************
 * Dem_MasterPreInit
 *****************************************************************************/
/*!
 * \brief         Initializes DemMaster basic functionality.
 *
 * \details       Initializes DemMaster basic functionality.
 *
 *                In multiple configuration use-cases (Post-Build Selectable),
 *                initialization has to provide a preliminary configuration.
 *                This preliminary configuration may be replaced during the
 *                final configuration in Dem_Init()
 *
 * \param[in]     ConfigPtr
 *                A pointer to the configuration data.
 *
 *                In multiple configuration use cases, a valid configuration
 *                must be provided here.
 *
 *                NULL_PTR is valid in the PRE-COMPILE configuration variant.
 *
 * \pre           The Dem may not have been initialized yet. Call this API first.
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(void, DEM_CODE)
Dem_MasterPreInit(
  P2CONST(Dem_ConfigType, AUTOMATIC, DEM_INIT_DATA)  ConfigPtr
  );

/* ****************************************************************************
 * Dem_PreInit
 *****************************************************************************/
/*!
 * \brief         Initializes basic functionality of DemMaster and DemSatellites.
 *
 * \details       This function performs the first half of initialization.
 *                After calling this function, the Dem enters a pre-initialized
 *                state in which basic functionality is available.
 *                Dem_SetEventStatus is supported to allow reporting results
 *                by BSW modules during the initialization phase.
 *
 *                In multiple configuration use-cases (Post-Build Selectable),
 *                initialization has to provide a preliminary configuration.
 *                This preliminary configuration may be replaced during the
 *                final configuration in Dem_Init().
 *
 *                This function pre-initializes both the DemMaster and the
 *                DemSatellite.
 *
 * \param[in]     ConfigPtr
 *                A pointer to the configuration data.
 *
 *                In multiple configuration use cases, a valid configuration
 *                must be provided here.
 *
 *                NULL_PTR is valid in the PRE-COMPILE configuration variant.
 *
 * \pre           This API can be used only in configurations with a single
 *                DemSatellite.
 * \pre           The Dem may not have been initialized yet. Call this prior to
 *                Dem_Init().
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(void, DEM_CODE)
Dem_PreInit(
  P2CONST(Dem_ConfigType, AUTOMATIC, DEM_INIT_DATA)  ConfigPtr
  );

/* ****************************************************************************
 * Dem_SatelliteInit
 *****************************************************************************/
/*!
 * \brief         Initializes functionality beyond the basic set.
 *
 * \details       This function initializes the local Dem Satellite variables
 *                required to provide the Dem services not already available
 *                Dem_PreInit().
 *
 *                During this initialization, the non-volatile data content
 *                is accessed to initialize derived state.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite
 *
 * \pre           The respective DemSatellite has been pre-initialized.
 * \pre           NvM has restored all non-volatile data used by the Dem.
 * \pre           DemMaster has been initialized.
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(void, DEM_CODE)
Dem_SatelliteInit(
    Dem_SatelliteInfoType  SatelliteId
  );

/* ****************************************************************************
 * Dem_SafeInit
 *****************************************************************************/
/*!
 * \brief         Initializes final global config pointer.
 *
 * \details       Initializes final global config pointer.
 *
 *                In multiple configuration use-cases (Post-Build Selectable),
 *                initialization has to provide a preliminary configuration.
 *                This preliminary configuration may be replaced with the
 *                final configuration during Dem_SafeInit() or Dem_Init()
 *
 * \param[in]     ConfigPtr
 *                A pointer to the final configuration data.
 *
 *                In multiple configuration use cases, a valid configuration
 *                must be provided here.
 *
 * \pre           The Dem is in PreInitialized state. 
 *                Call this API from a trusted (ASIL) partition if the Dem 
 *                Master runs in an untrusted partition (ASIL) and satellite 
 *                runs in a trusted partition (QM).
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(void, DEM_CODE)
Dem_SafeInit(
  P2CONST(Dem_ConfigType, AUTOMATIC, DEM_INIT_DATA)  ConfigPtr
  );

/* ****************************************************************************
 * Dem_MasterInit
 *****************************************************************************/
/*!
 * \brief         Initialize the DemMaster.
 *
 * \details       This function initializes the Dem variables required to
 *                provide the Dem services processed on the DemMaster.
 *
 *                During this initialization, the non-volatile data content
 *                is validated and the Dem assumes ownership of the respective
 *                RAM areas.
 *
 *                Depending on configuration, some event status changes trigger
 *                automatically from this initialization. These will not cause
 *                notification callbacks.
 *
 * \param[in]     ConfigPtr
 *                A pointer to the final configuration data.
 *                Pass NULL_PTR to keep the configuration data passed to
 *                Dem_PreInit().
 *
 * \pre           All DemSatellites have been pre-initialized.
 * \pre           NvM has restored all non-volatile data used by the Dem.
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(void, DEM_CODE)
Dem_MasterInit(
  P2CONST(Dem_ConfigType, AUTOMATIC, DEM_INIT_DATA)  ConfigPtr
  );


/* ****************************************************************************
 * Dem_Init
 *****************************************************************************/
/*!
 * \brief         Initialize the DemMaster and DemSatellite.
 *
 * \details       This function initializes the local Dem Satellite variables
 *                required to provide the Dem services not already available
 *                Dem_PreInit(), and to provide the Dem services processed on
 *                the DemMaster.
 *
 *                During this initialization, the non-volatile data content
 *                is validated and the Dem assumes ownership of the respective
 *                RAM areas.
 *
 *                Depending on configuration, some event status changes trigger
 *                automatically from this initialization. These will not cause
 *                notification callbacks.
 *
 * \param[in]     ConfigPtr
 *                A pointer to the final configuration data.
 *                Pass NULL_PTR to keep the configuration data passed to
 *                Dem_PreInit().
 *
 * \pre           This API can be used only in configurations with a single
 *                DemSatellite.
 * \pre           NvM has restored all non-volatile data used by the Dem.
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(void, DEM_CODE)
Dem_Init(
  P2CONST(Dem_ConfigType, AUTOMATIC, DEM_INIT_DATA)  ConfigPtr
  );

/* ****************************************************************************
 * Dem_Shutdown
 *****************************************************************************/
/*!
 * \brief         Shut down the Dem functionality.
 *
 * \details       When this function is called, the Dem will return into the
 *                basic initialization mode. This means
 *                Dem_ReportErrorStatus() is still available, but most other
 *                functions are not.
 *
 *                The Dem will mark modified non-volatile data structures,
 *                expecting NvN_WriteAll() following the shutdown. The Dem
 *                will no longer modify the RAM mirror areas configured for
 *                NV synchronization.
 *
 * \pre           Dem_PostRunRequested() returns FALSE.
 *
 * \context       TASK, from the master partition only
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(void, DEM_CODE)
Dem_Shutdown(
  void
  );

/* ****************************************************************************
 * Dem_MasterMainFunction
 *****************************************************************************/
/*!
 * \brief         Wrapper to call both timer and worker task.
 *
 * \details       Wrapper to call both timer and worker task.
 *
 * \pre           DemMaster has been pre-initialized.
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(void, DEM_CODE)
Dem_MasterMainFunction(                                                                                                          /* PRQA S 3451 */ /* MD_DEM_8.5_schm */
  void
  );

/* ****************************************************************************
 * Dem_SatelliteMainFunction
 *****************************************************************************/
/*!
 * \brief         Cyclic DemSatellite timer task.
 *
 * \details       This function creates the time base for a DemSatellite.
 *
 *                Call this function in a cyclic manner, with the configured
 *                cycle time. The run-time of this function is as minimal as
 *                possible, so it can be called on a higher priority task with
 *                minimal impact.
 *
 * \pre           DemSatellite has been pre-initialized.
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(void, DEM_CODE)
Dem_SatelliteMainFunction(                                                                                                       /* PRQA S 3451 */ /* MD_DEM_8.5_schm */
  void
  );

#if (DEM_CFG_SUPPORT_NVM_APPL_SYNCHRONIZE == STD_ON)
/* ****************************************************************************
 % Dem_RequestNvSynchronization
 *****************************************************************************/
/*!
 * \brief         Initiate NV synchronization.
 *
 * \details       This function causes the Dem to actively write all modified
 *                NV data blocks into non-volatile memory.
 *
 *                In normal operation, the Dem only synchronizes all data with
 *                the non-volatile storage on shutdown. This relies on the
 *                NvM_WriteAll() mechanism. It can be beneficial to force
 *                a complete NV synchronization more often, e.g. once per
 *                ignition cycle if the ECU does not power down when turning
 *                ignition off.
 *
 *                The NV synchronization is an asynchronous background process
 *                that will eventually store all blocks into non volatile
 *                memory. The Dem can be shut down during this time as normal,
 *                as long as the result of Dem_PostRunRequested() is
 *                respected.
 *
 *                This mechanism does not replace the DemClearDTCBehavior
 *                setting, or using NvM_WriteAll(). It is a complementary
 *                measure to reduce the impact of power loss.
 *
 *                This API is a MICROSAR extension to the AUTOSAR standard.
 *
 * \return        E_OK
 *                Request processed successfully
 *
 * \return        E_NOT_OK
 *                Only in case of detected development errors
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_NVM_APPL_SYNCHRONIZE == STD_ON
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   FALSE
 * \reentrant     TRUE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_RequestNvSynchronization(
  void
  );
#endif

#if (DEM_CFG_SUPPORT_VERSION_INFO == STD_ON)
/* ****************************************************************************
 * Dem_GetVersionInfo
 *****************************************************************************/
/*!
 * \brief         Get the version information of this module.
 *
 * \details       This function writes the module version information, module
 *                ID and vendor ID into the passed structure. The version
 *                information is decimal coded.
 *
 * \param[out]    versioninfo
 *                Pointer to a struct receiving the version information
 *
 * \pre           versioninfo may not be NULL_PTR.
 * \config        DEM_CFG_SUPPORT_VERSION_INFO == STD_ON
 *
 * \context       TASK|ISR2, from any partition
 * \synchronous   TRUE
 * \reentrant     TRUE
 * \trace         CREQ-102945
 *****************************************************************************/
FUNC(void, DEM_CODE)
Dem_GetVersionInfo(
  P2VAR(Std_VersionInfoType, AUTOMATIC, DEM_APPL_DATA)  versioninfo
  );
#endif

#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
/* ****************************************************************************
 * Dem_SetEventAvailable
 *****************************************************************************/
/*!
 * \brief         Change event configuration.
 *
 * \details       This function changes if events are present or not in a
 *                given configuration. The main use case is related to variant
 *                coding, this is a run-time option to change the event
 *                configuration.
 *
 *                Events that are set 'unavailable' cause
 *                all Event based APIs (but Dem_SetEventAvailable()) to
 *                return E_NOT_OK and perform no action.
 *                DTC based API will not find unavailable events, to the point
 *                that such DTCs are suppressed once all related events are
 *                unavailable.
 *
 *                For all status calculations, an 'unavailable' event has UDS
 *                status 0x00 (passed and tested). When an unavailable event is
 *                set 'available' again, its status is initialized to 0x50
 *                (not tested).
 *
 *                An event that is already failed or stored can not be
 *                disconnected. Such events need to be cleared first, see
 *                Dem_ClearDTC().
 *
 *                Variant coding can be achieved using PostBuild Selectable
 *                when the event availability is known statically based on few
 *                ECU configurations.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *
 * \param[in]     AvailableStatus
 *                TRUE: Event is available
 *                FALSE: Event is not available
 *
 * \return        E_OK
 *                The request was processed successfully
 *
 * \return        E_NOT_OK
 *                The request was rejected due to invalid arguments or state.
 *
 * \pre           If DEM_CFG_SUPPORT_EVENTAVAILABLE_NV == STD_ON, the Dem must
 *                be initialized. Otherwise this API is available after
 *                pre-initialization.
 * \config        DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE (for different EventIds)
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetEventAvailable(
  Dem_EventIdType  EventId,
  boolean  AvailableStatus
  );
#endif

#if (DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON)
/* ****************************************************************************
 * Dem_SetDTCSuppression
 *****************************************************************************/
/*!
 * \brief         Suppress a DTC.
 *
 * \details       This function suppresses DTCs such, that Dcm will not report
 *                the DTC for any reason. The internal processing of the event
 *                continues as usual.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 *
 * \param[in]     SuppressionStatus
 *                TRUE: Suppress the DTC
 *                FALSE: Lift suppression of the DTC
 *
 * \return        E_OK
 *                The request was processed successfully
 *
 * \return        E_NOT_OK
 *                No DTC was selected before the call or invalid parameters
 *                are passed to the function (only if DET is enabled).
 *
 * \return        DEM_WRONG_DTC
 *                The selected DTC does not exist in the selected origin
 *                or no single DTC has been selected
 *
 * \return        DEM_WRONG_DTCORIGIN
 *                The selected DTC Origin does not exist.
 *
 * \return        DEM_PENDING
 *                Never returned by this implementation
 *
 * \pre           Requires a preceding DTC selection by Dem_SelectDTC.
 * \config        DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetDTCSuppression(
  uint8  ClientId,
  boolean  SuppressionStatus
  );
#endif

#if (DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON)
/* ****************************************************************************
 * Dem_GetDTCSuppression
 *****************************************************************************/
/*!
 * \brief         Retrieve suppression state.
 *
 * \details       This function retrieves the current suppression state of
 *                the selected DTC.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 *
 * \param[out]    SuppressionStatus
 *                Pointer to receive the suppression state of the DTC.
 *
 * \return        E_OK
 *                The suppression state of the DTC was stored in
 *                SuppressionStatus.
 *
 * \return        E_NOT_OK
 *                No DTC was selected before the call or invalid parameters
 *                are passed to the function (only if Det is enabled)
 *
 * \return        DEM_WRONG_DTC
 *                The selected DTC does not exist in the selected origin
 *                or no single DTC has been selected
 *
 * \return        DEM_WRONG_DTCORIGIN
 *                The requested DTC Origin does not exist.
 *
 * \return        DEM_PENDING
 *                Never returned by this implementation
 *
 * \pre           Requires a preceding DTC selection by Dem_SelectDTC.
 * \config        DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetDTCSuppression(
  uint8  ClientId,
  P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA)  SuppressionStatus
  );
#endif


#if (DEM_CFG_SUPPORT_ENABLE_CONDITIONS == STD_ON)
/* ****************************************************************************
 * Dem_SetEnableCondition
 *****************************************************************************/
/*!
 * \brief         Set state of enable conditions.
 *
 * \details       Each event may have assigned several enable conditions. If
 *                any enable conditions referenced by the event is disabled,
 *                event reports are not processed (Dem_SetEventStatus(),
 *                Dem_ReportErrorStatus()).
 *
 *                Depending on DemDebounceBehavior, the debouncing of events
 *                with a disabled precondition is either paused or reset.
 *                Once all enable conditions are fulfilled again, the monitor
 *                will be notified.
 *
 *                During the pre-initialization phase, all enable conditions
 *                are ignored. Starting with Dem_Init() the configured
 *                initialization values for the enable conditions apply.
 *
 * \param[in]     EnableConditionID
 *                Unique handle of the EnableCondition
 *
 * \param[in]     ConditionFulfilled
 *                TRUE: Enable condition is fulfilled
 *                FALSE: Enable condition is not fulfilled
 *
 * \return        E_OK
 *                The request was processed successfully
 *
 * \return        E_NOT_OK
 *                Only in case of detected development errors
 *
 * \pre           RTE is active (if RTE is used).
 * \config        DEM_CFG_SUPPORT_ENABLE_CONDITIONS == STD_ON
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetEnableCondition(
  uint8  EnableConditionID,
  boolean  ConditionFulfilled
  );
#endif

#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 * Dem_SetStorageCondition
 *****************************************************************************/
/*!
 * \brief         Set state of storage conditions.
 *
 * \details       Each event may have assigned several storage conditions. If
 *                any storage condition referenced by the event is disabled,
 *                the event is not stored into the event memory.
 *
 *                Depending on configuration, this will have an effect on the
 *                Status bits modified, e.g. ConfirmedDTC is not set in case
 *                DemResetConfirmedBitOnOverflow = TRUE.
 *
 * \param[in]     StorageConditionID
 *                Unique handle of the StorageCondition
 *
 * \param[in]     ConditionFulfilled
 *                TRUE: Storage condition is fulfilled
 *                FALSE: Storage condition is not fulfilled
 *
 * \return        E_OK
 *                Request processed successfully
 *
 * \return        E_NOT_OK
 *                Only in case of detected development errors
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetStorageCondition(
  uint8  StorageConditionID,
  boolean  ConditionFulfilled
  );
#endif

/* ****************************************************************************
 * Dem_ReportErrorStatus
 *****************************************************************************/
/*!
 * \brief         API to report a monitor result.
 *
 * \details       This API is the application interface to report monitor
 *                results.
 *
 *                The monitor status is updated synchronously. This can cause
 *                notification function to be called, e.g. to the FiM module.
 *                The event UDS status is processed on task level.
 *
 *                If enable conditions are not set for the reported event,
 *                the report is discarded.
 *
 * \attention     The operations Dem_SetEventStatus(),
 *                Dem_ResetEventStatus(), Dem_PrestoreFreezeFrame(),
 *                Dem_ClearPrestoredFreezeFrame() and
 *                Dem_ResetEventDebounceStatus() are not reentrant
 *                for the same EventId.
 *
 * \param[in]     EventId
 *                Unique handle of the Event to report.
 *
 * \param[in]     EventStatus
 *                Monitor result reported for the Event. Valid values are
 *                 - DEM_EVENT_STATUS_PASSED
 *                 - DEM_EVENT_STATUS_FAILED
 *
 *                If monitor internal debouncing is disabled for the given EventId
 *                the following values are also allowed:
 *                 - DEM_EVENT_STATUS_PREPASSED
 *                 - DEM_EVENT_STATUS_PREFAILED
 *
 *                If monitor internal debouncing is enabled for the given EventId
 *                the following value is allowed:
 *                 - DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED
 *
 *                If similar conditions are used the following values
 *                are also allowed:
 *                 - DEM_EVENT_STATUS_PASSED_CONDITIONS_NOT_FULFILLED
 *                 - DEM_EVENT_STATUS_FAILED_CONDITIONS_NOT_FULFILLED
 *
 *                If similar conditions are used and monitor internal debouncing
 *                is enabled for the given EventId the following values are also
 *                allowed:
 *                 - DEM_EVENT_STATUS_PREPASSED_CONDITIONS_NOT_FULFILLED
 *                 - DEM_EVENT_STATUS_PREFAILED_CONDITIONS_NOT_FULFILLED
 *
 *
 * \pre           -
 *
 * \context       TASK|ISR2, from the respective satellite partition only
 * \synchronous   TRUE for monitor status, FALSE for event status
 * \reentrant     TRUE for different EventIds.
 *****************************************************************************/
FUNC(void, DEM_CODE)
Dem_ReportErrorStatus(
  Dem_EventIdType  EventId,
  Dem_EventStatusType  EventStatus
  );

/* ****************************************************************************
 * Dem_SetEventStatus
 *****************************************************************************/
/*!
 * \brief         API to report a monitor result.
 *
 * \details       This API is the application interface to report monitor
 *                results. It can be invoked via RTE_CALL interface, as
 *                Operation of port interface 'DiagnosticMonitor'.
 *
 *                The monitor status is updated synchronously. This can cause
 *                notification function to be called, e.g. to the FiM module.
 *                The event UDS status is processed on task level.
 *
 *                If enable conditions are not set for the reported event,
 *                the report is discarded.
 *
 * \attention     The operations Dem_SetEventStatus(),
 *                Dem_ResetEventStatus(), Dem_PrestoreFreezeFrame(),
 *                Dem_ClearPrestoredFreezeFrame() and
 *                Dem_ResetEventDebounceStatus() are not reentrant
 *                for the same EventId.
 *
 * \param[in]     EventId
 *                Unique handle of the Event to report.
 *
 * \param[in]     EventStatus
 *                Monitor result reported for the Event. Valid values are
 *                 - DEM_EVENT_STATUS_PASSED
 *                 - DEM_EVENT_STATUS_FAILED
 *
 *                If monitor internal debouncing is disabled for the given EventId
 *                the following values are also allowed:
 *                 - DEM_EVENT_STATUS_PREPASSED
 *                 - DEM_EVENT_STATUS_PREFAILED
 *
 *                If monitor internal debouncing is enabled for the given EventId
 *                the following value is allowed:
 *                 - DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED
 *
 *                If similar conditions are used the following values
 *                are also allowed:
 *                 - DEM_EVENT_STATUS_PASSED_CONDITIONS_NOT_FULFILLED
 *                 - DEM_EVENT_STATUS_FAILED_CONDITIONS_NOT_FULFILLED
 *
 *                If similar conditions are used and monitor internal debouncing
 *                is enabled for the given EventId the following values are also
 *                allowed:
 *                 - DEM_EVENT_STATUS_PREPASSED_CONDITIONS_NOT_FULFILLED
 *                 - DEM_EVENT_STATUS_PREFAILED_CONDITIONS_NOT_FULFILLED
 *
 * \return        E_OK
 *                The test result was processed successfully
 *
 * \return        E_NOT_OK
 *                The test result was rejected, e.g. due to enable conditions
 *                or variant coding (see Dem_SetEventAvailable() )
 *
 * \pre           -
 *
 * \context       TASK|ISR2, from the respective satellite partition only
 * \synchronous   TRUE for monitor status, FALSE for event status
 * \reentrant     TRUE for different EventIds.
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetEventStatus(
  Dem_EventIdType  EventId,
  Dem_EventStatusType  EventStatus
  );

/* ****************************************************************************
 * Dem_ResetEventStatus
 *****************************************************************************/
/*!
 * \brief         SWC API to reset an events failed bit.
 *
 * \details       This API is intended to be called via RTE_CALL interface,
 *                as Operation of port interface 'DiagnosticMonitor'.
 *
 *                Dem_ResetEventStatus() resets the failed bit of an event
 *                that can not be tested in this operation cycle. If the event
 *                has already completed a test, the request is rejected.
 *
 *                The Dem module will not treat resetting the event failed bit
 *                as a trigger to start aging of an event.
 *
 * \attention     The operations Dem_SetEventStatus(),
 *                Dem_ResetEventStatus(), Dem_PrestoreFreezeFrame(),
 *                Dem_ClearPrestoredFreezeFrame() and
 *                Dem_ResetEventDebounceStatus() are not reentrant
 *                for the same EventId.
 *
 * \param[in]     EventId
 *                Unique handle of the Event to reset.
 *
 * \return        E_OK
 *                The request was processed successfully
 *
 * \return        E_NOT_OK
 *                The request was rejected, e.g. the event had already
 *                completed testing, or due to variant coding
 *                (see Dem_SetEventAvailable() )
 *
 * \pre           RTE is started (if RTE is used).
 *
 * \context       TASK|ISR2, from the respective satellite partition only
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventIds.
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_ResetEventStatus(
  Dem_EventIdType  EventId
  );

/* ****************************************************************************
 * Dem_PrestoreFreezeFrame
 *****************************************************************************/
/*!
 * \brief         SWC API to immediately store snapshot data.
 *
 * \details       This API is intended to be called via RTE_CALL interface,
 *                as Operation of port interface 'DiagnosticMonitor'.
 *
 *                Dem_PrestoreFreezeFrame() stores the snapshot data for
 *                an event, in order to freeze that data set when the event
 *                qualifies 'failed' later. If a prestored record already
 *                exists, the Dem will update it's contents.
 *
 *                Normally, the Dem collects the configured DID data for an
 *                event during the storage processing on the Dem task function.
 *                This function can be used to close the timing gap between the
 *                event report and the Dem task invocation, e.g. if the DID
 *                data changes rapidly.
 *
 *                The prestored data is managed in a seperate buffer. The data sets
 *                are discarded once the event reports a qualified result, or
 *                the queue overflows.
 *                Also see Dem_ClearPrestoredFreezeFrame to actively free a
 *                prestored data set.
 *
 * \attention     The operations Dem_SetEventStatus(),
 *                Dem_ResetEventStatus(), Dem_PrestoreFreezeFrame(),
 *                Dem_ClearPrestoredFreezeFrame() and
 *                Dem_ResetEventDebounceStatus() are not reentrant
 *                for the same EventId.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *
 * \return        E_OK
 *                The data was collected successfully (if processed synchronously).
 *                Prestore freeze frame request accepted (if processed asynchronously).
 *
 * \return        E_NOT_OK
 *                No data was collected, e.g. due to variant coding (see
 *                Dem_SetEventAvailable() )
 *
 *
 * \pre           RTE is started (if RTE is used).
 *
 * \context       TASK|ISR2, from the respective satellite partition only
 *
 * \synchronous   TRUE if called from partition same as Dem master
 *                FALSE if called from partition other than Dem master
 *
 * \reentrant     TRUE for different EventIds.
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_PrestoreFreezeFrame(
  Dem_EventIdType  EventId
  );

/* ****************************************************************************
 * Dem_ClearPrestoredFreezeFrame
 *****************************************************************************/
/*!
 * \brief         SWC API to clear prestored data.
 *
 * \details       This API is intended to be called via RTE_CALL interface,
 *                as Operation of port interface 'DiagnosticMonitor'.
 *
 *                Dem_ClearPrestoredFreezeFrame() is not used for memory
 *                management, so its use is optional. The Dem automatically
 *                frees prestored data on use, or overflow. Call this API when
 *                the prestored data is no longer relevant and you want the
 *                Dem to ignore it.
 *
 *                If no prestored data exists, this function does nothing.
 *
 * \attention     The operations Dem_SetEventStatus(),
 *                Dem_ResetEventStatus(), Dem_PrestoreFreezeFrame(),
 *                Dem_ClearPrestoredFreezeFrame() and
 *                Dem_ResetEventDebounceStatus() are not reentrant
 *                for the same EventId.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *
 * \return        E_OK
 *                Prestore data cleared (if processed synchronously).
 *                Clear prestore data request accepted (if processed asynchronously).
 *
 * \return        E_NOT_OK
 *                No prestore data cleared, e.g. due to variant coding (see
 *                Dem_SetEventAvailable() )
 *
 *
 * \pre           RTE is started (if RTE is used).
 *
 * \context       TASK|ISR2, from the respective satellite partition only
 *
 * \synchronous   TRUE if called from partition same as Dem master
 *                FALSE if called from partition other than Dem master
 * \reentrant     TRUE for different EventIds.
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_ClearPrestoredFreezeFrame(
  Dem_EventIdType  EventId
  );

/* ****************************************************************************
 * Dem_ResetEventDebounceStatus
 *****************************************************************************/
/*!
 * \brief         SWC API to control the Dem internal event debouncing.
 *
 * \details       This API is intended to be called via RTE_CALL interface,
 *                as Operation of port interface 'DiagnosticMonitor'.
 *
 *                Depending on DebounceResetStatus and the EventId's configured
 *                debouncing algorithm, this API performs the following:
 *
 *                Time Based Debouncing:
 *                DEM_DEBOUNCE_STATUS_FREEZE: If the debounce timer is active,
 *                it is paused without modifying its current value. Otherwise
 *                this has no effect. The timer will continue if the monitor
 *                reports another PREFAILED or PREPASSED in the same direction.
 *
 *                DEM_DEBOUNCE_STATUS_RESET: The debounce timer is stopped and
 *                Its value is set to 0.
 *
 *                Counter Based Debouncing:
 *                DEM_DEBOUNCE_STATUS_FREEZE: This has no effect.
 *
 *                DEM_DEDOUNCE_STATUS_RESET: This will set the current value
 *                of the debounce counter back to 0.
 *
 *                Monitor Internal Debouncing:
 *                The API returns E_NOT_OK in either case.
 *
 * \attention     The operations Dem_SetEventStatus(),
 *                Dem_ResetEventStatus(), Dem_PrestoreFreezeFrame(),
 *                Dem_ClearPrestoredFreezeFrame() and
 *                Dem_ResetEventDebounceStatus() are not reentrant
 *                for the same EventId.
 *
 * \param[in]     EventId
 *                Unique handle of the Event to report.
 *
 * \param[in]     DebounceResetStatus
 *                DEM_DEBOUNCE_STATUS_RESET: Reset debouncing
 *                DEM_DEBOUNCE_STATUS_FREEZE: Freeze debouncing
 *
 * \return        E_OK
 *                The request was processed successfully
 *
 * \return        E_NOT_OK
 *                The request was rejected, e.g. due to variant coding (see
 *                Dem_SetEventAvailable() or supported debouncing algorithm )
 *
 * \pre           Dem has been pre-initialized.
 *
 * \context       TASK|ISR2, from the respective satellite partition only
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventIds.
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_ResetEventDebounceStatus(
  Dem_EventIdType  EventId,
  Dem_DebounceResetStatusType  DebounceResetStatus
  );

/* ****************************************************************************
 * Dem_GetDebouncingOfEvent
 *****************************************************************************/
/*!
 * \brief         SWC API to read the debouncing status of an event.
 *
 * \details       This API is intended to be called via RTE_CALL interface,
 *                as Operation of port interface 'DiagnosticInfo'.
 *
 * \param[in]     EventId
 *                Unique handle of the Event
 * \param[out]    DebouncingState
 *                Pointer receiving the current debouncing status
 *
 * \return        E_OK
 *                The debouncing status was stored into DebouncingState
 * \return        E_NOT_OK if
 *                The request was rejected, e.g. due to variant coding (see
 *                Dem_SetEventAvailable() )
 *
 * \pre           RTE is active (if RTE is used).
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetDebouncingOfEvent(
  Dem_EventIdType  EventId,
  P2VAR(Dem_DebouncingStateType, AUTOMATIC, DEM_APPL_DATA)  DebouncingState
  );

/* ****************************************************************************
 * Dem_SetOperationCycleState
 *****************************************************************************/
/*!
 *  \brief        Start and Stop operation cycles.
 *
 *  \details      This function is used to report operation cycle changes to
 *                the Dem.
 *
 *                Usually, starting an operation cycle will reset
 *                *ThisOperationCycle status bits and the debouncing state.
 *                Ending an operation cycle tests for healing and aging
 *                conditions and processes related statistics.
 *
 *                Starting the OBD driving cycle will qualify it (if it is not
 *                yet qualified), ending the OBD driving cycle will restart it
 *                if the cycle is qualified.
 *
 *                Starting the OBD warm-up cycle can be delayed to the restart
 *                of the OBD driving cycle by configuration.
 *
 *                Starting the OBD hybrid ignition cycle will not have an
 *                effect on events, that cycle is only processed for internal
 *                statistics.
 *
 *                There is no difference between restarting an operation cycle
 *                and stopping then starting the same cycle. The latter will
 *                result in the exact same run-time behavior.
 *
 *                The status change and all other effects are queued and 
 *                processed on the next invocation of the cyclic Dem task.
 *
 *                The processing queue for operation cycle changes is limited,
 *                this API will reject cycle state changes beyond a
 *                START-STOP or STOP-START double transition.
 *
 * \param[in]     OperationCycleId
 *                Identifier of the Cycle to change state
 *
 * \param[in]     CycleState
 *                DEM_CYCLE_STATE_START: Start a stopped cycle, or restart an
 *                                       active cycle.
 *                DEM_CYCLE_STATE_END:   Stop an active cycle.
 *
 * \return        E_OK
 *                Request was queued successfully
 *
 * \return        E_NOT_OK
 *                Only in case of detected development errors or in special
 *                case for OBD Driving cycle (Driving cycle qualification already
 *                queued, but not processed, and requested again).
 *
 * \pre           -
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   FALSE
 * \reentrant     TRUE (for different CycleIds)
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetOperationCycleState(
  uint8  OperationCycleId,
  Dem_OperationCycleStateType  CycleState
  );

/* ****************************************************************************
 * Dem_GetOperationCycleState
 *****************************************************************************/
/*!
 * \brief         Get the state of a specific operation cycle.
 *
 * \details       Get the state of a specific operation cycle.
 *
 * \param[in]     OperationCycleId
 *                Identifier of the Cycle of which to get the state
 *
 * \param[out]    CycleState
 *                The current state of the requested operation cycle.
 *                DEM_CYCLE_STATE_START: Cycle is started
 *                DEM_CYCLE_STATE_END:   Cycle is stopped
 *
 * \return        E_OK
 *                Request was successfully
 * \return        E_NOT_OK
 *                Only in case of detected development errors
 *
 * \pre           -
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetOperationCycleState(
  uint8  OperationCycleId,
  P2VAR(Dem_OperationCycleStateType, AUTOMATIC, DEM_APPL_DATA)  CycleState
  );

/* ****************************************************************************
 * Dem_GetIndicatorStatus
 *****************************************************************************/
/*!
 * \brief         Get current status of an indicator.
 *
 * \details       Calculates the accumulated status of an indicator.
 *
 *                Depending on the indicator and configuration, this includes
 *                the correct priorization of multiple concurrent requests,
 *                e.g. in J1939 you receive the same status that is reported
 *                in the DM messages.
 *
 * \param[in]     IndicatorId
 *                Unique identifier of the indicator
 *
 * \param[out]    IndicatorStatus
 *                The current status of the indicator
 *
 * \return        E_OK
 *                Request processed successfully
 *
 * \return        E_NOT_OK
 *                Only in case of detected development errors
 *
 * \pre           -
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetIndicatorStatus(
  uint8  IndicatorId,
  P2VAR(Dem_IndicatorStatusType, AUTOMATIC, DEM_APPL_DATA)  IndicatorStatus
  );

#if (DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON)
/* ****************************************************************************
 * Dem_GetWIRStatus
 *****************************************************************************/
/*!
 * \brief         Get state of Warning Indicator Request Bit override.
 *
 * \details       Check whether the WIR bit is latched for the event, or if its
 *                state is currently controlled by the Dem module.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 * \param[out]    WIRStatus
 *                TRUE:  WIR status is currently latched by user
 *                FALSE: WIR status is currently controlled by Dem
 *
 *                This API is a MICROSAR extension to the AUTOSAR standard.
 *
 * \return        E_OK
 *                Request processed successfully
 * \return        E_NOT_OK
 *                The request was rejected due to invalid arguments or
 *                variant coding (see Dem_SetEventAvailable() )
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetWIRStatus(
  Dem_EventIdType EventId,
  P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA) WIRStatus
  );
#endif

#if (DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON)
/* ****************************************************************************
 * Dem_SetWIRStatus
 *****************************************************************************/
/*!
 * \brief         Control Warning Indicator Request Bit override.
 *
 * \details       The Dem module controls the state of bit7 (RequestWarningInd)
 *                based on event healing. There are use-cases that require
 *                to keep the bit7 state alive longer than the normal healing
 *                algorithm does, e.g. because a fault reaction is disabled
 *                only with the next ignition cycle.
 *
 *                This function allows implementing such use-cases, without
 *                complicating the normal healing algorithm. Once a monitor
 *                calls this API with WIRStatus = TRUE, the WIR bit is active
 *                and remains active until this state is revoked by calling
 *                the API again, with WIRStatus = FALSE.
 *
 *                The related event will still heal bit7 as normal. Releasing
 *                the WIR latch will only result in WIR = FALSE if the event
 *                has healed.
 *
 *                During an active ControlDTCSetting (UDS service 0x85) the
 *                override state cannot be changed. In this case the API will
 *                return E_NOT_OK and the caller has to retry the operation
 *                later.
 *
 * \param[in]     EventId
 *                Unique handle of the Event
 * \param[in]     WIRStatus
 *                TRUE:  Latch WIR-bit to TRUE
 *                FALSE: Release the latch
 *
 * \return        E_OK
 *                Request processed successfully
 * \return        E_NOT_OK
 *                The request was rejected due to invalid arguments, state or
 *                variant coding (see Dem_SetEventAvailable() )
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE (for different EventIds)
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetWIRStatus(
  Dem_EventIdType EventId,
  boolean WIRStatus
  );
#endif

/* ****************************************************************************
 * Dem_SelectDTC
 *****************************************************************************/
/*!
 * \brief         Selects a DTC or DTC group as target for further operations.
 *
 * \details       The Dem provides a range of APIs controlling and accessing
 *                event memory and its behavior or configuration and states.
 *                Many of those APIs follow a 'select and request' mechanism.
 *                Initially a client selects a DTC or a group of DTCs and then
 *                calls APIs working on the active selection. A selection is
 *                client local and remains until a new selection is made.
 *
 *                If the API Dem_SelectDTC is called, the Dem uses the selected
 *                DTC or group of DTC in the requested DTCOrigin and DTCFormat
 *                as target for the following API calls:
 *                - Dem_GetStatusOfDTC
 *                - Dem_GetSeverityOfDTC
 *                - Dem_GetFunctionalUnitOfDTC
 *                - Dem_ClearDTC
 *                - Dem_DisableDTCRecordUpdate
 *                - Dem_EnableDTCRecordUpdate
 *                - Dem_GetDTCSelectionResult.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 * \param[in]     DTC
 *                Defines the DTC in respective format that is selected. If the
 *                DTC fits to a DTC group number, the DTC group is selected.
 * \param[in]     DTCFormat
 *                Defines the input-format of the provided DTC value.
 * \param[in]     DTCOrigin
 *                The event memory of the requested DTC or group of DTC.
 *
 * \return        E_OK
 *                Always. Use API Dem_GetDTCSelectionResult for the result of
 *                this selection.
 *
 * \pre           -
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_SelectDTC(
  uint8              ClientId,
  uint32             DTC,
  Dem_DTCFormatType  DTCFormat,
  Dem_DTCOriginType  DTCOrigin
  );

/* ****************************************************************************
 * Dem_GetDTCSelectionResult
 *****************************************************************************/
/*!
 * \brief         Returns the result of API Dem_SelectDTC.
 *
 * \details       This function returns the result of a preceding
 *                call of API Dem_SelectDTC. It is no precondition to
 *                call this API for subsequent operations on the
 *                selected DTCs.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 *
 * \return        E_OK
 *                The preceding DTC selection was successful.
 *
 * \return        DEM_STATUS_WRONG_DTC
 *                The requested DTC does not match the given DTC Origin.
 *
 * \return        DEM_STATUS_WRONG_DTCORIGIN
 *                The requested DTC Origin is not supported by configuration.
 *
 * \pre           Requires a preceding DTC selection by Dem_SelectDTC.
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   FALSE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetDTCSelectionResult(
  uint8 ClientId
  );

/* ****************************************************************************
 * Dem_GetMonitorStatus
 *****************************************************************************/
/*!
 * \brief         API to read the monitor status.
 *
 * \details       This API reads the current monitor status of an event.
 *
 *                Dem_GetMonitorStatus() is part of the RTE interface, but
 *                may be called directly as well.
 *
 * \param[in]     EventId
 *                Unique handle of the Event
 *
 * \param[out]    MonitorStatus
 *                Pointer receiving the monitor status:
 *                Bit0:  DEM_MONITOR_STATUS_TF (TestFailed)
 *                Bit1:  DEM_MONITOR_STATUS_TNCTOC (TestNotCompletedThisOpCycle)
 *
 * \return        E_OK
 *                MonitorStatus now contains the event status.
 *
 * \return        E_NOT_OK
 *                The request was rejected, e.g. due to variant coding (see
 *                Dem_SetEventAvailable()).
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetMonitorStatus(
  Dem_EventIdType  EventId,
  P2VAR(Dem_MonitorStatusType, AUTOMATIC, DEM_APPL_DATA)  MonitorStatus
  );

/* ****************************************************************************
 * Dem_GetEventUdsStatus
 * Dem_GetEventStatus
 *****************************************************************************/
/*!
 * \brief         API to read the UDS event status.
 *
 * \details       This API reads the current event status byte of an event.
 *                The status byte is encoded as described in ISO 14229, without
 *                applying the status availability mask.
 *
 *                Dem_GetEventUdsStatus() is part of the RTE interface, but
 *                may be called directly as well.
 *
 * \param[in]     EventId
 *                Unique handle of the Event
 *
 * \param[out]    UDSStatusByte
 *                Pointer receiving the event status:
 *                Bit0:  DEM_UDS_STATUS_TF
 *                Bit1:  DEM_UDS_STATUS_TFTOC
 *                Bit2:  DEM_UDS_STATUS_PDTC
 *                Bit3:  DEM_UDS_STATUS_CDTC
 *                Bit4:  DEM_UDS_STATUS_TNCSLC
 *                Bit5:  DEM_UDS_STATUS_TFSLC
 *                Bit6:  DEM_UDS_STATUS_TNCTOC
 *                Bit7:  DEM_UDS_STATUS_WIR
 *
 * \return        E_OK
 *                EventUdsStatus now contains the event status.
 *
 * \return        E_NOT_OK
 *                The request was rejected, e.g. due to variant coding (see
 *                Dem_SetEventAvailable()).
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetEventUdsStatus(
  Dem_EventIdType  EventId,
  P2VAR(Dem_UdsStatusByteType, AUTOMATIC, DEM_APPL_DATA)  UDSStatusByte
  );
#define Dem_GetEventStatus                          Dem_GetEventUdsStatus

/* ****************************************************************************
 * Dem_GetEventFailed
 *****************************************************************************/
/*!
 * \brief         API to read the event status bit 0.
 *
 * \details       This API returns bit0 of the current events status.
 *
 *                Dem_GetEventFailed() is part of the RTE interface, but
 *                may be called directly as well.
 *
 * \param[in]     EventId
 *                Unique handle of the Event
 *
 * \param[out]    EventFailed
 *                Pointer receiving the current failed bit:
 *                TRUE if bit0 is set, FALSE otherwise
 *
 * \return        E_OK
 *                EventFailed now contains the event status.
 *
 * \return        E_NOT_OK
 *                The request was rejected, e.g. due to variant coding (see
 *                Dem_SetEventAvailable()).
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetEventFailed(
  Dem_EventIdType  EventId,
  P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA)  EventFailed
  );

/* ****************************************************************************
 * Dem_GetEventTested
 *****************************************************************************/
/*!
 * \brief         SWC API to read the negated event status bit 6.
 *
 * \details       This API returns TRUE in 'EventTested' if the event has
 *                completed a test in this operation cycle, FALSE otherwise.
 *                This corresponds to the negated status bit6.
 *
 *                Dem_GetEventTested() is part of the RTE interface, but
 *                may be called directly as well.
 *
 * \param[in]     EventId
 *                Unique handle of the Event
 *
 * \param[out]    EventTested
 *                Pointer receiving the current tested bit
 *
 * \return        E_OK
 *                EventTested now contains the event status
 *
 * \return        E_NOT_OK
 *                The request was rejected, e.g. due to variant coding (see
 *                Dem_SetEventAvailable())
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetEventTested(
  Dem_EventIdType  EventId,
  P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA)  EventTested
  );

/* ****************************************************************************
 * Dem_GetEventFreezeFrameDataEx
 *****************************************************************************/
/*!
 * \brief         SWC API to read the stored snapshot data of an event.
 *
 * \details       This API is intended to be called via RTE_CALL interface,
 *                as Operation of port interface 'DiagnosticInfo'.
 *
 *                Dem_GetEventFreezeFrameDataEx() copies data from the stored
 *                snapshot data of an event into DestBuffer, following no
 *                particular format and contains no header-information like
 *                RecordNumber or DataId.
 *
 *                Only the DID data actually stored in the event storage is
 *                returned here. If the Dcm adds additional parts to a DID,
 *                these will be missing.
 *
 *                The record number 0xff is a magic value used to read the most
 *                recently stored record. This is only supported in case record
 *                numbers are calculated (DemTypeOfFreezeFrameRecordNumeration).
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 * \param[in]     RecordNumber
 *                SnapshotRecord number to read. Contrary to usual usage, 0xFF
 *                returns the most recently stored record.
 * \param[in]     DataId
 *                Return only the data of this DID.
 * \param[out]    DestBuffer
 *                Buffer to receive the data.
 * \param[in,out] BufSize
 *                In: Size of the buffer.
 *                Out: Number of bytes written.
 *
 * \return        E_OK
 *                The requested data was copied to the destination buffer.
 * \return        DEM_NO_SUCH_ELEMENT
 *                The data is currently not stored for the requested event.
 *                or
 *                the requested RecordNumber is not supported for the given
 *                event
 *                or
 *                the requested data identifier is not supported within the
 *                requested record (freeze frame).
 * \return        E_NOT_OK
 *                The request was rejected, e.g. due to variant coding (see
 *                Dem_SetEventAvailable() )
 *                or
 *                the requested data is currently not accessible (e.g. in case
 *                of asynchronous preempted data retrieval from application).
 * \return        DEM_BUFFER_TOO_SMALL
 *                The provided buffer is too small.
 *
 * \pre           RTE is active (if RTE is used).
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetEventFreezeFrameDataEx(
  Dem_EventIdType  EventId,
  uint8  RecordNumber,
  uint16  DataId,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)  DestBuffer,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  BufSize
  );

/* ****************************************************************************
 * Dem_GetEventExtendedDataRecordEx
 *****************************************************************************/
/*!
 * \brief         SWC API to read the extended record data of an event.
 *
 * \details       This API is intended to be called via RTE_CALL interface,
 *                as Operation of port interface 'DiagnosticInfo'.
 *
 *                Dem_GetEventExtendedDataRecordEx() copies extended data
 *                available or stored for an event into the passed buffer.
 *                This is particularly useful to retrieve statistic data, like
 *                occurrence counter or aging counter - if these are mapped to
 *                an extended data record.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 * \param[in]     RecordNumber
 *                Extended DataRecord number to read. The record numbers 0xfe
 *                and 0xff are reserved.
 * \param[out]    DestBuffer
 *                Buffer to receive the data.
 * \param[in,out] BufSize
 *                In:  Size of the buffer.
 *                Out: Number of bytes written.
 *
 * \return        E_OK
 *                The requested data was copied to the destination buffer.
 * \return        DEM_NO_SUCH_ELEMENT
 *                The data is not currently stored for the requested event
 *                or
 *                the requested data was not copied due to an undefined
 *                RecordNumber for the given event.
 * \return        E_NOT_OK
 *                The request was rejected, e.g. due to variant coding (see
 *                Dem_SetEventAvailable() )
 *                or
 *                the requested data is currently not accessible (e.g. in case
 *                of asynchronous preempted data retrieval from application).
 * \return        DEM_BUFFER_TOO_SMALL
 *                The provided buffer is too small.
 *
 * \pre           RTE is active (if RTE is used).
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetEventExtendedDataRecordEx(
  Dem_EventIdType  EventId,
  uint8  RecordNumber,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)  DestBuffer,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  BufSize
  );

#if (DEM_CFG_SUPPORT_OVFLIND_API == STD_ON)
/* ****************************************************************************
 * Dem_GetEventMemoryOverflow
 *****************************************************************************/
/*!
 * \brief         Test if an event memory overflowed.
 *
 * \details       This function reports if a DTC was displaced from the given
 *                event memory because the event memory was completely full at
 *                the time. This includes the case of DTCs that did not enter
 *                the event memory for the same reason.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling module.
 * \param[in]     DTCOrigin
 *                Identifier of the event memory concerned:
 *                DEM_DTC_ORIGIN_PRIMARY_MEMORY
 *                DEM_DTC_ORIGIN_PERMANENT_MEMORY
 *                DEM_DTC_ORIGIN_SECONDARY_MEMORY
 * \param[out]    OverflowIndication
 *                Pointer to receive the overflow status:
 *                TRUE: Memory 'DTCOrigin' overflowed
 *                FALSE: Memory 'DTCOrigin' didn't overflow
 *
 * \return        E_OK
 *                Request processed successfully
 * \return        E_NOT_OK
 *                The request was rejected due to invalid arguments
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OVFLIND_API == STD_ON
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetEventMemoryOverflow(
uint8  ClientId,
Dem_DTCOriginType  DTCOrigin,
P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA)  OverflowIndication
);
#endif

#if (DEM_CFG_SUPPORT_OVFLIND_API == STD_ON)
/* ****************************************************************************
 * Dem_GetNumberOfEventMemoryEntries
 *****************************************************************************/
/*!
 * \brief         Gets the number of events currently stored.
 *
 * \details       This function reports the number of event entries occupied
 *                by events. This does not necessarily correspond to the DTC
 *                count read by Dcm due to event combination and other effects
 *                like post-building the OBD relevance of a DTC stored in OBD
 *                permanent memory.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling module.
 * \param[in]     DTCOrigin
 *                Identifier of the event memory concerned:
 *                DEM_DTC_ORIGIN_PRIMARY_MEMORY
 *                DEM_DTC_ORIGIN_PERMANENT_MEMORY
 *                DEM_DTC_ORIGIN_SECONDARY_MEMORY
 * \param[out]    NumberOfEventMemoryEntries
 *                Pointer to receive the event count
 *
 * \return        E_OK
 *                Request processed successfully
 * \return        E_NOT_OK
 *                The request was rejected due to invalid arguments
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OVFLIND_API == STD_ON
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetNumberOfEventMemoryEntries(
uint8  ClientId,
Dem_DTCOriginType  DTCOrigin,                                                                                                  /* PRQA S 1330 */ /* MD_DEM_8.3_rte */
P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)  NumberOfEventMemoryEntries
);
#endif

/* ****************************************************************************
 * Dem_GetEventIdOfDTC
 *****************************************************************************/
/*!
 * \brief         Get the EventId of a DTC.
 *
 * \details       Returns the EventId of the DTC selected by Dem_SelectDTC.
 *
 * \param[in]     ClientId
 *                The client to query
 *
 * \param[out]    EventId
 *                Pointer to receive the EventId
 *
 * \return        E_OK
 *                The requested EventId is stored in EventId
 * \return        DEM_WRONG_DTC
 *                DTC does not exist in the selected origin
 *                OR a DTC group or all DTCs is selected
 *                OR DTC is suppressed
 * \return        DEM_WRONG_DTCORIGIN
 *                Selected origin does not exist
 * \return        E_NOT_OK
 *                No DTC is selected
 * \return        DEM_PENDING
 *                Never returned by this implementation
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           Requires a preceding DTC selection by Dem_SelectDTC.
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   FALSE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetEventIdOfDTC(
  uint8  ClientId,
  P2VAR(Dem_EventIdType, AUTOMATIC, DEM_APPL_DATA)  EventId
  );

                                               /* Service Interface ClearDTC */
/* ------------------------------------------------------------------------- */

/* ****************************************************************************
 * Dem_ClearDTC
 *****************************************************************************/
/*!
 * \brief         Clear DTC memory.
 *
 * \details       Clearing of a DTC clears the stored event data from the event
 *                memory, resets the event status byte and debouncing state.
 *
 *                There are a variety of configuration settings that further
 *                control the behavior of this function:
 *                Configuration option DemClearDTCBehavior controls if the
 *                clear operation is complete when the RAM contents are
 *                cleared, or if the NV-RAM content must be cleared as well.
 *                (NVRAM is updated in all cases.)
 *
 *                Using configuration option DemClearDTCLimitation the API can
 *                be restricted to DTC groups.
 *
 * \param[in]     ClientId
 *                The client to query
 *
 * \return        E_OK
 *                Clearing is completed for the requested DTC(s).
 * \return        DEM_E_WRONG_DTC
 *                The requested DTC is not valid in the context of DTCFormat
 *                and DTCOrigin
 * \return        DEM_E_WRONG_DTCORIGIN
 *                The requested DTC origin is not available
 * \return        DEM_E_FAILED
 *                The clear operation could not be completed
 * \return        DEM_E_CLEAR_MEMORY_ERROR
 *                The clear operation has completed in RAM, but synchronization
 *                to Nv-Ram has failed
 * \return        DEM_E_PENDING
 *                The clear operation is in progress.
 * \return        DEM_E_CLEAR_BUSY
 *                Another clear operation is currently in progress.
 *
 * \pre           -
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   FALSE
 * \reentrant     TRUE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_ClearDTC(
  uint8  ClientId
  );

                                                                      /* DTR */
/* ------------------------------------------------------------------------- */

/* ****************************************************************************
 * Dem_SetDTR
 *****************************************************************************/
/*!
 * \brief         Reports a DTR result with lower and upper limit.
 *
 * \details       Reports a DTR result with lower and upper limit.
 *                Depending on the reported control value and the configured
 *                DTR attributes the DTR values are either ignored, processed
 *                or reset.
 *
 * \param[in]     DTRId
 *                Unique handle of the DTR
 * \param[in]     TestResult
 *                Test Result
 * \param[in]     LowerLimit
 *                Lower Limit
 * \param[in]     UpperLimit
 *                Upper Limit
 * \param[in]     Ctrlval
 *                Dtr Control Value
 *
 * \return        E_OK
 *                Report of DTR result was succesful
 * \return        E_NOT_OK
 *                Report of DTR result failed (or no support for DTR)
 *
 * \pre           -
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetDTR(
  uint16 DTRId,
  sint32 TestResult,
  sint32 LowerLimit,
  sint32 UpperLimit,
  Dem_DTRControlType Ctrlval
  );


/* ****************************************************************************
 * Dem_UpdateAvailableOBDMIDs
 *****************************************************************************/
/*!
 * \brief         Requests the update of the available OBD MIDs.
 *
 * \details       As the visibility status of Dtrs can change during runtime
 *                and therefore MIDs might also not be visible anymore
 *                the application can trigger the update of the available
 *                OBD MIDs.
 *
 *
 * \return        E_OK
 *                Request processed successfully
 * \return        E_NOT_OK
 *                not used
 *
 * \pre           -
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_UpdateAvailableOBDMIDs(
  void
  );


#if (DEM_CFG_SUPPORT_ENABLE_CONDITIONS == STD_ON)
/* ****************************************************************************
 * Dem_GetEventEnableCondition
 *****************************************************************************/
/*!
 * \brief         Query if the events preconditions are fulfilled.
 *
 * \details       This API is an easy way for a monitor to verify (some of)
 *                its preconditions, as these tend to coincide with the
 *                Dem enable conditions for this event.
 *
 *                This API is a MICROSAR extension to the AUTOSAR standard
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 * \param[out]    ConditionFulfilled
 *                TRUE: All enable conditions are fulfilled
 *                FALSE: At least one enable condition is not fulfilled
 *
 * \return        E_OK
 *                Request processed successfully
 * \return        E_NOT_OK
 *                The request was rejected due to invalid arguments or
 *                variant coding (see Dem_SetEventAvailable() )
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_ENABLE_CONDITIONS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE: AR4.0.3, AR4.1.2 FALSE: AR4.2.1
 * \reentrant     TRUE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetEventEnableCondition(
  Dem_EventIdType  EventId,
  P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA)  ConditionFulfilled
  );
#endif

#if (DEM_CFG_SUPPORT_OBD_HIDE_OCCURRENCES == STD_ON)
/* ****************************************************************************
 * Dem_SetHideObdOccurrences
 *****************************************************************************/
/*!
 * \brief         Select Dependent Secondary ECU DTCs visibility mode
 *
 * \details       In primary ECUs, DTCs received from dependent secondary ECUs
 *                can optionally appear in enhanced diagnostic requests (most
 *                subservices of UDS service 0x19).
 *
 *                To select whether a DTC is in fact a dependent secondary ECU
 *                DTC, this logic uses the DemEventSignificance configuration
 *                option.
 *
 *                While the display mode is set to 'hide', all DTCs configured
 *                to support the MIL and marked with significance 'OCCURRENCE'
 *                are omitted from UDS responses that are unrelated to OBD.
 *                Otherwise, all DTCs are reported disregarding the setting of
 *                DemEventSignificance.
 *
 *                The behavior can be changed at any time, using this API. It
 *                is recommended to synchronize changing this setting with
 *                the Dcm service processing to avoid incomplete diagnostic
 *                responses.
 *
 *                This API is a MICROSAR extension to the AUTOSAR standard
 *
 * \param[in]     DoHide
 *                TRUE (default):  Hide 'Occurrence' DTCs
 *                FALSE: Show all DTCs
 *
 * \return        E_OK
 *                Request processed successfully
 * \return        E_NOT_OK
 *                Only in case of detected development errors
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBD_HIDE_OCCURRENCES == STD_ON
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetHideObdOccurrences(
  boolean DoHide
  );
#endif

#if (DEM_CFG_SUPPORT_OBD_HIDE_OCCURRENCES == STD_ON)
/* ****************************************************************************
 * Dem_GetHideObdOccurrences
 *****************************************************************************/
/*!
 * \brief         Read the current setting for displaying Dependent Secondary
 *                ECU DTCs in Dcm responses
 *
 * \details       Read the current setting for displaying Dependent Secondary
 *                ECU DTCs in Dcm responses
 *
 *                This API is a MICROSAR extension to the AUTOSAR standard
 *
 * \param[out]    IsHidden
 *                Pointer to variable receiving the display mode.
 *                TRUE:  'Occurrence' DTCs are omitted
 *                FALSE: All DTCs are included
 *
 * \return        E_OK
 *                Request processed successfully
 * \return        E_NOT_OK
 *                Only in case of detected development errors
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBD_HIDE_OCCURRENCES == STD_ON
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetHideObdOccurrences(
  P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA)  IsHidden
  );
#endif

                                                   /* Interface EcuM <-> Dem */
/* ------------------------------------------------------------------------- */

/* ****************************************************************************
 * Dem_InitMemory
 *****************************************************************************/
/*!
 * \brief         Initialize statically initialized RAM variables
 *
 * \details       Normally the complier start-up code initializes statically
 *                initialized RAM variables of the form
 *                    static var = value;
 *                This function can be used instead, if this task is omitted
 *                from the start-up code.
 *
 *                This API is a MICROSAR extension to the AUTOSAR standard
 *
 * \pre           The Dem may not have been initialized yet. Call this prior to
 *                Dem_PreInit().
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(void, DEM_CODE)
Dem_InitMemory(
  void
  );

                                                              /* Cyclic task */
/* ------------------------------------------------------------------------- */

/* ****************************************************************************
 * Dem_MainFunction
 *****************************************************************************/
/*!
 * \brief         Cyclic Dem task
 *
 * \details       The AUTOSAR conforming way for the Dem asynchronous status
 *                processing and time base. In case the resulting run-time is
 *                too high to guarantee the cycle time, please refer to the
 *                configuration option DemGeneral/DemSupportSplitTasks
 *
 *                This function is basically a wrapper that calls both
 *                Dem_MainFunctionTimer() and Dem_MainFunctionWorker(),
 *                in this order.
 *
 * \pre           Dem has been pre-initialized
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(void, DEM_CODE)
Dem_MainFunction(
  void
);

                                      /* Service Interface DiagnosticMonitor */
/* ------------------------------------------------------------------------- */

/* ****************************************************************************
 * Dem_SetEventDisabled
 *****************************************************************************/
/*!
 * \brief         SWC API to disable an event for the PID 0x41 computation
 *
 * \details       SWC API to disable an event for the PID 0x41 computation in the
 *                current driving cycle
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *
 * \return        E_OK
 *                Event disabled
 *                E_NOT_OK
 *                Event disabling failed OR
 *                'Major Monitor' AND 'Comprehensive Component always complete' disabled
 *
 *
 * \pre           RTE is started (if RTE is used)
 * \config        Feature OBD II or WWHO_OBD is enabled
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventIds.
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetEventDisabled(
  Dem_EventIdType  EventId
  );

                                         /* Service Interface DiagnosticInfo */
/* ------------------------------------------------------------------------- */

/* ****************************************************************************
 * Dem_GetDTCOfEvent
 *****************************************************************************/
/*!
 * \brief         API to read the DTC number for the given EventId
 *
 * \details       This function retrieves the configured DTC number of an event
 *                from the configuration. Since the configuration is not known
 *                until full initialization, this API cannot be called prior
 *                to Dem_Init().
 *
 *                Dem_GetEventTested() is part of the RTE interface, but
 *                but may be called directly as well.

 * \param[in]     EventId
 *                Unique handle of the Event
 * \param[in]     DTCFormat
 *                DEM_DTC_FORMAT_OBD or DEM_DTC_FORMAT_UDS to select which
 *                DTC number is requested
 * \param[out]    DTCOfEvent
 *                Pointer receiving the DTC number

 * \return        E_OK
 *                The request was successful, DTCOfEvent now contains the DTC
 *                value.
 * \return        DEM_E_NO_DTC_AVAILABLE
 *                The event has no DTC in the requested format.
 * \return        E_NOT_OK
 *                The request was rejected, e.g. due to variant coding (see
 *                Dem_SetEventAvailable() )
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 * \trace         CREQ-123114
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetDTCOfEvent(
  Dem_EventIdType  EventId,
  Dem_DTCFormatType  DTCFormat,
  P2VAR(uint32, AUTOMATIC, DEM_APPL_DATA)  DTCOfEvent
  );

/* ****************************************************************************
 * Dem_GetFaultDetectionCounter
 *****************************************************************************/
/*!
 * \brief         SWC API to read the fault detection counter of an event
 *
 * \details       This API is intended to be called via RTE_CALL interface,
 *                as Operation of port interface 'DiagnosticInfo'.
 *
 *                For events that are debounced within the Dem (counter based
 *                and time based debouncing), the internal debouncing state
 *                is converted to an UDS FaultDetectionCounter value in
 *                range [-128..127].
 *
 *                For events that are debounced in application, the configured
 *                callback is invoked to read the current FDC.
 *
 * \param[in]     EventId
 *                Unique handle of the Event
 * \param[out]    FaultDetectionCounter
 *                Pointer receiving the current fault detection counter.
 *
 * \return        E_OK
 *                The FDC was stored into FaultDetectionCounter
 * \return        DEM_E_NO_FDC_AVAILABLE
 *                The event is debounced within the application, but no
 *                callback was configured to read the FDC.
 * \return        E_NOT_OK if
 *                The request was rejected, e.g. due to variant coding (see
 *                Dem_SetEventAvailable() )
 *
 * \pre           RTE is active (if RTE is used)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetFaultDetectionCounter(
  Dem_EventIdType  EventId,
  P2VAR(sint8, AUTOMATIC, DEM_APPL_DATA)  FaultDetectionCounter
  );
                                         /* Service Interface IUMPRNumerator */
/* ------------------------------------------------------------------------- */

/* ****************************************************************************
 * Dem_RepIUMPRFaultDetect
 *****************************************************************************/
/*!
 * \brief         SWC API to report that an asymmetrical monitor is able to
 *                detect a fault
 *
 * \details       This API is intended to be called via RTE_CALL interface,
 *                as Operation of port interface 'IUMPRNumerator'.
 *
 *                For Ratios with DemRatioKind = API a qualified 'passed' test
 *                result is not sufficient to indicate that the monitor could
 *                also have detected a malfunction. This API is used to pass
 *                this information to the Dem module.
 *
 *                Ratios with DemRatioKind = OBSERVER are not allowed to use
 *                this API.
 *
 * \param[in]     RatioID
 *                Unique handle of the Ratio, which is equal to the EventId
 *                associated with the Ratio.
 *
 * \return        E_OK
 *                The monitor status was accepted
 * \return        E_NOT_OK
 *                The request was rejected, e.g. due to invalid arguments or
 *                variant coding (see Dem_SetEventAvailable() )
 *
 * \pre           RTE is active (if RTE is used). Feature IUMPR is supported.
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE for different RatioIds
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_RepIUMPRFaultDetect(
  Dem_RatioIdType  RatioID
  );

/* ****************************************************************************
 * Dem_IUMPRLockNumerators
 *****************************************************************************/
/*!
 * \brief         SWC API to lock all numerators for the currenty DCY
 *
 * \details       If this API is called, numerators are not incremented until
 *                the end ot the current OBD driving cycle.
 *                There is no way to reset but the restart of the current DCY.
 *
 *                This API is a MICROSAR extension to the AUTOSAR standard
 *
 * \return        E_OK
 *                The numerators were locked successfully
 * \return        E_NOT_OK
 *                Only in case of detected development errors
 *
 * \pre           RTE is active (if RTE is used). Feature IUMPR is supported.
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_IUMPRLockNumerators(
  void
  );
                                       /* Service Interface IUMPRDenumerator */
/* ------------------------------------------------------------------------- */

/* ****************************************************************************
 * Dem_RepIUMPRDenLock
 *****************************************************************************/
/*!
 * \brief         SWC API to report preconditions of function specific
 *                denominators
 *
 * \details       This API is intended to be called via RTE_CALL interface,
 *                as Operation of port interface 'IUMPRDenominator'.
 *
 *                After this function is called, increments of Denominator
 *                are blocked. This is only valid for Ratios of
 *                DemIUMPRDenGroup PHYS_API and INDEPENDENT.
 *
 * \attention     The operations Dem_RepIUMPRDenLock() and
 *                Dem_RepIUMPRDenRelease() are not reentrant for the same
 *                RatioId.
 *
 * \param[in]     RatioID
 *                Unique handle of the Ratio, which is equal to the EventId
 *                associated with the Ratio.
 *
 * \return        E_OK
 *                The Ratio was locked successfully
 * \return        E_NOT_OK
 *                The request was rejected due to invalid arguments or
 *                variant coding (see Dem_SetEventAvailable() )
 *
 * \pre           RTE is active (if RTE is used). Feature IUMPR is supported.
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE for different RatioIds
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_RepIUMPRDenLock(
  Dem_RatioIdType  RatioID
  );

/* ****************************************************************************
 * Dem_RepIUMPRDenRelease
 *****************************************************************************/
/*!
 * \brief         SWC API to report preconditions of function specific
 *                denominators
 *
 * \attention     The operations Dem_RepIUMPRDenLock() and
 *                Dem_RepIUMPRDenRelease() are not reentrant for the same
 *                RatioId.
 *
 * \details       This API is intended to be called via RTE_CALL interface,
 *                as Operation of port interface 'IUMPRDenominator'.
 *
 *                After this function is called, increments of Denominator
 *                are enabled. This is only valid for Ratios of 
 *                DemIUMPRDenGroup PHYS_API and INDEPENDENT.
 *
 * \param[in]     RatioID
 *                Unique handle of the Ratio, which is equal to the EventId
 *                associated with the Ratio.
 *
 * \return        E_OK
 *                The ratio was unlocked successfully
 * \return        E_NOT_OK
 *                The request was rejected due to invalid arguments or
 *                variant coding (see Dem_SetEventAvailable() )
 *
 * \pre           RTE is active (if RTE is used). Feature IUMPR is supported.
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE for different RatioIds
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_RepIUMPRDenRelease(
  Dem_RatioIdType  RatioID
  );

/* ****************************************************************************
 * Dem_SetIUMPRDenCondition
 *****************************************************************************/
/*!
 * \brief         SWC API to report preconditions of common denominator groups
 *
 * \details       This API is intended to be called via RTE_CALL interface,
 *                as Operation of port interface 'IUMPRDenominatorCondition'.
 *
 *                Dem_SetIUMPRDenCondition() sets the denominator status
 *                for all RatioIds using the denominator group indicated by
 *                ConditionId. This basically does the same as
 *                Dem_RepIUMPRDenLock() and Dem_RepIUMPRDenRelease(),
 *                but for groups of RatioIds.
 *
 * \param[in]     ConditionId
 *                The denominator group for which the conditions are reported.
 * \param[in]     ConditionStatus
 *                The new status of the given ConditionId
 *
 * \return        E_OK
 *                The new condition status was accepted
 * \return        E_NOT_OK
 *                The new condition status was not accepted
 *
 * \pre           RTE is active (if RTE is used). Feature IUMPR is supported.
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   FALSE
 * \reentrant     TRUE for different ConditionIds
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetIUMPRDenCondition(
     Dem_IumprDenomCondIdType ConditionId,
     Dem_IumprDenomCondStatusType ConditionStatus
  );


/* Service Interface IUMPRData */
/* ------------------------------------------------------------------------- */
/* ****************************************************************************
 * Dem_SetIUMPRFilter
 *****************************************************************************/
/*!
 * \brief         SWC API to set the IUMPR readiness group filter
 *
 * \details       Initializes the readiness group filter for the retrieving APIs
 *                Dem_GetNextIUMPRRatioDataAndDTC() and
 *                Dem_GetCurrentIUMPRRatioDataAndDTC()
 *
 * \param[in]     IumprReadinessGroup
 *                The readiness group which shall be set for filtering
 *
 * \param[in]     DTCOrigin
 *                Identifier of the event memory concerned:
 *                DEM_DTC_ORIGIN_PRIMARY_MEMORY
 *                DEM_DTC_ORIGIN_SECONDARY_MEMORY
 *
 * \return        E_OK
 *                The filter was accepted
 * \return        E_NOT_OK
 *                The filter was not accepted or in case of detected development
 *                errors
 *
 * \pre           Feature IUMPR is supported.
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetIUMPRFilter(
  Dem_IumprReadinessGroupType IumprReadinessGroup,
  Dem_DTCOriginType  DTCOrigin
  );

/* ****************************************************************************
 * Dem_GetNumberOfFilteredIUMPR
 *****************************************************************************/
/*!
 * \brief         SWC API to retrieve the number of filtered IUMPRs
 *
 * \details       Returns the number of IUMPRs matching the filter criteria
 *
 * \param[out]    NumberOfFilteredRatios
 *                The number of ratios matching the filter criteria
 *
 * \return        E_OK
 *                The number of filtered ratios was read successfully
 * \return        E_NOT_OK
 *                Only in case of detected development errors
 *
 * \pre           Feature IUMPR is supported.
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetNumberOfFilteredIUMPR(
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  NumberOfFilteredRatios
  );

/* ****************************************************************************
 * Dem_GetIUMPRGeneralData
 *****************************************************************************/
/*!
 * \brief         SWC API to retrieve general IUMPR data
 *
 * \details       This API copies the respective values to the provided
 *                pointer locations.
 *
 *                This API is a MICROSAR extension to the AUTOSAR standard
 *
 * \param[out]    GeneralDenominator
 *                Value of general denominator
 * \param[out]    IgnitionCycles
 *                Number of ignition cycles
 * \param[out]    IgnitionCyclesHybrid
 *                Number of additional ignition cycles for hybrid vehicles
 *
 * \return        E_OK
 *                The general IUMPR data was read successfully
 * \return        E_NOT_OK
 *                Only in case of detected development errors
 *
 * \pre           Feature IUMPR is supported.
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetIUMPRGeneralData(
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  GeneralDenominator,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  IgnitionCycles,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  IgnitionCyclesHybrid
  );

/* ****************************************************************************
 * Dem_GetNextIUMPRRatioDataAndDTC
 *****************************************************************************/
/*!
 * \brief         SWC API to retrieve the next ratio specific IUMPR data set
 *
 * \details       This function moves the internal iterator to the next Ratio
 *                and copies its DTC numbers as well as Denominator and
 *                Numerator values into the given pointer locations.
 *
 *                If no more Ratios are available (i.e. the iteration has
 *                completed) the function returns E_NOT_OK.
 *
 *                To read the current Ratio again, use
 *                Dem_GetCurrentIUMPRRatioDataAndDTC()
 *
 *                This API is a MICROSAR extension to the AUTOSAR standard
 *
 * \param[out]    UdsDtcNumber
 *                UDS DTC to identify the ratio
 * \param[out]    ObdDtcNumber
 *                OBD DTC to identify the ratio
 * \param[out]    Denominator
 *                The current value of the denominator
 * \param[out]    Numerator
 *                The current value of the numerator
 *
 * \return        E_OK
 *                The ratio specific IUMPR data was read successfully
 * \return        E_NOT_OK
 *                The request was rejected due to invalid arguments, the
 *                iteration has not started (see Dem_GetIUMPRGeneralData() )
 *                or all Ratios were enumerated.
 *
 * \pre           Feature IUMPR is supported.
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetNextIUMPRRatioDataAndDTC(
  P2VAR(uint32, AUTOMATIC, DEM_APPL_DATA)  UdsDtcNumber,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  ObdDtcNumber,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  Denominator,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  Numerator
  );

/* ****************************************************************************
 * Dem_GetCurrentIUMPRRatioDataAndDTC
 *****************************************************************************/
/*!
 * \brief         SWC API to retrieve the current ratio specific IUMPR data set
 *
 * \details       This function copies the current Ratios DTC numbers as well
 *                as Denominator and Numerator values into the given pointer
 *                locations. This works only if
 *                Dem_GetNextIUMPRRatioDataAndDTC() has already moved the
 *                internal iterator to a valid Ratio.
 *
 *                This API is a MICROSAR extension to the AUTOSAR standard
 *
 * \param[out]    UdsDtcNumber
 *                UDS DTC to identify the ratio
 * \param[out]    ObdDtcNumber
 *                OBD DTC to identify the ratio
 * \param[out]    Denominator
 *                The current value of the denominator
 * \param[out]    Numerator
 *                The current value of the numerator
 *
 * \return        E_OK
 *                The ratio specific IUMPR data was read successfully
 * \return        E_NOT_OK
 *                The request was rejected due to invalid arguments, the
 *                iteration has not returned a valid Ratio yet (see
 *                Dem_GetIUMPRGeneralData() and
 *                Dem_GetNextIUMPRRatioDataAndDTC() ) or the event became
 *                unavailable or suppressed during the iteration
 *
 *
 * \pre           Feature IUMPR is supported.
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetCurrentIUMPRRatioDataAndDTC(
  P2VAR(uint32, AUTOMATIC, DEM_APPL_DATA)  UdsDtcNumber,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  ObdDtcNumber,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  Denominator,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  Numerator
  );

                                         /* Service Interface EventAvailable */
/* ------------------------------------------------------------------------- */

#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
/* ****************************************************************************
 * Dem_GetEventAvailable
 *****************************************************************************/
/*!
 * \brief         Get event configuration
 *
 * \details       This function returns if an events is present or not in a
 *                given configuration. The main use case is related to variant
 *                coding, this is a run-time way to check if an event is
 *                currently removed (see Dem_SetEventAvailable()
 *
 *                Variant coding can be achieved using PostBuild Selectable
 *                when the event availability is known statically based on few
 *                ECU configurations.
 *
 *                This API is a MICROSAR extension to the AUTOSAR standard
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 * \param[out]    AvailableStatus
 *                TRUE: Event is available
 *                FALSE: Event is not available
 *
 * \return        E_OK
 *                The request was processed successfully
 * \return        E_NOT_OK
 *                The request was rejected due to invalid arguments or state.
 *                In this case, AvailableStatus will not be initialized.
 *
 * \pre           If DEM_CFG_SUPPORT_EVENTAVAILABLE_NV == STD_ON, the Dem must
 *                be initialized. Otherwise this API is available after
 *                pre-initialization.
 * \config        DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE (for different EventIds)
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetEventAvailable(
  Dem_EventIdType  EventId,
  P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA)  AvailableStatus
  );
#endif /* (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON) */

                                        /* Service Interface EnableCondition */
/* ------------------------------------------------------------------------- */
                                               /* Permanent Fault Code Cycle */
/* ------------------------------------------------------------------------- */
#if (DEM_CFG_SUPPORT_OBDII == STD_ON) && (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/* ****************************************************************************
 * Dem_SetPfcCycleQualified
 *****************************************************************************/
/*!
 * \brief         Report the pfc conditions
 *
 * \details       This API must be called once per driving cycle when the pfc
 *                conditions are met.
 *                The former API name 'Dem_SetPfcCycle' can still be used.
 *
 * \return        E_OK
 *                Request processed successfully
 * \return        E_NOT_OK
 *                Only in case of detected development errors
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON &&
 *                DEM_CFG_SUPPORT_PERMANENT == STD_ON
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetPfcCycleQualified(
  void
  );
#endif /* (DEM_CFG_SUPPORT_OBDII == STD_ON) && (DEM_CFG_SUPPORT_PERMANENT == STD_ON) */

/* Compatibility define */
#define Dem_SetPfcCycle                          Dem_SetPfcCycleQualified

                                             /* Permanent Storage Activation */
/* ------------------------------------------------------------------------- */

#if (DEM_CFG_SUPPORT_PERMANENTDTC_ACTIVATION_DISTANCE == STD_ON)
/* ****************************************************************************
 * Dem_EnablePermanentStorage
 *****************************************************************************/
/*!
 * \brief         Activates permanent storage
 *
 * \details       For production purposes the permanent storage can be delayed
 *                for some time. This API is used to activate the permanent
 *                storage.
 *
 *                If the permanent storage is not enabled actively, the Dem
 *                will enable it when receiving a configured odometer value.
 *
 *                This API is a MICROSAR extension to the AUTOSAR standard
 *
 * \return        E_OK
 *                Request processed successfully
 * \return        E_NOT_OK
 *                Only in case of detected development errors
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PERMANENTDTC_ACTIVATION_DISTANCE == STD_ON
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_EnablePermanentStorage(
  void
  );
#endif /*(DEM_CFG_SUPPORT_PERMANENTDTC_ACTIVATION_DISTANCE == STD_ON) */

#if (DEM_CFG_SUPPORT_PERMANENTDTC_ACTIVATION_DISTANCE == STD_ON)
/* ****************************************************************************
 * Dem_GetPermanentStorageState
 *****************************************************************************/
/*!
 * \brief         Get state of permanent storage
 *
 * \details       Reads the activation state of the permanent DTC storage. If
 *                this returns TRUE via the out parameter isEnabled, permanent
 *                DTC handling is active.
 *
 *                This API is a MICROSAR extension to the AUTOSAR standard
 *
 * \param[out]    isEnabled
 *                Pointer to the variable receiving the activation state
 *
 * \return        E_OK
 *                Request processed successfully
 * \return        E_NOT_OK
 *                Only in case of detected development errors
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PERMANENTDTC_ACTIVATION_DISTANCE == STD_ON
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetPermanentStorageState(
  P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA)  isEnabled
  );
#endif /*  (DEM_CFG_SUPPORT_PERMANENTDTC_ACTIVATION_DISTANCE == STD_ON) */

                                                               /* B1 Counter */
/* ------------------------------------------------------------------------- */
#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 % Dem_GetB1Counter
 *****************************************************************************/
/*!
 * \brief         Read the B1 counter value
 *
 * \details       The Dem module supports the global B1 counter variant defined
 *                in the GTR. This API returns its current value.
 *
 * \param[out]    B1Counter
 *                Pointer to the variable receiving the B1 counter value
 *
 * \return        E_OK
 *                Request processed successfully
 * \return        E_NOT_OK
 *                Only in case of detected development errors
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_WWHOBD == STD_ON
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetB1Counter(
  P2VAR(uint16, AUTOMATIC, DEM_DCM_DATA)  B1Counter
  );
#endif /* (DEM_CFG_SUPPORT_WWHOBD == STD_ON) */

                                                                /* PID Data */
/* ------------------------------------------------------------------------- */
#if (DEM_CFG_SUPPORT_PID01 == STD_ON)
/* ****************************************************************************
 * Dem_ReadDataOfPID01
 *****************************************************************************/
/*!
 * \brief         Read the monitoring status since DTCs cleared
 *
 * \details       Copies the 4 bytes of PID01, formatted this way:
 *                supported - 0 == FALSE; 1 == TRUE
 *                ready     - 0 == TRUE; 1 == FALSE
 *
 *                Byte 0
 *                  bit 0...6 - # of DTCs stored in this ECU
 *                  bit 7 - Malfunction Indicator Lamp (MIL) Status
 *
 *                Byte 1
 *                  bit 0 - Misfire monitoring supported
 *                  bit 1 - Fuel system monitoring supported
 *                  bit 2 - Comprehensive component monitoring supported
 *                  bit 3 - Compression ignition monitoring supported
 *                  bit 4 - Misfire monitoring ready
 *                  bit 5 - Fuel system monitoring ready
 *                  bit 6 - Comprehensive component monitoring ready
 *                  bit 7 - reserved
 *
 *                Byte 2
 *                  bit 0 - Catalyst monitoring supported
 *                  bit 1 - Heated catalyst monitoring supported
 *                  bit 2 - Evaporative system monitoring supported
 *                  bit 3 - Secondary air system monitoring supported
 *                  bit 4 - reserved
 *                  bit 5 - Oxygen sensor monitoring supported
 *                  bit 6 - Oxygen sensor heater monitoring
 *                  bit 7 - EGR system monitoring supported
 *
 *                Byte3
 *                  bit 0 - Catalyst monitoring ready
 *                  bit 1 - Heated catalyst monitoring ready
 *                  bit 2 - Evaporative system monitoring ready
 *                  bit 3 - Secondary air system monitoring ready
 *                  bit 4 - reserved
 *                  bit 5 - Oxygen sensor monitoring ready
 *                  bit 6 - Oxygen sensor heater monitoring ready
 *                  bit 7 - EGR system monitoring ready
 *
 * \param[out]    PID01value
 *                Pointer to the buffer receiving the current PID01 value
 *
 * \return        E_OK
 *                Request processed successfully
 * \return        E_NOT_OK
 *                Only in case of detected development errors
 *
 * \pre           -
 * \config        (DEM_CFG_SUPPORT_PID01 == STD_ON)
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_ReadDataOfPID01(
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  PID01value
  );
#endif /* ((DEM_CFG_SUPPORT_OBDII == STD_ON) || (DEM_CFG_SUPPORT_WWHOBD == STD_ON)) && (DEM_CFG_SUPPORT_PID01 == STD_ON) */

                                                     /* Extension to Autosar */
/* ------------------------------------------------------------------------- */

/* ****************************************************************************
 * Dem_PostRunRequested
 *****************************************************************************/
/*!
 * \brief         Test whether the Dem can be shut down safely
 *
 * \details       This function must be polled after leaving RUN mode (all
 *                application monitors have been stopped). Due to pending NvM
 *                activity, data loss is possible if Dem_Shutdown is called
 *                while this function still returns TRUE.
 *
 *                This situation only occurs if the dem has to persist two
 *                data changes for the same Event. Basically, the first change
 *                needs to complete the writing process before the Dem can
 *                finalize its state to allow shutdown. Until that time, the
 *                Dem, NvM and the memory stack need to continue running.
 *
 *                As soon as the NvM finishes writing the current Dem data
 *                block, this function will return FALSE. The delay time to
 *                enable shutdown only depends on the write time of that one
 *                data block.
 *
 *                This API is a MICROSAR extension to the AUTOSAR standard
 *
 * \param[out]    IsRequested
 *                TRUE:  Shutdown is not possible without data loss.
 *                FALSE: Shutdown is possible.
 *
 * \return        E_OK
 *                Request processed successfully
 * \return        E_NOT_OK
 *                Only in case of detected development errors
 *
 * \pre           -
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_PostRunRequested(
  P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA)  IsRequested
  );

/* ****************************************************************************
 * Dem_SetSI30Symptom
 *****************************************************************************/
/*!
 * \brief         This function is called by the FiM to report "Symptom
 *                Reached" condition for an event.
 *
 * \details       This function is called by the FiM to report "Symptom
 *                Reached" condition for an event. It queues an action that
 *                sets the SSLC bit of the Status Indicator byte of the 
 *                specified event.
 *
 *                This API is a MICROSAR extension to the AUTOSAR standard.
 *
 * \param[in]     EventId
 *                Unique handle of the Event to report.
 *
 * \return        E_OK
 *                StatusIndicator symptom action queued.
 *                E_NOT_OK
 *                StatusIndicator symptom action queue failed.
 *
 * \pre           Features StatusIndicator and Extended FiM are enabled.
 *
 * \context       TASK|ISR2, from the satellite partition only.
 * \synchronous   FALSE
 * \reentrant     TRUE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetSI30Symptom(
  Dem_EventIdType EventId
  );

/* ****************************************************************************
 * Dem_GetSI30Status
 *****************************************************************************/
/*!
 * \brief         This function is called by the FiM to get the StatusIndicator
 *                byte of the specified event.
 *
 * \details       This function is called by the FiM to get the StatusIndicator
 *                byte of the specified event.
 *
 *                Dem_GetSI30Status() is part of the RTE interface, but
 *                may be called directly as well.
 *
 *                This API is a MICROSAR extension to the AUTOSAR standard.
 *
 * \param[in]     EventId
 *                Unique handle of the Event to report.
 * \param[out]    Status
 *                Status Indicator byte containing the status bits:
 *                Bit0: DEM_STATUSINDICATOR30_UDTC
 *                Bit1: DEM_STATUSINDICATOR30_UDTCTOC
 *                Bit2: DEM_STATUSINDICATOR30_UDTCSLC
 *                Bit3: DEM_STATUSINDICATOR30_ADTC
 *                Bit4: DEM_STATUSINDICATOR30_SSLC
 *                Bit5: DEM_STATUSINDICATOR30_WIRSLC
 *                Bit6: DEM_STATUSINDICATOR30_ERDTC
 *                Bit7: DEM_STATUSINDICATOR30_TFSLC
 *
 * \return        E_OK
 *                Status Indicator byte stored to the Status pointer.
 *                E_NOT_OK
 *                Status Indicator byte NOT stored to the Status pointer.
 *
 * \pre           Features StatusIndicator and Extended FiM are enabled.
 *
 * \context       TASK|ISR2, from the satellite partition only.
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventIds.
*****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetSI30Status(
  Dem_EventIdType EventId,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) Status
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/***********************************************************************************************************************
 *  EXCLUSIVE AREA DEFINITION
 **********************************************************************************************************************/
/*! \page allEA Exclusive Areas
 * \exclusivearea DEM_EXCLUSIVE_AREA_0 (DiagMonitor)
 * Ensures consistency and atomicity of event reports.
 * \protects
 * Dem_Cfg_CombinedGroupInternalStatus
 * Dem_Cfg_EventInternalStatus
 * Dem_Cfg_ObdIumprData.Status
 * Dem_Cfg_StatusData.ExtendedEventStatus
 * Dem_Cfg_Prestorage<X>.EventId
 * Dem_Cfg_Prestorage<X>.State
 * Dem_Prestore_FreeListHeadIndex
 * Dem_Queue_Pid01UpdateFlag
 * Dem_Cfg_DtrData.TestValue
 * Dem_Cfg_DtrData.LowLimValue
 * Dem_Cfg_DtrData.UppLimValue
 * \usedin
 * Dem_ClearPrestoredFreezeFrame
 * Dem_DcmGetDTRData
 * Dem_Init
 * Dem_IUMPRLockNumerators
 * Dem_Iumpr_RestartDcy
 * Dem_MainFunction
 * Dem_MasterInit
 * Dem_MasterMainFunction
 * Dem_PrestoreFreezeFrame
 * Dem_RepIUMPRDenLock
 * Dem_RepIUMPRDenRelease
 * Dem_RepIUMPRFaultDetect
 * Dem_ReportErrorStatus
 * Dem_SetDTCSuppression
 * Dem_SetDTR
 * Dem_SetEventAvailable
 * Dem_SetEventStatus
 * Dem_SetIUMPRDenCondition
 * Dem_SetWIRStatus
 * Dem_Shutdown
 *
 * \exclude N/A
 * \length MEDIUM Resetting ratios blocked by FIDs must iterate all ratios, but
 *                releases the critical sections regularly.
 *         SHORT  In all other cases.
 * \endexclusivearea
 *
 ******************************************************************************
 *
 * \exclusivearea DEM_EXCLUSIVE_AREA_1 (StateManager)
 * Ensures consistent status updates when receiving ECU states managed outside
 * the Dem.
 *
 * \protects
 * Dem_Cfg_AdminData.ObdCycleState
 * Dem_Cfg_EnableConditionGroupCounter
 * Dem_Cfg_StorageConditionGroupCounter
 * Dem_Cfg_EnableConditionGroupState
 * Dem_OperationCycle_CycleFlag
 * Dem_OperationCycle_PendingCycleState
 *
 * \usedin
 * Dem_DisableDTCSetting
 * Dem_EnableDTCSetting
 * Dem_Init
 * Dem_MainFunction
 * Dem_MasterInit
 * Dem_MasterMainFunction
 * Dem_SetEnableCondition
 * Dem_SetOperationCycleState
 * Dem_SetPfcCycleQualified
 * Dem_SetStorageCondition
 * Dem_Shutdown
 *
 * \exclude N/A
 * \length LONG   Setting enable/storage conditions will update all
 *                enable/storage condition groups.
 * \length MEDIUM Updating the operation cycle queue state will use a couple of
 *                IF statements.
 * \length SHORT  Setting the PFC cycle.
 * \endexclusivearea
 *
 ******************************************************************************
 *
 * \exclusivearea DEM_EXCLUSIVE_AREA_2 (DcmAPI)
 * Ensures consistent status updates when receiving ECU states managed outside
 * the Dem.
 *
 * \protects
 * Dem_Cfg_AdminData.PermanentActivationState (transition off->on)
 * Dem_ClearTask_ClearRequest
 * Dem_Cfg_ReadoutBuffer.State (transition from QUEUED)
 * Dem_Cfg_TimeSeriesEntry.ReadoutStatus
 * Dem_Cfg_TimeSeriesEntry.ClientCounter
 *
 * \usedin
 * Dem_ClearDTC
 * Dem_EnableDTCRecordUpdate
 * Dem_EnablePermanentStorage
 * Dem_J1939DcmClearDTC
 * Dem_MainFunction
 * Dem_MasterMainFunction
 * Dem_SelectDTC
 *
 * \exclude N/A
 * \length MEDIUM Clear request polling requires atomic comparison of multiple
 *                values.
 * \endexclusivearea
 *
 ******************************************************************************
 *
 * \exclusivearea DEM_EXCLUSIVE_AREA_3 (CrossCoreComm)
 * Ensures consistent prestorage when called from multiple clients.
 * Ensures data consistency between satellites and master, if the platform does
 * not provide a specific CompareAndSwap instruction.
 *
 * \protects
 * Dem_Cfg_SatelliteInfo<X>.SatelliteData
 * Dem_Cfg_SatelliteInfo<X>.SatelliteExtendedData
 * Dem_Cfg_SatelliteInfo<X>.SatelliteStatus
 * Dem_Scheduler_ScheduledSingleInvocationTasks
 * Dem_Scheduler_ScheduledMultipleInvocationTasks
 *
 * \usedin
 * Dem_ClearDTC
 * Dem_ClearPrestoredFreezeFrame
 * Dem_DisableDTCRecordUpdate
 * Dem_DisableDTCSetting
 * Dem_EnableDTCSetting
 * Dem_Init
 * Dem_J1939DcmClearDTC
 * Dem_MainFunction
 * Dem_MasterInit
 * Dem_MasterMainFunction
 * Dem_PrestoreFreezeFrame
 * Dem_RepIUMPRDenRelease
 * Dem_RepIUMPRFaultDetect
 * Dem_ReportErrorStatus
 * Dem_ResetEventDebounceStatus
 * Dem_ResetEventStatus
 * Dem_SatelliteInit
 * Dem_SatelliteMainFunction
 * Dem_SetDTR
 * Dem_SetEnableCondition
 * Dem_SetEventAvailable
 * Dem_SetEventStatus
 * Dem_SetIUMPRDenCondition
 * Dem_SetOperationCycleState
 *
 * \exclude N/A
 * \length SHORT Single read and write access to RAM.
 * \endexclusivearea
 *
  ******************************************************************************
 *
 * \exclusivearea DEM_EXCLUSIVE_AREA_4 (NonAtomic32bit)
 * Ensures consistency if the platform doesn't provide an atomic 32 bit access.
 *
 * \protects
 * Dem_Cfg_AdminData.OdometerAtClear
 * Dem_Cfg_AdminData.OdometerMilOn
 *
 * \usedin
 * Dem_DcmReadDataOfPID21
 * Dem_DcmReadDataOfPID31
 * Dem_Init
 * Dem_MainFunction
 * Dem_MasterInit
 * Dem_MasterMainFunction
 * Dem_Shutdown
 *
 * \exclude N/A
 * \length SHORT Single read and write access to RAM.
 * \endexclusivearea
 */

/*!
 * \}
 */

#endif  /* DEM_H */

/* ********************************************************************************************************************
 *  END OF FILE: Dem.h
 *********************************************************************************************************************/
