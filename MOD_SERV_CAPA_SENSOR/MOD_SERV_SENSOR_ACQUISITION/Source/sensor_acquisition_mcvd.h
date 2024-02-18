/*------------------------------------------------------------------------------------------------+
| File: sensor_acquisition_mcvd.h                                                                 |
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
#ifndef SENSOR_ACQUISITION_MCVD_H_
#define SENSOR_ACQUISITION_MCVD_H_
#include "sensor_aquisition.h"

/* polyspace:begin < MISRA-C3:8.6 : Not a defect : Justify with annotations > It has just one definition inside sensor_acquisition_mcvd.c file. The others are just declarations. */
extern  SENSOR_MEASURE_VALUE_T S_UnlockRaw_ASM;/*buffer to store unlock sensor raw values*/
extern  SENSOR_MEASURE_VALUE_T S_LockRaw_ASM;/*buffer to store lock sensor raw values*/
/* polyspace:end < MISRA-C3:8.6 : Not a defect : Justify with annotations > It has just one definition inside sensor_acquisition_mcvd.c file. The others are just declarations. */

extern void Sensor_task_acquisition(void);
extern void Sensor_task_acquisition_LP(void);

#endif /* SENSOR_ACQUISITION_MCVD_H_ */
