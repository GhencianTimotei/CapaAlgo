#ifndef SENSOR_ACQUISITION_MCVD_H_
#define SENSOR_ACQUISITION_MCVD_H_
#include "sensor_aquisition.h"

extern  SENSOR_MEASURE_VALUE_T S_UnlockRaw_ASM;/*buffer to store unlock sensor raw values*/
extern  SENSOR_MEASURE_VALUE_T S_LockRaw_ASM;/*buffer to store lock sensor raw values*/

extern void Sensor_task_acquisition(void);
extern void Sensor_task_acquisition_LP(void);

#endif /* SENSOR_ACQUISITION_MCVD_H_ */
