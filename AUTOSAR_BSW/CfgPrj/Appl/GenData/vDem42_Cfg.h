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
 *            Module: vDem42
 *           Program: VAG AR4 (MSR_Vag_SLP5)
 *          Customer: Huf H_lsbeck & F_rst GmbH & Co. KG
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: S32K144
 *    License Scope : The usage is restricted to CBD2100188_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: vDem42_Cfg.h
 *   Generation Time: 2021-05-28 14:20:33
 *           Project: DaVinciConfigurationS32K144 - Version 1.0
 *          Delivery: CBD2100188_D01
 *      Tool Version: DaVinci Configurator  5.23.25
 *
 *
 *********************************************************************************************************************/


#if !defined (VDEM42_CFG_H)
# define VDEM42_CFG_H

/**********************************************************************************************************************
* INCLUDES
*********************************************************************************************************************/
#include "vDem42_Types.h"
/**********************************************************************************************************************
*  GLOBAL CONSTANT MACROS
*********************************************************************************************************************/ 
/* --- Component Version Information ------------------------------------------------------------------------------- */
/* AUTOSAR Version (from xsi:schemaLocation) */
#define VDEM42_CFG_AR_RELEASE_MAJOR_VERSION                              4u
#define VDEM42_CFG_AR_RELEASE_MINOR_VERSION                              0u
#define VDEM42_CFG_AR_RELEASE_REVISION_VERSION                           3u

/* AUTOSAR Software Specification Version Information of BSW-IMPLEMENTATION */
#define VDEM42_CFG_AR_MAJOR_VERSION                                      4u
#define VDEM42_CFG_AR_MINOR_VERSION                                      2u
#define VDEM42_CFG_AR_PATCH_VERSION                                      2u

/* SW version number of BSW-IMPLEMENTATION */
#define VDEM42_CFG_SW_MAJOR_VERSION                                      1u
#define VDEM42_CFG_SW_MINOR_VERSION                                      2u
#define VDEM42_CFG_SW_PATCH_VERSION                                      0u

/* Generator Version Information */
#define VDEM42_CFG_GEN_MAJOR_VERSION                                     1
#define VDEM42_CFG_GEN_MINOR_VERSION                                     2
#define VDEM42_CFG_GEN_PATCH_VERSION                                     0
 
 /* --- Global Configuration Values --------------------------------------------------------------------------------- */
#ifndef VDEM42_USE_DUMMY_STATEMENT
#define VDEM42_USE_DUMMY_STATEMENT STD_ON /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef VDEM42_DUMMY_STATEMENT
#define VDEM42_DUMMY_STATEMENT(v) (v)=(v) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef VDEM42_DUMMY_STATEMENT_CONST
#define VDEM42_DUMMY_STATEMENT_CONST(v) (void)(v) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef VDEM42_ATOMIC_BIT_ACCESS_IN_BITFIELD
#define VDEM42_ATOMIC_BIT_ACCESS_IN_BITFIELD STD_OFF /* /MICROSAR/EcuC/EcucGeneral/AtomicBitAccessInBitfield */
#endif
#ifndef VDEM42_ATOMIC_VARIABLE_ACCESS
#define VDEM42_ATOMIC_VARIABLE_ACCESS 32u /* /MICROSAR/EcuC/EcucGeneral/AtomicVariableAccess */
#endif
#ifndef VDEM42_PROCESSOR_S32K144
#define VDEM42_PROCESSOR_S32K144
#endif
#ifndef VDEM42_COMP_IAR
#define VDEM42_COMP_IAR
#endif
#ifndef VDEM42_GEN_GENERATOR_MSR
#define VDEM42_GEN_GENERATOR_MSR
#endif
#ifndef VDEM42_CPUTYPE_BITORDER_LSB2MSB
#define VDEM42_CPUTYPE_BITORDER_LSB2MSB /* /MICROSAR/vSet/vSetPlatform/vSetBitOrder */
#endif
#ifndef VDEM42_CONFIGURATION_VARIANT_PRECOMPILE
#define VDEM42_CONFIGURATION_VARIANT_PRECOMPILE 1
#endif
#ifndef VDEM42_CONFIGURATION_VARIANT_LINKTIME
#define VDEM42_CONFIGURATION_VARIANT_LINKTIME 2
#endif
#ifndef VDEM42_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE
#define VDEM42_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE 3
#endif
#ifndef VDEM42_CONFIGURATION_VARIANT
#define VDEM42_CONFIGURATION_VARIANT VDEM42_CONFIGURATION_VARIANT_PRECOMPILE
#endif
#ifndef VDEM42_POSTBUILD_VARIANT_SUPPORT
#define VDEM42_POSTBUILD_VARIANT_SUPPORT STD_OFF
#endif

#ifndef VDEM42_DEV_ERROR_DETECT
#define VDEM42_DEV_ERROR_DETECT STD_OFF
#endif
#ifndef VDEM42_DEV_ERROR_REPORT
#define VDEM42_DEV_ERROR_REPORT STD_OFF
#endif

#define VDEM42_GLOBAL_EVENT_ENABLED       STD_OFF 
#define VDEM42_CFG_SUPPORT_DTCSUPPRESSION STD_OFF 


/**********************************************************************************************************************
*  GLOBAL FUNCTION MACROS
*********************************************************************************************************************/

/**********************************************************************************************************************
*  GLOBAL DATA TYPES AND STRUCTURES
*********************************************************************************************************************/

/**********************************************************************************************************************
*  GLOBAL DATA PROTOTYPES
*********************************************************************************************************************/

/**********************************************************************************************************************
*  GLOBAL FUNCTION PROTOTYPES
*********************************************************************************************************************/


 #endif  /* VDEM42_CFG_H */
/**********************************************************************************************************************
  END OF FILE: vDem42_Cfg.h
**********************************************************************************************************************/
