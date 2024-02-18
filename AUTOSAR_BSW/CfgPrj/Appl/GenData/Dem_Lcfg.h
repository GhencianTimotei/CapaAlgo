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
 *            Module: Dem
 *           Program: VAG AR4 (MSR_Vag_SLP5)
 *          Customer: Huf H_lsbeck & F_rst GmbH & Co. KG
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: S32K144
 *    License Scope : The usage is restricted to CBD2100188_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: Dem_Lcfg.h
 *   Generation Time: 2024-01-27 22:50:09
 *           Project: DaVinciConfigurationS32K144 - Version 1.0
 *          Delivery: CBD2100188_D01
 *      Tool Version: DaVinci Configurator  5.23.45 SP4
 *
 *
 *********************************************************************************************************************/


/* configuration, interrupt handling and callback headers use different names
 * for the multiple inclusion protection define, shown in this example. The
 * appropriate names for these files can be taken from this list:
 *
 * Dem_Cfg.h:                   DEM_CFG_H
 * Dem_Lcfg.h:                  DEM_LCFG_H
 * Dem_PBcfg.h:                 DEM_PBFG_H
 * Dem_AdditionalIncludeCfg.h:  DEM_ADDITIONALINCLUDECFG_H
 * Dem_Swc.h:                   DEM_SWC_H
 * Dem_Swc_Types.h:             DEM_SWC_TYPES_H
 */
#if !defined (DEM_LCFG_H)
# define DEM_LCFG_H

/**********************************************************************************************************************
  MISRA JUSTIFICATIONS
**********************************************************************************************************************/

/* PRQA S 0777 EOF */ /* MD_MSR_Rule5.1 */                                          /* External identifier does not differ in 32 significant characters */
/* PRQA S 0779 EOF */ /* MD_MSR_Rule5.2 */                                          /* Identifier does not differ in 32 significant characters */


/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
#include "Dem_SatelliteData_Types.h"
#include "Dem_DTCSelector_Types.h"
#include "Dem_FilterData_Types.h"
#include "Dem_FreezeFrameIterator_Types.h"
#include "Dem_ClearDTC_Types.h"
#include "Dem_Event_Types.h"
#include "Dem_DTCReadoutBuffer_Types.h"
#include "Dem_MemoryEntry_Types.h"
#include "Dem_ERec_Types.h"
#include "Dem_0x1956_Types.h"

#include "Os.h"                                                                           /* get: ApplicationType    */

/**********************************************************************************************************************
  GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/** 
  \defgroup  Dem_CfgPCDataSwitches  Dem_Cfg Data Switches  (PRE_COMPILE)
  \brief  These defines are used to deactivate data and their processing.
  \{
*/ 
#define DEM_CFG_ADMINDATA                                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_AGINGDATA                                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_CALLBACKCLEAREVENTALLOWED                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_CALLBACKDTCSTATUSCHANGED                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_CALLBACKGETFDC                                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_CALLBACKJ1939DTCSTATUSCHANGED                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_CLEARDTCTABLE                                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_CLEARDTCNOTIFICATIONFINISHTABLE                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_CLEARDTCNOTIFICATIONSTARTTABLE                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_CLIENTTABLE                                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_CLEARDTCINDEXOFCLIENTTABLE                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_FILTERINDEXOFCLIENTTABLE                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_FREEZEFRAMEITERATORINDEXOFCLIENTTABLE                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_NMNODEIDOFCLIENTTABLE                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_READOUTBUFFERINDEXOFCLIENTTABLE                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SELECTORINDEXOFCLIENTTABLE                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_COMMITBUFFER                                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_CONFIGURATIONID                                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_CYCLECOUNTERDATA                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_CYCLEIDTABLE                                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_ENDSONINITOFCYCLEIDTABLE                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_MASKEDBITSOFCYCLEIDTABLE                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_OPCYCLETYPEOFCYCLEIDTABLE                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_USEDFORAGINGOFCYCLEIDTABLE                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DTCSELECTORTABLE                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DATACOLLECTIONTABLE                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_COLLECTIONSIZEOFDATACOLLECTIONTABLE                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DATAELEMENTTABLECOL2ELMTINDENDIDXOFDATACOLLECTIONTABLE                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DATAELEMENTTABLECOL2ELMTINDSTARTIDXOFDATACOLLECTIONTABLE                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DATAELEMENTTABLECOL2ELMTINDUSEDOFDATACOLLECTIONTABLE                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DIDOFFSETFASTOFDATACOLLECTIONTABLE                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DIDOFFSETNORMALOFDATACOLLECTIONTABLE                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_EVENTTABLE_EREC2EVENTIDINDENDIDXOFDATACOLLECTIONTABLE                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_EVENTTABLE_EREC2EVENTIDINDSTARTIDXOFDATACOLLECTIONTABLE                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_EVENTTABLE_EREC2EVENTIDINDUSEDOFDATACOLLECTIONTABLE                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_IDNUMBEROFDATACOLLECTIONTABLE                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_STORAGEKINDOFDATACOLLECTIONTABLE                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_TRIGGEROFDATACOLLECTIONTABLE                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_UPDATEOFDATACOLLECTIONTABLE                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DATACOLLECTIONTABLEEDR2COLLIND                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DATACOLLECTIONTABLEEREC2COLLIND                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DATACOLLECTIONTABLEFFM2COLLIND                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DATACOLLECTIONTABLEJ19392COLLIND                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DATACOLLECTIONTABLEPID2COLLIND                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DATAELEMENTTABLE                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DATAISSTOREDINNVOFDATAELEMENTTABLE                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_ELEMENTKINDOFDATAELEMENTTABLE                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_ELEMENTSIZEOFDATAELEMENTTABLE                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_READDATAFUNCOFDATAELEMENTTABLE                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DATAELEMENTTABLECOL2ELMTIND                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DEBOUNCEDATA                                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DEBOUNCEHIRESTABLE                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DEBOUNCELORESTABLE                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DEBOUNCETABLE                                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DEBOUNCECONTINUOUSOFDEBOUNCETABLE                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DECREMENTSTEPSIZEOFDEBOUNCETABLE                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_EVENTDEBOUNCEALGORITHMOFDEBOUNCETABLE                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_EVENTDEBOUNCEBEHAVIOROFDEBOUNCETABLE                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_FAILTIMERCYCLESOFDEBOUNCETABLE                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_FAILEDTHRESHOLDOFDEBOUNCETABLE                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_INCREMENTSTEPSIZEOFDEBOUNCETABLE                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_JUMPDOWNOFDEBOUNCETABLE                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_JUMPDOWNVALUEOFDEBOUNCETABLE                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_JUMPUPOFDEBOUNCETABLE                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_JUMPUPVALUEOFDEBOUNCETABLE                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_MASKEDBITSOFDEBOUNCETABLE                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_PASSTIMERCYCLESOFDEBOUNCETABLE                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_PASSEDTHRESHOLDOFDEBOUNCETABLE                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_PRECONFIRMEDTHRESHOLDOFDEBOUNCETABLE                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_STORAGEOFDEBOUNCETABLE                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_STORAGETHRESHOLDOFDEBOUNCETABLE                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_STORAGETIMERCYCLESOFDEBOUNCETABLE                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DTCGROUPMASK                                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_GROUPMASKOFDTCGROUPMASK                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_UDSGROUPDTCOFDTCGROUPMASK                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DTCTABLE                                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DTCSEVERITYOFDTCTABLE                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_FUNCTIONALUNITOFDTCTABLE                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_IMMEDIATENVSTORAGEOFDTCTABLE                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_J1939DTCOFDTCTABLE                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_J1939NODEIDINDENDIDXOFDTCTABLE                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_J1939NODEIDINDSTARTIDXOFDTCTABLE                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_J1939NODEIDINDUSEDOFDTCTABLE                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_OBDDTCOFDTCTABLE                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_UDSDTCOFDTCTABLE                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DTRDATA                                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DTRSTATUS                                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DTRTABLE                                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DIVISOROFDTRTABLE                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_EVENTTABLEIDXOFDTRTABLE                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_LINEARFACTOROFDTRTABLE                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_OFFSETOFDTRTABLE                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_UASIDOFDTRTABLE                                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_UPDATEKINDOFDTRTABLE                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DTRTABLEIND                                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_ENABLECONDITIONFULFILLED                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_ENABLECONDITIONGROUPCOUNTER                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_ENABLECONDITIONGROUPSTATE                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_ENABLECONDITIONGROUPTABLE                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_INDEXOFENABLECONDITIONGROUPTABLE                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_ENABLECONDITIONGROUPTABLEIND                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_ENABLECONDITIONINITTABLE                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_FULFILLEDATINITOFENABLECONDITIONINITTABLE                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_ENABLECONDITIONTABLE                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_ENABLECONDITIONGROUPTABLEINDENDIDXOFENABLECONDITIONTABLE                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_ENABLECONDITIONGROUPTABLEINDSTARTIDXOFENABLECONDITIONTABLE                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_ENABLECONDITIONGROUPTABLEINDUSEDOFENABLECONDITIONTABLE                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_EVENTAVAILABLEDATA                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_EVENTAVAILABLEDEFAULT                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_EVENTAVAILABLEINVARIANT                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_EVENTCYCLESTATUS                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_EVENTDATACHANGED                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_EVENTDATACOMMITNUMBER                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_EVENTDEBOUNCEVALUE                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_EVENTINTERNALSTATUS                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_EVENTSTATUSCHANGED                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_EVENTTABLE                                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_AGINGALLOWEDOFEVENTTABLE                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_AGINGCYCLECOUNTERTHRESHOLDOFEVENTTABLE                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_AGINGCYCLEIDOFEVENTTABLE                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_CALLBACKCLEAREVENTALLOWEDIDXOFEVENTTABLE                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_CALLBACKCLEAREVENTALLOWEDUSEDOFEVENTTABLE                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_CALLBACKGETFDCIDXOFEVENTTABLE                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DEBOUNCETABLEIDXOFEVENTTABLE                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DTCTABLEIDXOFEVENTTABLE                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DTRTABLEINDENDIDXOFEVENTTABLE                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DTRTABLEINDSTARTIDXOFEVENTTABLE                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DTRTABLEINDUSEDOFEVENTTABLE                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_ENABLECONDITIONGROUPTABLEIDXOFEVENTTABLE                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_EVENTDESTINATIONOFEVENTTABLE                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_EVENTFAILURECYCLECOUNTERTHRESHOLDOFEVENTTABLE                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_EVENTKINDOFEVENTTABLE                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_EVENTLATCHTFOFEVENTTABLE                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_EVENTPRIORITYOFEVENTTABLE                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_EVENTSIGNIFICANCEOFEVENTTABLE                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_EXTENDEDDATATABLEIDXOFEVENTTABLE                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_FAILEDCYCLECOUNTERINDEXOFEVENTTABLE                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_FAULTPENDINGCOUNTERINDEXOFEVENTTABLE                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_FREEZEFRAMENUMTABLEENDIDXOFEVENTTABLE                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_FREEZEFRAMENUMTABLESTARTIDXOFEVENTTABLE                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_FREEZEFRAMENUMTABLEUSEDOFEVENTTABLE                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_FREEZEFRAMETABLESTDFFIDXOFEVENTTABLE                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_HEALINGTARGETOFEVENTTABLE                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_MASKEDBITSOFEVENTTABLE                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_OBDVISIBILITYDELAYEDUNTILDCYQUALIFICATIONOFEVENTTABLE                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_OPERATIONCYCLEIDOFEVENTTABLE                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SATELLITEEVENTIDXOFEVENTTABLE                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SATELLITEINFOIDXOFEVENTTABLE                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SPECIALINDICATORTABLEENDIDXOFEVENTTABLE                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SPECIALINDICATORTABLESTARTIDXOFEVENTTABLE                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SPECIALINDICATORTABLEUSEDOFEVENTTABLE                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_EVENTTABLEIND                                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_EVENTTABLE_EREC2EVENTIDIND                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_EVENTTABLE_OBDRDYGROUP2EVENTIDIND                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_EXTENDEDDATARECORDITERATORTABLE                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_EXTENDEDDATARECORDTABLE                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DATACOLLECTIONTABLEEREC2COLLINDENDIDXOFEXTENDEDDATARECORDTABLE                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DATACOLLECTIONTABLEEREC2COLLINDSTARTIDXOFEXTENDEDDATARECORDTABLE                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DATACOLLECTIONTABLEEREC2COLLINDUSEDOFEXTENDEDDATARECORDTABLE                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_EXTENDEDDATATABLE                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DATACOLLECTIONTABLEEDR2COLLINDENDIDXOFEXTENDEDDATATABLE                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DATACOLLECTIONTABLEEDR2COLLINDSTARTIDXOFEXTENDEDDATATABLE                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DATACOLLECTIONTABLEEDR2COLLINDUSEDOFEXTENDEDDATATABLE                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_MAXRECORDSIZEOFEXTENDEDDATATABLE                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_FILTERINFOTABLE                                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_FILTERREPORTEDEVENTS                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_FINALMAGICNUMBER                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_FREEZEFRAMEDATA                                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_FREEZEFRAMEITERATORTABLE                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_FREEZEFRAMENUMTABLE                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_FFNUMBEROFFREEZEFRAMENUMTABLE                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_FFTRIGGEROFFREEZEFRAMENUMTABLE                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_FFUPDATEOFFREEZEFRAMENUMTABLE                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_FREEZEFRAMETABLE                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DATACOLLECTIONTABLEFFM2COLLINDENDIDXOFFREEZEFRAMETABLE                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DATACOLLECTIONTABLEFFM2COLLINDSTARTIDXOFFREEZEFRAMETABLE                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DATACOLLECTIONTABLEFFM2COLLINDUSEDOFFREEZEFRAMETABLE                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_RECORDSIZEOFFREEZEFRAMETABLE                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_RECORDSIZEUDSOFFASTRATETIMESERIESPOWERTRAINOFFREEZEFRAMETABLE                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_RECORDSIZEUDSOFFREEZEFRAMETABLE                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_RECORDSIZEUDSOFNORMALRATETIMESERIESPOWERTRAINOFFREEZEFRAMETABLE                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_GENERALJ1939TABLE                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DATACOLLECTIONTABLEJ19392COLLINDENDIDXOFGENERALJ1939TABLE                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DATACOLLECTIONTABLEJ19392COLLINDSTARTIDXOFGENERALJ1939TABLE                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DATACOLLECTIONTABLEJ19392COLLINDUSEDOFGENERALJ1939TABLE                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_RECORDSIZEOFGENERALJ1939TABLE                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_GENERALOBDINPUT                                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DATAELEMENTTABLEIDXOFGENERALOBDINPUT                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_GLOBALINDICATORSTATES                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_GLOBALOBDREQUIREMENTS                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_GLOBALSEVERITYMASK                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_INDICATORBLINKING                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_INDICATORCONTINUOUS                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_INDICATORFASTFLASH                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_INDICATORSLOWFLASH                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_INITDATAHASHCODE                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_INITMONLISTFORFUNC                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_INITMONITORFOREVENT                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_INITMONITORSFORFUNC                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_J1939NODEID                                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_J1939NODEIDIND                                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_J1939NODEINDICATOR                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_MEMORYBLOCKID                                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_MEMORYBLOCKIDTOMEMORYENTRYID                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_MEMORYDATAPTR                                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_MEMORYDATASIZE                                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_MEMORYENTRY                                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_MEMORYENTRYINIT                                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_MEMORYSTATUS                                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_MIDTABLE                                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DTRTABLEIDXOFMIDTABLE                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_MIDOFMIDTABLE                                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_TIDOFMIDTABLE                                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_MIRRORDATA                                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_NORMALINDICATORTABLE                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_BEHAVIOROFNORMALINDICATORTABLE                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_IDOFNORMALINDICATORTABLE                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_OBDIUMPRDATA                                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_OBDIUMPRUPDATEPENDING                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_PERMANENTDATA                                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_PIDTABLE                                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DATACOLLECTIONTABLEPID2COLLINDENDIDXOFPIDTABLE                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DATACOLLECTIONTABLEPID2COLLINDSTARTIDXOFPIDTABLE                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DATACOLLECTIONTABLEPID2COLLINDUSEDOFPIDTABLE                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_PRESTORAGE                                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_PRESTORAGEINDEX                                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_PRIMARYCHRONOLOGY                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_PRIMARYENTRY_0                                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_PRIMARYENTRY_1                                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_PRIMARYENTRY_2                                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_PRIMARYENTRY_3                                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_PRIMARYENTRY_4                                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_PRIMARYENTRY_5                                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_PRIMARYENTRY_6                                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_PRIMARYENTRY_7                                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_RATIOIDTABLE                                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_READINESSGROUPTABLE                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_EVENTTABLE_OBDRDYGROUP2EVENTIDINDENDIDXOFREADINESSGROUPTABLE                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_EVENTTABLE_OBDRDYGROUP2EVENTIDINDSTARTIDXOFREADINESSGROUPTABLE                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_EVENTTABLE_OBDRDYGROUP2EVENTIDINDUSEDOFREADINESSGROUPTABLE                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_READINESSGROUPOFREADINESSGROUPTABLE                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_READOUTBUFFER                                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_REPORTEDEVENTSOFFILTER                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SATELLITEINFO                                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_APPLICATIONIDOFSATELLITEINFO                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DEBOUNCELORESTIMEROFSATELLITEINFO                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_EVENTCOUNTOFSATELLITEINFO                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_EVENTTABLEINDENDIDXOFSATELLITEINFO                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_EVENTTABLEINDSTARTIDXOFSATELLITEINFO                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_EVENTTABLEINDUSEDOFSATELLITEINFO                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_MAXDEBOUNCEVALUESOFSATELLITEINFO                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SATELLITEDATAOFSATELLITEINFO                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SATELLITEEXTENDEDDATAOFSATELLITEINFO                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SATELLITESTATUSOFSATELLITEINFO                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SATELLITEINFO0                                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SATELLITETIMEDEBOUNCEINFO                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DEBOUNCEHIRESTABLEENDIDXOFSATELLITETIMEDEBOUNCEINFO                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DEBOUNCEHIRESTABLESTARTIDXOFSATELLITETIMEDEBOUNCEINFO                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DEBOUNCEHIRESTABLEUSEDOFSATELLITETIMEDEBOUNCEINFO                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DEBOUNCELORESTABLEENDIDXOFSATELLITETIMEDEBOUNCEINFO                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DEBOUNCELORESTABLESTARTIDXOFSATELLITETIMEDEBOUNCEINFO                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DEBOUNCELORESTABLEUSEDOFSATELLITETIMEDEBOUNCEINFO                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SECONDARYCHRONOLOGY                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFCALLBACKCLEAREVENTALLOWED                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFCALLBACKDTCSTATUSCHANGED                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFCALLBACKGETFDC                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFCALLBACKJ1939DTCSTATUSCHANGED                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFCLEARDTCTABLE                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFCLEARDTCNOTIFICATIONFINISHTABLE                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFCLEARDTCNOTIFICATIONSTARTTABLE                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFCLIENTTABLE                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFDTCSELECTORTABLE                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFDATAELEMENTTABLE                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFDEBOUNCEHIRESTABLE                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFDEBOUNCELORESTABLE                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFDTCGROUPMASK                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFDTRSTATUS                                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFDTRTABLE                                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFENABLECONDITIONFULFILLED                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFENABLECONDITIONGROUPCOUNTER                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFENABLECONDITIONGROUPSTATE                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFENABLECONDITIONGROUPTABLE                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFENABLECONDITIONTABLE                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFEVENTCYCLESTATUS                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFEVENTDATACHANGED                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFEVENTDATACOMMITNUMBER                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFEVENTDEBOUNCEVALUE                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFEVENTINTERNALSTATUS                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFEVENTSTATUSCHANGED                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFEVENTTABLE                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFEXTENDEDDATARECORDITERATORTABLE                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFFILTERINFOTABLE                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFFILTERREPORTEDEVENTS                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFFREEZEFRAMEITERATORTABLE                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFGLOBALINDICATORSTATES                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFINDICATORBLINKING                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFINDICATORCONTINUOUS                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFINDICATORFASTFLASH                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFINDICATORSLOWFLASH                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFINITMONITORFOREVENT                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFINITMONITORSFORFUNC                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFMEMORYBLOCKIDTOMEMORYENTRYID                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFMEMORYENTRY                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFMEMORYSTATUS                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFOBDIUMPRUPDATEPENDING                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFPRESTORAGEINDEX                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFPRIMARYCHRONOLOGY                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFREADINESSGROUPTABLE                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFREADOUTBUFFER                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFREPORTEDEVENTSOFFILTER                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFSATELLITEINFO                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFSECONDARYCHRONOLOGY                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFSPECIALINDICATORTABLE                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFSTARTIDX500MIDENRATIOTABLE                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFSTORAGECONDITIONFULFILLED                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFSTORAGECONDITIONGROUPCOUNTER                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFSTORAGECONDITIONGROUPTABLE                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFSTORAGECONDITIONTABLE                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFSUPPORTEDMIDSTABLE                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFTIMESERIESCHRONOLOGY                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SPECIALINDICATORTABLE                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_BEHAVIOROFSPECIALINDICATORTABLE                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_IDOFSPECIALINDICATORTABLE                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_STARTIDX500MIDENRATIOTABLE                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_STATUSDATA                                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_STORAGECONDITIONFULFILLED                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_STORAGECONDITIONGROUPCOUNTER                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_STORAGECONDITIONGROUPTABLE                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_INDEXOFSTORAGECONDITIONGROUPTABLE                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_STORAGECONDITIONGROUPTABLEIND                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_STORAGECONDITIONINITTABLE                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_FULFILLEDATINITOFSTORAGECONDITIONINITTABLE                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_STORAGECONDITIONTABLE                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_STORAGECONDITIONGROUPTABLEINDENDIDXOFSTORAGECONDITIONTABLE                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_STORAGECONDITIONGROUPTABLEINDSTARTIDXOFSTORAGECONDITIONTABLE                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_STORAGECONDITIONGROUPTABLEINDUSEDOFSTORAGECONDITIONTABLE                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SUPPORTEDMIDSTABLE                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_STARTIDXMIDTABLEOFSUPPORTEDMIDSTABLE                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SUPPORTEDMIDMASKOFSUPPORTEDMIDSTABLE                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_TIMESERIESCHRONOLOGY                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_TIMESERIESENTRYINIT                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_USEOBDIIINVARIANT                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_USEPERMANENTINVARIANT                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_USEWWHOBDINVARIANT                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_PCCONFIG                                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_ADMINDATAOFPCCONFIG                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_AGINGDATAOFPCCONFIG                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_CALLBACKCLEAREVENTALLOWEDOFPCCONFIG                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_CALLBACKDTCSTATUSCHANGEDOFPCCONFIG                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_CALLBACKGETFDCOFPCCONFIG                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_CALLBACKJ1939DTCSTATUSCHANGEDOFPCCONFIG                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_CLEARDTCTABLEOFPCCONFIG                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_CLEARDTCNOTIFICATIONFINISHTABLEOFPCCONFIG                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_CLEARDTCNOTIFICATIONSTARTTABLEOFPCCONFIG                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_CLIENTTABLEOFPCCONFIG                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_COMMITBUFFEROFPCCONFIG                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_CONFIGURATIONIDOFPCCONFIG                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_CYCLECOUNTERDATAOFPCCONFIG                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_CYCLEIDTABLEOFPCCONFIG                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DTCSELECTORTABLEOFPCCONFIG                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DATACOLLECTIONTABLEEDR2COLLINDOFPCCONFIG                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DATACOLLECTIONTABLEEREC2COLLINDOFPCCONFIG                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DATACOLLECTIONTABLEFFM2COLLINDOFPCCONFIG                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DATACOLLECTIONTABLEJ19392COLLINDOFPCCONFIG                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DATACOLLECTIONTABLEOFPCCONFIG                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DATACOLLECTIONTABLEPID2COLLINDOFPCCONFIG                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DATAELEMENTTABLECOL2ELMTINDOFPCCONFIG                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DATAELEMENTTABLEOFPCCONFIG                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DEBOUNCEDATAOFPCCONFIG                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DEBOUNCEHIRESTABLEOFPCCONFIG                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DEBOUNCELORESTABLEOFPCCONFIG                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DEBOUNCETABLEOFPCCONFIG                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DTCGROUPMASKOFPCCONFIG                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DTCTABLEOFPCCONFIG                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DTRDATAOFPCCONFIG                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DTRSTATUSOFPCCONFIG                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DTRTABLEINDOFPCCONFIG                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_DTRTABLEOFPCCONFIG                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_ENABLECONDITIONFULFILLEDOFPCCONFIG                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_ENABLECONDITIONGROUPCOUNTEROFPCCONFIG                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_ENABLECONDITIONGROUPSTATEOFPCCONFIG                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_ENABLECONDITIONGROUPTABLEINDOFPCCONFIG                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_ENABLECONDITIONGROUPTABLEOFPCCONFIG                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_ENABLECONDITIONINITTABLEOFPCCONFIG                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_ENABLECONDITIONTABLEOFPCCONFIG                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_EVENTAVAILABLEDATAOFPCCONFIG                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_EVENTAVAILABLEDEFAULTOFPCCONFIG                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_EVENTAVAILABLEINVARIANTOFPCCONFIG                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_EVENTCYCLESTATUSOFPCCONFIG                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_EVENTDATACHANGEDOFPCCONFIG                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_EVENTDATACOMMITNUMBEROFPCCONFIG                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_EVENTDEBOUNCEVALUEOFPCCONFIG                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_EVENTINTERNALSTATUSOFPCCONFIG                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_EVENTSTATUSCHANGEDOFPCCONFIG                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_EVENTTABLEINDOFPCCONFIG                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_EVENTTABLEOFPCCONFIG                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_EVENTTABLE_EREC2EVENTIDINDOFPCCONFIG                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_EVENTTABLE_OBDRDYGROUP2EVENTIDINDOFPCCONFIG                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_EXTENDEDDATARECORDITERATORTABLEOFPCCONFIG                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_EXTENDEDDATARECORDTABLEOFPCCONFIG                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_EXTENDEDDATATABLEOFPCCONFIG                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_FILTERINFOTABLEOFPCCONFIG                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_FILTERREPORTEDEVENTSOFPCCONFIG                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_FINALMAGICNUMBEROFPCCONFIG                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_FREEZEFRAMEDATAOFPCCONFIG                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_FREEZEFRAMEITERATORTABLEOFPCCONFIG                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_FREEZEFRAMENUMTABLEOFPCCONFIG                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_FREEZEFRAMETABLEOFPCCONFIG                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_GENERALJ1939TABLEOFPCCONFIG                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_GENERALOBDINPUTOFPCCONFIG                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_GLOBALINDICATORSTATESOFPCCONFIG                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_GLOBALOBDREQUIREMENTSOFPCCONFIG                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_GLOBALSEVERITYMASKOFPCCONFIG                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_INDICATORBLINKINGOFPCCONFIG                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_INDICATORCONTINUOUSOFPCCONFIG                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_INDICATORFASTFLASHOFPCCONFIG                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_INDICATORSLOWFLASHOFPCCONFIG                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_INITDATAHASHCODEOFPCCONFIG                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_INITMONLISTFORFUNCOFPCCONFIG                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_INITMONITORFOREVENTOFPCCONFIG                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_INITMONITORSFORFUNCOFPCCONFIG                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_J1939NODEIDINDOFPCCONFIG                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_J1939NODEIDOFPCCONFIG                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_J1939NODEINDICATOROFPCCONFIG                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_MEMORYBLOCKIDOFPCCONFIG                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_MEMORYBLOCKIDTOMEMORYENTRYIDOFPCCONFIG                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_MEMORYDATAPTROFPCCONFIG                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_MEMORYDATASIZEOFPCCONFIG                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_MEMORYENTRYINITOFPCCONFIG                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_MEMORYENTRYOFPCCONFIG                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_MEMORYSTATUSOFPCCONFIG                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_MIDTABLEOFPCCONFIG                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_MIRRORDATAOFPCCONFIG                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_NORMALINDICATORTABLEOFPCCONFIG                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_OBDIUMPRDATAOFPCCONFIG                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_OBDIUMPRUPDATEPENDINGOFPCCONFIG                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_PERMANENTDATAOFPCCONFIG                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_PIDTABLEOFPCCONFIG                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_PRESTORAGEINDEXOFPCCONFIG                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_PRESTORAGEOFPCCONFIG                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_PRIMARYCHRONOLOGYOFPCCONFIG                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_PRIMARYENTRY_0OFPCCONFIG                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_PRIMARYENTRY_1OFPCCONFIG                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_PRIMARYENTRY_2OFPCCONFIG                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_PRIMARYENTRY_3OFPCCONFIG                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_PRIMARYENTRY_4OFPCCONFIG                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_PRIMARYENTRY_5OFPCCONFIG                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_PRIMARYENTRY_6OFPCCONFIG                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_PRIMARYENTRY_7OFPCCONFIG                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_RATIOIDTABLEOFPCCONFIG                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_READINESSGROUPTABLEOFPCCONFIG                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_READOUTBUFFEROFPCCONFIG                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_REPORTEDEVENTSOFFILTEROFPCCONFIG                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SATELLITEINFO0OFPCCONFIG                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SATELLITEINFOOFPCCONFIG                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SATELLITETIMEDEBOUNCEINFOOFPCCONFIG                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SECONDARYCHRONOLOGYOFPCCONFIG                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFCALLBACKCLEAREVENTALLOWEDOFPCCONFIG                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFCALLBACKDTCSTATUSCHANGEDOFPCCONFIG                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFCALLBACKGETFDCOFPCCONFIG                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFCALLBACKJ1939DTCSTATUSCHANGEDOFPCCONFIG                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFCLEARDTCTABLEOFPCCONFIG                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFCLEARDTCNOTIFICATIONFINISHTABLEOFPCCONFIG                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFCLEARDTCNOTIFICATIONSTARTTABLEOFPCCONFIG                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFCLIENTTABLEOFPCCONFIG                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFDTCSELECTORTABLEOFPCCONFIG                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFDATAELEMENTTABLEOFPCCONFIG                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFDEBOUNCEHIRESTABLEOFPCCONFIG                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFDEBOUNCELORESTABLEOFPCCONFIG                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFDTCGROUPMASKOFPCCONFIG                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFDTRSTATUSOFPCCONFIG                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFDTRTABLEOFPCCONFIG                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFENABLECONDITIONFULFILLEDOFPCCONFIG                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFENABLECONDITIONGROUPCOUNTEROFPCCONFIG                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFENABLECONDITIONGROUPSTATEOFPCCONFIG                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFENABLECONDITIONGROUPTABLEOFPCCONFIG                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFENABLECONDITIONTABLEOFPCCONFIG                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFEVENTCYCLESTATUSOFPCCONFIG                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFEVENTDATACHANGEDOFPCCONFIG                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFEVENTDATACOMMITNUMBEROFPCCONFIG                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFEVENTDEBOUNCEVALUEOFPCCONFIG                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFEVENTINTERNALSTATUSOFPCCONFIG                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFEVENTSTATUSCHANGEDOFPCCONFIG                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFEVENTTABLEOFPCCONFIG                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFEXTENDEDDATARECORDITERATORTABLEOFPCCONFIG                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFFILTERINFOTABLEOFPCCONFIG                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFFILTERREPORTEDEVENTSOFPCCONFIG                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFFREEZEFRAMEITERATORTABLEOFPCCONFIG                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFGLOBALINDICATORSTATESOFPCCONFIG                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFINDICATORBLINKINGOFPCCONFIG                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFINDICATORCONTINUOUSOFPCCONFIG                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFINDICATORFASTFLASHOFPCCONFIG                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFINDICATORSLOWFLASHOFPCCONFIG                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFINITMONITORFOREVENTOFPCCONFIG                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFINITMONITORSFORFUNCOFPCCONFIG                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFMEMORYBLOCKIDTOMEMORYENTRYIDOFPCCONFIG                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFMEMORYENTRYOFPCCONFIG                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFMEMORYSTATUSOFPCCONFIG                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFOBDIUMPRUPDATEPENDINGOFPCCONFIG                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFPRESTORAGEINDEXOFPCCONFIG                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFPRIMARYCHRONOLOGYOFPCCONFIG                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFREADINESSGROUPTABLEOFPCCONFIG                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFREADOUTBUFFEROFPCCONFIG                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFREPORTEDEVENTSOFFILTEROFPCCONFIG                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFSATELLITEINFOOFPCCONFIG                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFSECONDARYCHRONOLOGYOFPCCONFIG                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFSPECIALINDICATORTABLEOFPCCONFIG                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFSTARTIDX500MIDENRATIOTABLEOFPCCONFIG                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFSTORAGECONDITIONFULFILLEDOFPCCONFIG                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFSTORAGECONDITIONGROUPCOUNTEROFPCCONFIG                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFSTORAGECONDITIONGROUPTABLEOFPCCONFIG                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFSTORAGECONDITIONTABLEOFPCCONFIG                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFSUPPORTEDMIDSTABLEOFPCCONFIG                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SIZEOFTIMESERIESCHRONOLOGYOFPCCONFIG                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SPECIALINDICATORTABLEOFPCCONFIG                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_STARTIDX500MIDENRATIOTABLEOFPCCONFIG                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_STATUSDATAOFPCCONFIG                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_STORAGECONDITIONFULFILLEDOFPCCONFIG                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_STORAGECONDITIONGROUPCOUNTEROFPCCONFIG                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_STORAGECONDITIONGROUPTABLEINDOFPCCONFIG                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_STORAGECONDITIONGROUPTABLEOFPCCONFIG                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_STORAGECONDITIONINITTABLEOFPCCONFIG                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_STORAGECONDITIONTABLEOFPCCONFIG                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_SUPPORTEDMIDSTABLEOFPCCONFIG                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_TIMESERIESCHRONOLOGYOFPCCONFIG                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_TIMESERIESENTRYINITOFPCCONFIG                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_USEOBDIIINVARIANTOFPCCONFIG                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_USEPERMANENTINVARIANTOFPCCONFIG                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
#define DEM_CFG_USEWWHOBDINVARIANTOFPCCONFIG                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
/** 
  \}
*/ 

/** 
  \defgroup  Dem_CfgPCMinNumericValueDefines  Dem_Cfg Min Numeric Value Defines (PRE_COMPILE)
  \brief  These defines are used to implement against the minimum value in numerical based data.
  \{
*/ 
#define DEM_CFG_MIN_ENABLECONDITIONGROUPCOUNTER                                                     0u
#define DEM_CFG_MIN_ENABLECONDITIONGROUPSTATE                                                       0u
#define DEM_CFG_MIN_EVENTCYCLESTATUS                                                                0u
#define DEM_CFG_MIN_EVENTDATACOMMITNUMBER                                                           0u
#define DEM_CFG_MIN_EVENTDEBOUNCEVALUE                                                              -32768
#define DEM_CFG_MIN_FILTERREPORTEDEVENTS                                                            0u
#define DEM_CFG_MIN_MEMORYSTATUS                                                                    0u
#define DEM_CFG_MIN_MIRRORDATA                                                                      0u
#define DEM_CFG_MIN_STORAGECONDITIONGROUPCOUNTER                                                    0u
/** 
  \}
*/ 

/** 
  \defgroup  Dem_CfgPCMaxNumericValueDefines  Dem_Cfg Max Numeric Value Defines (PRE_COMPILE)
  \brief  These defines are used to implement against the maximum value in numerical based data.
  \{
*/ 
#define DEM_CFG_MAX_ENABLECONDITIONGROUPCOUNTER                                                     255u
#define DEM_CFG_MAX_ENABLECONDITIONGROUPSTATE                                                       255u
#define DEM_CFG_MAX_EVENTCYCLESTATUS                                                                255u
#define DEM_CFG_MAX_EVENTDATACOMMITNUMBER                                                           255u
#define DEM_CFG_MAX_EVENTDEBOUNCEVALUE                                                              32767
#define DEM_CFG_MAX_FILTERREPORTEDEVENTS                                                            255u
#define DEM_CFG_MAX_MEMORYSTATUS                                                                    255u
#define DEM_CFG_MAX_MIRRORDATA                                                                      255u
#define DEM_CFG_MAX_STORAGECONDITIONGROUPCOUNTER                                                    255u
/** 
  \}
*/ 

/** 
  \defgroup  Dem_CfgPCNoReferenceDefines  Dem_Cfg No Reference Defines (PRE_COMPILE)
  \brief  These defines are used to indicate unused indexes in data relations.
  \{
*/ 
#define DEM_CFG_NO_DATAELEMENTTABLECOL2ELMTINDENDIDXOFDATACOLLECTIONTABLE                           255u
#define DEM_CFG_NO_DATAELEMENTTABLECOL2ELMTINDSTARTIDXOFDATACOLLECTIONTABLE                         255u
#define DEM_CFG_NO_EVENTTABLE_EREC2EVENTIDINDENDIDXOFDATACOLLECTIONTABLE                            255u
#define DEM_CFG_NO_EVENTTABLE_EREC2EVENTIDINDSTARTIDXOFDATACOLLECTIONTABLE                          255u
#define DEM_CFG_NO_J1939NODEIDINDENDIDXOFDTCTABLE                                                   255u
#define DEM_CFG_NO_J1939NODEIDINDSTARTIDXOFDTCTABLE                                                 255u
#define DEM_CFG_NO_ENABLECONDITIONGROUPTABLEINDENDIDXOFENABLECONDITIONTABLE                         255u
#define DEM_CFG_NO_ENABLECONDITIONGROUPTABLEINDSTARTIDXOFENABLECONDITIONTABLE                       255u
#define DEM_CFG_NO_CALLBACKCLEAREVENTALLOWEDIDXOFEVENTTABLE                                         255u
#define DEM_CFG_NO_DTRTABLEINDENDIDXOFEVENTTABLE                                                    255u
#define DEM_CFG_NO_DTRTABLEINDSTARTIDXOFEVENTTABLE                                                  255u
#define DEM_CFG_NO_FREEZEFRAMENUMTABLEENDIDXOFEVENTTABLE                                            255u
#define DEM_CFG_NO_FREEZEFRAMENUMTABLESTARTIDXOFEVENTTABLE                                          255u
#define DEM_CFG_NO_SPECIALINDICATORTABLEENDIDXOFEVENTTABLE                                          255u
#define DEM_CFG_NO_SPECIALINDICATORTABLESTARTIDXOFEVENTTABLE                                        255u
#define DEM_CFG_NO_DATACOLLECTIONTABLEEREC2COLLINDENDIDXOFEXTENDEDDATARECORDTABLE                   255u
#define DEM_CFG_NO_DATACOLLECTIONTABLEEREC2COLLINDSTARTIDXOFEXTENDEDDATARECORDTABLE                 255u
#define DEM_CFG_NO_DATACOLLECTIONTABLEEDR2COLLINDENDIDXOFEXTENDEDDATATABLE                          255u
#define DEM_CFG_NO_DATACOLLECTIONTABLEEDR2COLLINDSTARTIDXOFEXTENDEDDATATABLE                        255u
#define DEM_CFG_NO_DATACOLLECTIONTABLEFFM2COLLINDENDIDXOFFREEZEFRAMETABLE                           255u
#define DEM_CFG_NO_DATACOLLECTIONTABLEFFM2COLLINDSTARTIDXOFFREEZEFRAMETABLE                         255u
#define DEM_CFG_NO_DATACOLLECTIONTABLEJ19392COLLINDENDIDXOFGENERALJ1939TABLE                        255u
#define DEM_CFG_NO_DATACOLLECTIONTABLEJ19392COLLINDSTARTIDXOFGENERALJ1939TABLE                      255u
#define DEM_CFG_NO_DATACOLLECTIONTABLEPID2COLLINDENDIDXOFPIDTABLE                                   255u
#define DEM_CFG_NO_DATACOLLECTIONTABLEPID2COLLINDSTARTIDXOFPIDTABLE                                 255u
#define DEM_CFG_NO_EVENTTABLE_OBDRDYGROUP2EVENTIDINDENDIDXOFREADINESSGROUPTABLE                     255u
#define DEM_CFG_NO_EVENTTABLE_OBDRDYGROUP2EVENTIDINDSTARTIDXOFREADINESSGROUPTABLE                   255u
#define DEM_CFG_NO_EVENTTABLEINDENDIDXOFSATELLITEINFO                                               255u
#define DEM_CFG_NO_EVENTTABLEINDSTARTIDXOFSATELLITEINFO                                             255u
#define DEM_CFG_NO_DEBOUNCEHIRESTABLEENDIDXOFSATELLITETIMEDEBOUNCEINFO                              255u
#define DEM_CFG_NO_DEBOUNCEHIRESTABLESTARTIDXOFSATELLITETIMEDEBOUNCEINFO                            255u
#define DEM_CFG_NO_DEBOUNCELORESTABLEENDIDXOFSATELLITETIMEDEBOUNCEINFO                              255u
#define DEM_CFG_NO_DEBOUNCELORESTABLESTARTIDXOFSATELLITETIMEDEBOUNCEINFO                            255u
#define DEM_CFG_NO_STORAGECONDITIONGROUPTABLEINDENDIDXOFSTORAGECONDITIONTABLE                       255u
#define DEM_CFG_NO_STORAGECONDITIONGROUPTABLEINDSTARTIDXOFSTORAGECONDITIONTABLE                     255u
/** 
  \}
*/ 

/** 
  \defgroup  Dem_CfgPCEnumExistsDefines  Dem_Cfg Enum Exists Defines (PRE_COMPILE)
  \brief  These defines can be used to deactivate enumeration based code sequences if the enumeration value does not exist in the configuration data.
  \{
*/ 
#define DEM_CFG_EXISTS_DEM_CFG_DEBOUNCETYPE_COUNTER_EVENTDEBOUNCEALGORITHMOFDEBOUNCETABLE           STD_ON
#define DEM_CFG_EXISTS_DEM_CFG_DEBOUNCETYPE_TIMER_EVENTDEBOUNCEALGORITHMOFDEBOUNCETABLE             STD_ON
#define DEM_CFG_EXISTS_DEM_CFG_DEBOUNCETYPE_EXTERNAL_EVENTDEBOUNCEALGORITHMOFDEBOUNCETABLE          STD_ON
#define DEM_CFG_EXISTS_DEM_CFG_DEBOUNCETYPE_INVALID_EVENTDEBOUNCEALGORITHMOFDEBOUNCETABLE           STD_ON
#define DEM_CFG_EXISTS_DEM_EVENT_KIND_BSW_EVENTKINDOFEVENTTABLE                                     STD_ON
#define DEM_CFG_EXISTS_DEM_EVENT_KIND_SWC_EVENTKINDOFEVENTTABLE                                     STD_ON
#define DEM_CFG_EXISTS_DEM_EVENT_SIGNIFICANCE_OCCURRENCE_EVENTSIGNIFICANCEOFEVENTTABLE              STD_ON
#define DEM_CFG_EXISTS_DEM_EVENT_SIGNIFICANCE_FAULT_EVENTSIGNIFICANCEOFEVENTTABLE                   STD_ON
/** 
  \}
*/ 

/** 
  \defgroup  Dem_CfgPCEnumDefines  Dem_Cfg Enum Defines (PRE_COMPILE)
  \brief  These defines are the enumeration values of enumeration based CONST and VAR data.
  \{
*/ 
#define DEM_CFG_DEM_CFG_DEBOUNCETYPE_COUNTER_EVENTDEBOUNCEALGORITHMOFDEBOUNCETABLE                  0x00u
#define DEM_CFG_DEM_CFG_DEBOUNCETYPE_TIMER_EVENTDEBOUNCEALGORITHMOFDEBOUNCETABLE                    0x01u
#define DEM_CFG_DEM_CFG_DEBOUNCETYPE_EXTERNAL_EVENTDEBOUNCEALGORITHMOFDEBOUNCETABLE                 0x02u
#define DEM_CFG_DEM_CFG_DEBOUNCETYPE_INVALID_EVENTDEBOUNCEALGORITHMOFDEBOUNCETABLE                  0x03u
#define DEM_CFG_DEM_EVENT_KIND_BSW_EVENTKINDOFEVENTTABLE                                            0x00u
#define DEM_CFG_DEM_EVENT_KIND_SWC_EVENTKINDOFEVENTTABLE                                            0x01u
#define DEM_CFG_DEM_EVENT_SIGNIFICANCE_OCCURRENCE_EVENTSIGNIFICANCEOFEVENTTABLE                     0x00u
#define DEM_CFG_DEM_EVENT_SIGNIFICANCE_FAULT_EVENTSIGNIFICANCEOFEVENTTABLE                          0x01u
/** 
  \}
*/ 

/** 
  \defgroup  Dem_CfgPCMaskedBitDefines  Dem_Cfg Masked Bit Defines (PRE_COMPILE)
  \brief  These defines are masks to extract packed boolean data.
  \{
*/ 
#define DEM_CFG_USEDFORAGINGOFCYCLEIDTABLE_MASK                                                     0x01u
#define DEM_CFG_DEBOUNCECONTINUOUSOFDEBOUNCETABLE_MASK                                              0x10u
#define DEM_CFG_EVENTDEBOUNCEBEHAVIOROFDEBOUNCETABLE_MASK                                           0x08u
#define DEM_CFG_JUMPDOWNOFDEBOUNCETABLE_MASK                                                        0x04u
#define DEM_CFG_JUMPUPOFDEBOUNCETABLE_MASK                                                          0x02u
#define DEM_CFG_STORAGEOFDEBOUNCETABLE_MASK                                                         0x01u
#define DEM_CFG_AGINGALLOWEDOFEVENTTABLE_MASK                                                       0x04u
#define DEM_CFG_EVENTLATCHTFOFEVENTTABLE_MASK                                                       0x02u
#define DEM_CFG_OBDVISIBILITYDELAYEDUNTILDCYQUALIFICATIONOFEVENTTABLE_MASK                          0x01u
/** 
  \}
*/ 

/** 
  \defgroup  Dem_CfgPCIsReducedToDefineDefines  Dem_Cfg Is Reduced To Define Defines (PRE_COMPILE)
  \brief  If all values in a CONST array or an element in a CONST array of structs are equal, the define is STD_ON else STD_OFF.
  \{
*/ 
#define DEM_CFG_ISDEF_CALLBACKCLEAREVENTALLOWED                                                     STD_OFF
#define DEM_CFG_ISDEF_CALLBACKDTCSTATUSCHANGED                                                      STD_OFF
#define DEM_CFG_ISDEF_CALLBACKGETFDC                                                                STD_OFF
#define DEM_CFG_ISDEF_CALLBACKJ1939DTCSTATUSCHANGED                                                 STD_OFF
#define DEM_CFG_ISDEF_CLEARDTCNOTIFICATIONFINISHTABLE                                               STD_OFF
#define DEM_CFG_ISDEF_CLEARDTCNOTIFICATIONSTARTTABLE                                                STD_OFF
#define DEM_CFG_ISDEF_CLEARDTCINDEXOFCLIENTTABLE                                                    STD_ON
#define DEM_CFG_ISDEF_FILTERINDEXOFCLIENTTABLE                                                      STD_ON
#define DEM_CFG_ISDEF_FREEZEFRAMEITERATORINDEXOFCLIENTTABLE                                         STD_ON
#define DEM_CFG_ISDEF_NMNODEIDOFCLIENTTABLE                                                         STD_OFF
#define DEM_CFG_ISDEF_READOUTBUFFERINDEXOFCLIENTTABLE                                               STD_ON
#define DEM_CFG_ISDEF_SELECTORINDEXOFCLIENTTABLE                                                    STD_ON
#define DEM_CFG_ISDEF_ENDSONINITOFCYCLEIDTABLE                                                      STD_OFF
#define DEM_CFG_ISDEF_MASKEDBITSOFCYCLEIDTABLE                                                      STD_OFF
#define DEM_CFG_ISDEF_OPCYCLETYPEOFCYCLEIDTABLE                                                     STD_OFF
#define DEM_CFG_ISDEF_USEDFORAGINGOFCYCLEIDTABLE                                                    STD_OFF
#define DEM_CFG_ISDEF_COLLECTIONSIZEOFDATACOLLECTIONTABLE                                           STD_OFF
#define DEM_CFG_ISDEF_DATAELEMENTTABLECOL2ELMTINDENDIDXOFDATACOLLECTIONTABLE                        STD_OFF
#define DEM_CFG_ISDEF_DATAELEMENTTABLECOL2ELMTINDSTARTIDXOFDATACOLLECTIONTABLE                      STD_OFF
#define DEM_CFG_ISDEF_DATAELEMENTTABLECOL2ELMTINDUSEDOFDATACOLLECTIONTABLE                          STD_OFF
#define DEM_CFG_ISDEF_DIDOFFSETFASTOFDATACOLLECTIONTABLE                                            STD_OFF
#define DEM_CFG_ISDEF_DIDOFFSETNORMALOFDATACOLLECTIONTABLE                                          STD_OFF
#define DEM_CFG_ISDEF_EVENTTABLE_EREC2EVENTIDINDENDIDXOFDATACOLLECTIONTABLE                         STD_OFF
#define DEM_CFG_ISDEF_EVENTTABLE_EREC2EVENTIDINDSTARTIDXOFDATACOLLECTIONTABLE                       STD_OFF
#define DEM_CFG_ISDEF_EVENTTABLE_EREC2EVENTIDINDUSEDOFDATACOLLECTIONTABLE                           STD_OFF
#define DEM_CFG_ISDEF_IDNUMBEROFDATACOLLECTIONTABLE                                                 STD_OFF
#define DEM_CFG_ISDEF_STORAGEKINDOFDATACOLLECTIONTABLE                                              STD_OFF
#define DEM_CFG_ISDEF_TRIGGEROFDATACOLLECTIONTABLE                                                  STD_ON
#define DEM_CFG_ISDEF_UPDATEOFDATACOLLECTIONTABLE                                                   STD_OFF
#define DEM_CFG_ISDEF_DATACOLLECTIONTABLEEDR2COLLIND                                                STD_OFF
#define DEM_CFG_ISDEF_DATACOLLECTIONTABLEEREC2COLLIND                                               STD_OFF
#define DEM_CFG_ISDEF_DATACOLLECTIONTABLEFFM2COLLIND                                                STD_OFF
#define DEM_CFG_ISDEF_DATACOLLECTIONTABLEJ19392COLLIND                                              STD_OFF
#define DEM_CFG_ISDEF_DATACOLLECTIONTABLEPID2COLLIND                                                STD_OFF
#define DEM_CFG_ISDEF_DATAISSTOREDINNVOFDATAELEMENTTABLE                                            STD_OFF
#define DEM_CFG_ISDEF_ELEMENTKINDOFDATAELEMENTTABLE                                                 STD_OFF
#define DEM_CFG_ISDEF_ELEMENTSIZEOFDATAELEMENTTABLE                                                 STD_OFF
#define DEM_CFG_ISDEF_READDATAFUNCOFDATAELEMENTTABLE                                                STD_OFF
#define DEM_CFG_ISDEF_DATAELEMENTTABLECOL2ELMTIND                                                   STD_OFF
#define DEM_CFG_ISDEF_DEBOUNCEHIRESTABLE                                                            STD_OFF
#define DEM_CFG_ISDEF_DEBOUNCELORESTABLE                                                            STD_OFF
#define DEM_CFG_ISDEF_DEBOUNCECONTINUOUSOFDEBOUNCETABLE                                             STD_ON
#define DEM_CFG_ISDEF_DECREMENTSTEPSIZEOFDEBOUNCETABLE                                              STD_OFF
#define DEM_CFG_ISDEF_EVENTDEBOUNCEALGORITHMOFDEBOUNCETABLE                                         STD_OFF
#define DEM_CFG_ISDEF_EVENTDEBOUNCEBEHAVIOROFDEBOUNCETABLE                                          STD_OFF
#define DEM_CFG_ISDEF_FAILTIMERCYCLESOFDEBOUNCETABLE                                                STD_ON
#define DEM_CFG_ISDEF_FAILEDTHRESHOLDOFDEBOUNCETABLE                                                STD_OFF
#define DEM_CFG_ISDEF_INCREMENTSTEPSIZEOFDEBOUNCETABLE                                              STD_OFF
#define DEM_CFG_ISDEF_JUMPDOWNOFDEBOUNCETABLE                                                       STD_OFF
#define DEM_CFG_ISDEF_JUMPDOWNVALUEOFDEBOUNCETABLE                                                  STD_ON
#define DEM_CFG_ISDEF_JUMPUPOFDEBOUNCETABLE                                                         STD_OFF
#define DEM_CFG_ISDEF_JUMPUPVALUEOFDEBOUNCETABLE                                                    STD_ON
#define DEM_CFG_ISDEF_MASKEDBITSOFDEBOUNCETABLE                                                     STD_OFF
#define DEM_CFG_ISDEF_PASSTIMERCYCLESOFDEBOUNCETABLE                                                STD_ON
#define DEM_CFG_ISDEF_PASSEDTHRESHOLDOFDEBOUNCETABLE                                                STD_OFF
#define DEM_CFG_ISDEF_PRECONFIRMEDTHRESHOLDOFDEBOUNCETABLE                                          STD_OFF
#define DEM_CFG_ISDEF_STORAGEOFDEBOUNCETABLE                                                        STD_ON
#define DEM_CFG_ISDEF_STORAGETHRESHOLDOFDEBOUNCETABLE                                               STD_OFF
#define DEM_CFG_ISDEF_STORAGETIMERCYCLESOFDEBOUNCETABLE                                             STD_OFF
#define DEM_CFG_ISDEF_GROUPMASKOFDTCGROUPMASK                                                       STD_OFF
#define DEM_CFG_ISDEF_UDSGROUPDTCOFDTCGROUPMASK                                                     STD_OFF
#define DEM_CFG_ISDEF_DTCSEVERITYOFDTCTABLE                                                         STD_ON
#define DEM_CFG_ISDEF_FUNCTIONALUNITOFDTCTABLE                                                      STD_OFF
#define DEM_CFG_ISDEF_IMMEDIATENVSTORAGEOFDTCTABLE                                                  STD_ON
#define DEM_CFG_ISDEF_J1939DTCOFDTCTABLE                                                            STD_OFF
#define DEM_CFG_ISDEF_J1939NODEIDINDENDIDXOFDTCTABLE                                                STD_OFF
#define DEM_CFG_ISDEF_J1939NODEIDINDSTARTIDXOFDTCTABLE                                              STD_OFF
#define DEM_CFG_ISDEF_J1939NODEIDINDUSEDOFDTCTABLE                                                  STD_OFF
#define DEM_CFG_ISDEF_OBDDTCOFDTCTABLE                                                              STD_OFF
#define DEM_CFG_ISDEF_UDSDTCOFDTCTABLE                                                              STD_OFF
#define DEM_CFG_ISDEF_DIVISOROFDTRTABLE                                                             STD_OFF
#define DEM_CFG_ISDEF_EVENTTABLEIDXOFDTRTABLE                                                       STD_OFF
#define DEM_CFG_ISDEF_LINEARFACTOROFDTRTABLE                                                        STD_OFF
#define DEM_CFG_ISDEF_OFFSETOFDTRTABLE                                                              STD_OFF
#define DEM_CFG_ISDEF_UASIDOFDTRTABLE                                                               STD_OFF
#define DEM_CFG_ISDEF_UPDATEKINDOFDTRTABLE                                                          STD_OFF
#define DEM_CFG_ISDEF_DTRTABLEIND                                                                   STD_OFF
#define DEM_CFG_ISDEF_INDEXOFENABLECONDITIONGROUPTABLE                                              STD_OFF
#define DEM_CFG_ISDEF_ENABLECONDITIONGROUPTABLEIND                                                  STD_OFF
#define DEM_CFG_ISDEF_FULFILLEDATINITOFENABLECONDITIONINITTABLE                                     STD_OFF
#define DEM_CFG_ISDEF_ENABLECONDITIONGROUPTABLEINDENDIDXOFENABLECONDITIONTABLE                      STD_OFF
#define DEM_CFG_ISDEF_ENABLECONDITIONGROUPTABLEINDSTARTIDXOFENABLECONDITIONTABLE                    STD_OFF
#define DEM_CFG_ISDEF_ENABLECONDITIONGROUPTABLEINDUSEDOFENABLECONDITIONTABLE                        STD_ON
#define DEM_CFG_ISDEF_EVENTAVAILABLEDEFAULT                                                         STD_ON
#define DEM_CFG_ISDEF_EVENTAVAILABLEINVARIANT                                                       STD_ON
#define DEM_CFG_ISDEF_EVENTDATACHANGED                                                              STD_OFF
#define DEM_CFG_ISDEF_EVENTSTATUSCHANGED                                                            STD_OFF
#define DEM_CFG_ISDEF_AGINGALLOWEDOFEVENTTABLE                                                      STD_OFF
#define DEM_CFG_ISDEF_AGINGCYCLECOUNTERTHRESHOLDOFEVENTTABLE                                        STD_OFF
#define DEM_CFG_ISDEF_AGINGCYCLEIDOFEVENTTABLE                                                      STD_OFF
#define DEM_CFG_ISDEF_CALLBACKCLEAREVENTALLOWEDIDXOFEVENTTABLE                                      STD_OFF
#define DEM_CFG_ISDEF_CALLBACKCLEAREVENTALLOWEDUSEDOFEVENTTABLE                                     STD_ON
#define DEM_CFG_ISDEF_CALLBACKGETFDCIDXOFEVENTTABLE                                                 STD_OFF
#define DEM_CFG_ISDEF_DEBOUNCETABLEIDXOFEVENTTABLE                                                  STD_OFF
#define DEM_CFG_ISDEF_DTCTABLEIDXOFEVENTTABLE                                                       STD_OFF
#define DEM_CFG_ISDEF_DTRTABLEINDENDIDXOFEVENTTABLE                                                 STD_OFF
#define DEM_CFG_ISDEF_DTRTABLEINDSTARTIDXOFEVENTTABLE                                               STD_OFF
#define DEM_CFG_ISDEF_DTRTABLEINDUSEDOFEVENTTABLE                                                   STD_OFF
#define DEM_CFG_ISDEF_ENABLECONDITIONGROUPTABLEIDXOFEVENTTABLE                                      STD_OFF
#define DEM_CFG_ISDEF_EVENTDESTINATIONOFEVENTTABLE                                                  STD_ON
#define DEM_CFG_ISDEF_EVENTFAILURECYCLECOUNTERTHRESHOLDOFEVENTTABLE                                 STD_ON
#define DEM_CFG_ISDEF_EVENTKINDOFEVENTTABLE                                                         STD_OFF
#define DEM_CFG_ISDEF_EVENTLATCHTFOFEVENTTABLE                                                      STD_ON
#define DEM_CFG_ISDEF_EVENTPRIORITYOFEVENTTABLE                                                     STD_OFF
#define DEM_CFG_ISDEF_EVENTSIGNIFICANCEOFEVENTTABLE                                                 STD_ON
#define DEM_CFG_ISDEF_EXTENDEDDATATABLEIDXOFEVENTTABLE                                              STD_ON
#define DEM_CFG_ISDEF_FAILEDCYCLECOUNTERINDEXOFEVENTTABLE                                           STD_OFF
#define DEM_CFG_ISDEF_FAULTPENDINGCOUNTERINDEXOFEVENTTABLE                                          STD_OFF
#define DEM_CFG_ISDEF_FREEZEFRAMENUMTABLEENDIDXOFEVENTTABLE                                         STD_ON
#define DEM_CFG_ISDEF_FREEZEFRAMENUMTABLESTARTIDXOFEVENTTABLE                                       STD_ON
#define DEM_CFG_ISDEF_FREEZEFRAMENUMTABLEUSEDOFEVENTTABLE                                           STD_ON
#define DEM_CFG_ISDEF_FREEZEFRAMETABLESTDFFIDXOFEVENTTABLE                                          STD_ON
#define DEM_CFG_ISDEF_HEALINGTARGETOFEVENTTABLE                                                     STD_ON
#define DEM_CFG_ISDEF_MASKEDBITSOFEVENTTABLE                                                        STD_OFF
#define DEM_CFG_ISDEF_OBDVISIBILITYDELAYEDUNTILDCYQUALIFICATIONOFEVENTTABLE                         STD_ON
#define DEM_CFG_ISDEF_OPERATIONCYCLEIDOFEVENTTABLE                                                  STD_ON
#define DEM_CFG_ISDEF_SATELLITEEVENTIDXOFEVENTTABLE                                                 STD_OFF
#define DEM_CFG_ISDEF_SATELLITEINFOIDXOFEVENTTABLE                                                  STD_ON
#define DEM_CFG_ISDEF_SPECIALINDICATORTABLEENDIDXOFEVENTTABLE                                       STD_OFF
#define DEM_CFG_ISDEF_SPECIALINDICATORTABLESTARTIDXOFEVENTTABLE                                     STD_OFF
#define DEM_CFG_ISDEF_SPECIALINDICATORTABLEUSEDOFEVENTTABLE                                         STD_OFF
#define DEM_CFG_ISDEF_EVENTTABLEIND                                                                 STD_OFF
#define DEM_CFG_ISDEF_EVENTTABLE_EREC2EVENTIDIND                                                    STD_OFF
#define DEM_CFG_ISDEF_EVENTTABLE_OBDRDYGROUP2EVENTIDIND                                             STD_OFF
#define DEM_CFG_ISDEF_DATACOLLECTIONTABLEEREC2COLLINDENDIDXOFEXTENDEDDATARECORDTABLE                STD_ON
#define DEM_CFG_ISDEF_DATACOLLECTIONTABLEEREC2COLLINDSTARTIDXOFEXTENDEDDATARECORDTABLE              STD_ON
#define DEM_CFG_ISDEF_DATACOLLECTIONTABLEEREC2COLLINDUSEDOFEXTENDEDDATARECORDTABLE                  STD_ON
#define DEM_CFG_ISDEF_DATACOLLECTIONTABLEEDR2COLLINDENDIDXOFEXTENDEDDATATABLE                       STD_OFF
#define DEM_CFG_ISDEF_DATACOLLECTIONTABLEEDR2COLLINDSTARTIDXOFEXTENDEDDATATABLE                     STD_OFF
#define DEM_CFG_ISDEF_DATACOLLECTIONTABLEEDR2COLLINDUSEDOFEXTENDEDDATATABLE                         STD_OFF
#define DEM_CFG_ISDEF_MAXRECORDSIZEOFEXTENDEDDATATABLE                                              STD_OFF
#define DEM_CFG_ISDEF_FFNUMBEROFFREEZEFRAMENUMTABLE                                                 STD_ON
#define DEM_CFG_ISDEF_FFTRIGGEROFFREEZEFRAMENUMTABLE                                                STD_ON
#define DEM_CFG_ISDEF_FFUPDATEOFFREEZEFRAMENUMTABLE                                                 STD_ON
#define DEM_CFG_ISDEF_DATACOLLECTIONTABLEFFM2COLLINDENDIDXOFFREEZEFRAMETABLE                        STD_OFF
#define DEM_CFG_ISDEF_DATACOLLECTIONTABLEFFM2COLLINDSTARTIDXOFFREEZEFRAMETABLE                      STD_OFF
#define DEM_CFG_ISDEF_DATACOLLECTIONTABLEFFM2COLLINDUSEDOFFREEZEFRAMETABLE                          STD_OFF
#define DEM_CFG_ISDEF_RECORDSIZEOFFREEZEFRAMETABLE                                                  STD_ON
#define DEM_CFG_ISDEF_RECORDSIZEUDSOFFASTRATETIMESERIESPOWERTRAINOFFREEZEFRAMETABLE                 STD_ON
#define DEM_CFG_ISDEF_RECORDSIZEUDSOFFREEZEFRAMETABLE                                               STD_OFF
#define DEM_CFG_ISDEF_RECORDSIZEUDSOFNORMALRATETIMESERIESPOWERTRAINOFFREEZEFRAMETABLE               STD_ON
#define DEM_CFG_ISDEF_DATACOLLECTIONTABLEJ19392COLLINDENDIDXOFGENERALJ1939TABLE                     STD_OFF
#define DEM_CFG_ISDEF_DATACOLLECTIONTABLEJ19392COLLINDSTARTIDXOFGENERALJ1939TABLE                   STD_OFF
#define DEM_CFG_ISDEF_DATACOLLECTIONTABLEJ19392COLLINDUSEDOFGENERALJ1939TABLE                       STD_OFF
#define DEM_CFG_ISDEF_RECORDSIZEOFGENERALJ1939TABLE                                                 STD_OFF
#define DEM_CFG_ISDEF_DATAELEMENTTABLEIDXOFGENERALOBDINPUT                                          STD_ON
#define DEM_CFG_ISDEF_INITMONITORFOREVENT                                                           STD_OFF
#define DEM_CFG_ISDEF_INITMONITORSFORFUNC                                                           STD_OFF
#define DEM_CFG_ISDEF_J1939NODEID                                                                   STD_OFF
#define DEM_CFG_ISDEF_J1939NODEIDIND                                                                STD_OFF
#define DEM_CFG_ISDEF_J1939NODEINDICATOR                                                            STD_OFF
#define DEM_CFG_ISDEF_MEMORYBLOCKID                                                                 STD_OFF
#define DEM_CFG_ISDEF_MEMORYBLOCKIDTOMEMORYENTRYID                                                  STD_OFF
#define DEM_CFG_ISDEF_MEMORYDATAPTR                                                                 STD_OFF
#define DEM_CFG_ISDEF_MEMORYDATASIZE                                                                STD_OFF
#define DEM_CFG_ISDEF_MEMORYENTRY                                                                   STD_OFF
#define DEM_CFG_ISDEF_DTRTABLEIDXOFMIDTABLE                                                         STD_OFF
#define DEM_CFG_ISDEF_MIDOFMIDTABLE                                                                 STD_OFF
#define DEM_CFG_ISDEF_TIDOFMIDTABLE                                                                 STD_OFF
#define DEM_CFG_ISDEF_BEHAVIOROFNORMALINDICATORTABLE                                                STD_OFF
#define DEM_CFG_ISDEF_IDOFNORMALINDICATORTABLE                                                      STD_OFF
#define DEM_CFG_ISDEF_DATACOLLECTIONTABLEPID2COLLINDENDIDXOFPIDTABLE                                STD_OFF
#define DEM_CFG_ISDEF_DATACOLLECTIONTABLEPID2COLLINDSTARTIDXOFPIDTABLE                              STD_OFF
#define DEM_CFG_ISDEF_DATACOLLECTIONTABLEPID2COLLINDUSEDOFPIDTABLE                                  STD_OFF
#define DEM_CFG_ISDEF_EVENTTABLE_OBDRDYGROUP2EVENTIDINDENDIDXOFREADINESSGROUPTABLE                  STD_OFF
#define DEM_CFG_ISDEF_EVENTTABLE_OBDRDYGROUP2EVENTIDINDSTARTIDXOFREADINESSGROUPTABLE                STD_OFF
#define DEM_CFG_ISDEF_EVENTTABLE_OBDRDYGROUP2EVENTIDINDUSEDOFREADINESSGROUPTABLE                    STD_OFF
#define DEM_CFG_ISDEF_READINESSGROUPOFREADINESSGROUPTABLE                                           STD_ON
#define DEM_CFG_ISDEF_APPLICATIONIDOFSATELLITEINFO                                                  STD_ON
#define DEM_CFG_ISDEF_DEBOUNCELORESTIMEROFSATELLITEINFO                                             STD_OFF
#define DEM_CFG_ISDEF_EVENTCOUNTOFSATELLITEINFO                                                     STD_ON
#define DEM_CFG_ISDEF_EVENTTABLEINDENDIDXOFSATELLITEINFO                                            STD_ON
#define DEM_CFG_ISDEF_EVENTTABLEINDSTARTIDXOFSATELLITEINFO                                          STD_ON
#define DEM_CFG_ISDEF_EVENTTABLEINDUSEDOFSATELLITEINFO                                              STD_ON
#define DEM_CFG_ISDEF_MAXDEBOUNCEVALUESOFSATELLITEINFO                                              STD_OFF
#define DEM_CFG_ISDEF_SATELLITEDATAOFSATELLITEINFO                                                  STD_ON
#define DEM_CFG_ISDEF_SATELLITEEXTENDEDDATAOFSATELLITEINFO                                          STD_OFF
#define DEM_CFG_ISDEF_SATELLITESTATUSOFSATELLITEINFO                                                STD_ON
#define DEM_CFG_ISDEF_DEBOUNCEHIRESTABLEENDIDXOFSATELLITETIMEDEBOUNCEINFO                           STD_OFF
#define DEM_CFG_ISDEF_DEBOUNCEHIRESTABLESTARTIDXOFSATELLITETIMEDEBOUNCEINFO                         STD_OFF
#define DEM_CFG_ISDEF_DEBOUNCEHIRESTABLEUSEDOFSATELLITETIMEDEBOUNCEINFO                             STD_OFF
#define DEM_CFG_ISDEF_DEBOUNCELORESTABLEENDIDXOFSATELLITETIMEDEBOUNCEINFO                           STD_OFF
#define DEM_CFG_ISDEF_DEBOUNCELORESTABLESTARTIDXOFSATELLITETIMEDEBOUNCEINFO                         STD_OFF
#define DEM_CFG_ISDEF_DEBOUNCELORESTABLEUSEDOFSATELLITETIMEDEBOUNCEINFO                             STD_OFF
#define DEM_CFG_ISDEF_BEHAVIOROFSPECIALINDICATORTABLE                                               STD_OFF
#define DEM_CFG_ISDEF_IDOFSPECIALINDICATORTABLE                                                     STD_OFF
#define DEM_CFG_ISDEF_INDEXOFSTORAGECONDITIONGROUPTABLE                                             STD_OFF
#define DEM_CFG_ISDEF_STORAGECONDITIONGROUPTABLEIND                                                 STD_OFF
#define DEM_CFG_ISDEF_FULFILLEDATINITOFSTORAGECONDITIONINITTABLE                                    STD_OFF
#define DEM_CFG_ISDEF_STORAGECONDITIONGROUPTABLEINDENDIDXOFSTORAGECONDITIONTABLE                    STD_OFF
#define DEM_CFG_ISDEF_STORAGECONDITIONGROUPTABLEINDSTARTIDXOFSTORAGECONDITIONTABLE                  STD_OFF
#define DEM_CFG_ISDEF_STORAGECONDITIONGROUPTABLEINDUSEDOFSTORAGECONDITIONTABLE                      STD_OFF
#define DEM_CFG_ISDEF_STARTIDXMIDTABLEOFSUPPORTEDMIDSTABLE                                          STD_OFF
#define DEM_CFG_ISDEF_SUPPORTEDMIDMASKOFSUPPORTEDMIDSTABLE                                          STD_OFF
#define DEM_CFG_ISDEF_ADMINDATAOFPCCONFIG                                                           STD_ON
#define DEM_CFG_ISDEF_AGINGDATAOFPCCONFIG                                                           STD_ON
#define DEM_CFG_ISDEF_CALLBACKCLEAREVENTALLOWEDOFPCCONFIG                                           STD_ON
#define DEM_CFG_ISDEF_CALLBACKDTCSTATUSCHANGEDOFPCCONFIG                                            STD_ON
#define DEM_CFG_ISDEF_CALLBACKGETFDCOFPCCONFIG                                                      STD_ON
#define DEM_CFG_ISDEF_CALLBACKJ1939DTCSTATUSCHANGEDOFPCCONFIG                                       STD_ON
#define DEM_CFG_ISDEF_CLEARDTCTABLEOFPCCONFIG                                                       STD_ON
#define DEM_CFG_ISDEF_CLEARDTCNOTIFICATIONFINISHTABLEOFPCCONFIG                                     STD_ON
#define DEM_CFG_ISDEF_CLEARDTCNOTIFICATIONSTARTTABLEOFPCCONFIG                                      STD_ON
#define DEM_CFG_ISDEF_CLIENTTABLEOFPCCONFIG                                                         STD_ON
#define DEM_CFG_ISDEF_COMMITBUFFEROFPCCONFIG                                                        STD_ON
#define DEM_CFG_ISDEF_CYCLECOUNTERDATAOFPCCONFIG                                                    STD_ON
#define DEM_CFG_ISDEF_CYCLEIDTABLEOFPCCONFIG                                                        STD_ON
#define DEM_CFG_ISDEF_DTCSELECTORTABLEOFPCCONFIG                                                    STD_ON
#define DEM_CFG_ISDEF_DATACOLLECTIONTABLEEDR2COLLINDOFPCCONFIG                                      STD_ON
#define DEM_CFG_ISDEF_DATACOLLECTIONTABLEEREC2COLLINDOFPCCONFIG                                     STD_ON
#define DEM_CFG_ISDEF_DATACOLLECTIONTABLEFFM2COLLINDOFPCCONFIG                                      STD_ON
#define DEM_CFG_ISDEF_DATACOLLECTIONTABLEJ19392COLLINDOFPCCONFIG                                    STD_ON
#define DEM_CFG_ISDEF_DATACOLLECTIONTABLEOFPCCONFIG                                                 STD_ON
#define DEM_CFG_ISDEF_DATACOLLECTIONTABLEPID2COLLINDOFPCCONFIG                                      STD_ON
#define DEM_CFG_ISDEF_DATAELEMENTTABLECOL2ELMTINDOFPCCONFIG                                         STD_ON
#define DEM_CFG_ISDEF_DATAELEMENTTABLEOFPCCONFIG                                                    STD_ON
#define DEM_CFG_ISDEF_DEBOUNCEDATAOFPCCONFIG                                                        STD_ON
#define DEM_CFG_ISDEF_DEBOUNCEHIRESTABLEOFPCCONFIG                                                  STD_ON
#define DEM_CFG_ISDEF_DEBOUNCELORESTABLEOFPCCONFIG                                                  STD_ON
#define DEM_CFG_ISDEF_DEBOUNCETABLEOFPCCONFIG                                                       STD_ON
#define DEM_CFG_ISDEF_DTCGROUPMASKOFPCCONFIG                                                        STD_ON
#define DEM_CFG_ISDEF_DTCTABLEOFPCCONFIG                                                            STD_ON
#define DEM_CFG_ISDEF_DTRDATAOFPCCONFIG                                                             STD_ON
#define DEM_CFG_ISDEF_DTRSTATUSOFPCCONFIG                                                           STD_ON
#define DEM_CFG_ISDEF_DTRTABLEINDOFPCCONFIG                                                         STD_ON
#define DEM_CFG_ISDEF_DTRTABLEOFPCCONFIG                                                            STD_ON
#define DEM_CFG_ISDEF_ENABLECONDITIONFULFILLEDOFPCCONFIG                                            STD_ON
#define DEM_CFG_ISDEF_ENABLECONDITIONGROUPCOUNTEROFPCCONFIG                                         STD_ON
#define DEM_CFG_ISDEF_ENABLECONDITIONGROUPSTATEOFPCCONFIG                                           STD_ON
#define DEM_CFG_ISDEF_ENABLECONDITIONGROUPTABLEINDOFPCCONFIG                                        STD_ON
#define DEM_CFG_ISDEF_ENABLECONDITIONGROUPTABLEOFPCCONFIG                                           STD_ON
#define DEM_CFG_ISDEF_ENABLECONDITIONINITTABLEOFPCCONFIG                                            STD_ON
#define DEM_CFG_ISDEF_ENABLECONDITIONTABLEOFPCCONFIG                                                STD_ON
#define DEM_CFG_ISDEF_EVENTAVAILABLEDATAOFPCCONFIG                                                  STD_ON
#define DEM_CFG_ISDEF_EVENTAVAILABLEDEFAULTOFPCCONFIG                                               STD_ON
#define DEM_CFG_ISDEF_EVENTAVAILABLEINVARIANTOFPCCONFIG                                             STD_ON
#define DEM_CFG_ISDEF_EVENTCYCLESTATUSOFPCCONFIG                                                    STD_ON
#define DEM_CFG_ISDEF_EVENTDATACHANGEDOFPCCONFIG                                                    STD_ON
#define DEM_CFG_ISDEF_EVENTDATACOMMITNUMBEROFPCCONFIG                                               STD_ON
#define DEM_CFG_ISDEF_EVENTDEBOUNCEVALUEOFPCCONFIG                                                  STD_ON
#define DEM_CFG_ISDEF_EVENTINTERNALSTATUSOFPCCONFIG                                                 STD_ON
#define DEM_CFG_ISDEF_EVENTSTATUSCHANGEDOFPCCONFIG                                                  STD_ON
#define DEM_CFG_ISDEF_EVENTTABLEINDOFPCCONFIG                                                       STD_ON
#define DEM_CFG_ISDEF_EVENTTABLEOFPCCONFIG                                                          STD_ON
#define DEM_CFG_ISDEF_EVENTTABLE_EREC2EVENTIDINDOFPCCONFIG                                          STD_ON
#define DEM_CFG_ISDEF_EVENTTABLE_OBDRDYGROUP2EVENTIDINDOFPCCONFIG                                   STD_ON
#define DEM_CFG_ISDEF_EXTENDEDDATARECORDITERATORTABLEOFPCCONFIG                                     STD_ON
#define DEM_CFG_ISDEF_EXTENDEDDATARECORDTABLEOFPCCONFIG                                             STD_ON
#define DEM_CFG_ISDEF_EXTENDEDDATATABLEOFPCCONFIG                                                   STD_ON
#define DEM_CFG_ISDEF_FILTERINFOTABLEOFPCCONFIG                                                     STD_ON
#define DEM_CFG_ISDEF_FILTERREPORTEDEVENTSOFPCCONFIG                                                STD_ON
#define DEM_CFG_ISDEF_FREEZEFRAMEDATAOFPCCONFIG                                                     STD_ON
#define DEM_CFG_ISDEF_FREEZEFRAMEITERATORTABLEOFPCCONFIG                                            STD_ON
#define DEM_CFG_ISDEF_FREEZEFRAMENUMTABLEOFPCCONFIG                                                 STD_ON
#define DEM_CFG_ISDEF_FREEZEFRAMETABLEOFPCCONFIG                                                    STD_ON
#define DEM_CFG_ISDEF_GENERALJ1939TABLEOFPCCONFIG                                                   STD_ON
#define DEM_CFG_ISDEF_GENERALOBDINPUTOFPCCONFIG                                                     STD_ON
#define DEM_CFG_ISDEF_GLOBALINDICATORSTATESOFPCCONFIG                                               STD_ON
#define DEM_CFG_ISDEF_INDICATORBLINKINGOFPCCONFIG                                                   STD_ON
#define DEM_CFG_ISDEF_INDICATORCONTINUOUSOFPCCONFIG                                                 STD_ON
#define DEM_CFG_ISDEF_INDICATORFASTFLASHOFPCCONFIG                                                  STD_ON
#define DEM_CFG_ISDEF_INDICATORSLOWFLASHOFPCCONFIG                                                  STD_ON
#define DEM_CFG_ISDEF_INITMONLISTFORFUNCOFPCCONFIG                                                  STD_ON
#define DEM_CFG_ISDEF_INITMONITORFOREVENTOFPCCONFIG                                                 STD_ON
#define DEM_CFG_ISDEF_INITMONITORSFORFUNCOFPCCONFIG                                                 STD_ON
#define DEM_CFG_ISDEF_J1939NODEIDINDOFPCCONFIG                                                      STD_ON
#define DEM_CFG_ISDEF_J1939NODEIDOFPCCONFIG                                                         STD_ON
#define DEM_CFG_ISDEF_J1939NODEINDICATOROFPCCONFIG                                                  STD_ON
#define DEM_CFG_ISDEF_MEMORYBLOCKIDOFPCCONFIG                                                       STD_ON
#define DEM_CFG_ISDEF_MEMORYBLOCKIDTOMEMORYENTRYIDOFPCCONFIG                                        STD_ON
#define DEM_CFG_ISDEF_MEMORYDATAPTROFPCCONFIG                                                       STD_ON
#define DEM_CFG_ISDEF_MEMORYDATASIZEOFPCCONFIG                                                      STD_ON
#define DEM_CFG_ISDEF_MEMORYENTRYINITOFPCCONFIG                                                     STD_ON
#define DEM_CFG_ISDEF_MEMORYENTRYOFPCCONFIG                                                         STD_ON
#define DEM_CFG_ISDEF_MEMORYSTATUSOFPCCONFIG                                                        STD_ON
#define DEM_CFG_ISDEF_MIDTABLEOFPCCONFIG                                                            STD_ON
#define DEM_CFG_ISDEF_MIRRORDATAOFPCCONFIG                                                          STD_ON
#define DEM_CFG_ISDEF_NORMALINDICATORTABLEOFPCCONFIG                                                STD_ON
#define DEM_CFG_ISDEF_OBDIUMPRDATAOFPCCONFIG                                                        STD_ON
#define DEM_CFG_ISDEF_OBDIUMPRUPDATEPENDINGOFPCCONFIG                                               STD_ON
#define DEM_CFG_ISDEF_PERMANENTDATAOFPCCONFIG                                                       STD_ON
#define DEM_CFG_ISDEF_PIDTABLEOFPCCONFIG                                                            STD_ON
#define DEM_CFG_ISDEF_PRESTORAGEINDEXOFPCCONFIG                                                     STD_ON
#define DEM_CFG_ISDEF_PRESTORAGEOFPCCONFIG                                                          STD_ON
#define DEM_CFG_ISDEF_PRIMARYCHRONOLOGYOFPCCONFIG                                                   STD_ON
#define DEM_CFG_ISDEF_PRIMARYENTRY_0OFPCCONFIG                                                      STD_ON
#define DEM_CFG_ISDEF_PRIMARYENTRY_1OFPCCONFIG                                                      STD_ON
#define DEM_CFG_ISDEF_PRIMARYENTRY_2OFPCCONFIG                                                      STD_ON
#define DEM_CFG_ISDEF_PRIMARYENTRY_3OFPCCONFIG                                                      STD_ON
#define DEM_CFG_ISDEF_PRIMARYENTRY_4OFPCCONFIG                                                      STD_ON
#define DEM_CFG_ISDEF_PRIMARYENTRY_5OFPCCONFIG                                                      STD_ON
#define DEM_CFG_ISDEF_PRIMARYENTRY_6OFPCCONFIG                                                      STD_ON
#define DEM_CFG_ISDEF_PRIMARYENTRY_7OFPCCONFIG                                                      STD_ON
#define DEM_CFG_ISDEF_RATIOIDTABLEOFPCCONFIG                                                        STD_ON
#define DEM_CFG_ISDEF_READINESSGROUPTABLEOFPCCONFIG                                                 STD_ON
#define DEM_CFG_ISDEF_READOUTBUFFEROFPCCONFIG                                                       STD_ON
#define DEM_CFG_ISDEF_REPORTEDEVENTSOFFILTEROFPCCONFIG                                              STD_ON
#define DEM_CFG_ISDEF_SATELLITEINFO0OFPCCONFIG                                                      STD_ON
#define DEM_CFG_ISDEF_SATELLITEINFOOFPCCONFIG                                                       STD_ON
#define DEM_CFG_ISDEF_SATELLITETIMEDEBOUNCEINFOOFPCCONFIG                                           STD_ON
#define DEM_CFG_ISDEF_SECONDARYCHRONOLOGYOFPCCONFIG                                                 STD_ON
#define DEM_CFG_ISDEF_SPECIALINDICATORTABLEOFPCCONFIG                                               STD_ON
#define DEM_CFG_ISDEF_STARTIDX500MIDENRATIOTABLEOFPCCONFIG                                          STD_ON
#define DEM_CFG_ISDEF_STATUSDATAOFPCCONFIG                                                          STD_ON
#define DEM_CFG_ISDEF_STORAGECONDITIONFULFILLEDOFPCCONFIG                                           STD_ON
#define DEM_CFG_ISDEF_STORAGECONDITIONGROUPCOUNTEROFPCCONFIG                                        STD_ON
#define DEM_CFG_ISDEF_STORAGECONDITIONGROUPTABLEINDOFPCCONFIG                                       STD_ON
#define DEM_CFG_ISDEF_STORAGECONDITIONGROUPTABLEOFPCCONFIG                                          STD_ON
#define DEM_CFG_ISDEF_STORAGECONDITIONINITTABLEOFPCCONFIG                                           STD_ON
#define DEM_CFG_ISDEF_STORAGECONDITIONTABLEOFPCCONFIG                                               STD_ON
#define DEM_CFG_ISDEF_SUPPORTEDMIDSTABLEOFPCCONFIG                                                  STD_ON
#define DEM_CFG_ISDEF_TIMESERIESCHRONOLOGYOFPCCONFIG                                                STD_ON
#define DEM_CFG_ISDEF_TIMESERIESENTRYINITOFPCCONFIG                                                 STD_ON
/** 
  \}
*/ 

/** 
  \defgroup  Dem_CfgPCEqualsAlwaysToDefines  Dem_Cfg Equals Always To Defines (PRE_COMPILE)
  \brief  If all values in a CONST array or an element in a CONST array of structs are equal, the define contains the always equals value.
  \{
*/ 
#define DEM_CFG_EQ2_CALLBACKCLEAREVENTALLOWED                                                       
#define DEM_CFG_EQ2_CALLBACKDTCSTATUSCHANGED                                                        
#define DEM_CFG_EQ2_CALLBACKGETFDC                                                                  
#define DEM_CFG_EQ2_CALLBACKJ1939DTCSTATUSCHANGED                                                   
#define DEM_CFG_EQ2_CLEARDTCNOTIFICATIONFINISHTABLE                                                 
#define DEM_CFG_EQ2_CLEARDTCNOTIFICATIONSTARTTABLE                                                  
#define DEM_CFG_EQ2_CLEARDTCINDEXOFCLIENTTABLE                                                      0u
#define DEM_CFG_EQ2_FILTERINDEXOFCLIENTTABLE                                                        0u
#define DEM_CFG_EQ2_FREEZEFRAMEITERATORINDEXOFCLIENTTABLE                                           0u
#define DEM_CFG_EQ2_NMNODEIDOFCLIENTTABLE                                                           
#define DEM_CFG_EQ2_READOUTBUFFERINDEXOFCLIENTTABLE                                                 0u
#define DEM_CFG_EQ2_SELECTORINDEXOFCLIENTTABLE                                                      0u
#define DEM_CFG_EQ2_ENDSONINITOFCYCLEIDTABLE                                                        
#define DEM_CFG_EQ2_MASKEDBITSOFCYCLEIDTABLE                                                        
#define DEM_CFG_EQ2_OPCYCLETYPEOFCYCLEIDTABLE                                                       
#define DEM_CFG_EQ2_USEDFORAGINGOFCYCLEIDTABLE                                                      
#define DEM_CFG_EQ2_COLLECTIONSIZEOFDATACOLLECTIONTABLE                                             
#define DEM_CFG_EQ2_DATAELEMENTTABLECOL2ELMTINDENDIDXOFDATACOLLECTIONTABLE                          
#define DEM_CFG_EQ2_DATAELEMENTTABLECOL2ELMTINDSTARTIDXOFDATACOLLECTIONTABLE                        
#define DEM_CFG_EQ2_DATAELEMENTTABLECOL2ELMTINDUSEDOFDATACOLLECTIONTABLE                            
#define DEM_CFG_EQ2_DIDOFFSETFASTOFDATACOLLECTIONTABLE                                              
#define DEM_CFG_EQ2_DIDOFFSETNORMALOFDATACOLLECTIONTABLE                                            
#define DEM_CFG_EQ2_EVENTTABLE_EREC2EVENTIDINDENDIDXOFDATACOLLECTIONTABLE                           
#define DEM_CFG_EQ2_EVENTTABLE_EREC2EVENTIDINDSTARTIDXOFDATACOLLECTIONTABLE                         
#define DEM_CFG_EQ2_EVENTTABLE_EREC2EVENTIDINDUSEDOFDATACOLLECTIONTABLE                             
#define DEM_CFG_EQ2_IDNUMBEROFDATACOLLECTIONTABLE                                                   
#define DEM_CFG_EQ2_STORAGEKINDOFDATACOLLECTIONTABLE                                                
#define DEM_CFG_EQ2_TRIGGEROFDATACOLLECTIONTABLE                                                    DEM_CFG_TRIGGER_NONE
#define DEM_CFG_EQ2_UPDATEOFDATACOLLECTIONTABLE                                                     
#define DEM_CFG_EQ2_DATACOLLECTIONTABLEEDR2COLLIND                                                  
#define DEM_CFG_EQ2_DATACOLLECTIONTABLEEREC2COLLIND                                                 
#define DEM_CFG_EQ2_DATACOLLECTIONTABLEFFM2COLLIND                                                  
#define DEM_CFG_EQ2_DATACOLLECTIONTABLEJ19392COLLIND                                                
#define DEM_CFG_EQ2_DATACOLLECTIONTABLEPID2COLLIND                                                  
#define DEM_CFG_EQ2_DATAISSTOREDINNVOFDATAELEMENTTABLE                                              
#define DEM_CFG_EQ2_ELEMENTKINDOFDATAELEMENTTABLE                                                   
#define DEM_CFG_EQ2_ELEMENTSIZEOFDATAELEMENTTABLE                                                   
#define DEM_CFG_EQ2_READDATAFUNCOFDATAELEMENTTABLE                                                  
#define DEM_CFG_EQ2_DATAELEMENTTABLECOL2ELMTIND                                                     
#define DEM_CFG_EQ2_DEBOUNCEHIRESTABLE                                                              
#define DEM_CFG_EQ2_DEBOUNCELORESTABLE                                                              
#define DEM_CFG_EQ2_DEBOUNCECONTINUOUSOFDEBOUNCETABLE                                               FALSE
#define DEM_CFG_EQ2_DECREMENTSTEPSIZEOFDEBOUNCETABLE                                                
#define DEM_CFG_EQ2_EVENTDEBOUNCEALGORITHMOFDEBOUNCETABLE                                           
#define DEM_CFG_EQ2_EVENTDEBOUNCEBEHAVIOROFDEBOUNCETABLE                                            
#define DEM_CFG_EQ2_FAILTIMERCYCLESOFDEBOUNCETABLE                                                  0
#define DEM_CFG_EQ2_FAILEDTHRESHOLDOFDEBOUNCETABLE                                                  
#define DEM_CFG_EQ2_INCREMENTSTEPSIZEOFDEBOUNCETABLE                                                
#define DEM_CFG_EQ2_JUMPDOWNOFDEBOUNCETABLE                                                         
#define DEM_CFG_EQ2_JUMPDOWNVALUEOFDEBOUNCETABLE                                                    0
#define DEM_CFG_EQ2_JUMPUPOFDEBOUNCETABLE                                                           
#define DEM_CFG_EQ2_JUMPUPVALUEOFDEBOUNCETABLE                                                      0
#define DEM_CFG_EQ2_MASKEDBITSOFDEBOUNCETABLE                                                       
#define DEM_CFG_EQ2_PASSTIMERCYCLESOFDEBOUNCETABLE                                                  0
#define DEM_CFG_EQ2_PASSEDTHRESHOLDOFDEBOUNCETABLE                                                  
#define DEM_CFG_EQ2_PRECONFIRMEDTHRESHOLDOFDEBOUNCETABLE                                            
#define DEM_CFG_EQ2_STORAGEOFDEBOUNCETABLE                                                          FALSE
#define DEM_CFG_EQ2_STORAGETHRESHOLDOFDEBOUNCETABLE                                                 
#define DEM_CFG_EQ2_STORAGETIMERCYCLESOFDEBOUNCETABLE                                               
#define DEM_CFG_EQ2_GROUPMASKOFDTCGROUPMASK                                                         
#define DEM_CFG_EQ2_UDSGROUPDTCOFDTCGROUPMASK                                                       
#define DEM_CFG_EQ2_DTCSEVERITYOFDTCTABLE                                                           0u
#define DEM_CFG_EQ2_FUNCTIONALUNITOFDTCTABLE                                                        
#define DEM_CFG_EQ2_IMMEDIATENVSTORAGEOFDTCTABLE                                                    FALSE
#define DEM_CFG_EQ2_J1939DTCOFDTCTABLE                                                              
#define DEM_CFG_EQ2_J1939NODEIDINDENDIDXOFDTCTABLE                                                  
#define DEM_CFG_EQ2_J1939NODEIDINDSTARTIDXOFDTCTABLE                                                
#define DEM_CFG_EQ2_J1939NODEIDINDUSEDOFDTCTABLE                                                    
#define DEM_CFG_EQ2_OBDDTCOFDTCTABLE                                                                
#define DEM_CFG_EQ2_UDSDTCOFDTCTABLE                                                                
#define DEM_CFG_EQ2_DIVISOROFDTRTABLE                                                               
#define DEM_CFG_EQ2_EVENTTABLEIDXOFDTRTABLE                                                         
#define DEM_CFG_EQ2_LINEARFACTOROFDTRTABLE                                                          
#define DEM_CFG_EQ2_OFFSETOFDTRTABLE                                                                
#define DEM_CFG_EQ2_UASIDOFDTRTABLE                                                                 
#define DEM_CFG_EQ2_UPDATEKINDOFDTRTABLE                                                            
#define DEM_CFG_EQ2_DTRTABLEIND                                                                     
#define DEM_CFG_EQ2_INDEXOFENABLECONDITIONGROUPTABLE                                                
#define DEM_CFG_EQ2_ENABLECONDITIONGROUPTABLEIND                                                    
#define DEM_CFG_EQ2_FULFILLEDATINITOFENABLECONDITIONINITTABLE                                       
#define DEM_CFG_EQ2_ENABLECONDITIONGROUPTABLEINDENDIDXOFENABLECONDITIONTABLE                        
#define DEM_CFG_EQ2_ENABLECONDITIONGROUPTABLEINDSTARTIDXOFENABLECONDITIONTABLE                      
#define DEM_CFG_EQ2_ENABLECONDITIONGROUPTABLEINDUSEDOFENABLECONDITIONTABLE                          TRUE
#define DEM_CFG_EQ2_EVENTAVAILABLEDEFAULT                                                           TRUE
#define DEM_CFG_EQ2_EVENTAVAILABLEINVARIANT                                                         TRUE
#define DEM_CFG_EQ2_EVENTDATACHANGED                                                                
#define DEM_CFG_EQ2_EVENTSTATUSCHANGED                                                              
#define DEM_CFG_EQ2_AGINGALLOWEDOFEVENTTABLE                                                        
#define DEM_CFG_EQ2_AGINGCYCLECOUNTERTHRESHOLDOFEVENTTABLE                                          
#define DEM_CFG_EQ2_AGINGCYCLEIDOFEVENTTABLE                                                        
#define DEM_CFG_EQ2_CALLBACKCLEAREVENTALLOWEDIDXOFEVENTTABLE                                        
#define DEM_CFG_EQ2_CALLBACKCLEAREVENTALLOWEDUSEDOFEVENTTABLE                                       TRUE
#define DEM_CFG_EQ2_CALLBACKGETFDCIDXOFEVENTTABLE                                                   
#define DEM_CFG_EQ2_DEBOUNCETABLEIDXOFEVENTTABLE                                                    
#define DEM_CFG_EQ2_DTCTABLEIDXOFEVENTTABLE                                                         
#define DEM_CFG_EQ2_DTRTABLEINDENDIDXOFEVENTTABLE                                                   
#define DEM_CFG_EQ2_DTRTABLEINDSTARTIDXOFEVENTTABLE                                                 
#define DEM_CFG_EQ2_DTRTABLEINDUSEDOFEVENTTABLE                                                     
#define DEM_CFG_EQ2_ENABLECONDITIONGROUPTABLEIDXOFEVENTTABLE                                        
#define DEM_CFG_EQ2_EVENTDESTINATIONOFEVENTTABLE                                                    DEM_CFG_MEMORYID_PRIMARY
#define DEM_CFG_EQ2_EVENTFAILURECYCLECOUNTERTHRESHOLDOFEVENTTABLE                                   1u
#define DEM_CFG_EQ2_EVENTKINDOFEVENTTABLE                                                           
#define DEM_CFG_EQ2_EVENTLATCHTFOFEVENTTABLE                                                        FALSE
#define DEM_CFG_EQ2_EVENTPRIORITYOFEVENTTABLE                                                       
#define DEM_CFG_EQ2_EVENTSIGNIFICANCEOFEVENTTABLE                                                   DEM_CFG_DEM_EVENT_SIGNIFICANCE_FAULT_EVENTSIGNIFICANCEOFEVENTTABLE
#define DEM_CFG_EQ2_EXTENDEDDATATABLEIDXOFEVENTTABLE                                                1u
#define DEM_CFG_EQ2_FAILEDCYCLECOUNTERINDEXOFEVENTTABLE                                             
#define DEM_CFG_EQ2_FAULTPENDINGCOUNTERINDEXOFEVENTTABLE                                            
#define DEM_CFG_EQ2_FREEZEFRAMENUMTABLEENDIDXOFEVENTTABLE                                           1u
#define DEM_CFG_EQ2_FREEZEFRAMENUMTABLESTARTIDXOFEVENTTABLE                                         0u
#define DEM_CFG_EQ2_FREEZEFRAMENUMTABLEUSEDOFEVENTTABLE                                             TRUE
#define DEM_CFG_EQ2_FREEZEFRAMETABLESTDFFIDXOFEVENTTABLE                                            1u
#define DEM_CFG_EQ2_HEALINGTARGETOFEVENTTABLE                                                       0u
#define DEM_CFG_EQ2_MASKEDBITSOFEVENTTABLE                                                          
#define DEM_CFG_EQ2_OBDVISIBILITYDELAYEDUNTILDCYQUALIFICATIONOFEVENTTABLE                           TRUE
#define DEM_CFG_EQ2_OPERATIONCYCLEIDOFEVENTTABLE                                                    DemConf_DemOperationCycle_PowerCycle
#define DEM_CFG_EQ2_SATELLITEEVENTIDXOFEVENTTABLE                                                   
#define DEM_CFG_EQ2_SATELLITEINFOIDXOFEVENTTABLE                                                    0u
#define DEM_CFG_EQ2_SPECIALINDICATORTABLEENDIDXOFEVENTTABLE                                         
#define DEM_CFG_EQ2_SPECIALINDICATORTABLESTARTIDXOFEVENTTABLE                                       
#define DEM_CFG_EQ2_SPECIALINDICATORTABLEUSEDOFEVENTTABLE                                           
#define DEM_CFG_EQ2_EVENTTABLEIND                                                                   
#define DEM_CFG_EQ2_EVENTTABLE_EREC2EVENTIDIND                                                      
#define DEM_CFG_EQ2_EVENTTABLE_OBDRDYGROUP2EVENTIDIND                                               
#define DEM_CFG_EQ2_DATACOLLECTIONTABLEEREC2COLLINDENDIDXOFEXTENDEDDATARECORDTABLE                  2u
#define DEM_CFG_EQ2_DATACOLLECTIONTABLEEREC2COLLINDSTARTIDXOFEXTENDEDDATARECORDTABLE                0u
#define DEM_CFG_EQ2_DATACOLLECTIONTABLEEREC2COLLINDUSEDOFEXTENDEDDATARECORDTABLE                    TRUE
#define DEM_CFG_EQ2_DATACOLLECTIONTABLEEDR2COLLINDENDIDXOFEXTENDEDDATATABLE                         
#define DEM_CFG_EQ2_DATACOLLECTIONTABLEEDR2COLLINDSTARTIDXOFEXTENDEDDATATABLE                       
#define DEM_CFG_EQ2_DATACOLLECTIONTABLEEDR2COLLINDUSEDOFEXTENDEDDATATABLE                           
#define DEM_CFG_EQ2_MAXRECORDSIZEOFEXTENDEDDATATABLE                                                
#define DEM_CFG_EQ2_FFNUMBEROFFREEZEFRAMENUMTABLE                                                   1u
#define DEM_CFG_EQ2_FFTRIGGEROFFREEZEFRAMENUMTABLE                                                  DEM_CFG_TRIGGER_CONFIRMED
#define DEM_CFG_EQ2_FFUPDATEOFFREEZEFRAMENUMTABLE                                                   FALSE
#define DEM_CFG_EQ2_DATACOLLECTIONTABLEFFM2COLLINDENDIDXOFFREEZEFRAMETABLE                          
#define DEM_CFG_EQ2_DATACOLLECTIONTABLEFFM2COLLINDSTARTIDXOFFREEZEFRAMETABLE                        
#define DEM_CFG_EQ2_DATACOLLECTIONTABLEFFM2COLLINDUSEDOFFREEZEFRAMETABLE                            
#define DEM_CFG_EQ2_RECORDSIZEOFFREEZEFRAMETABLE                                                    0u
#define DEM_CFG_EQ2_RECORDSIZEUDSOFFASTRATETIMESERIESPOWERTRAINOFFREEZEFRAMETABLE                   0u
#define DEM_CFG_EQ2_RECORDSIZEUDSOFFREEZEFRAMETABLE                                                 
#define DEM_CFG_EQ2_RECORDSIZEUDSOFNORMALRATETIMESERIESPOWERTRAINOFFREEZEFRAMETABLE                 0u
#define DEM_CFG_EQ2_DATACOLLECTIONTABLEJ19392COLLINDENDIDXOFGENERALJ1939TABLE                       
#define DEM_CFG_EQ2_DATACOLLECTIONTABLEJ19392COLLINDSTARTIDXOFGENERALJ1939TABLE                     
#define DEM_CFG_EQ2_DATACOLLECTIONTABLEJ19392COLLINDUSEDOFGENERALJ1939TABLE                         
#define DEM_CFG_EQ2_RECORDSIZEOFGENERALJ1939TABLE                                                   
#define DEM_CFG_EQ2_DATAELEMENTTABLEIDXOFGENERALOBDINPUT                                            0u
#define DEM_CFG_EQ2_INITMONITORFOREVENT                                                             
#define DEM_CFG_EQ2_INITMONITORSFORFUNC                                                             
#define DEM_CFG_EQ2_J1939NODEID                                                                     
#define DEM_CFG_EQ2_J1939NODEIDIND                                                                  
#define DEM_CFG_EQ2_J1939NODEINDICATOR                                                              
#define DEM_CFG_EQ2_MEMORYBLOCKID                                                                   
#define DEM_CFG_EQ2_MEMORYBLOCKIDTOMEMORYENTRYID                                                    
#define DEM_CFG_EQ2_MEMORYDATAPTR                                                                   
#define DEM_CFG_EQ2_MEMORYDATASIZE                                                                  
#define DEM_CFG_EQ2_MEMORYENTRY                                                                     
#define DEM_CFG_EQ2_DTRTABLEIDXOFMIDTABLE                                                           
#define DEM_CFG_EQ2_MIDOFMIDTABLE                                                                   
#define DEM_CFG_EQ2_TIDOFMIDTABLE                                                                   
#define DEM_CFG_EQ2_BEHAVIOROFNORMALINDICATORTABLE                                                  
#define DEM_CFG_EQ2_IDOFNORMALINDICATORTABLE                                                        
#define DEM_CFG_EQ2_DATACOLLECTIONTABLEPID2COLLINDENDIDXOFPIDTABLE                                  
#define DEM_CFG_EQ2_DATACOLLECTIONTABLEPID2COLLINDSTARTIDXOFPIDTABLE                                
#define DEM_CFG_EQ2_DATACOLLECTIONTABLEPID2COLLINDUSEDOFPIDTABLE                                    
#define DEM_CFG_EQ2_EVENTTABLE_OBDRDYGROUP2EVENTIDINDENDIDXOFREADINESSGROUPTABLE                    
#define DEM_CFG_EQ2_EVENTTABLE_OBDRDYGROUP2EVENTIDINDSTARTIDXOFREADINESSGROUPTABLE                  
#define DEM_CFG_EQ2_EVENTTABLE_OBDRDYGROUP2EVENTIDINDUSEDOFREADINESSGROUPTABLE                      
#define DEM_CFG_EQ2_READINESSGROUPOFREADINESSGROUPTABLE                                             DEM_CFG_READINESS_GROUP_INVALID
#define DEM_CFG_EQ2_APPLICATIONIDOFSATELLITEINFO                                                    0
#define DEM_CFG_EQ2_DEBOUNCELORESTIMEROFSATELLITEINFO                                               
#define DEM_CFG_EQ2_EVENTCOUNTOFSATELLITEINFO                                                       16u
#define DEM_CFG_EQ2_EVENTTABLEINDENDIDXOFSATELLITEINFO                                              16u
#define DEM_CFG_EQ2_EVENTTABLEINDSTARTIDXOFSATELLITEINFO                                            0u
#define DEM_CFG_EQ2_EVENTTABLEINDUSEDOFSATELLITEINFO                                                TRUE
#define DEM_CFG_EQ2_MAXDEBOUNCEVALUESOFSATELLITEINFO                                                
#define DEM_CFG_EQ2_SATELLITEDATAOFSATELLITEINFO                                                    &Dem_Cfg_SatelliteInfo0.SatelliteData[0]
#define DEM_CFG_EQ2_SATELLITEEXTENDEDDATAOFSATELLITEINFO                                            
#define DEM_CFG_EQ2_SATELLITESTATUSOFSATELLITEINFO                                                  &Dem_Cfg_SatelliteInfo0.SatelliteStatus
#define DEM_CFG_EQ2_DEBOUNCEHIRESTABLEENDIDXOFSATELLITETIMEDEBOUNCEINFO                             
#define DEM_CFG_EQ2_DEBOUNCEHIRESTABLESTARTIDXOFSATELLITETIMEDEBOUNCEINFO                           
#define DEM_CFG_EQ2_DEBOUNCEHIRESTABLEUSEDOFSATELLITETIMEDEBOUNCEINFO                               
#define DEM_CFG_EQ2_DEBOUNCELORESTABLEENDIDXOFSATELLITETIMEDEBOUNCEINFO                             
#define DEM_CFG_EQ2_DEBOUNCELORESTABLESTARTIDXOFSATELLITETIMEDEBOUNCEINFO                           
#define DEM_CFG_EQ2_DEBOUNCELORESTABLEUSEDOFSATELLITETIMEDEBOUNCEINFO                               
#define DEM_CFG_EQ2_BEHAVIOROFSPECIALINDICATORTABLE                                                 
#define DEM_CFG_EQ2_IDOFSPECIALINDICATORTABLE                                                       
#define DEM_CFG_EQ2_INDEXOFSTORAGECONDITIONGROUPTABLE                                               
#define DEM_CFG_EQ2_STORAGECONDITIONGROUPTABLEIND                                                   
#define DEM_CFG_EQ2_FULFILLEDATINITOFSTORAGECONDITIONINITTABLE                                      
#define DEM_CFG_EQ2_STORAGECONDITIONGROUPTABLEINDENDIDXOFSTORAGECONDITIONTABLE                      
#define DEM_CFG_EQ2_STORAGECONDITIONGROUPTABLEINDSTARTIDXOFSTORAGECONDITIONTABLE                    
#define DEM_CFG_EQ2_STORAGECONDITIONGROUPTABLEINDUSEDOFSTORAGECONDITIONTABLE                        
#define DEM_CFG_EQ2_STARTIDXMIDTABLEOFSUPPORTEDMIDSTABLE                                            
#define DEM_CFG_EQ2_SUPPORTEDMIDMASKOFSUPPORTEDMIDSTABLE                                            
#define DEM_CFG_EQ2_ADMINDATAOFPCCONFIG                                                             (&(Dem_Cfg_AdminData))
#define DEM_CFG_EQ2_AGINGDATAOFPCCONFIG                                                             (&(Dem_Cfg_AgingData))
#define DEM_CFG_EQ2_CALLBACKCLEAREVENTALLOWEDOFPCCONFIG                                             Dem_Cfg_CallbackClearEventAllowed
#define DEM_CFG_EQ2_CALLBACKDTCSTATUSCHANGEDOFPCCONFIG                                              Dem_Cfg_CallbackDtcStatusChanged
#define DEM_CFG_EQ2_CALLBACKGETFDCOFPCCONFIG                                                        Dem_Cfg_CallbackGetFdc
#define DEM_CFG_EQ2_CALLBACKJ1939DTCSTATUSCHANGEDOFPCCONFIG                                         Dem_Cfg_CallbackJ1939DtcStatusChanged
#define DEM_CFG_EQ2_CLEARDTCTABLEOFPCCONFIG                                                         Dem_Cfg_ClearDTCTable
#define DEM_CFG_EQ2_CLEARDTCNOTIFICATIONFINISHTABLEOFPCCONFIG                                       Dem_Cfg_ClearDtcNotificationFinishTable
#define DEM_CFG_EQ2_CLEARDTCNOTIFICATIONSTARTTABLEOFPCCONFIG                                        Dem_Cfg_ClearDtcNotificationStartTable
#define DEM_CFG_EQ2_CLIENTTABLEOFPCCONFIG                                                           Dem_Cfg_ClientTable
#define DEM_CFG_EQ2_COMMITBUFFEROFPCCONFIG                                                          (&(Dem_Cfg_CommitBuffer))
#define DEM_CFG_EQ2_CYCLECOUNTERDATAOFPCCONFIG                                                      (&(Dem_Cfg_CycleCounterData))
#define DEM_CFG_EQ2_CYCLEIDTABLEOFPCCONFIG                                                          Dem_Cfg_CycleIdTable
#define DEM_CFG_EQ2_DTCSELECTORTABLEOFPCCONFIG                                                      Dem_Cfg_DTCSelectorTable
#define DEM_CFG_EQ2_DATACOLLECTIONTABLEEDR2COLLINDOFPCCONFIG                                        Dem_Cfg_DataCollectionTableEdr2CollInd
#define DEM_CFG_EQ2_DATACOLLECTIONTABLEEREC2COLLINDOFPCCONFIG                                       Dem_Cfg_DataCollectionTableErec2CollInd
#define DEM_CFG_EQ2_DATACOLLECTIONTABLEFFM2COLLINDOFPCCONFIG                                        Dem_Cfg_DataCollectionTableFfm2CollInd
#define DEM_CFG_EQ2_DATACOLLECTIONTABLEJ19392COLLINDOFPCCONFIG                                      Dem_Cfg_DataCollectionTableJ19392CollInd
#define DEM_CFG_EQ2_DATACOLLECTIONTABLEOFPCCONFIG                                                   Dem_Cfg_DataCollectionTable
#define DEM_CFG_EQ2_DATACOLLECTIONTABLEPID2COLLINDOFPCCONFIG                                        Dem_Cfg_DataCollectionTablePid2CollInd
#define DEM_CFG_EQ2_DATAELEMENTTABLECOL2ELMTINDOFPCCONFIG                                           Dem_Cfg_DataElementTableCol2ElmtInd
#define DEM_CFG_EQ2_DATAELEMENTTABLEOFPCCONFIG                                                      Dem_Cfg_DataElementTable
#define DEM_CFG_EQ2_DEBOUNCEDATAOFPCCONFIG                                                          (&(Dem_Cfg_DebounceData))
#define DEM_CFG_EQ2_DEBOUNCEHIRESTABLEOFPCCONFIG                                                    Dem_Cfg_DebounceHiResTable
#define DEM_CFG_EQ2_DEBOUNCELORESTABLEOFPCCONFIG                                                    Dem_Cfg_DebounceLoResTable
#define DEM_CFG_EQ2_DEBOUNCETABLEOFPCCONFIG                                                         Dem_Cfg_DebounceTable
#define DEM_CFG_EQ2_DTCGROUPMASKOFPCCONFIG                                                          Dem_Cfg_DtcGroupMask
#define DEM_CFG_EQ2_DTCTABLEOFPCCONFIG                                                              Dem_Cfg_DtcTable
#define DEM_CFG_EQ2_DTRDATAOFPCCONFIG                                                               (&(Dem_Cfg_DtrData))
#define DEM_CFG_EQ2_DTRSTATUSOFPCCONFIG                                                             Dem_Cfg_DtrStatus
#define DEM_CFG_EQ2_DTRTABLEINDOFPCCONFIG                                                           Dem_Cfg_DtrTableInd
#define DEM_CFG_EQ2_DTRTABLEOFPCCONFIG                                                              Dem_Cfg_DtrTable
#define DEM_CFG_EQ2_ENABLECONDITIONFULFILLEDOFPCCONFIG                                              Dem_Cfg_EnableConditionFulfilled
#define DEM_CFG_EQ2_ENABLECONDITIONGROUPCOUNTEROFPCCONFIG                                           Dem_Cfg_EnableConditionGroupCounter
#define DEM_CFG_EQ2_ENABLECONDITIONGROUPSTATEOFPCCONFIG                                             Dem_Cfg_EnableConditionGroupState
#define DEM_CFG_EQ2_ENABLECONDITIONGROUPTABLEINDOFPCCONFIG                                          Dem_Cfg_EnableConditionGroupTableInd
#define DEM_CFG_EQ2_ENABLECONDITIONGROUPTABLEOFPCCONFIG                                             Dem_Cfg_EnableConditionGroupTable
#define DEM_CFG_EQ2_ENABLECONDITIONINITTABLEOFPCCONFIG                                              Dem_Cfg_EnableConditionInitTable
#define DEM_CFG_EQ2_ENABLECONDITIONTABLEOFPCCONFIG                                                  Dem_Cfg_EnableConditionTable
#define DEM_CFG_EQ2_EVENTAVAILABLEDATAOFPCCONFIG                                                    (&(Dem_Cfg_EventAvailableData))
#define DEM_CFG_EQ2_EVENTAVAILABLEDEFAULTOFPCCONFIG                                                 Dem_Cfg_EventAvailableDefault
#define DEM_CFG_EQ2_EVENTAVAILABLEINVARIANTOFPCCONFIG                                               Dem_Cfg_EventAvailableInVariant
#define DEM_CFG_EQ2_EVENTCYCLESTATUSOFPCCONFIG                                                      Dem_Cfg_EventCycleStatus
#define DEM_CFG_EQ2_EVENTDATACHANGEDOFPCCONFIG                                                      Dem_Cfg_EventDataChanged
#define DEM_CFG_EQ2_EVENTDATACOMMITNUMBEROFPCCONFIG                                                 Dem_Cfg_EventDataCommitNumber
#define DEM_CFG_EQ2_EVENTDEBOUNCEVALUEOFPCCONFIG                                                    Dem_Cfg_EventDebounceValue
#define DEM_CFG_EQ2_EVENTINTERNALSTATUSOFPCCONFIG                                                   Dem_Cfg_EventInternalStatus
#define DEM_CFG_EQ2_EVENTSTATUSCHANGEDOFPCCONFIG                                                    Dem_Cfg_EventStatusChanged
#define DEM_CFG_EQ2_EVENTTABLEINDOFPCCONFIG                                                         Dem_Cfg_EventTableInd
#define DEM_CFG_EQ2_EVENTTABLEOFPCCONFIG                                                            Dem_Cfg_EventTable
#define DEM_CFG_EQ2_EVENTTABLE_EREC2EVENTIDINDOFPCCONFIG                                            Dem_Cfg_EventTable_ERec2EventIdInd
#define DEM_CFG_EQ2_EVENTTABLE_OBDRDYGROUP2EVENTIDINDOFPCCONFIG                                     Dem_Cfg_EventTable_ObdRdyGroup2EventIdInd
#define DEM_CFG_EQ2_EXTENDEDDATARECORDITERATORTABLEOFPCCONFIG                                       Dem_Cfg_ExtendedDataRecordIteratorTable
#define DEM_CFG_EQ2_EXTENDEDDATARECORDTABLEOFPCCONFIG                                               Dem_Cfg_ExtendedDataRecordTable
#define DEM_CFG_EQ2_EXTENDEDDATATABLEOFPCCONFIG                                                     Dem_Cfg_ExtendedDataTable
#define DEM_CFG_EQ2_FILTERINFOTABLEOFPCCONFIG                                                       Dem_Cfg_FilterInfoTable
#define DEM_CFG_EQ2_FILTERREPORTEDEVENTSOFPCCONFIG                                                  Dem_Cfg_FilterReportedEvents
#define DEM_CFG_EQ2_FREEZEFRAMEDATAOFPCCONFIG                                                       (&(Dem_Cfg_FreezeFrameData))
#define DEM_CFG_EQ2_FREEZEFRAMEITERATORTABLEOFPCCONFIG                                              Dem_Cfg_FreezeFrameIteratorTable
#define DEM_CFG_EQ2_FREEZEFRAMENUMTABLEOFPCCONFIG                                                   Dem_Cfg_FreezeFrameNumTable
#define DEM_CFG_EQ2_FREEZEFRAMETABLEOFPCCONFIG                                                      Dem_Cfg_FreezeFrameTable
#define DEM_CFG_EQ2_GENERALJ1939TABLEOFPCCONFIG                                                     Dem_Cfg_GeneralJ1939Table
#define DEM_CFG_EQ2_GENERALOBDINPUTOFPCCONFIG                                                       Dem_Cfg_GeneralObdInput
#define DEM_CFG_EQ2_GLOBALINDICATORSTATESOFPCCONFIG                                                 Dem_Cfg_GlobalIndicatorStates
#define DEM_CFG_EQ2_INDICATORBLINKINGOFPCCONFIG                                                     Dem_Cfg_IndicatorBlinking
#define DEM_CFG_EQ2_INDICATORCONTINUOUSOFPCCONFIG                                                   Dem_Cfg_IndicatorContinuous
#define DEM_CFG_EQ2_INDICATORFASTFLASHOFPCCONFIG                                                    Dem_Cfg_IndicatorFastFlash
#define DEM_CFG_EQ2_INDICATORSLOWFLASHOFPCCONFIG                                                    Dem_Cfg_IndicatorSlowFlash
#define DEM_CFG_EQ2_INITMONLISTFORFUNCOFPCCONFIG                                                    Dem_Cfg_InitMonListForFunc
#define DEM_CFG_EQ2_INITMONITORFOREVENTOFPCCONFIG                                                   Dem_Cfg_InitMonitorForEvent
#define DEM_CFG_EQ2_INITMONITORSFORFUNCOFPCCONFIG                                                   Dem_Cfg_InitMonitorsForFunc
#define DEM_CFG_EQ2_J1939NODEIDINDOFPCCONFIG                                                        Dem_Cfg_J1939NodeIdInd
#define DEM_CFG_EQ2_J1939NODEIDOFPCCONFIG                                                           Dem_Cfg_J1939NodeId
#define DEM_CFG_EQ2_J1939NODEINDICATOROFPCCONFIG                                                    Dem_Cfg_J1939NodeIndicator
#define DEM_CFG_EQ2_MEMORYBLOCKIDOFPCCONFIG                                                         Dem_Cfg_MemoryBlockId
#define DEM_CFG_EQ2_MEMORYBLOCKIDTOMEMORYENTRYIDOFPCCONFIG                                          Dem_Cfg_MemoryBlockIdToMemoryEntryId
#define DEM_CFG_EQ2_MEMORYDATAPTROFPCCONFIG                                                         Dem_Cfg_MemoryDataPtr
#define DEM_CFG_EQ2_MEMORYDATASIZEOFPCCONFIG                                                        Dem_Cfg_MemoryDataSize
#define DEM_CFG_EQ2_MEMORYENTRYINITOFPCCONFIG                                                       (&(Dem_Cfg_MemoryEntryInit))
#define DEM_CFG_EQ2_MEMORYENTRYOFPCCONFIG                                                           Dem_Cfg_MemoryEntry
#define DEM_CFG_EQ2_MEMORYSTATUSOFPCCONFIG                                                          Dem_Cfg_MemoryStatus
#define DEM_CFG_EQ2_MIDTABLEOFPCCONFIG                                                              Dem_Cfg_MidTable
#define DEM_CFG_EQ2_MIRRORDATAOFPCCONFIG                                                            (&(Dem_Cfg_MirrorData))
#define DEM_CFG_EQ2_NORMALINDICATORTABLEOFPCCONFIG                                                  Dem_Cfg_NormalIndicatorTable
#define DEM_CFG_EQ2_OBDIUMPRDATAOFPCCONFIG                                                          (&(Dem_Cfg_ObdIumprData))
#define DEM_CFG_EQ2_OBDIUMPRUPDATEPENDINGOFPCCONFIG                                                 Dem_Cfg_ObdIumprUpdatePending
#define DEM_CFG_EQ2_PERMANENTDATAOFPCCONFIG                                                         (&(Dem_Cfg_PermanentData))
#define DEM_CFG_EQ2_PIDTABLEOFPCCONFIG                                                              Dem_Cfg_PidTable
#define DEM_CFG_EQ2_PRESTORAGEINDEXOFPCCONFIG                                                       Dem_Cfg_PrestorageIndex
#define DEM_CFG_EQ2_PRESTORAGEOFPCCONFIG                                                            (&(Dem_Cfg_Prestorage))
#define DEM_CFG_EQ2_PRIMARYCHRONOLOGYOFPCCONFIG                                                     Dem_Cfg_PrimaryChronology
#define DEM_CFG_EQ2_PRIMARYENTRY_0OFPCCONFIG                                                        (&(Dem_Cfg_PrimaryEntry_0))
#define DEM_CFG_EQ2_PRIMARYENTRY_1OFPCCONFIG                                                        (&(Dem_Cfg_PrimaryEntry_1))
#define DEM_CFG_EQ2_PRIMARYENTRY_2OFPCCONFIG                                                        (&(Dem_Cfg_PrimaryEntry_2))
#define DEM_CFG_EQ2_PRIMARYENTRY_3OFPCCONFIG                                                        (&(Dem_Cfg_PrimaryEntry_3))
#define DEM_CFG_EQ2_PRIMARYENTRY_4OFPCCONFIG                                                        (&(Dem_Cfg_PrimaryEntry_4))
#define DEM_CFG_EQ2_PRIMARYENTRY_5OFPCCONFIG                                                        (&(Dem_Cfg_PrimaryEntry_5))
#define DEM_CFG_EQ2_PRIMARYENTRY_6OFPCCONFIG                                                        (&(Dem_Cfg_PrimaryEntry_6))
#define DEM_CFG_EQ2_PRIMARYENTRY_7OFPCCONFIG                                                        (&(Dem_Cfg_PrimaryEntry_7))
#define DEM_CFG_EQ2_RATIOIDTABLEOFPCCONFIG                                                          Dem_Cfg_RatioIdTable
#define DEM_CFG_EQ2_READINESSGROUPTABLEOFPCCONFIG                                                   Dem_Cfg_ReadinessGroupTable
#define DEM_CFG_EQ2_READOUTBUFFEROFPCCONFIG                                                         Dem_Cfg_ReadoutBuffer
#define DEM_CFG_EQ2_REPORTEDEVENTSOFFILTEROFPCCONFIG                                                Dem_Cfg_ReportedEventsOfFilter
#define DEM_CFG_EQ2_SATELLITEINFO0OFPCCONFIG                                                        (&(Dem_Cfg_SatelliteInfo0))
#define DEM_CFG_EQ2_SATELLITEINFOOFPCCONFIG                                                         Dem_Cfg_SatelliteInfo
#define DEM_CFG_EQ2_SATELLITETIMEDEBOUNCEINFOOFPCCONFIG                                             Dem_Cfg_SatelliteTimeDebounceInfo
#define DEM_CFG_EQ2_SECONDARYCHRONOLOGYOFPCCONFIG                                                   Dem_Cfg_SecondaryChronology
#define DEM_CFG_EQ2_SPECIALINDICATORTABLEOFPCCONFIG                                                 Dem_Cfg_SpecialIndicatorTable
#define DEM_CFG_EQ2_STARTIDX500MIDENRATIOTABLEOFPCCONFIG                                            Dem_Cfg_StartIdx500miDenRatioTable
#define DEM_CFG_EQ2_STATUSDATAOFPCCONFIG                                                            (&(Dem_Cfg_StatusData))
#define DEM_CFG_EQ2_STORAGECONDITIONFULFILLEDOFPCCONFIG                                             Dem_Cfg_StorageConditionFulfilled
#define DEM_CFG_EQ2_STORAGECONDITIONGROUPCOUNTEROFPCCONFIG                                          Dem_Cfg_StorageConditionGroupCounter
#define DEM_CFG_EQ2_STORAGECONDITIONGROUPTABLEINDOFPCCONFIG                                         Dem_Cfg_StorageConditionGroupTableInd
#define DEM_CFG_EQ2_STORAGECONDITIONGROUPTABLEOFPCCONFIG                                            Dem_Cfg_StorageConditionGroupTable
#define DEM_CFG_EQ2_STORAGECONDITIONINITTABLEOFPCCONFIG                                             Dem_Cfg_StorageConditionInitTable
#define DEM_CFG_EQ2_STORAGECONDITIONTABLEOFPCCONFIG                                                 Dem_Cfg_StorageConditionTable
#define DEM_CFG_EQ2_SUPPORTEDMIDSTABLEOFPCCONFIG                                                    Dem_Cfg_SupportedMidsTable
#define DEM_CFG_EQ2_TIMESERIESCHRONOLOGYOFPCCONFIG                                                  Dem_Cfg_TimeSeriesChronology
#define DEM_CFG_EQ2_TIMESERIESENTRYINITOFPCCONFIG                                                   (&(Dem_Cfg_TimeSeriesEntryInit))
/** 
  \}
*/ 

/** 
  \defgroup  Dem_CfgPCSymbolicNonDereferenciateablePointers  Dem_Cfg Symbolic Non Dereferenciateable Pointers (PRE_COMPILE)
  \brief  Symbolic non dereferenciateable pointers to be used if all values are optimized to a defined and to return a correct value for has macros in variants.
  \{
*/ 
#define Dem_Cfg_AgingData                                                                           ((Dem_Cfg_AgingDataPtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_CallbackDtcStatusChanged                                                            ((Dem_Cfg_CallbackDtcStatusChangedPtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_CallbackGetFdc                                                                      ((Dem_Cfg_CallbackGetFdcPtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_CallbackJ1939DtcStatusChanged                                                       ((Dem_Cfg_CallbackJ1939DtcStatusChangedPtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_ClearDtcNotificationFinishTable                                                     ((Dem_Cfg_ClearDtcNotificationFinishTablePtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_ClearDtcNotificationStartTable                                                      ((Dem_Cfg_ClearDtcNotificationStartTablePtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_CycleCounterData                                                                    ((Dem_Cfg_CycleCounterDataPtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_DataCollectionTableJ19392CollInd                                                    ((Dem_Cfg_DataCollectionTableJ19392CollIndPtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_DataCollectionTablePid2CollInd                                                      ((Dem_Cfg_DataCollectionTablePid2CollIndPtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_DebounceData                                                                        ((Dem_Cfg_DebounceDataPtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_DebounceHiResTable                                                                  ((Dem_Cfg_DebounceHiResTablePtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_DebounceLoResTable                                                                  ((Dem_Cfg_DebounceLoResTablePtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_DtcGroupMask                                                                        ((Dem_Cfg_DtcGroupMaskPtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_DtrData                                                                             ((Dem_Cfg_DtrDataPtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_DtrStatus                                                                           ((Dem_Cfg_DtrStatusPtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_DtrTable                                                                            ((Dem_Cfg_DtrTablePtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_DtrTableInd                                                                         ((Dem_Cfg_DtrTableIndPtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_EventAvailableData                                                                  ((Dem_Cfg_EventAvailableDataPtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_EventCycleStatus                                                                    ((Dem_Cfg_EventCycleStatusPtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_EventDataChanged                                                                    ((Dem_Cfg_EventDataChangedPtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_EventStatusChanged                                                                  ((Dem_Cfg_EventStatusChangedPtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_EventTable_ERec2EventIdInd                                                          ((Dem_Cfg_EventTable_ERec2EventIdIndPtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_EventTable_ObdRdyGroup2EventIdInd                                                   ((Dem_Cfg_EventTable_ObdRdyGroup2EventIdIndPtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_FreezeFrameData                                                                     ((Dem_Cfg_FreezeFrameDataPtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_GeneralJ1939Table                                                                   ((Dem_Cfg_GeneralJ1939TablePtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_GlobalIndicatorStates                                                               ((Dem_Cfg_GlobalIndicatorStatesPtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_IndicatorBlinking                                                                   ((Dem_Cfg_IndicatorBlinkingPtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_IndicatorContinuous                                                                 ((Dem_Cfg_IndicatorContinuousPtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_IndicatorFastFlash                                                                  ((Dem_Cfg_IndicatorFastFlashPtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_IndicatorSlowFlash                                                                  ((Dem_Cfg_IndicatorSlowFlashPtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_InitMonListForFunc                                                                  ((Dem_Cfg_InitMonListForFuncPtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_InitMonitorForEvent                                                                 ((Dem_Cfg_InitMonitorForEventPtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_InitMonitorsForFunc                                                                 ((Dem_Cfg_InitMonitorsForFuncPtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_J1939NodeId                                                                         ((Dem_Cfg_J1939NodeIdPtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_J1939NodeIdInd                                                                      ((Dem_Cfg_J1939NodeIdIndPtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_J1939NodeIndicator                                                                  ((Dem_Cfg_J1939NodeIndicatorPtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_MidTable                                                                            ((Dem_Cfg_MidTablePtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_MirrorData                                                                          ((Dem_Cfg_MirrorDataPtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_NormalIndicatorTable                                                                ((Dem_Cfg_NormalIndicatorTablePtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_ObdIumprData                                                                        ((Dem_Cfg_ObdIumprDataPtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_ObdIumprUpdatePending                                                               ((Dem_Cfg_ObdIumprUpdatePendingPtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_PermanentData                                                                       ((Dem_Cfg_PermanentDataPtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_PidTable                                                                            ((Dem_Cfg_PidTablePtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_Prestorage                                                                          ((Dem_Cfg_PrestoragePtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_PrestorageIndex                                                                     ((Dem_Cfg_PrestorageIndexPtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_RatioIdTable                                                                        ((Dem_Cfg_RatioIdTablePtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_SatelliteTimeDebounceInfo                                                           ((Dem_Cfg_SatelliteTimeDebounceInfoPtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_SecondaryChronology                                                                 ((Dem_Cfg_SecondaryChronologyPtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_SpecialIndicatorTable                                                               ((Dem_Cfg_SpecialIndicatorTablePtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_StartIdx500miDenRatioTable                                                          ((Dem_Cfg_StartIdx500miDenRatioTablePtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_StorageConditionFulfilled                                                           ((Dem_Cfg_StorageConditionFulfilledPtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_StorageConditionGroupCounter                                                        ((Dem_Cfg_StorageConditionGroupCounterPtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_StorageConditionGroupTable                                                          ((Dem_Cfg_StorageConditionGroupTablePtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_StorageConditionGroupTableInd                                                       ((Dem_Cfg_StorageConditionGroupTableIndPtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_StorageConditionInitTable                                                           ((Dem_Cfg_StorageConditionInitTablePtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_StorageConditionTable                                                               ((Dem_Cfg_StorageConditionTablePtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_SupportedMidsTable                                                                  ((Dem_Cfg_SupportedMidsTablePtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
#define Dem_Cfg_TimeSeriesChronology                                                                ((Dem_Cfg_TimeSeriesChronologyPtrType)(NULL_PTR))  /**< Non derefenciateable valid pointer */
/** 
  \}
*/ 

/** 
  \defgroup  Dem_CfgPCSymbolicInitializationPointers  Dem_Cfg Symbolic Initialization Pointers (PRE_COMPILE)
  \brief  Symbolic initialization pointers to be used in the call of a preinit or init function.
  \{
*/ 
#define Dem_Config_Ptr                                                                              NULL_PTR  /**< symbolic identifier which shall be used to initialize 'Dem' */
/** 
  \}
*/ 

/** 
  \defgroup  Dem_CfgPCInitializationSymbols  Dem_Cfg Initialization Symbols (PRE_COMPILE)
  \brief  Symbolic initialization pointers which may be used in the call of a preinit or init function. Please note, that the defined value can be a 'NULL_PTR' and the address operator is not usable.
  \{
*/ 
#define Dem_Config                                                                                  NULL_PTR  /**< symbolic identifier which could be used to initialize 'Dem */
/** 
  \}
*/ 

/** 
  \defgroup  Dem_CfgPCGeneral  Dem_Cfg General (PRE_COMPILE)
  \brief  General constant defines not associated with a group of defines.
  \{
*/ 
#define DEM_CFG_CHECK_INIT_POINTER                                                                  STD_OFF  /**< STD_ON if the init pointer shall not be used as NULL_PTR and a check shall validate this. */
#define DEM_CFG_FINAL_MAGIC_NUMBER                                                                  0x361Eu  /**< the precompile constant to validate the size of the initialization structure at initialization time of Dem */
#define DEM_CFG_INDIVIDUAL_POSTBUILD                                                                STD_OFF  /**< the precompile constant to check, that the module is individual postbuildable. The module 'Dem' is not configured to be postbuild capable. */
#define DEM_CFG_INIT_DATA                                                                           DEM_CONST  /**< CompilerMemClassDefine for the initialization data. */
#define DEM_CFG_INIT_DATA_HASH_CODE                                                                 -504453132  /**< the precompile constant to validate the initialization structure at initialization time of Dem with a hashcode. The seed value is '0x361Eu' */
#define DEM_CFG_USE_ECUM_BSW_ERROR_HOOK                                                             STD_OFF  /**< STD_ON if the EcuM_BswErrorHook shall be called in the ConfigPtr check. */
#define DEM_CFG_USE_INIT_POINTER                                                                    STD_OFF  /**< STD_ON if the init pointer Dem shall be used. */
/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/** 
  \defgroup  Dem_CfgLTDataSwitches  Dem_Cfg Data Switches  (LINK)
  \brief  These defines are used to deactivate data and their processing.
  \{
*/ 
#define DEM_LTCONFIG                                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is COMPILETIME_CHECKING. */
/** 
  \}
*/ 


/*********************************************************************************************************************/


 /*  Invalid Indicator IDs  */ 
#define DEM_CFG_INDICATOR_INVALID                                     0u           /* Lowest, unused IndicatorID */ 
#define DEM_CFG_SPECIAL_INDICATOR_NONE                                255u         /* Always different from DEM_CFG_INDICATOR_INVALID */ 

 /*  Indicator global definitions  */ 
#define DEM_CFG_GLOBAL_INDICATOR_COUNT                                0u           /* Total number of configured Indicators */ 
#define DEM_G_NUMBER_SPECIAL_INDICATORS                               0u           /* Number of special indicators (i.e. only MIL, AWL, PL, RSL) */ 


 /*  Aging- and OperationCycle IDs [symbolic name value]  */ 
#define DemConf_DemOperationCycle_DemOperationCycle                   0u 
#define DemConf_DemOperationCycle_PowerCycle                          1u 
#define DemConf_DemOperationCycle_WarmUpCycle                         2u 

 /*  Global, cycle related values  */ 
#define DEM_CFG_GLOBAL_CYCLE_COUNT                                    3u                                                                /* Total number of configured (operation and aging) cycles. */ 
#define DEM_CFG_GLOBAL_OBD_DRIVING_CYCLE_ID                           /* No DemOperationCycleType 'DEM_OPCYC_OBD_DCY' configured. */    /* Cycle ID of the DemOperationCycleType 'DEM_OPCYC_OBD_DCY'. */ 
#define DEM_CFG_GLOBAL_WARMUP_CYCLE_ID                                2u                                                                /* Cycle ID of the DemOperationCycleType 'DEM_OPCYC_WARMUP'. */ 


 /*  Dem general defines  */ 
#define DEM_CFG_BSW_ERROR_BUFFER_SIZE                                 0u                                                                   /* /Dem/DemGeneral/DemBswErrorBufferSize */ 
#define DEM_CFG_GLOBALCBKCONTROLDTCSETTING_FUNC                       NULL_PTR                                                             /* DEM_CFG_NOTIFY_CONTROL_DTC_SETTING==STD_OFF */ 
#define DEM_CFG_GLOBALCBKDATA_FUNC                                    NULL_PTR                                                             /* No ClientServerInterface GeneralCallbackEventDataChanged, DEM_CFG_NOTIFY_GENERAL_DATA==STD_OFF */ 
#define DEM_CFG_GLOBALCBKSTATUS_FUNC                                  &Appl_Dem_GeneralCBStatusEvt_GeneralCallbackEventUdsStatusChanged    /* DEM_CFG_NOTIFY_GENERAL_STATUS==STD_ON, signature: void Appl_Dem_GeneralCBStatusEvt_GeneralCallbackEventUdsStatusChanged(Dem_EventIdType eventId, Dem_UdsStatusByteType eventStatusOld, Dem_UdsStatusByteType eventStatusNew) */ 
#define DEM_CFG_GLOBALTRIGGERONMONITORSTATUS_FUNC                     NULL_PTR                                                             /* No or empty /Dem/DemGeneral/DemGeneralCallbackMonitorStatusChangedFnc parameter, DEM_CFG_NOTIFY_GENERAL_MONITORSTATUS_CHANGED==STD_OFF */ 
#define DEM_CFG_GLOBAL_CLEAR_DTC_RUNTIME_LIMIT                        16u                                                                  /* not configured, here substituted by number of events (incl. event #0) */ 
#define DEM_CFG_GLOBAL_DEBOUNCE_STORAGE_EVENT_COUNT                   0u                                                                   /* Number of events with .../DemEventClass/DemDebounceAlgorithClass/DemDebounceCounterBased/DemDebounceCounterStorage == TRUE */ 
#define DEM_CFG_GLOBAL_DTC_FORMAT                                     DEM_DTC_TRANSLATION_ISO14229_1                                       /* /Dem/DemGeneral/DemTypeOfDTCSupported */ 
#define DEM_CFG_GLOBAL_FREEZEFRAME_SIZE                               0u                                                                   /* /Dem/DemGeneral/DemMaxNumberEventEntryOBDFreezeFrame */ 
#define DEM_CFG_GLOBAL_J1939_READING_DTC_RUNTIME_LIMIT                16u                                                                  /* /Dem/DemGeneral/DemGeneralJ1939/DemJ1939ReadingDTCRuntimeLimit not configured, substituted by number of events (incl. event #0) */ 
#define DEM_CFG_GLOBAL_MIRROR_SIZE                                    0u                                                                   /* /Dem/DemGeneral/DemMaxNumberEventEntryMirror */ 
#define DEM_CFG_GLOBAL_NV_STORAGE_LIMIT                               0u                                                                   /* /Dem/DemGeneral/DemImmediateNvStorageLimit, 0: no limit configured */ 
#define DEM_CFG_GLOBAL_PERMANENT_SIZE                                 0u                                                                   /* /Dem/DemGeneral/DemMaxNumberEventEntryPermanent */ 
#define DEM_CFG_GLOBAL_PRESTORED_FF_SIZE                              0u                                                                   /* /Dem/DemGeneral/DemMaxNumberPrestoredFF, see Dem_Cfg_GlobalPrestorageSize() */ 
#define DEM_CFG_GLOBAL_PRIMARY_SIZE                                   8u                                                                   /* /Dem/DemGeneral/DemMaxNumberEventEntryPrimary */ 
#define DEM_CFG_GLOBAL_RESTART_CYCLE_ID                               1u                                                                   /* using DemOperationCycle: 'PowerCycle' */ 
#define DEM_CFG_GLOBAL_SECONDARY_SIZE                                 0u                                                                   /* /Dem/DemGeneral/DemMaxNumberEventEntrySecondary */ 
#define DEM_CFG_GLOBAL_STATUS_MASK                                    0xFFu                                                                /* /Dem/DemGeneral/DemDtcStatusAvailabilityMask */ 
#define DEM_CFG_GLOBAL_TASK_MS                                        12u                                                                  /* /Dem/DemGeneral/DemTaskTime in [ms]. See also macro DEM_CFG_TASK_TIME for exact float value */ 
#define DEM_CFG_GLOBAL_TIMESERIES_SNAPSHOTS_SIZE                      0u                                                                   /* /Dem/DemGeneral/DemMaxNumberTimeSeriesSnapshots */ 
#define DEM_CFG_J1939_NODE_INVALID                                    0u                                                                   /* Invalid NmNode index (Dem internal) */ 
#define DEM_CFG_MAX_NUMBER_PERMANENT_CHRONOLOGY                       1u                                                                   /* /Dem/DemGeneral/DemGeneralOBD/DemOBDPermanentChronologyMaxNumberEvents */ 
#define DEM_CFG_OEMCBKGETCURRENTODOMETER_FUNC                         NULL_PTR                                                             /* unused */ 
#define DEM_CFG_OEMCBKGETEXTERNALTESTERSTATUS_FUNC                    NULL_PTR                                                             /* unused */ 
#define DEM_CFG_RATIOINDEX_INVALID                                    255u                                                                 /* Internal use: no OBD RatioId configured */ 
#define DEM_CFG_SIZEOF_MAX_DATA_VALUE_TYPE                            10u                                                                  /* sizeof(Dem_MaxDataValueType) - typedef is generated by the RTE into Rte_Type.h */ 
#define DEM_CFG_TASK_TIME                                             12.5                                                                 /* /Dem/DemGeneral/DemTaskTime in [ms]. See also macro DEM_CFG_GLOBAL_TASK_MS for integer value. */ 
#define DEM_G_GLOBAL_PRESTORED_EVENT_COUNT                            0u                                                                   /* Number of events with DemEventClass/DemFFPrestorageSupported == TRUE, see Dem_Cfg_GlobalPrestorageEventCount() */ 
#define DEM_G_MAX_NUMBER_J1939_NODES                                  1u                                                                   /* Number of different J1939Nm node targets (=J1939NmNode) referenced via /Dem/DemConfigSet/DemJ1939NodeAddress/DemJ1939NmNodeRef - plus 1 when there are DTCs without a DemJ1939DTC_NodeAddressRef value. */ 
#define DEM_G_NUMBER_OF_EVENTS                                        16u                                                                  /* Total number of DemEventParameter, incl. event #0 */ 
#define DEM_G_NUMBER_OF_RATIO_IDS                                     0u                                                                   /* Number of OBD RatioIds (incl. ID 0, internally used for global values) */ 


 /*  Support for optimized routines of Vector DCM - FreezeFrame records. Deprecated macros for DCMs older R25S4 still generated for backward compatibility.  */ 
#define DEM_DCM_NUM_FRZFRAME_RECID                                    1u 
#define DEM_DCM_LST_FRZFRAME_RECID                                    0x01u 

 /*  Support for optimized routines of Vector DCM - Extended Data records  */ 
#define DEM_DCM_NUM_EXTDATA_RECID                                     2u 
#define DEM_DCM_LST_EXTDATA_RECID                                     0x01u, 0x02u 

 /*  Event IDs [symbolic name value] - sorted by name.
     See Dem_Cfg_EventTable[] for this list sorted by Ids.  */ 
#define DemConf_DemEventParameter_DTC_0x010000                        1u 
#define DemConf_DemEventParameter_DTC_0x010001                        2u 
#define DemConf_DemEventParameter_DTC_0x010002                        5u 
#define DemConf_DemEventParameter_DTC_0x010003                        3u 
#define DemConf_DemEventParameter_DTC_0x010004                        4u 
#define DemConf_DemEventParameter_DTC_0x010005                        6u 
#define DemConf_DemEventParameter_DTC_0x010007                        13u 
#define DemConf_DemEventParameter_DTC_0x010008                        14u 
#define DemConf_DemEventParameter_DTC_0x010009                        15u 
#define DemConf_DemEventParameter_DTC_0x010010                        7u 
#define DemConf_DemEventParameter_DTC_0x010011                        8u 
#define DemConf_DemEventParameter_DTC_0x010012                        9u 
#define DemConf_DemEventParameter_DTC_0x010013                        10u 
#define DemConf_DemEventParameter_DTC_0x010014                        11u 
#define DemConf_DemEventParameter_DTC_0x010020                        12u 




 /*  Existance of iterator interfaces  */ 
#define DEM_CFG_HAVEITER_CLEARDTCNOTIFICATIONFINISH                   STD_OFF      /* Deactivated due DEM_CFG_CLEARDTCNOTIFICATIONFINISHTABLE==STD_OFF */ 
#define DEM_CFG_HAVEITER_CLEARDTCNOTIFICATIONSTART                    STD_OFF      /* Deactivated due DEM_CFG_CLEARDTCNOTIFICATIONSTARTTABLE==STD_OFF */ 
#define DEM_CFG_HAVEITER_COMBINEDGROUP                                STD_OFF      /* Deactivated due DEM_CFG_SUPPORT_TYPE1_COMBINATION==STD_OFF */ 
#define DEM_CFG_HAVEITER_DEBOUNCEHIRES                                STD_OFF      /* Deactivated due DEM_CFG_SUPPORT_DEBOUNCE_TIME_HR==STD_OFF */ 
#define DEM_CFG_HAVEITER_DEBOUNCELORES                                STD_OFF      /* Deactivated due DEM_CFG_SUPPORT_DEBOUNCE_TIME_LR==STD_OFF */ 
#define DEM_CFG_HAVEITER_DIDDATA                                      STD_ON 
#define DEM_CFG_HAVEITER_ENABLECONDITIONGROUPS                        STD_ON 
#define DEM_CFG_HAVEITER_EREC                                         STD_ON 
#define DEM_CFG_HAVEITER_EVENTDID                                     STD_ON 
#define DEM_CFG_HAVEITER_EVENTEREC                                    STD_ON 
#define DEM_CFG_HAVEITER_EVENTIDLIST                                  STD_ON 
#define DEM_CFG_HAVEITER_EVENTJ1939NODE                               STD_OFF      /* Deactivated due (DEM_CFG_HAS_J1939_NODE == STD_OFF) */ 
#define DEM_CFG_HAVEITER_EVENTOBDDID                                  STD_OFF      /* Deactivated due DEM_CFG_SUPPORT_WWHOBD==STD_OFF */ 
#define DEM_CFG_HAVEITER_EVENTSPN                                     STD_OFF      /* Deactivated due DEM_CFG_SUPPORT_J1939==STD_OFF */ 
#define DEM_CFG_HAVEITER_EVENTSREC                                    STD_ON 
#define DEM_CFG_HAVEITER_GLOBALCBKDTC                                 STD_OFF      /* Deactivated due DEM_CFG_CALLBACKDTCSTATUSCHANGED==STD_OFF */ 
#define DEM_CFG_HAVEITER_GLOBALCBKJ1939DTC                            STD_OFF      /* Deactivated due DEM_CFG_CALLBACKJ1939DTCSTATUSCHANGED==STD_OFF */ 
#define DEM_CFG_HAVEITER_GLOBALPID                                    STD_ON 
#define DEM_CFG_HAVEITER_OBDFIMFID                                    STD_OFF      /* Deactivated due DEM_CFG_SUPPORT_IUMPR==STD_OFF */ 
#define DEM_CFG_HAVEITER_OBDRATIOID                                   STD_OFF      /* Deactivated due DEM_CFG_SUPPORT_IUMPR==STD_OFF */ 
#define DEM_CFG_HAVEITER_RDYGROUP                                     STD_ON 
#define DEM_CFG_HAVEITER_STORAGECONDITIONGROUPS                       STD_OFF      /* Deactivated due (DEM_CFG_HAS_STORAGE_CONDITIONS == STD_OFF) */ 
#define DEM_CFG_HAVEITER_TIMESERIESDIDFAST                            STD_OFF      /* Deactivated due (DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_NORMAL || DEM_CFG_SUPPORT_TIME_SERIES_PAST_NORMAL || DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_FAST || DEM_CFG_SUPPORT_TIME_SERIES_PAST_FAST) == STD_OFF */ 
#define DEM_CFG_HAVEITER_TIMESERIESDIDNORMAL                          STD_OFF      /* Deactivated due (DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_NORMAL || DEM_CFG_SUPPORT_TIME_SERIES_PAST_NORMAL || DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_FAST || DEM_CFG_SUPPORT_TIME_SERIES_PAST_FAST) == STD_OFF */ 

 /*  Event global definitions  */ 
#define DEM_CFG_FAILEDCYCLECOUNTER_INDEX_INVALID                      255u 
#define DEM_CFG_FAULTPENDINGCOUNTER_INDEX_INVALID                     255u 
#define DEM_CFG_GLOBAL_DTC_COUNT                                      16u 
#define DEM_CFG_GLOBAL_MIRROR_FIRST                                   0u           /* Lowest EventID with DemEventDestination==DEM_DTC_ORIGIN_MIRROR_MEMORY, or 0 if no such destination is configured. */ 
#define DEM_CFG_GLOBAL_MIRROR_LAST                                    0u           /* Highest EventID with DemEventDestination==DEM_DTC_ORIGIN_MIRROR_MEMORY, or 0 if no such destination is configured. */ 
#define DEM_CFG_GLOBAL_PERMANENT_FIRST                                0u           /* Lowest EventID with EventDestination==DEM_CFG_MEMORYID_PERMANENT, or 0 if no such destination is configured. */ 
#define DEM_CFG_GLOBAL_PERMANENT_LAST                                 0u           /* Highest EventID with EventDestination==DEM_CFG_MEMORYID_PERMANENT, or 0 if no such destination is configured. */ 
#define DEM_CFG_GLOBAL_PRIMARY_FIRST                                  1u           /* Lowest EventID with DemEventDestination==DEM_DTC_ORIGIN_PRIMARY_MEMORY, or 0 if no such destination is configured. */ 
#define DEM_CFG_GLOBAL_PRIMARY_LAST                                   15u          /* Highest EventID with DemEventDestination==DEM_DTC_ORIGIN_PRIMARY_MEMORY, or 0 if no such destination is configured. */ 
#define DEM_CFG_GLOBAL_SECONDARY_FIRST                                0u           /* Lowest EventID with DemEventDestination==DEM_DTC_ORIGIN_SECONDARY_MEMORY, or 0 if no such destination is configured. */ 
#define DEM_CFG_GLOBAL_SECONDARY_LAST                                 0u           /* Highest EventID with DemEventDestination==DEM_DTC_ORIGIN_SECONDARY_MEMORY, or 0 if no such destination is configured. */ 


 /*  Timebased debouncing - timing constants  */ 
#define DEM_CFG_DEBOUNCE_LO_RES_TIMER_VALUE                           12u          /* Ticks of the low resolution timer, based on Dem_MasterMainFunction() call cycle [12.5ms]. Tick count here equals 150.0ms. */ 


 /*  StorageCondition global definitions  */ 
#define DEM_CFG_GLOBAL_STORAGE_COND_COUNT                             0u           /* (DEM_CFG_HAS_STORAGE_CONDITIONS == STD_OFF) */ 

 /*  Satellite global definitions  */ 
#define DEM_CFG_GLOBAL_PARTITION_COUNT                                1u           /* Total number of different, referenced /Os/OsApplication containers (plus Application "0"). */ 
#define DEM_CFG_MASTER_APPLICATION_ID                                 0            /* no /Dem/DemGeneral/DemMasterOsApplicationRef configured */ 
#define DEM_SATELLITEINFO_0                                           0x00u        /* Index of partition "0" in SatelliteInfo[] table */ 


 /*  PID global definitions  */ 
#define DEM_CFG_GLOBAL_OBD_IIFFRAW_SIZE                               0u           /* Pure data size of OBD-II record. */ 
#define DEM_CFG_GLOBAL_OBD_IIFFUDS_SIZE                               2u           /* Data size of OBD-II record incl PID numbers (each 2B) plus RecordNumber (1B) plus RecordCount (1B). */ 

 /*  Defines for supporting A2L  */ 
#define DEM_A2L_MAX_NUMBER_PRIMEM_SNAPSHOTS                           1uL 
#define DEM_A2L_MAX_SIZE_PRIMEM_SNAPSHOTS                             0uL 
#define DEM_A2L_NUMBER_OF_EVENTS                                      16uL         /* incl. event #0 */ 
#define DEM_A2L_NUMBER_OF_MIL_GROUPS                                  0uL          /* number of DemMILGroup containers + 1 */ 
#define DEM_A2L_MAX_SIZE_STDENV_RECORD                                0uL          /* largest, configured StdEnvData */ 

 /*  NvRamBlock size configured in the NvM module  */ 
#define DEM_CFG_ADMIN_DATABLOCK_SIZE                                  12u          /* Size of the NvM block (NvM/NvMBlockDescriptor/NvMNvBlockLength) that's referenced via DemNvRamBlockId/DemNvRamBlockIdRef and has DemNvRamBlockId/DemNvRamBlockIdType=DEM_NVBLOCK_ADMIN */ 
#define DEM_CFG_STATUS_DATABLOCK_SIZE                                 38u          /* Size of the NvM block (NvM/NvMBlockDescriptor/NvMNvBlockLength) that's referenced via DemNvRamBlockId/DemNvRamBlockIdRef and has DemNvRamBlockId/DemNvRamBlockIdType=DEM_NVBLOCK_STATUS */ 
#define DEM_CFG_PRIMARY_DATABLOCK_SIZE                                50u          /* Size of the NvM block (NvM/NvMBlockDescriptor/NvMNvBlockLength) that's referenced via DemNvRamBlockId/DemNvRamBlockIdRef and has DemNvRamBlockId/DemNvRamBlockIdType=DEM_NVBLOCK_PRIMARY */ 




 /*  NV block global definitions  */ 
#define DEM_CFG_EVENTAVAILABLEDATATYPE_SIZE                           2u           /* Number of elements in arraytype 'Dem_Cfg_EventAvailableDataType'. */ 
#define DEM_CFG_GLOBAL_NV_BLOCK_COUNT                                 10u          /* Number of NV blocks. */ 
#define DEM_CFG_GLOBAL_PROCESSORWORDS_PER_REPORTEDEVENTSTYPE          1u           /* Number of Dem_Com_ProcessorWordType elements in arraytype 'Dem_Cfg_ReportedEventsType'. */ 
#define DEM_CFG_MAX_J1939_EXP_FF_SIZE                                 0u           /* Data size of the largest configured J1939 FreezeFrame record. */ 
#define DEM_CFG_MAX_J1939_FF_SIZE                                     0u           /* Data size of the largest configured J1939 FreezeFrame record. */ 
#define DEM_CFG_MAX_NUMBER_AGED_DTCS                                  0u           /* Maximum number of aged DTCs (number of DTCs assigned to an ageable event). */ 
#define DEM_CFG_MAX_NUMBER_AGING_DTCS                                 0u           /* Maximum number of aging DTCs (number of DTCs assigned to an event). */ 
#define DEM_CFG_MAX_NUMBER_CONFIGURABLE_DTRS                          0u           /* Maximum number of configurable Dtrs (defined by the largest DemDtrId value, or with PostBuild-Loadable the value /Dem/DemGeneral/DemPostbuild/DemMaxNumberDtr). */ 
#define DEM_CFG_MAX_NUMBER_FAILED_CYCLE_DTCS                          0u           /* Size of Dem_Cfg_CycleCounterDataType.FailedCycleCounter. */ 
#define DEM_CFG_MAX_NUMBER_FAULT_PENDING_DTCS                         0u           /* Size of Dem_Cfg_CycleCounterDataType.FaultPendingCounter. */ 
#define DEM_CFG_MAX_NUM_EXT_RECORDS                                   1u           /* Largest count of EDR records per event to be stored in ExtendedData[DEM_CFG_MAX_NUM_EXT_RECORDS][DEM_CFG_MAX_SIZE_EXT_RECORD] - ignore records with pure ROM data and/or data having own_variable. '1' if there are 0 records. */ 
#define DEM_CFG_MAX_NUM_SNAPSHOTS                                     1u           /* Largest count of FreezeFrame records per event to be stored in SnapshotData[DEM_CFG_MAX_NUM_SNAPSHOTS][DEM_CFG_MAX_SIZE_SNAPSHOT]. '1' if there are 0 records. */ 
#define DEM_CFG_MAX_SIZE_EXT_RECORD                                   1u           /* Data size of the largest EDR record to be stored in ExtendedData[DEM_CFG_MAX_NUM_EXT_RECORDS][DEM_CFG_MAX_SIZE_EXT_RECORD] or '1' if size is 0. */ 
#define DEM_CFG_MAX_SIZE_GLOBAL_SNAPSHOT                              1u           /* Data size of the global freeze frame record to be stored in GlobalSnapshotData[DEM_CFG_MAX_SIZE_GLOBAL_SNAPSHOT] or '1' if size is 0 or there is no global freeze frame. */ 
#define DEM_CFG_MAX_SIZE_OBDFREEZEFRAME                               1u           /* Data size of largest configured FreezeFrame 0 (OBD II) record. */ 
#define DEM_CFG_MAX_SIZE_SNAPSHOT                                     1u           /* Data size of the largest FreezeFrame record to be stored in SnapshotData[DEM_CFG_MAX_NUM_SNAPSHOTS][DEM_CFG_MAX_SIZE_SNAPSHOT] or '1' if size is 0 or there are 0 records. */ 
#define DEM_CFG_MAX_SIZE_TIMESERIESSNAPSHOT                           1u           /* Data size of the largest Time Series snapshot record or '1' if size is 0 or there are 0 records. Time series snapshot is stored in time series entry, e.g. in SnapshotData_NormalRate[DEM_CFG_TIMESERIES_NORMAL_SAMPLES][DEM_CFG_MAX_SIZE_TIMESERIESSNAPSHOT]; */ 
#define DEM_CFG_MAX_SIZE_WWHFREEZEFRAME                               1u           /* Data size of the largest WWH-OBD FreezeFrame record to be stored in ObdFreezeFrameData[DEM_CFG_MAX_SIZE_WWHFREEZEFRAME] or '1' if size is 0 or there are 0 records. */ 
#define DEM_CFG_MEMORYENTRY_HANDLE_INVALID                            9u           /* Value for an invalid memory entry handle */ 
#define DEM_CFG_MEMORYINDEX_MAX                                       255u         /* Maximum value of Dem_Cfg_MemoryIndexType */ 
#define DEM_CFG_MEMORY_ADMIN_INDEX                                    0u           /* Index into Dem_Cfg_MemoryBlockId[], Dem_Cfg_MemoryDataSize[], Dem_Cfg_MemoryDataPtr[] and other Memory*[] arrays. */ 
#define DEM_CFG_MEMORY_PRIMARY_INDEX                                  2u           /* Index into Dem_Cfg_MemoryBlockId[], Dem_Cfg_MemoryDataSize[], Dem_Cfg_MemoryDataPtr[] and other Memory*[] arrays. Buffer count: Dem_Cfg_GlobalPrimarySize() = 8 */ 
#define DEM_CFG_MEMORY_STATUS_INDEX                                   1u           /* Index into Dem_Cfg_MemoryBlockId[], Dem_Cfg_MemoryDataSize[], Dem_Cfg_MemoryDataPtr[] and other Memory*[] arrays. */ 
#define DEM_CFG_NUMBER_OF_SUBEVENT_DATA_READOUTBUFFERS                1u           /* Maximum number of required readout buffer for subevent data. If DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON: Min(#MaxSubEventsInOneGroup,#MaxEntryInPrimary/Secondary), else: 1 */ 
#define DEM_CFG_PROCESSEDCOMBINEDDTCGROUP_SIZE                        1u           /* Number of elements in arraytype 'Dem_Cfg_ProcessedCombinedDTCGroupType'. */ 



 /*  OBD global definitions  */ 
#define DEM_CFG_OBDACCELERATORPEDALINFORMATION_INDEX                  0u           /* not defined */ 
#define DEM_CFG_OBDAMBIENTPRESSURE_INDEX                              0u           /* not defined */ 
#define DEM_CFG_OBDAMBIENTTEMPERATURE_INDEX                           0u           /* not defined */ 
#define DEM_CFG_OBDDISTANCEINFORMATION_INDEX                          0u           /* not defined */ 
#define DEM_CFG_OBDENGINERUNTIME_INDEX                                0u           /* not defined */ 
#define DEM_CFG_OBDENGINESPEED_INDEX                                  0u           /* not defined */ 
#define DEM_CFG_OBDENGINETEMPERATURE_INDEX                            0u           /* not defined */ 
#define DEM_CFG_OBDPROGRAMMINGEVENT_INDEX                             0u           /* not defined */ 
#define DEM_CFG_OBDVEHICLESPEED_INDEX                                 0u           /* not defined */ 

 /*  EnableCondition IDs [symbolic name value]  */ 
#define DemConf_DemEnableCondition___Internal_ControlDtcSetting               0u 
#define DemConf_DemEnableCondition_DemEnableCondition_BatVoltageRange         1u 
#define DemConf_DemEnableCondition_DemEnableCondition_BusOff                  2u 
#define DemConf_DemEnableCondition_DemEnableCondition_KL15_ON                 3u 
#define DemConf_DemEnableCondition_DemEnableCondition_TimeoutMonitoringState  4u 
#define DemConf_DemEnableCondition_DemEnableCondition_tDiagStart              5u 

 /*  EnableCondition global definitions  */ 
#define DEM_CFG_GLOBAL_ENABLE_COND_COUNT                              6u           /* (DEM_CFG_SUPPORT_ENABLE_CONDITIONS == STD_ON) or there are internal EnableConditions. */ 

 /*  Client IDs [symbolic name value]  */ 
#define DemConf_DemClient_DemClient                                   0u 

 /*  Client global definitions  */ 
#define DEM_CFG_CLEARDTC_INVALID                                      255u         /* Value used as invalid index in Dem_Cfg_ClientTable[] for the ClearDTCIndex - the Client has no ClearDTC filter. */ 
#define DEM_CFG_DTCSELECTOR_INVALID                                   255u         /* Value used as invalid index in Dem_Cfg_ClientTable[] for the SelectorIndex - the Client has no selector. */ 
#define DEM_CFG_FILTER_INVALID                                        255u         /* Value used as invalid index in Dem_Cfg_ClientTable[] for the FilterIndex - the Client has no filter. */ 
#define DEM_CFG_FREEZEFRAMEITERATOR_INVALID                           255u         /* Value used as invalid index in Dem_Cfg_ClientTable[] for the FreezeFrameIteratorIndex - the Client has no FreezeFrameIterator. */ 
#define DEM_CFG_GLOBAL_CLIENT_COUNT                                   1u           /* Total number of configured /Dem/DemGeneral/DemClient containers. */ 
#define DEM_CFG_NMNODEID_INVALID                                      65535u       /* Value used in Dem_Cfg_ClientTable[] for a Client, that has no J1939NmNode configured in the J1939Dcm. */ 
#define DEM_CFG_NUMBER_OF_CLEARDTCS                                   1u           /* Currently equal to the total number of configured /Dem/DemGeneral/DemClient containers. */ 
#define DEM_CFG_NUMBER_OF_DTCSELECTORS                                1u           /* Currently equal to the total number of configured /Dem/DemGeneral/DemClient containers. */ 
#define DEM_CFG_NUMBER_OF_FILTER                                      1u           /* Currently equal to the total number of configured /Dem/DemGeneral/DemClient containers. */ 
#define DEM_CFG_NUMBER_OF_FREEZEFRAMEITERATORS                        1u           /* Currently equal to the total number of configured /Dem/DemGeneral/DemClient containers. */ 
#define DEM_CFG_NUMBER_OF_READOUTBUFFERS                              1u           /* Currently equal to the total number of configured /Dem/DemGeneral/DemClient containers. */ 
#define DEM_CFG_READOUTBUFFER_INVALID                                 255u         /* Value used as invalid index in Dem_Cfg_ClientTable[] for the ReadoutBufferIndex - the Client has no ReadoutBuffer. */ 




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
  \defgroup  Dem_CfgPCGetConstantDuplicatedRootDataMacros  Dem_Cfg Get Constant Duplicated Root Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated by constance root data elements.
  \{
*/ 
#define Dem_Cfg_GetAdminDataOfPCConfig()                                                            (&(Dem_Cfg_AdminData))  /**< the pointer to Dem_Cfg_AdminData */
#define Dem_Cfg_GetAgingDataOfPCConfig()                                                            (&(Dem_Cfg_AgingData))  /**< the pointer to Dem_Cfg_AgingData */
#define Dem_Cfg_GetCallbackClearEventAllowedOfPCConfig()                                            Dem_Cfg_CallbackClearEventAllowed  /**< the pointer to Dem_Cfg_CallbackClearEventAllowed */
#define Dem_Cfg_GetCallbackDtcStatusChangedOfPCConfig()                                             Dem_Cfg_CallbackDtcStatusChanged  /**< the pointer to Dem_Cfg_CallbackDtcStatusChanged */
#define Dem_Cfg_GetCallbackGetFdcOfPCConfig()                                                       Dem_Cfg_CallbackGetFdc  /**< the pointer to Dem_Cfg_CallbackGetFdc */
#define Dem_Cfg_GetCallbackJ1939DtcStatusChangedOfPCConfig()                                        Dem_Cfg_CallbackJ1939DtcStatusChanged  /**< the pointer to Dem_Cfg_CallbackJ1939DtcStatusChanged */
#define Dem_Cfg_GetClearDTCTableOfPCConfig()                                                        Dem_Cfg_ClearDTCTable  /**< the pointer to Dem_Cfg_ClearDTCTable */
#define Dem_Cfg_GetClearDtcNotificationFinishTableOfPCConfig()                                      Dem_Cfg_ClearDtcNotificationFinishTable  /**< the pointer to Dem_Cfg_ClearDtcNotificationFinishTable */
#define Dem_Cfg_GetClearDtcNotificationStartTableOfPCConfig()                                       Dem_Cfg_ClearDtcNotificationStartTable  /**< the pointer to Dem_Cfg_ClearDtcNotificationStartTable */
#define Dem_Cfg_GetClientTableOfPCConfig()                                                          Dem_Cfg_ClientTable  /**< the pointer to Dem_Cfg_ClientTable */
#define Dem_Cfg_GetCommitBufferOfPCConfig()                                                         (&(Dem_Cfg_CommitBuffer))  /**< the pointer to Dem_Cfg_CommitBuffer */
#define Dem_Cfg_GetConfigurationIdOfPCConfig()                                                      0x97BAu  /**< Magic constant derived from the configuration parameters /Dem/DemGeneral/DemCompiledConfigId and /Dem/DemGeneral/DemCompiledPostbuildCrc. Each value change is evidence to incompatible NV stored data and triggers a re-initialization of the NV data. */
#define Dem_Cfg_GetCycleCounterDataOfPCConfig()                                                     (&(Dem_Cfg_CycleCounterData))  /**< the pointer to Dem_Cfg_CycleCounterData */
#define Dem_Cfg_GetCycleIdTableOfPCConfig()                                                         Dem_Cfg_CycleIdTable  /**< the pointer to Dem_Cfg_CycleIdTable */
#define Dem_Cfg_GetDTCSelectorTableOfPCConfig()                                                     Dem_Cfg_DTCSelectorTable  /**< the pointer to Dem_Cfg_DTCSelectorTable */
#define Dem_Cfg_GetDataCollectionTableEdr2CollIndOfPCConfig()                                       Dem_Cfg_DataCollectionTableEdr2CollInd  /**< the pointer to Dem_Cfg_DataCollectionTableEdr2CollInd */
#define Dem_Cfg_GetDataCollectionTableErec2CollIndOfPCConfig()                                      Dem_Cfg_DataCollectionTableErec2CollInd  /**< the pointer to Dem_Cfg_DataCollectionTableErec2CollInd */
#define Dem_Cfg_GetDataCollectionTableFfm2CollIndOfPCConfig()                                       Dem_Cfg_DataCollectionTableFfm2CollInd  /**< the pointer to Dem_Cfg_DataCollectionTableFfm2CollInd */
#define Dem_Cfg_GetDataCollectionTableJ19392CollIndOfPCConfig()                                     Dem_Cfg_DataCollectionTableJ19392CollInd  /**< the pointer to Dem_Cfg_DataCollectionTableJ19392CollInd */
#define Dem_Cfg_GetDataCollectionTableOfPCConfig()                                                  Dem_Cfg_DataCollectionTable  /**< the pointer to Dem_Cfg_DataCollectionTable */
#define Dem_Cfg_GetDataCollectionTablePid2CollIndOfPCConfig()                                       Dem_Cfg_DataCollectionTablePid2CollInd  /**< the pointer to Dem_Cfg_DataCollectionTablePid2CollInd */
#define Dem_Cfg_GetDataElementTableCol2ElmtIndOfPCConfig()                                          Dem_Cfg_DataElementTableCol2ElmtInd  /**< the pointer to Dem_Cfg_DataElementTableCol2ElmtInd */
#define Dem_Cfg_GetDataElementTableOfPCConfig()                                                     Dem_Cfg_DataElementTable  /**< the pointer to Dem_Cfg_DataElementTable */
#define Dem_Cfg_GetDebounceDataOfPCConfig()                                                         (&(Dem_Cfg_DebounceData))  /**< the pointer to Dem_Cfg_DebounceData */
#define Dem_Cfg_GetDebounceHiResTableOfPCConfig()                                                   Dem_Cfg_DebounceHiResTable  /**< the pointer to Dem_Cfg_DebounceHiResTable */
#define Dem_Cfg_GetDebounceLoResTableOfPCConfig()                                                   Dem_Cfg_DebounceLoResTable  /**< the pointer to Dem_Cfg_DebounceLoResTable */
#define Dem_Cfg_GetDebounceTableOfPCConfig()                                                        Dem_Cfg_DebounceTable  /**< the pointer to Dem_Cfg_DebounceTable */
#define Dem_Cfg_GetDtcGroupMaskOfPCConfig()                                                         Dem_Cfg_DtcGroupMask  /**< the pointer to Dem_Cfg_DtcGroupMask */
#define Dem_Cfg_GetDtcTableOfPCConfig()                                                             Dem_Cfg_DtcTable  /**< the pointer to Dem_Cfg_DtcTable */
#define Dem_Cfg_GetDtrDataOfPCConfig()                                                              (&(Dem_Cfg_DtrData))  /**< the pointer to Dem_Cfg_DtrData */
#define Dem_Cfg_GetDtrStatusOfPCConfig()                                                            Dem_Cfg_DtrStatus  /**< the pointer to Dem_Cfg_DtrStatus */
#define Dem_Cfg_GetDtrTableIndOfPCConfig()                                                          Dem_Cfg_DtrTableInd  /**< the pointer to Dem_Cfg_DtrTableInd */
#define Dem_Cfg_GetDtrTableOfPCConfig()                                                             Dem_Cfg_DtrTable  /**< the pointer to Dem_Cfg_DtrTable */
#define Dem_Cfg_GetEnableConditionFulfilledOfPCConfig()                                             Dem_Cfg_EnableConditionFulfilled  /**< the pointer to Dem_Cfg_EnableConditionFulfilled */
#define Dem_Cfg_GetEnableConditionGroupCounterOfPCConfig()                                          Dem_Cfg_EnableConditionGroupCounter  /**< the pointer to Dem_Cfg_EnableConditionGroupCounter */
#define Dem_Cfg_GetEnableConditionGroupStateOfPCConfig()                                            Dem_Cfg_EnableConditionGroupState  /**< the pointer to Dem_Cfg_EnableConditionGroupState */
#define Dem_Cfg_GetEnableConditionGroupTableIndOfPCConfig()                                         Dem_Cfg_EnableConditionGroupTableInd  /**< the pointer to Dem_Cfg_EnableConditionGroupTableInd */
#define Dem_Cfg_GetEnableConditionGroupTableOfPCConfig()                                            Dem_Cfg_EnableConditionGroupTable  /**< the pointer to Dem_Cfg_EnableConditionGroupTable */
#define Dem_Cfg_GetEnableConditionInitTableOfPCConfig()                                             Dem_Cfg_EnableConditionInitTable  /**< the pointer to Dem_Cfg_EnableConditionInitTable */
#define Dem_Cfg_GetEnableConditionTableOfPCConfig()                                                 Dem_Cfg_EnableConditionTable  /**< the pointer to Dem_Cfg_EnableConditionTable */
#define Dem_Cfg_GetEventAvailableDataOfPCConfig()                                                   (&(Dem_Cfg_EventAvailableData))  /**< the pointer to Dem_Cfg_EventAvailableData */
#define Dem_Cfg_GetEventAvailableDefaultOfPCConfig()                                                Dem_Cfg_EventAvailableDefault  /**< the pointer to Dem_Cfg_EventAvailableDefault */
#define Dem_Cfg_GetEventAvailableInVariantOfPCConfig()                                              Dem_Cfg_EventAvailableInVariant  /**< the pointer to Dem_Cfg_EventAvailableInVariant */
#define Dem_Cfg_GetEventCycleStatusOfPCConfig()                                                     Dem_Cfg_EventCycleStatus  /**< the pointer to Dem_Cfg_EventCycleStatus */
#define Dem_Cfg_GetEventDataChangedOfPCConfig()                                                     Dem_Cfg_EventDataChanged  /**< the pointer to Dem_Cfg_EventDataChanged */
#define Dem_Cfg_GetEventDataCommitNumberOfPCConfig()                                                Dem_Cfg_EventDataCommitNumber  /**< the pointer to Dem_Cfg_EventDataCommitNumber */
#define Dem_Cfg_GetEventDebounceValueOfPCConfig()                                                   Dem_Cfg_EventDebounceValue  /**< the pointer to Dem_Cfg_EventDebounceValue */
#define Dem_Cfg_GetEventInternalStatusOfPCConfig()                                                  Dem_Cfg_EventInternalStatus  /**< the pointer to Dem_Cfg_EventInternalStatus */
#define Dem_Cfg_GetEventStatusChangedOfPCConfig()                                                   Dem_Cfg_EventStatusChanged  /**< the pointer to Dem_Cfg_EventStatusChanged */
#define Dem_Cfg_GetEventTableIndOfPCConfig()                                                        Dem_Cfg_EventTableInd  /**< the pointer to Dem_Cfg_EventTableInd */
#define Dem_Cfg_GetEventTableOfPCConfig()                                                           Dem_Cfg_EventTable  /**< the pointer to Dem_Cfg_EventTable */
#define Dem_Cfg_GetEventTable_ERec2EventIdIndOfPCConfig()                                           Dem_Cfg_EventTable_ERec2EventIdInd  /**< the pointer to Dem_Cfg_EventTable_ERec2EventIdInd */
#define Dem_Cfg_GetEventTable_ObdRdyGroup2EventIdIndOfPCConfig()                                    Dem_Cfg_EventTable_ObdRdyGroup2EventIdInd  /**< the pointer to Dem_Cfg_EventTable_ObdRdyGroup2EventIdInd */
#define Dem_Cfg_GetExtendedDataRecordIteratorTableOfPCConfig()                                      Dem_Cfg_ExtendedDataRecordIteratorTable  /**< the pointer to Dem_Cfg_ExtendedDataRecordIteratorTable */
#define Dem_Cfg_GetExtendedDataRecordTableOfPCConfig()                                              Dem_Cfg_ExtendedDataRecordTable  /**< the pointer to Dem_Cfg_ExtendedDataRecordTable */
#define Dem_Cfg_GetExtendedDataTableOfPCConfig()                                                    Dem_Cfg_ExtendedDataTable  /**< the pointer to Dem_Cfg_ExtendedDataTable */
#define Dem_Cfg_GetFilterInfoTableOfPCConfig()                                                      Dem_Cfg_FilterInfoTable  /**< the pointer to Dem_Cfg_FilterInfoTable */
#define Dem_Cfg_GetFilterReportedEventsOfPCConfig()                                                 Dem_Cfg_FilterReportedEvents  /**< the pointer to Dem_Cfg_FilterReportedEvents */
#define Dem_Cfg_GetFinalMagicNumberOfPCConfig(ConfigDataPtr)                                        0x361Eu  /**< the FinalMagicNumber to validate the size of the initialization structure at initialization time of Dem */
#define Dem_Cfg_GetFreezeFrameDataOfPCConfig()                                                      (&(Dem_Cfg_FreezeFrameData))  /**< the pointer to Dem_Cfg_FreezeFrameData */
#define Dem_Cfg_GetFreezeFrameIteratorTableOfPCConfig()                                             Dem_Cfg_FreezeFrameIteratorTable  /**< the pointer to Dem_Cfg_FreezeFrameIteratorTable */
#define Dem_Cfg_GetFreezeFrameNumTableOfPCConfig()                                                  Dem_Cfg_FreezeFrameNumTable  /**< the pointer to Dem_Cfg_FreezeFrameNumTable */
#define Dem_Cfg_GetFreezeFrameTableOfPCConfig()                                                     Dem_Cfg_FreezeFrameTable  /**< the pointer to Dem_Cfg_FreezeFrameTable */
#define Dem_Cfg_GetGeneralJ1939TableOfPCConfig()                                                    Dem_Cfg_GeneralJ1939Table  /**< the pointer to Dem_Cfg_GeneralJ1939Table */
#define Dem_Cfg_GetGeneralObdInputOfPCConfig()                                                      Dem_Cfg_GeneralObdInput  /**< the pointer to Dem_Cfg_GeneralObdInput */
#define Dem_Cfg_GetGlobalIndicatorStatesOfPCConfig()                                                Dem_Cfg_GlobalIndicatorStates  /**< the pointer to Dem_Cfg_GlobalIndicatorStates */
#define Dem_Cfg_GetGlobalObdRequirementsOfPCConfig()                                                1u
#define Dem_Cfg_GetGlobalSeverityMaskOfPCConfig()                                                   0x00u  /**< Variant specific mask from OR'ed /Dem/DemConfigSet/DemDTCClass/DemDTCSeverity bits. */
#define Dem_Cfg_GetIndicatorBlinkingOfPCConfig()                                                    Dem_Cfg_IndicatorBlinking  /**< the pointer to Dem_Cfg_IndicatorBlinking */
#define Dem_Cfg_GetIndicatorContinuousOfPCConfig()                                                  Dem_Cfg_IndicatorContinuous  /**< the pointer to Dem_Cfg_IndicatorContinuous */
#define Dem_Cfg_GetIndicatorFastFlashOfPCConfig()                                                   Dem_Cfg_IndicatorFastFlash  /**< the pointer to Dem_Cfg_IndicatorFastFlash */
#define Dem_Cfg_GetIndicatorSlowFlashOfPCConfig()                                                   Dem_Cfg_IndicatorSlowFlash  /**< the pointer to Dem_Cfg_IndicatorSlowFlash */
#define Dem_Cfg_GetInitDataHashCodeOfPCConfig(ConfigDataPtr)                                        -1327498799  /**< the hashcode to validate the initialization structure at initialization time of Dem */
#define Dem_Cfg_GetInitMonListForFuncOfPCConfig()                                                   Dem_Cfg_InitMonListForFunc  /**< the pointer to Dem_Cfg_InitMonListForFunc */
#define Dem_Cfg_GetInitMonitorForEventOfPCConfig()                                                  Dem_Cfg_InitMonitorForEvent  /**< the pointer to Dem_Cfg_InitMonitorForEvent */
#define Dem_Cfg_GetInitMonitorsForFuncOfPCConfig()                                                  Dem_Cfg_InitMonitorsForFunc  /**< the pointer to Dem_Cfg_InitMonitorsForFunc */
#define Dem_Cfg_GetJ1939NodeIdIndOfPCConfig()                                                       Dem_Cfg_J1939NodeIdInd  /**< the pointer to Dem_Cfg_J1939NodeIdInd */
#define Dem_Cfg_GetJ1939NodeIdOfPCConfig()                                                          Dem_Cfg_J1939NodeId  /**< the pointer to Dem_Cfg_J1939NodeId */
#define Dem_Cfg_GetJ1939NodeIndicatorOfPCConfig()                                                   Dem_Cfg_J1939NodeIndicator  /**< the pointer to Dem_Cfg_J1939NodeIndicator */
#define Dem_Cfg_GetMemoryBlockIdOfPCConfig()                                                        Dem_Cfg_MemoryBlockId  /**< the pointer to Dem_Cfg_MemoryBlockId */
#define Dem_Cfg_GetMemoryBlockIdToMemoryEntryIdOfPCConfig()                                         Dem_Cfg_MemoryBlockIdToMemoryEntryId  /**< the pointer to Dem_Cfg_MemoryBlockIdToMemoryEntryId */
#define Dem_Cfg_GetMemoryDataPtrOfPCConfig()                                                        Dem_Cfg_MemoryDataPtr  /**< the pointer to Dem_Cfg_MemoryDataPtr */
#define Dem_Cfg_GetMemoryDataSizeOfPCConfig()                                                       Dem_Cfg_MemoryDataSize  /**< the pointer to Dem_Cfg_MemoryDataSize */
#define Dem_Cfg_GetMemoryEntryInitOfPCConfig()                                                      (&(Dem_Cfg_MemoryEntryInit))  /**< the pointer to Dem_Cfg_MemoryEntryInit */
#define Dem_Cfg_GetMemoryEntryOfPCConfig()                                                          Dem_Cfg_MemoryEntry  /**< the pointer to Dem_Cfg_MemoryEntry */
#define Dem_Cfg_GetMemoryStatusOfPCConfig()                                                         Dem_Cfg_MemoryStatus  /**< the pointer to Dem_Cfg_MemoryStatus */
#define Dem_Cfg_GetMidTableOfPCConfig()                                                             Dem_Cfg_MidTable  /**< the pointer to Dem_Cfg_MidTable */
#define Dem_Cfg_GetMirrorDataOfPCConfig()                                                           (&(Dem_Cfg_MirrorData))  /**< the pointer to Dem_Cfg_MirrorData */
#define Dem_Cfg_GetNormalIndicatorTableOfPCConfig()                                                 Dem_Cfg_NormalIndicatorTable  /**< the pointer to Dem_Cfg_NormalIndicatorTable */
#define Dem_Cfg_GetObdIumprDataOfPCConfig()                                                         (&(Dem_Cfg_ObdIumprData))  /**< the pointer to Dem_Cfg_ObdIumprData */
#define Dem_Cfg_GetObdIumprUpdatePendingOfPCConfig()                                                Dem_Cfg_ObdIumprUpdatePending  /**< the pointer to Dem_Cfg_ObdIumprUpdatePending */
#define Dem_Cfg_GetPermanentDataOfPCConfig()                                                        (&(Dem_Cfg_PermanentData))  /**< the pointer to Dem_Cfg_PermanentData */
#define Dem_Cfg_GetPidTableOfPCConfig()                                                             Dem_Cfg_PidTable  /**< the pointer to Dem_Cfg_PidTable */
#define Dem_Cfg_GetPrestorageIndexOfPCConfig()                                                      Dem_Cfg_PrestorageIndex  /**< the pointer to Dem_Cfg_PrestorageIndex */
#define Dem_Cfg_GetPrestorageOfPCConfig()                                                           (&(Dem_Cfg_Prestorage))  /**< the pointer to Dem_Cfg_Prestorage */
#define Dem_Cfg_GetPrimaryChronologyOfPCConfig()                                                    Dem_Cfg_PrimaryChronology  /**< the pointer to Dem_Cfg_PrimaryChronology */
#define Dem_Cfg_GetPrimaryEntry_0OfPCConfig()                                                       (&(Dem_Cfg_PrimaryEntry_0))  /**< the pointer to Dem_Cfg_PrimaryEntry_0 */
#define Dem_Cfg_GetPrimaryEntry_1OfPCConfig()                                                       (&(Dem_Cfg_PrimaryEntry_1))  /**< the pointer to Dem_Cfg_PrimaryEntry_1 */
#define Dem_Cfg_GetPrimaryEntry_2OfPCConfig()                                                       (&(Dem_Cfg_PrimaryEntry_2))  /**< the pointer to Dem_Cfg_PrimaryEntry_2 */
#define Dem_Cfg_GetPrimaryEntry_3OfPCConfig()                                                       (&(Dem_Cfg_PrimaryEntry_3))  /**< the pointer to Dem_Cfg_PrimaryEntry_3 */
#define Dem_Cfg_GetPrimaryEntry_4OfPCConfig()                                                       (&(Dem_Cfg_PrimaryEntry_4))  /**< the pointer to Dem_Cfg_PrimaryEntry_4 */
#define Dem_Cfg_GetPrimaryEntry_5OfPCConfig()                                                       (&(Dem_Cfg_PrimaryEntry_5))  /**< the pointer to Dem_Cfg_PrimaryEntry_5 */
#define Dem_Cfg_GetPrimaryEntry_6OfPCConfig()                                                       (&(Dem_Cfg_PrimaryEntry_6))  /**< the pointer to Dem_Cfg_PrimaryEntry_6 */
#define Dem_Cfg_GetPrimaryEntry_7OfPCConfig()                                                       (&(Dem_Cfg_PrimaryEntry_7))  /**< the pointer to Dem_Cfg_PrimaryEntry_7 */
#define Dem_Cfg_GetRatioIdTableOfPCConfig()                                                         Dem_Cfg_RatioIdTable  /**< the pointer to Dem_Cfg_RatioIdTable */
#define Dem_Cfg_GetReadinessGroupTableOfPCConfig()                                                  Dem_Cfg_ReadinessGroupTable  /**< the pointer to Dem_Cfg_ReadinessGroupTable */
#define Dem_Cfg_GetReadoutBufferOfPCConfig()                                                        Dem_Cfg_ReadoutBuffer  /**< the pointer to Dem_Cfg_ReadoutBuffer */
#define Dem_Cfg_GetReportedEventsOfFilterOfPCConfig()                                               Dem_Cfg_ReportedEventsOfFilter  /**< the pointer to Dem_Cfg_ReportedEventsOfFilter */
#define Dem_Cfg_GetSatelliteInfo0OfPCConfig()                                                       (&(Dem_Cfg_SatelliteInfo0))  /**< the pointer to Dem_Cfg_SatelliteInfo0 */
#define Dem_Cfg_GetSatelliteInfoOfPCConfig()                                                        Dem_Cfg_SatelliteInfo  /**< the pointer to Dem_Cfg_SatelliteInfo */
#define Dem_Cfg_GetSatelliteTimeDebounceInfoOfPCConfig()                                            Dem_Cfg_SatelliteTimeDebounceInfo  /**< the pointer to Dem_Cfg_SatelliteTimeDebounceInfo */
#define Dem_Cfg_GetSecondaryChronologyOfPCConfig()                                                  Dem_Cfg_SecondaryChronology  /**< the pointer to Dem_Cfg_SecondaryChronology */
#define Dem_Cfg_GetSizeOfCallbackClearEventAllowedOfPCConfig()                                      5u  /**< the number of accomplishable value elements in Dem_Cfg_CallbackClearEventAllowed */
#define Dem_Cfg_GetSizeOfCallbackDtcStatusChangedOfPCConfig()                                       0u  /**< the number of accomplishable value elements in Dem_Cfg_CallbackDtcStatusChanged */
#define Dem_Cfg_GetSizeOfCallbackGetFdcOfPCConfig()                                                 0u  /**< the number of accomplishable value elements in Dem_Cfg_CallbackGetFdc */
#define Dem_Cfg_GetSizeOfCallbackJ1939DtcStatusChangedOfPCConfig()                                  0u  /**< the number of accomplishable value elements in Dem_Cfg_CallbackJ1939DtcStatusChanged */
#define Dem_Cfg_GetSizeOfClearDTCTableOfPCConfig()                                                  1u  /**< the number of accomplishable value elements in Dem_Cfg_ClearDTCTable */
#define Dem_Cfg_GetSizeOfClearDtcNotificationFinishTableOfPCConfig()                                0u  /**< the number of accomplishable value elements in Dem_Cfg_ClearDtcNotificationFinishTable */
#define Dem_Cfg_GetSizeOfClearDtcNotificationStartTableOfPCConfig()                                 0u  /**< the number of accomplishable value elements in Dem_Cfg_ClearDtcNotificationStartTable */
#define Dem_Cfg_GetSizeOfClientTableOfPCConfig()                                                    1u  /**< the number of accomplishable value elements in Dem_Cfg_ClientTable */
#define Dem_Cfg_GetSizeOfDTCSelectorTableOfPCConfig()                                               1u  /**< the number of accomplishable value elements in Dem_Cfg_DTCSelectorTable */
#define Dem_Cfg_GetSizeOfDataElementTableOfPCConfig()                                               10u  /**< the number of accomplishable value elements in Dem_Cfg_DataElementTable */
#define Dem_Cfg_GetSizeOfDebounceHiResTableOfPCConfig()                                             0u  /**< the number of accomplishable value elements in Dem_Cfg_DebounceHiResTable */
#define Dem_Cfg_GetSizeOfDebounceLoResTableOfPCConfig()                                             0u  /**< the number of accomplishable value elements in Dem_Cfg_DebounceLoResTable */
#define Dem_Cfg_GetSizeOfDtcGroupMaskOfPCConfig()                                                   0u  /**< the number of accomplishable value elements in Dem_Cfg_DtcGroupMask */
#define Dem_Cfg_GetSizeOfDtrStatusOfPCConfig()                                                      0u  /**< the number of accomplishable value elements in Dem_Cfg_DtrStatus */
#define Dem_Cfg_GetSizeOfDtrTableOfPCConfig()                                                       0u  /**< the number of accomplishable value elements in Dem_Cfg_DtrTable */
#define Dem_Cfg_GetSizeOfEnableConditionGroupTableOfPCConfig()                                      4u  /**< the number of accomplishable value elements in Dem_Cfg_EnableConditionGroupTable */
#define Dem_Cfg_GetSizeOfEnableConditionTableOfPCConfig()                                           6u  /**< the number of accomplishable value elements in Dem_Cfg_EnableConditionTable */
#define Dem_Cfg_GetSizeOfEventCycleStatusOfPCConfig()                                               0u  /**< the number of accomplishable value elements in Dem_Cfg_EventCycleStatus */
#define Dem_Cfg_GetSizeOfEventDataChangedOfPCConfig()                                               0u  /**< the number of accomplishable value elements in Dem_Cfg_EventDataChanged */
#define Dem_Cfg_GetSizeOfEventDataCommitNumberOfPCConfig()                                          16u  /**< the number of accomplishable value elements in Dem_Cfg_EventDataCommitNumber */
#define Dem_Cfg_GetSizeOfEventStatusChangedOfPCConfig()                                             0u  /**< the number of accomplishable value elements in Dem_Cfg_EventStatusChanged */
#define Dem_Cfg_GetSizeOfEventTableOfPCConfig()                                                     16u  /**< the number of accomplishable value elements in Dem_Cfg_EventTable */
#define Dem_Cfg_GetSizeOfExtendedDataRecordIteratorTableOfPCConfig()                                1u  /**< the number of accomplishable value elements in Dem_Cfg_ExtendedDataRecordIteratorTable */
#define Dem_Cfg_GetSizeOfFilterInfoTableOfPCConfig()                                                1u  /**< the number of accomplishable value elements in Dem_Cfg_FilterInfoTable */
#define Dem_Cfg_GetSizeOfFilterReportedEventsOfPCConfig()                                           2u  /**< the number of accomplishable value elements in Dem_Cfg_FilterReportedEvents */
#define Dem_Cfg_GetSizeOfFreezeFrameIteratorTableOfPCConfig()                                       1u  /**< the number of accomplishable value elements in Dem_Cfg_FreezeFrameIteratorTable */
#define Dem_Cfg_GetSizeOfGlobalIndicatorStatesOfPCConfig()                                          0u  /**< the number of accomplishable value elements in Dem_Cfg_GlobalIndicatorStates */
#define Dem_Cfg_GetSizeOfIndicatorBlinkingOfPCConfig()                                              0u  /**< the number of accomplishable value elements in Dem_Cfg_IndicatorBlinking */
#define Dem_Cfg_GetSizeOfIndicatorContinuousOfPCConfig()                                            0u  /**< the number of accomplishable value elements in Dem_Cfg_IndicatorContinuous */
#define Dem_Cfg_GetSizeOfIndicatorFastFlashOfPCConfig()                                             0u  /**< the number of accomplishable value elements in Dem_Cfg_IndicatorFastFlash */
#define Dem_Cfg_GetSizeOfIndicatorSlowFlashOfPCConfig()                                             0u  /**< the number of accomplishable value elements in Dem_Cfg_IndicatorSlowFlash */
#define Dem_Cfg_GetSizeOfInitMonitorForEventOfPCConfig()                                            0u  /**< the number of accomplishable value elements in Dem_Cfg_InitMonitorForEvent */
#define Dem_Cfg_GetSizeOfInitMonitorsForFuncOfPCConfig()                                            0u  /**< the number of accomplishable value elements in Dem_Cfg_InitMonitorsForFunc */
#define Dem_Cfg_GetSizeOfMemoryBlockIdToMemoryEntryIdOfPCConfig()                                   10u  /**< the number of accomplishable value elements in Dem_Cfg_MemoryBlockIdToMemoryEntryId */
#define Dem_Cfg_GetSizeOfMemoryEntryOfPCConfig()                                                    9u  /**< the number of accomplishable value elements in Dem_Cfg_MemoryEntry */
#define Dem_Cfg_GetSizeOfMemoryStatusOfPCConfig()                                                   10u  /**< the number of accomplishable value elements in Dem_Cfg_MemoryStatus */
#define Dem_Cfg_GetSizeOfObdIumprUpdatePendingOfPCConfig()                                          0u  /**< the number of accomplishable value elements in Dem_Cfg_ObdIumprUpdatePending */
#define Dem_Cfg_GetSizeOfPrestorageIndexOfPCConfig()                                                0u  /**< the number of accomplishable value elements in Dem_Cfg_PrestorageIndex */
#define Dem_Cfg_GetSizeOfPrimaryChronologyOfPCConfig()                                              8u  /**< the number of accomplishable value elements in Dem_Cfg_PrimaryChronology */
#define Dem_Cfg_GetSizeOfReadinessGroupTableOfPCConfig()                                            1u  /**< the number of accomplishable value elements in Dem_Cfg_ReadinessGroupTable */
#define Dem_Cfg_GetSizeOfReadoutBufferOfPCConfig()                                                  1u  /**< the number of accomplishable value elements in Dem_Cfg_ReadoutBuffer */
#define Dem_Cfg_GetSizeOfReportedEventsOfFilterOfPCConfig()                                         1u  /**< the number of accomplishable value elements in Dem_Cfg_ReportedEventsOfFilter */
#define Dem_Cfg_GetSizeOfSatelliteInfoOfPCConfig()                                                  1u  /**< the number of accomplishable value elements in Dem_Cfg_SatelliteInfo */
#define Dem_Cfg_GetSizeOfSecondaryChronologyOfPCConfig()                                            0u  /**< the number of accomplishable value elements in Dem_Cfg_SecondaryChronology */
#define Dem_Cfg_GetSizeOfSpecialIndicatorTableOfPCConfig()                                          0u  /**< the number of accomplishable value elements in Dem_Cfg_SpecialIndicatorTable */
#define Dem_Cfg_GetSizeOfStartIdx500miDenRatioTableOfPCConfig()                                     0u  /**< the number of accomplishable value elements in Dem_Cfg_StartIdx500miDenRatioTable */
#define Dem_Cfg_GetSizeOfStorageConditionFulfilledOfPCConfig()                                      0u  /**< the number of accomplishable value elements in Dem_Cfg_StorageConditionFulfilled */
#define Dem_Cfg_GetSizeOfStorageConditionGroupCounterOfPCConfig()                                   0u  /**< the number of accomplishable value elements in Dem_Cfg_StorageConditionGroupCounter */
#define Dem_Cfg_GetSizeOfStorageConditionGroupTableOfPCConfig()                                     0u  /**< the number of accomplishable value elements in Dem_Cfg_StorageConditionGroupTable */
#define Dem_Cfg_GetSizeOfStorageConditionTableOfPCConfig()                                          0u  /**< the number of accomplishable value elements in Dem_Cfg_StorageConditionTable */
#define Dem_Cfg_GetSizeOfSupportedMidsTableOfPCConfig()                                             0u  /**< the number of accomplishable value elements in Dem_Cfg_SupportedMidsTable */
#define Dem_Cfg_GetSizeOfTimeSeriesChronologyOfPCConfig()                                           0u  /**< the number of accomplishable value elements in Dem_Cfg_TimeSeriesChronology */
#define Dem_Cfg_GetSpecialIndicatorTableOfPCConfig()                                                Dem_Cfg_SpecialIndicatorTable  /**< the pointer to Dem_Cfg_SpecialIndicatorTable */
#define Dem_Cfg_GetStartIdx500miDenRatioTableOfPCConfig()                                           Dem_Cfg_StartIdx500miDenRatioTable  /**< the pointer to Dem_Cfg_StartIdx500miDenRatioTable */
#define Dem_Cfg_GetStatusDataOfPCConfig()                                                           (&(Dem_Cfg_StatusData))  /**< the pointer to Dem_Cfg_StatusData */
#define Dem_Cfg_GetStorageConditionFulfilledOfPCConfig()                                            Dem_Cfg_StorageConditionFulfilled  /**< the pointer to Dem_Cfg_StorageConditionFulfilled */
#define Dem_Cfg_GetStorageConditionGroupCounterOfPCConfig()                                         Dem_Cfg_StorageConditionGroupCounter  /**< the pointer to Dem_Cfg_StorageConditionGroupCounter */
#define Dem_Cfg_GetStorageConditionGroupTableIndOfPCConfig()                                        Dem_Cfg_StorageConditionGroupTableInd  /**< the pointer to Dem_Cfg_StorageConditionGroupTableInd */
#define Dem_Cfg_GetStorageConditionGroupTableOfPCConfig()                                           Dem_Cfg_StorageConditionGroupTable  /**< the pointer to Dem_Cfg_StorageConditionGroupTable */
#define Dem_Cfg_GetStorageConditionInitTableOfPCConfig()                                            Dem_Cfg_StorageConditionInitTable  /**< the pointer to Dem_Cfg_StorageConditionInitTable */
#define Dem_Cfg_GetStorageConditionTableOfPCConfig()                                                Dem_Cfg_StorageConditionTable  /**< the pointer to Dem_Cfg_StorageConditionTable */
#define Dem_Cfg_GetSupportedMidsTableOfPCConfig()                                                   Dem_Cfg_SupportedMidsTable  /**< the pointer to Dem_Cfg_SupportedMidsTable */
#define Dem_Cfg_GetTimeSeriesChronologyOfPCConfig()                                                 Dem_Cfg_TimeSeriesChronology  /**< the pointer to Dem_Cfg_TimeSeriesChronology */
#define Dem_Cfg_GetTimeSeriesEntryInitOfPCConfig()                                                  (&(Dem_Cfg_TimeSeriesEntryInit))  /**< the pointer to Dem_Cfg_TimeSeriesEntryInit */
#define Dem_Cfg_IsUseOBDIIInVariantOfPCConfig()                                                     (((FALSE)) != FALSE)
#define Dem_Cfg_IsUsePermanentInVariantOfPCConfig()                                                 (((FALSE)) != FALSE)
#define Dem_Cfg_IsUseWWHOBDInVariantOfPCConfig()                                                    (((FALSE)) != FALSE)
/** 
  \}
*/ 

/** 
  \defgroup  Dem_CfgPCGetDuplicatedRootDataMacros  Dem_Cfg Get Duplicated Root Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated root data elements.
  \{
*/ 
#define Dem_Cfg_GetSizeOfEnableConditionFulfilledOfPCConfig()                                       Dem_Cfg_GetSizeOfEnableConditionTableOfPCConfig()  /**< the number of accomplishable value elements in Dem_Cfg_EnableConditionFulfilled */
#define Dem_Cfg_GetSizeOfEnableConditionGroupCounterOfPCConfig()                                    Dem_Cfg_GetSizeOfEnableConditionGroupTableOfPCConfig()  /**< the number of accomplishable value elements in Dem_Cfg_EnableConditionGroupCounter */
#define Dem_Cfg_GetSizeOfEnableConditionGroupStateOfPCConfig()                                      Dem_Cfg_GetSizeOfEnableConditionGroupTableOfPCConfig()  /**< the number of accomplishable value elements in Dem_Cfg_EnableConditionGroupState */
#define Dem_Cfg_GetSizeOfEventDebounceValueOfPCConfig()                                             Dem_Cfg_GetSizeOfEventTableOfPCConfig()  /**< the number of accomplishable value elements in Dem_Cfg_EventDebounceValue */
#define Dem_Cfg_GetSizeOfEventInternalStatusOfPCConfig()                                            Dem_Cfg_GetSizeOfEventTableOfPCConfig()  /**< the number of accomplishable value elements in Dem_Cfg_EventInternalStatus */
/** 
  \}
*/ 

/** 
  \defgroup  Dem_CfgPCGetDataMacros  Dem_Cfg Get Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read CONST and VAR data.
  \{
*/ 
#define Dem_Cfg_GetAdminData()                                                                      ((*(Dem_Cfg_GetAdminDataOfPCConfig())))
#define Dem_Cfg_GetAgingData()                                                                      (NULL_PTR)
#define Dem_Cfg_GetCallbackClearEventAllowed(Index)                                                 (Dem_Cfg_GetCallbackClearEventAllowedOfPCConfig()[(Index)])
#define Dem_Cfg_GetCallbackDtcStatusChanged(Index)                                                  (NULL_PTR)
#define Dem_Cfg_GetCallbackGetFdc(Index)                                                            (NULL_PTR)
#define Dem_Cfg_GetCallbackJ1939DtcStatusChanged(Index)                                             (NULL_PTR)
#define Dem_Cfg_GetClearDTCTable(Index)                                                             (Dem_Cfg_GetClearDTCTableOfPCConfig()[(Index)])
#define Dem_Cfg_GetClearDtcNotificationFinishTable(Index)                                           (NULL_PTR)
#define Dem_Cfg_GetClearDtcNotificationStartTable(Index)                                            (NULL_PTR)
#define Dem_Cfg_GetNmNodeIdOfClientTable(Index)                                                     (NULL_PTR)
#define Dem_Cfg_GetCommitBuffer()                                                                   ((*(Dem_Cfg_GetCommitBufferOfPCConfig())))
#define Dem_Cfg_GetCycleCounterData()                                                               (NULL_PTR)
#define Dem_Cfg_GetMaskedBitsOfCycleIdTable(Index)                                                  (Dem_Cfg_GetCycleIdTableOfPCConfig()[(Index)].MaskedBitsOfCycleIdTable)
#define Dem_Cfg_GetOpCycleTypeOfCycleIdTable(Index)                                                 (Dem_Cfg_GetCycleIdTableOfPCConfig()[(Index)].OpCycleTypeOfCycleIdTable)
#define Dem_Cfg_GetDTCSelectorTable(Index)                                                          (Dem_Cfg_GetDTCSelectorTableOfPCConfig()[(Index)])
#define Dem_Cfg_GetCollectionSizeOfDataCollectionTable(Index)                                       (Dem_Cfg_GetDataCollectionTableOfPCConfig()[(Index)].CollectionSizeOfDataCollectionTable)
#define Dem_Cfg_GetDataElementTableCol2ElmtIndEndIdxOfDataCollectionTable(Index)                    (Dem_Cfg_GetDataCollectionTableOfPCConfig()[(Index)].DataElementTableCol2ElmtIndEndIdxOfDataCollectionTable)
#define Dem_Cfg_GetDataElementTableCol2ElmtIndStartIdxOfDataCollectionTable(Index)                  (Dem_Cfg_GetDataCollectionTableOfPCConfig()[(Index)].DataElementTableCol2ElmtIndStartIdxOfDataCollectionTable)
#define Dem_Cfg_GetDidOffsetFastOfDataCollectionTable(Index)                                        (0u)
#define Dem_Cfg_GetDidOffsetNormalOfDataCollectionTable(Index)                                      (0u)
#define Dem_Cfg_GetEventTable_ERec2EventIdIndEndIdxOfDataCollectionTable(Index)                     (0u)
#define Dem_Cfg_GetEventTable_ERec2EventIdIndStartIdxOfDataCollectionTable(Index)                   (0u)
#define Dem_Cfg_IsEventTable_ERec2EventIdIndUsedOfDataCollectionTable(Index)                        ((FALSE) != FALSE)
#define Dem_Cfg_GetIdNumberOfDataCollectionTable(Index)                                             (Dem_Cfg_GetDataCollectionTableOfPCConfig()[(Index)].IdNumberOfDataCollectionTable)
#define Dem_Cfg_GetStorageKindOfDataCollectionTable(Index)                                          (Dem_Cfg_GetDataCollectionTableOfPCConfig()[(Index)].StorageKindOfDataCollectionTable)
#define Dem_Cfg_GetDataCollectionTableJ19392CollInd(Index)                                          (0u)
#define Dem_Cfg_GetDataCollectionTablePid2CollInd(Index)                                            (0u)
#define Dem_Cfg_IsDataIsStoredInNVOfDataElementTable(Index)                                         ((Dem_Cfg_GetDataElementTableOfPCConfig()[(Index)].DataIsStoredInNVOfDataElementTable) != FALSE)
#define Dem_Cfg_GetElementKindOfDataElementTable(Index)                                             (Dem_Cfg_GetDataElementTableOfPCConfig()[(Index)].ElementKindOfDataElementTable)
#define Dem_Cfg_GetElementSizeOfDataElementTable(Index)                                             (Dem_Cfg_GetDataElementTableOfPCConfig()[(Index)].ElementSizeOfDataElementTable)
#define Dem_Cfg_GetReadDataFuncOfDataElementTable(Index)                                            (Dem_Cfg_GetDataElementTableOfPCConfig()[(Index)].ReadDataFuncOfDataElementTable)
#define Dem_Cfg_GetDataElementTableCol2ElmtInd(Index)                                               (Dem_Cfg_GetDataElementTableCol2ElmtIndOfPCConfig()[(Index)])
#define Dem_Cfg_GetDebounceData()                                                                   (NULL_PTR)
#define Dem_Cfg_GetDebounceHiResTable(Index)                                                        (0u)
#define Dem_Cfg_GetDebounceLoResTable(Index)                                                        (0u)
#define Dem_Cfg_GetDecrementStepSizeOfDebounceTable(Index)                                          (Dem_Cfg_GetDebounceTableOfPCConfig()[(Index)].DecrementStepSizeOfDebounceTable)
#define Dem_Cfg_GetEventDebounceAlgorithmOfDebounceTable(Index)                                     (Dem_Cfg_GetDebounceTableOfPCConfig()[(Index)].EventDebounceAlgorithmOfDebounceTable)
#define Dem_Cfg_GetFailedThresholdOfDebounceTable(Index)                                            (Dem_Cfg_GetDebounceTableOfPCConfig()[(Index)].FailedThresholdOfDebounceTable)
#define Dem_Cfg_GetIncrementStepSizeOfDebounceTable(Index)                                          (Dem_Cfg_GetDebounceTableOfPCConfig()[(Index)].IncrementStepSizeOfDebounceTable)
#define Dem_Cfg_GetMaskedBitsOfDebounceTable(Index)                                                 (Dem_Cfg_GetDebounceTableOfPCConfig()[(Index)].MaskedBitsOfDebounceTable)
#define Dem_Cfg_GetPassedThresholdOfDebounceTable(Index)                                            (Dem_Cfg_GetDebounceTableOfPCConfig()[(Index)].PassedThresholdOfDebounceTable)
#define Dem_Cfg_GetPreconfirmedThresholdOfDebounceTable(Index)                                      (0u)
#define Dem_Cfg_GetStorageThresholdOfDebounceTable(Index)                                           (0u)
#define Dem_Cfg_GetStorageTimerCyclesOfDebounceTable(Index)                                         (0)
#define Dem_Cfg_GetGroupMaskOfDtcGroupMask(Index)                                                   (NULL_PTR)
#define Dem_Cfg_GetUdsGroupDtcOfDtcGroupMask(Index)                                                 (0x00u)
#define Dem_Cfg_GetFunctionalUnitOfDtcTable(Index)                                                  (Dem_Cfg_GetDtcTableOfPCConfig()[(Index)].FunctionalUnitOfDtcTable)
#define Dem_Cfg_GetJ1939DtcOfDtcTable(Index)                                                        (0x00u)
#define Dem_Cfg_GetJ1939NodeIdIndEndIdxOfDtcTable(Index)                                            (0u)
#define Dem_Cfg_GetJ1939NodeIdIndStartIdxOfDtcTable(Index)                                          (0u)
#define Dem_Cfg_IsJ1939NodeIdIndUsedOfDtcTable(Index)                                               ((FALSE) != FALSE)
#define Dem_Cfg_GetObdDtcOfDtcTable(Index)                                                          (0x00u)
#define Dem_Cfg_GetUdsDtcOfDtcTable(Index)                                                          (Dem_Cfg_GetDtcTableOfPCConfig()[(Index)].UdsDtcOfDtcTable)
#define Dem_Cfg_GetDtrData()                                                                        (NULL_PTR)
#define Dem_Cfg_GetDtrStatus(Index)                                                                 ()
#define Dem_Cfg_GetDivisorOfDtrTable(Index)                                                         (NULL_PTR)
#define Dem_Cfg_GetEventTableIdxOfDtrTable(Index)                                                   (0u)
#define Dem_Cfg_GetLinearFactorOfDtrTable(Index)                                                    (NULL_PTR)
#define Dem_Cfg_GetOffsetOfDtrTable(Index)                                                          (NULL_PTR)
#define Dem_Cfg_GetUasidOfDtrTable(Index)                                                           (0u)
#define Dem_Cfg_GetUpdateKindOfDtrTable(Index)                                                      (NULL_PTR)
#define Dem_Cfg_GetDtrTableInd(Index)                                                               (0u)
#define Dem_Cfg_IsEnableConditionFulfilled(Index)                                                   ((Dem_Cfg_GetEnableConditionFulfilledOfPCConfig()[(Index)]) != FALSE)
#define Dem_Cfg_GetEnableConditionGroupCounter(Index)                                               (Dem_Cfg_GetEnableConditionGroupCounterOfPCConfig()[(Index)])
#define Dem_Cfg_GetEnableConditionGroupState(Index)                                                 (Dem_Cfg_GetEnableConditionGroupStateOfPCConfig()[(Index)])
#define Dem_Cfg_GetEnableConditionGroupTableInd(Index)                                              (Dem_Cfg_GetEnableConditionGroupTableIndOfPCConfig()[(Index)])
#define Dem_Cfg_IsFulfilledAtInitOfEnableConditionInitTable(Index)                                  ((Dem_Cfg_GetEnableConditionInitTableOfPCConfig()[(Index)].FulfilledAtInitOfEnableConditionInitTable) != FALSE)
#define Dem_Cfg_GetEnableConditionGroupTableIndEndIdxOfEnableConditionTable(Index)                  (Dem_Cfg_GetEnableConditionTableOfPCConfig()[(Index)].EnableConditionGroupTableIndEndIdxOfEnableConditionTable)
#define Dem_Cfg_GetEnableConditionGroupTableIndStartIdxOfEnableConditionTable(Index)                (Dem_Cfg_GetEnableConditionTableOfPCConfig()[(Index)].EnableConditionGroupTableIndStartIdxOfEnableConditionTable)
#define Dem_Cfg_GetEventAvailableData()                                                             (NULL_PTR)
#define Dem_Cfg_GetEventCycleStatus(Index)                                                          (0u)
#define Dem_Cfg_GetEventDataChanged(Index)                                                          (NULL_PTR)
#define Dem_Cfg_GetEventDataCommitNumber(Index)                                                     (Dem_Cfg_GetEventDataCommitNumberOfPCConfig()[(Index)])
#define Dem_Cfg_GetEventDebounceValue(Index)                                                        (Dem_Cfg_GetEventDebounceValueOfPCConfig()[(Index)])
#define Dem_Cfg_GetEventInternalStatus(Index)                                                       (Dem_Cfg_GetEventInternalStatusOfPCConfig()[(Index)])
#define Dem_Cfg_GetEventStatusChanged(Index)                                                        (NULL_PTR)
#define Dem_Cfg_GetAgingCycleCounterThresholdOfEventTable(Index)                                    (Dem_Cfg_GetEventTableOfPCConfig()[(Index)].AgingCycleCounterThresholdOfEventTable)
#define Dem_Cfg_GetAgingCycleIdOfEventTable(Index)                                                  (Dem_Cfg_GetEventTableOfPCConfig()[(Index)].AgingCycleIdOfEventTable)
#define Dem_Cfg_GetCallbackClearEventAllowedIdxOfEventTable(Index)                                  (Dem_Cfg_GetEventTableOfPCConfig()[(Index)].CallbackClearEventAllowedIdxOfEventTable)
#define Dem_Cfg_GetCallbackGetFdcIdxOfEventTable(Index)                                             (0u)
#define Dem_Cfg_GetDebounceTableIdxOfEventTable(Index)                                              (Dem_Cfg_GetEventTableOfPCConfig()[(Index)].DebounceTableIdxOfEventTable)
#define Dem_Cfg_GetDtcTableIdxOfEventTable(Index)                                                   (Dem_Cfg_GetEventTableOfPCConfig()[(Index)].DtcTableIdxOfEventTable)
#define Dem_Cfg_GetDtrTableIndEndIdxOfEventTable(Index)                                             (0u)
#define Dem_Cfg_GetDtrTableIndStartIdxOfEventTable(Index)                                           (0u)
#define Dem_Cfg_IsDtrTableIndUsedOfEventTable(Index)                                                ((FALSE) != FALSE)
#define Dem_Cfg_GetEnableConditionGroupTableIdxOfEventTable(Index)                                  (Dem_Cfg_GetEventTableOfPCConfig()[(Index)].EnableConditionGroupTableIdxOfEventTable)
#define Dem_Cfg_GetEventKindOfEventTable(Index)                                                     (Dem_Cfg_GetEventTableOfPCConfig()[(Index)].EventKindOfEventTable)
#define Dem_Cfg_GetEventPriorityOfEventTable(Index)                                                 (Dem_Cfg_GetEventTableOfPCConfig()[(Index)].EventPriorityOfEventTable)
#define Dem_Cfg_GetFailedCycleCounterIndexOfEventTable(Index)                                       (0u)
#define Dem_Cfg_GetFaultPendingCounterIndexOfEventTable(Index)                                      (0u)
#define Dem_Cfg_GetMaskedBitsOfEventTable(Index)                                                    (Dem_Cfg_GetEventTableOfPCConfig()[(Index)].MaskedBitsOfEventTable)
#define Dem_Cfg_GetSpecialIndicatorTableEndIdxOfEventTable(Index)                                   (0u)
#define Dem_Cfg_GetSpecialIndicatorTableStartIdxOfEventTable(Index)                                 (0u)
#define Dem_Cfg_IsSpecialIndicatorTableUsedOfEventTable(Index)                                      ((FALSE) != FALSE)
#define Dem_Cfg_GetEventTable_ERec2EventIdInd(Index)                                                (0u)
#define Dem_Cfg_GetEventTable_ObdRdyGroup2EventIdInd(Index)                                         (0u)
#define Dem_Cfg_GetExtendedDataRecordIteratorTable(Index)                                           (Dem_Cfg_GetExtendedDataRecordIteratorTableOfPCConfig()[(Index)])
#define Dem_Cfg_GetDataCollectionTableEdr2CollIndEndIdxOfExtendedDataTable(Index)                   (Dem_Cfg_GetExtendedDataTableOfPCConfig()[(Index)].DataCollectionTableEdr2CollIndEndIdxOfExtendedDataTable)
#define Dem_Cfg_GetDataCollectionTableEdr2CollIndStartIdxOfExtendedDataTable(Index)                 (Dem_Cfg_GetExtendedDataTableOfPCConfig()[(Index)].DataCollectionTableEdr2CollIndStartIdxOfExtendedDataTable)
#define Dem_Cfg_GetMaxRecordSizeOfExtendedDataTable(Index)                                          (Dem_Cfg_GetExtendedDataTableOfPCConfig()[(Index)].MaxRecordSizeOfExtendedDataTable)
#define Dem_Cfg_GetFilterInfoTable(Index)                                                           (Dem_Cfg_GetFilterInfoTableOfPCConfig()[(Index)])
#define Dem_Cfg_GetFilterReportedEvents(Index)                                                      (Dem_Cfg_GetFilterReportedEventsOfPCConfig()[(Index)])
#define Dem_Cfg_GetFreezeFrameData()                                                                (NULL_PTR)
#define Dem_Cfg_GetFreezeFrameIteratorTable(Index)                                                  (Dem_Cfg_GetFreezeFrameIteratorTableOfPCConfig()[(Index)])
#define Dem_Cfg_GetDataCollectionTableFfm2CollIndEndIdxOfFreezeFrameTable(Index)                    (Dem_Cfg_GetFreezeFrameTableOfPCConfig()[(Index)].DataCollectionTableFfm2CollIndEndIdxOfFreezeFrameTable)
#define Dem_Cfg_GetDataCollectionTableFfm2CollIndStartIdxOfFreezeFrameTable(Index)                  (Dem_Cfg_GetFreezeFrameTableOfPCConfig()[(Index)].DataCollectionTableFfm2CollIndStartIdxOfFreezeFrameTable)
#define Dem_Cfg_GetRecordSizeUdsOfFreezeFrameTable(Index)                                           (Dem_Cfg_GetFreezeFrameTableOfPCConfig()[(Index)].RecordSizeUdsOfFreezeFrameTable)
#define Dem_Cfg_GetDataCollectionTableJ19392CollIndEndIdxOfGeneralJ1939Table(Index)                 (0u)
#define Dem_Cfg_GetDataCollectionTableJ19392CollIndStartIdxOfGeneralJ1939Table(Index)               (0u)
#define Dem_Cfg_IsDataCollectionTableJ19392CollIndUsedOfGeneralJ1939Table(Index)                    ((FALSE) != FALSE)
#define Dem_Cfg_GetRecordSizeOfGeneralJ1939Table(Index)                                             (0u)
#define Dem_Cfg_GetGlobalIndicatorStates(Index)                                                     ()
#define Dem_Cfg_GetIndicatorBlinking(Index)                                                         ()
#define Dem_Cfg_GetIndicatorContinuous(Index)                                                       ()
#define Dem_Cfg_GetIndicatorFastFlash(Index)                                                        ()
#define Dem_Cfg_GetIndicatorSlowFlash(Index)                                                        ()
#define Dem_Cfg_GetInitMonitorForEvent(Index)                                                       (NULL_PTR)
#define Dem_Cfg_GetInitMonitorsForFunc(Index)                                                       (NULL_PTR)
#define Dem_Cfg_GetJ1939NodeId(Index)                                                               (NULL_PTR)
#define Dem_Cfg_GetJ1939NodeIdInd(Index)                                                            (0u)
#define Dem_Cfg_GetJ1939NodeIndicator(Index)                                                        (0x00u)
#define Dem_Cfg_GetMemoryBlockId(Index)                                                             (Dem_Cfg_GetMemoryBlockIdOfPCConfig()[(Index)])
#define Dem_Cfg_GetMemoryBlockIdToMemoryEntryId(Index)                                              (Dem_Cfg_GetMemoryBlockIdToMemoryEntryIdOfPCConfig()[(Index)])
#define Dem_Cfg_GetMemoryDataPtr(Index)                                                             (Dem_Cfg_GetMemoryDataPtrOfPCConfig()[(Index)])
#define Dem_Cfg_GetMemoryDataSize(Index)                                                            (Dem_Cfg_GetMemoryDataSizeOfPCConfig()[(Index)])
#define Dem_Cfg_GetMemoryEntry(Index)                                                               (Dem_Cfg_GetMemoryEntryOfPCConfig()[(Index)])
#define Dem_Cfg_GetMemoryEntryInit()                                                                ((*(Dem_Cfg_GetMemoryEntryInitOfPCConfig())))
#define Dem_Cfg_GetMemoryStatus(Index)                                                              (Dem_Cfg_GetMemoryStatusOfPCConfig()[(Index)])
#define Dem_Cfg_GetDtrTableIdxOfMidTable(Index)                                                     (0u)
#define Dem_Cfg_GetMidOfMidTable(Index)                                                             (0x00u)
#define Dem_Cfg_GetTidOfMidTable(Index)                                                             (0x00u)
#define Dem_Cfg_GetMirrorData()                                                                     (0u)
#define Dem_Cfg_GetBehaviorOfNormalIndicatorTable(Index)                                            (NULL_PTR)
#define Dem_Cfg_GetIdOfNormalIndicatorTable(Index)                                                  (NULL_PTR)
#define Dem_Cfg_GetObdIumprData()                                                                   (NULL_PTR)
#define Dem_Cfg_IsObdIumprUpdatePending(Index)                                                      ((FALSE) != FALSE)
#define Dem_Cfg_GetPermanentData()                                                                  (NULL_PTR)
#define Dem_Cfg_GetDataCollectionTablePid2CollIndEndIdxOfPidTable(Index)                            (0u)
#define Dem_Cfg_GetDataCollectionTablePid2CollIndStartIdxOfPidTable(Index)                          (0u)
#define Dem_Cfg_IsDataCollectionTablePid2CollIndUsedOfPidTable(Index)                               ((FALSE) != FALSE)
#define Dem_Cfg_GetPrestorage()                                                                     (NULL_PTR)
#define Dem_Cfg_GetPrestorageIndex(Index)                                                           ()
#define Dem_Cfg_GetPrimaryChronology(Index)                                                         (Dem_Cfg_GetPrimaryChronologyOfPCConfig()[(Index)])
#define Dem_Cfg_GetPrimaryEntry_0()                                                                 ((*(Dem_Cfg_GetPrimaryEntry_0OfPCConfig())))
#define Dem_Cfg_GetPrimaryEntry_1()                                                                 ((*(Dem_Cfg_GetPrimaryEntry_1OfPCConfig())))
#define Dem_Cfg_GetPrimaryEntry_2()                                                                 ((*(Dem_Cfg_GetPrimaryEntry_2OfPCConfig())))
#define Dem_Cfg_GetPrimaryEntry_3()                                                                 ((*(Dem_Cfg_GetPrimaryEntry_3OfPCConfig())))
#define Dem_Cfg_GetPrimaryEntry_4()                                                                 ((*(Dem_Cfg_GetPrimaryEntry_4OfPCConfig())))
#define Dem_Cfg_GetPrimaryEntry_5()                                                                 ((*(Dem_Cfg_GetPrimaryEntry_5OfPCConfig())))
#define Dem_Cfg_GetPrimaryEntry_6()                                                                 ((*(Dem_Cfg_GetPrimaryEntry_6OfPCConfig())))
#define Dem_Cfg_GetPrimaryEntry_7()                                                                 ((*(Dem_Cfg_GetPrimaryEntry_7OfPCConfig())))
#define Dem_Cfg_GetEventTable_ObdRdyGroup2EventIdIndEndIdxOfReadinessGroupTable(Index)              (0u)
#define Dem_Cfg_GetEventTable_ObdRdyGroup2EventIdIndStartIdxOfReadinessGroupTable(Index)            (0u)
#define Dem_Cfg_IsEventTable_ObdRdyGroup2EventIdIndUsedOfReadinessGroupTable(Index)                 ((FALSE) != FALSE)
#define Dem_Cfg_GetReadoutBuffer(Index)                                                             (Dem_Cfg_GetReadoutBufferOfPCConfig()[(Index)])
#define Dem_Cfg_GetReportedEventsOfFilter(Index)                                                    (Dem_Cfg_GetReportedEventsOfFilterOfPCConfig()[(Index)])
#define Dem_Cfg_GetDebounceLoResTimerOfSatelliteInfo(Index)                                         (NULL_PTR)
#define Dem_Cfg_GetMaxDebounceValuesOfSatelliteInfo(Index)                                          (NULL_PTR)
#define Dem_Cfg_GetSatelliteExtendedDataOfSatelliteInfo(Index)                                      (NULL_PTR)
#define Dem_Cfg_GetSatelliteInfo0()                                                                 ((*(Dem_Cfg_GetSatelliteInfo0OfPCConfig())))
#define Dem_Cfg_GetDebounceHiResTableEndIdxOfSatelliteTimeDebounceInfo(Index)                       (0u)
#define Dem_Cfg_GetDebounceHiResTableStartIdxOfSatelliteTimeDebounceInfo(Index)                     (0u)
#define Dem_Cfg_IsDebounceHiResTableUsedOfSatelliteTimeDebounceInfo(Index)                          ((FALSE) != FALSE)
#define Dem_Cfg_GetDebounceLoResTableEndIdxOfSatelliteTimeDebounceInfo(Index)                       (0u)
#define Dem_Cfg_GetDebounceLoResTableStartIdxOfSatelliteTimeDebounceInfo(Index)                     (0u)
#define Dem_Cfg_IsDebounceLoResTableUsedOfSatelliteTimeDebounceInfo(Index)                          ((FALSE) != FALSE)
#define Dem_Cfg_GetSecondaryChronology(Index)                                                       ()
#define Dem_Cfg_GetBehaviorOfSpecialIndicatorTable(Index)                                           (NULL_PTR)
#define Dem_Cfg_GetIdOfSpecialIndicatorTable(Index)                                                 (NULL_PTR)
#define Dem_Cfg_GetStatusData()                                                                     ((*(Dem_Cfg_GetStatusDataOfPCConfig())))
#define Dem_Cfg_IsStorageConditionFulfilled(Index)                                                  ((FALSE) != FALSE)
#define Dem_Cfg_GetStorageConditionGroupCounter(Index)                                              (0u)
#define Dem_Cfg_GetIndexOfStorageConditionGroupTable(Index)                                         (0u)
#define Dem_Cfg_GetStorageConditionGroupTableInd(Index)                                             (0u)
#define Dem_Cfg_IsFulfilledAtInitOfStorageConditionInitTable(Index)                                 ((FALSE) != FALSE)
#define Dem_Cfg_GetStorageConditionGroupTableIndEndIdxOfStorageConditionTable(Index)                (0u)
#define Dem_Cfg_GetStorageConditionGroupTableIndStartIdxOfStorageConditionTable(Index)              (0u)
#define Dem_Cfg_IsStorageConditionGroupTableIndUsedOfStorageConditionTable(Index)                   ((FALSE) != FALSE)
#define Dem_Cfg_GetStartIdxMidTableOfSupportedMidsTable(Index)                                      (0u)
#define Dem_Cfg_GetSupportedMidMaskOfSupportedMidsTable(Index)                                      (0x00u)
#define Dem_Cfg_GetTimeSeriesChronology(Index)                                                      ()
#define Dem_Cfg_GetTimeSeriesEntryInit()                                                            ((*(Dem_Cfg_GetTimeSeriesEntryInitOfPCConfig())))
/** 
  \}
*/ 

/** 
  \defgroup  Dem_CfgPCGetBitDataMacros  Dem_Cfg Get Bit Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read bitcoded data elements.
  \{
*/ 
#define Dem_Cfg_IsJumpUpOfDebounceTable(Index)                                                      (DEM_CFG_JUMPUPOFDEBOUNCETABLE_MASK == (Dem_Cfg_GetMaskedBitsOfDebounceTable(Index) & DEM_CFG_JUMPUPOFDEBOUNCETABLE_MASK))  /**< DemDebounceCounterJumpUp of the DemEventParameter/DemEventClass/DemDebounceAlgorithmClass/DemDebounceCounterBased */
/** 
  \}
*/ 

/** 
  \defgroup  Dem_CfgPCGetDeduplicatedDataMacros  Dem_Cfg Get Deduplicated Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated data elements.
  \{
*/ 
#define Dem_Cfg_GetClearDTCIndexOfClientTable(Index)                                                0u  /**< 'DEM_CFG_CLEARDTC_INVALID'(=255): no ClearDTC for the Client, else: index in Dem_Cfg_ClearDTCTable[] */
#define Dem_Cfg_GetFilterIndexOfClientTable(Index)                                                  0u  /**< 'DEM_CFG_FILTER_INVALID'(=255): no filter for the Client, else: index in Dem_Cfg_FilterInfoTable[] */
#define Dem_Cfg_GetFreezeFrameIteratorIndexOfClientTable(Index)                                     0u  /**< 'DEM_CFG_FREEZEFRAMEITERATOR_INVALID'(=255): no FreezeFrameIterator for the Client, else: index in Dem_Cfg_FreezeFrameIteratorTable[] */
#define Dem_Cfg_GetReadoutBufferIndexOfClientTable(Index)                                           0u  /**< 'DEM_CFG_READOUTBUFFER_INVALID'(=255): no ReadoutBuffer for the Client, else: index in Dem_Cfg_ReadoutBuffer[] */
#define Dem_Cfg_GetSelectorIndexOfClientTable(Index)                                                0u  /**< 'DEM_CFG_DTCSELECTOR_INVALID'(=255): no selector for the Client, else: index in Dem_Cfg_DTCSelectorTable[] */
#define Dem_Cfg_GetConfigurationId()                                                                Dem_Cfg_GetConfigurationIdOfPCConfig()
#define Dem_Cfg_IsUsedForAgingOfCycleIdTable(Index)                                                 (((boolean)(Dem_Cfg_GetMaskedBitsOfCycleIdTable(Index) == 0x01u)) != FALSE)  /**< DemOperationCycle is target of any DemEventParameter/DemEventClass/DemAgingCycleRef */
#define Dem_Cfg_IsDataElementTableCol2ElmtIndUsedOfDataCollectionTable(Index)                       (((boolean)(Dem_Cfg_GetDataElementTableCol2ElmtIndStartIdxOfDataCollectionTable(Index) != DEM_CFG_NO_DATAELEMENTTABLECOL2ELMTINDSTARTIDXOFDATACOLLECTIONTABLE)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to Dem_Cfg_DataElementTableCol2ElmtInd */
#define Dem_Cfg_GetTriggerOfDataCollectionTable(Index)                                              DEM_CFG_TRIGGER_NONE  /**< Trigger for storage and update of extended data records */
#define Dem_Cfg_IsUpdateOfDataCollectionTable(Index)                                                (((boolean)(Dem_Cfg_GetDataElementTableCol2ElmtIndEndIdxOfDataCollectionTable(Index) < 7u)) != FALSE)
#define Dem_Cfg_GetDataCollectionTableEdr2CollInd(Index)                                            ((Dem_Cfg_DataCollectionTableEdr2CollIndType)((((Dem_Cfg_DataCollectionTableEdr2CollIndType)(Index)) + 1u)))  /**< the indexes of the 1:1 sorted relation pointing to Dem_Cfg_DataCollectionTable */
#define Dem_Cfg_GetDataCollectionTableErec2CollInd(Index)                                           ((Dem_Cfg_DataCollectionTableErec2CollIndType)((((Dem_Cfg_DataCollectionTableErec2CollIndType)(Index)) + 1u)))  /**< the indexes of the 1:1 sorted relation pointing to Dem_Cfg_DataCollectionTable */
#define Dem_Cfg_GetDataCollectionTableFfm2CollInd(Index)                                            ((Dem_Cfg_DataCollectionTableFfm2CollIndType)((((Dem_Cfg_DataCollectionTableFfm2CollIndType)(Index)) + 3u)))  /**< the indexes of the 1:1 sorted relation pointing to Dem_Cfg_DataCollectionTable */
#define Dem_Cfg_IsDebounceContinuousOfDebounceTable(Index)                                          (((FALSE)) != FALSE)  /**< DemDebounceContinuous of the DemEventParameter/DemEventClass/DemDebounceAlgorithmClass/DemDebounceCounterBased and ~/DemDebounceTimeBase */
#define Dem_Cfg_IsEventDebounceBehaviorOfDebounceTable(Index)                                       (((boolean)(Dem_Cfg_GetMaskedBitsOfDebounceTable(Index) == 0x0Eu)) != FALSE)  /**< DemEventParameter/DemEventClass/DemDebounceAlgorithmClass/[algorithm]/DemDebounceBehavior == DEM_DEBOUNCE_RESET */
#define Dem_Cfg_GetFailTimerCyclesOfDebounceTable(Index)                                            0  /**< HiRes- or LoRes-Timer ticks for DemDebounceTimeFailedThreshold of the DemEventParameter/DemEventClass/DemDebounceAlgorithmClass/DemDebounceTimeBase */
#define Dem_Cfg_IsJumpDownOfDebounceTable(Index)                                                    Dem_Cfg_IsJumpUpOfDebounceTable(Index)  /**< DemDebounceCounterJumpDown of the DemEventParameter/DemEventClass/DemDebounceAlgorithmClass/DemDebounceCounterBase */
#define Dem_Cfg_GetJumpDownValueOfDebounceTable(Index)                                              0  /**< DemDebounceCounterJumpDownValue of the DemEventParameter/DemEventClass/DemDebounceAlgorithmClass/DemDebounceCounterBased */
#define Dem_Cfg_GetJumpUpValueOfDebounceTable(Index)                                                0  /**< DemDebounceCounterJumpUpValue of the DemEventParameter/DemEventClass/DemDebounceAlgorithmClass/DemDebounceCounterBased */
#define Dem_Cfg_GetPassTimerCyclesOfDebounceTable(Index)                                            0  /**< HiRes- or LoRes-Timer ticks for DemDebounceTimePassedThreshold of the DemEventParameter/DemEventClass/DemDebounceAlgorithmClass/DemDebounceTimeBase */
#define Dem_Cfg_IsStorageOfDebounceTable(Index)                                                     (((FALSE)) != FALSE)  /**< DemDebounceCounterStorage of the DemEventParameter/DemEventClass/DemDebounceAlgorithmClass/DemDebounceCounterBased */
#define Dem_Cfg_GetDtcSeverityOfDtcTable(Index)                                                     0u
#define Dem_Cfg_IsImmediateNvStorageOfDtcTable(Index)                                               (((FALSE)) != FALSE)
#define Dem_Cfg_GetIndexOfEnableConditionGroupTable(Index)                                          ((Dem_Cfg_IndexOfEnableConditionGroupTableType)((Index)))  /**< Dummy - contains always the index of this element (self) */
#define Dem_Cfg_IsEnableConditionGroupTableIndUsedOfEnableConditionTable(Index)                     (((TRUE)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to Dem_Cfg_EnableConditionGroupTableInd */
#define Dem_Cfg_IsEventAvailableDefault(Index)                                                      (((TRUE)) != FALSE)
#define Dem_Cfg_IsEventAvailableInVariant(Index)                                                    (((TRUE)) != FALSE)
#define Dem_Cfg_IsAgingAllowedOfEventTable(Index)                                                   (((boolean)(Dem_Cfg_GetAgingCycleCounterThresholdOfEventTable(Index) == 40u)) != FALSE)  /**< DemAgingAllowed of the DemEventParameter/DemEventClass */
#define Dem_Cfg_IsCallbackClearEventAllowedUsedOfEventTable(Index)                                  (((TRUE)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to Dem_Cfg_CallbackClearEventAllowed */
#define Dem_Cfg_GetEventDestinationOfEventTable(Index)                                              DEM_CFG_MEMORYID_PRIMARY  /**< DemEventDestination of the DemEventParameter/DemEventClass */
#define Dem_Cfg_GetEventFailureCycleCounterThresholdOfEventTable(Index)                             1u  /**< DemEventFailureCycleCounterThreshold of the DemEventParameter/DemEventClass, '0': is also default for unset parameter */
#define Dem_Cfg_IsEventLatchTFOfEventTable(Index)                                                   (((FALSE)) != FALSE)  /**< DemOBDVisibilityDelayedUntilDcyQualification of the DemEventParameter */
#define Dem_Cfg_GetEventSignificanceOfEventTable(Index)                                             DEM_CFG_DEM_EVENT_SIGNIFICANCE_FAULT_EVENTSIGNIFICANCEOFEVENTTABLE  /**< DemEventSignificance of the DemEventParameter/DemEventClass */
#define Dem_Cfg_GetExtendedDataTableIdxOfEventTable(Index)                                          1u  /**< the index of the 1:1 relation pointing to Dem_Cfg_ExtendedDataTable */
#define Dem_Cfg_GetFreezeFrameNumTableEndIdxOfEventTable(Index)                                     1u  /**< the end index of the 0:n relation pointing to Dem_Cfg_FreezeFrameNumTable */
#define Dem_Cfg_GetFreezeFrameNumTableStartIdxOfEventTable(Index)                                   0u  /**< the start index of the 0:n relation pointing to Dem_Cfg_FreezeFrameNumTable */
#define Dem_Cfg_IsFreezeFrameNumTableUsedOfEventTable(Index)                                        (((TRUE)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to Dem_Cfg_FreezeFrameNumTable */
#define Dem_Cfg_GetFreezeFrameTableStdFFIdxOfEventTable(Index)                                      1u  /**< the index of the 1:1 relation pointing to Dem_Cfg_FreezeFrameTable */
#define Dem_Cfg_GetHealingTargetOfEventTable(Index)                                                 0u  /**< DemIndicatorHealingCycleCounterThreshold of the DemEventParameter/DemEventClass/DemIndicatorAttribute (for each event all attribute's value must be identical). Events without DemIndicatorAttribute have: 0. */
#define Dem_Cfg_IsOBDVisibilityDelayedUntilDcyQualificationOfEventTable(Index)                      (((TRUE)) != FALSE)
#define Dem_Cfg_GetOperationCycleIdOfEventTable(Index)                                              DemConf_DemOperationCycle_PowerCycle  /**< DemOperationCycle (ID) referenced by DemEventParameter/DemEventClass/DemOperationCycleRef */
#define Dem_Cfg_GetSatelliteEventIdxOfEventTable(Index)                                             ((Dem_Cfg_SatelliteEventIdxOfEventTableType)((Index)))  /**< Index of this event in the satellite's RAM buffers Dem_Cfg_SatelliteInfoNN.SatelliteData[] and Dem_Cfg_SatelliteInfoNN.SatelliteExtendedData[]. */
#define Dem_Cfg_GetSatelliteInfoIdxOfEventTable(Index)                                              0u  /**< the index of the 1:1 relation pointing to Dem_Cfg_SatelliteInfo */
#define Dem_Cfg_GetEventTableInd(Index)                                                             ((Dem_Cfg_EventTableIndType)((Index)))  /**< the indexes of the 1:1 sorted relation pointing to Dem_Cfg_EventTable */
#define Dem_Cfg_GetDataCollectionTableErec2CollIndEndIdxOfExtendedDataRecordTable(Index)            2u  /**< the end index of the 0:n relation pointing to Dem_Cfg_DataCollectionTableErec2CollInd */
#define Dem_Cfg_GetDataCollectionTableErec2CollIndStartIdxOfExtendedDataRecordTable(Index)          0u  /**< the start index of the 0:n relation pointing to Dem_Cfg_DataCollectionTableErec2CollInd */
#define Dem_Cfg_IsDataCollectionTableErec2CollIndUsedOfExtendedDataRecordTable(Index)               (((TRUE)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to Dem_Cfg_DataCollectionTableErec2CollInd */
#define Dem_Cfg_IsDataCollectionTableEdr2CollIndUsedOfExtendedDataTable(Index)                      (((boolean)(Dem_Cfg_GetDataCollectionTableEdr2CollIndStartIdxOfExtendedDataTable(Index) != DEM_CFG_NO_DATACOLLECTIONTABLEEDR2COLLINDSTARTIDXOFEXTENDEDDATATABLE)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to Dem_Cfg_DataCollectionTableEdr2CollInd */
#define Dem_Cfg_GetFinalMagicNumber(ConfigDataPtr)                                                  Dem_Cfg_GetFinalMagicNumberOfPCConfig(ConfigDataPtr)
#define Dem_Cfg_GetFFNumberOfFreezeFrameNumTable(Index)                                             1u
#define Dem_Cfg_GetFFTriggerOfFreezeFrameNumTable(Index)                                            DEM_CFG_TRIGGER_CONFIRMED
#define Dem_Cfg_IsFFUpdateOfFreezeFrameNumTable(Index)                                              (((FALSE)) != FALSE)
#define Dem_Cfg_IsDataCollectionTableFfm2CollIndUsedOfFreezeFrameTable(Index)                       (((boolean)(Dem_Cfg_GetDataCollectionTableFfm2CollIndStartIdxOfFreezeFrameTable(Index) != DEM_CFG_NO_DATACOLLECTIONTABLEFFM2COLLINDSTARTIDXOFFREEZEFRAMETABLE)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to Dem_Cfg_DataCollectionTableFfm2CollInd */
#define Dem_Cfg_GetRecordSizeOfFreezeFrameTable(Index)                                              0u  /**< Summarized size of did data that is stored in Dem_Cfg_PrimaryEntryType.SnapshotData[][] (i.e. typically without size of dids containing internal data elements). */
#define Dem_Cfg_GetRecordSizeUdsOfFastRateTimeSeriesPowertrainOfFreezeFrameTable(Index)             0u  /**< Summarized size of did data, did numbers of all configured fast rate samples for time series powertrain and snapshot header (i.e. dynamical payload size of the uds response message). */
#define Dem_Cfg_GetRecordSizeUdsOfNormalRateTimeSeriesPowertrainOfFreezeFrameTable(Index)           0u  /**< Summarized size of did data, did numbers of all configured normal rate samples for time series powertrain and snapshot header (i.e. dynamical payload size of the uds response message). */
#define Dem_Cfg_GetDataElementTableIdxOfGeneralObdInput(Index)                                      0u  /**< the index of the 1:1 relation pointing to Dem_Cfg_DataElementTable */
#define Dem_Cfg_GetGlobalObdRequirements()                                                          Dem_Cfg_GetGlobalObdRequirementsOfPCConfig()
#define Dem_Cfg_GetGlobalSeverityMask()                                                             Dem_Cfg_GetGlobalSeverityMaskOfPCConfig()
#define Dem_Cfg_GetInitDataHashCode(ConfigDataPtr)                                                  Dem_Cfg_GetInitDataHashCodeOfPCConfig(ConfigDataPtr)
#define Dem_Cfg_GetReadinessGroupOfReadinessGroupTable(Index)                                       DEM_CFG_READINESS_GROUP_INVALID
#define Dem_Cfg_GetApplicationIdOfSatelliteInfo(Index)                                              0  /**< Partition (OsApplication identifier) of the satellite. */
#define Dem_Cfg_GetEventCountOfSatelliteInfo(Index)                                                 16u  /**< Satellite individual size of the monitor/event data RAM buffer */
#define Dem_Cfg_GetEventTableIndEndIdxOfSatelliteInfo(Index)                                        16u  /**< the end index of the 0:n relation pointing to Dem_Cfg_EventTableInd */
#define Dem_Cfg_GetEventTableIndStartIdxOfSatelliteInfo(Index)                                      0u  /**< the start index of the 0:n relation pointing to Dem_Cfg_EventTableInd */
#define Dem_Cfg_IsEventTableIndUsedOfSatelliteInfo(Index)                                           (((TRUE)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to Dem_Cfg_EventTableInd */
#define Dem_Cfg_GetSatelliteDataOfSatelliteInfo(Index)                                              &Dem_Cfg_SatelliteInfo0.SatelliteData[0]  /**< Satellite individual RAM buffer 1 for the monitor/event data */
#define Dem_Cfg_GetSatelliteStatusOfSatelliteInfo(Index)                                            &Dem_Cfg_SatelliteInfo0.SatelliteStatus  /**< Satellite individual RAM buffer for the monitor/event status */
#define Dem_Cfg_GetSizeOfCallbackClearEventAllowed()                                                Dem_Cfg_GetSizeOfCallbackClearEventAllowedOfPCConfig()
#define Dem_Cfg_GetSizeOfCallbackDtcStatusChanged()                                                 Dem_Cfg_GetSizeOfCallbackDtcStatusChangedOfPCConfig()
#define Dem_Cfg_GetSizeOfCallbackGetFdc()                                                           Dem_Cfg_GetSizeOfCallbackGetFdcOfPCConfig()
#define Dem_Cfg_GetSizeOfCallbackJ1939DtcStatusChanged()                                            Dem_Cfg_GetSizeOfCallbackJ1939DtcStatusChangedOfPCConfig()
#define Dem_Cfg_GetSizeOfClearDTCTable()                                                            Dem_Cfg_GetSizeOfClearDTCTableOfPCConfig()
#define Dem_Cfg_GetSizeOfClearDtcNotificationFinishTable()                                          Dem_Cfg_GetSizeOfClearDtcNotificationFinishTableOfPCConfig()
#define Dem_Cfg_GetSizeOfClearDtcNotificationStartTable()                                           Dem_Cfg_GetSizeOfClearDtcNotificationStartTableOfPCConfig()
#define Dem_Cfg_GetSizeOfClientTable()                                                              Dem_Cfg_GetSizeOfClientTableOfPCConfig()
#define Dem_Cfg_GetSizeOfDTCSelectorTable()                                                         Dem_Cfg_GetSizeOfDTCSelectorTableOfPCConfig()
#define Dem_Cfg_GetSizeOfDataElementTable()                                                         Dem_Cfg_GetSizeOfDataElementTableOfPCConfig()
#define Dem_Cfg_GetSizeOfDebounceHiResTable()                                                       Dem_Cfg_GetSizeOfDebounceHiResTableOfPCConfig()
#define Dem_Cfg_GetSizeOfDebounceLoResTable()                                                       Dem_Cfg_GetSizeOfDebounceLoResTableOfPCConfig()
#define Dem_Cfg_GetSizeOfDtcGroupMask()                                                             Dem_Cfg_GetSizeOfDtcGroupMaskOfPCConfig()
#define Dem_Cfg_GetSizeOfDtrStatus()                                                                Dem_Cfg_GetSizeOfDtrStatusOfPCConfig()
#define Dem_Cfg_GetSizeOfDtrTable()                                                                 Dem_Cfg_GetSizeOfDtrTableOfPCConfig()
#define Dem_Cfg_GetSizeOfEnableConditionFulfilled()                                                 Dem_Cfg_GetSizeOfEnableConditionFulfilledOfPCConfig()
#define Dem_Cfg_GetSizeOfEnableConditionGroupCounter()                                              Dem_Cfg_GetSizeOfEnableConditionGroupCounterOfPCConfig()
#define Dem_Cfg_GetSizeOfEnableConditionGroupState()                                                Dem_Cfg_GetSizeOfEnableConditionGroupStateOfPCConfig()
#define Dem_Cfg_GetSizeOfEnableConditionGroupTable()                                                Dem_Cfg_GetSizeOfEnableConditionGroupTableOfPCConfig()
#define Dem_Cfg_GetSizeOfEnableConditionTable()                                                     Dem_Cfg_GetSizeOfEnableConditionTableOfPCConfig()
#define Dem_Cfg_GetSizeOfEventCycleStatus()                                                         Dem_Cfg_GetSizeOfEventCycleStatusOfPCConfig()
#define Dem_Cfg_GetSizeOfEventDataChanged()                                                         Dem_Cfg_GetSizeOfEventDataChangedOfPCConfig()
#define Dem_Cfg_GetSizeOfEventDataCommitNumber()                                                    Dem_Cfg_GetSizeOfEventDataCommitNumberOfPCConfig()
#define Dem_Cfg_GetSizeOfEventDebounceValue()                                                       Dem_Cfg_GetSizeOfEventDebounceValueOfPCConfig()
#define Dem_Cfg_GetSizeOfEventInternalStatus()                                                      Dem_Cfg_GetSizeOfEventInternalStatusOfPCConfig()
#define Dem_Cfg_GetSizeOfEventStatusChanged()                                                       Dem_Cfg_GetSizeOfEventStatusChangedOfPCConfig()
#define Dem_Cfg_GetSizeOfEventTable()                                                               Dem_Cfg_GetSizeOfEventTableOfPCConfig()
#define Dem_Cfg_GetSizeOfExtendedDataRecordIteratorTable()                                          Dem_Cfg_GetSizeOfExtendedDataRecordIteratorTableOfPCConfig()
#define Dem_Cfg_GetSizeOfFilterInfoTable()                                                          Dem_Cfg_GetSizeOfFilterInfoTableOfPCConfig()
#define Dem_Cfg_GetSizeOfFilterReportedEvents()                                                     Dem_Cfg_GetSizeOfFilterReportedEventsOfPCConfig()
#define Dem_Cfg_GetSizeOfFreezeFrameIteratorTable()                                                 Dem_Cfg_GetSizeOfFreezeFrameIteratorTableOfPCConfig()
#define Dem_Cfg_GetSizeOfGlobalIndicatorStates()                                                    Dem_Cfg_GetSizeOfGlobalIndicatorStatesOfPCConfig()
#define Dem_Cfg_GetSizeOfIndicatorBlinking()                                                        Dem_Cfg_GetSizeOfIndicatorBlinkingOfPCConfig()
#define Dem_Cfg_GetSizeOfIndicatorContinuous()                                                      Dem_Cfg_GetSizeOfIndicatorContinuousOfPCConfig()
#define Dem_Cfg_GetSizeOfIndicatorFastFlash()                                                       Dem_Cfg_GetSizeOfIndicatorFastFlashOfPCConfig()
#define Dem_Cfg_GetSizeOfIndicatorSlowFlash()                                                       Dem_Cfg_GetSizeOfIndicatorSlowFlashOfPCConfig()
#define Dem_Cfg_GetSizeOfInitMonitorForEvent()                                                      Dem_Cfg_GetSizeOfInitMonitorForEventOfPCConfig()
#define Dem_Cfg_GetSizeOfInitMonitorsForFunc()                                                      Dem_Cfg_GetSizeOfInitMonitorsForFuncOfPCConfig()
#define Dem_Cfg_GetSizeOfMemoryBlockIdToMemoryEntryId()                                             Dem_Cfg_GetSizeOfMemoryBlockIdToMemoryEntryIdOfPCConfig()
#define Dem_Cfg_GetSizeOfMemoryEntry()                                                              Dem_Cfg_GetSizeOfMemoryEntryOfPCConfig()
#define Dem_Cfg_GetSizeOfMemoryStatus()                                                             Dem_Cfg_GetSizeOfMemoryStatusOfPCConfig()
#define Dem_Cfg_GetSizeOfObdIumprUpdatePending()                                                    Dem_Cfg_GetSizeOfObdIumprUpdatePendingOfPCConfig()
#define Dem_Cfg_GetSizeOfPrestorageIndex()                                                          Dem_Cfg_GetSizeOfPrestorageIndexOfPCConfig()
#define Dem_Cfg_GetSizeOfPrimaryChronology()                                                        Dem_Cfg_GetSizeOfPrimaryChronologyOfPCConfig()
#define Dem_Cfg_GetSizeOfReadinessGroupTable()                                                      Dem_Cfg_GetSizeOfReadinessGroupTableOfPCConfig()
#define Dem_Cfg_GetSizeOfReadoutBuffer()                                                            Dem_Cfg_GetSizeOfReadoutBufferOfPCConfig()
#define Dem_Cfg_GetSizeOfReportedEventsOfFilter()                                                   Dem_Cfg_GetSizeOfReportedEventsOfFilterOfPCConfig()
#define Dem_Cfg_GetSizeOfSatelliteInfo()                                                            Dem_Cfg_GetSizeOfSatelliteInfoOfPCConfig()
#define Dem_Cfg_GetSizeOfSecondaryChronology()                                                      Dem_Cfg_GetSizeOfSecondaryChronologyOfPCConfig()
#define Dem_Cfg_GetSizeOfSpecialIndicatorTable()                                                    Dem_Cfg_GetSizeOfSpecialIndicatorTableOfPCConfig()
#define Dem_Cfg_GetSizeOfStartIdx500miDenRatioTable()                                               Dem_Cfg_GetSizeOfStartIdx500miDenRatioTableOfPCConfig()
#define Dem_Cfg_GetSizeOfStorageConditionFulfilled()                                                Dem_Cfg_GetSizeOfStorageConditionFulfilledOfPCConfig()
#define Dem_Cfg_GetSizeOfStorageConditionGroupCounter()                                             Dem_Cfg_GetSizeOfStorageConditionGroupCounterOfPCConfig()
#define Dem_Cfg_GetSizeOfStorageConditionGroupTable()                                               Dem_Cfg_GetSizeOfStorageConditionGroupTableOfPCConfig()
#define Dem_Cfg_GetSizeOfStorageConditionTable()                                                    Dem_Cfg_GetSizeOfStorageConditionTableOfPCConfig()
#define Dem_Cfg_GetSizeOfSupportedMidsTable()                                                       Dem_Cfg_GetSizeOfSupportedMidsTableOfPCConfig()
#define Dem_Cfg_GetSizeOfTimeSeriesChronology()                                                     Dem_Cfg_GetSizeOfTimeSeriesChronologyOfPCConfig()
#define Dem_Cfg_IsUseOBDIIInVariant()                                                               Dem_Cfg_IsUseOBDIIInVariantOfPCConfig()
#define Dem_Cfg_IsUsePermanentInVariant()                                                           Dem_Cfg_IsUsePermanentInVariantOfPCConfig()
#define Dem_Cfg_IsUseWWHOBDInVariant()                                                              Dem_Cfg_IsUseWWHOBDInVariantOfPCConfig()
/** 
  \}
*/ 

/** 
  \defgroup  Dem_CfgPCSetDataMacros  Dem_Cfg Set Data Macros (PRE_COMPILE)
  \brief  These macros can be used to write data.
  \{
*/ 
#define Dem_Cfg_SetAdminData(Value)                                                                 (*(Dem_Cfg_GetAdminDataOfPCConfig())) = (Value)
#define Dem_Cfg_SetAgingData(Value)                                                                 
#define Dem_Cfg_SetClearDTCTable(Index, Value)                                                      Dem_Cfg_GetClearDTCTableOfPCConfig()[(Index)] = (Value)
#define Dem_Cfg_SetCommitBuffer(Value)                                                              (*(Dem_Cfg_GetCommitBufferOfPCConfig())) = (Value)
#define Dem_Cfg_SetCycleCounterData(Value)                                                          
#define Dem_Cfg_SetDTCSelectorTable(Index, Value)                                                   Dem_Cfg_GetDTCSelectorTableOfPCConfig()[(Index)] = (Value)
#define Dem_Cfg_SetDebounceData(Value)                                                              
#define Dem_Cfg_SetDtrData(Value)                                                                   
#define Dem_Cfg_SetDtrStatus(Index, Value)                                                          
#define Dem_Cfg_SetEnableConditionFulfilled(Index, Value)                                           Dem_Cfg_GetEnableConditionFulfilledOfPCConfig()[(Index)] = (Value)
#define Dem_Cfg_SetEnableConditionGroupCounter(Index, Value)                                        Dem_Cfg_GetEnableConditionGroupCounterOfPCConfig()[(Index)] = (Value)
#define Dem_Cfg_SetEnableConditionGroupState(Index, Value)                                          Dem_Cfg_GetEnableConditionGroupStateOfPCConfig()[(Index)] = (Value)
#define Dem_Cfg_SetEventAvailableData(Value)                                                        
#define Dem_Cfg_SetEventCycleStatus(Index, Value)                                                   
#define Dem_Cfg_SetEventDataCommitNumber(Index, Value)                                              Dem_Cfg_GetEventDataCommitNumberOfPCConfig()[(Index)] = (Value)
#define Dem_Cfg_SetEventDebounceValue(Index, Value)                                                 Dem_Cfg_GetEventDebounceValueOfPCConfig()[(Index)] = (Value)
#define Dem_Cfg_SetEventInternalStatus(Index, Value)                                                Dem_Cfg_GetEventInternalStatusOfPCConfig()[(Index)] = (Value)
#define Dem_Cfg_SetExtendedDataRecordIteratorTable(Index, Value)                                    Dem_Cfg_GetExtendedDataRecordIteratorTableOfPCConfig()[(Index)] = (Value)
#define Dem_Cfg_SetFilterInfoTable(Index, Value)                                                    Dem_Cfg_GetFilterInfoTableOfPCConfig()[(Index)] = (Value)
#define Dem_Cfg_SetFilterReportedEvents(Index, Value)                                               Dem_Cfg_GetFilterReportedEventsOfPCConfig()[(Index)] = (Value)
#define Dem_Cfg_SetFreezeFrameData(Value)                                                           
#define Dem_Cfg_SetFreezeFrameIteratorTable(Index, Value)                                           Dem_Cfg_GetFreezeFrameIteratorTableOfPCConfig()[(Index)] = (Value)
#define Dem_Cfg_SetGlobalIndicatorStates(Index, Value)                                              
#define Dem_Cfg_SetIndicatorBlinking(Index, Value)                                                  
#define Dem_Cfg_SetIndicatorContinuous(Index, Value)                                                
#define Dem_Cfg_SetIndicatorFastFlash(Index, Value)                                                 
#define Dem_Cfg_SetIndicatorSlowFlash(Index, Value)                                                 
#define Dem_Cfg_SetMemoryStatus(Index, Value)                                                       Dem_Cfg_GetMemoryStatusOfPCConfig()[(Index)] = (Value)
#define Dem_Cfg_SetMirrorData(Value)                                                                
#define Dem_Cfg_SetObdIumprData(Value)                                                              
#define Dem_Cfg_SetObdIumprUpdatePending(Index, Value)                                              
#define Dem_Cfg_SetPermanentData(Value)                                                             
#define Dem_Cfg_SetPrestorage(Value)                                                                
#define Dem_Cfg_SetPrestorageIndex(Index, Value)                                                    
#define Dem_Cfg_SetPrimaryChronology(Index, Value)                                                  Dem_Cfg_GetPrimaryChronologyOfPCConfig()[(Index)] = (Value)
#define Dem_Cfg_SetPrimaryEntry_0(Value)                                                            (*(Dem_Cfg_GetPrimaryEntry_0OfPCConfig())) = (Value)
#define Dem_Cfg_SetPrimaryEntry_1(Value)                                                            (*(Dem_Cfg_GetPrimaryEntry_1OfPCConfig())) = (Value)
#define Dem_Cfg_SetPrimaryEntry_2(Value)                                                            (*(Dem_Cfg_GetPrimaryEntry_2OfPCConfig())) = (Value)
#define Dem_Cfg_SetPrimaryEntry_3(Value)                                                            (*(Dem_Cfg_GetPrimaryEntry_3OfPCConfig())) = (Value)
#define Dem_Cfg_SetPrimaryEntry_4(Value)                                                            (*(Dem_Cfg_GetPrimaryEntry_4OfPCConfig())) = (Value)
#define Dem_Cfg_SetPrimaryEntry_5(Value)                                                            (*(Dem_Cfg_GetPrimaryEntry_5OfPCConfig())) = (Value)
#define Dem_Cfg_SetPrimaryEntry_6(Value)                                                            (*(Dem_Cfg_GetPrimaryEntry_6OfPCConfig())) = (Value)
#define Dem_Cfg_SetPrimaryEntry_7(Value)                                                            (*(Dem_Cfg_GetPrimaryEntry_7OfPCConfig())) = (Value)
#define Dem_Cfg_SetReadoutBuffer(Index, Value)                                                      Dem_Cfg_GetReadoutBufferOfPCConfig()[(Index)] = (Value)
#define Dem_Cfg_SetReportedEventsOfFilter(Index, Value)                                             Dem_Cfg_GetReportedEventsOfFilterOfPCConfig()[(Index)] = (Value)
#define Dem_Cfg_SetSatelliteInfo0(Value)                                                            (*(Dem_Cfg_GetSatelliteInfo0OfPCConfig())) = (Value)
#define Dem_Cfg_SetSecondaryChronology(Index, Value)                                                
#define Dem_Cfg_SetStatusData(Value)                                                                (*(Dem_Cfg_GetStatusDataOfPCConfig())) = (Value)
#define Dem_Cfg_SetStorageConditionFulfilled(Index, Value)                                          
#define Dem_Cfg_SetStorageConditionGroupCounter(Index, Value)                                       
#define Dem_Cfg_SetTimeSeriesChronology(Index, Value)                                               
/** 
  \}
*/ 

/** 
  \defgroup  Dem_CfgPCGetAddressOfDataMacros  Dem_Cfg Get Address Of Data Macros (PRE_COMPILE)
  \brief  These macros can be used to get the data by the address operator.
  \{
*/ 
#define Dem_Cfg_GetAddrAdminData()                                                                  (&Dem_Cfg_GetAdminData())
#define Dem_Cfg_GetAddrAgingData()                                                                  (&Dem_Cfg_GetAgingData())
#define Dem_Cfg_GetAddrCallbackClearEventAllowed(Index)                                             (&Dem_Cfg_GetCallbackClearEventAllowed(Index))
#define Dem_Cfg_GetAddrCallbackDtcStatusChanged(Index)                                              (&Dem_Cfg_GetCallbackDtcStatusChanged(Index))
#define Dem_Cfg_GetAddrCallbackGetFdc(Index)                                                        (&Dem_Cfg_GetCallbackGetFdc(Index))
#define Dem_Cfg_GetAddrCallbackJ1939DtcStatusChanged(Index)                                         (&Dem_Cfg_GetCallbackJ1939DtcStatusChanged(Index))
#define Dem_Cfg_GetAddrClearDTCTable(Index)                                                         (&Dem_Cfg_GetClearDTCTable(Index))
#define Dem_Cfg_GetAddrClearDtcNotificationFinishTable(Index)                                       (&Dem_Cfg_GetClearDtcNotificationFinishTable(Index))
#define Dem_Cfg_GetAddrClearDtcNotificationStartTable(Index)                                        (&Dem_Cfg_GetClearDtcNotificationStartTable(Index))
#define Dem_Cfg_GetAddrCommitBuffer()                                                               (&Dem_Cfg_GetCommitBuffer())
#define Dem_Cfg_GetAddrCycleCounterData()                                                           (&Dem_Cfg_GetCycleCounterData())
#define Dem_Cfg_GetAddrDTCSelectorTable(Index)                                                      (&Dem_Cfg_GetDTCSelectorTable(Index))
#define Dem_Cfg_GetAddrReadDataFuncOfDataElementTable(Index)                                        (&Dem_Cfg_GetReadDataFuncOfDataElementTable(Index))
#define Dem_Cfg_GetAddrDebounceData()                                                               (&Dem_Cfg_GetDebounceData())
#define Dem_Cfg_GetAddrDtrData()                                                                    (&Dem_Cfg_GetDtrData())
#define Dem_Cfg_GetAddrDtrStatus(Index)                                                             (&Dem_Cfg_GetDtrStatus(Index))
#define Dem_Cfg_GetAddrEnableConditionFulfilled(Index)                                              (&Dem_Cfg_IsEnableConditionFulfilled(Index))
#define Dem_Cfg_GetAddrEnableConditionGroupCounter(Index)                                           (&Dem_Cfg_GetEnableConditionGroupCounter(Index))
#define Dem_Cfg_GetAddrEnableConditionGroupState(Index)                                             (&Dem_Cfg_GetEnableConditionGroupState(Index))
#define Dem_Cfg_GetAddrEventAvailableData()                                                         (&Dem_Cfg_GetEventAvailableData())
#define Dem_Cfg_GetAddrEventCycleStatus(Index)                                                      (&Dem_Cfg_GetEventCycleStatus(Index))
#define Dem_Cfg_GetAddrEventDataChanged(Index)                                                      (&Dem_Cfg_GetEventDataChanged(Index))
#define Dem_Cfg_GetAddrEventDataCommitNumber(Index)                                                 (&Dem_Cfg_GetEventDataCommitNumber(Index))
#define Dem_Cfg_GetAddrEventDebounceValue(Index)                                                    (&Dem_Cfg_GetEventDebounceValue(Index))
#define Dem_Cfg_GetAddrEventInternalStatus(Index)                                                   (&Dem_Cfg_GetEventInternalStatus(Index))
#define Dem_Cfg_GetAddrEventStatusChanged(Index)                                                    (&Dem_Cfg_GetEventStatusChanged(Index))
#define Dem_Cfg_GetAddrExtendedDataRecordIteratorTable(Index)                                       (&Dem_Cfg_GetExtendedDataRecordIteratorTable(Index))
#define Dem_Cfg_GetAddrFilterInfoTable(Index)                                                       (&Dem_Cfg_GetFilterInfoTable(Index))
#define Dem_Cfg_GetAddrFilterReportedEvents(Index)                                                  (&Dem_Cfg_GetFilterReportedEvents(Index))
#define Dem_Cfg_GetAddrFreezeFrameData()                                                            (&Dem_Cfg_GetFreezeFrameData())
#define Dem_Cfg_GetAddrFreezeFrameIteratorTable(Index)                                              (&Dem_Cfg_GetFreezeFrameIteratorTable(Index))
#define Dem_Cfg_GetAddrGlobalIndicatorStates(Index)                                                 (&Dem_Cfg_GetGlobalIndicatorStates(Index))
#define Dem_Cfg_GetAddrIndicatorBlinking(Index)                                                     (&Dem_Cfg_GetIndicatorBlinking(Index))
#define Dem_Cfg_GetAddrIndicatorContinuous(Index)                                                   (&Dem_Cfg_GetIndicatorContinuous(Index))
#define Dem_Cfg_GetAddrIndicatorFastFlash(Index)                                                    (&Dem_Cfg_GetIndicatorFastFlash(Index))
#define Dem_Cfg_GetAddrIndicatorSlowFlash(Index)                                                    (&Dem_Cfg_GetIndicatorSlowFlash(Index))
#define Dem_Cfg_GetAddrInitMonitorForEvent(Index)                                                   (&Dem_Cfg_GetInitMonitorForEvent(Index))
#define Dem_Cfg_GetAddrInitMonitorsForFunc(Index)                                                   (&Dem_Cfg_GetInitMonitorsForFunc(Index))
#define Dem_Cfg_GetAddrMemoryStatus(Index)                                                          (&Dem_Cfg_GetMemoryStatus(Index))
#define Dem_Cfg_GetAddrMirrorData()                                                                 (&Dem_Cfg_GetMirrorData())
#define Dem_Cfg_GetAddrObdIumprData()                                                               (&Dem_Cfg_GetObdIumprData())
#define Dem_Cfg_GetAddrObdIumprUpdatePending(Index)                                                 (&Dem_Cfg_IsObdIumprUpdatePending(Index))
#define Dem_Cfg_GetAddrPermanentData()                                                              (&Dem_Cfg_GetPermanentData())
#define Dem_Cfg_GetAddrPrestorage()                                                                 (&Dem_Cfg_GetPrestorage())
#define Dem_Cfg_GetAddrPrestorageIndex(Index)                                                       (&Dem_Cfg_GetPrestorageIndex(Index))
#define Dem_Cfg_GetAddrPrimaryChronology(Index)                                                     (&Dem_Cfg_GetPrimaryChronology(Index))
#define Dem_Cfg_GetAddrPrimaryEntry_0()                                                             (&Dem_Cfg_GetPrimaryEntry_0())
#define Dem_Cfg_GetAddrPrimaryEntry_1()                                                             (&Dem_Cfg_GetPrimaryEntry_1())
#define Dem_Cfg_GetAddrPrimaryEntry_2()                                                             (&Dem_Cfg_GetPrimaryEntry_2())
#define Dem_Cfg_GetAddrPrimaryEntry_3()                                                             (&Dem_Cfg_GetPrimaryEntry_3())
#define Dem_Cfg_GetAddrPrimaryEntry_4()                                                             (&Dem_Cfg_GetPrimaryEntry_4())
#define Dem_Cfg_GetAddrPrimaryEntry_5()                                                             (&Dem_Cfg_GetPrimaryEntry_5())
#define Dem_Cfg_GetAddrPrimaryEntry_6()                                                             (&Dem_Cfg_GetPrimaryEntry_6())
#define Dem_Cfg_GetAddrPrimaryEntry_7()                                                             (&Dem_Cfg_GetPrimaryEntry_7())
#define Dem_Cfg_GetAddrReadoutBuffer(Index)                                                         (&Dem_Cfg_GetReadoutBuffer(Index))
#define Dem_Cfg_GetAddrReportedEventsOfFilter(Index)                                                (&Dem_Cfg_GetReportedEventsOfFilter(Index))
#define Dem_Cfg_GetAddrSatelliteInfo0()                                                             (&Dem_Cfg_GetSatelliteInfo0())
#define Dem_Cfg_GetAddrSecondaryChronology(Index)                                                   (&Dem_Cfg_GetSecondaryChronology(Index))
#define Dem_Cfg_GetAddrStatusData()                                                                 (&Dem_Cfg_GetStatusData())
#define Dem_Cfg_GetAddrStorageConditionFulfilled(Index)                                             (&Dem_Cfg_IsStorageConditionFulfilled(Index))
#define Dem_Cfg_GetAddrStorageConditionGroupCounter(Index)                                          (&Dem_Cfg_GetStorageConditionGroupCounter(Index))
#define Dem_Cfg_GetAddrTimeSeriesChronology(Index)                                                  (&Dem_Cfg_GetTimeSeriesChronology(Index))
/** 
  \}
*/ 

/** 
  \defgroup  Dem_CfgPCHasMacros  Dem_Cfg Has Macros (PRE_COMPILE)
  \brief  These macros can be used to detect at runtime a deactivated piece of information. TRUE in the CONFIGURATION_VARIANT PRE-COMPILE, TRUE or FALSE in the CONFIGURATION_VARIANT POST-BUILD.
  \{
*/ 
#define Dem_Cfg_HasAdminData()                                                                      (TRUE != FALSE)
#define Dem_Cfg_HasAgingData()                                                                      (FALSE != FALSE)
#define Dem_Cfg_HasCallbackClearEventAllowed()                                                      (TRUE != FALSE)
#define Dem_Cfg_HasCallbackDtcStatusChanged()                                                       (FALSE != FALSE)
#define Dem_Cfg_HasCallbackGetFdc()                                                                 (FALSE != FALSE)
#define Dem_Cfg_HasCallbackJ1939DtcStatusChanged()                                                  (FALSE != FALSE)
#define Dem_Cfg_HasClearDTCTable()                                                                  (TRUE != FALSE)
#define Dem_Cfg_HasClearDtcNotificationFinishTable()                                                (FALSE != FALSE)
#define Dem_Cfg_HasClearDtcNotificationStartTable()                                                 (FALSE != FALSE)
#define Dem_Cfg_HasClientTable()                                                                    (TRUE != FALSE)
#define Dem_Cfg_HasClearDTCIndexOfClientTable()                                                     (TRUE != FALSE)
#define Dem_Cfg_HasFilterIndexOfClientTable()                                                       (TRUE != FALSE)
#define Dem_Cfg_HasFreezeFrameIteratorIndexOfClientTable()                                          (TRUE != FALSE)
#define Dem_Cfg_HasNmNodeIdOfClientTable()                                                          (FALSE != FALSE)
#define Dem_Cfg_HasReadoutBufferIndexOfClientTable()                                                (TRUE != FALSE)
#define Dem_Cfg_HasSelectorIndexOfClientTable()                                                     (TRUE != FALSE)
#define Dem_Cfg_HasCommitBuffer()                                                                   (TRUE != FALSE)
#define Dem_Cfg_HasConfigurationId()                                                                (TRUE != FALSE)
#define Dem_Cfg_HasCycleCounterData()                                                               (FALSE != FALSE)
#define Dem_Cfg_HasCycleIdTable()                                                                   (TRUE != FALSE)
#define Dem_Cfg_HasEndsOnInitOfCycleIdTable()                                                       (FALSE != FALSE)
#define Dem_Cfg_HasMaskedBitsOfCycleIdTable()                                                       (TRUE != FALSE)
#define Dem_Cfg_HasOpCycleTypeOfCycleIdTable()                                                      (TRUE != FALSE)
#define Dem_Cfg_HasUsedForAgingOfCycleIdTable()                                                     (TRUE != FALSE)
#define Dem_Cfg_HasDTCSelectorTable()                                                               (TRUE != FALSE)
#define Dem_Cfg_HasDataCollectionTable()                                                            (TRUE != FALSE)
#define Dem_Cfg_HasCollectionSizeOfDataCollectionTable()                                            (TRUE != FALSE)
#define Dem_Cfg_HasDataElementTableCol2ElmtIndEndIdxOfDataCollectionTable()                         (TRUE != FALSE)
#define Dem_Cfg_HasDataElementTableCol2ElmtIndStartIdxOfDataCollectionTable()                       (TRUE != FALSE)
#define Dem_Cfg_HasDataElementTableCol2ElmtIndUsedOfDataCollectionTable()                           (TRUE != FALSE)
#define Dem_Cfg_HasDidOffsetFastOfDataCollectionTable()                                             (FALSE != FALSE)
#define Dem_Cfg_HasDidOffsetNormalOfDataCollectionTable()                                           (FALSE != FALSE)
#define Dem_Cfg_HasEventTable_ERec2EventIdIndEndIdxOfDataCollectionTable()                          (FALSE != FALSE)
#define Dem_Cfg_HasEventTable_ERec2EventIdIndStartIdxOfDataCollectionTable()                        (FALSE != FALSE)
#define Dem_Cfg_HasEventTable_ERec2EventIdIndUsedOfDataCollectionTable()                            (FALSE != FALSE)
#define Dem_Cfg_HasIdNumberOfDataCollectionTable()                                                  (TRUE != FALSE)
#define Dem_Cfg_HasStorageKindOfDataCollectionTable()                                               (TRUE != FALSE)
#define Dem_Cfg_HasTriggerOfDataCollectionTable()                                                   (TRUE != FALSE)
#define Dem_Cfg_HasUpdateOfDataCollectionTable()                                                    (TRUE != FALSE)
#define Dem_Cfg_HasDataCollectionTableEdr2CollInd()                                                 (TRUE != FALSE)
#define Dem_Cfg_HasDataCollectionTableErec2CollInd()                                                (TRUE != FALSE)
#define Dem_Cfg_HasDataCollectionTableFfm2CollInd()                                                 (TRUE != FALSE)
#define Dem_Cfg_HasDataCollectionTableJ19392CollInd()                                               (FALSE != FALSE)
#define Dem_Cfg_HasDataCollectionTablePid2CollInd()                                                 (FALSE != FALSE)
#define Dem_Cfg_HasDataElementTable()                                                               (TRUE != FALSE)
#define Dem_Cfg_HasDataIsStoredInNVOfDataElementTable()                                             (TRUE != FALSE)
#define Dem_Cfg_HasElementKindOfDataElementTable()                                                  (TRUE != FALSE)
#define Dem_Cfg_HasElementSizeOfDataElementTable()                                                  (TRUE != FALSE)
#define Dem_Cfg_HasReadDataFuncOfDataElementTable()                                                 (TRUE != FALSE)
#define Dem_Cfg_HasDataElementTableCol2ElmtInd()                                                    (TRUE != FALSE)
#define Dem_Cfg_HasDebounceData()                                                                   (FALSE != FALSE)
#define Dem_Cfg_HasDebounceHiResTable()                                                             (FALSE != FALSE)
#define Dem_Cfg_HasDebounceLoResTable()                                                             (FALSE != FALSE)
#define Dem_Cfg_HasDebounceTable()                                                                  (TRUE != FALSE)
#define Dem_Cfg_HasDebounceContinuousOfDebounceTable()                                              (TRUE != FALSE)
#define Dem_Cfg_HasDecrementStepSizeOfDebounceTable()                                               (TRUE != FALSE)
#define Dem_Cfg_HasEventDebounceAlgorithmOfDebounceTable()                                          (TRUE != FALSE)
#define Dem_Cfg_HasEventDebounceBehaviorOfDebounceTable()                                           (TRUE != FALSE)
#define Dem_Cfg_HasFailTimerCyclesOfDebounceTable()                                                 (TRUE != FALSE)
#define Dem_Cfg_HasFailedThresholdOfDebounceTable()                                                 (TRUE != FALSE)
#define Dem_Cfg_HasIncrementStepSizeOfDebounceTable()                                               (TRUE != FALSE)
#define Dem_Cfg_HasJumpDownOfDebounceTable()                                                        (TRUE != FALSE)
#define Dem_Cfg_HasJumpDownValueOfDebounceTable()                                                   (TRUE != FALSE)
#define Dem_Cfg_HasJumpUpOfDebounceTable()                                                          (TRUE != FALSE)
#define Dem_Cfg_HasJumpUpValueOfDebounceTable()                                                     (TRUE != FALSE)
#define Dem_Cfg_HasMaskedBitsOfDebounceTable()                                                      (TRUE != FALSE)
#define Dem_Cfg_HasPassTimerCyclesOfDebounceTable()                                                 (TRUE != FALSE)
#define Dem_Cfg_HasPassedThresholdOfDebounceTable()                                                 (TRUE != FALSE)
#define Dem_Cfg_HasPreconfirmedThresholdOfDebounceTable()                                           (FALSE != FALSE)
#define Dem_Cfg_HasStorageOfDebounceTable()                                                         (TRUE != FALSE)
#define Dem_Cfg_HasStorageThresholdOfDebounceTable()                                                (FALSE != FALSE)
#define Dem_Cfg_HasStorageTimerCyclesOfDebounceTable()                                              (FALSE != FALSE)
#define Dem_Cfg_HasDtcGroupMask()                                                                   (FALSE != FALSE)
#define Dem_Cfg_HasGroupMaskOfDtcGroupMask()                                                        (FALSE != FALSE)
#define Dem_Cfg_HasUdsGroupDtcOfDtcGroupMask()                                                      (FALSE != FALSE)
#define Dem_Cfg_HasDtcTable()                                                                       (TRUE != FALSE)
#define Dem_Cfg_HasDtcSeverityOfDtcTable()                                                          (TRUE != FALSE)
#define Dem_Cfg_HasFunctionalUnitOfDtcTable()                                                       (TRUE != FALSE)
#define Dem_Cfg_HasImmediateNvStorageOfDtcTable()                                                   (TRUE != FALSE)
#define Dem_Cfg_HasJ1939DtcOfDtcTable()                                                             (FALSE != FALSE)
#define Dem_Cfg_HasJ1939NodeIdIndEndIdxOfDtcTable()                                                 (FALSE != FALSE)
#define Dem_Cfg_HasJ1939NodeIdIndStartIdxOfDtcTable()                                               (FALSE != FALSE)
#define Dem_Cfg_HasJ1939NodeIdIndUsedOfDtcTable()                                                   (FALSE != FALSE)
#define Dem_Cfg_HasObdDtcOfDtcTable()                                                               (FALSE != FALSE)
#define Dem_Cfg_HasUdsDtcOfDtcTable()                                                               (TRUE != FALSE)
#define Dem_Cfg_HasDtrData()                                                                        (FALSE != FALSE)
#define Dem_Cfg_HasDtrStatus()                                                                      (FALSE != FALSE)
#define Dem_Cfg_HasDtrTable()                                                                       (FALSE != FALSE)
#define Dem_Cfg_HasDivisorOfDtrTable()                                                              (FALSE != FALSE)
#define Dem_Cfg_HasEventTableIdxOfDtrTable()                                                        (FALSE != FALSE)
#define Dem_Cfg_HasLinearFactorOfDtrTable()                                                         (FALSE != FALSE)
#define Dem_Cfg_HasOffsetOfDtrTable()                                                               (FALSE != FALSE)
#define Dem_Cfg_HasUasidOfDtrTable()                                                                (FALSE != FALSE)
#define Dem_Cfg_HasUpdateKindOfDtrTable()                                                           (FALSE != FALSE)
#define Dem_Cfg_HasDtrTableInd()                                                                    (FALSE != FALSE)
#define Dem_Cfg_HasEnableConditionFulfilled()                                                       (TRUE != FALSE)
#define Dem_Cfg_HasEnableConditionGroupCounter()                                                    (TRUE != FALSE)
#define Dem_Cfg_HasEnableConditionGroupState()                                                      (TRUE != FALSE)
#define Dem_Cfg_HasEnableConditionGroupTable()                                                      (TRUE != FALSE)
#define Dem_Cfg_HasIndexOfEnableConditionGroupTable()                                               (TRUE != FALSE)
#define Dem_Cfg_HasEnableConditionGroupTableInd()                                                   (TRUE != FALSE)
#define Dem_Cfg_HasEnableConditionInitTable()                                                       (TRUE != FALSE)
#define Dem_Cfg_HasFulfilledAtInitOfEnableConditionInitTable()                                      (TRUE != FALSE)
#define Dem_Cfg_HasEnableConditionTable()                                                           (TRUE != FALSE)
#define Dem_Cfg_HasEnableConditionGroupTableIndEndIdxOfEnableConditionTable()                       (TRUE != FALSE)
#define Dem_Cfg_HasEnableConditionGroupTableIndStartIdxOfEnableConditionTable()                     (TRUE != FALSE)
#define Dem_Cfg_HasEnableConditionGroupTableIndUsedOfEnableConditionTable()                         (TRUE != FALSE)
#define Dem_Cfg_HasEventAvailableData()                                                             (FALSE != FALSE)
#define Dem_Cfg_HasEventAvailableDefault()                                                          (TRUE != FALSE)
#define Dem_Cfg_HasEventAvailableInVariant()                                                        (TRUE != FALSE)
#define Dem_Cfg_HasEventCycleStatus()                                                               (FALSE != FALSE)
#define Dem_Cfg_HasEventDataChanged()                                                               (FALSE != FALSE)
#define Dem_Cfg_HasEventDataCommitNumber()                                                          (TRUE != FALSE)
#define Dem_Cfg_HasEventDebounceValue()                                                             (TRUE != FALSE)
#define Dem_Cfg_HasEventInternalStatus()                                                            (TRUE != FALSE)
#define Dem_Cfg_HasEventStatusChanged()                                                             (FALSE != FALSE)
#define Dem_Cfg_HasEventTable()                                                                     (TRUE != FALSE)
#define Dem_Cfg_HasAgingAllowedOfEventTable()                                                       (TRUE != FALSE)
#define Dem_Cfg_HasAgingCycleCounterThresholdOfEventTable()                                         (TRUE != FALSE)
#define Dem_Cfg_HasAgingCycleIdOfEventTable()                                                       (TRUE != FALSE)
#define Dem_Cfg_HasCallbackClearEventAllowedIdxOfEventTable()                                       (TRUE != FALSE)
#define Dem_Cfg_HasCallbackClearEventAllowedUsedOfEventTable()                                      (TRUE != FALSE)
#define Dem_Cfg_HasCallbackGetFdcIdxOfEventTable()                                                  (FALSE != FALSE)
#define Dem_Cfg_HasDebounceTableIdxOfEventTable()                                                   (TRUE != FALSE)
#define Dem_Cfg_HasDtcTableIdxOfEventTable()                                                        (TRUE != FALSE)
#define Dem_Cfg_HasDtrTableIndEndIdxOfEventTable()                                                  (FALSE != FALSE)
#define Dem_Cfg_HasDtrTableIndStartIdxOfEventTable()                                                (FALSE != FALSE)
#define Dem_Cfg_HasDtrTableIndUsedOfEventTable()                                                    (FALSE != FALSE)
#define Dem_Cfg_HasEnableConditionGroupTableIdxOfEventTable()                                       (TRUE != FALSE)
#define Dem_Cfg_HasEventDestinationOfEventTable()                                                   (TRUE != FALSE)
#define Dem_Cfg_HasEventFailureCycleCounterThresholdOfEventTable()                                  (TRUE != FALSE)
#define Dem_Cfg_HasEventKindOfEventTable()                                                          (TRUE != FALSE)
#define Dem_Cfg_HasEventLatchTFOfEventTable()                                                       (TRUE != FALSE)
#define Dem_Cfg_HasEventPriorityOfEventTable()                                                      (TRUE != FALSE)
#define Dem_Cfg_HasEventSignificanceOfEventTable()                                                  (TRUE != FALSE)
#define Dem_Cfg_HasExtendedDataTableIdxOfEventTable()                                               (TRUE != FALSE)
#define Dem_Cfg_HasFailedCycleCounterIndexOfEventTable()                                            (FALSE != FALSE)
#define Dem_Cfg_HasFaultPendingCounterIndexOfEventTable()                                           (FALSE != FALSE)
#define Dem_Cfg_HasFreezeFrameNumTableEndIdxOfEventTable()                                          (TRUE != FALSE)
#define Dem_Cfg_HasFreezeFrameNumTableStartIdxOfEventTable()                                        (TRUE != FALSE)
#define Dem_Cfg_HasFreezeFrameNumTableUsedOfEventTable()                                            (TRUE != FALSE)
#define Dem_Cfg_HasFreezeFrameTableStdFFIdxOfEventTable()                                           (TRUE != FALSE)
#define Dem_Cfg_HasHealingTargetOfEventTable()                                                      (TRUE != FALSE)
#define Dem_Cfg_HasMaskedBitsOfEventTable()                                                         (TRUE != FALSE)
#define Dem_Cfg_HasOBDVisibilityDelayedUntilDcyQualificationOfEventTable()                          (TRUE != FALSE)
#define Dem_Cfg_HasOperationCycleIdOfEventTable()                                                   (TRUE != FALSE)
#define Dem_Cfg_HasSatelliteEventIdxOfEventTable()                                                  (TRUE != FALSE)
#define Dem_Cfg_HasSatelliteInfoIdxOfEventTable()                                                   (TRUE != FALSE)
#define Dem_Cfg_HasSpecialIndicatorTableEndIdxOfEventTable()                                        (FALSE != FALSE)
#define Dem_Cfg_HasSpecialIndicatorTableStartIdxOfEventTable()                                      (FALSE != FALSE)
#define Dem_Cfg_HasSpecialIndicatorTableUsedOfEventTable()                                          (FALSE != FALSE)
#define Dem_Cfg_HasEventTableInd()                                                                  (TRUE != FALSE)
#define Dem_Cfg_HasEventTable_ERec2EventIdInd()                                                     (FALSE != FALSE)
#define Dem_Cfg_HasEventTable_ObdRdyGroup2EventIdInd()                                              (FALSE != FALSE)
#define Dem_Cfg_HasExtendedDataRecordIteratorTable()                                                (TRUE != FALSE)
#define Dem_Cfg_HasExtendedDataRecordTable()                                                        (TRUE != FALSE)
#define Dem_Cfg_HasDataCollectionTableErec2CollIndEndIdxOfExtendedDataRecordTable()                 (TRUE != FALSE)
#define Dem_Cfg_HasDataCollectionTableErec2CollIndStartIdxOfExtendedDataRecordTable()               (TRUE != FALSE)
#define Dem_Cfg_HasDataCollectionTableErec2CollIndUsedOfExtendedDataRecordTable()                   (TRUE != FALSE)
#define Dem_Cfg_HasExtendedDataTable()                                                              (TRUE != FALSE)
#define Dem_Cfg_HasDataCollectionTableEdr2CollIndEndIdxOfExtendedDataTable()                        (TRUE != FALSE)
#define Dem_Cfg_HasDataCollectionTableEdr2CollIndStartIdxOfExtendedDataTable()                      (TRUE != FALSE)
#define Dem_Cfg_HasDataCollectionTableEdr2CollIndUsedOfExtendedDataTable()                          (TRUE != FALSE)
#define Dem_Cfg_HasMaxRecordSizeOfExtendedDataTable()                                               (TRUE != FALSE)
#define Dem_Cfg_HasFilterInfoTable()                                                                (TRUE != FALSE)
#define Dem_Cfg_HasFilterReportedEvents()                                                           (TRUE != FALSE)
#define Dem_Cfg_HasFinalMagicNumber()                                                               (FALSE != FALSE)
#define Dem_Cfg_HasFreezeFrameData()                                                                (FALSE != FALSE)
#define Dem_Cfg_HasFreezeFrameIteratorTable()                                                       (TRUE != FALSE)
#define Dem_Cfg_HasFreezeFrameNumTable()                                                            (TRUE != FALSE)
#define Dem_Cfg_HasFFNumberOfFreezeFrameNumTable()                                                  (TRUE != FALSE)
#define Dem_Cfg_HasFFTriggerOfFreezeFrameNumTable()                                                 (TRUE != FALSE)
#define Dem_Cfg_HasFFUpdateOfFreezeFrameNumTable()                                                  (TRUE != FALSE)
#define Dem_Cfg_HasFreezeFrameTable()                                                               (TRUE != FALSE)
#define Dem_Cfg_HasDataCollectionTableFfm2CollIndEndIdxOfFreezeFrameTable()                         (TRUE != FALSE)
#define Dem_Cfg_HasDataCollectionTableFfm2CollIndStartIdxOfFreezeFrameTable()                       (TRUE != FALSE)
#define Dem_Cfg_HasDataCollectionTableFfm2CollIndUsedOfFreezeFrameTable()                           (TRUE != FALSE)
#define Dem_Cfg_HasRecordSizeOfFreezeFrameTable()                                                   (TRUE != FALSE)
#define Dem_Cfg_HasRecordSizeUdsOfFastRateTimeSeriesPowertrainOfFreezeFrameTable()                  (TRUE != FALSE)
#define Dem_Cfg_HasRecordSizeUdsOfFreezeFrameTable()                                                (TRUE != FALSE)
#define Dem_Cfg_HasRecordSizeUdsOfNormalRateTimeSeriesPowertrainOfFreezeFrameTable()                (TRUE != FALSE)
#define Dem_Cfg_HasGeneralJ1939Table()                                                              (FALSE != FALSE)
#define Dem_Cfg_HasDataCollectionTableJ19392CollIndEndIdxOfGeneralJ1939Table()                      (FALSE != FALSE)
#define Dem_Cfg_HasDataCollectionTableJ19392CollIndStartIdxOfGeneralJ1939Table()                    (FALSE != FALSE)
#define Dem_Cfg_HasDataCollectionTableJ19392CollIndUsedOfGeneralJ1939Table()                        (FALSE != FALSE)
#define Dem_Cfg_HasRecordSizeOfGeneralJ1939Table()                                                  (FALSE != FALSE)
#define Dem_Cfg_HasGeneralObdInput()                                                                (TRUE != FALSE)
#define Dem_Cfg_HasDataElementTableIdxOfGeneralObdInput()                                           (TRUE != FALSE)
#define Dem_Cfg_HasGlobalIndicatorStates()                                                          (FALSE != FALSE)
#define Dem_Cfg_HasGlobalObdRequirements()                                                          (FALSE != FALSE)
#define Dem_Cfg_HasGlobalSeverityMask()                                                             (TRUE != FALSE)
#define Dem_Cfg_HasIndicatorBlinking()                                                              (FALSE != FALSE)
#define Dem_Cfg_HasIndicatorContinuous()                                                            (FALSE != FALSE)
#define Dem_Cfg_HasIndicatorFastFlash()                                                             (FALSE != FALSE)
#define Dem_Cfg_HasIndicatorSlowFlash()                                                             (FALSE != FALSE)
#define Dem_Cfg_HasInitDataHashCode()                                                               (FALSE != FALSE)
#define Dem_Cfg_HasInitMonListForFunc()                                                             (FALSE != FALSE)
#define Dem_Cfg_HasInitMonitorForEvent()                                                            (FALSE != FALSE)
#define Dem_Cfg_HasInitMonitorsForFunc()                                                            (FALSE != FALSE)
#define Dem_Cfg_HasJ1939NodeId()                                                                    (FALSE != FALSE)
#define Dem_Cfg_HasJ1939NodeIdInd()                                                                 (FALSE != FALSE)
#define Dem_Cfg_HasJ1939NodeIndicator()                                                             (FALSE != FALSE)
#define Dem_Cfg_HasMemoryBlockId()                                                                  (TRUE != FALSE)
#define Dem_Cfg_HasMemoryBlockIdToMemoryEntryId()                                                   (TRUE != FALSE)
#define Dem_Cfg_HasMemoryDataPtr()                                                                  (TRUE != FALSE)
#define Dem_Cfg_HasMemoryDataSize()                                                                 (TRUE != FALSE)
#define Dem_Cfg_HasMemoryEntry()                                                                    (TRUE != FALSE)
#define Dem_Cfg_HasMemoryEntryInit()                                                                (TRUE != FALSE)
#define Dem_Cfg_HasMemoryStatus()                                                                   (TRUE != FALSE)
#define Dem_Cfg_HasMidTable()                                                                       (FALSE != FALSE)
#define Dem_Cfg_HasDtrTableIdxOfMidTable()                                                          (FALSE != FALSE)
#define Dem_Cfg_HasMidOfMidTable()                                                                  (FALSE != FALSE)
#define Dem_Cfg_HasTidOfMidTable()                                                                  (FALSE != FALSE)
#define Dem_Cfg_HasMirrorData()                                                                     (FALSE != FALSE)
#define Dem_Cfg_HasNormalIndicatorTable()                                                           (FALSE != FALSE)
#define Dem_Cfg_HasBehaviorOfNormalIndicatorTable()                                                 (FALSE != FALSE)
#define Dem_Cfg_HasIdOfNormalIndicatorTable()                                                       (FALSE != FALSE)
#define Dem_Cfg_HasObdIumprData()                                                                   (FALSE != FALSE)
#define Dem_Cfg_HasObdIumprUpdatePending()                                                          (FALSE != FALSE)
#define Dem_Cfg_HasPermanentData()                                                                  (FALSE != FALSE)
#define Dem_Cfg_HasPidTable()                                                                       (FALSE != FALSE)
#define Dem_Cfg_HasDataCollectionTablePid2CollIndEndIdxOfPidTable()                                 (FALSE != FALSE)
#define Dem_Cfg_HasDataCollectionTablePid2CollIndStartIdxOfPidTable()                               (FALSE != FALSE)
#define Dem_Cfg_HasDataCollectionTablePid2CollIndUsedOfPidTable()                                   (FALSE != FALSE)
#define Dem_Cfg_HasPrestorage()                                                                     (FALSE != FALSE)
#define Dem_Cfg_HasPrestorageIndex()                                                                (FALSE != FALSE)
#define Dem_Cfg_HasPrimaryChronology()                                                              (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryEntry_0()                                                                 (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryEntry_1()                                                                 (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryEntry_2()                                                                 (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryEntry_3()                                                                 (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryEntry_4()                                                                 (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryEntry_5()                                                                 (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryEntry_6()                                                                 (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryEntry_7()                                                                 (TRUE != FALSE)
#define Dem_Cfg_HasRatioIdTable()                                                                   (FALSE != FALSE)
#define Dem_Cfg_HasReadinessGroupTable()                                                            (TRUE != FALSE)
#define Dem_Cfg_HasEventTable_ObdRdyGroup2EventIdIndEndIdxOfReadinessGroupTable()                   (FALSE != FALSE)
#define Dem_Cfg_HasEventTable_ObdRdyGroup2EventIdIndStartIdxOfReadinessGroupTable()                 (FALSE != FALSE)
#define Dem_Cfg_HasEventTable_ObdRdyGroup2EventIdIndUsedOfReadinessGroupTable()                     (FALSE != FALSE)
#define Dem_Cfg_HasReadinessGroupOfReadinessGroupTable()                                            (TRUE != FALSE)
#define Dem_Cfg_HasReadoutBuffer()                                                                  (TRUE != FALSE)
#define Dem_Cfg_HasReportedEventsOfFilter()                                                         (TRUE != FALSE)
#define Dem_Cfg_HasSatelliteInfo()                                                                  (TRUE != FALSE)
#define Dem_Cfg_HasApplicationIdOfSatelliteInfo()                                                   (TRUE != FALSE)
#define Dem_Cfg_HasDebounceLoResTimerOfSatelliteInfo()                                              (FALSE != FALSE)
#define Dem_Cfg_HasEventCountOfSatelliteInfo()                                                      (TRUE != FALSE)
#define Dem_Cfg_HasEventTableIndEndIdxOfSatelliteInfo()                                             (TRUE != FALSE)
#define Dem_Cfg_HasEventTableIndStartIdxOfSatelliteInfo()                                           (TRUE != FALSE)
#define Dem_Cfg_HasEventTableIndUsedOfSatelliteInfo()                                               (TRUE != FALSE)
#define Dem_Cfg_HasMaxDebounceValuesOfSatelliteInfo()                                               (FALSE != FALSE)
#define Dem_Cfg_HasSatelliteDataOfSatelliteInfo()                                                   (TRUE != FALSE)
#define Dem_Cfg_HasSatelliteExtendedDataOfSatelliteInfo()                                           (FALSE != FALSE)
#define Dem_Cfg_HasSatelliteStatusOfSatelliteInfo()                                                 (TRUE != FALSE)
#define Dem_Cfg_HasSatelliteInfo0()                                                                 (TRUE != FALSE)
#define Dem_Cfg_HasSatelliteTimeDebounceInfo()                                                      (FALSE != FALSE)
#define Dem_Cfg_HasDebounceHiResTableEndIdxOfSatelliteTimeDebounceInfo()                            (FALSE != FALSE)
#define Dem_Cfg_HasDebounceHiResTableStartIdxOfSatelliteTimeDebounceInfo()                          (FALSE != FALSE)
#define Dem_Cfg_HasDebounceHiResTableUsedOfSatelliteTimeDebounceInfo()                              (FALSE != FALSE)
#define Dem_Cfg_HasDebounceLoResTableEndIdxOfSatelliteTimeDebounceInfo()                            (FALSE != FALSE)
#define Dem_Cfg_HasDebounceLoResTableStartIdxOfSatelliteTimeDebounceInfo()                          (FALSE != FALSE)
#define Dem_Cfg_HasDebounceLoResTableUsedOfSatelliteTimeDebounceInfo()                              (FALSE != FALSE)
#define Dem_Cfg_HasSecondaryChronology()                                                            (FALSE != FALSE)
#define Dem_Cfg_HasSizeOfCallbackClearEventAllowed()                                                (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfCallbackDtcStatusChanged()                                                 (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfCallbackGetFdc()                                                           (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfCallbackJ1939DtcStatusChanged()                                            (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfClearDTCTable()                                                            (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfClearDtcNotificationFinishTable()                                          (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfClearDtcNotificationStartTable()                                           (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfClientTable()                                                              (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfDTCSelectorTable()                                                         (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfDataElementTable()                                                         (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfDebounceHiResTable()                                                       (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfDebounceLoResTable()                                                       (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfDtcGroupMask()                                                             (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfDtrStatus()                                                                (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfDtrTable()                                                                 (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfEnableConditionFulfilled()                                                 (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfEnableConditionGroupCounter()                                              (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfEnableConditionGroupState()                                                (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfEnableConditionGroupTable()                                                (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfEnableConditionTable()                                                     (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfEventCycleStatus()                                                         (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfEventDataChanged()                                                         (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfEventDataCommitNumber()                                                    (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfEventDebounceValue()                                                       (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfEventInternalStatus()                                                      (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfEventStatusChanged()                                                       (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfEventTable()                                                               (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfExtendedDataRecordIteratorTable()                                          (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfFilterInfoTable()                                                          (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfFilterReportedEvents()                                                     (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfFreezeFrameIteratorTable()                                                 (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfGlobalIndicatorStates()                                                    (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfIndicatorBlinking()                                                        (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfIndicatorContinuous()                                                      (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfIndicatorFastFlash()                                                       (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfIndicatorSlowFlash()                                                       (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfInitMonitorForEvent()                                                      (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfInitMonitorsForFunc()                                                      (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfMemoryBlockIdToMemoryEntryId()                                             (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfMemoryEntry()                                                              (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfMemoryStatus()                                                             (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfObdIumprUpdatePending()                                                    (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfPrestorageIndex()                                                          (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfPrimaryChronology()                                                        (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfReadinessGroupTable()                                                      (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfReadoutBuffer()                                                            (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfReportedEventsOfFilter()                                                   (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfSatelliteInfo()                                                            (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfSecondaryChronology()                                                      (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfSpecialIndicatorTable()                                                    (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfStartIdx500miDenRatioTable()                                               (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfStorageConditionFulfilled()                                                (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfStorageConditionGroupCounter()                                             (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfStorageConditionGroupTable()                                               (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfStorageConditionTable()                                                    (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfSupportedMidsTable()                                                       (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfTimeSeriesChronology()                                                     (TRUE != FALSE)
#define Dem_Cfg_HasSpecialIndicatorTable()                                                          (FALSE != FALSE)
#define Dem_Cfg_HasBehaviorOfSpecialIndicatorTable()                                                (FALSE != FALSE)
#define Dem_Cfg_HasIdOfSpecialIndicatorTable()                                                      (FALSE != FALSE)
#define Dem_Cfg_HasStartIdx500miDenRatioTable()                                                     (FALSE != FALSE)
#define Dem_Cfg_HasStatusData()                                                                     (TRUE != FALSE)
#define Dem_Cfg_HasStorageConditionFulfilled()                                                      (FALSE != FALSE)
#define Dem_Cfg_HasStorageConditionGroupCounter()                                                   (FALSE != FALSE)
#define Dem_Cfg_HasStorageConditionGroupTable()                                                     (FALSE != FALSE)
#define Dem_Cfg_HasIndexOfStorageConditionGroupTable()                                              (FALSE != FALSE)
#define Dem_Cfg_HasStorageConditionGroupTableInd()                                                  (FALSE != FALSE)
#define Dem_Cfg_HasStorageConditionInitTable()                                                      (FALSE != FALSE)
#define Dem_Cfg_HasFulfilledAtInitOfStorageConditionInitTable()                                     (FALSE != FALSE)
#define Dem_Cfg_HasStorageConditionTable()                                                          (FALSE != FALSE)
#define Dem_Cfg_HasStorageConditionGroupTableIndEndIdxOfStorageConditionTable()                     (FALSE != FALSE)
#define Dem_Cfg_HasStorageConditionGroupTableIndStartIdxOfStorageConditionTable()                   (FALSE != FALSE)
#define Dem_Cfg_HasStorageConditionGroupTableIndUsedOfStorageConditionTable()                       (FALSE != FALSE)
#define Dem_Cfg_HasSupportedMidsTable()                                                             (FALSE != FALSE)
#define Dem_Cfg_HasStartIdxMidTableOfSupportedMidsTable()                                           (FALSE != FALSE)
#define Dem_Cfg_HasSupportedMidMaskOfSupportedMidsTable()                                           (FALSE != FALSE)
#define Dem_Cfg_HasTimeSeriesChronology()                                                           (FALSE != FALSE)
#define Dem_Cfg_HasTimeSeriesEntryInit()                                                            (TRUE != FALSE)
#define Dem_Cfg_HasUseOBDIIInVariant()                                                              (TRUE != FALSE)
#define Dem_Cfg_HasUsePermanentInVariant()                                                          (FALSE != FALSE)
#define Dem_Cfg_HasUseWWHOBDInVariant()                                                             (TRUE != FALSE)
#define Dem_HasPCConfig()                                                                           (TRUE != FALSE)
#define Dem_Cfg_HasAdminDataOfPCConfig()                                                            (TRUE != FALSE)
#define Dem_Cfg_HasAgingDataOfPCConfig()                                                            (FALSE != FALSE)
#define Dem_Cfg_HasCallbackClearEventAllowedOfPCConfig()                                            (TRUE != FALSE)
#define Dem_Cfg_HasCallbackDtcStatusChangedOfPCConfig()                                             (FALSE != FALSE)
#define Dem_Cfg_HasCallbackGetFdcOfPCConfig()                                                       (FALSE != FALSE)
#define Dem_Cfg_HasCallbackJ1939DtcStatusChangedOfPCConfig()                                        (FALSE != FALSE)
#define Dem_Cfg_HasClearDTCTableOfPCConfig()                                                        (TRUE != FALSE)
#define Dem_Cfg_HasClearDtcNotificationFinishTableOfPCConfig()                                      (FALSE != FALSE)
#define Dem_Cfg_HasClearDtcNotificationStartTableOfPCConfig()                                       (FALSE != FALSE)
#define Dem_Cfg_HasClientTableOfPCConfig()                                                          (TRUE != FALSE)
#define Dem_Cfg_HasCommitBufferOfPCConfig()                                                         (TRUE != FALSE)
#define Dem_Cfg_HasConfigurationIdOfPCConfig()                                                      (TRUE != FALSE)
#define Dem_Cfg_HasCycleCounterDataOfPCConfig()                                                     (FALSE != FALSE)
#define Dem_Cfg_HasCycleIdTableOfPCConfig()                                                         (TRUE != FALSE)
#define Dem_Cfg_HasDTCSelectorTableOfPCConfig()                                                     (TRUE != FALSE)
#define Dem_Cfg_HasDataCollectionTableEdr2CollIndOfPCConfig()                                       (TRUE != FALSE)
#define Dem_Cfg_HasDataCollectionTableErec2CollIndOfPCConfig()                                      (TRUE != FALSE)
#define Dem_Cfg_HasDataCollectionTableFfm2CollIndOfPCConfig()                                       (TRUE != FALSE)
#define Dem_Cfg_HasDataCollectionTableJ19392CollIndOfPCConfig()                                     (FALSE != FALSE)
#define Dem_Cfg_HasDataCollectionTableOfPCConfig()                                                  (TRUE != FALSE)
#define Dem_Cfg_HasDataCollectionTablePid2CollIndOfPCConfig()                                       (FALSE != FALSE)
#define Dem_Cfg_HasDataElementTableCol2ElmtIndOfPCConfig()                                          (TRUE != FALSE)
#define Dem_Cfg_HasDataElementTableOfPCConfig()                                                     (TRUE != FALSE)
#define Dem_Cfg_HasDebounceDataOfPCConfig()                                                         (FALSE != FALSE)
#define Dem_Cfg_HasDebounceHiResTableOfPCConfig()                                                   (FALSE != FALSE)
#define Dem_Cfg_HasDebounceLoResTableOfPCConfig()                                                   (FALSE != FALSE)
#define Dem_Cfg_HasDebounceTableOfPCConfig()                                                        (TRUE != FALSE)
#define Dem_Cfg_HasDtcGroupMaskOfPCConfig()                                                         (FALSE != FALSE)
#define Dem_Cfg_HasDtcTableOfPCConfig()                                                             (TRUE != FALSE)
#define Dem_Cfg_HasDtrDataOfPCConfig()                                                              (FALSE != FALSE)
#define Dem_Cfg_HasDtrStatusOfPCConfig()                                                            (FALSE != FALSE)
#define Dem_Cfg_HasDtrTableIndOfPCConfig()                                                          (FALSE != FALSE)
#define Dem_Cfg_HasDtrTableOfPCConfig()                                                             (FALSE != FALSE)
#define Dem_Cfg_HasEnableConditionFulfilledOfPCConfig()                                             (TRUE != FALSE)
#define Dem_Cfg_HasEnableConditionGroupCounterOfPCConfig()                                          (TRUE != FALSE)
#define Dem_Cfg_HasEnableConditionGroupStateOfPCConfig()                                            (TRUE != FALSE)
#define Dem_Cfg_HasEnableConditionGroupTableIndOfPCConfig()                                         (TRUE != FALSE)
#define Dem_Cfg_HasEnableConditionGroupTableOfPCConfig()                                            (TRUE != FALSE)
#define Dem_Cfg_HasEnableConditionInitTableOfPCConfig()                                             (TRUE != FALSE)
#define Dem_Cfg_HasEnableConditionTableOfPCConfig()                                                 (TRUE != FALSE)
#define Dem_Cfg_HasEventAvailableDataOfPCConfig()                                                   (FALSE != FALSE)
#define Dem_Cfg_HasEventAvailableDefaultOfPCConfig()                                                (TRUE != FALSE)
#define Dem_Cfg_HasEventAvailableInVariantOfPCConfig()                                              (TRUE != FALSE)
#define Dem_Cfg_HasEventCycleStatusOfPCConfig()                                                     (FALSE != FALSE)
#define Dem_Cfg_HasEventDataChangedOfPCConfig()                                                     (FALSE != FALSE)
#define Dem_Cfg_HasEventDataCommitNumberOfPCConfig()                                                (TRUE != FALSE)
#define Dem_Cfg_HasEventDebounceValueOfPCConfig()                                                   (TRUE != FALSE)
#define Dem_Cfg_HasEventInternalStatusOfPCConfig()                                                  (TRUE != FALSE)
#define Dem_Cfg_HasEventStatusChangedOfPCConfig()                                                   (FALSE != FALSE)
#define Dem_Cfg_HasEventTableIndOfPCConfig()                                                        (TRUE != FALSE)
#define Dem_Cfg_HasEventTableOfPCConfig()                                                           (TRUE != FALSE)
#define Dem_Cfg_HasEventTable_ERec2EventIdIndOfPCConfig()                                           (FALSE != FALSE)
#define Dem_Cfg_HasEventTable_ObdRdyGroup2EventIdIndOfPCConfig()                                    (FALSE != FALSE)
#define Dem_Cfg_HasExtendedDataRecordIteratorTableOfPCConfig()                                      (TRUE != FALSE)
#define Dem_Cfg_HasExtendedDataRecordTableOfPCConfig()                                              (TRUE != FALSE)
#define Dem_Cfg_HasExtendedDataTableOfPCConfig()                                                    (TRUE != FALSE)
#define Dem_Cfg_HasFilterInfoTableOfPCConfig()                                                      (TRUE != FALSE)
#define Dem_Cfg_HasFilterReportedEventsOfPCConfig()                                                 (TRUE != FALSE)
#define Dem_Cfg_HasFinalMagicNumberOfPCConfig()                                                     (FALSE != FALSE)
#define Dem_Cfg_HasFreezeFrameDataOfPCConfig()                                                      (FALSE != FALSE)
#define Dem_Cfg_HasFreezeFrameIteratorTableOfPCConfig()                                             (TRUE != FALSE)
#define Dem_Cfg_HasFreezeFrameNumTableOfPCConfig()                                                  (TRUE != FALSE)
#define Dem_Cfg_HasFreezeFrameTableOfPCConfig()                                                     (TRUE != FALSE)
#define Dem_Cfg_HasGeneralJ1939TableOfPCConfig()                                                    (FALSE != FALSE)
#define Dem_Cfg_HasGeneralObdInputOfPCConfig()                                                      (TRUE != FALSE)
#define Dem_Cfg_HasGlobalIndicatorStatesOfPCConfig()                                                (FALSE != FALSE)
#define Dem_Cfg_HasGlobalObdRequirementsOfPCConfig()                                                (FALSE != FALSE)
#define Dem_Cfg_HasGlobalSeverityMaskOfPCConfig()                                                   (TRUE != FALSE)
#define Dem_Cfg_HasIndicatorBlinkingOfPCConfig()                                                    (FALSE != FALSE)
#define Dem_Cfg_HasIndicatorContinuousOfPCConfig()                                                  (FALSE != FALSE)
#define Dem_Cfg_HasIndicatorFastFlashOfPCConfig()                                                   (FALSE != FALSE)
#define Dem_Cfg_HasIndicatorSlowFlashOfPCConfig()                                                   (FALSE != FALSE)
#define Dem_Cfg_HasInitDataHashCodeOfPCConfig()                                                     (FALSE != FALSE)
#define Dem_Cfg_HasInitMonListForFuncOfPCConfig()                                                   (FALSE != FALSE)
#define Dem_Cfg_HasInitMonitorForEventOfPCConfig()                                                  (FALSE != FALSE)
#define Dem_Cfg_HasInitMonitorsForFuncOfPCConfig()                                                  (FALSE != FALSE)
#define Dem_Cfg_HasJ1939NodeIdIndOfPCConfig()                                                       (FALSE != FALSE)
#define Dem_Cfg_HasJ1939NodeIdOfPCConfig()                                                          (FALSE != FALSE)
#define Dem_Cfg_HasJ1939NodeIndicatorOfPCConfig()                                                   (FALSE != FALSE)
#define Dem_Cfg_HasMemoryBlockIdOfPCConfig()                                                        (TRUE != FALSE)
#define Dem_Cfg_HasMemoryBlockIdToMemoryEntryIdOfPCConfig()                                         (TRUE != FALSE)
#define Dem_Cfg_HasMemoryDataPtrOfPCConfig()                                                        (TRUE != FALSE)
#define Dem_Cfg_HasMemoryDataSizeOfPCConfig()                                                       (TRUE != FALSE)
#define Dem_Cfg_HasMemoryEntryInitOfPCConfig()                                                      (TRUE != FALSE)
#define Dem_Cfg_HasMemoryEntryOfPCConfig()                                                          (TRUE != FALSE)
#define Dem_Cfg_HasMemoryStatusOfPCConfig()                                                         (TRUE != FALSE)
#define Dem_Cfg_HasMidTableOfPCConfig()                                                             (FALSE != FALSE)
#define Dem_Cfg_HasMirrorDataOfPCConfig()                                                           (FALSE != FALSE)
#define Dem_Cfg_HasNormalIndicatorTableOfPCConfig()                                                 (FALSE != FALSE)
#define Dem_Cfg_HasObdIumprDataOfPCConfig()                                                         (FALSE != FALSE)
#define Dem_Cfg_HasObdIumprUpdatePendingOfPCConfig()                                                (FALSE != FALSE)
#define Dem_Cfg_HasPermanentDataOfPCConfig()                                                        (FALSE != FALSE)
#define Dem_Cfg_HasPidTableOfPCConfig()                                                             (FALSE != FALSE)
#define Dem_Cfg_HasPrestorageIndexOfPCConfig()                                                      (FALSE != FALSE)
#define Dem_Cfg_HasPrestorageOfPCConfig()                                                           (FALSE != FALSE)
#define Dem_Cfg_HasPrimaryChronologyOfPCConfig()                                                    (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryEntry_0OfPCConfig()                                                       (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryEntry_1OfPCConfig()                                                       (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryEntry_2OfPCConfig()                                                       (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryEntry_3OfPCConfig()                                                       (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryEntry_4OfPCConfig()                                                       (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryEntry_5OfPCConfig()                                                       (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryEntry_6OfPCConfig()                                                       (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryEntry_7OfPCConfig()                                                       (TRUE != FALSE)
#define Dem_Cfg_HasRatioIdTableOfPCConfig()                                                         (FALSE != FALSE)
#define Dem_Cfg_HasReadinessGroupTableOfPCConfig()                                                  (TRUE != FALSE)
#define Dem_Cfg_HasReadoutBufferOfPCConfig()                                                        (TRUE != FALSE)
#define Dem_Cfg_HasReportedEventsOfFilterOfPCConfig()                                               (TRUE != FALSE)
#define Dem_Cfg_HasSatelliteInfo0OfPCConfig()                                                       (TRUE != FALSE)
#define Dem_Cfg_HasSatelliteInfoOfPCConfig()                                                        (TRUE != FALSE)
#define Dem_Cfg_HasSatelliteTimeDebounceInfoOfPCConfig()                                            (FALSE != FALSE)
#define Dem_Cfg_HasSecondaryChronologyOfPCConfig()                                                  (FALSE != FALSE)
#define Dem_Cfg_HasSizeOfCallbackClearEventAllowedOfPCConfig()                                      (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfCallbackDtcStatusChangedOfPCConfig()                                       (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfCallbackGetFdcOfPCConfig()                                                 (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfCallbackJ1939DtcStatusChangedOfPCConfig()                                  (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfClearDTCTableOfPCConfig()                                                  (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfClearDtcNotificationFinishTableOfPCConfig()                                (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfClearDtcNotificationStartTableOfPCConfig()                                 (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfClientTableOfPCConfig()                                                    (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfDTCSelectorTableOfPCConfig()                                               (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfDataElementTableOfPCConfig()                                               (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfDebounceHiResTableOfPCConfig()                                             (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfDebounceLoResTableOfPCConfig()                                             (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfDtcGroupMaskOfPCConfig()                                                   (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfDtrStatusOfPCConfig()                                                      (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfDtrTableOfPCConfig()                                                       (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfEnableConditionFulfilledOfPCConfig()                                       (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfEnableConditionGroupCounterOfPCConfig()                                    (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfEnableConditionGroupStateOfPCConfig()                                      (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfEnableConditionGroupTableOfPCConfig()                                      (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfEnableConditionTableOfPCConfig()                                           (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfEventCycleStatusOfPCConfig()                                               (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfEventDataChangedOfPCConfig()                                               (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfEventDataCommitNumberOfPCConfig()                                          (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfEventDebounceValueOfPCConfig()                                             (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfEventInternalStatusOfPCConfig()                                            (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfEventStatusChangedOfPCConfig()                                             (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfEventTableOfPCConfig()                                                     (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfExtendedDataRecordIteratorTableOfPCConfig()                                (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfFilterInfoTableOfPCConfig()                                                (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfFilterReportedEventsOfPCConfig()                                           (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfFreezeFrameIteratorTableOfPCConfig()                                       (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfGlobalIndicatorStatesOfPCConfig()                                          (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfIndicatorBlinkingOfPCConfig()                                              (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfIndicatorContinuousOfPCConfig()                                            (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfIndicatorFastFlashOfPCConfig()                                             (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfIndicatorSlowFlashOfPCConfig()                                             (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfInitMonitorForEventOfPCConfig()                                            (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfInitMonitorsForFuncOfPCConfig()                                            (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfMemoryBlockIdToMemoryEntryIdOfPCConfig()                                   (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfMemoryEntryOfPCConfig()                                                    (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfMemoryStatusOfPCConfig()                                                   (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfObdIumprUpdatePendingOfPCConfig()                                          (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfPrestorageIndexOfPCConfig()                                                (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfPrimaryChronologyOfPCConfig()                                              (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfReadinessGroupTableOfPCConfig()                                            (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfReadoutBufferOfPCConfig()                                                  (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfReportedEventsOfFilterOfPCConfig()                                         (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfSatelliteInfoOfPCConfig()                                                  (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfSecondaryChronologyOfPCConfig()                                            (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfSpecialIndicatorTableOfPCConfig()                                          (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfStartIdx500miDenRatioTableOfPCConfig()                                     (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfStorageConditionFulfilledOfPCConfig()                                      (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfStorageConditionGroupCounterOfPCConfig()                                   (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfStorageConditionGroupTableOfPCConfig()                                     (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfStorageConditionTableOfPCConfig()                                          (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfSupportedMidsTableOfPCConfig()                                             (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfTimeSeriesChronologyOfPCConfig()                                           (TRUE != FALSE)
#define Dem_Cfg_HasSpecialIndicatorTableOfPCConfig()                                                (FALSE != FALSE)
#define Dem_Cfg_HasStartIdx500miDenRatioTableOfPCConfig()                                           (FALSE != FALSE)
#define Dem_Cfg_HasStatusDataOfPCConfig()                                                           (TRUE != FALSE)
#define Dem_Cfg_HasStorageConditionFulfilledOfPCConfig()                                            (FALSE != FALSE)
#define Dem_Cfg_HasStorageConditionGroupCounterOfPCConfig()                                         (FALSE != FALSE)
#define Dem_Cfg_HasStorageConditionGroupTableIndOfPCConfig()                                        (FALSE != FALSE)
#define Dem_Cfg_HasStorageConditionGroupTableOfPCConfig()                                           (FALSE != FALSE)
#define Dem_Cfg_HasStorageConditionInitTableOfPCConfig()                                            (FALSE != FALSE)
#define Dem_Cfg_HasStorageConditionTableOfPCConfig()                                                (FALSE != FALSE)
#define Dem_Cfg_HasSupportedMidsTableOfPCConfig()                                                   (FALSE != FALSE)
#define Dem_Cfg_HasTimeSeriesChronologyOfPCConfig()                                                 (FALSE != FALSE)
#define Dem_Cfg_HasTimeSeriesEntryInitOfPCConfig()                                                  (TRUE != FALSE)
#define Dem_Cfg_HasUseOBDIIInVariantOfPCConfig()                                                    (TRUE != FALSE)
#define Dem_Cfg_HasUsePermanentInVariantOfPCConfig()                                                (FALSE != FALSE)
#define Dem_Cfg_HasUseWWHOBDInVariantOfPCConfig()                                                   (TRUE != FALSE)
/** 
  \}
*/ 

/** 
  \defgroup  Dem_CfgPCExistsEnumMacros  Dem_Cfg Exists Enum Macros (PRE_COMPILE)
  \brief  These macros can be used to deactivate enumeration based code sequences if the enumeration value does not exist in the configuration data.
  \{
*/ 
#define Dem_Cfg_ExistsDEM_CFG_DEBOUNCETYPE_COUNTEREventDebounceAlgorithmOfDebounceTable()           (TRUE != FALSE)
#define Dem_Cfg_ExistsDEM_CFG_DEBOUNCETYPE_TIMEREventDebounceAlgorithmOfDebounceTable()             (FALSE != FALSE)
#define Dem_Cfg_ExistsDEM_CFG_DEBOUNCETYPE_EXTERNALEventDebounceAlgorithmOfDebounceTable()          (TRUE != FALSE)
#define Dem_Cfg_ExistsDEM_CFG_DEBOUNCETYPE_INVALIDEventDebounceAlgorithmOfDebounceTable()           (TRUE != FALSE)
#define Dem_Cfg_ExistsDEM_EVENT_KIND_BSWEventKindOfEventTable()                                     (TRUE != FALSE)
#define Dem_Cfg_ExistsDEM_EVENT_KIND_SWCEventKindOfEventTable()                                     (TRUE != FALSE)
#define Dem_Cfg_ExistsDEM_EVENT_SIGNIFICANCE_OCCURRENCEEventSignificanceOfEventTable()              (FALSE != FALSE)
#define Dem_Cfg_ExistsDEM_EVENT_SIGNIFICANCE_FAULTEventSignificanceOfEventTable()                   (TRUE != FALSE)
/** 
  \}
*/ 

/** 
  \defgroup  Dem_CfgPCIncrementDataMacros  Dem_Cfg Increment Data Macros (PRE_COMPILE)
  \brief  These macros can be used to increment VAR data with numerical nature.
  \{
*/ 
#define Dem_Cfg_IncClearDTCTable(Index)                                                             Dem_Cfg_GetClearDTCTable(Index)++
#define Dem_Cfg_IncDTCSelectorTable(Index)                                                          Dem_Cfg_GetDTCSelectorTable(Index)++
#define Dem_Cfg_IncDtrStatus(Index)                                                                 
#define Dem_Cfg_IncEnableConditionGroupCounter(Index)                                               Dem_Cfg_GetEnableConditionGroupCounter(Index)++
#define Dem_Cfg_IncEnableConditionGroupState(Index)                                                 Dem_Cfg_GetEnableConditionGroupState(Index)++
#define Dem_Cfg_IncEventCycleStatus(Index)                                                          
#define Dem_Cfg_IncEventDataCommitNumber(Index)                                                     Dem_Cfg_GetEventDataCommitNumber(Index)++
#define Dem_Cfg_IncEventDebounceValue(Index)                                                        Dem_Cfg_GetEventDebounceValue(Index)++
#define Dem_Cfg_IncEventInternalStatus(Index)                                                       Dem_Cfg_GetEventInternalStatus(Index)++
#define Dem_Cfg_IncFilterReportedEvents(Index)                                                      Dem_Cfg_GetFilterReportedEvents(Index)++
#define Dem_Cfg_IncGlobalIndicatorStates(Index)                                                     
#define Dem_Cfg_IncIndicatorBlinking(Index)                                                         
#define Dem_Cfg_IncIndicatorContinuous(Index)                                                       
#define Dem_Cfg_IncIndicatorFastFlash(Index)                                                        
#define Dem_Cfg_IncIndicatorSlowFlash(Index)                                                        
#define Dem_Cfg_IncMemoryStatus(Index)                                                              Dem_Cfg_GetMemoryStatus(Index)++
#define Dem_Cfg_IncMirrorData()                                                                     
#define Dem_Cfg_IncPrestorageIndex(Index)                                                           
#define Dem_Cfg_IncPrimaryChronology(Index)                                                         Dem_Cfg_GetPrimaryChronology(Index)++
#define Dem_Cfg_IncSecondaryChronology(Index)                                                       
#define Dem_Cfg_IncStorageConditionGroupCounter(Index)                                              
#define Dem_Cfg_IncTimeSeriesChronology(Index)                                                      
/** 
  \}
*/ 

/** 
  \defgroup  Dem_CfgPCDecrementDataMacros  Dem_Cfg Decrement Data Macros (PRE_COMPILE)
  \brief  These macros can be used to decrement VAR data with numerical nature.
  \{
*/ 
#define Dem_Cfg_DecClearDTCTable(Index)                                                             Dem_Cfg_GetClearDTCTable(Index)--
#define Dem_Cfg_DecDTCSelectorTable(Index)                                                          Dem_Cfg_GetDTCSelectorTable(Index)--
#define Dem_Cfg_DecDtrStatus(Index)                                                                 
#define Dem_Cfg_DecEnableConditionGroupCounter(Index)                                               Dem_Cfg_GetEnableConditionGroupCounter(Index)--
#define Dem_Cfg_DecEnableConditionGroupState(Index)                                                 Dem_Cfg_GetEnableConditionGroupState(Index)--
#define Dem_Cfg_DecEventCycleStatus(Index)                                                          
#define Dem_Cfg_DecEventDataCommitNumber(Index)                                                     Dem_Cfg_GetEventDataCommitNumber(Index)--
#define Dem_Cfg_DecEventDebounceValue(Index)                                                        Dem_Cfg_GetEventDebounceValue(Index)--
#define Dem_Cfg_DecEventInternalStatus(Index)                                                       Dem_Cfg_GetEventInternalStatus(Index)--
#define Dem_Cfg_DecFilterReportedEvents(Index)                                                      Dem_Cfg_GetFilterReportedEvents(Index)--
#define Dem_Cfg_DecGlobalIndicatorStates(Index)                                                     
#define Dem_Cfg_DecIndicatorBlinking(Index)                                                         
#define Dem_Cfg_DecIndicatorContinuous(Index)                                                       
#define Dem_Cfg_DecIndicatorFastFlash(Index)                                                        
#define Dem_Cfg_DecIndicatorSlowFlash(Index)                                                        
#define Dem_Cfg_DecMemoryStatus(Index)                                                              Dem_Cfg_GetMemoryStatus(Index)--
#define Dem_Cfg_DecMirrorData()                                                                     
#define Dem_Cfg_DecPrestorageIndex(Index)                                                           
#define Dem_Cfg_DecPrimaryChronology(Index)                                                         Dem_Cfg_GetPrimaryChronology(Index)--
#define Dem_Cfg_DecSecondaryChronology(Index)                                                       
#define Dem_Cfg_DecStorageConditionGroupCounter(Index)                                              
#define Dem_Cfg_DecTimeSeriesChronology(Index)                                                      
/** 
  \}
*/ 

/** 
  \defgroup  Dem_CfgPCAddDataMacros  Dem_Cfg Add Data Macros (PRE_COMPILE)
  \brief  These macros can be used to add VAR data with numerical nature.
  \{
*/ 
#define Dem_Cfg_AddClearDTCTable(Index, Value)                                                      Dem_Cfg_SetClearDTCTable(Index, (Dem_Cfg_GetClearDTCTable(Index) + Value))
#define Dem_Cfg_AddDTCSelectorTable(Index, Value)                                                   Dem_Cfg_SetDTCSelectorTable(Index, (Dem_Cfg_GetDTCSelectorTable(Index) + Value))
#define Dem_Cfg_AddDtrStatus(Index, Value)                                                          
#define Dem_Cfg_AddEnableConditionGroupCounter(Index, Value)                                        Dem_Cfg_SetEnableConditionGroupCounter(Index, (Dem_Cfg_GetEnableConditionGroupCounter(Index) + Value))
#define Dem_Cfg_AddEnableConditionGroupState(Index, Value)                                          Dem_Cfg_SetEnableConditionGroupState(Index, (Dem_Cfg_GetEnableConditionGroupState(Index) + Value))
#define Dem_Cfg_AddEventCycleStatus(Index, Value)                                                   
#define Dem_Cfg_AddEventDataCommitNumber(Index, Value)                                              Dem_Cfg_SetEventDataCommitNumber(Index, (Dem_Cfg_GetEventDataCommitNumber(Index) + Value))
#define Dem_Cfg_AddEventDebounceValue(Index, Value)                                                 Dem_Cfg_SetEventDebounceValue(Index, (Dem_Cfg_GetEventDebounceValue(Index) + Value))
#define Dem_Cfg_AddEventInternalStatus(Index, Value)                                                Dem_Cfg_SetEventInternalStatus(Index, (Dem_Cfg_GetEventInternalStatus(Index) + Value))
#define Dem_Cfg_AddFilterReportedEvents(Index, Value)                                               Dem_Cfg_SetFilterReportedEvents(Index, (Dem_Cfg_GetFilterReportedEvents(Index) + Value))
#define Dem_Cfg_AddGlobalIndicatorStates(Index, Value)                                              
#define Dem_Cfg_AddIndicatorBlinking(Index, Value)                                                  
#define Dem_Cfg_AddIndicatorContinuous(Index, Value)                                                
#define Dem_Cfg_AddIndicatorFastFlash(Index, Value)                                                 
#define Dem_Cfg_AddIndicatorSlowFlash(Index, Value)                                                 
#define Dem_Cfg_AddMemoryStatus(Index, Value)                                                       Dem_Cfg_SetMemoryStatus(Index, (Dem_Cfg_GetMemoryStatus(Index) + Value))
#define Dem_Cfg_AddMirrorData(Value)                                                                
#define Dem_Cfg_AddPrestorageIndex(Index, Value)                                                    
#define Dem_Cfg_AddPrimaryChronology(Index, Value)                                                  Dem_Cfg_SetPrimaryChronology(Index, (Dem_Cfg_GetPrimaryChronology(Index) + Value))
#define Dem_Cfg_AddSecondaryChronology(Index, Value)                                                
#define Dem_Cfg_AddStorageConditionGroupCounter(Index, Value)                                       
#define Dem_Cfg_AddTimeSeriesChronology(Index, Value)                                               
/** 
  \}
*/ 

/** 
  \defgroup  Dem_CfgPCSubstractDataMacros  Dem_Cfg Substract Data Macros (PRE_COMPILE)
  \brief  These macros can be used to substract VAR data with numerical nature.
  \{
*/ 
#define Dem_Cfg_SubClearDTCTable(Index, Value)                                                      Dem_Cfg_SetClearDTCTable(Index, (Dem_Cfg_GetClearDTCTable(Index) - Value))
#define Dem_Cfg_SubDTCSelectorTable(Index, Value)                                                   Dem_Cfg_SetDTCSelectorTable(Index, (Dem_Cfg_GetDTCSelectorTable(Index) - Value))
#define Dem_Cfg_SubDtrStatus(Index, Value)                                                          
#define Dem_Cfg_SubEnableConditionGroupCounter(Index, Value)                                        Dem_Cfg_SetEnableConditionGroupCounter(Index, (Dem_Cfg_GetEnableConditionGroupCounter(Index) - Value))
#define Dem_Cfg_SubEnableConditionGroupState(Index, Value)                                          Dem_Cfg_SetEnableConditionGroupState(Index, (Dem_Cfg_GetEnableConditionGroupState(Index) - Value))
#define Dem_Cfg_SubEventCycleStatus(Index, Value)                                                   
#define Dem_Cfg_SubEventDataCommitNumber(Index, Value)                                              Dem_Cfg_SetEventDataCommitNumber(Index, (Dem_Cfg_GetEventDataCommitNumber(Index) - Value))
#define Dem_Cfg_SubEventDebounceValue(Index, Value)                                                 Dem_Cfg_SetEventDebounceValue(Index, (Dem_Cfg_GetEventDebounceValue(Index) - Value))
#define Dem_Cfg_SubEventInternalStatus(Index, Value)                                                Dem_Cfg_SetEventInternalStatus(Index, (Dem_Cfg_GetEventInternalStatus(Index) - Value))
#define Dem_Cfg_SubFilterReportedEvents(Index, Value)                                               Dem_Cfg_SetFilterReportedEvents(Index, (Dem_Cfg_GetFilterReportedEvents(Index) - Value))
#define Dem_Cfg_SubGlobalIndicatorStates(Index, Value)                                              
#define Dem_Cfg_SubIndicatorBlinking(Index, Value)                                                  
#define Dem_Cfg_SubIndicatorContinuous(Index, Value)                                                
#define Dem_Cfg_SubIndicatorFastFlash(Index, Value)                                                 
#define Dem_Cfg_SubIndicatorSlowFlash(Index, Value)                                                 
#define Dem_Cfg_SubMemoryStatus(Index, Value)                                                       Dem_Cfg_SetMemoryStatus(Index, (Dem_Cfg_GetMemoryStatus(Index) - Value))
#define Dem_Cfg_SubMirrorData(Value)                                                                
#define Dem_Cfg_SubPrestorageIndex(Index, Value)                                                    
#define Dem_Cfg_SubPrimaryChronology(Index, Value)                                                  Dem_Cfg_SetPrimaryChronology(Index, (Dem_Cfg_GetPrimaryChronology(Index) - Value))
#define Dem_Cfg_SubSecondaryChronology(Index, Value)                                                
#define Dem_Cfg_SubStorageConditionGroupCounter(Index, Value)                                       
#define Dem_Cfg_SubTimeSeriesChronology(Index, Value)                                               
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
/** 
  \defgroup  Dem_CfgLTHasMacros  Dem_Cfg Has Macros (LINK)
  \brief  These macros can be used to detect at runtime a deactivated piece of information. TRUE in the CONFIGURATION_VARIANT PRE-COMPILE, TRUE or FALSE in the CONFIGURATION_VARIANT POST-BUILD.
  \{
*/ 
#define Dem_HasLTConfig()                                                                           (FALSE != FALSE)
/** 
  \}
*/ 

  /* PRQA L:Macros_3453 */
/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL ACCESS FUNCTION MACROS
**********************************************************************************************************************/



/**********************************************************************************************************************
  GLOBAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
 /*  Return type of Dem_Cfg_EventNormalIndicatorIterGet() - returns: eventIndicatorIndex  */ 
typedef uint8                                                         Dem_Cfg_NormalIndicatorIndexType; 

typedef struct Dem_Cfg_TimeSeriesEntryCompanionType_s {
  uint8 ClientCounter;
  uint8 ReadoutStatus;
}                                                                     Dem_Cfg_TimeSeriesEntryCompanionType; 

typedef uint16                                                        Dem_Cfg_MaxDebounceValuesType; 

typedef uint8                                                         Dem_Cfg_DebounceLoResTimerType; 

typedef volatile P2VAR(Dem_Com_ProcessorWordType, TYPEDEF, DEM_VAR_NOINIT) Dem_Cfg_ProcessorWordPtrType; 

typedef volatile P2VAR(Dem_SatelliteData_DataType, TYPEDEF, DEM_VAR_NOINIT) Dem_Cfg_SatelliteDataPtrType; 

typedef volatile P2VAR(Dem_SatelliteData_ExtendedDataType, TYPEDEF, DEM_VAR_NOINIT) Dem_Cfg_SatelliteExtendedDataPtrType; 

typedef volatile P2CONST(Dem_SatelliteData_ExtendedDataType, TYPEDEF, DEM_VAR_NOINIT) Dem_Cfg_SatelliteExtendedDataConstPtrType; 

typedef volatile P2VAR(Dem_Cfg_MaxDebounceValuesType, TYPEDEF, DEM_VAR_NOINIT) Dem_Cfg_MaxDebounceValuesPtrType; 

typedef volatile P2CONST(Dem_Cfg_MaxDebounceValuesType, TYPEDEF, DEM_VAR_NOINIT) Dem_Cfg_MaxDebounceValuesConstPtrType; 

typedef P2VAR(Dem_Cfg_DebounceLoResTimerType, TYPEDEF, DEM_VAR_NOINIT) Dem_Cfg_DebounceLoResTimerPtrType; 

typedef P2CONST(Dem_Cfg_DebounceLoResTimerType, TYPEDEF, DEM_VAR_NOINIT) Dem_Cfg_DebounceLoResTimerConstPtrType; 

typedef struct Dem_Cfg_SatelliteInfoType0_s {
  volatile Dem_SatelliteData_DataType SatelliteData[ 16 ];
  volatile Dem_Com_ProcessorWordType  SatelliteStatus;
}                                                                     Dem_Cfg_SatelliteInfoType0;            /* Data structure for DEM satellite on partition "0" */ 

 /*  Return type of Dem_Cfg_EventRatioIdIdx() and Dem_Cfg_ObdRatioIdIterGet() - returns: ratioIdIndex   */ 
typedef uint8                                                         Dem_RatioIdIndexType; 

typedef struct Dem_Cfg_AdminDataType_s {
  uint16 ImplementationVersion;
  uint16 ConfigurationId;
  uint16 CycleCounter[ 3 /*DEM_CFG_GLOBAL_CYCLE_COUNT*/];
  uint8  MemoryOverflow;                                                        /* (DEM_CFG_DATA_OVFLIND == STD_ON) || (DEM_CFG_SUPPORT_OVFLIND_API == STD_ON) */
}                                                                     Dem_Cfg_AdminDataType; 

typedef struct Dem_Cfg_StatusDataType_s {
  uint16         FirstFailedEvent;
  uint16         FirstConfirmedEvent;
  uint16         MostRecentFailedEvent;
  uint16         MostRecentConfmdEvent;
  uint8          TripCount[ 16 /*DEM_G_NUMBER_OF_EVENTS (incl. #0)*/];          /* (DEM_CFG_SUPPORT_MULTITRIP == STD_ON) || use HealingCycleCounter */
  volatile uint8 EventStatus[ 16 /*DEM_G_NUMBER_OF_EVENTS (incl. #0)*/];
}                                                                     Dem_Cfg_StatusDataType; 

typedef struct Dem_Cfg_PrimaryEntryType_s {
  uint32 Timestamp;
  uint16 AgingCounter;
  uint16 EventId;
  uint8  SnapshotData[ 1 /*DEM_CFG_MAX_NUM_SNAPSHOTS*/][ 1 /*unused*/];         /* (DEM_CFG_SUPPORT_SRECS == STD_ON) */
  uint8  OccurrenceCounter;
  uint8  SnapshotHeader;                                                        /* (DEM_CFG_SUPPORT_SRECS == STD_ON) */
}                                                                     Dem_Cfg_PrimaryEntryType; 

typedef P2VAR(Dem_Cfg_PrimaryEntryType, TYPEDEF, DEM_SHARED_DATA)     Dem_SharedMemoryEntryPtrType; 

typedef P2CONST(Dem_Cfg_PrimaryEntryType, TYPEDEF, DEM_SHARED_DATA)   Dem_ConstSharedMemoryEntryPtrType; 

typedef struct Dem_Cfg_TimeSeriesEntryType_s {
  uint32 Timestamp;
  uint16 EventId;
}                                                                     Dem_Cfg_TimeSeriesEntryType; 

typedef struct Dem_Cfg_PermanentDataEntryType_s { /* Unused typedef, as DEM_CFG_GLOBAL_PERMANENT_SIZE= 0 */
  uint16 EventId;
  uint8  Status;
}                                                                     Dem_Cfg_PermanentDataEntryType; 

typedef struct Dem_Cfg_PermanentDataType_s { /* Unused typedef, as DEM_CFG_GLOBAL_PERMANENT_SIZE= 0 */
  Dem_Cfg_PermanentDataEntryType PermanentDataEntry[ 1 /*unused*/];
  uint16                         InitPattern;
}                                                                     Dem_Cfg_PermanentDataType; 

typedef struct Dem_Cfg_FreezeFrameDataEntryType_s { /* Unused typedef, as DEM_CFG_GLOBAL_FREEZEFRAME_SIZE= 0 */
  uint32          Timestamp;
  volatile uint16 EventId;
  uint8           FreezeFrameData[ 1 /*unused*/];
  boolean         IsVisible;
}                                                                     Dem_Cfg_FreezeFrameDataEntryType; 

typedef Dem_Cfg_FreezeFrameDataEntryType                              Dem_Cfg_FreezeFrameDataType[1];        /* size: [unused] Unused typedef, as (DEM_CFG_SUPPORT_OBDII == STD_OFF) */ 

typedef sint16                                                        Dem_Cfg_DebounceDataType[1];           /* size: [unused] Unused typedef, as DEM_CFG_GLOBAL_DEBOUNCE_STORAGE_EVENT_COUNT= 0 */ 

typedef uint8                                                         Dem_Cfg_EventAvailableDataType[2];     /* size: [ceiling( DEM_G_NUMBER_OF_EVENTS / 8 )] Unused typedef, as DEM_CFG_SUPPORT_EVENTAVAILABLE_NV==STD_OFF */ 

typedef struct Dem_Cfg_ObdIumprDataType_s { /* Unused typedef, as DEM_G_NUMBER_OF_RATIO_IDS = 0 */
  uint16         Numerator[ 1 /*unused*/];
  uint16         Denominator[ 1 /*unused*/];
  uint16         GeneralDenominator;
  volatile uint8 Status[ 1 /*unused*/];
  uint8          DenominatorConditionStatusReached;
  uint8          DenominatorConditionStatusInhibited;
  uint8          GlobalHybridStatus;
  uint8          GlobalNumeratorsLocked;
}                                                                     Dem_Cfg_ObdIumprDataType; 

typedef struct Dem_Cfg_DtrDataType_s { /* Unused typedef, as DEM_CFG_MAX_NUMBER_CONFIGURABLE_DTRS = 0 */
  uint16 TestValue[ 1 /*unused*/];
  uint16 LowLimValue[ 1 /*unused*/];
  uint16 UppLimValue[ 1 /*unused*/];
}                                                                     Dem_Cfg_DtrDataType; 

typedef struct Dem_Cfg_AgingDataType_s { /* Unused typedef, as DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS==STD_OFF && DEM_CFG_DATA_AGED_COUNTER==STD_OFF */
  uint8 AgedCounter[ 1 /*unused*/];
}                                                                     Dem_Cfg_AgingDataType; 

typedef struct Dem_Cfg_CycleCounterDataType_s { /* Unused typedef, as DEM_CFG_SUPPORT_MEM_INDEPENDENT_CYCLE_COUNTERS==STD_OFF */
  uint8 FaultPendingCounter[ 1 /*unused*/];
}                                                                     Dem_Cfg_CycleCounterDataType; 

typedef struct Dem_Cfg_PrestorageEntryType_s { /* Unused typedef, as DEM_CFG_GLOBAL_PRESTORED_FF_SIZE= 0 */
  uint16 EventId;                                                               /* An allocated buffer element holds here the EventId. When this buffer element is part of the free list, it is the index of next free buffer. */
  uint8  SnapshotData[ 1 /*unused*/];                                           /* (DEM_CFG_SUPPORT_SRECS == STD_ON) */
  uint8  State;
}                                                                     Dem_Cfg_PrestorageEntryType; 

typedef Dem_Cfg_PrestorageEntryType                                   Dem_Cfg_PrestorageType[1];             /* size: [1 + DEM_CFG_GLOBAL_PRESTORED_FF_SIZE] */ 

typedef uint8                                                         Dem_Cfg_MemoryEntryHandleType;         /* Number of valid entries in Dem_Cfg_MemoryBlockIdToMemoryEntryId. */ 

typedef uint8                                                         Dem_Cfg_MemoryIndexType;               /* Number of NV blocks, see Dem_Cfg_GlobalNvBlockCount(). */ 

typedef uint8_least                                                   Dem_Cfg_MemoryIndexIterType;           /* Type to iterate over memory indexes */ 

typedef uint8                                                         Dem_Cfg_DtrStatusType; 

 /*  Iterator data for Dem_Cfg_FilterData_InfoType  */ 
typedef union Dem_Cfg_Union_ChronoIterType_u { /* PRQA S 0750 */ /* MD_MSR_Union */
  Dem_Cfg_MemoryIndexType                      ChronoIter;                      /* chronology iterator for chronological order filtering */
  uint16                                       EventIndex;                      /* Event iterator for linear order filtering */
  uint8                                        PermanentIndex;                  /* permanent entry iterator for permanent filtering */
  Dem_FilterData_0x1956_ReadinessGroupIterType ReadinessGroupIter;              /* Readiness Group iterator */
  Dem_Dcm_ERec_ERecNumberIterType              ERecIterator;                    /* Extended data record iterator */
}                                                                     Dem_Cfg_Union_ChronoIterType; 

 /*  Table indexes for Dem_Cfg_FilterData_InfoType  */ 
typedef union Dem_Cfg_Union_TableIndexType_u { /* PRQA S 0750 */ /* MD_MSR_Union */
  uint8                 ReadinessGroupIdx;                                      /* Readiness Group Index */
  Dem_Cfg_ERecIndexType DataCollectionTableIdx;                                 /* Data collection table index of extended data record */
}                                                                     Dem_Cfg_Union_TableIndexType; 

typedef Dem_Com_ProcessorWordType                                     Dem_Cfg_ProcessedCombinedDTCGroupType[1];    /* size: [1] (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_OFF) */ 

 /*  Filter data for Dcm requests   */ 
typedef struct Dem_Cfg_FilterData_InfoType_s {
  Dem_Cfg_Union_ChronoIterType            Iterator;                             /* Chronology Iterator */
  Dem_FilterData_DTCFilteringStrategyType FilterDtcStrategy;                    /* Active DTC filtering strategy */
  uint16                                  EventId;                              /* Event Id for J1939 Freeze Frame filtering */
  uint16                                  NumberOfDTCsTested;                   /* Counter for limiting number of tested DTCs during J1939Dcm DTC filtering */
  Dem_Cfg_Union_TableIndexType            TableIndex;                           /* Table Index for filtering */
  Dem_DTCSeverityType                     SeverityMask;                         /* Severity mask filter */
  Dem_FilterData_FilterType               FilterState;                          /* Filter state */
  Dem_J1939DcmDTCStatusFilterType         DTCStatusFilterType;                  /* J1939Dcm DTC status filter type */
  sint8                                   FaultDetectionCounter;                /* FaultDetectionCounter for FDC filter */
  uint8                                   StatusMask;                           /* Status mask filter */
  uint8                                   MemoryId;                             /* Filtered event memory */
  uint8                                   FilterFlags;                          /* Filter flags */
  uint8                                   NodeId;                               /* Node Id */
}                                                                     Dem_Cfg_FilterData_InfoType; 

 /*  Snapshot entry handle type  */ 
typedef struct Dem_Cfg_SnapshotEntry_Handle_s {
  uint16                        EventId;                                        /* Event ID */
  Dem_Cfg_MemoryEntryHandleType MemoryEntryId;                                  /* Memory entry handle */
  Dem_Cfg_SRecIndexType         SnapshotIteratorIndex;                          /* snapshot record index */
  uint8                         SnapshotEntryIndex;                             /* Snapshot entry index */
}                                                                     Dem_Cfg_SnapshotEntry_IterType; 

typedef P2VAR(Dem_Cfg_SnapshotEntry_IterType, TYPEDEF, AUTOMATIC)     Dem_Cfg_SnapshotEntry_IterPtrType;     /* PRQA S 0779 */ /* MD_MSR_Rule5.2 */ 

 /*  FreezeFrameIterator data for Dcm requests  */ 
typedef struct Dem_Cfg_FreezeFrameIterator_FilterType_s {
  Dem_Cfg_SnapshotEntry_IterType        SnapshotEntryIter;                      /* Iterator for the snapshot entries */
  uint16                                EventId;                                /* Event Id for J1939 Freeze Frame filtering */
  Dem_FreezeFrameIterator_DTCFormatType FilterDTCFormat;                        /*  DTCFormat: UDS, OBD, J1939, INIT (no filter)  */
  Dem_J1939DcmSetFreezeFrameFilterType  FreezeFrameKind;                        /* Freeze Frame Kind for J1939 Freeze Frame filtering */
  Dem_Cfg_MemoryIndexType               MemoryIndex;                            /* Memory entry type */
  uint8                                 TimeSeriesRecordNumber;                 /* time series iterator position */
  uint8                                 NodeId;                                 /* Node Id for J1939 Freeze Frame filtering */
  uint8                                 FilterState;                            /* Filter state for J1939 Freeze Frame filtering */
}                                                                     Dem_Cfg_FreezeFrameIterator_FilterType; 

 /*  ExtendedDataRecordIterator data for Dcm requests  */ 
typedef struct Dem_Cfg_ExtendedDataRecordIterator_FilterType_s {
  Dem_Dcm_ERec_ERecNumberIterType ERecIterator;                                 /* Iterator for events of extended data record */
  Dem_DTCOriginType               DTCOrigin;                                    /* Dtc origin */
  Dem_Cfg_ERecIndexType           DataCollectionTableIdx;                       /* Data collection table index of extended data record */
  Dem_DTCFormatType               DTCFormat;                                    /* Dtc format */
  Dem_Cfg_MemoryIndexType         StoredMemoryIndex;                            /* Index to next memory entry */
}                                                                     Dem_Cfg_ExtendedDataRecordIterator_FilterType; 

typedef Dem_Com_ProcessorWordType                                     Dem_Cfg_ReportedEventsType[1];         /* size: [ceiling( DEM_G_NUMBER_OF_EVENTS / 32 )] = (((DEM_G_NUMBER_OF_EVENTS - 1) / 32) + 1), here: 1. See define DEM_CFG_GLOBAL_PROCESSORWORDS_PER_REPORTEDEVENTSTYPE */ 

typedef uint16                                                        Dem_Cfg_IndicatorContinuousType[1];    /* size = DEM_G_MAX_NUMBER_J1939_NODES */ 

typedef uint16                                                        Dem_Cfg_IndicatorBlinkingType[1];      /* size = DEM_G_MAX_NUMBER_J1939_NODES */ 

typedef uint16                                                        Dem_Cfg_IndicatorFastFlashType[1];     /* size = DEM_G_MAX_NUMBER_J1939_NODES */ 

typedef uint16                                                        Dem_Cfg_IndicatorSlowFlashType[1];     /* size = DEM_G_MAX_NUMBER_J1939_NODES */ 

typedef uint8                                                         Dem_Cfg_GlobalIndicatorStatesType[1];    /* size = DEM_G_MAX_NUMBER_J1939_NODES */ 

typedef uint8                                                         Dem_Cfg_PrestorageIndexType;           /* Span the index values of buffer slots in Dem_Cfg_Prestorage[], i.e. (/DemGeneral/DemMaxNumberPrestoredFF + 1) = 1 entries with index values in range [0..0]. */ 

 /*  Temporary buffer for interaction with NvM  */ 
typedef union Dem_Cfg_CommitBufferType_u { /* PRQA S 0750 */ /* MD_MSR_Union */
  uint8                    mRaw[ 1 ];
  Dem_Cfg_AdminDataType    mAdmin;
  Dem_Cfg_StatusDataType   mStatus;
  Dem_Cfg_PrimaryEntryType mPrimary;
}                                                                     Dem_Cfg_CommitBufferType; 

 /*  Iterator for extended data record types.  */ 
typedef struct Dem_Cfg_DTCReadoutBuffer_ExtendedDataIteratorType_s {
  Dem_ExtendedEntry_IterType ExtendedEntryIter;                                 /* Iterator for the extended entries */
  uint8                      ExtendedEntryIndex;                                /* Extended entry index */
}                                                                     Dem_Cfg_DTCReadoutBuffer_ExtendedDataIteratorType; 

typedef P2VAR(Dem_Cfg_DTCReadoutBuffer_ExtendedDataIteratorType, TYPEDEF, AUTOMATIC) Dem_Cfg_DTCReadoutBuffer_ExtendedDataIteratorPtrType;    /* PRQA S 0779 */ /* MD_MSR_Rule5.2 */ 

typedef P2CONST(Dem_Cfg_DTCReadoutBuffer_ExtendedDataIteratorType, TYPEDEF, AUTOMATIC) Dem_Cfg_DTCReadoutBuffer_ExtendedDataIteratorConstPtrType;    /* PRQA S 0779 */ /* MD_MSR_Rule5.2 */ 

 /*  Iterator for snapshot record types.  */ 
typedef struct Dem_Cfg_DTCReadoutBuffer_SnapshotDataIteratorType_s {
  Dem_Cfg_ComplexIterType        SourceIterator;                                /* Iterator for the different sources */
  Dem_Cfg_SnapshotEntry_IterType SnapshotEntryIter;                             /* Iterator for the snapshot entries */
}                                                                     Dem_Cfg_DTCReadoutBuffer_SnapshotDataIteratorType; 

typedef P2VAR(Dem_Cfg_DTCReadoutBuffer_SnapshotDataIteratorType, TYPEDEF, AUTOMATIC) Dem_Cfg_DTCReadoutBuffer_SnapshotDataIteratorPtrType;    /* PRQA S 0779 */ /* MD_MSR_Rule5.2 */ 

typedef P2CONST(Dem_Cfg_DTCReadoutBuffer_SnapshotDataIteratorType, TYPEDEF, AUTOMATIC) Dem_Cfg_DTCReadoutBuffer_SnapshotDataIteratorConstPtrType;    /* PRQA S 0779 */ /* MD_MSR_Rule5.2 */ 

 /*  Buffer for OBD Freeze Frame Data used in Dem_Cfg_ReadoutBufferEntryType.  */ 
typedef struct Dem_Cfg_ReadOutBufferFreezeFrameDataEntryType_s {
  uint8   ObdFreezeFrame[ 1 /*unused*/];
  boolean IsStored;                                                             /* TRUE if event has stored OBD Freeze Frame */
}                                                                     Dem_Cfg_ReadOutBufferFreezeFrameDataEntryType; 

typedef P2VAR(Dem_Cfg_ReadOutBufferFreezeFrameDataEntryType, TYPEDEF, DEM_VAR_NOINIT) Dem_Cfg_ReadOutBufferFreezeFrameDataEntryPtrType; 

 /*  Buffer for subevent entry, one for each subevent.  */ 
typedef struct Dem_Cfg_ReadoutBufferDataType_s {
  Dem_Cfg_PrimaryEntryType                          Data;                       /* Backed event data */
  Dem_Cfg_DTCReadoutBuffer_ExtendedDataIteratorType ExtendedIterator;           /* Internal state for reporting ExtendedData record(s) */
  Dem_Cfg_DTCReadoutBuffer_SnapshotDataIteratorType SnapshotIterator;           /* Internal state for reporting SnapshotData record(s) */
  uint16                                            EventId;                    /* Subevent ID */
}                                                                     Dem_Cfg_ReadoutBufferDataType; 

typedef P2VAR(Dem_Cfg_ReadoutBufferDataType, TYPEDEF, DEM_VAR_NOINIT) Dem_Cfg_ReadoutBufferDataPtrType; 

 /*  Buffer for statistical data stored outside of the event entry.  */ 
typedef struct Dem_Cfg_ReadoutMemIndeCounterType_s { /* Unused typedef, as DEM_CFG_SUPPORT_MEM_INDEPENDENT_CYCLE_COUNTERS==STD_OFF && and no event memory independent data elements requiring protection supported */
  uint8 FaultPendingCounter;
}                                                                     Dem_Cfg_ReadoutMemIndeCounterType; 

typedef P2CONST(Dem_Cfg_ReadoutMemIndeCounterType, TYPEDEF, AUTOMATIC) Dem_Cfg_ReadoutMemIndeCounterPtrType;    /* PRQA S 0779 */ /* MD_MSR_Rule5.2 */ 

 /*  Buffer for Event Data, used after calling Dem_DisableDTCRecordUpdate().  */ 
typedef struct Dem_Cfg_ReadoutBufferEntryType_s {
  Dem_Cfg_ReadoutBufferDataType                 ReadOutBufferData[ 1 ];         /* General: Backed (sub-)event data */
  Dem_DTCReadoutBuffer_SnapshotSourceType       Source;                         /* Data record selection: The source of a selected snapshot */
  uint8                                         MemoryId;                       /* General: MemoryId of this request */
  uint8                                         State;                          /* General: Internal state of this buffer, see Dem_DTCReadoutBuffer_StatusType */
  Dem_Cfg_ReadOutBufferFreezeFrameDataEntryType OBDFreezeFrameData;             /* General: Backed OBD freeze frame data */
  uint8                                         SelectedSnapshotRecordNumber;   /* Data record selection: Selected FreezeFrame Record Number */
  boolean                                       SnapshotSelected;               /* Data record selection: Specifies whether a snapshot is selected or not  */
  uint8                                         SelectedExtendedDataNumber;     /* Data record selection: Selected Extended Data Record Number */
  boolean                                       ExtendedRecordSelected;         /* Data record selection: Specifies whether an extended data record is selected or not  */
}                                                                     Dem_Cfg_ReadoutBufferEntryType; 

typedef P2VAR(Dem_Cfg_ReadoutBufferEntryType, TYPEDEF, DEM_VAR_NOINIT) Dem_Cfg_ReadoutBufferEntryPtrType; 

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL SIMPLE DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/** 
  \defgroup  Dem_CfgPCIterableTypes  Dem_Cfg Iterable Types (PRE_COMPILE)
  \brief  These type definitions are used to iterate over an array with least processor cycles for variable access as possible.
  \{
*/ 
/**   \brief  type used to iterate Dem_Cfg_CallbackClearEventAllowed */
typedef uint8_least Dem_Cfg_CallbackClearEventAllowedIterType;

/**   \brief  type used to iterate Dem_Cfg_CallbackDtcStatusChanged */
typedef uint8_least Dem_Cfg_CallbackDtcStatusChangedIterType;

/**   \brief  type used to iterate Dem_Cfg_CallbackGetFdc */
typedef uint8_least Dem_Cfg_CallbackGetFdcIterType;

/**   \brief  type used to iterate Dem_Cfg_CallbackJ1939DtcStatusChanged */
typedef uint8_least Dem_Cfg_CallbackJ1939DtcStatusChangedIterType;

/**   \brief  type used to iterate Dem_Cfg_ClearDTCTable */
typedef uint8_least Dem_Cfg_ClearDTCTableIterType;

/**   \brief  type used to iterate Dem_Cfg_ClearDtcNotificationFinishTable */
typedef uint8_least Dem_Cfg_ClearDtcNotificationFinishTableIterType;

/**   \brief  type used to iterate Dem_Cfg_ClearDtcNotificationStartTable */
typedef uint8_least Dem_Cfg_ClearDtcNotificationStartTableIterType;

/**   \brief  type used to iterate Dem_Cfg_ClientTable */
typedef uint8_least Dem_Cfg_ClientTableIterType;

/**   \brief  type used to iterate Dem_Cfg_CycleIdTable */
typedef uint8_least Dem_Cfg_CycleIdTableIterType;

/**   \brief  type used to iterate Dem_Cfg_DTCSelectorTable */
typedef uint8_least Dem_Cfg_DTCSelectorTableIterType;

/**   \brief  type used to iterate Dem_Cfg_DataCollectionTable */
typedef uint8_least Dem_Cfg_DataCollectionTableIterType;

/**   \brief  type used to iterate Dem_Cfg_DataCollectionTableEdr2CollInd */
typedef uint8_least Dem_Cfg_DataCollectionTableEdr2CollIndIterType;

/**   \brief  type used to iterate Dem_Cfg_DataCollectionTableErec2CollInd */
typedef uint8_least Dem_Cfg_DataCollectionTableErec2CollIndIterType;

/**   \brief  type used to iterate Dem_Cfg_DataCollectionTableFfm2CollInd */
typedef uint8_least Dem_Cfg_DataCollectionTableFfm2CollIndIterType;

/**   \brief  type used to iterate Dem_Cfg_DataCollectionTableJ19392CollInd */
typedef uint8_least Dem_Cfg_DataCollectionTableJ19392CollIndIterType;

/**   \brief  type used to iterate Dem_Cfg_DataCollectionTablePid2CollInd */
typedef uint8_least Dem_Cfg_DataCollectionTablePid2CollIndIterType;

/**   \brief  type used to iterate Dem_Cfg_DataElementTable */
typedef uint8_least Dem_Cfg_DataElementTableIterType;

/**   \brief  type used to iterate Dem_Cfg_DataElementTableCol2ElmtInd */
typedef uint8_least Dem_Cfg_DataElementTableCol2ElmtIndIterType;

/**   \brief  type used to iterate Dem_Cfg_DebounceHiResTable */
typedef uint8_least Dem_Cfg_DebounceHiResTableIterType;

/**   \brief  type used to iterate Dem_Cfg_DebounceLoResTable */
typedef uint8_least Dem_Cfg_DebounceLoResTableIterType;

/**   \brief  type used to iterate Dem_Cfg_DebounceTable */
typedef uint8_least Dem_Cfg_DebounceTableIterType;

/**   \brief  type used to iterate Dem_Cfg_DtcGroupMask */
typedef uint8_least Dem_Cfg_DtcGroupMaskIterType;

/**   \brief  type used to iterate Dem_Cfg_DtcTable */
typedef uint8_least Dem_Cfg_DtcTableIterType;

/**   \brief  type used to iterate Dem_Cfg_DtrStatus */
typedef uint8_least Dem_Cfg_DtrStatusIterType;

/**   \brief  type used to iterate Dem_Cfg_DtrTable */
typedef uint8_least Dem_Cfg_DtrTableIterType;

/**   \brief  type used to iterate Dem_Cfg_DtrTableInd */
typedef uint8_least Dem_Cfg_DtrTableIndIterType;

/**   \brief  type used to iterate Dem_Cfg_EnableConditionGroupTable */
typedef uint8_least Dem_Cfg_EnableConditionGroupTableIterType;

/**   \brief  type used to iterate Dem_Cfg_EnableConditionGroupTableInd */
typedef uint8_least Dem_Cfg_EnableConditionGroupTableIndIterType;

/**   \brief  type used to iterate Dem_Cfg_EnableConditionInitTable */
typedef uint8_least Dem_Cfg_EnableConditionInitTableIterType;

/**   \brief  type used to iterate Dem_Cfg_EnableConditionTable */
typedef uint8_least Dem_Cfg_EnableConditionTableIterType;

/**   \brief  type used to iterate Dem_Cfg_EventAvailableDefault */
typedef uint8_least Dem_Cfg_EventAvailableDefaultIterType;

/**   \brief  type used to iterate Dem_Cfg_EventAvailableInVariant */
typedef uint8_least Dem_Cfg_EventAvailableInVariantIterType;

/**   \brief  type used to iterate Dem_Cfg_EventDataChanged */
typedef uint8_least Dem_Cfg_EventDataChangedIterType;

/**   \brief  type used to iterate Dem_Cfg_EventDataCommitNumber */
typedef uint8_least Dem_Cfg_EventDataCommitNumberIterType;

/**   \brief  type used to iterate Dem_Cfg_EventStatusChanged */
typedef uint8_least Dem_Cfg_EventStatusChangedIterType;

/**   \brief  type used to iterate Dem_Cfg_EventTable */
typedef uint8_least Dem_Cfg_EventTableIterType;

/**   \brief  type used to iterate Dem_Cfg_EventTableInd */
typedef uint8_least Dem_Cfg_EventTableIndIterType;

/**   \brief  type used to iterate Dem_Cfg_EventTable_ERec2EventIdInd */
typedef uint8_least Dem_Cfg_EventTable_ERec2EventIdIndIterType;

/**   \brief  type used to iterate Dem_Cfg_EventTable_ObdRdyGroup2EventIdInd */
typedef uint8_least Dem_Cfg_EventTable_ObdRdyGroup2EventIdIndIterType;

/**   \brief  type used to iterate Dem_Cfg_ExtendedDataRecordIteratorTable */
typedef uint8_least Dem_Cfg_ExtendedDataRecordIteratorTableIterType;

/**   \brief  type used to iterate Dem_Cfg_ExtendedDataRecordTable */
typedef uint8_least Dem_Cfg_ExtendedDataRecordTableIterType;

/**   \brief  type used to iterate Dem_Cfg_ExtendedDataTable */
typedef uint8_least Dem_Cfg_ExtendedDataTableIterType;

/**   \brief  type used to iterate Dem_Cfg_FilterInfoTable */
typedef uint8_least Dem_Cfg_FilterInfoTableIterType;

/**   \brief  type used to iterate Dem_Cfg_FilterReportedEvents */
typedef uint8_least Dem_Cfg_FilterReportedEventsIterType;

/**   \brief  type used to iterate Dem_Cfg_FreezeFrameIteratorTable */
typedef uint8_least Dem_Cfg_FreezeFrameIteratorTableIterType;

/**   \brief  type used to iterate Dem_Cfg_FreezeFrameNumTable */
typedef uint8_least Dem_Cfg_FreezeFrameNumTableIterType;

/**   \brief  type used to iterate Dem_Cfg_FreezeFrameTable */
typedef uint8_least Dem_Cfg_FreezeFrameTableIterType;

/**   \brief  type used to iterate Dem_Cfg_GeneralJ1939Table */
typedef uint8_least Dem_Cfg_GeneralJ1939TableIterType;

/**   \brief  type used to iterate Dem_Cfg_GeneralObdInput */
typedef uint8_least Dem_Cfg_GeneralObdInputIterType;

/**   \brief  type used to iterate Dem_Cfg_GlobalIndicatorStates */
typedef uint8_least Dem_Cfg_GlobalIndicatorStatesIterType;

/**   \brief  type used to iterate Dem_Cfg_IndicatorBlinking */
typedef uint8_least Dem_Cfg_IndicatorBlinkingIterType;

/**   \brief  type used to iterate Dem_Cfg_IndicatorContinuous */
typedef uint8_least Dem_Cfg_IndicatorContinuousIterType;

/**   \brief  type used to iterate Dem_Cfg_IndicatorFastFlash */
typedef uint8_least Dem_Cfg_IndicatorFastFlashIterType;

/**   \brief  type used to iterate Dem_Cfg_IndicatorSlowFlash */
typedef uint8_least Dem_Cfg_IndicatorSlowFlashIterType;

/**   \brief  type used to iterate Dem_Cfg_InitMonListForFunc */
typedef uint8_least Dem_Cfg_InitMonListForFuncIterType;

/**   \brief  type used to iterate Dem_Cfg_InitMonitorForEvent */
typedef uint8_least Dem_Cfg_InitMonitorForEventIterType;

/**   \brief  type used to iterate Dem_Cfg_InitMonitorsForFunc */
typedef uint8_least Dem_Cfg_InitMonitorsForFuncIterType;

/**   \brief  type used to iterate Dem_Cfg_J1939NodeId */
typedef uint8_least Dem_Cfg_J1939NodeIdIterType;

/**   \brief  type used to iterate Dem_Cfg_J1939NodeIdInd */
typedef uint8_least Dem_Cfg_J1939NodeIdIndIterType;

/**   \brief  type used to iterate Dem_Cfg_J1939NodeIndicator */
typedef uint8_least Dem_Cfg_J1939NodeIndicatorIterType;

/**   \brief  type used to iterate Dem_Cfg_MemoryBlockId */
typedef uint8_least Dem_Cfg_MemoryBlockIdIterType;

/**   \brief  type used to iterate Dem_Cfg_MemoryBlockIdToMemoryEntryId */
typedef uint8_least Dem_Cfg_MemoryBlockIdToMemoryEntryIdIterType;

/**   \brief  type used to iterate Dem_Cfg_MemoryDataPtr */
typedef uint8_least Dem_Cfg_MemoryDataPtrIterType;

/**   \brief  type used to iterate Dem_Cfg_MemoryDataSize */
typedef uint8_least Dem_Cfg_MemoryDataSizeIterType;

/**   \brief  type used to iterate Dem_Cfg_MemoryEntry */
typedef uint8_least Dem_Cfg_MemoryEntryIterType;

/**   \brief  type used to iterate Dem_Cfg_MemoryStatus */
typedef uint8_least Dem_Cfg_MemoryStatusIterType;

/**   \brief  type used to iterate Dem_Cfg_MidTable */
typedef uint8_least Dem_Cfg_MidTableIterType;

/**   \brief  type used to iterate Dem_Cfg_NormalIndicatorTable */
typedef uint8_least Dem_Cfg_NormalIndicatorTableIterType;

/**   \brief  type used to iterate Dem_Cfg_ObdIumprUpdatePending */
typedef uint8_least Dem_Cfg_ObdIumprUpdatePendingIterType;

/**   \brief  type used to iterate Dem_Cfg_PidTable */
typedef uint8_least Dem_Cfg_PidTableIterType;

/**   \brief  type used to iterate Dem_Cfg_PrestorageIndex */
typedef uint8_least Dem_Cfg_PrestorageIndexIterType;

/**   \brief  type used to iterate Dem_Cfg_PrimaryChronology */
typedef uint8_least Dem_Cfg_PrimaryChronologyIterType;

/**   \brief  type used to iterate Dem_Cfg_RatioIdTable */
typedef uint8_least Dem_Cfg_RatioIdTableIterType;

/**   \brief  type used to iterate Dem_Cfg_ReadinessGroupTable */
typedef uint8_least Dem_Cfg_ReadinessGroupTableIterType;

/**   \brief  type used to iterate Dem_Cfg_ReadoutBuffer */
typedef uint8_least Dem_Cfg_ReadoutBufferIterType;

/**   \brief  type used to iterate Dem_Cfg_ReportedEventsOfFilter */
typedef uint8_least Dem_Cfg_ReportedEventsOfFilterIterType;

/**   \brief  type used to iterate Dem_Cfg_SatelliteInfo */
typedef uint8_least Dem_Cfg_SatelliteInfoIterType;

/**   \brief  type used to iterate Dem_Cfg_SatelliteTimeDebounceInfo */
typedef uint8_least Dem_Cfg_SatelliteTimeDebounceInfoIterType;

/**   \brief  type used to iterate Dem_Cfg_SecondaryChronology */
typedef uint8_least Dem_Cfg_SecondaryChronologyIterType;

/**   \brief  type used to iterate Dem_Cfg_SpecialIndicatorTable */
typedef uint8_least Dem_Cfg_SpecialIndicatorTableIterType;

/**   \brief  type used to iterate Dem_Cfg_StartIdx500miDenRatioTable */
typedef uint8_least Dem_Cfg_StartIdx500miDenRatioTableIterType;

/**   \brief  type used to iterate Dem_Cfg_StorageConditionGroupTable */
typedef uint8_least Dem_Cfg_StorageConditionGroupTableIterType;

/**   \brief  type used to iterate Dem_Cfg_StorageConditionGroupTableInd */
typedef uint8_least Dem_Cfg_StorageConditionGroupTableIndIterType;

/**   \brief  type used to iterate Dem_Cfg_StorageConditionInitTable */
typedef uint8_least Dem_Cfg_StorageConditionInitTableIterType;

/**   \brief  type used to iterate Dem_Cfg_StorageConditionTable */
typedef uint8_least Dem_Cfg_StorageConditionTableIterType;

/**   \brief  type used to iterate Dem_Cfg_SupportedMidsTable */
typedef uint8_least Dem_Cfg_SupportedMidsTableIterType;

/**   \brief  type used to iterate Dem_Cfg_TimeSeriesChronology */
typedef uint8_least Dem_Cfg_TimeSeriesChronologyIterType;

/** 
  \}
*/ 

/** 
  \defgroup  Dem_CfgPCIterableTypesWithSizeRelations  Dem_Cfg Iterable Types With Size Relations (PRE_COMPILE)
  \brief  These type definitions are used to iterate over a VAR based array with the same iterator as the related CONST array.
  \{
*/ 
/**   \brief  type used to iterate Dem_Cfg_EnableConditionFulfilled */
typedef Dem_Cfg_EnableConditionTableIterType Dem_Cfg_EnableConditionFulfilledIterType;

/**   \brief  type used to iterate Dem_Cfg_EnableConditionGroupCounter */
typedef Dem_Cfg_EnableConditionGroupTableIterType Dem_Cfg_EnableConditionGroupCounterIterType;

/**   \brief  type used to iterate Dem_Cfg_EnableConditionGroupState */
typedef Dem_Cfg_EnableConditionGroupTableIterType Dem_Cfg_EnableConditionGroupStateIterType;

/**   \brief  type used to iterate Dem_Cfg_EventCycleStatus */
typedef Dem_Cfg_EventTableIterType Dem_Cfg_EventCycleStatusIterType;

/**   \brief  type used to iterate Dem_Cfg_EventDebounceValue */
typedef Dem_Cfg_EventTableIterType Dem_Cfg_EventDebounceValueIterType;

/**   \brief  type used to iterate Dem_Cfg_EventInternalStatus */
typedef Dem_Cfg_EventTableIterType Dem_Cfg_EventInternalStatusIterType;

/**   \brief  type used to iterate Dem_Cfg_StorageConditionFulfilled */
typedef Dem_Cfg_StorageConditionTableIterType Dem_Cfg_StorageConditionFulfilledIterType;

/**   \brief  type used to iterate Dem_Cfg_StorageConditionGroupCounter */
typedef Dem_Cfg_StorageConditionGroupTableIterType Dem_Cfg_StorageConditionGroupCounterIterType;

/** 
  \}
*/ 

/** 
  \defgroup  Dem_CfgPCValueTypes  Dem_Cfg Value Types (PRE_COMPILE)
  \brief  These type definitions are used for value based data representations.
  \{
*/ 
/**   \brief  value based type definition for Dem_Cfg_ClearDTCIndexOfClientTable */
typedef uint8 Dem_Cfg_ClearDTCIndexOfClientTableType;

/**   \brief  value based type definition for Dem_Cfg_FilterIndexOfClientTable */
typedef uint8 Dem_Cfg_FilterIndexOfClientTableType;

/**   \brief  value based type definition for Dem_Cfg_FreezeFrameIteratorIndexOfClientTable */
typedef uint8 Dem_Cfg_FreezeFrameIteratorIndexOfClientTableType;

/**   \brief  value based type definition for Dem_Cfg_NmNodeIdOfClientTable */
typedef uint16 Dem_Cfg_NmNodeIdOfClientTableType;

/**   \brief  value based type definition for Dem_Cfg_ReadoutBufferIndexOfClientTable */
typedef uint8 Dem_Cfg_ReadoutBufferIndexOfClientTableType;

/**   \brief  value based type definition for Dem_Cfg_SelectorIndexOfClientTable */
typedef uint8 Dem_Cfg_SelectorIndexOfClientTableType;

/**   \brief  value based type definition for Dem_Cfg_ConfigurationId */
typedef uint16 Dem_Cfg_ConfigurationIdType;

/**   \brief  value based type definition for Dem_Cfg_EndsOnInitOfCycleIdTable */
typedef boolean Dem_Cfg_EndsOnInitOfCycleIdTableType;

/**   \brief  value based type definition for Dem_Cfg_MaskedBitsOfCycleIdTable */
typedef uint8 Dem_Cfg_MaskedBitsOfCycleIdTableType;

/**   \brief  value based type definition for Dem_Cfg_OpCycleTypeOfCycleIdTable */
typedef uint8 Dem_Cfg_OpCycleTypeOfCycleIdTableType;

/**   \brief  value based type definition for Dem_Cfg_UsedForAgingOfCycleIdTable */
typedef boolean Dem_Cfg_UsedForAgingOfCycleIdTableType;

/**   \brief  value based type definition for Dem_Cfg_CollectionSizeOfDataCollectionTable */
typedef uint8 Dem_Cfg_CollectionSizeOfDataCollectionTableType;

/**   \brief  value based type definition for Dem_Cfg_DataElementTableCol2ElmtIndEndIdxOfDataCollectionTable */
typedef uint8 Dem_Cfg_DataElementTableCol2ElmtIndEndIdxOfDataCollectionTableType;

/**   \brief  value based type definition for Dem_Cfg_DataElementTableCol2ElmtIndStartIdxOfDataCollectionTable */
typedef uint8 Dem_Cfg_DataElementTableCol2ElmtIndStartIdxOfDataCollectionTableType;

/**   \brief  value based type definition for Dem_Cfg_DataElementTableCol2ElmtIndUsedOfDataCollectionTable */
typedef boolean Dem_Cfg_DataElementTableCol2ElmtIndUsedOfDataCollectionTableType;

/**   \brief  value based type definition for Dem_Cfg_DidOffsetFastOfDataCollectionTable */
typedef uint8 Dem_Cfg_DidOffsetFastOfDataCollectionTableType;

/**   \brief  value based type definition for Dem_Cfg_DidOffsetNormalOfDataCollectionTable */
typedef uint8 Dem_Cfg_DidOffsetNormalOfDataCollectionTableType;

/**   \brief  value based type definition for Dem_Cfg_EventTable_ERec2EventIdIndEndIdxOfDataCollectionTable */
typedef uint8 Dem_Cfg_EventTable_ERec2EventIdIndEndIdxOfDataCollectionTableType;

/**   \brief  value based type definition for Dem_Cfg_EventTable_ERec2EventIdIndStartIdxOfDataCollectionTable */
typedef uint8 Dem_Cfg_EventTable_ERec2EventIdIndStartIdxOfDataCollectionTableType;

/**   \brief  value based type definition for Dem_Cfg_EventTable_ERec2EventIdIndUsedOfDataCollectionTable */
typedef boolean Dem_Cfg_EventTable_ERec2EventIdIndUsedOfDataCollectionTableType;

/**   \brief  value based type definition for Dem_Cfg_IdNumberOfDataCollectionTable */
typedef uint16 Dem_Cfg_IdNumberOfDataCollectionTableType;

/**   \brief  value based type definition for Dem_Cfg_StorageKindOfDataCollectionTable */
typedef uint8 Dem_Cfg_StorageKindOfDataCollectionTableType;

/**   \brief  value based type definition for Dem_Cfg_TriggerOfDataCollectionTable */
typedef uint16 Dem_Cfg_TriggerOfDataCollectionTableType;

/**   \brief  value based type definition for Dem_Cfg_UpdateOfDataCollectionTable */
typedef boolean Dem_Cfg_UpdateOfDataCollectionTableType;

/**   \brief  value based type definition for Dem_Cfg_DataCollectionTableEdr2CollInd */
typedef uint8 Dem_Cfg_DataCollectionTableEdr2CollIndType;

/**   \brief  value based type definition for Dem_Cfg_DataCollectionTableErec2CollInd */
typedef uint8 Dem_Cfg_DataCollectionTableErec2CollIndType;

/**   \brief  value based type definition for Dem_Cfg_DataCollectionTableFfm2CollInd */
typedef uint8 Dem_Cfg_DataCollectionTableFfm2CollIndType;

/**   \brief  value based type definition for Dem_Cfg_DataCollectionTableJ19392CollInd */
typedef uint8 Dem_Cfg_DataCollectionTableJ19392CollIndType;

/**   \brief  value based type definition for Dem_Cfg_DataCollectionTablePid2CollInd */
typedef uint8 Dem_Cfg_DataCollectionTablePid2CollIndType;

/**   \brief  value based type definition for Dem_Cfg_DataIsStoredInNVOfDataElementTable */
typedef boolean Dem_Cfg_DataIsStoredInNVOfDataElementTableType;

/**   \brief  value based type definition for Dem_Cfg_ElementKindOfDataElementTable */
typedef uint8 Dem_Cfg_ElementKindOfDataElementTableType;

/**   \brief  value based type definition for Dem_Cfg_ElementSizeOfDataElementTable */
typedef uint8 Dem_Cfg_ElementSizeOfDataElementTableType;

/**   \brief  value based type definition for Dem_Cfg_DataElementTableCol2ElmtInd */
typedef uint8 Dem_Cfg_DataElementTableCol2ElmtIndType;

/**   \brief  value based type definition for Dem_Cfg_DebounceHiResTable */
typedef uint8 Dem_Cfg_DebounceHiResTableType;

/**   \brief  value based type definition for Dem_Cfg_DebounceLoResTable */
typedef uint8 Dem_Cfg_DebounceLoResTableType;

/**   \brief  value based type definition for Dem_Cfg_DebounceContinuousOfDebounceTable */
typedef boolean Dem_Cfg_DebounceContinuousOfDebounceTableType;

/**   \brief  value based type definition for Dem_Cfg_DecrementStepSizeOfDebounceTable */
typedef sint8 Dem_Cfg_DecrementStepSizeOfDebounceTableType;

/**   \brief  value based type definition for Dem_Cfg_EventDebounceAlgorithmOfDebounceTable */
typedef uint8 Dem_Cfg_EventDebounceAlgorithmOfDebounceTableType;

/**   \brief  value based type definition for Dem_Cfg_EventDebounceBehaviorOfDebounceTable */
typedef boolean Dem_Cfg_EventDebounceBehaviorOfDebounceTableType;

/**   \brief  value based type definition for Dem_Cfg_FailTimerCyclesOfDebounceTable */
typedef sint8 Dem_Cfg_FailTimerCyclesOfDebounceTableType;

/**   \brief  value based type definition for Dem_Cfg_FailedThresholdOfDebounceTable */
typedef sint16 Dem_Cfg_FailedThresholdOfDebounceTableType;

/**   \brief  value based type definition for Dem_Cfg_IncrementStepSizeOfDebounceTable */
typedef sint8 Dem_Cfg_IncrementStepSizeOfDebounceTableType;

/**   \brief  value based type definition for Dem_Cfg_JumpDownOfDebounceTable */
typedef boolean Dem_Cfg_JumpDownOfDebounceTableType;

/**   \brief  value based type definition for Dem_Cfg_JumpDownValueOfDebounceTable */
typedef sint8 Dem_Cfg_JumpDownValueOfDebounceTableType;

/**   \brief  value based type definition for Dem_Cfg_JumpUpOfDebounceTable */
typedef boolean Dem_Cfg_JumpUpOfDebounceTableType;

/**   \brief  value based type definition for Dem_Cfg_JumpUpValueOfDebounceTable */
typedef sint8 Dem_Cfg_JumpUpValueOfDebounceTableType;

/**   \brief  value based type definition for Dem_Cfg_MaskedBitsOfDebounceTable */
typedef uint8 Dem_Cfg_MaskedBitsOfDebounceTableType;

/**   \brief  value based type definition for Dem_Cfg_PassTimerCyclesOfDebounceTable */
typedef sint8 Dem_Cfg_PassTimerCyclesOfDebounceTableType;

/**   \brief  value based type definition for Dem_Cfg_PassedThresholdOfDebounceTable */
typedef sint16 Dem_Cfg_PassedThresholdOfDebounceTableType;

/**   \brief  value based type definition for Dem_Cfg_PreconfirmedThresholdOfDebounceTable */
typedef uint8 Dem_Cfg_PreconfirmedThresholdOfDebounceTableType;

/**   \brief  value based type definition for Dem_Cfg_StorageOfDebounceTable */
typedef boolean Dem_Cfg_StorageOfDebounceTableType;

/**   \brief  value based type definition for Dem_Cfg_StorageThresholdOfDebounceTable */
typedef uint8 Dem_Cfg_StorageThresholdOfDebounceTableType;

/**   \brief  value based type definition for Dem_Cfg_StorageTimerCyclesOfDebounceTable */
typedef sint8 Dem_Cfg_StorageTimerCyclesOfDebounceTableType;

/**   \brief  value based type definition for Dem_Cfg_GroupMaskOfDtcGroupMask */
typedef uint8 Dem_Cfg_GroupMaskOfDtcGroupMaskType;

/**   \brief  value based type definition for Dem_Cfg_UdsGroupDtcOfDtcGroupMask */
typedef uint8 Dem_Cfg_UdsGroupDtcOfDtcGroupMaskType;

/**   \brief  value based type definition for Dem_Cfg_DtcSeverityOfDtcTable */
typedef uint8 Dem_Cfg_DtcSeverityOfDtcTableType;

/**   \brief  value based type definition for Dem_Cfg_FunctionalUnitOfDtcTable */
typedef uint8 Dem_Cfg_FunctionalUnitOfDtcTableType;

/**   \brief  value based type definition for Dem_Cfg_ImmediateNvStorageOfDtcTable */
typedef boolean Dem_Cfg_ImmediateNvStorageOfDtcTableType;

/**   \brief  value based type definition for Dem_Cfg_J1939DtcOfDtcTable */
typedef uint8 Dem_Cfg_J1939DtcOfDtcTableType;

/**   \brief  value based type definition for Dem_Cfg_J1939NodeIdIndEndIdxOfDtcTable */
typedef uint8 Dem_Cfg_J1939NodeIdIndEndIdxOfDtcTableType;

/**   \brief  value based type definition for Dem_Cfg_J1939NodeIdIndStartIdxOfDtcTable */
typedef uint8 Dem_Cfg_J1939NodeIdIndStartIdxOfDtcTableType;

/**   \brief  value based type definition for Dem_Cfg_J1939NodeIdIndUsedOfDtcTable */
typedef boolean Dem_Cfg_J1939NodeIdIndUsedOfDtcTableType;

/**   \brief  value based type definition for Dem_Cfg_ObdDtcOfDtcTable */
typedef uint8 Dem_Cfg_ObdDtcOfDtcTableType;

/**   \brief  value based type definition for Dem_Cfg_UdsDtcOfDtcTable */
typedef uint32 Dem_Cfg_UdsDtcOfDtcTableType;

/**   \brief  value based type definition for Dem_Cfg_DivisorOfDtrTable */
typedef float32 Dem_Cfg_DivisorOfDtrTableType;

/**   \brief  value based type definition for Dem_Cfg_EventTableIdxOfDtrTable */
typedef uint8 Dem_Cfg_EventTableIdxOfDtrTableType;

/**   \brief  value based type definition for Dem_Cfg_LinearFactorOfDtrTable */
typedef float32 Dem_Cfg_LinearFactorOfDtrTableType;

/**   \brief  value based type definition for Dem_Cfg_OffsetOfDtrTable */
typedef float32 Dem_Cfg_OffsetOfDtrTableType;

/**   \brief  value based type definition for Dem_Cfg_UasidOfDtrTable */
typedef uint8 Dem_Cfg_UasidOfDtrTableType;

/**   \brief  value based type definition for Dem_Cfg_UpdateKindOfDtrTable */
typedef uint8 Dem_Cfg_UpdateKindOfDtrTableType;

/**   \brief  value based type definition for Dem_Cfg_DtrTableInd */
typedef uint8 Dem_Cfg_DtrTableIndType;

/**   \brief  value based type definition for Dem_Cfg_EnableConditionFulfilled */
typedef boolean Dem_Cfg_EnableConditionFulfilledType;

/**   \brief  value based type definition for Dem_Cfg_EnableConditionGroupCounter */
typedef uint8 Dem_Cfg_EnableConditionGroupCounterType;

/**   \brief  value based type definition for Dem_Cfg_EnableConditionGroupState */
typedef uint8 Dem_Cfg_EnableConditionGroupStateType;

/**   \brief  value based type definition for Dem_Cfg_IndexOfEnableConditionGroupTable */
typedef uint8 Dem_Cfg_IndexOfEnableConditionGroupTableType;

/**   \brief  value based type definition for Dem_Cfg_EnableConditionGroupTableInd */
typedef uint8 Dem_Cfg_EnableConditionGroupTableIndType;

/**   \brief  value based type definition for Dem_Cfg_FulfilledAtInitOfEnableConditionInitTable */
typedef boolean Dem_Cfg_FulfilledAtInitOfEnableConditionInitTableType;

/**   \brief  value based type definition for Dem_Cfg_EnableConditionGroupTableIndEndIdxOfEnableConditionTable */
typedef uint8 Dem_Cfg_EnableConditionGroupTableIndEndIdxOfEnableConditionTableType;

/**   \brief  value based type definition for Dem_Cfg_EnableConditionGroupTableIndStartIdxOfEnableConditionTable */
typedef uint8 Dem_Cfg_EnableConditionGroupTableIndStartIdxOfEnableConditionTableType;

/**   \brief  value based type definition for Dem_Cfg_EnableConditionGroupTableIndUsedOfEnableConditionTable */
typedef boolean Dem_Cfg_EnableConditionGroupTableIndUsedOfEnableConditionTableType;

/**   \brief  value based type definition for Dem_Cfg_EventAvailableDefault */
typedef boolean Dem_Cfg_EventAvailableDefaultType;

/**   \brief  value based type definition for Dem_Cfg_EventAvailableInVariant */
typedef boolean Dem_Cfg_EventAvailableInVariantType;

/**   \brief  value based type definition for Dem_Cfg_EventCycleStatus */
typedef uint8 Dem_Cfg_EventCycleStatusType;

/**   \brief  value based type definition for Dem_Cfg_EventDataCommitNumber */
typedef uint8 Dem_Cfg_EventDataCommitNumberType;

/**   \brief  value based type definition for Dem_Cfg_EventDebounceValue */
typedef sint16 Dem_Cfg_EventDebounceValueType;

/**   \brief  value based type definition for Dem_Cfg_AgingAllowedOfEventTable */
typedef boolean Dem_Cfg_AgingAllowedOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_AgingCycleCounterThresholdOfEventTable */
typedef uint8 Dem_Cfg_AgingCycleCounterThresholdOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_AgingCycleIdOfEventTable */
typedef uint8 Dem_Cfg_AgingCycleIdOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_CallbackClearEventAllowedIdxOfEventTable */
typedef uint8 Dem_Cfg_CallbackClearEventAllowedIdxOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_CallbackClearEventAllowedUsedOfEventTable */
typedef boolean Dem_Cfg_CallbackClearEventAllowedUsedOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_CallbackGetFdcIdxOfEventTable */
typedef uint8 Dem_Cfg_CallbackGetFdcIdxOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_DebounceTableIdxOfEventTable */
typedef uint8 Dem_Cfg_DebounceTableIdxOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_DtcTableIdxOfEventTable */
typedef uint8 Dem_Cfg_DtcTableIdxOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_DtrTableIndEndIdxOfEventTable */
typedef uint8 Dem_Cfg_DtrTableIndEndIdxOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_DtrTableIndStartIdxOfEventTable */
typedef uint8 Dem_Cfg_DtrTableIndStartIdxOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_DtrTableIndUsedOfEventTable */
typedef boolean Dem_Cfg_DtrTableIndUsedOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_EnableConditionGroupTableIdxOfEventTable */
typedef uint8 Dem_Cfg_EnableConditionGroupTableIdxOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_EventDestinationOfEventTable */
typedef uint8 Dem_Cfg_EventDestinationOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_EventFailureCycleCounterThresholdOfEventTable */
typedef uint8 Dem_Cfg_EventFailureCycleCounterThresholdOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_EventKindOfEventTable */
typedef uint8 Dem_Cfg_EventKindOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_EventLatchTFOfEventTable */
typedef boolean Dem_Cfg_EventLatchTFOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_EventPriorityOfEventTable */
typedef uint8 Dem_Cfg_EventPriorityOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_EventSignificanceOfEventTable */
typedef uint8 Dem_Cfg_EventSignificanceOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_ExtendedDataTableIdxOfEventTable */
typedef uint8 Dem_Cfg_ExtendedDataTableIdxOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_FailedCycleCounterIndexOfEventTable */
typedef uint8 Dem_Cfg_FailedCycleCounterIndexOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_FaultPendingCounterIndexOfEventTable */
typedef uint8 Dem_Cfg_FaultPendingCounterIndexOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_FreezeFrameNumTableEndIdxOfEventTable */
typedef uint8 Dem_Cfg_FreezeFrameNumTableEndIdxOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_FreezeFrameNumTableStartIdxOfEventTable */
typedef uint8 Dem_Cfg_FreezeFrameNumTableStartIdxOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_FreezeFrameNumTableUsedOfEventTable */
typedef boolean Dem_Cfg_FreezeFrameNumTableUsedOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_FreezeFrameTableStdFFIdxOfEventTable */
typedef uint8 Dem_Cfg_FreezeFrameTableStdFFIdxOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_HealingTargetOfEventTable */
typedef uint8 Dem_Cfg_HealingTargetOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_MaskedBitsOfEventTable */
typedef uint8 Dem_Cfg_MaskedBitsOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_OBDVisibilityDelayedUntilDcyQualificationOfEventTable */
typedef boolean Dem_Cfg_OBDVisibilityDelayedUntilDcyQualificationOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_OperationCycleIdOfEventTable */
typedef uint8 Dem_Cfg_OperationCycleIdOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_SatelliteEventIdxOfEventTable */
typedef uint8 Dem_Cfg_SatelliteEventIdxOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_SatelliteInfoIdxOfEventTable */
typedef uint8 Dem_Cfg_SatelliteInfoIdxOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_SpecialIndicatorTableEndIdxOfEventTable */
typedef uint8 Dem_Cfg_SpecialIndicatorTableEndIdxOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_SpecialIndicatorTableStartIdxOfEventTable */
typedef uint8 Dem_Cfg_SpecialIndicatorTableStartIdxOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_SpecialIndicatorTableUsedOfEventTable */
typedef boolean Dem_Cfg_SpecialIndicatorTableUsedOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_EventTableInd */
typedef uint8 Dem_Cfg_EventTableIndType;

/**   \brief  value based type definition for Dem_Cfg_EventTable_ERec2EventIdInd */
typedef uint8 Dem_Cfg_EventTable_ERec2EventIdIndType;

/**   \brief  value based type definition for Dem_Cfg_EventTable_ObdRdyGroup2EventIdInd */
typedef uint8 Dem_Cfg_EventTable_ObdRdyGroup2EventIdIndType;

/**   \brief  value based type definition for Dem_Cfg_DataCollectionTableErec2CollIndEndIdxOfExtendedDataRecordTable */
typedef uint8 Dem_Cfg_DataCollectionTableErec2CollIndEndIdxOfExtendedDataRecordTableType;

/**   \brief  value based type definition for Dem_Cfg_DataCollectionTableErec2CollIndStartIdxOfExtendedDataRecordTable */
typedef uint8 Dem_Cfg_DataCollectionTableErec2CollIndStartIdxOfExtendedDataRecordTableType;

/**   \brief  value based type definition for Dem_Cfg_DataCollectionTableErec2CollIndUsedOfExtendedDataRecordTable */
typedef boolean Dem_Cfg_DataCollectionTableErec2CollIndUsedOfExtendedDataRecordTableType;

/**   \brief  value based type definition for Dem_Cfg_DataCollectionTableEdr2CollIndEndIdxOfExtendedDataTable */
typedef uint8 Dem_Cfg_DataCollectionTableEdr2CollIndEndIdxOfExtendedDataTableType;

/**   \brief  value based type definition for Dem_Cfg_DataCollectionTableEdr2CollIndStartIdxOfExtendedDataTable */
typedef uint8 Dem_Cfg_DataCollectionTableEdr2CollIndStartIdxOfExtendedDataTableType;

/**   \brief  value based type definition for Dem_Cfg_DataCollectionTableEdr2CollIndUsedOfExtendedDataTable */
typedef boolean Dem_Cfg_DataCollectionTableEdr2CollIndUsedOfExtendedDataTableType;

/**   \brief  value based type definition for Dem_Cfg_MaxRecordSizeOfExtendedDataTable */
typedef uint8 Dem_Cfg_MaxRecordSizeOfExtendedDataTableType;

/**   \brief  value based type definition for Dem_Cfg_FilterReportedEvents */
typedef uint8 Dem_Cfg_FilterReportedEventsType;

/**   \brief  value based type definition for Dem_Cfg_FinalMagicNumber */
typedef uint16 Dem_Cfg_FinalMagicNumberType;

/**   \brief  value based type definition for Dem_Cfg_FFNumberOfFreezeFrameNumTable */
typedef uint8 Dem_Cfg_FFNumberOfFreezeFrameNumTableType;

/**   \brief  value based type definition for Dem_Cfg_FFTriggerOfFreezeFrameNumTable */
typedef uint16 Dem_Cfg_FFTriggerOfFreezeFrameNumTableType;

/**   \brief  value based type definition for Dem_Cfg_FFUpdateOfFreezeFrameNumTable */
typedef boolean Dem_Cfg_FFUpdateOfFreezeFrameNumTableType;

/**   \brief  value based type definition for Dem_Cfg_DataCollectionTableFfm2CollIndEndIdxOfFreezeFrameTable */
typedef uint8 Dem_Cfg_DataCollectionTableFfm2CollIndEndIdxOfFreezeFrameTableType;

/**   \brief  value based type definition for Dem_Cfg_DataCollectionTableFfm2CollIndStartIdxOfFreezeFrameTable */
typedef uint8 Dem_Cfg_DataCollectionTableFfm2CollIndStartIdxOfFreezeFrameTableType;

/**   \brief  value based type definition for Dem_Cfg_DataCollectionTableFfm2CollIndUsedOfFreezeFrameTable */
typedef boolean Dem_Cfg_DataCollectionTableFfm2CollIndUsedOfFreezeFrameTableType;

/**   \brief  value based type definition for Dem_Cfg_RecordSizeOfFreezeFrameTable */
typedef uint8 Dem_Cfg_RecordSizeOfFreezeFrameTableType;

/**   \brief  value based type definition for Dem_Cfg_RecordSizeUdsOfFastRateTimeSeriesPowertrainOfFreezeFrameTable */
typedef uint8 Dem_Cfg_RecordSizeUdsOfFastRateTimeSeriesPowertrainOfFreezeFrameTableType;

/**   \brief  value based type definition for Dem_Cfg_RecordSizeUdsOfFreezeFrameTable */
typedef uint8 Dem_Cfg_RecordSizeUdsOfFreezeFrameTableType;

/**   \brief  value based type definition for Dem_Cfg_RecordSizeUdsOfNormalRateTimeSeriesPowertrainOfFreezeFrameTable */
typedef uint8 Dem_Cfg_RecordSizeUdsOfNormalRateTimeSeriesPowertrainOfFreezeFrameTableType;

/**   \brief  value based type definition for Dem_Cfg_DataCollectionTableJ19392CollIndEndIdxOfGeneralJ1939Table */
typedef uint8 Dem_Cfg_DataCollectionTableJ19392CollIndEndIdxOfGeneralJ1939TableType;

/**   \brief  value based type definition for Dem_Cfg_DataCollectionTableJ19392CollIndStartIdxOfGeneralJ1939Table */
typedef uint8 Dem_Cfg_DataCollectionTableJ19392CollIndStartIdxOfGeneralJ1939TableType;

/**   \brief  value based type definition for Dem_Cfg_DataCollectionTableJ19392CollIndUsedOfGeneralJ1939Table */
typedef boolean Dem_Cfg_DataCollectionTableJ19392CollIndUsedOfGeneralJ1939TableType;

/**   \brief  value based type definition for Dem_Cfg_RecordSizeOfGeneralJ1939Table */
typedef uint8 Dem_Cfg_RecordSizeOfGeneralJ1939TableType;

/**   \brief  value based type definition for Dem_Cfg_DataElementTableIdxOfGeneralObdInput */
typedef uint8 Dem_Cfg_DataElementTableIdxOfGeneralObdInputType;

/**   \brief  value based type definition for Dem_Cfg_GlobalObdRequirements */
typedef uint8 Dem_Cfg_GlobalObdRequirementsType;

/**   \brief  value based type definition for Dem_Cfg_GlobalSeverityMask */
typedef uint8 Dem_Cfg_GlobalSeverityMaskType;

/**   \brief  value based type definition for Dem_Cfg_InitDataHashCode */
typedef sint32 Dem_Cfg_InitDataHashCodeType;

/**   \brief  value based type definition for Dem_Cfg_J1939NodeId */
typedef uint8 Dem_Cfg_J1939NodeIdType;

/**   \brief  value based type definition for Dem_Cfg_J1939NodeIdInd */
typedef uint8 Dem_Cfg_J1939NodeIdIndType;

/**   \brief  value based type definition for Dem_Cfg_J1939NodeIndicator */
typedef uint8 Dem_Cfg_J1939NodeIndicatorType;

/**   \brief  value based type definition for Dem_Cfg_MemoryBlockId */
typedef uint16 Dem_Cfg_MemoryBlockIdType;

/**   \brief  value based type definition for Dem_Cfg_MemoryDataSize */
typedef uint16 Dem_Cfg_MemoryDataSizeType;

/**   \brief  value based type definition for Dem_Cfg_MemoryStatus */
typedef uint8 Dem_Cfg_MemoryStatusType;

/**   \brief  value based type definition for Dem_Cfg_DtrTableIdxOfMidTable */
typedef uint8 Dem_Cfg_DtrTableIdxOfMidTableType;

/**   \brief  value based type definition for Dem_Cfg_MidOfMidTable */
typedef uint8 Dem_Cfg_MidOfMidTableType;

/**   \brief  value based type definition for Dem_Cfg_TidOfMidTable */
typedef uint8 Dem_Cfg_TidOfMidTableType;

/**   \brief  value based type definition for Dem_Cfg_MirrorData */
typedef uint8 Dem_Cfg_MirrorDataType;

/**   \brief  value based type definition for Dem_Cfg_BehaviorOfNormalIndicatorTable */
typedef uint8 Dem_Cfg_BehaviorOfNormalIndicatorTableType;

/**   \brief  value based type definition for Dem_Cfg_IdOfNormalIndicatorTable */
typedef uint8 Dem_Cfg_IdOfNormalIndicatorTableType;

/**   \brief  value based type definition for Dem_Cfg_ObdIumprUpdatePending */
typedef boolean Dem_Cfg_ObdIumprUpdatePendingType;

/**   \brief  value based type definition for Dem_Cfg_DataCollectionTablePid2CollIndEndIdxOfPidTable */
typedef uint8 Dem_Cfg_DataCollectionTablePid2CollIndEndIdxOfPidTableType;

/**   \brief  value based type definition for Dem_Cfg_DataCollectionTablePid2CollIndStartIdxOfPidTable */
typedef uint8 Dem_Cfg_DataCollectionTablePid2CollIndStartIdxOfPidTableType;

/**   \brief  value based type definition for Dem_Cfg_DataCollectionTablePid2CollIndUsedOfPidTable */
typedef boolean Dem_Cfg_DataCollectionTablePid2CollIndUsedOfPidTableType;

/**   \brief  value based type definition for Dem_Cfg_EventTable_ObdRdyGroup2EventIdIndEndIdxOfReadinessGroupTable */
typedef uint8 Dem_Cfg_EventTable_ObdRdyGroup2EventIdIndEndIdxOfReadinessGroupTableType;

/**   \brief  value based type definition for Dem_Cfg_EventTable_ObdRdyGroup2EventIdIndStartIdxOfReadinessGroupTable */
typedef uint8 Dem_Cfg_EventTable_ObdRdyGroup2EventIdIndStartIdxOfReadinessGroupTableType;

/**   \brief  value based type definition for Dem_Cfg_EventTable_ObdRdyGroup2EventIdIndUsedOfReadinessGroupTable */
typedef boolean Dem_Cfg_EventTable_ObdRdyGroup2EventIdIndUsedOfReadinessGroupTableType;

/**   \brief  value based type definition for Dem_Cfg_ReadinessGroupOfReadinessGroupTable */
typedef uint8 Dem_Cfg_ReadinessGroupOfReadinessGroupTableType;

/**   \brief  value based type definition for Dem_Cfg_EventCountOfSatelliteInfo */
typedef uint8 Dem_Cfg_EventCountOfSatelliteInfoType;

/**   \brief  value based type definition for Dem_Cfg_EventTableIndEndIdxOfSatelliteInfo */
typedef uint8 Dem_Cfg_EventTableIndEndIdxOfSatelliteInfoType;

/**   \brief  value based type definition for Dem_Cfg_EventTableIndStartIdxOfSatelliteInfo */
typedef uint8 Dem_Cfg_EventTableIndStartIdxOfSatelliteInfoType;

/**   \brief  value based type definition for Dem_Cfg_EventTableIndUsedOfSatelliteInfo */
typedef boolean Dem_Cfg_EventTableIndUsedOfSatelliteInfoType;

/**   \brief  value based type definition for Dem_Cfg_DebounceHiResTableEndIdxOfSatelliteTimeDebounceInfo */
typedef uint8 Dem_Cfg_DebounceHiResTableEndIdxOfSatelliteTimeDebounceInfoType;

/**   \brief  value based type definition for Dem_Cfg_DebounceHiResTableStartIdxOfSatelliteTimeDebounceInfo */
typedef uint8 Dem_Cfg_DebounceHiResTableStartIdxOfSatelliteTimeDebounceInfoType;

/**   \brief  value based type definition for Dem_Cfg_DebounceHiResTableUsedOfSatelliteTimeDebounceInfo */
typedef boolean Dem_Cfg_DebounceHiResTableUsedOfSatelliteTimeDebounceInfoType;

/**   \brief  value based type definition for Dem_Cfg_DebounceLoResTableEndIdxOfSatelliteTimeDebounceInfo */
typedef uint8 Dem_Cfg_DebounceLoResTableEndIdxOfSatelliteTimeDebounceInfoType;

/**   \brief  value based type definition for Dem_Cfg_DebounceLoResTableStartIdxOfSatelliteTimeDebounceInfo */
typedef uint8 Dem_Cfg_DebounceLoResTableStartIdxOfSatelliteTimeDebounceInfoType;

/**   \brief  value based type definition for Dem_Cfg_DebounceLoResTableUsedOfSatelliteTimeDebounceInfo */
typedef boolean Dem_Cfg_DebounceLoResTableUsedOfSatelliteTimeDebounceInfoType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfCallbackClearEventAllowed */
typedef uint8 Dem_Cfg_SizeOfCallbackClearEventAllowedType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfCallbackDtcStatusChanged */
typedef uint8 Dem_Cfg_SizeOfCallbackDtcStatusChangedType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfCallbackGetFdc */
typedef uint8 Dem_Cfg_SizeOfCallbackGetFdcType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfCallbackJ1939DtcStatusChanged */
typedef uint8 Dem_Cfg_SizeOfCallbackJ1939DtcStatusChangedType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfClearDTCTable */
typedef uint8 Dem_Cfg_SizeOfClearDTCTableType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfClearDtcNotificationFinishTable */
typedef uint8 Dem_Cfg_SizeOfClearDtcNotificationFinishTableType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfClearDtcNotificationStartTable */
typedef uint8 Dem_Cfg_SizeOfClearDtcNotificationStartTableType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfClientTable */
typedef uint8 Dem_Cfg_SizeOfClientTableType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfDTCSelectorTable */
typedef uint8 Dem_Cfg_SizeOfDTCSelectorTableType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfDataElementTable */
typedef uint8 Dem_Cfg_SizeOfDataElementTableType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfDebounceHiResTable */
typedef uint8 Dem_Cfg_SizeOfDebounceHiResTableType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfDebounceLoResTable */
typedef uint8 Dem_Cfg_SizeOfDebounceLoResTableType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfDtcGroupMask */
typedef uint8 Dem_Cfg_SizeOfDtcGroupMaskType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfDtrStatus */
typedef uint8 Dem_Cfg_SizeOfDtrStatusType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfDtrTable */
typedef uint8 Dem_Cfg_SizeOfDtrTableType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfEnableConditionFulfilled */
typedef uint8 Dem_Cfg_SizeOfEnableConditionFulfilledType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfEnableConditionGroupCounter */
typedef uint8 Dem_Cfg_SizeOfEnableConditionGroupCounterType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfEnableConditionGroupState */
typedef uint8 Dem_Cfg_SizeOfEnableConditionGroupStateType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfEnableConditionGroupTable */
typedef uint8 Dem_Cfg_SizeOfEnableConditionGroupTableType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfEnableConditionTable */
typedef uint8 Dem_Cfg_SizeOfEnableConditionTableType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfEventCycleStatus */
typedef uint8 Dem_Cfg_SizeOfEventCycleStatusType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfEventDataChanged */
typedef uint8 Dem_Cfg_SizeOfEventDataChangedType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfEventDataCommitNumber */
typedef uint8 Dem_Cfg_SizeOfEventDataCommitNumberType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfEventDebounceValue */
typedef uint8 Dem_Cfg_SizeOfEventDebounceValueType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfEventInternalStatus */
typedef uint8 Dem_Cfg_SizeOfEventInternalStatusType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfEventStatusChanged */
typedef uint8 Dem_Cfg_SizeOfEventStatusChangedType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfEventTable */
typedef uint8 Dem_Cfg_SizeOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfExtendedDataRecordIteratorTable */
typedef uint8 Dem_Cfg_SizeOfExtendedDataRecordIteratorTableType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfFilterInfoTable */
typedef uint8 Dem_Cfg_SizeOfFilterInfoTableType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfFilterReportedEvents */
typedef uint8 Dem_Cfg_SizeOfFilterReportedEventsType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfFreezeFrameIteratorTable */
typedef uint8 Dem_Cfg_SizeOfFreezeFrameIteratorTableType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfGlobalIndicatorStates */
typedef uint8 Dem_Cfg_SizeOfGlobalIndicatorStatesType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfIndicatorBlinking */
typedef uint8 Dem_Cfg_SizeOfIndicatorBlinkingType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfIndicatorContinuous */
typedef uint8 Dem_Cfg_SizeOfIndicatorContinuousType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfIndicatorFastFlash */
typedef uint8 Dem_Cfg_SizeOfIndicatorFastFlashType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfIndicatorSlowFlash */
typedef uint8 Dem_Cfg_SizeOfIndicatorSlowFlashType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfInitMonitorForEvent */
typedef uint8 Dem_Cfg_SizeOfInitMonitorForEventType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfInitMonitorsForFunc */
typedef uint8 Dem_Cfg_SizeOfInitMonitorsForFuncType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfMemoryBlockIdToMemoryEntryId */
typedef uint8 Dem_Cfg_SizeOfMemoryBlockIdToMemoryEntryIdType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfMemoryEntry */
typedef uint8 Dem_Cfg_SizeOfMemoryEntryType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfMemoryStatus */
typedef uint8 Dem_Cfg_SizeOfMemoryStatusType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfObdIumprUpdatePending */
typedef uint8 Dem_Cfg_SizeOfObdIumprUpdatePendingType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfPrestorageIndex */
typedef uint8 Dem_Cfg_SizeOfPrestorageIndexType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfPrimaryChronology */
typedef uint8 Dem_Cfg_SizeOfPrimaryChronologyType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfReadinessGroupTable */
typedef uint8 Dem_Cfg_SizeOfReadinessGroupTableType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfReadoutBuffer */
typedef uint8 Dem_Cfg_SizeOfReadoutBufferType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfReportedEventsOfFilter */
typedef uint8 Dem_Cfg_SizeOfReportedEventsOfFilterType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfSatelliteInfo */
typedef uint8 Dem_Cfg_SizeOfSatelliteInfoType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfSecondaryChronology */
typedef uint8 Dem_Cfg_SizeOfSecondaryChronologyType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfSpecialIndicatorTable */
typedef uint8 Dem_Cfg_SizeOfSpecialIndicatorTableType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfStartIdx500miDenRatioTable */
typedef uint8 Dem_Cfg_SizeOfStartIdx500miDenRatioTableType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfStorageConditionFulfilled */
typedef uint8 Dem_Cfg_SizeOfStorageConditionFulfilledType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfStorageConditionGroupCounter */
typedef uint8 Dem_Cfg_SizeOfStorageConditionGroupCounterType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfStorageConditionGroupTable */
typedef uint8 Dem_Cfg_SizeOfStorageConditionGroupTableType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfStorageConditionTable */
typedef uint8 Dem_Cfg_SizeOfStorageConditionTableType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfSupportedMidsTable */
typedef uint8 Dem_Cfg_SizeOfSupportedMidsTableType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfTimeSeriesChronology */
typedef uint8 Dem_Cfg_SizeOfTimeSeriesChronologyType;

/**   \brief  value based type definition for Dem_Cfg_BehaviorOfSpecialIndicatorTable */
typedef uint8 Dem_Cfg_BehaviorOfSpecialIndicatorTableType;

/**   \brief  value based type definition for Dem_Cfg_IdOfSpecialIndicatorTable */
typedef uint8 Dem_Cfg_IdOfSpecialIndicatorTableType;

/**   \brief  value based type definition for Dem_Cfg_StorageConditionFulfilled */
typedef boolean Dem_Cfg_StorageConditionFulfilledType;

/**   \brief  value based type definition for Dem_Cfg_StorageConditionGroupCounter */
typedef uint8 Dem_Cfg_StorageConditionGroupCounterType;

/**   \brief  value based type definition for Dem_Cfg_IndexOfStorageConditionGroupTable */
typedef uint8 Dem_Cfg_IndexOfStorageConditionGroupTableType;

/**   \brief  value based type definition for Dem_Cfg_StorageConditionGroupTableInd */
typedef uint8 Dem_Cfg_StorageConditionGroupTableIndType;

/**   \brief  value based type definition for Dem_Cfg_FulfilledAtInitOfStorageConditionInitTable */
typedef boolean Dem_Cfg_FulfilledAtInitOfStorageConditionInitTableType;

/**   \brief  value based type definition for Dem_Cfg_StorageConditionGroupTableIndEndIdxOfStorageConditionTable */
typedef uint8 Dem_Cfg_StorageConditionGroupTableIndEndIdxOfStorageConditionTableType;

/**   \brief  value based type definition for Dem_Cfg_StorageConditionGroupTableIndStartIdxOfStorageConditionTable */
typedef uint8 Dem_Cfg_StorageConditionGroupTableIndStartIdxOfStorageConditionTableType;

/**   \brief  value based type definition for Dem_Cfg_StorageConditionGroupTableIndUsedOfStorageConditionTable */
typedef boolean Dem_Cfg_StorageConditionGroupTableIndUsedOfStorageConditionTableType;

/**   \brief  value based type definition for Dem_Cfg_StartIdxMidTableOfSupportedMidsTable */
typedef uint8 Dem_Cfg_StartIdxMidTableOfSupportedMidsTableType;

/**   \brief  value based type definition for Dem_Cfg_SupportedMidMaskOfSupportedMidsTable */
typedef uint8 Dem_Cfg_SupportedMidMaskOfSupportedMidsTableType;

/**   \brief  value based type definition for Dem_Cfg_UseOBDIIInVariant */
typedef boolean Dem_Cfg_UseOBDIIInVariantType;

/**   \brief  value based type definition for Dem_Cfg_UsePermanentInVariant */
typedef boolean Dem_Cfg_UsePermanentInVariantType;

/**   \brief  value based type definition for Dem_Cfg_UseWWHOBDInVariant */
typedef boolean Dem_Cfg_UseWWHOBDInVariantType;

/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL COMPLEX DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/** 
  \defgroup  Dem_CfgPCStructTypes  Dem_Cfg Struct Types (PRE_COMPILE)
  \brief  These type definitions are used for structured data representations.
  \{
*/ 
/**   \brief  type used in Dem_Cfg_ClientTable */
typedef struct sDem_Cfg_ClientTableType
{
  uint8 Dem_Cfg_ClientTableNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} Dem_Cfg_ClientTableType;

/**   \brief  type used in Dem_Cfg_CycleIdTable */
typedef struct sDem_Cfg_CycleIdTableType
{
  Dem_Cfg_MaskedBitsOfCycleIdTableType MaskedBitsOfCycleIdTable;  /**< contains bitcoded the boolean data of Dem_Cfg_EndsOnInitOfCycleIdTable, Dem_Cfg_UsedForAgingOfCycleIdTable */
  Dem_Cfg_OpCycleTypeOfCycleIdTableType OpCycleTypeOfCycleIdTable;  /**< DemOperationCycleType of the DemOperationCycle: [DEM_CFG_OPCYC_IGNITION, DEM_CFG_OPCYC_OBD_DCY, DEM_CFG_OPCYC_OTHER, DEM_CFG_OPCYC_POWER, DEM_CFG_OPCYC_TIME, DEM_CFG_OPCYC_WARMUP, DEM_CFG_OPCYC_IGNITION_HYBRID, DEM_CFG_OPCYC_AGING] */
} Dem_Cfg_CycleIdTableType;

/**   \brief  type used in Dem_Cfg_DataCollectionTable */
typedef struct sDem_Cfg_DataCollectionTableType
{
  Dem_Cfg_IdNumberOfDataCollectionTableType IdNumberOfDataCollectionTable;
  Dem_Cfg_CollectionSizeOfDataCollectionTableType CollectionSizeOfDataCollectionTable;
  Dem_Cfg_DataElementTableCol2ElmtIndEndIdxOfDataCollectionTableType DataElementTableCol2ElmtIndEndIdxOfDataCollectionTable;  /**< the end index of the 0:n relation pointing to Dem_Cfg_DataElementTableCol2ElmtInd */
  Dem_Cfg_DataElementTableCol2ElmtIndStartIdxOfDataCollectionTableType DataElementTableCol2ElmtIndStartIdxOfDataCollectionTable;  /**< the start index of the 0:n relation pointing to Dem_Cfg_DataElementTableCol2ElmtInd */
  Dem_Cfg_StorageKindOfDataCollectionTableType StorageKindOfDataCollectionTable;
} Dem_Cfg_DataCollectionTableType;

/**   \brief  type used in Dem_Cfg_DataElementTable */
typedef struct sDem_Cfg_DataElementTableType
{
  Dem_Cfg_DataIsStoredInNVOfDataElementTableType DataIsStoredInNVOfDataElementTable;
  Dem_Cfg_ElementKindOfDataElementTableType ElementKindOfDataElementTable;  /**< DataElement kind, returned by Dem_Cfg_DataCallbackType() */
  Dem_Cfg_ElementSizeOfDataElementTableType ElementSizeOfDataElementTable;  /**< Size of data element in Byte. */
  Dem_ReadDataFPtrType ReadDataFuncOfDataElementTable;  /**< C-function for getting the data. Its signature depends on ElementKind: With value(s) DEM_CFG_DATA_FROM_CBK_WITH_EVENTID use: Std_ReturnType (*)(uint8* Buffer, uint16 EventId); - and use: Std_ReturnType (*)(uint8* Buffer); with the other values DEM_CFG_DATA_FROM_CBK, DEM_CFG_DATA_FROM_SR_PORT_BOOLEAN, DEM_CFG_DATA_FROM_SR_PORT_SINT16, DEM_CFG_DATA_FROM_SR_PORT_SINT16_INTEL, DEM_CFG_DATA_FROM_SR_PORT_SINT32, DEM_CFG_DATA_FROM_SR_PORT_SINT32_INTEL, DEM_CFG_DATA_FROM_SR_PORT_SINT8, DEM_CFG_DATA_FROM_SR_PORT_SINT8_N, DEM_CFG_DATA_FROM_SR_PORT_UINT16, DEM_CFG_DATA_FROM_SR_PORT_UINT16_INTEL, DEM_CFG_DATA_FROM_SR_PORT_UINT32, DEM_CFG_DATA_FROM_SR_PORT_UINT32_INTEL, DEM_CFG_DATA_FROM_SR_PORT_UINT8, DEM_CFG_DATA_FROM_SR_PORT_UINT8_N. */
} Dem_Cfg_DataElementTableType;

/**   \brief  type used in Dem_Cfg_DebounceTable */
typedef struct sDem_Cfg_DebounceTableType
{
  Dem_Cfg_FailedThresholdOfDebounceTableType FailedThresholdOfDebounceTable;  /**< DemDebounceCounterFailedThreshold of the DemEventParameter/DemEventClass/DemDebounceAlgorithmClass/DemDebounceCounterBased */
  Dem_Cfg_PassedThresholdOfDebounceTableType PassedThresholdOfDebounceTable;  /**< DemDebounceCounterPassedThreshold of the DemEventParameter/DemEventClass/DemDebounceAlgorithmClass/DemDebounceCounterBased */
  Dem_Cfg_DecrementStepSizeOfDebounceTableType DecrementStepSizeOfDebounceTable;  /**< (-1) * DemDebounceCounterDecrementStepSize of the DemEventParameter/DemEventClass/DemDebounceAlgorithmClass/DemDebounceCounterBased */
  Dem_Cfg_IncrementStepSizeOfDebounceTableType IncrementStepSizeOfDebounceTable;  /**< DemDebounceCounterIncrementStepSize of the DemEventParameter/DemEventClass/DemDebounceAlgorithmClass/DemDebounceCounterBased */
  Dem_Cfg_EventDebounceAlgorithmOfDebounceTableType EventDebounceAlgorithmOfDebounceTable;  /**< Used DemEventParameter/DemEventClass/DemDebounceAlgorithmClass */
  Dem_Cfg_MaskedBitsOfDebounceTableType MaskedBitsOfDebounceTable;  /**< contains bitcoded the boolean data of Dem_Cfg_DebounceContinuousOfDebounceTable, Dem_Cfg_EventDebounceBehaviorOfDebounceTable, Dem_Cfg_JumpDownOfDebounceTable, Dem_Cfg_JumpUpOfDebounceTable, Dem_Cfg_StorageOfDebounceTable */
} Dem_Cfg_DebounceTableType;

/**   \brief  type used in Dem_Cfg_DtcGroupMask */
typedef struct sDem_Cfg_DtcGroupMaskType
{
  uint8 Dem_Cfg_DtcGroupMaskNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} Dem_Cfg_DtcGroupMaskType;

/**   \brief  type used in Dem_Cfg_DtcTable */
typedef struct sDem_Cfg_DtcTableType
{
  Dem_Cfg_UdsDtcOfDtcTableType UdsDtcOfDtcTable;
  Dem_Cfg_FunctionalUnitOfDtcTableType FunctionalUnitOfDtcTable;
} Dem_Cfg_DtcTableType;

/**   \brief  type used in Dem_Cfg_DtrTable */
typedef struct sDem_Cfg_DtrTableType
{
  uint8 Dem_Cfg_DtrTableNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} Dem_Cfg_DtrTableType;

/**   \brief  type used in Dem_Cfg_EnableConditionGroupTable */
typedef struct sDem_Cfg_EnableConditionGroupTableType
{
  uint8 Dem_Cfg_EnableConditionGroupTableNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} Dem_Cfg_EnableConditionGroupTableType;

/**   \brief  type used in Dem_Cfg_EnableConditionInitTable */
typedef struct sDem_Cfg_EnableConditionInitTableType
{
  Dem_Cfg_FulfilledAtInitOfEnableConditionInitTableType FulfilledAtInitOfEnableConditionInitTable;  /**< Initial value: 'FALSE' condition is not fulfilled, 'TRUE' condition is fulfilled */
} Dem_Cfg_EnableConditionInitTableType;

/**   \brief  type used in Dem_Cfg_EnableConditionTable */
typedef struct sDem_Cfg_EnableConditionTableType
{
  Dem_Cfg_EnableConditionGroupTableIndEndIdxOfEnableConditionTableType EnableConditionGroupTableIndEndIdxOfEnableConditionTable;  /**< the end index of the 0:n relation pointing to Dem_Cfg_EnableConditionGroupTableInd */
  Dem_Cfg_EnableConditionGroupTableIndStartIdxOfEnableConditionTableType EnableConditionGroupTableIndStartIdxOfEnableConditionTable;  /**< the start index of the 0:n relation pointing to Dem_Cfg_EnableConditionGroupTableInd */
} Dem_Cfg_EnableConditionTableType;

/**   \brief  type used in Dem_Cfg_EventTable */
/*! \spec weak type invariant () { 
 * (self.EnableConditionGroupTableIdxOfEventTable < Dem_Cfg_GetSizeOfEnableConditionGroupTable()) &&
 * (!(Dem_Cfg_IsCallbackClearEventAllowedUsedOfEventTable(0)) || (self.CallbackClearEventAllowedIdxOfEventTable < Dem_Cfg_GetSizeOfCallbackClearEventAllowed()))
 * } */
typedef struct sDem_Cfg_EventTableType
{
  Dem_Cfg_AgingCycleCounterThresholdOfEventTableType AgingCycleCounterThresholdOfEventTable;  /**< DemAgingCycleCounterThreshold of the DemEventParameter/DemEventClass. If AgingAllowedOfEventTable==FALSE and DemAgingCycleCounterThreshold does not exist '255' is set. If AgingAllowedOfEventTable==TRUE and DemAgingCycleCounterThreshold does not exist '0' is set. */
  Dem_Cfg_AgingCycleIdOfEventTableType AgingCycleIdOfEventTable;  /**< DemOperationCycle (ID) referenced by DemEventParameter/DemEventClass/DemAgingCycleRef */
  Dem_Cfg_CallbackClearEventAllowedIdxOfEventTableType CallbackClearEventAllowedIdxOfEventTable;  /**< the index of the 0:1 relation pointing to Dem_Cfg_CallbackClearEventAllowed */
  Dem_Cfg_DebounceTableIdxOfEventTableType DebounceTableIdxOfEventTable;  /**< the index of the 1:1 relation pointing to Dem_Cfg_DebounceTable */
  Dem_Cfg_DtcTableIdxOfEventTableType DtcTableIdxOfEventTable;  /**< the index of the 1:1 relation pointing to Dem_Cfg_DtcTable */
  Dem_Cfg_EnableConditionGroupTableIdxOfEventTableType EnableConditionGroupTableIdxOfEventTable;  /**< the index of the 1:1 relation pointing to Dem_Cfg_EnableConditionGroupTable */
  Dem_Cfg_EventKindOfEventTableType EventKindOfEventTable;  /**< DemEventKind of the DemEventParameter */
  Dem_Cfg_EventPriorityOfEventTableType EventPriorityOfEventTable;  /**< DemEventParameter/DemEventClass/DemEventPriority, values [1..255] for the configuration range [1..255]. */
  Dem_Cfg_MaskedBitsOfEventTableType MaskedBitsOfEventTable;  /**< contains bitcoded the boolean data of Dem_Cfg_AgingAllowedOfEventTable, Dem_Cfg_EventLatchTFOfEventTable, Dem_Cfg_OBDVisibilityDelayedUntilDcyQualificationOfEventTable */
} Dem_Cfg_EventTableType;

/**   \brief  type used in Dem_Cfg_ExtendedDataRecordTable */
typedef struct sDem_Cfg_ExtendedDataRecordTableType
{
  uint8 Dem_Cfg_ExtendedDataRecordTableNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} Dem_Cfg_ExtendedDataRecordTableType;

/**   \brief  type used in Dem_Cfg_ExtendedDataTable */
typedef struct sDem_Cfg_ExtendedDataTableType
{
  Dem_Cfg_DataCollectionTableEdr2CollIndEndIdxOfExtendedDataTableType DataCollectionTableEdr2CollIndEndIdxOfExtendedDataTable;  /**< the end index of the 0:n relation pointing to Dem_Cfg_DataCollectionTableEdr2CollInd */
  Dem_Cfg_DataCollectionTableEdr2CollIndStartIdxOfExtendedDataTableType DataCollectionTableEdr2CollIndStartIdxOfExtendedDataTable;  /**< the start index of the 0:n relation pointing to Dem_Cfg_DataCollectionTableEdr2CollInd */
  Dem_Cfg_MaxRecordSizeOfExtendedDataTableType MaxRecordSizeOfExtendedDataTable;
} Dem_Cfg_ExtendedDataTableType;

/**   \brief  type used in Dem_Cfg_FreezeFrameNumTable */
typedef struct sDem_Cfg_FreezeFrameNumTableType
{
  uint8 Dem_Cfg_FreezeFrameNumTableNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} Dem_Cfg_FreezeFrameNumTableType;

/**   \brief  type used in Dem_Cfg_FreezeFrameTable */
typedef struct sDem_Cfg_FreezeFrameTableType
{
  Dem_Cfg_DataCollectionTableFfm2CollIndEndIdxOfFreezeFrameTableType DataCollectionTableFfm2CollIndEndIdxOfFreezeFrameTable;  /**< the end index of the 0:n relation pointing to Dem_Cfg_DataCollectionTableFfm2CollInd */
  Dem_Cfg_DataCollectionTableFfm2CollIndStartIdxOfFreezeFrameTableType DataCollectionTableFfm2CollIndStartIdxOfFreezeFrameTable;  /**< the start index of the 0:n relation pointing to Dem_Cfg_DataCollectionTableFfm2CollInd */
  Dem_Cfg_RecordSizeUdsOfFreezeFrameTableType RecordSizeUdsOfFreezeFrameTable;  /**< Summarized size of did data, did numbers and snapshot header (i.e. dynamical payload size of the uds response message). */
} Dem_Cfg_FreezeFrameTableType;

/**   \brief  type used in Dem_Cfg_GeneralJ1939Table */
typedef struct sDem_Cfg_GeneralJ1939TableType
{
  uint8 Dem_Cfg_GeneralJ1939TableNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} Dem_Cfg_GeneralJ1939TableType;

/**   \brief  type used in Dem_Cfg_GeneralObdInput */
typedef struct sDem_Cfg_GeneralObdInputType
{
  uint8 Dem_Cfg_GeneralObdInputNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} Dem_Cfg_GeneralObdInputType;

/**   \brief  type used in Dem_Cfg_InitMonListForFunc */
typedef struct sDem_Cfg_InitMonListForFuncType
{
  uint8 Dem_Cfg_InitMonListForFuncNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} Dem_Cfg_InitMonListForFuncType;

/**   \brief  type used in Dem_Cfg_MidTable */
typedef struct sDem_Cfg_MidTableType
{
  uint8 Dem_Cfg_MidTableNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} Dem_Cfg_MidTableType;

/**   \brief  type used in Dem_Cfg_NormalIndicatorTable */
typedef struct sDem_Cfg_NormalIndicatorTableType
{
  uint8 Dem_Cfg_NormalIndicatorTableNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} Dem_Cfg_NormalIndicatorTableType;

/**   \brief  type used in Dem_Cfg_PidTable */
typedef struct sDem_Cfg_PidTableType
{
  uint8 Dem_Cfg_PidTableNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} Dem_Cfg_PidTableType;

/**   \brief  type used in Dem_Cfg_RatioIdTable */
typedef struct sDem_Cfg_RatioIdTableType
{
  uint8 Dem_Cfg_RatioIdTableNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} Dem_Cfg_RatioIdTableType;

/**   \brief  type used in Dem_Cfg_ReadinessGroupTable */
typedef struct sDem_Cfg_ReadinessGroupTableType
{
  uint8 Dem_Cfg_ReadinessGroupTableNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} Dem_Cfg_ReadinessGroupTableType;

/**   \brief  type used in Dem_Cfg_SatelliteInfo */
typedef struct sDem_Cfg_SatelliteInfoType
{
  uint8 Dem_Cfg_SatelliteInfoNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} Dem_Cfg_SatelliteInfoType;

/**   \brief  type used in Dem_Cfg_SatelliteTimeDebounceInfo */
typedef struct sDem_Cfg_SatelliteTimeDebounceInfoType
{
  uint8 Dem_Cfg_SatelliteTimeDebounceInfoNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} Dem_Cfg_SatelliteTimeDebounceInfoType;

/**   \brief  type used in Dem_Cfg_SpecialIndicatorTable */
typedef struct sDem_Cfg_SpecialIndicatorTableType
{
  uint8 Dem_Cfg_SpecialIndicatorTableNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} Dem_Cfg_SpecialIndicatorTableType;

/**   \brief  type used in Dem_Cfg_StartIdx500miDenRatioTable */
typedef struct sDem_Cfg_StartIdx500miDenRatioTableType
{
  uint8 Dem_Cfg_StartIdx500miDenRatioTableNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} Dem_Cfg_StartIdx500miDenRatioTableType;

/**   \brief  type used in Dem_Cfg_StorageConditionGroupTable */
typedef struct sDem_Cfg_StorageConditionGroupTableType
{
  uint8 Dem_Cfg_StorageConditionGroupTableNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} Dem_Cfg_StorageConditionGroupTableType;

/**   \brief  type used in Dem_Cfg_StorageConditionInitTable */
typedef struct sDem_Cfg_StorageConditionInitTableType
{
  uint8 Dem_Cfg_StorageConditionInitTableNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} Dem_Cfg_StorageConditionInitTableType;

/**   \brief  type used in Dem_Cfg_StorageConditionTable */
typedef struct sDem_Cfg_StorageConditionTableType
{
  uint8 Dem_Cfg_StorageConditionTableNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} Dem_Cfg_StorageConditionTableType;

/**   \brief  type used in Dem_Cfg_SupportedMidsTable */
typedef struct sDem_Cfg_SupportedMidsTableType
{
  uint8 Dem_Cfg_SupportedMidsTableNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} Dem_Cfg_SupportedMidsTableType;

/** 
  \}
*/ 

/** 
  \defgroup  Dem_CfgPCRootPointerTypes  Dem_Cfg Root Pointer Types (PRE_COMPILE)
  \brief  These type definitions are used to point from the config root to symbol instances.
  \{
*/ 
/**   \brief  type used to point to Dem_Cfg_AdminData */
typedef P2VAR(Dem_Cfg_AdminDataType, TYPEDEF, DEM_NVM_DATA_NOINIT) Dem_Cfg_AdminDataPtrType;

/**   \brief  type used to point to Dem_Cfg_AgingData */
typedef P2VAR(Dem_Cfg_AgingDataType, TYPEDEF, DEM_NVM_DATA_NOINIT) Dem_Cfg_AgingDataPtrType;

/**   \brief  type used to point to Dem_Cfg_CallbackClearEventAllowed */
typedef P2CONST(Dem_ClearEventAllowedFPtrType, TYPEDEF, DEM_CONST) Dem_Cfg_CallbackClearEventAllowedPtrType;

/**   \brief  type used to point to Dem_Cfg_CallbackDtcStatusChanged */
typedef P2CONST(Dem_DtcStatusChangedFPtrType, TYPEDEF, DEM_CONST) Dem_Cfg_CallbackDtcStatusChangedPtrType;

/**   \brief  type used to point to Dem_Cfg_CallbackGetFdc */
typedef P2CONST(Dem_GetFDCFPtrType, TYPEDEF, DEM_CONST) Dem_Cfg_CallbackGetFdcPtrType;

/**   \brief  type used to point to Dem_Cfg_CallbackJ1939DtcStatusChanged */
typedef P2CONST(Dem_DtcStatusChangedFPtrType, TYPEDEF, DEM_CONST) Dem_Cfg_CallbackJ1939DtcStatusChangedPtrType;

/**   \brief  type used to point to Dem_Cfg_ClearDTCTable */
typedef P2VAR(Dem_ClearDTC_DataType, TYPEDEF, DEM_VAR_NOINIT) Dem_Cfg_ClearDTCTablePtrType;

/**   \brief  type used to point to Dem_Cfg_ClearDtcNotificationFinishTable */
typedef P2CONST(Dem_ClearDtcNotificationFPtrType, TYPEDEF, DEM_CONST) Dem_Cfg_ClearDtcNotificationFinishTablePtrType;

/**   \brief  type used to point to Dem_Cfg_ClearDtcNotificationStartTable */
typedef P2CONST(Dem_ClearDtcNotificationFPtrType, TYPEDEF, DEM_CONST) Dem_Cfg_ClearDtcNotificationStartTablePtrType;

/**   \brief  type used to point to Dem_Cfg_ClientTable */
typedef P2CONST(Dem_Cfg_ClientTableType, TYPEDEF, DEM_CONST) Dem_Cfg_ClientTablePtrType;

/**   \brief  type used to point to Dem_Cfg_CommitBuffer */
typedef P2VAR(Dem_Cfg_CommitBufferType, TYPEDEF, DEM_VAR_NOINIT) Dem_Cfg_CommitBufferPtrType;

/**   \brief  type used to point to Dem_Cfg_CycleCounterData */
typedef P2VAR(Dem_Cfg_CycleCounterDataType, TYPEDEF, DEM_NVM_DATA_NOINIT) Dem_Cfg_CycleCounterDataPtrType;

/**   \brief  type used to point to Dem_Cfg_CycleIdTable */
typedef P2CONST(Dem_Cfg_CycleIdTableType, TYPEDEF, DEM_CONST) Dem_Cfg_CycleIdTablePtrType;

/**   \brief  type used to point to Dem_Cfg_DTCSelectorTable */
typedef P2VAR(Dem_DTCSelector_DataType, TYPEDEF, DEM_VAR_NOINIT) Dem_Cfg_DTCSelectorTablePtrType;

/**   \brief  type used to point to Dem_Cfg_DataCollectionTable */
typedef P2CONST(Dem_Cfg_DataCollectionTableType, TYPEDEF, DEM_CONST) Dem_Cfg_DataCollectionTablePtrType;

/**   \brief  type used to point to Dem_Cfg_DataCollectionTableEdr2CollInd */
typedef P2CONST(Dem_Cfg_DataCollectionTableEdr2CollIndType, TYPEDEF, DEM_CONST) Dem_Cfg_DataCollectionTableEdr2CollIndPtrType;

/**   \brief  type used to point to Dem_Cfg_DataCollectionTableErec2CollInd */
typedef P2CONST(Dem_Cfg_DataCollectionTableErec2CollIndType, TYPEDEF, DEM_CONST) Dem_Cfg_DataCollectionTableErec2CollIndPtrType;

/**   \brief  type used to point to Dem_Cfg_DataCollectionTableFfm2CollInd */
typedef P2CONST(Dem_Cfg_DataCollectionTableFfm2CollIndType, TYPEDEF, DEM_CONST) Dem_Cfg_DataCollectionTableFfm2CollIndPtrType;

/**   \brief  type used to point to Dem_Cfg_DataCollectionTableJ19392CollInd */
typedef P2CONST(Dem_Cfg_DataCollectionTableJ19392CollIndType, TYPEDEF, DEM_CONST) Dem_Cfg_DataCollectionTableJ19392CollIndPtrType;

/**   \brief  type used to point to Dem_Cfg_DataCollectionTablePid2CollInd */
typedef P2CONST(Dem_Cfg_DataCollectionTablePid2CollIndType, TYPEDEF, DEM_CONST) Dem_Cfg_DataCollectionTablePid2CollIndPtrType;

/**   \brief  type used to point to Dem_Cfg_ReadDataFuncOfDataElementTable */
typedef P2CONST(Dem_ReadDataFPtrType, TYPEDEF, DEM_CONST) Dem_Cfg_ReadDataFuncOfDataElementTablePtrType;

/**   \brief  type used to point to Dem_Cfg_DataElementTable */
typedef P2CONST(Dem_Cfg_DataElementTableType, TYPEDEF, DEM_CONST) Dem_Cfg_DataElementTablePtrType;

/**   \brief  type used to point to Dem_Cfg_DataElementTableCol2ElmtInd */
typedef P2CONST(Dem_Cfg_DataElementTableCol2ElmtIndType, TYPEDEF, DEM_CONST) Dem_Cfg_DataElementTableCol2ElmtIndPtrType;

/**   \brief  type used to point to Dem_Cfg_DebounceData */
typedef P2VAR(Dem_Cfg_DebounceDataType, TYPEDEF, DEM_NVM_DATA_NOINIT) Dem_Cfg_DebounceDataPtrType;

/**   \brief  type used to point to Dem_Cfg_DebounceHiResTable */
typedef P2CONST(Dem_Cfg_DebounceHiResTableType, TYPEDEF, DEM_CONST) Dem_Cfg_DebounceHiResTablePtrType;

/**   \brief  type used to point to Dem_Cfg_DebounceLoResTable */
typedef P2CONST(Dem_Cfg_DebounceLoResTableType, TYPEDEF, DEM_CONST) Dem_Cfg_DebounceLoResTablePtrType;

/**   \brief  type used to point to Dem_Cfg_DebounceTable */
typedef P2CONST(Dem_Cfg_DebounceTableType, TYPEDEF, DEM_CONST) Dem_Cfg_DebounceTablePtrType;

/**   \brief  type used to point to Dem_Cfg_DtcGroupMask */
typedef P2CONST(Dem_Cfg_DtcGroupMaskType, TYPEDEF, DEM_CONST) Dem_Cfg_DtcGroupMaskPtrType;

/**   \brief  type used to point to Dem_Cfg_DtcTable */
typedef P2CONST(Dem_Cfg_DtcTableType, TYPEDEF, DEM_CONST) Dem_Cfg_DtcTablePtrType;

/**   \brief  type used to point to Dem_Cfg_DtrData */
typedef P2VAR(Dem_Cfg_DtrDataType, TYPEDEF, DEM_NVM_DATA_NOINIT) Dem_Cfg_DtrDataPtrType;

/**   \brief  type used to point to Dem_Cfg_DtrStatus */
typedef P2VAR(volatile Dem_Cfg_DtrStatusType, TYPEDEF, DEM_VAR_NOINIT) Dem_Cfg_DtrStatusPtrType;

/**   \brief  type used to point to Dem_Cfg_DtrTable */
typedef P2CONST(Dem_Cfg_DtrTableType, TYPEDEF, DEM_CONST) Dem_Cfg_DtrTablePtrType;

/**   \brief  type used to point to Dem_Cfg_DtrTableInd */
typedef P2CONST(Dem_Cfg_DtrTableIndType, TYPEDEF, DEM_CONST) Dem_Cfg_DtrTableIndPtrType;

/**   \brief  type used to point to Dem_Cfg_EnableConditionFulfilled */
typedef P2VAR(Dem_Cfg_EnableConditionFulfilledType, TYPEDEF, DEM_VAR_NOINIT) Dem_Cfg_EnableConditionFulfilledPtrType;

/**   \brief  type used to point to Dem_Cfg_EnableConditionGroupCounter */
typedef P2VAR(Dem_Cfg_EnableConditionGroupCounterType, TYPEDEF, DEM_VAR_NOINIT) Dem_Cfg_EnableConditionGroupCounterPtrType;

/**   \brief  type used to point to Dem_Cfg_EnableConditionGroupState */
typedef P2VAR(volatile Dem_Cfg_EnableConditionGroupStateType, TYPEDEF, DEM_VAR_NOINIT) Dem_Cfg_EnableConditionGroupStatePtrType;

/**   \brief  type used to point to Dem_Cfg_EnableConditionGroupTable */
typedef P2CONST(Dem_Cfg_EnableConditionGroupTableType, TYPEDEF, DEM_CONST) Dem_Cfg_EnableConditionGroupTablePtrType;

/**   \brief  type used to point to Dem_Cfg_EnableConditionGroupTableInd */
typedef P2CONST(Dem_Cfg_EnableConditionGroupTableIndType, TYPEDEF, DEM_CONST) Dem_Cfg_EnableConditionGroupTableIndPtrType;

/**   \brief  type used to point to Dem_Cfg_EnableConditionInitTable */
typedef P2CONST(Dem_Cfg_EnableConditionInitTableType, TYPEDEF, DEM_CONST) Dem_Cfg_EnableConditionInitTablePtrType;

/**   \brief  type used to point to Dem_Cfg_EnableConditionTable */
typedef P2CONST(Dem_Cfg_EnableConditionTableType, TYPEDEF, DEM_CONST) Dem_Cfg_EnableConditionTablePtrType;

/**   \brief  type used to point to Dem_Cfg_EventAvailableData */
typedef P2VAR(Dem_Cfg_EventAvailableDataType, TYPEDEF, DEM_NVM_DATA_NOINIT) Dem_Cfg_EventAvailableDataPtrType;

/**   \brief  type used to point to Dem_Cfg_EventAvailableDefault */
typedef P2CONST(Dem_Cfg_EventAvailableDefaultType, TYPEDEF, DEM_CONST) Dem_Cfg_EventAvailableDefaultPtrType;

/**   \brief  type used to point to Dem_Cfg_EventAvailableInVariant */
typedef P2CONST(Dem_Cfg_EventAvailableInVariantType, TYPEDEF, DEM_CONST) Dem_Cfg_EventAvailableInVariantPtrType;

/**   \brief  type used to point to Dem_Cfg_EventCycleStatus */
typedef P2VAR(volatile Dem_Cfg_EventCycleStatusType, TYPEDEF, DEM_VAR_NOINIT) Dem_Cfg_EventCycleStatusPtrType;

/**   \brief  type used to point to Dem_Cfg_EventDataChanged */
typedef P2CONST(Dem_EventDataChangedFPtrType, TYPEDEF, DEM_CONST) Dem_Cfg_EventDataChangedPtrType;

/**   \brief  type used to point to Dem_Cfg_EventDataCommitNumber */
typedef P2VAR(volatile Dem_Cfg_EventDataCommitNumberType, TYPEDEF, DEM_VAR_NOINIT) Dem_Cfg_EventDataCommitNumberPtrType;

/**   \brief  type used to point to Dem_Cfg_EventDebounceValue */
typedef P2VAR(volatile Dem_Cfg_EventDebounceValueType, TYPEDEF, DEM_VAR_NOINIT) Dem_Cfg_EventDebounceValuePtrType;

/**   \brief  type used to point to Dem_Cfg_EventInternalStatus */
typedef P2VAR(volatile Dem_Event_InternalStatusType, TYPEDEF, DEM_VAR_NOINIT) Dem_Cfg_EventInternalStatusPtrType;

/**   \brief  type used to point to Dem_Cfg_EventStatusChanged */
typedef P2CONST(Dem_EventStatusChangedFPtrType, TYPEDEF, DEM_CONST) Dem_Cfg_EventStatusChangedPtrType;

/**   \brief  type used to point to Dem_Cfg_EventTable */
typedef P2CONST(Dem_Cfg_EventTableType, TYPEDEF, DEM_CONST) Dem_Cfg_EventTablePtrType;

/**   \brief  type used to point to Dem_Cfg_EventTableInd */
typedef P2CONST(Dem_Cfg_EventTableIndType, TYPEDEF, DEM_CONST) Dem_Cfg_EventTableIndPtrType;

/**   \brief  type used to point to Dem_Cfg_EventTable_ERec2EventIdInd */
typedef P2CONST(Dem_Cfg_EventTable_ERec2EventIdIndType, TYPEDEF, DEM_CONST) Dem_Cfg_EventTable_ERec2EventIdIndPtrType;

/**   \brief  type used to point to Dem_Cfg_EventTable_ObdRdyGroup2EventIdInd */
typedef P2CONST(Dem_Cfg_EventTable_ObdRdyGroup2EventIdIndType, TYPEDEF, DEM_CONST) Dem_Cfg_EventTable_ObdRdyGroup2EventIdIndPtrType;

/**   \brief  type used to point to Dem_Cfg_ExtendedDataRecordIteratorTable */
typedef P2VAR(Dem_Cfg_ExtendedDataRecordIterator_FilterType, TYPEDEF, DEM_VAR_NOINIT) Dem_Cfg_ExtendedDataRecordIteratorTablePtrType;

/**   \brief  type used to point to Dem_Cfg_ExtendedDataRecordTable */
typedef P2CONST(Dem_Cfg_ExtendedDataRecordTableType, TYPEDEF, DEM_CONST) Dem_Cfg_ExtendedDataRecordTablePtrType;

/**   \brief  type used to point to Dem_Cfg_ExtendedDataTable */
typedef P2CONST(Dem_Cfg_ExtendedDataTableType, TYPEDEF, DEM_CONST) Dem_Cfg_ExtendedDataTablePtrType;

/**   \brief  type used to point to Dem_Cfg_FilterInfoTable */
typedef P2VAR(Dem_Cfg_FilterData_InfoType, TYPEDEF, DEM_VAR_NOINIT) Dem_Cfg_FilterInfoTablePtrType;

/**   \brief  type used to point to Dem_Cfg_FilterReportedEvents */
typedef P2VAR(Dem_Cfg_FilterReportedEventsType, TYPEDEF, DEM_VAR_NOINIT) Dem_Cfg_FilterReportedEventsPtrType;

/**   \brief  type used to point to Dem_Cfg_FreezeFrameData */
typedef P2VAR(Dem_Cfg_FreezeFrameDataType, TYPEDEF, DEM_NVM_DATA_NOINIT) Dem_Cfg_FreezeFrameDataPtrType;

/**   \brief  type used to point to Dem_Cfg_FreezeFrameIteratorTable */
typedef P2VAR(Dem_Cfg_FreezeFrameIterator_FilterType, TYPEDEF, DEM_VAR_NOINIT) Dem_Cfg_FreezeFrameIteratorTablePtrType;

/**   \brief  type used to point to Dem_Cfg_FreezeFrameNumTable */
typedef P2CONST(Dem_Cfg_FreezeFrameNumTableType, TYPEDEF, DEM_CONST) Dem_Cfg_FreezeFrameNumTablePtrType;

/**   \brief  type used to point to Dem_Cfg_FreezeFrameTable */
typedef P2CONST(Dem_Cfg_FreezeFrameTableType, TYPEDEF, DEM_CONST) Dem_Cfg_FreezeFrameTablePtrType;

/**   \brief  type used to point to Dem_Cfg_GeneralJ1939Table */
typedef P2CONST(Dem_Cfg_GeneralJ1939TableType, TYPEDEF, DEM_CONST) Dem_Cfg_GeneralJ1939TablePtrType;

/**   \brief  type used to point to Dem_Cfg_GeneralObdInput */
typedef P2CONST(Dem_Cfg_GeneralObdInputType, TYPEDEF, DEM_CONST) Dem_Cfg_GeneralObdInputPtrType;

/**   \brief  type used to point to Dem_Cfg_GlobalIndicatorStates */
typedef P2VAR(Dem_Cfg_GlobalIndicatorStatesType, TYPEDEF, DEM_VAR_NOINIT) Dem_Cfg_GlobalIndicatorStatesPtrType;

/**   \brief  type used to point to Dem_Cfg_IndicatorBlinking */
typedef P2VAR(Dem_Cfg_IndicatorBlinkingType, TYPEDEF, DEM_VAR_NOINIT) Dem_Cfg_IndicatorBlinkingPtrType;

/**   \brief  type used to point to Dem_Cfg_IndicatorContinuous */
typedef P2VAR(Dem_Cfg_IndicatorContinuousType, TYPEDEF, DEM_VAR_NOINIT) Dem_Cfg_IndicatorContinuousPtrType;

/**   \brief  type used to point to Dem_Cfg_IndicatorFastFlash */
typedef P2VAR(Dem_Cfg_IndicatorFastFlashType, TYPEDEF, DEM_VAR_NOINIT) Dem_Cfg_IndicatorFastFlashPtrType;

/**   \brief  type used to point to Dem_Cfg_IndicatorSlowFlash */
typedef P2VAR(Dem_Cfg_IndicatorSlowFlashType, TYPEDEF, DEM_VAR_NOINIT) Dem_Cfg_IndicatorSlowFlashPtrType;

/**   \brief  type used to point to Dem_Cfg_InitMonListForFunc */
typedef P2CONST(Dem_Cfg_InitMonListForFuncType, TYPEDEF, DEM_CONST) Dem_Cfg_InitMonListForFuncPtrType;

/**   \brief  type used to point to Dem_Cfg_InitMonitorForEvent */
typedef P2CONST(Dem_InitMonitorForEventFPtrType, TYPEDEF, DEM_CONST) Dem_Cfg_InitMonitorForEventPtrType;

/**   \brief  type used to point to Dem_Cfg_InitMonitorsForFunc */
typedef P2CONST(Dem_InitMonitorForFuncFPtrType, TYPEDEF, DEM_CONST) Dem_Cfg_InitMonitorsForFuncPtrType;

/**   \brief  type used to point to Dem_Cfg_J1939NodeId */
typedef P2CONST(Dem_Cfg_J1939NodeIdType, TYPEDEF, DEM_CONST) Dem_Cfg_J1939NodeIdPtrType;

/**   \brief  type used to point to Dem_Cfg_J1939NodeIdInd */
typedef P2CONST(Dem_Cfg_J1939NodeIdIndType, TYPEDEF, DEM_CONST) Dem_Cfg_J1939NodeIdIndPtrType;

/**   \brief  type used to point to Dem_Cfg_J1939NodeIndicator */
typedef P2CONST(Dem_Cfg_J1939NodeIndicatorType, TYPEDEF, DEM_CONST) Dem_Cfg_J1939NodeIndicatorPtrType;

/**   \brief  type used to point to Dem_Cfg_MemoryBlockId */
typedef P2CONST(Dem_Cfg_MemoryBlockIdType, TYPEDEF, DEM_CONST) Dem_Cfg_MemoryBlockIdPtrType;

/**   \brief  type used to point to Dem_Cfg_MemoryBlockIdToMemoryEntryId */
typedef P2CONST(Dem_Cfg_MemoryEntryHandleType, TYPEDEF, DEM_CONST) Dem_Cfg_MemoryBlockIdToMemoryEntryIdPtrType;

/**   \brief  type used to point to Dem_Cfg_MemoryDataPtr */
typedef P2CONST(Dem_NvDataPtrType, TYPEDEF, DEM_CONST) Dem_Cfg_MemoryDataPtrPtrType;

/**   \brief  type used to point to Dem_Cfg_MemoryDataSize */
typedef P2CONST(Dem_Cfg_MemoryDataSizeType, TYPEDEF, DEM_CONST) Dem_Cfg_MemoryDataSizePtrType;

/**   \brief  type used to point to Dem_Cfg_MemoryEntry */
typedef P2CONST(Dem_SharedMemoryEntryPtrType, TYPEDEF, DEM_CONST) Dem_Cfg_MemoryEntryPtrType;

/**   \brief  type used to point to Dem_Cfg_MemoryEntryInit */
typedef P2CONST(Dem_Cfg_PrimaryEntryType, TYPEDEF, DEM_CONST) Dem_Cfg_MemoryEntryInitPtrType;

/**   \brief  type used to point to Dem_Cfg_MemoryStatus */
typedef P2VAR(Dem_Cfg_MemoryStatusType, TYPEDEF, DEM_VAR_NOINIT) Dem_Cfg_MemoryStatusPtrType;

/**   \brief  type used to point to Dem_Cfg_MidTable */
typedef P2CONST(Dem_Cfg_MidTableType, TYPEDEF, DEM_CONST) Dem_Cfg_MidTablePtrType;

/**   \brief  type used to point to Dem_Cfg_MirrorData */
typedef P2VAR(Dem_Cfg_MirrorDataType, TYPEDEF, DEM_NVM_DATA_NOINIT) Dem_Cfg_MirrorDataPtrType;

/**   \brief  type used to point to Dem_Cfg_NormalIndicatorTable */
typedef P2CONST(Dem_Cfg_NormalIndicatorTableType, TYPEDEF, DEM_CONST) Dem_Cfg_NormalIndicatorTablePtrType;

/**   \brief  type used to point to Dem_Cfg_ObdIumprData */
typedef P2VAR(Dem_Cfg_ObdIumprDataType, TYPEDEF, DEM_NVM_DATA_NOINIT) Dem_Cfg_ObdIumprDataPtrType;

/**   \brief  type used to point to Dem_Cfg_ObdIumprUpdatePending */
typedef P2VAR(Dem_Cfg_ObdIumprUpdatePendingType, TYPEDEF, DEM_VAR_NOINIT) Dem_Cfg_ObdIumprUpdatePendingPtrType;

/**   \brief  type used to point to Dem_Cfg_PermanentData */
typedef P2VAR(Dem_Cfg_PermanentDataType, TYPEDEF, DEM_NVM_DATA_NOINIT) Dem_Cfg_PermanentDataPtrType;

/**   \brief  type used to point to Dem_Cfg_PidTable */
typedef P2CONST(Dem_Cfg_PidTableType, TYPEDEF, DEM_CONST) Dem_Cfg_PidTablePtrType;

/**   \brief  type used to point to Dem_Cfg_Prestorage */
typedef P2VAR(Dem_Cfg_PrestorageType, TYPEDEF, DEM_VAR_NOINIT) Dem_Cfg_PrestoragePtrType;

/**   \brief  type used to point to Dem_Cfg_PrestorageIndex */
typedef P2VAR(Dem_Cfg_PrestorageIndexType, TYPEDEF, DEM_VAR_NOINIT) Dem_Cfg_PrestorageIndexPtrType;

/**   \brief  type used to point to Dem_Cfg_PrimaryChronology */
typedef P2VAR(Dem_Cfg_MemoryIndexType, TYPEDEF, DEM_VAR_NOINIT) Dem_Cfg_PrimaryChronologyPtrType;

/**   \brief  type used to point to Dem_Cfg_PrimaryEntry_0 */
typedef P2VAR(Dem_Cfg_PrimaryEntryType, TYPEDEF, DEM_NVM_DATA_NOINIT) Dem_Cfg_PrimaryEntry_0PtrType;

/**   \brief  type used to point to Dem_Cfg_PrimaryEntry_1 */
typedef P2VAR(Dem_Cfg_PrimaryEntryType, TYPEDEF, DEM_NVM_DATA_NOINIT) Dem_Cfg_PrimaryEntry_1PtrType;

/**   \brief  type used to point to Dem_Cfg_PrimaryEntry_2 */
typedef P2VAR(Dem_Cfg_PrimaryEntryType, TYPEDEF, DEM_NVM_DATA_NOINIT) Dem_Cfg_PrimaryEntry_2PtrType;

/**   \brief  type used to point to Dem_Cfg_PrimaryEntry_3 */
typedef P2VAR(Dem_Cfg_PrimaryEntryType, TYPEDEF, DEM_NVM_DATA_NOINIT) Dem_Cfg_PrimaryEntry_3PtrType;

/**   \brief  type used to point to Dem_Cfg_PrimaryEntry_4 */
typedef P2VAR(Dem_Cfg_PrimaryEntryType, TYPEDEF, DEM_NVM_DATA_NOINIT) Dem_Cfg_PrimaryEntry_4PtrType;

/**   \brief  type used to point to Dem_Cfg_PrimaryEntry_5 */
typedef P2VAR(Dem_Cfg_PrimaryEntryType, TYPEDEF, DEM_NVM_DATA_NOINIT) Dem_Cfg_PrimaryEntry_5PtrType;

/**   \brief  type used to point to Dem_Cfg_PrimaryEntry_6 */
typedef P2VAR(Dem_Cfg_PrimaryEntryType, TYPEDEF, DEM_NVM_DATA_NOINIT) Dem_Cfg_PrimaryEntry_6PtrType;

/**   \brief  type used to point to Dem_Cfg_PrimaryEntry_7 */
typedef P2VAR(Dem_Cfg_PrimaryEntryType, TYPEDEF, DEM_NVM_DATA_NOINIT) Dem_Cfg_PrimaryEntry_7PtrType;

/**   \brief  type used to point to Dem_Cfg_RatioIdTable */
typedef P2CONST(Dem_Cfg_RatioIdTableType, TYPEDEF, DEM_CONST) Dem_Cfg_RatioIdTablePtrType;

/**   \brief  type used to point to Dem_Cfg_ReadinessGroupTable */
typedef P2CONST(Dem_Cfg_ReadinessGroupTableType, TYPEDEF, DEM_CONST) Dem_Cfg_ReadinessGroupTablePtrType;

/**   \brief  type used to point to Dem_Cfg_ReadoutBuffer */
typedef P2VAR(Dem_Cfg_ReadoutBufferEntryType, TYPEDEF, DEM_VAR_NOINIT) Dem_Cfg_ReadoutBufferPtrType;

/**   \brief  type used to point to Dem_Cfg_ReportedEventsOfFilter */
typedef P2VAR(Dem_Cfg_ReportedEventsType, TYPEDEF, DEM_VAR_NOINIT) Dem_Cfg_ReportedEventsOfFilterPtrType;

/**   \brief  type used to point to Dem_Cfg_SatelliteInfo */
typedef P2CONST(Dem_Cfg_SatelliteInfoType, TYPEDEF, DEM_CONST) Dem_Cfg_SatelliteInfoPtrType;

/**   \brief  type used to point to Dem_Cfg_SatelliteInfo0 */
typedef P2VAR(Dem_Cfg_SatelliteInfoType0, TYPEDEF, DEM_VAR_ZERO_INIT) Dem_Cfg_SatelliteInfo0PtrType;

/**   \brief  type used to point to Dem_Cfg_SatelliteTimeDebounceInfo */
typedef P2CONST(Dem_Cfg_SatelliteTimeDebounceInfoType, TYPEDEF, DEM_CONST) Dem_Cfg_SatelliteTimeDebounceInfoPtrType;

/**   \brief  type used to point to Dem_Cfg_SecondaryChronology */
typedef P2VAR(Dem_Cfg_MemoryIndexType, TYPEDEF, DEM_VAR_NOINIT) Dem_Cfg_SecondaryChronologyPtrType;

/**   \brief  type used to point to Dem_Cfg_SpecialIndicatorTable */
typedef P2CONST(Dem_Cfg_SpecialIndicatorTableType, TYPEDEF, DEM_CONST) Dem_Cfg_SpecialIndicatorTablePtrType;

/**   \brief  type used to point to Dem_Cfg_StartIdx500miDenRatioTable */
typedef P2CONST(Dem_Cfg_StartIdx500miDenRatioTableType, TYPEDEF, DEM_CONST) Dem_Cfg_StartIdx500miDenRatioTablePtrType;

/**   \brief  type used to point to Dem_Cfg_StatusData */
typedef P2VAR(Dem_Cfg_StatusDataType, TYPEDEF, DEM_NVM_DATA_NOINIT) Dem_Cfg_StatusDataPtrType;

/**   \brief  type used to point to Dem_Cfg_StorageConditionFulfilled */
typedef P2VAR(Dem_Cfg_StorageConditionFulfilledType, TYPEDEF, DEM_VAR_NOINIT) Dem_Cfg_StorageConditionFulfilledPtrType;

/**   \brief  type used to point to Dem_Cfg_StorageConditionGroupCounter */
typedef P2VAR(Dem_Cfg_StorageConditionGroupCounterType, TYPEDEF, DEM_VAR_NOINIT) Dem_Cfg_StorageConditionGroupCounterPtrType;

/**   \brief  type used to point to Dem_Cfg_StorageConditionGroupTable */
typedef P2CONST(Dem_Cfg_StorageConditionGroupTableType, TYPEDEF, DEM_CONST) Dem_Cfg_StorageConditionGroupTablePtrType;

/**   \brief  type used to point to Dem_Cfg_StorageConditionGroupTableInd */
typedef P2CONST(Dem_Cfg_StorageConditionGroupTableIndType, TYPEDEF, DEM_CONST) Dem_Cfg_StorageConditionGroupTableIndPtrType;

/**   \brief  type used to point to Dem_Cfg_StorageConditionInitTable */
typedef P2CONST(Dem_Cfg_StorageConditionInitTableType, TYPEDEF, DEM_CONST) Dem_Cfg_StorageConditionInitTablePtrType;

/**   \brief  type used to point to Dem_Cfg_StorageConditionTable */
typedef P2CONST(Dem_Cfg_StorageConditionTableType, TYPEDEF, DEM_CONST) Dem_Cfg_StorageConditionTablePtrType;

/**   \brief  type used to point to Dem_Cfg_SupportedMidsTable */
typedef P2CONST(Dem_Cfg_SupportedMidsTableType, TYPEDEF, DEM_CONST) Dem_Cfg_SupportedMidsTablePtrType;

/**   \brief  type used to point to Dem_Cfg_TimeSeriesChronology */
typedef P2VAR(Dem_Cfg_MemoryIndexType, TYPEDEF, DEM_VAR_NOINIT) Dem_Cfg_TimeSeriesChronologyPtrType;

/**   \brief  type used to point to Dem_Cfg_TimeSeriesEntryInit */
typedef P2CONST(Dem_Cfg_TimeSeriesEntryType, TYPEDEF, DEM_CONST) Dem_Cfg_TimeSeriesEntryInitPtrType;

/** 
  \}
*/ 

/** 
  \defgroup  Dem_CfgPCRootValueTypes  Dem_Cfg Root Value Types (PRE_COMPILE)
  \brief  These type definitions are used for value representations in root arrays.
  \{
*/ 
/**   \brief  type used in Dem_PCConfig */
typedef struct sDem_PCConfigType
{
  uint8 Dem_PCConfigNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} Dem_PCConfigType;

typedef Dem_PCConfigType Dem_ConfigType;  /**< A structure type is present for data in each configuration class. This typedef redefines the probably different name to the specified one. */

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
  GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/
/**********************************************************************************************************************
  Dem_Cfg_CallbackClearEventAllowed
**********************************************************************************************************************/
#define DEM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(Dem_ClearEventAllowedFPtrType, DEM_CONST) Dem_Cfg_CallbackClearEventAllowed[5];  /* PRQA S 0777 */  /* MD_MSR_Rule5.1 */
#define DEM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_CycleIdTable
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_CycleIdTable
  \details
  Element        Description
  MaskedBits     contains bitcoded the boolean data of Dem_Cfg_EndsOnInitOfCycleIdTable, Dem_Cfg_UsedForAgingOfCycleIdTable
  OpCycleType    DemOperationCycleType of the DemOperationCycle: [DEM_CFG_OPCYC_IGNITION, DEM_CFG_OPCYC_OBD_DCY, DEM_CFG_OPCYC_OTHER, DEM_CFG_OPCYC_POWER, DEM_CFG_OPCYC_TIME, DEM_CFG_OPCYC_WARMUP, DEM_CFG_OPCYC_IGNITION_HYBRID, DEM_CFG_OPCYC_AGING]
*/ 
#define DEM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(Dem_Cfg_CycleIdTableType, DEM_CONST) Dem_Cfg_CycleIdTable[3];
#define DEM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_DataCollectionTable
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_DataCollectionTable
  \details
  Element                                Description
  IdNumber                           
  CollectionSize                     
  DataElementTableCol2ElmtIndEndIdx      the end index of the 0:n relation pointing to Dem_Cfg_DataElementTableCol2ElmtInd
  DataElementTableCol2ElmtIndStartIdx    the start index of the 0:n relation pointing to Dem_Cfg_DataElementTableCol2ElmtInd
  StorageKind                        
*/ 
#define DEM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(Dem_Cfg_DataCollectionTableType, DEM_CONST) Dem_Cfg_DataCollectionTable[8];
#define DEM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_DataElementTable
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_DataElementTable
  \details
  Element             Description
  DataIsStoredInNV
  ElementKind         DataElement kind, returned by Dem_Cfg_DataCallbackType()
  ElementSize         Size of data element in Byte.
  ReadDataFunc        C-function for getting the data. Its signature depends on ElementKind: With value(s) DEM_CFG_DATA_FROM_CBK_WITH_EVENTID use: Std_ReturnType (*)(uint8* Buffer, uint16 EventId); - and use: Std_ReturnType (*)(uint8* Buffer); with the other values DEM_CFG_DATA_FROM_CBK, DEM_CFG_DATA_FROM_SR_PORT_BOOLEAN, DEM_CFG_DATA_FROM_SR_PORT_SINT16, DEM_CFG_DATA_FROM_SR_PORT_SINT16_INTEL, DEM_CFG_DATA_FROM_SR_PORT_SINT32, DEM_CFG_DATA_FROM_SR_PORT_SINT32_INTEL, DEM_CFG_DATA_FROM_SR_PORT_SINT8, DEM_CFG_DATA_FROM_SR_PORT_SINT8_N, DEM_CFG_DATA_FROM_SR_PORT_UINT16, DEM_CFG_DATA_FROM_SR_PORT_UINT16_INTEL, DEM_CFG_DATA_FROM_SR_PORT_UINT32, DEM_CFG_DATA_FROM_SR_PORT_UINT32_INTEL, DEM_CFG_DATA_FROM_SR_PORT_UINT8, DEM_CFG_DATA_FROM_SR_PORT_UINT8_N.
*/ 
#define DEM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(Dem_Cfg_DataElementTableType, DEM_CONST) Dem_Cfg_DataElementTable[10];
#define DEM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_DataElementTableCol2ElmtInd
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_DataElementTableCol2ElmtInd
  \brief  the indexes of the 1:1 sorted relation pointing to Dem_Cfg_DataElementTable
*/ 
#define DEM_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(Dem_Cfg_DataElementTableCol2ElmtIndType, DEM_CONST) Dem_Cfg_DataElementTableCol2ElmtInd[11];  /* PRQA S 0777 */  /* MD_MSR_Rule5.1 */
#define DEM_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_DebounceTable
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_DebounceTable
  \details
  Element                   Description
  FailedThreshold           DemDebounceCounterFailedThreshold of the DemEventParameter/DemEventClass/DemDebounceAlgorithmClass/DemDebounceCounterBased
  PassedThreshold           DemDebounceCounterPassedThreshold of the DemEventParameter/DemEventClass/DemDebounceAlgorithmClass/DemDebounceCounterBased
  DecrementStepSize         (-1) * DemDebounceCounterDecrementStepSize of the DemEventParameter/DemEventClass/DemDebounceAlgorithmClass/DemDebounceCounterBased
  IncrementStepSize         DemDebounceCounterIncrementStepSize of the DemEventParameter/DemEventClass/DemDebounceAlgorithmClass/DemDebounceCounterBased
  EventDebounceAlgorithm    Used DemEventParameter/DemEventClass/DemDebounceAlgorithmClass
  MaskedBits                contains bitcoded the boolean data of Dem_Cfg_DebounceContinuousOfDebounceTable, Dem_Cfg_EventDebounceBehaviorOfDebounceTable, Dem_Cfg_JumpDownOfDebounceTable, Dem_Cfg_JumpUpOfDebounceTable, Dem_Cfg_StorageOfDebounceTable
*/ 
#define DEM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(Dem_Cfg_DebounceTableType, DEM_CONST) Dem_Cfg_DebounceTable[9];
#define DEM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_DtcTable
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_DtcTable
  \details
  Element           Description
  UdsDtc        
  FunctionalUnit
*/ 
#define DEM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(Dem_Cfg_DtcTableType, DEM_CONST) Dem_Cfg_DtcTable[16];
#define DEM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_EnableConditionGroupTableInd
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_EnableConditionGroupTableInd
  \brief  the indexes of the 1:1 sorted relation pointing to Dem_Cfg_EnableConditionGroupTable
*/ 
#define DEM_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(Dem_Cfg_EnableConditionGroupTableIndType, DEM_CONST) Dem_Cfg_EnableConditionGroupTableInd[11];  /* PRQA S 0777 */  /* MD_MSR_Rule5.1 */
#define DEM_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_EnableConditionInitTable
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_EnableConditionInitTable
  \details
  Element            Description
  FulfilledAtInit    Initial value: 'FALSE' condition is not fulfilled, 'TRUE' condition is fulfilled
*/ 
#define DEM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(Dem_Cfg_EnableConditionInitTableType, DEM_CONST) Dem_Cfg_EnableConditionInitTable[6];  /* PRQA S 0777 */  /* MD_MSR_Rule5.1 */
#define DEM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_EnableConditionTable
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_EnableConditionTable
  \brief  Map each EnableCondition(Id) to the referring EnableConditionGroups - this is reverse direction of the AUTOSAR configuration model.
  \details
  Element                                 Description
  EnableConditionGroupTableIndEndIdx      the end index of the 0:n relation pointing to Dem_Cfg_EnableConditionGroupTableInd
  EnableConditionGroupTableIndStartIdx    the start index of the 0:n relation pointing to Dem_Cfg_EnableConditionGroupTableInd
*/ 
#define DEM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(Dem_Cfg_EnableConditionTableType, DEM_CONST) Dem_Cfg_EnableConditionTable[6];
#define DEM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_EventTable
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_EventTable
  \details
  Element                         Description
  AgingCycleCounterThreshold      DemAgingCycleCounterThreshold of the DemEventParameter/DemEventClass. If AgingAllowedOfEventTable==FALSE and DemAgingCycleCounterThreshold does not exist '255' is set. If AgingAllowedOfEventTable==TRUE and DemAgingCycleCounterThreshold does not exist '0' is set.
  AgingCycleId                    DemOperationCycle (ID) referenced by DemEventParameter/DemEventClass/DemAgingCycleRef
  CallbackClearEventAllowedIdx    the index of the 0:1 relation pointing to Dem_Cfg_CallbackClearEventAllowed
  DebounceTableIdx                the index of the 1:1 relation pointing to Dem_Cfg_DebounceTable
  DtcTableIdx                     the index of the 1:1 relation pointing to Dem_Cfg_DtcTable
  EnableConditionGroupTableIdx    the index of the 1:1 relation pointing to Dem_Cfg_EnableConditionGroupTable
  EventKind                       DemEventKind of the DemEventParameter
  EventPriority                   DemEventParameter/DemEventClass/DemEventPriority, values [1..255] for the configuration range [1..255].
  MaskedBits                      contains bitcoded the boolean data of Dem_Cfg_AgingAllowedOfEventTable, Dem_Cfg_EventLatchTFOfEventTable, Dem_Cfg_OBDVisibilityDelayedUntilDcyQualificationOfEventTable
*/ 
#define DEM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(Dem_Cfg_EventTableType, DEM_CONST) Dem_Cfg_EventTable[16];
#define DEM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_ExtendedDataTable
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_ExtendedDataTable
  \details
  Element                                   Description
  DataCollectionTableEdr2CollIndEndIdx      the end index of the 0:n relation pointing to Dem_Cfg_DataCollectionTableEdr2CollInd
  DataCollectionTableEdr2CollIndStartIdx    the start index of the 0:n relation pointing to Dem_Cfg_DataCollectionTableEdr2CollInd
  MaxRecordSize                         
*/ 
#define DEM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(Dem_Cfg_ExtendedDataTableType, DEM_CONST) Dem_Cfg_ExtendedDataTable[2];
#define DEM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_FreezeFrameTable
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_FreezeFrameTable
  \details
  Element                                   Description
  DataCollectionTableFfm2CollIndEndIdx      the end index of the 0:n relation pointing to Dem_Cfg_DataCollectionTableFfm2CollInd
  DataCollectionTableFfm2CollIndStartIdx    the start index of the 0:n relation pointing to Dem_Cfg_DataCollectionTableFfm2CollInd
  RecordSizeUds                             Summarized size of did data, did numbers and snapshot header (i.e. dynamical payload size of the uds response message).
*/ 
#define DEM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(Dem_Cfg_FreezeFrameTableType, DEM_CONST) Dem_Cfg_FreezeFrameTable[2];
#define DEM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_MemoryBlockId
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_MemoryBlockId
  \brief  The array contains these items: Admin, Status, 8 * Primary
*/ 
#define DEM_START_SEC_CONST_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(Dem_Cfg_MemoryBlockIdType, DEM_CONST) Dem_Cfg_MemoryBlockId[10];
#define DEM_STOP_SEC_CONST_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_MemoryBlockIdToMemoryEntryId
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_MemoryBlockIdToMemoryEntryId
  \brief  The array contains these items: Admin, Status, 8 * Primary
*/ 
#define DEM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(Dem_Cfg_MemoryEntryHandleType, DEM_CONST) Dem_Cfg_MemoryBlockIdToMemoryEntryId[10];  /* PRQA S 0777 */  /* MD_MSR_Rule5.1 */
#define DEM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_MemoryDataPtr
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_MemoryDataPtr
  \brief  The array contains these items: Admin, Status, 8 * Primary
*/ 
#define DEM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(Dem_NvDataPtrType, DEM_CONST) Dem_Cfg_MemoryDataPtr[10];
#define DEM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_MemoryDataSize
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_MemoryDataSize
  \brief  The array contains these items: Admin, Status, 8 * Primary
*/ 
#define DEM_START_SEC_CONST_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(Dem_Cfg_MemoryDataSizeType, DEM_CONST) Dem_Cfg_MemoryDataSize[10];
#define DEM_STOP_SEC_CONST_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_MemoryEntry
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_MemoryEntry
  \brief  The array contains these items: 8 * Primary, ReadoutBuffer; size = DEM_CFG_GLOBAL_PRIMARY_SIZE + DEM_CFG_GLOBAL_SECONDARY_SIZE + DEM_CFG_NUMBER_OF_READOUTBUFFERS * DEM_CFG_NUMBER_OF_SUBEVENT_DATA_READOUTBUFFERS
*/ 
#define DEM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(Dem_SharedMemoryEntryPtrType, DEM_CONST) Dem_Cfg_MemoryEntry[9];
#define DEM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_MemoryEntryInit
**********************************************************************************************************************/
#define DEM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(Dem_Cfg_PrimaryEntryType, DEM_CONST) Dem_Cfg_MemoryEntryInit;
#define DEM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_TimeSeriesEntryInit
**********************************************************************************************************************/
#define DEM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(Dem_Cfg_TimeSeriesEntryType, DEM_CONST) Dem_Cfg_TimeSeriesEntryInit;
#define DEM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_AdminData
**********************************************************************************************************************/
#define DEM_START_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(Dem_Cfg_AdminDataType, DEM_NVM_DATA_NOINIT) Dem_Cfg_AdminData;
#define DEM_STOP_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_ClearDTCTable
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_ClearDTCTable
  \brief  size = DEM_CFG_NUMBER_OF_CLEARDTCS
*/ 
#define DEM_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(Dem_ClearDTC_DataType, DEM_VAR_NOINIT) Dem_Cfg_ClearDTCTable[1];
#define DEM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_CommitBuffer
**********************************************************************************************************************/
#define DEM_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(Dem_Cfg_CommitBufferType, DEM_VAR_NOINIT) Dem_Cfg_CommitBuffer;  /* PRQA S 0759 */  /* MD_MSR_Union */
#define DEM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_DTCSelectorTable
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_DTCSelectorTable
  \brief  size = DEM_CFG_NUMBER_OF_DTCSELECTORS
*/ 
#define DEM_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(Dem_DTCSelector_DataType, DEM_VAR_NOINIT) Dem_Cfg_DTCSelectorTable[1];
#define DEM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_EnableConditionFulfilled
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_EnableConditionFulfilled
  \brief  (DEM_CFG_SUPPORT_ENABLE_CONDITIONS == STD_ON) or there are internal EnableConditions. Table index: Condition ID. Table value: current condition state 'FALSE' not fulfilled, 'TRUE' fulfilled.
*/ 
#define DEM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(Dem_Cfg_EnableConditionFulfilledType, DEM_VAR_NOINIT) Dem_Cfg_EnableConditionFulfilled[6];  /* PRQA S 0777 */  /* MD_MSR_Rule5.1 */
#define DEM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_EnableConditionGroupCounter
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_EnableConditionGroupCounter
  \brief  (DEM_CFG_SUPPORT_ENABLE_CONDITIONS == STD_ON) or there are internal EnableConditions. Table index: Condition group number. Table value: count of conditions in state 'enable'.
*/ 
#define DEM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(Dem_Cfg_EnableConditionGroupCounterType, DEM_VAR_NOINIT) Dem_Cfg_EnableConditionGroupCounter[4];  /* PRQA S 0777 */  /* MD_MSR_Rule5.1 */
#define DEM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_EnableConditionGroupState
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_EnableConditionGroupState
  \brief  (DEM_CFG_SUPPORT_ENABLE_CONDITIONS == STD_ON) or there are internal EnableConditions. Table index: Condition group number. Table value: count of conditions in state 'enable'.
*/ 
#define DEM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern volatile VAR(Dem_Cfg_EnableConditionGroupStateType, DEM_VAR_NOINIT) Dem_Cfg_EnableConditionGroupState[4];  /* PRQA S 0777 */  /* MD_MSR_Rule5.1 */
#define DEM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_EventDataCommitNumber
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_EventDataCommitNumber
  \brief  Index = Index in Dem_Cfg_Eventtable
*/ 
#define DEM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern volatile VAR(Dem_Cfg_EventDataCommitNumberType, DEM_VAR_NOINIT) Dem_Cfg_EventDataCommitNumber[16];
#define DEM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_EventDebounceValue
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_EventDebounceValue
  \brief  size = DEM_G_NUMBER_OF_EVENTS
*/ 
#define DEM_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern volatile VAR(Dem_Cfg_EventDebounceValueType, DEM_VAR_NOINIT) Dem_Cfg_EventDebounceValue[16];
#define DEM_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_EventInternalStatus
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_EventInternalStatus
  \brief  size = DEM_G_NUMBER_OF_EVENTS
*/ 
#define DEM_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern volatile VAR(Dem_Event_InternalStatusType, DEM_VAR_NOINIT) Dem_Cfg_EventInternalStatus[16];
#define DEM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_ExtendedDataRecordIteratorTable
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_ExtendedDataRecordIteratorTable
  \brief  size = 1
*/ 
#define DEM_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(Dem_Cfg_ExtendedDataRecordIterator_FilterType, DEM_VAR_NOINIT) Dem_Cfg_ExtendedDataRecordIteratorTable[1];  /* PRQA S 0777 */  /* MD_MSR_Rule5.1 */
#define DEM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_FilterInfoTable
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_FilterInfoTable
  \brief  size = DEM_CFG_NUMBER_OF_FILTER
*/ 
#define DEM_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(Dem_Cfg_FilterData_InfoType, DEM_VAR_NOINIT) Dem_Cfg_FilterInfoTable[1];
#define DEM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_FilterReportedEvents
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_FilterReportedEvents
  \brief  size = ceiling( DEM_G_NUMBER_OF_EVENTS / 8 )
*/ 
#define DEM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(Dem_Cfg_FilterReportedEventsType, DEM_VAR_NOINIT) Dem_Cfg_FilterReportedEvents[2];
#define DEM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_FreezeFrameIteratorTable
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_FreezeFrameIteratorTable
  \brief  size = DEM_CFG_NUMBER_OF_FREEZEFRAMEITERATORS
*/ 
#define DEM_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(Dem_Cfg_FreezeFrameIterator_FilterType, DEM_VAR_NOINIT) Dem_Cfg_FreezeFrameIteratorTable[1];  /* PRQA S 0777 */  /* MD_MSR_Rule5.1 */
#define DEM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_MemoryStatus
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_MemoryStatus
  \brief  The array contains these items: Admin, Status, 8 * Primary
*/ 
#define DEM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(Dem_Cfg_MemoryStatusType, DEM_VAR_NOINIT) Dem_Cfg_MemoryStatus[10];
#define DEM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_PrimaryChronology
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_PrimaryChronology
  \brief  size = DEM_CFG_GLOBAL_PRIMARY_SIZE
*/ 
#define DEM_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(Dem_Cfg_MemoryIndexType, DEM_VAR_NOINIT) Dem_Cfg_PrimaryChronology[8];
#define DEM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_PrimaryEntry_0
**********************************************************************************************************************/
#define DEM_START_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(Dem_Cfg_PrimaryEntryType, DEM_NVM_DATA_NOINIT) Dem_Cfg_PrimaryEntry_0;
#define DEM_STOP_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_PrimaryEntry_1
**********************************************************************************************************************/
#define DEM_START_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(Dem_Cfg_PrimaryEntryType, DEM_NVM_DATA_NOINIT) Dem_Cfg_PrimaryEntry_1;
#define DEM_STOP_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_PrimaryEntry_2
**********************************************************************************************************************/
#define DEM_START_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(Dem_Cfg_PrimaryEntryType, DEM_NVM_DATA_NOINIT) Dem_Cfg_PrimaryEntry_2;
#define DEM_STOP_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_PrimaryEntry_3
**********************************************************************************************************************/
#define DEM_START_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(Dem_Cfg_PrimaryEntryType, DEM_NVM_DATA_NOINIT) Dem_Cfg_PrimaryEntry_3;
#define DEM_STOP_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_PrimaryEntry_4
**********************************************************************************************************************/
#define DEM_START_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(Dem_Cfg_PrimaryEntryType, DEM_NVM_DATA_NOINIT) Dem_Cfg_PrimaryEntry_4;
#define DEM_STOP_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_PrimaryEntry_5
**********************************************************************************************************************/
#define DEM_START_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(Dem_Cfg_PrimaryEntryType, DEM_NVM_DATA_NOINIT) Dem_Cfg_PrimaryEntry_5;
#define DEM_STOP_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_PrimaryEntry_6
**********************************************************************************************************************/
#define DEM_START_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(Dem_Cfg_PrimaryEntryType, DEM_NVM_DATA_NOINIT) Dem_Cfg_PrimaryEntry_6;
#define DEM_STOP_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_PrimaryEntry_7
**********************************************************************************************************************/
#define DEM_START_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(Dem_Cfg_PrimaryEntryType, DEM_NVM_DATA_NOINIT) Dem_Cfg_PrimaryEntry_7;
#define DEM_STOP_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_ReadoutBuffer
**********************************************************************************************************************/
#define DEM_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(Dem_Cfg_ReadoutBufferEntryType, DEM_VAR_NOINIT) Dem_Cfg_ReadoutBuffer[1];
#define DEM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_ReportedEventsOfFilter
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_ReportedEventsOfFilter
  \brief  size = DEM_CFG_NUMBER_OF_FILTER
*/ 
#define DEM_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(Dem_Cfg_ReportedEventsType, DEM_VAR_NOINIT) Dem_Cfg_ReportedEventsOfFilter[1];
#define DEM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_SatelliteInfo0
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_SatelliteInfo0
  \brief  Buffer for satellite data on OsApplication "0"
*/ 
#define DEM_START_SEC_0_VAR_ZERO_INIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(Dem_Cfg_SatelliteInfoType0, DEM_VAR_ZERO_INIT) Dem_Cfg_SatelliteInfo0;
#define DEM_STOP_SEC_0_VAR_ZERO_INIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_StatusData
**********************************************************************************************************************/
#define DEM_START_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(Dem_Cfg_StatusDataType, DEM_NVM_DATA_NOINIT) Dem_Cfg_StatusData;
#define DEM_STOP_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
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
  Justification of MISRA deviations
**********************************************************************************************************************/


#endif  /* DEM_LCFG_H */
/**********************************************************************************************************************
  END OF FILE: Dem_Lcfg.h     [Vag (Vector), VARIANT-PRE-COMPILE, 20.06.01.133983]
**********************************************************************************************************************/

