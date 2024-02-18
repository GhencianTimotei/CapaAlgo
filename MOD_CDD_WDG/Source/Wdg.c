/* polyspace+1 MISRA-C3:1.1 [Justified:Low] "All macro definitions are needed." */
/**
*   file:        WdgIf.c
*   description: Service layer, used to call watchdog complex driver interfaces .
*/

#include "Std_Types.h"
#include "S32K144.h"

#include "Wdg.h"
#include "Os.h"
#include "Mcu.h"

/*************************************************************************************
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
*************************************************************************************/


/*************************************************************************************
*                                       LOCAL MACROS
*************************************************************************************/
/* polyspace+16 MISRA-C3:2.5 [Justified:Low] "Macro should be kept for future usage" */
#define WDG_UNLOCK_KEY_U32      (0xD928C520uL)
#define WDG_UNLOCK_KEY0_U16     (0xC520u)
#define WDG_UNLOCK_KEY1_U16     (0xD928u)

#define WDG_REFRESH_KEY_U32     (0xB480A602u)  /* CS EN is set */
#define WDG_REFRESH_KEY0_U16    (0xA602u)       /* CS EN is cleared */
#define WDG_REFRESH_KEY1_U16    (0xB480u)       /* CS EN is cleared */

/* CS register defines */
#define WDG_CS_USES_WINDOW          (0x8000u)   /* bit 15 */
#define WDG_CS_USES_32_BIT          (0x2000u)   /* bit 13 */
#define WDG_CS_CLOCK_LPO            (0x0100u)   /* bit 8-9 */
#define WDG_CS_EN_WDG               (0x0080u)   /* bit 7 */
#define WDG_CS_USES_INT             (0x0040u)   /* bit 6 */
#define WDG_CS_UPDATE_ALLOWED       (0x0020u)   /* bit 5 */
#define WDG_CS_EN_STOP              (0x0001u)   /* bit 0 */

/*************************************************************************************
*                                      LOCAL CONSTANTS
*************************************************************************************/

/*************************************************************************************
*                                      LOCAL VARIABLES
*************************************************************************************/

/*************************************************************************************
*                                      GLOBAL CONSTANTS
*************************************************************************************/

/*************************************************************************************
*                                      GLOBAL VARIABLES
*************************************************************************************/

U16 WDG_windowValue = 0u;
U16 WDG_watchDogValue = 0u;

/*************************************************************************************
*                                   LOCAL FUNCTION PROTOTYPES
*************************************************************************************/

/* These are local function to WDG component, but from C point of view, are global function, no static key word */
void WDG_setWindowValue(U16 value);
void WDG_setWatchDogValue(U16 value);

U16 WDG_getWindowValue(void);
U16 WDG_getWatchDogValue(void);

/*************************************************************************************
*                                       LOCAL FUNCTIONS
*************************************************************************************/

void WDG_setWindowValue(U16 value)
{
    WDG_windowValue = value;
}

void WDG_setWatchDogValue(U16 value)
{
    WDG_watchDogValue = value;
}

U16 WDG_getWindowValue(void)
{
    return WDG_windowValue;
}

U16 WDG_getWatchDogValue(void)
{
    return WDG_watchDogValue;
}

/*************************************************************************************
*                                       GLOBAL FUNCTIONS
*************************************************************************************/

void Wdg_setTrigger(void)
{
    SuspendAllInterrupts();
    WDOG->CNT = WDG_REFRESH_KEY_U32;
    ResumeAllInterrupts();
}

void Wdg_init(void)
{
    WDG_initCfg();

    SuspendAllInterrupts();
    /* Watchdog reg are already changed in bootloader and 32 bit read write is configured */
    WDOG->CNT = WDG_UNLOCK_KEY_U32;

    while ((WDOG->CS & WDOG_CS_UPDATE_MASK) == 0u) { /* wait until watchdog becomes unlocked */ }
    /* No window, 32bitsupport, 256 prescalar disabled, Clock LPO, EN WDG, NO ISR, Update allowed, no test, DIS in Debug, DIS in Wait, EN in Stop */
    WDOG->CS = WDG_CS_USES_32_BIT | WDG_CS_CLOCK_LPO |  WDG_CS_EN_WDG | WDG_CS_UPDATE_ALLOWED | WDG_CS_EN_STOP;
#if(WDG_USES_WINDOW_MODE == STD_ON)
    WDOG->CS |= WDG_CS_USES_WINDOW;
#endif
#if(WDG_USES_ISR == STD_ON)
    WDOG->CS |= WDG_CS_USES_INT;
#endif
    WDOG->TOVAL = WDG_watchDogValue;
    WDOG->WIN = WDG_windowValue;

    while ((WDOG->CS & WDOG_CS_RCS_MASK) == 0u) { /* wait until watchdog becomes availble */ }
    ResumeAllInterrupts();
}

void Wdg_setMode(U16 value)
{
    SuspendAllInterrupts();
    WDOG->CNT = WDG_UNLOCK_KEY_U32;
    while ((WDOG->CS & WDOG_CS_UPDATE_MASK) == 0u) { /* wait until watchdog becomes unlocked */ }
    
    WDOG->TOVAL = value;

    while ((WDOG->CS & WDOG_CS_RCS_MASK) == 0u) { /* wait until watchdog becomes availble */ }
    ResumeAllInterrupts();
}
