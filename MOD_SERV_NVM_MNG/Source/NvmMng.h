/*
 * NvmMng.h
 *
 *  Created on: 27 Aug 2021
 *      Author: grovent
 */

#ifndef NVMMNG_H_
#define NVMMNG_H_

#include "NVM_Types.h"
/* polyspace < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
#define U16_def_test_ER                ((U16)10)
/* polyspace < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
#define U16_def_test_VR                ((U16)10)

/* Audi parameters */
/* Byte 0
 * Bit 5 - cp_enableCanWakeUpKessy - CAN wake-up activation due to Kessy
 * Bit 6 - cp_enableCanWakeUpNFC - CAN wake-up activation due to NFC
 * Bit 7 - cp_enableKessyMisuseProtection - Activation play protection for Kessy */
#define U8_Byte_0_AUDI_PARAM_NVM       0xE0u

/* Byte 1
 * Bit 0-7 - p_vehicleType - vehicle variant */
#define U8_Byte_1_AUDI_PARAM_NVM       0x13u

/* Byte 2
 * Bit 0 - cp_enableNFCMisuseProtection - Activate play protection for NFC
 * Bit 1 - cp_KL15disableNFC - NFC deactivation at Kl.15 on
 * Bit 2 - cp_NFC_TGS - 0 --> NFC TGS sensor not installed; 1 --> NFC TGS sensor installed
 * Bit 3 - cp_ESMdisableNFC - NFC deactivation in energy-saving mode
 * Bit 4 - cp_ESMdisableKessy - Deactivation of capacitive sensor Kessy with active ESM
 * Bit 5 - cp_ThresholdPositivActive - When a smartphone comes into range, the N-value can theoretically also become larger, then NFC should also be switched on
 * Bit 6 - cp_enableLighting - TGS lighting activation
 * Bit 7 - cp_ChromeCover - Activation of the settings implemented to adapt the behavior of the NFC and/or Kappa functions to the changed conditions due to the chrome application on the door handle. */
#define U8_Byte_2_AUDI_PARAM_NVM       0x15u

/* Byte 3
 * Bit 0-7 - p_tPollingDelay - Time after negative select after which polling is resumed in ms (Scaling 100) --> e.g. value 0x5 corresponds to 500ms */
#define U8_Byte_3_AUDI_PARAM_NVM       0x05u

/* Byte 4
 * Bit 0-7 - p_tRoutingTimer - Time after sending the Authentication Request message 
Time that the NFC field is still maintained after data has been sent to the function control device in ms (scaling 100) --> value 0x0F corresponds to 1500 ms */
#define U8_Byte_4_AUDI_PARAM_NVM       0x19u


/* Byte 5
 * Bit 0-7 - p_tWaitingApduResponse - Time that a smartphone has available until response occurs in ms (scaling 25) --> value 0x14 corresponds to 500ms */
#define U8_Byte_5_AUDI_PARAM_NVM       0x14u

/* Byte 6
 * Bit 0-7 - p_LpcdSensitivity - Sensitivity for activating NFC communication in LPCD mode */
#define U8_Byte_6_AUDI_PARAM_NVM       0x01u

/* Byte 7
 * Bit 0-7 - p_tLpcdPulseDuration - Length of the LPCD pulse
                                    Minimum length for the LPCD pulse: 40�s
                                    Target length for the LPCD pulse: 40�s
                                    Maximum length for the LPDC pulse: 50�s
                                    Time for which the field is measured for phase detection in �s (Scaling 10) --> Value 0x4 corresponds to 40�s */
#define U8_Byte_7_AUDI_PARAM_NVM       0x04u

/* Byte 8
 * Bit 0-7 - p_tActivateESM - Time until the NFC controller activates the ESM autonomously in h (Scaling 1) --> Value 0x48 corresponds to 72h */
#define U8_Byte_8_AUDI_PARAM_NVM       0x48u

/* Byte 9
 * Bit 0-7 - p_tPollingIntervalEsmActive - Waiting time between two measurements ESM active [long polling time] in ms (Scaling 25) --> Value 0x14 corresponds to 500ms */
#define U8_Byte_9_AUDI_PARAM_NVM       0x14u

/* Byte 10
 * Bit 0-7 - p_tPollingIntervalEsmInactive - Waiting time between two measurements ESM not active [short polling time] in ms (Scaling 10) --> Value 0xA corresponds to 100ms. */
#define U8_Byte_10_AUDI_PARAM_NVM       0x0Au

/* Byte 11
 * Bit 0-7 - p_nRetryNFCMisuseProtection - Number of times an unauthorized NFC device was detected within the qualification time (p_t_NMP_MODE_ENTER_TIMEOUT) of the NFC game protection (scaling 1).
                                           Maximum value of the "NFC game protection counter".*/
#define U8_Byte_11_AUDI_PARAM_NVM       0x28u

/* Byte 12
 * Bit 0-7 - p_nRetryKessyMisuseProtection - Number of detection of an unauthorized actuation of the kapa. Sensor within the qualification time (p_t_CMP_MODE_ENTER_TIMEOUT) of the Kessy game protection (Scaling 1)*/
#define U8_Byte_12_AUDI_PARAM_NVM       0x14u

/* Byte 13
 * Bit 0-3 - p_nLpcdCalibration - The number of NFC false triggers after which a new NFC calibration should be carried out must be applicable as "p_nLpcdCalibration"
 * Bit 4-7 - p_tLpcdCalibration - The time in seconds after which the counter ("p_nLpcdCalibration") is reset for the NFC false triggering must be applicable as "p_tLpcdCalibration" (Scaling 1) -> value 0x8 corresponds to 8s */
#define U8_Byte_13_AUDI_PARAM_NVM       0x85u

/* Byte 14
 * Bit 0-7 - p_tWakeUpTimer - Timeout value for the wake up timer, which must start if the connection was successfully established in ms (Scaling 10) -> value 0x5 corresponds to 50ms. */
#define U8_Byte_14_AUDI_PARAM_NVM       0x05u

/* Byte 15
 * Bit 0-7 - p_tWaitingCommunicationError - Time after sending the "Authentication Request" message in which an "Apdu Command" or an "Authentication Response" message is to be received from the function control device in ms (Scaling 10) -> value 0xA corresponds to 100ms. */
#define U8_Byte_15_AUDI_PARAM_NVM       0x0Au

/* Byte 16
 * TBD */
#define U8_Byte_16_AUDI_PARAM_NVM       0x00u

/* Byte 17
 * Bit 0-7 - p_nRetryAuthenticationRequest - Number of retries for sending the authentication request if it fails due to a communication error.*/
#define U8_Byte_17_AUDI_PARAM_NVM       0x03u

/* Byte 18
 * Bit 0-7 - p_tRetryAuthenticationRequest - Duration between two repetitions of the sending of the authentication request in ms (Scaling 10) -> value 0xA corresponds to 100ms. */
#define U8_Byte_18_AUDI_PARAM_NVM       0x0Au

/* Byte 19
 * Bit 0-7 - p_nEcpPollingCycles - Number of cycles that have to go through with each NFC polling process */
#define U8_Byte_19_AUDI_PARAM_NVM       0x06u

/* Byte 20
 * Bit 0-7 - p_tLpcdPulseIntervalEsmInactive - Time for the interval in which the NFC reader should generate an LPCD pulse if the energy-saving mode is not active in ms (Scaling 10) -> value 0xA corresponds to 100ms. */
#define U8_Byte_20_AUDI_PARAM_NVM       0x0Au

/* Byte 21
 * Bit 0-7 - p_tLpcdPulseIntervalEsmActive - Time for the interval in which the NFC reader should generate an LPCD pulse when the energy-saving mode is active in ms (scaling 25) -> value 0x14 corresponds to 500ms */
#define U8_Byte_21_AUDI_PARAM_NVM       0x14u

/* Byte 22
 * Bit 0-3 - p_EcpTci2LowerNibble - Value for the lower nibble of the TCI (2) bytes in the ECP frame */
#define U8_Byte_22_AUDI_PARAM_NVM       0x11u

/* Byte 23
 * Bit 0-7 - p_Licht_Helligkeit - max duty cycle*/
#define U8_Byte_23_AUDI_PARAM_NVM       0xBFu

/* Byte 24
 * Bit 0-7 - p_Licht_Dimmrampe_Dauer_Aufdimmen - ramp up */
#define U8_Byte_24_AUDI_PARAM_NVM       0x96u

/* Byte 25
 * Bit 0-7 - p_Licht_Dimmrampe_Dauer_Abdimmen - ramp down*/
#define U8_Byte_25_AUDI_PARAM_NVM       0x96u

/* Byte 26
 * Bit 0-7 - p_nRetryNFCDetection - Maximum number of attempts for a successful connection.  Number of failed SELECT sequences. */
#define U8_Byte_26_AUDI_PARAM_NVM       0x01u

/* Byte 27
 * TBD */
#define U8_Byte_27_AUDI_PARAM_NVM       0x00u

/* Byte 28
 * TBD */
#define U8_Byte_28_AUDI_PARAM_NVM       0x00u

/* Byte 29
 * TBD */
#define U8_Byte_29_AUDI_PARAM_NVM       0x00u

/* Byte 30
 * TBD */
#define U8_Byte_30_AUDI_PARAM_NVM       0x00u

/* Byte 31
 * TBD */
#define U8_Byte_31_AUDI_PARAM_NVM       0x00u

/* Byte 32
 * TBD */
#define U8_Byte_32_AUDI_PARAM_NVM       0x00u

/* Byte 33
 * TBD */
#define U8_Byte_33_AUDI_PARAM_NVM       0x00u

/* Byte 34
 * TBD */
#define U8_Byte_34_AUDI_PARAM_NVM       0x00u

/* Byte 35
 * TBD */
#define U8_Byte_35_AUDI_PARAM_NVM       0x00u

/* Byte 36
 * TBD */
#define U8_Byte_36_AUDI_PARAM_NVM       0x00u

/* Byte 37
 * TBD */
#define U8_Byte_37_AUDI_PARAM_NVM       0x00u

/* Byte 38
 * TBD */
#define U8_Byte_38_AUDI_PARAM_NVM       0x00u

/* Byte 39
 * TBD */
#define U8_Byte_39_AUDI_PARAM_NVM       0x00u

/* Byte 40
 * TBD */
#define U8_Byte_40_AUDI_PARAM_NVM       0x00u

/* Byte 41
 * TBD */
#define U8_Byte_41_AUDI_PARAM_NVM       0x00u

/* Byte 42
 * TBD */
#define U8_Byte_42_AUDI_PARAM_NVM       0x0Au

/* Byte 43
 * TBD */
#define U8_Byte_43_AUDI_PARAM_NVM       0xC8u

/* Byte 44
 * Play Protection - evaluation timer value for unlock - capacitive sensor and inductive */
#define U8_Byte_44_AUDI_PARAM_NVM       0x0Au

/* Byte 45
 * Play Protection - decrement timer to disable play protection, value for unlock - capacitive sensor and inductive */
#define U8_Byte_45_AUDI_PARAM_NVM       0x1Eu

/* Byte 46
 * Play Protection - evaluation timer value for lock - capacitive sensor */
#define U8_Byte_46_AUDI_PARAM_NVM       0x0Au

/* Byte 47
  * Play Protection - decrement timer to disable play protection, value for lock - capacitive sensor */
#define U8_Byte_47_AUDI_PARAM_NVM       0x1Eu

/* Byte 48
 * Bit 0-7 - p_t_NMP_MODE_ENTER_TIMEOUT - Qualification time in which the unauthorized NFC operations are evaluated in s (Scaling 1)*/
#define U8_Byte_48_AUDI_PARAM_NVM       0xB4u

/* Byte 49
 * Bit 0-7 - p_t_NMP_MODE_MAINTAIN_TIMEOUT - Dequalification time in which the NFC sensor is switched off due to NFC game protection in s (Scaling 1).*/
#define U8_Byte_49_AUDI_PARAM_NVM       0x1Eu

/************************Logistics params*******************************/
/* System supplier identifier */

#define U8_ZERO_VALUE					0x00

/* NvM values structure for System supplier software version number */
#define	DID_SPACE_DEFAULT_VALUE 		0x20

#define DID_DASH_VALUE                  0x2D  /* ASCII dash character '-' */

#define U8_0x31_VALUE					0x31
#define U8_0x33_VALUE					0x33
#define U8_0x39_VALUE					0x39
/* polyspace < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
/* polyspace+9 MISRA-C3:2.5 [Justified:Low] "Macro should be kept for future usage" */
#define U8_0x34_VALUE					0x34
#define U8_0x35_VALUE					0x35
#define U8_0x32_VALUE					0x32
#define U8_0x30_VALUE					0x30
#define U8_0x36_VALUE					0x36
#define U8_0x37_VALUE					0x37
#define U8_0x38_VALUE					0x38

/* NvM default values for TIME NFC DIAG parameters */

#define U16_TIME_NFC_DIAG_CYCLE_NORMAL		0xFD20
#define U16_TIME_NFC_DIAG_CYCLE_DEBOUNCE	0x01
#define U16_TIME_NFC_DIAG_CYCLE_FAIL_ACTIVE	0xE10
#define U16_TIME_NFC_DIAG_POR_STARTUP		0x01
#define U16_TIME_NFC_DIAG_RETRY				0x01

/* NvM default values for DIGIT NFC parameters */

#define U8_DIGIT_NFC_ANT_AMPL_OK_MIN		((U8)132)
#define U8_DIGIT_NFC_ANT_AMPL_OK_MAX		((U8)230)
#define U8_DIGIT_NFC_ANT_PHASE_OK_MIN		((U8)117)
#define U8_DIGIT_NFC_ANT_PHASE_OK_MAX		((U8)238)
#define U8_DIGIT_NFC_ANT_AMPL_SHORT_MIN		((U8)0)
#define U8_DIGIT_NFC_ANT_AMPL_SHORT_MAX		((U8)39)
#define U8_DIGIT_NFC_ANT_PHASE_SHORT_MIN	((U8)179)
#define U8_DIGIT_NFC_ANT_PHASE_SHORT_MAX	((U8)252)
#define U8_DIGIT_NFC_ANT_AMPL_OPEN_MIN		((U8)20)
#define U8_DIGIT_NFC_ANT_AMPL_OPEN_MAX		((U8)37)
#define U8_DIGIT_NFC_ANT_PHASE_OPEN_MIN		((U8)43)
#define U8_DIGIT_NFC_ANT_PHASE_OPEN_MAX		((U8)76)

#define U8_DIGIT_NFC_DEBOUCE_SPI_NOK			((U8)10)
#define U8_DIGIT_NFC_DEBOUCE_TRCV_NOK			((U8)10)
#define U8_DIGIT_NFC_DEBOUCE_OSC_NOK			((U8)10)
#define U8_DIGIT_NFC_DEBOUCE_ANT_SHORT			((U8)10)
#define U8_DIGIT_NFC_DEBOUCE_ANT_OPEN			((U8)10)
#define U8_DIGIT_NFC_DEBOUCE_ANT_HEAV_DETUNED	((U8)10)
#define U8_DIGIT_NFC_DEBOUCE_ANT_OK				((U8)10)

#define U8_SFDA_PERSISTENT_DATA_BUFFER_SIZE		30U
#define U8_SFDA_LOG_DATA_BUFFER_SIZE			19U

#define U16_UNLOCK_BUFFER_NVM_PARAM                     0xFFFF
#define U16_LOCK_BUFFER_NVM_PARAM                       0xFFFF
#define U16_INDUCTIVE_BUFFER_NVM_PARAM                  0xFFFF
#define U16_EMERGENCY_ACCESS_BUFFER_NVM_PARAM           0xFFFF
#define U16_OTHER_HUF_BUFFER_NVM_PARAM                  0xFFFF
#define U16_BATTERY_SUPERVISOR_BUFFER_NVM_PARAM         0x00
#define U16_TIME_NFC_BUFFER                             0xFFFF
#define U8_DIGIT_NFC_BUFFER                             0x00


#define U8_DIGIT_NFC_FRACTIONAL_DELTA_AMPL    ((U8)0x01)
#define U8_DIGIT_NFC_FRACTIONAL_DELTA_PHASE   ((U8)0x01)
#define U8_DIGIT_NFC_REGULATOR_VOLTAGE        ((U8)0x0E)
#define U8_DIGIT_NFC_AVERAGING_RATE           ((U8)0x01)

#define U8_DIGIT_NFC_COMPLIANCE_MODE                    0x00
#define U8_DIGIT_NFC_BUFFER                             0x00

#define SFD_TEST_MODE_INACTIVE (0x00u)
#define SFD_TEST_MODE_ACTIVE (0x01u)
#define SFD_TEST_MODE_DISABLED (0x02u)


/* NvM parameters structure for unlock sensor */
typedef struct
{
    U16 U16_P_ER_APPROACH_THRESHOLD;
	U16 U16_P_ER_TIMEOUT;
	U16 U16_P_ER_DEBOUNCE;
    U16 U16_P_ER_NOISE_DEBOUNCE;
    U16 U16_P_ER_NOISE_ACTIVE;
    U16 U16_P_ER_NOISE_THRESHOLD;
    U16 U16_P_ER_NOISE_OFFSET;
    U16 U16_P_ER_VAL_FOR_REF;
    U16 U16_P_ER_OFFDELAY;
    U16 U16_P_ER_DEACTIVATION_DEBOUNCE;
    U16 U16_P_CARRIER_VALUE;
    U16 U16_P_ER_FREEZE_CANCEL;
    U16 U16_P_ER_FREEZE_THRESHOLD;
    U16 U16_UNLOCK_BUFFER_PARAM_3;
    U16 U16_UNLOCK_BUFFER_PARAM_4;
    U16 U16_UNLOCK_BUFFER_PARAM_5;
    U16 U16_UNLOCK_BUFFER_PARAM_6;
    U16 U16_UNLOCK_BUFFER_PARAM_7;
}ST_unlock_sensor_NVM_parameters_T;

extern const ST_unlock_sensor_NVM_parameters_T ST_unlock_sensor_NVM_default_params;

extern ST_unlock_sensor_NVM_parameters_T ST_unlock_sensor_NVM_params;


/* NvM parameters structure for lock sensor */
typedef struct
{
    U16 U16_P_VR_APPROACH_THRESHOLD;
	U16 U16_P_VR_TOUCH_THRESHOLD;
	U16 U16_P_VR_TIMEOUT;
	U16 U16_P_VR_DEBOUNCE;
    U16 U16_P_VR_NOISE_DEBOUNCE;
    U16 U16_P_VR_NOISE_ACTIVE;
    U16 U16_P_VR_NOISE_THRESHOLD;
    U16 U16_P_VR_NOISE_OFFSET;
    U16 U16_P_VR_VAL_FOR_REF;
    U16 U16_P_VR_OFFDELAY;
    U16 U16_P_VR_DEACTIVATION_DEBOUNCE;
    U16 U16_P_VR_FREEZE_CANCEL;
    U16 U16_P_VR_FREEZE_THRESHOLD;
    U16 U16_LOCK_BUFFER_PARAM_3;
    U16 U16_LOCK_BUFFER_PARAM_4;
    U16 U16_LOCK_BUFFER_PARAM_5;
    U16 U16_LOCK_BUFFER_PARAM_6;
    U16 U16_LOCK_BUFFER_PARAM_7;
}ST_lock_sensor_NVM_parameters_T;

extern const ST_lock_sensor_NVM_parameters_T ST_lock_sensor_NVM_default_params;

extern ST_lock_sensor_NVM_parameters_T ST_lock_sensor_NVM_params;


/* NvM parameters structure for inductive sensor */
typedef struct
{
    U16 U16_LDC_THRESHOLD;
    U16 U16_LDC_VAL_FOR_REF;
    U16 U16_LDC_DEBOUNCE_NORMAL;
    U16 U16_LDC_DEBOUNCE_ACTIVE;
    U16 U16_OPEN_TIMEOUT;
    U16 U16_MODE_OF_ACTIVATION_PARAM;
    U16 U16_LDC_INT_LOW_TICKS;
    U16 U16_LDC_INT_HIGH_TICKS;
    U16 U16_LDC_FREEZE_CANCEL;
    U16 U16_LDC_FREEZE_THRESHOLD;
    U16 U16_INDUCTIVE_BUFFER_PARAM_3;
    U16 U16_INDUCTIVE_BUFFER_PARAM_4;
    U16 U16_INDUCTIVE_BUFFER_PARAM_5;
    U16 U16_INDUCTIVE_BUFFER_PARAM_6;
}ST_inductive_sensor_NVM_parameters_T;

extern const ST_inductive_sensor_NVM_parameters_T ST_inductive_sensor_NVM_default_params;

extern ST_inductive_sensor_NVM_parameters_T ST_inductive_sensor_NVM_params;


/* NvM parameters structure for other HUF parameters */
typedef struct
{
    U16 U16_OTHER_HUF_BUFFER_PARAM_0;
    U16 U16_OTHER_HUF_BUFFER_PARAM_1;
    U16 U16_OTHER_HUF_BUFFER_PARAM_2;
    U16 U16_OTHER_HUF_BUFFER_PARAM_3;
    U16 U16_OTHER_HUF_BUFFER_PARAM_4;
    U16 U16_OTHER_HUF_BUFFER_PARAM_5;
    U16 U16_OTHER_HUF_BUFFER_PARAM_6;
    U16 U16_OTHER_HUF_BUFFER_PARAM_7;
    U16 U16_OTHER_HUF_BUFFER_PARAM_8;
    U16 U16_OTHER_HUF_BUFFER_PARAM_9;

}ST_Other_HUF_NVM_parameters_T;

extern const ST_Other_HUF_NVM_parameters_T ST_Other_HUF_NVM_default_params;

extern ST_Other_HUF_NVM_parameters_T ST_Other_HUF_NVM_params;


/* NvM parameters structure for EMERGENCY ACCESS */
typedef struct
{
    U16 U16_ACTUATOR_SUPPLY_HIGH_VOLT_PARAM;
    U16 U16_ACTUATOR_SUPPLY_LOW_VOLT_PARAM;
    U16 U16_ACTUATOR_RETRIES_PARAM;
    U16 U16_TIME_ACTUATOR_COOLDOWN_PARAM;
    U16 U16_ACTUATOR_SUPPLY_BUFFER_PARAM_3;
    U16 U16_ACTUATOR_SUPPLY_BUFFER_PARAM_4;
}ST_EMERGENCY_ACCESS_NVM_parameters_T;

extern const ST_EMERGENCY_ACCESS_NVM_parameters_T ST_emergency_access_NVM_default_params;

extern ST_EMERGENCY_ACCESS_NVM_parameters_T ST_emergency_access_NVM_params;

/* NvM parameters structure for DID 0xFD02 spare block */
typedef struct
{
    U16 U16_UNUSED_PARAM_1;
    U16 U16_UNUSED_PARAM_2;
    U16 U16_UNUSED_PARAM_3;
    U16 U16_UNUSED_PARAM_4;
    U16 U16_UNUSED_PARAM_5;
    U16 U16_UNUSED_PARAM_6;
    U16 U16_UNUSED_PARAM_7;
    U16 U16_UNUSED_PARAM_8;
    U16 U16_UNUSED_PARAM_9;
    U16 U16_UNUSED_PARAM_10;
    U16 U16_UNUSED_PARAM_11;
    U16 U16_UNUSED_PARAM_12;
    U16 U16_UNUSED_PARAM_13;
    U16 U16_UNUSED_PARAM_14;
    U16 U16_UNUSED_PARAM_15;
    U16 U16_UNUSED_PARAM_16;
    U16 U16_UNUSED_PARAM_17;
    U16 U16_UNUSED_PARAM_18;
    U16 U16_UNUSED_PARAM_19;
    U16 U16_UNUSED_PARAM_20;
    U16 U16_UNUSED_PARAM_21;
    U16 U16_UNUSED_PARAM_22;

}ST_FD02_SPARE_NVM_parameters_T;

extern const ST_FD02_SPARE_NVM_parameters_T ST_FD02_spare_NVM_default_params;
/* polyspace+1 MISRA-C3:8.6 [Justified:Low] "External declaration is needed" */
extern ST_FD02_SPARE_NVM_parameters_T ST_FD02_spare_NVM_params;

/* NvM parameters structure for BATTERY SUPERVISOR */
typedef struct
{
    U16 U16_VOLTMON_DEBOUNCE_TIME_ACTIVE_PARAM;
    U16 U16_VOLTMON_DEBOUNCE_TIME_NORMAL_PARAM;
    U16 U16_BATTERY_SUPERVISOR_BUFFER_PARAM_1;
    U16 U16_BATTERY_SUPERVISOR_BUFFER_PARAM_2;
    U16 U16_BATTERY_SUPERVISOR_BUFFER_PARAM_3;
    U16 U16_BATTERY_SUPERVISOR_BUFFER_PARAM_4;
}ST_BATTERY_SUPERVISIOR_NVM_parameters_T;

extern const ST_BATTERY_SUPERVISIOR_NVM_parameters_T ST_battery_supervisor_NVM_default_params;
/* polyspace < MISRA-C3:8.6 : Not a defect : Justify with annotations > It has just one definition. The others are just declarations. */
extern ST_BATTERY_SUPERVISIOR_NVM_parameters_T ST_battery_supervisor_NVM_params;

/* NvM parameters structure for EEPEROM VERSION */
typedef struct
{
    U8 BYTE_1;
    U8 BYTE_2;

}ST_EEPROM_VERSION_NVM_parameters_T;

extern ST_EEPROM_VERSION_NVM_parameters_T ST_EEPROM_VERSION_NVM_params;

extern const ST_EEPROM_VERSION_NVM_parameters_T ST_EEPROM_VERSION_NVM_default_params;

/* NvM parameters structure for EEPEROM VERSION */
typedef struct
{
	U8 BYTE_1;
	U8 BYTE_2;
	U8 BYTE_3;
	U8 BYTE_4;
	U8 BYTE_5;
	U8 BYTE_6;
	U8 BYTE_7;
	U8 BYTE_8;
	U8 BYTE_9;
	U8 BYTE_10;
	U8 BYTE_11;

}ST_DID_System_Supplier_ECU_Software_Number_parameters_T;

/* polyspace+1 MISRA-C3:5.1 [Not a defect:Low] "C99 standard is used to compile, Huf naming convention" */
extern ST_DID_System_Supplier_ECU_Software_Number_parameters_T ST_DID_System_Supplier_ECU_Software_Number_params;
/* polyspace < MISRA-C3:5.1 : Not a defect : Justify with annotations > C99 standard is used to compile, Huf naming convention */
extern const ST_DID_System_Supplier_ECU_Software_Number_parameters_T ST_DID_System_Supplier_ECU_Software_Number_NVM_default_params;

/* NvM parameters structure for DID FAZIT */
typedef struct
{
	U8 U8_BYTE1;
	U8 U8_BYTE2;
	U8 U8_BYTE3;
	U8 U8_BYTE4;
	U8 U8_BYTE5;
	U8 U8_BYTE6;
	U8 U8_BYTE7;
	U8 U8_BYTE8;
	U8 U8_BYTE9;
	U8 U8_BYTE10;
	U8 U8_BYTE11;
	U8 U8_BYTE12;
	U8 U8_BYTE13;
	U8 U8_BYTE14;
	U8 U8_BYTE15;
	U8 U8_BYTE16;
	U8 U8_BYTE17;
	U8 U8_BYTE18;
	U8 U8_BYTE19;
	U8 U8_BYTE20;
	U8 U8_BYTE21;
	U8 U8_BYTE22;
	U8 U8_BYTE23;

}ST_DID_FAZIT_ID_NVM_parameters_T;

extern const ST_DID_FAZIT_ID_NVM_parameters_T ST_DID_FAZIT_ID_NVM_default_params;

extern ST_DID_FAZIT_ID_NVM_parameters_T ST_DID_FAZIT_ID_NVM_params;

/* NvM parameters structure for DID Spare part */
typedef struct
{
	U8 U8_BYTE1;
	U8 U8_BYTE2;
	U8 U8_BYTE3;
	U8 U8_BYTE4;
	U8 U8_BYTE5;
	U8 U8_BYTE6;
	U8 U8_BYTE7;
	U8 U8_BYTE8;
	U8 U8_BYTE9;
	U8 U8_BYTE10;
	U8 U8_BYTE11;

}ST_DID_SparePart_parameters_T;

extern ST_DID_SparePart_parameters_T ST_DID_SparePartNr_NVM_params;

extern const ST_DID_SparePart_parameters_T ST_DID_SparePartNr_NVM_default_params;

/* NvM parameters structure for DID ECU serial number */
typedef struct
{
	U8 U8_BYTE1;
	U8 U8_BYTE2;
	U8 U8_BYTE3;
	U8 U8_BYTE4;
	U8 U8_BYTE5;
	U8 U8_BYTE6;
	U8 U8_BYTE7;
	U8 U8_BYTE8;
	U8 U8_BYTE9;
	U8 U8_BYTE10;
	U8 U8_BYTE11;
	U8 U8_BYTE12;
	U8 U8_BYTE13;
	U8 U8_BYTE14;
	U8 U8_BYTE15;
	U8 U8_BYTE16;
	U8 U8_BYTE17;
	U8 U8_BYTE18;
	U8 U8_BYTE19;
	U8 U8_BYTE20;

}ST_DID_ECU_SerialNr_parameters_T;

extern ST_DID_ECU_SerialNr_parameters_T ST_DID_ECU_SerialNr_NVM_params;

extern  const ST_DID_ECU_SerialNr_parameters_T ST_DID_ECU_SerialNr_NVM_default_params;

/* NvM parameters structure for DID ECU hardware number */
typedef struct
{
	U8 U8_BYTE1;
	U8 U8_BYTE2;
	U8 U8_BYTE3;
	U8 U8_BYTE4;
	U8 U8_BYTE5;
	U8 U8_BYTE6;
	U8 U8_BYTE7;
	U8 U8_BYTE8;
	U8 U8_BYTE9;
	U8 U8_BYTE10;
	U8 U8_BYTE11;

}ST_DID_ECU_HardwareNr_parameters_T;

extern ST_DID_ECU_HardwareNr_parameters_T ST_DID_ECU_HardwareNr_NVM_params;

extern const ST_DID_ECU_HardwareNr_parameters_T ST_DID_ECU_HardwareNr_NVM_default_params;

/* NvM parameters structure for System_Supplier_ECU_Hardware_Number */
typedef struct
{
	U8 U8_BYTE1;
	U8 U8_BYTE2;
	U8 U8_BYTE3;
	U8 U8_BYTE4;
	U8 U8_BYTE5;
	U8 U8_BYTE6;
	U8 U8_BYTE7;
	U8 U8_BYTE8;
	U8 U8_BYTE9;
	U8 U8_BYTE10;
	U8 U8_BYTE11;

}ST_DID_SysSupplier_ECU_HardwareNr_parameters_T;

/* polyspace+1 MISRA-C3:5.1 [Not a defect:Low] "C99 standard is used to compile, Huf naming convention" */
extern ST_DID_SysSupplier_ECU_HardwareNr_parameters_T ST_DID_SysSupplier_ECU_HardwareNr_NVM_params;
/* polyspace < MISRA-C3:5.1 : Not a defect : Justify with annotations > C99 standard is used to compile, Huf naming convention */
extern const ST_DID_SysSupplier_ECU_HardwareNr_parameters_T ST_DID_SysSupplier_ECU_HardwareNr_NVM_default_params;

/* NvM parameters structure for SysNameOrEngineType */
typedef struct
{
	U8 U8_BYTE1;
	U8 U8_BYTE2;
	U8 U8_BYTE3;
	U8 U8_BYTE4;
	U8 U8_BYTE5;
	U8 U8_BYTE6;
	U8 U8_BYTE7;
	U8 U8_BYTE8;
	U8 U8_BYTE9;
	U8 U8_BYTE10;
	U8 U8_BYTE11;
	U8 U8_BYTE12;
	U8 U8_BYTE13;

}ST_DID_SysNameOrEngineType_parameters_T;
/* polyspace+2 MISRA-C3:8.6 [Justified:Low] "External declaration is needed" */
/* polyspace+1 MISRA-C3:5.1 [Not a defect:Low] "C99 standard is used to compile, Huf naming convention" */
extern ST_DID_SysNameOrEngineType_parameters_T ST_DID_SysNameOrEngineType_NVM_params;
/* polyspace < MISRA-C3:5.1 : Not a defect : Justify with annotations > C99 standard is used to compile, Huf naming convention */
extern const ST_DID_SysNameOrEngineType_parameters_T ST_DID_SysNameOrEngineType_NVM_default_params;
extern const ST_DID_SysNameOrEngineType_parameters_T SysNameOrEngineType_X564;

/* NvM parameters structure for DataSetNr */
typedef struct
{
	U8 U8_BYTE1;
	U8 U8_BYTE2;
	U8 U8_BYTE3;
	U8 U8_BYTE4;
	U8 U8_BYTE5;
	U8 U8_BYTE6;
	U8 U8_BYTE7;
	U8 U8_BYTE8;
	U8 U8_BYTE9;
	U8 U8_BYTE10;
	U8 U8_BYTE11;

}ST_DID_DataSetNr_parameters_T;

extern ST_DID_DataSetNr_parameters_T ST_DID_DataSetNr_NVM_params;

extern const ST_DID_DataSetNr_parameters_T ST_DID_DataSetNr_NVM_default_params;

/* NvM parameters structure for Data Set version number  */
typedef struct
{
	U8 U8_BYTE1;
	U8 U8_BYTE2;
	U8 U8_BYTE3;
	U8 U8_BYTE4;

}ST_DID_DataSetVersionNr_parameters_T;

extern ST_DID_DataSetVersionNr_parameters_T ST_DID_DataSetVersionNr_NVM_params;

extern const ST_DID_DataSetVersionNr_parameters_T ST_DID_DataSetVersionNr_NVM_default_params;

/* NvM parameters structure for Hardware version number */
typedef struct
{
	U8 U8_BYTE1;
	U8 U8_BYTE2;
	U8 U8_BYTE3;

}ST_DID_ECU_HardwareVersionNr_parameters_T;
/* polyspace+1 MISRA-C3:5.1 [Not a defect:Low] "C99 standard is used to compile, Huf naming convention" */
extern ST_DID_ECU_HardwareVersionNr_parameters_T ST_DID_ECU_HardwareVersionNr_NVM_params;
/* polyspace < MISRA-C3:5.1 : Not a defect : Justify with annotations > C99 standard is used to compile, Huf naming convention */
extern const ST_DID_ECU_HardwareVersionNr_parameters_T ST_DID_ECU_HardwareVersionNr_NVM_default_params;

/* NvM parameters structure for workshop system name  */
typedef struct
{
	U8 U8_BYTE1;
	U8 U8_BYTE2;
	U8 U8_BYTE3;
	U8 U8_BYTE4;
	U8 U8_BYTE5;

}ST_DID_WorkshopSystemName_parameters_T;

extern ST_DID_WorkshopSystemName_parameters_T ST_DID_WorkshopSystemName_NVM_params;

extern const ST_DID_WorkshopSystemName_parameters_T ST_DID_WorkshopSystemName_NVM_default_params;

/* NvM parameters structure for System Supplier Hardware version number */
typedef struct
{
	U8 U8_BYTE1;
	U8 U8_BYTE2;
	U8 U8_BYTE3;

}ST_DID_SysSupplier_ECU_HardwareVersionNr_parameters_T;
/* polyspace < MISRA-C3:5.1 : Not a defect : Justify with annotations > C99 standard is used to compile, Huf naming convention */
extern ST_DID_SysSupplier_ECU_HardwareVersionNr_parameters_T ST_DID_SysSupplier_ECU_HardwareVersionNr_NVM_params;
/* polyspace < MISRA-C3:5.1 : Not a defect : Justify with annotations > C99 standard is used to compile, Huf naming convention */
extern const ST_DID_SysSupplier_ECU_HardwareVersionNr_parameters_T ST_DID_SysSupplier_ECU_HardwareVersionNr_NVM_default_params;

/* NvM parameters structure for Data Set version number  */
typedef struct
{
	U8 U8_BYTE1;
	U8 U8_BYTE2;
	U8 U8_BYTE3;
	U8 U8_BYTE4;

}ST_DID_ProgrammingPreconditions_parameters_T;

/* polyspace+1 MISRA-C3:5.1 [Not a defect:Low] "C99 standard is used to compile, Huf naming convention" */
extern ST_DID_ProgrammingPreconditions_parameters_T ST_DID_ProgrammingPreconditions_NVM_params;
/* polyspace < MISRA-C3:5.1 : Not a defect : Justify with annotations > C99 standard is used to compile, Huf naming convention */
extern const ST_DID_ProgrammingPreconditions_parameters_T ST_DID_ProgrammingPreconditions_NVM_default_params;

/* NvM parameters structure for Data Set version number  */
typedef struct
{
	U8 U8_BYTE1;
	U8 U8_BYTE2;
	U8 U8_BYTE3;
	U8 U8_BYTE4;
	U8 U8_BYTE5;
	U8 U8_BYTE6;
	U8 U8_BYTE7;
	U8 U8_BYTE8;
	U8 U8_BYTE9;
	U8 U8_BYTE10;
	U8 U8_BYTE11;
	U8 U8_BYTE12;
	U8 U8_BYTE13;
	U8 U8_BYTE14;
	U8 U8_BYTE15;
	U8 U8_BYTE16;
	U8 U8_BYTE17;
	U8 U8_BYTE18;
	U8 U8_BYTE19;
	U8 U8_BYTE20;
	U8 U8_BYTE21;
	U8 U8_BYTE22;
	U8 U8_BYTE23;
	U8 U8_BYTE24;
	U8 U8_BYTE25;
	U8 U8_BYTE26;
	U8 U8_BYTE27;
	U8 U8_BYTE28;
	U8 U8_BYTE29;
	U8 U8_BYTE30;
	U8 U8_BYTE31;
	U8 U8_BYTE32;
	U8 U8_BYTE33;
	U8 U8_BYTE34;
	U8 U8_BYTE35;
	U8 U8_BYTE36;
	U8 U8_BYTE37;
	U8 U8_BYTE38;
	U8 U8_BYTE39;
	U8 U8_BYTE40;
	U8 U8_BYTE41;
	U8 U8_BYTE42;
	U8 U8_BYTE43;
	U8 U8_BYTE44;
	U8 U8_BYTE45;
	U8 U8_BYTE46;
	U8 U8_BYTE47;
	U8 U8_BYTE48;
	U8 U8_BYTE49;
	U8 U8_BYTE50;
	U8 U8_BYTE51;
	U8 U8_BYTE52;
	U8 U8_BYTE53;
	U8 U8_BYTE54;
	U8 U8_BYTE55;
	U8 U8_BYTE56;
	U8 U8_BYTE57;
	U8 U8_BYTE58;
	U8 U8_BYTE59;
	U8 U8_BYTE60;
	U8 U8_BYTE61;
	U8 U8_BYTE62;
	U8 U8_BYTE63;
	U8 U8_BYTE64;
	U8 U8_BYTE65;
	U8 U8_BYTE66;
	U8 U8_BYTE67;
	U8 U8_BYTE68;
	U8 U8_BYTE69;
	U8 U8_BYTE70;
	U8 U8_BYTE71;
	U8 U8_BYTE72;
	U8 U8_BYTE73;
	U8 U8_BYTE74;
	U8 U8_BYTE75;
	U8 U8_BYTE76;
	U8 U8_BYTE77;
	U8 U8_BYTE78;
	U8 U8_BYTE79;
	U8 U8_BYTE80;
	U8 U8_BYTE81;
	U8 U8_BYTE82;
	U8 U8_BYTE83;
	U8 U8_BYTE84;
	U8 U8_BYTE85;
	U8 U8_BYTE86;
	U8 U8_BYTE87;
	U8 U8_BYTE88;
	U8 U8_BYTE89;
	U8 U8_BYTE90;
	U8 U8_BYTE91;
	U8 U8_BYTE92;
	U8 U8_BYTE93;
	U8 U8_BYTE94;
	U8 U8_BYTE95;
	U8 U8_BYTE96;
	U8 U8_BYTE97;
	U8 U8_BYTE98;
	U8 U8_BYTE99;
	U8 U8_BYTE100;

}ST_DID_DID_System_Supplier_parameters_T;

extern const ST_DID_DID_System_Supplier_parameters_T ST_DID_System_Supplier_ID_NVM_default_params;

/* NvM parameters structure for NFC debug switch*/
typedef struct
{
	U8 U8_BYTE1;

}ST_DID_NFC_debugSwitch_parameters_T;
/* polyspace+1 MISRA-C3:8.6 [Justified:Low] "External declaration is needed" */
extern ST_DID_NFC_debugSwitch_parameters_T DID_NFC_debugSwitch_NVM_param;

extern const ST_DID_NFC_debugSwitch_parameters_T DID_NFC_debugSwitch_NVM_default_param;

/* NvM parameters structure for Homologation */
typedef struct
{
	U8 U8_BYTE1;

}ST_DID_Homologation_parameters_T;
/* polyspace+1 MISRA-C3:8.6 [Justified:Low] "External declaration is needed" */
extern ST_DID_Homologation_parameters_T DID_HomologationMode_NVM_param;

extern const ST_DID_Homologation_parameters_T DID_HomologationMode_NVM_default_param;

/* NvM parameters structure for EOL Done */
typedef struct
{
	U8 U8_BYTE1;
}ST_DID_Huf_EOL_Done_parameters_T;

typedef struct
{
    U8 U8_BYTE1;
    U8 U8_BYTE2;
    U8 U8_BYTE3;
    U8 U8_BYTE4;
    U8 U8_BYTE5;
    U8 U8_BYTE6;
    U8 U8_BYTE7;
    U8 U8_BYTE8;
    U8 U8_BYTE9;
    U8 U8_BYTE10;
    U8 U8_BYTE11;
    U8 U8_BYTE12;
    U8 U8_BYTE13;
    U8 U8_BYTE14;
    U8 U8_BYTE15;
}ST_DID_HUF_Production_Date_parameters_T;

typedef struct 
{
    U8 U8_BYTE1;
    U8 U8_BYTE2;
} ST_DID_Katek_EOL_Done_parameters_T;

/* NvM parameters structure for AUDI params */
typedef struct
{
    U8 U8_Byte_0_Audi_param_NVM;
    U8 U8_Byte_1_Audi_param_NVM;
    U8 U8_Byte_2_Audi_param_NVM;
    U8 U8_Byte_3_Audi_param_NVM;
    U8 U8_Byte_4_Audi_param_NVM;
    U8 U8_Byte_5_Audi_param_NVM;
    U8 U8_Byte_6_Audi_param_NVM;
    U8 U8_Byte_7_Audi_param_NVM;
    U8 U8_Byte_8_Audi_param_NVM;
    U8 U8_Byte_9_Audi_param_NVM;
    U8 U8_Byte_10_Audi_param_NVM;
    U8 U8_Byte_11_Audi_param_NVM;
    U8 U8_Byte_12_Audi_param_NVM;
    U8 U8_Byte_13_Audi_param_NVM;
    U8 U8_Byte_14_Audi_param_NVM;
    U8 U8_Byte_15_Audi_param_NVM;
    U8 U8_Byte_16_Audi_param_NVM;
    U8 U8_Byte_17_Audi_param_NVM;
    U8 U8_Byte_18_Audi_param_NVM;
    U8 U8_Byte_19_Audi_param_NVM;
    U8 U8_Byte_20_Audi_param_NVM;
    U8 U8_Byte_21_Audi_param_NVM;
    U8 U8_Byte_22_Audi_param_NVM;
    U8 U8_Byte_23_Audi_param_NVM;
    U8 U8_Byte_24_Audi_param_NVM;
    U8 U8_Byte_25_Audi_param_NVM;
    U8 U8_Byte_26_Audi_param_NVM;
    U8 U8_Byte_27_Audi_param_NVM;
    U8 U8_Byte_28_Audi_param_NVM;
    U8 U8_Byte_29_Audi_param_NVM;
    U8 U8_Byte_30_Audi_param_NVM;
    U8 U8_Byte_31_Audi_param_NVM;
    U8 U8_Byte_32_Audi_param_NVM;
    U8 U8_Byte_33_Audi_param_NVM;
    U8 U8_Byte_34_Audi_param_NVM;
    U8 U8_Byte_35_Audi_param_NVM;
    U8 U8_Byte_36_Audi_param_NVM;
    U8 U8_Byte_37_Audi_param_NVM;
    U8 U8_Byte_38_Audi_param_NVM;
    U8 U8_Byte_39_Audi_param_NVM;
    U8 U8_Byte_40_Audi_param_NVM;
    U8 U8_Byte_41_Audi_param_NVM;
    U8 U8_Byte_42_Audi_param_NVM;
    U8 U8_Byte_43_Audi_param_NVM;
    U8 U8_Byte_44_Audi_param_NVM;
    U8 U8_Byte_45_Audi_param_NVM;
    U8 U8_Byte_46_Audi_param_NVM;
    U8 U8_Byte_47_Audi_param_NVM;
    U8 U8_Byte_48_Audi_param_NVM;
    U8 U8_Byte_49_Audi_param_NVM;
}ST_AUDI_NVM_parameters_T;

typedef struct
{
    U16 PAR_TIME_NFC_DIAG_CYCLE_NORMAL;
	U16 PAR_TIME_NFC_DIAG_CYCLE_DEBOUNCE;
	U16 PAR_TIME_NFC_DIAG_CYCLE_FAIL_ACTIVE;
    U16 PAR_TIME_NFC_DIAG_POR_STARTUP;
    U16 PAR_TIME_NFC_DIAG_RETRY;
    U16 U16_NFC_BUFFER_PARAM_1;
    U16 U16_NFC_BUFFER_PARAM_2;
    U16 U16_NFC_BUFFER_PARAM_3;
    U16 U16_NFC_BUFFER_PARAM_4;
    U16 U16_NFC_BUFFER_PARAM_5;


}ST_TIME_NFC_DIAG_parameters_T;

extern ST_TIME_NFC_DIAG_parameters_T ST_TIME_NFC_DIAG_NVM_params;

extern const ST_TIME_NFC_DIAG_parameters_T ST_TIME_NFC_DIAG_NVM_default_params;

typedef struct
{
    U8 PAR_DIGIT_NFC_ANT_AMPL_OK_MIN;
    U8 PAR_DIGIT_NFC_ANT_AMPL_OK_MAX;
    U8 PAR_DIGIT_NFC_ANT_PHASE_OK_MIN;
    U8 PAR_DIGIT_NFC_ANT_PHASE_OK_MAX;
    U8 PAR_DIGIT_NFC_ANT_AMPL_SHORT_MIN;
    U8 PAR_DIGIT_NFC_ANT_AMPL_SHORT_MAX;
    U8 PAR_DIGIT_NFC_ANT_PHASE_SHORT_MIN;
    U8 PAR_DIGIT_NFC_ANT_PHASE_SHORT_MAX;
    U8 PAR_DIGIT_NFC_ANT_AMPL_OPEN_MIN;
    U8 PAR_DIGIT_NFC_ANT_AMPL_OPEN_MAX;
    U8 PAR_DIGIT_NFC_ANT_PHASE_OPEN_MIN;
    U8 PAR_DIGIT_NFC_ANT_PHASE_OPEN_MAX;
    U8 PAR_DIGIT_NFC_DEBOUCE_SPI_NOK;
    U8 PAR_DIGIT_NFC_DEBOUCE_TRCV_NOK;
    U8 PAR_DIGIT_NFC_DEBOUCE_OSC_NOK;
    U8 PAR_DIGIT_NFC_DEBOUCE_ANT_SHORT;
    U8 PAR_DIGIT_NFC_DEBOUCE_ANT_OPEN;
    U8 PAR_DIGIT_NFC_DEBOUCE_ANT_HEAV_DETUNED;
    U8 PAR_DIGIT_NFC_DEBOUCE_ANT_OK;
    U8 PAR_DIGIT_NFC_COMPLIANCE_MODE;
    U8 PAR_DIGIT_NFC_FRACTIONAL_DELTA_AMPL;
    U8 PAR_DIGIT_NFC_FRACTIONAL_DELTA_PHASE;
    U8 PAR_DIGIT_NFC_NFC_REGULATOR_VOLTAGE;
    U8 PAR_DIGIT_NFC_AVERAGING_RATE;
    U8 U8_NFC_BUFFER_PARAM_5;

}ST_DIGIT_NFC_parameters_T;

extern ST_DIGIT_NFC_parameters_T ST_DIGIT_NFC_NVM_params;
extern const ST_DIGIT_NFC_parameters_T ST_DIGIT_NFC_NVM_default_params;
extern const ST_AUDI_NVM_parameters_T ST_AUDI_NVM_default_params;
/* polyspace < MISRA-C3:8.6 : Not a defect : Justify with annotations > It has just one definition. The others are just declarations. */
extern ST_AUDI_NVM_parameters_T ST_AUDI_NVM_params;
extern const uint8 SFD_PersistentBuffer_Default_params[U8_SFDA_PERSISTENT_DATA_BUFFER_SIZE];
extern const uint8 SFD_LogData_Default_params[U8_SFDA_LOG_DATA_BUFFER_SIZE];
extern uint8 NVM_Sfd_Test_Mode_RAM;
extern uint8 NVM_Other_Sw_Version_Number_RAM[4];
extern uint8 ST_vehicle_identifier_NFC_NvM[8];
extern uint8 ST_vehicle_identifier_validity_NFC_NvM[1];

extern const uint8 NVM_Sfd_Test_Mode_Default;
extern const uint8 NVM_Other_Sw_Version_Number_Default[4];
extern const uint8 ST_vehicle_identifier_NFC_NvM_Default[8];
extern const uint8 ST_vehicle_identifier_validirty_NFC_NvM_Default[1];
extern U8 AU8_NVM_Fingerprint[9];
extern U8 AU8_NVM_Fingerprint_BL[9];
extern const U8 AU8_NVM_FingerprintDefault[9];
extern U8 AU8_NVM_AswProgAttemtsCnt[2];
extern U8 AU8_NVM_AswProgAttemtsCnt_BL[2];
extern const U8 AU8_NVM_AswProgAttemtsCntDefault[2];



extern ST_DID_HUF_Production_Date_parameters_T DID_HUF_Production_Date_NVM_param;
extern const ST_DID_HUF_Production_Date_parameters_T DID_HUF_Production_Date_NVM_default_param;

extern ST_DID_Katek_EOL_Done_parameters_T DID_Katek_EOL_Done_NVM_param;
extern const ST_DID_Katek_EOL_Done_parameters_T DID_Katek_EOL_Done_NVM_default_param;

extern ST_DID_Huf_EOL_Done_parameters_T DID_Huf_EOL_Done_NVM_param;
extern const ST_DID_Huf_EOL_Done_parameters_T DID_Huf_EOL_Done_NVM_default_param;


extern Std_ReturnType NFC_FS_DebugSwitch_BlockOperation_Callback (NvM_BlockIdType BlockId, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult);
extern Std_ReturnType NFC_HomologationModes_BlockOperation_Callback (NvM_BlockIdType BlockId, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult);
extern Std_ReturnType Audi_Params_BlockOperation_Callback (NvM_BlockIdType BlockId, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult);
extern Std_ReturnType Unlock_BlockOperation_Callback (NvM_BlockIdType BlockId, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult);
extern Std_ReturnType Lock_BlockOperation_Callback (NvM_BlockIdType BlockId, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult);
extern Std_ReturnType Other_HUF_BlockOperation_Callback (NvM_BlockIdType BlockId, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult);
extern Std_ReturnType Inductive_BlockOperation_Callback (NvM_BlockIdType BlockId, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult);
extern Std_ReturnType Emergency_BlockOperation_Callback (NvM_BlockIdType BlockId, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult);
extern Std_ReturnType FD02Spare_BlockOperation_Callback (NvM_BlockIdType BlockId, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult);
extern Std_ReturnType Battery_BlockOperation_Callback (NvM_BlockIdType BlockId, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult);
extern BOOL NvmMng_getEnableWakeUpByKessy(void);
extern BOOL NvmMng_getEnableWakeUpByNfc(void);
extern U8 NvmMng_getEnableKessyMisuseProtection(void);
extern U8 NvmMng_getEnableNFCMisuseProtection(void);
extern U8 NvmMng_getNFCMisuseProtectionPeak(void);
extern U8 NvmMng_getNFCMantainPlayProtValue(void);
extern U8 NvmMng_getNFCEnterPlayProtValue(void);

extern void SwVersionNumber_Updater(void);
#endif /* NVMMNG_H_ */
