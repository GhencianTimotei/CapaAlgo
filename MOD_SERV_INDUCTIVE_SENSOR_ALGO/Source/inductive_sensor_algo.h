/*------------------------------------------------------------------------------------------------+
| File: inductive_sensor_algo.h                                                                |
+-------------------------------------------------------------------------------------------------+
| Project: Audi eTab                                                                              |
+-------------------------------------------------------------------------------------------------+
| Short description: In this file are included all the headers                                    |
|                                                                                                 |
|                                                                                                 |
|                                                                                                 |
|                                                                                                 |
|                                                                                                 |
+------------------------------------------------------------------------------------------------*/
#ifndef INDUCTIVE_SENSOR_ALGO_H_
#define INDUCTIVE_SENSOR_ALGO_H_


#include "inductive_sensor_algo.hm"
#include "inductive_sensor_algo.hi"
#include "inductive_sensor_algo.ha"
#include "inductive_sensor_algo.hc"
#include "LDC3114.h"
#ifdef INTEGRATE_FROM_V4
#include "std_inc.h"
#endif

#ifndef INTEGRATE_FROM_V4
#include "Platform_Types.h"
#endif


/* Structure used to store the information for every channel */
typedef struct
{
    U32 ThresholdReference;
    U32 ThresholdValue;
    U32 *MeasuredValue;
    U32 MinMeasureValue;
    U32 MinValProcess;
    U32 FreezeThreshold;
    U16 LDC_THRESHOLD;
    U16 LdcDebounceTimeOut;
    U16 FreezeCounter;
    U8  LdcDebounce;
    U8  LdcOffDelayDebounce;
    U8  LdcRefDebounce;
    U8  FreezeActiveOnce;
    U8  NoiseActiveCnt;
    EN_INDUCTIVE_SENSOR_ID sensorChannel;
    ENUM_INDUCTIVE_ALGO_SM_STATE_TYPE AlgoStateSM;
} TASK_INDUCTIVE_SENSOR_PARAMETER;

/* Global variables used to limit the LDC and capa synchronization in Normal mode. */
extern U16 U16_Normal_Low_Ticks;
extern U16 U16_Normal_High_Ticks;
extern U8 U8_Inductive_Algo_Valid_Touch;

/* Iinitial values and references for every channel */
extern TASK_INDUCTIVE_SENSOR_PARAMETER inductive_sensor_param[INDUCTIVE_SENSOR_MAX];

extern BOOL boIsInductiveActive(void);
extern U8 InductiveAlgo_getInductiveValue(void);
extern void Inductive_Algo_Clear_Can_Signal(void);

#endif /* INDUCTIVE_SENSOR_ALGO_H_ */
