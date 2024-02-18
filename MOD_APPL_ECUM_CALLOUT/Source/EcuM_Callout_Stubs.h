#ifndef ECUM_CALLOUT_STUBS
#define ECUM_CALLOUT_STUBS
#include "EcuM.h"

typedef enum
{
    PassiveWakeUp = 0,
    ActiveWakeUp
} wakeUpType;

void EcuM_setWakeUpSource(EcuM_WakeupSourceType wupSource);
void EcuM_resetWakeUpSource(void);
EcuM_WakeupSourceType EcuM_getWakeUpSource(void);

void EcuM_EnableCanComByCAPA(void);
void EcuM_EnableCanComByNFC(void);

extern void Fls_AC_Callback_Test(void);
extern void Fls_StartFlashAccessNotif(void);
extern void Fls_FinishedFlashAccessNotif(void);
extern void Fee_ClusterFormatNotif(void);
extern void EcuM_CanWakeUp(void);

#define EcuM_WAKE_UP_EXIT_SLEEP     5u
#define EcuM_WAKE_UP_CAN            1u
#define EcuM_WAKE_UP_NFC            2u
#define EcuM_WAKE_UP_CAPA           3u
#define EcuM_WAKE_UP_ENTER_SLEEP    0u

/* polyspace+3 MISRA-C3:8.6 [Justified:Low] "External declaration is needed" */
extern U8 EcuM_WakeUpLogged;
extern U8 EcuM_BusSleepActive;
extern wakeUpType EcuM_WakeUpType;
extern U8 EcuM_calloutCanSignalNM_NFC_FS_FCAB[7];

#endif