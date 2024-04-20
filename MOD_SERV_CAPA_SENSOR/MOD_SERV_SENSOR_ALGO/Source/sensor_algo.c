#define SENSOR_ALGO_C

#ifndef INTEGRATE_FROM_V4
#include "Platform_Types.h"
#endif
#include "Compiler.h"
#include "sensor_aquisition.h"
#include "sensor_mcvd.h"
#include "sensor_algo.h"
#include "string.h"
#include "Com.h"
#include "EcuM.h"
#include "IntegrationTests.h"
#include "NvmMng.h"
#include "BatterySupervisor.h"
#include "inductive_sensor_algo.h"
#include "PlayProtection.h"

ST_lock_sensor_NVM_parameters_T ST_lock_sensor_NVM_params;
ST_unlock_sensor_NVM_parameters_T ST_unlock_sensor_NVM_params;

#define U8_SET_BIT ((U8)1)
#define U8_CLEAR_BIT ((U8)0)
#define LOCK_CROSSTALK_THRESHOLD ((U16)50)

#if (0 == U8_ER_DEBOUNCE_EEP)
#define U8_SX_DEBOUNCE_EEP ((U8)1) /*Minimum deounce counter to creating enough consecutive positive shifts of the reading above the baseline by at least the unlock APPROACH threshold*/
#endif

#if (0 == U8_VR_DEBOUNCE_EEP)
#define U8_SX_DEBOUNCE_EEP ((U8)1) /*Minimum deounce counter to creating enough consecutive positive shifts of the reading above the baseline by at least the lock APPROACH threshold*/
#endif

/************* Global variables *********************************/
SENSOR_BITS_T Sensor_Bits;

/************* Local variables **********************************/
/** Enumeration of the valid  active-mode sensor states */
STATIC NEAR S_ALGO_STATUS_FLAGS Algo_State_Flags;
NEAR ENUM_ALGO_SM_STATE_TYPE EN_ER_AlgoStateSM; /* active-mode unlock sensor states */
NEAR ENUM_ALGO_SM_STATE_TYPE EN_VR_AlgoStateSM; /* active-mode lock sensor states */
STATIC NEAR U16 U16_ER_RefWert;   /*sensor baseline calculated in function Unlock_UpdateBaseline*/
STATIC NEAR U16 U16_VR_RefWert;   /*sensor baseline calculated in function lock_UpdateBaseline*/
STATIC NEAR U16 U16_VR_Max_Value; /* save the calculated lock baseline until REF_VAL_COUNT has reached  */
STATIC NEAR U16 U16_ER_Max_Value; /* save the calculated unlock baseline until REF_VAL_COUNT has reached  */
STATIC NEAR U16 U16_ER_Rekcount;  /*counter for baseline A new calculation,that  will occur every REF_VAL_COUNT Unlock_UpdateBaseline  call.*/
STATIC NEAR U16 U16_VR_Rekcount;  /*counter for baseline A new calculation,that  will occur every REF_VAL_COUNT lock_UpdateBaseline  call.*/
STATIC U16 U16_ErNoiseOccurredCnt;
STATIC U16 U16_VrNoiseOccurredCnt;
STATIC U16 U16_VR_FreezeCounter;
STATIC U16 U16_ER_FreezeCounter;
STATIC U16 b_VR_FreezeOnce;
STATIC U16 b_ER_FreezeOnce;
STATIC U8 U8_VR_CrossTalk;

STATIC U16 U16_er_as_entprell;      /* Debounce Counter for active-mode unlock sensor states*/
STATIC U8 U8_ErOffCounter;          /* delay to leave from active-mode approach or TOUCH unlock sensor state*/
STATIC NEAR U16 U16_vr_as_entprell; /* Debounce Counter for active-mode lock sensor states*/
STATIC U8 U8_VrOffCounter;          /*delay to leave from active-mode approach or TOUCH lock sensor state*/
STATIC U16 U16_er_active_max_time;
STATIC U16 U16_vr_active_max_time;
STATIC U16 U16_er_offdelay;
STATIC U16 U16_vr_offdelay;
STATIC U16 U16_er_deactivation_debounce;
STATIC U16 U16_vr_deactivation_debounce;
STATIC U8 U8_VrDeactivationThresh; /* maintain threshold at touch level 2 samples before off delay state*/
STATIC U16 U16_ER_Freeze_Threshold_Ref;
STATIC U16 U16_VR_Freeze_Threshold_Ref;
STATIC U16 U16_ER_Tracking_Threshold;
STATIC U16 U16_VR_Tracking_Threshold;
STATIC U16 U16_VR_Touch_Threshold;

void getRefThreshold(U16 * buff)
{
    *(buff) = U16_ER_RefWert;
    *(buff+1) = U16_VR_RefWert;
    *(buff+2) = U16_ER_Freeze_Threshold_Ref;
    *(buff+3) = U16_VR_Freeze_Threshold_Ref;
    *(buff+4) = U16_VR_Touch_Threshold;
}

/************* Local Functions **********************************/
STATIC void Unlock_UpdateBaseline(void);
STATIC void Lock_UpdateBaseline(void);
STATIC void Unlock_StateMachine(void);
STATIC void Lock_StateMachine(void);
STATIC BOOL_BITS_T Get_Er_Approach_Detect(void);
STATIC BOOL_BITS_T Get_Vr_Approach_Detect(void);
static void Capa_Algo_VR_Freeze_Handle(void);
STATIC void update_VR_threshold_crosstalk(void);

/*------------------------------------------------------------------------
 Function      : algo_decrement_lock_activation_counter
 Description   : Timeout for lock sensor
 Return        : void
 ------------------------------------------------------------------------*/
STATIC void algo_decrement_lock_activation_counter(void)
{
    if (0U < U16_vr_active_max_time)
    {
        U16_vr_active_max_time--;
    }
    else
    {
        /*do nothing*/
    }
}

/*------------------------------------------------------------------------
 Function      : algo_decrement_unlock_activation_counter
 Description   : Timeout for unlock sensor
 Return        : void
 ------------------------------------------------------------------------*/
STATIC void algo_decrement_unlock_activation_counter(void)
{
    if (0U < U16_er_active_max_time)
    {
        U16_er_active_max_time--;
    }
    else
    {
        /*do nothing*/
    }
}


/*------------------------------------------------------------------------
 Function      : boIsCapaActive
 Description   : check if any sensor is touched
 Return        : void
 ------------------------------------------------------------------------*/
BOOL boIsCapaActive(void)
{
    BOOL boAlgo = FALSE;
    if ((EN_ASM_SX_APPROACH == EN_ER_AlgoStateSM) || 
        (NvmMng_getEnableWakeUpByKessy() && ((EN_ASM_SX_TOUCH == EN_VR_AlgoStateSM) || (EN_ASM_SX_APPROACH == EN_VR_AlgoStateSM))))
    {
        boAlgo = TRUE;
    }
    else
    {
        /*do nothing*/
    }
    return boAlgo;
}

/*------------------------------------------------------------------------
 Function      : boIsCapaActive
 Description   : sanity check for eeprom parameters
 Return        : void
 ------------------------------------------------------------------------*/
STATIC void algo_check_parameters(void)
{

    if (ST_lock_sensor_NVM_params.U16_P_VR_TOUCH_THRESHOLD < ST_lock_sensor_NVM_params.U16_P_VR_APPROACH_THRESHOLD)
    {
        ST_lock_sensor_NVM_params.U16_P_VR_TOUCH_THRESHOLD = ST_lock_sensor_NVM_params.U16_P_VR_APPROACH_THRESHOLD;
    }
    else
    {
        /*do nothing*/
    }

    if (ST_unlock_sensor_NVM_params.U16_P_ER_DEBOUNCE < 1u)
    {
        ST_unlock_sensor_NVM_params.U16_P_ER_DEBOUNCE = 1u;
    }
    else
    {
        /*do nothing*/
    }

    if (ST_lock_sensor_NVM_params.U16_P_VR_DEBOUNCE < 1u)
    {
        ST_lock_sensor_NVM_params.U16_P_VR_DEBOUNCE = 1u;
    }
    else
    {
        /*do nothing*/
    }
    if (ST_unlock_sensor_NVM_params.U16_P_ER_VAL_FOR_REF < 1u)
    {
        ST_unlock_sensor_NVM_params.U16_P_ER_VAL_FOR_REF = 1u;
    }
    else
    {
        /*do nothing*/
    }
    if (ST_lock_sensor_NVM_params.U16_P_VR_VAL_FOR_REF < 1u)
    {
        ST_lock_sensor_NVM_params.U16_P_VR_VAL_FOR_REF = 1u;
    }
    else
    {
        /*do nothing*/
    }

    if (ST_unlock_sensor_NVM_params.U16_P_ER_DEACTIVATION_DEBOUNCE < 1u)
    {
        ST_unlock_sensor_NVM_params.U16_P_ER_DEACTIVATION_DEBOUNCE = 1u;
    }
    else
    {
        /*do nothing*/
    }
    if (ST_lock_sensor_NVM_params.U16_P_VR_DEACTIVATION_DEBOUNCE < 1u)
    {
        ST_lock_sensor_NVM_params.U16_P_VR_DEACTIVATION_DEBOUNCE = 1u;
    }
    else
    {
        /*do nothing*/
    }
    if (ST_lock_sensor_NVM_params.U16_P_VR_OFFDELAY < 1u)
    {
        ST_lock_sensor_NVM_params.U16_P_VR_OFFDELAY = 1u;
    }
    else
    {
        /*do nothing*/
    }
    if (ST_unlock_sensor_NVM_params.U16_P_ER_OFFDELAY < 1u)
    {
        ST_unlock_sensor_NVM_params.U16_P_ER_OFFDELAY = 1u;
    }
    else
    {
        /*do nothing*/
    }
}

/*------------------------------------------------------------------------
 Function      : CAPA_publishCanSignals
 Description   : Initialize algo variables
 Return        : void
 ------------------------------------------------------------------------*/
void algo_init(void)
{
    algo_check_parameters();
    U16_ErNoiseOccurredCnt = U16_MAX;
    U16_VrNoiseOccurredCnt = U16_MAX;
    U16_er_active_max_time = ST_unlock_sensor_NVM_params.U16_P_ER_TIMEOUT;
    U16_vr_active_max_time = ST_lock_sensor_NVM_params.U16_P_VR_TIMEOUT;
    U16_vr_deactivation_debounce = ST_lock_sensor_NVM_params.U16_P_VR_DEACTIVATION_DEBOUNCE;
    U16_er_deactivation_debounce = ST_unlock_sensor_NVM_params.U16_P_ER_DEACTIVATION_DEBOUNCE;
    U16_vr_offdelay = ST_lock_sensor_NVM_params.U16_P_VR_OFFDELAY;
    U16_er_offdelay = ST_unlock_sensor_NVM_params.U16_P_ER_OFFDELAY;

    SET_ER_SENSOR_ALGO_STATE(EN_ASM_SX_IDLE); /*Set the Unlock state machine to Idle */
    SET_VR_SENSOR_ALGO_STATE(EN_ASM_SX_IDLE); /*Set the lock state machine to Idle */
    RESET_ER_REF_VALUE();                     /*Reset  Unlock sensor Baseline to the Maximum 65335,to Prevent thas the Sensor reading value will cross the baseline during the Initialising Time*/
    RESET_VR_REF_VALUE();                     /*Reset lock sensor Baseline to the Maximum 65335,to Prevent thas the Sensor reading value will cross the baseline during the Initialising Time*/
    Algo_State_Flags.U8_Algo_Byte = 0u;
    U16_ER_FreezeCounter = ST_unlock_sensor_NVM_params.U16_P_ER_FREEZE_CANCEL;
    U16_VR_FreezeCounter = ST_lock_sensor_NVM_params.U16_P_VR_FREEZE_CANCEL;
}


/*------------------------------------------------------------------------
 Function      : CAPA_publishCanSignals
 Description   : Publish com signals when ECU is in Active state
 Return        : void
 ------------------------------------------------------------------------*/
void CAPA_publishCanSignals(void)
{
    U8 signalValue = 0u;
    NFC_TSG_Kapa_deaktivieren_CAN_Signal_values Kapa_deaktivieren;

    signalValue = Algo_State_Flags._Algo_Bit.ER_Approach_u1;
    PlayProt_writeUnlockValue(&signalValue);
    (void)Com_SendSignal(ComConf_ComSignal_B_UnlockApproach, &signalValue);
    signalValue = InductiveAlgo_getInductiveValue();
    PlayProt_writeInductiveValue(&signalValue);
    (void)Com_SendSignal(ComConf_ComSignal_B_Inductive, &signalValue);
    
    
    // (void)Com_ReceiveSignal(ComConf_ComSignal_NFC_TGS_Kapa_deaktivieren_XIX_KeylessAccess_01_XIX_HCP4_CANFD01_51289079_Rx, &Kapa_deaktivieren);

    //     if (!Kapa_deaktivieren)
    //     {
            if (1u == Algo_State_Flags._Algo_Bit.VR_TOUCH_u1)
            {
                signalValue = Algo_State_Flags._Algo_Bit.VR_TOUCH_u1;
                PlayProt_writeLockValue(&signalValue);
                (void)Com_SendSignal(ComConf_ComSignal_B_LockTouch, &signalValue);
                (void)Com_SendSignal(ComConf_ComSignal_B_LockApproach, &signalValue);
            }
            else if (1u == Algo_State_Flags._Algo_Bit.VR_Approach_u1)
            {
                signalValue = Algo_State_Flags._Algo_Bit.VR_Approach_u1;
                PlayProt_writeLockValue(&signalValue);
                (void)Com_SendSignal(ComConf_ComSignal_B_LockApproach, &signalValue);
            }
            else
            {
                signalValue = 0u;
                (void)Com_SendSignal(ComConf_ComSignal_B_LockTouch, &signalValue);
                (void)Com_SendSignal(ComConf_ComSignal_B_LockApproach, &signalValue);
            }
        // }
        // else
        // {
        //     /* Do nothing */
        // }
}

/*------------------------------------------------------------------------
 Function      : algorithmus
 Description   : main function for algo
 Return        : void
 ------------------------------------------------------------------------*/
algo_export void algorithmus(void)
{
    if ((BOOL)FALSE == EcuM_lock_sensor_blocking())
    {
        Lock_StateMachine();
    }
    else
    {
        /* do nothing */
    }

    if ((BOOL)FALSE == EcuM_unlock_sensor_blocking())
    {
        Unlock_StateMachine();
    }
    else
    {
        /* do nothing */
    }
} /* algorithmus */



/*------------------------------------------------------------------------
 Function      : Unlock_UpdateBaseline
 Description   : Baseline for Unock sensor
 Return        : void
 ------------------------------------------------------------------------*/
STATIC void Unlock_UpdateBaseline(void)
{
    U16_ER_Rekcount++;
   
    if (ST_unlock_sensor_NVM_params.U16_P_ER_VAL_FOR_REF <= U16_ER_Rekcount) /*The Baseline Update #Window is  reaches*/
    {
        U16_ER_RefWert = U16_ER_Max_Value;   /* the baseline is updated to equal to the  sensor Maximum value which finding in this Window (REF_VAL_COUNT)*/
        U16_ER_Rekcount = (U8)0x00;          /* Reset the counter needed to update the reference value */
        U16_ER_Max_Value = U16_ER_MeasValue; /* Update the Maximum as initial value for the next evaluation*/
    }
    else if ((U16_ER_MeasValue > U16_ER_Max_Value)) /* counter is reseting or the current Sensor Reading is greater than the */
    {
        U16_ER_Max_Value = U16_ER_MeasValue; /* Update the Maximum */
    }
    else
    {
        /*do nothing*/
    }
    
}

/*------------------------------------------------------------------------
 Function      : Unlock_reference_tracking
 Description   : reference tracking during touch state for unlock sensor
 Return        : void
 ------------------------------------------------------------------------*/
STATIC void Unlock_reference_tracking(void)
{
    
    if (((U32)U16_ER_REF_TRACKING_CONS * (U32)ST_unlock_sensor_NVM_params.U16_P_ER_APPROACH_THRESHOLD) < (U32)U16_ER_MeasValue)
    {
        U16_ER_Tracking_Threshold = (U16_ER_MeasValue - (U16_ER_REF_TRACKING_CONS * ST_unlock_sensor_NVM_params.U16_P_ER_APPROACH_THRESHOLD));
    }
    else
    {
        /*do nothing*/
    }
    if (U16_ER_Tracking_Threshold > U16_ER_RefWert)
    {
        U16_ER_RefWert = U16_ER_Tracking_Threshold; /*  The baseline is now updates for a quick off if hand go out from the sensor */
    }
    else
    {
        /*do nothing*/
    }
}


/*------------------------------------------------------------------------
 Function      : Unlock_reference_tracking
 Description   : start the freeze of threshold
 Return        : void
 ------------------------------------------------------------------------*/
static void Capa_Algo_ER_Freeze_Handle(void)
{
    /* compute the freeze threshold ref  */
    U16_ER_Freeze_Threshold_Ref = (U16) U16_ER_RefWert + ST_unlock_sensor_NVM_params.U16_P_ER_FREEZE_THRESHOLD;

    
    if (U16_ER_Freeze_Threshold_Ref > U16_ER_MeasValue)  
    {
        /* update the base reference value with max measuered value */
        Unlock_UpdateBaseline(); 
        U16_ER_FreezeCounter = 0u;
        b_ER_FreezeOnce = 0u;

    }
    else if (0u == U16_ER_FreezeCounter)
    {        
        if (GET_ER_SENSOR_ALGO_STATE() == EN_ASM_SX_APPROACH)
        {
            /* If approach still present use quick off threshold */
            Unlock_reference_tracking();
            b_ER_FreezeOnce = 0u;
        }
        else if ((U16_ER_Freeze_Threshold_Ref < U16_ER_MeasValue) && (b_ER_FreezeOnce == 0u))
        {
            /* reset freeze counter*/
            U16_ER_FreezeCounter = ST_unlock_sensor_NVM_params.U16_P_ER_FREEZE_CANCEL;
            b_ER_FreezeOnce = 1u;
        }
        else if (b_ER_FreezeOnce == 1u)
        {
            Unlock_UpdateBaseline();
        }
        else
        {
            /* Do nothing */
        }
    }
    else
    {
        /* decrement freeze counter */
        U16_ER_FreezeCounter--;
    }
}

/*!
******************************************************************************
* \brief
* Lock_Reference_tracking
*
* \details
* @ingroup Decoding
*
*  reference tracking during touch state : update The baseline during  touche state for a quick off if hand release the sensor 
* SWR-473
******************************************************************************
*
* \sync          synchronous (function done in one pass)
* \reent         non reentrant
*
* \pre           all must be initialized.
* \post          process is started
*
* \param[in]     void
* \param[out]    void
*
* \glob_start	  EN_VR_AlgoStateSM        active-mode lock sensor states
*                 U8_Er_400ms_activation   approach und TOUCH activation  Counter
*                 Algo_State_Flags         Enumeration of the valid  active-mode sensor states 
* \glob_end
*
* \retval         void
*
******************************************************************************
*
* \author        Y.badal
* \version       1.0
* \date
*
******************************************************************************
*
* \par Change history:
*       -
*
******************************************************************************
*
* \par Remarks:
* CallFunct:
*
******************************************************************************/
/*------------------------------------------------------------------------
 Function      : Lock_Reference_tracking
 Description   : reference tracking during touch state for lock sensor
 Return        : void
 ------------------------------------------------------------------------*/
STATIC void Lock_Reference_tracking(void)
{
    
    if (((U32)U16_VR_REF_TRACKING_CONS * (U32)ST_lock_sensor_NVM_params.U16_P_VR_TOUCH_THRESHOLD) < (U32)U16_VR_MeasValue)
    {
        U16_VR_Tracking_Threshold = (U16_VR_MeasValue - (U16_VR_REF_TRACKING_CONS * ST_lock_sensor_NVM_params.U16_P_VR_TOUCH_THRESHOLD));
    }
    else
    {
        /*do nothing*/
    }
    if (U16_VR_Tracking_Threshold > U16_VR_RefWert)
    {
        U16_VR_RefWert = U16_VR_Tracking_Threshold; /*  The baseline is now updates for a quick off if hand go out from the sensor */
    }
    else
    {
        /*do nothing*/
    }
}

/*********************************************************************************************************
 *  Name                   : Capa_Algo_VR_Freeze_Handle
 *  Description            : start the freeze of threshold
 *                         :
 *  Parameters             : none
 *  Return                 : none
 *  Critical/explanation   : -
 *   Author                : tghenci
 *********************************************************************************************************/
static void Capa_Algo_VR_Freeze_Handle(void)
{
    /* compute the freeze threshold ref  */
        U16_VR_Freeze_Threshold_Ref = (U16) (U16_VR_RefWert + ST_lock_sensor_NVM_params.U16_P_VR_FREEZE_THRESHOLD + U8_VR_CrossTalk);

    
    if (U16_VR_Freeze_Threshold_Ref > U16_VR_MeasValue)  
    {
        /* update the base reference value with max measuered value */
        Lock_UpdateBaseline(); 
        U16_VR_FreezeCounter = 0u;
        b_VR_FreezeOnce = 0u;

    }
    else if (0u == U16_VR_FreezeCounter)
    {
        if ((GET_VR_SENSOR_ALGO_STATE() == EN_ASM_SX_APPROACH) || (GET_VR_SENSOR_ALGO_STATE() == EN_ASM_SX_TOUCH))
        {
            /* If touch still present use quick off threshold */
            Lock_Reference_tracking();
            b_VR_FreezeOnce = 0u;
        }
        else if ((U16_VR_Freeze_Threshold_Ref < U16_VR_MeasValue) && (b_VR_FreezeOnce == 0u))
        {
            /* reset freeze counter*/
            U16_VR_FreezeCounter = ST_lock_sensor_NVM_params.U16_P_VR_FREEZE_CANCEL;
            b_VR_FreezeOnce = 1u;
        }
        else if (b_VR_FreezeOnce == 1u)
        {
            Lock_UpdateBaseline();
        }
        else
        {
            /* Do nothing */
        }
    }
    else
    {
        /* decrement freeze counter */
        U16_VR_FreezeCounter--;
    }
}

/*!
******************************************************************************
* \brief
* Lock_UpdateBaseline
*
* \details
* @ingroup Decoding
*  calculate Baseline for Lock sensor ,REF_VAL_COUNT Determines how often the baseline Maximum will
             be updated. A new calculation will occur every REF_VAL_COUNT decode service call.
             Allowed Range :: [ 1 to 255 ].
@NOTE        calling this only in state and condition where the baseline is able to be
             updated, and we only use the latest Maximum reading to update the baseline once we
             know it's not crossing any thresholds (TOUCH or Approach).
* SWR-481, SWR-466
******************************************************************************
*
* \sync          synchronous (function done in one pass)
* \reent         non reentrant
*
* \pre           all must be initialized.
* \post          process is started
*
* \param[in]     void
* \param[out]    void
*
* \glob_start	 U16_VR_Rekcount        counter for baseline A new calculation,that  will occur every REF_VAL_COUNT lock_UpdateBaseline  call.
*                U16_VR_MeasValue;     final measurement value VR
 *               U16_VR_RefWert        sensor baseline calculated in function lock_UpdateBaseline
* \glob_end
*
* \retval         void
******************************************************************************
*
* \author        Y.badal
* \version       1.0
* \date          15.02.2015
*
******************************************************************************
*
* \par Change history:
*       -
*
******************************************************************************
*
* \par Remarks:
* CallFunct:
*
******************************************************************************/
STATIC void Lock_UpdateBaseline(void)
{
    /* polyspace < RTE:OVFL : Not a defect : Justify with annotations >"The index is not outside of the boundaries and the operation will not result into an overflow." */
    /* polyspace < MISRA-C3:D4.1 : Not a defect : Justify with annotations >"The index is not outside of the boundaries and the operation will not result into an overflow." */
    U16_VR_Rekcount++; /* firstly. increment the counter to start from 1 value on entry in IDLE state (see the INC-00000772) and to update the reference value once to U8_VR_REF_VAL_COUNT samples */
   
    if (ST_lock_sensor_NVM_params.U16_P_VR_VAL_FOR_REF <= U16_VR_Rekcount) /*The Baseline Update #Window is  reaches*/
    {
        U16_VR_RefWert = U16_VR_Max_Value;   /* the baseline is updated to equal to the  sensor Maximum value finding in this Window (REF_VAL_COUNT)*/
        U16_VR_Rekcount = (U8)0x00;          /* Reset the counter needed to update the reference value */
        U16_VR_Max_Value = U16_VR_MeasValue; /* Update the Maximum */
    }
    else if ((U16_VR_MeasValue > U16_VR_Max_Value)) /* counter is reseting or the current Sensor Reading is greater than the */
    {
        U16_VR_Max_Value = U16_VR_MeasValue; /* Update the Maximum */
    }
    else
    {
        /* Do nothing */
    }
    
}

/*!
******************************************************************************
* \brief
* Unlock_UpdateBaseline_by_noise
*
* \details
* @ingroup Decoding
*  add offset to the reference by noise detection
*  SWR-614, SWR-616
******************************************************************************
*
* \sync          synchronous (function done in one pass)
* \reent         non reentrant
*
* \pre           all must be initialized.
* \post          process is started
*
* \param[in]     void
* \param[in]
*
* \glob_start	 U16_VR_Rekcount        counter for baseline A new calculation,that  will occur every REF_VAL_COUNT lock_UpdateBaseline  call.
*                U16_VR_MeasValue;     final measurement value VR
*               U16_VR_RefWert        sensor baseline calculated in function lock_UpdateBaseline
* \glob_end
*
* \retval         void
******************************************************************************
*
* \author        Y.badal
* \version       1.0
* \date          14.03.2016
*
******************************************************************************
*
* \par Change history:
*       -
*
******************************************************************************
*
* \par Remarks:
* CallFunct:
*
******************************************************************************/
STATIC void Unlock_UpdateBaseline_by_noise(void)
{
    if (U8_SET_BIT == Sensor_Bits.ER_Noiseflag_u1) /*check  Sensor Noise Flag from Sensor Analysing Funktion is set*/
    /* polyspace < RTE:UNR : Not a defect : Justify with annotations> The condition is not redundant*/
    {
        /* polyspace<MISRA-C3:D4.1 : Not a defect : Justify with annotations > "No Error: Checks at beginning of calling function Get_Er_Approach_Detect make sure that overflow will not occur" */
        U16_ER_Twert += ST_unlock_sensor_NVM_params.U16_P_ER_NOISE_OFFSET; /* Update the baseline with an equal */ /* polyspace RTE:OVFL [Not a defect:Low] "No Error: Checks at beginning of calling function Get_Er_Approach_Detect make sure that overflow will not occur" */
        U16_ErNoiseOccurredCnt = U8_NULL;
    }
    else
    {
        if (ST_unlock_sensor_NVM_params.U16_P_ER_NOISE_ACTIVE > U16_ErNoiseOccurredCnt)
        /* polyspace < RTE:UNR : Not a defect : Justify with annotations> The condition is not redundant*/
        {
            /* polyspace<MISRA-C3:D4.1 : Not a defect : Justify with annotations > "No Error: Checks at beginning of calling function Get_Er_Approach_Detect make sure that overflow will not occur" */
            U16_ER_Twert += ST_unlock_sensor_NVM_params.U16_P_ER_NOISE_OFFSET; /* Update the baseline with an equal */ /* polyspace RTE:OVFL [Not a defect:Low] "No Error: Checks at beginning of calling function Get_Er_Approach_Detect make sure that overflow will not occur" */
            U16_ErNoiseOccurredCnt++;
        }
        else
        {
            /*do nothing*/
        }
    }
}
/*!
******************************************************************************
* \brief
* Get_Er_Approach_Detect
*
* \details
* @ingroup Decoding
*  check if Sensor reading is  greater than the baseline  by at least the approach or TOUCH threshold
   NOTE: if a noise has occured the baseline will be updated with naoiseoffset
* SWR-488
******************************************************************************
*
* \sync          synchronous (function done in one pass)
* \reent         non reentrant
*
* \pre           all must be initialized.
* \post          process is started
*
* \param[in]     void
* \param[in]
*
* \glob_start	   U16_ER_MeasValue final measurement value ER from sensor modul
 *                 U16_ER_Twert     sensor baseline calculated in this funktion
 *                 U16_ER_RefWert   sensor baseline calculated in function Unlock_UpdateBaseline
* \glob_end
*
* \retval         BOOL_BITS_T Return_bo
 *                Bits approach or touch will be set if Sensor reading is  greater than the baseline
*
******************************************************************************
*
* \author        Y.badal
* \version       1.0
* \date          07.01.2015
*
******************************************************************************
*
* \par Change history:
*       -
*
******************************************************************************
*
* \par Remarks:
* CallFunct:
*
******************************************************************************/
STATIC BOOL_BITS_T Get_Er_Approach_Detect(void)
{
    BOOL_BITS_T Return_bo = {0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u};

    if ((U32)U16_MAX_VALUE <=
        (((U32)ST_unlock_sensor_NVM_params.U16_P_ER_NOISE_OFFSET + (U32)ST_unlock_sensor_NVM_params.U16_P_ER_APPROACH_THRESHOLD) + (U32)U16_ER_RefWert))
    /* polyspace < RTE:UNR : Not a defect : Justify with annotations> The condition is not redundant*/
    {
        U16_ER_Twert = U16_MAX_VALUE;
    }
    else
    {
        /*Set the  baseline by at least the threshold*/
        U16_ER_Twert = (U16_ER_RefWert + (U16)ST_unlock_sensor_NVM_params.U16_P_ER_APPROACH_THRESHOLD);
        /*some environmental condition caused the sensor to become stuck,to Prevent that the Sensor Baseline must be updated with a preventoffset (U16_ER_NOISE_SENSIVITY)*/
        Unlock_UpdateBaseline_by_noise();
        /*check if unlock Sensor reading is  crossed the baseline by at least the  threshold*/
        if (U16_ER_MeasValue > U16_ER_Twert) /* If reading has crossed the  threshold */
        /* polyspace < RTE:UNR : Not a defect : Justify with annotations> The condition is not redundant*/
        {
            Return_bo.approach = U8_SET_BIT;
        }
        else
        {
            /*do nothing*/
        }
    }
    /* polyspace < RTE:NIVL : Not a defect : Justify with annotations >  Return_bo it is initialized */
    /* polyspace < MISRA-C3:9.1 : Not a defect : Justify with annotations > Return_bo it is initialized */
    return (Return_bo); /*TT 09801*/
}
/*!
******************************************************************************
* \brief
* Lock_UpdateBaseline_by_noise
*
* \details
* @ingroup Decoding
*  add offset to the reference by noise detection
*  SWR-644, SWR-645
******************************************************************************
*
* \sync          synchronous (function done in one pass)
* \reent         non reentrant
*
* \pre           all must be initialized.
* \post          process is started
*
* \param[in]     void
* \param[in]
*
* \glob_start	 U16_VR_Rekcount        counter for baseline A new calculation,that  will occur every REF_VAL_COUNT lock_UpdateBaseline  call.
*                U16_VR_MeasValue;     final measurement value VR
*               U16_VR_RefWert        sensor baseline calculated in function lock_UpdateBaseline
* \glob_end
*
* \retval         void
******************************************************************************
*
* \author        Y.badal
* \version       1.0
* \date          14.03.2016
*
******************************************************************************
*
* \par Change history:
*       -
*
******************************************************************************
*
* \par Remarks:
* CallFunct:
*
******************************************************************************/
STATIC void Lock_UpdateBaseline_by_noise(void)
{

    if (U8_SET_BIT == Sensor_Bits.VR_Noiseflag_u1) /*check  Sensor Noise Flag from Sensor Analysing Funktion is set*/
    /* polyspace < RTE:UNR : Not a defect : Justify with annotations> The condition is not redundant*/
    {
        /* polyspace<MISRA-C3:D4.1 : Not a defect : Justify with annotations > "No Error: Checks at beginning of calling function Get_Vr_Approach_Detect make sure that overflow will not occur" */
        U16_VR_Twert += ST_lock_sensor_NVM_params.U16_P_VR_NOISE_OFFSET; /* Update the baseline with an equal */ /* polyspace RTE:OVFL [Not a defect:Low] "No Error: Checks at beginning of calling function Get_Vr_Approach_Detect make sure that overflow will not occur" */
        U16_VrNoiseOccurredCnt = U8_NULL;
    }
    else
    {
        if (ST_lock_sensor_NVM_params.U16_P_VR_NOISE_ACTIVE > U16_VrNoiseOccurredCnt)
        /* polyspace < RTE:UNR : Not a defect : Justify with annotations> The condition is not redundant*/
        {
            /* polyspace<MISRA-C3:D4.1 : Not a defect : Justify with annotations > "No Error: Checks at beginning of calling function Get_Vr_Approach_Detect make sure that overflow will not occur" */
            U16_VR_Twert += ST_lock_sensor_NVM_params.U16_P_VR_NOISE_OFFSET; /* Update the baseline with an equal */ /* polyspace RTE:OVFL [Not a defect:Low] "No Error: Checks at beginning of calling function Get_Vr_Approach_Detect make sure that overflow will not occur" */
            U16_VrNoiseOccurredCnt++;
        }
        else
        {
            /*do nothing*/
        }
    }
}
/*!
******************************************************************************
* \brief
* Get_Vr_Approach_Detect
*
* \details
* @ingroup Decoding
*  check if Sensor reading is  greater than the baseline  by at least the approach or TOUCH threshold
   NOTE: if a noise has occured the baseline will be updated with naoiseoffset
* SWR-467, SWR-468
******************************************************************************
*
* \sync          synchronous (function done in one pass)
* \reent         non reentrant
*
* \pre           all must be initialized.
* \post          process is started
*
* \param[in]     void
* \param[in]
*
* \glob_start	  U16_VR_MeasValue final measurement value ER from sensor modul
 *                U16_VR_Twert     sensor baseline calculated in this funktion
 *                U16_VR_RefWert   sensor baseline calculated in function Unlock_UpdateBaseline
* \glob_end
*
* \retval         BOOL_BITS_T Return_bo
 *                Bits approach or touch will be set if Sensor reading is  greater than the baseline
*
******************************************************************************
*
* \author        Y.badal
* \version       1.0
* \date          07.01.2015
*
******************************************************************************
*
* \par Change history:
*       -
*
******************************************************************************
*
* \par Remarks:
* CallFunct:
*
******************************************************************************/
STATIC BOOL_BITS_T Get_Vr_Approach_Detect(void)
{
    BOOL_BITS_T Return_bo;

    Return_bo.approach = U8_NULL;
    Return_bo.touch = U8_NULL;
    if ((U32)U16_MAX_VALUE <=
        (((U32)ST_lock_sensor_NVM_params.U16_P_VR_NOISE_OFFSET + (U32)ST_lock_sensor_NVM_params.U16_P_VR_TOUCH_THRESHOLD + (U32)ST_lock_sensor_NVM_params.U16_P_VR_APPROACH_THRESHOLD) + (U32)U16_VR_RefWert))
    {
        /* TT 09801*/
        U16_VR_Twert = U16_MAX_VALUE;
    }
    else
    {
        /*Set the  baseline by at least the threshold*/
        U16_VR_Twert = (U16)(U16_VR_RefWert + ST_lock_sensor_NVM_params.U16_P_VR_APPROACH_THRESHOLD + U8_VR_CrossTalk);
        /*some environmental condition caused the sensor to become stuck,to Prevent that the Sensor Baseline must be updated with a preventoffset (U16_ER_NOISE_SENSIVITY)*/
        Lock_UpdateBaseline_by_noise();
        /*check if unlock Sensor reading is  crossed the baseline by at least the  threshold*/
        if (U16_VR_MeasValue > U16_VR_Twert) /* If reading has crossed the  threshold */
        {
            Return_bo.approach = U8_SET_BIT;
        }
        else
        {
            /*do nothing*/
        }
        U16_VR_Touch_Threshold = U16_VR_RefWert + ST_lock_sensor_NVM_params.U16_P_VR_TOUCH_THRESHOLD;
        if (U16_VR_MeasValue > U16_VR_Twert + (ST_lock_sensor_NVM_params.U16_P_VR_TOUCH_THRESHOLD - ST_lock_sensor_NVM_params.U16_P_VR_APPROACH_THRESHOLD)) /* polyspace RTE:OVFL [Not a defect:Low] "No Error: Checks at beginning of function and in algo_check_parameters make sure that both overflow and underflow will not occur" */
        {
            Return_bo.touch = U8_SET_BIT;
            
        }
        else if (U8_VrDeactivationThresh != U8_NULL) /* verify if sensor was in TOUCH state */
        {

            U8_VrDeactivationThresh--;
        }
        else
        {
            /*do nothing*/
        }
    }
    return (Return_bo); /*TT 09801*/
}

/*!
******************************************************************************
* \brief
* Unlock_StateMachine_Idle
*
* \details
* @ingroup Decoding
*  function to handle sensor state in idle:  check if Sensor reading is  greater than the baseline
*  by at least the APPROACH threshold otherwise calculate a reference value
*  SWR-678
******************************************************************************
*
* \sync          synchronous (function done in one pass)
* \reent         non reentrant
*
* \pre           all must be initialized.
* \post          process is started
*
* \param[in]     BOOL_BITS_T BO_ErUnderThres Bits approach or touch has been setting if Sensor reading is  greater than the baseline
* \param[in]
*
* \glob_start	  EN_VR_AlgoStateSM        active-mode lock sensor states
*                 U8_Er_400ms_activation   approach und TOUCH activation  Counter
*                 Algo_State_Flags         Enumeration of the valid  active-mode sensor states
*                U16_er_as_entprell       debounce counter to be start by transiton to debounce state
* \glob_end
*
* \retval         void
*
******************************************************************************
*
* \author        Y.badal
* \version       1.0
* \date
*
******************************************************************************
*
* \par Change history:
*       -
*
******************************************************************************
*
* \par Remarks:
* CallFunct:
*
******************************************************************************/
STATIC void Unlock_StateMachine_Idle(BOOL_BITS_T BO_ErUnderThres)
{
    if (U8_SET_BIT == BO_ErUnderThres.approach) /*check if Sensor reading is  greater than the baseline  by at least the APPROACH threshold */
    /* polyspace < RTE:UNR : Not a defect : Justify with annotations> The condition is not redundant*/
    {
        U16_er_as_entprell = ST_unlock_sensor_NVM_params.U16_P_ER_DEBOUNCE; /* debounce counter is reset to the initial  debounce value and the baseline is frozen*/
        if (((U8_SET_BIT == Sensor_Bits.ER_Noiseflag_u1) || (ST_unlock_sensor_NVM_params.U16_P_ER_NOISE_ACTIVE > U16_ErNoiseOccurredCnt)) && (((U32)ST_unlock_sensor_NVM_params.U16_P_ER_NOISE_DEBOUNCE + (U32)ST_unlock_sensor_NVM_params.U16_P_ER_DEBOUNCE) <= (U32)U16_MAX))
        {
            U16_er_as_entprell += ST_unlock_sensor_NVM_params.U16_P_ER_NOISE_DEBOUNCE;
        }
        else
        {
            /*do nothing*/
        }
        /* decrement directly since one debounce will be done in any way*/
        /* polyspace<MISRA-C3:D4.1 : Not a defect : Justify with annotations > "No Error: DEBOUNCE_SAMPLE_TIME  is checked to be above zero by algo_check_parameters" */
        U16_er_as_entprell--;                         /* polyspace RTE:OVFL [Not a defect:Low] "No Error: DEBOUNCE_SAMPLE_TIME  is checked to be above zero by algo_check_parameters" */
        SET_ER_SENSOR_ALGO_STATE(EN_ASM_SX_DEBOUNCE); /*  Sensor is now Debounce State by falling through to line 512 (cheched in assembling code)*/
        (void)EcuM_RequestRUN(E_ECUM_ER_SENSOR);
    }
    else
    {
        (void)EcuM_ReleaseRUN(E_ECUM_ER_SENSOR);
    }
}
/*!
******************************************************************************
* \brief
* Unlock_check_debounce_time_done
*
* \details
* @ingroup Decoding
*
*  check if debounce time is done for unlock sensor
* SWR-450
******************************************************************************
*
* \sync          synchronous (function done in one pass)
* \reent         non reentrant
*
* \pre           all must be initialized.
* \post          process is started
*
* \param[in]     void
* \param[out]     void
*
* \glob_start
* \glob_end
*
* \retval         void
*
******************************************************************************
*
* \author        Y.badal
* \version       1.0
* \date
*
******************************************************************************
*
* \par Change history:
*       -
*
******************************************************************************
*
* \par Remarks:
* CallFunct:
*
******************************************************************************/
STATIC void Unlock_check_debounce_time_done(void)
{
    if ((U16)U8_NULL == U16_er_as_entprell) /* Debounce counter has reached 0*/
    {
        SET_ER_SENSOR_ALGO_STATE(EN_ASM_SX_APPROACH); /*set the next State Approach,the Sensor ist in the next Sample in Approach state*/
        U8_ErOffCounter = U8_NULL;                    /*Reset the Delay ,this is the Bebounce Counter to leaving the EN_ASM_SX_APPROACH  St*/
        U16_er_active_max_time = ST_unlock_sensor_NVM_params.U16_P_ER_TIMEOUT;
    }
    else
    {
        /* polyspace < RTE:OVFL : Not a defect : Justify with annotations >"The index is not outside of the boundaries and the operation will not result into an overflow." */
        U16_er_as_entprell--; /*decrement the Debounce Counter */
    }                         // TODO Discuss take over from VW380 project
}
/*!
******************************************************************************
* \brief
* Unlock_StateMachine_debounce
*
* \details
* @ingroup Decoding
*  function to handle sensor state  debounce: if the sensor is
******************************************************************************
*
* \sync          synchronous (function done in one pass)
* \reent         non reentrant
*
* \pre           all must be initialized.
* \post          process is started
*
* \param[in]     BOOL_BITS_T BO_ErUnderThres Bits approach or touch has been setting if Sensor reading is  greater than the baseline
* \param[in]
*
* \glob_start	  EN_VR_AlgoStateSM        active-mode lock sensor states
*                 U8_Er_400ms_activation   approach und TOUCH activation  Counter
*                 Algo_State_Flags         Enumeration of the valid  active-mode sensor states
* \glob_end
*
* \retval         void
*
******************************************************************************
*
* \author        Y.badal
* \version       1.0
* \date
*
******************************************************************************
*
* \par Change history:
*       -
*
******************************************************************************
*
* \par Remarks:
* CallFunct:
*
******************************************************************************/
STATIC void Unlock_StateMachine_debounce(BOOL_BITS_T BO_ErUnderThres)
{
    /*check if Sensor reading is still greater than the baseline by at least the APPROACH threshold ,if not debounce counter is reset to the initial  debounce value and the baseline is updated*/
    if (U8_SET_BIT == BO_ErUnderThres.approach)
    {
        Unlock_check_debounce_time_done();
    }
    else
    {
        RELOAD_ER_REF_VALUE();
        SET_ER_SENSOR_ALGO_STATE(EN_ASM_SX_IDLE); /*Set the Sensor State to Idle*/
    }
}


/*!
******************************************************************************
* \brief
* Unlock_reset_activation
*
* \details
* @ingroup Decoding
*
*  if maximale ontime has been expired or sensor is released,the Sw change to offdelay state
* SWR-492, SWR-494
******************************************************************************
*
* \sync          synchronous (function done in one pass)
* \reent         non reentrant
*
* \pre           all must be initialized.
* \post          process is started
*
* \param[in]     void
* \param[in]
*
* \glob_start	  U16_er_offdelay          offdelay debounce timer
*                 U8_Er_400ms_activation   approach und TOUCH activation  Counter
*                 Algo_State_Flags         Enumeration of the valid  active-mode sensor states
* \glob_end
*
* \retval         void
*
******************************************************************************
*
* \author        Y.badal
* \version       1.0
* \date
*
******************************************************************************
*
* \par Change history:
*       -
*
******************************************************************************
*
* \par Remarks:
* CallFunct:
*
******************************************************************************/
STATIC void Unlock_reset_activation(void)
{
    U8_ErOffCounter = 0u;
    SET_SENSOR_ALGO_RESULT(ER_APPROACH, U8_CLEAR_BIT); /*Reset sensor TOUCH signal*/
    SET_SENSOR_ALGO_RESULT(ER_TOUCH, U8_CLEAR_BIT); /*Reset sensor TOUCH signal*/
    RELOAD_ER_REF_VALUE(); /*  The baseline is reset to current reading for a quick recovery if some environmental condition caused the sensor to become stuck*/
    U16_er_offdelay = ST_unlock_sensor_NVM_params.U16_P_ER_OFFDELAY;
    SET_ER_SENSOR_ALGO_STATE(EN_ASM_SX_OFF_DELAY); /*set sensor state to Off_Delay*/
}
/*!
******************************************************************************
* \brief
* Unlock_check_ontime
*
* \details
* @ingroup Decoding
*
*  check if maximale ontime has been  expired.
* SWR-647
******************************************************************************
*
* \sync          synchronous (function done in one pass)
* \reent         non reentrant
*
* \pre           all must be initialized.
* \post          process is started
*
* \param[in]     void
* \param[in]
*
* \glob_start
* \glob_end
*
* \retval         void
*
******************************************************************************
*
* \author        Y.badal
* \version       1.0
* \date
*
******************************************************************************
*
* \par Change history:
*       -
*
******************************************************************************
*
* \par Remarks:
* CallFunct:
*
******************************************************************************/
STATIC void Unlock_check_ontime(void)
{
    if ((U16)U8_NULL == U16_er_active_max_time)
    {
        Unlock_reset_activation();
        RESET_ER_REF_VALUE(); /*hard reset of reference*/
    }
    else
    {
        /*do nothing*/
    }
}

/*!
******************************************************************************
* \brief
* Unlock_check_approach_deactivation_debounce
*
* \details
*  count the number of consecutive sensor reading wich are  smaller then approach threshold,
*  when the number exceed the parameter value we change to offdelay state.
******************************************************************************
*
* \sync          synchronous (function done in one pass)
* \reent         non reentrant
*
* \pre           all must be initialized.
* \post          process is started
*
* \param[in]     void
* \param[in]
*
* \glob_start
* \glob_end
*
* \retval         void
*
******************************************************************************
*
* \author        grovent
* \version       1.0
* \date
*
******************************************************************************
*
* \par Change history:
*       -
*
******************************************************************************
*
* \par Remarks:
* CallFunct:
*
******************************************************************************/
STATIC void Unlock_check_approach_deactivation_debounce(void)
{
    /*increment the APPROACH timer off counter */
    /* polyspace < RTE:OVFL : Not a defect : Justify with annotations >"The index is not outside of the boundaries and the operation will not result into an overflow." */
    /* polyspace < MISRA-C3:D4.1 : Not a defect : Justify with annotations >"The index is not outside of the boundaries and the operation will not result into an overflow." */
    U8_ErOffCounter++;

    /*the APPROACH timer off counter has running out */
    if (U16_er_deactivation_debounce < U8_ErOffCounter)
    {
        Unlock_reset_activation();
    }
    else
    {
        /* do nothing */
    }
}

/*!
******************************************************************************
* \brief
* Unlock_StateMachine_approach
*
* \details
* @ingroup Decoding
*  function to handle sensor state for approach
* SWR-489, SWR-490, SWR-450
******************************************************************************
*
* \sync          synchronous (function done in one pass)
* \reent         non reentrant
*
* \pre           all must be initialized.
* \post          process is started
*
* \param[in]     BOOL_BITS_T BO_ErUnderThres Bits approach or touch has been setting if Sensor reading is  greater than the baseline
* \param[in]
*
* \glob_start    U8_ErOffCounter            counter to debounce the approach state if the sensor reading is smaller then reference
*                 U8_Er_400ms_acti vation   approach und TOUCH activation  Counter
*                 Algo_State_Flags         Enumeration of the valid  active-mode sensor states
* \glob_end
*
* \retval         void
*
******************************************************************************
*
* \author        Y.badal
* \version       1.0
* \date
*
******************************************************************************
*
* \par Change history:
*       -
*
******************************************************************************
*
* \par Remarks:
* CallFunct:
*
******************************************************************************/
STATIC void Unlock_StateMachine_approach(BOOL_BITS_T BO_ErUnderThres)
{
    if ((U8_SET_BIT == BO_ErUnderThres.approach)) /*check if Sensor reading is still greater than the baseline by at least the APPROACH threshold*/
    {
		/*set  the Sensor approach bit*/
        SET_SENSOR_ALGO_RESULT(ER_APPROACH, U8_SET_BIT);
        U16_ER_FreezeCounter = 0u;
        /* check if the APPROACH timer counter has running out*/
        Unlock_check_ontime();
    }
    else /*Sensor reading is smaller than the baseline by at least the APPROACH threshold*/
    {
        Unlock_check_approach_deactivation_debounce();
    }
}

/*!
******************************************************************************
* \brief
* Unlock_StateMachine_offdelay
*
* \details
* @ingroup Decoding
*  function to handle sensor state for offdelay
*  SWR-493
******************************************************************************
*
* \sync          synchronous (function done in one pass)
* \reent         non reentrant
*
* \pre           all must be initialized.
* \post          process is started
*
* \param[in]     BOOL_BITS_T BO_ErUnderThres Bits approach or touch has been setting if Sensor reading is  greater than the baseline
* \param[in]
*
* \glob_start	  U16_er_offdelay          offdelay counter: when expired  when go back to idle state
*                 Algo_State_Flags         Enumeration of the valid  active-mode sensor states
* \glob_end
*
* \retval         void
*
******************************************************************************
*
* \author        Y.badal
* \version       1.0
* \date
*
******************************************************************************
*
* \par Change history:
*       -
*
******************************************************************************
*
* \par Remarks:
* CallFunct:
*
******************************************************************************/
/* polyspace < MISRA-C3:2.7 : Not a defect : Justify with annotations > Paremeter should be kept for future usage */
STATIC void Unlock_StateMachine_offdelay(BOOL_BITS_T BO_ErUnderThres)
{
    /* polyspace < RTE:OVFL : Not a defect : Justify with annotations >"The index is not outside of the boundaries and the operation will not result into an overflow." */
    /* polyspace < MISRA-C3:D4.1 : Not a defect : Justify with annotations >"The index is not outside of the boundaries and the operation will not result into an overflow." */
    U16_er_offdelay--; /*decrement offdelay timer counter */

    /*the offdelay timer counter has runing out*/
    if ((U16)U8_NULL == U16_er_offdelay)
    {
        SET_ER_SENSOR_ALGO_STATE(EN_ASM_SX_IDLE); /*set   sensor state to Idle */
    }
    else
    {
        /* do nothing */
    }
}

/*!
******************************************************************************
* \brief
* Unlock_StateMachine
*
* \details
* @ingroup Decoding
*
*   Updates the state of each active-mode sensor using the latest acquisition value
*
*   This is the  service routine that performs sensor state transitions based on the result
* of the function Get_Er_Approach_Detect
*
******************************************************************************
*
* \sync          synchronous (function done in one pass)
* \reent         non reentrant
*
* \pre           all must be initialized.
* \post          process is started
*
* \param[in]     void
* \param[out]    void
*
* \glob_start
* \glob_end
*
* \retval         void
*
******************************************************************************
*
* \author        Y.badal
* \version       1.0
* \date
*
******************************************************************************
*
* \par Change history:
*       -
*
******************************************************************************
*
* \par Remarks:
* CallFunct:
*
******************************************************************************/
STATIC void Unlock_StateMachine(void)
{
    /* Update the baseline threshold if measuered value is under freeze threshold */
    Capa_Algo_ER_Freeze_Handle();

    /* Check if touch or approach */
    BOOL_BITS_T BO_ErUnderThres = Get_Er_Approach_Detect();

    algo_decrement_unlock_activation_counter();
    /* algo state machine */
    switch (GET_ER_SENSOR_ALGO_STATE())
    {
    case EN_ASM_SX_IDLE:
    {
        Unlock_StateMachine_Idle(BO_ErUnderThres);
    }
    break;

        /*The two way to leave this state is by creating enough
         *consecutive positive shifts of the reading above the baseline to underflow the
         *#U16_er_as_entprell variable for the sensor1. Once this is done, the sensor will enter
         *the EN_ASM_SX_APPROACH state,and if not the Sensor Reset his Baseline und The State Machine set again to Idle */
        /* polyspace < RTE:UNR : Not a defect : Justify with annotations> The condition is not redundant*/
    case EN_ASM_SX_DEBOUNCE:
    {
        Unlock_StateMachine_debounce(BO_ErUnderThres);
        if (EN_ASM_SX_APPROACH == GET_ER_SENSOR_ALGO_STATE()) /* if debouncing is done, next check should be done directly not to loose an additional timestep*/
        {
            Unlock_StateMachine_approach(BO_ErUnderThres);
        }
        else
        {
            /* do nothing */
        }
    }
    break;

        /*A sensor can only enter this state from the #EN_ASM_SX_DEBOUNCE state, but there
         *are two ways to leave:
         *First, by being in the state for too long and allowing approach timer counter U16_er_as_entprell to
         *run out.
         *Second, by having a Sensor reading is smaller than the baseline by at least the approach threshold  on
         *enough consecutive scans to cause the debounce counter U8_ErOffCounter to reach U8_ER_OFF_DELAY_CONS. */
        /* polyspace < RTE:UNR : Not a defect : Justify with annotations> The condition is not redundant*/
    case EN_ASM_SX_APPROACH:
    {
        Unlock_StateMachine_approach(BO_ErUnderThres);
    }
    break;

        /*A sensor can only enter this state from the #EN_ASM_SX_APPROACH state, but there
         *are two ways to leave:
         *First, by being in the state until offdelay timer counter has runing out
         *Second, by having a Sensor reading is  greater than the baseline  by at least the APPROACH threshold  */
        /* polyspace < RTE:UNR : Not a defect : Justify with annotations> The condition is not redundant*/
    case EN_ASM_SX_OFF_DELAY:
    {
        Unlock_StateMachine_offdelay(BO_ErUnderThres);
    }
    break;
    /* polyspace < RTE:UNR : Not a defect : Justify with annotations> The condition is not redundant*/
    default:
    {
        U16_ER_FreezeCounter = 0u;
        SET_ER_SENSOR_ALGO_STATE(EN_ASM_SX_IDLE); /*set   sensor state to Idle */
    }
    break;
    }
}
/*!
******************************************************************************
* \brief
* Lock_StateMachine_Idle
*
* \details
* @ingroup Decoding
*  function to handle sensor state for idle
*  SWR-679
******************************************************************************
*
* \sync          synchronous (function done in one pass)
* \reent         non reentrant
*
* \pre           all must be initialized.
* \post          process is started
*
* \param[in]     BOOL_BITS_T BO_VrUnderThres Bits approach or touch has been setting if Sensor reading is  greater than the baseline
* \param[in]
*
* \glob_start	  EN_VR_AlgoStateSM        active-mode lock sensor states
*                 U8_Er_400ms_activation   approach und TOUCH activation  Counter
*                 Algo_State_Flags         Enumeration of the valid  active-mode sensor states
* \glob_end
*
* \retval         void
*
******************************************************************************
*
* \author        Y.badal
* \version       1.0
* \date
*
******************************************************************************
*
* \par Change history:
*       -
*
******************************************************************************
*
* \par Remarks:
* CallFunct:
*
******************************************************************************/
STATIC void Lock_StateMachine_Idle(BOOL_BITS_T BO_VrUnderThres)
{
    if (U8_SET_BIT == BO_VrUnderThres.approach) /*check if Sensor reading is  greater than the baseline  by at least the APPROACH threshold */
    /* polyspace < RTE:UNR : Not a defect : Justify with annotations> The condition is not redundant*/
    {
        U16_vr_as_entprell = ST_lock_sensor_NVM_params.U16_P_VR_DEBOUNCE; /* debounce counter is reset to the initial  debounce value and the baseline is frozen*/
        if (((U8_SET_BIT == Sensor_Bits.VR_Noiseflag_u1) || (ST_lock_sensor_NVM_params.U16_P_VR_NOISE_ACTIVE > U16_VrNoiseOccurredCnt)) && (((U32)ST_lock_sensor_NVM_params.U16_P_VR_NOISE_DEBOUNCE + (U32)ST_lock_sensor_NVM_params.U16_P_VR_DEBOUNCE) <= (U32)U16_MAX))
        {
            U16_vr_as_entprell += ST_lock_sensor_NVM_params.U16_P_VR_NOISE_DEBOUNCE;
        }
        else
        {
            /*do nothing*/
        }
        /* polyspace <MISRA-C3:D4.1 : Not a defect : Justify with annotations > "No Error: DEBOUNCE_SAMPLE_TIME  is checked to be above zero by algo_check_parameters" */
        U16_vr_as_entprell--; /* polyspace RTE:OVFL [Not a defect:Low] "No Error: DEBOUNCE_SAMPLE_TIME  is checked to be above zero by algo_check_parameters" */

        SET_VR_SENSOR_ALGO_STATE(EN_ASM_SX_DEBOUNCE); /*  Sensor is now Debounce State by falling through to line 732 (cheched in assembling code)*/
        (void)EcuM_RequestRUN(E_ECUM_VR_SENSOR);
    }
    else
    {
        (void)EcuM_ReleaseRUN(E_ECUM_VR_SENSOR);
    }
}

/*!
******************************************************************************
* \brief
* Lock_check_debounce_time_done
*
* \details
*  check if debounce time is done for lock sensor: after this time the approach state will be transmit to ecu.
* SWR-471, SWR-451
******************************************************************************
*
* \sync          synchronous (function done in one pass)
* \reent         non reentrant
*
* \pre           all must be initialized.
* \post          process is started
*
* \param[in]     void
* \param[in]
*
* \glob_start
* \glob_end
*
* \retval        void
*
******************************************************************************
*
* \author        Y.badal
* \version       1.0
* \date
*
******************************************************************************
*
* \par Change history:
*       -
*
******************************************************************************
*
* \par Remarks:
* CallFunct:
*
******************************************************************************/
STATIC void Lock_check_debounce_time_done(void)
{
    if ((U16)U8_NULL == U16_vr_as_entprell) /*Counter has reached 0*/
    {
        SET_VR_SENSOR_ALGO_STATE(EN_ASM_SX_APPROACH); /*set the next State Approach,the Sensor ist in the next Sample in Approach state*/
        U16_vr_active_max_time = ST_lock_sensor_NVM_params.U16_P_VR_TIMEOUT;
    }
    else
    {
        /* polyspace < RTE:OVFL : Not a defect : Justify with annotations >"The index is not outside of the boundaries and the operation will not result into an overflow." */
        U16_vr_as_entprell--; /*decrement the Debounce Counter */
    }
}
/*!
******************************************************************************
* \brief
* Lock_StateMachine_Debounce
*
* \details
* @ingroup Decoding
*  function to handle sensor state for debounce :
* during debounce
******************************************************************************
*
* \sync          synchronous (function done in one pass)
* \reent         non reentrant
*
* \pre           all must be initialized.
* \post          process is started
*
* \param[in]     BOOL_BITS_T BO_VrUnderThres Bits approach or touch has been setting if Sensor reading is  greater than the baseline
* \param[in]
*
* \glob_start	  EN_VR_AlgoStateSM        active-mode lock sensor states
*                 U16_VR_Rekcount           timer fo baseline calculation.
*                 Algo_State_Flags         Enumeration of the valid  active-mode sensor states
* \glob_end
*
* \retval         void
*
******************************************************************************
*
* \author        Y.badal
* \version       1.0
* \date
*
******************************************************************************
*
* \par Change history:
*       -
*
******************************************************************************
*
* \par Remarks:
* CallFunct:
*
******************************************************************************/
STATIC void Lock_StateMachine_Debounce(BOOL_BITS_T BO_VrUnderThres)
{
    /*check if Sensor reading is still greater than the baseline by at least the APPROACH threshold ,if not debounce counter is reset to the initial  debounce value and the baseline is updated*/
    if (U8_SET_BIT == BO_VrUnderThres.approach) /* ER-wert liegt unter der Ausl�seschwelle */
    {
        Lock_check_debounce_time_done();
        

    }
    else
    {
        RELOAD_VR_REF_VALUE();
        SET_VR_SENSOR_ALGO_STATE(EN_ASM_SX_IDLE); /*Set the Sensor State to Idle*/
    }
}
/*!
******************************************************************************
* \brief
* Lock_approach_timeout
*
* \details
* @ingroup Decoding
*
*  check if off debounce time is done for lock sensor: we change to idle state if the offdelay time has been expired.
* SWR-474, SWR-475, SWR-477
******************************************************************************
*
* \sync          synchronous (function done in one pass)
* \reent         non reentrant
*
* \pre           all must be initialized.
* \post          process is started
*
* \param[in]     void
* \param[out]     void
*
* \glob_start
* \glob_end
*
* \retval         void
*
******************************************************************************
*
* \author        Y.badal
* \version       1.0
* \date
*
******************************************************************************
*
* \par Change history:
*       -
*
******************************************************************************
*
* \par Remarks:
* CallFunct:
*
******************************************************************************/
STATIC void Lock_approach_timeout(void)
{
    SET_SENSOR_ALGO_RESULT(VR_APPROACH, U8_CLEAR_BIT); /*reset the Sensor Approach signal*/
    SET_SENSOR_ALGO_RESULT(VR_TOUCH, U8_CLEAR_BIT);
    RESET_VR_REF_VALUE();
    SET_VR_SENSOR_ALGO_STATE(EN_ASM_SX_IDLE); /* set sensor state to Idle*/
}
/*!
******************************************************************************
* \brief
* lock_reset_activation
*
* \details
* @ingroup Decoding
*
*  if maximale ontime is expired or sensor is released,the Sw change to offdelay state
* SWR-478
******************************************************************************
*
* \sync          synchronous (function done in one pass)
* \reent         non reentrant
*
* \pre           all must be initialized.
* \post          process is started
*
* \param[in]     void
* \param[in]
*
* \glob_start
* \glob_end
*
* \retval         void
*
******************************************************************************
*
* \author        Y.badal
* \version       1.0
* \date
*
******************************************************************************
*
* \par Change history:
*       -
*
******************************************************************************
*
* \par Remarks:
* CallFunct:
*
******************************************************************************/
STATIC void lock_reset_activation(void)
{
    /*Reset TOUCH timer off counter*/
    U8_VrOffCounter = 0u;
    SET_SENSOR_ALGO_RESULT(VR_TOUCH, U8_CLEAR_BIT); /*Reset sensor TOUCH signal*/
    SET_SENSOR_ALGO_RESULT(VR_APPROACH, U8_CLEAR_BIT);
    RESET_VR_REF_VALUE(); /*  The baseline is reset to current reading for a quick recovery if some environmental condition caused the sensor to become stuck*/
    U16_vr_offdelay = ST_lock_sensor_NVM_params.U16_P_VR_OFFDELAY;
    SET_VR_SENSOR_ALGO_STATE(EN_ASM_SX_OFF_DELAY); /*set sensor state to Off_Delay*/
}
/*!
******************************************************************************
* \brief
* Lock_check_Touch_deactivation_debounce
*
* \details
*  count the number of consecutive sensor reading wich are  smaller then touch threshold,
*  when the number exceed the parameter value we change to offdelay state.
******************************************************************************
*
* \sync          synchronous (function done in one pass)
* \reent         non reentrant
*
* \pre           all must be initialized.
* \post          process is started
*
* \param[in]     void
* \param[in]
*
* \glob_start
* \glob_end
*
* \retval         void
*
******************************************************************************
*
* \author        Y.badal
* \version       1.0
* \date
*
******************************************************************************
*
* \par Change history:
*       -
*
******************************************************************************
*
* \par Remarks:
* CallFunct:
*
******************************************************************************/
STATIC void Lock_check_Touch_deactivation_debounce(void)
{
    /*firstly, increment the TOUCH timer off counter to avoid one sample in addition in touch state */
    /* polyspace < RTE:OVFL : Not a defect : Justify with annotations >"The index is not outside of the boundaries and the operation will not result into an overflow." */
    /* polyspace < MISRA-C3:D4.1 : Not a defect : Justify with annotations >"The index is not outside of the boundaries and the operation will not result into an overflow." */
    U8_VrOffCounter++;

    /*the TOUCH timer off counter has running out */
    if (U16_vr_deactivation_debounce < U8_VrOffCounter)
    {
        lock_reset_activation();
    }
    else
    {
        /* do nothing */
    }
}
/*!
******************************************************************************
* \brief
* Lock_StateMachine_Approach
*
* \details
* @ingroup Decoding
*  function to handle sensor state for approach
*  SWR-469, SWR-472, SWR-477, SWR-446, SWR-451
******************************************************************************
*
* \sync          synchronous (function done in one pass)
* \reent         non reentrant
*
* \pre           all must be initialized.
* \post          process is started
*
* \param[in]     BOOL_BITS_T BO_VrUnderThres Bits approach or touch has been setting if Sensor reading is  greater than the baseline
* \param[in]
*
* \glob_start	  EN_VR_AlgoStateSM        active-mode lock sensor states
*                 U8_Er_400ms_activation   approach und TOUCH activation  Counter
*                 Algo_State_Flags         Enumeration of the valid  active-mode sensor states
* \glob_end
*
* \retval         void
*
******************************************************************************
*
* \author        Y.badal
* \version       1.0
* \date
*
******************************************************************************
*
* \par Change history:
*       -
*
******************************************************************************
*
* \par Remarks:
* CallFunct:
*
******************************************************************************/
STATIC void Lock_StateMachine_Approach(BOOL_BITS_T BO_VrUnderThres)
{
    /*set  the Sensor approach signal*/
    SET_SENSOR_ALGO_RESULT(VR_APPROACH, U8_SET_BIT); 
    U16_VR_FreezeCounter = 0u;

    if (((U16)U8_NULL == U16_vr_active_max_time) /*Timeout*/ || (U8_CLEAR_BIT == BO_VrUnderThres.approach))
    {
        /* the approach off counter has running out */
        Lock_approach_timeout();
    }
    else if (U8_SET_BIT == BO_VrUnderThres.touch) /*check if Sensor reading is  greater than the baseline by at least the TOUCH threshold*/
    {
        U8_VrOffCounter = (U8)U8_NULL;                     /* reset the approach timer off counter*/
        SET_VR_SENSOR_ALGO_STATE(EN_ASM_SX_TOUCH);         /* set the sensor state to TOUCH */
        SET_SENSOR_ALGO_RESULT(VR_APPROACH, U8_CLEAR_BIT); /*reset the Sensor approach signal*/
        SET_SENSOR_ALGO_RESULT(VR_TOUCH, U8_SET_BIT);      /*set  the Sensor TOUCH signal*/
    }
    else
    {
        /* do nothing */
    }
}


/*!
******************************************************************************
* \brief
* Lock_check_ontime
*
* \details
* @ingroup Decoding
*
*  we change to offdelay state if maximale ontime is expired:
* SWR-648
******************************************************************************
*
* \sync          synchronous (function done in one pass)
* \reent         non reentrant
*
* \pre           all must be initialized.
* \post          process is started
*
* \param[in]     void
* \param[out]     void
*
* \glob_start
* \glob_end
*
* \retval         void
*
******************************************************************************
*
* \author        Y.badal
* \version       1.0
* \date
*
******************************************************************************
*
* \par Change history:
*       -
*
******************************************************************************
*
* \par Remarks:
* CallFunct:
*
******************************************************************************/
STATIC void Lock_check_ontime(void)
{

    if ((U16)U8_NULL == U16_vr_active_max_time)
    {
        lock_reset_activation();
        RESET_VR_REF_VALUE(); /*hard reset of reference*/
    }
    else
    {
        /*do nothing*/
    }
}
/*!
******************************************************************************
* \brief
* Lock_StateMachine_Touch
*
* \details
* @ingroup Decoding
*  function to handle sensor state for touch
*  SWR-446
******************************************************************************
*
* \sync          synchronous (function done in one pass)
* \reent         non reentrant
*
* \pre           all must be initialized.
* \post          process is started
*
* \param[in]     BOOL_BITS_T BO_VrUnderThres Bits approach or touch has been setting if Sensor reading is  greater than the baseline
* \param[in]
*
* \glob_start
* \glob_end
*
* \retval         void
*
******************************************************************************
*
* \author        Y.badal
* \version       1.0
* \date
*
******************************************************************************
*
* \par Change history:
*       -
*
******************************************************************************
*
* \par Remarks:
* CallFunct:
*
******************************************************************************/
STATIC void Lock_StateMachine_Touch(BOOL_BITS_T BO_VrUnderThres)
{
    /*check if Sensor reading is still greater than the baseline by at least the TOUCH threshold*/
    if (U8_SET_BIT == BO_VrUnderThres.touch)
    {
        U8_VrDeactivationThresh = (U8)U16_vr_deactivation_debounce;
        SET_SENSOR_ALGO_RESULT(VR_TOUCH, U8_SET_BIT); /*set  the Sensor approach signal*/
        
        /*the TOUCH timer counter has runing out*/
        Lock_check_ontime();
    }
    else /*Sensor reading is smaller than the baseline by at least the TOUCH threshold*/
    {
        /*the TOUCH timer off counter has running out */
        Lock_check_Touch_deactivation_debounce();
    }
}
/*!
******************************************************************************
* \brief
* Lock_StateMachine_Offdelay
*
* \details
* @ingroup Decoding
*  function to handle sensor state for offdelay
*  SWR-476
******************************************************************************
*
* \sync          synchronous (function done in one pass)
* \reent         non reentrant
*
* \pre           all must be initialized.
* \post          process is started
*
* \param[in]     BOOL_BITS_T BO_VrUnderThres Bits approach or touch has been setting if Sensor reading is  greater than the baseline
* \param[in]
*
* \glob_start	  EN_VR_AlgoStateSM        active-mode lock sensor states
*                 U16_vr_offdelay          time to leave the offdelay state
*                 Algo_State_Flags         Enumeration of the valid  active-mode sensor states
* \glob_end
*
* \retval         void
*
******************************************************************************
*
* \author        Y.badal
* \version       1.0
* \date
*
******************************************************************************
*
* \par Change history:
*       -
*
******************************************************************************
*
* \par Remarks:
* CallFunct:
*
******************************************************************************/
/* polyspace < MISRA-C3:2.7 : Not a defect : Justify with annotations > Paremeter should be kept for future usage */
STATIC void Lock_StateMachine_Offdelay(BOOL_BITS_T BO_VrUnderThres)
{
    /* polyspace < RTE:OVFL : Not a defect : Justify with annotations >"The index is not outside of the boundaries and the operation will not result into an overflow." */
    /* polyspace < MISRA-C3:D4.1 : Not a defect : Justify with annotations >"The index is not outside of the boundaries and the operation will not result into an overflow." */
    U16_vr_offdelay--; /*decrement offdelay timer counter */

    /*the offdelay timer counter has runing out*/
    if ((U16)U8_NULL == U16_vr_offdelay)
    {
        SET_VR_SENSOR_ALGO_STATE(EN_ASM_SX_IDLE); /*set sensor state to Idle */
    }
    else
    {
        /* do nothing */
    }
}
/*!
******************************************************************************
* \brief
* Lock_StateMachine
*
* \details
*  Updates the state of each active-mode sensor using the latest acquisition value
*
*   This is the  service routine that performs sensor state transitions based on the result
* of the function Get_Vr_Approach_Detect
******************************************************************************
*
* \sync          synchronous (function done in one pass)
* \reent         non reentrant
*
* \pre           all must be initialized.
* \post          process is started
*
* \param[in]     void
* \param[out]    void
*
* \glob_start	  EN_VR_AlgoStateSM active-mode unlock sensor states
* \glob_end
*
* \retval         BOOL
*
******************************************************************************
*
* \author        Y.badal
* \version       1.0
* \date
*
******************************************************************************
*
* \par Change history:
*       -
*
******************************************************************************
*
* \par Remarks:
* CallFunct:
*
******************************************************************************/
STATIC void Lock_StateMachine(void)
{

    update_VR_threshold_crosstalk();

    /* Update the baseline threshold if measuered value is under freeze threshold */
    Capa_Algo_VR_Freeze_Handle();

    /* Check if touch or approach */
    BOOL_BITS_T BO_VrUnderThres = Get_Vr_Approach_Detect();

    algo_decrement_lock_activation_counter();

    /* algo state machine */
    switch (GET_VR_SENSOR_ALGO_STATE())
    {
    case EN_ASM_SX_IDLE:
    {
        Lock_StateMachine_Idle(BO_VrUnderThres);
    }
    break;

        /*The two way to leave this state is by creating enough
         *consecutive positive shifts of the reading above the baseline to underflow the
         *#U16_vr_as_entprell variable for the sensor. Once this is done, the sensor will enter
         *the EN_ASM_SX_APPROACH state,and if not the Sensor Reset his Baseline and The State Machine set again to Idle */
        /* polyspace < RTE:UNR : Not a defect : Justify with annotations> The condition is not redundant*/
    case EN_ASM_SX_DEBOUNCE:
    {
        Lock_StateMachine_Debounce(BO_VrUnderThres);
        if (EN_ASM_SX_APPROACH == GET_VR_SENSOR_ALGO_STATE()) /* if debouncing is done, next check should be done directly not to loose an additional timestep*/
        {
            Lock_StateMachine_Approach(BO_VrUnderThres);
        }
        else
        {
            /* do nothing */
        }
    }
    break;

        /*A sensor can only enter this state from the #EN_ASM_SX_DEBOUNCE state, but there
         *are two ways to leave:
         *First, by being in the state for too long and allowing approach timer counter U16_vr_as_entprell to
         *run out.
         *Second, by having a Sensor reading is smaller than the baseline by at least the approach threshold  on
         *enough consecutive scans to cause the debounce counter U8_VrOffCounter to reach U8_VR_OFF_DELAY_CONS. */
        /* polyspace < RTE:UNR : Not a defect : Justify with annotations> The condition is not redundant*/
    case EN_ASM_SX_APPROACH:
    {
        Lock_StateMachine_Approach(BO_VrUnderThres);
    }
    break;

        /*A sensor can only enter this state from the #EN_ASM_SX_APPROACH state, but there
         *are two ways to leave:
         *First, by being in the state for too long and allowing the TOUCH timer U16_VRMaxOnzeit to
         *run out.
         *Second, by having a Sensor reading is smaller than the baseline by at least the TOUCH threshold  on
         *enough consecutive scans to cause the debounce counter U8_VrOffCounter to reach U8_VR_OFF_DELAY_CONS. */
        /* polyspace < RTE:UNR : Not a defect : Justify with annotations> The condition is not redundant*/
    case EN_ASM_SX_TOUCH:
    {
        Lock_StateMachine_Touch(BO_VrUnderThres);
    }
    break;

        /*A sensor can only enter this state from the #EN_ASM_SX_TOUCH state, but there
         *are two ways to leave:
         *First, by being in the state until offdelay timer counter has runing out
         *Second, by having a Sensor reading is  greater than the baseline  by at least the APPROACH threshold  */
        /* polyspace < RTE:UNR : Not a defect : Justify with annotations> The condition is not redundant*/
    case EN_ASM_SX_OFF_DELAY:
    {
        Lock_StateMachine_Offdelay(BO_VrUnderThres);
    }
    break;
    /* polyspace < RTE:UNR : Not a defect : Justify with annotations> The condition is not redundant*/
    default:
    {
        U16_VR_FreezeCounter = 0u;
        SET_VR_SENSOR_ALGO_STATE(EN_ASM_SX_IDLE); /*set   sensor state to Idle */
    }
    break;
    }
}

/*********************************************************************************************************
+ *  Name                   : update_VR_threshold_crosstalk
+ *  Description            : check if open is active
+ *                         : 
+ *  Parameters             : 
+ *  Return                 :
+ *  Critical/explanation   : -
+ *  Author                 : 
+ *********************************************************************************************************/
STATIC void update_VR_threshold_crosstalk(void)
{
    if ((EN_ASM_SX_DEBOUNCE == EN_ER_AlgoStateSM) || (EN_ASM_SX_APPROACH == EN_ER_AlgoStateSM) || (U8_Inductive_Algo_Valid_Touch == 1u))
    {
        U8_VR_CrossTalk = (U8)LOCK_CROSSTALK_THRESHOLD;
    } else
    {
        U8_VR_CrossTalk = 0u;
    }
}


/*********************************************************************************************************
 *  Name                   : isAlgoActive
 *  Description            : Verify is any sensor is active
 *                         :
 *  Parameters             : none
 *  Return                 : BOOL
 *  Critical/explanation   : -
 *  Author                 :
 *********************************************************************************************************/
/* polyspace < MISRA-C3:8.7,8.8 : Not a defect : Justify with annotations > External Usage dependent on project setup*/
boolean isAlgoActive(void)
{
    BOOL boAlgo = FALSE;
    /* polyspace < MISRA-C3:13.5 : Not a defect : Justify with annotations> the operands are different conditions*/
    if (((TRUE == boIsCapaActive()) ||
         /* polyspace < MISRA-C3:8.3,8.5 : Not a defect : Justify with annotations > Function use the same names and type */
         /* polyspace < MISRA-C3:10.5 : Not a defect : Justify with annotations > Will return only 0 and 1*/
         /* polyspace < MISRA-C3:17.3 : Not a defect : Justify with annotations > Function prototype is already declared.*/
         ((BOOL)TRUE == (BOOL)boIsInductiveActive())) && /* polyspace < RTE:UNR : Not a defect : Justify with annotations> The condition is not redundant*/
        (BatSup_isVoltageInNormal() != 0U ))
    /* polyspace < RTE:UNR : Not a defect : Justify with annotations> The condition is not redundant*/
    {
        boAlgo = TRUE;
    }
    else
    {
        /*do nothing*/
    }
    return boAlgo;
}

/*!
******************************************************************************
* \brief
* get_sensor_algo_state_result
*
* \details
*  return  Sensor algo result : this represent the powerline state(approach, touch)
******************************************************************************
*
* \sync          synchronous (function done in one pass)
* \reent         non reentrant
*
* \pre           all must be initialized.
* \post          process is started
*
* \param[in]     void
* \param[in]
*
* \glob_start
* \glob_end
*
* \retval         U8 Algo_State_Flags.U8_Byte :
*
******************************************************************************
*
* \author        Y.badal
* \version       1.0
* \date          07.01.2015
*
******************************************************************************
*
* \par Change history:
*       -
*
******************************************************************************
*
* \par Remarks:
* CallFunct:
*
******************************************************************************/
void get_sensor_algo_state_result(U8 *U8_algo_state_arg)
{
    if (U8_algo_state_arg != NULL)
    {
        *U8_algo_state_arg = Algo_State_Flags.U8_Algo_Byte;
    }
    else
    {
        /*do nothing*/
    }
}

void Algo_getErState(U8 *U8_algoState)
{
    if (U8_algoState != NULL)
    {
        *U8_algoState = Algo_State_Flags._Algo_Bit.ER_Approach_u1;
    }
    else
    {
        /*do nothing*/
    }
}

void Algo_getVrState(U8 *U8_algoState)
{
    if (U8_algoState != NULL)
    {
        *U8_algoState = Algo_State_Flags._Algo_Bit.VR_Approach_u1 | Algo_State_Flags._Algo_Bit.VR_TOUCH_u1;
    }
    else
    {
        /*do nothing*/
    }
}
/*!
******************************************************************************
* \brief
* get_sensor_algo_SM_NotIdle
*
* \details
*  return  true if Sensor algo result state machines(unlock and lock) not idle ist.
******************************************************************************
*
* \sync          synchronous (function done in one pass)
* \reent         non reentrant
*
* \pre           all must be initialized.
* \post          process is started
*
* \param[in]     void
* \param[in]
*
* \glob_start
* \glob_end
*
* \retval         BOOL  : TRUE,FALSE
*
******************************************************************************
*
* \author        Y.badal
* \version       1.0
* \date          07.01.2015
*
******************************************************************************
*
* \par Change history:
*       -
*
******************************************************************************
*
* \par Remarks:
* CallFunct:
*
******************************************************************************/
BOOL get_sensor_algo_SM_NotIdle(void)
{
    BOOL BO_algo_state_SM = FALSE;
    if (GET_VR_SENSOR_ALGO_STATE() != EN_ASM_SX_IDLE)
    {
        BO_algo_state_SM = TRUE;
    }
    else
    {
        /*do nothing*/
    }
    if (GET_ER_SENSOR_ALGO_STATE() != EN_ASM_SX_IDLE)
    {
        BO_algo_state_SM = TRUE;
    }
    else
    {
        /*do nothing*/
    }
    return BO_algo_state_SM;
}

/*needed to test the algo*/
/*------------------------------------------------------------------------
 Function      : EcuM_lock_sensor_blocking
 Description   : get true if lock sensor shall be blocked in case of 72 h ,or nfc is active
 Return        : BOOL : true :false
 ------------------------------------------------------------------------*/
/* polyspace <MISRA-C3:8.7: Not a defect : Justify with annotations > External Usage dependent on project setup*/
BOOL EcuM_lock_sensor_blocking(void)
{
    BOOL response = FALSE;
    U8 sigVal = 0u;
    //(void)Com_ReceiveSignal(ComConf_ComSignal_SI_T_Mode_XIX_Systeminfo_01_XIX_HCP4_CANFD01_16d86291_Rx, &sigVal);
    /* If ESM mode is active and ESM mode is enabled for lock sensor OR if transport mode is ON */
    //if ((((ST_AUDI_NVM_params.U8_Byte_2_Audi_param_NVM & MASK_FOR_cp_ESMdisableKessy) == MASK_FOR_cp_ESMdisableKessy)) || (1u == sigVal)) {
    //    response = TRUE;
    //}
    return response;
}

/*------------------------------------------------------------------------
 Function      : EcuM_unlock_sensor_blocking
 Description   : get true if lock sensor shall be blocked in case of 72 h ,or nfc is active
 Return        : BOOL : true :false
 ------------------------------------------------------------------------*/
/* polyspace <MISRA-C3:8.7: Not a defect : Justify with annotations > External Usage dependent on project setup*/
BOOL EcuM_unlock_sensor_blocking(void)
{
    return FALSE;
}
