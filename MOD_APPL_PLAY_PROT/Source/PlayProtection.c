/*
 * PlayProtection.c
 */
#include "PlayProtection.h"
#include "NvmMng.h"

#include "inductive_sensor_algo.h"
#include "sensor_algo.h"

/* ******************** Macro Declaration ******************** */
#define PLAYPROT_NR_OF_CALLS_PER_S 40u

/* ******************** Type Definitions ******************** */
/* polyspace+1 MISRA-C3:2.4 [Justified:Low] "Added for further implementation." */
typedef enum activationStateEnum
{
    PlayProt_notInitialized = 0u,
    PlayProt_initialized,
    PlayProt_Low,
    PlayProt_High
} PlayProt_activationStateType;

typedef U8 (*PlayProt_pfuncRetU8)(void);
typedef void (*PlayProt_pfuncCallback)(void);

/* polyspace+1 MISRA-C3:2.4 [Justified:Low] "Added for further implementation." */
typedef struct configVariables
{
    U16 evalTimeValue;
    U16 evalTimeCounter;
    U16 enabledDecValue;
    U16 enabledDecCounter;
    U16 decTimeCounter;
    U8 activationCounter;
    U8 enabled;
    U8 PPConfigured;
    PlayProt_activationStateType activationState;
} PlayProt_configVarType;

/* polyspace+1 MISRA-C3:2.4 [Justified:Low] "Added for further implementation." */
typedef struct configConst
{
    PlayProt_pfuncRetU8 pFunctActivationPresent;
    PlayProt_pfuncRetU8 pFunctConfigElemPresent;
    PlayProt_pfuncCallback callbackRaisingEdge;
    PlayProt_pfuncCallback callbackHigh;
    PlayProt_pfuncCallback callbackFallingEdge;
    U8 *audiEvalTimeParam;
    U8 *audiEnabledDecTimeParam;
    U8 activateCounterPeak;
    U8 disabledDecValue;
} PlayProt_configConstType;

/* ******************** Local Functions Declarations ******************** */
static U8 PlayProt_activationPresentInductiveUnlock(void);
static U8 PlayProt_activationPresentLock(void);
static U8 PlayProt_inductiveUnlockPresent(void);
static void PlayProt_initChannel(U8 counter);
/* State handle functions, used only for leasibility */
static void PlayProt_handleInit(U8 index, U8 activationState);
static void PlayProt_handleLow(U8 index, U8 activationState);
static void PlayProt_handleHigh(U8 index, U8 activationState);
/* Callbacks, sensor specific */
static void PlayProt_activationIsHighInductivAndUnlock(void);
static void PlayProt_raisingEdgeInductivAndUnlock(void);
static void PlayProt_fallingEdgeInductivAndUnlock(void);


/* ******************** Constant and Variables definition ******************** */

static const PlayProt_configConstType PlayProt_configConst[PlayProt_nrOfElements] =
{
    {
        &PlayProt_activationPresentInductiveUnlock,
        &PlayProt_inductiveUnlockPresent,
        &PlayProt_raisingEdgeInductivAndUnlock,
        &PlayProt_activationIsHighInductivAndUnlock,
        &PlayProt_fallingEdgeInductivAndUnlock,
        /* audiEvalTimeParam */
        &(ST_AUDI_NVM_params.U8_Byte_44_Audi_param_NVM),
        /* audiEnabledDecTimeParam */
        &(ST_AUDI_NVM_params.U8_Byte_45_Audi_param_NVM),
        200u, /* peak value for activate counter */
        10u   /* const value used to decrement from peak activate counter */
    },
    {
        &PlayProt_activationPresentLock,
        &NvmMng_getEnableKessyMisuseProtection,
        NULL,
        NULL,
        NULL,
        /* audiEvalTimeParam */
        &(ST_AUDI_NVM_params.U8_Byte_46_Audi_param_NVM),
        /* audiEnabledDecTimeParam */
        &(ST_AUDI_NVM_params.U8_Byte_47_Audi_param_NVM),
        200u, /* peak value for activate counter */
        10u   /* const value used to decrement from peak activate counter */
    }
};

static PlayProt_configVarType PlayProt_configVar[PlayProt_nrOfElements];

/* Specific variables and configurations - inductive and unlock */
static U8 const PlayProt_minActivateTimeValue = 20u; /* 500ms, delay used for inductive signal time */
static U8 PlayProt_minActivateTimerCounter = 0u;
static U8 PlayProt_prevInductiveVal = 0u;
/* ******************** Interface definition ******************** */

/*********************************************************************************************************
 *  Name                   : PlayProt_init
 *  Description            : Init function clears all states and counters
 *  Parameters             : void
 *  Return                 : void
 *  Critical/explanation   : -
 *  Author                 : petre
 *********************************************************************************************************/
void PlayProt_init(void)
{
    U8 counter;

    for (counter = 0u; counter < (U8)PlayProt_nrOfElements; counter += 1u)
    {
        PlayProt_initChannel(counter);
    }
}

/*********************************************************************************************************
 *  Name                   : PlayProt_mainRunnable
 *  Description            : This is the main runnable while ECU is in Active for PlPr. In this function the PlPr mode can
 *                         : be activated when it detects more activations within a specified time.
 *                         :
 *  Parameters             : void
 *  Return                 : void
 *  Critical/explanation   : -
 *  Author                 : petre
 *********************************************************************************************************/
/* polyspace+25 MISRA-C3:10.1 [Justified:Low] "variable PlayProt_enConfigElemType starts counting from 0 and is intentionally added like this" */
/* polyspace+15 MISRA-C3:10.3 [Justified:Low] "variable PlayProt_enConfigElemType starts counting from 0 and is intentionally added like this" */
/* polyspace+4 MISRA-C3:5.8 [Justified:Low] "Variable index is local and will not affect the code" */
void PlayProt_mainRunnable(void)
{
    PlayProt_enConfigElemType index;
    /* Update NvM parameters locally. */
    PlayProt_updateParameter();

    /* polyspace+1 MISRA-C3:10.5 [Justified:Low] "Cast from is needed in this case" */
    for (index = (PlayProt_enConfigElemType)0u; index < PlayProt_nrOfElements; index += (PlayProt_enConfigElemType)1u)
    {
        if (PlayProt_configVar[index].activationState >= PlayProt_initialized)
        {
            U8 activationPresent = PlayProt_configConst[index].pFunctActivationPresent();
            U8 playProtConfigured = PlayProt_configConst[index].pFunctConfigElemPresent();
            /* In case that there is a transition from 0 to 1 init PP */
            if((playProtConfigured == 0u) && (PlayProt_configVar[index].PPConfigured != 0u))
            {
                PlayProt_initChannel((U8)index);
            }
            PlayProt_configVar[index].PPConfigured = playProtConfigured;
            if (playProtConfigured != 0u)
            {
                if (PlayProt_configVar[index].activationState == PlayProt_initialized)
                {
                    /* Only once after init */
                    PlayProt_handleInit((U8)index, activationPresent);
                }
                else
                {
                    if (PlayProt_configVar[index].activationState == PlayProt_Low)
                    {
                        PlayProt_handleLow((U8)index, activationPresent);
                    }
                    else
                    {
                        PlayProt_handleHigh((U8)index, activationPresent);
                    }
                }
            }
        }
    }
}


/*********************************************************************************************************
 *  Name                   : PlayProt_mainRunSleep
 *  Description            : This is the main runnable for PlPr while ECU is in sleep. In this function the PlPr mode can
 *                         : be activated when it detects more activations within a specified time.
 *                         :
 *  Parameters             : void
 *  Return                 : void
 *  Critical/explanation   : -
 *  Author                 : petre
 *********************************************************************************************************/
/* polyspace+25 MISRA-C3:10.1 [Justified:Low] "variable PlayProt_enConfigElemType starts counting from 0 and is intentionally added like this" */
/* polyspace+15 MISRA-C3:10.3 [Justified:Low] "variable PlayProt_enConfigElemType starts counting from 0 and is intentionally added like this" */
/* polyspace+4 MISRA-C3:5.8 [Justified:Low] "Variable index is local and will not affect the code" */
void PlayProt_mainRunSleep(void)
{
    /* Since this is a function called in sleep, the assumption is that there is no NVM change */
    PlayProt_enConfigElemType index;

    /* polyspace+1 MISRA-C3:10.5 [Justified:Low] "Cast from is needed in this case" */
    for (index = (PlayProt_enConfigElemType)0u; index < PlayProt_nrOfElements; index += (PlayProt_enConfigElemType)1u)
    {
        if (PlayProt_configVar[index].PPConfigured != 0u)
        {
            U8 activationPresent = PlayProt_configConst[index].pFunctActivationPresent();
            if (PlayProt_configVar[index].activationState == PlayProt_Low)
            {
                PlayProt_handleLow((U8)index, activationPresent);
            }
            else
            {
                PlayProt_handleHigh((U8)index, activationPresent);
            }
        }
    }
}

/*********************************************************************************************************
 *  Name                   : PlayProt_updateParamete
 *  Description            : Function called to update times parameters in case of NVM change
 *  Parameters             : void
 *  Return                 : void
 *  Critical/explanation   : -
 *  Author                 : petre
 *********************************************************************************************************/
void PlayProt_updateParameter(void)
{
    U8 counter;
    for (counter = 0u; counter < (U8)PlayProt_nrOfElements; counter += 1u)
    {
        PlayProt_configVar[counter].evalTimeValue = (U16)(*(PlayProt_configConst[counter].audiEvalTimeParam)) * (U16)PLAYPROT_NR_OF_CALLS_PER_S;
        PlayProt_configVar[counter].enabledDecValue = (U16)(*(PlayProt_configConst[counter].audiEnabledDecTimeParam)) * (U16)PLAYPROT_NR_OF_CALLS_PER_S;
    }
}

/*********************************************************************************************************
 *  Name                   : PlayProt_getActivationCounter
 *  Description            : This is an interface for getting the Misuse_Protection_Counter
 *                         : used for RID 0x523E, byte 1
 *  Parameters             : PlayProt_configVarType - index for component/feature value
 *  Return                 : U8 - counter value
 *  Critical/explanation   : -
 *  Author                 : tghenci
 *********************************************************************************************************/
/* polyspace+1 MISRA-C3:15.5 [Justified:Low] "Does not affect the functionality, function returns only one value" */
U8 PlayProt_getActivationCounter(PlayProt_enConfigElemType usedComponent)
{
    U8 retval = 0u;
    if (usedComponent < PlayProt_nrOfElements)
    {
        retval = PlayProt_configVar[usedComponent].activationCounter;
    }
    return retval;
}

/*********************************************************************************************************
 *  Name                   : PlayProt_getActiveState
 *  Description            : This is an interface for getting if play protection is active or not. (reached peak value)
 *  Parameters             : PlayProt_configVarType - index for component/feature value
 *  Return                 : 1 enabled, peak reached, 0 not active
 *  Critical/explanation   : -
 *  Author                 : petre
 *********************************************************************************************************/
U8 PlayProt_getActiveState(PlayProt_enConfigElemType usedComponent)
{
    U8 retval = 0u;
    if(usedComponent < PlayProt_nrOfElements)
    {
        retval = PlayProt_configVar[usedComponent].enabled;
    }
    return retval;
}

/*********************************************************************************************************
 *  Name                   : PlayProt_getInductiveActiveTime
 *  Description            : This is an interface for getting Inductive active delay value
 *                           Should be called after Play Protection sleep runnable function.
 *                           Wake-up shall be made only of counter is 0
 *  Parameters             : void
 *  Return                 : U8 counter value
 *  Critical/explanation   : -
 *  Author                 : petre
 *********************************************************************************************************/
U8 PlayProt_getInductiveActiveTime(void)
{
    return PlayProt_minActivateTimerCounter;
}

void PlayProt_writeLockValue(U8* signalVal)
{
    if(PlayProt_configVar[PlayProt_capaLock].enabled != 0u)
    {
        *signalVal = 0u;
    }
}

void PlayProt_writeUnlockValue(U8* signalVal)
{
    if(PlayProt_configVar[PlayProt_inductive].enabled != 0u)
    {
        *signalVal = 0u;
    }
}

void PlayProt_writeInductiveValue(U8* signalVal)
{
    if(PlayProt_minActivateTimerCounter != 0u)
    {
        *signalVal = 0u;
    }
}

/* ******************** Local functions definition ******************** */

/*********************************************************************************************************
 *  Name                   : PlayProt_initChannel
 *  Description            : Indicates if there is an activation, for inductive and unlock
 *  Parameters             : U8 Channel ID
 *  Return                 : void
 *  Critical/explanation   : -
 *  Author                 : petre
 *********************************************************************************************************/
static void PlayProt_initChannel(U8 counter)
{
	PlayProt_configVar[counter].evalTimeValue = (U16)(*(PlayProt_configConst[counter].audiEvalTimeParam)) * (U16)PLAYPROT_NR_OF_CALLS_PER_S;
	PlayProt_configVar[counter].evalTimeCounter = 0u;
	PlayProt_configVar[counter].enabledDecValue = (U16)(*(PlayProt_configConst[counter].audiEnabledDecTimeParam)) * (U16)PLAYPROT_NR_OF_CALLS_PER_S;
	PlayProt_configVar[counter].enabledDecCounter = 0u;
	PlayProt_configVar[counter].decTimeCounter = 0u;
	PlayProt_configVar[counter].activationCounter = 0u;
	PlayProt_configVar[counter].enabled = 0u;
	PlayProt_configVar[counter].activationState = PlayProt_initialized;
    PlayProt_configVar[counter].PPConfigured = PlayProt_configConst[counter].pFunctConfigElemPresent();
}

/*********************************************************************************************************
 *  Name                   : PlayProt_activationPresentInductiveUnlock
 *  Description            : Indicates if there is an activation, for inductive and unlock
 *  Parameters             : void
 *  Return                 : U8 - activation present or not
 *  Critical/explanation   : -
 *  Author                 : petre
 *********************************************************************************************************/
static U8 PlayProt_activationPresentInductiveUnlock(void)
{
    U8 unlockCapaVal = 0u;
    U8 inductiveVal = 0u;
    U8 retVal = 0u;

    Algo_getErState(&unlockCapaVal);
    inductiveVal = InductiveAlgo_getInductiveValue();
    if ((unlockCapaVal != 0) || (inductiveVal != 0))
    {
        retVal = 1u;
    }
    return retVal;
}

/*********************************************************************************************************
 *  Name                   : PlayProt_activationPresentLock
 *  Description            : Indicates if there is an activation, lock
 *  Parameters             : void
 *  Return                 : U8 - activation present or not
 *  Critical/explanation   : -
 *  Author                 : petre
 *********************************************************************************************************/
static U8 PlayProt_activationPresentLock(void)
{
    U8 lockCapaVal = 0u;
    U8 retVal = 0u;

    Algo_getVrState(&lockCapaVal);
    if (lockCapaVal != 0)
    {
        retVal = 1u;
    }
    return retVal;
}

/*********************************************************************************************************
 *  Name                   : PlayProt_inductiveUnlockPresent
 *  Description            : Indicates if play protection is enabled for inductive and unlock sensors
 *  Parameters             : void
 *  Return                 : U8 - play protection is enabled for this component
 *  Critical/explanation   : -
 *  Author                 : petre
 *********************************************************************************************************/

static U8 PlayProt_inductiveUnlockPresent(void)
{
    return 1u;
}

/* State handle functions, used only for leasibility */
/* polyspace+1 MISRA-C3:5.8 [Justified:Low] "Variable index is local and will not affect the code" */
static void PlayProt_handleInit(U8 index, U8 activationState)
{
    if (activationState != 0u)
    {
        /* First activation, consider it as a transition from 0 to 1 and */
        PlayProt_configVar[index].activationState = PlayProt_High;
    }
    else
    {
        PlayProt_configVar[index].activationState = PlayProt_Low;
    }
}
/* polyspace+1 MISRA-C3:5.8 [Justified:Low] "Variable index is local and will not affect the code" */
static void PlayProt_handleLow(U8 index, U8 activationState)
{
    if (activationState != 0u)
    {
        /* Raising Edge Transition */
        if (PlayProt_configVar[index].evalTimeCounter > 0u)
        {
            /* There was a previous raising edge in the last 10s */
            PlayProt_configVar[index].activationCounter += 1u;
            PlayProt_configVar[index].evalTimeCounter = 0u;
            PlayProt_configVar[index].decTimeCounter = 0u;
            if (PlayProt_configVar[index].activationCounter >= PlayProt_configConst[index].activateCounterPeak)
            {
                PlayProt_configVar[index].activationCounter = PlayProt_configConst[index].activateCounterPeak;
                PlayProt_configVar[index].enabled = 1u;
                PlayProt_configVar[index].decTimeCounter = 0u;
                PlayProt_configVar[index].enabledDecCounter = 0u;
            }
        }
        else
        {
            /*
             * There are more then 10s from last sensor activation, nothing to do here
             * The minimum activation time is started on falling edge
             */
        }
        PlayProt_configVar[index].activationState = PlayProt_High;
        if( PlayProt_configConst[index].callbackRaisingEdge != NULL)
        {
            PlayProt_configConst[index].callbackRaisingEdge();
        }
    }
    else
    {
        /* no state change, check which counter shall be decremented */
        if (PlayProt_configVar[index].evalTimeCounter > 0u)
        {
            PlayProt_configVar[index].evalTimeCounter -= 1u;
        }
        if (PlayProt_configVar[index].enabled == 1u)
        {
            /* Additional check, enabledDecCntValue should never be 0 while play protection is enabled */
            if (PlayProt_configVar[index].enabledDecCounter > 0u)
            {
                PlayProt_configVar[index].enabledDecCounter -= 1u;
                if (PlayProt_configVar[index].enabledDecCounter == 0u)
                {
                    /* Disable play protection */
                    PlayProt_configVar[index].enabled = 0u;
                    PlayProt_configVar[index].decTimeCounter = (U16)(*(PlayProt_configConst[index].audiEvalTimeParam)) * (U16)PLAYPROT_NR_OF_CALLS_PER_S;
                    PlayProt_configVar[index].activationCounter -= PlayProt_configConst[index].disabledDecValue;
                }
            }
        }
        else
        {
            if (PlayProt_configVar[index].decTimeCounter > 0u)
            {
                PlayProt_configVar[index].decTimeCounter -= 1u;
                if (PlayProt_configVar[index].decTimeCounter == 0u)
                {
                    if (PlayProt_configVar[index].activationCounter > 0u)
                    {
                        PlayProt_configVar[index].activationCounter -= 1u;
                        if (PlayProt_configVar[index].activationCounter > 0u)
                        {
                            PlayProt_configVar[index].decTimeCounter = (U16)(*(PlayProt_configConst[index].audiEvalTimeParam)) * (U16)PLAYPROT_NR_OF_CALLS_PER_S;
                        }
                    }
                }
            }
        }
    }
}

/* polyspace+1 MISRA-C3:5.8 [Justified:Low] "Variable index is local and will not affect the code" */
static void PlayProt_handleHigh(U8 index, U8 activationState)
{
    /* Activation was present, check for new value */
    if (activationState != 0)
    {
        /* just wait for the falling edge and call the callback */
        if( PlayProt_configConst[index].callbackHigh != NULL)
        {
            PlayProt_configConst[index].callbackHigh();
        }
    }
    else
    {
        /* falling edge */
        PlayProt_configVar[index].evalTimeCounter = PlayProt_configVar[index].evalTimeValue;
        if (PlayProt_configVar[index].enabled == 1u)
        {
            PlayProt_configVar[index].enabledDecCounter = PlayProt_configVar[index].enabledDecValue;
        }
        else
        {
            PlayProt_configVar[index].decTimeCounter = (U16)(*(PlayProt_configConst[index].audiEvalTimeParam)) * (U16)PLAYPROT_NR_OF_CALLS_PER_S;
        }
        PlayProt_configVar[index].activationState = PlayProt_Low;
        if( PlayProt_configConst[index].callbackFallingEdge != NULL)
        {
            PlayProt_configConst[index].callbackFallingEdge();
        }
    }
}

/* Callback funcions for sensor specific behaviour */
static void PlayProt_activationIsHighInductivAndUnlock(void)
{
    if(PlayProt_configVar[PlayProt_inductive].enabled == 1u)
    {
        U8 inductiveVal = 0u;
        inductiveVal = InductiveAlgo_getInductiveValue();
        if(inductiveVal != 0u)
        {
            if(PlayProt_minActivateTimerCounter > 0u)
            {
                PlayProt_minActivateTimerCounter -= 1u;
            }
            /* Prev val of inductive was 0, restart counting */
            if(PlayProt_prevInductiveVal == 0u)
            {
                PlayProt_minActivateTimerCounter = PlayProt_minActivateTimeValue;
            }
        }
        else
        {
            PlayProt_minActivateTimerCounter = 0u;
        }
        PlayProt_prevInductiveVal = inductiveVal;
    }
    else
    {
        PlayProt_minActivateTimerCounter = 0u;
    }
}

static void PlayProt_raisingEdgeInductivAndUnlock(void)
{
    if(PlayProt_configVar[PlayProt_inductive].enabled == 1u)
    {
        U8 inductiveVal = 0u;
        inductiveVal = InductiveAlgo_getInductiveValue();
        if(inductiveVal != 0u)
        {
            PlayProt_minActivateTimerCounter = PlayProt_minActivateTimeValue;
        }
        else
        {
            PlayProt_minActivateTimerCounter = 0u;
        }
        PlayProt_prevInductiveVal = inductiveVal;
    }
}

static void PlayProt_fallingEdgeInductivAndUnlock(void)
{
    PlayProt_minActivateTimerCounter = 0u;
}

