/*
 * Appl_Custom_ISO_TP.h
 *
 *  Created on: Jan 19, 2022
 *      Author: lmilita
 */

#ifndef MOD_APPL_CUSTOM_ISO_TP_SOURCE_APPL_CUSTOM_ISO_TP_H_
#define MOD_APPL_CUSTOM_ISO_TP_SOURCE_APPL_CUSTOM_ISO_TP_H_

#define SWR_1084_CHECK_RX_MULTIFRAME_CONSECUTVE_FEATURE     TRUE

/* polyspace < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
#define MAX_UINT16    0xFFFFu

/* polyspace:begin<MISRA-C3:D4.9: Not a defect : Justify with annotations > Using macro like function is faster. No risk.*/
/* polyspace:begin<MISRA-C3:D4.6: Not a defect : Justify with annotations > Investigated. No risk.*/
/* polyspace+3 MISRA-C3:2.5 [Justified:Low] "Macro should be kept for future usage" */
#define INVERT_AND_CAST_TO_U32(X) (U32)(0xFFFFFFFF & (~((unsigned int)(X))))
#define INVERT_AND_CAST_TO_U16(X) (U16)(0xFFFF     & (~((unsigned int)(X))))
#define INVERT_AND_CAST_TO_U8(X)   (U8)(0xFFu       & (~((unsigned int)(X))))
/* polyspace:end<MISRA-C3:D4.9: Not a defect :  Justify with annotations >  */
/* polyspace:end<MISRA-C3:D4.6: Not a defect :  Justify with annotations >  */


#ifdef APP_ISO_TP_C
/* polyspace+2 MISRA-C3:10.6 [Justified:Low] "there are no signed values" */
/* polyspace+3 MISRA-C3:10.3 [Justified:Low] "there are no signed values" */
#define APP_ISO_TP_MAX_VALUE_FOR_ROUTING_ARRAY_U16    (U16)320U  /* 5 * 64 = 320bytes */
#define APP_ISO_TP_HEADER_LENGTH_FOR_ALL_5_FRAMES            6U  /* FF PCI byte + FF DL byte + 4*CF PCI/SN byte  = 6 bytes */
#define APP_ISO_TP_PADDING_VALUE_U8                   (U8)0xAAU  /* Implementation of SWR_1057 */

#define APP_ISO_TP_CAN_FD_FRAME_LENGTH_IN_BYTES_U8          64U

#define APP_ISO_TP_TIMER_VAL_FOR_1_SECOND_U32       (U32)1000U    /*  Value in milliseconds */
#define APP_ISO_TP_PCI_VALUE_FOR_SINGLE_FRAME_U8         0x00U
#define APP_ISO_TP_PCI_VALUE_FOR_FIRST_FRAME_U8          0x01U
#define APP_ISO_TP_PCI_VALUE_FOR_CONSECUTIVE_FRAME_U8    0x02U
#define APP_ISO_TP_CANTP_MESSAGE_HEADER_LENGTH_U8           2U
#define APP_ISO_TP_LOWER_NIBLE_MASK_U8                   0x0FU
#define APP_ISO_TP_NIBLE_SHIFT_BITS_U8                      4U
#define APP_ISO_TP_BYTE_SHIFT_BITS_U8                       8U

#define APP_ISO_TP_RX_SF_PCI_BYTE_OFFSET_U8           0U
#define APP_ISO_TP_RX_SF_DL_BYTE_OFFSET_U8            1U
#define APP_ISO_TP_RX_SF_START_DATA_BYTE_OFFSET_U8    2U

/* polyspace+26 MISRA-C3:2.5 [Justified:Low] "Macro should be kept for future usage" */
#define APP_ISO_TP_RX_FF_PCI_BYTE_OFFSET_U8           0U
#define APP_ISO_TP_RX_FF_PCI_MASK_U8               0xF0U
#define APP_ISO_TP_RX_FF_DL_MASK_U8                0x0FU
#define APP_ISO_TP_RX_FF_DL_BYTE_OFFSET_U8            1U
#define APP_ISO_TP_RX_FF_START_DATA_BYTE_OFFSET_U8    2U

#define APP_ISO_TP_RX_CF_PCI_SN_BYTE_OFFSET_U8        0U
#define APP_ISO_TP_RX_CF_START_DATA_BYTE_OFFSET_U8    1U
#define APP_ISO_TP_RX_CF_SN_MASK_U8                0x0FU
#define APP_ISO_TP_RX_CF_PCI_MASK_U8               0xF0U


#define APP_ISO_TP_TX_SF_PCI_BYTE_OFFSET_U8           0U
#define APP_ISO_TP_TX_SF_DL_BYTE_OFFSET_U8            1U
#define APP_ISO_TP_TX_SF_START_DATA_BYTE_OFFSET_U8    2U

#define APP_ISO_TP_TX_FF_PCI_BYTE_OFFSET_U8           0U
#define APP_ISO_TP_TX_FF_PCI_MASK_U8               0xF0U
#define APP_ISO_TP_TX_FF_DL_MASK_U8                0x0FU
#define APP_ISO_TP_TX_FF_DL_BYTE_OFFSET_U8            1U
#define APP_ISO_TP_TX_FF_START_DATA_BYTE_OFFSET_U8    2U

#define APP_ISO_TP_TX_CF_PCI_SN_BYTE_OFFSET_U8        0U
#define APP_ISO_TP_TX_CF_START_DATA_BYTE_OFFSET_U8    1U
#define APP_ISO_TP_TX_CF_SN_MASK_U8                0x0FU
#define APP_ISO_TP_TX_CF_PCI_MASK_U8               0xF0U


/**************************************************************************************************************************/

#define APP_ISO_TP_TX_FRAME_MKEntFT_FBS_01          0U
#define APP_ISO_TP_TX_FRAME_MKEntFT_FBS_02          1U
#define APP_ISO_TP_TX_FRAME_MKEntFT_FBS_03          2U
#define APP_ISO_TP_TX_FRAME_MKEntFT_FBS_04          3U
#define APP_ISO_TP_TX_FRAME_MKEntFT_FBS_05          4U
#define APP_ISO_TP_TX_FRAME_MAX                     5U

typedef U8 APP_ISO_TP_TX_FRAMES_VALUES_TYPE;
typedef U8 APP_ISO_TP_RX_FRAMES_VALUES_TYPE;

#define APP_ISO_TP_NO_RX_FRAME                      0U
#define APP_ISO_TP_RX_FRAME_FBS_MKEntFT_01          1U
#define APP_ISO_TP_RX_FRAME_FBS_MKEntFT_02          2U
#define APP_ISO_TP_RX_FRAME_FBS_MKEntFT_03          3U
#define APP_ISO_TP_RX_FRAME_FBS_MKEntFT_04          4U
#define APP_ISO_TP_RX_FRAME_FBS_MKEntFT_05          5U

#endif /* APP_ISO_TP_C */

typedef enum{
   APP_ISO_TP_COMM_LINE_FREE_E = 0u,
   APP_ISO_TP_COMM_ONGOING_E
}APP_ISO_TP_TX_COMM_LINE_STATUS_ENUM_TYPE;

/**************************************************************************************************************************/
/* Function exported to be called each 5ms in OS STUBS task */
extern void AppIsoTp_MainPeriodicTask(void);
/* This function will be used to build the CAN FD message to be sent to the higher level ECU */
extern APP_ISO_TP_TX_COMM_LINE_STATUS_ENUM_TYPE AppIsoTp_SetTransmitData(const U8 * const DataAddress_CPCU8, U16 DataLength_U16);
/* This function will be used to notify the NFC App when data is received from FBS function */
extern BOOL AppIsoTp_GetNewDataReceivedFromCan(U8 **const DataAddress_CPPU8, U16 *const DataLengthAddress_CPU16);
/* Callback for NFC App to inform Custom ISO TP when a new NFC is detected */
#if(SWR_1084_CHECK_RX_MULTIFRAME_CONSECUTVE_FEATURE != FALSE)
extern void AppIsoTp_ResetMultiframeReceiveProcedure(void);
#endif
/**************************************************************************************************************************/


#endif /* MOD_APPL_CUSTOM_ISO_TP_SOURCE_APPL_CUSTOM_ISO_TP_H_ */
