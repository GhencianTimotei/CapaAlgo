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
 *            Module: Fbl
 *           Program: FBL Vag SLP3 (FBL_Vag_SLP3)
 *          Customer: Huf H_lsbeck & F_rst GmbH & Co. KG
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: S32K144
 *    License Scope : The usage is restricted to CBD2100259_D00
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: Fbl_Cfg.h
 *   Generation Time: 2021-06-24 17:08:12
 *           Project: DemoAppl - Version 1
 *          Delivery: CBD2100259_D00
 *      Tool Version: DaVinci Configurator  5.23.30 SP1
 *
 *
 *********************************************************************************************************************/


#if !defined(__FBL_CFG_H__)
/* polyspace < MISRA-C3:21.1 : Not a defect : Justify with annotations> This macro is used to facilitate an easy adaptation */
#define __FBL_CFG_H__

/* Global Constant Macros ********************************************************************************************/
#ifndef FBL_USE_DUMMY_STATEMENT
#define FBL_USE_DUMMY_STATEMENT STD_ON /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef FBL_DUMMY_STATEMENT
/* polyspace < MISRA-C3:D4.9 : Not a defect : Justify with annotations > This macro is used to facilitate an easy adaptation */
#define FBL_DUMMY_STATEMENT(v) (v)=(v) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef FBL_DUMMY_STATEMENT_CONST
/* polyspace < MISRA-C3:D4.9 : Not a defect : Justify with annotations > This macro is used to facilitate an easy adaptation */
#define FBL_DUMMY_STATEMENT_CONST(v) (void)(v) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef FBL_ATOMIC_BIT_ACCESS_IN_BITFIELD
#define FBL_ATOMIC_BIT_ACCESS_IN_BITFIELD STD_OFF /* /MICROSAR/EcuC/EcucGeneral/AtomicBitAccessInBitfield */
#endif
#ifndef FBL_ATOMIC_VARIABLE_ACCESS
#define FBL_ATOMIC_VARIABLE_ACCESS 32u /* /MICROSAR/EcuC/EcucGeneral/AtomicVariableAccess */
#endif
#ifndef FBL_PROCESSOR_S32K144
#define FBL_PROCESSOR_S32K144
#endif
#ifndef FBL_COMP_IAR
#define FBL_COMP_IAR
#endif
#ifndef FBL_GEN_GENERATOR_MSR
#define FBL_GEN_GENERATOR_MSR
#endif
#ifndef FBL_CPUTYPE_BITORDER_LSB2MSB
#define FBL_CPUTYPE_BITORDER_LSB2MSB /* /MICROSAR/vSet/vSetPlatform/vSetBitOrder */
#endif
#ifndef FBL_CONFIGURATION_VARIANT_PRECOMPILE
#define FBL_CONFIGURATION_VARIANT_PRECOMPILE 1
#endif
#ifndef FBL_CONFIGURATION_VARIANT_LINKTIME
#define FBL_CONFIGURATION_VARIANT_LINKTIME 2
#endif
#ifndef FBL_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE
#define FBL_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE 3
#endif
#ifndef FBL_CONFIGURATION_VARIANT
#define FBL_CONFIGURATION_VARIANT FBL_CONFIGURATION_VARIANT_LINKTIME
#endif
#ifndef FBL_POSTBUILD_VARIANT_SUPPORT
#define FBL_POSTBUILD_VARIANT_SUPPORT STD_OFF
#endif

/* FblOem__base ******************************************************************************************************/
/* polyspace:begin < MISRA-C3:2.4,2.5 : Not a defect : Justify with annotations > Macro should be kept for future usage */
#define FBL_DISABLE_STAY_IN_BOOT 
#define FBL_USE_OWN_MEMCPY 
#define FBL_WATCHDOG_ON 
#define FBL_WATCHDOG_TIME                        	(1u / FBL_REPEAT_CALL_CYCLE) 
#ifndef TESSY
#define FBL_HEADER_ADDRESS                       	0x00004000uL
#else
const unsigned char TS_GetFblCommonDataPtr[4] = {0x12,0x34,0x56,0x78};
const unsigned long FBL_HEADER_ADDRESS_array[16] = {0,0,0,0,0,0,0,0,0,0,0,0,&TS_GetFblCommonDataPtr[0],0,0,0};
const unsigned long * const FBL_HEADER_ADDRESS = &FBL_HEADER_ADDRESS_array[0];
//#define GetFblCommonDataPtr()  (*((U32*)(FBL_HEADER_ADDRESS + FBL_HEADER_COMMON_DATA_OFFSET + FBL_HEADER_COMMON_DATA_FBL_VERSION_OFFSET)))
// (const void *)GetFblCommonDataPtr()
#endif
#define FBL_HEADER_COMMON_DATA_OFFSET            	(12u)
#define FBL_HEADER_COMMON_DATA_FBL_VERSION_OFFSET   (0u)
#define FBL_HEADER_COMMON_DATA_FBL_VERSION_SIZE  	(4u)
#define FBL_ENABLE_APPL_TIMER_TASK 
#define FBL_ENABLE_APPL_TASK 
#define FBL_DISABLE_APPL_STATE_TASK 
#define SWM_DATA_MAX_NOAR                        1u 
#define FBL_DIAG_BUFFER_LENGTH                   4095uL 
#define FBL_DIAG_TIME_P2MAX                      (50uL / FBL_REPEAT_CALL_CYCLE) 
#define FBL_DIAG_TIME_P3MAX                      (5000uL / FBL_REPEAT_CALL_CYCLE) 
#define FBL_DISABLE_SLEEPMODE 
#define FBL_SLEEP_TIME                           600000uL 
#define FBL_DISABLE_GAP_FILL 
#define kFillChar                                0xFFu 
#define FBL_DISABLE_GATEWAY_SUPPORT 
#define FBL_ENABLE_PRESENCE_PATTERN 
#define FBL_ENABLE_FBL_START 
#define FBL_DISABLE_COMMON_DATA 
#define FBL_ENABLE_RESPONSE_AFTER_RESET 
#define FBL_DISABLE_USERSUBFUNCTION 
#define FBL_DISABLE_USERSERVICE 
#define FBL_DISABLE_USERROUTINE 
#define FBL_DIAG_TIME_S3EXT                      (5000uL / FBL_REPEAT_CALL_CYCLE) 
#define FBL_DIAG_TIME_S3PRG                      (5000uL / FBL_REPEAT_CALL_CYCLE) 
#define FBL_DIAG_ENABLE_FLASHDRV_DOWNLOAD 
#define FBL_DIAG_DISABLE_FLASHDRV_ROM 
#define FBL_ENABLE_DATA_PROCESSING 
#define FBL_ENABLE_ENCRYPTION_MODE 
#define FBL_ENABLE_COMPRESSION_MODE 
#define FBL_INTEGRATION                          2uL 
#define FBL_PRODUCTION                           1uL 
#define FBL_PROJECT_STATE                        FBL_INTEGRATION 
#define FBL_ENABLE_SYSTEM_CHECK 
#define FBL_ENABLE_DEBUG_STATUS 
#define FBL_ENABLE_ASSERTION 
#define FBL_MEM_PROC_BUFFER_SIZE                 256uL 
#define FBL_MEM_DISABLE_VERIFY_INPUT 
#define FBL_MEM_DISABLE_VERIFY_PROCESSED 
#define FBL_MEM_ENABLE_VERIFY_PIPELINED 
#define FBL_MEM_DISABLE_VERIFY_OUTPUT 
#define FBL_MEM_VERIFY_SEGMENTATION              64uL 
#define FBL_DISABLE_ADAPTIVE_DATA_TRANSFER_RCRRP 
#define FBL_ENABLE_PIPELINED_PROGRAMMING 
#define FBL_DISABLE_SUSPEND_PROGRAMMING 
#define FBL_MEM_WRITE_SEGMENTATION               256uL 
#define FBL_ENABLE_UNALIGNED_DATA_TRANSFER 
#define FBL_BLOCK_START_ADDRESS                  0x00004000uL 
#define FBL_BLOCK_LENGTH                         114688uL 
#define FBL_DISABLE_OTA 
#define FBL_DISABLE_ONE_STEP_UPDATER 
/* polyspace+2 MISRA-C3:20.1 [Justified:Low] "preceded by comment" */
/* FblHal ************************************************************************************************************/
#include "FblHal_Cfg.h"
/* FblOem_Vag ********************************************************************************************************/
#define kBlockTypeWithoutFlashDrvCount         0x00000001uL 
#define FBL_DIAG_80126_VERSION                 0x0207u 
#define FBL_DIAG_ENABLE_VERIFY_CHECKSUM 
#define FBL_DIAG_DISABLE_COPY_VERSION_BYTES 
#define FBL_DIAG_DISABLE_MULTIPLE_SEGMENTS 
#define TESTER_PRESENT_TIMEOUT                 5000u 
#define FBL_ENABLE_SEC_ACCESS_DELAY 
#define FBL_SEC_ACCESS_DELAY_TIME              600000uL 
#define FBL_USERCFG_USE_SECMOD_FDS 
#define FBL_DISABLE_CERTIFICATE 
#define FBL_ENABLE_CERTIFICATE_IN_INTERNAL_ROM 
#define FBL_DIAG_DISABLE_DOWNGRADEPROTECTION 
#define FBL_APPL_ENABLE_DECOMPRESSION_ECL 
#define FBL_DIAG_DISABLE_CLEAR_RFS_DATA 
/* polyspace:end < MISRA-C3:2.4,2.5 : Not a defect : Justify with annotations > Macro should be kept for future usage */

/* User Config File **************************************************************************************************/
/* User Config File Start */
/******************************************************************************
 * FBL Configuration Area (user_config.cfg)
 *****************************************************************************/
/* polyspace+2 MISRA-C3:11.4 [Justified:Low] "A cast should not be performed" */
/* polyspace+1 MISRA-C3:D4.9 [Justified:Low] "Macro used to facilitate easier configuration." */
#define GetFblCommonDataPtr()  (*((U32*)(FBL_HEADER_ADDRESS + FBL_HEADER_COMMON_DATA_OFFSET + FBL_HEADER_COMMON_DATA_FBL_VERSION_OFFSET)))


/* Enable development board features */
/* #define FBL_ENABLE_VECTOR_HW */

/* User Section ************************************************************** */
/*************************************************/
/* DO NOT CHANGE ANYTHING BELOW THIS LINE        */
/*************************************************/
/* polyspace:begin < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
#define FBL_DIAG_ENABLE_SIG_ADDRESS_LOGICAL
#define kFblTpBlocksize                      15u
/* polyspace:end < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
/* *************************************************************************** */
/* User Config File End */


/* User Section ******************************************************************************************************/

#endif /* __FBL_CFG_H__ */

