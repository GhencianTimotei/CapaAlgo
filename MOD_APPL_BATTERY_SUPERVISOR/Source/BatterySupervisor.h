/*------------------------------------------------------------------------------------------------+
| File: BatterySupervisor.h                                                                          |
+-------------------------------------------------------------------------------------------------+
| Project: Audi eTab                                                                              |
+-------------------------------------------------------------------------------------------------+
| Short description: The file contains the header file of the Voltage Monitor module              |
|                                                                                                 |
|                                                                                                 |
|                                                                                                 |
|                                                                                                 |
|                                                                                                 |
+------------------------------------------------------------------------------------------------*/

#ifndef BATTERYSUPERVISOR_H_
#define BATTERYSUPERVISOR_H_

#include "Std_Types.h"
/* polyspace+2 MISRA-C3:2.4 [Justified:Low] "Added for further implementation." */
/* polyspace+10 MISRA-C3:8.12 [Justified:Low] "Intentionally added" */
typedef enum voltageState
{
    BATSUP_NO_STATE = 0u,
    BATSUP_FIRST_VALID_STATE,
    BATSUP_COM_OFF_1 = BATSUP_FIRST_VALID_STATE,
    BATSUP_UNDERVOLTAGE,
    BATSUP_NOMAL,
    BATSUP_OVERVOLTAGE,
    BATSUP_COM_OFF_2,
    BATSUP_VOLT_STATE_COUNT = BATSUP_COM_OFF_2
} BatSup_voltageStateType;

/* polyspace+1 MISRA-C3:2.4 [Justified:Low] "Added for further implementation." */
typedef enum errorState
{
    BATSUP_NO_ERROR = 0u,
    BATSUP_ADC_SAMPLE_ERROR,
    BATSUP_VOLTAGE_STATE_ERROR,
    BATSUP_UNKNOW_STATE_ERROR,
    BATSUP_ALGO_STATE_ERROR
}BatSup_errorStateType;


extern U8 BatSup_isVoltageInNormal(void);
extern U8 BatSup_isComOff(void);
extern BatSup_voltageStateType BatSup_getVoltageState(void);
extern BatSup_errorStateType BatSup_getErrorState(void);
extern void BatSup_initTask(void);
extern void BatSup_fastTask(void);
extern U8 BatSup_idleTask(void);
extern U16 BatSup_getVoltageValue(void);

/* Limits used as default values in NVM and PDL */
#define BATSUP_DEBOUNCE_TIME    ((U16)(80u))

#endif /* VOLTAGEMONITOR_H_ */
