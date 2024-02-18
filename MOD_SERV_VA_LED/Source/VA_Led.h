#ifndef MOD_SERV_VA_LED_SOURCE_VA_LED_H_
#define MOD_SERV_VA_LED_SOURCE_VA_LED_H_

#include "Platform_Types.h"

/* Global definitions */
#define VA_LED_TASK_TIME_MS 25u  /* VA_LED task time (ms) */

/* Global functions */
extern void VA_LED_Init(void);
extern void VA_LED_Task(void);
extern void VA_LED_DeInit(void);
extern U8 VA_LED_GetLightInfo(void);
extern void VA_LED_RequestDiag(U16 U16_Time_ms);
extern BOOL VA_LED_IsEnabled(void);
extern BOOL VA_LED_IsAvailable(void);
extern BOOL VA_LED_IsLightActive(void);
extern void VA_LED_turnOffLED(void);
extern void VA_LED_signalReceived(void);

#endif /* MOD_SERV_VA_LED_SOURCE_VA_LED_H_ */
