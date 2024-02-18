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
 *             File:  SchM_Mcu.h
 *           Config:  DaVinciConfigurationS32K144.dpa
 *      ECU-Project:  DaVinciConfigurationS32K144
 *
 *        Generator:  MICROSAR RTE Generator Version 4.24.0
 *                    RTE Core Version 1.24.0
 *          License:  CBD2100188
 *
 *      Description:  Header of BSW Scheduler for BSW Module <Mcu>
 *********************************************************************************************************************/
#ifndef SCHM_MCU_H
# define SCHM_MCU_H

# ifdef __cplusplus
extern "C" {
# endif  /* __cplusplus */

# include "SchM_Mcu_Type.h"

# define RTE_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

FUNC(void, RTE_CODE) SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_00(void);
FUNC(void, RTE_CODE) SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_00(void);
FUNC(void, RTE_CODE) SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_01(void);
FUNC(void, RTE_CODE) SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_01(void);
FUNC(void, RTE_CODE) SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_02(void);
FUNC(void, RTE_CODE) SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_02(void);
FUNC(void, RTE_CODE) SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_03(void);
FUNC(void, RTE_CODE) SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_03(void);
FUNC(void, RTE_CODE) SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_04(void);
FUNC(void, RTE_CODE) SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_04(void);
FUNC(void, RTE_CODE) SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_05(void);
FUNC(void, RTE_CODE) SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_05(void);
FUNC(void, RTE_CODE) SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_06(void);
FUNC(void, RTE_CODE) SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_06(void);
FUNC(void, RTE_CODE) SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_07(void);
FUNC(void, RTE_CODE) SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_07(void);
FUNC(void, RTE_CODE) SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_08(void);
FUNC(void, RTE_CODE) SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_08(void);
FUNC(void, RTE_CODE) SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_09(void);
FUNC(void, RTE_CODE) SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_09(void);
FUNC(void, RTE_CODE) SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_10(void);
FUNC(void, RTE_CODE) SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_10(void);
FUNC(void, RTE_CODE) SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_11(void);
FUNC(void, RTE_CODE) SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_11(void);
FUNC(void, RTE_CODE) SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_12(void);
FUNC(void, RTE_CODE) SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_12(void);
FUNC(void, RTE_CODE) SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_13(void);
FUNC(void, RTE_CODE) SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_13(void);
FUNC(void, RTE_CODE) SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_14(void);
FUNC(void, RTE_CODE) SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_14(void);
FUNC(void, RTE_CODE) SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_15(void);
FUNC(void, RTE_CODE) SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_15(void);
FUNC(void, RTE_CODE) SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_16(void);
FUNC(void, RTE_CODE) SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_16(void);
FUNC(void, RTE_CODE) SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_17(void);
FUNC(void, RTE_CODE) SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_17(void);
FUNC(void, RTE_CODE) SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_18(void);
FUNC(void, RTE_CODE) SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_18(void);
FUNC(void, RTE_CODE) SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_19(void);
FUNC(void, RTE_CODE) SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_19(void);
FUNC(void, RTE_CODE) SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_20(void);
FUNC(void, RTE_CODE) SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_20(void);
FUNC(void, RTE_CODE) SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_21(void);
FUNC(void, RTE_CODE) SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_21(void);
FUNC(void, RTE_CODE) SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_22(void);
FUNC(void, RTE_CODE) SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_22(void);
FUNC(void, RTE_CODE) SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_23(void);
FUNC(void, RTE_CODE) SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_23(void);
FUNC(void, RTE_CODE) SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_24(void);
FUNC(void, RTE_CODE) SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_24(void);
FUNC(void, RTE_CODE) SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_25(void);
FUNC(void, RTE_CODE) SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_25(void);
FUNC(void, RTE_CODE) SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_26(void);
FUNC(void, RTE_CODE) SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_26(void);
FUNC(void, RTE_CODE) SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_27(void);
FUNC(void, RTE_CODE) SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_27(void);
FUNC(void, RTE_CODE) SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_28(void);
FUNC(void, RTE_CODE) SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_28(void);
FUNC(void, RTE_CODE) SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_29(void);
FUNC(void, RTE_CODE) SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_29(void);
FUNC(void, RTE_CODE) SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_30(void);
FUNC(void, RTE_CODE) SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_30(void);

# define RTE_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

# ifdef __cplusplus
} /* extern "C" */
# endif  /* __cplusplus */

#endif /* SCHM_MCU_H */
