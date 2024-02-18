/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *             File:  SchM_Wdg.h
 *           Config:  D:/Projects/eTAB/SW/BSW/AudiPack_code/3_Coding/Main_MCU/AUTOSAR_BSW/CfgPrj/DaVinciConfigurationS32K144.dpa
 *      ECU-Project:  DaVinciConfigurationS32K144
 *  Generation Time:  2021-05-12 12:37:10
 *
 *        Generator:  MICROSAR RTE Generator Version 4.24.0
 *                    RTE Core Version 1.24.0
 *          License:  CBD2100188
 *
 *      Description:  Header of BSW Scheduler for BSW Module <Wdg>
 *********************************************************************************************************************/
#ifndef SCHM_WDG_H
# define SCHM_WDG_H

# ifdef __cplusplus
extern "C" {
# endif  /* __cplusplus */

# include "SchM_Wdg_Type.h"

# include "Os.h" /* PRQA S 0828, 0883 */ /* MD_MSR_Dir1.1, MD_Rte_Os */

# define SchM_Enter_Wdg_WDG_EXCLUSIVE_AREA_00() SuspendAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Exit_Wdg_WDG_EXCLUSIVE_AREA_00() ResumeAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Enter_Wdg_WDG_EXCLUSIVE_AREA_01() SuspendAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Exit_Wdg_WDG_EXCLUSIVE_AREA_01() ResumeAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Enter_Wdg_WDG_EXCLUSIVE_AREA_02() SuspendAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Exit_Wdg_WDG_EXCLUSIVE_AREA_02() ResumeAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Enter_Wdg_WDG_EXCLUSIVE_AREA_03() SuspendAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Exit_Wdg_WDG_EXCLUSIVE_AREA_03() ResumeAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Enter_Wdg_WDG_EXCLUSIVE_AREA_04() SuspendAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Exit_Wdg_WDG_EXCLUSIVE_AREA_04() ResumeAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Enter_Wdg_WDG_EXCLUSIVE_AREA_05() SuspendAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Exit_Wdg_WDG_EXCLUSIVE_AREA_05() ResumeAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Enter_Wdg_WDG_EXCLUSIVE_AREA_06() SuspendAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Exit_Wdg_WDG_EXCLUSIVE_AREA_06() ResumeAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Enter_Wdg_WDG_EXCLUSIVE_AREA_07() SuspendAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Exit_Wdg_WDG_EXCLUSIVE_AREA_07() ResumeAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Enter_Wdg_WDG_EXCLUSIVE_AREA_08() SuspendAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Exit_Wdg_WDG_EXCLUSIVE_AREA_08() ResumeAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Enter_Wdg_WDG_EXCLUSIVE_AREA_09() SuspendAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Exit_Wdg_WDG_EXCLUSIVE_AREA_09() ResumeAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Enter_Wdg_WDG_EXCLUSIVE_AREA_10() SuspendAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Exit_Wdg_WDG_EXCLUSIVE_AREA_10() ResumeAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Enter_Wdg_WDG_EXCLUSIVE_AREA_11() SuspendAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Exit_Wdg_WDG_EXCLUSIVE_AREA_11() ResumeAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Enter_Wdg_WDG_EXCLUSIVE_AREA_12() SuspendAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Exit_Wdg_WDG_EXCLUSIVE_AREA_12() ResumeAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Enter_Wdg_WDG_EXCLUSIVE_AREA_13() SuspendAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Exit_Wdg_WDG_EXCLUSIVE_AREA_13() ResumeAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Enter_Wdg_WDG_EXCLUSIVE_AREA_14() SuspendAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Exit_Wdg_WDG_EXCLUSIVE_AREA_14() ResumeAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Enter_Wdg_WDG_EXCLUSIVE_AREA_15() SuspendAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Exit_Wdg_WDG_EXCLUSIVE_AREA_15() ResumeAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Enter_Wdg_WDG_EXCLUSIVE_AREA_16() SuspendAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Exit_Wdg_WDG_EXCLUSIVE_AREA_16() ResumeAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Enter_Wdg_WDG_EXCLUSIVE_AREA_17() SuspendAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Exit_Wdg_WDG_EXCLUSIVE_AREA_17() ResumeAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Enter_Wdg_WDG_EXCLUSIVE_AREA_18() SuspendAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Exit_Wdg_WDG_EXCLUSIVE_AREA_18() ResumeAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Enter_Wdg_WDG_EXCLUSIVE_AREA_19() SuspendAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Exit_Wdg_WDG_EXCLUSIVE_AREA_19() ResumeAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Enter_Wdg_WDG_EXCLUSIVE_AREA_20() SuspendAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Exit_Wdg_WDG_EXCLUSIVE_AREA_20() ResumeAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Enter_Wdg_WDG_EXCLUSIVE_AREA_21() SuspendAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Exit_Wdg_WDG_EXCLUSIVE_AREA_21() ResumeAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Enter_Wdg_WDG_EXCLUSIVE_AREA_22() SuspendAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Exit_Wdg_WDG_EXCLUSIVE_AREA_22() ResumeAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Enter_Wdg_WDG_EXCLUSIVE_AREA_23() SuspendAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Exit_Wdg_WDG_EXCLUSIVE_AREA_23() ResumeAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Enter_Wdg_WDG_EXCLUSIVE_AREA_24() SuspendAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Exit_Wdg_WDG_EXCLUSIVE_AREA_24() ResumeAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Enter_Wdg_WDG_EXCLUSIVE_AREA_25() SuspendAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Exit_Wdg_WDG_EXCLUSIVE_AREA_25() ResumeAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Enter_Wdg_WDG_EXCLUSIVE_AREA_26() SuspendAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Exit_Wdg_WDG_EXCLUSIVE_AREA_26() ResumeAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Enter_Wdg_WDG_EXCLUSIVE_AREA_27() SuspendAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Exit_Wdg_WDG_EXCLUSIVE_AREA_27() ResumeAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Enter_Wdg_WDG_EXCLUSIVE_AREA_28() SuspendAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Exit_Wdg_WDG_EXCLUSIVE_AREA_28() ResumeAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Enter_Wdg_WDG_EXCLUSIVE_AREA_29() SuspendAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Exit_Wdg_WDG_EXCLUSIVE_AREA_29() ResumeAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Enter_Wdg_WDG_EXCLUSIVE_AREA_30() SuspendAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Exit_Wdg_WDG_EXCLUSIVE_AREA_30() ResumeAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */


# ifdef __cplusplus
} /* extern "C" */
# endif  /* __cplusplus */

#endif /* SCHM_WDG_H */

/**********************************************************************************************************************
 MISRA 2012 violations and justifications
 *********************************************************************************************************************/

/* module specific MISRA deviations:
   MD_Rte_Os:
     Reason:     This justification is used as summary justification for all deviations caused by the MICROSAR OS
                 which is for testing of the RTE. Those deviations are no issues in the RTE code.
     Risk:       No functional risk.
     Prevention: Not required.

*/
