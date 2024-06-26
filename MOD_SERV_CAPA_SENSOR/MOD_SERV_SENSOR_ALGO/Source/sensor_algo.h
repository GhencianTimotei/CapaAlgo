#ifndef SENSOR_ALGO_H
#define SENSOR_ALGO_H

#ifndef INTEGRATE_FROM_V4
#include "Platform_Types.h"
#endif
#include "sensor_algo.hc"
#include "sensor_algo.ha"
#include "sensor_algo.hi"
#include "sensor_algo.hm"


typedef enum
{
    EN_ASM_SX_IDLE = 0,                                         /*Sensor is still Idle No Thres*/
    EN_ASM_SX_DEBOUNCE,                                         /*Sensor cross the Approach threshold */
    EN_ASM_SX_APPROACH,                                         /*sensor still crossing the approach threshold*/
    EN_ASM_SX_TOUCH,                                            /*sensor cross the TOUCH threshold*/
    EN_ASM_SX_OFF_DELAY                                         /*sensor calculate a new baseline behaviour going back to idle */

} ENUM_ALGO_SM_STATE_TYPE;

typedef enum {
    Cx0_keine_Deaktivierung = 0U,
    Cx1_Deaktivierung       = 1U
}NFC_TSG_Kapa_deaktivieren_CAN_Signal_values;

extern NEAR ENUM_ALGO_SM_STATE_TYPE EN_ER_AlgoStateSM;          /* active-mode unlock sensor states */
extern NEAR ENUM_ALGO_SM_STATE_TYPE EN_VR_AlgoStateSM;          /* active-mode lock sensor states */
extern void CAPA_publishCanSignals(void);
extern void Algo_getVrState(U8 *U8_algoState);
extern void Algo_getErState(U8 *U8_algoState);
extern void get_sensor_algo_state_result(U8 *U8_algo_state_arg);
extern void getRefThreshold(U16 * buff);

#endif /* SENSOR_H */