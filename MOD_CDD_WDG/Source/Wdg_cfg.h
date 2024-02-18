#ifndef WDG_CFG_H
#define WDG_CFG_H

#include "Std_Types.h"

#ifndef STD_OFF
#error "Autosar standart types definitions are missing"
#endif

#define WDG_USES_ISR            STD_OFF
#define WDG_USES_WINDOW_MODE    STD_OFF

/* 
* Clock source is set to LPO which should have 128khz, one time quanta is about 7.8125 microseconds
* 10 ms 1280
*/
/* polyspace+4 MISRA-C3:2.5 [Justified:Low] "Macro should be kept for future usage" */
#define WDG_150ms       (19200u)
#define WDG_100ms       (12800u)
#define WDG_50ms        (6400u)
#define WDG_10ms        (1280u)

#define WDG_RUN_TIMEOUT         WDG_150ms
#define WDG_VLPR_TIMEOUT        WDG_100ms

extern void WDG_setWindowValue(U16 value);
extern void WDG_setWatchDogValue(U16 value);
extern U16 WDG_getWindowValue(void);
extern U16 WDG_getWatchDogValue(void);

extern void WDG_initCfg(void);

#endif /*WDG_CFG_H*/
