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
 *            Module: FblHal
 *           Program: FBL Vag SLP3 (FBL_Vag_SLP3)
 *          Customer: Huf H_lsbeck & F_rst GmbH & Co. KG
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: S32K144
 *    License Scope : The usage is restricted to CBD2100259_D00
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: FblHal_Cfg.h
 *   Generation Time: 2021-06-10 15:28:01
 *           Project: DemoAppl - Version 1
 *          Delivery: CBD2100259_D00
 *      Tool Version: DaVinci Configurator  5.23.30 SP1
 *
 *
 *********************************************************************************************************************/


#if !defined(__FBL_HAL_H__)
/* polyspace < MISRA-C3:21.1 : Not a defect : Justify with annotations> This macro is used to facilitate an easy adaptation */
#define __FBL_HAL_H__

/* FblHal__base ******************************************************************************************************/
/* polyspace:begin < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
#define FBL_FLASH_DISABLE_ECC_SAFE_READ 
#define FLASH_SIZE                      1024 
#define FBL_TIMER_RELOAD_VALUE          79999 
#define FBL_TIMER_PRESCALER_VALUE       1 

/* Derivative Specific Defines */
#define V_COMP_IAR
#define V_COMP_IAR_S32
#define C_COMP_IAR_S32_FLEXCAN3
#define C_PROCESSOR_S32K146
#define V_CPU_S32
#define C_CPUTYPE_32BIT
#define V_SUPPRESS_EXTENDED_VERSION_CHECK
#define VGEN_ENABLE_CANFBL
#define V_ENABLE_CAN_ASR_ABSTRACTION
#define FBL_SCG_BASE          0x40064000ul            /**< System Clock Generator base address     */
#define FBL_FTM0_BASE         0x40038000ul            /**< Flexible Timer Module 0 base address    */
#define FBL_FTM1_BASE         0x40039000ul            /**< Flexible Timer Module 1 base address    */
#define FBL_FTM2_BASE         0x4003A000ul            /**< Flexible Timer Module 2 base address    */
#define FBL_FTM3_BASE         0x40026000ul            /**< Flexible Timer Module 3 base address    */
#define FBL_PCC_BASE          0x40065000ul            /**< Peripheral Clock Control base address   */
#define FBL_SIM_BASE          0x40048000ul            /**< System Integration Module base address  */
#define FBL_GPIO_BASE         0x400FF000ul            /**< GPIO base address                       */
#define FBL_WDOG_BASE         0x40052000ul            /**< Watchdog Timer base address             */
#define FBL_SCS_BASE          0xE000E000ul            /**< System Control Space base address       */
#define FBL_SFR_BASE_ADRESSES_PRECONFIGURED
#define C_PROCESSOR_S32K148
#define C_PROCESSOR_S32K144
/* polyspace:end < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
/* FblHal_Generic ****************************************************************************************************/

#endif /* __FBL_HAL_H__ */

