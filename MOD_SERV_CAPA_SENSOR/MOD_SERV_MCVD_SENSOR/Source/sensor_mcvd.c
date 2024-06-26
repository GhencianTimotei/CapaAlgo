#ifndef SENSOR_MCVD_C
#define SENSOR_MCVD_C

#include "Platform_Types.h"
#include "sensor_algo.h"
#include "Os.h"


#include "sensor_aquisition.h"
#include "sensor_mcvd.h"
#include "NvmMng.h"


/* DC values for UNLOCK (ER)/LOCK (VR) filter */
U16 U16_ER_filter_dfc;
U16 U16_VR_filter_dfc;

#define U16_IIR_WARME_UP_CONSTANT_NOISE ST_unlock_sensor_NVM_params.U16_P_CARRIER_VALUE

typedef void (*FILTER_FUNC)(TASK_SENSOR_VAR_T * Sensor_Var,U16 NewSample_u16);
typedef SENSOR_MEASURE_VALUE_T* (*SCAN_SENSOR_FUNC)(void);
typedef void (*NOISE_DET_FUNC)(TASK_SENSOR_VAR_T * Sensor_Var,U16 NewSample_u16);

typedef  struct
{

    EN_SENSOR_ID   SensorID_EN; /*sensor id */
    FILTER_FUNC fnc_filter; /* function pointer to the sensor filter  */
    NOISE_DET_FUNC fnc_noiseDet; /* function pointer to the noise detector */
    SCAN_SENSOR_FUNC fnc_get_sensor_aquis ;/* function pointer to the get values sensor aquisiton interface*/
    U8 U8_filter_fill_init; /* window for filter warm up  */
    U8 U8_filter_init_recall; /* number of filter call during init time */

}SENSOR_PARAMETER_T;

TASK_SENSOR_VAR_T   Sensor_Var_Str[SENSOR_MAX]; /*! sensor  main structur  content the variables for each sensor used from the sensor module.*/
STATIC READONLY SENSOR_PARAMETER_T   ST_sensor_unit_par[SENSOR_MAX] ;

#define U8_LOCK_FILTER_FILL_LOOP    ((U8)3)
#define U8_UNLOCK_FILTER_FILL_LOOP  ((U8)3)
#define U8_LOCK_FILTER_INIT_RECALL    ((U8)4)
#define U8_UNLOCK_FILTER_INIT_RECALL  ((U8)4)

#define  U16_SAMPLEA_INIT_VALUE                  ((U16)647)
#define  U16_SAMPLEB_INIT_VALUE                  ((U16)376)

/* noise detector */
STATIC void sensor_noise_detect(TASK_SENSOR_VAR_T * Sensor_Var,U16 U16_filter_input);
STATIC void sensor_filter_unit(READONLY SENSOR_MEASURE_VALUE_T * sensor_raw_buffer,TASK_SENSOR_VAR_T * Sensor_Var);
STATIC void sensor_filter_unit_LP(READONLY SENSOR_MEASURE_VALUE_T * sensor_raw_buffer,TASK_SENSOR_VAR_T * Sensor_Var);
STATIC void sensor_unlock_iir_filter (TASK_SENSOR_VAR_T * Sensor_Var,U16 U16_filter_input);
STATIC void sensor_lock_iir_filter (TASK_SENSOR_VAR_T * Sensor_Var,U16 U16_filter_input);
/******************************************************************************/

/*stores general informations about each of the active sensors:
* sensor id, function pointer to sensor filter, function pointer to sensor aquisition, pon fill loop, pon filter recall  */
STATIC READONLY SENSOR_PARAMETER_T   ST_sensor_unit_par[SENSOR_MAX] = {
                                                                          #ifndef VARIANT_1
                                                                            {SENSOR_LOCK,&sensor_lock_iir_filter,&sensor_noise_detect,&Get_Sensor_Scan_VR,U8_LOCK_FILTER_FILL_LOOP,U8_LOCK_FILTER_INIT_RECALL},
                                                                          #endif
                                                                            {SENSOR_UNLOCK,&sensor_unlock_iir_filter,&sensor_noise_detect,&Get_Sensor_Scan_ER,U8_UNLOCK_FILTER_FILL_LOOP,U8_UNLOCK_FILTER_INIT_RECALL}
                                                                          };

STATIC inline void sensor_sampleAB_init(void)
{
    U8 sensor_id;

    SuspendAllInterrupts();
    Sensor_Scan_Both();/*call sensor aquisition*/
    ResumeAllInterrupts();
    for( sensor_id = (U8)0 ;sensor_id < (U8)SENSOR_MAX;sensor_id +=(U8)1)
    {
      AU_sensor_raw_buffer[sensor_id] = ST_sensor_unit_par[sensor_id].fnc_get_sensor_aquis(); /*get sensor aquisition result*/
      Sensor_Var_Str[sensor_id].U16_last_sampleA = AU_sensor_raw_buffer[sensor_id]->U16_Sensor_SA_Value; /* initialize th lock Sample (A-1)*/
      Sensor_Var_Str[sensor_id].U16_last_sampleB = AU_sensor_raw_buffer[sensor_id]->U16_Sensor_SB_Value; /* initialize th lock Sample (B-1)*/
    }
    

}
REF_SENSOR void sensor_mcvd_init(void)
{
    U8 sensor_id ;
    U8  U8_power_up_loop ;

    for( sensor_id = 0u ;sensor_id < (U8)SENSOR_MAX;sensor_id +=1u)
    {
    
      /*! initialization  of sensor id */
      Sensor_Var_Str[sensor_id].en_sensor_id = (EN_SENSOR_ID) sensor_id;
      
      /*explicit initialization of filter memory*/
      Sensor_Var_Str[sensor_id].S32_Filt_FeedbackBuffer[MEMORY_DEPTH_1]=0;
      Sensor_Var_Str[sensor_id].S32_Filt_FeedbackBuffer[MEMORY_DEPTH_2]=0;
      Sensor_Var_Str[sensor_id].S16_NoiseDet_FeedbackBuffer[MEMORY_DEPTH_1]=0;
      Sensor_Var_Str[sensor_id].S16_NoiseDet_FeedbackBuffer[MEMORY_DEPTH_2]=0;

    }

     Sensor_Var_Str[SENSOR_UNLOCK].U16_NoiseThresh = ST_unlock_sensor_NVM_params.U16_P_ER_NOISE_THRESHOLD;
     Sensor_Var_Str[SENSOR_LOCK].U16_NoiseThresh = ST_lock_sensor_NVM_params.U16_P_VR_NOISE_THRESHOLD;

   /*first sensor sample initialisation */
    sensor_sampleAB_init();

    /* initialisation of the filter with constant value for all active sensors*/
    for( sensor_id = (U8)0 ;sensor_id < (U8)SENSOR_MAX;sensor_id +=(U8)1)
    {
        for( U8_power_up_loop = (U8)0;U8_power_up_loop < ST_sensor_unit_par[sensor_id].U8_filter_fill_init;U8_power_up_loop++)
        {
          ST_sensor_unit_par[sensor_id].fnc_filter(&Sensor_Var_Str[sensor_id],U16_IIR_WARME_UP_CONSTANT);/*call the filter function for each sensor*/
          (void)ST_sensor_unit_par[sensor_id].fnc_noiseDet(&Sensor_Var_Str[sensor_id],U16_IIR_WARME_UP_CONSTANT_NOISE);/*call the noise detect function for each sensor*/
        }
    } 
}


REF_SENSOR void sensor_perform_OnInit(void)
{
U8 U8_power_up_loop = (U8)0;    
U8 sensor_id;

    SuspendAllInterrupts();
    Sensor_Scan_Both();/*call sensor aquisition*/
    ResumeAllInterrupts();

    for( sensor_id = (U8)0 ;sensor_id < (U8)SENSOR_MAX;sensor_id +=(U8)1)
    {
        AU_sensor_raw_buffer[sensor_id] = ST_sensor_unit_par[sensor_id].fnc_get_sensor_aquis(); /*get sensor aquisition result*/
    }

    /* perform OnInit for unlock sensor - 3x measured value */
    sensor_filter_unit(AU_sensor_raw_buffer[SENSOR_UNLOCK],&Sensor_Var_Str[SENSOR_UNLOCK]);/* call consecutive filter unit*/
    (void)ST_sensor_unit_par[SENSOR_UNLOCK].fnc_noiseDet(&Sensor_Var_Str[SENSOR_UNLOCK],AU_sensor_raw_buffer[SENSOR_UNLOCK]->U16_Sensor_SB_Value);/*call the noise detect function for each sensor*/

   /* perform OnInit for lock sensor - 3x measured value * 4 times per measured value */
    for( U8_power_up_loop = (U8)0;((U8_power_up_loop < ST_sensor_unit_par[SENSOR_LOCK].U8_filter_init_recall)&&((BOOL)FALSE == BO_LF_Signal_detected));U8_power_up_loop++)
    {
        sensor_filter_unit(AU_sensor_raw_buffer[SENSOR_LOCK],&Sensor_Var_Str[SENSOR_LOCK]);/* call consecutive filter unit*/
        (void)ST_sensor_unit_par[SENSOR_LOCK].fnc_noiseDet(&Sensor_Var_Str[SENSOR_LOCK],AU_sensor_raw_buffer[SENSOR_LOCK]->U16_Sensor_SB_Value);/*call the noise detect function for each sensor*/
    }
}
REF_SENSOR void sensor_perform_acquisition_filter(EN_SENSOR_MODE mode)
{
U8 sensor_id;

    
    for( sensor_id = (U8)0 ;((sensor_id < (U8)SENSOR_MAX) && ((BOOL)FALSE == BO_LF_Signal_detected ));sensor_id +=(U8)1)
    {

			AU_sensor_raw_buffer[sensor_id] = ST_sensor_unit_par[sensor_id].fnc_get_sensor_aquis(); /*get sensor aquisition result*/
            if (EN_LOWPOWER_SENSOR_MODE == mode)
            {
                /* If we are in Low power mode call filter unit twice. */
                sensor_filter_unit_LP(AU_sensor_raw_buffer[sensor_id],&Sensor_Var_Str[sensor_id]);/* call  filter unit*/
            } else{
                sensor_filter_unit(AU_sensor_raw_buffer[sensor_id],&Sensor_Var_Str[sensor_id]);/* call  filter unit*/
            }
			ST_sensor_unit_par[sensor_id].fnc_noiseDet(&Sensor_Var_Str[sensor_id],AU_sensor_raw_buffer[sensor_id]->U16_Sensor_SB_Value);/*call the noise detect function for each sensor*/

			U16_ER_MeasValue = Sensor_Var_Str[SENSOR_UNLOCK].U16_filter_unit_result;/*calculate a new average that will be the result to the sigma delta and algo*/
            U16_VR_MeasValue = Sensor_Var_Str[SENSOR_LOCK].U16_filter_unit_result;/*calculate a new average that will be the result to the sigma delta and algo*/
            Sensor_Bits.ER_Noiseflag_u1 = (U8)Sensor_Var_Str[SENSOR_UNLOCK].BO_noise_detected;
            Sensor_Bits.VR_Noiseflag_u1 = (U8)Sensor_Var_Str[SENSOR_LOCK].BO_noise_detected;


    }

}

STATIC void sensor_filter_unit(READONLY SENSOR_MEASURE_VALUE_T * sensor_raw_buffer,TASK_SENSOR_VAR_T * Sensor_Var)
{
    U16 U16_dc_filter_input;
    U16 Temp_SampleA;
    U16 Temp_SampleB;
 
    /*preselector*/   
    Temp_SampleA = sensor_raw_buffer[0].U16_Sensor_SA_Value;                    /*get current sample A */
    Temp_SampleB = sensor_raw_buffer[0].U16_Sensor_SB_Value;            /*get current sample B */

    Temp_SampleA += ST_unlock_sensor_NVM_params.U16_P_CARRIER_VALUE;
   
    Sensor_Var->U16_last_sampleA = sensor_raw_buffer[0].U16_Sensor_SA_Value;    /* save current values for next cycle */ 
    Sensor_Var->U16_last_sampleB = sensor_raw_buffer[0].U16_Sensor_SB_Value;   
    
    if(Temp_SampleA >= Temp_SampleB)
    {
        U16_dc_filter_input = Temp_SampleA - Temp_SampleB;   /*! calculate DC value*/
    }
    else
    {
    	U16_dc_filter_input = Temp_SampleB - Temp_SampleA;
    }

  
    if(SENSOR_UNLOCK == Sensor_Var->en_sensor_id)
    {
        U16_ER_filter_dfc = U16_dc_filter_input;
    }
    else
    {
        U16_VR_filter_dfc = U16_dc_filter_input;
    }
    ST_sensor_unit_par[Sensor_Var->en_sensor_id].fnc_filter(Sensor_Var, U16_dc_filter_input ); /* call  filter function for each sensor  */  

}

STATIC void sensor_filter_unit_LP(READONLY SENSOR_MEASURE_VALUE_T * sensor_raw_buffer,TASK_SENSOR_VAR_T * Sensor_Var)
{
    U16 U16_dc_filter_input;
    U16 Temp_SampleA;
    U16 Temp_SampleB;
 
    /*preselector*/   
    Temp_SampleA = sensor_raw_buffer[0].U16_Sensor_SA_Value;                    /*get current sample A */
    Temp_SampleB = sensor_raw_buffer[0].U16_Sensor_SB_Value;            /*get current sample B */

    Temp_SampleA += ST_unlock_sensor_NVM_params.U16_P_CARRIER_VALUE;
   
    Sensor_Var->U16_last_sampleA = sensor_raw_buffer[0].U16_Sensor_SA_Value;    /* save current values for next cycle */ 
    Sensor_Var->U16_last_sampleB = sensor_raw_buffer[0].U16_Sensor_SB_Value;   
    
    if(Temp_SampleA >= Temp_SampleB)
    {
        U16_dc_filter_input = Temp_SampleA - Temp_SampleB;   /*! calculate DC value*/
    }
    else
    {
    	U16_dc_filter_input = Temp_SampleB - Temp_SampleA;
    }

  
    if(SENSOR_UNLOCK == Sensor_Var->en_sensor_id)
    {
        U16_ER_filter_dfc = U16_dc_filter_input;
    }
    else
    {
        U16_VR_filter_dfc = U16_dc_filter_input;
    }
    ST_sensor_unit_par[Sensor_Var->en_sensor_id].fnc_filter(Sensor_Var, U16_dc_filter_input ); /* call  filter function for each sensor  */  
    ST_sensor_unit_par[Sensor_Var->en_sensor_id].fnc_filter(Sensor_Var, U16_dc_filter_input ); /* call  filter function for each sensor  */
}



STATIC void sensor_unlock_iir_filter (TASK_SENSOR_VAR_T * Sensor_Var,U16 U16_filter_input)
{  
    S32 S32_FeedbackSum;
    U16 U16_ShiftTemp;
    U32 U32_ShiftTemp;

    S32* PS32_ptr_FeedBack = Sensor_Var->S32_Filt_FeedbackBuffer;/*get feedback buffer pointer*/

    /* B0 = 1; A0=1*/
    S32_FeedbackSum=(S32)U16_filter_input + PS32_ptr_FeedBack[CASCADE_LEVEL1];
    /* make sure output does not overflow*/
    if(0 > S32_FeedbackSum)
    {
        Sensor_Var->U16_filter_unit_result = 0;
    }
    else if((S32)U16_MAX < S32_FeedbackSum)
    {
        Sensor_Var->U16_filter_unit_result = U16_MAX;
    }
    else
    {
        Sensor_Var->U16_filter_unit_result = (U16)S32_FeedbackSum;
    }

    /* B1 = 2 */
    U32_ShiftTemp = ((U32)U16_filter_input)<<1u;
    PS32_ptr_FeedBack[CASCADE_LEVEL1] = (S32)U32_ShiftTemp;
    /* A1 = 0.625 =  1/2+ 1/8  */
    U16_ShiftTemp = Sensor_Var->U16_filter_unit_result>>1u;
    PS32_ptr_FeedBack[CASCADE_LEVEL1] += (S32)U16_ShiftTemp;
    U16_ShiftTemp >>=2u;
    PS32_ptr_FeedBack[CASCADE_LEVEL1] += (S32)U16_ShiftTemp;
    PS32_ptr_FeedBack[CASCADE_LEVEL1] += PS32_ptr_FeedBack[CASCADE_LEVEL2];

    /* B2 = 1  */
    PS32_ptr_FeedBack[CASCADE_LEVEL2] = (S32)U16_filter_input;
    /* A2 = -0.25 = -(1/4)   */
    U16_ShiftTemp = Sensor_Var->U16_filter_unit_result >> 2u;
    PS32_ptr_FeedBack[CASCADE_LEVEL2] -= (S32)U16_ShiftTemp;

}


STATIC void sensor_lock_iir_filter (TASK_SENSOR_VAR_T * Sensor_Var,U16 U16_filter_input)
{  
    S32 S32_FeedbackSum;
    U32 U32_ShiftTemp;

    S32* PS32_ptr_FeedBack = Sensor_Var->S32_Filt_FeedbackBuffer;/*get feedback buffer pointer*/

    /* B0 = 1; A0=1*/
    S32_FeedbackSum=(S32)U16_filter_input + PS32_ptr_FeedBack[CASCADE_LEVEL1];
    if(0 > S32_FeedbackSum)
    {
        S32_FeedbackSum = 0;
    }
    else
    {
        /* value is ok */
    }
    /* B1 = 2 */
    U32_ShiftTemp = ((U32)U16_filter_input)<<1u;
    PS32_ptr_FeedBack[CASCADE_LEVEL1] = (S32) U32_ShiftTemp;
    /* A1 = 1.625 = 1 + 1/2+ 1/8  */

    PS32_ptr_FeedBack[CASCADE_LEVEL1] += S32_FeedbackSum;
    U32_ShiftTemp = ((U32)S32_FeedbackSum)>>1u;
    PS32_ptr_FeedBack[CASCADE_LEVEL1] += (S32)U32_ShiftTemp;
    U32_ShiftTemp >>=2u;
    PS32_ptr_FeedBack[CASCADE_LEVEL1] += (S32)U32_ShiftTemp;

    PS32_ptr_FeedBack[CASCADE_LEVEL1] += PS32_ptr_FeedBack[CASCADE_LEVEL2];

    /* B2 = 1  */
    PS32_ptr_FeedBack[CASCADE_LEVEL2] = (S32)U16_filter_input;
    /* A2 = -0.6875 = -(1/2 + 1/8 + 1/16)   */
    U32_ShiftTemp = ((U32)S32_FeedbackSum)>>1u;
    PS32_ptr_FeedBack[CASCADE_LEVEL2] -= (S32)U32_ShiftTemp;
    U32_ShiftTemp >>=2u;
    PS32_ptr_FeedBack[CASCADE_LEVEL2] -= (S32)U32_ShiftTemp;
    U32_ShiftTemp >>=1u;
    PS32_ptr_FeedBack[CASCADE_LEVEL2] -= (S32)U32_ShiftTemp;

    /* need to reduce result to prevent overflows*/

    U32_ShiftTemp= ((U32)S32_FeedbackSum)>>3u;

    /* make sure output does not overflow*/
    if((U32)U16_MAX < U32_ShiftTemp)
    {
        Sensor_Var->U16_filter_unit_result = U16_MAX;
    }
    else
    {
        Sensor_Var->U16_filter_unit_result = (U16)U32_ShiftTemp;
    }
      
}

STATIC void sensor_noise_detect(TASK_SENSOR_VAR_T * Sensor_Var,U16 U16_filter_input)
{
    S16 S16_Diff1;
    S16 S16_Diff2;
    S16* PS16_ptr_FeedBack = Sensor_Var->S16_NoiseDet_FeedbackBuffer;/*get feedback buffer pointer*/
    /* do serial differences */
    S16_Diff1 = (S16)U16_filter_input - PS16_ptr_FeedBack[MEMORY_DEPTH_1];
    S16_Diff2 = S16_Diff1 - PS16_ptr_FeedBack[MEMORY_DEPTH_2];

    /* forward memory */
    PS16_ptr_FeedBack[MEMORY_DEPTH_2] = S16_Diff1;
    PS16_ptr_FeedBack[MEMORY_DEPTH_1] = (S16)U16_filter_input;

    /* take absolute*/
    if(0 > S16_Diff2)
    {
        S16_Diff2 = -S16_Diff2;
    }
    else
    {
        /* is already absolute */
    }
    /* test against threshold */
    if( ((U16)S16_Diff2) > Sensor_Var->U16_NoiseThresh)
    {
        Sensor_Var->BO_noise_detected = TRUE;
    }
    else
    {
        Sensor_Var->BO_noise_detected = FALSE;
    }

}

#endif