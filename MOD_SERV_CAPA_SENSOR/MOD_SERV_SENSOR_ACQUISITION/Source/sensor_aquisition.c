/*!
 * \defgroup  (sensor_aquisition.c) Main Program
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
 *
 * sensor acquisition layer ,depend on  Which measurement unit is active perform the cvd
 * or the mcvd measurement.
 *
 ******************************************************************************
 *
 *  $Workfile:   sensor_aquisition.c  $
 *  $Revision:   1.5  $
 *  $Date::   Nov 29 2018 13:09:38  $
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
 *   \li -
 *
 ******************************************************************************
 *
 * \par Changes:
 ******************************************************************************/
#ifndef SENSOR_AQUISITION_C
#define SENSOR_AQUISITION_C

#ifdef INTEGRATE_FROM_V4
#include "std_inc.h"
#endif
#ifndef INTEGRATE_FROM_V4
#include "Platform_Types.h"
#endif
#include "sensor_aquisition.h"
#ifdef INTEGRATE_FROM_V4
/* Provide ADC interface*/
#include "Adc.h"
/* Provide gpt interface */
#include "Gpt.h"
#endif
/* Provide interface */
#include "Dio.h"
#include "Port.h"
#ifndef INTEGRATE_FROM_V4
#include "IntegrationTests.h"
#endif
#include "sensor_acquisition_mcvd.h"

#define HIGH       1
#define LOW        0

/* Compensation values for sensor readings in normal/active mode */
const U16 U16_Lock_A_Raw_Manipulation = (U16)4;
const U16 U16_Lock_B_Raw_Manipulation = (U16)8;
const U16 U16_Unlock_A_Raw_Manipulation = (U16)5;
const U16 U16_Unlock_B_Raw_Manipulation = (U16)5;

void SensorAquisition_Compensation(void);

/*!
******************************************************************************
* \brief
* Sensor_aquisition_init
*
* \details
* @ingroup sensor aquisition
*  initialisition of the both sensor after pon.
******************************************************************************
*
* \sync          synchronous (function done in one pass)
* \reent         non reentrant
*
* \pre           all must be initialized.
* \post          process is started
*
* \param[in]     void
* \param[in]
*
* \glob_start
* \glob_end
*
* \retval         void
******************************************************************************
*
* \author        Ybadal
* \version       1.0
* \date          15.09.2015
*
******************************************************************************
*
* \par Change history:
*       -
*
******************************************************************************
*
* \par Remarks:
* the GPT_Delay() macros is using to realise the equidistant sampling of A and B .
*
******************************************************************************/
SENSOR_AQ_EXPORT void Sensor_aquisition_init(void)
{
#ifdef INTEGRATE_FROM_V4
    ADPC = ADC_ALL_DIGITAL;

    DIO_SET_PORT(LOCK_ACTIVE_SHIELD0_PORT,UNLOCK_ACTIVE_SHIELD0_PIN,OUTPUT);
    DIO_SET_PIN(LOCK_ACTIVE_SHIELD0_PORT,UNLOCK_ACTIVE_SHIELD0_PIN,LOW);
    DIO_SET_PORT(UNLOCK_ACTIVE_SHIELD1_PORT,UNLOCK_ACTIVE_SHIELD1_PIN,OUTPUT);
    DIO_SET_PIN(UNLOCK_ACTIVE_SHIELD1_PORT,UNLOCK_ACTIVE_SHIELD1_PIN,LOW);

    DIO_SET_PORT(LOCK_ACTIVE_SHIELD0_PORT,LOCK_ACTIVE_SHIELD0_PIN,OUTPUT);
    DIO_SET_PIN(LOCK_ACTIVE_SHIELD0_PORT,LOCK_ACTIVE_SHIELD0_PIN,LOW);
    DIO_SET_PORT(LOCK_ACTIVE_SHIELD1_PORT,LOCK_ACTIVE_SHIELD1_PIN,OUTPUT);
    DIO_SET_PIN(LOCK_ACTIVE_SHIELD1_PORT,LOCK_ACTIVE_SHIELD1_PIN,LOW);
#endif
}

/*!
******************************************************************************
* \brief
* Get_Sensor_Scan_ER
*
* \details
* @ingroup sensor aquisition
*  this is the interface to get the values of the lock sensor aquisition CVD or MCVD.
******************************************************************************
*
* \sync          synchronous (function done in one pass)
* \reent         non reentrant
*
* \pre           all must be initialized.
* \post          process is started
*
* \param[in]     void
*
* \glob_start	SXValue[U8_SENSOR_OVERSAMPLING_LOOP]: buffer to store the ADC Result from sample A and sample B
* \glob_end
*
* \retval         SENSOR_MEASURE_VALUE_T*  : pointer to SXValue
******************************************************************************
*
* \author        hcostin
* \version       1.0
* \date          11.03.2021
*
******************************************************************************
*
* \par Change history:
*       -
*
******************************************************************************
*
* \par Remarks:
*
******************************************************************************/
SENSOR_AQ_EXPORT SENSOR_MEASURE_VALUE_T* Get_Sensor_Scan_ER(void)
{
    return &S_UnlockRaw_ASM;
}

/*!
******************************************************************************
* \brief
* SensorAqc_Init_Hw_both
*
* \details
* @ingroup sensor aquisition
*  initialisition of the lock sfr register.
******************************************************************************
*
* \sync          synchronous (function done in one pass)
* \reent         non reentrant
*
* \pre           all must be initialized.
* \post          process is started
*
* \param[in]     void
* \param[in]
*
* \glob_start
* \glob_end
*
* \retval         void
******************************************************************************
*
* \author        Ybadal
* \version       1.0
* \date          15.09.2015
*
******************************************************************************
*
* \par Change history:
*       -
*
******************************************************************************
*
* \par Remarks:
*
******************************************************************************/
static void SensorAqc_Init_Hw_both(void)
{
#ifdef INTEGRATE_FROM_V4
    ADPC = ADC_ALL_DIGITAL;

    DIO_SET_PORT(ER_SENSOR_GPIO,ER_PIN,OUTPUT);
    DIO_SET_PIN(ER_SENSOR_GPIO,ER_PIN,LOW);
    DIO_SET_PORT(VR_SENSOR_GPIO,VR_PIN,OUTPUT);
    DIO_SET_PIN(VR_SENSOR_GPIO,VR_PIN,LOW);

    DIO_SET_PORT(LOCK_ACTIVE_SHIELD1_PORT,LOCK_ACTIVE_SHIELD1_PIN,OUTPUT);
    DIO_SET_PIN(LOCK_ACTIVE_SHIELD1_PORT,LOCK_ACTIVE_SHIELD1_PIN,LOW);
    DIO_SET_PORT(LOCK_ACTIVE_SHIELD0_PORT,LOCK_ACTIVE_SHIELD0_PIN,OUTPUT);
    DIO_SET_PIN(LOCK_ACTIVE_SHIELD0_PORT,LOCK_ACTIVE_SHIELD0_PIN,LOW);

    #ifdef UNLOCK_DIFFERENT_ACTIVE_SHIELDS
        DIO_SET_PORT(UNLOCK_ACTIVE_SHIELD1_PORT,UNLOCK_ACTIVE_SHIELD1_PIN,OUTPUT);
        DIO_SET_PIN(UNLOCK_ACTIVE_SHIELD1_PORT,UNLOCK_ACTIVE_SHIELD1_PIN,LOW);
        DIO_SET_PORT(UNLOCK_ACTIVE_SHIELD0_PORT,UNLOCK_ACTIVE_SHIELD0_PIN,OUTPUT);
        DIO_SET_PIN(UNLOCK_ACTIVE_SHIELD0_PORT,LOCK_ACTIVE_SHIELD0_PIN,LOW);
    #endif

    DIO_SET_PORT(UNLOCK_C_LOAD_PORT,UNLOCK_C_LOAD_PIN,OUTPUT);
    DIO_SET_PIN(UNLOCK_C_LOAD_PORT,UNLOCK_C_LOAD_PIN,LOW);

    DIO_SET_PORT(LOCK_C_LOAD_PORT,LOCK_C_LOAD_PIN,OUTPUT);
    DIO_SET_PIN(LOCK_C_LOAD_PORT,LOCK_C_LOAD_PIN,LOW);
#endif
}

/*!
******************************************************************************
* \brief
* SensorAcq_reset_Hw_both
*
* \details
* @ingroup sensor aquisition
*  reset  the lock sfr register.
******************************************************************************
*
* \sync          synchronous (function done in one pass)
* \reent         non reentrant
*
* \pre           all must be initialized.
* \post          process is started
*
* \param[in]     void
* \param[in]
*
* \glob_start
* \glob_end
*
* \retval         void
******************************************************************************
*
* \author        Ybadal
* \version       1.0
* \date          15.09.2015
*
******************************************************************************
*
* \par Change history:
*       -
*
******************************************************************************
*
* \par Remarks:
*
******************************************************************************/
static void SensorAcq_reset_Hw_both(void)
{
#ifdef INTEGRATE_FROM_V4
    DIO_SET_PORT(ER_SENSOR_GPIO,ER_PIN,OUTPUT);
    DIO_SET_PIN(ER_SENSOR_GPIO,ER_PIN,LOW);
    DIO_SET_PORT(VR_SENSOR_GPIO,VR_PIN,OUTPUT);
    DIO_SET_PIN(VR_SENSOR_GPIO,VR_PIN,LOW);

    DIO_SET_PORT(LOCK_ACTIVE_SHIELD1_PORT,LOCK_ACTIVE_SHIELD1_PIN,OUTPUT);
    DIO_SET_PIN(LOCK_ACTIVE_SHIELD1_PORT,LOCK_ACTIVE_SHIELD1_PIN,LOW);
    DIO_SET_PORT(LOCK_ACTIVE_SHIELD0_PORT,LOCK_ACTIVE_SHIELD0_PIN,OUTPUT);
    DIO_SET_PIN(LOCK_ACTIVE_SHIELD0_PORT,LOCK_ACTIVE_SHIELD0_PIN,LOW);

    #ifdef UNLOCK_DIFFERENT_ACTIVE_SHIELDS
        DIO_SET_PORT(UNLOCK_ACTIVE_SHIELD0_PORT,UNLOCK_ACTIVE_SHIELD0_PIN,OUTPUT);
        DIO_SET_PIN(UNLOCK_ACTIVE_SHIELD0_PORT,UNLOCK_ACTIVE_SHIELD0_PIN,LOW);
        DIO_SET_PORT(UNLOCK_ACTIVE_SHIELD1_PORT,UNLOCK_ACTIVE_SHIELD1_PIN,OUTPUT);
        DIO_SET_PIN(UNLOCK_ACTIVE_SHIELD1_PORT,UNLOCK_ACTIVE_SHIELD1_PIN,LOW);
    #endif
    /*ADPC = 0x0Bu;*/
#endif
}
/*!
******************************************************************************
* \brief
* Get_Sensor_Scan_VR
*
* \details
* @ingroup sensor aquisition
*  this is the interface to get the values of the lock sensor aquisition CVD or MCVD.
******************************************************************************
*
* \sync          synchronous (function done in one pass)
* \reent         non reentrant
*
* \pre           all must be initialized.
* \post          process is started
*
* \param[in]     void
* \param[in]
*
* \glob_start	SXValue[U8_SENSOR_OVERSAMPLING_LOOP] buffer to store the ADC Result from sample A and sample B
* \glob_end
*
* \retval         SENSOR_MEASURE_VALUE_T*  : pointer to SXValue
******************************************************************************
*
* \author        hcostin
* \version       1.0
* \date          11.03.2021
*
******************************************************************************
*
* \par Change history:
*       -
*
******************************************************************************
*
* \par Remarks:
*       -
*
******************************************************************************/
SENSOR_AQ_EXPORT SENSOR_MEASURE_VALUE_T*  Get_Sensor_Scan_VR(void)
{
 return &S_LockRaw_ASM;
}

/*!
******************************************************************************
* \brief
* Sensor_Scan_Both
*
* \details
* @ingroup sensor aquisition
*  this is the interface to call the lock and unclok sensors aquisition MECVD.
******************************************************************************
*
* \sync          synchronous (function done in one pass)
* \reent         non reentrant
*
* \pre           all must be initialized.
* \post          process is started
*
* \param[in]     void
*
* \glob_start   SXValue[U8_SENSOR_OVERSAMPLING_LOOP]: buffer to store the ADC Result from sample A and sample B
* \glob_end
*
* \retval         SENSOR_MEASURE_VALUE_T*  : pointer to SXValue
******************************************************************************
*
* \author        hcostin
* \version       1.0
* \date          11.03.2021
*
******************************************************************************
*
* \par Change history:
*       -
*
******************************************************************************
*
* \par Remarks:
*
******************************************************************************/
void  Sensor_Scan_Both(void)
{
    /* polyspace < MISRA-C3:2.2 : Not a defect : Justify with annotations > Should be kept for future usage */
    SensorAqc_Init_Hw_both();
    /* polyspace<MISRA-C3:17.7 : Not a defect : Justify with annotations >  ASM function does not have return type; checked by developer*/
    Sensor_task_acquisition();
    SensorAquisition_Compensation();
    /* polyspace < MISRA-C3:2.2 : Not a defect : Justify with annotations > Should be kept for future usage */
    SensorAcq_reset_Hw_both();
}

/*!
******************************************************************************
* \brief
* Sensor_Scan_Both
*
* \details
* @ingroup sensor aquisition
*  this is the interface to call the lock and unclok sensors aquisition MECVD.
******************************************************************************
*
* \sync          synchronous (function done in one pass)
* \reent         non reentrant
*
* \pre           all must be initialized.
* \post          process is started
*
* \param[in]     void
*
* \glob_start   SXValue[U8_SENSOR_OVERSAMPLING_LOOP]: buffer to store the ADC Result from sample A and sample B
* \glob_end
*
* \retval         SENSOR_MEASURE_VALUE_T*  : pointer to SXValue
******************************************************************************
*
* \author        hcostin
* \version       1.0
* \date          11.03.2021
*
******************************************************************************
*
* \par Change history:
*       -
*
******************************************************************************
*
* \par Remarks:
*
******************************************************************************/
/* polyspace < MISRA-C3:8.4,8.5 : Not a defect : Justify with annotations > External Usage dependent on project setup */
void  Sensor_Scan_Both_LP(void)
{
    /* polyspace < MISRA-C3:2.2 : Not a defect : Justify with annotations > Should be kept for future usage */
    SensorAqc_Init_Hw_both();
    /* polyspace<MISRA-C3:17.7 : Not a defect : Justify with annotations >  ASM function does not have return type; checked by developer*/
   /* polyspace < MISRA-C3:8.3 : Not a defect : Justify with annotations > Function use the same names and type */
   /* polyspace < MISRA-C3:17.3: Not a defect : Justify with annotations > Function prototype is in Can.c */
    Sensor_task_acquisition_LP();
    /* polyspace < MISRA-C3:2.2 : Not a defect : Justify with annotations > Should be kept for future usage */
    SensorAcq_reset_Hw_both();
}

/*****************************************************************************
 * Description: Manipulate sensor values in normal mode (apply offset) in order
 *              to compensate for different readings due to increased current
 *              consumption (compared to low-power mode).
******************************************************************************/
void SensorAquisition_Compensation(void)
{
    /* Lock sensor - A sample */
    if ((U16)(S_LockRaw_ASM.U16_Sensor_SA_Value - U16_Lock_A_Raw_Manipulation) <= S_LockRaw_ASM.U16_Sensor_SA_Value)  /* Negative overflow check */
    {
        S_LockRaw_ASM.U16_Sensor_SA_Value -= U16_Lock_A_Raw_Manipulation;
    }
    else
    {
        S_LockRaw_ASM.U16_Sensor_SA_Value = (U16)0x0000u;
    }

    /* UnLock sensor - A sample */
    if ((U16)(S_UnlockRaw_ASM.U16_Sensor_SA_Value - U16_Unlock_A_Raw_Manipulation) <= S_UnlockRaw_ASM.U16_Sensor_SA_Value)  /* Negative overflow check */
    {
        S_UnlockRaw_ASM.U16_Sensor_SA_Value -= U16_Unlock_A_Raw_Manipulation;
    }
    else
    {
        S_UnlockRaw_ASM.U16_Sensor_SA_Value = (U16)0x0000u;
    }

    /* Lock sensor - B sample */
    S_LockRaw_ASM.U16_Sensor_SB_Value += U16_Lock_B_Raw_Manipulation;  /* No overflow check needed as ADC resolution is 12 bit and offset is fixed (3-4 bit) */

    /* UnLock sensor - B sample */
    S_UnlockRaw_ASM.U16_Sensor_SB_Value += U16_Unlock_B_Raw_Manipulation;  /* No overflow check needed as ADC resolution is 12 bit and offset is fixed (3-4 bit) */
}

#endif 
/* Automatic logging by PVCS ***********************************************

$Log::   J:/vmfs/VW/1508.008_380_ODH/archives/3_Coding/ECU_NFC_STACK-NXP/MCU_RL78/MOD_SERV_CAPA_SENSOR/MOD_SERV_SENSOR_AQUISITION/Source/s$
 * 
 *    Rev 1.5   Nov 29 2018 13:09:38   ybadal
 * add passive shield for VW_316 variant HW.
 * 
 *    Rev 1.4   Sep 06 2018 13:45:46   ybadal
 * neu active shield sequence implemented.
 * 
 *    Rev 1.3   Jul 09 2018 11:30:54   ybadal
 * remove first sensor raw value due to corrupted behaviour.
 * 
 *    Rev 1.2   Feb 26 2018 13:33:04   ybadal
 * - remove some defines
 * 
 *    Rev 1.1   10 Jan 2018 15:55:28   ybadal
 * - sensor cvd for HW revision 04 fixed.
 * 
 *    Rev 1.0   Sep 22 2017 16:12:14   Sbhanda
 * Initial revision.
 * 
 *    Rev 1.2   Aug 11 2017 09:47:10   ybadal
 * use set channel interface from mcal adc module
 * 
 *    Rev 1.1   Aug 08 2017 09:29:50   ybadal
 * - functions for cvd measurement for lock and unlock are moved to the module MOD_SERV_CVD_SENSOR_AQUISITION
 * - the both measurement principal cvd and mcvd are now implemented and can be activated by the define USED_SENSOR_MEASUREMENT_PRINCIPLE
 * - rename some functions to identify the cvd from mcvd measurement process.
 * 
 *    Rev 1.9   22 Dec 2015 16:39:28   ybadal
 * moduls and functions Headers changed to HUF standard header.
 * 
 *    Rev 1.8   17 Nov 2015 14:43:02   omuelle
 * forced correct timings by forcing memory addresses
 * 
 *    Rev 1.7   12 Nov 2015 16:58:22   omuelle
 * corrected order of time slices
 * 
 *    Rev 1.6   04 Nov 2015 08:56:02   ybadal
 * general noise detection implemented.
 * 
 *    Rev 1.5   28 Oct 2015 15:11:34   ybadal
 * - Bug fix for ADC On Time.
 * - new disturbance analyse :
 *    - examination of delta A - B
 *    - examination of delta A +B
 *    - examination of A+B 
 * 
 *    Rev 1.4   22 Oct 2015 17:03:18   ybadal
 * due to IIR overflow :
 * - Dittering disabled.
 * - carrier value from 2049 to 1024 changed.
 * - new disturbance detection.
 * - bugfix to compiler warning.
 * - new algo threshold  due to dittering disactivation.
 * 
 *    Rev 1.3   22 Oct 2015 12:19:40   ybadal
 * - SW Umstellung für unterschiedlische Daten Ausgabe implementiert.
 * 
 *    Rev 1.2   20 Oct 2015 10:35:50   ybadal
 * LF Modus test Flag entfernt.
 * 
 *    Rev 1.1   20 Oct 2015 10:09:46   ybadal
 * - Messung wird unterbrochen wenn LF erkannt ist.
 * 
 *    Rev 1.0   19 Oct 2015 09:43:26   ybadal
 * Initial revision.
 * 
*********************************************************** end of comment */
