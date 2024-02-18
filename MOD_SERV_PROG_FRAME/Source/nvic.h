/*================================================================================================*/
/**
*   @file    nvic.h
*   @version 1.0.1
*
*   @brief   Integration Framework - header file for NVIC driver
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


#ifndef NVIC_H
#define NVIC_H

#ifdef __cplusplus
extern "C"
{
#endif

/*==================================================================================================
*                                         INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
/* polyspace:begin < MISRA-C3:20.1 : Not a defect : Justify with annotations> does not affect the functionality */
#include "Platform_Types.h"
#include "Std_Types.h"
/* polyspace:end < MISRA-C3:20.1 : Not a defect : Justify with annotations> does not affect the functionality */
/*==================================================================================================
*                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/

/*==================================================================================================
*                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
#define NVIC_BASEADDR 0xE000E100
/* polyspace:begin < MISRA-C3:D4.9 : Not a defect : Justify with annotations > This macro is used to facilitate an easy adaptation */
#define NVIC_ISER_OFFSET(id) (uint8)((id >> 5) << 2)
#define NVIC_ICER_OFFSET(id) (0x80 + (uint8)((id >> 5) << 2))
#define NVIC_IPRO_OFFSET(id) (0x300 + (uint8)((id >> 2) << 2))
#define NVIC_IPRO_MASK(id) (uint32)(0xFF << ((id % 4)*8))
/* polyspace:end < MISRA-C3:D4.9 : Not a defect : Justify with annotations > This macro is used to facilitate an easy adaptation */

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/
typedef enum NVIC_interrptId {
    NVIC_DMA_CH0TX_COMPLETE = 0u,
    NVIC_DMA_CH1TX_COMPLETE,    /* 1 */
    NVIC_DMA_CH2TX_COMPLETE,    /* 2 */
    NVIC_DMA_CH3TX_COMPLETE,    /* 3 */
    NVIC_DMA_CH4TX_COMPLETE,    /* 4 */
    NVIC_DMA_CH5TX_COMPLETE,    /* 5 */
    NVIC_DMA_CH6TX_COMPLETE,    /* 6 */
    NVIC_DMA_CH7TX_COMPLETE,    /* 7 */
    NVIC_DMA_CH8TX_COMPLETE,    /* 8 */
    NVIC_DMA_CH9TX_COMPLETE,    /* 9 */
    NVIC_DMA_CH10TX_COMPLETE,   /* 10 */
    NVIC_DMA_CH11TX_COMPLETE,   /* 11 */
    NVIC_DMA_CH12TX_COMPLETE,   /* 12 */
    NVIC_DMA_CH13TX_COMPLETE,   /* 13 */
    NVIC_DMA_CH14TX_COMPLETE,   /* 14 */
    NVIC_DMA_CH15TX_COMPLETE,   /* 15 */
    NVIC_DMA_ERR_CH0_CH15,
    /* ..... */
    NVIC_LPUART0_INT = 31,      /* TX, RX, ERR, OVR Interrupts */
    NVIC_LPUART1_INT = 33,      /* TX, RX, ERR, OVR Interrupts */
    NVIC_LPUART2_INT = 35,      /* TX, RX, ERR, OVR Interrupts */
    NVIC_ADC0_INT_REQ = 39u,
    NVIC_ADC1_INT_REQ = 40u,
    /* ..... */
    NVIC_LPTIMER = 58u,
    NVIC_PORTA_INT = 59u,
    NVIC_PORTB_INT,             /* 60 */
    NVIC_PORTC_INT,             /* 61 */
    NVIC_PORTD_INT,             /* 62 */
    NVIC_PORTE_INT,             /* 63 */
    /* ..... */
    NVIC_CAN0_BUSOFF = 78u,     /* BusOff, BusOff Done, TEC becomes >= 96, REC becomes >= 96, Tx Wrn, Rx Wrn */
    NVIC_CAN0_ERR,              /* 79 - CAN bus error or CAN bus error in fast bit rate in CANFD  */
    NVIC_CAN0_PRETENDED_NTW,    /* 80 - When pretended network is enabled and a valid Rx received or no reception for a given time */
    NVIC_CAN0_MSGBUFF_0_15,     /* 81 */
    NVIC_CAN0_MSGBUFF_16_31,    /* 82 */
    NVIC_CAN0_MSGBUFF_32_47,    /* 83 */
    NVIC_CAN0_MSGBUFF_48_63,    /* 84 */
    NVIC_CAN1_BUSOFF,           /* 85 - BusOff, BusOff Done, TEC becomes >= 96, REC becomes >= 96, Tx Wrn, Rx Wrn */
    NVIC_CAN1_ERR,              /* 86 - CAN bus error or CAN bus error in fast bit rate in CANFD  */
    NVIC_CAN1_MSGBUFF_0_15 = 88u,
    NVIC_CAN1_MSGBUFF_16_31,    /* 89 */
    NVIC_CAN1_MSGBUFF_32_47,    /* 90 */
    NVIC_CAN1_MSGBUFF_48_63,    /* 91 */
    NVIC_CAN2_BUSOFF,           /* 92 - BusOff, BusOff Done, TEC becomes >= 96, REC becomes >= 96, Tx Wrn, Rx Wrn */
    NVIC_CAN2_ERR,              /* 93 - CAN bus error or CAN bus error in fast bit rate in CANFD  */
    NVIC_CAN2_MSGBUFF_0_15 = 95u,
    NVIC_CAN2_MSGBUFF_16_31,    /* 96 */
    /* ..... */
    NVIC_FTM0_CH0CH1 = 99u,
    NVIC_FTM0_CH2CH3,           /* 100 */
    /* ..... */
    NVIC_ECC_ERR_EEERAM = 152u,
    NVIC_ECC_ERR_MGATE,         /* 153 */
    NVIC_NR_OF_IDS = 156u
}NVIC_interrptIdType;


/*==================================================================================================
*                                     FUNCTION PROTOTYPES
==================================================================================================*/

void NVIC_SetPriorityGrouping(uint32 PriorityGroup);
/* polyspace < MISRA-C3:8.5 : Not a defect : Justify with annotations > Function is declared once here. */
void NVIC_EnableIRQ(uint8 IRQn);
/* polyspace < MISRA-C3:8.5 : Not a defect : Justify with annotations > Function is declared once here. */
void NVIC_DisableIRQ(uint8 IRQn);
void NVIC_SetPriority(uint8 IRQn, uint8 priority);


#ifdef __cplusplus
}
#endif

#endif /*NVIC_H*/
