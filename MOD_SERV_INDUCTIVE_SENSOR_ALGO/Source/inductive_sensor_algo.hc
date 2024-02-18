/*------------------------------------------------------------------------------------------------+
| File: inductive_sensor_algo.hc                                                                  |
+-------------------------------------------------------------------------------------------------+
| Project: Audi eTab                                                                              |
+-------------------------------------------------------------------------------------------------+
| Short description: Header containing module configurations of inductive algo                    |
|                                                                                                 |
|                                                                                                 |
|                                                                                                 |
|                                                                                                 |
+------------------------------------------------------------------------------------------------*/
#ifndef INDUCTIVE_SENSOR_ALGO_HC
#define INDUCTIVE_SENSOR_ALGO_HC

/* Inductive Channels which will be handled in algo */
typedef enum
{
	INDUCTIVE_SENSOR_CH0,
	INDUCTIVE_SENSOR_CH1,
	INDUCTIVE_SENSOR_MAX
}EN_INDUCTIVE_SENSOR_ID;

/* Algo States */
typedef enum
{
    EN_INDUCTIVE_STATE_IDLE=0,    /*Sensor is still IDLE No Thres*/
    EN_INDUCTIVE_STATE_DEBOUNCE,  /*ensor cross the TOUCH threshold and wait the debounce time for validation */
    EN_INDUCTIVE_STATE_TOUCH,     /*sensor cross the TOUCH threshold*/
    EN_INDUCTIVE_STATE_OFFDELAY   /*sensor returns to IDLE after coming from TOUCH state */

} ENUM_INDUCTIVE_ALGO_SM_STATE_TYPE;

/* polyspace < CERT-C:CON43-C : Not a defect : Justify with annotations > No concurrency on this variable */
static U8 U8_Debounce_Time_Reset;

#endif /* INDUCTIVE_SENSOR_ALGO_HC */