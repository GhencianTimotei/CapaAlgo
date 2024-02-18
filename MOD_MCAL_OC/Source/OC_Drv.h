/*
 ******************************************************************************
 * \image html "Kopf_oZusatz_A4hoch_4C.jpg"
 *
 * \par Module Owner:
 *   Huf H&uuml;lsbeck & F&uuml;rst GmbH & Co. KG \n
 *   Steeger Str. 17 \n
 *   42551 Velbert \n
 *   Department PDE-S
 *
 ******************************************************************************
 * \par Description:
 *
 * %PCMS_HEADER_SUBSTITUTION_START:% 
 ******************************************************************************
 * Document Management Information Log (generated by Dimensions CM)
 * 
 *
 *  CM Item:	%PID:%  
 *	Itemname:	%PM:%		
 *  Location:	%ARCHIVE:%
 *  Revision:	%PR:%
 *  Date:		%DATE:%
 *  Author:		%AUTHOR:%
 *
 * %PCMS_HEADER_SUBSTITUTION_END:%
 *
 ******************************************************************************/

#ifndef OC_DRV_H_							/* To avoid double inclusion */
#define OC_DRV_H_

#include "OC_Types.h"
#include "Platform_Types.h"
#include "S32K144.h"

#define OC_PIN_HIGH 1U
#define OC_PIN_LOW 0U
#define PORT_C3_GPIO_ALT 1U
#define PORT_C3_LPUART_ALT 4U
#define OC_SHORT_VDD_REFERENCE 38U
#ifndef NULL
   #define NULL 0U
#endif

/* LPUART module features */

/* @brief Has extended data register ED. */
#define FEATURE_LPUART_HAS_EXTENDED_DATA_REGISTER_FLAGS (1)
/* @brief Hardware flow control (RTS, CTS) is supported. */
#define FEATURE_LPUART_HAS_MODEM_SUPPORT (1)
/* @brief Baud rate oversampling is available. */
#define FEATURE_LPUART_HAS_BAUD_RATE_OVER_SAMPLING_SUPPORT (1)
/* @brief Baud rate oversampling is available. */
#define FEATURE_LPUART_HAS_BOTH_EDGE_SAMPLING_SUPPORT (1)
/* @brief Capacity (number of entries) of the transmit/receive FIFO (or zero if no FIFO is available). */
#define FEATURE_LPUART_FIFO_SIZE (4U)
/* @brief Supports two match addresses to filter incoming frames. */
#define FEATURE_LPUART_HAS_ADDRESS_MATCHING (1)
/* @brief Has transmitter/receiver DMA enable bits. */
#define FEATURE_LPUART_HAS_DMA_ENABLE (1)
/* @brief Flag clearance mask for STAT register. */
#define FEATURE_LPUART_STAT_REG_FLAGS_MASK (0xC01FC000U)
/* @brief Flag clearance mask for FIFO register. */
#define FEATURE_LPUART_FIFO_REG_FLAGS_MASK (0x00030000U)
/* @brief Reset mask for FIFO register. */
#define FEATURE_LPUART_FIFO_RESET_MASK (0x0003C000U)
/* @brief Default oversampling ratio. */
#define FEATURE_LPUART_DEFAULT_OSR (0x0FUL)
/* @brief Default baud rate modulo divisor. */
#define FEATURE_LPUART_DEFAULT_SBR (0x04UL)
/* @brief Clock names for LPUART. */
#define LPUART_CLOCK_NAMES {LPUART0_CLK, LPUART1_CLK}

#define OC_SHORT_CIRCUIT_VALIDITY_IN_MS_U16                     ((U16)1000)


/* polyspace:begin<MISRA-C3:D4.9 : Not a defect : Justify with annotations > Used for interface decoupling. */

/* Software timer interfaces decoupling */
#define OC_DRV_START_INTERVAL_SW_TIMER(Timer, TimerVal_ms)      timer_sw_start((Timer), SW_TIME_MS(TimerVal_ms))

#define OC_DRV_STOP_INTERVAL_SW_TIMER(Timer)                    timer_sw_stop((Timer))

#define OC_SHORT_CIRCUIT_VALIDITY_TIMER_U8                      ((U8)E_OC_SHORT_CIRCUIT_VALIDITY_TIMER)

/* polyspace:end<MISRA-C3:D4.9 : Not a defect : Justify with annotations > Used for interface decoupling. */

typedef enum
{
   OC_RET_ERR_E = 0U,
   OC_RET_OK_E = 1U,
   OC_RET_BUSY_E = 2U
} OC_RET_EN_TYPE;

typedef enum
{
   OC_OUT_LPUART_EN = 0U,
   OC_OUT_GPIO_EN = 1U,
   OC_OUT_DISABLED_EN = 2U,
   OC_OUT_UNINITIALIZED_EN = 3U
}  OC_OUTPUT_MODE_EN_TYPE;


/* -------------------------------------------------- */
/* ------- Exported functions prototypes ------------ */
/* -------------------------------------------------- */

void LPUART0_RxTx_IRQHandler(void);

extern void OC_Drv_Init_V(void);

extern void OC_Drv_EndBinaryTranmission_V(void);

extern void LPIT0_Channel3Setup(U32 A_Timer_Duration_U32);

extern OC_OUTPUT_MODE_EN_TYPE OC_Drv_SetOCMode_EN(OC_MODE_EN_TYPE A_Op_Mode_EN);

extern OC_RET_EN_TYPE OC_Drv_sendSignalBinary_EN(U32 A_Timer_Duration_U32);

extern OC_RET_EN_TYPE OC_Drv_sendSignalData_EN(U8 *A_SignalData_PU8, U8 A_DataSize_U8);

extern OC_RET_EN_TYPE OC_Drv_getStatus_EN(void);

extern OC_OUTPUT_MODE_EN_TYPE OC_Drv_getOpMode_EN(void);

extern OC_RET_EN_TYPE OC_Drv_StartTx_EN(void);

extern OC_RET_EN_TYPE OC_Drv_stopTx_EN(void);

extern void OC_Drv_InitShortCircuitDetection_V(void);

extern void OC_Drv_startShortCircuitDetection_V(void);

extern void OC_Drv_stopShortCircuitDetection_V(void);

extern BOOL OC_Drv_getShortCircuitDetected_BO(void);

extern void OC_Drv_ShortCircuit_FlexTimerCallout(void);

extern void OC_Drv_SetEndOfTransmissionCallback(void (*A_TxFinishedCallout_PFUNC)(void));

extern void CMP0_IRQHandler(void);



#endif /* OC_DRV */

/* %PCMS_HEADER_SUBSTITUTION_START:%
 ******************************************************************************
 * Document Management Information Log (generated by Dimensions CM)
 *
 *  Description:
 *  %PD:%
 *
 *  Used by Baselines:
 *  %PIRB:%
 *
 *  Used by Dimensions CM Projects:
 *  %PIRW:%
 *
 *  Change History:
 *  %PL:%
 *
 * %PCMS_HEADER_SUBSTITUTION_END:%
 */