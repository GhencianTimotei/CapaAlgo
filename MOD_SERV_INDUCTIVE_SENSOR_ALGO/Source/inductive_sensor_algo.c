/* polyspace <MISRA-C3:1.1 :  Not a defect : Justify with annotations >All macro definitions are needed. */
/*------------------------------------------------------------------------------------------------+
| File: inductive_sensor_algo.c                                                                   |
+-------------------------------------------------------------------------------------------------+
| Project: Audi eTab                                                                              |
+-------------------------------------------------------------------------------------------------+
| Short description: The file contains the implementation of the inductive algo                   |
|                                                                                                 |
|                                                                                                 |
|                                                                                                 |
|                                                                                                 |
|                                                                                                 |
+------------------------------------------------------------------------------------------------*/
/* polyspace < MISRA-C3:2.5 : Not a defect : Justify with annotations > should be kept for future usage */
#define INDUCTIVE_SENSOR_ALGO_C_
/* Used interfaces from other modules */
#include "EcuM.h"
#include "Com.h"
/* Provide interface */
/* ----------------- */
#include "inductive_sensor_algo.h"
#include "NvmMng.h"

/* Private functions, macros, types and data */
/* polyspace < MISRA-C3:8.7 : Not a defect : Justify with annotations > External Usage dependent on project setup*/
ST_inductive_sensor_NVM_parameters_T ST_inductive_sensor_NVM_params;
/* ---------------------------------------------------- */
static void algo_check_parameters(void);
static void Debounce_State_Inductive_Sensor(TASK_INDUCTIVE_SENSOR_PARAMETER * indChannel);
static void Idle_State_Inductive_Sensor(TASK_INDUCTIVE_SENSOR_PARAMETER * indChannel);
static U8 Inductive_Algo_All_Channels_Touched(void);
static void MeasuredVal_ToLow_Inductive(TASK_INDUCTIVE_SENSOR_PARAMETER * indChannel);
static void parameters_update(TASK_INDUCTIVE_SENSOR_PARAMETER * indChannel);
static void SM_Inductive_Sensor(TASK_INDUCTIVE_SENSOR_PARAMETER * indChannel);
static void Update_The_Minimum_Value(TASK_INDUCTIVE_SENSOR_PARAMETER * indChannel);
static void ThresholdReference_Debounce_Inductive(TASK_INDUCTIVE_SENSOR_PARAMETER * indChannel);
static void ThresholdReference_Init(TASK_INDUCTIVE_SENSOR_PARAMETER * indChannel);
static void Touch_State_Inductive_Sensor(TASK_INDUCTIVE_SENSOR_PARAMETER * indChannel);
static void OffDelay_State_Inductive_Sensor(TASK_INDUCTIVE_SENSOR_PARAMETER * indChannel);
static void Update_Threshold_Value(TASK_INDUCTIVE_SENSOR_PARAMETER * indChannel);
static void Update_Threshold_By_Noise(TASK_INDUCTIVE_SENSOR_PARAMETER * indChannel);
static void Inductive_Algo_Set_Can_Signal(void);
static U8 Inductive_Algo_One_Channel_Touched(void);
static void Inductive_Algo_Freeze_Handle(TASK_INDUCTIVE_SENSOR_PARAMETER * indChannel);

/* Public functions, macros, types and data */

/* polyspace+4 MISRA-C3:8.7 [Justified:Low] "External declaration is needed" */
U16 U16_Normal_Low_Ticks;
static U32 U32_Ldc_Ch0;
static U32 U32_Ldc_Ch1;
U16 U16_Normal_High_Ticks;
static U8 Algo_KY_Oeffnen_BetaetigungSignal = 0u;
U8 U8_Inductive_Algo_Valid_Touch = 0u;
/* Iinitial values and references for every channel */
TASK_INDUCTIVE_SENSOR_PARAMETER inductive_sensor_param[INDUCTIVE_SENSOR_MAX] = {
    {
        U32_DEFAULT_THRESHOLD_REFERENCE,
        U32_DEFAULT_THRESHOLD_VALUE,
        &U32_Ldc_Ch0,
        U16_INDUCTIVE_THRESHOLD_NVM_DEF,
        U16_INDUCTIVE_THRESHOLD_NVM_DEF,
        U32_DEFAULT_THRESHOLD_REFERENCE,
        U16_INDUCTIVE_CH0_THRESHOLD,
        U16_LDC_OPEN_TIMEOUT,
        U16_LDC_FREEZE_CANCEL_NVM_DEF,
        U8_LDC_DEBOUNCE_ACTIVE,
        U16_INDUCTIVE_OFFDELAY,
        U8_LDC_REF_DEBOUNCE,
        0u,
        0u,
        INDUCTIVE_SENSOR_CH0,
        EN_INDUCTIVE_STATE_IDLE
    },
    {
        U32_DEFAULT_THRESHOLD_REFERENCE,
        U32_DEFAULT_THRESHOLD_VALUE,
        &U32_Ldc_Ch1,
        U16_INDUCTIVE_THRESHOLD_NVM_DEF,
        U16_INDUCTIVE_THRESHOLD_NVM_DEF,
        U32_DEFAULT_THRESHOLD_REFERENCE,
        U16_INDUCTIVE_CH1_THRESHOLD,
        U16_LDC_OPEN_TIMEOUT,
        U16_LDC_FREEZE_CANCEL_NVM_DEF,
        U8_LDC_DEBOUNCE_ACTIVE,
        U16_INDUCTIVE_OFFDELAY,
        U8_LDC_REF_DEBOUNCE,
        0u,
        0u,
        INDUCTIVE_SENSOR_CH1,
        EN_INDUCTIVE_STATE_IDLE
    }
};
/*********************************************************************************************************
 *  Name                   : storeParametersFromNVM
 *  Description            : Store low and high ticks parameters from NVM.
 *                         :
 *  Parameters             : none
 *  Return                 : none
 *  Critical/explanation   : -
 *   Author                : grovent
 *********************************************************************************************************/
/* polyspace < MISRA-C3:8.7 : Not a defect : Justify with annotations > External Usage dependent on project setup*/
void storeParametersFromNVM(void)
{
    if(ST_inductive_sensor_NVM_params.U16_LDC_INT_LOW_TICKS < ST_inductive_sensor_NVM_params.U16_LDC_INT_HIGH_TICKS)
    /* polyspace < RTE:UNR : Not a defect : Justify with annotations> The condition is not redundant*/
    {
        U16_Normal_Low_Ticks = ST_inductive_sensor_NVM_params.U16_LDC_INT_LOW_TICKS;
        U16_Normal_High_Ticks = ST_inductive_sensor_NVM_params.U16_LDC_INT_HIGH_TICKS;
    }
    else
    {
        U16_Normal_Low_Ticks = ST_inductive_sensor_NVM_params.U16_LDC_INT_HIGH_TICKS;
        U16_Normal_High_Ticks = ST_inductive_sensor_NVM_params.U16_LDC_INT_LOW_TICKS;
    }
}

/*********************************************************************************************************
 *  Name                   : MeasuredVal_ToLow_Inductive
 *  Description            : Change the threshold reference value if measured value is lower.
 *                         : SWR-465
 *  Parameters             : indChannel - pointer for handled channel
 *  Return                 : none
 *  Critical/explanation   : -
 *   Author                : hcostin
 *********************************************************************************************************/
/* polyspace+3 MISRA-C3:10.8 [Justified:Low] "The value is converted to U32 to not overflow." */
static void MeasuredVal_ToLow_Inductive(TASK_INDUCTIVE_SENSOR_PARAMETER * indChannel)
{
	U32 thresholdX4 = (U32)(indChannel->LDC_THRESHOLD + indChannel->LDC_THRESHOLD + indChannel->LDC_THRESHOLD + indChannel->LDC_THRESHOLD);
	/* should works only when channel is touched */
	 /* polyspace < MISRA-C3:D4.1,18.1: Not a defect : Justify with annotations > Will not be overflow due to the condition inside*/ 
	 /* polyspace < RTE:OVFL: Not a defect : Justify with annotations > Will not be overflow due to the condition inside*/ 
	/* polyspace < RTE:OVFL,IDP: Not a defect : Justify with annotations > Will not be overflow due to the condition inside*/ 	
	/* polyspace < RTE:NIV: Not a defect: Justify with annotations > Variable is initialized in Inductive_Sensor_Algo_Init function */
	if((EN_INDUCTIVE_STATE_IDLE != indChannel->AlgoStateSM) && ((indChannel->ThresholdReference - thresholdX4) > (*(indChannel->MeasuredValue))) &&
        (indChannel->FreezeCounter == (U16)0))
	{
	    /* polyspace < RTE:OVFL : Not a defect : Justify with annotations >  No error: cast to U32 here to match with thresholdX4 type so will no overflow */
	    /* polyspace < MISRA-C3:D4.1 : Not a defect : Justify with annotations >  No error: cast to U32 here to match with thresholdX4 type so will no overflow */
	    indChannel->ThresholdReference = (U32)(*(indChannel->MeasuredValue) + thresholdX4);
	}
	else
	{
	    /* do nothing */
	}
}

/*********************************************************************************************************
 *  Name                   : Update_Threshold_Value
 *  Description            : Change the threshold value
 *                         : 
 *  Parameters             : indChannel - pointer for handled channel
 *  Return                 : none
 *  Critical/explanation   : -
 *   Author                : hcostin
 *********************************************************************************************************/
static void Update_Threshold_Value(TASK_INDUCTIVE_SENSOR_PARAMETER * indChannel)
{
    /* polyspace < RTE : OVFL : Not a defect : Justify with annotation > Will not be overflow */
    /* polyspace < MISRA-C3:D4.1 : Not a defect : Justify with annotation > Will not be overflow */
    /* Update Threshold Value subtracting the seted threshold from Threshold Reference*/
    if(indChannel->FreezeCounter == (U16)0)
    {
        if (indChannel->ThresholdReference >= indChannel->LDC_THRESHOLD)
        {
            indChannel->ThresholdValue = indChannel->ThresholdReference - indChannel->LDC_THRESHOLD;
            Update_Threshold_By_Noise(indChannel);
        } else 
        {
            indChannel->ThresholdValue = 0u;
        }
    }
    else
    {
        /* Threshold freezed. do nothing */
    }
}


static void Update_Threshold_By_Noise(TASK_INDUCTIVE_SENSOR_PARAMETER * indChannel)
{
    if ((BOOL)TRUE == LDC3114_Sensor_Var_Str[indChannel->sensorChannel].BO_noise_detected)
    {
        if (indChannel->ThresholdValue >= U16_LDC_NOISE_OFFSET)
        {
            indChannel->ThresholdValue -= U16_LDC_NOISE_OFFSET;
        } else 
        {
            indChannel->ThresholdValue = 0u;
        }
        
        indChannel->NoiseActiveCnt = U8_LDC_NOISE_ACTIVE;
    } else 
    {
        if (0u < indChannel->NoiseActiveCnt)
        {
            if (indChannel->ThresholdValue >= U16_LDC_NOISE_OFFSET)
            {
                indChannel->ThresholdValue -= U16_LDC_NOISE_OFFSET;
            }
            else
            {
                indChannel->ThresholdValue = 0u;
            }
            indChannel->NoiseActiveCnt--;
        }
    }
}
/*********************************************************************************************************
 *  Name                   : Update_The_Minimum_Value
 *  Description            : Check all last U8_LDC_REF_DEBOUNCE values and update the minimum value if needed.
 *                         : SWR-431, SWR-434, SWR-438
 *  Parameters             : indChannel - pointer to handled channel
 *  Return                 : none
 *  Critical/explanation   : -
 *   Author                : hcostin
 *********************************************************************************************************/
static void Update_The_Minimum_Value(TASK_INDUCTIVE_SENSOR_PARAMETER * indChannel)
{
    /* Store Measured Value */
    /* polyspace:begin <MISRA-C3:D4.1,18.1 : Not a defect : Justify with annotations > Will never overflow due to the condition below. indChannel->LdcRefDebounce will never be less than 0 */
    /* polyspace < RTE:OVFL : Justify with annotations > Will never overflow due to the condition below. indChannel->LdcRefDebounce will never be less than 0 */
    if (indChannel->LdcRefDebounce > 0u)
    {
        indChannel->LdcRefDebounce--;
    }
    else
    {
        /* Do nothing */
    }

    if(indChannel->MinValProcess > (*(indChannel->MeasuredValue)))
    {
        indChannel->MinValProcess = (*(indChannel->MeasuredValue));
    }
    else
    {
        /* do nothing */
    }
    
    /* triggern minimum calculation if all U8_LDC_REF_DEBOUNCE measured values were stored */
    if(indChannel->LdcRefDebounce == 0)
    {
        /* reset the reference debounce time */
        indChannel->LdcRefDebounce = (U8)ST_inductive_sensor_NVM_params.U16_LDC_VAL_FOR_REF;
        /* store the minimum measured value */
        indChannel->MinMeasureValue = indChannel->MinValProcess;
        /* reset the minimum value */
        indChannel->MinValProcess = U32_MAX;
    }
    else
    {
        /* do nothing */
    }
}

/*********************************************************************************************************
 *  Name                   : ThresholdReference_Debounce_Inductive
 *  Description            : Calculate new reference at every U8_LDC_REF_DEBOUNCE calls.
 *                         : SWR-431, SWR-434, SWR-438
 *  Parameters             : indChannel - pointer to handled channel
 *  Return                 : none
 *  Critical/explanation   : -
 *   Author                : hcostin
 *********************************************************************************************************/
static void ThresholdReference_Debounce_Inductive(TASK_INDUCTIVE_SENSOR_PARAMETER * indChannel)
{
    if (indChannel->FreezeCounter == 0u)
    {
        Update_The_Minimum_Value(indChannel);
    }

    /* update the Threshold Reference with the minimum value from last U8_LDC_REF_DEBOUNCE samples */
    indChannel->ThresholdReference = indChannel->MinMeasureValue;
}

/*********************************************************************************************************
 *  Name                   : Idle_State_Inductive_Sensor
 *  Description            : on Idle state and the transitions from this state.
 *                         : SWR-433
 *  Parameters             : indChannel - pointer to handled channel
 *  Return                 : none
 *  Critical/explanation   : -
 *   Author                : hcostin
 *********************************************************************************************************/
static void Idle_State_Inductive_Sensor(TASK_INDUCTIVE_SENSOR_PARAMETER * indChannel)
{
    /* recalculate the Threshold Reference only in IDLE state */
    ThresholdReference_Debounce_Inductive(indChannel);
    /* polyspace < RTE:NIV: Not a defect: Justify with annotations > Variable is initialized in Inductive_Sensor_Algo_Init function */
    /* polyspace < RTE:IDP: Not a defect: Justify with annotations > The pointer value will be generated in the inductive sensor algo files and it will not be outside of the bonds or NULL*/
    /* polyspace < MISRA-C3:D4.1,18.1 : Not a defect : Justify with annotations > Ponter is not outside of the bounds of the array and overflow will not occur during normal usage */
    if((*(indChannel->MeasuredValue)) <= indChannel->ThresholdValue)
    {
        /* A touch is detected and need to transit to debounce */
        indChannel->AlgoStateSM = EN_INDUCTIVE_STATE_DEBOUNCE;
        indChannel->LdcDebounce = (U8)ST_inductive_sensor_NVM_params.U16_LDC_DEBOUNCE_ACTIVE;

        if (0u < indChannel->NoiseActiveCnt)
        {
            indChannel->LdcDebounce += U8_LDC_NOISE_DEBOUNCE;
        }
    }
    else
    { 
        /* do nothing */
    }

}

/*********************************************************************************************************
 *  Name                   : Debounce_State_Inductive_Sensor
 *  Description            : on Debounce state and the transitions from this state.
 *                         : SWR-435
 *  Parameters             : indChannel - pointer to handled channel
 *  Return                 : none
 *  Critical/explanation   : -
 *   Author                : hcostin
 *********************************************************************************************************/
static void Debounce_State_Inductive_Sensor(TASK_INDUCTIVE_SENSOR_PARAMETER * indChannel)
{
    if (indChannel->LdcDebounce > 0u)
    {
        indChannel->LdcDebounce--;
    } else
    {
        /* Do nothing */
    }
    
	/* polyspace < RTE:NIV: Not a defect: Justify with annotations > Variable is initialized in Inductive_Sensor_Algo_Init function */
	 /* polyspace < RTE:IDP: Not a defect: Justify with annotations > The pointer value will be generated in the inductive sensor algo files and it will not be outside of the bonds or NULL*/
	/* polyspace < MISRA-C3:D4.1,18.1 : Not a defect : Justify with annotations > Pointer is not outside of the bounds of the array and overflow will not occur during normal usage */
	if((*(indChannel->MeasuredValue)) > indChannel->ThresholdValue)
	{
	    /* touch no more detected */
	    indChannel->AlgoStateSM = EN_INDUCTIVE_STATE_OFFDELAY;
	    /* reset counter for debounce state */
	    indChannel->LdcDebounce = U8_Debounce_Time_Reset;
	}
	else if(indChannel->LdcDebounce > 0)
	{
	   /* do nothing */
	}
	else
	{
	    /* countdown was finished and the touch still exists */
	    indChannel->AlgoStateSM = EN_INDUCTIVE_STATE_TOUCH;
	    /* reset counter for debounce state */
	    indChannel->LdcDebounce = U8_Debounce_Time_Reset;
        /* deactivate freeze threshold */
        indChannel->FreezeCounter = 0u;
	}
}


static void OffDelay_State_Inductive_Sensor(TASK_INDUCTIVE_SENSOR_PARAMETER * indChannel)
{
    indChannel->LdcOffDelayDebounce--;
    /* polyspace < RTE:NIV: Not a defect: Justify with annotations > Variable is initialized in Inductive_Sensor_Algo_Init function */
     /* polyspace < RTE:IDP: Not a defect: Justify with annotations > The pointer value will be generated in the inductive sensor algo files and it will not be outside of the bonds or NULL*/
    /* polyspace < MISRA-C3:D4.1,18.1 : Not a defect : Justify with annotations > Pointer is not outside of the bounds of the array and overflow will not occur during normal usage */
    if(indChannel->LdcOffDelayDebounce > 0u)
    {
        indChannel->LdcRefDebounce = indChannel->LdcOffDelayDebounce;
        /* recalculate the Threshold Reference only in IDLE state */
        ThresholdReference_Debounce_Inductive(indChannel);
    }
    else
    {
        /* countdown was finished and the touch still exists */
        /* reset counter for debounce state */
        indChannel->LdcOffDelayDebounce = U16_INDUCTIVE_OFFDELAY;
        /* touch no more detected */
        indChannel->AlgoStateSM = EN_INDUCTIVE_STATE_IDLE;
        /* reset the reference debounce time */
    }
}

/*********************************************************************************************************
 *  Name                   : Touch_State_Inductive_Sensor
 *  Description            : on Active state and the transitions from this state.
 *                         : SWR-439
 *  Parameters             : indChannel - pointer to handled channel
 *  Return                 : none
 *  Critical/explanation   : -
 *   Author                : hcostin
 *********************************************************************************************************/
static void Touch_State_Inductive_Sensor(TASK_INDUCTIVE_SENSOR_PARAMETER * indChannel)
{
	 /* polyspace < RTE:IDP: Not a defect: Justify with annotations > The pointer value will be generated in the inductive sensor algo files and it will not be outside of the bonds or NULL*/
	/* polyspace < RTE:NIV: Not a defect: Justify with annotations > Variable is initialized in Inductive_Sensor_Algo_Init function */
	/* polyspace < MISRA-C3:D4.1,18.1 : Not a defect : Justify with annotations > Pointer is not outside of the bounds of the array and overflow will not occur during normal usage */
	if((*(indChannel->MeasuredValue)) > indChannel->ThresholdValue)
	{
	    /* touch no more detected */
	    indChannel->AlgoStateSM = EN_INDUCTIVE_STATE_OFFDELAY;
	    /* reset counter for debounce state */
	    indChannel->LdcDebounceTimeOut = (U16)ST_inductive_sensor_NVM_params.U16_OPEN_TIMEOUT;
	}
	else if(indChannel->LdcDebounceTimeOut > 0)
	{
	    /* the touch still exists */
	    indChannel->LdcDebounceTimeOut--;
	}
	else
	{
	    /* the debounce time for touch was passed */
	    indChannel->AlgoStateSM = EN_INDUCTIVE_STATE_OFFDELAY;
	    /* reset counter for debounce state */
	    indChannel->LdcDebounceTimeOut = (U16)ST_inductive_sensor_NVM_params.U16_OPEN_TIMEOUT;
        indChannel->FreezeCounter = 0u;
	}
}

/*********************************************************************************************************
 *  Name                   : SM_Inductive_Sensor
 *  Description            : State Machine for Inductive Sensor
 *                         :
 *  Parameters             : indChannel - pointer to handled channel
 *  Return                 : none
 *  Critical/explanation   : -
 *   Author                : hcostin
 *********************************************************************************************************/
static void SM_Inductive_Sensor(TASK_INDUCTIVE_SENSOR_PARAMETER * indChannel)
{
    /* recalculate the Threshold Reference only in IDLE state (it is checked inside the functions below) */
    //ThresholdReference_Debounce_Inductive(indChannel);
    MeasuredVal_ToLow_Inductive(indChannel);

    /* update threshold value based on reference */
    Update_Threshold_Value(indChannel);

    /* freeze threshold if is needed */
    Inductive_Algo_Freeze_Handle(indChannel);

     /* polyspace:begin < MISRA-C3:16.1 : Not a defect : Justify with annotations > " */
    switch(indChannel->AlgoStateSM)
    {
        case EN_INDUCTIVE_STATE_IDLE:
            /* call idle state function */
            Idle_State_Inductive_Sensor(indChannel);
            break;

        case EN_INDUCTIVE_STATE_DEBOUNCE:
            /* call debounce state function */
            Debounce_State_Inductive_Sensor(indChannel);
            break;

        case EN_INDUCTIVE_STATE_TOUCH:
            /* call touch state function */
            Touch_State_Inductive_Sensor(indChannel);
            break;

        case EN_INDUCTIVE_STATE_OFFDELAY:
            /* call offdelay state function */
            OffDelay_State_Inductive_Sensor(indChannel);
            break;

        default:
	    /* do nothing */
            break;
    }
    /* polyspace:end < MISRA-C3:16.1 : Not a defect : Justify with annotations > " */
}

/*********************************************************************************************************
 *  Name                   : boIsInductiveActive
 *  Description            : If any channel is touched set the flag for active mode
 *                         : 
 *  Parameters             : none
 *  Return                 : none
 *  Critical/explanation   : -
 *   Author                : vradule
 *********************************************************************************************************/
BOOL boIsInductiveActive(void) {
    U8 sensor_id;
    BOOL boAlgo = FALSE;
    for(sensor_id = (U8)0 ;sensor_id < (U8)INDUCTIVE_SENSOR_MAX;sensor_id +=(U8)1)
    {
        if (EN_INDUCTIVE_STATE_TOUCH == inductive_sensor_param[sensor_id].AlgoStateSM)
        /* polyspace < RTE:UNR : Not a defect : Justify with annotations> The condition is not redundant*/
        {
            boAlgo = TRUE;
        }
        else
        {
            /*do nothing*/
        }
    }

    return boAlgo;
}

/*********************************************************************************************************
 *  Name                   : ThresholdReference_Init
 *  Description            : Update Thrshold Reference with Measured Value (only in init).
 *                         : SWR-431
 *  Parameters             : indChannel - pointer to handled channel
 *  Return                 : none
 *  Critical/explanation   : -
 *   Author                : hcostin
 *********************************************************************************************************/
static void ThresholdReference_Init(TASK_INDUCTIVE_SENSOR_PARAMETER * indChannel)
{
    indChannel->LdcRefDebounce = 40u;
    indChannel->ThresholdReference = indChannel->LDC_THRESHOLD;
    indChannel->MinMeasureValue = indChannel->LDC_THRESHOLD;
    indChannel->MinValProcess = U32_MAX;
}



/*********************************************************************************************************
 *  Name                   : algo_check_parameters
 *  Description            : Check the parameters from DDF
 *                         : SSA-209, SSA-255
 *  Parameters             : none
 *  Return                 : none
 *  Critical/explanation   : -
 *   Author                : hcostin
 *********************************************************************************************************/
/* polyspace < MISRA-C3:5.9: Not a defect : Justify with annotations > algo_check_parameters is a static local function. No conflict. */
static void algo_check_parameters(void)
{
    /* polyspace:begin < RTE:UNR : Not a defect : Justify with annotations> Should be kept for future usage*/
    if (ST_inductive_sensor_NVM_params.U16_LDC_DEBOUNCE_NORMAL < 1)
    {
        ST_inductive_sensor_NVM_params.U16_LDC_DEBOUNCE_NORMAL = 1;
    }
    else
    {
        /*do nothing*/
    }
    if (ST_inductive_sensor_NVM_params.U16_LDC_VAL_FOR_REF < 1)
    {
        ST_inductive_sensor_NVM_params.U16_LDC_VAL_FOR_REF = 1;
    }
    else
    {
        /*do nothing*/
    }
    if (ST_inductive_sensor_NVM_params.U16_LDC_DEBOUNCE_ACTIVE < 1)
    {
        ST_inductive_sensor_NVM_params.U16_LDC_DEBOUNCE_ACTIVE = 1;
    }
    else
    {
        /*do nothing*/
    }
    if (ST_inductive_sensor_NVM_params.U16_OPEN_TIMEOUT < 1)
    {
        ST_inductive_sensor_NVM_params.U16_OPEN_TIMEOUT = 1;
    }
    else
    {
        /*do nothing*/
    }
    /* polyspace:end < RTE:UNR : Not a defect : Justify with annotations> Should be kept for future usage*/
}

/*********************************************************************************************************
 *  Name                   : parameters_update
 *  Description            : Update the algo parameters with values from NVM
 *                         : SSA-209, SSA-255
 *  Parameters             : indChannel - pointer to handled channel
 *  Return                 : none
 *  Critical/explanation   : -
 *   Author                : hcostin
 *********************************************************************************************************/
static void parameters_update(TASK_INDUCTIVE_SENSOR_PARAMETER * indChannel)
{
    indChannel->LDC_THRESHOLD = ST_inductive_sensor_NVM_params.U16_LDC_THRESHOLD;
    indChannel->LdcRefDebounce = (U8)ST_inductive_sensor_NVM_params.U16_LDC_VAL_FOR_REF;
    indChannel->LdcDebounce = (U8)ST_inductive_sensor_NVM_params.U16_LDC_DEBOUNCE_ACTIVE;
    indChannel->LdcDebounceTimeOut = ST_inductive_sensor_NVM_params.U16_OPEN_TIMEOUT;
    indChannel->FreezeCounter = ST_inductive_sensor_NVM_params.U16_LDC_FREEZE_CANCEL;
    indChannel->FreezeThreshold = ST_inductive_sensor_NVM_params.U16_LDC_FREEZE_THRESHOLD;
}

/*********************************************************************************************************
 *  Name                   : Inductive_Sensor_Algo_Init
 *  Description            : Call ThresholdReference_Init for every channel and update with values from DDF
 *                         : SWR-432, SSA-209, SSA-255
 *  Parameters             : none
 *  Return                 : none
 *  Critical/explanation   : -
 *   Author                : hcostin
 *********************************************************************************************************/
/* polyspace < MISRA-C3:8.7: Not a defect : Justify with annotations > External Usage dependent on project setup*/
void Inductive_Sensor_Algo_Init(void)
{
    U8 sensor_id;
    storeParametersFromNVM();
    algo_check_parameters();
    for(sensor_id = (U8)0; sensor_id < (U8)INDUCTIVE_SENSOR_MAX; sensor_id +=(U8)1)
    {
        parameters_update(&inductive_sensor_param[sensor_id]);
    }

    for(sensor_id = (U8)0; sensor_id < (U8)INDUCTIVE_SENSOR_MAX; sensor_id +=(U8)1)
    {
        ThresholdReference_Init(&inductive_sensor_param[sensor_id]);
        inductive_sensor_param[sensor_id].AlgoStateSM = EN_INDUCTIVE_STATE_IDLE;
        /* reset freeze counter*/
        inductive_sensor_param[sensor_id].FreezeCounter = 0u;
    }
    U8_Debounce_Time_Reset = (U8)ST_inductive_sensor_NVM_params.U16_LDC_DEBOUNCE_ACTIVE;
}

U8 InductiveAlgo_getInductiveValue(void)
{
    return Algo_KY_Oeffnen_BetaetigungSignal;
}

/*********************************************************************************************************
* Name : Inductive_Algo_Set_Can_Signal
* Description : This function sets CAN signal
* Parameters : none
* Return :
* Critical/explanation : -
* Author : hcostin
*********************************************************************************************************/
/* polyspace < MISRA-C3:8.7: Not a defect : Justify with annotations > External Usage dependent on project setup*/
static void Inductive_Algo_Set_Can_Signal(void)
{
	U8 U8_Signal_Validation = 0;

	if((U8)1 == ST_inductive_sensor_NVM_params.U16_MODE_OF_ACTIVATION_PARAM)
	{
		/* set CAN signal if all channels are touched */
		U8_Signal_Validation = Inductive_Algo_All_Channels_Touched();
	}
	else
	{
		/* set CAN signal if a channel is touched */
		U8_Signal_Validation = Inductive_Algo_One_Channel_Touched();
	}
    /* Used in ECUM callout, ComConf_ComSignal_KY_Oeffnen_Betaetigung_XIX_NFC_TGS_01_XIX_HCP4_CANFD01_ebcf735e_Tx */
    Algo_KY_Oeffnen_BetaetigungSignal = U8_Signal_Validation;
}


/*********************************************************************************************************
* Name : Inductive_Algo_Set_Can_Signal_0
* Description : This function sets CAN signal to 0
* Parameters : none
* Return :
* Critical/explanation : -
* Author : tghenci
*********************************************************************************************************/
void Inductive_Algo_Clear_Can_Signal(void)
{
    Algo_KY_Oeffnen_BetaetigungSignal = 0u;
}

/*********************************************************************************************************
 *  Name                   : Inductive_Sensor_Algo
 *  Description            : interface to handle whole inductive algo including init.
 *                         :
 *  Parameters             : none
 *  Return                 : none
 *  Critical/explanation   : -
 *   Author                : hcostin
 *********************************************************************************************************/
void Inductive_Sensor_Algo(void)
{
    U8 sensor_id;
    U8 U8_power_up_loop;
    static U8 U8_init_flag = U16_INDUCTIVE_NO_OF_INITS;

    /* should works only if the measured values are positives (data is received)*/
    if(U8_Positives_Values != 0u)
    {
        /* call Init only once, when the first positives values comes from inductive chip */
        if(U8_init_flag > 0u)
        {
            for (sensor_id = (U8)0; sensor_id < (U8)INDUCTIVE_SENSOR_MAX; sensor_id += (U8)1)
            {
                for (U8_power_up_loop = (U8)0u; U8_power_up_loop < U8_LDC3114_FILTER_INIT_RECALL; U8_power_up_loop++)
                {
                    LDC3114_iir_filter(&LDC3114_Sensor_Var_Str[sensor_id], LDC3114_Sensor_Var_Str[sensor_id].U32_last_sample);
                    LDC3114_noise_detect(&LDC3114_Sensor_Var_Str[sensor_id], LDC3114_Sensor_Var_Str[sensor_id].U32_last_sample);
                }
            }
            U32_Ldc_Ch0 = LDC3114_Sensor_Var_Str[LDC3114_SENSOR_CH0].U32_filter_unit_result;
            U32_Ldc_Ch1 = LDC3114_Sensor_Var_Str[LDC3114_SENSOR_CH1].U32_filter_unit_result;
            U8_init_flag--;
            Inductive_Sensor_Algo_Init();
        }
        else
        {
            /* call inductive sensor SM for every configured inductive channel */
            for (sensor_id = (U8)0; sensor_id < (U8)INDUCTIVE_SENSOR_MAX; sensor_id += (U8)1)
            {
                LDC3114_iir_filter(&LDC3114_Sensor_Var_Str[sensor_id], LDC3114_Sensor_Var_Str[sensor_id].U32_last_sample);
                LDC3114_noise_detect(&LDC3114_Sensor_Var_Str[sensor_id], LDC3114_Sensor_Var_Str[sensor_id].U32_last_sample);
                U32_Ldc_Ch0 = LDC3114_Sensor_Var_Str[LDC3114_SENSOR_CH0].U32_filter_unit_result;
                U32_Ldc_Ch1 = LDC3114_Sensor_Var_Str[LDC3114_SENSOR_CH1].U32_filter_unit_result;
                SM_Inductive_Sensor(&inductive_sensor_param[sensor_id]);
            }

            Inductive_Algo_Set_Can_Signal();
        }
    }
    else
    {
        /* the inductive chip is not working */
        /* do nothing */
    }
        
}

/*********************************************************************************************************
 *  Name                   : Inductive_Algo_SMState_GetDiagData
 *  Description            : interface to get algo state.
 *                         :
 *  Parameters             : pu8buffer
 *  Return                 : none
 *  Critical/explanation   : -
 *   Author                : hcostin
 *********************************************************************************************************/
/* polyspace < MISRA-C3:D4.5 : Not a defect : Justify with annotations > it is a function local variable so it has only minor meaning in module level */
extern void Inductive_Algo_SMState_GetDiagData(U8 *pu8buffer)
{
    pu8buffer[0] = (U8)inductive_sensor_param[0].AlgoStateSM;
    pu8buffer[1] = (U8)inductive_sensor_param[1].AlgoStateSM;
}

/*********************************************************************************************************
 *  Name                   : Inductive_Algo_ThresholdValue_GetDiagData
 *  Description            : interface to get Threshold Value.
 *                         :
 *  Parameters             : pu32buffer
 *  Return                 : none
 *  Critical/explanation   : -
 *   Author                : hcostin
 *********************************************************************************************************/
extern void Inductive_Algo_ThresholdValue_GetDiagData(U32 *pu32buffer)
{
    pu32buffer[0] = inductive_sensor_param[0].ThresholdValue;
    pu32buffer[1] = inductive_sensor_param[1].ThresholdValue;
}

/*********************************************************************************************************
 *  Name                   : Inductive_Algo_All_Channels_Touched
 *  Description            : interface to check if all channels are touched
 *                         : SWR-441
 *  Parameters             : none
 *  Return                 : U8_allAreTouched - 1u for all channels touched xor 0u in other case
 *  Critical/explanation   : -
 *   Author                : hcostin
 *********************************************************************************************************/
/* polyspace < MISRA-C3:8.7: Not a defect : Justify with annotations > External Usage dependent on project setup*/
static U8 Inductive_Algo_All_Channels_Touched(void)
{
    /* assume that both are touched from the beginning */
    U8 U8_allAreTouched = 1u;
    U8 sensor_id;
    U8_Inductive_Algo_Valid_Touch = 1u;

    for(sensor_id = (U8)0; sensor_id < (U8)INDUCTIVE_SENSOR_MAX; sensor_id +=(U8)1)
    {
        if(EN_INDUCTIVE_STATE_TOUCH != inductive_sensor_param[sensor_id].AlgoStateSM)
        {
            /* channel not touched */
            U8_allAreTouched = 0u;
            U8_Inductive_Algo_Valid_Touch = 0u;
        }
        else
        {
            /* channel touched */
            /* do nothing */
        }
    }

    return U8_allAreTouched;
}

/*********************************************************************************************************
 *  Name                   : Inductive_Algo_One_Channel_Touched
 *  Description            : interface to check if one channel is touched
 *                         :
 *  Parameters             : none
 *  Return                 : U8_allAreTouched - 1u for one channel touched xor 0u in other case
 *  Critical/explanation   : -
 *   Author                : bbarlea
 *********************************************************************************************************/
/* polyspace < MISRA-C3:8.7: Not a defect : Justify with annotations > External Usage dependent on project setup*/
static U8 Inductive_Algo_One_Channel_Touched(void)
{
    /* assume that both are not touched from the beginning */
    U8 U8_oneTouched = 0u;
    U8_Inductive_Algo_Valid_Touch = 0u;
    U8 sensor_id;

    for(sensor_id = (U8)0; sensor_id < (U8)INDUCTIVE_SENSOR_MAX; sensor_id +=(U8)1)
    {
        if(EN_INDUCTIVE_STATE_TOUCH == inductive_sensor_param[sensor_id].AlgoStateSM)
        {
            /* channel touched */
            U8_oneTouched = 1u;
            U8_Inductive_Algo_Valid_Touch = 1u;
        }
        else
        {
            /* channel not touched */
            /* do nothing */
        }
    }

    return U8_oneTouched;
}

/*********************************************************************************************************
 *  Name                   : Inductive_Algo_Freeze_Handle
 *  Description            : start the freeze of threshold
 *                         :
 *  Parameters             : indChannel - pointer to handled channel
 *  Return                 : none
 *  Critical/explanation   : -
 *   Author                : hcostin
 *********************************************************************************************************/
static void Inductive_Algo_Freeze_Handle(TASK_INDUCTIVE_SENSOR_PARAMETER * indChannel)
{

    if((indChannel->FreezeThreshold) > (*(indChannel->MeasuredValue)))
    {
        if(0U == indChannel->FreezeCounter)
        {
            /* Check if Freeze Feature was active once since MeasuredValue has been below FreezeThreshold */
            if (0U == indChannel->FreezeActiveOnce)
            {
                /* reset freeze counter and set active once */
                indChannel->FreezeCounter = ST_inductive_sensor_NVM_params.U16_LDC_FREEZE_CANCEL;
                indChannel->LdcRefDebounce = (U8)ST_inductive_sensor_NVM_params.U16_LDC_VAL_FOR_REF;
                indChannel->FreezeActiveOnce = 1U;
            }
            else
            {
                /* Update FreezeThreshold */
                if (indChannel->ThresholdReference >= ST_inductive_sensor_NVM_params.U16_LDC_FREEZE_THRESHOLD)
                {
                    indChannel->FreezeThreshold = indChannel->ThresholdReference - ST_inductive_sensor_NVM_params.U16_LDC_FREEZE_THRESHOLD;
                }
                else
                {
                    indChannel->FreezeThreshold = 0u;
                }
            }
        }
        else
        {
            /* decrement freeze counter */
            indChannel->FreezeCounter--;
        }
    }
    else
    {
        /* Update FreezeThreshold */
        if (indChannel->ThresholdReference >= ST_inductive_sensor_NVM_params.U16_LDC_FREEZE_THRESHOLD)
        {
            indChannel->FreezeThreshold = indChannel->ThresholdReference - ST_inductive_sensor_NVM_params.U16_LDC_FREEZE_THRESHOLD;
        }
        else
        {
            indChannel->FreezeThreshold = 0u;
        }
        indChannel->FreezeActiveOnce = 0u;
        indChannel->FreezeCounter = 0;
    }
}

/*********************************************************************************************************
 *  Name                   : Induictive_Algo_Set_Debounce_Normal
 *  Description            : interface to set the debounce normal
 *                         : 
 *  Parameters             : none
 *  Return                 : 
 *  Critical/explanation   : -
 *   Author                : hcostin
 *********************************************************************************************************/
extern void Induictive_Algo_Set_Debounce_Normal(void)
{
    U8 sensor_id;

    for(sensor_id = (U8)0; sensor_id < (U8)INDUCTIVE_SENSOR_MAX; sensor_id +=(U8)1)
    {
        inductive_sensor_param[sensor_id].LdcDebounce = (U8)ST_inductive_sensor_NVM_params.U16_LDC_DEBOUNCE_NORMAL;
        U8_Debounce_Time_Reset = (U8)ST_inductive_sensor_NVM_params.U16_LDC_DEBOUNCE_NORMAL;
    }
}

/*********************************************************************************************************
 *  Name                   : Induictive_Algo_Set_Debounce_Active
 *  Description            : interface to set the debounce active
 *                         : 
 *  Parameters             : none
 *  Return                 : 
 *  Critical/explanation   : -
 *   Author                : hcostin
 *********************************************************************************************************/
extern void Induictive_Algo_Set_Debounce_Active(void)
{
    U8 sensor_id;

    for(sensor_id = (U8)0; sensor_id < (U8)INDUCTIVE_SENSOR_MAX; sensor_id +=(U8)1)
    {
        inductive_sensor_param[sensor_id].LdcDebounce = (U8)ST_inductive_sensor_NVM_params.U16_LDC_DEBOUNCE_ACTIVE;
        U8_Debounce_Time_Reset = (U8)ST_inductive_sensor_NVM_params.U16_LDC_DEBOUNCE_ACTIVE;
    }
}
