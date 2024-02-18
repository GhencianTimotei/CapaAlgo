/*!
 * \defgroup  (sensor_aquisition_mcvd.asm)as_sensor_aquisition Main Program
 * \{
 ******************************************************************************
 * \image html
 *
 * \par Module Owner:
 *   Huf H&uuml;lsbeck & F&uuml;rst GmbH & Co. KG \n
 *   Steeger Str. 17 \n
 *   42551 Velbert \n
 *   Department PDES
 *
 * \par Initial Project:
 *   - 1508.008_380_ODH
 *
 ******************************************************************************
 * \par Description:
*  The MCVD  acquisition method works by sharing charge between the externel C-load capacitor
*  (Cl) and the sense electrode capacitance (Cs).
*  The charge sharing is carried out in the following sequence:
*  Step 1. Cl is shortly charged and connected in parallel with Cs . This causes charge to flow between the capacitors until
*  the charge is distributed completely between them.
 * Step1.1  Step 1. is repeated 40 times
*  Step 2. The voltage across Cs, due to the remaining charge, is digitized by the ADC (Sample A).
 * Step3. discharge both capacitors.
*  Step 4. Cs is shortly charged and connected in parallel with Cl . This causes charge to flow between the capacitors until
*  the charge is distributed completely between them.
 * Step4.1  Step 4. is reapeted 40 times
*  Step 4. The resulting voltage across Cs is digitized by the ADC (sample B).
*  The two ADC values sample A and sample B obtained are stored in the buffer.

*  When the sensor is touched the effective capacitance of the sensor electrode increases and becomes Cx + Ct. This
*  affects the amount of charge shared between the capacitors.
*  When pre-charging Cs and sharing with Cl,charge remaining on Cs decreases on touch and ADC input voltage decreases ,sample A take decreases value
*  When pre-charging Cl and sharing with Cs, charge transferred to Cs increases on touch and ADC input voltage increases.sample B take increases value
 *
 ******************************************************************************
 *
 *  $Workfile:   sensor_aquisition_mcvd.h  $
 *  $Revision:   1.3  $
 *  $Date::   May 14 2018 16:29:24  $
 *  $Author:   ybadal  $
 *
 ******************************************************************************
 *
 * \par Purpose:
 *    OS, main part of operation system
 *
 * \par Compiler:
 *    ANSI, GHS specific pragmas for interrupt handling
 *
 * \par Controller:
 *    -
 *
 * \res_start
 *    \res_item{ROM,             0 kByte, }
 *    \res_item{RAM,             0  Byte, }
 *    \res_item{EEPROM,          0 Byte , }
 *    \res_item{Runtime Init,    X ms   , }
 *    \res_item{Runtime Task,    X ms   , }
 * \res_end
 *
 *
 * \qual_start
 *    \qual_item{Maintainability,   0,  0,  0,  0}
 *    \qual_item{Analyzeability ,   0,  0,  0,  0}
 *    \qual_item{Changeability  ,   0,  0,  0,  0}
 *    \qual_item{Stability      ,   0,  0,  0,  0}
 *    \qual_item{Testability    ,   0,  0,  0,  0}
 * \qual_end
 *
 * \par MISRA rules violations:
 *   \li t.b.d.
 *
 ******************************************************************************
 *
 * \attention
 *   the sensor result is stored in the buffer _S_LockRaw,_S_UnlockRaw
 *
 ******************************************************************************
 *
 * \par Changes:
 *
 *
 ******************************************************************************/
#ifdef INTEGRATE_FROM_V4
#include "../../../MOD_SERV_PROG_FRAME/Source/config.h"
#endif

/*------------------------------------------------------------------------
MACRO       : STRING_JOIN
Author      : ybadal
Input       : a: first string ,b : second string
Description :  Use this macro to concatenate 2 strings in the pre-compiler
------------------------------------------------------------------------*/
#define STRING_JOIN(a,b)   a##b
#define HASH #
#define CONST_VAL(a)    STRING_JOIN(HASH,a)

/* Bit definitions*/
#ifndef BIT0
	#define BIT0        (0x01u)
#endif
#ifndef BIT1
	#define BIT1        (0x02u)
	#endif
#ifndef BIT2
	#define BIT2        (0x04u)
#endif
#ifndef BIT3
	#define BIT3        (0x08u)
#endif
#ifndef BIT4
	#define BIT4        (0x10u)
#endif
#ifndef BIT5
	#define BIT5        (0x20u)
#endif
#ifndef BIT6
	#define BIT6        (0x40u)
#endif
#ifndef BIT7
	#define BIT7        (0x80u)
#endif

/*------------------------------------------------------------------------
MACRO       : UNLOCK_SENSOR_DIRECTION_GPIO
Author      : ybadal
Input       :
Description :  Specify the port direction register for lock sensor
------------------------------------------------------------------------*/
#define UNLOCK_SENSOR_DIRECTION_GPIO  PM8    /* lock trisc register */
/*------------------------------------------------------------------------
MACRO       : UNLOCK_SENSOR_LEVEL_GPIO
Author      : ybadal
Input       :
Description :  Specify the port level register for unlock sensor
------------------------------------------------------------------------*/
#define UNLOCK_SENSOR_LEVEL_GPIO      P8     /* lock lat register */
/*------------------------------------------------------------------------
MACRO       : U8_REF_N_AD_CHANNEL
Author      : ybadal
Input       :
Description :  Specify the adc channel to connect the adc to ground
------------------------------------------------------------------------*/
#define U8_REF_N_AD_CHANNEL                   STRING_JOIN(#,4) /* ADC MUX on gnd reference (ANI3=P8.1)*/
/*------------------------------------------------------------------------
MACRO       : U8_REF_P_AD_CHANNEL
Author      : ybadal
Input       :
Description :  Specify the adc channel to connect the adc to vdd
------------------------------------------------------------------------*/
#define U8_REF_P_AD_CHANNEL                   STRING_JOIN(#,3) /* ADC MUX on vdd reference (ANI2=P8.0)*/
/*------------------------------------------------------------------------
MACRO       : U8_UNLOCK_AD_CHANNEL
Author      : ybadal
Input       :
Description :  Specify the adc channel for unlock sensor
------------------------------------------------------------------------*/
#define U8_UNLOCK_AD_CHANNEL                  STRING_JOIN(#,5) /* ADC MUX on unlock electrode (ANI5=P8.3)*/

/*------------------------------------------------------------------------
MACRO       : U8_UNLOCK_C_LOAD_AD_CHANNEL
Author      : ybadal
Input       :
Description :  Specify the adc channel for unlock cload sensor
------------------------------------------------------------------------*/
#define U8_UNLOCK_C_LOAD_AD_CHANNEL           STRING_JOIN(#,4) /* ADC MUX on unlock electrode (ANI4=P8.2)*/
/*------------------------------------------------------------------------
MACRO       : UNLOCK_SHIELD1_PIN
Author      : ybadal
Input       :
Description :  Specify the pin number  for active shield 1
------------------------------------------------------------------------*/
#define UNLOCK_SHIELD1_PIN                    BIT1
/*------------------------------------------------------------------------
MACRO       : UNLOCK_SHIELD0_PIN
Author      : ybadal
Input       :
Description :  Specify the pin number  for active shield 0
------------------------------------------------------------------------*/
#define UNLOCK_SHIELD0_PIN                     BIT0
/*------------------------------------------------------------------------
MACRO       : UNLOCK_C_MCVD_SENSE_PIN
Author      : ybadal
Input       :
Description :  Specify the pin number  for unlock sensor
------------------------------------------------------------------------*/
#define UNLOCK_C_MCVD_SENSE_PIN                    BIT3 /*unlock c sense port pin position */
/*------------------------------------------------------------------------
MACRO       : UNLOCK_C_MCVD_LOAD_PIN
Author      : ybadal
Input       :
Description :  Specify the pin number  for unlock cload  sensor
------------------------------------------------------------------------*/
#define UNLOCK_C_MCVD_LOAD_PIN                     BIT2 /*unlock c load  port pin position */
/* parameter for lock sensor*/
/*------------------------------------------------------------------------
MACRO       : LOCK_SENSOR_DIRECTION_GPIO
Author      : ybadal
Input       :
Description :  Specify the port direction register for lock sensor
------------------------------------------------------------------------*/
#define BOTH_SENSOR_DIRECTION_GPIO  PM8    /* lock trisc register */
/*------------------------------------------------------------------------
MACRO       : LOCK_SENSOR_LEVEL_GPIO
Author      : ybadal
Input       :
Description :  Specify the port level register for lock sensor
------------------------------------------------------------------------*/
#define BOTH_SENSOR_LEVEL_GPIO      P8     /* lock lat register */

/*------------------------------------------------------------------------
MACRO       : LOCK_SHIELD1_DIRECTION_GPIO
Author      : ybadal
Input       :
Description :  Specify the pin number  for lock sensor active shield 1
------------------------------------------------------------------------*/
#define LOCK_SHIELD1_DIRECTION_GPIO              PM8
/*------------------------------------------------------------------------
MACRO       : LOCK_SHIELD1_LEVEL_GPIO
Author      : ybadal
Input       :
Description :  Specify the pin number  for lock sensor active shield 0
------------------------------------------------------------------------*/
#define LOCK_SHIELD1_LEVEL_GPIO              P8
/*------------------------------------------------------------------------
MACRO       : LOCK_SHIELD0_DIRECTION_GPIO
Author      : ybadal
Input       :
Description :  Specify the pin number  for lock sensor active shield 1
------------------------------------------------------------------------*/
#define LOCK_SHIELD0_DIRECTION_GPIO              PM8
/*------------------------------------------------------------------------
MACRO       : LOCK_SHIELD0_LEVEL_GPIO
Author      : ybadal
Input       :
Description :  Specify the port name  for  sensor active shield 0
------------------------------------------------------------------------*/
#define LOCK_SHIELD0_LEVEL_GPIO              P8
/*------------------------------------------------------------------------
MACRO       : LOCK_SHIELD1_PIN
Author      : ybadal
Input       :
Description :  Specify the pin number  for lock sensor active shield 1
------------------------------------------------------------------------*/
#define LOCK_SHIELD1_PIN              BIT1
/*------------------------------------------------------------------------
MACRO       : LOCK_SHIELD0_PIN
Author      : ybadal
Input       :
Description :  Specify the pin number  for lock sensor active shield 0
------------------------------------------------------------------------*/
#define LOCK_SHIELD0_PIN              BIT0
/*------------------------------------------------------------------------
MACRO       : LOCK_C_MCVD_SENSE_PIN
Author      : ybadal
Input       :
Description :  Specify the pin number  for unlock  sensor
------------------------------------------------------------------------*/
#define LOCK_C_MCVD_SENSE_PIN                    BIT7    /*lock c sense port pin position */
/*------------------------------------------------------------------------
MACRO       : LOCK_C_MCVD_SENSE_PIN
Author      : ybadal
Input       :
Description :  Specify the pin number  for unlock  cload sensor
------------------------------------------------------------------------*/
#define LOCK_C_MCVD_LOAD_PIN                     BIT6    /*lock c load  port pin position */

/*------------------------------------------------------------------------
MACRO       : U8_LOCK_C_LOAD_AD_CHANNEL
Author      : ybadal
Input       :
Description :  Specify the adc channel for lock cload sensor
------------------------------------------------------------------------*/
#define U8_LOCK_C_LOAD_AD_CHANNEL             STRING_JOIN(#,8) /* ADC MUX on lock electrode (ANI9=P8.7)*/
/*------------------------------------------------------------------------
MACRO       : U8_LOCK_AD_CHANNEL
Author      : ybadal
Input       :
Description :  Specify the adc channel for lock sensor
------------------------------------------------------------------------*/
#define U8_LOCK_AD_CHANNEL                    STRING_JOIN(#,9) /* ADC MUX on lock electrode (ANI8=P8.6)*/

#ifndef VARIANT_1
	/*------------------------------------------------------------------------
	MACRO       : BOTH_SENSOR_ALL_PINS
	Author      : hcostin
	Input       :
	Description :  mask to toggle csense,cload and active shield
	------------------------------------------------------------------------*/
	#define BOTH_SENSOR_ALL_PINS	CONST_VAL(LOCK_C_MCVD_LOAD_PIN | LOCK_C_MCVD_SENSE_PIN| LOCK_SHIELD1_PIN | LOCK_SHIELD0_PIN | UNLOCK_C_MCVD_LOAD_PIN | UNLOCK_C_MCVD_SENSE_PIN | UNLOCK_SHIELD1_PIN | UNLOCK_SHIELD0_PIN)
	
	/*------------------------------------------------------------------------
	MACRO       : BOTH_SENSOR_ALL_PINS_NEG
	Author      : hcostin
	Input       :
	Description :  mask to turn off csense,cload and active shield
	------------------------------------------------------------------------*/
	#define BOTH_SENSOR_ALL_PINS_NEG	CONST_VAL(~(LOCK_C_MCVD_LOAD_PIN | LOCK_C_MCVD_SENSE_PIN| LOCK_SHIELD1_PIN | LOCK_SHIELD0_PIN | UNLOCK_C_MCVD_LOAD_PIN | UNLOCK_C_MCVD_SENSE_PIN | UNLOCK_SHIELD1_PIN | UNLOCK_SHIELD0_PIN))
	
	/*------------------------------------------------------------------------
	MACRO       : BOTH_HBL
	Author      : hcostin
	Input       :
	Description :  mask to toggle cload
	------------------------------------------------------------------------*/
	#define BOTH_HBL	(LOCK_C_MCVD_LOAD_PIN | UNLOCK_C_MCVD_LOAD_PIN)
	
	/*------------------------------------------------------------------------
	MACRO       : BOTH_HBR
	Author      : hcostin
	Input       :
	Description :  mask to toggle csense
	------------------------------------------------------------------------*/
	#define BOTH_HBR	(LOCK_C_MCVD_SENSE_PIN | UNLOCK_C_MCVD_SENSE_PIN)
	
	/*------------------------------------------------------------------------
	MACRO       : BOTH_SHIELD0
	Author      : hcostin
	Input       :
	Description :  mask to toggle shield0
	------------------------------------------------------------------------*/
	#define BOTH_SHIELD0	(LOCK_SHIELD0_PIN | UNLOCK_SHIELD0_PIN)
	
	/*------------------------------------------------------------------------
	MACRO       : BOTH_SHIELD1
	Author      : hcostin
	Input       :
	Description :  mask to toggle shield1
	------------------------------------------------------------------------*/
	#define BOTH_SHIELD1	(LOCK_SHIELD1_PIN | UNLOCK_SHIELD1_PIN)
#else
	#define BOTH_SENSOR_ALL_PINS	CONST_VAL(UNLOCK_C_MCVD_LOAD_PIN | UNLOCK_C_MCVD_SENSE_PIN)
	#define BOTH_SENSOR_ALL_PINS_NEG	CONST_VAL(~(UNLOCK_C_MCVD_LOAD_PIN | UNLOCK_C_MCVD_SENSE_PIN))
	#define BOTH_HBL	(UNLOCK_C_MCVD_LOAD_PIN)
	#define BOTH_HBR	(UNLOCK_C_MCVD_SENSE_PIN)
	#define BOTH_SHIELD0	0u
	#define BOTH_SHIELD1	0u
#endif


/* Automatic logging by PVCS ***********************************************
$Log::   J:/vmfs/VW/1508.008_380_ODH/archives/3_Coding/ECU_NFC_STACK-NXP/MCU_RL78/MOD_SERV_CAPA_SENSOR/MOD_SERV_MCVD$
 * 
 *    Rev 1.3   May 14 2018 16:29:24   ybadal
 * add compiler switch to optimize the code in case that mcvd not used.
 * 
 * 
 * *** */
