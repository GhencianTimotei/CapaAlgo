 /*!
* \defgroup MOD_MCAL_OS
* \{
******************************************************************************
*
* \par Module Owner:
* Huf Group
*
* \par Initial Project:
* 1656.001 BSW
*
******************************************************************************
* \par Description:
*  This is the configurable header file for the MOD_MCAL_OS module.
*  Contains definitions for types, defines and external functions' declarations.
******************************************************************************
*
* %PCMS_HEADER_SUBSTITUTION_START:%
*
* Configuration Management Information Log (generated by Dimensions CM)
*
*
* CM Item: %PID:%
* Item name: %PM:%
* Location: %ARCHIVE:%
* Revision: %PR:%
* Date: %DATE:%
* Author: %AUTHOR:%
*
* %PCMS_HEADER_SUBSTITUTION_END:% *
******************************************************************************
*
* \par Layer:
*  Mcal
*
* \par Compiler dialect:
*  C99
*
* \par Controller:
*  RL78, RH850, S32K
*
* \par Estimated resources:
* | Resource | Amount   | Remarks         |
* | ---------| -------- | ----------------|
* | ROM      | x Byte   | on x controller |
* | RAM      | y Byte   | on x controller |
* | NVRAM    | z Byte   | on x controller |
* | Runtime Init | X ms |                 |
* | Runtime Task | X ms |                 |
*
******************************************************************************/  
#ifndef OS_MCAL_CFG_H_                   /* To avoid double inclusion */
#define OS_MCAL_CFG_H_

/* Include files */
/* polyspace-begin MISRA-C3:1.1 [Not a defect:Unset] "Includes are necessary into current implementation" */
#include "Os_CommonCfg.h"
#include "StdRegMacros.h"
#include "Mcal.h"
/* polyspace-end MISRA-C3:1.1 [Not a defect:Unset] "Includes are necessary into current implementation" */

/* polyspace-begin MISRA-C3:2.5 [Not a defect:Unset] "Macros are useful to integration project or into different configurations" */
/*[SWPS_SWS_MCALOS_00037]*/
/* Define timer interrupt cycle time in us */
#define OS_TICK_TIME_US ((U16)2500)

#define OS_RL78                0u
#define OS_RH850               1u
#define OS_S32K                2u
#define OS_OTHER_UC_FAMILY     3u
/* Use RL78,RH850, S32K or other controller family */
#define OS_CONTROLLER_FAMILY   OS_S32K

#define OS_TIMER_RJ_RL78       0u
#define OS_TIMER_BSW_GPT       1u
#define OS_TIMER_EXTERNAL      2u
#define OS_TIMER_OSTM0_RH850   3u
#define OS_TIMER_SYSTICK_S32K  4u
/* Use TimerRJ RL78, a BSW Gpt timer, OSTM0 timer, SYSTICK timer or the timer is handled externally */
#define OS_TIMER_SOURCE   OS_TIMER_SYSTICK_S32K /*[SWPS_SWS_MCALOS_00002]*/
/* polyspace-end MISRA-C3:2.5 [Not a defect:Unset] "Macros are useful to integration project or into different configurations" */

 /* SysTick registers and bits' definition */
#define SYSTICK_CSR_BASE_ADDRS      (0xE000E010u)  /* SysTick Control and Status Register */
#define SYSTICK_RVR_BASE_ADDRS      (0xE000E014u)  /* SysTick Reload Value Register */
#define SYSTICK_CVR_BASE_ADDRS      (0xE000E018u)  /* SysTick Current Value Register */
#define SCB_ICSR_BASE_ADDRS         (0xE000ED04u)  /* Interrupt Control and State Register */
#define SYSTICK_CSR_ENABLE_MASK     (0x00000001u)  /* This bit enables the counter: 0 - disabled, 1 - enabled*/
#define SYSTICK_CSR_TICKINT_MASK    (0x00000002u)  /* This bit enables SysTick exception request: 0 - disabled, 1 - enabled */
#define SYSTICK_CSR_CLKSOURCE_MASK  (0x00000004u)  /* This bit indicates the clock source: 0 - external clock, 1 - processor clock */
#define SCB_ICSR_PENDSTCLR_MASK     (0x02000000u)  /* SysTick exception clear-pending bit. Write: 0 - no effect, 1 - removes the pending state from the SysTick exception.*/

#if (STD_ON == OS_ENABLE_BACKGROUND_TASK)
#define PENDSV_SET_PENDING_MASK      (0x10000000u)  /* PendSV set-pending bit mask */
#define SVCALL_SET_PENDING_MASK      (0x00008000u)  /* SVCall set-pending bit mask */
#define SCB_SHCSR_BASE_ADDRS         (0xE000ED24u)  /* System Handler Control and State Register(SHCSR) base address */
#endif
/*OS tick timer frequency configured by user is TIMER_FREQ = 80MHz */
/* timer ticks are calculated based on the timer frequency and the expected interrupt time OS_TICK_TIME_US * TIMER_FREQ */
#define OS_TIMER_TICKS     (U32)(200000)

/* polyspace-begin MISRA-C3:D4.9,2.5 [Not a defect:Unset] "Macro used to facilitate an easier adaptation. Can be used into integration project." */
/* OS Timer interrupt handlers */
/*[SWPS_SWS_MCALOS_00009], [SWPS_SWS_MCALOS_00010], [SWPS_SWS_MCALOS_00011]*/
#define OS_ENABLE_TIMER_INT()         REG_BIT_SET32(SYSTICK_CSR_BASE_ADDRS, SYSTICK_CSR_TICKINT_MASK)  /*[SWPS_SWS_MCALOS_00027]*/
#define OS_DISABLE_TIMER_INT()        REG_BIT_CLEAR32(SYSTICK_CSR_BASE_ADDRS, SYSTICK_CSR_TICKINT_MASK)  /*[SWPS_SWS_MCALOS_00028]*/
#define OS_CLEAR_TIMER_PENDING_INT()  REG_BIT_SET32(SCB_ICSR_BASE_ADDRS, SCB_ICSR_PENDSTCLR_MASK)  /*[SWPS_SWS_MCALOS_00029]*/
/* polyspace-end MISRA-C3:D4.9,2.5 [Not a defect:Unset] "Macro used to facilitate an easier adaptation. Can be used into integration project." */

#define OS_ISR_USED_IN_SLEEP_MODE  STD_OFF

/*[SWPS_SWS_MCALOS_00006]*/
/* Enable/disable functionality of saving context on stack - used for background task functionality */
#if (STD_OFF == OS_ENABLE_BACKGROUND_TASK)
#define OS_SAVE_CONTEXT_ON_STACK STD_OFF
#else
#define OS_SAVE_CONTEXT_ON_STACK STD_ON
/* polyspace +1 MISRA-C3:D4.9 [Not a defect:Unset] "Macro used to facilitate an easier adaptation" */
#define OS_CHECK_ALARMS_FUNCTION()   Os_AlarmsEvaluation()
extern void Os_AlarmsEvaluation(void);

/* polyspace-begin MISRA-C3:D4.9 [Not a defect:Unset] "Macro used to facilitate an easier adaptation." */
/*Used into tick ISR to set as pending the PendSV exception; on the PendSV's handler the current context will be saved 
*and Os_CheckAlarms() will be pushed on stack to be executed after exiting from PendSV handler.*/
#define OS_SAVE_CONTEXT()    REG_BIT_SET32(SCB_ICSR_BASE_ADDRS, PENDSV_SET_PENDING_MASK)
/* Used into Os_CheckAlarms() to set SVCall exception to pending; on the SVCall's handler the context will be restored*/
#define OS_RESTORE_CONTEXT() REG_BIT_SET32(SCB_SHCSR_BASE_ADDRS, SVCALL_SET_PENDING_MASK)
/* polyspace-end MISRA-C3:D4.9 [Not a defect:Unset] "Macro used to facilitate an easier adaptation." */
#endif /*OS_ENABLE_BACKGROUND_TASK*/

/* Disable interrupts */
/* [SWPS_SWS_MCALOS_00008] */
/* polyspace +1 MISRA-C3:D4.9 [Not a defect:Unset] "Macro used to facilitate an easier adaptation" */
#define OS_DISABLE_INTERRUPT() __asm(" cpsid i") /*[SWPS_SWS_MCALOS_00026]*/
/* Enable interrupts */
/* [SWPS_SWS_MCALOS_00007] */
/* polyspace +1 MISRA-C3:D4.9 [Not a defect:Unset] "Macro used to facilitate an easier adaptation" */
#define OS_ENABLE_INTERRUPT() __asm(" cpsie i") /*[SWPS_SWS_MCALOS_00025]*/

#define OS_DEBUG_EN  STD_OFF
#if(STD_OFF != OS_DEBUG_EN)
/* polyspace +1 MISRA-C3:D4.9 [Not a defect:Unset] " The macro is used to facilitate an easy adaptation. " */
#define OS_TICK_PIN_TOGGLE()    
#endif /* OS_DEBUG_EN */

#endif /* OS_MCAL_CFG_H_ */

/* %PCMS_HEADER_SUBSTITUTION_START:%
******************************************************************************
* Document Management Information Log (generated by Dimensions CM)
*
* Description:
* %PD:%
*
* Used by Baselines:
* %PIRB:%
*
* Used by Dimensions CM Projects:
* %PIRW:%
*
* Change History:
* %PL:%
*
* %PCMS_HEADER_SUBSTITUTION_END:%
*/