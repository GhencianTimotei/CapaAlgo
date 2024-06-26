#ifndef SENSOR_AQUISITION_C
#define SENSOR_AQUISITION_C

#include "Platform_Types.h"
#include "sensor_aquisition.h"
/* Provide interface */
#include "Dio.h"
#include "Port.h"
#include "IntegrationTests.h"
#include "sensor_acquisition_mcvd.h"

#define HIGH       1
#define LOW        0

/* Compensation values for sensor readings in normal/active mode */
const U16 U16_Lock_A_Raw_Manipulation = (U16)4;
const U16 U16_Lock_B_Raw_Manipulation = (U16)8;
const U16 U16_Unlock_A_Raw_Manipulation = (U16)5;
const U16 U16_Unlock_B_Raw_Manipulation = (U16)5;

void SensorAquisition_Compensation(void);

SENSOR_AQ_EXPORT void Sensor_aquisition_init(void)
{

}

SENSOR_AQ_EXPORT SENSOR_MEASURE_VALUE_T* Get_Sensor_Scan_ER(void)
{
    return &S_UnlockRaw_ASM;
}

static void SensorAqc_Init_Hw_both(void)
{

}

static void SensorAcq_reset_Hw_both(void)
{
}
SENSOR_AQ_EXPORT SENSOR_MEASURE_VALUE_T*  Get_Sensor_Scan_VR(void)
{
 return &S_LockRaw_ASM;
}

void  Sensor_Scan_Both(void)
{
    SensorAqc_Init_Hw_both();
    Sensor_task_acquisition();
    SensorAquisition_Compensation();
    SensorAcq_reset_Hw_both();
}

void  Sensor_Scan_Both_LP(void)
{
    SensorAqc_Init_Hw_both();
    Sensor_task_acquisition_LP();
    SensorAcq_reset_Hw_both();
}

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