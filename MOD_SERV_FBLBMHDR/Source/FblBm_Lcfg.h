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
 *              File: FblBm_Lcfg.h
 *   Generation Time: 2021-06-10 15:28:01
 *           Project: DemoAppl - Version 1
 *          Delivery: CBD2100259_D00
 *      Tool Version: DaVinci Configurator  5.23.30 SP1
 *
 *
 *********************************************************************************************************************/

#if !defined (FBLBM_LCFG_H) /* PRQA S 0883 */ /* MD_FblBm_0883 */
# define FBLBM_LCFG_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

# include "fbl_def.h"
# include "bm_hdr_types.h"
# include "FblBm_Cfg.h"

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

typedef enum
{
   FBLBM_TARGET_TYPE_MANDATORY = 0u,
   FBLBM_TARGET_TYPE_OPTIONAL
} tFblBmTargetType;

/* polyspace:begin <MISRA-C3:D4.8 : Not a defect: Justify with annotations > No impact on functionality, just code encapsulation related.*/
typedef struct
{
   tFblBmHdrTargetHandle target;
   tFblBmTargetType      type;
}tFblBmHdrTargetDependency;
/* polyspace:end <MISRA-C3:D4.8 : Not a defect: Justify with annotations > No impact on functionality, just code encapsulation related.*/

/* polyspace:begin < MISRA-C3:2.3 : Not a defect : Justify with annotations > Struct should be kept for future usage */
typedef struct
{
   tFblBmHdrTargetHandle       target;
   V_MEMROM1 tFblBmHdrTargetDependency V_MEMROM2 V_MEMROM3 * dependencies;
   vuintx                      dependenciesSize;
}tFblBmHdrTargetListEntry;
/* polyspace:end < MISRA-C3:2.3 : Not a defect : Justify with annotations > Should be kept for future usage */

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
 

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#endif /* FBLBM_LCFG_H */

/**********************************************************************************************************************
 *  END OF FILE: FblBm_Lcfg.h
 *********************************************************************************************************************/
