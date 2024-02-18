/*!
 * \defgroup MOD_SERV_PDL (PDL.c)
 * \{
 ******************************************************************************
 *
 * \par Module Owner:
 * Huf Group
 *
 * \par Initial Project:
 * PDL - Persistent Data Logistics
 *
 ******************************************************************************
 * \par Description:
 * Module that stores a special section spanning a whole sector that will 
 * contain shared data betweeen entities and will be flash process survivable
 *
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
 * Operating System, Service Layer
 *
 * \par Compiler dialect:
 * C99
 *
 * \par Controller:
 * Independent
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

#include "PDL.h"
#include "NvmMng.h"
#include "BatterySupervisor.h"
#include "sensor_algo.h"
#include "sensor_mcvd.h"
#include "inductive_sensor_algo.h"
#include "NvmMng.h"
#include "EmergencyAccess.h"
#include "VA_Led.h"
#include "BatterySupervisor.h"
#include "Crc.h"

#define START_SEC_PDL_FLASH_DATA
#include "MemMap.h"

const volatile tstPDLData PDL = {
    .Header = PDL_PRESENCE_HEADER,

    .VersionID = {0x0, 0x0, 0x0, 0xC},

    .AUDI_PARAMS_BLOCK_DEFAULT = {
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
        U8_Byte_49_AUDI_PARAM_NVM },

    .BATTERY_SUPERVISOR_BLOCK_DEFAULT = {
        U16_BATTERY_SUPERVISOR_BUFFER_NVM_PARAM,
        BATSUP_DEBOUNCE_TIME,
        U16_BATTERY_SUPERVISOR_BUFFER_NVM_PARAM,
        U16_BATTERY_SUPERVISOR_BUFFER_NVM_PARAM,
        U16_BATTERY_SUPERVISOR_BUFFER_NVM_PARAM,
        U16_BATTERY_SUPERVISOR_BUFFER_NVM_PARAM },

    .ECU_Serial_Number = {
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
    },

    .System_Supplier_ECU_Hardware_Number = {
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
    },

    .System_Supplier_ECU_Hardware_Version_Number = {
        DID_SPACE_DEFAULT_VALUE,
        DID_SPACE_DEFAULT_VALUE,
        DID_SPACE_DEFAULT_VALUE
    },

    .System_Supplier_ECU_Software_Number = {
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
        U8_0x39_VALUE
    },

    .VW_ECU_Hardware_Number = {
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
    },

    .VW_ECU_Hardware_Version_Number = {
        DID_SPACE_DEFAULT_VALUE,
        DID_SPACE_DEFAULT_VALUE,
        DID_SPACE_DEFAULT_VALUE
    },

    .VW_FAZIT_Identification_String = {
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
    },

    .VW_Spare_Part_Number =  {
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
    },

    .EEPROM_VERSION = {
        U8_ZERO_VALUE,
        U8_ZERO_VALUE
    },
/* polyspace+8 MISRA-C3:9.3 [Justified:Low] "Partial initializing is mandatory because of configurable array size" */
    .EMERGENCY_ACCESS_BLOCK_DEFAULT = {
        U16_ACTUATOR_SUPPLY_HIGH_VOLT_NVM,
        U16_ACTUATOR_SUPPLY_LOW_VOLT_NVM,
        U16_ACTUATOR_RETRIES_NVM,
        U16_TIME_ACTUATOR_COOLDOWN_NVM,
        U16_EMERGENCY_ACCESS_BUFFER_NVM_PARAM,
        U16_EMERGENCY_ACCESS_BUFFER_NVM_PARAM
    },

    .INDUCTIVE_SENSOR_BLOCK_DEFAULT =  {
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
    },

    .LED_DUTY = {0xFFu},

    .LOCK_SENSOR_BLOCK_DEFAULT = {
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
    },

    .TIME_NFC_DIAG =  {
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
    },

    .UNLOCK_SENSOR_BLOCK_DEFAULT = {
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
    },

    .FD02_SPARE_BLOCK_DEFAULT = {
        (U16)0,
        (U16)0,
        (U16)0,
        (U16)0,
        (U16)0,
        (U16)0,
        (U16)0,
        (U16)0,
        (U16)0,
        (U16)0,
        (U16)0,
        (U16)0,
        (U16)0,
        (U16)0,
        (U16)0,
        (U16)0,
        (U16)0,
        (U16)0,
        (U16)0,
        (U16)0,
        (U16)0,
        (U16)0
    },

    .ST_DIGIT_NFC_NVM_params_DEFAULT = {
        U8_DIGIT_NFC_ANT_AMPL_OK_MIN,
        U8_DIGIT_NFC_ANT_AMPL_OK_MAX,
        U8_DIGIT_NFC_ANT_PHASE_OK_MIN,
        U8_DIGIT_NFC_ANT_PHASE_OK_MAX,
        U8_DIGIT_NFC_ANT_AMPL_SHORT_MIN,
        U8_DIGIT_NFC_ANT_AMPL_SHORT_MAX,
        U8_DIGIT_NFC_ANT_PHASE_SHORT_MIN,
        U8_DIGIT_NFC_ANT_PHASE_SHORT_MAX,
        U8_DIGIT_NFC_ANT_AMPL_OPEN_MIN,
        U8_DIGIT_NFC_ANT_AMPL_OPEN_MAX,
        U8_DIGIT_NFC_ANT_PHASE_OPEN_MIN,
        U8_DIGIT_NFC_ANT_PHASE_OPEN_MAX,
        U8_DIGIT_NFC_DEBOUCE_SPI_NOK,
        U8_DIGIT_NFC_DEBOUCE_TRCV_NOK,
        U8_DIGIT_NFC_DEBOUCE_OSC_NOK,
        U8_DIGIT_NFC_DEBOUCE_ANT_SHORT,
        U8_DIGIT_NFC_DEBOUCE_ANT_OPEN,
        U8_DIGIT_NFC_DEBOUCE_ANT_HEAV_DETUNED,
        U8_DIGIT_NFC_DEBOUCE_ANT_OK,
        U8_DIGIT_NFC_COMPLIANCE_MODE,
        U8_DIGIT_NFC_FRACTIONAL_DELTA_AMPL,
        U8_DIGIT_NFC_FRACTIONAL_DELTA_PHASE,
        U8_DIGIT_NFC_REGULATOR_VOLTAGE,
        U8_DIGIT_NFC_AVERAGING_RATE,
        U8_DIGIT_NFC_BUFFER,
    },

    .System_Supplier_Identifier = {0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x48,0x75,0x66,0x20,0x48,0xFC,0x6C,0x73,0x62,0x65,0x63,0x6B,0x20,0x26,0x20,0x46,0x75,0x72,0x73,0x74,0x20,0x47,0x6D,0x62,0x48,0x20,0x26,0x20,0x43,0x6F,0x2E,0x20,0x4B,0x47,0x0A,0x53,0x74,0x65,0x65,0x67,0x65,0x72,0x20,0x53,0x74,0x72,0x2E,0x20,0x31,0x37,0x0A,0x34,0x32,0x35,0x35,0x31,0x20,0x56,0x65,0x6C,0x62,0x65,0x72,0x74,0x0A,0x47,0x65,0x72,0x6D,0x61,0x6E,0x79,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20},

    .DataCRC = 0x0,
    .TransplantErrors = 0x0,
    .Validity = PDL_VALIDITY_HEADER
};

/* polyspace+2 MISRA-C3:20.1 [Justified:Low] "The file inclusion is used for memory mapping." */
#define STOP_SEC_PDL_FLASH_DATA
#include "MemMap.h"

/* polyspace+1 MISRA-C3:8.9 [Justified:Low] "Variable is declared once here" */
static tenPDLSts cached_sts = PDL_INVALID;

/* polyspace+2 MISRA-C3:20.1 [Justified:Low] "The file inclusion is used for memory mapping." */
#define START_SEC_CODE
#include "MemMap.h"

tenPDLSts is_pdl_valid(void) {
    if (cached_sts == PDL_INVALID)
    {
        if (PDL.Header != PDL_PRESENCE_HEADER) {
            cached_sts = PDL_INVALID;
        }
        /* polyspace+1 MISRA-C3:15.7 [Justified:Low] "else block is not needed here" */
        else if (PDL.Validity != PDL_VALIDITY_HEADER)
        {
            cached_sts = PDL_INVALID;
        }
        /* We run off a couple of assumptions, namely that the CRC is the last element in the PDL 
           and the whole PDL structure occupies the whole section */  
        /* polyspace+2 MISRA-C3:13.2 [Justified:Low] "The order of read accesses to the volatile variables is not significant" */
        /* polyspace+1 MISRA-C3:11.8 [Justified:Low] "does not affect the functionality" */   
        if (PDL.DataCRC != Crc_CalculateCRC32((uint8*)&PDL, ((uint8*) &PDL.DataCRC - (uint8*)&PDL), 0xffffffffU, TRUE))
        {
            cached_sts = PDL_INCOSISTENT;
        }
        else
        {
            cached_sts = PDL_OK;
        }
    }
    return cached_sts;
}

/* polyspace+2 MISRA-C3:20.1 [Justified:Low] "The file inclusion is used for memory mapping." */
#define STOP_SEC_CODE
#include "MemMap.h"
