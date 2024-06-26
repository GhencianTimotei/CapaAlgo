#ifndef SENSOR_MCVD_H
#define SENSOR_MCVD_H

#ifdef SENSOR_MCVD_C
#define REF_SENSOR
#else
#define REF_SENSOR extern
#endif

#include "sensor_mcvd.hc"
#include "sensor_mcvd.ha"
#include "sensor_mcvd.hi"
#include "sensor_mcvd.hm"

enum
{
    MEMORY_DEPTH_1 = 0x00u,
    MEMORY_DEPTH_2 = 0x01u,
    MEMORY_DEPTH_MAX
};

typedef struct
{
    U16 U16_filter_unit_result;/**/

      EN_SENSOR_ID en_sensor_id;
      S32 S32_Filt_FeedbackBuffer [(U8)CASCADE_LEVEL_MAX];
      U16 U16_last_sampleB;/**/
      U16 U16_last_sampleA;
      BOOL BO_sensor_active;
      S16 S16_NoiseDet_FeedbackBuffer [(U8)MEMORY_DEPTH_MAX]; /*! \details delay memory of noise filter  \par Range: Full */
      U16 U16_NoiseThresh;            /*! \details Threshold for noise detection  \par Range: Full */
      BOOL BO_noise_detected;   /*! \details Whether noise was detected on this sensor  \par Range: Full */
}TASK_SENSOR_VAR_T;

extern TASK_SENSOR_VAR_T   Sensor_Var_Str[SENSOR_MAX]; /*! sensor  main structur  content the variables for each sensor used from the sensor module.*/
#endif