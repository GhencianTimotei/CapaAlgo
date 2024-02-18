/*==================================================================================================
*   @file    Vector_core_iar.s
*   @version 1.0.1
*
*   @brief   Integration Framework - Intrerrupt vector definition for ARM (for IAR).
*   @details Intrerrupt vector definition for ARM (for IAR).
*     
*    (c) Copyright 2006-2016 Freescale Semiconductor, Inc. 
*       Copyright 2017-2018 NXP
*    All Rights Reserved.
*
*    This file contains sample code only. It is not part of the production code deliverables.
*/       
/*=================================================================================================
*    Platform      :      ARM
*    Build Version :      S32K14x_MCAL_1_0_1_RTM_ASR_REL_4_3_REV_0001_20190620
*
==================================================================================================*/
/*==================================================================================================
====================================================================================================*/
    
    MODULE vector_core.s

    SECTION .intc_vector : DATA (2)


    EXTERN undefined_handler
    PUBLIC VTABLE
    EXTERN _Stack_main_start              /* Top of Stack for Initial Stack Pointer */
    EXTERN Reset_Handler             /* Reset Handler */
    EXTERN NMI_Handler               /* NMI Handler */
    EXTERN HardFault_Handler         /* Hard Fault Handler */
    EXTERN MemManage_Handler         /* Reserved */
    EXTERN BusFault_Handler          /* Bus Fault Handler */
    EXTERN UsageFault_Handler        /* Usage Fault Handler */
    EXTERN SVC_Handler               /* SVCall Handler */
    EXTERN DebugMon_Handler          /* Debug Monitor Handler */
    EXTERN PendSV_Handler            /* PendSV Handler */
    EXTERN Os_ISR_Tick           	 /* SysTick Handler */ /* 15*/
    EXTERN CanBusOffIsr_0
    EXTERN CanMailboxIsr_0
    EXTERN Adc_Adc12bsarv2_EndGroupConvUnit0
    EXTERN ICU_PORT_CI_C_EXT_IRQ_ISR
    EXTERN ICU_PORT_CI_E_EXT_IRQ_ISR
    EXTERN FTM_0_CH_0_CH_1_ISR
    EXTERN LPIT_0_CH_0_ISR           /* Wdg Trigger */
    EXTERN Gpt_LPTIMR_ISR
    EXTERN LPUART0_RxTx_IRQHandler
    
VTABLE
    DCD _Stack_main_start              /* Top of Stack for Initial Stack Pointer */
    DCD Reset_Handler             /* Reset Handler */
    DCD NMI_Handler               /* NMI Handler */
    DCD HardFault_Handler         /* Hard Fault Handler */
    DCD MemManage_Handler         /* Reserved */
    DCD BusFault_Handler          /* Bus Fault Handler */
    DCD UsageFault_Handler        /* Usage Fault Handler */
    DCD 0                         /* Reserved */
    DCD 0                         /* Reserved */
    DCD 0                         /* Reserved */
    DCD 0                         /* Reserved */
    DCD SVC_Handler               /* SVCall Handler */
    DCD DebugMon_Handler          /* Debug Monitor Handler */
    DCD 0                         /* Reserved */
    DCD PendSV_Handler            /* PendSV Handler */
    DCD Os_ISR_Tick	              /* SysTick Handler */ /* 15*/
    
    DCD undefined_handler  /*0*/
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler /*10*/
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler 
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler /*20*/
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler 
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler /*30*/
    DCD LPUART0_RxTx_IRQHandler /*31*/
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD Adc_Adc12bsarv2_EndGroupConvUnit0 /*39*/
    DCD undefined_handler /*40*/
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    
    /* External interrupts */
    DCD LPIT_0_CH_0_ISR /*48*/
    DCD undefined_handler
    DCD undefined_handler /*50*/
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler /*55*/
    DCD undefined_handler
    DCD undefined_handler
    DCD Gpt_LPTIMR_ISR
    DCD undefined_handler
    DCD undefined_handler
    DCD ICU_PORT_CI_C_EXT_IRQ_ISR /*61*/
    DCD undefined_handler
    DCD ICU_PORT_CI_E_EXT_IRQ_ISR /*63*/
    DCD undefined_handler
    
    /* External interrupts */
    DCD undefined_handler 
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD CanBusOffIsr_0
    DCD CanBusOffIsr_0

    /* External interrupts */
    DCD CanBusOffIsr_0 /*80*/
    DCD CanMailboxIsr_0
    DCD CanMailboxIsr_0
    DCD CanMailboxIsr_0
    DCD CanMailboxIsr_0
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler

    /* External interrupts */
    DCD undefined_handler /*96*/
    DCD undefined_handler
    DCD undefined_handler
    DCD FTM_0_CH_0_CH_1_ISR
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    
    /* External interrupts */
    DCD undefined_handler /*112*/
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    
    /* External interrupts */
    DCD undefined_handler /*112*/
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    
    /* External interrupts */
    DCD undefined_handler /*128*/
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    
    /* External interrupts */
    DCD undefined_handler /*144*/
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    
    /* External interrupts */
    DCD undefined_handler /*160*/
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    
    /* External interrupts */
    DCD undefined_handler /*176*/
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    
    /* External interrupts */
    DCD undefined_handler /*192/
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    
    /* External interrupts */
    DCD undefined_handler /*208/
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler
    DCD undefined_handler /*223*/

   
  /*  VTABLE DS8 .-VTABLE */
    
    END
