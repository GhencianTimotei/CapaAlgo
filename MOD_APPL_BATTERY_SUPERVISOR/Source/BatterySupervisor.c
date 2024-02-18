/* polyspace+1 MISRA-C3:1.1 [Justified:Low] "All macro definitions are needed." */
/*------------------------------------------------------------------------------------------------+
| File: BatterySupervisor.c                                                                         |
+-------------------------------------------------------------------------------------------------+
| Project: Audi eTab                                                                              |
+-------------------------------------------------------------------------------------------------+
| Short description: The file contains the implementation of the Voltage Monitor module           |

+------------------------------------------------------------------------------------------------*/

/* Header files include */
#include "Std_Types.h"
#include "NvmMng.h"
#include "MeasureSupply.h"
#include "Com.h"
#include "can_appl.h"
#include "EmergencyAccess.h"

#include "BatterySupervisor.h"

/******************************** Local type definitions and macros **********************************/
/* polyspace+1 MISRA-C3:2.4 [Justified:Low] "Added for further implementation." */
typedef enum algoState
{
    BATSUP_NO_INIT = 0u,
    BATSUP_IDLE,
    BATSUP_PENDING,
    BATSUP_DEBOUNCE
} BatSup_algoStateType;

/* polyspace+1 MISRA-C3:2.4 [Justified:Low] "Added for further implementation." */
typedef struct voltageRange
{
    U16 thresholdLow;
    U16 thresholdHigh;
} BatSup_voltageRangeType;

/* polyspace+5 MISRA-C3:2.5 [Justified:Low] "Macro should be kept for future usage" */
#define BATSUP_MAX_UNSIGNED_10DIGIT (1024u)
#define BATSUP_QUEUE_SIZE (10u)
#define BATSUP_MAX_VOLTAGE_CNT (7u)
#define BATSUP_MAX_COM_ERROR_CNT (2u)
#define BATSUP_MAX_COM_ERROR_SIZE (3u)

/******************************** Local variables ****************************************************/
/* Reference value used in Pending and Debounce states */
static U16 BatSup_refVoltageValue = 0u;
/* Voltage states on each algorithm state */
static BatSup_voltageStateType BatSup_voltState;
static BatSup_voltageStateType BatSup_voltPeddingState;
static BatSup_voltageStateType BatSup_voltDebounceState;
static BatSup_voltageStateType BatSup_firstState;
/* Algorithm state */
static BatSup_algoStateType BatSup_algoState;
/* Error state */
static BatSup_errorStateType BatSup_errorState;
/* Queue and queue counters */
static BatSup_voltageStateType BatSup_queue[BATSUP_QUEUE_SIZE];
static U16 BatSup_debounceCounter = 0u;
static U8 BatSup_queueHead = 0u;
static U8 BatSup_queueCurrSize = 0u;
static U8 BatSup_queueUnderCnt = 0u;
static U8 BatSup_queueNormalCnt = 0u;
static U8 BatSup_queueOverCnt = 0u;
/* Debounce time, read from NVM */
static U16 BatSup_voltageDebounceTime;
/* After Init transition from pending is idle, not debounce */
static U8 BatSup_pendingAfterInit = 0u;
/* Needed for UDS */
static U16 BatSup_voltageValue = 0u;


/******************************** Constant definitions ***********************************************/

/* Hysteresis values, when new value is lower then reference, values are used as [a,b] and NOT (a,b) */
static const BatSup_voltageRangeType BatSup_voltageRangeHystHigh[BATSUP_VOLT_STATE_COUNT] =
{
    /* BATSUP_COM_OFF_1 */
    {
        1u,	/*Low threshold*/
        238u	/*High threshold*/
    },
    /* BATSUP_UNDERVOLTAGE */
    {
        239u,	/*Low threshold*/
        294u	/*High threshold*/
    },
    /* BATSUP_NOMAL */
    {
        295u,	/*Low threshold*/
        648u	/*High threshold*/
    },
    /* BATSUP_OVERVOLTAGE */
    {
        649u,	/*Low threshold*/
        724u	/*High threshold*/
    },
    /* BATSUP_COM_OFF_2 */
    {
        725u,	/*Low threshold*/
        1023u	/*High threshold*/
    }
};

/* Hysteresis values, when new value is higher then reference, values are used as [a,b] and NOT (a,b) */
static const BatSup_voltageRangeType BatSup_voltageRangeHystLow[BATSUP_VOLT_STATE_COUNT] =
{
    /* BATSUP_COM_OFF_1 */
    {
        1u,	/*Low threshold*/
        228u	/*High threshold*/
    },
    /* BATSUP_UNDERVOLTAGE */
    {
        229u,	/*Low threshold*/
        284u	/*High threshold*/
    },
    /* BATSUP_NOMAL */
    {
        285u,	/*Low threshold*/
        638u	/*High threshold*/
    },
    /* BATSUP_OVERVOLTAGE */
    {
        639u,	/*Low threshold*/
        714u	/*High threshold*/
    },
    /* BATSUP_COM_OFF_2 */
    {
        715u,	/*Low threshold*/
        1023u	/*High threshold*/
    }
};

static const U16 BatSup_thresholdComOff1 = 233u;
static const U16 BatSup_thresholdUndervoltage = 289u;
static const U16 BatSup_thresholdOvervoltage = 643u;   
static const U16 BatSup_thresholdComOff2 = 719u;

static const U16 BatSup_midRefVoltValue[BATSUP_VOLT_STATE_COUNT] =
{
    115u, /* BATSUP_COM_OFF_1 */
    260u, /* BATSUP_UNDERVOLTAGE */
    450u, /* BATSUP_NOMAL */
    680u, /* BATSUP_OVERVOLTAGE */
    870u  /* BATSUP_COM_OFF_2 */
};

/******************************** Local functions declaration ****************************************/

static U16 BatSup_getRefValue(BatSup_voltageStateType stateType);
static BatSup_voltageStateType BatSup_getFirstState(U16 value);
static U8 BatSup_isADC_Valid(U16 value);
static BatSup_voltageStateType BatSup_getVoltState(U16 value);
static void BatSup_addToQueue(BatSup_voltageStateType voltState);
static void BatSup_flushQueue(void);
static void BatSup_removeFromQueue(void);
static void BatSup_incCounter(BatSup_voltageStateType voltState);
static void BatSup_handleQueueData(BatSup_voltageStateType voltState);
static void BatSup_goToIdle(BatSup_voltageStateType voltState);
static void BatSup_handleNewState(BatSup_voltageStateType voltState);
static void BatSup_stateComOff(void);
static void BatSup_stateRecoverFromComOff(void);

/******************************** Interface functions definitions ************************************/

U8 BatSup_idleTask(void)
{
    BatSup_voltageStateType voltState;
    U16 voltageValue;
    U8 retVal = 0u;
    EmergencyAccess_stateType localEmergencyState;

    localEmergencyState = EmergencyAccess_getState();
    if(localEmergencyState != EmergencyAccess_HIGH)
    {
        if(BatSup_algoState == BATSUP_IDLE)
        {
            retVal = 1u;
            voltageValue = MeasureSupply_getUbattVoltage();
            if (BatSup_isADC_Valid(voltageValue) != 0U)
            {
                BatSup_voltageValue = voltageValue;
                voltState = BatSup_getVoltState(voltageValue);
                if(voltState != BatSup_voltState)
                {
                    BatSup_algoState = BATSUP_PENDING;
                    BatSup_addToQueue(voltState);
                }
            }
        }
    }
    else
    {
        /* actuator is on high, don't call fast if ECU is in normal */
        retVal = 1u;
    }
    return retVal;
}

void BatSup_fastTask(void)
{
    BatSup_voltageStateType voltState;
    U16 voltageValue;
    EmergencyAccess_stateType localEmergencyState;

    localEmergencyState = EmergencyAccess_getState();
    if(localEmergencyState != EmergencyAccess_HIGH)
    {
        if(BatSup_algoState > BATSUP_IDLE)
        {
            voltageValue = MeasureSupply_getUbattVoltage();
            if (BatSup_isADC_Valid(voltageValue) != 0U)
            {
                BatSup_voltageValue = voltageValue;
                voltState = BatSup_getVoltState(voltageValue);
                if(BatSup_algoState == BATSUP_PENDING)
                {
                    BatSup_addToQueue(voltState);
                }
                else
                {
                    BatSup_debounceCounter += 1u;
                    BatSup_addToQueue(voltState);
                    /* In addToQueue algoState can be changed to BATSUP_PENDING */
                    if(BatSup_algoState == BATSUP_DEBOUNCE)
                    {
                        if(BatSup_debounceCounter >= BatSup_voltageDebounceTime)
                        {
                            if(BatSup_voltPeddingState == BatSup_voltDebounceState)
                            {
                                BatSup_goToIdle(BatSup_voltDebounceState);
                            }
                            else
                            {
                                /* This case should be reached when after debounce time no valid debounce state was determined */
                                /* Pedding and Debounde state are different, start over */
                                BatSup_algoState = BATSUP_PENDING;
                                BatSup_voltPeddingState = BATSUP_NO_STATE;
                                BatSup_voltDebounceState = BATSUP_NO_STATE;
                                BatSup_flushQueue();
                            }
                        }
                    }
                }
            }
        }
    }
}

void BatSup_initTask(void)
{
    U16 voltageValue;

    BatSup_algoState = BATSUP_PENDING;
    BatSup_voltState = BATSUP_NO_STATE;
    BatSup_voltPeddingState = BATSUP_NO_STATE;
    BatSup_voltDebounceState = BATSUP_NO_STATE;
    BatSup_errorState = BATSUP_NO_ERROR;
    BatSup_debounceCounter = 0u;
    BatSup_queueHead = 0u;
    BatSup_queueCurrSize = 0u;
    BatSup_queueUnderCnt = 0u;
    BatSup_queueNormalCnt = 0u;
    BatSup_queueOverCnt = 0u;
    BatSup_pendingAfterInit = 1u;

    voltageValue = MeasureSupply_getUbattVoltage();
    if (BatSup_isADC_Valid(voltageValue) != 0U )
    {  
        BatSup_voltageValue = voltageValue;
        BatSup_firstState = BatSup_getFirstState(voltageValue);
        BatSup_refVoltageValue = BatSup_getRefValue(BatSup_firstState);
    }
}

U8 BatSup_isVoltageInNormal(void)
{
    U8 retVal = 0u;
    if(BatSup_voltState == BATSUP_NOMAL)
    {
        retVal = 1u;
    }
    return retVal;
}

U8 BatSup_isComOff(void)
{
    U8 retVal = 0u;
    if((BatSup_voltState == BATSUP_COM_OFF_1) || (BatSup_voltState == BATSUP_COM_OFF_2))
    {
        retVal = 1u;
    }
    return retVal;
}

/*********************************************************************************************************
 *  Name                   : BatSup_getVoltageState
 *  Description            : Function used only to return current state of voltage monitoring.
 *  Parameters             : none
 *  Return                 : Current state of voltage monitoring
 *  Critical/explanation   : -
 *********************************************************************************************************/
BatSup_voltageStateType BatSup_getVoltageState(void)
{
	return BatSup_voltState;
}

BatSup_errorStateType BatSup_getErrorState(void)
{
    return BatSup_errorState;
}

U16 BatSup_getVoltageValue(void)
{
    return BatSup_voltageValue;
}


/******************************** Local functions definitions ****************************************/
/* polyspace+200 MISRA-C3:10.1 [Justified:Low] "left operand will npt be affected" */
/* polyspace+200 MISRA-C3:10.3 [Justified:Low] "the left operand will not be affected" */
/* polyspace+200 MISRA-C3:10.4 [Not a defect:Low] "the left operand will not be affected" */
/* polyspace+7 MISRA-C3:17.8 [Justified:Low] "A function parameter is changed" */
static U16 BatSup_getRefValue(BatSup_voltageStateType stateType)
{
    if (stateType > BATSUP_NO_STATE)
    {
        stateType -= 1u;
    }
    return BatSup_midRefVoltValue[stateType];
}

static BatSup_voltageStateType BatSup_getFirstState(U16 value)
{
    BatSup_voltageStateType retVoltState;
    if (value <= BatSup_thresholdComOff1)
    {
        retVoltState = BATSUP_COM_OFF_1;
    }
    else if (value <= BatSup_thresholdUndervoltage)
    {
        retVoltState = BATSUP_UNDERVOLTAGE;
    }
    else if (value < BatSup_thresholdOvervoltage )
    {
        retVoltState = BATSUP_NOMAL;
    }
    else if (value < BatSup_thresholdComOff2)
    {
        retVoltState = BATSUP_OVERVOLTAGE;
    }
    else
    {
        retVoltState = BATSUP_COM_OFF_2;
    }
    return retVoltState;
}

static U8 BatSup_isADC_Valid(U16 value)
{
    U8 retVal = 0u;
    if((value > 0u) && (value < BATSUP_MAX_UNSIGNED_10DIGIT))
    {
        retVal = 1u;
    }
    else
    {
        BatSup_errorState = BATSUP_ADC_SAMPLE_ERROR;
    }
    return retVal;
}

static BatSup_voltageStateType BatSup_getVoltState(U16 value)
{
    /* polyspace+2 MISRA-C3:D4.5 [Justified:Low] "Local variable name is different than enum" */
    U8 boolStateFound = 0u;
    BatSup_errorStateType error_State = BATSUP_NO_ERROR;

    /* Need separate lines because of enum, compiler warning otherwise */
    BatSup_voltageStateType newState = BatSup_voltState;
    if(newState == BATSUP_NO_STATE)
    {
        newState = BatSup_firstState;
    }
    /* Decrese states to map it as array indexis */
    newState -= 1u;

    if ( value >=  BatSup_refVoltageValue)
    {
        while((newState < BATSUP_VOLT_STATE_COUNT) && (boolStateFound == 0u))
        {
            /* most of the time 2 consecutive voltages will bellong to same voltage state */
            if( (value >= BatSup_voltageRangeHystHigh[newState].thresholdLow) && 
                (value <= BatSup_voltageRangeHystHigh[newState].thresholdHigh))
            {
                boolStateFound = 1u;
            }
            else
            {
                newState += 1u;
            }
            if(newState == BATSUP_VOLT_STATE_COUNT)
            {
                error_State = BATSUP_VOLTAGE_STATE_ERROR;
            }
        }
    }
    else
    {
        while(boolStateFound == 0u)
        {
            /* most of the time 2 consecutive voltages will bellong to same voltage state */
            if( (value >= BatSup_voltageRangeHystLow[newState].thresholdLow) && 
                (value <= BatSup_voltageRangeHystLow[newState].thresholdHigh))
            {
                boolStateFound = 1u;
            }
            else
            {   
                if((U8)newState > 0U)
                {
                    newState -= 1u;
                }
                else
                {
                    boolStateFound = 1u;
                    error_State = BATSUP_VOLTAGE_STATE_ERROR;
                }
            }
        }
    }
    if(error_State == BATSUP_NO_ERROR)
    {
        /* Increase back the states to reflect the actual state */
        newState += 1u;
    }
    else
    {
        newState = BATSUP_NO_STATE;
        BatSup_errorState = error_State;
    }
    return newState;
}

static void BatSup_addToQueue(BatSup_voltageStateType voltState)
{
    if(BatSup_queueCurrSize < BATSUP_QUEUE_SIZE)
    {
        BatSup_queue[(BatSup_queueHead + BatSup_queueCurrSize)%BATSUP_QUEUE_SIZE] = voltState;
        BatSup_incCounter(voltState);
        BatSup_queueCurrSize += 1u;
    }
    else
    {
        BatSup_removeFromQueue();
        BatSup_queue[(BatSup_queueHead + BatSup_queueCurrSize)%BATSUP_QUEUE_SIZE] = voltState;
        BatSup_incCounter(voltState);
        BatSup_queueCurrSize += 1u;
    }
}

static void BatSup_flushQueue(void)
{
    BatSup_queueHead = 0u;
    BatSup_queueCurrSize = 0u;
    BatSup_queueUnderCnt = 0u;
    BatSup_queueNormalCnt = 0u;
    BatSup_queueOverCnt = 0u;
}

static void BatSup_removeFromQueue(void)
{
    switch(BatSup_queue[BatSup_queueHead])
    {
    case BATSUP_UNDERVOLTAGE:
        BatSup_queueUnderCnt -= 1u;
        break;
    case BATSUP_NOMAL:
        BatSup_queueNormalCnt -= 1u;
        break;
    case BATSUP_OVERVOLTAGE:
        BatSup_queueOverCnt -= 1u;
        break;
    default:
        /* No counter to be decremented */
        break;
    }
    BatSup_queueHead = (BatSup_queueHead + 1) % BATSUP_QUEUE_SIZE;
    BatSup_queueCurrSize -= 1u;
}

static void BatSup_incCounter(BatSup_voltageStateType voltState)
{
    if((voltState != BATSUP_COM_OFF_1) && (voltState != BATSUP_COM_OFF_2))
    {
        switch(voltState)
        {
        case BATSUP_UNDERVOLTAGE:
            BatSup_queueUnderCnt += 1;
            if(BatSup_queueUnderCnt >= BATSUP_MAX_VOLTAGE_CNT)
            {
                BatSup_handleQueueData(BATSUP_UNDERVOLTAGE);
            }
            break;
        case BATSUP_NOMAL:
            BatSup_queueNormalCnt += 1;
            if(BatSup_queueNormalCnt >= BATSUP_MAX_VOLTAGE_CNT)
            {
                BatSup_handleQueueData(BATSUP_NOMAL);
            }
            break;
        case BATSUP_OVERVOLTAGE:
            BatSup_queueOverCnt += 1;
            if(BatSup_queueOverCnt >= BATSUP_MAX_VOLTAGE_CNT)
            {
                BatSup_handleQueueData(BATSUP_OVERVOLTAGE);
            }
            break;
        default:
            BatSup_errorState = BATSUP_UNKNOW_STATE_ERROR;
            break;
        }
    }
    else
    {
        /* Queue size is incremented after inc counters -> real size is size + 1 */
        if(BatSup_queueCurrSize >= (BATSUP_MAX_COM_ERROR_SIZE - 1u))
        {
            /* check with previous 2 positions */
            if( (voltState == BatSup_queue[(BatSup_queueHead + BatSup_queueCurrSize - 1u) % BATSUP_QUEUE_SIZE]) ||
                (voltState == BatSup_queue[(BatSup_queueHead + BatSup_queueCurrSize - 2u) % BATSUP_QUEUE_SIZE]))
            {
                /* 2 out of 3 */
                BatSup_goToIdle(voltState);
            }
        }
        else
        {
            if(voltState == BatSup_queue[(BatSup_queueHead + BatSup_queueCurrSize - 1u) % BATSUP_QUEUE_SIZE])
            {
                /* queue has only 2 elemens, 2 out of 2 */
                BatSup_goToIdle(voltState);
            }
            
        }
    }
}    

static void BatSup_handleQueueData(BatSup_voltageStateType voltState)
{
    if(BatSup_algoState == BATSUP_PENDING)
    {
        if(BatSup_pendingAfterInit != 0U)
        {
            BatSup_goToIdle(voltState);
        }
        else
        {  
            BatSup_voltPeddingState = voltState;
            BatSup_algoState = BATSUP_DEBOUNCE;
            BatSup_debounceCounter = 0u;
            BatSup_flushQueue();
            BatSup_voltageDebounceTime = ST_battery_supervisor_NVM_params.U16_VOLTMON_DEBOUNCE_TIME_NORMAL_PARAM;
        }
    }
    else
    {
        /* BatSup_algoState is BATSUP_DEBOUNCE */
        if(BatSup_algoState == BATSUP_DEBOUNCE)
        {
            if(BatSup_voltPeddingState == voltState)
            {
                /* same state, wait for debounce to be over */
                BatSup_voltDebounceState = voltState;
            }
            else
            {
                /* Pedding and Debounde state are different, start over */
                BatSup_algoState = BATSUP_PENDING;
                BatSup_voltPeddingState = BATSUP_NO_STATE;
                BatSup_voltDebounceState = BATSUP_NO_STATE;
                BatSup_debounceCounter = 0u;
                BatSup_flushQueue();
            }
        }
        else
        {
            BatSup_errorState = BATSUP_ALGO_STATE_ERROR;
        }
    }
}

static void BatSup_goToIdle(BatSup_voltageStateType voltState)
{
    BatSup_algoState = BATSUP_IDLE;
    BatSup_voltPeddingState = BATSUP_NO_STATE;
    BatSup_voltDebounceState = BATSUP_NO_STATE;
    BatSup_flushQueue();
    CANAPP_clearUndervoltageError();
    CANAPP_clearOvervoltageError();
    BatSup_handleNewState(voltState);
    BatSup_voltState = voltState;
    BatSup_refVoltageValue = BatSup_getRefValue(voltState);
    BatSup_pendingAfterInit = 0u;
}

static void BatSup_handleNewState(BatSup_voltageStateType voltState)
{
    switch(voltState)
    {
    case BATSUP_UNDERVOLTAGE:
        if (BatSup_isComOff() != 0U)
        {
            BatSup_stateRecoverFromComOff();
        }
        CANAPP_setUndervoltageError();
        break;
    case BATSUP_COM_OFF_1:
    case BATSUP_COM_OFF_2:
        BatSup_stateComOff();
        break;
    case BATSUP_NOMAL:
        if (BatSup_isComOff() != 0U)
        {
            BatSup_stateRecoverFromComOff();
        }
        break;
    case BATSUP_OVERVOLTAGE:
        if (BatSup_isComOff() != 0U)
        {
            BatSup_stateRecoverFromComOff();
        }
        CANAPP_setOvervoltageError();
        break;
    default:
     /*do nothing*/
        break;
    }
}

/*********************************************************************************************************
 *  Name                   : VoltageMonitor_StateActionComOff1
 *  Description            : Perform actions required when COM_OFF_1 Voltage Monitor State is reached
 *                         : 
 *  Parameters             : none
 *  Return                 : none
 *  Critical/explanation   : -
 *********************************************************************************************************/
static void BatSup_stateComOff(void)
{
    /* Stop Tx IpduGroups */
    Com_IpduGroupStop(ComConf_ComIPduGroup_CommunicationControlTx);
}

/*********************************************************************************************************
 *  Name                   : VoltageMonitor_StateActionUndervoltage
 *  Description            : Perform actions required when UNDERVOLTAGE Voltage Monitor State is reached
 *                         : SWR-700
 *  Parameters             : none
 *  Return                 : none
 *  Critical/explanation   : -
 *********************************************************************************************************/
static void BatSup_stateRecoverFromComOff(void)
{
    /* Start Tx IpduGroups */
    Com_IpduGroupStart(ComConf_ComIPduGroup_CommunicationControlTx, TRUE);
}
