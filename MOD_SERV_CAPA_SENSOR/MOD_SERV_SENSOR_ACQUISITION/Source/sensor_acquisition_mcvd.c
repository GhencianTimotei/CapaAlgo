/* polyspace MISRA-C3:1.1 [Justified:Unset] "All macro definitions are needed." */
/*------------------------------------------------------------------------------------------------+
| File: sensor_acquisition_mcvd.c                                                                 |
+-------------------------------------------------------------------------------------------------+
| Project: Audi eTab                                                                              |
+-------------------------------------------------------------------------------------------------+
| Short description:                                                                              |
|                                                                                                 |
|                                                                                                 |
|                                                                                                 |
|                                                                                                 |
|                                                                                                 |
+------------------------------------------------------------------------------------------------*/

/* Header files include */
#include "sensor_acquisition_mcvd.h"
#include "S32K144.h"
#include "Adc.h"


/* polyspace:begin < MISRA-C3:8.2,8.5,21.2 : Not a defect : Justify with annotations > The function type is same as in prototype form */
extern void _SensorAcq_mcvd_both_scan(void);
extern void _SensorAcq_mcvd_both_scan_LP(void);

/* polyspace:end < MISRA-C3:8.2,8,21.2 : Not a defect : Justify with annotations > The function type is same as in prototype form */

SENSOR_MEASURE_VALUE_T S_UnlockRaw_ASM;/*buffer to store unlock sensor raw values*/
SENSOR_MEASURE_VALUE_T S_LockRaw_ASM;/*buffer to store lock sensor raw values*/


/*************************************************************************************************************
 *  Name                 : Sensor_task_acquisition
 *  Description          : This function starts sensors aquisition in active mode
 *
 *  Parameters           : -
 *  Return               : void
 *  Critical/explanation : -
 *  Author               : bbarlea
 *************************************************************************************************************/
void Sensor_task_acquisition(void)
{
    U32 u32CFG1, u32SC2, u32SC3, u32SC1A;

    /* Backup current configuration data */
    u32CFG1 = ADC0->CFG1;
    u32SC2 = ADC0->SC2;
    u32SC3 = ADC0->SC3;
    u32SC1A = ADC0->SC1[0];

    /* clear COCO field, bit 7 - conversion complete , it is readonly */
    u32SC1A &= 0x80U;

    /* Overwrite ADC configuration, SC1A is changed in the _SensorAcq_mcvd_both_scan function */
    ADC0->CFG1 = 0x000000004U; /* ADICLK=0: Input clk=ALTCLK1=(ADC0_ClkSrc)  ADIV=0: Prescaler=1  MODE=1: 12-bit conversion */
    ADC0->SC2 = 0x00000000U; /* ADTRG=0: SW trigger  ACFE,ACFGT,ACREN=0: Compare func disabled  DMAEN=0: DMA disabled  REFSEL=0: Voltage reference pins= VREFH, VREEFL */
    ADC0->SC3 = 0x00000000U; /* CAL=0: Do not start calibration sequence  ADCO=0: One conversion performed  AVGE,AVGS=0: HW average function disabled */
    /* function difinition in assambly */
    _SensorAcq_mcvd_both_scan();

    /* Restore previous data */
    ADC0->SC1[0] = u32SC1A;
    ADC0->CFG1 = u32CFG1;
    ADC0->SC2 = u32SC2;
    ADC0->SC3 = u32SC3;
}

/*************************************************************************************************************
 *  Name                 : Sensor_task_acquisition
 *  Description          : This function starts sensors aquisition in low power mode
 *
 *  Parameters           : -
 *  Return               : void
 *  Critical/explanation : -
 *  Author               : bbarlea
 *************************************************************************************************************/
/* polyspace < MISRA-C3:8.4,8.5 : Not a defect : Justify with annotations > External Usage dependent on project setup */
void Sensor_task_acquisition_LP(void)
{
    U32 u32CFG1, u32SC2, u32SC3, u32SC1A;

    /* Backup current configuration data */
    u32CFG1 = ADC0->CFG1;
    u32SC2 = ADC0->SC2;
    u32SC3 = ADC0->SC3;
    u32SC1A = ADC0->SC1[0];

    /* clear COCO field, bit 7 - conversion complete , it is readonly */
    u32SC1A &= 0x80U;
    ADC0->CFG1 = 0x000000004U;          /* ADICLK=0: Input clk=ALTCLK1=(ADC0_ClkSrc)  ADIV=0: Prescaler=1  MODE=1: 12-bit conversion */
    ADC0->SC2 = 0x00000000U;            /* ADTRG=0: SW trigger  ACFE,ACFGT,ACREN=0: Compare func disabled  DMAEN=0: DMA disabled  REFSEL=0: Voltage reference pins= VREFH, VREEFL */
    ADC0->SC3 = 0x00000000U;            /* CAL=0: Do not start calibration sequence  ADCO=0: One conversion performed  AVGE,AVGS=0: HW average function disabled */

    /* Overwrite ADC configuration, SC1A is changed in the _SensorAcq_mcvd_both_scan_LP function */
    _SensorAcq_mcvd_both_scan_LP();

    /* Restore previous data */
    ADC0->SC1[0] = u32SC1A;
    ADC0->CFG1 = u32CFG1;
    ADC0->SC2 = u32SC2;
    ADC0->SC3 = u32SC3;
}
