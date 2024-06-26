#ifndef SENSOR_ALGO_HA
#define SENSOR_ALGO_HA



/* XX_THRESHOLD_MAX_PP for all variants */
#define U16_REF_VALUE_MAX_PP           (64000u)        /* for deactivation, the reference value is pulled down to this level */
#define U8_ER_REF_VAL_COUNT            (13u)           /* number of values used to calculate the reference value for unlock sensor */
#define U8_VR_REF_VAL_COUNT            (13u)           /* number of values used to calculate the reference value for lock sensor */
#define U16_SENSOR_CYCLE_TIME          ((U16)10)
#define U16_PARAMETER_CORRECTUR        ((U16)10)

#define U16_REF_VALUE_MAX  ((U16)(U16_REF_VALUE_MAX_PP))

#define U16_ER_THRESHOLD_MIN_PP        (210u)           /* threshold value for unlock approach */
#define U16_VR_THRESHOLD_MIN_PP        (35u)           /* threshold value for lock approach */
#define U16_ER_THRESHOLD_MAX_PP        (110u)          /* threshold value for unlock touch */
#define U16_VR_THRESHOLD_MAX_PP        (150u)           /* threshold value for lock touch */
#define U8_ER_DEBOUNCE_EEP             (2u)            /* debounce counter to creating enough consecutive positive shifts of the reading above the baseline by at least the unlock APPROACH threshold*/
#define U8_VR_DEBOUNCE_EEP             (8u)            /* debounce counter to creating enough consecutive positive shifts of the reading above the baseline by at least the lock APPROACH threshold*/
#define U16_ER_ACTIVATION_TIME		   (1600u)		  /* maximum activation time for unlock sensor */
#define U16_VR_ACTIVATION_TIME		   (1600u)		  /* maximum activation time for lock sensor */

#define U16_ER_NOISE_DEBOUNCE          (10u)           /* additional debounce steps in case of noise */
#define U16_VR_NOISE_DEBOUNCE          (15u)           /* additional debounce steps in case of noise */
#define U16_ER_NOISE_ACTIVE_TIME       (48u)           /* number of samples the noise detection is kept active */
#define U16_VR_NOISE_ACTIVE_TIME       (96u)           /* number of samples the noise detection is kept active */
#define U16_ER_NOISE_SENSIVITY_PP      (25u)           /* offset for the approach in case of increased noise */
#define U16_VR_NOISE_SENSIVITY_PP      (75u)           /* offset for the approach in case of increased noise */
#define U16_ER_NOISE_THRESHOLD         (50u)           /* threshold to detect noise */
#define U16_VR_NOISE_THRESHOLD         (50u)           /* threshold to detect noise */

#define MASK_FOR_cp_ESMdisableKessy                    0x10U           /* mask for ESMdisableKessy bit */

#define U16_ER_SENSIVITY_APPROACH      ((U16)U16_ER_THRESHOLD_MIN_PP)       /* trigger threshold for the unlock approach  */
#define U16_ER_SENSIVITY_TOUCH         ((U16)U16_ER_THRESHOLD_MAX_PP)       /* trigger threshold for the unlock touch */
#define U16_ER_NOISE_SENSIVITY         ((U16)U16_ER_NOISE_SENSIVITY_PP)     /* offset for approximation of increased noise */


#define U16_VR_SENSIVITY_APPROACH      ((U16)U16_VR_THRESHOLD_MIN_PP)      /* trigger threshold for the lock approach */
#define U16_VR_SENSIVITY_TOUCH         ((U16)U16_VR_THRESHOLD_MAX_PP)      /* trigger threshold for the lock touch */
#define U16_VR_NOISE_SENSIVITY         ((U16)U16_VR_NOISE_SENSIVITY_PP)    /* offset for approximation of increased noise */

#define U16_ER_REF_TRACKING_CONS       ((U16)4)                            /* multiplicator of difference between touch threshold and reference value to update during tracking*/
#define U16_VR_REF_TRACKING_CONS       ((U16)4)                            /* multiplicator of difference between touch threshold and reference value to update during tracking*/

#define U16_ER_OFF_DELAY_CONS          ((U16)10)                           /*250 ms*/
#define U16_VR_OFF_DELAY_CONS          ((U16)10)                           /*250 ms*/

#define U16_ER_DEACTIVATION_DEBOUNCE   ((U16)2)
#define U16_VR_DEACTIVATION_DEBOUNCE   ((U16)2)

#define U16_ER_ACTIVE_MAX_TIME         ((U16)(((U16)30000   )/U16_SENSOR_CYCLE_TIME) / U16_PARAMETER_CORRECTUR)      /* 4 seconds*/
#define U16_VR_ACTIVE_MAX_TIME         ((U16)(((U16)30000  )/U16_SENSOR_CYCLE_TIME) /  U16_PARAMETER_CORRECTUR)      /* 4 seconds*/
#define U16_ER_AKTIVATION_400MS        ((U16)390)/U16_SENSOR_CYCLE_TIME  /* 400 ms */


#define U16_ER_SGD_NOT_DESTROY_ENV     ((U16)80)                           /*ER Maximum Signal update with noise free environment */
#define U16_ER_SGD_DESTROY_ENV         ((U16)10)                           /*ER Maximum Signal update with destroyed environment */
#define U16_VR_SGD_NOT_DESTROY_ENV     ((U16)130)                          /*VR Maximum Signal update with noise free environment */
#define U16_VR_SGD_DESTROY_ENV         ((U16)10)                           /*VR Maximum Signal update with destroyed environment */

#define U16_ER_FREEZE_THRESHOLD_NVM_DEF   (U16)73                          /* Freeze threshold calculation base */
#define U16_ER_FREEZE_CANCEL_NVM_DEF      (U16)80                          /* Debounce time for freeze (in samples) */
#define U16_VR_FREEZE_THRESHOLD_NVM_DEF   (U16)35                          /* Freeze threshold calculation base */
#define U16_VR_FREEZE_CANCEL_NVM_DEF      (U16)80                          /* Debounce time for freeze (in samples) */

#endif /* SENSOR_ALGO_HA */