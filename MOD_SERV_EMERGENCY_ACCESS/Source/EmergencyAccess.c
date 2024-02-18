/*------------------------------------------------------------------------------------------------+
| File: EmergencyAccess.c                                                                         |
+-------------------------------------------------------------------------------------------------+
| Project: Audi eTab                                                                              |
+-------------------------------------------------------------------------------------------------+
| Short description: The file contains the implementation of the Emergency Access module          |
|                                                                                                 |
|                                                                                                 |
|                                                                                                 |
|                                                                                                 |
|                                                                                                 |
+------------------------------------------------------------------------------------------------*/

/* ********** Header files include ********** */
#include "EmergencyAccess.h"
#include "BatterySupervisor.h"
#include "Dio.h"
#include "MeasureSupply.h"
#include "NvmMng.h"
#include "NvM.h"
#include "Com.h"

/* ********** Macro and Type Definitions ********** */
/* polyspace+1 MISRA-C3:2.4 [Justified:Low] "Added for further implementation." */
typedef enum testState {
    EmergencyAccess_COOLDOWN = 0u,
    EmergencyAccess_RUN,
    EmergencyAccess_DONE
} EmergencyAccess_testStateType;

/* ADC value for 11V */
#define EMERGENCY_ACCESS_VOLTAGE_THRESHOLD      (395u)
#define EMERGENCY_ACCESS_ACT_HIGH_TIME_LIMIT    (40u)
#define EMERGENCY_ACCESS_TEST_ITERATIONS        (1u)

/* ********** Local Functions Declarations ********** */

static void EmergencyAccess_handleChannel(void);
static void EmergencyAccess_setHighPeriod(void);
static void EmergencyAccess_parameterUpdate(void);
static void EmergencyAccess_Sfd_Test_Mode(void);
static void EmergencyAccess_checkSignal(U8 sigVal);


/* ********** Local Variable Definitions ********** */
static EmergencyAccess_testStateType EmergencyAccess_sfdTestState = EmergencyAccess_RUN;
static EmergencyAccess_stateType EmergencyAccess_state = EmergencyAccess_IDLE;
static U8 EmergencyAccess_sfdTestMode = 0u;
static U8 EmergencyAccess_lowVoltageHighPeriod = 0u;
static U8 EmergencyAccess_highVoltageHighPeriod = 0u;
static U16 EmergencyAccess_actuatorLowPeriod = 0u;
static U8 EmergencyAccess_actuatorRetries = 0u;
static U16 EmergencyAccess_timeCounter = 0u;
static U8 EmergencyAccess_prevSignalValue = 0u;
static U8 EmergencyAccess_signalValue = 0u;


/* ********** Global Function Definition ********** */

/*********************************************************************************************************
 *  Name                   : EmergencyAccess_Task
 *  Description            : Handle the task of Emergency Access
 *                         : 
 *  Parameters             : none
 *  Return                 : none
 *  Critical/explanation   : -
 *  Author                 : hcostin
 *********************************************************************************************************/
void EmergencyAccess_Task(void)
{
    /* Check if Voltage Monitor give the Emergency Access the permission to run */
    if(BatSup_isVoltageInNormal() != 0u)
    {
        /* Check if Sfd_Test_Mode is activated for Emergency Access */
        if (EmergencyAccess_sfdTestMode == 1u)
        {
            EmergencyAccess_Sfd_Test_Mode();
            /* Stop functionality */
            EmergencyAccess_state = EmergencyAccess_IDLE;
        }
        else
        {
            if(EmergencyAccess_state == EmergencyAccess_IDLE)
            {
                EmergencyAccess_checkSignal(EmergencyAccess_signalValue);
            }
            else
            {
                EmergencyAccess_handleChannel();
            }
        }
    }
    else
    {
        /* Stop functionality */
        EmergencyAccess_state = EmergencyAccess_IDLE;
        /* Stop SFD test */
        EmergencyAccess_sfdTestState = EmergencyAccess_DONE;
        /* Set the pin to low as a default */
        Dio_WriteChannel(DioConf_DioChannel_Dio_PTA0_Actor_EN, 0u);
    }
    EmergencyAccess_prevSignalValue = EmergencyAccess_signalValue;
}

void EmergencyAccess_signalReceived(void)
{
    (void)Com_ReceiveSignal(ComConf_ComSignal_B_ActuatorControl, &EmergencyAccess_signalValue);
}

/*********************************************************************************************************
 *  Name                   : EmergencyAccess_goToSleep
 *  Description            : Clears all states, when ECU goes to Normal state
 *  Parameters             : none
 *  Return                 : none
 *********************************************************************************************************/
void EmergencyAccess_goToSleep(void)
{
    /* Stop functionality */
    EmergencyAccess_state = EmergencyAccess_IDLE;
    /* Stop SFD test */
    EmergencyAccess_sfdTestState = EmergencyAccess_DONE;
    /* Set the pin to low as a default */
    Dio_WriteChannel(DioConf_DioChannel_Dio_PTA0_Actor_EN, 0u);
    EmergencyAccess_signalValue = 0u;
    /* Clear the previous value, ecu goes to sleep */
    EmergencyAccess_prevSignalValue = 0u;
}

/*********************************************************************************************************
 *  Name                   : EmergencyAccess_RequestSfdTestMode
 *  Description            : Request SFD Test Mode
 *  Parameters             : none
 *  Return                 : none
 *********************************************************************************************************/
void EmergencyAccess_RequestSfdTestMode(void)
{
    EmergencyAccess_sfdTestMode = 1u;
}

/*********************************************************************************************************
 *  Name                   : EmergencyAccess_checkParameters
 *  Description            : Check the parameters from NVM
 *                         : SSA-209, SSA-255
 *  Parameters             : none
 *  Return                 : none
 *  Critical/explanation   : -
 *   Author                : bbarlea
 *********************************************************************************************************/
void EmergencyAccess_checkParameters(void)
{
    /* polyspace+30 MISRA-C3:15.7 [Not a defect:Low] else block is not needed here */
    /* Check U16_ACTUATOR_SUPPLY_HIGH_VOLT_PARAM param validity */
    if (ST_emergency_access_NVM_params.U16_ACTUATOR_SUPPLY_HIGH_VOLT_PARAM < 1u)
    {
        ST_emergency_access_NVM_params.U16_ACTUATOR_SUPPLY_HIGH_VOLT_PARAM  = 1u;
    }
    else if (ST_emergency_access_NVM_params.U16_ACTUATOR_SUPPLY_HIGH_VOLT_PARAM > EMERGENCY_ACCESS_ACT_HIGH_TIME_LIMIT)
    {
        ST_emergency_access_NVM_params.U16_ACTUATOR_SUPPLY_HIGH_VOLT_PARAM  = EMERGENCY_ACCESS_ACT_HIGH_TIME_LIMIT ;
    }
    /* Check U16_ACTUATOR_SUPPLY_LOW_VOLT_PARAM param validity */
    if (ST_emergency_access_NVM_params.U16_ACTUATOR_SUPPLY_LOW_VOLT_PARAM < 1u)
    {
        ST_emergency_access_NVM_params.U16_ACTUATOR_SUPPLY_LOW_VOLT_PARAM = 1u;
    }
    else if (ST_emergency_access_NVM_params.U16_ACTUATOR_SUPPLY_LOW_VOLT_PARAM > EMERGENCY_ACCESS_ACT_HIGH_TIME_LIMIT)
    {
        ST_emergency_access_NVM_params.U16_ACTUATOR_SUPPLY_LOW_VOLT_PARAM = EMERGENCY_ACCESS_ACT_HIGH_TIME_LIMIT;
    }
    /* Check U16_ACTUATOR_RETRIES_PARAM param validity */
    if (ST_emergency_access_NVM_params.U16_ACTUATOR_RETRIES_PARAM < 1u)
    {
        ST_emergency_access_NVM_params.U16_ACTUATOR_RETRIES_PARAM = 1u;
    }
    /* Check U16_TIME_ACTUATOR_COOLDOWN_PARAM param validity */
    if (ST_emergency_access_NVM_params.U16_TIME_ACTUATOR_COOLDOWN_PARAM < 1u)
    {
        ST_emergency_access_NVM_params.U16_TIME_ACTUATOR_COOLDOWN_PARAM = 1u;
    }
}


EmergencyAccess_stateType EmergencyAccess_getState(void)
{
    return EmergencyAccess_state;
}

/* ********** Local Function Definition ********** */

/*********************************************************************************************************
 *  Name                   : EmergencyAccess_parameterUpdate
 *  Description            : Update the algo parameters with values from NVM
 *                         : SSA-209, SSA-255
 *  Parameters             :
 *  Return                 : none
 *  Critical/explanation   : -
 *   Author                : bbarlea
 *********************************************************************************************************/
static void EmergencyAccess_parameterUpdate(void)
{
    EmergencyAccess_highVoltageHighPeriod = (U8)ST_emergency_access_NVM_params.U16_ACTUATOR_SUPPLY_HIGH_VOLT_PARAM;
    EmergencyAccess_lowVoltageHighPeriod = (U8)ST_emergency_access_NVM_params.U16_ACTUATOR_SUPPLY_LOW_VOLT_PARAM;
    EmergencyAccess_actuatorRetries = (U8)ST_emergency_access_NVM_params.U16_ACTUATOR_RETRIES_PARAM;
    EmergencyAccess_actuatorLowPeriod = ST_emergency_access_NVM_params.U16_TIME_ACTUATOR_COOLDOWN_PARAM;
}

/*********************************************************************************************************
 *  Name                   : EmergencyAccess_handleChannel
 *  Description            : Stop DIO channel (OUTPUT LOW) after debounce time
 *                         : 
 *  Parameters             : none
 *  Return                 : none
 *  Critical/explanation   : -
 *  Author                 : hcostin
 *********************************************************************************************************/
static void EmergencyAccess_handleChannel(void)
{
	switch(EmergencyAccess_state)
    {
        case EmergencyAccess_HIGH:
            EmergencyAccess_timeCounter -= 1u;
            if(EmergencyAccess_timeCounter == 0u)
            {
                EmergencyAccess_state = EmergencyAccess_LOW;
                /* set pin to high */
                Dio_WriteChannel(DioConf_DioChannel_Dio_PTA0_Actor_EN, 0u);
                /* Load low period counter */
                EmergencyAccess_timeCounter = EmergencyAccess_actuatorLowPeriod;
            }
            else
            {
                /* just wait */
            }
            break;
        case EmergencyAccess_LOW:
            EmergencyAccess_timeCounter -= 1u;
            if(EmergencyAccess_timeCounter == 0u)
            {
                /* One period ended */
                EmergencyAccess_actuatorRetries -= 1u;
                if(EmergencyAccess_actuatorRetries == 0)
                {
                    /* go to Idle */
                    EmergencyAccess_state = EmergencyAccess_IDLE;
                    /* Pin is already low */
                }
                else
                {
                    /* Start a new period */
                    EmergencyAccess_state = EmergencyAccess_HIGH;
                    EmergencyAccess_setHighPeriod();
                    /* set DIO channel on HIGH */
                    Dio_WriteChannel(DioConf_DioChannel_Dio_PTA0_Actor_EN, 1u);
                }
            }
            else
            {
                /* just wait */
            }
            break;
        default:
            /* state is idle or invalid */
            break;
    }
}

/*********************************************************************************************************
 *  Name                   : EmergencyAccess_setHighPeriod
 *  Description            : Start DIO channel (OUTPUT HIGH) and set a specific debounce time
 *                         : 
 *  Parameters             : none
 *  Return                 : none
 *  Critical/explanation   : -
 *  Author                 : hcostin
 *********************************************************************************************************/
static void EmergencyAccess_setHighPeriod(void)
{
	U16 U16_ubatVoltage = 0u;

	U16_ubatVoltage = MeasureSupply_getUbattVoltage();
	if(EMERGENCY_ACCESS_VOLTAGE_THRESHOLD > U16_ubatVoltage)
	{
		/* power supply < actuator 11V(+/- 0.7V) */
		EmergencyAccess_timeCounter = (U16)(EmergencyAccess_lowVoltageHighPeriod);
    }
	else
	{
		/* power supply >= actuator 11V(+/- 0.7V) */
		EmergencyAccess_timeCounter = (U16)(EmergencyAccess_highVoltageHighPeriod);
	}
}

/*********************************************************************************************************
 *  Name                   : EmergencyAccess_checkSignal
 *  Description            : Check CAN Signal and handle the pin if needed
 *                         : 
 *  Parameters             : U8 sigVal, CAN signal value
 *  Return                 : none
 *  Critical/explanation   : -
 *  Author                 : hcostin
 *********************************************************************************************************/
static void EmergencyAccess_checkSignal(U8 sigVal)
{
    if((1u == sigVal) && (EmergencyAccess_prevSignalValue == 0u))
    {
        EmergencyAccess_state = EmergencyAccess_HIGH;
        /* Read values from NVM */
        EmergencyAccess_checkParameters();
        EmergencyAccess_parameterUpdate();
        EmergencyAccess_setHighPeriod();
        /* set DIO channel on HIGH */
        Dio_WriteChannel(DioConf_DioChannel_Dio_PTA0_Actor_EN, 1u);
    }
    else
    {
        /* There is no raising edge , no change in behaviour */
    }
}

/*********************************************************************************************************
 *  Name                   : EmergencyAccess_Sfd_Test_Mode
 *  Description            : Supply power to the actuator for PAR_DIGIT_ACTUATOR_SUPPLY_HIGH_VOLT
 *                         : SWR_2711
 *                         : 
 *  Parameters             : none
 *  Return                 : none
 *  Critical/explanation   : -
 *  Author                 : tghenci
 *********************************************************************************************************/
/* polyspace+1 MISRA-C3:D4.5 [Justified:Low] "No overlapping visibility" */
static void EmergencyAccess_Sfd_Test_Mode(void)
{
    static U8 NoOfIteations = 0u;
    static U8 debounce = 0u;

    /* Update parameters */
    EmergencyAccess_parameterUpdate();

    switch(EmergencyAccess_sfdTestState) {
        case EmergencyAccess_COOLDOWN:
            Dio_WriteChannel(DioConf_DioChannel_Dio_PTA0_Actor_EN, 0u);
            debounce++;
            /* Check if debounce time has passed, if so we'll go to RUN state */
            if (debounce >= EmergencyAccess_actuatorLowPeriod)
            {
                debounce = 0u;
                EmergencyAccess_sfdTestState = EmergencyAccess_RUN;
            }
            break;
        case EmergencyAccess_RUN:
            Dio_WriteChannel(DioConf_DioChannel_Dio_PTA0_Actor_EN, 1u);
            debounce++;
            /* Check if debounce time has passed */
            if (debounce >= EmergencyAccess_highVoltageHighPeriod)
            {
                NoOfIteations++;
                debounce = 0u;

                /* If NoOfIteations is equal or grater than NoOfTestsForEmergencyAcces we'll go to the last state, otherwise we'll go in COOLDOWN state */
                if (EMERGENCY_ACCESS_TEST_ITERATIONS <= NoOfIteations)
                {
                    EmergencyAccess_sfdTestState = EmergencyAccess_DONE;
                }
                else 
                {
                    EmergencyAccess_sfdTestState = EmergencyAccess_COOLDOWN;
                }
            }
            break;

        /* This is the final case where Sfd_Test_Mode will be set to false and the local counters will be reset */
        case EmergencyAccess_DONE:
            EmergencyAccess_sfdTestMode = 0u;
            EmergencyAccess_sfdTestState = EmergencyAccess_RUN;
            NoOfIteations = 0u;
            debounce = 0u;
            Dio_WriteChannel(DioConf_DioChannel_Dio_PTA0_Actor_EN, 0u);
            break;

        default:
            /*do nothing*/
            break;
    }
}
