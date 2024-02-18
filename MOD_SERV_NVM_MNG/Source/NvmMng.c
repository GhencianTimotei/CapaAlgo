/* polyspace MISRA-C3:1.1 [Justified:Unset] "All macro definitions are needed." */
/*------------------------------------------------------------------------------------------------+
| File: NvnMng.c                                                                   |
+-------------------------------------------------------------------------------------------------+
| Project: Audi eTab                                                                              |
+-------------------------------------------------------------------------------------------------+
| Short description: The module contains the implementation of NVM memory and default
|                    values that are stored in FlashNVM.
+-------------------------------------------------------------------------------------------------+
| Created on: 27 Aug 2021                                                                         |
|                                                                                                 |
|                                                                                                 |
+------------------------------------------------------------------------------------------------*/

#ifndef NVMMNG_C_
#define NVMMNG_C_

#include "Platform_Types.h"
#include "sensor_algo.h"
#include "sensor_mcvd.h"
#include "inductive_sensor_algo.h"
#include "NvmMng.h"
#include "EmergencyAccess.h"
#include "VA_Led.h"
#include "BatterySupervisor.h"
#include <string.h>
#include <assert.h>
#include "config.h"
#include "PDL.h"
#include "NvM_Cfg.h"
#include "NvM.h"
#include "Fee.h"
#include "Fls.h"


#define NVMMNG_PAR_ENABLE_CAN_WAKEUP_NFC_MASK     0x40U   /* SSR_797 Byte 0 bit 6  */
#define NVMMNG_ENABLE_CAN_WAKEUP_NFC              ((ST_AUDI_NVM_params.U8_Byte_0_Audi_param_NVM & NVMMNG_PAR_ENABLE_CAN_WAKEUP_NFC_MASK) != 0U)

#define NVMMNG_PAR_ENABLE_CAN_WAKEUP_KESSY_MASK   0x20U /* SSR_796 Byte 0 bit 5 */
#define NVMMNG_ENABLE_CAN_WAKEUP_KESSY            ((ST_AUDI_NVM_params.U8_Byte_0_Audi_param_NVM & NVMMNG_PAR_ENABLE_CAN_WAKEUP_KESSY_MASK) != 0U)

#define NVMMNG_PAR_ENABLE_KESSY_MISUSE_PROTECTION_MASK  0x80u /* byte 0, bit 7 */
#define NVMMNG_PAR_ENABLE_NFC_MISUSE_PROTECTION_MASK    0x01u /* byte 2, bit 1 */   

const ST_unlock_sensor_NVM_parameters_T ST_unlock_sensor_NVM_default_params = {
    U16_ER_THRESHOLD_MIN_PP,
    U16_ER_ACTIVATION_TIME,
    U8_ER_DEBOUNCE_EEP,
    U16_ER_NOISE_DEBOUNCE,
    U16_ER_NOISE_ACTIVE_TIME,
    U16_ER_NOISE_THRESHOLD,
    U16_ER_NOISE_SENSIVITY,
    U8_ER_REF_VAL_COUNT,
    U16_ER_OFF_DELAY_CONS,
    U16_ER_DEACTIVATION_DEBOUNCE,
    U16_CARRIER_VALUE,
    U16_ER_FREEZE_CANCEL_NVM_DEF,
    U16_ER_FREEZE_THRESHOLD_NVM_DEF,
    U16_UNLOCK_BUFFER_NVM_PARAM,
    U16_UNLOCK_BUFFER_NVM_PARAM,
    U16_UNLOCK_BUFFER_NVM_PARAM,
    U16_UNLOCK_BUFFER_NVM_PARAM,
    U16_UNLOCK_BUFFER_NVM_PARAM
};

const ST_lock_sensor_NVM_parameters_T ST_lock_sensor_NVM_default_params = {
    U16_VR_THRESHOLD_MIN_PP,
    U16_VR_THRESHOLD_MAX_PP,
    U16_VR_ACTIVATION_TIME,
    U8_VR_DEBOUNCE_EEP,
    U16_VR_NOISE_DEBOUNCE,
    U16_VR_NOISE_ACTIVE_TIME,
    U16_VR_NOISE_THRESHOLD,
    U16_VR_NOISE_SENSIVITY,
    U8_VR_REF_VAL_COUNT,
    U16_VR_OFF_DELAY_CONS,
    U16_VR_DEACTIVATION_DEBOUNCE,
    U16_VR_FREEZE_CANCEL_NVM_DEF,
    U16_VR_FREEZE_THRESHOLD_NVM_DEF,
    U16_LOCK_BUFFER_NVM_PARAM,
    U16_LOCK_BUFFER_NVM_PARAM,
    U16_LOCK_BUFFER_NVM_PARAM,
    U16_LOCK_BUFFER_NVM_PARAM,
    U16_LOCK_BUFFER_NVM_PARAM
};


const ST_inductive_sensor_NVM_parameters_T ST_inductive_sensor_NVM_default_params = {
        U16_INDUCTIVE_THRESHOLD_NVM_DEF,
        U16_LDC_REF_DEBOUNCE_NVM_DEF,
        U16_LDC_DEBOUNCE_NVM_DEF,
        U16_LDC_DEBOUNCE_ACTIVE_NVM_DEF,
        U16_LDC_OPEN_TIMEOUT_NVM_DEF,
        U16_MODE_OF_ACTIVATION_NVM_DEF,
        U16_LDC_INT_LOW_TICKS_NVM_DEF,
        U16_LDC_INT_HIGH_TICKS_NVM_DEF,
        U16_LDC_FREEZE_CANCEL_NVM_DEF,
        U16_LDC_FREEZE_THRESHOLD_NVM_DEF,
        U16_INDUCTIVE_BUFFER_NVM_PARAM,	
        U16_INDUCTIVE_BUFFER_NVM_PARAM,
        U16_INDUCTIVE_BUFFER_NVM_PARAM,
        U16_INDUCTIVE_BUFFER_NVM_PARAM
};


const ST_Other_HUF_NVM_parameters_T ST_Other_HUF_NVM_default_params = {
        U16_OTHER_HUF_BUFFER_NVM_PARAM,
        U16_OTHER_HUF_BUFFER_NVM_PARAM,
        U16_OTHER_HUF_BUFFER_NVM_PARAM,
        U16_OTHER_HUF_BUFFER_NVM_PARAM,
        U16_OTHER_HUF_BUFFER_NVM_PARAM,
        U16_OTHER_HUF_BUFFER_NVM_PARAM,
        U16_OTHER_HUF_BUFFER_NVM_PARAM,
        U16_OTHER_HUF_BUFFER_NVM_PARAM,
        U16_OTHER_HUF_BUFFER_NVM_PARAM,
        U16_OTHER_HUF_BUFFER_NVM_PARAM
};

const ST_EMERGENCY_ACCESS_NVM_parameters_T ST_emergency_access_NVM_default_params = {
        U16_ACTUATOR_SUPPLY_HIGH_VOLT_NVM,
        U16_ACTUATOR_SUPPLY_LOW_VOLT_NVM,
        U16_ACTUATOR_RETRIES_NVM,
        U16_TIME_ACTUATOR_COOLDOWN_NVM,
        U16_EMERGENCY_ACCESS_BUFFER_NVM_PARAM,
        U16_EMERGENCY_ACCESS_BUFFER_NVM_PARAM
};

const ST_FD02_SPARE_NVM_parameters_T ST_FD02_spare_NVM_default_params = {
        0u,
        0u,
        0u,
        0u,
        0u,
        0u,
        0u,
        0u,
        0u,
        0u,
        0u,
        0u,
        0u,
        0u,
        0u,
        0u,
        0u,
        0u,
        0u,
        0u,
        0u,
        0u
};

const ST_BATTERY_SUPERVISIOR_NVM_parameters_T ST_battery_supervisor_NVM_default_params = {
        U16_BATTERY_SUPERVISOR_BUFFER_NVM_PARAM,
        BATSUP_DEBOUNCE_TIME,
        U16_BATTERY_SUPERVISOR_BUFFER_NVM_PARAM,
        U16_BATTERY_SUPERVISOR_BUFFER_NVM_PARAM,
        U16_BATTERY_SUPERVISOR_BUFFER_NVM_PARAM,
        U16_BATTERY_SUPERVISOR_BUFFER_NVM_PARAM
};

const ST_AUDI_NVM_parameters_T ST_AUDI_NVM_default_params = {
        U8_Byte_0_AUDI_PARAM_NVM,
        U8_Byte_1_AUDI_PARAM_NVM,
        U8_Byte_2_AUDI_PARAM_NVM,
        U8_Byte_3_AUDI_PARAM_NVM,
        U8_Byte_4_AUDI_PARAM_NVM,
        U8_Byte_5_AUDI_PARAM_NVM,
        U8_Byte_6_AUDI_PARAM_NVM,
        U8_Byte_7_AUDI_PARAM_NVM,
        U8_Byte_8_AUDI_PARAM_NVM,
        U8_Byte_9_AUDI_PARAM_NVM,
        U8_Byte_10_AUDI_PARAM_NVM,
        U8_Byte_11_AUDI_PARAM_NVM,
        U8_Byte_12_AUDI_PARAM_NVM,
        U8_Byte_13_AUDI_PARAM_NVM,
        U8_Byte_14_AUDI_PARAM_NVM,
        U8_Byte_15_AUDI_PARAM_NVM,
        U8_Byte_16_AUDI_PARAM_NVM,
        U8_Byte_17_AUDI_PARAM_NVM,
        U8_Byte_18_AUDI_PARAM_NVM,
        U8_Byte_19_AUDI_PARAM_NVM,
        U8_Byte_20_AUDI_PARAM_NVM,
        U8_Byte_21_AUDI_PARAM_NVM,
        U8_Byte_22_AUDI_PARAM_NVM,
        U8_Byte_23_AUDI_PARAM_NVM,
        U8_Byte_24_AUDI_PARAM_NVM,
        U8_Byte_25_AUDI_PARAM_NVM,
        U8_Byte_26_AUDI_PARAM_NVM,
        U8_Byte_27_AUDI_PARAM_NVM,
        U8_Byte_28_AUDI_PARAM_NVM,
        U8_Byte_29_AUDI_PARAM_NVM,
        U8_Byte_30_AUDI_PARAM_NVM,
        U8_Byte_31_AUDI_PARAM_NVM,
        U8_Byte_32_AUDI_PARAM_NVM,
        U8_Byte_33_AUDI_PARAM_NVM,
        U8_Byte_34_AUDI_PARAM_NVM,
        U8_Byte_35_AUDI_PARAM_NVM,
        U8_Byte_36_AUDI_PARAM_NVM,
        U8_Byte_37_AUDI_PARAM_NVM,
        U8_Byte_38_AUDI_PARAM_NVM,
        U8_Byte_39_AUDI_PARAM_NVM,
        U8_Byte_40_AUDI_PARAM_NVM,
        U8_Byte_41_AUDI_PARAM_NVM,
        U8_Byte_42_AUDI_PARAM_NVM,
        U8_Byte_43_AUDI_PARAM_NVM,
        U8_Byte_44_AUDI_PARAM_NVM,
        U8_Byte_45_AUDI_PARAM_NVM,
        U8_Byte_46_AUDI_PARAM_NVM,
        U8_Byte_47_AUDI_PARAM_NVM,
        U8_Byte_48_AUDI_PARAM_NVM,
        U8_Byte_49_AUDI_PARAM_NVM

};

ST_AUDI_NVM_parameters_T ST_AUDI_NVM_params;

const ST_EEPROM_VERSION_NVM_parameters_T ST_EEPROM_VERSION_NVM_default_params = {
		U8_ZERO_VALUE,
		U8_ZERO_VALUE
};
/* polyspace < MISRA-C3:5.1 : Not a defect : Justify with annotations > C99 standard is used to compile, Huf naming convention */
const ST_DID_System_Supplier_ECU_Software_Number_parameters_T ST_DID_System_Supplier_ECU_Software_Number_NVM_default_params = {
		U8_0x31_VALUE,
		U8_0x33_VALUE,
		U8_0x39_VALUE,
		U8_0x30_VALUE,
		U8_0x37_VALUE,
		U8_0x32_VALUE,
		U8_0x36_VALUE,
		U8_0x32_VALUE,
		U8_0x30_VALUE,
		U8_0x30_VALUE,
		U8_0x33_VALUE
};

const ST_DID_FAZIT_ID_NVM_parameters_T ST_DID_FAZIT_ID_NVM_default_params = {

		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE
};

const ST_DID_SparePart_parameters_T ST_DID_SparePartNr_NVM_default_params = {

		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE

};

const ST_DID_ECU_SerialNr_parameters_T ST_DID_ECU_SerialNr_NVM_default_params = {
		DID_SPACE_DEFAULT_VALUE, /* 0 */
		DID_SPACE_DEFAULT_VALUE, /* 1 */
		DID_SPACE_DEFAULT_VALUE, /* 2 */
		DID_SPACE_DEFAULT_VALUE, /* 3 */
		DID_SPACE_DEFAULT_VALUE, /* 4 */
		DID_SPACE_DEFAULT_VALUE, /* 5 */
		DID_SPACE_DEFAULT_VALUE, /* 6 */
		DID_SPACE_DEFAULT_VALUE, /* 7 */
		DID_SPACE_DEFAULT_VALUE, /* 8 */
		DID_SPACE_DEFAULT_VALUE, /* 9 */
		DID_SPACE_DEFAULT_VALUE, /* 10 */
		DID_SPACE_DEFAULT_VALUE, /* 11 */
		DID_SPACE_DEFAULT_VALUE, /* 12 */
		DID_SPACE_DEFAULT_VALUE, /* 13 */
		DID_SPACE_DEFAULT_VALUE, /* 14 */
		DID_SPACE_DEFAULT_VALUE, /* 15 */
		DID_SPACE_DEFAULT_VALUE, /* 16 */
		DID_SPACE_DEFAULT_VALUE, /* 17 */
		DID_SPACE_DEFAULT_VALUE, /* 18 */
		DID_SPACE_DEFAULT_VALUE  /* 19 */
};

const ST_DID_ECU_HardwareNr_parameters_T ST_DID_ECU_HardwareNr_NVM_default_params = {

		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE

};
/* polyspace < MISRA-C3:5.1 : Not a defect : Justify with annotations > C99 standard is used to compile, Huf naming convention */
const ST_DID_SysSupplier_ECU_HardwareNr_parameters_T ST_DID_SysSupplier_ECU_HardwareNr_NVM_default_params = {

		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE

};
/* polyspace < MISRA-C3:5.1 : Not a defect : Justify with annotations > C99 standard is used to compile, Huf naming convention */
const ST_DID_SysNameOrEngineType_parameters_T ST_DID_SysNameOrEngineType_NVM_default_params = {
        /* SWR_1876 */
		(U8)'N',
		(U8)'F',
		(U8)'C',
		(U8)'T',
		(U8)'G',
		(U8)'S',
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE

};

/* polyspace+1 MISRA-C3:8.7 [Justified:Low] "It may be referenced from internal or external" */
const ST_DID_SysNameOrEngineType_parameters_T SysNameOrEngineType_X564 = {

		0x4E, 0x46, 0x43, 0x54, 0x47, 0x53, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20

};

const ST_DID_DataSetNr_parameters_T ST_DID_DataSetNr_NVM_default_params = {

		DID_DASH_VALUE,
		DID_DASH_VALUE,
		DID_DASH_VALUE,
		DID_DASH_VALUE,
		DID_DASH_VALUE,
		DID_DASH_VALUE,
		DID_DASH_VALUE,
		DID_DASH_VALUE,
		DID_DASH_VALUE,
		DID_DASH_VALUE,
		DID_DASH_VALUE

};

const ST_DID_DataSetVersionNr_parameters_T ST_DID_DataSetVersionNr_NVM_default_params = {

		DID_DASH_VALUE,
		DID_DASH_VALUE,
		DID_DASH_VALUE,
		DID_DASH_VALUE

};

/* polyspace < MISRA-C3:5.1 : Not a defect : Justify with annotations > C99 standard is used to compile, Huf naming convention */
const ST_DID_ECU_HardwareVersionNr_parameters_T ST_DID_ECU_HardwareVersionNr_NVM_default_params = {

		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE

};

const ST_DID_WorkshopSystemName_parameters_T ST_DID_WorkshopSystemName_NVM_default_params = {

		DID_DASH_VALUE,
		DID_DASH_VALUE,
		DID_DASH_VALUE,
		DID_DASH_VALUE,
		DID_DASH_VALUE

};
/* polyspace < MISRA-C3:5.1 : Not a defect : Justify with annotations > C99 standard is used to compile, Huf naming convention */
const ST_DID_ProgrammingPreconditions_parameters_T ST_DID_ProgrammingPreconditions_NVM_default_params = {

		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE,
		DID_SPACE_DEFAULT_VALUE

};
/* polyspace:begin <MISRA-C3:9.3 : Not a defect : Justify with annotations > Array is not partially initialized, it contains elements that are active only if certain compiler swtiches are active */

/* polyspace:end <MISRA-C3:9.3 : Not a defect : Justify with annotations > Array is not partially initialized, it contains elements that are active only if certain compiler swtiches are active */

/* polyspace < MISRA-C3:5.1 : Not a defect : Justify with annotations > C99 standard is used to compile, Huf naming convention */
const ST_DID_SysSupplier_ECU_HardwareVersionNr_parameters_T ST_DID_SysSupplier_ECU_HardwareVersionNr_NVM_default_params = {
	DID_SPACE_DEFAULT_VALUE,
	DID_SPACE_DEFAULT_VALUE,
	DID_SPACE_DEFAULT_VALUE
};

const ST_DID_NFC_debugSwitch_parameters_T DID_NFC_debugSwitch_NVM_default_param = {
	U8_ZERO_VALUE
};
const ST_DID_Homologation_parameters_T DID_HomologationMode_NVM_default_param = {
		U8_ZERO_VALUE
};
const ST_DID_Huf_EOL_Done_parameters_T DID_Huf_EOL_Done_NVM_default_param = {
		U8_ZERO_VALUE
};

const ST_DID_HUF_Production_Date_parameters_T DID_HUF_Production_Date_NVM_default_param = {
    DID_SPACE_DEFAULT_VALUE, /* 1 */
    DID_SPACE_DEFAULT_VALUE, /* 2 */
    DID_SPACE_DEFAULT_VALUE, /* 3 */
    DID_SPACE_DEFAULT_VALUE, /* 4 */
    DID_SPACE_DEFAULT_VALUE, /* 5 */
    DID_SPACE_DEFAULT_VALUE, /* 6 */
	DID_SPACE_DEFAULT_VALUE, /* 7 */
	DID_SPACE_DEFAULT_VALUE, /* 8 */
    DID_SPACE_DEFAULT_VALUE, /* 9 */
    DID_SPACE_DEFAULT_VALUE, /* 10 */
    DID_SPACE_DEFAULT_VALUE, /* 11 */
    DID_SPACE_DEFAULT_VALUE, /* 12 */
    DID_SPACE_DEFAULT_VALUE, /* 13 */
    DID_SPACE_DEFAULT_VALUE, /* 14 */
    DID_SPACE_DEFAULT_VALUE  /* 15 */
};

const ST_DID_Katek_EOL_Done_parameters_T DID_Katek_EOL_Done_NVM_default_param = {
    DID_SPACE_DEFAULT_VALUE,
    DID_SPACE_DEFAULT_VALUE
};

const ST_TIME_NFC_DIAG_parameters_T ST_TIME_NFC_DIAG_NVM_default_params = {

		U16_TIME_NFC_DIAG_CYCLE_NORMAL,
		U16_TIME_NFC_DIAG_CYCLE_DEBOUNCE,
		U16_TIME_NFC_DIAG_CYCLE_FAIL_ACTIVE,
		U16_TIME_NFC_DIAG_POR_STARTUP,
		U16_TIME_NFC_DIAG_RETRY,
		U16_TIME_NFC_BUFFER,
		U16_TIME_NFC_BUFFER,
		U16_TIME_NFC_BUFFER,
		U16_TIME_NFC_BUFFER,
		U16_TIME_NFC_BUFFER
};
ST_TIME_NFC_DIAG_parameters_T ST_TIME_NFC_DIAG_NVM_params;

const uint8 SFD_PersistentBuffer_Default_params[U8_SFDA_PERSISTENT_DATA_BUFFER_SIZE] =
	{
		0xA5, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x59, 0x00,
		0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00};

const uint8 SFD_LogData_Default_params[U8_SFDA_LOG_DATA_BUFFER_SIZE] = 
{
	U8_ZERO_VALUE, U8_ZERO_VALUE, U8_ZERO_VALUE, U8_ZERO_VALUE, U8_ZERO_VALUE, U8_ZERO_VALUE, U8_ZERO_VALUE, U8_ZERO_VALUE,
	U8_ZERO_VALUE, U8_ZERO_VALUE, U8_ZERO_VALUE, U8_ZERO_VALUE, U8_ZERO_VALUE, U8_ZERO_VALUE, U8_ZERO_VALUE, U8_ZERO_VALUE,
	U8_ZERO_VALUE, U8_ZERO_VALUE, U8_ZERO_VALUE
};

/* polyspace+7 MISRA-C3:8.7 [Justified:Low] "Variable may be referenced from internal or external" */
ST_DIGIT_NFC_parameters_T ST_DIGIT_NFC_NVM_params;
ST_BATTERY_SUPERVISIOR_NVM_parameters_T ST_battery_supervisor_NVM_params;
ST_Other_HUF_NVM_parameters_T ST_Other_HUF_NVM_params;
ST_EMERGENCY_ACCESS_NVM_parameters_T ST_emergency_access_NVM_params;

uint8 NVM_Sfd_Test_Mode_RAM;
uint8 NVM_Other_Sw_Version_Number_RAM[4];
uint8 ST_vehicle_identifier_NFC_NvM[8];
uint8 ST_vehicle_identifier_validity_NFC_NvM[1];

U8 AU8_NVM_Fingerprint[9];
U8 AU8_NVM_Fingerprint_BL[9];
U8 AU8_NVM_AswProgAttemtsCnt[2];
U8 AU8_NVM_AswProgAttemtsCnt_BL[2];
const U8 AU8_NVM_AswProgAttemtsCntDefault[2] = {0x00, 0x01};
const U8 AU8_NVM_FingerprintDefault[9] = {0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
const uint8 NVM_Other_Sw_Version_Number_Default[4] = {0x00, 0x00, 0x00, 0x00};
const uint8 ST_vehicle_identifier_NFC_NvM_Default[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
const uint8 ST_vehicle_identifier_validirty_NFC_NvM_Default[1] = {0x00};

const uint8 NVM_Sfd_Test_Mode_Default = 0x00u;

void NvM_WriteBlockSync(NvM_BlockIdType BlockId, P2CONST(void, AUTOMATIC, NVM_APPL_DATA) NvM_SrcPtr);
/*************************************************************************************************************
 *  Name                 : NFC_FS_DebugSwitch_BlockOperation_Callback
 *  Description          : This function is called every time when an operation (read or write) has finished on block NFC_FS_DebugSwitch
 *                         The purpose here is to set a variable to TRUE when write operation on our block has finished
 *  Parameters           : BlockId - The ID of the NVM block on which the operation has finished
 *                         ServiceId - NWM WRITE or NWM Read
 *                         JobResult - is the operation finished as OK or not
 *  Return               : Allways returns E_OK and this return is not used
 *  Critical/explanation : -
 *  Author               : lmilita
 *************************************************************************************************************/
/* polyspace < MISRA-C3:2.7 : Not a defect : Justify with annotations > Paremeter should be kept for future usage */
Std_ReturnType NFC_FS_DebugSwitch_BlockOperation_Callback (NvM_BlockIdType BlockId, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult)
{
#ifdef NFC_DEVELOPMENT_MESSAGE
	if((NvMConf_NvMBlockDescriptor_NvM_NFC_FS_debug_switch == BlockId) && (NVM_REQ_OK == JobResult) && (NVM_WRITE_BLOCK == ServiceId))
	{
	    NVM_Content_updated_for_NFC_DevMsg =TRUE;   /* This variable is updated in order to activate the reading from NVM in NFC module */
	    (void)NvM_ReadBlock(NvMConf_NvMBlockDescriptor_NvM_NFC_FS_debug_switch, &DID_NFC_debugSwitch_NVM_param);
	}
	else
	{
		/*do nothing*/
	}
#endif
    return E_OK;
}

/*************************************************************************************************************
 *  Name                 : NFC_HomologationModes_BlockOperation_Callback
 *  Description          : This function is called every time when an operation (read or write) has finished on block NFC_HomologationModes
 *                         The purpose here is to set a variable to TRUE when write operation on our block has finished
 *  Parameters           : BlockId - The ID of the NVM block on which the operation has finished
 *                         ServiceId - NWM WRITE or NWM Read
 *                         JobResult - is the operation finished as OK or not
 *  Return               : Allways returns E_OK and this return is not used
 *  Critical/explanation : -
 *  Author               : lmilita
 *************************************************************************************************************/
Std_ReturnType NFC_HomologationModes_BlockOperation_Callback (NvM_BlockIdType BlockId, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult)
{

	if((NvMConf_NvMBlockDescriptor_NvM_DID_NFC_Homologation_mode == BlockId) && (NVM_REQ_OK == JobResult) && (NVM_WRITE_BLOCK == ServiceId))
	{
#ifdef NFC_HOMOLOGATION_PRESENT
	    /* This variable is updated in order to activate the reading from NVM in NFC Momologation function */
		NVM_Content_updated_for_NFC_Homologation = TRUE;
#endif
#ifdef NFC_DIAGNOSTICS_PRESENT
		/* This variable is updated in order to activate the reading from NVM in NFC Diagnostics function */
		NVM_Content_updated_for_NFC_Diagnostics = TRUE;
#endif
	}
	else
	{
		/*do nothing*/
	}

	return E_OK;
}

/*************************************************************************************************************
 *  Name                 : Audi_Params_BlockOperation_Callback
 *  Description          : This function is called every time when an operation (read or write) has finished on block Audi_Params_Block
 *
 *  Parameters           : BlockId - The ID of the NVM block on which the operation has finished
 *                         ServiceId - NWM WRITE or NWM Read
 *                         JobResult - is the operation finished as OK or not
 *  Return               : E_OK if write was successful
 *  Critical/explanation : -
 *  Author               : ijovano
 *************************************************************************************************************/
/* polyspace < MISRA-C3:2.7 : Not a defect : Justify with annotations > Paremeter should be kept for future usage */
Std_ReturnType Audi_Params_BlockOperation_Callback (NvM_BlockIdType BlockId, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult)
{

    if((NVM_REQ_OK == JobResult) && (NVM_WRITE_BLOCK == ServiceId))
    {
        /* polyspace < MISRA-C3:8.3,17.3 : Not a defect : Justify with annotations > cast to void, not affect the functionality */
        (void)NvM_ReadBlock(NvMConf_NvMBlockDescriptor_NvM_AUDI_PARAMS_BLOCK, &ST_AUDI_NVM_params);
    }
	else
	{
		/*do nothing*/
	}
    return E_OK;
}

/*************************************************************************************************************
 *  Name                 : Unlock_BlockOperation_Callback
 *  Description          : This function is called every time when an operation (read or write) has finished on block Unlock block
 *  Parameters           : BlockId - The ID of the NVM block on which the operation has finished
 *                         ServiceId - NWM WRITE or NWM Read
 *                         JobResult - is the operation finished as OK or not
 *  Return               : E_OK if write was successful
 *  Critical/explanation : -
 *  Author               : ijovano
 *************************************************************************************************************/
/* polyspace < MISRA-C3:2.7 : Not a defect : Justify with annotations > Paremeter should be kept for future usage */
Std_ReturnType Unlock_BlockOperation_Callback (NvM_BlockIdType BlockId, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult)
{

	if((NVM_REQ_OK == JobResult) && (NVM_WRITE_BLOCK == ServiceId))
	{
	    /* polyspace < MISRA-C3:17.7,17.3 : Not a defect : Justify with annotations> Cast to void does not affect the functionality */
		(void)NvM_ReadBlock(NvMConf_NvMBlockDescriptor_NvM_UNLOCK_SENSOR_BLOCK, &ST_unlock_sensor_NVM_params);
	}
	else
	{
		/*do nothing*/
	}
	return E_OK;
}

/*************************************************************************************************************
 *  Name                 : Lock_BlockOperation_Callback
 *  Description          : This function is called every time when an operation (read or write) has finished on block Lock block
 *  Parameters           : BlockId - The ID of the NVM block on which the operation has finished
 *                         ServiceId - NWM WRITE or NWM Read
 *                         JobResult - is the operation finished as OK or not
 *  Return               : E_OK if write was successful
 *  Critical/explanation : -
 *  Author               : ijovano
 *************************************************************************************************************/
/* polyspace < MISRA-C3:2.7 : Not a defect : Justify with annotations > Paremeter should be kept for future usage */
Std_ReturnType Lock_BlockOperation_Callback (NvM_BlockIdType BlockId, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult)
{

	if((NVM_REQ_OK == JobResult) && (NVM_WRITE_BLOCK == ServiceId))
	{
	    /* polyspace < MISRA-C3:17.7,17.3 : Not a defect : Justify with annotations> Cast to void does not affect the functionality */
		(void)NvM_ReadBlock(NvMConf_NvMBlockDescriptor_NvM_LOCK_SENSOR_BLOCK, &ST_lock_sensor_NVM_params);
	}
	else
	{
		/*do nothing*/
	}
	return E_OK;
}

/*************************************************************************************************************
 *  Name                 : Other_HUF_BlockOperation_Callback
 *  Description          : This function is called every time when an operation (read or write) has finished
 *  Parameters           : BlockId - The ID of the NVM block on which the operation has finished
 *                         ServiceId - NWM WRITE or NWM Read
 *                         JobResult - is the operation finished as OK or not
 *  Return               : E_OK if write was successful
 *  Critical/explanation : -
 *  Author               : ijovano
 *************************************************************************************************************/
/* polyspace < MISRA-C3:2.7 : Not a defect : Justify with annotations > Paremeter should be kept for future usage */
Std_ReturnType Other_HUF_BlockOperation_Callback (NvM_BlockIdType BlockId, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult)
{

	if((NVM_REQ_OK == JobResult) && (NVM_WRITE_BLOCK == ServiceId))
	{
	    /* polyspace < MISRA-C3:17.7,17.3 : Not a defect : Justify with annotations> Cast to void does not affect the functionality */
		(void)NvM_ReadBlock(NvMConf_NvMBlockDescriptor_NvM_Other_HUF_BLOCK, &ST_Other_HUF_NVM_params);
	}
	else
	{
		/*do nothing*/
	}
	return E_OK;
}

/*************************************************************************************************************
 *  Name                 : Inductive_BlockOperation_Callback
 *  Description          : This function is called every time when an operation (read or write) has finished on block Inductive
 *  Parameters           : BlockId - The ID of the NVM block on which the operation has finished
 *                         ServiceId - NWM WRITE or NWM Read
 *                         JobResult - is the operation finished as OK or not
 *  Return               : E_OK if write was successful
 *  Critical/explanation : -
 *  Author               : ijovano
 *************************************************************************************************************/
/* polyspace < MISRA-C3:2.7 : Not a defect : Justify with annotations > Paremeter should be kept for future usage */
Std_ReturnType Inductive_BlockOperation_Callback (NvM_BlockIdType BlockId, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult)
{

	if((NVM_REQ_OK == JobResult) && (NVM_WRITE_BLOCK == ServiceId))
	{
	    /* polyspace < MISRA-C3:17.7,17.3 : Not a defect : Justify with annotations> Cast to void does not affect the functionality */
		(void)NvM_ReadBlock(NvMConf_NvMBlockDescriptor_NvM_INDUCTIVE_SENSOR_BLOCK, &ST_inductive_sensor_NVM_params);
	}
	else
	{
		/*do nothing*/
	}
	return E_OK;
}

/*************************************************************************************************************
 *  Name                 : Emergency_BlockOperation_Callback
 *  Description          : This function is called every time when an operation (read or write) has finished on block Emergency
 *  Parameters           : BlockId - The ID of the NVM block on which the operation has finished
 *                         ServiceId - NWM WRITE or NWM Read
 *                         JobResult - is the operation finished as OK or not
 *  Return               : E_OK if write was successful
 *  Critical/explanation : -
 *  Author               : ijovano
 *************************************************************************************************************/
/* polyspace < MISRA-C3:2.7 : Not a defect : Justify with annotations > Paremeter should be kept for future usage */
Std_ReturnType Emergency_BlockOperation_Callback (NvM_BlockIdType BlockId, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult)
{

	if((NVM_REQ_OK == JobResult) && (NVM_WRITE_BLOCK == ServiceId))
	{
	        /* polyspace < MISRA-C3:17.7,17.3 : Not a defect : Justify with annotations> Cast to void does not affect the functionality */
		(void)NvM_ReadBlock(NvMConf_NvMBlockDescriptor_NvM_EMERGENCY_ACCESS_BLOCK, &ST_emergency_access_NVM_params);
	}
	else
	{
		/*do nothing*/
	}
	return E_OK;
}

/*************************************************************************************************************
 *  Name                 : FD02Spare_BlockOperation_Callback
 *  Description          : This function is called every time when an operation (read or write) has finished on block FD02 Spare
 *  Parameters           : BlockId - The ID of the NVM block on which the operation has finished
 *                         ServiceId - NWM WRITE or NWM Read
 *                         JobResult - is the operation finished as OK or not
 *  Return               : E_OK if write was successful
 *  Critical/explanation : -
 *  Author               : ijovano
 *************************************************************************************************************/
/* polyspace < MISRA-C3:2.7 : Not a defect : Justify with annotations > Paremeter should be kept for future usage */
Std_ReturnType FD02Spare_BlockOperation_Callback (NvM_BlockIdType BlockId, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult)
{

	if((NVM_REQ_OK == JobResult) && (NVM_WRITE_BLOCK == ServiceId))
	{
	        /* polyspace < MISRA-C3:17.7,17.3 : Not a defect : Justify with annotations> Cast to void does not affect the functionality */
		(void)NvM_ReadBlock(NvMConf_NvMBlockDescriptor_NvM_FD02_SPARE_BLOCK, &ST_FD02_spare_NVM_params);
	}
	return E_OK;
}

/*************************************************************************************************************
 *  Name                 : Battery_BlockOperation_Callback
 *  Description          : This function is called every time when an operation (read or write) has finished on block Battery supervisor
 *  Parameters           : BlockId - The ID of the NVM block on which the operation has finished
 *                         ServiceId - NWM WRITE or NWM Read
 *                         JobResult - is the operation finished as OK or not
 *  Return               : E_OK if write was successful
 *  Critical/explanation : -
 *  Author               : ijovano
 *************************************************************************************************************/
/* polyspace < MISRA-C3:2.7 : Not a defect : Justify with annotations > Paremeter should be kept for future usage */
Std_ReturnType Battery_BlockOperation_Callback (NvM_BlockIdType BlockId, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult)
{

	if((NVM_REQ_OK == JobResult) && (NVM_WRITE_BLOCK == ServiceId))
	{
	    /* polyspace < MISRA-C3:8.5,17.3 : Not a defect : Justify with annotations > Function is declared once */
	    /* polyspace < MISRA-C3:17.7 : Not a defect : Justify with annotations> Cast to void does not affect the functionality */
            (void)NvM_ReadBlock(NvMConf_NvMBlockDescriptor_NvM_BATTERY_SUPERVISOR_BLOCK, &ST_battery_supervisor_NVM_params);
	}
	else
	{
		/*do nothing*/
	}
	return E_OK;
}

BOOL NvmMng_getEnableWakeUpByKessy(void)
{
    return NVMMNG_ENABLE_CAN_WAKEUP_KESSY;
}

BOOL NvmMng_getEnableWakeUpByNfc(void)
{
    return NVMMNG_ENABLE_CAN_WAKEUP_NFC;
}

U8 NvmMng_getEnableKessyMisuseProtection(void)
{
    return (ST_AUDI_NVM_params.U8_Byte_0_Audi_param_NVM & NVMMNG_PAR_ENABLE_KESSY_MISUSE_PROTECTION_MASK);
}


U8 NvmMng_getEnableNFCMisuseProtection(void)
{
    return (ST_AUDI_NVM_params.U8_Byte_2_Audi_param_NVM & NVMMNG_PAR_ENABLE_NFC_MISUSE_PROTECTION_MASK);
}

U8 NvmMng_getNFCMisuseProtectionPeak(void)
{
    return ST_AUDI_NVM_params.U8_Byte_11_Audi_param_NVM;
}

U8 NvmMng_getNFCEnterPlayProtValue(void)
{
    return ST_AUDI_NVM_params.U8_Byte_48_Audi_param_NVM;
}

U8 NvmMng_getNFCMantainPlayProtValue(void)
{
    return ST_AUDI_NVM_params.U8_Byte_49_Audi_param_NVM;
}


void SwVersionNumber_Updater(void)
{
	/* polyspace+3 MISRA-C3:12.1 [Justified:Low] "The operations will be done in the standard way" */
	/* polyspace+1 MISRA-C3:10.3 [Justified:Low] "The expression is assigned to an object with a different essential type category" */
	const char strCurrentSwVersion[4] = {'0', '0' + PARAM_VER_BYTE_EL_VAR, '0' + PARAM_VER_BYTE_SW_PREFIX, '0' + PARAM_VER_BYTE_SW_SUFFIX};
	uint16 currentSwVersion = (uint16) PARAM_VER_BYTE_EL_VAR * 100 + PARAM_VER_BYTE_SW_PREFIX * 10 + PARAM_VER_BYTE_SW_SUFFIX;
	uint16 nvmStoredSwVersion = 0u;
	
	/* This is to assure we are not underflowing storedSwVersion if the RAM value is 0 */
	/* polyspace+14 MISRA-C3:10.4 [Justified:Low] "no error: cast to U16 here to match with nvmStoredSwVersion type" */
	/* polyspace+13 MISRA-C3:10.2 [Justified:Low] "no error: cast to U16 here to match with nvmStoredSwVersion type" */
	/* polyspace+12 MISRA-C3:10.8 [Justified:Low] "no error: cast to U16 here to match with nvmStoredSwVersion type" */
	if (NVM_Other_Sw_Version_Number_RAM[1] >= '0')
	{
		nvmStoredSwVersion += (uint16) (NVM_Other_Sw_Version_Number_RAM[1] - '0') * 100u;
	}
	if (NVM_Other_Sw_Version_Number_RAM[2] >= '0')
	{
		nvmStoredSwVersion += (uint16) (NVM_Other_Sw_Version_Number_RAM[2] - '0') * 10u;
	}
	if (NVM_Other_Sw_Version_Number_RAM[3] >= '0')
	{
		nvmStoredSwVersion += (uint16) (NVM_Other_Sw_Version_Number_RAM[3] - '0');
	}

	/* In case of false condition a compile error will be raised */
	/* polyspace+4 MISRA-C3:11.8 [Justified:Low] "no error: cast to U8 here to match the data types" */
	assert(sizeof(NVM_Other_Sw_Version_Number_RAM) == sizeof(strCurrentSwVersion));
	memcpy((uint8 *)&NVM_Other_Sw_Version_Number_RAM, (uint8 *)&strCurrentSwVersion, sizeof(strCurrentSwVersion));

	/* Checking if we are coming from an older SW Version (an update was done) */
	if (nvmStoredSwVersion < currentSwVersion)
	{

		/* polyspace+20 MISRA-C3:11.8 [Justified:Low] "no error: cast to U8 here to match the data types" */
		assert(sizeof(ST_inductive_sensor_NVM_params) == sizeof(PDL.INDUCTIVE_SENSOR_BLOCK_DEFAULT));
		(void)memcpy((uint8 *)&ST_inductive_sensor_NVM_params, (uint8 *)&PDL.INDUCTIVE_SENSOR_BLOCK_DEFAULT, sizeof(ST_inductive_sensor_NVM_params));
		assert(sizeof(ST_DIGIT_NFC_NVM_params) == sizeof(PDL.ST_DIGIT_NFC_NVM_params_DEFAULT));
		(void)memcpy((uint8 *)&ST_DIGIT_NFC_NVM_params, (uint8 *)&PDL.ST_DIGIT_NFC_NVM_params_DEFAULT, sizeof(ST_DIGIT_NFC_NVM_params));
		assert(sizeof(ST_DID_SysNameOrEngineType_NVM_params) == sizeof(SysNameOrEngineType_X564));
		(void)memcpy((uint8 *)&ST_DID_SysNameOrEngineType_NVM_params, (uint8 *)&SysNameOrEngineType_X564, sizeof(ST_DID_SysNameOrEngineType_NVM_params));
		assert(sizeof(ST_AUDI_NVM_params) == sizeof(PDL.AUDI_PARAMS_BLOCK_DEFAULT));
		(void)memcpy((uint8 *)&ST_AUDI_NVM_params, (uint8 *)&PDL.AUDI_PARAMS_BLOCK_DEFAULT, sizeof(ST_AUDI_NVM_params));
		assert(sizeof(ST_battery_supervisor_NVM_params) == sizeof(PDL.BATTERY_SUPERVISOR_BLOCK_DEFAULT));
		(void)memcpy((uint8 *)&ST_battery_supervisor_NVM_params, (uint8 *)&PDL.BATTERY_SUPERVISOR_BLOCK_DEFAULT, sizeof(ST_battery_supervisor_NVM_params));
		assert(sizeof(ST_emergency_access_NVM_params) == sizeof(PDL.EMERGENCY_ACCESS_BLOCK_DEFAULT));
		(void)memcpy((uint8 *)&ST_emergency_access_NVM_params, (uint8 *)&PDL.EMERGENCY_ACCESS_BLOCK_DEFAULT, sizeof(ST_emergency_access_NVM_params));
		assert(sizeof(ST_lock_sensor_NVM_params) == sizeof(PDL.LOCK_SENSOR_BLOCK_DEFAULT));
		(void)memcpy((uint8 *)&ST_lock_sensor_NVM_params, (uint8 *)&PDL.LOCK_SENSOR_BLOCK_DEFAULT, sizeof(ST_lock_sensor_NVM_params));
		assert(sizeof(ST_TIME_NFC_DIAG_NVM_params) == sizeof(PDL.TIME_NFC_DIAG));
		(void)memcpy((uint8 *)&ST_TIME_NFC_DIAG_NVM_params, (uint8 *)&PDL.TIME_NFC_DIAG, sizeof(ST_TIME_NFC_DIAG_NVM_params));
		assert(sizeof(ST_unlock_sensor_NVM_params) == sizeof(PDL.UNLOCK_SENSOR_BLOCK_DEFAULT));
		(void)memcpy((uint8 *)&ST_unlock_sensor_NVM_params, (uint8 *)&PDL.UNLOCK_SENSOR_BLOCK_DEFAULT, sizeof(ST_unlock_sensor_NVM_params));
		/* polyspace+30 MISRA-C3:16.3 [Justified:Low] "Break statement is not needed in this case." */
		/* polyspace+30 MISRA-C3:16.1 [Justified:Low] "Break statement is not needed in this case." */
		switch (nvmStoredSwVersion)
		{
			case 0:
			case 560:
			case 561:
			case 562:
			case 563:
			case 564:
			case 565:
				/* "NFCTGS       " */
				NvM_WriteBlockSync(NvMConf_NvMBlockDescriptor_NvM_DID_VW_System_Name_Or_Engine_Type, &ST_DID_SysNameOrEngineType_NVM_params);
			case 570:
			case 571:
			case 580:
			case 581:
			case 590:
			case 591:
			case 592:
			case 593:
			default:
			/* For the last SW update all NvM params. */
				NvM_WriteBlockSync(NvMConf_NvMBlockDescriptor_NvM_DIGIT_NFC, &ST_DIGIT_NFC_NVM_params);
				NvM_WriteBlockSync(NvMConf_NvMBlockDescriptor_NvM_BATTERY_SUPERVISOR_BLOCK, &ST_battery_supervisor_NVM_params);
				NvM_WriteBlockSync(NvMConf_NvMBlockDescriptor_NvM_EMERGENCY_ACCESS_BLOCK, &ST_emergency_access_NVM_params);
				NvM_WriteBlockSync(NvMConf_NvMBlockDescriptor_NvM_LOCK_SENSOR_BLOCK, &ST_lock_sensor_NVM_params);
				NvM_WriteBlockSync(NvMConf_NvMBlockDescriptor_NvM_AUDI_PARAMS_BLOCK, &ST_AUDI_NVM_params);
				NvM_WriteBlockSync(NvMConf_NvMBlockDescriptor_NvM_UNLOCK_SENSOR_BLOCK, &ST_unlock_sensor_NVM_params);
				NvM_WriteBlockSync(NvMConf_NvMBlockDescriptor_NvM_TIME_NFC_DIAG, &ST_TIME_NFC_DIAG_NVM_params);
				NvM_WriteBlockSync(NvMConf_NvMBlockDescriptor_NvM_INDUCTIVE_SENSOR_BLOCK, &ST_inductive_sensor_NVM_params);
				NvM_WriteBlockSync(NvMConf_NvMBlockDescriptor_NvM_Other_Sw_Version_Number, &NVM_Other_Sw_Version_Number_RAM);
				break;
		}
	}
}

/* polyspace+2 MISRA-C3:8.7 [Justified:Low] "Function may be referenced from internal or external" */
/* This function should be replaced with a simple async function for NvM write that should be called in Task_5ms while it returns PENDING */
void NvM_WriteBlockSync(NvM_BlockIdType BlockId, P2CONST(void, AUTOMATIC, NVM_APPL_DATA) NvM_SrcPtr)
{
	uint8 repetitionNumber = 0u;
	NvM_RequestResultType BlockSts = NVM_REQ_PENDING;
    Std_ReturnType retSts = NvM_WriteBlock(BlockId, NvM_SrcPtr);

	while ((E_OK == retSts) && (NVM_REQ_PENDING == BlockSts) && (repetitionNumber < 6u))
	{
		repetitionNumber++;
		NvM_MainFunction();
		Fee_MainFunction();
		Fls_MainFunction();
		retSts = NvM_GetErrorStatus(BlockId, &BlockSts);
	}
}

#endif /* NVMMNG_C_ */
