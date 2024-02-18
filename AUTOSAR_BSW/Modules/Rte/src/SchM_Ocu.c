/**
*   @file    SchM_Ocu.c
*   @version 1.0.1
*
*   @brief   AUTOSAR Rte - module implementation
*   @details his module implements stubs for the AUTOSAR Rte
*            This file contains sample code only. It is not part of the production code deliverables.
*
*   @addtogroup RTE_MODULE
*   @{
*/
/*==================================================================================================
*   Project              : AUTOSAR 4.3 MCAL
*   Platform             : ARM
*   Peripheral           : 
*   Dependencies         : none
*
*   Autosar Version      : 4.3.1
*   Autosar Revision     : ASR_REL_4_3_REV_0001
*   Autosar Conf.Variant :
*   SW Version           : 1.0.1
*   Build Version        : S32K14x_MCAL_1_0_1_RTM_P1_ASR_REL_4_3_REV_0001_20191011
*
*   (c) Copyright 2006-2016 Freescale Semiconductor, Inc. 
*       Copyright 2017-2019 NXP
*   All Rights Reserved.
==================================================================================================*/
/*==================================================================================================
==================================================================================================*/

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                         INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Std_Types.h"
#include "Mcal.h"
#include "SchM_Ocu.h"
#ifdef MCAL_TESTING_ENVIRONMENT
#include "EUnit.h" /* EUnit Test Suite */
#endif

/*==================================================================================================
*                                       LOCAL CONSTANTS
==================================================================================================*/
#ifdef MCAL_PLATFORM_ARM
    #if (MCAL_PLATFORM_ARM == MCAL_ARM_AARCH64)
        #define ISR_STATE_MASK     ((uint32)0x00000002UL)   /**< @brief DAIF bit I and F */
    #else 
        #ifdef MCAL_ENABLE_USER_MODE_SUPPORT
            #define ISR_STATE_MASK     ((uint32)0x000000FFUL)   /**< @brief BASEPRI[7:0] mask */
        #else
            #define ISR_STATE_MASK     ((uint32)0x00000001UL)   /**< @brief PRIMASK bit 0 */
        #endif
    #endif 
#else
    #ifdef MCAL_PLATFORM_S12
        #define ISR_STATE_MASK     ((uint32)0x00000010UL)   /**< @brief I bit of CCR */
    #else
        #define ISR_STATE_MASK     ((uint32)0x00008000UL)   /**< @brief EE bit of MSR */
    #endif
#endif
/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/
#ifdef MCAL_PLATFORM_ARM
    #if (MCAL_PLATFORM_ARM == MCAL_ARM_AARCH64)
        #define ISR_ON(msr)            (uint32)(((uint32)(msr) & (uint32)(ISR_STATE_MASK)) != (uint32)3)
    #else
        #define ISR_ON(msr)            (uint32)(((uint32)(msr) & (uint32)(ISR_STATE_MASK)) == (uint32)0)
    #endif    
#else
    #ifdef MCAL_PLATFORM_S12
        #define ISR_ON(msr)            (uint32)(((uint32)(msr) & (uint32)(ISR_STATE_MASK)) == (uint32)0)
    #else
        #define ISR_ON(msr)            (uint32)((uint32)(msr) & (uint32)(ISR_STATE_MASK))
    #endif
#endif

/*==================================================================================================
*                                      FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL VARIABLES
==================================================================================================*/
static uint32 msr_00;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_01;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_02;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_03;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_04;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_05;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_06;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_07;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_08;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_09;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_10;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_11;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_12;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_13;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_14;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_15;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_16;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_17;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_18;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_19;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_20;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_21;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_22;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_23;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_24;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_25;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_26;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_27;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_28;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_29;    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_30;    /**< @brief exclusive area MSR state upon entering*/
static volatile uint32 reentry_guard_00 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_01 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_02 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_03 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_04 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_05 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_06 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_07 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_08 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_09 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_10 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_11 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_12 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_13 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_14 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_15 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_16 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_17 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_18 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_19 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_20 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_21 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_22 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_23 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_24 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_25 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_26 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_27 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_28 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_29 = 0; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_30 = 0; /**< @brief guard for the msr variable against overwrite*/

/*==================================================================================================
*                                       GLOBAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
*                                       GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

#ifndef _COSMIC_C_S32K14x_
/*================================================================================================*/
/** 
* @brief   This function returns the MSR register value (32 bits). 
* @details This function returns the MSR register value (32 bits). 
*     
* @param[in]     void        No input parameters
* @return        uint32 msr  This function returns the MSR register value (32 bits). 
* 
* @pre  None
* @post None
* 
*/
FUNC(uint32, RTE_CODE) Ocu_schm_read_msr(void); 
#endif /*ifndef _COSMIC_C_S32K14x_*/
/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/

#if (defined(_GREENHILLS_C_S32K14x_) || defined(_DIABDATA_C_S32K14x_) || defined(_CODEWARRIOR_C_S32K14x_))
/*================================================================================================*/
/** 
* @brief   This macro returns the MSR register value (32 bits). 
* @details This macro function implementation returns the MSR register value in r3 (32 bits). 
*     
* @pre  None
* @post None
* 
*/
#ifdef MCAL_PLATFORM_ARM
#if (MCAL_PLATFORM_ARM == MCAL_ARM_AARCH64)
ASM_KEYWORD FUNC(uint32, RTE_CODE) Ocu_schm_read_msr(void)
{
    mrs x0, S3_3_c4_c2_1
}
#else
ASM_KEYWORD FUNC(uint32, RTE_CODE) Ocu_schm_read_msr(void)
{
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
    mrs r0, BASEPRI
#else
    mrs r0, PRIMASK
#endif
}
#endif
#else
#ifdef MCAL_PLATFORM_S12
ASM_KEYWORD FUNC(uint32, RTE_CODE) Ocu_schm_read_msr(void)
{
   tfr ccr, d6
}
#else
ASM_KEYWORD FUNC(uint32, RTE_CODE) Ocu_schm_read_msr(void)
{
    mfmsr r3
}
#endif
#endif
#endif /*#ifdef GHS||DIAB||CW*/

#ifdef _COSMIC_C_S32K14x_
/*================================================================================================*/
/** 
* @brief   This function returns the MSR register value (32 bits). 
* @details This function returns the MSR register value (32 bits). 
*     
* @param[in]     void        No input parameters
* @return        uint32 msr  This function returns the MSR register value (32 bits). 
* 
* @pre  None
* @post None
* 
*/

#ifdef MCAL_PLATFORM_S12
    #define Ocu_schm_read_msr()  ASM_KEYWORD("tfr ccr, d6")
#else
    #define Ocu_schm_read_msr() ASM_KEYWORD("mfmsr r3")
#endif

#endif  /*Cosmic compiler only*/


#ifdef _HITECH_C_S32K14x_
/*================================================================================================*/
/** 
* @brief   This function returns the MSR register value (32 bits). 
* @details This function returns the MSR register value (32 bits). 
*     
* @param[in]     void        No input parameters
* @return        uint32 msr  This function returns the MSR register value (32 bits). 
* 
* @pre  None
* @post None
* 
*/
FUNC(uint32, RTE_CODE) Ocu_schm_read_msr(void)
{
    uint32 result;
    __asm volatile("mfmsr %0" : "=r" (result) :);
    return result;
}

#endif  /*HighTec compiler only*/
 /*================================================================================================*/
#ifdef _LINARO_C_S32K14x_
/** 
* @brief   This function returns the MSR register value (32 bits). 
* @details This function returns the MSR register value (32 bits). 
*     
* @param[in]     void        No input parameters
* @return        uint32 msr  This function returns the MSR register value (32 bits). 
* 
* @pre  None
* @post None
* 
*/
FUNC(uint32, RTE_CODE) Ocu_schm_read_msr(void)
{
    register uint32 reg_tmp;
    #if (MCAL_PLATFORM_ARM == MCAL_ARM_AARCH64)
        __asm volatile( " mrs %x0, DAIF " : "=r" (reg_tmp) );
    #else
        #ifdef MCAL_ENABLE_USER_MODE_SUPPORT
        __asm volatile( " mrs %0, basepri " : "=r" (reg_tmp) );
        #else
        __asm volatile( " mrs %0, primask " : "=r" (reg_tmp) );
        #endif
    #endif
    return (uint32)reg_tmp;
}
#endif   /* _LINARO_C_S32K14x_*/
/*================================================================================================*/

#ifdef _ARM_DS5_C_S32K14x_
/** 
* @brief   This function returns the MSR register value (32 bits). 
* @details This function returns the MSR register value (32 bits). 
*     
* @param[in]     void        No input parameters
* @return        uint32 msr  This function returns the MSR register value (32 bits). 
* 
* @pre  None
* @post None
* 
*/
FUNC(uint32, RTE_CODE) Ocu_schm_read_msr(void)
{
    register uint32 reg_tmp;
    #if (MCAL_PLATFORM_ARM == MCAL_ARM_AARCH64)
        __asm volatile( " mrs %x0, DAIF " : "=r" (reg_tmp) );
    #else
        #ifdef MCAL_ENABLE_USER_MODE_SUPPORT
        __asm volatile( " mrs %0, basepri " : "=r" (reg_tmp) );
        #else
        __asm volatile( " mrs %0, primask " : "=r" (reg_tmp) );
        #endif
    #endif
    return (uint32)reg_tmp;
}
#endif   /* _ARM_DS5_C_S32K14x_ */

#ifdef _IAR_C_S32K14x_
/** 
* @brief   This function returns the MSR register value (32 bits). 
* @details This function returns the MSR register value (32 bits). 
*     
* @param[in]     void        No input parameters
* @return        uint32 msr  This function returns the MSR register value (32 bits). 
* 
* @pre  None
* @post None
* 
*/
FUNC(uint32, RTE_CODE) Ocu_schm_read_msr(void)
{
    register uint32 reg_tmp;
   
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
   __asm volatile( " mrs %0, basepri " : "=r" (reg_tmp) );
#else
   __asm volatile( " mrs %0, primask " : "=r" (reg_tmp) );
#endif
   
    return (uint32)reg_tmp;
}
#endif   /* _IAR_C_S32K14x_ */
/*================================================================================================*/
/** 
* @brief   This function is called to allow OCU to enter the specific critical region. 
* @details This is a local function stub only. 
*     
* @param[in]     void     No input parameters
* @return        void     This function does not return anything
* 
* @pre  None
* @post None
* 
*/
FUNC (void, RTE_CODE) SchM_Enter_Ocu_OCU_EXCLUSIVE_AREA_00(void)
{
    if(0UL == reentry_guard_00)
    {
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
       msr_00 = Mcal_Trusted_Call_Return(Ocu_schm_read_msr);
#else
       msr_00 = Ocu_schm_read_msr();  /*read MSR (to store interrupts state)*/
#endif /* MCAL_ENABLE_USER_MODE_SUPPORT */
       if (ISR_ON(msr_00)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
       {
         SuspendAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
         ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
      }
    }
    reentry_guard_00++;
}
FUNC (void, RTE_CODE) SchM_Enter_Ocu_OCU_EXCLUSIVE_AREA_01(void)
{
    if(0UL == reentry_guard_01)
    {
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
       msr_01 = Mcal_Trusted_Call_Return(Ocu_schm_read_msr);
#else
       msr_01 = Ocu_schm_read_msr();  /*read MSR (to store interrupts state)*/
#endif /* MCAL_ENABLE_USER_MODE_SUPPORT */
       if (ISR_ON(msr_01)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
       {
         SuspendAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
         ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
      }
    }
    reentry_guard_01++;
}
FUNC (void, RTE_CODE) SchM_Enter_Ocu_OCU_EXCLUSIVE_AREA_02(void)
{
    if(0UL == reentry_guard_02)
    {
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
       msr_02 = Mcal_Trusted_Call_Return(Ocu_schm_read_msr);
#else
       msr_02 = Ocu_schm_read_msr();  /*read MSR (to store interrupts state)*/
#endif /* MCAL_ENABLE_USER_MODE_SUPPORT */
       if (ISR_ON(msr_02)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
       {
         SuspendAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
         ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
      }
    }
    reentry_guard_02++;
}
FUNC (void, RTE_CODE) SchM_Enter_Ocu_OCU_EXCLUSIVE_AREA_03(void)
{
    if(0UL == reentry_guard_03)
    {
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
       msr_03 = Mcal_Trusted_Call_Return(Ocu_schm_read_msr);
#else
       msr_03 = Ocu_schm_read_msr();  /*read MSR (to store interrupts state)*/
#endif /* MCAL_ENABLE_USER_MODE_SUPPORT */
       if (ISR_ON(msr_03)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
       {
         SuspendAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
         ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
      }
    }
    reentry_guard_03++;
}
FUNC (void, RTE_CODE) SchM_Enter_Ocu_OCU_EXCLUSIVE_AREA_04(void)
{
    if(0UL == reentry_guard_04)
    {
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
       msr_04 = Mcal_Trusted_Call_Return(Ocu_schm_read_msr);
#else
       msr_04 = Ocu_schm_read_msr();  /*read MSR (to store interrupts state)*/
#endif /* MCAL_ENABLE_USER_MODE_SUPPORT */
       if (ISR_ON(msr_04)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
       {
         SuspendAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
         ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
      }
    }
    reentry_guard_04++;
}
FUNC (void, RTE_CODE) SchM_Enter_Ocu_OCU_EXCLUSIVE_AREA_05(void)
{
    if(0UL == reentry_guard_05)
    {
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
       msr_05 = Mcal_Trusted_Call_Return(Ocu_schm_read_msr);
#else
       msr_05 = Ocu_schm_read_msr();  /*read MSR (to store interrupts state)*/
#endif /* MCAL_ENABLE_USER_MODE_SUPPORT */
       if (ISR_ON(msr_05)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
       {
         SuspendAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
         ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
      }
    }
    reentry_guard_05++;
}
FUNC (void, RTE_CODE) SchM_Enter_Ocu_OCU_EXCLUSIVE_AREA_06(void)
{
    if(0UL == reentry_guard_06)
    {
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
       msr_06 = Mcal_Trusted_Call_Return(Ocu_schm_read_msr);
#else
       msr_06 = Ocu_schm_read_msr();  /*read MSR (to store interrupts state)*/
#endif /* MCAL_ENABLE_USER_MODE_SUPPORT */
       if (ISR_ON(msr_06)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
       {
         SuspendAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
         ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
      }
    }
    reentry_guard_06++;
}
FUNC (void, RTE_CODE) SchM_Enter_Ocu_OCU_EXCLUSIVE_AREA_07(void)
{
    if(0UL == reentry_guard_07)
    {
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
       msr_07 = Mcal_Trusted_Call_Return(Ocu_schm_read_msr);
#else
       msr_07 = Ocu_schm_read_msr();  /*read MSR (to store interrupts state)*/
#endif /* MCAL_ENABLE_USER_MODE_SUPPORT */
       if (ISR_ON(msr_07)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
       {
         SuspendAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
         ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
      }
    }
    reentry_guard_07++;
}
FUNC (void, RTE_CODE) SchM_Enter_Ocu_OCU_EXCLUSIVE_AREA_08(void)
{
    if(0UL == reentry_guard_08)
    {
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
       msr_08 = Mcal_Trusted_Call_Return(Ocu_schm_read_msr);
#else
       msr_08 = Ocu_schm_read_msr();  /*read MSR (to store interrupts state)*/
#endif /* MCAL_ENABLE_USER_MODE_SUPPORT */
       if (ISR_ON(msr_08)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
       {
         SuspendAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
         ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
      }
    }
    reentry_guard_08++;
}
FUNC (void, RTE_CODE) SchM_Enter_Ocu_OCU_EXCLUSIVE_AREA_09(void)
{
    if(0UL == reentry_guard_09)
    {
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
       msr_09 = Mcal_Trusted_Call_Return(Ocu_schm_read_msr);
#else
       msr_09 = Ocu_schm_read_msr();  /*read MSR (to store interrupts state)*/
#endif /* MCAL_ENABLE_USER_MODE_SUPPORT */
       if (ISR_ON(msr_09)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
       {
         SuspendAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
         ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
      }
    }
    reentry_guard_09++;
}
FUNC (void, RTE_CODE) SchM_Enter_Ocu_OCU_EXCLUSIVE_AREA_10(void)
{
    if(0UL == reentry_guard_10)
    {
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
       msr_10 = Mcal_Trusted_Call_Return(Ocu_schm_read_msr);
#else
       msr_10 = Ocu_schm_read_msr();  /*read MSR (to store interrupts state)*/
#endif /* MCAL_ENABLE_USER_MODE_SUPPORT */
       if (ISR_ON(msr_10)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
       {
         SuspendAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
         ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
      }
    }
    reentry_guard_10++;
}
FUNC (void, RTE_CODE) SchM_Enter_Ocu_OCU_EXCLUSIVE_AREA_11(void)
{
    if(0UL == reentry_guard_11)
    {
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
       msr_11 = Mcal_Trusted_Call_Return(Ocu_schm_read_msr);
#else
       msr_11 = Ocu_schm_read_msr();  /*read MSR (to store interrupts state)*/
#endif /* MCAL_ENABLE_USER_MODE_SUPPORT */
       if (ISR_ON(msr_11)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
       {
         SuspendAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
         ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
      }
    }
    reentry_guard_11++;
}
FUNC (void, RTE_CODE) SchM_Enter_Ocu_OCU_EXCLUSIVE_AREA_12(void)
{
    if(0UL == reentry_guard_12)
    {
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
       msr_12 = Mcal_Trusted_Call_Return(Ocu_schm_read_msr);
#else
       msr_12 = Ocu_schm_read_msr();  /*read MSR (to store interrupts state)*/
#endif /* MCAL_ENABLE_USER_MODE_SUPPORT */
       if (ISR_ON(msr_12)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
       {
         SuspendAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
         ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
      }
    }
    reentry_guard_12++;
}
FUNC (void, RTE_CODE) SchM_Enter_Ocu_OCU_EXCLUSIVE_AREA_13(void)
{
    if(0UL == reentry_guard_13)
    {
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
       msr_13 = Mcal_Trusted_Call_Return(Ocu_schm_read_msr);
#else
       msr_13 = Ocu_schm_read_msr();  /*read MSR (to store interrupts state)*/
#endif /* MCAL_ENABLE_USER_MODE_SUPPORT */
       if (ISR_ON(msr_13)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
       {
         SuspendAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
         ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
      }
    }
    reentry_guard_13++;
}
FUNC (void, RTE_CODE) SchM_Enter_Ocu_OCU_EXCLUSIVE_AREA_14(void)
{
    if(0UL == reentry_guard_14)
    {
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
       msr_14 = Mcal_Trusted_Call_Return(Ocu_schm_read_msr);
#else
       msr_14 = Ocu_schm_read_msr();  /*read MSR (to store interrupts state)*/
#endif /* MCAL_ENABLE_USER_MODE_SUPPORT */
       if (ISR_ON(msr_14)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
       {
         SuspendAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
         ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
      }
    }
    reentry_guard_14++;
}
FUNC (void, RTE_CODE) SchM_Enter_Ocu_OCU_EXCLUSIVE_AREA_15(void)
{
    if(0UL == reentry_guard_15)
    {
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
       msr_15 = Mcal_Trusted_Call_Return(Ocu_schm_read_msr);
#else
       msr_15 = Ocu_schm_read_msr();  /*read MSR (to store interrupts state)*/
#endif /* MCAL_ENABLE_USER_MODE_SUPPORT */
       if (ISR_ON(msr_15)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
       {
         SuspendAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
         ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
      }
    }
    reentry_guard_15++;
}
FUNC (void, RTE_CODE) SchM_Enter_Ocu_OCU_EXCLUSIVE_AREA_16(void)
{
    if(0UL == reentry_guard_16)
    {
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
       msr_16 = Mcal_Trusted_Call_Return(Ocu_schm_read_msr);
#else
       msr_16 = Ocu_schm_read_msr();  /*read MSR (to store interrupts state)*/
#endif /* MCAL_ENABLE_USER_MODE_SUPPORT */
       if (ISR_ON(msr_16)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
       {
         SuspendAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
         ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
      }
    }
    reentry_guard_16++;
}
FUNC (void, RTE_CODE) SchM_Enter_Ocu_OCU_EXCLUSIVE_AREA_17(void)
{
    if(0UL == reentry_guard_17)
    {
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
       msr_17 = Mcal_Trusted_Call_Return(Ocu_schm_read_msr);
#else
       msr_17 = Ocu_schm_read_msr();  /*read MSR (to store interrupts state)*/
#endif /* MCAL_ENABLE_USER_MODE_SUPPORT */
       if (ISR_ON(msr_17)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
       {
         SuspendAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
         ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
      }
    }
    reentry_guard_17++;
}
FUNC (void, RTE_CODE) SchM_Enter_Ocu_OCU_EXCLUSIVE_AREA_18(void)
{
    if(0UL == reentry_guard_18)
    {
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
       msr_18 = Mcal_Trusted_Call_Return(Ocu_schm_read_msr);
#else
       msr_18 = Ocu_schm_read_msr();  /*read MSR (to store interrupts state)*/
#endif /* MCAL_ENABLE_USER_MODE_SUPPORT */
       if (ISR_ON(msr_18)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
       {
         SuspendAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
         ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
      }
    }
    reentry_guard_18++;
}
FUNC (void, RTE_CODE) SchM_Enter_Ocu_OCU_EXCLUSIVE_AREA_19(void)
{
    if(0UL == reentry_guard_19)
    {
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
       msr_19 = Mcal_Trusted_Call_Return(Ocu_schm_read_msr);
#else
       msr_19 = Ocu_schm_read_msr();  /*read MSR (to store interrupts state)*/
#endif /* MCAL_ENABLE_USER_MODE_SUPPORT */
       if (ISR_ON(msr_19)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
       {
         SuspendAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
         ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
      }
    }
    reentry_guard_19++;
}
FUNC (void, RTE_CODE) SchM_Enter_Ocu_OCU_EXCLUSIVE_AREA_20(void)
{
    if(0UL == reentry_guard_20)
    {
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
       msr_20 = Mcal_Trusted_Call_Return(Ocu_schm_read_msr);
#else
       msr_20 = Ocu_schm_read_msr();  /*read MSR (to store interrupts state)*/
#endif /* MCAL_ENABLE_USER_MODE_SUPPORT */
       if (ISR_ON(msr_20)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
       {
         SuspendAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
         ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
      }
    }
    reentry_guard_20++;
}
FUNC (void, RTE_CODE) SchM_Enter_Ocu_OCU_EXCLUSIVE_AREA_21(void)
{
    if(0UL == reentry_guard_21)
    {
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
       msr_21 = Mcal_Trusted_Call_Return(Ocu_schm_read_msr);
#else
       msr_21 = Ocu_schm_read_msr();  /*read MSR (to store interrupts state)*/
#endif /* MCAL_ENABLE_USER_MODE_SUPPORT */
       if (ISR_ON(msr_21)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
       {
         SuspendAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
         ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
      }
    }
    reentry_guard_21++;
}
FUNC (void, RTE_CODE) SchM_Enter_Ocu_OCU_EXCLUSIVE_AREA_22(void)
{
    if(0UL == reentry_guard_22)
    {
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
       msr_22 = Mcal_Trusted_Call_Return(Ocu_schm_read_msr);
#else
       msr_22 = Ocu_schm_read_msr();  /*read MSR (to store interrupts state)*/
#endif /* MCAL_ENABLE_USER_MODE_SUPPORT */
       if (ISR_ON(msr_22)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
       {
         SuspendAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
         ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
      }
    }
    reentry_guard_22++;
}
FUNC (void, RTE_CODE) SchM_Enter_Ocu_OCU_EXCLUSIVE_AREA_23(void)
{
    if(0UL == reentry_guard_23)
    {
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
       msr_23 = Mcal_Trusted_Call_Return(Ocu_schm_read_msr);
#else
       msr_23 = Ocu_schm_read_msr();  /*read MSR (to store interrupts state)*/
#endif /* MCAL_ENABLE_USER_MODE_SUPPORT */
       if (ISR_ON(msr_23)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
       {
         SuspendAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
         ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
      }
    }
    reentry_guard_23++;
}
FUNC (void, RTE_CODE) SchM_Enter_Ocu_OCU_EXCLUSIVE_AREA_24(void)
{
    if(0UL == reentry_guard_24)
    {
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
       msr_24 = Mcal_Trusted_Call_Return(Ocu_schm_read_msr);
#else
       msr_24 = Ocu_schm_read_msr();  /*read MSR (to store interrupts state)*/
#endif /* MCAL_ENABLE_USER_MODE_SUPPORT */
       if (ISR_ON(msr_24)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
       {
         SuspendAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
         ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
      }
    }
    reentry_guard_24++;
}
FUNC (void, RTE_CODE) SchM_Enter_Ocu_OCU_EXCLUSIVE_AREA_25(void)
{
    if(0UL == reentry_guard_25)
    {
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
       msr_25 = Mcal_Trusted_Call_Return(Ocu_schm_read_msr);
#else
       msr_25 = Ocu_schm_read_msr();  /*read MSR (to store interrupts state)*/
#endif /* MCAL_ENABLE_USER_MODE_SUPPORT */
       if (ISR_ON(msr_25)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
       {
         SuspendAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
         ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
      }
    }
    reentry_guard_25++;
}
FUNC (void, RTE_CODE) SchM_Enter_Ocu_OCU_EXCLUSIVE_AREA_26(void)
{
    if(0UL == reentry_guard_26)
    {
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
       msr_26 = Mcal_Trusted_Call_Return(Ocu_schm_read_msr);
#else
       msr_26 = Ocu_schm_read_msr();  /*read MSR (to store interrupts state)*/
#endif /* MCAL_ENABLE_USER_MODE_SUPPORT */
       if (ISR_ON(msr_26)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
       {
         SuspendAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
         ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
      }
    }
    reentry_guard_26++;
}
FUNC (void, RTE_CODE) SchM_Enter_Ocu_OCU_EXCLUSIVE_AREA_27(void)
{
    if(0UL == reentry_guard_27)
    {
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
       msr_27 = Mcal_Trusted_Call_Return(Ocu_schm_read_msr);
#else
       msr_27 = Ocu_schm_read_msr();  /*read MSR (to store interrupts state)*/
#endif /* MCAL_ENABLE_USER_MODE_SUPPORT */
       if (ISR_ON(msr_27)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
       {
         SuspendAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
         ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
      }
    }
    reentry_guard_27++;
}
FUNC (void, RTE_CODE) SchM_Enter_Ocu_OCU_EXCLUSIVE_AREA_28(void)
{
    if(0UL == reentry_guard_28)
    {
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
       msr_28 = Mcal_Trusted_Call_Return(Ocu_schm_read_msr);
#else
       msr_28 = Ocu_schm_read_msr();  /*read MSR (to store interrupts state)*/
#endif /* MCAL_ENABLE_USER_MODE_SUPPORT */
       if (ISR_ON(msr_28)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
       {
         SuspendAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
         ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
      }
    }
    reentry_guard_28++;
}
FUNC (void, RTE_CODE) SchM_Enter_Ocu_OCU_EXCLUSIVE_AREA_29(void)
{
    if(0UL == reentry_guard_29)
    {
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
       msr_29 = Mcal_Trusted_Call_Return(Ocu_schm_read_msr);
#else
       msr_29 = Ocu_schm_read_msr();  /*read MSR (to store interrupts state)*/
#endif /* MCAL_ENABLE_USER_MODE_SUPPORT */
       if (ISR_ON(msr_29)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
       {
         SuspendAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
         ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
      }
    }
    reentry_guard_29++;
}
FUNC (void, RTE_CODE) SchM_Enter_Ocu_OCU_EXCLUSIVE_AREA_30(void)
{
    if(0UL == reentry_guard_30)
    {
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
       msr_30 = Mcal_Trusted_Call_Return(Ocu_schm_read_msr);
#else
       msr_30 = Ocu_schm_read_msr();  /*read MSR (to store interrupts state)*/
#endif /* MCAL_ENABLE_USER_MODE_SUPPORT */
       if (ISR_ON(msr_30)) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
       {
         SuspendAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
         ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
      }
    }
    reentry_guard_30++;
}
                          
/*================================================================================================*/
/** 
* @brief   This function is called to allow OCU to exit the specific critical region. 
* @details This is a local function stub only. It will resume interrupts if no other 
*          critical area is still executing.
*     
* @param[in]     void     No input parameters
* @return        void     This function does not return anything
* 
* @pre  None
* @post None
* 
*/
FUNC (void, RTE_CODE) SchM_Exit_Ocu_OCU_EXCLUSIVE_AREA_00(void)
{
    reentry_guard_00--;
    if ((ISR_ON(msr_00))&&(0UL == reentry_guard_00))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
      ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
    }
}
FUNC (void, RTE_CODE) SchM_Exit_Ocu_OCU_EXCLUSIVE_AREA_01(void)
{
    reentry_guard_01--;
    if ((ISR_ON(msr_01))&&(0UL == reentry_guard_01))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
      ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
    }
}
FUNC (void, RTE_CODE) SchM_Exit_Ocu_OCU_EXCLUSIVE_AREA_02(void)
{
    reentry_guard_02--;
    if ((ISR_ON(msr_02))&&(0UL == reentry_guard_02))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
      ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
    }
}
FUNC (void, RTE_CODE) SchM_Exit_Ocu_OCU_EXCLUSIVE_AREA_03(void)
{
    reentry_guard_03--;
    if ((ISR_ON(msr_03))&&(0UL == reentry_guard_03))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
      ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
    }
}
FUNC (void, RTE_CODE) SchM_Exit_Ocu_OCU_EXCLUSIVE_AREA_04(void)
{
    reentry_guard_04--;
    if ((ISR_ON(msr_04))&&(0UL == reentry_guard_04))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
      ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
    }
}
FUNC (void, RTE_CODE) SchM_Exit_Ocu_OCU_EXCLUSIVE_AREA_05(void)
{
    reentry_guard_05--;
    if ((ISR_ON(msr_05))&&(0UL == reentry_guard_05))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
      ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
    }
}
FUNC (void, RTE_CODE) SchM_Exit_Ocu_OCU_EXCLUSIVE_AREA_06(void)
{
    reentry_guard_06--;
    if ((ISR_ON(msr_06))&&(0UL == reentry_guard_06))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
      ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
    }
}
FUNC (void, RTE_CODE) SchM_Exit_Ocu_OCU_EXCLUSIVE_AREA_07(void)
{
    reentry_guard_07--;
    if ((ISR_ON(msr_07))&&(0UL == reentry_guard_07))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
      ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
    }
}
FUNC (void, RTE_CODE) SchM_Exit_Ocu_OCU_EXCLUSIVE_AREA_08(void)
{
    reentry_guard_08--;
    if ((ISR_ON(msr_08))&&(0UL == reentry_guard_08))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
      ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
    }
}
FUNC (void, RTE_CODE) SchM_Exit_Ocu_OCU_EXCLUSIVE_AREA_09(void)
{
    reentry_guard_09--;
    if ((ISR_ON(msr_09))&&(0UL == reentry_guard_09))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
      ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
    }
}
FUNC (void, RTE_CODE) SchM_Exit_Ocu_OCU_EXCLUSIVE_AREA_10(void)
{
    reentry_guard_10--;
    if ((ISR_ON(msr_10))&&(0UL == reentry_guard_10))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
      ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
    }
}
FUNC (void, RTE_CODE) SchM_Exit_Ocu_OCU_EXCLUSIVE_AREA_11(void)
{
    reentry_guard_11--;
    if ((ISR_ON(msr_11))&&(0UL == reentry_guard_11))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
      ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
    }
}
FUNC (void, RTE_CODE) SchM_Exit_Ocu_OCU_EXCLUSIVE_AREA_12(void)
{
    reentry_guard_12--;
    if ((ISR_ON(msr_12))&&(0UL == reentry_guard_12))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
      ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
    }
}
FUNC (void, RTE_CODE) SchM_Exit_Ocu_OCU_EXCLUSIVE_AREA_13(void)
{
    reentry_guard_13--;
    if ((ISR_ON(msr_13))&&(0UL == reentry_guard_13))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
      ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
    }
}
FUNC (void, RTE_CODE) SchM_Exit_Ocu_OCU_EXCLUSIVE_AREA_14(void)
{
    reentry_guard_14--;
    if ((ISR_ON(msr_14))&&(0UL == reentry_guard_14))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
      ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
    }
}
FUNC (void, RTE_CODE) SchM_Exit_Ocu_OCU_EXCLUSIVE_AREA_15(void)
{
    reentry_guard_15--;
    if ((ISR_ON(msr_15))&&(0UL == reentry_guard_15))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
      ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
    }
}
FUNC (void, RTE_CODE) SchM_Exit_Ocu_OCU_EXCLUSIVE_AREA_16(void)
{
    reentry_guard_16--;
    if ((ISR_ON(msr_16))&&(0UL == reentry_guard_16))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
      ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
    }
}
FUNC (void, RTE_CODE) SchM_Exit_Ocu_OCU_EXCLUSIVE_AREA_17(void)
{
    reentry_guard_17--;
    if ((ISR_ON(msr_17))&&(0UL == reentry_guard_17))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
      ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
    }
}
FUNC (void, RTE_CODE) SchM_Exit_Ocu_OCU_EXCLUSIVE_AREA_18(void)
{
    reentry_guard_18--;
    if ((ISR_ON(msr_18))&&(0UL == reentry_guard_18))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
      ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
    }
}
FUNC (void, RTE_CODE) SchM_Exit_Ocu_OCU_EXCLUSIVE_AREA_19(void)
{
    reentry_guard_19--;
    if ((ISR_ON(msr_19))&&(0UL == reentry_guard_19))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
      ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
    }
}
FUNC (void, RTE_CODE) SchM_Exit_Ocu_OCU_EXCLUSIVE_AREA_20(void)
{
    reentry_guard_20--;
    if ((ISR_ON(msr_20))&&(0UL == reentry_guard_20))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
      ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
    }
}
FUNC (void, RTE_CODE) SchM_Exit_Ocu_OCU_EXCLUSIVE_AREA_21(void)
{
    reentry_guard_21--;
    if ((ISR_ON(msr_21))&&(0UL == reentry_guard_21))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
      ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
    }
}
FUNC (void, RTE_CODE) SchM_Exit_Ocu_OCU_EXCLUSIVE_AREA_22(void)
{
    reentry_guard_22--;
    if ((ISR_ON(msr_22))&&(0UL == reentry_guard_22))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
      ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
    }
}
FUNC (void, RTE_CODE) SchM_Exit_Ocu_OCU_EXCLUSIVE_AREA_23(void)
{
    reentry_guard_23--;
    if ((ISR_ON(msr_23))&&(0UL == reentry_guard_23))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
      ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
    }
}
FUNC (void, RTE_CODE) SchM_Exit_Ocu_OCU_EXCLUSIVE_AREA_24(void)
{
    reentry_guard_24--;
    if ((ISR_ON(msr_24))&&(0UL == reentry_guard_24))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
      ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
    }
}
FUNC (void, RTE_CODE) SchM_Exit_Ocu_OCU_EXCLUSIVE_AREA_25(void)
{
    reentry_guard_25--;
    if ((ISR_ON(msr_25))&&(0UL == reentry_guard_25))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
      ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
    }
}
FUNC (void, RTE_CODE) SchM_Exit_Ocu_OCU_EXCLUSIVE_AREA_26(void)
{
    reentry_guard_26--;
    if ((ISR_ON(msr_26))&&(0UL == reentry_guard_26))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
      ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
    }
}
FUNC (void, RTE_CODE) SchM_Exit_Ocu_OCU_EXCLUSIVE_AREA_27(void)
{
    reentry_guard_27--;
    if ((ISR_ON(msr_27))&&(0UL == reentry_guard_27))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
      ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
    }
}
FUNC (void, RTE_CODE) SchM_Exit_Ocu_OCU_EXCLUSIVE_AREA_28(void)
{
    reentry_guard_28--;
    if ((ISR_ON(msr_28))&&(0UL == reentry_guard_28))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
      ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
    }
}
FUNC (void, RTE_CODE) SchM_Exit_Ocu_OCU_EXCLUSIVE_AREA_29(void)
{
    reentry_guard_29--;
    if ((ISR_ON(msr_29))&&(0UL == reentry_guard_29))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
      ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
    }
}
FUNC (void, RTE_CODE) SchM_Exit_Ocu_OCU_EXCLUSIVE_AREA_30(void)
{
    reentry_guard_30--;
    if ((ISR_ON(msr_30))&&(0UL == reentry_guard_30))         /*if interrupts were enabled*/
    {
      ResumeAllInterrupts();
#ifdef _ARM_DS5_C_S32K14x_
      ASM_KEYWORD(" nop ");/* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
    }
}

#ifdef MCAL_TESTING_ENVIRONMENT
/** 
@brief   This function checks that all entered exclusive areas were also exited. 
@details This function checks that all entered exclusive areas were also exited. The check
         is done by verifying that all reentry_guard_* static variables are back to the
         zero value.
    
@param[in]     void       No input parameters
@return        void       This function does not return a value. Test asserts are used instead. 

@pre  None
@post None

@remarks Covers 
@remarks Implements 
*/
FUNC(void, RTE_CODE) SchM_Check_ocu(void)
{
  EU_ASSERT(0UL == reentry_guard_00);
  EU_ASSERT(0UL == reentry_guard_01);
  EU_ASSERT(0UL == reentry_guard_02);
  EU_ASSERT(0UL == reentry_guard_03);
  EU_ASSERT(0UL == reentry_guard_04);
  EU_ASSERT(0UL == reentry_guard_05);
  EU_ASSERT(0UL == reentry_guard_06);
  EU_ASSERT(0UL == reentry_guard_07);
  EU_ASSERT(0UL == reentry_guard_08);
  EU_ASSERT(0UL == reentry_guard_09);
  EU_ASSERT(0UL == reentry_guard_10);
  EU_ASSERT(0UL == reentry_guard_11);
  EU_ASSERT(0UL == reentry_guard_12);
  EU_ASSERT(0UL == reentry_guard_13);
  EU_ASSERT(0UL == reentry_guard_14);
  EU_ASSERT(0UL == reentry_guard_15);
  EU_ASSERT(0UL == reentry_guard_16);
  EU_ASSERT(0UL == reentry_guard_17);
  EU_ASSERT(0UL == reentry_guard_18);
  EU_ASSERT(0UL == reentry_guard_19);
  EU_ASSERT(0UL == reentry_guard_20);
  EU_ASSERT(0UL == reentry_guard_21);
  EU_ASSERT(0UL == reentry_guard_22);
  EU_ASSERT(0UL == reentry_guard_23);
  EU_ASSERT(0UL == reentry_guard_24);
  EU_ASSERT(0UL == reentry_guard_25);
  EU_ASSERT(0UL == reentry_guard_26);
  EU_ASSERT(0UL == reentry_guard_27);
  EU_ASSERT(0UL == reentry_guard_28);
  EU_ASSERT(0UL == reentry_guard_29);
  EU_ASSERT(0UL == reentry_guard_30);
  reentry_guard_00 = 0UL; /*reset reentry_guard_00 for the next test in the suite*/
  reentry_guard_01 = 0UL; /*reset reentry_guard_01 for the next test in the suite*/
  reentry_guard_02 = 0UL; /*reset reentry_guard_02 for the next test in the suite*/
  reentry_guard_03 = 0UL; /*reset reentry_guard_03 for the next test in the suite*/
  reentry_guard_04 = 0UL; /*reset reentry_guard_04 for the next test in the suite*/
  reentry_guard_05 = 0UL; /*reset reentry_guard_05 for the next test in the suite*/
  reentry_guard_06 = 0UL; /*reset reentry_guard_06 for the next test in the suite*/
  reentry_guard_07 = 0UL; /*reset reentry_guard_07 for the next test in the suite*/
  reentry_guard_08 = 0UL; /*reset reentry_guard_08 for the next test in the suite*/
  reentry_guard_09 = 0UL; /*reset reentry_guard_09 for the next test in the suite*/
  reentry_guard_10 = 0UL; /*reset reentry_guard_10 for the next test in the suite*/
  reentry_guard_11 = 0UL; /*reset reentry_guard_11 for the next test in the suite*/
  reentry_guard_12 = 0UL; /*reset reentry_guard_12 for the next test in the suite*/
  reentry_guard_13 = 0UL; /*reset reentry_guard_13 for the next test in the suite*/
  reentry_guard_14 = 0UL; /*reset reentry_guard_14 for the next test in the suite*/
  reentry_guard_15 = 0UL; /*reset reentry_guard_15 for the next test in the suite*/
  reentry_guard_16 = 0UL; /*reset reentry_guard_16 for the next test in the suite*/
  reentry_guard_17 = 0UL; /*reset reentry_guard_17 for the next test in the suite*/
  reentry_guard_18 = 0UL; /*reset reentry_guard_18 for the next test in the suite*/
  reentry_guard_19 = 0UL; /*reset reentry_guard_19 for the next test in the suite*/
  reentry_guard_20 = 0UL; /*reset reentry_guard_20 for the next test in the suite*/
  reentry_guard_21 = 0UL; /*reset reentry_guard_21 for the next test in the suite*/
  reentry_guard_22 = 0UL; /*reset reentry_guard_22 for the next test in the suite*/
  reentry_guard_23 = 0UL; /*reset reentry_guard_23 for the next test in the suite*/
  reentry_guard_24 = 0UL; /*reset reentry_guard_24 for the next test in the suite*/
  reentry_guard_25 = 0UL; /*reset reentry_guard_25 for the next test in the suite*/
  reentry_guard_26 = 0UL; /*reset reentry_guard_26 for the next test in the suite*/
  reentry_guard_27 = 0UL; /*reset reentry_guard_27 for the next test in the suite*/
  reentry_guard_28 = 0UL; /*reset reentry_guard_28 for the next test in the suite*/
  reentry_guard_29 = 0UL; /*reset reentry_guard_29 for the next test in the suite*/
  reentry_guard_30 = 0UL; /*reset reentry_guard_30 for the next test in the suite*/
}
#endif /*MCAL_TESTING_ENVIRONMENT*/


#ifdef __cplusplus
}
#endif

/** @} */
