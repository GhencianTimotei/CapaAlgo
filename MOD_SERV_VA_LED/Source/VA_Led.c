/* polyspace+1 MISRA-C3:1.1 [Justified:Low] "All macro definitions are needed." */
#include "VA_Led.h"

#include "typedefs.h"
#include "NvmMng.h"
#include "Com.h"
#include "Pwm.h"

#include "BatterySupervisor.h"
#include "EcuM.h"

/*-----------------------------------------------------------------------------------------------*/
/* Local definitions                                                                             */
/*-----------------------------------------------------------------------------------------------*/

/* Ramp-Up/Ramp-Down time factor (Audi parameters have 10ms resolution, e.g. 150 -> 1500ms) */
#define VA_LED_RAMP_TIME_FACTOR_MS 10u

/* Maximum duty cycle allowed by PWM component (corresponding to 100%) */
#define VA_LED_PWM_DUTY_CYCLE_MAX 32768u  /* 0x8000 (Standard AUTOSAR PWM SW Component) */

/* Maximum duty cycle possible to set by Audi parameter */
#define VA_LED_PARAM_DUTY_CYCLE_MAX 255u

/* LED states */
typedef enum
{
    VA_LED_OFF = 0,
    VA_LED_RAMPUP,
    VA_LED_ON,
    VA_LED_RAMPDOWN
} VA_LED_State_t;

/* polyspace+8 MISRA-C3:2.3 [Justified:Low] "Added for further implementation." */
/* VA_LED Timer IDs */
typedef enum
{
    VA_LED_TIMER_DIAG = 0,
    VA_LED_TIMER_RAMPUP,
    VA_LED_TIMER_RAMPDOWN,
    VA_LED_NO_OF_TIMERS
} VA_LED_U8_TimerID_t;  /* Typedef name is not used, enum values only */

/* Timer structure */
typedef struct
{
    U16 Limit_ms;  /* Maximum value */
    U16 Value_ms;  /* Current/counter value */
} VA_LED_Timer_t;



/*-----------------------------------------------------------------------------------------------*/
/* Local functions                                                                               */
/*-----------------------------------------------------------------------------------------------*/

/* Main functions, used in cyclic task */
static void VA_LED_UpdateParameters(void);
static void VA_LED_UpdateTimers(void);
static void VA_LED_ProcessDiagRequest(void);
static void VA_LED_UpdateStateConditions(void);
static void VA_LED_StateDetermination(void);
static void VA_LED_CalculatePWMDutyCycle(void);
static void VA_LED_ApplyPWMDutyCycle(void);
static void VA_LED_UpdateDelayValues(void);

/* Helper functions */
static BOOL VA_LED_GetComRequest(void);
static BOOL VA_LED_TurnOffDetected(void);
static BOOL VA_LED_DiagEndDetected(void);

/* Timer functions */
static void VA_LED_Timer_SetLimit(U8 U8_TimerID, U16 U16_Limit_ms);
static void VA_LED_Timer_Reset(U8 U8_TimerID);
static void VA_LED_Timer_Tick(U8 U8_TimerID);
static BOOL VA_LED_Timer_IsRunning(U8 U8_TimerID);
static BOOL VA_LED_Timer_IsExpired(U8 U8_TimerID);
static U16  VA_LED_Timer_GetLimit(U8 U8_TimerID);
static U16  VA_LED_Timer_GetElapsed(U8 U8_TimerID);
static U16  VA_LED_Timer_GetRemaining(U8 U8_TimerID);


/*-----------------------------------------------------------------------------------------------*/
/* Local variables                                                                               */
/*-----------------------------------------------------------------------------------------------*/

LOCAL BOOL VA_LED_Initialized = FALSE;                  /* Flag for checking component initialization */
static BOOL VA_LED_dataReceived = FALSE;                /* Indicates that data was received in this current Active cycle */
LOCAL VA_LED_State_t VA_LED_State = VA_LED_OFF;         /* LED state */
LOCAL VA_LED_State_t VA_LED_State_Prev = VA_LED_OFF;    /* LED state, delayed value */

LOCAL BOOL VA_LED_EnabledByParam = FALSE;               /* LED enabled condition based on Audi parameter */
LOCAL BOOL VA_LED_VoltMonAllowed = FALSE;               /* LED illumination allowed by voltage monitoring */

LOCAL BOOL VA_LED_CAN_Req = FALSE;                      /* LED illumination request by CAN signal */
LOCAL BOOL VA_LED_Diag_Req = FALSE;                     /* LED illumination request by diagnosis */
LOCAL BOOL VA_LED_Diag_Req_Prev = FALSE;                /* LED illumination request by diagnosis, delayed value */

LOCAL U16  VA_LED_Diag_ReqDuration_ms = 0u;             /* Diagnosis (timed) request / duration (ms) */

LOCAL U16  VA_LED_PWMDutyCycle = 0u;                    /* Current PWM duty cycle */
LOCAL U16  VA_LED_PWMDutyCycle_Max = 0u;                /* Maximum PWM duty cycle (considering Audi parameter limit) */

/* polyspace+4 MISRA-C3:8.9 [Justified:Low] "Variable is declared once here" */
LOCAL U8   VA_LED_AudiParamByte2 = 0u;                  /* Audi parameter: enable illumination */
LOCAL U8   VA_LED_AudiParamByte23 = 0u;                 /* Audi parameter: maximum PWM duty cycle */
LOCAL U8   VA_LED_AudiParamByte24 = 0u;                 /* Audi parameter: ramp-up time */
LOCAL U8   VA_LED_AudiParamByte25 = 0u;                 /* Audi parameter: ramp-down time */

LOCAL U8   VA_LED_SleepActive = 0u;

LOCAL VA_LED_Timer_t VA_LED_Timers[VA_LED_NO_OF_TIMERS] = { {0u, 0u},     /* VA_LED_TIMER_DIAG */
                                                            {0u, 0u},     /* VA_LED_TIMER_RAMPUP */
                                                            {0u, 0u} };   /* VA_LED_TIMER_RAMPDOWN */



/*-----------------------------------------------------------------------------------------------*/
/* Global functions                                                                              */
/*-----------------------------------------------------------------------------------------------*/

/*************************************************************************************************
 * Name               : VA_LED_Init
 * Input parameter(s) : N/A
 * Output parameter(s): N/A
 * Return value       : N/A
 * Description        : Initialize VA_LED component:
 *                      - Set PWM duty cycle to 0
 *                      - Set LED state to OFF
 *                      - Update internal parameters (e.g. maximum PWM duty cycle)
 *                      - Update conditions used for state determination
 *************************************************************************************************/
void VA_LED_Init(void)
{
    Pwm_SetDutyCycle(PTA11_LIGHT_PWM, 0u);

    /* Initialize state variables just in case init function is called again after de-init */
    VA_LED_State = VA_LED_OFF;
    VA_LED_State_Prev = VA_LED_OFF;

    /* Initialize parameter/condition variables just in case VA_LED_GetBrightness() is called before VA_LED_Task() */
    VA_LED_UpdateParameters();
    VA_LED_UpdateStateConditions();

    VA_LED_Initialized = TRUE;
}


/*************************************************************************************************
 * Name               : VA_LED_Task
 * Input parameter(s) : N/A
 * Output parameter(s): N/A
 * Return value       : N/A
 * Description        : Cyclic task for VA_LED component
 *************************************************************************************************/
void VA_LED_Task(void)
{
    if (( VA_LED_Initialized ) && (VA_LED_dataReceived))
    {
        VA_LED_UpdateParameters();       /* Update internal parameters (in case Audi parameters were changed) */
        VA_LED_UpdateTimers();           /* Update running timers */
        VA_LED_ProcessDiagRequest();     /* Process timed-on request from diagnosis (0xFD42) */
        VA_LED_UpdateStateConditions();  /* Update conditions used for state determination */
        VA_LED_StateDetermination();     /* LED state determination */
        VA_LED_CalculatePWMDutyCycle();  /* Calculate PWM duty cycle based on LED state */
        VA_LED_ApplyPWMDutyCycle();      /* Apply calculated duty cycle */
        VA_LED_UpdateDelayValues();      /* Update delayed (previous) values */
    }
}

/*************************************************************************************************
 * Name               : VA_LED_signalReceived
 * Input parameter(s) : N/A
 * Output parameter(s): N/A
 * Return value       : N/A
 * Description        : Used toindicate that a valid data was received
 *************************************************************************************************/
void VA_LED_signalReceived(void)
{
    VA_LED_dataReceived = TRUE;
}

/*************************************************************************************************
 * Name               : VA_LED_DeInit
 * Input parameter(s) : N/A
 * Output parameter(s): N/A
 * Return value       : N/A
 * Description        : De-Initialize VA_LED component:
 *                      - Set PWM duty cycle to 0
 *************************************************************************************************/
void VA_LED_DeInit(void)
{
    Pwm_SetDutyCycle(PTA11_LIGHT_PWM, 0u);
    VA_LED_dataReceived = FALSE;
    VA_LED_Initialized = FALSE;
}


/*************************************************************************************************
 * Name               : VA_LED_GetLightInfo
 * Input parameter(s) : N/A
 * Output parameter(s): N/A
 * Return value       : U8 - LED duty cycle percentage [0...100], 0xFF for unavailable
 * Description        : Provide LED PWM duty cycle as percentage
 *************************************************************************************************/
U8 VA_LED_GetLightInfo(void)
{
    U8 U8_LED_Brightness = 0xFFu;  /* If LED functionality is not available (e.g. disabled by Audi parameter or
                                      under-/over-voltage situation), LED brightness is unavailable (0xFF). */

    /* polyspace+7 MISRA-C3:12.1 [Justified:Low] "The operations will be done in the standard way" */
    /* Calculate LED duty cycle percentage when LED is on (partially or fully) and when LED is off
       but LED functionality is available (in this case the result will be 0); result is rounded to
       nearest integer percentage. */
    if ( VA_LED_IsAvailable() )  /* VA_LED_IsAvailable() also checks VA_LED_Initialized */
    {
        U8_LED_Brightness = (U8)(((U32)100u * (U32)VA_LED_PWMDutyCycle + (U32)(VA_LED_PWM_DUTY_CYCLE_MAX / 2u)) /
                                             ((U32)VA_LED_PWM_DUTY_CYCLE_MAX));
    }

    return U8_LED_Brightness;
}


/*************************************************************************************************
 * Name               : VA_LED_RequestDiag
 * Input parameter(s) : U16 - LED on time (ms)
 * Output parameter(s): N/A
 * Return value       : N/A
 * Description        : Force LED on for a predetermined perioud (afterwards turn it off)
 *************************************************************************************************/
void VA_LED_RequestDiag(U16 U16_Time_ms)
{
    if ( VA_LED_Initialized )
    {
        VA_LED_Diag_ReqDuration_ms = U16_Time_ms;
    }
}


/**************************************************************************************************
 * Name               : VA_LED_IsEnabled
 * Input parameter(s) : N/A
 * Output parameter(s): N/A
 * Return value       : BOOL - illumination enabled by Audi parameter
 * Description        : Return boolean value for chrome cover lighting enable Audi parameter
 *************************************************************************************************/
BOOL VA_LED_IsEnabled(void)
{
    BOOL RetVal = FALSE;

    if ( VA_LED_Initialized )
    {
        RetVal = VA_LED_EnabledByParam;
    }

    return RetVal;
}



/**************************************************************************************************
 * Name               : VA_LED_IsAvailable
 * Input parameter(s) : N/A
 * Output parameter(s): N/A
 * Return value       : BOOL - availability of illumination
 * Description        : Check if illumination is available (enabled by Audi parameter and no
 *                      under-/over-voltage situation)
 *************************************************************************************************/
/* polyspace+1 MISRA-C3:8.7 [Justified:Low] "Function may be referenced from internal or external" */
BOOL VA_LED_IsAvailable(void)
{
    BOOL RetVal = FALSE;

    if ( VA_LED_Initialized )
    {
        RetVal = (VA_LED_EnabledByParam && VA_LED_VoltMonAllowed);
    }

    return RetVal;
}


/*************************************************************************************************
 * Name               : VA_LED_IsLightActive
 * Input parameter(s) : N/A
 * Output parameter(s): N/A
 * Return value       : BOOL - light activity
 * Description        : Determine if there is LED activity (LED on/ramp-up/ramp-down)
 *************************************************************************************************/
/* polyspace+1 MISRA-C3:8.7 [Justified:Low] "Function may be referenced from internal or external" */
BOOL VA_LED_IsLightActive(void)
{
    BOOL RetVal = FALSE;

    if ( VA_LED_Initialized )
    {
        RetVal = (BOOL)(VA_LED_State != VA_LED_OFF);
    }

    return RetVal;
}


/*************************************************************************************************
 * Name               : VA_LED_turnOffLED
 * Input parameter(s) : void
 * Output parameter(s): void
 * Return value       : void
 * Description        : If LED is turned on or in fade-out in will turn directly the LED off.
 *************************************************************************************************/
void VA_LED_turnOffLED(void)
{
    VA_LED_dataReceived = FALSE;
    VA_LED_State = VA_LED_OFF;
    VA_LED_State_Prev = VA_LED_OFF;
    VA_LED_PWMDutyCycle = 0u;
    Pwm_SetOutputToIdle(PTA11_LIGHT_PWM);
    VA_LED_SleepActive = 1u;
    VA_LED_CAN_Req = FALSE;
}
/*-----------------------------------------------------------------------------------------------*/
/* Local functions                                                                               */
/*-----------------------------------------------------------------------------------------------*/

/*************************************************************************************************
 * Name               : VA_LED_UpdateParameters
 * Input parameter(s) : N/A
 * Output parameter(s): N/A
 * Return value       : N/A
 * Description        : Update internal parameters in case Audi parameters were changed:
 *                      - Audi parameters copy
 *                      - maximum PWM duty cycle
 *                      - ramp-up/ramp-down time
 *************************************************************************************************/
static void VA_LED_UpdateParameters(void)
{
    /* If any of the Audi parameters is updated (rare occurence) update all internal parameters and duty cycle / timer parameters */
    if ((VA_LED_AudiParamByte2  != ST_AUDI_NVM_params.U8_Byte_2_Audi_param_NVM)  ||
        (VA_LED_AudiParamByte23 != ST_AUDI_NVM_params.U8_Byte_23_Audi_param_NVM) ||
        (VA_LED_AudiParamByte24 != ST_AUDI_NVM_params.U8_Byte_24_Audi_param_NVM) ||
        (VA_LED_AudiParamByte25 != ST_AUDI_NVM_params.U8_Byte_25_Audi_param_NVM))
    {
        /* Update internal copy of parameters */
        VA_LED_AudiParamByte2  = ST_AUDI_NVM_params.U8_Byte_2_Audi_param_NVM;
        VA_LED_AudiParamByte23 = ST_AUDI_NVM_params.U8_Byte_23_Audi_param_NVM;
        VA_LED_AudiParamByte24 = ST_AUDI_NVM_params.U8_Byte_24_Audi_param_NVM;
        VA_LED_AudiParamByte25 = ST_AUDI_NVM_params.U8_Byte_25_Audi_param_NVM;

        /* Determine enable condition and redo duty cycle & timer parameter calculations */
        VA_LED_EnabledByParam = ((VA_LED_AudiParamByte2 & (U8)BIT6) != (U8)0u);  /* Audi parameter BYTE2 / bit 6 (cp_EnableLighting) */
        VA_LED_PWMDutyCycle_Max = (U16)( (U32)VA_LED_PWM_DUTY_CYCLE_MAX * (U32)VA_LED_AudiParamByte23
                                                                        / (U32)VA_LED_PARAM_DUTY_CYCLE_MAX );
        VA_LED_Timer_SetLimit((U8)VA_LED_TIMER_RAMPUP,   VA_LED_AudiParamByte24 * (U16)VA_LED_RAMP_TIME_FACTOR_MS);
        VA_LED_Timer_SetLimit((U8)VA_LED_TIMER_RAMPDOWN, VA_LED_AudiParamByte25 * (U16)VA_LED_RAMP_TIME_FACTOR_MS);
    }
} 


/*************************************************************************************************
 * Name               : VA_LED_UpdateTimers
 * Input parameter(s) : N/A
 * Output parameter(s): N/A
 * Return value       : N/A
 * Description        : Update timers (cyclic)
 *************************************************************************************************/
static void VA_LED_UpdateTimers(void)
{
    switch ( VA_LED_State )
    {
        case VA_LED_RAMPUP:
            VA_LED_Timer_Tick((U8)VA_LED_TIMER_RAMPUP); 
            break;
        case VA_LED_ON:
            VA_LED_Timer_Tick((U8)VA_LED_TIMER_DIAG); 
            break;
        case VA_LED_RAMPDOWN:
            VA_LED_Timer_Tick((U8)VA_LED_TIMER_RAMPDOWN); 
            break;
        default:
        /*do nothing*/
            break;
    }
}


/*************************************************************************************************
 * Name               : VA_LED_ProcessDiagRequest
 * Input parameter(s) : N/A
 * Output parameter(s): N/A
 * Return value       : N/A
 * Description        : Process (timed) request from diag:
 *                      - set timer to requested value
 *                      - reset timer (i.e. start it)
 *                      - clear request
 *************************************************************************************************/
static void VA_LED_ProcessDiagRequest(void)
{
    if ( VA_LED_Diag_ReqDuration_ms != 0u )  /* New diag request */
    {
        VA_LED_Timer_SetLimit((U8)VA_LED_TIMER_DIAG, VA_LED_Diag_ReqDuration_ms);
        VA_LED_Timer_Reset((U8)VA_LED_TIMER_DIAG);
        VA_LED_Diag_ReqDuration_ms = 0u;  /* Clear request */
    }
}


/*************************************************************************************************
 * Name               : VA_LED_UpdateStateConditions
 * Input parameter(s) : N/A
 * Output parameter(s): N/A
 * Return value       : N/A
 * Description        : Update conditions used for LED state determination:
 *                      - allowance by voltage monitoring
 *                      - request from diag
 *                      - request by CAN message
 *************************************************************************************************/
static void VA_LED_UpdateStateConditions(void)
{
    /* Check voltage permission */
    /* polyspace+1 MISRA-C3:10.5 [Justified:Low] "Cast from u8 to bool is needed in this case" */
    VA_LED_VoltMonAllowed = (BOOL)BatSup_isVoltageInNormal();

    /* Check diag request for LED lighting, only allowed if voltage monitoring also allows it */
    VA_LED_Diag_Req = (VA_LED_Timer_IsRunning((U8)VA_LED_TIMER_DIAG) && VA_LED_VoltMonAllowed);

    /* Check CAN request for LED lighting; only allowed if voltage monitoring also allows it and LED
       lighting is enabled via Audi parameter */
    VA_LED_CAN_Req = (VA_LED_GetComRequest() && VA_LED_VoltMonAllowed && VA_LED_EnabledByParam);
 }


/*************************************************************************************************
 * Name               : VA_LED_StateDetermination
 * Input parameter(s) : N/A
 * Output parameter(s): N/A
 * Return value       : N/A
 * Description        : LED state machine, based on inputs from:
 *                      - voltage monitoring - can set state(s): OFF
 *                      - diagnosis request  - can set state(s): OFF, ON
 *                      - CAn request        - can set state(s): OFF, ON, RAMPUP, RAMPDOWN
 *************************************************************************************************/
static void VA_LED_StateDetermination(void)
{
    /* Voltage monitoring does not allow LED lighting, force LED off regardless of current state (highest priority) */
    if ( VA_LED_VoltMonAllowed == FALSE )
    {
        VA_LED_State = VA_LED_OFF;
    }
    else
    {
        /* Diag request has higher priority then normal operation, force LED on regardless of current state */
        if ( VA_LED_Diag_Req == TRUE )
        {
            VA_LED_State = VA_LED_ON;
        }
        else
        {
            /* If diag request just expired and no CAN request present then turn LED off */
            if ( (VA_LED_DiagEndDetected() == TRUE) && (VA_LED_CAN_Req == FALSE) )
            {  
                VA_LED_State = VA_LED_OFF;
            }

            /* LED state machine for normal operation (lowest priority) */
            switch ( VA_LED_State )
            {
                case VA_LED_OFF:
                    if ( VA_LED_CAN_Req )  /* CAN request present, go to LED fade-in */
                    {
                        VA_LED_Timer_Reset((U8)VA_LED_TIMER_RAMPUP);
                        VA_LED_State = VA_LED_RAMPUP;
                    }
                    break;

                case VA_LED_RAMPUP:
                    if ( VA_LED_Timer_IsExpired((U8)VA_LED_TIMER_RAMPUP) )  /* Fading-in finished, go to LED on */
                    {
                        VA_LED_State = VA_LED_ON;
                    }
                    break;

                case VA_LED_ON:
                    if ( VA_LED_CAN_Req == FALSE )  /* CAN request ceased, go to LED dimming */
                    {
                        VA_LED_Timer_Reset((U8)VA_LED_TIMER_RAMPDOWN);
                        VA_LED_State = VA_LED_RAMPDOWN;
                    }
                    break;

                case VA_LED_RAMPDOWN:
                    if ( VA_LED_Timer_IsExpired((U8)VA_LED_TIMER_RAMPDOWN) )  /* Finished dimming, go to LED off */
                    {
                        VA_LED_State = VA_LED_OFF;
                    }
                    break;

                default:
                /*do nothing*/
                    break;
            }
        }
    }
}


/*************************************************************************************************
 * Name               : VA_LED_CalculatePWMDutyCycle
 * Input parameter(s) : N/A
 * Output parameter(s): N/A
 * Return value       : N/A
 * Description        : Calculate PWM duty cycle:
 *                      - Off      : 0
 *                      - On       : maximum duty cycle (considering Audi param limitation)
 *                      - Ramp-Up  : Proportional to passed time since transition off-on started
 *                      - Ramp-Down: Proportional to remaining time in transition on-off
 *************************************************************************************************/
static void VA_LED_CalculatePWMDutyCycle(void)
{
    switch ( VA_LED_State )
    {
        case VA_LED_OFF:
            VA_LED_PWMDutyCycle = 0u;
            break;

        case VA_LED_RAMPUP:
            VA_LED_PWMDutyCycle = (U16)((U32)VA_LED_PWMDutyCycle_Max * (U32)VA_LED_Timer_GetElapsed((U8)VA_LED_TIMER_RAMPUP)
                                                                     / (U32)VA_LED_Timer_GetLimit((U8)VA_LED_TIMER_RAMPUP));
            break;

        case VA_LED_ON:
            VA_LED_PWMDutyCycle = VA_LED_PWMDutyCycle_Max;
            break;

        case VA_LED_RAMPDOWN:
            VA_LED_PWMDutyCycle = (U16)((U32)VA_LED_PWMDutyCycle_Max * (U32)VA_LED_Timer_GetRemaining((U8)VA_LED_TIMER_RAMPDOWN)
                                                                     / (U32)VA_LED_Timer_GetLimit((U8)VA_LED_TIMER_RAMPDOWN));
            break;

        default:
        /*do nothing*/
            break;
    }
}


/*************************************************************************************************
 * Name               : VA_LED_ApplyPWMDutyCycle
 * Input parameter(s) : N/A
 * Output parameter(s): N/A
 * Return value       : N/A
 * Description        : Apply PWM duty cycle (if needed):
 *                      - when LED is active (on/ramp-up/ramp-down)
 *                      - when LED just turned off (for setting to 0)
 *************************************************************************************************/
static void VA_LED_ApplyPWMDutyCycle(void)
{
    /* Set PWM duty cycle when illumination is on or it has just been turned off (in this last case it's set to 0) */
    if ( VA_LED_IsLightActive() || VA_LED_TurnOffDetected() ) 
    {
        Pwm_SetDutyCycle(PTA11_LIGHT_PWM, VA_LED_PWMDutyCycle);
    }
}


/*************************************************************************************************
 * Name               : VA_LED_UpdateDelayValues
 * Input parameter(s) : N/A
 * Output parameter(s): N/A
 * Return value       : N/A
 * Description        : Update delayed (previous) values (used for state transition)
 *************************************************************************************************/
static void VA_LED_UpdateDelayValues(void)
{
    VA_LED_State_Prev    = VA_LED_State;
    VA_LED_Diag_Req_Prev = VA_LED_Diag_Req;
}


/*************************************************************************************************
 * Name               : VA_LED_GetComRequest
 * Input parameter(s) : N/A
 * Output parameter(s): N/A
 * Return value       : N/A
 * Description        : Get CAN/LIN request - read and evaluate signals:
 *                      - EL_Umfeldleuchte_VL_Anf
 *                      - EL_Umfeldleuchte_VR_Anf
 *************************************************************************************************/
static BOOL VA_LED_GetComRequest(void)
{
    U8 U8_EL_Umfeldleuchte_VL_Anf = 0u;
    U8 U8_EL_Umfeldleuchte_VR_Anf = 0u;

    // (void)Com_ReceiveSignal(ComConf_ComSignal_EL_Umfeldleuchte_VL_Anf_XIX_ExteriorLight_01_XIX_HCP4_CANFD01_aff410fa_Rx, &U8_EL_Umfeldleuchte_VL_Anf);
    // (void)Com_ReceiveSignal(ComConf_ComSignal_EL_Umfeldleuchte_VR_Anf_XIX_ExteriorLight_01_XIX_HCP4_CANFD01_19f8e78c_Rx, &U8_EL_Umfeldleuchte_VR_Anf);

    /* polyspace+6 MISRA-C3:14.3 [Justified:Low] "Condition always true" */
    if (1u == VA_LED_SleepActive)
    {
        U8_EL_Umfeldleuchte_VL_Anf = 0u;
        U8_EL_Umfeldleuchte_VR_Anf = 0u;
        if ((0u == U8_EL_Umfeldleuchte_VL_Anf) && (0u == U8_EL_Umfeldleuchte_VR_Anf))
        {
            VA_LED_SleepActive = 0u;
        }
    }
    return (BOOL)((U8_EL_Umfeldleuchte_VL_Anf != 0u) || (U8_EL_Umfeldleuchte_VR_Anf != 0u));
}


/*************************************************************************************************
 * Name               : VA_LED_TurnOffDetected
 * Input parameter(s) : N/A
 * Output parameter(s): N/A
 * Return value       : N/A
 * Description        : Edge detection for LED-off
 *************************************************************************************************/
static BOOL VA_LED_TurnOffDetected(void)
{
    return (BOOL)((VA_LED_State_Prev != VA_LED_OFF) && (VA_LED_State == VA_LED_OFF));
}


/*************************************************************************************************
 * Name               : VA_LED_DiagEndDetected
 * Input parameter(s) : N/A
 * Output parameter(s): N/A
 * Return value       : N/A
 * Description        : Edge detection for diagnostic request end
 *************************************************************************************************/
static BOOL VA_LED_DiagEndDetected(void)
{
    return (BOOL)((VA_LED_Diag_Req_Prev == TRUE) && (VA_LED_Diag_Req == FALSE));
}


/*-----------------------------------------------------------------------------------------------*/
/* (Local) Timer functions                                                                       */
/*-----------------------------------------------------------------------------------------------*/

/*************************************************************************************************
 * Name               : VA_LED_Timer_SetLimit
 * Input parameter(s) : U8  - timer ID
 *                      U16 - timer limit (ms)
 * Output parameter(s): N/A
 * Return value       : N/A
 * Description        : Set timer limit
 *************************************************************************************************/
static void VA_LED_Timer_SetLimit(U8 U8_TimerID, U16 U16_Limit_ms)
{
    VA_LED_Timers[U8_TimerID].Limit_ms = U16_Limit_ms;
}


/*************************************************************************************************
 * Name               : VA_LED_Timer_Reset
 * Input parameter(s) : U8 - timer ID
 * Output parameter(s): N/A
 * Return value       : N/A
 * Description        : Reset timer counter
 *************************************************************************************************/
static void VA_LED_Timer_Reset(U8 U8_TimerID)
{
    VA_LED_Timers[U8_TimerID].Value_ms = VA_LED_Timers[U8_TimerID].Limit_ms;
}


/*************************************************************************************************
 * Name               : VA_LED_Timer_Tick
 * Input parameter(s) : U8 - timer ID
 * Output parameter(s): N/A
 * Return value       : N/A
 * Description        : Decrease timer counter with task time (countdown timer)
 *************************************************************************************************/
static void VA_LED_Timer_Tick(U8 U8_TimerID)
{
    if ( VA_LED_Timers[U8_TimerID].Value_ms > (U16)VA_LED_TASK_TIME_MS )
    {
        VA_LED_Timers[U8_TimerID].Value_ms -= (U16)VA_LED_TASK_TIME_MS;
    }
    else
    {
        VA_LED_Timers[U8_TimerID].Value_ms = (U16)0u;
    }
}


/*************************************************************************************************
 * Name               : VA_LED_Timer_Tick
 * Input parameter(s) : U8 - timer ID
 * Output parameter(s): N/A
 * Return value       : BOOL - TRUE: timer runing, FALSE: timer expired
 * Description        : Check if timer is running (i.e. not expired)
 *************************************************************************************************/
static BOOL VA_LED_Timer_IsRunning(U8 U8_TimerID)
{
    return (BOOL)(VA_LED_Timers[U8_TimerID].Value_ms > (U16)0u);
}


/*************************************************************************************************
 * Name               : VA_LED_Timer_IsExpired
 * Input parameter(s) : U8 - timer ID
 * Output parameter(s): N/A
 * Return value       : BOOL - TRUE: timer expired, FALSE: timer still running
 * Description        : Check if timer elapsed/expired
 *************************************************************************************************/
static BOOL VA_LED_Timer_IsExpired(U8 U8_TimerID)
{
    return (BOOL)(VA_LED_Timers[U8_TimerID].Value_ms == (U16)0u);
}


/*************************************************************************************************
 * Name               : VA_LED_Timer_GetLimit
 * Input parameter(s) : U8 - timer ID
 * Output parameter(s): N/A
 * Return value       : U16 - timer limit (ms)
 * Description        : Return timer limit (maximum value)
 *************************************************************************************************/
static U16 VA_LED_Timer_GetLimit(U8 U8_TimerID)
{
    return VA_LED_Timers[U8_TimerID].Limit_ms;
}


/*************************************************************************************************
 * Name               : VA_LED_Timer_GetElapsed
 * Input parameter(s) : U8 - timer ID
 * Output parameter(s): N/A
 * Return value       : U16 - elapse time (ms)
 * Description        : Return elapsed time since timer was reset
 *************************************************************************************************/
static U16 VA_LED_Timer_GetElapsed(U8 U8_TimerID)
{
    U16 RetVal = 0u;

    if (VA_LED_Timers[U8_TimerID].Value_ms < VA_LED_Timers[U8_TimerID].Limit_ms)
    {
        RetVal = (VA_LED_Timers[U8_TimerID].Limit_ms - VA_LED_Timers[U8_TimerID].Value_ms);
    }
    return RetVal;
}


/*************************************************************************************************
 * Name               : VA_LED_Timer_GetRemaining
 * Input parameter(s) : U8 - timer ID
 * Output parameter(s): N/A
 * Return value       : U16 - remaining time (ms)
 * Description        : Return remaining time until timer expires
 *************************************************************************************************/
static U16 VA_LED_Timer_GetRemaining(U8 U8_TimerID)
{
    return VA_LED_Timers[U8_TimerID].Value_ms;
}

