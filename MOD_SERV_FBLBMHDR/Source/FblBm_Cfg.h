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
 *            Module: FblBm
 *           Program: FBL Vag SLP3 (FBL_Vag_SLP3)
 *          Customer: Huf H_lsbeck & F_rst GmbH & Co. KG
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: S32K144
 *    License Scope : The usage is restricted to CBD2100259_D00
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: FblBm_Cfg.h
 *   Generation Time: 2021-06-10 16:15:52
 *           Project: DemoAppl - Version 1
 *          Delivery: CBD2100259_D00
 *      Tool Version: DaVinci Configurator  5.23.30 SP1
 *
 *
 *********************************************************************************************************************/

#if !defined (FBLBM_CFG_H) /* PRQA S 0883 */ /* MD_FblBm_0883 */
# define FBLBM_CFG_H


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* polyspace:begin < MISRA-C3:2.5 : Not a defect : Justify with annotations > Macro should be kept for future usage */
/* Configuration major version identification */ 
# define FBLBM_CFG_MAJOR_VERSION 2u 
/* Configuration minor version identification */ 
# define FBLBM_CFG_MINOR_VERSION 2u 
/* Defines how a corrupted bootloader is handled */ 
# define FBLBM_DISABLE_UPDATER_FAILSAFE 
/* Defines how missing keys are handled */ 
# define FBLBM_DISABLE_SECBOOT_FBL_INIT_KEY 
/* Defines how a missing bootloader mac is handled */ 
# define FBLBM_DISABLE_SECBOOT_FBL_INIT_MAC 
/* Defines whether secure boot is enabled or disabled */ 
# define FBLBM_DISABLE_SECURE_BOOT 
/* Defines whether stand-alone mode is enabled or disabled */ 
# define FBLBM_DISABLE_STANDALONE_MODE 
/* Defines the start address of the header */ 
# define FBLBM_HEADER_ADDRESS 0x0001F8C0uL 
/* Defines size of the boottarget list */ 
# define FBLBM_BOOTTARGETLIST_SIZE 0u 
/* Defines build context */ 
# define FBLBM_INSTANCE_APPLICATION 
/* Defines configuration files to be included */ 
# define FBLBM_DISABLE_GENERIC_CONFIGURATION 
# define FBLBM_DISABLE_HARDWARE_CONFIGURATION 
# define FBLBM_DISABLE_OEM_CONFIGURATION 
/* If enabled it is possible to verify the header structure separately */ 
# define FBLBM_DISABLE_HEADER_VERIFICATION 
/* If enabled it is possible to verify the LBT of the FBL separately */ 
# define FBLBM_DISABLE_FBLLBT_VERIFICATION 

/* General define block */
# ifndef FBLBM_USE_DUMMY_STATEMENT
#  define FBLBM_USE_DUMMY_STATEMENT STD_ON /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
# endif
# ifndef FBLBM_DUMMY_STATEMENT
/* polyspace < MISRA-C3:D4.9 : Not a defect : Justify with annotations > This macro is used to facilitate an easy adaptation */
#  define FBLBM_DUMMY_STATEMENT(v) (v)=(v) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
# endif
# ifndef FBLBM_DUMMY_STATEMENT_CONST
/* polyspace < MISRA-C3:D4.9 : Not a defect : Justify with annotations > This macro is used to facilitate an easy adaptation */
#  define FBLBM_DUMMY_STATEMENT_CONST(v) (void)(v) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
# endif
# ifndef FBLBM_ATOMIC_BIT_ACCESS_IN_BITFIELD
#  define FBLBM_ATOMIC_BIT_ACCESS_IN_BITFIELD STD_OFF /* /MICROSAR/EcuC/EcucGeneral/AtomicBitAccessInBitfield */
# endif
# ifndef FBLBM_ATOMIC_VARIABLE_ACCESS
#  define FBLBM_ATOMIC_VARIABLE_ACCESS 32u /* /MICROSAR/EcuC/EcucGeneral/AtomicVariableAccess */
# endif
# ifndef FBLBM_PROCESSOR_S32K144
#  define FBLBM_PROCESSOR_S32K144
# endif
# ifndef FBLBM_COMP_IAR
#  define FBLBM_COMP_IAR
# endif
# ifndef FBLBM_GEN_GENERATOR_MSR
#  define FBLBM_GEN_GENERATOR_MSR
# endif
# ifndef FBLBM_CPUTYPE_BITORDER_LSB2MSB
#  define FBLBM_CPUTYPE_BITORDER_LSB2MSB /* /MICROSAR/vSet/vSetPlatform/vSetBitOrder */
# endif
# ifndef FBLBM_CONFIGURATION_VARIANT_PRECOMPILE
#  define FBLBM_CONFIGURATION_VARIANT_PRECOMPILE 1
# endif
# ifndef FBLBM_CONFIGURATION_VARIANT_LINKTIME
#  define FBLBM_CONFIGURATION_VARIANT_LINKTIME 2
# endif
# ifndef FBLBM_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE
#  define FBLBM_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE 3
# endif
# ifndef FBLBM_CONFIGURATION_VARIANT
#  define FBLBM_CONFIGURATION_VARIANT FBLBM_CONFIGURATION_VARIANT_PRECOMPILE
# endif
# ifndef FBLBM_POSTBUILD_VARIANT_SUPPORT
#  define FBLBM_POSTBUILD_VARIANT_SUPPORT STD_OFF
# endif

/* polyspace:end < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
/**********************************************************************************************************************
 *  USER CONFIG FILE
 *********************************************************************************************************************/



#endif /* FBLBM_CFG_H */

/**********************************************************************************************************************
 *  END OF FILE: FblBm_Cfg.h
 *********************************************************************************************************************/
