#ifndef SENSOR_ALGO_HC
#define SENSOR_ALGO_HC

#include "typedefs.h"


#define UNLOCK_SENSOR       ER
#define LOCK_SENSOR         VR

/* It will be removed in the moment when it is clear that the touch state is not necessary anymore */
#define TOUCH_DISABLED
typedef struct
{
    XINT approach:1;
    XINT touch:1;
    XINT bit2:1;
    XINT bit3:1;
    XINT bit4:1;
    XINT bit5:1;
    XINT bit6:1;
    XINT bit7:1;
}BOOL_BITS_T;

#endif /* SENSOR_ALGO_HC */