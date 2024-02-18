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
 *              File: FblBmHdr_Lcfg.c
 *   Generation Time: 2021-06-10 15:28:01
 *           Project: DemoAppl - Version 1
 *          Delivery: CBD2100259_D00
 *      Tool Version: DaVinci Configurator  5.23.30 SP1
 *
 *
 *********************************************************************************************************************/
/* polyspace < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
#define FBLBMHDR_LCFG_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "Std_Types.h"
#include "FblBmHdr_Cfg.h"



/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/* Entry address symbol declaration */
/* polyspace < MISRA-C3:8.5 : Not a defect : Justify with annotations > Function is declared once here */
extern uint8 Reset_Handler(void);

#define FBLBMHDR_BMHEADER_START_SEC_CONST
/* polyspace < MISRA-C3:20.1 : Not a defect : Justify with annotations> does not affect the functionality */
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

CONST(tFblBmHdrHeader, FBLBMHDR_CONST) FblBmHdrHeader =
{
  FBLBMHDR_MAGIC_FLAG, 
  /* polyspace < MISRA-C3:11.1 : Not a defect : Justify with annotations > Function address is needed */
  (tFblAddress) &Reset_Handler, 
  FBLBMHDR_TARGET_APPL, 
  0x00030000uL, 
  0x00040000uL, 
  (tFblAddress) 0x00030000uL
};

#define FBLBMHDR_BMHEADER_STOP_SEC_CONST
/* polyspace < MISRA-C3:20.1 : Not a defect : Justify with annotations> does not affect the functionality */
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#define FBLBMHDR_START_SEC_CONST
/* polyspace < MISRA-C3:20.1 : Not a defect : Justify with annotations> does not affect the functionality */
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

CONST(uint32, FBLBMHDR_CONST) FblBmHdrTargets[FBLBMHDR_NUM_OF_TARGETS] =
{
  255uL /*  Fbl -> empty  */ , 
  255uL /*  FblUpdater -> empty  */ , 
  255uL /*  Appl -> empty  */ , 
  255uL /*  Data -> empty  */ 
};

#define FBLBMHDR_STOP_SEC_CONST
/* polyspace < MISRA-C3:20.1 : Not a defect : Justify with annotations> does not affect the functionality */
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define FBLBMHDR_START_SEC_CODE
/* polyspace < MISRA-C3:20.1 : Not a defect : Justify with annotations> does not affect the functionality */
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

#define FBLBMHDR_STOP_SEC_CODE
/* polyspace < MISRA-C3:20.1 : Not a defect : Justify with annotations> does not affect the functionality */
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  END OF FILE: FblBmHdr_Lcfg.c
 *********************************************************************************************************************/
