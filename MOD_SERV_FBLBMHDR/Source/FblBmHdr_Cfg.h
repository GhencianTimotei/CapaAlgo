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
 *            Module: FblBmHdr
 *           Program: FBL Vag SLP3 (FBL_Vag_SLP3)
 *          Customer: Huf H_lsbeck & F_rst GmbH & Co. KG
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: S32K144
 *    License Scope : The usage is restricted to CBD2100259_D00
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: FblBmHdr_Cfg.h
 *   Generation Time: 2021-06-10 15:28:01
 *           Project: DemoAppl - Version 1
 *          Delivery: CBD2100259_D00
 *      Tool Version: DaVinci Configurator  5.23.30 SP1
 *
 *
 *********************************************************************************************************************/

#if !defined (FBLBMHDR_CFG_H) /* PRQA S 0883 */ /* MD_FblBmHdr_0883 */
# define FBLBMHDR_CFG_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

# include "Std_Types.h"
# include "fbl_def.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* polyspace:begin < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
/* Configuration major version identification */ 
# define FBLBMHDR_CFG_MAJOR_VERSION 2u 
/* Configuration minor version identification */ 
# define FBLBMHDR_CFG_MINOR_VERSION 1u 
/* Defines the configuration magic flag */ 
# define FBLBMHDR_MAGIC_FLAG 0xECE9654AuL 
/* Defines the number of verification entries */ 
# define FBLBMHDR_NUM_OF_VERIFICATION_ENTRIES 1uL 
/* Defines the number of targets */ 
# define FBLBMHDR_NUM_OF_TARGETS 4uL 
/* Defines invalid entry address */ 
# define FBLBMHDR_ENTRY_ADDRESS_INVALID 0xFFFFFFFFuL 
/* Defines if a verification list in the FblBmHdrHeader structure is required */ 
# define FBLBMHDR_DISABLE_HEADER_VERIFICATION_LIST 
/* polyspace:end < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
/* General define block */
# ifndef FBLBMHDR_USE_DUMMY_STATEMENT
#  define FBLBMHDR_USE_DUMMY_STATEMENT STD_ON /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
# endif
# ifndef FBLBMHDR_DUMMY_STATEMENT
/* polyspace < MISRA-C3:D4.9 : Not a defect : Justify with annotations > This macro is used to facilitate an easy adaptation */
#  define FBLBMHDR_DUMMY_STATEMENT(v) (v)=(v) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
# endif
# ifndef FBLBMHDR_DUMMY_STATEMENT_CONST
/* polyspace < MISRA-C3:D4.9 : Not a defect : Justify with annotations > This macro is used to facilitate an easy adaptation */
#  define FBLBMHDR_DUMMY_STATEMENT_CONST(v) (void)(v) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
# endif
# ifndef FBLBMHDR_ATOMIC_BIT_ACCESS_IN_BITFIELD
#  define FBLBMHDR_ATOMIC_BIT_ACCESS_IN_BITFIELD STD_OFF /* /MICROSAR/EcuC/EcucGeneral/AtomicBitAccessInBitfield */
# endif
# ifndef FBLBMHDR_ATOMIC_VARIABLE_ACCESS
#  define FBLBMHDR_ATOMIC_VARIABLE_ACCESS 32u /* /MICROSAR/EcuC/EcucGeneral/AtomicVariableAccess */
# endif
# ifndef FBLBMHDR_PROCESSOR_S32K144
#  define FBLBMHDR_PROCESSOR_S32K144
# endif
# ifndef FBLBMHDR_COMP_IAR
#  define FBLBMHDR_COMP_IAR
# endif
# ifndef FBLBMHDR_GEN_GENERATOR_MSR
#  define FBLBMHDR_GEN_GENERATOR_MSR
# endif
# ifndef FBLBMHDR_CPUTYPE_BITORDER_LSB2MSB
#  define FBLBMHDR_CPUTYPE_BITORDER_LSB2MSB /* /MICROSAR/vSet/vSetPlatform/vSetBitOrder */
# endif
# ifndef FBLBMHDR_CONFIGURATION_VARIANT_PRECOMPILE
#  define FBLBMHDR_CONFIGURATION_VARIANT_PRECOMPILE 1
# endif
# ifndef FBLBMHDR_CONFIGURATION_VARIANT_LINKTIME
#  define FBLBMHDR_CONFIGURATION_VARIANT_LINKTIME 2
# endif
# ifndef FBLBMHDR_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE
#  define FBLBMHDR_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE 3
# endif
# ifndef FBLBMHDR_CONFIGURATION_VARIANT
#  define FBLBMHDR_CONFIGURATION_VARIANT FBLBMHDR_CONFIGURATION_VARIANT_PRECOMPILE
# endif
# ifndef FBLBMHDR_POSTBUILD_VARIANT_SUPPORT
#  define FBLBMHDR_POSTBUILD_VARIANT_SUPPORT STD_OFF
# endif


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/* Get MAC job ids */
/* polyspace < MISRA-C3:D4.9 : Not a defect : Justify with annotations > This macro is used to facilitate an easy adaptation */
/* polyspace < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
# define FblBmHdr_GetFblSbMacId(targetId)        FblBmHdrTargets[targetId]

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/* All predefined targets */
typedef enum
{
  FBLBMHDR_TARGET_FBL = 0, 
  FBLBMHDR_TARGET_FBLUPDATER = 1, 
  FBLBMHDR_TARGET_APPL = 2, 
  FBLBMHDR_TARGET_DATA = 3
} tFblBmHdrTargetHandle;

/* Structure of the verification list */
/* polyspace:begin < MISRA-C3:2.3 : Not a defect : Justify with annotations > struct should be kept for future usage */
typedef struct
{
   vuint32 address;
   vuint32 length;
} tFblBmHdrVerificationList;
/* polyspace:end < MISRA-C3:2.3 : Not a defect : Justify with annotations > Should be kept for future usage */
/* Structure of the BootManager header */
typedef struct
{
   vuint32                    bmMagicFlag;
   tFblAddress                bmEntryAddress;
   tFblBmHdrTargetHandle      bmTargetHandle;
   tFblAddress                bmBlockStartAddress;
   tFblLength                 bmBlockLength;
   tFblAddress                bmAuthenticationHeaderAddress;
} tFblBmHdrHeader;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

#define FBLBMHDR_BMHEADER_START_SEC_CONST
/* polyspace < MISRA-C3:20.1 : Not a defect : Justify with annotations> does not affect the functionality */
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

extern CONST(tFblBmHdrHeader, FBLBMHDR_CONST) FblBmHdrHeader;

#define FBLBMHDR_BMHEADER_STOP_SEC_CONST
/* polyspace < MISRA-C3:20.1 : Not a defect : Justify with annotations> does not affect the functionality */
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# define FBLBMHDR_START_SEC_CONST
/* polyspace < MISRA-C3:20.1 : Not a defect : Justify with annotations> does not affect the functionality */
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

extern CONST(uint32, FBLBMHDR_CONST) FblBmHdrTargets[FBLBMHDR_NUM_OF_TARGETS];

# define FBLBMHDR_STOP_SEC_CONST
/* polyspace < MISRA-C3:20.1 : Not a defect : Justify with annotations> does not affect the functionality */
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define FBLBMHDR_START_SEC_CODE
/* polyspace < MISRA-C3:20.1 : Not a defect : Justify with annotations> does not affect the functionality */
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define FBLBMHDR_STOP_SEC_CODE
/* polyspace < MISRA-C3:20.1 : Not a defect : Justify with annotations> does not affect the functionality */
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  USER CONFIG FILE
 *********************************************************************************************************************/



#endif /* FBLBMHDR_CFG_H */

/**********************************************************************************************************************
 *  END OF FILE: FblBmHdr_Cfg.h
 *********************************************************************************************************************/
