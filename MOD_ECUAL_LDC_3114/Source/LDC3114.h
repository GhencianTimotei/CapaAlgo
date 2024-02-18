/*------------------------------------------------------------------------------------------------+
| File: LDC3114.h                                                                              |
+-------------------------------------------------------------------------------------------------+
| Project: Audi eTab                                                                              |
+-------------------------------------------------------------------------------------------------+
| Short description: In this file are included all the headers                                    |
|                                                                                                 |
|                                                                                                 |
|                                                                                                 |
|                                                                                                 |
+-------------------------------------------------------------------------------------------------+
| for Information, to do:                                                                         |
|                                                                                                 |
|                                                                                                 |
+-------------------------------------------------------------------------------------------------+
| $Revision::                                                                                  $: |
| $Date::                                                                                      $: |
| $Author::                                                                                    $: |
| $URL::                                                                                       $: |
|                                                                                                 |
+------------------------------------------------------------------------------------------------*/
#ifndef LDC3114_H_
#define LDC3114_H_


#include "LDC3114.hm"
#include "LDC3114.hi"
#include "LDC3114.ha"
#include "LDC3114.hc"

#define U8_SYNC_TIMEOUT_ACTIVE_MS (U8)(16) /* call capa if LDC interrupt does not came after 30ms (LDC interrupt polling checked on 5ms task) SWR_657*/
#define U8_LDC3114_FILTER_INIT_RECALL   ((U8) 4u)
/* polyspace+1 MISRA-C3:8.5 [Not a defect:Low] "these declarations will never meet" */
extern void Mcu_PerformReset(void);

enum
{
    LDC3114_CASCADE_LEVEL1 = 0x00u,
    LDC3114_CASCADE_LEVEL2,
    LDC3114_CASCADE_LEVEL_MAX
};

enum
{
    LDC3114_MEMORY_DEPTH_1 = 0x00u,
    LDC3114_MEMORY_DEPTH_2 = 0x01u,
    LDC3114_MEMORY_DEPTH_MAX
};
typedef enum
{
   LDC3114_SENSOR_CH0,
   LDC3114_SENSOR_CH1,
   LDC3114_SENSOR_MAX
}EN_LDC3114_SENSOR_ID;
/* polyspace+4 MISRA-C3:D4.8 [Justified:Low] "No impact on functionality, just code encapsulation related" */
typedef struct
{
    U32 U32_filter_unit_result;
    EN_LDC3114_SENSOR_ID en_sensor_id;
    S64 S64_Filt_FeedbackBuffer [(U8)LDC3114_CASCADE_LEVEL_MAX];
    U32 U32_last_sample;
    BOOL BO_sensor_active;
    S64 S64_NoiseDet_FeedbackBuffer [(U8)LDC3114_MEMORY_DEPTH_MAX]; /*! \details delay memory of noise filter  \par Range: Full */
    U32 U32_NoiseThresh;            /*! \details Threshold for noise detection  \par Range: Full */
    BOOL BO_noise_detected;   /*! \details Whether noise was detected on this sensor  \par Range: Full */
}TASK_LDC3114_VAR_T;

/* polyspace+1 MISRA-C3:8.6 [Justified:Low] "External declaration is needed" */
extern TASK_LDC3114_VAR_T LDC3114_Sensor_Var_Str[LDC3114_SENSOR_MAX];

/* polyspace+3 MISRA-C3:8.6 [Justified:Low] "External declaration is needed" */
/* Debug only !!!!! */
extern U32 Ch0_NoiseMeasVal;
extern U32 Ch1_NoiseMeasVal;
/* __________________ */
extern void LDC3114_iir_filter (TASK_LDC3114_VAR_T * Sensor_Var,U32 U32_filter_input);
extern void LDC3114_noise_detect(TASK_LDC3114_VAR_T * Sensor_Var,U32 U32_filter_input);

#endif /* LDC3114_H_ */
