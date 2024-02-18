/*!
 * \defgroup <sensor_diag.c>
 * \{
 ******************************************************************************
 * \image html ""
 *
 * \par Module Owner:
 *   Huf H&uuml;lsbeck & F&uuml;rst GmbH & Co. KG \n
 *   Steeger Str. 17 \n
 *   42551 Velbert \n
 *   Department PDE-S
 *
 * \par Initial Project:
 *   1508.008_380_ODH
 *
 ******************************************************************************
 * \par Description:
 * during develepement time(rain / EMC tests)   a sensor data (filter result, threshold, raw data, touch state....)will be send over UART interafce to the HUF monitor for later analyse with the tools matlab
 * the UART communication is based on Software UART, the communication speed is to configure with the define BAUDRATE (38Kb or 115100kb)
 * and the controller pin is to configure with the define RS232_PIN.
 ******************************************************************************
 *
 *  $Workfile:   sensor_diag.c  $
 *  $Revision:   1.8  $
 *  $Date:   Nov 30 2018 14:07:12  $
 *  $Author:   ybadal  $
 *
 ******************************************************************************
 * Change history:
 * see PVCS History at the end of the file
 ******************************************************************************
 *
 * \par Purpose:
 *    i.e Operating System, Service Layer
 *
 * \par Compiler:
 *    ANSI
 *
 * \par Controller:
 *    independant
 *
 * \par Resources:
 *    | Resource      | Amount    | Remarks     |
 *    | ------------- | --------: | ----------- |
 *    | ROM           |  X Byte   |             |
 *    | RAM           |  X Byte   |             |
 *    | EEPROM        |  X Byte   |             |
 *    | Runtime Init  |    X ms   |             |
 *    | Runtime Task  |    X ms   |             |
 *
 * \par Quality:
 *    | Factor            | Excl  | Good  | Fair  | Poor  |
 *    | ----------------- | ----: | ----: | ----: | ----: |
 *    | _Maintainability_ |   0 % |   0 % |   0 % |   0 % |
 *    | Analyzability     |   0 % |   0 % |   0 % |   0 % |
 *    | Changeability     |   0 % |   0 % |   0 % |   0 % |
 *    | Stability         |   0 % |   0 % |   0 % |   0 % |
 *    | Testability       |   0 % |   0 % |   0 % |   0 % |
 *
 * \par MISRA rules violations:
 *     \li none(?)
 *
 ******************************************************************************
 *
 * \attention
 *   \li text for Information, to do ..
 *
 ******************************************************************************/
#ifndef SENSOR_DIAG_C
#define SENSOR_DIAG_C

#include "Platform_Types.h"          /* Standard include files */
#include "sensor_mcvd.h"
#include "sensor_sequencer.h"
#include "sensor_aquisition.h"
#include "sensor_algo.h"
#include "Os.h"
#include "sensor_diag.h"
#include "LDC3114.h"
#include "inductive_sensor_algo.h"
#include "sensor_acquisition_mcvd.h"
#include "config.h"
#include "OC_drv.h"
#include "Com.h"



#if defined RS232_ON_SENSOR || defined (RS232_ON_NFC) || defined (RS232_ON)

U8 AU8_LDCData[LDC3114_HUF_MONITOR_DIAG_DATA_LENGTH];
SENSOR_DIAG_EXPORT U8 AU8_Array_data_out[43];
U8 U8_indAlg_SM_Ch[2] = {0u, 0u};
U32 U32_indAlg_ThreVal_Ch[2] = {0u, 0u};

SENSOR_DIAG_EXPORT void sensor_diag_data_out_UART (void)
{
    U8 U8_temp_send_byte = 0x00u;
    U8 U8_LDC_Status = 0x00u;
    U8 U8_Index = 0u;

    LDC3114_GetDiagData(&AU8_LDCData[0]);
    Inductive_Algo_ThresholdValue_GetDiagData(&U32_indAlg_ThreVal_Ch[0]);
    Inductive_Algo_SMState_GetDiagData(&U8_indAlg_SM_Ch[0]);
    if((U8)2 == U8_indAlg_SM_Ch[0])
    {
        U8_LDC_Status |= 0x01u;
    }
    else
    {
        U8_LDC_Status &= ~(0x01u);
    }

    if((U8)2 == U8_indAlg_SM_Ch[1])
    {
        U8_LDC_Status |= 0x02u;
    }
    else
    {
        U8_LDC_Status &= ~(0x02u);
    }

        /* Byte 0: Send START */
    U8_temp_send_byte = 0xDAu;
    AU8_Array_data_out[U8_Index++] = U8_temp_send_byte;

    /* Byte 1: High-Byte of RAW-Value for LDC Channel 0  */
    /* LDC test*/
    U8_temp_send_byte = AU8_LDCData[4];
    AU8_Array_data_out[U8_Index++] = U8_temp_send_byte;

    /* Byte 2: Middle-Byte of RAW-Value for LDC Channel 0 */
    /* LDC test*/
    U8_temp_send_byte = AU8_LDCData[3];
    AU8_Array_data_out[U8_Index++] = U8_temp_send_byte;

    /* Byte 3: Low-Byte of RAW-Value for LDC Channel 0 */
    /* LDC test*/
    U8_temp_send_byte = AU8_LDCData[2];
    AU8_Array_data_out[U8_Index++] = U8_temp_send_byte;
    /* Byte 4: High-Byte of RAW-Value for LDC Channel 1 */
    /* LDC test*/
    U8_temp_send_byte = AU8_LDCData[7];
    AU8_Array_data_out[U8_Index++] = U8_temp_send_byte;

    /* Byte 5: Middle-Byte of RAW-Value for LDC Channel 1 */
    /* LDC test*/
    U8_temp_send_byte = AU8_LDCData[6];
    AU8_Array_data_out[U8_Index++] = U8_temp_send_byte;

    /* Byte 6: Low-Byte of RAW-Value for LDC Channel 1 */
    /* LDC test*/
    U8_temp_send_byte = AU8_LDCData[5];
    AU8_Array_data_out[U8_Index++] = U8_temp_send_byte;

    /* Byte 7: High-Byte of Threshold Value for LDC Channel 0 */
    U8_temp_send_byte = (U32_indAlg_ThreVal_Ch[0] >> 16u) & 0xFFu;
    AU8_Array_data_out[U8_Index++] = U8_temp_send_byte;

    /* Byte 8: Middle-Byte of Threshold Value for LDC Channel 0 */
    U8_temp_send_byte = (U32_indAlg_ThreVal_Ch[0] >> 8u) & 0xFFu;
    AU8_Array_data_out[U8_Index++] = U8_temp_send_byte;

    /* Byte 9: Low-Byte of Threshold Value for LDC Channel 0 */
    U8_temp_send_byte = U32_indAlg_ThreVal_Ch[0] & 0xFFu;
    AU8_Array_data_out[U8_Index++] = U8_temp_send_byte;

    /* Byte 10: High-Byte of Threshold Value for LDC Channel 1 */
    U8_temp_send_byte = (U32_indAlg_ThreVal_Ch[1] >> 16u) & 0xFFu;
    AU8_Array_data_out[U8_Index++] = U8_temp_send_byte;

    /* Byte 11: Middle-Byte of Threshold Value for LDC Channel 1 */
    U8_temp_send_byte = (U32_indAlg_ThreVal_Ch[1] >> 8u) & 0xFFu;
    AU8_Array_data_out[U8_Index++] = U8_temp_send_byte;

    /* Byte 12: Low-Byte of Threshold Value for LDC Channel 1 */
    U8_temp_send_byte = U32_indAlg_ThreVal_Ch[1] & 0xFFu;
    AU8_Array_data_out[U8_Index++] = U8_temp_send_byte;

    /* Byte 13: CH0 State */
    U8_temp_send_byte = U8_indAlg_SM_Ch[0];
    AU8_Array_data_out[U8_Index++] = U8_temp_send_byte;

    /* Byte 14: CH1 State */
    U8_temp_send_byte = U8_indAlg_SM_Ch[1];
    AU8_Array_data_out[U8_Index++] = U8_temp_send_byte;

    /* Byte 15: High-Byte of Sample A raw Value Unlock Sensor */
    U8_temp_send_byte= S_UnlockRaw_ASM.U16_Sensor_SA_Value >> 8u;
    AU8_Array_data_out[U8_Index++] = U8_temp_send_byte;

    /* Byte 16: Low-Byte of Sample A raw Value Unlock Sensor */
    U8_temp_send_byte= S_UnlockRaw_ASM.U16_Sensor_SA_Value & 0xFFu;
    AU8_Array_data_out[U8_Index++] = U8_temp_send_byte;

    /* Byte 17: High-Byte of Sample B raw Value Unlock Sensor */
    U8_temp_send_byte= S_UnlockRaw_ASM.U16_Sensor_SB_Value >> 8u;
    AU8_Array_data_out[U8_Index++] = U8_temp_send_byte;

    /* Byte 18: Low-Byte of Sample B raw Value Unlock Sensor */
    U8_temp_send_byte= S_UnlockRaw_ASM.U16_Sensor_SB_Value & 0xFF;
    AU8_Array_data_out[U8_Index++] = U8_temp_send_byte;

    /* Byte 19: High-Byte filter input Unlock Sensor*/
    U8_temp_send_byte = U16_ER_filter_dfc >> 8u;
    AU8_Array_data_out[U8_Index++] = U8_temp_send_byte;

    /* Byte 20: Low-Byte filter input Unlock Sensor */
    U8_temp_send_byte = U16_ER_filter_dfc & 0xFFu;
    AU8_Array_data_out[U8_Index++] = U8_temp_send_byte;

    /* Byte 21: High-Byte filter output Unlock Sensor */
    U8_temp_send_byte = U16_ER_MeasValue >> 8u;
    AU8_Array_data_out[U8_Index++] = U8_temp_send_byte;

    /* Byte 22: Low-Byte filter output Unlock Sensor */
    U8_temp_send_byte = U16_ER_MeasValue & 0xFF;
    AU8_Array_data_out[U8_Index++] = U8_temp_send_byte;

    /* Byte 23:  High-Byte Threshold Unlock Sensor */
    U8_temp_send_byte = U16_ER_Twert >> 8u;
    AU8_Array_data_out[U8_Index++] = U8_temp_send_byte;

    /* Byte 24: Low-Byte Threshold Unlock Sensor */
    U8_temp_send_byte = U16_ER_Twert & 0xFFu;
    AU8_Array_data_out[U8_Index++] = U8_temp_send_byte;

    /* Byte 25: Algo State Unlock Sensor */
    get_sensor_algo_state_result(&U8_temp_send_byte);
    U8_temp_send_byte = (U8_temp_send_byte & 0x03u);
    AU8_Array_data_out[U8_Index++] = U8_temp_send_byte;

    /* Byte 26: Noise Flag Unlock Sensor */
    U8_temp_send_byte = 0x00;
    if (1 == Sensor_Bits.ER_Noiseflag_u1)
    {
        U8_temp_send_byte = 0x01u;
    }
    AU8_Array_data_out[U8_Index++] = U8_temp_send_byte;

    /* Byte 27: High-Byte of Sample A raw Value Lock Sensor */
    U8_temp_send_byte= S_LockRaw_ASM.U16_Sensor_SA_Value >> 8u;
    AU8_Array_data_out[U8_Index++] = U8_temp_send_byte;

    /* Byte 28: Low-Byte of Sample A raw Value Lock Sensor */
    U8_temp_send_byte= S_LockRaw_ASM.U16_Sensor_SA_Value & 0xFFu;
    AU8_Array_data_out[U8_Index++] = U8_temp_send_byte;

    /* Byte 29: High-Byte of Sample B raw Value Lock Sensor */
    U8_temp_send_byte= S_LockRaw_ASM.U16_Sensor_SB_Value >> 8u;
    AU8_Array_data_out[U8_Index++] = U8_temp_send_byte;

    /* Byte 30: Low-Byte of Sample B raw Value Lock Sensor */
    U8_temp_send_byte= S_LockRaw_ASM.U16_Sensor_SB_Value & 0xFF;
    AU8_Array_data_out[U8_Index++] = U8_temp_send_byte;

    /* Byte 31: High-Byte filter input Lock Sensor*/
    U8_temp_send_byte = U16_VR_filter_dfc >> 8u;
    AU8_Array_data_out[U8_Index++] = U8_temp_send_byte;

    /* Byte 32: Low-Byte filter input Lock Sensor */
    U8_temp_send_byte = U16_VR_filter_dfc & 0xFFu;
    AU8_Array_data_out[U8_Index++] = U8_temp_send_byte;

    /* Byte 33: High-Byte filter output Lock Sensor */
    U8_temp_send_byte = U16_VR_MeasValue >> 8u;
    AU8_Array_data_out[U8_Index++] = U8_temp_send_byte;

    /* Byte 34: Low-Byte filter output Lock Sensor */
    U8_temp_send_byte = U16_VR_MeasValue & 0xFFu;
    AU8_Array_data_out[U8_Index++] = U8_temp_send_byte;

    /* Byte 35: High-Byte Threshold Lock Sensor */
    U8_temp_send_byte = U16_VR_Twert >> 8u;
    AU8_Array_data_out[U8_Index++] = U8_temp_send_byte;

    /* Byte 36: Low-Byte Threshold Lock Sensor */
    U8_temp_send_byte = U16_VR_Twert & 0xFFu;
    AU8_Array_data_out[U8_Index++] = U8_temp_send_byte;

    /* Byte 37: Algo State Lock Sensor */
    get_sensor_algo_state_result(&U8_temp_send_byte);
    U8_temp_send_byte = (U8_temp_send_byte & 0x0Cu) >> 2u;
    AU8_Array_data_out[U8_Index++] = U8_temp_send_byte;

    /* Byte 38: Noise Flag Lock Sensor */
    U8_temp_send_byte = 0x00u;
    if (1 == Sensor_Bits.VR_Noiseflag_u1)
    {
        U8_temp_send_byte = 0x01u;
    }
    AU8_Array_data_out[U8_Index++] = U8_temp_send_byte;

    /* Byte 39: Status Register of LDC */
    /* LDC test*/
    U8_temp_send_byte = AU8_LDCData[0];
    AU8_Array_data_out[U8_Index++] = U8_temp_send_byte;

    /* Byte 40: LDC Status */
    /* LDC test*/
    U8_temp_send_byte = U8_LDC_Status;
    AU8_Array_data_out[U8_Index++] = U8_temp_send_byte;

    /* Byte 41: Capa Status */
    /* LDC test*/
    get_sensor_algo_state_result(&U8_temp_send_byte);
    AU8_Array_data_out[U8_Index++] = U8_temp_send_byte;

    /* Send STOP */
    U8_temp_send_byte = 0xDEu;
    AU8_Array_data_out[U8_Index++] = U8_temp_send_byte;

    OC_SignalMng_setSignalFrame_EN(AU8_Array_data_out, U8_Index);
    OC_SignalMng_StartTx_V();
    while (OC_RET_BUSY_E == OC_Drv_getStatus_EN()){};
}

#endif

void NfcDevMsg_SendMessage()
{
    uint8 NfcDevMsg_MessageContent_AU8[64]; 

    NfcDevMsg_MessageContent_AU8[0] = (U8)((Sensor_Var_Str[SENSOR_UNLOCK].U16_last_sampleA) >> 8);
    NfcDevMsg_MessageContent_AU8[1] = (U8)(Sensor_Var_Str[SENSOR_UNLOCK].U16_last_sampleA);
    NfcDevMsg_MessageContent_AU8[2] = (U8)((Sensor_Var_Str[SENSOR_UNLOCK].U16_last_sampleB) >> 8);
    NfcDevMsg_MessageContent_AU8[3] = (U8)(Sensor_Var_Str[SENSOR_UNLOCK].U16_last_sampleB);
    NfcDevMsg_MessageContent_AU8[4] = (U8)(U16_ER_filter_dfc >> 8);
    NfcDevMsg_MessageContent_AU8[5] = (U8)(U16_ER_filter_dfc);
    NfcDevMsg_MessageContent_AU8[6] = (U8)(Sensor_Var_Str[SENSOR_UNLOCK].U16_filter_unit_result >> 8);
    NfcDevMsg_MessageContent_AU8[7] = (U8)(Sensor_Var_Str[SENSOR_UNLOCK].U16_filter_unit_result);
    NfcDevMsg_MessageContent_AU8[8] = (U8)(U16_ER_Twert >> 8);
    ;
    NfcDevMsg_MessageContent_AU8[9] = (U8)(U16_ER_Twert);
    NfcDevMsg_MessageContent_AU8[10] = (U8)EN_ER_AlgoStateSM;
    NfcDevMsg_MessageContent_AU8[11] = (U8)0x00;
    if (Sensor_Bits.ER_Noiseflag_u1 != 0)
    {
        NfcDevMsg_MessageContent_AU8[11] |= (U8)0x01;
    }
    if (Sensor_Bits.VR_Noiseflag_u1 != 0)
    {
        NfcDevMsg_MessageContent_AU8[11] |= (U8)0x02;
    }
    NfcDevMsg_MessageContent_AU8[12] = (U8)((Sensor_Var_Str[SENSOR_LOCK].U16_last_sampleA) >> 8);
    NfcDevMsg_MessageContent_AU8[13] = (U8)(Sensor_Var_Str[SENSOR_LOCK].U16_last_sampleA);
    NfcDevMsg_MessageContent_AU8[14] = (U8)((Sensor_Var_Str[SENSOR_LOCK].U16_last_sampleB) >> 8);
    NfcDevMsg_MessageContent_AU8[15] = (U8)(Sensor_Var_Str[SENSOR_LOCK].U16_last_sampleB);
    NfcDevMsg_MessageContent_AU8[16] = (U8)(U16_VR_filter_dfc >> 8);
    NfcDevMsg_MessageContent_AU8[17] = (U8)(U16_VR_filter_dfc);
    NfcDevMsg_MessageContent_AU8[18] = (U8)(Sensor_Var_Str[SENSOR_LOCK].U16_filter_unit_result >> 8);
    NfcDevMsg_MessageContent_AU8[19] = (U8)(Sensor_Var_Str[SENSOR_LOCK].U16_filter_unit_result);
    NfcDevMsg_MessageContent_AU8[20] = (U8)(U16_VR_Twert >> 8);
    NfcDevMsg_MessageContent_AU8[21] = (U8)(U16_VR_Twert); /* polyspace MISRA-C3:D4.1 [Justified:Unset] "The value of this variable is between 0 and the buffer dimension" */
    NfcDevMsg_MessageContent_AU8[22] = (U8)EN_VR_AlgoStateSM;
    NfcDevMsg_MessageContent_AU8[23] = (U8)(((LDC3114_Sensor_Var_Str[LDC3114_SENSOR_CH0].U32_last_sample)) >> 16);
    NfcDevMsg_MessageContent_AU8[24] = (U8)(((LDC3114_Sensor_Var_Str[LDC3114_SENSOR_CH0].U32_last_sample)) >> 8);
    NfcDevMsg_MessageContent_AU8[25] = (U8)(LDC3114_Sensor_Var_Str[LDC3114_SENSOR_CH0].U32_last_sample);
    NfcDevMsg_MessageContent_AU8[26] = (U8)(((LDC3114_Sensor_Var_Str[LDC3114_SENSOR_CH1].U32_last_sample)) >> 16);
    NfcDevMsg_MessageContent_AU8[27] = (U8)(((LDC3114_Sensor_Var_Str[LDC3114_SENSOR_CH1].U32_last_sample)) >> 8);
    NfcDevMsg_MessageContent_AU8[28] = (U8)(LDC3114_Sensor_Var_Str[LDC3114_SENSOR_CH1].U32_last_sample);
    NfcDevMsg_MessageContent_AU8[29] = (U8)((LDC3114_Sensor_Var_Str[LDC3114_SENSOR_CH0].U32_filter_unit_result) >> 16);
    NfcDevMsg_MessageContent_AU8[30] = (U8)((LDC3114_Sensor_Var_Str[LDC3114_SENSOR_CH0].U32_filter_unit_result) >> 8);
    NfcDevMsg_MessageContent_AU8[31] = (U8)(LDC3114_Sensor_Var_Str[LDC3114_SENSOR_CH0].U32_filter_unit_result);
    NfcDevMsg_MessageContent_AU8[32] = (U8)((LDC3114_Sensor_Var_Str[LDC3114_SENSOR_CH1].U32_filter_unit_result) >> 16);
    NfcDevMsg_MessageContent_AU8[33] = (U8)((LDC3114_Sensor_Var_Str[LDC3114_SENSOR_CH1].U32_filter_unit_result) >> 8);
    NfcDevMsg_MessageContent_AU8[34] = (U8)(LDC3114_Sensor_Var_Str[LDC3114_SENSOR_CH1].U32_filter_unit_result);
    NfcDevMsg_MessageContent_AU8[35] = (U8)((inductive_sensor_param[INDUCTIVE_SENSOR_CH0].FreezeThreshold) >> 16);
    NfcDevMsg_MessageContent_AU8[36] = (U8)((inductive_sensor_param[INDUCTIVE_SENSOR_CH0].FreezeThreshold) >> 8);
    NfcDevMsg_MessageContent_AU8[37] = (U8)(inductive_sensor_param[INDUCTIVE_SENSOR_CH0].FreezeThreshold);
    NfcDevMsg_MessageContent_AU8[38] = (U8)((inductive_sensor_param[INDUCTIVE_SENSOR_CH1].FreezeThreshold) >> 16);
    NfcDevMsg_MessageContent_AU8[39] = (U8)((inductive_sensor_param[INDUCTIVE_SENSOR_CH1].FreezeThreshold) >> 8);
    NfcDevMsg_MessageContent_AU8[40] = (U8)(inductive_sensor_param[INDUCTIVE_SENSOR_CH1].FreezeThreshold);
    NfcDevMsg_MessageContent_AU8[41] = (U8)((inductive_sensor_param[INDUCTIVE_SENSOR_CH0].ThresholdReference) >> 16);
    NfcDevMsg_MessageContent_AU8[42] = (U8)((inductive_sensor_param[INDUCTIVE_SENSOR_CH0].ThresholdReference) >> 8);
    NfcDevMsg_MessageContent_AU8[43] = (U8)(inductive_sensor_param[INDUCTIVE_SENSOR_CH0].ThresholdReference);
    NfcDevMsg_MessageContent_AU8[44] = (U8)((inductive_sensor_param[INDUCTIVE_SENSOR_CH1].ThresholdReference) >> 16);
    NfcDevMsg_MessageContent_AU8[45] = (U8)((inductive_sensor_param[INDUCTIVE_SENSOR_CH1].ThresholdReference) >> 8);
    NfcDevMsg_MessageContent_AU8[46] = (U8)(inductive_sensor_param[INDUCTIVE_SENSOR_CH1].ThresholdReference);
    NfcDevMsg_MessageContent_AU8[47] = (U8)((Ch0_NoiseMeasVal) >> 8);
    NfcDevMsg_MessageContent_AU8[48] = (U8)(Ch0_NoiseMeasVal);
    NfcDevMsg_MessageContent_AU8[49] = (U8)((Ch1_NoiseMeasVal) >> 8);
    NfcDevMsg_MessageContent_AU8[50] = (U8)(Ch1_NoiseMeasVal);
    /* polyspace+4 MISRA-C3:10.5 [Justified:Low] "cast to u8 is needed in this case" */
    NfcDevMsg_MessageContent_AU8[51] = (U8)(inductive_sensor_param[INDUCTIVE_SENSOR_CH0].AlgoStateSM);
    NfcDevMsg_MessageContent_AU8[52] = (U8)(inductive_sensor_param[INDUCTIVE_SENSOR_CH1].AlgoStateSM);
    NfcDevMsg_MessageContent_AU8[53] = (U8)(LDC3114_Sensor_Var_Str[LDC3114_SENSOR_CH0].BO_noise_detected);
    NfcDevMsg_MessageContent_AU8[54] = (U8)(LDC3114_Sensor_Var_Str[LDC3114_SENSOR_CH1].BO_noise_detected);
    /* polyspace+2 MISRA-C3:12.1 [Justified:Low] "The operations will be done in the standard way" */
    NfcDevMsg_MessageContent_AU8[55] = (U8)(inductive_sensor_param[INDUCTIVE_SENSOR_CH0].FreezeCounter > 0u ? 1u : 0u);
    NfcDevMsg_MessageContent_AU8[56] = (U8)(inductive_sensor_param[INDUCTIVE_SENSOR_CH1].FreezeCounter > 0u ? 1u : 0u);
    NfcDevMsg_MessageContent_AU8[57] = (U8)((inductive_sensor_param[INDUCTIVE_SENSOR_CH0].ThresholdValue) >> 16);
    NfcDevMsg_MessageContent_AU8[58] = (U8)((inductive_sensor_param[INDUCTIVE_SENSOR_CH0].ThresholdValue) >> 8);
    NfcDevMsg_MessageContent_AU8[59] = (U8)(inductive_sensor_param[INDUCTIVE_SENSOR_CH0].ThresholdValue);
    NfcDevMsg_MessageContent_AU8[60] = (U8)((inductive_sensor_param[INDUCTIVE_SENSOR_CH1].ThresholdValue) >> 16);
    NfcDevMsg_MessageContent_AU8[61] = (U8)((inductive_sensor_param[INDUCTIVE_SENSOR_CH1].ThresholdValue) >> 8);
    NfcDevMsg_MessageContent_AU8[62] = (U8)(inductive_sensor_param[INDUCTIVE_SENSOR_CH1].ThresholdValue);
    NfcDevMsg_MessageContent_AU8[63] = LDC3114_getStatusByte();

    (void)Com_SendSignal(ComConf_ComSignal_DEV_NFC_FS_Resp_3F_Data_XIX_DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_56a7f80a_Tx, &NfcDevMsg_MessageContent_AU8[0]);
}
#endif 
/* Automatic logging by PVCS ***********************************************

$Log:   J:/vmfs/VW/1508.008_380_ODH/archives/3_Coding/ECU_NFC_STACK-NXP/MCU_RL78/MOD_SERV_CAPA_SENSOR/MOD_SERV_SENSOR_DIAGNOSE/Source/sensor_diag.c-arc  $
 * 
 *    Rev 1.8   Nov 30 2018 14:07:12   ybadal
 * configure the SW UART Function when TOOL0 is used as debug pin.
 * 
 *    Rev 1.7   Sep 19 2018 16:00:28   ybadal
 * - disable optimization to get the correct SW uart.
 * 
 *    Rev 1.6   Jul 16 2018 14:05:58   ybadal
 * - RS232 Baudrat corrected.
 * - add temperature sensor values output.
 * 
 *    Rev 1.5   18 Apr 2018 12:23:26   sbhanda
 * Unused function NFC_diag_data_out() has been removed.
 * 
 *    Rev 1.4   Feb 16 2018 11:53:52   ybadal
 * - add timer and interrupt irq  for  ram check
 * 
 *    Rev 1.3   Feb 01 2018 09:14:18   cpascal
 * Interfaces from Vector CAN stack called instead of the ones from local CAN stack.
 * 
 *    Rev 1.2   04 Dec 2017 14:22:22   sbhanda
 * CAN signal renamed and NFC debug  functionality aktivated
 * 
 *    Rev 1.1   29 Nov 2017 08:47:28   sbhanda
 * Base for SW release V01.01
 * 
 *    Rev 1.0   Sep 22 2017 16:12:18   Sbhanda
 * Initial revision.
 * 
 *    Rev 1.0   Aug 07 2017 10:28:32   ybadal
 * Initial revision.
 * 
 *    Rev 1.0   Apr 13 2017 13:24:56   ufalkne
 * Initial revision.
 * 
 *    Rev 1.47.1.0   18 Mar 2016 11:24:02   dwippic
 * TT 12314 Lock-Senor deactivated during power save mode 
 * 
 *    Rev 1.47   12 Oct 2015 14:40:50   ybadal
 * bug fixed after review with Jiri Tihelka.
 * 
 *    Rev 1.46   09 Oct 2015 15:51:40   ybadal
 * - bug fix for TT 11278 and 11277.
 * - code comment added.
 * 
 *    Rev 1.45   07 Oct 2015 12:19:14   ybadal
 * a part of code comment is done.
 * 
 *    Rev 1.44   30 Sep 2015 13:59:16   apeschl
 * Short circuit condition on RC1/RC2 within sensor_init corrected
 * 
 *    Rev 1.43   21 Sep 2015 15:17:22   ybadal
 * Rauschanalyse Grenze als Parameter f�r beide Sensoren in der Funktion task_Sensor implementiert.
 * 
 *    Rev 1.42   18 Sep 2015 07:55:52   ybadal
 * New Structure implementiert.(neues messwerk und signal analyse)siehe Prog Info von v04.01
 * 
 *    Rev 1.41   09 Sep 2015 10:57:52   umuelle3
 * MISRA changes proposed by Polyspace.
 * 
 *    Rev 1.40   24 Aug 2015 13:49:46   ybadal
 * SW Change siehe proginfo 24.08.2015
 * 
 *    Rev 1.39   Jul 15 2015 14:50:16   jyomkil
 * Undo changes to avoid the using of pointer for the decimation filter.
 * 
 *    Rev 1.38   Jul 14 2015 16:32:28   jyomkil
 * sensor.c modified to avoid the using of pointer for the filter function.
 * 
 *    Rev 1.37   13 Jul 2015 11:52:56   apeschl
 * Parameter LOCK_ADD_BOUNDARY corrected
 * 
 *    Rev 1.36   08 Jul 2015 08:55:10   ybadal
 * - new Filter implemented in sensor.c.
 * - Variablen f�r Set_ss werden auf absoluten Adressen im Bank0 verlinkt.
 * - bugsfix to Review Punkte mit den Whiteboxtester aus Polen Olejnik, Piotr / Dulski, Mariusz .sehe Exel Datei sensor_algo_V03.03_issues_review.
 * -Oversampling  f�r die Rohr Sensor Messerung implementiert.
 * 
 *    Rev 1.35   10 Jun 2015 09:00:18   ybadal
 * - Powerup Kalibration wurde ersetzt.
 * - weitere Misra Rules gefixt.
 * 
 * 
 *    Rev 1.33   03 Jun 2015 09:45:04   ybadal
 * GPIO Modul eingef�gt.
 * 
 *    Rev 1.32   02 Jun 2015 13:12:12   ybadal
 * Diverse TT Punkte und Review Punkte.
 * 
 *    Rev 1.31   29 May 2015 14:24:40   ybadal
 * - Diverse TT Reviews weiter implementiert.
 * - einige Misra Violation behoben.
 * 
 *    Rev 1.30   28 May 2015 10:52:24   ybadal
 * Huf Guidline SW Coding implementiert.
 * 
 *    Rev 1.29   20 May 2015 16:27:02   ybadal
 * - Diverse Misra Rules behoben.
 * - Abstraction betwenn  sensor aquisition sensor analyse.
 * 
 *    Rev 1.28   19 May 2015 11:31:00   ybadal
 * Misra Rules "Macro 'XX' does not expand to compliant construct. (required)" fixed
 * 
 *    Rev 1.27   13 May 2015 15:19:46   ybadal
 * Bug fix for TT 10412  ,TT 10402 and TT 10397
 * 
 *    Rev 1.26   12 May 2015 15:45:34   ybadal
 *  - MISRA RULES : Assembly language shall be encapsulated and isolated.
 * -Dezimation filter implemented to activate with the Define DECIMATION_FILTER
 * 
 *    Rev 1.25   Mar 06 2015 15:24:04   pclemen
 * appy comments in english without change of binary result
 * 
 *    Rev 1.24   Feb 06 2015 15:40:18   mstei
 * Changes for compliance with CSpec-095 Rev. 01 - Guideline for Software Coding.pdf:
 * - curly brackets are separately positioned in the next line after an instruction. The code between two brackets must be indented.
 * 
 *    Rev 1.23   Feb 06 2015 13:02:46   mstei
 * - added cast to the corresponding type
 * 
 *    Rev 1.22   Feb 02 2015 15:11:38   mstei
 * Naming convention for enums according to CSpec-095 Rev. 01 - Guideline for Software Coding.pdf.
 * 
 *    Rev 1.21   Jan 30 2015 16:40:12   mstei
 * Naming convention for preprocessor defines according to CSpec-095 Rev. 01 - Guideline for Software Coding.pdf
 * 
 *    Rev 1.20   Jan 29 2015 13:07:10   mstei
 * Naming convention for variables. There should no changes in the hex file.
 * 
 *    Rev 1.19   Jan 26 2015 16:42:56   mstei
 * Changes for compliance with CSpec-095 Rev. 01 - Guideline for Software Coding.pdf:
 * - naming convention for variables
 * 
 *    Rev 1.18   Jan 26 2015 16:30:48   mstei
 * Changes for compliance with CSpec-095 Rev. 01 - Guideline for Software Coding.pdf:
 * - comments from C++ were modified to C comments
 * 
 *    Rev 1.17   26 Jan 2015 14:01:26   apeschl
 * Sensorparameter angepasst
 * Sensor_Scan Funktionen angepasst
 * 
 *    Rev 1.16   24 Sep 2014 10:22:10   apeschl
 * RS232 Datenausgabe: Kompilerschalter Fehler behoben
 * 
 *    Rev 1.14   19 Sep 2014 13:15:20   apeschl
 * ER & VR Rauschwert (Addwert) Kalibrierung im laufenden Betrieb hinzu
 * 
 *    Rev 1.13   15 Sep 2014 15:28:58   ybadal
 * Rausch Analyse wird nicht bei ausgel�sten Sensor ausgef�hrt.
 * 
 *    Rev 1.12   11 Sep 2014 15:03:42   ybadal
 * - Bug zum nicht wieder Verlassen des Rausch Modus behoben.
 * - Wechseln zum  Activ Mode wenn der Sensor anf�ngt zu Rauschen.
 * 
 *    Rev 1.11   09 Sep 2014 14:04:54   apeschl
 * Ersetzen bei Interrupt korrigiert
 * Er_noise_counter_lock_u8 & Vr_noise_counter_lock_u8 wird bei RS232_ON global definiert
 * 
 *    Rev 1.10   29 Aug 2014 08:51:42   ybadal
 * Bug fixed for TT  8644  und TT 8913
 * 
 *    Rev 1.9   19 Aug 2014 15:10:28   apeschl
 * RS232 Ausgabe korrigiert.
 * _ADD_BOUNDARY angepasst
 * 
 *    Rev 1.8   17 Jul 2014 10:12:56   ybadal
 * Code Umsetzung zum Review  von 15.07.2014
 * 
 *    Rev 1.7   28 May 2014 09:50:34   apeschl
 * Invertierte Datenausgabe f�r EMV Messungen hinzu.
 * Sensormessung und Berechnung zeitoptimiert.
 * 
 *    Rev 1.5   22 May 2014 16:41:04   ybadal
 * - Bug Fixed for Team Track Error : TT8640 ,TT8623 und TT8621.
 * -72 Hours Low Power Message implementiert.
 * -Power up Message implementiert.
 *
 *    Rev 1.4   12 May 2014 17:15:30   ybadal
 * -VW Kommunication implementiert.
 * - Bug Fix for TT 8621
 *
 *    Rev 1.3   30 Apr 2014 09:03:10   apeschl
 * task_er/vr & Sensor_Scan_VR/ER optimiert
 *
 *    Rev 1.2   24 Apr 2014 11:37:06   ybadal
 * ER Sperrung  aufgehoben.
 *
 *    Rev 1.1   23 Apr 2014 12:15:24   apeschl
 * div. Optimierungen
 * Zeiten ER/VR Sensor angepasst
 *
 *    Rev 1.0   28 Mar 2014 14:10:06   ybadal
 * Initial revision.
 *
 *    Rev 1.7   15 Jan 2014 15:32:02   apeschl
 * Oversampling Spike Detection ER hinzu.
 * Grenzwerte f�r Spizenwerte in EEPROM definiert.
 *
 *    Rev 1.6   07 Jan 2014 12:18:28   ybadal
 * - NFC Karten Erkennung wird �ber eine State Machine durchlaufen.
 * - NFC Antennen Rekalibrierung bei gr�ssen Phasen �nderungen  implementiert.
 * - NFC Part mit dem Compiler Switches "NFC_PART_AKTIV" zu aktivieren.
 *
 *    Rev 1.5   13 Dec 2013 13:44:08   apeschl
 * Einige Defines bereinigt, Spike detection VR hinzu, muss aber noch verifiziert werden.
 *
 *    Rev 1.4   13 Dec 2013 12:48:30   ybadal
 * - NFC Phasen Messung korrigiert.
 * -NFC Funktionalit�t wird �ber den Parameter (E_EEP_VR_Par_Mirr_6 == 1 ) aktiviert
 *
 *    Rev 1.3   09 Dec 2013 16:21:06   ybadal
 * NFC Part implementiert.
 *
 *    Rev 1.2   29 Nov 2013 11:14:30   apeschl
 * Inkompatibilit�ten in  Sensor_Abort_IRQ_Handler f�r CVD beseitigt.
 *
 *    Rev 1.1   29 Nov 2013 09:46:48   apeschl
 * Erste Implementierung des CVD Sensorverfahrens. Deaktivierung der Regelung.
 *
 *    Rev 1.0   25 Nov 2013 09:44:10   ufalkne
 * Initial revision.


*********************************************************** end of comment */
