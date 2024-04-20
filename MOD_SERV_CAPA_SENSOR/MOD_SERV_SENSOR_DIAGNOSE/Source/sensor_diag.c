
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
    uint16 buff[5u];
    getRefThreshold(&buff[0]);

    NfcDevMsg_MessageContent_AU8[0] = (U8)((Sensor_Var_Str[SENSOR_UNLOCK].U16_last_sampleA) >> 8);
    NfcDevMsg_MessageContent_AU8[1] = (U8)(Sensor_Var_Str[SENSOR_UNLOCK].U16_last_sampleA);
    NfcDevMsg_MessageContent_AU8[2] = (U8)((Sensor_Var_Str[SENSOR_UNLOCK].U16_last_sampleB) >> 8);
    NfcDevMsg_MessageContent_AU8[3] = (U8)(Sensor_Var_Str[SENSOR_UNLOCK].U16_last_sampleB);
    NfcDevMsg_MessageContent_AU8[4] = (U8)(U16_ER_filter_dfc >> 8);
    NfcDevMsg_MessageContent_AU8[5] = (U8)(U16_ER_filter_dfc);
    NfcDevMsg_MessageContent_AU8[6] = (U8)(Sensor_Var_Str[SENSOR_UNLOCK].U16_filter_unit_result >> 8);
    NfcDevMsg_MessageContent_AU8[7] = (U8)(Sensor_Var_Str[SENSOR_UNLOCK].U16_filter_unit_result);
    NfcDevMsg_MessageContent_AU8[8] = (U8)(U16_ER_Twert >> 8);
    NfcDevMsg_MessageContent_AU8[9] = (U8)(U16_ER_Twert);
    NfcDevMsg_MessageContent_AU8[10] = (U8)EN_ER_AlgoStateSM;
    NfcDevMsg_MessageContent_AU8[12] = (U8)((Sensor_Var_Str[SENSOR_LOCK].U16_last_sampleA) >> 8);
    NfcDevMsg_MessageContent_AU8[13] = (U8)(Sensor_Var_Str[SENSOR_LOCK].U16_last_sampleA);
    NfcDevMsg_MessageContent_AU8[14] = (U8)((Sensor_Var_Str[SENSOR_LOCK].U16_last_sampleB) >> 8);
    NfcDevMsg_MessageContent_AU8[15] = (U8)(Sensor_Var_Str[SENSOR_LOCK].U16_last_sampleB);
    NfcDevMsg_MessageContent_AU8[16] = (U8)(U16_VR_filter_dfc >> 8);
    NfcDevMsg_MessageContent_AU8[17] = (U8)(U16_VR_filter_dfc);
    NfcDevMsg_MessageContent_AU8[18] = (U8)(Sensor_Var_Str[SENSOR_LOCK].U16_filter_unit_result >> 8);
    NfcDevMsg_MessageContent_AU8[19] = (U8)(Sensor_Var_Str[SENSOR_LOCK].U16_filter_unit_result);
    NfcDevMsg_MessageContent_AU8[20] = (U8)(U16_VR_Twert >> 8);
    NfcDevMsg_MessageContent_AU8[21] = (U8)(U16_VR_Twert);
    NfcDevMsg_MessageContent_AU8[22] = (U8)EN_VR_AlgoStateSM;
    NfcDevMsg_MessageContent_AU8[23] = (U8)((buff[0]) >> 8);
    NfcDevMsg_MessageContent_AU8[24] = (U8)(buff[0]);
    NfcDevMsg_MessageContent_AU8[25] = (U8)((buff[1]) >> 8);
    NfcDevMsg_MessageContent_AU8[26] = (U8)(buff[1]);
    NfcDevMsg_MessageContent_AU8[27] = (U8)((buff[2]) >> 8);
    NfcDevMsg_MessageContent_AU8[28] = (U8)(buff[2]);
    NfcDevMsg_MessageContent_AU8[29] = (U8)((buff[3]) >> 8);
    NfcDevMsg_MessageContent_AU8[30] = (U8)(buff[3]);
    NfcDevMsg_MessageContent_AU8[31] = (U8)((buff[4]) >> 8);
    NfcDevMsg_MessageContent_AU8[32] = (U8)(buff[4]);
    
    //NfcDevMsg_MessageContent_AU8[63] = LDC3114_getStatusByte();

    (void)Com_SendSignal(ComConf_ComSignal_DEV_NFC_FS_Resp_3F_Data_XIX_DEV_NFC_FS_Resp_3F_XIX_HCP4_CANFD01_56a7f80a_Tx, &NfcDevMsg_MessageContent_AU8[0]);
}
#endif 
