#ifndef SENSOR_MCVD_HC
#define SENSOR_MCVD_HC

#ifdef SENSOR_MCVD_C
#define REF_SENSOR
#else
#define REF_SENSOR extern
#endif

/* includes */

#define U16_MAX         ((U16)0xFFFFu)
#define U16_IIR_WARME_UP_CONSTANT ((U16)4096)

#define U16_CARRIER_VALUE                ((U16)4096)

enum
{
    CASCADE_LEVEL1 = 0x00u,
    CASCADE_LEVEL2,
    CASCADE_LEVEL_MAX
};

#endif